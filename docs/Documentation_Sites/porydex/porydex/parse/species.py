from collections import defaultdict
from dataclasses import dataclass

import pathlib
import re

from pycparser.c_ast import Constant, ExprList, NamedInitializer
from yaspin import yaspin

from porydex.common import name_key
from porydex.model import ExpansionEvoMethod, DAMAGE_TYPE, EGG_GROUP, BODY_COLOR, EVO_METHOD
from porydex.parse import load_truncated, extract_id, extract_int, extract_u8_str

_RHH_EVO_METHOD_BY_NAME: dict[str, int] = {
    # constants/pokemon.h enum EvolutionMethods order in RHH 1.12
    'EVO_NONE': 0,
    'EVO_LEVEL': 1,
    'EVO_TRADE': 2,
    'EVO_ITEM': 3,
    'EVO_SPLIT_FROM_EVO': 4,
    'EVO_SCRIPT_TRIGGER': 5,
    'EVO_LEVEL_BATTLE_ONLY': 6,
    'EVO_BATTLE_END': 7,
    'EVO_SPIN': 8,
}


_RHH_EVO_METHOD_IDS = set(_RHH_EVO_METHOD_BY_NAME.values())

def _guess_pokemon_h_path(species_info_path: pathlib.Path | None = None) -> pathlib.Path | None:
    # Try common repo layouts
    candidates: list[pathlib.Path] = []
    here = pathlib.Path(__file__).resolve()
    for p in [here] + list(here.parents):
        candidates.extend([
            p / 'include' / 'constants' / 'pokemon.h',
            p / 'constants' / 'pokemon.h',
        ])
    if species_info_path is not None:
        for p in [species_info_path] + list(species_info_path.parents):
            candidates.extend([
                p / 'include' / 'constants' / 'pokemon.h',
                p / 'constants' / 'pokemon.h',
            ])
    cwd = pathlib.Path.cwd()
    candidates.extend([
        cwd / 'include' / 'constants' / 'pokemon.h',
        cwd / 'constants' / 'pokemon.h',
    ])
    for c in candidates:
        if c.exists():
            return c
    return None

def _load_rhh_evo_condition_id_to_name(pokemon_h: pathlib.Path) -> dict[int, str]:
    text = _safe_read_text(pokemon_h)
    if not text:
        return {}
    m = re.search(r'enum\s+EvolutionConditions\s*\{(.*?)\};', text, flags=re.S)
    if not m:
        return {}
    body = m.group(1)
    names: list[str] = []
    for line in body.splitlines():
        line = line.split('//', 1)[0].strip()
        if not line:
            continue
        line = line.rstrip(',')
        if '=' in line:
            name = line.split('=', 1)[0].strip()
        else:
            name = line.strip()
        if name:
            names.append(name)
    return {i: n for i, n in enumerate(names)}

_RHH_COND_ID_TO_NAME: dict[int, str] | None = None

def _cond_name(cond_id: int) -> str | None:
    global _RHH_COND_ID_TO_NAME
    if _RHH_COND_ID_TO_NAME is None:
        p = _guess_pokemon_h_path()
        _RHH_COND_ID_TO_NAME = _load_rhh_evo_condition_id_to_name(p) if p else {}
    return _RHH_COND_ID_TO_NAME.get(cond_id)

def _peel(node):
    # unwrap Cast / CompoundLiteral-like wrappers produced by pycparser/preprocessor
    for _ in range(8):
        if node is None:
            return None
        if hasattr(node, 'expr') and not hasattr(node, 'exprs'):
            node = getattr(node, 'expr')
            continue
        if hasattr(node, 'init'):
            node = getattr(node, 'init')
            continue
        if hasattr(node, 'args'):
            node = getattr(node, 'args')
            continue
        break
    return node

def _extract_conditions(cond_expr):
    """Return list of (cond_name, cond_param) from CONDITIONS(...) pointer initializer."""
    out = []
    if cond_expr is None:
        return out
    node = _peel(cond_expr)
    exprs = getattr(node, 'exprs', None)
    if exprs is None and hasattr(node, 'expr') and hasattr(node.expr, 'exprs'):
        exprs = node.expr.exprs
    if exprs is None:
        return out

    for entry in exprs:
        entry_node = _peel(entry)
        e = getattr(entry_node, 'exprs', None)
        if not e:
            continue
        # terminator is usually a single-field {CONDITIONS_END}
        if len(e) < 2:
            break
        try:
            cid = extract_id(e[0])
        except Exception:
            cid = extract_int(e[0])
        if isinstance(cid, int):
            cid = _cond_name(cid) or f'IF_{cid}'
        if cid == 'CONDITIONS_END':
            break
        try:
            cparam = extract_int(e[1])
        except Exception:
            cparam = extract_id(e[1])
        out.append((cid, cparam))
        
    return out


def _safe_read_text(path: pathlib.Path) -> str | None:
    try:
        return path.read_text(encoding='utf-8', errors='ignore')
    except Exception:
        return None


def _load_species_id_to_symbol(species_header: pathlib.Path) -> dict[int, str]:
    """Parse include/constants/species.h (or equivalent) to build {id: SYMBOL}.

    We only keep numeric definitions (aliases are skipped).
    """
    text = _safe_read_text(species_header)
    if not text:
        return {}

    out: dict[int, str] = {}
    # e.g. #define SPECIES_GRENINJA 658
    for m in re.finditer(r'^\s*#define\s+(SPECIES_[A-Z0-9_]+)\s+([0-9]+)\s*$', text, flags=re.M):
        sym = m.group(1)
        sid = int(m.group(2))
        out[sid] = sym.removeprefix('SPECIES_')
    return out


def _guess_repo_species_header(species_info_path: pathlib.Path) -> pathlib.Path | None:
    """Try to locate the species constants header relative to the species_info file."""
    candidates: list[pathlib.Path] = []
    for p in [species_info_path] + list(species_info_path.parents):
        candidates.extend([
            p / 'include' / 'constants' / 'species.h',
            p / 'constants' / 'species.h',
            p / 'include' / 'constants' / 'species.h',
            p / 'include' / 'constants' / 'species.h',
        ])
    # Also try cwd-based paths (common when running from repo root)
    cwd = pathlib.Path.cwd()
    candidates.extend([
        cwd / 'include' / 'constants' / 'species.h',
        cwd / 'constants' / 'species.h',
    ])

    for c in candidates:
        if c.exists():
            return c
    return None


def _pretty_forme_from_symbol_suffix(base_name: str, suffix: str) -> str:
    """Convert a SPECIES_* suffix (e.g. 'MEGA_X', 'ALOLA', 'BATTLE_BOND') into a showdown-ish forme label."""
    if not suffix:
        return 'Base'

    # Common normalization
    s = suffix
    s = s.replace('__', '_').strip('_')
    tokens = [t for t in s.split('_') if t]

    # Percent-y special cases
    if base_name == 'Zygarde':
        # We'll still apply a higher-level hack, but keep something sensible here.
        if tokens and tokens[0] in ('10', '50'):
            return f'{tokens[0]}%'

    # Showdown conventions (selected)
    replacements = {
        'MEGA': 'Mega',
        'PRIMAL': 'Primal',
        'ALOLA': 'Alola',
        'GALAR': 'Galar',
        'HISUI': 'Hisui',
        'PALDEA': 'Paldea',
        'ORIGIN': 'Origin',
        'ZEN': 'Zen',
        'SUNNY': 'Sunny',
        'RAINY': 'Rainy',
        'SNOWY': 'Snowy',
        'THERIAN': 'Therian',
        'INCARNATE': 'Incarnate',
        'GMAX': 'Gmax',
        'TOTEM': 'Totem',
        'SCHOOL': 'School',
        'BATTLE': 'Battle',
        'BOND': 'Bond',
        'ASH': 'Ash',
        'CROWNED': 'Crowned',
        'HANGRY': 'Hangry',
        'ETERNAL': 'Eternal',
        'METEOR': 'Meteor',
    }

    pretty_tokens: list[str] = []
    for t in tokens:
        if t.isdigit():
            pretty_tokens.append(t)
            continue
        pretty_tokens.append(replacements.get(t, t.title().replace('-', '')))

    # Keep common compound patterns stable
    # Mega X/Y
    if pretty_tokens[:2] == ['Mega', 'X']:
        return 'Mega-X'
    if pretty_tokens[:2] == ['Mega', 'Y']:
        return 'Mega-Y'

    return '-'.join(pretty_tokens)




def _normalize_form_label(label: str) -> str:
    """Normalize form labels to Pokémon Showdown naming conventions.

    Some datasets use demonyms like 'Hisuian/Alolan/Galarian/Paldean' while Showdown
    sprite and dex naming typically use the region name: 'Hisui/Alola/Galar/Paldea'.
    """
    if not label:
        return label

    regional = {
        'Hisuian': 'Hisui',
        'Alolan': 'Alola',
        'Galarian': 'Galar',
        'Paldean': 'Paldea',
    }

    for src, dst in regional.items():
        if label == src:
            return dst
        if label.startswith(src + '-'):
            return dst + label[len(src):]  # keep suffix (e.g. '-Tera')
    return label


def _apply_form_table_to_group(base_name: str, mons_sorted: list[dict], form_labels: list[str]) -> None:
    """Apply form metadata to a group of mons sharing the same formSpeciesIdTable."""
    if len(mons_sorted) <= 1:
        return

    base_mon = mons_sorted[0]
    labels = form_labels

    # Base mon
    if labels[0] != 'Base':
        base_mon['baseForme'] = labels[0]

    # Ugly Urshifu hack
    if base_mon.get('name') == 'Urshifu':
        base_mon['formeOrder'] = [base_mon['name'] + (f'-{labels[i].replace("-Style", "")}' if i > 0 else '') for i in range(len(labels))]
    # Ugly Xerneas hack
    elif base_mon.get('name') == 'Xerneas':
        base_mon['formeOrder'] = ['Xerneas', 'Xerneas-Neutral']
        base_mon['baseForme'] = 'Active'
    # Ugly Vivillon hack
    elif base_mon.get('name') == 'Vivillon':
        # showdown expects Meadow as default; keep same behavior as legacy code
        base_mon['formeOrder'] = [f'{base_mon["name"]}', f'{base_mon["name"]}-Icy-Snow']
        base_mon['formeOrder'].extend([
            f'{base_mon["name"]}-{labels[i]}'
            for i in range(len(labels))
            if labels[i] not in ('Base', COSMETIC_FORME_SPECIES[base_mon['name']].base)
        ])
    # Ugly Minior hack
    elif base_mon.get('name') == 'Minior':
        base_mon['formeOrder'] = [f'{base_mon["name"]}', f'{base_mon["name"]}-Meteor']
        base_mon['formeOrder'].extend([
            f'{base_mon["name"]}-{labels[i]}'
            for i in range(len(labels))
            if labels[i] not in ('Base', COSMETIC_FORME_SPECIES[base_mon['name']].base) and 'Meteor' not in labels[i]
        ])
    # Ugly Zygarde hack
    elif base_mon.get('name') == 'Zygarde':
        base_mon['formeOrder'] = ['Zygarde', 'Zygarde-10%', 'Zygarde-Complete']
        base_mon['baseForme'] = '50%'
    # Ugly Greninja hack
    elif base_mon.get('name') == 'Greninja':
        base_mon['formeOrder'] = ['Greninja', 'Greninja-Ash']
        base_mon['baseForme'] = 'Base'
    else:
        base_mon['formeOrder'] = [
            base_mon['name'] + (f'-{labels[i]}' if i > 0 else '')
            for i in range(len(labels))
        ]

    # Cosmetic Formes
    cosmetics = None if base_mon.get('name') in NON_COSMETIC_FORM_BASES else COSMETIC_FORME_SPECIES.get(base_mon['name'], None)
    if cosmetics:
        if cosmetics.alts is not None:
            base_mon['cosmeticFormes'] = [
                f'{base_mon["name"]}-{labels[i]}'
                for i in range(len(labels))
                if labels[i] not in ('Base', '', cosmetics.base)
                    and labels[i] not in cosmetics.alts
                    and (cosmetics.exclude_pattern is None or not re.match(cosmetics.exclude_pattern, labels[i]))
            ]
            base_mon['baseForme'] = cosmetics.base

            if cosmetics.alts:
                base_mon['otherFormes'] = list(map(lambda alt: f'{base_mon["name"]}-{alt}', cosmetics.alts))
    else:
        base_mon['otherFormes'] = base_mon['formeOrder'][1:]

    # Alternate mons
    for mon, label in zip(mons_sorted[1:], labels[1:]):
        form_name = label
        # ugly xerneas neutral-active swap
        if mon.get('name') == 'Xerneas':
            form_name = 'Neutral'
        # ugly urshifu forms hack
        elif mon.get('name') == 'Urshifu':
            form_name = form_name.replace('-Style', '')

        mon['baseSpecies'] = base_mon['name']
        mon['forme'] = form_name
        mon['name'] = f'{base_mon["name"]}-{form_name}'


EXPANSION_GEN9_START = 1289
VANILLA_GEN9_START = 906
EXPANSION_GEN9_OFFSET = EXPANSION_GEN9_START - VANILLA_GEN9_START

@dataclass
class CosmeticFormes:
    base: str
    alts: list[str] | None
    exclude_pattern: str | None

COSMETIC_FORME_SPECIES: dict[str, CosmeticFormes] = {
    'Unown': CosmeticFormes('A', [], None),
    'Vivillon': CosmeticFormes('Meadow', [], None), # Technically, Fancy and Poke Ball are alt forms and not cosmetic, but eff that
    'Furfrou': CosmeticFormes('Natural', [], None),
    'Spewpa': CosmeticFormes('Icy-Snow', None, None),
    'Scatterbug': CosmeticFormes('Icy-Snow', None, None),
    'Burmy': CosmeticFormes('Plant', [], None),
    'Mothim': CosmeticFormes('Plant', None, None),
    'Shellos': CosmeticFormes('West', [], None),
    'Gastrodon': CosmeticFormes('West', [], None),
    'Flabébé': CosmeticFormes('Red', [], None),
    'Floette': CosmeticFormes('Red', ['Eternal'], None),
    'Florges': CosmeticFormes('Red', [], None),
    'Tatsugiri': CosmeticFormes('Curly', [], None),
    'Minior': CosmeticFormes('Red', ['Meteor'], r'Meteor-*'),
    'Alcremie': CosmeticFormes('Vanilla-Cream', ['Gmax'], None),
}

# Some hacks implement these 'forms' as gameplay-relevant (different typing/stats),
# so they must not be treated as cosmetic-only.
NON_COSMETIC_FORM_BASES: set[str] = {'Deerling', 'Sawsbuck'}


@dataclass
class SpecialAbilities:
    form: str
    ability: str

SPECIAL_ABILITIES: dict[str, SpecialAbilities] = {
    'Greninja': SpecialAbilities('Bond', 'Battle Bond'),
    'Zygarde': SpecialAbilities('Power-Construct', 'Power Construct'),
}

def parse_mon(struct_init: NamedInitializer,
              ability_names: list[str],
              item_names: list[str],
              form_tables: dict[str, dict[int, str]],
              level_up_learnsets: dict[str, dict[str, list[int]]],
              teachable_learnsets: dict[str, dict[str, list[str]]],
              national_dex: dict[str, int]) -> tuple[dict, list, dict, dict]:
    init_list = struct_init.expr.exprs
    mon = {}
    mon['num'] = extract_int(struct_init.name[0])
    mon['baseStats'] = {}
    mon['types'] = []
    mon['evYields'] = {}
    mon['items'] = {}
    mon['eggGroups'] = []

    evos = []
    lvlup_learnset = {}
    teach_learnset = {}

    for field_init in init_list:
        field_name = field_init.name[0].name
        field_expr = field_init.expr

        match field_name:
            case 'baseHP':
                mon['baseStats']['hp'] = extract_int(field_expr)
            case 'baseAttack':
                mon['baseStats']['atk'] = extract_int(field_expr)
            case 'baseDefense':
                mon['baseStats']['def'] = extract_int(field_expr)
            case 'baseSpeed':
                mon['baseStats']['spe'] = extract_int(field_expr)
            case 'baseSpAttack':
                mon['baseStats']['spa'] = extract_int(field_expr)
            case 'baseSpDefense':
                mon['baseStats']['spd'] = extract_int(field_expr)
            case 'types':
                types = [DAMAGE_TYPE[extract_int(t)] for t in field_expr.exprs]
                unique_types = []
                [unique_types.append(t) for t in types if t not in unique_types]
                mon['types'].extend(unique_types)
            case 'catchRate':
                mon['catchRate'] = extract_int(field_expr)
            case 'expYield':
                mon['expYield'] = extract_int(field_expr)
            case 'evYield_HP':
                mon['evYields']['hp'] = extract_int(field_expr)
            case 'evYield_Attack':
                mon['evYields']['atk'] = extract_int(field_expr)
            case 'evYield_Defense':
                mon['evYields']['def'] = extract_int(field_expr)
            case 'evYield_Speed':
                mon['evYields']['spe'] = extract_int(field_expr)
            case 'evYield_SpAttack':
                mon['evYields']['spa'] = extract_int(field_expr)
            case 'evYield_SpDefense':
                mon['evYields']['spd'] = extract_int(field_expr)
            case 'genderRatio':
                # If the field expression is a constant, then we can just pull it out and do a quick
                # evaluation against known constants to map to the appropriate gender
                gendered = True
                female = 0
                if isinstance(field_expr, Constant):
                    val = extract_int(field_expr)
                    match val:
                        case 0xFF:
                            gendered = False
                        case 0xFE | 0x00:
                            female = val / 0xFE
                        case _:
                            raise ValueError('unrecognized gender constant: ', val)
                else:
                    # Female % is nested as a raw constant inside a ternary; we can just pull it straight out
                    female = float(field_expr.iffalse.left.left.value) / 100

                if gendered:
                    male = 1 - female
                    mon['genderRatio'] = { 'M': male, 'F': female }
                else:
                    mon['gender'] = 'N'
            case 'eggGroups':
                group_1 = extract_int(field_expr.exprs[0])
                group_2 = extract_int(field_expr.exprs[1])
                mon['eggGroups'].append(EGG_GROUP[group_1])
                if group_2 != group_1:
                    mon['eggGroups'].append(EGG_GROUP[group_2])
            case 'abilities':
                # ability index 0 in expansion means do not output to showdown
                # all mons have at least 1 ability
                ability_0 = extract_int(field_expr.exprs[0])
                ability_1, ability_H = 0, 0
                if len(field_expr.exprs) > 1:
                    ability_1 = extract_int(field_expr.exprs[1])
                if len(field_expr.exprs) > 2:
                    ability_H = extract_int(field_expr.exprs[2])

                mon['abilities'] = { '0': ability_names[ability_0] }
                if ability_1 != 0 and ability_1 != ability_0:
                    mon['abilities']['1'] = ability_names[ability_1]
                if ability_H != 0 and ability_H != ability_0:
                    mon['abilities']['H'] = ability_names[ability_H]
            case 'bodyColor':
                mon['color'] = BODY_COLOR[extract_int(field_expr)]
            case 'speciesName':
                name = extract_u8_str(field_expr).replace('♂', '-M').replace('♀', '-F')
                if name == '??????????':
                    name = 'MissingNo.'
                mon['name'] = name
            case 'natDexNum':
                mon['nationalDex'] = national_dex[extract_id(field_expr)]
            case 'height':
                # Stored in expansion as M * 10
                mon['heightm'] = extract_int(field_expr) / 10
            case 'weight':
                # Stored in expansion as KG * 10
                mon['weightkg'] = extract_int(field_expr) / 10
            case 'itemRare':
                mon['items']['R'] = item_names[extract_int(field_expr)]
            case 'itemUncommon':
                mon['items']['U'] = item_names[extract_int(field_expr)]
            case 'formSpeciesIdTable':
                # Defer: RHH 1.12 changed how form tables are represented.
                # We'll resolve these tables after the first parsing pass.
                mon['_formTableId'] = extract_id(field_expr)
            case 'evolutions':

                # general schema from RHH 1.12: {method_id, method_param, target_species, optional CONDITIONS(...)}

                for evo_method in field_expr.init.exprs:

                    method_raw = evo_method.exprs[0]

                    is_rhh_method = False

                    method_raw = evo_method.exprs[0]                    

                    # FIX: se è un token RHH EVO_*, NON passare da extract_int (evita collisione con ExpansionEvoMethod)
                    if hasattr(method_raw, "name") and method_raw.name in _RHH_EVO_METHOD_BY_NAME:
                        method_id = _RHH_EVO_METHOD_BY_NAME[method_raw.name]
                        is_rhh_method = True
                    else:
                        try:

                            method_id = extract_int(method_raw)

                        except Exception:

                            method_name = extract_id(method_raw)

                            if method_name in _RHH_EVO_METHOD_BY_NAME:

                                method_id = _RHH_EVO_METHOD_BY_NAME[method_name]

                                is_rhh_method = True

                            else:

                                continue

                    if method_id == 0xFFFF:
                        break

                    if method_id == 0xFFFE:
                        continue
                    
                    # If preprocessing expanded EVO_* to integers, avoid ExpansionEvoMethod collisions.

                    if method_id in _RHH_EVO_METHOD_IDS:
                        is_rhh_method = True

                    method = method_id
                    if not is_rhh_method:
                        try:
                            method = ExpansionEvoMethod(method_id)
                        except Exception:
                            pass

                    param_expr = evo_method.exprs[1]
                    try:
                        param = extract_int(param_expr)
                    except Exception:
                        param = extract_id(param_expr)

                    target = extract_int(evo_method.exprs[2])
                    conds = []

                    if len(evo_method.exprs) >= 4:
                        conds = _extract_conditions(evo_method.exprs[3])

                    evos.append([method, param, target, conds])

                evos.sort(key=lambda evo: evo[2])
            case 'levelUpLearnset':
                lvlup_learnset = level_up_learnsets.get(extract_id(field_expr), {})
            case 'teachableLearnset':
                teach_learnset = teachable_learnsets.get(extract_id(field_expr), {})

    # Sprite packs use "-hisui" rather than "-hisuian" in filenames (e.g. lilligant-hisui.png).
    if "name" in mon and "-Hisuian" in mon["name"]:
        mon.setdefault("spriteid", mon["name"].replace("-Hisuian", "-Hisui").lower())

    return mon, evos, lvlup_learnset, teach_learnset



def _pretty_identifier(name: str) -> str:
    # Convert constant-like identifiers into a readable label.
    # Examples: MAP_PETALBURG_WOODS -> Petalburg Woods
    s = str(name)
    s = re.sub(r'^(MAPSEC|MAP|ITEM|MOVE|SPECIES)_', '', s)
    s = s.replace('_', ' ').strip()
    return s.title() if s else str(name)


def _safe_extract_int_or_id(expr):
    try:
        return extract_int(expr)
    except Exception:
        try:
            return extract_id(expr)
        except Exception:
            return str(expr)


def _describe_alt_evo(method, param, conds, items, moves, map_sections) -> str:
    """Return a human-friendly description for an alternate evolution method.

    Used when multiple evolution entries lead to the same child, so we can render
    '... or use Leaf Stone' etc without needing UI changes.
    """
    # method can be an int (preprocessed) or an ID node ('EVO_ITEM', ...).
    if hasattr(method, 'name'):
        method_name = method.name
        method_id = _RHH_EVO_METHOD_BY_NAME.get(method_name)
    elif isinstance(method, int):
        method_id = int(method)
        method_name = None
        # Build an inverse map on demand
        if method_id in _RHH_EVO_METHOD_BY_NAME.values():
            method_name = {v: k for k, v in _RHH_EVO_METHOD_BY_NAME.items()}[method_id]
    else:
        method_name = str(method)
        method_id = _RHH_EVO_METHOD_BY_NAME.get(method_name)

    p = _safe_extract_int_or_id(param)

    # Base description from method
    base = ''
    if method_name == 'EVO_ITEM' or method_id == _RHH_EVO_METHOD_BY_NAME.get('EVO_ITEM'):
        try:
            base = f"use {items[int(p)]}"
        except Exception:
            base = f"use {_pretty_identifier(p)}"
    elif method_name == 'EVO_LEVEL' or method_id == _RHH_EVO_METHOD_BY_NAME.get('EVO_LEVEL'):
        try:
            lvl = int(p)
        except Exception:
            lvl = 0
        base = f"level {lvl}" if lvl else "level-up"
    elif method_name == 'EVO_MOVE' or method_id == _RHH_EVO_METHOD_BY_NAME.get('EVO_MOVE'):
        try:
            base = f"know {moves[int(p)]}"
        except Exception:
            base = f"know {_pretty_identifier(p)}"
    else:
        # Fallback (rare). Still try to say something.
        if method_name:
            base = _pretty_identifier(method_name)
        else:
            base = 'evolve'

    # Conditions
    notes: list[str] = []
    for key, cparam in (conds or []):
        c = cparam
        # cparam can be already an int, an ID, or an expression.
        c = _safe_extract_int_or_id(c)
        if key == 'IF_HOLD_ITEM':
            try:
                notes.append(f"while holding {items[int(c)]}")
            except Exception:
                notes.append(f"while holding {_pretty_identifier(c)}")
        elif key == 'IF_IN_MAP':
            notes.append(f"in {_pretty_identifier(c)}")
        elif key == 'IF_TIME':
            # TIME_* may be numeric after preprocessing; also accept names.
            t = str(c)
            tmap = {
                'TIME_MORNING': 'in the morning',
                'TIME_DAY': 'during the day',
                'TIME_NIGHT': 'at night',
                'TIME_EVENING': 'in the evening',
                'TIME_DUSK': 'at dusk',
                'TIME_DAWN': 'at dawn',
            }
            notes.append(tmap.get(t, _pretty_identifier(t)))
        else:
            # Keep unknown conditions readable.
            notes.append(_pretty_identifier(key).lower())

    if notes:
        return (base + ' ' + ' '.join(notes)).strip()
    return base.strip()
def zip_evos(all_data: dict,
             items: list[str],
             moves: list[str],
             map_sections: list[str]):
    for _, (mon, evos) in all_data.items():
        if not evos:
            continue

        mon['evos'] = []
        for i, evo in enumerate(evos):
            parent_dex_id = evo[2]
            parent_mon = all_data.get(parent_dex_id, (None,))[0]
            if not parent_mon:
                continue

            # Clean up Milcery's evos to Alcremie
            if mon['name'] == 'Milcery' and parent_mon['name'].startswith('Alcremie') and i > 0:
                continue

            # if the mon is already listed as evolving into this parent, continue
            method, param = evo[0], evo[1]

            conds = evo[3] if len(evo) > 3 else []

            # A parent can have multiple evolution entries that lead to the same child (e.g. Eevee -> Leafeon
            # via map condition OR via stone). We keep mon['evos'] unique for the evolution table, but we also
            # append alternate methods to the child's evoCondition so the UI can show all of them.
            if parent_mon['name'] in mon['evos']:
                alt_desc = _describe_alt_evo(method, param, conds, items, moves, map_sections)
                if alt_desc:
                    cur = parent_mon.get('evoCondition', '').strip()
                    parent_mon['evoCondition'] = (cur + (' or ' if cur else '') + alt_desc).strip()
                continue

            mon['evos'].append(parent_mon['name'])
            parent_mon['prevo'] = mon['name']

            method_val = method.value if hasattr(method, 'value') else method

            if isinstance(method_val, int) and method_val in _RHH_EVO_METHOD_IDS:

                method = method_val

            # RHH 1.12: evolution methods are a small enum (EVO_LEVEL/EVO_ITEM/...).
            # When we fail to cast to ExpansionEvoMethod we keep the raw int.
            if isinstance(method, int):
                # Method-specific params
                if method == _RHH_EVO_METHOD_BY_NAME['EVO_LEVEL']:
                    parent_mon['evoLevel'] = param
                    parent_mon['evoType'] = 'level'
                    parent_mon['evoCondition'] = ''
                elif method == _RHH_EVO_METHOD_BY_NAME['EVO_LEVEL_BATTLE_ONLY']:
                    parent_mon['evoLevel'] = param
                    parent_mon['evoType'] = 'level'
                    parent_mon['evoCondition'] = 'in battle'
                elif method == _RHH_EVO_METHOD_BY_NAME['EVO_TRADE']:
                    parent_mon['evoType'] = 'trade'
                    parent_mon['evoCondition'] = ''
                elif method == _RHH_EVO_METHOD_BY_NAME['EVO_ITEM']:
                    parent_mon['evoItem'] = items[param]
                    parent_mon['evoType'] = 'useItem'
                    parent_mon['evoCondition'] = ''
                elif method == _RHH_EVO_METHOD_BY_NAME['EVO_BATTLE_END']:
                    parent_mon['evoType'] = 'other'
                    parent_mon['evoCondition'] = 'after battle'
                elif method == _RHH_EVO_METHOD_BY_NAME['EVO_SPIN']:
                    parent_mon['evoType'] = 'spin'
                    parent_mon['evoCondition'] = str(param) if param is not None else ''
                else:
                    parent_mon['evoType'] = 'other'
                    parent_mon['evoCondition'] = ''
                # Apply RHH CONDITIONS(...)
                for c_name, c_param in conds:
                    if c_name == 'IF_HOLD_ITEM':
                        # RHH: this is a *condition* on a level/trade evolution, not an item-use evolution.
                        try:
                            held_item = items[int(c_param)]
                        except Exception:
                            held_item = str(c_param)

                        parent_mon['evoItem'] = held_item

                        note = f"while holding {held_item}"
                        parent_mon['evoCondition'] = (
                            (parent_mon.get('evoCondition') + ', ' if parent_mon.get('evoCondition') else '') + note
                        ).strip()
                    elif c_name == 'IF_TIME':
                        # RHH: time-of-day gate for level evolutions (e.g. Lycanroc forms).
                        t = c_param
                        note = None                 

                        if isinstance(t, int):
                            _tmap = {
                                0: 'during the day',
                                1: 'at night',
                                2: 'at dusk',
                                3: 'at dawn',
                                4: 'in the morning',
                                5: 'in the evening',
                            }
                            note = _tmap.get(t, f'time {t}')
                        else:
                            s = str(t)
                            if s.startswith('TIME_'):
                                s = s[5:]
                            key = s.strip().lower()                 

                            _smap = {
                                'day': 'during the day',
                                'night': 'at night',
                                'dusk': 'at dusk',
                                'dawn': 'at dawn',
                                'morning': 'in the morning',
                                'evening': 'in the evening',
                                'noon': 'at noon',
                            }
                            note = _smap.get(key, f'at {key.replace("_", " ")}')                    

                        parent_mon['evoCondition'] = (
                            (parent_mon.get('evoCondition') + ', ' if parent_mon.get('evoCondition') else '') + note
                        ).strip()

                    elif c_name == 'IF_MIN_FRIENDSHIP':
                        if parent_mon.get('evoType', '').startswith('level'):
                            parent_mon['evoType'] = 'friendship'
                    else:
                        note = c_name.replace('IF_', '').lower().replace('_', ' ')
                        if note:
                            parent_mon['evoCondition'] = (parent_mon.get('evoCondition','') + (', ' if parent_mon.get('evoCondition') else '') + note).strip()
                continue

            match method:
                # These evo methods have no additional parameter in showdown
                case ExpansionEvoMethod.FRIENDSHIP \
                    | ExpansionEvoMethod.FRIENDSHIP_DAY \
                    | ExpansionEvoMethod.FRIENDSHIP_NIGHT \
                    | ExpansionEvoMethod.TRADE \
                    | ExpansionEvoMethod.BEAUTY \
                    | ExpansionEvoMethod.CRITICAL_HITS \
                    | ExpansionEvoMethod.SCRIPT_TRIGGER_DMG \
                    | ExpansionEvoMethod.DARK_SCROLL \
                    | ExpansionEvoMethod.WATER_SCROLL \
                    | ExpansionEvoMethod.RECOIL_DAMAGE_MALE \
                    | ExpansionEvoMethod.RECOIL_DAMAGE_FEMALE \
                    | ExpansionEvoMethod.DEFEAT_WITH_ITEM \
                    | ExpansionEvoMethod.OVERWORLD_STEPS:
                    pass

                # These evo methods interpret the parameter as a minimum level
                case ExpansionEvoMethod.LEVEL \
                    | ExpansionEvoMethod.LEVEL_ATK_GT_DEF \
                    | ExpansionEvoMethod.LEVEL_ATK_EQ_DEF \
                    | ExpansionEvoMethod.LEVEL_ATK_LT_DEF \
                    | ExpansionEvoMethod.LEVEL_SILCOON \
                    | ExpansionEvoMethod.LEVEL_CASCOON \
                    | ExpansionEvoMethod.LEVEL_SHEDINJA \
                    | ExpansionEvoMethod.LEVEL_NINJASK \
                    | ExpansionEvoMethod.LEVEL_FEMALE \
                    | ExpansionEvoMethod.LEVEL_MALE \
                    | ExpansionEvoMethod.LEVEL_NIGHT \
                    | ExpansionEvoMethod.LEVEL_DAY \
                    | ExpansionEvoMethod.LEVEL_DUSK \
                    | ExpansionEvoMethod.LEVEL_RAIN \
                    | ExpansionEvoMethod.LEVEL_DARK_TYPE_MON_IN_PARTY \
                    | ExpansionEvoMethod.LEVEL_NATURE_AMPED \
                    | ExpansionEvoMethod.LEVEL_NATURE_LOW_KEY \
                    | ExpansionEvoMethod.LEVEL_TWO_SEGMENT \
                    | ExpansionEvoMethod.LEVEL_THREE_SEGMENT \
                    | ExpansionEvoMethod.LEVEL_CRITICAL_HITS \
                    | ExpansionEvoMethod.LEVEL_USE_MOVE_TWENTY_TIMES \
                    | ExpansionEvoMethod.LEVEL_DEF_EQ_ATK \
                    | ExpansionEvoMethod.LEVEL_ATK_EQ_DEF \
                    | ExpansionEvoMethod.LEVEL_ATK_GT_DEF \
                    | ExpansionEvoMethod.LEVEL_ATK_LT_DEF \
                    | ExpansionEvoMethod.LEVEL_FOG \
                    | ExpansionEvoMethod.LEVEL_FAMILY_OF_THREE \
                    | ExpansionEvoMethod.LEVEL_FAMILY_OF_FOUR:
                    parent_mon['evoLevel'] = param
                # These evo methods interpret the parameter as a specific item
                case ExpansionEvoMethod.TRADE_ITEM \
                    | ExpansionEvoMethod.ITEM \
                    | ExpansionEvoMethod.ITEM_HOLD_DAY \
                    | ExpansionEvoMethod.ITEM_HOLD_NIGHT \
                    | ExpansionEvoMethod.ITEM_MALE \
                    | ExpansionEvoMethod.ITEM_FEMALE \
                    | ExpansionEvoMethod.ITEM_NIGHT \
                    | ExpansionEvoMethod.ITEM_DAY \
                    | ExpansionEvoMethod.ITEM_HOLD \
                    | ExpansionEvoMethod.ITEM_COUNT_999:
                    parent_mon['evoItem'] = items[param]

                # These evo methods interpret the parameter as a specific move
                case ExpansionEvoMethod.MOVE \
                    | ExpansionEvoMethod.MOVE_TWO_SEGMENT \
                    | ExpansionEvoMethod.MOVE_THREE_SEGMENT \
                    | ExpansionEvoMethod.USE_MOVE_TWENTY_TIMES:
                    parent_mon['evoMove'] = moves[param]
                    pass

                # These evo methods interpret the parameter as another species
                case ExpansionEvoMethod.SPECIFIC_MON_IN_PARTY \
                    | ExpansionEvoMethod.TRADE_SPECIFIC_MON:
                    parent_mon['evoSpecies'] = all_data[param][0]['name']

                # This evo method interprets the parameter as a damage type
                case ExpansionEvoMethod.FRIENDSHIP_MOVE_TYPE:
                    parent_mon['evoMove'] = f'a {DAMAGE_TYPE[param]}-type move'

                # These evo methods interpret the parameter as a specific map zone
                case ExpansionEvoMethod.MAPSEC:
                    parent_mon['evoMap'] = map_sections[param]

                case _:
                    raise ValueError('Unimplemented evo method: ', evo[0])

            descriptor = EVO_METHOD[method.value]
            parent_mon['evoType'] = descriptor.type
            parent_mon['evoCondition'] = descriptor.condition

def zip_learnsets(lvlup_learnset: dict[str, list[int]],
                  teach_learnset: dict[str, list[str]]) -> dict:
    full_learnset = defaultdict(list)
    for move, levels in lvlup_learnset.items():
        full_learnset[move] = [f'L{level}' for level in levels]
    for method, moves in teach_learnset.items():
        for move in moves:
            full_learnset[move].append(method.upper())

    return full_learnset

def parse_species_data(species_data: ExprList,
                       abilities: list[str],
                       items: list[str],
                       moves: list[str],
                       forms: dict[str, dict[int, str]],
                       map_sections: list[str],
                       level_up_learnsets: dict[str, dict[str, list[int]]],
                       teachable_learnsets: dict[str, dict[str, list[str]]],
                       national_dex: dict[str, int],
                       included_mons: list[str],
                       species_info_path: pathlib.Path | None = None) -> tuple[dict, dict]:
    # first pass: raw AST parse (defer forms), build evolutions table
    all_species_data: dict[int, tuple[dict, list]] = {}
    learnsets_by_num: dict[int, tuple[dict, dict]] = {}

    for species_init in species_data:
        try:
            mon, evos, lvlup_learnset, teach_learnset = parse_mon(
                species_init,
                abilities,
                items,
                forms,
                level_up_learnsets,
                teachable_learnsets,
                national_dex,
            )
            all_species_data[mon['num']] = (mon, evos)
            learnsets_by_num[mon['num']] = (lvlup_learnset, teach_learnset)
        except Exception as err:
            print('error parsing species info')
            print(species_init.show())
            raise err

    # Resolve forms for RHH 1.12 if needed
    species_id_to_symbol: dict[int, str] = {}
    if species_info_path is not None:
        header = _guess_repo_species_header(species_info_path)
        if header is not None:
            species_id_to_symbol = _load_species_id_to_symbol(header)

    groups: dict[str, list[dict]] = defaultdict(list)
    for mon, _ in all_species_data.values():
        table_id = mon.get('_formTableId')
        if table_id:
            groups[table_id].append(mon)

    for table_id, mons in groups.items():
        mons_sorted = sorted(mons, key=lambda m: m['num'])
        base_mon = mons_sorted[0]

        # Prefer explicit parsed tables, otherwise infer from species symbols.
        table = forms.get(table_id)
        labels: list[str] = []
        if table:
            for m in mons_sorted:
                label = table.get(m['num'])
                # Ogerpon tera forms exist but are not always present in the table in older layouts
                if label is None and m.get('name') == 'Ogerpon' and (m['num'] - 4) in table:
                    label = f"{table[m['num'] - 4]}-Tera"
                if label is None:
                    label = 'Base' if m is base_mon else _pretty_forme_from_symbol_suffix(
                        base_mon.get('name', ''),
                        (species_id_to_symbol.get(m['num'], '') or '').replace((species_id_to_symbol.get(base_mon['num'], '') or '') + '_', '', 1)
                    )
                label = _normalize_form_label(label)
                labels.append(label)
        else:
            base_sym = species_id_to_symbol.get(base_mon['num'], '')
            for m in mons_sorted:
                sym = species_id_to_symbol.get(m['num'], '')
                suffix = ''
                if base_sym and sym.startswith(base_sym + '_'):
                    suffix = sym[len(base_sym) + 1:]
                elif sym and sym != base_sym:
                    suffix = sym
                labels.append(_pretty_forme_from_symbol_suffix(base_mon.get('name', ''), suffix))

        _apply_form_table_to_group(base_mon.get('name', ''), mons_sorted, labels)

    # Now that form names are stable, build learnsets and do cosmetic/special cleanup
    all_learnsets: dict[str, dict] = {}
    for num in list(all_species_data.keys()):
        mon, _ = all_species_data[num]
        if 'name' not in mon or not mon['name']:
            continue

        if mon['name'].rfind('-') != -1:
            base_name = mon['name'].split('-')[0]
            cosmetics = None if base_name in NON_COSMETIC_FORM_BASES else COSMETIC_FORME_SPECIES.get(base_name, None)
            if cosmetics and any(map(lambda s: s[0].get('name') == base_name, all_species_data.values())):
                if cosmetics.alts is None or mon['name'] not in map(lambda alt: f'{base_name}-{alt}', cosmetics.alts):
                    mon['cosmetic'] = True
                    # still keep the species entry, but skip learnsets
                    continue

            special = SPECIAL_ABILITIES.get(base_name, None)
            if special:
                form_name = mon['name'].replace(base_name, '')[1:]
                if '-' in form_name:
                    sub_form = f'-{form_name.split("-")[0]}'
                    special_form = '-'.join(form_name.split('-')[1:])
                else:
                    sub_form = ''
                    special_form = form_name

                if special.form == special_form:
                    target = f'{base_name}{sub_form}'
                    parent_mon = None
                    candidates = [target]

                    m_num = re.match(r"^(.*)-(\d+)$", target)
                    if m_num:
                        candidates.insert(1, f"{m_num.group(1)}-{m_num.group(2)}%")

                    # Fallback: sometimes special-form entries should merge into the base species
                    if base_name not in candidates:
                        candidates.append(base_name)

                    for cand in candidates:
                        for s in all_species_data.values():
                            nm = s[0].get('name')
                            if not nm:
                                continue
                            if nm == cand or (
                                ('baseForme' in s[0])
                                and f"{nm}-{s[0]['baseForme']}" == cand
                            ):
                                parent_mon = s[0]
                                target = cand
                                break
                        if parent_mon is not None:
                            break

                    if parent_mon is None:
                        print(f"WARNING: could not find parent species '{target}' for special ability merge from '{mon.get('name','')}'. Keeping it as separate entry.")
                        continue

                    parent_mon['abilities']['S'] = special.ability
                    del all_species_data[mon['num']]
                    learnsets_by_num.pop(mon['num'], None)
                    continue

        key = name_key(mon['name'])
        all_learnsets[key] = {'learnset': {}}
        lvlup_learnset, teach_learnset = learnsets_by_num.get(mon['num'], ({}, {}))
        if lvlup_learnset or teach_learnset:
            all_learnsets[key]['learnset'] = zip_learnsets(lvlup_learnset, teach_learnset)

    # second pass: re-target evos from source mon to target mon
    zip_evos(all_species_data, items, moves, map_sections)

    # re-zip the whole dictionary keyed according to showdown's key format
    # and flag mons which are not available
    final_species = {}
    for mon, _ in all_species_data.values():
        if 'name' not in mon or not mon['name']: # egg has no name; don't try
            continue

        if included_mons:
            mon['tier'] = 'obtainable' if mon['name'] in included_mons else 'unobtainable'

        final_species[name_key(mon['name'])] = mon

    return final_species, all_learnsets

def parse_species(fname: pathlib.Path,
                  abilities: list[str],
                  items: list[str],
                  moves: list[str],
                  forms: dict[str, dict[int, str]],
                  map_sections: list[str],
                  level_up_learnsets: dict[str, dict[str, list[int]]],
                  teachable_learnsets: dict[str, dict[str, list[str]]],
                  national_dex: dict[str, int],
                  included_mons: list[str]) -> tuple[dict, dict]:
    # If a preprocessed/minimal header is available next to species_info.h, prefer it.
    try:
        fpath = pathlib.Path(fname)
        if fpath.name == 'species_info.h':
            alt = fpath.with_name('porydex_species.h')
            if alt.exists():
                fname = alt
    except Exception:
        pass
    species_data: ExprList
    with yaspin(text=f'Loading species data: {fname}', color='cyan') as spinner:

        species_data = load_truncated(fname, extra_includes=[
            r'-include', r'constants/moves.h',
            # RHH 1.12 uses EVO_* enum tokens from constants/pokemon.h in EVOLUTION() macros.
            r'-include', r'constants/pokemon.h',
            # Helpful for resolving SPECIES_* names in initializers.
            r'-include', r'constants/species.h',
        ])
        spinner.ok("✅")

    return parse_species_data(
        species_data,
        abilities,
        items,
        moves,
        forms,
        map_sections,
        level_up_learnsets,
        teachable_learnsets,
        national_dex,
        included_mons,
        species_info_path=fname,
    )
