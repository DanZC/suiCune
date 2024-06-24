#include "../constants.h"
#include "../util/scripting.h"
#include "LakeOfRage.h"
//// EVENTS
enum {
    LAKEOFRAGE_LANCE = 2,
    LAKEOFRAGE_GRAMPS,
    LAKEOFRAGE_SUPER_NERD1,
    LAKEOFRAGE_COOLTRAINER_F1,
    LAKEOFRAGE_FISHER1,
    LAKEOFRAGE_FISHER2,
    LAKEOFRAGE_COOLTRAINER_M,
    LAKEOFRAGE_COOLTRAINER_F2,
    LAKEOFRAGE_GYARADOS,
    LAKEOFRAGE_WESLEY,
    LAKEOFRAGE_POKE_BALL1,
    LAKEOFRAGE_POKE_BALL2,
};

const Script_fn_t LakeOfRage_SceneScripts[] = {
    LakeOfRage_MapScripts_DummyScene0 , //  unusable,
    LakeOfRage_MapScripts_DummyScene1 , //  unusable,
};

const struct MapCallback LakeOfRage_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, LakeOfRage_MapScripts_FlyPoint),
    map_callback(MAPCALLBACK_OBJECTS, LakeOfRage_MapScripts_Wesley),
};

const struct MapScripts LakeOfRage_MapScripts = {
    .scene_script_count = lengthof(LakeOfRage_SceneScripts),
    .scene_scripts = LakeOfRage_SceneScripts,

    .callback_count = lengthof(LakeOfRage_MapCallbacks),
    .callbacks = LakeOfRage_MapCallbacks,
};

static const struct CoordEvent LakeOfRage_CoordEvents[] = {
    0,
};

static const struct BGEvent LakeOfRage_BGEvents[] = {
    bg_event(21, 27, BGEVENT_READ, &LakeOfRageSign),
    bg_event(25, 31, BGEVENT_READ, &MagikarpHouseSignScript),
    bg_event(11, 28, BGEVENT_ITEM, &LakeOfRageHiddenFullRestore),
    bg_event(4, 4, BGEVENT_ITEM, &LakeOfRageHiddenRareCandy),
    bg_event(35, 5, BGEVENT_ITEM, &LakeOfRageHiddenMaxPotion),
};

static const struct WarpEventData LakeOfRage_WarpEvents[] = {
    warp_event(7, 3, LAKE_OF_RAGE_HIDDEN_POWER_HOUSE, 1),
    warp_event(27, 31, LAKE_OF_RAGE_MAGIKARP_HOUSE, 1),
};

static const struct ObjEvent LakeOfRage_ObjectEvents[] = {
    object_event(21, 28, SPRITE_LANCE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LakeOfRageLanceScript, EVENT_LAKE_OF_RAGE_LANCE),
    object_event(20, 26, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LakeOfRageGrampsScript, -1),
    object_event(36, 13, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LakeOfRageSuperNerdScript, -1),
    object_event(25, 29, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LakeOfRageCooltrainerFScript, -1),
    object_event(30, 23, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerFisherAndre, EVENT_LAKE_OF_RAGE_CIVILIANS),
    object_event(24, 26, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerFisherRaymond, EVENT_LAKE_OF_RAGE_CIVILIANS),
    object_event(4, 15, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerCooltrainermAaron, EVENT_LAKE_OF_RAGE_CIVILIANS),
    object_event(36, 7, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 0, &TrainerCooltrainerfLois, EVENT_LAKE_OF_RAGE_CIVILIANS),
    object_event(18, 22, SPRITE_GYARADOS, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RedGyarados, EVENT_LAKE_OF_RAGE_RED_GYARADOS),
    object_event(4, 4, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &WesleyScript, EVENT_LAKE_OF_RAGE_WESLEY_OF_WEDNESDAY),
    object_event(7, 10, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &LakeOfRageElixer, EVENT_LAKE_OF_RAGE_ELIXER),
    object_event(35, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &LakeOfRageTMDetect, EVENT_LAKE_OF_RAGE_TM_DETECT),
};

const struct MapEvents LakeOfRage_MapEvents = {
    .warp_event_count = lengthof(LakeOfRage_WarpEvents),
    .warp_events = LakeOfRage_WarpEvents,

    .coord_event_count = 0, // lengthof(LakeOfRage_CoordEvents),
    .coord_events = LakeOfRage_CoordEvents,

    .bg_event_count = lengthof(LakeOfRage_BGEvents),
    .bg_events = LakeOfRage_BGEvents,

    .obj_event_count = lengthof(LakeOfRage_ObjectEvents),
    .obj_events = LakeOfRage_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "LakeOfRage.h"

bool LakeOfRage_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool LakeOfRage_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool LakeOfRage_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_LAKE_OF_RAGE)
    s_endcallback
    SCRIPT_END
}
bool LakeOfRage_MapScripts_Wesley(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal(WEDNESDAY, WesleyAppears)
    disappear(LAKEOFRAGE_WESLEY)
    s_endcallback
WesleyAppears:
    appear(LAKEOFRAGE_WESLEY)
    s_endcallback
    SCRIPT_END
}
bool LakeOfRageLanceScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_REFUSED_TO_HELP_LANCE_AT_LAKE_OF_RAGE)
    iftrue(AskAgainForHelp)
    opentext
    writetext(LakeOfRageLanceForcedToEvolveText)
    promptbutton
    faceplayer
    writetext(LakeOfRageLanceIntroText)
    yesorno
    iffalse(RefusedToHelp)
AgreedToHelp:
    writetext(LakeOfRageLanceRadioSignalText)
    waitbutton
    closetext
    playsound(SFX_WARP_TO)
    applymovement(LAKEOFRAGE_LANCE, LakeOfRageLanceTeleportIntoSkyMovement)
    disappear(LAKEOFRAGE_LANCE)
    clearevent(EVENT_MAHOGANY_MART_LANCE_AND_DRAGONITE)
    setevent(EVENT_DECIDED_TO_HELP_LANCE)
    setmapscene(MAHOGANY_MART_1F, SCENE_MAHOGANYMART1F_LANCE_UNCOVERS_STAIRS)
    s_end
RefusedToHelp:
    writetext(LakeOfRageLanceRefusedText)
    waitbutton
    closetext
    setevent(EVENT_REFUSED_TO_HELP_LANCE_AT_LAKE_OF_RAGE)
    s_end
AskAgainForHelp:
    faceplayer
    opentext
    writetext(LakeOfRageLanceAskHelpText)
    yesorno
    iffalse(RefusedToHelp)
    goto AgreedToHelp;
    SCRIPT_END
}
bool RedGyarados(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(LakeOfRageGyaradosCryText)
    pause(15)
    playcry(GYARADOS)
    closetext
    loadwildmon(GYARADOS, 30)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_SHINY)
    startbattle
    ifequal(LOSE, NotBeaten)
    disappear(LAKEOFRAGE_GYARADOS)
NotBeaten:
    reloadmapafterbattle
    opentext
    giveitem(RED_SCALE, 1)
    waitsfx
    writetext(LakeOfRageGotRedScaleText)
    playsound(SFX_ITEM)
    waitsfx
    itemnotify
    closetext
    setscene(0) // Lake of Rage does not have a scene variable
    appear(LAKEOFRAGE_LANCE)
    s_end
    SCRIPT_END
}
bool LakeOfRageGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(ClearedRocketHideout)
    writetext(LakeOfRageGrampsText)
    waitbutton
    closetext
    s_end
ClearedRocketHideout:
    writetext(LakeOfRageGrampsText_ClearedRocketHideout)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LakeOfRageSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LakeOfRageSuperNerdText)
    SCRIPT_END
}
bool LakeOfRageCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LakeOfRageCooltrainerFText)
    SCRIPT_END
}
bool LakeOfRageSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(LakeOfRageSignText)
    SCRIPT_END
}
bool MagikarpHouseSignScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(FishingGurusHouseSignText)
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(MagikarpLengthRecord)
    waitbutton
    closetext
    s_end
MagikarpLengthRecord:
    promptbutton
    special(MagikarpHouseSign)
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherAndre = {FISHER, ANDRE, EVENT_BEAT_FISHER_ANDRE, FisherAndreSeenText, FisherAndreBeatenText, 0, TrainerFisherAndre_Script};
bool TrainerFisherAndre_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherAndreAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherRaymond = {FISHER, RAYMOND, EVENT_BEAT_FISHER_RAYMOND, FisherRaymondSeenText, FisherRaymondBeatenText, 0, TrainerFisherRaymond_Script};
bool TrainerFisherRaymond_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherRaymondAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainermAaron = {COOLTRAINERM, AARON, EVENT_BEAT_COOLTRAINERM_AARON, CooltrainermAaronSeenText, CooltrainermAaronBeatenText, 0, TrainerCooltrainermAaron_Script};
bool TrainerCooltrainermAaron_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainermAaronAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfLois = {COOLTRAINERF, LOIS, EVENT_BEAT_COOLTRAINERF_LOIS, CooltrainerfLoisSeenText, CooltrainerfLoisBeatenText, 0, TrainerCooltrainerfLois_Script};
bool TrainerCooltrainerfLois_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CooltrainerfLoisAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool WesleyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_BLACKBELT_FROM_WESLEY)
    iftrue_jump(WesleyWednesdayScript)
    readvar(VAR_WEEKDAY)
    ifnotequal_jump(WEDNESDAY, WesleyNotWednesdayScript)
    checkevent(EVENT_MET_WESLEY_OF_WEDNESDAY)
    iftrue(MetWesley)
    writetext(MeetWesleyText)
    promptbutton
    setevent(EVENT_MET_WESLEY_OF_WEDNESDAY)
MetWesley:
    writetext(WesleyGivesGiftText)
    promptbutton
    verbosegiveitem(BLACKBELT_I, 1)
    iffalse_jump(WesleyDoneScript)
    setevent(EVENT_GOT_BLACKBELT_FROM_WESLEY)
    writetext(WesleyGaveGiftText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool WesleyWednesdayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(WesleyWednesdayText)
    waitbutton
    SCRIPT_FALLTHROUGH(WesleyDoneScript)
}
bool WesleyDoneScript(script_s* s) {
    SCRIPT_BEGIN
    closetext
    s_end
    SCRIPT_END
}
bool WesleyNotWednesdayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(WesleyNotWednesdayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall LakeOfRageElixer = {ELIXER, 1};
const struct ItemBall LakeOfRageTMDetect = {TM_DETECT, 1};
const struct HiddenItem LakeOfRageHiddenFullRestore = {FULL_RESTORE, EVENT_LAKE_OF_RAGE_HIDDEN_FULL_RESTORE};
const struct HiddenItem LakeOfRageHiddenRareCandy = {RARE_CANDY, EVENT_LAKE_OF_RAGE_HIDDEN_RARE_CANDY};
const struct HiddenItem LakeOfRageHiddenMaxPotion = {MAX_POTION, EVENT_LAKE_OF_RAGE_HIDDEN_MAX_POTION};
const uint8_t LakeOfRageLanceTeleportIntoSkyMovement[] = {
    movement_teleport_from,
    movement_step_end,
};
const txt_cmd_s LakeOfRageLanceForcedToEvolveText[] = {
    text_start("This lake is full"
        t_line "of GYARADOS but"
        t_cont "nothing else…"
        t_para "So the MAGIKARP"
        t_line "are being forced"
        t_cont "to evolve…"
        t_done )
};
const txt_cmd_s LakeOfRageLanceIntroText[] = {
    text_start("Did you come here"
        t_line "because of the"
        t_cont "rumors?"
        t_para "You're <PLAYER>?"
        t_line "I'm LANCE, a"
        t_cont "trainer like you."
        t_para "I heard some ru-"
        t_line "mors, so I came to"
        t_cont "investigate…"
        t_para "I saw the way you"
        t_line "battled earlier,"
        t_cont "<PLAY_G>."
        t_para "I can tell that"
        t_line "you're a trainer"
        t_para "with considerable"
        t_line "skill."
        t_para "If you don't mind,"
        t_line "could you help me"
        t_cont "investigate?"
        t_done )
};
const txt_cmd_s LakeOfRageLanceRadioSignalText[] = {
    text_start("LANCE: Excellent!"
        t_para "It seems that the"
        t_line "LAKE's MAGIKARP"
        t_para "are being forced"
        t_line "to evolve."
        t_para "A mysterious radio"
        t_line "broadcast coming"
        t_para "from MAHOGANY is"
        t_line "the cause."
        t_para "I'll be waiting"
        t_line "for you, <PLAY_G>."
        t_done )
};
const txt_cmd_s LakeOfRageLanceRefusedText[] = {
    text_start("Oh… Well, if you"
        t_line "change your mind,"
        t_cont "please help me."
        t_done )
};
const txt_cmd_s LakeOfRageLanceAskHelpText[] = {
    text_start("LANCE: Hm? Are you"
        t_line "going to help me?"
        t_done )
};
const txt_cmd_s LakeOfRageGyaradosCryText[] = {
    text_start("GYARADOS: Gyashaa!"
        t_done )
};
const txt_cmd_s LakeOfRageGotRedScaleText[] = {
    text_start("<PLAYER> obtained a"
        t_line "RED SCALE."
        t_done )
};
const txt_cmd_s LakeOfRageGrampsText[] = {
    text_start("The GYARADOS are"
        t_line "angry!"
        t_para "It's a bad omen!"
        t_done )
};
const txt_cmd_s LakeOfRageGrampsText_ClearedRocketHideout[] = {
    text_start("Hahah! The MAGI-"
        t_line "KARP are biting!"
        t_done )
};
const txt_cmd_s LakeOfRageSuperNerdText[] = {
    text_start("I heard this lake"
        t_line "was made by ram-"
        t_cont "paging GYARADOS."
        t_para "I wonder if there"
        t_line "is any connection"
        t_para "to their mass out-"
        t_line "break now?"
        t_done )
};
const txt_cmd_s LakeOfRageCooltrainerFText[] = {
    text_start("Did my eyes de-"
        t_line "ceive me? I saw a"
        t_para "red GYARADOS in"
        t_line "the LAKE…"
        t_para "But I thought"
        t_line "GYARADOS were"
        t_cont "usually blue?"
        t_done )
};
const txt_cmd_s FisherAndreSeenText[] = {
    text_start("Let me battle with"
        t_line "the #MON I just"
        t_cont "caught!"
        t_done )
};
const txt_cmd_s FisherAndreBeatenText[] = {
    text_start("I might be an ex-"
        t_line "pert angler, but"
        t_para "I stink as a #-"
        t_line "MON trainer…"
        t_done )
};
const txt_cmd_s FisherAndreAfterBattleText[] = {
    text_start("I won't lose as an"
        t_line "angler! I catch"
        t_cont "#MON all day."
        t_done )
};
const txt_cmd_s FisherRaymondSeenText[] = {
    text_start("No matter what I"
        t_line "do, all I catch"
        t_para "are the same #-"
        t_line "MON…"
        t_done )
};
const txt_cmd_s FisherRaymondBeatenText[] = {
    text_start("My line's all"
        t_line "tangled up…"
        t_done )
};
const txt_cmd_s FisherRaymondAfterBattleText[] = {
    text_start("Why can't I catch"
        t_line "any good #MON?"
        t_done )
};
const txt_cmd_s CooltrainermAaronSeenText[] = {
    text_start("If a trainer spots"
        t_line "another trainer,"
        t_para "he has to make a"
        t_line "challenge."
        t_para "That is our"
        t_line "destiny."
        t_done )
};
const txt_cmd_s CooltrainermAaronBeatenText[] = {
    text_start("Whew…"
        t_line "Good battle."
        t_done )
};
const txt_cmd_s CooltrainermAaronAfterBattleText[] = {
    text_start("#MON and their"
        t_line "trainer become"
        t_para "powerful through"
        t_line "constant battling."
        t_done )
};
const txt_cmd_s CooltrainerfLoisSeenText[] = {
    text_start("What happened to"
        t_line "the red GYARADOS?"
        t_para "It's gone?"
        t_para "Oh, darn. I came"
        t_line "here for nothing?"
        t_para "I know--let's"
        t_line "battle!"
        t_done )
};
const txt_cmd_s CooltrainerfLoisBeatenText[] = {
    text_start("Good going!"
        t_done )
};
const txt_cmd_s CooltrainerfLoisAfterBattleText[] = {
    text_start("Come to think of"
        t_line "it, I've seen a"
        t_cont "pink BUTTERFREE."
        t_done )
};
const txt_cmd_s MeetWesleyText[] = {
    text_start("WESLEY: Well, how"
        t_line "do you do?"
        t_para "Seeing as how it's"
        t_line "Wednesday today,"
        t_para "I'm WESLEY of"
        t_line "Wednesday."
        t_done )
};
const txt_cmd_s WesleyGivesGiftText[] = {
    text_start("Pleased to meet"
        t_line "you. Please take a"
        t_cont "souvenir."
        t_done )
};
const txt_cmd_s WesleyGaveGiftText[] = {
    text_start("WESLEY: BLACKBELT"
        t_line "beefs up the power"
        t_cont "of fighting moves."
        t_done )
};
const txt_cmd_s WesleyWednesdayText[] = {
    text_start("WESLEY: Since you"
        t_line "found me, you must"
        t_para "have met my broth-"
        t_line "ers and sisters."
        t_para "Or did you just"
        t_line "get lucky?"
        t_done )
};
const txt_cmd_s WesleyNotWednesdayText[] = {
    text_start("WESLEY: Today's"
        t_line "not Wednesday."
        t_cont "That's too bad."
        t_done )
};
const txt_cmd_s LakeOfRageSignText[] = {
    text_start("LAKE OF RAGE,"
        t_line "also known as"
        t_cont "GYARADOS LAKE."
        t_done )
};
const txt_cmd_s FishingGurusHouseSignText[] = {
    text_start("FISHING GURU'S"
        t_line "HOUSE"
        t_done )
    //db(0, 0) // filler
};
