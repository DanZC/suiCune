#include "../constants.h"
#include "../util/scripting.h"
#include "SeafoamGym.h"
//// EVENTS
enum {
    SEAFOAMGYM_BLAINE = 2,
    SEAFOAMGYM_GYM_GUIDE,
};

const Script_fn_t SeafoamGym_SceneScripts[] = {
    SeafoamGym_MapScripts_DummyScene,
};

const struct MapCallback SeafoamGym_MapCallbacks[] = {
    0,
};

const struct MapScripts SeafoamGym_MapScripts = {
    .scene_script_count = lengthof(SeafoamGym_SceneScripts),
    .scene_scripts = SeafoamGym_SceneScripts,

    .callback_count = 0, // lengthof(SeafoamGym_MapCallbacks),
    .callbacks = SeafoamGym_MapCallbacks,
};

static const struct CoordEvent SeafoamGym_CoordEvents[] = {
    0,
};

static const struct BGEvent SeafoamGym_BGEvents[] = {
    0,
};

static const struct WarpEventData SeafoamGym_WarpEvents[] = {
    warp_event(5, 5, ROUTE_20, 1),
};

static const struct ObjEvent SeafoamGym_ObjectEvents[] = {
    object_event(5, 2, SPRITE_BLAINE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &SeafoamGymBlaineScript, -1),
    object_event(6, 5, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SeafoamGymGuideScript, EVENT_SEAFOAM_GYM_GYM_GUIDE),
};

const struct MapEvents SeafoamGym_MapEvents = {
    .warp_event_count = lengthof(SeafoamGym_WarpEvents),
    .warp_events = SeafoamGym_WarpEvents,

    .coord_event_count = 0, // lengthof(SeafoamGym_CoordEvents),
    .coord_events = SeafoamGym_CoordEvents,

    .bg_event_count = 0, // lengthof(SeafoamGym_BGEvents),
    .bg_events = SeafoamGym_BGEvents,

    .obj_event_count = lengthof(SeafoamGym_ObjectEvents),
    .obj_events = SeafoamGym_ObjectEvents,
};

//// CODE

bool SeafoamGym_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool SeafoamGymBlaineScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_VOLCANOBADGE)
    iftrue(FightDone)
    writetext(BlaineIntroText)
    waitbutton
    closetext
    winlosstext(BlaineWinLossText, 0)
    loadtrainer(BLAINE, BLAINE1)
    startbattle
    iftrue(ReturnAfterBattle)
    appear(SEAFOAMGYM_GYM_GUIDE)
ReturnAfterBattle:
    reloadmapafterbattle
    setevent(EVENT_BEAT_BLAINE)
    opentext
    writetext(ReceivedVolcanoBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_VOLCANOBADGE)
    writetext(BlaineAfterBattleText)
    waitbutton
    closetext
    s_end
FightDone:
    writetext(BlaineFightDoneText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SeafoamGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TALKED_TO_SEAFOAM_GYM_GUIDE_ONCE)
    iftrue(TalkedToSeafoamGymGuideScript)
    writetext(SeafoamGymGuideWinText)
    waitbutton
    closetext
    setevent(EVENT_TALKED_TO_SEAFOAM_GYM_GUIDE_ONCE)
    s_end
TalkedToSeafoamGymGuideScript:
    writetext(SeafoamGymGuideWinText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s BlaineIntroText[] = {
    text_start("BLAINE: Waaah!"
        t_para "My GYM in CINNABAR"
        t_line "burned down."
        t_para "My fire-breathing"
        t_line "#MON and I are"
        t_para "homeless because"
        t_line "of the volcano."
        t_para "Waaah!"
        t_para "But I'm back in"
        t_line "business as a GYM"
        t_para "LEADER here in"
        t_line "this cave."
        t_para "If you can beat"
        t_line "me, I'll give you"
        t_cont "a BADGE."
        t_para "Ha! You'd better"
        t_line "have BURN HEAL!"
        t_done )
};
const txt_cmd_s BlaineWinLossText[] = {
    text_start("BLAINE: Awesome."
        t_line "I've burned out…"
        t_para "You've earned"
        t_line "VOLCANOBADGE!"
        t_done )
};
const txt_cmd_s ReceivedVolcanoBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "VOLCANOBADGE."
        t_done )
};
const txt_cmd_s BlaineAfterBattleText[] = {
    text_start("BLAINE: I did lose"
        t_line "this time, but I'm"
        t_para "going to win the"
        t_line "next time."
        t_para "When I rebuild my"
        t_line "CINNABAR GYM,"
        t_para "we'll have to have"
        t_line "a rematch."
        t_done )
};
const txt_cmd_s BlaineFightDoneText[] = {
    text_start("BLAINE: My fire"
        t_line "#MON will be"
        t_para "even stronger."
        t_line "Just you watch!"
        t_done )
};
const txt_cmd_s SeafoamGymGuideWinText[] = {
    text_start("Yo!"
        t_para "… Huh? It's over"
        t_line "already?"
        t_para "Sorry, sorry!"
        t_para "CINNABAR GYM was"
        t_line "gone, so I didn't"
        t_para "know where to find"
        t_line "you."
        t_para "But, hey, you're"
        t_line "plenty strong even"
        t_para "without my advice."
        t_line "I knew you'd win!"
        t_done )
};
const txt_cmd_s SeafoamGymGuideWinText2[] = {
    text_start("A #MON GYM can"
        t_line "be anywhere as"
        t_para "long as the GYM"
        t_line "LEADER is there."
        t_para "There's no need"
        t_line "for a building."
        t_done )
    //db(0, 0) // filler
};
