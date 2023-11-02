from dataclasses import dataclass
from typing import List, Union, Dict
import sys
import json
from convScript import convert_script_from_lines

do_print = len(sys.argv) < 3

map_name = sys.argv[1][sys.argv[1].rfind('/')+1:sys.argv[1].rfind('.')]

with open(sys.argv[1], 'r', encoding='utf8') as f:
    lines = f.read().splitlines()

c = 0

out = {
    "map_name": map_name,
    "object_const_def": [],
    "scene_scripts": [],
    "callbacks": [],
    "warp_events": [],
    "coord_events": [],
    "bg_events": [],
    "object_events": [],
}

script_lines = []
in_map_scripts = False

i = 0
while i < len(lines):
    line = lines[i]
    if line == '':
        script_lines.append(line)
        i += 1
        continue
    if not line[0].isspace():
        if line.startswith(f'{map_name}_MapScripts:'):
            in_map_scripts = True
            i += 1
            continue
        elif line.startswith(f'{map_name}_MapEvents:'):
            in_map_scripts = True
            i += 1
            continue
        elif in_map_scripts and line[0] == '.':
            script_lines.append(f'{map_name}_MapScripts_{line[1:]}:')
            i += 1
            continue
        in_map_scripts = False
        script_lines.append(line)
        i += 1
        continue
    full_line = line
    line = line.strip()
    if line == 'object_const_def':
        i += 1
        while i < len(lines) and lines[i].strip().startswith('const'):
            obj_const = lines[i].strip().split(' ', maxsplit=1)[1]
            out["object_const_def"].append(obj_const)
            i += 1
        continue
    if line == 'def_scene_scripts':
        i += 1
        while i < len(lines) and lines[i].strip().startswith('scene_script'):
            restline = script = lines[i].strip().split(' ', maxsplit=1)[1]
            if restline.find(';') != -1:
                script = restline.replace(';', ', // ')
            else:
                script = restline + ','
            if script.startswith('.'):
                script = f'{map_name}_MapScripts_{script[1:]}'
            out["scene_scripts"].append(script)
            i += 1
        continue
    if line == 'def_callbacks':
        i += 1
        while i < len(lines) and lines[i].strip().startswith('callback'):
            callback_line = lines[i].strip().split(' ', maxsplit=1)[1]
            callback_line_parts = callback_line.split(',')
            callback = {
                "type": callback_line_parts[0].strip(),
                "script": callback_line_parts[1].strip()
            }
            out["callbacks"].append(callback)
            i += 1
        continue
    if line == 'def_warp_events':
        i += 1
        while i < len(lines) and lines[i].strip().startswith('warp_event'):
            warp_event_line = lines[i].strip().split(' ', maxsplit=1)[1]
            warp_event_line_parts = warp_event_line.split(',')
            warp_event = {
                "x": int(warp_event_line_parts[0].strip()),
                "y": int(warp_event_line_parts[1].strip()),
                "map": warp_event_line_parts[2].strip(),
                "warpNumber": int(warp_event_line_parts[3].strip()),
            }
            out["warp_events"].append(warp_event)
            i += 1
        continue
    if line == 'def_coord_events':
        i += 1
        while i < len(lines) and lines[i].strip().startswith('coord_event'):
            coord_event_line = lines[i].strip().split(' ', maxsplit=1)[1]
            coord_event_line_parts = coord_event_line.split(',')
            coord_event = {
                "x": int(coord_event_line_parts[0].strip()),
                "y": int(coord_event_line_parts[1].strip()),
                "scene_id": coord_event_line_parts[2].strip(),
                "script": coord_event_line_parts[3].strip(),
            }
            out["coord_events"].append(coord_event)
            i += 1
        continue
    if line == 'def_bg_events':
        i += 1
        while i < len(lines) and lines[i].strip().startswith('bg_event'):
            event_line = lines[i].strip().split(' ', maxsplit=1)[1]
            event_line_parts = event_line.split(',')
            event = {
                "x": int(event_line_parts[0].strip()),
                "y": int(event_line_parts[1].strip()),
                "function": event_line_parts[2].strip(),
                "script": event_line_parts[3].strip(),
            }
            out["bg_events"].append(event)
            i += 1
        continue
    if line == 'def_object_events':
        i += 1
        while i < len(lines) and lines[i].strip().startswith('object_event'):
            event_line = lines[i].strip().split(' ', maxsplit=1)[1]
            event_line_parts = event_line.split(',')
            event = {
                "x": int(event_line_parts[0].strip()),
                "y": int(event_line_parts[1].strip()),
                "sprite": event_line_parts[2].strip(),
                "movement": event_line_parts[3].strip(),
                "radiusX": int(event_line_parts[4].strip()),
                "radiusY": int(event_line_parts[5].strip()),
                "h1": event_line_parts[6].strip(),
                "h2": event_line_parts[7].strip(),
                "color": event_line_parts[8].strip(),
                "function": event_line_parts[9].strip(),
                "sightRange": int(event_line_parts[10].strip()),
                "script": event_line_parts[11].strip(),
                "eventFlag": event_line_parts[12].strip(),
            }
            out["object_events"].append(event)
            i += 1
        continue
    script_lines.append(full_line)
    i += 1

# print(json.dumps(out, indent=2))
def map_json_to_c(dict: Dict[str, any]):
    out_h = '#pragma once\n//// EVENTS\n'
    out = '//// EVENTS\n'
    if len(dict["object_const_def"]) > 0:
        out += 'enum {\n'
        for const in dict["object_const_def"]:
            out += f'    {const},\n'
        out += '};\n\n'
    
    out += f'const Script_fn_t {dict["map_name"]}_SceneScripts[] = {{\n'
    for script in dict["scene_scripts"]:
        out += f'    {script},\n'
    out += '};\n\n'
    out_h += f'extern const Script_fn_t {dict["map_name"]}_SceneScripts[];\n'

    out += f'const struct MapCallback {dict["map_name"]}_MapCallbacks[] = {{\n'
    for script in dict["callbacks"]:
        if script["script"].startswith('.'):
            s = f'{dict["map_name"]}_MapScripts_{script["script"][1:]}'
        else:
            s = script["script"]
        out += f'    map_callback({script["type"]}, {s}),\n'
    out += '};\n\n'
    out_h += f'extern const struct MapCallback {dict["map_name"]}_MapCallbacks[];\n\n'

    out += f'const struct CoordEvent {dict["map_name"]}_CoordEvents[] = {{\n'
    for event in dict["coord_events"]:
        out += f'    coord_event({event["x"]}, {event["y"]}, {event["scene_id"]}, {event["script"]}),\n'
    out += '};\n\n'

    out += f'const struct BGEvent {dict["map_name"]}_BGEvents[] = {{\n'
    for event in dict["bg_events"]:
        out += f'    bg_event({event["x"]}, {event["y"]}, {event["function"]}, {event["script"]}),\n'
    out += '};\n\n'

    out += f'static const struct WarpEvent {dict["map_name"]}_WarpEvents[] = {{\n'
    for event in dict["warp_events"]:
        out += f'    warp_event({event["x"]}, {event["y"]}, {event["map"]}, {event["warpNumber"]}),\n'
    out += '};\n\n'

    out += f'static const struct ObjEvent {dict["map_name"]}_ObjectEvents[] = {{\n'
    for event in dict["object_events"]:
        out += f'    object_event({event["x"]}, {event["y"]}, {event["sprite"]}, {event["movement"]}, '
        out += f'{event["radiusX"]}, {event["radiusY"]}, {event["h1"]}, {event["h2"]}, {event["color"]}, '
        out += f'{event["function"]}, {event["sightRange"]}, {event["script"]}, {event["eventFlag"]}),\n'
    out += '};\n\n'

    out += f'const struct MapEvents {dict["map_name"]}_MapEvents = {{\n'
    out += f'    .warp_event_count = lengthof({dict["map_name"]}_WarpEvents),\n'
    out += f'    .warp_events = {dict["map_name"]}_WarpEvents,\n\n'
    out += f'    .coord_event_count = lengthof({dict["map_name"]}_CoordEvents),\n'
    out += f'    .coord_events = {dict["map_name"]}_CoordEvents,\n\n'
    out += f'    .bg_event_count = lengthof({dict["map_name"]}_BGEvents),\n'
    out += f'    .bg_event = {dict["map_name"]}_BGEvents,\n\n'
    out += f'    .obj_event_count = lengthof({dict["map_name"]}_ObjectEvents),\n'
    out += f'    .obj_events = {dict["map_name"]}_ObjectEvents,\n'
    out += '};\n\n'
    out_h += f'extern const struct MapEvents {dict["map_name"]}_MapEvents;\n\n'

    out += '//// CODE\n'
    out_h += '//// CODE\n'
    return out, out_h

if do_print:
    out_, out_h_ = map_json_to_c(out)
    out2_, out2_h_ = convert_script_from_lines(sys.argv[1], script_lines)
    out2_h_ = out2_h_.replace('#pragma once\n', '\n')
    out2_ = out2_.replace('#include "../../../constants.h"\n#include "../../../util/scripting_macros.h"', '')
    out3_h = out_h_ + out2_h_
    out3 = out_ + out2_
    print(out3)
else:
    out_filepath = sys.argv[2]
    if out_filepath.endswith('.json'):
        with open(sys.argv[2], "w", encoding='utf8') as f:
            json.dump(out, f, indent=4)
    else:
        out_, out_h_ = map_json_to_c(out)
        out2_, out2_h_ = convert_script_from_lines(sys.argv[1], script_lines)
        print(out2_)
