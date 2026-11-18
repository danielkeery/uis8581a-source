#!/usr/bin/env bash
# recover_ko.sh — Reconstruct a Linux kernel module source skeleton from DWARF debug info.
#
# Methodology (reusable PoC for recovering kernel module sources from shipped .ko):
#   1. modinfo  -> author/description/license/version/depends/vermagic
#   2. readelf  -> symbols (defined + undefined), sections, .modinfo
#   3. DWARF (.debug_info / .debug_str / .debug_line) via gdb:
#        - function inventory (name + full C signature + source line)
#        - struct typedefs (ptype)
#        - global variables
#        - source file path(s)
#        - per-function source-line disassembly
#   4. objdump  -> register/constant immediates referenced in code
#   5. strings  -> format strings / register names / messages
#   6. Assemble a header + function-skeleton .c for a maintainer to fill in.
#
# Usage: recover_ko.sh <module.ko> <output_dir>
set -euo pipefail

KO="$1"
OUT="$2"
NAME="$(basename "$KO" .ko)"
mkdir -p "$OUT"

echo "### modinfo" | tee "$OUT/modinfo.txt"
modinfo "$KO" 2>/dev/null | tee -a "$OUT/modinfo.txt" || true

echo "### defined functions" | tee "$OUT/functions.txt"
gdb -batch -q "$KO" -ex "info functions" 2>/dev/null | \
  grep -E "^(File|\s*[0-9]+:)" | tee -a "$OUT/functions.txt" || true

echo "### undefined (extern kernel API) symbols" | tee "$OUT/extern_symbols.txt"
readelf -s "$KO" 2>/dev/null | awk '$7=="UND"{print $8}' | sort -u | \
  grep -vE "^$" | tee -a "$OUT/extern_symbols.txt" || true

echo "### defined symbols" | tee "$OUT/defined_symbols.txt"
readelf -s "$KO" 2>/dev/null | awk '$7!="UND"{print $8}' | sort -u | \
  grep -vE "^$" | tee -a "$OUT/defined_symbols.txt" || true

echo "### global variables" | tee "$OUT/globals.txt"
gdb -batch -q "$KO" -ex "info variables" 2>/dev/null | \
  grep -E "\.c:" | tee -a "$OUT/globals.txt" || true

echo "### source file paths" | tee "$OUT/sources.txt"
strings -n 3 "$KO" | grep -oE "/[^ ]+\.c$|/[^ ]+\.h$" | sort -u | tee -a "$OUT/sources.txt" || true

echo "### format strings / messages" | tee "$OUT/strings.txt"
strings -n 6 "$KO" | grep -vE "^__|\[R[0-9]|^vsmk|^aarch64|^clang|^SMP|^vermagic|^srcver|\.symtab|\.strtab|\.debug" | \
  grep -vE "\.ko$|^[0-9a-f]{8}$" | sort -u | tee -a "$OUT/strings.txt" || true

echo "### struct typedefs" | tee "$OUT/types.txt"
# Heuristic: dump all DWARF type names referenced (device/private structs).
gdb -batch -q "$KO" -ex "info types" 2>/dev/null | \
  grep -E "struct |typedef |union " | grep -vE "^\*" | head -200 | tee -a "$OUT/types.txt" || true

echo "### immediate constants in code" | tee "$OUT/constants.txt"
objdump -d "$KO" 2>/dev/null | grep -oE "#0x[0-9a-f]+" | sort | uniq -c | sort -rn | \
  tee -a "$OUT/constants.txt" || true

echo "### register map (rodata bytes 0x20..0x60, likely i2c command table)" | tee "$OUT/rodata.txt"
objdump -s -j .rodata "$KO" 2>/dev/null | head -12 | tee -a "$OUT/rodata.txt" || true

echo "Recovery data written to $OUT/"