#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonGym.h"
//// EVENTS
enum {
    CELADONGYM_ERIKA = 2,
    CELADONGYM_LASS1,
    CELADONGYM_LASS2,
    CELADONGYM_BEAUTY,
    CELADONGYM_TWIN1,
    CELADONGYM_TWIN2,
};

const Script_fn_t CeladonGym_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonGym_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonGym_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonGym_SceneScripts),
    .scene_scripts = CeladonGym_SceneScripts,

    .callback_count = 0, // lengthof(CeladonGym_MapCallbacks),
    .callbacks = CeladonGym_MapCallbacks,
};

static const struct CoordEvent CeladonGym_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonGym_BGEvents[] = {
    bg_event(3, 15, BGEVENT_READ, &CeladonGymStatue),
    bg_event(6, 15, BGEVENT_READ, &CeladonGymStatue),
};

static const struct WarpEventData CeladonGym_WarpEvents[] = {
    warp_event(4, 17, CELADON_CITY, 8),
    warp_event(5, 17, CELADON_CITY, 8),
};

static const struct ObjEvent CeladonGym_ObjectEvents[] = {
    object_event(5, 3, SPRITE_ERIKA, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonGymErikaScript, -1),
    object_event(7, 8, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerLassMichelle, -1),
    object_event(2, 8, SPRITE_LASS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 2, &TrainerPicnickerTanya, -1),
    object_event(3, 5, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerBeautyJulia, -1),
    object_event(4, 10, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsJoAndZoe1, -1),
    object_event(5, 10, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 1, &TrainerTwinsJoAndZoe2, -1),
};

const struct MapEvents CeladonGym_MapEvents = {
    .warp_event_count = lengthof(CeladonGym_WarpEvents),
    .warp_events = CeladonGym_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonGym_CoordEvents),
    .coord_events = CeladonGym_CoordEvents,

    .bg_event_count = lengthof(CeladonGym_BGEvents),
    .bg_events = CeladonGym_BGEvents,

    .obj_event_count = lengthof(CeladonGym_ObjectEvents),
    .obj_events = CeladonGym_ObjectEvents,
};

//// CODE

bool CeladonGymErikaScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(ENGINE_RAINBOWBADGE)
    iftrue(FightDone)
    writetext(ErikaBeforeBattleText)
    waitbutton
    closetext
    winlosstext(ErikaBeatenText, 0)
    loadtrainer(ERIKA, ERIKA1)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_ERIKA)
    setevent(EVENT_BEAT_LASS_MICHELLE)
    setevent(EVENT_BEAT_PICNICKER_TANYA)
    setevent(EVENT_BEAT_BEAUTY_JULIA)
    setevent(EVENT_BEAT_TWINS_JO_AND_ZOE)
    opentext
    writetext(PlayerReceivedRainbowBadgeText)
    playsound(SFX_GET_BADGE)
    waitsfx
    setflag(ENGINE_RAINBOWBADGE)
FightDone:
    checkevent(EVENT_GOT_TM19_GIGA_DRAIN)
    iftrue(GotGigaDrain)
    writetext(ErikaExplainTMText)
    promptbutton
    verbosegiveitem(TM_GIGA_DRAIN, 1)
    iffalse(GotGigaDrain)
    setevent(EVENT_GOT_TM19_GIGA_DRAIN)
GotGigaDrain:
    writetext(ErikaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerLassMichelle = {LASS, MICHELLE, EVENT_BEAT_LASS_MICHELLE, LassMichelleSeenText, LassMichelleBeatenText, 0, TrainerLassMichelle_Script};
bool TrainerLassMichelle_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(LassMichelleAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerTanya = {PICNICKER, TANYA, EVENT_BEAT_PICNICKER_TANYA, PicnickerTanyaSeenText, PicnickerTanyaBeatenText, 0, TrainerPicnickerTanya_Script};
bool TrainerPicnickerTanya_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PicnickerTanyaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBeautyJulia = {BEAUTY, JULIA, EVENT_BEAT_BEAUTY_JULIA, BeautyJuliaSeenText, BeautyJuliaBeatenText, 0, TrainerBeautyJulia_Script};
bool TrainerBeautyJulia_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BeautyJuliaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsJoAndZoe1 = {TWINS, JOANDZOE1, EVENT_BEAT_TWINS_JO_AND_ZOE, TwinsJoAndZoe1SeenText, TwinsJoAndZoe1BeatenText, 0, TrainerTwinsJoAndZoe1_Script};
bool TrainerTwinsJoAndZoe1_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsJoAndZoe1AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerTwinsJoAndZoe2 = {TWINS, JOANDZOE2, EVENT_BEAT_TWINS_JO_AND_ZOE, TwinsJoAndZoe2SeenText, TwinsJoAndZoe2BeatenText, 0, TrainerTwinsJoAndZoe2_Script};
bool TrainerTwinsJoAndZoe2_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(TwinsJoAndZoe2AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CeladonGymStatue(script_s* s) {
    SCRIPT_BEGIN
    checkflag(ENGINE_RAINBOWBADGE)
    iftrue(Beaten)
    jumpstd(GymStatue1Script)
Beaten:
    gettrainername(STRING_BUFFER_4, ERIKA, ERIKA1)
    jumpstd(GymStatue2Script)
    SCRIPT_END
}
const txt_cmd_s ErikaBeforeBattleText[] = {
    text_start("ERIKA: Hello…"
        t_line "Lovely weather,"
        t_para "isn't it?"
        t_line "It's so pleasant…"
        t_para "…I'm afraid I may"
        t_line "doze off…"
        t_para "My name is ERIKA."
        t_line "I am the LEADER of"
        t_cont "CELADON GYM."
        t_para "…Oh? All the way"
        t_line "from JOHTO, you"
        t_cont "say? How nice…"
        t_para "Oh. I'm sorry, I"
        t_line "didn't realize"
        t_para "that you wished to"
        t_line "challenge me."
        t_para "Very well, but I"
        t_line "shall not lose."
        t_done )
};
const txt_cmd_s ErikaBeatenText[] = {
    text_start("ERIKA: Oh!"
        t_line "I concede defeat…"
        t_para "You are remarkably"
        t_line "strong…"
        t_para "I shall give you"
        t_line "RAINBOWBADGE…"
        t_done )
};
const txt_cmd_s PlayerReceivedRainbowBadgeText[] = {
    text_start("<PLAYER> received"
        t_line "RAINBOWBADGE."
        t_done )
};
const txt_cmd_s ErikaExplainTMText[] = {
    text_start("ERIKA: That was a"
        t_line "delightful match."
        t_para "I felt inspired."
        t_line "Please, I wish you"
        t_cont "to have this TM."
        t_para "It is GIGA DRAIN."
        t_para "It is a wonderful"
        t_line "move that drains"
        t_para "half the damage it"
        t_line "inflicts to heal"
        t_cont "your #MON."
        t_para "Please use it if"
        t_line "it pleases you…"
        t_done )
};
const txt_cmd_s ErikaAfterBattleText[] = {
    text_start("ERIKA: Losing"
        t_line "leaves a bitter"
        t_cont "aftertaste…"
        t_para "But knowing that"
        t_line "there are strong"
        t_para "trainers spurs me"
        t_line "to do better…"
        t_done )
};
const txt_cmd_s LassMichelleSeenText[] = {
    text_start("Do you think a"
        t_line "girls-only GYM"
        t_cont "is rare?"
        t_done )
};
const txt_cmd_s LassMichelleBeatenText[] = {
    text_start("Oh, bleah!"
        t_done )
};
const txt_cmd_s LassMichelleAfterBattleText[] = {
    text_start("I just got care-"
        t_line "less, that's all!"
        t_done )
};
const txt_cmd_s PicnickerTanyaSeenText[] = {
    text_start("Oh, a battle?"
        t_line "That's kind of"
        t_cont "scary, but OK!"
        t_done )
};
const txt_cmd_s PicnickerTanyaBeatenText[] = {
    text_start("Oh, that's it?"
        t_done )
};
const txt_cmd_s PicnickerTanyaAfterBattleText[] = {
    text_start("Oh, look at all"
        t_line "your BADGES. No"
        t_para "wonder I couldn't"
        t_line "win!"
        t_done )
};
const txt_cmd_s BeautyJuliaSeenText[] = {
    text_start("Were you looking"
        t_line "at these flowers"
        t_cont "or at me?"
        t_done )
};
const txt_cmd_s BeautyJuliaBeatenText[] = {
    text_start("How annoying!"
        t_done )
};
const txt_cmd_s BeautyJuliaAfterBattleText[] = {
    text_start("How do I go about"
        t_line "becoming ladylike"
        t_cont "like ERIKA?"
        t_done )
};
const txt_cmd_s TwinsJoAndZoe1SeenText[] = {
    text_start("We'll show you"
        t_line "#MON moves that"
        t_cont "ERIKA taught us!"
        t_done )
};
const txt_cmd_s TwinsJoAndZoe1BeatenText[] = {
    text_start("Oh… We lost…"
        t_done )
};
const txt_cmd_s TwinsJoAndZoe1AfterBattleText[] = {
    text_start("ERIKA will get you"
        t_line "back for us!"
        t_done )
};
const txt_cmd_s TwinsJoAndZoe2SeenText[] = {
    text_start("We're going to"
        t_line "protect ERIKA!"
        t_done )
};
const txt_cmd_s TwinsJoAndZoe2BeatenText[] = {
    text_start("We couldn't win…"
        t_done )
};
const txt_cmd_s TwinsJoAndZoe2AfterBattleText[] = {
    text_start("ERIKA is much,"
        t_line "much stronger!"
        t_done )
    //db(0, 0) // filler
};
