#include "../constants.h"
#include "../util/scripting.h"
#include "Route9.h"
//// EVENTS
enum {
    ROUTE9_YOUNGSTER1 = 2,
    ROUTE9_LASS1,
    ROUTE9_YOUNGSTER2,
    ROUTE9_LASS2,
    ROUTE9_POKEFAN_M1,
    ROUTE9_POKEFAN_M2,
};

const Script_fn_t Route9_SceneScripts[] = {
    0,
};

const struct MapCallback Route9_MapCallbacks[] = {
    0,
};

const struct MapScripts Route9_MapScripts = {
    .scene_script_count = 0, // lengthof(Route9_SceneScripts),
    .scene_scripts = Route9_SceneScripts,

    .callback_count = 0, // lengthof(Route9_MapCallbacks),
    .callbacks = Route9_MapCallbacks,
};

static const struct CoordEvent Route9_CoordEvents[] = {
    0,
};

static const struct BGEvent Route9_BGEvents[] = {
    bg_event(15, 7, BGEVENT_READ, &Route9Sign),
    bg_event(41, 15, BGEVENT_ITEM, &Route9HiddenEther),
};

static const struct WarpEventData Route9_WarpEvents[] = {
    warp_event(48, 15, ROCK_TUNNEL_1F, 1),
};

static const struct ObjEvent Route9_ObjectEvents[] = {
    object_event(23, 11, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerCamperDean, -1),
    object_event(39, 8, SPRITE_LASS, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 3, &TrainerPicnickerHeidi, -1),
    object_event(11, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 5, &TrainerCamperSid, -1),
    object_event(12, 15, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_TRAINER, 1, &TrainerPicnickerEdna, -1),
    object_event(28, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerHikerTim, -1),
    object_event(36, 15, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 4, &TrainerHikerSidney, -1),
};

const struct MapEvents Route9_MapEvents = {
    .warp_event_count = lengthof(Route9_WarpEvents),
    .warp_events = Route9_WarpEvents,

    .coord_event_count = 0, // lengthof(Route9_CoordEvents),
    .coord_events = Route9_CoordEvents,

    .bg_event_count = lengthof(Route9_BGEvents),
    .bg_events = Route9_BGEvents,

    .obj_event_count = lengthof(Route9_ObjectEvents),
    .obj_events = Route9_ObjectEvents,
};

//// CODE

const struct TrainerObj TrainerCamperDean = {CAMPER, DEAN, EVENT_BEAT_CAMPER_DEAN, CamperDeanSeenText, CamperDeanBeatenText, 0, TrainerCamperDean_Script};
bool TrainerCamperDean_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperDeanAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerHeidi = {PICNICKER, HEIDI, EVENT_BEAT_PICNICKER_HEIDI, PicnickerHeidiSeenText, PicnickerHeidiBeatenText, 0, TrainerPicnickerHeidi_Script};
bool TrainerPicnickerHeidi_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PicnickerHeidiAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerCamperSid = {CAMPER, SID, EVENT_BEAT_CAMPER_SID, CamperSidSeenText, CamperSidBeatenText, 0, TrainerCamperSid_Script};
bool TrainerCamperSid_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(CamperSidAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerPicnickerEdna = {PICNICKER, EDNA, EVENT_BEAT_PICNICKER_EDNA, PicnickerEdnaSeenText, PicnickerEdnaBeatenText, 0, TrainerPicnickerEdna_Script};
bool TrainerPicnickerEdna_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(PicnickerEdnaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerTim = {HIKER, TIM, EVENT_BEAT_HIKER_TIM, HikerTimSeenText, HikerTimBeatenText, 0, TrainerHikerTim_Script};
bool TrainerHikerTim_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerTimAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerHikerSidney = {HIKER, SIDNEY, EVENT_BEAT_HIKER_SIDNEY, HikerSidneySeenText, HikerSidneyBeatenText, 0, TrainerHikerSidney_Script};
bool TrainerHikerSidney_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(HikerSidneyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route9Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route9SignText)
    SCRIPT_END
}
const struct HiddenItem Route9HiddenEther = {ETHER, EVENT_ROUTE_9_HIDDEN_ETHER};
const txt_cmd_s CamperDeanSeenText[] = {
    text_start("I came to explore"
        t_line "ROCK TUNNEL."
        t_done )
};
const txt_cmd_s CamperDeanBeatenText[] = {
    text_start("Whoa! Danger, man."
        t_done )
};
const txt_cmd_s CamperDeanAfterBattleText[] = {
    text_start("My #MON were"
        t_line "hurt before even"
        t_para "entering ROCK"
        t_line "TUNNEL."
        t_para "I'd better take"
        t_line "them to a #MON"
        t_cont "CENTER right away."
        t_done )
};
const txt_cmd_s PicnickerHeidiSeenText[] = {
    text_start("Have you ever been"
        t_line "to a picnic?"
        t_para "They're so much"
        t_line "fun!"
        t_done )
};
const txt_cmd_s PicnickerHeidiBeatenText[] = {
    text_start("Ohhhh!"
        t_done )
};
const txt_cmd_s PicnickerHeidiAfterBattleText[] = {
    text_start("We bake lots of"
        t_line "goodies and share"
        t_para "them all around."
        t_line "They're delicious!"
        t_done )
};
const txt_cmd_s CamperSidSeenText[] = {
    text_start("Hey, you!"
        t_line "Don't litter!"
        t_done )
};
const txt_cmd_s CamperSidBeatenText[] = {
    text_start("I was just point-"
        t_line "ing out…"
        t_done )
};
const txt_cmd_s CamperSidAfterBattleText[] = {
    text_start("Sorry. You weren't"
        t_line "littering. It was"
        t_cont "my mistake."
        t_done )
};
const txt_cmd_s PicnickerEdnaSeenText[] = {
    text_start("People shouldn't"
        t_line "leave any litter"
        t_cont "behind."
        t_done )
};
const txt_cmd_s PicnickerEdnaBeatenText[] = {
    text_start("Ohh… I lost…"
        t_done )
};
const txt_cmd_s PicnickerEdnaAfterBattleText[] = {
    text_start("Conserving energy"
        t_line "is important, but"
        t_para "the environment is"
        t_line "even more vital."
        t_done )
};
const txt_cmd_s HikerTimSeenText[] = {
    text_start("She'll be coming"
        t_line "'round MT.SILVER"
        t_cont "when she comes…"
        t_para "MT.SILVER is in"
        t_line "JOHTO, right?"
        t_done )
};
const txt_cmd_s HikerTimBeatenText[] = {
    text_start("I was too busy"
        t_line "singing…"
        t_done )
};
const txt_cmd_s HikerTimAfterBattleText[] = {
    text_start("Battles are about"
        t_line "concentration."
        t_done )
};
const txt_cmd_s HikerSidneySeenText[] = {
    text_start("I'll tell you a"
        t_line "secret."
        t_para "But first, we"
        t_line "battle!"
        t_done )
};
const txt_cmd_s HikerSidneyBeatenText[] = {
    text_start("Oh, dang!"
        t_line "I lost that…"
        t_done )
};
const txt_cmd_s HikerSidneyAfterBattleText[] = {
    text_start("The POWER PLANT is"
        t_line "across a small"
        t_cont "river."
        t_done )
};
const txt_cmd_s Route9SignText[] = {
    text_start("ROUTE 9"
        t_para "CERULEAN CITY -"
        t_line "ROCK TUNNEL"
        t_done )
    //db(0, 0) // filler
};
