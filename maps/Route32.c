#include "../constants.h"
#include "../util/scripting.h"
#include "Route32.h"
//// EVENTS
enum {
    ROUTE32_FISHER1 = 2,
    ROUTE32_FISHER2,
    ROUTE32_FISHER3,
    ROUTE32_YOUNGSTER1,
    ROUTE32_YOUNGSTER2,
    ROUTE32_YOUNGSTER3,
    ROUTE32_LASS1,
    ROUTE32_COOLTRAINER_M,
    ROUTE32_YOUNGSTER4,
    ROUTE32_FISHER4,
    ROUTE32_POKE_BALL1,
    ROUTE32_FISHER5,
    ROUTE32_FRIEDA,
    ROUTE32_POKE_BALL2,
};

const Script_fn_t Route32_SceneScripts[] = {
    Route32_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    Route32_MapScripts_DummyScene1 , //  SCENE_ROUTE32_OFFER_SLOWPOKETAIL,
    Route32_MapScripts_DummyScene2 , //  SCENE_ROUTE32_NOTHING,
};

const struct MapCallback Route32_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Route32_MapScripts_Frieda),
};

const struct MapScripts Route32_MapScripts = {
    .scene_script_count = lengthof(Route32_SceneScripts),
    .scene_scripts = Route32_SceneScripts,

    .callback_count = lengthof(Route32_MapCallbacks),
    .callbacks = Route32_MapCallbacks,
};

static const struct CoordEvent Route32_CoordEvents[] = {
    coord_event(18, 8, SCENE_DEFAULT, &Route32CooltrainerMStopsYouScene),
    coord_event(7, 71, SCENE_ROUTE32_OFFER_SLOWPOKETAIL, &Route32WannaBuyASlowpokeTailScript),
};

static const struct BGEvent Route32_BGEvents[] = {
    bg_event(13, 5, BGEVENT_READ, &Route32Sign),
    bg_event(9, 1, BGEVENT_READ, &Route32RuinsSign),
    bg_event(10, 84, BGEVENT_READ, &Route32UnionCaveSign),
    bg_event(12, 73, BGEVENT_READ, &Route32PokecenterSign),
    bg_event(12, 67, BGEVENT_ITEM, &Route32HiddenGreatBall),
    bg_event(11, 40, BGEVENT_ITEM, &Route32HiddenSuperPotion),
};

static const struct WarpEventData Route32_WarpEvents[] = {
    warp_event(11, 73, ROUTE_32_POKECENTER_1F, 1),
    warp_event(4, 2, ROUTE_32_RUINS_OF_ALPH_GATE, 3),
    warp_event(4, 3, ROUTE_32_RUINS_OF_ALPH_GATE, 4),
    warp_event(6, 79, UNION_CAVE_1F, 4),
};

static const struct ObjEvent Route32_ObjectEvents[] = {
    object_event(8, 49, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerFisherJustin, -1),
    object_event(12, 56, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerFisherRalph1, -1),
    object_event(6, 48, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerFisherHenry, -1),
    object_event(12, 22, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerYoungsterAlbert, -1),
    object_event(4, 63, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerYoungsterGordon, -1),
    object_event(3, 45, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerCamperRoland, -1),
    object_event(10, 30, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerPicnickerLiz1, -1),
    object_event(19, 8, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route32CooltrainerMScript, -1),
    object_event(11, 82, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerBirdKeeperPeter, -1),
    object_event(7, 70, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SlowpokeTailSalesmanScript, EVENT_SLOWPOKE_WELL_ROCKETS),
    object_event(6, 53, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route32GreatBall, EVENT_ROUTE_32_GREAT_BALL),
    object_event(15, 13, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route32RoarTMGuyScript, -1),
    object_event(12, 67, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FriedaScript, EVENT_ROUTE_32_FRIEDA_OF_FRIDAY),
    object_event(3, 30, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route32Repel, EVENT_ROUTE_32_REPEL),
};

const struct MapEvents Route32_MapEvents = {
    .warp_event_count = lengthof(Route32_WarpEvents),
    .warp_events = Route32_WarpEvents,

    .coord_event_count = lengthof(Route32_CoordEvents),
    .coord_events = Route32_CoordEvents,

    .bg_event_count = lengthof(Route32_BGEvents),
    .bg_events = Route32_BGEvents,

    .obj_event_count = lengthof(Route32_ObjectEvents),
    .obj_events = Route32_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route32.h"

bool Route32_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route32_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route32_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route32_MapScripts_Frieda(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal_jump(FRIDAY, Route32_MapScripts_FriedaAppears)
    disappear(ROUTE32_FRIEDA)
    s_endcallback
    SCRIPT_END
}
bool Route32_MapScripts_FriedaAppears(script_s* s) {
    SCRIPT_BEGIN
    appear(ROUTE32_FRIEDA)
    s_endcallback
    SCRIPT_END
}
bool Route32CooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    SCRIPT_FALLTHROUGH(Route32CooltrainerMContinueScene)
}
bool Route32CooltrainerMContinueScene(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_GOT_MIRACLE_SEED_IN_ROUTE_32)
    iftrue(GotMiracleSeed)
    checkflag(ENGINE_ZEPHYRBADGE)
    iffalse(DontHaveZephyrBadge)
    checkevent(EVENT_GOT_TOGEPI_EGG_FROM_ELMS_AIDE)
    iftrue(GiveMiracleSeed)
    writetext(Route32CooltrainerMText_AideIsWaiting)
    waitbutton
    closetext
    s_end
GoToSproutTower:
    writetext(Route32CooltrainerMText_UnusedSproutTower)
    waitbutton
    closetext
    s_end
GiveMiracleSeed:
    writetext(Route32CooltrainerMText_HaveThisSeed)
    promptbutton
    verbosegiveitem(MIRACLE_SEED, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_MIRACLE_SEED_IN_ROUTE_32)
    goto GotMiracleSeed;
DontHaveZephyrBadge:
    writetext(Route32CooltrainerMText_VioletGym)
    waitbutton
    closetext
    s_end
GotMiracleSeed:
    writetext(Route32CooltrainerMText_ExperiencesShouldBeUseful)
    waitbutton
BagFull:
    closetext
    s_end
    SCRIPT_END
}
bool Route32CooltrainerMStopsYouScene(script_s* s) {
    SCRIPT_BEGIN
    turnobject(ROUTE32_COOLTRAINER_M, LEFT)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(Route32CooltrainerMText_WhatsTheHurry)
    waitbutton
    closetext
    follow(PLAYER, ROUTE32_COOLTRAINER_M)
    applymovement(PLAYER, Movement_Route32CooltrainerMPushesYouBackToViolet)
    stopfollow
    turnobject(PLAYER, DOWN)
    scall(Route32CooltrainerMContinueScene)
    applymovement(ROUTE32_COOLTRAINER_M, Movement_Route32CooltrainerMReset1)
    applymovement(ROUTE32_COOLTRAINER_M, Movement_Route32CooltrainerMReset2)
    s_end
    SCRIPT_END
}
bool Route32RoarTMGuyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM05_ROAR)
    iftrue(AlreadyHaveRoar)
    writetext(Text_RoarIntro)
    promptbutton
    verbosegiveitem(TM_ROAR, 1)
    iffalse(Finish)
    setevent(EVENT_GOT_TM05_ROAR)
AlreadyHaveRoar:
    writetext(Text_RoarOutro)
    waitbutton
Finish:
    closetext
    s_end
    SCRIPT_END
}
bool Route32WannaBuyASlowpokeTailScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(ROUTE32_FISHER4, DOWN)
    turnobject(PLAYER, UP)
    sjump(_OfferToSellSlowpokeTail)
    SCRIPT_END
}
bool SlowpokeTailSalesmanScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    SCRIPT_FALLTHROUGH(_OfferToSellSlowpokeTail)
}
bool _OfferToSellSlowpokeTail(script_s* s) {
    SCRIPT_BEGIN
    setscene(SCENE_ROUTE32_NOTHING)
    opentext
    writetext(Text_MillionDollarSlowpokeTail)
    yesorno
    iffalse(refused)
    writetext(Text_ThoughtKidsWereLoaded)
    waitbutton
    closetext
    s_end
refused:
    writetext(Text_RefusedToBuySlowpokeTail)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCamperRoland = {CAMPER, ROLAND, EVENT_BEAT_CAMPER_ROLAND, CamperRolandSeenText, CamperRolandBeatenText, 0, TrainerCamperRoland_Script};
bool TrainerCamperRoland_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperRolandAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherJustin = {FISHER, JUSTIN, EVENT_BEAT_FISHER_JUSTIN, FisherJustinSeenText, FisherJustinBeatenText, 0, TrainerFisherJustin_Script};
bool TrainerFisherJustin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherJustinAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherRalph1 = {FISHER, RALPH1, EVENT_BEAT_FISHER_RALPH, FisherRalph1SeenText, FisherRalph1BeatenText, 0, TrainerFisherRalph1_Script};
bool TrainerFisherRalph1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_FISHER_RALPH)
    endifjustbattled
    opentext
    checkflag(ENGINE_RALPH_READY_FOR_REMATCH)
    iftrue(Rematch)
    checkflag(ENGINE_FISH_SWARM)
    iftrue(Swarm)
    checkcellnum(PHONE_FISHER_RALPH)
    iftrue(NumberAccepted)
    checkevent(EVENT_RALPH_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(FisherRalphAfterText)
    promptbutton
    setevent(EVENT_RALPH_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskAgain:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_FISHER_RALPH)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, FISHER, RALPH1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
Rematch:
    scall_local(RematchStd);
    winlosstext(FisherRalph1BeatenText, 0)
    readmem(&gPlayer.RalphFightCount)
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
    checkflag(ENGINE_FLYPOINT_LAKE_OF_RAGE)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_ECRUTEAK)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(FISHER, RALPH1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.RalphFightCount, 1)
    clearflag(ENGINE_RALPH_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(FISHER, RALPH2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.RalphFightCount, 2)
    clearflag(ENGINE_RALPH_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(FISHER, RALPH3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.RalphFightCount, 3)
    clearflag(ENGINE_RALPH_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(FISHER, RALPH4)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.RalphFightCount, 4)
    clearflag(ENGINE_RALPH_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(FISHER, RALPH5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_RALPH_READY_FOR_REMATCH)
    s_end
Swarm:
    writetext(FisherRalphSwarmText)
    waitbutton
    closetext
    s_end
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
    SCRIPT_END
}
const struct TrainerObj TrainerFisherHenry = {FISHER, HENRY, EVENT_BEAT_FISHER_HENRY, FisherHenrySeenText, FisherHenryBeatenText, 0, TrainerFisherHenry_Script};
bool TrainerFisherHenry_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherHenryAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerLiz1 = {PICNICKER, LIZ1, EVENT_BEAT_PICNICKER_LIZ, PicnickerLiz1SeenText, PicnickerLiz1BeatenText, 0, TrainerPicnickerLiz1_Script};
bool TrainerPicnickerLiz1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_PICNICKER_LIZ)
    endifjustbattled
    opentext
    checkflag(ENGINE_LIZ_READY_FOR_REMATCH)
    iftrue(Rematch)
    checkcellnum(PHONE_PICNICKER_LIZ)
    iftrue(NumberAccepted)
    checkevent(EVENT_LIZ_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(PicnickerLiz1AfterText)
    promptbutton
    setevent(EVENT_LIZ_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskAgain:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_PICNICKER_LIZ)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, PICNICKER, LIZ1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
Rematch:
    scall_local(RematchStd);
    winlosstext(PicnickerLiz1BeatenText, 0)
    readmem(&gPlayer.LizFightCount)
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
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_ECRUTEAK)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(PICNICKER, LIZ1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.LizFightCount, 1)
    clearflag(ENGINE_LIZ_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(PICNICKER, LIZ2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.LizFightCount, 2)
    clearflag(ENGINE_LIZ_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(PICNICKER, LIZ3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.LizFightCount, 3)
    clearflag(ENGINE_LIZ_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(PICNICKER, LIZ4)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.LizFightCount, 4)
    clearflag(ENGINE_LIZ_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(PICNICKER, LIZ5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_LIZ_READY_FOR_REMATCH)
    s_end
AskNumber1:
    jumpstd(AskNumber1FScript)
    s_end
AskNumber2:
    jumpstd(AskNumber2FScript)
    s_end
RegisteredNumber:
    jumpstd(RegisteredNumberFScript)
    s_end
NumberAccepted:
    jumpstd(NumberAcceptedFScript)
    s_end
NumberDeclined:
    jumpstd(NumberDeclinedFScript)
    s_end
PhoneFull:
    jumpstd(PhoneFullFScript)
    s_end
RematchStd:
    jumpstd(RematchFScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterAlbert = {YOUNGSTER, ALBERT, EVENT_BEAT_YOUNGSTER_ALBERT, YoungsterAlbertSeenText, YoungsterAlbertBeatenText, 0, TrainerYoungsterAlbert_Script};
bool TrainerYoungsterAlbert_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterAlbertAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterGordon = {YOUNGSTER, GORDON, EVENT_BEAT_YOUNGSTER_GORDON, YoungsterGordonSeenText, YoungsterGordonBeatenText, 0, TrainerYoungsterGordon_Script};
bool TrainerYoungsterGordon_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterGordonAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBirdKeeperPeter = {BIRD_KEEPER, PETER, EVENT_BEAT_BIRD_KEEPER_PETER, BirdKeeperPeterSeenText, BirdKeeperPeterBeatenText, 0, TrainerBirdKeeperPeter_Script};
bool TrainerBirdKeeperPeter_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperPeterAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FriedaScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_POISON_BARB_FROM_FRIEDA)
    iftrue(Friday)
    readvar(VAR_WEEKDAY)
    ifnotequal(FRIDAY, NotFriday)
    checkevent(EVENT_MET_FRIEDA_OF_FRIDAY)
    iftrue(MetFrieda)
    writetext(MeetFriedaText)
    promptbutton
    setevent(EVENT_MET_FRIEDA_OF_FRIDAY)
MetFrieda:
    writetext(FriedaGivesGiftText)
    promptbutton
    verbosegiveitem(POISON_BARB, 1)
    iffalse(Done)
    setevent(EVENT_GOT_POISON_BARB_FROM_FRIEDA)
    writetext(FriedaGaveGiftText)
    waitbutton
    closetext
    s_end
Friday:
    writetext(FriedaFridayText)
    waitbutton
Done:
    closetext
    s_end
NotFriday:
    writetext(FriedaNotFridayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall Route32GreatBall = {GREAT_BALL, 1};
const struct ItemBall Route32Repel = {REPEL, 1};
bool Route32Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route32SignText)
    SCRIPT_END
}
bool Route32RuinsSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route32RuinsSignText)
    SCRIPT_END
}
bool Route32UnionCaveSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route32UnionCaveSignText)
    SCRIPT_END
}
bool Route32PokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
const struct HiddenItem Route32HiddenGreatBall = {GREAT_BALL, EVENT_ROUTE_32_HIDDEN_GREAT_BALL};
const struct HiddenItem Route32HiddenSuperPotion = {SUPER_POTION, EVENT_ROUTE_32_HIDDEN_SUPER_POTION};
const uint8_t Movement_Route32CooltrainerMPushesYouBackToViolet[] = {
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t Movement_Route32CooltrainerMReset1[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t Movement_Route32CooltrainerMReset2[] = {
    step(RIGHT),
    movement_step_end,
};
const txt_cmd_s Route32CooltrainerMText_WhatsTheHurry[] = {
    text_start("Wait up!"
        t_line "What's the hurry?"
        t_done )
};
const txt_cmd_s Route32CooltrainerMText_AideIsWaiting[] = {
    text_start("<PLAYER>, right?"
        t_line "Some guy wearing"
        t_para "glasses was look-"
        t_line "ing for you."
        t_para "See for yourself."
        t_line "He's waiting for"
        t_para "you at the #MON"
        t_line "CENTER."
        t_done )
};
const txt_cmd_s Route32CooltrainerMText_UnusedSproutTower[] = {
    text_start("Have you gone to"
        t_line "SPROUT TOWER?"
        t_para "If you ever visit"
        t_line "VIOLET CITY, "
        t_para "they'll expect you"
        t_line "to train there."
        t_para "That's basic for"
        t_line "trainers. Go to"
        t_cont "SPROUT TOWER!"
        t_done )
};
const txt_cmd_s Route32CooltrainerMText_VioletGym[] = {
    text_start("Have you gone to"
        t_line "the #MON GYM?"
        t_para "You can test your"
        t_line "#MON and your-"
        t_cont "self there."
        t_para "It's a rite of"
        t_line "passage for all"
        t_cont "trainers!"
        t_done )
};
const txt_cmd_s Route32CooltrainerMText_HaveThisSeed[] = {
    text_start("You have some good"
        t_line "#MON there."
        t_para "It must be from"
        t_line "the training you"
        t_para "gave them around"
        t_line "VIOLET CITY."
        t_para "The training at"
        t_line "the GYM must have"
        t_para "been especially"
        t_line "helpful."
        t_para "As a souvenir of"
        t_line "VIOLET CITY, take"
        t_cont "this."
        t_para "It increases the"
        t_line "power of grass-"
        t_cont "type moves."
        t_done )
};
const txt_cmd_s Route32CooltrainerMText_ExperiencesShouldBeUseful[] = {
    text_start("Your experiences"
        t_line "in VIOLET CITY"
        t_para "should be useful"
        t_line "for your journey."
        t_done )
};
const txt_cmd_s Text_MillionDollarSlowpokeTail[] = {
    text_start("How would you like"
        t_line "to have this"
        t_para "tasty, nutritious"
        t_line "SLOWPOKETAIL?"
        t_para "For you right now,"
        t_line "just ¥1,000,000!"
        t_para "You'll want this!"
        t_done )
};
const txt_cmd_s Text_ThoughtKidsWereLoaded[] = {
    text_start("Tch! I thought"
        t_line "kids these days"
        t_cont "were loaded…"
        t_done )
};
const txt_cmd_s Text_RefusedToBuySlowpokeTail[] = {
    text_start("You don't want it?"
        t_line "Then scram. Shoo!"
        t_done )
};
const txt_cmd_s FisherJustinSeenText[] = {
    text_start("Whoa!"
        t_para "You made me lose"
        t_line "that fish!"
        t_done )
};
const txt_cmd_s FisherJustinBeatenText[] = {
    text_start("Sploosh!"
        t_done )
};
const txt_cmd_s FisherJustinAfterText[] = {
    text_start("Calm, collected…"
        t_line "The essence of"
        t_para "fishing and #-"
        t_line "MON is the same."
        t_done )
};
const txt_cmd_s FisherRalph1SeenText[] = {
    text_start("I'm really good at"
        t_line "both fishing and"
        t_cont "#MON."
        t_para "I'm not about to"
        t_line "lose to any kid!"
        t_done )
};
const txt_cmd_s FisherRalph1BeatenText[] = {
    text_start("Tch! I tried to"
        t_line "rush things…"
        t_done )
};
const txt_cmd_s FisherRalphAfterText[] = {
    text_start("Fishing is a life-"
        t_line "long passion."
        t_para "#MON are life-"
        t_line "long friends!"
        t_done )
};
const txt_cmd_s FisherRalphSwarmText[] = {
    text_start("One, two, three…"
        t_line "Muahahaha, what a"
        t_para "great haul!"
        t_line "I'm done! Go ahead"
        t_para "and catch as many"
        t_line "as you can, kid!"
        t_done )
};
const txt_cmd_s Route32UnusedFisher1SeenText[] = {
    text_start("I keep catching"
        t_line "the same #MON…"
        t_para "Maybe a battle"
        t_line "will turn things"
        t_cont "around for me."
        t_done )
};
const txt_cmd_s Route32UnusedFisher1BeatenText[] = {
    text_start("Nothing ever goes"
        t_line "right for me now…"
        t_done )
};
const txt_cmd_s Route32UnusedFisher1AfterText[] = {
    text_start("How come the guy"
        t_line "next to me catches"
        t_cont "good #MON?"
        t_done )
};
const txt_cmd_s Route32UnusedFisher2SeenText[] = {
    text_start("Heh, I'm on a roll"
        t_line "today. How about a"
        t_cont "battle, kid?"
        t_done )
};
const txt_cmd_s Route32UnusedFisher2BeatenText[] = {
    text_start("Oof. I wasn't"
        t_line "lucky that time."
        t_done )
};
const txt_cmd_s Route32UnusedFisher2AfterText[] = {
    text_start("You have to have a"
        t_line "good ROD if you"
        t_para "want to catch good"
        t_line "#MON."
        t_done )
};
const txt_cmd_s FisherHenrySeenText[] = {
    text_start("My #MON?"
        t_line "Freshly caught!"
        t_done )
};
const txt_cmd_s FisherHenryBeatenText[] = {
    text_start("SPLASH?"
        t_done )
};
const txt_cmd_s FisherHenryAfterText[] = {
    text_start("Freshly caught"
        t_line "#MON are no"
        t_para "match for properly"
        t_line "raised ones."
        t_done )
};
const txt_cmd_s YoungsterAlbertSeenText[] = {
    text_start("I haven't seen you"
        t_line "around before."
        t_para "So you think you"
        t_line "are pretty tough?"
        t_done )
};
const txt_cmd_s YoungsterAlbertBeatenText[] = {
    text_start("You're strong!"
        t_done )
};
const txt_cmd_s YoungsterAlbertAfterText[] = {
    text_start("I'm going to try"
        t_line "to be the best"
        t_cont "with my favorites."
        t_para "I'm not using the"
        t_line "same tough #MON"
        t_cont "as everyone else."
        t_done )
};
const txt_cmd_s YoungsterGordonSeenText[] = {
    text_start("I found some good"
        t_line "#MON in the"
        t_cont "grass!"
        t_para "I think they'll do"
        t_line "it for me!"
        t_done )
};
const txt_cmd_s YoungsterGordonBeatenText[] = {
    text_start("Darn. I thought I"
        t_line "could win."
        t_done )
};
const txt_cmd_s YoungsterGordonAfterText[] = {
    text_start("The grass is full"
        t_line "of clingy things."
        t_done )
};
const txt_cmd_s CamperRolandSeenText[] = {
    text_start("That glance…"
        t_line "It's intriguing."
        t_done )
};
const txt_cmd_s CamperRolandBeatenText[] = {
    text_start("Hmmm. This is"
        t_line "disappointing."
        t_done )
};
const txt_cmd_s CamperRolandAfterText[] = {
    text_start("If you don't want"
        t_line "to battle, just"
        t_cont "avoid eye contact."
        t_done )
};
const txt_cmd_s PicnickerLiz1SeenText[] = {
    text_start("Uh-huh. Yeah, and"
        t_line "you know…"
        t_para "Pardon? Battle?"
        t_line "I'm on the phone."
        t_para "Oh, all right. But"
        t_line "make it fast."
        t_done )
};
const txt_cmd_s PicnickerLiz1BeatenText[] = {
    text_start("Oh! I've got to"
        t_line "relieve my anger!"
        t_done )
};
const txt_cmd_s PicnickerLiz1AfterText[] = {
    text_start("I was having a"
        t_line "nice chat too."
        t_done )
};
const txt_cmd_s BirdKeeperPeterSeenText[] = {
    text_start("That BADGE! It's"
        t_line "from VIOLET CITY!"
        t_para "You beat FALKNER?"
        t_done )
};
const txt_cmd_s BirdKeeperPeterBeatenText[] = {
    text_start("I know what my"
        t_line "weaknesses are."
        t_done )
};
const txt_cmd_s BirdKeeperPeterAfterText[] = {
    text_start("I should train"
        t_line "again at the GYM"
        t_cont "in VIOLET CITY."
        t_done )
};
const txt_cmd_s Route32UnusedText[] = {
    text_start("The fishermen"
        t_line "yelled at me for"
        t_cont "bugging them…"
        t_done )
};
const txt_cmd_s Text_RoarIntro[] = {
    text_start("WROOOOAR!"
        t_line "PEOPLE RUN WHEN I"
        t_para "ROAR! BUT YOU"
        t_line "CAME LOOKING!"
        t_para "THAT PLEASES ME!"
        t_line "NOW TAKE THIS!"
        t_done )
};
const txt_cmd_s Text_RoarOutro[] = {
    text_start("WROOOAR!"
        t_line "IT'S ROAR!"
        t_para "EVEN #MON RUN"
        t_line "FROM A GOOD ROAR!"
        t_done )
};
const txt_cmd_s MeetFriedaText[] = {
    text_start("FRIEDA: Yahoo!"
        t_line "It's Friday!"
        t_para "I'm FRIEDA of"
        t_line "Friday!"
        t_para "Nice to meet you!"
        t_done )
};
const txt_cmd_s FriedaGivesGiftText[] = {
    text_start("Here's a POISON"
        t_line "BARB for you!"
        t_done )
};
const txt_cmd_s FriedaGaveGiftText[] = {
    text_start("FRIEDA: Give it to"
        t_line "a #MON that has"
        t_cont "poison-type moves."
        t_para "Oh!"
        t_para "It's wicked!"
        t_para "You'll be shocked"
        t_line "how good it makes"
        t_cont "poison moves!"
        t_done )
};
const txt_cmd_s FriedaFridayText[] = {
    text_start("FRIEDA: Hiya! What"
        t_line "day do you like?"
        t_para "I love Friday. No"
        t_line "doubt about it!"
        t_para "Don't you think"
        t_line "it's great too?"
        t_done )
};
const txt_cmd_s FriedaNotFridayText[] = {
    text_start("FRIEDA: Isn't it"
        t_line "Friday today?"
        t_para "It's so boring"
        t_line "when it's not!"
        t_done )
};
const txt_cmd_s Route32SignText[] = {
    text_start("ROUTE 32"
        t_para "VIOLET CITY -"
        t_line "AZALEA TOWN"
        t_done )
};
const txt_cmd_s Route32RuinsSignText[] = {
    text_start("RUINS OF ALPH"
        t_line "EAST ENTRANCE"
        t_done )
};
const txt_cmd_s Route32UnionCaveSignText[] = {
    text_start("UNION CAVE"
        t_line "AHEAD"
        t_done )
    //db(0, 0) // filler
};
