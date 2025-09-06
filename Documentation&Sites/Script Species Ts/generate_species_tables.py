
import re, glob, os, pathlib
from collections import OrderedDict

BASE_DIR = os.path.dirname(__file__) or "."

def read(path):
    return pathlib.Path(path).read_text(encoding="utf-8", errors="ignore")

# ---------- Macro parsing ----------
def collect_macros(text):
    macros = {}
    lines = text.splitlines()
    i = 0
    while i < len(lines):
        line = lines[i]
        # multiline define
        m = re.match(r'\s*#define\s+([A-Z0-9_]+)\s*(\(([^)]*)\))?\s*\\\s*$', line)
        if m:
            name = m.group(1)
            params = [p.strip() for p in (m.group(3) or '').split(',')] if m.group(2) else None
            body_lines = []
            i += 1
            while i < len(lines):
                L = lines[i]
                body_lines.append(L.rstrip('\\').rstrip())
                if not L.rstrip().endswith('\\'):
                    break
                i += 1
            body = "\n".join(body_lines)
            macros.setdefault(name, []).append({"body":body, "params":params})
            i += 1
            continue
        # single-line define
        m = re.match(r'\s*#define\s+([A-Z0-9_]+)\s*(\(([^)]*)\))?\s*(.+)$', line)
        if m:
            name = m.group(1)
            params = [p.strip() for p in (m.group(3) or '').split(',')] if m.group(2) else None
            body = m.group(4).strip()
            macros.setdefault(name, []).append({"body":body, "params":params})
            i += 1
            continue
        i += 1
    return macros

def choose_latest(variants): return variants[-1] if variants else None

def split_args(args_str):
    args, cur, depth = [], "", 0
    for ch in args_str:
        if ch == '(':
            depth += 1; cur += ch
        elif ch == ')':
            depth -= 1; cur += ch
        elif ch == ',' and depth == 0:
            args.append(cur.strip()); cur = ""
        else:
            cur += ch
    if cur.strip(): args.append(cur.strip())
    return args

def substitute_params(body, params, args):
    if not params: return body
    for name, val in list(zip(params, args)):
        body = re.sub(rf'\b{re.escape(name)}\b', val, body)
    return body

# ---------- Type helpers ----------
def tok_to_type(t):
    m = re.match(r'\s*TYPE_([A-Z_]+)\s*$', t)
    if not m: return None
    return m.group(1).capitalize().replace('_',' ').replace(' ','')

def resolve_type_token(tok, macros):
    tok = tok.strip().strip('{} ')
    # direct TYPE_*
    t = tok_to_type(tok)
    if t: return t
    # macro that yields a TYPE_*
    if re.match(r'^[A-Z][A-Z0-9_]*$', tok) and tok in macros:
        body = choose_latest(macros[tok])["body"]
        # ternary
        mt = re.search(r'\?\s*([A-Z0-9_]+)\s*:\s*([A-Z0-9_]+)', body)
        if mt:
            return resolve_type_token(mt.group(1), macros)
        # direct TYPE_*
        mt2 = re.search(r'TYPE_([A-Z_]+)', body)
        if mt2:
            return mt2.group(1).capitalize().replace('_',' ').replace(' ','')
    return None

def parse_types_expr(expr, macros):
    tokens = split_args(expr) if '(' in expr or ')' in expr else [t.strip() for t in expr.split(',') if t.strip()]
    out = []
    for tok in tokens:
        t = resolve_type_token(tok, macros)
        if t: out.append(t)
    # collapse dupes & limit to 2
    res = []
    for t in out:
        if not res or t != res[-1]:
            res.append(t)
    if len(res) == 2 and res[0] == res[1]: res = [res[0]]
    return res[:2]

def extract_types(body, macros):
    m = re.search(r'\.types\s*=\s*MON_TYPES\((.*?)\)', body, re.DOTALL)
    if m: return parse_types_expr(m.group(1), macros)
    m = re.search(r'\.types\s*=\s*(\{[^}]*\})', body, re.DOTALL)
    if m:
        inner = m.group(1).strip('{} \n')
        return parse_types_expr(inner, macros)
    m = re.search(r'\.types\s*=\s*([A-Z0-9_]+)\s*,', body)
    if m:
        macro = m.group(1)
        if macro in macros:
            b = choose_latest(macros[macro])["body"]
            mm = re.search(r'MON_TYPES\((.*?)\)', b, re.DOTALL)
            if mm: return parse_types_expr(mm.group(1), macros)
            inner = re.search(r'\{([^}]*)\}', b, re.DOTALL)
            if inner: return parse_types_expr(inner.group(1), macros)
            t1 = resolve_type_token(b, macros)
            if t1: return [t1]
    return []

def extract_weightkg(body):
    m = re.search(r'\.weight\s*=\s*(\d+)\s*,', body)
    return (int(m.group(1))/10.0) if m else 0.0

def extract_stats(body):
    out = {}
    for cfield, short in [('baseHP','hp'),('baseAttack','at'),('baseDefense','df'),('baseSpeed','sp'),('baseSpAttack','sa'),('baseSpDefense','sd')]:
        m = re.search(r'\.%s\s*=\s*(\d+)' % re.escape(cfield), body)
        if m: out[short] = int(m.group(1))
    for k in ['hp','at','df','sa','sd','sp']: out.setdefault(k, 0)
    return out

# ---------- Name normalization ----------
SUFFIX_MAP = {
    'MEGA':'Mega','GMAX':'Gmax','ALOLA':'Alola','ALOLAN':'Alola','HISUI':'Hisui','HISUIAN':'Hisui',
    'GALAR':'Galar','GALARIAN':'Galar','PALDEA':'Paldea','PALDEAN':'Paldea','TOTEM':'Totem','THERIAN':'Therian',
    'INCARNATE':'Incarnate','ORIGIN':'Origin','SKY':'Sky','DUSK':'Dusk','MIDDAY':'Midday','MIDNIGHT':'Midnight',
    'DUSK_MANE':'Dusk-Mane','DAWN_WINGS':'Dawn-Wings','BLADE':'Blade','SHIELD':'Shield','ZEN':'Zen','COMPLETE':'Complete',
    '10':'10%','10_PERCENT':'10%','50':'50%','F':'F','M':'M','SUNSHINE':'Sunshine','SCHOOL':'School','CROWNED':'Crowned',
    'PRIMAL':'Primal','BLACK':'Black','WHITE':'White','BLUE':'Blue','ORANGE':'Orange','RED':'Red','YELLOW':'Yellow','FLOWER':'Flower',
    'VANILLA_CREAM':'Vanilla-Cream','RUBY_CREAM':'Ruby-Cream','MATCHA_CREAM':'Matcha-Cream','MINT_CREAM':'Mint-Cream',
    'LEMON_CREAM':'Lemon-Cream','SALTED_CREAM':'Salted-Cream','RUBY_SWIRL':'Ruby-Swirl','CARAMEL_SWIRL':'Caramel-Swirl','RAINBOW_SWIRL':'Rainbow-Swirl',
    'STRAWBERRY':'Strawberry','BERRY':'Berry','LOVE':'Love','STAR':'Star','CLOVER':'Clover','RIBBON':'Ribbon',
    'TEAL':'Teal','WELLSPRING':'Wellspring','HEARTHFLAME':'Hearthflame','CORNERSTONE':'Cornerstone','TERA':'Tera',
}
def normalize_name(token):
    parts = token.split('_')
    base = parts[0].capitalize().title()
    if len(parts) == 1: return base
    mapped = [SUFFIX_MAP.get(s, s.capitalize().title()) for s in parts[1:]]
    return base + '-' + '-'.join(mapped)

# ---------- Species parsing ----------
SPECIES_BLOCK_RE = re.compile(r'\[SPECIES_([A-Z0-9_]+)\]\s*=\s*\{(.*?)\n\s*\}', re.DOTALL)
SPECIES_MACRO_ASSIGN_RE = re.compile(r'\[SPECIES_([A-Z0-9_]+)\]\s*=\s*([A-Z0-9_]+)\s*\(([^)]*)\)\s*,')

def parse_species(text):
    macros = collect_macros(text)
    data = {}
    # Case 1: direct blocks

    for m in SPECIES_BLOCK_RE.finditer(text):
        token, body = m.group(1), m.group(2)
        name = normalize_name(token)
        # inline function-like macros referenced in this body (one or two passes)
        exp = body
        for _ in range(2):
            calls = list(re.finditer(r'\b([A-Z][A-Z0-9_]+)\s*\(([^)]*)\)', exp))
            changed = False
            for call in calls:
                mname = call.group(1)
                if mname in macros:
                    mv = choose_latest(macros[mname])
                    args = split_args(call.group(2))
                    sub = substitute_params(mv["body"], mv["params"], args)
                    exp += "\n" + sub
                    changed = True
            if not changed: break
        _t = extract_types(exp, macros)
        if name.startswith('Alcremie') and (not _t):
            _t = ['Fairy']
        data[name] = {'types': _t, 'bs': extract_stats(exp), 'weightkg': extract_weightkg(exp)}

    # Case 2: macro-based with params
    for m in SPECIES_MACRO_ASSIGN_RE.finditer(text):
        token, mname, argstr = m.group(1), m.group(2), m.group(3)
        name = normalize_name(token)
        if name in data: continue
        mv = choose_latest(macros.get(mname, []))
        if not mv: continue
        args = split_args(argstr)
        body = substitute_params(mv["body"], mv["params"], args)
        # Expand nested function-like macros (one or two passes) so that inner .types become visible
        for _ in range(2):
            calls = list(re.finditer(r'\b([A-Z][A-Z0-9_]+)\s*\(([^)]*)\)', body))
            changed = False
            for call in calls:
                mname2 = call.group(1)
                if mname2 in macros:
                    mv2 = choose_latest(macros[mname2])
                    args2 = split_args(call.group(2))
                    sub2 = substitute_params(mv2["body"], mv2["params"], args2)
                    body += "\n" + sub2
                    changed = True
            if not changed: break
        types = extract_types(body, macros)
        # Force override for parametric species (Gen9 view)
        if 'OGERPON_SPECIES_INFO' in mname and len(args) >= 3:
            sec = tok_to_type(args[2])
            types = ['Grass'] + ([sec] if sec and sec != 'Grass' else [])
        elif 'SILVALLY_SPECIES_INFO' in mname and len(args) >= 1:
            t1 = tok_to_type(args[0])
            types = [t1] if t1 else []
        elif 'ARCEUS_SPECIES_INFO' in mname and len(args) >= 1:
            t1 = tok_to_type(args[0])
            types = [t1] if t1 else []
        if name.startswith('Ogerpon') or name.startswith('Silvally') or name.startswith('Arceus'):
            print('DBG', name, 'mname', mname, 'args', args[:3], 'types', types)
        # Alcremie family: force Fairy typing if unresolved/empty
        if name.startswith('Alcremie') and (not types):
            types = ['Fairy']
        data[name] = {'types': types, 'bs': extract_stats(body), 'weightkg': extract_weightkg(body)}
    return data

def main():
    label_map = {'1':'RBY','2':'GSC','3':'ADV','4':'DPP','5':'BW','6':'XY','7':'SM','8':'SS','9':'SV'}
    gens = OrderedDict()
    for gf in sorted(glob.glob(os.path.join(BASE_DIR, "gen_*_families.h"))):
        m = re.search(r'gen_(\d+)_families\.h$', gf)
        if not m: continue
        lbl = label_map.get(m.group(1))
        if not lbl: continue
        gens[lbl] = parse_species(read(gf))

    patches, prev = OrderedDict(), {}
    for lbl, data in gens.items():
        patch = {}
        for name, info in data.items():
            if name not in prev:
                patch[name] = info
            else:
                changed = {}
                if prev[name].get('types') != info.get('types'): changed['types'] = info.get('types')
                if prev[name].get('bs') != info.get('bs'): changed['bs'] = info.get('bs')
                if abs(prev[name].get('weightkg', 0) - info.get('weightkg', 0)) > 1e-6: changed['weightkg'] = info.get('weightkg')
                if changed: patch[name] = changed
        patches[lbl + "_PATCH"] = patch
        prev = {**prev, **data}

    def fmt_types(types): return '[' + ', '.join(f"'{t}'" for t in types) + ']'
    def fmt_bs(bs): return '{' + ', '.join(f"{k}: {bs.get(k,0)}" for k in ['hp','at','df','sa','sd','sp']) + '}'
    def fmt_entry(val):
        parts = []
        if 'types' in val: parts.append(f"types: {fmt_types(val['types'])}")
        if 'bs' in val: parts.append(f"bs: {fmt_bs(val['bs'])}")
        if 'weightkg' in val: parts.append(f"weightkg: {val['weightkg']:.1f}")
        return '{' + ', '.join(parts) + '}'


    # Force Alcremie: set Fairy if types are empty
    for _lbl, _patch in patches.items():
        for _name, _info in _patch.items():
            if _name.startswith('Alcremie') and (not _info.get('types')):
                _info['types'] = ['Fairy']

    ts = []
    ts.append("import {extend} from '../util';")
    ts.append("import type * as I from './interface';")
    ts.append("import type {SpeciesData} from './species';\n")
    for lbl, patch in patches.items():
        ts.append(f"const {lbl}: {{[name: string]: SpeciesData}} = {{")
        for name in sorted(patch.keys()):
            ts.append(f"  '{name}': {fmt_entry(patch[name])},")
        ts.append("};\n")
        if lbl == 'RBY_PATCH': ts.append("const RBY: {[name: string]: SpeciesData} = extend(true, {}, {} as any, RBY_PATCH);\n")
        if lbl == 'GSC_PATCH': ts.append("const GSC: {[name: string]: SpeciesData} = extend(true, {}, RBY, GSC_PATCH);\n")
        if lbl == 'ADV_PATCH': ts.append("const ADV: {[name: string]: SpeciesData} = extend(true, {}, GSC, ADV_PATCH);\n")
        if lbl == 'DPP_PATCH': ts.append("const DPP: {[name: string]: SpeciesData} = extend(true, {}, ADV, DPP_PATCH);\n")
        if lbl == 'BW_PATCH':  ts.append("const BW: {[name: string]: SpeciesData} = extend(true, {}, DPP, BW_PATCH);\n")
        if lbl == 'XY_PATCH':  ts.append("const XY: {[name: string]: SpeciesData} = extend(true, {}, BW, XY_PATCH);\n")
        if lbl == 'SM_PATCH':  ts.append("const SM: {[name: string]: SpeciesData} = extend(true, {}, XY, SM_PATCH);\n")
        if lbl == 'SS_PATCH':  ts.append("const SS: {[name: string]: SpeciesData} = extend(true, {}, SM, SS_PATCH);\n")
        if lbl == 'SV_PATCH':  ts.append("const SV: {[name: string]: SpeciesData} = extend(true, {}, SS, SV_PATCH);\n")
    ts.append("\nexport const SPECIES = [RBY, GSC, ADV, DPP, BW, XY, SM, SS, SV];")
    out = os.path.join(BASE_DIR, "species_tables.ts")
    pathlib.Path(out).write_text("\n".join(ts), encoding="utf-8")
    print("Wrote", out)

if __name__ == '__main__':
    main()
