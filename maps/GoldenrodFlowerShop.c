#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodFlowerShop.h"
//// EVENTS
enum {
    GOLDENRODFLOWERSHOP_TEACHER = 2,
    GOLDENRODFLOWERSHOP_FLORIA,
};

const Script_fn_t GoldenrodFlowerShop_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodFlowerShop_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodFlowerShop_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodFlowerShop_SceneScripts),
    .scene_scripts = GoldenrodFlowerShop_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodFlowerShop_MapCallbacks),
    .callbacks = GoldenrodFlowerShop_MapCallbacks,
};

static const struct CoordEvent GoldenrodFlowerShop_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodFlowerShop_BGEvents[] = {
    0,
};

static const struct WarpEventData GoldenrodFlowerShop_WarpEvents[] = {
    warp_event(2, 7, GOLDENROD_CITY, 6),
    warp_event(3, 7, GOLDENROD_CITY, 6),
};

static const struct ObjEvent GoldenrodFlowerShop_ObjectEvents[] = {
    object_event(2, 4, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FlowerShopTeacherScript, -1),
    object_event(5, 6, SPRITE_LASS, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &FlowerShopFloriaScript, EVENT_FLORIA_AT_FLOWER_SHOP),
};

const struct MapEvents GoldenrodFlowerShop_MapEvents = {
    .warp_event_count = lengthof(GoldenrodFlowerShop_WarpEvents),
    .warp_events = GoldenrodFlowerShop_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodFlowerShop_CoordEvents),
    .coord_events = GoldenrodFlowerShop_CoordEvents,

    .bg_event_count = 0, // lengthof(GoldenrodFlowerShop_BGEvents),
    .bg_events = GoldenrodFlowerShop_BGEvents,

    .obj_event_count = lengthof(GoldenrodFlowerShop_ObjectEvents),
    .obj_events = GoldenrodFlowerShop_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodFlowerShop.h"

bool FlowerShopTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOUGHT_SUDOWOODO)
    iftrue(Lalala)
    checkevent(EVENT_GOT_SQUIRTBOTTLE)
    iftrue(GotSquirtbottle)
    checkevent(EVENT_MET_FLORIA)
    iffalse(HaventMetFloria)
    checkevent(EVENT_TALKED_TO_FLORIA_AT_FLOWER_SHOP)
    iffalse(Lalala)
    checkflag(ENGINE_PLAINBADGE)
    iffalse(NoPlainBadge)
    faceplayer
    opentext
    writetext(GoldenrodFlowerShopTeacherHeresTheSquirtbottleText)
    promptbutton
    verbosegiveitem(SQUIRTBOTTLE, 1)
    setevent(EVENT_GOT_SQUIRTBOTTLE)
    closetext
    setevent(EVENT_FLORIA_AT_SUDOWOODO)
    clearevent(EVENT_FLORIA_AT_FLOWER_SHOP)
    s_end
Lalala:
    turnobject(GOLDENRODFLOWERSHOP_TEACHER, LEFT)
    opentext
    writetext(GoldenrodFlowerShopTeacherLalalaHavePlentyOfWaterText)
    waitbutton
    closetext
    s_end
GotSquirtbottle:
    jumptextfaceplayer(GoldenrodFlowerShopTeacherDontDoAnythingDangerousText)
NoPlainBadge:
    jumptextfaceplayer(GoldenrodFlowerShopTeacherAskWantToBorrowWaterBottleText)
HaventMetFloria:
    jumptextfaceplayer(GoldenrodFlowerShopTeacherMySisterWentToSeeWigglyTreeRoute36Text)
    SCRIPT_END
}
bool FlowerShopFloriaScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FOUGHT_SUDOWOODO)
    iftrue(FoughtSudowoodo)
    checkevent(EVENT_GOT_SQUIRTBOTTLE)
    iftrue(GotSquirtbottle)
    writetext(GoldenrodFlowerShopFloriaWonderIfSisWillLendWaterBottleText)
    waitbutton
    closetext
    setevent(EVENT_TALKED_TO_FLORIA_AT_FLOWER_SHOP)
    setevent(EVENT_FLORIA_AT_FLOWER_SHOP)
    clearevent(EVENT_FLORIA_AT_SUDOWOODO)
    s_end
GotSquirtbottle:
    writetext(GoldenrodFlowerShopFloriaYouBeatWhitneyText)
    waitbutton
    closetext
    s_end
FoughtSudowoodo:
    writetext(GoldenrodFlowerShopFloriaItReallyWasAMonText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FlowerShopShelf1(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
bool FlowerShopShelf2(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
bool FlowerShopRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
    SCRIPT_END
}
const txt_cmd_s GoldenrodFlowerShopTeacherMySisterWentToSeeWigglyTreeRoute36Text[] = {
    text_start("Have you seen that"
        t_line "wiggly tree that's"
        t_para "growing on ROUTE"
        t_line "36?"
        t_para "My little sister"
        t_line "got all excited"
        t_para "and went to see"
        t_line "it…"
        t_para "I'm worried… Isn't"
        t_line "it dangerous?"
        t_done )
};
const txt_cmd_s GoldenrodFlowerShopTeacherAskWantToBorrowWaterBottleText[] = {
    text_start("Do you want to"
        t_line "borrow the water"
        t_para "bottle too?"
        t_line "I don't want you"
        t_para "doing anything"
        t_line "dangerous with it."
        t_done )
};
const txt_cmd_s GoldenrodFlowerShopTeacherHeresTheSquirtbottleText[] = {
    text_start("Oh, you're better"
        t_line "than WHITNEY…"
        t_para "You'll be OK,"
        t_line "then. Here's the"
        t_cont "SQUIRTBOTTLE!"
        t_done )
};
const txt_cmd_s GoldenrodFlowerShopTeacherDontDoAnythingDangerousText[] = {
    text_start("Don't do anything"
        t_line "too dangerous!"
        t_done )
};
const txt_cmd_s GoldenrodFlowerShopTeacherLalalaHavePlentyOfWaterText[] = {
    text_start("Lalala lalalala."
        t_line "Have plenty of"
        t_cont "water, my lovely!"
        t_done )
};
const txt_cmd_s GoldenrodFlowerShopFloriaWonderIfSisWillLendWaterBottleText[] = {
    text_start("When I told my sis"
        t_line "about the jiggly"
        t_para "tree, she told me"
        t_line "it's dangerous."
        t_para "If I beat WHITNEY,"
        t_line "I wonder if she'll"
        t_para "lend me her water"
        t_line "bottle…"
        t_done )
};
const txt_cmd_s GoldenrodFlowerShopFloriaYouBeatWhitneyText[] = {
    text_start("Wow, you beat"
        t_line "WHITNEY? Cool!"
        t_done )
};
const txt_cmd_s GoldenrodFlowerShopFloriaItReallyWasAMonText[] = {
    text_start("So it really was a"
        t_line "#MON!"
        t_done )
    //db(0, 0) // filler
};
