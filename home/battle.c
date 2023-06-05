#include "../constants.h"
#include "battle.h"
#include "array.h"
#include "copy.h"
#include "text.h"
#include "tilemap.h"

void GetPartyParamLocation(void){
    //  Get the location of parameter a from wCurPartyMon in hl
    PUSH_BC;
    LD_HL(wPartyMons);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wCurPartyMon);
    CALL(aGetPartyLocation);
    POP_BC;
    RET;

}

void GetPartyLocation(void){
    //  Add the length of a PartyMon struct to hl a times.
    LD_BC(PARTYMON_STRUCT_LENGTH);
    JP(mAddNTimes);

}

//  Get the location of parameter a from wCurPartyMon in hl
uint16_t GetPartyParamLocation_Conv(uint8_t a){
    // PUSH_BC;
    // LD_HL(wPartyMons);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    uint16_t hl = wPartyMons + a;

    // LD_A_addr(wCurPartyMon);
    // CALL(aGetPartyLocation);
    // POP_BC;
    // RET;
    return GetPartyLocation_Conv(hl, gb_read(wCurPartyMon));
}

//  Add the length of a PartyMon struct to hl a times.
uint16_t GetPartyLocation_Conv(uint16_t hl, uint8_t a){
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // JP(mAddNTimes);
    return AddNTimes_Conv(PARTYMON_STRUCT_LENGTH, hl, a);
}

void GetDexNumber(void){
    //  //  unreferenced
//  Probably used in gen 1 to convert index number to dex number
//  Not required in gen 2 because index number == dex number
    PUSH_HL;
    LD_A_B;
    DEC_A;
    LD_B(0);
    ADD_HL_BC;
    LD_HL(mBaseData + BASE_DEX_NO);
    LD_BC(BASE_DATA_SIZE);
    CALL(aAddNTimes);
    LD_A(BANK(aBaseData));
    CALL(aGetFarWord);
    LD_B_L;
    LD_C_H;
    POP_HL;
    RET;

}

void UserPartyAttr(void){
        PUSH_AF;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto ot;
    POP_AF;
    JR(mBattlePartyAttr);

ot:
        POP_AF;
    JR(mOTPartyAttr);

}

uint16_t UserPartyAttr_Conv(uint8_t a){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ot;
    if(gb_read(hBattleTurn) != 0)
    {
        // JR(mOTPartyAttr);
        return OTPartyAttr_Conv(a);
    }

    // JR(mBattlePartyAttr);
    return BattlePartyAttr_Conv(a);
}

void OpponentPartyAttr(void){
        PUSH_AF;
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ot;
    POP_AF;
    JR(mBattlePartyAttr);

ot:
        POP_AF;
    JR(mOTPartyAttr);

}

uint16_t OpponentPartyAttr_Conv(uint8_t a){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ot;
    if(gb_read(hBattleTurn) == 0)
    {
        // JR(mOTPartyAttr);
        return OTPartyAttr_Conv(a);
    }

    // JR(mBattlePartyAttr);
    return BattlePartyAttr_Conv(a);
}

void BattlePartyAttr(void){
    //  Get attribute a from the party struct of the active battle mon.
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(wPartyMons);
    ADD_HL_BC;
    LD_A_addr(wCurBattleMon);
    CALL(aGetPartyLocation);
    POP_BC;
    RET;

}

//  Get attribute a from the party struct of the active battle mon.
uint16_t BattlePartyAttr_Conv(uint8_t a){
    // PUSH_BC;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wPartyMons);
    // ADD_HL_BC;
    uint16_t hl = wPartyMons + a;

    // LD_A_addr(wCurBattleMon);
    // CALL(aGetPartyLocation);
    // POP_BC;
    // RET;
    return GetPartyLocation_Conv(hl, gb_read(wCurBattleMon));
}

void OTPartyAttr(void){
    //  Get attribute a from the party struct of the active enemy mon.
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartyMon1Species);
    ADD_HL_BC;
    LD_A_addr(wCurOTMon);
    CALL(aGetPartyLocation);
    POP_BC;
    RET;

}

//  Get attribute a from the party struct of the active enemy mon.
uint16_t OTPartyAttr_Conv(uint8_t a){
    // PUSH_BC;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wOTPartyMon1Species);
    // ADD_HL_BC;
    uint16_t hl = wOTPartyMon1Species + a;

    // LD_A_addr(wCurOTMon);
    // CALL(aGetPartyLocation);
    // POP_BC;
    // RET;
    return GetPartyLocation_Conv(hl, gb_read(wCurOTMon));
}

void ResetDamage(void){
        XOR_A_A;
    LD_addr_A(wCurDamage);
    LD_addr_A(wCurDamage + 1);
    RET;

}

void ResetDamage_Conv(void){
    // XOR_A_A;
    // LD_addr_A(wCurDamage);
    // LD_addr_A(wCurDamage + 1);
    gb_write16(wCurDamage, 0);
}

void SetPlayerTurn(void){
        XOR_A_A;
    LDH_addr_A(hBattleTurn);
    RET;

}

void SetPlayerTurn_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBattleTurn);
    gb_write(hBattleTurn, 0); // Player's turn
}

void SetEnemyTurn(void){
        LD_A(1);
    LDH_addr_A(hBattleTurn);
    RET;

}

void SetEnemyTurn_Conv(void){
    // LD_A(1);
    // LDH_addr_A(hBattleTurn);
    gb_write(hBattleTurn, 1); // Enemy's turn
}

void UpdateOpponentInParty(void){
        LDH_A_addr(hBattleTurn);
    AND_A_A;
    JR_Z (mUpdateEnemyMonInParty);
    JR(mUpdateBattleMonInParty);

}

void UpdateUserInParty(void){
        LDH_A_addr(hBattleTurn);
    AND_A_A;
    JR_Z (mUpdateBattleMonInParty);
    JR(mUpdateEnemyMonInParty);

}

void UpdateOpponentInParty_Conv(void){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JR_Z (mUpdateEnemyMonInParty);
    if(gb_read(hBattleTurn) == 0)
        return UpdateEnemyMonInParty_Conv();

    // JR(mUpdateBattleMonInParty);
    return UpdateBattleMonInParty_Conv();
}

void UpdateUserInParty_Conv(void){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JR_Z (mUpdateBattleMonInParty);
    if(gb_read(hBattleTurn) == 0)
        return UpdateBattleMonInParty_Conv();
    
    // JR(mUpdateEnemyMonInParty);
    return UpdateEnemyMonInParty_Conv();
}

void UpdateBattleMonInParty(void){
    //  Update level, status, current HP

    LD_A_addr(wCurBattleMon);

    return UpdateBattleMon();
}

//  Update level, status, current HP
void UpdateBattleMonInParty_Conv(void){
    // LD_A_addr(wCurBattleMon);
    // return UpdateBattleMon();
    return UpdateBattleMon_Conv(gb_read(wCurBattleMon));
}

void UpdateBattleMon(void){
        LD_HL(wPartyMon1Level);
    CALL(aGetPartyLocation);

    LD_D_H;
    LD_E_L;
    LD_HL(wBattleMonLevel);
    LD_BC(wBattleMonMaxHP - wBattleMonLevel);
    JP(mCopyBytes);

}

void UpdateBattleMon_Conv(uint8_t a){
    // LD_HL(wPartyMon1Level);
    // CALL(aGetPartyLocation);
    // LD_D_H;
    // LD_E_L;
    uint16_t de = GetPartyLocation_Conv(wPartyMon1Level, a);

    // LD_HL(wBattleMonLevel);
    // LD_BC(wBattleMonMaxHP - wBattleMonLevel);
    // JP(mCopyBytes);
    CopyBytes_Conv(de, wBattleMonLevel, (wBattleMonMaxHP - wBattleMonLevel));
}

void UpdateEnemyMonInParty(void){
    //  Update level, status, current HP

//  No wildmons.
    LD_A_addr(wBattleMode);
    DEC_A;
    RET_Z ;

    LD_A_addr(wCurOTMon);
    LD_HL(wOTPartyMon1Level);
    CALL(aGetPartyLocation);

    LD_D_H;
    LD_E_L;
    LD_HL(wEnemyMonLevel);
    LD_BC(wEnemyMonMaxHP - wEnemyMonLevel);
    JP(mCopyBytes);

}

//  Update level, status, current HP
void UpdateEnemyMonInParty_Conv(void){
//  No wildmons.
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // RET_Z ;
    if(gb_read(wBattleMode) - 1 == 0)
        return;

    // LD_A_addr(wCurOTMon);
    // LD_HL(wOTPartyMon1Level);
    // CALL(aGetPartyLocation);
    // LD_D_H;
    // LD_E_L;
    uint16_t de = GetPartyLocation_Conv(wOTPartyMon1Level, gb_read(wCurOTMon));

    // LD_HL(wEnemyMonLevel);
    // LD_BC(wEnemyMonMaxHP - wEnemyMonLevel);
    // JP(mCopyBytes);
    CopyBytes_Conv(de, wEnemyMonLevel, (wEnemyMonMaxHP - wEnemyMonLevel));
}

void RefreshBattleHuds(void){
        CALL(aUpdateBattleHuds);
    LD_C(3);
    CALL(aDelayFrames);
    JP(mWaitBGMap);

}

void UpdateBattleHuds(void){
        FARCALL(aUpdatePlayerHUD);
    FARCALL(aUpdateEnemyHUD);
    RET;

// INCLUDE "home/battle_vars.asm"

    return FarCopyRadioText();
}

void FarCopyRadioText(void){
        INC_HL;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
    LD_A_E;
    LD_L_A;
    LD_A_D;
    LD_H_A;
    LD_DE(wRadioText);
    LD_BC(2 * SCREEN_WIDTH);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
    RET;

}

void MobileTextBorder(void){
    // For mobile link battles only.
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    RET_C ;

// Draw a cell phone icon at the
// top right corner of the border.
    hlcoord(19, 12, wTilemap);
    LD_hl(0x5e);  // top
    hlcoord(19, 13, wTilemap);
    LD_hl(0x5f);  // bottom
    RET;

}

// For mobile link battles only.
void MobileTextBorder_Conv(void){
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // RET_C ;
    if(gb_read(wLinkMode) < LINK_MOBILE)
        return;

// Draw a cell phone icon at the
// top right corner of the border.
    // hlcoord(19, 12, wTilemap);
    // LD_hl(0x5e);  // top
    gb_write(coord(19, 12, wTilemap), 0x5e);  // top
    // hlcoord(19, 13, wTilemap);
    // LD_hl(0x5f);  // bottom
    gb_write(coord(19, 12, wTilemap), 0x5f);  // bottom
}

void BattleTextbox(void){
    //  Open a textbox and print text at hl.
    PUSH_HL;
    CALL(aSpeechTextbox);
    CALL(aMobileTextBorder);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    POP_HL;
    CALL(aPrintTextboxText);
    RET;

}

//  Open a textbox and print text at hl.
void BattleTextbox_Conv(uint16_t hl){
    // PUSH_HL;
    // CALL(aSpeechTextbox);
    SpeechTextbox_Conv();

    // CALL(aMobileTextBorder);
    MobileTextBorder_Conv();

    CALL(aUpdateSprites);

    // CALL(aApplyTilemap);
    ApplyTilemap_Conv();

    // POP_HL;
    // CALL(aPrintTextboxText);
    PrintTextboxText_Conv(hl);
    // RET;
}

void StdBattleTextbox(void){
    //  Open a textbox and print battle text at 20:hl.

    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A(BANK(aBattleText));
    RST(aBankswitch);

    CALL(aBattleTextbox);

    POP_AF;
    RST(aBankswitch);
    RET;

}

//  Open a textbox and print battle text at 20:hl.
void StdBattleTextbox_Conv(uint16_t hl){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A(BANK(aBattleText));
    // RST(aBankswitch);
    bank_push(BANK(aBattleText));

    // CALL(aBattleTextbox);
    BattleTextbox_Conv(hl);

    // POP_AF;
    // RST(aBankswitch);
    // RET;
    bank_pop;
}

void GetBattleAnimPointer(void){
        LD_A(BANK(aBattleAnimations));
    RST(aBankswitch);

    LD_A_hli;
    LD_addr_A(wBattleAnimAddress);
    LD_A_hl;
    LD_addr_A(wBattleAnimAddress + 1);

// ClearBattleAnims is the only function that calls this...
    LD_A(BANK(aClearBattleAnims));
    RST(aBankswitch);

    RET;

}

void GetBattleAnimPointer_Conv(uint16_t hl){
    // LD_A(BANK(aBattleAnimations));
    // RST(aBankswitch);
    Bankswitch_Conv(BANK(aBattleAnimations));

    // LD_A_hli;
    // LD_addr_A(wBattleAnimAddress);
    // LD_A_hl;
    // LD_addr_A(wBattleAnimAddress + 1);
    gb_write16(wBattleAnimAddress, gb_read16(hl));

// ClearBattleAnims is the only function that calls this...
    // LD_A(BANK(aClearBattleAnims));
    // RST(aBankswitch);
    Bankswitch_Conv(BANK(aClearBattleAnims));
}

void GetBattleAnimByte(void){
        PUSH_HL;
    PUSH_DE;

    LD_HL(wBattleAnimAddress);
    LD_E_hl;
    INC_HL;
    LD_D_hl;

    LD_A(BANK(aBattleAnimations));
    RST(aBankswitch);

    LD_A_de;
    LD_addr_A(wBattleAnimByte);
    INC_DE;

    LD_A(BANK(aBattleAnimCommands));
    RST(aBankswitch);

    LD_hl_D;
    DEC_HL;
    LD_hl_E;

    POP_DE;
    POP_HL;

    LD_A_addr(wBattleAnimByte);
    RET;

}

uint8_t GetBattleAnimByte_Conv(void){
    // PUSH_HL;
    // PUSH_DE;

    // LD_HL(wBattleAnimAddress);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    uint16_t de = gb_read16(wBattleAnimAddress);

    // LD_A(BANK(aBattleAnimations));
    // RST(aBankswitch);
    Bankswitch_Conv(BANK(aBattleAnimations));

    // LD_A_de;
    // LD_addr_A(wBattleAnimByte);
    // INC_DE;
    gb_write(wBattleAnimByte, gb_read(de++));

    // LD_A(BANK(aBattleAnimCommands));
    // RST(aBankswitch);
    Bankswitch_Conv(BANK(aBattleAnimCommands));

    // LD_hl_D;
    // DEC_HL;
    // LD_hl_E;
    gb_write16(wBattleAnimAddress, de);

    // POP_DE;
    // POP_HL;

    // LD_A_addr(wBattleAnimByte);
    // RET;
    return gb_read(wBattleAnimByte);
}

void PushLYOverrides(void){
        LDH_A_addr(hLCDCPointer);
    AND_A_A;
    RET_Z ;

    LD_A(LOW(wLYOverridesBackup));
    LD_addr_A(wRequested2bppSource);
    LD_A(HIGH(wLYOverridesBackup));
    LD_addr_A(wRequested2bppSource + 1);

    LD_A(LOW(wLYOverrides));
    LD_addr_A(wRequested2bppDest);
    LD_A(HIGH(wLYOverrides));
    LD_addr_A(wRequested2bppDest + 1);

    LD_A((wLYOverridesEnd - wLYOverrides) / LEN_2BPP_TILE);
    LD_addr_A(wRequested2bppSize);
    RET;

}
