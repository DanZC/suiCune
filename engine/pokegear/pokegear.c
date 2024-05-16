#include "../../constants.h"
#include "pokegear.h"
#include "radio.h"
#include "townmap_convertlinebreakcharacters.h"
#include "../../home/audio.h"
#include "../../home/gfx.h"
#include "../../home/map.h"
#include "../../home/delay.h"
#include "../../home/decompress.h"
#include "../../home/copy.h"
#include "../../home/palettes.h"
#include "../../home/text.h"
#include "../../home/time.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/joypad.h"
#include "../../home/region.h"
#include "../../home/lcd.h"
#include "../../home/sprite_anims.h"
#include "../../home/menu.h"
#include "../overworld/landmarks.h"
#include "../gfx/player_gfx.h"
#include "../gfx/sprites.h"
#include "../gfx/mon_icons.h"
#include "../../data/maps/flypoints.h"
#include "../../audio/engine.h"
#include "../rtc/print_hours_mins.h"
#include "../../gfx/font.h"
#include "../../data/text/common.h"
#include "../../gfx/misc.h"
#include "../phone/phone.h"
#include "../../charmap.h"

void (*gPokegearRadioChannelAddr)(void);
struct SpriteAnim* gPokegearMapCursorObjectPointer = NULL;
struct SpriteAnim* gTownMapCursorObjectPointer = NULL;
struct SpriteAnim* gTownMapCursorCoordinates = NULL;

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

static const char PokegearSpritesGFX[] = "gfx/pokegear/pokegear_sprites.png";
static const char FastShipGFX[] = "gfx/pokegear/fast_ship.png";

static const char RadioTilemapRLE[] = "gfx/pokegear/radio.tilemap.rle";
static const char PhoneTilemapRLE[] = "gfx/pokegear/phone.tilemap.rle";
static const char ClockTilemapRLE[] = "gfx/pokegear/clock.tilemap.rle";

void PokeGear(void){
    PEEK("");
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    bit_set(wram->wPokegearFlags, POKEGEAR_RADIO_CARD_F);
    bit_set(wram->wPokegearFlags, POKEGEAR_MAP_CARD_F);
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;
    // CALL(aPokeGear_InitTilemap);
    PokeGear_InitTilemap_Conv();
    // CALL(aDelayFrame);
    DelayFrame();

    while(1) {
    // loop:
        // SET_PC(aPokeGear_loop);
        // CALL(aUpdateTime);
        UpdateTime_Conv();
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aPokegearJumptable);
        PokegearJumptable();

        // SAVE_REGS;
        {
            bank_push(BANK(aPlaySpriteAnimations));
            // FARCALL(aPlaySpriteAnimations);
            PlaySpriteAnimations_Conv();
            bank_pop;
        }
        // RESTORE_REGS;
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }


// done:
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_READ_TEXT_2);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // XOR_A_A;  // LOW(vBGMap0)
    // LDH_addr_A(hBGMapAddress);
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap0;
    // LD_A(SCREEN_HEIGHT_PX);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // RET;


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
    ClearTilemap_Conv2();

    // CALL(aClearSprites);
    ClearSprites_Conv();

    // CALL(aDisableLCD);
    DisableLCD_Conv();

    //XOR_A_A;
    //LDH_addr_A(hSCY);
    //LDH_addr_A(hSCX);
    hram->hSCY = 0;
    hram->hSCX = 0;

    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;

    Pokegear_LoadGFX_Conv();
    // CALL(aPokegear_LoadGFX);
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aInitPokegearModeIndicatorArrow);
    InitPokegearModeIndicatorArrow_Conv();
    // LD_A(8);
    // CALL(aSkipMusic);
    SkipMusic_Conv(4);

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

    wram->wJumptableIndex = POKEGEARSTATE_CLOCKINIT;  // POKEGEARSTATE_CLOCKINIT
    wram->wPokegearCard = POKEGEARCARD_CLOCK;  // POKEGEARCARD_CLOCK
    wram->wPokegearMapRegion = JOHTO_REGION;  // JOHTO_REGION
    wram->wUnusedPokegearByte = 0;
    wram->wPokegearPhoneScrollPosition = 0;
    wram->wPokegearPhoneCursorPosition = 0;
    wram->wPokegearPhoneSelectedPerson = 0;
    gb_write(wPokegearRadioChannelBank, 0);
    gb_write(wPokegearRadioChannelAddr, 0);
    gb_write(wPokegearRadioChannelAddr + 1, 0);

    //CALL(aPokegear_InitJumptableIndices);
    Pokegear_InitJumptableIndices_Conv();

    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap_Conv();

    // LD_B(SCGB_POKEGEAR_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_POKEGEAR_PALS);

    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z return;
    if(hram->hCGB == 0)
        return;
    // LD_A(0b11100100);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0_Conv(0b11100100);
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
    // FarDecompress_Conv(BANK(aTownMapGFX), mTownMapGFX, vTiles2);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, TownMapGFX);
    // FarDecompress_Conv(BANK(aPokegearGFX), mPokegearGFX, (vTiles2 + LEN_2BPP_TILE * 0x30));
    LoadPNG2bppAssetToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x30, PokegearGFX);
    // LD_HL(mPokegearSpritesGFX);
    // LD_DE(vTiles0);
    // LD_A(BANK(aPokegearSpritesGFX));
    // CALL(aDecompress);
    // FarDecompress_Conv(BANK(aPokegearSpritesGFX), mPokegearSpritesGFX, vTiles0);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, PokegearSpritesGFX);

    uint8_t landmark = GetWorldMapLocation_Conv2(wram->wMapGroup, wram->wMapNumber);
    if(landmark == LANDMARK_FAST_SHIP) {
        LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x10, FastShipGFX, 0, 8);
        return;
    }

    // uint16_t iconptr;
    // uint8_t iconbank;
    // GetPlayerIcon_Conv(&iconptr, &iconbank);
    const char* iconpath = GetPlayerIcon_Conv2();
// standing sprite
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x10, iconpath, 0, 4);
// walking sprite
    // iconptr += (12 * LEN_2BPP_TILE);
    // FarCopyBytes_Conv(vTiles0 + LEN_2BPP_TILE * 0x14, iconbank, iconptr, 4 * LEN_2BPP_TILE);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x14, iconpath, 12, 4);
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
    // depixel4(4, 2, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_POKEGEAR_ARROW);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_POKEGEAR_ARROW, pixel4(4, 2, 4, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x0);
    // RET;
    bc->tileID = 0x0;
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

void AnimatePokegearModeIndicatorArrow_Conv(struct SpriteAnim* bc){
    static const uint8_t XCoords[] = {
        [POKEGEARCARD_CLOCK]    = 0x00,  // POKEGEARCARD_CLOCK
        [POKEGEARCARD_MAP]      = 0x10,  // POKEGEARCARD_MAP
        [POKEGEARCARD_PHONE]    = 0x20,  // POKEGEARCARD_PHONE
        [POKEGEARCARD_RADIO]    = 0x30,  // POKEGEARCARD_RADIO
    };
    bc->xOffset = XCoords[wram->wPokegearCard];
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
    uint8_t landmark = GetWorldMapLocation_Conv2(wram->wMapGroup, wram->wMapNumber);
    if(landmark == LANDMARK_SPECIAL)
    {
        landmark = GetWorldMapLocation_Conv2(wram->wBackupMapGroup, wram->wBackupMapNumber);
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
        wram->wPokegearMapPlayerIconLandmark = landmark;
        //LD_A(LANDMARK_NEW_BARK_TOWN);
        //LD_addr_A(wPokegearMapCursorLandmark);
        wram->wPokegearMapCursorLandmark = LANDMARK_NEW_BARK_TOWN;
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
    wram->wJumptableIndex = POKEGEARSTATE_CLOCKINIT;
    wram->wPokegearCard = POKEGEARCARD_CLOCK;  // POKEGEARCARD_CLOCK
}

void InitPokegearTilemap(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x4f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x4f);
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
    hram->hBGMapMode = 0;
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x4F);
    uint8_t card = wram->wPokegearCard & (NUM_POKEGEAR_CARDS - 1);
    switch(card)
    {
        case POKEGEARCARD_CLOCK:
        {
            Pokegear_LoadTilemapRLE_Conv2(ClockTilemapRLE);
            // hlcoord(12, 1, wTilemap);
            // LD_DE(mInitPokegearTilemap_switch);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(" SWITCH▶@"), coord(12, 1, wram->wTilemap));
            Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
            Pokegear_UpdateClock_Conv();
        }
        break;
        case POKEGEARCARD_MAP:
        {
            uint8_t landmark = wram->wPokegearMapPlayerIconLandmark;
            if(landmark != LANDMARK_FAST_SHIP && landmark >= KANTO_LANDMARK) {
                PokegearMap_Conv(1);
            }
            else {
                PokegearMap_Conv(0);
            }
            // FARCALL(aPokegearMap);
            ByteFill_Conv2(coord(1, 2, wram->wTilemap), (SCREEN_WIDTH - 2), 0x07);
            *coord(0, 2, wram->wTilemap) = 0x06;
            *coord(19, 2, wram->wTilemap) = 0x17;
            // REG_A = gb_read(wPokegearMapCursorLandmark);
            // CALL(aPokegearMap_UpdateLandmarkName);
            PokegearMap_UpdateLandmarkName_Conv(wram->wPokegearMapCursorLandmark);
        }
        break;
        case POKEGEARCARD_PHONE:
        {
            Pokegear_LoadTilemapRLE_Conv2(PhoneTilemapRLE);
            Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
            InitPokegearTilemap_PlacePhoneBars_Conv();
            // CALL(aPokegearPhone_UpdateDisplayList);
            PokegearPhone_UpdateDisplayList();
            //RET;
        }
        break;
        case POKEGEARCARD_RADIO:
        {
            Pokegear_LoadTilemapRLE_Conv2(RadioTilemapRLE);
            Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
        }
        break;
    }

    // CALL(aPokegear_FinishTilemap);
    Pokegear_FinishTilemap_Conv();

    // FARCALL(aTownMapPals);
    TownMapPals_Conv();
    if(wram->wPokegearMapRegion == KANTO_REGION)
    {
        hram->hBGMapAddress = vBGMap1;
        InitPokegearTilemap_UpdateBGMap_Conv();
        hram->hWY = 0;
    }
    else 
    {
        hram->hBGMapAddress = vBGMap0;
        InitPokegearTilemap_UpdateBGMap_Conv();
        hram->hWY = SCREEN_HEIGHT_PX;
    }
// swap region maps
    wram->wPokegearMapRegion = (wram->wPokegearMapRegion & (NUM_REGIONS - 1)) ^ 1;
}

void InitPokegearTilemap_UpdateBGMap_Conv(void) {
    if(hram->hCGB == 0)
    {
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        return;
    }

    hram->hBGMapMode = 0x2;
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    hram->hBGMapMode = 0x1;
}

void InitPokegearTilemap_PlacePhoneBars_Conv() {
    tile_t* hl = coord(17, 1, wram->wTilemap);
    uint8_t tile = 0x3C;
    *(hl++) = tile++;
    *hl = tile++;
    hl = coord(17, 2, wram->wTilemap);
    *(hl++) = tile;

    // CALL(aGetMapPhoneService);
    uint8_t srv = GetMapPhoneService_Conv();
    if(srv != 0)
    {
        return;
    }
    *coord(18, 2, wram->wTilemap) = 0x3F;
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
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), 0x8, 0x4f);

    // hlcoord(0, 1, wTilemap);
    // LD_BC(0x8);
    // LD_A(0x4f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 1, wram->wTilemap), 0x8, 0x4f);

    // LD_DE(wPokegearFlags);
    // LD_A_de;
    uint8_t flags = wram->wPokegearFlags;

    // BIT_A(POKEGEAR_MAP_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlaceMapIcon);
    if(flags & (1 << POKEGEAR_MAP_CARD_F))
    {
        // hlcoord(2, 0, wTilemap);
        uint8_t* hl = coord(2, 0, wram->wTilemap);

        // LD_A(0x40);
        // LD_hli_A;
        hl[0] = 0x40;

        // INC_A;
        // LD_hld_A;
        hl[1] = 0x41;

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        hl[0] = 0x50;

        // INC_A;
        // LD_hld_A;
        hl[1] = 0x51;
    }

    // LD_A_de;
    // BIT_A(POKEGEAR_PHONE_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlacePhoneIcon);
    if(flags & (1 << POKEGEAR_PHONE_CARD_F))
    {
        // hlcoord(4, 0, wTilemap);
        uint8_t* hl = coord(4, 0, wram->wTilemap);

        // LD_A(0x44);
        // LD_hli_A;
        hl[0] = 0x44;

        // INC_A;
        // LD_hld_A;
        hl[1] = 0x45;

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        hl[0] = 0x54;

        // INC_A;
        // LD_hld_A;
        hl[1] = 0x55;
    }

    // LD_A_de;
    // BIT_A(POKEGEAR_RADIO_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlaceRadioIcon);
    if(flags & (1 << POKEGEAR_RADIO_CARD_F))
    {
        // hlcoord(6, 0, wTilemap);
        tile_t* hl = coord(6, 0, wram->wTilemap);

        // LD_A(0x42);
        // LD_hli_A;
        *(hl++) = 0x42;

        // INC_A;
        // LD_hld_A;
        *(hl--) = 0x43;

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        *(hl++) = 0x52;

        // INC_A;
        // LD_hld_A;
        *(hl--) = 0x53;
    }

    // hlcoord(0, 0, wTilemap);
    uint8_t* hl = coord(0, 0, wram->wTilemap);

    // LD_A(0x46);
    // LD_hli_A;
    hl[0] = 0x46;

    // INC_A;
    // LD_hld_A;
    hl[1] = 0x47;

    // LD_BC(0x14);
    // ADD_HL_BC;
    hl += 0x14;

    // ADD_A(0xf);
    // LD_hli_A;
    hl[0] = 0x56;

    // INC_A;
    // LD_hld_A;
    hl[1] = 0x57;
}

void PokegearJumptable(void) {
    //jumptable ['.Jumptable', 'wJumptableIndex']
    // jumptable(mPokegearJumptable_Jumptable, wJumptableIndex);
    // return;


// Jumptable:
//  entries correspond to POKEGEARSTATE_* constants
    switch(wram->wJumptableIndex)
    {
        case POKEGEARSTATE_CLOCKINIT:       return PokegearClock_Init_Conv();
        case POKEGEARSTATE_CLOCKJOYPAD:     return PokegearClock_Joypad();
        case POKEGEARSTATE_MAPCHECKREGION:  return PokegearMap_CheckRegion();
        case POKEGEARSTATE_JOHTOMAPINIT:    return PokegearMap_Init();
        case POKEGEARSTATE_JOHTOMAPJOYPAD:  return PokegearMap_JohtoMap();
        case POKEGEARSTATE_KANTOMAPINIT:    return PokegearMap_Init();
        case POKEGEARSTATE_KANTOMAPJOYPAD:  return PokegearMap_KantoMap();
        case POKEGEARSTATE_PHONEINIT:       return PokegearPhone_Init_Conv();
        case POKEGEARSTATE_PHONEJOYPAD:     return PokegearPhone_Joypad();
        case POKEGEARSTATE_MAKEPHONECALL:   return PokegearPhone_MakePhoneCall();
        case POKEGEARSTATE_FINISHPHONECALL: return PokegearPhone_FinishPhoneCall();
        case POKEGEARSTATE_RADIOINIT:       return PokegearRadio_Init();
        case POKEGEARSTATE_RADIOJOYPAD:     return PokegearRadio_Joypad();
        default: return;
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

    // REG_HL = mPokegearPressButtonText;
    // CALL(aPrintText);
    PrintText_Conv2(PokegearPressButtonText);

    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;

    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // RET;

}

static void PokegearClock_Joypad_UpdateClock(void) {
    // SET_PC(aPokegearClock_Joypad_UpdateClock);
    // PEEK("UpdateClock");
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aPokegear_UpdateClock);
    // Pokegear_UpdateClock();
    Pokegear_UpdateClock_Conv();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 1;
    // RET;
}

void PokegearClock_Joypad(void) {
    // SET_PC(aPokegearClock_Joypad);
    // CALL(aPokegearClock_Joypad_UpdateClock);
    PokegearClock_Joypad_UpdateClock();
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(A_BUTTON | B_BUTTON | START | SELECT);
    // IF_NZ goto quit;
    if(hram->hJoyLast & (A_BUTTON | B_BUTTON | START | SELECT)) {
    // quit:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // RET_Z ;
    if(!(hram->hJoyLast & D_RIGHT))
        return;
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_MAP_CARD_F);
    // IF_Z goto no_map_card;
    if(bit_test(wram->wPokegearFlags, POKEGEAR_MAP_CARD_F)) {
        // LD_C(POKEGEARSTATE_MAPCHECKREGION);
        // LD_B(POKEGEARCARD_MAP);
        // goto done;
        Pokegear_SwitchPage_Conv(POKEGEARSTATE_MAPCHECKREGION, POKEGEARCARD_MAP);
        return;
    }


// no_map_card:
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_PHONE_CARD_F);
    // IF_Z goto no_phone_card;
    else if(bit_test(wram->wPokegearFlags, POKEGEAR_PHONE_CARD_F)) {
        // LD_C(POKEGEARSTATE_PHONEINIT);
        // LD_B(POKEGEARCARD_PHONE);
        // goto done;
        Pokegear_SwitchPage_Conv(POKEGEARSTATE_PHONEINIT, POKEGEARCARD_PHONE);
        return;
    }


// no_phone_card:
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_RADIO_CARD_F);
    // RET_Z ;
    else if(bit_test(wram->wPokegearFlags, POKEGEAR_RADIO_CARD_F)) {
        // LD_C(POKEGEARSTATE_RADIOINIT);
        // LD_B(POKEGEARCARD_RADIO);
    // done:
        // CALL(aPokegear_SwitchPage);
        // return;
        // RET;
        Pokegear_SwitchPage_Conv(POKEGEARSTATE_RADIOINIT, POKEGEARCARD_RADIO);
        return;
    }

    else {
        return;
    }


// quit:
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    // return;
    // RET;


// UpdateClock:
    // // PEEK("UpdateClock");
    // SET_PC(aPokegearClock_Joypad_UpdateClock);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    // // CALL(aPokegear_UpdateClock);
    // Pokegear_UpdateClock_Conv();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    // RET;

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
    // PEEK("UpdateClock");
    static const txt_cmd_s GearTodayText[] = {
        text_far(v_GearTodayText)
        text_end
    };
    // PEEK("UpdateClock");
    UpdateTime_Conv();
    // hlcoord(3, 5, wTilemap);
    // LD_BC((5 << 8) | 14);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(3, 5, wram->wTilemap), 14, 5);
    // LDH_A_addr(hHours);
    // LD_B_A;
    // LDH_A_addr(hMinutes);
    // LD_C_A;
    // REG_B = gb_read(hHours);
    // REG_C = gb_read(hMinutes);
    // REG_DE = coord(6, 8, wTilemap);
    // decoord(6, 8, wTilemap);
    // FARCALL(aPrintHoursMins);
    PrintHoursMins_Conv(wram->wTilemap + coordidx(6, 8), hram->hHours, hram->hMinutes);
    // bank_push(aPrintHoursMins);
    // bank_pop;
    // LD_HL(mPokegear_UpdateClock_GearTodayText);
    // bccoord(6, 6, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(6, 6, wram->wTilemap), GearTodayText);
}

void PokegearMap_CheckRegion(void){
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CP_A(LANDMARK_FAST_SHIP);
    // IF_Z goto johto;
    // CP_A(KANTO_LANDMARK);
    // IF_NC goto kanto;
    if(wram->wPokegearMapPlayerIconLandmark != LANDMARK_FAST_SHIP
    && wram->wPokegearMapPlayerIconLandmark >= KANTO_LANDMARK) {
    // kanto:
        // LD_A(POKEGEARSTATE_KANTOMAPINIT);
        wram->wJumptableIndex = POKEGEARSTATE_KANTOMAPINIT;
    }
    else {
    // johto:
        // LD_A(POKEGEARSTATE_JOHTOMAPINIT);
        wram->wJumptableIndex = POKEGEARSTATE_JOHTOMAPINIT;
        // goto done;
        // return;
        // RET;
    }

// done:
    // LD_addr_A(wJumptableIndex);
    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // return;
    // RET;
}

void PokegearMap_Init(void){
    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap_Conv();
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CALL(aPokegearMap_InitPlayerIcon);
    PokegearMap_InitPlayerIcon_Conv(wram->wPokegearMapPlayerIconLandmark);
    // LD_A_addr(wPokegearMapCursorLandmark);
    // CALL(aPokegearMap_InitCursor);
    // LD_A_C;
    // LD_addr_A(wPokegearMapCursorObjectPointer);
    // LD_A_B;
    // LD_addr_A(wPokegearMapCursorObjectPointer + 1);
    gPokegearMapCursorObjectPointer = PokegearMap_InitCursor_Conv(wram->wPokegearMapPlayerIconLandmark);
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // return;
    // RET;
}

void PokegearMap_KantoMap(void){
    // CALL(aTownMap_GetKantoLandmarkLimits);
    // JR(mPokegearMap_ContinueMap);
    return PokegearMap_ContinueMap_Conv(TownMap_GetKantoLandmarkLimits_Conv());
}

void PokegearMap_JohtoMap(void){
    // LD_D(LANDMARK_SILVER_CAVE);
    // LD_E(LANDMARK_NEW_BARK_TOWN);
    return PokegearMap_ContinueMap_Conv(u8_pair(LANDMARK_SILVER_CAVE, LANDMARK_NEW_BARK_TOWN));
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

static void PokegearMap_ContinueMap_DPad(u8_pair_s de) {
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(hram->hJoyLast & D_UP) {
    // up:
        // LD_HL(wPokegearMapCursorLandmark);
        // LD_A_hl;
        // CP_A_D;
        // IF_C goto wrap_around_up;
        if(wram->wPokegearMapCursorLandmark >= de.a) {
            // LD_A_E;
            // DEC_A;
            // LD_hl_A;
            wram->wPokegearMapCursorLandmark = de.b - 1;
        }

    // wrap_around_up:
        // INC_hl;
        wram->wPokegearMapCursorLandmark++;
        // goto done_dpad;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_HL(wPokegearMapCursorLandmark);
        // LD_A_hl;
        // CP_A_E;
        // IF_NZ goto wrap_around_down;
        if(wram->wPokegearMapCursorLandmark == de.b) {
            // LD_A_D;
            // INC_A;
            // LD_hl_A;
            wram->wPokegearMapCursorLandmark = de.a + 1;
        }

    // wrap_around_down:
        // DEC_hl;
        wram->wPokegearMapCursorLandmark--;
    }
    else {
        return;
        // RET;
    }

// done_dpad:
    // LD_A_addr(wPokegearMapCursorLandmark);
    // CALL(aPokegearMap_UpdateLandmarkName);
    PokegearMap_UpdateLandmarkName_Conv(wram->wPokegearMapCursorLandmark);
    // LD_A_addr(wPokegearMapCursorObjectPointer);
    // LD_C_A;
    // LD_A_addr(wPokegearMapCursorObjectPointer + 1);
    // LD_B_A;
    // LD_A_addr(wPokegearMapCursorLandmark);
    // CALL(aPokegearMap_UpdateCursorPosition);
    PokegearMap_UpdateCursorPosition_Conv(gPokegearMapCursorObjectPointer, wram->wPokegearMapCursorLandmark);
    // RET;
    // return;
}

void PokegearMap_ContinueMap_Conv(u8_pair_s de){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto cancel;
    if(hram->hJoyLast & B_BUTTON) {
    // cancel:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        return;
        // RET;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    if(hram->hJoyLast & D_RIGHT) {
    // right:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_PHONE_CARD_F);
        // IF_Z goto no_phone;
        if(bit_test(wram->wPokegearFlags, POKEGEAR_PHONE_CARD_F)) {
            // LD_C(POKEGEARSTATE_PHONEINIT);
            // LD_B(POKEGEARCARD_PHONE);
            Pokegear_SwitchPage_Conv(POKEGEARSTATE_PHONEINIT, POKEGEARCARD_PHONE);
            // goto done;
        }
    // no_phone:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_RADIO_CARD_F);
        // RET_Z ;
        // LD_C(POKEGEARSTATE_RADIOINIT);
        // LD_B(POKEGEARCARD_RADIO);
        // goto done;
        else if(bit_test(wram->wPokegearFlags, POKEGEAR_RADIO_CARD_F)) {
            Pokegear_SwitchPage_Conv(POKEGEARSTATE_RADIOINIT, POKEGEARCARD_RADIO);
        }
        
        return;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(hram->hJoyLast & D_LEFT) {
    // left:
        // LD_C(POKEGEARSTATE_CLOCKINIT);
        // LD_B(POKEGEARCARD_CLOCK);

    // done:
        // CALL(aPokegear_SwitchPage);
        // RET;
        return Pokegear_SwitchPage_Conv(POKEGEARSTATE_CLOCKINIT, POKEGEARCARD_CLOCK);
    }
    // CALL(aPokegearMap_ContinueMap_DPad);
    PokegearMap_ContinueMap_DPad(de);
    //RET;
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

void PokegearMap_InitPlayerIcon_Conv(uint8_t landmark){
    // PUSH_AF;
    //depixel ['0', '0']
    // depixel2(0, 0);
    // LD_B(SPRITE_ANIM_INDEX_RED_WALK);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_gender;
    // LD_B(SPRITE_ANIM_INDEX_BLUE_WALK);
    uint8_t b = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? SPRITE_ANIM_INDEX_BLUE_WALK: SPRITE_ANIM_INDEX_RED_WALK;

// got_gender:
    // LD_A_B;
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(b, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x10);
    bc->tileID = 0x10;
    // POP_AF;
    // LD_E_A;
    // PUSH_BC;
    // FARCALL(aGetLandmarkCoords);
    struct Coords coord = GetLandmarkCoords_Conv(landmark);
    // POP_BC;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->xCoord = coord.x;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yCoord = coord.y;
    // RET;
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

struct SpriteAnim* PokegearMap_InitCursor_Conv(uint8_t landmark) {
    // PUSH_AF;
    // depixel2(0, 0);
    // LD_A(SPRITE_ANIM_INDEX_POKEGEAR_ARROW);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_POKEGEAR_ARROW, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x04);
    bc->tileID = 0x04;
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_NULL);
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
    // POP_AF;
    // PUSH_BC;
    // CALL(aPokegearMap_UpdateCursorPosition);
    PokegearMap_UpdateCursorPosition_Conv(bc, landmark);
    // POP_BC;
    // RET;
    return bc;
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
    ClearBox_Conv2(coord(8, 0, wram->wTilemap), 12, 2);

    // LD_E_A;
    // REG_DE = landmark;
    // PUSH_DE;
    // FARCALL(aGetLandmarkName);
    GetLandmarkName_Conv(landmark);
    // POP_DE;
    // FARCALL(aTownMap_ConvertLineBreakCharacters);
    TownMap_ConvertLineBreakCharacters();

    // hlcoord(8, 0, wTilemap);
    // LD_hl(0x34);
    *coord(8, 0, wram->wTilemap) = 0x34;
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

void PokegearMap_UpdateCursorPosition_Conv(struct SpriteAnim* bc, uint8_t landmark){
    // PUSH_BC;
    // LD_E_A;
    // FARCALL(aGetLandmarkCoords);
    struct Coords coord = GetLandmarkCoords_Conv(landmark);
    // POP_BC;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->xCoord = coord.x;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yCoord = coord.y;
    // RET;
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

u8_pair_s TownMap_GetKantoLandmarkLimits_Conv(void){
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
    // IF_Z goto not_hof;
    if(bit_test(wram->wStatusFlags, STATUSFLAGS_HALL_OF_FAME_F)) {
        // LD_D(LANDMARK_ROUTE_28);
        // LD_E(LANDMARK_PALLET_TOWN);
        return u8_pair(LANDMARK_ROUTE_28, LANDMARK_PALLET_TOWN);
    }
    else {
    // not_hof:
        // LD_D(LANDMARK_ROUTE_28);
        // LD_E(LANDMARK_VICTORY_ROAD);
        // RET;
        return u8_pair(LANDMARK_ROUTE_28, LANDMARK_VICTORY_ROAD);
    }
    // RET;
}

void PokegearRadio_Init(void){
    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap_Conv();
    //depixel ['4', '10', '4', '4']
    // depixel4(4, 10, 4, 4);
    // LD_A(SPRITE_ANIM_INDEX_RADIO_TUNING_KNOB);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_RADIO_TUNING_KNOB, pixel4(4, 10, 4, 4));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x08);
    bc->tileID = 0x08;
    // CALL(av_UpdateRadioStation);
    v_UpdateRadioStation_Conv();
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    //RET;

}

void PokegearRadio_Joypad(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto cancel;
    if(hram->hJoyLast & B_BUTTON) {
    // cancel:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        //RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(hram->hJoyLast & D_LEFT) {
    // left:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_PHONE_CARD_F);
        // IF_Z goto no_phone;
        if(bit_set(wram->wPokegearFlags, POKEGEAR_PHONE_CARD_F)) {
            // LD_C(POKEGEARSTATE_PHONEINIT);
            // LD_B(POKEGEARCARD_PHONE);
            // goto switch_page;
            Pokegear_SwitchPage_Conv(POKEGEARSTATE_PHONEINIT, POKEGEARCARD_PHONE);
        }

    // no_phone:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_MAP_CARD_F);
        // IF_Z goto no_map;
        else if(bit_set(wram->wPokegearFlags, POKEGEAR_MAP_CARD_F)) {
            // LD_C(POKEGEARSTATE_MAPCHECKREGION);
            // LD_B(POKEGEARCARD_MAP);
            // goto switch_page;
            Pokegear_SwitchPage_Conv(POKEGEARSTATE_MAPCHECKREGION, POKEGEARCARD_MAP);
        }

    // no_map:
        else {
            // LD_C(POKEGEARSTATE_CLOCKINIT);
            // LD_B(POKEGEARCARD_CLOCK);
            Pokegear_SwitchPage_Conv(POKEGEARSTATE_CLOCKINIT, POKEGEARCARD_CLOCK);
        }

    // switch_page:
        // CALL(aPokegear_SwitchPage);
        return;
        //RET;
    }
    // LD_A_addr(wPokegearRadioChannelAddr);
    // LD_L_A;
    // LD_A_addr(wPokegearRadioChannelAddr + 1);
    // LD_H_A;
    // LD_A_addr(wPokegearRadioChannelBank);
    // AND_A_A;
    // RET_Z ;
    if(gPokegearRadioChannelAddr == NULL)
        return;
    // RST(aFarCall);
    return gPokegearRadioChannelAddr();
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
    wram->wJumptableIndex++;
    // XOR_A_A;
    // LD_addr_A(wPokegearPhoneScrollPosition);
    // LD_addr_A(wPokegearPhoneCursorPosition);
    // LD_addr_A(wPokegearPhoneSelectedPerson);
    wram->wPokegearPhoneScrollPosition = 0;
    wram->wPokegearPhoneCursorPosition = 0;
    wram->wPokegearPhoneSelectedPerson = 0;
    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap_Conv();
    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // LD_HL(mPokegearAskWhoCallText);
    // CALL(aPrintText);
    PrintText_Conv2(PokegearAskWhoCallText);
    // RET;

}

void PokegearPhone_Joypad(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    uint8_t pressed = hram->hJoyPressed;
    // AND_A(B_BUTTON);
    // IF_NZ goto b;
    if(pressed & B_BUTTON) {
    // b:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto a;
    else if(pressed & A_BUTTON) {
    // a:
        // LD_HL(wPhoneList);
        // LD_A_addr(wPokegearPhoneScrollPosition);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // LD_A_addr(wPokegearPhoneCursorPosition);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // LD_A_hl;
        uint8_t contact = wram->wPhoneList[wram->wPokegearPhoneScrollPosition + wram->wPokegearPhoneCursorPosition];
        // AND_A_A;
        // RET_Z ;
        if(contact == 0)
            return;
        // LD_addr_A(wPokegearPhoneSelectedPerson);
        wram->wPokegearPhoneSelectedPerson = contact;
        // hlcoord(1, 4, wTilemap);
        // LD_A_addr(wPokegearPhoneCursorPosition);
        // LD_BC(SCREEN_WIDTH * 2);
        // CALL(aAddNTimes);
        // LD_hl(0xec);
        *coord(1, 4 + wram->wPokegearPhoneCursorPosition * 2, wram->wTilemap) = CHAR_RIGHT_CURSOR_SEL;
        // CALL(aPokegearPhoneContactSubmenu);
        // IF_C goto quit_submenu;
        if(PokegearPhoneContactSubmenu_Conv()) {
        // quit_submenu:
            // LD_A(POKEGEARSTATE_PHONEJOYPAD);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = POKEGEARSTATE_PHONEJOYPAD;
            // RET;
            return;
        }
        // LD_HL(wJumptableIndex);
        // INC_hl;
        wram->wJumptableIndex++;
        // RET;
        return;
    }
    // LD_HL(hJoyLast);
    // LD_A_hl;
    uint8_t last = hram->hJoyLast;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(last & D_LEFT) {
    // left:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_MAP_CARD_F);
        // IF_Z goto no_map;
        if(bit_test(wram->wPokegearFlags, POKEGEAR_MAP_CARD_F)) {
            // LD_C(POKEGEARSTATE_MAPCHECKREGION);
            // LD_B(POKEGEARCARD_MAP);
            // goto switch_page;
            Pokegear_SwitchPage_Conv(POKEGEARSTATE_MAPCHECKREGION, POKEGEARCARD_MAP);
            return;
        }
        else {
        // no_map:
            // LD_C(POKEGEARSTATE_CLOCKINIT);
            // LD_B(POKEGEARCARD_CLOCK);
            // goto switch_page;
            Pokegear_SwitchPage_Conv(POKEGEARSTATE_CLOCKINIT, POKEGEARCARD_CLOCK);
            return;
        }
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    else if(last & D_RIGHT) {
    // right:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_RADIO_CARD_F);
        // RET_Z ;
        if(!bit_test(wram->wPokegearFlags, POKEGEAR_RADIO_CARD_F))
            return;
        // LD_C(POKEGEARSTATE_RADIOINIT);
        // LD_B(POKEGEARCARD_RADIO);
        Pokegear_SwitchPage_Conv(POKEGEARSTATE_RADIOINIT, POKEGEARCARD_RADIO);
        return;
    }
    // CALL(aPokegearPhone_GetDPad);
    PokegearPhone_GetDPad();
    // RET;
    return;

// switch_page:
    // CALL(aPokegear_SwitchPage);
    // return;
    // RET;

}

void PokegearPhone_MakePhoneCall(void){
    static const txt_cmd_s GearEllipseText[] = {
        text_far(v_GearEllipseText)
        text_end
    };
    static const txt_cmd_s GearOutOfServiceText[] = {
        text_far(v_GearOutOfServiceText)
        text_end
    };
    // CALL(aGetMapPhoneService);
    // AND_A_A;
    // IF_NZ goto no_service;
    if(!GetMapPhoneService_Conv()) {
        // LD_HL(wOptions);
        // RES_hl(NO_TEXT_SCROLL);
        bit_reset(wram->wOptions, NO_TEXT_SCROLL);
        // XOR_A_A;
        // LDH_addr_A(hInMenu);
        hram->hInMenu = FALSE;
        // LD_DE(SFX_CALL);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_CALL);
        // LD_HL(mPokegearPhone_MakePhoneCall_GearEllipseText);
        // CALL(aPrintText);
        PrintText_Conv2(GearEllipseText);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // LD_DE(SFX_CALL);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_CALL);
        // LD_HL(mPokegearPhone_MakePhoneCall_GearEllipseText);
        // CALL(aPrintText);
        PrintText_Conv2(GearEllipseText);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // LD_A_addr(wPokegearPhoneSelectedPerson);
        // LD_B_A;
        // CALL(aMakePhoneCallFromPokegear);
        MakePhoneCallFromPokegear_Conv(wram->wPokegearPhoneSelectedPerson);
        // LD_C(10);
        // CALL(aDelayFrames);
        DelayFrames_Conv(10);
        // LD_HL(wOptions);
        // SET_hl(NO_TEXT_SCROLL);
        bit_set(wram->wOptions, NO_TEXT_SCROLL);
        // LD_A(0x1);
        // LDH_addr_A(hInMenu);
        hram->hInMenu = TRUE;
        // CALL(aPokegearPhone_UpdateCursor);
        PokegearPhone_UpdateCursor();
        // LD_HL(wJumptableIndex);
        // INC_hl;
        wram->wJumptableIndex++;
        //RET;
    }
    else {
    // no_service:
        // FARCALL(aPhone_NoSignal);
        Phone_NoSignal();
        // LD_HL(mPokegearPhone_MakePhoneCall_GearOutOfServiceText);
        // CALL(aPrintText);
        PrintText_Conv2(GearOutOfServiceText);
        // LD_A(POKEGEARSTATE_PHONEJOYPAD);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = POKEGEARSTATE_PHONEJOYPAD;
        // LD_HL(mPokegearAskWhoCallText);
        // CALL(aPrintText);
        PrintText_Conv2(PokegearAskWhoCallText);
        //RET;
    }
}

void PokegearPhone_FinishPhoneCall(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON | B_BUTTON);
    // RET_Z ;
    if((hram->hJoyPressed & (A_BUTTON | B_BUTTON)) == 0)
        return;
    // FARCALL(aHangUp);
    HangUp();
    // LD_A(POKEGEARSTATE_PHONEJOYPAD);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = POKEGEARSTATE_PHONEJOYPAD;
    // LD_HL(mPokegearAskWhoCallText);
    // CALL(aPrintText);
    PrintText_Conv2(PokegearAskWhoCallText);
    //RET;

}

void PokegearPhone_GetDPad(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(hram->hJoyLast & D_UP) {
    // up:
        // LD_HL(wPokegearPhoneCursorPosition);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto scroll_page_up;
        if(wram->wPokegearPhoneCursorPosition == 0) {
        // scroll_page_up:
            // LD_HL(wPokegearPhoneScrollPosition);
            // LD_A_hl;
            // AND_A_A;
            // RET_Z ;
            if(wram->wPokegearPhoneScrollPosition == 0)
                return;
            // DEC_hl;
            --wram->wPokegearPhoneScrollPosition;
            goto done_joypad_update_page;
        }
        // DEC_hl;
        --wram->wPokegearPhoneCursorPosition;
        goto done_joypad_same_page;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_HL(wPokegearPhoneCursorPosition);
        // LD_A_hl;
        // CP_A(PHONE_DISPLAY_HEIGHT - 1);
        // IF_NC goto scroll_page_down;
        if(wram->wPokegearPhoneCursorPosition >= PHONE_DISPLAY_HEIGHT - 1) {
        // scroll_page_down:
            // LD_HL(wPokegearPhoneScrollPosition);
            // LD_A_hl;
            // CP_A(CONTACT_LIST_SIZE - PHONE_DISPLAY_HEIGHT);
            // RET_NC ;
            if(wram->wPokegearPhoneScrollPosition >= CONTACT_LIST_SIZE - PHONE_DISPLAY_HEIGHT)
                return;
            // INC_hl;
            ++wram->wPokegearPhoneScrollPosition;
            goto done_joypad_update_page;
        }
        // INC_hl;
        ++wram->wPokegearPhoneCursorPosition;
        goto done_joypad_same_page;
    }
    // RET;
    return;


done_joypad_same_page:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aPokegearPhone_UpdateCursor);
    PokegearPhone_UpdateCursor();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // RET;
    return;


done_joypad_update_page:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aPokegearPhone_UpdateDisplayList);
    PokegearPhone_UpdateDisplayList();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // RET;
    return;

}

void PokegearPhone_UpdateCursor(void){
    // LD_A(0x7f);
    uint8_t a = CHAR_SPACE;
    for(int y = 0; y < PHONE_DISPLAY_HEIGHT; y++){
        // hlcoord(1, 4 + y * 2, wTilemap);
        // LD_hl_A;
        *coord(1, 4 + y * 2, wram->wTilemap) = a;
    }
    // hlcoord(1, 4, wTilemap);
    // LD_A_addr(wPokegearPhoneCursorPosition);
    // LD_BC(2 * SCREEN_WIDTH);
    // CALL(aAddNTimes);
    // LD_hl(0xed);
    *coord(1, 4 + wram->wPokegearPhoneCursorPosition * 2, wram->wTilemap) = CHAR_RIGHT_CURSOR;
    // RET;

}

void PokegearPhone_UpdateDisplayList(void){
    // hlcoord(1, 3, wTilemap);
    tile_t* hl = coord(1, 3, wram->wTilemap);
    // LD_B(PHONE_DISPLAY_HEIGHT * 2 + 1);
    // LD_A(0x7f);

    for(uint32_t b = 0; b < PHONE_DISPLAY_HEIGHT * 2 + 1; ++b) {
    // row:
        // LD_C(SCREEN_WIDTH - 2);
        for(uint32_t c = 0; c < SCREEN_WIDTH - 2; ++c) {
        // col:
            // LD_hli_A;
            // DEC_C;
            // IF_NZ goto col;
            hl[c + (SCREEN_WIDTH * b)] = CHAR_SPACE;
        }
        // INC_HL;
        // INC_HL;
        // DEC_B;
        // IF_NZ goto row;
    }
    // LD_A_addr(wPokegearPhoneScrollPosition);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPhoneList);
    // ADD_HL_DE;
    uint8_t* de = wram->wPhoneList + wram->wPokegearPhoneScrollPosition;
    // XOR_A_A;
    // LD_addr_A(wPokegearPhoneDisplayPosition);
    wram->wPokegearPhoneDisplayPosition = 0;

    do {
    // loop:
        // LD_A_hli;
        uint8_t contact = de[wram->wPokegearPhoneDisplayPosition];
        // PUSH_HL;
        // PUSH_AF;
        // hlcoord(2, 4, wTilemap);
        // LD_A_addr(wPokegearPhoneDisplayPosition);
        // LD_BC(2 * SCREEN_WIDTH);
        // CALL(aAddNTimes);
        // LD_D_H;
        // LD_E_L;
        // POP_AF;
        // LD_B_A;
        // CALL(aGetCallerClassAndName);
        GetCallerClassAndName_Conv(coord(2, 4 + (2 * wram->wPokegearPhoneDisplayPosition), wram->wTilemap), contact);
        // POP_HL;
        // LD_A_addr(wPokegearPhoneDisplayPosition);
        // INC_A;
        // LD_addr_A(wPokegearPhoneDisplayPosition);
        // CP_A(PHONE_DISPLAY_HEIGHT);
        // IF_C goto loop;
    } while(++wram->wPokegearPhoneDisplayPosition < PHONE_DISPLAY_HEIGHT);
    // CALL(aPokegearPhone_UpdateCursor);
    PokegearPhone_UpdateCursor();
    // RET;

}

void PokegearPhone_DeletePhoneNumber(void){
    // LD_HL(wPhoneList);
    // LD_A_addr(wPokegearPhoneScrollPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_addr(wPokegearPhoneCursorPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    uint8_t* hl = wram->wPhoneList + wram->wPokegearPhoneScrollPosition + wram->wPokegearPhoneCursorPosition;
    // LD_hl(0);
    *hl = 0;
    // LD_HL(wPhoneList);
    // LD_C(CONTACT_LIST_SIZE);

    for(uint32_t i = 0; i < CONTACT_LIST_SIZE; ++i) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_NZ goto skip;
        if(wram->wPhoneList[i] == 0) {
            // LD_A_hld;
            // LD_hli_A;
            // LD_hl(0);
            wram->wPhoneList[i] = wram->wPhoneList[i+1];
            wram->wPhoneList[i+1] = 0;
        }

    // skip:
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;

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

struct PokegearPhoneSubmenu {
    tile_t* coord;
    uint8_t count;
    const char* strings;
};

static void PokegearPhoneContactSubmenu_UpdateCursor(const struct PokegearPhoneSubmenu* de) {
    // PUSH_DE;
    // LD_A_de;
    // INC_DE;
    // LD_L_A;
    // LD_A_de;
    // INC_DE;
    // LD_H_A;
    tile_t* hl = de->coord;
    // LD_A_de;
    // LD_C_A;
    // PUSH_HL;
    // LD_A(0x7f);
    // LD_DE(SCREEN_WIDTH * 2);

    for(uint32_t i = 0; i < de->count; ++i) {
    // clear_column:
        // LD_hl_A;
        // ADD_HL_DE;
        hl[SCREEN_WIDTH * 2 * i] = CHAR_SPACE;
        // DEC_C;
        // IF_NZ goto clear_column;
    }
    // POP_HL;
    // LD_A_addr(wPokegearPhoneSubmenuCursor);
    // LD_BC(SCREEN_WIDTH * 2);
    // CALL(aAddNTimes);
    // LD_hl(0xed);
    hl[SCREEN_WIDTH * 2 * wram->wPokegearPhoneSubmenuCursor] = CHAR_RIGHT_CURSOR;
    // POP_DE;
    // RET;
}

bool PokegearPhoneContactSubmenu_Conv(void){
    static const struct PokegearPhoneSubmenu Submenus[] = {
        {
            //dwcoord ['10', '6'];
            .coord = coord(10, 6, wram_ptr(wTilemap)),
            //db ['2'];
            .count = 3,
            .strings =
                //db ['"CALL"'];
                "CALL" t_next
                //next ['"DELETE"']
                "DELETE" t_next
                //next ['"CANCEL"']
                "CANCEL@",
                //db ['"@"'];
        },
        {
            //dwcoord ['10', '8'];
            .coord = coord(10, 8, wram_ptr(wTilemap)),
            //db ['2'];
            .count = 2,
            .strings =
                //db ['"CALL"'];
                "CALL" t_next
                //next ['"CANCEL"']
                "CANCEL@",
                //db ['"@"'];
        }
    };
    // LD_HL(wPhoneList);
    // LD_A_addr(wPokegearPhoneScrollPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_addr(wPokegearPhoneCursorPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_C_hl;
    uint8_t contact = wram->wPhoneList[wram->wPokegearPhoneScrollPosition + wram->wPokegearPhoneCursorPosition];
    // FARCALL(aCheckCanDeletePhoneNumber);
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto cant_delete;
    uint8_t which;
    if(CheckCanDeletePhoneNumber_Conv(contact)) {
        // LD_HL(mPokegearPhoneContactSubmenu_CallDeleteCancelJumptable);
        // LD_DE(mPokegearPhoneContactSubmenu_CallDeleteCancelStrings);
        which = 0;
        // goto got_menu_data;
    }
    else {
    // cant_delete:
        // LD_HL(mPokegearPhoneContactSubmenu_CallCancelJumptable);
        // LD_DE(mPokegearPhoneContactSubmenu_CallCancelStrings);
        which = 1;
    }

// got_menu_data:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // PUSH_HL;
    // PUSH_DE;
    // LD_A_de;
    // LD_L_A;
    // INC_DE;
    // LD_A_de;
    // LD_H_A;
    // INC_DE;
    // PUSH_HL;
    tile_t* hl = Submenus[which].coord;
    // bccoord(-1, -2, 0);
    // ADD_HL_BC;
    // LD_A_de;
    // INC_DE;
    // SLA_A;
    // LD_B_A;
    // LD_C(8);
    // PUSH_DE;
    // CALL(aTextbox);
    Textbox_Conv2(hl + coord(-1, -2, 0), Submenus[which].count * 2, 8);
    // POP_DE;
    // POP_HL;
    // INC_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Submenus[which].strings), hl + 1);
    // POP_DE;
    // XOR_A_A;
    // LD_addr_A(wPokegearPhoneSubmenuCursor);
    wram->wPokegearPhoneSubmenuCursor = 0;
    // CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
    PokegearPhoneContactSubmenu_UpdateCursor(Submenus + which);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();

    while(1) {
    // loop:
        // PUSH_DE;
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // POP_DE;
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        uint8_t pressed = hram->hJoyPressed;
        // AND_A(D_UP);
        // IF_NZ goto d_up;
        if(pressed & D_UP) {
        // d_up:
            // LD_HL(wPokegearPhoneSubmenuCursor);
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto loop;
            if(wram->wPokegearPhoneSubmenuCursor == 0)
                continue;
            // DEC_hl;
            wram->wPokegearPhoneSubmenuCursor--;
            // CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
            PokegearPhoneContactSubmenu_UpdateCursor(Submenus + which);
            // goto loop;
            continue;
        }
        // LD_A_hl;
        // AND_A(D_DOWN);
        // IF_NZ goto d_down;
        else if(pressed & D_DOWN) {
        // d_down:
            // LD_HL(2);
            // ADD_HL_DE;
            uint8_t count = Submenus[which].count;
            // LD_A_addr(wPokegearPhoneSubmenuCursor);
            // INC_A;
            // CP_A_hl;
            // IF_NC goto loop;
            if(wram->wPokegearPhoneSubmenuCursor + 1 >= count)
                continue;
            // LD_addr_A(wPokegearPhoneSubmenuCursor);
            wram->wPokegearPhoneSubmenuCursor++;
            // CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
            PokegearPhoneContactSubmenu_UpdateCursor(Submenus + which);
            // goto loop;
            continue;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto a_b;
        else if(pressed & (A_BUTTON | B_BUTTON)) {
        // a_b:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0;
            // CALL(aPokegearPhone_UpdateDisplayList);
            PokegearPhone_UpdateDisplayList();
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0x1;
            // POP_HL;
            // LDH_A_addr(hJoyPressed);
            // AND_A(B_BUTTON);
            // IF_NZ goto Cancel;
            if(hram->hJoyPressed & B_BUTTON)
                goto Cancel;
            // LD_A_addr(wPokegearPhoneSubmenuCursor);
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // ADD_HL_DE;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // JP_hl;
            switch(wram->wPokegearPhoneSubmenuCursor) {
            case 0:
            // Call:
                // AND_A_A;
                // RET;
                return false;
            case 1:
                if(which == 0) {
                // Delete:
                    // LD_HL(mPokegearAskDeleteText);
                    // CALL(aMenuTextbox);
                    MenuTextbox_Conv(PokegearAskDeleteText);
                    // CALL(aYesNoBox);
                    bool cancel = !YesNoBox_Conv();
                    // CALL(aExitMenu);
                    ExitMenu_Conv2();
                    // IF_C goto CancelDelete;
                    if(!cancel) {
                        // CALL(aPokegearPhone_DeletePhoneNumber);
                        PokegearPhone_DeletePhoneNumber();
                        // XOR_A_A;
                        // LDH_addr_A(hBGMapMode);
                        hram->hBGMapMode = 0;
                        // CALL(aPokegearPhone_UpdateDisplayList);
                        PokegearPhone_UpdateDisplayList();
                        // LD_HL(mPokegearAskWhoCallText);
                        // CALL(aPrintText);
                        PrintText_Conv2(PokegearAskWhoCallText);
                        // CALL(aWaitBGMap);
                        WaitBGMap_Conv();
                    }

                // CancelDelete:
                    // SCF;
                    // RET;
                    return true;
                }
                fallthrough;
            case 2:
            Cancel:
                // LD_HL(mPokegearAskWhoCallText);
                // CALL(aPrintText);
                PrintText_Conv2(PokegearAskWhoCallText);
                // SCF;
                // RET;
                return true;
            }
        }
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }
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

void Pokegear_SwitchPage_Conv(uint8_t c, uint8_t b){
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_READ_TEXT_2);
    // LD_A_C;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = c;
    // LD_A_B;
    // LD_addr_A(wPokegearCard);
    wram->wPokegearCard = b;
    // CALL(aDeleteSpriteAnimStruct2ToEnd);
    DeleteSpriteAnimStruct2ToEnd();
    // RET;
}

void ExitPokegearRadio_HandleMusic(void){
    // LD_A_addr(wPokegearRadioMusicPlaying);
    // CP_A(RESTART_MAP_MUSIC);
    // IF_Z goto restart_map_music;
    if(wram->wPokegearRadioMusicPlaying == RESTART_MAP_MUSIC) {
    // restart_map_music:
        // CALL(aRestartMapMusic);
        RestartMapMusic_Conv();
        // XOR_A_A;
        // LD_addr_A(wPokegearRadioMusicPlaying);
        wram->wPokegearRadioMusicPlaying = 0;
        // RET;
        return;
    }
    // CP_A(ENTER_MAP_MUSIC);
    // CALL_Z (aPlayMapMusicBike);
    else if(wram->wPokegearRadioMusicPlaying == RESTART_MAP_MUSIC) {
        return PlayMapMusicBike_Conv();
    }
    // XOR_A_A;
    // LD_addr_A(wPokegearRadioMusicPlaying);
    // RET;
    wram->wPokegearRadioMusicPlaying = 0;
}

void DeleteSpriteAnimStruct2ToEnd(void){
    // LD_HL(wSpriteAnim2);
    struct SpriteAnim* hl = wram->wSpriteAnim + 1;
    // LD_BC(wSpriteAnimationStructsEnd - wSpriteAnim2);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(hl, wSpriteAnimationStructsEnd - wSpriteAnim2, 0);
    // LD_A(2);
    // LD_addr_A(wSpriteAnimCount);
    wram->wSpriteAnimCount = 2;
    // RET;
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

// Format: repeat count, tile ID
// Terminated with -1
void Pokegear_LoadTilemapRLE_Conv2(const char* path){
    asset_s a = LoadAsset(path);
    const uint8_t* de = a.ptr;
    uint8_t* hl = coord(0, 0, wram->wTilemap);

    while(1)
    {
        uint8_t id = *(de++);
        if(id == 0xff) 
            break;
        
        uint8_t repeat = *(de++);
        do {
            *(hl++) = id;
        } while(--repeat != 0);
    }

    FreeAsset(a);
}

const txt_cmd_s PokegearAskWhoCallText[] = {
    text_far(v_PokegearAskWhoCallText)
    text_end
};

const txt_cmd_s PokegearPressButtonText[] = {
    text_far(v_PokegearPressButtonText)
    text_end
};

const txt_cmd_s PokegearAskDeleteText[] = {
    text_far(v_PokegearAskDeleteText)
    text_end
};

void v_UpdateRadioStation(void){
    JR(mUpdateRadioStation);

//  called from engine/gfx/sprite_anims.asm

    return AnimateTuningKnob();
}

void v_UpdateRadioStation_Conv(void){
    // JR(mUpdateRadioStation);
    return UpdateRadioStation_Conv();
}

//  called from engine/gfx/sprite_anims.asm
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

static void AnimateTuningKnob_TuningKnob(void) {
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_HL(wRadioTuningKnob);
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wRadioTuningKnob == 0)
            return;
        // DEC_hl;
        // DEC_hl;
        wram->wRadioTuningKnob -= 2;
        // goto update;
    }
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    else if(hram->hJoyLast & D_UP) {
    // up:
        // LD_HL(wRadioTuningKnob);
        // LD_A_hl;
        // CP_A(80);
        // RET_NC ;
        if(wram->wRadioTuningKnob >= 80)
            return;
        // INC_hl;
        // INC_hl;
        wram->wRadioTuningKnob += 2;
    }
    // RET;
    else {
        return;
    }

// update:
    return UpdateRadioStation_Conv();
}

void AnimateTuningKnob_Conv(struct SpriteAnim* bc){
    // PUSH_BC;
    // CALL(aAnimateTuningKnob_TuningKnob);
    AnimateTuningKnob_TuningKnob();
    // POP_BC;
    // LD_A_addr(wRadioTuningKnob);
    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = wram->wRadioTuningKnob;
    // RET;
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

static const char* RadioChannels_NoSignal(void) {
    // CALL(aNoRadioStation);
    NoRadioStation_Conv();
    // RET;
    return NULL;
}

static bool RadioChannels_InJohto(void) {
//  if in Johto or on the S.S. Aqua, set carry
//  otherwise clear carry
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CP_A(LANDMARK_FAST_SHIP);
    // IF_Z goto johto;
    // CP_A(KANTO_LANDMARK);
    // IF_C goto johto;
    if(wram->wPokegearMapPlayerIconLandmark != LANDMARK_FAST_SHIP && wram->wPokegearMapPlayerIconLandmark >= KANTO_LANDMARK) {
    //  kanto
        // AND_A_A;
        // RET;
        return false;
    }

// johto:
    // SCF;
    // RET;
    return true;
}

//  Pokédex Show in the morning
//  Oak's Pokémon Talk in the afternoon and evening
static const char* RadioChannels_PKMNTalkAndPokedexShow(void){
    // CALL(aRadioChannels_InJohto);
    // IF_NC goto NoSignal;
    if(!RadioChannels_InJohto()) 
        return RadioChannels_NoSignal();
    // LD_A_addr(wTimeOfDay);
    // AND_A_A;
    // JP_Z (mLoadStation_PokedexShow);
    if(wram->wTimeOfDay == MORN_F)
        return LoadStation_PokedexShow_Conv();
    // JP(mLoadStation_OaksPokemonTalk);
    return LoadStation_OaksPokemonTalk_Conv();
}

static const char* RadioChannels_PokemonMusic(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_NC goto NoSignal;
    if(!RadioChannels_InJohto()) 
        return RadioChannels_NoSignal();
    // JP(mLoadStation_PokemonMusic);
    return LoadStation_PokemonMusic_Conv();
}

static const char* RadioChannels_LuckyChannel(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_NC goto NoSignal;
    if(!RadioChannels_InJohto()) 
        return RadioChannels_NoSignal();
    // JP(mLoadStation_LuckyChannel);
    return LoadStation_LuckyChannel_Conv();
}

static const char* RadioChannels_BuenasPassword(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_NC goto NoSignal;
    if(!RadioChannels_InJohto()) 
        return RadioChannels_NoSignal();
    // JP(mLoadStation_BuenasPassword);
    return LoadStation_BuenasPassword_Conv();
}

static const char* RadioChannels_RuinsOfAlphRadio(void) {
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CP_A(LANDMARK_RUINS_OF_ALPH);
    // IF_NZ goto NoSignal;
    if(wram->wPokegearMapPlayerIconLandmark != LANDMARK_RUINS_OF_ALPH)
        return RadioChannels_NoSignal();
    // JP(mLoadStation_UnownRadio);
    return LoadStation_UnownRadio_Conv();
}

static const char* RadioChannels_PlacesAndPeople(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_C goto NoSignal;
    if(RadioChannels_InJohto())
        return RadioChannels_NoSignal();
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_EXPN_CARD_F);
    // IF_Z goto NoSignal;
    if(!bit_test(wram->wPokegearFlags, POKEGEAR_EXPN_CARD_F))
        return RadioChannels_NoSignal();
    // JP(mLoadStation_PlacesAndPeople);
    return LoadStation_PlacesAndPeople_Conv();
}

static const char* RadioChannels_LetsAllSing(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_C goto NoSignal;
    if(RadioChannels_InJohto())
        return RadioChannels_NoSignal();
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_EXPN_CARD_F);
    // IF_Z goto NoSignal;
    if(!bit_test(wram->wPokegearFlags, POKEGEAR_EXPN_CARD_F))
        return RadioChannels_NoSignal();
    // JP(mLoadStation_LetsAllSing);
    return LoadStation_LetsAllSing_Conv();
}

static const char* RadioChannels_PokeFluteRadio(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_C goto NoSignal;
    if(RadioChannels_InJohto())
        return RadioChannels_NoSignal();
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_EXPN_CARD_F);
    // IF_Z goto NoSignal;
    if(!bit_test(wram->wPokegearFlags, POKEGEAR_EXPN_CARD_F))
        return RadioChannels_NoSignal();
    // JP(mLoadStation_PokeFluteRadio);
    return LoadStation_PokeFluteRadio_Conv();
}

//  This station airs in the Lake of Rage area when Team Rocket is still in Mahogany.
static const char* RadioChannels_EvolutionRadio(void) {
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_ROCKET_SIGNAL_F);
    // IF_Z goto NoSignal;
    if(!bit_test(wram->wStatusFlags, STATUSFLAGS_ROCKET_SIGNAL_F))
        return RadioChannels_NoSignal();
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CP_A(LANDMARK_MAHOGANY_TOWN);
    // IF_Z goto ok;
    // CP_A(LANDMARK_ROUTE_43);
    // IF_Z goto ok;
    // CP_A(LANDMARK_LAKE_OF_RAGE);
    // IF_NZ goto NoSignal;
    if(wram->wPokegearMapPlayerIconLandmark == LANDMARK_MAHOGANY_TOWN
    || wram->wPokegearMapPlayerIconLandmark == LANDMARK_ROUTE_43
    || wram->wPokegearMapPlayerIconLandmark == LANDMARK_LAKE_OF_RAGE) {
        return LoadStation_EvolutionRadio_Conv();
    }

// ok:
    // JP(mLoadStation_EvolutionRadio);
    return RadioChannels_NoSignal();
}

#define radio_freq(_x) (uint8_t)((_x * 4) - 2)

struct RadioChannel {
    uint8_t freq;
    const char* (*fn)(void);
};

const struct RadioChannel RadioChannels[] = {
    {radio_freq(04.5), RadioChannels_PKMNTalkAndPokedexShow},
    {radio_freq(07.5), RadioChannels_PokemonMusic},
    {radio_freq(08.5), RadioChannels_LuckyChannel},
    {radio_freq(10.5), RadioChannels_BuenasPassword},
    {radio_freq(13.5), RadioChannels_RuinsOfAlphRadio},
    {radio_freq(16.5), RadioChannels_PlacesAndPeople},
    {radio_freq(18.5), RadioChannels_LetsAllSing},
    {radio_freq(20.0), RadioChannels_PokeFluteRadio},
    {radio_freq(20.5), RadioChannels_EvolutionRadio},
};

#if 0
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
#endif

void UpdateRadioStation_Conv(void){
    // LD_HL(wRadioTuningKnob);
    // LD_D_hl;
    //REG_D = gb_read(wRadioTuningKnob);
    //REG_HL = mRadioChannels;
    uint8_t d = wram->wRadioTuningKnob;
    // LD_HL(mRadioChannels);

// loop:
    for(uint32_t i = 0; i < lengthof(RadioChannels); ++i) {
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto nostation;
        // CP_A_D;
        // IF_Z goto foundstation;
        if(RadioChannels[i].freq == d) {
        // foundstation:
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // LD_DE(mUpdateRadioStation_returnafterstation);
            // PUSH_DE;
            // JP_hl;
            const char* de = RadioChannels[i].fn();

        // returnafterstation:
            // LD_A_addr(wPokegearRadioChannelBank);
            // AND_A_A;
            // RET_Z ;
            if(!de)
                return;
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0;
            // hlcoord(2, 9, wTilemap);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(de), coord(2, 9, wram->wTilemap));
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0x1;
            // RET;
            return;
        }
        // INC_HL;
        // INC_HL;
        // goto loop;
    }


// nostation:
    // CALL(aNoRadioStation);
    NoRadioStation_Conv();
    // RET;
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

const char* LoadStation_OaksPokemonTalk_Conv(void){
    // XOR_A_A;  // OAKS_POKEMON_TALK
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = OAKS_POKEMON_TALK;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mOaksPKMNTalkName);
    // RET;
    return OaksPKMNTalkName;
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

const char* LoadStation_PokedexShow_Conv(void){
    // LD_A(POKEDEX_SHOW);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = POKEDEX_SHOW;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mPokedexShowName);
    // RET;
    return PokedexShowName;
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

const char* LoadStation_PokemonMusic_Conv(void){
    // LD_A(POKEMON_MUSIC);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = POKEMON_MUSIC;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mPokemonMusicName);
    // RET;
    return PokemonMusicName;
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

const char* LoadStation_LuckyChannel_Conv(void){
    // LD_A(LUCKY_CHANNEL);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = LUCKY_CHANNEL;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mLuckyChannelName);
    // RET;
    return LuckyChannelName;
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

const char* LoadStation_BuenasPassword_Conv(void){
    // LD_A(BUENAS_PASSWORD);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = BUENAS_PASSWORD;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mNotBuenasPasswordName);
    // LD_A_addr(wStatusFlags2);
    // BIT_A(STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F);
    // RET_Z ;
    // LD_DE(mBuenasPasswordName);
    // RET;
    return (bit_test(wram->wStatusFlags2, STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F))? BuenasPasswordName: NotBuenasPasswordName;
}

const char BuenasPasswordName[] = "BUENA'S PASSWORD@";

const char NotBuenasPasswordName[] = "@";

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

const char* LoadStation_UnownRadio_Conv(void){
    // LD_A(UNOWN_RADIO);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = UNOWN_RADIO;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mUnownStationName);
    // RET;
    return UnownStationName;
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

const char* LoadStation_PlacesAndPeople_Conv(void){
    // LD_A(PLACES_AND_PEOPLE);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = PLACES_AND_PEOPLE;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mPlacesAndPeopleName);
    // RET;
    return PlacesAndPeopleName;
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

const char* LoadStation_LetsAllSing_Conv(void){
    // LD_A(LETS_ALL_SING);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = LETS_ALL_SING;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mLetsAllSingName);
    // RET;
    return LetsAllSingName;
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

const char* LoadStation_RocketRadio_Conv(void){
    // LD_A(ROCKET_RADIO);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = ROCKET_RADIO;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mLetsAllSingName);
    // RET;
    return LetsAllSingName;
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

const char* LoadStation_PokeFluteRadio_Conv(void){
    // LD_A(POKE_FLUTE_RADIO);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = POKE_FLUTE_RADIO;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mPokeFluteStationName);
    // RET;
    return PokeFluteStationName;
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

const char* LoadStation_EvolutionRadio_Conv(void){
    // LD_A(EVOLUTION_RADIO);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = EVOLUTION_RADIO;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams_Conv(PlayRadioShow_Conv);
    // LD_DE(mUnownStationName);
    // RET;
    return UnownStationName;
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
    wram->wPokegearRadioMusicPlaying = (uint8_t)(de & 0xFF);
    PlayMusic_Conv(MUSIC_NONE);
    wram->wMapMusic = (uint8_t)(de & 0xFF);
    PlayMusic_Conv(de);
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
    PlayMusic_Conv(MUSIC_NONE);
    PlayMusic_Conv(MUSIC_POKEMON_CHANNEL);
}

void Radio_BackUpFarCallParams(void){
    LD_addr_A(wPokegearRadioChannelBank);
    LD_A_L;
    LD_addr_A(wPokegearRadioChannelAddr);
    LD_A_H;
    LD_addr_A(wPokegearRadioChannelAddr + 1);
    RET;

}

void Radio_BackUpFarCallParams_Conv(void (*hl)(void)){
    // LD_addr_A(wPokegearRadioChannelBank);
    // LD_A_L;
    // LD_addr_A(wPokegearRadioChannelAddr);
    // LD_A_H;
    // LD_addr_A(wPokegearRadioChannelAddr + 1);
    // RET;
    gPokegearRadioChannelAddr = hl;
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
    wram->wPokegearRadioChannelBank = 0;
    // gb_write16(wPokegearRadioChannelAddr, 0);
    gPokegearRadioChannelAddr = NULL;
    hram->hBGMapMode = 0x1;
}

void NoRadioMusic(void){
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    LD_A(ENTER_MAP_MUSIC);
    LD_addr_A(wPokegearRadioMusicPlaying);
    RET;

}

void NoRadioMusic_Conv(void){
    PlayMusic_Conv(MUSIC_NONE);
    wram->wPokegearRadioMusicPlaying = ENTER_MAP_MUSIC;
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
    hram->hBGMapMode = 0;

    // hlcoord(1, 8, wTilemap);
    // LD_BC((3 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv(coord(1, 8, wTilemap), (3 << 8) | 18);

    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
    // RET;
}

const char OaksPKMNTalkName[] = "OAK's <PK><MN> Talk@";

const char PokedexShowName[] = "#DEX Show@";

const char PokemonMusicName[] = "#MON Music@";

const char LuckyChannelName[] = "Lucky Channel@";

const char UnownStationName[] = "?????@";

const char PlacesAndPeopleName[] = "Places & People@";

const char LetsAllSingName[] = "Let's All Sing!@";

const char PokeFluteStationName[] = "# FLUTE@";

static void v_TownMap_loop(uint8_t d, uint8_t e){
    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // RET_NZ ;
        if(hram->hJoyPressed & B_BUTTON)
            return;

        // LD_HL(hJoyLast);
        // LD_A_hl;
        // AND_A(D_UP);
        // IF_NZ goto pressed_up;
        if(hram->hJoyLast & D_UP) {
        // pressed_up:
            // LD_HL(wTownMapCursorLandmark);
            // LD_A_hl;
            // CP_A_D;
            // IF_C goto okay;
            // LD_A_E;
            // DEC_A;
            // LD_hl_A;


        // okay:
            // INC_hl;
            wram->wTownMapCursorLandmark = (wram->wTownMapCursorLandmark < d)
                ? wram->wTownMapCursorLandmark + 1
                : e;
            // goto next;
            break;
        }

        // LD_A_hl;
        // AND_A(D_DOWN);
        // IF_NZ goto pressed_down;
        else if(hram->hJoyLast & D_DOWN) {
        // pressed_down:
            // LD_HL(wTownMapCursorLandmark);
            // LD_A_hl;
            // CP_A_E;
            // IF_NZ goto okay2;
            // LD_A_D;
            // INC_A;
            // LD_hl_A;


        // okay2:
            wram->wTownMapCursorLandmark = (wram->wTownMapCursorLandmark != e)
                ? wram->wTownMapCursorLandmark - 1
                : d;
            // DEC_hl;
            break;
        }
        else {
        loop2:
            // PUSH_DE;
            // FARCALL(aPlaySpriteAnimations);
            {
                bank_push(BANK(aPlaySpriteAnimations));
                PlaySpriteAnimations_Conv();
                bank_pop;
            }
            // POP_DE;
            // CALL(aDelayFrame);
            DelayFrame();
            // goto loop;
        }
    } while(1);


// next:
    // PUSH_DE;
    // LD_A_addr(wTownMapCursorLandmark);
    // CALL(aPokegearMap_UpdateLandmarkName);
    PokegearMap_UpdateLandmarkName_Conv(wram->wTownMapCursorLandmark);
    // LD_A_addr(wTownMapCursorObjectPointer);
    // LD_C_A;
    // LD_A_addr(wTownMapCursorObjectPointer + 1);
    // LD_B_A;
    struct SpriteAnim* bc = gTownMapCursorObjectPointer;
    // LD_A_addr(wTownMapCursorLandmark);
    // CALL(aPokegearMap_UpdateCursorPosition);
    PokegearMap_UpdateCursorPosition_Conv(bc, wram->wTownMapCursorLandmark);
    // POP_DE;
    goto loop2;
}

static void v_TownMap_InitTilemap(void) {
// InitTilemap:
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // CP_A(KANTO_LANDMARK);
    // IF_NC goto kanto2;
    // LD_E(JOHTO_REGION);
    // goto okay_tilemap;


// kanto2:
    // LD_E(KANTO_REGION);
    uint8_t region = (wram->wTownMapPlayerIconLandmark >= KANTO_LANDMARK)
        ? KANTO_REGION
        : JOHTO_REGION;

// okay_tilemap:
    // FARCALL(aPokegearMap);
    PokegearMap_Conv(region);
    // LD_A(0x07);
    // LD_BC(6);
    // hlcoord(1, 0, wTilemap);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(1, 0, wram->wTilemap), 6, 0x07);
    // hlcoord(0, 0, wTilemap);
    // LD_hl(0x06);
    *coord(0, 0, wram->wTilemap) = 0x06;
    // hlcoord(7, 0, wTilemap);
    // LD_hl(0x17);
    *coord(7, 0, wram->wTilemap) = 0x17;
    // hlcoord(7, 1, wTilemap);
    // LD_hl(0x16);
    *coord(7, 1, wram->wTilemap) = 0x16;
    // hlcoord(7, 2, wTilemap);
    // LD_hl(0x26);
    *coord(7, 2, wram->wTilemap) = 0x26;
    // LD_A(0x07);
    // LD_BC(NAME_LENGTH);
    // hlcoord(8, 2, wTilemap);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(8, 2, wram->wTilemap), NAME_LENGTH, 0x07);
    // hlcoord(19, 2, wTilemap);
    // LD_hl(0x17);
    *coord(19, 2, wram->wTilemap) = 0x17;
    // LD_A_addr(wTownMapCursorLandmark);
    // CALL(aPokegearMap_UpdateLandmarkName);
    PokegearMap_UpdateLandmarkName_Conv(wram->wTownMapCursorLandmark);
    // FARCALL(aTownMapPals);
    TownMapPals_Conv();
    // RET;
}

void v_TownMap(void){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);

    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;

    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;

    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALL(aPokegear_LoadGFX);
    Pokegear_LoadGFX_Conv();
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // LD_A(8);
    // CALL(aSkipMusic);
    SkipMusic_Conv(4);
    // LD_A(LCDC_DEFAULT);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, LCDC_DEFAULT);
    // CALL(aTownMap_GetCurrentLandmark);
    uint8_t landmark = TownMap_GetCurrentLandmark_Conv();
    // LD_addr_A(wTownMapPlayerIconLandmark);
    wram->wTownMapPlayerIconLandmark = landmark;
    // LD_addr_A(wTownMapCursorLandmark);
    wram->wTownMapCursorLandmark = landmark;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(av_TownMap_InitTilemap);
    v_TownMap_InitTilemap();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // CALL(aPokegearMap_InitPlayerIcon);
    PokegearMap_InitPlayerIcon_Conv(landmark);
    // LD_A_addr(wTownMapCursorLandmark);
    // CALL(aPokegearMap_InitCursor);
    struct SpriteAnim* bc = PokegearMap_InitCursor_Conv(wram->wTownMapCursorLandmark);
    // LD_A_C;
    // LD_addr_A(wTownMapCursorObjectPointer);
    // LD_A_B;
    // LD_addr_A(wTownMapCursorObjectPointer + 1);
    gTownMapCursorObjectPointer = bc;
    // LD_B(SCGB_POKEGEAR_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_POKEGEAR_PALS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto dmg;
    if(hram->hCGB == 0) {
    // dmg:
        // LD_A_addr(wTownMapPlayerIconLandmark);
        // CP_A(KANTO_LANDMARK);
        // IF_NC goto kanto;
        if(wram->wTownMapPlayerIconLandmark >= KANTO_LANDMARK)
            goto kanto;
        // LD_D(KANTO_LANDMARK - 1);
        // LD_E(1);
        // CALL(av_TownMap_loop);
        v_TownMap_loop(KANTO_LANDMARK - 1, 1);
        // goto resume;
    }
    else {
        // LD_A(0b11100100);
        // CALL(aDmgToCgbObjPal0);
        DmgToCgbObjPal0_Conv(0b11100100);
        // CALL(aDelayFrame);
        DelayFrame();

        kanto: {
            // CALL(aTownMap_GetKantoLandmarkLimits);
            u8_pair_s de = TownMap_GetKantoLandmarkLimits_Conv();
            // CALL(av_TownMap_loop);
            v_TownMap_loop(de.a, de.b);
        }
    }

// resume:
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // RET;
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

static void PlayRadio_PlayStation(uint8_t e) {
    // LD_A(ENTER_MAP_MUSIC);
    // LD_addr_A(wPokegearRadioMusicPlaying);
    wram->wPokegearRadioMusicPlaying = ENTER_MAP_MUSIC;
    // LD_HL(mPlayRadioStationPointers);
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mPlayRadio_jump_return);
    // PUSH_DE;
    // JP_hl;
    const char* de = PlayRadioStationPointers[e]();


// jump_return:
    // PUSH_DE;
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
    // hlcoord(1, 14, wTilemap);
    // LD_hl(0x72);
    *coord(1, 14, wram->wTilemap) = 0x72;
    // POP_DE;
    // hlcoord(2, 14, wTilemap);
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = U82C(de), .hl = coord(2, 14, wram->wTilemap)};
    PlaceString_Conv(&st, st.hl);
    // LD_H_B;
    // LD_L_C;
    // LD_hl(0x73);
    *st.bc = 0x73;
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // RET;
}

void PlayRadio_Conv(uint8_t e){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aPlayRadio_PlayStation);
    PlayRadio_PlayStation(e);
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames_Conv(100);

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LDH_A_addr(hJoyPressed);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto stop;
        if(hram->hJoyPressed & (A_BUTTON | B_BUTTON))
            break;
        // LD_A_addr(wPokegearRadioChannelAddr);
        // LD_L_A;
        // LD_A_addr(wPokegearRadioChannelAddr + 1);
        // LD_H_A;
        // LD_A_addr(wPokegearRadioChannelBank);
        // AND_A_A;
        // IF_Z goto zero;
        // RST(aFarCall);
        if(gPokegearRadioChannelAddr != NULL)
            gPokegearRadioChannelAddr();

    // zero:
        // CALL(aDelayFrame);
        // goto loop;
        DelayFrame();
    }


// stop:
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // RET;
}

const char* (*const PlayRadioStationPointers[])(void) = {
//  entries correspond to MAPRADIO_* constants
    //table_width ['2', 'PlayRadioStationPointers']
    [MAPRADIO_POKEMON_CHANNEL]  = LoadStation_PokemonChannel_Conv,
    [MAPRADIO_OAKS_POKEMON_TALK]= LoadStation_OaksPokemonTalk_Conv,
    [MAPRADIO_POKEDEX_SHOW]     = LoadStation_PokedexShow_Conv,
    [MAPRADIO_POKEMON_MUSIC]    = LoadStation_PokemonMusic_Conv,
    [MAPRADIO_LUCKY_CHANNEL]    = LoadStation_LuckyChannel_Conv,
    [MAPRADIO_UNOWN]            = LoadStation_UnownRadio_Conv,
    [MAPRADIO_PLACES_PEOPLE]    = LoadStation_PlacesAndPeople_Conv,
    [MAPRADIO_LETS_ALL_SING]    = LoadStation_LetsAllSing_Conv,
    [MAPRADIO_ROCKET]           = LoadStation_RocketRadio_Conv,
    //assert_table_length ['NUM_MAP_RADIO_STATIONS']
};

static_assert(lengthof(PlayRadioStationPointers) == NUM_MAP_RADIO_STATIONS, "");

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

const char* LoadStation_PokemonChannel_Conv(void){
    // CALL(aIsInJohto);
    // AND_A_A;
    // IF_NZ goto kanto;
    if(IsInJohto_Conv() == JOHTO_REGION) {
        // CALL(aUpdateTime);
        UpdateTime_Conv();
        // LD_A_addr(wTimeOfDay);
        // AND_A_A;
        // JP_Z (mLoadStation_PokedexShow);
        if(wram->wTimeOfDay == MORN_F)
            return LoadStation_PokedexShow_Conv();
        // JP(mLoadStation_OaksPokemonTalk);
        return LoadStation_OaksPokemonTalk_Conv();
    }
    else {
    // kanto:
        // JP(mLoadStation_PlacesAndPeople);
        return LoadStation_PlacesAndPeople_Conv();
    }
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

void PokegearMap_Conv(uint8_t e){
    // LD_A_E;
    // AND_A_A;
    // IF_NZ goto kanto;
    if(e != JOHTO_REGION) {
    // kanto:
        // CALL(aLoadTownMapGFX);
        LoadTownMapGFX_Conv();
        // CALL(aFillKantoMap);
        FillKantoMap_Conv();
        // RET;
        return;
    }
    else {
        // CALL(aLoadTownMapGFX);
        LoadTownMapGFX_Conv();
        // CALL(aFillJohtoMap);
        FillJohtoMap_Conv();
        // RET;
        return;
    }
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

static void TownMapBubble_Name(void) {
//  We need the map location of the default flypoint
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;  // two bytes per flypoint
    // LD_DE(mFlypoints);
    // ADD_HL_DE;
    // LD_E_hl;
    // FARCALL(aGetLandmarkName);
    // hlcoord(2, 1, wTilemap);
    // LD_DE(wStringBuffer1);
    // CALL(aPlaceString);
    PlaceStringSimple(GetLandmarkName_Conv(Flypoints[wram->wTownMapPlayerIconLandmark].landmark), coord(2, 1, wram->wTilemap));
    // RET;
}

void TownMapBubble(void){
//  Draw the bubble containing the location text in the town map HUD

//  Top-left corner
    // hlcoord(1, 0, wTilemap);
    // LD_A(0x30);
    // LD_hli_A;
    *coord(1, 0, wram->wTilemap) = 0x30;
//  Top row
    // LD_BC(16);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(2, 0, wram->wTilemap), 16, 0x7f);
//  Top-right corner
    // LD_A(0x31);
    // LD_hl_A;
    *coord(18, 0, wram->wTilemap) = 0x31;
    // hlcoord(1, 1, wTilemap);

//  Middle row
    // LD_BC(SCREEN_WIDTH - 2);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(1, 1, wram->wTilemap), SCREEN_WIDTH - 2, 0x7f);

//  Bottom-left corner
    // hlcoord(1, 2, wTilemap);
    // LD_A(0x32);
    // LD_hli_A;
    *coord(1, 2, wram->wTilemap) = 0x32;
//  Bottom row
    // LD_BC(16);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(2, 2, wram->wTilemap), 16, 0x7f);
//  Bottom-right corner
    // LD_A(0x33);
    // LD_hl_A;
    *coord(18, 2, wram->wTilemap) = 0x33;

//  Print "Where?"
    // hlcoord(2, 0, wTilemap);
    // LD_DE(mTownMapBubble_Where);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("Where?@"), coord(2, 0, wram->wTilemap));
//  Print the name of the default flypoint
    // CALL(aTownMapBubble_Name);
    TownMapBubble_Name();
//  Up/down arrows
    // hlcoord(18, 1, wTilemap);
    // LD_hl(0x34);
    *coord(18, 1, wram->wTilemap) = 0x34;
    // RET;
    return;

// Where:
    //db ['"Where?@"'];
}

void GetMapCursorCoordinates(void){
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // LD_DE(mFlypoints);
    // ADD_HL_DE;
    // LD_E_hl;
    uint8_t e = Flypoints[wram->wTownMapPlayerIconLandmark].landmark;
    // FARCALL(aGetLandmarkCoords);
    struct Coords coord = GetLandmarkCoords_Conv(e);
    // LD_A_addr(wTownMapCursorCoordinates);
    // LD_C_A;
    // LD_A_addr(wTownMapCursorCoordinates + 1);
    // LD_B_A;
    // LD_HL(4);
    // ADD_HL_BC;
    // LD_hl_E;
    gTownMapCursorCoordinates->xCoord = (uint8_t)coord.x;
    // LD_HL(5);
    // ADD_HL_BC;
    // LD_hl_D;
    gTownMapCursorCoordinates->yCoord = (uint8_t)coord.y;
    // RET;
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

//  Update BG Map tiles and attributes
void TownMapBGUpdate_Conv(uint16_t hl){
//  BG Map address
    // LD_A_L;
    // LDH_addr_A(hBGMapAddress);
    // LD_A_H;
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = hl;
//  Only update palettes on CGB
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto tiles;
    if(hram->hCGB != 0) {
    //  BG Map mode 2 (palettes)
        // LD_A(2);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 2;
    //  The BG Map is updated in thirds, so we wait

    //  3 frames to update the whole screen's palettes.
        // LD_C(3);
        // CALL(aDelayFrames);
        DelayFrames_Conv(3);
    }
// tiles:
//  Update BG Map tiles
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
//  Turn off BG Map update
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // RET;
    return;
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
    asset_s a = LoadAsset(JohtoMap);
    FillTownMap_Conv(a.ptr);
    FreeAsset(a);
}

void FillKantoMap_Conv(void){
    asset_s a = LoadAsset(KantoMap);
    FillTownMap_Conv(a.ptr);
    FreeAsset(a);
}

void FillTownMap_Conv(const uint8_t* map){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    const uint8_t* de = map;

    while(*de != 0xff)
    {
        // LD_A_de;

        // CP_A(-1);
        // RET_Z ;

        // LD_A_de;
        // LD_hli_A;
        // INC_DE;
        *(hl++) = *(de++);
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


// PalMap:
// INCLUDE "gfx/pokegear/town_map_palette_map.asm"
}

enum {
    PAL_TOWNMAP_BORDER,   // 0
    PAL_TOWNMAP_EARTH,    // 1
    PAL_TOWNMAP_MOUNTAIN, // 2
    PAL_TOWNMAP_CITY,     // 3
    PAL_TOWNMAP_POI,      // 4
    PAL_TOWNMAP_POI_MTN,  // 5
};

#define townmappair(_0, _1) ((PAL_TOWNMAP_##_1 & 0xf) << 4) | (PAL_TOWNMAP_##_0 & 0xf)
#define townmappals(_0, _1, _2, _3, _4, _5, _6, _7) townmappair(_0, _1), townmappair(_2, _3), townmappair(_4, _5), townmappair(_6, _7)

void TownMapPals_Conv(void){
    static const uint8_t PalMap[] = {
    // gfx/pokegear/town_map.png
        townmappals(EARTH,    EARTH,    EARTH,    MOUNTAIN, MOUNTAIN, MOUNTAIN, BORDER,   BORDER),
        townmappals(EARTH,    EARTH,    CITY,     EARTH,    POI,      POI_MTN,  POI,      POI_MTN),
        townmappals(EARTH,    EARTH,    EARTH,    MOUNTAIN, MOUNTAIN, MOUNTAIN, BORDER,   BORDER),
        townmappals(EARTH,    EARTH,    BORDER,   EARTH,    EARTH,    BORDER,   BORDER,   BORDER),
        townmappals(EARTH,    EARTH,    EARTH,    MOUNTAIN, MOUNTAIN, MOUNTAIN, BORDER,   BORDER),
        townmappals(BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER),
    // gfx/pokegear/pokegear.png
        townmappals(BORDER,   BORDER,   BORDER,   BORDER,   POI,      POI,      POI,      BORDER),
        townmappals(BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER),
        townmappals(CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY),
        townmappals(CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     BORDER),
        townmappals(CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY),
        townmappals(BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER),
    };
//  Assign palettes based on tile ids
    // hlcoord(0, 0, wTilemap);
    const uint8_t* hl = coord(0, 0, wram->wTilemap);
    // decoord(0, 0, wAttrmap);
    uint8_t* de = coord(0, 0, wram->wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    uint16_t bc = SCREEN_WIDTH * SCREEN_HEIGHT;

    do {
    // loop:
    //  Current tile
        // LD_A_hli;
        uint8_t a = *(hl++);
        // PUSH_HL;
    //  The palette map covers tiles $00 to $5f
        // CP_A(0x60);
        // IF_NC goto pal0;
        if(a < 0x60) {

        //  The palette data is condensed to nybbles, least-significant first.
            // LD_HL(mTownMapPals_PalMap);
            // SRL_A;
            // IF_C goto odd;
            if((a & 1) == 0) {
            //  Even-numbered tile ids take the bottom nybble...
                // ADD_A_L;
                // LD_L_A;
                // LD_A_H;
                // ADC_A(0);
                // LD_H_A;
                // LD_A_hl;
                // AND_A(PALETTE_MASK);
                a = PalMap[a >> 1] & PALETTE_MASK;
                // goto update;
            }
            else {
            // odd:
            //  ...and odd ids take the top.
                // ADD_A_L;
                // LD_L_A;
                // LD_A_H;
                // ADC_A(0);
                // LD_H_A;
                // LD_A_hl;
                // SWAP_A;
                // AND_A(PALETTE_MASK);
                a = (PalMap[a >> 1] >> 4) & PALETTE_MASK;
                // goto update;
            }
        } else {
        // pal0:
            // XOR_A_A;
            a = 0;
        }
    // update:
        // POP_HL;
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
    return;
}

void TownMapMon(void){
//  Draw the FlyMon icon at town map location

//  Get FlyMon species
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartySpecies);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wTempIconSpecies);
    wram->wTempIconSpecies = wram->wPartySpecies[wram->wCurPartyMon];
//  Get FlyMon icon
    // LD_E(0x08);  // starting tile in VRAM
    // FARCALL(aGetSpeciesIcon);
    GetSpeciesIcon_Conv(0x08);
//  Animation/palette
    //depixel ['0', '0']
    // depixel2(0, 0);
    // LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_PARTY_MON, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x08);
    bc->tileID = 0x08;
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_NULL);
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
    // RET;
}

//  Draw the FlyMon icon at town map location
struct SpriteAnim* TownMapMon_Conv(void){

//  Get FlyMon species
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartySpecies);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wTempIconSpecies);
    wram->wTempIconSpecies = wram->wPartySpecies[wram->wCurPartyMon];
//  Get FlyMon icon
    // LD_E(0x08);  // starting tile in VRAM
    // FARCALL(aGetSpeciesIcon);
    GetSpeciesIcon_Conv(0x08);
//  Animation/palette
    //depixel ['0', '0']
    // depixel2(0, 0);
    // LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_PARTY_MON, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x08);
    bc->tileID = 0x08;
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_NULL);
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
    // RET;
    return bc;
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

struct SpriteAnim* TownMapPlayerIcon_Conv(uint8_t location){
//  Draw the player icon at town map location in a
    // PUSH_AF;
    // FARCALL(aGetPlayerIcon);
    const char* path = GetPlayerIcon_Conv2();
//  Standing icon
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x10);
    // LD_C(4);  // # tiles
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x10, path, 0, 4);
//  Walking icon
    // LD_HL(12 * LEN_2BPP_TILE);
    // ADD_HL_DE;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x14);
    // LD_C(4);  // # tiles
    // LD_A(BANK(aChrisSpriteGFX));  // does nothing
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x14, path, 12, 4);
//  Animation/palette
    //depixel ['0', '0']
    // depixel2(0, 0);
    // LD_B(SPRITE_ANIM_INDEX_RED_WALK);  // Male
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_gender;
    // LD_B(SPRITE_ANIM_INDEX_BLUE_WALK);  // Female
    uint8_t b = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? SPRITE_ANIM_INDEX_BLUE_WALK: SPRITE_ANIM_INDEX_RED_WALK;

// got_gender:
    // LD_A_B;
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(b, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x10);
    bc->tileID = 0x10;
    // POP_AF;
    // LD_E_A;
    // PUSH_BC;
    // FARCALL(aGetLandmarkCoords);
    struct Coords coord = GetLandmarkCoords_Conv(location);
    // POP_BC;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->xCoord = (uint8_t)coord.x;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yCoord = (uint8_t)coord.y;
    // RET;
    return bc;
}

void LoadTownMapGFX(void){
    // LD_HL(mTownMapGFX);
    // LD_DE(vTiles2);
    // LD_BC((BANK(aTownMapGFX) << 8) | 48);
    // CALL(aDecompressRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, TownMapGFX, 0, 48);
    // RET;

}

void LoadTownMapGFX_Conv(void){
    // LD_HL(mTownMapGFX);
    // LD_DE(vTiles2);
    // LD_BC((BANK(aTownMapGFX) << 8) | 48);
    // CALL(aDecompressRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, TownMapGFX, 0, 48);
    // RET;
}

const char JohtoMap[] = "gfx/pokegear/johto.bin";

const char KantoMap[] = "gfx/pokegear/kanto.bin";

void PokedexNestIconGFX(void){
// INCBIN "gfx/pokegear/dexmap_nest_icon.2bpp"
}

static const char FlyMapLabelBorderGFX[] = "gfx/pokegear/flymap_label_border.png";

static void EntireFlyMap_HandleDPad(void){
    // LD_HL(hJoyLast);
    uint8_t joy = hram->hJoyLast;
    // LD_A_hl;
    // AND_A(D_DOWN | D_RIGHT);
    // IF_NZ goto ScrollNext;
    if(joy & (D_DOWN | D_RIGHT)) {
    // ScrollNext:
        // LD_HL(wTownMapPlayerIconLandmark);
        // LD_A_hl;
        // CP_A(NUM_FLYPOINTS - 1);
        // IF_C goto NotAtEndYet;
        if(wram->wTownMapPlayerIconLandmark >= NUM_FLYPOINTS - 1) {
            // LD_hl(-1);
            wram->wTownMapPlayerIconLandmark = 0xff;
        }
    // NotAtEndYet:
        // INC_hl;
        wram->wTownMapPlayerIconLandmark++;
        // goto FillMap;
    }
    // LD_A_hl;
    // AND_A(D_UP | D_LEFT);
    // IF_NZ goto ScrollPrev;
    else if(joy & (D_UP | D_LEFT)) {
    // ScrollPrev:
        // LD_HL(wTownMapPlayerIconLandmark);
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto NotAtStartYet;
        if(wram->wTownMapPlayerIconLandmark == 0) {
            // LD_hl(NUM_FLYPOINTS);
            wram->wTownMapPlayerIconLandmark = NUM_FLYPOINTS;
        }

    // NotAtStartYet:
        // DEC_hl;
        wram->wTownMapPlayerIconLandmark--;
    }
    else {
        return;
    }
    // RET;

// FillMap:
    uint16_t b;
    uint8_t y;
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // CP_A(KANTO_FLYPOINT);
    // IF_C goto InJohto;
    if(wram->wTownMapPlayerIconLandmark >= KANTO_FLYPOINT) {
        // CALL(aFillKantoMap);
        FillKantoMap_Conv();
        // XOR_A_A;
        y = 0;
        // LD_B(HIGH(vBGMap1));
        b = vBGMap1;
        // goto Finally;
    }
    else {
    // InJohto:
        // CALL(aFillJohtoMap);
        FillJohtoMap_Conv();
        // LD_A(SCREEN_HEIGHT_PX);
        y = SCREEN_HEIGHT_PX;
        // LD_B(HIGH(vBGMap0));
        b = vBGMap0;
    }

// Finally:
    // LDH_addr_A(hWY);
    hram->hWY = y;
    // LD_A_B;
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = b;
    // CALL(aTownMapBubble);
    TownMapBubble();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // RET;
}

//  //  unreferenced
//  Similar to _FlyMap, but scrolls through the entire
//  Flypoints data of both regions. A debug function?
uint8_t EntireFlyMap(void){
    // XOR_A_A;
    // LD_addr_A(wTownMapPlayerIconLandmark);
    wram->wTownMapPlayerIconLandmark = 0;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // LD_HL(hInMenu);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_hl(0x1);
    hram->hInMenu = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aLoadTownMapGFX);
    LoadTownMapGFX_Conv();
    // LD_DE(mFlyMapLabelBorderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x30);
    // LD_BC((BANK(aFlyMapLabelBorderGFX) << 8) | 6);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x30, FlyMapLabelBorderGFX, 0, 6);
    // CALL(aFillKantoMap);
    FillKantoMap_Conv();
    // CALL(aTownMapBubble);
    TownMapBubble();
    // CALL(aTownMapPals);
    TownMapPals_Conv();
    // hlbgcoord(0, 0, vBGMap1);
    // CALL(aTownMapBGUpdate);
    TownMapBGUpdate_Conv(vBGMap1);
    // CALL(aFillJohtoMap);
    FillJohtoMap_Conv();
    // CALL(aTownMapBubble);
    TownMapBubble();
    // CALL(aTownMapPals);
    TownMapPals_Conv();
    // hlbgcoord(0, 0, vBGMap0);
    // CALL(aTownMapBGUpdate);
    TownMapBGUpdate_Conv(vBGMap0);
    // CALL(aTownMapMon);
    // LD_A_C;
    // LD_addr_A(wTownMapCursorCoordinates);
    // LD_A_B;
    // LD_addr_A(wTownMapCursorCoordinates + 1);
    gTownMapCursorCoordinates = TownMapPlayerIcon_Conv(wram->wTownMapPlayerIconLandmark);
    // LD_B(SCGB_POKEGEAR_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_POKEGEAR_PALS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();

    uint8_t a;
    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto pressedB;
        if(hram->hJoyPressed & B_BUTTON) {
        // pressedB:
            // LD_A(-1);
            // goto exit;
            a = 0xff;
            break;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON);
        // IF_NZ goto pressedA;
        else if(hram->hJoypadPressed & A_BUTTON) {
        // pressedA:
            // LD_A_addr(wTownMapPlayerIconLandmark);
            // LD_L_A;
            // LD_H(0);
            // ADD_HL_HL;
            // LD_DE(mFlypoints + 1);
            // ADD_HL_DE;
            // LD_A_hl;
            a = Flypoints[wram->wTownMapPlayerIconLandmark].spawn;
            break;
        }
        // CALL(aEntireFlyMap_HandleDPad);
        EntireFlyMap_HandleDPad();
        // CALL(aGetMapCursorCoordinates);
        GetMapCursorCoordinates();
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations_Conv();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// exit:
    // LD_addr_A(wTownMapPlayerIconLandmark);
    wram->wTownMapPlayerIconLandmark = a;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // LD_A(SCREEN_HEIGHT_PX);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // XOR_A_A;  // LOW(vBGMap0)
    // LDH_addr_A(hBGMapAddress);
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap0;
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // LD_E_A;
    return wram->wTownMapPlayerIconLandmark;
    // RET;

}
