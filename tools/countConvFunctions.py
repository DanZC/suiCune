import sys
import os.path as fs
from glob import glob
import re
from typing import Tuple

# Counts the number of asm functions/symbols converted in the converted engine files.

def get_c_name(expr: str) -> Tuple[str, bool]:
    parts = re.findall(r'\w+', expr)
    if not parts:
        return expr, False
    is_not_vanilla = False
    if parts[0] != 'void':
        is_not_vanilla = True
    while parts[0] == 'struct' or parts[0] == 'extern' or parts[0] == 'const' or parts[0] == 'union':
        parts = parts[1:]
    if len(parts) == 1:
        return '', is_not_vanilla
    parts = parts[1:]
    return parts[0], is_not_vanilla or (len(parts) > 1 and parts[1] != 'void')

def read_symbols_from_file(file):
    path = file.replace('.c', '.h')
    if not fs.exists(path):
        return {}
    with open(path, 'r') as f:
        text = f.read()
    mat = re.search(r'(\\{[^\\}]\\})', text)
    if mat:
        text = text.replace(mat.string, '')
    lines = text.splitlines()
    symbols = {}
    for line in lines:
        while line.startswith('//'):
            line = line[2:].strip()
        if line.startswith('#'):
            continue
        if line == '':
            continue
        if '{' in line:
            continue
        name, is_not_vanila = get_c_name(line)
        if name.endswith('_Conv') or name.endswith('_Conv2'):
            symbols[name[:name.find('_Conv')]] = True
            continue
        elif is_not_vanila:
            symbols[name] = True
            continue
        else:
            symbols[name] = False
            continue
    return symbols

with open('functions.c', 'r') as f:
    text = f.read()

lines = text[text.find('// home/array.c'):].splitlines()

i = 0
files = {}
cur_file = ''
while i < len(lines):
    line = lines[i].strip()
    if line == '}':
        break
    if line == '':
        i += 1
        continue
    while line.startswith('//'):
        line = line[2:].strip()
    if line.startswith('CONVERTED'):
        i += 1
        name = line[line.find('(')+1:line.find(')')]
        files[cur_file]['symbols'][name] = True
        continue
    if line.startswith('REDIRECTED'):
        i += 1
        continue
    if line.startswith('maps'):
        i += 1
        continue
    cur_file = line
    files[cur_file] = {'symbols': read_symbols_from_file(line.replace('.c', '.h'))}
    i += 1

file_total = 0
converted_total = 0
for key, value in files.items():
    total = len(value['symbols'])
    if total == 0:
        continue
    converted = 0
    print(f'{key}:')
    for k, v in value['symbols'].items():
        print('   ', k, f'converted = {v}')
        converted += 1 if v else 0
        converted_total += 1 if v else 0
        continue
    file_total += total
    print(f'    {converted:02}/{total:02} functions converted ({(converted / total) * 100:.2f}%)')

print()
print(f"Total: {converted_total:02}/{file_total:02} converted ({(converted_total / file_total) * 100:.2f}%)")
