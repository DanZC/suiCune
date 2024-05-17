#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodHappinessRater.h"
//// EVENTS
enum {
    GOLDENRODHAPPINESSRATER_TEACHER = 2,
    GOLDENRODHAPPINESSRATER_POKEFAN_M,
    GOLDENRODHAPPINESSRATER_TWIN,
};

const Script_fn_t GoldenrodHappinessRater_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodHappinessRater_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodHappinessRater_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodHappinessRater_SceneScripts),
    .scene_scripts = GoldenrodHappinessRater_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodHappinessRater_MapCallbacks),
    .callbacks = GoldenrodHappinessRater_MapCallbacks,
};

static const struct CoordEvent GoldenrodHappinessRater_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodHappinessRater_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &HappinessRatersHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &HappinessRatersHouseBookshelf),
    bg_event(7, 1, BGEVENT_READ, &HappinessRatersHouseRadio),
};

static const struct WarpEventData GoldenrodHappinessRater_WarpEvents[] = {
    warp_event(2, 7, GOLDENROD_CITY, 3),
    warp_event(3, 7, GOLDENROD_CITY, 3),
};

static const struct ObjEvent GoldenrodHappinessRater_ObjectEvents[] = {
    object_event(2, 4, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GoldenrodHappinessRaterTeacherScript, -1),
    object_event(5, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodHappinessRaterPokefanMScript, -1),
    object_event(5, 6, SPRITE_TWIN, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodHappinessRaterTwinScript, -1),
};

const struct MapEvents GoldenrodHappinessRater_MapEvents = {
    .warp_event_count = lengthof(GoldenrodHappinessRater_WarpEvents),
    .warp_events = GoldenrodHappinessRater_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodHappinessRater_CoordEvents),
    .coord_events = GoldenrodHappinessRater_CoordEvents,

    .bg_event_count = lengthof(GoldenrodHappinessRater_BGEvents),
    .bg_events = GoldenrodHappinessRater_BGEvents,

    .obj_event_count = lengthof(GoldenrodHappinessRater_ObjectEvents),
    .obj_events = GoldenrodHappinessRater_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodHappinessRater.h"

bool GoldenrodHappinessRaterTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    special(GetFirstPokemonHappiness)
    writetext(GoldenrodHappinessRaterTeacherText)
    promptbutton
    ifgreater(250 - 1, LovesYouALot)
    ifgreater(200 - 1, ReallyTrustsYou)
    ifgreater(150 - 1, SortOfHappy)
    ifgreater(100 - 1, QuiteCute)
    ifgreater(50 - 1, NotUsedToYou)
    goto LooksMean;
LovesYouALot:
    writetext(GoldenrodHappinessRatingText_LovesYouALot)
    waitbutton
    closetext
    s_end
ReallyTrustsYou:
    writetext(GoldenrodHappinessRatingText_ReallyTrustsYou)
    waitbutton
    closetext
    s_end
SortOfHappy:
    writetext(GoldenrodHappinessRatingText_SortOfHappy)
    waitbutton
    closetext
    s_end
QuiteCute:
    writetext(GoldenrodHappinessRatingText_QuiteCute)
    waitbutton
    closetext
    s_end
NotUsedToYou:
    writetext(GoldenrodHappinessRatingText_NotUsedToYou)
    waitbutton
    closetext
    s_end
LooksMean:
    writetext(GoldenrodHappinessRatingText_LooksMean)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodHappinessRaterPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodHappinessRaterPokefanMText)
    SCRIPT_END
}
bool GoldenrodHappinessRaterTwinScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodHappinessRaterTwinText)
    SCRIPT_END
}
bool HappinessRatersHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
bool HappinessRatersHouseRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
    SCRIPT_END
}
const txt_cmd_s GoldenrodHappinessRaterTeacherText[] = {
    text_start("If you treat your"
        t_line "#MON nicely,"
        t_para "they will love you"
        t_line "in return."
        t_para "Oh? Let me see"
        t_line "your @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_done )
};
const txt_cmd_s GoldenrodHappinessRatingText_LovesYouALot[] = {
    text_start("It looks really"
        t_line "happy! It must"
        t_cont "love you a lot."
        t_done )
};
const txt_cmd_s GoldenrodHappinessRatingText_ReallyTrustsYou[] = {
    text_start("I get the feeling"
        t_line "that it really"
        t_cont "trusts you."
        t_done )
};
const txt_cmd_s GoldenrodHappinessRatingText_SortOfHappy[] = {
    text_start("It's friendly to-"
        t_line "ward you. It looks"
        t_cont "sort of happy."
        t_done )
};
const txt_cmd_s GoldenrodHappinessRatingText_QuiteCute[] = {
    text_start("It's quite cute."
        t_done )
};
const txt_cmd_s GoldenrodHappinessRatingText_NotUsedToYou[] = {
    text_start("You should treat"
        t_line "it better. It's"
        t_cont "not used to you."
        t_done )
};
const txt_cmd_s GoldenrodHappinessRatingText_LooksMean[] = {
    text_start("It doesn't seem to"
        t_line "like you at all."
        t_cont "It looks mean."
        t_done )
};
const txt_cmd_s GoldenrodHappinessRaterPokefanMText[] = {
    text_start("I keep losing in"
        t_line "battles, and my"
        t_para "#MON end up"
        t_line "fainting…"
        t_para "Maybe that's why"
        t_line "my #MON don't"
        t_cont "like me much…"
        t_done )
};
const txt_cmd_s GoldenrodHappinessRaterTwinText[] = {
    text_start("When I use an item"
        t_line "on my #MON, it"
        t_cont "acts really glad!"
        t_done )
    //db(0, 0) // filler
};
