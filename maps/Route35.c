#include "../constants.h"
#include "../util/scripting.h"
#include "Route35.h"
//// EVENTS
enum {
    ROUTE35_YOUNGSTER1 = 2,
    ROUTE35_YOUNGSTER2,
    ROUTE35_LASS1,
    ROUTE35_LASS2,
    ROUTE35_YOUNGSTER3,
    ROUTE35_FISHER,
    ROUTE35_BUG_CATCHER,
    ROUTE35_SUPER_NERD,
    ROUTE35_OFFICER,
    ROUTE35_FRUIT_TREE,
    ROUTE35_POKE_BALL,
};

const Script_fn_t Route35_SceneScripts[] = {
    0,
};

const struct MapCallback Route35_MapCallbacks[] = {
    0,
};

const struct MapScripts Route35_MapScripts = {
    .scene_script_count = 0, // lengthof(Route35_SceneScripts),
    .scene_scripts = Route35_SceneScripts,

    .callback_count = 0, // lengthof(Route35_MapCallbacks),
    .callbacks = Route35_MapCallbacks,
};

static const struct CoordEvent Route35_CoordEvents[] = {
    0,
};

static const struct BGEvent Route35_BGEvents[] = {
    bg_event(1, 7, BGEVENT_READ, &Route35Sign),
    bg_event(11, 31, BGEVENT_READ, &Route35Sign),
};

static const struct WarpEventData Route35_WarpEvents[] = {
    warp_event(9, 33, ROUTE_35_GOLDENROD_GATE, 1),
    warp_event(10, 33, ROUTE_35_GOLDENROD_GATE, 2),
    warp_event(3, 5, ROUTE_35_NATIONAL_PARK_GATE, 3),
};

static const struct ObjEvent Route35_ObjectEvents[] = {
    object_event(4, 19, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerCamperIvan, -1),
    object_event(8, 20, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerCamperElliot, -1),
    object_event(7, 20, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerPicnickerBrooke, -1),
    object_event(10, 26, SPRITE_LASS, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerPicnickerKim, -1),
    object_event(14, 28, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 0, &TrainerBirdKeeperBryan, -1),
    object_event(2, 10, SPRITE_FISHER, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerFirebreatherWalt, -1),
    object_event(16, 7, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 2, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerBugCatcherArnie, -1),
    object_event(5, 10, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerJugglerIrwin, -1),
    object_event(5, 6, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &TrainerOfficerDirk, -1),
    object_event(2, 25, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route35FruitTree, -1),
    object_event(13, 16, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route35TMRollout, EVENT_ROUTE_35_TM_ROLLOUT),
};

const struct MapEvents Route35_MapEvents = {
    .warp_event_count = lengthof(Route35_WarpEvents),
    .warp_events = Route35_WarpEvents,

    .coord_event_count = 0, // lengthof(Route35_CoordEvents),
    .coord_events = Route35_CoordEvents,

    .bg_event_count = lengthof(Route35_BGEvents),
    .bg_events = Route35_BGEvents,

    .obj_event_count = lengthof(Route35_ObjectEvents),
    .obj_events = Route35_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route35.h"

const struct TrainerObj TrainerBirdKeeperBryan = {BIRD_KEEPER, BRYAN, EVENT_BEAT_BIRD_KEEPER_BRYAN, BirdKeeperBryanSeenText, BirdKeeperBryanBeatenText, 0, TrainerBirdKeeperBryan_Script};
bool TrainerBirdKeeperBryan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperBryanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerJugglerIrwin = {JUGGLER, IRWIN1, EVENT_BEAT_JUGGLER_IRWIN, JugglerIrwin1SeenText, JugglerIrwin1BeatenText, 0, TrainerJugglerIrwin_Script};
bool TrainerJugglerIrwin_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_JUGGLER_IRWIN)
    endifjustbattled
    opentext
    checkcellnum(PHONE_JUGGLER_IRWIN)
    iftrue_jump(Route35NumberAcceptedM)
    checkevent(EVENT_IRWIN_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(JugglerIrwinAfterBattleText)
    promptbutton
    setevent(EVENT_IRWIN_ASKED_FOR_PHONE_NUMBER)
    scall(Route35AskNumber1M)
    goto AskForNumber;
AskedAlready:
    scall(Route35AskNumber2M)
AskForNumber:
    askforphonenumber(PHONE_JUGGLER_IRWIN)
    ifequal_jump(PHONE_CONTACTS_FULL, Route35PhoneFullM)
    ifequal_jump(PHONE_CONTACT_REFUSED, Route35NumberDeclinedM)
    gettrainername(STRING_BUFFER_3, JUGGLER, IRWIN1)
    scall(Route35RegisteredNumberM)
    sjump(Route35NumberAcceptedM)
    SCRIPT_END
}
bool Route35AskNumber1M(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(AskNumber1MScript)
    s_end
    SCRIPT_END
}
bool Route35AskNumber2M(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(AskNumber2MScript)
    s_end
    SCRIPT_END
}
bool Route35RegisteredNumberM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RegisteredNumberMScript)
    s_end
    SCRIPT_END
}
bool Route35NumberAcceptedM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(NumberAcceptedMScript)
    s_end
    SCRIPT_END
}
bool Route35NumberDeclinedM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(NumberDeclinedMScript)
    s_end
    SCRIPT_END
}
bool Route35PhoneFullM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PhoneFullMScript)
    s_end
    SCRIPT_END
}
bool Route35RematchM(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RematchMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCamperIvan = {CAMPER, IVAN, EVENT_BEAT_CAMPER_IVAN, CamperIvanSeenText, CamperIvanBeatenText, 0, TrainerCamperIvan_Script};
bool TrainerCamperIvan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperIvanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCamperElliot = {CAMPER, ELLIOT, EVENT_BEAT_CAMPER_ELLIOT, CamperElliotSeenText, CamperElliotBeatenText, 0, TrainerCamperElliot_Script};
bool TrainerCamperElliot_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperElliotAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerBrooke = {PICNICKER, BROOKE, EVENT_BEAT_PICNICKER_BROOKE, PicnickerBrookeSeenText, PicnickerBrookeBeatenText, 0, TrainerPicnickerBrooke_Script};
bool TrainerPicnickerBrooke_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PicnickerBrookeAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerKim = {PICNICKER, KIM, EVENT_BEAT_PICNICKER_KIM, PicnickerKimSeenText, PicnickerKimBeatenText, 0, TrainerPicnickerKim_Script};
bool TrainerPicnickerKim_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PicnickerKimAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherArnie = {BUG_CATCHER, ARNIE1, EVENT_BEAT_BUG_CATCHER_ARNIE, BugCatcherArnieSeenText, BugCatcherArnieBeatenText, 0, TrainerBugCatcherArnie_Script};
bool TrainerBugCatcherArnie_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_BUG_CATCHER_ARNIE)
    endifjustbattled
    opentext
    checkflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkflag(ENGINE_YANMA_SWARM)
    iftrue(YanmaSwarming)
    checkcellnum(PHONE_BUG_CATCHER_ARNIE)
    iftrue_jump(Route35NumberAcceptedM)
    checkevent(EVENT_ARNIE_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(BugCatcherArnieAfterBattleText)
    promptbutton
    setevent(EVENT_ARNIE_ASKED_FOR_PHONE_NUMBER)
    scall(Route35AskNumber1M)
    goto AskForNumber;
AskedAlready:
    scall(Route35AskNumber2M)
AskForNumber:
    askforphonenumber(PHONE_BUG_CATCHER_ARNIE)
    ifequal_jump(PHONE_CONTACTS_FULL, Route35PhoneFullM)
    ifequal_jump(PHONE_CONTACT_REFUSED, Route35NumberDeclinedM)
    gettrainername(STRING_BUFFER_3, BUG_CATCHER, ARNIE1)
    scall(Route35RegisteredNumberM)
    sjump(Route35NumberAcceptedM)
WantsBattle:
    scall(Route35RematchM)
    winlosstext(BugCatcherArnieBeatenText, 0)
    readmem(&gPlayer.ArnieFightCount)
    ifequal(4, Fight4)
    ifequal(3, Fight3)
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight4:
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight4)
Fight3:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight3)
Fight2:
    checkflag(ENGINE_FLYPOINT_BLACKTHORN)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_LAKE_OF_RAGE)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(BUG_CATCHER, ARNIE1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ArnieFightCount, 1)
    clearflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(BUG_CATCHER, ARNIE2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ArnieFightCount, 2)
    clearflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(BUG_CATCHER, ARNIE3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ArnieFightCount, 3)
    clearflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(BUG_CATCHER, ARNIE4)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ArnieFightCount, 4)
    clearflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(BUG_CATCHER, ARNIE5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_ARNIE_READY_FOR_REMATCH)
    s_end
YanmaSwarming:
    writetext(BugCatcherArnieYanmaText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFirebreatherWalt = {FIREBREATHER, WALT, EVENT_BEAT_FIREBREATHER_WALT, FirebreatherWaltSeenText, FirebreatherWaltBeatenText, 0, TrainerFirebreatherWalt_Script};
bool TrainerFirebreatherWalt_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FirebreatherWaltAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TrainerOfficerDirk(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checktime(NITE)
    iffalse(NotNight)
    checkevent(EVENT_BEAT_OFFICER_DIRK)
    iftrue(AfterBattle)
    playmusic(MUSIC_OFFICER_ENCOUNTER)
    writetext(OfficerDirkSeenText)
    waitbutton
    closetext
    winlosstext(OfficerDirkBeatenText, 0)
    loadtrainer(OFFICER, DIRK)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_OFFICER_DIRK)
    closetext
    s_end
AfterBattle:
    writetext(OfficerDirkAfterBattleText)
    waitbutton
    closetext
    s_end
NotNight:
    writetext(OfficerDirkPrettyToughText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route35SignText)
    SCRIPT_END
}
const struct ItemBall Route35TMRollout = {TM_ROLLOUT, 1};
bool Route35FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_35)
    SCRIPT_END
}
const txt_cmd_s CamperIvanSeenText[] = {
    text_start("I've been getting"
        t_line "#MON data off"
        t_para "my radio. I think"
        t_line "I'm good."
        t_done )
};
const txt_cmd_s CamperIvanBeatenText[] = {
    text_start("I give!"
        t_done )
};
const txt_cmd_s CamperIvanAfterBattleText[] = {
    text_start("Music on the radio"
        t_line "changes the moods"
        t_cont "of wild #MON."
        t_done )
};
const txt_cmd_s CamperElliotSeenText[] = {
    text_start("I'm gonna show my"
        t_line "girlfriend I'm hot"
        t_cont "stuff!"
        t_done )
};
const txt_cmd_s CamperElliotBeatenText[] = {
    text_start("I wish you would"
        t_line "have lost for me…"
        t_done )
};
const txt_cmd_s CamperElliotAfterBattleText[] = {
    text_start("I was humiliated"
        t_line "in front of my"
        t_cont "girlfriend…"
        t_done )
};
const txt_cmd_s PicnickerBrookeSeenText[] = {
    text_start("My boyfriend's"
        t_line "weak, so I can't"
        t_cont "rely on him."
        t_done )
};
const txt_cmd_s PicnickerBrookeBeatenText[] = {
    text_start("Oh, my! You're so"
        t_line "strong!"
        t_done )
};
const txt_cmd_s PicnickerBrookeAfterBattleText[] = {
    text_start("I can count on my"
        t_line "#MON more than"
        t_cont "my boyfriend."
        t_done )
};
const txt_cmd_s PicnickerKimSeenText[] = {
    text_start("Are you going to"
        t_line "the GYM? Me too!"
        t_done )
};
const txt_cmd_s PicnickerKimBeatenText[] = {
    text_start("Oh. I couldn't"
        t_line "win…"
        t_done )
};
const txt_cmd_s PicnickerKimAfterBattleText[] = {
    text_start("The GYM BADGES are"
        t_line "pretty. I collect"
        t_cont "them."
        t_done )
};
const txt_cmd_s BirdKeeperBryanSeenText[] = {
    text_start("What kinds of"
        t_line "BALLS do you use?"
        t_done )
};
const txt_cmd_s BirdKeeperBryanBeatenText[] = {
    text_start("Yikes! Not fast"
        t_line "enough!"
        t_done )
};
const txt_cmd_s BirdKeeperBryanAfterBattleText[] = {
    text_start("Some #MON flee"
        t_line "right away."
        t_para "Try catching them"
        t_line "with KURT's FAST"
        t_cont "BALL."
        t_para "Whenever I find a"
        t_line "WHT APRICORN, I"
        t_cont "take it to KURT."
        t_para "He turns it into a"
        t_line "custom BALL."
        t_done )
};
const txt_cmd_s JugglerIrwin1SeenText[] = {
    text_start("Behold my graceful"
        t_line "BALL dexterity!"
        t_done )
};
const txt_cmd_s JugglerIrwin1BeatenText[] = {
    text_start("Whew! That was a"
        t_line "jolt!"
        t_done )
};
const txt_cmd_s JugglerIrwinAfterBattleText[] = {
    text_start("I was going to"
        t_line "dazzle you with my"
        t_cont "prize #MON."
        t_para "But your prowess"
        t_line "electrified me!"
        t_done )
};
const txt_cmd_s BugCatcherArnieSeenText[] = {
    text_start("I'll go anywhere"
        t_line "if bug #MON"
        t_cont "appear there."
        t_done )
};
const txt_cmd_s BugCatcherArnieBeatenText[] = {
    text_start("Huh? I shouldn't"
        t_line "have lost that…"
        t_done )
};
const txt_cmd_s BugCatcherArnieAfterBattleText[] = {
    text_start("My VENONAT won me"
        t_line "the Bug-Catching"
        t_para "Contest at the"
        t_line "NATIONAL PARK."
        t_done )
};
const txt_cmd_s BugCatcherArnieYanmaText[] = {
    text_start("Wow… Look at all"
        t_line "those YANMA!"
        t_para "I'm so blown away,"
        t_line "I can't move."
        t_done )
};
const txt_cmd_s FirebreatherWaltSeenText[] = {
    text_start("I'm practicing my"
        t_line "fire breathing."
        t_done )
};
const txt_cmd_s FirebreatherWaltBeatenText[] = {
    text_start("Ow! I scorched the"
        t_line "tip of my nose!"
        t_done )
};
const txt_cmd_s FirebreatherWaltAfterBattleText[] = {
    text_start("The #MON March"
        t_line "on the radio lures"
        t_cont "wild #MON."
        t_done )
};
const txt_cmd_s OfficerDirkSeenText[] = {
    text_start("Danger lurks in"
        t_line "the night!"
        t_done )
};
const txt_cmd_s OfficerDirkBeatenText[] = {
    text_start("Whoops!"
        t_done )
};
const txt_cmd_s OfficerDirkAfterBattleText[] = {
    text_start("You know, night-"
        t_line "time is fun in its"
        t_cont "own ways."
        t_para "But don't overdo"
        t_line "it, OK?"
        t_done )
};
const txt_cmd_s OfficerDirkPrettyToughText[] = {
    text_start("Your #MON look"
        t_line "pretty tough."
        t_para "You could go any-"
        t_line "where safely."
        t_done )
};
const txt_cmd_s Route35SignText[] = {
    text_start("ROUTE 35"
        t_done )
    //db(0, 0) // filler
};
