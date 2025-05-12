#include "../../constants.h"
#include "link.h"
#include "link_trade.h"
#include "time_capsule.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/joypad.h"
#include "../../home/tilemap.h"
#include "../../home/serial.h"
#include "../../home/time_palettes.h"
#include "../gfx/crystal_layouts.h"
#include "../gfx/sprites.h"
#include "../menus/menu.h"

const char LinkCommsBorderGFX[] = "gfx/trade/border_tiles.png";

void v__LoadTradeScreenBorderGFX(void){
    // LD_DE(mLinkCommsBorderGFX);
    // LD_HL(vTiles2);
    // LD_BC((BANK(aLinkCommsBorderGFX) << 8) | 70);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, LinkCommsBorderGFX, 0, 70);
    // RET;
}

void LoadMobileTradeBorderTilemap(void){
    // LD_HL(mMobileTradeBorderTilemap);
    // decoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, MobileTradeBorderTilemap);
    // RET;
}

void TestMobileTradeBorderTilemap(void){
//  //  unreferenced
//  Loads the mobile trade border graphics and tilemap,
//  with a placeholder SCGB_DIPLOMA layout, and exits
//  after pressing A or B. Possibly used for testing.
    CALL(aLoadStandardMenuHeader);
    CALL(aClearBGPalettes);
    CALL(aClearTilemap);
    CALL(aClearSprites);
    FARCALL(av__LoadTradeScreenBorderGFX);  // useless to farcall
    FARCALL(aLoadMobileTradeBorderTilemap);  // useless to farcall
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    CALL(aWaitBGMap);
    CALL(aJoyWaitAorB);
    CALL(aCall_ExitMenu);
    RET;

}

const char MobileTradeBorderTilemap[] = "gfx/trade/border_mobile.tilemap";
const char CableTradeBorderTopTilemap[] = "gfx/trade/border_cable_top.tilemap";
const char CableTradeBorderBottomTilemap[] = "gfx/trade/border_cable_bottom.tilemap";

static tile_t* v_LinkTextbox_PlaceRow(tile_t* hl, uint8_t c, uint8_t a) {
    // LD_D_C;

    do {
    // row_loop:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_D;
        // IF_NZ goto row_loop;
    } while(--c != 0);
    // RET;
    return hl;
}


static void v_LinkTextbox_PlaceBorder(tile_t* hl, uint8_t b, uint8_t c) {
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x30);
    // LD_hli_A;
    *(hl++) = 0x30;
    // INC_A;
    // CALL(av_LinkTextbox_PlaceRow);
    hl = v_LinkTextbox_PlaceRow(hl, c, 0x31);
    // INC_A;
    // LD_hl_A;
    *hl = 0x32;
    // POP_HL;
    // LD_DE(SCREEN_WIDTH);
    // ADD_HL_DE;
    hl = hl2 + SCREEN_WIDTH;

    do {
    // loop:
        // PUSH_HL;
        hl2 = hl;
        // LD_A(0x33);
        // LD_hli_A;
        *(hl++) = 0x33;
        // LD_A(0x7f);
        // CALL(av_LinkTextbox_PlaceRow);
        hl = v_LinkTextbox_PlaceRow(hl, c, 0x7f);
        // LD_hl(0x34);
        *hl = 0x34;
        // POP_HL;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        hl = hl2 + SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);

    // LD_A(0x35);
    // LD_hli_A;
    *(hl++) = 0x35;
    // LD_A(0x36);
    // CALL(av_LinkTextbox_PlaceRow);
    hl = v_LinkTextbox_PlaceRow(hl, c, 0x36);
    // LD_hl(0x37);
    *hl = 0x37;
    // RET;
}

void v_LinkTextbox(tile_t* de, uint8_t b, uint8_t c){
    // LD_H_D;
    // LD_L_E;
    // PUSH_BC;
    // PUSH_HL;
    // CALL(av_LinkTextbox_PlaceBorder);
    v_LinkTextbox_PlaceBorder(de, b, c);
    // POP_HL;
    // POP_BC;

    // LD_DE(wAttrmap - wTilemap);
    // ADD_HL_DE;
    de += (wAttrmap - wTilemap);
    // INC_B;
    // INC_B;
    b += 2;
    // INC_C;
    // INC_C;
    c += 2;
    // LD_A(PAL_BG_TEXT);

    do {
    // row:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        tile_t* hl = de;

        do {
        // col:
            // LD_hli_A;
            *(de++) = PAL_BG_TEXT;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // POP_HL;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        de = hl + SCREEN_WIDTH;
        // POP_BC;
        c = c2;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void InitTradeSpeciesList(void){
    static const char CancelString[] = "CANCEL@";
    // CALL(av_LoadTradeScreenBorderGFX);
    v_LoadTradeScreenBorderGFX();
    // CALL(aLoadCableTradeBorderTilemap);
    LoadCableTradeBorderTilemap();
    // FARCALL(aInitMG_Mobile_LinkTradePalMap);
    InitMG_Mobile_LinkTradePalMap();
    // FARCALL(aPlaceTradePartnerNamesAndParty);
    PlaceTradePartnerNamesAndParty();
    // hlcoord(10, 17, wTilemap);
    // LD_DE(mInitTradeSpeciesList_CancelString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(CancelString), coord(10, 17, wram->wTilemap));
    // RET;
}

void v_LoadTradeScreenBorderGFX(void){
    // CALL(av__LoadTradeScreenBorderGFX);
    // RET;
    //  This has no reason to exist
    return v__LoadTradeScreenBorderGFX();
}

void LinkComms_LoadPleaseWaitTextboxBorderGFX(void){
    // LD_DE(mLinkCommsBorderGFX + 0x30 * LEN_2BPP_TILE);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x76);
    // LD_BC((BANK(aLinkCommsBorderGFX) << 8) | 8);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x76, LinkCommsBorderGFX, 0x30, 8);
    // RET;
}

void LoadTradeRoomBGPals(void){
    // FARCALL(av_LoadTradeRoomBGPals);
    // RET;
    return v_LoadTradeRoomBGPals();
}

void LoadCableTradeBorderTilemap(void){
    // CALL(aLoadMobileTradeBorderTilemap);
    LoadMobileTradeBorderTilemap();
    // LD_HL(mCableTradeBorderTopTilemap);
    // decoord(0, 0, wTilemap);
    // LD_BC(2 * SCREEN_WIDTH);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wTilemap), 2 * SCREEN_WIDTH, CableTradeBorderTopTilemap);
    // LD_HL(mCableTradeBorderBottomTilemap);
    // decoord(0, 16, wTilemap);
    // LD_BC(2 * SCREEN_WIDTH);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 16, wram->wTilemap), 2 * SCREEN_WIDTH, CableTradeBorderBottomTilemap);
    // RET;
}

void LinkTextbox(tile_t* de, uint8_t b, uint8_t c){
    // CALL(av_LinkTextbox);
    // RET;
    return v_LinkTextbox(de, b, c);
}

static void PrintWaitingTextAndSyncAndExchangeNybble_PrintWaitingText(void) {
    static const char Waiting[] = "WAITING..!@";
    // hlcoord(4, 10, wTilemap);
    // LD_B(1);
    // LD_C(10);
    // PREDEF(pLinkTextboxAtHL);
    LinkTextboxAtHL(coord(4, 10, wram->wTilemap), 1, 10);
    // hlcoord(5, 11, wTilemap);
    // LD_DE(mPrintWaitingTextAndSyncAndExchangeNybble_Waiting);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Waiting), coord(5, 11, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // LD_C(50);
    // JP(mDelayFrames);
    DelayFrames(50);
}

void PrintWaitingTextAndSyncAndExchangeNybble(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aPrintWaitingTextAndSyncAndExchangeNybble_PrintWaitingText);
    PrintWaitingTextAndSyncAndExchangeNybble_PrintWaitingText();
    // FARCALL(aWaitLinkTransfer);
    WaitLinkTransfer();
    // CALL(aCall_ExitMenu);
    ExitMenu();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // RET;
}

static bool LinkTradeMenu_TryAnims(void);

static uint8_t LinkTradeMenu_GetJoypad(void){
    // PUSH_BC;
    // PUSH_AF;
    // LDH_A_addr(hJoyLast);
    // AND_A(D_PAD);
    // LD_B_A;
    // LDH_A_addr(hJoyPressed);
    // AND_A(BUTTONS);
    // OR_A_B;
    // LD_B_A;
    uint8_t b = (hram->hJoyLast & (D_PAD)) | (hram->hJoyPressed & (BUTTONS));
    // POP_AF;
    // LD_A_B;
    // POP_BC;
    // LD_D_A;
    // RET;
    return b;
}

static void LinkTradeMenu_UpdateBGMapAndOAM(void) {
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t oam = hram->hOAMUpdate;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x1;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = oam;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // RET;
}

static bool LinkTradeMenu_loop2(void) {
    do {
        // CALL(aUpdateTimeAndPals);
        UpdateTimeAndPals();
        // CALL(aLinkTradeMenu_TryAnims);
        // RET_C ;
        if(LinkTradeMenu_TryAnims())
            return true;
        // LD_A_addr(w2DMenuFlags1);
        // BIT_A(7);
        // IF_Z goto loop2;
    } while(!bit_test(wram->w2DMenuFlags1, 7));
    // AND_A_A;
    // RET;
    return false;
}

static void LinkTradeMenu_UpdateCursor(void) {
    // LD_HL(wCursorCurrentTile);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    tile_t* hl = wram->wTilemap + (wram->wCursorCurrentTile - 1);
    // LD_A_hl;
    // CP_A(0x1f);
    // IF_NZ goto not_currently_selected;
    if(*hl == 0x1f) {
        // LD_A_addr(wCursorOffCharacter);
        // LD_hl_A;
        *hl = wram->wCursorOffCharacter;
        // PUSH_HL;
        // PUSH_BC;
        // LD_BC(MON_NAME_LENGTH);
        // ADD_HL_BC;
        // LD_hl_A;
        hl[MON_NAME_LENGTH] = wram->wCursorOffCharacter;
        // POP_BC;
        // POP_HL;
    }

// not_currently_selected:
    // LD_A_addr(w2DMenuCursorInitY);
    // LD_B_A;
    // LD_A_addr(w2DMenuCursorInitX);
    // LD_C_A;
    // CALL(aCoord2Tile);
    hl = Coord2Tile(wram->w2DMenuCursorInitX, wram->w2DMenuCursorInitY);
    // LD_A_addr(w2DMenuCursorOffsets);
    // SWAP_A;
    // AND_A(0xf);
    // LD_C_A;
    uint8_t c = (wram->w2DMenuCursorOffsets >> 4) & 0xf;
    // LD_A_addr(wMenuCursorY);
    // LD_B_A;
    uint8_t b = wram->wMenuCursorY;
    // XOR_A_A;
    // DEC_B;
    // IF_Z goto skip;
    // loop3:
        // ADD_A_C;
        // DEC_B;
        // IF_NZ goto loop3;
    // }
    uint8_t a = c * (b - 1);

// skip:
    // LD_C(SCREEN_WIDTH);
    // CALL(aAddNTimes);
    hl += (a * SCREEN_WIDTH);
    // LD_A_addr(w2DMenuCursorOffsets);
    // AND_A(0xf);
    // LD_C_A;
    c = wram->w2DMenuCursorOffsets & 0xf;
    // LD_A_addr(wMenuCursorX);
    // LD_B_A;
    b = wram->wMenuCursorX;
    // XOR_A_A;
    // DEC_B;
    // IF_Z goto skip2;

// loop4:
    // ADD_A_C;
    // DEC_B;
    // IF_NZ goto loop4;
    a = c * (b - 1);

// skip2:
    // LD_C_A;
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t n = hl[a];
    // CP_A(0x1f);
    // IF_Z goto cursor_already_there;
    if(n != 0x1f) {
        // LD_addr_A(wCursorOffCharacter);
        wram->wCursorOffCharacter = n;
        // LD_hl(0x1f);
        hl[a] = 0x1f;
        // PUSH_HL;
        // PUSH_BC;
        // LD_BC(MON_NAME_LENGTH);
        // ADD_HL_BC;
        // LD_hl(0x1f);
        hl[a + MON_NAME_LENGTH] = 0x1f;
        // POP_BC;
        // POP_HL;
    }
// cursor_already_there:
    // LD_A_L;
    // LD_addr_A(wCursorCurrentTile);
    // LD_A_H;
    // LD_addr_A(wCursorCurrentTile + 1);
    wram->wCursorCurrentTile = ((hl + a) - wram->wTilemap) + 1;
    // RET;
    return;
}

static bool LinkTradeMenu_TryAnims(void) {
    // LD_A_addr(w2DMenuFlags1);
    // BIT_A(6);
    // IF_Z goto skip_anims;
    if(bit_test(wram->w2DMenuFlags1, 6)) {
        // FARCALL(aPlaySpriteAnimationsAndDelayFrame);
        bank_push(BANK(aPlaySpriteAnimationsAndDelayFrame));
        PlaySpriteAnimationsAndDelayFrame();
        bank_pop;
    }
// skip_anims:
    // CALL(aJoyTextDelay);
    JoyTextDelay();
    DelayFrame();
    // CALL(aLinkTradeMenu_GetJoypad);
    // AND_A_A;
    // RET_Z ;
    if(!LinkTradeMenu_GetJoypad())
        return false;
    // SCF;
    // RET;
    return true;
}

static void LinkTradeMenu_loop(void) {
    do {
        // CALL(aLinkTradeMenu_UpdateCursor);
        LinkTradeMenu_UpdateCursor();
        // CALL(aLinkTradeMenu_UpdateBGMapAndOAM);
        LinkTradeMenu_UpdateBGMapAndOAM();
        // CALL(aLinkTradeMenu_loop2);
        // IF_NC goto done;
        if(!LinkTradeMenu_loop2())
            break;
        // FARCALL(av_2DMenuInterpretJoypad);
        // IF_C goto done;
        if(v_2DMenuInterpretJoypad())
            break;
        // LD_A_addr(w2DMenuFlags1);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->w2DMenuFlags1, 7))
            break;
        // CALL(aLinkTradeMenu_GetJoypad);
        // LD_B_A;
        // LD_A_addr(wMenuJoypadFilter);
        // AND_A_B;
        // IF_Z goto loop;
    } while((wram->wMenuJoypadFilter & LinkTradeMenu_GetJoypad()) == 0);
    printf("CursorY = %d\n", (wram->wMenuCursorY));

// done:
    // RET;
    return;
}

static void LinkTradeMenu_MenuAction(void) {
    // LD_HL(w2DMenuFlags2);
    // RES_hl(7);
    bit_reset(wram->w2DMenuFlags2, 7);
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    uint8_t mapMode = hram->hBGMapMode;
    // CALL(aLinkTradeMenu_loop);
    LinkTradeMenu_loop();
    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = mapMode;
    // RET;
}

uint8_t LinkTradeMenu(void){
    // CALL(aLinkTradeMenu_MenuAction);
    LinkTradeMenu_MenuAction();
    // CALL(aLinkTradeMenu_GetJoypad);
    // RET;
    return LinkTradeMenu_GetJoypad();
}
