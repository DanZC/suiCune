#include "../../constants.h"

// macros taken from pokered's data/sgb_packets.asm
// names taken from pandocs
// http://gbdev.gg8.se/wiki/articles/SGB_Functions#SGB_Palette_Commands

// #define sgb_pal_set(_0, _1, _2, _3)
// 	db (SGB_PAL_SET << 3) + 1
// 	dw PREDEFPAL_\1, PREDEFPAL_\2, PREDEFPAL_\3, PREDEFPAL_\4
// 	ds 7, 0
// ENDM

#define sgb_pal_set(_0, _1, _2, _3) {.set=(SGB_PAL_SET << 3) + 1, .colors={PREDEFPAL_##_0,PREDEFPAL_##_1,PREDEFPAL_##_2,PREDEFPAL_##_3}}

// sgb_pal01: MACRO
// 	db (SGB_PAL01 << 3) + 1
// ENDM

// sgb_pal23: MACRO
// 	db (SGB_PAL23 << 3) + 1
// ENDM

const struct PalSet PalPacket_GSTitleScreen =
	sgb_pal_set(GS_TITLE_SCREEN_0, GS_TITLE_SCREEN_1, GS_TITLE_SCREEN_2, GS_TITLE_SCREEN_3);

const struct PalSet PalPacket_MagnetTrain =
	sgb_pal_set(BETA_SHINY_GREENMON, CGB_BADGE, RB_BROWNMON, ROUTES);

const struct PalSet PalPacket_BetaPoker =
	sgb_pal_set(BETA_POKER_0, BETA_POKER_1, BETA_POKER_2, BETA_POKER_3);

const struct PalSet PalPacket_UnownPuzzle =
	sgb_pal_set(UNOWN_PUZZLE, UNOWN_PUZZLE, UNOWN_PUZZLE, UNOWN_PUZZLE);

const struct PalSet PalPacket_AllPal0 =
	sgb_pal_set(ROUTES, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_GSIntroShellderLapras =
	sgb_pal_set(GS_INTRO_SHELLDER_LAPRAS, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_BetaIntroLapras = // unreferenced
	sgb_pal_set(BETA_INTRO_LAPRAS, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_GSIntroJigglypuffPikachu = 
	sgb_pal_set(GS_INTRO_JIGGLYPUFF_PIKACHU_BG, GS_INTRO_JIGGLYPUFF_PIKACHU_OB, ROUTES, ROUTES);

const struct PalSet PalPacket_GSIntroStartersTransition = 
	sgb_pal_set(GS_INTRO_STARTERS_TRANSITION, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_BetaIntroVenusaur = 
	sgb_pal_set(BETA_INTRO_VENUSAUR, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_Pack = 
	sgb_pal_set(PACK, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_BetaPikachuMinigame = 
	sgb_pal_set(GS_INTRO_JIGGLYPUFF_PIKACHU_OB, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_PartyMenu = 
	sgb_pal_set(PARTY_ICON, HP_GREEN, HP_YELLOW, HP_RED);

const struct PalSet PalPacket_BattleGrayscale = 
	sgb_pal_set(BLACKOUT, BLACKOUT, BLACKOUT, BLACKOUT);

const struct PalSet PalPacket_Pokegear = 
	sgb_pal_set(POKEGEAR, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_Pack2 = // unreferenced
	sgb_pal_set(PACK, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_SlotMachine = 
	sgb_pal_set(SLOT_MACHINE_0, SLOT_MACHINE_1, SLOT_MACHINE_2, SLOT_MACHINE_3);

const struct PalSet PalPacket_BetaTitleScreen = 
	sgb_pal_set(BETA_LOGO_1, BETA_LOGO_2, DIPLOMA, RB_PURPLEMON);

const struct PalSet PalPacket_Diploma = 
	sgb_pal_set(DIPLOMA, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_TradeTube = 
	sgb_pal_set(TRADE_TUBE, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_GamefreakLogo = 
	sgb_pal_set(GS_INTRO_GAMEFREAK_LOGO, ROUTES, ROUTES, ROUTES);

const struct PalSet PalPacket_Pal01 = {
	// sgb_pal01
    (SGB_PAL01 << 3) + 1,
    .colors = {
        rgb(31, 31, 31),
        rgb( 0,  0,  0),
        rgb( 0,  0,  0),
        rgb( 0,  0,  0),
    // rept 6
    //     RGB 00, 00, 00
    // endr
    },
    // db 0
};

const struct PalSet PalPacket_Pal23 = {
	// sgb_pal23
    (SGB_PAL23 << 3) + 1,
    .colors = {
        rgb(31, 31, 31),
        rgb( 0,  0,  0),
        rgb( 0,  0,  0),
        rgb( 0,  0,  0),
    // rept 6
    //     RGB 00, 00, 00
    // endr
    },
	// db 0
};
