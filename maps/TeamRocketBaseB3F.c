#include "../constants.h"
#include "../util/scripting.h"
#include "TeamRocketBaseB3F.h"
//// EVENTS
enum {
    TEAMROCKETBASEB3F_LANCE = 2,
    TEAMROCKETBASEB3F_ROCKET1,
    TEAMROCKETBASEB3F_MOLTRES,
    TEAMROCKETBASEB3F_ROCKET_GIRL,
    TEAMROCKETBASEB3F_ROCKET2,
    TEAMROCKETBASEB3F_SCIENTIST1,
    TEAMROCKETBASEB3F_SCIENTIST2,
    TEAMROCKETBASEB3F_ROCKET3,
    TEAMROCKETBASEB3F_SILVER,
    TEAMROCKETBASEB3F_POKE_BALL1,
    TEAMROCKETBASEB3F_POKE_BALL2,
    TEAMROCKETBASEB3F_POKE_BALL3,
    TEAMROCKETBASEB3F_POKE_BALL4,
    TEAMROCKETBASEB3F_POKE_BALL5,
};

const Script_fn_t TeamRocketBaseB3F_SceneScripts[] = {
    TeamRocketBaseB3F_MapScripts_LanceGetsPassword , //  SCENE_DEFAULT,
    TeamRocketBaseB3F_MapScripts_DummyScene1 , //  SCENE_TEAMROCKETBASEB3F_RIVAL_ENCOUNTER,
    TeamRocketBaseB3F_MapScripts_DummyScene2 , //  SCENE_TEAMROCKETBASEB3F_ROCKET_BOSS,
    TeamRocketBaseB3F_MapScripts_DummyScene3 , //  SCENE_TEAMROCKETBASEB3F_NOTHING,
};

const struct MapCallback TeamRocketBaseB3F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, TeamRocketBaseB3F_MapScripts_CheckGiovanniDoor),
};

const struct MapScripts TeamRocketBaseB3F_MapScripts = {
    .scene_script_count = lengthof(TeamRocketBaseB3F_SceneScripts),
    .scene_scripts = TeamRocketBaseB3F_SceneScripts,

    .callback_count = lengthof(TeamRocketBaseB3F_MapCallbacks),
    .callbacks = TeamRocketBaseB3F_MapCallbacks,
};

static const struct CoordEvent TeamRocketBaseB3F_CoordEvents[] = {
    coord_event(10, 8, SCENE_TEAMROCKETBASEB3F_ROCKET_BOSS, &RocketBaseBossLeft),
    coord_event(11, 8, SCENE_TEAMROCKETBASEB3F_ROCKET_BOSS, &RocketBaseBossRight),
    coord_event(8, 10, SCENE_TEAMROCKETBASEB3F_RIVAL_ENCOUNTER, &RocketBaseRival),
};

static const struct BGEvent TeamRocketBaseB3F_BGEvents[] = {
    bg_event(10, 9, BGEVENT_IFNOTSET, &TeamRocketBaseB3FLockedDoor),
    bg_event(11, 9, BGEVENT_IFNOTSET, &TeamRocketBaseB3FLockedDoor),
    bg_event(10, 1, BGEVENT_READ, &TeamRocketBaseB3FOathScript),
    bg_event(11, 1, BGEVENT_READ, &TeamRocketBaseB3FOathScript),
    bg_event(12, 1, BGEVENT_READ, &TeamRocketBaseB3FOathScript),
    bg_event(13, 1, BGEVENT_READ, &TeamRocketBaseB3FOathScript),
    bg_event(4, 13, BGEVENT_READ, &TeamRocketBaseB3FOathScript),
    bg_event(5, 13, BGEVENT_READ, &TeamRocketBaseB3FOathScript),
    bg_event(6, 13, BGEVENT_READ, &TeamRocketBaseB3FOathScript),
    bg_event(7, 13, BGEVENT_READ, &TeamRocketBaseB3FOathScript),
};

static const struct WarpEventData TeamRocketBaseB3F_WarpEvents[] = {
    warp_event(3, 2, TEAM_ROCKET_BASE_B2F, 2),
    warp_event(27, 2, TEAM_ROCKET_BASE_B2F, 3),
    warp_event(3, 6, TEAM_ROCKET_BASE_B2F, 4),
    warp_event(27, 14, TEAM_ROCKET_BASE_B2F, 5),
};

static const struct ObjEvent TeamRocketBaseB3F_ObjectEvents[] = {
    object_event(25, 14, SPRITE_LANCE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LanceGetPasswordScript, EVENT_TEAM_ROCKET_BASE_B3F_LANCE_PASSWORDS),
    object_event(8, 3, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_B3F_EXECUTIVE),
    object_event(7, 2, SPRITE_MOLTRES, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &RocketBaseMurkrow, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(21, 7, SPRITE_ROCKET_GIRL, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 0, &SlowpokeTailGrunt, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(5, 14, SPRITE_ROCKET, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &RaticateTailGrunt, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(23, 11, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 0, &TrainerScientistRoss, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(11, 15, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerScientistMitch, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(24, 14, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TeamRocketBaseB3FRocketScript, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(4, 5, SPRITE_SILVER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_RIVAL_TEAM_ROCKET_BASE),
    object_event(1, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB3FProtein, EVENT_TEAM_ROCKET_BASE_B3F_PROTEIN),
    object_event(3, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB3FXSpecial, EVENT_TEAM_ROCKET_BASE_B3F_X_SPECIAL),
    object_event(28, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB3FFullHeal, EVENT_TEAM_ROCKET_BASE_B3F_FULL_HEAL),
    object_event(17, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB3FIceHeal, EVENT_TEAM_ROCKET_BASE_B3F_ICE_HEAL),
    object_event(14, 10, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB3FUltraBall, EVENT_TEAM_ROCKET_BASE_B3F_ULTRA_BALL),
};

const struct MapEvents TeamRocketBaseB3F_MapEvents = {
    .warp_event_count = lengthof(TeamRocketBaseB3F_WarpEvents),
    .warp_events = TeamRocketBaseB3F_WarpEvents,

    .coord_event_count = lengthof(TeamRocketBaseB3F_CoordEvents),
    .coord_events = TeamRocketBaseB3F_CoordEvents,

    .bg_event_count = lengthof(TeamRocketBaseB3F_BGEvents),
    .bg_events = TeamRocketBaseB3F_BGEvents,

    .obj_event_count = lengthof(TeamRocketBaseB3F_ObjectEvents),
    .obj_events = TeamRocketBaseB3F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "TeamRocketBaseB3F.h"

bool TeamRocketBaseB3F_MapScripts_LanceGetsPassword(script_s* s) {
    SCRIPT_BEGIN
    sdefer(LanceGetPasswordScript)
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB3F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB3F_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB3F_MapScripts_DummyScene3(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB3F_MapScripts_CheckGiovanniDoor(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_OPENED_DOOR_TO_GIOVANNIS_OFFICE)
    iftrue(OpenSesame)
    s_endcallback
OpenSesame:
    changeblock(10, 8, 0x07) // floor
    s_endcallback
    SCRIPT_END
}
bool LanceGetPasswordScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, LEFT)
    pause(5)
    turnobject(TEAMROCKETBASEB3F_MOLTRES, RIGHT)
    pause(20)
    applymovement(TEAMROCKETBASEB3F_LANCE, RocketBaseLanceApproachesPlayerMovement)
    opentext
    writetext(LanceGetPasswordText)
    waitbutton
    closetext
    applymovement(TEAMROCKETBASEB3F_LANCE, RocketBaseLanceLeavesMovement)
    disappear(TEAMROCKETBASEB3F_LANCE)
    setscene(SCENE_TEAMROCKETBASEB3F_RIVAL_ENCOUNTER)
    s_end
    SCRIPT_END
}
bool RocketBaseRival(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, LEFT)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    special(FadeOutMusic)
    appear(TEAMROCKETBASEB3F_SILVER)
    applymovement(TEAMROCKETBASEB3F_SILVER, RocketBaseRivalEnterMovement)
    turnobject(PLAYER, LEFT)
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    opentext
    writetext(RocketBaseRivalText)
    waitbutton
    closetext
    playsound(SFX_TACKLE)
    applymovement(PLAYER, RocketBaseRivalShovesPlayerMovement)
    applymovement(TEAMROCKETBASEB3F_SILVER, RocketBaseRivalLeavesMovement)
    disappear(TEAMROCKETBASEB3F_SILVER)
    setscene(SCENE_TEAMROCKETBASEB3F_ROCKET_BOSS)
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB3FRocketScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(TeamRocketBaseB3FRocketText)
    SCRIPT_END
}
bool RocketBaseBossLeft(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, RocketBasePlayerApproachesBossLeftMovement)
    sjump(RocketBaseBoss)
    SCRIPT_END
}
bool RocketBaseBossRight(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, RocketBasePlayerApproachesBossRightMovement)
    SCRIPT_FALLTHROUGH(RocketBaseBoss)
}
bool RocketBaseBoss(script_s* s) {
    SCRIPT_BEGIN
    pause(30)
    showemote(EMOTE_SHOCK, TEAMROCKETBASEB3F_ROCKET1, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    turnobject(TEAMROCKETBASEB3F_ROCKET1, DOWN)
    opentext
    writetext(ExecutiveM4BeforeText)
    waitbutton
    closetext
    applymovement(TEAMROCKETBASEB3F_ROCKET1, RocketBaseBossApproachesPlayerMovement)
    winlosstext(ExecutiveM4BeatenText, 0)
    setlasttalked(TEAMROCKETBASEB3F_ROCKET1)
    loadtrainer(EXECUTIVEM, EXECUTIVEM_4)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_ROCKET_EXECUTIVEM_4)
    opentext
    writetext(ExecutiveM4AfterText)
    waitbutton
    closetext
    applymovement(TEAMROCKETBASEB3F_ROCKET1, RocketBaseBossHitsTableMovement)
    playsound(SFX_TACKLE)
    applymovement(TEAMROCKETBASEB3F_ROCKET1, RocketBaseBossLeavesMovement)
    disappear(TEAMROCKETBASEB3F_ROCKET1)
    setscene(SCENE_TEAMROCKETBASEB3F_NOTHING)
    s_end
    SCRIPT_END
}
bool RocketBaseMurkrow(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RocketBaseMurkrowText)
    waitbutton
    closetext
    setevent(EVENT_LEARNED_HAIL_GIOVANNI)
    s_end
    SCRIPT_END
}
const struct TrainerObj SlowpokeTailGrunt = {GRUNTF, GRUNTF_5, EVENT_BEAT_ROCKET_GRUNTF_5, GruntF5SeenText, GruntF5BeatenText, 0, GruntF5Script};
bool GruntF5Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntF5AfterBattleText)
    waitbutton
    closetext
    setevent(EVENT_LEARNED_SLOWPOKETAIL)
    s_end
    SCRIPT_END
}
const struct TrainerObj RaticateTailGrunt = {GRUNTM, GRUNTM_28, EVENT_BEAT_ROCKET_GRUNTM_28, GruntM28SeenText, GruntM28BeatenText, 0, GruntM28Script};
bool GruntM28Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM28AfterBattleText)
    waitbutton
    closetext
    setevent(EVENT_LEARNED_RATICATE_TAIL)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerScientistRoss = {SCIENTIST, ROSS, EVENT_BEAT_SCIENTIST_ROSS, ScientistRossSeenText, ScientistRossBeatenText, 0, TrainerScientistRoss_Script};
bool TrainerScientistRoss_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(ScientistRossAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerScientistMitch = {SCIENTIST, MITCH, EVENT_BEAT_SCIENTIST_MITCH, ScientistMitchSeenText, ScientistMitchBeatenText, 0, TrainerScientistMitch_Script};
bool TrainerScientistMitch_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(ScientistMitchAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB3FLockedDoor(script_s* s) {
    SCRIPT_BEGIN
    //conditional_event(EVENT_OPENED_DOOR_TO_GIOVANNIS_OFFICE, .Script)
Script:
    opentext
    checkevent(EVENT_LEARNED_SLOWPOKETAIL)
    iffalse(NeedsPassword)
    checkevent(EVENT_LEARNED_RATICATE_TAIL)
    iffalse(NeedsPassword)
    goto OpenSesame;
NeedsPassword:
    writetext(TeamRocketBaseB3FLockedDoorNeedsPasswordText)
    waitbutton
    closetext
    s_end
OpenSesame:
    writetext(TeamRocketBaseB3FLockedDoorOpenSesameText)
    waitbutton
    playsound(SFX_ENTER_DOOR)
    changeblock(10, 8, 0x07) // floor
    reloadmappart
    closetext
    setevent(EVENT_OPENED_DOOR_TO_GIOVANNIS_OFFICE)
    waitsfx
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB3FOathScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(TeamRocketOathScript)
    SCRIPT_END
}
const struct ItemBall TeamRocketBaseB3FProtein = {PROTEIN, 1};
const struct ItemBall TeamRocketBaseB3FXSpecial = {X_SPECIAL, 1};
const struct ItemBall TeamRocketBaseB3FFullHeal = {FULL_HEAL, 1};
const struct ItemBall TeamRocketBaseB3FIceHeal = {ICE_HEAL, 1};
const struct ItemBall TeamRocketBaseB3FUltraBall = {ULTRA_BALL, 1};
const uint8_t RocketBaseLanceApproachesPlayerMovement[] = {
    step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBaseLanceLeavesMovement[] = {
    step(DOWN),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t RocketBasePlayerApproachesBossLeftMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(LEFT),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t RocketBasePlayerApproachesBossRightMovement[] = {
    step(UP),
    step(UP),
    step(LEFT),
    step(UP),
    step(LEFT),
    step(LEFT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t RocketBaseBossApproachesPlayerMovement[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t RocketBaseBossHitsTableMovement[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBaseBossLeavesMovement[] = {
    movement_fix_facing,
    fast_jump_step(LEFT),
    movement_remove_fixed_facing,
    step_sleep(8),
    step_sleep(8),
    slow_step(RIGHT),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(RIGHT),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t RocketBaseRivalEnterMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t RocketBaseRivalLeavesMovement[] = {
    step(LEFT),
    step(LEFT),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t RocketBaseRivalShovesPlayerMovement[] = {
    movement_fix_facing,
    big_step(RIGHT),
    movement_remove_fixed_facing,
    movement_step_end,
};
const txt_cmd_s LanceGetPasswordText[] = {
    text_start("LANCE: It takes"
        t_line "two passwords to"
        t_para "get into the"
        t_line "boss's quarters."
        t_para "Those passwords"
        t_line "are known only to"
        t_cont "a few ROCKETS."
        t_para "That ROCKET there"
        t_line "very graciously"
        t_cont "told me so."
        t_para "<PLAY_G>, let's go"
        t_line "get the passwords."
        t_done )
};
const txt_cmd_s TeamRocketBaseB3FRocketText[] = {
    text_start("Urrggh… The guy"
        t_line "in the cape is"
        t_cont "incredibly tough…"
        t_done )
};
const txt_cmd_s RocketBaseRivalText[] = {
    text_start("…"
        t_para "Didn't I tell you"
        t_line "that I was going"
        t_para "to destroy TEAM"
        t_line "ROCKET?"
        t_para "…Tell me, who was"
        t_line "the guy in the"
        t_para "cape who used"
        t_line "dragon #MON?"
        t_para "My #MON were no"
        t_line "match at all."
        t_para "I don't care that"
        t_line "I lost. I can beat"
        t_para "him by getting"
        t_line "stronger #MON."
        t_para "It's what he said"
        t_line "that bothers me…"
        t_para "He told me that"
        t_line "I don't love and"
        t_para "trust my #MON"
        t_line "enough."
        t_para "I'm furious that I"
        t_line "lost to a bleeding"
        t_cont "heart like him."
        t_para "…Humph! I don't"
        t_line "have the time for"
        t_cont "the likes of you!"
        t_done )
};
const txt_cmd_s ExecutiveM4BeforeText[] = {
    text_start("What? Who are you?"
        t_line "This is the office"
        t_para "of our leader,"
        t_line "GIOVANNI."
        t_para "Since disbanding"
        t_line "TEAM ROCKET three"
        t_para "years ago, he has"
        t_line "been in training."
        t_para "But we're certain"
        t_line "he will be back"
        t_para "some day to assume"
        t_line "command again."
        t_para "That's why we're"
        t_line "standing guard."
        t_para "I won't let any-"
        t_line "one disturb this"
        t_cont "place!"
        t_done )
};
const txt_cmd_s ExecutiveM4BeatenText[] = {
    text_start("I… I couldn't do a"
        t_line "thing…"
        t_para "GIOVANNI, please"
        t_line "forgive me…"
        t_done )
};
const txt_cmd_s ExecutiveM4AfterText[] = {
    text_start("No, I can't let"
        t_line "this affect me."
        t_para "I have to inform"
        t_line "the others…"
        t_done )
};
const txt_cmd_s RocketBaseMurkrowText[] = {
    text_start("MURKROW: The"
        t_line "password is…"
        t_para "HAIL GIOVANNI."
        t_done )
};
const txt_cmd_s GruntF5SeenText[] = {
    text_start("Do I know the"
        t_line "password?"
        t_para "Maybe."
        t_para "But no weakling's"
        t_line "going to get it!"
        t_done )
};
const txt_cmd_s GruntF5BeatenText[] = {
    text_start("All right. Stop."
        t_line "I'll tell you."
        t_done )
};
const txt_cmd_s GruntF5AfterBattleText[] = {
    text_start("The password to"
        t_line "the boss's room is"
        t_para "SLOWPOKETAIL."
        t_para "But it's useless"
        t_line "unless you have"
        t_cont "two passwords."
        t_done )
};
const txt_cmd_s GruntM28SeenText[] = {
    text_start("Hyuck-hyuck-hyuck!"
        t_para "You're challenging"
        t_line "me to a battle?"
        t_para "Hah! You're nuts,"
        t_line "but you have guts!"
        t_para "I like that!"
        t_para "If you can beat"
        t_line "me, I'll tell you"
        t_para "a password to the"
        t_line "boss's room!"
        t_done )
};
const txt_cmd_s GruntM28BeatenText[] = {
    text_start("Hyuck-hyuck-hyuck!"
        t_line "You're good!"
        t_done )
};
const txt_cmd_s GruntM28AfterBattleText[] = {
    text_start("Hyuck-hyuck-hyuck!"
        t_para "The password to"
        t_line "the boss's room…"
        t_para "Uh…, I think it is"
        t_line "RATICATE TAIL."
        t_done )
};
const txt_cmd_s ScientistRossSeenText[] = {
    text_start("I used to work for"
        t_line "SILPH, but now I"
        t_para "run research for"
        t_line "TEAM ROCKET."
        t_para "A meddlesome child"
        t_line "like you needs to"
        t_cont "be punished."
        t_done )
};
const txt_cmd_s ScientistRossBeatenText[] = {
    text_start("A mere tactical"
        t_line "error cost me…"
        t_done )
};
const txt_cmd_s ScientistRossAfterBattleText[] = {
    text_start("A radio signal"
        t_line "that drives #-"
        t_cont "MON mad…"
        t_para "My experiment is a"
        t_line "complete success."
        t_para "My promotion is"
        t_line "assured. This loss"
        t_para "means absolutely"
        t_line "nothing."
        t_done )
};
const txt_cmd_s ScientistMitchSeenText[] = {
    text_start("I don't care that"
        t_line "#MON are hurt"
        t_cont "by our experiment."
        t_done )
};
const txt_cmd_s ScientistMitchBeatenText[] = {
    text_start("Thinking is my"
        t_line "strong suit, not"
        t_cont "battling."
        t_done )
};
const txt_cmd_s ScientistMitchAfterBattleText[] = {
    text_start("If we turn up the"
        t_line "power of our radio"
        t_para "signal for broad-"
        t_line "cast nationwide…"
        t_para "The very thought"
        t_line "excites me!"
        t_done )
};
const txt_cmd_s TeamRocketBaseB3FLockedDoorNeedsPasswordText[] = {
    text_start("The door's closed…"
        t_para "It needs two"
        t_line "passwords to open."
        t_done )
};
const txt_cmd_s TeamRocketBaseB3FLockedDoorOpenSesameText[] = {
    text_start("The door's closed…"
        t_para "<PLAYER> entered"
        t_line "the two passwords."
        t_para "The door opened!"
        t_done )
    //db(0, 0) // filler
};
