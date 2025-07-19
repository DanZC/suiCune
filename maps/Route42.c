#include "../constants.h"
#include "../util/scripting.h"
#include "Route42.h"
//// EVENTS
enum {
    ROUTE42_FISHER = 2,
    ROUTE42_POKEFAN_M,
    ROUTE42_SUPER_NERD,
    ROUTE42_FRUIT_TREE1,
    ROUTE42_FRUIT_TREE2,
    ROUTE42_FRUIT_TREE3,
    ROUTE42_POKE_BALL1,
    ROUTE42_POKE_BALL2,
    ROUTE42_SUICUNE,
};

const Script_fn_t Route42_SceneScripts[] = {
    Route42_MapScripts_DummyScene0 , //  SCENE_ROUTE42_NOTHING,
    Route42_MapScripts_DummyScene1 , //  SCENE_ROUTE42_SUICUNE,
};

const struct MapCallback Route42_MapCallbacks[] = {
    0,
};

const struct MapScripts Route42_MapScripts = {
    .scene_script_count = lengthof(Route42_SceneScripts),
    .scene_scripts = Route42_SceneScripts,

    .callback_count = 0, // lengthof(Route42_MapCallbacks),
    .callbacks = Route42_MapCallbacks,
};

static const struct CoordEvent Route42_CoordEvents[] = {
    coord_event(24, 14, SCENE_ROUTE42_SUICUNE, &Route42SuicuneScript),
};

static const struct BGEvent Route42_BGEvents[] = {
    bg_event(4, 10, BGEVENT_READ, &Route42Sign1),
    bg_event(7, 5, BGEVENT_READ, &MtMortarSign1),
    bg_event(45, 9, BGEVENT_READ, &MtMortarSign2),
    bg_event(54, 8, BGEVENT_READ, &Route42Sign2),
    bg_event(16, 11, BGEVENT_ITEM, &Route42HiddenMaxPotion),
};

static const struct WarpEventData Route42_WarpEvents[] = {
    warp_event(0, 8, ROUTE_42_ECRUTEAK_GATE, 3),
    warp_event(0, 9, ROUTE_42_ECRUTEAK_GATE, 4),
    warp_event(10, 5, MOUNT_MORTAR_1F_OUTSIDE, 1),
    warp_event(28, 9, MOUNT_MORTAR_1F_OUTSIDE, 2),
    warp_event(46, 7, MOUNT_MORTAR_1F_OUTSIDE, 3),
};

static const struct ObjEvent Route42_ObjectEvents[] = {
    object_event(40, 10, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerFisherTully, -1),
    object_event(51, 9, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 3, &TrainerHikerBenjamin, -1),
    object_event(47, 8, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacShane, -1),
    object_event(27, 16, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route42FruitTree1, -1),
    object_event(28, 16, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route42FruitTree2, -1),
    object_event(29, 16, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route42FruitTree3, -1),
    object_event(6, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route42UltraBall, EVENT_ROUTE_42_ULTRA_BALL),
    object_event(33, 8, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route42SuperPotion, EVENT_ROUTE_42_SUPER_POTION),
    object_event(26, 16, SPRITE_SUICUNE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_SAW_SUICUNE_ON_ROUTE_42),
};

const struct MapEvents Route42_MapEvents = {
    .warp_event_count = lengthof(Route42_WarpEvents),
    .warp_events = Route42_WarpEvents,

    .coord_event_count = lengthof(Route42_CoordEvents),
    .coord_events = Route42_CoordEvents,

    .bg_event_count = lengthof(Route42_BGEvents),
    .bg_events = Route42_BGEvents,

    .obj_event_count = lengthof(Route42_ObjectEvents),
    .obj_events = Route42_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route42.h"

bool Route42_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route42_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route42SuicuneScript(script_s* s) {
    SCRIPT_BEGIN
    showemote(EMOTE_SHOCK, PLAYER, 15)
    pause(15)
    playsound(SFX_WARP_FROM)
    applymovement(ROUTE42_SUICUNE, Route42SuicuneMovement)
    disappear(ROUTE42_SUICUNE)
    pause(10)
    setscene(SCENE_ROUTE42_NOTHING)
    clearevent(EVENT_SAW_SUICUNE_ON_ROUTE_36)
    setmapscene(ROUTE_36, SCENE_ROUTE36_SUICUNE)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherTully = {FISHER, TULLY1, EVENT_BEAT_FISHER_TULLY, FisherTullySeenText, FisherTullyBeatenText, 0, TrainerFisherTully_Script};
bool TrainerFisherTully_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_FISHER_TULLY)
    endifjustbattled
    opentext
    checkflag(ENGINE_TULLY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkflag(ENGINE_TULLY_HAS_WATER_STONE)
    iftrue(HasWaterStone)
    checkcellnum(PHONE_FISHER_TULLY)
    iftrue(NumberAccepted)
    checkevent(EVENT_TULLY_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(FisherTullyAfterBattleText)
    promptbutton
    setevent(EVENT_TULLY_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedAlready:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_FISHER_TULLY)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, FISHER, TULLY1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
WantsBattle:
    scall_local(Rematch);
    winlosstext(FisherTullyBeatenText, 0)
    readmem(&gPlayer.TullyFightCount)
    ifequal(3, Fight3)
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight3:
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight3)
Fight2:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight2)
Fight1:
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(FISHER, TULLY1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.TullyFightCount, 1)
    clearflag(ENGINE_TULLY_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(FISHER, TULLY2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.TullyFightCount, 2)
    clearflag(ENGINE_TULLY_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(FISHER, TULLY3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.TullyFightCount, 3)
    clearflag(ENGINE_TULLY_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(FISHER, TULLY4)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_TULLY_READY_FOR_REMATCH)
    s_end
HasWaterStone:
    scall_local(Gift);
    verbosegiveitem(WATER_STONE, 1)
    iffalse(NoRoom)
    clearflag(ENGINE_TULLY_HAS_WATER_STONE)
    setevent(EVENT_TULLY_GAVE_WATER_STONE)
    goto NumberAccepted;
NoRoom:
    goto PackFull;
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
Rematch:
    jumpstd(RematchMScript)
    s_end
Gift:
    jumpstd(GiftMScript)
    s_end
PackFull:
    jumpstd(PackFullMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacShane = {POKEMANIAC, SHANE, EVENT_BEAT_POKEMANIAC_SHANE, PokemaniacShaneSeenText, PokemaniacShaneBeatenText, 0, TrainerPokemaniacShane_Script};
bool TrainerPokemaniacShane_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacShaneAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerBenjamin = {HIKER, BENJAMIN, EVENT_BEAT_HIKER_BENJAMIN, HikerBenjaminSeenText, HikerBenjaminBeatenText, 0, TrainerHikerBenjamin_Script};
bool TrainerHikerBenjamin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerBenjaminAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route42Sign1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route42Sign1Text)
    SCRIPT_END
}
bool MtMortarSign1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MtMortarSign1Text)
    SCRIPT_END
}
bool MtMortarSign2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MtMortarSign2Text)
    SCRIPT_END
}
bool Route42Sign2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route42Sign2Text)
    SCRIPT_END
}
const struct ItemBall Route42UltraBall = {ULTRA_BALL, 1};
const struct ItemBall Route42SuperPotion = {SUPER_POTION, 1};
bool Route42FruitTree1(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_42_1)
    SCRIPT_FALLTHROUGH(Route42FruitTree2)
}
bool Route42FruitTree2(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_42_2)
    SCRIPT_FALLTHROUGH(Route42FruitTree3)
}
bool Route42FruitTree3(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_42_3)
    SCRIPT_END
}
const struct HiddenItem Route42HiddenMaxPotion = {MAX_POTION, EVENT_ROUTE_42_HIDDEN_MAX_POTION};
const uint8_t Route42SuicuneMovement[] = {
    movement_set_sliding,
    fast_jump_step(UP),
    fast_jump_step(UP),
    fast_jump_step(UP),
    fast_jump_step(RIGHT),
    fast_jump_step(RIGHT),
    fast_jump_step(RIGHT),
    movement_remove_sliding,
    movement_step_end,
};
const txt_cmd_s FisherTullySeenText[] = {
    text_start("Let me demonstrate"
        t_line "the power of the"
        t_cont "#MON I caught!"
        t_done )
};
const txt_cmd_s FisherTullyBeatenText[] = {
    text_start("What? That's not"
        t_line "right."
        t_done )
};
const txt_cmd_s FisherTullyAfterBattleText[] = {
    text_start("I want to become"
        t_line "the trainer CHAMP"
        t_para "using the #MON"
        t_line "I caught."
        t_para "That's the best"
        t_line "part of fishing!"
        t_done )
};
const txt_cmd_s HikerBenjaminSeenText[] = {
    text_start("Ah, it's good to"
        t_line "be outside!"
        t_cont "I feel so free!"
        t_done )
};
const txt_cmd_s HikerBenjaminBeatenText[] = {
    text_start("Gahahah!"
        t_done )
};
const txt_cmd_s HikerBenjaminAfterBattleText[] = {
    text_start("Losing feels in-"
        t_line "significant if you"
        t_para "look up at the big"
        t_line "sky!"
        t_done )
};
const txt_cmd_s PokemaniacShaneSeenText[] = {
    text_start("HEY!"
        t_para "This is my secret"
        t_line "place! Get lost,"
        t_cont "you outsider!"
        t_done )
};
const txt_cmd_s PokemaniacShaneBeatenText[] = {
    text_start("I should have used"
        t_line "my MOON STONE…"
        t_done )
};
const txt_cmd_s PokemaniacShaneAfterBattleText[] = {
    text_start("You're working on"
        t_line "a #DEX?"
        t_para "Wow, you must know"
        t_line "some pretty rare"
        t_cont "#MON!"
        t_para "May I please see"
        t_line "it. Please?"
        t_done )
};
const txt_cmd_s Route42Sign1Text[] = {
    text_start("ROUTE 42"
        t_para "ECRUTEAK CITY -"
        t_line "MAHOGANY TOWN"
        t_done )
};
const txt_cmd_s MtMortarSign1Text[] = {
    text_start("MT.MORTAR"
        t_para "WATERFALL CAVE"
        t_line "INSIDE"
        t_done )
};
const txt_cmd_s MtMortarSign2Text[] = {
    text_start("MT.MORTAR"
        t_para "WATERFALL CAVE"
        t_line "INSIDE"
        t_done )
};
const txt_cmd_s Route42Sign2Text[] = {
    text_start("ROUTE 42"
        t_para "ECRUTEAK CITY -"
        t_line "MAHOGANY TOWN"
        t_done )
    //db(0, 0) // filler
};
