#include "../constants.h"
#include "../util/scripting.h"
#include "DragonsDenB1F.h"
//// EVENTS
enum {
    DRAGONSDENB1F_POKE_BALL1 = 2,
    DRAGONSDENB1F_CLAIR,
    DRAGONSDENB1F_SILVER,
    DRAGONSDENB1F_COOLTRAINER_M,
    DRAGONSDENB1F_COOLTRAINER_F,
    DRAGONSDENB1F_TWIN1,
    DRAGONSDENB1F_TWIN2,
    DRAGONSDENB1F_POKE_BALL2,
    DRAGONSDENB1F_POKE_BALL3,
};

const Script_fn_t DragonsDenB1F_SceneScripts[] = {
    DragonsDenB1F_MapScripts_DummyScene0 , //  SCENE_DRAGONSDENB1F_NOTHING,
    DragonsDenB1F_MapScripts_DummyScene1 , //  SCENE_DRAGONSDENB1F_CLAIR_GIVES_TM,
};

const struct MapCallback DragonsDenB1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, DragonsDenB1F_MapScripts_CheckSilver),
};

const struct MapScripts DragonsDenB1F_MapScripts = {
    .scene_script_count = lengthof(DragonsDenB1F_SceneScripts),
    .scene_scripts = DragonsDenB1F_SceneScripts,

    .callback_count = lengthof(DragonsDenB1F_MapCallbacks),
    .callbacks = DragonsDenB1F_MapCallbacks,
};

static const struct CoordEvent DragonsDenB1F_CoordEvents[] = {
    coord_event(19, 30, SCENE_DRAGONSDENB1F_CLAIR_GIVES_TM, &DragonsDenB1F_ClairScene),
};

static const struct BGEvent DragonsDenB1F_BGEvents[] = {
    bg_event(18, 24, BGEVENT_READ, &DragonShrineSignpost),
    bg_event(33, 29, BGEVENT_ITEM, &DragonsDenB1FHiddenRevive),
    bg_event(21, 17, BGEVENT_ITEM, &DragonsDenB1FHiddenMaxPotion),
    bg_event(31, 15, BGEVENT_ITEM, &DragonsDenB1FHiddenMaxElixer),
};

static const struct WarpEventData DragonsDenB1F_WarpEvents[] = {
    warp_event(20, 3, DRAGONS_DEN_1F, 3),
    warp_event(19, 29, DRAGON_SHRINE, 1),
};

static const struct ObjEvent DragonsDenB1F_ObjectEvents[] = {
    object_event(35, 16, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DragonsDenB1FDragonFangScript, EVENT_DRAGONS_DEN_B1F_DRAGON_FANG),
    object_event(14, 30, SPRITE_CLAIR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_DRAGONS_DEN_CLAIR),
    object_event(20, 23, SPRITE_SILVER, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DragonsDenB1FSilverScript, EVENT_RIVAL_DRAGONS_DEN),
    object_event(20, 8, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerCooltrainermDarin, -1),
    object_event(8, 8, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainerfCara, -1),
    object_event(4, 17, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsLeaandpia1, -1),
    object_event(4, 18, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsLeaandpia2, -1),
    object_event(30, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &DragonsDenB1FCalcium, EVENT_DRAGONS_DEN_B1F_CALCIUM),
    object_event(5, 20, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &DragonsDenB1FMaxElixer, EVENT_DRAGONS_DEN_B1F_MAX_ELIXER),
};

const struct MapEvents DragonsDenB1F_MapEvents = {
    .warp_event_count = lengthof(DragonsDenB1F_WarpEvents),
    .warp_events = DragonsDenB1F_WarpEvents,

    .coord_event_count = lengthof(DragonsDenB1F_CoordEvents),
    .coord_events = DragonsDenB1F_CoordEvents,

    .bg_event_count = lengthof(DragonsDenB1F_BGEvents),
    .bg_events = DragonsDenB1F_BGEvents,

    .obj_event_count = lengthof(DragonsDenB1F_ObjectEvents),
    .obj_events = DragonsDenB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "DragonsDenB1F.h"

bool DragonsDenB1F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool DragonsDenB1F_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool DragonsDenB1F_MapScripts_CheckSilver(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_BEAT_RIVAL_IN_MT_MOON)
    iftrue(CheckDay)
    disappear(DRAGONSDENB1F_SILVER)
    s_endcallback
CheckDay:
    readvar(VAR_WEEKDAY)
    ifequal(TUESDAY, AppearSilver)
    ifequal(THURSDAY, AppearSilver)
    disappear(DRAGONSDENB1F_SILVER)
    s_endcallback
AppearSilver:
    appear(DRAGONSDENB1F_SILVER)
    s_endcallback
    SCRIPT_END
}
bool DragonsDenB1F_ClairScene(script_s* s) {
    SCRIPT_BEGIN
    appear(DRAGONSDENB1F_CLAIR)
    opentext
    writetext(ClairText_Wait)
    pause(30)
    closetext
    showemote(EMOTE_SHOCK, PLAYER, 15)
    turnobject(PLAYER, LEFT)
    playmusic(MUSIC_CLAIR)
    applymovement(DRAGONSDENB1F_CLAIR, MovementDragonsDen_ClairWalksToYou)
    opentext
    writetext(ClairText_GiveDragonbreathDragonDen)
    promptbutton
    giveitem(TM_DRAGONBREATH, 1)
    iffalse(BagFull)
    getitemname(STRING_BUFFER_3, TM_DRAGONBREATH)
    writetext(Text_ReceivedTM24)
    playsound(SFX_ITEM)
    waitsfx
    itemnotify
    setevent(EVENT_GOT_TM24_DRAGONBREATH)
    writetext(ClairText_DescribeDragonbreathDragonDen)
    promptbutton
    writetext(ClairText_WhatsTheMatterDragonDen)
    waitbutton
    closetext
    goto FinishClair;
BagFull:
    writetext(ClairText_NoRoom)
    waitbutton
    closetext
FinishClair:
    applymovement(DRAGONSDENB1F_CLAIR, MovementDragonsDen_ClairWalksAway)
    special(FadeOutMusic)
    pause(30)
    special(RestartMapMusic)
    disappear(DRAGONSDENB1F_CLAIR)
    setscene(SCENE_DRAGONSDENB1F_NOTHING)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermDarin = {COOLTRAINERM, DARIN, EVENT_BEAT_COOLTRAINERM_DARIN, CooltrainermDarinSeenText, CooltrainermDarinBeatenText, 0, TrainerCooltrainermDarin_Script};
bool TrainerCooltrainermDarin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermDarinAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfCara = {COOLTRAINERF, CARA, EVENT_BEAT_COOLTRAINERF_CARA, CooltrainerfCaraSeenText, CooltrainerfCaraBeatenText, 0, TrainerCooltrainerfCara_Script};
bool TrainerCooltrainerfCara_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfCaraAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsLeaandpia1 = {TWINS, LEAANDPIA1, EVENT_BEAT_TWINS_LEA_AND_PIA, TwinsLeaandpia1SeenText, TwinsLeaandpia1BeatenText, 0, TrainerTwinsLeaandpia1_Script};
bool TrainerTwinsLeaandpia1_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsLeaandpia1AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsLeaandpia2 = {TWINS, LEAANDPIA1, EVENT_BEAT_TWINS_LEA_AND_PIA, TwinsLeaandpia2SeenText, TwinsLeaandpia2BeatenText, 0, TrainerTwinsLeaandpia2_Script};
bool TrainerTwinsLeaandpia2_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsLeaandpia2AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DragonsDenB1FDragonFangScript(script_s* s) {
    SCRIPT_BEGIN
// This whole script is written out rather than as an itemball
// because it's left over from the GS event.
    giveitem(DRAGON_FANG, 1)
    iffalse(BagFull)
    disappear(DRAGONSDENB1F_POKE_BALL1)
    opentext
    getitemname(STRING_BUFFER_3, DRAGON_FANG)
    writetext(Text_FoundDragonFang)
    playsound(SFX_ITEM)
    waitsfx
    itemnotify
    closetext
    s_end
BagFull:
    opentext
    getitemname(STRING_BUFFER_3, DRAGON_FANG)
    writetext(Text_FoundDragonFang)
    promptbutton
    writetext(Text_NoRoomForDragonFang)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DragonsDenB1FSilverScript(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_RIVAL_ENCOUNTER)
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue(SilverTalkAgain)
    writetext(SilverText_Training1)
    waitbutton
    closetext
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    special(RestartMapMusic)
    s_end
SilverTalkAgain:
    writetext(SilverText_Training2)
    waitbutton
    closetext
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool DragonShrineSignpost(script_s* s) {
    SCRIPT_BEGIN
    jumptext(DragonShrineSignpostText)
    SCRIPT_END
}
const struct ItemBall DragonsDenB1FCalcium = {CALCIUM, 1};
const struct ItemBall DragonsDenB1FMaxElixer = {MAX_ELIXER, 1};
const struct HiddenItem DragonsDenB1FHiddenRevive = {REVIVE, EVENT_DRAGONS_DEN_B1F_HIDDEN_REVIVE};
const struct HiddenItem DragonsDenB1FHiddenMaxPotion = {MAX_POTION, EVENT_DRAGONS_DEN_B1F_HIDDEN_MAX_POTION};
const struct HiddenItem DragonsDenB1FHiddenMaxElixer = {MAX_ELIXER, EVENT_DRAGONS_DEN_B1F_HIDDEN_MAX_ELIXER};
const uint8_t MovementDragonsDen_ClairWalksToYou[] = {
    slow_step(RIGHT),
    slow_step(RIGHT),
    slow_step(RIGHT),
    slow_step(RIGHT),
    movement_step_end,
};
const uint8_t MovementDragonsDen_ClairWalksAway[] = {
    slow_step(LEFT),
    slow_step(LEFT),
    slow_step(LEFT),
    slow_step(LEFT),
    movement_step_end,
};
const txt_cmd_s ClairText_Wait[] = {
    text_start("Wait!"
        t_done )
};
const txt_cmd_s ClairText_GiveDragonbreathDragonDen[] = {
    text_start("CLAIR: I'm sorry"
        t_line "about this."
        t_para "Here, take this as"
        t_line "my apology."
        t_done )
};
const txt_cmd_s Text_ReceivedTM24[] = {
    text_start("<PLAYER> received"
        t_line "TM24."
        t_done )
};
const txt_cmd_s ClairText_DescribeDragonbreathDragonDen[] = {
    text_start("That contains"
        t_line "DRAGONBREATH."
        t_para "No, it doesn't"
        t_line "have anything to"
        t_cont "do with my breath."
        t_para "If you don't want"
        t_line "it, you don't have"
        t_cont "to take it."
        t_done )
};
const txt_cmd_s ClairText_NoRoom[] = {
    text_start("Oh? You don't have"
        t_line "any room for this."
        t_para "I'm going back to"
        t_line "the GYM, so make"
        t_para "room, then come"
        t_line "see me there."
        t_done )
};
const txt_cmd_s ClairText_WhatsTheMatterDragonDen[] = {
    text_start("CLAIR: What's the"
        t_line "matter? Aren't you"
        t_para "going on to the"
        t_line "#MON LEAGUE?"
        t_para "Do you know how to"
        t_line "get there?"
        t_para "From here, go to"
        t_line "NEW BARK TOWN."
        t_para "Then SURF east to"
        t_line "#MON LEAGUE."
        t_para "The route there is"
        t_line "very tough."
        t_para "Don't you dare"
        t_line "lose at the #-"
        t_cont "MON LEAGUE!"
        t_para "If you do, I'll"
        t_line "feel even worse"
        t_para "about having lost"
        t_line "to you!"
        t_para "Give it everything"
        t_line "you've got."
        t_done )
};
const txt_cmd_s DragonShrineSignpostText[] = {
    text_start("DRAGON SHRINE"
        t_para "A shrine honoring"
        t_line "the dragon #MON"
        t_para "said to have lived"
        t_line "in DRAGON'S DEN."
        t_done )
};
const txt_cmd_s SilverText_Training1[] = {
    text_start("…"
        t_line "What? <PLAYER>?"
        t_para "…No, I won't"
        t_line "battle you now…"
        t_para "My #MON aren't"
        t_line "ready to beat you."
        t_para "I can't push them"
        t_line "too hard now."
        t_para "I have to be dis-"
        t_line "ciplined to become"
        t_para "the greatest #-"
        t_line "MON trainer…"
        t_done )
};
const txt_cmd_s SilverText_Training2[] = {
    text_start("…"
        t_para "Whew…"
        t_para "Learn to stay out"
        t_line "of my way…"
        t_done )
};
const txt_cmd_s CooltrainermDarinSeenText[] = {
    text_start("You! How dare you"
        t_line "enter uninvited!"
        t_done )
};
const txt_cmd_s CooltrainermDarinBeatenText[] = {
    text_start("S-strong!"
        t_done )
};
const txt_cmd_s CooltrainermDarinAfterBattleText[] = {
    text_start("The SHRINE ahead"
        t_line "is home to the"
        t_para "MASTER of our"
        t_line "dragon-user clan."
        t_para "You're not allowed"
        t_line "to just go in!"
        t_done )
};
const txt_cmd_s CooltrainerfCaraSeenText[] = {
    text_start("You shouldn't be"
        t_line "in here!"
        t_done )
};
const txt_cmd_s CooltrainerfCaraBeatenText[] = {
    text_start("Oh yikes, I lost!"
        t_done )
};
const txt_cmd_s CooltrainerfCaraAfterBattleText[] = {
    text_start("Soon I'm going to"
        t_line "get permission"
        t_para "from our MASTER to"
        t_line "use dragons."
        t_para "When I do, I'm"
        t_line "going to become an"
        t_para "admirable dragon"
        t_line "trainer and gain"
        t_para "our MASTER's"
        t_line "approval."
        t_done )
};
const txt_cmd_s TwinsLeaandpia1SeenText[] = {
    text_start("It's a stranger we"
        t_line "don't know."
        t_done )
};
const txt_cmd_s TwinsLeaandpia1BeatenText[] = {
    text_start("Ouchies."
        t_done )
};
const txt_cmd_s TwinsLeaandpia1AfterBattleText[] = {
    text_start("It was like having"
        t_line "to battle LANCE."
        t_done )
};
const txt_cmd_s TwinsLeaandpia2SeenText[] = {
    text_start("Who are you?"
        t_done )
};
const txt_cmd_s TwinsLeaandpia2BeatenText[] = {
    text_start("Meanie."
        t_done )
};
const txt_cmd_s TwinsLeaandpia2AfterBattleText[] = {
    text_start("We'll tell on you."
        t_para "MASTER will be"
        t_line "angry with you."
        t_done )
};
const txt_cmd_s Text_FoundDragonFang[] = {
    text_start("<PLAYER> found"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s Text_NoRoomForDragonFang[] = {
    text_start("But <PLAYER> can't"
        t_line "carry any more"
        t_cont "items."
        t_done )
    //db(0, 0) // filler
};
