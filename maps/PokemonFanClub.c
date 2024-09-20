#include "../constants.h"
#include "../util/scripting.h"
#include "PokemonFanClub.h"
//// EVENTS
enum {
    POKEMONFANCLUB_CHAIRMAN = 2,
    POKEMONFANCLUB_RECEPTIONIST,
    POKEMONFANCLUB_CLEFAIRY_GUY,
    POKEMONFANCLUB_TEACHER,
    POKEMONFANCLUB_FAIRY,
    POKEMONFANCLUB_ODDISH,
};

const Script_fn_t PokemonFanClub_SceneScripts[] = {
    0,
};

const struct MapCallback PokemonFanClub_MapCallbacks[] = {
    0,
};

const struct MapScripts PokemonFanClub_MapScripts = {
    .scene_script_count = 0, // lengthof(PokemonFanClub_SceneScripts),
    .scene_scripts = PokemonFanClub_SceneScripts,

    .callback_count = 0, // lengthof(PokemonFanClub_MapCallbacks),
    .callbacks = PokemonFanClub_MapCallbacks,
};

static const struct CoordEvent PokemonFanClub_CoordEvents[] = {
    0,
};

static const struct BGEvent PokemonFanClub_BGEvents[] = {
    bg_event(7, 0, BGEVENT_READ, &PokemonFanClubListenSign),
    bg_event(9, 0, BGEVENT_READ, &PokemonFanClubBraggingSign),
};

static const struct WarpEventData PokemonFanClub_WarpEvents[] = {
    warp_event(2, 7, VERMILION_CITY, 3),
    warp_event(3, 7, VERMILION_CITY, 3),
};

static const struct ObjEvent PokemonFanClub_ObjectEvents[] = {
    object_event(3, 1, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PokemonFanClubChairmanScript, -1),
    object_event(4, 1, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PokemonFanClubReceptionistScript, -1),
    object_event(2, 3, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PokemonFanClubClefairyGuyScript, -1),
    object_event(7, 2, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PokemonFanClubTeacherScript, -1),
    object_event(2, 4, SPRITE_FAIRY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PokemonFanClubClefairyDollScript, EVENT_VERMILION_FAN_CLUB_DOLL),
    object_event(7, 3, SPRITE_ODDISH, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PokemonFanClubBayleefScript, -1),
};

const struct MapEvents PokemonFanClub_MapEvents = {
    .warp_event_count = lengthof(PokemonFanClub_WarpEvents),
    .warp_events = PokemonFanClub_WarpEvents,

    .coord_event_count = 0, // lengthof(PokemonFanClub_CoordEvents),
    .coord_events = PokemonFanClub_CoordEvents,

    .bg_event_count = lengthof(PokemonFanClub_BGEvents),
    .bg_events = PokemonFanClub_BGEvents,

    .obj_event_count = lengthof(PokemonFanClub_ObjectEvents),
    .obj_events = PokemonFanClub_ObjectEvents,
};

//// CODE

bool PokemonFanClubChairmanScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_LISTENED_TO_FAN_CLUB_PRESIDENT)
    iftrue(HeardSpeech)
    checkevent(EVENT_LISTENED_TO_FAN_CLUB_PRESIDENT_BUT_BAG_WAS_FULL)
    iftrue(HeardSpeechButBagFull)
    writetext(PokemonFanClubChairmanDidYouVisitToHearAboutMyMonText)
    yesorno
    iffalse(NotListening)
    writetext(PokemonFanClubChairmanRapidashText)
    promptbutton
HeardSpeechButBagFull:
    writetext(PokemonFanClubChairmanIWantYouToHaveThisText)
    promptbutton
    verbosegiveitem(RARE_CANDY, 1)
    iffalse(BagFull)
    setevent(EVENT_LISTENED_TO_FAN_CLUB_PRESIDENT)
    writetext(PokemonFanClubChairmanItsARareCandyText)
    waitbutton
    closetext
    s_end
HeardSpeech:
    writetext(PokemonFanClubChairmanMoreTalesToTellText)
    waitbutton
    closetext
    s_end
NotListening:
    writetext(PokemonFanClubChairmanHowDisappointingText)
    waitbutton
BagFull:
    closetext
    s_end
    SCRIPT_END
}
bool PokemonFanClubReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PokemonFanClubReceptionistText)
    SCRIPT_END
}
bool PokemonFanClubClefairyGuyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_LOST_ITEM_FROM_FAN_CLUB)
    iftrue(GotLostItem)
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(FoundClefairyDoll)
    writetext(PokemonFanClubClefairyGuyClefairyIsSoAdorableText)
    waitbutton
    closetext
    s_end
FoundClefairyDoll:
    writetext(PokemonFanClubClefairyGuyMakingDoWithADollIFoundText)
    checkevent(EVENT_MET_COPYCAT_FOUND_OUT_ABOUT_LOST_ITEM)
    iftrue(MetCopycat)
    waitbutton
    closetext
    s_end
MetCopycat:
    promptbutton
    writetext(PokemonFanClubClefairyGuyTakeThisDollBackToGirlText)
    promptbutton
    waitsfx
    giveitem(LOST_ITEM, 1)
    iffalse(NoRoom)
    disappear(POKEMONFANCLUB_FAIRY)
    writetext(PokemonFanClubPlayerReceivedDollText)
    playsound(SFX_KEY_ITEM)
    waitsfx
    itemnotify
    setevent(EVENT_GOT_LOST_ITEM_FROM_FAN_CLUB)
    closetext
    s_end
GotLostItem:
    writetext(PokemonFanClubClefairyGuyGoingToGetARealClefairyText)
    waitbutton
    closetext
    s_end
NoRoom:
    writetext(PokemonFanClubClefairyGuyPackIsJammedFullText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PokemonFanClubTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PokemonFanClubTeacherText)
    SCRIPT_END
}
bool PokemonFanClubClefairyDollScript(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PokemonFanClubClefairyDollText)
    SCRIPT_END
}
bool PokemonFanClubBayleefScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(PokemonFanClubBayleefText)
    playcry(BAYLEEF)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PokemonFanClubListenSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PokemonFanClubListenSignText)
    SCRIPT_END
}
bool PokemonFanClubBraggingSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(PokemonFanClubBraggingSignText)
    SCRIPT_END
}
const txt_cmd_s PokemonFanClubChairmanDidYouVisitToHearAboutMyMonText[] = {
    text_start("I'm the CHAIRMAN"
        t_line "of the #MON FAN"
        t_cont "CLUB."
        t_para "I've raised over"
        t_line "150 #MON."
        t_para "I'm very fussy"
        t_line "when it comes to"
        t_cont "#MON."
        t_para "Did you visit just"
        t_line "to hear about my"
        t_cont "#MON?"
        t_done )
};
const txt_cmd_s PokemonFanClubChairmanRapidashText[] = {
    text_start("Good!"
        t_line "Then listen up!"
        t_para "So… my favorite"
        t_line "RAPIDASH…"
        t_para "It… cute… lovely…"
        t_line "smart… unbearably…"
        t_cont "plus… amazing… oh…"
        t_cont "you think so?…"
        t_cont "Too much… wild…"
        t_cont "beautiful… kindly…"
        t_cont "love it!"
        t_para "Hug it… when…"
        t_line "sleeping… warm and"
        t_cont "cuddly… Oh, and…"
        t_cont "spectacular…"
        t_cont "ravishing… simply"
        t_cont "divine…"
        t_cont "Oops! Look at the"
        t_cont "time! I've kept"
        t_cont "you too long!"
        t_done )
};
const txt_cmd_s PokemonFanClubChairmanIWantYouToHaveThisText[] = {
    text_start("Thanks for hearing"
        t_line "me out. I want you"
        t_cont "to have this!"
        t_done )
};
const txt_cmd_s PokemonFanClubChairmanItsARareCandyText[] = {
    text_start("It's a RARE CANDY"
        t_line "that makes #MON"
        t_cont "stronger."
        t_para "I prefer making my"
        t_line "#MON stronger"
        t_para "by battling, so"
        t_line "you can have it."
        t_done )
};
const txt_cmd_s PokemonFanClubChairmanMoreTalesToTellText[] = {
    text_start("Hello, <PLAY_G>!"
        t_para "Did you come see"
        t_line "me about my #-"
        t_cont "MON again?"
        t_para "No? Oh… I had more"
        t_line "tales to tell…"
        t_done )
};
const txt_cmd_s PokemonFanClubChairmanHowDisappointingText[] = {
    text_start("How disappointing…"
        t_para "Come back if you"
        t_line "want to listen."
        t_done )
};
const txt_cmd_s PokemonFanClubReceptionistText[] = {
    text_start("Our CHAIRMAN is"
        t_line "very vocal when it"
        t_cont "comes to #MON…"
        t_done )
};
const txt_cmd_s PokemonFanClubClefairyGuyClefairyIsSoAdorableText[] = {
    text_start("I love the way"
        t_line "CLEFAIRY waggles"
        t_para "its finger when"
        t_line "it's trying to use"
        t_para "METRONOME."
        t_line "It's so adorable!"
        t_done )
};
const txt_cmd_s PokemonFanClubClefairyGuyMakingDoWithADollIFoundText[] = {
    text_start("I love CLEFAIRY,"
        t_line "but I could never"
        t_para "catch one. So I'm"
        t_line "making do with a"
        t_para "# DOLL that I"
        t_line "found."
        t_done )
};
const txt_cmd_s PokemonFanClubClefairyGuyTakeThisDollBackToGirlText[] = {
    text_start("Oh, I see now. The"
        t_line "girl who lost this"
        t_para "# DOLL is sad…"
        t_para "OK. Could you take"
        t_line "this # DOLL"
        t_para "back to that poor"
        t_line "little girl?"
        t_para "I'll befriend a"
        t_line "real CLEFAIRY on"
        t_para "my own one day."
        t_line "No worries!"
        t_done )
};
const txt_cmd_s PokemonFanClubPlayerReceivedDollText[] = {
    text_start("<PLAYER> received"
        t_line "# DOLL."
        t_done )
};
const txt_cmd_s PokemonFanClubClefairyGuyGoingToGetARealClefairyText[] = {
    text_start("You watch. I'm"
        t_line "going to get a"
        t_para "real CLEFAIRY as"
        t_line "my friend."
        t_done )
};
const txt_cmd_s PokemonFanClubClefairyGuyPackIsJammedFullText[] = {
    text_start("Your PACK is"
        t_line "jammed full."
        t_done )
};
const txt_cmd_s PokemonFanClubTeacherText[] = {
    text_start("Look at my darling"
        t_line "BAYLEEF!"
        t_para "The leaf on its"
        t_line "head is so cute!"
        t_done )
};
const txt_cmd_s PokemonFanClubClefairyDollText[] = {
    text_start("It's a CLEFAIRY!"
        t_line "Huh?"
        t_para "Oh, right. It's a"
        t_line "CLEFAIRY #"
        t_cont "DOLL."
        t_done )
};
const txt_cmd_s PokemonFanClubBayleefText[] = {
    text_start("BAYLEEF: Li liif!"
        t_done )
};
const txt_cmd_s PokemonFanClubListenSignText[] = {
    text_start("Let's all listen"
        t_line "politely to other"
        t_cont "trainers."
        t_done )
};
const txt_cmd_s PokemonFanClubBraggingSignText[] = {
    text_start("If someone brags,"
        t_line "brag right back!"
        t_done )
    //db(0, 0) // filler
};
