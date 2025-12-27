from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import re
from typing import Dict, List, Tuple, Optional


_DEFINE_RE = re.compile(r'^\s*#\s*define\s+(SPECIES_[A-Z0-9_]+)\s+(.+?)\s*(?:/\*.*\*/)?$')


def _strip_c_comments(s: str) -> str:
    # Remove /* ... */ and // ... comments (good enough for headers)
    s = re.sub(r'/\*.*?\*/', '', s, flags=re.S)
    s = re.sub(r'//.*', '', s)
    return s


def load_species_defines(species_h: str | Path) -> Tuple[Dict[str, int], Dict[int, List[str]]]:
    """
    Parse include/constants/species.h and resolve:
      - token_to_id: SPECIES_* -> integer
      - id_to_tokens: integer -> list of SPECIES_* tokens that resolve to it (aliases included)
    """
    species_h = Path(species_h)
    raw = species_h.read_text(encoding='utf-8', errors='replace')
    token_to_rhs: Dict[str, str] = {}

    for line in raw.splitlines():
        m = _DEFINE_RE.match(line)
        if not m:
            continue
        tok, rhs = m.group(1), m.group(2).strip()
        rhs = _strip_c_comments(rhs).strip()
        if not rhs:
            continue
        # Only keep the first token/number on the rhs to avoid weird macro tails
        rhs = rhs.split()[0]
        token_to_rhs[tok] = rhs

    resolving: Dict[str, int] = {}

    def resolve(tok: str, stack: Optional[List[str]] = None) -> Optional[int]:
        if tok in resolving:
            return resolving[tok]
        if stack is None:
            stack = []
        if tok in stack:
            return None  # cycle
        stack.append(tok)
        rhs = token_to_rhs.get(tok)
        if rhs is None:
            stack.pop()
            return None
        if rhs.isdigit():
            val = int(rhs, 10)
            resolving[tok] = val
            stack.pop()
            return val
        if rhs.startswith('0x') or rhs.startswith('0X'):
            try:
                val = int(rhs, 16)
            except ValueError:
                stack.pop()
                return None
            resolving[tok] = val
            stack.pop()
            return val
        if rhs.startswith('SPECIES_'):
            val = resolve(rhs, stack)
            if val is not None:
                resolving[tok] = val
            stack.pop()
            return val
        stack.pop()
        return None

    token_to_id: Dict[str, int] = {}
    id_to_tokens: Dict[int, List[str]] = {}

    for tok in list(token_to_rhs.keys()):
        val = resolve(tok, [])
        if val is None:
            continue
        token_to_id[tok] = val
        id_to_tokens.setdefault(val, []).append(tok)

    # Keep id_to_tokens stable: sort by "descriptiveness" (longer + more underscores first)
    for sid, toks in id_to_tokens.items():
        toks.sort(key=lambda t: (t.count('_'), len(t)), reverse=True)

    return token_to_id, id_to_tokens


_REGION_SUFFIX_MAP = {
    'ALOLAN': 'Alola',
    'GALAR': 'Galar',
    'GALARIAN': 'Galar',
    'HISUI': 'Hisui',
    'HISUIAN': 'Hisui',
    'PALDEA': 'Paldea',
    'PALDEAN': 'Paldea',
}


def _title_token(tok: str) -> str:
    if tok.isdigit():
        return tok
    if tok in _REGION_SUFFIX_MAP:
        return _REGION_SUFFIX_MAP[tok]
    if tok == 'FEMALE':
        return 'F'
    if tok == 'MALE':
        return 'M'
    # Keep some common abbreviations
    if tok in ('GMAX', 'TOTEM'):
        return tok.title().replace('Max', 'Max')  # "Gmax" -> "Gmax", will be normalized by showdown hacks anyway
    return tok.title()


def _derive_form_label(species_token: str) -> str:
    """
    From SPECIES_LYCANROC_MIDDAY -> "Midday"
    From SPECIES_ALCREMIE_STRAWBERRY_VANILLA_CREAM -> "Strawberry-Vanilla-Cream"
    From SPECIES_LILLIGANT_HISUIAN -> "Hisui"
    """
    body = species_token.removeprefix('SPECIES_')
    parts = body.split('_')
    if len(parts) <= 1:
        return 'Base'
    form_parts = parts[1:]
    # Reduce "RAPID_STRIKE_STYLE" -> "Rapid-Strike-Style" (species.py has a hack for removing "-Style")
    label_parts = [_title_token(p) for p in form_parts if p]
    label = '-'.join(label_parts).replace('--', '-').strip('-')
    return label or 'Base'


def _find_project_root(start: Path) -> Optional[Path]:
    p = start.resolve()
    for _ in range(10):
        candidate = p / 'include' / 'constants' / 'species.h'
        if candidate.exists():
            return p
        if p.parent == p:
            break
        p = p.parent
    return None


_ARRAY_DECL_RE = re.compile(
    r'\b(?:static\s+)?(?:const\s+)?u16\s+(s[A-Za-z0-9_]*FormSpeciesIdTable)\s*\[\s*\]\s*=\s*\{',
    re.M
)


def _extract_brace_block(text: str, start_idx: int) -> Tuple[str, int]:
    """
    Given index at the '{' after the array decl, return (contents_inside, end_idx_after_closing_brace).
    """
    i = start_idx
    while i < len(text) and text[i] != '{':
        i += 1
    if i >= len(text) or text[i] != '{':
        return '', start_idx
    depth = 0
    i += 1
    depth = 1
    content_start = i
    in_str = False
    esc = False
    while i < len(text) and depth > 0:
        c = text[i]
        if in_str:
            if esc:
                esc = False
            elif c == '\\':
                esc = True
            elif c == '"':
                in_str = False
        else:
            if c == '"':
                in_str = True
            elif c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
        i += 1
    content = text[content_start:i-1] if depth == 0 else text[content_start:]
    return content, i


def parse_form_tables(form_species_tables_h: str | Path) -> Dict[str, Dict[int, str]]:
    """
    Parse src/data/pokemon/form_species_tables.h and produce:
      { "sLycanrocFormSpeciesIdTable": {745:"Midday", 1173:"Midnight", ...}, ... }

    Order matters: dict preserves insertion order and species.py checks the first entry as base.
    """
    form_species_tables_h = Path(form_species_tables_h)
    root = _find_project_root(form_species_tables_h)
    if root is None:
        raise FileNotFoundError("Couldn't locate project root containing include/constants/species.h")

    token_to_id, id_to_tokens = load_species_defines(root / 'include' / 'constants' / 'species.h')

    raw = form_species_tables_h.read_text(encoding='utf-8', errors='replace')
    raw = _strip_c_comments(raw)

    out: Dict[str, Dict[int, str]] = {}

    for m in _ARRAY_DECL_RE.finditer(raw):
        table_name = m.group(1)
        brace_idx = m.end() - 1  # near '{'
        body, end_idx = _extract_brace_block(raw, brace_idx)
        if not body:
            continue

        entries: List[int] = []
        for item in body.split(','):
            item = item.strip()
            if not item:
                continue
            # Stop tokens
            if item in ('FORM_SPECIES_END', 'SPECIES_NONE', 'SPECIES_EGG', '0', '0U', '0u'):
                break

            # Resolve to id
            sid: Optional[int] = None
            if item.isdigit():
                sid = int(item, 10)
            elif item.startswith('0x') or item.startswith('0X'):
                try:
                    sid = int(item, 16)
                except ValueError:
                    sid = None
            elif item.startswith('SPECIES_'):
                sid = token_to_id.get(item)
                if sid is None:
                    # try to resolve via aliases list
                    # (if token not in header, skip)
                    sid = None
            if sid is None:
                continue
            entries.append(sid)

        if not entries:
            continue

        table: Dict[int, str] = {}
        used_labels: Dict[str, int] = {}
        for sid in entries:
            # Choose the most descriptive token for this sid, if any (helps with aliases like _F)
            tok = (id_to_tokens.get(sid) or [None])[0]
            label = _derive_form_label(tok) if tok else 'Base'
            # Ensure uniqueness
            base_label = label
            k = used_labels.get(base_label, 0)
            if k:
                label = f'{base_label}-{k+1}'
            used_labels[base_label] = k + 1
            table[sid] = label

        out[table_name] = table

    return out
