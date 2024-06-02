#include "../constants.h"
#include "../util/scripting.h"
#include "BurnedTower1F.h"
//// EVENTS
enum {
    BURNEDTOWER1F_ROCK = 2,
    BURNEDTOWER1F_EUSINE,
    BURNEDTOWER1F_SILVER,
    BURNEDTOWER1F_MORTY,
    BURNEDTOWER1F_POKE_BALL,
};

const Script_fn_t BurnedTower1F_SceneScripts[] = {
    BurnedTower1F_MapScripts_EusineScene , //  SCENE_DEFAULT,
    BurnedTower1F_MapScripts_DummyScene1 , //  SCENE_BURNEDTOWER1F_RIVAL_BATTLE,
    BurnedTower1F_MapScripts_DummyScene2 , //  SCENE_BURNEDTOWER1F_NOTHING,
};

const struct MapCallback BurnedTower1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, BurnedTower1F_MapScripts_HoleAndLadder),
};

const struct MapScripts BurnedTower1F_MapScripts = {
    .scene_script_count = lengthof(BurnedTower1F_SceneScripts),
    .scene_scripts = BurnedTower1F_SceneScripts,

    .callback_count = lengthof(BurnedTower1F_MapCallbacks),
    .callbacks = BurnedTower1F_MapCallbacks,
};

static const struct CoordEvent BurnedTower1F_CoordEvents[] = {
    coord_event(11, 9, SCENE_BURNEDTOWER1F_RIVAL_BATTLE, &BurnedTowerRivalBattleScript),
};

static const struct BGEvent BurnedTower1F_BGEvents[] = {
    bg_event(8, 7, BGEVENT_ITEM, &BurnedTower1FHiddenEther),
    bg_event(13, 11, BGEVENT_ITEM, &BurnedTower1FHiddenUltraBall),
};

static const struct WarpEventData BurnedTower1F_WarpEvents[] = {
    warp_event(9, 15, ECRUTEAK_CITY, 13),
    warp_event(10, 15, ECRUTEAK_CITY, 13),
    warp_event(10, 9, BURNED_TOWER_B1F, 1),
    warp_event(5, 5, BURNED_TOWER_B1F, 1), // inaccessible, left over from G/S
    warp_event(5, 6, BURNED_TOWER_B1F, 1), // inaccessible, left over from G/S
    warp_event(4, 6, BURNED_TOWER_B1F, 1), // inaccessible, left over from G/S
    warp_event(15, 4, BURNED_TOWER_B1F, 2), // inaccessible, left over from G/S
    warp_event(15, 5, BURNED_TOWER_B1F, 2), // inaccessible, left over from G/S
    warp_event(10, 7, BURNED_TOWER_B1F, 3), // inaccessible, left over from G/S
    warp_event(5, 14, BURNED_TOWER_B1F, 4), // inaccessible, left over from G/S
    warp_event(4, 14, BURNED_TOWER_B1F, 4), // inaccessible, left over from G/S
    warp_event(14, 14, BURNED_TOWER_B1F, 5), // inaccessible, left over from G/S
    warp_event(15, 14, BURNED_TOWER_B1F, 5), // inaccessible, left over from G/S
    warp_event(7, 15, BURNED_TOWER_B1F, 6), // inaccessible, left over from G/S
};

static const struct ObjEvent BurnedTower1F_ObjectEvents[] = {
    object_event(15, 4, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BurnedTower1FRock, -1),
    object_event(12, 12, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BurnedTower1FEusineScript, EVENT_BURNED_TOWER_1F_EUSINE),
    object_event(8, 9, SPRITE_SILVER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &ObjectEvent, EVENT_RIVAL_BURNED_TOWER),
    object_event(14, 14, SPRITE_MORTY, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &BurnedTower1FMortyScript, EVENT_BURNED_TOWER_MORTY),
    object_event(14, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &BurnedTower1FHPUp, EVENT_BURNED_TOWER_1F_HP_UP),
};

const struct MapEvents BurnedTower1F_MapEvents = {
    .warp_event_count = lengthof(BurnedTower1F_WarpEvents),
    .warp_events = BurnedTower1F_WarpEvents,

    .coord_event_count = lengthof(BurnedTower1F_CoordEvents),
    .coord_events = BurnedTower1F_CoordEvents,

    .bg_event_count = lengthof(BurnedTower1F_BGEvents),
    .bg_events = BurnedTower1F_BGEvents,

    .obj_event_count = lengthof(BurnedTower1F_ObjectEvents),
    .obj_events = BurnedTower1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BurnedTower1F.h"

bool BurnedTower1F_MapScripts_EusineScene(script_s* s) {
    SCRIPT_BEGIN
    sdefer(BurnedTower1F_MapScripts_MeetEusine);
    s_end
    SCRIPT_END
}
bool BurnedTower1F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool BurnedTower1F_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool BurnedTower1F_MapScripts_HoleAndLadder(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_HOLE_IN_BURNED_TOWER)
    iftrue(KeepHoleOpen)
    changeblock(10, 8, 0x32) // floor
KeepHoleOpen:
    checkevent(EVENT_RELEASED_THE_BEASTS)
    iftrue(HideBasement)
    changeblock(6, 14, 0x09) // ladder
HideBasement:
    s_endcallback
    SCRIPT_END
}
bool BurnedTower1F_MapScripts_MeetEusine(script_s* s) {
    SCRIPT_BEGIN
    turnobject(BURNEDTOWER1F_EUSINE, DOWN)
    showemote(EMOTE_SHOCK, BURNEDTOWER1F_EUSINE, 15)
    applymovement(BURNEDTOWER1F_EUSINE, BurnedTower1FEusineMovement)
    opentext
    writetext(BurnedTower1FEusineIntroText)
    waitbutton
    closetext
    moveobject(BURNEDTOWER1F_EUSINE, 9, 14)
    setscene(SCENE_BURNEDTOWER1F_RIVAL_BATTLE)
    s_end
    SCRIPT_END
}
bool BurnedTowerRivalBattleScript(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_SHOCK, BURNEDTOWER1F_SILVER, 15)
    special(FadeOutMusic)
    pause(15)
    turnobject(BURNEDTOWER1F_SILVER, RIGHT)
    pause(15)
    applymovement(PLAYER, BurnedTowerMovement_PlayerWalksToSilver)
    applymovement(BURNEDTOWER1F_SILVER, BurnedTowerMovement_SilverWalksToPlayer)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(BurnedTowerSilver_BeforeText)
    waitbutton
    closetext
    checkevent(EVENT_GOT_TOTODILE_FROM_ELM)
    iftrue(totodile)
    checkevent(EVENT_GOT_CHIKORITA_FROM_ELM)
    iftrue(chikorita)
    winlosstext(BurnedTowerSilver_WinText, BurnedTowerSilver_LossText)
    setlasttalked(BURNEDTOWER1F_SILVER)
    loadtrainer(RIVAL1, RIVAL1_3_TOTODILE)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto returnfrombattle;
totodile:
    winlosstext(BurnedTowerSilver_WinText, BurnedTowerSilver_LossText)
    setlasttalked(BURNEDTOWER1F_SILVER)
    loadtrainer(RIVAL1, RIVAL1_3_CHIKORITA)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto returnfrombattle;
chikorita:
    winlosstext(BurnedTowerSilver_WinText, BurnedTowerSilver_LossText)
    setlasttalked(BURNEDTOWER1F_SILVER)
    loadtrainer(RIVAL1, RIVAL1_3_CYNDAQUIL)
    startbattle
    dontrestartmapmusic
    reloadmapafterbattle
    goto returnfrombattle;
returnfrombattle:
    playmusic(MUSIC_RIVAL_AFTER)
    opentext
    writetext(BurnedTowerSilver_AfterText1)
    waitbutton
    closetext
    setscene(SCENE_BURNEDTOWER1F_NOTHING)
    setevent(EVENT_RIVAL_BURNED_TOWER)
    special(FadeOutMusic)
    pause(15)
    earthquake(50)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playsound(SFX_ENTER_DOOR)
    waitsfx
    changeblock(10, 8, 0x25) // hole
    reloadmappart
    pause(15)
    applymovement(PLAYER, BurnedTower1FMovement_PlayerStartsToFall)
    playsound(SFX_KINESIS)
    showemote(EMOTE_SHOCK, BURNEDTOWER1F_SILVER, 20)
    opentext
    writetext(BurnedTowerSilver_AfterText2)
    waitbutton
    closetext
    setevent(EVENT_HOLE_IN_BURNED_TOWER)
    pause(15)
    warpcheck
    s_end
    SCRIPT_END
}
bool BurnedTower1FEusineScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BurnedTower1FEusineText)
    SCRIPT_END
}
bool BurnedTower1FMortyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BurnedTower1FMortyText)
    SCRIPT_END
}
bool BurnedTower1FRock(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(SmashRockScript)
    SCRIPT_END
}
const struct HiddenItem BurnedTower1FHiddenEther = {ETHER, EVENT_BURNED_TOWER_1F_HIDDEN_ETHER};
const struct HiddenItem BurnedTower1FHiddenUltraBall = {ULTRA_BALL, EVENT_BURNED_TOWER_1F_HIDDEN_ULTRA_BALL};
const struct ItemBall BurnedTower1FHPUp = {HP_UP, 1};
const uint8_t BurnedTowerMovement_PlayerWalksToSilver[] = {
    step(LEFT),
    movement_step_end,
};
const uint8_t BurnedTowerMovement_SilverWalksToPlayer[] = {
    step(RIGHT),
    movement_step_end,
};
const uint8_t BurnedTower1FMovement_PlayerStartsToFall[] = {
    movement_skyfall_top,
    movement_step_end,
};
const uint8_t BurnedTower1FEusineMovement[] = {
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s BurnedTowerSilver_BeforeText[] = {
    text_start("<……> <……> <……>"
        t_para "…Oh, it's you."
        t_para "I came looking for"
        t_line "some legendary"
        t_para "#MON that they"
        t_line "say roosts here."
        t_para "But there's"
        t_line "nothing here!"
        t_para "Nothing after all"
        t_line "the trouble of"
        t_para "coming to this"
        t_line "dump? No way!"
        t_para "It's all your"
        t_line "fault!"
        t_done )
};
const txt_cmd_s BurnedTowerSilver_WinText[] = {
    text_start("…Humph!"
        t_para "This is why I hate"
        t_line "battling wimps."
        t_para "There's no"
        t_line "challenge in it."
        t_done )
};
const txt_cmd_s BurnedTowerSilver_AfterText1[] = {
    text_start("…Aw, whatever."
        t_para "You would never be"
        t_line "able to catch a"
        t_para "legendary #MON"
        t_line "anyway."
        t_done )
};
const txt_cmd_s BurnedTowerSilver_LossText[] = {
    text_start("…Humph!"
        t_para "This is why I hate"
        t_line "battling wimps."
        t_para "It's just a waste"
        t_line "of my time."
        t_done )
};
const txt_cmd_s BurnedTowerSilver_AfterText2[] = {
    text_start("Humph!"
        t_para "What are you doing"
        t_line "falling into a"
        t_para "hole? Some genius"
        t_line "you are!"
        t_para "Serves you right!"
        t_done )
};
const txt_cmd_s BurnedTower1FEusineIntroText[] = {
    text_start("EUSINE: My name's"
        t_line "EUSINE."
        t_para "I'm on the trail"
        t_line "of a #MON named"
        t_cont "SUICUNE."
        t_para "And you are…?"
        t_para "<PLAYER>? Glad to"
        t_line "meet you!"
        t_para "I heard rumors"
        t_line "that SUICUNE is in"
        t_para "this BURNED TOWER,"
        t_line "so I came to look."
        t_para "But where exactly"
        t_line "could it be?"
        t_done )
};
const txt_cmd_s BurnedTower1FEusineText[] = {
    text_start("EUSINE: I heard"
        t_line "that SUICUNE is in"
        t_para "this BURNED TOWER,"
        t_line "so I came to look."
        t_para "But where exactly"
        t_line "could it be?"
        t_done )
};
const txt_cmd_s BurnedTower1FMortyText[] = {
    text_start("MORTY: ECRUTEAK's"
        t_line "GYM LEADER has to"
        t_para "study what are"
        t_line "said to be the"
        t_para "legendary #MON"
        t_line "--SUICUNE, ENTEI"
        t_cont "and RAIKOU."
        t_para "EUSINE is here, so"
        t_line "I've decided to"
        t_para "investigate the"
        t_line "TOWER with him."
        t_done )
    //db(0, 0) // filler
};
