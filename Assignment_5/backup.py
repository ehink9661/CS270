#!/usr/bin/env python3
# backup.py

import os
import shutil

filedirs = os.listdir(os.curdir)

if not os.path.isdir('.backup'):
    os.mkdir('.backup')

for fd in filedirs:
    if os.path.exists('.backup/' + fd):
        if os.path.isfile('.backup/' + fd):
            os.remove('.backup/' + fd)
            shutil.copyfile(fd, '.backup/' + fd)
        elif os.path.isdir('.backup/' + fd):
            os.rmdir('.backup/' + fd)
            shutil.copytree(fd, '.backup/' + fd)
    else:
        if os.path.isfile('.backup/' + fd):
            shutil.copyfile(fd, '.backup/' + fd)
        elif os.path.isdir('.backup/' + fd):
            shutil.copytree(fd, '.backup/' + fd)

