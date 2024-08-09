#include "../../constants.h"
#include "card_flip.h"
#include "../../home/audio.h"
#include "../../home/clear_sprites.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/gfx.h"
#include "../../home/joypad.h"
#include "../../home/lcd.h"
#include "../../home/menu.h"
#include "../../home/palettes.h"
#include "../../home/print_text.h"
#include "../../home/random.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../charmap.h"
#include "../../data/text/common.h"

#define CARDFLIP_LIGHT_OFF (0xef)  //  "♂"
#define CARDFLIP_LIGHT_ON (0xf5)  //  $

#define CARDFLIP_DECK_SIZE (wDeckEnd - wDeck)
    //assert ['wDiscardPileEnd - wDiscardPile == wDeckEnd - wDeck'];

void MemoryGameGFX(void){
//  Graphics for an unused Game Corner
//  game were meant to be here.

    // return UnusedCursor_InterpretJoypad_AnimateCursor();
}

void UnusedCursor_InterpretJoypad_AnimateCursor(void){
    // RET;
}

static void v_CardFlip_CardFlip(void);

void v_CardFlip(void){
    // LD_HL(wOptions);
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();

    // LD_HL(mCardFlipLZ01);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, CardFlipLZ01);
    // LD_HL(mCardFlipLZ02);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x3e);
    // CALL(aDecompress);
    LoadPNG2bppAssetSectionToVRAM_SkipEmptyTiles(vram->vTiles2 + LEN_2BPP_TILE * 0x3e, CardFlipLZ02, 0, 52);
    // LD_HL(mCardFlipLZ03);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, CardFlipLZ03);
    // LD_HL(mCardFlipOffButtonGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * CARDFLIP_LIGHT_OFF);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * CARDFLIP_LIGHT_OFF, CardFlipOffButtonGFX, 0, 1);
    // LD_HL(mCardFlipOnButtonGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * CARDFLIP_LIGHT_ON);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * CARDFLIP_LIGHT_ON, CardFlipOnButtonGFX, 0, 1);

    // CALL(aCardFlip_ShiftDigitsUpOnePixel);
    CardFlip_ShiftDigitsUpOnePixel();
    // CALL(aCardFlip_InitTilemap);
    CardFlip_InitTilemap();
    // CALL(aCardFlip_InitAttrPals);
    CardFlip_InitAttrPals();
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // LD_DE((0b11100100 << 8) | 0b11100100);
    // CALL(aDmgToCgbObjPals);
    DmgToCgbObjPals_Conv(0b11100100, 0b11100100);
    // CALL(aDelayFrame);
    DelayFrame();
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // LD_A(0x2);
    // LD_addr_A(wCardFlipCursorY);
    wram->wCardFlipCursorY = 0x2;
    // LD_addr_A(wCardFlipCursorX);
    wram->wCardFlipCursorX = 0x2;
    // LD_DE(MUSIC_GAME_CORNER);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_GAME_CORNER);

    while(!bit_test(wram->wJumptableIndex, 7)){
    // MasterLoop:
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto leavethegame;
        // CALL(av_CardFlip_CardFlip);
        v_CardFlip_CardFlip();
        // goto MasterLoop;
    }

// leavethegame:
    // CALL(aWaitSFX);
    // LD_DE(SFX_QUIT_SLOTS);
    WaitSFX_Conv();
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_QUIT_SLOTS);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // LD_HL(wOptions);
    // RES_hl(4);
    bit_reset(wram->wOptions, 4);
    // RET;
}

static void v_CardFlip_Increment(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    // RET;
    wram->wJumptableIndex++;
}

static void v_CardFlip_CardFlip(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']


// Jumptable:
    switch(wram->wJumptableIndex){
        //dw ['.AskPlayWithThree'];
    case 0:
    // AskPlayWithThree:
        static const txt_cmd_s CardFlipPlayWithThreeCoinsText[] = {
            text_far(v_CardFlipPlayWithThreeCoinsText)
            text_end
        };
        // LD_HL(mv_CardFlip_CardFlipPlayWithThreeCoinsText);
        // CALL(aCardFlip_UpdateCoinBalanceDisplay);
        CardFlip_UpdateCoinBalanceDisplay(CardFlipPlayWithThreeCoinsText);
        // CALL(aYesNoBox);
        // IF_C goto SaidNo;
        if(YesNoBox_Conv()){
            // CALL(aCardFlip_ShuffleDeck);
            CardFlip_ShuffleDeck();
            // CALL(av_CardFlip_Increment);
            v_CardFlip_Increment();
            // RET;
            return;
        }

    // SaidNo:
        // LD_A(7);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 7;
        // RET;
        return;

        //dw ['.DeductCoins'];
    case 1: {
    // DeductCoins:
        static const txt_cmd_s CardFlipNotEnoughCoinsText[] = {
            text_far(v_CardFlipNotEnoughCoinsText)
            text_end
        };
        // LD_A_addr(wCoins);
        // LD_H_A;
        // LD_A_addr(wCoins + 1);
        // LD_L_A;
        // LD_A_H;
        uint16_t coins = BigEndianToNative16(wram->wCoins);
        // AND_A_A;
        // IF_NZ goto deduct;  // You have at least 256 coins.
        // LD_A_L;
        // CP_A(3);
        // IF_NC goto deduct;  // You have at least 3 coins.
        if(coins < 3){
            // LD_HL(mv_CardFlip_CardFlipNotEnoughCoinsText);
            // CALL(aCardFlip_UpdateCoinBalanceDisplay);
            CardFlip_UpdateCoinBalanceDisplay(CardFlipNotEnoughCoinsText);
            // LD_A(7);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 7;
            // RET;
            return;
        }

    // deduct:
        // LD_DE(-3);
        // ADD_HL_DE;
        // LD_A_H;
        // LD_addr_A(wCoins);
        // LD_A_L;
        // LD_addr_A(wCoins + 1);
        wram->wCoins = NativeToBigEndian16(coins - 3);
        // LD_DE(SFX_TRANSACTION);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_TRANSACTION);
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
        // CALL(aCardFlip_PrintCoinBalance);
        CardFlip_PrintCoinBalance();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // CALL(av_CardFlip_Increment);
        v_CardFlip_Increment();
        // RET;
    } return;

        //dw ['.ChooseACard'];
    case 2: {
    // ChooseACard:
        static const txt_cmd_s CardFlipChooseACardText[] = {
            text_far(v_CardFlipChooseACardText)
            text_end
        };
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
        // hlcoord(0, 0, wTilemap);
        // LD_BC((12 << 8) | 9);
        // CALL(aCardFlip_FillGreenBox);
        CardFlip_FillGreenBox(coord(0, 0, wram->wTilemap), 12, 9);
        // hlcoord(9, 0, wTilemap);
        // LD_BC(SCREEN_WIDTH);
        // LD_A_addr(wCardFlipNumCardsPlayed);
        // CALL(aAddNTimes);
        // LD_hl(CARDFLIP_LIGHT_ON);
        coord(9, 0, wram->wTilemap)[SCREEN_WIDTH * wram->wCardFlipNumCardsPlayed] = CARDFLIP_LIGHT_ON;
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);
        // hlcoord(2, 0, wTilemap);
        // CALL(aPlaceCardFaceDown);
        PlaceCardFaceDown(coord(2, 0, wram->wTilemap));
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);
        // hlcoord(2, 6, wTilemap);
        // CALL(aPlaceCardFaceDown);
        PlaceCardFaceDown(coord(2, 6, wram->wTilemap));
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // LD_HL(mv_CardFlip_CardFlipChooseACardText);
        // CALL(aCardFlip_UpdateCoinBalanceDisplay);
        CardFlip_UpdateCoinBalanceDisplay(CardFlipChooseACardText);
        // XOR_A_A;
        // LD_addr_A(wCardFlipWhichCard);
        wram->wCardFlipWhichCard = 0x0;

        while(1){
        // loop:
            // CALL(aJoyTextDelay);
            JoyTextDelay_Conv();
            // LDH_A_addr(hJoyLast);
            // AND_A(A_BUTTON);
            // IF_NZ goto next;
            if(hram->hJoyLast & A_BUTTON)
                break;
            // LD_DE(SFX_KINESIS);
            // CALL(aPlaySFX);
            PlaySFX_Conv(SFX_KINESIS);
            // CALL(aPlaceOAMCardBorder);
            PlaceOAMCardBorder(wram->wCardFlipWhichCard);
            // LD_C(4);
            // CALL(aDelayFrames);
            DelayFrames_Conv(4);
            // LD_HL(wCardFlipWhichCard);
            // LD_A_hl;
            // XOR_A(0x1);
            // LD_hl_A;
            wram->wCardFlipWhichCard ^= 0x1;
            // goto loop;
        }

    // next:
        // LD_DE(SFX_SLOT_MACHINE_START);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_SLOT_MACHINE_START);
        // LD_A(0x3);
        uint8_t a = 0x3;

        do {
        // loop2:
            // PUSH_AF;
            // CALL(aPlaceOAMCardBorder);
            PlaceOAMCardBorder(wram->wCardFlipWhichCard);
            // LD_C(4);
            // CALL(aDelayFrames);
            DelayFrames_Conv(4);
            // CALL(aClearSprites);
            ClearSprites_Conv();
            // LD_C(4);
            // CALL(aDelayFrames);
            DelayFrames_Conv(4);
            // POP_AF;
            // DEC_A;
            // IF_NZ goto loop2;
        } while(--a != 0);
        // LD_HL(wCardFlipWhichCard);
        // LD_A_hl;
        // PUSH_AF;
        // XOR_A(0x1);
        // LD_hl_A;
        tile_t* hl;
        uint16_t bc;
        // CALL(aGetCoordsOfChosenCard);
        GetCoordsOfChosenCard(&hl, &bc, wram->wCardFlipWhichCard ^ 0x1);
        // LD_BC((6 << 8) | 5);
        // CALL(aCardFlip_FillGreenBox);
        CardFlip_FillGreenBox(hl, 6, 5);
        // POP_AF;
        // LD_addr_A(wCardFlipWhichCard);
        // CALL(av_CardFlip_Increment);
        v_CardFlip_Increment();
        // RET;
    } return;

        //dw ['.PlaceYourBet'];
    case 3:
    // PlaceYourBet:
        static const txt_cmd_s CardFlipPlaceYourBetText[] = {
            text_far(v_CardFlipPlaceYourBetText)
            text_end
        };
        // LD_HL(mv_CardFlip_CardFlipPlaceYourBetText);
        // CALL(aCardFlip_UpdateCoinBalanceDisplay);
        CardFlip_UpdateCoinBalanceDisplay(CardFlipPlaceYourBetText);

        while(1){
        // betloop:
            // CALL(aJoyTextDelay);
            JoyTextDelay_Conv();
            // LDH_A_addr(hJoyLast);
            // AND_A(A_BUTTON);
            // IF_NZ goto betdone;
            if(hram->hJoyLast & A_BUTTON)
                break;
            // CALL(aChooseCard_HandleJoypad);
            ChooseCard_HandleJoypad();
            // CALL(aCardFlip_UpdateCursorOAM);
            CardFlip_UpdateCursorOAM();
            // CALL(aDelayFrame);
            DelayFrame();
            // goto betloop;
        }


    // betdone:
        // CALL(av_CardFlip_Increment);
        v_CardFlip_Increment();
        // RET;
        return;

        //dw ['.CheckTheCard'];
    case 4: {
    // CheckTheCard:
        // XOR_A_A;
        // LDH_addr_A(hVBlankCounter);
        hram->hVBlankCounter = 0x0;
        // CALL(aCardFlip_UpdateCursorOAM);
        CardFlip_UpdateCursorOAM();
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // LD_DE(SFX_CHOOSE_A_CARD);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_CHOOSE_A_CARD);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // LD_A_addr(wCardFlipNumCardsPlayed);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(wDeck);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_addr(wCardFlipWhichCard);
        // LD_E_A;
        // ADD_HL_DE;
        // LD_A_hl;
        // LD_addr_A(wCardFlipFaceUpCard);
        wram->wCardFlipFaceUpCard = wram->wDeck[2 * wram->wCardFlipNumCardsPlayed + wram->wCardFlipWhichCard];
        // LD_E_A;
        // LD_HL(wDiscardPile);
        // ADD_HL_DE;
        // LD_hl(TRUE);
        wram->wDiscardPile[wram->wCardFlipFaceUpCard] = TRUE;
        // CALL(aGetCoordsOfChosenCard);
        tile_t* hl;
        uint16_t bc;
        GetCoordsOfChosenCard(&hl, &bc, wram->wCardFlipWhichCard);
        // CALL(aCardFlip_DisplayCardFaceUp);
        CardFlip_DisplayCardFaceUp(hl);
        // CALL(aWaitBGMap2);
        WaitBGMap2_Conv();
        // CALL(av_CardFlip_Increment);
        v_CardFlip_Increment();
        // RET;
    } return;

        //dw ['.TabulateTheResult'];
    case 5:
    // TabulateTheResult:
        // CALL(aCardFlip_CheckWinCondition);
        CardFlip_CheckWinCondition();
        // CALL(aWaitPressAorB_BlinkCursor);
        WaitPressAorB_BlinkCursor_Conv();
        // CALL(av_CardFlip_Increment);
        v_CardFlip_Increment();
        // RET;
        return;

        //dw ['.PlayAgain'];
    case 6:
    // PlayAgain:
        static const txt_cmd_s CardFlipPlayAgainText[] = {
            text_far(v_CardFlipPlayAgainText)
            text_end
        };
        static const txt_cmd_s CardFlipShuffledText[] = {
            text_far(v_CardFlipShuffledText)
            text_end
        };
        // CALL(aClearSprites);
        ClearSprites_Conv();
        // LD_HL(mv_CardFlip_CardFlipPlayAgainText);
        // CALL(aCardFlip_UpdateCoinBalanceDisplay);
        CardFlip_UpdateCoinBalanceDisplay(CardFlipPlayAgainText);
        // CALL(aYesNoBox);
        // IF_NC goto Continue;
        if(!YesNoBox_Conv()){
            // CALL(av_CardFlip_Increment);
            v_CardFlip_Increment();
            // RET;
            return;
        }

    // Continue:
        // LD_A_addr(wCardFlipNumCardsPlayed);
        // INC_A;
        // LD_addr_A(wCardFlipNumCardsPlayed);
        // CP_A(12);
        // IF_C goto KeepTheCurrentDeck;
        if(++wram->wCardFlipNumCardsPlayed >= 12){
            // CALL(aCardFlip_InitTilemap);
            CardFlip_InitTilemap();
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0x1;
            // CALL(aCardFlip_ShuffleDeck);
            CardFlip_ShuffleDeck();
            // LD_HL(mv_CardFlip_CardFlipShuffledText);
            // CALL(aPrintText);
            PrintText_Conv2(CardFlipShuffledText);
            // goto LoopAround;
        }
        else {
        // KeepTheCurrentDeck:
            // CALL(aCardFlip_BlankDiscardedCardSlot);
            CardFlip_BlankDiscardedCardSlot();
        }

    // LoopAround:
        // LD_A(1);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 1;
        // RET;
        return;

    case 7:
        //dw ['.Quit'];
    // Quit:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        // RET;
        return;
    }
}

void CardFlip_ShuffleDeck(void){
    // LD_HL(wDeck);
    // LD_BC(CARDFLIP_DECK_SIZE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wDeck, sizeof(wram->wDeck), 0x0);
    // LD_DE(wDeck);
    uint8_t* de = wram->wDeck;
    // LD_C(CARDFLIP_DECK_SIZE - 1);
    uint8_t c = CARDFLIP_DECK_SIZE - 1;

    do {
        uint8_t a;
        do {
            do {
            // loop:
                // CALL(aRandom);
                // AND_A(0x1f);
                a = Random_Conv() & 0x1f;
                // CP_A(CARDFLIP_DECK_SIZE);
                // IF_NC goto loop;
            } while(a >= CARDFLIP_DECK_SIZE);
            // LD_L_A;
            // LD_H(0);
            // ADD_HL_DE;
            // LD_A_hl;
            // AND_A_A;
            // IF_NZ goto loop;
        } while(de[a] != 0);
        // LD_hl_C;
        de[a] = c;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // XOR_A_A;
    // LD_addr_A(wCardFlipNumCardsPlayed);
    wram->wCardFlipNumCardsPlayed = 0x0;
    // LD_HL(wDiscardPile);
    // LD_BC(CARDFLIP_DECK_SIZE);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wDiscardPile, sizeof(wram->wDiscardPile), 0x0);
    // RET;
}

uint16_t CollapseCursorPosition(void){
    // LD_HL(0);
    // LD_BC(6);
    // LD_A_addr(wCardFlipCursorY);
    // CALL(aAddNTimes);
    // LD_B(0x0);
    // LD_A_addr(wCardFlipCursorX);
    // LD_C_A;
    // ADD_HL_BC;
    // RET;
    return (6 * wram->wCardFlipCursorY) + wram->wCardFlipCursorX;
}

void GetCoordsOfChosenCard(tile_t** hl, uint16_t* bc, uint8_t card){
    // LD_A_addr(wCardFlipWhichCard);
    // AND_A_A;
    // IF_NZ goto BottomCard;
    if(card == 0){
        // hlcoord(2, 0, wTilemap);
        *hl = coord(2, 0, wram->wTilemap);
        // bcpixel2(2, 3);
        *bc = pixel2(2, 3);
        // goto done;
    }
    else {
    // BottomCard:
        // hlcoord(2, 6, wTilemap);
        *hl = coord(2, 6, wram->wTilemap);
        // bcpixel2(8, 3);
        *bc = pixel2(8, 3);
    }
// done:
    // RET;
}

void PlaceCardFaceDown(tile_t* hl){
    static const tile_t FaceDownCardTilemap[] = {
        0x08, 0x09, 0x09, 0x09, 0x0a,
        0x0b, 0x28, 0x2b, 0x28, 0x0c,
        0x0b, 0x2c, 0x2d, 0x2e, 0x0c,
        0x0b, 0x2f, 0x30, 0x31, 0x0c,
        0x0b, 0x32, 0x33, 0x34, 0x0c,
        0x0d, 0x0e, 0x0e, 0x0e, 0x0f,
    };
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // LD_DE(mPlaceCardFaceDown_FaceDownCardTilemap);
    // LD_BC((6 << 8) | 5);
    // CALL(aCardFlip_CopyToBox);
    CardFlip_CopyToBox(hl, FaceDownCardTilemap, 6, 5);
    // RET;
}

void CardFlip_DisplayCardFaceUp(tile_t* hl){
    static const tile_t FaceUpCardTilemap[] = {
        0x18, 0x19, 0x19, 0x19, 0x1a,
        0x1b, 0x35, 0x7f, 0x7f, 0x1c,
        0x0b, 0x28, 0x28, 0x28, 0x0c,
        0x0b, 0x28, 0x28, 0x28, 0x0c,
        0x0b, 0x28, 0x28, 0x28, 0x0c,
        0x1d, 0x1e, 0x1e, 0x1e, 0x1f,
    };
    typedef struct DeckCard {
        tile_t level;
        uint8_t pic;
    } deckcard_s;
    #define _C(_n) (CHAR_0 + (_n - '0'))
    static const deckcard_s Deck[] = {
    // level, pic anchor (3x3)
        {_C('1'), 0x4e}, {_C('1'), 0x57}, {_C('1'), 0x69}, {_C('1'), 0x60},
        {_C('2'), 0x4e}, {_C('2'), 0x57}, {_C('2'), 0x69}, {_C('2'), 0x60},
        {_C('3'), 0x4e}, {_C('3'), 0x57}, {_C('3'), 0x69}, {_C('3'), 0x60},
        {_C('4'), 0x4e}, {_C('4'), 0x57}, {_C('4'), 0x69}, {_C('4'), 0x60},
        {_C('5'), 0x4e}, {_C('5'), 0x57}, {_C('5'), 0x69}, {_C('5'), 0x60},
        {_C('6'), 0x4e}, {_C('6'), 0x57}, {_C('6'), 0x69}, {_C('6'), 0x60},
    };
    #undef _C
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // PUSH_HL;
    // PUSH_HL;
// Flip the card face up.
    // LD_DE(mCardFlip_DisplayCardFaceUp_FaceUpCardTilemap);
    // LD_BC((6 << 8) | 5);
    // CALL(aCardFlip_CopyToBox);
    CardFlip_CopyToBox(hl, FaceUpCardTilemap, 6, 5);

// Get the level and species of the upturned card.
    // LD_A_addr(wCardFlipFaceUpCard);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mCardFlip_DisplayCardFaceUp_Deck);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    tile_t e = Deck[wram->wCardFlipFaceUpCard].level;
    uint8_t d = Deck[wram->wCardFlipFaceUpCard].pic;

// Place the level.
    // POP_HL;
    tile_t* hl2 = hl;
    // LD_BC(3 + SCREEN_WIDTH);
    // ADD_HL_BC;
    hl2 += 3 + SCREEN_WIDTH;
    // LD_hl_E;
    *hl2 = e;

// Place the Pokepic.
    // LD_BC(SCREEN_HEIGHT);
    // ADD_HL_BC;
    hl2 += SCREEN_HEIGHT;
    // LD_A_D;
    uint8_t a = d;
    // LD_DE(SCREEN_WIDTH);
    // LD_B(3);
    uint8_t b = 3;

    do {
    // row:
        // PUSH_HL;
        tile_t* hl3 = hl2;
        // LD_C(3);
        uint8_t c = 3;

        do {
        // col:
            // LD_hli_A;
            // INC_A;
            *(hl3++) = a++;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl2 += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // POP_HL;

// Pointless CGB check
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram->hCGB == 0)
        return;

// Set the attributes
    // LD_DE(wAttrmap - wTilemap);
    // ADD_HL_DE;
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(3);
    // INC_A;
    // LD_BC((6 << 8) | 5);
    // CALL(aCardFlip_FillBox);
    CardFlip_FillBox(hl + (wAttrmap - wTilemap), 6, 5, (wram->wCardFlipFaceUpCard & 3) + 1);
    // RET;
}

void CardFlip_UpdateCoinBalanceDisplay(const txt_cmd_s* hl){
    // PUSH_HL;
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(SCREEN_WIDTH - 2);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, SCREEN_WIDTH - 2);
    // POP_HL;
    // CALL(aPrintTextboxText);
    PrintTextboxText_Conv2(hl);
    // CALL(aCardFlip_PrintCoinBalance);
    CardFlip_PrintCoinBalance();
    // RET;
}

void CardFlip_PrintCoinBalance(void){
    // hlcoord(9, 15, wTilemap);
    // LD_B(1);
    // LD_C(9);
    // CALL(aTextbox);
    Textbox_Conv2(coord(9, 15, wram->wTilemap), 1, 9);
    // hlcoord(10, 16, wTilemap);
    // LD_DE(mCardFlip_PrintCoinBalance_CoinStr);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("COIN"), coord(10, 16, wram->wTilemap));
    // hlcoord(15, 16, wTilemap);
    // LD_DE(wCoins);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 4);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(15, 16, wram->wTilemap), &wram->wCoins, PRINTNUM_LEADINGZEROS | 2, 4);
    // RET;
}

void CardFlip_InitTilemap(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // LD_A(0x29);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x29);
    // hlcoord(9, 0, wTilemap);
    // LD_DE(mCardFlipTilemap);
    asset_s tm = LoadAsset(CardFlipTilemap);
    // LD_BC((12 << 8) | 11);
    // CALL(aCardFlip_CopyToBox);
    CardFlip_CopyToBox(coord(9, 0, wram->wTilemap), tm.ptr, 12, 11);
    FreeAsset(tm);
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
    // RET;
}

void CardFlip_FillGreenBox(tile_t* hl, uint8_t b, uint8_t c){
    // LD_A(0x29);

    return CardFlip_FillBox(hl, b, c, 0x29);
}

void CardFlip_FillBox(tile_t* hl, uint8_t b, uint8_t c, uint8_t a){
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
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void CardFlip_CopyToBox(tile_t* hl, const tile_t* de, uint8_t b, uint8_t c){
    do{
    // row:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // col:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *hl2 = *de;
            de++;
            hl2++;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c2 != 0);
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void CardFlip_CopyOAM(const uint8_t* hl, uint8_t b, uint8_t c){
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;
    // LD_A_hli;
    uint8_t count = *(hl++);

    do {
    // loop:
        // PUSH_AF;
        // LD_A_hli;
        // ADD_A_B;
        // LD_de_A;  // y
        de->yCoord = *(hl++) + b;
        // INC_DE;
        // LD_A_hli;
        // ADD_A_C;
        // LD_de_A;  // x
        de->xCoord = *(hl++) + c;
        // INC_DE;
        // LD_A_hli;
        // LD_de_A;  // tile id
        de->tileID = *(hl++);
        // INC_DE;
        // LD_A_hli;
        // LD_de_A;  // attributes
        de->attributes = *(hl++);
        // INC_DE;
        de++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--count != 0);
    // RET;
}

//  The top rows of digits 1-9 become the bottom rows of 0-8,
//  so this routine relies on the top rows being blank.
void CardFlip_ShiftDigitsUpOnePixel(void){
    // LD_DE(vTiles0 + LEN_2BPP_TILE * CHAR_0);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * CHAR_0 + 2);
    // LD_BC(10 * LEN_2BPP_TILE - 2);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(vram->vTiles0 + LEN_2BPP_TILE * CHAR_0, vram->vTiles0 + LEN_2BPP_TILE * CHAR_0 + 2, 10 * LEN_2BPP_TILE - 2);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * CHAR_9 + 1 * LEN_2BPP_TILE - 2);
    // XOR_A_A;
    // LD_hli_A;
    vram->vTiles0[LEN_2BPP_TILE * CHAR_9 + 1 * LEN_2BPP_TILE - 2] = 0;
    // LD_hl_A;
    vram->vTiles0[LEN_2BPP_TILE * CHAR_9 + 1 * LEN_2BPP_TILE - 1] = 0;
    // RET;
}

void CardFlip_BlankDiscardedCardSlot(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // LD_A_addr(wCardFlipFaceUpCard);
    // LD_E_A;
    // LD_D(0);
    uint8_t card = wram->wCardFlipFaceUpCard;

    // AND_A(3);  // get mon
    // LD_C_A;
    // LD_B(0);
    uint8_t mon = card & 3;

    // LD_A_E;
    // AND_A(0x1c);  // get level
    // SRL_A;
    uint8_t level = (card & 0x1c) >> 2;
    // ADD_A(LOW(aCardFlip_BlankDiscardedCardSlot_Jumptable));
    // LD_L_A;
    // LD_A(0);
    // ADC_A(HIGH(aCardFlip_BlankDiscardedCardSlot_Jumptable));
    // LD_H_A;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    switch(level){
    // Jumptable:
    //dw ['.Level1'];
    // Level1:
    case 0:
        // LD_HL(wDiscardPile + 4);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto discarded2;
        if(wram->wDiscardPile[4 + card] == 0){
            // hlcoord(13, 3, wTilemap);
            // ADD_HL_BC;
            // ADD_HL_BC;
            // LD_hl(0x36);
            coord(13, 3, wram->wTilemap)[mon * 2] = 0x36;
            // LD_BC(SCREEN_WIDTH);
            // ADD_HL_BC;
            // LD_hl(0x37);
            coord(13, 3, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x37;
            // RET;
            return;
        }

    // discarded2:
        // hlcoord(13, 3, wTilemap);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_hl(0x36);
        coord(13, 3, wram->wTilemap)[mon * 2] = 0x36;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // LD_hl(0x3d);
        coord(13, 3, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3d;
        // RET;
        return;

    //dw ['.Level2'];
    case 1:
    // Level2:
        // LD_HL(wDiscardPile - 4);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto discarded1;
        if(wram->wDiscardPile[card - 4] == 0){
            // hlcoord(13, 4, wTilemap);
            // ADD_HL_BC;
            // ADD_HL_BC;
            // LD_hl(0x3b);
            coord(13, 4, wram->wTilemap)[mon * 2] = 0x3b;
            // LD_BC(SCREEN_WIDTH);
            // ADD_HL_BC;
            // LD_hl(0x3a);
            coord(13, 4, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3a;
            // RET;
            return;
        }

    // discarded1:
        // hlcoord(13, 4, wTilemap);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_hl(0x3d);
        coord(13, 4, wram->wTilemap)[mon * 2] = 0x3d;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // LD_hl(0x3a);
        coord(13, 4, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3a;
        // RET;
        return;

    //dw ['.Level3'];
    case 2:
    // Level3:
        // LD_HL(wDiscardPile + 4);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto discarded4;
        if(wram->wDiscardPile[card + 4]){
            // hlcoord(13, 6, wTilemap);
            // ADD_HL_BC;
            // ADD_HL_BC;
            // LD_hl(0x36);
            coord(13, 6, wram->wTilemap)[mon * 2] = 0x36;
            // LD_BC(SCREEN_WIDTH);
            // ADD_HL_BC;
            // LD_hl(0x38);
            coord(13, 6, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x38;
            // RET;
            return;
        }

    // discarded4:
        // hlcoord(13, 6, wTilemap);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_hl(0x36);
        coord(13, 6, wram->wTilemap)[mon * 2] = 0x36;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // LD_hl(0x3d);
        coord(13, 6, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3d;
        // RET;
        return;

    //dw ['.Level4'];
    case 3:
    // Level4:
        // LD_HL(wDiscardPile - 4);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto discarded3;
        if(wram->wDiscardPile[card + 4] == 0){
            // hlcoord(13, 7, wTilemap);
            // ADD_HL_BC;
            // ADD_HL_BC;
            // LD_hl(0x3c);
            coord(13, 7, wram->wTilemap)[mon * 2] = 0x3c;
            // LD_BC(SCREEN_WIDTH);
            // ADD_HL_BC;
            // LD_hl(0x3a);
            coord(13, 7, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3a;
            // RET;
            return;
        }

    // discarded3:
        // hlcoord(13, 7, wTilemap);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_hl(0x3d);
        coord(13, 7, wram->wTilemap)[mon * 2] = 0x3d;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // LD_hl(0x3a);
        coord(13, 7, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3a;
        // RET;
        return;

    //dw ['.Level5'];
    case 4:
    // Level5:
        // LD_HL(wDiscardPile + 4);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto discarded6;
        if(wram->wDiscardPile[card + 4] == 0){
            // hlcoord(13, 9, wTilemap);
            // ADD_HL_BC;
            // ADD_HL_BC;
            // LD_hl(0x36);
            coord(13, 9, wram->wTilemap)[mon * 2] = 0x36;
            // LD_BC(SCREEN_WIDTH);
            // ADD_HL_BC;
            // LD_hl(0x39);
            coord(13, 9, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x39;
            // RET;
            return;
        }

    // discarded6:
        // hlcoord(13, 9, wTilemap);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_hl(0x36);
        coord(13, 9, wram->wTilemap)[mon * 2] = 0x36;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // LD_hl(0x3d);
        coord(13, 9, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3d;
        // RET;
        return;

    //dw ['.Level6'];
    case 5:
    // Level6:
        // LD_HL(wDiscardPile - 4);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto discarded5;
        if(wram->wDiscardPile[card - 4] == 0){
            // hlcoord(13, 10, wTilemap);
            // ADD_HL_BC;
            // ADD_HL_BC;
            // LD_hl(0x3c);
            coord(13, 10, wram->wTilemap)[mon * 2] = 0x3c;
            // LD_BC(SCREEN_WIDTH);
            // ADD_HL_BC;
            // LD_hl(0x3a);
            coord(13, 10, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3a;
            // RET;
            return;
        }

    // discarded5:
        // hlcoord(13, 10, wTilemap);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_hl(0x3d);
        coord(13, 10, wram->wTilemap)[mon * 2] = 0x3d;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // LD_hl(0x3a);
        coord(13, 10, wram->wTilemap)[mon * 2 + SCREEN_WIDTH] = 0x3a;
        // RET;
        return;
    }
}

static bool CardFlip_CheckWinCondition_IsCoinCaseFull(void){
    // LD_A_addr(wCoins);
    // CP_A(HIGH(MAX_COINS));
    // IF_C goto less;
    // IF_Z goto check_low;
    // goto more;

// check_low:
    // LD_A_addr(wCoins + 1);
    // CP_A(LOW(MAX_COINS));
    // IF_C goto less;
    if(BigEndianToNative16(wram->wCoins) >= MAX_COINS) {
    // more:
        // SCF;
        // RET;
        return true;
    }

// less:
    // AND_A_A;
    // RET;
    return false;
}

static void CardFlip_CheckWinCondition_AddCoinPlaySFX(void){
    // LD_A_addr(wCoins);
    // LD_H_A;
    // LD_A_addr(wCoins + 1);
    // LD_L_A;
    // INC_HL;
    // LD_A_H;
    // LD_addr_A(wCoins);
    // LD_A_L;
    // LD_addr_A(wCoins + 1);
    wram->wCoins = NativeToBigEndian16(BigEndianToNative16(wram->wCoins) + 1);
    // LD_DE(SFX_PAY_DAY);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_PAY_DAY);
    // RET;
}

static void CardFlip_CheckWinCondition_Payout(uint16_t de, uint8_t c){
    static const txt_cmd_s CardFlipYeahText[] = {
        text_far(v_CardFlipYeahText)
        text_end
    };
    // PUSH_BC;
    // PUSH_DE;
    // LD_HL(mCardFlip_CheckWinCondition_CardFlipYeahText);
    // CALL(aCardFlip_UpdateCoinBalanceDisplay);
    CardFlip_UpdateCoinBalanceDisplay(CardFlipYeahText);
    // POP_DE;
    // CALL(aPlaySFX);
    PlaySFX_Conv(de);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // POP_BC;

    do {
    // loop:
        // PUSH_BC;
        // CALL(aCardFlip_CheckWinCondition_IsCoinCaseFull);
        // IF_C goto full;
        if(!CardFlip_CheckWinCondition_IsCoinCaseFull()){
            // CALL(aCardFlip_CheckWinCondition_AddCoinPlaySFX);
            CardFlip_CheckWinCondition_AddCoinPlaySFX();
        }

    // full:
        // CALL(aCardFlip_PrintCoinBalance);
        CardFlip_PrintCoinBalance();
        // LD_C(2);
        // CALL(aDelayFrames);
        DelayFrames_Conv(2);
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
    return;
}

// TODO: Clean up this function.
void CardFlip_CheckWinCondition(void){
    static const txt_cmd_s CardFlipDarnText[] = {
        text_far(v_CardFlipDarnText)
        text_end
    };
    // CALL(aCollapseCursorPosition);
    // ADD_HL_HL;
    // LD_DE(mCardFlip_CheckWinCondition_Jumptable);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    uint16_t position = CollapseCursorPosition();
    #define POS(x, y) ((6*(y))+(x))
// Jumptable:
    switch(position){
        case POS(0,0): goto Impossible; //dw ['.Impossible'];
        case POS(1,0): goto Impossible; //dw ['.Impossible'];
        case POS(2,0): goto PikaJiggly; //dw ['.PikaJiggly'];
        case POS(3,0): goto PikaJiggly; //dw ['.PikaJiggly'];
        case POS(4,0): goto PoliOddish; //dw ['.PoliOddish'];
        case POS(5,0): goto PoliOddish; //dw ['.PoliOddish'];

        case POS(0,1): goto Impossible; //dw ['.Impossible'];
        case POS(1,1): goto Impossible; //dw ['.Impossible'];
        case POS(2,1): goto Pikachu;    //dw ['.Pikachu'];
        case POS(3,1): goto Jigglypuff; //dw ['.Jigglypuff'];
        case POS(4,1): goto Poliwag;    //dw ['.Poliwag'];
        case POS(5,1): goto Oddish;     //dw ['.Oddish'];

        case POS(0,2): goto OneTwo;     //dw ['.OneTwo'];
        case POS(1,2): goto One;        //dw ['.One'];
        case POS(2,2): goto PikaOne;    //dw ['.PikaOne'];
        case POS(3,2): goto JigglyOne;  //dw ['.JigglyOne'];
        case POS(4,2): goto PoliOne;    //dw ['.PoliOne'];
        case POS(5,2): goto OddOne;     //dw ['.OddOne'];

        case POS(0,3): goto OneTwo;     //dw ['.OneTwo'];
        case POS(1,3): goto Two;        //dw ['.Two'];
        case POS(2,3): goto PikaTwo;    //dw ['.PikaTwo'];
        case POS(3,3): goto JigglyTwo;  //dw ['.JigglyTwo'];
        case POS(4,3): goto PoliTwo;    //dw ['.PoliTwo'];
        case POS(5,3): goto OddTwo;     //dw ['.OddTwo'];

        case POS(0,4): goto ThreeFour;  //dw ['.ThreeFour'];
        case POS(1,4): goto Three;      //dw ['.Three'];
        case POS(2,4): goto PikaThree;  //dw ['.PikaThree'];
        case POS(3,4): goto JigglyThree;//dw ['.JigglyThree'];
        case POS(4,4): goto PoliThree;  //dw ['.PoliThree'];
        case POS(5,4): goto OddThree;   //dw ['.OddThree'];

        case POS(0,5): goto ThreeFour;  //dw ['.ThreeFour'];
        case POS(1,5): goto Four;       //dw ['.Four'];
        case POS(2,5): goto PikaFour;   //dw ['.PikaFour'];
        case POS(3,5): goto JigglyFour; //dw ['.JigglyFour'];
        case POS(4,5): goto PoliFour;   //dw ['.PoliFour'];
        case POS(5,5): goto OddFour;    //dw ['.OddFour'];

        case POS(0,6): goto FiveSix;    //dw ['.FiveSix'];
        case POS(1,6): goto Five;       //dw ['.Five'];
        case POS(2,6): goto PikaFive;   //dw ['.PikaFive'];
        case POS(3,6): goto JigglyFive; //dw ['.JigglyFive'];
        case POS(4,6): goto PoliFive;   //dw ['.PoliFive'];
        case POS(5,6): goto OddFive;    //dw ['.OddFive'];

        case POS(0,7): goto FiveSix;    //dw ['.FiveSix'];
        case POS(1,7): goto Six;        //dw ['.Six'];
        case POS(2,7): goto PikaSix;    //dw ['.PikaSix'];
        case POS(3,7): goto JigglySix;  //dw ['.JigglySix'];
        case POS(4,7): goto PoliSix;    //dw ['.PoliSix'];
        case POS(5,7): goto OddSix;     //dw ['.OddSix'];
    }
    #undef POS

Impossible:
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

PikaJiggly:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x2);
    // JP_NZ (mCardFlip_CheckWinCondition_Lose);
    if((wram->wCardFlipFaceUpCard & 0x2) != 0)
        goto Lose;
    goto WinSix;

PoliOddish:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x2);
    // IF_NZ goto WinSix;
    if((wram->wCardFlipFaceUpCard & 0x2) != 0)
        goto WinSix;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

WinSix:
    // LD_C(0x6);
    // LD_DE(SFX_2ND_PLACE);
    // JP(mCardFlip_CheckWinCondition_Payout);
    return CardFlip_CheckWinCondition_Payout(SFX_2ND_PLACE, 0x6);


OneTwo:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x18);
    // IF_Z goto WinNine;
    if((wram->wCardFlipFaceUpCard & 0x18) == 0)
        goto WinNine;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

ThreeFour:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x18);
    // CP_A(0x8);
    // IF_Z goto WinNine;
    if((wram->wCardFlipFaceUpCard & 0x18) == 0x18)
        goto WinNine;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

FiveSix:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x18);
    // CP_A(0x10);
    // IF_Z goto WinNine;
    if((wram->wCardFlipFaceUpCard & 0x18) == 0x10)
        goto WinNine;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

WinNine:
    // LD_C(0x9);
    // LD_DE(SFX_2ND_PLACE);
    // JP(mCardFlip_CheckWinCondition_Payout);
    return CardFlip_CheckWinCondition_Payout(SFX_2ND_PLACE, 0x9);


Pikachu:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x3);
    // IF_Z goto WinTwelve;
    if((wram->wCardFlipFaceUpCard & 0x3) == 0x0)
        goto WinTwelve;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

Jigglypuff:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x3);
    // CP_A(0x1);
    // IF_Z goto WinTwelve;
    if((wram->wCardFlipFaceUpCard & 0x3) == 0x1)
        goto WinTwelve;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

Poliwag:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x3);
    // CP_A(0x2);
    // IF_Z goto WinTwelve;
    if((wram->wCardFlipFaceUpCard & 0x3) == 0x2)
        goto WinTwelve;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

Oddish:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x3);
    // CP_A(0x3);
    // IF_Z goto WinTwelve;
    if((wram->wCardFlipFaceUpCard & 0x3) == 0x3)
        goto WinTwelve;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

WinTwelve:
    // LD_C(0xc);
    // LD_DE(SFX_2ND_PLACE);
    // JP(mCardFlip_CheckWinCondition_Payout);
    return CardFlip_CheckWinCondition_Payout(SFX_2ND_PLACE, 0xc);


One:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x1c);
    // IF_Z goto WinEighteen;
    if((wram->wCardFlipFaceUpCard & 0x1c) == 0x0)
        goto WinEighteen;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

Two:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x1c);
    // CP_A(0x4);
    // IF_Z goto WinEighteen;
    if((wram->wCardFlipFaceUpCard & 0x1c) == 0x4)
        goto WinEighteen;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

Three:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x1c);
    // CP_A(0x8);
    // IF_Z goto WinEighteen;
    if((wram->wCardFlipFaceUpCard & 0x1c) == 0x8)
        goto WinEighteen;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

Four:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x1c);
    // CP_A(0xc);
    // IF_Z goto WinEighteen;
    if((wram->wCardFlipFaceUpCard & 0x1c) == 0xc)
        goto WinEighteen;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

Five:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x1c);
    // CP_A(0x10);
    // IF_Z goto WinEighteen;
    if((wram->wCardFlipFaceUpCard & 0x1c) == 0x10)
        goto WinEighteen;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

Six:
    // LD_A_addr(wCardFlipFaceUpCard);
    // AND_A(0x1c);
    // CP_A(0x14);
    // IF_Z goto WinEighteen;
    if((wram->wCardFlipFaceUpCard & 0x1c) == 0x14)
        goto WinEighteen;
    // JP(mCardFlip_CheckWinCondition_Lose);
    goto Lose;

WinEighteen:
    // LD_C(0x12);
    // LD_DE(SFX_2ND_PLACE);
    // JP(mCardFlip_CheckWinCondition_Payout);
    return CardFlip_CheckWinCondition_Payout(SFX_2ND_PLACE, 0x12);

    {
        uint8_t e;

    PikaOne:
        // LD_E(0x0);
        e = 0x0;
        goto CheckWin72;


    JigglyOne:
        // LD_E(0x1);
        e = 0x1;
        goto CheckWin72;


    PoliOne:
        // LD_E(0x2);
        e = 0x2;
        goto CheckWin72;


    OddOne:
        // LD_E(0x3);
        e = 0x3;
        goto CheckWin72;


    PikaTwo:
        // LD_E(0x4);
        e = 0x4;
        goto CheckWin72;


    JigglyTwo:
        // LD_E(0x5);
        e = 0x5;
        goto CheckWin72;


    PoliTwo:
        // LD_E(0x6);
        e = 0x6;
        goto CheckWin72;


    OddTwo:
        // LD_E(0x7);
        e = 0x7;
        goto CheckWin72;


    PikaThree:
        // LD_E(0x8);
        e = 0x8;
        goto CheckWin72;


    JigglyThree:
        // LD_E(0x9);
        e = 0x9;
        goto CheckWin72;


    PoliThree:
        // LD_E(0xa);
        e = 0xa;
        goto CheckWin72;


    OddThree:
        // LD_E(0xb);
        e = 0xb;
        goto CheckWin72;


    PikaFour:
        // LD_E(0xc);
        e = 0xc;
        goto CheckWin72;


    JigglyFour:
        // LD_E(0xd);
        e = 0xd;
        goto CheckWin72;


    PoliFour:
        // LD_E(0xe);
        e = 0xe;
        goto CheckWin72;


    OddFour:
        // LD_E(0xf);
        e = 0xf;
        goto CheckWin72;


    PikaFive:
        // LD_E(0x10);
        e = 0x10;
        goto CheckWin72;


    JigglyFive:
        // LD_E(0x11);
        e = 0x11;
        goto CheckWin72;


    PoliFive:
        // LD_E(0x12);
        e = 0x12;
        goto CheckWin72;


    OddFive:
        // LD_E(0x13);
        e = 0x13;
        goto CheckWin72;


    PikaSix:
        // LD_E(0x14);
        e = 0x14;
        goto CheckWin72;


    JigglySix:
        // LD_E(0x15);
        e = 0x15;
        goto CheckWin72;


    PoliSix:
        // LD_E(0x16);
        e = 0x16;
        goto CheckWin72;


    OddSix:
        // LD_E(0x17);
        e = 0x17;


    CheckWin72:
        // LD_A_addr(wCardFlipFaceUpCard);
        // CP_A_E;
        // IF_NZ goto Lose;
        if(wram->wCardFlipFaceUpCard != e)
            goto Lose;
        // LD_C(72);
        // LD_DE(SFX_2ND_PLACE);
        // goto Payout;
        return CardFlip_CheckWinCondition_Payout(SFX_2ND_PLACE, 72);

    Lose:
        // LD_DE(SFX_WRONG);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_WRONG);
        // LD_HL(mCardFlip_CheckWinCondition_CardFlipDarnText);
        // CALL(aCardFlip_UpdateCoinBalanceDisplay);
        CardFlip_UpdateCoinBalanceDisplay(CardFlipDarnText);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // RET;
        return;
    }
}

void PlaceOAMCardBorder(uint8_t card){
    static const uint8_t SpriteData[] = {
        18,
        dbsprite(0, 0, 0, 0, 0x04, 0),
        dbsprite(1, 0, 0, 0, 0x06, 0),
        dbsprite(2, 0, 0, 0, 0x06, 0),
        dbsprite(3, 0, 0, 0, 0x06, 0),
        dbsprite(4, 0, 0, 0, 0x04, 0 | X_FLIP),

        dbsprite(0, 1, 0, 0, 0x05, 0),
        dbsprite(4, 1, 0, 0, 0x05, 0 | X_FLIP),

        dbsprite(0, 2, 0, 0, 0x05, 0),
        dbsprite(4, 2, 0, 0, 0x05, 0 | X_FLIP),

        dbsprite(0, 3, 0, 0, 0x05, 0),
        dbsprite(4, 3, 0, 0, 0x05, 0 | X_FLIP),

        dbsprite(0, 4, 0, 0, 0x05, 0x00),
        dbsprite(4, 4, 0, 0, 0x05, 0 | X_FLIP),

        dbsprite(0, 5, 0, 0, 0x04, 0 | Y_FLIP),
        dbsprite(1, 5, 0, 0, 0x06, 0 | Y_FLIP),
        dbsprite(2, 5, 0, 0, 0x06, 0 | Y_FLIP),
        dbsprite(3, 5, 0, 0, 0x06, 0 | Y_FLIP),
        dbsprite(4, 5, 0, 0, 0x04, 0 | X_FLIP | Y_FLIP),
    };
    // CALL(aGetCoordsOfChosenCard);
    tile_t* hl;
    uint16_t bc;
    GetCoordsOfChosenCard(&hl, &bc, card);
    // LD_HL(mPlaceOAMCardBorder_SpriteData);
    // CALL(aCardFlip_CopyOAM);
    CardFlip_CopyOAM(SpriteData, HIGH(bc), LOW(bc));
    // RET;
}

// TODO: Clean up gotos in this function,
void ChooseCard_HandleJoypad(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    uint8_t input = hram->hJoyLast;
    uint8_t* hl;
    // AND_A(D_LEFT);
    // JP_NZ (mChooseCard_HandleJoypad_d_left);
    if(input & D_LEFT){
    // d_left:
        // LD_HL(wCardFlipCursorX);
        hl = &wram->wCardFlipCursorX;
        // LD_A_addr(wCardFlipCursorY);
        // AND_A_A;
        // IF_Z goto mon_pair_left;
        if(wram->wCardFlipCursorY == 0)
            goto mon_pair_left;
        // CP_A(0x1);
        // IF_Z goto mon_group_left;
        else if(wram->wCardFlipCursorY == 0x1)
            goto mon_group_left;
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wCardFlipCursorX == 0x0)
            return;
        // DEC_hl;
        --wram->wCardFlipCursorX;
        // JP(mChooseCard_HandleJoypad_play_sound);
        goto play_sound;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // JP_NZ (mChooseCard_HandleJoypad_d_right);
    else if(input & D_RIGHT){
    // d_right:
        // LD_HL(wCardFlipCursorX);
        hl = &wram->wCardFlipCursorX;
        // LD_A_addr(wCardFlipCursorY);
        // AND_A_A;
        // IF_Z goto mon_pair_right;
        if(wram->wCardFlipCursorY == 0x0)
            goto mon_pair_right;
        // LD_A_hl;
        // CP_A(0x5);
        // RET_NC ;
        if(wram->wCardFlipCursorX >= 0x5)
            return;
        // INC_hl;
        ++wram->wCardFlipCursorX;
        goto play_sound;
    }
    // LD_A_hl;
    // AND_A(D_UP);
    // JP_NZ (mChooseCard_HandleJoypad_d_up);
    else if(input & D_UP){
    // d_up:
        // LD_HL(wCardFlipCursorY);
        hl = &wram->wCardFlipCursorY;
        // LD_A_addr(wCardFlipCursorX);
        // AND_A_A;
        // IF_Z goto num_pair_up;
        if(wram->wCardFlipCursorX == 0)
            goto num_pair_up;
        // CP_A(0x1);
        // IF_Z goto num_gp_up;
        else if(wram->wCardFlipCursorX == 0x1)
            goto num_gp_up;
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wCardFlipCursorY == 0x0)
            return;
        // DEC_hl;
        --wram->wCardFlipCursorY;
        goto play_sound;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JP_NZ (mChooseCard_HandleJoypad_d_down);
    else if(input & D_DOWN){
    // d_down:
        // LD_HL(wCardFlipCursorY);
        hl = &wram->wCardFlipCursorY;
        // LD_A_addr(wCardFlipCursorX);
        // AND_A_A;
        // IF_Z goto num_pair_down;
        if(wram->wCardFlipCursorX == 0)
            goto num_pair_down;
        // LD_HL(wCardFlipCursorY);
        // LD_A_hl;
        // CP_A(0x7);
        // RET_NC ;
        if(wram->wCardFlipCursorY >= 0x7)
            return;
        // INC_hl;
        ++wram->wCardFlipCursorY;
        goto play_sound;
    }
    // RET;
    return;

mon_group_left:
    // LD_A_hl;
    // CP_A(0x3);
    // IF_C goto left_to_number_gp;
    if(*hl < 0x3)
        goto left_to_number_gp;
    // DEC_hl;
    (*hl)--;
    // JP(mChooseCard_HandleJoypad_play_sound);
    goto play_sound;

mon_pair_left:
    // LD_A_hl;
    // AND_A(0xe);
    // LD_hl_A;
    *hl &= 0xe;
    // CP_A(0x3);
    // IF_C goto left_to_number_gp;
    if(*hl < 0x3)
        goto left_to_number_gp;
    // DEC_hl;
    // DEC_hl;
    *hl -= 2;
    // JP(mChooseCard_HandleJoypad_play_sound);
    goto play_sound;

left_to_number_gp:
    // LD_A(0x2);
    // LD_addr_A(wCardFlipCursorY);
    wram->wCardFlipCursorY = 0x2;
    // LD_A(0x1);
    // LD_addr_A(wCardFlipCursorX);
    wram->wCardFlipCursorX = 0x1;
    // JP(mChooseCard_HandleJoypad_play_sound);
    goto play_sound;

mon_pair_right:
    // LD_A_hl;
    // AND_A(0xe);
    // LD_hl_A;
    *hl &= 0xe;
    // CP_A(0x4);
    // RET_NC ;
    if(*hl >= 0x4)
        return;
    // INC_hl;
    // INC_hl;
    *hl += 2;
    goto play_sound;

num_gp_up:
    // LD_A_hl;
    // CP_A(0x3);
    // IF_C goto up_to_mon_group;
    if(*hl < 0x3)
        goto up_to_mon_group;
    // DEC_hl;
    (*hl)--;
    goto play_sound;

num_pair_up:
    // LD_A_hl;
    // AND_A(0xe);
    // LD_hl_A;
    *hl &= 0xe;
    // CP_A(0x3);
    // IF_C goto up_to_mon_group;
    if(*hl < 0x3)
        goto up_to_mon_group;
    // DEC_hl;
    // DEC_hl;
    *hl -= 2;
    goto play_sound;

up_to_mon_group:
    // LD_A(0x1);
    // LD_addr_A(wCardFlipCursorY);
    wram->wCardFlipCursorY = 0x1;
    // LD_A(0x2);
    // LD_addr_A(wCardFlipCursorX);
    wram->wCardFlipCursorX = 0x2;
    goto play_sound;

num_pair_down:
    // LD_A_hl;
    // AND_A(0xe);
    // LD_hl_A;
    *hl &= 0xe;
    // CP_A(0x6);
    // RET_NC ;
    if(*hl >= 0x6)
        return;
    // INC_hl;
    // INC_hl;
    *hl -= 2;

play_sound:
    // LD_DE(SFX_POKEBALLS_PLACED_ON_TABLE);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_POKEBALLS_PLACED_ON_TABLE);
    // RET;
    return;
}

void CardFlip_UpdateCursorOAM(void){
    static const uint8_t SingleTile[] = {
        6,
        dbsprite(-1, 0, 7, 0, 0x00, 0 | PRIORITY),
        dbsprite( 0, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite( 1, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1, 0, 7, 5, 0x00, 0 | Y_FLIP | PRIORITY),
        dbsprite( 0, 0, 0, 5, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 1, 0, 0, 5, 0x03, 0 | PRIORITY),
    };

    static const uint8_t PokeGroup[] = {
        26,
        dbsprite(-1,  0, 7, 0, 0x00, 0 | PRIORITY),
        dbsprite( 0,  0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite( 1,  0, 0, 0, 0x00, 0 | X_FLIP | PRIORITY),
        dbsprite(-1,  1, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  1, 0, 0, 0x01, 0 | X_FLIP | PRIORITY),
        dbsprite(-1,  2, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  2, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  3, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  3, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  4, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  4, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  5, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  5, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  6, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  6, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  7, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  7, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  8, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  8, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  9, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  9, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1, 10, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1, 10, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1, 10, 7, 1, 0x00, 0 | Y_FLIP | PRIORITY),
        dbsprite( 0, 10, 0, 1, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 1, 10, 0, 1, 0x03, 0 | PRIORITY),
    };

    static const uint8_t NumGroup[] = {
        20,
        dbsprite(-1, 0, 7, 0, 0x00, 0 | PRIORITY),
        dbsprite( 0, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite( 1, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite( 2, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite( 4, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 5, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite( 6, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 7, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite( 8, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1, 0, 7, 5, 0x00, 0 | Y_FLIP | PRIORITY),
        dbsprite( 0, 0, 0, 5, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 1, 0, 0, 5, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 2, 0, 0, 5, 0x03, 0 | PRIORITY),
        dbsprite( 3, 0, 0, 5, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 4, 0, 0, 5, 0x03, 0 | PRIORITY),
        dbsprite( 5, 0, 0, 5, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 6, 0, 0, 5, 0x03, 0 | PRIORITY),
        dbsprite( 7, 0, 0, 5, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 8, 0, 0, 5, 0x03, 0 | PRIORITY),
    };

    static const uint8_t NumGroupPair[] = {
        30,
        dbsprite(0, 0, 0, 0, 0x00, 0 | PRIORITY),
        dbsprite(1, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite(2, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite(3, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(4, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite(5, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(6, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite(7, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(8, 0, 0, 0, 0x02, 0 | PRIORITY),
        dbsprite(9, 0, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(0, 1, 0, 0, 0x01, 0 | PRIORITY),
        dbsprite(3, 1, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(5, 1, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(7, 1, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(9, 1, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(0, 2, 0, 0, 0x01, 0 | PRIORITY),
        dbsprite(3, 2, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(5, 2, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(7, 2, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(9, 2, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(0, 2, 0, 1, 0x00, 0 | Y_FLIP | PRIORITY),
        dbsprite(1, 2, 0, 1, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite(2, 2, 0, 1, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite(3, 2, 0, 1, 0x03, 0 | PRIORITY),
        dbsprite(4, 2, 0, 1, 0x03, 0 | PRIORITY),
        dbsprite(5, 2, 0, 1, 0x03, 0 | PRIORITY),
        dbsprite(6, 2, 0, 1, 0x03, 0 | PRIORITY),
        dbsprite(7, 2, 0, 1, 0x03, 0 | PRIORITY),
        dbsprite(8, 2, 0, 1, 0x03, 0 | PRIORITY),
        dbsprite(9, 2, 0, 1, 0x03, 0 | PRIORITY),
    };

    static const uint8_t PokeGroupPair[] = {
        38,
        dbsprite(-1,  0, 7, 0, 0x00, 0 | PRIORITY),
        dbsprite( 3,  0, 0, 0, 0x00, 0 | X_FLIP | PRIORITY),
        dbsprite(-1,  1, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 3,  1, 0, 0, 0x01, 0 | X_FLIP | PRIORITY),
        dbsprite(-1,  2, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 3,  2, 0, 0, 0x01, 0 | X_FLIP | PRIORITY),
        dbsprite(-1,  3, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  3, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3,  3, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  4, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  4, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3,  4, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  5, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  5, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3,  5, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  6, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  6, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3,  6, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  7, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  7, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3,  7, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  8, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  8, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3,  8, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1,  9, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1,  9, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3,  9, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1, 10, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1, 10, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3, 10, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1, 11, 7, 0, 0x01, 0 | PRIORITY),
        dbsprite( 1, 11, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite( 3, 11, 0, 0, 0x03, 0 | PRIORITY),
        dbsprite(-1, 11, 7, 1, 0x00, 0 | Y_FLIP | PRIORITY),
        dbsprite( 0, 11, 0, 1, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 1, 11, 0, 1, 0x03, 0 | Y_FLIP | PRIORITY),
        dbsprite( 2, 11, 0, 1, 0x02, 0 | Y_FLIP | PRIORITY),
        dbsprite( 3, 11, 0, 1, 0x03, 0 | X_FLIP | Y_FLIP | PRIORITY),
    };

    static const uint8_t Impossible[] = {
        4,
        dbsprite(0, 0, 0, 0, 0x00, 0 | PRIORITY),
        dbsprite(1, 0, 0, 0, 0x00, 0 | X_FLIP | PRIORITY),
        dbsprite(0, 1, 0, 0, 0x00, 0 | Y_FLIP | PRIORITY),
        dbsprite(1, 1, 0, 0, 0x00, 0 | X_FLIP | Y_FLIP | PRIORITY),
    };

    struct CardFlipCursor {
        uint8_t x;
        uint8_t y;
        const uint8_t* data;
    };
// cardflip_cursor: MACRO
// if _NARG >= 5
//     dbpixel \1, \2, \3, \4
//     dw \5
// else
//     dbpixel \1, \2
//     dw \3
// endc
// ENDM
    #define cardflip_cursor2(_x, _y, _d)           {dbpixel2(_x, _y),           _d}
    #define cardflip_cursor4(_x, _y, _x2, _y2, _d) {dbpixel4(_x, _y, _x2, _y2), _d}

    static const struct CardFlipCursor OAMData[] = {
        cardflip_cursor2(11, 2, Impossible),
        cardflip_cursor2(12, 2, Impossible),
        cardflip_cursor2(13, 2, PokeGroupPair),
        cardflip_cursor2(13, 2, PokeGroupPair),
        cardflip_cursor2(17, 2, PokeGroupPair),
        cardflip_cursor2(17, 2, PokeGroupPair),

        cardflip_cursor2(11, 3, Impossible),
        cardflip_cursor2(12, 3, Impossible),
        cardflip_cursor2(13, 3, PokeGroup),
        cardflip_cursor2(15, 3, PokeGroup),
        cardflip_cursor2(17, 3, PokeGroup),
        cardflip_cursor2(19, 3, PokeGroup),

        cardflip_cursor2(11, 5, NumGroupPair),
        cardflip_cursor2(12, 5, NumGroup),
        cardflip_cursor2(13, 5, SingleTile),
        cardflip_cursor2(15, 5, SingleTile),
        cardflip_cursor2(17, 5, SingleTile),
        cardflip_cursor2(19, 5, SingleTile),

        cardflip_cursor2(11, 5, NumGroupPair),
        cardflip_cursor4(12, 6, 0, 4, NumGroup),
        cardflip_cursor4(13, 6, 0, 4, SingleTile),
        cardflip_cursor4(15, 6, 0, 4, SingleTile),
        cardflip_cursor4(17, 6, 0, 4, SingleTile),
        cardflip_cursor4(19, 6, 0, 4, SingleTile),

        cardflip_cursor2(11, 8, NumGroupPair),
        cardflip_cursor2(12, 8, NumGroup),
        cardflip_cursor2(13, 8, SingleTile),
        cardflip_cursor2(15, 8, SingleTile),
        cardflip_cursor2(17, 8, SingleTile),
        cardflip_cursor2(19, 8, SingleTile),

        cardflip_cursor2(11, 8, NumGroupPair),
        cardflip_cursor4(12, 9, 0, 4, NumGroup),
        cardflip_cursor4(13, 9, 0, 4, SingleTile),
        cardflip_cursor4(15, 9, 0, 4, SingleTile),
        cardflip_cursor4(17, 9, 0, 4, SingleTile),
        cardflip_cursor4(19, 9, 0, 4, SingleTile),

        cardflip_cursor2(11, 11, NumGroupPair),
        cardflip_cursor2(12, 11, NumGroup),
        cardflip_cursor2(13, 11, SingleTile),
        cardflip_cursor2(15, 11, SingleTile),
        cardflip_cursor2(17, 11, SingleTile),
        cardflip_cursor2(19, 11, SingleTile),

        cardflip_cursor2(11, 11, NumGroupPair),
        cardflip_cursor4(12, 12, 0, 4, NumGroup),
        cardflip_cursor4(13, 12, 0, 4, SingleTile),
        cardflip_cursor4(15, 12, 0, 4, SingleTile),
        cardflip_cursor4(17, 12, 0, 4, SingleTile),
        cardflip_cursor4(19, 12, 0, 4, SingleTile),
    };
    // CALL(aClearSprites);
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto skip;
    // LDH_A_addr(hVBlankCounter);
    // AND_A(0x4);
    // RET_NZ ;
    if(hram->hCGB == 0 && (hram->hVBlankCounter & 0x4) != 0)
        return;

// skip:
    // CALL(aCollapseCursorPosition);
    uint16_t position = CollapseCursorPosition();
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(mCardFlip_UpdateCursorOAM_OAMData);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aCardFlip_CopyOAM);
    CardFlip_CopyOAM(OAMData[position].data, OAMData[position].y, OAMData[position].x);
    // RET;
}

void CardFlip_InitAttrPals(void){
    static const char palettes[] = "gfx/card_flip/card_flip.pal";
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram->hCGB == 0)
        return;

    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wAttrmap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x0);

    // hlcoord(12, 1, wAttrmap);
    // LD_BC((2 << 8) | 2);
    // LD_A(0x1);
    // CALL(aCardFlip_FillBox);
    CardFlip_FillBox(coord(12, 1, wram->wAttrmap), 2, 2, 0x1);

    // hlcoord(14, 1, wAttrmap);
    // LD_BC((2 << 8) | 2);
    // LD_A(0x2);
    // CALL(aCardFlip_FillBox);
    CardFlip_FillBox(coord(14, 1, wram->wAttrmap), 2, 2, 0x2);

    // hlcoord(16, 1, wAttrmap);
    // LD_BC((2 << 8) | 2);
    // LD_A(0x3);
    // CALL(aCardFlip_FillBox);
    CardFlip_FillBox(coord(16, 1, wram->wAttrmap), 2, 2, 0x3);

    // hlcoord(18, 1, wAttrmap);
    // LD_BC((2 << 8) | 2);
    // LD_A(0x4);
    // CALL(aCardFlip_FillBox);
    CardFlip_FillBox(coord(18, 1, wram->wAttrmap), 2, 2, 0x4);

    // hlcoord(9, 0, wAttrmap);
    // LD_BC((12 << 8) | 1);
    // LD_A(0x1);
    // CALL(aCardFlip_FillBox);
    CardFlip_FillBox(coord(9, 0, wram->wAttrmap), 12, 1, 0x1);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);
    // LD_HL(mCardFlip_InitAttrPals_palettes);
    // LD_DE(wBGPals1);
    // LD_BC(9 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    LoadPaletteAssetColorsToArray(wram->wBGPals1, palettes, 0, 9 * NUM_PAL_COLORS);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

const char CardFlipLZ03[] = "gfx/card_flip/card_flip_3.png";
const char CardFlipOffButtonGFX[] = "gfx/card_flip/off.png";
const char CardFlipOnButtonGFX[] = "gfx/card_flip/on.png";
const char CardFlipLZ01[] = "gfx/card_flip/card_flip_1.png";
const char CardFlipLZ02[] = "gfx/card_flip/card_flip_2.png";
const char CardFlipTilemap[] = "gfx/card_flip/card_flip.tilemap";
