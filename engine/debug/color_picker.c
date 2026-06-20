#include "../../constants.h"
#include "color_picker.h"
#include "../../home/audio.h"
#include "../../home/copy.h"
#include "../../home/clear_sprites.h"
#include "../../home/delay.h"
#include "../../home/gfx.h"
#include "../../home/joypad.h"
#include "../../home/lcd.h"
#include "../../home/map.h"
#include "../../home/names.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/print_text.h"
#include "../../home/pokemon.h"
#include "../../charmap.h"
#include "../battle/read_trainer_attributes.h"
#include "../gfx/color.h"
#include "../gfx/place_graphic.h"
#include "../gfx/load_pics.h"
#include "../items/tmhm2.h"

// DebugColor_GFX tile IDs
enum {
    DEBUGTEST_TICKS_1 = 0x69, // $6a
    DEBUGTEST_TICKS_2,        // $6b
    DEBUGTEST_WHITE,          // $6c
    DEBUGTEST_LIGHT,          // $6d
    DEBUGTEST_DARK,           // $6e
    DEBUGTEST_BLACK,          // $6f
    DEBUGTEST_0,              // $70
    DEBUGTEST_1,              // $71
    DEBUGTEST_2,              // $72
    DEBUGTEST_3,              // $73
    DEBUGTEST_4,              // $74
    DEBUGTEST_5,              // $75
    DEBUGTEST_6,              // $76
    DEBUGTEST_7,              // $77
    DEBUGTEST_8,              // $78
    DEBUGTEST_9,              // $79
    DEBUGTEST_A,              // $7a
    DEBUGTEST_B,              // $7b
    DEBUGTEST_C,              // $7c
    DEBUGTEST_D,              // $7d
    DEBUGTEST_E,              // $7e
    DEBUGTEST_F,              // $7f
};

// DebugColorMain.Jumptable indexes
enum {
    DEBUGCOLORMAIN_INITSCREEN,  // 0
    DEBUGCOLORMAIN_UPDATESCREEN,  // 1
    DEBUGCOLORMAIN_UPDATEPALETTES,  // 2
    DEBUGCOLORMAIN_JOYPAD,  // 3
    DEBUGCOLORMAIN_INITTMHM,  // 4
    DEBUGCOLORMAIN_TMHMJOYPAD,  // 5
};

static inline void DebugColor_PreviousRGBColor(void);
static inline void DebugColor_NextRGBColor(void);

static void DebugColor_InitMonOrTrainerColor(bool is_shiny);
static void DebugColor_InitMonColor(bool is_shiny);
static void DebugColor_InitTrainerColor(void);
static void DebugColor_InitColor(uint8_t* de, const uint16_t* pal);
static void DebugColor_InitVRAM(void);
static void DebugColor_LoadGFX(void);
static void DebugColor_InitPalettes(void);

static void DebugColorMain(void);
static void DebugColor_InitScreen(void);
static void DebugColor_LoadRGBMeter(void);
static void DebugColor_SetRGBMeter(void);
static void DebugColor_UpdateScreen(void);
static void DebugColor_UpdatePalettes(void);
static void DebugColor_PrintHexColor(tile_t* hl, const uint8_t* de);
static void DebugColor_Joypad(void);
static void DebugColor_SelectColorBox(void);
static void DebugColor_ChangeRedValue(void);
static void DebugColor_ChangeGreenValue(void);
static void DebugColor_ChangeBlueValue(void);
static void DebugColor_UpdateRGBColor(uint8_t* hl);
static void DebugColor_PreviousRGBColor(void);
static void DebugColor_NextRGBColor(void);
static void DebugColor_InitTMHM(void);
static void DebugColor_TMHMJoypad(void);
static void DebugColor_PrintTMHMMove(void);
static void DebugColor_CalculatePalette(void);
static void DebugColor_CalculateRGB(const uint8_t* de);
static void DebugColor_BackupSpriteColors(void);
static void DebugColor_LoadPalettes_White_Col1_Col2_Black(void* hl, const void* de, uint8_t c);
static void DebugColor_FillBoxWithByte(tile_t* hl, uint8_t c, uint8_t b, tile_t a);
static void DebugColor_PlaceCursor(void);

static void DebugTileset_DrawColorSwatch(uint16_t de, uint8_t a);
static void DebugColor_DrawAttributeSwatch(uint16_t de);
static void v_DebugColor_DrawSwatch(uint8_t* de, uint8_t a);
static void DebugTileset_LoadRGBMeter(void);
static void DebugTileset_LoadPalettes(void);
static void DebugColorMain2(void);
static void DebugTileset_UpdatePalettes(void);
static void DebugTileset_Joypad(void);
static void DebugTileset_SelectColorBox(void);
static void DebugTileset_ChangeRedValue(void);
static void DebugTileset_ChangeGreenValue(void);
static void DebugTileset_ChangeBlueValue(void);
static void DebugTileset_UpdateRGBColor(uint8_t* hl);
static inline void DebugTileset_PreviousRGBColor(void);
static inline void DebugTileset_NextRGBColor(void);
static void DebugTileset_CalculatePalette(void);

static const char DebugColor_AreYouFinishedString[] = 
           "Done?" //db ['"おわりますか？"'];  // Are you finished?
    t_next "YES..<DEBUGTEST_A>" //next ['"はい<DOT><DOT><DOT>"', 'DEBUGTEST_A']  // YES...(A)
    t_next "NO...<DEBUGTEST_B>@";  //next ['"いいえ<DOT><DOT>"', 'DEBUGTEST_B']  // NO..(B)
    //db ['"@"'];

static const char Palette_DebugBG[] = "gfx/debug/bg.pal";
static const char Palette_DebugOB[] = "gfx/debug/ob.pal";

static const char DebugColor_UpArrowGFX[] = "gfx/debug/up_arrow.png";
static const char DebugColor_GFX[] = "gfx/debug/color_test.png";

void DebugColorPicker(void){
//  //  unreferenced
//  A debug menu to test monster and trainer palettes at runtime.
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    // LDH_A_addr(hSGB);
    // AND_A_A;
    // RET_Z ;
    if(hram.hCGB == 0 && hram.hSGB == 0)
        return;

// cgb:
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram.hInMenu;
    // LD_A(TRUE);
    // LDH_addr_A(hInMenu);
    hram.hInMenu = TRUE;

    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aDebugColor_InitVRAM);
    DebugColor_InitVRAM();
    // CALL(aDebugColor_LoadGFX);
    DebugColor_LoadGFX();
    // CALL(aDebugColor_InitPalettes);
    DebugColor_InitPalettes();
    // CALL(aDebugColor_InitMonOrTrainerColor);
    DebugColor_InitMonOrTrainerColor(false);
    // CALL(aEnableLCD);
    EnableLCD();
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);

    // XOR_A_A;  // DEBUGCOLORMAIN_INITSCREEN
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = DEBUGCOLORMAIN_INITSCREEN;
    // LD_addr_A(wDebugColorCurMon);
    wram->wDebugColorCurMon = 0;
    // LD_addr_A(wDebugColorIsShiny);
    wram->wDebugColorIsShiny = 0;

    while(!bit_test(wram->wJumptableIndex, 7)) {
    // loop:
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto exit;
        // CALL(aDebugColorMain);
        DebugColorMain();
        // CALL(aDebugColor_PlaceCursor);
        DebugColor_PlaceCursor();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// exit:
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram.hInMenu = inMenu;
    // RET;
}

static void DebugColor_InitMonOrTrainerColor(bool is_shiny){
    // LD_A_addr(wDebugColorIsTrainer);
    // AND_A_A;
    // JR_NZ (mDebugColor_InitTrainerColor);
    if(wram->wDebugColorIsTrainer)
        return DebugColor_InitTrainerColor();
    // LD_HL(mPokemonPalettes);
// fallthrough

    return DebugColor_InitMonColor(is_shiny);
}

static void DebugColor_InitMonColor(bool is_shiny){
    uint16_t buffer[NUM_PAL_COLORS];
    // LD_DE(wDebugOriginalColors);
    uint8_t* de = wram->wDebugOriginalColors;
    // LD_C(NUM_POKEMON + 1);

    for(uint32_t i = 0; i < NUM_POKEMON + 1; ++i) {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aDebugColor_InitColor);
        DebugColor_InitColor(de, GetMonNormalOrShinyPalettePointerCustom(buffer, i, is_shiny));
        
        // POP_HL;
        // LD_BC(8);
        // ADD_HL_BC;
        de += 4;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

static void DebugColor_InitTrainerColor(void){
    uint16_t buffer[NUM_PAL_COLORS];
    // LD_HL(mTrainerPalettes);
    // LD_DE(wDebugOriginalColors);
    uint8_t* de = wram->wDebugOriginalColors;
    // LD_C(NUM_TRAINER_CLASSES + 1);

    for(uint32_t i = 0; i < NUM_TRAINER_CLASSES + 1; ++i) {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aDebugColor_InitColor);
        DebugColor_InitColor(de, GetTrainerPalettePointer(buffer, i));
        // POP_HL;
        // LD_BC(4);
        // ADD_HL_BC;
        de += 4;

        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

static void DebugColor_InitColor(uint8_t* de, const uint16_t *pal){
    // for(int rept = 0; rept < 3; rept++){
    // LD_A(BANK(aPokemonPalettes));  // aka BANK(TrainerPalettes)
    // CALL(aGetFarByte);
    // LD_de_A;
    // INC_DE;
    // INC_HL;
    // }
    // LD_A(BANK(aPokemonPalettes));  // aka BANK(TrainerPalettes)
    // CALL(aGetFarByte);
    de[0] = LOW(pal[0]);
    de[1] = HIGH(pal[0]);
    de[2] = LOW(pal[1]);
    de[3] = HIGH(pal[1]);
    // LD_de_A;
    // INC_DE;
    // RET;
}

static void DebugColor_InitVRAM(void){
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(VRAM_Begin);
    // LD_BC(VRAM_End - VRAM_Begin);
    // XOR_A_A;
    // CALL(aByteFill);

    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // LD_HL(VRAM_Begin);
    // LD_BC(VRAM_End - VRAM_Begin);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(vram, sizeof(*vram), 0x0);

    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0);

    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0);

    // CALL(aClearSprites);
    ClearSprites();
    // RET;
}

static void DebugColor_LoadGFX(void){
    // LD_HL(mDebugColor_GFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * DEBUGTEST_TICKS_1);
    // LD_BC(22 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * DEBUGTEST_TICKS_1, DebugColor_GFX, 0, 22);
    CopyBytes(vram->vTiles2 + LEN_2BPP_TILE * CHAR_SPACE, vram->vTiles2 + LEN_2BPP_TILE * DEBUGTEST_BLACK, LEN_2BPP_TILE);

    // LD_HL(mDebugColor_UpArrowGFX);
    // LD_DE(vTiles0);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0, DebugColor_UpArrowGFX, 0, 1);

//  Invert the font colors.
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // LD_HL(vTiles1);
    uint8_t* hl = vram->vTiles1;
    // LD_BC(0x80 * LEN_2BPP_TILE);
    uint16_t bc = 0x80 * LEN_2BPP_TILE;

    do {
    // loop:
        // LD_A_hl;
        // XOR_A(0xff);
        // LD_hli_A;
        *hl ^= 0xff;
        hl++;
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;

}

static void DebugColor_InitPalettes(void){
    uint8_t buffer[8 * PALETTE_SIZE];
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram.hCGB == 0)
        return;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals2));
    // LDH_addr_A(rSVBK);

    // LD_HL(mPalette_DebugBG);
    // LD_DE(wBGPals2);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    LoadPaletteAssetColorsToArray(
        wram->wBGPals2,
        Palette_DebugBG,
        0, 16 * NUM_PAL_COLORS
    );

    // LD_A(1 << rBGPI_AUTO_INCREMENT);
    // LDH_addr_A(rBGPI);
    gb_write(rBGPI, 1 << rBGPI_AUTO_INCREMENT);
    // LD_HL(mPalette_DebugBG);
    // LD_C(8 * PALETTE_SIZE);
    uint8_t c = 8 * PALETTE_SIZE;
    // XOR_A_A;

    do {
    // bg_loop:
        // LDH_addr_A(rBGPD);
        gb_write(rBGPD, 0);
        // DEC_C;
        // IF_NZ goto bg_loop;
    } while(--c != 0);

    // LD_A(1 << rOBPI_AUTO_INCREMENT);
    // LDH_addr_A(rOBPI);
    gb_write(rOBPI, 1 << rOBPI_AUTO_INCREMENT);
    // LD_HL(mPalette_DebugOB);
    LoadPaletteAssetColorsToArray(
        buffer,
        Palette_DebugOB,
        0, 16 * NUM_PAL_COLORS
    );
    // LD_C(8 * PALETTE_SIZE);

    for(uint32_t i = 0; i < 8 * PALETTE_SIZE; ++i) {
    // ob_loop:
        // LD_A_hli;
        // LDH_addr_A(rOBPD);
        gb_write(rOBPD, buffer[i]);
        // DEC_C;
        // IF_NZ goto ob_loop;
    }

    // LD_A(LOW((1 << 0) * 20 + (1 << 5) * 20 + (1 << 10) * 20));
    // LD_addr_A(wDebugLightColor + 0);
    wram->wDebugLightColor[0] = LOW((1 << 0) * 20 + (1 << 5) * 20 + (1 << 10) * 20);
    // LD_A(HIGH((1 << 0) * 20 + (1 << 5) * 20 + (1 << 10) * 20));
    // LD_addr_A(wDebugLightColor + 1);
    wram->wDebugLightColor[1] = HIGH((1 << 0) * 20 + (1 << 5) * 20 + (1 << 10) * 20);
    // LD_A(LOW((1 << 0) * 10 + (1 << 5) * 10 + (1 << 10) * 10));
    // LD_addr_A(wDebugDarkColor + 0);
    wram->wDebugDarkColor[0] = LOW((1 << 0) * 10 + (1 << 5) * 10 + (1 << 10) * 10);
    // LD_A(HIGH((1 << 0) * 10 + (1 << 5) * 10 + (1 << 10) * 10));
    // LD_addr_A(wDebugDarkColor + 1);
    wram->wDebugDarkColor[1] = HIGH((1 << 0) * 10 + (1 << 5) * 10 + (1 << 10) * 10);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

static inline uint8_t DebugColorMain_SetMaxNum(void);

static void DebugColorMain(void){
    // CALL(aJoyTextDelay);
    JoyTextDelay();
    // LD_A_addr(wJumptableIndex);
    // CP_A(DEBUGCOLORMAIN_INITTMHM);
    // IF_NC goto no_start_select;
    if(wram->wJumptableIndex < DEBUGCOLORMAIN_INITTMHM) {
        uint8_t a;
        // LD_HL(hJoyLast);
        // LD_A_hl;
        // AND_A(SELECT);
        // IF_NZ goto NextMon;
        if(hram.hJoyLast & SELECT) {
        // NextMon:
            // CALL(aDebugColor_BackupSpriteColors);
            DebugColor_BackupSpriteColors();
            // CALL(aDebugColorMain_SetMaxNum);
            // LD_E_A;
            // LD_A_addr(wDebugColorCurMon);
            a = wram->wDebugColorCurMon;
            // INC_A;
            // CP_A_E;
            // IF_C goto SwitchMon;
            if(++a >= DebugColorMain_SetMaxNum()) {
                // XOR_A_A;
                a = 0;
            }
            goto SwitchMon;
        }
        // LD_A_hl;
        // AND_A(START);
        // IF_NZ goto PreviousMon;
        if(hram.hJoyLast & START) {
        // PreviousMon:
            // CALL(aDebugColor_BackupSpriteColors);
            DebugColor_BackupSpriteColors();
            // LD_A_addr(wDebugColorCurMon);
            // DEC_A;
            a = wram->wDebugColorCurMon;
            // CP_A(-1);
            // IF_NZ goto SwitchMon;
            if(a-- == 0) {
                // CALL(aDebugColorMain_SetMaxNum);
                // DEC_A;
                a = DebugColorMain_SetMaxNum() - 1;
            }
            // goto SwitchMon;
        SwitchMon:
            // LD_addr_A(wDebugColorCurMon);
            wram->wDebugColorCurMon = a;
            // LD_A(DEBUGCOLORMAIN_INITSCREEN);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = DEBUGCOLORMAIN_INITSCREEN;
            // RET;
            return;
        }
    }

// no_start_select:
    //jumptable ['.Jumptable', 'wJumptableIndex']
    switch(wram->wJumptableIndex) {
    // Jumptable:
    //  entries correspond to DEBUGCOLORMAIN_* constants
        case DEBUGCOLORMAIN_INITSCREEN: DebugColor_InitScreen(); fallthrough;
        case DEBUGCOLORMAIN_UPDATESCREEN: return DebugColor_UpdateScreen();
        case DEBUGCOLORMAIN_UPDATEPALETTES: return DebugColor_UpdatePalettes();
        case DEBUGCOLORMAIN_JOYPAD: return DebugColor_Joypad();
        case DEBUGCOLORMAIN_INITTMHM: return DebugColor_InitTMHM();
        case DEBUGCOLORMAIN_TMHMJOYPAD: return DebugColor_TMHMJoypad();
    }
}

static inline uint8_t DebugColorMain_SetMaxNum(void){
//  Looping back around the pic set.
    // LD_A_addr(wDebugColorIsTrainer);
    // AND_A_A;
    // IF_NZ goto trainer;
    if(wram->wDebugColorIsTrainer) {
    // trainer:
        // LD_A(NUM_TRAINER_CLASSES);  // MYSTICALMAN
        // RET;
        return NUM_TRAINER_CLASSES;
    }
//  mon
    // LD_A(NUM_POKEMON);  // CELEBI
    // RET;
    return NUM_POKEMON;
}

static void DebugColor_InitScreen(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(DEBUGTEST_BLACK);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, DEBUGTEST_BLACK);
    // hlcoord(1, 3, wTilemap);
    // LD_BC((7 << 8) | 18);
    // LD_A(DEBUGTEST_WHITE);
    // CALL(aDebugColor_FillBoxWithByte);
    DebugColor_FillBoxWithByte(coord(1, 3, wram->wTilemap), 18, 7, DEBUGTEST_WHITE);
    // hlcoord(11, 0, wTilemap);
    // LD_BC((2 << 8) | 3);
    // LD_A(DEBUGTEST_LIGHT);
    // CALL(aDebugColor_FillBoxWithByte);
    DebugColor_FillBoxWithByte(coord(11, 0, wram->wTilemap), 3, 2, DEBUGTEST_WHITE);
    // hlcoord(16, 0, wTilemap);
    // LD_BC((2 << 8) | 3);
    // LD_A(DEBUGTEST_DARK);
    // CALL(aDebugColor_FillBoxWithByte);
    DebugColor_FillBoxWithByte(coord(16, 0, wram->wTilemap), 3, 2, DEBUGTEST_DARK);
    // CALL(aDebugColor_LoadRGBMeter);
    DebugColor_LoadRGBMeter();
    // CALL(aDebugColor_SetRGBMeter);
    DebugColor_SetRGBMeter();
    // LD_A_addr(wDebugColorCurMon);
    // INC_A;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wDebugColorCurMon + 1;
    // LD_addr_A(wTextDecimalByte);
    wram->wTextDecimalByte = wram->wDebugColorCurMon + 1;
    // hlcoord(0, 1, wTilemap);
    // LD_DE(wTextDecimalByte);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum(coord(0, 1, wram->wTilemap), &wram->wTextDecimalByte, PRINTNUM_LEADINGZEROS | 1, 3);
    // LD_A_addr(wDebugColorIsTrainer);
    // AND_A_A;
    // IF_NZ goto trainer;
    if(wram->wDebugColorIsTrainer) {
    // trainer:
        // LD_A_addr(wTextDecimalByte);
        // LD_addr_A(wTrainerClass);
        wram->wTrainerClass = wram->wTextDecimalByte;
        // CALLFAR(aGetTrainerAttributes);
        GetTrainerAttributes(wram->wTrainerClass);
        // LD_DE(wStringBuffer1);
        // hlcoord(4, 1, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(wram->wOTClassName, coord(4, 1, wram->wTilemap));
        // LD_DE(vTiles2);
        // CALLFAR(aGetTrainerPic);
        GetTrainerPic(vram->vTiles2, wram->wTrainerClass);
        // XOR_A_A;
        // LD_addr_A(wTempEnemyMonSpecies);
        wram->wTempEnemyMonSpecies = 0;
        // LDH_addr_A(hGraphicStartTile);
        hram.hGraphicStartTile = 0;
        // hlcoord(2, 3, wTilemap);
        // LD_BC((7 << 8) | 7);
        // PREDEF(pPlaceGraphic);
        PlaceGraphicYStagger(coord(2, 3, wram->wTilemap), 7, 7);
    }
    else {
    //  mon
        species_t species = wram->wTextDecimalByte;
        // LD_A(UNOWN_A);
        // LD_addr_A(wUnownLetter);
        wram->wUnownLetter = UNOWN_A;
        // CALL(aGetPokemonName);
        // hlcoord(4, 1, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(GetPokemonName(species), coord(4, 1, wram->wTilemap));
        // XOR_A_A;
        // LD_addr_A(wBoxAlignment);
        wram->wBoxAlignment = 0;
        // hlcoord(12, 3, wTilemap);
        // CALL(av_PrepMonFrontpic);
        v_PrepMonFrontpic(coord(12, 3, wram->wTilemap));
        // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
        // PREDEF(pGetMonBackpic);
        GetMonBackpic(vram->vTiles2 + LEN_2BPP_TILE * 0x31, species);
        // LD_A(0x31);
        // LDH_addr_A(hGraphicStartTile);
        hram.hGraphicStartTile = 0x31;
        // hlcoord(2, 4, wTilemap);
        // LD_BC((6 << 8) | 6);
        // PREDEF(pPlaceGraphic);
        PlaceGraphicYStagger(coord(2, 4, wram->wTilemap), 6, 6);

        static const char ShinyText[] = "SHINY<DEBUGTEST_BLACK><DEBUGTEST_BLACK>@";
            //db ['"レア"', 'DEBUGTEST_BLACK', 'DEBUGTEST_BLACK', '"@"'];  // Rare (shiny)
        static const char NormalText[] = "NORMAL@";
            //db ['"ノーマル@"'];  // Normal
        static const char SwitchText[] = "<DEBUGTEST_A> Switch▶@";
            //db ['DEBUGTEST_A', '"きりかえ▶@"'];  // (A) Switches
        // LD_A_addr(wDebugColorIsShiny);
        // AND_A_A;
        // IF_Z goto normal;
        if(wram->wDebugColorIsShiny) {
        //  shiny
            // LD_DE(mDebugColor_InitScreen_ShinyText);
            // goto place_text;
            PlaceStringSimple(U82C(ShinyText), coord(9, 17, wram->wTilemap));
        }
        else {
        // normal:
            // LD_DE(mDebugColor_InitScreen_NormalText);
            PlaceStringSimple(U82C(NormalText), coord(9, 17, wram->wTilemap));
        }

    // place_text:
        // hlcoord(7, 17, wTilemap);
        // CALL(aPlaceString);
        // hlcoord(0, 17, wTilemap);
        // LD_DE(mDebugColor_InitScreen_SwitchText);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(SwitchText), coord(0, 17, wram->wTilemap));
        // goto done;
    }

// done:
    // LD_A(DEBUGCOLORMAIN_UPDATESCREEN);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = DEBUGCOLORMAIN_UPDATESCREEN;
    // RET;
}

static inline void DebugColor_LoadRGBMeter_load_meter(uint8_t* de, tile_t* hl, uint8_t a);

static void DebugColor_LoadRGBMeter(void){
    // decoord(0, 11, wAttrmap);
    // hlcoord(2, 11, wTilemap);
    // LD_A(1);
    // CALL(aDebugColor_LoadRGBMeter_load_meter);
    DebugColor_LoadRGBMeter_load_meter(coord(0, 11, wram->wAttrmap), coord(2, 11, wram->wTilemap), 1);
    // decoord(0, 13, wAttrmap);
    // hlcoord(2, 13, wTilemap);
    // LD_A(2);
    // CALL(aDebugColor_LoadRGBMeter_load_meter);
    DebugColor_LoadRGBMeter_load_meter(coord(0, 13, wram->wAttrmap), coord(2, 13, wram->wTilemap), 2);
    // decoord(0, 15, wAttrmap);
    // hlcoord(2, 15, wTilemap);
    // LD_A(3);
    DebugColor_LoadRGBMeter_load_meter(coord(0, 15, wram->wAttrmap), coord(2, 15, wram->wTilemap), 3);
}

static inline void DebugColor_LoadRGBMeter_load_meter(uint8_t* de, tile_t* hl, uint8_t a) {
    // PUSH_AF;
    // LD_A(DEBUGTEST_TICKS_1);
    // LD_hli_A;
    *(hl++) = DEBUGTEST_TICKS_1;
    // LD_BC(15);
    // LD_A(DEBUGTEST_TICKS_2);
    // CALL(aByteFill);
    ByteFill(hl, 15, DEBUGTEST_TICKS_2);
    // LD_L_E;
    // LD_H_D;
    // POP_AF;
    // LD_BC(20 * 2);
    // CALL(aByteFill);
    ByteFill(de, SCREEN_WIDTH * 2, a);
    // RET;
}

static void DebugColor_SetRGBMeter(void){
    // LD_A_addr(wDebugColorCurMon);
    // INC_A;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(wDebugOriginalColors);
    // ADD_HL_DE;
    const uint8_t* hl = wram->wDebugOriginalColors + ((wram->wDebugColorCurMon + 1) << 2);
    // LD_DE(wDebugMiddleColors);
    // LD_BC(4);
    // CALL(aCopyBytes);
    CopyBytes(wram->wDebugMiddleColors, hl, 4);
    // XOR_A_A;
    // LD_addr_A(wDebugColorRGBJumptableIndex);
    wram->wDebugColorRGBJumptableIndex = 0;
    // LD_addr_A(wDebugColorCurColor);
    wram->wDebugColorCurColor = 0;
    // LD_DE(wDebugLightColor);
    // CALL(aDebugColor_CalculateRGB);
    DebugColor_CalculateRGB(wram->wDebugLightColor);
    // RET;
}

static void DebugColor_UpdateScreen(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto sgb;
    if(hram.hCGB != 0) {
        // LD_A(2);
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_UPDATE_ATTRS;
        // CALL(aDelayFrame);
        DelayFrame();
#if !ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
#endif // ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
    }

// sgb:
    // CALL(aWaitBGMap);
    WaitBGMap();

    // LD_A(DEBUGCOLORMAIN_UPDATEPALETTES);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = DEBUGCOLORMAIN_UPDATEPALETTES;
    // RET;
}

static void DebugColor_UpdatePalettes(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto sgb;

    if(hram.hCGB != 0) {
    //  cgb
        // LDH_A_addr(rSVBK);
        // PUSH_AF;
        // LD_A(BANK(wBGPals2));
        // LDH_addr_A(rSVBK);

        // LD_HL(wBGPals2);
        // LD_DE(wDebugMiddleColors);
        // LD_C(1);
        // CALL(aDebugColor_LoadPalettes_White_Col1_Col2_Black);
        DebugColor_LoadPalettes_White_Col1_Col2_Black(wram->wBGPals2, wram->wDebugMiddleColors, 1);

        // hlcoord(10, 2, wTilemap);
        // LD_DE(wDebugLightColor);
        // CALL(aDebugColor_PrintHexColor);
        DebugColor_PrintHexColor(coord(10, 2, wram->wTilemap), wram->wDebugLightColor);
        // hlcoord(15, 2, wTilemap);
        // LD_DE(wDebugDarkColor);
        // CALL(aDebugColor_PrintHexColor);
        DebugColor_PrintHexColor(coord(15, 2, wram->wTilemap), wram->wDebugDarkColor);

        // LD_A(TRUE);
        // LDH_addr_A(hCGBPalUpdate);
        hram.hCGBPalUpdate = TRUE;

        // LD_A(DEBUGCOLORMAIN_JOYPAD);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEBUGCOLORMAIN_JOYPAD;

        // POP_AF;
        // LDH_addr_A(rSVBK);
        // RET;
        return;
    }

// sgb:
    // LD_HL(wSGBPals);
    // LD_A(1);
    // LD_hli_A;
    // LD_A(LOW(PALRGB_WHITE));
    // LD_hli_A;
    // LD_A(HIGH(PALRGB_WHITE));
    // LD_hli_A;
    // LD_A_addr(wDebugLightColor + 0);
    // LD_hli_A;
    // LD_A_addr(wDebugLightColor + 1);
    // LD_hli_A;
    // LD_A_addr(wDebugDarkColor + 0);
    // LD_hli_A;
    // LD_A_addr(wDebugDarkColor + 1);
    // LD_hli_A;
    // XOR_A_A;
    // LD_hli_A;
    // LD_hli_A;
    // LD_hl_A;

    // LD_HL(wSGBPals);
    // CALL(aDebugColor_PushSGBPals);

    // hlcoord(10, 2, wTilemap);
    // LD_DE(wDebugLightColor);
    // CALL(aDebugColor_PrintHexColor);
    // hlcoord(15, 2, wTilemap);
    // LD_DE(wDebugDarkColor);
    // CALL(aDebugColor_PrintHexColor);

    // LD_A(DEBUGCOLORMAIN_JOYPAD);
    // LD_addr_A(wJumptableIndex);
    // RET;

}

static void DebugColor_PrintHexColor_place_tile(tile_t* hl, tile_t a){
    // AND_A(0xf);
    // ADD_A(DEBUGTEST_0);
    // LD_hld_A;
    *hl = (a & 0xf) + DEBUGTEST_0;
    // RET;
}

static void DebugColor_PrintHexColor(tile_t* hl, const uint8_t* de){
    // INC_HL;
    // INC_HL;
    // INC_HL;
    // LD_A_de;
    // CALL(aDebugColor_PrintHexColor_place_tile);
    DebugColor_PrintHexColor_place_tile(&hl[3], de[0]);
    // LD_A_de;
    // SWAP_A;
    // CALL(aDebugColor_PrintHexColor_place_tile);
    DebugColor_PrintHexColor_place_tile(&hl[2], de[0] >> 4);
    // INC_DE;
    // LD_A_de;
    // CALL(aDebugColor_PrintHexColor_place_tile);
    DebugColor_PrintHexColor_place_tile(&hl[1], de[1]);
    // LD_A_de;
    // SWAP_A;
    DebugColor_PrintHexColor_place_tile(&hl[0], de[1] >> 4);
}

static void DebugColor_Joypad(void){
    // LDH_A_addr(hJoyLast);
    // AND_A(B_BUTTON);
    // IF_NZ goto tmhm;
    if(hram.hJoyLast & B_BUTTON) {
    // tmhm:
    //  Enter the TM/HM checker.
        if(wram->wDebugColorIsTrainer)
            return;
        // LD_A(DEBUGCOLORMAIN_INITTMHM);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEBUGCOLORMAIN_INITTMHM;
        // RET;
        return;
    }
    // LDH_A_addr(hJoyLast);
    // AND_A(A_BUTTON);
    // IF_NZ goto toggle_shiny;
    if(hram.hJoyLast & A_BUTTON) {
    // toggle_shiny:
    //  Toggle between the normal and shiny mon colors.
        // LD_A_addr(wDebugColorIsTrainer);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wDebugColorIsTrainer)
            return;

        // LD_A_addr(wDebugColorIsShiny);
        // XOR_A(0b00000100);
        // LD_addr_A(wDebugColorIsShiny);
        wram->wDebugColorIsShiny ^= 0b00000100;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(mPokemonPalettes);
        // ADD_HL_BC;
        // CALL(aDebugColor_InitMonColor);
        DebugColor_InitMonColor(wram->wDebugColorIsShiny != 0);

        // LD_A(DEBUGCOLORMAIN_INITSCREEN);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEBUGCOLORMAIN_INITSCREEN;
        // RET;
        return;
    }
    // LD_A_addr(wDebugColorRGBJumptableIndex);
    // maskbits(4, 0);  // .PointerTable length
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mDebugColor_Joypad_PointerTable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;

// PointerTable:
    switch(wram->wDebugColorRGBJumptableIndex & 3) {
        case 0: return DebugColor_SelectColorBox(); //dw ['DebugColor_SelectColorBox'];
        case 1: return DebugColor_ChangeRedValue(); //dw ['DebugColor_ChangeRedValue'];
        case 2: return DebugColor_ChangeGreenValue(); //dw ['DebugColor_ChangeGreenValue'];
        case 3: return DebugColor_ChangeBlueValue(); //dw ['DebugColor_ChangeBlueValue'];
    }
}

static void DebugColor_SelectColorBox(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mDebugColor_NextRGBColor);
    if(hram.hJoyLast & D_DOWN)
        return DebugColor_NextRGBColor();
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto light;
    if(hram.hJoyLast & D_LEFT) {
    // light:
        // XOR_A_A;  // FALSE
        // LD_addr_A(wDebugColorCurColor);
        wram->wDebugColorCurColor = 0;
        // LD_DE(wDebugLightColor);
        // CALL(aDebugColor_CalculateRGB);
        DebugColor_CalculateRGB(wram->wDebugLightColor);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto dark;
    if(hram.hJoyLast & D_RIGHT) {
    // dark:
        // LD_A(TRUE);
        // LD_addr_A(wDebugColorCurColor);
        wram->wDebugColorCurColor = TRUE;
        // LD_DE(wDebugDarkColor);
        // CALL(aDebugColor_CalculateRGB);
        DebugColor_CalculateRGB(wram->wDebugDarkColor);
        // RET;
        return;
    }
    // RET;
}

static void DebugColor_ChangeRedValue(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mDebugColor_NextRGBColor);
    if(hram.hJoyLast & D_DOWN)
        return DebugColor_NextRGBColor();
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mDebugColor_PreviousRGBColor);
    if(hram.hJoyLast & D_UP)
        return DebugColor_PreviousRGBColor();
    // LD_HL(wDebugRedChannel);
    // JR(mDebugColor_UpdateRGBColor);
    return DebugColor_UpdateRGBColor(&wram->wDebugRedChannel);
}

static void DebugColor_ChangeGreenValue(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mDebugColor_NextRGBColor);
    if(hram.hJoyLast & D_DOWN)
        return DebugColor_NextRGBColor();
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mDebugColor_PreviousRGBColor);
    if(hram.hJoyLast & D_UP)
        return DebugColor_PreviousRGBColor();
    // LD_HL(wDebugGreenChannel);
    // JR(mDebugColor_UpdateRGBColor);
    return DebugColor_UpdateRGBColor(&wram->wDebugGreenChannel);
}

static void DebugColor_ChangeBlueValue(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mDebugColor_PreviousRGBColor);
    if(hram.hJoyLast & D_UP)
        return DebugColor_PreviousRGBColor();
    // LD_HL(wDebugBlueChannel);
// fallthrough

    return DebugColor_UpdateRGBColor(&wram->wDebugBlueChannel);
}

static void DebugColor_UpdateRGBColor(uint8_t* hl){
    // LDH_A_addr(hJoyLast);
    // AND_A(D_RIGHT);
    // IF_NZ goto increment;
    if(hram.hJoyLast & D_RIGHT) {
    // increment:
        // LD_A_hl;
        // CP_A(31);
        // RET_NC ;
        if(*hl >= 31)
            return;
        // INC_hl;
        (*hl)++;
        // goto done;
    }
    // LDH_A_addr(hJoyLast);
    // AND_A(D_LEFT);
    // IF_NZ goto decrement;
    else if(hram.hJoyLast & D_LEFT) {
    // decrement:
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(*hl == 0)
            return;
        // DEC_hl;
        (*hl)--;
    }
    // RET;
    else {
        return;
    }

// done:
    // CALL(aDebugColor_CalculatePalette);
    DebugColor_CalculatePalette();
    // LD_A(DEBUGCOLORMAIN_UPDATEPALETTES);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = DEBUGCOLORMAIN_UPDATEPALETTES;
    // RET;
}

static inline void DebugColor_PreviousRGBColor(void){
    // LD_HL(wDebugColorRGBJumptableIndex);
    // DEC_hl;
    // RET;
    wram->wDebugColorRGBJumptableIndex--;
}

static inline void DebugColor_NextRGBColor(void){
    // LD_HL(wDebugColorRGBJumptableIndex);
    // INC_hl;
    // RET;
    wram->wDebugColorRGBJumptableIndex++;
}

static void DebugColor_InitTMHM(void){
    // hlcoord(0, 10, wTilemap);
    // LD_BC(SCREEN_WIDTH * 8);
    // LD_A(DEBUGTEST_BLACK);
    // CALL(aByteFill);
    ByteFill(coord(0, 10, wram->wTilemap), SCREEN_WIDTH * 8, DEBUGTEST_BLACK);
    // hlcoord(2, 12, wTilemap);
    // LD_DE(mDebugColor_AreYouFinishedString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(DebugColor_AreYouFinishedString), coord(1, 12, wram->wTilemap));
    // XOR_A_A;
    // LD_addr_A(wDebugColorCurTMHM);
    wram->wDebugColorCurTMHM = 0;
    // CALL(aDebugColor_PrintTMHMMove);
    DebugColor_PrintTMHMMove();
    // LD_A(DEBUGCOLORMAIN_TMHMJOYPAD);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = DEBUGCOLORMAIN_TMHMJOYPAD;
    // RET;
}

static void DebugColor_TMHMJoypad(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto cancel;
    if(hram.hJoyPressed & B_BUTTON) {
    // cancel:
        // LD_A(DEBUGCOLORMAIN_INITSCREEN);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEBUGCOLORMAIN_INITSCREEN;
        // RET;
        return;
    }
    // CALL(aDebugColor_TMHMJoypad_scroll);
    // RET;
// Inlined
// scroll:
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(hram.hJoyLast & D_UP) {
    // up:
        // LD_A_addr(wDebugColorCurTMHM);
        // CP_A(NUM_TM_HM_TUTOR - 1);
        // IF_Z goto wrap_down;
        if(wram->wDebugColorCurTMHM == NUM_TM_HM_TUTOR - 1) {
        // wrap_down:
            // XOR_A_A;
            // goto done;
            wram->wDebugColorCurTMHM = 0;
        }
        else {
            // INC_A;
            wram->wDebugColorCurTMHM++;
            // goto done;
        }
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram.hJoyLast & D_DOWN) {
    // down:
        // LD_A_addr(wDebugColorCurTMHM);
        // AND_A_A;
        // IF_Z goto wrap_up;
        if(wram->wDebugColorCurTMHM == 0) {
        // wrap_up:
            // LD_A(NUM_TM_HM_TUTOR - 1);
            wram->wDebugColorCurTMHM = NUM_TM_HM_TUTOR - 1;
        }
        else {
            // DEC_A;
            wram->wDebugColorCurTMHM--;
            // goto done;
        }
    }
    else {
        // RET;
        return;
    }


// down:
    // LD_A_addr(wDebugColorCurTMHM);
    // AND_A_A;
    // IF_Z goto wrap_up;
    // DEC_A;
    // goto done;

// done:
    // LD_addr_A(wDebugColorCurTMHM);
    // CALL(aDebugColor_PrintTMHMMove);
    DebugColor_PrintTMHMMove();
    // RET;

// exit:
//   //  unreferenced
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    // RET;
}

static inline void DebugColor_PrintTMHMMove_ClearRow(tile_t* hl);
static inline item_t DebugColor_PrintTMHMMove_GetNumberedTMHM(uint8_t tmhm);

static void DebugColor_PrintTMHMMove(void){
    static const char AbleText[] = "ABLE@"; //db ['"おぼえられる@"'];  // Learnable
    static const char NotAbleText[] = "UNABLE@"; //db ['"おぼえられない@"'];  // Not learnable

    // hlcoord(10, 11, wTilemap);
    // CALL(aDebugColor_PrintTMHMMove_ClearRow);
    DebugColor_PrintTMHMMove_ClearRow(coord(8, 11, wram->wTilemap));
    // hlcoord(10, 12, wTilemap);
    // CALL(aDebugColor_PrintTMHMMove_ClearRow);
    DebugColor_PrintTMHMMove_ClearRow(coord(8, 12, wram->wTilemap));
    // hlcoord(10, 13, wTilemap);
    // CALL(aDebugColor_PrintTMHMMove_ClearRow);
    DebugColor_PrintTMHMMove_ClearRow(coord(8, 13, wram->wTilemap));
    // hlcoord(10, 14, wTilemap);
    // CALL(aDebugColor_PrintTMHMMove_ClearRow);
    DebugColor_PrintTMHMMove_ClearRow(coord(8, 14, wram->wTilemap));

    // LD_A_addr(wDebugColorCurTMHM);
    // INC_A;
    // LD_addr_A(wTempTMHM);
    wram->wTempTMHM = wram->wDebugColorCurTMHM + 1;
    // PREDEF(pGetTMHMMove);
    move_t move = GetTMHMMove(wram->wDebugColorCurTMHM + 1);
    // LD_A_addr(wTempTMHM);
    // LD_addr_A(wPutativeTMHMMove);
    // CALL(aGetMoveName);
    // hlcoord(10, 12, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(GetMoveName(move), coord(8, 12, wram->wTilemap));

    // LD_A_addr(wDebugColorCurTMHM);
    // CALL(aDebugColor_PrintTMHMMove_GetNumberedTMHM);
    // LD_addr_A(wCurItem);
    // PREDEF(pCanLearnTMHMMove);
    uint8_t able = CanLearnTMHMMove(wram->wCurPartySpecies, DebugColor_PrintTMHMMove_GetNumberedTMHM(wram->wDebugColorCurTMHM));
    // LD_A_C;
    // AND_A_A;
    // LD_DE(mDebugColor_PrintTMHMMove_AbleText);
    // IF_NZ goto place_string;
    // LD_DE(mDebugColor_PrintTMHMMove_NotAbleText);

// place_string:
    const char* de = (able)? AbleText: NotAbleText;
    // hlcoord(10, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(de), coord(8, 14, wram->wTilemap));
    // RET;
}

static inline void DebugColor_PrintTMHMMove_ClearRow(tile_t* hl) {
    // LD_BC(10);
    // LD_A(DEBUGTEST_BLACK);
    // CALL(aByteFill);
    ByteFill(hl, SCREEN_WIDTH - 8, DEBUGTEST_BLACK);
    // RET;
}

static inline item_t DebugColor_PrintTMHMMove_GetNumberedTMHM(uint8_t tmhm){
    // CP_A(NUM_TMS);
    // IF_C goto tm;
    if(tmhm >= NUM_TMS) {
    //  hm - skip two gap items
        // INC_A;
        // INC_A;
        tmhm += 2;
    }

// tm:
    // ADD_A(TM01);
    // RET;
    return TM01 + tmhm;
}

static void DebugColor_CalculatePalette(void){
    // LD_A_addr(wDebugRedChannel);
    // AND_A(0b00011111);
    // LD_E_A;
    // LD_A_addr(wDebugGreenChannel);
    // AND_A(0b00000111);
    // SLA_A;
    // SWAP_A;
    // OR_A_E;
    // LD_E_A;
    uint8_t e = (wram->wDebugRedChannel & 0b00011111) |
        ((wram->wDebugGreenChannel & 0b00000111) << 5);
    // LD_A_addr(wDebugGreenChannel);
    // AND_A(0b00011000);
    // SLA_A;
    // SWAP_A;
    // LD_D_A;
    // LD_A_addr(wDebugBlueChannel);
    // AND_A(0b00011111);
    // SLA_A;
    // SLA_A;
    // OR_A_D;
    // LD_D_A;
    uint8_t d = ((wram->wDebugGreenChannel & 0b00011000) >> 3) |
        ((wram->wDebugBlueChannel & 0b00011111) << 2);
    // LD_A_addr(wDebugColorCurColor);
    // AND_A_A;
    // IF_Z goto light;
    if(wram->wDebugColorCurColor == 0) {
    // light:
        // LD_A_E;
        // LD_addr_A(wDebugLightColor + 0);
        wram->wDebugLightColor[0] = e;
        // LD_A_D;
        // LD_addr_A(wDebugLightColor + 1);
        wram->wDebugLightColor[1] = d;
        // RET;
        return;
    }
    else {
    //  dark
        // LD_A_E;
        // LD_addr_A(wDebugDarkColor + 0);
        wram->wDebugDarkColor[0] = e;
        // LD_A_D;
        // LD_addr_A(wDebugDarkColor + 1);
        wram->wDebugDarkColor[1] = d;
        // RET;
        return;
    }
}

static void DebugColor_CalculateRGB(const uint8_t* de){
    // LD_A_de;
    // AND_A(0b00011111);
    // LD_addr_A(wDebugRedChannel);
    wram->wDebugRedChannel = de[0] & 0b00011111;
    // LD_A_de;
    // AND_A(0b11100000);
    // SWAP_A;
    // SRL_A;
    // LD_B_A;
    // INC_DE;
    // LD_A_de;
    // AND_A(0b00000011);
    // SWAP_A;
    // SRL_A;
    // OR_A_B;
    // LD_addr_A(wDebugGreenChannel);
    wram->wDebugGreenChannel = ((de[0] & 0b11100000) >> 5) | ((de[1] & 0b00000011) << 3);
    // LD_A_de;
    // AND_A(0b01111100);
    // SRL_A;
    // SRL_A;
    // LD_addr_A(wDebugBlueChannel);
    wram->wDebugBlueChannel = (de[1] & 0b01111100) >> 2;
    // RET;
}

static void DebugColor_BackupSpriteColors(void){
    // LD_A_addr(wDebugColorCurMon);
    // INC_A;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(wDebugOriginalColors);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    uint8_t* de = wram->wDebugOriginalColors + ((wram->wDebugColorCurMon + 1) << 2);
    // LD_HL(wDebugMiddleColors);
    // LD_BC(4);
    // CALL(aCopyBytes);
    CopyBytes(de, wram->wDebugMiddleColors, 4);
    // RET;
}

static void DebugColor_LoadPalettes_White_Col1_Col2_Black(void* hl_, const void* de_, uint8_t c){
    const color_t* de = de_;
    color_t* hl = hl_;
    do {
    // loop:
        // LD_A(LOW(PALRGB_WHITE));
        // LD_hli_A;
        // LD_A(HIGH(PALRGB_WHITE));
        // LD_hli_A;
        hl[0] = PALRGB_WHITE;
        // for(int rept = 0; rept < 4; rept++){
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        hl[1] = de[0];
        hl[2] = de[1];
        // }
        // XOR_A_A;
        // LD_hli_A;
        // LD_hli_A;
        hl[3] = 0x0000;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

//  For some reason, we have another copy of FillBoxWithByte here
static void DebugColor_FillBoxWithByte(tile_t* hl, uint8_t c, uint8_t b, tile_t a){
    do {
    // row:
        // PUSH_BC;
        // PUSH_HL;

        for(uint8_t x = 0; x < c; ++x) {
        // col:
            // LD_hli_A;
            hl[x] = a;
            // DEC_C;
            // IF_NZ goto col;
        }
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        hl += SCREEN_WIDTH;
        // ADD_HL_BC;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

// void DebugColor_PushSGBPals(void){
//     LD_A_addr(wJoypadDisable);
//     PUSH_AF;
//     SET_A(JOYPAD_DISABLE_SGB_TRANSFER_F);
//     LD_addr_A(wJoypadDisable);
//     CALL(av_DebugColor_PushSGBPals);
//     POP_AF;
//     LD_addr_A(wJoypadDisable);
//     RET;

// }

// void v_DebugColor_PushSGBPals(void){
//     LD_A_hl;
//     AND_A(0x7);
//     RET_Z ;
//     LD_B_A;

// loop:
//     PUSH_BC;
//     XOR_A_A;
//     LDH_addr_A(rJOYP);
//     LD_A(0x30);
//     LDH_addr_A(rJOYP);
//     LD_B(0x10);

// loop2:
//     LD_E(0x8);
//     LD_A_hli;
//     LD_D_A;

// loop3:
//     BIT_D(0);
//     LD_A(0x10);
//     IF_NZ goto okay;
//     LD_A(0x20);

// okay:
//     LDH_addr_A(rJOYP);
//     LD_A(0x30);
//     LDH_addr_A(rJOYP);
//     RR_D;
//     DEC_E;
//     IF_NZ goto loop3;
//     DEC_B;
//     IF_NZ goto loop2;
//     LD_A(0x20);
//     LDH_addr_A(rJOYP);
//     LD_A(0x30);
//     LDH_addr_A(rJOYP);
//     LD_DE(7000);

// wait:
//     NOP;
//     NOP;
//     NOP;
//     DEC_DE;
//     LD_A_D;
//     OR_A_E;
//     IF_NZ goto wait;
//     POP_BC;
//     DEC_B;
//     IF_NZ goto loop;
//     RET;

// }

static inline uint8_t DebugColor_PlaceCursor_placesprite(struct SpriteOAM* hl, uint8_t x, uint8_t y, uint8_t attr);

static void DebugColor_PlaceCursor(void){
    // LD_A(DEBUGTEST_BLACK);
    // hlcoord(10, 0, wTilemap);
    // LD_hl_A;
    *coord(10, 0, wram->wTilemap) = DEBUGTEST_BLACK;
    // hlcoord(15, 0, wTilemap);
    // LD_hl_A;
    *coord(15, 0, wram->wTilemap) = DEBUGTEST_BLACK;
    // hlcoord(1, 11, wTilemap);
    // LD_hl_A;
    *coord(1, 11, wram->wTilemap) = DEBUGTEST_BLACK;
    // hlcoord(1, 13, wTilemap);
    // LD_hl_A;
    *coord(1, 13, wram->wTilemap) = DEBUGTEST_BLACK;
    // hlcoord(1, 15, wTilemap);
    // LD_hl_A;
    *coord(1, 15, wram->wTilemap) = DEBUGTEST_BLACK;

    // LD_A_addr(wJumptableIndex);
    // CP_A(DEBUGCOLORMAIN_JOYPAD);
    // IF_NZ goto clearsprites;
    if(wram->wJumptableIndex != DEBUGCOLORMAIN_JOYPAD) {
    // clearsprites:
        // CALL(aClearSprites);
        ClearSprites();
        // RET;
        return;
    }

    // LD_A_addr(wDebugColorRGBJumptableIndex);
    // AND_A_A;
    // IF_Z goto place_cursor;
    if(wram->wDebugColorRGBJumptableIndex != 0) {
        // DEC_A;
        uint8_t idx = wram->wDebugColorRGBJumptableIndex - 1;
        // hlcoord(1, 11, wTilemap);
        // LD_BC(2 * SCREEN_WIDTH);
        // CALL(aAddNTimes);
        // LD_hl(0xed);
        *(coord(1, 11, wram->wTilemap) + (2 * SCREEN_WIDTH * idx)) = CHAR_RIGHT_CURSOR;
    }

// place_cursor:
    // LD_A_addr(wDebugColorCurColor);
    // AND_A_A;
    // IF_Z goto light;
//  dark
    // hlcoord(15, 0, wTilemap);
    // goto place;

// light:
    // hlcoord(10, 0, wTilemap);
    tile_t* hl = (wram->wDebugColorCurColor == 0)
        ? coord(10, 0, wram->wTilemap)
        : coord(15, 0, wram->wTilemap);

// place:
    // LD_hl(0xed);
    *hl = CHAR_RIGHT_CURSOR;

    // LD_B(0x70);  // initial tile id
    uint8_t b = DEBUGTEST_0;
    // LD_C(5);  // initial palette
    // LD_HL(wVirtualOAM);
    // LD_DE(wDebugRedChannel);
    // CALL(aDebugColor_PlaceCursor_placesprite);
    b = DebugColor_PlaceCursor_placesprite(wram->wVirtualOAMSprite + 0x0, wram->wDebugRedChannel, b, 5);
    // LD_DE(wDebugGreenChannel);
    // CALL(aDebugColor_PlaceCursor_placesprite);
    b = DebugColor_PlaceCursor_placesprite(wram->wVirtualOAMSprite + 0x1, wram->wDebugGreenChannel, b, 6);
    // LD_DE(wDebugBlueChannel);
    // CALL(aDebugColor_PlaceCursor_placesprite);
    b = DebugColor_PlaceCursor_placesprite(wram->wVirtualOAMSprite + 0x2, wram->wDebugBlueChannel, b, 7);
    // RET;
}

static inline uint8_t DebugColor_PlaceCursor_placesprite(struct SpriteOAM* hl, uint8_t x, uint8_t y, uint8_t attr) {
    // LD_A_B;
    // LD_hli_A;  // y
    hl->yCoord = y;
    // LD_A_de;
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A(3 * TILE_WIDTH);
    // LD_hli_A;  // x
    hl->xCoord = (x << 2) + 3 * TILE_WIDTH;
    // XOR_A_A;
    // LD_hli_A;  // tile id
    hl->tileID = 0;
    // LD_A_C;
    // LD_hli_A;  // attributes
    hl->attributes = attr;
    // LD_A(2 * TILE_WIDTH);
    // ADD_A_B;
    // LD_B_A;
    // INC_C;
    // RET;
    return y + (2 * TILE_WIDTH);
}

void TilesetColorPicker(void){
//  //  unreferenced
//  A debug menu to test tileset palettes at runtime.
//  dummied out
    // RET;

    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // LD_addr_A(wDebugTilesetCurPalette);
    wram->wDebugTilesetCurPalette = 0;
    // LD_addr_A(wDebugTilesetRGBJumptableIndex);
    wram->wDebugTilesetRGBJumptableIndex = 0;
    // LD_addr_A(wDebugTilesetCurColor);
    wram->wDebugTilesetCurColor = 0;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = FALSE;
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // LD_DE(mDebugColor_GFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * DEBUGTEST_TICKS_1);
    // LD_BC((BANK(aDebugColor_GFX) << 8) | 22);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * DEBUGTEST_TICKS_1, DebugColor_GFX, 0, 22);
    // LD_DE(mDebugColor_UpArrowGFX);
    // LD_HL(vTiles1);
    // LD_BC((BANK(aDebugColor_UpArrowGFX) << 8) | 1);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles1, DebugColor_UpArrowGFX, 0, 1);
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    hram.hBGMapAddress = LOW(hram.hBGMapAddress) | (vBGMap1 & 0xff00);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(DEBUGTEST_BLACK);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, DEBUGTEST_BLACK);
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(PAL_BG_TEXT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, PAL_BG_TEXT);
    // decoord(1, 1, 0);
    // LD_A(DEBUGTEST_WHITE);
    // CALL(aDebugTileset_DrawColorSwatch);
    DebugTileset_DrawColorSwatch(coord(1, 1, 0), DEBUGTEST_WHITE);
    // decoord(6, 1, 0);
    // LD_A(DEBUGTEST_LIGHT);
    // CALL(aDebugTileset_DrawColorSwatch);
    DebugTileset_DrawColorSwatch(coord(6, 1, 0), DEBUGTEST_LIGHT);
    // decoord(11, 1, 0);
    // LD_A(DEBUGTEST_DARK);
    // CALL(aDebugTileset_DrawColorSwatch);
    DebugTileset_DrawColorSwatch(coord(11, 1, 0), DEBUGTEST_DARK);
    // decoord(16, 1, 0);
    // LD_A(DEBUGTEST_BLACK);
    // CALL(aDebugTileset_DrawColorSwatch);
    DebugTileset_DrawColorSwatch(coord(16, 1, 0), DEBUGTEST_BLACK);
    // CALL(aDebugTileset_LoadRGBMeter);
    DebugTileset_LoadRGBMeter();
    // CALL(aDebugTileset_LoadPalettes);
    DebugTileset_LoadPalettes();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0; // A is zero?
    // LD_A(0x40);
    // LDH_addr_A(hWY);
    hram.hWY = 0x40;

    while(!bit_test(wram->wJumptableIndex, 7)) {
        DebugColorMain2();
        DelayFrame();
    }
    // RET;
}

static void DebugTileset_DrawColorSwatch(uint16_t de, uint8_t a){
    // hlcoord(0, 0, wTilemap);
    // CALL(av_DebugColor_DrawSwatch);
    v_DebugColor_DrawSwatch(coord(0, 0, wram->wTilemap) + de, a);

    return DebugColor_DrawAttributeSwatch(de);
}

static void DebugColor_DrawAttributeSwatch(uint16_t de){
    // LD_A_addr(wDebugTilesetCurPalette);
    // hlcoord(0, 0, wAttrmap);
// fallthrough

    return v_DebugColor_DrawSwatch(coord(0, 0, wram->wAttrmap) + de, wram->wDebugTilesetCurPalette);
}

//  Fills a 4x3 box at de with byte a.
static void v_DebugColor_DrawSwatch(uint8_t* de, uint8_t a){
    // ADD_HL_DE;
    for(int rept = 0; rept < 4; rept++){
        // LD_hli_A;
        *(de++) = a;
    }
    for(int rept = 0; rept < 2; rept++){
        // LD_BC(SCREEN_WIDTH - 4);
        // ADD_HL_BC;
        de += SCREEN_WIDTH - 4;
        for(int rept_ = 0; rept_ < 4; rept_++){
            // LD_hli_A;
            *(de++) = a;
        }
    }
    // RET;
}

static inline void DebugTileset_LoadRGBMeter_Place(tile_t* hl);

static void DebugTileset_LoadRGBMeter(void){
    // hlcoord(2, 4, wTilemap);
    // CALL(aDebugTileset_LoadRGBMeter_Place);
    DebugTileset_LoadRGBMeter_Place(coord(2, 4, wram->wTilemap));
    // hlcoord(2, 6, wTilemap);
    // CALL(aDebugTileset_LoadRGBMeter_Place);
    DebugTileset_LoadRGBMeter_Place(coord(2, 6, wram->wTilemap));
    // hlcoord(2, 8, wTilemap);
    DebugTileset_LoadRGBMeter_Place(coord(2, 8, wram->wTilemap));
}

static inline void DebugTileset_LoadRGBMeter_Place(tile_t* hl){
    // LD_A(DEBUGTEST_TICKS_1);
    // LD_hli_A;
    *(hl++) = DEBUGTEST_TICKS_1;
    // LD_BC(15);
    // LD_A(DEBUGTEST_TICKS_2);
    // CALL(aByteFill);
    ByteFill(hl, 15, DEBUGTEST_TICKS_2);
    // RET;
}

static void DebugTileset_LoadPalettes(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_A_addr(wDebugTilesetCurPalette);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(wBGPals1);
    // ADD_HL_DE;
    // LD_DE(wDebugPalette);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wDebugPalette, wram->wBGPals1 + (wram->wDebugTilesetCurPalette * PALETTE_SIZE), PALETTE_SIZE);
    // LD_DE(wDebugPalette);
    // CALL(aDebugColor_CalculateRGB);
    DebugColor_CalculateRGB(wram->wDebugPalette);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

static void DebugColorMain2(void){
//  //  unreferenced
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(SELECT);
    // IF_NZ goto next_palette;
    if(hram.hJoyLast & SELECT) {
    // next_palette:
        // LD_HL(wDebugTilesetCurPalette);
        // LD_A_hl;
        // INC_A;
        // AND_A(PALETTE_MASK);
        uint8_t pal = (wram->wDebugTilesetCurPalette + 1) & PALETTE_MASK;
        // CP_A(PAL_BG_TEXT);
        // IF_NZ goto palette_ok;
        if(pal == PAL_BG_TEXT) {
            // XOR_A_A;  // PAL_BG_GRAY
            pal = PAL_BG_GRAY;
        }

    // palette_ok:
        // LD_hl_A;
        wram->wDebugTilesetCurPalette = pal;
        // decoord(1, 1, 0);
        // CALL(aDebugColor_DrawAttributeSwatch);
        DebugColor_DrawAttributeSwatch(coord(1, 1, 0));
        // decoord(6, 1, 0);
        // CALL(aDebugColor_DrawAttributeSwatch);
        DebugColor_DrawAttributeSwatch(coord(6, 1, 0));
        // decoord(11, 1, 0);
        // CALL(aDebugColor_DrawAttributeSwatch);
        DebugColor_DrawAttributeSwatch(coord(11, 1, 0));
        // decoord(16, 1, 0);
        // CALL(aDebugColor_DrawAttributeSwatch);
        DebugColor_DrawAttributeSwatch(coord(16, 1, 0));

        // LDH_A_addr(rSVBK);
        // PUSH_AF;
        // LD_A(BANK(wBGPals2));
        // LDH_addr_A(rSVBK);

        // LD_HL(wBGPals2);
        // LD_A_addr(wDebugTilesetCurPalette);
        // LD_BC(1 * PALETTE_SIZE);
        // CALL(aAddNTimes);
        // LD_DE(wDebugPalette);
        // LD_BC(1 * PALETTE_SIZE);
        // CALL(aCopyBytes);
        CopyBytes(wram->wDebugPalette, wram->wBGPals2 + (wram->wDebugTilesetCurPalette * PALETTE_SIZE), PALETTE_SIZE);

        // POP_AF;
        // LDH_addr_A(rSVBK);

        // LD_A(2);
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_UPDATE_ATTRS;
#if ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
        DelayFrame();
#else
        // LD_C(3);
        // CALL(aDelayFrames);
        DelayFrames(3);
#endif
        // LD_A(1);
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // RET;
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto cancel;
    if(hram.hJoyLast & B_BUTTON) {
    // cancel:
        // CALL(aClearSprites);
        ClearSprites();
        // LDH_A_addr(hWY);
        // XOR_A(0b11010000);
        // LDH_addr_A(hWY);
        hram.hWY ^= 0b11010000;
        bit_set(wram->wJumptableIndex, 7);
        // RET;
        return;
    }
    // CALL(aDebugTileset_Joypad);
    DebugTileset_Joypad();
    // RET;
    return;
}

static void DebugTileset_UpdatePalettes(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals2));
    // LDH_addr_A(rSVBK);

    // LD_HL(wBGPals2);
    // LD_A_addr(wDebugTilesetCurPalette);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aAddNTimes);
    // LD_E_L;
    // LD_D_H;
    // LD_HL(wDebugPalette);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals2 + (wram->wDebugTilesetCurPalette * PALETTE_SIZE), wram->wDebugPalette, PALETTE_SIZE);

    // hlcoord(1, 0, wTilemap);
    // LD_DE(wDebugWhiteTileColor);
    // CALL(aDebugColor_PrintHexColor);
    DebugColor_PrintHexColor(coord(1, 0, wram->wTilemap), wram->wDebugWhiteTileColor);
    // hlcoord(6, 0, wTilemap);
    // LD_DE(wDebugLightTileColor);
    // CALL(aDebugColor_PrintHexColor);
    DebugColor_PrintHexColor(coord(6, 0, wram->wTilemap), wram->wDebugLightTileColor);
    // hlcoord(11, 0, wTilemap);
    // LD_DE(wDebugDarkTileColor);
    // CALL(aDebugColor_PrintHexColor);
    DebugColor_PrintHexColor(coord(11, 0, wram->wTilemap), wram->wDebugDarkTileColor);
    // hlcoord(16, 0, wTilemap);
    // LD_DE(wDebugBlackTileColor);
    // CALL(aDebugColor_PrintHexColor);
    DebugColor_PrintHexColor(coord(16, 0, wram->wTilemap), wram->wDebugBlackTileColor);

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram.hCGBPalUpdate = TRUE;

    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

static void DebugTileset_Joypad(void){
    // LD_A_addr(wDebugTilesetRGBJumptableIndex);
    // maskbits(4, 0);  // .PointerTable length
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mDebugTileset_Joypad_PointerTable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;


// PointerTable:
    switch(wram->wDebugTilesetRGBJumptableIndex & 3) {
        case 0: return DebugTileset_SelectColorBox();
        case 1: return DebugTileset_ChangeRedValue();
        case 2: return DebugTileset_ChangeGreenValue();
        case 3: return DebugTileset_ChangeBlueValue();
    }
}

static void DebugTileset_SelectColorBox(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mDebugTileset_NextRGBColor);
    if(hram.hJoyLast & D_DOWN)
        return DebugTileset_NextRGBColor();
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(hram.hJoyLast & D_LEFT) {
    // left:
        // LD_A_addr(wDebugTilesetCurColor);
        // DEC_A;
        // goto done;
        wram->wDebugTilesetCurColor = (wram->wDebugTilesetCurColor - 1) & 3;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    else if(hram.hJoyLast & D_RIGHT) {
    // right:
        // LD_A_addr(wDebugTilesetCurColor);
        // INC_A;
        wram->wDebugTilesetCurColor = (wram->wDebugTilesetCurColor + 1) & 3;
    }
    else {
        // RET;
        return;
    }

// done:
    // maskbits(NUM_PAL_COLORS, 0);
    // LD_addr_A(wDebugTilesetCurColor);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wDebugPalette);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    // CALL(aDebugColor_CalculateRGB);
    DebugColor_CalculateRGB(wram->wDebugPalette + (wram->wDebugTilesetCurColor * PALETTE_SIZE));
    // RET;
}

static void DebugTileset_ChangeRedValue(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mDebugTileset_NextRGBColor);
    if(hram.hJoyLast & D_DOWN)
        return DebugTileset_NextRGBColor();
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mDebugTileset_PreviousRGBColor);
    if(hram.hJoyLast & D_UP)
        return DebugTileset_PreviousRGBColor();
    // LD_HL(wDebugRedChannel);
    // JR(mDebugTileset_UpdateRGBColor);
    return DebugTileset_UpdateRGBColor(&wram->wDebugRedChannel);
}

static void DebugTileset_ChangeGreenValue(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mDebugTileset_NextRGBColor);
    if(hram.hJoyLast & D_DOWN)
        return DebugTileset_NextRGBColor();
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mDebugTileset_PreviousRGBColor);
    if(hram.hJoyLast & D_UP)
        return DebugTileset_PreviousRGBColor();
    // LD_HL(wDebugGreenChannel);
    // JR(mDebugTileset_UpdateRGBColor);
    return DebugTileset_UpdateRGBColor(&wram->wDebugGreenChannel);
}

static void DebugTileset_ChangeBlueValue(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mDebugTileset_PreviousRGBColor);
    if(hram.hJoyLast & D_UP)
        return DebugTileset_PreviousRGBColor();
    // LD_HL(wDebugBlueChannel);
// fallthrough

    return DebugTileset_UpdateRGBColor(&wram->wDebugBlueChannel);
}

static void DebugTileset_UpdateRGBColor(uint8_t* hl){
    // LDH_A_addr(hJoyLast);
    // AND_A(D_RIGHT);
    // IF_NZ goto increment;
    if(hram.hJoyLast & D_RIGHT){
    // increment:
        // LD_A_hl;
        // CP_A(31);
        // RET_NC ;
        if(*hl >= 31)
            return;
        // INC_hl;
        (*hl)++;
        // goto done;
    }
    // LDH_A_addr(hJoyLast);
    // AND_A(D_LEFT);
    // IF_NZ goto decrement;
    else if(hram.hJoyLast & D_LEFT){
    // decrement:
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(*hl == 0)
            return;
        // DEC_hl;
        (*hl)--;
    }
    else {
        // RET;
        return;
    }

// done:
    // CALL(aDebugTileset_CalculatePalette);
    DebugTileset_CalculatePalette();
    // CALL(aDebugTileset_UpdatePalettes);
    DebugTileset_UpdatePalettes();
    // RET;
}

static inline void DebugTileset_PreviousRGBColor(void){
    // LD_HL(wDebugTilesetRGBJumptableIndex);
    // DEC_hl;
    // RET;
    wram->wDebugTilesetRGBJumptableIndex--;
}

static inline void DebugTileset_NextRGBColor(void){
    // LD_HL(wDebugTilesetRGBJumptableIndex);
    // INC_hl;
    // RET;
    wram->wDebugTilesetRGBJumptableIndex++;
}

static void DebugTileset_CalculatePalette(void){
    // LD_A_addr(wDebugRedChannel);
    // AND_A(0b00011111);
    // LD_E_A;
    // LD_A_addr(wDebugGreenChannel);
    // AND_A(0b0000111);
    // SLA_A;
    // SWAP_A;
    // OR_A_E;
    // LD_E_A;
    uint8_t e = (wram->wDebugRedChannel & 0b00011111) |
        ((wram->wDebugGreenChannel & 0b00000111) << 5);
    // LD_A_addr(wDebugGreenChannel);
    // AND_A(0b00011000);
    // SLA_A;
    // SWAP_A;
    // LD_D_A;
    // LD_A_addr(wDebugBlueChannel);
    // AND_A(0b00011111);
    // SLA_A;
    // SLA_A;
    // OR_A_D;
    // LD_D_A;
    uint8_t d = ((wram->wDebugGreenChannel & 0b00011000) >> 3) |
        ((wram->wDebugBlueChannel & 0b00011111) << 2);
    // LD_A_addr(wDebugTilesetCurColor);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wDebugPalette);
    // ADD_HL_BC;
    // ADD_HL_BC;
    uint8_t* hl = wram->wDebugPalette + (wram->wDebugTilesetCurColor * 2);
    // LD_A_E;
    // LD_hli_A;
    hl[0] = e;
    // LD_hl_D;
    hl[1] = d;
    // RET;

// dummy1:
//   //  unreferenced
    // RET;


// dummy2:
//   //  unreferenced
    // RET;
}
