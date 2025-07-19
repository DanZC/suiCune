#include "../constants.h"
#include "../util/scripting.h"
#include "Route33.h"
//// EVENTS
enum {
    ROUTE33_POKEFAN_M = 2,
    ROUTE33_LASS,
    ROUTE33_FRUIT_TREE,
};

const Script_fn_t Route33_SceneScripts[] = {
    0,
};

const struct MapCallback Route33_MapCallbacks[] = {
    0,
};

const struct MapScripts Route33_MapScripts = {
    .scene_script_count = 0, // lengthof(Route33_SceneScripts),
    .scene_scripts = Route33_SceneScripts,

    .callback_count = 0, // lengthof(Route33_MapCallbacks),
    .callbacks = Route33_MapCallbacks,
};

static const struct CoordEvent Route33_CoordEvents[] = {
    0,
};

static const struct BGEvent Route33_BGEvents[] = {
    bg_event(11, 11, BGEVENT_READ, &Route33Sign),
};

static const struct WarpEventData Route33_WarpEvents[] = {
    warp_event(11, 9, UNION_CAVE_1F, 3),
};

static const struct ObjEvent Route33_ObjectEvents[] = {
    object_event(6, 13, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_TRAINER, 2, &TrainerHikerAnthony, -1),
    object_event(13, 16, SPRITE_LASS, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route33LassScript, -1),
    object_event(14, 16, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route33FruitTree, -1),
};

const struct MapEvents Route33_MapEvents = {
    .warp_event_count = lengthof(Route33_WarpEvents),
    .warp_events = Route33_WarpEvents,

    .coord_event_count = 0, // lengthof(Route33_CoordEvents),
    .coord_events = Route33_CoordEvents,

    .bg_event_count = lengthof(Route33_BGEvents),
    .bg_events = Route33_BGEvents,

    .obj_event_count = lengthof(Route33_ObjectEvents),
    .obj_events = Route33_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route33.h"

bool Route33LassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route33LassText)
    SCRIPT_END
}
const struct TrainerObj TrainerHikerAnthony = {HIKER, ANTHONY2, EVENT_BEAT_HIKER_ANTHONY, HikerAnthony2SeenText, HikerAnthony2BeatenText, 0, TrainerHikerAnthony_Script};
bool TrainerHikerAnthony_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_HIKER_ANTHONY)
    endifjustbattled
    opentext
    checkflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    iftrue(Rematch)
    checkflag(ENGINE_DUNSPARCE_SWARM)
    iftrue(Swarm)
    checkcellnum(PHONE_HIKER_ANTHONY)
    iftrue(NumberAccepted)
    checkevent(EVENT_ANTHONY_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskAgain)
    writetext(HikerAnthony2AfterText)
    promptbutton
    setevent(EVENT_ANTHONY_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForPhoneNumber;
AskAgain:
    scall_local(AskNumber2);
AskForPhoneNumber:
    askforphonenumber(PHONE_HIKER_ANTHONY)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, HIKER, ANTHONY2)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
Rematch:
    scall_local(RematchStd);
    winlosstext(HikerAnthony2BeatenText, 0)
    readmem(&gPlayer.AnthonyFightCount)
    ifequal(4, Fight4)
    ifequal(3, Fight3)
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight4:
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight4)
Fight3:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight3)
Fight2:
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(LoadFight2)
Fight1:
    checkflag(ENGINE_FLYPOINT_OLIVINE)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(HIKER, ANTHONY2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.AnthonyFightCount, 1)
    clearflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(HIKER, ANTHONY1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.AnthonyFightCount, 2)
    clearflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(HIKER, ANTHONY3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.AnthonyFightCount, 3)
    clearflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(HIKER, ANTHONY4)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.AnthonyFightCount, 4)
    clearflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(HIKER, ANTHONY5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_ANTHONY_READY_FOR_REMATCH)
    s_end
Swarm:
    writetext(HikerAnthonyDunsparceText)
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
RematchStd:
    jumpstd(RematchMScript)
    s_end
    SCRIPT_END
}
bool Route33Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route33SignText)
    SCRIPT_END
}
bool Route33FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_33)
    SCRIPT_END
}
const txt_cmd_s HikerAnthony2SeenText[] = {
    text_start("I came through the"
        t_line "tunnel, but I"
        t_para "still have plenty"
        t_line "of energy left."
        t_done )
};
const txt_cmd_s HikerAnthony2BeatenText[] = {
    text_start("Whoa! You've got"
        t_line "more zip than me!"
        t_done )
};
const txt_cmd_s HikerAnthony2AfterText[] = {
    text_start("We HIKERS are at"
        t_line "our best in the"
        t_cont "mountains."
        t_done )
};
const txt_cmd_s HikerAnthonyDunsparceText[] = {
    text_start("Hey, did you get a"
        t_line "DUNSPARCE?"
        t_para "I caught one too."
        t_para "Take a look at it"
        t_line "in the light. It's"
        t_cont "got a funny face!"
        t_done )
};
const txt_cmd_s Route33LassText[] = {
    text_start("Pant, pant…"
        t_para "I finally got"
        t_line "through that cave."
        t_para "It was much bigger"
        t_line "than I'd expected."
        t_para "I got too tired to"
        t_line "explore the whole"
        t_para "thing, so I came"
        t_line "outside."
        t_done )
};
const txt_cmd_s Route33SignText[] = {
    text_start("ROUTE 33"
        t_done )
    //db(0, 0) // filler
};
