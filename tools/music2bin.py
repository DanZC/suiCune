import sys
import os
import dataclasses
symbols = {}
locations = {}
octave_cmd = 0xd0
note_type_cmd = 0xd8
transpose_cmd = 0xd9
tempo_cmd = 0xda
duty_cycle_cmd = 0xdb
volume_envelope_cmd = 0xdc
pitch_sweep_cmd = 0xdd
duty_cycle_pattern_cmd = 0xde
toggle_sfx_cmd = 0xdf
vibrato_cmd = 0xe1
volume_cmd = 0xe5
pitch_offset_cmd = 0xe6
sfx_priority_on_cmd = 0xec
sfx_priority_off_cmd = 0xed
sfx_toggle_noise_cmd = 0xf0
sound_jump_cmd = 0xfc
sound_loop_cmd = 0xfd
sound_call_cmd = 0xfe
sound_ret_cmd = 0xff
constants = {
    'C_': 1,
    'C#': 2,
    'D_': 3,
    'D#': 4,
    'E_': 5,
    'F_': 6,
    'F#': 7,
    'G_': 8,
    'G#': 9,
    'A_': 10,
    'A#': 11,
    'B_': 12,
    'sound_loop_cmd': sound_loop_cmd
}
offset = 0
chan_cnt = 0
diffing = False

if len(sys.argv) < 2:
    print("Usage: music2bin.py <file>")
    exit(-1)

if len(sys.argv) > 2:
    diffing = True
    difffile = sys.argv[2]

with open(sys.argv[1], 'r') as f:
    text = f.read()

if diffing == True:
    with open(difffile, 'rb') as f:
        diffbin = f.read()

lines = text.splitlines()

def remove_trailing_comment(s: str):
    f = s.find(';')
    if f != -1:
        return s[:f]
    return s

def get_local_symbol_name(name, offset):
    global locations
    while offset > 0 and offset not in locations:
        offset -= 1
    if offset in locations:
        return locations[offset] + name
    return name

def symbol_name(name, offset):
    if is_local_symbol(name):
        return get_local_symbol_name(name, offset)
    return name

def add_local_symbol(name, offset):
    global symbols
    global locations
    key = get_local_symbol_name(name, offset)
    symbols[key] = offset
    return key

def is_local_symbol(name: str):
    return name[0] == '.'

def add_symbol(name, offset):
    global symbols
    global locations
    if is_local_symbol(name):
        return add_local_symbol(name, offset)
    symbols[name] = offset
    locations[offset] = name
    return name

def parse_args(arg_str: str):
    l = []
    args = arg_str.split(',')
    for arg in args:
        arg = arg.strip()
        if arg[0].isnumeric():
            l.append(int(arg, 10))
        elif arg[0] == '-':
            if arg[1].isnumeric():
                l.append(int(arg, 10))
            elif arg[1:] in constants:
                l.append(-constants[arg[1:]])
            else:
                l.append(arg)
        elif arg in constants:
            l.append(constants[arg])
        else:
            l.append(arg)
    return l

class note:
    def __init__(self, pitch, length):
        self.pitch = pitch
        self.length = length
    
    def generate(self, offset):
        return bytearray([(self.pitch << 4) | (self.length - 1)])

    def size(self):
        return 1

class channel_count:
    def __init__(self, count):
        self.count = count
    
    def generate(self, offset):
        global chan_cnt
        chan_cnt = self.count - 1
        return bytearray()

    def size(self):
        return 0

class channel:
    def __init__(self, id, address):
        self.id = id
        self.address = address
    
    def generate(self, offset):
        global chan_cnt
        out = bytearray()
        out.append(((chan_cnt << 2) << 4) | (self.id - 1))
        addr = symbols[symbol_name(self.address, offset)]
        out.extend([addr & 0xff, (addr >> 8) & 0xff])
        chan_cnt = 0
        return out

    def size(self):
        return 3

class rest(note):
    def __init__(self, length):
        super().__init__(0, length)

class drum_note(note):
    def __init__(self, pitch, length):
        super().__init__(pitch, length)

class sound_ret:
    def __init__(self):
        pass

    def generate(self, offset):
        return bytearray([sound_ret_cmd])

    def size(self):
        return 1

class octave:
    def __init__(self, oct):
        self.octave = oct
    
    def generate(self, offset):
        return bytearray([octave_cmd + 8 - self.octave])

    def size(self):
        return 1

class note_type:
    def __init__(self, length, vol=None, env=None):
        self.length = length
        self.volume = vol
        self.env = env
    
    def generate(self, offset):
        out = bytearray([note_type_cmd])
        out.append(self.length)
        if self.volume is not None:
            if self.env < 0:
                out.append((self.volume << 4) | (0b1000 | (self.env * -1)))
            else:
                out.append((self.volume << 4) | (self.env))
        
        assert self.size() == len(out)
        return out

    def size(self):
        if self.volume is not None:
            return 3
        return 2

class drum_speed(note_type):
    def __init__(self, length):
        super().__init__(length)

class transpose:
    def __init__(self, octaves, pitches):
        self.octaves = octaves
        self.pitches = pitches
    
    def generate(self, offset):
        out = bytearray([transpose_cmd])
        out.append((self.octaves << 4) | (self.pitches))
        assert self.size() == len(out)
        return out

    def size(self):
        return 2

class toggle_sfx:
    def __init__(self):
        pass

    def generate(self, offset):
        return bytearray([toggle_sfx_cmd])

    def size(self):
        return 1

class tempo:
    def __init__(self, t):
        self.tempo = t

    def generate(self, offset):
        out = bytearray([tempo_cmd])
        out.extend([(self.tempo >> 8) & 0xff, (self.tempo & 0xff)])
        assert self.size() == len(out)
        return out # da

    def size(self):
        return 3

class duty_cycle:
    def __init__(self, cycle):
        self.cycle = cycle

    def generate(self, offset):
        return bytearray([duty_cycle_cmd, self.cycle])

    def size(self):
        return 2

class volume_envelope:
    def __init__(self, vol, env):
        self.volume = vol
        self.fade = env
    
    def generate(self, offset):
        out = bytearray([volume_envelope_cmd])
        if self.fade < 0:
            out.append((self.volume << 4) | (0b1000 | (self.fade * -1)))
        else:
            out.append((self.volume << 4) | (self.fade))
        assert self.size() == len(out)
        return out

    def size(self):
        return 2
    
class pitch_sweep:
    def __init__(self, pitch, sweep):
        self.pitch = pitch
        self.sweep = sweep
    
    def generate(self, offset):
        out = bytearray([pitch_sweep_cmd])
        if self.sweep < 0:
            out.append((self.pitch << 4) | (0b1000 | (self.sweep * -1)))
        else:
            out.append((self.pitch << 4) | (self.sweep))
        assert self.size() == len(out)
        return out

    def size(self):
        return 2
    
class duty_cycle_pattern:
    def __init__(self, a, b, c, d) -> None:
        self.a = a
        self.b = b
        self.c = c
        self.d = d
    
    def generate(self, offset):
        out = bytearray([duty_cycle_pattern_cmd])
        out.append((self.a << 6) | (self.b << 4) | (self.c << 2) | (self.d << 0))
        assert self.size() == len(out)
        return out

    def size(self):
        return 2

class vibrato:
    def __init__(self, delay, extent, rate=None) -> None:
        self.delay = delay
        self.extent = extent
        self.rate = rate
    
    def generate(self, offset):
        out = bytearray([vibrato_cmd])
        out.append(self.delay)
        if self.rate is not None:
            out.append((self.extent << 4) | (self.rate))
        else:
            out.append(self.extent)
        assert self.size() == len(out)
        return out

    def size(self):
        return 3
    
class volume:
    def __init__(self, left, right=None) -> None:
        self.left = left
        self.right = right
    
    def generate(self, offset):
        out = bytearray([volume_cmd])
        if self.right is not None:
            out.append((self.left << 4) | (self.right))
        else:
            out.append(self.left)
        assert self.size() == len(out)
        return out

    def size(self):
        return 2
    
class pitch_offset:
    def __init__(self, offset) -> None:
        self.offset = offset
    
    def generate(self, offset):
        out = bytearray([pitch_offset_cmd])
        out.extend([(self.offset >> 8) & 0xff, self.offset & 0xff])
        assert self.size() == len(out)
        return out

    def size(self):
        return 3

class sfx_priority_on:
    def __init__(self):
        pass

    def generate(self, offset):
        return bytearray([sfx_priority_on_cmd])

    def size(self):
        return 1

class sfx_priority_off:
    def __init__(self):
        pass

    def generate(self, offset):
        return bytearray([sfx_priority_off_cmd])

    def size(self):
        return 1
    
class sfx_toggle_noise:
    def __init__(self, kit=None) -> None:
        self.kit = kit
    
    def generate(self, offset):
        out = bytearray([sfx_toggle_noise_cmd])
        if self.kit is not None:
            out.append(self.kit)
        assert self.size() == len(out)
        return out

    def size(self):
        if self.kit is not None:
            return 2
        return 1

class sound_jump:
    def __init__(self, address):
        self.address = address
    
    def generate(self, offset):
        out = bytearray([sound_jump_cmd])
        addr = symbols[symbol_name(self.address, offset)]
        out.extend([addr & 0xff, (addr >> 8) & 0xff])
        assert self.size() == len(out)
        return out

    def size(self):
        return 3

class sound_call:
    def __init__(self, address):
        self.address = address
    
    def generate(self, offset):
        out = bytearray([sound_call_cmd])
        addr = symbols[symbol_name(self.address, offset)]
        # print(f'{symbol_name(self.address, offset)} = 0x{addr:02x}')
        out.extend([addr & 0xff, (addr >> 8) & 0xff])
        assert self.size() == len(out)
        return out

    def size(self):
        return 3

class sound_loop:
    def __init__(self, count, address):
        self.count = count
        self.address = address
    
    def generate(self, offset):
        out = bytearray([0xfd])
        out.append(self.count)
        addr = symbols[symbol_name(self.address, offset)]
        # print(f'{symbol_name(self.address, offset)} = 0x{addr:02x}')
        out.extend([addr & 0xff, (addr >> 8) & 0xff])
        assert self.size() == len(out)
        return out

    def size(self):
        return 4

class square_note:
    def __init__(self, length, volume, fade, freq):
        self.length = length
        self.volume = volume
        self.fade = fade
        self.freq = freq

    def generate(self, offset):
        out = bytearray()
        out.append(self.length)
        if self.fade < 0:
            out.append((self.volume << 4) | (0b1000 | (self.fade * -1)))
        else:
            out.append((self.volume << 4) | (self.fade))
        out.append(self.freq & 0xff)
        out.append((self.freq >> 8) & 0xff)
        assert self.size() == len(out)
        return out

    def size(self):
        return 4
    
class noise_note:
    def __init__(self, length, volume, fade, freq):
        self.length = length
        self.volume = volume
        self.fade = fade
        self.freq = freq

    def generate(self, offset):
        out = bytearray()
        out.append(self.length)
        if self.fade < 0:
            out.append((self.volume << 4) | (0b1000 | (self.fade * -1)))
        else:
            out.append((self.volume << 4) | (self.fade))
        out.append(self.freq & 0xff)
        assert self.size() == len(out)
        return out

    def size(self):
        return 3
    
class db:
    def __init__(self, byte):
        self.byte = byte
    
    def generate(self, offset):
        print(f'    db ${self.byte:02x}')
        return bytearray([self.byte])

    def size(self):
        return 1

class Unk:
    def __init__(self, cmd, *args):
        self.cmd = cmd
        self.args = [*args]

    def generate(self, offset):
        print('Unknown cmd:', self.cmd, ', args:', self.args)
        return bytearray([0x0])

    def size(self):
        return 1

cmd_table = {
    'note': note,
    'channel_count': channel_count,
    'channel': channel,
    'drum_note': drum_note,
    'rest': rest,
    'square_note': square_note,
    'noise_note': noise_note,
    'octave': octave,
    'note_type': note_type,
    'drum_speed': drum_speed,
    'transpose': transpose,
    'sound_ret': sound_ret,
    'tempo': tempo,
    'duty_cycle': duty_cycle,
    'volume_envelope': volume_envelope,
    'pitch_sweep': pitch_sweep,
    'toggle_sfx': toggle_sfx,
    'duty_cycle_pattern': duty_cycle_pattern,
    'vibrato': vibrato,
    'volume': volume,
    'pitch_offset': pitch_offset,
    'sfx_priority_on': sfx_priority_on,
    'sfx_priority_off': sfx_priority_off,
    'sfx_toggle_noise': sfx_toggle_noise,
    'sound_jump': sound_jump,
    'sound_loop': sound_loop,
    'sound_call': sound_call,
    'db': db
}

cmds = []
log = ''

for line in lines:
    if line == '':
        continue
    if line[0].isspace():
        line = remove_trailing_comment(line)
        line = line.strip()
        if ' ' in line:
            segments = line.split(' ', maxsplit=1)
            cmd = segments[0]
            if cmd == 'assert':
                continue
            args = segments[1]
            # print(f'    {cmd}({args})')
            aargs = parse_args(args)
            if cmd in cmd_table.keys():
                cmd_ = cmd_table[cmd](*aargs)
                cmds.append((cmd_, offset))
                # print((offset, cmd_.__class__.__name__))
                offset += cmd_.size()
            else:
                cmd_ = Unk(cmd, *aargs)
                cmds.append((cmd_, offset))
                offset += cmd_.size()
        else:
            cmd = line
            # print(f'    {cmd}')
            if cmd in cmd_table.keys():
                cmd_ = cmd_table[cmd]()
                cmds.append((cmd_, offset))
                # print((offset, cmd_.__class__.__name__))
                offset += cmd_.size()
            else:
                cmd_ = Unk(cmd)
                cmds.append((cmd_, offset))
                offset += cmd_.size()
    else:
        colonloc = line.find(':')
        if colonloc != -1:
            name = line[:colonloc]
            sname = add_symbol(name, offset)
            # print(f'0x{offset:04x}', sname)
        # print('x', line)

output = bytearray()
for cmd in cmds:
    # print(cmd)
    b = bytes(cmd[0].generate(cmd[1]))
    if len(b) != cmd[0].size():
        print(f'Size of {cmd[0].__class__.__name__} ({cmd[0].size()}) does not equal size of bytes output ({len(b)}).')
        exit(-1)
    # log += f'0x{cmd[1]:03x} ' + cmd[0].__class__.__name__.ljust(16) + ' '(*[f'{i:02x}' for i in b])
    if cmd[1] in locations.keys():
        log += f'{locations[cmd[1]]}:\n'
    log += f'0x{cmd[1]:04x} ' + cmd[0].__class__.__name__.ljust(16) + ' '
    for i in b:
        log += f'{i:02x} '
    if diffing == True:
        b2 = diffbin[cmd[1]:cmd[1] + cmd[0].size()]
        if b2 != b:
            log += ' ' * 4
            for i in b2:
                log += f'{i:02x} '
    log += '\n'
    output.extend(b)

with open(sys.argv[1].replace('.asm', '.bin'), 'wb') as out:
    out.write(output)

with open(sys.argv[1].replace('.asm', '.h'), 'w', encoding='utf8') as out:
    out.write('#pragma once\n\n')
    out.write(f'// {sys.argv[1]}\n')
    out.write('enum {\n')
    for k, v in symbols.items():
        if '.' in k:
            continue
        # k = k.replace('.', '_')
        out.write(f'    o{k.ljust(32)} = 0x{v:04x},\n')
    out.write('};\n')

with open(sys.argv[1].replace('.asm', '.log'), 'w', encoding='utf8') as out:
    out.write(log)
