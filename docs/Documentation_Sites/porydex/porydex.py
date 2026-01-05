import argparse
import json
import pathlib
import os
from copy import deepcopy

import porydex.config
import porydex.showdown

from typing import Optional, Set, Dict, Any


def _strip_max_prefix_from_key(key: str) -> Optional[str]:
    if key.startswith("gmax") and len(key) > 4:
        return key[4:]
    if key.startswith("max") and len(key) > 3:
        return key[3:]
    return None


def _strip_max_prefix_from_name(name: str) -> str:
    if name.startswith("G-Max "):
        return name[6:]
    if name.startswith("Max "):
        return name[4:]
    return name


def _iter_learnset_move_keys(learnsets: Dict[str, Any]) -> Set[str]:
    refs: Set[str] = set()
    for _, mon_data in learnsets.items():
        ls = mon_data.get("learnset")
        if isinstance(ls, dict):
            refs.update(ls.keys())
    return refs


def _fixup_moves_missing_from_learnsets(moves: Dict[str, Any], learnsets: Dict[str, Any]) -> None:
    # If learnsets reference a move key that doesn't exist in moves,
    # try to resolve it by stripping Max/G-Max prefixes (or the reverse).
    refs = _iter_learnset_move_keys(learnsets)

    for key in sorted(refs):
        if key in moves:
            continue

        base = _strip_max_prefix_from_key(key)
        if base and base in moves:
            moves[key] = deepcopy(moves[base])
            continue

        # Reverse: learnsets might reference a stripped key, while moves only has max/gmax.
        for pref in ("gmax", "max"):
            alt = pref + key
            if alt in moves:
                m2 = deepcopy(moves[alt])
                if "name" in m2:
                    m2["name"] = _strip_max_prefix_from_name(m2["name"])
                moves[key] = m2
                break

    for key in sorted(refs):
        if key in moves:
            continue

        base = _strip_max_prefix_from_key(key)
        if base and base in moves:
            moves[key] = deepcopy(moves[base])
            continue

        # Reverse: learnsets might reference a stripped key, while moves only has max/gmax.
        for pref in ("gmax", "max"):
            alt = pref + key
            if alt in moves:
                m = deepcopy(moves[alt])
                if "name" in m:
                    m["name"] = _strip_max_prefix_from_name(m["name"])
                moves[key] = m
                break

from porydex.common import PICKLE_PATH, name_key
from porydex.parse.abilities import parse_abilities
from porydex.parse.encounters import parse_encounters
from porydex.parse.form_tables import parse_form_tables
from porydex.parse.items import parse_items
from porydex.parse.learnsets import parse_level_up_learnsets, parse_teachable_learnsets
from porydex.parse.maps import parse_maps
from porydex.parse.moves import parse_moves
from porydex.parse.national_dex import parse_national_dex_enum
from porydex.parse.species import parse_species

MAX_SPECIES_EXPANSION = 1524 + 1

def prepend_file(f, s: str):
    f_data = f.read()
    f.seek(0, 0)
    f.write(s + f_data)

def config_show(_):
    porydex.config.load()
    print(f'compiler command:  {str(porydex.config.compiler)}')
    print(f'path to expansion: {str(porydex.config.expansion)}')
    print(f'output directory:  {str(porydex.config.output)}')
    print(f'output format:     {str(porydex.config.format)}')
    print(f'include mons file: {str(porydex.config.included_mons_file)}')
    print(f'custom abilities:  {str(porydex.config.custom_ability_defs)}')

def config_set(args):
    if args.expansion:
        assert args.expansion.resolve().exists(), f'specified expansion directory {args.expansion} does not exist'
        porydex.config.expansion = args.expansion.resolve()

    porydex.config.load()
    update = False

    if args.compiler:
        porydex.config.compiler = args.compiler
        update = True

    if args.output:
        porydex.config.output = args.output.resolve()
        update = True

    if args.format:
        porydex.config.format = args.format
        update = True

    if args.included_species_file:
        porydex.config.included_mons_file = args.included_species_file
        update = True

    if args.custom_ability_defs:
        porydex.config.custom_ability_defs = args.custom_ability_defs
        update = True

    if update:
        porydex.config.save()
    else:
        print('No config options given; nothing to do')

def config_clear(_):
    porydex.config.clear()

def extract(args):
    if args.reload:
        for f in PICKLE_PATH.glob('*'):
            os.remove(f)

    porydex.config.load()

    [path.mkdir(parents=True) if not path.exists() else () for path in (PICKLE_PATH, porydex.config.output)]

    expansion_data = porydex.config.expansion / 'src' / 'data'
    custom_headers = pathlib.Path('custom_headers')
    moves = parse_moves(expansion_data / 'moves_info.h')
    # Dense array indexed by move id (num). This prevents misalignment if the moves
    # mapping ever contains duplicates/aliases.
    max_num = max((int(m.get('num', 0)) for m in moves.values()), default=0)
    move_names = [''] * (max_num + 1)
    for m in moves.values():
        num = int(m.get('num', 0))
        if 0 <= num <= max_num:
            move_names[num] = str(m.get('name', ''))
    abilities = parse_abilities(expansion_data / 'abilities.h')
    items = parse_items(expansion_data / 'items.h')
    forms = parse_form_tables(expansion_data / 'pokemon' / 'form_species_tables.h')
    map_sections = parse_maps(expansion_data / 'region_map' / 'region_map_entries.h')
    valid_move_keys = set(moves.keys())
    lvlup_learnsets = parse_level_up_learnsets(porydex.config.expansion / 'src' / 'data' / 'pokemon' / 'level_up_learnsets' / 'gen_9.h', move_names, valid_move_keys)
    teach_learnsets = parse_teachable_learnsets(expansion_data / 'pokemon' / 'teachable_learnsets.h', move_names, valid_move_keys)
    national_dex = parse_national_dex_enum(porydex.config.expansion / 'include' / 'constants' / 'pokedex.h')

    included_mons = []
    if porydex.config.included_mons_file:
        with open(porydex.config.included_mons_file, 'r', encoding='utf-8') as included:
            included_mons = list(filter(lambda s: len(s) > 0, map(lambda s: s.strip(), included.readlines())))

    species, learnsets = parse_species(
        expansion_data / 'pokemon' / 'species_info.h',
        abilities,
        items,
        move_names,
        forms,
        map_sections,
        lvlup_learnsets,
        teach_learnsets,
        national_dex,
        included_mons,
    )
    _fixup_moves_missing_from_learnsets(moves, learnsets)

    species_names = ['????????????'] * (MAX_SPECIES_EXPANSION + 1)
    for mon in species.values():
        if mon.get('cosmetic', False):
            species_names[mon['num']] = mon['name'].split('-')[0]
        else:
            species_names[mon['num']] = mon['name']

    # cleanup cosmetic forms and missingno from species
    to_purge = ['missingno']
    for key, mon in species.items():
        if mon.get('cosmetic', False):
            to_purge.append(key)
    for key in to_purge:
        species.pop(key, None)


    # species_names = [mon['name'] for mon in sorted(species.values(), key=lambda m: m['num'])]
    encounters = parse_encounters(expansion_data / 'wild_encounters.h', species_names)

    # Re-index num to nationalDex on the species before finishing up
    for _, mon in species.items():
        nd = mon.pop('nationalDex', None)
        if nd is not None:
            mon['num'] = nd

    if porydex.config.format == porydex.config.OutputFormat.json:
        with open(porydex.config.output / 'moves.json', 'w', encoding='utf-8') as outf:
            json.dump(moves, outf, indent=4, ensure_ascii=False)

        with open(porydex.config.output / 'species.json', 'w', encoding='utf-8') as outf:
            json.dump(species, outf, indent=4, ensure_ascii=False)

        with open(porydex.config.output / 'learnsets.json', 'w', encoding='utf-8') as outf:
            json.dump(learnsets, outf, indent=4, ensure_ascii=False)

        with open(porydex.config.output / 'encounters.json', 'w', encoding='utf-8') as outf:
            json.dump(encounters, outf, indent=4, ensure_ascii=False)
    else: # showdown
        porydex.showdown.index(moves, species, learnsets, encounters, items)

def main():
    argp = argparse.ArgumentParser(prog='porydex',
                                   description='generate data exports from pokeemerald-expansion for showdown dex')
    subp = argp.add_subparsers(required=True)

    config_p = subp.add_parser('config', help='configuration options for porydex')
    config_subp = config_p.add_subparsers(required=True)

    config_show_p = config_subp.add_parser('show', help='show configured options for porydex')
    config_show_p.set_defaults(func=config_show)

    config_set_p = config_subp.add_parser('set', help='set configurable options for porydex')
    config_set_p.add_argument('-e', '--expansion', action='store',
                              help='path to the root of your pokeemerald-expansion repository; default: ../pokeemerald-expansion',
                              type=pathlib.Path)
    config_set_p.add_argument('-c', '--compiler', action='store',
                              help='command for or path to the compiler to be used for pre-processing; default: gcc',
                              type=pathlib.Path)
    config_set_p.add_argument('-o', '--output', action='store',
                              help='path to output directory for extracted data files; default: ./out',
                              type=pathlib.Path)
    config_set_p.add_argument('-f', '--format',
                              help='format for output files',
                              type=porydex.config.OutputFormat.argparse,
                              choices=list(porydex.config.OutputFormat))
    config_set_p.add_argument('-i', '--included-species-file',
                              help='text file describing species to be included in the pokedex',
                              type=pathlib.Path)
    config_set_p.add_argument('-a', '--custom-ability-defs',
                              help='JSON file describing custom ability definitions and descriptions for a Showdown Dex',
                              type=pathlib.Path)
    config_set_p.set_defaults(func=config_set)

    config_clear_p = config_subp.add_parser('clear', help='clear configured options')
    config_clear_p.set_defaults(func=config_clear)

    extract_p = subp.add_parser('extract', help='run data extraction')
    extract_p.add_argument('--reload', action='store_true',
                           help='if specified, flush the cache of parsed data and reload from expansion')
    extract_p.set_defaults(func=extract)

    args = argp.parse_args()
    args.func(args)

if __name__ == '__main__':
    main()

