#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower3F.h"
//// EVENTS
enum {
    RADIOTOWER3F_SUPER_NERD = 2,
    RADIOTOWER3F_GYM_GUIDE,
    RADIOTOWER3F_COOLTRAINER_F,
    RADIOTOWER3F_ROCKET1,
    RADIOTOWER3F_ROCKET2,
    RADIOTOWER3F_ROCKET3,
    RADIOTOWER3F_SCIENTIST,
};

const Script_fn_t RadioTower3F_SceneScripts[] = {
    0,
};

const struct MapCallback RadioTower3F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, RadioTower3F_MapScripts_CardKeyShutterCallback),
};

const struct MapScripts RadioTower3F_MapScripts = {
    .scene_script_count = 0, // lengthof(RadioTower3F_SceneScripts),
    .scene_scripts = RadioTower3F_SceneScripts,

    .callback_count = lengthof(RadioTower3F_MapCallbacks),
    .callbacks = RadioTower3F_MapCallbacks,
};

static const struct CoordEvent RadioTower3F_CoordEvents[] = {
    0,
};

static const struct BGEvent RadioTower3F_BGEvents[] = {
    bg_event(3, 0, BGEVENT_READ, &RadioTower3FPersonnelSign),
    bg_event(9, 0, BGEVENT_READ, &RadioTower3FPokemonMusicSign),
    bg_event(14, 2, BGEVENT_UP, &CardKeySlotScript),
};

static const struct WarpEventData RadioTower3F_WarpEvents[] = {
    warp_event(0, 0, RADIO_TOWER_2F, 1),
    warp_event(7, 0, RADIO_TOWER_4F, 2),
    warp_event(17, 0, RADIO_TOWER_4F, 4),
};

static const struct ObjEvent RadioTower3F_ObjectEvents[] = {
    object_event(7, 4, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &RadioTower3FSuperNerdScript, EVENT_RADIO_TOWER_CIVILIANS_AFTER),
    object_event(3, 4, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &RadioTower3FGymGuideScript, -1),
    object_event(11, 3, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &RadioTower3FCooltrainerFScript, -1),
    object_event(5, 1, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 2, &TrainerGruntM7, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(6, 2, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM8, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(16, 6, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM9, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
    object_event(9, 6, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 5, &TrainerScientistMarc, EVENT_RADIO_TOWER_ROCKET_TAKEOVER),
};

const struct MapEvents RadioTower3F_MapEvents = {
    .warp_event_count = lengthof(RadioTower3F_WarpEvents),
    .warp_events = RadioTower3F_WarpEvents,

    .coord_event_count = 0, // lengthof(RadioTower3F_CoordEvents),
    .coord_events = RadioTower3F_CoordEvents,

    .bg_event_count = lengthof(RadioTower3F_BGEvents),
    .bg_events = RadioTower3F_BGEvents,

    .obj_event_count = lengthof(RadioTower3F_ObjectEvents),
    .obj_events = RadioTower3F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RadioTower3F.h"

bool RadioTower3F_MapScripts_CardKeyShutterCallback(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER)
    iftrue(Change)
    s_endcallback
Change:
    changeblock(14, 2, 0x2a) // open shutter
    changeblock(14, 4, 0x01) // floor
    s_endcallback
    SCRIPT_END
}
bool RadioTower3FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(RadioTower3FSuperNerdText)
    SCRIPT_END
}
bool RadioTower3FGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(NoRockets)
    writetext(RadioTower3FGymGuideText_Rockets)
    waitbutton
    closetext
    s_end
NoRockets:
    writetext(RadioTower3FGymGuideText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool RadioTower3FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_SUNNY_DAY_FROM_RADIO_TOWER)
    iftrue(GotSunnyDay)
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(NoRockets)
    checkevent(EVENT_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER)
    iftrue(UsedCardKey)
    writetext(RadioTower3FCooltrainerFPleaseSaveDirectorText)
    waitbutton
    closetext
    s_end
UsedCardKey:
    writetext(RadioTower3FCooltrainerFIsDirectorSafeText)
    waitbutton
    closetext
    s_end
NoRockets:
    writetext(RadioTower3FCooltrainerFYoureMyHeroText)
    promptbutton
    verbosegiveitem(TM_SUNNY_DAY, 1)
    iffalse(NoRoom)
    writetext(RadioTower3FCooltrainerFItsSunnyDayText)
    waitbutton
    closetext
    setevent(EVENT_GOT_SUNNY_DAY_FROM_RADIO_TOWER)
    s_end
GotSunnyDay:
    writetext(RadioTower3FCooltrainerFYouWereMarvelousText)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM7 = {GRUNTM, GRUNTM_7, EVENT_BEAT_ROCKET_GRUNTM_7, GruntM7SeenText, GruntM7BeatenText, 0, TrainerGruntM7_Script};
bool TrainerGruntM7_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM7AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM8 = {GRUNTM, GRUNTM_8, EVENT_BEAT_ROCKET_GRUNTM_8, GruntM8SeenText, GruntM8BeatenText, 0, TrainerGruntM8_Script};
bool TrainerGruntM8_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM8AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM9 = {GRUNTM, GRUNTM_9, EVENT_BEAT_ROCKET_GRUNTM_9, GruntM9SeenText, GruntM9BeatenText, 0, TrainerGruntM9_Script};
bool TrainerGruntM9_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM9AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerScientistMarc = {SCIENTIST, MARC, EVENT_BEAT_SCIENTIST_MARC, ScientistMarcSeenText, ScientistMarcBeatenText, 0, TrainerScientistMarc_Script};
bool TrainerScientistMarc_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(ScientistMarcAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CardKeySlotScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RadioTower3FCardKeySlotText)
    waitbutton
    checkevent(EVENT_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER)
    iftrue(UsedCardKey)
    checkitem(CARD_KEY)
    iftrue(HaveCardKey)
UsedCardKey:
    closetext
    s_end
HaveCardKey:
    writetext(InsertedTheCardKeyText)
    waitbutton
    setevent(EVENT_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER)
    playsound(SFX_ENTER_DOOR)
    changeblock(14, 2, 0x2a) // open shutter
    changeblock(14, 4, 0x01) // floor
    reloadmappart
    closetext
    waitsfx
    s_end
    SCRIPT_END
}
bool RadioTower3FPersonnelSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower3FPersonnelSignText)
    SCRIPT_END
}
bool RadioTower3FPokemonMusicSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(RadioTower3FPokemonMusicSignText)
    SCRIPT_END
}
const txt_cmd_s RadioTower3FSuperNerdText[] = {
    text_start("We have recordings"
        t_line "of the cries of"
        t_para "all #MON that"
        t_line "have been found."
        t_para "We must have about"
        t_line "200 kinds."
        t_done )
};
const txt_cmd_s RadioTower3FGymGuideText_Rockets[] = {
    text_start("To trainers, #-"
        t_line "MON are their"
        t_cont "beloved partners."
        t_para "It's terrible how"
        t_line "TEAM ROCKET is"
        t_para "trying to control"
        t_line "#MON."
        t_done )
};
const txt_cmd_s RadioTower3FGymGuideText[] = {
    text_start("We run 24 hours a"
        t_line "day to broadcast"
        t_para "entertaining pro-"
        t_line "grams."
        t_para "I'll do my best to"
        t_line "run around the"
        t_cont "clock too!"
        t_done )
};
const txt_cmd_s RadioTower3FCooltrainerFPleaseSaveDirectorText[] = {
    text_start("The TEAM ROCKET"
        t_line "boss has locked"
        t_cont "himself in."
        t_para "But the DIRECTOR"
        t_line "can open it."
        t_para "He's up on the"
        t_line "fifth floor."
        t_para "Please save him!"
        t_done )
};
const txt_cmd_s RadioTower3FCooltrainerFIsDirectorSafeText[] = {
    text_start("Is the DIRECTOR"
        t_line "safe?"
        t_done )
};
const txt_cmd_s RadioTower3FCooltrainerFYoureMyHeroText[] = {
    text_start("Thank you!"
        t_line "You're my hero!"
        t_para "This is a token of"
        t_line "my appreciation."
        t_done )
};
const txt_cmd_s RadioTower3FCooltrainerFItsSunnyDayText[] = {
    text_start("It's SUNNY DAY."
        t_line "It powers up fire-"
        t_cont "type moves for a"
        t_cont "while."
        t_done )
};
const txt_cmd_s RadioTower3FCooltrainerFYouWereMarvelousText[] = {
    text_start("You were simply"
        t_line "marvelous!"
        t_done )
};
const txt_cmd_s GruntM7SeenText[] = {
    text_start("I've been given"
        t_line "strict orders."
        t_para "I'm to crush any-"
        t_line "one who challenges"
        t_cont "TEAM ROCKET!"
        t_done )
};
const txt_cmd_s GruntM7BeatenText[] = {
    text_start("What?!"
        t_done )
};
const txt_cmd_s GruntM7AfterBattleText[] = {
    text_start("I failed in my"
        t_line "duties…"
        t_para "I'll be docked pay"
        t_line "for this…"
        t_done )
};
const txt_cmd_s GruntM8SeenText[] = {
    text_start("It feels great"
        t_line "ordering #MON"
        t_cont "to commit crimes."
        t_done )
};
const txt_cmd_s GruntM8BeatenText[] = {
    text_start("You're kidding!"
        t_done )
};
const txt_cmd_s GruntM8AfterBattleText[] = {
    text_start("I feel lousy over"
        t_line "losing!"
        t_para "Darn it! I hate"
        t_line "useless #MON!"
        t_done )
};
const txt_cmd_s GruntM9SeenText[] = {
    text_start("Why did the shut-"
        t_line "ter open? Did you"
        t_para "have something to"
        t_line "do with this?"
        t_done )
};
const txt_cmd_s GruntM9BeatenText[] = {
    text_start("I'm done for!"
        t_done )
};
const txt_cmd_s GruntM9AfterBattleText[] = {
    text_start("What?! You made it"
        t_line "past our men in"
        t_cont "the UNDERGROUND?"
        t_para "How could you?"
        t_done )
};
const txt_cmd_s ScientistMarcSeenText[] = {
    text_start("An unknown child"
        t_line "wandering here?"
        t_para "Who are you?"
        t_done )
};
const txt_cmd_s ScientistMarcBeatenText[] = {
    text_start("Tch! I took you"
        t_line "too lightly!"
        t_done )
};
const txt_cmd_s ScientistMarcAfterBattleText[] = {
    text_start("Bwahahaha…"
        t_para "I can transmit as"
        t_line "strong a signal as"
        t_cont "I need from here."
        t_done )
};
const txt_cmd_s RadioTower3FCardKeySlotText[] = {
    text_start("It's the CARD KEY"
        t_line "slot."
        t_done )
};
const txt_cmd_s InsertedTheCardKeyText[] = {
    text_start("<PLAYER> inserted"
        t_line "the CARD KEY."
        t_done )
};
const txt_cmd_s RadioTower3FPersonnelSignText[] = {
    text_start("3F PERSONNEL"
        t_done )
};
const txt_cmd_s RadioTower3FPokemonMusicSignText[] = {
    text_start("#MON MUSIC with"
        t_line "Host DJ BEN"
        t_done )
    //db(0, 0) // filler
};
