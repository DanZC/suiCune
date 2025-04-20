#include "../../constants.h"
#include "naming_screen.h"
#include "../../home/joypad.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"
#include "../../home/lcd.h"
#include "../../home/video.h"
#include "../../home/copy.h"
#include "../../home/clear_sprites.h"
#include "../../home/gfx.h"
#include "../../home/text.h"
#include "../../home/names.h"
#include "../../home/sprite_anims.h"
#include "../../home/sprite_updates.h"
#include "../../home/map.h"
#include "../../home/palettes.h"
#include "../pokemon/mon_stats.h"
#include "../gfx/sprites.h"
#include "../gfx/mon_icons.h"
#include "../gfx/player_gfx.h"
#include "../../gfx/sprites.h"
#include "../../data/text/name_input_chars.h"
#include "../../data/text/mail_input_chars.h"

#define NAMINGSCREEN_CURSOR     (0x7e)

#define NAMINGSCREEN_BORDER     (0x60)  //  "■"
#define NAMINGSCREEN_MIDDLELINE (0xeb)  //  "→"
#define NAMINGSCREEN_UNDERLINE  (0xf2)  //  "<DOT>"

uint8_t* gNamingScreenDestinationPointer;
uint8_t* gNamingScreenStringEntryCoord;
struct SpriteAnim* gNamingScreenCursorObjectPointer;

void v_NamingScreen(void){
    CALL(aDisableSpriteUpdates);
    CALL(aNamingScreen);
    CALL(aReturnToMapWithSpeechTextbox);
    RET;

}

void v_NamingScreen_Conv(uint8_t* de, uint8_t b){
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates_Conv();
    // CALL(aNamingScreen);
    NamingScreen_Conv(de, b);
    // CALL(aReturnToMapWithSpeechTextbox);
    ReturnToMapWithSpeechTextbox_Conv();
    // RET;
}

void NamingScreen(void){
    LD_HL(wNamingScreenDestinationPointer);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    LD_HL(wNamingScreenType);
    LD_hl_B;
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    LDH_A_addr(hMapAnims);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    CALL(aNamingScreen_SetUpNamingScreen);
    CALL(aDelayFrame);

loop:
    CALL(aNamingScreenJoypadLoop);
    IF_NC goto loop;
    POP_AF;
    LDH_addr_A(hInMenu);
    POP_AF;
    LDH_addr_A(hMapAnims);
    POP_AF;
    LD_addr_A(wOptions);
    CALL(aClearJoypad);
    RET;


SetUpNamingScreen:
    CALL(aClearBGPalettes);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    CALL(aDisableLCD);
    CALL(aLoadNamingScreenGFX);
    CALL(aNamingScreen_InitText);
    LD_A(LCDC_DEFAULT);
    LDH_addr_A(rLCDC);
    CALL(aNamingScreen_GetNamingScreenSetup);
    CALL(aWaitBGMap);
    CALL(aWaitTop);
    CALL(aSetPalettes);
    CALL(aNamingScreen_InitNameEntry);
    RET;


GetNamingScreenSetup:
    LD_A_addr(wNamingScreenType);
    maskbits(NUM_NAME_TYPES, 0);
    LD_E_A;
    LD_D(0);
    LD_HL(mNamingScreen_Jumptable);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


Jumptable:
//  entries correspond to NAME_* constants
    //dw ['.Pokemon'];
    //dw ['.Player'];
    //dw ['.Rival'];
    //dw ['.Mom'];
    //dw ['.Box'];
    //dw ['.Tomodachi'];
    //dw ['.Pokemon'];
    //dw ['.Pokemon'];


Pokemon:
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wTempIconSpecies);
    LD_HL(mLoadMenuMonIcon);
    LD_A(BANK(aLoadMenuMonIcon));
    LD_E(MONICON_NAMINGSCREEN);
    RST(aFarCall);
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    hlcoord(5, 2, wTilemap);
    CALL(aPlaceString);
    LD_L_C;
    LD_H_B;
    LD_DE(mNamingScreen_NicknameStrings);
    CALL(aPlaceString);
    INC_DE;
    hlcoord(5, 4, wTilemap);
    CALL(aPlaceString);
    FARCALL(aGetGender);
    IF_C goto genderless;
    LD_A(0xef);
    IF_NZ goto place_gender;
    LD_A(0xf5);

place_gender:
    hlcoord(1, 2, wTilemap);
    LD_hl_A;

genderless:
    CALL(aNamingScreen_StoreMonIconParams);
    RET;


NicknameStrings:
    //db ['"\'S@"'];
    //db ['"NICKNAME?@"'];


Player:
    FARCALL(aGetPlayerIcon);
    CALL(aNamingScreen_LoadSprite);
    hlcoord(5, 2, wTilemap);
    LD_DE(mNamingScreen_PlayerNameString);
    CALL(aPlaceString);
    CALL(aNamingScreen_StoreSpriteIconParams);
    RET;


PlayerNameString:
    //db ['"YOUR NAME?@"'];


Rival:
    LD_DE(mSilverSpriteGFX);
    LD_B(BANK(aSilverSpriteGFX));
    CALL(aNamingScreen_LoadSprite);
    hlcoord(5, 2, wTilemap);
    LD_DE(mNamingScreen_RivalNameString);
    CALL(aPlaceString);
    CALL(aNamingScreen_StoreSpriteIconParams);
    RET;


RivalNameString:
    //db ['"RIVAL\'S NAME?@"'];


Mom:
    LD_DE(mMomSpriteGFX);
    LD_B(BANK(aMomSpriteGFX));
    CALL(aNamingScreen_LoadSprite);
    hlcoord(5, 2, wTilemap);
    LD_DE(mNamingScreen_MomNameString);
    CALL(aPlaceString);
    CALL(aNamingScreen_StoreSpriteIconParams);
    RET;


MomNameString:
    //db ['"MOTHER\'S NAME?@"'];


Box:
    LD_DE(mPokeBallSpriteGFX);
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    LD_BC((BANK(aPokeBallSpriteGFX) << 8) | 4);
    CALL(aRequest2bpp);
    XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT and tile offset $00
    LD_HL(wSpriteAnimDict);
    LD_hli_A;
    LD_hl_A;
    depixel4(4, 4, 4, 0);
    LD_A(SPRITE_ANIM_INDEX_RED_WALK);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_hl(0x0);
    hlcoord(5, 2, wTilemap);
    LD_DE(mNamingScreen_BoxNameString);
    CALL(aPlaceString);
    CALL(aNamingScreen_StoreBoxIconParams);
    RET;


BoxNameString:
    //db ['"BOX NAME?@"'];


Tomodachi:
    hlcoord(3, 2, wTilemap);
    LD_DE(mNamingScreen_oTomodachi_no_namae_sutoringu);
    CALL(aPlaceString);
    CALL(aNamingScreen_StoreSpriteIconParams);
    RET;


oTomodachi_no_namae_sutoringu:
    //db ['"おともだち\u3000の\u3000なまえは？@"'];


LoadSprite:
    PUSH_DE;
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    LD_C(4);
    PUSH_BC;
    CALL(aRequest2bpp);
    POP_BC;
    LD_HL(12 * LEN_2BPP_TILE);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x04);
    CALL(aRequest2bpp);
    XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT and tile offset $00
    LD_HL(wSpriteAnimDict);
    LD_hli_A;
    LD_hl_A;
    POP_DE;
    LD_B(SPRITE_ANIM_INDEX_RED_WALK);
    LD_A_D;
    CP_A(HIGH(aKrisSpriteGFX));
    IF_NZ goto not_kris;
    LD_A_E;
    CP_A(LOW(aKrisSpriteGFX));
    IF_NZ goto not_kris;
    LD_B(SPRITE_ANIM_INDEX_BLUE_WALK);

not_kris:
    LD_A_B;
    depixel4(4, 4, 4, 0);
    CALL(aInitSpriteAnimStruct);
    RET;


StoreMonIconParams:
    LD_A(MON_NAME_LENGTH - 1);
    hlcoord(5, 6, wTilemap);
    goto StoreParams;


StoreSpriteIconParams:
    LD_A(PLAYER_NAME_LENGTH - 1);
    hlcoord(5, 6, wTilemap);
    goto StoreParams;


StoreBoxIconParams:
    LD_A(BOX_NAME_LENGTH - 1);
    hlcoord(5, 4, wTilemap);
    goto StoreParams;


StoreParams:
    LD_addr_A(wNamingScreenMaxNameLength);
    LD_A_L;
    LD_addr_A(wNamingScreenStringEntryCoord);
    LD_A_H;
    LD_addr_A(wNamingScreenStringEntryCoord + 1);
    RET;

}

static void NamingScreen_SetUpNamingScreen(void);
static void NamingScreen_GetNamingScreenSetup(void);
static void NamingScreen_StoreParams(uint8_t* de, uint8_t a);
static void NamingScreen_StoreMonIconParams(void);
static void NamingScreen_StoreSpriteIconParams(void);
static void NamingScreen_StoreBoxIconParams(void);
static void NamingScreen_LoadSprite(const char* path);

void NamingScreen_Conv(uint8_t* de, uint8_t b){
    // LD_HL(wNamingScreenDestinationPointer);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gNamingScreenDestinationPointer = de;
    // LD_HL(wNamingScreenType);
    // LD_hl_B;
    wram->wNamingScreenType = b;
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    uint8_t mapAnims = hram->hMapAnims;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0;
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = TRUE;
    // CALL(aNamingScreen_SetUpNamingScreen);
    NamingScreen_SetUpNamingScreen();
    // CALL(aDelayFrame);
    DelayFrame();

    do {
    // loop:
        // CALL(aNamingScreenJoypadLoop);
        // IF_NC goto loop;
    } while(!NamingScreenJoypadLoop());
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = mapAnims;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // CALL(aClearJoypad);
    ClearJoypad();
    // RET;
    return;

}

static void NamingScreen_SetUpNamingScreen(void) {
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aLoadNamingScreenGFX);
    LoadNamingScreenGFX();
    // CALL(aNamingScreen_InitText);
    NamingScreen_InitText();
    // LD_A(LCDC_DEFAULT);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, LCDC_DEFAULT);
    // CALL(aNamingScreen_GetNamingScreenSetup);
    NamingScreen_GetNamingScreenSetup();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aWaitTop);
    WaitTop();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aNamingScreen_InitNameEntry);
    NamingScreen_InitNameEntry();
    // RET;
}

static void NamingScreen_GetNamingScreenSetup(void) {
    // LD_A_addr(wNamingScreenType);
    // maskbits(NUM_NAME_TYPES, 0);
    // LD_E_A;
    uint8_t type = wram->wNamingScreenType & 7;
    // LD_D(0);
    // LD_HL(mNamingScreen_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;


// Jumptable:
//  entries correspond to NAME_* constants
    switch(type) {
        //dw ['.Pokemon'];
        case NAME_6:
        case NAME_7:
        case NAME_MON: {
        // Pokemon:
            static const char NicknameStrings[] = "'S@""NICKNAME?@";
            // LD_A_addr(wCurPartySpecies);
            // LD_addr_A(wTempIconSpecies);
            wram->wTempIconSpecies = wram->wCurPartySpecies;
            // LD_HL(mLoadMenuMonIcon);
            // LD_A(BANK(aLoadMenuMonIcon));
            // LD_E(MONICON_NAMINGSCREEN);
            // RST(aFarCall);
            LoadMenuMonIcon_Conv(MONICON_NAMINGSCREEN);
            // LD_A_addr(wCurPartySpecies);
            // LD_addr_A(wNamedObjectIndex);
            // CALL(aGetPokemonName);
            // hlcoord(5, 2, wTilemap);
            // CALL(aPlaceString);
            struct TextPrintState st = {.de = GetPokemonName(wram->wCurPartySpecies), .hl = coord(5, 2, wram->wTilemap)};
            PlaceString_Conv(&st, st.hl);
            // LD_L_C;
            // LD_H_B;
            st.hl = st.bc;
            // LD_DE(mNamingScreen_NicknameStrings);
            st.de = U82C(NicknameStrings);
            // CALL(aPlaceString);
            PlaceString_Conv(&st, st.hl);
            // INC_DE;
            st.de++;
            // hlcoord(5, 4, wTilemap);
            st.hl = coord(5, 4, wram->wTilemap);
            // CALL(aPlaceString);
            PlaceString_Conv(&st, st.hl);
            // FARCALL(aGetGender);
            // IF_C goto genderless;
            u8_flag_s res = GetGender_Conv(wram->wMonType);
            if(!res.flag) {
                // LD_A(0xef);
                // IF_NZ goto place_gender;
                // LD_A(0xf5);

            // place_gender:
                // hlcoord(1, 2, wTilemap);
                // LD_hl_A;
                *coord(1, 2, wram->wTilemap) = (res.a != 0)? 0xef: 0xf5; 
            }

        // genderless:
            // CALL(aNamingScreen_StoreMonIconParams);
            NamingScreen_StoreMonIconParams();
            // RET;
        } return;
        //dw ['.Player'];
        case NAME_PLAYER: {
        // Player:
            static const char PlayerNameString[] = "YOUR NAME?@";
            // FARCALL(aGetPlayerIcon);
            // CALL(aNamingScreen_LoadSprite);
            NamingScreen_LoadSprite(GetPlayerIcon_Conv2());
            // hlcoord(5, 2, wTilemap);
            // LD_DE(mNamingScreen_PlayerNameString);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(PlayerNameString), coord(5, 2, wram->wTilemap));
            // CALL(aNamingScreen_StoreSpriteIconParams);
            NamingScreen_StoreSpriteIconParams();
            // RET;
        } return;
        //dw ['.Rival'];
        case NAME_RIVAL: {
        // Rival:
            static const char RivalNameString[] = "RIVAL'S NAME?@";
            // LD_DE(mSilverSpriteGFX);
            // LD_B(BANK(aSilverSpriteGFX));
            // CALL(aNamingScreen_LoadSprite);
            NamingScreen_LoadSprite(SilverSpriteGFX);
            // hlcoord(5, 2, wTilemap);
            // LD_DE(mNamingScreen_RivalNameString);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(RivalNameString), coord(5, 2, wram->wTilemap));
            // CALL(aNamingScreen_StoreSpriteIconParams);
            NamingScreen_StoreSpriteIconParams();
            // RET;
        } return;
        //dw ['.Mom'];
        case NAME_MOM: {
        // Mom:
            static const char MomNameString[] = "MOTHER'S NAME?@";
            // LD_DE(mMomSpriteGFX);
            // LD_B(BANK(aMomSpriteGFX));
            // CALL(aNamingScreen_LoadSprite);
            NamingScreen_LoadSprite(MomSpriteGFX);
            // hlcoord(5, 2, wTilemap);
            // LD_DE(mNamingScreen_MomNameString);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(MomNameString), coord(5, 2, wram->wTilemap));
            // CALL(aNamingScreen_StoreSpriteIconParams);
            NamingScreen_StoreSpriteIconParams();
            // RET;
        } return;
        //dw ['.Box'];
        case NAME_BOX: {
        // Box:
            static const char BoxNameString[] = "BOX NAME?@";
            // LD_DE(mPokeBallSpriteGFX);
            // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
            // LD_BC((BANK(aPokeBallSpriteGFX) << 8) | 4);
            // CALL(aRequest2bpp);
            LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, PokeBallSpriteGFX, 0, 4);
            // XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT and tile offset $00
            // LD_HL(wSpriteAnimDict);
            // LD_hli_A;
            wram->wSpriteAnimDict[0] = SPRITE_ANIM_DICT_DEFAULT;
            // LD_hl_A;
            wram->wSpriteAnimDict[1] = 0;
            // depixel4(4, 4, 4, 0);
            // LD_A(SPRITE_ANIM_INDEX_RED_WALK);
            // CALL(aInitSpriteAnimStruct);
            struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_RED_WALK, pixel4(4, 4, 4, 0));
            // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
            // ADD_HL_BC;
            // LD_hl(0x0);
            bc->framesetID = 0x0;
            // hlcoord(5, 2, wTilemap);
            // LD_DE(mNamingScreen_BoxNameString);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(BoxNameString), coord(5, 2, wram->wTilemap));
            // CALL(aNamingScreen_StoreBoxIconParams);
            NamingScreen_StoreBoxIconParams();
            // RET;
        } return;
        //dw ['.Tomodachi'];
        case NAME_FRIEND: {
        // Tomodachi:
            static const char oTomodachi_no_namae_sutoringu[] = "FRIEND'S NAME?"; // "おともだち\u3000の\u3000なまえは？@";
            // hlcoord(3, 2, wTilemap);
            // LD_DE(mNamingScreen_oTomodachi_no_namae_sutoringu);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(oTomodachi_no_namae_sutoringu), coord(3, 2, wram->wTilemap));
            // CALL(aNamingScreen_StoreSpriteIconParams);
            NamingScreen_StoreSpriteIconParams();
            // RET;
        } return;
        //dw ['.Pokemon'];
        //dw ['.Pokemon'];
    }
}

static void NamingScreen_LoadSprite(const char* path) {
    // PUSH_DE;
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    // LD_C(4);
    // PUSH_BC;
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, path, 0, 4);
    // POP_BC;
    // LD_HL(12 * LEN_2BPP_TILE);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x04);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x04, path, 12, 4);
    // XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT and tile offset $00
    // LD_HL(wSpriteAnimDict);
    // LD_hli_A;
    wram->wSpriteAnimDict[0] = SPRITE_ANIM_DICT_DEFAULT;
    // LD_hl_A;
    wram->wSpriteAnimDict[1] = 0;
    // POP_DE;
    // LD_B(SPRITE_ANIM_INDEX_RED_WALK);
    // LD_A_D;
    // CP_A(HIGH(aKrisSpriteGFX));
    // IF_NZ goto not_kris;
    // LD_A_E;
    // CP_A(LOW(aKrisSpriteGFX));
    // IF_NZ goto not_kris;
    // LD_B(SPRITE_ANIM_INDEX_BLUE_WALK);
    uint8_t b = (path == KrisSpriteGFX)? SPRITE_ANIM_INDEX_BLUE_WALK: SPRITE_ANIM_INDEX_RED_WALK;

// not_kris:
    // LD_A_B;
    // depixel4(4, 4, 4, 0);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct_Conv(b, pixel4(4, 4, 4, 0));
    // RET;
}

static void NamingScreen_StoreMonIconParams(void) {
    // LD_A(MON_NAME_LENGTH - 1);
    // hlcoord(5, 6, wTilemap);
    // goto StoreParams;
    return NamingScreen_StoreParams(coord(5, 6, wram->wTilemap), MON_NAME_LENGTH - 1);
}

static void NamingScreen_StoreSpriteIconParams(void) {
    // LD_A(PLAYER_NAME_LENGTH - 1);
    // hlcoord(5, 6, wTilemap);
    // goto StoreParams;
    return NamingScreen_StoreParams(coord(5, 6, wram->wTilemap), PLAYER_NAME_LENGTH - 1);
}

static void NamingScreen_StoreBoxIconParams(void) {
    // LD_A(BOX_NAME_LENGTH - 1);
    // hlcoord(5, 4, wTilemap);
    // goto StoreParams;
    return NamingScreen_StoreParams(coord(5, 4, wram->wTilemap), BOX_NAME_LENGTH - 1);
}

static void NamingScreen_StoreParams(uint8_t* de, uint8_t a) {
    // LD_addr_A(wNamingScreenMaxNameLength);
    wram->wNamingScreenMaxNameLength = a;
    // LD_A_L;
    // LD_addr_A(wNamingScreenStringEntryCoord);
    // LD_A_H;
    // LD_addr_A(wNamingScreenStringEntryCoord + 1);
    gNamingScreenStringEntryCoord = de;
    // RET;
}

//  Return true (z) if [wNamingScreenType] == NAME_BOX.
bool NamingScreen_IsTargetBox(void){
    // PUSH_BC;
    // PUSH_AF;
    // LD_A_addr(wNamingScreenType);
    // SUB_A(NAME_BOX - 1);
    // LD_B_A;
    // POP_AF;
    // DEC_B;
    // POP_BC;
    // RET;
    return wram->wNamingScreenType == NAME_BOX;
}

void NamingScreen_InitText(void){
    // CALL(aWaitTop);
    WaitTop();
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(NAMINGSCREEN_BORDER);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, NAMINGSCREEN_BORDER);
    // hlcoord(1, 1, wTilemap);
    // LD_BC((6 << 8) | 18);
    // CALL(aNamingScreen_IsTargetBox);
    // IF_NZ goto not_box;
    // LD_BC((4 << 8) | 18);
    if(NamingScreen_IsTargetBox())
        ClearBox_Conv2(coord(1, 1, wram->wTilemap), 18, 4);
    else
        ClearBox_Conv2(coord(1, 1, wram->wTilemap), 18, 6);

// not_box:
    // CALL(aClearBox);
    // LD_DE(mNameInputUpper);
    return NamingScreen_ApplyTextInputMode(NameInputUpper);
}

void NamingScreen_ApplyTextInputMode(const char* de){
    // CALL(aNamingScreen_IsTargetBox);
    // IF_NZ goto not_box;
    if(NamingScreen_IsTargetBox()) {
        //assert ['BoxNameInputLower - NameInputLower == BoxNameInputUpper - NameInputUpper'];
        // LD_HL(mBoxNameInputLower - mNameInputLower);
        // ADD_HL_DE;
        // LD_D_H;
        // LD_E_L;
        de += (BoxNameInputLower - NameInputLower);
    }

// not_box:
    const uint8_t* de2 = U82C(de);
    // PUSH_DE;
    // hlcoord(1, 8, wTilemap);
    // LD_BC((7 << 8) | 18);
    // CALL(aNamingScreen_IsTargetBox);
    // IF_NZ goto not_box_2;
    // hlcoord(1, 6, wTilemap);
    // LD_BC((9 << 8) | 18);


// not_box_2:
    // CALL(aClearBox);
    if(NamingScreen_IsTargetBox())
        ClearBox_Conv2(coord(1, 6, wram->wTilemap), 18, 9);
    else
        ClearBox_Conv2(coord(1, 8, wram->wTilemap), 18, 7);
    // hlcoord(1, 16, wTilemap);
    // LD_BC((1 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 16, wram->wTilemap), 18, 1);
    // POP_DE;
    uint8_t* hl;
    uint8_t b;
    if(!NamingScreen_IsTargetBox()) {
        // hlcoord(2, 8, wTilemap);
        hl = coord(2, 8, wram->wTilemap);
        // LD_B(0x5);
        b = 0x5;
        // CALL(aNamingScreen_IsTargetBox);
        // IF_NZ goto row;
    }
    else {
        // hlcoord(2, 6, wTilemap);
        hl = coord(2, 6, wram->wTilemap);
        // LD_B(0x6);
        b = 0x6;
    }

    do {
    // row:
        // LD_C(0x11);
        uint8_t c = 0x11;

        do {
        // col:
            // LD_A_de;
            // LD_hli_A;
            // INC_DE;
            *(hl++) = *(de2++);
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // PUSH_DE;
        // LD_DE(2 * SCREEN_WIDTH - 0x11);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH - 0x11;
        // POP_DE;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

static void NamingScreenJoypadLoop_UpdateStringEntry(void);
static uint8_t NamingScreenJoypadLoop_GetCursorPosition(void);

static void NamingScreenJoypadLoop_Jumptable(void) {
    switch(wram->wJumptableIndex) {
    //dw ['.InitCursor'];
    case 0: {
    // InitCursor:
        // depixel2(10, 3);
        // CALL(aNamingScreen_IsTargetBox);
        // IF_NZ goto got_cursor_position;
        // LD_D(8 * 8);
        uint16_t px = (NamingScreen_IsTargetBox())? pixel2(8, 3): pixel2(10, 3);

    // got_cursor_position:
        // LD_A(SPRITE_ANIM_INDEX_NAMING_SCREEN_CURSOR);
        // CALL(aInitSpriteAnimStruct);
        struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_NAMING_SCREEN_CURSOR, px);
        // LD_A_C;
        // LD_addr_A(wNamingScreenCursorObjectPointer);
        // LD_A_B;
        // LD_addr_A(wNamingScreenCursorObjectPointer + 1);
        gNamingScreenCursorObjectPointer = bc;
        // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_HL(SPRITEANIMSTRUCT_VAR3);
        // ADD_HL_BC;
        // LD_hl_A;
        bc->var3 = bc->framesetID;
        // LD_HL(wJumptableIndex);
        // INC_hl;
        wram->wJumptableIndex++;
        // RET;
    } return;
    //dw ['.ReadButtons'];
    case 1: {
    // ReadButtons:
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        uint8_t pressed = hram->hJoyPressed;
        // AND_A(A_BUTTON);
        // IF_NZ goto a;
        if(pressed & A_BUTTON) {
        // a:
            // CALL(aNamingScreenJoypadLoop_GetCursorPosition);
            uint8_t a = NamingScreenJoypadLoop_GetCursorPosition();
            // CP_A(0x1);
            // IF_Z goto select;
            if(a == 0x1)
                goto select;
            // CP_A(0x2);
            // IF_Z goto b;
            if(a == 0x2)
                goto b;
            // CP_A(0x3);
            // IF_Z goto end;
            if(a == 0x3) {
            // end:
                // CALL(aNamingScreen_StoreEntry);
                NamingScreen_StoreEntry();
                // LD_HL(wJumptableIndex);
                // SET_hl(7);
                bit_set(wram->wJumptableIndex, 7);
                // RET;
                return;
            }
            // CALL(aNamingScreen_GetLastCharacter);
            NamingScreen_GetLastCharacter();
            // CALL(aNamingScreen_TryAddCharacter);
            // RET_NC ;
            if(!NamingScreen_TryAddCharacter())
                return;
            goto start;
        }
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto b;
        else if(pressed & B_BUTTON) {
        b:
            // CALL(aNamingScreen_DeleteCharacter);
            NamingScreen_DeleteCharacter();
            // RET;
            return;
        }
        // LD_A_hl;
        // AND_A(START);
        // IF_NZ goto start;
        else if(pressed & START) {
            struct SpriteAnim* bc;
        start:
            // LD_HL(wNamingScreenCursorObjectPointer);
            // LD_C_hl;
            // INC_HL;
            // LD_B_hl;
            bc = gNamingScreenCursorObjectPointer;
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl(0x8);
            bc->var1 = 0x8;
            // LD_HL(SPRITEANIMSTRUCT_VAR2);
            // ADD_HL_BC;
            // LD_hl(0x4);
            // CALL(aNamingScreen_IsTargetBox);
            // RET_NZ ;
            // INC_hl;
            bc->var2 = (NamingScreen_IsTargetBox())? 0x5: 0x4;
            // RET;
            return;
        }
        // LD_A_hl;
        // AND_A(SELECT);
        // IF_NZ goto select;
        else if(pressed & SELECT) {
        select:
            // LD_HL(wNamingScreenLetterCase);
            // LD_A_hl;
            // XOR_A(1);
            // LD_hl_A;
            wram->wNamingScreenLetterCase ^= 1;
            // IF_Z goto upper;
            if(wram->wNamingScreenLetterCase) {
                // LD_DE(mNameInputLower);
                // CALL(aNamingScreen_ApplyTextInputMode);
                NamingScreen_ApplyTextInputMode(NameInputLower);
                // RET;
                return;
            }
            else {
            // upper:
                // LD_DE(mNameInputUpper);
                // CALL(aNamingScreen_ApplyTextInputMode);
                NamingScreen_ApplyTextInputMode(NameInputUpper);
                // RET;
                return;
            }
        }
        // RET;
        return;
    } return;
    }
}

bool NamingScreenJoypadLoop(void){
    // CALL(aJoyTextDelay);
    JoyTextDelay_Conv();
    // LD_A_addr(wJumptableIndex);
    // BIT_A(7);
    // IF_NZ goto quit;
    if(!bit_test(wram->wJumptableIndex, 7)) {
        // CALL(aNamingScreenJoypadLoop_RunJumptable);
        NamingScreenJoypadLoop_Jumptable();
        // FARCALL(aPlaySpriteAnimationsAndDelayFrame);
        PlaySpriteAnimationsAndDelayFrame_Conv();
        // CALL(aNamingScreenJoypadLoop_UpdateStringEntry);
        NamingScreenJoypadLoop_UpdateStringEntry();
        // CALL(aDelayFrame);
        DelayFrame();
        // AND_A_A;
        // RET;
        return false;
    }

// quit:
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // SCF;
    // RET;
    return true;


// RunJumptable:
    //jumptable ['.Jumptable', 'wJumptableIndex']
}

static void NamingScreenJoypadLoop_UpdateStringEntry(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(1, 5, wTilemap);
    // CALL(aNamingScreen_IsTargetBox);
    // IF_NZ goto got_coords;
    // hlcoord(1, 3, wTilemap);
    uint8_t* hl = (NamingScreen_IsTargetBox())? coord(1, 3, wram->wTilemap): coord(1, 5, wram->wTilemap);

// got_coords:
    // LD_BC((1 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv2(hl, 18, 1);
    // LD_HL(wNamingScreenDestinationPointer);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // LD_HL(wNamingScreenStringEntryCoord);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aPlaceString);
    PlaceStringSimple(gNamingScreenDestinationPointer, gNamingScreenStringEntryCoord);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

static uint8_t NamingScreenJoypadLoop_GetCursorPosition(void){
    // LD_HL(wNamingScreenCursorObjectPointer);
    // LD_C_hl;
    // INC_HL;
    // LD_B_hl;
    struct SpriteAnim* bc = gNamingScreenCursorObjectPointer;

    return NamingScreen_GetCursorPosition(bc);
}

uint8_t NamingScreen_GetCursorPosition(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t var2 = bc->var2;
    // PUSH_BC;
    // LD_B(0x4);
    // CALL(aNamingScreen_IsTargetBox);
    // IF_NZ goto not_box;
    // INC_B;

// not_box:
    uint8_t b = (NamingScreen_IsTargetBox())? 0x5: 0x4;
    // CP_A_B;
    // POP_BC;
    // IF_NZ goto not_bottom_row;
    if(var2 != b)
        return 0x0;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x3);
    // IF_C goto case_switch;
    if(bc->var1 < 0x3)
        return 0x1;
    // CP_A(0x6);
    // IF_C goto delete;
    if(bc->var1 < 0x6)
        return 0x2;
    // LD_A(0x3);
    // RET;
    return 0x3;

// case_switch:
    // LD_A(0x1);
    // RET;

// delete:
    // LD_A(0x2);
    // RET;

// not_bottom_row:
    // XOR_A_A;
    // RET;
}

static void NamingScreen_AnimateCursor_GetDPad(struct SpriteAnim* bc){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    uint8_t joy = hram->hJoyLast;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(joy & D_UP) {
    // up:
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto wrap_down;
        if(bc->var2 == 0) {
        // wrap_down:
            // LD_hl(0x4);
            bc->var2 = 0x4;
            // CALL(aNamingScreen_IsTargetBox);
            // RET_NZ ;
            if(!NamingScreen_IsTargetBox())
                return;
            // INC_hl;
            bc->var2++;
            // RET;
            return;
        }
        // DEC_hl;
        bc->var2--;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(joy & D_DOWN) {
    // down:
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // CALL(aNamingScreen_IsTargetBox);
        // IF_NZ goto not_box;
        if(!NamingScreen_IsTargetBox()) {
        // not_box:
            // CP_A(0x4);
            // IF_NC goto wrap_up;
            if(bc->var2 >= 0x4) {
                bc->var2 = 0;
                return;
            }
            // INC_hl;
            bc->var2++;
            // RET;
            return;
        }
        // CP_A(0x5);
        // IF_NC goto wrap_up;
        else if(bc->var2 >= 0x5) {
        // wrap_up:
            // LD_hl(0x0);
            bc->var2 = 0x0;
            // RET;
            return;
        }
        // INC_hl;
        bc->var2++;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    else if(joy & D_LEFT) {
    // left:
        // CALL(aNamingScreen_GetCursorPosition);
        uint8_t pos = NamingScreen_GetCursorPosition(bc);
        // AND_A_A;
        // IF_NZ goto target_left;
        if(pos != 0) {
        // target_left:
            // CP_A(0x1);
            // IF_NZ goto no_wrap_target_right;
            // LD_A(0x4);

        // no_wrap_target_right:
            // DEC_A;
            // DEC_A;
            // LD_E_A;
            uint8_t e = ((pos != 0x1)? pos: 0x4) - 2;
            // ADD_A_A;
            // ADD_A_E;
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->var1 = (e << 1) + e;
            // RET;
            return;
        }
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto wrap_right;
        if(bc->var1 == 0) {
        // wrap_right:
            // LD_hl(0x8);
            bc->var1 = 0x8;
            // RET;
        }
        // DEC_hl;
        bc->var1--;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    else if(joy & D_RIGHT) {
    // right:
        // CALL(aNamingScreen_GetCursorPosition);
        uint8_t pos = NamingScreen_GetCursorPosition(bc);
        // AND_A_A;
        // IF_NZ goto target_right;
        if(pos != 0) {
        // target_right:
            // CP_A(0x3);
            // IF_NZ goto no_wrap_target_left;
            // XOR_A_A;

        // no_wrap_target_left:
            // LD_E_A;
            uint8_t e = (pos != 0x3)? pos: 0x0;
            // ADD_A_A;
            // ADD_A_E;
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->var1 = (e << 1) + e;
            // RET;
            return;
        }
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x8);
        // IF_NC goto wrap_left;
        else if(bc->var1 >= 0x8) {
        // wrap_left:
            // LD_hl(0x0);
            bc->var1 = 0x0;
            // RET;
            return;
        }
        // INC_hl;
        bc->var1++;
        // RET;
        return;
    }
    // RET;
    return;
}

void NamingScreen_AnimateCursor_Conv(struct SpriteAnim* bc){
    static const uint8_t LetterEntries[] = {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
    static const uint8_t CaseDelEnd[] = {0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x60, 0x60, 0x60};
    // CALL(aNamingScreen_AnimateCursor_GetDPad);
    NamingScreen_AnimateCursor_GetDPad(bc);
    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_E_A;
    uint8_t e = bc->var2;
    // SWAP_E;
    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->yOffset = (e << 4) | (e >> 4);
    // LD_D(0x4);
    // CALL(aNamingScreen_IsTargetBox);
    // IF_NZ goto ok;
    // INC_D;
    uint8_t d = (NamingScreen_IsTargetBox())? 0x5: 0x4;

// ok:
    // CP_A_D;
    // LD_DE(mNamingScreen_AnimateCursor_LetterEntries);
    // LD_A(SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR - SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR);  // 0
    // IF_NZ goto ok2;
    // LD_DE(mNamingScreen_AnimateCursor_CaseDelEnd);
    // LD_A(SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR_BIG - SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR);  // 1
    uint8_t a = (e != d)? SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR - SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR
                        : SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR_BIG - SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR;
    const uint8_t* de = (e != d)? LetterEntries: CaseDelEnd;

// ok2:
    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // ADD_A_hl;  // default SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR
    // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->framesetID = bc->var3 + a;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_L_hl;
    // LD_H(0x0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = de[bc->var1];
    // RET;
}

void NamingScreen_AnimateCursor(void){
    CALL(aNamingScreen_AnimateCursor_GetDPad);
    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    LD_E_A;
    SWAP_E;
    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_E;
    LD_D(0x4);
    CALL(aNamingScreen_IsTargetBox);
    IF_NZ goto ok;
    INC_D;

ok:
    CP_A_D;
    LD_DE(mNamingScreen_AnimateCursor_LetterEntries);
    LD_A(SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR - SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR);  // 0
    IF_NZ goto ok2;
    LD_DE(mNamingScreen_AnimateCursor_CaseDelEnd);
    LD_A(SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR_BIG - SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR);  // 1

ok2:
    LD_HL(SPRITEANIMSTRUCT_VAR3);
    ADD_HL_BC;
    ADD_A_hl;  // default SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR
    LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0x0);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;


LetterEntries:
    //db ['0x00', '0x10', '0x20', '0x30', '0x40', '0x50', '0x60', '0x70', '0x80'];


CaseDelEnd:
    //db ['0x00', '0x00', '0x00', '0x30', '0x30', '0x30', '0x60', '0x60', '0x60'];


GetDPad:
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto up;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto down;
    LD_A_hl;
    AND_A(D_LEFT);
    IF_NZ goto left;
    LD_A_hl;
    AND_A(D_RIGHT);
    IF_NZ goto right;
    RET;


right:
    CALL(aNamingScreen_GetCursorPosition);
    AND_A_A;
    IF_NZ goto target_right;
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x8);
    IF_NC goto wrap_left;
    INC_hl;
    RET;


wrap_left:
    LD_hl(0x0);
    RET;


target_right:
    CP_A(0x3);
    IF_NZ goto no_wrap_target_left;
    XOR_A_A;

no_wrap_target_left:
    LD_E_A;
    ADD_A_A;
    ADD_A_E;
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    RET;


left:
    CALL(aNamingScreen_GetCursorPosition);
    AND_A_A;
    IF_NZ goto target_left;
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto wrap_right;
    DEC_hl;
    RET;


wrap_right:
    LD_hl(0x8);
    RET;


target_left:
    CP_A(0x1);
    IF_NZ goto no_wrap_target_right;
    LD_A(0x4);

no_wrap_target_right:
    DEC_A;
    DEC_A;
    LD_E_A;
    ADD_A_A;
    ADD_A_E;
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    RET;


down:
    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aNamingScreen_IsTargetBox);
    IF_NZ goto not_box;
    CP_A(0x5);
    IF_NC goto wrap_up;
    INC_hl;
    RET;


not_box:
    CP_A(0x4);
    IF_NC goto wrap_up;
    INC_hl;
    RET;


wrap_up:
    LD_hl(0x0);
    RET;


up:
    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto wrap_down;
    DEC_hl;
    RET;


wrap_down:
    LD_hl(0x4);
    CALL(aNamingScreen_IsTargetBox);
    RET_NZ ;
    INC_hl;
    RET;

}

bool NamingScreen_TryAddCharacter(void){
    // LD_A_addr(wNamingScreenLastCharacter);  // lost
    return MailComposition_TryAddCharacter();
}

bool MailComposition_TryAddCharacter(void){
    // LD_A_addr(wNamingScreenMaxNameLength);
    // LD_C_A;
    // LD_A_addr(wNamingScreenCurNameLength);
    // CP_A_C;
    // RET_NC ;
    if(wram->wNamingScreenCurNameLength >= wram->wNamingScreenMaxNameLength)
        return false;

    // LD_A_addr(wNamingScreenLastCharacter);

    return NamingScreen_LoadNextCharacter(wram->wNamingScreenLastCharacter);
}

bool NamingScreen_LoadNextCharacter(uint8_t a){
    // CALL(aNamingScreen_GetTextCursorPosition);
    // LD_hl_A;
    *NamingScreen_GetTextCursorPosition() = a;

    return NamingScreen_AdvanceCursor_CheckEndOfString();
}

bool NamingScreen_AdvanceCursor_CheckEndOfString(void){
    // LD_HL(wNamingScreenCurNameLength);
    // INC_hl;
    wram->wNamingScreenCurNameLength++;
    // CALL(aNamingScreen_GetTextCursorPosition);
    // LD_A_hl;
    uint8_t* hl = NamingScreen_GetTextCursorPosition();
    // CP_A(0x50);
    // IF_Z goto end_of_string;
    if(*hl != 0x50) {
        // LD_hl(NAMINGSCREEN_UNDERLINE);
        *hl = NAMINGSCREEN_UNDERLINE;
        // AND_A_A;
        // RET;
        return false;
    }

// end_of_string:
    // SCF;
    // RET;
    return true;
}

void AddDakutenToCharacter(void){
//  //  unreferenced
    LD_A_addr(wNamingScreenCurNameLength);
    AND_A_A;
    RET_Z ;
    PUSH_HL;
    LD_HL(wNamingScreenCurNameLength);
    DEC_hl;
    CALL(aNamingScreen_GetTextCursorPosition);
    LD_C_hl;
    POP_HL;


loop:
    LD_A_hli;
    CP_A(-1);
    JR_Z (mNamingScreen_AdvanceCursor_CheckEndOfString);
    CP_A_C;
    IF_Z goto done;
    INC_HL;
    goto loop;


done:
    LD_A_hl;
    JR(mNamingScreen_LoadNextCharacter);

// INCLUDE "data/text/unused_dakutens.asm"
}

void NamingScreen_DeleteCharacter(void){
    // LD_HL(wNamingScreenCurNameLength);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(wram->wNamingScreenCurNameLength == 0)
        return;
    // DEC_hl;
    --wram->wNamingScreenCurNameLength;
    // CALL(aNamingScreen_GetTextCursorPosition);
    uint8_t* hl = NamingScreen_GetTextCursorPosition();
    // LD_hl(NAMINGSCREEN_UNDERLINE);
    *hl = NAMINGSCREEN_UNDERLINE;
    // INC_HL;
    // LD_A_hl;
    // CP_A(NAMINGSCREEN_UNDERLINE);
    // RET_NZ ;
    if(hl[1] != NAMINGSCREEN_UNDERLINE)
        return;
    // LD_hl(NAMINGSCREEN_MIDDLELINE);
    // RET;
    hl[1] = NAMINGSCREEN_MIDDLELINE;
}

uint8_t* NamingScreen_GetTextCursorPosition(void){
    // PUSH_AF;
    // LD_HL(wNamingScreenDestinationPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wNamingScreenCurNameLength);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // POP_AF;
    // RET;
    return gNamingScreenDestinationPointer + wram->wNamingScreenCurNameLength;
}

//  load NAMINGSCREEN_UNDERLINE, (NAMINGSCREEN_MIDDLELINE * [wNamingScreenMaxNameLength]), "@" into the dw address at wNamingScreenDestinationPointer
void NamingScreen_InitNameEntry(void){
    // LD_HL(wNamingScreenDestinationPointer);
    uint8_t* hl = gNamingScreenDestinationPointer;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_hl(NAMINGSCREEN_UNDERLINE);
    *hl = NAMINGSCREEN_UNDERLINE;
    // INC_HL;
    hl++;
    // LD_A_addr(wNamingScreenMaxNameLength);
    // DEC_A;
    // LD_C_A;
    // LD_A(NAMINGSCREEN_MIDDLELINE);
    uint8_t c = wram->wNamingScreenMaxNameLength - 1;
    do {
    // loop:
        // LD_hli_A;
        *(hl++) = NAMINGSCREEN_MIDDLELINE;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_hl(0x50);
    *hl = 0x50;
    // RET;
}

void NamingScreen_StoreEntry(void){
    // LD_HL(wNamingScreenDestinationPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = gNamingScreenDestinationPointer;
    // LD_A_addr(wNamingScreenMaxNameLength);
    // LD_C_A;
    uint8_t c = wram->wNamingScreenMaxNameLength;

    do {
    // loop:
        // LD_A_hl;
        uint8_t a = *hl;
        // CP_A(NAMINGSCREEN_MIDDLELINE);
        // IF_Z goto terminator;
        // CP_A(NAMINGSCREEN_UNDERLINE);
        // IF_NZ goto not_terminator;
        if(a == NAMINGSCREEN_MIDDLELINE || a == NAMINGSCREEN_UNDERLINE) {
        // terminator:
            // LD_hl(0x50);
            *hl = 0x50;
        }

    // not_terminator:
        // INC_HL;
        hl++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void NamingScreen_GetLastCharacter(void){
    // LD_HL(wNamingScreenCursorObjectPointer);
    // LD_C_hl;
    // INC_HL;
    // LD_B_hl;
    struct SpriteAnim* bc = gNamingScreenCursorObjectPointer;
    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // ADD_A_hl;
    // SUB_A(0x8);
    // SRL_A;
    // SRL_A;
    // SRL_A;
    // LD_E_A;
    uint8_t e = ((bc->xOffset + bc->xCoord) - 0x8) >> 3;
    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // ADD_A_hl;
    // SUB_A(0x10);
    // SRL_A;
    // SRL_A;
    // SRL_A;
    // LD_D_A;
    uint8_t d = ((bc->yOffset + bc->yCoord) - 0x10) >> 3;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH);

// loop:
    // LD_A_D;
    // AND_A_A;
    // IF_Z goto done;
    // ADD_HL_BC;
    // DEC_D;
    // goto loop;

// done:
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wNamingScreenLastCharacter);
    wram->wNamingScreenLastCharacter = *coord(e, d, wram->wTilemap);
    // RET;
}

void LoadNamingScreenGFX(void){
    // CALL(aClearSprites);
    ClearSprites();
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();

    // LD_DE(mNamingScreenGFX_MiddleLine);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * NAMINGSCREEN_MIDDLELINE);
    // LD_BC((BANK(aNamingScreenGFX_MiddleLine) << 8) | 1);
    // CALL(aGet1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * NAMINGSCREEN_MIDDLELINE, NamingScreenGFX_MiddleLine, 0, 1);

    // LD_DE(mNamingScreenGFX_UnderLine);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * NAMINGSCREEN_UNDERLINE);
    // LD_BC((BANK(aNamingScreenGFX_UnderLine) << 8) | 1);
    // CALL(aGet1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * NAMINGSCREEN_UNDERLINE, NamingScreenGFX_UnderLine, 0, 1);

    // LD_DE(vTiles2 + LEN_2BPP_TILE * NAMINGSCREEN_BORDER);
    // LD_HL(mNamingScreenGFX_Border);
    // LD_BC(1 * LEN_2BPP_TILE);
    // LD_A(BANK(aNamingScreenGFX_Border));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * NAMINGSCREEN_BORDER, NamingScreenGFX_Border, 0, 1);

    // LD_DE(vTiles0 + LEN_2BPP_TILE * NAMINGSCREEN_CURSOR);
    // LD_HL(mNamingScreenGFX_Cursor);
    // LD_BC(2 * LEN_2BPP_TILE);
    // LD_A(BANK(aNamingScreenGFX_Cursor));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * NAMINGSCREEN_CURSOR, NamingScreenGFX_Cursor, 0, 2);

    // LD_A(SPRITE_ANIM_DICT_TEXT_CURSOR);
    // LD_HL(wSpriteAnimDict + (NUM_SPRITEANIMDICT_ENTRIES - 1) * 2);
    uint8_t* hl = wram->wSpriteAnimDict + (NUM_SPRITEANIMDICT_ENTRIES - 1) * 2;
    // LD_hli_A;
    hl[0] = SPRITE_ANIM_DICT_TEXT_CURSOR;
    // LD_hl(NAMINGSCREEN_CURSOR);
    hl[1] = NAMINGSCREEN_CURSOR;
    // XOR_A_A;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // LD_addr_A(wGlobalAnimYOffset);
    wram->wGlobalAnimYOffset = 0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LD_addr_A(wGlobalAnimXOffset);
    wram->wGlobalAnimXOffset = 0;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // LD_addr_A(wNamingScreenLetterCase);
    wram->wNamingScreenLetterCase = 0;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_addr_A(wNamingScreenCurNameLength);
    wram->wNamingScreenCurNameLength = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // RET;
}

const char NamingScreenGFX_Border[] = "gfx/naming_screen/border.png";

const char NamingScreenGFX_Cursor[] = "gfx/naming_screen/cursor.png";

// INCLUDE "data/text/name_input_chars.asm"


void NamingScreenGFX_End(void){
//  //  unreferenced
// INCBIN "gfx/naming_screen/end.1bpp"
}

const char NamingScreenGFX_MiddleLine[] = "gfx/naming_screen/middle_line.png";

const char NamingScreenGFX_UnderLine[] = "gfx/naming_screen/underline.png";

static void v_ComposeMailMessage_PlaceMailCharset(uint8_t* de){
    // hlcoord(1, 7, wTilemap);
    tile_t* hl = coord(1, 7, wram->wTilemap);
    // LD_B(6);
    uint8_t b = 6;

    do {
    // next:
        // LD_C(SCREEN_WIDTH - 1);
        uint8_t c = SCREEN_WIDTH - 1;

        do {
        // loop_:
            // LD_A_de;
            // LD_hli_A;
            *(hl++) = *(de++);
            // INC_DE;
            // DEC_C;
            // IF_NZ goto loop_;
        } while(--c != 0);
        // PUSH_DE;
        // LD_DE(SCREEN_WIDTH + 1);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH + 1;
        // POP_DE;
        // DEC_B;
        // IF_NZ goto next;
    } while(--b != 0);
    // RET;
}

static void v_ComposeMailMessage_InitCharset(void){
    // CALL(aWaitTop);
    WaitTop();
    // hlcoord(0, 0, wTilemap);
    // LD_BC(6 * SCREEN_WIDTH);
    // LD_A(NAMINGSCREEN_BORDER);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), 6 * SCREEN_WIDTH, NAMINGSCREEN_BORDER);
    // hlcoord(0, 6, wTilemap);
    // LD_BC(12 * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 6, wram->wTilemap), 12 * SCREEN_WIDTH, 0x7f);
    // hlcoord(1, 1, wTilemap);
    // LD_BC((4 << 8) | (SCREEN_WIDTH - 2));
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 1, wram->wTilemap), SCREEN_WIDTH - 2, 4);
    // LD_DE(mMailEntry_Uppercase);
    return v_ComposeMailMessage_PlaceMailCharset(U82C(MailEntry_Uppercase));
}

static void v_ComposeMailMessage_InitBlankMail(void) {
    static const char MailIcon[] = "gfx/icons/mail_big.png";
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aLoadNamingScreenGFX);
    LoadNamingScreenGFX();
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // LD_HL(mv_ComposeMailMessage_MailIcon);
    // LD_BC(8 * LEN_2BPP_TILE);
    // LD_A(BANK(av_ComposeMailMessage_MailIcon));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, MailIcon, 0, 8);
    // XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT and tile offset $00
    // LD_HL(wSpriteAnimDict);
    // LD_hli_A;
    wram->wSpriteAnimDict[0] = SPRITE_ANIM_DICT_DEFAULT;
    // LD_hl_A;
    wram->wSpriteAnimDict[1] = 0;

// init mail icon
    // depixel2(3, 2);
    // LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_PARTY_MON, pixel2(3, 2));

    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->animSeqID = 0x0;
    // CALL(av_ComposeMailMessage_InitCharset);
    v_ComposeMailMessage_InitCharset();
    // LD_A(LCDC_DEFAULT);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, LCDC_DEFAULT);
    // CALL(av_ComposeMailMessage_initwNamingScreenMaxNameLength);
    {
    // initwNamingScreenMaxNameLength:
        // LD_A(MAIL_MSG_LENGTH + 1);
        // LD_addr_A(wNamingScreenMaxNameLength);
        wram->wNamingScreenMaxNameLength = MAIL_MSG_LENGTH + 1;
        // RET;
    }
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aWaitTop);
    WaitTop();
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // LD_A(0b11100100);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0_Conv(0b11100100);
    // CALL(aNamingScreen_InitNameEntry);
    NamingScreen_InitNameEntry();
    // LD_HL(wNamingScreenDestinationPointer);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // LD_HL(MAIL_LINE_LENGTH);
    // ADD_HL_DE;
    // LD_hl(0x4e);
    gNamingScreenDestinationPointer[MAIL_LINE_LENGTH] = 0x4e;
    // RET;

// PleaseWriteAMailString:
//   //  unreferenced
    //db ['"メールを\u3000かいてね@"'];
}

static void v_ComposeMailMessage_Update(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(1, 1, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 1, wram->wTilemap), 18, 4);
    // LD_HL(wNamingScreenDestinationPointer);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // hlcoord(2, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(gNamingScreenDestinationPointer, coord(2, 2, wram->wTilemap));
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

static void v_ComposeMailMessage_DoJumptable(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']

    switch(wram->wJumptableIndex) {
    // Jumptable:
        //dw ['.init_blinking_cursor'];
        case 0: {
        // init_blinking_cursor:
            // depixel2(9, 2);
            // LD_A(SPRITE_ANIM_INDEX_COMPOSE_MAIL_CURSOR);
            // CALL(aInitSpriteAnimStruct);
            struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_COMPOSE_MAIL_CURSOR, pixel2(9, 2));
            // LD_A_C;
            // LD_addr_A(wNamingScreenCursorObjectPointer);
            // LD_A_B;
            // LD_addr_A(wNamingScreenCursorObjectPointer + 1);
            gNamingScreenCursorObjectPointer = bc;
            // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_HL(SPRITEANIMSTRUCT_VAR3);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->var3 = bc->framesetID;
            // LD_HL(wJumptableIndex);
            // INC_hl;
            wram->wJumptableIndex++;
            // RET;
        } return;
        //dw ['.process_joypad'];
        case 1:
        // process_joypad:
            // LD_HL(hJoyPressed);
            // LD_A_hl;
            // AND_A(A_BUTTON);
            // IF_NZ goto a;
            if(hram->hJoyPressed & A_BUTTON) {
            // a:
                // CALL(aNamingScreen_PressedA_GetCursorCommand);
                uint8_t a = NamingScreen_PressedA_GetCursorCommand();
                // CP_A(0x1);
                // IF_Z goto select;
                if(a == 0x1) goto select;
                // CP_A(0x2);
                // IF_Z goto b;
                if(a == 0x2) goto b;
                // CP_A(0x3);
                // IF_Z goto finished;
                if(a == 0x3) break;
                // CALL(aNamingScreen_GetLastCharacter);
                NamingScreen_GetLastCharacter();
                // CALL(aMailComposition_TryAddLastCharacter);
                // IF_C goto start;
                if(MailComposition_TryAddLastCharacter())
                    goto start;
                // LD_HL(wNamingScreenCurNameLength);
                // LD_A_hl;
                // CP_A(MAIL_LINE_LENGTH);
                // RET_NZ ;
                if(wram->wNamingScreenCurNameLength != MAIL_LINE_LENGTH)
                    return;
                // INC_hl;
                wram->wNamingScreenCurNameLength++;
                // CALL(aNamingScreen_GetTextCursorPosition);
                uint8_t* hl = NamingScreen_GetTextCursorPosition();
                // LD_hl(NAMINGSCREEN_UNDERLINE);
                hl[0] = NAMINGSCREEN_UNDERLINE;
                // DEC_HL;
                // LD_hl(0x4e);
                hl[1] = 0x4e;
                // RET;
                return;
            }
            // LD_A_hl;
            // AND_A(B_BUTTON);
            // IF_NZ goto b;
            else if(hram->hJoyPressed & B_BUTTON) {
            b:
                // CALL(aNamingScreen_DeleteCharacter);
                NamingScreen_DeleteCharacter();
                // LD_HL(wNamingScreenCurNameLength);
                // LD_A_hl;
                // CP_A(MAIL_LINE_LENGTH);
                // RET_NZ ;
                if(wram->wNamingScreenCurNameLength != MAIL_LINE_LENGTH)
                    return;
                // DEC_hl;
                wram->wNamingScreenCurNameLength--;
                // CALL(aNamingScreen_GetTextCursorPosition);
                uint8_t* hl = NamingScreen_GetTextCursorPosition();
                // LD_hl(NAMINGSCREEN_UNDERLINE);
                hl[0] = NAMINGSCREEN_UNDERLINE;
                // INC_HL;
                // LD_hl(0x4e);
                hl[1] = 0x4e;
                // RET;
                return;
            }
            // LD_A_hl;
            // AND_A(START);
            // IF_NZ goto start;
            else if(hram->hJoyPressed & START) {
            start:
                // LD_HL(wNamingScreenCursorObjectPointer);
                // LD_C_hl;
                // INC_HL;
                // LD_B_hl;
                struct SpriteAnim* bc = gNamingScreenCursorObjectPointer;
                // LD_HL(SPRITEANIMSTRUCT_VAR1);
                // ADD_HL_BC;
                // LD_hl(0x9);
                bc->var1 = 0x9;
                // LD_HL(SPRITEANIMSTRUCT_VAR2);
                // ADD_HL_BC;
                // LD_hl(0x5);
                bc->var2 = 0x5;
                // RET;
                return;
            }
            // LD_A_hl;
            // AND_A(SELECT);
            // IF_NZ goto select;
            else if(hram->hJoyPressed & SELECT) {
            select:
                // LD_HL(wNamingScreenLetterCase);
                // LD_A_hl;
                // XOR_A(1);
                // LD_hl_A;
                wram->wNamingScreenLetterCase ^= 1;
                // IF_NZ goto switch_to_lowercase;
                if(wram->wNamingScreenLetterCase == 0) {
                    // LD_DE(mMailEntry_Uppercase);
                    // CALL(av_ComposeMailMessage_PlaceMailCharset);
                    v_ComposeMailMessage_PlaceMailCharset(U82C(MailEntry_Uppercase));
                    // RET;
                    return;
                }
                else {
                // switch_to_lowercase:
                    // LD_DE(mMailEntry_Lowercase);
                    // CALL(av_ComposeMailMessage_PlaceMailCharset);
                    v_ComposeMailMessage_PlaceMailCharset(U82C(MailEntry_Lowercase));
                    // RET;
                    return;
                }
            }
            // RET;
            return;
    }

// finished:
    // CALL(aNamingScreen_StoreEntry);
    NamingScreen_StoreEntry();
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

static bool v_ComposeMailMessage_DoMailEntry(void){
    // CALL(aJoyTextDelay);
    JoyTextDelay_Conv();
    // LD_A_addr(wJumptableIndex);
    // BIT_A(7);
    // IF_NZ goto exit_mail;
    if(!bit_test(wram->wJumptableIndex, 7)){
        // CALL(av_ComposeMailMessage_DoJumptable);
        v_ComposeMailMessage_DoJumptable();
        // FARCALL(aPlaySpriteAnimationsAndDelayFrame);
        PlaySpriteAnimationsAndDelayFrame_Conv();
        // CALL(av_ComposeMailMessage_Update);
        v_ComposeMailMessage_Update();
        // CALL(aDelayFrame);
        DelayFrame();
        // AND_A_A;
        // RET;
        return false;
    }

// exit_mail:
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0x0;
    // SCF;
    // RET;
    return true;
}

void v_ComposeMailMessage(uint8_t* dest){
    // LD_HL(wNamingScreenDestinationPointer);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gNamingScreenDestinationPointer = dest;
    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    uint8_t mapAnims = hram->hMapAnims;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0x0;
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // CALL(av_ComposeMailMessage_InitBlankMail);
    v_ComposeMailMessage_InitBlankMail();
    // CALL(aDelayFrame);
    DelayFrame();

    do {
    // loop:
        // CALL(av_ComposeMailMessage_DoMailEntry);
        // IF_NC goto loop;
    } while(!v_ComposeMailMessage_DoMailEntry());

    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = mapAnims;
    // RET;
    return;

//  called from engine/gfx/sprite_anims.asm
}

static void ComposeMail_AnimateCursor_GetDPad(struct SpriteAnim* bc){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(hram->hJoyLast & D_UP) {
    // up:
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto wrap_around_up;
        if(bc->var2 == 0) {
        // wrap_around_up:
            // LD_hl(0x5);
            bc->var2 = 0x5;
            // RET;
            return;
        }
        // DEC_hl;
        bc->var2--;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x5);
        // IF_NC goto wrap_around_down;
        if(bc->var2 >= 0x5) {
        // wrap_around_down:
            // LD_hl(0x0);
            bc->var2 = 0x0;
            // RET;
            return;
        }
        // INC_hl;
        bc->var2++;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    else if(hram->hJoyLast & D_LEFT){
    // left:
        // CALL(aComposeMail_GetCursorPosition);
        uint8_t pos = ComposeMail_GetCursorPosition(bc);
        // AND_A_A;
        // IF_NZ goto caps_del_done_left;
        if(pos != 0) {
        // caps_del_done_left:
            // CP_A(0x1);
            // IF_NZ goto wrap_around_command_left;
            // LD_A(0x4);
            if(pos == 0x1)
                pos = 0x4;

        // wrap_around_command_left:
            // DEC_A;
            // DEC_A;
            pos -= 2;
            // LD_E_A;
            // ADD_A_A;
            // ADD_A_E;
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->var1 = (pos << 1) + pos;
            // RET;
            return;
        }
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto wrap_around_letter_left;
        if(bc->var1 == 0) {
        // wrap_around_letter_left:
            // LD_hl(0x9);
            bc->var1 = 0x9;
            // RET;
            return;
        }
        // DEC_hl;
        bc->var1--;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    else if(hram->hJoyLast & D_RIGHT){
    // right:
        // CALL(aComposeMail_GetCursorPosition);
        uint8_t pos = ComposeMail_GetCursorPosition(bc);
        // AND_A_A;
        // IF_NZ goto case_del_done_right;
        if(pos != 0) {
        // case_del_done_right:
            // CP_A(0x3);
            // IF_NZ goto wrap_around_command_right;
            // XOR_A_A;
            if(pos == 0x3)
                pos = 0x0;

        // wrap_around_command_right:
            // LD_E_A;
            // ADD_A_A;
            // ADD_A_E;
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->var1 = (pos << 1) + pos;
            // RET;
            return;
        }
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x9);
        // IF_NC goto wrap_around_letter_right;
        if(bc->var1 >= 0x9){
        // wrap_around_letter_right:
            // LD_hl(0x0);
            bc->var1 = 0x0;
            // RET;
            return;
        }
        // INC_hl;
        bc->var1++;
        // RET;
        return;
    }
    // RET;
}

void ComposeMail_AnimateCursor(struct SpriteAnim* bc){
static const uint8_t LetterEntries[] = {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90};
static const uint8_t CaseDelEnd[] = {0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x60, 0x60, 0x60, 0x60};
    // CALL(aComposeMail_AnimateCursor_GetDPad);
    ComposeMail_AnimateCursor_GetDPad(bc);
    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_E_A;
    // SWAP_E;
    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->yOffset = (bc->var2 << 4) | (bc->var2 >> 4);
    // CP_A(0x5);
    uint8_t a;
    const uint8_t* de;
    if(bc->var2 != 0x5) {
        // LD_DE(mComposeMail_AnimateCursor_LetterEntries);
        de = LetterEntries;
        // LD_A(0);
        a = 0;
        // IF_NZ goto got_pointer;
    }
    else {
        // LD_DE(mComposeMail_AnimateCursor_CaseDelEnd);
        de = CaseDelEnd;
        // LD_A(1);
        a = 1;
    }

// got_pointer:
    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // ADD_A_hl;
    // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->framesetID = bc->var3 + a;
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_L_hl;
    // LD_H(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = de[bc->var1];
    // RET;

}

uint8_t NamingScreen_PressedA_GetCursorCommand(void){
    // LD_HL(wNamingScreenCursorObjectPointer);
    // LD_C_hl;
    // INC_HL;
    // LD_B_hl;

    return ComposeMail_GetCursorPosition(gNamingScreenCursorObjectPointer);
}

uint8_t ComposeMail_GetCursorPosition(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x5);
    // IF_NZ goto letter;
    if(bc->var2 != 0x5) {
    // letter:
        // XOR_A_A;
        // RET;
        return 0x0;
    }
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(0x3);
    // IF_C goto case_;
    else if(bc->var1 < 0x3) {
    // case_:
        // LD_A(0x1);
        // RET;
        return 0x1;
    }
    // CP_A(0x6);
    // IF_C goto del;
    else if(bc->var1 < 0x6) {
    // del:
        // LD_A(0x2);
        // RET;
        return 0x2;
    }
    else {
        // LD_A(0x3);
        // RET;
        return 0x3;
    }
}

bool MailComposition_TryAddLastCharacter(void){
    // LD_A_addr(wNamingScreenLastCharacter);
    // JP(mMailComposition_TryAddCharacter);
    return MailComposition_TryAddCharacter();


// add_dakuten:
//   //  unreferenced
    // LD_A_addr(wNamingScreenCurNameLength);
    // AND_A_A;
    // RET_Z ;
    // CP_A(0x11);
    // IF_NZ goto one_back;
    // PUSH_HL;
    // LD_HL(wNamingScreenCurNameLength);
    // DEC_hl;
    // DEC_hl;
    // goto continue_;


// one_back:
    // PUSH_HL;
    // LD_HL(wNamingScreenCurNameLength);
    // DEC_hl;


// continue_:
    // CALL(aNamingScreen_GetTextCursorPosition);
    // LD_C_hl;
    // POP_HL;

// loop:
    // LD_A_hli;
    // CP_A(-1);  // end?
    // JP_Z (mNamingScreen_AdvanceCursor_CheckEndOfString);
    // CP_A_C;
    // IF_Z goto done;
    // INC_HL;
    // goto loop;


// done:
    // LD_A_hl;
    // JP(mNamingScreen_LoadNextCharacter);

// INCLUDE "data/text/mail_input_chars.asm"

}
