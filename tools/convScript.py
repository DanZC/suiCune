from dataclasses import dataclass
from typing import List, Union
import sys

@dataclass
class Cmd:
    name: str
    args: list

@dataclass
class SubCmd:
    name: str
    term: bool

commands = {
    'special': Cmd('special', ['id']),
    'promptbutton': Cmd('promptbutton', []),
    'waitbutton': Cmd('waitbutton', []),
    'playsound': Cmd('playsound', ['sfx']),
    'waitsfx': Cmd('waitsfx', []),
    'playmusic': Cmd('playmusic', ['music']),
    'setevent': Cmd('setevent', ['event']),
    'checkevent': Cmd('checkevent', ['event']),
    'clearevent': Cmd('clearevent', ['event']),
    'setscene': Cmd('setscene', ['scene']),
    'setmapscene': Cmd('setmapscene', ['map', 'scene']),
    'setval': Cmd('setval', ['value']),
    'addval': Cmd('addval', ['value']),
    'readvar': Cmd('readvar', ['var']),
    'end': Cmd("s_end", []),
    'checkflag': Cmd('checkflag', ['flag']),
    'setflag': Cmd('setflag', ['flag']),
    'clearflag': Cmd('clearflag', ['flag']),
    'sjump': Cmd('sjump', ['dest']),
    'farsjump': Cmd('sjump', ['dest']),
    'scall': Cmd('scall', ['dest']),
    'farscall': Cmd('scall', ['dest']),
    'ifless': Cmd('ifless_jump', ['dest']),
    'iftrue': Cmd('iftrue_jump', ['dest']),
    'iffalse': Cmd('iffalse_jump', ['dest']),
    'ifequal': Cmd('ifequal_jump', ['value', 'dest']),
    'ifnotequal': Cmd('ifnotequal_jump', ['value', 'dest']),
    'readvar': Cmd('readvar', ['value']),
    'farwritetext': Cmd('writetext', ['text']),
    'writetext': Cmd('writetext', ['text']),
    'jumptext': Cmd('jumptext', ['text']),
    'farjumptext': Cmd('jumptext', ['text']),
    'opentext': Cmd('opentext', []),
    'closetext': Cmd('closetext', []),
    'faceplayer': Cmd('faceplayer', []),
    'trainer': Cmd('trainer', ['unk']),
    'jumpstd': Cmd('jumpstd', ['std']),
    'callstd': Cmd('callstd', ['std']),
    'pause': Cmd('pause', ['n']),
    'wait': Cmd('wait', []),
    'checktime': Cmd('checktime', ['tod']),
    'specialphonecall': Cmd('specialphonecall', ['id']),
    'checkphonecall': Cmd('checkphonecall', []),
    'endcallback': Cmd('s_endcallback', []),
    'getcurlandmarkname': Cmd('getcurlandmarkname', []),
    'getlandmarkname': Cmd('getlandmarkname', ['buffer', 'landmark_id']),
    'gettrainername': Cmd('gettrainername', ['buffer', 'trainer_class', 'trainer_id']),
    'getmonname': Cmd('getmonname', ['buffer', 'mon_id']),
    'getstring': Cmd('getstring', ['buffer', 'str']),
    'random': Cmd('srandom', ['val']),
}

text_commands = {
    'text': Cmd('text_start', ['str']),
    'text_ram': Cmd('text_ram', ['wram_ptr']),
    'text_start': Cmd('text_start', ['str']),
    'text_end': Cmd('text_end', []),
    'text_promptbutton': Cmd('text_promptbutton', [])
}

mvmt_commands = {
    'step': Cmd('step', ['dir']),
    'big_step': Cmd('big_step', ['dir']),
    'turn_head': Cmd('turn_head', ['dir']),
    'step_end': Cmd('movement_step_end', []),
}

text_sub_commands = {
    'para': SubCmd('t_para', False),
    'line': SubCmd('t_line', False),
    'cont': SubCmd('t_cont', False),
    'done': SubCmd('t_done', True),
    'prompt': SubCmd('t_prompt', True),
}

term = ['sjump', 'farsjump', 'end', 'jumpstd', 'jumptext', 'farjumptext', 'endcallback']

@dataclass
class Comment:
    value: str
    local: bool

@dataclass
class StrLabel:
    name: str
    value: str
    comment: str

@dataclass
class Label:
    name: str
    comment: str
    local: bool

@dataclass
class Command:
    name: str
    args: List[str]
    comment: str

def format_arg(arg: str):
    if arg.startswith('$'):
        return f'0x{arg[1:]}'
    return arg

def parse_string(line: str, start: int):
    for i in range(start, len(line)):
        if line[i] != '\"':
            continue
        return i


def split_args(line: str):
    args = []
    a = 0
    i = 0
    while i < len(line):
        if line[i] == '\"':
            i = parse_string(line, i + 1)
            i += 1
            continue
        if line[i] == ',':
            args.append(line[a:i].strip())
            a = i + 1
            i = a
            continue
        i += 1
    if i > a:
        args.append(line[a:i].strip())
        a = i + 1
        i = a
    return args


def format_command(cmd: str, parts: List[str]):
    print(cmd, parts)
    if cmd in commands.keys():
        if cmd in ['iftrue', 'iffalse']:
            if parts[0].startswith('.'):
                return f"{cmd}({parts[0][1:]})"
            else:
                return f"{cmd}_jump({parts[0]})"
        if cmd in ['ifequal', 'ifnotequal', 'ifless']:
            if parts[1].startswith('.'):
                return f"{cmd}({format_arg(parts[0])}, {parts[1][1:]})"
            else:
                return f"{cmd}_jump({format_arg(parts[0])}, {parts[1]})"
        if cmd == 'sjump' and parts[0].startswith('.'):
            return f"goto {parts[0][1:]};"
        if len(commands[cmd].args) == 0:
            return f"{commands[cmd].name}"
        else:
            s = f"{commands[cmd].name}("
            for part in parts:
                s += f"{format_arg(part)}, "
            s = s[:-2] + ")"
            return s
    elif cmd in text_commands.keys():
        if cmd == 'text':
            if len(parts) > 0:
                return f"text_start({parts[0]}"
            return f"text_start("
        s = f'{text_commands[cmd].name}('
        for part in parts:
            s += f"{format_arg(part)}, "
        s = s[:-2] + ")"
        return s
    elif cmd in text_sub_commands.keys():
        s = f"{text_sub_commands[cmd].name} "
        for part in parts:
            s += part
        if text_sub_commands[cmd].term:
            s += ')'
        return s
    elif cmd in mvmt_commands.keys():
        if len(mvmt_commands[cmd].args) > 0:
            s = f"{mvmt_commands[cmd].name}("
            for part in parts:
                s += f"{format_arg(part)}, "
            s = s[:-2] + "),"
            return s
        else:
            return f'{mvmt_commands[cmd].name},'
    else:
        if len(parts) == 0:
            return f"// {cmd}"
        s = f"// {cmd}("
        for part in parts:
            s += f"{part}, "
        return s[:-2] + ")"
        
    
def begin_script(name: str):
    return f"bool {name}(script_s* s) {{\n    SCRIPT_BEGIN\n"

def end_script():
    return "    SCRIPT_END\n}\n"

def string_label(name: str, value: str):
    return f"const char {name}[] = \"{value}\";\n"

def begin_text(name: str):
    return f"const struct TextCmd {name}[] = {{\n"

def end_text():
    return "};\n"

def begin_movement(name: str):
    return f"const uint8_t {name}[] = {{\n"

def end_movement():
    return "};\n"

def fallthrough_script(name: str):
    return f"    SCRIPT_FALLTHROUGH({name})\n}}\n"

def local_label(name: str):
    return f"{name}:\n"

def do_command(cmd: str, args: List[str], comment: str):
    if comment != '':
        comment = f' //{comment}'
    return '    ' + format_command(cmd, args) + comment + '\n'

def do_text(args: List[str]):
    return '    ' + format_command('text', args) + '\n'

def do_text_sub_command(cmd: str, args: List[str]):
    return '        ' + format_command(cmd, args) + '\n'

def do_text_end():
    return '    )'

def local_comment(comment: str):
    return '    //' + comment + '\n'

def global_comment(comment: str):
    return '//' + comment + '\n'

def parse_inline_label(name: str, after: str, comment: str):
    parts = after.split(' ', maxsplit=1)
    dcmd = parts[0]
    dval = parts[1]
    if dcmd == 'db':
        if dval.startswith('"'):
            sval = dval[dval.find('"')+1:dval.rfind('"')]
            return StrLabel(name, sval, comment)

def parse_line(line: str):
    if line == '':
        return None
    print(line)
    if line.startswith(';'):
        return Comment(line[1:], False)
    if line.startswith('INCLUDE'):
        return Comment(line, False)
    if not line[0].isspace() and line.find(':') != -1:
        parts = line.split(':', maxsplit=1)
        afterpart = parts[1].strip()
        if afterpart.startswith(';') != -1:
            comment = afterpart[1:]
        else:
            comment = None
        if afterpart.startswith('db') or afterpart.startswith('dw'):
            return parse_inline_label(parts[0], afterpart, comment)
        if parts[0].startswith('.'):
            return Label(parts[0], comment, True)
        return Label(parts[0], comment, False)
    if line[0].startswith('.'):
        if line[0].find(';') != -1:
            part = line[0][:line[0].find(';')]
            comment = line[0][line[0].find(';')+1:]
        else:
            comment = None
            part = line.strip()
        return Label(part, comment, True)
    line = line.strip()
    if line.startswith(';'):
        return Comment(line[1:], True)
    if line.find(';') != -1:
        halves = line.split(';', maxsplit=1)
        comment = halves[1]
        line = halves[0]
    else:
        comment = ''
    if line.find(' ') != -1:
        parts = line.split(' ', maxsplit=1)
        cmd = parts[0]
        args = split_args(parts[1])
        for arg in range(len(args)):
            args[arg] = args[arg].strip()
        return Command(cmd, args, comment)
    else:
        return Command(line, [], comment)
    
def find_next_command(script: List[Union[Comment, Label, StrLabel, Command]], i: int):
    for j in range(i, len(script)):
        if isinstance(script[j], Comment):
            continue
        if isinstance(script[j], Command):
            return script[j]
        return None
    return None

with open(sys.argv[1], 'r', encoding='utf8') as f:
    lines = f.read().splitlines()

script: List[Union[Comment, Label, StrLabel, Command]] = []

for line in lines:
    ln = parse_line(line)
    if ln is not None:
        script.append(ln)

# out = '''#include "../../constants.h"
# #include "../../util/scripting_macros.h"
# #include "../../data/text/std_text.h"

# const Script_fn_t StdScripts[] = {
#     PokecenterNurseScript,
#     DifficultBookshelfScript,
#     PictureBookshelfScript,
#     MagazineBookshelfScript,
#     TeamRocketOathScript,
#     IncenseBurnerScript,
#     MerchandiseShelfScript,
#     TownMapScript,
#     WindowScript,
#     TVScript,
#     HomepageScript, // unused
#     Radio1Script,
#     Radio2Script,
#     TrashCanScript,
#     StrengthBoulderScript,
#     SmashRockScript,
#     PokecenterSignScript,
#     MartSignScript,
#     GoldenrodRocketsScript,
#     RadioTowerRocketsScript,
#     ElevatorButtonScript,
#     DayToTextScript,
#     BugContestResultsWarpScript,
#     BugContestResultsScript,
#     InitializeEventsScript,
#     AskNumber1MScript,
#     AskNumber2MScript,
#     RegisteredNumberMScript,
#     NumberAcceptedMScript,
#     NumberDeclinedMScript,
#     PhoneFullMScript,
#     RematchMScript,
#     GiftMScript,
#     PackFullMScript,
#     RematchGiftMScript,
#     AskNumber1FScript,
#     AskNumber2FScript,
#     RegisteredNumberFScript,
#     NumberAcceptedFScript,
#     NumberDeclinedFScript,
#     PhoneFullFScript,
#     RematchFScript,
#     GiftFScript,
#     PackFullFScript,
#     RematchGiftFScript,
#     GymStatue1Script,
#     GymStatue2Script,
#     ReceiveItemScript,
#     ReceiveTogepiEggScript,
#     PCScript,
#     GameCornerCoinVendorScript,
#     HappinessCheckScript,
# };
# '''
# #include "../../util/scripting_macros.h"
out = '#include "../../../constants.h"\n#include "../../../util/scripting_macros.h"\n\n'
out_h = '#pragma once\n'
cur_text = ''
cur_movement = ''
cur_script = ''
in_sub_text = False
last_cmd = ''

for i, ln in enumerate(script):
    if isinstance(ln, Label):
        nxt = find_next_command(script, i+1)
        if nxt is not None:
            if nxt.name == 'text':
                if cur_text != '':
                    out += end_text()
                if cur_script != '':
                    out += end_script()
                if cur_movement != '':
                    out += end_movement()
                cur_script = ''
                cur_text = ln.name
                out += begin_text(ln.name)
                out_h += f"extern const struct TextCmd {ln.name}[];\n"
                continue
            if nxt.name in mvmt_commands.keys():
                if cur_text != '':
                    out += end_text()
                if cur_script != '':
                    out += end_script()
                if cur_movement != '':
                    out += end_movement()
                cur_script = ''
                cur_text = ''
                cur_movement = ln.name
                out += begin_movement(ln.name)
                out_h += f"extern const uint8_t {ln.name}[];\n"
                continue
        if not ln.local:
            if cur_text != '':
                out += end_text()
            if cur_movement != '':
                out += end_movement()
            if cur_script != '':
                if last_cmd in term:
                    out += end_script()
                else:
                    out += fallthrough_script(ln.name)
            cur_movement = ''
            cur_text = ''
            cur_script = ln.name
            out += begin_script(ln.name)
            out_h += f"bool {ln.name}(script_s* s);\n"
            continue
        else:
            out += local_label(ln.name[1:])
            continue
    if isinstance(ln, StrLabel):
        if cur_text != '':
            out += end_text()
        if cur_script != '':
            out += end_script()
        if cur_movement != '':
            out += end_movement()
        cur_movement = ''
        cur_text = ''
        cur_script = ''
        out += string_label(ln.name, ln.value)
    if isinstance(ln, Command):
        if ln.name in ('text', 'text_start'):
            in_sub_text = True
            out += do_text(ln.args)
        elif ln.name in text_sub_commands.keys():
            in_sub_text = True
            out += do_text_sub_command(ln.name, ln.args)
            if text_sub_commands[ln.name].term:
                in_sub_text = False
        else:
            if in_sub_text:
                out = out[:-1] + ')\n'
                in_sub_text = False
            out += do_command(ln.name, ln.args, ln.comment)
            last_cmd = ln.name
    if isinstance(ln, Comment):
        if ln.local:
            out += local_comment(ln.value)
        else:
            out += global_comment(ln.value)

if cur_movement != '':
    out += end_movement()
if cur_text != '':
    out += end_text()
if cur_script != '':
    out += end_script()

with open(sys.argv[1].replace('.asm', '.c'), 'w', encoding='utf8') as f:
    f.write(out)

with open(sys.argv[1].replace('.asm', '.h'), 'w', encoding='utf8') as f:
    f.write(out_h)
