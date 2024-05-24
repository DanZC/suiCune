#include "../constants.h"
#include "../util/scripting.h"
#include "DayCare.h"
//// EVENTS
enum {
    DAYCARE_GRAMPS = 2,
    DAYCARE_GRANNY,
};

const Script_fn_t DayCare_SceneScripts[] = {
    0,
};

const struct MapCallback DayCare_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, DayCare_MapScripts_EggCheckCallback),
};

const struct MapScripts DayCare_MapScripts = {
    .scene_script_count = 0, // lengthof(DayCare_SceneScripts),
    .scene_scripts = DayCare_SceneScripts,

    .callback_count = lengthof(DayCare_MapCallbacks),
    .callbacks = DayCare_MapCallbacks,
};

static const struct CoordEvent DayCare_CoordEvents[] = {
    0,
};

static const struct BGEvent DayCare_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &DayCareBookshelf),
    bg_event(1, 1, BGEVENT_READ, &DayCareBookshelf),
};

static const struct WarpEventData DayCare_WarpEvents[] = {
    warp_event(0, 5, ROUTE_34, 3),
    warp_event(0, 6, ROUTE_34, 4),
    warp_event(2, 7, ROUTE_34, 5),
    warp_event(3, 7, ROUTE_34, 5),
};

static const struct ObjEvent DayCare_ObjectEvents[] = {
    object_event(2, 3, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DayCareManScript_Inside, EVENT_DAY_CARE_MAN_IN_DAY_CARE),
    object_event(5, 3, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &DayCareLadyScript, -1),
};

const struct MapEvents DayCare_MapEvents = {
    .warp_event_count = lengthof(DayCare_WarpEvents),
    .warp_events = DayCare_WarpEvents,

    .coord_event_count = 0, // lengthof(DayCare_CoordEvents),
    .coord_events = DayCare_CoordEvents,

    .bg_event_count = lengthof(DayCare_BGEvents),
    .bg_events = DayCare_BGEvents,

    .obj_event_count = lengthof(DayCare_ObjectEvents),
    .obj_events = DayCare_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "DayCare.h"

bool DayCare_MapScripts_EggCheckCallback(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_DAY_CARE_MAN_HAS_EGG)
    iftrue_jump(DayCare_MapScripts_PutDayCareManOutside)
    clearevent(EVENT_DAY_CARE_MAN_IN_DAY_CARE)
    setevent(EVENT_DAY_CARE_MAN_ON_ROUTE_34)
    s_endcallback
    SCRIPT_END
}
bool DayCare_MapScripts_PutDayCareManOutside(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_DAY_CARE_MAN_IN_DAY_CARE)
    clearevent(EVENT_DAY_CARE_MAN_ON_ROUTE_34)
    s_endcallback
    SCRIPT_END
}
bool DayCareManScript_Inside(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_ODD_EGG)
    iftrue(AlreadyHaveOddEgg)
    writetext(DayCareManText_GiveOddEgg)
    promptbutton
    closetext
    readvar(VAR_PARTYCOUNT)
    ifequal(PARTY_LENGTH, PartyFull)
    special(GiveOddEgg)
    opentext
    writetext(DayCareText_GotOddEgg)
    playsound(SFX_KEY_ITEM)
    waitsfx
    writetext(DayCareText_DescribeOddEgg)
    waitbutton
    closetext
    setevent(EVENT_GOT_ODD_EGG)
    s_end
PartyFull:
    opentext
    writetext(DayCareText_PartyFull)
    waitbutton
    closetext
    s_end
AlreadyHaveOddEgg:
    special(DayCareMan)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DayCareLadyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_DAY_CARE_MAN_HAS_EGG)
    iftrue(HusbandWasLookingForYou)
    special(DayCareLady)
    waitbutton
    closetext
    s_end
HusbandWasLookingForYou:
    writetext(Text_GrampsLookingForYou)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DayCareBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s Text_GrampsLookingForYou[] = {
    text_start("Gramps was looking"
        t_line "for you."
        t_done )
};
const txt_cmd_s Text_DayCareManTalksAboutEggTicket[] = {
    text_start("I'm the DAY-CARE"
        t_line "MAN."
        t_para "There's something"
        t_line "new in GOLDENROD"
        t_para "called the TRADE"
        t_line "CORNER."
        t_para "I was given an EGG"
        t_line "TICKET that can be"
        t_para "traded in for a"
        t_line "ODD EGG."
        t_para "But since we run a"
        t_line "DAY-CARE, we don't"
        t_para "need it. You may"
        t_line "as well have it."
        t_done )
};
const txt_cmd_s DayCareManText_GiveOddEgg[] = {
    text_start("I'm the DAY-CARE"
        t_line "MAN."
        t_para "Do you know about"
        t_line "EGGS?"
        t_para "I was raising"
        t_line "#MON with my"
        t_cont "wife, you see."
        t_para "We were shocked to"
        t_line "find an EGG!"
        t_para "How incredible is"
        t_line "that?"
        t_para "Well, wouldn't you"
        t_line "like this EGG?"
        t_para "Then fine, this is"
        t_line "yours to keep!"
        t_done )
};
const txt_cmd_s DayCareText_ComeAgain[] = {
    text_start("Come again."
        t_done )
};
const txt_cmd_s DayCareText_GotOddEgg[] = {
    text_start("<PLAYER> received"
        t_line "ODD EGG!"
        t_done )
};
const txt_cmd_s DayCareText_DescribeOddEgg[] = {
    text_start("I found that when"
        t_line "I was caring for"
        t_para "someone's #MON"
        t_line "before."
        t_para "But the trainer"
        t_line "didn't want the"
        t_para "EGG, so I'd kept"
        t_line "it around."
        t_done )
};
const txt_cmd_s DayCareText_PartyFull[] = {
    text_start("You've no room for"
        t_line "this."
        t_done )
    //db(0, 0) // filler
};
