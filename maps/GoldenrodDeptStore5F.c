#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore5F.h"
//// EVENTS
enum {
    GOLDENRODDEPTSTORE5F_CLERK = 2,
    GOLDENRODDEPTSTORE5F_LASS,
    GOLDENRODDEPTSTORE5F_MIKE,
    GOLDENRODDEPTSTORE5F_POKEFAN_M,
    GOLDENRODDEPTSTORE5F_CARRIE,
    GOLDENRODDEPTSTORE5F_RECEPTIONIST,
};

const Script_fn_t GoldenrodDeptStore5F_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStore5F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, GoldenrodDeptStore5F_MapScripts_CheckIfSunday),
};

const struct MapScripts GoldenrodDeptStore5F_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStore5F_SceneScripts),
    .scene_scripts = GoldenrodDeptStore5F_SceneScripts,

    .callback_count = lengthof(GoldenrodDeptStore5F_MapCallbacks),
    .callbacks = GoldenrodDeptStore5F_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStore5F_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStore5F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &GoldenrodDeptStore5FDirectory),
    bg_event(3, 0, BGEVENT_READ, &GoldenrodDeptStore5FElevatorButton),
};

static const struct WarpEventData GoldenrodDeptStore5F_WarpEvents[] = {
    warp_event(12, 0, GOLDENROD_DEPT_STORE_4F, 1),
    warp_event(15, 0, GOLDENROD_DEPT_STORE_6F, 1),
    warp_event(2, 0, GOLDENROD_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent GoldenrodDeptStore5F_ObjectEvents[] = {
    object_event(8, 5, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore5FClerkScript, -1),
    object_event(3, 6, SPRITE_LASS, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore5FLassScript, -1),
    object_event(6, 3, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Mike, -1),
    object_event(13, 5, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore5FPokefanMScript, -1),
    object_event(9, 1, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Carrie, -1),
    object_event(7, 5, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore5FReceptionistScript, EVENT_GOLDENROD_DEPT_STORE_5F_HAPPINESS_EVENT_LADY),
};

const struct MapEvents GoldenrodDeptStore5F_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStore5F_WarpEvents),
    .warp_events = GoldenrodDeptStore5F_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStore5F_CoordEvents),
    .coord_events = GoldenrodDeptStore5F_CoordEvents,

    .bg_event_count = lengthof(GoldenrodDeptStore5F_BGEvents),
    .bg_events = GoldenrodDeptStore5F_BGEvents,

    .obj_event_count = lengthof(GoldenrodDeptStore5F_ObjectEvents),
    .obj_events = GoldenrodDeptStore5F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore5F.h"

bool GoldenrodDeptStore5F_MapScripts_CheckIfSunday(script_s* s) {
    SCRIPT_BEGIN
    readvar(VAR_WEEKDAY)
    ifequal(SUNDAY, yes)
    disappear(GOLDENRODDEPTSTORE5F_RECEPTIONIST)
    s_endcallback
yes:
    appear(GOLDENRODDEPTSTORE5F_RECEPTIONIST)
    s_endcallback
    SCRIPT_END
}
bool GoldenrodDeptStore5FClerkScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM02_HEADBUTT)
    iftrue(headbutt)
    checkevent(EVENT_GOT_TM08_ROCK_SMASH)
    iftrue(onlyrocksmash)
    goto neither;
headbutt:
    checkevent(EVENT_GOT_TM08_ROCK_SMASH)
    iftrue(both)
    goto onlyheadbutt;
neither:
    pokemart(MARTTYPE_STANDARD, MART_GOLDENROD_5F_1)
    closetext
    s_end
onlyheadbutt:
    pokemart(MARTTYPE_STANDARD, MART_GOLDENROD_5F_2)
    closetext
    s_end
onlyrocksmash:
    pokemart(MARTTYPE_STANDARD, MART_GOLDENROD_5F_3)
    closetext
    s_end
both:
    pokemart(MARTTYPE_STANDARD, MART_GOLDENROD_5F_4)
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStore5FReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    readvar(VAR_WEEKDAY)
    ifnotequal(SUNDAY, EventIsOver)
    checkflag(ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN)
    iftrue(EventIsOver)
    special(GetFirstPokemonHappiness)
    writetext(GoldenrodDeptStore5FReceptionistOhYourMonDotDotDotText)
    promptbutton
    ifgreater(150 - 1, VeryHappy)
    ifgreater(50 - 1, SomewhatHappy)
    goto NotVeryHappy;
VeryHappy:
    writetext(GoldenrodDeptStore5FReceptionistThisMoveShouldBePerfectText)
    promptbutton
    verbosegiveitem(TM_RETURN, 1)
    iffalse(Done)
    setflag(ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN)
    closetext
    s_end
SomewhatHappy:
    writetext(GoldenrodDeptStore5FReceptionistItsAdorableText)
    waitbutton
    closetext
    s_end
NotVeryHappy:
    writetext(GoldenrodDeptStore5FReceptionistItLooksEvilHowAboutThisTMText)
    promptbutton
    verbosegiveitem(TM_FRUSTRATION, 1)
    iffalse(Done)
    setflag(ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN)
    closetext
    s_end
EventIsOver:
    writetext(GoldenrodDeptStore5FReceptionistThereAreTMsPerfectForMonText)
    waitbutton
Done:
    closetext
    s_end
    SCRIPT_END
}
bool Carrie(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    special(GameboyCheck)
    ifnotequal(GBCHECK_CGB, NotGBC) // This is a dummy check from Gold/Silver
    writetext(GoldenrodDeptStore5FCarrieMysteryGiftExplanationText)
    waitbutton
    closetext
    special(UnlockMysteryGift)
    s_end
NotGBC:
    writetext(GoldenrodDeptStore5FCarrieMysteryGiftRequiresGBCText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStore5FLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore5FLassText)
    SCRIPT_END
}
bool Mike(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    trade(NPC_TRADE_MIKE)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStore5FPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore5FPokefanMText)
    SCRIPT_END
}
bool GoldenrodDeptStore5FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodDeptStore5FDirectoryText)
    SCRIPT_END
}
bool GoldenrodDeptStore5FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s GoldenrodDeptStore5FReceptionistOhYourMonDotDotDotText[] = {
    text_start("Hello. Oh, your"
        t_line "#MON…"
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FReceptionistThisMoveShouldBePerfectText[] = {
    text_start("It's very attached"
        t_line "to you."
        t_para "This move should"
        t_line "be perfect for a"
        t_cont "pair like you."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FReceptionistItsAdorableText[] = {
    text_start("It's adorable!"
        t_para "You should teach"
        t_line "it good TM moves."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FReceptionistItLooksEvilHowAboutThisTMText[] = {
    text_start("It looks evil. How"
        t_line "about this TM for"
        t_cont "it?"
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FReceptionistThereAreTMsPerfectForMonText[] = {
    text_start("There are sure to"
        t_line "be TMs that are"
        t_para "just perfect for"
        t_line "your #MON."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FCarrieMysteryGiftExplanationText[] = {
    text_start("MYSTERY GIFT."
        t_para "With just a"
        t_line "little beep, you"
        t_cont "get a gift."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FCarrieMysteryGiftRequiresGBCText[] = {
    text_start("The MYSTERY GIFT"
        t_line "option requires a"
        t_cont "Game Boy Color."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FLassText[] = {
    text_start("On Sundays, a lady"
        t_line "comes to check out"
        t_cont "#MON."
        t_para "She even gives"
        t_line "away TMs!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FPokefanMText[] = {
    text_start("You can't rename a"
        t_line "#MON you get in"
        t_cont "a trade."
        t_para "The name is a re-"
        t_line "flection of the"
        t_para "original trainer's"
        t_line "feelings for it."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore5FDirectoryText[] = {
    text_start("Customize Your"
        t_line "#MON"
        t_para "5F TM CORNER"
        t_done )
    //db(0, 0) // filler
};
