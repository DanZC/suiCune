#include "../constants.h"
#include "../util/scripting.h"
#include "WiseTriosRoom.h"
//// EVENTS
enum {
    WISETRIOSROOM_SAGE1 = 2,
    WISETRIOSROOM_SAGE2,
    WISETRIOSROOM_SAGE3,
    WISETRIOSROOM_SAGE4,
    WISETRIOSROOM_SAGE5,
    WISETRIOSROOM_SAGE6,
};

const Script_fn_t WiseTriosRoom_SceneScripts[] = {
    WiseTriosRoom_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    WiseTriosRoom_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback WiseTriosRoom_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, WiseTriosRoom_MapScripts_WiseTrioCallback),
};

const struct MapScripts WiseTriosRoom_MapScripts = {
    .scene_script_count = lengthof(WiseTriosRoom_SceneScripts),
    .scene_scripts = WiseTriosRoom_SceneScripts,

    .callback_count = lengthof(WiseTriosRoom_MapCallbacks),
    .callbacks = WiseTriosRoom_MapCallbacks,
};

static const struct CoordEvent WiseTriosRoom_CoordEvents[] = {
    coord_event(7, 4, SCENE_DEFAULT, &WiseTriosRoom_CannotEnterTinTowerScript),
};

static const struct BGEvent WiseTriosRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData WiseTriosRoom_WarpEvents[] = {
    warp_event(7, 4, ECRUTEAK_CITY, 4),
    warp_event(7, 5, ECRUTEAK_CITY, 5),
    warp_event(1, 4, ECRUTEAK_TIN_TOWER_ENTRANCE, 5),
};

static const struct ObjEvent WiseTriosRoom_ObjectEvents[] = {
    object_event(6, 2, SPRITE_SAGE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &WiseTriosRoomSage1Script, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_1),
    object_event(6, 7, SPRITE_SAGE, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &WiseTriosRoomSage2Script, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_1),
    object_event(7, 5, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &WiseTriosRoomSage3Script, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_1),
    object_event(4, 2, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 2, &TrainerSageGaku, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2),
    object_event(4, 6, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 2, &TrainerSageMasa, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2),
    object_event(6, 4, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 2, &TrainerSageKoji, EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2),
};

const struct MapEvents WiseTriosRoom_MapEvents = {
    .warp_event_count = lengthof(WiseTriosRoom_WarpEvents),
    .warp_events = WiseTriosRoom_WarpEvents,

    .coord_event_count = lengthof(WiseTriosRoom_CoordEvents),
    .coord_events = WiseTriosRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(WiseTriosRoom_BGEvents),
    .bg_events = WiseTriosRoom_BGEvents,

    .obj_event_count = lengthof(WiseTriosRoom_ObjectEvents),
    .obj_events = WiseTriosRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "WiseTriosRoom.h"

bool WiseTriosRoom_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool WiseTriosRoom_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool WiseTriosRoom_MapScripts_WiseTrioCallback(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOUGHT_SUICUNE)
    iftrue(NoWiseTrio)
    checkevent(EVENT_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER)
    iftrue(WiseTrio2)
    checkitem(CLEAR_BELL)
    iftrue(WiseTrio2)
    clearevent(EVENT_WISE_TRIOS_ROOM_WISE_TRIO_1)
    setevent(EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2)
    s_endcallback
WiseTrio2:
    setevent(EVENT_WISE_TRIOS_ROOM_WISE_TRIO_1)
    clearevent(EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2)
    s_endcallback
NoWiseTrio:
    setevent(EVENT_WISE_TRIOS_ROOM_WISE_TRIO_1)
    setevent(EVENT_WISE_TRIOS_ROOM_WISE_TRIO_2)
    s_endcallback
    SCRIPT_END
}
bool WiseTriosRoomSage1Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(WiseTriosRoomSage1Text)
    SCRIPT_END
}
bool WiseTriosRoomSage2Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(WiseTriosRoomSage2Text)
    SCRIPT_END
}
bool WiseTriosRoomSage3Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(WiseTriosRoomSage3Text)
    SCRIPT_END
}
bool WiseTriosRoom_CannotEnterTinTowerScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(WISETRIOSROOM_SAGE3, UP)
    turnobject(PLAYER, DOWN)
    showemote(EMOTE_SHOCK, WISETRIOSROOM_SAGE3, 20)
    follow(PLAYER, WISETRIOSROOM_SAGE3)
    applymovement(PLAYER, WiseTriosRoomSageBlocksPlayerMovement)
    stopfollow
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(WiseTriosRoomSage3BlocksExitText)
    waitbutton
    closetext
    applymovement(WISETRIOSROOM_SAGE3, WiseTriosRoomSageReturnsMovement)
    turnobject(WISETRIOSROOM_SAGE3, LEFT)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSageGaku = {SAGE, GAKU, EVENT_BEAT_SAGE_GAKU, SageGakuSeenText, SageGakuBeatenText, 0, TrainerSageGaku_Script};
bool TrainerSageGaku_Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(SageGakuAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSageMasa = {SAGE, MASA, EVENT_BEAT_SAGE_MASA, SageMasaSeenText, SageMasaBeatenText, 0, TrainerSageMasa_Script};
bool TrainerSageMasa_Script(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(SageMasaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSageKoji = {SAGE, KOJI, EVENT_BEAT_SAGE_KOJI, SageKojiSeenText, SageKojiBeatenText, 0, TrainerSageKoji_Script};
bool TrainerSageKoji_Script(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER)
    iftrue(KojiAllowsPassage)
    pause(10)
    showemote(EMOTE_SHOCK, WISETRIOSROOM_SAGE6, 20)
    opentext
    writetext(SageKojiAfterBattleQuestionText)
    promptbutton
    writetext(SageKojiAfterBattleSpeechText)
    waitbutton
    closetext
    applymovement(WISETRIOSROOM_SAGE6, WiseTriosRoomSageAllowsPassageMovement)
    turnobject(WISETRIOSROOM_SAGE6, UP)
    setevent(EVENT_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER)
    setscene(SCENE_FINISHED)
    s_end
KojiAllowsPassage:
    opentext
    writetext(SageKojiAfterBattleFinalText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const uint8_t WiseTriosRoomSageBlocksPlayerMovement[] = {
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t WiseTriosRoomSageReturnsMovement[] = {
    step(RIGHT),
    step(DOWN),
    movement_step_end,
};
const uint8_t WiseTriosRoomSageAllowsPassageMovement[] = {
    step(RIGHT),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s WiseTriosRoomSage1Text[] = {
    text_start("Astounding…"
        t_para "SUICUNE, ENTEI and"
        t_line "RAIKOU have arisen"
        t_cont "from their sleep…"
        t_para "Is the legend"
        t_line "coming true?"
        t_done )
};
const txt_cmd_s WiseTriosRoomSage2Text[] = {
    text_start("We train at the"
        t_line "BURNED TOWER, but"
        t_para "we've never heard"
        t_line "of a hole opening"
        t_para "up there before."
        t_line "It must have been"
        t_para "deliberately made"
        t_line "by someone."
        t_done )
};
const txt_cmd_s WiseTriosRoomSage3BlocksExitText[] = {
    text_start("TIN TOWER may be"
        t_line "entered by those"
        t_para "bearing ECRUTEAK's"
        t_line "GYM BADGE."
        t_para "However, now that"
        t_line "SUICUNE, RAIKOU"
        t_para "and ENTEI have"
        t_line "arisen, I ask you"
        t_para "to refrain from"
        t_line "entering!"
        t_done )
};
const txt_cmd_s WiseTriosRoomSage3Text[] = {
    text_start("We, the WISE TRIO,"
        t_line "are the protectors"
        t_para "of the legendary"
        t_line "#MON."
        t_done )
};
const txt_cmd_s SageGakuSeenText[] = {
    text_start("Legend has it that"
        t_line "upon the emergence"
        t_para "of a trainer who"
        t_line "has the ability to"
        t_para "touch the souls of"
        t_line "#MON, a #MON"
        t_para "will come forth to"
        t_line "put that trainer"
        t_para "to test at the TIN"
        t_line "TOWER."
        t_para "The legend has"
        t_line "come true!"
        t_para "The legendary"
        t_line "#MON SUICUNE"
        t_cont "has arrived!"
        t_para "We, the WISE TRIO,"
        t_line "shall test your"
        t_para "worthiness to go"
        t_line "inside!"
        t_done )
};
const txt_cmd_s SageGakuBeatenText[] = {
    text_start("Stronger than we"
        t_line "thought? Perhaps…"
        t_done )
};
const txt_cmd_s SageGakuAfterBattleText[] = {
    text_start("Ah, so it is you"
        t_line "who claim to have"
        t_para "seen SUICUNE,"
        t_line "ENTEI and RAIKOU"
        t_cont "while they slept?"
        t_para "Unbelievable!"
        t_para "Legend has it that"
        t_line "they can't be seen"
        t_cont "while they sleep…"
        t_done )
};
const txt_cmd_s SageMasaSeenText[] = {
    text_start("Can you be trusted"
        t_line "with the truth?"
        t_para "I must ascertain"
        t_line "your worthiness."
        t_done )
};
const txt_cmd_s SageMasaBeatenText[] = {
    text_start("…I will tell you"
        t_line "the truth…"
        t_done )
};
const txt_cmd_s SageMasaAfterBattleText[] = {
    text_start("In the past, there"
        t_line "were two nine-tier"
        t_cont "towers here."
        t_para "The BRASS TOWER,"
        t_line "which was said to"
        t_para "awaken #MON,"
        t_line "and the TIN TOWER,"
        t_para "where #MON were"
        t_line "said to rest."
        t_para "The view from the"
        t_line "tops of the TOWERS"
        t_para "must have been"
        t_line "magnificent."
        t_para "At the time, an"
        t_line "immense, silver-"
        t_para "colored #MON"
        t_line "was said to make"
        t_para "its roost atop the"
        t_line "BRASS TOWER."
        t_para "However…"
        t_para "About 150 years"
        t_line "ago, a lightning"
        t_para "bolt struck one of"
        t_line "the TOWERS."
        t_para "It was engulfed in"
        t_line "flames that raged"
        t_cont "for three days."
        t_para "A sudden downpour"
        t_line "finally put out"
        t_cont "the blaze."
        t_para "And that is how"
        t_line "the BURNED TOWER"
        t_cont "came to be."
        t_done )
};
const txt_cmd_s SageKojiSeenText[] = {
    text_start("Let me see your"
        t_line "power!"
        t_done )
};
const txt_cmd_s SageKojiBeatenText[] = {
    text_start("Too strong!"
        t_line "Why?"
        t_done )
};
const txt_cmd_s SageKojiAfterBattleQuestionText[] = {
    text_start("You… Are you the"
        t_line "trainer who is"
        t_para "awaited by the"
        t_line "legendary #MON?"
        t_done )
};
const txt_cmd_s SageKojiAfterBattleSpeechText[] = {
    text_start("I see…"
        t_para "We, the WISE TRIO,"
        t_line "have been given "
        t_para "the responsibility"
        t_line "of protecting the"
        t_para "legendary #MON."
        t_line "We are to allow"
        t_para "passage only to"
        t_line "those people who"
        t_para "possess the power"
        t_line "and soul of truth."
        t_para "Please, do go on"
        t_line "and enter the TIN"
        t_cont "TOWER ahead."
        t_para "SUICUNE will put"
        t_line "you to the test."
        t_done )
};
const txt_cmd_s SageKojiAfterBattleFinalText[] = {
    text_start("Please, do go on."
        t_para "SUICUNE will put"
        t_line "you to the test."
        t_done )
    //db(0, 0) // filler
};
