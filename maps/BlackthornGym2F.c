#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornGym2F.h"
//// EVENTS
enum {
    BLACKTHORNGYM2F_COOLTRAINER_M = 2,
    BLACKTHORNGYM2F_COOLTRAINER_F,
    BLACKTHORNGYM2F_BOULDER1,
    BLACKTHORNGYM2F_BOULDER2,
    BLACKTHORNGYM2F_BOULDER3,
    BLACKTHORNGYM2F_BOULDER4,
    BLACKTHORNGYM2F_BOULDER5,
    BLACKTHORNGYM2F_BOULDER6,
};

const Script_fn_t BlackthornGym2F_SceneScripts[] = {
    0,
};

const struct MapCallback BlackthornGym2F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_CMDQUEUE, BlackthornGym2F_MapScripts_SetUpStoneTable),
};

const struct MapScripts BlackthornGym2F_MapScripts = {
    .scene_script_count = 0, // lengthof(BlackthornGym2F_SceneScripts),
    .scene_scripts = BlackthornGym2F_SceneScripts,

    .callback_count = lengthof(BlackthornGym2F_MapCallbacks),
    .callbacks = BlackthornGym2F_MapCallbacks,
};

static const struct CoordEvent BlackthornGym2F_CoordEvents[] = {
    0,
};

static const struct BGEvent BlackthornGym2F_BGEvents[] = {
    0,
};

static const struct WarpEventData BlackthornGym2F_WarpEvents[] = {
    warp_event(1, 7, BLACKTHORN_GYM_1F, 3),
    warp_event(7, 9, BLACKTHORN_GYM_1F, 4),
    warp_event(2, 5, BLACKTHORN_GYM_1F, 5), // hole
    warp_event(8, 7, BLACKTHORN_GYM_1F, 6), // hole
    warp_event(8, 3, BLACKTHORN_GYM_1F, 7), // hole
};

static const struct ObjEvent BlackthornGym2F_ObjectEvents[] = {
    object_event(4, 1, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerCooltrainermCody, -1),
    object_event(4, 11, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerCooltrainerfFran, -1),
    object_event(8, 2, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornGymBoulder, EVENT_BOULDER_IN_BLACKTHORN_GYM_1),
    object_event(2, 3, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornGymBoulder, EVENT_BOULDER_IN_BLACKTHORN_GYM_2),
    object_event(6, 16, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornGymBoulder, EVENT_BOULDER_IN_BLACKTHORN_GYM_3),
    object_event(3, 3, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornGymBoulder, -1),
    object_event(6, 1, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornGymBoulder, -1),
    object_event(8, 14, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornGymBoulder, -1),
};

const struct MapEvents BlackthornGym2F_MapEvents = {
    .warp_event_count = lengthof(BlackthornGym2F_WarpEvents),
    .warp_events = BlackthornGym2F_WarpEvents,

    .coord_event_count = 0, // lengthof(BlackthornGym2F_CoordEvents),
    .coord_events = BlackthornGym2F_CoordEvents,

    .bg_event_count = 0, // lengthof(BlackthornGym2F_BGEvents),
    .bg_events = BlackthornGym2F_BGEvents,

    .obj_event_count = lengthof(BlackthornGym2F_ObjectEvents),
    .obj_events = BlackthornGym2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornGym2F.h"

bool BlackthornGym2F_MapScripts_SetUpStoneTable(script_s* s) {
    SCRIPT_BEGIN
    writecmdqueue(BlackthornGym2F_MapScripts_CommandQueue)
    s_endcallback
    SCRIPT_END
}
const struct CmdQueue BlackthornGym2F_MapScripts_CommandQueue[] = {
    cmdqueue(CMDQUEUE_STONETABLE, BlackthornGym2F_MapScripts_StoneTable) // check if any stones are sitting on a warp
};
const struct Stonetable BlackthornGym2F_MapScripts_StoneTable[] = {
    stonetable(5, BLACKTHORNGYM2F_BOULDER1, BlackthornGym2F_MapScripts_Boulder1),
    stonetable(3, BLACKTHORNGYM2F_BOULDER2, BlackthornGym2F_MapScripts_Boulder2),
    stonetable(4, BLACKTHORNGYM2F_BOULDER3, BlackthornGym2F_MapScripts_Boulder3),
    {-1, 0, 0},
    //db(-1) // end
};
bool BlackthornGym2F_MapScripts_Boulder1(script_s* s) {
    SCRIPT_BEGIN
    disappear(BLACKTHORNGYM2F_BOULDER1)
    sjump(BlackthornGym2F_MapScripts_Fall)
    SCRIPT_END
}
bool BlackthornGym2F_MapScripts_Boulder2(script_s* s) {
    SCRIPT_BEGIN
    disappear(BLACKTHORNGYM2F_BOULDER2)
    sjump(BlackthornGym2F_MapScripts_Fall)
    SCRIPT_END
}
bool BlackthornGym2F_MapScripts_Boulder3(script_s* s) {
    SCRIPT_BEGIN
    disappear(BLACKTHORNGYM2F_BOULDER3)
    sjump(BlackthornGym2F_MapScripts_Fall)
    SCRIPT_END
}
bool BlackthornGym2F_MapScripts_Fall(script_s* s) {
    SCRIPT_BEGIN
    pause(30)
    scall(BlackthornGym2F_MapScripts_FX);
    opentext
    writetext(BlackthornGym2FBoulderFellText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BlackthornGym2F_MapScripts_FX(script_s* s) {
    SCRIPT_BEGIN
    playsound(SFX_STRENGTH)
    earthquake(80)
    s_end
    SCRIPT_END
}
bool BlackthornGymBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermCody = {COOLTRAINERM, CODY, EVENT_BEAT_COOLTRAINERM_CODY, CooltrainermCodySeenText, CooltrainermCodyBeatenText, 0, TrainerCooltrainermCody_Script};
bool TrainerCooltrainermCody_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermCodyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfFran = {COOLTRAINERF, FRAN, EVENT_BEAT_COOLTRAINERF_FRAN, CooltrainerfFranSeenText, CooltrainerfFranBeatenText, 0, TrainerCooltrainerfFran_Script};
bool TrainerCooltrainerfFran_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfFranAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s CooltrainermCodySeenText[] = {
    text_start("It's not as if we"
        t_line "all use dragon-"
        t_cont "type #MON."
        t_done )
};
const txt_cmd_s CooltrainermCodyBeatenText[] = {
    text_start("Rats! If only I"
        t_line "had a dragon!"
        t_done )
};
const txt_cmd_s CooltrainermCodyAfterBattleText[] = {
    text_start("Members of our"
        t_line "dragon-user clan"
        t_para "can use dragon"
        t_line "#MON only after"
        t_para "our MASTER allows"
        t_line "it."
        t_done )
};
const txt_cmd_s CooltrainerfFranSeenText[] = {
    text_start("I can't allow a"
        t_line "nameless trainer"
        t_cont "past me!"
        t_para "CLAIR would be"
        t_line "livid if I did!"
        t_done )
};
const txt_cmd_s CooltrainerfFranBeatenText[] = {
    text_start("Awww… I lost…"
        t_done )
};
const txt_cmd_s CooltrainerfFranAfterBattleText[] = {
    text_start("Uh-oh… CLAIR is"
        t_line "going to be mad…"
        t_done )
};
const txt_cmd_s BlackthornGym2FBoulderFellText[] = {
    text_start("The boulder fell"
        t_line "through!"
        t_done )
    //db(0, 0) // filler
};
