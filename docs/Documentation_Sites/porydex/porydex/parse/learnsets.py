import collections
import pathlib
import re

import porydex.config

from pycparser.c_ast import Decl, ExprList
from yaspin import yaspin

from porydex.common import name_key
from porydex.parse import extract_int, load_data_and_start


def _resolve_move_key(move_id: int,
                      move_names: list[str],
                      valid_move_keys: set[str] | None = None) -> str | None:
    """Resolve the canonical move key for a numeric move id.

    Some ROMs keep the MOVE_G_MAX_* constant names but rename the in-game move
    (e.g. "G-Max Vine Lash" -> "Vine Lash"). We prefer the key derived from
    the in-game name, and (optionally) fall back by stripping 'gmax'/'max'
    prefixes if needed.
    """
    if move_id < 0 or move_id >= len(move_names):
        return None

    move_name = (move_names[move_id] or '').strip()
    if not move_name:
        return None

    key = name_key(move_name)
    if valid_move_keys is None or key in valid_move_keys:
        return key

    # Fallback: strip common Max/G-Max prefixes used by Showdown ids.
    if key.startswith('gmax'):
        alt = key[4:]
        if alt in valid_move_keys:
            return alt
    if key.startswith('max'):
        alt = key[3:]
        if alt in valid_move_keys:
            return alt

    return key


def _prefer_levelup_gen9(fname: pathlib.Path) -> pathlib.Path:
    """Prefer the generated Gen 9 level-up learnset header if present.

    This avoids relying on aggregate headers that may not include the latest generated file.
    """
    candidates = [
        porydex.config.expansion / 'src' / 'data' / 'pokemon' / 'level_up_learnsets' / 'gen_9.h',
        fname.parent / 'gen_9.h',
        fname.parent / 'level_up_learnsets' / 'gen_9.h',
        fname,
    ]
    for c in candidates:
        try:
            if c and c.exists():
                return c
        except Exception:
            pass
    return fname

def parse_level_up_learnset(
    decl: Decl,
    move_names: list[str],
    valid_move_keys: set[str] | None = None,
) -> dict[str, list[int]]:
    learnset = collections.defaultdict(list)
    entry_inits = decl.init.exprs
    for entry in entry_inits:
        move = extract_int(entry.exprs[0].expr)
        if move == 0xFFFF:
            break

        level = extract_int(entry.exprs[1].expr)
        move_key = _resolve_move_key(move, move_names, valid_move_keys)
        if move_key is None:
            continue
        learnset[move_key].append(level)

    return learnset

def parse_teachable_learnset(
    decl: Decl,
    move_names: list[str],
    tm_moves: list[str],
    valid_move_keys: set[str] | None = None,
) -> dict[str, list[str]]:
    learnset = {
        'm': [],
        't': [],
    }
    entry_inits = decl.init.exprs
    for entry in entry_inits:
        move = extract_int(entry)
        if move == 0xFFFF:
            break

        move_name = move_names[move] if 0 <= move < len(move_names) else ''
        if not move_name:
            continue

        move_key = _resolve_move_key(move, move_names, valid_move_keys)
        if move_key is None:
            continue

        if move_name in tm_moves:
            learnset['m'].append(move_key)
        else:
            learnset['t'].append(move_key)

    return learnset

def parse_level_up_learnsets_data(
    decls: list[Decl],
    move_names: list[str],
    valid_move_keys: set[str] | None = None,
) -> dict[str, dict[str, list[int]]]:
    return {
        decl.name: parse_level_up_learnset(decl, move_names, valid_move_keys)
        for decl in decls
    }

def parse_teachable_learnsets_data(
    decls: list[Decl],
    move_names: list[str],
    tm_moves: list[str],
    valid_move_keys: set[str] | None = None,
) -> dict[str, dict[str, list[str]]]:
    return {
        decl.name: parse_teachable_learnset(decl, move_names, tm_moves, valid_move_keys)
        for decl in decls
    }

def parse_level_up_learnsets(fname: pathlib.Path,
                             move_names: list[str],
                             valid_move_keys: set[str] | None = None) -> dict[str, dict[str, list[int]]]:
    fname = _prefer_levelup_gen9(fname)
    pattern = re.compile(r's(\w+)LevelUpLearnset')
    data: ExprList
    start: int

    with yaspin(text=f'Loading level-up learnsets: {fname}', color='cyan') as spinner:
        data, start = load_data_and_start(
            fname,
            pattern,
            extra_includes=[
                rf'-I{porydex.config.expansion}/src',
                r'-include', r'constants/moves.h',
            ]
        )
        spinner.ok("✅")

    return parse_level_up_learnsets_data(data[start:], move_names, valid_move_keys)

def parse_teachable_learnsets(fname: pathlib.Path,
                              move_names: list[str],
                              valid_move_keys: set[str] | None = None) -> dict[str, dict[str, list[str]]]:
    pattern = re.compile(r's(\w+)TeachableLearnset')
    data: ExprList
    start: int

    with yaspin(text=f'Loading teachable learnsets: {fname}', color='cyan') as spinner:
        data, start = load_data_and_start(
            fname,
            pattern,
            extra_includes=[
                rf'-I{porydex.config.expansion}/src',
                r'-include', r'constants/moves.h',
            ]
        )
        spinner.ok("✅")

    # Don't preprocess these files
    tm_moves = []
    tm_hm_list_file = porydex.config.expansion / 'include' / 'constants' / 'tms_hms.h'
    with yaspin(text=f'Loading TM/HM list: {tm_hm_list_file}', color='cyan') as spinner, open(tm_hm_list_file, 'r') as tm_hm_file:
        tm_moves = list({
            move.replace('_', ' ').title() for move in re.findall(r'F\((.*)\)', tm_hm_file.read())
        })
        spinner.ok("✅")

    return parse_teachable_learnsets_data(data[start:], move_names, tm_moves, valid_move_keys)

