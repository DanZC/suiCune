#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse2F.h"
//// EVENTS
enum {
    OLIVINELIGHTHOUSE2F_SAILOR = 2,
    OLIVINELIGHTHOUSE2F_GENTLEMAN,
};

const Script_fn_t OlivineLighthouse2F_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineLighthouse2F_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineLighthouse2F_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineLighthouse2F_SceneScripts),
    .scene_scripts = OlivineLighthouse2F_SceneScripts,

    .callback_count = 0, // lengthof(OlivineLighthouse2F_MapCallbacks),
    .callbacks = OlivineLighthouse2F_MapCallbacks,
};

static const struct CoordEvent OlivineLighthouse2F_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineLighthouse2F_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivineLighthouse2F_WarpEvents[] = {
    warp_event(3, 11, OLIVINE_LIGHTHOUSE_1F, 3),
    warp_event(5, 3, OLIVINE_LIGHTHOUSE_3F, 2),
    warp_event(16, 13, OLIVINE_LIGHTHOUSE_1F, 4),
    warp_event(17, 13, OLIVINE_LIGHTHOUSE_1F, 5),
    warp_event(16, 11, OLIVINE_LIGHTHOUSE_3F, 4),
    warp_event(17, 11, OLIVINE_LIGHTHOUSE_3F, 5),
};

static const struct ObjEvent OlivineLighthouse2F_ObjectEvents[] = {
    object_event(9, 3, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerSailorHuey, -1),
    object_event(17, 8, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerGentlemanAlfred, -1),
};

const struct MapEvents OlivineLighthouse2F_MapEvents = {
    .warp_event_count = lengthof(OlivineLighthouse2F_WarpEvents),
    .warp_events = OlivineLighthouse2F_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineLighthouse2F_CoordEvents),
    .coord_events = OlivineLighthouse2F_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivineLighthouse2F_BGEvents),
    .bg_events = OlivineLighthouse2F_BGEvents,

    .obj_event_count = lengthof(OlivineLighthouse2F_ObjectEvents),
    .obj_events = OlivineLighthouse2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineLighthouse2F.h"

const struct TrainerObj TrainerGentlemanAlfred = {GENTLEMAN, ALFRED, EVENT_BEAT_GENTLEMAN_ALFRED, GentlemanAlfredSeenText, GentlemanAlfredBeatenText, 0, TrainerGentlemanAlfred_Script};
bool TrainerGentlemanAlfred_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GentlemanAlfredAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorHuey = {SAILOR, HUEY1, EVENT_BEAT_SAILOR_HUEY, SailorHueySeenText, SailorHueyBeatenText, 0, TrainerSailorHuey_Script};
bool TrainerSailorHuey_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_SAILOR_HUEY)
    endifjustbattled
    opentext
    checkflag(ENGINE_HUEY_READY_FOR_REMATCH)
    iftrue(WantsBattle)
    checkcellnum(PHONE_SAILOR_HUEY)
    iftrue(NumberAccepted)
    checkevent(EVENT_HUEY_ASKED_FOR_PHONE_NUMBER)
    iftrue(AskedBefore)
    setevent(EVENT_HUEY_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1);
    goto AskForNumber;
AskedBefore:
    scall_local(AskNumber2);
AskForNumber:
    askforphonenumber(PHONE_SAILOR_HUEY)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, NumberDeclined)
    gettrainername(STRING_BUFFER_3, SAILOR, HUEY1)
    scall_local(RegisteredNumber);
    goto NumberAccepted;
WantsBattle:
    scall_local(Rematch);
    winlosstext(SailorHueyBeatenText, 0)
    readmem(&gPlayer.HueyFightCount)
    ifequal(3, Fight3)
    ifequal(2, Fight2)
    ifequal(1, Fight1)
    ifequal(0, LoadFight0)
Fight3:
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(LoadFight3)
Fight2:
    checkevent(EVENT_BEAT_ELITE_FOUR)
    iftrue(LoadFight2)
Fight1:
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(SAILOR, HUEY1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.HueyFightCount, 1)
    clearflag(ENGINE_HUEY_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(SAILOR, HUEY2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.HueyFightCount, 2)
    clearflag(ENGINE_HUEY_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(SAILOR, HUEY3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.HueyFightCount, 3)
    clearflag(ENGINE_HUEY_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(SAILOR, HUEY4)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_HUEY_READY_FOR_REMATCH)
    checkevent(EVENT_HUEY_PROTEIN)
    iftrue(HasProtein)
    checkevent(EVENT_GOT_PROTEIN_FROM_HUEY)
    iftrue(SkipGift)
    scall_local(RematchGift);
    verbosegiveitem(PROTEIN, 1)
    iffalse(PackFull)
    setevent(EVENT_GOT_PROTEIN_FROM_HUEY)
    goto NumberAccepted;
SkipGift:
    s_end
HasProtein:
    opentext
    writetext(SailorHueyGiveProteinText)
    waitbutton
    verbosegiveitem(PROTEIN, 1)
    iffalse(PackFull)
    clearevent(EVENT_HUEY_PROTEIN)
    setevent(EVENT_GOT_PROTEIN_FROM_HUEY)
    goto NumberAccepted;
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
Rematch:
    jumpstd(RematchMScript)
    s_end
PackFull:
    setevent(EVENT_HUEY_PROTEIN)
    jumpstd(PackFullMScript)
    s_end
RematchGift:
    jumpstd(RematchGiftMScript)
    s_end
    SCRIPT_END
}
const txt_cmd_s SailorHueySeenText[] = {
    text_start("Men of the sea are"
        t_line "always spoiling"
        t_cont "for a good fight!"
        t_done )
};
const txt_cmd_s SailorHueyBeatenText[] = {
    text_start("Urf!"
        t_line "I lose!"
        t_done )
};
const txt_cmd_s SailorHueyUnusedText[] = {
    text_start("What power!"
        t_line "How would you like"
        t_para "to sail the seas"
        t_line "with me?"
        t_done )
};
const txt_cmd_s GentlemanAlfredSeenText[] = {
    text_start("Hm? This is no"
        t_line "place for playing."
        t_done )
};
const txt_cmd_s GentlemanAlfredBeatenText[] = {
    text_start("Ah! I can see that"
        t_line "you're serious."
        t_done )
};
const txt_cmd_s GentlemanAlfredAfterBattleText[] = {
    text_start("Up top is a #-"
        t_line "MON that keeps the"
        t_cont "LIGHTHOUSE lit."
        t_para "But I hear that"
        t_line "it's sick now and"
        t_para "can't be cured by"
        t_line "ordinary medicine."
        t_done )
};
const txt_cmd_s SailorHueyGiveProteinText[] = {
    text_start("Man! You're as"
        t_line "tough as ever!"
        t_para "Anyway, here's"
        t_line "that medicine from"
        t_cont "before."
        t_done )
    //db(0, 0) // filler
};
