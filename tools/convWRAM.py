#!/usr/bin/env python3
import argparse
import time
import os
import re
from typing import Any, Dict, List, Union
from dataclasses import dataclass

tab = "    "
toolDir = os.path.dirname(os.path.realpath(__file__))
wramAsmFile = f"{toolDir}/../wram.asm"
wramHFile = f"{toolDir}/../wram.h"
wramCFile = f"{toolDir}/../wram.c"

exprs = re.compile(r'(\;[^\n]*)'
                   r'|([0-9]+|\$[0-9a-fA-F]+|\%[0-1]+)'
                   r'|(db|dw|dt|ds|SECTION|UNION|NEXTU|ENDU|for|if|endc|endr|flag_array)'
                   r'|([\w]+)'
                   r'|(\+|\-|\*|\&|\||\:\:|\:|\{|\}|\(|\)|\,)'
                   r'|(\"[^\"]*\")')

asmPos = 0

def parse_line(line: str):
    if line == '' or line.startswith(';'):
        return None
    if line.startswith('SECTION'):
        sparts = line[8:].split(',')
        name = sparts[0].strip()
        bank = sparts[1].strip()
        return {'type': 'section', 'name': name[1:len(name)-1], 'data': bank}
    parts = line.strip().split('::')
    if parts[0].startswith('w'):
        name = parts[0]
        if len(parts) > 1:
            data = parts[1].strip()
            return {'type': 'field', 'name': name, 'data': data}
        else:
            return {'type': 'field', 'name': name, 'data': ''}
    elif parts[0].startswith('d'):
        return {'type': 'field', 'name': '', 'data': parts[0]}
    elif parts[0].startswith('UNION'):
        return {'type': 'union', 'name': 'union', 'data': 'begin'}
    elif parts[0].startswith('NEXTU'):
        return {'type': 'union', 'name': 'union', 'data': 'next'}
    elif parts[0].startswith('ENDU'):
        return {'type': 'union', 'name': 'union', 'data': 'end'}
    elif parts[0].startswith('if'):
        return {'type': 'if', 'name': 'if', 'data': parts[0].split(' ', 1)[1]}
    elif parts[0].startswith('endc'):
        return {'type': 'endc', 'name': 'if', 'data': 'end'}

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
    if s['type'] == 'section':
        print('Section', s['name'])
        spos += 1
        return
    if s['name'] == '':
        if s['data'].startswith('ds'):
            if len(s['data']) > 2:
                if s['data'][3:].startswith('$'):
                    n = int(s['data'][4:], '16')
                else:
                    n = int(s['data'][3:])
            else:
                n = 1
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
            if len(data) > 2:
                size = int(data[3:])
            else:
                size = 1
        else:
            size = 0
        res = {'type': 'field', 'pos': asmPos, 'name': s['name'], 'size': size}
        print(f'{data} {s["name"]}')
        asmPos += size 
        spos += 1
        return res

@dataclass
class SectionData:
    align: int
    org: int

banks = [
    [
        "Stack",
        "Audio RAM",
        "WRAM",
        # align 8
        "wSpriteAnims",
        # align 8
        "Sprites",
        "Tilemap",
        "Miscellaneous",
        "Unused Map Buffer",
        # align 8
        "Overworld Map",
        # align 4
        "Video",
    ], 
# WRAMX 1
    [
        "WRAM 1",
        "Miscellaneous WRAM 1",
        "More WRAM 1",
        "Enemy Party",
        "Party",
    ],
# WRAMX 2
    [
        "Pic Animations"
    ],
# WRAMX 3
    [
        "Battle Tower RAM"
    ],
# WRAMX 4
    [], # empty
# WRAMX 5
    [
        # align 8
        "GBC Video",
        # org $d300
        "Battle Animations",
        # org $d800
        "Mobile RAM",
    ],
# WRAMX 6
    [
        "Scratch RAM"
    ],
# WRAMX 7
    [
        "Stack RAM",
    ]
]

section_data = {
    'wSpriteAnims': SectionData(8, 0), #align 8, .org auto
    'Sprites': SectionData(8, 0), #align 8, .org auto
    'Overworld Map': SectionData(8, 0), #align 8, .org auto
    'Video': SectionData(4, 0), #align 4, .org auto
    'GBC Video': SectionData(8, 0), #align 8, .org auto
    'Battle Animations': SectionData(1, 0xd300), #align 1, .org $d300
}

section_padding = {
    'WRAM': 1,
    'Overworld Map': 12,
    'GBC Video': 0x70,
    'Battle Animations': 0x39E,
}

mapped_fields = {
    'wChannel': 'wChannel1',
    'wSpriteAnim': 'wSpriteAnim1',
    'wVirtualOAMSprite': 'wVirtualOAMSprite00',
    'wLinkPlayerPartyMon': 'wLinkPlayerPartyMon1',
    'wLinkPlayerPartyMonOT': 'wLinkPlayerPartyMon1OT',
    'wLinkPlayerPartyMonNickname': 'wLinkPlayerPartyMon1Nickname',
    'wTimeCapsulePartyMon': 'wTimeCapsulePartyMon1',
    'wTimeCapsulePartyMonOT': 'wTimeCapsulePartyMon1OT',
    'wTimeCapsulePartyMonNickname': 'wTimeCapsulePartyMon1Nickname',
    'wLinkOTPartyMonType': 'wLinkOTPartyMon1Type',
    'wOTPartyMon': 'wOTPartyMon1',
    'wOTPartyMonOT': 'wOTPartyMon1OT',
    'wOTPartyMonNickname': 'wOTPartyMon1Nickname',
    'wObjectStruct': 'wObjectStruct1',
    'wMapObject': 'wMapObject1',
    'wPartyMon': 'wPartyMon1',
    'wPartyMonOT': 'wPartyMon1OT',
    'wPartyMonNickname': 'wPartyMon1Nickname',
    'wAnimObject': 'wAnimObject1',
    'wBGEffect': 'wBGEffect1',
}

asm_struct_to_c = {
    'box_struct': 'struct BoxMon',
    'battle_tower_struct': 'struct BattleTowerData',
    'channel_struct': 'struct Channel_',
    'party_struct': 'struct PartyMon',
    'move_struct': 'struct Move',
    'battle_struct': 'struct BattleMon',
    'roam_struct': 'struct Roamer',
    'slot_reel': 'struct SlotReel',
    'object_struct': 'struct Object',
    'map_connection_struct': 'struct MapConnection',
    'bugcontestwinner': 'struct BugContestWinner',
    'sprite_anim_struct': 'struct SpriteAnim',
    'sprite_oam_struct': 'struct SpriteOAM',
    'hall_of_fame': 'struct HallOfFameData',
    'map_object': 'struct MapObject',
    'trademon': 'struct TradeMon',
    'red_party_struct': 'struct RedPartyMon',
    'battle_anim_struct': 'struct BattleAnim',
    'battle_bg_effect': 'struct BattleBGEffect',
}

sections = {}
curr_section = None
curr_union = []
curr_union_index = 0
curr_skip_index = 0

def parse_expr_unit(tokens: List[Dict[str, str]]):
    if tokens[0]['type'] == 'num':
        return tokens[0], tokens[1:]
    if tokens[0]['type'] == 'ident':
        return tokens[0], tokens[1:]
    if tokens[0]['value'] == '(':
        expr, tokens = parse_expr(tokens[1:])
        expr['paren'] = True
        return expr, tokens[1:]
    return None, tokens

def parse_expr(tokens: List[Dict[str, str]]):
    lhs, tokens = parse_expr_unit(tokens)
    if lhs is not None:
        if tokens[0]['type'] == 'op':
            while tokens[0]['type'] == 'op' and tokens[0]['value'] not in (',', ')'):
                op = tokens[0]
                rhs, tokens = parse_expr_unit(tokens[1:])
                ex = {'type': 'binop', 'lhs': lhs, 'rhs': rhs, 'op': op}
                lhs = ex
        return lhs, tokens
    return None, tokens


def parse_tokens(tokens: List[Dict[str, str]]):
    global curr_section
    global curr_union
    global curr_skip_index
    def convert_expr_to_cexpr(value):
        print(value)
        if value is None:
            return 'null'
        if value['type'] == 'ident':
            return value['value']
        if value['type'] == 'num':
            if value['value'].startswith('$'):
                return '0x' + value['value'][1:]
            else:
                return value['value']
        elif value['type'] == 'binop':
            if 'paren' in value.keys():
                return '({} {} {})'.format(convert_expr_to_cexpr(value['lhs']), value['op']['value'], convert_expr_to_cexpr(value['rhs']))
            return '{} {} {}'.format(convert_expr_to_cexpr(value['lhs']), value['op']['value'], convert_expr_to_cexpr(value['rhs']))
        return value

    while len(tokens) > 0:
        if tokens[0]['type'] == 'comment':
            curr_section.append(tokens[0])
            tokens = tokens[1:]
            continue
        elif tokens[0]['type'] == 'cmd':
            if tokens[0]['value'] == 'SECTION':
                if tokens[1]['type'] == 'string':
                    sectname = tokens[1]['value'][1:-1]
                    print('Section', sectname)
                    if sectname not in sections.keys():
                        sections[sectname] = []
                    curr_section = sections[sectname]
                    tokens = tokens[3:]
                    continue
                elif tokens[1]['value'] == 'UNION':
                    sectname = tokens[2]['value'][1:-1]
                    print('Section Union', sectname)
                    if sectname not in sections.keys():
                        sections[sectname] = [{'type': 'union', 'sections': [[]], 'parent': None}]
                        sections[sectname][0]['parent'] = sections[sectname]
                    else:
                        sections[sectname][0]['sections'].append([])
                    curr_section = sections[sectname][0]['sections'][-1]
                    tokens = tokens[4:]
                    continue
            elif tokens[0]['value'] == 'UNION':
                curr_union.append({'type': 'union', 'sections': [[]], 'parent': curr_section})
                curr_section.append(curr_union[-1])
                curr_section = curr_union[-1]['sections'][-1]
                tokens = tokens[1:]
                continue
            elif tokens[0]['value'] == 'NEXTU':
                curr_union[-1]['sections'].append([])
                curr_section = curr_union[-1]['sections'][-1]
                tokens = tokens[1:]
                continue
            elif tokens[0]['value'] == 'ENDU':
                curr_section = curr_union[-1]['parent']
                curr_union = curr_union[:-1]
                tokens = tokens[1:]
                continue
            elif tokens[0]['value'] == 'for':
                print('For')
                stop = None
                var, tokens = parse_expr(tokens[1:])
                tokens = tokens[1:]
                start, tokens = parse_expr(tokens)
                if tokens[0]['value'] == ',':
                    tokens = tokens[1:]
                    stop, tokens = parse_expr(tokens)
                    curr_section.append({'type': 'comment', 'value': '; for {}, {}, {}'.format(
                        convert_expr_to_cexpr(var),
                        convert_expr_to_cexpr(start),
                        convert_expr_to_cexpr(stop),
                    )})
                else:
                    curr_section.append({'type': 'comment', 'value': '; for {}, {}'.format(
                        convert_expr_to_cexpr(var),
                        convert_expr_to_cexpr(start)
                    )})
                while tokens[0]['type'] != 'cmd' and tokens[0]['value'] != 'endr':
                    if tokens[0]['type'] == 'comment':
                        curr_section.append(tokens[0])
                        tokens = tokens[1:]
                        continue
                    if tokens[0]['type'] == 'ident':
                        fname = tokens[0]['value']
                        tokens = tokens[1:]
                        while tokens[0]['value'] != '::':
                            if tokens[0]['value'] == 'endr':
                                break
                            if tokens[0]['value'] == '{':
                                while tokens[0]["value"] != '}':
                                    tokens = tokens[1:]
                                tokens = tokens[1:]
                            if tokens[0]['value'] == '::':
                                break
                            fname += tokens[0]['value'] if tokens[0]['value'] not in ('{', '}', ':') else ''
                            tokens = tokens[1:]
                        if tokens[0]['value'] == '::':
                            tokens = tokens[1:]
                            if tokens[0]['value'] in asm_struct_to_c.keys():
                                ftype = asm_struct_to_c[tokens[0]['value']]
                                if stop is not None:
                                    curr_section.append({'type': 'field', 'name': fname, 'ftype': ftype + '[({}) - {}]'.format(
                                        convert_expr_to_cexpr(stop),
                                        convert_expr_to_cexpr(start)
                                    ), 'comments': comments})
                                else:
                                    curr_section.append({'type': 'field', 'name': fname, 'ftype': ftype + '[{}]'.format(
                                        convert_expr_to_cexpr(start)
                                    ), 'comments': comments})
                                tokens = tokens[2:]
                                if tokens[0]['value'] == '{':
                                    while tokens[0]["value"] != '}':
                                        tokens = tokens[1:]
                                    tokens = tokens[1:]
                                continue
                            elif tokens[0]['value'] == 'ds':
                                value, tokens = parse_expr(tokens[1:])
                                if stop is not None:
                                    curr_section.append({'type': 'field', 'name': fname, 'ftype': 'uint8_t[({}) - {}][{}]'.format(
                                        convert_expr_to_cexpr(stop),
                                        convert_expr_to_cexpr(start),
                                        convert_expr_to_cexpr(value)
                                    ), 'comments': []})
                                else:
                                    curr_section.append({'type': 'field', 'name': fname, 'ftype': 'uint8_t[{}][{}]'.format(
                                        convert_expr_to_cexpr(start),
                                        convert_expr_to_cexpr(value)
                                    ), 'comments': []})
                                continue
                            elif tokens[0]['value'] == 'dw':
                                curr_section.append({'type': 'field', 'name': fname, 'ftype': 'uint16_t', 'comments': []})
                                tokens = tokens[1:]
                                continue
                            else:
                                curr_section.append({'type': 'comment', 'value': '; {}'.format(tokens[0]['value'])})
                                tokens = tokens[1:]
                                continue
                        else:
                            curr_section.append({'type': 'comment', 'value': '; {}'.format(tokens[0]['value'])})
                            tokens = tokens[1:]
                            continue
                    curr_section.append({'type': 'comment', 'value': '; {}'.format(tokens[0]['value'])})
                    tokens = tokens[1:]
                tokens = tokens[1:]
                continue
            elif tokens[0]['value'] == 'db':
                curr_section.append({'type': 'comment', 'value': '; {}'.format(tokens[0]['value'])})
                tokens = tokens[1:]
                continue
            elif tokens[0]['value'] == 'ds':
                value, tokens = parse_expr(tokens[1:])
                curr_section.append({'type': 'skip', 'name': '', 'ftype': 'uint8_t[{}]'.format(convert_expr_to_cexpr(value)), 'comments': []})
                continue
            else:
                curr_section.append({'type': 'comment', 'value': '; {}'.format(tokens[0]['value'])})
                tokens = tokens[1:]
                continue
        elif tokens[0]['type'] == 'ident':
            if tokens[0]['value'] == 'INCLUDE':
                tokens = tokens[2:]
                continue
            if tokens[1]['type'] == 'op' and tokens[1]['value'] == '::':
                comments = []
                fname = tokens[0]['value']
                tokens = tokens[2:]
                while tokens[0]['type'] == 'comment':
                    comments.append(tokens[0])
                    tokens = tokens[1:]
                if tokens[0]['type'] == 'cmd':
                    if tokens[0]['value'] == 'db':
                        curr_section.append({'type': 'field', 'name': fname, 'ftype': 'uint8_t', 'comments': comments})
                        tokens = tokens[1:]
                        continue
                    elif tokens[0]['value'] == 'dw':
                        curr_section.append({'type': 'field', 'name': fname, 'ftype': 'uint16_t', 'comments': comments})
                        tokens = tokens[1:]
                        continue
                    elif tokens[0]['value'] == 'ds':
                        value, tokens = parse_expr(tokens[1:])
                        curr_section.append({'type': 'field', 'name': fname, 'ftype': 'uint8_t[{}]'.format(convert_expr_to_cexpr(value)), 'comments': comments})
                        continue
                    elif tokens[0]['value'] == 'flag_array':
                        value, tokens = parse_expr(tokens[1:])
                        curr_section.append({'type': 'field', 'name': fname, 'ftype': 'uint8_t[(({}) + 7) / 8]'.format(convert_expr_to_cexpr(value)), 'comments': comments})
                        continue
                    elif tokens[0]['value'] == 'for':
                        curr_section.append({'type': 'field', 'name': fname, 'ftype': 'union', 'comments': comments})
                        continue
                    else:
                        curr_section.append({'type': 'field', 'name': fname, 'ftype': 'void', 'comments': comments})
                        continue
                elif tokens[0]['value'] in asm_struct_to_c.keys():
                    ftype = asm_struct_to_c[tokens[0]['value']]
                    curr_section.append({'type': 'field', 'name': fname, 'ftype': ftype, 'comments': comments})
                    tokens = tokens[2:]
                    continue
                else:
                    curr_section.append({'type': 'field', 'name': fname, 'ftype': 'union', 'comments': comments})
                    continue
        curr_section.append({'type': 'comment', 'value': '; {}'.format(tokens[0]['value'])})
        tokens = tokens[1:]
        continue


def read_asm():
    global wramAsmFile
    global wramHFile
    global asmPos
    global spos
    global output
    with open(wramAsmFile, "r", encoding="utf8") as inFile:
        asmFile = inFile.read().split("\n")
    
    token_types = ['comment', 'num', 'cmd', 'ident', 'op', 'string']
    tokens = []
    for line in asmFile[1:]:
        t = exprs.findall(line)
        for tk in t:
            i = 0
            while i < len(tk) and tk[i] == '':
                i += 1
            tokens.append({'type': token_types[i], 'value': tk[i]})

    parse_tokens(tokens)

    def print_element(el, tb = 0):
        global curr_skip_index
        s = ''
        if el['type'] == 'field':
            for comment in el['comments']:
                 s += (tab * tb) + '//{}\n'.format(comment['value'][1:])
            if el['ftype'] in ('union', 'void'):
                s += (tab * tb) + '//{} {}\n'.format(el['ftype'], el['name'])
                return s
            array_size = el['ftype'][el['ftype'].find('[')+1:-1] if '[' in el['ftype'] else ''
            if array_size == '':
                s += (tab * tb) + '{} {};\n'.format(el['ftype'], el['name'])
            else:
                s += (tab * tb) + '{} {}[{}];\n'.format(el['ftype'][:el['ftype'].find('[')], el['name'], array_size)
            return s
        elif el['type'] == 'skip':
            array_size = el['ftype'][el['ftype'].find('[')+1:-1] if '[' in el['ftype'] else ''
            s += (tab * tb) + '{} skip_{}[{}];\n'.format(el['ftype'][:el['ftype'].find('[')], curr_skip_index, array_size)
            curr_skip_index += 1
            return s
        elif el['type'] == 'union':
            s += (tab * tb) + 'union {\n'
            for sect in el['sections']:
                s += (tab * (tb + 1)) + 'struct PACKED {\n'
                for e in sect:
                    s += print_element(e, tb + 2)
                s += (tab * (tb + 1)) + '};\n'
            s += (tab * tb) + '};\n'
            return s
        elif el['type'] == 'comment':
            s += (tab * tb) + '//{}\n'.format(el['value'][1:])
            return s
        return '\n'
    
    def print_celement(el, bank, tb = 0):
        global curr_skip_index
        c = ''
        if el['type'] == 'field' and el['ftype'] not in ('union', 'void'):
            if el['name'] not in mapped_fields.keys():
                if bank == 0:
                    c += 'check_wram0_field({});\n'.format(el['name'])
                else:
                    c += 'check_wramx_field({}, {});\n'.format(el['name'], bank)
            else:
                if bank == 0:
                    c += 'check_wram0_field_mapped({}, {});\n'.format(el['name'], mapped_fields[el['name']])
                else:
                    c += 'check_wramx_field_mapped({}, {}, {});\n'.format(el['name'], bank, mapped_fields[el['name']])
            return c
        elif el['type'] == 'union':
            for sect in el['sections']:
                for e in sect:
                    c += print_celement(e, bank, tb + 2)
            return c
        return ''

    s = ''
    c = ''
    pad_count = 0
    for bankn, bank in enumerate(banks):
        c += '// bank {}\n'.format(bankn)
        s += tab + '// bank {}\n'.format(bankn)
        s += tab + 'union {\n'
        s += (tab*2) + 'uint8_t wram{}[0x1000];\n'.format(bankn)
        s += (tab*2) + 'struct PACKED {\n'
        for sect in bank:
            if sect not in sections:
                continue
            print(sections[sect])
            c += '// section {}\n'.format(sect)
            s += (tab*3) + '// {}\n'.format(sect)
            align = 1
            if sect in section_data.keys():
                if section_data[sect].align != 1:
                    align = section_data[sect].align
            s += (tab*3) + 'struct PACKED {\n'
            for v in sections[sect]:
                s += print_element(v, 4)
                c += print_celement(v, bankn, 0)
            s += (tab*3) + '};\n'
            if sect in section_padding.keys():
                s += (tab*3) + 'uint8_t section_pad_{}[{}]; // Padding for {}\n'.format(pad_count, section_padding[sect], sect)
        s += (tab*2) + '};\n'
        s += tab + '};\n'
    
    out = """#pragma once
#include "constants.h"

#if defined(__cplusplus) || defined(_MSC_VER)
#define PACKED 
#else
#define PACKED __attribute__((packed))
#endif

// A struct representing WRAM.
struct PACKED wram_s
{
"""
    out += s
    out += '};\n'

    with open(wramHFile, "w", encoding="utf8") as outFile:
        outFile.write(out)

    outc = '''#include "wram.h"

#if defined(__cplusplus) || defined(_MSC_VER)
#define check_wram0_field(_fld) static_assert(offsetof(struct wram_s, _fld) == (_fld - WRAM_0_ADDR), "")
#define check_wramx_field(_fld, _bank) static_assert(offsetof(struct wram_s, _fld) - (0x1000 * (_bank)) == (_fld - WRAM_1_ADDR), "")

#define check_wram0_field_mapped(_fld, _wvar) static_assert(offsetof(struct wram_s, _fld) == (_wvar - WRAM_0_ADDR), "")
#define check_wramx_field_mapped(_fld, _bank, _wvar) static_assert(offsetof(struct wram_s, _fld) - (0x1000 * (_bank)) == (_wvar - WRAM_1_ADDR), "")
#else
#define check_wram0_field(_fld) _Static_assert(offsetof(struct wram_s, _fld) == (_fld - WRAM_0_ADDR), "")
#define check_wramx_field(_fld, _bank) _Static_assert(offsetof(struct wram_s, _fld) - (0x1000 * (_bank)) == (_fld - WRAM_1_ADDR), "")

#define check_wram0_field_mapped(_fld, _wvar) _Static_assert(offsetof(struct wram_s, _fld) == (_wvar - WRAM_0_ADDR), "")
#define check_wramx_field_mapped(_fld, _bank, _wvar) _Static_assert(offsetof(struct wram_s, _fld) - (0x1000 * (_bank)) == (_wvar - WRAM_1_ADDR), "")
#endif

'''
    outc += c

    with open(wramCFile, "w", encoding="utf8") as outFile:
        outFile.write(outc)
    
    exit(0)
    
    slist = [parse_line(line) for line in asmFile]
    output = {}
    flds = []

    print(slist)

    while spos < len(slist):
        seg = read_asm_segment(slist)
        if seg is not None:
            if seg['pos'] not in output.keys():
                output[seg['pos']] = []
            output[seg['pos']].append(seg)
    
    exit(0)

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
    
    with open(wramHFile, "w", encoding="utf8") as outFile:
        outFile.write(out)

if __name__ == '__main__':
    read_asm()