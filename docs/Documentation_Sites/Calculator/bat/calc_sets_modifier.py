#!/usr/bin/env python3
import argparse
import re
import shutil
from pathlib import Path


RE_HEADER = re.compile(r'^\s*window\.TRAINER_SETS\s*=\s*\{', re.MULTILINE)

# Remove trailing " (M)" / " (F)" inside quoted strings (both " and ')
RE_GENDER_QUOTED_DQ = re.compile(r'"([^"\n]*?)\s*\((M|F)\)"')
RE_GENDER_QUOTED_SQ = re.compile(r"'([^'\n]*?)\s*\((M|F)\)'")


def transform(text: str) -> tuple[str, dict]:
    stats = {
        "header_replaced": 0,
        "gender_removed_dq": 0,
        "gender_removed_sq": 0,
    }

    # Header
    new_text, n = RE_HEADER.subn("var SETDEX_SV = {", text, count=1)
    stats["header_replaced"] = n
    text = new_text

    # Gender suffixes in double-quoted strings
    def _dq(m: re.Match) -> str:
        stats["gender_removed_dq"] += 1
        return f"\"{m.group(1)}\""

    text = RE_GENDER_QUOTED_DQ.sub(_dq, text)

    # Gender suffixes in single-quoted strings
    def _sq(m: re.Match) -> str:
        stats["gender_removed_sq"] += 1
        return f"'{m.group(1)}'"

    text = RE_GENDER_QUOTED_SQ.sub(_sq, text)

    return text, stats


def main() -> int:
    ap = argparse.ArgumentParser(description="Prepare gen9.js for the calc (SETDEX_SV + remove (M)/(F)).")
    ap.add_argument("--src", default="../../Trainer_Docs/gen9.js", help="Source gen9.js path")
    ap.add_argument("--dst", default="./gen9.js", help="Destination path (edited copy)")
    args = ap.parse_args()

    src = Path(args.src).resolve()
    dst = Path(args.dst).resolve()

    if not src.is_file():
        print(f"[error] Source not found: {src}")
        return 2

    dst.parent.mkdir(parents=True, exist_ok=True)

    # Copy first, then edit the copy
    shutil.copyfile(src, dst)

    original = dst.read_text(encoding="utf-8", errors="replace")
    updated, stats = transform(original)
    dst.write_text(updated, encoding="utf-8", newline="\n")

    if stats["header_replaced"] == 0:
        print("[warn] Header 'window.TRAINER_SETS = {' not found; no header replacement applied.")
    print(f"[ok] Written: {dst}")
    print(f"     header_replaced={stats['header_replaced']}")
    print(f"     gender_removed={stats['gender_removed_dq'] + stats['gender_removed_sq']} "
          f"(dq={stats['gender_removed_dq']}, sq={stats['gender_removed_sq']})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
