#include "../constants.h"
#include "../util/scripting.h"
#include "UnionCave1F.h"
//// EVENTS
enum {
    UNIONCAVE1F_POKEFAN_M1 = 2,
    UNIONCAVE1F_SUPER_NERD,
    UNIONCAVE1F_POKEFAN_M2,
    UNIONCAVE1F_FISHER1,
    UNIONCAVE1F_FISHER2,
    UNIONCAVE1F_POKE_BALL1,
    UNIONCAVE1F_POKE_BALL2,
    UNIONCAVE1F_POKE_BALL3,
    UNIONCAVE1F_POKE_BALL4,
};

const Script_fn_t UnionCave1F_SceneScripts[] = {
    0,
};

const struct MapCallback UnionCave1F_MapCallbacks[] = {
    0,
};

const struct MapScripts UnionCave1F_MapScripts = {
    .scene_script_count = 0, // lengthof(UnionCave1F_SceneScripts),
    .scene_scripts = UnionCave1F_SceneScripts,

    .callback_count = 0, // lengthof(UnionCave1F_MapCallbacks),
    .callbacks = UnionCave1F_MapCallbacks,
};

static const struct CoordEvent UnionCave1F_CoordEvents[] = {
    0,
};

static const struct BGEvent UnionCave1F_BGEvents[] = {
    0,
};

static const struct WarpEventData UnionCave1F_WarpEvents[] = {
    warp_event(5, 19, UNION_CAVE_B1F, 3),
    warp_event(3, 33, UNION_CAVE_B1F, 4),
    warp_event(17, 31, ROUTE_33, 1),
    warp_event(17, 3, ROUTE_32, 4),
};

static const struct ObjEvent UnionCave1F_ObjectEvents[] = {
    object_event(3, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerHikerDaniel, -1),
    object_event(4, 21, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacLarry, -1),
    object_event(11, 8, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 1, &TrainerHikerRussell, -1),
    object_event(15, 27, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerFirebreatherRay, -1),
    object_event(14, 19, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerFirebreatherBill, -1),
    object_event(17, 21, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &UnionCave1FGreatBall, EVENT_UNION_CAVE_1F_GREAT_BALL),
    object_event(4, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &UnionCave1FXAttack, EVENT_UNION_CAVE_1F_X_ATTACK),
    object_event(4, 17, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &UnionCave1FPotion, EVENT_UNION_CAVE_1F_POTION),
    object_event(12, 33, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &UnionCave1FAwakening, EVENT_UNION_CAVE_1F_AWAKENING),
};

const struct MapEvents UnionCave1F_MapEvents = {
    .warp_event_count = lengthof(UnionCave1F_WarpEvents),
    .warp_events = UnionCave1F_WarpEvents,

    .coord_event_count = 0, // lengthof(UnionCave1F_CoordEvents),
    .coord_events = UnionCave1F_CoordEvents,

    .bg_event_count = 0, // lengthof(UnionCave1F_BGEvents),
    .bg_events = UnionCave1F_BGEvents,

    .obj_event_count = lengthof(UnionCave1F_ObjectEvents),
    .obj_events = UnionCave1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "UnionCave1F.h"

const struct TrainerObj TrainerPokemaniacLarry = {POKEMANIAC, LARRY, EVENT_BEAT_POKEMANIAC_LARRY, PokemaniacLarrySeenText, PokemaniacLarryBeatenText, 0, TrainerPokemaniacLarry_Script};
bool TrainerPokemaniacLarry_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacLarryAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerRussell = {HIKER, RUSSELL, EVENT_BEAT_HIKER_RUSSELL, HikerRussellSeenText, HikerRussellBeatenText, 0, TrainerHikerRussell_Script};
bool TrainerHikerRussell_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerRussellAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerDaniel = {HIKER, DANIEL, EVENT_BEAT_HIKER_DANIEL, HikerDanielSeenText, HikerDanielBeatenText, 0, TrainerHikerDaniel_Script};
bool TrainerHikerDaniel_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerDanielAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFirebreatherBill = {FIREBREATHER, BILL, EVENT_BEAT_FIREBREATHER_BILL, FirebreatherBillSeenText, FirebreatherBillBeatenText, 0, TrainerFirebreatherBill_Script};
bool TrainerFirebreatherBill_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FirebreatherBillAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFirebreatherRay = {FIREBREATHER, RAY, EVENT_BEAT_FIREBREATHER_RAY, FirebreatherRaySeenText, FirebreatherRayBeatenText, 0, TrainerFirebreatherRay_Script};
bool TrainerFirebreatherRay_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FirebreatherRayAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall UnionCave1FGreatBall = {GREAT_BALL, 1};
const struct ItemBall UnionCave1FXAttack = {X_ATTACK, 1};
const struct ItemBall UnionCave1FPotion = {POTION, 1};
const struct ItemBall UnionCave1FAwakening = {AWAKENING, 1};
bool UnionCave1FUnusedSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(UnionCave1FUnusedSignText)
    SCRIPT_END
}
const txt_cmd_s HikerRussellSeenText[] = {
    text_start("You're headed to"
        t_line "AZALEA, are you?"
        t_para "Let my #MON see"
        t_line "if you are good"
        t_cont "enough to battle."
        t_done )
};
const txt_cmd_s HikerRussellBeatenText[] = {
    text_start("Oh, oh, oh!"
        t_done )
};
const txt_cmd_s HikerRussellAfterBattleText[] = {
    text_start("All right, then!"
        t_line "I've decided."
        t_para "I'm not leaving"
        t_line "until my #MON"
        t_cont "get tougher!"
        t_done )
};
const txt_cmd_s PokemaniacLarrySeenText[] = {
    text_start("I roam far and"
        t_line "wide in search of"
        t_cont "#MON."
        t_para "Are you looking"
        t_line "for #MON too?"
        t_para "Then you're my"
        t_line "collecting rival!"
        t_done )
};
const txt_cmd_s PokemaniacLarryBeatenText[] = {
    text_start("Ugh. My poor #-"
        t_line "MON…"
        t_done )
};
const txt_cmd_s PokemaniacLarryAfterBattleText[] = {
    text_start("Every Friday, you"
        t_line "can hear #MON"
        t_para "roars from deep"
        t_line "inside the cave."
        t_done )
};
const txt_cmd_s HikerDanielSeenText[] = {
    text_start("Whoa! What a"
        t_line "surprise!"
        t_para "I didn't expect to"
        t_line "see anyone here!"
        t_done )
};
const txt_cmd_s HikerDanielBeatenText[] = {
    text_start("Whoa! I'm beaten"
        t_line "big time!"
        t_done )
};
const txt_cmd_s HikerDanielAfterBattleText[] = {
    text_start("I was conned into"
        t_line "buying a SLOWPOKE-"
        t_cont "TAIL."
        t_para "I feel sorry for"
        t_line "the poor #MON."
        t_done )
};
const txt_cmd_s FirebreatherBillSeenText[] = {
    text_start("ZUBAT's SUPERSONIC"
        t_line "keeps confusing"
        t_cont "my #MON."
        t_para "I'm seriously"
        t_line "upset about that!"
        t_done )
};
const txt_cmd_s FirebreatherBillBeatenText[] = {
    text_start("I flamed out!"
        t_done )
};
const txt_cmd_s FirebreatherBillAfterBattleText[] = {
    text_start("On weekends, you"
        t_line "can hear strange"
        t_para "roars from deep in"
        t_line "the cave."
        t_done )
};
const txt_cmd_s FirebreatherRaySeenText[] = {
    text_start("If it's light, a"
        t_line "cave isn't scary."
        t_para "If you're strong,"
        t_line "#MON aren't"
        t_cont "scary."
        t_done )
};
const txt_cmd_s FirebreatherRayBeatenText[] = {
    text_start("FLASH!"
        t_done )
};
const txt_cmd_s FirebreatherRayAfterBattleText[] = {
    text_start("It's my #MON's"
        t_line "fire that lights"
        t_cont "up this cave."
        t_done )
};
const txt_cmd_s UnionCave1FUnusedSignText[] = {
    text_start("UNION CAVE"
        t_done )
    //db(0, 0) // filler
};
