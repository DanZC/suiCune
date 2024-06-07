#include "../constants.h"
#include "../util/scripting.h"
#include "Route39.h"
//// EVENTS
enum {
    ROUTE39_SAILOR = 2,
    ROUTE39_POKEFAN_M,
    ROUTE39_POKEFAN_F1,
    ROUTE39_MILTANK1,
    ROUTE39_MILTANK2,
    ROUTE39_MILTANK3,
    ROUTE39_MILTANK4,
    ROUTE39_PSYCHIC_NORMAN,
    ROUTE39_FRUIT_TREE,
    ROUTE39_POKEFAN_F2,
};

const Script_fn_t Route39_SceneScripts[] = {
    0,
};

const struct MapCallback Route39_MapCallbacks[] = {
    0,
};

const struct MapScripts Route39_MapScripts = {
    .scene_script_count = 0, // lengthof(Route39_SceneScripts),
    .scene_scripts = Route39_SceneScripts,

    .callback_count = 0, // lengthof(Route39_MapCallbacks),
    .callbacks = Route39_MapCallbacks,
};

static const struct CoordEvent Route39_CoordEvents[] = {
    0,
};

static const struct BGEvent Route39_BGEvents[] = {
    bg_event(5, 31, BGEVENT_READ, &Route39TrainerTips),
    bg_event(9, 5, BGEVENT_READ, &MoomooFarmSign),
    bg_event(15, 7, BGEVENT_READ, &Route39Sign),
    bg_event(5, 13, BGEVENT_ITEM, &Route39HiddenNugget),
};

static const struct WarpEventData Route39_WarpEvents[] = {
    warp_event(1, 3, ROUTE_39_BARN, 1),
    warp_event(5, 3, ROUTE_39_FARMHOUSE, 1),
};

static const struct ObjEvent Route39_ObjectEvents[] = {
    object_event(13, 29, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 5, &TrainerSailorEugene, -1),
    object_event(10, 22, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerPokefanmDerek, -1),
    object_event(11, 19, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_TRAINER, 4, &TrainerPokefanfRuth, -1),
    object_event(3, 12, SPRITE_TAUROS, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route39Miltank, -1),
    object_event(6, 11, SPRITE_TAUROS, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route39Miltank, -1),
    object_event(4, 15, SPRITE_TAUROS, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route39Miltank, -1),
    object_event(8, 13, SPRITE_TAUROS, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route39Miltank, -1),
    object_event(13, 7, SPRITE_STANDING_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerPsychicNorman, -1),
    object_event(9, 3, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route39FruitTree, -1),
    object_event(4, 22, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &TrainerPokefanfJaime, -1),
};

const struct MapEvents Route39_MapEvents = {
    .warp_event_count = lengthof(Route39_WarpEvents),
    .warp_events = Route39_WarpEvents,

    .coord_event_count = 0, // lengthof(Route39_CoordEvents),
    .coord_events = Route39_CoordEvents,

    .bg_event_count = lengthof(Route39_BGEvents),
    .bg_events = Route39_BGEvents,

    .obj_event_count = lengthof(Route39_ObjectEvents),
    .obj_events = Route39_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route39.h"

bool Route39Miltank(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(Route39MiltankText)
    playcry(MILTANK)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanmDerek = {POKEFANM, DEREK1, EVENT_BEAT_POKEFANM_DEREK, PokefanmDerekSeenText, PokefanmDerekBeatenText, 0, TrainerPokefanmDerek_Script};
bool TrainerPokefanmDerek_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_POKEFANM_DEREK)
    endifjustbattled
    opentext
    checkflag(ENGINE_DEREK_HAS_NUGGET)
    iftrue(HasNugget)
    checkcellnum(PHONE_POKEFANM_DEREK)
    iftrue(NumberAccepted)
    checkpoke(PIKACHU)
    iffalse(WantsPikachu)
    checkevent(EVENT_DEREK_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedAlready)
    writetext(PokefanMDerekText_NotBragging)
    promptbutton
    setevent(EVENT_DEREK_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedAlready:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_POKEFANM_DEREK)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, POKEFANM, DEREK1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
HasNugget:
    scall_local(Gift);
    verbosegiveitem(NUGGET, 1)
    iffalse(NoRoom)
    clearflag(ENGINE_DEREK_HAS_NUGGET)
    goto NumberAccepted;
NoRoom:
    goto PackFull;
WantsPikachu:
    writetext(PokefanMDerekPikachuIsItText)
    waitbutton
    closetext
    s_end
AskNumber1:
    jumpstd(AskNumber1MScript)
    s_end
AskNumber2:
    jumpstd(AskNumber2MScript)
    s_end
RegisteredNumber:
    jumpstd(RegisteredNumberMScript)
    s_end
NumberAccepted:
    jumpstd(NumberAcceptedMScript)
    s_end
NumberDeclined:
    jumpstd(NumberDeclinedMScript)
    s_end
PhoneFull:
    jumpstd(PhoneFullMScript)
    s_end
Gift:
    jumpstd(GiftMScript)
    s_end
PackFull:
    jumpstd(PackFullMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPokefanfRuth = {POKEFANF, RUTH, EVENT_BEAT_POKEFANF_RUTH, PokefanfRuthSeenText, PokefanfRuthBeatenText, 0, TrainerPokefanfRuth_Script};
bool TrainerPokefanfRuth_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PokefanfRuthAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorEugene = {SAILOR, EUGENE, EVENT_BEAT_SAILOR_EUGENE, SailorEugeneSeenText, SailorEugeneBeatenText, 0, TrainerSailorEugene_Script};
bool TrainerSailorEugene_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SailorEugeneAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPsychicNorman = {PSYCHIC_T, NORMAN, EVENT_BEAT_PSYCHIC_NORMAN, PsychicNormanSeenText, PsychicNormanBeatenText, 0, TrainerPsychicNorman_Script};
bool TrainerPsychicNorman_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PsychicNormanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TrainerPokefanfJaime(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checktime(NITE)
    iffalse(NotNight)
    checkevent(EVENT_BEAT_POKEFANF_JAIME)
    iftrue(Beaten)
    writetext(PokefanfJaimeSeenText)
    waitbutton
    closetext
    winlosstext(PokefanfJaimeBeatenText, 0)
    loadtrainer(POKEFANF, JAIME)
    startbattle
    reloadmapafterbattle
    setevent(EVENT_BEAT_POKEFANF_JAIME)
    closetext
    s_end
Beaten:
    writetext(PokefanfJaimeAfterBattleText)
    waitbutton
    closetext
    s_end
NotNight:
    writetext(PokefanfJaimeHopeItGetsDarkText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route39Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route39SignText)
    SCRIPT_END
}
bool MoomooFarmSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MoomooFarmSignText)
    SCRIPT_END
}
bool Route39TrainerTips(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route39TrainerTipsText)
    SCRIPT_END
}
bool Route39FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_39)
    SCRIPT_END
}
const struct HiddenItem Route39HiddenNugget = {NUGGET, EVENT_ROUTE_39_HIDDEN_NUGGET};
const txt_cmd_s Route39MiltankText[] = {
    text_start("MILTANK: Mooo!"
        t_done )
};
const txt_cmd_s SailorEugeneSeenText[] = {
    text_start("I just got back to"
        t_line "OLIVINE."
        t_para "So how about a"
        t_line "#MON battle?"
        t_done )
};
const txt_cmd_s SailorEugeneBeatenText[] = {
    text_start("Awaaargh!"
        t_done )
};
const txt_cmd_s SailorEugeneAfterBattleText[] = {
    text_start("My #MON were"
        t_line "caught and raised"
        t_cont "overseas."
        t_para "They're my compan-"
        t_line "ions on those long"
        t_cont "voyages."
        t_done )
};
const txt_cmd_s PokefanmDerekSeenText[] = {
    text_start("This is a good"
        t_line "time to brag about"
        t_cont "my PIKACHU!"
        t_done )
};
const txt_cmd_s PokefanmDerekBeatenText[] = {
    text_start("I had no time to"
        t_line "show off PIKACHU…"
        t_done )
};
const txt_cmd_s PokefanMDerekText_NotBragging[] = {
    text_start("I'm not listening"
        t_line "to your bragging!"
        t_para "We # FANS have"
        t_line "a policy of not"
        t_para "listening to other"
        t_line "people brag!"
        t_done )
};
const txt_cmd_s PokefanfRuthSeenText[] = {
    text_start("Such darling"
        t_line "#MON."
        t_para "Let's show our"
        t_line "#MON together"
        t_cont "at the same time."
        t_done )
};
const txt_cmd_s PokefanfRuthBeatenText[] = {
    text_start("I don't mind"
        t_line "losing."
        t_done )
};
const txt_cmd_s PokefanfRuthAfterBattleText[] = {
    text_start("Do you know about"
        t_line "baby #MON?"
        t_para "I bet they're just"
        t_line "adorable!"
        t_done )
};
const txt_cmd_s PokefanMDerekPikachuIsItText[] = {
    text_start("PIKACHU is it!"
        t_line "Don't you agree?"
        t_done )
};
const txt_cmd_s PsychicNormanSeenText[] = {
    text_start("Let me see what"
        t_line "your #MON are"
        t_cont "capable of."
        t_done )
};
const txt_cmd_s PsychicNormanBeatenText[] = {
    text_start("Ooh, your #MON"
        t_line "have potential."
        t_done )
};
const txt_cmd_s PsychicNormanAfterBattleText[] = {
    text_start("You know how #-"
        t_line "MON have different"
        t_cont "abilities?"
        t_para "People are like"
        t_line "that too. Every-"
        t_cont "one has different"
        t_cont "potential."
        t_done )
};
const txt_cmd_s PokefanfJaimeHopeItGetsDarkText[] = {
    text_start("Ufufufu… I hope it"
        t_line "gets dark soon."
        t_done )
};
const txt_cmd_s PokefanfJaimeSeenText[] = {
    text_start("You came at just"
        t_line "the right time."
        t_para "Let's battle."
        t_done )
};
const txt_cmd_s PokefanfJaimeBeatenText[] = {
    text_start("Oh, how disap-"
        t_line "pointing…"
        t_done )
};
const txt_cmd_s PokefanfJaimeAfterBattleText[] = {
    text_start("I met my MEOWTH at"
        t_line "night, right here"
        t_cont "on ROUTE 39."
        t_para "I'm not sure why,"
        t_line "but it seems to"
        t_para "like it when I"
        t_line "train here."
        t_para "It seems to become"
        t_line "friendlier by"
        t_para "training here than"
        t_line "anywhere else."
        t_done )
};
const txt_cmd_s Route39SignText[] = {
    text_start("ROUTE 39"
        t_para "OLIVINE CITY -"
        t_line "ECRUTEAK CITY"
        t_done )
};
const txt_cmd_s MoomooFarmSignText[] = {
    text_start("MOOMOO FARM"
        t_para "Enjoy Our Fresh"
        t_line "and Tasty Milk"
        t_done )
};
const txt_cmd_s Route39TrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "Use HEADBUTT on"
        t_line "trees to shake"
        t_cont "#MON out."
        t_para "Different kinds of"
        t_line "#MON drop out"
        t_cont "of trees."
        t_para "Use HEADBUTT on"
        t_line "any tree you see!"
        t_done )
    //db(0, 0) // filler
};
