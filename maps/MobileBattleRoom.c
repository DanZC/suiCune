#include "../constants.h"
#include "../util/scripting.h"
#include "MobileBattleRoom.h"
//// EVENTS
const Script_fn_t MobileBattleRoom_SceneScripts[] = {
    MobileBattleRoom_MapScripts_InitializeMobileBattleRoom , //  SCENE_DEFAULT,
    MobileBattleRoom_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback MobileBattleRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts MobileBattleRoom_MapScripts = {
    .scene_script_count = lengthof(MobileBattleRoom_SceneScripts),
    .scene_scripts = MobileBattleRoom_SceneScripts,

    .callback_count = 0, // lengthof(MobileBattleRoom_MapCallbacks),
    .callbacks = MobileBattleRoom_MapCallbacks,
};

static const struct CoordEvent MobileBattleRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent MobileBattleRoom_BGEvents[] = {
    bg_event(4, 2, BGEVENT_UP, &MobileBattleRoomConsoleScript),
};

static const struct WarpEventData MobileBattleRoom_WarpEvents[] = {
    warp_event(4, 7, POKECENTER_2F, 6),
    warp_event(5, 7, POKECENTER_2F, 6),
};

static const struct ObjEvent MobileBattleRoom_ObjectEvents[] = {
    0,
};

const struct MapEvents MobileBattleRoom_MapEvents = {
    .warp_event_count = lengthof(MobileBattleRoom_WarpEvents),
    .warp_events = MobileBattleRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(MobileBattleRoom_CoordEvents),
    .coord_events = MobileBattleRoom_CoordEvents,

    .bg_event_count = lengthof(MobileBattleRoom_BGEvents),
    .bg_events = MobileBattleRoom_BGEvents,

    .obj_event_count = 0, // lengthof(MobileBattleRoom_ObjectEvents),
    .obj_events = MobileBattleRoom_ObjectEvents,
};

//// CODE

bool MobileBattleRoom_MapScripts_InitializeMobileBattleRoom(script_s* s) {
    SCRIPT_BEGIN
    sdefer(MobileBattleRoom_MapScripts_InitializeAndPreparePokecenter2F);
    s_end
    SCRIPT_END
}
bool MobileBattleRoom_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool MobileBattleRoom_MapScripts_InitializeAndPreparePokecenter2F(script_s* s) {
    SCRIPT_BEGIN
    setscene(SCENE_FINISHED)
    setmapscene(POKECENTER_2F, SCENE_POKECENTER2F_LEAVE_MOBILE_BATTLE_ROOM)
    s_end
    SCRIPT_END
}
bool MobileBattleRoomConsoleScript(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    special(Function1037c2)
    ifequal(0x1, one)
    special(Function1037eb)
    iffalse(false_)
    ifequal(0x1, one_)
    ifequal(0x2, two_)
    goto false_;
one_:
    writetext(MobileBattleRoom_HealText)
    pause(20)
    closetext
    special(FadeOutPalettes)
    playmusic(MUSIC_HEAL)
    special(LoadMapPalettes)
    pause(60)
    special(FadeInPalettes)
    special(RestartMapMusic)
    refreshscreen
two_:
    special(StubbedTrainerRankings_Healings)
    special(HealParty)
    special(Function10383c)
    iftrue(false_)
one:
    special(Function10387b)
    writetext(MobileBattleRoom_EstablishingCommsText)
    waitbutton
    reloadmappart
    special(Function101225)
false_:
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s MobileBattleRoom_EstablishingCommsText[] = {
    text_start("Establishing"
        t_line "communications…"
        t_done )
};
const txt_cmd_s MobileBattleRoom_HealText[] = {
    text_start("Your #MON will"
        t_line "be fully healed"
        t_cont "before battle."
        t_done )
    //db(0, 0) // filler
};
