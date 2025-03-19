#include "../constants.h"
#include "mobile_12_2.h"
#include "../data/text/common.h"
#include "../home/map.h"
#include "../home/copy.h"
#include "../home/tilemap.h"
#include "../home/audio.h"
#include "../home/text.h"
#include "../home/delay.h"
#include "../home/menu.h"
#include "../engine/pokemon/mon_menu.h"
#include "../engine/pokemon/party_menu.h"
#include "../engine/gfx/mon_icons.h"
#include "../engine/gfx/sprites.h"

uint8_t gMobileParticipant1Nickname[MON_NAME_LENGTH];
uint8_t gMobileParticipant2Nickname[MON_NAME_LENGTH];
uint8_t gMobileParticipant3Nickname[MON_NAME_LENGTH];

void MobileCheckOwnMonAnywhere(void){
//  Like CheckOwnMonAnywhere, but only check for species.
//  OT/ID don't matter.

    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;

    LD_D_A;
    LD_E(0);
    LD_HL(wPartyMon1Species);
    LD_BC(wPartyMonOTs);

asm_4a851:
    CALL(aMobileCheckOwnMonAnywhere_CheckMatch);
    RET_C ;
    PUSH_BC;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    CALL(aMobileCheckOwnMonAnywhere_AdvanceOTName);
    DEC_D;
    IF_NZ goto asm_4a851;
    LD_A(BANK(sBoxCount));
    CALL(aOpenSRAM);
    LD_A_addr(sBoxCount);
    AND_A_A;
    IF_Z goto asm_4a888;
    LD_D_A;
    LD_HL(sBoxMon1Species);
    LD_BC(sBoxMonOTs);

asm_4a873:
    CALL(aMobileCheckOwnMonAnywhere_CheckMatch);
    IF_NC goto asm_4a87c;
    CALL(aCloseSRAM);
    RET;


asm_4a87c:
    PUSH_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    CALL(aMobileCheckOwnMonAnywhere_AdvanceOTName);
    DEC_D;
    IF_NZ goto asm_4a873;


asm_4a888:
    CALL(aCloseSRAM);
    LD_C(0);

asm_4a88d:
    LD_A_addr(wCurBox);
    AND_A(0xf);
    CP_A_C;
    IF_Z goto asm_4a8d1;
    LD_HL(mMobileCheckOwnMonAnywhere_BoxAddresses);
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    CALL(aOpenSRAM);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hl;
    AND_A_A;
    IF_Z goto asm_4a8d1;
    PUSH_BC;
    PUSH_HL;
    LD_DE(sBoxMons - sBoxCount);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    POP_HL;
    PUSH_DE;
    LD_DE(sBoxMonOTs - sBoxCount);
    ADD_HL_DE;
    LD_B_H;
    LD_C_L;
    POP_HL;
    LD_D_A;

asm_4a8ba:
    CALL(aMobileCheckOwnMonAnywhere_CheckMatch);
    IF_NC goto asm_4a8c4;
    POP_BC;
    CALL(aCloseSRAM);
    RET;


asm_4a8c4:
    PUSH_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    CALL(aMobileCheckOwnMonAnywhere_AdvanceOTName);
    DEC_D;
    IF_NZ goto asm_4a8ba;
    POP_BC;


asm_4a8d1:
    INC_C;
    LD_A_C;
    CP_A(NUM_BOXES);
    IF_C goto asm_4a88d;
    CALL(aCloseSRAM);
    AND_A_A;
    RET;


CheckMatch:
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    LD_D_B;
    LD_E_C;
    LD_A_addr(wScriptVar);
    LD_B_hl;
    CP_A_B;
    IF_NZ goto no_match;
    goto match;


no_match:
    POP_DE;
    POP_HL;
    POP_BC;
    AND_A_A;
    RET;


match:
    POP_DE;
    POP_HL;
    POP_BC;
    SCF;
    RET;


BoxAddresses:
    //table_width ['3', 'MobileCheckOwnMonAnywhere.BoxAddresses']
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


AdvanceOTName:
    PUSH_HL;
    LD_HL(NAME_LENGTH);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;

}

void UnusedFindItemInPCOrBag(void){
    LD_A_addr(wScriptVar);
    LD_addr_A(wCurItem);
    LD_HL(wNumPCItems);
    CALL(aCheckItem);
    IF_C goto found;

    LD_A_addr(wScriptVar);
    LD_addr_A(wCurItem);
    LD_HL(wNumItems);
    CALL(aCheckItem);
    IF_C goto found;

    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;


found:
    LD_A(1);
    LD_addr_A(wScriptVar);
    RET;

}

//  TODO: Lots of gotos. Try and fix them.
bool Function4a94e(void){
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // LD_A(-1);
    // LD_HL(wd002);
    // LD_BC(3);
    // CALL(aByteFill);
    ByteFill(wram->wMobileAdapterPlayerSelectionBuffer, 3, 0xff);
    // XOR_A_A;
    // LD_addr_A(wd018);
    wram->wd018 = 0x0;
    // LD_addr_A(wd019);
    wram->wd019 = 0x0;
    // LD_B(SCGB_PACKPALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_PACKPALS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aFunction4aa22);
    u8_flag_s res = Function4aa22();
    // IF_C goto asm_4a985;
    if(res.flag) goto asm_4a985;
    // IF_Z goto asm_4a9a1;
    if(res.a == 0x0) goto asm_4a9a1;
    goto asm_4a97b;

asm_4a974:
    // CALL(aFunction4aa25);
    res = Function4aa25();
    // IF_C goto asm_4a985;
    if(res.flag) goto asm_4a985;
    // IF_Z goto asm_4a9a1;
    if(res.a == 0x0) goto asm_4a9a1;

asm_4a97b:
    // CALL(aFunction4ac58);
    Function4ac58();
    // LD_HL(wd019);
    // RES_hl(1);
    goto asm_4a974;


asm_4a985:
    // LD_A_addr(wd018);
    // AND_A_A;
    // IF_NZ goto asm_4a990;
    // CALL(aFunction4aba8);
    // IF_C goto asm_4a974;
    if(wram->wd018 == 0x0 && Function4aba8()) {
        goto asm_4a974;
    }

// asm_4a990:
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // LD_HL(wd002);
    // LD_A(-1);
    // LD_BC(3);
    // CALL(aByteFill);
    ByteFill(wram->wMobileAdapterPlayerSelectionBuffer, 3, 0xff);
    // SCF;
    // goto asm_4a9af;
    return true;

asm_4a9a1:
    // CALL(aFunction4a9c3);
    // IF_C goto asm_4a9b0;
    if(Function4a9c3()) {
    // asm_4a9b0:
        // LD_DE(SFX_WRONG);
        // CALL(aPlaySFX);
        PlaySFX(SFX_WRONG);
        // LD_HL(mMobilePickThreeMonForBattleText);
        // CALL(aPrintText);
        PrintText_Conv2(MobilePickThreeMonForBattleText);
        goto asm_4a974;
    }
    // CALL(aFunction4a9d7);
    // IF_C goto asm_4a974;
    if(!Function4a9d7())
        goto asm_4a974;
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // AND_A_A;

// asm_4a9af:
    // RET;
    return false;
}

const txt_cmd_s MobilePickThreeMonForBattleText[] = {
    text_far(v_MobilePickThreeMonForBattleText)
    text_end
};

// Mobile_CheckAnyMonSelectionInvalid
bool Function4a9c3(void){
    // LD_HL(wd002);
    // LD_A(0xff);
    // CP_A_hl;
    // IF_Z goto asm_4a9d5;
    // INC_HL;
    // CP_A_hl;
    // IF_Z goto asm_4a9d5;
    // INC_HL;
    // CP_A_hl;
    // IF_Z goto asm_4a9d5;
    // AND_A_A;
    // RET;

// asm_4a9d5:
    // SCF;
    // RET;
    return (wram->wMobileAdapterPlayerSelectionBuffer[0] == 0xff 
         || wram->wMobileAdapterPlayerSelectionBuffer[1] == 0xff
         || wram->wMobileAdapterPlayerSelectionBuffer[2] == 0xff);
}

// Mobile_CopyNamesAndConfirmSelections
bool Function4a9d7(void){
    // LD_A_addr(wd002);
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetNickname);
    // LD_H_D;
    // LD_L_E;
    // LD_DE(wMobileParticipant1Nickname);
    // LD_BC(NAME_LENGTH_JAPANESE);
    // CALL(aCopyBytes);
    CopyBytes(gMobileParticipant1Nickname, wram->wPartyMonNickname[wram->wMobileAdapterPlayerSelectionBuffer[0]], MON_NAME_LENGTH);
    // LD_A_addr(wd003);
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetNickname);
    // LD_H_D;
    // LD_L_E;
    // LD_DE(wMobileParticipant2Nickname);
    // LD_BC(NAME_LENGTH_JAPANESE);
    // CALL(aCopyBytes);
    CopyBytes(gMobileParticipant2Nickname, wram->wPartyMonNickname[wram->wMobileAdapterPlayerSelectionBuffer[1]], MON_NAME_LENGTH);
    // LD_A_addr(wd004);
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetNickname);
    // LD_H_D;
    // LD_L_E;
    // LD_DE(wMobileParticipant3Nickname);
    // LD_BC(NAME_LENGTH_JAPANESE);
    // CALL(aCopyBytes);
    CopyBytes(gMobileParticipant3Nickname, wram->wPartyMonNickname[wram->wMobileAdapterPlayerSelectionBuffer[2]], MON_NAME_LENGTH);
    // LD_HL(mMobileUseTheseThreeMonText);
    // CALL(aPrintText);
    PrintText_Conv2(MobileUseTheseThreeMonText);
    // CALL(aYesNoBox);
    // RET;
    return YesNoBox_Conv();
}

const txt_cmd_s MobileUseTheseThreeMonText[] = {
    text_far(v_MobileUseTheseThreeMonText)
    text_end
};

u8_flag_s Function4aa22(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();

    return Function4aa25();
}

u8_flag_s Function4aa25(void){
    // FARCALL(aLoadPartyMenuGFX);
    LoadPartyMenuGFX();
    // FARCALL(aInitPartyMenuWithCancel);
    InitPartyMenuWithCancel();
    // CALL(aFunction4aad3);
    Function4aad3();

    return Function4aa34();
}

u8_flag_s Function4aa34(void){
    // LD_A(PARTYMENUACTION_MOBILE);
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = PARTYMENUACTION_MOBILE;
    // FARCALL(aWritePartyMenuTilemap);
    WritePartyMenuTilemap();
    // XOR_A_A;
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = 0x0;
    // FARCALL(aPrintPartyMenuText);
    PrintPartyMenuText();
    // CALL(aFunction4aab6);
    Function4aab6();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aFunction4ab1a);
    u8_flag_s res = Function4ab1a();
    // IF_Z goto asm_4aa66;
    if(res.a == 0x0)
        return res;
    // PUSH_AF;
    // CALL(aFunction4aafb);
    // IF_C goto asm_4aa67;
    // CALL(aFunction4ab06);
    // IF_C goto asm_4aa67;
    if(Function4aafb() || Function4ab06()) {
    // asm_4aa67:
        // LD_HL(wd019);
        // SET_hl(1);
        bit_set(wram->wd019, 1);
        // POP_AF;
        // RET;
    }
    // POP_AF;

// asm_4aa66:
    // RET;
    return res;
}

void Function4aa6e(void){
//  //  unreferenced
    // POP_AF;
    // LD_DE(SFX_WRONG);
    // CALL(aPlaySFX);
    // CALL(aWaitSFX);
    // JR(mFunction4aa34);
}

void Function4aa7a(void){
    // LD_HL(wd002);
    uint8_t* hl = wram->wMobileAdapterPlayerSelectionBuffer;
    // LD_D(0x3);
    uint8_t d = 0x3;

    do {
    // loop:
        // LD_E(PARTY_LENGTH);
        uint8_t e = PARTY_LENGTH;
        // LD_A_hli;
        uint8_t a = *(hl++);
        // PUSH_DE;
        // PUSH_HL;
        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff)
            return;
        // LD_HL(wSpriteAnimationStructs);
        struct SpriteAnim* hl2 = wram->wSpriteAnim;
        // INC_A;
        // LD_D_A;
        uint8_t d2 = ++a;

        do {
        // inner_loop:
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto next;
            // CP_A_D;
            // IF_Z goto same_as_d;
            if(hl2->index != 0 && hl2->index == d2) {
            // same_as_d:
                // LD_A(0x2);

            // proceed:
                // PUSH_HL;
                // LD_C_L;
                // LD_B_H;
                // LD_HL(0x2);
                // ADD_HL_BC;
                // LD_hl_A;
                // POP_HL;
                hl2->animSeqID = 0x2; // index field + 0x2 bytes = animSeqID
            }
            // goto next;

            // LD_A(0x3);
            // goto proceed;

        // next:
            // LD_BC(0x10);
            // ADD_HL_BC;
            hl2++;
            // DEC_E;
            // IF_NZ goto inner_loop;
        } while(--e != 0);
        // POP_HL;
        // POP_DE;
        // DEC_D;
        // IF_NZ goto loop;
    } while(--d != 0);
    // goto finished;

// done:
    // POP_HL;
    // POP_DE;

// finished:
    // RET;
}

// Draw selected pokemon indicies
void Function4aab6(void){
    // LD_HL(wd002);
    uint8_t* hl = wram->wMobileAdapterPlayerSelectionBuffer;
    // LD_D(0x3);
    uint8_t d = 0x3;

    do {
    // loop:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff)
            break;
        // PUSH_DE;
        // PUSH_HL;
        // hlcoord(0, 1, wTilemap);
        // LD_BC(0x28);
        // CALL(aAddNTimes);
        // LD_hl(0xec);
        coord(0, 1, wram->wTilemap)[0x28 * a] = 0xec;
        // POP_HL;
        // POP_DE;
        // DEC_D;
        // IF_NZ goto loop;
    } while(--d != 0);

// done:
    // RET;
}

void Function4aad3(void){
    // LD_HL(wPartyCount);
    // LD_A_hli;
    // AND_A_A;
    // RET_Z ;  // Nothing in your party
    if(wram->wPartyCount == 0)
        return;

    // LD_C_A;
    uint8_t c = wram->wPartyCount;
    // XOR_A_A;
    // LDH_addr_A(hObjectStructIndex);
    hram->hObjectStructIndex = 0x0;

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // LD_E(MONICON_PARTYMENU);
        // FARCALL(aLoadMenuMonIcon);
        LoadMenuMonIcon_Conv(MONICON_PARTYMENU);
        // LDH_A_addr(hObjectStructIndex);
        // INC_A;
        // LDH_addr_A(hObjectStructIndex);
        hram->hObjectStructIndex++;
        // POP_HL;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

    // CALL(aFunction4aa7a);
    Function4aa7a();
    // FARCALL(aPlaySpriteAnimations);
    PlaySpriteAnimations_Conv();
    // RET;
}

// Mobile_IsSelectedMonEgg
bool Function4aafb(void){
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto egg;
    // AND_A_A;
    // RET;

// egg:
    // SCF;
    // RET;
    return wram->wCurPartySpecies == EGG;
}

// Mobile_IsSelectedMonFainted
bool Function4ab06(void){
    // LD_A_addr(wCurPartyMon);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_HL(wPartyMon1HP);
    // CALL(aAddNTimes);
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hl;
    // OR_A_B;
    // IF_NZ goto NotFainted;
    // SCF;

// NotFainted:
    // RET;
    return wram->wPartyMon[wram->wCurPartyMon].HP == 0;
}

u8_flag_s Function4ab1a(void){
    uint8_t joypad;
    do {
    // asm_4ab1a:
        // LD_A(0xfb);
        // LD_addr_A(wMenuJoypadFilter);
        wram->wMenuJoypadFilter = (D_PAD | A_BUTTON | B_BUTTON | START);
        // LD_A(0x26);
        // LD_addr_A(w2DMenuCursorOffsets);
        wram->w2DMenuCursorOffsets = (0x2 << 4) | 0x6;
        // LD_A(0x2);
        // LD_addr_A(w2DMenuNumCols);
        wram->w2DMenuNumCols = 0x2;
        // CALL(aFunction4adf7);
        Function4adf7();
        // CALL(aStaticMenuJoypad);
        joypad = StaticMenuJoypad_Conv();
        // CALL(aFunction4abc3);
        // IF_C goto asm_4ab1a;
    } while(Function4abc3(joypad));
    // PUSH_AF;
    // CALL(aFunction4ab99);
    // CALL_NC (aPlaceHollowCursor);
    if(!Function4ab99(joypad))
        PlaceHollowCursor_Conv();
    // POP_AF;
    // BIT_A(1);
    // IF_NZ goto asm_4ab6d;
    if(!bit_test(joypad, B_BUTTON_F)) {
        // LD_A_addr(wPartyCount);
        // INC_A;
        // LD_B_A;
        // LD_A_addr(wMenuCursorY);
        // LD_addr_A(wPartyMenuCursor);
        wram->wPartyMenuCursor = wram->wMenuCursorY;
        // CP_A_B;
        // IF_Z goto asm_4ab7e;
        if(wram->wMenuCursorY == wram->wPartyCount + 1) {
        // asm_4ab7e:
            // LD_A(0x1);
            // LD_addr_A(wd018);
            wram->wd018 = 0x1;
            // LD_A_addr(wMenuCursorX);
            // CP_A(0x2);
            // IF_Z goto asm_4ab73;
            if(wram->wMenuCursorX == 0x2)
                goto asm_4ab73;
            // LD_DE(SFX_READ_TEXT_2);
            // CALL(aPlaySFX);
            PlaySFX(SFX_READ_TEXT_2);
            // CALL(aWaitSFX);
            WaitSFX();
            // XOR_A_A;
            // LD_addr_A(wd018);
            wram->wd018 = 0x0;
            // AND_A_A;
            // RET;
            return u8_flag(0x0, false);
        }
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = wram->wMenuCursorY - 1;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(wPartySpecies);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = wram->wPartySpecies[wram->wCurPartyMon];
        // LD_DE(SFX_READ_TEXT_2);
        // CALL(aPlaySFX);
        PlaySFX(SFX_READ_TEXT_2);
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_A(0x1);
        // AND_A_A;
        // RET;
        return u8_flag(0x1, false);
    }

// asm_4ab6d:
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wPartyMenuCursor);
    wram->wPartyMenuCursor = wram->wMenuCursorY;

asm_4ab73:
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // CALL(aWaitSFX);
    WaitSFX();
    // SCF;
    // RET;
    return u8_flag(0x1, true);
}

bool Function4ab99(uint8_t joypad){
    // BIT_A(1);
    // IF_Z goto asm_4aba6;
    // LD_A_addr(wd002);
    // CP_A(0xff);
    // IF_Z goto asm_4aba6;
    // SCF;
    // RET;
    return bit_test(joypad, B_BUTTON_F) && wram->wMobileAdapterPlayerSelectionBuffer[0] != 0xff;

// asm_4aba6:
    // AND_A_A;
    // RET;
}

bool Function4aba8(void){
    // LD_HL(wd004);
    // LD_A_hl;
    // CP_A(0xff);
    // IF_NZ goto asm_4abbe;
    if(wram->wMobileAdapterPlayerSelectionBuffer[2] != 0xff) {
        wram->wMobileAdapterPlayerSelectionBuffer[2] = 0xff;
        return true;
    }
    // DEC_HL;
    // LD_A_hl;
    // CP_A(0xff);
    // IF_NZ goto asm_4abbe;
    if(wram->wMobileAdapterPlayerSelectionBuffer[1] != 0xff) {
        wram->wMobileAdapterPlayerSelectionBuffer[1] = 0xff;
        return true;
    }
    // DEC_HL;
    // LD_A_hl;
    // CP_A(0xff);
    // IF_NZ goto asm_4abbe;
    if(wram->wMobileAdapterPlayerSelectionBuffer[0] != 0xff) {
        wram->wMobileAdapterPlayerSelectionBuffer[0] = 0xff;
        return true;
    }
    // AND_A_A;
    // RET;
    return false;

// asm_4abbe:
    // LD_A(0xff);
    // LD_hl_A;
    // SCF;
    // RET;
}

bool Function4abc3(uint8_t a){
    // BIT_A(3);
    // IF_Z goto asm_4abd5;
    if(bit_test(a, START_F)) {
        // LD_A_addr(wPartyCount);
        // INC_A;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = wram->wPartyCount + 1;
        // LD_A(0x1);
        // LD_addr_A(wMenuCursorX);
        wram->wMenuCursorX = 0x1;
        // goto asm_4ac29;
    }
// asm_4abd5:
    // BIT_A(6);
    // IF_Z goto asm_4abeb;
    else if(bit_test(a, D_UP_F)){
        // LD_A_addr(wMenuCursorY);
        // LD_addr_A(wMenuCursorY);
        // AND_A_A;
        // IF_NZ goto asm_4ac29;
        if(wram->wMenuCursorY == 0) {
            // LD_A_addr(wPartyCount);
            // INC_A;
            // LD_addr_A(wMenuCursorY);
            wram->wMenuCursorY = wram->wPartyCount + 1;
        }
        // goto asm_4ac29;
    }
// asm_4abeb:
    // BIT_A(7);
    // IF_Z goto asm_4ac08;
    else if(bit_test(a, D_DOWN_F)){
        // LD_A_addr(wMenuCursorY);
        // LD_addr_A(wMenuCursorY);
        // LD_A_addr(wPartyCount);
        // INC_A;
        // INC_A;
        // LD_B_A;
        // LD_A_addr(wMenuCursorY);
        // CP_A_B;
        // IF_NZ goto asm_4ac29;
        if(wram->wMenuCursorY == wram->wPartyCount + 2) {
            // LD_A(0x1);
            // LD_addr_A(wMenuCursorY);
            wram->wMenuCursorY = 0x1;
        }
        // goto asm_4ac29;
    }
// asm_4ac08:
    // BIT_A(4);
    // IF_NZ goto asm_4ac10;
    // BIT_A(5);
    // IF_Z goto asm_4ac56;
    else if(bit_test(a, D_RIGHT_F) || bit_test(a, D_LEFT_F)) {
    // asm_4ac10:
        // LD_A_addr(wMenuCursorY);
        // LD_B_A;
        // LD_A_addr(wPartyCount);
        // INC_A;
        // CP_A_B;
        // IF_NZ goto asm_4ac29;
        if(wram->wMenuCursorY == wram->wPartyCount + 1) {
            // LD_A_addr(wMenuCursorX);
            // CP_A(0x1);
            // IF_Z goto asm_4ac26;
            if(wram->wMenuCursorX == 0x1) {
            // asm_4ac26:
                // LD_addr_A(wMenuCursorX);
                wram->wMenuCursorX = wram->wMenuCursorX;
            }
            // LD_A(0x1);
            // goto asm_4ac29;
        }
    }
    else {
        return false;
    }

// asm_4ac29:
    // hlcoord(0, 1, wTilemap);
    // LD_BC((13 << 8) | 1);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(0, 1, wram->wTilemap), 1, 13);
    // CALL(aFunction4aab6);
    Function4aab6();
    // LD_A_addr(wPartyCount);
    // hlcoord(6, 1, wTilemap);

// asm_4ac3b:
    // LD_BC(0x28);
    // ADD_HL_BC;
    // DEC_A;
    // IF_NZ goto asm_4ac3b;
    // LD_hl(0x7f);
    *(coord(6, 1, wram->wTilemap) + (0x28 * wram->wPartyCount)) = 0x7f;
    // LD_A_addr(wMenuCursorY);
    // LD_B_A;
    // LD_A_addr(wPartyCount);
    // INC_A;
    // CP_A_B;
    // IF_Z goto asm_4ac54;
    if(wram->wMenuCursorY != wram->wPartyCount + 1) {
        // LD_A(0x1);
        // LD_addr_A(wMenuCursorX);
        wram->wMenuCursorX = 0x1;
    }

// asm_4ac54:
    // SCF;
    // RET;
    return true;

// asm_4ac56:
    // AND_A_A;
    // RET;
}

void Function4ac58(void){
    // LD_BC((2 << 8) | 18);
    // hlcoord(1, 15, wTilemap);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 15, wram->wTilemap), 18, 2);
    // FARCALL(aFreezeMonIcons);
    FreezeMonIcons_Conv();
    // LD_HL(mMenuHeader_0x4aca2);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_0x4aca2);
    // LD_HL(wd019);
    // BIT_hl(1);
    // IF_Z goto asm_4ac89;
    if(bit_test(wram->wd019, 1)) {
        // hlcoord(11, 13, wTilemap);
        // LD_B(0x3);
        // LD_C(0x7);
        // CALL(aTextbox);
        Textbox_Conv2(coord(9, 13, wram->wTilemap), 0x3, 0x9);
        // hlcoord(13, 14, wTilemap);
        // LD_DE(mString_4ada7);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_4ada7), coord(11, 14, wram->wTilemap));
        // goto asm_4ac96;
    }
    else {
    // asm_4ac89:
        // hlcoord(11, 9, wTilemap);
        // LD_B(0x7);
        // LD_C(0x7);
        // CALL(aTextbox);
        Textbox_Conv2(coord(9, 9, wram->wTilemap), 0x7, 0x9);
        // CALL(aFunction4ad68);
        Function4ad68();
    }

// asm_4ac96:
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // CALL(aFunction4acaa);
    Function4acaa();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // AND_A_A;
    // RET;
}

const struct MenuHeader MenuHeader_0x4aca2 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 9, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = NULL,
    .defaultOption = 1,  // default option
};

void Function4acaa(void){
    while(1) {
    // asm_4acaa:
        struct MenuData data = {0};
        // LD_A(0xa0);
        // LD_addr_A(wMenuDataFlags);
        data.flags = (D_DOWN | D_LEFT);
        // LD_A_addr(wd019);
        // BIT_A(1);
        // IF_Z goto asm_4acc2;
        if(bit_test(wram->wd019, 1)) {
            // LD_A(0x2);
            // LD_addr_A(wMenuDataItems);
            data.verticalMenu.count = 0x2;
            // LD_A(0xc);
            // LD_addr_A(wMenuBorderTopCoord);
            wram->wMenuBorderTopCoord = 0xc;
            // goto asm_4accc;
        }
        else {
        // asm_4acc2:
            // LD_A(0x4);
            // LD_addr_A(wMenuDataItems);
            data.verticalMenu.count = 0x4;
            // LD_A(0x8);
            // LD_addr_A(wMenuBorderTopCoord);
            wram->wMenuBorderTopCoord = 0x8;
        }

    // asm_4accc:
        // LD_A(0xb);
        // LD_addr_A(wMenuBorderLeftCoord);
        wram->wMenuBorderLeftCoord = 0x9;
        // LD_A(0x1);
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = 0x1;
        // CALL(aInitVerticalMenuCursor);
        InitVerticalMenuCursor_Conv(&data);
        // LD_HL(w2DMenuFlags1);
        // SET_hl(6);
        bit_set(wram->w2DMenuFlags1, 6);
        // CALL(aStaticMenuJoypad);
        StaticMenuJoypad_Conv();
        // LD_DE(SFX_READ_TEXT_2);
        // CALL(aPlaySFX);
        PlaySFX(SFX_READ_TEXT_2);
        // LDH_A_addr(hJoyPressed);
        // BIT_A(0);
        // IF_NZ goto asm_4acf4;
        if(bit_test(hram->hJoyPressed, A_BUTTON_F)) {
        // asm_4acf4:
            // LD_A_addr(wd019);
            // BIT_A(1);
            // IF_NZ goto asm_4ad0e;
            if(!bit_test(wram->wd019, 1)) {
                // LD_A_addr(wMenuCursorY);
                // CP_A(0x1);
                // JR_Z (mFunction4ad17);
                // CP_A(0x2);
                // JP_Z (mFunction4ad56);
                // CP_A(0x3);
                // JP_Z (mFunction4ad60);
                switch(wram->wMenuCursorY) {
                    case 0x1: return Function4ad17();
                    case 0x2: return Function4ad56();
                    case 0x3: return Function4ad60();
                }
                // goto asm_4acf3;
            }
            else {
            // asm_4ad0e:
                // LD_A_addr(wMenuCursorY);
                // CP_A(0x1);
                // JR_Z (mFunction4ad56);
                if(wram->wMenuCursorY == 0x1)
                    return Function4ad56();
                // goto asm_4acf3;
            }
            return;
        }
        // BIT_A(1);
        // IF_NZ goto asm_4acf3;
        else if(bit_test(hram->hJoyPressed, B_BUTTON_F))
            break;
        // goto asm_4acaa;
    }

// asm_4acf3:
    // RET;
}

void Function4ad17(void){
    // CALL(aFunction4adb2);
    uint8_t* hl = Function4adb2();
    // IF_Z goto asm_4ad4a;
    if(hl) {
    // asm_4ad4a:
        // LD_A(0xff);
        // LD_hl_A;
        *hl = 0xff;
        // CALL(aFunction4adc2);
        Function4adc2();
        // RET;
        return;
    }
    // LD_HL(wd002);
    hl = wram->wMobileAdapterPlayerSelectionBuffer;
    // LD_A(0xff);
    // CP_A_hl;
    // IF_Z goto asm_4ad39;
    if(*hl != 0xff) {
        // INC_HL;
        hl++;
        // CP_A_hl;
        // IF_Z goto asm_4ad39;
        if(*hl != 0xff) {
            // INC_HL;
            hl++;
            // CP_A_hl;
            // IF_Z goto asm_4ad39;
            if(*hl != 0xff) {
                // LD_DE(SFX_WRONG);
                // CALL(aWaitPlaySFX);
                WaitPlaySFX(SFX_WRONG);
                // LD_HL(mMobileOnlyThreeMonMayEnterText);
                // CALL(aPrintText);
                PrintText_Conv2(MobileOnlyThreeMonMayEnterText);
                // RET;
            }
        }
    }

// asm_4ad39:
    // LD_A_addr(wCurPartyMon);
    // LD_hl_A;
    *hl = wram->wCurPartyMon;
    // CALL(aFunction4a9c3);
    // RET_C ;
    if(!Function4a9c3()) {
        // LD_A_addr(wd019);
        // SET_A(0);
        // LD_addr_A(wd019);
        bit_set(wram->wd019, 0);
        // RET;
    }
}

const txt_cmd_s MobileOnlyThreeMonMayEnterText[] = {
    text_far(v_MobileOnlyThreeMonMayEnterText)
    text_end
};

// Mobile_OpenPartyStats
void Function4ad56(void){
    // FARCALL(aOpenPartyStats);
    OpenPartyStats();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // RET;
}

// Mobile_ManagePokemonMoves
void Function4ad60(void){
    // FARCALL(aManagePokemonMoves);
    ManagePokemonMoves();
    // RET;
}

void Function4ad67(void){
//  //  unreferenced
    // RET;
}

// Mobile_PlaceEntryString
void Function4ad68(void){
    // hlcoord(13, 12, wTilemap);
    // LD_DE(mString_4ad88);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_4ad88), coord(11, 12, wram->wTilemap));
    // CALL(aFunction4adb2);
    // IF_C goto asm_4ad7e;
    if(!Function4adb2()) {
    // asm_4ad7e:
        // hlcoord(13, 10, wTilemap);
        // LD_DE(mString_4ad9a);
        PlaceStringSimple(U82C(String_4ad9a), coord(11, 10, wram->wTilemap));
    }
    else {
        // hlcoord(13, 10, wTilemap);
        // LD_DE(mString_4ada0);
        PlaceStringSimple(U82C(String_4ada0), coord(11, 10, wram->wTilemap));
        // goto asm_4ad84;
    }

// asm_4ad84:
    // CALL(aPlaceString);
    // RET;
}

const char String_4ad88[] =
            "STATS" //db "つよさをみる"
    t_next  "MOVE"  //next "つかえるわざ"
    t_next  "BACK"; //next "もどる@"

const char String_4ad9a[] = "ENTRY"; // "さんかする@"
const char String_4ada0[] = "NO ENTRY"; // "さんかしない@"

const char String_4ada7[] =
            "STATS"                 //db    "つよさをみる"
    t_next  "BACK@";                //next  "もどる@"  // BACK

// Mobile_CurPartyMonIsSelected
uint8_t* Function4adb2(void){
    // LD_HL(wd002);
    // LD_A_addr(wCurPartyMon);
    // CP_A_hl;
    // RET_Z ;
    if(wram->wCurPartyMon == wram->wMobileAdapterPlayerSelectionBuffer[0])
        return wram->wMobileAdapterPlayerSelectionBuffer + 0;
    // INC_HL;
    // CP_A_hl;
    // RET_Z ;
    if(wram->wCurPartyMon == wram->wMobileAdapterPlayerSelectionBuffer[1])
        return wram->wMobileAdapterPlayerSelectionBuffer + 1;
    // INC_HL;
    // CP_A_hl;
    // RET_Z ;
    if(wram->wCurPartyMon == wram->wMobileAdapterPlayerSelectionBuffer[2])
        return wram->wMobileAdapterPlayerSelectionBuffer + 2;
    // SCF;
    // RET;
    return NULL;
}

void Function4adc2(void){
    // LD_A_addr(wd002);
    // CP_A(0xff);
    // IF_NZ goto skip;
    if(wram->wMobileAdapterPlayerSelectionBuffer[0] == 0xff) {
        // LD_A_addr(wd003);
        // CP_A(0xff);
        // IF_NZ goto skip2;
        if(wram->wMobileAdapterPlayerSelectionBuffer[1] == 0xff) {
            // LD_A_addr(wd004);
            // LD_addr_A(wd002);
            wram->wMobileAdapterPlayerSelectionBuffer[0] = wram->wMobileAdapterPlayerSelectionBuffer[2];
            // LD_A(0xff);
            // LD_addr_A(wd004);
            wram->wMobileAdapterPlayerSelectionBuffer[2] = 0xff;
            // goto skip;
        }
        else {
        // skip2:
            // LD_addr_A(wd002);
            wram->wMobileAdapterPlayerSelectionBuffer[0] = wram->wMobileAdapterPlayerSelectionBuffer[1];
            // LD_A(0xff);
            // LD_addr_A(wd003);
            wram->wMobileAdapterPlayerSelectionBuffer[1] = 0xff;
        }
    }

// skip:
    // LD_A_addr(wd003);
    // CP_A(0xff);
    // RET_NZ ;
    if(wram->wMobileAdapterPlayerSelectionBuffer[1] == 0xff) {
        // LD_B_A;
        uint8_t b = wram->wMobileAdapterPlayerSelectionBuffer[1];
        // LD_A_addr(wd004);
        // LD_addr_A(wd003);
        wram->wMobileAdapterPlayerSelectionBuffer[1] = wram->wMobileAdapterPlayerSelectionBuffer[2];
        // LD_A_B;
        // LD_addr_A(wd004);
        wram->wMobileAdapterPlayerSelectionBuffer[2] = b;
        // RET;
    }
}

// Set cursor to end of list?
void Function4adf7(void){
    // LD_A_addr(wd019);
    // BIT_A(0);
    // RET_Z ;
    if(!bit_test(wram->wd019, 0))
        return;
    // LD_A_addr(wPartyCount);
    // INC_A;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wPartyCount + 1;
    // LD_A(0x1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 0x1;
    // LD_A_addr(wd019);
    // RES_A(0);
    // LD_addr_A(wd019);
    bit_reset(wram->wd019, 0);
    // RET;
}
