#!/usr/bin/env python3
# cxxtocpp.py

import os

files = [f for f in os.listdir(os.curdir) if os.path.isfile(f)]

for f in files:
    if not f.startswith('.') and f.endswith('.cxx'):
        newf = f[0:-4] + '.cpp'
        os.rename(f, newf)
