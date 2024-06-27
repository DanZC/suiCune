#include "../constants.h"
#include "../util/scripting.h"
#include "IndigoPlateauPokecenter1F.h"
//// EVENTS
enum {
    INDIGOPLATEAUPOKECENTER1F_NURSE = 2,
    INDIGOPLATEAUPOKECENTER1F_CLERK,
    INDIGOPLATEAUPOKECENTER1F_COOLTRAINER_M,
    INDIGOPLATEAUPOKECENTER1F_SILVER,
    INDIGOPLATEAUPOKECENTER1F_GRAMPS,
    INDIGOPLATEAUPOKECENTER1F_ABRA,
};

const Script_fn_t IndigoPlateauPokecenter1F_SceneScripts[] = {
    IndigoPlateauPokecenter1F_MapScripts_DummyScene , //  SCENE_DEFAULT,
};

const struct MapCallback IndigoPlateauPokecenter1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, IndigoPlateauPokecenter1F_MapScripts_PrepareElite4),
};

const struct MapScripts IndigoPlateauPokecenter1F_MapScripts = {
    .scene_script_count = lengthof(IndigoPlateauPokecenter1F_SceneScripts),
    .scene_scripts = IndigoPlateauPokecenter1F_SceneScripts,

    .callback_count = lengthof(IndigoPlateauPokecenter1F_MapCallbacks),
    .callbacks = IndigoPlateauPokecenter1F_MapCallbacks,
};

static const struct CoordEvent IndigoPlateauPokecenter1F_CoordEvents[] = {
    coord_event(16, 4, SCENE_DEFAULT, &PlateauRivalBattle1),
    coord_event(17, 4, SCENE_DEFAULT, &PlateauRivalBattle2),
};

static const struct BGEvent IndigoPlateauPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData IndigoPlateauPokecenter1F_WarpEvents[] = {
    warp_event(5, 13, ROUTE_23, 1),
    warp_event(6, 13, ROUTE_23, 2),
    warp_event(0, 13, POKECENTER_2F, 1),
    warp_event(14, 3, WILLS_ROOM, 1),
};

static const struct ObjEvent IndigoPlateauPokecenter1F_ObjectEvents[] = {
    object_event(3, 7, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IndigoPlateauPokecenter1FNurseScript, -1),
    object_event(11, 7, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IndigoPlateauPokecenter1FClerkScript, -1),
    object_event(11, 11, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IndigoPlateauPokecenter1FCooltrainerMScript, -1),
    object_event(16, 9, SPRITE_SILVER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_INDIGO_PLATEAU_POKECENTER_RIVAL),
    object_event(1, 9, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &TeleportGuyScript, EVENT_TELEPORT_GUY),
    object_event(0, 9, SPRITE_JYNX, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &AbraScript, EVENT_TELEPORT_GUY),
};

const struct MapEvents IndigoPlateauPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(IndigoPlateauPokecenter1F_WarpEvents),
    .warp_events = IndigoPlateauPokecenter1F_WarpEvents,

    .coord_event_count = lengthof(IndigoPlateauPokecenter1F_CoordEvents),
    .coord_events = IndigoPlateauPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(IndigoPlateauPokecenter1F_BGEvents),
    .bg_events = IndigoPlateauPokecenter1F_BGEvents,

    .obj_event_count = lengthof(IndigoPlateauPokecenter1F_ObjectEvents),
    .obj_events = IndigoPlateauPokecenter1F_ObjectEvents,
};

//// CODE

bool IndigoPlateauPokecenter1F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool IndigoPlateauPokecenter1F_MapScripts_PrepareElite4(script_s* s) {
    SCRIPT_BEGIN
    setmapscene(WILLS_ROOM, SCENE_DEFAULT)
    setmapscene(KOGAS_ROOM, SCENE_DEFAULT)
    setmapscene(BRUNOS_ROOM, SCENE_DEFAULT)
    setmapscene(KARENS_ROOM, SCENE_DEFAULT)
    setmapscene(LANCES_ROOM, SCENE_DEFAULT)
    setmapscene(HALL_OF_FAME, SCENE_DEFAULT)
    clearevent(EVENT_WILLS_ROOM_ENTRANCE_CLOSED)
    clearevent(EVENT_WILLS_ROOM_EXIT_OPEN)
    clearevent(EVENT_KOGAS_ROOM_ENTRANCE_CLOSED)
    clearevent(EVENT_KOGAS_ROOM_EXIT_OPEN)
    clearevent(EVENT_BRUNOS_ROOM_ENTRANCE_CLOSED)
    clearevent(EVENT_BRUNOS_ROOM_EXIT_OPEN)
    clearevent(EVENT_KARENS_ROOM_ENTRANCE_CLOSED)
    clearevent(EVENT_KARENS_ROOM_EXIT_OPEN)
    clearevent(EVENT_LANCES_ROOM_ENTRANCE_CLOSED)
    clearevent(EVENT_LANCES_ROOM_EXIT_OPEN)
    clearevent(EVENT_BEAT_ELITE_4_WILL)
    clearevent(EVENT_BEAT_ELITE_4_KOGA)
    clearevent(EVENT_BEAT_ELITE_4_BRUNO)
    clearevent(EVENT_BEAT_ELITE_4_KAREN)
    clearevent(EVENT_BEAT_CHAMPION_LANCE)
    setevent(EVENT_LANCES_ROOM_OAK_AND_MARY)
    s_endcallback
    SCRIPT_END
}
bool PlateauRivalBattle1(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_RIVAL_IN_MT_MOON)
    iffalse_jump(PlateauRivalScriptDone)
    checkflag(ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT)
    iftrue_jump(PlateauRivalScriptDone)
    readvar(VAR_WEEKDAY)
    ifequal_jump(SUNDAY, PlateauRivalScriptDone)
    ifequal_jump(TUESDAY, PlateauRivalScriptDone)
    ifequal_jump(THURSDAY, PlateauRivalScriptDone)
    ifequal_jump(FRIDAY, PlateauRivalScriptDone)
    ifequal_jump(SATURDAY, PlateauRivalScriptDone)
    moveobject(INDIGOPLATEAUPOKECENTER1F_SILVER, 17, 9)
    appear(INDIGOPLATEAUPOKECENTER1F_SILVER)
    turnobject(PLAYER, DOWN)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    applymovement(INDIGOPLATEAUPOKECENTER1F_SILVER, PlateauRivalMovement1)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    turnobject(PLAYER, RIGHT)
    sjump(PlateauRivalBattleCommon)
    SCRIPT_END
}
bool PlateauRivalBattle2(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_RIVAL_IN_MT_MOON)
    iffalse_jump(PlateauRivalScriptDone)
    checkflag(ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT)
    iftrue_jump(PlateauRivalScriptDone)
    readvar(VAR_WEEKDAY)
    ifequal_jump(SUNDAY, PlateauRivalScriptDone)
    ifequal_jump(TUESDAY, PlateauRivalScriptDone)
    ifequal_jump(THURSDAY, PlateauRivalScriptDone)
    ifequal_jump(FRIDAY, PlateauRivalScriptDone)
    ifequal_jump(SATURDAY, PlateauRivalScriptDone)
    appear(INDIGOPLATEAUPOKECENTER1F_SILVER)
    turnobject(PLAYER, DOWN)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    pause(15)
    applymovement(INDIGOPLATEAUPOKECENTER1F_SILVER, PlateauRivalMovement2)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    turnobject(PLAYER, LEFT)
    SCRIPT_FALLTHROUGH(PlateauRivalBattleCommon)
}
bool PlateauRivalBattleCommon(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(PlateauRivalText1)
    waitbutton
    closetext
    setevent(EVENT_INDIGO_PLATEAU_POKECENTER_RIVAL)
    checkevent(EVENT_GOT_TOTODILE_FROM_ELM)
    iftrue(Totodile)
    checkevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    iftrue(Chikorita)
    // Cyndaquil
    winlosstext(PlateauRivalWinText, PlateauRivalLoseText)
    setlasttalked(INDIGOPLATEAUPOKECENTER1F_SILVER)
    loadtrainer(RIVAL2, RIVAL2_2_TOTODILE)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    sjump(PlateauRivalPostBattle)
Totodile:
    winlosstext(PlateauRivalWinText, PlateauRivalLoseText)
    setlasttalked(INDIGOPLATEAUPOKECENTER1F_SILVER)
    loadtrainer(RIVAL2, RIVAL2_2_CHIKORITA)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    sjump(PlateauRivalPostBattle)
Chikorita:
    winlosstext(PlateauRivalWinText, PlateauRivalLoseText)
    setlasttalked(INDIGOPLATEAUPOKECENTER1F_SILVER)
    loadtrainer(RIVAL2, RIVAL2_2_CYNDAQUIL)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    sjump(PlateauRivalPostBattle)
    SCRIPT_END
}
bool PlateauRivalPostBattle(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_RIVAL_AFTER)
    opentext
    writetext(PlateauRivalText2)
    waitbutton
    closetext
    turnobject(PLAYER, DOWN)
    applymovement(INDIGOPLATEAUPOKECENTER1F_SILVER, PlateauRivalLeavesMovement)
    disappear(INDIGOPLATEAUPOKECENTER1F_SILVER)
    setscene(SCENE_DEFAULT)
    playmapmusic
    setflag(ENGINE_INDIGO_PLATEAU_RIVAL_FIGHT)
    SCRIPT_FALLTHROUGH(PlateauRivalScriptDone)
}
bool PlateauRivalScriptDone(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool IndigoPlateauPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool IndigoPlateauPokecenter1FClerkScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    pokemart(MARTTYPE_STANDARD, MART_INDIGO_PLATEAU)
    closetext
    s_end
    SCRIPT_END
}
bool IndigoPlateauPokecenter1FCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(IndigoPlateauPokecenter1FCooltrainerMText)
    SCRIPT_END
}
bool TeleportGuyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(TeleportGuyText1)
    yesorno
    iffalse(No)
    writetext(TeleportGuyYesText)
    waitbutton
    closetext
    playsound(SFX_WARP_TO)
    special(FadeOutPalettes)
    waitsfx
    warp(NEW_BARK_TOWN, 13, 6)
    s_end
No:
    writetext(TeleportGuyNoText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool AbraScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(AbraText)
    playcry(ABRA)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t PlateauRivalMovement1[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t PlateauRivalMovement2[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t PlateauRivalLeavesMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s IndigoPlateauPokecenter1FCooltrainerMText[] = {
    text_start("At the #MON"
        t_line "LEAGUE, you'll get"
        t_para "tested by the"
        t_line "ELITE FOUR."
        t_para "You have to beat"
        t_line "them all. If you"
        t_para "lose, you have to"
        t_line "start all over!"
        t_done )
};
const txt_cmd_s PlateauRivalText1[] = {
    text_start("Hold it."
        t_para "You're going to"
        t_line "take the #MON"
        t_para "LEAGUE challenge"
        t_line "now?"
        t_para "That's not going"
        t_line "to happen."
        t_para "My super-well-"
        t_line "trained #MON"
        t_para "are going to pound"
        t_line "you."
        t_para "<PLAYER>!"
        t_line "I challenge you!"
        t_done )
};
const txt_cmd_s PlateauRivalWinText[] = {
    text_start("…"
        t_para "OK--I lost…"
        t_done )
};
const txt_cmd_s PlateauRivalText2[] = {
    text_start("…Darn… I still"
        t_line "can't win…"
        t_para "I… I have to think"
        t_line "more about my"
        t_cont "#MON…"
        t_para "Humph! Try not to"
        t_line "lose!"
        t_done )
};
const txt_cmd_s PlateauRivalLoseText[] = {
    text_start("…"
        t_para "Whew…"
        t_line "With my partners,"
        t_para "I'm going to be"
        t_line "the CHAMPION!"
        t_done )
};
const txt_cmd_s TeleportGuyText1[] = {
    text_start("Ah! You're chal-"
        t_line "lenging the ELITE"
        t_para "FOUR? Are you sure"
        t_line "you're ready?"
        t_para "If you need to"
        t_line "train some more,"
        t_para "my ABRA can help"
        t_line "you."
        t_para "It can TELEPORT"
        t_line "you home."
        t_para "Would you like to"
        t_line "go home now?"
        t_done )
};
const txt_cmd_s TeleportGuyYesText[] = {
    text_start("OK, OK. Picture"
        t_line "your house in your"
        t_cont "mind…"
        t_done )
};
const txt_cmd_s TeleportGuyNoText[] = {
    text_start("OK, OK. The best"
        t_line "of luck to you!"
        t_done )
};
const txt_cmd_s AbraText[] = {
    text_start("ABRA: Aabra…"
        t_done )
    //db(0, 0) // filler
};
