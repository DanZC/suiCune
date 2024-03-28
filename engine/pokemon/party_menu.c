#include "../../constants.h"
#include "party_menu.h"
#include "../../home/gfx.h"
#include "../gfx/color.h"
#include "../gfx/sprites.h"

void SelectMonFromParty(void){
    CALL(aDisableSpriteUpdates);
    XOR_A_A;
    LD_addr_A(wPartyMenuActionText);
    CALL(aClearBGPalettes);
    CALL(aInitPartyMenuLayout);
    CALL(aWaitBGMap);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    CALL(aPartyMenuSelect);
    CALL(aReturnToMapWithSpeechTextbox);
    RET;

}

void SelectTradeOrDayCareMon(void){
    LD_A_B;
    LD_addr_A(wPartyMenuActionText);
    CALL(aDisableSpriteUpdates);
    CALL(aClearBGPalettes);
    CALL(aInitPartyMenuLayout);
    CALL(aWaitBGMap);
    LD_B(SCGB_PARTY_MENU);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    CALL(aPartyMenuSelect);
    CALL(aReturnToMapWithSpeechTextbox);
    RET;

}

void InitPartyMenuLayout(void){
    CALL(aLoadPartyMenuGFX);
    CALL(aInitPartyMenuWithCancel);
    CALL(aInitPartyMenuGFX);
    CALL(aWritePartyMenuTilemap);
    CALL(aPrintPartyMenuText);
    RET;

}

void LoadPartyMenuGFX(void){
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();
    // CALLFAR(aInitPartyMenuPalettes);
    InitPartyMenuPalettes_Conv();
    // CALLFAR(aClearSpriteAnims2);
    ClearSpriteAnims2_Conv();
    // RET;
}

void WritePartyMenuTilemap(void){
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    LD_A(0x7f);
    CALL(aByteFill);  // blank the tilemap
    CALL(aGetPartyMenuQualityIndexes);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto end;
    PUSH_HL;
    LD_HL(mWritePartyMenuTilemap_Jumptable);
    RST(aJumpTable);
    POP_HL;
    goto loop;

end:
    POP_AF;
    LD_addr_A(wOptions);
    RET;


Jumptable:
//  entries correspond to PARTYMENUQUALITY_* constants
    //dw ['PlacePartyNicknames'];
    //dw ['PlacePartyHPBar'];
    //dw ['PlacePartyMenuHPDigits'];
    //dw ['PlacePartyMonLevel'];
    //dw ['PlacePartyMonStatus'];
    //dw ['PlacePartyMonTMHMCompatibility'];
    //dw ['PlacePartyMonEvoStoneCompatibility'];
    //dw ['PlacePartyMonGender'];
    //dw ['PlacePartyMonMobileBattleSelection'];

    return PlacePartyNicknames();
}

void PlacePartyNicknames(void){
    hlcoord(3, 1, wTilemap);
    LD_A_addr(wPartyCount);
    AND_A_A;
    IF_Z goto end;
    LD_C_A;
    LD_B(0);

loop:
    PUSH_BC;
    PUSH_HL;
    PUSH_HL;
    LD_HL(wPartyMonNicknames);
    LD_A_B;
    CALL(aGetNickname);
    POP_HL;
    CALL(aPlaceString);
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;


end:
    DEC_HL;
    DEC_HL;
    LD_DE(mPlacePartyNicknames_CancelString);
    CALL(aPlaceString);
    RET;


CancelString:
    //db ['"CANCEL@"'];

    return PlacePartyHPBar();
}

void PlacePartyHPBar(void){
    XOR_A_A;
    LD_addr_A(wSGBPals);
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_B(0);
    hlcoord(11, 2, wTilemap);

loop:
    PUSH_BC;
    PUSH_HL;
    CALL(aPartyMenuCheckEgg);
    IF_Z goto skip;
    PUSH_HL;
    CALL(aPlacePartymonHPBar);
    POP_HL;
    LD_D(0x6);
    LD_B(0x0);
    CALL(aDrawBattleHPBar);
    LD_HL(wHPPals);
    LD_A_addr(wSGBPals);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    CALL(aSetHPPal);
    LD_B(SCGB_PARTY_MENU_HP_BARS);
    CALL(aGetSGBLayout);

skip:
    LD_HL(wSGBPals);
    INC_hl;
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    LD_B(SCGB_PARTY_MENU);
    CALL(aGetSGBLayout);
    RET;

}

void PlacePartymonHPBar(void){
    LD_A_B;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1HP);
    CALL(aAddNTimes);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto not_fainted;
    XOR_A_A;
    LD_E_A;
    LD_C_A;
    RET;


not_fainted:
    DEC_HL;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_E_A;
    PREDEF(pComputeHPBarPixels);
    RET;

}

uint8_t PlacePartymonHPBar_Conv(uint8_t b){
    // LD_A_B;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_HL(wPartyMon1HP);
    // CALL(aAddNTimes);
    // LD_A_hli;
    // OR_A_hl;
    // IF_NZ goto not_fainted;
    if(wram->wPartyMon[b].HP == 0) {
        // XOR_A_A;
        // LD_E_A;
        // LD_C_A;
        // RET;
        return 0;
    }


// not_fainted:
    // DEC_HL;
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_C_A;
    uint16_t bc = ReverseEndian16(wram->wPartyMon[b].HP);
    // LD_A_hli;
    // LD_D_A;
    // LD_A_hli;
    // LD_E_A;
    uint16_t de = ReverseEndian16(wram->wPartyMon[b].maxHP);
    // PREDEF(pComputeHPBarPixels);
    return bc * (6 * 8) / de;
    // RET;
}

void PlacePartyMenuHPDigits(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_B(0);
    hlcoord(13, 1, wTilemap);

loop:
    PUSH_BC;
    PUSH_HL;
    CALL(aPartyMenuCheckEgg);
    IF_Z goto next;
    PUSH_HL;
    LD_A_B;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1HP);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    POP_HL;
    PUSH_DE;
    LD_BC((2 << 8) | 3);
    CALL(aPrintNum);
    POP_DE;
    LD_A(0xf3);
    LD_hli_A;
    INC_DE;
    INC_DE;
    LD_BC((2 << 8) | 3);
    CALL(aPrintNum);


next:
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void PlacePartyMonLevel(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_B(0);
    hlcoord(8, 2, wTilemap);

loop:
    PUSH_BC;
    PUSH_HL;
    CALL(aPartyMenuCheckEgg);
    IF_Z goto next;
    PUSH_HL;
    LD_A_B;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1Level);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    POP_HL;
    LD_A_de;
    CP_A(100);  // This is distinct from MAX_LEVEL.
    IF_NC goto ThreeDigits;
    LD_A(0x6e);
    LD_hli_A;
    LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
// jr .okay

ThreeDigits:
    LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 3);
//  .okay
    CALL(aPrintNum);


next:
    POP_HL;
    LD_DE(SCREEN_WIDTH * 2);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void PlacePartyMonStatus(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_B(0);
    hlcoord(5, 2, wTilemap);

loop:
    PUSH_BC;
    PUSH_HL;
    CALL(aPartyMenuCheckEgg);
    IF_Z goto next;
    PUSH_HL;
    LD_A_B;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1Status);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    POP_HL;
    CALL(aPlaceStatusString);


next:
    POP_HL;
    LD_DE(SCREEN_WIDTH * 2);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void PlacePartyMonTMHMCompatibility(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_B(0);
    hlcoord(12, 2, wTilemap);

loop:
    PUSH_BC;
    PUSH_HL;
    CALL(aPartyMenuCheckEgg);
    IF_Z goto next;
    PUSH_HL;
    LD_HL(wPartySpecies);
    LD_E_B;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);
    PREDEF(pCanLearnTMHMMove);
    POP_HL;
    CALL(aPlacePartyMonTMHMCompatibility_PlaceAbleNotAble);
    CALL(aPlaceString);


next:
    POP_HL;
    LD_DE(SCREEN_WIDTH * 2);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    RET;


PlaceAbleNotAble:
    LD_A_C;
    AND_A_A;
    IF_NZ goto able;
    LD_DE(mPlacePartyMonTMHMCompatibility_string_not_able);
    RET;


able:
    LD_DE(mPlacePartyMonTMHMCompatibility_string_able);
    RET;


string_able:
    //db ['"ABLE@"'];


string_not_able:
    //db ['"NOT ABLE@"'];

    return PlacePartyMonEvoStoneCompatibility();
}

void PlacePartyMonEvoStoneCompatibility(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_B(0);
    hlcoord(12, 2, wTilemap);

loop:
    PUSH_BC;
    PUSH_HL;
    CALL(aPartyMenuCheckEgg);
    IF_Z goto next;
    PUSH_HL;
    LD_A_B;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1Species);
    CALL(aAddNTimes);
    LD_A_hl;
    DEC_A;
    LD_E_A;
    LD_D(0);
    LD_HL(mEvosAttacksPointers);
    ADD_HL_DE;
    ADD_HL_DE;
    CALL(aPlacePartyMonEvoStoneCompatibility_DetermineCompatibility);
    POP_HL;
    CALL(aPlaceString);


next:
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    RET;


DetermineCompatibility:
    LD_DE(wStringBuffer1);
    LD_A(BANK(aEvosAttacksPointers));
    LD_BC(2);
    CALL(aFarCopyBytes);
    LD_HL(wStringBuffer1);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wStringBuffer1);
    // LD_A(BANK("Evolutions and Attacks"));
    LD_BC(10);
    CALL(aFarCopyBytes);
    LD_HL(wStringBuffer1);

loop2:
    LD_A_hli;
    AND_A_A;
    IF_Z goto nope;
    INC_HL;
    INC_HL;
    CP_A(EVOLVE_ITEM);
    IF_NZ goto loop2;
    DEC_HL;
    DEC_HL;
    LD_A_addr(wCurItem);
    CP_A_hl;
    INC_HL;
    INC_HL;
    IF_NZ goto loop2;
    LD_DE(mPlacePartyMonEvoStoneCompatibility_string_able);
    RET;


nope:
    LD_DE(mPlacePartyMonEvoStoneCompatibility_string_not_able);
    RET;


string_able:
    //db ['"ABLE@"'];

string_not_able:
    //db ['"NOT ABLE@"'];

    return PlacePartyMonGender();
}

void PlacePartyMonGender(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_B(0);
    hlcoord(12, 2, wTilemap);

loop:
    PUSH_BC;
    PUSH_HL;
    CALL(aPartyMenuCheckEgg);
    IF_Z goto next;
    LD_addr_A(wCurPartySpecies);
    PUSH_HL;
    LD_A_B;
    LD_addr_A(wCurPartyMon);
    XOR_A_A;
    LD_addr_A(wMonType);
    CALL(aGetGender);
    LD_DE(mPlacePartyMonGender_unknown);
    IF_C goto got_gender;
    LD_DE(mPlacePartyMonGender_male);
    IF_NZ goto got_gender;
    LD_DE(mPlacePartyMonGender_female);


got_gender:
    POP_HL;
    CALL(aPlaceString);


next:
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    RET;


male:
    //db ['"♂…MALE@"'];


female:
    //db ['"♀…FEMALE@"'];


unknown:
    //db ['"…UNKNOWN@"'];

    return PlacePartyMonMobileBattleSelection();
}

void PlacePartyMonMobileBattleSelection(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_B(0);
    hlcoord(12, 1, wTilemap);

loop:
    PUSH_BC;
    PUSH_HL;
    LD_DE(mPlacePartyMonMobileBattleSelection_String_Sanka_Shinai);
    CALL(aPlaceString);
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    INC_B;
    DEC_C;
    IF_NZ goto loop;
    LD_A_L;
    LD_E(MON_NAME_LENGTH);
    SUB_A_E;
    LD_L_A;
    LD_A_H;
    SBC_A(0x0);
    LD_H_A;
    LD_DE(mPlacePartyMonMobileBattleSelection_String_Kettei_Yameru);
    CALL(aPlaceString);
    LD_B(0x3);
    LD_C(0x0);
    LD_HL(wd002);
    LD_A_hl;

loop2:
    PUSH_HL;
    PUSH_BC;
    hlcoord(12, 1, wTilemap);

loop3:
    AND_A_A;
    IF_Z goto done;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    DEC_A;
    goto loop3;


done:
    LD_DE(mPlacePartyMonMobileBattleSelection_String_Banme);
    PUSH_HL;
    CALL(aPlaceString);
    POP_HL;
    POP_BC;
    PUSH_BC;
    PUSH_HL;
    LD_A_C;
    LD_HL(mPlacePartyMonMobileBattleSelection_Strings_1_2_3);
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aPlaceString);
    POP_BC;
    POP_HL;
    INC_HL;
    LD_A_hl;
    INC_C;
    DEC_B;
    RET_Z ;
    goto loop2;


String_Banme:
    //db ['"\u3000ばんめ\u3000\u3000@"'];  // Place

String_Sanka_Shinai:
    //db ['"さんかしない@"'];  // Cancel

String_Kettei_Yameru:
    //db ['"けってい\u3000\u3000やめる@"'];  // Quit

Strings_1_2_3:
    //db ['"１@"', '"２@"', '"３@"'];  // 1st, 2nd, 3rd

    return PartyMenuCheckEgg();
}

void PartyMenuCheckEgg(void){
    LD_A(LOW(wPartySpecies));
    ADD_A_B;
    LD_E_A;
    LD_A(HIGH(wPartySpecies));
    ADC_A(0);
    LD_D_A;
    LD_A_de;
    CP_A(EGG);
    RET;

}

void GetPartyMenuQualityIndexes(void){
    LD_A_addr(wPartyMenuActionText);
    AND_A(0xf0);
    IF_NZ goto skip;
    LD_A_addr(wPartyMenuActionText);
    AND_A(0xf);
    LD_E_A;
    LD_D(0);
    LD_HL(mPartyMenuQualityPointers);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;


skip:
    LD_HL(mPartyMenuQualityPointers_Default);
    RET;

// INCLUDE "data/party_menu_qualities.asm"

    return InitPartyMenuGFX();
}

void InitPartyMenuGFX(void){
    LD_HL(wPartyCount);
    LD_A_hli;
    AND_A_A;
    RET_Z ;
    LD_C_A;
    XOR_A_A;
    LDH_addr_A(hObjectStructIndex);

loop:
    PUSH_BC;
    PUSH_HL;
    LD_HL(mLoadMenuMonIcon);
    LD_A(BANK(aLoadMenuMonIcon));
    LD_E(MONICON_PARTYMENU);
    RST(aFarCall);
    LDH_A_addr(hObjectStructIndex);
    INC_A;
    LDH_addr_A(hObjectStructIndex);
    POP_HL;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    CALLFAR(aPlaySpriteAnimations);
    RET;

}

void InitPartyMenuWithCancel(void){
//  with cancel
    XOR_A_A;
    LD_addr_A(wSwitchMon);
    LD_DE(mPartyMenu2DMenuData);
    CALL(aLoad2DMenuData);
    LD_A_addr(wPartyCount);
    INC_A;
    LD_addr_A(w2DMenuNumRows);  // list length
    DEC_A;
    LD_B_A;
    LD_A_addr(wPartyMenuCursor);
    AND_A_A;
    IF_Z goto skip;
    INC_B;
    CP_A_B;
    IF_C goto done;


skip:
    LD_A(1);


done:
    LD_addr_A(wMenuCursorY);
    LD_A(A_BUTTON | B_BUTTON);
    LD_addr_A(wMenuJoypadFilter);
    RET;

}

void InitPartyMenuNoCancel(void){
//  no cancel
    LD_DE(mPartyMenu2DMenuData);
    CALL(aLoad2DMenuData);
    LD_A_addr(wPartyCount);
    LD_addr_A(w2DMenuNumRows);  // list length
    LD_B_A;
    LD_A_addr(wPartyMenuCursor);
    AND_A_A;
    IF_Z goto skip;
    INC_B;
    CP_A_B;
    IF_C goto done;

skip:
    LD_A(1);

done:
    LD_addr_A(wMenuCursorY);
    LD_A(A_BUTTON | B_BUTTON);
    LD_addr_A(wMenuJoypadFilter);
    RET;

}

void PartyMenu2DMenuData(void){
    //db ['1', '0'];  // cursor start y, x
    //db ['0', '1'];  // rows, columns
    //db ['0x60', '0x00'];  // flags
    //dn ['2', '0'];  // cursor offset
    //db ['0'];  // accepted buttons

    return PartyMenuSelect();
}

void PartyMenuSelect(void){
//  sets carry if exitted menu.
    CALL(aStaticMenuJoypad);
    CALL(aPlaceHollowCursor);
    LD_A_addr(wPartyCount);
    INC_A;
    LD_B_A;
    LD_A_addr(wMenuCursorY);  // menu selection?
    CP_A_B;
    IF_Z goto exitmenu;  // CANCEL
    LD_addr_A(wPartyMenuCursor);
    LDH_A_addr(hJoyLast);
    LD_B_A;
    BIT_B(B_BUTTON_F);
    IF_NZ goto exitmenu;  // B button
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);

    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    AND_A_A;
    RET;


exitmenu:
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    SCF;
    RET;

}

void PrintPartyMenuText(void){
    hlcoord(0, 14, wTilemap);
    LD_BC((2 << 8) | 18);
    CALL(aTextbox);
    LD_A_addr(wPartyCount);
    AND_A_A;
    IF_NZ goto haspokemon;
    LD_DE(mYouHaveNoPKMNString);
    goto gotstring;

haspokemon:
    LD_A_addr(wPartyMenuActionText);
    AND_A(0xf);  // drop high nibble
    LD_HL(mPartyMenuStrings);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;

gotstring:
    LD_A_addr(wOptions);
    PUSH_AF;
    SET_A(NO_TEXT_SCROLL);
    LD_addr_A(wOptions);
    hlcoord(1, 16, wTilemap);  // Coord
    CALL(aPlaceString);
    POP_AF;
    LD_addr_A(wOptions);
    RET;

}

void PartyMenuStrings(void){
    //dw ['ChooseAMonString'];
    //dw ['UseOnWhichPKMNString'];
    //dw ['WhichPKMNString'];
    //dw ['TeachWhichPKMNString'];
    //dw ['MoveToWhereString'];
    //dw ['UseOnWhichPKMNString'];
    //dw ['ChooseAMonString'];  // Probably used to be ChooseAFemalePKMNString
    //dw ['ChooseAMonString'];  // Probably used to be ChooseAMalePKMNString
    //dw ['ToWhichPKMNString'];

    return ChooseAMonString();
}

void ChooseAMonString(void){
    //db ['"Choose a #MON.@"'];

    return UseOnWhichPKMNString();
}

void UseOnWhichPKMNString(void){
    //db ['"Use on which <PK><MN>?@"'];

    return WhichPKMNString();
}

void WhichPKMNString(void){
    //db ['"Which <PK><MN>?@"'];

    return TeachWhichPKMNString();
}

void TeachWhichPKMNString(void){
    //db ['"Teach which <PK><MN>?@"'];

    return MoveToWhereString();
}

void MoveToWhereString(void){
    //db ['"Move to where?@"'];

    return ChooseAFemalePKMNString();
}

void ChooseAFemalePKMNString(void){
//  //  unreferenced
    //db ['"Choose a ♀<PK><MN>.@"'];

    return ChooseAMalePKMNString();
}

void ChooseAMalePKMNString(void){
//  //  unreferenced
    //db ['"Choose a ♂<PK><MN>.@"'];

    return ToWhichPKMNString();
}

void ToWhichPKMNString(void){
    //db ['"To which <PK><MN>?@"'];

    return YouHaveNoPKMNString();
}

void YouHaveNoPKMNString(void){
    //db ['"You have no <PK><MN>!@"'];

    return PrintPartyMenuActionText();
}

void PrintPartyMenuActionText(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    CALL(aGetNickname);
    LD_A_addr(wPartyMenuActionText);
    AND_A(0xf);
    LD_HL(mPrintPartyMenuActionText_MenuActionTexts);
    CALL(aPrintPartyMenuActionText_PrintText);
    RET;


MenuActionTexts:
//  entries correspond to PARTYMENUTEXT_* constants
    //dw ['.CuredOfPoisonText'];
    //dw ['.BurnWasHealedText'];
    //dw ['.WasDefrostedText'];
    //dw ['.WokeUpText'];
    //dw ['.RidOfParalysisText'];
    //dw ['.RecoveredSomeHPText'];
    //dw ['.HealthReturnedText'];
    //dw ['.RevitalizedText'];
    //dw ['.GrewToLevelText'];
    //dw ['.CameToItsSensesText'];


RecoveredSomeHPText:
    //text_far ['_RecoveredSomeHPText']
    //text_end ['?']


CuredOfPoisonText:
    //text_far ['_CuredOfPoisonText']
    //text_end ['?']


RidOfParalysisText:
    //text_far ['_RidOfParalysisText']
    //text_end ['?']


BurnWasHealedText:
    //text_far ['_BurnWasHealedText']
    //text_end ['?']


WasDefrostedText:
    //text_far ['_WasDefrostedText']
    //text_end ['?']


WokeUpText:
    //text_far ['_WokeUpText']
    //text_end ['?']


HealthReturnedText:
    //text_far ['_HealthReturnedText']
    //text_end ['?']


RevitalizedText:
    //text_far ['_RevitalizedText']
    //text_end ['?']


GrewToLevelText:
    //text_far ['_GrewToLevelText']
    //text_end ['?']


CameToItsSensesText:
    //text_far ['_CameToItsSensesText']
    //text_end ['?']


PrintText:
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wOptions);
    PUSH_AF;
    SET_A(NO_TEXT_SCROLL);
    LD_addr_A(wOptions);
    CALL(aPrintText);
    POP_AF;
    LD_addr_A(wOptions);
    RET;

}
