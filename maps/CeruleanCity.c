#include "../constants.h"
#include "../util/scripting.h"
#include "CeruleanCity.h"
//// EVENTS
enum {
    CERULEANCITY_COOLTRAINER_M = 2,
    CERULEANCITY_SUPER_NERD,
    CERULEANCITY_SLOWPOKE,
    CERULEANCITY_COOLTRAINER_F,
    CERULEANCITY_FISHER,
    CERULEANCITY_YOUNGSTER,
};

const Script_fn_t CeruleanCity_SceneScripts[] = {
    0,
};

const struct MapCallback CeruleanCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, CeruleanCity_MapScripts_FlyPoint),
};

const struct MapScripts CeruleanCity_MapScripts = {
    .scene_script_count = 0, // lengthof(CeruleanCity_SceneScripts),
    .scene_scripts = CeruleanCity_SceneScripts,

    .callback_count = lengthof(CeruleanCity_MapCallbacks),
    .callbacks = CeruleanCity_MapCallbacks,
};

static const struct CoordEvent CeruleanCity_CoordEvents[] = {
    0,
};

static const struct BGEvent CeruleanCity_BGEvents[] = {
    bg_event(23, 23, BGEVENT_READ, &CeruleanCitySign),
    bg_event(27, 25, BGEVENT_READ, &CeruleanGymSign),
    bg_event(11, 29, BGEVENT_READ, &CeruleanBikeShopSign),
    bg_event(25, 17, BGEVENT_READ, &CeruleanPoliceSign),
    bg_event(23, 7, BGEVENT_READ, &CeruleanCapeSign),
    bg_event(14, 29, BGEVENT_READ, &CeruleanLockedDoor),
    bg_event(20, 21, BGEVENT_READ, &CeruleanCityPokecenterSign),
    bg_event(26, 29, BGEVENT_READ, &CeruleanCityMartSign),
    bg_event(2, 12, BGEVENT_ITEM, &CeruleanCityHiddenBerserkGene),
};

static const struct WarpEventData CeruleanCity_WarpEvents[] = {
    warp_event(7, 15, CERULEAN_GYM_BADGE_SPEECH_HOUSE, 1),
    warp_event(28, 17, CERULEAN_POLICE_STATION, 1),
    warp_event(13, 19, CERULEAN_TRADE_SPEECH_HOUSE, 1),
    warp_event(19, 21, CERULEAN_POKECENTER_1F, 1),
    warp_event(30, 23, CERULEAN_GYM, 1),
    warp_event(25, 29, CERULEAN_MART, 2),
};

static const struct ObjEvent CeruleanCity_ObjectEvents[] = {
    object_event(15, 23, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeruleanCityCooltrainerMScript, -1),
    object_event(23, 15, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeruleanCitySuperNerdScript, -1),
    object_event(20, 24, SPRITE_SLOWPOKE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeruleanCitySlowbro, -1),
    object_event(21, 24, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeruleanCityCooltrainerFScript, -1),
    object_event(30, 26, SPRITE_FISHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeruleanCityFisherScript, -1),
    object_event(6, 12, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeruleanCityYoungsterScript, -1),
};

const struct MapEvents CeruleanCity_MapEvents = {
    .warp_event_count = lengthof(CeruleanCity_WarpEvents),
    .warp_events = CeruleanCity_WarpEvents,

    .coord_event_count = 0, // lengthof(CeruleanCity_CoordEvents),
    .coord_events = CeruleanCity_CoordEvents,

    .bg_event_count = lengthof(CeruleanCity_BGEvents),
    .bg_events = CeruleanCity_BGEvents,

    .obj_event_count = lengthof(CeruleanCity_ObjectEvents),
    .obj_events = CeruleanCity_ObjectEvents,
};

//// CODE

bool CeruleanCity_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_CERULEAN)
    s_endcallback
    SCRIPT_END
}
bool CeruleanCityCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(CeruleanCityCooltrainerMText1)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(CeruleanCityCooltrainerMText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanCitySuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanCitySuperNerdText)
    SCRIPT_END
}
bool CeruleanCitySlowbro(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeruleanCitySlowbroText)
    playcry(SLOWBRO)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanCityCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeruleanCityCooltrainerFText1)
    waitbutton
    closetext
    turnobject(CERULEANCITY_COOLTRAINER_F, LEFT)
    opentext
    writetext(CeruleanCityCooltrainerFText2)
    waitbutton
    closetext
    opentext
    writetext(CeruleanCitySlowbroText)
    playcry(SLOWBRO)
    waitbutton
    closetext
    opentext
    writetext(CeruleanCityCooltrainerFText3)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanCityFisherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    checkevent(EVENT_MET_ROCKET_GRUNT_AT_CERULEAN_GYM)
    iftrue(MetCeruleanRocket)
ReturnedMachinePart:
    writetext(CeruleanCityFisherText)
    waitbutton
    closetext
    s_end
MetCeruleanRocket:
    writetext(CeruleanCityFisherRocketTipText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanCityYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeruleanCityYoungsterText1)
    waitbutton
    closetext
    checkevent(EVENT_FOUND_BERSERK_GENE_IN_CERULEAN_CITY)
    iffalse(BerserkGenePingsItemfinder)
    s_end
BerserkGenePingsItemfinder:
    waitsfx
    playsound(SFX_SECOND_PART_OF_ITEMFINDER)
    waitsfx
    playsound(SFX_TRANSACTION)
    waitsfx
    playsound(SFX_SECOND_PART_OF_ITEMFINDER)
    waitsfx
    playsound(SFX_TRANSACTION)
    waitsfx
    playsound(SFX_SECOND_PART_OF_ITEMFINDER)
    waitsfx
    playsound(SFX_TRANSACTION)
    waitsfx
    playsound(SFX_SECOND_PART_OF_ITEMFINDER)
    waitsfx
    playsound(SFX_TRANSACTION)
    waitsfx
    showemote(EMOTE_SHOCK, CERULEANCITY_YOUNGSTER, 15)
    turnobject(CERULEANCITY_YOUNGSTER, LEFT)
    opentext
    writetext(CeruleanCityYoungsterText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeruleanCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeruleanCitySignText)
    SCRIPT_END
}
bool CeruleanGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeruleanGymSignText)
    SCRIPT_END
}
bool CeruleanBikeShopSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeruleanBikeShopSignText)
    SCRIPT_END
}
bool CeruleanPoliceSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeruleanPoliceSignText)
    SCRIPT_END
}
bool CeruleanCapeSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeruleanCapeSignText)
    SCRIPT_END
}
bool CeruleanLockedDoor(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeruleanLockedDoorText)
    SCRIPT_END
}
bool CeruleanCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool CeruleanCityMartSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const struct HiddenItem CeruleanCityHiddenBerserkGene = {BERSERK_GENE, EVENT_FOUND_BERSERK_GENE_IN_CERULEAN_CITY};
const txt_cmd_s CeruleanCityCooltrainerMText1[] = {
    text_start("KANTO's POWER"
        t_line "PLANT?"
        t_para "It's near the end"
        t_line "of ROUTE 9, the"
        t_para "road that heads"
        t_line "east from here."
        t_para "I think there was"
        t_line "an accident of"
        t_cont "some sort there."
        t_done )
};
const txt_cmd_s CeruleanCityCooltrainerMText2[] = {
    text_start("You're collecting"
        t_line "every single kind"
        t_cont "of #MON?"
        t_para "That must be quite"
        t_line "a challenge, but"
        t_cont "it sounds fun too."
        t_done )
};
const txt_cmd_s CeruleanCitySuperNerdText[] = {
    text_start("The CAPE in the"
        t_line "north is a good"
        t_para "place for dates."
        t_line "Girls like it!"
        t_done )
};
const txt_cmd_s CeruleanCitySlowbroText[] = {
    text_start("SLOWBRO: Yarah?"
        t_done )
};
const txt_cmd_s CeruleanCityCooltrainerFText1[] = {
    text_start("My SLOWBRO and I"
        t_line "make an awesome"
        t_cont "combination!"
        t_done )
};
const txt_cmd_s CeruleanCityCooltrainerFText2[] = {
    text_start("SLOWBRO, show me"
        t_line "your CONFUSION!"
        t_done )
};
const txt_cmd_s CeruleanCityCooltrainerFText3[] = {
    text_start("…"
        t_done )
};
const txt_cmd_s CeruleanCityFisherText[] = {
    text_start("I'm a huge fan of"
        t_line "CERULEAN GYM's"
        t_cont "MISTY."
        t_done )
};
const txt_cmd_s CeruleanCityFisherRocketTipText[] = {
    text_start("I saw this shady"
        t_line "guy go off toward"
        t_cont "CERULEAN's CAPE."
        t_done )
};
const txt_cmd_s CeruleanCityYoungsterText1[] = {
    text_start("There used to be a"
        t_line "cave here that had"
        t_para "horribly powerful"
        t_line "#MON in it."
        t_done )
};
const txt_cmd_s CeruleanCityYoungsterText2[] = {
    text_start("Ayuh?"
        t_para "My ITEMFINDER is"
        t_line "responding…"
        t_done )
};
const txt_cmd_s CeruleanCitySignText[] = {
    text_start("CERULEAN CITY"
        t_para "A Mysterious Blue"
        t_line "Aura Surrounds It"
        t_done )
};
const txt_cmd_s CeruleanGymSignText[] = {
    text_start("CERULEAN CITY"
        t_line "#MON GYM"
        t_cont "LEADER: MISTY"
        t_para "The Tomboyish"
        t_line "Mermaid"
        t_done )
};
const txt_cmd_s CeruleanBikeShopSignText[] = {
    text_start("There's a notice"
        t_line "here…"
        t_para "The BIKE SHOP has"
        t_line "moved to GOLDENROD"
        t_cont "CITY in JOHTO…"
        t_done )
};
const txt_cmd_s CeruleanPoliceSignText[] = {
    text_start("There's a notice"
        t_line "here…"
        t_para "Stamp out thievery"
        t_line "and make the city"
        t_para "a friendlier, more"
        t_line "cheerful place!"
        t_para "CERULEAN POLICE"
        t_done )
};
const txt_cmd_s CeruleanCapeSignText[] = {
    text_start("CERULEAN CAPE"
        t_line "AHEAD"
        t_done )
};
const txt_cmd_s CeruleanLockedDoorText[] = {
    text_start("It's locked…"
        t_done )
    //db(0, 0) // filler
};
