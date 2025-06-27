#include "../../constants.h"
#include "trainer_card.h"
#include "../../home/time.h"
#include "../../home/joypad.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/text.h"
#include "../../home/lcd.h"
#include "../../home/print_text.h"
#include "../../home/pokedex_flags.h"
#include "../gfx/place_graphic.h"
#include "../gfx/player_gfx.h"

//  TrainerCard.Jumptable indexes
enum {
    TRAINERCARDSTATE_PAGE1_LOADGFX,  // 0
    TRAINERCARDSTATE_PAGE1_JOYPAD,  // 1
    TRAINERCARDSTATE_PAGE2_LOADGFX,  // 2
    TRAINERCARDSTATE_PAGE2_JOYPAD,  // 3
    TRAINERCARDSTATE_PAGE3_LOADGFX,  // 4
    TRAINERCARDSTATE_PAGE3_JOYPAD,  // 5
    TRAINERCARDSTATE_QUIT,  // 6
};

struct JohtoBadgesOAM {
    uint8_t* badges;
    struct {
        uint8_t y;
        uint8_t x;
        uint8_t pal;
        union {
            struct {
                uint8_t face;
                uint8_t in1;
                uint8_t in2;
                uint8_t in3;
            } cycle[2];
            uint8_t tileIDs[8];
        };
    } tilemaps[8];
};

static void TrainerCard_InitRAM(void);
static void TrainerCard_Page2_3_AnimateBadges(const struct JohtoBadgesOAM* hl);
static void TrainerCard_Page2_3_OAMUpdate(const struct JohtoBadgesOAM* hl);
static const struct JohtoBadgesOAM TrainerCard_JohtoBadgesOAM;

void TrainerCard(void){
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = gOptions.options;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // CALL(aTrainerCard_InitRAM);
    TrainerCard_InitRAM();

    while(1) {
    // loop:
        // CALL(aUpdateTime);
        UpdateTime();
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto quit;
        // LDH_A_addr(hJoyLast);
        // AND_A(B_BUTTON);
        // IF_NZ goto quit;
        if(bit_test(wram->wJumptableIndex, 7) || bit_test(hram.hJoyLast, B_BUTTON))
            break;
        // CALL(aTrainerCard_RunJumptable);
        // Jumptable:
        switch(wram->wJumptableIndex) {
        //  entries correspond to TRAINERCARDSTATE_* constants
            case TRAINERCARDSTATE_PAGE1_LOADGFX: TrainerCard_Page1_LoadGFX(); break;
            case TRAINERCARDSTATE_PAGE1_JOYPAD:  TrainerCard_Page1_Joypad(); break;
            case TRAINERCARDSTATE_PAGE2_LOADGFX: TrainerCard_Page2_LoadGFX(); break;
            case TRAINERCARDSTATE_PAGE2_JOYPAD:  TrainerCard_Page2_Joypad(); break;
            case TRAINERCARDSTATE_PAGE3_LOADGFX: TrainerCard_Page3_LoadGFX(); break;
            case TRAINERCARDSTATE_PAGE3_JOYPAD:  TrainerCard_Page3_Joypad(); break;
            case TRAINERCARDSTATE_QUIT: TrainerCard_Quit(); break;
        }

        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// quit:
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // RET;


// RunJumptable:
    //jumptable ['.Jumptable', 'wJumptableIndex']
}

#define TILE_TRAINERCARD_RIGHTCORNER 0x4 // 0x1c

static const char CardRightCornerGFX[] = "gfx/trainer_card/card_right_corner.png";
static const char CardStatusGFX[] = "gfx/trainer_card/card_status.png";

static const char LeaderGFX[] = "gfx/trainer_card/leaders.png";
static const char LeaderGFX2[] = "gfx/trainer_card/leaders.png";

static const char BadgeGFX[] = "gfx/trainer_card/badges.png";
static const char BadgeGFX2[] = "gfx/trainer_card/badges.png";

static void TrainerCard_InitRAM(void) {
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aDisableLCD);
    DisableLCD();

    // FARCALL(aGetCardPic);
    GetCardPic();

    // LD_HL(mCardRightCornerGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x1c);
    // LD_BC(1 * LEN_2BPP_TILE);
    // LD_A(BANK(aCardRightCornerGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * TILE_TRAINERCARD_RIGHTCORNER, CardRightCornerGFX, 0, 1);

    // LD_HL(mCardStatusGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x29);
    // LD_BC(86 * LEN_2BPP_TILE);
    // LD_A(BANK(aCardStatusGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x29, CardStatusGFX, 0, 86);

    // CALL(aTrainerCard_PrintTopHalfOfCard);
    TrainerCard_PrintTopHalfOfCard();

    // hlcoord(0, 8, wTilemap);
    // LD_D(6);
    // CALL(aTrainerCard_InitBorder);
    TrainerCard_InitBorder(coord(0, 8, wram->wTilemap), 6);

    // CALL(aEnableLCD);
    EnableLCD();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_B(SCGB_TRAINER_CARD);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_TRAINER_CARD);
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_HL(wJumptableIndex);
    // XOR_A_A;  // TRAINERCARDSTATE_PAGE1_LOADGFX
    // LD_hli_A;  // wJumptableIndex
    wram->wJumptableIndex = TRAINERCARDSTATE_PAGE1_LOADGFX;
    // LD_hli_A;  // wTrainerCardBadgeFrameCounter
    wram->wTrainerCardBadgeFrameCounter = 0;
    // LD_hli_A;  // wTrainerCardBadgeTileID
    wram->wTrainerCardBadgeTileID = 0;
    // LD_hl_A;  // wTrainerCardBadgeAttributes
    wram->wTrainerCardBadgeAttributes = 0;
    // RET;
}

void TrainerCard_IncrementJumptable(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    // RET;
    wram->wJumptableIndex++;
}

void TrainerCard_Quit(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

void TrainerCard_Page1_LoadGFX(void){
    // CALL(aClearSprites);
    ClearSprites();
    // hlcoord(0, 8, wTilemap);
    // LD_D(6);
    // CALL(aTrainerCard_InitBorder);
    TrainerCard_InitBorder(coord(0, 8, wram->wTilemap), 6);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_DE(mCardStatusGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x29);
    // LD_BC((BANK(aCardStatusGFX) << 8) | 86);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x29, CardStatusGFX, 0, 86);
    // CALL(aTrainerCard_Page1_PrintDexCaught_GameTime);
    TrainerCard_Page1_PrintDexCaught_GameTime();
    // CALL(aTrainerCard_IncrementJumptable);
    TrainerCard_IncrementJumptable();
    // RET;
}

void TrainerCard_Page1_Joypad(void){
    // CALL(aTrainerCard_Page1_PrintGameTime);
    TrainerCard_Page1_PrintGameTime();
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_RIGHT | A_BUTTON);
    // IF_NZ goto pressed_right_a;
    if(hram.hJoyLast & (D_RIGHT | A_BUTTON)) {
    // pressed_right_a:
        // LD_A(TRAINERCARDSTATE_PAGE2_LOADGFX);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = TRAINERCARDSTATE_PAGE2_LOADGFX;
        // RET;
        return;
    }
    // RET;
    return;


// KantoBadgeCheck:
//   //  unreferenced
    // LD_A_addr(wKantoBadges);
    // AND_A_A;
    // RET_Z ;
    // LD_A(TRAINERCARDSTATE_PAGE3_LOADGFX);
    // LD_addr_A(wJumptableIndex);
    // RET;
}

void TrainerCard_Page2_LoadGFX(void){
    // CALL(aClearSprites);
    ClearSprites();
    // hlcoord(0, 8, wTilemap);
    // LD_D(6);
    // CALL(aTrainerCard_InitBorder);
    TrainerCard_InitBorder(coord(0, 8, wram->wTilemap), 6);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_DE(mLeaderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x29);
    // LD_BC((BANK(aLeaderGFX) << 8) | 86);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x29, LeaderGFX, 0, 86);
    // LD_DE(mBadgeGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    // LD_BC((BANK(aBadgeGFX) << 8) | 44);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, BadgeGFX, 0, 44);
    // CALL(aTrainerCard_Page2_3_InitObjectsAndStrings);
    TrainerCard_Page2_3_InitObjectsAndStrings();
    // CALL(aTrainerCard_IncrementJumptable);
    TrainerCard_IncrementJumptable();
    // RET;
}

void TrainerCard_Page2_Joypad(void){
    // LD_HL(mTrainerCard_JohtoBadgesOAM);
    // CALL(aTrainerCard_Page2_3_AnimateBadges);
    TrainerCard_Page2_3_AnimateBadges(&TrainerCard_JohtoBadgesOAM);
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto Quit;
    if(hram.hJoyLast & A_BUTTON) {
    // Quit:
        // LD_A(TRAINERCARDSTATE_QUIT);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = TRAINERCARDSTATE_QUIT;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto d_left;
    if(hram.hJoyLast & D_LEFT) {
    // d_left:
        // LD_A(TRAINERCARDSTATE_PAGE1_LOADGFX);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = TRAINERCARDSTATE_PAGE1_LOADGFX;
        // RET;
        return;
    }
    // RET;
    return;


// KantoBadgeCheck:
//   //  unreferenced
    // LD_A_addr(wKantoBadges);
    // AND_A_A;
    // RET_Z ;
    // LD_A(TRAINERCARDSTATE_PAGE3_LOADGFX);
    // LD_addr_A(wJumptableIndex);
    // RET;
}

void TrainerCard_Page3_LoadGFX(void){
    // CALL(aClearSprites);
    ClearSprites();
    // hlcoord(0, 8, wTilemap);
    // LD_D(6);
    // CALL(aTrainerCard_InitBorder);
    TrainerCard_InitBorder(coord(0, 8, wram->wTilemap), 6);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_DE(mLeaderGFX2);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x29);
    // LD_BC((BANK(aLeaderGFX2) << 8) | 86);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x29, LeaderGFX2, 0, 86);
    // LD_DE(mBadgeGFX2);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    // LD_BC((BANK(aBadgeGFX2) << 8) | 44);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, BadgeGFX2, 0, 44);
    // CALL(aTrainerCard_Page2_3_InitObjectsAndStrings);
    TrainerCard_Page2_3_InitObjectsAndStrings();
    // CALL(aTrainerCard_IncrementJumptable);
    TrainerCard_IncrementJumptable();
    // RET;
}

void TrainerCard_Page3_Joypad(void){
    // LD_HL(mTrainerCard_JohtoBadgesOAM);
    // CALL(aTrainerCard_Page2_3_AnimateBadges);
    TrainerCard_Page2_3_AnimateBadges(&TrainerCard_JohtoBadgesOAM);
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(hram.hJoyLast & D_LEFT) {
    // left:
        // LD_A(TRAINERCARDSTATE_PAGE2_LOADGFX);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = TRAINERCARDSTATE_PAGE2_LOADGFX;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    else if(hram.hJoyLast & D_RIGHT) {
    // right:
        // LD_A(TRAINERCARDSTATE_PAGE1_LOADGFX);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = TRAINERCARDSTATE_PAGE1_LOADGFX;
        // RET;
        return;
    }
    // RET;
    return;
}

void TrainerCard_PrintTopHalfOfCard(void){
    static const char Name_Money[] = "NAME/"
        t_next ""
        t_next "MONEY@";

    static const uint8_t ID_No[] = {0x27, 0x28, 0xff};  // ID NO
    // ____________>
    static const uint8_t HorizontalDivider[] = {
        0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x26, (uint8_t)-1
    };
    // hlcoord(0, 0, wTilemap);
    // LD_D(5);
    // CALL(aTrainerCard_InitBorder);
    TrainerCard_InitBorder(coord(0, 0, wram->wTilemap), 5);
    // hlcoord(2, 2, wTilemap);
    // LD_DE(mTrainerCard_PrintTopHalfOfCard_Name_Money);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Name_Money), coord(2, 2, wram->wTilemap));
    // hlcoord(2, 4, wTilemap);
    // LD_DE(mTrainerCard_PrintTopHalfOfCard_ID_No);
    // CALL(aTrainerCardSetup_PlaceTilemapString);
    TrainerCardSetup_PlaceTilemapString(coord(2, 4, wram->wTilemap), ID_No);
    // hlcoord(7, 2, wTilemap);
    // LD_DE(wPlayerName);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wPlayerName, coord(7, 2, wram->wTilemap));
    // hlcoord(5, 4, wTilemap);
    // LD_DE(wPlayerID);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum(coord(5, 4, wram->wTilemap), &wram->wPlayerID, PRINTNUM_LEADINGZEROS | 2, 5);
    // hlcoord(7, 6, wTilemap);
    // LD_DE(wMoney);
    // LD_BC((PRINTNUM_MONEY | 3 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum(coord(7, 6, wram->wTilemap), &wram->wMoney, PRINTNUM_MONEY | 3, 6);
    // hlcoord(1, 3, wTilemap);
    // LD_DE(mTrainerCard_PrintTopHalfOfCard_HorizontalDivider);
    // CALL(aTrainerCardSetup_PlaceTilemapString);
    TrainerCardSetup_PlaceTilemapString(coord(1, 3, wram->wTilemap), HorizontalDivider);
    // hlcoord(14, 1, wTilemap);
    // LD_BC((5 << 8) | 7);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = 0;
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(coord(14, 1, wram->wTilemap), 5, 7);
    // RET;
}

void TrainerCard_Page1_PrintDexCaught_GameTime(void){
    static const char Dex_PlayTime[] = "#DEX"
        t_next "PLAY TIME@";
    static const char Badges[] = "  BADGES▶@";
    static const uint8_t StatusTilemap[] = {0x29, 0x2a, 0x2b, 0x2c, 0x2d, (uint8_t)-1};

    // hlcoord(2, 10, wTilemap);
    // LD_DE(mTrainerCard_Page1_PrintDexCaught_GameTime_Dex_PlayTime);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Dex_PlayTime), coord(2, 10, wram->wTilemap));
    // hlcoord(10, 15, wTilemap);
    // LD_DE(mTrainerCard_Page1_PrintDexCaught_GameTime_Badges);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Badges), coord(10, 15, wram->wTilemap));
    // LD_HL(wPokedexCaught);
    // LD_B(wEndPokedexCaught - wPokedexCaught);
    // CALL(aCountSetBits);
    // LD_DE(wNumSetBits);
    uint8_t setbits = CountSetBits(wram->wPokedexCaught, sizeof(wram->wPokedexCaught));
    // hlcoord(15, 10, wTilemap);
    // LD_BC((1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum(coord(15, 10, wram->wTilemap), &setbits, 1, 3);
    // CALL(aTrainerCard_Page1_PrintGameTime);
    TrainerCard_Page1_PrintGameTime();
    // hlcoord(2, 8, wTilemap);
    // LD_DE(mTrainerCard_Page1_PrintDexCaught_GameTime_StatusTilemap);
    // CALL(aTrainerCardSetup_PlaceTilemapString);
    TrainerCardSetup_PlaceTilemapString(coord(2, 8, wram->wTilemap), StatusTilemap);
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_POKEDEX_F);
    // RET_NZ ;
    if(bit_test(wram->wStatusFlags, STATUSFLAGS_POKEDEX_F))
        return;
    // hlcoord(1, 9, wTilemap);
    // LD_BC((2 << 8) | 17);
    // CALL(aClearBox);
    ClearBox(coord(1, 9, wram->wTilemap), 17, 2);
    // RET;


// Unused:
//   //  unreferenced
    //db ['"@"'];
}

void TrainerCard_Page2_3_InitObjectsAndStrings(void){
    static const uint8_t BadgesTilemap[] = {0x79, 0x7a, 0x7b, 0x7c, 0x7d, (uint8_t)-1};  // "BADGES"
    // hlcoord(2, 8, wTilemap);
    // LD_DE(mTrainerCard_Page2_3_InitObjectsAndStrings_BadgesTilemap);
    // CALL(aTrainerCardSetup_PlaceTilemapString);
    TrainerCardSetup_PlaceTilemapString(coord(2, 8, wram->wTilemap), BadgesTilemap);
    // hlcoord(2, 10, wTilemap);
    tile_t* hl = coord(2, 10, wram->wTilemap);
    // LD_A(0x29);
    uint8_t a = 0x29;
    // LD_C(4);
    uint8_t c = 4;

    do {
    // loop:
        // CALL(aTrainerCard_Page2_3_PlaceLeadersFaces);
        a = TrainerCard_Page2_3_PlaceLeadersFaces(hl, a);
        // for(int rept = 0; rept < 4; rept++){
        // INC_HL;
        // }
        hl += 4;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // hlcoord(2, 13, wTilemap);
    hl = coord(2, 13, wram->wTilemap);
    // LD_A(0x51);
    a = 0x51;
    // LD_C(4);
    c = 4;

    do {
    // loop2:
        // CALL(aTrainerCard_Page2_3_PlaceLeadersFaces);
        a = TrainerCard_Page2_3_PlaceLeadersFaces(hl, a);
        // for(int rept = 0; rept < 4; rept++){
        // INC_HL;
        // }
        hl += 4;
        // DEC_C;
        // IF_NZ goto loop2;
    } while(--c != 0);
    // XOR_A_A;
    // LD_addr_A(wTrainerCardBadgeFrameCounter);
    wram->wTrainerCardBadgeFrameCounter = 0;
    // LD_HL(mTrainerCard_JohtoBadgesOAM);
    // CALL(aTrainerCard_Page2_3_OAMUpdate);
    // RET;
}

void TrainerCardSetup_PlaceTilemapString(tile_t* hl, const uint8_t* de){
    while(1) {
    // loop:
        // LD_A_de;
        uint8_t a = *de;
        // CP_A(-1);
        // RET_Z ;
        if(a == 0xff)
            return;
        // LD_hli_A;
        *(hl++) = a;
        // INC_DE;
        de++;
        // goto loop;
    }
}

void TrainerCard_InitBorder(tile_t* hl, uint8_t d){
    // LD_E(SCREEN_WIDTH);
    uint8_t e = SCREEN_WIDTH;

    do {
    // loop1:
        // LD_A(0x23);
        // LD_hli_A;
        *(hl++) = 0x23;
        // DEC_E;
        // IF_NZ goto loop1;
    } while(--e != 0);

    // LD_A(0x23);
    // LD_hli_A;
    *(hl++) = 0x23;

    // LD_E(SCREEN_WIDTH - 3);
    e = SCREEN_WIDTH - 3;
    // LD_A(0x7f);
    do {
    // loop2:
        // LD_hli_A;
        *(hl++) = 0x7f;
        // DEC_E;
        // IF_NZ goto loop2;
    } while(--e != 0);

    // LD_A(0x1c);
    // LD_hli_A;
    *(hl++) = TILE_TRAINERCARD_RIGHTCORNER;
    // LD_A(0x23);
    // LD_hli_A;
    *(hl++) = 0x23;

    do {
    // loop3:
        // LD_A(0x23);
        // LD_hli_A;
        *(hl++) = 0x23;

        // LD_E(SCREEN_WIDTH - 2);
        e = SCREEN_WIDTH - 2;
        // LD_A(0x7f);

        do {
        // loop4:
            // LD_hli_A;
            *(hl++) = 0x7f;
            // DEC_E;
            // IF_NZ goto loop4;
        } while(--e != 0);

        // LD_A(0x23);
        // LD_hli_A;
        *(hl++) = 0x23;

        // DEC_D;
        // IF_NZ goto loop3;
    } while(--d != 0);

    // LD_A(0x23);
    // LD_hli_A;
    *(hl++) = 0x23;
    // LD_A(0x24);
    // LD_hli_A;
    *(hl++) = 0x24;

    // LD_E(SCREEN_WIDTH - 3);
    e = SCREEN_WIDTH - 3;
    // LD_A(0x7f);

    do {
    // loop5:
        // LD_hli_A;
        *(hl++) = 0x7f;
        // DEC_E;
        // IF_NZ goto loop5;
    } while(--e != 0);

    // LD_A(0x23);
    // LD_hli_A;
    *(hl++) = 0x23;

    // LD_E(SCREEN_WIDTH);
    e = SCREEN_WIDTH;

    do {
    // loop6:
        // LD_A(0x23);
        // LD_hli_A;
        *(hl++) = 0x23;
        // DEC_E;
        // IF_NZ goto loop6;
    } while(--e != 0);
    // RET;
}

uint8_t TrainerCard_Page2_3_PlaceLeadersFaces(tile_t* hl, uint8_t a){
    // PUSH_DE;
    // PUSH_HL;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_DE(SCREEN_WIDTH - 3);
    // ADD_HL_DE;
    hl += SCREEN_WIDTH - 3;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_DE(SCREEN_WIDTH - 3);
    // ADD_HL_DE;
    hl += SCREEN_WIDTH - 3;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // POP_HL;
    // POP_DE;
    // RET;
    return a;
}

void TrainerCard_Page1_PrintGameTime(void){
    // hlcoord(11, 12, wTilemap);
    uint8_t* hl = coord(11, 12, wram->wTilemap);
    // LD_DE(wGameTimeHours);
    // LD_BC((2 << 8) | 4);
    // CALL(aPrintNum);
    hl = PrintNum(hl, &wram->wGameTimeHours, 2, 4);
    // INC_HL;
    // LD_DE(wGameTimeMinutes);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum(hl + 1, &wram->wGameTimeMinutes, PRINTNUM_LEADINGZEROS | 1, 2);
    // LDH_A_addr(hVBlankCounter);
    // AND_A(0x1f);
    // RET_NZ ;
    if(hram.hVBlankCounter & 0x1f)
        return;
    // hlcoord(15, 12, wTilemap);
    // LD_A_hl;
    // XOR_A(0x7f ^ 0x2e);  // alternate between space and small colon ($2e) tiles
    // LD_hl_A;
    *coord(15, 12, wram->wTilemap) ^= 0x7f ^ 0x2e;
    // RET;
}

static void TrainerCard_Page2_3_AnimateBadges(const struct JohtoBadgesOAM* hl){
    // LDH_A_addr(hVBlankCounter);
    // AND_A(0b111);
    // RET_NZ ;
    if(hram.hVBlankCounter & 0b111)
        return;
    // LD_A_addr(wTrainerCardBadgeFrameCounter);
    // INC_A;
    // AND_A(0b111);
    // LD_addr_A(wTrainerCardBadgeFrameCounter);
    wram->wTrainerCardBadgeFrameCounter = (wram->wTrainerCardBadgeFrameCounter + 1) & 0b111;
    // JR(mTrainerCard_Page2_3_OAMUpdate);
    return TrainerCard_Page2_3_OAMUpdate(hl);
}

static void TrainerCard_Page2_3_OAMUpdate_PrepOAM(struct SpriteOAM* de, uint8_t b, uint8_t c) {
    static const uint8_t facing1[] = {
        dbsprite(0, 0, 0, 0, 0x00, 0),
        dbsprite(1, 0, 0, 0, 0x01, 0),
        dbsprite(0, 1, 0, 0, 0x02, 0),
        dbsprite(1, 1, 0, 0, 0x03, 0),
        (uint8_t)-1,
    };

    static const uint8_t facing2[] = {
        dbsprite(0, 0, 0, 0, 0x01, 0 | X_FLIP),
        dbsprite(1, 0, 0, 0, 0x00, 0 | X_FLIP),
        dbsprite(0, 1, 0, 0, 0x03, 0 | X_FLIP),
        dbsprite(1, 1, 0, 0, 0x02, 0 | X_FLIP),
        (uint8_t)-1,
    };
    // LD_A_addr(wTrainerCardBadgeTileID);
    // AND_A(1 << 7);
    // IF_NZ goto xflip;

    const uint8_t* hl;
    if(wram->wTrainerCardBadgeTileID & (1 << 7)) {
    // xflip:
        // LD_HL(mTrainerCard_Page2_3_OAMUpdate_facing2);
        hl = facing2;
    }
    else {
        // LD_HL(mTrainerCard_Page2_3_OAMUpdate_facing1);
        hl = facing1;
        // goto loop2;
    }

    while(1) {
    // loop2:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(-1);
        // RET_Z ;
        if(a == 0xff)
            return;

        // ADD_A_B;
        // LD_de_A;  // y
        de->yCoord = a + b;
        // INC_DE;

        // LD_A_hli;
        a = *(hl++);
        // ADD_A_C;
        // LD_de_A;  // x
        de->xCoord = a + c;
        // INC_DE;

        // LD_A_addr(wTrainerCardBadgeTileID);
        // AND_A(~(1 << 7));
        // ADD_A_hl;
        // LD_de_A;  // tile id
        de->tileID = (wram->wTrainerCardBadgeTileID & ~(1 << 7)) + *hl;
        // INC_HL;
        hl++;
        // INC_DE;

        // LD_A_addr(wTrainerCardBadgeAttributes);
        // ADD_A_hl;
        // LD_de_A;  // attributes
        de->attributes = wram->wTrainerCardBadgeAttributes + *hl;
        // INC_HL;
        hl++;
        // INC_DE;
        de++;
        // goto loop2;
    }
}

static void TrainerCard_Page2_3_OAMUpdate(const struct JohtoBadgesOAM* hl){
//  copy flag array pointer
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
//  get flag array
    // LD_D_A;
    // LD_A_de;
    // LD_C_A;
    uint8_t c = *hl->badges;
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;
    // LD_B(NUM_JOHTO_BADGES);

    for(uint8_t i = 0; i < NUM_JOHTO_BADGES; ++i) {
    // loop:
        // SRL_C;
        // PUSH_BC;
        // IF_NC goto skip_badge;
        if(c & 1) {
            // PUSH_HL;
            // LD_A_hli;  // y
            // LD_B_A;
            uint8_t b = hl->tilemaps[i].y;
            // LD_A_hli;  // x
            // LD_C_A;
            uint8_t c = hl->tilemaps[i].x;
            // LD_A_hli;  // pal
            // LD_addr_A(wTrainerCardBadgeAttributes);
            wram->wTrainerCardBadgeAttributes = hl->tilemaps[i].pal;
            // LD_A_addr(wTrainerCardBadgeFrameCounter);
            // ADD_A_L;
            // LD_L_A;
            // LD_A(0);
            // ADC_A_H;
            // LD_H_A;
            // LD_A_hl;
            // LD_addr_A(wTrainerCardBadgeTileID);
            wram->wTrainerCardBadgeTileID = hl->tilemaps[i].tileIDs[wram->wTrainerCardBadgeFrameCounter];
            // CALL(aTrainerCard_Page2_3_OAMUpdate_PrepOAM);
            TrainerCard_Page2_3_OAMUpdate_PrepOAM(de, b, c);
            // POP_HL;
        }

    // skip_badge:
        // LD_BC(0xb);  // 3 + 2 * 4
        // ADD_HL_BC;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop;
        c >>= 1;
    }
    // RET;
}

//  Template OAM data for each badge on the trainer card.
//  Format:
// y, x, palette
// cycle 1: face tile, in1 tile, in2 tile, in3 tile
// cycle 2: face tile, in1 tile, in2 tile, in3 tile
static const struct JohtoBadgesOAM TrainerCard_JohtoBadgesOAM = {
    //dw ['wJohtoBadges'];
    .badges = wram_ptr(wJohtoBadges),

    .tilemaps = {
    // Zephyrbadge
    [ZEPHYRBADGE] = {
        .y=0x68, .x=0x18, .pal=0,
        .cycle = {
            {0x00, 0x20, 0x24, 0x20 | (1 << 7)},
            {0x00, 0x20, 0x24, 0x20 | (1 << 7)},
        },
    },

    // Hivebadge
    [HIVEBADGE] = {
        .y=0x68, .x=0x38, .pal=0,
        .cycle = {
            {0x04, 0x20, 0x24, 0x20 | (1 << 7)},
            {0x04, 0x20, 0x24, 0x20 | (1 << 7)},
        },
    },

    // Plainbadge
    [PLAINBADGE] = {
        .y=0x68, .x=0x58, .pal=0,
        .cycle = {
            {0x08, 0x20, 0x24, 0x20 | (1 << 7)},
            {0x08, 0x20, 0x24, 0x20 | (1 << 7)},
        },
    },

    // Fogbadge
    [FOGBADGE] = {
        .y=0x68, .x=0x78, .pal=0,
        .cycle = {
            {0x0c, 0x20, 0x24, 0x20 | (1 << 7)},
            {0x0c, 0x20, 0x24, 0x20 | (1 << 7)},
        },
    },

    // Mineralbadge
    [MINERALBADGE] = {
        .y=0x80, .x=0x38, .pal=0,
        .cycle = {
            {0x10, 0x20, 0x24, 0x20 | (1 << 7)},
            {0x10, 0x20, 0x24, 0x20 | (1 << 7)},
        },
    },

    // Stormbadge
    [STORMBADGE] = {
        .y=0x80, .x=0x18, .pal=0,
        .cycle = {
            {0x14, 0x20, 0x24, 0x20 | (1 << 7)},
            {0x14, 0x20, 0x24, 0x20 | (1 << 7)},
        },
    },

    // Glacierbadge
    [GLACIERBADGE] = {
        .y=0x80, .x=0x58, .pal=0,
        .cycle = {
            {0x18, 0x20, 0x24, 0x20 | (1 << 7)},
            {0x18, 0x20, 0x24, 0x20 | (1 << 7)},
        },
    },

    // Risingbadge
    // X-flips on alternate cycles.
    [RISINGBADGE] = {
        .y=0x80, .x=0x78, .pal=0,
        .cycle = {
            {0x1c, 0x20, 0x24, 0x20 | (1 << 7)},
            {0x1c | (1 << 7), 0x20, 0x24, 0x20 | (1 << 7)},
        },
    },
    }
};
