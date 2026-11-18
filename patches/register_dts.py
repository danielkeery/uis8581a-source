import sys

p = sys.argv[1]
lines = open(p).read().split('\n')

# Insert uis8581a2h10.dtb right after sp9863a-2h10.dtb in the dtb list
out = []
inserted = False
for ln in lines:
    out.append(ln)
    if not inserted and 'sp9863a-2h10.dtb' in ln:
        indent = ln[:len(ln) - len(ln.lstrip())]
        out.append(indent + '   uis8581a2h10.dtb\t\\')
        inserted = True

open(p, 'w').write('\n'.join(out))
if inserted:
    print("DTS-REGISTERED")
else:
    print("DTS-REGISTER-FAILED")
    sys.exit(1)