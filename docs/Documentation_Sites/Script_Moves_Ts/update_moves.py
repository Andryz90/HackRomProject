#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Update calc's moves.ts from moves_info.h (current directory).

- Legge moves_info.h e moves.ts nella cartella corrente.
- Genera moves.ts.updated nella stessa cartella.
- Gestisce warning ed errori in modo tollerante.
- Ignora sempre un'entry con nome '-' (placeholder).
"""

import re, json, collections, pathlib, sys
from math import gcd

# ---------- costanti ----------
BAD_TS_KEYS = {"-"}  # chiavi che NON vanno toccate/aggiornate/aggiunte

# ---------- helpers & mappings ----------
TYPE_MAP = {
    "TYPE_NORMAL":"Normal","TYPE_FIGHTING":"Fighting","TYPE_FLYING":"Flying","TYPE_POISON":"Poison",
    "TYPE_GROUND":"Ground","TYPE_ROCK":"Rock","TYPE_BUG":"Bug","TYPE_GHOST":"Ghost","TYPE_STEEL":"Steel",
    "TYPE_FIRE":"Fire","TYPE_WATER":"Water","TYPE_GRASS":"Grass","TYPE_ELECTRIC":"Electric","TYPE_PSYCHIC":"Psychic",
    "TYPE_ICE":"Ice","TYPE_DRAGON":"Dragon","TYPE_DARK":"Dark","TYPE_FAIRY":"Fairy",
}
CAT_MAP = {
    "DAMAGE_CATEGORY_PHYSICAL":"Physical",
    "DAMAGE_CATEGORY_SPECIAL":"Special",
    "DAMAGE_CATEGORY_STATUS":"Status",
}
FLAG_MAP_BOOL = {
    "makesContact":"makesContact",
    "punchingMove":"isPunch",
    "bitingMove":"isBite",
    "ballisticMove":"isBullet",
    "soundMove":"isSound",
    "pulseMove":"isPulse",
    "slicingMove":"isSlicing",
    "windMove":"isWind",
}

# regex
MOVE_BLOCK_RE = re.compile(r"\[\s*(?P<tag>MOVE_[A-Z0-9_]+)\s*\]\s*=\s*\{(?P<body>.*?)\},\s*", re.DOTALL)
NAME_RE   = re.compile(r"\.name\s*=\s*COMPOUND_STRING\(\s*\"(?P<name>.*?)\"\s*\)\s*,", re.DOTALL)
POWER_RE  = re.compile(r"\.power\s*=\s*(?P<num>[-]?\d+)\s*,")
TYPE_RE   = re.compile(r"\.type\s*=\s*(?P<val>[A-Z_]+)\s*,")
CAT_RE    = re.compile(r"\.category\s*=\s*(?P<val>[A-Z_]+)\s*,")
PRIORITY_RE = re.compile(r"\.priority\s*=\s*(?P<num>[-]?\d+)\s*,")
STRIKE_RE   = re.compile(r"\.strikeCount\s*=\s*(?P<num>\d+)\s*,")
EFFECT_RE   = re.compile(r"\.effect\s*=\s*(?P<val>[A-Z_]+)\s*,")
ABSORB_RE   = re.compile(r"\.argument\s*=\s*\{\s*\.absorbPercentage\s*=\s*(?P<num>\d+)\s*\}\s*,", re.DOTALL)
SECONDARIES_RE = re.compile(r"\.additionalEffects\s*=\s*ADDITIONAL_EFFECTS", re.DOTALL)

def flag_present(body, c_field): 
    return re.search(rf"\.{c_field}\s*=\s*TRUE\s*,", body) is not None

def drain_from_absorb(pct):
    if pct == 50: return [1,2]
    if pct == 75: return [3,4]
    if pct == 100: return [1,1]
    g = gcd(pct, 100); return [pct//g, 100//g]

GEN_KEYS = ["RBY","GSC","ADV","DPP","BW","XY","SM","SS","SV"]
GEN_OBJ_RE = {g: re.compile(rf"(const\s+{g}.*?\{{)(?P<body>.*?)(\}}\s*;)", re.DOTALL) for g in GEN_KEYS}
ENTRY_RE = re.compile(r"('(?P<name>[^']+?)'\s*:\s*\{(?P<obj>.*?)\}\s*,?)", re.DOTALL)

def parse_ts_gen_object(body):
    return collections.OrderedDict((m.group("name"), m.group(0)) for m in ENTRY_RE.finditer(body))

def emit_ts_entry(name, data):
    order = ["bp","type","category","zp","maxPower","makesContact","isPunch","isBite","isBullet",
             "isSound","isPulse","isSlicing","isWind","priority","multihit","drain","hasCrashDamage","secondaries"]
    def val(v):
        if isinstance(v,bool): return "true" if v else "false"
        if isinstance(v,int): return str(v)
        if isinstance(v,list): return json.dumps(v)
        return f"'{v}'"
    parts = [f"{k}: {val(data[k])}" for k in order if k in data]
    return f"  '{name}': {{ {', '.join(parts)} }},"


# ---------- parse moves_info.h ----------
def parse_moves_info(h_text):
    moves, warns, kicking = {}, [], []
    for m in MOVE_BLOCK_RE.finditer(h_text):
        body = m.group("body")
        try:
            nm = NAME_RE.search(body)
            if not nm:
                warns.append(f"[skip] Blocco {m.group('tag')} senza .name")
                continue
            name = nm.group("name").strip()
            if not name or name in BAD_TS_KEYS:
                warns.append(f"[skip] Nome mossa non valido o placeholder ignorato: '{name}'")
                continue

            data = {}
            pw = POWER_RE.search(body); data["bp"] = int(pw.group("num")) if pw else 0
            ty = TYPE_RE.search(body)
            if ty and ty.group("val") in TYPE_MAP: data["type"]=TYPE_MAP[ty.group("val")]
            else:
                warns.append(f"[skip] .type mancante/sconosciuto per '{name}'")
                continue
            cat = CAT_RE.search(body); 
            if cat and cat.group("val") in CAT_MAP: data["category"]=CAT_MAP[cat.group("val")]
            pr = PRIORITY_RE.search(body); 
            if pr: data["priority"]=int(pr.group("num"))
            st = STRIKE_RE.search(body); 
            if st: data["multihit"]=int(st.group("num"))
            ab = ABSORB_RE.search(body); 
            if ab: data["drain"]=drain_from_absorb(int(ab.group("num")))
            eff = EFFECT_RE.search(body)
            if eff and eff.group("val")=="EFFECT_RECOIL_IF_MISS": data["hasCrashDamage"]=True
            if SECONDARIES_RE.search(body): data["secondaries"]=True
            for c_field, ts_field in FLAG_MAP_BOOL.items():
                if flag_present(body, c_field): data[ts_field]=True
            if flag_present(body, "kickingMove"): kicking.append(name)
            moves[name]=data
        except Exception as e:
            warns.append(f"[error] Parsing {m.group('tag')}: {e}")
    return moves, warns, kicking

# ---------- read & update moves.ts ----------
def read_ts_generations(ts_text):
    gens = {}
    for g,rx in GEN_OBJ_RE.items():
        m=rx.search(ts_text)
        if m: 
            gens[g]={
                "start":m.start("body"),"end":m.end("body"),
                "prefix":m.group(1),"body":m.group("body"),
                "suffix":m.group(3),
                "entries":parse_ts_gen_object(m.group("body"))
            }
    return gens

def build_reverse_index(gens):
    out={}
    for g,info in gens.items():
        for n in info["entries"]:
            out[n]=g
    return out

def merge(gens, parsed_moves):
    added, updated, skipped_placeholder = [], [], False
    name_to_gen = build_reverse_index(gens)

    # aggiorna quelle esistenti (saltando placeholder)
    for name,g in name_to_gen.items():
        if name in BAD_TS_KEYS:
            skipped_placeholder = True
            continue
        if name in parsed_moves:
            gens[g]["entries"][name]=emit_ts_entry(name,parsed_moves[name])
            updated.append(name)

    # aggiungi nuove (mai con nome placeholder)
    for name,data in parsed_moves.items():
        if name in BAD_TS_KEYS:  # già filtrato prima, ma per sicurezza
            skipped_placeholder = True
            continue
        if name not in name_to_gen:
            gens["SV"]["entries"][name]=emit_ts_entry(name,data)
            added.append(name)

    # ricostruisci i corpi ordinati
    for g,info in gens.items():
        ordered=collections.OrderedDict(sorted(info["entries"].items(), key=lambda kv:kv[0].lower()))
        info["new_body"]="\n"+"\n".join(ordered.values())+"\n"
    return updated, added, skipped_placeholder

def apply_to_ts(ts_text, gens):
    rep=[]
    for g,info in gens.items():
        rep.append((info["start"],info["end"],info["new_body"]))
    rep.sort(key=lambda x:x[0], reverse=True)
    for s,e,new in rep:
        ts_text=ts_text[:s]+new+ts_text[e:]
    return ts_text

# ---------- main ----------
def main():
    h_path=pathlib.Path("moves_info.h")
    ts_path=pathlib.Path("moves.ts")
    if not h_path.exists() or not ts_path.exists():
        sys.exit("Devi avere moves_info.h e moves.ts nella cartella corrente.")
    h=h_path.read_text(encoding="utf-8",errors="ignore")
    ts=ts_path.read_text(encoding="utf-8",errors="ignore")
    parsed, warns, kicking=parse_moves_info(h)
    gens=read_ts_generations(ts)

    missing_gens = [g for g in GEN_KEYS if g not in gens]
    if missing_gens:
        sys.exit(f"[fatal] Mancano gli oggetti di generazione in moves.ts: {', '.join(missing_gens)}")

    updated, added, skipped_placeholder = merge(gens, parsed)
    out=apply_to_ts(ts, gens)
    out_path=ts_path.with_suffix(".ts.updated")
    out_path.write_text(out, encoding="utf-8")

    print(f"[ok] {len(updated)} mosse aggiornate, {len(added)} aggiunte (in SV). Output: {out_path}")
    if skipped_placeholder:
        print("[note] È presente una mossa placeholder con nome '-' in moves.ts: è stata lasciata intatta/ignorata.")
    if kicking:
        print("[note] kickingMove trovate:",", ".join(sorted(set(kicking))))
    if warns:
        print("[warn]", *warns, sep="\n  ")

if __name__=="__main__":
    main()
