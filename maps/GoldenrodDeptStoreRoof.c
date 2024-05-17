#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStoreRoof.h"
//// EVENTS
enum {
    GOLDENRODDEPTSTOREROOF_CLERK = 2,
    GOLDENRODDEPTSTOREROOF_POKEFAN_F,
    GOLDENRODDEPTSTOREROOF_FISHER,
    GOLDENRODDEPTSTOREROOF_TWIN,
    GOLDENRODDEPTSTOREROOF_SUPER_NERD,
    GOLDENRODDEPTSTOREROOF_POKEFAN_M,
    GOLDENRODDEPTSTOREROOF_TEACHER,
    GOLDENRODDEPTSTOREROOF_BUG_CATCHER,
};

const Script_fn_t GoldenrodDeptStoreRoof_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStoreRoof_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, GoldenrodDeptStoreRoof_MapScripts_CheckSaleChangeBlock),
    map_callback(MAPCALLBACK_OBJECTS, GoldenrodDeptStoreRoof_MapScripts_CheckSaleChangeClerk),
};

const struct MapScripts GoldenrodDeptStoreRoof_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStoreRoof_SceneScripts),
    .scene_scripts = GoldenrodDeptStoreRoof_SceneScripts,

    .callback_count = lengthof(GoldenrodDeptStoreRoof_MapCallbacks),
    .callbacks = GoldenrodDeptStoreRoof_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStoreRoof_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStoreRoof_BGEvents[] = {
    bg_event(15, 3, BGEVENT_RIGHT, &Binoculars1),
    bg_event(15, 5, BGEVENT_RIGHT, &Binoculars2),
    bg_event(15, 6, BGEVENT_RIGHT, &Binoculars3),
    bg_event(3, 0, BGEVENT_UP, &PokeDollVendingMachine),
};

static const struct WarpEventData GoldenrodDeptStoreRoof_WarpEvents[] = {
    warp_event(13, 1, GOLDENROD_DEPT_STORE_6F, 3),
};

static const struct ObjEvent GoldenrodDeptStoreRoof_ObjectEvents[] = {
    object_event(1, 4, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreRoofClerkScript, EVENT_GOLDENROD_SALE_OFF),
    object_event(10, 3, SPRITE_POKEFAN_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreRoofPokefanFScript, -1),
    object_event(2, 1, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreRoofFisherScript, -1),
    object_event(3, 4, SPRITE_TWIN, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreRoofTwinScript, EVENT_GOLDENROD_SALE_ON),
    object_event(14, 6, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreRoofSuperNerdScript, EVENT_GOLDENROD_SALE_ON),
    object_event(7, 0, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreRoofPokefanMScript, EVENT_GOLDENROD_SALE_OFF),
    object_event(5, 3, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreRoofTeacherScript, EVENT_GOLDENROD_SALE_OFF),
    object_event(1, 6, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStoreRoofBugCatcherScript, EVENT_GOLDENROD_SALE_OFF),
};

const struct MapEvents GoldenrodDeptStoreRoof_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStoreRoof_WarpEvents),
    .warp_events = GoldenrodDeptStoreRoof_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStoreRoof_CoordEvents),
    .coord_events = GoldenrodDeptStoreRoof_CoordEvents,

    .bg_event_count = lengthof(GoldenrodDeptStoreRoof_BGEvents),
    .bg_events = GoldenrodDeptStoreRoof_BGEvents,

    .obj_event_count = lengthof(GoldenrodDeptStoreRoof_ObjectEvents),
    .obj_events = GoldenrodDeptStoreRoof_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStoreRoof.h"

bool GoldenrodDeptStoreRoof_MapScripts_CheckSaleChangeBlock(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON)
    iftrue(SaleIsOn)
    s_endcallback
SaleIsOn:
    changeblock(0, 2, 0x3f) // cardboard boxes
    changeblock(0, 4, 0x0f) // vendor booth
    s_endcallback
    SCRIPT_END
}
bool GoldenrodDeptStoreRoof_MapScripts_CheckSaleChangeClerk(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON)
    iftrue(ChangeClerk)
    setevent(EVENT_GOLDENROD_SALE_OFF)
    clearevent(EVENT_GOLDENROD_SALE_ON)
    s_endcallback
ChangeClerk:
    clearevent(EVENT_GOLDENROD_SALE_OFF)
    setevent(EVENT_GOLDENROD_SALE_ON)
    s_endcallback
    SCRIPT_END
}
bool GoldenrodDeptStoreRoofClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_ROOFTOP, 0)
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStoreRoofPokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStoreRoofPokefanFText)
    SCRIPT_END
}
bool GoldenrodDeptStoreRoofFisherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodDeptStoreRoofFisherText)
    waitbutton
    closetext
    turnobject(GOLDENRODDEPTSTOREROOF_FISHER, UP)
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStoreRoofTwinScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStoreRoofTwinText)
    SCRIPT_END
}
bool GoldenrodDeptStoreRoofSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(GoldenrodDeptStoreRoofSuperNerdOhWowText)
    waitbutton
    closetext
    turnobject(GOLDENRODDEPTSTOREROOF_SUPER_NERD, UP)
    opentext
    writetext(GoldenrodDeptStoreRoofSuperNerdQuitBotheringMeText)
    waitbutton
    closetext
    turnobject(GOLDENRODDEPTSTOREROOF_SUPER_NERD, RIGHT)
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStoreRoofPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStoreRoofPokefanMText)
    SCRIPT_END
}
bool GoldenrodDeptStoreRoofTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStoreRoofTeacherText)
    SCRIPT_END
}
bool GoldenrodDeptStoreRoofBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStoreRoofBugCatcherText)
    SCRIPT_END
}
bool Binoculars1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Binoculars1Text)
    SCRIPT_END
}
bool Binoculars2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Binoculars2Text)
    SCRIPT_END
}
bool Binoculars3(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Binoculars3Text)
    SCRIPT_END
}
bool PokeDollVendingMachine(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PokeDollVendingMachineText)
    SCRIPT_END
}
const txt_cmd_s GoldenrodDeptStoreRoofPokefanFText[] = {
    text_start("Whew, I'm tired."
        t_para "I sometimes come"
        t_line "up to the rooftop"
        t_para "to take a break"
        t_line "from shopping."
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreRoofFisherText[] = {
    text_start("Pardon? Who says"
        t_line "an adult can't get"
        t_cont "into this?"
        t_para "I'm going to be"
        t_line "back every day to"
        t_para "collect all the"
        t_line "dolls!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreRoofTwinText[] = {
    text_start("They have bargain"
        t_line "sales here every"
        t_cont "so often."
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreRoofSuperNerdOhWowText[] = {
    text_start("Oh, wow!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreRoofSuperNerdQuitBotheringMeText[] = {
    text_start("Will you quit"
        t_line "bothering me?"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreRoofPokefanMText[] = {
    text_start("There's something"
        t_line "I really want, but"
        t_para "I don't have the"
        t_line "necessary cash…"
        t_para "Maybe I'll sell"
        t_line "off the BERRIES"
        t_cont "I've collected…"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreRoofTeacherText[] = {
    text_start("Oh, everything is"
        t_line "so cheap!"
        t_para "I bought so much,"
        t_line "my PACK's crammed!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreRoofBugCatcherText[] = {
    text_start("My #MON always"
        t_line "get paralyzed or"
        t_para "poisoned when the"
        t_line "chips are down…"
        t_para "So I came to buy"
        t_line "some FULL HEAL."
        t_para "I wonder if"
        t_line "there's any left?"
        t_done )
};
const txt_cmd_s Binoculars1Text[] = {
    text_start("These binoculars"
        t_line "let me see far"
        t_para "away. Maybe I can"
        t_line "see my own house."
        t_para "Is it the one with"
        t_line "the green roof?"
        t_done )
};
const txt_cmd_s Binoculars2Text[] = {
    text_start("Hey! Some trainers"
        t_line "are battling on"
        t_cont "the road!"
        t_para "A #MON fired a"
        t_line "flurry of leaves!"
        t_para "That makes me feel"
        t_line "like battling"
        t_cont "right now!"
        t_done )
};
const txt_cmd_s Binoculars3Text[] = {
    text_start("A FISHER caught a"
        t_line "lot of MAGIKARP…"
        t_para "They're SPLASHing"
        t_line "at the same time!"
        t_para "Look at the water"
        t_line "going everywhere!"
        t_done )
};
const txt_cmd_s PokeDollVendingMachineText[] = {
    text_start("A vending machine"
        t_line "for #MON dolls?"
        t_para "Insert money, then"
        t_line "turn the crank…"
        t_para "But it's almost"
        t_line "empty…"
        t_done )
    //db(0, 0) // filler
};
