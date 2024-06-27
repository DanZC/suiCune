#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornCity.h"
//// EVENTS
enum {
    BLACKTHORNCITY_SUPER_NERD1 = 2,
    BLACKTHORNCITY_SUPER_NERD2,
    BLACKTHORNCITY_GRAMPS1,
    BLACKTHORNCITY_GRAMPS2,
    BLACKTHORNCITY_BLACK_BELT,
    BLACKTHORNCITY_COOLTRAINER_F1,
    BLACKTHORNCITY_YOUNGSTER1,
    BLACKTHORNCITY_SANTOS,
    BLACKTHORNCITY_COOLTRAINER_F2,
};

const Script_fn_t BlackthornCity_SceneScripts[] = {
    0,
};

const struct MapCallback BlackthornCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, BlackthornCity_MapScripts_FlyPoint),
    map_callback(MAPCALLBACK_OBJECTS, BlackthornCity_MapScripts_Santos),
};

const struct MapScripts BlackthornCity_MapScripts = {
    .scene_script_count = 0, // lengthof(BlackthornCity_SceneScripts),
    .scene_scripts = BlackthornCity_SceneScripts,

    .callback_count = lengthof(BlackthornCity_MapCallbacks),
    .callbacks = BlackthornCity_MapCallbacks,
};

static const struct CoordEvent BlackthornCity_CoordEvents[] = {
    0,
};

static const struct BGEvent BlackthornCity_BGEvents[] = {
    bg_event(34, 24, BGEVENT_READ, &BlackthornCitySign),
    bg_event(17, 13, BGEVENT_READ, &BlackthornGymSign),
    bg_event(7, 31, BGEVENT_READ, &MoveDeletersHouseSign),
    bg_event(21, 3, BGEVENT_READ, &DragonDensSign),
    bg_event(5, 25, BGEVENT_READ, &BlackthornCityTrainerTips),
    bg_event(16, 29, BGEVENT_READ, &BlackthornCityMartSign),
    bg_event(22, 29, BGEVENT_READ, &BlackthornCityPokecenterSign),
};

static const struct WarpEventData BlackthornCity_WarpEvents[] = {
    warp_event(18, 11, BLACKTHORN_GYM_1F, 1),
    warp_event(13, 21, BLACKTHORN_DRAGON_SPEECH_HOUSE, 1),
    warp_event(29, 23, BLACKTHORN_EMYS_HOUSE, 1),
    warp_event(15, 29, BLACKTHORN_MART, 2),
    warp_event(21, 29, BLACKTHORN_POKECENTER_1F, 1),
    warp_event(9, 31, MOVE_DELETERS_HOUSE, 1),
    warp_event(36, 9, ICE_PATH_1F, 2),
    warp_event(20, 1, DRAGONS_DEN_1F, 1),
};

static const struct ObjEvent BlackthornCity_ObjectEvents[] = {
    object_event(18, 12, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BlackthornSuperNerdScript, EVENT_BLACKTHORN_CITY_SUPER_NERD_BLOCKS_GYM),
    object_event(19, 12, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BlackthornSuperNerdScript, EVENT_BLACKTHORN_CITY_SUPER_NERD_DOES_NOT_BLOCK_GYM),
    object_event(20, 2, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornGramps1Script, EVENT_BLACKTHORN_CITY_GRAMPS_BLOCKS_DRAGONS_DEN),
    object_event(21, 2, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornGramps2Script, EVENT_BLACKTHORN_CITY_GRAMPS_NOT_BLOCKING_DRAGONS_DEN),
    object_event(24, 31, SPRITE_BLACK_BELT, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BlackthornBlackBeltScript, -1),
    object_event(9, 25, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BlackthornCooltrainerF1Script, -1),
    object_event(13, 15, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornYoungsterScript, -1),
    object_event(22, 20, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SantosScript, EVENT_BLACKTHORN_CITY_SANTOS_OF_SATURDAY),
    object_event(35, 19, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BlackthornCooltrainerF2Script, -1),
};

const struct MapEvents BlackthornCity_MapEvents = {
    .warp_event_count = lengthof(BlackthornCity_WarpEvents),
    .warp_events = BlackthornCity_WarpEvents,

    .coord_event_count = 0, // lengthof(BlackthornCity_CoordEvents),
    .coord_events = BlackthornCity_CoordEvents,

    .bg_event_count = lengthof(BlackthornCity_BGEvents),
    .bg_events = BlackthornCity_BGEvents,

    .obj_event_count = lengthof(BlackthornCity_ObjectEvents),
    .obj_events = BlackthornCity_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornCity.h"

bool BlackthornCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_BLACKTHORN)
    s_endcallback
    SCRIPT_END
}
bool BlackthornCity_MapScripts_Santos(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal(SATURDAY, SantosAppears)
    disappear(BLACKTHORNCITY_SANTOS)
    s_endcallback
SantosAppears:
    appear(BLACKTHORNCITY_SANTOS)
    s_endcallback
    SCRIPT_END
}
bool BlackthornSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BEAT_CLAIR)
    iftrue(BeatClair)
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(ClearedRadioTower)
    writetext(Text_ClairIsOut)
    waitbutton
    closetext
    s_end
ClearedRadioTower:
    writetext(Text_ClairIsIn)
    waitbutton
    closetext
    s_end
BeatClair:
    writetext(Text_ClairIsBeaten)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BlackthornGramps1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornGrampsRefusesEntryText)
    SCRIPT_END
}
bool BlackthornGramps2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornGrampsGrantsEntryText)
    SCRIPT_END
}
bool BlackthornBlackBeltScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(ClearedRadioTower)
    writetext(BlackBeltText_WeirdRadio)
    waitbutton
    closetext
    s_end
ClearedRadioTower:
    writetext(BlackBeltText_VoicesInMyHead)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BlackthornCooltrainerF1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornCooltrainerF1Text)
    SCRIPT_END
}
bool BlackthornYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornYoungsterText)
    SCRIPT_END
}
bool BlackthornCooltrainerF2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornCooltrainerF2Text)
    SCRIPT_END
}
bool SantosScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_SPELL_TAG_FROM_SANTOS)
    iftrue(Saturday)
    readvar(VAR_WEEKDAY)
    ifnotequal(SATURDAY, NotSaturday)
    checkevent(EVENT_MET_SANTOS_OF_SATURDAY)
    iftrue(MetSantos)
    writetext(MeetSantosText)
    promptbutton
    setevent(EVENT_MET_SANTOS_OF_SATURDAY)
MetSantos:
    writetext(SantosGivesGiftText)
    promptbutton
    verbosegiveitem(SPELL_TAG, 1)
    iffalse(Done)
    setevent(EVENT_GOT_SPELL_TAG_FROM_SANTOS)
    writetext(SantosGaveGiftText)
    waitbutton
    closetext
    s_end
Saturday:
    writetext(SantosSaturdayText)
    waitbutton
Done:
    closetext
    s_end
NotSaturday:
    writetext(SantosNotSaturdayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BlackthornCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(BlackthornCitySignText)
    SCRIPT_END
}
bool BlackthornGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(BlackthornGymSignText)
    SCRIPT_END
}
bool MoveDeletersHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MoveDeletersHouseSignText)
    SCRIPT_END
}
bool DragonDensSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(DragonDensSignText)
    SCRIPT_END
}
bool BlackthornCityTrainerTips(script_s* s) {
    SCRIPT_BEGIN
    jumptext(BlackthornCityTrainerTipsText)
    SCRIPT_END
}
bool BlackthornCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool BlackthornCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const txt_cmd_s Text_ClairIsOut[] = {
    text_start("I am sorry."
        t_para "CLAIR, our GYM"
        t_line "LEADER, entered"
        t_para "the DRAGON'S DEN"
        t_line "behind the GYM."
        t_para "I have no idea"
        t_line "when our LEADER"
        t_cont "will return."
        t_done )
};
const txt_cmd_s Text_ClairIsIn[] = {
    text_start("CLAIR, our GYM"
        t_line "LEADER, is waiting"
        t_cont "for you."
        t_para "However, it would"
        t_line "be impossible for"
        t_para "a run-of-the-mill"
        t_line "trainer to win."
        t_done )
};
const txt_cmd_s Text_ClairIsBeaten[] = {
    text_start("You defeated"
        t_line "CLAIR?"
        t_para "That's amazing!"
        t_para "I've never heard"
        t_line "of her losing to"
        t_para "anyone other than"
        t_line "LANCE."
        t_done )
};
const txt_cmd_s BlackthornGrampsRefusesEntryText[] = {
    text_start("No. Only chosen"
        t_line "trainers may train"
        t_para "here."
        t_line "Please leave."
        t_done )
};
const txt_cmd_s BlackthornGrampsGrantsEntryText[] = {
    text_start("If CLAIR allows"
        t_line "it, her grand-"
        t_cont "father--our MASTER"
        t_cont "--will also."
        t_para "You may enter."
        t_done )
};
const txt_cmd_s BlackBeltText_WeirdRadio[] = {
    text_start("My radio's busted?"
        t_line "Lately, I only get"
        t_cont "this weird signal."
        t_done )
};
const txt_cmd_s BlackBeltText_VoicesInMyHead[] = {
    text_start("Arooo! Voices in"
        t_line "my head!"
        t_para "Huh? I'm listening"
        t_line "to my radio!"
        t_done )
};
const txt_cmd_s BlackthornCooltrainerF1Text[] = {
    text_start("Are you going to"
        t_line "make your #MON"
        t_cont "forget some moves?"
        t_done )
};
const txt_cmd_s BlackthornYoungsterText[] = {
    text_start("Dragon masters all"
        t_line "come from the city"
        t_cont "of BLACKTHORN."
        t_done )
};
const txt_cmd_s MeetSantosText[] = {
    text_start("SANTOS: …"
        t_para "It's Saturday…"
        t_para "I'm SANTOS of"
        t_line "Saturday…"
        t_done )
};
const txt_cmd_s SantosGivesGiftText[] = {
    text_start("You can have this…"
        t_done )
};
const txt_cmd_s SantosGaveGiftText[] = {
    text_start("SANTOS: …"
        t_para "SPELL TAG…"
        t_para "Ghost-type moves"
        t_line "get stronger…"
        t_para "It will frighten"
        t_line "you…"
        t_done )
};
const txt_cmd_s SantosSaturdayText[] = {
    text_start("SANTOS: …"
        t_para "See you again on"
        t_line "another Saturday…"
        t_para "I won't have any"
        t_line "more gifts…"
        t_done )
};
const txt_cmd_s SantosNotSaturdayText[] = {
    text_start("SANTOS: Today's"
        t_line "not Saturday…"
        t_done )
};
const txt_cmd_s BlackthornCooltrainerF2Text[] = {
    text_start("Wow, you came"
        t_line "through the ICE"
        t_cont "PATH?"
        t_para "You must be a real"
        t_line "hotshot trainer!"
        t_done )
};
const txt_cmd_s BlackthornCitySignText[] = {
    text_start("BLACKTHORN CITY"
        t_para "A Quiet Mountain"
        t_line "Retreat"
        t_done )
};
const txt_cmd_s BlackthornGymSignText[] = {
    text_start("BLACKTHORN CITY"
        t_line "#MON GYM"
        t_cont "LEADER: CLAIR"
        t_para "The Blessed User"
        t_line "of Dragon #MON"
        t_done )
};
const txt_cmd_s MoveDeletersHouseSignText[] = {
    text_start("MOVE DELETER'S"
        t_line "HOUSE"
        t_done )
};
const txt_cmd_s DragonDensSignText[] = {
    text_start("DRAGON'S DEN"
        t_line "AHEAD"
        t_done )
};
const txt_cmd_s BlackthornCityTrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "A #MON holding"
        t_line "a MIRACLEBERRY"
        t_para "will cure itself"
        t_line "of any status"
        t_cont "problem."
        t_done )
    //db(0, 0) // filler
};
