#include "../constants.h"
#include "../util/scripting.h"
#include "DanceTheatre.h"
//// EVENTS
enum {
    DANCETHEATRE_KIMONO_GIRL1 = 2,
    DANCETHEATRE_KIMONO_GIRL2,
    DANCETHEATRE_KIMONO_GIRL3,
    DANCETHEATRE_KIMONO_GIRL4,
    DANCETHEATRE_KIMONO_GIRL5,
    DANCETHEATRE_GENTLEMAN,
    DANCETHEATRE_RHYDON,
    DANCETHEATRE_COOLTRAINER_M,
    DANCETHEATRE_GRANNY,
};

const Script_fn_t DanceTheatre_SceneScripts[] = {
    0,
};

const struct MapCallback DanceTheatre_MapCallbacks[] = {
    0,
};

const struct MapScripts DanceTheatre_MapScripts = {
    .scene_script_count = 0, // lengthof(DanceTheatre_SceneScripts),
    .scene_scripts = DanceTheatre_SceneScripts,

    .callback_count = 0, // lengthof(DanceTheatre_MapCallbacks),
    .callbacks = DanceTheatre_MapCallbacks,
};

static const struct CoordEvent DanceTheatre_CoordEvents[] = {
    0,
};

static const struct BGEvent DanceTheatre_BGEvents[] = {
    bg_event(5, 6, BGEVENT_UP, &DanceTheatreFancyPanel),
    bg_event(6, 6, BGEVENT_UP, &DanceTheatreFancyPanel),
};

static const struct WarpEventData DanceTheatre_WarpEvents[] = {
    warp_event(5, 13, ECRUTEAK_CITY, 8),
    warp_event(6, 13, ECRUTEAK_CITY, 8),
};

static const struct ObjEvent DanceTheatre_ObjectEvents[] = {
    object_event(0, 2, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 0, &TrainerKimonoGirlNaoko, -1),
    object_event(2, 1, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 0, &TrainerKimonoGirlSayo, -1),
    object_event(6, 2, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 0, &TrainerKimonoGirlZuki, -1),
    object_event(9, 1, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 0, &TrainerKimonoGirlKuni, -1),
    object_event(11, 2, SPRITE_KIMONO_GIRL, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 0, &TrainerKimonoGirlMiki, -1),
    object_event(7, 10, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DanceTheaterSurfGuy, -1),
    object_event(6, 8, SPRITE_RHYDON, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &DanceTheaterRhydon, -1),
    object_event(10, 10, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &DanceTheatreCooltrainerMScript, -1),
    object_event(3, 6, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DanceTheatreGrannyScript, -1),
};

const struct MapEvents DanceTheatre_MapEvents = {
    .warp_event_count = lengthof(DanceTheatre_WarpEvents),
    .warp_events = DanceTheatre_WarpEvents,

    .coord_event_count = 0, // lengthof(DanceTheatre_CoordEvents),
    .coord_events = DanceTheatre_CoordEvents,

    .bg_event_count = lengthof(DanceTheatre_BGEvents),
    .bg_events = DanceTheatre_BGEvents,

    .obj_event_count = lengthof(DanceTheatre_ObjectEvents),
    .obj_events = DanceTheatre_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "DanceTheatre.h"

const struct TrainerObj TrainerKimonoGirlNaoko = {KIMONO_GIRL, NAOKO, EVENT_BEAT_KIMONO_GIRL_NAOKO, KimonoGirlNaokoSeenText, KimonoGirlNaokoBeatenText, 0, TrainerKimonoGirlNaoko_Script};
bool TrainerKimonoGirlNaoko_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(KimonoGirlNaokoAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerKimonoGirlSayo = {KIMONO_GIRL, SAYO, EVENT_BEAT_KIMONO_GIRL_SAYO, KimonoGirlSayoSeenText, KimonoGirlSayoBeatenText, 0, TrainerKimonoGirlSayo_Script};
bool TrainerKimonoGirlSayo_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(KimonoGirlSayoAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerKimonoGirlZuki = {KIMONO_GIRL, ZUKI, EVENT_BEAT_KIMONO_GIRL_ZUKI, KimonoGirlZukiSeenText, KimonoGirlZukiBeatenText, 0, TrainerKimonoGirlZuki_Script};
bool TrainerKimonoGirlZuki_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(KimonoGirlZukiAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerKimonoGirlKuni = {KIMONO_GIRL, KUNI, EVENT_BEAT_KIMONO_GIRL_KUNI, KimonoGirlKuniSeenText, KimonoGirlKuniBeatenText, 0, TrainerKimonoGirlKuni_Script};
bool TrainerKimonoGirlKuni_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(KimonoGirlKuniAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerKimonoGirlMiki = {KIMONO_GIRL, MIKI, EVENT_BEAT_KIMONO_GIRL_MIKI, KimonoGirlMikiSeenText, KimonoGirlMikiBeatenText, 0, TrainerKimonoGirlMiki_Script};
bool TrainerKimonoGirlMiki_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(KimonoGirlMikiAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DanceTheaterSurfGuy(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(SurfGuyNeverLeftAScratchText)
    promptbutton
    checkevent(EVENT_GOT_HM03_SURF)
    iftrue_jump(SurfGuyAlreadyGaveSurf)
    checkevent(EVENT_BEAT_KIMONO_GIRL_NAOKO)
    iffalse(KimonoGirlsUndefeated)
    checkevent(EVENT_BEAT_KIMONO_GIRL_SAYO)
    iffalse(KimonoGirlsUndefeated)
    checkevent(EVENT_BEAT_KIMONO_GIRL_ZUKI)
    iffalse(KimonoGirlsUndefeated)
    checkevent(EVENT_BEAT_KIMONO_GIRL_KUNI)
    iffalse(KimonoGirlsUndefeated)
    checkevent(EVENT_BEAT_KIMONO_GIRL_MIKI)
    iffalse(KimonoGirlsUndefeated)
    goto GetSurf;
KimonoGirlsUndefeated:
    checkflag(ENGINE_PLAYER_IS_FEMALE)
    iftrue(PlayerIsFemale)
    writetext(SurfGuyLadGiftText)
    waitbutton
    closetext
    s_end
PlayerIsFemale:
    writetext(SurfGuyLassieGiftText)
    waitbutton
    closetext
    s_end
GetSurf:
    writetext(SurfGuyLikeADanceText)
    promptbutton
    verbosegiveitem(HM_SURF, 1)
    setevent(EVENT_GOT_HM03_SURF)
    writetext(SurfGuySurfExplanationText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SurfGuyAlreadyGaveSurf(script_s* s) {
    SCRIPT_BEGIN
    writetext(SurfGuyElegantKimonoGirlsText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DanceTheaterRhydon(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(RhydonText)
    playcry(RHYDON)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool DanceTheatreCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(DanceTheatreCooltrainerMText)
    SCRIPT_END
}
bool DanceTheatreGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(DanceTheatreGrannyText)
    SCRIPT_END
}
bool DanceTheatreFancyPanel(script_s* s) {
    SCRIPT_BEGIN
    jumptext(DanceTheatreFancyPanelText)
    SCRIPT_END
}
const txt_cmd_s KimonoGirlNaokoSeenText[] = {
    text_start("You have lovely"
        t_line "#MON. May I see"
        t_cont "them in battle?"
        t_done )
};
const txt_cmd_s KimonoGirlNaokoBeatenText[] = {
    text_start("Oh, you are very"
        t_line "strong."
        t_done )
};
const txt_cmd_s KimonoGirlNaokoAfterBattleText[] = {
    text_start("I enjoyed that"
        t_line "bout. I would like"
        t_cont "to see you again."
        t_done )
};
const txt_cmd_s KimonoGirlSayoSeenText[] = {
    text_start("I always dance"
        t_line "with my #MON."
        t_para "Of course, I also"
        t_line "train them."
        t_done )
};
const txt_cmd_s KimonoGirlSayoBeatenText[] = {
    text_start("Oh, so close!"
        t_line "I almost had you."
        t_done )
};
const txt_cmd_s KimonoGirlSayoAfterBattleText[] = {
    text_start("Rhythm is impor-"
        t_line "tant for both"
        t_para "dancing and #-"
        t_line "MON."
        t_done )
};
const txt_cmd_s KimonoGirlZukiSeenText[] = {
    text_start("Isn't my barrette"
        t_line "pretty?"
        t_para "Oh. A #MON"
        t_line "battle?"
        t_done )
};
const txt_cmd_s KimonoGirlZukiBeatenText[] = {
    text_start("I don't have any"
        t_line "#MON left…"
        t_done )
};
const txt_cmd_s KimonoGirlZukiAfterBattleText[] = {
    text_start("I put a different"
        t_line "flower in my bar-"
        t_cont "rette every month."
        t_done )
};
const txt_cmd_s KimonoGirlKuniSeenText[] = {
    text_start("Oh, you're a cute"
        t_line "trainer. Would you"
        t_cont "like to battle?"
        t_done )
};
const txt_cmd_s KimonoGirlKuniBeatenText[] = {
    text_start("You're stronger"
        t_line "than you look."
        t_done )
};
const txt_cmd_s KimonoGirlKuniAfterBattleText[] = {
    text_start("I trained a lot,"
        t_line "so I thought I was"
        t_para "a capable trainer."
        t_line "I guess I'm not."
        t_done )
};
const txt_cmd_s KimonoGirlMikiSeenText[] = {
    text_start("Do you like my"
        t_line "dancing? I'm good"
        t_cont "at #MON too."
        t_done )
};
const txt_cmd_s KimonoGirlMikiBeatenText[] = {
    text_start("Ooh, you're good"
        t_line "at #MON too."
        t_done )
};
const txt_cmd_s KimonoGirlMikiAfterBattleText[] = {
    text_start("I can keep dancing"
        t_line "because there are"
        t_para "people who enjoy"
        t_line "what I do."
        t_para "My #MON keep my"
        t_line "spirits up too."
        t_done )
};
const txt_cmd_s SurfGuyNeverLeftAScratchText[] = {
    text_start("Not only are the"
        t_line "KIMONO GIRLS great"
        t_para "dancers, they're"
        t_line "also skilled at"
        t_cont "#MON."
        t_para "I always challenge"
        t_line "them, but I've"
        t_para "never even left a"
        t_line "scratch…"
        t_done )
};
const txt_cmd_s SurfGuyLadGiftText[] = {
    text_start("Lad! If you can"
        t_line "defeat all the"
        t_para "KIMONO GIRLS, I'll"
        t_line "give you a gift."
        t_done )
};
const txt_cmd_s SurfGuyLassieGiftText[] = {
    text_start("Lassie, if you can"
        t_line "defeat all the"
        t_para "KIMONO GIRLS, I'll"
        t_line "give you a gift."
        t_done )
};
const txt_cmd_s SurfGuyLikeADanceText[] = {
    text_start("The way you bat-"
        t_line "tled, it was like"
        t_cont "watching a dance."
        t_para "It was a rare"
        t_line "treat to see!"
        t_para "I want you to have"
        t_line "this. Don't worry"
        t_cont "--take it!"
        t_done )
};
const txt_cmd_s SurfGuySurfExplanationText[] = {
    text_start("That's SURF."
        t_para "It's a move that"
        t_line "lets #MON swim"
        t_cont "across water."
        t_done )
};
const txt_cmd_s SurfGuyElegantKimonoGirlsText[] = {
    text_start("I wish my #MON"
        t_line "were as elegant as"
        t_cont "the KIMONO GIRLS…"
        t_done )
};
const txt_cmd_s RhydonText[] = {
    text_start("RHYDON: Gugooh"
        t_line "gugogooh!"
        t_done )
};
const txt_cmd_s DanceTheatreCooltrainerMText[] = {
    text_start("That man's always"
        t_line "with his RHYDON."
        t_para "Says he wants a"
        t_line "#MON that can"
        t_cont "SURF and dance."
        t_para "Is he trying to"
        t_line "make a synchro-"
        t_cont "nized swimming"
        t_cont "#MON?"
        t_done )
};
const txt_cmd_s DanceTheatreGrannyText[] = {
    text_start("The KIMONO GIRLS"
        t_line "are so beautiful…"
        t_para "But they have to"
        t_line "go through rigor-"
        t_cont "ous training."
        t_para "And they have to"
        t_line "learn to follow"
        t_para "customs before ap-"
        t_line "pearing in public."
        t_para "But if you love"
        t_line "something, any-"
        t_cont "thing is possible."
        t_done )
};
const txt_cmd_s DanceTheatreFancyPanelText[] = {
    text_start("It's a fancy panel"
        t_line "that's decorated"
        t_cont "with flowers."
        t_done )
    //db(0, 0) // filler
};
