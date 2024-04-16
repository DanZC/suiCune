#include "../constants.h"
#include "../util/scripting.h"
#include "Route31.h"
//// EVENTS
enum {
    ROUTE31_FISHER = 2,
    ROUTE31_YOUNGSTER,
    ROUTE31_BUG_CATCHER,
    ROUTE31_COOLTRAINER_M,
    ROUTE31_FRUIT_TREE,
    ROUTE31_POKE_BALL1,
    ROUTE31_POKE_BALL2,
};

const Script_fn_t Route31_SceneScripts[] = {
    0
};

const struct MapCallback Route31_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route31_MapScripts_CheckMomCall),
};

const struct MapScripts Route31_MapScripts = {
    .scene_script_count = lengthof(Route31_SceneScripts),
    .scene_scripts = Route31_SceneScripts,

    .callback_count = lengthof(Route31_MapCallbacks),
    .callbacks = Route31_MapCallbacks,
};

static const struct CoordEvent Route31_CoordEvents[] = {
    0
};

static const struct BGEvent Route31_BGEvents[] = {
    bg_event(7, 5, BGEVENT_READ, &Route31Sign),
    bg_event(31, 5, BGEVENT_READ, &DarkCaveSign),
};

static const struct WarpEventData Route31_WarpEvents[] = {
    warp_event(4, 6, ROUTE_31_VIOLET_GATE, 3),
    warp_event(4, 7, ROUTE_31_VIOLET_GATE, 4),
    warp_event(34, 5, DARK_CAVE_VIOLET_ENTRANCE, 1),
};

static const struct ObjEvent Route31_ObjectEvents[] = {
    object_event(17, 7, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route31MailRecipientScript, -1),
    object_event(9, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route31YoungsterScript, -1),
    object_event(21, 13, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 5, &TrainerBugCatcherWade1, -1),
    object_event(33, 8, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route31CooltrainerMScript, -1),
    object_event(16, 7, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route31FruitTree, -1),
    object_event(29, 5, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route31Potion, EVENT_ROUTE_31_POTION),
    object_event(19, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &Route31PokeBall, EVENT_ROUTE_31_POKE_BALL),
};

const struct MapEvents Route31_MapEvents = {
    .warp_event_count = lengthof(Route31_WarpEvents),
    .warp_events = Route31_WarpEvents,

    .coord_event_count = lengthof(Route31_CoordEvents),
    .coord_events = Route31_CoordEvents,

    .bg_event_count = lengthof(Route31_BGEvents),
    .bg_events = Route31_BGEvents,

    .obj_event_count = lengthof(Route31_ObjectEvents),
    .obj_events = Route31_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route31.h"

bool Route31_MapScripts_CheckMomCall(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST)
    iffalse_jump(Route31_MapScripts_DoMomCall)
    s_endcallback
    SCRIPT_END
}
bool Route31_MapScripts_DoMomCall(script_s* s) {
    SCRIPT_BEGIN
    specialphonecall(SPECIALCALL_WORRIED)
    s_endcallback
    SCRIPT_END
}
const struct TrainerObj TrainerBugCatcherWade1 = {BUG_CATCHER, WADE1, EVENT_BEAT_BUG_CATCHER_WADE, BugCatcherWade1SeenText, BugCatcherWade1BeatenText, 0, TrainerBugCatcherWade1_Script};
bool TrainerBugCatcherWade1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_BUG_CATCHER_WADE)
    endifjustbattled
    opentext
    checkflag(ENGINE_WADE_READY_FOR_REMATCH)
    iftrue(WadeRematch)
    checkflag(ENGINE_WADE_HAS_ITEM)
    iftrue(WadeItem)
    checkcellnum(PHONE_BUG_CATCHER_WADE)
    iftrue(AcceptedNumberSTD)
    checkevent(EVENT_WADE_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(BugCatcherWade1AfterText)
    waitbutton
    setevent(EVENT_WADE_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskPhoneNumberSTD);
    goto Continue;
AskAgain:
    scall_local(AskAgainSTD);
Continue:
    askforphonenumber(PHONE_BUG_CATCHER_WADE)
    ifequal(PHONE_CONTACTS_FULL, PhoneFullSTD)
    ifequal(PHONE_CONTACT_REFUSED, DeclinedNumberSTD)
    gettrainername(STRING_BUFFER_3, BUG_CATCHER, WADE1)
    scall_local(RegisterNumberSTD);
    goto AcceptedNumberSTD;
WadeRematch:
    scall_local(RematchSTD);
    winlosstext(BugCatcherWade1BeatenText, 0)
    readmem(wram_ptr(wWadeFightCount))
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
    checkflag(ENGINE_FLYPOINT_MAHOGANY)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_GOLDENROD)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(BUG_CATCHER, WADE1)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wWadeFightCount), 1)
    clearflag(ENGINE_WADE_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(BUG_CATCHER, WADE2)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wWadeFightCount), 2)
    clearflag(ENGINE_WADE_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(BUG_CATCHER, WADE3)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wWadeFightCount), 3)
    clearflag(ENGINE_WADE_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(BUG_CATCHER, WADE4)
    startbattle
    reloadmapafterbattle
    loadmem(wram_ptr(wWadeFightCount), 4)
    clearflag(ENGINE_WADE_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(BUG_CATCHER, WADE5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_WADE_READY_FOR_REMATCH)
    s_end
WadeItem:
    scall_local(ItemSTD);
    checkevent(EVENT_WADE_HAS_BERRY)
    iftrue(Berry)
    checkevent(EVENT_WADE_HAS_PSNCUREBERRY)
    iftrue(Psncureberry)
    checkevent(EVENT_WADE_HAS_PRZCUREBERRY)
    iftrue(Przcureberry)
    checkevent(EVENT_WADE_HAS_BITTER_BERRY)
    iftrue(BitterBerry)
Berry:
    verbosegiveitem(BERRY, 1)
    iffalse(PackFull)
    goto Done;
Psncureberry:
    verbosegiveitem(PSNCUREBERRY, 1)
    iffalse(PackFull)
    goto Done;
Przcureberry:
    verbosegiveitem(PRZCUREBERRY, 1)
    iffalse(PackFull)
    goto Done;
BitterBerry:
    verbosegiveitem(BITTER_BERRY, 1)
    iffalse(PackFull)
Done:
    clearflag(ENGINE_WADE_HAS_ITEM)
    goto AcceptedNumberSTD;
PackFull:
    goto PackFullSTD;
AskPhoneNumberSTD:
    jumpstd(AskNumber1MScript)
    s_end
AskAgainSTD:
    jumpstd(AskNumber2MScript)
    s_end
RegisterNumberSTD:
    jumpstd(RegisteredNumberMScript)
    s_end
AcceptedNumberSTD:
    jumpstd(NumberAcceptedMScript)
    s_end
DeclinedNumberSTD:
    jumpstd(NumberDeclinedMScript)
    s_end
PhoneFullSTD:
    jumpstd(PhoneFullMScript)
    s_end
RematchSTD:
    jumpstd(RematchMScript)
    s_end
ItemSTD:
    jumpstd(GiftMScript)
    s_end
PackFullSTD:
    jumpstd(PackFullMScript)
    s_end
    SCRIPT_END
}
bool Route31MailRecipientScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM50_NIGHTMARE)
    iftrue(DescribeNightmare)
    checkevent(EVENT_GOT_KENYA)
    iftrue(TryGiveKenya)
    writetext(Text_Route31SleepyMan)
    waitbutton
    closetext
    s_end
TryGiveKenya:
    writetext(Text_Route31SleepyManGotMail)
    promptbutton
    checkpokemail(ReceivedSpearowMailText)
    ifequal(POKEMAIL_WRONG_MAIL, WrongMail)
    ifequal(POKEMAIL_REFUSED, Refused)
    ifequal(POKEMAIL_NO_MAIL, NoMail)
    ifequal(POKEMAIL_LAST_MON, LastMon)
    // POKEMAIL_CORRECT
    writetext(Text_Route31HandOverMailMon)
    promptbutton
    writetext(Text_Route31ReadingMail)
    promptbutton
    setevent(EVENT_GAVE_KENYA)
    verbosegiveitem(TM_NIGHTMARE, 1)
    iffalse(NoRoomForItems)
    setevent(EVENT_GOT_TM50_NIGHTMARE)
DescribeNightmare:
    writetext(Text_Route31DescribeNightmare)
    waitbutton
NoRoomForItems:
    closetext
    s_end
WrongMail:
    writetext(Text_Route31WrongMail)
    waitbutton
    closetext
    s_end
NoMail:
    writetext(Text_Route31MissingMail)
    waitbutton
    closetext
    s_end
Refused:
    writetext(Text_Route31DeclinedToHandOverMail)
    waitbutton
    closetext
    s_end
LastMon:
    writetext(Text_Route31CantTakeLastMon)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}

const char ReceivedSpearowMailText[] = "DARK CAVE leads"
    t_next "to another road@";

bool Route31YoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route31YoungsterText)
    SCRIPT_END
}
bool Route31Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route31SignText)
    SCRIPT_END
}
bool DarkCaveSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(DarkCaveSignText)
    SCRIPT_END
}
bool Route31CooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route31CooltrainerMText)
    SCRIPT_END
}
bool Route31FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_31)
    SCRIPT_END
}
const struct ItemBall Route31Potion = {POTION, 1};
const struct ItemBall Route31PokeBall = {POKE_BALL, 1};
const txt_cmd_s Route31CooltrainerMText[] = {
    text_start("DARK CAVE…"
        t_para "If #MON could"
        t_line "light it up, I'd"
        t_cont "explore it."
        t_done )
};
const txt_cmd_s BugCatcherWade1SeenText[] = {
    text_start("I caught a bunch"
        t_line "of #MON. Let me"
        t_cont "battle with you!"
        t_done )
};
const txt_cmd_s BugCatcherWade1BeatenText[] = {
    text_start("Awwwww…"
        t_done )
};
const txt_cmd_s BugCatcherWade1AfterText[] = {
    text_start("You can catch"
        t_line "#MON even if"
        t_para "you have six with"
        t_line "you."
        t_para "If you catch one,"
        t_line "it'll go to your"
        t_cont "BOX automatically."
        t_done )
};
const txt_cmd_s Text_Route31SleepyMan[] = {
    text_start("… Hnuurg… Huh?"
        t_para "I walked too far"
        t_line "today looking for"
        t_cont "#MON."
        t_para "My feet hurt and"
        t_line "I'm sleepy…"
        t_para "If I were a wild"
        t_line "#MON, I'd be"
        t_cont "easy to catch…"
        t_para "…Zzzz…"
        t_done )
};
const txt_cmd_s Text_Route31SleepyManGotMail[] = {
    text_start("…Zzzz… Huh?"
        t_para "What's that? You"
        t_line "have MAIL for me?"
        t_done )
};
const txt_cmd_s Text_Route31HandOverMailMon[] = {
    text_start("<PLAYER> handed"
        t_line "over the #MON"
        t_cont "holding the MAIL."
        t_done )
};
const txt_cmd_s Text_Route31ReadingMail[] = {
    text_start("Let's see…"
        t_para "…DARK CAVE leads"
        t_line "to another road…"
        t_para "That's good to"
        t_line "know."
        t_para "Thanks for bring-"
        t_line "ing this to me."
        t_para "My friend's a good"
        t_line "guy, and you're"
        t_cont "swell too!"
        t_para "I'd like to do"
        t_line "something good in"
        t_cont "return too!"
        t_para "I know! I want you"
        t_line "to have this!"
        t_done )
};
const txt_cmd_s Text_Route31DescribeNightmare[] = {
    text_start("TM50 is NIGHTMARE."
        t_para "It's a wicked move"
        t_line "that steadily cuts"
        t_para "the HP of a sleep-"
        t_line "ing enemy."
        t_para "Ooooh…"
        t_line "That's scary…"
        t_para "I don't want to"
        t_line "have bad dreams."
        t_done )
};
const txt_cmd_s Text_Route31WrongMail[] = {
    text_start("This MAIL isn't"
        t_line "for me."
        t_done )
};
const txt_cmd_s Text_Route31MissingMail[] = {
    text_start("Why is this #-"
        t_line "MON so special?"
        t_para "It doesn't have"
        t_line "any MAIL."
        t_done )
};
const txt_cmd_s Text_Route31DeclinedToHandOverMail[] = {
    text_start("What? You don't"
        t_line "want anything?"
        t_done )
};
const txt_cmd_s Text_Route31CantTakeLastMon[] = {
    text_start("If I take that"
        t_line "#MON from you,"
        t_para "what are you going"
        t_line "to use in battle?"
        t_done )
};
const txt_cmd_s Route31YoungsterText[] = {
    text_start("I found a good"
        t_line "#MON in DARK"
        t_cont "CAVE."
        t_para "I'm going to raise"
        t_line "it to take on"
        t_cont "FALKNER."
        t_para "He's the leader of"
        t_line "VIOLET CITY's GYM."
        t_done )
};
const txt_cmd_s Route31SignText[] = {
    text_start("ROUTE 31"
        t_para "VIOLET CITY -"
        t_line "CHERRYGROVE CITY"
        t_done )
};
const txt_cmd_s DarkCaveSignText[] = {
    text_start("DARK CAVE"
        t_done )
    //db(0, 0) // filler
};
