#include "../constants.h"
#include "../util/scripting.h"
#include "BillsHouse.h"
//// EVENTS
enum {
    BILLSHOUSE_GRAMPS = 2,
};

const Script_fn_t BillsHouse_SceneScripts[] = {
    0,
};

const struct MapCallback BillsHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts BillsHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(BillsHouse_SceneScripts),
    .scene_scripts = BillsHouse_SceneScripts,

    .callback_count = 0, // lengthof(BillsHouse_MapCallbacks),
    .callbacks = BillsHouse_MapCallbacks,
};

static const struct CoordEvent BillsHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent BillsHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData BillsHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_25, 1),
    warp_event(3, 7, ROUTE_25, 1),
};

static const struct ObjEvent BillsHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 2, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &BillsGrandpa, -1),
};

const struct MapEvents BillsHouse_MapEvents = {
    .warp_event_count = lengthof(BillsHouse_WarpEvents),
    .warp_events = BillsHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(BillsHouse_CoordEvents),
    .coord_events = BillsHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(BillsHouse_BGEvents),
    .bg_events = BillsHouse_BGEvents,

    .obj_event_count = lengthof(BillsHouse_ObjectEvents),
    .obj_events = BillsHouse_ObjectEvents,
};

//// CODE

bool BillsGrandpa(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue(JustShowedSomething)
    checkevent(EVENT_GOT_THUNDERSTONE_FROM_BILLS_GRANDPA)
    iftrue(GotThunderstone)
    checkevent(EVENT_MET_BILLS_GRANDPA)
    iftrue(MetGrandpa)
    writetext(BillsGrandpaIntroText)
    promptbutton
    setevent(EVENT_MET_BILLS_GRANDPA)
MetGrandpa:
    checkevent(EVENT_SHOWED_PICHU_TO_BILLS_GRANDPA)
    iftrue(ShowedPichu)
    checkevent(EVENT_SHOWED_GROWLITHE_VULPIX_TO_BILLS_GRANDPA)
    iftrue(ShowedGrowlitheVulpix)
    checkevent(EVENT_SHOWED_STARYU_TO_BILLS_GRANDPA)
    iftrue(ShowedStaryu)
    checkevent(EVENT_SHOWED_ODDISH_TO_BILLS_GRANDPA)
    iftrue(ShowedOddish)
    checkevent(EVENT_SHOWED_LICKITUNG_TO_BILLS_GRANDPA)
    iftrue(ShowedLickitung)
    writetext(BillsGrandpaLickitungText)
    promptbutton
    writetext(BillsGrandpaAskToSeeMonText)
    yesorno
    iffalse(SaidNo)
    scall_local(ExcitedToSee);
    special(BillsGrandfather)
    iffalse(SaidNo)
    ifnotequal(LICKITUNG, WrongPokemon)
    scall_local(CorrectPokemon);
    setevent(EVENT_SHOWED_LICKITUNG_TO_BILLS_GRANDPA)
    goto ShowedLickitung;
GotEverstone:
    writetext(BillsGrandpaOddishText)
    promptbutton
    writetext(BillsGrandpaAskToSeeMonText)
    yesorno
    iffalse(SaidNo)
    scall_local(ExcitedToSee);
    special(BillsGrandfather)
    iffalse(SaidNo)
    ifnotequal(ODDISH, WrongPokemon)
    scall_local(CorrectPokemon);
    setevent(EVENT_SHOWED_ODDISH_TO_BILLS_GRANDPA)
    goto ShowedOddish;
GotLeafStone:
    writetext(BillsGrandpaStaryuText)
    promptbutton
    writetext(BillsGrandpaAskToSeeMonText)
    yesorno
    iffalse(SaidNo)
    scall_local(ExcitedToSee);
    special(BillsGrandfather)
    iffalse(SaidNo)
    ifnotequal(STARYU, WrongPokemon)
    scall_local(CorrectPokemon);
    setevent(EVENT_SHOWED_STARYU_TO_BILLS_GRANDPA)
    goto ShowedStaryu;
GotWaterStone:
    //checkver
    iftrue(AskVulpix)
    writetext(BillsGrandpaGrowlitheText)
    promptbutton
    writetext(BillsGrandpaAskToSeeMonText)
    yesorno
    iffalse(SaidNo)
    scall_local(ExcitedToSee);
    special(BillsGrandfather)
    iffalse(SaidNo)
    ifnotequal(GROWLITHE, WrongPokemon)
    scall_local(CorrectPokemon);
    setevent(EVENT_SHOWED_GROWLITHE_VULPIX_TO_BILLS_GRANDPA)
    goto ShowedGrowlitheVulpix;
AskVulpix:
    writetext(BillsGrandpaVulpixText)
    promptbutton
    writetext(BillsGrandpaAskToSeeMonText)
    yesorno
    iffalse(SaidNo)
    scall_local(ExcitedToSee);
    special(BillsGrandfather)
    iffalse(SaidNo)
    ifnotequal(VULPIX, WrongPokemon)
    scall_local(CorrectPokemon);
    setevent(EVENT_SHOWED_GROWLITHE_VULPIX_TO_BILLS_GRANDPA)
    goto ShowedGrowlitheVulpix;
GotFireStone:
    writetext(BillsGrandpaPichuText)
    promptbutton
    writetext(BillsGrandpaAskToSeeMonText)
    yesorno
    iffalse(SaidNo)
    scall_local(ExcitedToSee);
    special(BillsGrandfather)
    iffalse(SaidNo)
    ifnotequal(PICHU, WrongPokemon)
    scall_local(CorrectPokemon);
    setevent(EVENT_SHOWED_PICHU_TO_BILLS_GRANDPA)
    goto ShowedPichu;
ShowedLickitung:
    checkevent(EVENT_GOT_EVERSTONE_FROM_BILLS_GRANDPA)
    iftrue(GotEverstone)
    scall_local(ReceiveItem);
    verbosegiveitem(EVERSTONE, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_EVERSTONE_FROM_BILLS_GRANDPA)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    closetext
    s_end
ShowedOddish:
    checkevent(EVENT_GOT_LEAF_STONE_FROM_BILLS_GRANDPA)
    iftrue(GotLeafStone)
    scall_local(ReceiveItem);
    verbosegiveitem(LEAF_STONE, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_LEAF_STONE_FROM_BILLS_GRANDPA)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    closetext
    s_end
ShowedStaryu:
    checkevent(EVENT_GOT_WATER_STONE_FROM_BILLS_GRANDPA)
    iftrue(GotWaterStone)
    scall_local(ReceiveItem);
    verbosegiveitem(WATER_STONE, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_WATER_STONE_FROM_BILLS_GRANDPA)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    closetext
    s_end
ShowedGrowlitheVulpix:
    checkevent(EVENT_GOT_FIRE_STONE_FROM_BILLS_GRANDPA)
    iftrue(GotFireStone)
    scall_local(ReceiveItem);
    verbosegiveitem(FIRE_STONE, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_FIRE_STONE_FROM_BILLS_GRANDPA)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    closetext
    s_end
ShowedPichu:
    scall_local(ReceiveItem);
    verbosegiveitem(THUNDERSTONE, 1)
    iffalse(BagFull)
    setevent(EVENT_GOT_THUNDERSTONE_FROM_BILLS_GRANDPA)
    closetext
    s_end
ExcitedToSee:
    writetext(BillsGrandpaExcitedToSeeText)
    promptbutton
    s_end
SaidNo:
    writetext(BillsGrandpaYouDontHaveItTextText)
    waitbutton
    closetext
    s_end
CorrectPokemon:
    writetext(BillsGrandpaShownPokemonText)
    promptbutton
    s_end
ReceiveItem:
    writetext(BillsGrandpaTokenOfAppreciationText)
    promptbutton
    s_end
JustShowedSomething:
    writetext(BillsGrandpaComeAgainText)
    waitbutton
    closetext
    s_end
GotThunderstone:
    writetext(BillsGrandpaShownAllThePokemonText)
    waitbutton
    closetext
    s_end
WrongPokemon:
    writetext(BillsGrandpaWrongPokemonText)
    waitbutton
    closetext
    s_end
BagFull:
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s BillsGrandpaIntroText[] = {
    text_start("Hm? You know BILL?"
        t_line "He's my grandson."
        t_para "He's in JOHTO. He"
        t_line "does something"
        t_para "with PCs, so I'm"
        t_line "house-sitting."
        t_done )
};
const txt_cmd_s BillsGrandpaAskToSeeMonText[] = {
    text_start("If you have that"
        t_line "#MON, may I see"
        t_cont "it, please?"
        t_done )
};
const txt_cmd_s BillsGrandpaExcitedToSeeText[] = {
    text_start("You will show me?"
        t_line "How good of you!"
        t_done )
};
const txt_cmd_s BillsGrandpaYouDontHaveItTextText[] = {
    text_start("You don't have it?"
        t_line "That's too bad…"
        t_done )
};
const txt_cmd_s BillsGrandpaShownPokemonText[] = {
    text_start("Ah, so that is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "Isn't it cute!"
        t_line "That's so kind of"
        t_cont "you."
        t_done )
};
const txt_cmd_s BillsGrandpaTokenOfAppreciationText[] = {
    text_start("Thanks!"
        t_para "This is a token of"
        t_line "my appreciation."
        t_done )
};
const txt_cmd_s BillsGrandpaComeAgainText[] = {
    text_start("Come visit again"
        t_line "sometime."
        t_done )
};
const txt_cmd_s BillsGrandpaShownAllThePokemonText[] = {
    text_start("Thanks for showing"
        t_line "me so many cute"
        t_cont "#MON."
        t_para "I really enjoyed"
        t_line "myself. I'm glad"
        t_para "I've lived such a"
        t_line "long life."
        t_done )
};
const txt_cmd_s BillsGrandpaWrongPokemonText[] = {
    text_start("Hm?"
        t_para "That's not the"
        t_line "#MON that I was"
        t_cont "told about."
        t_done )
};
const txt_cmd_s BillsGrandpaLickitungText[] = {
    text_start("My grandson BILL"
        t_line "told me about a"
        t_para "#MON that has a"
        t_line "long tongue."
        t_done )
};
const txt_cmd_s BillsGrandpaOddishText[] = {
    text_start("Ah, my grandson"
        t_line "mentioned a round,"
        t_para "green #MON that"
        t_line "has leaves growing"
        t_cont "on its head."
        t_done )
};
const txt_cmd_s BillsGrandpaStaryuText[] = {
    text_start("Do you know of a"
        t_line "sea #MON that"
        t_para "has a red sphere"
        t_line "in its body?"
        t_para "You know, the one"
        t_line "that's shaped like"
        t_cont "a star?"
        t_para "I heard that it"
        t_line "appears at night."
        t_para "I would surely"
        t_line "like to see it."
        t_done )
};
const txt_cmd_s BillsGrandpaGrowlitheText[] = {
    text_start("BILL told me about"
        t_line "a #MON that is"
        t_para "very loyal to its"
        t_line "trainer."
        t_para "It's supposed to"
        t_line "ROAR well."
        t_done )
};
const txt_cmd_s BillsGrandpaVulpixText[] = {
    text_start("I heard about a"
        t_line "cute #MON that"
        t_cont "has six tails."
        t_para "I would love to"
        t_line "hug a cute #MON"
        t_cont "like that."
        t_done )
};
const txt_cmd_s BillsGrandpaPichuText[] = {
    text_start("Do you know that"
        t_line "hugely popular"
        t_cont "#MON?"
        t_para "The #MON that"
        t_line "has a yellow body"
        t_cont "and red cheeks."
        t_para "I would love to"
        t_line "see what it looks"
        t_para "like before it"
        t_line "evolves."
        t_done )
    //db(0, 0) // filler
};
