import pathlib
import re

from pycparser.c_ast import ExprList, NamedInitializer, ID
from yaspin import yaspin

from porydex.common import name_key
from porydex.model import DAMAGE_TYPE, DAMAGE_CATEGORY, CONTEST_CATEGORY
from porydex.parse import load_truncated, extract_int, extract_compound_str


FLAGS_EXPANSION_TO_SHOWDOWN = {
    'bitingMove': 'bite',
    'ballisticMove': 'bullet',
    'ignoresSubstitute': 'bypasssub',
    'cantUseTwice': 'cantusetwice',
    'makesContact': 'contact',
    'thawsUser': 'defrost',
    'mirrorMoveBanned': 'mirror',
    'powderMove': 'powder',
    'ignoresProtect': 'protect',
    'pulseMove': 'pulse',
    'punchingMove': 'punch',
    'magicCoatAffected': 'reflectable',
    'slicingMove': 'slicing',
    'snatchAffected': 'snatch',
    'soundMove': 'sound',
    'windMove': 'wind',
}

# --------------------------------------------------------------------
# Description extraction (from *source text*, not AST)
# --------------------------------------------------------------------

_DESC_DECL_RE = re.compile(
    r'static\s+const\s+u8\s+(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s*\[\s*\]\s*=\s*(?P<rhs>.*?);',
    re.DOTALL
)
_STRING_RE = re.compile(r'"(?:\\.|[^"\\])*"')


def _collect_descriptions_from_source(path: pathlib.Path) -> dict:
    """
    Estrae stringhe da definizioni tipo:
      static const u8 sMegaDrainDescription[] = _(
          "A\n"
          "B");
    con #define _(x) {x}
    o anche altre forme purché contengano string literal.

    Ritorna dict: { "sMegaDrainDescription": "A B" }
    """
    text = path.read_text(encoding="utf-8", errors="replace")
    out = {}

    for m in _DESC_DECL_RE.finditer(text):
        name = m.group("name")
        if not name.endswith("Description"):
            continue

        rhs = m.group("rhs")
        parts = [s[1:-1] for s in _STRING_RE.findall(rhs)]
        if not parts:
            continue

        desc = "".join(parts).replace("\\n", " ")
        out[name] = desc

    return out


# --------------------------------------------------------------------
# moves parsing
# --------------------------------------------------------------------

def parse_move(struct_init: NamedInitializer, desc_by_id: dict) -> dict:
    init_list = struct_init.expr.exprs
    move = {}
    move['num'] = extract_int(struct_init.name[0])
    move['flags'] = {
        # showdown dex interpreta questi come "affetto da / invocabile da"
        # mentre expansion li tiene spesso al contrario
        'protect': 1,
        'mirror': 1,
    }

    for field_init in init_list:
        field_name = field_init.name[0].name
        field_expr = field_init.expr

        match field_name:
            case 'name':
                move['name'] = extract_compound_str(field_expr)

            case 'description':
                desc = None

                # Caso: .description = sHyperBeamDescription
                if isinstance(field_expr, ID):
                    desc = desc_by_id.get(field_expr.name)
                    if desc is None:
                        # non crashare: lascia vuoto + warning
                        print(f"warning: missing description symbol {field_expr.name}")
                        desc = ''
                else:
                    # Caso: .description = COMPOUND_STRING("...") (o simili)
                    # (se non gestito da extract_compound_str, torna None)
                    desc = extract_compound_str(field_expr) or ''

                move['shortDesc'] = desc.replace('\n', ' ')
                move['desc'] = desc

            case 'power':
                move['basePower'] = extract_int(field_expr)

            case 'type':
                move['type'] = DAMAGE_TYPE[extract_int(field_expr)]

            case 'accuracy':
                # expansion: 0 = "infinite accuracy"
                acc = extract_int(field_expr)
                move['accuracy'] = acc if acc > 0 else True

            case 'pp':
                move['pp'] = extract_int(field_expr)

            case 'priority':
                move['priority'] = extract_int(field_expr)

            case 'category':
                move['category'] = DAMAGE_CATEGORY[extract_int(field_expr)]

            case 'criticalHitStage':
                # expansion: "additional" stage; showdown: include implicit +1
                move['critRatio'] = extract_int(field_expr) + 1

            case 'contestCategory':
                move['contestType'] = CONTEST_CATEGORY[extract_int(field_expr)]

            case 'bitingMove' \
                | 'ballisticMove' \
                | 'ignoresSubstitute' \
                | 'cantUseTwice' \
                | 'makesContact' \
                | 'thawsUser' \
                | 'powderMove' \
                | 'pulseMove' \
                | 'punchingMove' \
                | 'magicCoatAffected' \
                | 'slicingMove' \
                | 'snatchAffected' \
                | 'soundMove' \
                | 'windMove':
                move['flags'][FLAGS_EXPANSION_TO_SHOWDOWN[field_name]] = 1

            case 'ignoresProtect' | 'mirrorMoveBanned':
                # showdown usa flag opposta: se expansion dice "ignores", rimuoviamo
                key = FLAGS_EXPANSION_TO_SHOWDOWN[field_name]
                if key in move['flags']:
                    del move['flags'][key]

            case _:
                pass

    # cleanup: expansion talvolta marca sound moves anche bypasssub
    if 'sound' in move['flags'] and 'bypasssub' in move['flags']:
        del move['flags']['bypasssub']

    # se per qualunque motivo manca description, evita che la UI stampi undefined
    move.setdefault('shortDesc', '')
    move.setdefault('desc', '')

    return move


def parse_moves_data(moves_data: ExprList, desc_by_id: dict) -> dict:
    all_moves = {}
    for move_init in moves_data:
        try:
            move = parse_move(move_init, desc_by_id)
            key = name_key(move['name'])
            all_moves[key] = move
        except Exception as err:
            print('error parsing move')
            print(move_init.show())
            raise err

    return all_moves


# --------------------------------------------------------------------
# Pre-sanitize moves_info for pycparser
# --------------------------------------------------------------------

def _strip_additional_effects_from_text(source: str) -> str:
    """
    Rimuove le inizializzazioni del campo `.additionalEffects`
    che usano la macro ADDITIONAL_EFFECTS(...) da moves_info.h,
    lasciando il resto del file invariato.
    """
    out = []
    i = 0
    n = len(source)

    while i < n:
        if source.startswith(".additionalEffects", i):
            # es: ".additionalEffects = ADDITIONAL_EFFECTS({ ... }),"
            k = source.find("ADDITIONAL_EFFECTS", i)
            if k == -1:
                out.append(source[i])
                i += 1
                continue

            p = source.find("(", k)
            if p == -1:
                out.append(source[i])
                i += 1
                continue

            depth = 0
            idx = p
            while idx < n:
                ch = source[idx]
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth -= 1
                    if depth == 0:
                        idx += 1
                        break
                idx += 1

            while idx < n and source[idx] in " \t":
                idx += 1
            if idx < n and source[idx] == ",":
                idx += 1
            while idx < n and source[idx] in " \t":
                idx += 1

            i = idx
            continue

        out.append(source[i])
        i += 1

    return "".join(out)


def _prepare_moves_file_for_porydex(src: pathlib.Path) -> pathlib.Path:
    """
    Crea un file temporaneo "sanitized" vicino al src, in modo che:
    - pycparser non si schianti su additionalEffects
    - restino nel testo le static const u8 sXDescription[] ...; (per il collector regex)
    """
    sanitized = src.with_name(src.stem + "_porydex_tmp" + src.suffix)

    text = src.read_text(encoding="utf-8", errors="replace")
    text = _strip_additional_effects_from_text(text)

    sanitized.write_text(text, encoding="utf-8")
    return sanitized


# --------------------------------------------------------------------
# Public entry point
# --------------------------------------------------------------------

def parse_moves(fname: pathlib.Path) -> dict:
    sanitized_fname = _prepare_moves_file_for_porydex(fname)

    # ✅ Prima raccogliamo tutte le sXDescription dal TESTO
    desc_by_id = _collect_descriptions_from_source(sanitized_fname)

    moves_data: ExprList
    with yaspin(text=f'Loading moves data: {sanitized_fname}', color='cyan') as spinner:
        moves_data = load_truncated(
            sanitized_fname,
            extra_includes=[
                r'-include', r'constants/battle.h',
                r'-include', r'constants/moves.h',
            ],
        )
        spinner.ok("✅")

    return parse_moves_data(moves_data, desc_by_id)
