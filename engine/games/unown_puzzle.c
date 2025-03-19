#include "../../constants.h"
#include "unown_puzzle.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/text.h"
#include "../../home/palettes.h"
#include "../../home/joypad.h"
#include "../../home/audio.h"
#include "../../home/sram.h"
#include "../../home/random.h"

#define PUZZLE_BORDER (0xee)
#define PUZZLE_VOID (0xef)

#define puzcoord * 6 +

void v_UnownPuzzle(void){
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aDisableLCD);
    // LD_HL(STARTOF("Miscellaneous"));  // includes wPuzzlePieces
    // LD_BC(SIZEOF("Miscellaneous"));
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wSurroundingTiles, sizeof(wram->wSurroundingTiles), 0);
    // LD_HL(mUnownPuzzleCursorGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0xe0);
    // LD_BC(4 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0xe0, UnownPuzzleCursorGFX, 0, 4);
    // LD_HL(mUnownPuzzleStartCancelLZ);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0xed);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0xed, UnownPuzzleStartCancelLZ);
    // CALL(aLoadUnownPuzzlePiecesGFX);
    LoadUnownPuzzlePiecesGFX();
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(PUZZLE_BORDER);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, PUZZLE_BORDER);
    // hlcoord(4, 3, wTilemap);
    // LD_BC((12 << 8) | 12);
    // LD_A(PUZZLE_VOID);
    // CALL(aUnownPuzzle_FillBox);
    UnownPuzzle_FillBox(coord(4, 3, wram->wTilemap), 12, 12, PUZZLE_VOID);
    // CALL(aInitUnownPuzzlePiecePositions);
    InitUnownPuzzlePiecePositions();
    // CALL(aUnownPuzzle_UpdateTilemap);
    UnownPuzzle_UpdateTilemap();
    // CALL(aPlaceStartCancelBox);
    PlaceStartCancelBox();
    // XOR_A_A;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LDH_addr_A(rWY);
    gb_write(rWY, 0);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // LD_addr_A(wHoldingUnownPuzzlePiece);
    wram->wHoldingUnownPuzzlePiece = FALSE;
    // LD_addr_A(wUnownPuzzleCursorPosition);
    wram->wUnownPuzzleCursorPosition = 0;
    // LD_addr_A(wUnownPuzzleHeldPiece);
    wram->wUnownPuzzleHeldPiece = 0;
    // LD_A(0b10010011);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, 0b10010011);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_UNOWN_PUZZLE);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_UNOWN_PUZZLE);
    // LD_A(0xe4);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0xe4);
    // LD_A(0x24);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0_Conv(0x24);
    // XOR_A_A;
    // LD_addr_A(wSolvedUnownPuzzle);
    wram->wSolvedUnownPuzzle = FALSE;
    // CALL(aDelayFrame);
    DelayFrame();

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto quit;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aUnownPuzzleJumptable);
        UnownPuzzleJumptable();
        // LD_A_addr(wHoldingUnownPuzzlePiece);
        // AND_A_A;
        // IF_NZ goto holding_piece;
        // LDH_A_addr(hVBlankCounter);
        // AND_A(0x10);
        // IF_Z goto clear;
        if(wram->wHoldingUnownPuzzlePiece != 0 || (hram->hVBlankCounter & 0x10)) {
        // holding_piece:
            // CALL(aRedrawUnownPuzzlePieces);
            RedrawUnownPuzzlePieces();
            // goto next;
        }
        else {
        // clear:
            // CALL(aClearSprites);
            ClearSprites();
        }

    // next:
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// quit:
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites();
    // LD_A(LCDC_DEFAULT);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, LCDC_DEFAULT);
    // RET;
}

void InitUnownPuzzlePiecePositions(void){
    static const uint8_t PuzzlePieceInitialPositions[] = {
    // initpuzcoord: MACRO
    // rept _NARG / 2
    //     db \1 puzcoord \2
    //     shift 2
    // endr
    // ENDM
        0 puzcoord 0, 0 puzcoord 1, 0 puzcoord 2, 0 puzcoord 3, 0 puzcoord 4, 0 puzcoord 5,
        1 puzcoord 0, 1 puzcoord 5,
        2 puzcoord 0, 2 puzcoord 5,
        3 puzcoord 0, 3 puzcoord 5,
        4 puzcoord 0, 4 puzcoord 5,
        5 puzcoord 0, 5 puzcoord 5,
    // ['?']  // START > CANCEL
    };
    // LD_C(1);
    uint8_t c = 1;
    // LD_B(16);
    uint8_t b = 16;

    do {
        uint8_t e;
        do {
        // load_loop:
            // CALL(aRandom);
            // AND_A(0xf);
            // LD_HL(mInitUnownPuzzlePiecePositions_PuzzlePieceInitialPositions);
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // LD_E_hl;
            e = PuzzlePieceInitialPositions[Random() & 0xf];
            // LD_HL(wPuzzlePieces);
            // ADD_HL_DE;
            // LD_A_hl;
            // AND_A_A;
            // IF_NZ goto load_loop;
        } while(wram->wPuzzlePieces[e] != 0);
        // LD_hl_C;
        wram->wPuzzlePieces[e] = c;
        // INC_C;
        c++;
        // DEC_B;
        // IF_NZ goto load_loop;
    } while(--b != 0);
    // RET;
}

void PlaceStartCancelBox(void){
    // CALL(aPlaceStartCancelBoxBorder);
    PlaceStartCancelBoxBorder();
    // hlcoord(5, 16, wTilemap);
    tile_t* hl = coord(5, 16, wram->wTilemap);
    // LD_A(0xf6);
    uint8_t a = 0xf6;
    // LD_C(10);
    uint8_t c = 10;

    do {
    // loop:
        // LD_hli_A;
        // INC_A;
        *(hl++) = a++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void PlaceStartCancelBoxBorder(void){
    // hlcoord(4, 15, wTilemap);
    tile_t* hl = coord(4, 15, wram->wTilemap);
    // LD_A(0xf0);
    // LD_hli_A;
    *(hl++) = 0xf0;
    // LD_BC(10);
    // LD_A(0xf1);
    // CALL(aByteFill);
    ByteFill(hl, 10, 0xf1);
    // hlcoord(15, 15, wTilemap);
    // LD_A(0xf2);
    // LD_hli_A;
    *coord(15, 15, wram->wTilemap) = 0xf2;
    // hlcoord(4, 16, wTilemap);
    hl = coord(4, 16, wram->wTilemap);
    // LD_A(0xf3);
    // LD_hli_A;
    *(hl++) = 0xf3;
    // LD_BC(10);
    // LD_A(PUZZLE_VOID);
    // CALL(aByteFill);
    ByteFill(hl, 10, PUZZLE_VOID);
    // hlcoord(15, 16, wTilemap);
    // LD_A(0xf3);
    // LD_hli_A;
    *coord(15, 16, wram->wTilemap) = 0xf3;
    // hlcoord(4, 17, wTilemap);
    hl = coord(4, 17, wram->wTilemap);
    // LD_A(0xf4);
    // LD_hli_A;
    *(hl++) = 0xf4;
    // LD_BC(10);
    // LD_A(0xf1);
    // CALL(aByteFill);
    ByteFill(hl, 10, 0xf1);
    // hlcoord(15, 17, wTilemap);
    // LD_A(0xf5);
    // LD_hl_A;
    *coord(15, 17, wram->wTilemap) = 0xf5;
    // RET;
}

static void UnownPuzzleJumptable_Function(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A(START);
    // JP_NZ (mUnownPuzzle_Quit);
    if(hram->hJoyPressed & START)
        return UnownPuzzle_Quit();
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON);
    // JP_NZ (mUnownPuzzle_A);
    if(hram->hJoyPressed & A_BUTTON)
        return UnownPuzzle_A();
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto d_up;
    if(hram->hJoyLast & D_UP) {
    // d_up:
        // LD_HL(wUnownPuzzleCursorPosition);
        // LD_A_hl;
        // CP_A(1 puzcoord 0);
        // RET_C ;
        if(wram->wUnownPuzzleCursorPosition < 1 puzcoord 0)
            return;
        // SUB_A(6);
        // LD_hl_A;
        wram->wUnownPuzzleCursorPosition -= 6;
        // goto done_joypad;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto d_down;
    else if(hram->hJoyLast & D_DOWN) {
    // d_down:
        // LD_HL(wUnownPuzzleCursorPosition);
        // LD_A_hl;
        uint8_t pos = wram->wUnownPuzzleCursorPosition;
        // CP_A(4 puzcoord 1);
        // RET_Z ;
        // CP_A(4 puzcoord 2);
        // RET_Z ;
        // CP_A(4 puzcoord 3);
        // RET_Z ;
        // CP_A(4 puzcoord 4);
        // RET_Z ;
        // CP_A(5 puzcoord 0);
        // RET_NC ;
        if(pos == 4 puzcoord 1
        || pos == 4 puzcoord 2
        || pos == 4 puzcoord 3
        || pos == 4 puzcoord 4
        || pos >= 5 puzcoord 0)
            return;
        // ADD_A(6);
        // LD_hl_A;
        wram->wUnownPuzzleCursorPosition = pos + 6;
        // goto done_joypad;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto d_left;
    else if(hram->hJoyLast & D_LEFT) {
    // d_left:
        // LD_HL(wUnownPuzzleCursorPosition);
        // LD_A_hl;
        uint8_t pos = wram->wUnownPuzzleCursorPosition;
        // AND_A_A;
        // RET_Z ;
        if(pos == 0)
            return;
        // CP_A(1 puzcoord 0);
        // RET_Z ;
        // CP_A(2 puzcoord 0);
        // RET_Z ;
        // CP_A(3 puzcoord 0);
        // RET_Z ;
        // CP_A(4 puzcoord 0);
        // RET_Z ;
        // CP_A(5 puzcoord 0);
        // RET_Z ;
        if(pos == 1 puzcoord 0
        || pos == 2 puzcoord 0
        || pos == 3 puzcoord 0
        || pos == 4 puzcoord 0
        || pos == 5 puzcoord 0)
            return;
        // CP_A(5 puzcoord 5);
        // IF_Z goto left_overflow;
        if(pos == 5 puzcoord 5) {
        // left_overflow:
            // LD_hl(5 puzcoord 0);
            wram->wUnownPuzzleCursorPosition = 5 puzcoord 0;
            // goto done_joypad;
        }
        else {
            // DEC_hl;
            wram->wUnownPuzzleCursorPosition--;
            // goto done_joypad;
        }
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto d_right;
    else if(hram->hJoyLast & D_RIGHT) {
    // d_right:
        // LD_HL(wUnownPuzzleCursorPosition);
        // LD_A_hl;
        uint8_t pos = wram->wUnownPuzzleCursorPosition;
        // CP_A(0 puzcoord 5);
        // RET_Z ;
        // CP_A(1 puzcoord 5);
        // RET_Z ;
        // CP_A(2 puzcoord 5);
        // RET_Z ;
        // CP_A(3 puzcoord 5);
        // RET_Z ;
        // CP_A(4 puzcoord 5);
        // RET_Z ;
        // CP_A(5 puzcoord 5);
        // RET_Z ;
        if(pos == 0 puzcoord 5
        || pos == 1 puzcoord 5
        || pos == 2 puzcoord 5
        || pos == 3 puzcoord 5
        || pos == 4 puzcoord 5
        || pos == 5 puzcoord 5)
            return;
        // CP_A(5 puzcoord 0);
        // IF_Z goto right_overflow;
        if(pos == 5 puzcoord 0) {
        // right_overflow:
            // LD_hl(5 puzcoord 5);
            wram->wUnownPuzzleCursorPosition = 5 puzcoord 5;
        }
        else {
            // INC_hl;
            wram->wUnownPuzzleCursorPosition++;
        }
        // goto done_joypad;
    }
    else {
        // RET;
        return;
    }

// done_joypad:
    // LD_A_addr(wHoldingUnownPuzzlePiece);
    // AND_A_A;
    // IF_NZ goto holding_piece;
    // LD_DE(SFX_POUND);
    // goto play_sfx;

// holding_piece:
    // LD_DE(SFX_MOVE_PUZZLE_PIECE);

// play_sfx:
    uint16_t sfx = (wram->wHoldingUnownPuzzlePiece)? SFX_MOVE_PUZZLE_PIECE: SFX_POUND;
    // CALL(aPlaySFX);
    PlaySFX(sfx);
    // RET;
}

void UnownPuzzleJumptable(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']
    switch(wram->wJumptableIndex) {
        default: UnownPuzzleJumptable_Function(); break;
    }

// Jumptable:
//   //  redundant one-entry jumptable
    //dw ['.Function'];

}

void UnownPuzzle_A(void){
    // LD_A_addr(wHoldingUnownPuzzlePiece);
    // AND_A_A;
    // IF_NZ goto TryPlacePiece;
    if(wram->wHoldingUnownPuzzlePiece == 0) {
        // CALL(aUnownPuzzle_CheckCurrentTileOccupancy);
        uint8_t* hl = UnownPuzzle_CheckCurrentTileOccupancy();
        // AND_A_A;
        uint8_t piece = *hl;
        // JR_Z (mUnownPuzzle_InvalidAction);
        if(piece == 0)
            return UnownPuzzle_InvalidAction();
        // LD_DE(SFX_MEGA_KICK);
        // CALL(aPlaySFX);
        PlaySFX(SFX_MEGA_KICK);
        // LD_hl(0);
        *hl = 0;
        // LD_addr_A(wUnownPuzzleHeldPiece);
        wram->wUnownPuzzleHeldPiece = piece;
        // CALL(aRedrawUnownPuzzlePieces);
        RedrawUnownPuzzlePieces();
        // CALL(aFillUnoccupiedPuzzleSpace);
        FillUnoccupiedPuzzleSpace();
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_A(TRUE);
        // LD_addr_A(wHoldingUnownPuzzlePiece);
        wram->wHoldingUnownPuzzlePiece = TRUE;
        // RET;
        return;
    }

// TryPlacePiece:
    // CALL(aUnownPuzzle_CheckCurrentTileOccupancy);
    uint8_t* hl = UnownPuzzle_CheckCurrentTileOccupancy();
    // AND_A_A;
    uint8_t piece = *hl;
    // JR_NZ (mUnownPuzzle_InvalidAction);
    if(piece != 0)
        return UnownPuzzle_InvalidAction();
    // LD_DE(SFX_PLACE_PUZZLE_PIECE_DOWN);
    // CALL(aPlaySFX);
    PlaySFX(SFX_PLACE_PUZZLE_PIECE_DOWN);
    // LD_A_addr(wUnownPuzzleHeldPiece);
    // LD_hl_A;
    *hl = wram->wUnownPuzzleHeldPiece;
    // CALL(aPlaceUnownPuzzlePieceGFX);
    PlaceUnownPuzzlePieceGFX();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // XOR_A_A;
    // LD_addr_A(wUnownPuzzleHeldPiece);
    wram->wUnownPuzzleHeldPiece = 0;
    // CALL(aRedrawUnownPuzzlePieces);
    RedrawUnownPuzzlePieces();
    // XOR_A_A;
    // LD_addr_A(wHoldingUnownPuzzlePiece);
    wram->wHoldingUnownPuzzlePiece = FALSE;
    // CALL(aWaitSFX);
    WaitSFX();
    // CALL(aCheckSolvedUnownPuzzle);
    // RET_NC ;
    if(!CheckSolvedUnownPuzzle())
        return;

//  You solved the puzzle!
    // CALL(aPlaceStartCancelBoxBorder);
    PlaceStartCancelBoxBorder();
    // CALL(aClearSprites);
    ClearSprites();
    // LD_DE(SFX_1ST_PLACE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_1ST_PLACE);
    // CALL(aWaitSFX);
    WaitSFX();
    // CALL(aSimpleWaitPressAorB);
    SimpleWaitPressAorB_Conv();
    // LD_A(TRUE);
    // LD_addr_A(wSolvedUnownPuzzle);
    wram->wSolvedUnownPuzzle = TRUE;
    return UnownPuzzle_Quit();
}

void UnownPuzzle_Quit(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    // RET;
    bit_set(wram->wJumptableIndex, 7);
}

void UnownPuzzle_InvalidAction(void){
    // LD_DE(SFX_WRONG);
    // CALL(aPlaySFX);
    PlaySFX(SFX_WRONG);
    // CALL(aWaitSFX);
    WaitSFX();
    // RET;
}

void UnownPuzzle_FillBox(tile_t* hl, uint8_t b, uint8_t c, tile_t a){
    // LD_DE(SCREEN_WIDTH);

    do {
    // row:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // col:
            // LD_hli_A;
            *(hl2++) = a;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c2 != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void UnownPuzzle_UpdateTilemap(void){
    // XOR_A_A;
    // LD_addr_A(wUnownPuzzleCursorPosition);
    wram->wUnownPuzzleCursorPosition = 0;
    // LD_C(6 * 6);
    uint8_t c = 6 * 6;

    do {
    // loop:
        // PUSH_BC;
        // CALL(aUnownPuzzle_CheckCurrentTileOccupancy);
        uint8_t* tile = UnownPuzzle_CheckCurrentTileOccupancy();
        // LD_addr_A(wUnownPuzzleHeldPiece);
        wram->wUnownPuzzleHeldPiece = *tile;
        // AND_A_A;
        // IF_Z goto not_holding_piece;
        if(*tile != 0) {
            // CALL(aPlaceUnownPuzzlePieceGFX);
            PlaceUnownPuzzlePieceGFX();
            // goto next;
        }
        else {
        // not_holding_piece:
            // CALL(aFillUnoccupiedPuzzleSpace);
            FillUnoccupiedPuzzleSpace();
        }

    // next:
        // LD_HL(wUnownPuzzleCursorPosition);
        // INC_hl;
        wram->wUnownPuzzleCursorPosition++;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void PlaceUnownPuzzlePieceGFX(void){
    // LD_A(0x2);  // tilemap coords
    // CALL(aGetUnownPuzzleCoordData);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    tile_t* hl = wram->wTilemap + *(const uint16_t*)GetUnownPuzzleCoordData(0x2);
    // PUSH_HL;
    // CALL(aGetCurrentPuzzlePieceVTileCorner);
    uint8_t a = GetCurrentPuzzlePieceVTileCorner();
    // POP_HL;
    // LD_DE(SCREEN_WIDTH);
    // LD_B(3);
    uint8_t b = 3;

    do {
    // row:
        // LD_C(3);
        uint8_t c = 3;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // col:
            // LD_hli_A;
            // INC_A;
            *(hl2++) = a++;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // ADD_A(9);
        a += 9;
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void FillUnoccupiedPuzzleSpace(void){
    // LD_A(2);  // tilemap coords
    // CALL(aGetUnownPuzzleCoordData);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // PUSH_HL;
    uint8_t* hl = wram->wTilemap + *(const uint16_t*)GetUnownPuzzleCoordData(2);
    // LD_A(4);  // tile
    // CALL(aGetUnownPuzzleCoordData);
    // LD_A_hl;
    // POP_HL;
    uint8_t a = *GetUnownPuzzleCoordData(4);
    // LD_DE(SCREEN_WIDTH);
    // LD_B(3);
    uint8_t b = 3;

    do {
    // row:
        // LD_C(3);
        uint8_t c = 3;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // col:
            // LD_hli_A;
            *(hl2++) = a;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

const uint8_t* GetUnownPuzzleCoordData(uint8_t a){
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mUnownPuzzleCoordData);
    // ADD_HL_DE;
    switch(a) {
        default:
        case 0: return (const uint8_t*)&UnownPuzzleCoordData[wram->wUnownPuzzleCursorPosition].oamCoord;
        case 2: return (const uint8_t*)&UnownPuzzleCoordData[wram->wUnownPuzzleCursorPosition].coord;
        case 4: return &UnownPuzzleCoordData[wram->wUnownPuzzleCursorPosition].vacantTile;
        case 5: return &UnownPuzzleCoordData[wram->wUnownPuzzleCursorPosition].filler;
        // LD_A_addr(wUnownPuzzleCursorPosition);
        // LD_E_A;
        // for(int rept = 0; rept < 6; rept++){
        // ADD_HL_DE;
        // }
        // RET;
    }
}

uint8_t* UnownPuzzle_CheckCurrentTileOccupancy(void){
    // LD_HL(wPuzzlePieces);
    // LD_A_addr(wUnownPuzzleCursorPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    return wram->wPuzzlePieces + wram->wUnownPuzzleCursorPosition;
    // RET;

}

uint8_t GetCurrentPuzzlePieceVTileCorner(void){
    static const uint8_t Corners[] = {
    //  00, 01, 02
    //  0c, 0d, 0e
    //  18, 19, 1a
        0xe0,  // no piece selected
        0x00, 0x03, 0x06, 0x09,
        0x24, 0x27, 0x2a, 0x2d,
        0x48, 0x4b, 0x4e, 0x51,
        0x6c, 0x6f, 0x72, 0x75,
    };
    // LD_A_addr(wUnownPuzzleHeldPiece);
    uint8_t a = wram->wUnownPuzzleHeldPiece;
    // LD_HL(mGetCurrentPuzzlePieceVTileCorner_Corners);
    // ADD_A_L;
    // LD_L_A;
    // LD_A(0x0);
    // ADC_A_H;
    // LD_H_A;
    // LD_A_hl;
    return Corners[a];
    // RET;
}

bool CheckSolvedUnownPuzzle(void){
    static const uint8_t SolvedPuzzleConfiguration[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x02, 0x03, 0x04, 0x00,
        0x00, 0x05, 0x06, 0x07, 0x08, 0x00,
        0x00, 0x09, 0x0a, 0x0b, 0x0c, 0x00,
        0x00, 0x0d, 0x0e, 0x0f, 0x10, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    // LD_HL(mCheckSolvedUnownPuzzle_SolvedPuzzleConfiguration);
    const uint8_t* hl = SolvedPuzzleConfiguration;
    // LD_DE(wPuzzlePieces);
    const uint8_t* de = wram->wPuzzlePieces;
    // LD_C(6 * 6);

    for(uint8_t c = 0; c < 6 * 6; ++c) {
    // loop:
        // LD_A_de;
        // CP_A_hl;
        // IF_NZ goto not_solved;
        if(de[c] != hl[c])
            return false;
        // INC_DE;
        // INC_HL;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // SCF;
    // RET;
    return true;

// not_solved:
    // AND_A_A;
    // RET;
}

void RedrawUnownPuzzlePieces(void){
    static const uint8_t OAM_HoldingPiece[] = {
        dbsprite(-1, -1, -4, -4, 0x00, 0),
        dbsprite( 0, -1, -4, -4, 0x01, 0),
        dbsprite( 0, -1,  4, -4, 0x02, 0),
        dbsprite(-1,  0, -4, -4, 0x0c, 0),
        dbsprite( 0,  0, -4, -4, 0x0d, 0),
        dbsprite( 0,  0,  4, -4, 0x0e, 0),
        dbsprite(-1,  0, -4,  4, 0x18, 0),
        dbsprite( 0,  0, -4,  4, 0x19, 0),
        dbsprite( 0,  0,  4,  4, 0x1a, 0),
        (uint8_t)-1,
    };
    static const uint8_t OAM_NotHoldingPiece[] = {
        dbsprite(-1, -1, -4, -4, 0x00, 0),
        dbsprite( 0, -1, -4, -4, 0x01, 0),
        dbsprite( 0, -1,  4, -4, 0x00, 0 | X_FLIP),
        dbsprite(-1,  0, -4, -4, 0x02, 0),
        dbsprite( 0,  0, -4, -4, 0x03, 0),
        dbsprite( 0,  0,  4, -4, 0x02, 0 | X_FLIP),
        dbsprite(-1,  0, -4,  4, 0x00, 0 | Y_FLIP),
        dbsprite( 0,  0, -4,  4, 0x01, 0 | Y_FLIP),
        dbsprite( 0,  0,  4,  4, 0x00, 0 | X_FLIP | Y_FLIP),
        (uint8_t)-1,
    };
    // CALL(aGetCurrentPuzzlePieceVTileCorner);
    // LD_addr_A(wUnownPuzzleCornerTile);
    wram->wUnownPuzzleCornerTile = GetCurrentPuzzlePieceVTileCorner();
    // XOR_A_A;
    // CALL(aGetUnownPuzzleCoordData);  // get pixel positions
    uint16_t oamCoord = *(const uint16_t*)GetUnownPuzzleCoordData(0);
    // LD_A_hli;
    // LD_B_hl;
    // LD_C_A;
    // LD_A_addr(wUnownPuzzleCornerTile);
    // CP_A(0xe0);
    // IF_Z goto NoPiece;
    // LD_HL(mRedrawUnownPuzzlePieces_OAM_HoldingPiece);
    // goto load;

// NoPiece:
    // LD_HL(mRedrawUnownPuzzlePieces_OAM_NotHoldingPiece);
    const uint8_t* hl = (wram->wUnownPuzzleCornerTile == 0xe0)
        ? OAM_NotHoldingPiece
        : OAM_HoldingPiece; 

// load:
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;

    while(1) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        uint8_t a = *(hl++);
        // RET_Z ;
        if(a == (uint8_t)-1)
            return;
        // ADD_A_B;
        // LD_de_A;  // y
        de->yCoord = a + LOW(oamCoord);
        // INC_DE;
        // LD_A_hli;
        a = *(hl++);
        // ADD_A_C;
        // LD_de_A;  // x
        de->xCoord = a + HIGH(oamCoord);
        // INC_DE;
        // LD_A_addr(wUnownPuzzleCornerTile);
        // ADD_A_hl;
        a = *hl;
        // LD_de_A;  // tile id
        de->tileID = a + wram->wUnownPuzzleCornerTile;
        // INC_HL;
        hl++;
        // INC_DE;
        // LD_A_hli;
        a = *(hl++);
        // LD_de_A;  // attributes
        de->attributes = a;
        // INC_DE;
        de++;
        // goto loop;
    }
}

#define puzzle_coords(_ox1, _oy1, _ox2, _oy2, _tx, _ty, _v, _f) \
    {pixel4(_ox1, _oy1, _ox2, _oy2), coord(_tx, _ty, 0), _v, _f}
const struct PuzzleCoord UnownPuzzleCoordData[] = {
// puzzle_coords: MACRO
//     dbpixel \1, \2, \3, \4
//     dwcoord \5, \6
//     db \7, \8
// ENDM
//  OAM coords, tilemap coords, vacant tile, filler
    puzzle_coords(3, 3, 4, 4, 1, 0, PUZZLE_BORDER, 0),
    puzzle_coords(6, 3, 4, 4, 4, 0, PUZZLE_BORDER, 0),
    puzzle_coords(9, 3, 4, 4, 7, 0, PUZZLE_BORDER, 0),
    puzzle_coords(12, 3, 4, 4, 10, 0, PUZZLE_BORDER, 0),
    puzzle_coords(15, 3, 4, 4, 13, 0, PUZZLE_BORDER, 0),
    puzzle_coords(18, 3, 4, 4, 16, 0, PUZZLE_BORDER, 0),

    puzzle_coords(3, 6, 4, 4, 1, 3, PUZZLE_BORDER, 0),
    puzzle_coords(6, 6, 4, 4, 4, 3, PUZZLE_VOID, 0),
    puzzle_coords(9, 6, 4, 4, 7, 3, PUZZLE_VOID, 0),
    puzzle_coords(12, 6, 4, 4, 10, 3, PUZZLE_VOID, 0),
    puzzle_coords(15, 6, 4, 4, 13, 3, PUZZLE_VOID, 0),
    puzzle_coords(18, 6, 4, 4, 16, 3, PUZZLE_BORDER, 0),

    puzzle_coords(3, 9, 4, 4, 1, 6, PUZZLE_BORDER, 0),
    puzzle_coords(6, 9, 4, 4, 4, 6, PUZZLE_VOID, 0),
    puzzle_coords(9, 9, 4, 4, 7, 6, PUZZLE_VOID, 0),
    puzzle_coords(12, 9, 4, 4, 10, 6, PUZZLE_VOID, 0),
    puzzle_coords(15, 9, 4, 4, 13, 6, PUZZLE_VOID, 0),
    puzzle_coords(18, 9, 4, 4, 16, 6, PUZZLE_BORDER, 0),

    puzzle_coords(3, 12, 4, 4, 1, 9, PUZZLE_BORDER, 0),
    puzzle_coords(6, 12, 4, 4, 4, 9, PUZZLE_VOID, 0),
    puzzle_coords(9, 12, 4, 4, 7, 9, PUZZLE_VOID, 0),
    puzzle_coords(12, 12, 4, 4, 10, 9, PUZZLE_VOID, 0),
    puzzle_coords(15, 12, 4, 4, 13, 9, PUZZLE_VOID, 0),
    puzzle_coords(18, 12, 4, 4, 16, 9, PUZZLE_BORDER, 0),

    puzzle_coords(3, 15, 4, 4, 1, 12, PUZZLE_BORDER, 0),
    puzzle_coords(6, 15, 4, 4, 4, 12, PUZZLE_VOID, 0),
    puzzle_coords(9, 15, 4, 4, 7, 12, PUZZLE_VOID, 0),
    puzzle_coords(12, 15, 4, 4, 10, 12, PUZZLE_VOID, 0),
    puzzle_coords(15, 15, 4, 4, 13, 12, PUZZLE_VOID, 0),
    puzzle_coords(18, 15, 4, 4, 16, 12, PUZZLE_BORDER, 0),

    puzzle_coords(3, 18, 4, 4, 1, 15, PUZZLE_BORDER, 0),
    puzzle_coords(6, 18, 4, 4, 4, 15, PUZZLE_BORDER, 0),
    puzzle_coords(9, 18, 4, 4, 7, 15, PUZZLE_BORDER, 0),
    puzzle_coords(12, 18, 4, 4, 10, 15, PUZZLE_BORDER, 0),
    puzzle_coords(15, 18, 4, 4, 13, 15, PUZZLE_BORDER, 0),
    puzzle_coords(18, 18, 4, 4, 16, 15, PUZZLE_BORDER, 0),
};

static uint8_t ConvertLoadedPuzzlePieces_GetEnlargedTile(uint8_t a) {
#define entry(x) ((x & 0b1000) * 0b11000) + ((x & 0b0100) * 0b1100) + ((x & 0b0010) * 0b110) + ((x & 0b0001) * 0b11)
    static const uint8_t EnlargedTiles[] = {
        entry( 0),entry( 1),entry( 2),entry( 3),
        entry( 4),entry( 5),entry( 6),entry( 7),
        entry( 8),entry( 9),entry(10),entry(11),
        entry(12),entry(13),entry(14),entry(15),
    };
#undef entry
    // PUSH_HL;
    // LD_HL(mConvertLoadedPuzzlePieces_EnlargedTiles);
    // ADD_A_L;
    // LD_L_A;
    // LD_A(0);
    // ADC_A_H;
    // LD_H_A;
    // LD_A_hl;
    // POP_HL;
    // RET;
    return EnlargedTiles[a];
}

static tile_t* ConvertLoadedPuzzlePieces_EnlargePuzzlePieceTiles(tile_t* de, const tile_t* hl) {
//  double size
    // LD_C(6);
    uint8_t c = 6;

    do {
    // loop1:
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_HL;
        const tile_t* hl2 = hl;
        // LD_C(4);
        uint8_t c2 = 4;

        do {
        // loop2:
            // PUSH_BC;
            // LD_A_hli;
            // AND_A(0xf0);
            // SWAP_A;
            tile_t a = *(hl2++);
            a = (a & 0xf0) >> 4;
            // CALL(aConvertLoadedPuzzlePieces_GetEnlargedTile);
            // LD_C_A;
            uint8_t c3 = ConvertLoadedPuzzlePieces_GetEnlargedTile(a);
            // LD_A_hli;
            // AND_A(0xf0);
            // SWAP_A;
            a = *(hl2++);
            a = (a & 0xf0) >> 4;
            // CALL(aConvertLoadedPuzzlePieces_GetEnlargedTile);
            // LD_B_A;
            uint8_t b3 = ConvertLoadedPuzzlePieces_GetEnlargedTile(a);
            // LD_A_C;
            // LD_de_A;
            *(de++) = c3;
            // INC_DE;
            // LD_A_B;
            // LD_de_A;
            *(de++) = b3;
            // INC_DE;
            // LD_A_C;
            // LD_de_A;
            *(de++) = c3;
            // INC_DE;
            // LD_A_B;
            // LD_de_A;
            *(de++) = b3;
            // INC_DE;
            // POP_BC;
            // DEC_C;
            // IF_NZ goto loop2;
        } while(--c2 != 0);
        // POP_HL;
        hl2 = hl;
        // LD_C(4);
        c2 = 4;

        do {
        // loop3:
            // PUSH_BC;
            // LD_A_hli;
            // AND_A(0xf);
            tile_t a = *(hl2++);
            a &= 0xf;
            // CALL(aConvertLoadedPuzzlePieces_GetEnlargedTile);
            // LD_C_A;
            uint8_t c3 = ConvertLoadedPuzzlePieces_GetEnlargedTile(a);
            // LD_A_hli;
            // AND_A(0xf);
            a = *(hl2++);
            a &= 0xf;
            // CALL(aConvertLoadedPuzzlePieces_GetEnlargedTile);
            // LD_B_A;
            uint8_t b3 = ConvertLoadedPuzzlePieces_GetEnlargedTile(a);
            // LD_A_C;
            // LD_de_A;
            *(de++) = c3;
            // INC_DE;
            // LD_A_B;
            // LD_de_A;
            *(de++) = b3;
            // INC_DE;
            // LD_A_C;
            // LD_de_A;
            *(de++) = c3;
            // INC_DE;
            // LD_A_B;
            // LD_de_A;
            *(de++) = b3;
            // INC_DE;
            // POP_BC;
            // DEC_C;
            // IF_NZ goto loop3;
        } while(--c2 != 0);
        // POP_HL;
        // LD_BC(1 * LEN_2BPP_TILE);
        // ADD_HL_BC;
        hl += 1 * LEN_2BPP_TILE;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop1;
    } while(--c != 0);
    // RET;
    return de;
}

void ConvertLoadedPuzzlePieces(void){
    // LD_HL(vTiles2);
    uint8_t* hl = vram->vTiles2;
    // LD_DE(vTiles0);
    uint8_t* de = vram->vTiles0;
    // LD_B(6);
    uint8_t b = 6;

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_HL;
        // CALL(aConvertLoadedPuzzlePieces_EnlargePuzzlePieceTiles);
        de = ConvertLoadedPuzzlePieces_EnlargePuzzlePieceTiles(de, hl);
        // POP_HL;
        // LD_BC(1 * LEN_2BPP_TILE / 2);
        // ADD_HL_BC;
        // CALL(aConvertLoadedPuzzlePieces_EnlargePuzzlePieceTiles);
        de = ConvertLoadedPuzzlePieces_EnlargePuzzlePieceTiles(de, hl + (1 * LEN_2BPP_TILE / 2));
        // POP_HL;
        // LD_BC(6 * LEN_2BPP_TILE);
        // ADD_HL_BC;
        hl += 6 * LEN_2BPP_TILE;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // CALL(aUnownPuzzle_AddPuzzlePieceBorders);
    UnownPuzzle_AddPuzzlePieceBorders();
    // RET;
}

static const struct {
    uint8_t stile;
    uint8_t dtile;
} PuzzlePieceBorderData[] = {
    //dw ['.TileBordersGFX + 0 * LEN_2BPP_TILE', 'vTiles0 + LEN_2BPP_TILE * 0x00'];
    //dw ['.TileBordersGFX + 1 * LEN_2BPP_TILE', 'vTiles0 + LEN_2BPP_TILE * 0x01'];
    //dw ['.TileBordersGFX + 2 * LEN_2BPP_TILE', 'vTiles0 + LEN_2BPP_TILE * 0x02'];
    //dw ['.TileBordersGFX + 3 * LEN_2BPP_TILE', 'vTiles0 + LEN_2BPP_TILE * 0x0c'];
    //dw ['.TileBordersGFX + 4 * LEN_2BPP_TILE', 'vTiles0 + LEN_2BPP_TILE * 0x0e'];
    //dw ['.TileBordersGFX + 5 * LEN_2BPP_TILE', 'vTiles0 + LEN_2BPP_TILE * 0x18'];
    //dw ['.TileBordersGFX + 6 * LEN_2BPP_TILE', 'vTiles0 + LEN_2BPP_TILE * 0x19'];
    //dw ['.TileBordersGFX + 7 * LEN_2BPP_TILE', 'vTiles0 + LEN_2BPP_TILE * 0x1a'];
    {0, 0x00},
    {1, 0x01},
    {2, 0x02},
    {3, 0x0c},
    {4, 0x0e},
    {5, 0x18},
    {6, 0x19},
    {7, 0x1a},
};
static const char TileBordersGFX[] = "gfx/unown_puzzle/tile_borders.png";

static void UnownPuzzle_AddPuzzlePieceBorders_LoadGFX(tile_t* hl, const tile_t* de){
    // LD_BC((4 << 8) | 4);
    uint8_t b = 4;

    do {
    // loop1:
        // PUSH_BC;
        uint8_t c = 4;

        do {
        // loop2:
            // PUSH_DE;
            const tile_t* de2 = de;
            // PUSH_HL;
            tile_t* hl2 = hl;

            // LD_B(1 * LEN_2BPP_TILE);
            uint8_t b2 = 1 * LEN_2BPP_TILE;

            do {
            // loop3:
                // LD_A_de;
                // OR_A_hl;
                tile_t a = *de2 | *hl2;
                // LD_hli_A;
                *(hl2++) = a;
                // INC_DE;
                de2++;
                // DEC_B;
                // IF_NZ goto loop3;
            } while(--b2 != 0);

            // POP_HL;
            // LD_DE(3 * LEN_2BPP_TILE);
            // ADD_HL_DE;
            hl += 3 * LEN_2BPP_TILE;
            // POP_DE;
            // DEC_C;
            // IF_NZ goto loop2;
        } while(--c != 0);

        // LD_BC(24 * LEN_2BPP_TILE);
        // ADD_HL_BC;
        hl += 24 * LEN_2BPP_TILE;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop1;
    } while(--b != 0);
    // RET;
}

void UnownPuzzle_AddPuzzlePieceBorders(void){
    // LD_HL(mPuzzlePieceBorderData);
    OpenSRAM_Conv(MBANK(asScratch));
    // LD_A(8);
    uint8_t* de = (uint8_t*)GBToRAMAddr(sScratch);
    LoadPNG2bppAssetToVRAM(de, TileBordersGFX);

    for(uint32_t i = 0; i < lengthof(PuzzlePieceBorderData); ++i) {
    // loop:
        // PUSH_AF;
        // PUSH_HL;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint8_t dtile = PuzzlePieceBorderData[i].dtile;
        uint8_t stile = PuzzlePieceBorderData[i].stile;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // CALL(aUnownPuzzle_AddPuzzlePieceBorders_LoadGFX);
        UnownPuzzle_AddPuzzlePieceBorders_LoadGFX(vram->vTiles0 + (dtile * LEN_2BPP_TILE),
            de + (stile * LEN_2BPP_TILE));
        // POP_HL;
        // for(int rept = 0; rept < 4; rept++){
        // INC_HL;
        // }
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    }
    CloseSRAM_Conv();
    // RET;
}

void LoadUnownPuzzlePiecesGFX(void){
    //  entries correspond to UNOWNPUZZLE_* constants
    static const char *LZPointers[] = {
        [UNOWNPUZZLE_KABUTO] = KabutoPuzzleLZ,
        [UNOWNPUZZLE_OMANYTE] = OmanytePuzzleLZ,
        [UNOWNPUZZLE_AERODACTYL] = AerodactylPuzzleLZ,
        [UNOWNPUZZLE_HO_OH] = HoOhPuzzleLZ,
    };
    // LD_A_addr(wScriptVar);
    // maskbits(NUM_UNOWN_PUZZLES, 0);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mLoadUnownPuzzlePiecesGFX_LZPointers);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const char* path = LZPointers[wram->wScriptVar];
    // LD_DE(vTiles2);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, path);
    // CALL(aConvertLoadedPuzzlePieces);
    ConvertLoadedPuzzlePieces();
    // RET;
}

const char UnownPuzzleCursorGFX[] = "gfx/unown_puzzle/cursor.png";
const char UnownPuzzleStartCancelLZ[] = "gfx/unown_puzzle/start_cancel.png";
const char HoOhPuzzleLZ[] = "gfx/unown_puzzle/hooh.png";
const char AerodactylPuzzleLZ[] = "gfx/unown_puzzle/aerodactyl.png";
const char KabutoPuzzleLZ[] = "gfx/unown_puzzle/kabuto.png";
const char OmanytePuzzleLZ[] = "gfx/unown_puzzle/omanyte.png";
