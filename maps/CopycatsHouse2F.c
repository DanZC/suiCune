#include "../constants.h"
#include "../util/scripting.h"
#include "CopycatsHouse2F.h"
//// EVENTS
enum {
    COPYCATSHOUSE2F_COPYCAT1 = 2, // if player is male
    COPYCATSHOUSE2F_DODRIO,
    COPYCATSHOUSE2F_FAIRYDOLL, // lost item
    COPYCATSHOUSE2F_MONSTERDOLL,
    COPYCATSHOUSE2F_BIRDDOLL,
    COPYCATSHOUSE2F_COPYCAT2, // if player is female
};

const Script_fn_t CopycatsHouse2F_SceneScripts[] = {
    0,
};

const struct MapCallback CopycatsHouse2F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, CopycatsHouse2F_MapScripts_Callback),
};

const struct MapScripts CopycatsHouse2F_MapScripts = {
    .scene_script_count = 0, // lengthof(CopycatsHouse2F_SceneScripts),
    .scene_scripts = CopycatsHouse2F_SceneScripts,

    .callback_count = lengthof(CopycatsHouse2F_MapCallbacks),
    .callbacks = CopycatsHouse2F_MapCallbacks,
};

static const struct CoordEvent CopycatsHouse2F_CoordEvents[] = {
    0,
};

static const struct BGEvent CopycatsHouse2F_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &CopycatsHouse2FBookshelf),
    bg_event(1, 1, BGEVENT_READ, &CopycatsHouse2FBookshelf),
};

static const struct WarpEventData CopycatsHouse2F_WarpEvents[] = {
    warp_event(3, 0, COPYCATS_HOUSE_1F, 3),
};

static const struct ObjEvent CopycatsHouse2F_ObjectEvents[] = {
    object_event(4, 3, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Copycat, EVENT_COPYCAT_1),
    object_event(6, 4, SPRITE_MOLTRES, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &CopycatsDodrio, -1),
    object_event(6, 1, SPRITE_FAIRY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CopycatsHouse2FDoll, EVENT_COPYCATS_HOUSE_2F_DOLL),
    object_event(2, 1, SPRITE_MONSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CopycatsHouse2FDoll, -1),
    object_event(7, 1, SPRITE_BIRD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CopycatsHouse2FDoll, -1),
    object_event(4, 3, SPRITE_COPYCAT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Copycat, EVENT_COPYCAT_2),
};

const struct MapEvents CopycatsHouse2F_MapEvents = {
    .warp_event_count = lengthof(CopycatsHouse2F_WarpEvents),
    .warp_events = CopycatsHouse2F_WarpEvents,

    .coord_event_count = 0, // lengthof(CopycatsHouse2F_CoordEvents),
    .coord_events = CopycatsHouse2F_CoordEvents,

    .bg_event_count = lengthof(CopycatsHouse2F_BGEvents),
    .bg_events = CopycatsHouse2F_BGEvents,

    .obj_event_count = lengthof(CopycatsHouse2F_ObjectEvents),
    .obj_events = CopycatsHouse2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CopycatsHouse2F.h"

bool CopycatsHouse2F_MapScripts_Callback(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Female)
    disappear(COPYCATSHOUSE2F_COPYCAT2)
    appear(COPYCATSHOUSE2F_COPYCAT1)
    goto Done;
Female:
    disappear(COPYCATSHOUSE2F_COPYCAT1)
    appear(COPYCATSHOUSE2F_COPYCAT2)
Done:
    s_endcallback
    SCRIPT_END
}
bool Copycat(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    checkevent(EVENT_GOT_PASS_FROM_COPYCAT)
    iftrue(GotPass)
    checkevent(EVENT_RETURNED_LOST_ITEM_TO_COPYCAT)
    iftrue(TryGivePassAgain)
    checkitem(LOST_ITEM)
    iftrue(ReturnLostItem)
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Default_Female_1)
    applymovement(COPYCATSHOUSE2F_COPYCAT1, CopycatSpinAroundMovementData)
    faceplayer
    variablesprite(SPRITE_COPYCAT, SPRITE_CHRIS)
    goto Default_Merge_1;
Default_Female_1:
    applymovement(COPYCATSHOUSE2F_COPYCAT2, CopycatSpinAroundMovementData)
    faceplayer
    variablesprite(SPRITE_COPYCAT, SPRITE_KRIS)
Default_Merge_1:
    special(LoadUsedSpritesGFX)
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(TalkAboutLostItem)
    opentext
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Default_Female_2a)
    writetext(CopycatText_Male_1)
    goto Default_Merge_2a;
Default_Female_2a:
    writetext(CopycatText_Female_1)
Default_Merge_2a:
    waitbutton
    closetext
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Default_Female_3a)
    applymovement(COPYCATSHOUSE2F_COPYCAT1, CopycatSpinAroundMovementData)
    goto Default_Merge_3a;
Default_Female_3a:
    applymovement(COPYCATSHOUSE2F_COPYCAT2, CopycatSpinAroundMovementData)
Default_Merge_3a:
    faceplayer
    variablesprite(SPRITE_COPYCAT, SPRITE_LASS)
    special(LoadUsedSpritesGFX)
    opentext
    writetext(CopycatText_QuickMimicking)
    waitbutton
    closetext
    s_end
TalkAboutLostItem:
    opentext
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Default_Female_2b)
    writetext(CopycatText_Male_2)
    goto Default_Merge_2b;
Default_Female_2b:
    writetext(CopycatText_Female_2)
Default_Merge_2b:
    waitbutton
    closetext
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(Default_Female_3b)
    applymovement(COPYCATSHOUSE2F_COPYCAT1, CopycatSpinAroundMovementData)
    goto Default_Merge_3b;
Default_Female_3b:
    applymovement(COPYCATSHOUSE2F_COPYCAT2, CopycatSpinAroundMovementData)
Default_Merge_3b:
    faceplayer
    variablesprite(SPRITE_COPYCAT, SPRITE_LASS)
    special(LoadUsedSpritesGFX)
    opentext
    writetext(CopycatText_Worried)
    waitbutton
    closetext
    setevent(EVENT_MET_COPYCAT_FOUND_OUT_ABOUT_LOST_ITEM)
    s_end
ReturnLostItem:
    opentext
    writetext(CopycatText_GiveDoll)
    promptbutton
    takeitem(LOST_ITEM, 1)
    setevent(EVENT_RETURNED_LOST_ITEM_TO_COPYCAT)
    clearevent(EVENT_COPYCATS_HOUSE_2F_DOLL)
    goto GivePass;
TryGivePassAgain:
    opentext
GivePass:
    writetext(CopycatText_GivePass)
    promptbutton
    verbosegiveitem(PASS, 1)
    iffalse(Cancel)
    setevent(EVENT_GOT_PASS_FROM_COPYCAT)
    writetext(CopycatText_ExplainPass)
    waitbutton
    closetext
    s_end
GotPass:
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(GotPass_Female_1)
    applymovement(COPYCATSHOUSE2F_COPYCAT1, CopycatSpinAroundMovementData)
    faceplayer
    variablesprite(SPRITE_COPYCAT, SPRITE_CHRIS)
    goto GotPass_Merge_1;
GotPass_Female_1:
    applymovement(COPYCATSHOUSE2F_COPYCAT2, CopycatSpinAroundMovementData)
    faceplayer
    variablesprite(SPRITE_COPYCAT, SPRITE_KRIS)
GotPass_Merge_1:
    special(LoadUsedSpritesGFX)
    opentext
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(GotPass_Female_2)
    writetext(CopycatText_Male_3)
    goto GotPass_Merge_2;
GotPass_Female_2:
    writetext(CopycatText_Female_3)
GotPass_Merge_2:
    waitbutton
    closetext
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(GotPass_Female_3)
    applymovement(COPYCATSHOUSE2F_COPYCAT1, CopycatSpinAroundMovementData)
    goto GotPass_Merge_3;
GotPass_Female_3:
    applymovement(COPYCATSHOUSE2F_COPYCAT2, CopycatSpinAroundMovementData)
GotPass_Merge_3:
    faceplayer
    variablesprite(SPRITE_COPYCAT, SPRITE_LASS)
    special(LoadUsedSpritesGFX)
    opentext
    writetext(CopycatText_ItsAScream)
    waitbutton
Cancel:
    closetext
    s_end
    SCRIPT_END
}
bool CopycatsDodrio(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CopycatsDodrioText1)
    playcry(DODRIO)
    promptbutton
    writetext(CopycatsDodrioText2)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CopycatsHouse2FDoll(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CopycatsHouse2FDollText)
    SCRIPT_END
}
bool CopycatsHouse2FBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const uint8_t CopycatSpinAroundMovementData[] = {
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    turn_head(LEFT),
    turn_head(UP),
    turn_head(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s CopycatText_Male_1[] = {
    text_start("<PLAYER>: Hi! Do"
        t_line "you like #MON?"
        t_para "<PLAYER>: Uh, no, I"
        t_line "just asked you."
        t_para "<PLAYER>: Huh?"
        t_line "You're strange!"
        t_done )
};
const txt_cmd_s CopycatText_QuickMimicking[] = {
    text_start("COPYCAT: Hmm?"
        t_line "Quit mimicking?"
        t_para "But that's my"
        t_line "favorite hobby!"
        t_done )
};
const txt_cmd_s CopycatText_Male_2[] = {
    text_start("<PLAYER>: Hi!"
        t_line "I heard that you"
        t_para "lost your favorite"
        t_line "# DOLL."
        t_para "<PLAYER>: If I find"
        t_line "it, you'll give me"
        t_cont "a rail PASS?"
        t_para "<PLAYER>: I'll go"
        t_line "find it for you."
        t_para "You think you lost"
        t_line "it when you went"
        t_cont "to VERMILION CITY?"
        t_done )
};
const txt_cmd_s CopycatText_Worried[] = {
    text_start("COPYCAT: Pardon?"
        t_para "I shouldn't decide"
        t_line "what you should"
        t_cont "do?"
        t_para "But I'm really"
        t_line "worried… What if"
        t_cont "someone finds it?"
        t_done )
};
const txt_cmd_s CopycatText_GiveDoll[] = {
    text_start("COPYCAT: Yay!"
        t_line "That's my CLEFAIRY"
        t_cont "# DOLL!"
        t_para "See the tear where"
        t_line "the right leg is"
        t_para "sewn on? That's"
        t_line "proof!"
        t_done )
};
const txt_cmd_s CopycatText_GivePass[] = {
    text_start("OK. Here's the"
        t_line "MAGNET TRAIN PASS"
        t_cont "like I promised!"
        t_done )
};
const txt_cmd_s CopycatText_ExplainPass[] = {
    text_start("COPYCAT: That's"
        t_line "the PASS for the"
        t_cont "MAGNET TRAIN."
        t_para "The rail company"
        t_line "man gave me that"
        t_para "when they tore"
        t_line "down our old house"
        t_cont "for the STATION."
        t_done )
};
const txt_cmd_s CopycatText_Male_3[] = {
    text_start("<PLAYER>: Hi!"
        t_line "Thanks a lot for"
        t_cont "the rail PASS!"
        t_para "<PLAYER>: Pardon?"
        t_para "<PLAYER>: Is it"
        t_line "that fun to mimic"
        t_cont "my every move?"
        t_done )
};
const txt_cmd_s CopycatText_ItsAScream[] = {
    text_start("COPYCAT: You bet!"
        t_line "It's a scream!"
        t_done )
};
const txt_cmd_s CopycatText_Female_1[] = {
    text_start("<PLAYER>: Hi. You"
        t_line "must like #MON."
        t_para "<PLAYER>: No, not"
        t_line "me. I asked you."
        t_para "<PLAYER>: Pardon?"
        t_line "You're weird!"
        t_done )
};
const txt_cmd_s CopycatText_Female_2[] = {
    text_start("<PLAYER>: Hi. Did"
        t_line "you really lose"
        t_cont "your # DOLL?"
        t_para "<PLAYER>: You'll"
        t_line "really give me a"
        t_para "rail PASS if I"
        t_line "find it for you?"
        t_para "<PLAYER>: Sure,"
        t_line "I'll look for it!"
        t_para "You think you lost"
        t_line "it when you were"
        t_cont "in VERMILION?"
        t_done )
};
const txt_cmd_s CopycatText_Female_3[] = {
    text_start("<PLAYER>: Thank you"
        t_line "for the rail PASS!"
        t_para "<PLAYER>: …Pardon?"
        t_para "<PLAYER>: Is it"
        t_line "really that fun to"
        t_para "copy what I say"
        t_line "and do?"
        t_done )
};
const txt_cmd_s CopycatsDodrioText1[] = {
    text_start("DODRIO: Gii giii!"
        t_done )
};
const txt_cmd_s CopycatsDodrioText2[] = {
    text_start("MIRROR, MIRROR ON"
        t_line "THE WALL, WHO'S"
        t_para "THE FAIREST ONE OF"
        t_line "ALL?"
        t_done )
};
const txt_cmd_s CopycatsHouse2FDollText[] = {
    text_start("This is a rare"
        t_line "#MON! Huh?"
        t_para "It's only a doll…"
        t_done )
    //db(0, 0) // filler
};
