#!/usr/bin/env python3
"""Run a syntax check for every project-owned C source file."""

from __future__ import annotations

import shutil
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"
COMPILER = shutil.which("cc")


def check_source(source: Path) -> subprocess.CompletedProcess[str]:
    standard = "c2x" if "c23-features" in source.parts else "c17"
    return subprocess.run(
        [str(COMPILER), f"-std={standard}", "-Wall", "-Wextra", "-pedantic", "-fsyntax-only", str(source)],
        cwd=ROOT,
        capture_output=True,
        text=True,
        timeout=120,
    )


def main() -> int:
    if not COMPILER:
        print("No C compiler was found", file=sys.stderr)
        return 2
    sources = sorted(SRC.rglob("*.c"))
    failures: list[tuple[str, str]] = []
    for source in sources:
        result = check_source(source)
        relative = source.relative_to(ROOT).as_posix()
        if result.returncode == 0:
            print(f"PASS {relative}")
        else:
            failures.append((relative, result.stderr or result.stdout))
            print(f"FAIL {relative}")
    if failures:
        print("\nBuild failures:", file=sys.stderr)
        for name, output in failures:
            print(f"\n[{name}]\n{output[-4000:]}", file=sys.stderr)
        return 1
    print(f"Checked {len(sources)} C source files")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
