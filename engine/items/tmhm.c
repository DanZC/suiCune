#include "../../constants.h"
#include "tmhm.h"
#include "tmhm2.h"
#include "items.h"
#include "../pokemon/party_menu.h"
#include "../../home/menu.h"
#include "../../home/tilemap.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/audio.h"
#include "../../data/text/common.h"

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
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    CALL(aTMHM_PocketLoop);
    // LD_A(0x0);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x0;
    // RET_NC ;
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

void AskTeachTMHM(void){
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    RES_hl(NO_TEXT_SCROLL);
    LD_A_addr(wCurItem);
    CP_A(TM01);
    IF_C goto NotTMHM;
    CALL(aGetTMHMItemMove);
    LD_A_addr(wTempTMHM);
    LD_addr_A(wPutativeTMHMMove);
    CALL(aGetMoveName);
    CALL(aCopyName1);
    LD_HL(mBootedTMText);  // Booted up a TM
    LD_A_addr(wCurItem);
    CP_A(HM01);
    IF_C goto TM;
    LD_HL(mBootedHMText);  // Booted up an HM

TM:
    CALL(aPrintText);
    LD_HL(mContainedMoveText);
    CALL(aPrintText);
    CALL(aYesNoBox);

NotTMHM:
    POP_BC;
    LD_A_B;
    LD_addr_A(wOptions);
    RET;

}

u8_flag_s ChooseMonToLearnTMHM(void){
    // LD_HL(wStringBuffer2);
    // LD_DE(wTMHMMoveNameBackup);
    // LD_BC(MOVE_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wTMHMMoveNameBackup, wram->wStringBuffer2, MOVE_NAME_LENGTH - 1);
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
            CopyBytes_Conv2(wram->wStringBuffer2, wram->wTMHMMoveNameBackup, MOVE_NAME_LENGTH - 1);
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
        PlaySFX_Conv(SFX_WRONG);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // POP_AF;
        // POP_BC;
        // POP_DE;
        // POP_HL;
        // goto loopback;
    }
}

void TeachTMHM(void){
    PREDEF(pCanLearnTMHMMove);

    PUSH_BC;
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    CALL(aGetNickname);
    POP_BC;

    LD_A_C;
    AND_A_A;
    IF_NZ goto compatible;
    PUSH_DE;
    LD_DE(SFX_WRONG);
    CALL(aPlaySFX);
    POP_DE;
    LD_HL(mTMHMNotCompatibleText);
    CALL(aPrintText);
    goto nope;


compatible:
    CALLFAR(aKnowsMove);
    IF_C goto nope;

    PREDEF(pLearnMove);
    LD_A_B;
    AND_A_A;
    IF_Z goto nope;

    FARCALL(aStubbedTrainerRankings_TMsHMsTaught);
    LD_A_addr(wCurItem);
    CALL(aIsHM);
    RET_C ;

    LD_C(HAPPINESS_LEARNMOVE);
    CALLFAR(aChangeHappiness);
    CALL(aConsumeTM);
    goto learned_move;


nope:
    AND_A_A;
    RET;


didnt_use:
//   //  unreferenced
    LD_A(2);
    LD_addr_A(wItemEffectSucceeded);

learned_move:
    SCF;
    RET;

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
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aTMHM_DisplayPocketItems);
    LD_A(2);
    LD_addr_A(w2DMenuCursorInitY);
    LD_A(7);
    LD_addr_A(w2DMenuCursorInitX);
    LD_A(1);
    LD_addr_A(w2DMenuNumCols);
    LD_A(5);
    SUB_A_D;
    INC_A;
    CP_A(6);
    IF_NZ goto okay;
    DEC_A;

okay:
    LD_addr_A(w2DMenuNumRows);
    LD_A(0xc);
    LD_addr_A(w2DMenuFlags1);
    XOR_A_A;
    LD_addr_A(w2DMenuFlags2);
    LD_A(0x20);
    LD_addr_A(w2DMenuCursorOffsets);
    LD_A(A_BUTTON | B_BUTTON | D_UP | D_DOWN | D_LEFT | D_RIGHT);
    LD_addr_A(wMenuJoypadFilter);
    LD_A_addr(wTMHMPocketCursor);
    INC_A;
    LD_addr_A(wMenuCursorY);
    LD_A(0x1);
    LD_addr_A(wMenuCursorX);
    JR(mTMHM_ShowTMMoveDescription);

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

void TMHM_ChooseTMorHM(void){
    CALL(aTMHM_PlaySFX_ReadText2);
    CALL(aCountTMsHMs);  // This stores the count to wTempTMHM.
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_B_A;
    LD_A_addr(wTMHMPocketScrollPosition);
    ADD_A_B;
    LD_B_A;
    LD_A_addr(wTempTMHM);
    CP_A_B;
    JR_Z (mv_TMHM_ExitPack);  // our cursor was hovering over CANCEL
    return TMHM_CheckHoveringOverCancel();
}

void TMHM_CheckHoveringOverCancel(void){
    CALL(aTMHM_GetCurrentPocketPosition);
    LD_A_addr(wMenuCursorY);
    LD_B_A;

loop:
    INC_C;
    LD_A_C;
    CP_A(NUM_TMS + NUM_HMS + 1);
    IF_NC goto okay;
    LD_A_hli;
    AND_A_A;
    IF_Z goto loop;
    DEC_B;
    IF_NZ goto loop;
    LD_A_C;

okay:
    LD_addr_A(wCurItem);
    CP_A(-1);
    RET;

}

void TMHM_ExitPack(void){
    CALL(aTMHM_PlaySFX_ReadText2);
    return v_TMHM_ExitPack();
}

void v_TMHM_ExitPack(void){
    LD_A(0x2);
    LD_addr_A(wMenuJoypad);
    AND_A_A;
    RET;

}

void TMHM_ExitPocket(void){
    AND_A_A;
    RET;

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

void TMHM_DisplayPocketItems(void){
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    JP_Z (mTutorial_TMHMPocket);

    hlcoord(5, 2, wTilemap);
    LD_BC((10 << 8) | 15);
    LD_A(0x7f);
    CALL(aClearBox);
    CALL(aTMHM_GetCurrentPocketPosition);
    LD_D(0x5);

loop2:
    INC_C;
    LD_A_C;
    CP_A(NUM_TMS + NUM_HMS + 1);
    IF_NC goto NotTMHM;
    LD_A_hli;
    AND_A_A;
    IF_Z goto loop2;
    LD_B_A;
    LD_A_C;
    LD_addr_A(wTempTMHM);
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aTMHMPocket_GetCurrentLineCoord);
    PUSH_HL;
    LD_A_addr(wTempTMHM);
    CP_A(NUM_TMS + 1);
    IF_NC goto HM;
    LD_DE(wTempTMHM);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    goto okay;


HM:
    PUSH_AF;
    SUB_A(NUM_TMS);
    LD_addr_A(wTempTMHM);
    LD_hl(0x87);
    INC_HL;
    LD_DE(wTempTMHM);
    LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
    CALL(aPrintNum);
    POP_AF;
    LD_addr_A(wTempTMHM);

okay:
    PREDEF(pGetTMHMMove);
    LD_A_addr(wNamedObjectIndex);
    LD_addr_A(wPutativeTMHMMove);
    CALL(aGetMoveName);
    POP_HL;
    LD_BC(3);
    ADD_HL_BC;
    PUSH_HL;
    CALL(aPlaceString);
    POP_HL;
    POP_BC;
    LD_A_C;
    PUSH_BC;
    CP_A(NUM_TMS + 1);
    IF_NC goto hm2;
    LD_BC(SCREEN_WIDTH + 9);
    ADD_HL_BC;
    LD_hl(0xf1);
    INC_HL;
    LD_A(0xf6);  // why are we doing this?
    POP_BC;
    PUSH_BC;
    LD_A_B;
    LD_addr_A(wTempTMHM);
    LD_DE(wTempTMHM);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);

hm2:
    POP_BC;
    POP_DE;
    POP_HL;
    DEC_D;
    IF_NZ goto loop2;
    goto done;


NotTMHM:
    CALL(aTMHMPocket_GetCurrentLineCoord);
    INC_HL;
    INC_HL;
    INC_HL;
    PUSH_DE;
    LD_DE(mTMHM_CancelString);
    CALL(aPlaceString);
    POP_DE;

done:
    RET;

}

void TMHMPocket_GetCurrentLineCoord(void){
    hlcoord(5, 0, wTilemap);
    LD_BC(2 * SCREEN_WIDTH);
    LD_A(6);
    SUB_A_D;
    LD_E_A;
// AddNTimes

loop:
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    RET;

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

void TMHM_CancelString(void){
    //db ['"CANCEL@"'];

    return TMHM_GetCurrentPocketPosition();
}

void TMHM_GetCurrentPocketPosition(void){
    LD_HL(wTMsHMs);
    LD_A_addr(wTMHMPocketScrollPosition);
    LD_B_A;
    INC_B;
    LD_C(0);

loop:
    INC_C;
    LD_A_hli;
    AND_A_A;
    IF_Z goto loop;
    DEC_B;
    IF_NZ goto loop;
    DEC_HL;
    DEC_C;
    RET;

}

void Tutorial_TMHMPocket(void){
    hlcoord(9, 3, wTilemap);
    PUSH_DE;
    LD_DE(mTMHM_CancelString);
    CALL(aPlaceString);
    POP_DE;
    RET;

}

void TMHM_PlaySFX_ReadText2(void){
    PUSH_DE;
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    POP_DE;
    RET;

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
    CALL(aConvertCurItemIntoCurTMHM);
    LD_A_addr(wTempTMHM);
    DEC_A;
    LD_HL(wTMsHMs);
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_hl_A;
    RET_NZ ;
    LD_A_addr(wTMHMPocketScrollPosition);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wTMHMPocketScrollPosition);
    RET;

}

void CountTMsHMs(void){
    LD_B(0);
    LD_C(NUM_TMS + NUM_HMS);
    LD_HL(wTMsHMs);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto skip;
    INC_B;

skip:
    DEC_C;
    IF_NZ goto loop;
    LD_A_B;
    LD_addr_A(wTempTMHM);
    RET;

}
