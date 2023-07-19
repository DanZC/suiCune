#include "../../constants.h"
#include "pokegear.h"
#include "../../home/gfx.h"
#include "../../home/map.h"
#include "../../home/delay.h"
#include "../../home/decompress.h"
#include "../../home/copy.h"
#include "../../home/palettes.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/lcd.h"
#include "../gfx/player_gfx.h"
#include "../../audio/engine.h"
#include "../rtc/print_hours_mins.h"

//  Pokégear cards
enum {
    POKEGEARCARD_CLOCK = 0,
    POKEGEARCARD_MAP = 1,
    POKEGEARCARD_PHONE = 2,
    POKEGEARCARD_RADIO = 3,
    NUM_POKEGEAR_CARDS
};
    //const_def ['?']
    //const ['POKEGEARCARD_CLOCK']  // 0
    //const ['POKEGEARCARD_MAP']  // 1
    //const ['POKEGEARCARD_PHONE']  // 2
    //const ['POKEGEARCARD_RADIO']  // 3
// #define NUM_POKEGEAR_CARDS (POKEGEARCARD_RADIO + 1)

#define PHONE_DISPLAY_HEIGHT (4)

//  PokegearJumptable.Jumptable indexes
enum {
    POKEGEARSTATE_CLOCKINIT = 0,   //const ['POKEGEARSTATE_CLOCKINIT']  // 0
    POKEGEARSTATE_CLOCKJOYPAD, //const ['POKEGEARSTATE_CLOCKJOYPAD']  // 1
    POKEGEARSTATE_MAPCHECKREGION, //const ['POKEGEARSTATE_MAPCHECKREGION']  // 2
    POKEGEARSTATE_JOHTOMAPINIT,//const ['POKEGEARSTATE_JOHTOMAPINIT']  // 3
    POKEGEARSTATE_JOHTOMAPJOYPAD, //const ['POKEGEARSTATE_JOHTOMAPJOYPAD']  // 4
    POKEGEARSTATE_KANTOMAPINIT,//const ['POKEGEARSTATE_KANTOMAPINIT']  // 5
    POKEGEARSTATE_KANTOMAPJOYPAD, //const ['POKEGEARSTATE_KANTOMAPJOYPAD']  // 6
    POKEGEARSTATE_PHONEINIT, //const ['POKEGEARSTATE_PHONEINIT']  // 7
    POKEGEARSTATE_PHONEJOYPAD, //const ['POKEGEARSTATE_PHONEJOYPAD']  // 8
    POKEGEARSTATE_MAKEPHONECALL, //const ['POKEGEARSTATE_MAKEPHONECALL']  // 9
    POKEGEARSTATE_FINISHPHONECALL, //const ['POKEGEARSTATE_FINISHPHONECALL']  // a
    POKEGEARSTATE_RADIOINIT, //const ['POKEGEARSTATE_RADIOINIT']  // b
    POKEGEARSTATE_RADIOJOYPAD //const ['POKEGEARSTATE_RADIOJOYPAD']  // c
};

void PokeGear(void){
    PEEK("");
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    LD_A_addr(wVramState);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wVramState);
    CALL(aPokeGear_InitTilemap);
    // PokeGear_InitTilemap_Conv();
    CALL(aDelayFrame);

loop:
    SET_PC(aPokeGear_loop);
    CALL(aUpdateTime);
    CALL(aJoyTextDelay);
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto done;
    CALL(aPokegearJumptable);
    FARCALL(aPlaySpriteAnimations);
    CALL(aDelayFrame);
    goto loop;


done:
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    POP_AF;
    LD_addr_A(wVramState);
    POP_AF;
    LDH_addr_A(hInMenu);
    POP_AF;
    LD_addr_A(wOptions);
    CALL(aClearBGPalettes);
    XOR_A_A;  // LOW(vBGMap0)
    LDH_addr_A(hBGMapAddress);
    LD_A(HIGH(vBGMap0));
    LDH_addr_A(hBGMapAddress + 1);
    LD_A(SCREEN_HEIGHT_PX);
    LDH_addr_A(hWY);
    CALL(aExitPokegearRadio_HandleMusic);
    RET;


// InitTilemap:
//     CALL(aClearBGPalettes);
//     CALL(aClearTilemap);
//     CALL(aClearSprites);
//     CALL(aDisableLCD);
//     XOR_A_A;
//     LDH_addr_A(hSCY);
//     LDH_addr_A(hSCX);
//     LD_A(0x7);
//     LDH_addr_A(hWX);
//     CALL(aPokegear_LoadGFX);
//     FARCALL(aClearSpriteAnims);
//     CALL(aInitPokegearModeIndicatorArrow);
//     LD_A(8);
//     CALL(aSkipMusic);
//     LD_A(LCDC_DEFAULT);
//     LDH_addr_A(rLCDC);
//     CALL(aTownMap_InitCursorAndPlayerIconPositions);
//     XOR_A_A;
//     LD_addr_A(wJumptableIndex);  // POKEGEARSTATE_CLOCKINIT
//     LD_addr_A(wPokegearCard);  // POKEGEARCARD_CLOCK
//     LD_addr_A(wPokegearMapRegion);  // JOHTO_REGION
//     LD_addr_A(wUnusedPokegearByte);
//     LD_addr_A(wPokegearPhoneScrollPosition);
//     LD_addr_A(wPokegearPhoneCursorPosition);
//     LD_addr_A(wPokegearPhoneSelectedPerson);
//     LD_addr_A(wPokegearRadioChannelBank);
//     LD_addr_A(wPokegearRadioChannelAddr);
//     LD_addr_A(wPokegearRadioChannelAddr + 1);
//     CALL(aPokegear_InitJumptableIndices);
//     CALL(aInitPokegearTilemap);
//     LD_B(SCGB_POKEGEAR_PALS);
//     CALL(aGetSGBLayout);
//     CALL(aSetPalettes);
//     LDH_A_addr(hCGB);
//     AND_A_A;
//     RET_Z ;
//     LD_A(0b11100100);
//     CALL(aDmgToCgbObjPal0);
//     RET;

}

void PokeGear_InitTilemap(void) {
    CALL(aClearBGPalettes);
    CALL(aClearTilemap);
    CALL(aClearSprites);
    CALL(aDisableLCD);
    XOR_A_A;
    LDH_addr_A(hSCY);
    LDH_addr_A(hSCX);
    LD_A(0x7);
    LDH_addr_A(hWX);
    CALL(aPokegear_LoadGFX);
    FARCALL(aClearSpriteAnims);
    CALL(aInitPokegearModeIndicatorArrow);
    LD_A(8);
    CALL(aSkipMusic);
    LD_A(LCDC_DEFAULT);
    LDH_addr_A(rLCDC);
    CALL(aTownMap_InitCursorAndPlayerIconPositions);
    XOR_A_A;
    LD_addr_A(wJumptableIndex);  // POKEGEARSTATE_CLOCKINIT
    LD_addr_A(wPokegearCard);  // POKEGEARCARD_CLOCK
    LD_addr_A(wPokegearMapRegion);  // JOHTO_REGION
    LD_addr_A(wUnusedPokegearByte);
    LD_addr_A(wPokegearPhoneScrollPosition);
    LD_addr_A(wPokegearPhoneCursorPosition);
    LD_addr_A(wPokegearPhoneSelectedPerson);
    LD_addr_A(wPokegearRadioChannelBank);
    LD_addr_A(wPokegearRadioChannelAddr);
    LD_addr_A(wPokegearRadioChannelAddr + 1);
    CALL(aPokegear_InitJumptableIndices);
    CALL(aInitPokegearTilemap);
    LD_B(SCGB_POKEGEAR_PALS);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z return;
    LD_A(0b11100100);
    CALL(aDmgToCgbObjPal0);
    RET;
}

void PokeGear_InitTilemap_Conv(void) {
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();

    // CALL(aClearTilemap);
    ClearTilemap_Conv();

    // CALL(aClearSprites);
    ClearSprites_Conv();

    // CALL(aDisableLCD);
    DisableLCD_Conv();

    //XOR_A_A;
    //LDH_addr_A(hSCY);
    //LDH_addr_A(hSCX);
    gb_write(hSCY, 0);
    gb_write(hSCX, 0);

    // LD_A(0x7);
    // LDH_addr_A(hWX);
    gb_write(hWX, 0x7);

    Pokegear_LoadGFX_Conv();
    // CALL(aPokegear_LoadGFX);
    FARCALL(aClearSpriteAnims);
    // CALL(aInitPokegearModeIndicatorArrow);
    InitPokegearModeIndicatorArrow_Conv();
    LD_A(8);
    CALL(aSkipMusic);

    // LD_A(LCDC_DEFAULT);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, LCDC_DEFAULT);

    //CALL(aTownMap_InitCursorAndPlayerIconPositions);
    TownMap_InitCursorAndPlayerIconPositions_Conv();

    //XOR_A_A;
    //LD_addr_A(wJumptableIndex);  // POKEGEARSTATE_CLOCKINIT
    //LD_addr_A(wPokegearCard);  // POKEGEARCARD_CLOCK
    //LD_addr_A(wPokegearMapRegion);  // JOHTO_REGION
    //LD_addr_A(wUnusedPokegearByte);
    //LD_addr_A(wPokegearPhoneScrollPosition);
    //LD_addr_A(wPokegearPhoneCursorPosition);
    //LD_addr_A(wPokegearPhoneSelectedPerson);
    //LD_addr_A(wPokegearRadioChannelBank);
    //LD_addr_A(wPokegearRadioChannelAddr);
    //LD_addr_A(wPokegearRadioChannelAddr + 1);

    gb_write(wJumptableIndex, POKEGEARSTATE_CLOCKINIT);  // POKEGEARSTATE_CLOCKINIT
    gb_write(wPokegearCard, POKEGEARCARD_CLOCK);  // POKEGEARCARD_CLOCK
    gb_write(wPokegearMapRegion, JOHTO_REGION);  // JOHTO_REGION
    gb_write(wUnusedPokegearByte, 0);
    gb_write(wPokegearPhoneScrollPosition, 0);
    gb_write(wPokegearPhoneCursorPosition, 0);
    gb_write(wPokegearPhoneSelectedPerson, 0);
    gb_write(wPokegearRadioChannelBank, 0);
    gb_write(wPokegearRadioChannelAddr, 0);
    gb_write(wPokegearRadioChannelAddr + 1, 0);

    //CALL(aPokegear_InitJumptableIndices);
    Pokegear_InitJumptableIndices_Conv();

    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap_Conv();

    LD_B(SCGB_POKEGEAR_PALS);
    CALL(aGetSGBLayout);
    // GetSGBLayout_Conv();

    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z return;
    if(gb_read(hCGB) == 0)
        return;
    LD_A(0b11100100);
    CALL(aDmgToCgbObjPal0);
    //RET;
}

void Pokegear_LoadGFX(void){
    CALL(aClearVBank1);
    LD_HL(mTownMapGFX);
    LD_DE(vTiles2);
    LD_A(BANK(aTownMapGFX));
    CALL(aFarDecompress);
    LD_HL(mPokegearGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x30);
    LD_A(BANK(aPokegearGFX));
    CALL(aFarDecompress);
    LD_HL(mPokegearSpritesGFX);
    LD_DE(vTiles0);
    LD_A(BANK(aPokegearSpritesGFX));
    CALL(aDecompress);
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);
    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto ssaqua;
    FARCALL(aGetPlayerIcon);
    PUSH_DE;
    LD_H_D;
    LD_L_E;
    LD_A_B;
// standing sprite
    PUSH_AF;
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x10);
    LD_BC(4 * LEN_2BPP_TILE);
    CALL(aFarCopyBytes);
    POP_AF;
    POP_HL;
// walking sprite
    LD_DE(12 * LEN_2BPP_TILE);
    ADD_HL_DE;
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x14);
    LD_BC(4 * LEN_2BPP_TILE);
    CALL(aFarCopyBytes);
    RET;


ssaqua:
    LD_HL(mFastShipGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x10);
    LD_BC(8 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    RET;

}

void Pokegear_LoadGFX_Conv(void){
    ClearVBank1_Conv();
    FarDecompress_Conv(BANK(aTownMapGFX), mTownMapGFX, vTiles2);
    FarDecompress_Conv(BANK(aPokegearGFX), mPokegearGFX, (vTiles2 + LEN_2BPP_TILE * 0x30));
    // LD_HL(mPokegearSpritesGFX);
    // LD_DE(vTiles0);
    // LD_A(BANK(aPokegearSpritesGFX));
    // CALL(aDecompress);
    FarDecompress_Conv(BANK(aPokegearSpritesGFX), mPokegearSpritesGFX, vTiles0);
    uint8_t landmark = GetWorldMapLocation_Conv(gb_read(wMapGroup), gb_read(wMapNumber));
    if(landmark == LANDMARK_FAST_SHIP)
    {
        CopyBytes_Conv(vTiles0 + LEN_2BPP_TILE * 0x10, mFastShipGFX, 8 * LEN_2BPP_TILE);
        return;
    }
    uint16_t iconptr;
    uint8_t iconbank;
    GetPlayerIcon_Conv(&iconptr, &iconbank);
// standing sprite
    FarCopyBytes_Conv(vTiles0 + LEN_2BPP_TILE * 0x10, iconbank, iconptr, 4 * LEN_2BPP_TILE);
// walking sprite
    iconptr += (12 * LEN_2BPP_TILE);
    FarCopyBytes_Conv(vTiles0 + LEN_2BPP_TILE * 0x14, iconbank, iconptr, 4 * LEN_2BPP_TILE);
}

void FastShipGFX(void){
// INCBIN "gfx/pokegear/fast_ship.2bpp"

    return InitPokegearModeIndicatorArrow();
}

void InitPokegearModeIndicatorArrow(void){
    //depixel ['4', '2', '4', '0']
    depixel4(4, 2, 4, 0);
    LD_A(SPRITE_ANIM_INDEX_POKEGEAR_ARROW);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

}

void InitPokegearModeIndicatorArrow_Conv(void){
    //depixel ['4', '2', '4', '0']
    depixel4(4, 2, 4, 0);
    LD_A(SPRITE_ANIM_INDEX_POKEGEAR_ARROW);
    CALL(aInitSpriteAnimStruct);
    REG_HL = SPRITEANIMSTRUCT_TILE_ID + REG_BC;
    gb_write(REG_HL, 0x0);
}

void AnimatePokegearModeIndicatorArrow(void){
    LD_HL(wPokegearCard);
    LD_E_hl;
    LD_D(0);
    LD_HL(mAnimatePokegearModeIndicatorArrow_XCoords);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;


XCoords:
    //db ['0x00'];  // POKEGEARCARD_CLOCK
    //db ['0x10'];  // POKEGEARCARD_MAP
    //db ['0x20'];  // POKEGEARCARD_PHONE
    //db ['0x30'];  // POKEGEARCARD_RADIO

    return TownMap_GetCurrentLandmark();
}

void AnimatePokegearModeIndicatorArrow_Conv(uint16_t bc){
    uint16_t de = gb_read(wPokegearCard);
    uint16_t hl = mAnimatePokegearModeIndicatorArrow_XCoords + de;
    gb_write(SPRITEANIMSTRUCT_XOFFSET + bc, gb_read(hl));
}

void TownMap_GetCurrentLandmark(void){
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);
    CP_A(LANDMARK_SPECIAL);
    RET_NZ ;
    LD_A_addr(wBackupMapGroup);
    LD_B_A;
    LD_A_addr(wBackupMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);
    RET;

}

uint8_t TownMap_GetCurrentLandmark_Conv(void){
    uint8_t landmark = GetWorldMapLocation_Conv(gb_read(wMapGroup), gb_read(wMapNumber));
    if(landmark == LANDMARK_SPECIAL)
    {
        landmark = GetWorldMapLocation_Conv(gb_read(wBackupMapGroup), gb_read(wBackupMapNumber));
    }
    return landmark;
}

void TownMap_InitCursorAndPlayerIconPositions(void){
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);
    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto FastShip;
    CP_A(LANDMARK_SPECIAL);
    IF_NZ goto LoadLandmark;
    LD_A_addr(wBackupMapGroup);
    LD_B_A;
    LD_A_addr(wBackupMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);

LoadLandmark:
    LD_addr_A(wPokegearMapPlayerIconLandmark);
    LD_addr_A(wPokegearMapCursorLandmark);
    RET;


FastShip:
    LD_addr_A(wPokegearMapPlayerIconLandmark);
    LD_A(LANDMARK_NEW_BARK_TOWN);
    LD_addr_A(wPokegearMapCursorLandmark);
    RET;

}

void TownMap_InitCursorAndPlayerIconPositions_Conv(void){
    //LD_A_addr(wMapGroup);
    //LD_B_A;
    //LD_A_addr(wMapNumber);
    //LD_C_A;
    //CALL(aGetWorldMapLocation);
    uint8_t landmark = GetWorldMapLocation_Conv(gb_read(wMapGroup), gb_read(wMapNumber));

    //CP_A(LANDMARK_FAST_SHIP);
    //IF_Z goto FastShip;
    if(landmark == LANDMARK_FAST_SHIP)
    {
        //LD_addr_A(wPokegearMapPlayerIconLandmark);
        gb_write(wPokegearMapPlayerIconLandmark, landmark);
        //LD_A(LANDMARK_NEW_BARK_TOWN);
        //LD_addr_A(wPokegearMapCursorLandmark);
        gb_write(wPokegearMapCursorLandmark, LANDMARK_NEW_BARK_TOWN);
        return;
    }
    
    //CP_A(LANDMARK_SPECIAL);
    //IF_NZ goto LoadLandmark;
    if(landmark == LANDMARK_SPECIAL)
    {
        landmark = GetWorldMapLocation_Conv(gb_read(wBackupMapGroup), gb_read(wBackupMapNumber));
    }

    //LD_addr_A(wPokegearMapPlayerIconLandmark);
    //LD_addr_A(wPokegearMapCursorLandmark);
    gb_write(wPokegearMapPlayerIconLandmark, landmark);
    gb_write(wPokegearMapCursorLandmark, landmark);
    return;
}

void Pokegear_InitJumptableIndices(void){
    LD_A(POKEGEARSTATE_CLOCKINIT);
    LD_addr_A(wJumptableIndex);
    XOR_A_A;  // POKEGEARCARD_CLOCK
    LD_addr_A(wPokegearCard);
    RET;

}

void Pokegear_InitJumptableIndices_Conv(void){
    gb_write(wJumptableIndex, POKEGEARSTATE_CLOCKINIT);
    gb_write(wPokegearCard, POKEGEARCARD_CLOCK);  // POKEGEARCARD_CLOCK
}

void InitPokegearTilemap(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    LD_A(0x4f);
    CALL(aByteFill);
    LD_A_addr(wPokegearCard);
    maskbits(NUM_POKEGEAR_CARDS, 0);
    // ADD_A_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mInitPokegearTilemap_Jumptable);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mInitPokegearTilemap_return_from_jumptable);
    // PUSH_DE;
    goto Jumptable;
    // JP_hl;


return_from_jumptable:
    CALL(aPokegear_FinishTilemap);
    FARCALL(aTownMapPals);
    LD_A_addr(wPokegearMapRegion);
    AND_A_A;
    IF_NZ goto kanto_0;
    XOR_A_A;  // LOW(vBGMap0)
    LDH_addr_A(hBGMapAddress);
    LD_A(HIGH(vBGMap0));
    LDH_addr_A(hBGMapAddress + 1);
    CALL(aInitPokegearTilemap_UpdateBGMap);
    LD_A(SCREEN_HEIGHT_PX);
    goto finish;


kanto_0:
    XOR_A_A;  // LOW(vBGMap1)
    LDH_addr_A(hBGMapAddress);
    LD_A(HIGH(vBGMap1));
    LDH_addr_A(hBGMapAddress + 1);
    CALL(aInitPokegearTilemap_UpdateBGMap);
    XOR_A_A;

finish:
    LDH_addr_A(hWY);
// swap region maps
    LD_A_addr(wPokegearMapRegion);
    maskbits(NUM_REGIONS, 0);
    XOR_A(1);
    LD_addr_A(wPokegearMapRegion);
    RET;


UpdateBGMap:
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto dmg;
    LD_A(0x2);
    LDH_addr_A(hBGMapMode);
    LD_C(3);
    CALL(aDelayFrames);

dmg:
    CALL(aWaitBGMap);
    RET;


Jumptable:
//  entries correspond to POKEGEARCARD_* constants
    // SET_PC(aInitPokegearTilemap_Jumptable);
    switch(REG_A)
    {
        case POKEGEARCARD_CLOCK: goto Clock;
        case POKEGEARCARD_MAP:   goto Map;
        case POKEGEARCARD_PHONE: goto Phone;
        case POKEGEARCARD_RADIO: goto Radio;
    }
    //dw ['.Clock'];
    //dw ['.Map'];
    //dw ['.Phone'];
    //dw ['.Radio'];


Clock:
    LD_DE(mClockTilemapRLE);
    CALL(aPokegear_LoadTilemapRLE);
    hlcoord(12, 1, wTilemap);
    LD_DE(mInitPokegearTilemap_switch);
    CALL(aPlaceString);
    hlcoord(0, 12, wTilemap);
    LD_BC((4 << 8) | 18);
    CALL(aTextbox);
    CALL(aPokegear_UpdateClock);
    // Pokegear_UpdateClock();
    // RET;
    goto return_from_jumptable;

    //_switch:
    //db ['" SWITCH▶@"'];

Map:
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto johto;
    CP_A(KANTO_LANDMARK);
    IF_NC goto kanto;

johto:
    LD_E(0);
    goto ok;


kanto:
    LD_E(1);

ok:
    FARCALL(aPokegearMap);
    LD_A(0x07);
    LD_BC(SCREEN_WIDTH - 2);
    hlcoord(1, 2, wTilemap);
    CALL(aByteFill);
    hlcoord(0, 2, wTilemap);
    LD_hl(0x06);
    hlcoord(19, 2, wTilemap);
    LD_hl(0x17);
    LD_A_addr(wPokegearMapCursorLandmark);
    CALL(aPokegearMap_UpdateLandmarkName);
    // RET;
    goto return_from_jumptable;


Radio:
    LD_DE(mRadioTilemapRLE);
    CALL(aPokegear_LoadTilemapRLE);
    hlcoord(0, 12, wTilemap);
    LD_BC((4 << 8) | 18);
    CALL(aTextbox);
    // RET;
    goto return_from_jumptable;


Phone:
    LD_DE(mPhoneTilemapRLE);
    CALL(aPokegear_LoadTilemapRLE);
    hlcoord(0, 12, wTilemap);
    LD_BC((4 << 8) | 18);
    CALL(aTextbox);
    CALL(aInitPokegearTilemap_PlacePhoneBars);
    CALL(aPokegearPhone_UpdateDisplayList);
    // RET;
    goto return_from_jumptable;


PlacePhoneBars:
    hlcoord(17, 1, wTilemap);
    LD_A(0x3c);
    LD_hli_A;
    INC_A;
    LD_hl_A;
    hlcoord(17, 2, wTilemap);
    INC_A;
    LD_hli_A;
    CALL(aGetMapPhoneService);
    AND_A_A;
    RET_NZ ;
    hlcoord(18, 2, wTilemap);
    LD_hl(0x3f);
    RET;

}

void InitPokegearTilemap_Conv(void){
    gb_write(hBGMapMode, 0);
    ByteFill_Conv(coord(0, 0, wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x4F);
    uint8_t card = gb_read(wPokegearCard) & (NUM_POKEGEAR_CARDS - 1);
    switch(card)
    {
        case POKEGEARCARD_CLOCK:
        {
            Pokegear_LoadTilemapRLE_Conv(mClockTilemapRLE);
            hlcoord(12, 1, wTilemap);
            LD_DE(mInitPokegearTilemap_switch);
            CALL(aPlaceString);
            Textbox_Conv(coord(0, 12, wTilemap), 4, 18);
            Pokegear_UpdateClock_Conv();
        }
        break;
        case POKEGEARCARD_MAP:
        {
            uint8_t landmark = gb_read(wPokegearMapPlayerIconLandmark);
            REG_A = landmark;
            if(landmark != LANDMARK_FAST_SHIP && landmark >= KANTO_LANDMARK)
            {
                REG_E = 1;
            }
            else
            {
                REG_E = 0;
            }
            FARCALL(aPokegearMap);
            ByteFill_Conv(coord(1, 2, wTilemap), (SCREEN_WIDTH - 2), 0x07);
            gb_write(coord(0, 2, wTilemap), 0x06);
            gb_write(coord(19, 2, wTilemap), 0x17);
            // REG_A = gb_read(wPokegearMapCursorLandmark);
            // CALL(aPokegearMap_UpdateLandmarkName);
            PokegearMap_UpdateLandmarkName_Conv(gb_read(wPokegearMapCursorLandmark));
        }
        break;
        case POKEGEARCARD_PHONE:
        {
            Pokegear_LoadTilemapRLE_Conv(mPhoneTilemapRLE);
            Textbox_Conv(coord(0, 12, wTilemap), 4, 18);
            InitPokegearTilemap_PlacePhoneBars_Conv();
            CALL(aPokegearPhone_UpdateDisplayList);
            //RET;
        }
        break;
        case POKEGEARCARD_RADIO:
        {
            Pokegear_LoadTilemapRLE_Conv(mRadioTilemapRLE);
            Textbox_Conv(coord(0, 12, wTilemap), 4, 18);
        }
        break;
    }

    // CALL(aPokegear_FinishTilemap);
    Pokegear_FinishTilemap_Conv();

    FARCALL(aTownMapPals);
    if(gb_read(wPokegearMapRegion) == KANTO_REGION)
    {
        gb_write16(hBGMapAddress, vBGMap1);
        InitPokegearTilemap_UpdateBGMap_Conv();
        gb_write(hWY, 0);
    }
    else 
    {
        gb_write16(hBGMapAddress, vBGMap0);
        InitPokegearTilemap_UpdateBGMap_Conv();
        gb_write(hWY, SCREEN_HEIGHT_PX);
    }
// swap region maps
    gb_write(wPokegearMapRegion, (gb_read(wPokegearMapRegion) & (NUM_REGIONS - 1)) ^ 1);
}

void InitPokegearTilemap_UpdateBGMap_Conv(void) {
    if(gb_read(hCGB) == 0)
    {
        CALL(aWaitBGMap);
        return;
    }

    gb_write(hBGMapMode, 0x2);
    LD_C(3);
    CALL(aDelayFrames);
}

void InitPokegearTilemap_PlacePhoneBars_Conv() {
    uint16_t hl = coord(17, 1, wTilemap);
    uint8_t tile = 0x3C;
    gb_write(hl++, tile++);
    gb_write(hl, tile++);
    hl = coord(17, 2, wTilemap);
    gb_write(hl++, tile);

    // CALL(aGetMapPhoneService);
    uint8_t srv = GetMapPhoneService_Conv();
    if(srv != 0)
    {
        return;
    }
    gb_write(coord(18, 2, wTilemap), 0x3F);
}

void Pokegear_FinishTilemap(void){
    hlcoord(0, 0, wTilemap);
    LD_BC(0x8);
    LD_A(0x4f);
    CALL(aByteFill);
    hlcoord(0, 1, wTilemap);
    LD_BC(0x8);
    LD_A(0x4f);
    CALL(aByteFill);
    LD_DE(wPokegearFlags);
    LD_A_de;
    BIT_A(POKEGEAR_MAP_CARD_F);
    CALL_NZ (aPokegear_FinishTilemap_PlaceMapIcon);
    LD_A_de;
    BIT_A(POKEGEAR_PHONE_CARD_F);
    CALL_NZ (aPokegear_FinishTilemap_PlacePhoneIcon);
    LD_A_de;
    BIT_A(POKEGEAR_RADIO_CARD_F);
    CALL_NZ (aPokegear_FinishTilemap_PlaceRadioIcon);
    hlcoord(0, 0, wTilemap);
    LD_A(0x46);
    CALL(aPokegear_FinishTilemap_PlacePokegearCardIcon);
    RET;


PlaceMapIcon:
    hlcoord(2, 0, wTilemap);
    LD_A(0x40);
    goto PlacePokegearCardIcon;


PlacePhoneIcon:
    hlcoord(4, 0, wTilemap);
    LD_A(0x44);
    goto PlacePokegearCardIcon;


PlaceRadioIcon:
    hlcoord(6, 0, wTilemap);
    LD_A(0x42);

PlacePokegearCardIcon:
    LD_hli_A;
    INC_A;
    LD_hld_A;
    LD_BC(0x14);
    ADD_HL_BC;
    ADD_A(0xf);
    LD_hli_A;
    INC_A;
    LD_hld_A;
    RET;

}

void Pokegear_FinishTilemap_Conv(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(0x8);
    // LD_A(0x4f);
    // CALL(aByteFill);
    ByteFill_Conv(coord(0, 0, wTilemap), 0x8, 0x4f);

    // hlcoord(0, 1, wTilemap);
    // LD_BC(0x8);
    // LD_A(0x4f);
    // CALL(aByteFill);
    ByteFill_Conv(coord(0, 1, wTilemap), 0x8, 0x4f);

    // LD_DE(wPokegearFlags);
    // LD_A_de;
    uint8_t flags = gb_read(wPokegearFlags);

    // BIT_A(POKEGEAR_MAP_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlaceMapIcon);
    if(flags & (1 << POKEGEAR_MAP_CARD_F))
    {
        // hlcoord(2, 0, wTilemap);
        uint16_t hl = coord(2, 0, wTilemap);

        // LD_A(0x40);
        // LD_hli_A;
        gb_write(hl++, 0x40);

        // INC_A;
        // LD_hld_A;
        gb_write(hl--, 0x41);

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        gb_write(hl++, 0x50);

        // INC_A;
        // LD_hld_A;
        gb_write(hl--, 0x51);
    }

    // LD_A_de;
    // BIT_A(POKEGEAR_PHONE_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlacePhoneIcon);
    if(flags & (1 << POKEGEAR_PHONE_CARD_F))
    {
        // hlcoord(4, 0, wTilemap);
        uint16_t hl = coord(4, 0, wTilemap);

        // LD_A(0x44);
        // LD_hli_A;
        gb_write(hl++, 0x44);

        // INC_A;
        // LD_hld_A;
        gb_write(hl--, 0x45);

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        gb_write(hl++, 0x54);

        // INC_A;
        // LD_hld_A;
        gb_write(hl--, 0x55);
    }

    // LD_A_de;
    // BIT_A(POKEGEAR_RADIO_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlaceRadioIcon);
    if(flags & (1 << POKEGEAR_RADIO_CARD_F))
    {
        // hlcoord(6, 0, wTilemap);
        uint16_t hl = coord(6, 0, wTilemap);

        // LD_A(0x42);
        // LD_hli_A;
        gb_write(hl++, 0x42);

        // INC_A;
        // LD_hld_A;
        gb_write(hl--, 0x43);

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        gb_write(hl++, 0x52);

        // INC_A;
        // LD_hld_A;
        gb_write(hl--, 0x53);
    }

    // hlcoord(0, 0, wTilemap);
    uint16_t hl = coord(0, 0, wTilemap);

    // LD_A(0x46);
    // LD_hli_A;
    gb_write(hl++, 0x46);

    // INC_A;
    // LD_hld_A;
    gb_write(hl--, 0x47);

    // LD_BC(0x14);
    // ADD_HL_BC;
    hl += 0x14;

    // ADD_A(0xf);
    // LD_hli_A;
    gb_write(hl++, 0x56);

    // INC_A;
    // LD_hld_A;
    gb_write(hl--, 0x57);
}

void PokegearJumptable(void) {
    //jumptable ['.Jumptable', 'wJumptableIndex']
    // jumptable(mPokegearJumptable_Jumptable, wJumptableIndex);
    // return;


Jumptable:
//  entries correspond to POKEGEARSTATE_* constants
    switch(gb_read(wJumptableIndex))
    {
        case POKEGEARSTATE_CLOCKINIT:      return PokegearClock_Init();
        case POKEGEARSTATE_CLOCKJOYPAD:    return PokegearClock_Joypad();
        case POKEGEARSTATE_MAPCHECKREGION: return PokegearMap_CheckRegion();
        case POKEGEARSTATE_JOHTOMAPINIT:   return PokegearMap_Init();
        case POKEGEARSTATE_JOHTOMAPJOYPAD: return PokegearMap_JohtoMap();
        case POKEGEARSTATE_KANTOMAPINIT:   return PokegearMap_Init();
        case POKEGEARSTATE_KANTOMAPJOYPAD: return PokegearMap_KantoMap();
        case POKEGEARSTATE_PHONEINIT:      return PokegearPhone_Init();
        case POKEGEARSTATE_PHONEJOYPAD:    return PokegearPhone_Joypad();
        case POKEGEARSTATE_MAKEPHONECALL:  return PokegearPhone_MakePhoneCall();
        case POKEGEARSTATE_FINISHPHONECALL:return PokegearPhone_FinishPhoneCall();
        case POKEGEARSTATE_RADIOINIT:      return PokegearRadio_Init();
        case POKEGEARSTATE_RADIOJOYPAD:    return PokegearRadio_Joypad();
        default: RET;
    }
    //dw ['PokegearClock_Init'];
    //dw ['PokegearClock_Joypad'];
    //dw ['PokegearMap_CheckRegion'];
    //dw ['PokegearMap_Init'];
    //dw ['PokegearMap_JohtoMap'];
    //dw ['PokegearMap_Init'];
    //dw ['PokegearMap_KantoMap'];
    //dw ['PokegearPhone_Init'];
    //dw ['PokegearPhone_Joypad'];
    //dw ['PokegearPhone_MakePhoneCall'];
    //dw ['PokegearPhone_FinishPhoneCall'];
    //dw ['PokegearRadio_Init'];
    //dw ['PokegearRadio_Joypad'];
}

void PokegearClock_Init(void) {
    CALL(aInitPokegearTilemap);
    LD_HL(mPokegearPressButtonText);
    CALL(aPrintText);
    LD_HL(wJumptableIndex);
    INC_hl;
    CALL(aExitPokegearRadio_HandleMusic);
    RET;

}

void PokegearClock_Init_Conv(void) {
    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap_Conv();

    REG_HL = mPokegearPressButtonText;
    CALL(aPrintText);

    gb_write(wJumptableIndex, gb_read(wJumptableIndex) + 1);

    REG_HL = wJumptableIndex;
    CALL(aExitPokegearRadio_HandleMusic);
    RET;

}

void PokegearClock_Joypad(void){
    SET_PC(aPokegearClock_Joypad);
    CALL(aPokegearClock_Joypad_UpdateClock);
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(A_BUTTON | B_BUTTON | START | SELECT);
    IF_NZ goto quit;
    LD_A_hl;
    AND_A(D_RIGHT);
    // IF_Z return;
    RET_Z ;
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_MAP_CARD_F);
    IF_Z goto no_map_card;
    LD_C(POKEGEARSTATE_MAPCHECKREGION);
    LD_B(POKEGEARCARD_MAP);
    goto done;


no_map_card:
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_PHONE_CARD_F);
    IF_Z goto no_phone_card;
    LD_C(POKEGEARSTATE_PHONEINIT);
    LD_B(POKEGEARCARD_PHONE);
    goto done;


no_phone_card:
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_RADIO_CARD_F);
    RET_Z ;
    LD_C(POKEGEARSTATE_RADIOINIT);
    LD_B(POKEGEARCARD_RADIO);

done:
    CALL(aPokegear_SwitchPage);
    // return;
    RET;


quit:
    LD_HL(wJumptableIndex);
    SET_hl(7);
    // return;
    RET;


UpdateClock:
    // PEEK("UpdateClock");
    SET_PC(aPokegearClock_Joypad_UpdateClock);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    // CALL(aPokegear_UpdateClock);
    Pokegear_UpdateClock_Conv();
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void PokegearClock_Joypad_UpdateClock(void) {
    SET_PC(aPokegearClock_Joypad_UpdateClock);
    // PEEK("UpdateClock");
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aPokegear_UpdateClock);
    // Pokegear_UpdateClock();
    Pokegear_UpdateClock_Conv();
    DelayFrames_Conv(4);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 1;
    DelayFrames_Conv(4);
    RET;
}

void Pokegear_UpdateClock(void){
    PEEK("UpdateClock");
    hlcoord(3, 5, wTilemap);
    LD_BC((5 << 8) | 14);
    CALL(aClearBox);
    LDH_A_addr(hHours);
    LD_B_A;
    LDH_A_addr(hMinutes);
    LD_C_A;
    decoord(6, 8, wTilemap);
    FARCALL(aPrintHoursMins);
    LD_HL(mPokegear_UpdateClock_GearTodayText);
    bccoord(6, 6, wTilemap);
    CALL(aPlaceHLTextAtBC);
    // return;
    RET;

    //db ['"ごぜん@"'];
    //db ['"ごご@"'];


GearTodayText:
    //text_far ['_GearTodayText']
    //text_end ['?']

    return PokegearMap_CheckRegion();
}

void Pokegear_UpdateClock_Conv(void){
    PEEK("UpdateClock");
    ClearBox_Conv(coord(3, 5, wTilemap), ((5 << 8) | 14));
    // LDH_A_addr(hHours);
    // LD_B_A;
    // LDH_A_addr(hMinutes);
    // LD_C_A;
    // REG_B = gb_read(hHours);
    // REG_C = gb_read(hMinutes);
    // REG_DE = coord(6, 8, wTilemap);
    // decoord(6, 8, wTilemap);
    // FARCALL(aPrintHoursMins);
    farcall(PrintHoursMins, wram->wTilemap + coordidx(6, 8), gb_read(hHours), gb_read(hMinutes));
    // bank_push(aPrintHoursMins);
    // bank_pop;
    // LD_HL(mPokegear_UpdateClock_GearTodayText);
    // bccoord(6, 6, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv(GBToRAMAddr(mPokegear_UpdateClock_GearTodayText), wram->wTilemap + coordidx(6, 6));
}

void PokegearMap_CheckRegion(void){
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto johto;
    CP_A(KANTO_LANDMARK);
    IF_NC goto kanto;

johto:
    LD_A(POKEGEARSTATE_JOHTOMAPINIT);
    goto done;
    // return;
    RET;


kanto:
    LD_A(POKEGEARSTATE_KANTOMAPINIT);

done:
    LD_addr_A(wJumptableIndex);
    CALL(aExitPokegearRadio_HandleMusic);
    // return;
    RET;

}

void PokegearMap_Init(void){
    CALL(aInitPokegearTilemap);
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CALL(aPokegearMap_InitPlayerIcon);
    LD_A_addr(wPokegearMapCursorLandmark);
    CALL(aPokegearMap_InitCursor);
    LD_A_C;
    LD_addr_A(wPokegearMapCursorObjectPointer);
    LD_A_B;
    LD_addr_A(wPokegearMapCursorObjectPointer + 1);
    LD_HL(wJumptableIndex);
    INC_hl;
    // return;
    RET;

}

void PokegearMap_KantoMap(void){
    CALL(aTownMap_GetKantoLandmarkLimits);
    JR(mPokegearMap_ContinueMap);

}

void PokegearMap_JohtoMap(void){
    LD_D(LANDMARK_SILVER_CAVE);
    LD_E(LANDMARK_NEW_BARK_TOWN);
    return PokegearMap_ContinueMap();
}

void PokegearMap_ContinueMap(void){
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto cancel;
    LD_A_hl;
    AND_A(D_RIGHT);
    IF_NZ goto right;
    LD_A_hl;
    AND_A(D_LEFT);
    IF_NZ goto left;
    CALL(aPokegearMap_ContinueMap_DPad);
    return;
    //RET;


right:
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_PHONE_CARD_F);
    IF_Z goto no_phone;
    LD_C(POKEGEARSTATE_PHONEINIT);
    LD_B(POKEGEARCARD_PHONE);
    goto done;


no_phone:
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_RADIO_CARD_F);
    RET_Z ;
    LD_C(POKEGEARSTATE_RADIOINIT);
    LD_B(POKEGEARCARD_RADIO);
    goto done;


left:
    LD_C(POKEGEARSTATE_CLOCKINIT);
    LD_B(POKEGEARCARD_CLOCK);

done:
    CALL(aPokegear_SwitchPage);
    // return;
    RET;


cancel:
    LD_HL(wJumptableIndex);
    SET_hl(7);
    // return;
    RET;


DPad:
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto up;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto down;
    // return;
    RET;


up:
    LD_HL(wPokegearMapCursorLandmark);
    LD_A_hl;
    CP_A_D;
    IF_C goto wrap_around_up;
    LD_A_E;
    DEC_A;
    LD_hl_A;

wrap_around_up:
    INC_hl;
    goto done_dpad;


down:
    LD_HL(wPokegearMapCursorLandmark);
    LD_A_hl;
    CP_A_E;
    IF_NZ goto wrap_around_down;
    LD_A_D;
    INC_A;
    LD_hl_A;

wrap_around_down:
    DEC_hl;

done_dpad:
    LD_A_addr(wPokegearMapCursorLandmark);
    CALL(aPokegearMap_UpdateLandmarkName);
    LD_A_addr(wPokegearMapCursorObjectPointer);
    LD_C_A;
    LD_A_addr(wPokegearMapCursorObjectPointer + 1);
    LD_B_A;
    LD_A_addr(wPokegearMapCursorLandmark);
    CALL(aPokegearMap_UpdateCursorPosition);
    RET;
    // return;

}

void PokegearMap_InitPlayerIcon(void){
    PUSH_AF;
    //depixel ['0', '0']
    depixel2(0, 0);
    LD_B(SPRITE_ANIM_INDEX_RED_WALK);
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto got_gender;
    LD_B(SPRITE_ANIM_INDEX_BLUE_WALK);

got_gender:
    LD_A_B;
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl(0x10);
    POP_AF;
    LD_E_A;
    PUSH_BC;
    FARCALL(aGetLandmarkCoords);
    POP_BC;
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hl_D;
    RET;

}

void PokegearMap_InitCursor(void){
    PUSH_AF;
    //depixel ['0', '0']
    depixel2(0, 0);
    LD_A(SPRITE_ANIM_INDEX_POKEGEAR_ARROW);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl(0x04);
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_hl(SPRITE_ANIM_SEQ_NULL);
    POP_AF;
    PUSH_BC;
    CALL(aPokegearMap_UpdateCursorPosition);
    POP_BC;
    RET;

}

void PokegearMap_UpdateLandmarkName(void){
    PUSH_AF;
    hlcoord(8, 0, wTilemap);
    LD_BC((2 << 8) | 12);
    CALL(aClearBox);
    POP_AF;
    LD_E_A;
    PUSH_DE;
    FARCALL(aGetLandmarkName);
    POP_DE;
    FARCALL(aTownMap_ConvertLineBreakCharacters);
    hlcoord(8, 0, wTilemap);
    LD_hl(0x34);
    RET;

}

void PokegearMap_UpdateLandmarkName_Conv(uint8_t landmark){
    // hlcoord(8, 0, wTilemap);
    // LD_BC((2 << 8) | 12);
    // CALL(aClearBox);
    ClearBox_Conv(coord(8, 0, wTilemap), (2 << 8) | 12);

    // LD_E_A;
    REG_DE = landmark;
    PUSH_DE;
    FARCALL(aGetLandmarkName);
    POP_DE;
    FARCALL(aTownMap_ConvertLineBreakCharacters);

    // hlcoord(8, 0, wTilemap);
    // LD_hl(0x34);
    gb_write(coord(8, 0, wTilemap), 0x34);
}

void PokegearMap_UpdateCursorPosition(void){
    PUSH_BC;
    LD_E_A;
    FARCALL(aGetLandmarkCoords);
    POP_BC;
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hl_D;
    RET;

}

void TownMap_GetKantoLandmarkLimits(void){
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
    IF_Z goto not_hof;
    LD_D(LANDMARK_ROUTE_28);
    LD_E(LANDMARK_PALLET_TOWN);
    RET;


not_hof:
    LD_D(LANDMARK_ROUTE_28);
    LD_E(LANDMARK_VICTORY_ROAD);
    RET;

}

void PokegearRadio_Init(void){
    CALL(aInitPokegearTilemap);
    //depixel ['4', '10', '4', '4']
    depixel4(4, 10, 4, 4);
    LD_A(SPRITE_ANIM_INDEX_RADIO_TUNING_KNOB);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl(0x08);
    CALL(av_UpdateRadioStation);
    LD_HL(wJumptableIndex);
    INC_hl;
    //RET;

}

void PokegearRadio_Joypad(void){
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto cancel;
    LD_A_hl;
    AND_A(D_LEFT);
    IF_NZ goto left;
    LD_A_addr(wPokegearRadioChannelAddr);
    LD_L_A;
    LD_A_addr(wPokegearRadioChannelAddr + 1);
    LD_H_A;
    LD_A_addr(wPokegearRadioChannelBank);
    AND_A_A;
    RET_Z ;
    RST(aFarCall);
    return;
    //RET;


left:
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_PHONE_CARD_F);
    IF_Z goto no_phone;
    LD_C(POKEGEARSTATE_PHONEINIT);
    LD_B(POKEGEARCARD_PHONE);
    goto switch_page;


no_phone:
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_MAP_CARD_F);
    IF_Z goto no_map;
    LD_C(POKEGEARSTATE_MAPCHECKREGION);
    LD_B(POKEGEARCARD_MAP);
    goto switch_page;


no_map:
    LD_C(POKEGEARSTATE_CLOCKINIT);
    LD_B(POKEGEARCARD_CLOCK);

switch_page:
    CALL(aPokegear_SwitchPage);
    return;
    //RET;


cancel:
    LD_HL(wJumptableIndex);
    SET_hl(7);
    //RET;

}

void PokegearPhone_Init(void){
    LD_HL(wJumptableIndex);
    INC_hl;
    XOR_A_A;
    LD_addr_A(wPokegearPhoneScrollPosition);
    LD_addr_A(wPokegearPhoneCursorPosition);
    LD_addr_A(wPokegearPhoneSelectedPerson);
    CALL(aInitPokegearTilemap);
    CALL(aExitPokegearRadio_HandleMusic);
    LD_HL(mPokegearAskWhoCallText);
    CALL(aPrintText);
    RET;

}

void PokegearPhone_Init_Conv(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    gb_write(wJumptableIndex, gb_read(wJumptableIndex) + 1);
    // XOR_A_A;
    // LD_addr_A(wPokegearPhoneScrollPosition);
    // LD_addr_A(wPokegearPhoneCursorPosition);
    // LD_addr_A(wPokegearPhoneSelectedPerson);
    gb_write(wPokegearPhoneScrollPosition, 0);
    gb_write(wPokegearPhoneCursorPosition, 0);
    gb_write(wPokegearPhoneSelectedPerson, 0);
    CALL(aInitPokegearTilemap);
    CALL(aExitPokegearRadio_HandleMusic);
    LD_HL(mPokegearAskWhoCallText);
    CALL(aPrintText);
    // RET;

}

void PokegearPhone_Joypad(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto b;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto a;
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_LEFT);
    IF_NZ goto left;
    LD_A_hl;
    AND_A(D_RIGHT);
    IF_NZ goto right;
    CALL(aPokegearPhone_GetDPad);
    // return;
    RET;


left:
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_MAP_CARD_F);
    IF_Z goto no_map;
    LD_C(POKEGEARSTATE_MAPCHECKREGION);
    LD_B(POKEGEARCARD_MAP);
    goto switch_page;


no_map:
    LD_C(POKEGEARSTATE_CLOCKINIT);
    LD_B(POKEGEARCARD_CLOCK);
    goto switch_page;


right:
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_RADIO_CARD_F);
    RET_Z ;
    LD_C(POKEGEARSTATE_RADIOINIT);
    LD_B(POKEGEARCARD_RADIO);

switch_page:
    CALL(aPokegear_SwitchPage);
    // return;
    RET;


b:
    LD_HL(wJumptableIndex);
    SET_hl(7);
    // return;
    RET;


a:
    LD_HL(wPhoneList);
    LD_A_addr(wPokegearPhoneScrollPosition);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wPokegearPhoneCursorPosition);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    LD_addr_A(wPokegearPhoneSelectedPerson);
    hlcoord(1, 4, wTilemap);
    LD_A_addr(wPokegearPhoneCursorPosition);
    LD_BC(SCREEN_WIDTH * 2);
    CALL(aAddNTimes);
    LD_hl(0xec);
    CALL(aPokegearPhoneContactSubmenu);
    IF_C goto quit_submenu;
    LD_HL(wJumptableIndex);
    INC_hl;
    // return;
    RET;


quit_submenu:
    LD_A(POKEGEARSTATE_PHONEJOYPAD);
    LD_addr_A(wJumptableIndex);
    // return;
    RET;

}

void PokegearPhone_MakePhoneCall(void){
    CALL(aGetMapPhoneService);
    AND_A_A;
    IF_NZ goto no_service;
    LD_HL(wOptions);
    RES_hl(NO_TEXT_SCROLL);
    XOR_A_A;
    LDH_addr_A(hInMenu);
    LD_DE(SFX_CALL);
    CALL(aPlaySFX);
    LD_HL(mPokegearPhone_MakePhoneCall_GearEllipseText);
    CALL(aPrintText);
    CALL(aWaitSFX);
    LD_DE(SFX_CALL);
    CALL(aPlaySFX);
    LD_HL(mPokegearPhone_MakePhoneCall_GearEllipseText);
    CALL(aPrintText);
    CALL(aWaitSFX);
    LD_A_addr(wPokegearPhoneSelectedPerson);
    LD_B_A;
    CALL(aMakePhoneCallFromPokegear);
    LD_C(10);
    CALL(aDelayFrames);
    LD_HL(wOptions);
    SET_hl(NO_TEXT_SCROLL);
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    CALL(aPokegearPhone_UpdateCursor);
    LD_HL(wJumptableIndex);
    INC_hl;
    return;
    //RET;


no_service:
    FARCALL(aPhone_NoSignal);
    LD_HL(mPokegearPhone_MakePhoneCall_GearOutOfServiceText);
    CALL(aPrintText);
    LD_A(POKEGEARSTATE_PHONEJOYPAD);
    LD_addr_A(wJumptableIndex);
    LD_HL(mPokegearAskWhoCallText);
    CALL(aPrintText);
    return;
    //RET;


GearEllipseText:
    //text_far ['_GearEllipseText']
    //text_end ['?']


GearOutOfServiceText:
    //text_far ['_GearOutOfServiceText']
    //text_end ['?']

    return PokegearPhone_FinishPhoneCall();
}

void PokegearPhone_FinishPhoneCall(void){
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON | B_BUTTON);
    RET_Z ;
    FARCALL(aHangUp);
    LD_A(POKEGEARSTATE_PHONEJOYPAD);
    LD_addr_A(wJumptableIndex);
    LD_HL(mPokegearAskWhoCallText);
    CALL(aPrintText);
    //RET;

}

void PokegearPhone_GetDPad(void){
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto up;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto down;
    RET;


up:
    LD_HL(wPokegearPhoneCursorPosition);
    LD_A_hl;
    AND_A_A;
    IF_Z goto scroll_page_up;
    DEC_hl;
    goto done_joypad_same_page;


scroll_page_up:
    LD_HL(wPokegearPhoneScrollPosition);
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    goto done_joypad_update_page;


down:
    LD_HL(wPokegearPhoneCursorPosition);
    LD_A_hl;
    CP_A(PHONE_DISPLAY_HEIGHT - 1);
    IF_NC goto scroll_page_down;
    INC_hl;
    goto done_joypad_same_page;


scroll_page_down:
    LD_HL(wPokegearPhoneScrollPosition);
    LD_A_hl;
    CP_A(CONTACT_LIST_SIZE - PHONE_DISPLAY_HEIGHT);
    RET_NC ;
    INC_hl;
    goto done_joypad_update_page;


done_joypad_same_page:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPokegearPhone_UpdateCursor);
    CALL(aWaitBGMap);
    RET;


done_joypad_update_page:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPokegearPhone_UpdateDisplayList);
    CALL(aWaitBGMap);
    RET;

}

void PokegearPhone_UpdateCursor(void){
    LD_A(0x7f);
    for(int y = 0; y < PHONE_DISPLAY_HEIGHT; y++){
    hlcoord(1, 4 + y * 2, wTilemap);
    LD_hl_A;
    }
    hlcoord(1, 4, wTilemap);
    LD_A_addr(wPokegearPhoneCursorPosition);
    LD_BC(2 * SCREEN_WIDTH);
    CALL(aAddNTimes);
    LD_hl(0xed);
    RET;

}

void PokegearPhone_UpdateDisplayList(void){
    hlcoord(1, 3, wTilemap);
    LD_B(PHONE_DISPLAY_HEIGHT * 2 + 1);
    LD_A(0x7f);

row:
    LD_C(SCREEN_WIDTH - 2);

col:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    INC_HL;
    INC_HL;
    DEC_B;
    IF_NZ goto row;
    LD_A_addr(wPokegearPhoneScrollPosition);
    LD_E_A;
    LD_D(0);
    LD_HL(wPhoneList);
    ADD_HL_DE;
    XOR_A_A;
    LD_addr_A(wPokegearPhoneDisplayPosition);

loop:
    LD_A_hli;
    PUSH_HL;
    PUSH_AF;
    hlcoord(2, 4, wTilemap);
    LD_A_addr(wPokegearPhoneDisplayPosition);
    LD_BC(2 * SCREEN_WIDTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    POP_AF;
    LD_B_A;
    CALL(aGetCallerClassAndName);
    POP_HL;
    LD_A_addr(wPokegearPhoneDisplayPosition);
    INC_A;
    LD_addr_A(wPokegearPhoneDisplayPosition);
    CP_A(PHONE_DISPLAY_HEIGHT);
    IF_C goto loop;
    CALL(aPokegearPhone_UpdateCursor);
    RET;

}

void PokegearPhone_DeletePhoneNumber(void){
    LD_HL(wPhoneList);
    LD_A_addr(wPokegearPhoneScrollPosition);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wPokegearPhoneCursorPosition);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_hl(0);
    LD_HL(wPhoneList);
    LD_C(CONTACT_LIST_SIZE);

loop:
    LD_A_hli;
    AND_A_A;
    IF_NZ goto skip;
    LD_A_hld;
    LD_hli_A;
    LD_hl(0);

skip:
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void PokegearPhoneContactSubmenu(void){
    LD_HL(wPhoneList);
    LD_A_addr(wPokegearPhoneScrollPosition);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wPokegearPhoneCursorPosition);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_C_hl;
    FARCALL(aCheckCanDeletePhoneNumber);
    LD_A_C;
    AND_A_A;
    IF_Z goto cant_delete;
    LD_HL(mPokegearPhoneContactSubmenu_CallDeleteCancelJumptable);
    LD_DE(mPokegearPhoneContactSubmenu_CallDeleteCancelStrings);
    goto got_menu_data;


cant_delete:
    LD_HL(mPokegearPhoneContactSubmenu_CallCancelJumptable);
    LD_DE(mPokegearPhoneContactSubmenu_CallCancelStrings);

got_menu_data:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    PUSH_HL;
    PUSH_DE;
    LD_A_de;
    LD_L_A;
    INC_DE;
    LD_A_de;
    LD_H_A;
    INC_DE;
    PUSH_HL;
    bccoord(-1, -2, 0);
    ADD_HL_BC;
    LD_A_de;
    INC_DE;
    SLA_A;
    LD_B_A;
    LD_C(8);
    PUSH_DE;
    CALL(aTextbox);
    POP_DE;
    POP_HL;
    INC_HL;
    CALL(aPlaceString);
    POP_DE;
    XOR_A_A;
    LD_addr_A(wPokegearPhoneSubmenuCursor);
    CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
    CALL(aWaitBGMap);

loop:
    PUSH_DE;
    CALL(aJoyTextDelay);
    POP_DE;
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto d_up;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto d_down;
    LD_A_hl;
    AND_A(A_BUTTON | B_BUTTON);
    IF_NZ goto a_b;
    CALL(aDelayFrame);
    goto loop;


d_up:
    LD_HL(wPokegearPhoneSubmenuCursor);
    LD_A_hl;
    AND_A_A;
    IF_Z goto loop;
    DEC_hl;
    CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
    goto loop;


d_down:
    LD_HL(2);
    ADD_HL_DE;
    LD_A_addr(wPokegearPhoneSubmenuCursor);
    INC_A;
    CP_A_hl;
    IF_NC goto loop;
    LD_addr_A(wPokegearPhoneSubmenuCursor);
    CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
    goto loop;


a_b:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPokegearPhone_UpdateDisplayList);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    POP_HL;
    LDH_A_addr(hJoyPressed);
    AND_A(B_BUTTON);
    IF_NZ goto Cancel;
    LD_A_addr(wPokegearPhoneSubmenuCursor);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


Cancel:
    LD_HL(mPokegearAskWhoCallText);
    CALL(aPrintText);
    SCF;
    RET;


Delete:
    LD_HL(mPokegearAskDeleteText);
    CALL(aMenuTextbox);
    CALL(aYesNoBox);
    CALL(aExitMenu);
    IF_C goto CancelDelete;
    CALL(aPokegearPhone_DeletePhoneNumber);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPokegearPhone_UpdateDisplayList);
    LD_HL(mPokegearAskWhoCallText);
    CALL(aPrintText);
    CALL(aWaitBGMap);

CancelDelete:
    SCF;
    RET;


Call:
    AND_A_A;
    RET;


UpdateCursor:
    PUSH_DE;
    LD_A_de;
    INC_DE;
    LD_L_A;
    LD_A_de;
    INC_DE;
    LD_H_A;
    LD_A_de;
    LD_C_A;
    PUSH_HL;
    LD_A(0x7f);
    LD_DE(SCREEN_WIDTH * 2);

clear_column:
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto clear_column;
    POP_HL;
    LD_A_addr(wPokegearPhoneSubmenuCursor);
    LD_BC(SCREEN_WIDTH * 2);
    CALL(aAddNTimes);
    LD_hl(0xed);
    POP_DE;
    RET;


CallDeleteCancelStrings:
    //dwcoord ['10', '6'];
    //db ['3'];
    //db ['"CALL"'];
    //next ['"DELETE"']
    //next ['"CANCEL"']
    //db ['"@"'];


CallDeleteCancelJumptable:
    //dw ['.Call'];
    //dw ['.Delete'];
    //dw ['.Cancel'];


CallCancelStrings:
    //dwcoord ['10', '8'];
    //db ['2'];
    //db ['"CALL"'];
    //next ['"CANCEL"']
    //db ['"@"'];


CallCancelJumptable:
    //dw ['.Call'];
    //dw ['.Cancel'];

    return GetAMPMHours();
}

void GetAMPMHours(void){
//  //  unreferenced
    LDH_A_addr(hHours);
    CP_A(NOON_HOUR);
    IF_C goto am;
    SUB_A(NOON_HOUR);
    LD_addr_A(wTempByteValue);
    SCF;
    RET;


am:
    LD_addr_A(wTempByteValue);
    AND_A_A;
    RET;

}

void Pokegear_SwitchPage(void){
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    LD_A_C;
    LD_addr_A(wJumptableIndex);
    LD_A_B;
    LD_addr_A(wPokegearCard);
    CALL(aDeleteSpriteAnimStruct2ToEnd);
    RET;

}

void ExitPokegearRadio_HandleMusic(void){
    LD_A_addr(wPokegearRadioMusicPlaying);
    CP_A(RESTART_MAP_MUSIC);
    IF_Z goto restart_map_music;
    CP_A(ENTER_MAP_MUSIC);
    CALL_Z (aPlayMapMusicBike);
    XOR_A_A;
    LD_addr_A(wPokegearRadioMusicPlaying);
    RET;


restart_map_music:
    CALL(aRestartMapMusic);
    XOR_A_A;
    LD_addr_A(wPokegearRadioMusicPlaying);
    RET;

}

void DeleteSpriteAnimStruct2ToEnd(void){
    LD_HL(wSpriteAnim2);
    LD_BC(wSpriteAnimationStructsEnd - wSpriteAnim2);
    XOR_A_A;
    CALL(aByteFill);
    LD_A(2);
    LD_addr_A(wSpriteAnimCount);
    RET;

}

void Pokegear_LoadTilemapRLE(void){
// Format: repeat count, tile ID
// Terminated with -1
    hlcoord(0, 0, wTilemap);

loop:
    LD_A_de;
    CP_A(-1);
    RET_Z ;
    LD_B_A;
    INC_DE;
    LD_A_de;
    LD_C_A;
    INC_DE;
    LD_A_B;

load:
    LD_hli_A;
    DEC_C;
    IF_NZ goto load;
    goto loop;

    return PokegearAskWhoCallText();
}

// Format: repeat count, tile ID
// Terminated with -1
void Pokegear_LoadTilemapRLE_Conv(uint16_t de){
    uint16_t hl = coord(0, 0, wTilemap);

    while(1)
    {
        uint8_t id = gb_read(de++);
        if(id == 0xff) 
            return;
        
        uint8_t repeat = gb_read(de++);
        do {
            gb_write(hl++, id);
        } while(--repeat != 0);
    }
}

void PokegearAskWhoCallText(void){
    //text_far ['_PokegearAskWhoCallText']
    //text_end ['?']

    return PokegearPressButtonText();
}

void PokegearPressButtonText(void){
    //text_far ['_PokegearPressButtonText']
    //text_end ['?']

    return PokegearAskDeleteText();
}

void PokegearAskDeleteText(void){
    //text_far ['_PokegearAskDeleteText']
    //text_end ['?']

    return PokegearSpritesGFX();
}

void PokegearSpritesGFX(void){
// INCBIN "gfx/pokegear/pokegear_sprites.2bpp.lz"

    return RadioTilemapRLE();
}

void RadioTilemapRLE(void){
// INCBIN "gfx/pokegear/radio.tilemap.rle"
    return PhoneTilemapRLE();
}

void PhoneTilemapRLE(void){
// INCBIN "gfx/pokegear/phone.tilemap.rle"
    return ClockTilemapRLE();
}

void ClockTilemapRLE(void){
// INCBIN "gfx/pokegear/clock.tilemap.rle"

    return v_UpdateRadioStation();
}

void v_UpdateRadioStation(void){
    JR(mUpdateRadioStation);

//  called from engine/gfx/sprite_anims.asm

    return AnimateTuningKnob();
}

void AnimateTuningKnob(void){
    PUSH_BC;
    CALL(aAnimateTuningKnob_TuningKnob);
    POP_BC;
    LD_A_addr(wRadioTuningKnob);
    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;


TuningKnob:
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto down;
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto up;
    RET;


down:
    LD_HL(wRadioTuningKnob);
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    DEC_hl;
    goto update;


up:
    LD_HL(wRadioTuningKnob);
    LD_A_hl;
    CP_A(80);
    RET_NC ;
    INC_hl;
    INC_hl;

update:
    return UpdateRadioStation();
}

void UpdateRadioStation(void){
    LD_HL(wRadioTuningKnob);
    LD_D_hl;
    //REG_D = gb_read(wRadioTuningKnob);
    //REG_HL = mRadioChannels;
    LD_HL(mRadioChannels);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto nostation;
    CP_A_D;
    IF_Z goto foundstation;
    INC_HL;
    INC_HL;
    goto loop;


nostation:
    CALL(aNoRadioStation);
    RET;


foundstation:
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(mUpdateRadioStation_returnafterstation);
    PUSH_DE;
    JP_hl;


returnafterstation:
    LD_A_addr(wPokegearRadioChannelBank);
    AND_A_A;
    RET_Z ;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    hlcoord(2, 9, wTilemap);
    CALL(aPlaceString);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void LoadPokegearRadioChannelPointer(void){
//  //  unreferenced
    LD_addr_A(wPokegearRadioChannelBank);
    LD_A_hli;
    LD_addr_A(wPokegearRadioChannelAddr);
    LD_A_hli;
    LD_addr_A(wPokegearRadioChannelAddr + 1);
    RET;

}

void RadioChannels(void){
//  entries correspond to constants/radio_constants.asm
//  frequency value given here = 4 × ingame_frequency − 2
    //dbw ['16', '.PKMNTalkAndPokedexShow']  // 04.5
    //dbw ['28', '.PokemonMusic']  // 07.5
    //dbw ['32', '.LuckyChannel']  // 08.5
    //dbw ['40', '.BuenasPassword']  // 10.5
    //dbw ['52', '.RuinsOfAlphRadio']  // 13.5
    //dbw ['64', '.PlacesAndPeople']  // 16.5
    //dbw ['72', '.LetsAllSing']  // 18.5
    //dbw ['78', '.PokeFluteRadio']  // 20.0
    //dbw ['80', '.EvolutionRadio']  // 20.5
    //db ['-1'];


PKMNTalkAndPokedexShow:
//  Pokédex Show in the morning
//  Oak's Pokémon Talk in the afternoon and evening
    CALL(aRadioChannels_InJohto);
    IF_NC goto NoSignal;
    LD_A_addr(wTimeOfDay);
    AND_A_A;
    JP_Z (mLoadStation_PokedexShow);
    JP(mLoadStation_OaksPokemonTalk);


PokemonMusic:
    CALL(aRadioChannels_InJohto);
    IF_NC goto NoSignal;
    JP(mLoadStation_PokemonMusic);


LuckyChannel:
    CALL(aRadioChannels_InJohto);
    IF_NC goto NoSignal;
    JP(mLoadStation_LuckyChannel);


BuenasPassword:
    CALL(aRadioChannels_InJohto);
    IF_NC goto NoSignal;
    JP(mLoadStation_BuenasPassword);


RuinsOfAlphRadio:
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CP_A(LANDMARK_RUINS_OF_ALPH);
    IF_NZ goto NoSignal;
    JP(mLoadStation_UnownRadio);


PlacesAndPeople:
    CALL(aRadioChannels_InJohto);
    IF_C goto NoSignal;
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_EXPN_CARD_F);
    IF_Z goto NoSignal;
    JP(mLoadStation_PlacesAndPeople);


LetsAllSing:
    CALL(aRadioChannels_InJohto);
    IF_C goto NoSignal;
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_EXPN_CARD_F);
    IF_Z goto NoSignal;
    JP(mLoadStation_LetsAllSing);


PokeFluteRadio:
    CALL(aRadioChannels_InJohto);
    IF_C goto NoSignal;
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_EXPN_CARD_F);
    IF_Z goto NoSignal;
    JP(mLoadStation_PokeFluteRadio);


EvolutionRadio:
//  This station airs in the Lake of Rage area when Team Rocket is still in Mahogany.
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_ROCKET_SIGNAL_F);
    IF_Z goto NoSignal;
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CP_A(LANDMARK_MAHOGANY_TOWN);
    IF_Z goto ok;
    CP_A(LANDMARK_ROUTE_43);
    IF_Z goto ok;
    CP_A(LANDMARK_LAKE_OF_RAGE);
    IF_NZ goto NoSignal;

ok:
    JP(mLoadStation_EvolutionRadio);


NoSignal:
    CALL(aNoRadioStation);
    RET;


InJohto:
//  if in Johto or on the S.S. Aqua, set carry
//  otherwise clear carry
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto johto;
    CP_A(KANTO_LANDMARK);
    IF_C goto johto;
//  kanto
    AND_A_A;
    RET;


johto:
    SCF;
    RET;

}

void LoadStation_OaksPokemonTalk(void){
    XOR_A_A;  // OAKS_POKEMON_TALK
    LD_addr_A(wCurRadioLine);
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mOaksPKMNTalkName);
    RET;

}

void LoadStation_PokedexShow(void){
    LD_A(POKEDEX_SHOW);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mPokedexShowName);
    RET;

}

void LoadStation_PokemonMusic(void){
    LD_A(POKEMON_MUSIC);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mPokemonMusicName);
    RET;

}

void LoadStation_LuckyChannel(void){
    LD_A(LUCKY_CHANNEL);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mLuckyChannelName);
    RET;

}

void LoadStation_BuenasPassword(void){
    LD_A(BUENAS_PASSWORD);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mNotBuenasPasswordName);
    LD_A_addr(wStatusFlags2);
    BIT_A(STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F);
    RET_Z ;
    LD_DE(mBuenasPasswordName);
    RET;

}

void BuenasPasswordName(void){
//   db "BUENA'S PASSWORD@"
    return NotBuenasPasswordName();
}

void NotBuenasPasswordName(void){
//db "@"

    return LoadStation_UnownRadio();
}

void LoadStation_UnownRadio(void){
    LD_A(UNOWN_RADIO);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mUnownStationName);
    RET;

}

void LoadStation_PlacesAndPeople(void){
    LD_A(PLACES_AND_PEOPLE);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mPlacesAndPeopleName);
    RET;

}

void LoadStation_LetsAllSing(void){
    LD_A(LETS_ALL_SING);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mLetsAllSingName);
    RET;

}

void LoadStation_RocketRadio(void){
    LD_A(ROCKET_RADIO);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mLetsAllSingName);
    RET;

}

void LoadStation_PokeFluteRadio(void){
    LD_A(POKE_FLUTE_RADIO);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mPokeFluteStationName);
    RET;

}

void LoadStation_EvolutionRadio(void){
    LD_A(EVOLUTION_RADIO);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(BANK(aPlayRadioShow));
    LD_HL(mPlayRadioShow);
    CALL(aRadio_BackUpFarCallParams);
    LD_DE(mUnownStationName);
    RET;

}

void DummyLoadStation(void){
//  //  unreferenced
    RET;

}

void RadioMusicRestartDE(void){
    PUSH_DE;
    LD_A_E;
    LD_addr_A(wPokegearRadioMusicPlaying);
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    POP_DE;
    LD_A_E;
    LD_addr_A(wMapMusic);
    CALL(aPlayMusic);
    RET;

}

void RadioMusicRestartDE_Conv(uint16_t de){
    uint16_t temp = de;
    gb_write(wPokegearRadioMusicPlaying, (uint8_t)(de & 0xFF));
    v_PlayMusic(MUSIC_NONE);
    de = temp;
    gb_write(wMapMusic, (uint8_t)(de & 0xFF));
    v_PlayMusic(de);
}

void RadioMusicRestartPokemonChannel(void){
    PUSH_DE;
    LD_A(RESTART_MAP_MUSIC);
    LD_addr_A(wPokegearRadioMusicPlaying);
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    POP_DE;
    LD_DE(MUSIC_POKEMON_CHANNEL);
    CALL(aPlayMusic);
    RET;

}

void RadioMusicRestartPokemonChannel_Conv(void){
    gb_write(wPokegearRadioMusicPlaying, RESTART_MAP_MUSIC);
    v_PlayMusic(MUSIC_NONE);
    v_PlayMusic(MUSIC_POKEMON_CHANNEL);
}

void Radio_BackUpFarCallParams(void){
    LD_addr_A(wPokegearRadioChannelBank);
    LD_A_L;
    LD_addr_A(wPokegearRadioChannelAddr);
    LD_A_H;
    LD_addr_A(wPokegearRadioChannelAddr + 1);
    RET;

}

void NoRadioStation(void){
    CALL(aNoRadioMusic);
    CALL(aNoRadioName);
//  no radio channel
    XOR_A_A;
    LD_addr_A(wPokegearRadioChannelBank);
    LD_addr_A(wPokegearRadioChannelAddr);
    LD_addr_A(wPokegearRadioChannelAddr + 1);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void NoRadioStation_Conv(void){
    NoRadioMusic_Conv();
    NoRadioName_Conv();
//  no radio channel
    gb_write(wPokegearRadioChannelBank, 0);
    gb_write16(wPokegearRadioChannelAddr, 0);
    gb_write(hBGMapMode, 0x1);
}

void NoRadioMusic(void){
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    LD_A(ENTER_MAP_MUSIC);
    LD_addr_A(wPokegearRadioMusicPlaying);
    RET;

}

void NoRadioMusic_Conv(void){
    v_PlayMusic(MUSIC_NONE);
    gb_write(wPokegearRadioMusicPlaying, ENTER_MAP_MUSIC);
}

void NoRadioName(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    hlcoord(1, 8, wTilemap);
    LD_BC((3 << 8) | 18);
    CALL(aClearBox);
    hlcoord(0, 12, wTilemap);
    LD_BC((4 << 8) | 18);
    CALL(aTextbox);
    RET;

}

void NoRadioName_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    gb_write(hBGMapMode, 0);

    // hlcoord(1, 8, wTilemap);
    // LD_BC((3 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv(coord(1, 8, wTilemap), (3 << 8) | 18);

    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox_Conv(coord(0, 12, wTilemap), 4, 18);
    // RET;
}

void OaksPKMNTalkName(void){
//    db "OAK's <PK><MN> Talk@"
    return PokedexShowName();
}

void PokedexShowName(void){
//     db "#DEX Show@"
    return PokemonMusicName();
}

void PokemonMusicName(void){
//    db "#MON Music@"
    return LuckyChannelName();
}

void LuckyChannelName(void){
//    db "Lucky Channel@"
    return UnownStationName();
}

void UnownStationName(void){
//    db "?????@"

    return PlacesAndPeopleName();
}

void PlacesAndPeopleName(void){
// db "Places & People@"
    return LetsAllSingName();
}

void LetsAllSingName(void){
//     db "Let's All Sing!@"
    return PokeFluteStationName();
}

void PokeFluteStationName(void){
//db "# FLUTE@"

    return v_TownMap();
}

void v_TownMap(void){
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);

    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);

    LD_A_addr(wVramState);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wVramState);

    CALL(aClearBGPalettes);
    CALL(aClearTilemap);
    CALL(aClearSprites);
    CALL(aDisableLCD);
    CALL(aPokegear_LoadGFX);
    FARCALL(aClearSpriteAnims);
    LD_A(8);
    CALL(aSkipMusic);
    LD_A(LCDC_DEFAULT);
    LDH_addr_A(rLCDC);
    CALL(aTownMap_GetCurrentLandmark);
    LD_addr_A(wTownMapPlayerIconLandmark);
    LD_addr_A(wTownMapCursorLandmark);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(av_TownMap_InitTilemap);
    CALL(aWaitBGMap2);
    LD_A_addr(wTownMapPlayerIconLandmark);
    CALL(aPokegearMap_InitPlayerIcon);
    LD_A_addr(wTownMapCursorLandmark);
    CALL(aPokegearMap_InitCursor);
    LD_A_C;
    LD_addr_A(wTownMapCursorObjectPointer);
    LD_A_B;
    LD_addr_A(wTownMapCursorObjectPointer + 1);
    LD_B(SCGB_POKEGEAR_PALS);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto dmg;
    LD_A(0b11100100);
    CALL(aDmgToCgbObjPal0);
    CALL(aDelayFrame);


dmg:
    LD_A_addr(wTownMapPlayerIconLandmark);
    CP_A(KANTO_LANDMARK);
    IF_NC goto kanto;
    LD_D(KANTO_LANDMARK - 1);
    LD_E(1);
    CALL(av_TownMap_loop);
    goto resume;


kanto:
    CALL(aTownMap_GetKantoLandmarkLimits);
    CALL(av_TownMap_loop);


resume:
    POP_AF;
    LD_addr_A(wVramState);
    POP_AF;
    LDH_addr_A(hInMenu);
    POP_AF;
    LD_addr_A(wOptions);
    CALL(aClearBGPalettes);
    RET;


loop:
    CALL(aJoyTextDelay);
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    RET_NZ ;

    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto pressed_up;

    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto pressed_down;

loop2:
    PUSH_DE;
    FARCALL(aPlaySpriteAnimations);
    POP_DE;
    CALL(aDelayFrame);
    goto loop;


pressed_up:
    LD_HL(wTownMapCursorLandmark);
    LD_A_hl;
    CP_A_D;
    IF_C goto okay;
    LD_A_E;
    DEC_A;
    LD_hl_A;


okay:
    INC_hl;
    goto next;


pressed_down:
    LD_HL(wTownMapCursorLandmark);
    LD_A_hl;
    CP_A_E;
    IF_NZ goto okay2;
    LD_A_D;
    INC_A;
    LD_hl_A;


okay2:
    DEC_hl;


next:
    PUSH_DE;
    LD_A_addr(wTownMapCursorLandmark);
    CALL(aPokegearMap_UpdateLandmarkName);
    LD_A_addr(wTownMapCursorObjectPointer);
    LD_C_A;
    LD_A_addr(wTownMapCursorObjectPointer + 1);
    LD_B_A;
    LD_A_addr(wTownMapCursorLandmark);
    CALL(aPokegearMap_UpdateCursorPosition);
    POP_DE;
    goto loop2;


InitTilemap:
    LD_A_addr(wTownMapPlayerIconLandmark);
    CP_A(KANTO_LANDMARK);
    IF_NC goto kanto2;
    LD_E(JOHTO_REGION);
    goto okay_tilemap;


kanto2:
    LD_E(KANTO_REGION);

okay_tilemap:
    FARCALL(aPokegearMap);
    LD_A(0x07);
    LD_BC(6);
    hlcoord(1, 0, wTilemap);
    CALL(aByteFill);
    hlcoord(0, 0, wTilemap);
    LD_hl(0x06);
    hlcoord(7, 0, wTilemap);
    LD_hl(0x17);
    hlcoord(7, 1, wTilemap);
    LD_hl(0x16);
    hlcoord(7, 2, wTilemap);
    LD_hl(0x26);
    LD_A(0x07);
    LD_BC(NAME_LENGTH);
    hlcoord(8, 2, wTilemap);
    CALL(aByteFill);
    hlcoord(19, 2, wTilemap);
    LD_hl(0x17);
    LD_A_addr(wTownMapCursorLandmark);
    CALL(aPokegearMap_UpdateLandmarkName);
    FARCALL(aTownMapPals);
    RET;

}

void PlayRadio(void){
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    CALL(aPlayRadio_PlayStation);
    LD_C(100);
    CALL(aDelayFrames);

loop:
    CALL(aJoyTextDelay);
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON | B_BUTTON);
    IF_NZ goto stop;
    LD_A_addr(wPokegearRadioChannelAddr);
    LD_L_A;
    LD_A_addr(wPokegearRadioChannelAddr + 1);
    LD_H_A;
    LD_A_addr(wPokegearRadioChannelBank);
    AND_A_A;
    IF_Z goto zero;
    RST(aFarCall);

zero:
    CALL(aDelayFrame);
    goto loop;


stop:
    POP_AF;
    LD_addr_A(wOptions);
    CALL(aExitPokegearRadio_HandleMusic);
    RET;


PlayStation:
    LD_A(ENTER_MAP_MUSIC);
    LD_addr_A(wPokegearRadioMusicPlaying);
    LD_HL(mPlayRadioStationPointers);
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(mPlayRadio_jump_return);
    PUSH_DE;
    JP_hl;


jump_return:
    PUSH_DE;
    hlcoord(0, 12, wTilemap);
    LD_BC((4 << 8) | 18);
    CALL(aTextbox);
    hlcoord(1, 14, wTilemap);
    LD_hl(0x72);
    POP_DE;
    hlcoord(2, 14, wTilemap);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_hl(0x73);
    CALL(aWaitBGMap);
    RET;

}

void PlayRadioStationPointers(void){
//  entries correspond to MAPRADIO_* constants
    //table_width ['2', 'PlayRadioStationPointers']
    //dw ['LoadStation_PokemonChannel'];
    //dw ['LoadStation_OaksPokemonTalk'];
    //dw ['LoadStation_PokedexShow'];
    //dw ['LoadStation_PokemonMusic'];
    //dw ['LoadStation_LuckyChannel'];
    //dw ['LoadStation_UnownRadio'];
    //dw ['LoadStation_PlacesAndPeople'];
    //dw ['LoadStation_LetsAllSing'];
    //dw ['LoadStation_RocketRadio'];
    //assert_table_length ['NUM_MAP_RADIO_STATIONS']

    return LoadStation_PokemonChannel();
}

void LoadStation_PokemonChannel(void){
    CALL(aIsInJohto);
    AND_A_A;
    IF_NZ goto kanto;
    CALL(aUpdateTime);
    LD_A_addr(wTimeOfDay);
    AND_A_A;
    JP_Z (mLoadStation_PokedexShow);
    JP(mLoadStation_OaksPokemonTalk);


kanto:
    JP(mLoadStation_PlacesAndPeople);

}

void PokegearMap(void){
    LD_A_E;
    AND_A_A;
    IF_NZ goto kanto;
    CALL(aLoadTownMapGFX);
    CALL(aFillJohtoMap);
    RET;


kanto:
    CALL(aLoadTownMapGFX);
    CALL(aFillKantoMap);
    RET;

}

void v_FlyMap(void){
    CALL(aClearBGPalettes);
    CALL(aClearTilemap);
    CALL(aClearSprites);
    LD_HL(hInMenu);
    LD_A_hl;
    PUSH_AF;
    LD_hl(0x1);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    FARCALL(aClearSpriteAnims);
    CALL(aLoadTownMapGFX);
    LD_DE(mFlyMapLabelBorderGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x30);
    LD_BC((BANK(aFlyMapLabelBorderGFX) << 8) | 6);
    CALL(aRequest1bpp);
    CALL(aFlyMap);
    CALL(aPokegear_DummyFunction);
    LD_B(SCGB_POKEGEAR_PALS);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);

loop:
    CALL(aJoyTextDelay);
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto pressedB;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto pressedA;
    CALL(av_FlyMap_HandleDPad);
    CALL(aGetMapCursorCoordinates);
    FARCALL(aPlaySpriteAnimations);
    CALL(aDelayFrame);
    goto loop;


pressedB:
    LD_A(-1);
    goto exit;


pressedA:
    LD_A_addr(wTownMapPlayerIconLandmark);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    LD_DE(mFlypoints + 1);
    ADD_HL_DE;
    LD_A_hl;

exit:
    LD_addr_A(wTownMapPlayerIconLandmark);
    POP_AF;
    LDH_addr_A(hInMenu);
    CALL(aClearBGPalettes);
    LD_A(SCREEN_HEIGHT_PX);
    LDH_addr_A(hWY);
    XOR_A_A;  // LOW(vBGMap0)
    LDH_addr_A(hBGMapAddress);
    LD_A(HIGH(vBGMap0));
    LDH_addr_A(hBGMapAddress + 1);
    LD_A_addr(wTownMapPlayerIconLandmark);
    LD_E_A;
    RET;


HandleDPad:
    LD_A_addr(wStartFlypoint);
    LD_E_A;
    LD_A_addr(wEndFlypoint);
    LD_D_A;
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto ScrollNext;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto ScrollPrev;
    RET;


ScrollNext:
    LD_HL(wTownMapPlayerIconLandmark);
    LD_A_hl;
    CP_A_D;
    IF_NZ goto NotAtEndYet;
    LD_A_E;
    DEC_A;
    LD_hl_A;

NotAtEndYet:
    INC_hl;
    CALL(aCheckIfVisitedFlypoint);
    IF_Z goto ScrollNext;
    goto Finally;


ScrollPrev:
    LD_HL(wTownMapPlayerIconLandmark);
    LD_A_hl;
    CP_A_E;
    IF_NZ goto NotAtStartYet;
    LD_A_D;
    INC_A;
    LD_hl_A;

NotAtStartYet:
    DEC_hl;
    CALL(aCheckIfVisitedFlypoint);
    IF_Z goto ScrollPrev;

Finally:
    CALL(aTownMapBubble);
    CALL(aWaitBGMap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    RET;

}

void TownMapBubble(void){
//  Draw the bubble containing the location text in the town map HUD

//  Top-left corner
    hlcoord(1, 0, wTilemap);
    LD_A(0x30);
    LD_hli_A;
//  Top row
    LD_BC(16);
    LD_A(0x7f);
    CALL(aByteFill);
//  Top-right corner
    LD_A(0x31);
    LD_hl_A;
    hlcoord(1, 1, wTilemap);

//  Middle row
    LD_BC(SCREEN_WIDTH - 2);
    LD_A(0x7f);
    CALL(aByteFill);

//  Bottom-left corner
    hlcoord(1, 2, wTilemap);
    LD_A(0x32);
    LD_hli_A;
//  Bottom row
    LD_BC(16);
    LD_A(0x7f);
    CALL(aByteFill);
//  Bottom-right corner
    LD_A(0x33);
    LD_hl_A;

//  Print "Where?"
    hlcoord(2, 0, wTilemap);
    LD_DE(mTownMapBubble_Where);
    CALL(aPlaceString);
//  Print the name of the default flypoint
    CALL(aTownMapBubble_Name);
//  Up/down arrows
    hlcoord(18, 1, wTilemap);
    LD_hl(0x34);
    RET;


Where:
    //db ['"Where?@"'];


Name:
//  We need the map location of the default flypoint
    LD_A_addr(wTownMapPlayerIconLandmark);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;  // two bytes per flypoint
    LD_DE(mFlypoints);
    ADD_HL_DE;
    LD_E_hl;
    FARCALL(aGetLandmarkName);
    hlcoord(2, 1, wTilemap);
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    RET;

}

void GetMapCursorCoordinates(void){
    LD_A_addr(wTownMapPlayerIconLandmark);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    LD_DE(mFlypoints);
    ADD_HL_DE;
    LD_E_hl;
    FARCALL(aGetLandmarkCoords);
    LD_A_addr(wTownMapCursorCoordinates);
    LD_C_A;
    LD_A_addr(wTownMapCursorCoordinates + 1);
    LD_B_A;
    LD_HL(4);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(5);
    ADD_HL_BC;
    LD_hl_D;
    RET;

}

void CheckIfVisitedFlypoint(void){
//  Check if the flypoint loaded in [hl] has been visited yet.
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_L_hl;
    LD_H(0);
    ADD_HL_HL;
    LD_DE(mFlypoints + 1);
    ADD_HL_DE;
    LD_C_hl;
    CALL(aHasVisitedSpawn);
    POP_HL;
    POP_DE;
    POP_BC;
    AND_A_A;
    RET;

}

void HasVisitedSpawn(void){
//  Check if spawn point c has been visited.
    LD_HL(wVisitedSpawns);
    LD_B(CHECK_FLAG);
    LD_D(0);
    PREDEF(pSmallFarFlagAction);
    LD_A_C;
    RET;

// INCLUDE "data/maps/flypoints.asm"

    return Pokegear_DummyFunction();
}

void Pokegear_DummyFunction(void){
    RET;

}

void FlyMap(void){
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);
//  If we're not in a valid location, i.e. Pokecenter floor 2F,
//  the backup map information is used.
    CP_A(LANDMARK_SPECIAL);
    IF_NZ goto CheckRegion;
    LD_A_addr(wBackupMapGroup);
    LD_B_A;
    LD_A_addr(wBackupMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);

CheckRegion:
//  The first 46 locations are part of Johto. The rest are in Kanto.
    CP_A(KANTO_LANDMARK);
    IF_NC goto KantoFlyMap;
//  Johto fly map
//  Note that .NoKanto should be modified in tandem with this branch
    PUSH_AF;
    LD_A(JOHTO_FLYPOINT);  // first Johto flypoint
    LD_addr_A(wTownMapPlayerIconLandmark);  // first one is default (New Bark Town)
    LD_addr_A(wStartFlypoint);
    LD_A(KANTO_FLYPOINT - 1);  // last Johto flypoint
    LD_addr_A(wEndFlypoint);
//  Fill out the map
    CALL(aFillJohtoMap);
    CALL(aFlyMap_MapHud);
    POP_AF;
    CALL(aTownMapPlayerIcon);
    RET;


KantoFlyMap:
//  The event that there are no flypoints enabled in a map is not
//  accounted for. As a result, if you attempt to select a flypoint
//  when there are none enabled, the game will crash. Additionally,
//  the flypoint selection has a default starting point that
//  can be flown to even if none are enabled.
//  To prevent both of these things from happening when the player
//  enters Kanto, fly access is restricted until Indigo Plateau is
//  visited and its flypoint enabled.
    PUSH_AF;
    LD_C(SPAWN_INDIGO);
    CALL(aHasVisitedSpawn);
    AND_A_A;
    IF_Z goto NoKanto;
//  Kanto's map is only loaded if we've visited Indigo Plateau
    LD_A(KANTO_FLYPOINT);  // first Kanto flypoint
    LD_addr_A(wStartFlypoint);
    LD_A(NUM_FLYPOINTS - 1);  // last Kanto flypoint
    LD_addr_A(wEndFlypoint);
    LD_addr_A(wTownMapPlayerIconLandmark);  // last one is default (Indigo Plateau)
//  Fill out the map
    CALL(aFillKantoMap);
    CALL(aFlyMap_MapHud);
    POP_AF;
    CALL(aTownMapPlayerIcon);
    RET;


NoKanto:
//  If Indigo Plateau hasn't been visited, we use Johto's map instead
    LD_A(JOHTO_FLYPOINT);  // first Johto flypoint
    LD_addr_A(wTownMapPlayerIconLandmark);  // first one is default (New Bark Town)
    LD_addr_A(wStartFlypoint);
    LD_A(KANTO_FLYPOINT - 1);  // last Johto flypoint
    LD_addr_A(wEndFlypoint);
    CALL(aFillJohtoMap);
    POP_AF;

MapHud:
    CALL(aTownMapBubble);
    CALL(aTownMapPals);
    hlbgcoord(0, 0, vBGMap0);  // BG Map 0
    CALL(aTownMapBGUpdate);
    CALL(aTownMapMon);
    LD_A_C;
    LD_addr_A(wTownMapCursorCoordinates);
    LD_A_B;
    LD_addr_A(wTownMapCursorCoordinates + 1);
    RET;

}

void Pokedex_GetArea(void){
//  e: Current landmark
    LD_A_addr(wTownMapPlayerIconLandmark);
    PUSH_AF;
    LD_A_addr(wTownMapCursorLandmark);
    PUSH_AF;
    LD_A_E;
    LD_addr_A(wTownMapPlayerIconLandmark);
    CALL(aClearSprites);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    LD_DE(mPokedexNestIconGFX);
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x7f);
    LD_BC((BANK(aPokedexNestIconGFX) << 8) | 1);
    CALL(aRequest2bpp);
    CALL(aPokedex_GetArea_GetPlayerOrFastShipIcon);
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x78);
    LD_C(4);
    CALL(aRequest2bpp);
    CALL(aLoadTownMapGFX);
    CALL(aFillKantoMap);
    CALL(aPokedex_GetArea_PlaceString_MonsNest);
    CALL(aTownMapPals);
    hlbgcoord(0, 0, vBGMap1);
    CALL(aTownMapBGUpdate);
    CALL(aFillJohtoMap);
    CALL(aPokedex_GetArea_PlaceString_MonsNest);
    CALL(aTownMapPals);
    hlbgcoord(0, 0, vBGMap0);
    CALL(aTownMapBGUpdate);
    LD_B(SCGB_POKEGEAR_PALS);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    XOR_A_A;  // JOHTO_REGION
    CALL(aPokedex_GetArea_GetAndPlaceNest);

loop:
    CALL(aJoyTextDelay);
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(A_BUTTON | B_BUTTON);
    IF_NZ goto a_b;
    LDH_A_addr(hJoypadDown);
    AND_A(SELECT);
    IF_NZ goto select;
    CALL(aPokedex_GetArea_LeftRightInput);
    CALL(aPokedex_GetArea_BlinkNestIcons);
    goto next;


select:
    CALL(aPokedex_GetArea_HideNestsShowPlayer);

next:
    CALL(aDelayFrame);
    goto loop;


a_b:
    CALL(aClearSprites);
    POP_AF;
    LD_addr_A(wTownMapCursorLandmark);
    POP_AF;
    LD_addr_A(wTownMapPlayerIconLandmark);
    RET;


LeftRightInput:
    LD_A_hl;
    AND_A(D_LEFT);
    IF_NZ goto left;
    LD_A_hl;
    AND_A(D_RIGHT);
    IF_NZ goto right;
    RET;


left:
    LDH_A_addr(hWY);
    CP_A(SCREEN_HEIGHT_PX);
    RET_Z ;
    CALL(aClearSprites);
    LD_A(SCREEN_HEIGHT_PX);
    LDH_addr_A(hWY);
    XOR_A_A;  // JOHTO_REGION
    CALL(aPokedex_GetArea_GetAndPlaceNest);
    RET;


right:
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
    RET_Z ;
    LDH_A_addr(hWY);
    AND_A_A;
    RET_Z ;
    CALL(aClearSprites);
    XOR_A_A;
    LDH_addr_A(hWY);
    LD_A(KANTO_REGION);
    CALL(aPokedex_GetArea_GetAndPlaceNest);
    RET;


BlinkNestIcons:
    LDH_A_addr(hVBlankCounter);
    LD_E_A;
    AND_A(0xf);
    RET_NZ ;
    LD_A_E;
    AND_A(0x10);
    IF_NZ goto copy_sprites;
    CALL(aClearSprites);
    RET;


copy_sprites:
    hlcoord(0, 0, wTilemap);
    LD_DE(wVirtualOAM);
    LD_BC(wVirtualOAMEnd - wVirtualOAM);
    CALL(aCopyBytes);
    RET;


PlaceString_MonsNest:
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH);
    LD_A(0x7f);
    CALL(aByteFill);
    hlcoord(0, 1, wTilemap);
    LD_A(0x06);
    LD_hli_A;
    LD_BC(SCREEN_WIDTH - 2);
    LD_A(0x07);
    CALL(aByteFill);
    LD_hl(0x17);
    CALL(aGetPokemonName);
    hlcoord(2, 0, wTilemap);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mPokedex_GetArea_String_SNest);
    CALL(aPlaceString);
    RET;


String_SNest:
    //db ['"\'S NEST@"'];


GetAndPlaceNest:
    LD_addr_A(wTownMapCursorLandmark);
    LD_E_A;
    FARCALL(aFindNest);  // load nest landmarks into wTilemap[0,0]
    decoord(0, 0, wTilemap);
    LD_HL(wVirtualOAMSprite00);

nestloop:
    LD_A_de;
    AND_A_A;
    IF_Z goto done_nest;
    PUSH_DE;
    LD_E_A;
    PUSH_HL;
    FARCALL(aGetLandmarkCoords);
    POP_HL;
// load into OAM
    LD_A_D;
    SUB_A(4);
    LD_hli_A;  // y
    LD_A_E;
    SUB_A(4);
    LD_hli_A;  // x
    LD_A(0x7f);  // nest icon
    LD_hli_A;  // tile id
    XOR_A_A;
    LD_hli_A;  // attributes
// next
    POP_DE;
    INC_DE;
    goto nestloop;


done_nest:
    LD_HL(wVirtualOAM);
    decoord(0, 0, wTilemap);
    LD_BC(wVirtualOAMEnd - wVirtualOAM);
    CALL(aCopyBytes);
    RET;


HideNestsShowPlayer:
    CALL(aPokedex_GetArea_CheckPlayerLocation);
    RET_C ;
    LD_A_addr(wTownMapPlayerIconLandmark);
    LD_E_A;
    FARCALL(aGetLandmarkCoords);
    LD_C_E;
    LD_B_D;
    LD_DE(mPokedex_GetArea_PlayerOAM);
    LD_HL(wVirtualOAMSprite00);

ShowPlayerLoop:
    LD_A_de;
    CP_A(0x80);
    IF_Z goto clear_oam;
    ADD_A_B;
    LD_hli_A;  // y
    INC_DE;
    LD_A_de;
    ADD_A_C;
    LD_hli_A;  // x
    INC_DE;
    LD_A_de;
    ADD_A(0x78);  // where the player's sprite is loaded
    LD_hli_A;  // tile id
    INC_DE;
    PUSH_BC;
    LD_C(PAL_OW_RED);
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto male;
    INC_C;  // PAL_OW_BLUE

male:
    LD_A_C;
    LD_hli_A;  // attributes
    POP_BC;
    goto ShowPlayerLoop;


clear_oam:
    LD_HL(wVirtualOAMSprite04);
    LD_BC(wVirtualOAMEnd - wVirtualOAMSprite04);
    XOR_A_A;
    CALL(aByteFill);
    RET;


PlayerOAM:
// y pxl, x pxl, tile offset
    //db ['-1 * 8', '-1 * 8', '0'];  // top left
    //db ['-1 * 8', '0 * 8', '1'];  // top right
    //db ['0 * 8', '-1 * 8', '2'];  // bottom left
    //db ['0 * 8', '0 * 8', '3'];  // bottom right
    //db ['0x80'];  // terminator


CheckPlayerLocation:
//  Don't show the player's sprite if you're
//  not in the same region as what's currently
//  on the screen.
    LD_A_addr(wTownMapPlayerIconLandmark);
    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto johto;
    CP_A(KANTO_LANDMARK);
    IF_C goto johto;
//  kanto
    LD_A_addr(wTownMapCursorLandmark);
    AND_A_A;
    IF_Z goto clear;
    goto ok;


johto:
    LD_A_addr(wTownMapCursorLandmark);
    AND_A_A;
    IF_NZ goto clear;

ok:
    AND_A_A;
    RET;


clear:
    LD_HL(wVirtualOAM);
    LD_BC(wVirtualOAMEnd - wVirtualOAM);
    XOR_A_A;
    CALL(aByteFill);
    SCF;
    RET;


GetPlayerOrFastShipIcon:
    LD_A_addr(wTownMapPlayerIconLandmark);
    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto FastShip;
    FARCALL(aGetPlayerIcon);
    RET;


FastShip:
    LD_DE(mFastShipGFX);
    LD_B(BANK(aFastShipGFX));
    RET;

}

void TownMapBGUpdate(void){
//  Update BG Map tiles and attributes

//  BG Map address
    LD_A_L;
    LDH_addr_A(hBGMapAddress);
    LD_A_H;
    LDH_addr_A(hBGMapAddress + 1);
//  Only update palettes on CGB
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto tiles;
//  BG Map mode 2 (palettes)
    LD_A(2);
    LDH_addr_A(hBGMapMode);
//  The BG Map is updated in thirds, so we wait

//  3 frames to update the whole screen's palettes.
    LD_C(3);
    CALL(aDelayFrames);

tiles:
//  Update BG Map tiles
    CALL(aWaitBGMap);
//  Turn off BG Map update
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    RET;

}

void FillJohtoMap(void){
    LD_DE(mJohtoMap);
    JR(mFillTownMap);

}

void FillKantoMap(void){
    LD_DE(mKantoMap);
    return FillTownMap();
}

void FillJohtoMap_Conv(void){
    return FillTownMap_Conv(mJohtoMap);
}

void FillKantoMap_Conv(void){
    return FillTownMap_Conv(mKantoMap);
}

void FillTownMap_Conv(const uint16_t map){
    // hlcoord(0, 0, wTilemap);
    uint16_t hl = coord(0, 0, wTilemap);
    uint16_t de = map;
    uint8_t a;

    while(1)
    {
        // LD_A_de;
        a = gb_read(de);

        // CP_A(-1);
        // RET_Z ;
        if(a == 0xFF)
            return;

        // LD_A_de;
        // LD_hli_A;
        // INC_DE;
        gb_write(hl++, gb_read(de++));
    }
}

void FillTownMap(void){
    hlcoord(0, 0, wTilemap);

loop:
    LD_A_de;
    CP_A(-1);
    RET_Z ;
    LD_A_de;
    LD_hli_A;
    INC_DE;
    goto loop;

    return TownMapPals();
}

void TownMapPals(void){
//  Assign palettes based on tile ids
    hlcoord(0, 0, wTilemap);
    decoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);

loop:
//  Current tile
    LD_A_hli;
    PUSH_HL;
//  The palette map covers tiles $00 to $5f
    CP_A(0x60);
    IF_NC goto pal0;

//  The palette data is condensed to nybbles, least-significant first.
    LD_HL(mTownMapPals_PalMap);
    SRL_A;
    IF_C goto odd;
//  Even-numbered tile ids take the bottom nybble...
    ADD_A_L;
    LD_L_A;
    LD_A_H;
    ADC_A(0);
    LD_H_A;
    LD_A_hl;
    AND_A(PALETTE_MASK);
    goto update;


odd:
//  ...and odd ids take the top.
    ADD_A_L;
    LD_L_A;
    LD_A_H;
    ADC_A(0);
    LD_H_A;
    LD_A_hl;
    SWAP_A;
    AND_A(PALETTE_MASK);
    goto update;


pal0:
    XOR_A_A;

update:
    POP_HL;
    LD_de_A;
    INC_DE;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;


PalMap:
// INCLUDE "gfx/pokegear/town_map_palette_map.asm"

    return TownMapMon();
}

void TownMapMon(void){
//  Draw the FlyMon icon at town map location

//  Get FlyMon species
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartySpecies);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wTempIconSpecies);
//  Get FlyMon icon
    LD_E(0x08);  // starting tile in VRAM
    FARCALL(aGetSpeciesIcon);
//  Animation/palette
    //depixel ['0', '0']
    depixel2(0, 0);
    LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl(0x08);
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_hl(SPRITE_ANIM_SEQ_NULL);
    RET;

}

void TownMapPlayerIcon(void){
//  Draw the player icon at town map location in a
    PUSH_AF;
    FARCALL(aGetPlayerIcon);
//  Standing icon
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x10);
    LD_C(4);  // # tiles
    CALL(aRequest2bpp);
//  Walking icon
    LD_HL(12 * LEN_2BPP_TILE);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x14);
    LD_C(4);  // # tiles
    LD_A(BANK(aChrisSpriteGFX));  // does nothing
    CALL(aRequest2bpp);
//  Animation/palette
    //depixel ['0', '0']
    depixel2(0, 0);
    LD_B(SPRITE_ANIM_INDEX_RED_WALK);  // Male
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto got_gender;
    LD_B(SPRITE_ANIM_INDEX_BLUE_WALK);  // Female

got_gender:
    LD_A_B;
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl(0x10);
    POP_AF;
    LD_E_A;
    PUSH_BC;
    FARCALL(aGetLandmarkCoords);
    POP_BC;
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hl_D;
    RET;

}

void LoadTownMapGFX(void){
    LD_HL(mTownMapGFX);
    LD_DE(vTiles2);
    LD_BC((BANK(aTownMapGFX) << 8) | 48);
    CALL(aDecompressRequest2bpp);
    RET;

}

void JohtoMap(void){
// INCBIN "gfx/pokegear/johto.bin"

    return KantoMap();
}

void KantoMap(void){
// INCBIN "gfx/pokegear/kanto.bin"

    return PokedexNestIconGFX();
}

void PokedexNestIconGFX(void){
// INCBIN "gfx/pokegear/dexmap_nest_icon.2bpp"
    return FlyMapLabelBorderGFX();
}

void FlyMapLabelBorderGFX(void){
// INCBIN "gfx/pokegear/flymap_label_border.1bpp"

    return EntireFlyMap();
}

void EntireFlyMap(void){
//  //  unreferenced
//  Similar to _FlyMap, but scrolls through the entire
//  Flypoints data of both regions. A debug function?
    XOR_A_A;
    LD_addr_A(wTownMapPlayerIconLandmark);
    CALL(aClearBGPalettes);
    CALL(aClearTilemap);
    CALL(aClearSprites);
    LD_HL(hInMenu);
    LD_A_hl;
    PUSH_AF;
    LD_hl(0x1);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    FARCALL(aClearSpriteAnims);
    CALL(aLoadTownMapGFX);
    LD_DE(mFlyMapLabelBorderGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x30);
    LD_BC((BANK(aFlyMapLabelBorderGFX) << 8) | 6);
    CALL(aRequest1bpp);
    CALL(aFillKantoMap);
    CALL(aTownMapBubble);
    CALL(aTownMapPals);
    hlbgcoord(0, 0, vBGMap1);
    CALL(aTownMapBGUpdate);
    CALL(aFillJohtoMap);
    CALL(aTownMapBubble);
    CALL(aTownMapPals);
    hlbgcoord(0, 0, vBGMap0);
    CALL(aTownMapBGUpdate);
    CALL(aTownMapMon);
    LD_A_C;
    LD_addr_A(wTownMapCursorCoordinates);
    LD_A_B;
    LD_addr_A(wTownMapCursorCoordinates + 1);
    LD_B(SCGB_POKEGEAR_PALS);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);

loop:
    CALL(aJoyTextDelay);
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto pressedB;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto pressedA;
    CALL(aEntireFlyMap_HandleDPad);
    CALL(aGetMapCursorCoordinates);
    FARCALL(aPlaySpriteAnimations);
    CALL(aDelayFrame);
    goto loop;


pressedB:
    LD_A(-1);
    goto exit;


pressedA:
    LD_A_addr(wTownMapPlayerIconLandmark);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    LD_DE(mFlypoints + 1);
    ADD_HL_DE;
    LD_A_hl;

exit:
    LD_addr_A(wTownMapPlayerIconLandmark);
    POP_AF;
    LDH_addr_A(hInMenu);
    CALL(aClearBGPalettes);
    LD_A(SCREEN_HEIGHT_PX);
    LDH_addr_A(hWY);
    XOR_A_A;  // LOW(vBGMap0)
    LDH_addr_A(hBGMapAddress);
    LD_A(HIGH(vBGMap0));
    LDH_addr_A(hBGMapAddress + 1);
    LD_A_addr(wTownMapPlayerIconLandmark);
    LD_E_A;
    RET;


HandleDPad:
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_DOWN | D_RIGHT);
    IF_NZ goto ScrollNext;
    LD_A_hl;
    AND_A(D_UP | D_LEFT);
    IF_NZ goto ScrollPrev;
    RET;


ScrollNext:
    LD_HL(wTownMapPlayerIconLandmark);
    LD_A_hl;
    CP_A(NUM_FLYPOINTS - 1);
    IF_C goto NotAtEndYet;
    LD_hl(-1);

NotAtEndYet:
    INC_hl;
    goto FillMap;


ScrollPrev:
    LD_HL(wTownMapPlayerIconLandmark);
    LD_A_hl;
    AND_A_A;
    IF_NZ goto NotAtStartYet;
    LD_hl(NUM_FLYPOINTS);

NotAtStartYet:
    DEC_hl;

FillMap:
    LD_A_addr(wTownMapPlayerIconLandmark);
    CP_A(KANTO_FLYPOINT);
    IF_C goto InJohto;
    CALL(aFillKantoMap);
    XOR_A_A;
    LD_B(HIGH(vBGMap1));
    goto Finally;


InJohto:
    CALL(aFillJohtoMap);
    LD_A(SCREEN_HEIGHT_PX);
    LD_B(HIGH(vBGMap0));

Finally:
    LDH_addr_A(hWY);
    LD_A_B;
    LDH_addr_A(hBGMapAddress + 1);
    CALL(aTownMapBubble);
    CALL(aWaitBGMap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    RET;

}
