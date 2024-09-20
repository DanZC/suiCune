#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonPokecenter1F.h"
//// EVENTS
enum {
    CELADONPOKECENTER1F_NURSE = 2,
    CELADONPOKECENTER1F_GENTLEMAN,
    CELADONPOKECENTER1F_PHARMACIST,
    CELADONPOKECENTER1F_COOLTRAINER_F,
    CELADONPOKECENTER1F_EUSINE,
};

const Script_fn_t CeladonPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonPokecenter1F_SceneScripts),
    .scene_scripts = CeladonPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonPokecenter1F_MapCallbacks),
    .callbacks = CeladonPokecenter1F_MapCallbacks,
};

static const struct CoordEvent CeladonPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData CeladonPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, CELADON_CITY, 5),
    warp_event(4, 7, CELADON_CITY, 5),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent CeladonPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonPokecenter1FNurseScript, -1),
    object_event(1, 5, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonPokecenter1FGentlemanScript, -1),
    object_event(0, 3, SPRITE_PHARMACIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonPokecenter1FPharmacistScript, -1),
    object_event(8, 6, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonPokecenter1FCooltrainerFScript, -1),
    object_event(4, 3, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonEusine, EVENT_SET_WHEN_FOUGHT_HO_OH),
};

const struct MapEvents CeladonPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(CeladonPokecenter1F_WarpEvents),
    .warp_events = CeladonPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonPokecenter1F_CoordEvents),
    .coord_events = CeladonPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(CeladonPokecenter1F_BGEvents),
    .bg_events = CeladonPokecenter1F_BGEvents,

    .obj_event_count = lengthof(CeladonPokecenter1F_ObjectEvents),
    .obj_events = CeladonPokecenter1F_ObjectEvents,
};

//// CODE

bool CeladonPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool CeladonPokecenter1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(HappinessCheckScript)
    SCRIPT_END
}
bool CeladonPokecenter1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonPokecenter1FCooltrainerFText)
    SCRIPT_END
}
bool CeladonPokecenter1FPharmacistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonPokecenter1FPharmacistText)
    SCRIPT_END
}
bool CeladonEusine(script_s* s) {
    static const uint8_t Movement2[] = {
        step(LEFT),
        step(DOWN),
        step(DOWN),
        step(DOWN),
        step(DOWN),
        movement_step_end,
    };
    static const uint8_t Movement1[] = {
        step(DOWN),
        step(DOWN),
        step(DOWN),
        step(DOWN),
        movement_step_end,
    };
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonEusineText1)
    promptbutton
    setval(SUICUNE)
    special(MonCheck)
    iffalse(NoSuicune)
    special(BeastsCheck)
    iftrue(HoOh)
    writetext(NoBeastsText)
    waitbutton
NoSuicune:
    closetext
    s_end
HoOh:
    writetext(EusineLeavesCeladonText)
    waitbutton
    closetext
    readvar(VAR_FACING)
    ifequal(UP, Location1)
    applymovement(CELADONPOKECENTER1F_EUSINE, Movement1)
    goto Continue;
Location1:
    applymovement(CELADONPOKECENTER1F_EUSINE, Movement2)
Continue:
    disappear(CELADONPOKECENTER1F_EUSINE)
    playsound(SFX_EXIT_BUILDING)
    waitsfx
    s_end
    SCRIPT_END
}
const txt_cmd_s CeladonPokecenter1FCooltrainerFText[] = {
    text_start("ERIKA is a master"
        t_line "of grass #MON."
        t_para "She'll make you"
        t_line "pay if you don't"
        t_cont "watch yourself."
        t_done )
};
const txt_cmd_s CeladonPokecenter1FPharmacistText[] = {
    text_start("TEAM ROCKET's"
        t_line "hideout is in the"
        t_para "basement of the"
        t_line "GAME CORNER."
        t_para "Oh, wait. That was"
        t_line "three years ago."
        t_done )
};
const txt_cmd_s CeladonEusineText1[] = {
    text_start("EUSINE: Hi!"
        t_para "I'm back visiting"
        t_line "my hometown."
        t_para "It's been quite a"
        t_line "while."
        t_done )
};
const txt_cmd_s EusineLeavesCeladonText[] = {
    text_start("<PLAYER>, have you"
        t_line "heard?"
        t_para "There have been"
        t_line "fresh rumors of a"
        t_para "rainbow-colored"
        t_line "#MON appearing"
        t_cont "at TIN TOWER."
        t_para "I've just had my"
        t_line "party healed, so"
        t_para "now I'm headed to"
        t_line "ECRUTEAK."
        t_para "I'll be seeing"
        t_line "you, <PLAYER>!"
        t_done )
};
const txt_cmd_s NoBeastsText[] = {
    text_start("Oh, by the way,"
        t_line "<PLAYER>."
        t_para "Have you caught"
        t_line "the legendary"
        t_para "#MON RAIKOU and"
        t_line "ENTEI?"
        t_para "<……><……><……>"
        t_para "Okay…"
        t_para "If you catch even"
        t_line "one, I hope that"
        t_cont "you'll inform me."
        t_para "I'm counting on"
        t_line "you, <PLAYER>!"
        t_done )
    //db(0, 0) // filler
};
