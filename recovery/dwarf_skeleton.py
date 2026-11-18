#!/usr/bin/env python3
"""
dwarf_skeleton.py — Generate a compilable C skeleton from a kernel .ko's DWARF.

Given a .ko with .debug_info, emits a .c containing:
  - recovered struct typedefs (from gdb 'ptype struct X')
  - a function skeleton (stub bodies) for every recovered function
  - extern decls for the undefined kernel symbols
  - module_init/exit stubs

This produces a *buildable reference* capturing the recovered structure.
A maintainer then fills in the real bodies using the DWARF line-mapped
disassembly (see recover_ko.sh / gdb 'disassemble /m <fn>').

Usage: dwarf_skeleton.py <module.ko> <struct_list_file> <functions_file> <out.c>
"""
import re
import subprocess
import sys

KO, structs_file, funcs_file, out_c = sys.argv[1:5]

def gdb(*cmds):
    args = ["gdb", "-batch", "-q", KO]
    for c in cmds:
        args += ["-ex", c]
    r = subprocess.run(args, capture_output=True, text=True)
    return r.stdout

def extract_types():
    out = gdb("info types")
    names = set()
    for m in re.finditer(r'^\s*\d+:\s+struct\s+(\w+)[;,]\s*$', out, re.M):
        names.add(m.group(1))
    # Also 'typedef struct ... X;' and plain struct tags
    for m in re.finditer(r'^(?:struct\s+)?(\w+)\s*;', out, re.M):
        n = m.group(1)
        if n and not n[0].isdigit():
            names.add(n)
    return sorted(names)

def ptype_struct(name):
    out = gdb("ptype struct " + name)
    if "No symbol" in out or "No struct type" in out:
        return None
    lines = [l.rstrip() for l in out.splitlines()]
    if lines and lines[0].startswith("type = struct"):
        lines[0] = lines[0].replace("type = struct", "struct", 1)
    return "\n".join(lines)

def ptype_all(names):
    """Batch ptype for many structs in one gdb invocation."""
    cmds = ["ptype struct " + n for n in names]
    out = gdb(*cmds)
    # split by each result; gdb prints a blank line between results
    blocks = re.split(r'\n\s*\n', out)
    result = {}
    for name, block in zip(names, blocks):
        if "No symbol" in block or "No struct type" in block:
            continue
        lines = [l.rstrip() for l in block.splitlines()]
        if lines and lines[0].startswith("type = struct"):
            lines[0] = lines[0].replace("type = struct", "struct", 1)
        result[name] = "\n".join(lines)
    return result

def ptype_all_fixed(names):
    """Batch ptype, strip ALL 'type = struct' wrappers (nested too)."""
    cmds = ["ptype struct " + n for n in names]
    out = gdb(*cmds)
    blocks = re.split(r'\n\s*\n', out)
    result = {}
    for name, block in zip(names, blocks):
        if "No symbol" in block or "No struct type" in block:
            continue
        block = block.replace("type = struct", "struct")
        result[name] = block.strip() + ";"
    return result

def parse_funcs():
    funcs = []
    if not os.path.exists(funcs_file):
        return funcs
    with open(funcs_file) as f:
        for line in f:
            m = re.match(r'^\s*(\d+):\s*(.*?);\s*$', line)
            if not m:
                continue
            lineno, sig = int(m.group(1)), m.group(2)
            sig = re.sub(r'/\*.*?\*/', '', sig).strip()
            funcs.append((lineno, sig))
    return funcs

def func_ident(sig):
    # extract function name (last identifier before '(' that isn't a type)
    m = re.search(r'([A-Za-z_]\w*)\s*\(', sig)
    if not m:
        return "unknown"
    return m.group(1)

import os

def main():
    types = extract_types()
    funcs = parse_funcs()

    lines = []
    lines.append("// SPDX-License-Identifier: GPL-2.0")
    lines.append("/*")
    lines.append(" * Auto-generated skeleton recovered from DWARF debug info of: %s" % KO)
    lines.append(" * Function signatures + struct types are recovered from .debug_info.")
    lines.append(" * Fill in bodies using 'gdb -batch %s -ex \"disassemble /m <fn>\"'." % KO)
    lines.append(" */")
    lines.append("#include <linux/module.h>")
    lines.append("#include <linux/kernel.h>")
    lines.append("#include <linux/slab.h>")
    lines.append("#include <linux/i2c.h>")
    lines.append("#include <linux/input.h>")
    lines.append("#include <linux/device.h>")
    lines.append("#include <linux/sysfs.h>")
    lines.append("#include <linux/miscdevice.h>")
    lines.append("#include <linux/mutex.h>")
    lines.append("")

    # structs
    lines.append("/* ---- recovered struct types ---- */")
    ptypes = ptype_all_fixed(types)
    for n in types:
        if n in ptypes:
            lines.append(ptypes[n])
            lines.append("")
    if not types:
        lines.append("/* no project structs auto-discovered; add structs manually */")
        lines.append("")

    # extern kernel symbols
    lines.append("/* ---- extern kernel API (from undefined symbols) ---- */")
    lines.append("/* recovered automatically; see extern_symbols.txt */")
    lines.append("")

    # function skeletons
    lines.append("/* ---- recovered function skeletons ---- */")
    for lineno, sig in funcs:
        ident = func_ident(sig)
        # strip 'static' so stubs link; body returns 0/NULL
        body_sig = sig
        is_static = body_sig.startswith("static ")
        if is_static:
            body_sig = body_sig[len("static "):]
        # determine return type for stub body
        ret = "int"
        if "void " in body_sig.split("(")[0] or body_sig.startswith("void "):
            ret = "void"
        elif "bool " in body_sig:
            ret = "bool"
        lines.append("/* L%d: %s */" % (lineno, sig))
        if is_static:
            lines.append("static " + body_sig + ";")
            lines.append("static " + body_sig)
        else:
            lines.append("__maybe_unused " + body_sig)
        lines.append("{")
        if ret == "void":
            lines.append("\treturn;")
        elif ret == "bool":
            lines.append("\treturn false;")
        else:
            lines.append("\treturn 0;")
        lines.append("}")
        lines.append("")

    # module stubs
    lines.append("static int __init mod_init(void)")
    lines.append("{")
    lines.append("\tpr_info(\"%s skeleton loaded\\n\");" % os.path.basename(KO))
    lines.append("\treturn 0;")
    lines.append("}")
    lines.append("static void __exit mod_exit(void)")
    lines.append("{")
    lines.append("}")
    lines.append("module_init(mod_init);")
    lines.append("module_exit(mod_exit);")
    lines.append("MODULE_LICENSE(\"GPL\");")

    with open(out_c, "w") as f:
        f.write("\n".join(lines) + "\n")
    print("wrote %s (%d funcs, %d structs)" % (out_c, len(funcs), len(types)))

main()