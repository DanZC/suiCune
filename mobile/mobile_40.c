#include "../constants.h"
#include "mobile_40.h"
#include "mobile_41.h"
#include "mobile_12_2.h"
#include "mobile_45_sprite_engine.h"
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
#include "../home/gfx.h"
#include "../home/lcd.h"
#include "../home/audio.h"
#include "../home/window.h"
#include "../home/clear_sprites.h"
#include "../home/double_speed.h"
#include "../home/print_text.h"
#include "../engine/tilesets/timeofday_pals.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/color.h"
#include "../engine/gfx/crystal_layouts.h"
#include "../engine/battle/core.h"
#include "../engine/link/place_waiting_text.h"
#include "../engine/link/link_trade.h"
#include "../engine/events/battle_tower/rules.h"
#include "../engine/overworld/scripting.h"
#include "../engine/overworld/player_object.h"
#include "../engine/overworld/map_setup.h"
#include "../engine/menus/save.h"
#include "../engine/menus/menu.h"
#include "../data/text/common.h"
#include "../charmap.h"

const mobile_comm_fn_t *gMobileCommsJumptable;

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
    ByteFill_Conv2(wram->wBGMapBuffer, 0x65, 0x0);
    // XOR_A_A;
    // LD_HL(wMobileWRAM);
    // LD_BC(wMobileWRAMEnd - wMobileWRAM);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wMobileErrorCodeBuffer, wMobileWRAMEnd - wMobileWRAM, 0x0);
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
    ByteFill_Conv2(wram->wOverworldMapBlocks, sizeof(wram->wOverworldMapBlocks), 0x0);

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
        gMobileCommsJumptable[wram->wMobileCommsJumptableIndex]();

        // CALL(aFunction1000e8);
        Function1000e8();
        // CALL(aFunction1000fa);
        Function1000fa();
        // CALL(aFunction100144);
        Function100144();
        // CALL(aFunction100163);
        Function100163();
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
    wram->wc314[5] = 0x04;
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
        HDMATransferTilemapToWRAMBank3_Conv();
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
    HideSprites_Conv();
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
    UpdateSprites_Conv();
    // hlcoord(1, 2, wTilemap);
    // POP_DE;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(de), coord(1, 2, wram->wTilemap));
    // CALL(aFunction100320);
    Function100320();
    // CALL(aJoyWaitAorB);
    JoyWaitAorB_Conv();
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
    LoadStandardFont_Conv();
    // RET;
}

void Function1002ed(void){
    // FARCALL(aLoadOW_BGPal7);
    LoadOW_BGPal7();
    // FARCALL(aApplyPals);
    ApplyPals_Conv();
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
    JoyWaitAorB_Conv();
    // RET;
}

// Call_Mobile_ReloadMapPart
void Function100320(void){
    // FARCALL(aMobile_ReloadMapPart);
    // RET;
    return Mobile_ReloadMapPart_Conv();
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

void Function100382(void){
    // LD_A_addr(wcd27);
    // LD_HL(mJumptable_10044e);
    // RST(aJumpTable);
    switch(wram->wcd27) {
        case 0: Function10046a(); break;
        case 1: Function10047c(); break;
        case 2: Function100493(); break;
        case 3: Function1004ba(); break;
        case 4: Function1004f4(); break;
        case 5: Function1004ce(); break;
        case 6: Function1004de(); break;
        case 7: Function1004a4(); break;
        case 8: Function100495(); break;
        case 9: Function1004ce(); break;
        case 10: Function1004de(); break;
        case 11: Function1004e9(); break;
        case 12: Function1004f4(); break;
        case 13: Function1004a4(); break;
    }
    // RET;
}

uint8_t Function10038a(void){
    // LD_HL(wccb4);
    mobile_api_data_s out = {.hl = &wram->wccb4};
    // LD_A(MOBILEAPI_17);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_17, &out);
    // RET;
    return out.a;
}

void Function100393(void){
    // LD_HL(wcc60);
    mobile_api_data_s out = {.hl = wram->wcc60_str};
    // LD_A(MOBILEAPI_1D);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_1D, &out);
    // RET;
}

void Function10039c(void){
    // LD_HL(wcc60);
    // LD_DE(w3_d000);
    // LD_BC(0x54);
    // LD_A(0x03);
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(wram->w3_d000, wram->wcc60_str, 0x54);
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

void Function1003ba(void){
    // LD_HL(wccb4);
    // LD_DE(w3_d080);
    // LD_BC(0x54);
    // LD_A(0x03);
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(wram->w3_d080, &wram->wccb4, 0x54);
    // RET;
}

void Function1003c9(void){
    // LD_HL(w3_d080);
    // LD_DE(wccb4);
    // LD_BC(0x54);
    // LD_A(0x03);
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(&wram->wccb4, wram->w3_d080, 0x54);
    // RET;
}

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
    if((wram->wcc61[bc] | (wram->wcc61[bc+1] << 8)) != de) {
    // asm_100426:
        // LD_A(0xf4);
        // LD_addr_A(wcd2b);
        wram->wcd2b = 0xf4;
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
    }
    else {
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

void Function10047c(void){
    // CALL(aFunction100337);
    u8_flag_s res = Function100337();
    // RET_C ;
    // RET_Z ;
    if(res.flag || res.a == 0)
        return;
    // CP_A(0x02);
    // IF_Z goto asm_100487;
    if(res.a == 0x02) {
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

void Function100493(void){
    // JR(masm_100497);
    return asm_100497();
}

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

void Function1004de(void){
    // CALL(aFunction100393);
    Function100393();
    // LD_A_addr(wcd27);
    // INC_A;
    // LD_addr_A(wcd27);
    wram->wcd27++;
    // RET;
}

void Function1004e9(void){
    CALL(aFunction10038a);
    LD_A_addr(wcd27);
    INC_A;
    LD_addr_A(wcd27);
    RET;

}

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
    UpdateSprites_Conv();
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
    PlaceVerticalMenuItems_Conv2();
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor_Conv(GetMenuData());
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
    UpdateSprites_Conv();
    // CALL(aApplyTilemap);
    ApplyTilemap_Conv();
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
    MenuClickSound_Conv(joypad);
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
    LoadMenuHeader_Conv2(&MenuHeader_1005b2);
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
    ExitMenu_Conv2();
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

void Function1005c3(void){
    LD_A_addr(wcd26);
    LD_HL(mJumptable_1005cb);
    RST(aJumpTable);
    RET;

}

void Jumptable_1005cb(void){
    //dw ['Function1005cf'];
    //dw ['Function1005e1'];

    return Function1005cf();
}

void Function1005cf(void){
    LD_HL(mMenuHeader_1005fc);
    CALL(aLoadMenuHeader);
    LD_A(0);
    LD_addr_A(wcd28);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);

    return Function1005e1();
}

void Function1005e1(void){
    CALL(aFunction100522);
    LD_A_addr(wcd28);
    BIT_A(7);
    RET_Z ;
    IF_NC goto asm_1005f0;
    XOR_A_A;
    LD_addr_A(wMenuCursorY);

asm_1005f0:
    CALL(aExitMenu);
    LD_A_addr(wcd26);
    SET_A(7);
    LD_addr_A(wcd26);
    RET;

}

// Call/Cancel Menu
const struct MenuHeader MenuHeader_1005fc = {
    .flags = MENU_BACKUP_TILES,  // flags
    //db ['6', '14'];
    //db ['10', '19'];
    .coord = menu_coords(14, 6, 19, 10),
    .data = &MenuData_100604,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_100604 = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
    .verticalMenu = {
        .count = 2,
        .options = (const char*[]) {
            "CALL",     // "かける@"
            "CANCEL",   // "まつ@"
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
    UpdateTime_Conv();
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
    return PrintNum_Conv2(hl, de, PRINTNUM_LEADINGZEROS | 1, 2);
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
    PlaceString_Conv(&st, st.hl);
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
    UpdateTime_Conv();
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
    a = hram->hMinutes;
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
    OpenSRAM_Conv(MBANK(asMobileBattleTimer));
    // XOR_A_A;
    // LD_hli_A;
    gb_write(sMobileBattleTimer, 0);
    // LD_hli_A;
    gb_write(sMobileBattleTimer + 1, 0);
    // LD_hli_A;
    gb_write(sMobileBattleTimer + 2, 0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void MobileBattleFixTimer(void){
    // LD_A(BANK(sMobileBattleTimer));
    // LD_HL(sMobileBattleTimer);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileBattleTimer));
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
    CloseSRAM_Conv();
    // RET;
}

// MobileBattleUpdateAndLoadTimer?
void Function100720(void){
    // XOR_A_A;
    // LD_addr_A(wcd6a);
    wram->wcd6a = 0;
    // CALL(aUpdateTime);
    UpdateTime_Conv();
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
    OpenSRAM_Conv(MBANK(asMobileBattleTimer));
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
    CloseSRAM_Conv();
    // LD_A_addr(wcd6d);
    // LD_addr_A(wcd6b);
    wram->wcd6b = wram->wcd6d;
    // RET;

}

// MobileBattleUpdateTime?
void Function100754(void){
    // CALL(aUpdateTime);
    UpdateTime_Conv();
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

void Function100772(void){
    PUSH_DE;
    LD_HL(wcd6c);
    LD_A_de;
    CP_A_hl;
    IF_C goto asm_10079a;
    IF_NZ goto asm_10078c;
    INC_HL;
    INC_DE;
    LD_A_de;
    CP_A_hl;
    IF_C goto asm_10079a;
    IF_NZ goto asm_10078c;
    INC_HL;
    INC_DE;
    LD_A_de;
    CP_A_hl;
    IF_C goto asm_10079a;
    IF_Z goto asm_10079a;


asm_10078c:
    POP_HL;
    LD_A_hli;
    LD_addr_A(wcd6c);
    LD_A_hli;
    LD_addr_A(wcd6d);
    LD_A_hli;
    LD_addr_A(wcd6e);
    RET;


asm_10079a:
    POP_DE;
    RET;

}

void Function10079c(void){
    LD_A_addr(wcd21);
    CP_A(0x01);
    IF_NZ goto dont_quit;
    LD_HL(wcd2a);
    BIT_hl(5);
    IF_NZ goto dont_quit;
    LD_HL(wcd2a);
    BIT_hl(6);
    IF_NZ goto dont_quit;
    LD_A_addr(wcd6a);
    ADD_A_C;
    CP_A(60);
    IF_NC goto overflow;
    LD_addr_A(wcd6a);
    AND_A_A;
    RET;


overflow:
    SUB_A(60);
    LD_addr_A(wcd6a);
    LD_D_B;
    PUSH_DE;
    CALL(aFunction1007f6);
    POP_DE;
    IF_C goto quit;
    LD_A_C;
    AND_A_A;
    IF_NZ goto quit;
    LD_A_B;
    CP_A(10);
    IF_NC goto quit;
    LD_A_D;
    AND_A_A;
    RET_Z ;
    LD_A_addr(wcd6b);
    CP_A_B;
    RET_Z ;
    LD_A_B;
    LD_addr_A(wcd6b);
    CALL(aFunction1008e0);
    AND_A_A;
    RET;


quit:
    CALL(aFunction1008e0);
    LD_HL(wcd2a);
    SET_hl(4);
    LD_A(0xfc);
    LD_addr_A(wcd2b);
    SCF;
    RET;


dont_quit:
    AND_A_A;
    RET;

}

void Function1007f6(void){
    CALL(aUpdateTime);
    LD_HL(wcd74);
    LD_DE(wcd71);
    CALL(aFunction1006dc);
    LD_A(0x04);
    CALL(aOpenSRAM);
    LD_HL(0xa802);
    CALL(aFunction100826);
    CALL(aCloseSRAM);
    LD_HL(wcd6e);
    CALL(aFunction100826);
    LDH_A_addr(hHours);
    LD_addr_A(wcd72);
    LDH_A_addr(hMinutes);
    LD_addr_A(wcd73);
    LDH_A_addr(hSeconds);
    LD_addr_A(wcd74);
    RET;

}

void Function100826(void){
    LD_A_addr(wcd71);
    ADD_A_hl;
    SUB_A(0x3c);
    IF_NC goto asm_100830;
    ADD_A(0x3c);


asm_100830:
    LD_hld_A;
    CCF;
    LD_A_addr(wcd70);
    ADC_A_hl;
    SUB_A(0x3c);
    IF_NC goto asm_10083c;
    ADD_A(0x3c);


asm_10083c:
    LD_hld_A;
    LD_B_A;
    CCF;
    LD_A_addr(wcd6f);
    ADC_A_hl;
    LD_hl_A;
    LD_C_A;
    RET;

}

void Function100846(void){
    LD_HL(wcd2a);
    BIT_hl(5);
    IF_NZ goto asm_10087c;
    LD_A_addr(wcd6e);
    LD_C_A;
    LD_A(0);
    SUB_A_C;
    IF_NC goto asm_100858;
    ADD_A(0x3c);


asm_100858:
    LD_addr_A(wStringBuffer2 + 2);
    LD_A_addr(wcd6d);
    LD_C_A;
    LD_A(0x0a);
    SBC_A_C;
    LD_addr_A(wStringBuffer2 + 1);
    XOR_A_A;
    LD_addr_A(wStringBuffer2);
    LD_DE(mString_10088e);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_DE(wStringBuffer2);
    hlcoord(4, 16, wTilemap);
    CALL(aFunction100697);
    RET;


asm_10087c:
    LD_DE(mString_10088e);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mString_10089f);
    CALL(aPlaceString);
    RET;

}

const char String_10088e[] = 
            "MOBILE BATTLE TIME@";  // "モバイルたいせん\u3000できる"
                                    //next "じかん@"

const char String_10089f[] = "UNLIMITED@"; // "\u3000むせいげん@"

//  Calculates the difference between 10 minutes and sMobileBattleTimer
//  Returns minutes in c (b) and seconds in b (a)
u8_pair_s MobileBattleGetRemainingTime(void){
    // LD_A(BANK(sMobileBattleTimer));
    // LD_HL(sMobileBattleTimer);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileBattleTimer));
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2);
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2 + 1);
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2 + 2);
    CopyBytes_Conv2(wram->wStringBuffer2, GBToRAMAddr(sMobileBattleTimer), 3);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
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
    LDH_A_addr(hBGMapMode);
    LD_B_A;
    LDH_A_addr(hVBlank);
    LD_C_A;
    PUSH_BC;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x03);
    LDH_addr_A(hVBlank);
    CALL(aFunction100970);
    CALL(aFunction100902);
    CALL(aFunction100989);
    CALL(aDelayFrame);
    POP_BC;
    LD_A_C;
    LDH_addr_A(hVBlank);
    LD_A_B;
    LDH_addr_A(hBGMapMode);
    RET;

}

void Function100902(void){
    hlcoord(3, 10, wTilemap);
    LD_B(0x01);
    LD_C(0x0b);
    CALL(aTextbox);
    LD_A_addr(wcd6d);
    LD_C_A;
    LD_A(0x0a);
    SUB_A_C;
    LD_addr_A(wStringBuffer2);
    IF_Z goto asm_10093f;
    LD_DE(mFunction100902_string_100966);
    hlcoord(4, 11, wTilemap);
    CALL(aPlaceString);
    hlcoord(8, 11, wTilemap);
    LD_BC((1 << 8) | 2);
    LD_DE(wStringBuffer2);
    CALL(aPrintNum);
    LD_DE(SFX_TWO_PC_BEEPS);
    CALL(aPlaySFX);
    FARCALL(aReloadMapPart);
    LD_C(0x3c);
    CALL(aDelayFrames);
    RET;


asm_10093f:
    LD_DE(mFunction100902_string_10095a);
    hlcoord(4, 11, wTilemap);
    CALL(aPlaceString);
    LD_DE(SFX_4_NOTE_DITTY);
    CALL(aPlaySFX);
    FARCALL(aReloadMapPart);
    LD_C(120);
    CALL(aDelayFrames);
    RET;


string_10095a:
    //db ['"たいせん\u3000しゅうりょう@"'];

string_100966:
    //db ['"のこり\u3000\u3000\u3000ふん！@"'];

    return Function100970();
}

void Function100970(void){
    hlcoord(0, 0, wTilemap);
    LD_DE(w3_dc00);
    CALL(aFunction1009a5);
    hlcoord(0, 0, wAttrmap);
    LD_DE(w3_dd68);
    CALL(aFunction1009a5);
    CALL(aFunction1009d2);
    CALL(aFunction1009ae);
    RET;

}

void Function100989(void){
    LD_HL(w3_dc00);
    decoord(0, 0, wTilemap);
    CALL(aFunction1009a5);
    CALL(aFunction1009ae);
    FARCALL(aReloadMapPart);
    LD_HL(w3_dd68);
    decoord(0, 0, wAttrmap);
    CALL(aFunction1009a5);
    RET;

}

void Function1009a5(void){
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    LD_A(0x03);
    CALL(aFarCopyWRAM);
    RET;

}

void Function1009ae(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x03);
    LDH_addr_A(rSVBK);

    LD_HL(w3_d800);
    decoord(0, 0, wAttrmap);
    LD_C(SCREEN_WIDTH);
    LD_B(SCREEN_HEIGHT);

loop_row:
    PUSH_BC;

loop_col:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop_col;
    LD_BC(BG_MAP_WIDTH - SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto loop_row;

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function1009d2(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x03);
    LDH_addr_A(rSVBK);

    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x01);
    LDH_addr_A(rVBK);

    LD_HL(w3_d800);
    debgcoord(0, 0, vBGMap0);
    LD_BC((0x03 << 8) | 0x24);
    CALL(aGet2bpp);

    POP_AF;
    LDH_addr_A(rVBK);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function1009f3(void){
    LDH_A_addr(hJoyDown);
    AND_A(SELECT + A_BUTTON);
    CP_A(SELECT + A_BUTTON);
    IF_NZ goto select_a;
    LD_HL(wcd2a);
    SET_hl(4);
    LD_A(0xf8);
    LD_addr_A(wcd2b);
    SCF;
    RET;


select_a:
    XOR_A_A;
    RET;

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
    CALL(aFunction100acf);
    CALL(aStartMobileInactivityTimer);
    LD_A(0);
    LD_addr_A(wcd27);

asm_100a92:
    CALL(aDelayFrame);
    CALL(aGetJoypad);
    FARCALL(aFunction100382);
    LD_C(0x01);
    LD_B(0x03);
    PUSH_BC;
    CALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    POP_BC;
    IF_C goto asm_100ac7;
    LD_B(0x01);
    CALL(aFunction10079c);
    IF_C goto asm_100ac7;
    CALL(aFunction1009f3);
    IF_C goto asm_100ac7;
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_100ac7;
    LD_A_addr(wcd27);
    BIT_A(7);
    IF_Z goto asm_100a92;
    CALL(aFunction100ae7);
    goto asm_100ace;


asm_100ac7:
    LD_A(0x0f);
    LD_addr_A(wd430);
    goto asm_100ace;


asm_100ace:
    RET;
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
        else if(a == *hl) {
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
    CALL(aFunction100dd8);
    RET_C ;
    LD_HL(mBattleMenuHeader);
    LD_A(BANK(aBattleMenuHeader));
    LD_DE(mLoadMenuHeader);
    CALL(aFarCall_de);
    LD_A(BANK(aBattleMenuHeader));
    LD_addr_A(wMenuData_2DMenuItemStringsBank);
    LD_A_addr(wBattleMenuCursorPosition);
    LD_addr_A(wMenuCursorPosition);
    CALL(aFunction100e72);
    CALL(aFunction100b45);
    FARCALL(aInitPartyMenuBGPal7);
    CALL(aFunction100ed4);
    LD_A_addr(wMenuCursorPosition);
    LD_addr_A(wBattleMenuCursorPosition);
    CALL(aExitMenu);
    RET;

}

void Function100b45(void){
    CALL(aFunction100b7a);

loop:
    CALL(aMobile_SetOverworldDelay);
    FARCALL(aMobileMenuJoypad);
    PUSH_BC;
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    CALL(aFunction100e2d);
    POP_BC;
    IF_C goto asm_100b6b;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    IF_Z goto loop;
    FARCALL(aMobile_GetMenuSelection);
    RET;


asm_100b6b:
    LD_A_addr(w2DMenuNumCols);
    LD_C_A;
    LD_A_addr(w2DMenuNumRows);
    CALL(aSimpleMultiply);
    LD_addr_A(wMenuCursorPosition);
    AND_A_A;
    RET;

}

void Function100b7a(void){
    LD_HL(mCopyMenuData);
    LD_A_addr(wMenuData_2DMenuItemStringsBank);
    RST(aFarCall);
    FARCALL(aDraw2DMenu);
    FARCALL(aMobileTextBorder);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    FARCALL(aInit2DMenuCursorPosition);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RET;

}

void Mobile_MoveSelectionScreen(void){
    XOR_A_A;
    LD_addr_A(wSwappingMove);
    FARCALL(aCheckPlayerHasUsableMoves);
    RET_Z ;
    CALL(aFunction100dd8);
    JP_C (mxor_a_dec_a);
    CALL(aFunction100e72);
    CALL(aMobile_MoveSelectionScreen_GetMoveSelection);
    PUSH_AF;
    FARCALL(aInitPartyMenuBGPal7);
    CALL(aFunction100ed4);
    POP_AF;
    RET;


GetMoveSelection:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aMobile_MoveSelectionScreen_ListMoves);
    CALL(aFunction100c98);

master_loop:
    FARCALL(aMoveInfoBox);

loop:
    CALL(aMobile_SetOverworldDelay);
    FARCALL(aMobileMenuJoypad);
    PUSH_BC;
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    CALL(aFunction100e2d);
    POP_BC;
    IF_C goto b_button;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    BIT_A(D_UP_F);
    JP_NZ (mMobile_MoveSelectionScreen_d_up);
    BIT_A(D_DOWN_F);
    JP_NZ (mMobile_MoveSelectionScreen_d_down);
    BIT_A(A_BUTTON_F);
    IF_NZ goto a_button;
    BIT_A(B_BUTTON_F);
    IF_NZ goto b_button;
    goto loop;


d_up:
    LD_A_addr(wMenuCursorY);
    AND_A_A;
    JP_NZ (mMobile_MoveSelectionScreen_master_loop);
    LD_A_addr(wNumMoves);
    INC_A;
    LD_addr_A(wMenuCursorY);
    JP(mMobile_MoveSelectionScreen_master_loop);


d_down:
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wNumMoves);
    INC_A;
    INC_A;
    CP_A_B;
    JP_NZ (mMobile_MoveSelectionScreen_master_loop);
    LD_A(0x01);
    LD_addr_A(wMenuCursorY);
    JP(mMobile_MoveSelectionScreen_master_loop);


b_button:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurMoveNum);
    LD_A(0x01);
    AND_A_A;
    RET;


a_button:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurMoveNum);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wBattleMonPP);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3f);
    IF_Z goto no_pp_left;
    LD_A_addr(wPlayerDisableCount);
    SWAP_A;
    AND_A(0x0f);
    DEC_A;
    CP_A_C;
    IF_Z goto move_disabled;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wBattleMonMoves);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPlayerMove);
    XOR_A_A;
    RET;


move_disabled:
    LD_HL(mBattleText_TheMoveIsDisabled);
    goto print_text;


no_pp_left:
    LD_HL(mBattleText_TheresNoPPLeftForThisMove);


print_text:
    CALL(aStdBattleTextbox);
    CALL(aSafeLoadTempTilemapToTilemap);
    JP(mMobile_MoveSelectionScreen_GetMoveSelection);


ListMoves:
    hlcoord(0, 8, wTilemap);
    LD_B(8);
    LD_C(8);
    CALL(aTextbox);
    LD_HL(wBattleMonMoves);
    LD_DE(wListMoves_MoveIndicesBuffer);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);
    LD_A(SCREEN_WIDTH * 2);
    LD_addr_A(wListMovesLineSpacing);
    hlcoord(2, 10, wTilemap);
    PREDEF(pListMoves);
    RET;

}

void Function100c98(void){
    LD_DE(mFunction100c98_data);
    CALL(aLoad2DMenuData);
    LD_A_addr(wNumMoves);
    INC_A;
    LD_addr_A(w2DMenuNumRows);
    LD_A_addr(wCurMoveNum);
    INC_A;
    LD_addr_A(wMenuCursorY);
    RET;


data:
    //db ['10', '1'];  // cursor start y, x
    //db ['-1', '1'];  // rows, columns
    //db ['0xa0', '0x00'];  // flags
    //dn ['2', '0'];  // cursor offsets
    //db ['D_UP | D_DOWN | A_BUTTON | B_BUTTON'];  // accepted buttons

    return Mobile_PartyMenuSelect();
}

void Mobile_PartyMenuSelect(void){
    CALL(aFunction100dd8);
    RET_C ;
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RES_hl(6);

loop:
    CALL(aMobile_SetOverworldDelay);
    FARCALL(aMobileMenuJoypad);
    PUSH_BC;
    FARCALL(aPlaySpriteAnimations);
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    CALL(aMobileComms_CheckInactivityTimer);
    POP_BC;
    IF_C goto done;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    IF_Z goto loop;
    CALL(aPlaceHollowCursor);
    LD_A_addr(wPartyCount);
    INC_A;
    LD_B_A;
    LD_A_addr(wMenuCursorY);
    CP_A_B;
    IF_Z goto done;
    LD_addr_A(wPartyMenuCursor);
    LDH_A_addr(hJoyLast);
    LD_B_A;
    BIT_B(1);
    IF_NZ goto done;
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


done:
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    SCF;
    RET;

}

void MobileBattleMonMenu(void){
    CALL(aFunction100dd8);
    RET_C ;
    CALL(aFunction100d67);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RES_hl(6);

asm_100d30:
    CALL(aMobile_SetOverworldDelay);
    FARCALL(aMobileMenuJoypad);
    PUSH_BC;
    FARCALL(aPlaySpriteAnimations);
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    CALL(aMobileComms_CheckInactivityTimer);
    POP_BC;
    IF_C goto asm_100d54;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    IF_NZ goto asm_100d56;
    goto asm_100d30;


asm_100d54:
    SCF;
    RET;


asm_100d56:
    PUSH_AF;
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    POP_AF;
    BIT_A(1);
    IF_Z goto asm_100d65;
    RET_Z ;
    SCF;
    RET;


asm_100d65:
    AND_A_A;
    RET;

}

void Function100d67(void){
    LD_HL(mFunction100d67_MenuHeader);
    CALL(aCopyMenuHeader);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aMenuBox);
    CALL(aUpdateSprites);
    CALL(aPlaceVerticalMenuItems);
    CALL(aWaitBGMap);
    CALL(aCopyMenuData);
    CALL(aInitVerticalMenuCursor);
    LD_HL(w2DMenuFlags1);
    SET_hl(6);
    RET;


MenuHeader:
    //db ['0'];  // flags
    //menu_coords ['11', '11', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['3'];
    //db ['"いれかえる@"'];  // TRADE
    //db ['"つよさをみる@"'];  // STATS
    //db ['"キャンセル@"'];  // CANCEL

    return Function100da5();
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

void Function100dd8(void){
    LD_C(0x01);
    LD_B(0x03);
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    IF_C goto asm_100dfb;
    LD_C(0x3c);
    LD_B(0x01);
    CALL(aFunction10079c);
    IF_C goto asm_100dfb;
    FARCALL(aFunction10032e);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_100dfb;
    XOR_A_A;
    RET;


asm_100dfb:
    SCF;
    RET;

}

void MobileComms_CheckInactivityTimer(void){
    LD_A_addr(wOverworldDelay);
    LD_C_A;
    LD_A(30);
    SUB_A_C;
    LD_C_A;
    LD_B(3);
    PUSH_BC;
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);  // useless to farcall
    POP_BC;
    IF_C goto quit;
    LD_B(1);
    CALL(aFunction10079c);
    IF_C goto quit;
    CALL(aFunction1009f3);
    IF_C goto quit;
    FARCALL(aFunction10032e);  // useless to farcall
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto quit;
    XOR_A_A;
    RET;


quit:
    SCF;
    RET;

}

void Function100e2d(void){
    LD_A_addr(wOverworldDelay);
    LD_C_A;
    LD_A(30);
    SUB_A_C;
    LD_C_A;
    LD_B(3);
    PUSH_BC;
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    POP_BC;
    IF_C goto asm_100e61;
    LD_B(1);
    CALL(aFunction10079c);
    IF_C goto asm_100e61;
    CALL(aFunction1009f3);
    IF_C goto asm_100e61;
    FARCALL(aFunction10032e);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_100e61;
    CALL(aFunction100e63);
    CALL(aFunction100e84);
    XOR_A_A;
    RET;


asm_100e61:
    SCF;
    RET;

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
    PlaySFX_Conv(SFX_ELEVATOR_END);
    // RET;
}

void Function100e72(void){
    XOR_A_A;
    LD_HL(wcd29);
    BIT_hl(0);
    IF_Z goto asm_100e7c;
    LD_A(0x0a);


asm_100e7c:
    LD_addr_A(wcd67);
    XOR_A_A;
    LD_addr_A(wcd68);
    RET;

}

void Function100e84(void){
    LD_A_addr(wcd67);
    LD_HL(mJumptable_100e8c);
    RST(aJumpTable);
    RET;

}

void Jumptable_100e8c(void){
    //dw ['Function100ea2'];
    //dw ['Function100eae'];
    //dw ['Function100eb4'];
    //dw ['Function100eae'];
    //dw ['Function100eb4'];
    //dw ['Function100eae'];
    //dw ['Function100eb4'];
    //dw ['Function100eae'];
    //dw ['Function100eb4'];
    //dw ['Function100eae'];
    //dw ['Function100ec4'];

    return Function100ea2();
}

void Function100ea2(void){
    CALL(aFunction100dc0);
    RET_NC ;
    LD_HL(wcd29);
    SET_hl(0);
    CALL(aFunction100ec5);

    return Function100eae();
}

void Function100eae(void){
    SCF;
    CALL(aFunction100eca);
    JR(masm_100eb8);

}

void Function100eb4(void){
    AND_A_A;
    CALL(aFunction100eca);

    return asm_100eb8();
}

void asm_100eb8(void){
    LD_HL(wcd68);
    INC_hl;
    LD_A_hl;
    CP_A(0x02);
    RET_C ;
    LD_hl(0);
    JR(mFunction100ec5);

}

void Function100ec4(void){
    RET;

}

void Function100ec5(void){
    LD_HL(wcd67);
    INC_hl;
    RET;

}

void Function100eca(void){
    FARCALL(aMobile_InitPartyMenuBGPal7);
    CALL(aFunction100ed4);
    RET;

}

void Function100ed4(void){
    FARCALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void Function100edf(void){
    LD_HL(mUnknown_100fc0);
    LD_C(1);
    JR(mFunction100f02);

}

void Function100ee6(void){
    LD_HL(mUnknown_100fc0);
    LD_C(2);
    JR(mFunction100f02);

}

void Function100eed(void){
    LD_HL(mUnknown_100feb);
    LD_C(1);
    JR(mFunction100f02);

}

void Function100ef4(void){
    LD_HL(mUnknown_100ff3);
    LD_C(1);
    JR(mFunction100f02);

}

void Function100efb(void){
//  //  unreferenced
    LD_HL(mUnknown_10102c);
    LD_C(1);
    JR(mFunction100f02);

}

void Function100f02(void){
    LD_A_C;
    LD_addr_A(wStringBuffer2);
// someting that was previously stored in de gets backed up to here
    LD_A_E;
    LD_addr_A(wStringBuffer2 + 1);
    LD_A_D;
    LD_addr_A(wStringBuffer2 + 2);
// empty this
    XOR_A_A;
    LD_addr_A(wStringBuffer2 + 4);
    LD_addr_A(wStringBuffer2 + 5);

loop:
    LD_A_hl;
    CP_A(0xff);
    IF_Z goto done;
    LD_addr_A(wStringBuffer2 + 3);  // bank
    PUSH_HL;
    INC_HL;
// addr 1
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
// size
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
// addr 2
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aFunction100f3d);
// next line
    POP_HL;
    LD_DE(7);
    ADD_HL_DE;
    goto loop;


done:
// recover the values into bc
    LD_A_addr(wStringBuffer2 + 4);
    LD_C_A;
    LD_A_addr(wStringBuffer2 + 5);
    LD_B_A;
    RET;

}

void Function100f3d(void){
// parameter
    LD_A_addr(wStringBuffer2);
    CP_A(0x02);
    IF_Z goto two;
    CP_A(0x01);
    IF_Z goto one;
    CP_A(0x03);
    IF_Z goto three;
    RET;


three:
// what was once in de gets copied to hl,
// modified by Function100f8d, and put back
// into this backup
    LD_A_addr(wStringBuffer2 + 1);
    LD_L_A;
    LD_A_addr(wStringBuffer2 + 2);
    LD_H_A;
    CALL(aFunction100f8d);
    LD_A_L;
    LD_addr_A(wStringBuffer2 + 1);
    LD_A_H;
    LD_addr_A(wStringBuffer2 + 2);
    RET;


two:
// hl gets backed up to de, then
// do the same as in .three
    LD_D_H;
    LD_E_L;
    LD_A_addr(wStringBuffer2 + 1);
    LD_L_A;
    LD_A_addr(wStringBuffer2 + 2);
    LD_H_A;
    CALL(aFunction100f8d);
    LD_A_L;
    LD_addr_A(wStringBuffer2 + 1);
    LD_A_H;
    LD_addr_A(wStringBuffer2 + 2);
    RET;


one:
// de gets copied to hl, then
// load the backup into de,
// finally run Function100f8d
// and store the de result
    LD_H_D;
    LD_L_E;
    LD_A_addr(wStringBuffer2 + 1);
    LD_E_A;
    LD_A_addr(wStringBuffer2 + 2);
    LD_D_A;
    CALL(aFunction100f8d);
    LD_A_E;
    LD_addr_A(wStringBuffer2 + 1);
    LD_A_D;
    LD_addr_A(wStringBuffer2 + 2);
    RET;

}

void Function100f8d(void){
    PUSH_HL;
    LD_A_addr(wStringBuffer2 + 4);
    LD_L_A;
    LD_A_addr(wStringBuffer2 + 5);
    LD_H_A;
    ADD_HL_BC;
    LD_A_L;
    LD_addr_A(wStringBuffer2 + 4);
    LD_A_H;
    LD_addr_A(wStringBuffer2 + 5);
    POP_HL;
    LD_A_addr(wStringBuffer2 + 3);
    BIT_A(7);
    RES_A(7);
    IF_Z goto sram;
    AND_A_A;
    IF_NZ goto far_wram;
    CALL(aCopyBytes);
    RET;


far_wram:
    AND_A(0x7f);
    CALL(aFarCopyWRAM);
    RET;


sram:
    CALL(aOpenSRAM);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

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

}

void Unknown_100fc0(void){
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH', 'wOTPlayerName']
    //macro_100fc0 ['wPartyCount', '1 + PARTY_LENGTH + 1', 'wOTPartyCount']
    //macro_100fc0 ['wPlayerID', '2', 'wOTPlayerID']
    //macro_100fc0 ['wPartyMons', 'PARTYMON_STRUCT_LENGTH * PARTY_LENGTH', 'wOTPartyMons']
    //macro_100fc0 ['wPartyMonOTs', 'NAME_LENGTH * PARTY_LENGTH', 'wOTPartyMonOTs']
    //macro_100fc0 ['wPartyMonNicknames', 'MON_NAME_LENGTH * PARTY_LENGTH', 'wOTPartyMonNicknames']
    //db ['-1'];  // end

    return Unknown_100feb();
}

void Unknown_100feb(void){
    //macro_100fc0 ['sPartyMail', 'MAIL_STRUCT_LENGTH * PARTY_LENGTH']
    //db ['-1'];  // end

    return Unknown_100ff3();
}

void Unknown_100ff3(void){
    //macro_100fc0 ['wdc41', '1']
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH']
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH']
    //macro_100fc0 ['wPlayerID', '2']
    //macro_100fc0 ['wSecretID', '2']
    //macro_100fc0 ['wPlayerGender', '1']
    //macro_100fc0 ['s4_a603', '8']
    //macro_100fc0 ['s4_a007', 'PARTYMON_STRUCT_LENGTH']
    //db ['-1'];  // end

    return Unknown_10102c();
}

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
    CALL(aFunction10107d);
    LD_A_addr(wOTPartyCount);
    for(int rept = 0; rept < 2; rept++){  //  ???
    LD_HL(wc608);
    }
    LD_BC(wc7bb - wc608);
    CALL(aFunction1010de);
    LD_HL(wc7bb);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    LD_A(0x07);
    CALL(aOpenSRAM);
    LD_HL(wc608);
    LD_DE(0xa001);
    LD_BC(wc7bd - wc608);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void Function10107d(void){
    XOR_A_A;
    LD_HL(wc608);
    LD_BC(wc7bd - wc608);
    CALL(aByteFill);
    LD_HL(wOTPlayerName);
    LD_DE(wc608);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_HL(wd271);
    LD_A_hli;
    LD_addr_A(wc608 + 11);
    LD_A_hl;
    LD_addr_A(wc608 + 12);
    LD_HL(wOTPartyMonNicknames);
    LD_DE(wc608 + 13);
    LD_BC(NAME_LENGTH);
    CALL(aFunction10107d_CopyAllFromOT);
    LD_HL(wOTPartyMonOTs);
    LD_DE(wOTClassName + 1);
    LD_BC(NAME_LENGTH);
    CALL(aFunction10107d_CopyAllFromOT);
    LD_HL(wOTPartyMon1Species);
    LD_DE(0xc699);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aFunction10107d_CopyAllFromOT);
    LD_A(0x50);
    LD_addr_A(wc7b9);
    LD_A(0x33);
    LD_addr_A(wc7ba);
    RET;


CopyAllFromOT:
    PUSH_HL;
    LD_HL(0);
    LD_A_addr(wOTPartyCount);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    POP_HL;
    CALL(aCopyBytes);
    RET;

}

void Function1010de(void){
    PUSH_HL;
    PUSH_BC;
    LD_DE(0);

loop:
    LD_A_hli;
    ADD_A_E;
    LD_E_A;
    LD_A_D;
    ADC_A(0);
    LD_D_A;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    POP_BC;
    POP_HL;
    RET;

}

void LoadSelectedPartiesForColosseum(void){
    XOR_A_A;
    LD_HL(wStringBuffer2);
    LD_BC(9);
    CALL(aByteFill);
    LD_HL(wPlayerMonSelection);
    LD_DE(wPartyCount);
    CALL(aLoadSelectedPartiesForColosseum_CopyThreeSpecies);
    LD_HL(wPlayerMonSelection);
    LD_DE(wPartyMon1Species);
    CALL(aLoadSelectedPartiesForColosseum_CopyPartyStruct);
    LD_HL(wPlayerMonSelection);
    LD_DE(wPartyMonOTs);
    CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LD_HL(wPlayerMonSelection);
    LD_DE(wPartyMonNicknames);
    CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LD_HL(wOTMonSelection);
    LD_DE(wOTPartyCount);
    CALL(aLoadSelectedPartiesForColosseum_CopyThreeSpecies);
    LD_HL(wOTMonSelection);
    LD_DE(wOTPartyMon1Species);
    CALL(aLoadSelectedPartiesForColosseum_CopyPartyStruct);
    LD_HL(wOTMonSelection);
    LD_DE(wOTPartyMonOTs);
    CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LD_HL(wOTMonSelection);
    LD_DE(wOTPartyMonNicknames);
    CALL(aLoadSelectedPartiesForColosseum_CopyName);
    RET;


CopyThreeSpecies:
//  Load the 3 choices to the buffer
    PUSH_DE;
    LD_BC(wStringBuffer2 + NAME_LENGTH_JAPANESE);
    XOR_A_A;

party_loop:
    PUSH_AF;
    CALL(aLoadSelectedPartiesForColosseum_GetNthSpecies);
    LD_bc_A;
    INC_BC;
    POP_AF;
    INC_A;
    CP_A(3);
    IF_NZ goto party_loop;
    POP_DE;
//  Copy the 3 choices to the party
    LD_A(3);
    LD_de_A;
    INC_DE;
    LD_HL(wStringBuffer2 + NAME_LENGTH_JAPANESE);
    LD_BC(3);
    CALL(aCopyBytes);
    LD_A(0xff);
    LD_de_A;
    RET;


GetNthSpecies:
//  Preserves hl and de
//  Get the index of the Nth selection
    PUSH_HL;
    ADD_A_L;
    LD_L_A;
    LD_A_H;
    ADC_A(0);
    LD_H_A;
    LD_A_hl;
    POP_HL;
//  Get the corresponding species
    PUSH_DE;
    INC_DE;
    ADD_A_E;
    LD_E_A;
    LD_A_D;
    ADC_A(0);
    LD_D_A;
    LD_A_de;
    POP_DE;
    RET;


CopyPartyStruct:
    LD_BC(PARTYMON_STRUCT_LENGTH);
    goto ContinueCopy;


CopyName:
    LD_BC(NAME_LENGTH);


ContinueCopy:
// Copy, via wc608...
    LD_A(LOW(wc608));
    LD_addr_A(wStringBuffer2);
    LD_A(HIGH(wc608));
    LD_addr_A(wStringBuffer2 + 1);
// ... bc bytes...
    LD_A_C;
    LD_addr_A(wStringBuffer2 + 2);
    LD_A_B;
    LD_addr_A(wStringBuffer2 + 3);
// ... to de...
    LD_A_E;
    LD_addr_A(wStringBuffer2 + 4);
    LD_A_D;
    LD_addr_A(wStringBuffer2 + 5);
// ... 3 times.
    LD_A(3);

big_copy_loop:
    PUSH_AF;
    LD_A_hli;
    PUSH_HL;
    PUSH_AF;
    CALL(aLoadSelectedPartiesForColosseum_GetDestinationAddress);
    CALL(aLoadSelectedPartiesForColosseum_GetCopySize);
    POP_AF;
    CALL(aAddNTimes);
    LD_A_addr(wStringBuffer2);
    LD_E_A;
    LD_A_addr(wStringBuffer2 + 1);
    LD_D_A;
    CALL(aCopyBytes);
    LD_A_E;
    LD_addr_A(wStringBuffer2);
    LD_A_D;
    LD_addr_A(wStringBuffer2 + 1);
    POP_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto big_copy_loop;
    CALL(aLoadSelectedPartiesForColosseum_GetCopySize);
    LD_A(3);
    LD_HL(0);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    CALL(aLoadSelectedPartiesForColosseum_GetDestinationAddress);
    LD_D_H;
    LD_E_L;
    LD_HL(wc608);
    CALL(aCopyBytes);
    RET;


GetDestinationAddress:
    LD_A_addr(wStringBuffer2 + 4);
    LD_L_A;
    LD_A_addr(wStringBuffer2 + 5);
    LD_H_A;
    RET;


GetCopySize:
    LD_A_addr(wStringBuffer2 + 2);
    LD_C_A;
    LD_A_addr(wStringBuffer2 + 3);
    LD_B_A;
    RET;

}

// Mobile_StartLinkMode?
void Function1011f1(void){
    // LD_A(BANK(s4_a60c));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as4_a60c));
    // LD_A_addr(s4_a60c);
    // LD_addr_A(wdc41);
    wram->wdc41 = gb_read(s4_a60c);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
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
    UpdateSprites_Conv();
    // CALL(aRefreshScreen);
    RefreshScreen_Conv();
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
    UpdateSprites_Conv();
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

void Function10138b(void){
    FARCALL(aFunction8adcc);
    LD_C(0);
    IF_C goto asm_101396;
    INC_C;


asm_101396:
    SLA_C;
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_Z goto asm_10139f;
    INC_C;


asm_10139f:
    SLA_C;
    LD_A_addr(wcd21);
    CP_A(0x01);
    IF_Z goto asm_1013a9;
    INC_C;


asm_1013a9:
    RET;

}

void Function1013aa(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // CALL(aReloadTilesetAndPalettes);
    ReloadTilesetAndPalettes_Conv();
    // FARCALL(aFunction106464);
    Function106464();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aFinishExitMenu);
    FinishExitMenu_Conv();
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
    FinishExitMenu_Conv();
    // RET;
}

// Mobile_HDMATransferAttrmapAndTilemapToWRAMBank3
void Function1013d6(void){
    // FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    // RET;
    return HDMATransferAttrmapAndTilemapToWRAMBank3_Conv();
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

void Function1013f5(void){
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_C_A;

asm_1013f9:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto asm_1013f9;
    RET;

}

void Function101400(void){
//  //  unreferenced
    LD_A_de;
    INC_DE;
    CP_A_hl;
    JR_NZ (masm_101416);
    INC_HL;

    return Function101406();
}

void Function101406(void){
    LD_C_A;
    LD_B(0);

asm_101409:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    JR_NZ (masm_101416);
    INC_HL;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto asm_101409;
    AND_A_A;
    RET;

}

void asm_101416(void){
    SCF;
    RET;

}

// Mobile_CheckSelectA
bool Function101418(void){
    // CALL(aGetJoypad);
    GetJoypad_Conv2();
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
    GetJoypad_Conv2();
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
    LD_DE(wcd30);
    LD_HL(0x40);
    LD_BC(0x40);
    LD_A(MOBILEAPI_01);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

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
    LD_A(MOBILEAPI_1B);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101537(void){
    LD_A(MOBILEAPI_05);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101544(void){
    FARCALL(aStartMobileInactivityTimer);
    LD_A(MOBILEAPI_09);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101557(void){
    FARCALL(aStartMobileInactivityTimer);
    LD_HL(wcd53);
    LD_A(MOBILEAPI_04);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10156d(void){
    CALL(aFunction101418);
    RET_C ;

    return Function101571();
}

void Function101571(void){
    FARCALL(aFunction10032e);
    RET_C ;
    RET_Z ;
    LD_A_E;
    CP_A(0x01);
    IF_Z goto asm_101582;
    LD_addr_A(wcd2b);
    RET;


asm_101582:
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10158a(void){
    FARCALL(aIncrementMobileInactivityTimerBy1Frame);
    LD_A_addr(wMobileInactivityTimerMinutes);
    CP_A(0x0a);
    JR_C (mFunction10156d);
    LD_A(0xfb);
    LD_addr_A(wcd2b);
    RET;

}

void Function10159d(void){
    LD_DE(wc608);
    FARCALL(aFunction100edf);
    LD_DE(wc608);
    LD_A(0x05);
    LD_HL(w5_d800);
    CALL(aFunction10174c);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1015be(void){
    LD_DE(wc608);
    FARCALL(aFunction100eed);
    LD_DE(wc608);
    LD_A(0x05);
    LD_HL(w5_d800);
    CALL(aFunction10174c);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1015df(void){
    LD_DE(wc608);
    FARCALL(aFunction100ef4);
    LD_DE(wc608);
    LD_A(0x05);
    LD_HL(w5_d800);
    CALL(aFunction10174c);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101600(void){
    // LD_HL(w5_d800);
    // LD_DE(wc608);
    // LD_BC(0x1e0);
    // LD_A(0x05);
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(wram->wc608, wram->w5_d800, 0x1e0);
    LD_DE(wc608);
    FARCALL(aFunction100ee6);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function10161f(void){
    // CALL(aFunction101649);
    Function101649();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

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
    CopyBytes_Conv2(wram->wMobileTransferData, hl, 0x1e0);
    // RET;
}

void MobileCopyTransferData2(void* de){
    // LD_HL(wMobileTransferData);
    // LD_BC(0x1e0);
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(de, wram->wMobileTransferData, 0x1e0);
    // RET;
}

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

void Function10168a(void){
    // CALL(aFunction101418);
    // RET_C ;
    if(Function101418())
        return;

    return Function10168e();
}

void Function10168e(void){
    LD_B(0);
    LD_C(0x01);
    FARCALL(aFunction10079c);
    RET_C ;
    LD_C(0x01);
    LD_B(0x03);
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    RET_C ;
    LD_A_addr(wcd26);
    LD_HL(mJumptable_1016c3);
    RST(aJumpTable);
    LD_HL(wcd29);
    SET_hl(6);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Jumptable_1016c3(void){
    //dw ['Function1016cf'];
    //dw ['Function1016de'];
    //dw ['Function1016f8'];
    //dw ['Function101705'];
    //dw ['Function101719'];
    //dw ['Function101724'];

    return Function1016cf();
}

void Function1016cf(void){
    LD_HL(wcd3a);
    INC_hl;
    CALL(aFunction10176f);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function1016de(void){
    CALL(aFunction10177b);
    IF_NC goto asm_1016eb;
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;


asm_1016eb:
    LD_A(0xff);
    LD_addr_A(wcd39);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function1016f8(void){
    LD_A(0);
    LD_addr_A(wcd27);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function101705(void){
    FARCALL(aFunction100382);
    LD_A_addr(wcd27);
    BIT_A(7);
    RET_Z ;
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function101719(void){
    CALL(aFunction1017c7);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function101724(void){
    LD_A_addr(wcd39);
    CP_A(0xff);
    IF_Z goto asm_101731;
    LD_A(0);
    LD_addr_A(wcd26);
    RET;


asm_101731:
    LD_A_addr(wcd26);
    SET_A(7);
    LD_addr_A(wcd26);
    RET;

}

void Unknown_10173a(void){
    //db ['0x50'];

    return Function10173b();
}

void Function10173b(void){
    PUSH_BC;
    PUSH_AF;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(mUnknown_10173a);
    LD_C_A;
    LD_B(0);
    POP_AF;
    CALL(aAddNTimes);
    POP_BC;
    RET;

}

void Function10174c(void){
    LD_addr_A(wcd3d);
    LD_A_L;
    LD_addr_A(wcd3e);
    LD_A_H;
    LD_addr_A(wcd3f);
    LD_A_E;
    LD_addr_A(wcd3b);
    LD_A_D;
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A_C;
    LD_addr_A(wcd40);
    LD_A_B;
    LD_addr_A(wcd41);
    XOR_A_A;
    LD_addr_A(wcd39);
    LD_addr_A(wcd3a);
    RET;

}

void Function10176f(void){
    LD_HL(wccb4);
    LD_BC(0x54);
    LD_A(0x11);
    CALL(aByteFill);
    RET;

}

void Function10177b(void){
    LD_A_addr(mUnknown_10173a);
    LD_C_A;
    LD_B(0);
    LD_A_addr(wcd3a);
    LD_HL(0);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    LD_HL(wcd40);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_L;
    SUB_A_E;
    LD_L_A;
    LD_A_H;
    SBC_A_D;
    LD_H_A;
    IF_C goto asm_1017a0;
    ADD_HL_BC;
    CALL(aFunction1017b0);
    SCF;
    RET;


asm_1017a0:
    LD_A(0xff);
    LD_addr_A(wcd39);
    ADD_HL_BC;
    LD_A_H;
    OR_A_L;
    RET_Z ;
    LD_C_L;
    LD_B_H;
    CALL(aFunction1017b0);
    XOR_A_A;
    RET;

}

void Function1017b0(void){
    LD_A_C;
    LD_addr_A(wccb4);
    PUSH_BC;
    LD_A_addr(wcd3a);
    DEC_A;
    LD_HL(wcd3b);
    CALL(aFunction10173b);
    POP_BC;
    LD_DE(wccb5);
    CALL(aCopyBytes);
    RET;

}

void Function1017c7(void){
    LD_A_addr(wcc60);
    LD_C_A;
    LD_B(0);
    LD_A_addr(wcd3a);
    DEC_A;
    LD_HL(wcd3e);
    CALL(aFunction10173b);
    LD_E_L;
    LD_D_H;
    LD_HL(wcc61);
    LD_A_addr(wcd3d);
    CALL(aFarCopyWRAM);
    AND_A_A;
    RET;

}

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

void Function1017f1(void){
    // CALL(aFunction101418);
    // RET_C ;
    if(Function101418())
        return;

    return Function1017f5();
}

void Function1017f5(void){
    LD_B(0);
    LD_C(0x01);
    FARCALL(aFunction10079c);
    RET_C ;
    LD_C(0x01);
    LD_B(0x03);
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    RET_C ;
    FARCALL(aFunction100382);
    LD_A_addr(wcd27);
    BIT_A(7);
    IF_NZ goto next;
    LD_HL(wcd29);
    SET_hl(6);
    RET;


next:
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101826(void){
    LD_A_addr(wcd21);
    CP_A(0x02);
    IF_Z goto asm_101833;
    CP_A(0x01);
    IF_Z goto asm_101844;
    goto asm_101869;


asm_101833:
    LD_HL(mUnknown_10186f);
    LD_DE(wccb4);
    CALL(aFunction1013f5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101844:
    FARCALL(aFunction103654);
    LD_A_C;
    LD_HL(mUnknown_101882);
    CP_A(0x01);
    IF_Z goto asm_10185b;
    LD_HL(mUnknown_101895);
    CP_A(0x02);
    IF_Z goto asm_10185b;
    goto asm_101869;


asm_10185b:
    LD_DE(wccb4);
    CALL(aFunction1013f5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101869:
    LD_A(0xfe);
    LD_addr_A(wcd2b);
    RET;
}

// pushc
// setcharmap ascii
void Unknown_10186f(void){
    //db ['.end - @'];
    //db ['0x19', '0x73', '0x09', '0x13', '"trade_crystal"'];

// end    db:
// 0

    return Unknown_101882();
}

void Unknown_101882(void){
    //db ['.end - @'];
    //db ['0x19', '0x67', '0x10', '0x01', '"free__crystal"'];

// end    db:
// 0

    return Unknown_101895();
}

void Unknown_101895(void){
    //db ['.end - @'];
    //db ['0x19', '0x67', '0x10', '0x01', '"limit_crystal"'];

// end    db:
// 0

// popc

    return Function1018a8();
}

void Function1018a8(void){
    LD_HL(wccb5);
    LD_DE(wcc61);
    LD_A(0x04);
    CALL(aFunction101406);
    IF_C goto asm_1018d0;
    LD_HL(wccb9);
    LD_DE(wcc65);
    LD_A(0x06);
    CALL(aFunction101406);
    IF_C goto asm_1018ca;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_1018ca:
    LD_A(0xf6);
    LD_addr_A(wcd2b);
    RET;


asm_1018d0:
    LD_A(0xf5);
    LD_addr_A(wcd2b);
    RET;

}

void Function1018d6(void){
    // CALL(aFunction1018ec);
    Function1018ec();
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;

}

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
        *(hl++) = Random_Conv();
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
    CopyBytes_Conv2(wram->wLinkBattleRNs, hl, 10);
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
    CALL(aDisableSpriteUpdates);
    CALL(aClearSprites);
    FARCALL(aFunction1021f9);
    LD_HL(wcd29);
    BIT_hl(3);
    IF_NZ goto asm_101967;
    CALL(aFunction1013c0);
    LD_A(0x71);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101967:
    LD_A(0x60);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void v_SelectMonsForMobileBattle(void){
    FARCALL(aBlankScreen);
    FARCALL(aMobile_CommunicationStandby);
    LD_HL(wcd29);
    SET_hl(5);
    LD_HL(wcd2a);
    SET_hl(6);
    LD_A(0x06);
    LD_addr_A(wccb4);
    LD_HL(wPlayerMonSelection);
    LD_DE(wccb5);
    LD_BC(3);
    CALL(aCopyBytes);
    LD_HL(wcd6c);
    LD_A_hli;
    LD_addr_A(wccb8);
    LD_A_hli;
    LD_addr_A(wccb9);
    LD_A_hl;
    LD_addr_A(wccba);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void v_StartMobileBattle(void){
    CALL(aCopyOtherPlayersBattleMonSelection);
    FARCALL(aFunction100754);
    XOR_A_A;
    LD_addr_A(wdc5f);
    LD_addr_A(wdc60);
    FARCALL(aBlankScreen);
    CALL(aSpeechTextbox);
    FARCALL(aFunction100846);
    LD_C(120);
    CALL(aDelayFrames);
    FARCALL(aClearTilemap);
    CALL(av_StartMobileBattle_CopyOTDetails);
    CALL(aStartMobileBattle);
    LD_A_addr(wcd2b);
    CP_A(0xfc);
    IF_NZ goto asm_1019e6;
    XOR_A_A;
    LD_addr_A(wcd2b);

asm_1019e6:
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


CopyOTDetails:
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(5);
    LDH_addr_A(rSVBK);

    LD_BC(w5_dc0d);
    LD_DE(w5_dc11);
    FARCALL(aGetMobileOTTrainerClass);

    POP_AF;
    LDH_addr_A(rSVBK);

    LD_A_C;
    LD_addr_A(wOtherTrainerClass);
    LD_HL(wOTPlayerName);
    LD_DE(wOTClassName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wcd2f);
    AND_A_A;
    LD_A(USING_INTERNAL_CLOCK);
    IF_Z goto got_link_player_number;
    LD_A(USING_EXTERNAL_CLOCK);

got_link_player_number:
    LDH_addr_A(hSerialConnectionStatus);
    RET;

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
    LD_HL(wcc61);
    LD_DE(wOTMonSelection);
    LD_BC(3);
    CALL(aCopyBytes);
    LD_DE(wcc64);
    FARCALL(aFunction100772);
    FARCALL(aFunction101050);
    FARCALL(aLoadSelectedPartiesForColosseum);
    RET;

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
    UpdateSprites_Conv();
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
    FARCALL(aFunction1005c3);
    LD_HL(wcd29);
    SET_hl(2);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    CALL(aFunction1013dd);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    IF_Z goto asm_101bbc;
    LD_A(0x01);
    LD_addr_A(wcd2f);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101bbc:
    XOR_A_A;
    LD_addr_A(wcd2f);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

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
    FARCALL(aFunction100579);
    LD_HL(wcd29);
    SET_hl(2);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    CALL(aFunction1013dd);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    IF_NZ goto asm_101c0b;
    LD_A(0x2a);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101c0b:
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

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
    FARCALL(aFunction115d99);
    LD_HL(wcd29);
    SET_hl(7);
    LD_C(0x01);
    CALL(aFunction10142c);
    XOR_A_A;
    LD_addr_A(wc30d);
    LD_HL(wcd29);
    RES_hl(4);
    LD_E(0x0b);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    LD_A(0);
    LD_addr_A(wcd26);
    RET;

}

void Function101c92(void){
    FARCALL(aFunction100675);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

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
    FARCALL(aFunction10138b);
    LD_B(0);
    LD_HL(mUnknown_101d8d);
    ADD_HL_BC;
    LD_C_hl;
    LD_A_C;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Unknown_101d8d(void){
    //db ['0x15', '0x15', '0x1f', '0x1f', '0x0c', '0x12', '0x3a', '0x3a'];
}

void Function101d95(void){
    // CALL(aFunction101ee2);
    Function101ee2();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
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
    FARCALL(aFunction103302);
    CALL(aExitMenu);
    LD_HL(wcd29);
    SET_hl(5);
    IF_C goto asm_101dca;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101dca:
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

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
    CALL(aFunction101ecc);
    CALL(aFunction101ead);
    IF_C goto asm_101df3;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101df3:
    CALL(aFunction101e98);
    IF_C goto asm_101e00;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e00:
    CALL(aFunction101ed3);
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101e09(void){
    CALL(aFunction101ead);
    IF_C goto asm_101e16;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e16:
    CALL(aFunction101ecc);
    CALL(aFunction101e98);
    PUSH_AF;
    CALL(aFunction101ed3);
    POP_AF;
    IF_C goto asm_101e2b;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e2b:
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101e31(void){
    // LD_A(0x3a);
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex = 0x3a;
    // JP(mFunction101c2b);
    return Function101c2b();
}

void Function101e39(void){
    CALL(aFunction1020bf);
    PUSH_AF;
    CALL(aFunction101ed3);
    POP_AF;
    IF_C goto asm_101e49;
    LD_A(0x2a);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e49:
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

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
    CALL(aFunction101ecc);
    CALL(aFunction1020a8);
    PUSH_AF;
    CALL(aFunction101ed3);
    POP_AF;
    IF_C goto asm_101e77;
    LD_A(0x24);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e77:
    LD_HL(wcd29);
    SET_hl(5);
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

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

void Function101e98(void){
    CALL(aClearSprites);
    FARCALL(aFunction8adb3);
    RET_C ;
    LD_HL(wGameTimerPaused);
    SET_hl(GAME_TIMER_MOBILE_F);
    LD_HL(wdc41);
    SET_hl(4);
    RET;

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
    FadeToMenu_Conv();
    // RET;
}

void Function101ed3(void){
    CALL(aFunction1013aa);
    FARCALL(aFunction115d99);
    LD_HL(wcd29);
    SET_hl(7);
    RET;

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
            "Call this no.?@";  //next ['"に\u3000でんわを\u3000かけます@"']

const char String_101fd2[] =
            "Calling…@";        //next ['"に\u3000でんわを\u3000かけています@"']

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
    CopyBytes_Conv2(wram->wdc42, de, 8);
}

// ClearBufferWdc42
void Function10209c(void){
    // LD_A(0xff);
    // LD_HL(wdc42);
    // LD_BC(8);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wdc42, sizeof(wram->wdc42), 0xff);
    // RET;
}

void Function1020a8(void){
    CALL(aFunction10209c);
    LD_C(0x01);
    LD_DE(wdc42);
    FARCALL(aFunction17a68f);
    RET_C ;
    CALL(aFunction10208e);
    CALL(aFunction102068);
    XOR_A_A;
    RET;

}

void Function1020bf(void){
    CALL(aClearSprites);
    FARCALL(aFunction8aba9);
    LD_A_C;
    AND_A_A;
    IF_Z goto asm_1020e8;
    DEC_A;
    LD_HL(0xa04c);
    LD_BC(0x25);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_A(0x04);
    CALL(aOpenSRAM);
    CALL(aFunction10208e);
    CALL(aFunction102068);
    CALL(aCloseSRAM);
    XOR_A_A;
    RET;


asm_1020e8:
    SCF;
    RET;

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
    OpenSRAM_Conv(MBANK(as4_a03b));
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
        CloseSRAM_Conv();
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
    CloseSRAM_Conv();
    // POP_AF;
    // RET;
    return 0x1;
}

void Function102142(void){
    CALL(aFunction10218d);
    CALL(aFunction102180);
    LD_HL(mNewCardArrivedText);
    CALL(aMenuTextbox);
    LD_DE(SFX_LEVEL_UP);
    CALL(aPlaySFX);
    CALL(aJoyWaitAorB);
    CALL(aExitMenu);
    CALL(aFunction10219f);
    LD_HL(mPutCardInCardFolderText);
    CALL(aMenuTextbox);
    CALL(aYesNoBox);
    CALL(aExitMenu);
    IF_C goto asm_10217c;
    CALL(aFunction1021b8);
    IF_C goto asm_10217c;
    CALL(aFunction10218d);
    CALL(aFunction102180);
    LD_HL(mCardWasListedText);
    CALL(aPrintText);


asm_10217c:
    CALL(aFunction1013d6);
    RET;

}

void Function102180(void){
    // LD_HL(wc608 + 1);
    // LD_DE(wStringBuffer2);
    // LD_BC(11);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes_Conv2(wram->wStringBuffer2, wram->wc608, NAME_LENGTH);
}

void Function10218d(void){
    // LD_HL(w5_dc00);
    // LD_DE(wc608);
    // LD_BC(0x26);
    // LD_A(0x05);
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(wram->wc608, wram->w5_dc00, 0x26);
    // LD_DE(wc608 + 1);  // useless
    // RET;
}

void Function10219f(void){
    CALL(aFadeToMenu);
    CALL(aFunction10218d);
    LD_DE(wc608 + 1);
    FARCALL(aFunction8ac4e);
    CALL(aJoyWaitAorB);
    CALL(aPlayClickSFX);
    CALL(aFunction1013aa);
    RET;

}

void Function1021b8(void){
    CALL(aFadeToMenu);
    CALL(aFunction10218d);
    LD_DE(wPlayerMoveStruct);
    FARCALL(aFunction8ac70);
    LD_A_C;
    LD_addr_A(wStringBuffer1);
    PUSH_AF;
    CALL(aFunction1013aa);
    POP_AF;
    RET;

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
    MenuTextbox_Conv(txt);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB_Conv();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
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

void Function1021f9(void){
    CALL(aFunction102233);
    LD_A(0x0);  // Function10234b
    LD_addr_A(wcd49);
    LD_HL(wcd29);
    BIT_hl(3);
    RES_hl(3);
    IF_Z goto asm_10220f;
    LD_A(0x1);  // Function102361
    LD_addr_A(wcd49);


asm_10220f:
    CALL(aFunction1022ca);
    LD_A_addr(wcd49);
    LD_HL(mJumptable_1022f5);
    RST(aJumpTable);
    CALL(aFunction102241);
    CALL(aFunction1022d0);
    IF_C goto asm_102231;
    LD_A_addr(wcd49);
    BIT_A(7);
    IF_Z goto asm_10220f;
    XOR_A_A;
    LD_HL(wcd29);
    BIT_hl(3);
    RET_Z ;
    SCF;
    RET;


asm_102231:
    XOR_A_A;
    RET;

}

void Function102233(void){
    LD_HL(wcd49);
    LD_BC(10);
    XOR_A_A;
    CALL(aByteFill);
    CALL(aFunction10304f);
    RET;

}

void Function102241(void){
    CALL(aFunction10226a);
    CALL(aFunction102274);
    CALL(aFunction10224b);
    RET;

}

void Function10224b(void){
    LD_HL(wcd4b);
    BIT_hl(1);
    IF_NZ goto asm_10225e;
    BIT_hl(2);
    IF_NZ goto asm_10225e;
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    XOR_A_A;
    RET;


asm_10225e:
    RES_hl(1);
    RES_hl(2);
    FARCALL(aMobile_ReloadMapPart);
    SCF;
    RET;

}

void Function10226a(void){
    LD_HL(wcd4b);
    BIT_hl(0);
    RET_Z ;
    CALL(aFunction10305d);
    RET;

}

void Function102274(void){
    LD_HL(wcd4b);
    BIT_hl(3);
    RET_Z ;
    RES_hl(3);
    LD_DE(8);
    CALL(aPlaySFX);
    RET;

}

void Function102283(void){
    LD_A(0x01);
    LD_addr_A(wAttrmapEnd);
    LD_HL(wcd4b);
    SET_hl(0);
    RET;

}

void Function10228e(void){
    XOR_A_A;
    LD_addr_A(wAttrmapEnd);
    LD_HL(wcd4b);
    RES_hl(0);
    RET;

}

void Function102298(void){
    LD_A_E;
    CP_A(0x02);
    RET_NZ ;
    LD_HL(wcd4b);
    BIT_hl(6);
    IF_Z goto asm_1022b6;
    LD_HL(wcd4b);
    BIT_hl(7);
    LD_HL(wcd4b);
    SET_hl(7);
    RET_NZ ;
    LD_DE(SFX_ELEVATOR_END);
    CALL(aPlaySFX);
    goto asm_1022c1;


asm_1022b6:
    LD_HL(wcd4b);
    BIT_hl(7);
    LD_HL(wcd4b);
    RES_hl(7);
    RET_Z ;


asm_1022c1:
    CALL(aFunction10304f);
    LD_A(0x01);
    LD_addr_A(wAttrmapEnd);
    RET;

}

void Function1022ca(void){
    LD_A(30);
    LD_addr_A(wOverworldDelay);
    RET;

}

void Function1022d0(void){
    FARCALL(aFunction10032e);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_1022f3;
    CALL(aFunction102298);
    LD_A_addr(wOverworldDelay);
    LD_C_A;
    LD_A(30);
    SUB_A_C;
    LD_C_A;
    LD_B(03);
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    IF_C goto asm_1022f3;
    XOR_A_A;
    RET;


asm_1022f3:
    SCF;
    RET;

}

void Jumptable_1022f5(void){
    //dw ['Function10234b'];  // 00
    //dw ['Function102361'];  // 01
    //dw ['Function10236e'];  // 02
    //dw ['Function102387'];  // 03
    //dw ['Function1023a1'];  // 04
    //dw ['Function1025c7'];  // 05
    //dw ['Function1025dc'];  // 06
    //dw ['Function1024f6'];  // 07
    //dw ['Function10250c'];  // 08
    //dw ['Function1024a8'];  // 09
    //dw ['Function102591'];  // 0a
    //dw ['Function1024a8'];  // 0b
    //dw ['Function1025b0'];  // 0c
    //dw ['Function1025bd'];  // 0d
    //dw ['Function102814'];  // 0e
    //dw ['Function10283c'];  // 0f
    //dw ['Function102862'];  // 10
    //dw ['Function10286f'];  // 11
    //dw ['Function1024a8'];  // 12
    //dw ['Function1028a5'];  // 13
    //dw ['Function1028ab'];  // 14
    //dw ['Function1023b5'];  // 15
    //dw ['Function1023c6'];  // 16
    //dw ['Function1024af'];  // 17
    //dw ['Function102416'];  // 18
    //dw ['Function102423'];  // 19
    //dw ['Function10244b'];  // 1a
    //dw ['Function1024af'];  // 1b
    //dw ['Function10246a'];  // 1c
    //dw ['Function102652'];  // 1d
    //dw ['Function10266b'];  // 1e
    //dw ['Function1025e9'];  // 1f
    //dw ['Function1025ff'];  // 20
    //dw ['Function102738'];  // 21
    //dw ['Function102754'];  // 22
    //dw ['Function1026b7'];  // 23
    //dw ['Function1026c8'];  // 24
    //dw ['Function1028bf'];  // 25
    //dw ['Function1028c6'];  // 26
    //dw ['Function1028d3'];  // 27
    //dw ['Function1028da'];  // 28
    //dw ['Function1024a8'];  // 29
    //dw ['Function10248d'];  // 2a

    return Function10234b();
}

void Function10234b(void){
    CALL(aFunction102d9a);
    CALL(aFunction102dd3);
    CALL(aFunction102dec);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function102361(void){
    LD_A(0xcc);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10236e(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A_addr(wcd51);
    CP_A(0xcc);
    IF_Z goto asm_10237f;
    LD_A(0xf2);
    LD_addr_A(wcd2b);
    RET;


asm_10237f:
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function102387(void){
    LD_HL(wcd4b);
    SET_hl(6);
    XOR_A_A;
    LD_addr_A(wdc5f);
    LD_DE(MUSIC_ROUTE_30);
    CALL(aPlayMusic);
    CALL(aFunction102d9a);
    CALL(aFunction102dd3);
    LD_A(0x01);
    LD_addr_A(wMenuCursorY);

    return Function1023a1();
}

void Function1023a1(void){
    CALL(aFunction102283);
    CALL(aFunction102db7);
    CALL(aFunction102dec);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x1d);
    LD_addr_A(wcd49);
    RET;

}

void Function1023b5(void){
    CALL(aFunction10228e);
    CALL(aFunction102a3b);
    CALL(aFunction102b12);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1023c6(void){
    CALL(aFunction102c48);
    CALL(aFunction102c87);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    LD_HL(wPartyCount);
    INC_hl;
    LD_A_hli;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_hl(0xff);
    LD_A_addr(wPartyCount);
    LD_addr_A(wcd4c);
    CALL(aFunction102c07);
    CALL(aFunction102d48);
    CALL(aFunction102b32);
    CALL(aFunction102f50);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x14);
    LD_addr_A(wcd4e);
    LD_A(0);
    LD_addr_A(wcd4f);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function102416(void){
    LD_A(0xaa);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function102423(void){
    CALL(aFunction102921);
    RET_NC ;
    FARCALL(aSaveAfterLinkTrade);
    FARCALL(aStubbedTrainerRankings_Trades);
    FARCALL(aBackupMobileEventIndex);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10244b(void){
    CALL(aFunction102f32);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x19);
    LD_addr_A(wcd4e);
    LD_A(0);
    LD_addr_A(wcd4f);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10246a(void){
    CALL(aFunction102d9a);
    LD_HL(wcd29);
    SET_hl(3);
    CALL(aFunction102e07);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x2a);
    LD_addr_A(wcd49);
    RET;

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
    LD_A_addr(wcd49);
    SET_A(7);
    LD_addr_A(wcd49);
    RET;

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
    FARCALL(aFunction1009f3);
    RET_C ;

    return Function1024af();
}

void Function1024af(void){
    CALL(aGetJoypad);
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_1024ba);
    RST(aJumpTable);
    RET;

}

void Jumptable_1024ba(void){
    //dw ['Function1024c0'];
    //dw ['Function1024cb'];
    //dw ['Function1024de'];

    return Function1024c0();
}

void Function1024c0(void){
    LD_HL(wcd4e);
    INC_hl;
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);

    return Function1024cb();
}

void Function1024cb(void){
    LD_HL(wcd4e);
    DEC_hl;
    RET_NZ ;
    LD_A_addr(wcd4f);
    INC_A;
    LD_addr_A(wcd4e);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);

    return Function1024de();
}

void Function1024de(void){
    LD_HL(wcd4e);
    DEC_hl;
    IF_Z goto asm_1024e9;
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON | B_BUTTON);
    RET_Z ;


asm_1024e9:
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1024f6(void){
    CALL(aPlaceHollowCursor);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd4c);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10250c(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A_addr(wcd51);
    CP_A(0x0f);
    IF_Z goto asm_10254b;
    AND_A_A;
    IF_Z goto asm_102572;
    CP_A(0xaa);
    IF_Z goto asm_102572;
    CP_A(0x07);
    IF_NC goto asm_102572;
    LD_addr_A(wcd4d);
    DEC_A;
    LD_addr_A(wd003);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_addr_A(wd002);
    CALL(aFunction102b9c);
    CALL(aFunction102bdc);
    IF_C goto asm_10256d;
    FARCALL(aCheckAnyOtherAliveMonsForTrade);
    IF_C goto asm_102568;
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x0e);
    LD_addr_A(wcd49);
    RET;


asm_10254b:
    CALL(aFunction103021);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(0x1e);
    LD_addr_A(wcd4f);
    LD_A(0x29);
    LD_addr_A(wcd49);
    RET;


asm_102568:
    CALL(aFunction102ff5);
    goto asm_102577;


asm_10256d:
    CALL(aFunction102f85);
    goto asm_102577;


asm_102572:
    CALL(aFunction102fce);
    goto asm_102577;


asm_102577:
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(0x3c);
    LD_addr_A(wcd4f);
    LD_A(0x09);
    LD_addr_A(wcd49);
    RET;

}

void Function102591(void){
    CALL(aFunction102ee7);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(0x3c);
    LD_addr_A(wcd4f);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1025b0(void){
    LD_A(0x09);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1025bd(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A(0x04);
    LD_addr_A(wcd49);
    RET;

}

void Function1025c7(void){
    CALL(aFunction102f6d);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x0f);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1025dc(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A_addr(wcd49);
    SET_A(7);
    LD_addr_A(wcd49);
    RET;

}

void Function1025e9(void){
    NOP;
    LD_HL(wcd4b);
    SET_hl(6);
    CALL(aFunction102b4e);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1025ff(void){
    LD_HL(wcd4b);
    SET_hl(2);
    FARCALL(aFunction1009f3);
    RET_C ;
    FARCALL(aMobileMenuJoypad);
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    RET_Z ;
    BIT_C(A_BUTTON_F);
    IF_NZ goto a_button;
    BIT_C(D_UP_F);
    IF_NZ goto d_up;
    BIT_C(D_DOWN_F);
    IF_NZ goto d_down;
    RET;


a_button:
    LD_HL(wcd4b);
    SET_hl(3);
    LD_A(0x27);  // Function1028d3
    LD_addr_A(wcd49);
    RET;


d_up:
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wOTPartyCount);
    CP_A_B;
    RET_NZ ;
    CALL(aHideCursor);
    LD_A_addr(wPartyCount);
    LD_addr_A(wMenuCursorY);
    LD_A(0x1d);  // Function102652
    LD_addr_A(wcd49);
    RET;


d_down:
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    RET_NZ ;
    LD_A(0x23);  // Function1026b7
    LD_addr_A(wcd49);
    RET;

}

void Function102652(void){
    NOP;
    LD_HL(wcd4b);
    SET_hl(6);
    NOP;
    CALL(aFunction102b7b);
    NOP;
    LD_HL(wcd4b);
    SET_hl(1);
    NOP;
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10266b(void){
    LD_HL(wcd4b);
    SET_hl(2);
    FARCALL(aFunction1009f3);
    RET_C ;
    FARCALL(aMobileMenuJoypad);
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    RET_Z ;
    BIT_C(A_BUTTON_F);
    IF_NZ goto a_button;
    BIT_C(D_DOWN_F);
    IF_NZ goto d_down;
    BIT_C(D_UP_F);
    IF_NZ goto d_up;
    RET;


a_button:
    LD_HL(wcd4b);
    SET_hl(3);
    LD_A(0x21);  // Function102738
    LD_addr_A(wcd49);
    RET;


d_down:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    RET_NZ ;
    CALL(aHideCursor);
    LD_A(0x1f);  // Function1025e9
    LD_addr_A(wcd49);
    RET;


d_up:
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wPartyCount);
    CP_A_B;
    RET_NZ ;
    LD_A(0x23);  // Function1026b7
    LD_addr_A(wcd49);
    RET;

}

void Function1026b7(void){
    LD_HL(wcd4b);
    SET_hl(6);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    LD_A(0);
    LD_addr_A(wcd4a);

    return Function1026c8();
}

void Function1026c8(void){
    CALL(aGetJoypad);
    FARCALL(aFunction1009f3);
    RET_C ;
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_1026da);
    RST(aJumpTable);
    RET;

}

void Jumptable_1026da(void){
    //dw ['Function1026de'];
    //dw ['Function1026f3'];

    return Function1026de();
}

void Function1026de(void){
    CALL(aHideCursor);
    hlcoord(9, 17, wTilemap);
    LD_hl(0xed);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    LD_HL(wcd4b);
    SET_hl(1);
    RET;

}

void Function1026f3(void){
    LDH_A_addr(hJoyPressed);
    BIT_A(A_BUTTON_F);
    IF_NZ goto asm_102723;
    BIT_A(D_UP_F);
    IF_NZ goto asm_102712;
    BIT_A(D_DOWN_F);
    IF_NZ goto asm_102702;
    RET;


asm_102702:
    hlcoord(9, 17, wTilemap);
    LD_hl(0x7f);
    LD_A(0x01);
    LD_addr_A(wMenuCursorY);
    LD_A(0x1d);  // Function102652
    LD_addr_A(wcd49);
    RET;


asm_102712:
    hlcoord(9, 17, wTilemap);
    LD_hl(0x7f);
    LD_A_addr(wOTPartyCount);
    LD_addr_A(wMenuCursorY);
    LD_A(0x1f);  // Function1025e9
    LD_addr_A(wcd49);
    RET;


asm_102723:
    hlcoord(9, 17, wTilemap);
    LD_hl(0xec);
    LD_HL(wcd4b);
    SET_hl(3);
    LD_HL(wcd4b);
    SET_hl(2);
    LD_A(0x5);  // Function1025c7
    LD_addr_A(wcd49);
    RET;

}

void Function102738(void){
    LD_HL(wcd4b);
    SET_hl(6);
    CALL(aPlaceHollowCursor);
    CALL(aFunction1027eb);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    LD_A(0);
    LD_addr_A(wcd4a);

    return Function102754();
}

void Function102754(void){
    CALL(aGetJoypad);
    FARCALL(aFunction1009f3);
    RET_C ;
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_102766);
    RST(aJumpTable);
    RET;

}

void Jumptable_102766(void){
    //dw ['Function102770'];
    //dw ['Function102775'];
    //dw ['Function10278c'];
    //dw ['Function1027a0'];
    //dw ['Function1027b7'];

    return Function102770();
}

void Function102770(void){
    LD_A(0x01);
    LD_addr_A(wcd4a);

    return Function102775();
}

void Function102775(void){
    hlcoord(1, 16, wTilemap);
    LD_hl(0xed);
    hlcoord(11, 16, wTilemap);
    LD_hl(0x7f);
    LD_HL(wcd4b);
    SET_hl(2);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    RET;

}

void Function10278c(void){
    LDH_A_addr(hJoyPressed);
    BIT_A(A_BUTTON_F);
    JR_NZ (masm_1027c6);
    BIT_A(B_BUTTON_F);
    JR_NZ (masm_1027e2);
    BIT_A(D_RIGHT_F);
    IF_NZ goto asm_10279b;
    RET;


asm_10279b:
    LD_A(0x03);
    LD_addr_A(wcd4a);
    return Function1027a0();
}

void Function1027a0(void){
    hlcoord(1, 16, wTilemap);
    LD_hl(0x7f);
    hlcoord(11, 16, wTilemap);
    LD_hl(0xed);
    LD_HL(wcd4b);
    SET_hl(2);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    RET;

}

void Function1027b7(void){
    LDH_A_addr(hJoyPressed);
    BIT_A(A_BUTTON_F);
    JR_NZ (masm_1027d1);
    BIT_A(B_BUTTON_F);
    JR_NZ (masm_1027e2);
    BIT_A(D_LEFT_F);
    JR_NZ (mFunction102770);
    RET;

}

void asm_1027c6(void){
    LD_HL(wcd4b);
    SET_hl(3);
    LD_A(0x25);  // Function1028bf
    LD_addr_A(wcd49);
    RET;

}

void asm_1027d1(void){
    LD_HL(wcd4b);
    SET_hl(3);
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wcd4c);
    LD_A(0x7);  // Function1024f6
    LD_addr_A(wcd49);
    RET;

}

void asm_1027e2(void){
    CALL(aFunction102db7);
    LD_A(0x1d);  // Function102652
    LD_addr_A(wcd49);
    RET;

}

void Function1027eb(void){
    hlcoord(0, 14, wTilemap);
    LD_B(2);
    LD_C(18);
    LD_D_H;
    LD_E_L;
    FARCALL(av_LinkTextbox);
    LD_DE(mFunction1027eb_Stats_Trade);
    hlcoord(2, 16, wTilemap);
    CALL(aPlaceString);
    RET;


Stats_Trade:
    //db ['"STATS     TRADE@"'];

    return Function102814();
}

void Function102814(void){
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wcd52);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_addr_A(wd002);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_addr_A(wd003);
    CALL(aFunction102ea8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_HL(wcd4b);
    SET_hl(1);

    return Function10283c();
}

void Function10283c(void){
    LD_HL(wcd4b);
    SET_hl(2);
    CALL(aFunction1029c3);
    RET_Z ;
    IF_C goto asm_102852;
    LD_A(0x10);  // Function102862
    LD_addr_A(wcd49);
    LD_HL(wcd4b);
    SET_hl(1);
    RET;


asm_102852:
    LD_A(0x14);  // Function1028ab
    LD_addr_A(wcd49);
    LD_HL(wcd4b);
    SET_hl(3);
    LD_HL(wcd4b);
    SET_hl(1);
    RET;

}

void Function102862(void){
    LD_A(0x08);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10286f(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A_addr(wcd52);
    LD_addr_A(wMenuCursorY);
    LD_A_addr(wcd51);
    CP_A(0x08);
    IF_NZ goto asm_102886;
    LD_A(0x15);  // Function1023b5
    LD_addr_A(wcd49);
    RET;


asm_102886:
    CALL(aFunction102ee7);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(0x3c);
    LD_addr_A(wcd4f);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1028a5(void){
    LD_A(0x4);  // Function1023a1
    LD_addr_A(wcd49);
    RET;

}

void Function1028ab(void){
    LD_A_addr(wcd52);
    LD_addr_A(wMenuCursorY);
    CALL(aFunction102f15);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0xc);  // Function1025b0
    LD_addr_A(wcd49);
    RET;

}

void Function1028bf(void){
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);

    return Function1028c6();
}

void Function1028c6(void){
    XOR_A_A;
    LD_addr_A(wMonType);
    CALL(aFunction102bac);
    LD_A(0x1d);  // Function102652
    LD_addr_A(wcd49);
    RET;

}

void Function1028d3(void){
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);

    return Function1028da();
}

void Function1028da(void){
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    CALL(aFunction102bac);
    LD_A(0x1f);  // Function1025e9
    LD_addr_A(wcd49);
    RET;

}

void Function1028e8(void){
    LD_HL(wcd4b);
    RES_hl(6);
    LD_addr_A(wcd50);
    FARCALL(aStartMobileInactivityTimer);
    LD_A(0);
    LD_addr_A(wcd4a);
    RET;

}

void Function1028fc(void){
    CALL(aGetJoypad);
    FARCALL(aFunction1009f3);
    IF_NC goto asm_102909;
    AND_A_A;
    RET;


asm_102909:
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_102917);
    RST(aJumpTable);
    RET_NC ;
    LD_A(0);
    LD_addr_A(wcd4a);
    RET;

}

void Jumptable_102917(void){
    //dw ['Function102933'];
    //dw ['Function10294f'];
    //dw ['Function10295d'];
    //dw ['Function10296e'];
    //dw ['Function102996'];

    return Function102921();
}

void Function102921(void){
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_10292f);
    RST(aJumpTable);
    RET_NC ;
    LD_A(0);
    LD_addr_A(wcd4a);
    RET;

}

void Jumptable_10292f(void){
    //dw ['Function10295d'];
    //dw ['Function102984'];

    return Function102933();
}

void Function102933(void){
    LD_HL(mMenuHeader_1029bb);
    CALL(aLoadMenuHeader);
    CALL(aFunction102e07);
    LD_A(0x32);
    LD_addr_A(wTextDelayFrames);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    AND_A_A;
    RET;

}

void Function10294f(void){
    LD_A_addr(wTextDelayFrames);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    AND_A_A;
    RET;

}

void Function10295d(void){
    CALL(aFunction10299e);
    LD_A(0);
    LD_addr_A(wcd27);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    AND_A_A;
    RET;

}

void Function10296e(void){
    FARCALL(aFunction100382);
    AND_A_A;
    LD_A_addr(wcd27);
    BIT_A(7);
    RET_Z ;
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    AND_A_A;
    RET;

}

void Function102984(void){
    FARCALL(aFunction100382);
    AND_A_A;
    LD_A_addr(wcd27);
    BIT_A(7);
    RET_Z ;
    CALL(aFunction1029af);
    SCF;
    RET;

}

void Function102996(void){
    CALL(aFunction1029af);
    CALL(aExitMenu);
    SCF;
    RET;

}

void Function10299e(void){
    LD_A(0x01);
    LD_addr_A(wccb4);
    LD_A_addr(wcd50);
    LD_addr_A(wccb5);
    LD_A(0xaa);
    LD_addr_A(wcd51);
    RET;

}

void Function1029af(void){
    LD_HL(wcd4b);
    RES_hl(7);
    LD_A_addr(wcc61);
    LD_addr_A(wcd51);
    RET;

}

void MenuHeader_1029bb(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['3', '10', '15', '12'];
    //dw ['NULL'];
    //db ['1'];  // default option

    return Function1029c3();
}

void Function1029c3(void){
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_1029cb);
    RST(aJumpTable);
    RET;

}

void Jumptable_1029cb(void){
    //dw ['Function1029cf'];
    //dw ['Function1029fe'];

    return Function1029cf();
}

void Function1029cf(void){
    CALL(aLoadStandardMenuHeader);
    hlcoord(10, 7, wTilemap);
    LD_B(3);
    LD_C(8);
    LD_D_H;
    LD_E_L;
    FARCALL(av_LinkTextbox);
    LD_DE(mString_102a26);
    hlcoord(12, 8, wTilemap);
    CALL(aPlaceString);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_DE(mMenuData3_102a33);
    CALL(aLoad2DMenuData);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    XOR_A_A;
    RET;

}

void Function1029fe(void){
    FARCALL(aFunction1009f3);
    RET_C ;
    FARCALL(aMobileMenuJoypad);
    LD_A_C;
    LD_HL(wMenuJoypadFilter);
    AND_A_hl;
    RET_Z ;
    PUSH_AF;
    CALL(aExitMenu);
    POP_AF;
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    IF_NZ goto asm_102a21;
    LD_A(0x01);
    AND_A_A;
    RET;


asm_102a21:
    LD_A(0x01);
    AND_A_A;
    SCF;
    RET;

}

void String_102a26(void){
    //db ['"TRADE"'];
    //next ['"CANCEL"']
    //db ['"@"'];

    return MenuData3_102a33();
}

void MenuData3_102a33(void){
    //db ['8', '11'];  // cursor start y, x
    //db ['2', '1'];  // rows, columns
    //db ['0x80', '0x00'];  // flags
    //dn ['2', '0'];  // cursor offset
    //db ['A_BUTTON'];  // accepted buttons

    return Function102a3b();
}

void Function102a3b(void){
    LD_A_addr(wcd30);
    LD_addr_A(wc74e);
    LD_HL(wPlayerName);
    LD_DE(wPlayerTrademonSenderName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wPlayerTrademonSpecies);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_HL(wPartyMonOTs);
    CALL(aSkipNames);
    LD_DE(wPlayerTrademonOTName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_HL(wPartyMon1ID);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wPlayerTrademonID);
    LD_A_hl;
    LD_addr_A(wPlayerTrademonID + 1);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_HL(wPartyMon1DVs);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wPlayerTrademonDVs);
    LD_A_hl;
    LD_addr_A(wPlayerTrademonDVs + 1);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_HL(wPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_B_H;
    LD_C_L;
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wPlayerTrademonCaughtData);
    LD_HL(wOTPlayerName);
    LD_DE(wOTTrademonSenderName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);

    LD_A_addr(wcd4d);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wOTTrademonSpecies);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMonOTs);
    CALL(aSkipNames);
    LD_DE(wOTTrademonOTName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMon1ID);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wOTTrademonID);
    LD_A_hl;
    LD_addr_A(wOTTrademonID + 1);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMon1DVs);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wOTTrademonDVs);
    LD_A_hl;
    LD_addr_A(wOTTrademonDVs + 1);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_B_H;
    LD_C_L;
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wOTTrademonCaughtData);
    RET;

}

void Function102b12(void){
    LD_C(100);
    CALL(aDelayFrames);
    CALL(aFunction102d9a);
    CALL(aLoadFontsBattleExtra);
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_NZ goto asm_102b2b;
    FARCALL(aFunction108026);
    goto asm_102b31;


asm_102b2b:
    FARCALL(aFunction10802a);


asm_102b31:
    RET;

}

void Function102b32(void){
    LD_A_addr(wcd4c);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    LD_A(0x01);
    LD_addr_A(wForceEvolution);
    FARCALL(aEvolvePokemon);
    CALL(aFunction102d9a);
    CALL(aFunction102dd3);
    CALL(aFunction102dec);
    RET;

}

void Function102b4e(void){
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    LD_DE(mMenuData_102b73);
    CALL(aLoad2DMenuData);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    LD_A_addr(wOTPartyCount);
    LD_addr_A(w2DMenuNumRows);
    RET;

}

void Function102b68(void){
//  //  unreferenced
    XOR_A_A;
    LD_HL(wWindowStackPointer);
    LD_BC(0x10);
    CALL(aByteFill);
    RET;

}

void MenuData_102b73(void){
    //db ['9', '6'];  // cursor start y, x
    //db ['-1', '1'];  // rows, columns
    //db ['0xa0', '0x00'];  // flags
    //dn ['1', '0'];  // cursor offset
    //db ['D_UP | D_DOWN | A_BUTTON'];  // accepted buttons

    return Function102b7b();
}

void Function102b7b(void){
    XOR_A_A;
    LD_addr_A(wMonType);
    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    LD_DE(mMenuData_102b94);
    CALL(aLoad2DMenuData);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    LD_A_addr(wPartyCount);
    LD_addr_A(w2DMenuNumRows);
    RET;

}

void MenuData_102b94(void){
    //db ['1', '6'];  // cursor start y, x
    //db ['255', '1'];  // rows, columns
    //db ['0xa0', '0x00'];  // flags
    //dn ['1', '0'];  // cursor offset
    //db ['D_UP | D_DOWN | A_BUTTON'];  // accepted buttons

    return Function102b9c();
}

void Function102b9c(void){
    LD_A_addr(wcd4d);
    DEC_A;
    hlcoord(6, 9, wTilemap);
    LD_BC(0x14);
    CALL(aAddNTimes);
    LD_hl(0xec);
    RET;

}

void Function102bac(void){
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    CALL(aLowVolume);
    CALL(aClearSprites);
    FARCALL(av_MobileStatsScreenInit);
    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_addr_A(wMenuCursorY);
    CALL(aFunction102d9a);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(aMaxVolume);
    CALL(aFunction102dd3);
    CALL(aFunction102dec);
    CALL(aFunction102db7);
    RET;

}

void Function102bdc(void){
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMon1Species);
    CALL(aGetPartyLocation);
    PUSH_HL;
    LD_A_addr(wcd4d);
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartyCount);
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    CP_A(EGG);
    IF_Z goto asm_102bfa;
    CP_A_hl;
    IF_NZ goto asm_102c05;


asm_102bfa:
    LD_BC(MON_LEVEL);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(MAX_LEVEL + 1);
    IF_NC goto asm_102c05;
    AND_A_A;
    RET;


asm_102c05:
    SCF;
    RET;

}

void Function102c07(void){
    CALL(aFunction102c14);
    CALL(aFunction102c3b);
    CALL(aFunction102c21);
    CALL(aFunction102c2e);
    RET;

}

void Function102c14(void){
    LD_HL(wPartySpecies);
    LD_DE(wOTPartySpecies);
    LD_BC(1);
    CALL(aFunction102c71);
    RET;

}

void Function102c21(void){
    LD_HL(wPartyMonNicknames);
    LD_DE(wOTPartyMonNicknames);
    LD_BC(11);
    CALL(aFunction102c71);
    RET;

}

void Function102c2e(void){
    LD_HL(wPartyMonOTs);
    LD_DE(wOTPartyMonOTs);
    LD_BC(11);
    CALL(aFunction102c71);
    RET;

}

void Function102c3b(void){
    LD_HL(wPartyMon1);
    LD_DE(wOTPartyMon1);
    LD_BC(0x30);
    CALL(aFunction102c71);
    RET;

}

void Function102c48(void){
    FARCALL(aFunction10165a);
    LD_A(0);
    CALL(aOpenSRAM);
    LD_HL(0xa600);
    LD_DE(wc608);
    LD_BC(0x2f);
    CALL(aFunction102c71);
    CALL(aCloseSRAM);
    LD_HL(wc608);
    LD_DE(w5_da00);
    LD_BC(0x1e0);
    LD_A(0x05);
    CALL(aFarCopyWRAM);
    RET;

}

void Function102c71(void){
    LD_A_addr(wcd4c);
    DEC_A;
    CALL(aAddNTimes);
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    LD_A_addr(wcd4d);
    DEC_A;
    CALL(aAddNTimes);
    POP_DE;
    CALL(aSwapBytes);
    RET;

}

void Function102c87(void){
    LD_A_addr(wJumptableIndex);
    PUSH_AF;
    LD_A_addr(wcf64);
    PUSH_AF;
    LD_A_addr(wcd4c);
    LD_addr_A(wJumptableIndex);
    LD_A_addr(wPartyCount);
    LD_addr_A(wcf64);
    LD_A(0);
    LD_HL(0xa600);
    LD_DE(wc608);
    LD_BC(0x11a);
    CALL(aFunction102d3e);
    CALL(aFunction102cee);
    LD_A(0);
    LD_HL(wc608);
    LD_DE(0xa600);
    LD_BC(0x11a);
    CALL(aFunction102d3e);
    LD_A_addr(wcd4d);
    LD_addr_A(wJumptableIndex);
    LD_A_addr(wOTPartyCount);
    LD_addr_A(wcf64);
    LD_A(0x05);
    LD_HL(w5_da00);
    LD_DE(wc608);
    LD_BC(0x11a);
    CALL(aFarCopyWRAM);
    CALL(aFunction102cee);
    LD_A(0x05);
    LD_HL(wc608);
    LD_DE(w5_da00);
    LD_BC(0x11a);
    CALL(aFarCopyWRAM);
    POP_AF;
    LD_addr_A(wcf64);
    POP_AF;
    LD_addr_A(wJumptableIndex);
    RET;

}

void Function102cee(void){
    LD_A_addr(wJumptableIndex);
    DEC_A;
    CALL(aFunction102d34);
    LD_DE(wd002);
    LD_BC(0x2f);
    CALL(aCopyBytes);
    LD_A_addr(wJumptableIndex);
    LD_C_A;
    LD_A(0x06);
    SUB_A_C;
    RET_Z ;
    LD_BC(0x2f);
    LD_HL(0);
    CALL(aAddNTimes);
    PUSH_HL;
    LD_A_addr(wJumptableIndex);
    DEC_A;
    CALL(aFunction102d34);
    LD_D_H;
    LD_E_L;
    LD_HL(0x2f);
    ADD_HL_DE;
    POP_BC;
    CALL(aCopyBytes);
    LD_A_addr(wcf64);
    DEC_A;
    CALL(aFunction102d34);
    LD_D_H;
    LD_E_L;
    LD_HL(wd002);
    LD_BC(0x2f);
    CALL(aCopyBytes);
    RET;

}

void Function102d34(void){
    LD_HL(wc608);
    LD_BC(0x2f);
    CALL(aAddNTimes);
    RET;

}

void Function102d3e(void){
    CALL(aOpenSRAM);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void Function102d48(void){
    LD_A_addr(wcd4c);
    LD_E_A;
    LD_D(0);
    LD_HL(wPartyCount);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wTempSpecies);
    CP_A(EGG);
    IF_Z goto asm_102d6d;
    DEC_A;
    CALL(aSetSeenAndCaughtMon);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1Happiness);
    CALL(aAddNTimes);
    LD_hl(BASE_HAPPINESS);


asm_102d6d:
    LD_A_addr(wTempSpecies);
    CP_A(UNOWN);
    IF_NZ goto asm_102d98;
    LD_A_addr(wcd4c);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1DVs);
    CALL(aAddNTimes);
    PREDEF(pGetUnownLetter);
    FARCALL(aUpdateUnownDex);
    LD_A_addr(wFirstUnownSeen);
    AND_A_A;
    IF_NZ goto asm_102d98;
    LD_A_addr(wUnownLetter);
    LD_addr_A(wFirstUnownSeen);


asm_102d98:
    AND_A_A;
    RET;

}

void Function102d9a(void){
    LD_A(0x7f);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    LD_A(0x07);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    RET;

}

void Function102db7(void){
    CALL(aFunction102e4f);
    CALL(aFunction102e3e);
    LD_HL(wcd4b);
    SET_hl(1);
    RET;

}

void Function102dc3(void){
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    LD_D_H;
    LD_E_L;
    FARCALL(av_LinkTextbox);
    RET;

}

// MobileComms_LoadTradeLightsGFX
void Function102dd3(void){
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // LD_DE(mMobileTradeLightsGFX);
    // LD_HL(vTiles0);
    // LD_BC((BANK(aMobileTradeLightsGFX) << 8) | 4);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0, MobileTradeLightsGFX, 0, 4);
    // FARCALL(av__LoadTradeScreenBorderGFX);
    v__LoadTradeScreenBorderGFX();
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // RET;
}

void Function102dec(void){
    LD_HL(mMobileTradeLightsPalettes);
    LD_DE(wOBPals1);
    LD_BC(4 * PALETTE_SIZE);
    LD_A(0x05);
    CALL(aFarCopyWRAM);
    FARCALL(aFunction49742);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    RET;

}

void Function102e07(void){
    hlcoord(3, 10, wTilemap);
    LD_B(1);
    LD_C(11);
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_Z goto link_battle;
    CALL(aTextbox);
    goto okay;


link_battle:
//  the next three operations are pointless
    hlcoord(3, 10, wTilemap);
    LD_B(1);
    LD_C(11);
    LD_D_H;
    LD_E_L;
    FARCALL(av_LinkTextbox);


okay:
    LD_DE(mFunction102e07_waiting);
    hlcoord(4, 11, wTilemap);
    CALL(aPlaceString);
    RET;


waiting:
    //db ['"Waiting...!@"'];

    return Function102e3e();
}

void Function102e3e(void){
    LD_DE(mFunction102e3e_CancelString);
    hlcoord(10, 17, wTilemap);
    CALL(aPlaceString);
    RET;


CancelString:
    //db ['"CANCEL@"'];

    return Function102e4f();
}

void Function102e4f(void){
    FARCALL(aLoadMobileTradeBorderTilemap);
    FARCALL(av_InitMG_Mobile_LinkTradePalMap);
    LD_DE(wPlayerName);
    hlcoord(4, 0, wTilemap);
    CALL(aPlaceString);
    LD_A(0x14);
    LD_bc_A;
    LD_DE(wOTPlayerName);
    hlcoord(4, 8, wTilemap);
    CALL(aPlaceString);
    LD_A(0x14);
    LD_bc_A;
    hlcoord(7, 1, wTilemap);
    LD_DE(wPartySpecies);
    CALL(aFunction102e4f_PlaceSpeciesNames);
    hlcoord(7, 9, wTilemap);
    LD_DE(wOTPartySpecies);
    CALL(aFunction102e4f_PlaceSpeciesNames);
    RET;


PlaceSpeciesNames:
    LD_C(0);

count_loop:
    LD_A_de;
    CP_A(0xff);
    RET_Z ;
    LD_addr_A(wNamedObjectIndex);
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    PUSH_HL;
    LD_A_C;
    LDH_addr_A(hDividend);
    CALL(aGetPokemonName);
    POP_HL;
    CALL(aPlaceString);
    POP_DE;
    INC_DE;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    INC_C;
    goto count_loop;

    return Function102ea8();
}

void Function102ea8(void){
    CALL(aFunction102dc3);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wStringBuffer2);
    LD_BC(11);
    CALL(aCopyBytes);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(mTradingMonForOTMonText);
    CALL(aPrintTextboxText);
    RET;

}

void TradingMonForOTMonText(void){
    //text_far ['_TradingMonForOTMonText']
    //text_end ['?']

    return Function102ee7();
}

void Function102ee7(void){
    CALL(aFunction102dc3);
    LD_DE(mString_102ef4);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

const char String_102ef4[] =
            "Too bad! The trade"
    t_next  "was canceled!@";

void Function102f15(void){
    CALL(aFunction102dc3);
    LD_DE(mFunction102f15_TooBadTheTradeWasCanceled);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;


TooBadTheTradeWasCanceled:
    //db ['"こうかんを\u3000キャンセルしました@"'];

    return Function102f32();
}

void Function102f32(void){
    CALL(aFunction102dc3);
    LD_DE(mFunction102f32_TradeCompleted);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;


TradeCompleted:
    //db ['"Trade completed!@"'];

    return Function102f50();
}

void Function102f50(void){
    CALL(aFunction102dc3);
    LD_DE(mFunction102f50_PleaseWait);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;


PleaseWait:
    //db ['"しょうしょう\u3000おまち\u3000ください@"'];

    return Function102f6d();
}

void Function102f6d(void){
    CALL(aFunction102dc3);
    LD_DE(mFunction102f6d_Finished);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;


Finished:
    //db ['"しゅうりょう\u3000します@"'];

    return Function102f85();
}

void Function102f85(void){
    LD_A_addr(wd003);
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    CALL(aFunction102dc3);
    LD_DE(mString_102fb2);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_DE(wStringBuffer1);
    hlcoord(13, 14, wTilemap);
    CALL(aPlaceString);
    LD_DE(mString_102fcc);
    CALL(aPlaceString);
    RET;

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

void Function102fce(void){
    CALL(aFunction102dc3);
    LD_DE(mString_102fdb);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

const char String_102fdb[] = 
            "Your friend's"     // "あいてがわ<NO>せんたくに"
    t_next  "#MON appears"      //next "いじょう<PKMN>あるようです！！"
    t_cont  "to be abnormal!"
    t_done;                     //done ['?']

void Function102ff5(void){
    CALL(aFunction102dc3);
    LD_DE(mString_103002);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

void String_103002(void){
    //db ['"その#を\u3000こうかんすると"'];
    //next ['"せんとう\u3000できなく\u3000なっちゃうよ！"']
    //db ['"@"'];

    return Function103021();
}

void Function103021(void){
    CALL(aFunction102dc3);
    LD_DE(mString_10302e);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

void String_10302e(void){
    //db ['"あいてが\u3000ちゅうしを\u3000えらんだので"'];
    //next ['"こうかんを\u3000ちゅうし\u3000します"']
    //db ['"@"'];

    return Function10304f();
}

void Function10304f(void){
    XOR_A_A;
    LD_addr_A(wAttrmapEnd);
    LD_addr_A(wcf42);
    LD_addr_A(wcf44);
    LD_addr_A(wcf45);
    RET;

}

void Function10305d(void){
    NOP;
    LD_A_addr(wAttrmapEnd);
    AND_A_A;
    RET_Z ;
    CALL(aFunction10307f);
    RET_C ;
    CALL(aFunction103094);
    CALL(aFunction10306e);
    RET;

}

void Function10306e(void){
    LD_A(0x01);
    LDH_addr_A(hOAMUpdate);
    CALL(aClearSprites);
    LD_DE(wVirtualOAM);
    CALL(aFunction1030cd);
    XOR_A_A;
    LDH_addr_A(hOAMUpdate);
    RET;

}

void Function10307f(void){
    LD_C(0x02);
    LD_HL(wcd4b);
    BIT_hl(7);
    IF_Z goto asm_10308a;
    LD_C(0x01);


asm_10308a:
    LD_HL(wcf45);
    INC_hl;
    LD_A_hl;
    CP_A_C;
    RET_C ;
    XOR_A_A;
    LD_hl_A;
    RET;

}

void Function103094(void){
    LD_HL(wcd4b);
    BIT_hl(7);
    IF_NZ goto asm_1030c0;
    LD_A_addr(wcf42);
    BIT_A(7);
    IF_NZ goto asm_1030b2;
    LD_A_addr(wcf44);
    INC_A;
    LD_addr_A(wcf44);
    CP_A(0x2c);
    RET_NZ ;
    LD_HL(wcf42);
    SET_hl(7);
    RET;


asm_1030b2:
    LD_A_addr(wcf44);
    DEC_A;
    LD_addr_A(wcf44);
    RET_NZ ;
    LD_HL(wcf42);
    RES_hl(7);
    RET;


asm_1030c0:
    LD_HL(wcf44);
    LD_A_hl;
    AND_A_A;
    IF_Z goto asm_1030ca;
    DEC_A;
    LD_hl_A;
    RET_NZ ;


asm_1030ca:
    LD_hl(0x2c);
    RET;

}

void Function1030cd(void){
    LD_A_addr(wcf44);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mUnknown_103112);
    ADD_HL_BC;
    LD_B(0x30);
    LD_C(0x08);

asm_1030de:
    PUSH_HL;
    LD_HL(wcd4b);
    BIT_hl(7);
    POP_HL;
    LD_A(0);
    IF_Z goto asm_1030eb;
    LD_A(0x05);

asm_1030eb:

    ADD_A_hl;
    INC_HL;
    PUSH_HL;

    ADD_A_A;
    ADD_A_A;

    ADD_A(LOW(aUnknown_10327a));
    LD_L_A;
    LD_A(HIGH(aUnknown_10327a));
    ADC_A(0);
    LD_H_A;

    LD_A_B;
    ADD_A_hl;
    INC_HL;
    LD_de_A;
    INC_DE;
    LD_A(0x0a);
    ADD_A_hl;
    INC_HL;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    POP_HL;
    LD_A_B;
    ADD_A(0x08);
    LD_B_A;
    DEC_C;
    IF_NZ goto asm_1030de;
    RET;

}

void Unknown_103112(void){
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x01', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x02', '0x01', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x03', '0x02', '0x01', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x04', '0x03', '0x02', '0x01', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x04', '0x04', '0x03', '0x02', '0x01', '0x00', '0x00', '0x00'];
    //db ['0x04', '0x04', '0x04', '0x03', '0x02', '0x01', '0x00', '0x00'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x03', '0x02', '0x01', '0x00'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x03', '0x02', '0x01'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x03', '0x02'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x03'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x03', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x02', '0x03', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x01', '0x02', '0x03', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x00', '0x01', '0x02', '0x03', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x00', '0x00', '0x01', '0x02', '0x03', '0x04', '0x04', '0x04'];
    //db ['0x00', '0x00', '0x00', '0x01', '0x02', '0x03', '0x04', '0x04'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x01', '0x02', '0x03', '0x04'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x01', '0x02', '0x03'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x01', '0x02'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x01'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];

    return Unknown_10327a();
}

void Unknown_10327a(void){
    //db ['0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x01', '0x00'];
    //db ['0x00', '0x00', '0x02', '0x00'];
    //db ['0x00', '0x00', '0x03', '0x00'];
    //db ['0x00', '0x00', '0x01', '0x01'];
    //db ['0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x01', '0x02'];
    //db ['0x00', '0x00', '0x02', '0x02'];
    //db ['0x00', '0x00', '0x03', '0x02'];
    //db ['0x00', '0x00', '0x01', '0x03'];
}

const char MobileTradeLightsGFX[] = "gfx/mobile/mobile_trade_lights.png"; // 2bpp

void MobileTradeLightsPalettes(void){
// INCLUDE "gfx/mobile/mobile_trade_lights.pal"

    return Function103302();
}

void Function103302(void){
    CALL(aFunction103309);
    CALL(aFunction103362);
    RET;

}

void Function103309(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_HL(wd1ea);
    LD_BC(10);
    XOR_A_A;
    CALL(aByteFill);
    LD_A(BANK(s4_a60c));
    CALL(aOpenSRAM);
    LD_A_addr(wdc41);
    LD_addr_A(s4_a60c);
    LD_addr_A(wd1ea);
    CALL(aCloseSRAM);
    CALL(aFunction1035c6);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_addr_A(wd1ef);
    LD_A_hli;
    LD_addr_A(wd1ec);
    LD_A_hli;
    LD_addr_A(wd1ed);
    LD_H_D;
    LD_L_E;
    CALL(aFunction3eea);
    LD_HL(wd1ec);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hl;
    LD_addr_A(wd1ee);
    CALL(aFunction1034be);
    CALL(aUpdateSprites);
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    LD_A(0x01);
    LD_addr_A(wd1f0);
    CALL(aFunction10339a);
    RET;

}

void Function103362(void){

asm_103362:
    LD_A_addr(wd1f0);
    LD_addr_A(wd1f1);
    CALL(aFunction1033af);
    CALL(aFunction10339a);
    CALL(aFunction10342c);
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    LD_A_addr(wd1eb);
    BIT_A(7);
    IF_Z goto asm_103362;
    LD_HL(wd1eb);
    BIT_hl(6);
    IF_Z goto asm_103398;
    LD_A(BANK(s4_a60c));
    CALL(aOpenSRAM);
    LD_A_addr(wd1ea);
    LD_addr_A(s4_a60c);
    LD_addr_A(wdc41);
    CALL(aCloseSRAM);
    XOR_A_A;
    RET;


asm_103398:
    SCF;
    RET;

}

void Function10339a(void){
    LD_A_addr(wd1f0);
    LD_addr_A(wd1f2);
    LD_C_A;
    LD_B(0);
    LD_HL(wd1ec);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wd1f3);
    RET;

}

void Function1033af(void){
    CALL(aGetJoypad);
    LDH_A_addr(hJoyPressed);
    BIT_A(D_LEFT_F);
    IF_NZ goto left;
    BIT_A(D_RIGHT_F);
    IF_NZ goto right;
    BIT_A(B_BUTTON_F);
    IF_NZ goto b;
    BIT_A(A_BUTTON_F);
    IF_NZ goto a;
    BIT_A(D_UP_F);
    IF_NZ goto up;
    BIT_A(D_DOWN_F);
    IF_NZ goto down;
    RET;


up:
    LD_A_addr(wd1f0);
    DEC_A;
    LD_addr_A(wd1f0);
    CP_A(1);
    RET_NC ;
    LD_A_addr(wd1ee);
    LD_addr_A(wd1f0);
    RET;


down:
    LD_A_addr(wd1f0);
    INC_A;
    LD_addr_A(wd1f0);
    LD_C_A;
    LD_A_addr(wd1ee);
    CP_A_C;
    RET_NC ;
    LD_A(1);
    LD_addr_A(wd1f0);
    RET;


b:
    CALL(aPlayClickSFX);
    LD_HL(wd1eb);
    SET_hl(7);
    RET;


a:
    LD_A_addr(wd1f3);
    CP_A(3);
    IF_NZ goto a_return;
    LD_DE(SFX_TRANSACTION);
    CALL(aPlaySFX);
    LD_HL(wd1eb);
    SET_hl(7);
    LD_HL(wd1eb);
    SET_hl(6);
    RET;


left:

right:

a_return:
    LD_A_addr(wd1f3);
    CP_A(3);
    RET_Z ;
    LD_DE(SFX_PUSH_BUTTON);
    CALL(aPlaySFX);
    LD_BC(8);
    CALL(aFunction10350f);
    LD_A_addr(wd1ea);
    XOR_A_E;
    LD_addr_A(wd1ea);
    RET;

}

void Function10342c(void){
    LD_A_addr(wd1f0);
    LD_addr_A(wd1f2);
    CALL(aFunction103490);
    CALL(aFunction10343c);
    CALL(aFunction1034a7);
    RET;

}

void Function10343c(void){
    LD_A_addr(wd1f3);
    CP_A(0x02);
    IF_NZ goto asm_103452;
    LD_BC(1);
    CALL(aFunction1034f7);
    LD_C(0x12);
    LD_B(0x01);
    CALL(aFunction1034e0);
    goto asm_10345f;


asm_103452:
    LD_BC(0xffed);
    CALL(aFunction1034f7);
    LD_C(0x12);
    LD_B(0x02);
    CALL(aFunction1034e0);


asm_10345f:
    LD_BC(0);
    CALL(aFunction10350f);
    LD_BC(1);
    CALL(aFunction103487);
    LD_BC(8);
    CALL(aFunction10350f);
    LD_A_addr(wd1ea);
    AND_A_E;
    LD_BC(2);
    IF_Z goto asm_10347d;
    LD_BC(4);


asm_10347d:
    CALL(aFunction10350f);
    LD_BC(11);
    CALL(aFunction103487);
    RET;

}

void Function103487(void){
    PUSH_DE;
    CALL(aFunction1034f7);
    POP_DE;
    CALL(aPlaceString);
    RET;

}

void Function103490(void){
    hlcoord(0, 15, wTilemap);
    LD_C(0x14);
    LD_B(0x03);
    CALL(aFunction1034e0);
    LD_BC(6);
    CALL(aFunction10350f);
    hlcoord(1, 16, wTilemap);
    CALL(aPlaceString);
    RET;

}

void Function1034a7(void){
    LD_A_addr(wd1f1);
    LD_addr_A(wd1f2);
    LD_BC(10);
    CALL(aFunction1034f7);
    LD_hl(0x7f);
    LD_BC(10);
    CALL(aFunction1034f1);
    LD_hl(0xed);
    RET;

}

void Function1034be(void){
    LD_A(0x01);
    LD_addr_A(wd1f2);
    LD_HL(wd1ec);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hli;

asm_1034ca:
    PUSH_AF;
    LD_A_hli;
    PUSH_HL;
    LD_addr_A(wd1f3);
    CALL(aFunction10343c);
    LD_HL(wd1f2);
    INC_hl;
    POP_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_1034ca;
    CALL(aFunction103490);
    RET;

}

void Function1034e0(void){
    PUSH_BC;
    PUSH_HL;
    CALL(aClearBox);
    POP_HL;
    LD_BC(wAttrmap - wTilemap);
    ADD_HL_BC;
    POP_BC;
    LD_A(0x06);
    CALL(aFillBoxWithByte);
    RET;

}

void Function1034f1(void){
    LD_A_addr(wd1f0);
    LD_addr_A(wd1f2);

    return Function1034f7();
}

void Function1034f7(void){
    hlcoord(0, 0, wTilemap);
    ADD_HL_BC;
    LD_A_addr(wd1ef);
    LD_BC(SCREEN_WIDTH);
    CALL(aAddNTimes);
    LD_A_addr(wd1f2);
    DEC_A;
    LD_BC(40);
    CALL(aAddNTimes);
    RET;

}

void Function10350f(void){
    LD_A_addr(wd1f3);
    PUSH_BC;
    LD_HL(mUnknown_103522);
    LD_BC(9);
    CALL(aAddNTimes);
    POP_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    RET;

}

struct Unknown_103522_s {
    const char* title;
    const char* opt1;
    const char* opt2;
    const char* desc;
    uint8_t n;
};

const struct Unknown_103522_s Unknown_103522[] = {
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

void Function1035c6(void){
    FARCALL(aFunction10138b);
    LD_B(0);
    LD_HL(mUnknown_1035d7);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;

}

void Unknown_1035d7(void){
    //dw ['Unknown_1035e7'];
    //dw ['Unknown_1035f3'];
    //dw ['Unknown_103608'];
    //dw ['Unknown_103608'];
    //dw ['Unknown_1035fe'];
    //dw ['AskMobileOrCable'];
    //dw ['AskMobileOrCable'];
    //dw ['AskMobileOrCable'];

    return Unknown_1035e7();
}

void Unknown_1035e7(void){
    //dwcoord ['0', '6'];
    //db ['0x12', '0x07', '0x07'];
    //dw ['.this'];

this:
    //db ['4', '2', '1', '0', '3'];

    return Unknown_1035f3();
}

void Unknown_1035f3(void){
    //dwcoord ['0', '7'];
    //db ['0x12', '0x06', '0x09'];
    //dw ['.this'];

this:
    //db ['3', '2', '1', '3'];

    return Unknown_1035fe();
}

void Unknown_1035fe(void){
    //dwcoord ['0', '9'];
    //db ['0x12', '0x04', '0x0b'];
    //dw ['.this'];

this:
    //db ['2', '0', '3'];

    return Unknown_103608();
}

void Unknown_103608(void){
    //dwcoord ['0', '9'];
    //db ['0x12', '0x04', '0x0b'];
    //dw ['.this'];

// this:
    //db ['2', '2', '3'];
}

void AskMobileOrCable(void){
    // LD_HL(mMenuHeader_103640);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_103640);
    // LD_A_addr(wMobileOrCable_LastSelection);
    // AND_A(0x0f);
    // IF_Z goto skip_load;
    if((wram->wMobileOrCable_LastSelection & 0x0f) != 0){
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = wram->wMobileOrCable_LastSelection & 0x0f;
    }

// skip_load:
    // CALL(aVerticalMenu);
    bool cancel = !VerticalMenu_Conv();
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
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
            "NETWORK", //db ['"モバイル@"'];
            "LAN", //db ['"ケーブル@"'];
        },
    },
};

const struct MenuHeader MenuHeader_103640 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(13, 6, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
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
        PrintText_Conv2(MobileBattleMustPickThreeMonText);
        // CALL(aYesNoBox);
        // IF_C goto asm_103696;
        if(YesNoBox_Conv()){
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
            JoyWaitAorB_Conv();
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
            PrintText_Conv2(MobileBattleMoreInfoText);
            // CALL(aYesNoBox);
            // IF_C goto asm_1036b5;
            if(YesNoBox_Conv()){
                // CALL(aFunction1036f9);
                Function1036f9();
                // CALL(aJoyWaitAorB);
                JoyWaitAorB_Conv();
            }
        }

        while(!Function103700()){
        // asm_1036b5:
            // CALL(aFunction103700);
            // IF_C goto asm_1036f4;
            // LD_HL(mMenuHeader_103747);
            // CALL(aLoadMenuHeader);
            LoadMenuHeader_Conv2(&MenuHeader_103747);
            // CALL(aVerticalMenu);
            bool quit = !VerticalMenu_Conv();
            // CALL(aExitMenu);
            ExitMenu_Conv2();
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
                JoyWaitAorB_Conv();
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
                JoyWaitAorB_Conv();
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
    PrintText_Conv2(MobileBattleRulesText);
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
        PrintText_Conv2(WouldYouLikeToMobileBattleText);
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
        PrintText_Conv2(WantAQuickMobileBattleText);
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
        PrintText_Conv2(WantToRushThroughAMobileBattleText);
        // AND_A_A;
        // RET;
        return false;
    }
    // goto times_up;
    else {
    // times_up:
        // LD_HL(mPleaseTryAgainTomorrowText);
        // CALL(aPrintText);
        PrintText_Conv2(PleaseTryAgainTomorrowText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
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
    bool saved = Link_SaveGame();
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
        PrintText_Conv2(TryAgainUsingSameSettingsText);
        // CALL(aYesNoBox);
        bool yes = YesNoBox_Conv();
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
        PrintText_Conv2(MobileBattleLessThanOneMinuteLeftText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
        // LD_HL(mMobileBattleNoTimeLeftForLinkingText);
        // CALL(aPrintText);
        PrintText_Conv2(MobileBattleNoTimeLeftForLinkingText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
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
    PrintText_Conv2(PickThreeMonForMobileBattleText);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB_Conv();
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
    CopyBytes_Conv2(wram->wPlayerMonSelection, wram->wMobileAdapterPlayerSelectionBuffer, 3);
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
    PrintText_Conv2(MobileBattleRemainingTimeText);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB_Conv();
    // RET;
}

const txt_cmd_s MobileBattleRemainingTimeText[] = {
    text_far(v_MobileBattleRemainingTimeText)
    text_end
};
