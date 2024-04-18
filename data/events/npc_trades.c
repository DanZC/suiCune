#include "../../constants.h"

// npctrade: MACRO
// ; dialog set, requested mon, offered mon, nickname, dvs, item, OT ID, OT name, gender requested
// 	db \1, \2, \3, \4, \5, \6, \7
// 	dw \8
// 	db \9, \<10>, 0
// ENDM

#define npctrade(_d, _rm, _om, _nick, _dv1, _dv2, _item, _ot, _otname, _gr) {_d, _rm, _om, _nick, {_dv1, _dv2}, _item, _ot, _otname, _gr}

const struct NPCTrade NPCTrades[] = {
// entries correspond to NPCTRADE_* constants
    // table_width NPCTRADE_STRUCT_LENGTH, NPCTrades
    npctrade(TRADE_DIALOGSET_COLLECTOR, ABRA,       MACHOP,     "MUSCLE@@@@@", 0x37, 0x66, GOLD_BERRY,   37460, "MIKE@@@@@@@", TRADE_GENDER_EITHER),
    npctrade(TRADE_DIALOGSET_COLLECTOR, BELLSPROUT, ONIX,       "ROCKY@@@@@@", 0x96, 0x66, BITTER_BERRY, 48926, "KYLE@@@@@@@", TRADE_GENDER_EITHER),
    npctrade(TRADE_DIALOGSET_HAPPY,     KRABBY,     VOLTORB,    "VOLTY@@@@@@", 0x98, 0x88, PRZCUREBERRY, 29189, "TIM@@@@@@@@", TRADE_GENDER_EITHER),
    npctrade(TRADE_DIALOGSET_GIRL,      DRAGONAIR,  DODRIO,     "DORIS@@@@@@", 0x77, 0x66, SMOKE_BALL,     283, "EMY@@@@@@@@", TRADE_GENDER_FEMALE),
    npctrade(TRADE_DIALOGSET_NEWBIE,    HAUNTER,    XATU,       "PAUL@@@@@@@", 0x96, 0x86, MYSTERYBERRY, 15616, "CHRIS@@@@@@", TRADE_GENDER_EITHER),
    npctrade(TRADE_DIALOGSET_GIRL,      CHANSEY,    AERODACTYL, "AEROY@@@@@@", 0x96, 0x66, GOLD_BERRY,   26491, "KIM@@@@@@@@", TRADE_GENDER_EITHER),
    npctrade(TRADE_DIALOGSET_COLLECTOR, DUGTRIO,    MAGNETON,   "MAGGIE@@@@@", 0x96, 0x66, METAL_COAT,   50082, "FOREST@@@@@", TRADE_GENDER_EITHER),
};
static_assert(lengthof(NPCTrades) == NUM_NPC_TRADES);
