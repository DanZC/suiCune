#include "../constants.h"
#include "../util/scripting.h"
#include "Route46.h"
//// EVENTS
enum {
    ROUTE46_POKEFAN_M = 2,
    ROUTE46_YOUNGSTER,
    ROUTE46_LASS,
    ROUTE46_FRUIT_TREE1,
    ROUTE46_FRUIT_TREE2,
    ROUTE46_POKE_BALL,
};

const Script_fn_t Route46_SceneScripts[] = {
    0,
};

const struct MapCallback Route46_MapCallbacks[] = {
    0,
};

const struct MapScripts Route46_MapScripts = {
    .scene_script_count = 0, // lengthof(Route46_SceneScripts),
    .scene_scripts = Route46_SceneScripts,

    .callback_count = 0, // lengthof(Route46_MapCallbacks),
    .callbacks = Route46_MapCallbacks,
};

static const struct CoordEvent Route46_CoordEvents[] = {
    0,
};

static const struct BGEvent Route46_BGEvents[] = {
    bg_event(9, 27, BGEVENT_READ, &Route46Sign),
};

static const struct WarpEventData Route46_WarpEvents[] = {
    warp_event(7, 33, ROUTE_29_ROUTE_46_GATE, 1),
    warp_event(8, 33, ROUTE_29_ROUTE_46_GATE, 2),
    warp_event(14, 5, DARK_CAVE_VIOLET_ENTRANCE, 3),
};

static const struct ObjEvent Route46_ObjectEvents[] = {
    object_event(12, 19, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerHikerBailey, -1),
    object_event(4, 14, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerCamperTed, -1),
    object_event(2, 13, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerPicnickerErin1, -1),
    object_event(7, 5, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route46FruitTree1, -1),
    object_event(8, 6, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route46FruitTree2, -1),
    object_event(1, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route46XSpeed, EVENT_ROUTE_46_X_SPEED),
};

const struct MapEvents Route46_MapEvents = {
    .warp_event_count = lengthof(Route46_WarpEvents),
    .warp_events = Route46_WarpEvents,

    .coord_event_count = 0, // lengthof(Route46_CoordEvents),
    .coord_events = Route46_CoordEvents,

    .bg_event_count = lengthof(Route46_BGEvents),
    .bg_events = Route46_BGEvents,

    .obj_event_count = lengthof(Route46_ObjectEvents),
    .obj_events = Route46_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route46.h"

const struct TrainerObj TrainerCamperTed = {CAMPER, TED, EVENT_BEAT_CAMPER_TED, CamperTedSeenText, CamperTedBeatenText, 0, TrainerCamperTed_Script};
bool TrainerCamperTed_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperTedAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerErin1 = {PICNICKER, ERIN1, EVENT_BEAT_PICNICKER_ERIN, PicnickerErin1SeenText, PicnickerErin1BeatenText, 0, TrainerPicnickerErin1_Script};
bool TrainerPicnickerErin1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_PICNICKER_ERIN)
    endifjustbattled
    opentext
    checkflag(ENGINE_ERIN_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkcellnum(PHONE_PICNICKER_ERIN)
    iftrue_jump(Route46NumberAcceptedF)
    checkevent(EVENT_ERIN_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(PicnickerErinAfterBattleText)
    promptbutton
    setevent(EVENT_ERIN_ASKED_FOR_PHONE_NUMBER)
    scall(Route46AskNumber1F)
    goto AskForNumber;
AskedAlready:
    scall(Route46AskNumber2F)
AskForNumber:
    askforphonenumber(PHONE_PICNICKER_ERIN)
    ifequal_jump(PHONE_CONTACTS_FULL, Route46PhoneFullF)
    ifequal_jump(PHONE_CONTACT_REFUSED, Route46NumberDeclinedF)
    gettrainername(STRING_BUFFER_3, PICNICKER, ERIN1)
    scall(Route46RegisteredNumberF)
    sjump(Route46NumberAcceptedF)
WantsBattle:
    scall(Route46RematchF)
    winlosstext(PicnickerErin1BeatenText, 0)
    readmem(&gPlayer.ErinFightCount)
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight2:
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight2)
Fight1:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(PICNICKER, ERIN1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ErinFightCount, 1)
    clearflag(ENGINE_ERIN_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(PICNICKER, ERIN2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ErinFightCount, 2)
    clearflag(ENGINE_ERIN_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(PICNICKER, ERIN3)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_ERIN_READY_FOR_REMATCH)
    checkevent(EVENT_ERIN_CALCIUM)
    iftrue(HasCalcium)
    checkevent(EVENT_GOT_CALCIUM_FROM_ERIN)
    iftrue(GotCalciumAlready)
    scall(Route46RematchGiftF)
    verbosegiveitem(CALCIUM, 1)
    iffalse_jump(ErinNoRoomForCalcium)
    setevent(EVENT_GOT_CALCIUM_FROM_ERIN)
    sjump(Route46NumberAcceptedF)
GotCalciumAlready:
    s_end
HasCalcium:
    opentext
    writetext(PicnickerErin2BeatenText)
    waitbutton
    verbosegiveitem(CALCIUM, 1)
    iffalse_jump(ErinNoRoomForCalcium)
    clearevent(EVENT_ERIN_CALCIUM)
    setevent(EVENT_GOT_CALCIUM_FROM_ERIN)
    sjump(Route46NumberAcceptedF)
    SCRIPT_END
}
bool Route46AskNumber1F(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(AskNumber1FScript)
    s_end
    SCRIPT_END
}
bool Route46AskNumber2F(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(AskNumber2FScript)
    s_end
    SCRIPT_END
}
bool Route46RegisteredNumberF(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RegisteredNumberFScript)
    s_end
    SCRIPT_END
}
bool Route46NumberAcceptedF(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(NumberAcceptedFScript)
    s_end
    SCRIPT_END
}
bool Route46NumberDeclinedF(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(NumberDeclinedFScript)
    s_end
    SCRIPT_END
}
bool Route46PhoneFullF(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PhoneFullFScript)
    s_end
    SCRIPT_END
}
bool Route46RematchF(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RematchFScript)
    s_end
    SCRIPT_END
}
bool ErinNoRoomForCalcium(script_s* s) {
    SCRIPT_BEGIN
    setevent(EVENT_ERIN_CALCIUM)
    jumpstd(PackFullFScript)
    s_end
    SCRIPT_END
}
bool Route46RematchGiftF(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(RematchGiftFScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerBailey = {HIKER, BAILEY, EVENT_BEAT_HIKER_BAILEY, HikerBaileySeenText, HikerBaileyBeatenText, 0, TrainerHikerBailey_Script};
bool TrainerHikerBailey_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerBaileyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route46Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route46SignText)
    SCRIPT_END
}
const struct ItemBall Route46XSpeed = {X_SPEED, 1};
bool Route46FruitTree1(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_46_1)
    SCRIPT_FALLTHROUGH(Route46FruitTree2)
}
bool Route46FruitTree2(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_46_2)
    SCRIPT_END
}
const txt_cmd_s HikerBaileySeenText[] = {
    text_start("Awright! I'll show"
        t_line "you the power of"
        t_cont "mountain #MON!"
        t_done )
};
const txt_cmd_s HikerBaileyBeatenText[] = {
    text_start("Mercy! You showed"
        t_line "me your power!"
        t_done )
};
const txt_cmd_s HikerBaileyAfterBattleText[] = {
    text_start("It's over. I don't"
        t_line "mind. We HIKERS"
        t_cont "are like that."
        t_done )
};
const txt_cmd_s CamperTedSeenText[] = {
    text_start("I'm raising #-"
        t_line "MON too!"
        t_para "Will you battle"
        t_line "with me?"
        t_done )
};
const txt_cmd_s CamperTedBeatenText[] = {
    text_start("Wha…?"
        t_done )
};
const txt_cmd_s CamperTedAfterBattleText[] = {
    text_start("I did my best but"
        t_line "came up short."
        t_para "No excuses--I"
        t_line "admit I lost."
        t_done )
};
const txt_cmd_s PicnickerErin1SeenText[] = {
    text_start("I raise #MON"
        t_line "too!"
        t_para "Will you battle"
        t_line "with me?"
        t_done )
};
const txt_cmd_s PicnickerErin1BeatenText[] = {
    text_start("Oh, rats!"
        t_done )
};
const txt_cmd_s PicnickerErinAfterBattleText[] = {
    text_start("I've been to many"
        t_line "GYMS, but the GYM"
        t_para "in GOLDENROD is my"
        t_line "favorite."
        t_para "It's filled with"
        t_line "pretty flowers!"
        t_done )
};
const txt_cmd_s PicnickerErin2BeatenText[] = {
    text_start("Aww… I keep losing"
        t_line "all the time!"
        t_para "I'll just have to"
        t_line "try harder!"
        t_para "Anyway, thanks for"
        t_line "battling me again"
        t_para "and again. Here's"
        t_line "that present from"
        t_cont "the other time."
        t_done )
};
const txt_cmd_s Route46SignText[] = {
    text_start("ROUTE 46"
        t_line "MOUNTAIN RD. AHEAD"
        t_done )
    //db(0, 0) // filler
};
