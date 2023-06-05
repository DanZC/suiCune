#ifndef CONSTANTS_H
#define CONSTANTS_H
extern void (*redirectFunc[])(void);
extern void (*convertedFunc[])(void);
#include <stdio.h>
#include "tools/emu/peanut_gb.h"

//#include "charmap.h"
#include "macros.h"

#include "tools/emu/macros.h"
#include "global.h"
#include "home/header.h"
#include "hram.h"

#include "constants/hardware_constants.h"
#include "constants/deco_constants.h"
#include "constants/wram_constants.h"
#include "constants/misc_constants.h"
#include "constants/input_constants.h"
#include "constants/gfx_constants.h"
#include "constants/text_constants.h"
#include "constants/audio_constants.h"
#include "constants/battle_anim_constants.h"
#include "constants/battle_constants.h"
#include "constants/collision_constants.h"
#include "constants/credits_constants.h"
#include "constants/cry_constants.h"
#include "constants/engine_flags.h"
#include "constants/event_flags.h"
#include "constants/icon_constants.h"
#include "constants/landmark_constants.h"
#include "constants/map_constants.h"
#include "constants/map_data_constants.h"
#include "constants/map_object_constants.h"
#include "constants/map_setup_constants.h"
#include "constants/mart_constants.h"
#include "constants/menu_constants.h"
#include "constants/mobile_constants.h"
#include "constants/move_constants.h"
#include "constants/move_effect_constants.h"
#include "constants/item_constants.h"
#include "constants/item_data_constants.h"
#include "constants/music_constants.h"
#include "constants/npc_trade_constants.h"
#include "constants/phone_constants.h"
#include "constants/pokemon_constants.h"
#include "constants/pokemon_data_constants.h"
#include "constants/printer_constants.h"
#include "constants/radio_constants.h"
#include "constants/scgb_constants.h"
#include "constants/scene_constants.h"
#include "constants/script_constants.h"
#include "constants/serial_constants.h"
#include "constants/sfx_constants.h"
#include "constants/sprite_anim_constants.h"
#include "constants/sprite_constants.h"
#include "constants/sprite_data_constants.h"
#include "constants/tileset_constants.h"
#include "constants/trainer_constants.h"
#include "constants/trainer_data_constants.h"
#include "constants/type_constants.h"
#include "constants/battle_tower_constants.h"

#include "constants/types.h"

#include "vram.h"

extern struct gb_s gb;
extern struct hram_s *hram;
extern struct vram_s *vram;
#endif