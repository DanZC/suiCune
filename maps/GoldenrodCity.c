#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodCity.h"
//// EVENTS
enum {
    GOLDENRODCITY_POKEFAN_M1 = 2,
    GOLDENRODCITY_YOUNGSTER1,
    GOLDENRODCITY_COOLTRAINER_F1,
    GOLDENRODCITY_COOLTRAINER_F2,
    GOLDENRODCITY_YOUNGSTER2,
    GOLDENRODCITY_LASS,
    GOLDENRODCITY_GRAMPS,
    GOLDENRODCITY_ROCKETSCOUT,
    GOLDENRODCITY_ROCKET1,
    GOLDENRODCITY_ROCKET2,
    GOLDENRODCITY_ROCKET3,
    GOLDENRODCITY_ROCKET4,
    GOLDENRODCITY_ROCKET5,
    GOLDENRODCITY_ROCKET6,
    GOLDENRODCITY_MOVETUTOR,
};

const Script_fn_t GoldenrodCity_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodCity_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, GoldenrodCity_MapScripts_FlyPointAndFloria),
    map_callback(MAPCALLBACK_OBJECTS, GoldenrodCity_MapScripts_MoveTutor),
};

const struct MapScripts GoldenrodCity_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodCity_SceneScripts),
    .scene_scripts = GoldenrodCity_SceneScripts,

    .callback_count = lengthof(GoldenrodCity_MapCallbacks),
    .callbacks = GoldenrodCity_MapCallbacks,
};

static const struct CoordEvent GoldenrodCity_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodCity_BGEvents[] = {
    bg_event(10, 14, BGEVENT_READ, &GoldenrodCityStationSign),
    bg_event(4, 17, BGEVENT_READ, &GoldenrodCityRadioTowerSign),
    bg_event(26, 27, BGEVENT_READ, &GoldenrodDeptStoreSign),
    bg_event(26, 9, BGEVENT_READ, &GoldenrodGymSign),
    bg_event(22, 18, BGEVENT_READ, &GoldenrodCitySign),
    bg_event(28, 30, BGEVENT_READ, &GoldenrodCityBikeShopSign),
    bg_event(16, 22, BGEVENT_READ, &GoldenrodCityGameCornerSign),
    bg_event(12, 7, BGEVENT_READ, &GoldenrodCityNameRaterSign),
    bg_event(8, 6, BGEVENT_READ, &GoldenrodCityUndergroundSignNorth),
    bg_event(10, 30, BGEVENT_READ, &GoldenrodCityUndergroundSignSouth),
    bg_event(16, 27, BGEVENT_UP, &GoldenrodCityPokecenterSign),
    bg_event(30, 6, BGEVENT_READ, &GoldenrodCityFlowerShopSign),
    bg_event(17, 27, BGEVENT_READ, &GoldenrodCityPokecenterSign),
};

static const struct WarpEventData GoldenrodCity_WarpEvents[] = {
    warp_event(24, 7, GOLDENROD_GYM, 1),
    warp_event(29, 29, GOLDENROD_BIKE_SHOP, 1),
    warp_event(31, 21, GOLDENROD_HAPPINESS_RATER, 1),
    warp_event(5, 25, BILLS_FAMILYS_HOUSE, 1),
    warp_event(9, 13, GOLDENROD_MAGNET_TRAIN_STATION, 2),
    warp_event(29, 5, GOLDENROD_FLOWER_SHOP, 1),
    warp_event(33, 9, GOLDENROD_PP_SPEECH_HOUSE, 1),
    warp_event(15, 7, GOLDENROD_NAME_RATER, 1),
    warp_event(24, 27, GOLDENROD_DEPT_STORE_1F, 1),
    warp_event(14, 21, GOLDENROD_GAME_CORNER, 1),
    warp_event(5, 15, RADIO_TOWER_1F, 1),
    warp_event(19, 1, ROUTE_35_GOLDENROD_GATE, 3),
    warp_event(9, 5, GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 8),
    warp_event(9, 29, GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 5),
    warp_event(14, 27, GOLDENROD_POKECENTER_1F, 2),
};

static const struct ObjEvent GoldenrodCity_ObjectEvents[] = {
    object_event(7, 18, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityPokefanMScript, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(30, 17, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityYoungster1Script, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(12, 16, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityCooltrainerF1Script, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(20, 26, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WANDER, 1, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityCooltrainerF2Script, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(19, 17, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityYoungster2Script, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(17, 10, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityLassScript, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(9, 27, SPRITE_GRAMPS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityGrampsScript, EVENT_GOLDENROD_CITY_CIVILIANS),
    object_event(4, 16, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityRocketScoutScript, EVENT_GOLDENROD_CITY_ROCKET_SCOUT),
    object_event(28, 20, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityRocket1Script, EVENT_GOLDENROD_CITY_ROCKET_TAKEOVER),
    object_event(8, 15, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityRocket2Script, EVENT_GOLDENROD_CITY_ROCKET_TAKEOVER),
    object_event(16, 23, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityRocket3Script, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(29, 20, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityRocket4Script, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(29, 7, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityRocket5Script, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(31, 10, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodCityRocket6Script, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(12, 22, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &MoveTutorScript, EVENT_GOLDENROD_CITY_MOVE_TUTOR),
};

const struct MapEvents GoldenrodCity_MapEvents = {
    .warp_event_count = lengthof(GoldenrodCity_WarpEvents),
    .warp_events = GoldenrodCity_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodCity_CoordEvents),
    .coord_events = GoldenrodCity_CoordEvents,

    .bg_event_count = lengthof(GoldenrodCity_BGEvents),
    .bg_events = GoldenrodCity_BGEvents,

    .obj_event_count = lengthof(GoldenrodCity_ObjectEvents),
    .obj_events = GoldenrodCity_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodCity.h"

bool GoldenrodCity_MapScripts_FlyPointAndFloria(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_GOLDENROD)
    setflag(ENGINE_REACHED_GOLDENROD)
    checkevent(EVENT_MET_FLORIA)
    iftrue_jump(GoldenrodCity_MapScripts_FloriaDone)
    clearevent(EVENT_FLORIA_AT_SUDOWOODO)
    SCRIPT_FALLTHROUGH(GoldenrodCity_MapScripts_FloriaDone)
}
bool GoldenrodCity_MapScripts_FloriaDone(script_s* s) {
    SCRIPT_BEGIN
    s_endcallback
    SCRIPT_END
}
bool GoldenrodCity_MapScripts_MoveTutor(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iffalse_jump(GoldenrodCity_MapScripts_MoveTutorDone)
    checkitem(COIN_CASE)
    iffalse_jump(GoldenrodCity_MapScripts_MoveTutorDisappear)
    readvar(VAR_WEEKDAY)
    ifequal_jump(WEDNESDAY, GoldenrodCity_MapScripts_MoveTutorAppear)
    ifequal_jump(SATURDAY, GoldenrodCity_MapScripts_MoveTutorAppear)
    SCRIPT_FALLTHROUGH(GoldenrodCity_MapScripts_MoveTutorDisappear)
}
bool GoldenrodCity_MapScripts_MoveTutorDisappear(script_s* s) {
    SCRIPT_BEGIN
    disappear(GOLDENRODCITY_MOVETUTOR)
    s_endcallback
    SCRIPT_END
}
bool GoldenrodCity_MapScripts_MoveTutorAppear(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_DAILY_MOVE_TUTOR)
    iftrue_jump(GoldenrodCity_MapScripts_MoveTutorDone)
    appear(GOLDENRODCITY_MOVETUTOR)
    SCRIPT_FALLTHROUGH(GoldenrodCity_MapScripts_MoveTutorDone)
}
bool GoldenrodCity_MapScripts_MoveTutorDone(script_s* s) {
    SCRIPT_BEGIN
    s_endcallback
    SCRIPT_END
}

static struct MenuHeader MoveMenuHeader = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 2, 15, TEXTBOX_Y - 1),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count=4, // items
            .options = (const char*[]) {
                "FLAMETHROWER@",
                "THUNDERBOLT@",
                "ICE BEAM@",
                "CANCEL@",
            },
        },
    },
    .defaultOption = 1, // default option
};
bool MoveTutorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodCityMoveTutorAskTeachAMoveText)
    yesorno
    iffalse(Refused)
    special(DisplayCoinCaseBalance)
    writetext(GoldenrodCityMoveTutorAsk4000CoinsOkayText)
    yesorno
    iffalse(Refused2)
    checkcoins(4000)
    ifequal(HAVE_LESS, NotEnoughMoney)
    writetext(GoldenrodCityMoveTutorWhichMoveShouldITeachText)
    loadmenu(&MoveMenuHeader)
    verticalmenu
    closewindow
    ifequal(MOVETUTOR_FLAMETHROWER, Flamethrower)
    ifequal(MOVETUTOR_THUNDERBOLT, Thunderbolt)
    ifequal(MOVETUTOR_ICE_BEAM, IceBeam)
    goto Incompatible;
Flamethrower:
    setval(MOVETUTOR_FLAMETHROWER)
    writetext(GoldenrodCityMoveTutorMoveText)
    special(MoveTutor)
    ifequal(FALSE, TeachMove)
    goto Incompatible;
Thunderbolt:
    setval(MOVETUTOR_THUNDERBOLT)
    writetext(GoldenrodCityMoveTutorMoveText)
    special(MoveTutor)
    ifequal(FALSE, TeachMove)
    goto Incompatible;
IceBeam:
    setval(MOVETUTOR_ICE_BEAM)
    writetext(GoldenrodCityMoveTutorMoveText)
    special(MoveTutor)
    ifequal(FALSE, TeachMove)
    goto Incompatible;
Refused:
    writetext(GoldenrodCityMoveTutorAwwButTheyreAmazingText)
    waitbutton
    closetext
    s_end
Refused2:
    writetext(GoldenrodCityMoveTutorHmTooBadText)
    waitbutton
    closetext
    s_end
TeachMove:
    writetext(GoldenrodCityMoveTutorIfYouUnderstandYouveMadeItText)
    promptbutton
    takecoins(4000)
    waitsfx
    playsound(SFX_TRANSACTION)
    special(DisplayCoinCaseBalance)
    writetext(GoldenrodCityMoveTutorFarewellKidText)
    waitbutton
    closetext
    readvar(VAR_FACING)
    ifequal(LEFT, WalkAroundPlayer)
    applymovement(GOLDENRODCITY_MOVETUTOR, GoldenrodCityMoveTutorEnterGameCornerMovement)
    goto GoInside;
WalkAroundPlayer:
    applymovement(GOLDENRODCITY_MOVETUTOR, GoldenrodCityMoveTutorWalkAroundPlayerThenEnterGameCornerMovement)
GoInside:
    playsound(SFX_ENTER_DOOR)
    disappear(GOLDENRODCITY_MOVETUTOR)
    clearevent(EVENT_GOLDENROD_GAME_CORNER_MOVE_TUTOR)
    setflag(ENGINE_DAILY_MOVE_TUTOR)
    waitsfx
    s_end
Incompatible:
    writetext(GoldenrodCityMoveTutorBButText)
    waitbutton
    closetext
    s_end
NotEnoughMoney:
    writetext(GoldenrodCityMoveTutorYouDontHaveEnoughCoinsText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodCityPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityPokefanMText)
    SCRIPT_END
}
bool GoldenrodCityYoungster1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityYoungster1Text)
    SCRIPT_END
}
bool GoldenrodCityCooltrainerF1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(ClearedRadioTower)
    writetext(GoldenrodCityCooltrainerF1Text)
    waitbutton
    closetext
    s_end
ClearedRadioTower:
    writetext(GoldenrodCityCooltrainerF1Text_ClearedRadioTower)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodCityCooltrainerF2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_RADIO_CARD)
    iftrue(GotRadioCard)
    writetext(GoldenrodCityCooltrainerF2Text)
    waitbutton
    closetext
    s_end
GotRadioCard:
    writetext(GoldenrodCityCooltrainerF2Text_GotRadioCard)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodCityYoungster2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityYoungster2Text)
    SCRIPT_END
}
bool GoldenrodCityLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityLassText)
    SCRIPT_END
}
bool GoldenrodCityGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityGrampsText)
    SCRIPT_END
}
bool GoldenrodCityRocketScoutScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(GoldenrodCityRocketScoutText1)
    promptbutton
    faceplayer
    writetext(GoldenrodCityRocketScoutText2)
    waitbutton
    closetext
    turnobject(GOLDENRODCITY_ROCKETSCOUT, UP)
    s_end
    SCRIPT_END
}
bool GoldenrodCityRocket1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityRocket1Text)
    SCRIPT_END
}
bool GoldenrodCityRocket2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityRocket2Text)
    SCRIPT_END
}
bool GoldenrodCityRocket3Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityRocket3Text)
    SCRIPT_END
}
bool GoldenrodCityRocket4Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityRocket4Text)
    SCRIPT_END
}
bool GoldenrodCityRocket5Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityRocket5Text)
    SCRIPT_END
}
bool GoldenrodCityRocket6Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodCityRocket6Text)
    SCRIPT_END
}
bool GoldenrodCityStationSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityStationSignText)
    SCRIPT_END
}
bool GoldenrodCityRadioTowerSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityRadioTowerSignText)
    SCRIPT_END
}
bool GoldenrodDeptStoreSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodDeptStoreSignText)
    SCRIPT_END
}
bool GoldenrodGymSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodGymSignText)
    SCRIPT_END
}
bool GoldenrodCitySign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCitySignText)
    SCRIPT_END
}
bool GoldenrodCityBikeShopSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityBikeShopSignText)
    SCRIPT_END
}
bool GoldenrodCityGameCornerSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityGameCornerSignText)
    SCRIPT_END
}
bool GoldenrodCityNameRaterSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityNameRaterSignText)
    SCRIPT_END
}
bool GoldenrodCityUndergroundSignNorth(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityUndergroundSignNorthText)
    SCRIPT_END
}
bool GoldenrodCityUndergroundSignSouth(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityUndergroundSignSouthText)
    SCRIPT_END
}
bool GoldenrodCityPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityPokeComCenterSignText)
    // jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool GoldenrodCityFlowerShopSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodCityFlowerShopSignText)
    SCRIPT_END
}
const uint8_t GoldenrodCityMoveTutorEnterGameCornerMovement[] = {
    step(RIGHT),
    step(RIGHT),
    step(UP),
    movement_step_end,
};
const uint8_t GoldenrodCityMoveTutorWalkAroundPlayerThenEnterGameCornerMovement[] = {
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s GoldenrodCityPokefanMText[] = {
    text_start("They built the new"
        t_line "RADIO TOWER to"
        t_para "replace the old,"
        t_line "creaky one."
        t_done )
};
const txt_cmd_s GoldenrodCityYoungster1Text[] = {
    text_start("I know there's a"
        t_line "new BIKE SHOP, but"
        t_para "I can't find it"
        t_line "anywhere."
        t_done )
};
const txt_cmd_s GoldenrodCityCooltrainerF1Text[] = {
    text_start("Is that man in"
        t_line "black dressed up"
        t_para "like a TEAM ROCKET"
        t_line "member? How silly!"
        t_done )
};
const txt_cmd_s GoldenrodCityCooltrainerF1Text_ClearedRadioTower[] = {
    text_start("Was that man in"
        t_line "black really part"
        t_para "of TEAM ROCKET? I"
        t_line "can't believe it!"
        t_done )
};
const txt_cmd_s GoldenrodCityCooltrainerF2Text[] = {
    text_start("The RADIO TOWER in"
        t_line "GOLDENROD CITY is"
        t_cont "a landmark."
        t_para "They're running a"
        t_line "promotional cam- "
        t_cont "paign right now."
        t_para "They'll modify"
        t_line "your #GEAR,"
        t_para "so it can also"
        t_line "serve as a radio."
        t_done )
};
const txt_cmd_s GoldenrodCityCooltrainerF2Text_GotRadioCard[] = {
    text_start("Oh, your #GEAR"
        t_line "works as a radio!"
        t_done )
};
const txt_cmd_s GoldenrodCityYoungster2Text[] = {
    text_start("E-he-he-he…"
        t_para "I got in trouble"
        t_line "for playing in the"
        t_para "basement of the"
        t_line "DEPT.STORE."
        t_done )
};
const txt_cmd_s GoldenrodCityLassText[] = {
    text_start("The man at that"
        t_line "house rates your"
        t_cont "#MON names."
        t_para "He can even rename"
        t_line "your #MON."
        t_done )
};
const txt_cmd_s GoldenrodCityGrampsText[] = {
    text_start("Whew! This is one"
        t_line "big town. I don't"
        t_para "know where any-"
        t_line "thing is."
        t_done )
};
const txt_cmd_s GoldenrodCityRocketScoutText1[] = {
    text_start("So this is the"
        t_line "RADIO TOWER…"
        t_done )
};
const txt_cmd_s GoldenrodCityRocketScoutText2[] = {
    text_start("What do you want,"
        t_line "you pest? Scram!"
        t_done )
};
const txt_cmd_s GoldenrodCityRocket1Text[] = {
    text_start("Stay out of the"
        t_line "way! Beat it!"
        t_done )
};
const txt_cmd_s GoldenrodCityRocket2Text[] = {
    text_start("Take over the"
        t_line "RADIO TOWER…"
        t_para "What? It's none of"
        t_line "your business!"
        t_done )
};
const txt_cmd_s GoldenrodCityRocket3Text[] = {
    text_start("#MON? They're"
        t_line "nothing more than"
        t_para "tools for making"
        t_line "money!"
        t_done )
};
const txt_cmd_s GoldenrodCityRocket4Text[] = {
    text_start("Our dream will"
        t_line "soon come true…"
        t_para "It was such a long"
        t_line "struggle…"
        t_done )
};
const txt_cmd_s GoldenrodCityRocket5Text[] = {
    text_start("Hey, brat! You"
        t_line "don't belong here!"
        t_cont "Get lost!"
        t_done )
};
const txt_cmd_s GoldenrodCityRocket6Text[] = {
    text_start("Come taste the"
        t_line "true terror of"
        t_cont "TEAM ROCKET!"
        t_done )
};
const txt_cmd_s GoldenrodCityStationSignText[] = {
    text_start("GOLDENROD CITY"
        t_line "STATION"
        t_done )
};
const txt_cmd_s GoldenrodCityRadioTowerSignText[] = {
    text_start("GOLDENROD CITY"
        t_line "RADIO TOWER"
        t_done )
};
const txt_cmd_s GoldenrodDeptStoreSignText[] = {
    text_start("Full Selection of"
        t_line "#MON Goods!"
        t_para "GOLDENROD CITY"
        t_line "DEPT.STORE"
        t_done )
};
const txt_cmd_s GoldenrodGymSignText[] = {
    text_start("GOLDENROD CITY"
        t_line "#MON GYM"
        t_cont "LEADER: WHITNEY"
        t_para "The Incredibly"
        t_line "Pretty Girl!"
        t_done )
};
const txt_cmd_s GoldenrodCitySignText[] = {
    text_start("GOLDENROD CITY"
        t_para "The Festive City"
        t_line "of Opulent Charm"
        t_done )
};
const txt_cmd_s GoldenrodCityBikeShopSignText[] = {
    text_start("The World is a"
        t_line "Cycle Path!"
        t_cont "BIKE SHOP"
        t_done )
};
const txt_cmd_s GoldenrodCityGameCornerSignText[] = {
    text_start("Your Playground!"
        t_para "GOLDENROD CITY"
        t_line "GAME CORNER"
        t_done )
};
const txt_cmd_s GoldenrodCityNameRaterSignText[] = {
    text_start("NAME RATER"
        t_para "Get Your #MON"
        t_line "Nicknames Rated"
        t_done )
};
const txt_cmd_s GoldenrodCityUndergroundSignNorthText[] = {
    text_start("UNDERGROUND"
        t_line "ENTRANCE"
        t_done )
};
const txt_cmd_s GoldenrodCityUndergroundSignSouthText[] = {
    text_start("UNDERGROUND"
        t_line "ENTRANCE"
        t_done )
};
const txt_cmd_s GoldenrodCityPokeComCenterSignText[] = {
    text_start("For Mobile Tips!"
        t_line "#COM CENTER"
        t_done )
};
const txt_cmd_s GoldenrodCityFlowerShopSignText[] = {
    text_start("Blooming Beautiful"
        t_line "FLOWER SHOP"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorAskTeachAMoveText[] = {
    text_start("I can teach your"
        t_line "#MON amazing"
        t_para "moves if you'd"
        t_line "like."
        t_para "Should I teach a"
        t_line "new move?"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorAsk4000CoinsOkayText[] = {
    text_start("It will cost you"
        t_line "4000 coins. Okay?"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorAwwButTheyreAmazingText[] = {
    text_start("Aww… But they're"
        t_line "amazing…"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorWhichMoveShouldITeachText[] = {
    text_start("Wahahah! You won't"
        t_line "regret it!"
        t_para "Which move should"
        t_line "I teach?"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorHmTooBadText[] = {
    text_start("Hm, too bad. I'll"
        t_line "have to get some"
        t_cont "cash from home…"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorIfYouUnderstandYouveMadeItText[] = {
    text_start("If you understand"
        t_line "what's so amazing"
        t_para "about this move,"
        t_line "you've made it as"
        t_cont "a trainer."
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorFarewellKidText[] = {
    text_start("Wahahah!"
        t_line "Farewell, kid!"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorBButText[] = {
    text_start("B-but…"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorYouDontHaveEnoughCoinsText[] = {
    text_start("…You don't have"
        t_line "enough coins here…"
        t_done )
};
const txt_cmd_s GoldenrodCityMoveTutorMoveText[] = {
    text_start(
        t_done )
};
