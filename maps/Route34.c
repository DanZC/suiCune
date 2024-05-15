#include "../constants.h"
#include "../util/scripting.h"
#include "Route34.h"
//// EVENTS
enum {
    ROUTE34_YOUNGSTER1 = 2,
    ROUTE34_YOUNGSTER2,
    ROUTE34_YOUNGSTER3,
    ROUTE34_LASS,
    ROUTE34_OFFICER,
    ROUTE34_POKEFAN_M,
    ROUTE34_GRAMPS,
    ROUTE34_DAY_CARE_MON_1,
    ROUTE34_DAY_CARE_MON_2,
    ROUTE34_COOLTRAINER_F1,
    ROUTE34_COOLTRAINER_F2,
    ROUTE34_COOLTRAINER_F3,
    ROUTE34_POKE_BALL,
};

const Script_fn_t Route34_SceneScripts[] = {
    0,
};

const struct MapCallback Route34_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Route34_MapScripts_EggCheckCallback),
};

const struct MapScripts Route34_MapScripts = {
    .scene_script_count = 0, // lengthof(Route34_SceneScripts),
    .scene_scripts = Route34_SceneScripts,

    .callback_count = lengthof(Route34_MapCallbacks),
    .callbacks = Route34_MapCallbacks,
};

static const struct CoordEvent Route34_CoordEvents[] = {
    0,
};

static const struct BGEvent Route34_BGEvents[] = {
    bg_event(12, 6, BGEVENT_READ, &Route34Sign),
    bg_event(13, 33, BGEVENT_READ, &Route34TrainerTips),
    bg_event(10, 13, BGEVENT_READ, &DayCareSign),
    bg_event(8, 32, BGEVENT_ITEM, &Route34HiddenRareCandy),
    bg_event(17, 19, BGEVENT_ITEM, &Route34HiddenSuperPotion),
};

static const struct WarpEventData Route34_WarpEvents[] = {
    warp_event(13, 37, ROUTE_34_ILEX_FOREST_GATE, 1),
    warp_event(14, 37, ROUTE_34_ILEX_FOREST_GATE, 2),
    warp_event(11, 14, DAY_CARE, 1),
    warp_event(11, 15, DAY_CARE, 2),
    warp_event(13, 15, DAY_CARE, 3),
};

static const struct ObjEvent Route34_ObjectEvents[] = {
    object_event(13, 7, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 5, &TrainerCamperTodd1, -1),
    object_event(15, 32, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerYoungsterSamuel, -1),
    object_event(11, 20, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerYoungsterIan, -1),
    object_event(10, 26, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerPicnickerGina1, -1),
    object_event(9, 11, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &OfficerKeithScript, -1),
    object_event(18, 28, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerPokefanmBrandon, -1),
    object_event(15, 16, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DayCareManScript_Outside, EVENT_DAY_CARE_MAN_ON_ROUTE_34),
    object_event(14, 18, SPRITE_DAY_CARE_MON_1, SPRITEMOVEDATA_POKEMON, 2, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DayCareMon1Script, EVENT_DAY_CARE_MON_1),
    object_event(17, 19, SPRITE_DAY_CARE_MON_2, SPRITEMOVEDATA_POKEMON, 2, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DayCareMon2Script, EVENT_DAY_CARE_MON_2),
    object_event(11, 48, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 5, &TrainerCooltrainerfIrene, -1),
    object_event(3, 48, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 3, &TrainerCooltrainerfJenn, -1),
    object_event(6, 51, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 2, &TrainerCooltrainerfKate, -1),
    object_event(7, 30, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route34Nugget, EVENT_ROUTE_34_NUGGET),
};

const struct MapEvents Route34_MapEvents = {
    .warp_event_count = lengthof(Route34_WarpEvents),
    .warp_events = Route34_WarpEvents,

    .coord_event_count = 0, // lengthof(Route34_CoordEvents),
    .coord_events = Route34_CoordEvents,

    .bg_event_count = lengthof(Route34_BGEvents),
    .bg_events = Route34_BGEvents,

    .obj_event_count = lengthof(Route34_ObjectEvents),
    .obj_events = Route34_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route34.h"

bool Route34_MapScripts_EggCheckCallback(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_DAY_CARE_MAN_HAS_EGG)
    iftrue_jump(Route34_MapScripts_PutDayCareManOutside)
    clearevent(EVENT_DAY_CARE_MAN_IN_DAY_CARE)
    setevent(EVENT_DAY_CARE_MAN_ON_ROUTE_34)
    sjump(Route34_MapScripts_CheckMon1)
    SCRIPT_END
}
bool Route34_MapScripts_PutDayCareManOutside(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_DAY_CARE_MAN_IN_DAY_CARE)
    clearevent(EVENT_DAY_CARE_MAN_ON_ROUTE_34)
    sjump(Route34_MapScripts_CheckMon1)
    SCRIPT_END
}
bool Route34_MapScripts_CheckMon1(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_DAY_CARE_MAN_HAS_MON)
    iffalse_jump(Route34_MapScripts_HideMon1)
    clearevent(EVENT_DAY_CARE_MON_1)
    sjump(Route34_MapScripts_CheckMon2)
    SCRIPT_END
}
bool Route34_MapScripts_HideMon1(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_DAY_CARE_MON_1)
    sjump(Route34_MapScripts_CheckMon2)
    SCRIPT_END
}
bool Route34_MapScripts_CheckMon2(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_DAY_CARE_LADY_HAS_MON)
    iffalse_jump(Route34_MapScripts_HideMon2)
    clearevent(EVENT_DAY_CARE_MON_2)
    s_endcallback
    SCRIPT_END
}
bool Route34_MapScripts_HideMon2(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_DAY_CARE_MON_2)
    s_endcallback
    SCRIPT_END
}
bool DayCareManScript_Outside(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    special(DayCareManOutside)
    waitbutton
    closetext
    ifequal(TRUE, end_fail)
    clearflag(ENGINE_DAY_CARE_MAN_HAS_EGG)
    readvar(VAR_FACING)
    ifequal(RIGHT, walk_around_player)
    applymovement(ROUTE34_GRAMPS, Route34MovementData_DayCareManWalksBackInside)
    playsound(SFX_ENTER_DOOR)
    disappear(ROUTE34_GRAMPS)
end_fail:
    s_end
walk_around_player:
    applymovement(ROUTE34_GRAMPS, Route34MovementData_DayCareManWalksBackInside_WalkAroundPlayer)
    playsound(SFX_ENTER_DOOR)
    disappear(ROUTE34_GRAMPS)
    s_end
    SCRIPT_END
}
bool DayCareMon1Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    special(DayCareMon1)
    closetext
    s_end
    SCRIPT_END
}
bool DayCareMon2Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    special(DayCareMon2)
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCamperTodd1 = {CAMPER, TODD1, EVENT_BEAT_CAMPER_TODD, CamperTodd1SeenText, CamperTodd1BeatenText, 0, TrainerCamperTodd1_Script};
bool TrainerCamperTodd1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_CAMPER_TODD)
    endifjustbattled
    opentext
    checkflag(ENGINE_TODD_READY_FOR_REMATCH)
    iftrue(Rematch)
    checkflag(ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON)
    iftrue(SaleIsOn)
    checkcellnum(PHONE_CAMPER_TODD)
    iftrue(NumberAccepted)
    checkevent(EVENT_TODD_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(CamperTodd1AfterText)
    promptbutton
    setevent(EVENT_TODD_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber);
    goto FinishAsk;
AskAgain:
    scall_local(AskNumber2);
FinishAsk:
    askforphonenumber(PHONE_CAMPER_TODD)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, CAMPER, TODD1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
Rematch:
    scall_local(RematchStd);
    winlosstext(CamperTodd1BeatenText, 0)
    readmem(wram_ptr(wToddFightCount))
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
    checkflag(ENGINE_FLYPOINT_CIANWOOD)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(CAMPER, TODD1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wToddFightCount), 1)
    clearflag(ENGINE_TODD_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(CAMPER, TODD2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wToddFightCount), 2)
    clearflag(ENGINE_TODD_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(CAMPER, TODD3)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wToddFightCount), 3)
    clearflag(ENGINE_TODD_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(CAMPER, TODD4)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wToddFightCount), 4)
    clearflag(ENGINE_TODD_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(CAMPER, TODD5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_TODD_READY_FOR_REMATCH)
    s_end
SaleIsOn:
    writetext(CamperToddSaleText)
    waitbutton
    closetext
    s_end
AskNumber:
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
const struct TrainerObj TrainerPicnickerGina1 = {PICNICKER, GINA1, EVENT_BEAT_PICNICKER_GINA, PicnickerGina1SeenText, PicnickerGina1BeatenText, 0, TrainerPicnickerGina1_Script};
bool TrainerPicnickerGina1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_PICNICKER_GINA)
    endifjustbattled
    opentext
    checkflag(ENGINE_GINA_READY_FOR_REMATCH)
    iftrue(Rematch)
    checkflag(ENGINE_GINA_HAS_LEAF_STONE)
    iftrue(LeafStone)
    checkcellnum(PHONE_PICNICKER_GINA)
    iftrue(NumberAccepted)
    checkevent(EVENT_GINA_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(PicnickerGina1AfterText)
    promptbutton
    setevent(EVENT_GINA_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto FinishAsk;
AskAgain:
    scall_local(AskNumber2);
FinishAsk:
    askforphonenumber(PHONE_PICNICKER_GINA)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, PICNICKER, GINA1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
Rematch:
    scall_local(RematchStd);
    winlosstext(PicnickerGina1BeatenText, 0)
    readmem(wram_ptr(wGinaFightCount))
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
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_MAHOGANY)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(PICNICKER, GINA1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wGinaFightCount), 1)
    clearflag(ENGINE_GINA_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(PICNICKER, GINA2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wGinaFightCount), 2)
    clearflag(ENGINE_GINA_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(PICNICKER, GINA3)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wGinaFightCount), 3)
    clearflag(ENGINE_GINA_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(PICNICKER, GINA4)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wGinaFightCount), 4)
    clearflag(ENGINE_GINA_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(PICNICKER, GINA5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_GINA_READY_FOR_REMATCH)
    s_end
LeafStone:
    scall_local(Gift);
    verbosegiveitem(LEAF_STONE, 1)
    iffalse(BagFull)
    clearflag(ENGINE_GINA_HAS_LEAF_STONE)
    setevent(EVENT_GINA_GAVE_LEAF_STONE)
    goto NumberAccepted;
BagFull:
    goto PackFull;
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
Gift:
    jumpstd(GiftFScript)
    s_end
PackFull:
    jumpstd(PackFullFScript)
    s_end
    SCRIPT_END
}
bool OfficerKeithScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checktime(NITE)
    iffalse(NoFight)
    checkevent(EVENT_BEAT_OFFICER_KEITH)
    iftrue(AfterScript)
    playmusic(MUSIC_OFFICER_ENCOUNTER)
    writetext(OfficerKeithSeenText)
    waitbutton
    closetext
    winlosstext(OfficerKeithWinText, 0)
    loadtrainer(OFFICER, KEITH)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_OFFICER_KEITH)
    closetext
    s_end
AfterScript:
    writetext(OfficerKeithAfterText)
    waitbutton
    closetext
    s_end
NoFight:
    writetext(OfficerKeithDaytimeText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterSamuel = {YOUNGSTER, SAMUEL, EVENT_BEAT_YOUNGSTER_SAMUEL, YoungsterSamuelSeenText, YoungsterSamuelBeatenText, 0, TrainerYoungsterSamuel_Script};
bool TrainerYoungsterSamuel_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterSamuelAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerYoungsterIan = {YOUNGSTER, IAN, EVENT_BEAT_YOUNGSTER_IAN, YoungsterIanSeenText, YoungsterIanBeatenText, 0, TrainerYoungsterIan_Script};
bool TrainerYoungsterIan_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(YoungsterIanAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmBrandon = {POKEFANM, BRANDON, EVENT_BEAT_POKEFANM_BRANDON, PokefanmBrandonSeenText, PokefanmBrandonBeatenText, 0, TrainerPokefanmBrandon_Script};
bool TrainerPokefanmBrandon_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanmBrandonAfterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfIrene = {COOLTRAINERF, IRENE, EVENT_BEAT_COOLTRAINERF_IRENE, CooltrainerfIreneSeenText, CooltrainerfIreneBeatenText, 0, TrainerCooltrainerfIrene_Script};
bool TrainerCooltrainerfIrene_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    checkevent(EVENT_GOT_SOFT_SAND_FROM_KATE)
    iftrue(GotSoftSand)
    writetext(CooltrainerfIreneAfterText1)
    waitbutton
    closetext
    s_end
GotSoftSand:
    writetext(CooltrainerfIreneAfterText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfJenn = {COOLTRAINERF, JENN, EVENT_BEAT_COOLTRAINERF_JENN, CooltrainerfJennSeenText, CooltrainerfJennBeatenText, 0, TrainerCooltrainerfJenn_Script};
bool TrainerCooltrainerfJenn_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    checkevent(EVENT_GOT_SOFT_SAND_FROM_KATE)
    iftrue(GotSoftSand)
    writetext(CooltrainerfJennAfterText1)
    waitbutton
    closetext
    s_end
GotSoftSand:
    writetext(CooltrainerfJennAfterText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCooltrainerfKate = {COOLTRAINERF, KATE, EVENT_BEAT_COOLTRAINERF_KATE, CooltrainerfKateSeenText, CooltrainerfKateBeatenText, 0, TrainerCooltrainerfKate_Script};
bool TrainerCooltrainerfKate_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    checkevent(EVENT_GOT_SOFT_SAND_FROM_KATE)
    iftrue(GotSoftSand)
    writetext(CooltrainerfKateOfferSoftSandText)
    promptbutton
    verbosegiveitem(SOFT_SAND, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_SOFT_SAND_FROM_KATE)
GotSoftSand:
    writetext(CooltrainerfKateAfterText)
    waitbutton
BagFull:
    closetext
    s_end
    SCRIPT_END
}
bool Route34IlexForestSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route34IlexForestSignText)
    SCRIPT_END
}
bool Route34Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route34SignText)
    SCRIPT_END
}
bool Route34TrainerTips(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route34TrainerTipsText)
    SCRIPT_END
}
bool DayCareSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(DayCareSignText)
    SCRIPT_END
}
const struct ItemBall Route34Nugget = {NUGGET, 1};
const struct HiddenItem Route34HiddenRareCandy = {RARE_CANDY, EVENT_ROUTE_34_HIDDEN_RARE_CANDY};
const struct HiddenItem Route34HiddenSuperPotion = {SUPER_POTION, EVENT_ROUTE_34_HIDDEN_SUPER_POTION};
const uint8_t Route34MovementData_DayCareManWalksBackInside[] = {
    slow_step(LEFT),
    slow_step(LEFT),
    slow_step(UP),
    movement_step_end,
};
const uint8_t Route34MovementData_DayCareManWalksBackInside_WalkAroundPlayer[] = {
    slow_step(DOWN),
    slow_step(LEFT),
    slow_step(LEFT),
    slow_step(UP),
    slow_step(UP),
    movement_step_end,
};
const txt_cmd_s YoungsterSamuelSeenText[] = {
    text_start("This is where I do"
        t_line "my training!"
        t_done )
};
const txt_cmd_s YoungsterSamuelBeatenText[] = {
    text_start("Beaten by a"
        t_line "passing stranger!"
        t_done )
};
const txt_cmd_s YoungsterSamuelMobileText[] = {
    text_start("Have you been to"
        t_line "GOLDENROD CITY?"
        t_para "Weren't you amazed"
        t_line "by how they've"
        t_para "changed the"
        t_line "#MON CENTER?"
        t_done )
};
const txt_cmd_s YoungsterSamuelAfterText[] = {
    text_start("I'm going to train"
        t_line "even harder."
        t_para "After all, I'm"
        t_line "trying to become"
        t_cont "a GYM LEADER."
        t_done )
};
const txt_cmd_s YoungsterIanSeenText[] = {
    text_start("I'm the best in my"
        t_line "class at #MON."
        t_done )
};
const txt_cmd_s YoungsterIanBeatenText[] = {
    text_start("No! There are bet-"
        t_line "ter trainers…"
        t_done )
};
const txt_cmd_s YoungsterIanAfterText[] = {
    text_start("I'm trying hard so"
        t_line "I can be the star"
        t_cont "in my class."
        t_done )
};
const txt_cmd_s CamperTodd1SeenText[] = {
    text_start("I'm confident in"
        t_line "my ability to"
        t_cont "raise #MON."
        t_para "Want to see?"
        t_done )
};
const txt_cmd_s CamperTodd1BeatenText[] = {
    text_start("Did I screw up my"
        t_line "training?"
        t_done )
};
const txt_cmd_s CamperTodd1AfterText[] = {
    text_start("Maybe I should"
        t_line "take one to a DAY-"
        t_para "CARE. Or maybe use"
        t_line "some items…"
        t_done )
};
const txt_cmd_s CamperToddSaleText[] = {
    text_start("Shopping under the"
        t_line "sky!"
        t_para "It feels so nice"
        t_line "up on a rooftop."
        t_done )
};
const txt_cmd_s PicnickerGina1SeenText[] = {
    text_start("Are you a trainer?"
        t_para "Let's have a"
        t_line "practice battle."
        t_done )
};
const txt_cmd_s PicnickerGina1BeatenText[] = {
    text_start("Oh, no! I just"
        t_line "can't win…"
        t_done )
};
const txt_cmd_s PicnickerGina1AfterText[] = {
    text_start("You're too strong"
        t_line "to be a practice"
        t_cont "partner."
        t_done )
};
const txt_cmd_s OfficerKeithSeenText[] = {
    text_start("Who goes there?"
        t_line "What are you up"
        t_cont "to?"
        t_done )
};
const txt_cmd_s OfficerKeithWinText[] = {
    text_start("You're a tough"
        t_line "little kid."
        t_done )
};
const txt_cmd_s OfficerKeithAfterText[] = {
    text_start("Yep, I see nothing"
        t_line "wrong today. You"
        t_para "be good and stay"
        t_line "out of trouble."
        t_done )
};
const txt_cmd_s OfficerKeithDaytimeText[] = {
    text_start("I'm on patrol for"
        t_line "suspicious indi-"
        t_cont "viduals."
        t_done )
};
const txt_cmd_s PokefanmBrandonSeenText[] = {
    text_start("I just got my"
        t_line "#MON back from"
        t_cont "DAY-CARE."
        t_para "Let's see how much"
        t_line "stronger it got!"
        t_done )
};
const txt_cmd_s PokefanmBrandonBeatenText[] = {
    text_start("Why does it end"
        t_line "this way?"
        t_done )
};
const txt_cmd_s PokefanmBrandonAfterText[] = {
    text_start("My #MON knew"
        t_line "moves I didn't"
        t_cont "know it had."
        t_para "That confounded me"
        t_line "to no end!"
        t_done )
};
const txt_cmd_s CooltrainerfIreneSeenText[] = {
    text_start("IRENE: Kyaaah!"
        t_line "Someone found us!"
        t_done )
};
const txt_cmd_s CooltrainerfIreneBeatenText[] = {
    text_start("IRENE: Ohhh!"
        t_line "Too strong!"
        t_done )
};
const txt_cmd_s CooltrainerfIreneAfterText1[] = {
    text_start("IRENE: My sister"
        t_line "KATE will get you"
        t_cont "for this!"
        t_done )
};
const txt_cmd_s CooltrainerfIreneAfterText2[] = {
    text_start("IRENE: Isn't this"
        t_line "beach great?"
        t_para "It's our secret"
        t_line "little getaway!"
        t_done )
};
const txt_cmd_s CooltrainerfJennSeenText[] = {
    text_start("JENN: You can't"
        t_line "beat IRENE and go"
        t_cont "unpunished!"
        t_done )
};
const txt_cmd_s CooltrainerfJennBeatenText[] = {
    text_start("JENN: So sorry,"
        t_line "IRENE! Sis!"
        t_done )
};
const txt_cmd_s CooltrainerfJennAfterText1[] = {
    text_start("JENN: Don't get"
        t_line "cocky! My sister"
        t_cont "KATE is tough!"
        t_done )
};
const txt_cmd_s CooltrainerfJennAfterText2[] = {
    text_start("JENN: Sunlight"
        t_line "makes your body"
        t_cont "stronger."
        t_done )
};
const txt_cmd_s CooltrainerfKateSeenText[] = {
    text_start("KATE: You sure"
        t_line "were mean to my"
        t_cont "little sisters!"
        t_done )
};
const txt_cmd_s CooltrainerfKateBeatenText[] = {
    text_start("KATE: No! I can't"
        t_line "believe I lost."
        t_done )
};
const txt_cmd_s CooltrainerfKateOfferSoftSandText[] = {
    text_start("KATE: You're too"
        t_line "strong. I didn't"
        t_cont "stand a chance."
        t_para "Here. You deserve"
        t_line "this."
        t_done )
};
const txt_cmd_s CooltrainerfKateAfterText[] = {
    text_start("KATE: I'm sorry we"
        t_line "jumped you."
        t_para "We never expected"
        t_line "anyone to find us"
        t_para "here. You sure"
        t_line "startled us."
        t_done )
};
const txt_cmd_s Route34IlexForestSignText[] = {
    text_start("ILEX FOREST"
        t_line "THROUGH THE GATE"
        t_done )
};
const txt_cmd_s Route34SignText[] = {
    text_start("ROUTE 34"
        t_para "GOLDENROD CITY -"
        t_line "AZALEA TOWN"
        t_para "ILEX FOREST"
        t_line "SOMEWHERE BETWEEN"
        t_done )
};
const txt_cmd_s Route34TrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "BERRY trees grow"
        t_line "new BERRIES"
        t_cont "every day."
        t_para "Make a note of"
        t_line "which trees bear"
        t_cont "which BERRIES."
        t_done )
};
const txt_cmd_s DayCareSignText[] = {
    text_start("DAY-CARE"
        t_para "LET US RAISE YOUR"
        t_line "#MON FOR YOU!"
        t_done )
    //db(0, 0) // filler
};
