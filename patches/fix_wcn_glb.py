import sys

path = sys.argv[1]
with open(path, 'r') as f:
    c = f.read()

if 'CONFIG_UMW2653' not in c:
    c = c.rstrip()
    if c.endswith('#endif'):
        c = c[:-6] + '#ifdef CONFIG_UMW2653\n#include "umw2653_glb.h"\n#include "wcn_dump.h"\n#endif\n#endif\n'
    with open(path, 'w') as f:
        f.write(c)
