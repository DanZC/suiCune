#include "../constants.h"
#include "../util/scripting.h"
#include "Route35GoldenrodGate.h"
//// EVENTS
enum {
    ROUTE35GOLDENRODGATE_RANDY = 2,
    ROUTE35GOLDENRODGATE_POKEFAN_F,
    ROUTE35GOLDENRODGATE_FISHER,
};

const Script_fn_t Route35GoldenrodGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route35GoldenrodGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route35GoldenrodGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route35GoldenrodGate_SceneScripts),
    .scene_scripts = Route35GoldenrodGate_SceneScripts,

    .callback_count = 0, // lengthof(Route35GoldenrodGate_MapCallbacks),
    .callbacks = Route35GoldenrodGate_MapCallbacks,
};

static const struct CoordEvent Route35GoldenrodGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route35GoldenrodGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route35GoldenrodGate_WarpEvents[] = {
    warp_event(4, 0, ROUTE_35, 1),
    warp_event(5, 0, ROUTE_35, 2),
    warp_event(4, 7, GOLDENROD_CITY, 12),
    warp_event(5, 7, GOLDENROD_CITY, 12),
};

static const struct ObjEvent Route35GoldenrodGate_ObjectEvents[] = {
    object_event(0, 4, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RandyScript, -1),
    object_event(6, 4, SPRITE_POKEFAN_F, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route35GoldenrodGatePokefanFScript, -1),
    object_event(3, 2, SPRITE_FISHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route35GoldenrodGateFisherScript, -1),
};

const struct MapEvents Route35GoldenrodGate_MapEvents = {
    .warp_event_count = lengthof(Route35GoldenrodGate_WarpEvents),
    .warp_events = Route35GoldenrodGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route35GoldenrodGate_CoordEvents),
    .coord_events = Route35GoldenrodGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route35GoldenrodGate_BGEvents),
    .bg_events = Route35GoldenrodGate_BGEvents,

    .obj_event_count = lengthof(Route35GoldenrodGate_ObjectEvents),
    .obj_events = Route35GoldenrodGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route35GoldenrodGate.h"

bool RandyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_HP_UP_FROM_RANDY)
    iftrue(gothpup)
    checkevent(EVENT_GAVE_KENYA)
    iftrue(questcomplete)
    checkevent(EVENT_GOT_KENYA)
    iftrue(alreadyhavekenya)
    writetext(Route35GoldenrodGateRandyAskTakeThisMonToMyFriendText)
    yesorno
    iffalse(refused)
    writetext(Route35GoldenrodGateRandyThanksText)
    promptbutton
    waitsfx
    readvar(VAR_PARTYCOUNT)
    ifequal(PARTY_LENGTH, partyfull)
    writetext(Route35GoldenrodGatePlayerReceivedAMonWithMailText)
    playsound(SFX_KEY_ITEM)
    waitsfx
    givepokeext(SPEAROW, 10, NO_ITEM, GiftSpearowName, GiftSpearowOTName)
    givepokemail(&GiftSpearowMail)
    setevent(EVENT_GOT_KENYA)
alreadyhavekenya:
    writetext(Route35GoldenrodGateRandyWeirdTreeBlockingRoadText)
    waitbutton
    closetext
    s_end
partyfull:
    writetext(Route35GoldenrodGateRandyCantCarryAnotherMonText)
    waitbutton
    closetext
    s_end
refused:
    writetext(Route35GoldenrodGateRandyOhNeverMindThenText)
    waitbutton
    closetext
    s_end
questcomplete:
    writetext(Route35GoldenrodGateRandySomethingForYourTroubleText)
    promptbutton
    verbosegiveitem(HP_UP, 1)
    iffalse(bagfull)
    setevent(EVENT_GOT_HP_UP_FROM_RANDY)
gothpup:
    writetext(Route35GoldenrodGateRandyMyPalWasSnoozingRightText)
    waitbutton
bagfull:
    closetext
    s_end
    SCRIPT_END
}
const struct Pokemail GiftSpearowMail = {
    .item = FLOWER_MAIL,
    .message = "DARK CAVE leads"
        t_next "to another road@"
};
const char GiftSpearowName[] = "KENYA@";
const char GiftSpearowOTName[] = "RANDY@";
    //db(0) // unused
bool Route35GoldenrodGatePokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FOUGHT_SUDOWOODO)
    iftrue(FoughtSudowoodo)
    writetext(Route35GoldenrodGatePokefanFText)
    waitbutton
    closetext
    s_end
FoughtSudowoodo:
    writetext(Route35GoldenrodGatePokefanFText_FoughtSudowoodo)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route35GoldenrodGateFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route35GoldenrodGateFisherText)
    SCRIPT_END
}
const txt_cmd_s Route35GoldenrodGateRandyAskTakeThisMonToMyFriendText[] = {
    text_start("Excuse me, kid!"
        t_line "Can you do a guy"
        t_cont "a favor?"
        t_para "Can you take this"
        t_line "#MON with MAIL"
        t_cont "to my friend?"
        t_para "He's on ROUTE 31."
        t_done )
};
const txt_cmd_s Route35GoldenrodGateRandyThanksText[] = {
    text_start("You will? Perfect!"
        t_line "Thanks, kid!"
        t_para "My pal's a chubby"
        t_line "guy who snoozes"
        t_cont "all the time."
        t_para "You'll recognize"
        t_line "him right away!"
        t_done )
};
const txt_cmd_s Route35GoldenrodGatePlayerReceivedAMonWithMailText[] = {
    text_start("<PLAYER> received a"
        t_line "#MON with MAIL."
        t_done )
};
const txt_cmd_s Route35GoldenrodGateRandyWeirdTreeBlockingRoadText[] = {
    text_start("You can read it,"
        t_line "but don't lose it!"
        t_cont "ROUTE 31!"
        t_para "Oh, yeah. There"
        t_line "was a weird tree"
        t_cont "blocking the road."
        t_para "I wonder if it's"
        t_line "been cleared?"
        t_done )
};
const txt_cmd_s Route35GoldenrodGateRandyCantCarryAnotherMonText[] = {
    text_start("You can't carry"
        t_line "another #MON…"
        t_done )
};
const txt_cmd_s Route35GoldenrodGateRandyOhNeverMindThenText[] = {
    text_start("Oh… Never mind,"
        t_line "then…"
        t_done )
};
const txt_cmd_s Route35GoldenrodGateRandySomethingForYourTroubleText[] = {
    text_start("Thanks, kid! You"
        t_line "made the delivery"
        t_cont "for me!"
        t_para "Here's something"
        t_line "for your trouble!"
        t_done )
};
const txt_cmd_s Route35GoldenrodGateRandyMyPalWasSnoozingRightText[] = {
    text_start("My pal was snooz-"
        t_line "ing, right? Heh,"
        t_cont "what'd I say?"
        t_done )
};
const txt_cmd_s Route35GoldenrodGatePokefanFText[] = {
    text_start("A strange tree is"
        t_line "blocking the road."
        t_para "It wriggles around"
        t_line "if you talk to it."
        t_para "I heard it became"
        t_line "wild when someone"
        t_para "watered it with a"
        t_line "SQUIRTBOTTLE."
        t_done )
};
const txt_cmd_s Route35GoldenrodGatePokefanFText_FoughtSudowoodo[] = {
    text_start("I like the #MON"
        t_line "Lullaby they play"
        t_cont "on the radio."
        t_done )
};
const txt_cmd_s Route35GoldenrodGateFisherText[] = {
    text_start("I wonder how many"
        t_line "kinds of #MON"
        t_para "there are in the"
        t_line "world."
        t_para "Three years ago,"
        t_line "PROF.OAK said that"
        t_para "there were 150"
        t_line "different kinds."
        t_done )
    //db(0, 0) // filler
};
