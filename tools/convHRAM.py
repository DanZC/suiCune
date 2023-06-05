#!/usr/bin/env python3
import argparse
import time
import os
import re
from typing import Any, Dict, List, Union

tab = "    "
toolDir = os.path.dirname(os.path.realpath(__file__))
hramAsmFile = f"{toolDir}/../hram.asm"
hramHFile = f"{toolDir}/../hram.h"

asmPos = 0

def parse_line(line: str):
    if line == '' or line.startswith('SECTION') or line.startswith(';'):
        return None
    parts = line.strip().split('::')
    if parts[0].startswith('h'):
        name = parts[0]
        if len(parts) > 1:
            data = parts[1].strip()
            return {'name': name, 'data': data}
        else:
            return {'name': name, 'data': ''}
    elif parts[0].startswith('d'):
        return {'name': '', 'data': parts[0]}
    elif parts[0].startswith('UNION'):
        return {'name': 'union', 'data': 'begin'}
    elif parts[0].startswith('NEXTU'):
        return {'name': 'union', 'data': 'next'}
    elif parts[0].startswith('ENDU'):
        return {'name': 'union', 'data': 'end'}
    elif parts[0].startswith('if'):
        return {'name': 'if', 'data': parts[0].split(' ', 1)[1]}
    elif parts[0].startswith('endc'):
        return {'name': 'if', 'data': 'end'}

output: Dict[int, list] = {}
spos = 0
lastname = ''

def read_asm_segment(slist: List[Dict[str, Union[str, int]]]):
    global asmPos
    global spos
    global lastname
    s = slist[spos]

    if s is None:
        spos += 1
        return
    if s['name'] == '':
        if s['data'].startswith('ds'):
            n = int(s['data'][3:])
            print(f'skip {n}')
            res = {'type': 'field', 'pos': asmPos, 'name': 'skip', 'size': n}
            asmPos += n
            spos += 1
            return res
        else:
            print(s)
            spos += 1
            return
    elif s['name'] == 'union':
        if s['data'] == 'begin':
            spos += 1
            apos = asmPos
            epos = 0
            segments = []
            segment = {}
            print(f'union begin')
            while spos < len(slist):
                s = slist[spos]
                if s is not None and s['name'] == 'union':
                    if s['data'] == 'next':
                        segments.append(segment.copy())
                        segment = {}
                        epos = max(asmPos, epos)
                        asmPos = apos
                        print(f'union next')
                        spos += 1
                        continue
                    elif s['data'] == 'end':
                        epos = max(asmPos, epos)
                        asmPos = epos
                        spos += 1
                        segments.append(segment.copy())
                        print(f'union end')
                        return {'type': 'union', 'pos': apos, 'segments': segments}
                seg = read_asm_segment(slist)
                if seg is not None:
                    if seg['pos'] not in seg.keys():
                        segment[seg['pos']] = []
                    segment[seg['pos']].append(seg.copy())
    else:
        data = s['data']
        if data == 'db':
            size = 1
        elif data == 'dw':
            size = 2
        elif data.startswith('ds'):
            size = int(data[3:])
        else:
            size = 0
        res = {'type': 'field', 'pos': asmPos, 'name': s['name'], 'size': size}
        print(f'{data} {s["name"]}')
        asmPos += size 
        spos += 1
        return res



def read_asm():
    global hramAsmFile
    global hramHFile
    global asmPos
    global spos
    global output
    with open(hramAsmFile, "r", encoding="utf8") as inFile:
        asmFile = inFile.read().split("\n")
    
    slist = [parse_line(line) for line in asmFile]
    output = {}
    flds = []

    while spos < len(slist):
        seg = read_asm_segment(slist)
        if seg is not None:
            if seg['pos'] not in output.keys():
                output[seg['pos']] = []
            output[seg['pos']].append(seg)

    def print_item(indent, d: dict, sz = -1):
        dsizes = {0: 'void*', 1: 'uint8_t', 2: 'uint16_t', 4: 'uint32_t'}

        if d['type'] == 'field':
            if d['name'] == 'skip':
                nm = f'unused_{d["pos"]}'
            else:
                nm = d['name']
                flds.append(nm)
            nm = f'unused_{d["pos"]}' if d['name'] == 'skip' else d['name']
            if sz == -1:
                sz = d['size']
            if sz in dsizes.keys():
                return (tab * indent) + f"{dsizes[sz]} {nm};\n"
            else:
                return (tab * indent) + f"uint8_t {nm}[{sz}];\n"
        elif d['type'] == 'union':
            out = (tab * indent) + "union {\n"
            for v2 in d['segments']:
                out += (tab * (indent + 1)) + "struct __attribute__((packed)) {\n"
                for kk, vv in v2.items():
                    out += (tab * (indent + 2)) + f"// {kk}\n"
                    if len(vv) == 1:
                        out += print_item(indent + 2, vv[0])
                    else:
                        out += (tab * (indent + 2)) + "union {\n"
                        sz2 = vn[-1]['size']
                        for vn in vv:
                            out += print_item(indent + 3, vn, sz2)
                        out += (tab * (indent + 2)) + "};\n"
                out += (tab * (indent + 1)) + "};\n"
            out += (tab * indent) + "};\n"
            return out
        else:
            return "(void)"

    out = """#pragma once
#include "constants.h"

// A struct representing HRAM.
struct __attribute__((packed)) hram_s
{
    uint8_t padding[hROMBankBackup - 0xff80];
"""
    for k, v in output.items():
        out += tab + f"// {k}\n"
        if len(v) == 1:
            out += print_item(1, v[0])
        else:
            out += (tab) + "union {\n"
            sz2 = v[-1]['size']
            for vn in v:
                out += print_item(2, vn, sz2)
            out += (tab) + "};\n"
    
    out += """};

extern struct hram_s* hram;
#define check_field(_fld) _Static_assert(__builtin_offsetof(struct hram_s, _fld) == (_fld - 0xff80));

"""
    for fld in flds:
        out += f"check_field({fld})\n"
    
    with open(hramHFile, "w", encoding="utf8") as outFile:
        outFile.write(out)

if __name__ == '__main__':
    read_asm()