#!/usr/bin/env python3
import argparse
import time
import os
import re
import sys
from typing import Any, Dict, List, Union

tab = "    "
toolDir = os.path.dirname(os.path.realpath(__file__))

infile = sys.argv[1]
outCFile = infile.replace(".asm", ".c")
outHFile = infile.replace(".asm", ".h")

asmPos = 0
labels = []
curLabel = None
inText = False

def convert_line(line: str):
    global labels
    global curLabel
    global inText
    if line == '' or line == ' ':
        return ''
    if not line.startswith('\t'):
        if line.find(":") == -1:
            return ""
        name = line[:line.rfind(":")]
        if name.startswith('_'):
            name = name[1:]
        labels.append(name)
        if curLabel is not None:
            return f"}};\n\nconst struct TextCmd {name}[] = {{"
        curLabel = name
        return f"const struct TextCmd {name}[] = {{"
    line = line.lstrip()
    if line.startswith('sound_'):
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'{line}'
        else:
            return tab + f'{line}'
    if line.startswith('text_ram'):
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'text_ram(wram_ptr({line[9:]}))'
        else:
            return tab + f'text_ram(wram_ptr({line[9:]}))'
    if line.startswith('text_end'):
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'text_end'
        else:
            return tab + f'text_end'
    if line.startswith('text_promptbutton'):
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'text_promptbutton'
        else:
            return tab + f'text_promptbutton'
    if line.startswith('text_today'):
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'text_today'
        else:
            return tab + f'text_today'
    if line.startswith('text_low'):
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'text_low'
        else:
            return tab + f'text_low'
    if line.startswith('text_scroll'):
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'text_scroll'
        else:
            return tab + f'text_scroll'
    if line.startswith('text_decimal'):
        n = line[13:]
        rest = n[n.find(',')+1:]
        ptr = n[:n.find(',')]
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'text_decimal(wram_ptr({ptr}),{rest})'
        else:
            return tab + f'text_decimal(wram_ptr({ptr}),{rest})'
    if line.startswith('text_start'):
        if inText:
            return tab*2 + ')\n' + tab + f'text_start({line[11:]}'
        else:
            inText = True
            return tab + f'text_start({line[11:]}'
    if line.startswith('text_pause'):
        if inText:
            inText = False
            return tab*2 + ')\n' + tab + f'text_pause'
        else:
            return tab + f'text_pause'
    if line.startswith('text'):
        inText = True
        return tab + f'text_start({line[5:]}'
    if line.startswith('line'):
        return tab*2 + f't_line {line[5:]}'
    if line.startswith('done'):
        if inText:
            inText = False
            return tab*2 + f't_done {line[5:]})'
        else:
            return tab*2 + f't_done {line[5:]}'
    if line.startswith('para'):
        return tab*2 + f't_para {line[5:]}'
    if line.startswith('next'):
        return tab*2 + f't_next {line[5:]}'
    if line.startswith('cont'):
        return tab*2 + f't_cont {line[5:]}'
    if line.startswith('prompt'):
        inText = False
        return tab*2 + f't_prompt {line[7:]})'
    return line

with open(infile, 'r', encoding='utf8') as f:
    lines = f.read().splitlines(False)

out = '#include "../../constants.h"\n'

for line in lines:
    out += convert_line(line) + '\n'

if inText:
    out += tab*2 + ')\n'

out += '};\n'

outh = '#pragma once\n'

for label in labels:
    outh += f'extern const struct TextCmd {label}[];\n'

with open(outHFile, 'w', encoding='utf8') as f:
    f.write(outh)

with open(outCFile, 'w', encoding='utf8') as f:
    f.write(out)

