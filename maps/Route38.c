#include "../constants.h"
#include "../util/scripting.h"
#include "Route38.h"
//// EVENTS
enum {
    ROUTE38_STANDING_YOUNGSTER1 = 2,
    ROUTE38_LASS,
    ROUTE38_STANDING_YOUNGSTER2,
    ROUTE38_BEAUTY1,
    ROUTE38_SAILOR,
    ROUTE38_FRUIT_TREE,
    ROUTE38_BEAUTY2,
};

const Script_fn_t Route38_SceneScripts[] = {
    0,
};

const struct MapCallback Route38_MapCallbacks[] = {
    0,
};

const struct MapScripts Route38_MapScripts = {
    .scene_script_count = 0, // lengthof(Route38_SceneScripts),
    .scene_scripts = Route38_SceneScripts,

    .callback_count = 0, // lengthof(Route38_MapCallbacks),
    .callbacks = Route38_MapCallbacks,
};

static const struct CoordEvent Route38_CoordEvents[] = {
    0,
};

static const struct BGEvent Route38_BGEvents[] = {
    bg_event(33, 7, BGEVENT_READ, &Route38Sign),
    bg_event(5, 13, BGEVENT_READ, &Route38TrainerTips),
};

static const struct WarpEventData Route38_WarpEvents[] = {
    warp_event(35, 8, ROUTE_38_ECRUTEAK_GATE, 1),
    warp_event(35, 9, ROUTE_38_ECRUTEAK_GATE, 2),
};

static const struct ObjEvent Route38_ObjectEvents[] = {
    object_event(4, 1, SPRITE_STANDING_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerSchoolboyChad1, -1),
    object_event(15, 3, SPRITE_LASS, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerLassDana1, -1),
    object_event(12, 15, SPRITE_STANDING_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerBirdKeeperToby, -1),
    object_event(19, 9, SPRITE_BEAUTY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerBeautyValerie, -1),
    object_event(24, 5, SPRITE_SAILOR, SPRITEMOVEDATA_SPINCOUNTERCLOCKWISE, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 2, &TrainerSailorHarry, -1),
    object_event(12, 10, SPRITE_FRUIT_TREE, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &Route38FruitTree, -1),
    object_event(5, 8, SPRITE_BEAUTY, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 1, &TrainerBeautyOlivia, -1),
};

const struct MapEvents Route38_MapEvents = {
    .warp_event_count = lengthof(Route38_WarpEvents),
    .warp_events = Route38_WarpEvents,

    .coord_event_count = 0, // lengthof(Route38_CoordEvents),
    .coord_events = Route38_CoordEvents,

    .bg_event_count = lengthof(Route38_BGEvents),
    .bg_events = Route38_BGEvents,

    .obj_event_count = lengthof(Route38_ObjectEvents),
    .obj_events = Route38_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route38.h"

const struct TrainerObj TrainerBirdKeeperToby = {BIRD_KEEPER, TOBY, EVENT_BEAT_BIRD_KEEPER_TOBY, BirdKeeperTobySeenText, BirdKeeperTobyBeatenText, 0, TrainerBirdKeeperToby_Script};
bool TrainerBirdKeeperToby_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BirdKeeperTobyAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSailorHarry = {SAILOR, HARRY, EVENT_BEAT_SAILOR_HARRY, SailorHarrySeenText, SailorHarryBeatenText, 0, TrainerSailorHarry_Script};
bool TrainerSailorHarry_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(SailorHarryAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerLassDana1 = {LASS, DANA1, EVENT_BEAT_LASS_DANA, LassDana1SeenText, LassDana1BeatenText, 0, TrainerLassDana1_Script};
bool TrainerLassDana1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_LASS_DANA)
    endifjustbattled
    opentext
    checkflag(ENGINE_DANA_READY_FOR_REMATCH)
    iftrue(DanaRematch)
    checkflag(ENGINE_DANA_HAS_THUNDERSTONE)
    iftrue(TryGiveThunderstone)
    checkcellnum(PHONE_LASS_DANA)
    iftrue(NumberAccepted)
    checkevent(EVENT_DANA_ASKED_FOR_PHONE_NUMBER)
    iftrue(SecondTimeAsking)
    writetext(LassDanaMoomooMilkText)
    promptbutton
    setevent(EVENT_DANA_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskNumber1F);
    goto AskForPhoneNumber;
SecondTimeAsking:
    scall_local(AskNumber2F);
AskForPhoneNumber:
    askforphonenumber(PHONE_LASS_DANA)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, DeclinedPhoneNumber)
    gettrainername(STRING_BUFFER_3, LASS, DANA1)
    scall_local(RegisteredPhoneNumber);
    goto NumberAccepted;
DanaRematch:
    scall_local(Rematch);
    winlosstext(LassDana1BeatenText, 0)
    readmem(&gPlayer.DanaFightCount)
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
    checkflag(ENGINE_FLYPOINT_CIANWOOD)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(LASS, DANA1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.DanaFightCount, 1)
    clearflag(ENGINE_DANA_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(LASS, DANA2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.DanaFightCount, 2)
    clearflag(ENGINE_DANA_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(LASS, DANA3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.DanaFightCount, 3)
    clearflag(ENGINE_DANA_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(LASS, DANA4)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.DanaFightCount, 4)
    clearflag(ENGINE_DANA_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(LASS, DANA5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_DANA_READY_FOR_REMATCH)
    s_end
TryGiveThunderstone:
    scall_local(Gift);
    verbosegiveitem(THUNDERSTONE, 1)
    iffalse(NoRoomForThunderstone)
    clearflag(ENGINE_DANA_HAS_THUNDERSTONE)
    setevent(EVENT_DANA_GAVE_THUNDERSTONE)
    goto NumberAccepted;
NoRoomForThunderstone:
    goto PackFull;
AskNumber1F:
    jumpstd(AskNumber1FScript)
    s_end
AskNumber2F:
    jumpstd(AskNumber2FScript)
    s_end
RegisteredPhoneNumber:
    jumpstd(RegisteredNumberFScript)
    s_end
NumberAccepted:
    jumpstd(NumberAcceptedFScript)
    s_end
DeclinedPhoneNumber:
    jumpstd(NumberDeclinedFScript)
    s_end
PhoneFull:
    jumpstd(PhoneFullFScript)
    s_end
Rematch:
    jumpstd(RematchFScript)
    s_end
Gift:
    jumpstd(GiftFScript)
    s_end
PackFull:
    jumpstd(PackFullFScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerSchoolboyChad1 = {SCHOOLBOY, CHAD1, EVENT_BEAT_SCHOOLBOY_CHAD, SchoolboyChad1SeenText, SchoolboyChad1BeatenText, 0, TrainerSchoolboyChad1_Script};
bool TrainerSchoolboyChad1_Script(script_s* s) {
    SCRIPT_BEGIN
    loadvar(VAR_CALLERID, PHONE_SCHOOLBOY_CHAD)
    endifjustbattled
    opentext
    checkflag(ENGINE_CHAD_READY_FOR_REMATCH)
    iftrue(ChadRematch)
    checkcellnum(PHONE_SCHOOLBOY_CHAD)
    iftrue(HaveChadsNumber)
    checkevent(EVENT_CHAD_ASKED_FOR_PHONE_NUMBER)
    iftrue(SecondTimeAsking)
    writetext(SchoolboyChadSoManyTestsText)
    promptbutton
    setevent(EVENT_CHAD_ASKED_FOR_PHONE_NUMBER)
    scall_local(AskPhoneNumber1);
    goto AskToRegisterNumber;
SecondTimeAsking:
    scall_local(AskPhoneNumber2);
AskToRegisterNumber:
    askforphonenumber(PHONE_SCHOOLBOY_CHAD)
    ifequal(PHONE_CONTACTS_FULL, PhoneFull)
    ifequal(PHONE_CONTACT_REFUSED, SaidNo)
    gettrainername(STRING_BUFFER_3, SCHOOLBOY, CHAD1)
    scall_local(RegisteredChad);
    goto HaveChadsNumber;
ChadRematch:
    scall_local(Rematch);
    winlosstext(SchoolboyChad1BeatenText, 0)
    readmem(&gPlayer.ChadFightCount)
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
    checkflag(ENGINE_FLYPOINT_MAHOGANY)
    iftrue(LoadFight1)
LoadFight0:
    loadtrainer(SCHOOLBOY, CHAD1)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ChadFightCount, 1)
    clearflag(ENGINE_CHAD_READY_FOR_REMATCH)
    s_end
LoadFight1:
    loadtrainer(SCHOOLBOY, CHAD2)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ChadFightCount, 2)
    clearflag(ENGINE_CHAD_READY_FOR_REMATCH)
    s_end
LoadFight2:
    loadtrainer(SCHOOLBOY, CHAD3)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ChadFightCount, 3)
    clearflag(ENGINE_CHAD_READY_FOR_REMATCH)
    s_end
LoadFight3:
    loadtrainer(SCHOOLBOY, CHAD4)
    startbattle
    reloadmapafterbattle
    loadmem(&gPlayer.ChadFightCount, 4)
    clearflag(ENGINE_CHAD_READY_FOR_REMATCH)
    s_end
LoadFight4:
    loadtrainer(SCHOOLBOY, CHAD5)
    startbattle
    reloadmapafterbattle
    clearflag(ENGINE_CHAD_READY_FOR_REMATCH)
    s_end
AskPhoneNumber1:
    jumpstd(AskNumber1MScript)
    s_end
AskPhoneNumber2:
    jumpstd(AskNumber2MScript)
    s_end
RegisteredChad:
    jumpstd(RegisteredNumberMScript)
    s_end
HaveChadsNumber:
    jumpstd(NumberAcceptedMScript)
    s_end
SaidNo:
    jumpstd(NumberDeclinedMScript)
    s_end
PhoneFull:
    jumpstd(PhoneFullMScript)
    s_end
Rematch:
    jumpstd(RematchMScript)
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBeautyValerie = {BEAUTY, VALERIE, EVENT_BEAT_BEAUTY_VALERIE, BeautyValerieSeenText, BeautyValerieBeatenText, 0, TrainerBeautyValerie_Script};
bool TrainerBeautyValerie_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BeautyValerieAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerBeautyOlivia = {BEAUTY, OLIVIA, EVENT_BEAT_BEAUTY_OLIVIA, BeautyOliviaSeenText, BeautyOliviaBeatenText, 0, TrainerBeautyOlivia_Script};
bool TrainerBeautyOlivia_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(BeautyOliviaAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route38Sign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route38SignText)
    SCRIPT_END
}
bool Route38TrainerTips(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route38TrainerTipsText)
    SCRIPT_END
}
bool Route38FruitTree(script_s* s) {
    SCRIPT_BEGIN
    fruittree(FRUITTREE_ROUTE_38)
    SCRIPT_END
}
const txt_cmd_s BirdKeeperTobySeenText[] = {
    text_start("Fly high into the"
        t_line "sky, my beloved"
        t_cont "bird #MON!"
        t_done )
};
const txt_cmd_s BirdKeeperTobyBeatenText[] = {
    text_start("I feel like just"
        t_line "flying away now."
        t_done )
};
const txt_cmd_s BirdKeeperTobyAfterBattleText[] = {
    text_start("I plan to train in"
        t_line "CIANWOOD CITY to"
        t_para "teach my #MON"
        t_line "how to FLY."
        t_done )
};
const txt_cmd_s SchoolboyChad1SeenText[] = {
    text_start("Let me try some-"
        t_line "thing I learned"
        t_cont "today."
        t_done )
};
const txt_cmd_s SchoolboyChad1BeatenText[] = {
    text_start("I didn't study"
        t_line "enough, I guess."
        t_done )
};
const txt_cmd_s SchoolboyChadSoManyTestsText[] = {
    text_start("I have to take so"
        t_line "many tests, I"
        t_para "don't have much"
        t_line "time for #MON."
        t_para "So when I do get"
        t_line "to play, I really"
        t_cont "concentrate."
        t_done )
};
const txt_cmd_s LassDana1SeenText[] = {
    text_start("You seem to be"
        t_line "good at #MON."
        t_para "If you are, how"
        t_line "about giving me"
        t_cont "some advice?"
        t_done )
};
const txt_cmd_s LassDana1BeatenText[] = {
    text_start("I see. So you can"
        t_line "battle that way."
        t_done )
};
const txt_cmd_s LassDanaMoomooMilkText[] = {
    text_start("I know something"
        t_line "good!"
        t_para "MOOMOO FARM's milk"
        t_line "is famous for its"
        t_cont "flavor."
        t_done )
};
const txt_cmd_s BeautyValerieSeenText[] = {
    text_start("Hi! Aren't you a"
        t_line "cute trainer!"
        t_para "May I see your"
        t_line "#MON?"
        t_done )
};
const txt_cmd_s BeautyValerieBeatenText[] = {
    text_start("I'm glad I got to"
        t_line "see your #MON!"
        t_done )
};
const txt_cmd_s BeautyValerieAfterBattleText[] = {
    text_start("When I see #-"
        t_line "MON, it seems to"
        t_cont "soothe my nerves."
        t_done )
};
const txt_cmd_s SailorHarrySeenText[] = {
    text_start("I've been over-"
        t_line "seas, so I know"
        t_para "about all sorts of"
        t_line "#MON!"
        t_done )
};
const txt_cmd_s SailorHarryBeatenText[] = {
    text_start("Your skill is"
        t_line "world class!"
        t_done )
};
const txt_cmd_s SailorHarryAfterBattleText[] = {
    text_start("All kinds of peo-"
        t_line "ple around the"
        t_para "world live happily"
        t_line "with #MON."
        t_done )
};
const txt_cmd_s BeautyOliviaSeenText[] = {
    text_start("Don't you think my"
        t_line "#MON and I are"
        t_cont "beautiful?"
        t_done )
};
const txt_cmd_s BeautyOliviaBeatenText[] = {
    text_start("We drink MOOMOO"
        t_line "MILK every day."
        t_done )
};
const txt_cmd_s BeautyOliviaAfterBattleText[] = {
    text_start("MOOMOO MILK is"
        t_line "good for beauty"
        t_para "and health, but"
        t_line "inconveniently,"
        t_para "they only sell a"
        t_line "bottle at a time."
        t_done )
};
const txt_cmd_s Route38SignText[] = {
    text_start("ROUTE 38"
        t_para "OLIVINE CITY -"
        t_line "ECRUTEAK CITY"
        t_done )
};
const txt_cmd_s Route38TrainerTipsText[] = {
    text_start("TRAINER TIPS"
        t_para "If a #MON is"
        t_line "trying to evolve,"
        t_cont "you can stop it."
        t_para "Press the B But-"
        t_line "ton during evolu-"
        t_cont "tion."
        t_para "That startles the"
        t_line "#MON and stops"
        t_cont "its evolution."
        t_done )
    //db(0, 0) // filler
};
