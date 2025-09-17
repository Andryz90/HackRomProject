#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
createsitefromindx.py (clean, path-agnostic)
- Parse site/index.html like main.py does (row-wise)
- Build site/trainer_sheet.html using site/splits.txt
- Robust trainer sprite detection (Maxie, Cooltrainer, Parasol Lady, Sr & Jr, etc.)
"""

from __future__ import annotations
import os, re, sys, unicodedata, argparse
from pathlib import Path
from collections import defaultdict

try:
    from bs4 import BeautifulSoup  # pip install beautifulsoup4
except ImportError:
    print("[error] Missing dependency: beautifulsoup4. Install with: pip install beautifulsoup4", file=sys.stderr)
    sys.exit(1)

# ===== CLI & path detection =====
def detect_site_dir(cli_site: Path|None, cli_infile: Path|None) -> Path:
    script_dir = Path(__file__).resolve().parent
    if cli_site:
        return Path(cli_site).resolve()
    if cli_infile:
        return Path(cli_infile).resolve().parent

    cwd = Path.cwd()
    if (cwd / "site" / "index.html").exists():
        return (cwd / "site").resolve()
    if (cwd / "index.html").exists():
        return cwd.resolve()
    if (script_dir / "site" / "index.html").exists():
        return (script_dir / "site").resolve()

    for p in [*cwd.parents]:
        cand = p / "site"
        if (cand / "index.html").exists():
            return cand.resolve()

    print("[error] Cannot find site/index.html; pass --site or --in", file=sys.stderr)
    sys.exit(2)

def build_paths(args):
    site_dir = detect_site_dir(args.site, args.infile)
    in_file = Path(args.infile).resolve() if args.infile else (site_dir / "index.html")
    out_main = Path(args.outfile).resolve() if args.outfile else (site_dir / "trainer_sheet.html")
    splits_file = Path(args.splits).resolve() if args.splits else (site_dir / "splits.txt")
    sprites_dir = site_dir / "trainer_sprites"
    sprites_map = site_dir / "trainer_sprites.txt"
    return site_dir, in_file, out_main, splits_file, sprites_dir, sprites_map

# ===== Utilities =====
CALC_URL = "https://andryz90.github.io/HackRomProject/Documentation_Sites/Calculator/dist/index.html"
MERGE_SIDE_LIMIT = 3
MERGE_PICK = "first"

def _rel_to_output(local_path: Path, out_parent: Path) -> str:
    try:
        rel = os.path.relpath(local_path, start=out_parent)
    except Exception:
        rel = str(local_path)
    return Path(rel).as_posix()

def slugify(text: str) -> str:
    s = text.lower()
    s = re.sub(r"[^a-z0-9]+", "-", s).strip("-")
    return s or "trainer"

def canonicalize(s: str) -> str:
    if s is None: return ""
    x = unicodedata.normalize("NFKD", s)
    x = "".join(ch for ch in x if not unicodedata.combining(ch))
    x = x.lower()
    x = re.sub(r"[^\w\s]+", " ", x)
    x = re.sub(r"\s+", " ", x).strip()
    return x

def make_inorder_regex(s: str):
    words = re.findall(r"[a-z0-9]+", s.lower())
    if not words:
        return re.compile(r"$^")
    pat = r"\b" + r"\b.*\b".join(map(re.escape, words)) + r"\b"
    return re.compile(pat, re.I)

def _cell_text(c) -> str:
    return (c.get_text(" ", strip=True) or "").strip()

# ===== Row classifiers =====
ITEM_WORDS = {
    "oran berry","sitrus berry","lum berry","passho berry","shuca berry","rindo berry","yache berry",
    "chople berry","occa berry","kebia berry","kasib berry","tanga berry","colbur berry","babiri berry",
    "haban berry","wacan berry","figy berry","iapapa berry","wiki berry","aguav berry","mago berry",
    "leftovers","life orb","choice band","choice scarf","choice specs","eviolite","expert belt",
    "air balloon","assault vest","heavy-duty boots","scope lens","muscle band","wise glasses","focus sash",
    "white herb","light clay","black sludge","metal coat","quick claw","miracle seed","charcoal",
    "mystic water","never-melt ice","soft sand","sharp beak","pixie plate","dragon fang",
    "spell tag","rocky helmet","throat spray","amulet coin","lucky egg","safety goggles","shed shell",
    "heat rock"
}
NATURES = {
    "adamant","modest","timid","jolly","bold","impish","careful","calm","naive","hasty","lonely","naughty",
    "brave","quiet","rash","gentle","sassy","relaxed","hardy","docile","serious","bashful","quirky","lax"
}
IVS_ROW_RE = re.compile(r"^\s*\d{1,2}\s*/\s*\d{1,2}\s*/\s*\d{1,2}\s*/\s*\d{1,2}\s*/\s*\d{1,2}\s*/\s*\d{1,2}\s*$")

def is_items_row(tds) -> bool:
    for td in tds:
        txt = _cell_text(td).lower()
        if not txt: continue
        if " berry" in txt or txt in ITEM_WORDS:
            return True
    return False

def is_ivs_row(tds) -> bool:
    for td in tds:
        if IVS_ROW_RE.match(_cell_text(td)):
            return True
    return False

def is_nature_row(tds) -> bool:
    return any(_cell_text(td).lower() in NATURES for td in tds)

# ===== Sprite mapping =====
TRAINER_SPRITES_BASE = "https://play.pokemonshowdown.com/sprites/trainers"
TRAINER_SPRITES = [
    # Specific teams/characters first
    (re.compile(r"\bteam\s+aqua\s+grunt\b", re.I),   "aquagrunt"),
    (re.compile(r"\bteam\s+magma\s+grunt\b", re.I),  "magmagrunt"),
    (re.compile(r"^\s*(?:Team\s+)?Magma\s+(?:Leader|Boss)\s+Maxie\b", re.I), "maxie"),
    (re.compile(r"^\s*(?:Team\s+)?Magma\s+Admin\s+Tabitha\b", re.I), "tabitha"),

    # Parasol Lady
    (re.compile(r"^\s*Parasol\s*Lady\b", re.I), "parasollady"),

    # Cooltrainer / Ace Trainer (space or no-space; with/without M/F)
    (re.compile(r"^\s*Cool\s*Trainer\s*M\b", re.I),  "cooltrainerm"),
    (re.compile(r"^\s*Cool\s*Trainer\s*F\b", re.I),  "cooltrainerf"),
    (re.compile(r"^\s*Cooltrainer\s*M\b", re.I),     "cooltrainerm"),
    (re.compile(r"^\s*Cooltrainer\s*F\b", re.I),     "cooltrainerf"),
    (re.compile(r"^\s*Cool\s*Trainer\b", re.I),      "cooltrainerm"),
    (re.compile(r"^\s*Cooltrainer\b", re.I),         "cooltrainerm"),
    (re.compile(r"^\s*Ace\s*Trainer\s*M\b", re.I),   "cooltrainerm"),
    (re.compile(r"^\s*Ace\s*Trainer\s*F\b", re.I),   "cooltrainerf"),
    (re.compile(r"^\s*Ace\s*Trainer\b", re.I),       "cooltrainerm"),

    # Common classes
    (re.compile(r"^\s*Youngster\b", re.I),           "youngster"),
    (re.compile(r"^\s*Bug\s*Catcher\b", re.I),       "bugcatcher"),
    (re.compile(r"^\s*Lass\b", re.I),                "lass"),
    (re.compile(r"^\s*Lady\b", re.I),                "lady"),
    (re.compile(r"^\s*Rich\s*Boy\b", re.I),          "richboy"),
    (re.compile(r"^\s*Fisher(man)?\b", re.I),        "fisherman"),
    (re.compile(r"^\s*Sailor\b", re.I),              "sailor"),
    (re.compile(r"^\s*Hiker\b", re.I),               "hiker"),
    (re.compile(r"^\s*Twins?\b", re.I),              "twins"),
    (re.compile(r"^\s*Tuber\b.*\bF\b", re.I),        "tuberf"),
    (re.compile(r"^\s*Tuber\b", re.I),               "tuber"),
    (re.compile(r"^\s*Swimmer\s*M\b", re.I),         "swimmerm"),
    (re.compile(r"^\s*Swimmer\s*F\b", re.I),         "swimmerf"),
    (re.compile(r"^\s*Battle\s*Girl\b", re.I),       "battlegirl"),
    (re.compile(r"^\s*Black\s*Belt\b", re.I),        "blackbelt"),
    (re.compile(r"^\s*Beauty\b", re.I),              "beauty"),
    (re.compile(r"^\s*Gentleman\b", re.I),           "gentleman"),
    (re.compile(r"^\s*Psychic\b", re.I),             "psychic"),
    (re.compile(r"^\s*Collector\b", re.I),           "collector"),
    (re.compile(r"^\s*Camper\b", re.I),              "camper"),
    (re.compile(r"^\s*Picnicker\b", re.I),           "picnicker"),
    (re.compile(r"^\s*Ninja\s*Boy\b", re.I),         "ninjaboy"),
    (re.compile(r"^\s*Aroma\s*Lady\b", re.I),        "aromalady"),
    (re.compile(r"^\s*Hex\s*Maniac\b", re.I),        "hexmaniac"),
    (re.compile(r"^\s*Bird\s*Keeper\b", re.I),       "birdkeeper"),
    (re.compile(r"^\s*Bug\s*Maniac\b", re.I),        "bugmaniac"),
    (re.compile(r"^\s*Pok[eé]?maniac\b", re.I),      "pokemaniac"),
    (re.compile(r"^\s*Guitarist\b", re.I),           "guitarist"),
    (re.compile(r"^\s*Kindler\b", re.I),             "kindler"),
    (re.compile(r"^\s*Scientist\b", re.I),           "scientist"),
    (re.compile(r"^\s*Pok[eé]?fan\b", re.I),         "pokefan"),
    (re.compile(r"^\s*School\s*Kid\b", re.I),        "schoolkid"),
    (re.compile(r"^\s*Triathlete\b", re.I),          "triathlete"),
    # Sr. and Jr.
    (re.compile(r"^\s*Sr\s*(?:\.|and)?\s*&?\s*Jr", re.I), "srandjr"),
    # Breeder
    (re.compile(r"^\s*(Pkmn\s*Breeder|Pok[eé]?mon\s*Breeder)\b", re.I), "pkmnbreeder"),
    # Leaders (fallback by captured name)
    (re.compile(r"^\s*Leader\s+([A-Za-z]+)", re.I),  None),
    # Rivals / Partners
    (re.compile(r"^\s*Rival\s+WALLY\b", re.I),       "wally"),
    (re.compile(r"^\s*Rival\s+MAY\b", re.I),         "may"),
    (re.compile(r"^\s*Rival\s+BRENDAN\b", re.I),     "brendan"),
    (re.compile(r"^\s*Partner\b.*\bWALLY\b", re.I),  "wally"),
    (re.compile(r"^\s*Partner\b.*\bSTEVEN\b", re.I), "steven"),
    (re.compile(r"^\s*Partner\b", re.I),             "tagteam"),
]

def read_custom_sprites_map(sprites_map: Path):
    """Parse trainer_sprites.txt.

    Syntax per line (ignoring blank lines and comments starting with '#'):

        <regex> => <candidate>[ | <candidate> ...]

    Each <candidate> can be:
      - a local filename relative to the sprites folder (png/jpg/gif). Case-insensitive.
      - a full URL (http/https).
      - the special token 'showdown:<name>' which expands to
            f"{TRAINER_SPRITES_BASE}/{name}.png" and a couple of common variants
            (e.g., '-rse', '-oras' for some well-known characters).

    Examples:
        ^Developer\s+Andry$ => Andry_front_pic.png
        ^\s*Parasol\s*Lady\b => parasol_custom.png | showdown:parasollady
        ^\s*(?:Team\s+)?Magma\s+(?:Leader|Boss)\s+Maxie\b => showdown:maxie | maxie.png
    """
    rules = []
    if not sprites_map.exists():
        return rules

    for ln_no, raw in enumerate(sprites_map.read_text(encoding="utf-8").splitlines(), 1):
        line = raw.strip()
        if not line or line.startswith('#'):
            continue
        if '=>' not in line:
            print(f"[warn] trainer_sprites.txt:{ln_no}: missing '=>': {line}", file=sys.stderr)
            continue
        pat, rhs = line.split('=>', 1)
        try:
            rx = re.compile(pat.strip(), re.I)
        except re.error as e:
            print(f"[warn] trainer_sprites.txt:{ln_no}: invalid regex: {pat} ({e})", file=sys.stderr)
            continue
        # Split candidates by | and commas, keep order
        cand_tokens = [t.strip() for t in re.split(r"[|,]", rhs) if t.strip()]
        rules.append((rx, cand_tokens))
    return rules

def _find_custom_sprite_ci(sprites_dir: Path, *names: str) -> Path|None:
    for n in names:
        p = sprites_dir / n
        if p.exists(): return p
        if p.parent.exists():
            for f in p.parent.iterdir():
                if f.is_file() and f.name.lower() == n.lower():
                    return f
    return None


def _expand_candidate_token(token: str, sprites_dir: Path, out_parent: Path) -> list[str]:
    """Expand one token from trainer_sprites.txt into one or more URL candidates."""
    t = token.strip()
    out = []

    # Full URL
    if re.match(r'^https?://', t):
        out.append(t)
        return out

    # 'showdown:<name>'
    m = re.match(r'^(?:showdown|ps|trainer):\s*([\w\-]+)$', t, re.I)
    if m:
        name = m.group(1)
        # add a few common variants: base, -rse, -oras (for Hoenn bosses), gendered M/F variants
        base = f"{TRAINER_SPRITES_BASE}/{name}.png"
        out.append(base)
        # common alternates
        for suf in ("-rse", "-oras", "-gen3", "-m", "-f"):
            out.append(f"{TRAINER_SPRITES_BASE}/{name}{suf}.png")
        return out

    # Local file in sprites_dir (case-insensitive)
    # Fill extension if omitted
    if not os.path.splitext(t)[1]:
        t = t + ".png"
    p = _find_custom_sprite_ci(sprites_dir, t)
    if p:
        out.append(_rel_to_output(p, out_parent))

    # Also try showdown fallbacks using the (extensionless) basename
    base_name = os.path.splitext(os.path.basename(t))[0]
    out.append(f"{TRAINER_SPRITES_BASE}/{base_name}.png")
    for suf in ("-rse", "-oras", "-gen3", "-m", "-f"):
        out.append(f"{TRAINER_SPRITES_BASE}/{base_name}{suf}.png")
    return out

def detect_trainer_sprite(caption_text: str, custom_rules, sprites_dir: Path, out_parent: Path) -> list[str]:
    """Return a candidate list of sprite urls to try in order."""
    txt = caption_text or ""
    low = canonicalize(txt)

    # Custom "Developer ..."
    if re.search(r"^\s*Developer\s+Andry\b", txt, re.I):
        p = _find_custom_sprite_ci(sprites_dir, "andry.png","andry_front_pic.png","andry_front.png")
        if p: return [_rel_to_output(p, out_parent)]
    if re.search(r"^\s*Developer\s+Splitface\b", txt, re.I):
        p = _find_custom_sprite_ci(sprites_dir, "splitface.png","splitface_front.png","Splitface_front.png")
        if p: return [_rel_to_output(p, out_parent)]

    
    # User overrides from trainer_sprites.txt
    for rx, tokens in custom_rules:
        if rx.search(txt):
            candidates = []
            for tok in tokens:
                candidates.extend(_expand_candidate_token(tok, sprites_dir, out_parent))
            # Deduplicate preserving order
            dedup = []
            seen = set()
            for u in candidates:
                if u not in seen:
                    dedup.append(u); seen.add(u)
            if dedup:
                return dedup


    base = re.sub(r"\s*\[.*?\]\s*$", "", txt).strip()
    for key in (slugify(base), slugify(txt)):
        p = sprites_dir / f"{key}.png"
        if p.exists(): return [_rel_to_output(p, out_parent)]

    # Special direct-name catches
    if "maxie" in low:
        return [f"{TRAINER_SPRITES_BASE}/maxie.png",
                f"{TRAINER_SPRITES_BASE}/maxie-gen3.png",
                f"{TRAINER_SPRITES_BASE}/maxie-oras.png"]

    def both(main: str):
        return [f"{TRAINER_SPRITES_BASE}/{main}.png",
                f"{TRAINER_SPRITES_BASE}/{main}-rse.png"]

    for rx, key in TRAINER_SPRITES:
        m = rx.search(txt)
        if not m: continue

        if key is None:
            name = (m.group(1) or "").lower()
            return both(name)

        # Rich fallbacks per class
        if key == "triathlete":
            return [
                f"{TRAINER_SPRITES_BASE}/triathlete.png",
                f"{TRAINER_SPRITES_BASE}/triathlete-gen3.png",
                f"{TRAINER_SPRITES_BASE}/triathlete-m.png",
                f"{TRAINER_SPRITES_BASE}/triathlete-f.png",
                f"{TRAINER_SPRITES_BASE}/cyclist.png",
                f"{TRAINER_SPRITES_BASE}/biker.png",
            ]
        if key == "cooltrainerm":
            return [
                f"{TRAINER_SPRITES_BASE}/cooltrainerm.png",
                f"{TRAINER_SPRITES_BASE}/cooltrainerm-rse.png",
                f"{TRAINER_SPRITES_BASE}/cooltrainerf.png",
                f"{TRAINER_SPRITES_BASE}/cooltrainerf-rse.png",
                f"{TRAINER_SPRITES_BASE}/acetrainer.png",
                f"{TRAINER_SPRITES_BASE}/acetrainer-m.png",
                f"{TRAINER_SPRITES_BASE}/acetrainer-f.png",
            ]
        if key == "cooltrainerf":
            return [
                f"{TRAINER_SPRITES_BASE}/cooltrainerf.png",
                f"{TRAINER_SPRITES_BASE}/cooltrainerf-rse.png",
                f"{TRAINER_SPRITES_BASE}/cooltrainerm.png",
                f"{TRAINER_SPRITES_BASE}/cooltrainerm-rse.png",
                f"{TRAINER_SPRITES_BASE}/acetrainer.png",
                f"{TRAINER_SPRITES_BASE}/acetrainer-f.png",
                f"{TRAINER_SPRITES_BASE}/acetrainer-m.png",
            ]
        if key == "parasollady":
            return [
                f"{TRAINER_SPRITES_BASE}/parasollady.png",
                f"{TRAINER_SPRITES_BASE}/parasollady-rse.png",
            ]
        if key == "srandjr":
            return [
                f"{TRAINER_SPRITES_BASE}/srandjr.png",
                f"{TRAINER_SPRITES_BASE}/srandjr-rse.png",
                f"{TRAINER_SPRITES_BASE}/srandjr-gen3.png",
                f"{TRAINER_SPRITES_BASE}/twins.png",
                f"{TRAINER_SPRITES_BASE}/sisterandbro.png",
            ]
        if key == "pkmnbreeder":
            return [
                f"{TRAINER_SPRITES_BASE}/pkmnbreeder.png",
                f"{TRAINER_SPRITES_BASE}/pokemonbreeder.png",
                f"{TRAINER_SPRITES_BASE}/breeder.png",
            ]
        if key == "magmagrunt":
            return [
                f"{TRAINER_SPRITES_BASE}/magmagrunt-rse.png",
                f"{TRAINER_SPRITES_BASE}/magmagrunt.png",
                f"{TRAINER_SPRITES_BASE}/magma-grunt.png",
            ]
        if key == "aquagrunt":
            # try both genders
            return [
                f"{TRAINER_SPRITES_BASE}/aquagrunt-rse.png",
                f"{TRAINER_SPRITES_BASE}/aquagrunt.png",
                f"{TRAINER_SPRITES_BASE}/aquagruntf-rse.png",
                f"{TRAINER_SPRITES_BASE}/aquagruntf.png",
                f"{TRAINER_SPRITES_BASE}/aqua-grunt.png",
            ]
        if key == "kindler":
            return [
                f"{TRAINER_SPRITES_BASE}/kindler.png",
                f"{TRAINER_SPRITES_BASE}/kindler-rse.png",
                f"{TRAINER_SPRITES_BASE}/firebreather.png",
            ]
        if key == "fisherman":
            return [f"{TRAINER_SPRITES_BASE}/fisherman.png", f"{TRAINER_SPRITES_BASE}/fisher.png"]
        if key == "bugmaniac":
            return [f"{TRAINER_SPRITES_BASE}/bugmaniac-gen3.png", f"{TRAINER_SPRITES_BASE}/bugmaniac-gen6.png"]
        # generics
        return both(key)

    # Partner fallback
    if "partner" in low:
        if "wally" in low:  return [f"{TRAINER_SPRITES_BASE}/wally.png"]
        if "steven" in low: return [f"{TRAINER_SPRITES_BASE}/steven.png"]
        return [f"{TRAINER_SPRITES_BASE}/tagteam.png"]

    return []

def set_img_with_fallbacks(img_tag, urls: list[str]):
    """Attach src and a JS onerror that cycles through candidates."""
    if not urls:
        img_tag["class"] = (img_tag.get("class", []) + ["trainer-pic","hidden"])
        return
    img_tag["src"] = urls[0]
    img_tag["class"] = (img_tag.get("class", []) + ["trainer-pic"])
    if len(urls) == 1:
        return
    arr_js = "[" + ",".join(f"'{u}'" for u in urls) + "]"
    img_tag["onerror"] = (
        "this.dataset.try=(this.dataset.try||0)-0+1;"
        f"var a={arr_js};"
        "if(this.dataset.try<a.length){this.src=a[this.dataset.try];}"
        "else{this.onerror=null;this.classList.add('hidden');}"
    )

# ===== Parse source table (row-wise) =====
def parse_table_columns(tbl):
    cols = []
    rows = tbl.select("tbody > tr")
    if not rows or len(rows) < 3:
        return cols

    imgs    = rows[0].find_all("td")
    species = rows[1].find_all("th")
    levels  = rows[2].find_all("td")
    max_cols = max(len(imgs), len(species), len(levels), 0)

    def pick_img(td):
        im = None
        for cand in td.find_all("img"):
            src = (cand.get("src") or "")
            if src and not src.endswith("/.png"):
                im = cand; break
        return str(im) if im else ""

    for i in range(max_cols):
        cols.append({
            "img_html": pick_img(imgs[i]) if i < len(imgs) else "",
            "species":  _cell_text(species[i]) if i < len(species) else "",
            "level":    _cell_text(levels[i]) if i < len(levels) else "",
            "item": "", "ability":"", "ivs":"", "nature":"", "moves":[]
        })

    idx = 3
    if idx < len(rows):
        cells = rows[idx].find_all(["td","th"])
        if is_items_row(cells):
            for i in range(max_cols):
                cols[i]["item"] = _cell_text(cells[i]) if i < len(cells) else ""
            idx += 1

    if idx < len(rows):
        cells = rows[idx].find_all(["td","th"])
        for i in range(max_cols):
            cols[i]["ability"] = _cell_text(cells[i]) if i < len(cells) else ""
        idx += 1

    if idx < len(rows) and is_ivs_row(rows[idx].find_all(["td","th"])):
        cells = rows[idx].find_all(["td","th"])
        for i in range(max_cols):
            cols[i]["ivs"] = _cell_text(cells[i]) if i < len(cells) else ""
        idx += 1

    if idx < len(rows) and is_nature_row(rows[idx].find_all(["td","th"])):
        cells = rows[idx].find_all(["td","th"])
        for i in range(max_cols):
            cols[i]["nature"] = _cell_text(cells[i]) if i < len(cells) else ""
        idx += 1

    while idx < len(rows):
        cells = rows[idx].find_all(["td","th"])
        for i in range(max_cols):
            mv = _cell_text(cells[i]) if i < len(cells) else ""
            if mv: cols[i]["moves"].append(mv)
        idx += 1

    for c in cols:
        if len(c["moves"]) > 4:
            c["moves"] = c["moves"][:4]
    return cols

# ===== Build HTML =====
def build_table_from_columns(title, columns, trainer_pic_lists, themed="single", cut_after=None):
    soup = BeautifulSoup('<table class="content-table"><caption class="caption-content"></caption><tbody></tbody></table>', "html.parser")
    tbl = soup.table
    cap = tbl.caption
    tbody = tbl.tbody

    # Sprites (each element may be a list of candidates)
    for candidates in trainer_pic_lists:
        if isinstance(candidates, str):
            candidates = [candidates]
        img = soup.new_tag("img")
        set_img_with_fallbacks(img, candidates or [])
        cap.append(img)

    cap.append(title + (" [Double Battle]" if themed == "double" else ""))
    sep = soup.new_tag("span"); sep.string = " · "; cap.append(sep)
    a = soup.new_tag("a", href=CALC_URL, target="_blank", rel="noopener"); a.string = "Open Calculator"; cap.append(a)

    def make_row(values, tag="td"):
        r = soup.new_tag("tr")
        for idx, val in enumerate(values):
            cell = soup.new_tag(tag)
            if val:
                frag = BeautifulSoup(val, "html.parser")
                cell.extend(frag.contents)
            if cut_after is not None and idx == cut_after:
                cell["class"] = (cell.get("class", []) + ["cut-right"])
            r.append(cell)
        tbody.append(r)

    make_row([c["img_html"] for c in columns], "td")
    make_row([c["species"]  for c in columns], "th")
    make_row([c["level"]    for c in columns], "td")
    if any(c["item"]    for c in columns): make_row([c["item"] for c in columns], "td")
    make_row([c["ability"] for c in columns], "td")
    if any(c["ivs"]     for c in columns): make_row([c["ivs"] for c in columns], "td")
    if any(c["nature"]  for c in columns): make_row([c["nature"] for c in columns], "td")

    max_moves = max((len(c["moves"]) for c in columns), default=0)
    for r in range(max_moves):
        make_row([ (c["moves"][r] if r < len(c["moves"]) else "") for c in columns ], "td")

    return tbl

def merge_two_tables(title1, t1, title2, t2, custom_rules, sprites_dir: Path, out_parent: Path):
    cols1_all = parse_table_columns(t1)
    cols2_all = parse_table_columns(t2)

    def pick(cols):
        if MERGE_SIDE_LIMIT is None or len(cols) <= MERGE_SIDE_LIMIT:
            return cols
        return cols[:MERGE_SIDE_LIMIT] if MERGE_PICK == "first" else cols[-MERGE_SIDE_LIMIT:]

    cols1 = pick(cols1_all)
    cols2 = pick(cols2_all)
    columns = cols1 + cols2

    pics1 = detect_trainer_sprite(title1, custom_rules, sprites_dir, out_parent)
    pics2 = detect_trainer_sprite(title2, custom_rules, sprites_dir, out_parent)
    merged_title = f"{title1} & {title2}"
    cut_after = (len(cols1) - 1) if cols1 else None
    merged_tbl = build_table_from_columns(merged_title, columns, [pics1, pics2], themed="double", cut_after=cut_after)
    return merged_tbl

# ===== splits.txt =====
def parse_splits(splits_file: Path):
    def _parse_sub_occ(piece: str):
        m = re.match(r"^(.*?)(?:\s*#(\d+))?$", piece.strip())
        raw = (m.group(1) or "").strip() if m else ""
        occ = int(m.group(2)) if (m and m.group(2)) else None
        return canonicalize(raw), occ

    mapping = []
    if not splits_file.exists():
        print(f"[error] Missing {splits_file}", file=sys.stderr); sys.exit(2)
    for raw in splits_file.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith("#"): continue
        if "@" not in line:
            mapping.append((line.strip(), [])); continue
        name, rhs = line.split("@", 1)
        name = name.strip()
        tokens = []
        for tok in rhs.split("|"):
            tok = tok.strip()
            if not tok: continue
            if "&&" in tok:
                left, right = tok.split("&&", 1)
                s1, o1 = _parse_sub_occ(left); s2, o2 = _parse_sub_occ(right)
                if s1 and s2: tokens.append(("merge", s1, o1, s2, o2))
            else:
                s, o = _parse_sub_occ(tok)
                if s: tokens.append(("single", s, o))
        mapping.append((name, tokens))
    return mapping

# ===== main =====
def main(argv=None):
    ap = argparse.ArgumentParser(description="Build trainer_sheet.html from index.html + splits.txt")
    ap.add_argument("--site", type=Path, default=None, help="Directory containing index.html (autodetected)")
    ap.add_argument("--in", dest="infile", type=Path, default=None, help="Explicit path to index.html")
    ap.add_argument("--out", dest="outfile", type=Path, default=None, help="Output HTML path (default: site/trainer_sheet.html)")
    ap.add_argument("--splits", type=Path, default=None, help="Path to splits.txt (default: site/splits.txt)")
    args = ap.parse_args(argv)

    site_dir, in_file, out_main, splits_file, sprites_dir, sprites_map = build_paths(args)
    print(f"[info] site:   {site_dir}")
    print(f"[info] input:  {in_file}")
    print(f"[info] output: {out_main}")
    print(f"[info] splits: {splits_file}")

    if not in_file.exists():
        print(f"[error] Missing index.html at {in_file}", file=sys.stderr); sys.exit(3)

    html_src = in_file.read_text(encoding="utf-8", errors="ignore")
    soup = BeautifulSoup(html_src, "html.parser")
    tables = soup.select("table.content-table")
    if not tables:
        soup = BeautifulSoup(f"<main>{html_src}</main>", "html.parser")
        tables = soup.select("table.content-table")
    if not tables:
        print("[error] No <table class='content-table'> in index.html", file=sys.stderr); sys.exit(4)

    splits_cfg = parse_splits(splits_file)
    if not splits_cfg:
        print("[error] splits.txt is empty", file=sys.stderr); sys.exit(5)

    custom_rules = read_custom_sprites_map(sprites_map)

    def cap_title(t):
        cap = t.find("caption", class_="caption-content") or t.find("caption")
        title = (cap.get_text(" ", strip=True) if cap else "Trainer")
        title = re.sub(r"<.*?>","",title).strip() or "Trainer"
        return title

    needed = set()
    for _, toks in splits_cfg:
        for tk in toks:
            if tk[0] == "single": needed.add(tk[1])
            else: needed.add(tk[1]); needed.add(tk[3])
    matchers = {s: make_inorder_regex(s) for s in needed}

    seen = defaultdict(int)
    found = {}
    totals = defaultdict(int)

    for t in tables:
        title = cap_title(t)
        low = canonicalize(title)
        for sub in list(needed):
            if not sub: continue
            if sub in low or matchers[sub].search(low):
                seen[sub] += 1; occ = seen[sub]
                totals[sub] = occ
                key = (sub, occ)
                if key not in found:
                    found[key] = (title, BeautifulSoup(str(t), "html.parser").table)

    buttons, panels = [], []
    default_active = splits_cfg[0][0]

    for idx, (name, toks) in enumerate(splits_cfg):
        buttons.append(f'<button type="button" data-target="{name}">{name}</button>')
        items = []

        for tk in toks:
            if tk[0] == "single":
                _, sub, occ = tk
                occ = occ if occ is not None else 1
                key = (sub, occ)
                if key not in found:
                    print(f'[warn] token not matched: {name}: "{sub}" #{occ}', file=sys.stderr)
                    continue
                title, raw_tag = found[key]
                pic_candidates = detect_trainer_sprite(title, custom_rules, sprites_dir, out_main.parent)
                cols = parse_table_columns(raw_tag)
                rebuilt = build_table_from_columns(title, cols, [pic_candidates], themed="single")
                rebuilt["id"] = slugify(title)
                rebuilt["class"] = (rebuilt.get("class", []) + ["trainer-block"])
                items.append(str(rebuilt))

            else:
                _, s1, o1, s2, o2 = tk
                occ1 = (o1 if o1 is not None else totals.get(s1, 1))
                occ2 = (o2 if o2 is not None else totals.get(s2, 1))
                k1 = (s1, occ1); k2 = (s2, occ2)
                if k1 not in found or k2 not in found:
                    print(f'[warn] incomplete merge in "{name}": "{s1}" #{occ1} && "{s2}" #{occ2}', file=sys.stderr)
                    continue
                title1, tag1 = found[k1]
                title2, tag2 = found[k2]
                merged_tbl = merge_two_tables(title1, tag1, title2, tag2, custom_rules, sprites_dir, out_main.parent)
                merged_tbl["id"] = slugify(f"{title1} & {title2} [Double Battle]")
                merged_tbl["class"] = (merged_tbl.get("class", []) + ["trainer-block"])
                items.append(str(merged_tbl))

        items_html = "".join(items) if items else '<p class="split-empty">Nessun trainer assegnato.</p>'
        active_cls = " active" if idx == 0 else ""
        panels.append(
            f'<div class="split-panel{active_cls}" data-split="{name}">\n'
            f'  <h2 class="split-title">{name}</h2>\n'
            f'  {items_html}\n'
            f'</div>'
        )

    page = f"""<!DOCTYPE html>
<html lang="it">
<head>
  <meta charset="UTF-8" />
  <title>Trainer Sheet – Hack Rom</title>
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <link rel="stylesheet" href="sheet_style.css" />
</head>
<body>
  <nav class="topbar">
    <span class="brand">Hack Rom</span>
    <a class="toplink" href="{CALC_URL}" target="_blank" rel="noopener">Calculator</a>
    <a class="toplink" href="{out_main.name}" aria-current="page">Trainer Sheet</a>
    <a class="toplink" href="#" title="Dex coming soon">Dex (soon)</a>
    <span class="fx1"></span>
  </nav>
  <nav class="splitbar" id="splitbar">
    {' '.join(buttons)}
  </nav>
  <main id="sheet">
    {"".join(panels)}
  </main>
  <script>
  (function(){{
    var def = {repr(default_active)};
    function activate(name){{
      document.querySelectorAll('.splitbar button').forEach(function(b){{
        b.classList.toggle('active', b.getAttribute('data-target')===name);
      }});
      document.querySelectorAll('.split-panel').forEach(function(p){{
        p.classList.toggle('active', p.getAttribute('data-split')===name);
      }});
      try{{ history.replaceState(null, "", "#split="+encodeURIComponent(name)); }}catch(e){{}}
    }}
    var m=(location.hash||"").match(/#split=([^&]+)/);
    var target=m?decodeURIComponent(m[1]):def;
    document.getElementById('splitbar').addEventListener('click', function(ev){{
      var b=ev.target.closest('button[data-target]'); if(!b) return;
      ev.preventDefault(); activate(b.getAttribute('data-target'));
    }});
    if(target) activate(target);
  }})();
  </script>
</body>
</html>"""
    out_main.write_text(page, encoding="utf-8")
    print(f"[ok] Wrote: {out_main}")

if __name__ == "__main__":
    main()
