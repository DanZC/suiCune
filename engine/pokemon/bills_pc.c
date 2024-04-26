#include "../../constants.h"
#include "bills_pc.h"
#include "../gfx/load_pics.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"

void v_DepositPKMN(void){
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    LD_A_addr(wVramState);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wVramState);
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    CALL(aBillsPC_InitRAM);
    XOR_A_A;
    LD_addr_A(wBillsPC_LoadedBox);
    CALL(aDelayFrame);

loop:
    CALL(aJoyTextDelay);
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto done;
    CALL(av_DepositPKMN_RunJumptable);
    CALL(aDelayFrame);
    goto loop;

done:
    CALL(aClearSprites);
    POP_AF;
    LDH_addr_A(hInMenu);
    POP_AF;
    LD_addr_A(wVramState);
    POP_AF;
    LD_addr_A(wOptions);
    RET;


RunJumptable:
    LD_A_addr(wJumptableIndex);
    LD_HL(mv_DepositPKMN_Jumptable);
    CALL(aBillsPC_Jumptable);
    JP_hl;


Jumptable:
    //dw ['.Init'];
    //dw ['.HandleJoypad'];
    //dw ['.WhatsUp'];
    //dw ['.Submenu'];
    //dw ['BillsPC_EndJumptableLoop'];


Init:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aClearSprites);
    CALL(aCopyBoxmonSpecies);
    CALL(aBillsPC_BoxName);
    LD_DE(mPCString_ChooseaPKMN);
    CALL(aBillsPC_PlaceString);
    LD_A(0x5);
    LD_addr_A(wBillsPC_NumMonsOnScreen);
    CALL(aBillsPC_RefreshTextboxes);
    CALL(aPCMonInfo);
    LD_A(0xff);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    CALL(aWaitBGMap);
    CALL(aBillsPC_UpdateSelectionCursor);
    CALL(aBillsPC_IncrementJumptableIndex);
    RET;


HandleJoypad:
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto b_button;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto a_button;
    CALL(aWithdraw_UpDown);
    AND_A_A;
    RET_Z ;
    CALL(aBillsPC_UpdateSelectionCursor);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aBillsPC_RefreshTextboxes);
    CALL(aPCMonInfo);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    RET;


a_button:
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    AND_A_A;
    RET_Z ;
    CP_A(-1);
    IF_Z goto b_button;
    LD_A(0x2);
    LD_addr_A(wJumptableIndex);
    RET;


go_back:
//   //  unreferenced
    LD_HL(wJumptableIndex);
    DEC_hl;
    RET;


b_button:
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    RET;


WhatsUp:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aClearSprites);
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    LD_DE(mPCString_WhatsUp);
    CALL(aBillsPC_PlaceString);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    CALL(aBillsPC_IncrementJumptableIndex);
    RET;


Submenu:
    LD_HL(mBillsPCDepositMenuHeader);
    CALL(aCopyMenuHeader);
    LD_A_addr(wMenuCursorY);
    CALL(aStoreMenuCursorPosition);
    CALL(aVerticalMenu);
    JP_C (mBillsPCDepositFuncCancel);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    AND_A(0b11);
    LD_E_A;
    LD_D(0);
    LD_HL(mBillsPCDepositJumptable);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;

}

void BillsPCDepositJumptable(void){
    //dw ['BillsPCDepositFuncDeposit'];  // Deposit Pokemon
    //dw ['BillsPCDepositFuncStats'];  // Pokemon Stats
    //dw ['BillsPCDepositFuncRelease'];  // Release Pokemon
    //dw ['BillsPCDepositFuncCancel'];  // Cancel

    return BillsPCDepositFuncDeposit();
}

void BillsPCDepositFuncDeposit(void){
    CALL(aBillsPC_CheckMail_PreventBlackout);
    JP_C (mBillsPCDepositFuncCancel);
    CALL(aDepositPokemon);
    IF_C goto box_full;
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    XOR_A_A;
    LD_addr_A(wBillsPC_CursorPosition);
    LD_addr_A(wBillsPC_ScrollPosition);
    RET;


box_full:
    LD_DE(mPCString_WhatsUp);
    CALL(aBillsPC_PlaceString);
    RET;

}

void BillsPCDepositFuncStats(void){
    CALL(aLoadStandardMenuHeader);
    CALL(aBillsPC_StatsScreen);
    CALL(aExitMenu);
    CALL(aPCMonInfo);
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    RET;

}

void BillsPCDepositFuncRelease(void){
    CALL(aBillsPC_CheckMail_PreventBlackout);
    JR_C (mBillsPCDepositFuncCancel);
    CALL(aBillsPC_IsMonAnEgg);
    JR_C (mBillsPCDepositFuncCancel);
    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    LD_DE(mPCString_ReleasePKMN);
    CALL(aBillsPC_PlaceString);
    CALL(aLoadStandardMenuHeader);
    LD_BC((14 << 8) | 11);
    CALL(aPlaceYesNoBox);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    CALL(aExitMenu);
    AND_A_A;
    IF_NZ goto failed_release;
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    CALL(aReleasePKMN_ByePKMN);
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    XOR_A_A;
    LD_addr_A(wBillsPC_CursorPosition);
    LD_addr_A(wBillsPC_ScrollPosition);
    POP_AF;
    RET;


failed_release:
    LD_DE(mPCString_WhatsUp);
    CALL(aBillsPC_PlaceString);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    RET;

}

void BillsPCDepositFuncCancel(void){
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    RET;

}

void BillsPCDepositMenuHeader(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['9', '4', 'SCREEN_WIDTH - 1', '13'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['4'];  // items
    //db ['"DEPOSIT@"'];
    //db ['"STATS@"'];
    //db ['"RELEASE@"'];
    //db ['"CANCEL@"'];

    return BillsPCClearThreeBoxes();
}

void BillsPCClearThreeBoxes(void){
//  //  unreferenced
    hlcoord(0, 0, wTilemap);
    LD_B(4);
    LD_C(8);
    CALL(aClearBox);
    hlcoord(0, 4, wTilemap);
    LD_B(10);
    LD_C(9);
    CALL(aClearBox);
    hlcoord(0, 14, wTilemap);
    LD_B(2);
    LD_C(8);
    CALL(aClearBox);
    RET;

}

void v_WithdrawPKMN(void){
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    LD_A_addr(wVramState);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wVramState);
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    CALL(aBillsPC_InitRAM);
    LD_A(NUM_BOXES + 1);
    LD_addr_A(wBillsPC_LoadedBox);
    CALL(aDelayFrame);

loop:
    CALL(aJoyTextDelay);
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto done;
    CALL(av_WithdrawPKMN_RunJumptable);
    CALL(aDelayFrame);
    goto loop;

done:
    CALL(aClearSprites);
    POP_AF;
    LDH_addr_A(hInMenu);
    POP_AF;
    LD_addr_A(wVramState);
    POP_AF;
    LD_addr_A(wOptions);
    RET;


RunJumptable:
    LD_A_addr(wJumptableIndex);
    LD_HL(mv_WithdrawPKMN_Jumptable);
    CALL(aBillsPC_Jumptable);
    JP_hl;


Jumptable:
    //dw ['.Init'];
    //dw ['.Joypad'];
    //dw ['.PrepSubmenu'];
    //dw ['BillsPC_Withdraw'];
    //dw ['BillsPC_EndJumptableLoop'];


Init:
    LD_A(NUM_BOXES + 1);
    LD_addr_A(wBillsPC_LoadedBox);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aClearSprites);
    CALL(aCopyBoxmonSpecies);
    CALL(aBillsPC_BoxName);
    LD_DE(mPCString_ChooseaPKMN);
    CALL(aBillsPC_PlaceString);
    LD_A(0x5);
    LD_addr_A(wBillsPC_NumMonsOnScreen);
    CALL(aBillsPC_RefreshTextboxes);
    CALL(aPCMonInfo);
    LD_A(0xff);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    CALL(aWaitBGMap);
    CALL(aBillsPC_UpdateSelectionCursor);
    CALL(aBillsPC_IncrementJumptableIndex);
    RET;


Joypad:
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto b_button;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto a_button;
    CALL(aWithdraw_UpDown);
    AND_A_A;
    RET_Z ;
    CALL(aBillsPC_UpdateSelectionCursor);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aBillsPC_RefreshTextboxes);
    CALL(aPCMonInfo);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    RET;

a_button:
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    AND_A_A;
    RET_Z ;
    CP_A(-1);
    IF_Z goto b_button;
    LD_A(0x2);
    LD_addr_A(wJumptableIndex);
    RET;


go_back:
//   //  unreferenced
    LD_HL(wJumptableIndex);
    DEC_hl;
    RET;


b_button:
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    RET;


PrepSubmenu:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aClearSprites);
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    LD_DE(mPCString_WhatsUp);
    CALL(aBillsPC_PlaceString);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    CALL(aBillsPC_IncrementJumptableIndex);
    RET;

}

void BillsPC_Withdraw(void){
    LD_HL(mBillsPC_Withdraw_MenuHeader);
    CALL(aCopyMenuHeader);
    LD_A_addr(wMenuCursorY);
    CALL(aStoreMenuCursorPosition);
    CALL(aVerticalMenu);
    JP_C (mBillsPC_Withdraw_cancel);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    AND_A(0b11);
    LD_E_A;
    LD_D(0);
    LD_HL(mBillsPC_Withdraw_dw);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


dw:
    //dw ['.withdraw'];  // Withdraw
    //dw ['.stats'];  // Stats
    //dw ['.release'];  // Release
    //dw ['.cancel'];  // Cancel


withdraw:
    CALL(aBillsPC_CheckMail_PreventBlackout);
    JP_C (mBillsPC_Withdraw_cancel);
    CALL(aTryWithdrawPokemon);
    IF_C goto FailedWithdraw;
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    XOR_A_A;
    LD_addr_A(wBillsPC_CursorPosition);
    LD_addr_A(wBillsPC_ScrollPosition);
    RET;

FailedWithdraw:
    LD_DE(mPCString_WhatsUp);
    CALL(aBillsPC_PlaceString);
    RET;


stats:
    CALL(aLoadStandardMenuHeader);
    CALL(aBillsPC_StatsScreen);
    CALL(aExitMenu);
    CALL(aPCMonInfo);
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    RET;


release:
    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    CALL(aBillsPC_IsMonAnEgg);
    IF_C goto FailedRelease;
    LD_DE(mPCString_ReleasePKMN);
    CALL(aBillsPC_PlaceString);
    CALL(aLoadStandardMenuHeader);
    LD_BC((14 << 8) | 11);
    CALL(aPlaceYesNoBox);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    CALL(aExitMenu);
    AND_A_A;
    IF_NZ goto FailedRelease;
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_A(REMOVE_BOX);
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    CALL(aReleasePKMN_ByePKMN);
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    XOR_A_A;
    LD_addr_A(wBillsPC_CursorPosition);
    LD_addr_A(wBillsPC_ScrollPosition);
    POP_AF;
    RET;

FailedRelease:
    LD_DE(mPCString_WhatsUp);
    CALL(aBillsPC_PlaceString);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    RET;


cancel:
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    RET;


MenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['9', '4', 'SCREEN_WIDTH - 1', '13'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['4'];  // items
    //db ['"WITHDRAW@"'];
    //db ['"STATS@"'];
    //db ['"RELEASE@"'];
    //db ['"CANCEL@"'];

    return v_MovePKMNWithoutMail();
}

void v_MovePKMNWithoutMail(void){
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    LD_A_addr(wVramState);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wVramState);
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    CALL(aBillsPC_InitRAM);
    LD_A_addr(wCurBox);
    AND_A(0xf);
    INC_A;
    LD_addr_A(wBillsPC_LoadedBox);
    CALL(aDelayFrame);

loop:
    CALL(aJoyTextDelay);
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto done;
    CALL(av_MovePKMNWithoutMail_RunJumptable);
    CALL(aDelayFrame);
    goto loop;


done:
    CALL(aClearSprites);
    POP_AF;
    LDH_addr_A(hInMenu);
    POP_AF;
    LD_addr_A(wVramState);
    POP_AF;
    LD_addr_A(wOptions);
    RET;


RunJumptable:
    LD_A_addr(wJumptableIndex);
    LD_HL(mv_MovePKMNWithoutMail_Jumptable);
    CALL(aBillsPC_Jumptable);
    JP_hl;


Jumptable:
    //dw ['.Init'];
    //dw ['.Joypad'];
    //dw ['.PrepSubmenu'];
    //dw ['.MoveMonWOMailSubmenu'];
    //dw ['.PrepInsertCursor'];
    //dw ['.Joypad2'];
    //dw ['BillsPC_EndJumptableLoop'];


Init:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aClearSprites);
    CALL(aCopyBoxmonSpecies);
    LD_DE(mPCString_ChooseaPKMN);
    CALL(aBillsPC_PlaceString);
    LD_A(5);
    LD_addr_A(wBillsPC_NumMonsOnScreen);
    CALL(aBillsPC_RefreshTextboxes);
    CALL(aBillsPC_MoveMonWOMail_BoxNameAndArrows);
    CALL(aPCMonInfo);
    LD_A(0xff);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    CALL(aWaitBGMap);
    CALL(aBillsPC_UpdateSelectionCursor);
    CALL(aBillsPC_IncrementJumptableIndex);
    RET;


Joypad:
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto b_button;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto a_button;
    CALL(aMoveMonWithoutMail_DPad);
    IF_C goto d_pad;
    AND_A_A;
    RET_Z ;
    CALL(aBillsPC_UpdateSelectionCursor);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aBillsPC_RefreshTextboxes);
    CALL(aPCMonInfo);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    RET;


d_pad:
    XOR_A_A;
    LD_addr_A(wBillsPC_CursorPosition);
    LD_addr_A(wBillsPC_ScrollPosition);
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    RET;


a_button:
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    AND_A_A;
    RET_Z ;
    CP_A(-1);
    IF_Z goto b_button;
    LD_A(0x2);
    LD_addr_A(wJumptableIndex);
    RET;


go_back:
//   //  unreferenced
    LD_HL(wJumptableIndex);
    DEC_hl;
    RET;


b_button:
    LD_A(0x6);
    LD_addr_A(wJumptableIndex);
    RET;


PrepSubmenu:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aClearSprites);
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    LD_DE(mPCString_WhatsUp);
    CALL(aBillsPC_PlaceString);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    CALL(aBillsPC_IncrementJumptableIndex);
    RET;


MoveMonWOMailSubmenu:
    LD_HL(mv_MovePKMNWithoutMail_MenuHeader);
    CALL(aCopyMenuHeader);
    LD_A_addr(wMenuCursorY);
    CALL(aStoreMenuCursorPosition);
    CALL(aVerticalMenu);
    JP_C (mv_MovePKMNWithoutMail_Cancel);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    AND_A(0b11);
    LD_E_A;
    LD_D(0);
    LD_HL(mv_MovePKMNWithoutMail_Jumptable2);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


Jumptable2:
    //dw ['.Move'];
    //dw ['.Stats'];
    //dw ['.Cancel'];


Move:
    CALL(aBillsPC_CheckMail_PreventBlackout);
    JP_C (mv_MovePKMNWithoutMail_Cancel);
    LD_A_addr(wBillsPC_ScrollPosition);
    LD_addr_A(wBillsPC_BackupScrollPosition);
    LD_A_addr(wBillsPC_CursorPosition);
    LD_addr_A(wBillsPC_BackupCursorPosition);
    LD_A_addr(wBillsPC_LoadedBox);
    LD_addr_A(wBillsPC_BackupLoadedBox);
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    RET;


Stats:
    CALL(aLoadStandardMenuHeader);
    CALL(aBillsPC_StatsScreen);
    CALL(aExitMenu);
    CALL(aPCMonInfo);
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A(SCGB_BILLS_PC);
    CALL(aBillsPC_ApplyPalettes);
    RET;


Cancel:
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    RET;


MenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['9', '4', 'SCREEN_WIDTH - 1', '13'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['3'];  // items
    //db ['"MOVE@"'];
    //db ['"STATS@"'];
    //db ['"CANCEL@"'];


PrepInsertCursor:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aCopyBoxmonSpecies);
    LD_DE(mPCString_MoveToWhere);
    CALL(aBillsPC_PlaceString);
    LD_A(0x5);
    LD_addr_A(wBillsPC_NumMonsOnScreen);
    CALL(aBillsPC_RefreshTextboxes);
    CALL(aBillsPC_MoveMonWOMail_BoxNameAndArrows);
    CALL(aClearSprites);
    CALL(aBillsPC_UpdateInsertCursor);
    CALL(aWaitBGMap);
    CALL(aBillsPC_IncrementJumptableIndex);
    RET;


Joypad2:
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto b_button_2;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto a_button_2;
    CALL(aMoveMonWithoutMail_DPad_2);
    IF_C goto dpad_2;
    AND_A_A;
    RET_Z ;
    CALL(aBillsPC_UpdateInsertCursor);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aBillsPC_RefreshTextboxes);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    RET;


dpad_2:
    XOR_A_A;
    LD_addr_A(wBillsPC_CursorPosition);
    LD_addr_A(wBillsPC_ScrollPosition);
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    RET;


a_button_2:
    CALL(aBillsPC_CheckSpaceInDestination);
    IF_C goto no_space;
    CALL(aMovePKMNWitoutMail_InsertMon);
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    RET;


no_space:
    LD_HL(wJumptableIndex);
    DEC_hl;
    RET;


b_button_2:
    LD_A_addr(wBillsPC_BackupScrollPosition);
    LD_addr_A(wBillsPC_ScrollPosition);
    LD_A_addr(wBillsPC_BackupCursorPosition);
    LD_addr_A(wBillsPC_CursorPosition);
    LD_A_addr(wBillsPC_BackupLoadedBox);
    LD_addr_A(wBillsPC_LoadedBox);
    LD_A(0x0);
    LD_addr_A(wJumptableIndex);
    RET;

}

void BillsPC_InitRAM(void){
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    CALL(aBillsPC_InitGFX);
    LD_HL(wBillsPCData);
    LD_BC(wBillsPCDataEnd - wBillsPCData);
    XOR_A_A;
    CALL(aByteFill);
    XOR_A_A;
    LD_addr_A(wJumptableIndex);
    LD_addr_A(wUnusedBillsPCData);
    LD_addr_A(wUnusedBillsPCData+1);
    LD_addr_A(wUnusedBillsPCData+2);
    LD_addr_A(wBillsPC_CursorPosition);
    LD_addr_A(wBillsPC_ScrollPosition);
    RET;

}

void BillsPC_IncrementJumptableIndex(void){
    LD_HL(wJumptableIndex);
    INC_hl;
    RET;

}

void BillsPC_EndJumptableLoop(void){
    LD_HL(wJumptableIndex);
    SET_hl(7);
    RET;

}

void v_StatsScreenDPad(void){
    LD_A_addr(wBillsPC_NumMonsOnScreen);
    LD_D_A;
    LD_A_addr(wBillsPC_NumMonsInBox);
    AND_A_A;
    IF_Z goto empty;
    DEC_A;
    CP_A(0x1);
    IF_Z goto empty;
    LD_E_A;
    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mBillsPC_PressUp);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mBillsPC_PressDown);

empty:
    JP(mBillsPC_JoypadDidNothing);

}

u8_flag_s v_StatsScreenDPad_Conv(uint8_t* hl){
    // LD_A_addr(wBillsPC_NumMonsOnScreen);
    // LD_D_A;
    union Register de;
    de.hi = wram->wBillsPC_NumMonsOnScreen;
    // LD_A_addr(wBillsPC_NumMonsInBox);
    de.lo = wram->wBillsPC_NumMonsInBox;
    // AND_A_A;
    // IF_Z goto empty;
    if(de.lo == 0) {
        return BillsPC_JoypadDidNothing_Conv();
    }
    // DEC_A;
    // CP_A(0x1);
    // IF_Z goto empty;
    if(--de.lo == 0x1) {
        return BillsPC_JoypadDidNothing_Conv();
    }
    // LD_E_A;
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mBillsPC_PressUp);
    if(*hl & D_UP)
        return BillsPC_PressUp_Conv();
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mBillsPC_PressDown);
    if(*hl & D_DOWN)
        return BillsPC_PressDown_Conv(de.reg);

// empty:
    // JP(mBillsPC_JoypadDidNothing);
    return BillsPC_JoypadDidNothing_Conv();
}

void Withdraw_UpDown(void){
    LD_HL(hJoyLast);
    LD_A_addr(wBillsPC_NumMonsOnScreen);
    LD_D_A;
    LD_A_addr(wBillsPC_NumMonsInBox);
    LD_E_A;
    AND_A_A;
    IF_Z goto empty;
    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mBillsPC_PressUp);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mBillsPC_PressDown);

empty:
    JP(mBillsPC_JoypadDidNothing);

}

void MoveMonWithoutMail_DPad(void){
    LD_HL(hJoyLast);
    LD_A_addr(wBillsPC_NumMonsOnScreen);
    LD_D_A;
    LD_A_addr(wBillsPC_NumMonsInBox);
    LD_E_A;
    AND_A_A;
    IF_Z goto check_left_right;
    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mBillsPC_PressUp);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mBillsPC_PressDown);


check_left_right:
    LD_A_hl;
    AND_A(D_LEFT);
    JR_NZ (mBillsPC_PressLeft);
    LD_A_hl;
    AND_A(D_RIGHT);
    JR_NZ (mBillsPC_PressRight);
    JR(mBillsPC_JoypadDidNothing);

}

void MoveMonWithoutMail_DPad_2(void){
    LD_HL(hJoyLast);
    LD_A_addr(wBillsPC_NumMonsOnScreen);
    LD_D_A;
    LD_A_addr(wBillsPC_NumMonsInBox);
    LD_E_A;
    AND_A_A;
    IF_Z goto check_left_right;

    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mBillsPC_PressUp);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mBillsPC_PressDown);


check_left_right:
    LD_A_hl;
    AND_A(D_LEFT);
    JR_NZ (mBillsPC_PressLeft);
    LD_A_hl;
    AND_A(D_RIGHT);
    JR_NZ (mBillsPC_PressRight);
    JR(mBillsPC_JoypadDidNothing);

}

void BillsPC_PressUp(void){
    LD_HL(wBillsPC_CursorPosition);
    LD_A_hl;
    AND_A_A;
    IF_Z goto top;
    DEC_hl;
    JR(mBillsPC_UpDownDidSomething);


top:
    LD_HL(wBillsPC_ScrollPosition);
    LD_A_hl;
    AND_A_A;
    JR_Z (mBillsPC_JoypadDidNothing);
    DEC_hl;
    JR(mBillsPC_UpDownDidSomething);

}

u8_flag_s BillsPC_PressUp_Conv(void){
    // LD_HL(wBillsPC_CursorPosition);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto top;
    if(wram->wBillsPC_CursorPosition != 0) {
        // DEC_hl;
        // JR(mBillsPC_UpDownDidSomething);
        --wram->wBillsPC_CursorPosition;
        return BillsPC_UpDownDidSomething_Conv();
    }

// top:
    // LD_HL(wBillsPC_ScrollPosition);
    // LD_A_hl;
    // AND_A_A;
    // JR_Z (mBillsPC_JoypadDidNothing);
    if(wram->wBillsPC_ScrollPosition == 0)
        return BillsPC_JoypadDidNothing_Conv();
    // DEC_hl;
    // JR(mBillsPC_UpDownDidSomething);
    --wram->wBillsPC_ScrollPosition;
    return BillsPC_UpDownDidSomething_Conv();
}

void BillsPC_PressDown(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    INC_A;
    CP_A_E;
    JR_NC (mBillsPC_JoypadDidNothing);

    LD_HL(wBillsPC_CursorPosition);
    LD_A_hl;
    INC_A;
    CP_A_D;
    IF_NC goto not_bottom;
    INC_hl;
    JR(mBillsPC_UpDownDidSomething);


not_bottom:
    LD_HL(wBillsPC_ScrollPosition);
    INC_hl;
    JR(mBillsPC_UpDownDidSomething);

}

u8_flag_s BillsPC_PressDown_Conv(uint16_t de){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // INC_A;
    // CP_A_E;
    // JR_NC (mBillsPC_JoypadDidNothing);
    if(wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition + 1 >= LOW(de))
        return BillsPC_JoypadDidNothing_Conv();

    // LD_HL(wBillsPC_CursorPosition);
    // LD_A_hl;
    // INC_A;
    // CP_A_D;
    // IF_NC goto not_bottom;
    if(wram->wBillsPC_CursorPosition + 1 < HIGH(de)) {
        // INC_hl;
        // JR(mBillsPC_UpDownDidSomething);
        wram->wBillsPC_CursorPosition++;
        return BillsPC_UpDownDidSomething_Conv();
    }

// not_bottom:
    // LD_HL(wBillsPC_ScrollPosition);
    // INC_hl;
    // JR(mBillsPC_UpDownDidSomething);
    wram->wBillsPC_ScrollPosition++;
    return BillsPC_UpDownDidSomething_Conv();
}

void BillsPC_PressLeft(void){
    LD_HL(wBillsPC_LoadedBox);
    LD_A_hl;
    AND_A_A;
    IF_Z goto wrap_around;
    DEC_hl;
    JR(mBillsPC_LeftRightDidSomething);


wrap_around:
    LD_hl(NUM_BOXES);
    JR(mBillsPC_LeftRightDidSomething);

}

void BillsPC_PressRight(void){
    LD_HL(wBillsPC_LoadedBox);
    LD_A_hl;
    CP_A(NUM_BOXES);
    IF_Z goto wrap_around;
    INC_hl;
    JR(mBillsPC_LeftRightDidSomething);


wrap_around:
    LD_hl(0);
    JR(mBillsPC_LeftRightDidSomething);

}

void BillsPC_JoypadDidNothing(void){
    XOR_A_A;
    AND_A_A;
    RET;

}

u8_flag_s BillsPC_JoypadDidNothing_Conv(void){
    // XOR_A_A;
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

void BillsPC_UpDownDidSomething(void){
    LD_A(TRUE);
    AND_A_A;
    RET;

}

u8_flag_s BillsPC_UpDownDidSomething_Conv(void){
    // LD_A(TRUE);
    // AND_A_A;
    // RET;
    return u8_flag(TRUE, false);
}

void BillsPC_LeftRightDidSomething(void){
    SCF;
    RET;

}

u8_flag_s BillsPC_LeftRightDidSomething_Conv(void){
    // SCF;
    // RET;
    return u8_flag(0, true);
}

void BillsPC_PlaceString(void){
    PUSH_DE;
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);
    POP_DE;
    hlcoord(1, 16, wTilemap);
    CALL(aPlaceString);
    RET;

}

void BillsPC_MoveMonWOMail_BoxNameAndArrows(void){
    CALL(aBillsPC_BoxName);
    hlcoord(8, 1, wTilemap);
    LD_hl(0x5f);
    hlcoord(19, 1, wTilemap);
    LD_hl(0x5e);
    RET;

}

void BillsPC_BoxName(void){
    hlcoord(8, 0, wTilemap);
    LD_BC((1 << 8) | 10);
    CALL(aTextbox);

    LD_A_addr(wBillsPC_LoadedBox);
    AND_A_A;
    IF_Z goto party;

    CP_A(NUM_BOXES + 1);
    IF_NZ goto gotbox;

    LD_A_addr(wCurBox);
    INC_A;

gotbox:
    DEC_A;
    LD_HL(wBoxNames);
    LD_BC(BOX_NAME_LENGTH);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    goto print;


party:
    LD_DE(mBillsPC_BoxName_PartyPKMN);

print:
    hlcoord(10, 1, wTilemap);
    CALL(aPlaceString);
    RET;


PartyPKMN:
    //db ['"PARTY <PK><MN>@"'];

    return PCMonInfo();
}

void PCMonInfo(void){
//  Display a monster's pic and
//  attributes when highlighting
//  it in a PC menu.

//  Includes the neat cascading
//  effect when showing the pic.

//  Example: Species, level, gender,
//  whether it's holding an item.

    hlcoord(0, 0, wTilemap);
    LD_BC((15 << 8) | 8);
    CALL(aClearBox);

    hlcoord(8, 14, wTilemap);
    LD_BC((1 << 8) | 3);
    CALL(aClearBox);

    CALL(aBillsPC_GetSelectedPokemonSpecies);
    AND_A_A;
    RET_Z ;
    CP_A(-1);
    RET_Z ;

    LD_addr_A(wTempSpecies);
    hlcoord(1, 4, wTilemap);
    XOR_A_A;
    LD_B(7);

row:
    LD_C(7);
    PUSH_AF;
    PUSH_HL;

col:
    LD_hli_A;
    ADD_A(7);
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    POP_AF;
    INC_A;
    DEC_B;
    IF_NZ goto row;

    CALL(aBillsPC_LoadMonStats);
    LD_A_addr(wTempSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    LD_HL(wTempMonDVs);
    PREDEF(pGetUnownLetter);
    CALL(aGetBaseData);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    PREDEF(pGetMonFrontpic);
    XOR_A_A;
    LD_addr_A(wBillsPC_MonHasMail);
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wTempSpecies);
    CP_A(EGG);
    RET_Z ;

    CALL(aGetBasePokemonName);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);

    hlcoord(1, 12, wTilemap);
    CALL(aPrintLevel);

    LD_A(0x3);
    LD_addr_A(wMonType);
    FARCALL(aGetGender);
    IF_C goto skip_gender;
    LD_A(0xef);
    IF_NZ goto printgender;
    LD_A(0xf5);

printgender:
    hlcoord(5, 12, wTilemap);
    LD_hl_A;

skip_gender:

    LD_A_addr(wTempMonItem);
    AND_A_A;
    RET_Z ;

    LD_D_A;
    CALLFAR(aItemIsMail);
    IF_C goto mail;
    LD_A(0x5d);  // item icon
    goto printitem;

mail:
    LD_A(0x1);
    LD_addr_A(wBillsPC_MonHasMail);
    LD_A(0x5c);  // mail icon

printitem:
    hlcoord(7, 12, wTilemap);
    LD_hl_A;
    RET;

}

void BillsPC_LoadMonStats(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_E_A;
    LD_D(0);
    LD_HL(wBillsPCPokemonList + 1);  // box number
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    IF_Z goto party;
    CP_A(NUM_BOXES + 1);
    IF_Z goto sBox;
    LD_B_A;
    CALL(aGetBoxPointer);
    LD_A_B;
    CALL(aOpenSRAM);
    PUSH_HL;
    LD_BC(sBoxMon1Level - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonLevel);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMon1Item - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonItem);
    POP_HL;
    LD_BC(sBoxMon1DVs - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    CALL(aCloseSRAM);
    RET;


party:
    LD_HL(wPartyMon1Level);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonLevel);
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonItem);
    LD_HL(wPartyMon1DVs);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    RET;


sBox:
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxMon1Level);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonLevel);

    LD_HL(sBoxMon1Item);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonItem);

    LD_HL(sBoxMon1DVs);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;

    CALL(aCloseSRAM);
    RET;

}

void BillsPC_LoadMonStats_Conv(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_E_A;
    uint8_t e = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // LD_D(0);
    // LD_HL(wBillsPCPokemonList + 1);  // box number
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hl;
    uint8_t a = wram->wBillsPCPokemonList[3 * e + 1];
    // AND_A_A;
    // IF_Z goto party;
    if(a == 0){
    // party:
        // LD_HL(wPartyMon1Level);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        struct PartyMon* bc = wram->wPartyMon + e;
        // LD_A_hl;
        // LD_addr_A(wTempMonLevel);
        wram->wTempMon.mon.level = bc->mon.level;
        // LD_HL(wPartyMon1Item);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        // LD_A_hl;
        // LD_addr_A(wTempMonItem);
        wram->wTempMon.mon.item = bc->mon.item;
        // LD_HL(wPartyMon1DVs);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        // LD_DE(wTempMonDVs);
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        // LD_A_hl;
        // LD_de_A;
        wram->wTempMon.mon.DVs = bc->mon.DVs;
        // RET;
        return;
    }
    // CP_A(NUM_BOXES + 1);
    // IF_Z goto sBox;
    if(a == NUM_BOXES + 1)
        goto sBox;
    LD_B_A;
    CALL(aGetBoxPointer);
    LD_A_B;
    CALL(aOpenSRAM);
    PUSH_HL;
    LD_BC(sBoxMon1Level - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonLevel);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMon1Item - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonItem);
    POP_HL;
    LD_BC(sBoxMon1DVs - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    CALL(aCloseSRAM);
    RET;

sBox:
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxMon1Level);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonLevel);

    LD_HL(sBoxMon1Item);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonItem);

    LD_HL(sBoxMon1DVs);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;

    CALL(aCloseSRAM);
    RET;

}

void BillsPC_RefreshTextboxes(void){
    hlcoord(8, 2, wTilemap);
    LD_BC((10 << 8) | 10);
    CALL(aTextbox);

    hlcoord(8, 2, wTilemap);
    LD_hl(0x7d);
    hlcoord(19, 2, wTilemap);
    LD_hl(0x7e);

    LD_A_addr(wBillsPC_ScrollPosition);
    LD_E_A;
    LD_D(0);
    LD_HL(wBillsPCPokemonList);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    hlcoord(9, 4, wTilemap);
    LD_A_addr(wBillsPC_NumMonsOnScreen);

loop:
    PUSH_AF;
    PUSH_DE;
    PUSH_HL;
    CALL(aBillsPC_RefreshTextboxes_PlaceNickname);
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_DE;
    INC_DE;
    INC_DE;
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    RET;


CancelString:
    //db ['"CANCEL@"'];


PlaceNickname:
    LD_A_de;
    AND_A_A;
    RET_Z ;
    CP_A(-1);
    IF_NZ goto get_nickname;
    LD_DE(mBillsPC_RefreshTextboxes_CancelString);
    CALL(aPlaceString);
    RET;


get_nickname:
    INC_DE;
    LD_A_de;
    LD_B_A;
    INC_DE;
    LD_A_de;
    LD_E_A;
    LD_A_B;
    AND_A_A;
    IF_Z goto party;
    CP_A(NUM_BOXES + 1);
    IF_Z goto sBox;
    PUSH_HL;
    CALL(aGetBoxPointer);
    LD_A_B;
    CALL(aOpenSRAM);
    PUSH_HL;
    LD_BC(sBoxMons - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    POP_HL;
    AND_A_A;
    IF_Z goto boxfail;
    LD_BC(sBoxMonNicknames - sBox);
    ADD_HL_BC;
    LD_BC(MON_NAME_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wStringBuffer1);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    POP_HL;
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    RET;


boxfail:
    CALL(aCloseSRAM);
    POP_HL;
    goto placeholder_string;


party:
    PUSH_HL;
    LD_HL(wPartySpecies);
    LD_D(0x0);
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    IF_Z goto partyfail;
    LD_HL(wPartyMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wStringBuffer1);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    POP_HL;
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    RET;


partyfail:
    POP_HL;
    goto placeholder_string;


sBox:
    PUSH_HL;
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxSpecies);
    LD_D(0x0);
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    IF_Z goto sBoxFail;
    LD_HL(sBoxMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wStringBuffer1);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    POP_HL;
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    RET;


sBoxFail:
    CALL(aCloseSRAM);
    POP_HL;

placeholder_string:
    LD_DE(mBillsPC_RefreshTextboxes_Placeholder);
    CALL(aPlaceString);
    RET;


Placeholder:
    //db ['"-----@"'];

// copy_box_data: MACRO
// .loop\@
//     ld a, [hl]
//     cp -1
//     jr z, .done\@
//     and a
//     jr z, .done\@
//     ld [de], a ; species
//     inc de
//     ld a, [wBillsPC_LoadedBox]
//     ld [de], a ; box number
//     inc de
//     ld a, [wBillsPCTempListIndex]
//     ld [de], a ; list index
//     inc a
//     ld [wBillsPCTempListIndex], a
//     inc de
//     inc hl
//     ld a, [wBillsPCTempBoxCount]
//     inc a
//     ld [wBillsPCTempBoxCount], a
//     jr .loop\@

// .done\@
// if \1
//     call CloseSRAM
// endc
//     ld a, -1
//     ld [de], a
//     ld a, [wBillsPCTempBoxCount]
//     inc a
//     ld [wBillsPC_NumMonsInBox], a
// ENDM

    return CopyBoxmonSpecies();
}

void CopyBoxmonSpecies(void){
    XOR_A_A;
    LD_HL(wBillsPCPokemonList);
    LD_BC(3 * 30);
    CALL(aByteFill);
    LD_DE(wBillsPCPokemonList);
    XOR_A_A;
    LD_addr_A(wBillsPCTempListIndex);
    LD_addr_A(wBillsPCTempBoxCount);
    LD_A_addr(wBillsPC_LoadedBox);
    AND_A_A;
    IF_Z goto party;
    CP_A(NUM_BOXES + 1);
    IF_Z goto sBox;
    LD_B_A;
    CALL(aGetBoxPointer);
    LD_A_B;
    CALL(aOpenSRAM);
    INC_HL;
    //copy_box_data ['1']
    RET;


party:
    LD_HL(wPartySpecies);
    //copy_box_data ['0']
    RET;


sBox:
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxSpecies);
    //copy_box_data ['1']
    RET;

}

void BillsPC_GetSelectedPokemonSpecies(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_E_A;
    LD_D(0);
    LD_HL(wBillsPCPokemonList);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hl;
    RET;

}

species_t BillsPC_GetSelectedPokemonSpecies_Conv(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wBillsPCPokemonList);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hl;
    // RET;
    return (species_t)wram->wBillsPCPokemonList[3 * (wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition)];
}

void BillsPC_UpdateSelectionCursor(void){
    LD_A_addr(wBillsPC_NumMonsInBox);
    AND_A_A;
    IF_NZ goto place_cursor;
    CALL(aClearSprites);
    RET;


place_cursor:
    LD_HL(mBillsPC_UpdateSelectionCursor_OAM);
    LD_DE(wVirtualOAMSprite00);

loop:
    LD_A_hl;
    CP_A(-1);
    RET_Z ;
    LD_A_addr(wBillsPC_CursorPosition);
    AND_A(0x7);
    SWAP_A;
    ADD_A_hl;
    INC_HL;
    LD_de_A;  // y
    INC_DE;
    for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
    LD_A_hli;
    LD_de_A;
    INC_DE;
    }
    goto loop;


OAM:
    //dbsprite ['10', '4', '0', '6', '0x00', '0']
    //dbsprite ['11', '4', '0', '6', '0x00', '0']
    //dbsprite ['12', '4', '0', '6', '0x00', '0']
    //dbsprite ['13', '4', '0', '6', '0x00', '0']
    //dbsprite ['14', '4', '0', '6', '0x00', '0']
    //dbsprite ['15', '4', '0', '6', '0x00', '0']
    //dbsprite ['16', '4', '0', '6', '0x00', '0']
    //dbsprite ['17', '4', '0', '6', '0x00', '0']
    //dbsprite ['18', '4', '0', '6', '0x00', '0']
    //dbsprite ['18', '4', '7', '6', '0x00', '0']
    //dbsprite ['10', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['11', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['12', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['13', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['14', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['15', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['16', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['17', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['18', '7', '0', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['18', '7', '7', '1', '0x00', '0 | Y_FLIP']
    //dbsprite ['9', '5', '6', '6', '0x01', '0']
    //dbsprite ['9', '6', '6', '1', '0x01', '0 | Y_FLIP']
    //dbsprite ['19', '5', '1', '6', '0x01', '0 | X_FLIP']
    //dbsprite ['19', '6', '1', '1', '0x01', '0 | X_FLIP | Y_FLIP']
    //db ['-1'];

    return BillsPC_UpdateInsertCursor();
}

void BillsPC_UpdateInsertCursor(void){
    LD_HL(mBillsPC_UpdateInsertCursor_OAM);
    LD_DE(wVirtualOAMSprite00);

loop:
    LD_A_hl;
    CP_A(-1);
    RET_Z ;
    LD_A_addr(wBillsPC_CursorPosition);
    AND_A(0x7);
    SWAP_A;
    ADD_A_hl;
    INC_HL;
    LD_de_A;  // y
    INC_DE;
    for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
    LD_A_hli;
    LD_de_A;
    INC_DE;
    }
    goto loop;


OAM:
    //dbsprite ['10', '4', '0', '7', '0x06', '0']
    //dbsprite ['11', '5', '0', '3', '0x00', '0 | Y_FLIP']
    //dbsprite ['12', '5', '0', '3', '0x00', '0 | Y_FLIP']
    //dbsprite ['13', '5', '0', '3', '0x00', '0 | Y_FLIP']
    //dbsprite ['14', '5', '0', '3', '0x00', '0 | Y_FLIP']
    //dbsprite ['15', '5', '0', '3', '0x00', '0 | Y_FLIP']
    //dbsprite ['16', '5', '0', '3', '0x00', '0 | Y_FLIP']
    //dbsprite ['17', '5', '0', '3', '0x00', '0 | Y_FLIP']
    //dbsprite ['18', '5', '0', '3', '0x00', '0 | Y_FLIP']
    //dbsprite ['19', '4', '0', '7', '0x07', '0']
    //db ['-1'];

    return BillsPC_FillBox();
}

void BillsPC_FillBox(void){
//  //  unreferenced

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

void BillsPC_CheckSpaceInDestination(void){
//  If moving within a box, no need to be here.
    LD_HL(wBillsPC_LoadedBox);
    LD_A_addr(wBillsPC_BackupLoadedBox);
    CP_A_hl;
    IF_Z goto same_box;

//  Exceeding box or party capacity is a big no-no.
    LD_A_addr(wBillsPC_LoadedBox);
    AND_A_A;
    IF_Z goto party;
    LD_E(MONS_PER_BOX + 1);
    goto compare;


party:
    LD_E(PARTY_LENGTH + 1);

compare:
    LD_A_addr(wBillsPC_NumMonsInBox);
    CP_A_E;
    IF_NC goto no_room;

same_box:
    AND_A_A;
    RET;


no_room:
    LD_DE(mPCString_TheresNoRoom);
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

void BillsPC_CheckMail_PreventBlackout(void){
    LD_A_addr(wBillsPC_LoadedBox);
    AND_A_A;
    IF_NZ goto Okay;
    LD_A_addr(wBillsPC_NumMonsInBox);
    CP_A(0x3);
    IF_C goto ItsYourLastPokemon;
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    FARCALL(aCheckCurPartyMonFainted);
    IF_C goto AllOthersFainted;
    LD_A_addr(wBillsPC_MonHasMail);
    AND_A_A;
    IF_NZ goto HasMail;

Okay:
    AND_A_A;
    RET;


HasMail:
    LD_DE(mPCString_RemoveMail);
    goto NotOkay;


AllOthersFainted:
    LD_DE(mPCString_NoMoreUsablePKMN);
    goto NotOkay;


ItsYourLastPokemon:
    LD_DE(mPCString_ItsYourLastPKMN);

NotOkay:
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

void BillsPC_IsMonAnEgg(void){
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto egg;
    AND_A_A;
    RET;


egg:
    LD_DE(mPCString_NoReleasingEGGS);
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

void BillsPC_StatsScreen(void){
    CALL(aLowVolume);
    CALL(aBillsPC_CopyMon);
    LD_A(TEMPMON);
    LD_addr_A(wMonType);
    PREDEF(pStatsScreenInit);
    CALL(aBillsPC_InitGFX);
    CALL(aMaxVolume);
    RET;

}

void StatsScreenDPad(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(A_BUTTON | B_BUTTON | D_RIGHT | D_LEFT);
    LD_addr_A(wMenuJoypad);
    IF_NZ goto pressed_a_b_right_left;
    LD_A_hl;
    AND_A(D_DOWN | D_UP);
    LD_addr_A(wMenuJoypad);
    IF_NZ goto pressed_down_up;
    goto pressed_a_b_right_left;


pressed_down_up:
    CALL(av_StatsScreenDPad);
    AND_A_A;
    IF_Z goto did_nothing;
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    LD_addr_A(wTempSpecies);
    CALL(aBillsPC_LoadMonStats);
    LD_A_addr(wTempSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    LD_HL(wTempMonDVs);
    PREDEF(pGetUnownLetter);
    CALL(aGetBaseData);
    CALL(aBillsPC_CopyMon);

pressed_a_b_right_left:
    RET;


did_nothing:
    XOR_A_A;
    LD_addr_A(wMenuJoypad);
    RET;

}

void StatsScreenDPad_Conv(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(A_BUTTON | B_BUTTON | D_RIGHT | D_LEFT);
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = hram->hJoyPressed & (A_BUTTON | B_BUTTON | D_RIGHT | D_LEFT);
    // IF_NZ goto pressed_a_b_right_left;
    if(wram->wMenuJoypad != 0)
        return;
    // LD_A_hl;
    // AND_A(D_DOWN | D_UP);
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = hram->hJoyPressed & (D_DOWN | D_UP);
    // IF_NZ goto pressed_down_up;
    if(wram->wMenuJoypad != 0) {
    // pressed_down_up:
        // CALL(av_StatsScreenDPad);
        // AND_A_A;
        // IF_Z goto did_nothing;
        if(v_StatsScreenDPad_Conv(&hram->hJoyPressed).a == 0) {
        // did_nothing:
            // XOR_A_A;
            // LD_addr_A(wMenuJoypad);
            wram->wMenuJoypad = NO_INPUT;
            // RET;
            return;
        }
        // CALL(aBillsPC_GetSelectedPokemonSpecies);
        // LD_addr_A(wTempSpecies);
        wram->wTempSpecies = BillsPC_GetSelectedPokemonSpecies_Conv();
        // CALL(aBillsPC_LoadMonStats);
        BillsPC_LoadMonStats_Conv();
        // LD_A_addr(wTempSpecies);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = wram->wTempSpecies;
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = wram->wTempSpecies;
        // LD_HL(wTempMonDVs);
        // PREDEF(pGetUnownLetter);
        GetUnownLetter_Conv(wram->wTempMon.mon.DVs);
        // CALL(aGetBaseData);
        GetBaseData_Conv2(wram->wCurSpecies);
        // CALL(aBillsPC_CopyMon);
        BillsPC_CopyMon_Conv();

    // pressed_a_b_right_left:
        // RET;
    }
    // goto pressed_a_b_right_left;
    return;
}

void BillsPC_CopyMon(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_A_addr(wBillsPC_LoadedBox);
    AND_A_A;
    IF_Z goto party;
    CP_A(NUM_BOXES + 1);
    IF_NZ goto box;
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxSpecies);
    CALL(aCopySpeciesToTemp);
    LD_HL(sBoxMonNicknames);
    CALL(aCopyNicknameToTemp);
    LD_HL(sBoxMonOTs);
    CALL(aCopyOTNameToTemp);
    LD_HL(sBoxMons);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMon);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    FARCALL(aCalcBufferMonStats);
    RET;


party:
    LD_HL(wPartySpecies);
    CALL(aCopySpeciesToTemp);
    LD_HL(wPartyMonNicknames);
    CALL(aCopyNicknameToTemp);
    LD_HL(wPartyMonOTs);
    CALL(aCopyOTNameToTemp);
    LD_HL(wPartyMon1);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMon);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    RET;


box:
    LD_B_A;
    CALL(aGetBoxPointer);
    LD_A_B;
    CALL(aOpenSRAM);
    PUSH_HL;
    INC_HL;
    CALL(aCopySpeciesToTemp);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMonNicknames - sBox);
    ADD_HL_BC;
    CALL(aCopyNicknameToTemp);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMonOTs - sBox);
    ADD_HL_BC;
    CALL(aCopyOTNameToTemp);
    POP_HL;
    LD_BC(sBoxMons - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aCopyMonToTemp);
    CALL(aCloseSRAM);
    FARCALL(aCalcBufferMonStats);
    RET;

}

void BillsPC_CopyMon_Conv(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // LD_A_addr(wBillsPC_LoadedBox);
    // AND_A_A;
    // IF_Z goto party;
    if(wram->wBillsPC_LoadedBox == 0) {
    // party:
        // LD_HL(wPartySpecies);
        // CALL(aCopySpeciesToTemp);
        CopySpeciesToTemp_Conv(wram->wPartySpecies);
        // LD_HL(wPartyMonNicknames);
        // CALL(aCopyNicknameToTemp);
        CopyNicknameToTemp_Conv(wram->wPartyMonNickname);
        // LD_HL(wPartyMonOTs);
        // CALL(aCopyOTNameToTemp);
        CopyOTNameToTemp_Conv(wram->wPartyMonOT);
        // LD_HL(wPartyMon1);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_addr(wCurPartyMon);
        // CALL(aAddNTimes);
        // LD_DE(wBufferMon);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        // RET;
        return CopyBytes_Conv2(&wram->wBufferMon, &wram->wPartyMon[wram->wCurPartyMon], sizeof(struct PartyMon));
    }
    CP_A(NUM_BOXES + 1);
    IF_NZ goto box;
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxSpecies);
    CALL(aCopySpeciesToTemp);
    LD_HL(sBoxMonNicknames);
    CALL(aCopyNicknameToTemp);
    LD_HL(sBoxMonOTs);
    CALL(aCopyOTNameToTemp);
    LD_HL(sBoxMons);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMon);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    FARCALL(aCalcBufferMonStats);
    RET;


box:
    LD_B_A;
    CALL(aGetBoxPointer);
    LD_A_B;
    CALL(aOpenSRAM);
    PUSH_HL;
    INC_HL;
    CALL(aCopySpeciesToTemp);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMonNicknames - sBox);
    ADD_HL_BC;
    CALL(aCopyNicknameToTemp);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMonOTs - sBox);
    ADD_HL_BC;
    CALL(aCopyOTNameToTemp);
    POP_HL;
    LD_BC(sBoxMons - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aCopyMonToTemp);
    CALL(aCloseSRAM);
    FARCALL(aCalcBufferMonStats);
    RET;

}

void DepositPokemon(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    LD_A_addr(wCurPartyMon);
    CALL(aGetNickname);
    LD_A(PC_DEPOSIT);
    LD_addr_A(wPokemonWithdrawDepositParameter);
    PREDEF(pSendGetMonIntoFromBox);
    IF_C goto BoxFull;
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    LD_A_addr(wCurPartySpecies);
    CALL(aPlayMonCry);
    hlcoord(0, 0, wTilemap);
    LD_BC((15 << 8) | 8);
    CALL(aClearBox);
    hlcoord(8, 14, wTilemap);
    LD_BC((1 << 8) | 3);
    CALL(aClearBox);
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);
    CALL(aWaitBGMap);
    hlcoord(1, 16, wTilemap);
    LD_DE(mPCString_Stored);
    CALL(aPlaceString);
    LD_L_C;
    LD_H_B;
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    LD_A(0xe7);
    LD_bc_A;
    LD_C(50);
    CALL(aDelayFrames);
    AND_A_A;
    RET;


BoxFull:
    LD_DE(mPCString_BoxFull);
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

void TryWithdrawPokemon(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_A(BANK(sBoxMonNicknames));
    CALL(aOpenSRAM);
    LD_A_addr(wCurPartyMon);
    LD_HL(sBoxMonNicknames);
    CALL(aGetNickname);
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(wPokemonWithdrawDepositParameter);
    PREDEF(pSendGetMonIntoFromBox);
    IF_C goto PartyFull;
    LD_A(REMOVE_BOX);
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    LD_A_addr(wCurPartySpecies);
    CALL(aPlayMonCry);
    hlcoord(0, 0, wTilemap);
    LD_BC((15 << 8) | 8);
    CALL(aClearBox);
    hlcoord(8, 14, wTilemap);
    LD_BC((1 << 8) | 3);
    CALL(aClearBox);
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);
    CALL(aWaitBGMap);
    hlcoord(1, 16, wTilemap);
    LD_DE(mPCString_Got);
    CALL(aPlaceString);
    LD_L_C;
    LD_H_B;
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    LD_A(0xe7);
    LD_bc_A;
    LD_C(50);
    CALL(aDelayFrames);
    AND_A_A;
    RET;


PartyFull:
    LD_DE(mPCString_PartyFull);
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

void ReleasePKMN_ByePKMN(void){
    hlcoord(0, 0, wTilemap);
    LD_BC((15 << 8) | 8);
    CALL(aClearBox);
    hlcoord(8, 14, wTilemap);
    LD_BC((1 << 8) | 3);
    CALL(aClearBox);
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);

    CALL(aWaitBGMap);
    LD_A_addr(wCurPartySpecies);
    CALL(aGetCryIndex);
    IF_C goto skip_cry;
    LD_E_C;
    LD_D_B;
    CALL(aPlayCry);

skip_cry:

    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wTempSpecies);
    CALL(aGetPokemonName);
    hlcoord(1, 16, wTilemap);
    LD_DE(mPCString_ReleasedPKMN);
    CALL(aPlaceString);
    LD_C(80);
    CALL(aDelayFrames);
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);
    hlcoord(1, 16, wTilemap);
    LD_DE(mPCString_Bye);
    CALL(aPlaceString);
    LD_L_C;
    LD_H_B;
    INC_HL;
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    LD_L_C;
    LD_H_B;
    LD_hl(0xe7);
    LD_C(50);
    CALL(aDelayFrames);
    RET;

}

void MovePKMNWitoutMail_InsertMon(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_AF;
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);
    hlcoord(1, 16, wTilemap);
    LD_DE(mMovePKMNWitoutMail_InsertMon_Saving_LeaveOn);
    CALL(aPlaceString);
    LD_C(20);
    CALL(aDelayFrames);
    POP_AF;
    POP_BC;
    POP_DE;
    POP_HL;
    LD_A_addr(wCurBox);
    PUSH_AF;
    LD_BC(0);
    LD_A_addr(wBillsPC_BackupLoadedBox);
    AND_A_A;
    IF_NZ goto moving_from_box;
    SET_C(0);


moving_from_box:
    LD_A_addr(wBillsPC_LoadedBox);
    AND_A_A;
    IF_NZ goto moving_to_box;
    SET_C(1);


moving_to_box:
    LD_HL(mMovePKMNWitoutMail_InsertMon_Jumptable);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(mMovePKMNWitoutMail_InsertMon_dw_return);
    PUSH_DE;
    JP_hl;


dw_return:
    POP_AF;
    LD_E_A;
    FARCALL(aMoveMonWOMail_InsertMon_SaveGame);
    RET;


Saving_LeaveOn:
    //db ['"Saving… Leave ON!@"'];


Jumptable:
    //dw ['.BoxToBox'];
    //dw ['.PartyToBox'];
    //dw ['.BoxToParty'];
    //dw ['.PartyToParty'];


BoxToBox:
    LD_HL(wBillsPC_BackupLoadedBox);
    LD_A_addr(wBillsPC_LoadedBox);
    CP_A_hl;
    IF_Z goto same_box;
    CALL(aMovePKMNWitoutMail_InsertMon_CopyFromBox);
    CALL(aMovePKMNWitoutMail_InsertMon_CopyToBox);
    RET;


same_box:
    CALL(aMovePKMNWitoutMail_InsertMon_CopyFromBox);
    CALL(aMovePKMNWitoutMail_InsertMon_CheckTrivialMove);
    CALL(aMovePKMNWitoutMail_InsertMon_CopyToBox);
    RET;


PartyToBox:
    CALL(aMovePKMNWitoutMail_InsertMon_CopyFromParty);
    LD_A(0x1);
    LD_addr_A(wGameLogicPaused);
    FARCALL(aSaveGameData);
    XOR_A_A;
    LD_addr_A(wGameLogicPaused);
    CALL(aMovePKMNWitoutMail_InsertMon_CopyToBox);
    RET;


BoxToParty:
    CALL(aMovePKMNWitoutMail_InsertMon_CopyFromBox);
    CALL(aMovePKMNWitoutMail_InsertMon_CopyToParty);
    RET;


PartyToParty:
    CALL(aMovePKMNWitoutMail_InsertMon_CopyFromParty);
    CALL(aMovePKMNWitoutMail_InsertMon_CheckTrivialMove);
    CALL(aMovePKMNWitoutMail_InsertMon_CopyToParty);
    RET;


CheckTrivialMove:
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_E_A;
    LD_A_addr(wBillsPC_BackupCursorPosition);
    LD_HL(wBillsPC_BackupScrollPosition);
    ADD_A_hl;
    CP_A_E;
    RET_NC ;
    LD_HL(wBillsPC_CursorPosition);
    LD_A_hl;
    AND_A_A;
    IF_Z goto top_of_screen;
    DEC_hl;
    RET;


top_of_screen:
    LD_HL(wBillsPC_ScrollPosition);
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    RET;


CopyFromBox:
    LD_A_addr(wBillsPC_BackupLoadedBox);
    DEC_A;
    LD_E_A;
    FARCALL(aMoveMonWOMail_SaveGame);
    LD_A_addr(wBillsPC_BackupCursorPosition);
    LD_HL(wBillsPC_BackupScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxSpecies);
    CALL(aCopySpeciesToTemp);
    LD_HL(sBoxMonNicknames);
    CALL(aCopyNicknameToTemp);
    LD_HL(sBoxMonOTs);
    CALL(aCopyOTNameToTemp);
    LD_HL(sBoxMons);
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aCopyMonToTemp);
    CALL(aCloseSRAM);
    FARCALL(aCalcBufferMonStats);
    LD_A(REMOVE_BOX);
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    RET;


CopyToBox:
    LD_A_addr(wBillsPC_LoadedBox);
    DEC_A;
    LD_E_A;
    FARCALL(aMoveMonWOMail_SaveGame);
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    FARCALL(aInsertPokemonIntoBox);
    RET;


CopyFromParty:
    LD_A_addr(wBillsPC_BackupCursorPosition);
    LD_HL(wBillsPC_BackupScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_HL(wPartySpecies);
    CALL(aCopySpeciesToTemp);
    LD_HL(wPartyMonNicknames);
    CALL(aCopyNicknameToTemp);
    LD_HL(wPartyMonOTs);
    CALL(aCopyOTNameToTemp);
    LD_HL(wPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyMonToTemp);
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    RET;


CopyToParty:
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    FARCALL(aInsertPokemonIntoParty);
    RET;

}

void CopySpeciesToTemp(void){
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);
    RET;

}

void CopySpeciesToTemp_Conv(const uint8_t* hl){
    // LD_A_addr(wCurPartyMon);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wCurPartySpecies);
    // RET;
    wram->wCurPartySpecies = hl[wram->wCurPartyMon];
}

void CopyNicknameToTemp(void){
    LD_BC(MON_NAME_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMonNickname);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    RET;

}

void CopyNicknameToTemp_Conv(const uint8_t (*hl)[MON_NAME_LENGTH]){
    // LD_BC(MON_NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_DE(wBufferMonNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes_Conv2(wram->wBufferMonNickname, hl[wram->wCurPartyMon], MON_NAME_LENGTH);
}

void CopyOTNameToTemp(void){
    LD_BC(NAME_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMonOT);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    RET;

}

void CopyOTNameToTemp_Conv(const uint8_t (*hl)[NAME_LENGTH]){
    // LD_BC(NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_DE(wBufferMonOT);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes_Conv2(wram->wBufferMonOT, hl[wram->wCurPartyMon], NAME_LENGTH);
}

void CopyMonToTemp(void){
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMon);
    CALL(aCopyBytes);
    RET;

}

void CopyMonToTemp_Conv(struct PartyMon* hl){
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_DE(wBufferMon);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes_Conv2(&wram->wBufferMon, hl + wram->wCurPartyMon, sizeof(struct PartyMon));
}

void GetBoxPointer(void){
    DEC_B;
    LD_C_B;
    LD_B(0);
    LD_HL(mGetBoxPointer_BoxBankAddresses);
    ADD_HL_BC;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;


BoxBankAddresses:
    //table_width ['3', 'GetBoxPointer.BoxBankAddresses']
    //dba ['sBox1']
    //dba ['sBox2']
    //dba ['sBox3']
    //dba ['sBox4']
    //dba ['sBox5']
    //dba ['sBox6']
    //dba ['sBox7']
    //dba ['sBox8']
    //dba ['sBox9']
    //dba ['sBox10']
    //dba ['sBox11']
    //dba ['sBox12']
    //dba ['sBox13']
    //dba ['sBox14']
    //assert_table_length ['NUM_BOXES']

    return BillsPC_ApplyPalettes();
}

void BillsPC_ApplyPalettes(void){
    LD_B_A;
    CALL(aGetSGBLayout);
    LD_A(0b11100100);
    CALL(aDmgToCgbBGPals);
    LD_A(0b11111100);
    CALL(aDmgToCgbObjPal0);
    RET;

}

void BillsPC_Jumptable(void){
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;

}

void BillsPC_InitGFX(void){
    CALL(aDisableLCD);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x00);
    LD_BC(0x31 * LEN_2BPP_TILE);
    XOR_A_A;
    CALL(aByteFill);
    CALL(aLoadStandardFont);
    CALL(aLoadFontsBattleExtra);
    LD_HL(mPCMailGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x5c);
    LD_BC(4 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    LD_HL(mPCSelectLZ);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    CALL(aDecompress);
    LD_A(6);
    CALL(aSkipMusic);
    CALL(aEnableLCD);
    RET;

}

void PCSelectLZ(void){
//INCBIN "gfx/pc/pc.2bpp.lz"
    return PCMailGFX();
}

void PCMailGFX(void){
// INCBIN "gfx/pc/pc_mail.2bpp"

    return PCString_ChooseaPKMN();
}

void PCString_ChooseaPKMN(void){
//db "Choose a <PK><MN>.@"
    return PCString_WhatsUp();
}

void PCString_WhatsUp(void){
//db "What's up?@"
    return PCString_ReleasePKMN();
}

void PCString_ReleasePKMN(void){
//db "Release <PK><MN>?@"
    return PCString_MoveToWhere();
}

void PCString_MoveToWhere(void){
//db "Move to where?@"
    return PCString_ItsYourLastPKMN();
}

void PCString_ItsYourLastPKMN(void){
//db "It's your last <PK><MN>!@"
    return PCString_TheresNoRoom();
}

void PCString_TheresNoRoom(void){
//db "There's no room!@"
    return PCString_NoMoreUsablePKMN();
}

void PCString_NoMoreUsablePKMN(void){
//db "No more usable <PK><MN>!@"
    return PCString_RemoveMail();
}

void PCString_RemoveMail(void){
//db "Remove MAIL.@"
    return PCString_ReleasedPKMN();
}

void PCString_ReleasedPKMN(void){
//db "Released <PK><MN>.@"
    return PCString_Bye();
}

void PCString_Bye(void){
//db "Bye,@"
    return PCString_Stored();
}

void PCString_Stored(void){
//db "Stored @"
    return PCString_Got();
}

void PCString_Got(void){
//db "Got @"
    return PCString_Non();
}

void PCString_Non(void){
//db "Non.@"   //  unreferenced
    return PCString_BoxFull();
}

void PCString_BoxFull(void){
//db "The BOX is full.@"
    return PCString_PartyFull();
}

void PCString_PartyFull(void){
//db "The party's full!@"
    return PCString_NoReleasingEGGS();
}

void PCString_NoReleasingEGGS(void){
//db "No releasing EGGS!@"

    return v_ChangeBox();
}

void v_ChangeBox(void){
    CALL(aLoadStandardMenuHeader);
    CALL(aBillsPC_ClearTilemap);

loop:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aBillsPC_PrintBoxName);
    CALL(aBillsPC_PlaceChooseABoxString);
    LD_HL(mv_ChangeBox_MenuHeader);
    CALL(aCopyMenuHeader);
    XOR_A_A;
    LD_addr_A(wMenuScrollPosition);
    hlcoord(0, 4, wTilemap);
    LD_BC((8 << 8) | 9);
    CALL(aTextbox);
    CALL(aScrollingMenu);
    LD_A_addr(wMenuJoypad);
    CP_A(B_BUTTON);
    IF_Z goto done;
    CALL(aBillsPC_PlaceWhatsUpString);
    CALL(aBillsPC_ChangeBoxSubmenu);
    goto loop;

done:
    CALL(aCloseWindow);
    RET;

}

void BillsPC_ClearTilemap(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    LD_A(0x7f);
    CALL(aByteFill);
    RET;

}

void v_ChangeBox_MenuHeader(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['1', '5', '9', '12'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['SCROLLINGMENU_CALL_FUNCTION3_NO_SWITCH | SCROLLINGMENU_ENABLE_FUNCTION3'];  // flags
    //db ['4', '0'];  // rows, columns
    //db ['SCROLLINGMENU_ITEMS_NORMAL'];  // item format
    //dba ['.Boxes']
    //dba ['.PrintBoxNames']
    //dba ['NULL']
    //dba ['BillsPC_PrintBoxCountAndCapacity']


Boxes:
    //db ['NUM_BOXES'];
    for(int x = 0; x < NUM_BOXES; x++){
    //db ['x + 1'];
    }
    //db ['-1'];


PrintBoxNames:
    PUSH_DE;
    LD_A_addr(wMenuSelection);
    DEC_A;
    CALL(aGetBoxName);
    POP_HL;
    CALL(aPlaceString);
    RET;

}

void GetBoxName(void){
    LD_BC(BOX_NAME_LENGTH);
    LD_HL(wBoxNames);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    RET;

}

void BillsPC_PrintBoxCountAndCapacity(void){
    hlcoord(11, 7, wTilemap);
    LD_BC((5 << 8) | 7);
    CALL(aTextbox);
    LD_A_addr(wMenuSelection);
    CP_A(-1);
    RET_Z ;
    hlcoord(12, 9, wTilemap);
    LD_DE(mBillsPC_PrintBoxCountAndCapacity_Pokemon);
    CALL(aPlaceString);
    CALL(aGetBoxCount);
    LD_addr_A(wTextDecimalByte);
    hlcoord(13, 11, wTilemap);
    LD_DE(wTextDecimalByte);
    LD_BC((1 << 8) | 2);
    CALL(aPrintNum);
    LD_DE(mBillsPC_PrintBoxCountAndCapacity_OutOf20);
    CALL(aPlaceString);
    RET;


Pokemon:
    //db ['"#MON@"'];


OutOf20:
    //db ['"/{d:MONS_PER_BOX}@"'];  // "/20@"

    return GetBoxCount();
}

void GetBoxCount(void){
    LD_A_addr(wCurBox);
    LD_C_A;
    LD_A_addr(wMenuSelection);
    DEC_A;
    CP_A_C;
    IF_Z goto activebox;
    LD_C_A;
    LD_B(0);
    LD_HL(mGetBoxCount_BoxBankAddresses);
    ADD_HL_BC;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_B_A;
    CALL(aOpenSRAM);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hl;
    CALL(aCloseSRAM);
    LD_C_A;
    LD_A_addr(wSavedAtLeastOnce);
    AND_A_A;
    IF_Z goto newfile;
    LD_A_C;
    RET;


newfile:
    XOR_A_A;
    RET;


activebox:
    LD_A(BANK(sBoxCount));
    LD_B_A;
    CALL(aOpenSRAM);
    LD_HL(sBoxCount);
    LD_A_hl;
    CALL(aCloseSRAM);
    RET;


BoxBankAddresses:
    //table_width ['3', 'GetBoxCount.BoxBankAddresses']
    //dba ['sBox1']
    //dba ['sBox2']
    //dba ['sBox3']
    //dba ['sBox4']
    //dba ['sBox5']
    //dba ['sBox6']
    //dba ['sBox7']
    //dba ['sBox8']
    //dba ['sBox9']
    //dba ['sBox10']
    //dba ['sBox11']
    //dba ['sBox12']
    //dba ['sBox13']
    //dba ['sBox14']
    //assert_table_length ['NUM_BOXES']

    return BillsPC_PrintBoxName();
}

void BillsPC_PrintBoxName(void){
    hlcoord(0, 0, wTilemap);
    LD_B(2);
    LD_C(18);
    CALL(aTextbox);
    hlcoord(1, 2, wTilemap);
    LD_DE(mBillsPC_PrintBoxName_Current);
    CALL(aPlaceString);
    LD_A_addr(wCurBox);
    AND_A(0xf);
    CALL(aGetBoxName);
    hlcoord(11, 2, wTilemap);
    CALL(aPlaceString);
    RET;


Current:
    //db ['"CURRENT@"'];

    return BillsPC_ChangeBoxSubmenu();
}

void BillsPC_ChangeBoxSubmenu(void){
    LD_HL(mBillsPC_ChangeBoxSubmenu_MenuHeader);
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    CALL(aExitMenu);
    RET_C ;
    LD_A_addr(wMenuCursorY);
    CP_A(0x1);
    IF_Z goto Switch;
    CP_A(0x2);
    IF_Z goto Name;
    CP_A(0x3);
    IF_Z goto Print;
    AND_A_A;
    RET;


Print:
    CALL(aGetBoxCount);
    AND_A_A;
    IF_Z goto EmptyBox;
    LD_E_L;
    LD_D_H;
    LD_A_addr(wMenuSelection);
    DEC_A;
    LD_C_A;
    FARCALL(aPrintPCBox);
    CALL(aBillsPC_ClearTilemap);
    AND_A_A;
    RET;


EmptyBox:
    CALL(aBillsPC_PlaceEmptyBoxString_SFX);
    AND_A_A;
    RET;


Switch:
    LD_A_addr(wMenuSelection);
    DEC_A;
    LD_E_A;
    LD_A_addr(wCurBox);
    CP_A_E;
    RET_Z ;
    FARCALL(aChangeBoxSaveGame);
    RET;


Name:
    LD_B(NAME_BOX);
    LD_DE(wBoxNameBuffer);
    FARCALL(aNamingScreen);
    CALL(aClearTilemap);
    CALL(aLoadStandardFont);
    CALL(aLoadFontsBattleExtra);
    LD_A_addr(wMenuSelection);
    DEC_A;
    CALL(aGetBoxName);
    LD_E_L;
    LD_D_H;
    LD_HL(wBoxNameBuffer);
    LD_C(BOX_NAME_LENGTH - 1);
    CALL(aInitString);
    LD_A_addr(wMenuSelection);
    DEC_A;
    CALL(aGetBoxName);
    LD_DE(wBoxNameBuffer);
    CALL(aCopyName2);
    RET;

    hlcoord(11, 7, wTilemap);  // unreferenced


MenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '4', 'SCREEN_WIDTH - 1', '13'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['4'];  // items
    //db ['"SWITCH@"'];
    //db ['"NAME@"'];
    //db ['"PRINT@"'];
    //db ['"QUIT@"'];

    return BillsPC_PlaceChooseABoxString();
}

void BillsPC_PlaceChooseABoxString(void){
    LD_DE(mBillsPC_PlaceChooseABoxString_ChooseABox);
    JR(mBillsPC_PlaceChangeBoxString);


ChooseABox:
    //db ['"Choose a BOX.@"'];

    return BillsPC_PlaceWhatsUpString();
}

void BillsPC_PlaceWhatsUpString(void){
    LD_DE(mBillsPC_PlaceWhatsUpString_WhatsUp);
    JR(mBillsPC_PlaceChangeBoxString);


WhatsUp:
    //db ['"What\'s up?@"'];

    return BillsPC_PlaceEmptyBoxString_SFX();
}

void BillsPC_PlaceEmptyBoxString_SFX(void){
    LD_DE(mBillsPC_PlaceEmptyBoxString_SFX_NoMonString);
    CALL(aBillsPC_PlaceChangeBoxString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    RET;


NoMonString:
    //db ['"There\'s no #MON.@"'];

    return BillsPC_PlaceChangeBoxString();
}

void BillsPC_PlaceChangeBoxString(void){
    PUSH_DE;
    hlcoord(0, 14, wTilemap);
    LD_BC((2 << 8) | 18);
    CALL(aTextbox);
    POP_DE;
    hlcoord(1, 16, wTilemap);
    CALL(aPlaceString);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}
