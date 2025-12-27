import pathlib
import pickle
import re
import typing

import porydex.config

_MAPSEC_ENUM_VALUES: dict[str, int] | None = None

def _get_mapsec_enum_values() -> dict[str, int]:
    """
    Legge include/constants/region_map_sections.h e costruisce una
    mappa { "MAPSEC_xxx": intero } basata sull'ordine dell'enum.
    """
    global _MAPSEC_ENUM_VALUES
    if _MAPSEC_ENUM_VALUES is not None:
        return _MAPSEC_ENUM_VALUES

    header = porydex.config.expansion / 'include' / 'constants' / 'region_map_sections.h'
    mapping: dict[str, int] = {}
    current = 0

    try:
        text = header.read_text(encoding='utf-8')
    except FileNotFoundError:
        _MAPSEC_ENUM_VALUES = {}
        return _MAPSEC_ENUM_VALUES

    for line in text.splitlines():
        line = line.strip()
        # ignoriamo commenti a fine riga
        if '//' in line:
            line = line.split('//', 1)[0].strip()
        if not line:
            continue

        if not line.startswith('MAPSEC_'):
            continue

        # togli la virgola finale e/o '}' se presenti
        line = line.rstrip(',}').strip()

        # gestisci il caso (in futuro) MAPSEC_X = 123
        if '=' in line:
            name, value = line.split('=', 1)
            name = name.strip()
            value = value.strip()
            try:
                current = int(value, 0)
            except ValueError:
                # valore strano, skippa
                continue
        else:
            name = line

        mapping[name] = current
        current += 1

    _MAPSEC_ENUM_VALUES = mapping
    return _MAPSEC_ENUM_VALUES


from pycparser import parse_file
from pycparser.c_ast import (
    BinaryOp,
    Cast,
    CompoundLiteral,
    Decl,
    ExprList,
    FuncCall,
    ID,
    TernaryOp,
    UnaryOp,
)

from porydex.common import (
    PICKLE_PATH,
    BINARY_BOOL_OPS,
    CONFIG_INCLUDES,
    EXPANSION_INCLUDES,
    GLOBAL_PREPROC,
    PREPROCESS_LIBC,
)

def _pickle_target(fname: pathlib.Path) -> pathlib.Path:
    return PICKLE_PATH / fname.stem

def _load_pickled(fname: pathlib.Path) -> ExprList | None:
    target = _pickle_target(fname)
    exts = None
    if target.exists():
        with open(target, 'rb') as f:
            exts = pickle.load(f)
    return exts

def _dump_pickled(fname: pathlib.Path, exts: list):
    PICKLE_PATH.mkdir(parents=True, exist_ok=True)
    target = _pickle_target(fname)
    with open(target, 'wb') as f:
        pickle.dump(exts, f, protocol=pickle.HIGHEST_PROTOCOL)

def load_data(fname: pathlib.Path,
              extra_includes: list[str]=[]) -> ExprList:
    exts = _load_pickled(fname)
    if not exts:
        include_dirs = [f'-I{porydex.config.expansion / dir}' for dir in EXPANSION_INCLUDES]
        exts = parse_file(
            fname,
            use_cpp=True,
            cpp_path=porydex.config.compiler,
            cpp_args=[
                *PREPROCESS_LIBC,
                *include_dirs,
                *GLOBAL_PREPROC,
                *CONFIG_INCLUDES,
                *extra_includes
            ]
        ).ext
        _dump_pickled(fname, exts)

    return exts

def load_truncated(fname: pathlib.Path,
                   extra_includes: list[str]=[]) -> ExprList:
    return load_data(fname, extra_includes)[-1].init.exprs

def load_table_set(fname: pathlib.Path,
                   extra_includes: list[str]=[],
                   minimal_preprocess: bool=False) -> list[Decl]:
    include_dirs = [f'-I{porydex.config.expansion / dir}' for dir in EXPANSION_INCLUDES]

    if minimal_preprocess:
        # do NOT dump this version
        exts = parse_file(
            fname,
            use_cpp=True,
            cpp_path=porydex.config.compiler,
            cpp_args=[
                *PREPROCESS_LIBC,
                *include_dirs,
                r'-DTRUE=1',
                r'-DFALSE=0',
                r'-Du16=short',
                r'-include', r'config/species_enabled.h',
                *extra_includes
            ]
        ).ext
    else:
        exts = _load_pickled(fname)

    if not exts:
        exts = parse_file(
            fname,
            use_cpp=True,
            cpp_path=porydex.config.compiler,
            cpp_args=[
                *PREPROCESS_LIBC,
                *include_dirs,
                *GLOBAL_PREPROC,
                *CONFIG_INCLUDES,
                *extra_includes
            ]
        ).ext
        _dump_pickled(fname, exts)

    return exts

def load_data_and_start(fname: pathlib.Path,
                        pattern: re.Pattern,
                        extra_includes: list[str]=[]) -> tuple[ExprList, int]:
    all_data = load_data(fname, extra_includes)

    start = 0
    if pattern:
        end = len(all_data)
        for i in range(-1, -end, -1):
            if not all_data[i].name or not pattern.match(all_data[i].name):
                start = i + 1
                break

    return (all_data, start)

def eval_binary_operand(expr) -> int:
    if isinstance(expr, BinaryOp):
        return int(process_binary(expr))
    elif isinstance(expr, TernaryOp):
        return int(process_ternary(expr).value)
    return int(expr.value)

def process_binary(expr: BinaryOp) -> int | bool:
    left = eval_binary_operand(expr.left)
    right = eval_binary_operand(expr.right)
    op = BINARY_BOOL_OPS[expr.op]
    return op(left, right)

def process_ternary(expr: TernaryOp) -> typing.Any:
    if isinstance(expr.cond.left, ID):
        raise ValueError('cannot process left-side ID value in ternary')
    if isinstance(expr.cond.right, ID):
        raise ValueError('cannot process right-side ID value in ternary')

    op = BINARY_BOOL_OPS[expr.cond.op]
    if op(expr.cond.left.value, expr.cond.right.value):
        return expr.iftrue
    else:
        return expr.iffalse



from pycparser.c_ast import Cast, CompoundLiteral, FuncCall, ID, InitList, Constant

def extract_compound_str(expr):

    if expr is None:
        return None

    # Caso: macro _(x) definita come {x} -> InitList di Constant string
    if isinstance(expr, InitList):
        parts = []
        for e in (expr.exprs or []):
            if isinstance(e, Constant) and e.type == 'string':
                parts.append(e.value[1:-1])  # togli virgolette
        if parts:
            return ''.join(parts).replace('\\n', ' ')
        return ''

    # arm-none-eabi-gcc: Cast(FuncCall(ExprList([Constant])))
    if isinstance(expr, Cast):
        return expr.expr.args.exprs[-1].value.replace('\\n', ' ')[1:-1]

    # clang: CompoundLiteral(InitList([Constant]))
    if isinstance(expr, CompoundLiteral):
        return extract_compound_str(expr.init)

    # Alcuni preprocessing producono qualcosa con .exprs (ExprList/InitList-like)
    if hasattr(expr, 'exprs') and expr.exprs:
        if isinstance(expr.exprs[-1], FuncCall):
            return extract_compound_str(expr.exprs[0].args)

        last = expr.exprs[-1]
        if isinstance(last, Constant) and last.type == 'string':
            return last.value.replace('\\n', ' ')[1:-1]

    # Simbolo: deve essere risolto fuori (desc_by_id)
    if isinstance(expr, ID):
        return None

    return None



def extract_u8_str(expr) -> str:
    # Depending on the compiler used for preprocessing, this could be expanded
    # to a number of types.

    # arm-none-eabi-gcc and gcc expand the macro to FuncCall(ExprList([Constant]))
    if isinstance(expr, FuncCall):
        return expr.args.exprs[-1].value.replace('\\n', ' ')[1:-1]

    # clang expands the macro to InitList([Constant])
    return expr.exprs[0].value.replace('\\n', ' ')[1:-1]

def extract_int(expr) -> int:
    if isinstance(expr, TernaryOp):
        return int(process_ternary(expr).value)

    if isinstance(expr, UnaryOp):
        # we only care about the negative symbol
        if expr.op != '-':
            raise ValueError(f'unrecognized unary operator: {expr.op}')
        return -1 * int(expr.expr.value)

    if isinstance(expr, BinaryOp):
        return int(process_binary(expr))

    # NEW: gestisce ID tipo MAPSEC_LITTLEROOT_TOWN
    if isinstance(expr, ID):
        values = _get_mapsec_enum_values()
        if expr.name in values:
            return values[expr.name]
        # se è un altro identificatore sconosciuto, fallo fallire esplicitamente
        raise ValueError(f'unrecognized identifier in extract_int: {expr.name!r}')

    try:
        return int(expr.value)
    except ValueError:
        # try hexadecimal; if that doesn't work, just fail
        return int(expr.value, 16)


    if isinstance(expr, UnaryOp):
        # we only care about the negative symbol
        if expr.op != '-':
            raise ValueError(f'unrecognized unary operator: {expr.op}')
        return -1 * int(expr.expr.value)

    if isinstance(expr, BinaryOp):
        return int(process_binary(expr))

    try:
        return int(expr.value)
    except ValueError:
        # try hexadecimal; if that doesn't work, just fail
        return int(expr.value, 16)

def extract_id(expr) -> str:
    if isinstance(expr, TernaryOp):
        return process_ternary(expr).name

    if isinstance(expr, BinaryOp):
        return str(expr.op).join([expr.left.name, expr.right.name])

    return expr.name

def extract_prefixed(prefix: str | re.Pattern, val: str, mod_if_match: typing.Callable[[str], str]=lambda x: x) -> str:
    match = re.match(prefix, val)
    if match:
        return mod_if_match(match.group(1))

    return val

