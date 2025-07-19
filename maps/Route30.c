#include "../constants.h"
#include "../util/scripting.h"
#include "Route30.h"
//// EVENTS
enum {
    ROUTE30_YOUNGSTER1 = 2,
    ROUTE30_YOUNGSTER2,
    ROUTE30_YOUNGSTER3,
    ROUTE30_BUG_CATCHER,
    ROUTE30_YOUNGSTER4,
    ROUTE30_MONSTER1,
    ROUTE30_MONSTER2,
    ROUTE30_FRUIT_TREE1,
    ROUTE30_FRUIT_TREE2,
    ROUTE30_COOLTRAINER_F,
    ROUTE30_POKE_BALL,
};

const Script_fn_t Route30_SceneScripts[] = {
    0,
};

const struct MapCallback Route30_MapCallbacks[] = {
    0,
};

const struct MapScripts Route30_MapScripts = {
    .scene_script_count = 0, // lengthof(Route30_SceneScripts),
    .scene_scripts = Route30_SceneScripts,

    .callback_count = 0, // lengthof(Route30_MapCallbacks),
    .callbacks = Route30_MapCallbacks,
};

static const struct CoordEvent Route30_CoordEvents[] = {
    0,
};

static const struct BGEvent Route30_BGEvents[] = {
    bg_event(9, 43, BGEVENT_READ, &Route30Sign),
    bg_event(13, 29, BGEVENT_READ, &MrPokemonsHouseDirectionsSign),
    bg_event(15, 5, BGEVENT_READ, &MrPokemonsHouseSign),
    bg_event(3, 21, BGEVENT_READ, &Route30TrainerTips),
    bg_event(14, 9, BGEVENT_ITEM, &Route30HiddenPotion),
};

static const struct WarpEventData Route30_WarpEvents[] = {
    warp_event(7, 39, ROUTE_30_BERRY_HOUSE, 1),
    warp_event(17, 5, MR_POKEMONS_HOUSE, 1),
};

static const struct ObjEvent Route30_ObjectEvents[] = {
    object_event(5, 26, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &YoungsterJoey_ImportantBattleScript, EVENT_ROUTE_30_BATTLE),
    object_event(2, 28, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerYoungsterJoey, EVENT_ROUTE_30_YOUNGSTER_JOEY),
    object_event(5, 23, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerYoungsterMikey, -1),
    object_event(1, 7, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBugCatcherDon, -1),
    object_event(7, 30, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route30YoungsterScript, -1),
    object_event(5, 24, SPRITE_MONSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_ROUTE_30_BATTLE),
    object_event(5, 25, SPRITE_MONSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_ROUTE_30_BATTLE),
    object_event(5, 39, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route30FruitTree1, -1),
    object_event(11, 5, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route30FruitTree2, -1),
    object_event(2, 13, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route30CooltrainerFScript, -1),
    object_event(8, 35, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route30Antidote, EVENT_ROUTE_30_ANTIDOTE),
};

const struct MapEvents Route30_MapEvents = {
    .warp_event_count = lengthof(Route30_WarpEvents),
    .warp_events = Route30_WarpEvents,

    .coord_event_count = 0, // lengthof(Route30_CoordEvents),
    .coord_events = Route30_CoordEvents,

    .bg_event_count = lengthof(Route30_BGEvents),
    .bg_events = Route30_BGEvents,

    .obj_event_count = lengthof(Route30_ObjectEvents),
    .obj_events = Route30_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route30.h"

bool YoungsterJoey_ImportantBattleScript(script_s* s) {
    SCRIPT_BEGIN
    waitsfx
    playmusic(MUSIC_JOHTO_TRAINER_BATTLE)
    opentext
    writetext(Text_UseTackle)
    pause(30)
    closetext
    playsound(SFX_TACKLE)
    applymovement(ROUTE30_MONSTER2, Route30_JoeysRattataAttacksMovement)
    opentext
    faceplayer
    writetext(Text_ThisIsABigBattle)
    waitbutton
    turnobject(ROUTE30_YOUNGSTER1, UP)
    closetext
    playsound(SFX_TACKLE)
    applymovement(ROUTE30_MONSTER1, Route30_MikeysRattataAttacksMovement)
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterJoey = {YOUNGSTER, JOEY1, EVENT_BEAT_YOUNGSTER_JOEY, YoungsterJoey1SeenText, YoungsterJoey1BeatenText, 0, TrainerYoungsterJoey_Script};
bool TrainerYoungsterJoey_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_YOUNGSTER_JOEY)
    endifjustbattled
    opentext
    checkflag(ENGINE_JOEY_READY_FOR_REMATCH)
    iftrue(Rematch)
    checkcellnum(PHONE_YOUNGSTER_JOEY)
    iftrue(NumberAccepted)
    checkevent(EVENT_JOEY_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(YoungsterJoey1AfterText)
    promptbutton
    setevent(EVENT_JOEY_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto RequestNumber;
AskAgain:
    scall_local(AskNumber2);
RequestNumber:
    askforphonenumber(PHONE_YOUNGSTER_JOEY)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, YOUNGSTER, JOEY1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
Rematch:
    scall_local(RematchStd);
    winlosstext(YoungsterJoey1BeatenText, 0)
    readmem(&gPlayer.JoeyFightCount)
    ifequal(4, Fight4)
    ifequal(3, Fight3)
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight4:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight4)
Fight3:
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(LoadFight3)
Fight2:
    checkflag(ENGINE_FLYPOINT_OLIVINE)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_GOLDENROD)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(YOUNGSTER, JOEY1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.JoeyFightCount, 1)
    clearflag(ENGINE_JOEY_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(YOUNGSTER, JOEY2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.JoeyFightCount, 2)
    clearflag(ENGINE_JOEY_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(YOUNGSTER, JOEY3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.JoeyFightCount, 3)
    clearflag(ENGINE_JOEY_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(YOUNGSTER, JOEY4)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.JoeyFightCount, 4)
    clearflag(ENGINE_JOEY_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(YOUNGSTER, JOEY5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_JOEY_READY_FOR_REMATCH)
    checkevent(EVENT_JOEY_HP_UP)
    iftrue(GiveHPUp)
    checkevent(EVENT_GOT_HP_UP_FROM_JOEY)
    iftrue(done)
    scall_local(RematchGift);
    verbosegiveitem(HP_UP, 1)
    iffalse(PackFull)
    setevent(EVENT_GOT_HP_UP_FROM_JOEY)
    goto NumberAccepted;
done:
    s_end
GiveHPUp:
    opentext
    writetext(YoungsterJoeyText_GiveHPUpAfterBattle)
    waitbutton
    verbosegiveitem(HP_UP, 1)
    iffalse(PackFull)
    clearevent(EVENT_JOEY_HP_UP)
    setevent(EVENT_GOT_HP_UP_FROM_JOEY)
    goto NumberAccepted;
AskNumber1:
    jumpstd(AskNumber1MScript)
    s_end
AskNumber2:
    jumpstd(AskNumber2MScript)
    s_end
RegisteredNumber:
    jumpstd(RegisteredNumberMScript)
    s_end
NumberAccepted:
    jumpstd(NumberAcceptedMScript)
    s_end
NumberDeclined:
    jumpstd(NumberDeclinedMScript)
    s_end
PhoneFull:
    jumpstd(PhoneFullMScript)
    s_end
RematchStd:
    jumpstd(RematchMScript)
    s_end
PackFull:
    setevent(EVENT_JOEY_HP_UP)
    jumpstd(PackFullMScript)
    s_end
RematchGift:
    jumpstd(RematchGiftMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterMikey = {YOUNGSTER, MIKEY, EVENT_BEAT_YOUNGSTER_MIKEY, YoungsterMikeySeenText, YoungsterMikeyBeatenText, 0, TrainerYoungsterMikey_Script};
bool TrainerYoungsterMikey_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterMikeyAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherDon = {BUG_CATCHER, DON, EVENT_BEAT_BUG_CATCHER_DON, BugCatcherDonSeenText, BugCatcherDonBeatenText, 0, TrainerBugCatcherDon_Script};
bool TrainerBugCatcherDon_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BugCatcherDonAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route30YoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue(CompletedEggQuest)
    writetext(Route30YoungsterText_DirectionsToMrPokemonsHouse)
    waitbutton
    closetext
    s_end
CompletedEggQuest:
    writetext(Route30YoungsterText_EveryoneIsBattling)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route30CooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route30CooltrainerFText)
    SCRIPT_END
}
bool Route30Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route30SignText)
    SCRIPT_END
}
bool MrPokemonsHouseDirectionsSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MrPokemonsHouseDirectionsSignText)
    SCRIPT_END
}
bool MrPokemonsHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MrPokemonsHouseSignText)
    SCRIPT_END
}
bool Route30TrainerTips(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route30TrainerTipsText)
    SCRIPT_END
}
const struct ItemBall Route30Antidote = {ANTIDOTE, 1};
bool Route30FruitTree1(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_30_1)
    SCRIPT_FALLTHROUGH(Route30FruitTree2)
}
bool Route30FruitTree2(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_30_2)
    SCRIPT_END
}
const struct HiddenItem Route30HiddenPotion = {POTION, EVENT_ROUTE_30_HIDDEN_POTION};
const uint8_t Route30_JoeysRattataAttacksMovement[] = {
    movement_fix_facing,
    big_step(UP),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t Route30_MikeysRattataAttacksMovement[] = {
    movement_fix_facing,
    big_step(DOWN),
    big_step(UP),
    movement_step_end,
};
const txt_cmd_s Text_UseTackle[] = {
    text_start("Go, RATTATA!"
        t_para "TACKLE!"
        t_done )
};
const txt_cmd_s Text_ThisIsABigBattle[] = {
    text_start("What? This is a"
        t_line "big battle!"
        t_cont "Leave me alone!"
        t_done )
};
const txt_cmd_s YoungsterJoey1SeenText[] = {
    text_start("I just lost, so"
        t_line "I'm trying to find"
        t_cont "more #MON."
        t_para "Wait! You look"
        t_line "weak! Come on,"
        t_cont "let's battle!"
        t_done )
};
const txt_cmd_s YoungsterJoey1BeatenText[] = {
    text_start("Ack! I lost again!"
        t_line "Doggone it!"
        t_done )
};
const txt_cmd_s YoungsterJoey1AfterText[] = {
    text_start("Do I have to have"
        t_line "more #MON in"
        t_para "order to battle"
        t_line "better?"
        t_para "No! I'm sticking"
        t_line "with this one no"
        t_cont "matter what!"
        t_done )
};
const txt_cmd_s YoungsterMikeySeenText[] = {
    text_start("You're a #MON"
        t_line "trainer, right?"
        t_para "Then you have to"
        t_line "battle!"
        t_done )
};
const txt_cmd_s YoungsterMikeyBeatenText[] = {
    text_start("That's strange."
        t_line "I won before."
        t_done )
};
const txt_cmd_s YoungsterMikeyAfterText[] = {
    text_start("Becoming a good"
        t_line "trainer is really"
        t_cont "tough."
        t_para "I'm going to bat-"
        t_line "tle other people"
        t_cont "to get better."
        t_done )
};
const txt_cmd_s BugCatcherDonSeenText[] = {
    text_start("Instead of a bug"
        t_line "#MON, I found"
        t_cont "a trainer!"
        t_done )
};
const txt_cmd_s BugCatcherDonBeatenText[] = {
    text_start("Argh! You're too"
        t_line "strong!"
        t_done )
};
const txt_cmd_s BugCatcherDonAfterText[] = {
    text_start("I ran out of #"
        t_line "BALLS while I was"
        t_cont "catching #MON."
        t_para "I should've bought"
        t_line "some more…"
        t_done )
};
const txt_cmd_s Route30YoungsterText_DirectionsToMrPokemonsHouse[] = {
    text_start("MR.#MON's"
        t_line "house? It's a bit"
        t_cont "farther ahead."
        t_done )
};
const txt_cmd_s Route30YoungsterText_EveryoneIsBattling[] = {
    text_start("Everyone's having"
        t_line "fun battling!"
        t_cont "You should too!"
        t_done )
};
const txt_cmd_s Route30CooltrainerFText[] = {
    text_start("I'm not a trainer."
        t_para "But if you look"
        t_line "one in the eyes,"
        t_cont "prepare to battle."
        t_done )
};
const txt_cmd_s Route30SignText[] = {
    text_start("ROUTE 30"
        t_para "VIOLET CITY -"
        t_line "CHERRYGROVE CITY"
        t_done )
};
const txt_cmd_s MrPokemonsHouseDirectionsSignText[] = {
    text_start("MR.#MON'S HOUSE"
        t_line "STRAIGHT AHEAD!"
        t_done )
};
const txt_cmd_s MrPokemonsHouseSignText[] = {
    text_start("MR.#MON'S HOUSE"
        t_done )
};
const txt_cmd_s Route30TrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "No stealing other"
        t_line "people's #MON!"
        t_para "# BALLS are to"
        t_line "be thrown only at"
        t_cont "wild #MON!"
        t_done )
};
const txt_cmd_s YoungsterJoeyText_GiveHPUpAfterBattle[] = {
    text_start("I lost again…"
        t_line "Gee, you're tough!"
        t_para "Oh yeah, I almost"
        t_line "forgot that I had"
        t_cont "to give you this."
        t_para "Use it to get even"
        t_line "tougher, OK?"
        t_para "I'm going to get"
        t_line "tougher too."
        t_done )
    //db(0, 0) // filler
};
