#!/usr/bin/env python3
import argparse
import time
import os
import json
from typing import Any, Dict, List, Union
from dataclasses import dataclass

tab = "    "
toolDir = os.path.dirname(os.path.realpath(__file__))
dataDir = f"{toolDir}/../data"
partyASMFile = f"{dataDir}/trainers/parties.asm"
partyJSONFile = f"{dataDir}/trainers/parties.json"
partyCFile = f"{dataDir}/trainers/parties.c"

CBegin = '''#include "../../constants.h"

'''

@dataclass
class MonNormal:
    species: str 
    level: int 

@dataclass
class MonItem:
    species: str 
    level: int 
    item: str

@dataclass
class MonMoves:
    species: str 
    level: int 
    moves: List[str]

@dataclass
class MonItemMoves:
    species: str 
    level: int 
    item: str
    moves: List[str]

@dataclass
class Party:
    name: str 
    ptype: str 
    mons: List[Union[MonNormal, MonItem, MonMoves]]

@dataclass 
class Group:
    name: str 
    parties: List[Party]


def print_trainer_group(group: Group):
    print(f'{tab}{group.name}:')
    for party in group.parties:
        print(f'{tab * 2}{party.name} {party.ptype}')
        if party.ptype == 'MOVES':
            for mon in party.mons:
                print(f'{tab * 3}{mon.level:02d} {mon.species}', end=' ')
                print(*mon.moves, sep=', ')
        elif party.ptype == 'NORMAL':
            for mon in party.mons:
                print(f'{tab * 3}{mon.level:02d} {mon.species}')
        elif party.ptype == 'ITEM':
            for mon in party.mons:
                print(f'{tab * 3}{mon.level:02d} {mon.species} {mon.item}')
        elif party.ptype == 'ITEM_MOVES':
            for mon in party.mons:
                print(f'{tab * 3}{mon.level:02d} {mon.species} {mon.item}')
                print(*mon.moves, sep=', ')

def asm2json():
    with open(partyASMFile) as f:
        asm = f.read()

    lines = asm.splitlines()

    curr_group: Group = None
    curr_party: Party = None

    groups: List[Group] = []

    for line in lines:
        if line.startswith('INCLUDE'):
            continue
        if line.startswith(';'):
            # print('//' + line[1:])
            continue
        line = line.strip()
        if line.startswith(';'):
            # print(tab, '//' + line[1:])
            continue
        elif line.endswith('Group:'):
            # print('TrainerGroup', line[:line.rfind('Group:')])
            if curr_group is not None:
                groups.append(curr_group)
            curr_group = Group(line[:line.rfind('Group:')] + 'Group', [])
            continue
        elif line.startswith('db'):
            data = line[3:].split(',')
            # print(*data, sep=',')
            if data[0].startswith('"'):
                if curr_party is not None:
                    curr_group.parties.append(curr_party)
                curr_party = Party(data[0][1:data[0].rfind('"')], data[1][data[1].find('_') + 1:].rstrip(), [])
                # print(curr_party.name, curr_party.ptype)
            elif data[0].startswith('-1'):
                curr_group.parties.append(curr_party)
                curr_party = None
            else:
                level = int(data[0])
                species = data[1].strip()
                if curr_party.ptype == 'MOVES':
                    moves = [mv.strip() for mv in data[2:]]
                    curr_party.mons.append(MonMoves(species, level, moves))
                elif curr_party.ptype == 'NORMAL':
                    curr_party.mons.append(MonNormal(species, level))
                elif curr_party.ptype == 'ITEM':
                    curr_party.mons.append(MonItem(species, level, data[2].strip()))
                elif curr_party.ptype == 'ITEM_MOVES':
                    item = data[2].strip()
                    moves = [mv.strip() for mv in data[3:]]
                    curr_party.mons.append(MonItemMoves(species, level, item, moves))
        elif line.startswith('Trainers:'):
            continue
        else:
            pass
            # print(line)
    d = []

    for group in groups:
        dparties = []
        for party in group.parties:
            dparty = {'name': party.name, 'type': party.ptype}
            dmons = []
            for mon in party.mons:
                dmon = {'lvl': mon.level, 'species': mon.species}
                if party.ptype == 'ITEM' or party.ptype == 'ITEM_MOVES':
                    dmon['item'] = mon.item
                if party.ptype == 'MOVES' or party.ptype == 'ITEM_MOVES':
                    dmon['moves'] = mon.moves
                dmons.append(dmon)
            dparty['party'] = dmons
            dparties.append(dparty)
        d.append({'name': group.name, 'parties': dparties})

    with open(partyJSONFile, mode='w', encoding='utf8') as f:
        json.dump(d, f, indent=4)


def trainer_group_to_c(group: Group):
    out = f'const struct TrainerParty {group.name}[]'
    out += ' = {'
    if len(group.parties) == 0:
        out += '};\n'
        return out
    out += '\n'
    for party in group.parties:
        if party.ptype == 'NORMAL':
            out += f'{tab}{{"{party.name}", TRAINERTYPE_{party.ptype}, .size={len(party.mons)}, .pnormal=(struct TrainerPartyNormal[]){{\n'
            for i, mon in enumerate(party.mons):
                out += f'{tab*2}{{.level={mon.level}, .species={mon.species}}}'
                if i < len(party.mons) - 1:
                    out += ','
                out += '\n'
            out += f'{tab}}}}},\n'
        elif party.ptype == 'ITEM':
            out += f'{tab}{{"{party.name}", TRAINERTYPE_{party.ptype}, .size={len(party.mons)}, .pitem=(struct TrainerPartyItem[]){{\n'
            for i, mon in enumerate(party.mons):
                out += f'{tab*2}{{.level={mon.level}, .species={mon.species}, .item={mon.item}}}'
                if i < len(party.mons) - 1:
                    out += ','
                out += '\n'
            out += f'{tab}}}}},\n'
        elif party.ptype == 'MOVES':
            out += f'{tab}{{"{party.name}", TRAINERTYPE_{party.ptype}, .size={len(party.mons)}, .pmoves=(struct TrainerPartyMoves[]){{\n'
            for i, mon in enumerate(party.mons):
                out += f'{tab*2}{{.level={mon.level}, .species={mon.species}, .moves={{'
                for j, mv in enumerate(mon.moves):
                    out += f'{mv}'
                    if j < len(mon.moves) - 1:
                        out += ', '
                out += f'}}}}'
                if i < len(party.mons) - 1:
                    out += ','
                out += '\n'
            out += f'{tab}}}}},\n'
        elif party.ptype == 'ITEM_MOVES':
            out += f'{tab}{{"{party.name}", TRAINERTYPE_{party.ptype}, .size={len(party.mons)}, .pitemmoves=(struct TrainerPartyItemMoves[]){{\n'
            for i, mon in enumerate(party.mons):
                out += f'{tab*2}{{.level={mon.level}, .species={mon.species}, .item={mon.item}, .moves={{'
                for j, mv in enumerate(mon.moves):
                    out += f'{mv}'
                    if j < len(mon.moves) - 1:
                        out += ', '
                out += f'}}}}'
                if i < len(party.mons) - 1:
                    out += ','
                out += '\n'
            out += f'{tab}}}}},\n'
    out += '};\n'
    return out

def json2c():
    with open(partyJSONFile) as f:
        d: list = json.load(f)

    group_names = []
    groups = {}

    out = ''

    for dgroup in d:
        group_names.append(dgroup['name'])
        group: Group = Group(dgroup['name'], [])
        for i, party in enumerate(dgroup['parties']):
            mons: List[Union[MonNormal, MonItem, MonMoves]] = []
            if len(party['party']) > 6:
                print("Invalid number of pokemon. There should be between 1 and 6 Pokemon for each party.")
                print(dgroup['name'], f'party {i}')
                exit(-1)
            if party['type'] == 'MOVES':
                for j, mon in enumerate(party['party']):
                    if len(mon['moves']) == 0 or len(mon['moves']) > 4:
                        print("Invalid number of moves on pokemon. There should be between 1 and 4 moves on each Pokemon.")
                        print(dgroup['name'], f'party {i}', f'mon {j}')
                        exit(-1)
                    if len(mon['moves']) < 4:
                        mon['moves'].extend(['NO_MOVE'] * (4 - len(mon['moves'])))
                    mons.append(MonMoves(mon['species'], mon['lvl'], mon['moves']))
            elif party['type'] == 'NORMAL':
                for mon in party['party']:
                    mons.append(MonNormal(mon['species'], mon['lvl']))
            elif party['type'] == 'ITEM':
                for mon in party['party']:
                    mons.append(MonItem(mon['species'], mon['lvl'], mon['item']))
            elif party['type'] == 'ITEM_MOVES':
                for j, mon in enumerate(party['party']):
                    if len(mon['moves']) == 0 or len(mon['moves']) > 4:
                        print("Invalid number of moves on pokemon. There should be between 1 and 4 moves on each Pokemon.")
                        print(dgroup['name'], f'party {i}', f'mon {j}')
                        exit(-1)
                    if len(mon['moves']) < 4:
                        mon['moves'].extend(['NO_MOVE'] * (4 - len(mon['moves'])))
                    mons.append(MonItemMoves(mon['species'], mon['lvl'], mon['item'], mon['moves']))
            group.parties.append(Party(party['name'], party['type'], mons))
        groups[group.name] = group

    out = ''
    out2 = 'const struct TrainerParty* TrainerGroups[] = {\n'

    for group in groups.values():
        out += trainer_group_to_c(group) + '\n'
        out2 += f'{tab}{group.name},\n'
    
    out2 += '};\n'

    with open(partyCFile, mode='w', encoding='utf8') as f:
        f.write(CBegin + out + out2)

json2c()