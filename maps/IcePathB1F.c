#include "../constants.h"
#include "../util/scripting.h"
#include "IcePathB1F.h"
//// EVENTS
enum {
    ICEPATHB1F_BOULDER1 = 2,
    ICEPATHB1F_BOULDER2,
    ICEPATHB1F_BOULDER3,
    ICEPATHB1F_BOULDER4,
    ICEPATHB1F_POKE_BALL,
};

const Script_fn_t IcePathB1F_SceneScripts[] = {
    0,
};

const struct MapCallback IcePathB1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_CMDQUEUE, IcePathB1F_MapScripts_SetUpStoneTable),
};

const struct MapScripts IcePathB1F_MapScripts = {
    .scene_script_count = 0, // lengthof(IcePathB1F_SceneScripts),
    .scene_scripts = IcePathB1F_SceneScripts,

    .callback_count = lengthof(IcePathB1F_MapCallbacks),
    .callbacks = IcePathB1F_MapCallbacks,
};

static const struct CoordEvent IcePathB1F_CoordEvents[] = {
    0,
};

static const struct BGEvent IcePathB1F_BGEvents[] = {
    bg_event(17, 30, BGEVENT_ITEM, &IcePathB1FHiddenMaxPotion),
};

static const struct WarpEventData IcePathB1F_WarpEvents[] = {
    warp_event(3, 15, ICE_PATH_1F, 3),
    warp_event(17, 3, ICE_PATH_B2F_MAHOGANY_SIDE, 1),
    warp_event(11, 2, ICE_PATH_B2F_MAHOGANY_SIDE, 3), // hole
    warp_event(4, 7, ICE_PATH_B2F_MAHOGANY_SIDE, 4), // hole
    warp_event(5, 12, ICE_PATH_B2F_MAHOGANY_SIDE, 5), // hole
    warp_event(12, 13, ICE_PATH_B2F_MAHOGANY_SIDE, 6), // hole
    warp_event(5, 25, ICE_PATH_1F, 4),
    warp_event(11, 27, ICE_PATH_B2F_BLACKTHORN_SIDE, 1),
};

static const struct ObjEvent IcePathB1F_ObjectEvents[] = {
    object_event(11, 7, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB1FBoulder, EVENT_BOULDER_IN_ICE_PATH_1),
    object_event(7, 8, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB1FBoulder, EVENT_BOULDER_IN_ICE_PATH_2),
    object_event(8, 9, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB1FBoulder, EVENT_BOULDER_IN_ICE_PATH_3),
    object_event(17, 7, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB1FBoulder, EVENT_BOULDER_IN_ICE_PATH_4),
    object_event(5, 35, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IcePathB1FIron, EVENT_ICE_PATH_B1F_IRON),
};

const struct MapEvents IcePathB1F_MapEvents = {
    .warp_event_count = lengthof(IcePathB1F_WarpEvents),
    .warp_events = IcePathB1F_WarpEvents,

    .coord_event_count = 0, // lengthof(IcePathB1F_CoordEvents),
    .coord_events = IcePathB1F_CoordEvents,

    .bg_event_count = lengthof(IcePathB1F_BGEvents),
    .bg_events = IcePathB1F_BGEvents,

    .obj_event_count = lengthof(IcePathB1F_ObjectEvents),
    .obj_events = IcePathB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "IcePathB1F.h"

bool IcePathB1F_MapScripts_SetUpStoneTable(script_s* s) {
    SCRIPT_BEGIN
    writecmdqueue(IcePathB1F_MapScripts_CommandQueue)
    s_endcallback
    SCRIPT_END
}
const struct CmdQueue IcePathB1F_MapScripts_CommandQueue[] = {
    cmdqueue(CMDQUEUE_STONETABLE, IcePathB1F_MapScripts_StoneTable) // check if any stones are sitting on a warp
};
const struct Stonetable IcePathB1F_MapScripts_StoneTable[] = {
    stonetable(3, ICEPATHB1F_BOULDER1, IcePathB1F_MapScripts_Boulder1),
    stonetable(4, ICEPATHB1F_BOULDER2, IcePathB1F_MapScripts_Boulder2),
    stonetable(5, ICEPATHB1F_BOULDER3, IcePathB1F_MapScripts_Boulder3),
    stonetable(6, ICEPATHB1F_BOULDER4, IcePathB1F_MapScripts_Boulder4),
    //db(-1) // end
    {-1, 0, 0},
};
bool IcePathB1F_MapScripts_Boulder1(script_s* s) {
    SCRIPT_BEGIN
    disappear(ICEPATHB1F_BOULDER1)
    clearevent(EVENT_BOULDER_IN_ICE_PATH_1A)
    sjump(IcePathB1F_MapScripts_FinishBoulder)
    SCRIPT_END
}
bool IcePathB1F_MapScripts_Boulder2(script_s* s) {
    SCRIPT_BEGIN
    disappear(ICEPATHB1F_BOULDER2)
    clearevent(EVENT_BOULDER_IN_ICE_PATH_2A)
    sjump(IcePathB1F_MapScripts_FinishBoulder)
    SCRIPT_END
}
bool IcePathB1F_MapScripts_Boulder3(script_s* s) {
    SCRIPT_BEGIN
    disappear(ICEPATHB1F_BOULDER3)
    clearevent(EVENT_BOULDER_IN_ICE_PATH_3A)
    sjump(IcePathB1F_MapScripts_FinishBoulder)
    SCRIPT_END
}
bool IcePathB1F_MapScripts_Boulder4(script_s* s) {
    SCRIPT_BEGIN
    disappear(ICEPATHB1F_BOULDER4)
    clearevent(EVENT_BOULDER_IN_ICE_PATH_4A)
    sjump(IcePathB1F_MapScripts_FinishBoulder)
    SCRIPT_END
}
bool IcePathB1F_MapScripts_FinishBoulder(script_s* s) {
    SCRIPT_BEGIN
    pause(30)
    scall_local(BoulderFallsThrough);
    opentext
    writetext(IcePathBoulderFellThroughText)
    waitbutton
    closetext
    s_end
BoulderFallsThrough:
    playsound(SFX_STRENGTH)
    earthquake(80)
    s_end
    SCRIPT_END
}
bool IcePathB1FBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
const struct ItemBall IcePathB1FIron = {IRON, 1};
const struct HiddenItem IcePathB1FHiddenMaxPotion = {MAX_POTION, EVENT_ICE_PATH_B1F_HIDDEN_MAX_POTION};
const txt_cmd_s IcePathBoulderFellThroughText[] = {
    text_start("The boulder fell"
        t_line "through."
        t_done )
    //db(0, 0) // filler
};
