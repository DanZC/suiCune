#include "../constants.h"
#include "mobile_40.h"
#include "mobile_41.h"
#include "mobile_42.h"
#include "mobile_12_2.h"
#include "mobile_22.h"
#include "mobile_45_sprite_engine.h"
#include "mobile_5e.h"
#include "mobile_5f.h"
#include "../home/delay.h"
#include "../home/copy.h"
#include "../home/sram.h"
#include "../home/menu.h"
#include "../home/text.h"
#include "../home/joypad.h"
#include "../home/serial.h"
#include "../home/map.h"
#include "../home/mobile.h"
#include "../home/time.h"
#include "../home/random.h"
#include "../home/map_objects.h"
#include "../home/tilemap.h"
#include "../home/copy_tilemap.h"
#include "../home/gfx.h"
#include "../home/lcd.h"
#include "../home/audio.h"
#include "../home/window.h"
#include "../home/clear_sprites.h"
#include "../home/double_speed.h"
#include "../home/print_text.h"
#include "../home/sprite_updates.h"
#include "../home/names.h"
#include "../home/battle.h"
#include "../home/pokedex_flags.h"
#include "../engine/tilesets/timeofday_pals.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/color.h"
#include "../engine/gfx/crystal_layouts.h"
#include "../engine/gfx/load_pics.h"
#include "../engine/gfx/sprites.h"
#include "../engine/battle/core.h"
#include "../engine/battle/menu.h"
#include "../engine/link/place_waiting_text.h"
#include "../engine/link/link_trade.h"
#include "../engine/link/time_capsule.h"
#include "../engine/events/battle_tower/rules.h"
#include "../engine/events/battle_tower/get_trainer_class.h"
#include "../engine/events/poke_seer.h"
#include "../engine/overworld/scripting.h"
#include "../engine/overworld/player_object.h"
#include "../engine/overworld/map_setup.h"
#include "../engine/pokemon/stats_screen.h"
#include "../engine/pokemon/evolve.h"
#include "../engine/pokemon/breeding.h"
#include "../engine/pokemon/mon_stats.h"
#include "../engine/pokemon/move_mon.h"
#include "../engine/pokedex/unown_dex.h"
#include "../engine/menus/save.h"
#include "../engine/menus/menu.h"
#include "../data/text/common.h"
#include "../data/text/battle.h"
#include "../charmap.h"

const mobile_comm_fn_t *gMobileCommsJumptable;
uint8_t* gMobile_wcd3b; // ChunkedDataSource
uint8_t* gMobile_wcd3e; // ChunkedDataDest
const uint8_t* gMobile_wd1ec;

// macro_100fc0: MACRO
//     ; first byte:
//     ;     Bit 7 set: Not SRAM
//     ;     Lower 7 bits: Bank if SRAM
//     ; address, size[, OT address]
//     db ($80 * (\1 >= SRAM_End)) | (BANK(\1) * (\1 < SRAM_End))
//     dw \1, \2
//     if _NARG == 3
//         dw \3
//     else
//         dw NULL
//     endc
// ENDM

#define macro_100fc0(A, B, C) {(0x80 * ((A & 0xffff) >= SRAM_End)) | (MBANK(A) * ((A & 0xffff) < SRAM_End)), A, B, C}

//  d: 1 or 2
//  e: bank
//  bc: addr
uint8_t Function100000(uint8_t d, uint8_t e, const mobile_comm_fn_t *bc){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(1);
    // LDH_addr_A(rSVBK);

    // CALL(aFunction100022);
    Function100022(d, e, bc);
    // CALL(aFunction1000ba);
    Function1000ba();
    // CALL(aFunction100675);
    Function100675();
    // CALL(aFunction100057);
    Function100057();
    // CALL(aFunction10016f);
    Function10016f();
    // CALL(aFunction100276);
    uint8_t c = Function100276();

    // PUSH_BC;
    // CALL(aFunction100301);
    Function100301();
    // POP_BC;

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    return c;
}

void Function100022(uint8_t d, uint8_t e, const mobile_comm_fn_t* bc){
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aSetRAMStateForMobile);
    SetRAMStateForMobile();
    // POP_BC;
    // POP_DE;
    // LD_A_D;
    // LD_addr_A(wcd21);
    wram->wcd21 = d;
    // LD_A_E;
    // LD_addr_A(wcd22);
    wram->wcd22 = e;
    // LD_A_C;
    // LD_addr_A(wcd23);
    // LD_A_B;
    // LD_addr_A(wcd24);
    gMobileCommsJumptable = bc;
    // FARCALL(aFunction10127e);
    Function10127e();
    // FARCALL(aStubbed_Function106462);
    // FARCALL(aFunction106464);  // load broken gfx
    Function106464();
    // FARCALL(aFunction11615a);  // init RAM
    Function11615a();
    // LD_HL(wVramState);
    // SET_hl(1);
    bit_set(wram->wVramState, 1);
    // RET;
}

void Function100057(void){
    // CALL(aDisableMobile);
    DisableMobile();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // LD_HL(wVramState);
    // RES_hl(1);
    bit_reset(wram->wVramState, 1);
    // RET;

}

void SetRAMStateForMobile(void){
    // XOR_A_A;
    // LD_HL(wBGMapBuffer);
    // LD_BC(0x65);
    // CALL(aByteFill);
    ByteFill(wram->wBGMapBuffer, 0x65, 0x0);
    // XOR_A_A;
    // LD_HL(wMobileWRAM);
    // LD_BC(wMobileWRAMEnd - wMobileWRAM);
    // CALL(aByteFill);
    ByteFill(wram->wMobileErrorCodeBuffer, wMobileWRAMEnd - wMobileWRAM, 0x0);
    // LDH_A_addr(rIE);
    // LD_addr_A(wBGMapBuffer);
    wram->wBGMapBuffer[0] = gb_read(rIE);
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0x0;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // RET;

}

void EnableMobile(void){
    // XOR_A_A;
    // LD_HL(wOverworldMapBlocks);
    // LD_BC(wOverworldMapBlocksEnd - wOverworldMapBlocks);
    // CALL(aByteFill);
    ByteFill(wram->wOverworldMapBlocks, sizeof(wram->wOverworldMapBlocks), 0x0);

    // NOP;
    // CALL(aDoubleSpeed);
    DoubleSpeed();
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // LD_A(IE_DEFAULT);
    // LDH_addr_A(rIE);
    gb_write(rIE, IE_DEFAULT);
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0x0;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // LD_A(0x01);
    // LDH_addr_A(hMobileReceive);
    hram->hMobileReceive = 0x01;
    // LDH_addr_A(hMobile);
    hram->hMobile = 0x01;
    // NOP;

    // RET;
}

void DisableMobile(void){
    // NOP;
    // XOR_A_A;
    // LDH_addr_A(hMobileReceive);
    hram->hMobileReceive = 0x0;
    // LDH_addr_A(hMobile);
    hram->hMobile = 0x0;
    // XOR_A_A;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0x0;
    // CALL(aNormalSpeed);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // LD_A_addr(wBGMapBuffer);
    // LDH_addr_A(rIE);
    gb_write(rIE, wram->wBGMapBuffer[0]);
    // NOP;
    // RET;
}

// MobileComms_JumptableLoop
void Function1000ba(void){
    do {
    // loop:
    // call [wcd22]:([wcd23][wcd24] + [wMobileCommsJumptableIndex])
        // HACK TO REMOVE SOFTLOCK
        wram->wVBlankOccurred = 1;
        // LD_HL(wcd23);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_A_addr(wMobileCommsJumptableIndex);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_addr(wcd22);
        // CALL(aGetFarWord);
        // LD_A_addr(wcd22);
        // RST(aFarCall);
        printf("Mobile comms 0x%02X\n", wram->wMobileCommsJumptableIndex);
        gMobileCommsJumptable[wram->wMobileCommsJumptableIndex]();

        // CALL(aFunction1000e8);
        Function1000e8();
        // CALL(aFunction1000fa);
        Function1000fa();
        // CALL(aFunction100144);
        Function100144();
        // CALL(aFunction100163);
        Function100163();
        if(wram->wVBlankOccurred == 1) // If we haven't delayed yet.
            DelayFrame();
        // LD_A_addr(wcd2b);
        // AND_A_A;
        // IF_Z goto loop;
    } while(wram->wcd2b == 0);
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void Function1000e8(void){
    // LD_HL(wcd29);
    // BIT_hl(7);
    // RET_Z ;
    if(!bit_test(wram->wcd29, 7))
        return;
    // FARCALL(aFunction115dd3);
    Function115dd3();
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // RET;
}

void Function1000fa(void){
    // LD_A_addr(wc30d);
    // AND_A_A;
    // RET_Z ;
    // LD_HL(wcd29);
    // BIT_hl(4);
    // RET_Z ;
    if(wram->wc30d == 0 || !bit_test(wram->wcd29, 4))
        return;
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto asm_100117;
    if(wram->wcd2b == 0) {
        // FARCALL(aFunction11619d);
        Function11619d();
        // LD_HL(wcd29);
        // SET_hl(6);
        bit_set(wram->wcd29, 6);
        // RET;
        return;
    }

// asm_100117:
    // NOP;
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // LDH_A_addr(rIE);
    // AND_A(0x1f ^ (1 << SERIAL | 1 << TIMER));
    // LDH_addr_A(rIE);
    gb_write(rIE, gb_read(rIE) & (0x1f ^ (1 << SERIAL | 1 << TIMER)));
    // XOR_A_A;
    // LDH_addr_A(hMobileReceive);
    hram->hMobileReceive = 0x0;
    // LDH_addr_A(hMobile);
    hram->hMobile = 0x0;
    // NOP;

    // LD_A_addr(wLinkMode);
    // PUSH_AF;
    uint8_t linkMode = wram->wLinkMode;
    // XOR_A_A;
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_NULL;
    // LD_A(0x04);
    // LD_addr_A(wc314 + 5);
    wram->wc319 = 0x04;
    // FARCALL(aFunction11619d);
    Function11619d();
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // POP_AF;
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = linkMode;
    // RET;

}

void Function100144(void){
    // LD_HL(wcd29);
    // BIT_hl(5);
    // IF_Z goto asm_100155;
    if(!bit_test(wram->wcd29, 5)) {
    // asm_100155:
        // BIT_hl(2);
        // RET_Z ;
        if(!bit_test(wram->wcd29, 2))
            return;
        // RES_hl(2);
        bit_reset(wram->wcd29, 2);
        // RES_hl(6);
        bit_reset(wram->wcd29, 6);
        // FARCALL(aHDMATransferTilemapToWRAMBank3);
        HDMATransferTilemapToWRAMBank3();
        // RET;
        return;
    }
    // RES_hl(5);
    bit_reset(wram->wcd29, 5);
    // RES_hl(2);
    bit_reset(wram->wcd29, 2);
    // RES_hl(6);
    bit_reset(wram->wcd29, 6);
    // CALL(aFunction100320);
    Function100320();
    // RET;
}

void Function100163(void){
    // LD_HL(wcd29);
    // BIT_hl(6);
    // RET_Z ;
    if(!bit_test(wram->wcd29, 6))
        return;
    // RES_hl(6);
    bit_reset(wram->wcd29, 6);
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void Function10016f(void){
    // LD_A_addr(wcd2b);
    uint8_t a;
    uint16_t de;
    switch(wram->wcd2b) {
        // CP_A(0x01);
        // RET_Z ;
        // CP_A(0x02);
        // RET_Z ;
        case 0x01:
        case 0x02:
            return;
        // CP_A(0xff);
        // JP_Z (mFunction10016f_asm_1001f5);
        case 0xff:
        // asm_1001f5:
            // LD_A_addr(wcd2c);
            // LD_addr_A(wMobileErrorCodeBuffer);
            wram->wMobileErrorCodeBuffer[0] = wram->wcd2c;
            // LD_A_addr(wcd2d);
            // LD_addr_A(wMobileErrorCodeBuffer + 2);
            wram->wMobileErrorCodeBuffer[2] = wram->wcd2d;
            // LD_A_addr(wcd2d);
            // LD_addr_A(wMobileErrorCodeBuffer + 1);
            wram->wMobileErrorCodeBuffer[1] = wram->wcd2d;
            // CALL(aFunction10020b);
            Function10020b();
            // RET;
            return;
        // CP_A(0xfe);
        // IF_Z goto asm_1001c4;
        case 0xfe:
        // CP_A(0xf1);
        // IF_Z goto asm_1001c4;
        // CP_A(0xf2);
        // IF_Z goto asm_1001c4;
        case 0xf1:
        case 0xf2:
        // asm_1001c4:
            // LD_A(0xd2);
            a = 0xd2;
            // LD_DE(2);
            de = 2;
            // goto asm_1001d7;
            break;
        // CP_A(0xf5);
        // IF_Z goto asm_1001e7;
        case 0xf5:
        // asm_1001e7:
            // LD_DE(mString10025e);
            // CALL(aFunction100232);
            Function100232(String10025e);
            // RET;
            return;
        // CP_A(0xf6);
        // IF_Z goto asm_1001b6;
        case 0xf6:
        // asm_1001b6:
            // LD_A(0xd5);
            a = 0xd5;
            // LD_DE(0);
            de = 0;
            // goto asm_1001d7;
            break;
        // CP_A(0xfa);
        // JP_Z (mFunction10016f_asm_1001bd);
        case 0xfa:
        // asm_1001bd:
            // LD_A(0xd6);
            a = 0xd6;
            // LD_DE(0);
            de = 0;
            // goto asm_1001d7;
            break;
        // CP_A(0xf7);
        // JP_Z (mFunction10016f_asm_1001ee);
        case 0xf7:
        // asm_1001ee:
            // LD_DE(mString10024d);
            // CALL(aFunction100232);
            Function100232(String10024d);
            // RET;
            return;
        // CP_A(0xf4);
        // IF_Z goto asm_1001d2;
        case 0xf4:
        // asm_1001d2:
            // LD_A(0xd0);
            a = 0xd0;
            // LD_DE(0);
            de = 0;
            break;
        // CP_A(0xf3);
        // IF_Z goto asm_1001cb;
        case 0xf3:
        // asm_1001cb:
            // LD_A(0xd1);
            a = 0xd1;
            // LD_DE(1);
            de = 1;
            // goto asm_1001d7;
            break;
        // CP_A(0xfc);
        // IF_Z goto asm_1001e6;
        case 0xfc: // Dummied out?
        // asm_1001e6:
            // RET;
            return;
        // CP_A(0xfb);
        // IF_Z goto asm_1001af;
        case 0xfb:
        // asm_1001af:
            // LD_A(0xd7);
            a = 0xd7;
            // LD_DE(0);
            de = 0;
            // goto asm_1001d7;
            break;
        // CP_A(0xf8);
        // RET_Z ; // Dummied out?
        // RET;  // ????????????????????????????
        case 0xf8:
        default:
            return;
    }

// asm_1001d7:
    // LD_addr_A(wMobileErrorCodeBuffer);
    wram->wMobileErrorCodeBuffer[0] = a;
    // LD_A_D;
    // LD_addr_A(wMobileErrorCodeBuffer + 2);
    wram->wMobileErrorCodeBuffer[2] = HIGH(de);
    // LD_A_E;
    // LD_addr_A(wMobileErrorCodeBuffer + 1);
    wram->wMobileErrorCodeBuffer[1] = LOW(de);
    // CALL(aFunction10020b);
    Function10020b();
    // RET;
}

void Function10020b(void){
    // XOR_A_A;
    // LD_addr_A(wc303);
    wram->wc303 = 0x0;
    // FARCALL(aFadeOutPalettes);
    FadeOutPalettes();
    // FARCALL(aFunction106464);
    Function106464();
    // CALL(aHideSprites);
    HideSprites();
    // CALL(aDelayFrame);
    DelayFrame();

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x01);
    // LDH_addr_A(rSVBK);

    // FARCALL(aDisplayMobileError);
    DisplayMobileError();

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

// MobileComms_PrintMessage?
void Function100232(const char* de){
    // PUSH_DE;
    // FARCALL(aFunction106464);
    Function106464();
    // CALL(aFunction3f20);
    Function3f20();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // hlcoord(1, 2, wTilemap);
    // POP_DE;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(de), coord(1, 2, wram->wTilemap));
    // CALL(aFunction100320);
    Function100320();
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // RET;

}

const char String10024d[] =
            "Communication" // "つうしんを　キャンセル　しました@"
    t_next  "canceled.@";

const char String10025e[] = 
            "The chosen rooms"  // "おともだちと　えらんだ　へやが"
    t_next  "differ!@";         // "ちがうようです@"

uint8_t Function100276(void){
    // LD_A_addr(wcd2b);
    switch(wram->wcd2b) {
    // CP_A(0x01);
    // IF_Z goto asm_10029f;
    case 0x01:
    // asm_10029f:
        // CALL(aFunction1002dc);
        Function1002dc();
        // LD_C(0);
        // RET;
        return 0;
    // CP_A(0x02);
    // IF_Z goto asm_100296;
    case 0x02:
    // asm_100296:
        // FARCALL(aScript_reloadmappart);
        Script_reloadmappart_Conv(&gCurScript);
        // LD_C(0x04);
        // RET;
        return 0x04;
    // CP_A(0xf5);
    // IF_Z goto asm_1002a5;
    // CP_A(0xf6);
    // IF_Z goto asm_1002a5;
    case 0xf5:
    case 0xf6:
    // asm_1002a5:
        // FARCALL(aScript_reloadmappart);
        Script_reloadmappart_Conv(&gCurScript);
        // CALL(aFunction1002ed);
        Function1002ed();
        // LD_C(0x03);
        // RET;
        return 0x03;
    // CP_A(0xf7);
    // IF_Z goto asm_100293;
    case 0xf7:
    // asm_100293:
        // LD_C(0x02);
        // RET;
        return 0x02;
    // CP_A(0xf8);
    // IF_Z goto asm_1002b1;
    case 0xf8:
    // asm_1002b1:
        // CALL(aFunction1002c9);
        Function1002c9();
        // CALL(aFunction1002dc);
        Function1002dc();
        // LD_DE(mString10024d);
        // CALL(aFunction100232);
        Function100232(String10024d);
        // LD_C(0x02);
        // RET;
        return 0x02;
    // goto asm_1002c0;
    default:
    // asm_1002c0:
        // CALL(aFunction1002c9);
        Function1002c9();
        // CALL(aFunction1002dc);
        Function1002dc();
        // LD_C(0x01);
        // RET;
        return 0x01;
    }

}

void Function1002c9(void){
    // LD_HL(wcd2a);
    // BIT_hl(0);
    // RET_Z ;
    if(!bit_test(wram->wcd2a, 0))
        return;
    // FARCALL(aCleanUpBattleRAM);
    CleanUpBattleRAM();
    // FARCALL(aLoadPokemonData);
    LoadPokemonData();
    // RET;
}

void Function1002dc(void){
    // LD_A(MAPSETUP_LINKRETURN);
    // LDH_addr_A(hMapEntryMethod);
    hram->hMapEntryMethod = MAPSETUP_LINKRETURN;
    // FARCALL(aRunMapSetupScript);
    RunMapSetupScript();
    // XOR_A_A;
    // LDH_addr_A(hMapEntryMethod);
    hram->hMapEntryMethod = 0;
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // RET;
}

void Function1002ed(void){
    // FARCALL(aLoadOW_BGPal7);
    LoadOW_BGPal7();
    // FARCALL(aApplyPals);
    ApplyPals();
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void Function100301(void){
    // LD_HL(wcd2a);
    // BIT_hl(1);
    // RET_Z ;
    if(!bit_test(wram->wcd2a, 1))
        return;
    // FARCALL(aFunction106464);
    Function106464();
    // FARCALL(aFunction10202c);
    Function10202c();
    // FARCALL(aFunction115dd3);
    Function115dd3();
    // CALL(aFunction100320);
    Function100320();
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // RET;
}

// Call_Mobile_ReloadMapPart
void Function100320(void){
    // FARCALL(aMobile_ReloadMapPart);
    // RET;
    return Mobile_ReloadMapPart();
}

void Function100327(void){
//  //  unreferenced
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    RET;

}

u8_flag_s Function10032e(void){
    // CALL(aFunction10034d);
    u8_flag_s res = Function10034d();
    // LD_E_A;
    // RET_NC ;
    if(res.flag) {
        // LD_addr_A(wcd2b);
        wram->wcd2b = res.a;
    }
    // RET;
    return res;
}

// MobileComms_CheckTransfer
u8_flag_s Function100337(void){
    // CALL(aFunction10032e);
    u8_flag_s res = Function10032e();
    // RET_C ;
    if(res.flag)
        return res;
    // LD_A_addr(wc821);
    // BIT_A(4);
    // IF_Z goto asm_100345;
    if(!bit_test(wram->wc821, 4)) {
    // asm_100345:
        // LD_A(0xf9);
        // LD_E_A;
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf9;
        // SCF;
        // RET;
        return u8_flag(0xf9, true);
    }
    // LD_A_E;
    // AND_A_A;
    // RET;
    return u8_flag(res.a, false);
}

// CheckP2PMobileTransferStatus?
u8_flag_s Function10034d(void){
    // LD_A_addr(wc821);
    // BIT_A(1);
    // IF_NZ goto asm_10036a;
    if(bit_test(wram->wc821, 1)) {
    // asm_10036a:
        mobile_api_data_s out = {0};
        // LD_A(MOBILEAPI_00);
        // CALL(aMobileAPI);
        MobileAPI(MOBILEAPI_00, &out);
        // LD_addr_A(wcd2c);
        wram->wcd2c = out.a;
        // LD_A_H;
        // LD_addr_A(wcd2d);
        wram->wcd2d = out.h;
        // LD_A_L;
        // LD_addr_A(wcd2e);
        wram->wcd2e = out.l;
        // LD_A(0xff);
        // SCF;
        // RET;
        return u8_flag(0xff, true);
    }
    // BIT_A(2);
    // IF_NZ goto asm_10037e;
    else if(bit_test(wram->wc821, 2)) {
    // asm_10037e:
        // LD_A(0xfe);
        // SCF;
        // RET;
        return u8_flag(0xfe, true);
    }
    // BIT_A(3);
    // IF_NZ goto asm_100366;
    else if(bit_test(wram->wc821, 3)) {
    // asm_100366:
        // LD_A(0x02);
        // AND_A_A;
        // RET;
        return u8_flag(0x02, false);
    }
    // BIT_A(0);
    // IF_NZ goto asm_100364;
    else if(bit_test(wram->wc821, 0)) {
    // asm_100364:
        // XOR_A_A;
        // RET;
        return u8_flag(0x0, false);
    }
    else {
        // LD_A(0x01);
        // AND_A_A;
        // RET;
        return u8_flag(0x01, false);
    }
}

// MobileComms_P2PTransferJumptable?
void Function100382(void){
    // LD_A_addr(wcd27);
    // LD_HL(mJumptable_10044e);
    printf("P2PTransfer 0x%02x\n", wram->wcd27);
    // RST(aJumpTable);
    switch(wram->wcd27) {
        case 0x0: Function10046a(); break;
        case 0x1: Function10047c(); break;
        case 0x2: Function100493(); break;
        case 0x3: Function1004ba(); break;
        case 0x4: Function1004f4(); break;
        case 0x5: Function1004ce(); break;
        case 0x6: Function1004de(); break;
        case 0x7: Function1004a4(); break;
        case 0x8: Function100495(); break;
        case 0x9: Function1004ce(); break;
        case 0xa: Function1004de(); break;
        case 0xb: Function1004e9(); break;
        case 0xc: Function1004f4(); break;
        case 0xd: Function1004a4(); break;
    }
    // RET;
}

// CopyTransferBufferToPacketBuffer
// Returns 0xff on failure
// Returns 0x0 on success
uint8_t Function10038a(void){
    // LD_HL(wccb4);
    mobile_api_data_s out = {.hl = &wram->wccb4};
    // LD_A(MOBILEAPI_17);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_17, &out);
    // RET;
    return out.a;
}

// CopyReceivedPacketBufferToWCC60
void Function100393(void){
    // LD_HL(wcc60);
    mobile_api_data_s out = {.hl = wram->wcc60_str};
    // LD_A(MOBILEAPI_1D);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_1D, &out);
    // RET;
}

// CopyCC60StringToWram3
void Function10039c(void){
    // LD_HL(wcc60);
    // LD_DE(w3_d000);
    // LD_BC(0x54);
    // LD_A(0x03);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->w3_d000, wram->wcc60_str, 0x54);
    // RET;
}

void Function1003ab(void){
//  //  unreferenced
    LD_HL(w3_d000);
    LD_DE(wcc60);
    LD_BC(0x54);
    LD_A(0x03);
    CALL(aFarCopyWRAM);
    RET;

}

// CopyTransferBufferToWram3
void Function1003ba(void){
    // LD_HL(wccb4);
    // LD_DE(w3_d080);
    // LD_BC(0x54);
    // LD_A(0x03);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->w3_d080, &wram->wccb4, 0x54);
    // RET;
}

// CopyFromWram3ToTransferBuffer
void Function1003c9(void){
    // LD_HL(w3_d080);
    // LD_DE(wccb4);
    // LD_BC(0x54);
    // LD_A(0x03);
    // CALL(aFarCopyWRAM);
    CopyBytes(&wram->wccb4, wram->w3_d080, 0x54);
    // RET;
}

// InitializeTransferBuffer?
void Function1003d8(void){
    // LD_HL(wccb4);
    // LD_A_hli;
    // LD_C_A;
    // LD_B(0);
    uint16_t bc = wram->wccb4;
    // PUSH_HL;
    // ADD_HL_BC;
    // LD_A_addr(wBGMapPalBuffer);
    // LD_hl_A;
    wram->wccb5[bc] = wram->wcd48;
    // POP_HL;
    // INC_BC;
    bc++;
    // CALL(aFunction10043a);
    uint16_t de = Function10043a(wram->wccb5, bc);
    // ADD_HL_BC;
    // LD_hl_E;
    wram->wccb5[bc] = LOW(de);
    // INC_HL;
    // LD_hl_D;
    wram->wccb5[bc+1] = HIGH(de);
    // LD_A_C;
    // ADD_A(0x02);
    // LD_addr_A(wccb4);
    wram->wccb4 = LOW(bc) + 0x02;
    // RET;
}

// Subtract3FromCC60andCCB4
void Function1003f5(void){
    // LD_A_addr(wcc60);
    // SUB_A(0x03);
    // LD_addr_A(wcc60);
    wram->wcc60 -= 0x03;
    // LD_A_addr(wccb4);
    // SUB_A(0x03);
    // LD_addr_A(wccb4);
    wram->wccb4 -= 0x03;
    // RET;
}

// CheckReceivedP2PPacketChecksum?
bool Function100406(void){
    // LD_A_addr(wcc60);
    // SUB_A(0x02);
    // LD_C_A;
    // LD_B(0);
    uint16_t bc = wram->wcc60 - 2;
    // LD_HL(wcc61);
    // CALL(aFunction10043a);
    uint16_t de = Function10043a(wram->wcc61, bc);
    // ADD_HL_BC;
    // LD_A_hli;
    // CP_A_E;
    // IF_NZ goto asm_100426;
    // LD_A_hld;
    // CP_A_D;
    // IF_NZ goto asm_100426;
    if((wram->wcc60_arr[bc+1] | (wram->wcc60_arr[bc+2] << 8)) != de) {
    // asm_100426:
        // LD_A(0xf4);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf4;
        printf("Failed packet checksum! Checksums does not match! Expected %d, Got %d.\n",
            de,
            (wram->wcc60_arr[bc+1] | (wram->wcc60_arr[bc+2] << 8)));
        // goto asm_100432;
    }
    // DEC_HL;
    // LD_A_addr(wBGMapPalBuffer);
    // CP_A_hl;
    // IF_NZ goto asm_10042d;
    else if(wram->wcc61[bc-1] != wram->wcd48) {
    // asm_10042d:
        // LD_A(0xf3);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf3;
        printf("Failed packet checksum! Command ID is incorrect! Expected %d, Got %d.\n", 
            wram->wcd48,
            wram->wcc61[bc-1]);
    }
    else {
        printf("Passed packet checksum.\n");
        // XOR_A_A;
        // RET;
        return false;
    }

// asm_100432:
    // PUSH_HL;
    // LD_HL(wcd7c);
    // INC_hl;
    wram->wcd7c[0]++;
    // POP_HL;
    // SCF;
    // RET;
    return true;
}

// Some kind of checksum?
uint16_t Function10043a(uint8_t* hl, uint16_t bc){
    // PUSH_HL;
    // PUSH_BC;
    // LD_DE(0);
    uint16_t de = 0;

    do {
    // asm_10043f:
        // LD_A_hli;
        // ADD_A_E;
        // LD_E_A;
        // LD_A_D;
        // ADC_A(0);
        // LD_D_A;
        de += *(hl++);
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto asm_10043f;
    } while(--bc != 0);
    // POP_BC;
    // POP_HL;
    // RET;
    return de;
}

// MobileComms_P2PTransfer00
void Function10046a(void){
    // LD_HL(wBGMapPalBuffer);
    // INC_hl;
    wram->wcd48++;
    // CALL(aFunction1003d8);
    Function1003d8();
    // CALL(aFunction1003ba);
    Function1003ba();
    // LD_A_addr(wcd27);
    // INC_A;
    // LD_addr_A(wcd27);
    wram->wcd27++;
    // RET;
}

// MobileComms_P2PTransfer01
void Function10047c(void){
    // CALL(aFunction100337);
    u8_flag_s res = Function100337();
    // RET_C ;
    // RET_Z ;
    if(res.flag || res.a == 0)
        return;
    // CP_A(0x02);
    // IF_Z goto asm_100487;
    if(res.a == 0x02) { // Check if you're sending or receiving first?
    // asm_100487:
        // LD_A(0x08);
        // LD_addr_A(wcd27);
        wram->wcd27 = 0x08;
        // RET;
        return;
    }
    // goto asm_10048d;
    else {
    // asm_10048d:
        // LD_A(0x02);
        // LD_addr_A(wcd27);
        wram->wcd27 = 0x02;
        // RET;
        return;
    }
}

// MobileComms_P2PTransfer02
void Function100493(void){
    // JR(masm_100497);
    return asm_100497();
}

// MobileComms_P2PTransfer08
void Function100495(void){
    // JR(masm_100497);
    return asm_100497();
}

void asm_100497(void){
    // CALL(aFunction100337);
    u8_flag_s res = Function100337();
    // RET_C ;
    // RET_Z ;
    if(res.flag || res.a == 0x0)
        return;
    // LD_A_addr(wcd27);
    // INC_A;
    // LD_addr_A(wcd27);
    wram->wcd27++;
    // RET;
}

// MobileComms_CheckReceivedP2PPacket
bool Function1004a4(void){
    // CALL(aFunction100406);
    // IF_C goto asm_1004b8;
    if(Function100406()) {
    // asm_1004b8:
        // SCF;
        // RET;
        return true;
    }
    // CALL(aFunction1003c9);
    Function1003c9();
    // CALL(aFunction1003f5);
    Function1003f5();
    // LD_A_addr(wcd27);
    // SET_A(7);
    // LD_addr_A(wcd27);
    bit_set(wram->wcd27, 7);
    // RET;
    return false;
}

// MobileComms_P2PTransfer03
void Function1004ba(void){
    // CALL(aFunction10038a);
    uint8_t a = Function10038a();
    // AND_A_A;
    // IF_NZ goto asm_1004c8;
    if(a != 0x0) {
    // asm_1004c8:
        // LD_A(0x08);
        // LD_addr_A(wcd27);
        wram->wcd27 = 0x08;
        // RET;
        return;
    }
    // LD_A_addr(wcd27);
    // INC_A;
    // LD_addr_A(wcd27);
    wram->wcd27++;
    // RET;
}

// MobileComms_P2PTransfer05
void Function1004ce(void){
    // CALL(aFunction100337);
    u8_flag_s res = Function100337();
    // RET_C ;
    // RET_Z ;
    // CP_A(0x02);
    // RET_NZ ;
    if(res.flag || res.a == 0x0 || res.a != 0x02)
        return;
    // LD_A_addr(wcd27);
    // INC_A;
    // LD_addr_A(wcd27);
    wram->wcd27++;
    // RET;

}

// MobileComms_P2PTransfer06
void Function1004de(void){
    // CALL(aFunction100393);
    Function100393();
    // LD_A_addr(wcd27);
    // INC_A;
    // LD_addr_A(wcd27);
    wram->wcd27++;
    // RET;
}

// MobileComms_P2PTransfer0B
void Function1004e9(void){
    // CALL(aFunction10038a);
    Function10038a();
    // LD_A_addr(wcd27);
    // INC_A;
    // LD_addr_A(wcd27);
    wram->wcd27++;
    // RET;
}

// MobileComms_WaitTransferThenCopyResultToWram3
void Function1004f4(void){
    // CALL(aFunction100337);
    u8_flag_s res = Function100337();
    // RET_C ;
    // RET_Z ;
    if(res.flag || res.a == 0x0)
        return;
    // LD_A_addr(wcd27);
    // INC_A;
    // LD_addr_A(wcd27);
    wram->wcd27++;
    // CALL(aFunction10039c);
    Function10039c();
    // RET;
}

void Function100504(uint8_t* de){
    // PUSH_DE;
    // CALL(aFunction3f20);
    Function3f20();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // POP_DE;
    // hlcoord(4, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(4, 2, wram->wTilemap));
    // RET;
}

// MobileComms_InitVerticalMenu?
void Function100513(void){
    // CALL(aFunction3f7c);
    Function3f7c();
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems();
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor(GetMenuData());
    // LD_HL(w2DMenuFlags1);
    // SET_hl(7);
    bit_set(wram->w2DMenuFlags1, 7);
    // RET;
}

bool Function100522(void){
    // LD_A_addr(wcd28);
    // LD_HL(mJumptable_10052a);
    switch(wram->wcd28) {
        case 0: Function100534(); break;
        case 1: Function100545(); break;
        case 2: Function100545(); break;
        case 3: Function100545(); break;
        case 4: return Function10054d();
    }
    // RST(aJumpTable);
    // RET;
    return false;
}

void Jumptable_10052a(void){
    //dw ['Function100534'];
    //dw ['Function100545'];
    //dw ['Function100545'];
    //dw ['Function100545'];
    //dw ['Function10054d'];

    return Function100534();
}

void Function100534(void){
    // CALL(aFunction100513);
    Function100513();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // LD_A_addr(wcd28);
    // INC_A;
    // LD_addr_A(wcd28);
    wram->wcd28++;
    // RET;
}

void Function100545(void){
    // LD_A_addr(wcd28);
    // INC_A;
    // LD_addr_A(wcd28);
    wram->wcd28++;
    // RET;
}

bool Function10054d(void){
    // FARCALL(aMobileMenuJoypad);
    // LD_A_C;
    uint8_t joypad = MobileMenuJoypad_Conv();
    // LD_HL(wMenuJoypadFilter);
    // AND_A_hl;
    // RET_Z ;
    if((joypad & wram->wMenuJoypadFilter) == 0)
        return false;
    // CALL(aMenuClickSound);
    MenuClickSound(joypad);
    // BIT_A(0);
    // IF_NZ goto asm_100565;
    if(bit_test(joypad, A_BUTTON_F)) {
    // asm_100565:
        // LD_A_addr(wcd28);
        // SET_A(7);
        // LD_addr_A(wcd28);
        bit_set(wram->wcd28, 7);
        // AND_A_A;
        // RET;
        return false;
    }
    // BIT_A(1);
    // IF_NZ goto asm_10056f;
    else if(bit_test(joypad, B_BUTTON_F)) {
    // asm_10056f:
        // LD_A_addr(wcd28);
        // SET_A(7);
        // LD_addr_A(wcd28);
        bit_set(wram->wcd28, 7);
        // SCF;
        // RET;
        return true;
    }
    // RET;
    return false;
}

// Mobile_YesNoMenu?
void Function100579(void){
    // LD_A_addr(wcd26);
    // LD_HL(mJumptable_100581);
    switch(wram->wcd26) {
        case 0: Function100585(); break;
        case 1: Function100597(); break;
    }
    // RST(aJumpTable);
    // RET;
}

void Jumptable_100581(void){
    //dw ['Function100585'];
    //dw ['Function100597'];

    return Function100585();
}

void Function100585(void){
    // LD_HL(mMenuHeader_1005b2);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_1005b2);
    // LD_A(0);
    // LD_addr_A(wcd28);
    wram->wcd28 = 0;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;

    return Function100597();
}

void Function100597(void){
    // CALL(aFunction100522);
    bool cancel = Function100522();
    // LD_A_addr(wcd28);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd28, 7))
        return;
    // IF_NC goto asm_1005a6;
    if(cancel) {
        // XOR_A_A;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 0;
    }

// asm_1005a6:
    // CALL(aExitMenu);
    ExitMenu();
    // LD_A_addr(wcd26);
    // SET_A(7);
    // LD_addr_A(wcd26);
    bit_set(wram->wcd26, 7);
    // RET;
}

// Duplicate yes/no menu
const struct MenuHeader MenuHeader_1005b2 = {
    .flags = MENU_BACKUP_TILES,  // flags
    //db ['6', '14'];
    //db ['10', '19'];
    .coord = menu_coords(14, 6, 19, 10),
    .data = &MenuData_1005ba,
    .defaultOption = 1,  // default option
};

// Duplicate yes/no menu
const struct MenuData MenuData_1005ba = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
    .verticalMenu = {
        .count = 2,
        .options = (const char*[]) {
            "YES",  // "はい@"
            "NO",   // "いいえ@"
        },
    },
};

// Call/Wait Menu Jumptable
void Function1005c3(void){
    // LD_A_addr(wcd26);
    // LD_HL(mJumptable_1005cb);
    // RST(aJumpTable);
    switch(wram->wcd26) {
        case 0: return Function1005cf();
        case 1: return Function1005e1();
    }
    // RET;
}

void Jumptable_1005cb(void){
    //dw ['Function1005cf'];
    //dw ['Function1005e1'];

    return Function1005cf();
}

void Function1005cf(void){
    // LD_HL(mMenuHeader_1005fc);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_1005fc); // CALL/WAIT Menu
    // LD_A(0);
    // LD_addr_A(wcd28);
    wram->wcd28 = 0;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;

    return Function1005e1();
}

void Function1005e1(void){
    // CALL(aFunction100522);
    bool carry = Function100522();
    // LD_A_addr(wcd28);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd28, 7))
        return;
    // IF_NC goto asm_1005f0;
    if(carry) {
        // XOR_A_A;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 0;
    }

// asm_1005f0:
    // CALL(aExitMenu);
    ExitMenu();
    // LD_A_addr(wcd26);
    // SET_A(7);
    // LD_addr_A(wcd26);
    bit_set(wram->wcd26, 7);
    // RET;
}

// Call/Cancel Menu
const struct MenuHeader MenuHeader_1005fc = {
    .flags = MENU_BACKUP_TILES,  // flags
    //db ['6', '14'];
    //db ['10', '19'];
    .coord = menu_coords(12, 6, 19, 10),
    .data = &MenuData_100604,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_100604 = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
    .verticalMenu = {
        .count = 2,
        .options = (const char*[]) {
            "CALL",     // "かける@"
            "WAIT",   // "まつ@"
        },
    },
};

void Mobile_CommunicationStandby(void){
    static const char String[] = "PLEASE WAIT!@"; // "つうしんたいきちゅう！@";
    // hlcoord(3, 10, wTilemap);
    // LD_B(1);
    // LD_C(11);
    // CALL(aFunction3eea);
    Function3eea(coord(3, 10, wram->wTilemap), 1, 11);
    // LD_DE(mMobile_CommunicationStandby_String);
    // hlcoord(4, 11, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String), coord(4, 11, wram->wTilemap));
    // RET;
}

bool AdvanceMobileInactivityTimerAndCheckExpired(uint8_t c, uint8_t b){
    // PUSH_BC;
    // CALL(aIncrementMobileInactivityTimerByCFrames);
    IncrementMobileInactivityTimerByCFrames(c);
    // POP_BC;
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // CP_A_B;
    // IF_NC goto timed_out;
    if(wram->wMobileInactivityTimerMinutes >= b) {
    // timed_out:
        // LD_A(0xfa);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xfa;
        // SCF;
        // RET;
        return true;
    }
    // AND_A_A;
    // RET;
    return false;
}

void StartMobileInactivityTimer(void){
    // XOR_A_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0;
    // LD_addr_A(wMobileInactivityTimerSeconds);
    wram->wMobileInactivityTimerSeconds = 0;
    // LD_addr_A(wMobileInactivityTimerFrames);
    wram->wMobileInactivityTimerFrames = 0;
    // RET;
}

void IncrementMobileInactivityTimerBy1Frame(void){
    // LD_C(1);
    return IncrementMobileInactivityTimerByCFrames(1);
}

void IncrementMobileInactivityTimerByCFrames(uint8_t c){
    // LD_HL(wMobileInactivityTimerFrames);  // timer?
    // LD_A_hl;
    // ADD_A_C;
    // CP_A(60);
    // IF_C goto seconds;
    if(wram->wMobileInactivityTimerFrames + c >= 60) {
        // XOR_A_A;
        wram->wMobileInactivityTimerFrames = 0;
    }
    else {
    // seconds:
        // LD_hld_A;
        wram->wMobileInactivityTimerFrames += c;
        // RET_C ;
        return;
    }
    // LD_A_hl;
    // INC_A;
    // CP_A(60);
    // IF_C goto minutes;
    // XOR_A_A;
    if(++wram->wMobileInactivityTimerSeconds < 60) {
        return;
    }

// minutes:
    // LD_hld_A;
    // RET_C ;
    wram->wMobileInactivityTimerSeconds = 0;
    // INC_hl;
    wram->wMobileInactivityTimerMinutes++;
    // RET;
}

// Mobile_UpdateTime
void Function100665(void){
    // CALL(aUpdateTime);
    UpdateTime();
    // LD_HL(wcd36);
    // LDH_A_addr(hHours);
    // LD_hli_A;
    wram->wcd36 = hram->hHours;
    // LDH_A_addr(hMinutes);
    // LD_hli_A;
    wram->wcd37 = hram->hMinutes;
    // LDH_A_addr(hSeconds);
    // LD_hl_A;
    wram->wcd38 = hram->hSeconds;
    // RET;
}

void Function100675(void){
    // LD_HL(wcd2a);
    // BIT_hl(2);
    bool is_set = bit_test(wram->wcd2a, 2) != 0;
    // SET_hl(2);
    bit_set(wram->wcd2a, 2);
    // RET_NZ ;
    if(is_set)
        return;
    // CALL(aFunction1006d3);
    Function1006d3();
    // RET;
}

void Function100681(tile_t* hl){
    // PUSH_HL;
    // LD_HL(wcd2a);
    // BIT_hl(2);
    bool bt = bit_test(wram->wcd2a, 2);
    // LD_HL(wcd2a);
    // SET_hl(2);
    bit_set(wram->wcd2a, 2);
    // POP_HL;
    // IF_NZ goto asm_100694;
    if(!bt) {
        // PUSH_HL;
        // CALL(aFunction1006d3);
        Function1006d3();
        // POP_HL;
    }

// asm_100694:
    // LD_DE(wcd32);
    uint8_t* de = &wram->wcd32;

    return Function100697(hl, de);
}

static tile_t* Function100697_asm_1006b4(tile_t* hl, uint8_t* de) {
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    // RET;
    return PrintNum(hl, de, PRINTNUM_LEADINGZEROS | 1, 2);
}

void Function100697(tile_t* hl, uint8_t* de){
    // LD_A_de;
    // AND_A_A;
    // IF_NZ goto asm_1006bb;
    if(*de != 0) {
    // asm_1006bb:
        // LD_DE(mString1006ca);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String1006ca), hl);
        // RET;
        return;
    }
    // INC_DE;
    de++;
    // PUSH_DE;
    // CALL(aFunction100697_asm_1006b4);
    hl = Function100697_asm_1006b4(hl, de);
    // LD_DE(mString1006c2);
    struct TextPrintState st = {.de = U82C(String1006c2), .hl = hl};
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_H_B;
    // LD_L_C;
    // POP_DE;
    // INC_DE;
    de++;
    // CALL(aFunction100697_asm_1006b4);
    hl = Function100697_asm_1006b4(st.bc, de);
    // LD_DE(mString1006c6);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String1006c6), hl);
    // RET;
}

const char String1006c2[] = " min. @";          // "ふん\u3000@"
const char String1006c6[] = " sec.@";           // "びょう@"
const char String1006ca[] = "1 hour or more@";  // "１じかんいじょう@"

// Mobile_UpdateAndCalculateElapsedTime?
void Function1006d3(void){
    // CALL(aUpdateTime);
    UpdateTime();
    // LD_DE(wcd34);
    // LD_HL(wcd38);

    return Function1006dc(&wram->wcd32, &wram->wcd36);
}

// Mobile_CalculateElapsedTime?
void Function1006dc(uint8_t* de, const uint8_t* hl){
    uint8_t cy = 0;
    // LD_A_hld;
    // LD_C_A;
    uint8_t c = hl[2];
    // LDH_A_addr(hSeconds);
    uint8_t a = hram->hSeconds;
    // SUB_A_C;
    // IF_NC goto asm_1006e5;
    if((cy = a < c)) {
        // ADD_A(0x3c);
        a += 60;
    }

// asm_1006e5:
    // LD_de_A;
    de[2] = a - c;
    // DEC_DE;
    // LD_A_hld;
    // LD_C_A;
    c = hl[1] + cy;
    // LDH_A_addr(hMinutes);
    a = hram->hMinutes;
    // SBC_A_C;
    // IF_NC goto asm_1006f0;
    if((cy = a < c)) {
        // ADD_A(0x3c);
        a += 60;
    }

// asm_1006f0:
    // LD_de_A;
    de[1] = a - c;
    // DEC_DE;
    // LD_A_hl;
    // LD_C_A;
    c = hl[0] + cy;
    // LDH_A_addr(hHours);
    a = hram->hHours;
    // SBC_A_C;
    // IF_NC goto asm_1006fb;
    if((cy = a < c)) {
        // ADD_A(MAX_HOUR);
        a += MAX_HOUR;
    }

// asm_1006fb:
    // LD_de_A;
    de[0] = a - c;
    // RET;
}

void MobileBattleResetTimer(void){
    // LD_A(BANK(sMobileBattleTimer));
    // LD_HL(sMobileBattleTimer);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMobileBattleTimer));
    // XOR_A_A;
    // LD_hli_A;
    gb_write(sMobileBattleTimer, 0);
    // LD_hli_A;
    gb_write(sMobileBattleTimer + 1, 0);
    // LD_hli_A;
    gb_write(sMobileBattleTimer + 2, 0);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void MobileBattleFixTimer(void){
    // LD_A(BANK(sMobileBattleTimer));
    // LD_HL(sMobileBattleTimer);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMobileBattleTimer));
    // XOR_A_A;  // MOBILE_BATTLE_ALLOWED_SECONDS
    // LD_hli_A;
    gb_write(sMobileBattleTimer, MOBILE_BATTLE_ALLOWED_SECONDS);
    // LD_A(MOBILE_BATTLE_ALLOWED_MINUTES);
    // LD_hli_A;
    gb_write(sMobileBattleTimer + 1, MOBILE_BATTLE_ALLOWED_MINUTES);
    // XOR_A_A;
    // LD_hli_A;
    gb_write(sMobileBattleTimer + 2, 0);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

// MobileBattleUpdateAndLoadTimer?
void Function100720(void){
    // XOR_A_A;
    // LD_addr_A(wcd6a);
    wram->wcd6a = 0;
    // CALL(aUpdateTime);
    UpdateTime();
    // LDH_A_addr(hHours);
    // LD_addr_A(wcd72);
    wram->wcd72 = hram->hHours;
    // LDH_A_addr(hMinutes);
    // LD_addr_A(wcd73);
    wram->wcd73 = hram->hMinutes;
    // LDH_A_addr(hSeconds);
    // LD_addr_A(wcd74);
    wram->wcd74 = hram->hSeconds;
    // LD_A(BANK(sMobileBattleTimer));
    // LD_HL(sMobileBattleTimer);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMobileBattleTimer));
    uint8_t* hl = GBToRAMAddr(sMobileBattleTimer);
    // LD_A_hli;
    // LD_addr_A(wcd6c);
    wram->wcd6c = hl[0];
    // LD_A_hli;
    // LD_addr_A(wcd6d);
    wram->wcd6d = hl[1];
    // LD_A_hli;
    // LD_addr_A(wcd6e);
    wram->wcd6e = hl[2];
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A_addr(wcd6d);
    // LD_addr_A(wcd6b);
    wram->wcd6b = wram->wcd6d;
    // RET;

}

// MobileBattleUpdateTime?
void Function100754(void){
    // CALL(aUpdateTime);
    UpdateTime();
    // LDH_A_addr(hHours);
    // LD_addr_A(wcd72);
    wram->wcd72 = hram->hHours;
    // LDH_A_addr(hMinutes);
    // LD_addr_A(wcd73);
    wram->wcd73 = hram->hMinutes;
    // LDH_A_addr(hSeconds);
    // LD_addr_A(wcd74);
    wram->wcd74 = hram->hSeconds;
    // LD_A_addr(wcd6d);
    // LD_addr_A(wcd6b);
    wram->wcd6b = wram->wcd6d;
    // LD_HL(wcd2a);
    // RES_hl(6);
    bit_reset(wram->wcd2a, 6);
    // RET;
}

void Function100772(const uint8_t* de){
    // PUSH_DE;
    const uint8_t* de2 = de;
    // LD_HL(wcd6c);
    const uint8_t* hl = &wram->wcd6c;
    // LD_A_de;
    // CP_A_hl;
    // IF_C goto asm_10079a;
    if(*de < *hl)
        return;
    // IF_NZ goto asm_10078c;
    if(*de == *hl) {
        // INC_HL;
        // INC_DE;
        hl++, de++;
        // LD_A_de;
        // CP_A_hl;
        // IF_C goto asm_10079a;
        if(*de < *hl)
            return;
        // IF_NZ goto asm_10078c;
        if(*de == *hl) {
            // INC_HL;
            // INC_DE;
            hl++, de++;
            // LD_A_de;
            // CP_A_hl;
            // IF_C goto asm_10079a;
            // IF_Z goto asm_10079a;
            if(*de <= *hl)
                return;
        }
    }

// asm_10078c:
    // POP_HL;
    // LD_A_hli;
    // LD_addr_A(wcd6c);
    wram->wcd6c = de2[0];
    // LD_A_hli;
    // LD_addr_A(wcd6d);
    wram->wcd6d = de2[1];
    // LD_A_hli;
    // LD_addr_A(wcd6e);
    wram->wcd6e = de2[2];
    // RET;

// asm_10079a:
    // POP_DE;
    // RET;
}

bool Function10079c(uint8_t b, uint8_t c){
    // LD_A_addr(wcd21);
    // CP_A(0x01);
    // IF_NZ goto dont_quit;
    // LD_HL(wcd2a);
    // BIT_hl(5);
    // IF_NZ goto dont_quit;
    // LD_HL(wcd2a);
    // BIT_hl(6);
    // IF_NZ goto dont_quit;
    if(wram->wcd21 != 0x01 || bit_test(wram->wcd2a, 5) || bit_test(wram->wcd2a, 6))
        return false;
    // LD_A_addr(wcd6a);
    // ADD_A_C;
    // CP_A(60);
    // IF_NC goto overflow;
    if(wram->wcd6a + c < 60) {
        // LD_addr_A(wcd6a);
        wram->wcd6a += c;
        // AND_A_A;
        // RET;
        return false;
    }

// overflow:
    // SUB_A(60);
    // LD_addr_A(wcd6a);
    wram->wcd6a = (wram->wcd6a + c) - 60;
    // LD_D_B;
    // PUSH_DE;
    uint8_t d = b;
    // CALL(aFunction1007f6);
    u8_pair_flag_s res = Function1007f6();
    // POP_DE;
    // IF_C goto quit;
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto quit;
    // LD_A_B;
    // CP_A(10);
    // IF_NC goto quit;
    if(!res.flag && res.b == 0 && res.a < 10) {
        // LD_A_D;
        // AND_A_A;
        // RET_Z ;
        if(d == 0)
            return false;
        // LD_A_addr(wcd6b);
        // CP_A_B;
        // RET_Z ;
        if(wram->wcd6b == res.a)
            return false;
        // LD_A_B;
        // LD_addr_A(wcd6b);
        wram->wcd6b = res.a;
        // CALL(aFunction1008e0);
        Function1008e0();
        // AND_A_A;
        // RET;
        return false;
    }

// quit:
    // CALL(aFunction1008e0);
    Function1008e0();
    // LD_HL(wcd2a);
    // SET_hl(4);
    bit_set(wram->wcd2a, 4);
    // LD_A(0xfc);
    // LD_addr_A(wcd2b);
    wram->wcd2b = 0xfc;
    // SCF;
    // RET;
    return true;

// dont_quit:
    // AND_A_A;
    // RET;
}

u8_pair_flag_s Function1007f6(void){
    // CALL(aUpdateTime);
    UpdateTime();
    // LD_HL(wcd74);
    // LD_DE(wcd71);
    // CALL(aFunction1006dc);
    Function1006dc(wram->wcd6f, &wram->wcd72);
    // LD_A(0x04);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMobileBattleTimer));
    // LD_HL(0xa802);
    // CALL(aFunction100826);
    Function100826(GBToRAMAddr(sMobileBattleTimer));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_HL(wcd6e);
    // CALL(aFunction100826);
    u8_pair_flag_s res = Function100826(&wram->wcd6c);
    // LDH_A_addr(hHours);
    // LD_addr_A(wcd72);
    wram->wcd72 = hram->hHours;
    // LDH_A_addr(hMinutes);
    // LD_addr_A(wcd73);
    wram->wcd73 = hram->hMinutes;
    // LDH_A_addr(hSeconds);
    // LD_addr_A(wcd74);
    wram->wcd74 = hram->hSeconds;
    // RET;
    return res;
}

u8_pair_flag_s Function100826(uint8_t* hl){
    // LD_A_addr(wcd71);
    // ADD_A_hl;
    uint8_t a = wram->wcd71[0] + hl[2];
    uint8_t carry = 0;
    // SUB_A(0x3c);
    if(a >= 60) {
        // IF_NC goto asm_100830;
        // ADD_A(0x3c);
        a -= 60;
        carry = 1;
    }

// asm_100830:
    // LD_hld_A;
    hl[2] = a;
    // CCF;
    // LD_A_addr(wcd70);
    // ADC_A_hl;
    a = wram->wcd70[0] + hl[1] + carry;
    // SUB_A(0x3c);
    if(a >= 60) {
        // IF_NC goto asm_10083c;
        // ADD_A(0x3c);
        a -= 60;
        carry = 1;
    }
    else {
        carry = 0;
    }

// asm_10083c:
    // LD_hld_A;
    hl[1] = a;
    // LD_B_A;
    uint8_t b = a;
    // CCF;
    // LD_A_addr(wcd6f);
    // ADC_A_hl;
    uint16_t c = wram->wcd6f[0] + hl[0] + carry;
    // LD_hl_A;
    hl[0] = (uint8_t)c;
    // LD_C_A;
    // RET;
    return u8_pair_flag(b, c, c >= 256);
}

// MobileBattle_PrintRemainingBattleTime
void Function100846(void){
    // LD_HL(wcd2a);
    // BIT_hl(5);
    // IF_NZ goto asm_10087c;
    if(bit_test(wram->wcd2a, 5)) { // Unlimited battle time
    // asm_10087c:
        // LD_DE(mString_10088e);
        // hlcoord(1, 14, wTilemap);
        struct TextPrintState st = {.de = U82C(String_10088e), .hl = coord(1, 14, wram->wTilemap)};
        // CALL(aPlaceString);
        PlaceString(&st, st.hl);
        // LD_H_B;
        // LD_L_C;
        // LD_DE(mString_10089f);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_10089f), st.bc);
        // RET;
        return;
    }
    // LD_A_addr(wcd6e);
    // LD_C_A;
    // LD_A(0);
    // SUB_A_C;
    // IF_NC goto asm_100858;
    // ADD_A(0x3c);

// asm_100858:
    // LD_addr_A(wStringBuffer2 + 2);
    wram->wStringBuffer2[2] = (wram->wcd6e > 0)? 0x3c - wram->wcd6e: 0;
    // LD_A_addr(wcd6d);
    // LD_C_A;
    // LD_A(0x0a);
    // SBC_A_C;
    // LD_addr_A(wStringBuffer2 + 1);
    wram->wStringBuffer2[1] = 0x0a - wram->wcd6d - (wram->wcd6e > 0);
    // XOR_A_A;
    // LD_addr_A(wStringBuffer2);
    wram->wStringBuffer2[0] = 0;
    // LD_DE(mString_10088e);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_10088e), coord(1, 14, wram->wTilemap));
    // LD_DE(wStringBuffer2);
    // hlcoord(4, 16, wTilemap);
    // CALL(aFunction100697);
    Function100697(coord(4, 16, wram->wTilemap), wram->wStringBuffer2);
    // RET;
}

const char String_10088e[] = 
            "MOBILE BATTLE TIME"    // "モバイルたいせん\u3000できる"
    t_next  "";                     //next "じかん@"

const char String_10089f[] = "UNLIMITED"; // "\u3000むせいげん@"

//  Calculates the difference between 10 minutes and sMobileBattleTimer
//  Returns minutes in c (b) and seconds in b (a)
u8_pair_s MobileBattleGetRemainingTime(void){
    // LD_A(BANK(sMobileBattleTimer));
    // LD_HL(sMobileBattleTimer);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMobileBattleTimer));
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2);
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2 + 1);
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2 + 2);
    CopyBytes(wram->wStringBuffer2, GBToRAMAddr(sMobileBattleTimer), 3);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A_addr(wStringBuffer2 + 2);
    // LD_B_A;
    uint8_t b = wram->wStringBuffer2[2];
    uint8_t carry = 0;
    // LD_A(MOBILE_BATTLE_ALLOWED_SECONDS);
    // SUB_A_B;
    // IF_NC goto no_carry_seconds;
    if(MOBILE_BATTLE_ALLOWED_SECONDS < b){
        // ADD_A(60);
        b = (MOBILE_BATTLE_ALLOWED_SECONDS - b) + 60;
        carry = 1;
    }
    else {
        b = MOBILE_BATTLE_ALLOWED_SECONDS - b;
    }
// no_carry_seconds:
    // LD_B_A;
    // LD_A_addr(wStringBuffer2 + 1);
    // LD_C_A;
    uint8_t c = wram->wStringBuffer2[1];
    // LD_A(MOBILE_BATTLE_ALLOWED_MINUTES);
    // SBC_A_C;
    // LD_C_A;
    // IF_C goto fail;
    if(MOBILE_BATTLE_ALLOWED_MINUTES - carry >= c){
        c = MOBILE_BATTLE_ALLOWED_MINUTES - carry - c;
        // LD_A_addr(wStringBuffer2);
        // AND_A_A;
        // IF_NZ goto fail;
        if(wram->wStringBuffer2[0] == 0){
            // RET;
            return u8_pair(b, c);
        }
    }

// fail:
    // CALL(aMobileBattleFixTimer);
    MobileBattleFixTimer();
    // LD_C(0);
    // RET;
    return u8_pair(b, 0);
}

void Function1008e0(void){
    // LDH_A_addr(hBGMapMode);
    // LD_B_A;
    uint8_t bg_map_mode = hram->hBGMapMode;
    // LDH_A_addr(hVBlank);
    // LD_C_A;
    uint8_t vblank = hram->hVBlank;
    // PUSH_BC;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x03);
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0x03;
    // CALL(aFunction100970);
    Function100970();
    // CALL(aFunction100902);
    Function100902();
    // CALL(aFunction100989);
    Function100989();
    // CALL(aDelayFrame);
    DelayFrame();
    // POP_BC;
    // LD_A_C;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = vblank;
    // LD_A_B;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = bg_map_mode;
    // RET;
}

void Function100902(void){
static const char string_10095a[] = "Time's up!@"; //db ['"たいせん\u3000しゅうりょう@"'];
static const char string_100966[] = "   min. remaining!@"; //db ['"のこり\u3000\u3000\u3000ふん！@"'];
    // hlcoord(3, 10, wTilemap);
    // LD_B(0x01);
    // LD_C(0x0b);
    // CALL(aTextbox);
    Textbox(coord(3, 10, wram->wTilemap), 0x01, 0x0b);
    // LD_A_addr(wcd6d);
    // LD_C_A;
    // LD_A(0x0a);
    // SUB_A_C;
    // LD_addr_A(wStringBuffer2);
    wram->wStringBuffer2[0] = 0x0a - wram->wcd6d;
    // IF_Z goto asm_10093f;
    if(0x0a - wram->wcd6d != 0) {
        // LD_DE(mFunction100902_string_100966);
        // hlcoord(4, 11, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(string_100966), coord(4, 11, wram->wTilemap));
        // hlcoord(8, 11, wTilemap);
        // LD_BC((1 << 8) | 2);
        // LD_DE(wStringBuffer2);
        // CALL(aPrintNum);
        PrintNum(coord(4, 11, wram->wTilemap), wram->wStringBuffer2, 1, 2);
        // LD_DE(SFX_TWO_PC_BEEPS);
        // CALL(aPlaySFX);
        PlaySFX(SFX_TWO_PC_BEEPS);
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_C(0x3c);
        // CALL(aDelayFrames);
        DelayFrames(60);
        // RET;
        return;
    }
    else {
    // asm_10093f:
        // LD_DE(mFunction100902_string_10095a);
        // hlcoord(4, 11, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(string_10095a), coord(4, 11, wram->wTilemap));
        // LD_DE(SFX_4_NOTE_DITTY);
        // CALL(aPlaySFX);
        PlaySFX(SFX_4_NOTE_DITTY);
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_C(120);
        // CALL(aDelayFrames);
        DelayFrames(120);
        // RET;
        return;
    }
}

void Function100970(void){
    // hlcoord(0, 0, wTilemap);
    // LD_DE(w3_dc00);
    // CALL(aFunction1009a5);
    Function1009a5(wram->w3_dc00, coord(0, 0, wram->wTilemap));
    // hlcoord(0, 0, wAttrmap);
    // LD_DE(w3_dd68);
    // CALL(aFunction1009a5);
    Function1009a5(wram->w3_dd68, coord(0, 0, wram->wAttrmap));
    // CALL(aFunction1009d2);
    Function1009d2();
    // CALL(aFunction1009ae);
    Function1009ae();
    // RET;
}

void Function100989(void){
    // LD_HL(w3_dc00);
    // decoord(0, 0, wTilemap);
    // CALL(aFunction1009a5);
    Function1009a5(coord(0, 0, wram->wTilemap), wram->w3_dc00);
    // CALL(aFunction1009ae);
    Function1009ae();
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // LD_HL(w3_dd68);
    // decoord(0, 0, wAttrmap);
    // CALL(aFunction1009a5);
    Function1009a5(coord(0, 0, wram->wAttrmap), wram->w3_dd68);
    // RET;
}

// CopyScreenTiles?
void Function1009a5(uint8_t* de, const uint8_t* hl){
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x03);
    // CALL(aFarCopyWRAM);
    CopyBytes(de, hl, SCREEN_WIDTH * SCREEN_HEIGHT);
    // RET;
}

void Function1009ae(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x03);
    // LDH_addr_A(rSVBK);

    // LD_HL(w3_d800);
    const uint8_t* hl = wram->w3_d800;
    // decoord(0, 0, wAttrmap);
    uint8_t* de = coord(0, 0, wram->wAttrmap);
    // LD_C(SCREEN_WIDTH);
    uint8_t c = SCREEN_WIDTH;
    // LD_B(SCREEN_HEIGHT);
    uint8_t b = SCREEN_HEIGHT;

    do {
    // loop_row:
        // PUSH_BC;
        uint8_t c2 = c;

        do {
        // loop_col:
            // LD_A_hli;
            // LD_de_A;
            *(de++) = *(hl++);
            // INC_DE;
            // DEC_C;
            // IF_NZ goto loop_col;
        } while(--c2 != 0);
        // LD_BC(BG_MAP_WIDTH - SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += BG_MAP_WIDTH - SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop_row;
    } while(--b != 0);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void Function1009d2(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x03);
    // LDH_addr_A(rSVBK);

    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A(0x01);
    // LDH_addr_A(rVBK);

    // LD_HL(w3_d800);
    // debgcoord(0, 0, vBGMap0);
    // LD_BC((0x03 << 8) | 0x24);
    // CALL(aGet2bpp);
    CopyBytes(wram->w3_d800, bgcoord(0, 0, vram->vBGMap2), 0x24 * LEN_2BPP_TILE);

    // POP_AF;
    // LDH_addr_A(rVBK);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

bool Function1009f3(void){
    // LDH_A_addr(hJoyDown);
    // AND_A(SELECT + A_BUTTON);
    // CP_A(SELECT + A_BUTTON);
    // IF_NZ goto select_a;
    if((hram->hJoyDown & (SELECT + A_BUTTON)) == (SELECT + A_BUTTON)) {
        // LD_HL(wcd2a);
        // SET_hl(4);
        bit_set(wram->wcd2a, 4);
        // LD_A(0xf8);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf8;
        // SCF;
        // RET;
        return true;
    }

// select_a:
    // XOR_A_A;
    // RET;
    return false;
}

static uint8_t v_LinkBattleSendReceiveAction_StageForSend(void){
    // LD_A_addr(wBattlePlayerAction);
    // AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    // IF_NZ goto switch_;
    if(wram->wBattlePlayerAction == BATTLEPLAYERACTION_USEMOVE) {
        // LD_A_addr(wCurPlayerMove);
        // LD_B(BATTLEACTION_STRUGGLE);
        // CP_A(STRUGGLE);
        // IF_Z goto struggle;
        if(wram->wCurPlayerMove == STRUGGLE)
            return BATTLEACTION_STRUGGLE & 0x0f;
        // LD_B(BATTLEACTION_SKIPTURN);
        // CP_A(0xff);
        // IF_Z goto struggle;
        if(wram->wCurPlayerMove == 0xff)
            return BATTLEACTION_SKIPTURN & 0x0f;
        // LD_A_addr(wCurMoveNum);
        // goto use_move;
        return (wram->wCurMoveNum) & 0x0f;
    }
    else {
    // switch_:
        // LD_A_addr(wCurPartyMon);
        // ADD_A(BATTLEACTION_SWITCH1);
        // goto use_move;
        return (wram->wCurPartyMon + BATTLEACTION_SWITCH1) & 0x0f;
    }

// struggle:
    // LD_A_B;

// use_move:
    // AND_A(0x0f);
    // RET;
}

static void v_LinkBattleSendReceiveAction_MobileBattle_SendReceiveAction(void){
    // CALL(aFunction100acf);
    Function100acf();
    // CALL(aStartMobileInactivityTimer);
    StartMobileInactivityTimer();
    // LD_A(0);
    // LD_addr_A(wcd27);
    wram->wcd27 = 0;

    do {
    // asm_100a92:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aGetJoypad);
        GetJoypad();
        // FARCALL(aFunction100382);
        Function100382();
        // LD_C(0x01);
        // LD_B(0x03);
        // PUSH_BC;
        // CALL(aAdvanceMobileInactivityTimerAndCheckExpired);
        // POP_BC;
        // IF_C goto asm_100ac7;
        // LD_B(0x01);
        // CALL(aFunction10079c);
        // IF_C goto asm_100ac7;
        // CALL(aFunction1009f3);
        // IF_C goto asm_100ac7;
        // LD_A_addr(wcd2b);
        // AND_A_A;
        // IF_NZ goto asm_100ac7;
        if(AdvanceMobileInactivityTimerAndCheckExpired(0x01, 0x03) || Function10079c(0x01, 0x01) || Function1009f3() || wram->wcd2b != 0) {
        // asm_100ac7:
            // LD_A(0x0f);
            // LD_addr_A(wd430);
            wram->wd430 = 0x0f;
            // goto asm_100ace;

        // asm_100ace:
            // RET;
            return;
        }
        // LD_A_addr(wcd27);
        // BIT_A(7);
        // IF_Z goto asm_100a92;
    } while(!bit_test(wram->wcd27, 7));
    // CALL(aFunction100ae7);
    Function100ae7();
    // goto asm_100ace;
    return;
}

static void v_LinkBattleSendReceiveAction_LinkBattle_SendReceiveAction(void){
    // LD_A_addr(wLinkBattleSentAction);
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = wram->wLinkBattleSentAction;
    // LD_A(0xff);
    // LD_addr_A(wOtherPlayerLinkAction);
    wram->wOtherPlayerLinkAction = 0xff;

    do {
    // waiting:
        // CALL(aLinkTransfer);
        LinkTransfer();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wOtherPlayerLinkAction);
        // INC_A;
        // IF_Z goto waiting;
    } while(wram->wOtherPlayerLinkAction == 0xff);

    // LD_B(10);
    uint8_t b = 10;

    do {
    // receive:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aLinkTransfer);
        LinkTransfer();
        // DEC_B;
        // IF_NZ goto receive;
    } while(--b != 0);

    // LD_B(10);
    b = 10;

    do {
    // acknowledge:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aLinkDataReceived);
        LinkDataReceived();
        // DEC_B;
        // IF_NZ goto acknowledge;
    } while(--b != 0);

    // LD_A_addr(wOtherPlayerLinkAction);
    // LD_addr_A(wBattleAction);
    wram->wBattleAction = wram->wOtherPlayerLinkAction;
    // RET;
}

void v_LinkBattleSendReceiveAction(void){
    // CALL(av_LinkBattleSendReceiveAction_StageForSend);
    // LD_addr_A(wLinkBattleSentAction);
    wram->wLinkBattleSentAction = v_LinkBattleSendReceiveAction_StageForSend();
    // FARCALL(aPlaceWaitingText);
    PlaceWaitingText();
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // IF_NZ goto not_mobile;
    if(wram->wLinkMode == LINK_MOBILE) {
        // CALL(av_LinkBattleSendReceiveAction_MobileBattle_SendReceiveAction);
        v_LinkBattleSendReceiveAction_MobileBattle_SendReceiveAction();
        // CALL(aFunction100da5);
        Function100da5();
        // FARCALL(aFinishBattleAnim);
        FinishBattleAnim();
        // goto done;
    }
    else {
    // not_mobile:
        // CALL(av_LinkBattleSendReceiveAction_LinkBattle_SendReceiveAction);
        v_LinkBattleSendReceiveAction_LinkBattle_SendReceiveAction();
    }

// done:
    // RET;
    return;

}

// SetupMobileActionBuffer?
void Function100acf(void){
    // LD_DE(mUnknown_100b0a);
    const char* de = Unknown_100b0a; // "tetsuji" string
    // LD_HL(wccb5);
    uint8_t* hl = wram->wccb5;
    // LD_A_addr(wLinkBattleSentAction);
    // LD_hli_A;
    *(hl++) = wram->wLinkBattleSentAction;
    // LD_C(0x01);
    uint8_t c = 0x01;
    uint8_t a;

    do {
    // asm_100adb:
        // LD_A_de;
        // INC_DE;
        a = (uint8_t)*(de++);
        // LD_hli_A;
        *(hl++) = a;
        // INC_C;
        c++;
        // AND_A_A;
        // IF_NZ goto asm_100adb;
    } while(a != 0);
    // LD_A_C;
    // LD_addr_A(wccb4);
    wram->wccb4 = c;
    // RET;
}

// CheckMobileActionString?
void Function100ae7(void){
    // LD_DE(mUnknown_100b0a);
    const char* de = Unknown_100b0a; // "tetsuji" string
    // LD_HL(wcc62);
    uint8_t* hl = wram->wcc62;

    while(1) {
    // asm_100aed:
        // LD_A_de;
        // INC_DE;
        uint8_t a = (uint8_t)*(de++);
        // AND_A_A;
        // IF_Z goto asm_100af8;
        if(a == 0) {
        // asm_100af8:
            // LD_A_addr(wcc61);
            // LD_addr_A(wd430);
            wram->wd430 = wram->wcc61[0];
            // RET;
            return;
        }
        // CP_A_hl;
        // IF_NZ goto asm_100aff;
        else if(a != *hl) {
        // asm_100aff:
            // LD_A(0x0f);
            // LD_addr_A(wd430);
            wram->wd430 = 0x0f;
            // LD_A(0xf1);
            // LD_addr_A(wcd2b);
            wram->wcd2b = 0xf1;
            // RET;
            return;
        }
        // INC_HL;
        hl++;
        // goto asm_100aed;
    }
}

// pushc
// setcharmap ascii
const char Unknown_100b0a[] = "tetsuji";
// popc

void Mobile_LoadBattleMenu(void){
    // CALL(aFunction100dd8);
    // RET_C ;
    if(Function100dd8())
        return;
    // LD_HL(mBattleMenuHeader);
    // LD_A(BANK(aBattleMenuHeader));
    // LD_DE(mLoadMenuHeader);
    // CALL(aFarCall_de);
    LoadMenuHeader(&BattleMenuHeader);
    // LD_A(BANK(aBattleMenuHeader));
    // LD_addr_A(wMenuData_2DMenuItemStringsBank);
    // LD_A_addr(wBattleMenuCursorPosition);
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wBattleMenuCursorPosition;
    // CALL(aFunction100e72);
    Function100e72();
    // CALL(aFunction100b45);
    Function100b45();
    // FARCALL(aInitPartyMenuBGPal7);
    InitPartyMenuBGPal7();
    // CALL(aFunction100ed4);
    Function100ed4();
    // LD_A_addr(wMenuCursorPosition);
    // LD_addr_A(wBattleMenuCursorPosition);
    wram->wBattleMenuCursorPosition = wram->wMenuCursorPosition;
    // CALL(aExitMenu);
    ExitMenu();
    // RET;
}

bool Function100b45(void){
    // CALL(aFunction100b7a);
    Function100b7a();

    uint8_t c;
    do {
    // loop:
        // CALL(aMobile_SetOverworldDelay);
        Mobile_SetOverworldDelay();
        // FARCALL(aMobileMenuJoypad);
        c = MobileMenuJoypad_Conv();
        // PUSH_BC;
        // FARCALL(aHDMATransferTilemapToWRAMBank3);
        HDMATransferTilemapToWRAMBank3();
        // CALL(aFunction100e2d);
        // POP_BC;
        // IF_C goto asm_100b6b;
        if(Function100e2d()) {
        // asm_100b6b:
            // LD_A_addr(w2DMenuNumCols);
            // LD_C_A;
            // LD_A_addr(w2DMenuNumRows);
            // CALL(aSimpleMultiply);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->w2DMenuNumCols * wram->w2DMenuNumRows;
            // AND_A_A;
            // RET;
            return false;
        }
        // LD_A_addr(wMenuJoypadFilter);
        // AND_A_C;
        // IF_Z goto loop;
    } while((c & wram->wMenuJoypadFilter) == 0);
    // FARCALL(aMobile_GetMenuSelection);
    // RET;
    return Mobile_GetMenuSelection_Conv(GetMenuData());
}

void Function100b7a(void){
    // LD_HL(mCopyMenuData);
    // LD_A_addr(wMenuData_2DMenuItemStringsBank);
    // RST(aFarCall);
    const struct MenuData* data = GetMenuData();
    // FARCALL(aDraw2DMenu);
    Draw2DMenu_Conv(data);
    // FARCALL(aMobileTextBorder);
    MobileTextBorder();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // FARCALL(aInit2DMenuCursorPosition);
    Init2DMenuCursorPosition_Conv(data);
    // LD_HL(w2DMenuFlags1);
    // SET_hl(7);
    bit_set(wram->w2DMenuFlags1, 7);
    // RET;
}

static void Mobile_MoveSelectionScreen_ListMoves(void){
    // hlcoord(0, 8, wTilemap);
    // LD_B(8);
    // LD_C(8);
    // CALL(aTextbox);
    Textbox(coord(0, 8, wram->wTilemap), 8, 8);
    // LD_HL(wBattleMonMoves);
    // LD_DE(wListMoves_MoveIndicesBuffer);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(wram->wListMoves_MoveIndicesBuffer, wram->wBattleMon.moves, sizeof(wram->wBattleMon.moves));
    // LD_A(SCREEN_WIDTH * 2);
    // LD_addr_A(wListMovesLineSpacing);
    wram->wListMovesLineSpacing = SCREEN_WIDTH * 2;
    // hlcoord(2, 10, wTilemap);
    // PREDEF(pListMoves);
    ListMoves_Conv(coord(2, 10, wram->wTilemap));
    // RET;
}

static uint8_t Mobile_MoveSelectionScreen_GetMoveSelection(void){
Top:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aMobile_MoveSelectionScreen_ListMoves);
    Mobile_MoveSelectionScreen_ListMoves();
    // CALL(aFunction100c98);
    Function100c98();

    while(1) {
    master_loop:
        // FARCALL(aMoveInfoBox);
        MoveInfoBox();

        while(1) {
        // loop:
            // CALL(aMobile_SetOverworldDelay);
            Mobile_SetOverworldDelay();
            // FARCALL(aMobileMenuJoypad);
            uint8_t c = MobileMenuJoypad_Conv();
            // PUSH_BC;
            // FARCALL(aHDMATransferTilemapToWRAMBank3);
            HDMATransferTilemapToWRAMBank3();
            // CALL(aFunction100e2d);
            // POP_BC;
            // IF_C goto b_button;
            if(Function100e2d())
                goto b_button;
            // LD_A_addr(wMenuJoypadFilter);
            // AND_A_C;
            c &= wram->wMenuJoypadFilter;
            // BIT_A(D_UP_F);
            // JP_NZ (mMobile_MoveSelectionScreen_d_up);
            if(bit_test(c, D_UP_F))
                goto d_up;
            // BIT_A(D_DOWN_F);
            // JP_NZ (mMobile_MoveSelectionScreen_d_down);
            else if(bit_test(c, D_DOWN_F))
                goto d_down;
            // BIT_A(A_BUTTON_F);
            // IF_NZ goto a_button;
            else if(bit_test(c, A_BUTTON_F))
                goto a_button;
            // BIT_A(B_BUTTON_F);
            // IF_NZ goto b_button;
            else if(bit_test(c, B_BUTTON_F))
                goto b_button;
            // goto loop;
        }


    d_up:
        // LD_A_addr(wMenuCursorY);
        // AND_A_A;
        // JP_NZ (mMobile_MoveSelectionScreen_master_loop);
        if(wram->wMenuCursorY == 0) {
            // LD_A_addr(wNumMoves);
            // INC_A;
            // LD_addr_A(wMenuCursorY);
            wram->wMenuCursorY = wram->wNumMoves + 1;
        }
        // JP(mMobile_MoveSelectionScreen_master_loop);
        continue;


    d_down:
        // LD_A_addr(wMenuCursorY);
        // LD_B_A;
        // LD_A_addr(wNumMoves);
        // INC_A;
        // INC_A;
        // CP_A_B;
        // JP_NZ (mMobile_MoveSelectionScreen_master_loop);
        if(wram->wMenuCursorY == wram->wNumMoves + 2) {
            // LD_A(0x01);
            // LD_addr_A(wMenuCursorY);
            wram->wMenuCursorY = 0x1;
        }
        // JP(mMobile_MoveSelectionScreen_master_loop);
        continue;


    b_button:
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // LD_addr_A(wCurMoveNum);
        wram->wCurMoveNum = wram->wMenuCursorY - 1;
        // LD_A(0x01);
        // AND_A_A;
        // RET;
        return 0x1;

    a_button:
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // LD_addr_A(wCurMoveNum);
        wram->wCurMoveNum = wram->wMenuCursorY - 1;
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(wBattleMonPP);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(0x3f);
        // IF_Z goto no_pp_left;
        if((wram->wBattleMon.pp[wram->wMenuCursorY - 1] & 0x3f) == 0) {
        // no_pp_left:
            // LD_HL(mBattleText_TheresNoPPLeftForThisMove);
    
        // print_text:
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(BattleText_TheresNoPPLeftForThisMove);
            // CALL(aSafeLoadTempTilemapToTilemap);
            SafeLoadTempTilemapToTilemap();
            // JP(mMobile_MoveSelectionScreen_GetMoveSelection);
            goto Top;
        }
        // LD_A_addr(wPlayerDisableCount);
        // SWAP_A;
        // AND_A(0x0f);
        // DEC_A;
        // CP_A_C;
        // IF_Z goto move_disabled;
        if(((wram->wPlayerDisableCount >> 4) & 0xf) - 1 == wram->wCurMoveNum) {
        // move_disabled:
            // LD_HL(mBattleText_TheMoveIsDisabled);
            // goto print_text;
    
        // print_text:
            // CALL(aStdBattleTextbox);
            StdBattleTextbox(BattleText_TheMoveIsDisabled);
            // CALL(aSafeLoadTempTilemapToTilemap);
            SafeLoadTempTilemapToTilemap();
            // JP(mMobile_MoveSelectionScreen_GetMoveSelection);
            goto Top;
        }
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(wBattleMonMoves);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wCurPlayerMove);
        wram->wCurPlayerMove = wram->wBattleMon.moves[wram->wMenuCursorY - 1];
        // XOR_A_A;
        // RET;
        return 0x0;
    }
}

uint8_t Mobile_MoveSelectionScreen(void){
    // XOR_A_A;
    // LD_addr_A(wSwappingMove);
    wram->wSwappingMove = 0;
    // FARCALL(aCheckPlayerHasUsableMoves);
    // RET_Z ;
    if(!CheckPlayerHasUsableMoves())
        return 0;
    // CALL(aFunction100dd8);
    // JP_C (mxor_a_dec_a);
    if(Function100dd8())
        return 0xff;
    // CALL(aFunction100e72);
    Function100e72();
    // CALL(aMobile_MoveSelectionScreen_GetMoveSelection);
    uint8_t res = Mobile_MoveSelectionScreen_GetMoveSelection();
    // PUSH_AF;
    // FARCALL(aInitPartyMenuBGPal7);
    InitPartyMenuBGPal7();
    // CALL(aFunction100ed4);
    Function100ed4();
    // POP_AF;
    // RET;
    return res;
}

void Function100c98(void){
    static const uint8_t data[] = {
        10, 1,  // cursor start y, x
        (uint8_t)-1, 1,  // rows, columns
        0xa0, 0x00,  // flags
        (2 << 4) | 0,  // cursor offsets
        D_UP | D_DOWN | A_BUTTON | B_BUTTON  // accepted buttons
    };
    // LD_DE(mFunction100c98_data);
    // CALL(aLoad2DMenuData);
    Load2DMenuData(data);
    // LD_A_addr(wNumMoves);
    // INC_A;
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wNumMoves + 1;
    // LD_A_addr(wCurMoveNum);
    // INC_A;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wCurMoveNum + 1;
    // RET;
}

bool Mobile_PartyMenuSelect(void){
    // CALL(aFunction100dd8);
    // RET_C ;
    if(Function100dd8())
        return true;
    // LD_HL(w2DMenuFlags1);
    // SET_hl(7);
    bit_set(wram->w2DMenuFlags1, 7);
    // RES_hl(6);
    bit_reset(wram->w2DMenuFlags1, 6);

    uint8_t c;
    do {
    // loop:
        // CALL(aMobile_SetOverworldDelay);
        Mobile_SetOverworldDelay();
        // FARCALL(aMobileMenuJoypad);
        c = MobileMenuJoypad_Conv();
        // PUSH_BC;
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // FARCALL(aHDMATransferTilemapToWRAMBank3);
        HDMATransferTilemapToWRAMBank3();
        // CALL(aMobileComms_CheckInactivityTimer);
        // POP_BC;
        // IF_C goto done;
        if(MobileComms_CheckInactivityTimer())
            goto done;
        // LD_A_addr(wMenuJoypadFilter);
        // AND_A_C;
        // IF_Z goto loop;
    } while((c & wram->wMenuJoypadFilter) == 0);
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor();
    // LD_A_addr(wPartyCount);
    // INC_A;
    // LD_B_A;
    // LD_A_addr(wMenuCursorY);
    // CP_A_B;
    // IF_Z goto done;
    if(wram->wMenuCursorY == wram->wPartyCount + 1)
        goto done;
    // LD_addr_A(wPartyMenuCursor);
    wram->wPartyMenuCursor = wram->wMenuCursorY;
    // LDH_A_addr(hJoyLast);
    // LD_B_A;
    // BIT_B(1);
    // IF_NZ goto done;
    if(bit_test(hram->hJoyLast, B_BUTTON_F))
        goto done;
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
    // AND_A_A;
    // RET;
    return false;

done:
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // CALL(aWaitSFX);
    WaitSFX();
    // SCF;
    // RET;
    return true;
}

bool MobileBattleMonMenu(void){
    // CALL(aFunction100dd8);
    // RET_C ;
    if(Function100dd8())
        return true;
    // CALL(aFunction100d67);
    Function100d67();
    // LD_HL(w2DMenuFlags1);
    // SET_hl(7);
    bit_set(wram->w2DMenuFlags1, 7);
    // RES_hl(6);
    bit_reset(wram->w2DMenuFlags1, 6);

    uint8_t c;
    do {
    // asm_100d30:
        // CALL(aMobile_SetOverworldDelay);
        Mobile_SetOverworldDelay();
        // FARCALL(aMobileMenuJoypad);
        c = MobileMenuJoypad_Conv();
        // PUSH_BC;
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // FARCALL(aHDMATransferTilemapToWRAMBank3);
        HDMATransferTilemapToWRAMBank3();
        // CALL(aMobileComms_CheckInactivityTimer);
        // POP_BC;
        // IF_C goto asm_100d54;
        if(MobileComms_CheckInactivityTimer())
            return true;
        // LD_A_addr(wMenuJoypadFilter);
        // AND_A_C;
        // IF_NZ goto asm_100d56;
        // goto asm_100d30;
    } while((c & wram->wMenuJoypadFilter) == 0);

// asm_100d54:
    // SCF;
    // RET;

// asm_100d56:
    uint8_t a = (c & wram->wMenuJoypadFilter);
    // PUSH_AF;
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // POP_AF;
    // BIT_A(1);
    // IF_Z goto asm_100d65;
    if(!bit_test(a, B_BUTTON_F)) {
    // asm_100d65:
        // AND_A_A;
        // RET;
        return false;
    }
    // RET_Z ;
    // SCF;
    // RET;
    return true;
}

static const struct MenuData Function100d67_MenuData = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
    .verticalMenu = {
        .count = 3,
        .options = (const char*[]) {
            "TRADE", //db ['"いれかえる@"'];  // TRADE
            "STATS", //db ['"つよさをみる@"'];  // STATS
            "CANCEL", //db ['"キャンセル@"'];  // CANCEL
        },
    },
};
static const struct MenuHeader Function100d67_MenuHeader = {
    .flags = 0,  // flags
    .coord = menu_coords(11, 11, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = &Function100d67_MenuData,
    .defaultOption = 1,  // default option
};
void Function100d67(void){
    // LD_HL(mFunction100d67_MenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&Function100d67_MenuHeader);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aMenuBox);
    MenuBox();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aCopyMenuData);
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor(GetMenuData());
    // LD_HL(w2DMenuFlags1);
    // SET_hl(6);
    bit_set(wram->w2DMenuFlags1, 6);
    // RET;
}

void Function100da5(void){
    // LD_HL(wcd2a);
    // RES_hl(3);
    bit_reset(wram->wcd2a, 3);
    // LD_HL(wcd29);
    // RES_hl(0);
    bit_reset(wram->wcd29, 0);
    // RET;
}

bool Function100db0(void){
    // LD_HL(wcd2a);
    // BIT_hl(3);
    // IF_NZ goto asm_100dbe;
    if(!bit_test(wram->wcd2a, 3)) {
        // LD_HL(wcd2a);
        // SET_hl(3);
        bit_set(wram->wcd2a, 3);
        // SCF;
        // RET;
        return true;
    }

// asm_100dbe:
    // XOR_A_A;
    // RET;
    return false;
}

bool Function100dc0(void){
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // IF_NZ goto mobile;
    // LD_HL(wcd2a);
    // BIT_hl(3);
    // IF_Z goto mobile;
    if(wram->wLinkMode == LINK_MOBILE && bit_test(wram->wcd2a, 3)) {
        // SCF;
        // RET;
        return true;
    }

// mobile:
    // XOR_A_A;
    // RET;
    return false;
}

void Mobile_SetOverworldDelay(void){
    // LD_A(30);
    // LD_addr_A(wOverworldDelay);
    wram->wOverworldDelay = 30;
    // RET;
}

bool Function100dd8(void){
    // LD_C(0x01);
    // LD_B(0x03);
    // FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    // IF_C goto asm_100dfb;
    if(AdvanceMobileInactivityTimerAndCheckExpired(0x01, 0x03))
        return true;
    // LD_C(0x3c);
    // LD_B(0x01);
    // CALL(aFunction10079c);
    // IF_C goto asm_100dfb;
    if(Function10079c(0x01, 0x3c))
        return true;
    // FARCALL(aFunction10032e);
    Function10032e();
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto asm_100dfb;
    if(wram->wcd2b != 0)
        return true;
    // XOR_A_A;
    // RET;
    return false;

// asm_100dfb:
    // SCF;
    // RET;
}

bool MobileComms_CheckInactivityTimer(void){
    // LD_A_addr(wOverworldDelay);
    // LD_C_A;
    // LD_A(30);
    // SUB_A_C;
    // LD_C_A;
    uint8_t c = 30 - wram->wOverworldDelay;
    // LD_B(3);
    uint8_t b = 3;
    // PUSH_BC;
    // FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);  // useless to farcall
    // POP_BC;
    // IF_C goto quit;
    if(AdvanceMobileInactivityTimerAndCheckExpired(c, b))
        return true;
    // LD_B(1);
    // CALL(aFunction10079c);
    // IF_C goto quit;
    if(Function10079c(1, c))
        return true;
    // CALL(aFunction1009f3);
    // IF_C goto quit;
    if(Function1009f3())
        return true;
    // FARCALL(aFunction10032e);  // useless to farcall
    Function10032e();
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto quit;
    if(wram->wcd2b != 0)
        return true;
    // XOR_A_A;
    // RET;
    return false;

// quit:
    // SCF;
    // RET;
}

bool Function100e2d(void){
    // LD_A_addr(wOverworldDelay);
    // LD_C_A;
    // LD_A(30);
    // SUB_A_C;
    // LD_C_A;
    uint8_t c = 30 - wram->wOverworldDelay;
    // LD_B(3);
    uint8_t b = 3;
    // PUSH_BC;
    // FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    // POP_BC;
    // IF_C goto asm_100e61;
    if(AdvanceMobileInactivityTimerAndCheckExpired(c, b))
        return true;
    // LD_B(1);
    // CALL(aFunction10079c);
    // IF_C goto asm_100e61;
    if(Function10079c(1, c))
        return true;
    // CALL(aFunction1009f3);
    // IF_C goto asm_100e61;
    if(Function1009f3())
        return true;
    // FARCALL(aFunction10032e);
    u8_flag_s res = Function10032e();
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto asm_100e61;
    if(wram->wcd2b == 0) {
        // CALL(aFunction100e63);
        Function100e63(res.a);
        // CALL(aFunction100e84);
        Function100e84();
        // XOR_A_A;
        // RET;
        return false;
    }
    else {
    // asm_100e61:
        // SCF;
        // RET;
        return true;
    }
}

void Function100e63(uint8_t e){
    // LD_A_E;
    // CP_A(0x02);
    // RET_NZ ;
    if(e != 0x2)
        return;
    // CALL(aFunction100db0);
    // RET_NC ;
    if(!Function100db0())
        return;
    // LD_DE(SFX_ELEVATOR_END);
    // CALL(aPlaySFX);
    PlaySFX(SFX_ELEVATOR_END);
    // RET;
}

void Function100e72(void){
    // XOR_A_A;
    // LD_HL(wcd29);
    // BIT_hl(0);
    // IF_Z goto asm_100e7c;
    // LD_A(0x0a);

// asm_100e7c:
    // LD_addr_A(wcd67);
    wram->wcd67 = (bit_test(wram->wcd29, 0))? 0x0a: 0;
    // XOR_A_A;
    // LD_addr_A(wcd68);
    wram->wcd68 = 0;
    // RET;
}

void Function100e84(void){
    // LD_A_addr(wcd67);
    // LD_HL(mJumptable_100e8c);
    // RST(aJumpTable);
    // RET;
    return Jumptable_100e8c(wram->wcd67);
}

void Jumptable_100e8c(uint8_t a){
    switch(a) {
        case 0x0: return Function100ea2();
        case 0x1: return Function100eae();
        case 0x2: return Function100eb4();
        case 0x3: return Function100eae();
        case 0x4: return Function100eb4();
        case 0x5: return Function100eae();
        case 0x6: return Function100eb4();
        case 0x7: return Function100eae();
        case 0x8: return Function100eb4();
        case 0x9: return Function100eae();
        case 0xa: return Function100ec4();
    }
}

void Function100ea2(void){
    // CALL(aFunction100dc0);
    // RET_NC ;
    if(!Function100dc0())
        return;
    // LD_HL(wcd29);
    // SET_hl(0);
    bit_set(wram->wcd29, 0);
    // CALL(aFunction100ec5);
    Function100ec5();

    return Function100eae();
}

void Function100eae(void){
    // SCF;
    // CALL(aFunction100eca);
    Function100eca(true);
    // JR(masm_100eb8);
    return asm_100eb8();
}

void Function100eb4(void){
    // AND_A_A;
    // CALL(aFunction100eca);
    Function100eca(false);

    return asm_100eb8();
}

void asm_100eb8(void){
    // LD_HL(wcd68);
    // INC_hl;
    wram->wcd68++;
    // LD_A_hl;
    // CP_A(0x02);
    // RET_C ;
    if(wram->wcd68 < 2)
        return;
    // LD_hl(0);
    wram->wcd68 = 0;
    // JR(mFunction100ec5);
    return Function100ec5();
}

void Function100ec4(void){
    // RET;

}

void Function100ec5(void){
    // LD_HL(wcd67);
    // INC_hl;
    wram->wcd67++;
    // RET;

}

void Function100eca(bool isMobile){
    // FARCALL(aMobile_InitPartyMenuBGPal7);
    Mobile_InitPartyMenuBGPal7(isMobile);
    // CALL(aFunction100ed4);
    Function100ed4();
    // RET;
}

void Function100ed4(void){
    // FARCALL(aApplyPals);
    ApplyPals();
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;

}

// LoadStoredPartyDataForTransfer?
uint16_t Function100edf(uint8_t* de){
    // LD_HL(mUnknown_100fc0);
    // LD_C(1);
    // JR(mFunction100f02);
    return Function100f02(de, Unknown_100fc0, 1);
}

// StoreTransferedOTData?
uint16_t Function100ee6(uint8_t* de){
    // LD_HL(mUnknown_100fc0);
    // LD_C(2);
    // JR(mFunction100f02);
    return Function100f02(de, Unknown_100fc0, 2);
}

// LoadStoredMailDataForTransfer?
uint16_t Function100eed(uint8_t* de){
    // LD_HL(mUnknown_100feb);
    // LD_C(1);
    // JR(mFunction100f02);
    return Function100f02(de, Unknown_100feb, 1);
}

// LoadStoredOTDataForTransfer?
uint16_t Function100ef4(uint8_t* de){
    // LD_HL(mUnknown_100ff3);
    // LD_C(1);
    // JR(mFunction100f02);
    return Function100f02(de, Unknown_100ff3, 1);
}

void Function100efb(void){
//  //  unreferenced
    LD_HL(mUnknown_10102c);
    LD_C(1);
    JR(mFunction100f02);

}

uint16_t Function100f02(uint8_t* de, const macro_100fc0_s* hl, uint8_t c){
    Function100f02_Data_s data = {};
    // LD_A_C;
    // LD_addr_A(wStringBuffer2);
    data.c = c;
// someting that was previously stored in de gets backed up to here
    // LD_A_E;
    // LD_addr_A(wStringBuffer2 + 1);
    // LD_A_D;
    // LD_addr_A(wStringBuffer2 + 2);
    data.de = de;
// empty this
    // XOR_A_A;
    // LD_addr_A(wStringBuffer2 + 4);
    // LD_addr_A(wStringBuffer2 + 5);
    data.hl = 0;

    while(hl->bank != 0xff) {
    // loop:
        // LD_A_hl;
        // CP_A(0xff);
        // IF_Z goto done;
        // LD_addr_A(wStringBuffer2 + 3);  // bank
        data.bank = hl->bank;
        if(!bit_test(data.bank, 7)) {
            OpenSRAM(data.bank);
        }
        // PUSH_HL;
        // INC_HL;
    // addr 1
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint8_t* de2 = AbsGBToRAMAddr(hl->ptr1);
    // size
        // LD_A_hli;
        // LD_C_A;
        // LD_A_hli;
        // LD_B_A;
        uint16_t bc = hl->size;
    // addr 2
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        uint8_t* hl2 = AbsGBToRAMAddr(hl->ptr2);
        // CALL(aFunction100f3d);
        Function100f3d(&data, de2, hl2, bc);
    // next line
        CloseSRAM();
        // POP_HL;
        // LD_DE(7);
        // ADD_HL_DE;
        hl++;
        // goto loop;
    }

// done:
// recover the values into bc
    // LD_A_addr(wStringBuffer2 + 4);
    // LD_C_A;
    // LD_A_addr(wStringBuffer2 + 5);
    // LD_B_A;
    // RET;
    return data.hl;
}

void Function100f3d(Function100f02_Data_s* data, uint8_t* de, uint8_t* hl, uint16_t bc){
// parameter
    // LD_A_addr(wStringBuffer2);
    // CP_A(0x02);
    // IF_Z goto two;
    // CP_A(0x01);
    // IF_Z goto one;
    // CP_A(0x03);
    // IF_Z goto three;
    // RET;
    switch(data->c) {
    case 0x03: {
    // three:
    // what was once in de gets copied to hl,
    // modified by Function100f8d, and put back
    // into this backup
    // Copy data->de -> de
        // LD_A_addr(wStringBuffer2 + 1);
        // LD_L_A;
        // LD_A_addr(wStringBuffer2 + 2);
        // LD_H_A;
        uint8_t* hl2 = data->de;
        // CALL(aFunction100f8d);
        data->de = Function100f8d(data, de, hl2, bc);
        // LD_A_L;
        // LD_addr_A(wStringBuffer2 + 1);
        // LD_A_H;
        // LD_addr_A(wStringBuffer2 + 2);
        // RET;
    } return;

    case 0x02: {
    // two:
    // hl gets backed up to de, then
    // do the same as in .three
    // Copy data->de -> hl
        // LD_D_H;
        // LD_E_L;
        // LD_A_addr(wStringBuffer2 + 1);
        // LD_L_A;
        // LD_A_addr(wStringBuffer2 + 2);
        // LD_H_A;
        uint8_t* hl2 = data->de;
        // CALL(aFunction100f8d);
        data->de = Function100f8d(data, hl, hl2, bc);
        // LD_A_L;
        // LD_addr_A(wStringBuffer2 + 1);
        // LD_A_H;
        // LD_addr_A(wStringBuffer2 + 2);
        // RET;
    } return;

    case 0x01: {
    // one:
    // de gets copied to hl, then
    // load the backup into de,
    // finally run Function100f8d
    // and store the de result
    // Copy de -> data->de
        // LD_H_D;
        // LD_L_E;
        // LD_A_addr(wStringBuffer2 + 1);
        // LD_E_A;
        // LD_A_addr(wStringBuffer2 + 2);
        // LD_D_A;
        uint8_t* de2 = data->de;
        // CALL(aFunction100f8d);
        Function100f8d(data, de2, de, bc);
        // LD_A_E;
        // LD_addr_A(wStringBuffer2 + 1);
        // LD_A_D;
        // LD_addr_A(wStringBuffer2 + 2);
        data->de += bc;
        // RET;
        
    } return;
    }
}

uint8_t* Function100f8d(Function100f02_Data_s* data, uint8_t* de, uint8_t* hl, uint16_t bc){
    // PUSH_HL;
    // LD_A_addr(wStringBuffer2 + 4);
    // LD_L_A;
    // LD_A_addr(wStringBuffer2 + 5);
    // LD_H_A;
    // ADD_HL_BC;
    // LD_A_L;
    // LD_addr_A(wStringBuffer2 + 4);
    // LD_A_H;
    // LD_addr_A(wStringBuffer2 + 5);
    data->hl += bc;
    // POP_HL;
    // LD_A_addr(wStringBuffer2 + 3);
    // BIT_A(7);
    // RES_A(7);
    // IF_Z goto sram;
    // AND_A_A;
    // IF_NZ goto far_wram;
    // CALL(aCopyBytes);
    CopyBytes(de, hl, bc);
    // RET;
    return hl + bc;

// far_wram:
    // AND_A(0x7f);
    // CALL(aFarCopyWRAM);
    // RET;

// sram:
    // CALL(aOpenSRAM);
    // CALL(aCopyBytes);
    // CALL(aCloseSRAM);
    // RET;
}

const macro_100fc0_s Unknown_100fc0[] = {
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH', 'wOTPlayerName']
    //macro_100fc0 ['wPartyCount', '1 + PARTY_LENGTH + 1', 'wOTPartyCount']
    //macro_100fc0 ['wPlayerID', '2', 'wOTPlayerID']
    //macro_100fc0 ['wPartyMons', 'PARTYMON_STRUCT_LENGTH * PARTY_LENGTH', 'wOTPartyMons']
    //macro_100fc0 ['wPartyMonOTs', 'NAME_LENGTH * PARTY_LENGTH', 'wOTPartyMonOTs']
    //macro_100fc0 ['wPartyMonNicknames', 'MON_NAME_LENGTH * PARTY_LENGTH', 'wOTPartyMonNicknames']
    macro_100fc0(awPlayerName, NAME_LENGTH, awOTPlayerName),
    macro_100fc0(awPartyCount, 1 + PARTY_LENGTH + 1, awOTPartyCount),
    macro_100fc0(awPlayerID, 2, awOTPlayerID),
    macro_100fc0(awPartyMons, PARTYMON_STRUCT_LENGTH * PARTY_LENGTH, awOTPartyMons),
    macro_100fc0(awPartyMonOTs, NAME_LENGTH * PARTY_LENGTH, awOTPartyMonOTs),
    macro_100fc0(awPartyMonNicknames, MON_NAME_LENGTH * PARTY_LENGTH, awOTPartyMonNicknames),
    {(uint8_t)-1, 0, 0, 0},
    //db ['-1'];  // end
};

const macro_100fc0_s Unknown_100feb[] = {
    //macro_100fc0 ['sPartyMail', 'MAIL_STRUCT_LENGTH * PARTY_LENGTH']
    macro_100fc0(asPartyMail, MAIL_STRUCT_LENGTH * PARTY_LENGTH, 0),
    {(uint8_t)-1, 0, 0, 0},
    //db ['-1'];  // end
};

const macro_100fc0_s Unknown_100ff3[] = {
    //macro_100fc0 ['wdc41', '1']
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH']
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH']
    //macro_100fc0 ['wPlayerID', '2']
    //macro_100fc0 ['wSecretID', '2']
    //macro_100fc0 ['wPlayerGender', '1']
    //macro_100fc0 ['s4_a603', '8']
    //macro_100fc0 ['s4_a007', 'PARTYMON_STRUCT_LENGTH']
    macro_100fc0(awdc41, 1, 0),
    macro_100fc0(awPlayerName, NAME_LENGTH, 0),
    macro_100fc0(awPlayerName, NAME_LENGTH, 0),
    macro_100fc0(awPlayerID, 2, 0),
    macro_100fc0(awSecretID, 2, 0),
    macro_100fc0(awPlayerGender, 1, 0),
    macro_100fc0(as4_a603, 8, 0),
    macro_100fc0(as4_a007, PARTYMON_STRUCT_LENGTH, 0),
    {(uint8_t)-1, 0, 0, 0},
    //db ['-1'];  // end
};

void Unknown_10102c(void){
    //macro_100fc0 ['wOTPlayerName', 'NAME_LENGTH']
    //macro_100fc0 ['wOTPlayerID', '2']
    //macro_100fc0 ['wOTPartyMonNicknames', 'MON_NAME_LENGTH * PARTY_LENGTH']
    //macro_100fc0 ['wOTPartyMonOTs', 'NAME_LENGTH * PARTY_LENGTH']
    //macro_100fc0 ['wOTPartyMons', 'PARTYMON_STRUCT_LENGTH * PARTY_LENGTH']
    //db ['-1'];  // end

    return Function101050();
}

void Function101050(void){
    // CALL(aFunction10107d);
    Function10107d();
    // LD_A_addr(wOTPartyCount);
    // for(int rept = 0; rept < 2; rept++){  //  ???
    // LD_HL(wc608);
    // }
    // LD_BC(wc7bb - wc608);
    // CALL(aFunction1010de);
    uint16_t de = Function1010de(wram->wc608, wc7bb - wc608);
    // LD_HL(wc7bb);
    // LD_hl_E;
    wram->wc7bb[0] = LOW(de);
    // INC_HL;
    // LD_hl_D;
    wram->wc7bb[1] = HIGH(de);
    // LD_A(0x07);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as7_a000));
    // LD_HL(wc608);
    // LD_DE(0xa001);
    // LD_BC(wc7bd - wc608);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s7_a000 + 1), wram->wc608, wc7bd - wc608);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

static void Function10107d_CopyAllFromOT(uint8_t* de, const uint8_t* hl, uint16_t bc){
    // PUSH_HL;
    // LD_HL(0);
    // LD_A_addr(wOTPartyCount);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // CALL(aCopyBytes);
    CopyBytes(de, hl, wram->wOTPartyCount * bc);
    // RET;
}

// MobileComms_LoadOTData
void Function10107d(void){
    // XOR_A_A;
    // LD_HL(wc608);
    // LD_BC(wc7bd - wc608);
    // CALL(aByteFill);
    ByteFill(wram->wc608, wc7bd - wc608, 0x0);
    // LD_HL(wOTPlayerName);
    // LD_DE(wc608);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, wram->wOTPlayerName, NAME_LENGTH);
    // LD_HL(wd271);
    // LD_A_hli;
    // LD_addr_A(wc608 + 11);
    wram->wc608[11] = LOW(wram->wd271);
    // LD_A_hl;
    // LD_addr_A(wc608 + 12);
    wram->wc608[12] = HIGH(wram->wd271);
    // LD_HL(wOTPartyMonNicknames);
    // LD_DE(wc608 + 13);
    // LD_BC(NAME_LENGTH);
    // CALL(aFunction10107d_CopyAllFromOT);
    Function10107d_CopyAllFromOT(wram->wc608 + 13, wram->wOTPartyMonNickname[0], NAME_LENGTH);
    // LD_HL(wOTPartyMonOTs);
    // LD_DE(wOTClassName + 1);
    // LD_BC(NAME_LENGTH);
    // CALL(aFunction10107d_CopyAllFromOT);
    Function10107d_CopyAllFromOT(wram->wOTClassName + 1, wram->wOTPartyMonOT[0], NAME_LENGTH);
    // LD_HL(wOTPartyMon1Species);
    // LD_DE(0xc699);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aFunction10107d_CopyAllFromOT);
    Function10107d_CopyAllFromOT(wram->wc688 + 0x11, (const uint8_t*)wram->wOTPartyMon, PARTYMON_STRUCT_LENGTH);
    // LD_A(0x50);
    // LD_addr_A(wc7b9);
    wram->wc7b9[0] = 0x50;
    // LD_A(0x33);
    // LD_addr_A(wc7ba);
    wram->wc7ba[0] = 0x33;
    // RET;
}

// MobileComms_Checksum
uint16_t Function1010de(const uint8_t* hl, uint16_t bc){
    // PUSH_HL;
    // PUSH_BC;
    // LD_DE(0);
    uint16_t de = 0;

    do {
    // loop:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // ADD_A_E;
        // LD_E_A;
        // LD_A_D;
        // ADC_A(0);
        // LD_D_A;
        de += a;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // POP_BC;
    // POP_HL;
    // RET;
    return bc;
}

static species_t LoadSelectedPartiesForColosseum_GetNthSpecies(const uint8_t* de, const uint8_t* hl, uint8_t a) {
//  Preserves hl and de
//  Get the index of the Nth selection
    // PUSH_HL;
    // ADD_A_L;
    // LD_L_A;
    // LD_A_H;
    // ADC_A(0);
    // LD_H_A;
    // LD_A_hl;
    // POP_HL;
//  Get the corresponding species
    // PUSH_DE;
    // INC_DE;
    // ADD_A_E;
    // LD_E_A;
    // LD_A_D;
    // ADC_A(0);
    // LD_D_A;
    // LD_A_de;
    // POP_DE;
    // RET;
    return de[hl[a]];
}

static void LoadSelectedPartiesForColosseum_CopyThreeSpecies(uint8_t* de, const uint8_t* hl){
//  Load the 3 choices to the buffer
    // PUSH_DE;
    // LD_BC(wStringBuffer2 + NAME_LENGTH_JAPANESE);
    uint8_t* bc = wram->wStringBuffer2 + NAME_LENGTH;
    // XOR_A_A;
    uint8_t a = 0;

    do {
    // party_loop:
        // PUSH_AF;
        // CALL(aLoadSelectedPartiesForColosseum_GetNthSpecies);
        // LD_bc_A;
        // INC_BC;
        bc[a] = LoadSelectedPartiesForColosseum_GetNthSpecies(de + 1, hl, a);
        // POP_AF;
        // INC_A;
        // CP_A(3);
        // IF_NZ goto party_loop;
    } while(++a != 3);
    // POP_DE;
//  Copy the 3 choices to the party
    // LD_A(3);
    // LD_de_A;
    // INC_DE;
    *(de++) = 3;
    // LD_HL(wStringBuffer2 + NAME_LENGTH_JAPANESE);
    // LD_BC(3);
    // CALL(aCopyBytes);
    CopyBytes(de, wram->wStringBuffer2 + NAME_LENGTH, 3);
    // LD_A(0xff);
    // LD_de_A;
    de[3] = 0xff;
    // RET;
}

static void LoadSelectedPartiesForColosseum_CopyPartyStruct(struct PartyMon* de, const uint8_t* hl) {
// LD_BC(PARTYMON_STRUCT_LENGTH);
// goto ContinueCopy;
    uint16_t bc = PARTYMON_STRUCT_LENGTH;
    uint8_t* dst = wram->wc608;
    uint8_t a = 3;

    do {
        uint8_t n = *(hl++);
        CopyBytes(dst, de + n, bc);
        dst += bc;
    } while(--a != 0);

    CopyBytes(de, wram->wc608, bc * 3);
}

static void LoadSelectedPartiesForColosseum_CopyName(uint8_t* de, const uint8_t* hl) {
    // LD_BC(NAME_LENGTH);
    uint16_t bc = NAME_LENGTH;

// ContinueCopy:
    // Copy, via wc608...
    // LD_A(LOW(wc608));
    // LD_addr_A(wStringBuffer2);
    // LD_A(HIGH(wc608));
    // LD_addr_A(wStringBuffer2 + 1);
    uint8_t* dst = wram->wc608;
    // ... bc bytes...
    // LD_A_C;
    // LD_addr_A(wStringBuffer2 + 2);
    // LD_A_B;
    // LD_addr_A(wStringBuffer2 + 3);
    // ... to de...
    // LD_A_E;
    // LD_addr_A(wStringBuffer2 + 4);
    // LD_A_D;
    // LD_addr_A(wStringBuffer2 + 5);
    // ... 3 times.
    // LD_A(3);
    uint8_t a = 3;

    do {
    // big_copy_loop:
        // PUSH_AF;
        // LD_A_hli;
        uint8_t n = *(hl++);
        // PUSH_HL;
        // PUSH_AF;
        // CALL(aLoadSelectedPartiesForColosseum_GetDestinationAddress);
        // CALL(aLoadSelectedPartiesForColosseum_GetCopySize);
        // POP_AF;
        // CALL(aAddNTimes);
        // LD_A_addr(wStringBuffer2);
        // LD_E_A;
        // LD_A_addr(wStringBuffer2 + 1);
        // LD_D_A;
        // CALL(aCopyBytes);
        CopyBytes(dst, de + (bc * n), bc);
        // LD_A_E;
        // LD_addr_A(wStringBuffer2);
        // LD_A_D;
        // LD_addr_A(wStringBuffer2 + 1);
        dst += bc;
        // POP_HL;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto big_copy_loop;
    } while(--a != 0);
    // CALL(aLoadSelectedPartiesForColosseum_GetCopySize);
    // LD_A(3);
    // LD_HL(0);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    // CALL(aLoadSelectedPartiesForColosseum_GetDestinationAddress);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wc608);
    // CALL(aCopyBytes);
    CopyBytes(de, wram->wc608, bc * 3);
    // RET;


// GetDestinationAddress:
    // LD_A_addr(wStringBuffer2 + 4);
    // LD_L_A;
    // LD_A_addr(wStringBuffer2 + 5);
    // LD_H_A;
    // RET;

// GetCopySize:
    // LD_A_addr(wStringBuffer2 + 2);
    // LD_C_A;
    // LD_A_addr(wStringBuffer2 + 3);
    // LD_B_A;
    // RET;
}

void LoadSelectedPartiesForColosseum(void){
    // XOR_A_A;
    // LD_HL(wStringBuffer2);
    // LD_BC(9);
    // CALL(aByteFill);
    ByteFill(wram->wStringBuffer2, 9, 0);
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wPartyCount);
    // CALL(aLoadSelectedPartiesForColosseum_CopyThreeSpecies);
    LoadSelectedPartiesForColosseum_CopyThreeSpecies(&wram->wPartyCount, wram->wPlayerMonSelection);
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wPartyMon1Species);
    // CALL(aLoadSelectedPartiesForColosseum_CopyPartyStruct);
    LoadSelectedPartiesForColosseum_CopyPartyStruct(wram->wPartyMon, wram->wPlayerMonSelection);
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wPartyMonOTs);
    // CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LoadSelectedPartiesForColosseum_CopyName(wram->wPartyMonOT[0], wram->wPlayerMonSelection);
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wPartyMonNicknames);
    // CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LoadSelectedPartiesForColosseum_CopyName(wram->wPartyMonNickname[0], wram->wPlayerMonSelection);
    // LD_HL(wOTMonSelection);
    // LD_DE(wOTPartyCount);
    // CALL(aLoadSelectedPartiesForColosseum_CopyThreeSpecies);
    LoadSelectedPartiesForColosseum_CopyThreeSpecies(&wram->wOTPartyCount, wram->wOTMonSelection);
    // LD_HL(wOTMonSelection);
    // LD_DE(wOTPartyMon1Species);
    // CALL(aLoadSelectedPartiesForColosseum_CopyPartyStruct);
    LoadSelectedPartiesForColosseum_CopyPartyStruct(wram->wOTPartyMon, wram->wOTMonSelection);
    // LD_HL(wOTMonSelection);
    // LD_DE(wOTPartyMonOTs);
    // CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LoadSelectedPartiesForColosseum_CopyName(wram->wOTPartyMonOT[0], wram->wOTMonSelection);
    // LD_HL(wOTMonSelection);
    // LD_DE(wOTPartyMonNicknames);
    // CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LoadSelectedPartiesForColosseum_CopyName(wram->wOTPartyMonNickname[0], wram->wOTMonSelection);
    // RET;
}

void LoadSelectedPartyForBattleTower(void){
    // XOR_A_A;
    // LD_HL(wStringBuffer2);
    // LD_BC(9);
    // CALL(aByteFill);
    ByteFill(wram->wStringBuffer2, 9, 0);
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wPartyCount);
    // CALL(aLoadSelectedPartiesForColosseum_CopyThreeSpecies);
    LoadSelectedPartiesForColosseum_CopyThreeSpecies(&wram->wPartyCount, wram->wPlayerMonSelection);
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wPartyMon1Species);
    // CALL(aLoadSelectedPartiesForColosseum_CopyPartyStruct);
    LoadSelectedPartiesForColosseum_CopyPartyStruct(wram->wPartyMon, wram->wPlayerMonSelection);
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wPartyMonOTs);
    // CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LoadSelectedPartiesForColosseum_CopyName(wram->wPartyMonOT[0], wram->wPlayerMonSelection);
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wPartyMonNicknames);
    // CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LoadSelectedPartiesForColosseum_CopyName(wram->wPartyMonNickname[0], wram->wPlayerMonSelection);
    // RET;
}

// Mobile_StartLinkMode?
void Function1011f1(void){
    // LD_A(BANK(s4_a60c));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as4_a60c));
    // LD_A_addr(s4_a60c);
    // LD_addr_A(wdc41);
    wram->wdc41 = gb_read(s4_a60c);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_HL(wdc41);
    // RES_hl(4);
    bit_reset(wram->wdc41, 4);
    // LD_HL(wGameTimerPaused);
    // BIT_hl(GAME_TIMER_MOBILE_F);
    // IF_Z goto skip;
    if(bit_test(wram->wGameTimerPaused, GAME_TIMER_MOBILE_F)) {
        // LD_HL(wdc41);
        // SET_hl(4);
        bit_set(wram->wdc41, 4);
    }

// skip:
    // CALL(aFunction10209c);
    Function10209c();
    // XOR_A_A;
    // LD_addr_A(wdc5f);
    wram->wdc5f = 0;
    // LD_addr_A(wdc60);
    wram->wdc60 = 0;
    // LD_A(LINK_MOBILE);
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_MOBILE;
    // RET;
}

// Mobile_EndLinkMode?
void Function101220(void){
    // XOR_A_A;
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_NULL;
    // RET;
}

// Mobile_DoConnectionForMobileBattle
void Function101225(void){
    // LD_D(1);
    // LD_E(BANK(aJumptable_101297));
    // LD_BC(mJumptable_101297);
    // CALL(aFunction100000);
    uint8_t c = Function100000(1, BANK(aJumptable_101297), Jumptable_101297);
    // JR(mFunction10123d);
    return Function10123d(c);
}

// Mobile_DoConnectionForMobileTrade
void Function101231(void){
    // LD_D(2);
    // LD_E(BANK(aJumptable_101297));
    // LD_BC(mJumptable_101297);
    // CALL(aFunction100000);
    uint8_t c = Function100000(2, BANK(aJumptable_101297), Jumptable_101297);
    // JR(mFunction10123d);
    return Function10123d(c);
}

void Function10123d(uint8_t c){
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x0;
    // LD_A_C;
    // LD_HL(mJumptable_101247);
    // RST(aJumpTable);
    Jumptable_101247[c]();
    // RET;
}

// EndMobileComm_Jumptable
const mobile_comm_fn_t Jumptable_101247[] = {
    Function101251,
    Function10127d,
    Function10127c,
    Function10126c,
    Function101265,
};

void Function101251(void){
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aRefreshScreen);
    RefreshScreen();
    // LD_HL(mClosingLinkText);
    // CALL(aFunction1021e0);
    Function1021e0(ClosingLinkText);
    // CALL(aFunction1020ea);
    // RET_C ;
    if(Function1020ea())
        return;
    // CALL(aFunction102142);
    Function102142();
    // RET;
}

// MobileComms_PrintLinkTerminatedText
void Function101265(void){
    // LD_HL(mLinkTerminatedText);
    // CALL(aFunction1021e0);
    Function1021e0(LinkTerminatedText);
    // RET;
}

// MobileComms_PrintClosingLinkText
void Function10126c(void){
    // CALL(aUpdateSprites);
    UpdateSprites();
    // FARCALL(aScript_reloadmappart);
    Script_reloadmappart_Conv(&gCurScript);
    // LD_HL(mClosingLinkText);
    // CALL(aFunction1021e0);
    Function1021e0(ClosingLinkText);
    // RET;
}

void Function10127c(void){
    // RET;
}

void Function10127d(void){
    // RET;
}

void Function10127e(void){
    // LD_A_addr(wdc5f);
    // AND_A_A;
    // IF_Z goto zero;
    if(wram->wdc5f == 0) {
    // zero:
        // LD_C(0);
        wram->wMobileCommsJumptableIndex = 0;
    }
    // CP_A(1);
    // LD_C(0x27);
    // IF_Z goto load;
    else if(wram->wdc5f == 1) {
        wram->wMobileCommsJumptableIndex = 0x27;
    }
    // CP_A(2);
    // LD_C(0x37);
    // IF_Z goto load;
    else if(wram->wdc5f == 2) {
        wram->wMobileCommsJumptableIndex = 0x27;
    }
    else {
    // zero:
        // LD_C(0);
        wram->wMobileCommsJumptableIndex = 0;
    }

// load:
    // LD_A_C;
    // LD_addr_A(wMobileCommsJumptableIndex);
    // RET;
}

const mobile_comm_fn_t Jumptable_101297[] = {
    Function101a97,  // 00
    Function101ab4,  // 01
    Function101475,  // 02
    Function101b0f,  // 03
    Function101438,  // 04
    Function101b2b,  // 05
    Function101b59,  // 06
    Function101475,  // 07
    Function101b70,  // 08
    Function101438,  // 09
    Function101b8f,  // 0a
    Function101d7b,  // 0b
    Function101d95,  // 0c
    Function101475,  // 0d
    Function101db2,  // 0e
    Function101e4f,  // 0f
    Function101475,  // 10
    Function101e64,  // 11
    Function101e4f,  // 12
    Function101475,  // 13
    Function101e64,  // 14
    Function101d95,  // 15
    Function101475,  // 16
    Function101db2,  // 17
    Function101dd0,  // 18
    Function101de3,  // 19
    Function101e39,  // 1a
    Function101e09,  // 1b
    Function101e4f,  // 1c
    Function101475,  // 1d
    Function101e64,  // 1e
    Function101d95,  // 1f
    Function101475,  // 20
    Function101db2,  // 21
    Function101e09,  // 22
    Function101e31,  // 23
    Function101bc8,  // 24
    Function101438,  // 25
    Function101be5,  // 26
    Function101ac6,  // 27
    Function101ab4,  // 28
    Function101475,  // 29
    Function101c11,  // 2a
    Function1014f4,  // 2b
    Function101cc8,  // 2c
    Function1014e2,  // 2d
    Function1014e2,  // 2e
    Function101d10,  // 2f
    Function101d2a,  // 30
    Function101d2a,  // 31
    Function101507,  // 32
    Function10156d,  // 33
    Function101557,  // 34
    Function10158a,  // 35
    Function101c42,  // 36
    Function101aed,  // 37
    Function101ab4,  // 38
    Function101475,  // 39
    Function101c2b,  // 3a
    Function1014f4,  // 3b
    Function101cdf,  // 3c
    Function1014e2,  // 3d
    Function1014e2,  // 3e
    Function101d1e,  // 3f
    Function101d2a,  // 40
    Function101d2a,  // 41
    Function101507,  // 42
    Function10156d,  // 43
    Function101544,  // 44
    Function10158a,  // 45
    Function101c42,  // 46
    Function101c50,  // 47
    Function1014ce,  // 48
    Function101cf6,  // 49
    Function101826,  // 4a
    Function1017e4,  // 4b
    Function1017f1,  // 4c
    Function1018a8,  // 4d
    Function1018d6,  // 4e
    Function1017e4,  // 4f
    Function1017f1,  // 50
    Function1018e1,  // 51
    Function1015df,  // 52
    Function10167d,  // 53
    Function10168a,  // 54
    Function10162a,  // 55
    Function1015be,  // 56
    Function10167d,  // 57
    Function10168a,  // 58
    Function10161f,  // 59
    Function10159d,  // 5a
    Function10167d,  // 5b
    Function10168a,  // 5c
    Function101600,  // 5d
    Function101d03,  // 5e
    Function101d6b,  // 5f
    Function10159d,  // 60
    Function1014ce,  // 61
    Function10168e,  // 62
    Function101600,  // 63
    Function101913,  // 64
    Function10194b,  // 65
    v_SelectMonsForMobileBattle,  // 66
    Function1017e4,  // 67
    Function1017f5,  // 68
    v_StartMobileBattle,  // 69
    Function101537,  // 6a
    Function101571,  // 6b
    Function101c92,  // 6c
    Function10152a,  // 6d
    Function101571,  // 6e
    Function101a4f,  // 6f
    Function101cbc,  // 70
    Function101c62,  // 71
    Function101537,  // 72
    Function101571,  // 73
    Function101c92,  // 74
    Function10152a,  // 75
    Function101571,  // 76
    Function101ca0,  // 77
    Function101475,  // 78
    Function101cbc,  // 79
};

uint8_t Function10138b(void){
    // FARCALL(aFunction8adcc);
    bool carry = Function8adcc();
    // LD_C(0);
    uint8_t c = 0;
    // IF_C goto asm_101396;
    if(!carry) {
        // INC_C;
        c++;
    }

// asm_101396:
    // SLA_C;
    c <<= 1;
    // LD_A_addr(wcd2f);
    // AND_A_A;
    // IF_Z goto asm_10139f;
    if(wram->wcd2f != 0) {
        // INC_C;
        c++;
    }

// asm_10139f:
    // SLA_C;
    c <<= 1;
    // LD_A_addr(wcd21);
    // CP_A(0x01);
    // IF_Z goto asm_1013a9;
    if(wram->wcd21 != 0x1) {
        // INC_C;
        c++;
    }

// asm_1013a9:
    // RET;
    return c;
}

void Function1013aa(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aCall_ExitMenu);
    ExitMenu();
    // CALL(aReloadTilesetAndPalettes);
    ReloadTilesetAndPalettes();
    // FARCALL(aFunction106464);
    Function106464();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aFinishExitMenu);
    FinishExitMenu();
    // RET;
}

// Mobile_BackToDialingMenu?
void Function1013c0(void){
    // FARCALL(aBlankScreen);
    BlankScreen();
    // FARCALL(aStubbed_Function106462);
    Stubbed_Function106462();
    // FARCALL(aFunction106464);
    Function106464();
    // CALL(aFinishExitMenu);
    FinishExitMenu();
    // RET;
}

// Mobile_HDMATransferAttrmapAndTilemapToWRAMBank3
void Function1013d6(void){
    // FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    // RET;
    return HDMATransferAttrmapAndTilemapToWRAMBank3();
}

// Mobile_CGBOnly_CopyTilemapAtOnce
void Function1013dd(void){
    // CALL(aCGBOnly_CopyTilemapAtOnce);
    // RET;
    return CGBOnly_CopyTilemapAtOnce();
}

void Function1013e1(void){
//  //  unreferenced
    PUSH_DE;
    INC_DE;
    LD_B_A;
    LD_C(0);

asm_1013e6:
    INC_C;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    AND_A_A;
    IF_Z goto asm_1013f1;
    DEC_B;
    IF_NZ goto asm_1013e6;
    SCF;


asm_1013f1:
    POP_DE;
    LD_A_C;
    LD_de_A;
    RET;

}

void Function1013f5(uint8_t* de, const uint8_t* hl){
    // LD_A_hli;
    uint8_t c = *(hl++);
    // LD_de_A;
    // INC_DE;
    *(de++) = c;
    // LD_C_A;

    do {
    // asm_1013f9:
        // LD_A_hli;
        // LD_de_A;
        *(de++) = *(hl++);
        // INC_DE;
        // DEC_C;
        // IF_NZ goto asm_1013f9;
    } while(--c != 0);
    // RET;
}

void Function101400(void){
//  //  unreferenced
    LD_A_de;
    INC_DE;
    CP_A_hl;
    JR_NZ (masm_101416);
    INC_HL;

    // return Function101406();
}

bool Function101406(const uint8_t* de, const uint8_t* hl, uint8_t a){
    // LD_C_A;
    // LD_B(0);
    uint16_t bc = a;

    do {
    // asm_101409:
        // LD_A_de;
        // INC_DE;
        // CP_A_hl;
        // JR_NZ (masm_101416);
        if(*de != *hl)
            return true;
        // INC_HL;
        de++, hl++;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto asm_101409;
    } while(--bc != 0);
    // AND_A_A;
    // RET;
    return false;
}

// void asm_101416(void){
    // SCF;
    // RET;

// }

// Mobile_CheckSelectA
bool Function101418(void){
    // CALL(aGetJoypad);
    GetJoypad();
    // LDH_A_addr(hJoyDown);
    // AND_A(SELECT + A_BUTTON);
    // CP_A(SELECT + A_BUTTON);
    // IF_Z goto asm_101425;
    if((hram->hJoyDown & (SELECT + A_BUTTON)) == (SELECT + A_BUTTON)) {
    // asm_101425:
        // LD_A(0xf7);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf7;
        // SCF;
        // RET;
        return true;
    }
    // XOR_A_A;
    // RET;
    return false;
}

void Function10142c(uint8_t c){
    // LD_A(0x01);
    // LD_addr_A(wc305);
    wram->wc305 = 0x01;
    // FARCALL(aFunction115e18);
    Function115e18(c);
    // RET;
}

void Function101438(void){
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // LD_A_addr(wcd26);
    // LD_HL(mJumptable_101457);
    // RST(aJumpTable);
    switch(wram->wcd26) {
        default:
        case 0: Function10145b(); break;
        case 1: Function101467(); break;
    }
    // LD_A_addr(wcd26);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd26, 7))
        return;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;

}

void Jumptable_101457(void){
    //dw ['Function10145b'];
    //dw ['Function101467'];

    return Function10145b();
}

void Function10145b(void){
    // LD_A(0x3c);
    // LD_addr_A(wcd42);
    wram->wcd42 = 0x3c;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;

    return Function101467();
}

void Function101467(void){
    // LD_HL(wcd42);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcd42 != 0)
        return;
    // LD_A_addr(wcd26);
    // SET_A(7);
    // LD_addr_A(wcd26);
    bit_set(wram->wcd26, 7);
    // RET;
}

void Function101475(void){
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // LD_A_addr(wcd26);
    // LD_HL(mJumptable_101494);
    // RST(aJumpTable);
    switch(wram->wcd26) {
        default:
        case 0: Function10149a(); break;
        case 1: Function1014a6(); break;
        case 2: Function1014b7(); break;
    }
    // LD_A_addr(wcd26);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd26, 7))
        return;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;

}

void Jumptable_101494(void){
    //dw ['Function10149a'];
    //dw ['Function1014a6'];
    //dw ['Function1014b7'];

    // return Function10149a();
}

void Function10149a(void){
    // LD_A(0x28);
    // LD_addr_A(wcd42);
    wram->wcd42 = 0x28;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;

    return Function1014a6();
}

void Function1014a6(void){
    // LD_HL(wcd42);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcd42 != 0)
        return;
    // LD_A(0x50);
    // LD_addr_A(wcd42);
    wram->wcd42 = 0x50;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;

    return Function1014b7();
}

void Function1014b7(void){
    // CALL(aGetJoypad);
    GetJoypad();
    // LDH_A_addr(hJoyPressed);
    // AND_A(0x03);
    // IF_NZ goto asm_1014c5;
    if((hram->hJoyPressed & (A_BUTTON | B_BUTTON)) == 0) {
        // LD_HL(wcd42);
        // DEC_hl;
        // RET_NZ ;
        if(--wram->wcd42 != 0)
            return;
    }

// asm_1014c5:
    // LD_A_addr(wcd26);
    // SET_A(7);
    // LD_addr_A(wcd26);
    bit_set(wram->wcd26, 7);
    // RET;
}

void Function1014ce(void){
    // FARCALL(aFunction100720);
    Function100720();
    // FARCALL(aStartMobileInactivityTimer);
    StartMobileInactivityTimer();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function1014e2(void){
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function1014f4(void){
    // FARCALL(aEnableMobile);
    EnableMobile();
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101507(void){
    // LD_DE(wcd30);
    // LD_HL(0x40);
    // LD_BC(0x40);
    // LD_A(MOBILEAPI_01);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_01, &(mobile_api_data_s){.de = &wram->wcd30, .h = 0, .l = 0x40, .bc = 0x40});
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function10151d(void){
//  //  unreferenced
    LD_A(MOBILEAPI_1A);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10152a(void){
    // LD_A(MOBILEAPI_1B);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_1B, &(mobile_api_data_s){0});
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101537(void){
    // LD_A(MOBILEAPI_05);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_05, &(mobile_api_data_s){0});
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101544(void){
    // FARCALL(aStartMobileInactivityTimer);
    StartMobileInactivityTimer();
    // LD_A(MOBILEAPI_09);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_09, &(mobile_api_data_s){0});
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101557(void){
    // FARCALL(aStartMobileInactivityTimer);
    StartMobileInactivityTimer();
    // LD_HL(wcd53);
    // LD_A(MOBILEAPI_04);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_04, &(mobile_api_data_s){.hl = wram->wMobileOpponentBattleMessage});
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function10156d(void){
    // CALL(aFunction101418);
    // RET_C ;
    if(Function101418())
        return;

    return Function101571();
}

void Function101571(void){
    // FARCALL(aFunction10032e);
    u8_flag_s res = Function10032e();
    // RET_C ;
    // RET_Z ;
    if(res.flag || res.a == 0)
        return;
    // LD_A_E;
    // CP_A(0x01);
    // IF_Z goto asm_101582;
    if(res.a != 0x1) {
        // LD_addr_A(wcd2b);
        wram->wcd2b = res.a;
        // RET;
        return;
    }

// asm_101582:
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function10158a(void){
    // FARCALL(aIncrementMobileInactivityTimerBy1Frame);
    IncrementMobileInactivityTimerBy1Frame();
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // CP_A(0x0a);
    // JR_C (mFunction10156d);
    if(wram->wMobileInactivityTimerMinutes < 0x0a)
        return Function10156d();
    // LD_A(0xfb);
    // LD_addr_A(wcd2b);
    wram->wcd2b = 0xfb;
    // RET;
}

// MobileComms_LoadAndStagePartyDataForTransfer
void Function10159d(void){
    // LD_DE(wc608);
    // FARCALL(aFunction100edf);
    uint16_t bc = Function100edf(wram->wc608);
    // LD_DE(wc608);
    // LD_A(0x05);
    // LD_HL(w5_d800);
    // CALL(aFunction10174c);
    Function10174c(wram->wc608, 0x05, wram->w5_d800, bc);
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// MobileComms_LoadAndStageMailDataForTransfer
void Function1015be(void){
    // LD_DE(wc608);
    // FARCALL(aFunction100eed);
    uint16_t bc = Function100eed(wram->wc608);
    // LD_DE(wc608);
    // LD_A(0x05);
    // LD_HL(w5_d800);
    // CALL(aFunction10174c);
    Function10174c(wram->wc608, 0x05, wram->w5_d800, bc);
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// MobileComms_LoadAndStageOTDataForTransfer
void Function1015df(void){
    // LD_DE(wc608);
    // FARCALL(aFunction100ef4);
    uint16_t bc = Function100ef4(wram->wc608);
    // LD_DE(wc608);
    // LD_A(0x05);
    // LD_HL(w5_d800);
    // CALL(aFunction10174c);
    Function10174c(wram->wc608, 0x05, wram->w5_d800, bc);
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// MobileComms_LoadOTDataFromTransfer
void Function101600(void){
    // LD_HL(w5_d800);
    // LD_DE(wc608);
    // LD_BC(0x1e0);
    // LD_A(0x05);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wc608, wram->w5_d800, 0x1e0);
    // LD_DE(wc608);
    // FARCALL(aFunction100ee6);
    Function100ee6(wram->wc608);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// MobileComms_TransferFromW5D800ToW5DA00
void Function10161f(void){
    // CALL(aFunction101649);
    Function101649();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// MobileComms_TransferFromW5D800ToW5DC00
void Function10162a(void){
    // CALL(aFunction101663);
    Function101663();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void MobileCopyTransferData(const void* hl){
    // LD_DE(wMobileTransferData);
    // LD_BC(0x1e0);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wMobileTransferData, hl, 0x1e0);
    // RET;
}

void MobileCopyTransferData2(void* de){
    // LD_HL(wMobileTransferData);
    // LD_BC(0x1e0);
    // CALL(aFarCopyWRAM);
    CopyBytes(de, wram->wMobileTransferData, 0x1e0);
    // RET;
}

// TransferFromW5D800ToW5DA00
void Function101649(void){
    // LD_A(BANK(w5_d800));
    // LD_HL(w5_d800);
    // CALL(aMobileCopyTransferData);
    MobileCopyTransferData(wram->w5_d800);
    // LD_A(BANK(w5_da00));
    // LD_DE(w5_da00);
    // CALL(aMobileCopyTransferData2);
    MobileCopyTransferData2(wram->w5_da00);
    // RET;
}

void Function10165a(void){
    // LD_A(BANK(w5_da00));
    // LD_HL(w5_da00);
    // CALL(aMobileCopyTransferData);
    MobileCopyTransferData(wram->w5_da00);
    // RET;
}

// TransferFromW5D800ToW5DC00
void Function101663(void){
    // LD_A(BANK(w5_dc00));
    // LD_HL(w5_d800);
    // CALL(aMobileCopyTransferData);
    MobileCopyTransferData(wram->w5_d800);
    // LD_A(BANK(w5_dc00));
    // LD_DE(w5_dc00);
    // CALL(aMobileCopyTransferData2);
    MobileCopyTransferData2(wram->w5_dc00);
    // RET;
}

void Function101674(void){
//  //  unreferenced
    LD_A(BANK(w5_dc00));
    LD_HL(w5_dc00);
    CALL(aMobileCopyTransferData);
    RET;

}

// MobileComms_ResetBattleDataTransferJumptableIndex
void Function10167d(void){
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// MobileComms_CheckSelectAOrCheckTimeoutOrBattleDataTransfer
void Function10168a(void){
    // CALL(aFunction101418);
    // RET_C ;
    if(Function101418())
        return;

    return Function10168e();
}

// MobileComms_CheckTimeoutOrBattleDataTransfer
void Function10168e(void){
    // LD_B(0);
    // LD_C(0x01);
    // FARCALL(aFunction10079c);
    // RET_C ;
    if(Function10079c(0, 0x01))
        return;
    // LD_C(0x01);
    // LD_B(0x03);
    // FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    // RET_C ;
    if(AdvanceMobileInactivityTimerAndCheckExpired(0x01, 0x03))
        return;
    // LD_A_addr(wcd26);
    // LD_HL(mJumptable_1016c3);
    Jumptable_1016c3(wram->wcd26);
    // RST(aJumpTable);
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // LD_A_addr(wcd26);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd26, 7))
        return;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// P2PBattleDataTransfer?
void Jumptable_1016c3(uint8_t a){
    switch(a) {
        case 0: Function1016cf(); break;
        case 1: Function1016de(); break;
        case 2: Function1016f8(); break;
        case 3: Function101705(); break;
        case 4: Function101719(); break;
        case 5: Function101724(); break;
    }
}

// P2PBattleDataTransfer_InitTransferBuffer
void Function1016cf(void){
    // LD_HL(wcd3a);
    // INC_hl;
    wram->wcd3a++;
    // CALL(aFunction10176f);
    Function10176f();
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;
    // RET;
}

// P2PBattleDataTransfer_StageTransferData
void Function1016de(void){
    // CALL(aFunction10177b);
    // IF_NC goto asm_1016eb;
    if(Function10177b()) {
        // LD_A_addr(wcd26);
        // INC_A;
        // LD_addr_A(wcd26);
        wram->wcd26++;
        // RET;
        return;
    }

// asm_1016eb:
    // LD_A(0xff);
    // LD_addr_A(wcd39);
    wram->wcd39 = 0xff;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;
    // RET;
}

// P2PBattleDataTransfer_ResetP2PJumptableIndex
void Function1016f8(void){
    // LD_A(0);
    // LD_addr_A(wcd27);
    wram->wcd27 = 0;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;
    // RET;
}

// P2PBattleDataTransfer_DoP2PTransfer
void Function101705(void){
    // FARCALL(aFunction100382);
    Function100382();
    // LD_A_addr(wcd27);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd27, 7))
        return;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;
    // RET;
}

void Function101719(void){
    // CALL(aFunction1017c7);
    Function1017c7();
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;
    // RET;
}

void Function101724(void){
    // LD_A_addr(wcd39);
    // CP_A(0xff);
    // IF_Z goto asm_101731;
    if(wram->wcd39 == 0xff) { // No more data to transfer?
    // asm_101731:
        // LD_A_addr(wcd26);
        // SET_A(7);
        // LD_addr_A(wcd26);
        bit_set(wram->wcd26, 7);
        // RET;
    }
    else {
        // LD_A(0);
        // LD_addr_A(wcd26);
        wram->wcd26 = 0;
        // RET;
    }
}

const uint8_t P2PTransferChunkSize = 0x50; // Unknown_10173a

// returns hl + (a * 80)
uint8_t* Function10173b(uint8_t* hl, uint8_t a){
    // PUSH_BC;
    // PUSH_AF;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(mUnknown_10173a);
    // LD_C_A;
    // LD_B(0);
    // POP_AF;
    // CALL(aAddNTimes);
    // POP_BC;
    // RET;
    return hl + (P2PTransferChunkSize * a);
}

void Function10174c(uint8_t* de, uint8_t a, uint8_t* hl, uint16_t bc){
    // LD_addr_A(wcd3d);
    wram->wcd3d[0] = a;
    // LD_A_L;
    // LD_addr_A(wcd3e);
    // LD_A_H;
    // LD_addr_A(wcd3f);
    gMobile_wcd3e = hl;
    // LD_A_E;
    // LD_addr_A(wcd3b);
    // LD_A_D;
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    gMobile_wcd3b = de;
    // LD_A_C;
    // LD_addr_A(wcd40);
    wram->wcd40 = LOW(bc);
    // LD_A_B;
    // LD_addr_A(wcd41);
    wram->wcd41 = HIGH(bc);
    // XOR_A_A;
    // LD_addr_A(wcd39);
    wram->wcd39 = 0x0;
    // LD_addr_A(wcd3a);
    wram->wcd3a = 0x0;
    // RET;
}

// FillTransferBufferwith0x11
void Function10176f(void){
    // LD_HL(wccb4);
    // LD_BC(0x54);
    // LD_A(0x11);
    // CALL(aByteFill);
    ByteFill(&wram->wccb4, 0x54, 0x11);
    // RET;
}

bool Function10177b(void){
    // LD_A_addr(mUnknown_10173a);
    // LD_C_A;
    // LD_B(0);
    uint16_t bc = P2PTransferChunkSize;
    // LD_A_addr(wcd3a);
    // LD_HL(0);
    // CALL(aAddNTimes);
    // LD_E_L;
    // LD_D_H;
    uint16_t de = bc * wram->wcd3a;
    // LD_HL(wcd40);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint16_t hl = wram->wcd40 | (wram->wcd41 << 8);
    // LD_A_L;
    // SUB_A_E;
    // LD_L_A;
    // LD_A_H;
    // SBC_A_D;
    // LD_H_A;
    // IF_C goto asm_1017a0;
    if(hl >= de) {
        // ADD_HL_BC;
        hl = (hl - de) + bc;
        // CALL(aFunction1017b0);
        Function1017b0(bc);
        // SCF;
        // RET;
        return true;
    }

// asm_1017a0:
    // LD_A(0xff);
    // LD_addr_A(wcd39);
    wram->wcd39 = 0xff;
    // ADD_HL_BC;
    hl = (hl - de) + bc;
    // LD_A_H;
    // OR_A_L;
    // RET_Z ;
    if(hl == 0)
        return false;
    // LD_C_L;
    // LD_B_H;
    // CALL(aFunction1017b0);
    Function1017b0(hl);
    // XOR_A_A;
    // RET;
    return false;
}

// ReadTransferChunk?
void Function1017b0(uint16_t bc){
    // LD_A_C;
    // LD_addr_A(wccb4);
    wram->wccb4 = LOW(bc);
    // PUSH_BC;
    // LD_A_addr(wcd3a);
    // DEC_A;
    // LD_HL(wcd3b);
    // CALL(aFunction10173b);
    uint8_t* hl = Function10173b(gMobile_wcd3b, wram->wcd3a - 1);
    // POP_BC;
    // LD_DE(wccb5);
    // CALL(aCopyBytes);
    CopyBytes(wram->wccb5, hl, bc);
    // RET;
}

// WriteTransferChunk?
void Function1017c7(void){
    // LD_A_addr(wcc60);
    // LD_C_A;
    // LD_B(0);
    uint16_t bc = wram->wcc60;
    // LD_A_addr(wcd3a);
    // DEC_A;
    // LD_HL(wcd3e);
    // CALL(aFunction10173b);
    // LD_E_L;
    // LD_D_H;
    uint8_t* de = Function10173b(gMobile_wcd3e, wram->wcd3a - 1);
    // LD_HL(wcc61);
    // LD_A_addr(wcd3d);
    // CALL(aFarCopyWRAM);
    CopyBytes(de, wram->wcc61, bc);
    // AND_A_A;
    // RET;
}

// MobileComms_ResetP2PJumptableIndex
void Function1017e4(void){
    // LD_A(0);
    // LD_addr_A(wcd27);
    wram->wcd27 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// MobileComms_CheckSelectAOrCheckTimeoutOrP2PTransfer
void Function1017f1(void){
    // CALL(aFunction101418);
    // RET_C ;
    if(Function101418())
        return;

    return Function1017f5();
}

// MobileComms_CheckTimeoutOrP2PTransfer
void Function1017f5(void){
    // LD_B(0);
    // LD_C(0x01);
    // FARCALL(aFunction10079c);
    // RET_C ;
    if(Function10079c(0, 0x01))
        return;
    // LD_C(0x01);
    // LD_B(0x03);
    // FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    // RET_C ;
    if(AdvanceMobileInactivityTimerAndCheckExpired(0x01, 0x03))
        return;
    // FARCALL(aFunction100382);
    Function100382();
    // LD_A_addr(wcd27);
    // BIT_A(7);
    // IF_NZ goto next;
    if(bit_test(wram->wcd27, 7)) {
    // next:
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }
    else {
        // LD_HL(wcd29);
        // SET_hl(6);
        bit_set(wram->wcd29, 6);
        // RET;
        return;
    }
}

// CopyP2PSelectedPlayerOption?
void Function101826(void){
    // LD_A_addr(wcd21);
    // CP_A(0x02);
    // IF_Z goto asm_101833;
    if(wram->wcd21 == 2) {
    // asm_101833:
        // LD_HL(mUnknown_10186f);
        // LD_DE(wccb4);
        // CALL(aFunction1013f5);
        Function1013f5(&wram->wccb4, (const uint8_t*)Unknown_10186f);
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }
    // CP_A(0x01);
    // IF_Z goto asm_101844;
    else if(wram->wcd21 == 1) {
    // asm_101844:
        // FARCALL(aFunction103654);
        // LD_A_C;
        uint8_t c = Function103654();
        const uint8_t* hl = (const uint8_t*)((c == 1)? Unknown_101882: Unknown_101895);
        // LD_HL(mUnknown_101882);
        // CP_A(0x01);
        // IF_Z goto asm_10185b;
        // LD_HL(mUnknown_101895);
        // CP_A(0x02);
        // IF_Z goto asm_10185b;
        if(c == 1 || c == 2) {
        // asm_10185b:
            // LD_DE(wccb4);
            // CALL(aFunction1013f5);
            Function1013f5(&wram->wccb4, hl);
            // LD_A_addr(wMobileCommsJumptableIndex);
            // INC_A;
            // LD_addr_A(wMobileCommsJumptableIndex);
            wram->wMobileCommsJumptableIndex++;
            // RET;
            return;
        }
        // goto asm_101869;
    }
    // goto asm_101869;
// asm_101869:
    // LD_A(0xfe);
    // LD_addr_A(wcd2b);
    wram->wcd2b = 0xfe;
    // RET;
}

// pushc
// setcharmap ascii
const char Unknown_10186f[] =
    //db ['.end - @'];
    "\x11"
    //db ['0x19', '0x73', '0x09', '0x13', '"trade_crystal"'];
    "\x19\x73\x09\x13""trade_crystal";

// end    db:
// 0

const char Unknown_101882[] =
    //db ['.end - @'];
    "\x11"
    //db ['0x19', '0x67', '0x10', '0x01', '"free__crystal"'];
    "\x19\x67\x10\x01""free__crystal";

// end    db:
// 0

const char Unknown_101895[] =
    //db ['.end - @'];
    "\x11"
    //db ['0x19', '0x67', '0x10', '0x01', '"limit_crystal"'];
    "\x19\x67\x10\x01""limit_crystal";

// end    db:
// 0

// popc

// MobileComms_CheckOtherPlayersSelection
void Function1018a8(void){
    // LD_HL(wccb5);
    // LD_DE(wcc61);
    // LD_A(0x04);
    // CALL(aFunction101406);
    // IF_C goto asm_1018d0;
    if(Function101406(wram->wcc61, wram->wccb5, 0x4)) {
    // asm_1018d0:
        // LD_A(0xf5);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf5;
        // RET;
        return;
    }
    // LD_HL(wccb9);
    // LD_DE(wcc65);
    // LD_A(0x06);
    // CALL(aFunction101406);
    // IF_C goto asm_1018ca;
    if(Function101406(wram->wcc65, wram->wccb9, 0x6)) {
    // asm_1018ca:
        // LD_A(0xf6);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf6;
        // RET;
        return;
    }
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// MobileComms_GenerateLinkBattleRNs
void Function1018d6(void){
    // CALL(aFunction1018ec);
    Function1018ec();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;

}

// MobileComms_CopyLinkBattleRNs
void Function1018e1(void){
    // CALL(aFunction1018fb);
    Function1018fb();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;

}

// Mobile_GenerateLinkBattleRNs?
void Function1018ec(void){
    // LD_A(0x0a);
    // LD_HL(wccb4);
    uint8_t* hl = wram->wccb5;
    // LD_hli_A;
    // LD_C_A;
    uint8_t c = 10;
    wram->wccb4 = c;

    do {
    // asm_1018f3:
        // CALL(aRandom);
        // LD_hli_A;
        *(hl++) = Random();
        // DEC_C;
        // IF_NZ goto asm_1018f3;
    } while(--c != 0);
    // RET;
}

// Mobile_CopyLinkBattleRNs?
void Function1018fb(void){
    // LD_A_addr(wcd2f);
    // AND_A_A;
    // IF_Z goto asm_101906;
    // LD_HL(wcc61);
    // goto asm_101909;


// asm_101906:
    // LD_HL(wccb5);
    const uint8_t* hl = (wram->wcd2f == 0)? wram->wccb5: wram->wcc61;

// asm_101909:
    // LD_DE(wLinkBattleRNs);
    // LD_BC(10);
    // CALL(aCopyBytes);
    CopyBytes(wram->wLinkBattleRNs, hl, 10);
    // RET;
}

void Function101913(void){
    // LD_HL(wcd2a);
    // SET_hl(0);
    bit_set(wram->wcd2a, 0);
    // XOR_A_A;
    // LD_addr_A(wc30d);
    wram->wc30d = 0x0;
    // LD_HL(wcd29);
    // RES_hl(4);
    bit_reset(wram->wcd29, 4);
    // XOR_A_A;
    // LD_addr_A(wc305);
    wram->wc305 = 0x0;
    // LD_HL(wcd29);
    // RES_hl(7);
    bit_reset(wram->wcd29, 7);
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // LD_A_addr(wcd21);
    switch(wram->wcd21) {
    // CP_A(0x01);
    // IF_Z goto asm_10193f;
    case 0x01:
    // asm_10193f:
        // LD_A(0x66);
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex = 0x66;
        // RET;
        return;
    // CP_A(0x02);
    // IF_Z goto asm_101945;
    case 0x02:
    // asm_101945:
        // LD_A(0x65);
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex = 0x65;
        // RET;
        return;
    default:
        // LD_A(0x71);
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex = 0x71;
        // RET;
        return;
    }
}

void Function10194b(void){
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // CALL(aClearSprites);
    ClearSprites();
    // FARCALL(aFunction1021f9);
    Function1021f9();
    // LD_HL(wcd29);
    // BIT_hl(3);
    // IF_NZ goto asm_101967;
    if(!bit_test(wram->wcd29, 3)) {
        // CALL(aFunction1013c0);
        Function1013c0();
        // LD_A(0x71);
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex = 0x71;
        // RET;
    }
    else {
    // asm_101967:
        // LD_A(0x60);
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex = 0x60;
        // RET;
    }
}

void v_SelectMonsForMobileBattle(void){
    // FARCALL(aBlankScreen);
    BlankScreen();
    // FARCALL(aMobile_CommunicationStandby);
    Mobile_CommunicationStandby();
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_HL(wcd2a);
    // SET_hl(6);
    bit_set(wram->wcd2a, 6);
    // LD_A(0x06);
    // LD_addr_A(wccb4);
    wram->wccb4 = 0x06;
    // LD_HL(wPlayerMonSelection);
    // LD_DE(wccb5);
    // LD_BC(3);
    // CALL(aCopyBytes);
    CopyBytes(wram->wccb5, wram->wPlayerMonSelection, sizeof(wram->wPlayerMonSelection));
    // LD_HL(wcd6c);
    // LD_A_hli;
    // LD_addr_A(wccb8);
    wram->wccb8[0] = wram->wcd6c;
    // LD_A_hli;
    // LD_addr_A(wccb9);
    wram->wccb9[0] = wram->wcd6d;
    // LD_A_hl;
    // LD_addr_A(wccba);
    wram->wccba[0] = wram->wcd6e;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

static void v_StartMobileBattle_CopyOTDetails(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(5);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 5);

    // LD_BC(w5_dc0d);
    // LD_DE(w5_dc11);
    // FARCALL(aGetMobileOTTrainerClass);
    wram->wOtherTrainerClass = GetMobileOTTrainerClass(wram->w5_dc11, wram->w5_dc0d);
    wram->wOtherTrainerID = 1;

    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);

    // LD_A_C;
    // LD_addr_A(wOtherTrainerClass);
    // LD_HL(wOTPlayerName);
    // LD_DE(wOTClassName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wOTClassName, wram->wOTPlayerName, NAME_LENGTH);
    // LD_A_addr(wcd2f);
    // AND_A_A;
    // LD_A(USING_INTERNAL_CLOCK);
    // IF_Z goto got_link_player_number;
    // LD_A(USING_EXTERNAL_CLOCK);

// got_link_player_number:
    // LDH_addr_A(hSerialConnectionStatus);
    hram->hSerialConnectionStatus = (wram->wcd2f == 0)? USING_INTERNAL_CLOCK: USING_EXTERNAL_CLOCK;
    // RET;
}

void v_StartMobileBattle(void){
    // CALL(aCopyOtherPlayersBattleMonSelection);
    CopyOtherPlayersBattleMonSelection();
    // FARCALL(aFunction100754);
    Function100754();
    // XOR_A_A;
    // LD_addr_A(wdc5f);
    wram->wdc5f = 0;
    // LD_addr_A(wdc60);
    wram->wdc60 = 0;
    // FARCALL(aBlankScreen);
    BlankScreen();
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // FARCALL(aFunction100846);
    Function100846();
    // LD_C(120);
    // CALL(aDelayFrames);
    DelayFrames(120);
    // FARCALL(aClearTilemap);
    ClearTilemap();
    // CALL(av_StartMobileBattle_CopyOTDetails);
    v_StartMobileBattle_CopyOTDetails();
    // CALL(aStartMobileBattle);
    StartMobileBattle();
    // LD_A_addr(wcd2b);
    // CP_A(0xfc);
    // IF_NZ goto asm_1019e6;
    if(wram->wcd2b == 0xfc) {
        // XOR_A_A;
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0;
    }

// asm_1019e6:
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void StartMobileBattle(void){
// force stereo and fast text speed
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // AND_A((1 << STEREO));
    // OR_A(1);  // 1 frame per character i.e. fast text
    // LD_hl_A;
    wram->wOptions = (options & (1 << STEREO)) | 1;
    // LD_A(1);
    // LD_addr_A(wDisableTextAcceleration);
    wram->wDisableTextAcceleration = 1;
    // FARCALL(aBattleIntro);
    BattleIntro();
    // FARCALL(aDoBattle);
    DoBattle();
    // FARCALL(aShowLinkBattleParticipantsAfterEnd);
    ShowLinkBattleParticipantsAfterEnd();
    // XOR_A_A;
    // LD_addr_A(wDisableTextAcceleration);
    wram->wDisableTextAcceleration = 0x0;
    // LD_A(CONNECTION_NOT_ESTABLISHED);
    // LDH_addr_A(hSerialConnectionStatus);
    hram->hSerialConnectionStatus = CONNECTION_NOT_ESTABLISHED;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;
}

// Mobile_DisplayLinkBattleResult
void Function101a4f(void){
    // LD_A(1);
    // LD_addr_A(wDisableTextAcceleration);
    wram->wDisableTextAcceleration = 1;
    // FARCALL(aDisplayLinkBattleResult);
    DisplayLinkBattleResult();
    // XOR_A_A;
    // LD_addr_A(wDisableTextAcceleration);
    wram->wDisableTextAcceleration = 0;
    // FARCALL(aCleanUpBattleRAM);
    CleanUpBattleRAM();
    // FARCALL(aLoadPokemonData);
    LoadPokemonData();
    // CALL(aFunction1013c0);
    Function1013c0();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void CopyOtherPlayersBattleMonSelection(void){
    // LD_HL(wcc61);
    // LD_DE(wOTMonSelection);
    // LD_BC(3);
    // CALL(aCopyBytes);
    CopyBytes(wram->wOTMonSelection, wram->wcc61, 3);
    // LD_DE(wcc64);
    // FARCALL(aFunction100772);
    Function100772(wram->wcc64);
    // FARCALL(aFunction101050);
    Function101050();
    // FARCALL(aLoadSelectedPartiesForColosseum);
    LoadSelectedPartiesForColosseum();
    // RET;
}

void Function101a97(void){
    // FARCALL(aFunction115d99);
    Function115d99();
    // LD_HL(wcd29);
    // SET_hl(7);
    bit_set(wram->wcd29, 7);
    // LD_C(0x02);
    // CALL(aFunction10142c);
    Function10142c(0x02);
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101ab4(void){
    // LD_E(0x01);
    // CALL(aFunction101ee4);
    Function101ee4(0x01); // Communicate with a friend!
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101ac6(void){
    // FARCALL(aFunction115d99);
    Function115d99();
    // LD_HL(wcd29);
    // SET_hl(7);
    bit_set(wram->wcd29, 7);
    // LD_C(0x02);
    // CALL(aFunction10142c);
    Function10142c(0x02);
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // XOR_A_A;
    // LD_addr_A(wcd2f);
    wram->wcd2f = 0x00;
    // LD_DE(wdc42);
    // CALL(aFunction102068);
    Function102068(wram->wdc42);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101aed(void){
    // FARCALL(aFunction115d99);
    Function115d99();
    // LD_HL(wcd29);
    // SET_hl(7);
    bit_set(wram->wcd29, 7);
    // LD_C(0x02);
    // CALL(aFunction10142c);
    Function10142c(0x02);
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // LD_A(0x01);
    // LD_addr_A(wcd2f);
    wram->wcd2f = 0x01;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101b0f(void){
    // LD_C(0);
    // CALL(aFunction10142c);
    Function10142c(0);
    // LD_E(0x03);
    // CALL(aFunction101ee4);
    Function101ee4(0x03); // Is the adapter ready?
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // RET;
}

void Function101b2b(void){
    // FARCALL(aFunction100579);
    Function100579();
    // LD_HL(wcd29);
    // SET_hl(2);
    bit_set(wram->wcd29, 2);
    // LD_A_addr(wcd26);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd26, 7))
        return;
    // CALL(aFunction1013dd);
    Function1013dd();
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMenuCursorY);
    // CP_A(0x01);
    // IF_Z goto asm_101b51;
    if(wram->wMenuCursorY != 0x01) {
        // LD_A(0x02);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0x02;
        // RET;
        return;
    }

// asm_101b51:
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101b59(void){
    // LD_C(0x02);
    // CALL(aFunction10142c);
    Function10142c(0x02);
    // LD_E(0x02);
    // CALL(aFunction101ee4);
    Function101ee4(0x02); // Caller will be charged.
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101b70(void){
    // LD_C(0x02);
    // CALL(aFunction10142c);
    Function10142c(0x02);
    // LD_E(0x04);
    // CALL(aFunction101ee4);
    Function101ee4(0x04); // Want to call your friend?
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // CALL(aUpdateSprites);
    UpdateSprites();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // RET;
}

void Function101b8f(void){
    // FARCALL(aFunction1005c3);
    Function1005c3();
    // LD_HL(wcd29);
    // SET_hl(2);
    bit_set(wram->wcd29, 2);
    // LD_A_addr(wcd26);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd26, 7))
        return;
    // CALL(aFunction1013dd);
    Function1013dd();
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMenuCursorY);
    // CP_A(0x01);
    // IF_Z goto asm_101bbc;
    if(wram->wMenuCursorY != 0x1) {
        // LD_A(0x01);
        // LD_addr_A(wcd2f);
        wram->wcd2f = 1;
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }
    else {
    // asm_101bbc:
        // XOR_A_A;
        // LD_addr_A(wcd2f);
        wram->wcd2f = 0;
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }
}

void Function101bc8(void){
    // LD_C(0x02);
    // CALL(aFunction10142c);
    Function10142c(0x02);
    // LD_E(0x08);
    // CALL(aFunction101ee4);
    Function101ee4(0x08); // Call this no.?
    // CALL(aFunction102048);
    Function102048();
    // CALL(aFunction1013dd);
    Function1013dd();
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101be5(void){
    // FARCALL(aFunction100579);
    Function100579();
    // LD_HL(wcd29);
    // SET_hl(2);
    bit_set(wram->wcd29, 2);
    // LD_A_addr(wcd26);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd26, 7))
        return;
    // CALL(aFunction1013dd);
    Function1013dd();
    // LD_A(0);
    // LD_addr_A(wcd26);
    // LD_A_addr(wMenuCursorY);
    // CP_A(0x01);
    // IF_NZ goto asm_101c0b;
    if(wram->wMenuCursorY != 1) {
    // asm_101c0b:
        // LD_A(0x02);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0x2;
        // RET;
    }
    else {
        // LD_A(0x2a);
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex = 0x2a;
        // RET;
    }
}

void Function101c11(void){
    // LD_A(0x01);
    // LD_addr_A(wdc5f);
    wram->wdc5f = 0x01;
    // LD_E(0x09);
    // CALL(aFunction101ee4);
    Function101ee4(0x09); // Use the card folder?
    // CALL(aFunction102048);
    Function102048();
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101c2b(void){
    // LD_A(0x02);
    // LD_addr_A(wdc5f);
    wram->wdc5f = 0x02;
    // LD_E(0x07);
    // CALL(aFunction101ee4);
    Function101ee4(0x07); // Waiting for call
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101c42(void){
    // LD_HL(wcd2a);
    // SET_hl(1);
    bit_set(wram->wcd2a, 1);
    // CALL(aFunction100665);
    Function100665();
    // LD_A(0x47);
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex = 0x47;
    // RET;
}

void Function101c50(void){
    // LD_E(0x0a);
    // CALL(aFunction101ee4);
    Function101ee4(0x0a); // Call connected
    // LD_HL(wcd29);
    // SET_hl(2);
    bit_set(wram->wcd29, 2);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101c62(void){
    // FARCALL(aFunction115d99);
    Function115d99();
    // LD_HL(wcd29);
    // SET_hl(7);
    bit_set(wram->wcd29, 7);
    // LD_C(0x01);
    // CALL(aFunction10142c);
    Function10142c(0x1);
    // XOR_A_A;
    // LD_addr_A(wc30d);
    wram->wc30d = 0x0;
    // LD_HL(wcd29);
    // RES_hl(4);
    bit_reset(wram->wcd29, 4);
    // LD_E(0x0b);
    // CALL(aFunction101ee4);
    Function101ee4(0x0b); // "Choose the settings"
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // RET;
}

void Function101c92(void){
    // FARCALL(aFunction100675);
    Function100675();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101ca0(void){
    // LD_C(0x02);
    // CALL(aFunction10142c);
    Function10142c(0x02);
    // LD_E(0x0c);
    // CALL(aFunction101ee4);
    Function101ee4(0x0c); // Communication Ended...
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // RET;
}

void Function101cbc(void){
    // LD_A(0x01);
    // LD_addr_A(wcd2b);
    wram->wcd2b = 0x01;
    // RET;
}

void Function101cc2(void){
//  //  unreferenced
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101cc8(void){
    // LD_A(0x01);
    // LD_addr_A(wc314);
    wram->wc314[0] = 0x01;
    // LD_A(0x01);
    // LD_addr_A(wc30d);
    wram->wc30d = 0x01;
    // LD_HL(wcd29);
    // SET_hl(4);
    bit_set(wram->wcd29, 4);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101cdf(void){
    // LD_A(0x06);
    // LD_addr_A(wc314);
    wram->wc314[0] = 0x06;
    // LD_A(0x01);
    // LD_addr_A(wc30d);
    wram->wc30d = 0x01;
    // LD_HL(wcd29);
    // SET_hl(4);
    bit_set(wram->wcd29, 4);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101cf6(void){
    // LD_A(0x0b);
    // LD_addr_A(wc314 + 1);
    wram->wc314[1] = 0x0b;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101d03(void){
    // LD_A(0x0e);
    // LD_addr_A(wc314 + 1);
    wram->wc314[1] = 0x0e;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101d10(void){
    // LD_C(0x01);
    // CALL(aFunction10142c);
    Function10142c(0x01);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // JR(mFunction101d2a);
    return Function101d2a();
}

void Function101d1e(void){
    // LD_C(0x03);
    // CALL(aFunction10142c);
    Function10142c(0x03);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;

    return Function101d2a();
}

void Function101d2a(void){
    // CALL(aFunction101418);
    // RET_C ;
    if(Function101418())
        return;
    // LD_HL(wcd29);
    // SET_hl(6);
    bit_set(wram->wcd29, 6);
    // LD_A_addr(wcd26);
    // LD_HL(mJumptable_101d4d);
    // RST(aJumpTable);
    switch(wram->wcd26) {
        default:
        case 0: Function101d51(); break;
        case 1: Function101d5d(); break;
    }
    // LD_A_addr(wcd26);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd26, 7))
        return;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

// void Jumptable_101d4d(void){
    //dw ['Function101d51'];
    //dw ['Function101d5d'];
// }

void Function101d51(void){
    // LD_A(0x3c);
    // LD_addr_A(wcd42);
    wram->wcd42 = 0x3c;
    // LD_A_addr(wcd26);
    // INC_A;
    // LD_addr_A(wcd26);
    wram->wcd26++;

    return Function101d5d();
}

void Function101d5d(void){
    // LD_HL(wcd42);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcd42 != 0)
        return;
    // LD_A_addr(wcd26);
    // SET_A(7);
    // LD_addr_A(wcd26);
    bit_set(wram->wcd26, 7);
    // RET;
}

void Function101d6b(void){
    // LD_A_addr(wc30d);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wc30d != 0)
        return;
    // LD_HL(wcd29);
    // RES_hl(4);
    bit_reset(wram->wcd29, 4);
    // LD_A(0x64);
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex = 0x64;
    // RET;

}

void Function101d7b(void){
    // FARCALL(aFunction10138b);
    uint8_t c = Function10138b();
    // LD_B(0);
    // LD_HL(mUnknown_101d8d);
    // ADD_HL_BC;
    // LD_C_hl;
    // LD_A_C;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex = Unknown_101d8d[c];
    // RET;
}

const uint8_t Unknown_101d8d[] = {0x15, 0x15, 0x1f, 0x1f, 0x0c, 0x12, 0x3a, 0x3a};

void Function101d95(void){
    // CALL(aFunction101ee2);
    Function101ee2();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // LD_E(0x0e);
    // CALL(aFunction101ee4);
    Function101ee4(0x0e); // Choose the settings
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // RET;
}

void Function101db2(void){
    // FARCALL(aFunction103302);
    bool carry = Function103302();
    // CALL(aExitMenu);
    ExitMenu();
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // IF_C goto asm_101dca;
    if(carry) {
    // asm_101dca:
        // LD_A(0x02);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0x2;
        // RET;
        return;
    }
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function101dd0(void){
    // LD_HL(wdc41);
    // BIT_hl(1);
    // IF_NZ goto asm_101ddd;
    // LD_A(0x19);
    // LD_addr_A(wMobileCommsJumptableIndex);
    // RET;

// asm_101ddd:
    // LD_A(0x1b);
    // LD_addr_A(wMobileCommsJumptableIndex);
    // RET;
    wram->wMobileCommsJumptableIndex = (bit_test(wram->wdc41, 1))? 0x1b: 0x19;
}

void Function101de3(void){
    // CALL(aFunction101ecc);
    Function101ecc();
    // CALL(aFunction101ead);
    // IF_C goto asm_101df3;
    if(!Function101ead()) {
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }

// asm_101df3:
    // CALL(aFunction101e98);
    // IF_C goto asm_101e00;
    if(!Function101e98()) {
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }

// asm_101e00:
    // CALL(aFunction101ed3);
    Function101ed3();
    // LD_A(0x02);
    // LD_addr_A(wcd2b);
    wram->wcd2b = 0x02;
    // RET;
}

void Function101e09(void){
    // CALL(aFunction101ead);
    // IF_C goto asm_101e16;
    if(!Function101ead()) {
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }

// asm_101e16:
    // CALL(aFunction101ecc);
    Function101ecc();
    // CALL(aFunction101e98);
    bool carry = Function101e98();
    // PUSH_AF;
    // CALL(aFunction101ed3);
    // POP_AF;
    // IF_C goto asm_101e2b;
    if(!carry) {
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }

// asm_101e2b:
    // LD_A(0x02);
    // LD_addr_A(wcd2b);
    wram->wcd2b = 0x02;
    // RET;
}

void Function101e31(void){
    // LD_A(0x3a);
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex = 0x3a;
    // JP(mFunction101c2b);
    return Function101c2b();
}

void Function101e39(void){
    // CALL(aFunction1020bf);
    bool carry = Function1020bf();
    // PUSH_AF;
    // CALL(aFunction101ed3);
    Function101ed3();
    // POP_AF;
    // IF_C goto asm_101e49;
    if(!carry) {
        // LD_A(0x2a);
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex = 0x2a;
        // RET;
        return;
    }

// asm_101e49:
    // LD_A(0x02);
    // LD_addr_A(wcd2b);
    wram->wcd2b = 0x02;
    // RET;
}

void Function101e4f(void){
    // LD_E(0x06);
    // CALL(aFunction101ee4);
    Function101ee4(0x06); // Please enter a phone number.
    // CALL(aFunction1013d6);
    Function1013d6();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // LD_A(0);
    // LD_addr_A(wcd26);
    wram->wcd26 = 0;
    // RET;
}

void Function101e64(void){
    // CALL(aFunction101ecc);
    Function101ecc();
    // CALL(aFunction1020a8);
    bool carry = Function1020a8();
    // PUSH_AF;
    // CALL(aFunction101ed3);
    Function101ed3();
    // POP_AF;
    // IF_C goto asm_101e77;
    if(!carry) {
        // LD_A(0x24);
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex = 0x24;
        // RET;
        return;
    }

// asm_101e77:
    // LD_HL(wcd29);
    // SET_hl(5);
    bit_set(wram->wcd29, 5);
    // LD_A(0x02);
    // LD_addr_A(wcd2b);
    wram->wcd2b = 0x02;
    // RET;
}

void Function101e82(void){
//  //  unreferenced
    CALL(aFunction101ecc);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101e8d(void){
//  //  unreferenced
    CALL(aFunction101ed3);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

bool Function101e98(void){
    // CALL(aClearSprites);
    ClearSprites();
    // FARCALL(aFunction8adb3);
    // RET_C ;
    if(Function8adb3())
        return true;
    // LD_HL(wGameTimerPaused);
    // SET_hl(GAME_TIMER_MOBILE_F);
    bit_set(wram->wGameTimerPaused, GAME_TIMER_MOBILE_F);
    // LD_HL(wdc41);
    // SET_hl(4);
    bit_set(wram->wdc41, 4);
    // RET;
    return false;
}

bool Function101ead(void){
    // LD_HL(wGameTimerPaused);
    // BIT_hl(GAME_TIMER_MOBILE_F);
    // IF_NZ goto asm_101ec8;
    if(bit_test(wram->wGameTimerPaused, GAME_TIMER_MOBILE_F))
        return false;
    // LD_HL(wdc41);
    // BIT_hl(2);
    // IF_Z goto asm_101eca;
    if(!bit_test(wram->wdc41, 2))
        return true;
    // LD_A_addr(wcd2f);
    // AND_A_A;
    // IF_NZ goto asm_101ec8;
    if(wram->wcd2f != 0)
        return false;
    // LD_HL(wdc41);
    // BIT_hl(1);
    // IF_Z goto asm_101eca;
    if(!bit_test(wram->wdc41, 1))
        return true;

// asm_101ec8:
    // XOR_A_A;
    // RET;
    return false;

// asm_101eca:
    // SCF;
    // RET;
}

void Function101ecc(void){
    // CALL(aFunction101ee2);
    Function101ee2();
    // CALL(aFadeToMenu);
    FadeToMenu();
    // RET;
}

void Function101ed3(void){
    // CALL(aFunction1013aa);
    Function1013aa();
    // FARCALL(aFunction115d99);
    Function115d99();
    // LD_HL(wcd29);
    // SET_hl(7);
    bit_set(wram->wcd29, 7);
    // RET;
}

void Function101ee2(void){
    // LD_E(0);

    return Function101ee4(0);
}

// Mobile_PrintStatusMessage?
void Function101ee4(uint8_t e){
    // LD_D(0);
    // LD_HL(mUnknown_101ef5);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // FARCALL(aFunction100504);
    Function100504(U82C(Unknown_101ef5[e]));
    // RET;
}

const char* const Unknown_101ef5[] = {
    String_101f13, // 00
    String_101f14, // 01
    String_101f32, // 02
    String_101f4f, // 03
    String_101f69, // 04
    String_101f81, // 05
    String_101f93, // 06
    String_101faa, // 07
    String_101fc5, // 08
    String_101fd2, // 09
    String_101fe1, // 0a
    String_101fef, // 0b
    String_102000, // 0c
    String_10200c, // 0d
    String_102014, // 0e
};

enum {
    MOBILESTATUS_00,
    MOBILESTATUS_COMMUNICATE_WITH_FRIEND,
    MOBILESTATUS_CALLER_WILL_BE_CHARGED,
    MOBILESTATUS_IS_ADAPTER_READY,
    MOBILESTATUS_WANT_TO_CALL_FRIEND,
};

const char String_101f13[] = "@";

const char String_101f14[] = 
           "Communicate"        // "モバイルアダプタを\u3000つかって"
    t_next "with a friend!@";   // "おともだちと\u3000つうしんします@"

const char String_101f32[] = 
            "The caller will"   // "でんわを\u3000かけるひとには"
    t_next  "be charged.@";     // "つうわりょうきんが\u3000かかります@"

const char String_101f4f[] = 
            "Is the MOBILE"     // "モバイルアダプタの\u3000じゅんびは"
    t_next  "ADAPTER ready?@";  // "できて\u3000いますか？@"

const char String_101f69[] = 
            "Want to call"      // "あなたが\u3000おともだちに"
    t_next  "your friend?@";    // "でんわを\u3000かけますか？@"

const char String_101f81[] = 
            "Use the"	        // "めいしフォルダーを"
    t_next  "CARD FOLDER?@";    // "つかいますか？@"

const char String_101f93[] =
            "Please enter a"    // "でんわばんごうを\u3000にゅうりょく"
    t_next  "phone number.@";   // "してください@"

const char String_101faa[] = 
            "Waiting for"       // "それでは\u3000おともだちからの"
    t_next  "a call…@";         // "でんわを\u3000おまちします⋯@"

const char String_101fc5[] = 
    t_next  "Call this no.?@";  //next ['"に\u3000でんわを\u3000かけます@"']

const char String_101fd2[] =
    t_next  "Calling…@";        //next ['"に\u3000でんわを\u3000かけています@"']

const char String_101fe1[] = 
            "Call connected!@"; // "でんわが\u3000つながりました!@"

const char String_101fef[] = 
            "Ending call…@";    // "つうわを"
                                // "しゅうりょう\u3000します⋯@"

const char String_102000[] =
            "Communication"     // "つうしん\u3000しゅうりょう@"
    t_next  "ended.@";

const char String_10200c[] = 
            "CALL TIME@";       // "つうわ\u3000じかん@"

const char String_102014[] = 
            "Please choose"     // "それでは\u3000つうしんの"
    t_next  "the settings.@";   // "せっていを\u3000してください@"

void Function10202c(void){
    // FARCALL(aFunction115d99);
    Function115d99();
    // LD_HL(wcd29);
    // SET_hl(7);
    bit_set(wram->wcd29, 7);
    // LD_C(0x02);
    // CALL(aFunction10142c);
    Function10142c(0x02);
    // LD_E(0x0d);
    // CALL(aFunction101ee4);
    Function101ee4(0x0d); // CALL TIME
    // hlcoord(4, 4, wTilemap);
    // CALL(aFunction100681);
    Function100681(coord(4, 4, wram->wTilemap));
    // RET;
}

void Function102048(void){
    // CALL(aFunction10204c);
    // RET;
    return Function10204c();
}

void Function10204c(void){
    // hlcoord(3, 2, wTilemap);
    tile_t* hl = coord(3, 2, wram->wTilemap);
    // LD_C(0x10);
    uint8_t c = 0x10;
    // LD_DE(wcd53);
    uint8_t* de = wram->wMobileOpponentBattleMessage;

    do {
    // asm_102054:
        // LD_A_de;
        // INC_DE;
        uint8_t a = *(de++);
        // AND_A_A;
        // IF_Z goto asm_102067;
        // SUB_A(0x30);
        // IF_C goto asm_102067;
        // CP_A(0x0a);
        // IF_NC goto asm_102067;
        if(a == 0 || a < 0x30 || a - 0x30 >= 10)
            break;
        // ADD_A(0xf6);
        // LD_hli_A;
        *(hl++) = CHAR_0 + (a - 0x30);
        // DEC_C;
        // IF_NZ goto asm_102054;
    } while(--c != 0);

// asm_102067:
    // RET;
}

void Function102068(const uint8_t* de){
    // LD_HL(wcd53);
    uint8_t* hl = wram->wMobileOpponentBattleMessage;
    // LD_C(0x08);
    uint8_t c = 0x08;

    do {
    // asm_10206d:
        // LD_A_de;
        // CALL(aFunction102080);
        bool carry = Function102080(*de, hl);
        // IF_C goto asm_10207f;
        if(carry)
            break;
        hl++;
        // LD_A_de;
        // SWAP_A;
        // CALL(aFunction102080);
        carry = Function102080((*de) >> 4, hl);
        // IF_C goto asm_10207f;
        if(carry)
            break;
        hl++;
        // INC_DE;
        de++;
        // DEC_C;
        // IF_NZ goto asm_10206d;
    } while(--c != 0);

// asm_10207f:
    // RET;
}

bool Function102080(uint8_t a, uint8_t* hl){
    // AND_A(0x0f);
    // CP_A(0x0f);
    // IF_Z goto asm_10208a;
    if((a & 0x0f) == 0x0f) {
    // asm_10208a:
        // LD_hl(0);
        *hl = 0;
        // SCF;
        // RET;
        return true;
    }
    // ADD_A(0x30);
    // LD_hli_A;
    *(hl++) = (a & 0x0f) + 0x30;
    // RET;
    return false;
}

// CopyToBufferWdc42
void Function10208e(const void* de){
    // PUSH_DE;
    // LD_H_D;
    // LD_L_E;
    // LD_DE(wdc42);
    // LD_BC(8);
    // CALL(aCopyBytes);
    // POP_DE;
    // RET;
    CopyBytes(wram->wdc42, de, 8);
}

// ClearBufferWdc42
void Function10209c(void){
    // LD_A(0xff);
    // LD_HL(wdc42);
    // LD_BC(8);
    // CALL(aByteFill);
    ByteFill(wram->wdc42, sizeof(wram->wdc42), 0xff);
    // RET;
}

bool Function1020a8(void){
    // CALL(aFunction10209c);
    Function10209c();
    // LD_C(0x01);
    // LD_DE(wdc42);
    // FARCALL(aFunction17a68f);
    // RET_C ;
    if(Function17a68f(wram->wdc42, 0x1))
        return true;
    // CALL(aFunction10208e);
    Function10208e(wram->wStringBuffer1);
    // CALL(aFunction102068);
    Function102068(wram->wStringBuffer1);
    // XOR_A_A;
    // RET;
    return false;
}

bool Function1020bf(void){
    // CALL(aClearSprites);
    ClearSprites();
    // FARCALL(aFunction8aba9);
    uint8_t c = Function8aba9();
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto asm_1020e8;
    if(c == 0) {
    // asm_1020e8:
        // SCF;
        // RET;
        return true;
    }
    // DEC_A;
    // LD_HL(0xa04c);
    // LD_BC(0x25);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_A(0x04);
    // CALL(aOpenSRAM);
    OpenSRAM(0x4);
    const uint8_t* de = GBToRAMAddr(0xa04c + (25 * (c - 1)));
    // CALL(aFunction10208e);
    Function10208e(de);
    // CALL(aFunction102068);
    Function102068(de);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // XOR_A_A;
    // RET;
    return false;
}

bool Function1020ea(void){
    // LD_HL(wdc41);
    // BIT_hl(4);
    // IF_Z goto quit;
    // LD_HL(wdc41);
    // BIT_hl(2);
    // IF_NZ goto quit;
    if(!bit_test(wram->wdc41, 4) || bit_test(wram->wdc41, 2))
        return true;
    // CALL(aFunction10218d);
    Function10218d();
    // LD_HL(wc608);
    // BIT_hl(4);
    // IF_Z goto quit;
    // LD_HL(wc608);
    // BIT_hl(2);
    // IF_NZ goto quit;
    if(!bit_test(wram->wc608[0], 4) || bit_test(wram->wc608[0], 2))
        return true;
    // CALL(aFunction102112);
    // IF_Z goto quit;
    if(Function102112() == 0) {
        // AND_A_A;
        // RET;
        return false;
    }

// quit:
    // SCF;
    // RET;
    return true;
}

uint8_t Function102112(void){
    // LD_A(0x04);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as4_a03b));
    // LD_HL(0xa041);
    uint8_t* hl = GBToRAMAddr(s4_a03b + 6);
    // LD_C(40);
    uint8_t c = 40;

    do {
    // outer_loop:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_DE(0xc60f);
        const uint8_t* de = wram->wHallOfFameTemp.mon[0].nickname;
        // LD_B(31);
        uint8_t b = 31;

        do {
        // inner_loop:
            // LD_A_de;
            // CP_A_hl;
            // IF_NZ goto not_matching;
            if(*de != *hl2)
                goto not_matching;
            // INC_DE;
            de++;
            // INC_HL;
            hl2++;
            // DEC_B;
            // IF_NZ goto inner_loop;
        } while(--b != 0);
        // POP_HL;
        // XOR_A_A;
        // goto done;
        CloseSRAM();
        return 0x0;

    not_matching:
        // POP_HL;
        // LD_DE(37);
        // ADD_HL_DE;
        hl += 37;
        // DEC_C;
        // IF_NZ goto outer_loop;
    } while(--c != 0);
    // LD_A(0x01);
    // AND_A_A;
    // goto done;  // useless jr

// done:
    // PUSH_AF;
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_AF;
    // RET;
    return 0x1;
}

void Function102142(void){
    // CALL(aFunction10218d);
    Function10218d();
    // CALL(aFunction102180);
    Function102180();
    // LD_HL(mNewCardArrivedText);
    // CALL(aMenuTextbox);
    MenuTextbox(NewCardArrivedText);
    // LD_DE(SFX_LEVEL_UP);
    // CALL(aPlaySFX);
    PlaySFX(SFX_LEVEL_UP);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // CALL(aExitMenu);
    ExitMenu();
    // CALL(aFunction10219f);
    Function10219f();
    // LD_HL(mPutCardInCardFolderText);
    // CALL(aMenuTextbox);
    MenuTextbox(PutCardInCardFolderText);
    // CALL(aYesNoBox);
    bool cancel = !YesNoBox();
    // CALL(aExitMenu);
    ExitMenu();
    // IF_C goto asm_10217c;
    // CALL(aFunction1021b8);
    // IF_C goto asm_10217c;
    if(!cancel && !Function1021b8()) {
        // CALL(aFunction10218d);
        Function10218d();
        // CALL(aFunction102180);
        Function102180();
        // LD_HL(mCardWasListedText);
        // CALL(aPrintText);
        PrintText(CardWasListedText);
    }

// asm_10217c:
    // CALL(aFunction1013d6);
    Function1013d6();
    // RET;
}

void Function102180(void){
    // LD_HL(wc608 + 1);
    // LD_DE(wStringBuffer2);
    // LD_BC(11);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes(wram->wStringBuffer2, wram->wc608, NAME_LENGTH);
}

void Function10218d(void){
    // LD_HL(w5_dc00);
    // LD_DE(wc608);
    // LD_BC(0x26);
    // LD_A(0x05);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wc608, wram->w5_dc00, 0x26);
    // LD_DE(wc608 + 1);  // useless
    // RET;
}

void Function10219f(void){
    // CALL(aFadeToMenu);
    FadeToMenu();
    // CALL(aFunction10218d);
    Function10218d();
    // LD_DE(wc608 + 1);
    // FARCALL(aFunction8ac4e);
    Function8ac4e(wram->wc608 + 1);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // CALL(aFunction1013aa);
    Function1013aa();
    // RET;
}

bool Function1021b8(void){
    // CALL(aFadeToMenu);
    FadeToMenu();
    // CALL(aFunction10218d);
    Function10218d();
    // LD_DE(wPlayerMoveStruct);
    // FARCALL(aFunction8ac70);
    u8_flag_s res = Function8ac70(wram->wc608 + 7);
    // LD_A_C;
    // LD_addr_A(wStringBuffer1);
    wram->wStringBuffer1[0] = res.a;
    // PUSH_AF;
    // CALL(aFunction1013aa);
    Function1013aa();
    // POP_AF;
    // RET;
    return res.flag;
}

const txt_cmd_s NewCardArrivedText[] = {
    text_far(v_NewCardArrivedText)
    text_end
};

const txt_cmd_s PutCardInCardFolderText[] = {
    text_far(v_PutCardInCardFolderText)
    text_end
};

const txt_cmd_s CardWasListedText[] = {
    text_far(v_CardWasListedText)
    text_end
};

void Function1021e0(const txt_cmd_s* txt){
    // CALL(aMenuTextbox);
    MenuTextbox(txt);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // CALL(aExitMenu);
    ExitMenu();
    // RET;
}

void StartingLinkText(void){
//  //  unreferenced
    //text_far ['_StartingLinkText']
    //text_end ['?']
}

const txt_cmd_s LinkTerminatedText[] = {
    text_far(v_LinkTerminatedText)
    text_end
};

const txt_cmd_s ClosingLinkText[] = {
    text_far(v_ClosingLinkText)
    text_end
};

bool Function1021f9(void){
    // CALL(aFunction102233);
    Function102233();
    // LD_A(0x0);  // Function10234b
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x0;  // Function10234b
    // LD_HL(wcd29);
    // BIT_hl(3);
    // RES_hl(3);
    // IF_Z goto asm_10220f;
    if(bit_test(wram->wcd29, 3)) {
        bit_reset(wram->wcd29, 3);
        // LD_A(0x1);  // Function102361
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x1;  // Function102361
    }

    do {
    // asm_10220f:
        // CALL(aFunction1022ca);
        Function1022ca();
        // LD_A_addr(wcd49);
        // LD_HL(mJumptable_1022f5); // TODO: Convert Jumptable_1022f5
        // RST(aJumpTable);
        Jumptable_1022f5(wram->wcd49);
        // CALL(aFunction102241);
        Function102241();
        // CALL(aFunction1022d0);
        // IF_C goto asm_102231;
        if(Function1022d0()) {
        // asm_102231:
            // XOR_A_A;
            // RET;
            return false;
        }
        // LD_A_addr(wcd49);
        // BIT_A(7);
        // IF_Z goto asm_10220f;
    } while(!bit_test(wram->wcd49, 7));
    // XOR_A_A;
    // LD_HL(wcd29);
    // BIT_hl(3);
    // RET_Z ;
    if(!bit_test(wram->wcd29, 3))
        return false;
    // SCF;
    // RET;
    return true;
}

void Function102233(void){
    // LD_HL(wcd49);
    // LD_BC(10);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(&wram->wcd49, 10, 0);
    // CALL(aFunction10304f);
    Function10304f();
    // RET;
}

void Function102241(void){
    // CALL(aFunction10226a);
    Function10226a();
    // CALL(aFunction102274);
    Function102274();
    // CALL(aFunction10224b);
    Function10224b();
    // RET;
}

bool Function10224b(void){
    // LD_HL(wcd4b);
    // BIT_hl(1);
    // IF_NZ goto asm_10225e;
    // BIT_hl(2);
    // IF_NZ goto asm_10225e;
    if(!bit_test(wram->wcd4b, 1) && !bit_test(wram->wcd4b, 2)) {
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
        // XOR_A_A;
        // RET;
        return false;
    }

// asm_10225e:
    // RES_hl(1);
    // RES_hl(2);
    wram->wcd4b &= ~((1 << 1) | (1 << 2));
    // FARCALL(aMobile_ReloadMapPart);
    Mobile_ReloadMapPart();
    // SCF;
    // RET;
    return true;
}

void Function10226a(void){
    // LD_HL(wcd4b);
    // BIT_hl(0);
    // RET_Z ;
    if(!bit_test(wram->wcd4b, 0))
        return;
    // CALL(aFunction10305d);
    Function10305d();
    // RET;
}

void Function102274(void){
    // LD_HL(wcd4b);
    // BIT_hl(3);
    // RET_Z ;
    if(!bit_test(wram->wcd4b, 3))
        return;
    // RES_hl(3);
    bit_reset(wram->wcd4b, 3);
    // LD_DE(8);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // RET;
}

void Function102283(void){
    // LD_A(0x01);
    // LD_addr_A(wAttrmapEnd);
    wram->wAttrmapEnd = 0x01;
    // LD_HL(wcd4b);
    // SET_hl(0);
    bit_set(wram->wcd4b, 0);
    // RET;
}

void Function10228e(void){
    // XOR_A_A;
    // LD_addr_A(wAttrmapEnd);
    wram->wAttrmapEnd = 0x0;
    // LD_HL(wcd4b);
    // RES_hl(0);
    bit_reset(wram->wcd4b, 0);
    // RET;
}

void Function102298(uint8_t e){
    // LD_A_E;
    // CP_A(0x02);
    // RET_NZ ;
    if(e != 0x2)
        return;
    // LD_HL(wcd4b);
    // BIT_hl(6);
    // IF_Z goto asm_1022b6;
    if(bit_test(wram->wcd4b, 6)) {
        // LD_HL(wcd4b);
        // BIT_hl(7);
        // LD_HL(wcd4b);
        // SET_hl(7);
        // RET_NZ ;
        if(bit_test(wram->wcd4b, 7))
            return;
        bit_set(wram->wcd4b, 7);
        // LD_DE(SFX_ELEVATOR_END);
        // CALL(aPlaySFX);
        PlaySFX(SFX_ELEVATOR_END);
        // goto asm_1022c1;
    }
    else {
    // asm_1022b6:
        // LD_HL(wcd4b);
        // BIT_hl(7);
        if(!bit_test(wram->wcd4b, 7))
            return;
        // LD_HL(wcd4b);
        // RES_hl(7);
        // RET_Z ;
        bit_reset(wram->wcd4b, 7);
    }
// asm_1022c1:
    // CALL(aFunction10304f);
    Function10304f();
    // LD_A(0x01);
    // LD_addr_A(wAttrmapEnd);
    wram->wAttrmapEnd = 1;
    // RET;
}

// Mobile_SetOverworldDelayTo30
void Function1022ca(void){
    // LD_A(30);
    // LD_addr_A(wOverworldDelay);
    wram->wOverworldDelay = 30;
    // RET;
}

bool Function1022d0(void){
    // FARCALL(aFunction10032e);
    u8_flag_s res = Function10032e();
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto asm_1022f3;
    if(wram->wcd2b != 0)
        return true;
    // CALL(aFunction102298);
    Function102298(res.a);
    // LD_A_addr(wOverworldDelay);
    // LD_C_A;
    // LD_A(30);
    // SUB_A_C;
    // LD_C_A;
    // LD_B(03);
    // FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    // IF_C goto asm_1022f3;
    if(AdvanceMobileInactivityTimerAndCheckExpired(30 - wram->wOverworldDelay, 3))
        return true;
    // XOR_A_A;
    // RET;
    return false;

// asm_1022f3:
    // SCF;
    // RET;
}

void Jumptable_1022f5(uint8_t a){
    switch(a) {
        case 0x00: return Function10234b();  // 00
        case 0x01: return Function102361();  // 01
        case 0x02: return Function10236e();  // 02
        case 0x03: return Function102387();  // 03
        case 0x04: return Function1023a1();  // 04
        case 0x05: return Function1025c7();  // 05
        case 0x06: return Function1025dc();  // 06
        case 0x07: return Function1024f6();  // 07
        case 0x08: return Function10250c();  // 08
        case 0x09: return Function1024a8();  // 09
        case 0x0a: return Function102591();  // 0a
        case 0x0b: return Function1024a8();  // 0b
        case 0x0c: return Function1025b0();  // 0c
        case 0x0d: return Function1025bd();  // 0d
        case 0x0e: return Function102814();  // 0e
        case 0x0f: return Function10283c();  // 0f
        case 0x10: return Function102862();  // 10
        case 0x11: return Function10286f();  // 11
        case 0x12: return Function1024a8();  // 12
        case 0x13: return Function1028a5();  // 13
        case 0x14: return Function1028ab();  // 14
        case 0x15: return Function1023b5();  // 15
        case 0x16: return Function1023c6();  // 16
        case 0x17: return Function1024af();  // 17
        case 0x18: return Function102416();  // 18
        case 0x19: return Function102423();  // 19
        case 0x1a: return Function10244b();  // 1a
        case 0x1b: return Function1024af();  // 1b
        case 0x1c: return Function10246a();  // 1c
        case 0x1d: return Function102652();  // 1d
        case 0x1e: return Function10266b();  // 1e
        case 0x1f: return Function1025e9();  // 1f
        case 0x20: return Function1025ff();  // 20
        case 0x21: return Function102738();  // 21
        case 0x22: return Function102754();  // 22
        case 0x23: return Function1026b7();  // 23
        case 0x24: return Function1026c8();  // 24
        case 0x25: return Function1028bf();  // 25
        case 0x26: return Function1028c6();  // 26
        case 0x27: return Function1028d3();  // 27
        case 0x28: return Function1028da();  // 28
        case 0x29: return Function1024a8();  // 29
        case 0x2a: return Function10248d();  // 2a
    }
}

void Function10234b(void){
    // CALL(aFunction102d9a);
    Function102d9a();
    // CALL(aFunction102dd3);
    Function102dd3();
    // CALL(aFunction102dec);
    Function102dec();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;

}

void Function102361(void){
    // LD_A(0xcc);
    // CALL(aFunction1028e8);
    Function1028e8(0xcc);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function10236e(void){
    // CALL(aFunction1028fc);
    // RET_NC ;
    if(!Function1028fc())
        return;
    // LD_A_addr(wcd51);
    // CP_A(0xcc);
    // IF_Z goto asm_10237f;
    if(wram->wcd51 != 0xcc) {
        // LD_A(0xf2);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf2;
        // RET;
        return;
    }

// asm_10237f:
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function102387(void){
    // LD_HL(wcd4b);
    // SET_hl(6);
    bit_set(wram->wcd4b, 6);
    // XOR_A_A;
    // LD_addr_A(wdc5f);
    wram->wdc5f = 0;
    // LD_DE(MUSIC_ROUTE_30);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_ROUTE_30);
    // CALL(aFunction102d9a);
    Function102d9a();
    // CALL(aFunction102dd3);
    Function102dd3();
    // LD_A(0x01);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 0x01;

    return Function1023a1();
}

void Function1023a1(void){
    // CALL(aFunction102283);
    Function102283();
    // CALL(aFunction102db7);
    Function102db7();
    // CALL(aFunction102dec);
    Function102dec();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0x1d);
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x1d;
    // RET;
}

void Function1023b5(void){
    // CALL(aFunction10228e);
    Function10228e();
    // CALL(aFunction102a3b);
    Function102a3b();
    // CALL(aFunction102b12);
    Function102b12();
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function1023c6(void){
    // CALL(aFunction102c48);
    Function102c48();
    // CALL(aFunction102c87);
    Function102c87();
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wcd4c - 1;
    // XOR_A_A;  // REMOVE_PARTY
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    wram->wPokemonWithdrawDepositParameter = REMOVE_PARTY;
    // FARCALL(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox_Conv(REMOVE_PARTY);
    // LD_HL(wPartyCount);
    // INC_hl;
    wram->wPartyCount++;
    // LD_A_hli;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_hl(0xff);
    wram->wPartySpecies[wram->wPartyCount - 1] = 0xff;
    // LD_A_addr(wPartyCount);
    // LD_addr_A(wcd4c);
    wram->wcd4c = wram->wPartyCount;
    // CALL(aFunction102c07);
    Function102c07();
    // CALL(aFunction102d48);
    Function102d48();
    // CALL(aFunction102b32);
    Function102b32();
    // CALL(aFunction102f50);
    Function102f50();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0x14);
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0x14;
    // LD_A(0);
    // LD_addr_A(wcd4f);
    wram->wcd4f = 0;
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function102416(void){
    // LD_A(0xaa);
    // CALL(aFunction1028e8);
    Function1028e8(0xaa);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function102423(void){
    // CALL(aFunction102921);
    // RET_NC ;
    if(!Function102921())
        return;
    // FARCALL(aSaveAfterLinkTrade);
    SaveAfterLinkTrade();
    // FARCALL(aStubbedTrainerRankings_Trades);
    StubbedTrainerRankings_Trades();
    // FARCALL(aBackupMobileEventIndex);
    BackupMobileEventIndex();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function10244b(void){
    // CALL(aFunction102f32);
    Function102f32();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0x19);
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0x19;
    // LD_A(0);
    // LD_addr_A(wcd4f);
    wram->wcd4f = 0;
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function10246a(void){
    // CALL(aFunction102d9a);
    Function102d9a();
    // LD_HL(wcd29);
    // SET_hl(3);
    bit_set(wram->wcd29, 3);
    // CALL(aFunction102e07);
    Function102e07();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0x2a);
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x2a;
    // RET;
}

void Function102480(void){
//  //  unreferenced
    LD_C(0x32);
    CALL(aDelayFrames);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10248d(void){
    // LD_A_addr(wcd49);
    // SET_A(7);
    // LD_addr_A(wcd49);
    bit_set(wram->wcd49, 7);
    // RET;
}

void Function102496(void){
//  //  unreferenced
    LD_HL(wcd4e);
    DEC_hl;
    RET_NZ ;
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1024a8(void){
    // FARCALL(aFunction1009f3);
    // RET_C ;
    if(Function1009f3())
        return;

    return Function1024af();
}

void Function1024af(void){
    // CALL(aGetJoypad);
    GetJoypad();
    // LD_A_addr(wcd4a);
    // LD_HL(mJumptable_1024ba);
    // RST(aJumpTable);
    Jumptable_1024ba(wram->wcd4a);
    // RET;
}

void Jumptable_1024ba(uint8_t a){
    switch(a) {
        case 0: return Function1024c0();
        case 1: return Function1024cb();
        case 2: return Function1024de();
    }
}

void Function1024c0(void){
    // LD_HL(wcd4e);
    // INC_hl;
    wram->wcd4e++;
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;

    return Function1024cb();
}

void Function1024cb(void){
    // LD_HL(wcd4e);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcd4e != 0)
        return;
    // LD_A_addr(wcd4f);
    // INC_A;
    // LD_addr_A(wcd4e);
    wram->wcd4e = wram->wcd4f + 1;
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;

    return Function1024de();
}

void Function1024de(void){
    // LD_HL(wcd4e);
    // DEC_hl;
    // IF_Z goto asm_1024e9;
    if(--wram->wcd4e != 0) {
        // LDH_A_addr(hJoyPressed);
        // AND_A(A_BUTTON | B_BUTTON);
        // RET_Z ;
        if((hram->hJoyPressed & (A_BUTTON | B_BUTTON)) == 0)
            return;
    }

// asm_1024e9:
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function1024f6(void){
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A_addr(wcd4c);
    // CALL(aFunction1028e8);
    Function1028e8(wram->wcd4c);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function10250c(void){
    // CALL(aFunction1028fc);
    // RET_NC ;
    if(!Function1028fc())
        return;
    // LD_A_addr(wcd51);
    // CP_A(0x0f);
    // IF_Z goto asm_10254b;
    if(wram->wcd51 == 0x0f) {
    // asm_10254b:
        // CALL(aFunction103021);
        Function103021();
        // LD_HL(wcd4b);
        // SET_hl(1);
        bit_set(wram->wcd4b, 1);
        // LD_A(0);
        // LD_addr_A(wcd4a);
        wram->wcd4a = 0;
        // LD_A(0x1e);
        // LD_addr_A(wcd4e);
        wram->wcd4e = 0x1e;
        // LD_A(0x1e);
        // LD_addr_A(wcd4f);
        wram->wcd4f = 0x1e;
        // LD_A(0x29);
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x29;
        // RET;
        return;
    }
    // AND_A_A;
    // IF_Z goto asm_102572;
    // CP_A(0xaa);
    // IF_Z goto asm_102572;
    // CP_A(0x07);
    // IF_NC goto asm_102572;
    else if(wram->wcd51 == 0 || wram->wcd51 == 0xaa || wram->wcd51 == 0x07) {
    // asm_102572:
        // CALL(aFunction102fce);
        Function102fce();
        // goto asm_102577;
    }
    else {
        // LD_addr_A(wcd4d);
        wram->wcd4d = wram->wcd51;
        // DEC_A;
        // LD_addr_A(wd003);
        wram->wd003 = wram->wcd51 - 1;
        // LD_A_addr(wcd4c);
        // DEC_A;
        // LD_addr_A(wd002);
        wram->wd002 = wram->wcd4c - 1;
        // CALL(aFunction102b9c);
        Function102b9c();
        // CALL(aFunction102bdc);
        // IF_C goto asm_10256d;
        if(Function102bdc()) {
        // asm_10256d:
            // CALL(aFunction102f85);
            Function102f85();
            // goto asm_102577;
        }
        // FARCALL(aCheckAnyOtherAliveMonsForTrade);
        // IF_C goto asm_102568;
        else if(!CheckAnyOtherAliveMonsForTrade(wram->wCurTradePartyMon)) {
        // asm_102568:
            // CALL(aFunction102ff5);
            Function102ff5();
            // goto asm_102577;
        }
        else {
            // LD_HL(wcd4b);
            // SET_hl(1);
            bit_set(wram->wcd4b, 1);
            // LD_A(0x0e);
            // LD_addr_A(wcd49);
            wram->wcd49 = 0x0e;
            // RET;
            return;
        }
    }

// asm_102577:
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_A(0x1e);
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0x1e;
    // LD_A(0x3c);
    // LD_addr_A(wcd4f);
    wram->wcd4f = 0x3c;
    // LD_A(0x09);
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x09;
    // RET;
}

void Function102591(void){
    // CALL(aFunction102ee7);
    Function102ee7();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_A(0x1e);
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0x1e;
    // LD_A(0x3c);
    // LD_addr_A(wcd4f);
    wram->wcd4f = 0x3c;
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function1025b0(void){
    // LD_A(0x09);
    // CALL(aFunction1028e8);
    Function1028e8(0x09);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function1025bd(void){
    // CALL(aFunction1028fc);
    // RET_NC ;
    if(!Function1028fc())
        return;
    // LD_A(0x04);
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x04;
    // RET;
}

void Function1025c7(void){
    // CALL(aFunction102f6d);
    Function102f6d();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0x0f);
    // CALL(aFunction1028e8);
    Function1028e8(0x0f);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function1025dc(void){
    // CALL(aFunction1028fc);
    // RET_NC ;
    if(!Function1028fc())
        return;
    // LD_A_addr(wcd49);
    // SET_A(7);
    // LD_addr_A(wcd49);
    bit_set(wram->wcd49, 7);
    // RET;
}

void Function1025e9(void){
    // NOP;
    // LD_HL(wcd4b);
    // SET_hl(6);
    bit_set(wram->wcd4b, 6);
    // CALL(aFunction102b4e);
    Function102b4e();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function1025ff(void){
    // LD_HL(wcd4b);
    // SET_hl(2);
    bit_set(wram->wcd4b, 2);
    // FARCALL(aFunction1009f3);
    // RET_C ;
    if(Function1009f3())
        return;
    // FARCALL(aMobileMenuJoypad);
    uint8_t c = MobileMenuJoypad_Conv();
    // LD_A_addr(wMenuJoypadFilter);
    // AND_A_C;
    c &= wram->wMenuJoypadFilter;
    // RET_Z ;
    if(c == 0)
        return;
    // BIT_C(A_BUTTON_F);
    // IF_NZ goto a_button;
    if(bit_test(c, A_BUTTON_F)) {
    // a_button:
        // LD_HL(wcd4b);
        // SET_hl(3);
        bit_set(wram->wcd4b, 3);
        // LD_A(0x27);  // Function1028d3
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x27;  // Function1028d3
        // RET;
        return;
    }
    // BIT_C(D_UP_F);
    // IF_NZ goto d_up;
    else if(bit_test(c, D_UP_F)) {
    // d_up:
        // LD_A_addr(wMenuCursorY);
        // LD_B_A;
        // LD_A_addr(wOTPartyCount);
        // CP_A_B;
        // RET_NZ ;
        if(wram->wMenuCursorY != wram->wOTPartyCount)
            return;
        // CALL(aHideCursor);
        HideCursor();
        // LD_A_addr(wPartyCount);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = wram->wPartyCount;
        // LD_A(0x1d);  // Function102652
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x1d;  // Function102652
        // RET;    
        return;
    }
    // BIT_C(D_DOWN_F);
    // IF_NZ goto d_down;
    else if(bit_test(c, D_DOWN_F)) {
    // d_down:
        // LD_A_addr(wMenuCursorY);
        // CP_A(0x01);
        // RET_NZ ;
        if(wram->wMenuCursorY != 0x01)
            return;
        // LD_A(0x23);  // Function1026b7
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x23;  // Function1026b7
        // RET;
        return;
    }
    // RET;
}

void Function102652(void){
    // NOP;
    // LD_HL(wcd4b);
    // SET_hl(6);
    bit_set(wram->wcd4b, 6);
    // NOP;
    // CALL(aFunction102b7b);
    Function102b7b();
    // NOP;
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // NOP;
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function10266b(void){
    // LD_HL(wcd4b);
    // SET_hl(2);
    bit_set(wram->wcd4b, 2);
    // FARCALL(aFunction1009f3);
    // RET_C ;
    if(Function1009f3())
        return;
    // FARCALL(aMobileMenuJoypad);
    uint8_t c = MobileMenuJoypad_Conv();
    // LD_A_addr(wMenuJoypadFilter);
    c &= wram->wMenuJoypadFilter;
    // AND_A_C;
    // RET_Z ;
    if(c == 0)
        return;
    // BIT_C(A_BUTTON_F);
    // IF_NZ goto a_button;
    if(bit_test(c, A_BUTTON_F)) {
    // a_button:
        // LD_HL(wcd4b);
        // SET_hl(3);
        bit_set(wram->wcd4b, 3);
        // LD_A(0x21);  // Function102738
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x21;  // Function102738
        // RET;
        return;
    }
    // BIT_C(D_DOWN_F);
    // IF_NZ goto d_down;
    else if(bit_test(c, D_DOWN_F)) {
    // d_down:
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // RET_NZ ;
        if(wram->wMenuCursorY - 1 != 0)
            return;
        // CALL(aHideCursor);
        HideCursor();
        // LD_A(0x1f);  // Function1025e9
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x1f;  // Function1025e9
        // RET;
        return;
    }
    // BIT_C(D_UP_F);
    // IF_NZ goto d_up;
    else if(bit_test(c, D_UP_F)) {
    // d_up:
        // LD_A_addr(wMenuCursorY);
        // LD_B_A;
        // LD_A_addr(wPartyCount);
        // CP_A_B;
        // RET_NZ ;
        if(wram->wMenuCursorY != wram->wPartyCount)
            return;
        // LD_A(0x23);  // Function1026b7
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x23;  // Function1026b7
        // RET;
        return;
    }
    // RET;
}

void Function1026b7(void){
    // LD_HL(wcd4b);
    // SET_hl(6);
    bit_set(wram->wcd4b, 6);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;

    return Function1026c8();
}

void Function1026c8(void){
    // CALL(aGetJoypad);
    GetJoypad();
    // FARCALL(aFunction1009f3);
    // RET_C ;
    if(Function1009f3())
        return;
    // LD_A_addr(wcd4a);
    // LD_HL(mJumptable_1026da);
    Jumptable_1026da(wram->wcd4a);
    // RST(aJumpTable);
    // RET;
}

void Jumptable_1026da(uint8_t a){
    switch(a) {
        case 0: return Function1026de();
        case 1: return Function1026f3();
    }
}

void Function1026de(void){
    // CALL(aHideCursor);
    HideCursor();
    // hlcoord(9, 17, wTilemap);
    // LD_hl(0xed);
    *coord(9, 17, wram->wTilemap) = 0xed;
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // RET;
}

void Function1026f3(void){
    // LDH_A_addr(hJoyPressed);
    // BIT_A(A_BUTTON_F);
    // IF_NZ goto asm_102723;
    if(bit_test(hram->hJoyPressed, A_BUTTON_F)) {
    // asm_102723:
        // hlcoord(9, 17, wTilemap);
        // LD_hl(0xec);
        *coord(9, 17, wram->wTilemap) = 0xec;
        // LD_HL(wcd4b);
        // SET_hl(3);
        // LD_HL(wcd4b);
        // SET_hl(2);
        wram->wcd4b |= ((1 << 3) | (1 << 2));
        // LD_A(0x5);  // Function1025c7
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x5;  // Function1025c7
        // RET;
        return;
    }
    // BIT_A(D_UP_F);
    // IF_NZ goto asm_102712;
    else if(bit_test(hram->hJoyPressed, D_UP_F)) {
    // asm_102712:
        // hlcoord(9, 17, wTilemap);
        // LD_hl(0x7f);
        *coord(9, 17, wram->wTilemap) = 0x7f;
        // LD_A_addr(wOTPartyCount);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = wram->wOTPartyCount;
        // LD_A(0x1f);  // Function1025e9
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x1f;  // Function1025e9
        // RET;
        return;
    }
    // BIT_A(D_DOWN_F);
    // IF_NZ goto asm_102702;
    else if(bit_test(hram->hJoyPressed, D_DOWN_F)) {
    // asm_102702:
        // hlcoord(9, 17, wTilemap);
        // LD_hl(0x7f);
        *coord(9, 17, wram->wTilemap) = 0x7f;
        // LD_A(0x01);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 0x1;
        // LD_A(0x1d);  // Function102652
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x1d;  // Function102652
        // RET;
        return;
    }
    // RET;
}

void Function102738(void){
    // LD_HL(wcd4b);
    // SET_hl(6);
    bit_set(wram->wcd4b, 6);
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor();
    // CALL(aFunction1027eb);
    Function1027eb();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;

    return Function102754();
}

void Function102754(void){
    // CALL(aGetJoypad);
    GetJoypad();
    // FARCALL(aFunction1009f3);
    // RET_C ;
    if(Function1009f3())
        return;
    // LD_A_addr(wcd4a);
    // LD_HL(mJumptable_102766);
    Jumptable_102766(wram->wcd4a);
    // RST(aJumpTable);
    // RET;
}

void Jumptable_102766(uint8_t a){
    switch(a) {
        case 0x0: return Function102770();
        case 0x1: return Function102775();
        case 0x2: return Function10278c();
        case 0x3: return Function1027a0();
        case 0x4: return Function1027b7();
    }
}

void Function102770(void){
    // LD_A(0x01);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0x1;

    return Function102775();
}

void Function102775(void){
    // hlcoord(1, 16, wTilemap);
    // LD_hl(0xed);
    *coord(1, 16, wram->wTilemap) = 0xed;
    // hlcoord(11, 16, wTilemap);
    // LD_hl(0x7f);
    *coord(11, 16, wram->wTilemap) = 0x7f;
    // LD_HL(wcd4b);
    // SET_hl(2);
    bit_set(wram->wcd4b, 2);
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // RET;
}

void Function10278c(void){
    // LDH_A_addr(hJoyPressed);
    // BIT_A(A_BUTTON_F);
    // JR_NZ (masm_1027c6);
    if(bit_test(hram->hJoyPressed, A_BUTTON_F))
        return asm_1027c6();
    // BIT_A(B_BUTTON_F);
    // JR_NZ (masm_1027e2);
    else if(bit_test(hram->hJoyPressed, B_BUTTON_F))
        return asm_1027e2();
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto asm_10279b;
    else if(bit_test(hram->hJoyPressed, D_RIGHT_F)) {
    // asm_10279b:
        // LD_A(0x03);
        // LD_addr_A(wcd4a);
        wram->wcd4a = 0x3;
        return Function1027a0();
    }
    // RET;
}

void Function1027a0(void){
    // hlcoord(1, 16, wTilemap);
    // LD_hl(0x7f);
    *coord(1, 16, wram->wTilemap) = 0x7f;
    // hlcoord(11, 16, wTilemap);
    // LD_hl(0xed);
    *coord(11, 16, wram->wTilemap) = 0xed;
    // LD_HL(wcd4b);
    // SET_hl(2);
    bit_set(wram->wcd4b, 2);
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // RET;
}

void Function1027b7(void){
    // LDH_A_addr(hJoyPressed);
    // BIT_A(A_BUTTON_F);
    // JR_NZ (masm_1027d1);
    if(bit_test(hram->hJoyPressed, A_BUTTON_F))
        return asm_1027d1();
    // BIT_A(B_BUTTON_F);
    // JR_NZ (masm_1027e2);
    else if(bit_test(hram->hJoyPressed, B_BUTTON_F))
        return asm_1027e2();
    // BIT_A(D_LEFT_F);
    // JR_NZ (mFunction102770);
    else if(bit_test(hram->hJoyPressed, D_LEFT_F))
        return Function102770();
    // RET;
}

void asm_1027c6(void){
    // LD_HL(wcd4b);
    // SET_hl(3);
    bit_set(wram->wcd4b, 3);
    // LD_A(0x25);  // Function1028bf
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x25;  // Function1028bf
    // RET;
}

void asm_1027d1(void){
    // LD_HL(wcd4b);
    // SET_hl(3);
    bit_set(wram->wcd4b, 3);
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wcd4c);
    wram->wcd4c = wram->wMenuCursorY;
    // LD_A(0x7);  // Function1024f6
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x7;  // Function1024f6
    // RET;
}

void asm_1027e2(void){
    // CALL(aFunction102db7);
    Function102db7();
    // LD_A(0x1d);  // Function102652
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x1d;  // Function102652
    // RET;
}

void Function1027eb(void){
    static const char Stats_Trade[] = "STATS     TRADE@";
    // hlcoord(0, 14, wTilemap);
    // LD_B(2);
    // LD_C(18);
    // LD_D_H;
    // LD_E_L;
    // FARCALL(av_LinkTextbox);
    v_LinkTextbox(coord(0, 14, wram->wTilemap), 2, 18);
    // LD_DE(mFunction1027eb_Stats_Trade);
    // hlcoord(2, 16, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Stats_Trade), coord(2, 16, wram->wTilemap));
    // RET;
}

void Function102814(void){
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wcd52);
    wram->wcd52 = wram->wMenuCursorY;
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_addr_A(wd002);
    wram->wd002 = wram->wcd4c - 1;
    // LD_A_addr(wcd4d);
    // DEC_A;
    // LD_addr_A(wd003);
    wram->wd003 = wram->wcd4d - 1;
    // CALL(aFunction102ea8);
    Function102ea8();
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);

    return Function10283c();
}

void Function10283c(void){
    // LD_HL(wcd4b);
    // SET_hl(2);
    bit_set(wram->wcd4b, 2);
    // CALL(aFunction1029c3);
    u8_flag_s res = Function1029c3();
    // RET_Z ;
    if(res.a == 0)
        return;
    // IF_C goto asm_102852;
    if(res.flag) {
    // asm_102852:
        // LD_A(0x14);  // Function1028ab
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x14;  // Function1028ab
        // LD_HL(wcd4b);
        // SET_hl(3);
        // LD_HL(wcd4b);
        // SET_hl(1);
        wram->wcd4b |= ((1 << 1) | (1 << 3));
        // RET;
        return;
    }
    else {
        // LD_A(0x10);  // Function102862
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x10;  // Function102862
        // LD_HL(wcd4b);
        // SET_hl(1);
        bit_set(wram->wcd4b, 1);
        // RET;
        return;
    }
}

void Function102862(void){
    // LD_A(0x08);
    // CALL(aFunction1028e8);
    Function1028e8(0x08);
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function10286f(void){
    // CALL(aFunction1028fc);
    // RET_NC ;
    if(!Function1028fc())
        return;
    // LD_A_addr(wcd52);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wcd52;
    // LD_A_addr(wcd51);
    // CP_A(0x08);
    // IF_NZ goto asm_102886;
    if(wram->wcd51 == 0x8) {
        // LD_A(0x15);  // Function1023b5
        // LD_addr_A(wcd49);
        wram->wcd49 = 0x15;  // Function1023b5
        // RET;
        return;
    }

// asm_102886:
    // CALL(aFunction102ee7);
    Function102ee7();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0x1e);
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0x1e;
    // LD_A(0x3c);
    // LD_addr_A(wcd4f);
    wram->wcd4f = 0x3c;
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // RET;
}

void Function1028a5(void){
    // LD_A(0x4);  // Function1023a1
    // LD_addr_A(wcd49);
    // RET;
    wram->wcd49 = 0x4;  // Function1023a1
}

void Function1028ab(void){
    // LD_A_addr(wcd52);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wcd52;
    // CALL(aFunction102f15);
    Function102f15();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A(0xc);  // Function1025b0
    // LD_addr_A(wcd49);
    wram->wcd49 = 0xc;  // Function1025b0
    // RET;

}

void Function1028bf(void){
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;

    return Function1028c6();
}

void Function1028c6(void){
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // CALL(aFunction102bac);
    Function102bac();
    // LD_A(0x1d);  // Function102652
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x1d;  // Function102652
    // RET;

}

void Function1028d3(void){
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;

    return Function1028da();
}

void Function1028da(void){
    // LD_A(OTPARTYMON);
    // LD_addr_A(wMonType);
    wram->wMonType = OTPARTYMON;
    // CALL(aFunction102bac);
    Function102bac();
    // LD_A(0x1f);  // Function1025e9
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x1f;  // Function1025e9
    // RET;
}

void Function1028e8(uint8_t a){
    // LD_HL(wcd4b);
    // RES_hl(6);
    bit_reset(wram->wcd4b, 6);
    // LD_addr_A(wcd50);
    wram->wcd50 = a;
    // FARCALL(aStartMobileInactivityTimer);
    StartMobileInactivityTimer();
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // RET;
}

bool Function1028fc(void){
    // CALL(aGetJoypad);
    GetJoypad();
    // FARCALL(aFunction1009f3);
    // IF_NC goto asm_102909;
    if(Function1009f3()) {
        // AND_A_A;
        // RET;
        return false;
    }

// asm_102909:
    // LD_A_addr(wcd4a);
    // LD_HL(mJumptable_102917);
    // RST(aJumpTable);
    bool carry = false;
    switch(wram->wcd4a) {
        case 0: carry = Function102933(); break;
        case 1: carry = Function10294f(); break;
        case 2: carry = Function10295d(); break;
        case 3: carry = Function10296e(); break;
        case 4: carry = Function102996(); break;
    }
    // RET_NC ;
    if(!carry)
        return false;
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // RET;
    return true;
}

void Jumptable_102917(void){
    //dw ['Function102933'];
    //dw ['Function10294f'];
    //dw ['Function10295d'];
    //dw ['Function10296e'];
    //dw ['Function102996'];
}

bool Function102921(void){
    // LD_A_addr(wcd4a);
    // LD_HL(mJumptable_10292f);
    bool carry = true;
    // RST(aJumpTable);
    switch(wram->wcd4a) {
        case 0: carry = Function10295d(); break;
        case 1: carry = Function102984(); break;
    }
    // RET_NC ;
    if(!carry)
        return false;
    // LD_A(0);
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // RET;
    return true;
}

void Jumptable_10292f(void){
    //dw ['Function10295d'];
    //dw ['Function102984'];
}

bool Function102933(void){
    // LD_HL(mMenuHeader_1029bb);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_1029bb);
    // CALL(aFunction102e07);
    Function102e07();
    // LD_A(0x32);
    // LD_addr_A(wTextDelayFrames);
    wram->wTextDelayFrames = 0x32;
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // AND_A_A;
    // RET;
    return false;
}

bool Function10294f(void){
    // LD_A_addr(wTextDelayFrames);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wTextDelayFrames != 0)
        return false;
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // AND_A_A;
    // RET;
    return false;
}

bool Function10295d(void){
    // CALL(aFunction10299e);
    Function10299e();
    // LD_A(0);
    // LD_addr_A(wcd27);
    wram->wcd27 = 0;
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // AND_A_A;
    // RET;
    return false;
}

bool Function10296e(void){
    // FARCALL(aFunction100382);
    // AND_A_A;
    Function100382();
    // LD_A_addr(wcd27);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd27, 7))
        return false;
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // AND_A_A;
    // RET;
    return false;
}

bool Function102984(void){
    // FARCALL(aFunction100382);
    Function100382();
    // AND_A_A;
    // LD_A_addr(wcd27);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(wram->wcd27, 7))
        return false;
    // CALL(aFunction1029af);
    Function1029af();
    // SCF;
    // RET;
    return true;
}

bool Function102996(void){
    // CALL(aFunction1029af);
    Function1029af();
    // CALL(aExitMenu);
    ExitMenu();
    // SCF;
    // RET;
    return true;
}

void Function10299e(void){
    // LD_A(0x01);
    // LD_addr_A(wccb4);
    wram->wccb4 = 0x01;
    // LD_A_addr(wcd50);
    // LD_addr_A(wccb5);
    wram->wccb5[0] = wram->wcd50;
    // LD_A(0xaa);
    // LD_addr_A(wcd51);
    wram->wcd51 = 0xaa;
    // RET;
}

void Function1029af(void){
    // LD_HL(wcd4b);
    // RES_hl(7);
    bit_reset(wram->wcd4b, 7);
    // LD_A_addr(wcc61);
    // LD_addr_A(wcd51);
    wram->wcd51 = wram->wcc61[0];
    // RET;
}

const struct MenuHeader MenuHeader_1029bb = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(3, 10, 15, 12),
    .data = NULL,
    .defaultOption = 1,  // default option
};

u8_flag_s Function1029c3(void){
    // LD_A_addr(wcd4a);
    // LD_HL(mJumptable_1029cb);
    // RST(aJumpTable);
    // RET;
    switch(wram->wcd4a) {
        default:
        case 0x0: return Function1029cf();
        case 0x1: return Function1029fe();
    }
}

void Jumptable_1029cb(void){
    //dw ['Function1029cf'];
    //dw ['Function1029fe'];
}

u8_flag_s Function1029cf(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // hlcoord(10, 7, wTilemap);
    // LD_B(3);
    // LD_C(8);
    // LD_D_H;
    // LD_E_L;
    // FARCALL(av_LinkTextbox);
    v_LinkTextbox(coord(10, 7, wram->wTilemap), 3, 8);
    // LD_DE(mString_102a26);
    // hlcoord(12, 8, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_102a26), coord(12, 8, wram->wTilemap));
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // LD_DE(mMenuData3_102a33);
    // CALL(aLoad2DMenuData);
    Load2DMenuData(MenuData3_102a33);
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

u8_flag_s Function1029fe(void){
    // FARCALL(aFunction1009f3);
    // RET_C ;
    if(Function1009f3())
        return u8_flag(0xf8, true);
    // FARCALL(aMobileMenuJoypad);
    uint8_t c = MobileMenuJoypad_Conv();
    // LD_A_C;
    // LD_HL(wMenuJoypadFilter);
    // AND_A_hl;
    // RET_Z ;
    if((c & wram->wMenuJoypadFilter) == 0)
        return u8_flag(0, false);
    // PUSH_AF;
    // CALL(aExitMenu);
    ExitMenu();
    // POP_AF;
    // LD_A_addr(wMenuCursorY);
    // CP_A(0x01);
    // IF_NZ goto asm_102a21;
    if(wram->wMenuCursorY == 0x01) {
        // LD_A(0x01);
        // AND_A_A;
        // RET;
        return u8_flag(0x1, false);
    }
    else {
    // asm_102a21:
        // LD_A(0x01);
        // AND_A_A;
        // SCF;
        // RET;
        return u8_flag(0x1, true);
    }
}

const char String_102a26[] =
            "TRADE"
    t_next  "CANCEL@";

const uint8_t MenuData3_102a33[] = {
    8, 11,  // cursor start y, x
    2, 1,  // rows, columns
    0x80, 0x00,  // flags
    (2 << 4) | 0,  // cursor offset
    A_BUTTON,  // accepted buttons
};

void Function102a3b(void){
    // LD_A_addr(wcd30);
    // LD_addr_A(wc74e);
    wram->wc74e[0] = wram->wcd30;
    // LD_HL(wPlayerName);
    // LD_DE(wPlayerTrademonSenderName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPlayerTrademon.senderName, wram->wPlayerName, NAME_LENGTH);
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wPartySpecies);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wPlayerTrademonSpecies);
    wram->wPlayerTrademon.species = wram->wPartySpecies[wram->wcd4c - 1];
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_HL(wPartyMonOTs);
    // CALL(aSkipNames);
    // LD_DE(wPlayerTrademonOTName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPlayerTrademon.otName, wram->wPartyMonOT[wram->wcd4c - 1], NAME_LENGTH);
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_HL(wPartyMon1ID);
    // CALL(aGetPartyLocation);
    struct PartyMon* hl = wram->wPartyMon + (wram->wcd4c - 1);
    // LD_A_hli;
    // LD_addr_A(wPlayerTrademonID);
    // LD_A_hl;
    // LD_addr_A(wPlayerTrademonID + 1);
    wram->wPlayerTrademon.id = hl->mon.id;
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_HL(wPartyMon1DVs);
    // CALL(aGetPartyLocation);
    // LD_A_hli;
    // LD_addr_A(wPlayerTrademonDVs);
    // LD_A_hl;
    // LD_addr_A(wPlayerTrademonDVs + 1);
    wram->wPlayerTrademon.dvs = hl->mon.DVs;
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_HL(wPartyMon1Species);
    // CALL(aGetPartyLocation);
    // LD_B_H;
    // LD_C_L;
    // FARCALL(aGetCaughtGender);
    // LD_A_C;
    // LD_addr_A(wPlayerTrademonCaughtData);
    wram->wPlayerTrademon.caughtData = GetCaughtGender_Conv(&hl->mon);
    // LD_HL(wOTPlayerName);
    // LD_DE(wOTTrademonSenderName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wOTTrademon.senderName, wram->wOTPlayerName, NAME_LENGTH);

    // LD_A_addr(wcd4d);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wOTPartySpecies);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wOTTrademonSpecies);
    wram->wOTTrademon.species = wram->wOTPartySpecies[wram->wcd4d - 1];
    // LD_A_addr(wcd4d);
    // DEC_A;
    // LD_HL(wOTPartyMonOTs);
    // CALL(aSkipNames);
    // LD_DE(wOTTrademonOTName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wOTTrademon.otName, wram->wOTPartyMonOT[wram->wcd4d - 1], NAME_LENGTH);
    // LD_A_addr(wcd4d);
    // DEC_A;
    // LD_HL(wOTPartyMon1ID);
    // CALL(aGetPartyLocation);
    hl = wram->wOTPartyMon + (wram->wcd4d - 1);
    // LD_A_hli;
    // LD_addr_A(wOTTrademonID);
    // LD_A_hl;
    // LD_addr_A(wOTTrademonID + 1);
    wram->wOTTrademon.id = hl->mon.id;
    // LD_A_addr(wcd4d);
    // DEC_A;
    // LD_HL(wOTPartyMon1DVs);
    // CALL(aGetPartyLocation);
    // LD_A_hli;
    // LD_addr_A(wOTTrademonDVs);
    // LD_A_hl;
    // LD_addr_A(wOTTrademonDVs + 1);
    wram->wOTTrademon.dvs = hl->mon.DVs;
    // LD_A_addr(wcd4d);
    // DEC_A;
    // LD_HL(wOTPartyMon1Species);
    // CALL(aGetPartyLocation);
    // LD_B_H;
    // LD_C_L;
    // FARCALL(aGetCaughtGender);
    // LD_A_C;
    // LD_addr_A(wOTTrademonCaughtData);
    wram->wOTTrademon.caughtData = GetCaughtGender_Conv(&hl->mon);
    // RET;
}

// MobileTrade_StartMobileTradeAnimation
void Function102b12(void){
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames(100);
    // CALL(aFunction102d9a);
    Function102d9a();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra();
    // LD_A_addr(wcd2f);
    // AND_A_A;
    // IF_NZ goto asm_102b2b;
    if(wram->wcd2f != 0) {
    // asm_102b2b:
        // FARCALL(aFunction10802a);
        Function10802a();
    }
    else {
        // FARCALL(aFunction108026);
        Function108026();
        // goto asm_102b31;
    }

// asm_102b31:
    // RET;
}

// MobileTrade_DoEvolutionAndReturnToTradeMenu
void Function102b32(void){
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wcd4c;
    // LD_A(0x01);
    // LD_addr_A(wForceEvolution);
    wram->wForceEvolution = 0x01;
    // FARCALL(aEvolvePokemon);
    EvolvePokemon();
    // CALL(aFunction102d9a);
    Function102d9a();
    // CALL(aFunction102dd3);
    Function102dd3();
    // CALL(aFunction102dec);
    Function102dec();
    // RET;
}

void Function102b4e(void){
    // LD_A(OTPARTYMON);
    // LD_addr_A(wMonType);
    wram->wMonType = OTPARTYMON;
    // LD_A_addr(wMenuCursorY);
    // PUSH_AF;
    uint8_t cursorY = wram->wMenuCursorY;
    // LD_DE(mMenuData_102b73);
    // CALL(aLoad2DMenuData);
    Load2DMenuData(MenuData_102b73);
    // POP_AF;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = cursorY;
    // LD_A_addr(wOTPartyCount);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wOTPartyCount;
    // RET;
}

void Function102b68(void){
//  //  unreferenced
    XOR_A_A;
    LD_HL(wWindowStackPointer);
    LD_BC(0x10);
    CALL(aByteFill);
    RET;

}

const uint8_t MenuData_102b73[] = {
    9, 6,  // cursor start y, x
    (uint8_t)-1, 1,  // rows, columns
    0xa0, 0x00,  // flags
    (1 << 4) | 0,  // cursor offset
    D_UP | D_DOWN | A_BUTTON,  // accepted buttons
};

void Function102b7b(void){
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // LD_A_addr(wMenuCursorY);
    // PUSH_AF;
    uint8_t cursorY = wram->wMenuCursorY;
    // LD_DE(mMenuData_102b94);
    // CALL(aLoad2DMenuData);
    Load2DMenuData(MenuData_102b94);
    // POP_AF;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = cursorY;
    // LD_A_addr(wPartyCount);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wPartyCount;
    // RET;

}

const uint8_t MenuData_102b94[] = {
    1, 6,  // cursor start y, x
    255, 1,  // rows, columns
    0xa0, 0x00,  // flags
    (1 << 4) | 0,  // cursor offset
    D_UP | D_DOWN | A_BUTTON,  // accepted buttons
};

void Function102b9c(void){
    // LD_A_addr(wcd4d);
    // DEC_A;
    // hlcoord(6, 9, wTilemap);
    // LD_BC(0x14);
    // CALL(aAddNTimes);
    // LD_hl(0xec);
    coord(6, 9, wram->wTilemap)[(wram->wcd4d - 1) * SCREEN_WIDTH] = 0xec;
    // RET;
}

void Function102bac(void){
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wMenuCursorY - 1;
    // CALL(aLowVolume);
    LowVolume();
    // CALL(aClearSprites);
    ClearSprites();
    // FARCALL(av_MobileStatsScreenInit);
    v_MobileStatsScreenInit();
    // LD_A_addr(wCurPartyMon);
    // INC_A;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wCurPartyMon + 1;
    // CALL(aFunction102d9a);
    Function102d9a();
    // CALL(aClearPalettes);
    ClearPalettes();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aMaxVolume);
    MaxVolume();
    // CALL(aFunction102dd3);
    Function102dd3();
    // CALL(aFunction102dec);
    Function102dec();
    // CALL(aFunction102db7);
    Function102db7();
    // RET;
}

// MobileTrade_CheckIfMonIsAbnormal
bool Function102bdc(void){
    // LD_A_addr(wcd4d);
    // DEC_A;
    // LD_HL(wOTPartyMon1Species);
    // CALL(aGetPartyLocation);
    struct PartyMon* hl = wram->wOTPartyMon + (wram->wcd4d - 1);
    // PUSH_HL;
    // LD_A_addr(wcd4d);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wOTPartyCount);
    // ADD_HL_BC;
    // LD_A_hl;
    species_t a = wram->wOTPartySpecies[wram->wcd4d - 1];
    // POP_HL;
    // CP_A(EGG);
    // IF_Z goto asm_102bfa;
    // CP_A_hl;
    // IF_NZ goto asm_102c05;
    if(a != EGG && a != hl->mon.species)
        return true;

// asm_102bfa:
    // LD_BC(MON_LEVEL);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(MAX_LEVEL + 1);
    // IF_NC goto asm_102c05;
    if(hl->mon.level > MAX_LEVEL)
        return true;
    // AND_A_A;
    // RET;
    return false;

// asm_102c05:
    // SCF;
    // RET;
}

// MobileTrade_SwapData
void Function102c07(void){
    // CALL(aFunction102c14);
    Function102c14();
    // CALL(aFunction102c3b);
    Function102c3b();
    // CALL(aFunction102c21);
    Function102c21();
    // CALL(aFunction102c2e);
    Function102c2e();
    // RET;
}

// MobileTrade_SwapPartySpeciesData
void Function102c14(void){
    // LD_HL(wPartySpecies);
    // LD_DE(wOTPartySpecies);
    // LD_BC(1);
    // CALL(aFunction102c71);
    Function102c71(wram->wOTPartySpecies, wram->wPartySpecies, sizeof(wram->wPartySpecies[0]));
    // RET;
}

// MobileTrade_SwapPartyMonNicknameData
void Function102c21(void){
    // LD_HL(wPartyMonNicknames);
    // LD_DE(wOTPartyMonNicknames);
    // LD_BC(11);
    // CALL(aFunction102c71);
    Function102c71(wram->wOTPartyMonNickname, wram->wPartyMonNickname, sizeof(wram->wPartyMonNickname[0]));
    // RET;
}

// MobileTrade_SwapPartyMonOTData
void Function102c2e(void){
    // LD_HL(wPartyMonOTs);
    // LD_DE(wOTPartyMonOTs);
    // LD_BC(11);
    // CALL(aFunction102c71);
    Function102c71(wram->wOTPartyMonOT, wram->wPartyMonOT, sizeof(wram->wPartyMonOT[0]));
    // RET;
}

// MobileTrade_SwapPartyMonData
void Function102c3b(void){
    // LD_HL(wPartyMon1);
    // LD_DE(wOTPartyMon1);
    // LD_BC(0x30);
    // CALL(aFunction102c71);
    Function102c71(wram->wOTPartyMon, wram->wPartyMon, sizeof(wram->wPartyMon[0]));
    // RET;
}

void Function102c48(void){
    // FARCALL(aFunction10165a);
    Function10165a();
    // LD_A(0);
    // CALL(aOpenSRAM);
    OpenSRAM(0);
    // LD_HL(0xa600);
    // LD_DE(wc608);
    // LD_BC(0x2f);
    // CALL(aFunction102c71);
    Function102c71(GBToRAMAddr(0xa600), wram->wc608, 0x2f);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_HL(wc608);
    // LD_DE(w5_da00);
    // LD_BC(0x1e0);
    // LD_A(0x05);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->w5_da00, wram->wc608, 0x1e0);
    // RET;
}

void Function102c71(void* de, void* hl, uint16_t bc){
    // LD_A_addr(wcd4c);
    // DEC_A;
    // CALL(aAddNTimes);
    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // LD_A_addr(wcd4d);
    // DEC_A;
    // CALL(aAddNTimes);
    // POP_DE;
    // CALL(aSwapBytes);
    SwapBytes((uint8_t*)hl + (wram->wcd4c - 1) * bc, (uint8_t*)de + (wram->wcd4d - 1) * bc, bc);
    // RET;
}

void Function102c87(void){
    // LD_A_addr(wJumptableIndex);
    // PUSH_AF;
    uint8_t jumptableIndex = wram->wJumptableIndex;
    // LD_A_addr(wcf64);
    uint8_t cf64 = wram->wcf64;
    // PUSH_AF;
    // LD_A_addr(wcd4c);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = wram->wcd4c;
    // LD_A_addr(wPartyCount);
    // LD_addr_A(wcf64);
    wram->wcf64 = wram->wPartyCount;
    // LD_A(0);
    OpenSRAM(MBANK(asPartyMon1MailMessage));
    // LD_HL(0xa600);
    // LD_DE(wc608);
    // LD_BC(0x11a);
    // CALL(aFunction102d3e);
    CopyBytes(wram->wc608, GBToRAMAddr(sPartyMon1MailMessage), 0x11a);
    CloseSRAM();
    // CALL(aFunction102cee);
    Function102cee();
    // LD_A(0);
    OpenSRAM(MBANK(asPartyMon1MailMessage));
    // LD_HL(wc608);
    // LD_DE(0xa600);
    // LD_BC(0x11a);
    // CALL(aFunction102d3e);
    CopyBytes(GBToRAMAddr(sPartyMon1MailMessage), wram->wc608, 0x11a);
    CloseSRAM();
    // LD_A_addr(wcd4d);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = wram->wcd4d;
    // LD_A_addr(wOTPartyCount);
    // LD_addr_A(wcf64);
    wram->wcf64 = wram->wOTPartyCount;
    // LD_A(0x05);
    // LD_HL(w5_da00);
    // LD_DE(wc608);
    // LD_BC(0x11a);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wc608, wram->w5_da00, 0x11a);
    // CALL(aFunction102cee);
    Function102cee();
    // LD_A(0x05);
    // LD_HL(wc608);
    // LD_DE(w5_da00);
    // LD_BC(0x11a);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->w5_da00, wram->wc608, 0x11a);
    // POP_AF;
    // LD_addr_A(wcf64);
    wram->wcf64 = cf64;
    // POP_AF;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = jumptableIndex;
    // RET;
}

void Function102cee(void){
    // LD_A_addr(wJumptableIndex);
    // DEC_A;
    // CALL(aFunction102d34);
    // LD_DE(wd002);
    // LD_BC(0x2f);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wd002, Function102d34(wram->wJumptableIndex - 1), 0x2f);
    // LD_A_addr(wJumptableIndex);
    // LD_C_A;
    // LD_A(0x06);
    // SUB_A_C;
    // RET_Z ;
    if(wram->wJumptableIndex == 0x6)
        return;
    // LD_BC(0x2f);
    // LD_HL(0);
    // CALL(aAddNTimes);
    // PUSH_HL;
    uint16_t hl = (0x2f * (0x6 - wram->wJumptableIndex));
    // LD_A_addr(wJumptableIndex);
    // DEC_A;
    // CALL(aFunction102d34);
    // LD_D_H;
    // LD_E_L;
    uint8_t* de = Function102d34(wram->wJumptableIndex - 1);
    // LD_HL(0x2f);
    // ADD_HL_DE;
    // POP_BC;
    // CALL(aCopyBytes);
    CopyBytes(de, de + 0x2f, hl);
    // LD_A_addr(wcf64);
    // DEC_A;
    // CALL(aFunction102d34);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wd002);
    // LD_BC(0x2f);
    // CALL(aCopyBytes);
    CopyBytes(Function102d34(wram->wcf64 - 1), &wram->wd002, 0x2f);
    // RET;
}

uint8_t* Function102d34(uint8_t a){
    // LD_HL(wc608);
    // LD_BC(0x2f);
    // CALL(aAddNTimes);
    // RET;
    return wram->wc608 + (0x2f * a);
}

// void Function102d3e(uint32_t de, uint8_t* hl, uint16_t bc){
    // CALL(aOpenSRAM);
    // OpenSRAM(MBANK(de));
    // CALL(aCopyBytes);
    // CopyBytes(GBToRAMAddr(de & 0xffff), hl, bc);
    // CALL(aCloseSRAM);
    // CloseSRAM();
    // RET;
// }

void Function102d48(void){
    // LD_A_addr(wcd4c);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPartyCount);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wTempSpecies);
    wram->wTempSpecies = wram->wPartySpecies[wram->wcd4c - 1];
    // CP_A(EGG);
    // IF_Z goto asm_102d6d;
    if(wram->wTempSpecies != EGG) {
        // DEC_A;
        // CALL(aSetSeenAndCaughtMon);
        SetSeenAndCaughtMon(wram->wTempSpecies - 1);
        // LD_A_addr(wcd4c);
        // DEC_A;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_HL(wPartyMon1Happiness);
        // CALL(aAddNTimes);
        // LD_hl(BASE_HAPPINESS);
        wram->wPartyMon[wram->wcd4c - 1].mon.happiness = BASE_HAPPINESS;
    }

// asm_102d6d:
    // LD_A_addr(wTempSpecies);
    // CP_A(UNOWN);
    // IF_NZ goto asm_102d98;
    if(wram->wTempSpecies == UNOWN) {
        // LD_A_addr(wcd4c);
        // DEC_A;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_HL(wPartyMon1DVs);
        // CALL(aAddNTimes);
        // PREDEF(pGetUnownLetter);
        unown_letter_t letter = GetUnownLetter(wram->wPartyMon[wram->wcd4c - 1].mon.DVs);
        // FARCALL(aUpdateUnownDex);
        UpdateUnownDex_Conv(letter);
        // LD_A_addr(wFirstUnownSeen);
        // AND_A_A;
        // IF_NZ goto asm_102d98;
        // LD_A_addr(wUnownLetter);
        // LD_addr_A(wFirstUnownSeen);
        if(wram->wFirstUnownSeen == 0)
            wram->wFirstUnownSeen = letter;
    }

// asm_102d98:
    // AND_A_A;
    // RET;
}

// Mobile_BlankTilemapAndAttrmap
void Function102d9a(void){
    // LD_A(0x7f);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // LD_A(0x07);
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x07);
    // FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    HDMATransferAttrmapAndTilemapToWRAMBank3();
    // RET;
}

void Function102db7(void){
    // CALL(aFunction102e4f);
    Function102e4f();
    // CALL(aFunction102e3e);
    Function102e3e();
    // LD_HL(wcd4b);
    // SET_hl(1);
    bit_set(wram->wcd4b, 1);
    // RET;
}

// DrawLinkTextbox
void Function102dc3(void){
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(18);
    // LD_D_H;
    // LD_E_L;
    // FARCALL(av_LinkTextbox);
    v_LinkTextbox(coord(0, 12, wram->wTilemap), 4, 18);
    // RET;
}

// MobileComms_LoadTradeLightsGFX
void Function102dd3(void){
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_DE(mMobileTradeLightsGFX);
    // LD_HL(vTiles0);
    // LD_BC((BANK(aMobileTradeLightsGFX) << 8) | 4);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0, MobileTradeLightsGFX, 0, 4);
    // FARCALL(av__LoadTradeScreenBorderGFX);
    v__LoadTradeScreenBorderGFX();
    // CALL(aEnableLCD);
    EnableLCD();
    // RET;
}

// LoadMobileTradePalettes
void Function102dec(void){
    // LD_HL(mMobileTradeLightsPalettes);
    // LD_DE(wOBPals1);
    // LD_BC(4 * PALETTE_SIZE);
    // LD_A(0x05);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wOBPals1, MobileTradeLightsPalettes, 4 * PALETTE_SIZE);
    // FARCALL(aFunction49742);
    Function49742();
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

// Mobile_DrawWaitingText
void Function102e07(void){
static const char waiting[] = "Waiting...!@";
    // hlcoord(3, 10, wTilemap);
    // LD_B(1);
    // LD_C(11);
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // IF_Z goto link_battle;
    if(wram->wBattleMode != 0) {
        // CALL(aTextbox);
        Textbox(coord(3, 10, wram->wTilemap), 1, 11);
        // goto okay;
    }
    else {
    // link_battle:
    //  the next three operations are pointless
        // hlcoord(3, 10, wTilemap);
        // LD_B(1);
        // LD_C(11);
        // LD_D_H;
        // LD_E_L;
        // FARCALL(av_LinkTextbox);
        v_LinkTextbox(coord(3, 10, wram->wTilemap), 1, 11);
    }

// okay:
    // LD_DE(mFunction102e07_waiting);
    // hlcoord(4, 11, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(waiting), coord(4, 11, wram->wTilemap));
    // RET;
}

// DrawCancelString
void Function102e3e(void){
static const char CancelString[] = "CANCEL@";
    // LD_DE(mFunction102e3e_CancelString);
    // hlcoord(10, 17, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(CancelString), coord(10, 17, wram->wTilemap));
    // RET;
}

static void Function102e4f_PlaceSpeciesNames(tile_t* hl, const species_t* de){
    // LD_C(0);
    uint8_t c = 0;

    while(*de != 0xff) {
    // count_loop:
        // LD_A_de;
        // CP_A(0xff);
        // RET_Z ;
        // LD_addr_A(wNamedObjectIndex);
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_HL;
        // LD_A_C;
        // LDH_addr_A(hDividend);
        // CALL(aGetPokemonName);
        // POP_HL;
        // CALL(aPlaceString);
        PlaceStringSimple(GetPokemonName(*de), hl);
        // POP_DE;
        // INC_DE;
        de++;
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        hl += SCREEN_WIDTH;
        // ADD_HL_BC;
        // POP_BC;
        // INC_C;
        c++;
        // goto count_loop;
    }
}

// LayoutMobileTradeScreen?
void Function102e4f(void){
    // FARCALL(aLoadMobileTradeBorderTilemap);
    LoadMobileTradeBorderTilemap();
    // FARCALL(av_InitMG_Mobile_LinkTradePalMap);
    v_InitMG_Mobile_LinkTradePalMap();
    // LD_DE(wPlayerName);
    // hlcoord(4, 0, wTilemap);
    struct TextPrintState st = {.de = wram->wPlayerName, .hl = coord(4, 0, wram->wTilemap)};
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_A(0x14);
    // LD_bc_A;
    *st.bc = 0x14;
    // LD_DE(wOTPlayerName);
    st.de = wram->wOTPlayerName;
    // hlcoord(4, 8, wTilemap);
    st.hl = coord(4, 8, wram->wTilemap);
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_A(0x14);
    // LD_bc_A;
    *st.bc = 0x14;
    // hlcoord(7, 1, wTilemap);
    // LD_DE(wPartySpecies);
    // CALL(aFunction102e4f_PlaceSpeciesNames);
    Function102e4f_PlaceSpeciesNames(coord(7, 1, wram->wTilemap), wram->wPartySpecies);
    // hlcoord(7, 9, wTilemap);
    // LD_DE(wOTPartySpecies);
    // CALL(aFunction102e4f_PlaceSpeciesNames);
    Function102e4f_PlaceSpeciesNames(coord(7, 9, wram->wTilemap), wram->wOTPartySpecies);
    // RET;
}

void Function102ea8(void){
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_A_addr(wcd4c);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wPartySpecies);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wStringBuffer2);
    // LD_BC(11);
    // CALL(aCopyBytes);
    CopyBytes(wram->wStringBuffer2, GetPokemonName(wram->wPartySpecies[wram->wcd4c - 1]), NAME_LENGTH);
    // LD_A_addr(wcd4d);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wOTPartySpecies);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wOTPartySpecies[wram->wcd4d - 1]);
    // LD_HL(mTradingMonForOTMonText);
    // CALL(aPrintTextboxText);
    PrintTextboxText(TradingMonForOTMonText);
    // RET;
}

const txt_cmd_s TradingMonForOTMonText[] = {
    text_far(v_TradingMonForOTMonText)
    text_end
};

// Mobile_DrawTradeWasCancelledText
void Function102ee7(void){
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mString_102ef4);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_102ef4), coord(1, 14, wram->wTilemap));
    // RET;
}

const char String_102ef4[] =
            "Too bad! The trade"
    t_next  "was canceled!@";

void Function102f15(void){
    static const char TooBadTheTradeWasCanceled[] = 
            "The trade was" //db ['"こうかんを\u3000キャンセルしました@"'];
    t_next  "canceled!";

    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mFunction102f15_TooBadTheTradeWasCanceled);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(TooBadTheTradeWasCanceled), coord(1, 14, wram->wTilemap));
    // RET;
}

// Mobile_DrawTradeCompletedText
void Function102f32(void){
static const char TradeCompleted[] = "Trade completed!@";
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mFunction102f32_TradeCompleted);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(TradeCompleted), coord(1, 14, wram->wTilemap));
    // RET;
}

void Function102f50(void){
    static const char PleaseWait[] = 
                "Please wait a"
        t_next  "moment..."; //db ['"しょうしょう\u3000おまち\u3000ください@"'];
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mFunction102f50_PleaseWait);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(PleaseWait), coord(1, 14, wram->wTilemap));
    // RET;
}

void Function102f6d(void){
    static const char Finished[] = "Finishing trade..."; //db ['"しゅうりょう\u3000します@"'];
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mFunction102f6d_Finished);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Finished), coord(1, 14, wram->wTilemap));
    // RET;
}

const txt_cmd_s MobileTrade_Text_YourFriendsMonIsAbnormal[] = {
    text_start(String_102fdb)
    text_end
};

void Function102f85(void){
    // LD_A_addr(wd003);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wOTPartySpecies);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wOTPartySpecies[wram->wd003]);
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mString_102fb2);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    // LD_DE(wStringBuffer1);
    // hlcoord(13, 14, wTilemap);
    // CALL(aPlaceString);
    // LD_DE(mString_102fcc);
    // CALL(aPlaceString);
    PlaceHLTextAtBC(coord(1, 14, wram->wTilemap), MobileTrade_Text_YourFriendsMonIsAbnormal);
    // RET;
}

void String_102fb2(void){
    //db ['"あいてがわ<PKMN>えらんだ\u3000"'];
    //next ['"いじょう<PKMN>あるようです！！"']
    //db ['"@"'];

    return String_102fcc();
}

void String_102fcc(void){
    //db ['"に@"'];

    return Function102fce();
}

// MobileTrade_ShowLinkString_YourFriendsMonIsAbnormal
void Function102fce(void){
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mString_102fdb);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_102fdb), coord(1, 14, wram->wTilemap));
    // RET;
}

const char String_102fdb[] = 
            "Your friend's"     // "あいてがわ<NO>せんたくに"
    t_next  "#MON appears"      //next "いじょう<PKMN>あるようです！！"
    t_cont  "to be abnormal!"
    t_done;                     //done ['?']

// MobileTrade_ShowLinkString_ThatsYourLastMon
void Function102ff5(void){
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mString_103002);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_103002), coord(1, 14, wram->wTilemap));
    // RET;
}

const char String_103002[] = 
            "If you trade that"     //db ['"その#を\u3000こうかんすると"'];
    t_next  "#MON, you won't"       //next ['"せんとう\u3000できなく\u3000なっちゃうよ！"']
    t_cont  "be able to battle.";   //db ['"@"'];

// MobileTrade_ShowLinkString_YourFriendEndedTheTrade
void Function103021(void){
    // CALL(aFunction102dc3);
    Function102dc3();
    // LD_DE(mString_10302e);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_10302e), coord(1, 14, wram->wTilemap));
    // RET;
}

const char String_10302e[] =
            "Your friend"   //db ['"あいてが\u3000ちゅうしを\u3000えらんだので"'];
    t_next  "chose to end"  //next ['"こうかんを\u3000ちゅうし\u3000します"']
    t_cont  "the trade.";   //db ['"@"'];

void Function10304f(void){
    // XOR_A_A;
    // LD_addr_A(wAttrmapEnd);
    wram->wAttrmapEnd = 0;
    // LD_addr_A(wcf42);
    wram->wcf42 = 0;
    // LD_addr_A(wcf44);
    wram->wcf44 = 0;
    // LD_addr_A(wcf45);
    wram->wcf45 = 0;
    // RET;
}

void Function10305d(void){
    // NOP;
    // LD_A_addr(wAttrmapEnd);
    // AND_A_A;
    // RET_Z ;
    if(wram->wAttrmapEnd == 0)
        return;
    // CALL(aFunction10307f);
    // RET_C ;
    if(Function10307f())
        return;
    // CALL(aFunction103094);
    Function103094();
    // CALL(aFunction10306e);
    Function10306e();
    // RET;
}

void Function10306e(void){
    // LD_A(0x01);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x1;
    // CALL(aClearSprites);
    ClearSprites();
    // LD_DE(wVirtualOAM);
    // CALL(aFunction1030cd);
    Function1030cd(wram->wVirtualOAMSprite);
    // XOR_A_A;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x0;
    // RET;
}

bool Function10307f(void){
    // LD_C(0x02);
    // LD_HL(wcd4b);
    // BIT_hl(7);
    // IF_Z goto asm_10308a;
    // LD_C(0x01);

// asm_10308a:
    uint8_t c = (!bit_test(wram->wcd4b, 7))? 0x02: 0x01;
    // LD_HL(wcf45);
    // INC_hl;
    // LD_A_hl;
    // CP_A_C;
    // RET_C ;
    if(++wram->wcf45 < c)
        return true;
    // XOR_A_A;
    // LD_hl_A;
    wram->wcf45 = 0;
    // RET;
    return false;
}

void Function103094(void){
    // LD_HL(wcd4b);
    // BIT_hl(7);
    // IF_NZ goto asm_1030c0;
    if(bit_test(wram->wcd4b, 7)) {
    // asm_1030c0:
        // LD_HL(wcf44);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto asm_1030ca;
        if(wram->wcf44 != 0) {
            // DEC_A;
            // LD_hl_A;
            // RET_NZ ;
            if(--wram->wcf44 != 0)
                return;
        }
    
    // asm_1030ca:
        // LD_hl(0x2c);
        wram->wcf44 = 0x2c;
        // RET;
        return;
    }
    // LD_A_addr(wcf42);
    // BIT_A(7);
    // IF_NZ goto asm_1030b2;
    else if(bit_test(wram->wcf42, 7)) {
    // asm_1030b2:
        // LD_A_addr(wcf44);
        // DEC_A;
        // LD_addr_A(wcf44);
        // RET_NZ ;
        if(--wram->wcf44 != 0)
            return;
        // LD_HL(wcf42);
        // RES_hl(7);
        bit_reset(wram->wcf42, 7);
        // RET;
        return;
    }
    else {
        // LD_A_addr(wcf44);
        // INC_A;
        // LD_addr_A(wcf44);
        // CP_A(0x2c);
        // RET_NZ ;
        if(++wram->wcf44 != 0x2c)
            return;
        // LD_HL(wcf42);
        // SET_hl(7);
        bit_set(wram->wcf42, 7);
        // RET;
        return;
    }
}

void Function1030cd(struct SpriteOAM* de){
    // LD_A_addr(wcf44);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_BC(mUnknown_103112);
    // ADD_HL_BC;
    const uint8_t* hl = Unknown_103112;
    // LD_B(0x30);
    uint8_t b = 0x30;
    // LD_C(0x08);
    uint8_t c = 0x08;

    do {
    // asm_1030de:
        // PUSH_HL;
        // LD_HL(wcd4b);
        // BIT_hl(7);
        // POP_HL;
        // LD_A(0);
        // IF_Z goto asm_1030eb;
        // LD_A(0x05);

    // asm_1030eb:
        uint8_t a = (!bit_test(wram->wcd4b, 7))? 0: 5;

        // ADD_A_hl;
        a += *hl;
        // INC_HL;
        hl++;
        // PUSH_HL;

        // ADD_A_A;
        // ADD_A_A;

        // ADD_A(LOW(aUnknown_10327a));
        // LD_L_A;
        // LD_A(HIGH(aUnknown_10327a));
        // ADC_A(0);
        // LD_H_A;
        const struct SpriteOAM* hl2 = Unknown_10327a + a;

        // LD_A_B;
        // ADD_A_hl;
        // INC_HL;
        // LD_de_A;
        // INC_DE;
        de->yCoord = b + hl2->yCoord;
        // LD_A(0x0a);
        // ADD_A_hl;
        // INC_HL;
        // LD_de_A;
        // INC_DE;
        de->xCoord = hl2->xCoord + 0x0a;
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        de->tileID = hl2->tileID;
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        de->attributes = hl2->attributes;
        de++;
        // POP_HL;
        // LD_A_B;
        // ADD_A(0x08);
        // LD_B_A;
        b += 8;
        // DEC_C;
        // IF_NZ goto asm_1030de;
    } while(--c != 0);
    // RET;
}

const uint8_t Unknown_103112[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x04, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00,
    0x04, 0x04, 0x04, 0x03, 0x02, 0x01, 0x00, 0x00,
    0x04, 0x04, 0x04, 0x04, 0x03, 0x02, 0x01, 0x00,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x02, 0x01,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x02,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x02, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x01, 0x02, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x04, 0x04, 0x04,
    0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x04, 0x04,
    0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const struct SpriteOAM Unknown_10327a[] = {
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x00, .attributes=0x00},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x01, .attributes=0x00},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x02, .attributes=0x00},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x03, .attributes=0x00},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x01, .attributes=0x01},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x00, .attributes=0x00},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x01, .attributes=0x02},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x02, .attributes=0x02},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x03, .attributes=0x02},
    {.yCoord=0x00, .xCoord=0x00, .tileID=0x01, .attributes=0x03},
};

const char MobileTradeLightsGFX[] = "gfx/mobile/mobile_trade_lights.png"; // 2bpp

const uint16_t MobileTradeLightsPalettes[] = {
// INCLUDE "gfx/mobile/mobile_trade_lights.pal"
    rgb( 0,  0,  0),
    rgb(31, 31,  7),
    rgb(20, 31,  6),
    rgb(13, 20, 16),

    rgb( 0,  0,  0),
    rgb( 7, 11, 17),
    rgb( 0,  0,  0),
    rgb( 0,  0,  0),

    rgb( 0,  0,  0),
    rgb(31, 24,  4),
    rgb(25, 12,  0),
    rgb(31,  7,  4),

    rgb( 0,  0,  0),
    rgb(25,  0,  0),
    rgb( 0,  0,  0),
    rgb( 0,  0,  0),
};

bool Function103302(void){
    // CALL(aFunction103309);
    Function103309();
    // CALL(aFunction103362);
    // RET;
    return Function103362();
}

void Function103309(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_HL(wd1ea);
    // LD_BC(10);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(&wram->wd1ea, 10, 0);
    // LD_A(BANK(s4_a60c));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as4_a60c));
    // LD_A_addr(wdc41);
    // LD_addr_A(s4_a60c);
    gb_write(s4_a60c, wram->wdc41);
    // LD_addr_A(wd1ea);
    wram->wd1ea = wram->wdc41;
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aFunction1035c6);
    const Unknown_1035d7_s* data = Function1035c6();
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_addr_A(wd1ef);
    wram->wd1ef = data->n;
    // LD_A_hli;
    // LD_addr_A(wd1ec);
    // LD_A_hli;
    // LD_addr_A(wd1ed);
    gMobile_wd1ec = data->hl;
    // LD_H_D;
    // LD_L_E;
    // CALL(aFunction3eea);
    Function3eea(wram->wTilemap + data->de, data->b, data->c);
    // LD_HL(wd1ec);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_hl;
    // LD_addr_A(wd1ee);
    wram->wd1ee = data->hl[0];
    // CALL(aFunction1034be);
    Function1034be(data->hl);
    // CALL(aUpdateSprites);
    UpdateSprites();
    // FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    HDMATransferAttrmapAndTilemapToWRAMBank3();
    // LD_A(0x01);
    // LD_addr_A(wd1f0);
    wram->wd1f0 = 0x1;
    // CALL(aFunction10339a);
    Function10339a();
    // RET;
}

bool Function103362(void){
    do {
    // asm_103362:
        // LD_A_addr(wd1f0);
        // LD_addr_A(wd1f1);
        wram->wd1f1 = wram->wd1f0;
        // CALL(aFunction1033af);
        Function1033af();
        // CALL(aFunction10339a);
        Function10339a();
        // CALL(aFunction10342c);
        Function10342c();
        // FARCALL(aHDMATransferTilemapToWRAMBank3);
        HDMATransferTilemapToWRAMBank3();
        // LD_A_addr(wd1eb);
        // BIT_A(7);
        // IF_Z goto asm_103362;
    } while(!bit_test(wram->wd1eb, 7));
    // LD_HL(wd1eb);
    // BIT_hl(6);
    // IF_Z goto asm_103398;
    if(bit_test(wram->wd1eb, 6)) {
        // LD_A(BANK(s4_a60c));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(as4_a60c));
        // LD_A_addr(wd1ea);
        // LD_addr_A(s4_a60c);
        gb_write(s4_a60c, wram->wd1ea);
        // LD_addr_A(wdc41);
        wram->wdc41 = wram->wd1ea;
        // CALL(aCloseSRAM);
        CloseSRAM();
        // XOR_A_A;
        // RET;
        return false;
    }
    else {
    // asm_103398:
        // SCF;
        // RET;
        return true;
    }
}

void Function10339a(void){
    // LD_A_addr(wd1f0);
    // LD_addr_A(wd1f2);
    wram->wd1f2 = wram->wd1f0;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wd1ec);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wd1f3);
    wram->wd1f3 = gMobile_wd1ec[wram->wd1f0];
    // RET;
}

void Function1033af(void){
    // CALL(aGetJoypad);
    GetJoypad();
    // LDH_A_addr(hJoyPressed);
    // BIT_A(D_LEFT_F);
    // IF_NZ goto left;
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto right;
    if(bit_test(hram->hJoyPressed, D_LEFT_F)
    || bit_test(hram->hJoyPressed, D_RIGHT_F)) {
    // left:
    // right:
    a_return:
        // LD_A_addr(wd1f3);
        // CP_A(3);
        // RET_Z ;
        if(wram->wd1f3 == 3)
            return;
        // LD_DE(SFX_PUSH_BUTTON);
        // CALL(aPlaySFX);
        PlaySFX(SFX_PUSH_BUTTON);
        // LD_BC(8);
        // CALL(aFunction10350f);
        // LD_A_addr(wd1ea);
        // XOR_A_E;
        // LD_addr_A(wd1ea);
        wram->wd1ea ^= Unknown_103522[wram->wd1f3].n;
        // RET;
        return;
    }
    // BIT_A(B_BUTTON_F);
    // IF_NZ goto b;
    else if(bit_test(hram->hJoyPressed, B_BUTTON_F)) {
    // b:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_HL(wd1eb);
        // SET_hl(7);
        bit_set(wram->wd1eb, 7);
        // RET;
        return;
    }
    // BIT_A(A_BUTTON_F);
    // IF_NZ goto a;
    else if(bit_test(hram->hJoyPressed, A_BUTTON_F)) {
    // a:
        // LD_A_addr(wd1f3);
        // CP_A(3);
        // IF_NZ goto a_return;
        if(wram->wd1f3 != 3)
            goto a_return;
        // LD_DE(SFX_TRANSACTION);
        // CALL(aPlaySFX);
        PlaySFX(SFX_TRANSACTION);
        // LD_HL(wd1eb);
        // SET_hl(7);
        // LD_HL(wd1eb);
        // SET_hl(6);
        wram->wd1eb |= ((1 << 7) | (1 << 6));
        // RET;    
        return;
    }
    // BIT_A(D_UP_F);
    // IF_NZ goto up;
    else if(bit_test(hram->hJoyPressed, D_UP_F)) {
    // up:
        // LD_A_addr(wd1f0);
        // DEC_A;
        // LD_addr_A(wd1f0);
        wram->wd1f0--;
        // CP_A(1);
        // RET_NC ;
        if(wram->wd1f0 >= 1)
            return;
        // LD_A_addr(wd1ee);
        // LD_addr_A(wd1f0);
        wram->wd1f0 = wram->wd1ee;
        // RET;
        return;
    }
    // BIT_A(D_DOWN_F);
    // IF_NZ goto down;
    else if(bit_test(hram->hJoyPressed, D_DOWN_F)) {
    // down:
        // LD_A_addr(wd1f0);
        // INC_A;
        // LD_addr_A(wd1f0);
        wram->wd1f0++;
        // LD_C_A;
        // LD_A_addr(wd1ee);
        // CP_A_C;
        // RET_NC ;
        if(wram->wd1ee >= wram->wd1f0)
            return;
        // LD_A(1);
        // LD_addr_A(wd1f0);
        wram->wd1f0 = 1;
        // RET;
    }
    // RET;
    return;
}

void Function10342c(void){
    // LD_A_addr(wd1f0);
    // LD_addr_A(wd1f2);
    wram->wd1f2 = wram->wd1f0;
    // CALL(aFunction103490);
    Function103490();
    // CALL(aFunction10343c);
    Function10343c();
    // CALL(aFunction1034a7);
    Function1034a7();
    // RET;
}

void Function10343c(void){
    // LD_A_addr(wd1f3);
    // CP_A(0x02);
    // IF_NZ goto asm_103452;
    if(wram->wd1f3 == 0x2) {
        // LD_BC(1);
        // CALL(aFunction1034f7);
        // LD_C(0x12);
        // LD_B(0x01);
        // CALL(aFunction1034e0);
        Function1034e0(Function1034f7(1), 0x01, 0x12);
        // goto asm_10345f;
    }
    else {
    // asm_103452:
        // LD_BC(0xffed);
        // CALL(aFunction1034f7);
        // LD_C(0x12);
        // LD_B(0x02);
        // CALL(aFunction1034e0);
        Function1034e0(Function1034f7(-19), 0x02, 0x01);
    }

// asm_10345f:
    // LD_BC(0);
    // CALL(aFunction10350f);
    const char* title = Function10350f(0);
    // LD_BC(1);
    // CALL(aFunction103487);
    Function103487(title, 1);
    // LD_BC(8);
    // CALL(aFunction10350f);
    uint8_t e = Unknown_103522[wram->wd1f3].n;
    // LD_A_addr(wd1ea);
    // AND_A_E;
    // LD_BC(2);
    // IF_Z goto asm_10347d;
    // LD_BC(4);

// asm_10347d:
    uint16_t bc = (wram->wd1ea & e)? 4: 2;
    // CALL(aFunction10350f);
    const char* opt = Function10350f(bc);
    // LD_BC(11);
    // CALL(aFunction103487);
    Function103487(opt, 14);
    // RET;
}

void Function103487(const char* de, uint16_t bc){
    // PUSH_DE;
    // CALL(aFunction1034f7);
    // POP_DE;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(de), wram->wTilemap + Function1034f7((int16_t)bc));
    // RET;
}

void Function103490(void){
    // hlcoord(0, 15, wTilemap);
    // LD_C(0x14);
    // LD_B(0x03);
    // CALL(aFunction1034e0);
    Function1034e0(coord(0, 15, 0), 0x03, 0x14);
    // LD_BC(6);
    // CALL(aFunction10350f);
    const char* desc = Function10350f(6);
    // hlcoord(1, 16, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(desc), coord(1, 16, wram->wTilemap));
    // RET;
}

void Function1034a7(void){
    // LD_A_addr(wd1f1);
    // LD_addr_A(wd1f2);
    wram->wd1f2 = wram->wd1f1;
    // LD_BC(10);
    // CALL(aFunction1034f7);
    // LD_hl(0x7f);
    wram->wTilemap[Function1034f7(1)] = 0x7f;
    // LD_BC(10);
    // CALL(aFunction1034f1);
    // LD_hl(0xed);
    wram->wTilemap[Function1034f1(1)] = 0xed;
    // RET;
}

void Function1034be(const uint8_t* hl){
    // LD_A(0x01);
    // LD_addr_A(wd1f2);
    wram->wd1f2 = 0x1;
    // LD_HL(wd1ec);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_hli;
    uint8_t a = *(hl++);

    do {
    // asm_1034ca:
        // PUSH_AF;
        // LD_A_hli;
        // PUSH_HL;
        // LD_addr_A(wd1f3);
        wram->wd1f3 = *(hl++);
        // CALL(aFunction10343c);
        Function10343c();
        // LD_HL(wd1f2);
        // INC_hl;
        wram->wd1f2++;
        // POP_HL;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_1034ca;
    } while(--a != 0);
    // CALL(aFunction103490);
    Function103490();
    // RET;

}

void Function1034e0(uint16_t hl, uint8_t b, uint8_t c){
    // PUSH_BC;
    // PUSH_HL;
    // CALL(aClearBox);
    ClearBox(wram->wTilemap + hl, c, b);
    // POP_HL;
    // LD_BC(wAttrmap - wTilemap);
    // ADD_HL_BC;
    // POP_BC;
    // LD_A(0x06);
    // CALL(aFillBoxWithByte);
    FillBoxWithByte(wram->wAttrmap + hl, c, b, 0x6);
    // RET;
}

uint16_t Function1034f1(uint16_t bc){
    // LD_A_addr(wd1f0);
    // LD_addr_A(wd1f2);
    wram->wd1f2 = wram->wd1f0;

    return Function1034f7(bc);
}

uint16_t Function1034f7(int16_t bc){
    // hlcoord(0, 0, wTilemap);
    // ADD_HL_BC;
    // LD_A_addr(wd1ef);
    // LD_BC(SCREEN_WIDTH);
    // CALL(aAddNTimes);
    // LD_A_addr(wd1f2);
    // DEC_A;
    // LD_BC(40);
    // CALL(aAddNTimes);
    // RET;
    return coord(0, 0, 0) + (wram->wd1ef * SCREEN_WIDTH) + ((wram->wd1f2 - 1) * SCREEN_WIDTH*2) + bc;
}

const char* Function10350f(uint16_t bc){
    // LD_A_addr(wd1f3);
    // PUSH_BC;
    // LD_HL(mUnknown_103522);
    // LD_BC(9);
    // CALL(aAddNTimes);
    // POP_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // RET;
    switch(bc) {
        default:
        case 0: return Unknown_103522[wram->wd1f3].title;
        case 2: return Unknown_103522[wram->wd1f3].opt1;
        case 4: return Unknown_103522[wram->wd1f3].opt2;
        case 6: return Unknown_103522[wram->wd1f3].desc;
    }
    return NULL;
}

const Unknown_103522_s Unknown_103522[] = {
    {
        String_103546,
        String_103598,
        String_1035a0,
        String_10355f,
        0x01,
    },
    {
        String_10354f,
        String_1035a8,
        String_1035b1,
        String_103571,
        0x02,
    },
    {
        String_103557,
        String_1035ba,
        String_1035bd,
        String_103585,
        0x04,
    },
    {
        String_103545,
        String_1035c1,
        String_1035c1,
        String_103545,
        0xff,
    },
};

const char String_103545[] = "@";
const char String_103546[] = " BATTLE SCENE@";      // "せんとう　アニメ@"
const char String_10354f[] = " PHONE NUMBER@";      // "でんわばんごう@"
const char String_103557[] = " CARD TRADE@";        // "めいしこうかん@"
const char String_10355f[] = "Caller decides.@";    // "でんわを　かけるひとが　きめられる@"
const char String_103571[] = "Input method.@";      // "でんわばんごうの　にゅうりょくのしかた@"
const char String_103585[] = "Replace old CARD.@";  // "あたらしいめいしが　あれば　こうかん@"
const char String_103598[] = "<LF>:OFF@";           // "とばして　みる@"
const char String_1035a0[] = "<LF>:ON @";           // "じっくり　みる@"
const char String_1035a8[] = "<LF>:CARD@";          // "めいしからえらぶ@"
const char String_1035b1[] = "<LF>:DIAL@";          // "すうじで　いれる@"
const char String_1035ba[] = "<LF>:ON @";           // "する@"
const char String_1035bd[] = "<LF>:OFF@";           // "しない@"
const char String_1035c1[] = " OK@";                // "けってい@"

const Unknown_1035d7_s* Function1035c6(void){
    // FARCALL(aFunction10138b);
    uint8_t c = Function10138b();
    // LD_B(0);
    // LD_HL(mUnknown_1035d7);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;
    return Unknown_1035d7[c];
}

const Unknown_1035d7_s* const Unknown_1035d7[] = {
    &Unknown_1035e7,
    &Unknown_1035f3,
    &Unknown_103608,
    &Unknown_103608,
    &Unknown_1035fe,
    //dw ['AskMobileOrCable'];
    //dw ['AskMobileOrCable'];
    //dw ['AskMobileOrCable'];
};

const Unknown_1035d7_s Unknown_1035e7 = {
    .de = coord(0, 6, 0), //dwcoord ['0', '6'];
    .c = 0x12, .b = 0x07, .n = 0x07, //db ['0x12', '0x07', '0x07'];
    .hl = (const uint8_t[]) { //dw ['.this'];
// this:
        4, 2, 1, 0, 3
    }
};

const Unknown_1035d7_s Unknown_1035f3 = {
    .de = coord(0, 7, 0), //dwcoord ['0', '7'];
    .c = 0x12, .b = 0x06, .n = 0x09, //db ['0x12', '0x06', '0x09'];
    .hl = (const uint8_t[]) { //dw ['.this'];
    // this:
        3, 2, 1, 3
    }
};

const Unknown_1035d7_s Unknown_1035fe = {
    .de = coord(0, 9, 0), //dwcoord ['0', '9'];
    .c = 0x12, .b = 0x04, .n = 0x0b, //db ['0x12', '0x04', '0x0b'];
    .hl = (const uint8_t[]) { //dw ['.this'];
    // this:
        2, 0, 3,
    }
};

const Unknown_1035d7_s Unknown_103608 = {
    .de = coord(0, 9, 0), //dwcoord ['0', '9'];
    .c = 0x12, .b = 0x04, .n = 0x0b, //db ['0x12', '0x04', '0x0b'];
    .hl = (const uint8_t[]) {//dw ['.this'];
    // this:
        2, 2, 3,
    }
};

void AskMobileOrCable(void){
    // LD_HL(mMenuHeader_103640);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_103640);
    // LD_A_addr(wMobileOrCable_LastSelection);
    // AND_A(0x0f);
    // IF_Z goto skip_load;
    if((wram->wMobileOrCable_LastSelection & 0x0f) != 0){
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = wram->wMobileOrCable_LastSelection & 0x0f;
    }

// skip_load:
    // CALL(aVerticalMenu);
    bool cancel = !VerticalMenu();
    // CALL(aCloseWindow);
    CloseWindow();
    // IF_C goto pressed_b;
    if(cancel){
    // pressed_b:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x0;
        // RET;
        return;
    }
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wMenuCursorY;
    // LD_C_A;
    // LD_A_addr(wMobileOrCable_LastSelection);
    // AND_A(0xf0);
    // OR_A_C;
    // LD_addr_A(wMobileOrCable_LastSelection);
    wram->wMobileOrCable_LastSelection = (wram->wMobileOrCable_LastSelection & 0xf0) | wram->wMenuCursorY;
    // RET;
}

const struct MenuData MenuData_103648 = {
    .flags = STATICMENU_CURSOR,  // flags
    .verticalMenu = {
        .count = 2,
        .options = (const char*[]){
            "MOBILE", //db ['"モバイル@"'];
            "CABLE", //db ['"ケーブル@"'];
        },
    },
};

const struct MenuHeader MenuHeader_103640 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 6, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['MenuData_103648'];
    .data = &MenuData_103648,
    .defaultOption = 1,  // default option
};

uint8_t Function103654(void){
    // FARCALL(aMobile_AlwaysReturnNotCarry);
    u8_flag_s res = Mobile_AlwaysReturnNotCarry();
    // BIT_C(7);
    // IF_NZ goto asm_103666;
    if(!bit_test(res.a, 7)) {
        // LD_HL(wcd2a);
        // RES_hl(5);
        bit_reset(wram->wcd2a, 5);
        // LD_C(0x02);
        // RET;
        return 0x02;
    }
    else {
    // asm_103666:
        // LD_HL(wcd2a);
        // SET_hl(5);
        bit_set(wram->wcd2a, 5);
        // LD_C(0x01);
        // RET;
        return 0x01;
    }
}

void Mobile_SelectThreeMons(void){
    // FARCALL(aMobile_AlwaysReturnNotCarry);
    u8_flag_s res = Mobile_AlwaysReturnNotCarry();
    // BIT_C(7);
    // IF_Z goto asm_10369b;
    if(bit_test(res.a, 7)){
        // LD_HL(mMobileBattleMustPickThreeMonText);
        // CALL(aPrintText);
        PrintText(MobileBattleMustPickThreeMonText);
        // CALL(aYesNoBox);
        // IF_C goto asm_103696;
        if(YesNoBox()){
            // FARCALL(aCheckForMobileBattleRules);
            // IF_NC goto asm_103690;
            if(!CheckForMobileBattleRules()){
            // asm_103690:
                // LD_A(0x01);
                // LD_addr_A(wScriptVar);
                wram->wScriptVar = 0x01;
                // RET;
                return;
            }
            // CALL(aJoyWaitAorB);
            // goto asm_103696;
            JoyWaitAorB();
        }

    // asm_103696:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x00;
        // RET;
        return;
    }
    else {
    // asm_10369b:
        // LD_HL(wMobileOrCable_LastSelection);
        // BIT_hl(7);
        bool test = bit_test(wram->wMobileOrCable_LastSelection, 7) != 0;
        // SET_hl(7);
        bit_set(wram->wMobileOrCable_LastSelection, 7);
        // IF_NZ goto asm_1036b5;
        if(!test){
            // LD_HL(mMobileBattleMoreInfoText);
            // CALL(aPrintText);
            PrintText(MobileBattleMoreInfoText);
            // CALL(aYesNoBox);
            // IF_C goto asm_1036b5;
            if(YesNoBox()){
                // CALL(aFunction1036f9);
                Function1036f9();
                // CALL(aJoyWaitAorB);
                JoyWaitAorB();
            }
        }

        while(!Function103700()){
        // asm_1036b5:
            // CALL(aFunction103700);
            // IF_C goto asm_1036f4;
            // LD_HL(mMenuHeader_103747);
            // CALL(aLoadMenuHeader);
            LoadMenuHeader(&MenuHeader_103747);
            // CALL(aVerticalMenu);
            bool quit = !VerticalMenu();
            // CALL(aExitMenu);
            ExitMenu();
            // IF_C goto asm_1036f4;
            if(quit)
                break;
            // LD_A_addr(wMenuCursorY);
            // CP_A(0x01);
            // IF_Z goto asm_1036d9;
            if(wram->wMenuCursorY == 0x01){
            // asm_1036d9:
                // FARCALL(aCheckForMobileBattleRules);
                // IF_NC goto asm_1036e6;
                if(!CheckForMobileBattleRules()){
                // asm_1036e6:
                    // LD_A(0x01);
                    // LD_addr_A(wScriptVar);
                    wram->wScriptVar = TRUE;
                    // RET;
                    return;
                }
                // CALL(aJoyWaitAorB);
                JoyWaitAorB();
                // goto asm_1036f4;
                break;
            }
            // CP_A(0x02);
            // IF_Z goto asm_1036f4;
            else if(wram->wMenuCursorY == 0x02)
                break;
            // CP_A(0x03);
            // IF_Z goto asm_1036ec;
            else if(wram->wMenuCursorY == 0x03){
            // asm_1036ec:
                // CALL(aFunction1036f9);
                Function1036f9();
                // CALL(aJoyWaitAorB);
                JoyWaitAorB();
                // goto asm_1036b5;
                continue;
            }
            // goto asm_1036b5;
        }

    // asm_1036f4:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = FALSE;
        // RET;
        return;
    }
}

// Mobile_PrintBattleRules
void Function1036f9(void){
    // LD_HL(mMobileBattleRulesText);
    // CALL(aPrintText);
    PrintText(MobileBattleRulesText);
    // RET;
}

// Mobile_CheckRemainingTime
bool Function103700(void){
    // LD_C(10);
    uint8_t c = 10;
    // LD_HL(wSwarmFlags);
    // BIT_hl(SWARMFLAGS_MOBILE_4_F);
    // IF_Z goto asm_10370f;
    if(bit_test(wram->wSwarmFlags, SWARMFLAGS_MOBILE_4_F)){
        // FARCALL(aMobileBattleGetRemainingTime);
        c = MobileBattleGetRemainingTime().b;
    }

// asm_10370f:
    // LD_A_C;
    // LD_addr_A(wStringBuffer2);
    wram->wStringBuffer2[0] = c;
    // LD_A_addr(wStringBuffer2);
    // CP_A(5);
    // IF_NC goto five_or_more_mins;
    if(c >= 5){
    // five_or_more_mins:
        // LD_HL(mWouldYouLikeToMobileBattleText);
        // CALL(aPrintText);
        PrintText(WouldYouLikeToMobileBattleText);
        // AND_A_A;
        // RET;
        return false;
    }
    // CP_A(2);
    // IF_NC goto two_to_five_mins;
    else if(c >= 2){
    // two_to_five_mins:
        // LD_HL(mWantAQuickMobileBattleText);
        // CALL(aPrintText);
        PrintText(WantAQuickMobileBattleText);
        // AND_A_A;
        // RET;
        return false;
    }
    // CP_A(1);
    // IF_NC goto one_min;
    else if(c >= 1){
    // one_min:
        // LD_HL(mWantToRushThroughAMobileBattleText);
        // CALL(aPrintText);
        PrintText(WantToRushThroughAMobileBattleText);
        // AND_A_A;
        // RET;
        return false;
    }
    // goto times_up;
    else {
    // times_up:
        // LD_HL(mPleaseTryAgainTomorrowText);
        // CALL(aPrintText);
        PrintText(PleaseTryAgainTomorrowText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB();
        // SCF;
        // RET;
        return true;
    }
}

const struct MenuData MenuData_10374f = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
    .verticalMenu = {
        .count = 3,
        .options = (const char*[]){
            "YES",  // "はい@"
            "NO",   // "やめる@"
            "INFO", // "せつめい@"
        },
    },
};

const struct MenuHeader MenuHeader_103747 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(13, 5, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['MenuData_10374f'];
    .data = &MenuData_10374f,
    .defaultOption = 1,  // default option
};

const txt_cmd_s MobileBattleMustPickThreeMonText[] = {
    text_far(v_MobileBattleMustPickThreeMonText)
    text_end
};

const txt_cmd_s MobileBattleMoreInfoText[] = {
    text_far(v_MobileBattleMoreInfoText)
    text_end
};

const txt_cmd_s MobileBattleRulesText[] = {
    text_far(v_MobileBattleRulesText)
    text_end
};

const txt_cmd_s WouldYouLikeToMobileBattleText[] = {
    text_far(v_WouldYouLikeToMobileBattleText)
    text_end
};

const txt_cmd_s WantAQuickMobileBattleText[] = {
    text_far(v_WantAQuickMobileBattleText)
    text_end
};

const txt_cmd_s WantToRushThroughAMobileBattleText[] = {
    text_far(v_WantToRushThroughAMobileBattleText)
    text_end
};

const txt_cmd_s PleaseTryAgainTomorrowText[] = {
    text_far(v_PleaseTryAgainTomorrowText)
    text_end
};

// Mobile_SaveGameAndSetBattleTimerSpecial
void Function103780(void){
    // LD_A_addr(wChosenCableClubRoom);
    // PUSH_AF;
    uint8_t cableRoom = wram->wChosenCableClubRoom;
    // CALL(aFunction10378c);
    Function10378c();
    // POP_AF;
    // LD_addr_A(wChosenCableClubRoom);
    wram->wChosenCableClubRoom = cableRoom;
    // RET;
}

// Mobile_SaveGameAndSetBattleTimer
// Asks to save the game and starts the mobile battle timer if saved.
void Function10378c(void){
    // LD_C(0);
    uint8_t c = 0;
    // LD_HL(wSwarmFlags);
    // BIT_hl(SWARMFLAGS_MOBILE_4_F);
    // IF_NZ goto already_set;
    if(!bit_test(wram->wSwarmFlags, SWARMFLAGS_MOBILE_4_F)) {
        // LD_C(1);
        c = 1;
        // LD_HL(wSwarmFlags);
        // SET_hl(SWARMFLAGS_MOBILE_4_F);
        bit_set(wram->wSwarmFlags, SWARMFLAGS_MOBILE_4_F);
    }

// already_set:
    // PUSH_BC;
    // FARCALL(aLink_SaveGame);
// For now, removing saving requirement
    // bool saved = Link_SaveGame();
    bool saved = true;
    // POP_BC;
    // IF_C goto failed_to_save;
    if(saved) {
        // LD_A(1);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 1;
        // LD_A_C;
        // AND_A_A;
        // RET_Z ;
        if(c != 0) {
            // FARCALL(aMobileBattleResetTimer);
            MobileBattleResetTimer();
        }
        // RET;
        return;
    }
    else {
    // failed_to_save:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0;
        // LD_A_C;
        // AND_A_A;
        // RET_Z ;
        if(c != 0) {
            // LD_HL(wSwarmFlags);
            // RES_hl(SWARMFLAGS_MOBILE_4_F);
            bit_reset(wram->wSwarmFlags, SWARMFLAGS_MOBILE_4_F);
        }
        // RET;
    }
}

// Mobile_CheckRemainingTimeAndAskAgainSpecial?
void Function1037c2(void){
    // CALL(aMobileCheckRemainingBattleTime);
    bool enough_time = !MobileCheckRemainingBattleTime();
    // IF_C goto nope;
    // LD_A_addr(wdc5f);
    // AND_A_A;
    // IF_Z goto nope;
    if(enough_time && wram->wdc5f != 0) {
        // LD_HL(mTryAgainUsingSameSettingsText);
        // CALL(aPrintText);
        PrintText(TryAgainUsingSameSettingsText);
        // CALL(aYesNoBox);
        bool yes = YesNoBox();
        // IF_C goto nope;
        if(yes) {
            // LD_A(0x01);
            // LD_addr_A(wScriptVar);
            wram->wScriptVar = 0x01;
            // RET;
            return;
        }
    }
// nope:
    // XOR_A_A;
    // LD_addr_A(wdc5f);
    wram->wdc5f = 0x0;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x0;
    // RET;
}

const txt_cmd_s TryAgainUsingSameSettingsText[] = {
    text_far(v_TryAgainUsingSameSettingsText)
    text_end
};

// CheckAbleToMobileBattle
//  wScriptVar == 0x0 -> Don't connect
//  wScriptVar == 0x1 -> Can connect
//  wScriptVar == 0x2 -> Already connected
void Function1037eb(void){
    // CALL(aMobileCheckRemainingBattleTime);
    // IF_NC goto asm_103807;
    if(MobileCheckRemainingBattleTime()) {
        // LD_HL(mMobileBattleLessThanOneMinuteLeftText);
        // CALL(aPrintText);
        PrintText(MobileBattleLessThanOneMinuteLeftText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB();
        // LD_HL(mMobileBattleNoTimeLeftForLinkingText);
        // CALL(aPrintText);
        PrintText(MobileBattleNoTimeLeftForLinkingText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB();
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x0;
        // RET;
        return;
    }

// asm_103807:
    // LD_A_addr(wdc60);
    // AND_A_A;
    // IF_NZ goto asm_103813;
    else if(wram->wdc60 == 0) {
        // LD_A(0x01);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x1;
        // RET;
        return;
    }
    else {
    // asm_103813:
        // LD_A(0x02);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x2;
        // RET;
        return;
    }
}

const txt_cmd_s MobileBattleLessThanOneMinuteLeftText[] = {
    text_far(v_MobileBattleLessThanOneMinuteLeftText)
    text_end
};

const txt_cmd_s MobileBattleNoTimeLeftForLinkingText[] = {
    text_far(v_MobileBattleNoTimeLeftForLinkingText)
    text_end
};

//  Returns carry if less than one minute remains
bool MobileCheckRemainingBattleTime(void){
    // FARCALL(aMobile_AlwaysReturnNotCarry);
    u8_flag_s res = Mobile_AlwaysReturnNotCarry();
    // BIT_C(7);
    // IF_NZ goto ok;
    if(bit_test(res.a, 7))
        return false;
    // FARCALL(aMobileBattleGetRemainingTime);
    u8_pair_s time = MobileBattleGetRemainingTime();
    // LD_A_C;
    // CP_A(1);
    // IF_C goto fail;
    if(time.b < 1)
        return true;

// ok:
    // XOR_A_A;
    // RET;
    return false;

// fail:
    // SCF;
    // RET;
}

// Mobile_SelectThreeMons2
void Function10383c(void){
    // LD_A(0x01);
    // LD_addr_A(wdc60);
    wram->wdc60 = 0x01;
    // XOR_A_A;
    // LD_HL(wPlayerMonSelection);
    // LD_hli_A;
    wram->wPlayerMonSelection[0] = 0x0;
    // LD_hli_A;
    wram->wPlayerMonSelection[1] = 0x0;
    // LD_hl_A;
    wram->wPlayerMonSelection[2] = 0x0;
    // LD_HL(mPickThreeMonForMobileBattleText);
    // CALL(aPrintText);
    PrintText(PickThreeMonForMobileBattleText);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // FARCALL(aScript_reloadmappart);
    Script_reloadmappart_Conv(&gCurScript);
    // FARCALL(aFunction4a94e);
    // IF_C goto asm_103870;
    if(Function4a94e()) {
    // asm_103870:
        // LD_A(0x01);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x01;
        // RET;
        return;
    }
    // LD_HL(wd002);
    // LD_DE(wPlayerMonSelection);
    // LD_BC(3);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPlayerMonSelection, wram->wMobileAdapterPlayerSelectionBuffer, 3);
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x0;
    // RET;
}

const txt_cmd_s PickThreeMonForMobileBattleText[] = {
    text_far(v_PickThreeMonForMobileBattleText)
    text_end
};

// PrintBattleRemainingTimeText
void Function10387b(void){
    // FARCALL(aMobile_AlwaysReturnNotCarry);
    // BIT_C(7);
    // RET_NZ ;
    if(bit_test(Mobile_AlwaysReturnNotCarry().a, 7))
        return;
    // FARCALL(aMobileBattleGetRemainingTime);
    // LD_A_C;
    // LD_addr_A(wStringBuffer2);
    wram->wStringBuffer2[0] = MobileBattleGetRemainingTime().b;
    // LD_HL(mMobileBattleRemainingTimeText);
    // CALL(aPrintText);
    PrintText(MobileBattleRemainingTimeText);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // RET;
}

const txt_cmd_s MobileBattleRemainingTimeText[] = {
    text_far(v_MobileBattleRemainingTimeText)
    text_end
};
