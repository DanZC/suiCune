#include "../../constants.h"
#include "tmhm.h"
#include "tmhm2.h"
#include "items.h"
#include "../pokemon/party_menu.h"
#include "../pokemon/print_move_description.h"
#include "../pokemon/knows_move.h"
#include "../pokemon/learn.h"
#include "../events/happiness_egg.h"
#include "../../home/menu.h"
#include "../../home/tilemap.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/audio.h"
#include "../../home/text.h"
#include "../../home/print_text.h"
#include "../../home/names.h"
#include "../../home/copy_name.h"
#include "../../home/pokemon.h"
#include "../../data/text/common.h"
#include "../../mobile/mobile_41.h"

static void TMHMPocket_ConvertItemToTMHMNumber(void){
    // LD_A_addr(wCurItem);
    // LD_C_A;
    // CALLFAR(aGetNumberedTMHM);
    // LD_A_C;
    // LD_addr_A(wCurItem);
    wram->wCurItem = GetNumberedTMHM_Conv(wram->wCurItem);
    // RET;
}

void TMHMPocket(void){
    TMHMPocket_Conv();
}

bool TMHMPocket_Conv(void){
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // CALL(aTMHM_PocketLoop);
    bool exit = TMHM_PocketLoop_Conv();
    // LD_A(0x0);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x0;
    // RET_NC ;
    if(!exit)
        return false;
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor_Conv();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_A_addr(wCurItem);
    // DEC_A;
    // LD_addr_A(wCurItemQuantity);
    wram->wCurItemQuantity = wram->wCurItem - 1;
    // LD_HL(wTMsHMs);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wItemQuantity);
    wram->wItemQuantity = wram->wTMsHMs[wram->wCurItemQuantity];
    // CALL(aTMHMPocket_ConvertItemToTMHMNumber);
    TMHMPocket_ConvertItemToTMHMNumber();
    // SCF;
    // RET;
    return true;
}

void ConvertCurItemIntoCurTMHM(void){
    // LD_A_addr(wCurItem);
    // LD_C_A;
    // CALLFAR(aGetTMHMNumber);
    // LD_A_C;
    // LD_addr_A(wTempTMHM);
    wram->wTempTMHM = GetTMHMNumber_Conv(wram->wCurItem);
    // RET;

}

void GetTMHMItemMove(void){
    // CALL(aConvertCurItemIntoCurTMHM);
    ConvertCurItemIntoCurTMHM();
    // PREDEF(pGetTMHMMove);
    wram->wTempTMHM = GetTMHMMove_Conv(wram->wTempTMHM);
    // RET;
}

move_t GetTMHMItemMove_Conv(item_t item){
    // CALL(aConvertCurItemIntoCurTMHM);
    // PREDEF(pGetTMHMMove);
    return GetTMHMMove_Conv(GetTMHMNumber_Conv(item));
    // RET;
}

bool AskTeachTMHM(void){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // RES_hl(NO_TEXT_SCROLL);
    bit_reset(wram->wOptions, NO_TEXT_SCROLL);
    // LD_A_addr(wCurItem);
    // CP_A(TM01);
    // IF_C goto NotTMHM;
    bool quit = true;
    if(wram->wCurItem >= TM01){
        // CALL(aGetTMHMItemMove);
        // LD_A_addr(wTempTMHM);
        // LD_addr_A(wPutativeTMHMMove);
        wram->wPutativeTMHMMove = GetTMHMItemMove_Conv(wram->wCurItem);
        // CALL(aGetMoveName);
        // CALL(aCopyName1);
        CopyName1(GetMoveName(wram->wPutativeTMHMMove));
        // LD_HL(mBootedTMText);  // Booted up a TM
        // LD_A_addr(wCurItem);
        // CP_A(HM01);
        // IF_C goto TM;
        // LD_HL(mBootedHMText);  // Booted up an HM

    // TM:
        // CALL(aPrintText);
        PrintText_Conv2((wram->wCurItem < HM01)? BootedTMText: BootedHMText);
        // LD_HL(mContainedMoveText);
        // CALL(aPrintText);
        PrintText_Conv2(ContainedMoveText);
        // CALL(aYesNoBox);
        quit = !YesNoBox_Conv();
    }

// NotTMHM:
    // POP_BC;
    // LD_A_B;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;
    return quit;
}

u8_flag_s ChooseMonToLearnTMHM(void){
    // LD_HL(wStringBuffer2);
    // LD_DE(wTMHMMoveNameBackup);
    // LD_BC(MOVE_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes(wram->wTMHMMoveNameBackup, wram->wStringBuffer2, MOVE_NAME_LENGTH - 1);
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    return ChooseMonToLearnTMHM_NoRefresh();
}

u8_flag_s ChooseMonToLearnTMHM_NoRefresh(void){
    // FARCALL(aLoadPartyMenuGFX);
    LoadPartyMenuGFX();
    // FARCALL(aInitPartyMenuWithCancel);
    InitPartyMenuWithCancel();
    // FARCALL(aInitPartyMenuGFX);
    InitPartyMenuGFX();
    // LD_A(PARTYMENUACTION_TEACH_TMHM);
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = PARTYMENUACTION_TEACH_TMHM;

    while(1) {
    // loopback:
        // FARCALL(aWritePartyMenuTilemap);
        WritePartyMenuTilemap();
        // FARCALL(aPrintPartyMenuText);
        PrintPartyMenuText();
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // CALL(aSetPalettes);
        SetPalettes_Conv();
        // CALL(aDelayFrame);
        DelayFrame();
        // FARCALL(aPartyMenuSelect);
        u8_flag_s res = PartyMenuSelect();
        // PUSH_AF;
        // LD_A_addr(wCurPartySpecies);
        // CP_A(EGG);
        // POP_BC;  // now contains the former contents of af
        // IF_Z goto egg;
        if(wram->wCurPartySpecies != EGG) {
            // PUSH_BC;
            // LD_HL(wTMHMMoveNameBackup);
            // LD_DE(wStringBuffer2);
            // LD_BC(MOVE_NAME_LENGTH - 1);
            // CALL(aCopyBytes);
            CopyBytes(wram->wStringBuffer2, wram->wTMHMMoveNameBackup, MOVE_NAME_LENGTH - 1);
            // POP_AF;  // now contains the original contents of af
            // RET;
            return res;
        }
    // egg:
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // PUSH_AF;
        // LD_DE(SFX_WRONG);
        // CALL(aPlaySFX);
        PlaySFX(SFX_WRONG);
        // CALL(aWaitSFX);
        WaitSFX();
        // POP_AF;
        // POP_BC;
        // POP_DE;
        // POP_HL;
        // goto loopback;
    }
}

void TeachTMHM(void){
    // PREDEF(pCanLearnTMHMMove);
    uint8_t c = CanLearnTMHMMove_Conv(wram->wCurSpecies, wram->wPutativeTMHMMove);

    // PUSH_BC;
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetNickname);
    GetNickname_Conv(wram->wPartyMonNickname[0], wram->wCurPartyMon);
    // POP_BC;

    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto compatible;
    if(c == 0){
        // PUSH_DE;
        // LD_DE(SFX_WRONG);
        // CALL(aPlaySFX);
        PlaySFX(SFX_WRONG);
        // POP_DE;
        // LD_HL(mTMHMNotCompatibleText);
        // CALL(aPrintText);
        PrintText_Conv2(TMHMNotCompatibleText);
        // goto nope;
        return;
    }

// compatible:
    // CALLFAR(aKnowsMove);
    // IF_C goto nope;
    if(KnowsMove_Conv(&wram->wPartyMon[wram->wCurPartyMon].mon, wram->wPutativeTMHMMove))
        return;

    // PREDEF(pLearnMove);
    uint8_t b = LearnMove(wram->wPutativeTMHMMove);
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto nope;
    if(b == 0)
        return;

    // FARCALL(aStubbedTrainerRankings_TMsHMsTaught);
    StubbedTrainerRankings_TMsHMsTaught();
    // LD_A_addr(wCurItem);
    // CALL(aIsHM);
    // RET_C ;
    if(IsHM(wram->wCurItem))
        return;

    // LD_C(HAPPINESS_LEARNMOVE);
    // CALLFAR(aChangeHappiness);
    ChangeHappiness_Conv(HAPPINESS_LEARNMOVE);
    // CALL(aConsumeTM);
    ConsumeTM();
    // goto learned_move;

// nope:
    // AND_A_A;
    // RET;


// didnt_use:
//   //  unreferenced
    // LD_A(2);
    // LD_addr_A(wItemEffectSucceeded);

// learned_move:
    // SCF;
    // RET;
}

const txt_cmd_s BootedTMText[] = {
    text_far(v_BootedTMText)
    text_end
};

const txt_cmd_s BootedHMText[] = {
    text_far(v_BootedHMText)
    text_end
};

const txt_cmd_s ContainedMoveText[] = {
    text_far(v_ContainedMoveText)
    text_end
};

const txt_cmd_s TMHMNotCompatibleText[] = {
    text_far(v_TMHMNotCompatibleText)
    text_end
};

void TMHM_PocketLoop(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // CALL(aTMHM_DisplayPocketItems);
    uint8_t d = TMHM_DisplayPocketItems();
    // LD_A(2);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 2;
    // LD_A(7);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 7;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 7;
    // LD_A(5);
    uint8_t a = 5;
    // SUB_A_D;
    // INC_A;
    // CP_A(6);
    // IF_NZ goto okay;
    if((a - d) + 1 == 6){ // Just d == 0?
        // DEC_A;
        wram->w2DMenuNumRows = (a - d);
    }
    else {
        wram->w2DMenuNumRows = (a - d) + 1;
    }

// okay:
    // LD_addr_A(w2DMenuNumRows);
    // LD_A(0xc);
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = 0xc;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0x0;
    // LD_A(0x20);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = 0x20;
    // LD_A(A_BUTTON | B_BUTTON | D_UP | D_DOWN | D_LEFT | D_RIGHT);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = A_BUTTON | B_BUTTON | D_UP | D_DOWN | D_LEFT | D_RIGHT;
    // LD_A_addr(wTMHMPocketCursor);
    // INC_A;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wTMHMPocketCursor + 1;
    // LD_A(0x1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 0x1;
    // JR(mTMHM_ShowTMMoveDescription);
    return TMHM_ShowTMMoveDescription();
}

bool TMHM_PocketLoop_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // CALL(aTMHM_DisplayPocketItems);
    uint8_t d = TMHM_DisplayPocketItems();
    // LD_A(2);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 2;
    // LD_A(7);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 7;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(5);
    uint8_t a = 5;
    printf("Rows: %d-%d\n", a, d);
    // SUB_A_D;
    // INC_A;
    // CP_A(6);
    // IF_NZ goto okay;
    if((a - d) + 1 == 6){ // Just d == 0?
        // DEC_A;
        wram->w2DMenuNumRows = (a - d);
    }
    else {
        wram->w2DMenuNumRows = (a - d) + 1;
    }

// okay:
    // LD_addr_A(w2DMenuNumRows);
    // LD_A(0xc);
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = 0xc;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0x0;
    // LD_A(0x20);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = 0x20;
    // LD_A(A_BUTTON | B_BUTTON | D_UP | D_DOWN | D_LEFT | D_RIGHT);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = A_BUTTON | B_BUTTON | D_UP | D_DOWN | D_LEFT | D_RIGHT;
    // LD_A_addr(wTMHMPocketCursor);
    // INC_A;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wTMHMPocketCursor + 1;
    // LD_A(0x1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 0x1;
    // JR(mTMHM_ShowTMMoveDescription);
    while(1){
    TMHM_ShowTMMoveDescription:
        // CALL(aTMHM_CheckHoveringOverCancel);
        // JP_NC (mTMHM_ExitPocket);
        if(!TMHM_CheckHoveringOverCancel())
            return TMHM_ExitPocket();
        // hlcoord(0, 12, wTilemap);
        // LD_B(4);
        // LD_C(SCREEN_WIDTH - 2);
        // CALL(aTextbox);
        Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, SCREEN_WIDTH - 2);
        // LD_A_addr(wCurItem);
        // CP_A(NUM_TMS + NUM_HMS + 1);
        // JR_NC (mTMHM_JoypadLoop);
        if(wram->wCurItem < NUM_TMS + NUM_HMS + 1){
            // LD_addr_A(wTempTMHM);
            // PREDEF(pGetTMHMMove);
            // LD_A_addr(wTempTMHM);
            // LD_addr_A(wCurSpecies);
            // hlcoord(1, 14, wTilemap);
            // CALL(aPrintMoveDescription);
            PrintMoveDescription_Conv(coord(1, 14, wram->wTilemap), GetTMHMMove_Conv(wram->wCurItem));
            // JP(mTMHM_JoypadLoop);
        }

    TMHM_JoypadLoop:
        // CALL(aTMHM_DisplayPocketItems);
        TMHM_DisplayPocketItems();
        // CALL(aStaticMenuJoypad);
        // LD_B_A;
        uint8_t b = StaticMenuJoypad_Conv();
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // LD_addr_A(wTMHMPocketCursor);
        wram->wTMHMPocketCursor = wram->wMenuCursorY - 1;
        printf("wTMHMPocketCursor: %d\n", wram->wTMHMPocketCursor);
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
        // LD_A_addr(w2DMenuFlags2);
        // BIT_A(7);
        // JP_NZ (mTMHM_ScrollPocket);
        if(bit_test(wram->w2DMenuFlags2, 7)){
        // TMHM_ScrollPocket:
            // LD_A_B;
            // BIT_A(7);
            // IF_NZ goto skip;
            if(!bit_test(b, 7)) {
                // LD_HL(wTMHMPocketScrollPosition);
                // LD_A_hl;
                // AND_A_A;
                // JP_Z (mTMHM_JoypadLoop);
                if(wram->wTMHMPocketScrollPosition == 0)
                    goto TMHM_JoypadLoop;
                // DEC_hl;
                --wram->wTMHMPocketScrollPosition;
                // CALL(aTMHM_DisplayPocketItems);
                TMHM_DisplayPocketItems();
                // JP(mTMHM_ShowTMMoveDescription);
                goto TMHM_ShowTMMoveDescription;
            }

        // skip:
            // CALL(aTMHM_GetCurrentPocketPosition);
            uint8_t c = TMHM_GetCurrentPocketPosition();
            // LD_B(5);
            uint8_t b = 5;

            do {
            // loop:
                // INC_C;
                ++c;
                // LD_A_C;
                // CP_A(NUM_TMS + NUM_HMS + 1);
                // JP_NC (mTMHM_JoypadLoop);
                if(c >= NUM_TMS + NUM_HMS + 1)
                    goto TMHM_JoypadLoop;
                // LD_A_hli;
                // AND_A_A;
                // IF_Z goto loop;
                // DEC_B;
                // IF_NZ goto loop;
            } while(wram->wTMsHMs[c-1] == 0 || --b != 0);
            // LD_HL(wTMHMPocketScrollPosition);
            // INC_hl;
            ++wram->wTMHMPocketScrollPosition;
            // CALL(aTMHM_DisplayPocketItems);
            TMHM_DisplayPocketItems();
            // JP(mTMHM_ShowTMMoveDescription);
            goto TMHM_ShowTMMoveDescription;
        }
        // LD_A_B;
        // LD_addr_A(wMenuJoypad);
        wram->wMenuJoypad = b;
        // BIT_A(A_BUTTON_F);
        // JP_NZ (mTMHM_ChooseTMorHM);
        if(bit_test(b, A_BUTTON_F))
            return TMHM_ChooseTMorHM();
        // BIT_A(B_BUTTON_F);
        // JP_NZ (mTMHM_ExitPack);
        if(bit_test(b, B_BUTTON_F))
            return TMHM_ExitPack();
        // BIT_A(D_RIGHT_F);
        // JP_NZ (mTMHM_ExitPocket);
        if(bit_test(b, D_RIGHT_F))
            return TMHM_ExitPocket();
        // BIT_A(D_LEFT_F);
        // JP_NZ (mTMHM_ExitPocket);
        if(bit_test(b, D_LEFT_F))
            return TMHM_ExitPocket();
        // return TMHM_ShowTMMoveDescription();
    }
}

void TMHM_JoypadLoop(void){
    CALL(aTMHM_DisplayPocketItems);
    CALL(aStaticMenuJoypad);
    LD_B_A;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wTMHMPocketCursor);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A_addr(w2DMenuFlags2);
    BIT_A(7);
    JP_NZ (mTMHM_ScrollPocket);
    LD_A_B;
    LD_addr_A(wMenuJoypad);
    BIT_A(A_BUTTON_F);
    JP_NZ (mTMHM_ChooseTMorHM);
    BIT_A(B_BUTTON_F);
    JP_NZ (mTMHM_ExitPack);
    BIT_A(D_RIGHT_F);
    JP_NZ (mTMHM_ExitPocket);
    BIT_A(D_LEFT_F);
    JP_NZ (mTMHM_ExitPocket);
    return TMHM_ShowTMMoveDescription();
}

void TMHM_ShowTMMoveDescription(void){
    CALL(aTMHM_CheckHoveringOverCancel);
    JP_NC (mTMHM_ExitPocket);
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(SCREEN_WIDTH - 2);
    CALL(aTextbox);
    LD_A_addr(wCurItem);
    CP_A(NUM_TMS + NUM_HMS + 1);
    JR_NC (mTMHM_JoypadLoop);
    LD_addr_A(wTempTMHM);
    PREDEF(pGetTMHMMove);
    LD_A_addr(wTempTMHM);
    LD_addr_A(wCurSpecies);
    hlcoord(1, 14, wTilemap);
    CALL(aPrintMoveDescription);
    JP(mTMHM_JoypadLoop);

}

bool TMHM_ChooseTMorHM(void){
    // CALL(aTMHM_PlaySFX_ReadText2);
    TMHM_PlaySFX_ReadText2();
    // CALL(aCountTMsHMs);  // This stores the count to wTempTMHM.
    CountTMsHMs();
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_B_A;
    // LD_A_addr(wTMHMPocketScrollPosition);
    // ADD_A_B;
    // LD_B_A;
    // LD_A_addr(wTempTMHM);
    // CP_A_B;
    // JR_Z (mv_TMHM_ExitPack);  // our cursor was hovering over CANCEL
    if(wram->wTempTMHM == (wram->wMenuCursorY - 1) + wram->wTMHMPocketScrollPosition)
        return v_TMHM_ExitPack();
    return TMHM_CheckHoveringOverCancel();
}

bool TMHM_CheckHoveringOverCancel(void){
    // CALL(aTMHM_GetCurrentPocketPosition);
    uint8_t c = TMHM_GetCurrentPocketPosition();
    // LD_A_addr(wMenuCursorY);
    // LD_B_A;
    uint8_t b = wram->wMenuCursorY;

    uint8_t a;
    do {
    // loop:
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_TMS + NUM_HMS + 1);
        // IF_NC goto okay;
        if(++c >= NUM_TMS + NUM_HMS + 1)
            break;
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto loop;
        // DEC_B;
        // IF_NZ goto loop;
    } while(wram->wTMsHMs[c-1] == 0 || --b != 0);
    // LD_A_C;
    a = c;

// okay:
    // LD_addr_A(wCurItem);
    wram->wCurItem = a;
    // CP_A(-1);
    // RET;
    return a < 0xff;
}

bool TMHM_ExitPack(void){
    // CALL(aTMHM_PlaySFX_ReadText2);
    TMHM_PlaySFX_ReadText2();
    return v_TMHM_ExitPack();
}

bool v_TMHM_ExitPack(void){
    // LD_A(0x2);
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = 0x2;
    // AND_A_A;
    // RET;
    return false;
}

bool TMHM_ExitPocket(void){
    // AND_A_A;
    // RET;
    return false;
}

void TMHM_ScrollPocket(void){
    LD_A_B;
    BIT_A(7);
    IF_NZ goto skip;
    LD_HL(wTMHMPocketScrollPosition);
    LD_A_hl;
    AND_A_A;
    JP_Z (mTMHM_JoypadLoop);
    DEC_hl;
    CALL(aTMHM_DisplayPocketItems);
    JP(mTMHM_ShowTMMoveDescription);


skip:
    CALL(aTMHM_GetCurrentPocketPosition);
    LD_B(5);

loop:
    INC_C;
    LD_A_C;
    CP_A(NUM_TMS + NUM_HMS + 1);
    JP_NC (mTMHM_JoypadLoop);
    LD_A_hli;
    AND_A_A;
    IF_Z goto loop;
    DEC_B;
    IF_NZ goto loop;
    LD_HL(wTMHMPocketScrollPosition);
    INC_hl;
    CALL(aTMHM_DisplayPocketItems);
    JP(mTMHM_ShowTMMoveDescription);

}

uint8_t TMHM_DisplayPocketItems(void){
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);
    // JP_Z (mTutorial_TMHMPocket);
    if(wram->wBattleType == BATTLETYPE_TUTORIAL)
        return Tutorial_TMHMPocket();

    // hlcoord(5, 2, wTilemap);
    // LD_BC((10 << 8) | 15);
    // LD_A(0x7f);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(5, 2, wram->wTilemap), 15, 10);
    // CALL(aTMHM_GetCurrentPocketPosition);
    uint8_t c = TMHM_GetCurrentPocketPosition();
    // LD_D(0x5);
    uint8_t d = 0x5;

    do {
        do {
        // loop2:
            // INC_C;
            ++c;
            // LD_A_C;
            // CP_A(NUM_TMS + NUM_HMS + 1);
            // IF_NC goto NotTMHM;
            if(c >= NUM_TMS + NUM_HMS + 1) {
            // NotTMHM:
                // CALL(aTMHMPocket_GetCurrentLineCoord);
                // INC_HL;
                // INC_HL;
                // INC_HL;
                // PUSH_DE;
                // LD_DE(mTMHM_CancelString);
                // CALL(aPlaceString);
                PlaceStringSimple(U82C(TMHM_CancelString), TMHMPocket_GetCurrentLineCoord(d) + 3);
                // POP_DE;
                return d;
            }
            // LD_A_hli;
            // AND_A_A;
            // IF_Z goto loop2;
        } while(wram->wTMsHMs[c-1] == 0);
        // LD_B_A;
        uint8_t b = wram->wTMsHMs[c-1];
        // LD_A_C;
        // LD_addr_A(wTempTMHM);
        wram->wTempTMHM = c;
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // CALL(aTMHMPocket_GetCurrentLineCoord);
        // PUSH_HL;
        uint8_t* lineCoord = TMHMPocket_GetCurrentLineCoord(d);
        // LD_A_addr(wTempTMHM);
        // CP_A(NUM_TMS + 1);
        // IF_NC goto HM;
        if(wram->wTempTMHM < NUM_TMS + 1){
            // LD_DE(wTempTMHM);
            // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
            // CALL(aPrintNum);
            PrintNum_Conv2(lineCoord, &wram->wTempTMHM, PRINTNUM_LEADINGZEROS | 1, 2);
            // goto okay;
        }
        else {
        // HM:
            // PUSH_AF;
            uint8_t tm = wram->wTempTMHM - NUM_TMS;
            // SUB_A(NUM_TMS);
            // LD_addr_A(wTempTMHM);
            // LD_hl(0x87);
            *lineCoord = 0x87;
            // INC_HL;
            // LD_DE(wTempTMHM);
            // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
            // CALL(aPrintNum);
            PrintNum_Conv2(lineCoord + 1, &tm, PRINTNUM_LEADINGZEROS | 1, 2);
            // POP_AF;
            // LD_addr_A(wTempTMHM);
        }

    // okay:
        // PREDEF(pGetTMHMMove);
        move_t move = GetTMHMMove_Conv(wram->wTempTMHM);
        // LD_A_addr(wNamedObjectIndex);
        // LD_addr_A(wPutativeTMHMMove);
        // CALL(aGetMoveName);
        // POP_HL;
        // LD_BC(3);
        // ADD_HL_BC;
        lineCoord += 3;
        // PUSH_HL;
        // CALL(aPlaceString);
        PlaceStringSimple(GetMoveName(move), lineCoord);
        // POP_HL;
        // POP_BC;
        // LD_A_C;
        // PUSH_BC;
        // CP_A(NUM_TMS + 1);
        // IF_NC goto hm2;
        if(c <= NUM_TMS){
            // LD_BC(SCREEN_WIDTH + 9);
            // ADD_HL_BC;
            lineCoord += SCREEN_WIDTH + 9;
            // LD_hl(0xf1);
            *lineCoord = 0xf1;
            // INC_HL;
            // LD_A(0xf6);  // why are we doing this?
            // POP_BC;
            // PUSH_BC;
            // LD_A_B;
            // LD_addr_A(wTempTMHM);
            // LD_DE(wTempTMHM);
            // LD_BC((1 << 8) | 2);
            // CALL(aPrintNum);
            PrintNum_Conv2(lineCoord + 1, &b, 1, 2);
        }

    // hm2:
        // POP_BC;
        // POP_DE;
        // POP_HL;
        // DEC_D;
        // IF_NZ goto loop2;
    } while(--d != 0);
    // goto done;

// done:
    // RET;
    return d;
}

uint8_t* TMHMPocket_GetCurrentLineCoord(uint8_t d){
    // hlcoord(5, 0, wTilemap);
    // LD_BC(2 * SCREEN_WIDTH);
    // LD_A(6);
    // SUB_A_D;
    // LD_E_A;
// AddNTimes

// loop:
    // ADD_HL_BC;
    // DEC_E;
    // IF_NZ goto loop;
    // RET;
    return coord(5, 0, wram->wTilemap) + (2 * SCREEN_WIDTH * (6 - d));
}

void PlaceMoveNameAfterTMHMName(void){
//  //  unreferenced
//  Similar to a part of TMHM_DisplayPocketItems.
    POP_HL;
    LD_BC(3);
    ADD_HL_BC;
    PREDEF(pGetTMHMMove);
    LD_A_addr(wTempTMHM);
    LD_addr_A(wPutativeTMHMMove);
    CALL(aGetMoveName);
    PUSH_HL;
    CALL(aPlaceString);
    POP_HL;
    RET;

}

const char TMHM_CancelString[] = "CANCEL@";

uint8_t TMHM_GetCurrentPocketPosition(void){
    // LD_HL(wTMsHMs);
    uint8_t* hl = wram->wTMsHMs;
    // LD_A_addr(wTMHMPocketScrollPosition);
    // LD_B_A;
    // INC_B;
    uint8_t b = wram->wTMHMPocketScrollPosition + 1;
    // LD_C(0);
    uint8_t c = 0;

    uint8_t a;
    do {
    // loop:
        // INC_C;
        c++;
        // LD_A_hli;
        a = *(hl++);
        // AND_A_A;
        // IF_Z goto loop;
        // DEC_B;
        // IF_NZ goto loop;
    } while(a == 0 || --b != 0);
    // DEC_HL;
    // DEC_C;
    // RET;
    return --c;
}

uint8_t Tutorial_TMHMPocket(void){
    // hlcoord(9, 3, wTilemap);
    // PUSH_DE;
    // LD_DE(mTMHM_CancelString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(TMHM_CancelString), coord(9, 3, wram->wTilemap));
    // POP_DE;
    // RET;
    return 0;
}

void TMHM_PlaySFX_ReadText2(void){
    // PUSH_DE;
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // POP_DE;
    // RET;
}

void VerboseReceiveTMHM(void){
//  //  unreferenced
    CALL(aConvertCurItemIntoCurTMHM);
    CALL(aVerboseReceiveTMHM_CheckHaveRoomForTMHM);
    LD_HL(mVerboseReceiveTMHM_NoRoomTMHMText);
    IF_NC goto print;
    LD_HL(mVerboseReceiveTMHM_ReceivedTMHMText);

print:
    JP(mPrintText);


NoRoomTMHMText:
    //text_far ['_NoRoomTMHMText']
    //text_end ['?']


ReceivedTMHMText:
    //text_far ['_ReceivedTMHMText']
    //text_end ['?']


CheckHaveRoomForTMHM:
    LD_A_addr(wTempTMHM);
    DEC_A;
    LD_HL(wTMsHMs);
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A_hl;
    INC_A;
    CP_A(MAX_ITEM_STACK + 1);
    RET_NC ;
    LD_hl_A;
    RET;

}

void ConsumeTM(void){
    // CALL(aConvertCurItemIntoCurTMHM);
    ConvertCurItemIntoCurTMHM();
    // LD_A_addr(wTempTMHM);
    // DEC_A;
    // LD_HL(wTMsHMs);
    // LD_B(0);
    // LD_C_A;
    // ADD_HL_BC;
    uint8_t* hl = wram->wTMsHMs + wram->wTempTMHM;
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(*hl == 0)
        return;
    // DEC_A;
    // LD_hl_A;
    // RET_NZ ;
    if(--*hl != 0)
        return;
    // LD_A_addr(wTMHMPocketScrollPosition);
    // AND_A_A;
    // RET_Z ;
    if(wram->wTMHMPocketScrollPosition == 0)
        return;
    // DEC_A;
    // LD_addr_A(wTMHMPocketScrollPosition);
    --wram->wTMHMPocketScrollPosition;
    // RET;
}

void CountTMsHMs(void){
    // LD_B(0);
    uint8_t b = 0;
    // LD_C(NUM_TMS + NUM_HMS);
    uint8_t c = NUM_TMS + NUM_HMS;
    // LD_HL(wTMsHMs);
    uint8_t* hl = wram->wTMsHMs;

    do {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto skip;
        if(*(hl++) != 0) {
            // INC_B;
            b++;
        }

    // skip:
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_A_B;
    // LD_addr_A(wTempTMHM);
    // RET;
    wram->wTempTMHM = b;
}
