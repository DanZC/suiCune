#include "../constants.h"
#include "../util/scripting.h"
#include "Route43.h"
//// EVENTS
enum {
    ROUTE43_SUPER_NERD1 = 2,
    ROUTE43_SUPER_NERD2,
    ROUTE43_SUPER_NERD3,
    ROUTE43_FISHER,
    ROUTE43_LASS,
    ROUTE43_YOUNGSTER,
    ROUTE43_FRUIT_TREE,
    ROUTE43_POKE_BALL,
};

const Script_fn_t Route43_SceneScripts[] = {
    0,
};

const struct MapCallback Route43_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route43_MapScripts_CheckIfRockets),
};

const struct MapScripts Route43_MapScripts = {
    .scene_script_count = 0, // lengthof(Route43_SceneScripts),
    .scene_scripts = Route43_SceneScripts,

    .callback_count = lengthof(Route43_MapCallbacks),
    .callbacks = Route43_MapCallbacks,
};

static const struct CoordEvent Route43_CoordEvents[] = {
    0,
};

static const struct BGEvent Route43_BGEvents[] = {
    bg_event(13, 3, BGEVENT_READ, &Route43Sign1),
    bg_event(11, 49, BGEVENT_READ, &Route43Sign2),
    bg_event(16, 38, BGEVENT_READ, &Route43TrainerTips),
};

static const struct WarpEventData Route43_WarpEvents[] = {
    warp_event(9, 51, ROUTE_43_MAHOGANY_GATE, 1),
    warp_event(10, 51, ROUTE_43_MAHOGANY_GATE, 2),
    warp_event(17, 35, ROUTE_43_GATE, 3),
    warp_event(17, 31, ROUTE_43_GATE, 1),
    warp_event(18, 31, ROUTE_43_GATE, 2),
};

static const struct ObjEvent Route43_ObjectEvents[] = {
    object_event(13, 5, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerPokemaniacBen, -1),
    object_event(13, 20, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerPokemaniacBrent, -1),
    object_event(14, 7, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerPokemaniacRon, -1),
    object_event(4, 16, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 4, &TrainerFisherMarvin, -1),
    object_event(9, 25, SPRITE_LASS, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerPicnickerTiffany, -1),
    object_event(13, 40, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerCamperSpencer, -1),
    object_event(1, 26, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route43FruitTree, -1),
    object_event(12, 32, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route43MaxEther, EVENT_ROUTE_43_MAX_ETHER),
};

const struct MapEvents Route43_MapEvents = {
    .warp_event_count = lengthof(Route43_WarpEvents),
    .warp_events = Route43_WarpEvents,

    .coord_event_count = 0, // lengthof(Route43_CoordEvents),
    .coord_events = Route43_CoordEvents,

    .bg_event_count = lengthof(Route43_BGEvents),
    .bg_events = Route43_BGEvents,

    .obj_event_count = lengthof(Route43_ObjectEvents),
    .obj_events = Route43_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route43.h"

bool Route43_MapScripts_CheckIfRockets(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_CLEARED_ROCKET_HIDEOUT)
    iftrue(NoRockets)
    setmapscene(ROUTE_43_GATE, SCENE_DEFAULT)
    s_endcallback
NoRockets:
    setmapscene(ROUTE_43_GATE, SCENE_FINISHED)
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerCamperSpencer = {CAMPER, SPENCER, EVENT_BEAT_CAMPER_SPENCER, CamperSpencerSeenText, CamperSpencerBeatenText, 0, TrainerCamperSpencer_Script};
bool TrainerCamperSpencer_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperSpencerAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacBen = {POKEMANIAC, BEN, EVENT_BEAT_POKEMANIAC_BEN, PokemaniacBenSeenText, PokemaniacBenBeatenText, 0, TrainerPokemaniacBen_Script};
bool TrainerPokemaniacBen_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacBenAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacBrent = {POKEMANIAC, BRENT1, EVENT_BEAT_POKEMANIAC_BRENT, PokemaniacBrentSeenText, PokemaniacBrentBeatenText, 0, TrainerPokemaniacBrent_Script};
bool TrainerPokemaniacBrent_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_POKEMANIAC_BRENT)
    endifjustbattled
    opentext
    checkflag(ENGINE_BRENT_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkcellnum(PHONE_POKEMANIAC_BRENT)
    iftrue(NumberAccepted)
    checkevent(EVENT_BRENT_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(PokemaniacBrentAfterBattleText)
    promptbutton
    setevent(EVENT_BRENT_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedAlready:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_POKEMANIAC_BRENT)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, POKEMANIAC, BRENT1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
WantsBattle:
    scall_local(Rematch);
    winlosstext(PokemaniacBrentBeatenText, 0)
    readmem(wram_ptr(wBrentFightCount))
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
    loadtrainer(POKEMANIAC, BRENT1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wBrentFightCount), 1)
    clearflag(ENGINE_BRENT_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(POKEMANIAC, BRENT2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wBrentFightCount), 2)
    clearflag(ENGINE_BRENT_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(POKEMANIAC, BRENT3)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wBrentFightCount), 3)
    clearflag(ENGINE_BRENT_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(POKEMANIAC, BRENT4)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_BRENT_READY_FOR_REMATCH)
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
Rematch:
    jumpstd(RematchMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokemaniacRon = {POKEMANIAC, RON, EVENT_BEAT_POKEMANIAC_RON, PokemaniacRonSeenText, PokemaniacRonBeatenText, 0, TrainerPokemaniacRon_Script};
bool TrainerPokemaniacRon_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokemaniacRonAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerFisherMarvin = {FISHER, MARVIN, EVENT_BEAT_FISHER_MARVIN, FisherMarvinSeenText, FisherMarvinBeatenText, 0, TrainerFisherMarvin_Script};
bool TrainerFisherMarvin_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(FisherMarvinAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerTiffany = {PICNICKER, TIFFANY3, EVENT_BEAT_PICNICKER_TIFFANY, PicnickerTiffanySeenText, PicnickerTiffanyBeatenText, 0, TrainerPicnickerTiffany_Script};
bool TrainerPicnickerTiffany_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_PICNICKER_TIFFANY)
    endifjustbattled
    opentext
    checkflag(ENGINE_TIFFANY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkflag(ENGINE_TIFFANY_HAS_PINK_BOW)
    iftrue(HasPinkBow)
    checkcellnum(PHONE_PICNICKER_TIFFANY)
    iftrue(NumberAccepted)
    checkpoke(CLEFAIRY)
    iffalse(NoClefairy)
    checkevent(EVENT_TIFFANY_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(PicnickerTiffanyWantsPicnicText)
    promptbutton
    setevent(EVENT_TIFFANY_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedAlready:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_PICNICKER_TIFFANY)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, PICNICKER, TIFFANY3)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
WantsBattle:
    scall_local(Rematch);
    winlosstext(PicnickerTiffanyBeatenText, 0)
    readmem(wram_ptr(wTiffanyFightCount))
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
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(PICNICKER, TIFFANY3)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wTiffanyFightCount), 1)
    clearflag(ENGINE_TIFFANY_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(PICNICKER, TIFFANY1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wTiffanyFightCount), 2)
    clearflag(ENGINE_TIFFANY_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(PICNICKER, TIFFANY2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wTiffanyFightCount), 3)
    clearflag(ENGINE_TIFFANY_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(PICNICKER, TIFFANY4)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_TIFFANY_READY_FOR_REMATCH)
    s_end
HasPinkBow:
    scall_local(Gift);
    verbosegiveitem(PINK_BOW, 1)
    iffalse(NoRoom)
    clearflag(ENGINE_TIFFANY_HAS_PINK_BOW)
    setevent(EVENT_TIFFANY_GAVE_PINK_BOW)
    goto NumberAccepted;
NoRoom:
    goto PackFull;
NoClefairy:
    writetext(PicnickerTiffanyClefairyText)
    waitbutton
    closetext
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
Rematch:
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
bool Route43Sign1(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route43Sign1Text)
    SCRIPT_END
}
bool Route43Sign2(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route43Sign2Text)
    SCRIPT_END
}
bool Route43TrainerTips(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route43TrainerTipsText)
    SCRIPT_END
}
bool Route43FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_43)
    SCRIPT_END
}
const struct ItemBall Route43MaxEther = {MAX_ETHER, 1};
const txt_cmd_s PokemaniacBenSeenText[] = {
    text_start("I love #MON!"
        t_para "That's why I"
        t_line "started--and why"
        t_para "I'll keep on col-"
        t_line "lecting #MON!"
        t_done )
};
const txt_cmd_s PokemaniacBenBeatenText[] = {
    text_start("How could you do"
        t_line "this to me?"
        t_done )
};
const txt_cmd_s PokemaniacBenAfterBattleText[] = {
    text_start("What else do I"
        t_line "like besides"
        t_cont "#MON?"
        t_para "MARY on the radio."
        t_line "I bet she's cute!"
        t_done )
};
const txt_cmd_s PokemaniacBrentSeenText[] = {
    text_start("Hey! Do you have"
        t_line "any rare #MON?"
        t_done )
};
const txt_cmd_s PokemaniacBrentBeatenText[] = {
    text_start("Oh, my poor #-"
        t_line "MON! Darlings!"
        t_done )
};
const txt_cmd_s PokemaniacBrentAfterBattleText[] = {
    text_start("I'd be happy just"
        t_line "to own a single"
        t_cont "rare #MON."
        t_done )
};
const txt_cmd_s PokemaniacRonSeenText[] = {
    text_start("Would you get"
        t_line "this?"
        t_para "Some <RIVAL> guy"
        t_line "made fun of my"
        t_cont "#MON!"
        t_para "Darn it! My #-"
        t_line "MON's great!"
        t_done )
};
const txt_cmd_s PokemaniacRonBeatenText[] = {
    text_start("My NIDOKING did"
        t_line "pretty right on!"
        t_done )
};
const txt_cmd_s PokemaniacRonAfterBattleText[] = {
    text_start("It's okay for"
        t_line "people to like"
        t_para "different types"
        t_line "of #MON."
        t_para "#MON isn't just"
        t_line "about having the"
        t_cont "most powerful one."
        t_done )
};
const txt_cmd_s FisherMarvinSeenText[] = {
    text_start("I'm in a slump."
        t_para "Maybe it's the"
        t_line "gear I'm using."
        t_para "Let's battle for a"
        t_line "change of pace!"
        t_done )
};
const txt_cmd_s FisherMarvinBeatenText[] = {
    text_start("I lost, but I feel"
        t_line "better anyway."
        t_done )
};
const txt_cmd_s FisherMarvinAfterBattleText[] = {
    text_start("KURT's LURE BALL"
        t_line "is the best for"
        t_para "catching hooked"
        t_line "#MON."
        t_para "It's much more"
        t_line "effective than a"
        t_cont "ULTRA BALL."
        t_done )
};
const txt_cmd_s CamperSpencerSeenText[] = {
    text_start("I can do so much"
        t_line "with my #MON--"
        t_cont "it's super-fun!"
        t_done )
};
const txt_cmd_s CamperSpencerBeatenText[] = {
    text_start("Losing isn't fun"
        t_line "at all…"
        t_done )
};
const txt_cmd_s CamperSpencerAfterBattleText[] = {
    text_start("What is going on"
        t_line "at LAKE OF RAGE?"
        t_para "We were planning"
        t_line "to camp there."
        t_done )
};
const txt_cmd_s PicnickerTiffanySeenText[] = {
    text_start("Are you going to"
        t_line "LAKE OF RAGE too?"
        t_para "Let's play for a "
        t_line "little while!"
        t_done )
};
const txt_cmd_s PicnickerTiffanyBeatenText[] = {
    text_start("I played too much!"
        t_done )
};
const txt_cmd_s PicnickerTiffanyWantsPicnicText[] = {
    text_start("I'm having a pic-"
        t_line "nic with #MON."
        t_para "Won't you join us?"
        t_done )
};
const txt_cmd_s PicnickerTiffanyClefairyText[] = {
    text_start("Isn't my CLEFAIRY"
        t_line "just the most"
        t_cont "adorable thing?"
        t_done )
};
const txt_cmd_s Route43Sign1Text[] = {
    text_start("ROUTE 43"
        t_para "LAKE OF RAGE -"
        t_line "MAHOGANY TOWN"
        t_done )
};
const txt_cmd_s Route43Sign2Text[] = {
    text_start("ROUTE 43"
        t_para "LAKE OF RAGE -"
        t_line "MAHOGANY TOWN"
        t_done )
};
const txt_cmd_s Route43TrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "All #MON have"
        t_line "pros and cons"
        t_para "depending on their"
        t_line "types."
        t_para "If their types"
        t_line "differ, a higher-"
        t_para "level #MON may"
        t_line "lose in battle."
        t_para "Learn which types"
        t_line "are strong and"
        t_para "weak against your"
        t_line "#MON's type."
        t_done )
    //db(0, 0) // filler
};
