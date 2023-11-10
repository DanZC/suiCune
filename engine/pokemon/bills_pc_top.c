#include "../../constants.h"
#include "bills_pc_top.h"
#include "../../home/copy.h"
#include "../../home/sram.h"

void v_BillsPC(void){
    CALL(av_BillsPC_CheckCanUsePC);
    RET_C ;
    CALL(av_BillsPC_LogIn);
    CALL(av_BillsPC_UseBillsPC);
    JP(mv_BillsPC_LogOut);


CheckCanUsePC:
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_NZ ;
    LD_HL(mv_BillsPC_PCGottaHavePokemonText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;


PCGottaHavePokemonText:
    //text_far ['_PCGottaHavePokemonText']
    //text_end ['?']


LogIn:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aLoadStandardMenuHeader);
    CALL(aClearPCItemScreen);
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    LD_HL(mv_BillsPC_PCWhatText);
    CALL(aPrintText);
    POP_AF;
    LD_addr_A(wOptions);
    CALL(aLoadFontsBattleExtra);
    RET;


PCWhatText:
    //text_far ['_PCWhatText']
    //text_end ['?']


LogOut:
    CALL(aCloseSubmenu);
    RET;


UseBillsPC:
    LD_HL(mv_BillsPC_MenuHeader);
    CALL(aLoadMenuHeader);
    LD_A(0x1);

loop:
    LD_addr_A(wMenuCursorPosition);
    CALL(aSetPalettes);
    XOR_A_A;
    LD_addr_A(wWhichIndexSet);
    LDH_addr_A(hBGMapMode);
    CALL(aDoNthMenu);
    IF_C goto cancel;
    LD_A_addr(wMenuCursorPosition);
    PUSH_AF;
    LD_A_addr(wMenuSelection);
    LD_HL(mv_BillsPC_Jumptable);
    RST(aJumpTable);
    POP_BC;
    LD_A_B;
    IF_NC goto loop;

cancel:
    CALL(aCloseWindow);
    RET;


MenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['0'];  // items
    //dw ['.items'];
    //dw ['PlaceMenuStrings'];
    //dw ['.strings'];


strings:
    //db ['"WITHDRAW <PK><MN>@"'];
    //db ['"DEPOSIT <PK><MN>@"'];
    //db ['"CHANGE BOX@"'];
    //db ['"MOVE <PK><MN> W/O MAIL@"'];
    //db ['"SEE YA!@"'];


Jumptable:
    //dw ['BillsPC_WithdrawMenu'];
    //dw ['BillsPC_DepositMenu'];
    //dw ['BillsPC_ChangeBoxMenu'];
    //dw ['BillsPC_MovePKMNMenu'];
    //dw ['BillsPC_SeeYa'];


items:
    //db ['5'];  // # items
    //db ['0'];  // WITHDRAW
    //db ['1'];  // DEPOSIT
    //db ['2'];  // CHANGE BOX
    //db ['3'];  // MOVE PKMN
    //db ['4'];  // SEE YA!
    //db ['-1'];

    return BillsPC_SeeYa();
}

void BillsPC_SeeYa(void){
    SCF;
    RET;

}

void BillsPC_MovePKMNMenu(void){
    CALL(aLoadStandardMenuHeader);
    FARCALL(aIsAnyMonHoldingMail);
    IF_NC goto no_mail;
    LD_HL(mBillsPC_MovePKMNMenu_PCMonHoldingMailText);
    CALL(aPrintText);
    goto quit;


no_mail:
    FARCALL(aStartMoveMonWOMail_SaveGame);
    IF_C goto quit;
    FARCALL(av_MovePKMNWithoutMail);
    CALL(aReturnToMapFromSubmenu);
    CALL(aClearPCItemScreen);


quit:
    CALL(aCloseWindow);
    AND_A_A;
    RET;


PCMonHoldingMailText:
    //text_far ['_PCMonHoldingMailText']
    //text_end ['?']

    return BillsPC_DepositMenu();
}

void BillsPC_DepositMenu(void){
    CALL(aLoadStandardMenuHeader);
    FARCALL(av_DepositPKMN);
    CALL(aReturnToMapFromSubmenu);
    CALL(aClearPCItemScreen);
    CALL(aCloseWindow);
    AND_A_A;
    RET;

}

void BillsPC_Deposit_CheckPartySize(void){
//  //  unreferenced
    LD_A_addr(wPartyCount);
    AND_A_A;
    IF_Z goto no_mon;
    CP_A(2);
    IF_C goto only_one_mon;
    AND_A_A;
    RET;


no_mon:
    LD_HL(mBillsPC_Deposit_CheckPartySize_PCNoSingleMonText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;


only_one_mon:
    LD_HL(mBillsPC_Deposit_CheckPartySize_PCCantDepositLastMonText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;


PCNoSingleMonText:
    //text_far ['_PCNoSingleMonText']
    //text_end ['?']


PCCantDepositLastMonText:
    //text_far ['_PCCantDepositLastMonText']
    //text_end ['?']

    return CheckCurPartyMonFainted();
}

void CheckCurPartyMonFainted(void){
    LD_HL(wPartyMon1HP);
    LD_DE(PARTYMON_STRUCT_LENGTH);
    LD_B(0x0);

loop:
    LD_A_addr(wCurPartyMon);
    CP_A_B;
    IF_Z goto skip;
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto notfainted;
    DEC_HL;


skip:
    INC_B;
    LD_A_addr(wPartyCount);
    CP_A_B;
    IF_Z goto done;
    ADD_HL_DE;
    goto loop;


done:
    SCF;
    RET;


notfainted:
    AND_A_A;
    RET;

}

bool CheckCurPartyMonFainted_Conv(void){
    if(wram->wCurPartyMon >= wram->wPartyCount)
        return true;
    // LD_HL(wPartyMon1HP);
    struct PartyMon* hl = wram->wPartyMon;
    // LD_DE(PARTYMON_STRUCT_LENGTH);
    // LD_B(0x0);
    uint8_t b = 0x0;

    do {
    // loop:
        // LD_A_addr(wCurPartyMon);
        // CP_A_B;
        // IF_Z goto skip;
        if(wram->wCurPartyMon != b) {
            // LD_A_hli;
            // OR_A_hl;
            // IF_NZ goto notfainted;
            if(hl[b].HP != 0) {
            // notfainted:
                // AND_A_A;
                // RET;
                return false;
            }
            // DEC_HL;
        }

    // skip:
        // INC_B;
        // LD_A_addr(wPartyCount);
        // CP_A_B;
        // IF_Z goto done;
        // ADD_HL_DE;
        // goto loop;
    } while(++b != wram->wPartyCount);

// done:
    // SCF;
    // RET;
    return true;
}

void BillsPC_WithdrawMenu(void){
    CALL(aLoadStandardMenuHeader);
    FARCALL(av_WithdrawPKMN);
    CALL(aReturnToMapFromSubmenu);
    CALL(aClearPCItemScreen);
    CALL(aCloseWindow);
    AND_A_A;
    RET;

}

void BillsPC_Withdraw_CheckPartySize(void){
//  //  unreferenced
    LD_A_addr(wPartyCount);
    CP_A(PARTY_LENGTH);
    IF_NC goto party_full;
    AND_A_A;
    RET;


party_full:
    LD_HL(mPCCantTakeText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;

}

void PCCantTakeText(void){
    //text_far ['_PCCantTakeText']
    //text_end ['?']

    return BillsPC_ChangeBoxMenu();
}

void BillsPC_ChangeBoxMenu(void){
    FARCALL(av_ChangeBox);
    AND_A_A;
    RET;

}

void ClearPCItemScreen(void){
    CALL(aDisableSpriteUpdates);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    LD_A(0x7f);
    CALL(aByteFill);
    hlcoord(0, 0, wTilemap);
    LD_BC((10 << 8) | 18);
    CALL(aTextbox);
    hlcoord(0, 12, wTilemap);
    LD_BC((4 << 8) | 18);
    CALL(aTextbox);
    CALL(aWaitBGMap2);
    CALL(aSetPalettes);  // load regular palettes?
    RET;

}

void CopyBoxmonToTempMon(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(sBoxMon1Species);
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_DE(wTempMonSpecies);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A(BANK(sBoxMon1Species));
    CALL(aOpenSRAM);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void CopyBoxmonToTempMon_Conv(void){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(sBoxMon1Species);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    uint16_t hl = sBoxMon1Species + wram->wCurPartyMon * BOXMON_STRUCT_LENGTH;
    // LD_DE(wTempMonSpecies);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // LD_A(BANK(sBoxMon1Species));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(sBoxMon1Species));
    // CALL(aCopyBytes);
    CopyBytes_Conv(wTempMonSpecies, hl, BOXMON_STRUCT_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void LoadBoxMonListing(void){
//  //  unreferenced
    LD_A_addr(wCurBox);
    CP_A_B;
    IF_Z goto same_box;
    LD_A_B;
    LD_HL(mLoadBoxMonListing_BoxAddresses);
    LD_BC(3);
    CALL(aAddNTimes);
    LD_A_hli;
    PUSH_AF;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_AF;
    goto okay;


same_box:
    LD_A(BANK(sBoxCount));
    LD_HL(sBoxCount);


okay:
    CALL(aOpenSRAM);
    LD_A_hl;
    LD_BC(sBoxMons - sBox);
    ADD_HL_BC;
    LD_B_A;
    LD_C(0x0);
    LD_DE(wBoxPartialData);
    LD_A_B;
    AND_A_A;
    IF_Z goto empty_box;

loop:
    PUSH_HL;
    PUSH_BC;
    LD_A_C;
    LD_BC(sBoxMon1Species - sBoxMons);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hl;
    LD_de_A;
    INC_DE;
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    POP_BC;
    POP_HL;

    PUSH_HL;
    PUSH_BC;
    LD_A_C;
    LD_BC(sBoxMonNicknames - sBoxMons);
    ADD_HL_BC;
    CALL(aSkipNames);
    CALL(aCopyBytes);
    POP_BC;
    POP_HL;

    PUSH_HL;
    PUSH_BC;
    LD_A_C;
    LD_BC(MON_LEVEL);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hl;
    LD_de_A;
    INC_DE;
    POP_BC;
    POP_HL;

    PUSH_HL;
    PUSH_BC;
    LD_A_C;
    LD_BC(MON_DVS);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hli;
    AND_A(0xf0);
    LD_B_A;
    LD_A_hl;
    AND_A(0xf0);
    SWAP_A;
    OR_A_B;
    LD_B_A;
    LD_A_addr(wBaseGender);
    CP_A_B;
    LD_A(0x1);
    IF_C goto okay2;
    XOR_A_A;

okay2:
    LD_de_A;
    INC_DE;
    POP_BC;
    POP_HL;

    INC_C;
    DEC_B;
    IF_NZ goto loop;

empty_box:
    CALL(aCloseSRAM);
    RET;


BoxAddresses:
    //table_width ['3', 'LoadBoxMonListing.BoxAddresses']
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

}
