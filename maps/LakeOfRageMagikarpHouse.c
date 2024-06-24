#include "../constants.h"
#include "../util/scripting.h"
#include "LakeOfRageMagikarpHouse.h"
//// EVENTS
enum {
    LAKEOFRAGEMAGIKARPHOUSE_FISHING_GURU = 2,
};

const Script_fn_t LakeOfRageMagikarpHouse_SceneScripts[] = {
    0,
};

const struct MapCallback LakeOfRageMagikarpHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts LakeOfRageMagikarpHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(LakeOfRageMagikarpHouse_SceneScripts),
    .scene_scripts = LakeOfRageMagikarpHouse_SceneScripts,

    .callback_count = 0, // lengthof(LakeOfRageMagikarpHouse_MapCallbacks),
    .callbacks = LakeOfRageMagikarpHouse_MapCallbacks,
};

static const struct CoordEvent LakeOfRageMagikarpHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent LakeOfRageMagikarpHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &MagikarpHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &MagikarpHouseBookshelf),
};

static const struct WarpEventData LakeOfRageMagikarpHouse_WarpEvents[] = {
    warp_event(2, 7, LAKE_OF_RAGE, 2),
    warp_event(3, 7, LAKE_OF_RAGE, 2),
};

static const struct ObjEvent LakeOfRageMagikarpHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_FISHING_GURU, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MagikarpLengthRaterScript, -1),
};

const struct MapEvents LakeOfRageMagikarpHouse_MapEvents = {
    .warp_event_count = lengthof(LakeOfRageMagikarpHouse_WarpEvents),
    .warp_events = LakeOfRageMagikarpHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(LakeOfRageMagikarpHouse_CoordEvents),
    .coord_events = LakeOfRageMagikarpHouse_CoordEvents,

    .bg_event_count = lengthof(LakeOfRageMagikarpHouse_BGEvents),
    .bg_events = LakeOfRageMagikarpHouse_BGEvents,

    .obj_event_count = lengthof(LakeOfRageMagikarpHouse_ObjectEvents),
    .obj_events = LakeOfRageMagikarpHouse_ObjectEvents,
};

//// CODE

bool MagikarpLengthRaterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_LAKE_OF_RAGE_ELIXIR_ON_STANDBY)
    iftrue(GetReward)
    checkevent(EVENT_LAKE_OF_RAGE_ASKED_FOR_MAGIKARP)
    iftrue(AskedForMagikarp)
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(ClearedRocketHideout)
    checkevent(EVENT_LAKE_OF_RAGE_EXPLAINED_WEIRD_MAGIKARP)
    iftrue(ExplainedHistory)
    writetext(MagikarpLengthRaterText_LakeOfRageHistory)
    waitbutton
    closetext
    setevent(EVENT_LAKE_OF_RAGE_EXPLAINED_WEIRD_MAGIKARP)
    s_end
ExplainedHistory:
    writetext(MagikarpLengthRaterText_MenInBlack)
    waitbutton
    closetext
    s_end
ClearedRocketHideout:
    writetext(MagikarpLengthRaterText_WorldsLargestMagikarp)
    waitbutton
    closetext
    setevent(EVENT_LAKE_OF_RAGE_ASKED_FOR_MAGIKARP)
    s_end
AskedForMagikarp:
    setval(MAGIKARP)
    special(FindPartyMonThatSpecies)
    iffalse(ClearedRocketHideout)
    writetext(MagikarpLengthRaterText_YouHaveAMagikarp)
    waitbutton
    special(CheckMagikarpLength)
    ifequal(MAGIKARPLENGTH_NOT_MAGIKARP, NotMagikarp)
    ifequal(MAGIKARPLENGTH_REFUSED, Refused)
    ifequal(MAGIKARPLENGTH_TOO_SHORT, TooShort)
    // MAGIKARPLENGTH_BEAT_RECORD
    goto GetReward;
GetReward:
    writetext(MagikarpLengthRaterText_Memento)
    promptbutton
    verbosegiveitem(ELIXER, 1)
    iffalse(NoRoom)
    writetext(MagikarpLengthRaterText_Bonus)
    waitbutton
    closetext
    clearevent(EVENT_LAKE_OF_RAGE_ELIXIR_ON_STANDBY)
    s_end
NoRoom:
    closetext
    setevent(EVENT_LAKE_OF_RAGE_ELIXIR_ON_STANDBY)
    s_end
TooShort:
    writetext(MagikarpLengthRaterText_TooShort)
    waitbutton
    closetext
    s_end
NotMagikarp:
    writetext(MagikarpLengthRaterText_NotMagikarp)
    waitbutton
    closetext
    s_end
Refused:
    writetext(MagikarpLengthRaterText_Refused)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LakeOfRageMagikarpHouseUnusedRecordSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(LakeOfRageMagikarpHouseUnusedRecordText)
    SCRIPT_END
}
bool MagikarpHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s MagikarpLengthRaterText_LakeOfRageHistory[] = {
    text_start("LAKE OF RAGE is"
        t_line "actually a crater"
        t_para "made by rampaging"
        t_line "GYARADOS."
        t_para "The crater filled"
        t_line "up with rainwater"
        t_para "and the LAKE was"
        t_line "formed."
        t_para "That's the story"
        t_line "passed on from my"
        t_para "Grandpa's great-"
        t_line "great-grandpa."
        t_para "It used to be that"
        t_line "you could catch"
        t_para "lively MAGIKARP"
        t_line "there, but…"
        t_para "I don't understand"
        t_line "what's happening."
        t_done )
};
const txt_cmd_s MagikarpLengthRaterText_MenInBlack[] = {
    text_start("The LAKE hasn't"
        t_line "been normal since"
        t_para "those men wearing"
        t_line "black arrived."
        t_done )
};
const txt_cmd_s MagikarpLengthRaterText_WorldsLargestMagikarp[] = {
    text_start("LAKE OF RAGE is"
        t_line "back to normal."
        t_para "The MAGIKARP have"
        t_line "returned."
        t_para "I may yet realize"
        t_line "my dream of see-"
        t_cont "ing the world's"
        t_cont "largest MAGIKARP."
        t_para "Do you have a ROD?"
        t_line "Please help me if"
        t_cont "you do."
        t_done )
};
const txt_cmd_s MagikarpLengthRaterText_YouHaveAMagikarp[] = {
    text_start("Ah, you have a"
        t_line "MAGIKARP! Let's"
        t_para "see how big that"
        t_line "baby is."
        t_done )
};
const txt_cmd_s MagikarpLengthRaterText_Memento[] = {
    text_start("Wow! This one is"
        t_line "outstanding!"
        t_para "I tip my hat to"
        t_line "you!"
        t_para "Take this as a"
        t_line "memento!"
        t_done )
};
const txt_cmd_s MagikarpLengthRaterText_Bonus[] = {
    text_start("The record is the"
        t_line "important thing."
        t_para "Think of that as"
        t_line "a bonus!"
        t_done )
};
const txt_cmd_s MagikarpLengthRaterText_TooShort[] = {
    text_start("Wow! This one is"
        t_line "outstanding!"
        t_para "…I wish I could"
        t_line "say that, but I've"
        t_para "seen a bigger one"
        t_line "before."
        t_done )
};
const txt_cmd_s MagikarpLengthRaterText_NotMagikarp[] = {
    text_start("What? That's not a"
        t_line "MAGIKARP!"
        t_done )
};
const txt_cmd_s MagikarpLengthRaterText_Refused[] = {
    text_start("Oh… So you didn't"
        t_line "get one good"
        t_para "enough to show me?"
        t_line "Maybe next time."
        t_done )
};
const txt_cmd_s LakeOfRageMagikarpHouseUnusedRecordText[] = {
    text_start("CURRENT RECORD"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" caught by"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_done )
};
// bool LakeOfRageMagikarpHouseUnusedDummyText(script_s* s) {
//     SCRIPT_BEGIN
//     text_en)
//     //db(0, 0) // filler
//     SCRIPT_END
// }
