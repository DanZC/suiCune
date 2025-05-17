#include "../../constants.h"
#include "player_gfx.h"
#include "place_graphic.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../gfx/sprites.h"
#include "../../gfx/misc.h"
#include "../../data/player_names.h"

// void ChrisPic(void){
// INCBIN "gfx/player/chris.2bpp"

    // return KrisPic();
// }

// void KrisPic(void){
// INCBIN "gfx/player/kris.2bpp"

    // return GetKrisBackpic();
// }

// void KrisBackpic(void){
// INCBIN "gfx/player/kris_back.2bpp"

// }

static const char ChrisPic[] = "gfx/player/chris.png";
static const char KrisPic[] = "gfx/player/kris.png";
static const char KrisBackpic[] = "gfx/player/kris_back.png";

void BetaLoadPlayerTrainerClass(void){
//  //  unreferenced
    LD_C(CAL);
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto got_class;
    LD_C(KAREN);  // not KRIS?

got_class:
    LD_A_C;
    LD_addr_A(wTrainerClass);
    RET;

}

void MovePlayerPicRight(void){
    // hlcoord(6, 4, wTilemap);
    // LD_DE(1);
    // JR(mMovePlayerPic);
    return MovePlayerPic(wram->wTilemap + coordidx(6, 4), 1);
}

void MovePlayerPicLeft(void){
    // hlcoord(13, 4, wTilemap);
    // LD_DE(-1);
// fallthrough

    return MovePlayerPic(wram->wTilemap + coordidx(13, 4), -1);
}

//  Move player pic at hl by de * 7 tiles.
void MovePlayerPic(uint8_t* hl, int16_t de){
    // LD_C(0x8);
    uint8_t c = 0x8;

    while(1) {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_DE;
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_NONE;
        // LD_BC((7 << 8) | 7);
        // PREDEF(pPlaceGraphic);
        PlaceGraphicYStagger(hl, 7, 7);
        // XOR_A_A;
        // LDH_addr_A(hBGMapThird);
        hram.hBGMapThird = 0;
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aDelayFrame);
        DelayFrame();
        // POP_DE;
        // POP_HL;
        // ADD_HL_DE;
        hl += de;
        // POP_BC;
        // DEC_C;
        // RET_Z ;
        if(--c == 0)
            return;
        // PUSH_HL;
        // PUSH_BC;
        // LD_A_L;
        // SUB_A_E;
        // LD_L_A;
        // LD_A_H;
        // SBC_A_D;
        // LD_H_A;
        // LD_BC((7 << 8) | 7);
        // CALL(aClearBox);
        ClearBox(hl - de, 7, 7);
        // POP_BC;
        // POP_HL;
        // goto loop;
    }
}

void ShowPlayerNamingChoices(void){
    // LD_HL(mChrisNameMenuHeader);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_header;
    // LD_HL(mKrisNameMenuHeader);

// got_header:
    const struct MenuHeader *hdr = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? &KrisNameMenuHeader: &ChrisNameMenuHeader;
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(hdr);
    // CALL(aVerticalMenu);
    VerticalMenu();
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // CALL(aCopyNameFromMenu);
    CopyNameFromMenu(wram->wMenuCursorY - 1);
    // CALL(aCloseWindow);
    CloseWindow();
    // RET;

// INCLUDE "data/player_names.asm"
}

void GetPlayerNameArray(void){
//  //  unreferenced
    LD_HL(wPlayerName);
    LD_DE(mMalePlayerNameArray);
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto got_array;
    LD_DE(mFemalePlayerNameArray);

got_array:
    CALL(aInitName);
    RET;

}

const char* GetPlayerIcon(void){
    if(bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))
    {
        // Load Kris graphics
        return KrisSpriteGFX;
    }
    return ChrisSpriteGFX;
}

static const char ChrisCardPic[] = "gfx/trainer_card/chris_card.png";
static const char KrisCardPic[] = "gfx/trainer_card/kris_card.png";
static const char TrainerCardGFX[] = "gfx/trainer_card/trainer_card.png";

void GetCardPic(void){
    // LD_HL(mChrisCardPic);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_pic;
    // LD_HL(mKrisCardPic);

// got_pic:
    const char* path = (!bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))
        ? ChrisCardPic
        : KrisCardPic;
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_BC(0x23 * LEN_2BPP_TILE);
    // LD_A(BANK(aChrisCardPic));  // aka BANK(KrisCardPic)
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, path, 0, 0x23);
    // LD_HL(mTrainerCardGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x23);
    // LD_BC(6 * LEN_2BPP_TILE);
    // LD_A(BANK(aTrainerCardGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x23, TrainerCardGFX, 0, 6);
    // RET;
}

void GetPlayerBackpic(void){
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // JR_Z (mGetChrisBackpic);
    if(!bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))
        return GetChrisBackpic();
    // CALL(aGetKrisBackpic);
    // RET;
    return GetKrisBackpic();
}

void GetChrisBackpic(void){
    // LD_HL(mChrisBackpic);
    // LD_B(BANK(aChrisBackpic));
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_C(7 * 7);
    // PREDEF(pDecompressGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x31, ChrisBackpic, 0, 7 * 7);
    // RET;

}

void HOF_LoadTrainerFrontpic(void){
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;

//  Get class
    // LD_E(CHRIS);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_class;
    // LD_E(KRIS);

// got_class:
    // LD_A_E;
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? KRIS: CHRIS;

//  Load pic
    // LD_DE(mChrisPic);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_pic;
    // LD_DE(mKrisPic);
    const char* pic = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? KrisPic: ChrisPic;

// got_pic:
    // LD_HL(vTiles2);
    // LD_B(BANK(aChrisPic));  // aka BANK(KrisPic)
    // LD_C(7 * 7);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, pic, 0, 7 * 7);

    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

//  Draw the player pic at (6,4).
void DrawIntroPlayerPic(void){
//  Get class
    // LD_E(CHRIS);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_class;
    // LD_E(KRIS);

// got_class:
    // LD_A_E;
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? KRIS: CHRIS;

//  Load pic
    // LD_DE(mChrisPic);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_pic;
    // LD_DE(mKrisPic);
    const char* pic = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? KrisPic: ChrisPic;

// got_pic:
    // LD_HL(vTiles2);
    // LD_B(BANK(aChrisPic));  // aka BANK(KrisPic)
    // LD_C(7 * 7);  // dimensions
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, pic, 0, 7 * 7);

//  Draw
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = 0;
    // hlcoord(6, 4, wTilemap);
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(coord(6, 4, wram->wTilemap), 7, 7);
    // RET;
}

void GetKrisBackpic(void){
//  Kris's backpic is uncompressed.
    // LD_DE(mKrisBackpic);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_BC((BANK(aKrisBackpic) << 8) | 7 * 7);  // dimensions
    // CALL(aGet2bpp);
    LoadPNG2bppAssetToVRAMByColumn(vram->vTiles2 + LEN_2BPP_TILE * 0x31, KrisBackpic);
    // RET;
}

