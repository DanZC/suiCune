#include "../constants.h"
#include "mobile_5c.h"
#include "mobile_46.h"
#include "../home/sram.h"
#include "../home/lcd.h"
#include "../home/copy.h"
#include "../home/text.h"
#include "../home/tilemap.h"
#include "../home/joypad.h"
#include "../home/clear_sprites.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/sprites.h"

void Function170000(void){
    LD_A_addr(0xc62b);
    LD_addr_A(wPlayerTrademonSpecies);
    LD_HL(0xc62e);
    LD_DE(wPlayerTrademonSenderName);
    LD_BC(0x0005);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    LD_HL(0xc663);
    LD_DE(wPlayerTrademonOTName);
    LD_BC(0x0005);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    LD_HL(0xc648);
    LD_A_hli;
    LD_addr_A(wPlayerTrademonDVs);
    LD_A_hl;
    LD_addr_A(wPlayerTrademonDVs + 1);
    LD_HL(0xc639);
    LD_A_hli;
    LD_addr_A(wPlayerTrademonID);
    LD_A_hl;
    LD_addr_A(wPlayerTrademonID + 1);
    LD_BC(0xc633);
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wPlayerTrademonCaughtData);
    LD_A_addr(wcd81);
    LD_addr_A(wc74e);
    LD_HL(0xc608);
    LD_DE(0xd800);
    LD_BC(0x008f);
    CALL(aCopyBytes);
    RET;

}

void Function17005a(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_A_addr(0xa824);
    LD_addr_A(wOTTrademonSpecies);
    LD_HL(0xa827);
    LD_DE(wOTTrademonSenderName);
    LD_BC(NAME_LENGTH_JAPANESE - 1);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    LD_HL(0xa85c);
    LD_DE(wOTTrademonOTName);
    LD_BC(NAME_LENGTH_JAPANESE - 1);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    LD_HL(0xa841);
    LD_A_hli;
    LD_addr_A(wOTTrademonDVs);
    LD_A_hl;
    LD_addr_A(wOTTrademonDVs + 1);
    LD_HL(0xa832);
    LD_A_hli;
    LD_addr_A(wOTTrademonID);
    LD_A_hl;
    LD_addr_A(wOTTrademonID + 1);
    LD_BC(0xa82c);
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wOTTrademonCaughtData);
    LD_A_addr(wcd81);
    LD_addr_A(wc74e);
    CALL(aCloseSRAM);
    RET;

// INCLUDE "engine/events/battle_tower/battle_tower.asm"

    return Function170be4();
}

void Function170be4(void){
    LD_A(BANK(s5_a894));
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_HL(s5_a894);
    LD_BC(6 + 2);
    CALL(aByteFill);
    CALL(aCloseSRAM);
    RET;

}

void Clears5_a89a(void){
    // LD_A(BANK(s5_a89a));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_a89a));
    // LD_HL(s5_a89a);
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    gb_write16(s5_a89a, 0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;

}

void Function170c06(void){
//  //  unreferenced
    LD_A(BANK(s5_a894));
    CALL(aOpenSRAM);
    LD_HL(s5_a894);
    LD_A_addr(wBattleResult);
    AND_A_A;  // WIN?
    IF_NZ goto asm_170c15;
    INC_hl;


asm_170c15:
    INC_HL;
    INC_HL;
    LD_A_addr(s5_a89a + 1);
    ADD_A_hl;
    LD_hld_A;
    LD_A_addr(s5_a89a);
    ADC_A_hl;
    LD_hli_A;
    IF_NC goto asm_170c27;
    LD_A(0xff);
    LD_hld_A;
    LD_hli_A;


asm_170c27:
    INC_HL;
    PUSH_HL;
    LD_DE(0);
    XOR_A_A;
    LD_addr_A(wTempByteValue);

asm_170c30:
    LD_HL(wPartyMon1HP);
    LD_A_addr(wTempByteValue);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    INC_HL;
    INC_HL;
    LD_A_hld;
    SUB_A_C;
    LD_C_A;
    LD_A_hl;
    SBC_A_B;
    LD_B_A;
    PUSH_DE;
    POP_HL;
    ADD_HL_BC;
    PUSH_HL;
    POP_DE;
    IF_C goto asm_170c58;
    LD_A_addr(wTempByteValue);
    INC_A;
    LD_addr_A(wTempByteValue);
    CP_A(0x3);
    IF_C goto asm_170c30;
    goto asm_170c5b;


asm_170c58:
    LD_DE(-1);


asm_170c5b:
    POP_HL;
    INC_HL;
    LD_A_E;
    ADD_A_hl;
    LD_hld_A;
    LD_A_D;
    ADC_A_hl;
    LD_hli_A;
    IF_NC goto asm_170c69;
    LD_A(0xff);
    LD_hld_A;
    LD_hli_A;


asm_170c69:
    INC_HL;
    PUSH_HL;
    LD_B(0x0);
    LD_C(0x0);

asm_170c6f:
    LD_HL(wPartyMon1HP);
    LD_A_B;
    PUSH_BC;
    CALL(aGetPartyLocation);
    POP_BC;
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto asm_170c7d;
    INC_C;


asm_170c7d:
    INC_B;
    LD_A_B;
    CP_A(0x3);
    IF_C goto asm_170c6f;
    POP_HL;
    LD_A_hl;
    ADD_A_C;
    LD_hl_A;
    CALL(aCloseSRAM);
    RET;

}

void Function170c8b(void){
    LD_HL(wLastEnemyCounterMove);
    LD_B(0x5);

asm_170c90:
    LD_A_hl;
    XOR_A(0xff);
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_170c90;
    RET;

}

void CheckBTMonMovesForErrors(void){
    LD_C(BATTLETOWER_PARTY_LENGTH);
    LD_HL(wBT_OTTempMon1Moves);

loop:
    PUSH_HL;
    LD_A_hl;
    CP_A(NUM_ATTACKS + 1);
    IF_C goto okay;
    LD_A(POUND);
    LD_hl_A;


okay:
    INC_HL;
    LD_B(NUM_MOVES - 1);

loop2:
    LD_A_hl;
    AND_A_A;
    IF_Z goto loop3;
    CP_A(NUM_ATTACKS + 1);
    IF_C goto next;


loop3:
    XOR_A_A;
    LD_hl_A;
    INC_HL;
    DEC_B;
    IF_NZ goto loop3;
    goto done;


next:
    INC_HL;
    DEC_B;
    IF_NZ goto loop2;


done:
    POP_HL;
    LD_DE(NICKNAMED_MON_STRUCT_LENGTH);
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void CheckBTMonMovesForErrors_Conv(void){
    // LD_C(BATTLETOWER_PARTY_LENGTH);
    uint8_t c = BATTLETOWER_PARTY_LENGTH;
    // LD_HL(wBT_OTTempMon1Moves);
    struct BattleTowerPartyMon* mon = wram->wBT_OTTemp.party;

    do {
    // loop:
        move_t* moves = mon->mon.mon.moves;
        // PUSH_HL;
        // LD_A_hl;
        move_t move = moves[0];
        
        // CP_A(NUM_ATTACKS + 1);
        // IF_C goto okay;
        if(move >= NUM_ATTACKS + 1) {
            // LD_A(POUND);
            // LD_hl_A;
            moves[0] = POUND;
        }

    // okay:
        // INC_HL;
        moves++;
        // LD_B(NUM_MOVES - 1);
        uint8_t b = NUM_MOVES - 1;

        do {
        // loop2:
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto loop3;
            if(*moves != NO_MOVE) {
                // CP_A(NUM_ATTACKS + 1);
                // IF_C goto next;
                if(*moves <= NUM_ATTACKS)
                    continue;
            }

            do {
            // loop3:
                // XOR_A_A;
                // LD_hl_A;
                *moves = NO_MOVE;
                // INC_HL;
                // DEC_B;
                // IF_NZ goto loop3;
            } while(moves++, --b != 0);
            // goto done;
            break;

        // next:
            // INC_HL;
            // DEC_B;
            // IF_NZ goto loop2;
        } while(moves++, --b != 0);


    // done:
        // POP_HL;
        // LD_DE(NICKNAMED_MON_STRUCT_LENGTH);
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto loop;
    } while(mon++, --c != 0);
    // RET;
}

// LoadPichuAnimatedMobileGFX
void Function170cc6(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wDecompressScratch));
    // LDH_addr_A(rSVBK);
    // LD_HL(mPichuAnimatedMobileGFX);
    // LD_DE(wDecompressScratch);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(wram->wDecompressScratch, PichuAnimatedMobileGFX);
    // LD_A(1);
    // LDH_addr_A(rVBK);
    // LD_DE(wDecompressScratch);
    // LD_HL(vTiles0);
    // LD_BC((BANK(wDecompressScratch) << 8) | 193);
    // CALL(aGet2bpp);
    CopyBytes_Conv2(vram->vTiles3, wram->wDecompressScratch, 193 * LEN_2BPP_TILE);
    // XOR_A_A;
    // LDH_addr_A(rVBK);
    // LD_HL(mElectroBallMobileGFX);
    // LD_DE(wDecompressScratch);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(wram->wDecompressScratch, ElectroBallMobileGFX);
    // LD_DE(wBGPals1);
    // LD_HL(vTiles0);
    // LD_BC((BANK(wDecompressScratch) << 8) | 83);
    // CALL(aGet2bpp);
    CopyBytes_Conv2(vram->vTiles0, wram->wDecompressScratch, 83 * LEN_2BPP_TILE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

// LoadPichuBorderMobileGFX
void Function170d02(void){
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_DE(mPichuBorderMobileGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0xc1);
    // LD_BC((BANK(aPichuBorderMobileGFX) << 8) | 24);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles3 + LEN_2BPP_TILE * 0xc1, PichuBorderMobileGFX, 0, 24);
    // XOR_A_A;
    // LDH_addr_A(rVBK);
    // RET;
}

const char PichuAnimatedMobileGFX[] = "gfx/mobile/pichu_animated.png";
const char ElectroBallMobileGFX[] = "gfx/mobile/electro_ball.png";
const char PichuBorderMobileGFX[] = "gfx/mobile/pichu_border.png";

void Function1719c8(void){
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // CALL(aFunction1719d6); // TODO: Convert Function1719d6
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // RET;
}

void Function1719d6(void){
    // FARCALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    // CALL(aFunction1719ed);
    Function1719ed();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // CALL(aFunction171a11);
    Function171a11();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void Function1719ed(void){
    // XOR_A_A;
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x0;
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0x0;
    // DEC_A;
    // LD_addr_A(wcd4b);
    wram->wcd4b = 0xff;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // FARCALL(aFunction171d2b);
    Function171d2b();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // RET;
}

void Function171a11(void){

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_A_addr(wcd49);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->wcd49, 7))
            break;
        // CALL(aFunction171a36);
        Function171a36();
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations_Conv();
        // FARCALL(aReloadMapPart);
        ReloadMapPart_Conv();
        // goto loop;
    }

// done:
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // RET;
}

void Function171a36(void){
    //jumptable ['Jumptable_171a45', 'wcd49']

    return Jumptable_171a45();
}

void Jumptable_171a45(void){
    //dw ['Function171a95'];
    //dw ['Function171ac9'];
    //dw ['Function171a5d'];
    //dw ['Function171ad7'];
    //dw ['Function171a5d'];
    //dw ['Function171aec'];
    //dw ['Function171b4b'];
    //dw ['Function171b85'];
    //dw ['Function171bcc'];
    //dw ['Function171c2c'];
    //dw ['Function171c39'];
    //dw ['Function171c41'];

    return Function171a5d();
}

void Function171a5d(void){
    LD_A_addr(wc821);
    BIT_A(1);
    IF_NZ goto asm_171a6a;
    BIT_A(0);
    RET_NZ ;
    JP(mFunction171c66);


asm_171a6a:
    LD_A(MOBILEAPI_00);
    CALL(aMobileAPI);
    LD_addr_A(wMobileErrorCodeBuffer);
    LD_A_L;
    LD_addr_A(wMobileErrorCodeBuffer + 1);
    LD_A_H;
    LD_addr_A(wMobileErrorCodeBuffer + 2);
    LD_A(MOBILEAPI_05);
    CALL(aMobileAPI);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    FARCALL(aBattleTowerRoomMenu_Cleanup);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(0xa);
    LD_addr_A(wcd49);
    RET;

}

void Function171a95(void){
    FARCALL(aFunction171ccd);
    hlcoord(2, 8, wTilemap);
    LD_DE(mString_171aa7);
    CALL(aPlaceString);
    JP(mFunction171c66);

}

const char String_171aa7[] = 
           "Connecting to"      //db ['"モバイルアダプタに"'];
    t_next "MOBILE ADAPTER…";   //next ['"せつぞく\u3000しています"']
                                //next ['"しばらく\u3000おまちください"']
                                //db ['"@"'];

void Function171ac9(void){
    LD_DE(wcd81);
    LD_HL(0x5c);
    LD_A(MOBILEAPI_01);
    CALL(aMobileAPI);
    JP(mFunction171c66);

}

void Function171ad7(void){
    XOR_A_A;
    LD_HL(0xc608);
    LD_BC(0x66);
    CALL(aByteFill);
    LD_DE(0xc608);
    LD_A(MOBILEAPI_06);
    CALL(aMobileAPI);
    JP(mFunction171c66);

}

void Function171aec(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    FARCALL(aBattleTowerRoomMenu_Cleanup);
    POP_AF;
    LDH_addr_A(rSVBK);
    hlcoord(2, 6, wTilemap);
    LD_A(0x8);

asm_171b01:
    PUSH_AF;
    PUSH_HL;
    XOR_A_A;
    LD_BC(0x10);
    CALL(aByteFill);
    POP_HL;
    LD_DE(0x14);
    ADD_HL_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_171b01;
    hlcoord(2, 7, wTilemap);
    LD_A(0x3);
    LD_DE(0xc608);

asm_171b1b:
    PUSH_AF;
    PUSH_HL;
    LD_A_de;
    AND_A_A;
    IF_Z goto asm_171b34;
    LD_A_addr(wcd4b);
    INC_A;
    LD_addr_A(wcd4b);
    PUSH_HL;
    CALL(aFunction171b42);
    POP_HL;
    LD_BC(0xffec);
    ADD_HL_BC;
    CALL(aFunction171b42);

asm_171b34:
    POP_HL;
    LD_BC(0x14);
    ADD_HL_BC;
    ADD_HL_BC;
    ADD_HL_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_171b1b;
    JP(mFunction171c66);

}

void Function171b42(void){
    LD_A_de;
    INC_DE;
    AND_A_A;
    RET_Z ;
    SUB_A(0x20);
    LD_hli_A;
    JR(mFunction171b42);

}

void Function171b4b(void){
    depixel2(8, 2);
    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A(0x8);
    LD_hl_A;

    depixel2(8, 19);
    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A(0x9);
    LD_hl_A;

    depixel4(17, 14, 2, 0);
    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A(0xa);
    LD_hl_A;

    LD_A(0x4);
    LD_addr_A(wcd23);
    LD_A(0x8);
    LD_addr_A(wcd24);
    JP(mFunction171c66);

}

void Function171b85(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(0x2);
    JP_NZ (mFunction171b9f);
    LD_A_hl;
    AND_A(0x1);
    JP_NZ (mFunction171bbd);
    LD_A_hl;
    AND_A(0x40);
    JR_NZ (masm_171ba5);
    LD_A_hl;
    AND_A(0x80);
    JR_NZ (masm_171baf);
    RET;

}

void Function171b9f(void){
    LD_A(0x80);
    LD_addr_A(wcd49);
    RET;

}

void asm_171ba5(void){
    LD_A_addr(wcd4a);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wcd4a);
    RET;

}

void asm_171baf(void){
    LD_A_addr(wcd4b);
    LD_C_A;
    LD_A_addr(wcd4a);
    CP_A_C;
    RET_Z ;
    INC_A;
    LD_addr_A(wcd4a);
    RET;

}

void Function171bbd(void){
    CALL(aPlayClickSFX);
    LD_A(0x8);
    LD_addr_A(wcd23);
    XOR_A_A;
    LD_addr_A(wcd24);
    JP(mFunction171c66);

}

void Function171bcc(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(0x2);
    JP_NZ (mFunction171bdc);
    LD_A_hl;
    AND_A(0x1);
    JP_NZ (mFunction171beb);
    RET;

}

void Function171bdc(void){
    LD_A(0x4);
    LD_addr_A(wcd23);
    LD_A(0x8);
    LD_addr_A(wcd24);
    LD_HL(wcd49);
    DEC_hl;
    RET;

}

void Function171beb(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_A_addr(wcd4a);
    LD_addr_A(0xaa4a);
    CALL(aCloseSRAM);
    LD_HL(mMenuHeader_171c6b);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    FARCALL(aReloadMapPart);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_171c73);
    CALL(aPlaceString);
    LD_A_addr(wcd4a);
    CP_A(0x2);
    IF_Z goto asm_171c1f;
    LD_A(0x8);
    goto asm_171c21;

asm_171c1f:
    LD_A(0xc);

asm_171c21:
    LD_addr_A(wcd24);
    LD_A(0x1e);
    LD_addr_A(wcd4c);
    CALL(aFunction171c66);

    return Function171c2c();
}

void Function171c2c(void){
    LD_HL(wcd4c);
    DEC_hl;
    RET_NZ ;
    CALL(aExitMenu);
    CALL(aClearBGPalettes);
    JR(masm_171c60);

}

void Function171c39(void){
    LD_A(0x28);
    LD_addr_A(wcd4c);
    CALL(aFunction171c66);

    return Function171c41();
}

void Function171c41(void){
    LD_HL(wcd4c);
    DEC_hl;
    RET_NZ ;
    CALL(aClearBGPalettes);
    FARCALL(aStubbed_Function106462);
    FARCALL(aFunction106464);
    LD_A(0x2);
    LD_addr_A(wc303);
    FARCALL(aDisplayMobileError);
    return asm_171c60();
}

void asm_171c60(void){
    LD_A(0x80);
    LD_addr_A(wcd49);
    RET;

}

void Function171c66(void){
    // LD_HL(wcd49);
    // INC_hl;
    wram->wcd49++;
    // RET;
}

void MenuHeader_171c6b(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return String_171c73();
}

void String_171c73(void){
    //db ['"モバイルセンターを\u3000けってい"'];
    //next ['"しました@"']

    return Function171c87();
}

// LoadEnterPasswordGFX
void Function171c87(void){
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // LD_HL(mAsciiFontGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_BC(0x6e0);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, AsciiFontGFX, 0x0, 0x6e0 / LEN_2BPP_TILE);
    // LD_HL(mPasswordSlowpokeLZ);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, PasswordSlowpokeLZ);
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // LD_HL(mPasswordTopTilemap);
    // decoord(0, 0, wTilemap);
    // LD_BC(0x168);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, PasswordTopTilemap);
    // LD_HL(mMobilePasswordAttrmap);
    // decoord(0, 0, wAttrmap);
    // LD_BC(0x168);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, MobilePasswordAttrmap);
    // hlcoord(3, 2, wTilemap);
    // LD_DE(mString_172e31);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_172e31), coord(3, 2, wram->wTilemap));
    // hlcoord(3, 16, wTilemap);
    // LD_DE(mString_172e3f);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_172e3f), coord(3, 16, wram->wTilemap));
    // RET;
}

void Function171ccd(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(mMobilePasswordPalettes);
    LD_DE(wBGPals1);
    LD_BC(8 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(wOBPals1 + PALETTE_SIZE * 0 + PAL_COLOR_SIZE * 1);
    LD_A(LOW(PALRGB_WHITE));
    LD_hli_A;
    LD_A(HIGH(PALRGB_WHITE));
    LD_hl_A;
    CALL(aSetPalettes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function171cf0(void){
    XOR_A_A;
    hlcoord(4, 15, wTilemap);
    LD_hli_A;
    LD_hli_A;
    LD_A_addr(wcd4b);
    XOR_A(0x1);
    LD_addr_A(wcd4b);
    AND_A_A;
    IF_NZ goto shifted;
    LD_HL(mPasswordBottomTilemap);
    decoord(0, 7, wTilemap);
    LD_BC(0x8c);
    CALL(aCopyBytes);
    hlcoord(3, 16, wTilemap);
    LD_DE(mString_172e3f);
    JP(mPlaceString);


shifted:
    LD_HL(mPasswordShiftTilemap);
    decoord(0, 7, wTilemap);
    LD_BC(0x8c);
    CALL(aCopyBytes);
    hlcoord(3, 16, wTilemap);
    LD_DE(mString_172e4e);
    JP(mPlaceString);

}

void Function171d2b(void){
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // LD_HL(mAsciiFontGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_BC(0x6e0);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, AsciiFontGFX, 0, 110); // 0x6e0 / LEN_2BPP_TILE
    // LD_HL(mPasswordSlowpokeLZ);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, PasswordSlowpokeLZ);
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // LD_HL(mChooseMobileCenterTilemap);
    // decoord(0, 0, wTilemap);
    // LD_BC(0x168);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wTilemap), 0x168, ChooseMobileCenterTilemap);
    // LD_HL(mChooseMobileCenterAttrmap);
    // decoord(0, 0, wAttrmap);
    // LD_BC(0x168);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wAttrmap), 0x168, ChooseMobileCenterAttrmap);
    // hlcoord(2, 2, wTilemap);
    // LD_DE(mString_172e5d);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_172e5d), coord(2, 2, wram->wTilemap));
    // hlcoord(14, 16, wTilemap);
    // LD_DE(mString_172e58);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_172e58), coord(14, 16, wram->wTilemap));
    // RET;
}

void MobilePasswordPalettes(void){
// INCLUDE "gfx/mobile/mobile_password.pal"
}

const char AsciiFontGFX[] = "gfx/mobile/ascii_font.png";

const char PasswordTopTilemap[] = "gfx/mobile/password_top.tilemap";
const char PasswordBottomTilemap[] = "gfx/mobile/password_bottom.tilemap";
const char PasswordShiftTilemap[] = "gfx/mobile/password_shift.tilemap";

const char ChooseMobileCenterTilemap[] = "gfx/mobile/mobile_center.tilemap";
const char MobilePasswordAttrmap[] = "gfx/mobile/password.attrmap";
const char ChooseMobileCenterAttrmap[] = "gfx/mobile/mobile_center.attrmap";

const char PasswordSlowpokeLZ[] = "gfx/pokedex/slowpoke.png";

const char String_172e31[] = "Enter PASSWORD@"; // "パスワード<WO>いれてください@"
const char String_172e3f[] = " SWAP QUIT  OK @"; // "きりかえ\u3000やめる\u3000\u3000けってい@"
const char String_172e4e[] = " SWAP QUIT  OK @"; // "きりかえ\u3000やめる\u3000\u3000"
const char String_172e58[] = "OK"; // "けってい@"
const char String_172e5d[] = 
            "Connect to a" // "せつぞくする\u3000モバイルセンターを"
    t_next  "MOBILE CENTER@"; // "えらんで\u3000ください@"

// LoadMobileStadiumGFX
void Function172e78(void){
    // LD_A(0x7f);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(0x168);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // LD_A(0x7);
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(0x168);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7);
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // LD_HL(mStadium2N64GFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_BC(0x610);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, Stadium2N64GFX, 0x0, 0x610 / LEN_2BPP_TILE);
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // LD_HL(mStadium2N64Tilemap);
    // decoord(0, 0, wTilemap);
    // LD_BC(0x168);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wTilemap), 0x168, Stadium2N64Tilemap);
    // LD_HL(mStadium2N64Attrmap);
    // decoord(0, 0, wAttrmap);
    // LD_BC(0x168);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wAttrmap), 0x168, Stadium2N64Attrmap);
    // RET;
}

void Function172eb9(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mPalette_172edf);
    // LD_DE(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wBGPals1, Palette_172edf, 8 * PALETTE_SIZE);
    // LD_HL(mPalette_172edf);
    // LD_DE(wBGPals2);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wBGPals2, Palette_172edf, 8 * PALETTE_SIZE);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

const uint16_t Palette_172edf[] = {
    rgb(5, 12, 17),
    rgb(31, 31, 31),
    rgb(18, 25, 28),
    rgb(10, 17, 21),
    rgb(6, 13, 18),
    rgb(31, 31, 31),
    rgb(20, 26, 28),
    rgb(12, 19, 23),
    rgb(3, 10, 16),
    rgb(31, 31, 31),
    rgb(6, 13, 18),
    rgb(20, 26, 28),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(5, 5, 16),
    rgb(8, 19, 28),
    rgb(0, 0, 0),
    rgb(31, 31, 31),
    rgb(31, 31, 31),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
};

const char Stadium2N64GFX[] = "gfx/mobile/stadium2_n64.2bpp";

const char Stadium2N64Tilemap[] =
#if defined(_CRYSTAL11)
//  Crystal 1.1 corrupted this tilemap by treating $0a bytes as Unix newlines,
//  and converting them to $0d $0a Windows newlines.
    "gfx/mobile/stadium2_n64_corrupt.tilemap";
#else
    "gfx/mobile/stadium2_n64.tilemap";
#endif

const char Stadium2N64Attrmap[] = "gfx/mobile/stadium2_n64.attrmap";
