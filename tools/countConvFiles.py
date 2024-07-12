import sys
import os.path as fs
from glob import glob

# These files will be ignored, either because their contents were unused
# or merged into another converted file.

skip_files = [
    'data/events/pokedex_ratings.asm',
    'data/items/mom_phone.asm',
    'data/maps/map_data.asm',
    'data/maps/scripts.asm',
    'data/maps/sgb_roof_pal_inds.asm',
    'data/moves/effects_pointers.asm',
    'data/moves/grammar.asm',
    'data/pokemon/egg_move_pointers.asm',
    'data/pokemon/evos_attacks.asm',
    'data/pokemon/dex_entry_pointers.asm',
    'data/sprite_anims/unused_gfx.asm',
    'data/text/common.asm',
    'data/text/mail_input_chars.asm',
    'data/trainers/party_pointers.asm',
    'data/wild/swarm_water.asm',
    'data/sgb_ctrl_packets.asm',
    'data/text_buffers.asm',
    'engine/battle/battlestart_copytilemapatonce.asm',
    'engine/battle/getgen1trainerclassname.asm',
    'engine/link/init_list.asm',
    'engine/overworld/map_object_action.asm',
    'engine/pokemon/correct_party_errors.asm',
    'engine/printer/printer_serial.asm',
    'gfx/pokemon/anim_pointers.asm',
    'gfx/pokemon/bitmask_pointers.asm',
    'gfx/pokemon/bitmasks.asm',
    'gfx/pokemon/frame_pointers.asm',
    'gfx/pokemon/idle_pointers.asm',
    'gfx/pokemon/johto_frames.asm',
    'gfx/pokemon/kanto_frames.asm',
    'gfx/pokemon/unown_anim_pointers.asm',
    'gfx/pokemon/unown_bitmask_pointers.asm',
    'gfx/pokemon/unown_bitmasks.asm',
    'gfx/pokemon/unown_frame_pointers.asm',
    'gfx/pokemon/unown_frames.asm',
    'gfx/pokemon/unown_idle_pointers.asm',
]

# Counts the number of asm files and how many are converted in each directory.

def count_dir(dir):
    converted_count = 0
    file_count = 0
    for path in glob(f'{dir}/*.asm'):
        if path.rsplit('\\', maxsplit=1)[1].startswith('unused_'):
            continue
        if path.replace('\\', '/') in skip_files:
            continue
        if fs.isfile(path.replace('.asm', '.c')):
            converted_count += 1
        file_count += 1
    return (converted_count, file_count)

counts = {
    'engine/battle/ai': count_dir('engine/battle/ai'),
    'engine/battle/move_effects': count_dir('engine/battle/move_effects'),
    'engine/battle': count_dir('engine/battle'),
    'engine/battle_anims': count_dir('engine/battle_anims'),
    'engine/debug': count_dir('engine/debug'),
    'engine/events/battle_tower': count_dir('engine/events/battle_tower'),
    'engine/events/bug_contest': count_dir('engine/events/bug_contest'),
    'engine/events/pokerus': count_dir('engine/events/pokerus'),
    'engine/events': count_dir('engine/events'),
    'engine/games': count_dir('engine/games'),
    'engine/gfx': count_dir('engine/gfx'),
    'engine/items': count_dir('engine/items'),
    'engine/link': count_dir('engine/link'),
    'engine/math': count_dir('engine/math'),
    'engine/menus': count_dir('engine/menus'),
    'engine/movie': count_dir('engine/movie'),
    'engine/overworld': count_dir('engine/overworld'),
    'engine/phone': count_dir('engine/phone'),
    'engine/pokedex': count_dir('engine/pokedex'),
    'engine/pokegear': count_dir('engine/pokegear'),
    'engine/pokemon': count_dir('engine/pokemon'),
    'engine/printer': count_dir('engine/printer'),
    'engine/rtc': count_dir('engine/rtc'),
    'engine/tilesets': count_dir('engine/tilesets'),
    'gfx': count_dir('gfx'),
    'gfx/pokemon': count_dir('gfx/pokemon'),
    'home': count_dir('home'),
    'maps': count_dir('maps'),
    'mobile': count_dir('mobile'),
    'data/battle/ai': count_dir('data/battle/ai'),
    'data/battle': count_dir('data/battle'),
    'data/battle_anims': count_dir('data/battle_anims'),
    'data/battle_tower': count_dir('data/battle_tower'),
    'data/collision': count_dir('data/collision'),
    'data/decorations': count_dir('data/decorations'),
    'data/events': count_dir('data/events'),
    'data/items': count_dir('data/items'),
    'data/maps': count_dir('data/maps'),
    'data/moves': count_dir('data/moves'),
    'data/phone': count_dir('data/phone'),
    'data/pokemon': count_dir('data/pokemon'),
    'data/radio': count_dir('data/radio'),
    'data/sprite_anims': count_dir('data/sprite_anims'),
    'data/sprites': count_dir('data/sprites'),
    'data/text': count_dir('data/text'),
    'data/trainers': count_dir('data/trainers'),
    'data/types': count_dir('data/types'),
    'data/wild': count_dir('data/wild'),
    'data': count_dir('data'),
}

converted_total = 0
file_total = 0

for k, v in counts.items():
    converted_total += v[0]
    file_total += v[1]
    print(f'{k}: {v[0]:02}/{v[1]:02} converted ({(v[0] / v[1]) * 100:.2f}%)')

print()

l = []
for k, v in counts.items():
    if v[1] - v[0] == 0:
        continue
    l.append([k, v[1]-v[0]])

l.sort(key=lambda e: e[1], reverse=True)

for n in l:
    print(f'{n[0]}: {n[1]} left')

print()

print(f"Total: {converted_total:02}/{file_total:02} converted ({(converted_total / file_total) * 100:.2f}%)")
