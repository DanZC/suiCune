#include "../constants.h"
#include "mobile_46.h"
#include "mobile_41.h"
#include "mobile_42.h"
#include "mobile_45_sprite_engine.h"
#include "mobile_45_stadium.h"
#include "mobile_5c.h"
#include "mobile_5f.h"
#include "../home/audio.h"
#include "../home/copy.h"
#include "../home/sram.h"
#include "../home/joypad.h"
#include "../home/menu.h"
#include "../home/map.h"
#include "../home/text.h"
#include "../home/tilemap.h"
#include "../home/delay.h"
#include "../home/names.h"
#include "../home/double_speed.h"
#include "../home/mobile.h"
#include "../home/map_objects.h"
#include "../home/print_text.h"
#include "../home/clear_sprites.h"
#include "../home/pokemon.h"
#include "../home/pokedex_flags.h"
#include "../home/time.h"
#include "../engine/events/poke_seer.h"
#include "../engine/events/battle_tower/battle_tower.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/sprites.h"
#include "../engine/gfx/mon_icons.h"
#include "../engine/menus/save.h"
#include "../engine/pokemon/bills_pc_top.h"
#include "../engine/pokemon/evolve.h"
#include "../engine/pokemon/mon_stats.h"
#include "../engine/pokemon/move_mon.h"
#include "../engine/pokedex/pokedex.h"
#include "../util/network.h"
#include "../charmap.h"
#include <stddef.h>
#include <string.h>

// static uint8_t gMobileMessageBuffer[256];

static uint8_t* gMobileMessagePtr; // wc31b-wc31c
static const txt_cmd_s* gMobileTextPtr; // wc31b-wc31c
static tile_t* gMobileMessageDestPtr; // wc31d-wc31e
static const char** gMobileStringList; // wcd4b-wdc4c
uint8_t* gMobile_wcd4d; // wcd4d-wcd4e

void Function118000(void){
    // LD_A(0x1);
    // LD_addr_A(wcd38);
    wram->wcd38 = 1;
    // JR(masm_11800b);

    return asm_11800b();
}

void Function118007(void){
    // XOR_A_A;
    // LD_addr_A(wcd38);
    wram->wcd38 = 0;

    return asm_11800b();
}

void asm_11800b(void){
    // CALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    // LD_A(0x18);
    // LD_addr_A(wcd33);
    wram->wcd33 = 0x18;
    // LD_A(0x19);
    // LD_addr_A(wcd34);
    wram->wcd34 = 0x19;
    // LD_A(0x4);
    // LD_addr_A(wc3f0);
    wram->wc3f0 = 0x4;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 0x3);

    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aFunction118473);
        Function118473();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0x1b);
        // IF_C goto skip;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0x1b) {
            // LD_A_addr(wcd34);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        }

    // skip:
        // CALL(aFunction1184a5);
        Function1184a5();
        // CALL(aBattleTowerRoomMenu_WriteMessage);
        BattleTowerRoomMenu_WriteMessage();
        // FARCALL(aFunction115dd3);
        Function115dd3();
        // FARCALL(aFunction11619d);
        Function11619d();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // LD_HL(wcd33);
        // CP_A_hl;
        // IF_NZ goto loop;
    } while(wram->wBattleTowerRoomMenuJumptableIndex != wram->wcd33);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // CALL(aBattleTowerRoomMenu_Cleanup);
    BattleTowerRoomMenu_Cleanup();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    return BattleTowerRoomMenu_DoNothing();
}

void BattleTowerRoomMenu_DoNothing(void){
    // RET;
}

void Function11805f(void){
    // LD_A(0x1);
    // LD_addr_A(wcd38);
    wram->wcd38 = 0x1;
    // CALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    // LD_A(0x18);
    // LD_addr_A(wcd33);
    wram->wcd33 = 0x18;
    // LD_A(0x19);
    // LD_addr_A(wcd34);
    wram->wcd34 = 0x19;
    // LD_A(0x4);
    // LD_addr_A(wc3f0);
    wram->wc3f0 = 0x4;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 0x3);

    do {
    // asm_11807d:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aFunction118473);
        Function118473();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0x1b);
        // IF_C goto asm_118090;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0x1b) {
            // LD_A_addr(wcd34);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        }

    // asm_118090:
        // CALL(aFunction11857c);
        Function11857c();
        // CALL(aBattleTowerRoomMenu_WriteMessage);
        BattleTowerRoomMenu_WriteMessage();
        // FARCALL(aFunction115dd3);
        Function115dd3();
        // FARCALL(aFunction11619d);
        Function11619d();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // LD_HL(wcd33);
        // CP_A_hl;
        // IF_NZ goto asm_11807d;
    } while(wram->wBattleTowerRoomMenuJumptableIndex != wram->wcd33);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // CALL(aBattleTowerRoomMenu_Cleanup);
    BattleTowerRoomMenu_Cleanup();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // RET;
}

void Function1180b8(void){
    // CALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    // LD_A(0x22);
    // LD_addr_A(wcd33);
    wram->wcd33 = 0x22;
    // LD_A(0x23);
    // LD_addr_A(wcd34);
    wram->wcd34 = 0x23;
    // LD_A(0x4);
    // LD_addr_A(wc3f0);
    wram->wc3f0 = 0x4;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 0x3);

    do {
    // asm_1180d1:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aFunction118473);
        Function118473();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0x28);
        // IF_C goto asm_1180e4;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0x28) {
            // LD_A_addr(wcd34);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        }

    // asm_1180e4:
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0x10);
        // IF_C goto asm_1180f2;
        // CP_A(0x16);
        // IF_NC goto asm_1180f2;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0x10 && wram->wBattleTowerRoomMenuJumptableIndex < 0x16) {
            // CALL(aFunction11884c);
            Function11884c();
        }

    // asm_1180f2:
        // CALL(aFunction1184ec);
        Function1184ec();
        // CALL(aBattleTowerRoomMenu_WriteMessage);
        BattleTowerRoomMenu_WriteMessage();
        // FARCALL(aFunction115dd3);
        Function115dd3();
        // FARCALL(aFunction11619d);
        Function11619d();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // LD_HL(wcd33);
        // CP_A_hl;
        // IF_NZ goto asm_1180d1;
    } while(wram->wBattleTowerRoomMenuJumptableIndex != wram->wcd33);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // CALL(aBattleTowerRoomMenu_Cleanup);
    BattleTowerRoomMenu_Cleanup();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // RET;
}

// Download honor roll data
void Function11811a(void){
    // LD_A(1);
    // LD_addr_A(wcd38);
    wram->wcd38 = 1;
    // JR(mFunction118125);
    return Mobile_BattleTowerRoomMenu();
}

void v_BattleTowerRoomMenu(void){
    // XOR_A_A;
    // LD_addr_A(wcd38);
    wram->wcd38 = 0;
    return Function118125();
}

void Function118125(void){
    // CALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    // LD_A(0x3);
    // LD_addr_A(wcd33);
    wram->wcd33 = 0x3;
    // LD_A(0xd);
    // LD_addr_A(wcd34);
    wram->wcd34 = 0xd;
    // LD_A(0x4);
    // LD_addr_A(wc3f0);
    wram->wc3f0 = 0x4;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);

    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aFunction118473);
        Function118473();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0xf);
        // IF_C goto skip;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0xf) {
            // LD_A_addr(wcd34);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        }

    // skip:
        // CALL(aBattleTowerRoomMenu_Jumptable);
        BattleTowerRoomMenu_Jumptable();
        // CALL(aBattleTowerRoomMenu_WriteMessage);
        BattleTowerRoomMenu_WriteMessage();
        // FARCALL(aFunction115dd3);
        Function115dd3();
        // FARCALL(aFunction11619d);
        Function11619d();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // LD_HL(wcd33);
        // CP_A_hl;
        // IF_NZ goto loop;
    } while(wram->wBattleTowerRoomMenuJumptableIndex != wram->wcd33);
    // XOR_A_A;
    // LD_addr_A(w3_d000);
    wram->w3_d000[0] = 0;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aBattleTowerRoomMenu_Cleanup);
    BattleTowerRoomMenu_Cleanup();
    // CALL(aFunction118180);
    Function118180();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // RET;
}

void v_BattleTowerRoomMenuMobile(void){
    // XOR_A_A;
    // LD_addr_A(wcd38);
    wram->wcd38 = 0;
    return Mobile_BattleTowerRoomMenu();
}

void Mobile_BattleTowerRoomMenu(void){
    // CALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    wram->wBattleTowerRoomMenuJumptableIndex = 0x0;
    // LD_A(0x3);
    // LD_addr_A(wcd33);
    wram->wcd33 = 0x23;
    // LD_A(0xd);
    // LD_addr_A(wcd34);
    wram->wcd34 = 0x2d;
    // LD_A(0x4);
    // LD_addr_A(wc3f0);
    wram->wc3f0 = 0x4;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 0x3);

    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aFunction118473);
        Function118473();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0xf);
        // IF_C goto skip;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0x32) {
            // LD_A_addr(wcd34);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        }

    // skip:
        // CALL(aBattleTowerRoomMenu_Jumptable);
        BattleTowerRoomMenu_Mobile_Jumptable();
        // CALL(aBattleTowerRoomMenu_WriteMessage);
        BattleTowerRoomMenu_WriteMessage();
        // FARCALL(aFunction115dd3);
        Function115dd3();
        // FARCALL(aFunction11619d);
        Function11619d();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // LD_HL(wcd33);
        // CP_A_hl;
        // IF_NZ goto loop;
    } while(wram->wBattleTowerRoomMenuJumptableIndex != wram->wcd33);
    // XOR_A_A;
    // LD_addr_A(w3_d000);
    wram->w3_d000[0] = 0;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // CALL(aBattleTowerRoomMenu_Cleanup);
    BattleTowerRoomMenu_Cleanup();
    // CALL(aFunction118180);
    Function118180();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // RET;
}

void Function118180(void){
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wScriptVar != 0)
        return;
    // LD_A_addr(wcd38);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd38 == 0)
        return;
    // LD_A(BANK(s5_a89c));  // aka BANK(s5_a8b2)
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_a89c));
    // LD_HL(wcd69);
    // LD_DE(s5_a89c);
    // LD_BC(22);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_a89c), wram->wcd69, 22);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(w3_d202));
    // LDH_addr_A(rSVBK);

    // LD_DE(w3_d202);
    // LD_C(0x96);
    // FARCALL(aCheckStringForErrors_IgnoreTerminator);
    // IF_C goto return_d3;

    // LD_DE(w3_d202);
    // LD_BC((1 << 8) | 0x96);
    // FARCALL(aCheckStringContainsLessThanBNextCharacters);
    // IF_C goto return_d3;
    if(CheckStringForErrors_IgnoreTerminator((const uint8_t*)&wram->w3_d202, HONOR_ROLL_DATA_LENGTH)
    || CheckStringContainsLessThanBNextCharacters((const uint8_t*)&wram->w3_d202, 1, HONOR_ROLL_DATA_LENGTH).flag) {
    // return_d3:
        // LD_A(0xd3);
        // LD_addr_A(wMobileErrorCodeBuffer);
        wram->wMobileErrorCodeBuffer[0] = 0xd3;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0xd3;
        // goto reset_banks;
    }
    else {
        // LD_HL(w3_d202);
        // LD_DE(s5_a8b2);
        // LD_BC(150);
        // CALL(aCopyBytes);
        CopyBytes(GBToRAMAddr(s5_a8b2), &wram->w3_d202, HONOR_ROLL_DATA_LENGTH);
    }

// reset_banks:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

// Mobile_DownloadNews
void Function1181da(void){
    // CALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    wram->wBattleTowerRoomMenuJumptableIndex = 0x0;
    // LD_A(0x2);
    // LD_addr_A(wcd38);
    wram->wcd38 = 0x2;
    // LD_A(0x21);
    // LD_addr_A(wcd33);
    wram->wcd33 = 0x21;
    // LD_A(0x22);
    // LD_addr_A(wcd34);
    wram->wcd34 = 0x22;
    // LD_A(0x4);
    // LD_addr_A(wc3f0);
    wram->wc3f0 = 0x4;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 0x3);

    do {
    // asm_1181f8:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aFunction118473);
        Function118473();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0x28);
        // IF_C goto asm_11820b;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0x28) {
            // LD_A_addr(wcd34);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        }

    // asm_11820b:
        // CALL(aFunction1185c3);
        Function1185c3();
        // CALL(aBattleTowerRoomMenu_WriteMessage);
        BattleTowerRoomMenu_WriteMessage();
        // FARCALL(aFunction115dd3);
        Function115dd3();
        // FARCALL(aFunction11619d);
        Function11619d();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // LD_HL(wcd33);
        // CP_A_hl;
        // IF_NZ goto asm_1181f8;
    } while(wram->wBattleTowerRoomMenuJumptableIndex != wram->wcd33);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // CALL(aBattleTowerRoomMenu_Cleanup);
    BattleTowerRoomMenu_Cleanup();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // RET;
}

// Mobile_UpdateNewsRankings?
void Function118233(void){
    // CALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    wram->wBattleTowerRoomMenuJumptableIndex = 0x0;
    // LD_A(0x1b);
    // LD_addr_A(wcd33);
    wram->wcd33 = 0x1b;
    // LD_A(0x1c);
    // LD_addr_A(wcd34);
    wram->wcd34 = 0x1c;
    // LD_A(0x6);
    // LD_addr_A(wc3f0);
    wram->wc3f0 = 0x6;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 0x3);

    do {
    // asm_11824c:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aFunction118473);
        Function118473();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0x1e);
        // IF_C goto asm_11825f;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0x1e) {
            // LD_A_addr(wcd34);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        }

    // asm_11825f:
        // CALL(aFunction118624);
        Function118624();
        // CALL(aBattleTowerRoomMenu_WriteMessage);
        BattleTowerRoomMenu_WriteMessage();
        // FARCALL(aFunction115dd3);
        Function115dd3();
        // FARCALL(aFunction11619d);
        Function11619d();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // LD_HL(wcd33);
        // CP_A_hl;
        // IF_NZ goto asm_11824c;
    } while(wram->wBattleTowerRoomMenuJumptableIndex != wram->wcd33);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // CALL(aBattleTowerRoomMenu_Cleanup);
    BattleTowerRoomMenu_Cleanup();
    // RET;
}

void Function118284(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x19);
    LD_addr_A(wcd33);
    LD_A(0x1e);
    LD_addr_A(wcd34);
    LD_A(0x5);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_11829d:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x20);
    IF_C goto asm_1182b0;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);

asm_1182b0:
    CALL(aFunction1186f5);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_11829d;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    RET;

}

void Function1182d5(void){
//  //  unreferenced
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x18);
    LD_addr_A(wcd33);
    LD_A(0x19);
    LD_addr_A(wcd34);
    LD_A(0x4);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_1182ee:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x1b);
    IF_C goto asm_118301;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_118301:
    CALL(aFunction118746);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_1182ee;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    CALL(aReturnToMapFromSubmenu);
    RET;

}

void Function118329(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x15);
    LD_addr_A(wcd33);
    LD_A(0x16);
    LD_addr_A(wcd34);
    LD_A(0x6);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_118342:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x18);
    IF_C goto asm_118355;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_118355:
    CALL(aFunction118671);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_118342;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    RET;

}

void Function11837a(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x16);
    LD_addr_A(wcd33);
    LD_A(0x17);
    LD_addr_A(wcd34);
    LD_A(0x6);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_118393:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x19);
    IF_C goto asm_1183a6;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_1183a6:
    CALL(aFunction1186b2);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_118393;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    RET;

}

void BattleTowerRoomMenu_InitRAM(void){
    // NOP;
    // LDH_A_addr(rIE);
    // LD_addr_A(wcd32);
    wram->wcd32 = gb_read(rIE);
    // CALL(aDoubleSpeed);
    DoubleSpeed();
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LD_addr_A(wMobileErrorCodeBuffer);
    wram->wMobileErrorCodeBuffer[0] = 0;
    // LD_addr_A(wMobileErrorCodeBuffer + 1);
    wram->wMobileErrorCodeBuffer[1] = 0;
    // LD_addr_A(wMobileErrorCodeBuffer + 2);
    wram->wMobileErrorCodeBuffer[2] = 0;
    // LD_addr_A(wcd80);
    wram->wcd80 = 0;
    // LD_addr_A(wcd65);
    wram->wcd65 = 0;
    // LD_addr_A(wcd66);
    wram->wcd66 = 0;
    // LD_addr_A(wcd67);
    wram->wcd67 = 0;
    // LD_addr_A(wcd68);
    wram->wcd68 = 0;
    // LD_addr_A(wc31a);
    wram->wc31a = 0;
    // LD_addr_A(wcd89);
    wram->wcd89 = 0;
    // LD_addr_A(wcd8a);
    wram->wcd8a = 0;
    // LD_addr_A(wcd8b);
    wram->wcd8b = 0;
    // LD_addr_A(wc3ec);
    wram->wc3ec = 0;
    // LD_addr_A(wc3ed);
    wram->wc3ed = 0;
    // LD_addr_A(wc3ee);
    wram->wc3ee = 0;
    // LD_addr_A(wc3ef);
    wram->wc3ef = 0;
    // LD_HL(wVramState);
    // LD_A_hl;
    // LD_addr_A(wcd7f);
    wram->wcd7f = wram->wVramState;
    // SET_hl(1);
    bit_set(wram->wVramState, 1);
    // LD_A((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
    // LDH_addr_A(rIE);
    gb_write(rIE, (1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
    // LD_A(0x1);
    // LDH_addr_A(hMobileReceive);
    hram.hMobileReceive = 0x1;
    // LDH_addr_A(hMobile);
    hram.hMobile = 0x1;
    // NOP;
    // FARCALL(aStubbed_Function106462);
    Stubbed_Function106462();
    // FARCALL(aFunction106464);
    Function106464();
    // FARCALL(aFunction115d99);
    Function115d99();
    // FARCALL(aFunction11615a);
    Function11615a();
    // LD_A(BANK(s5_bfff));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_bfff));
    // XOR_A_A;
    // LD_addr_A(s5_bfff);
    gb_write(s5_bfff, 0);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

// IncrementS5bfff
void Function118440(void){
    // PUSH_AF;
    // LD_A(BANK(s5_bfff));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_bfff));
    // LD_A_addr(s5_bfff);
    // INC_A;
    // LD_addr_A(s5_bfff);
    gb_write(s5_bfff, gb_read(s5_bfff) + 1);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_AF;
    // RET;
}

void BattleTowerRoomMenu_Cleanup(void){
    // NOP;
    // XOR_A_A;
    // LDH_addr_A(hMobileReceive);
    hram.hMobileReceive = 0;
    // LDH_addr_A(hMobile);
    hram.hMobile = 0;
    // LDH_addr_A(hVBlank);
    hram.hVBlank = 0;
    // CALL(aNormalSpeed);
    NormalSpeed();
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // LD_A_addr(wcd32);
    // LDH_addr_A(rIE);
    gb_write(rIE, wram->wcd32);
    // NOP;
    // LD_A_addr(wcd7f);
    // LD_addr_A(wVramState);
    wram->wVramState = wram->wcd7f;
    // LD_A_addr(wMobileErrorCodeBuffer);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wMobileErrorCodeBuffer[0];
    // RET;
}

void Function118473(void){
    // LD_A_addr(wcd65);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd65 == 0)
        return;
    // LD_A_addr(wcd66);
    // INC_A;
    // LD_addr_A(wcd66);
    // CP_A(60);
    // RET_NZ ;
    if(++wram->wcd66 != 60)
        return;
    // XOR_A_A;
    // LD_addr_A(wcd66);
    wram->wcd66 = 0;
    // LD_A_addr(wcd67);
    // INC_A;
    // LD_addr_A(wcd67);
    // CP_A(60);
    // RET_NZ ;
    if(++wram->wcd67 != 60)
        return;
    // LD_A_addr(wcd68);
    // INC_A;
    // LD_addr_A(wcd68);
    // CP_A(99);
    // IF_Z goto ninety_nine;
    if(++wram->wcd68 == 99) {
    // ninety_nine:
        // XOR_A_A;
        // LD_addr_A(wcd65);
        wram->wcd65 = 0;
        // RET;
        return;
    }
    // XOR_A_A;
    // LD_addr_A(wcd67);
    wram->wcd67 = 0;
    // RET;
}

// Mobile_UploadGTSMonJumptable
void Function1184a5(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']
    printf("Upload GTS Mon Jumptable 0x%02x\n", wram->wBattleTowerRoomMenuJumptableIndex);
    switch(wram->wBattleTowerRoomMenuJumptableIndex) {
    // Jumptable:
        case 0x00: return Function11886e(); //dw ['Function11886e'];
        case 0x01: return Function118880(); //dw ['Function118880'];
        case 0x02: return Function11878d(); //dw ['Function11878d'];
        case 0x03: return Function1188b0(); //dw ['Function1188b0'];
        case 0x04: return Function11878d(); //dw ['Function11878d'];
        case 0x05: return Function1188b8(); //dw ['Function1188b8'];
        case 0x06: return Function11878d(); //dw ['Function11878d'];
        case 0x07: return Function1188c0(); //dw ['Function1188c0'];
        case 0x08: return Function11878d(); //dw ['Function11878d'];
        case 0x09: return Function1188c8(); //dw ['Function1188c8'];
        case 0x0a: return Function11878d(); //dw ['Function11878d'];
        case 0x0b: return Function118903(); //dw ['Function118903'];
        case 0x0c: return Function118a8f(); //dw ['Function118a8f'];
        case 0x0d: return Function11878d(); //dw ['Function11878d'];
        case 0x0e: return Function118d80(); //dw ['Function118d80'];
        case 0x0f: return Function118d9b(); //dw ['Function118d9b'];
        case 0x10: return Function11878d(); //dw ['Function11878d'];
        case 0x11: return Function118ded(); //dw ['Function118ded'];
        case 0x12: return Function118e6d(); //dw ['Function118e6d'];
        case 0x13: return Function11878d(); //dw ['Function11878d'];
        case 0x14: return Function11984e(); //dw ['Function11984e'];
        case 0x15: return Function118e76(); //dw ['Function118e76'];
        case 0x16: return Function118e7e(); //dw ['Function118e7e'];
        case 0x17: return Function11878d(); //dw ['Function11878d'];
        case 0x18: return BattleTowerRoomMenu_DoNothing(); //dw ['BattleTowerRoomMenu_DoNothing'];
        case 0x19: return Function118e76(); //dw ['Function118e76'];
        case 0x1a: return BattleTowerRoomMenu_CallRoomMenu2(); //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
        case 0x1b: return Function118e76(); //dw ['Function118e76'];
    }
}

void Function1184ec(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']
    printf("Check GTS Mon Jumptable 0x%02x\n", wram->wBattleTowerRoomMenuJumptableIndex);
    switch(wram->wBattleTowerRoomMenuJumptableIndex) {
    // Jumptable:
        case 0x00: return Function11886e(); //dw ['Function11886e'];
        case 0x01: return Function118880(); //dw ['Function118880'];
        case 0x02: return Function11878d(); //dw ['Function11878d'];
        case 0x03: return Function1188b0(); //dw ['Function1188b0'];
        case 0x04: return Function11878d(); //dw ['Function11878d'];
        case 0x05: return Function1188b8(); //dw ['Function1188b8'];
        case 0x06: return Function11878d(); //dw ['Function11878d'];
        case 0x07: return Function1188c0(); //dw ['Function1188c0'];
        case 0x08: return Function11878d(); //dw ['Function11878d'];
        case 0x09: return Function1188c8(); //dw ['Function1188c8'];
        case 0x0a: return Function11878d(); //dw ['Function11878d'];
        case 0x0b: return Function118903(); //dw ['Function118903'];
        case 0x0c: return Function119954(); //dw ['Function119954'];
        case 0x0d: return Function11878d(); //dw ['Function11878d'];
        case 0x0e: return Function119973(); //dw ['Function119973'];
        case 0x0f: return Function11878d(); //dw ['Function11878d'];
        case 0x10: return Function119987(); //dw ['Function119987'];
        case 0x11: return Function11878d(); //dw ['Function11878d'];
        case 0x12: return Function1199b4(); //dw ['Function1199b4'];
        case 0x13: return Function1199ca(); //dw ['Function1199ca'];
        case 0x14: return Function11878d(); //dw ['Function11878d'];
        case 0x15: return Function1199e2(); //dw ['Function1199e2'];
        case 0x16: return Function119b0d(); //dw ['Function119b0d'];
        case 0x17: return Function11878d(); //dw ['Function11878d'];
        case 0x18: return Function119b6b(); //dw ['Function119b6b'];
        case 0x19: return Function119b3b(); //dw ['Function119b3b'];
        case 0x1a: return Function11878d(); //dw ['Function11878d'];
        case 0x1b: return Function119b52(); //dw ['Function119b52'];
        case 0x1c: return Function11878d(); //dw ['Function11878d'];
        case 0x1d: return Function118e6d(); //dw ['Function118e6d'];
        case 0x1e: return Function11878d(); //dw ['Function11878d'];
        case 0x1f: return Function118e76(); //dw ['Function118e76'];
        case 0x20: return Function118e7e(); //dw ['Function118e7e'];
        case 0x21: return Function11878d(); //dw ['Function11878d'];
        case 0x22: return BattleTowerRoomMenu_DoNothing(); //dw ['BattleTowerRoomMenu_DoNothing'];
        case 0x23: return Function118e76(); //dw ['Function118e76'];
        case 0x24: return BattleTowerRoomMenu_CallRoomMenu2(); //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
        case 0x25: return Function119b45(); //dw ['Function119b45'];
        case 0x26: return Function11878d(); //dw ['Function11878d'];
        case 0x27: return Function119ac9(); //dw ['Function119ac9'];
        case 0x28: return Function118e76(); //dw ['Function118e76'];
    }
}

void BattleTowerRoomMenu_Jumptable(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']

// Jumptable:
    switch(wram->wBattleTowerRoomMenuJumptableIndex) {
        //dw ['BattleTowerRoomMenu_PickLevelMessage'];
        case 0: return BattleTowerRoomMenu_PickLevelMessage();
        //dw ['BattleTowerRoomMenu_PlacePickLevelMenu'];
        case 1: return BattleTowerRoomMenu_PlacePickLevelMenu();
        //dw ['BattleTowerRoomMenu_UpdatePickLevelMenu'];
        case 2: return BattleTowerRoomMenu_UpdatePickLevelMenu();
        //dw ['BattleTowerRoomMenu_DoNothing'];
        case 3: return BattleTowerRoomMenu_DoNothing();
        //dw ['BattleTowerRoomMenu_PartyMonTopsThisLevelMessage'];
        case 4: return BattleTowerRoomMenu_PartyMonTopsThisLevelMessage();
        //dw ['BattleTowerRoomMenu_WaitForMessage'];
        case 5: return BattleTowerRoomMenu_WaitForMessage();
        //dw ['BattleTowerRoomMenu_DelayRestartMenu'];
        case 6: return BattleTowerRoomMenu_DelayRestartMenu();
        //dw ['BattleTowerRoomMenu_QuitMessage'];
        case 7: return BattleTowerRoomMenu_QuitMessage();
        //dw ['BattleTowerRoomMenu_PlaceYesNoMenu'];
        case 8: return BattleTowerRoomMenu_PlaceYesNoMenu();
        //dw ['BattleTowerRoomMenu_UpdateYesNoMenu'];
        case 9: return BattleTowerRoomMenu_UpdateYesNoMenu();
        //dw ['BattleTowerRoomMenu_UberRestrictionMessage'];
        case 10: return BattleTowerRoomMenu_UberRestrictionMessage();
        //dw ['BattleTowerRoomMenu_WaitForMessage'];
        case 11: return BattleTowerRoomMenu_WaitForMessage();
        //dw ['BattleTowerRoomMenu_DelayRestartMenu'];
        case 12: return BattleTowerRoomMenu_DelayRestartMenu();
        //dw ['Function118e76'];  // mobile
        case 13: return Function118e76();
        //dw ['BattleTowerRoomMenu_CallRoomMenu2'];  // mobile
        case 14: return BattleTowerRoomMenu_CallRoomMenu2();
        //dw ['Function118e76'];  // mobile
        case 15: return Function118e76();
    }
}

void BattleTowerRoomMenu_Mobile_Jumptable(void) {
    // the jumptable in the japanese version
    printf("Mobile Battle Tower Jumptable 0x%02x\n", wram->wBattleTowerRoomMenuJumptableIndex);
    switch(wram->wBattleTowerRoomMenuJumptableIndex) {
        case 0x00: return BattleTowerRoomMenu_PickLevelMessage(); // BattleTowerRoomMenu_PickLevelMessage ;6849
        case 0x01: return BattleTowerRoomMenu_PlacePickLevelMenu(); //7C49
        case 0x02: return BattleTowerRoomMenu_UpdatePickLevelMenu(); //C849
        case 0x03: return BattleTowerRoomMenu_Mobile_03(); //9A4A
        case 0x04: return Function11886e(); //B448
        case 0x05: return Function118880(); //C648
        case 0x06: return Function11878d(); //D347
        case 0x07: return Function1188b0(); //F648
        case 0x08: return Function11878d(); //D347
        case 0x09: return Function1188b8(); //FE48
        case 0x0a: return Function11878d(); //D347
        case 0x0b: return Function1188c0(); //0649
        case 0x0c: return Function11878d(); //D347
        case 0x0d: return Function1188c8(); //0E49
        case 0x0e: return Function11878d(); //D347
        case 0x0f: return Function118903(); //4949
        case 0x10: return Function118a65(); //4E4D
        case 0x11: return Function11878d(); //D347
        case 0x12: return Function11891c(); //6249
        case 0x13: return Function118a54(); //3D4D
        case 0x14: return Function11878d(); //D347
        case 0x15: return BattleTowerRoomMenu_Mobile_15(); //A84A
        case 0x16: return BattleTowerRoomMenu_Mobile_16(); //D84A
        case 0x17: return BattleTowerRoomMenu_Mobile_17(); //244B
        case 0x18: return BattleTowerRoomMenu_Mobile_18(); //4D4C
        case 0x19: return BattleTowerRoomMenu_Mobile_19(); //D54C
        case 0x1a: return BattleTowerRoomMenu_Mobile_1a(); //DE4C
        case 0x1b: return BattleTowerRoomMenu_Mobile_1b(); //154D
        case 0x1c: return Function11878d(); //D347
        case 0x1d: return Function118d35(); //5B50
        case 0x1e: return Function118e6d(); //9351
        case 0x1f: return Function11878d(); //D347
        case 0x20: return Function118e76(); //9C51
        case 0x21: return Function118e7e(); //A451
        case 0x22: return Function11878d(); //D347
        case 0x23: return BattleTowerRoomMenu_DoNothing(); //5E40
        case 0x24: return BattleTowerRoomMenu_PartyMonTopsThisLevelMessage(); //B260
        case 0x25: return BattleTowerRoomMenu_WaitForMessage(); //BB60
        case 0x26: return BattleTowerRoomMenu_DelayRestartMenu(); //C860
        case 0x27: return BattleTowerRoomMenu_QuitMessage(); //1261
        case 0x28: return BattleTowerRoomMenu_PlaceYesNoMenu(); //2E61
        case 0x29: return BattleTowerRoomMenu_UpdateYesNoMenu(); //3B61
        case 0x2a: return BattleTowerRoomMenu_UberRestrictionMessage(); //A760
        case 0x2b: return BattleTowerRoomMenu_WaitForMessage(); //BB60
        case 0x2c: return BattleTowerRoomMenu_DelayRestartMenu(); //C860
        case 0x2d: return Function118e76(); //9C51
        case 0x2e: return BattleTowerRoomMenu_CallRoomMenu2(); // Function118e7e AD51
        case 0x2f: return BattleTowerRoomMenu_Mobile_2f(); //6060
        case 0x30: return BattleTowerRoomMenu_Mobile_30(); //6960
        case 0x31: return BattleTowerRoomMenu_Mobile_31(); //7660
        case 0x32: return Function118e76(); //9C51
    }
}

void Function11857c(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']
    printf("Send Battle Tower Record Jumptable 0x%02x\n", wram->wBattleTowerRoomMenuJumptableIndex);

// Jumptable:
    switch(wram->wBattleTowerRoomMenuJumptableIndex) {
        case 0x00: return Function11886e(); //dw ['Function11886e'];
        case 0x01: return Function118880(); //dw ['Function118880'];
        case 0x02: return Function11878d(); //dw ['Function11878d'];
        case 0x03: return Function1188b0(); //dw ['Function1188b0'];
        case 0x04: return Function11878d(); //dw ['Function11878d'];
        case 0x05: return Function1188b8(); //dw ['Function1188b8'];
        case 0x06: return Function11878d(); //dw ['Function11878d'];
        case 0x07: return Function1188c0(); //dw ['Function1188c0'];
        case 0x08: return Function11878d(); //dw ['Function11878d'];
        case 0x09: return Function1188c8(); //dw ['Function1188c8'];
        case 0x0a: return Function11878d(); //dw ['Function11878d'];
        case 0x0b: return Function118903(); //dw ['Function118903'];
        case 0x0c: return Function118a7a(); //dw ['Function118a7a'];
        case 0x0d: return Function11878d(); //dw ['Function11878d'];
        case 0x0e: return Function11891c(); //dw ['Function11891c'];
        case 0x0f: return Function1198ee(); //dw ['Function1198ee'];
        case 0x10: return Function1198f7(); //dw ['Function1198f7'];
        case 0x11: return Function11878d(); //dw ['Function11878d'];
        case 0x12: return Function119937(); //dw ['Function119937'];
        case 0x13: return Function118e6d(); //dw ['Function118e6d'];
        case 0x14: return Function11878d(); //dw ['Function11878d'];
        case 0x15: return Function118e76(); //dw ['Function118e76'];
        case 0x16: return Function118e7e(); //dw ['Function118e7e'];
        case 0x17: return Function11878d(); //dw ['Function11878d'];
        case 0x18: return BattleTowerRoomMenu_DoNothing(); //dw ['BattleTowerRoomMenu_DoNothing'];
        case 0x19: return Function118e76(); //dw ['Function118e76'];
        case 0x1a: return BattleTowerRoomMenu_CallRoomMenu2(); //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
        case 0x1b: return Function118e76(); //dw ['Function118e76'];
    }
}

// Mobile_DownloadNewsJumptable?
void Function1185c3(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']
    printf("Download News Jumptable 0x%02x\n", wram->wBattleTowerRoomMenuJumptableIndex);
    switch(wram->wBattleTowerRoomMenuJumptableIndex) {
    // Jumptable:
        case 0x00: return Function11886e(); //dw ['Function11886e'];
        case 0x01: return Function118880(); //dw ['Function118880'];
        case 0x02: return Function11878d(); //dw ['Function11878d'];
        case 0x03: return Function1188b0(); //dw ['Function1188b0'];
        case 0x04: return Function11878d(); //dw ['Function11878d'];
        case 0x05: return Function1188b8(); //dw ['Function1188b8'];
        case 0x06: return Function11878d(); //dw ['Function11878d'];
        case 0x07: return Function1188c0(); //dw ['Function1188c0'];
        case 0x08: return Function11878d(); //dw ['Function11878d'];
        case 0x09: return Function1188c8(); //dw ['Function1188c8'];
        case 0x0A: return Function11878d(); //dw ['Function11878d'];
        case 0x0B: return Function118903(); //dw ['Function118903'];
        case 0x0C: return Function118aa4(); //dw ['Function118aa4'];
        case 0x0D: return Function11878d(); //dw ['Function11878d'];
        case 0x0E: return Function118e92(); //dw ['Function118e92'];
        case 0x0F: return Function11878d(); //dw ['Function11878d'];
        case 0x10: return Function118eb0(); //dw ['Function118eb0'];
        case 0x11: return Function118ec6(); //dw ['Function118ec6'];
        case 0x12: return Function118f0d(); //dw ['Function118f0d'];
        case 0x13: return Function118f14(); //dw ['Function118f14'];
        case 0x14: return Function118f5e(); //dw ['Function118f5e'];
        case 0x15: return Function11878d(); //dw ['Function11878d'];
        case 0x16: return Function118fc0(); //dw ['Function118fc0'];
        case 0x17: return Function11878d(); //dw ['Function11878d'];
        case 0x18: return Function119054(); //dw ['Function119054'];
        case 0x19: return Function1190d0(); //dw ['Function1190d0'];
        case 0x1a: return Function11878d(); //dw ['Function11878d'];
        case 0x1b: return Function1190ec(); //dw ['Function1190ec'];
        case 0x1c: return Function118e6d(); //dw ['Function118e6d'];
        case 0x1d: return Function11878d(); //dw ['Function11878d'];
        case 0x1e: return Function118e76(); //dw ['Function118e76'];
        case 0x1f: return Function118e7e(); //dw ['Function118e7e'];
        case 0x20: return Function11878d(); //dw ['Function11878d'];
        case 0x21: return BattleTowerRoomMenu_DoNothing(); //dw ['BattleTowerRoomMenu_DoNothing'];
        case 0x22: return Function118e76(); //dw ['Function118e76'];
        case 0x23: return BattleTowerRoomMenu_CallRoomMenu2(); //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
        case 0x24: return BattleTowerRoomMenu_QuitMessage(); //dw ['BattleTowerRoomMenu_QuitMessage'];
        case 0x25: return BattleTowerRoomMenu_PlaceYesNoMenu(); //dw ['BattleTowerRoomMenu_PlaceYesNoMenu'];
        case 0x26: return BattleTowerRoomMenu_UpdateYesNoMenu(); //dw ['BattleTowerRoomMenu_UpdateYesNoMenu'];
        case 0x27: return Function11914e(); //dw ['Function11914e'];
        case 0x28: return Function118e76(); //dw ['Function118e76'];
    }
}

// Mobile_UpdateNewsRankingsJumptable?
void Function118624(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']
    printf("Update News Rankings Jumptable 0x%02x\n", wram->wBattleTowerRoomMenuJumptableIndex);
    switch(wram->wBattleTowerRoomMenuJumptableIndex) {
    // Jumptable:
        case 0x00: return Function118866(); //dw ['Function118866'];
        case 0x01: return Function118880(); //dw ['Function118880'];
        case 0x02: return Function11878d(); //dw ['Function11878d'];
        case 0x03: return Function1188b0(); //dw ['Function1188b0'];
        case 0x04: return Function11878d(); //dw ['Function11878d'];
        case 0x05: return Function1188b8(); //dw ['Function1188b8'];
        case 0x06: return Function11878d(); //dw ['Function11878d'];
        case 0x07: return Function1188c0(); //dw ['Function1188c0'];
        case 0x08: return Function11878d(); //dw ['Function11878d'];
        case 0x09: return Function1188c8(); //dw ['Function1188c8'];
        case 0x0a: return Function11878d(); //dw ['Function11878d'];
        case 0x0b: return Function118903(); //dw ['Function118903'];
        case 0x0c: return Function118aa4(); //dw ['Function118aa4'];
        case 0x0d: return Function11878d(); //dw ['Function11878d'];
        case 0x0e: return Function118e92(); //dw ['Function118e92'];
        case 0x0f: return Function11878d(); //dw ['Function11878d'];
        case 0x10: return Function11915d(); //dw ['Function11915d'];
        case 0x11: return Function118f68(); //dw ['Function118f68'];
        case 0x12: return Function11878d(); //dw ['Function11878d'];
        case 0x13: return Function119009(); //dw ['Function119009'];
        case 0x14: return Function11878d(); //dw ['Function11878d'];
        case 0x15: return Function119054(); //dw ['Function119054'];
        case 0x16: return Function118e6d(); //dw ['Function118e6d'];
        case 0x17: return Function11878d(); //dw ['Function11878d'];
        case 0x18: return Function118e76(); //dw ['Function118e76'];
        case 0x19: return Function118e7e(); //dw ['Function118e7e'];
        case 0x1a: return Function11878d(); //dw ['Function11878d'];
        case 0x1b: return BattleTowerRoomMenu_DoNothing(); //dw ['BattleTowerRoomMenu_DoNothing'];
        case 0x1c: return Function118e76(); //dw ['Function118e76'];
        case 0x1d: return BattleTowerRoomMenu_CallRoomMenu2(); //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
        case 0x1e: return Function118e76(); //dw ['Function118e76'];
    }
}

void Function118671(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function118866'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function119380'];
    //dw ['Function119388'];
    //dw ['Function1193a0'];
    //dw ['Function11878d'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function1186b2();
}

void Function1186b2(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function118866'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function119380'];
    //dw ['Function1193e3'];
    //dw ['Function1193fb'];
    //dw ['Function11878d'];
    //dw ['Function119413'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function1186f5();
}

void Function1186f5(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function11886a'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function118abc'];
    //dw ['Function11878d'];
    //dw ['Function119451'];
    //dw ['Function1195f8'];
    //dw ['Function119612'];
    //dw ['Function119629'];
    //dw ['Function119648'];
    //dw ['Function11878d'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function11967d'];
    //dw ['Function119685'];
    //dw ['Function119665'];
    //dw ['Function11966d'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function118746();
}

void Function118746(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function11886e'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function118ad0'];
    //dw ['Function11878d'];
    //dw ['Function1196f2'];
    //dw ['Function1197c9'];
    //dw ['Function1197dc'];
    //dw ['Function11878d'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function119800'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function11878d();
}

void Function11878d(void){
    // LD_A_addr(wc821);
    // BIT_A(1);
    // IF_NZ goto asm_1187af;
    if(bit_test(wram->wc821, 1)) {
    // asm_1187af:
        mobile_api_data_s data = {};
        // LD_A(MOBILEAPI_00);
        // CALL(aMobileAPI);
        MobileAPI(MOBILEAPI_00, &data);
        // LD_addr_A(wMobileErrorCodeBuffer);
        wram->wMobileErrorCodeBuffer[0] = data.a;
        // LD_A_L;
        // LD_addr_A(wMobileErrorCodeBuffer + 1);
        wram->wMobileErrorCodeBuffer[1] = data.l;
        // LD_A_H;
        // LD_addr_A(wMobileErrorCodeBuffer + 2);
        wram->wMobileErrorCodeBuffer[2] = data.h;
        // LD_A(MOBILEAPI_05);
        // CALL(aMobileAPI);
        MobileAPI(MOBILEAPI_05, &data);
        // LD_A_addr(wc3f0);
        // LD_addr_A(wc319);
        wram->wc319 = wram->wc3f0;
        // LD_A_addr(wcd34);
        // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
        wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        // RET;
        return;
    }
    // BIT_A(2);
    // IF_NZ goto asm_1187d1;
    if(bit_test(wram->wc821, 2)) {
    // asm_1187d1:
        // LD_HL(wcd89);
        // BIT_hl(0);
        // IF_NZ goto asm_118803;
        if(bit_test(wram->wcd89, 0)) {
        // asm_118803:
            // LD_A(0xd3);

            return SetMobileErrorCode(0xd3);
        }
        // SET_hl(0);
        bit_set(wram->wcd89, 0);
        // LD_A(BANK(w6_d000));
        // LDH_addr_A(rSVBK);
        // LD_DE(w6_d000);
        // LD_BC(0x1000);
        mobile_api_data_s data = {.de = wram->w6_d000, .bc = 0x1000};
        uint8_t a;
        // LD_A_hl;
        // SLA_A;
        // IF_C goto asm_1187f9;
        if((wram->wcd89 & 0x80) != 0) {
        // asm_1187f9:
            // LD_A(MOBILEAPI_15);
            a = MOBILEAPI_15;
            // goto asm_1187ff;
        }
        // SLA_A;
        // IF_C goto asm_1187fd;
        else if((wram->wcd89 & 0x40) != 0) {
        // asm_1187fd:
            // LD_A(MOBILEAPI_16);
            a = MOBILEAPI_16;
        }
        // SLA_A;
        // IF_C goto asm_1187f5;
        else if((wram->wcd89 & 0x20) != 0) {
        // asm_1187f5:
            // LD_A(MOBILEAPI_14);
            a = MOBILEAPI_14;
            // goto asm_1187ff;
        }
        else {
            // LD_A(MOBILEAPI_12);
            a = MOBILEAPI_12;
            // goto asm_1187ff;
        }

    // asm_1187ff:
        // CALL(aMobileAPI);
        MobileAPI(a, &data);
        // RET;
        return;
    }
    // BIT_A(0);
    // IF_NZ goto asm_1187aa;
    if(bit_test(wram->wc821, 0)) {
    // asm_1187aa:
        // CALL(aFunction118821);
        // RET_C ;
        if(Function118821())
            return;
        // RET;
        return;
    }
    // LD_A_addr(wcd89);
    // AND_A(0x1);
    // IF_Z goto asm_1187a7;
    if((wram->wcd89 & 0x1) != 0) {
        // LD_A(0x3);
        // LDH_addr_A(rSVBK);
    }

// asm_1187a7:
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    return BattleTowerRoomMenu_IncrementJumptable();
}

void SetMobileErrorCode(uint8_t code){
    // LD_addr_A(wMobileErrorCodeBuffer);
    wram->wMobileErrorCodeBuffer[0] = code;
    // XOR_A_A;
    // LD_addr_A(wMobileErrorCodeBuffer + 1);
    wram->wMobileErrorCodeBuffer[1] = 0x0;
    // LD_addr_A(wMobileErrorCodeBuffer + 2);
    wram->wMobileErrorCodeBuffer[2] = 0x0;
    // LD_A(MOBILEAPI_05);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_05, &(mobile_api_data_s){});
    // LD_A_addr(wc3f0);
    // LD_addr_A(wc319);
    wram->wc319 = wram->wc3f0;
    // LD_A_addr(wcd34);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
    // RET;
}

bool Function118821(void){
    // LD_A_addr(wc319);
    // CP_A(0x3);
    // IF_C goto asm_11884a;
    // CP_A(0x4);
    // IF_Z goto asm_11884a;
    // LDH_A_addr(hJoyDown);
    // CP_A(0x5);
    // IF_NZ goto asm_11884a;
    if(wram->wc319 < 0x3 || wram->wc319 == 0x4 || hram.hJoyDown != (A_BUTTON | SELECT)) {
    // asm_11884a:
        // AND_A_A;
        // RET;
        return false;
    }
    mobile_api_data_s data = {};
    // LD_A(MOBILEAPI_05);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_05, &data);
    // LD_A(0xa);
    // LD_addr_A(wMobileErrorCodeBuffer);
    wram->wMobileErrorCodeBuffer[0] = 0xa;
    // LD_A_addr(wc3f0);
    // LD_addr_A(wc319);
    wram->wc319 = wram->wc3f0;
    // LD_A_addr(wcd34);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
    // SCF;
    // RET;
    return true;
}

bool Function11884c(void){
    // LDH_A_addr(hJoyDown);
    // CP_A(0x5);
    // IF_NZ goto asm_118864;
    if(hram.hJoyDown == (SELECT | A_BUTTON)) {
        mobile_api_data_s data = {};
        // LD_A(MOBILEAPI_05);
        // CALL(aMobileAPI);
        MobileAPI(MOBILEAPI_05, &data);
        // LD_A(0xa);
        // LD_addr_A(wMobileErrorCodeBuffer);
        wram->wMobileErrorCodeBuffer[0] = 0xa;
        // LD_A_addr(wcd34);
        // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
        wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        // SCF;
        // RET;
        return true;
    }

// asm_118864:
    // AND_A_A;
    // RET;
    return false;
}

void Function118866(void){
    // LD_A(2);
    // JR(masm_11886f);
    return asm_11886f(2);
}

void Function11886a(void){
    // LD_A(1);
    // JR(masm_11886f);
    return asm_11886f(1);
}

void Function11886e(void){
    // XOR_A_A;

    return asm_11886f(0);
}

void asm_11886f(uint8_t a){
    // LD_addr_A(wBGMapPalBuffer);
    wram->wcd48 = a;
    // LD_A(0x0);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x0;
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
    // LD_A_addr(wcd33);
    // LD_addr_A(wMobileInactivityTimerSeconds);
    wram->wMobileInactivityTimerSeconds = wram->wcd33;

    return Function118880();
}

void Function118880(void){
    // CALL(aBattleTowerRoomMenu2);
    // RET_C ;
    if(BattleTowerRoomMenu2())
        return;
    // XOR_A_A;
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x0;
    // LD_addr_A(wc807);
    wram->wc807 = 0x0;
    // LD_DE(wcd81);
    // LD_HL(0x46);
    // LD_A(MOBILEAPI_01);
    // JP(mFunction119e2b);
    Function119e2b(MOBILEAPI_01, &(mobile_api_data_s){.de = &wram->wcd81, .l = 0x46});
}

void Function118896(void){
//  //  unreferenced
    LD_A_addr(wc821);
    BIT_A(1);
    IF_NZ goto asm_1188a5;
    BIT_A(2);
    IF_NZ goto asm_1188a5;
    BIT_A(0);
    IF_Z goto asm_1188aa;


asm_1188a5:
    LD_A(MOBILEAPI_1A);
    JP(mFunction119e2b);


asm_1188aa:
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function1188b0(void){
    // LD_DE(wc346);
    // LD_A(MOBILEAPI_06);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_06, &(mobile_api_data_s){.de = wram->wc346});
}

void Function1188b8(void){
    // LD_DE(wc3ac);
    // LD_A(MOBILEAPI_07);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_07, &(mobile_api_data_s){.de = wram->wc3ac});
}

void Function1188c0(void){
    // LD_DE(wc3cd);
    // LD_A(MOBILEAPI_08);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_08, &(mobile_api_data_s){.de = wram->wc3cd});
}

void Function1188c8(void){
    // LD_A(0x1);
    // LD_addr_A(wcd65);
    wram->wcd65 = 0x1;
    // CALL(aFunction1188e7);
    const uint8_t* de = Function1188e7();
    // LD_HL(wc708);
    uint8_t* hl = wram->wMobilePasswordBuffer;
    uint8_t a;

    do {
    // asm_1188d3:
        // LD_A_de;
        // INC_DE;
        a = *(de++);
        // LD_hli_A;
        *(hl++) = a;
        // AND_A_A;
        // IF_NZ goto asm_1188d3;
    } while(a != 0);
    // CALL(aFunction119eb4);
    hl = Function119eb4(hl);
    // CALL(aFunction119ec2);
    Function119ec2(hl);
    // LD_HL(wc708);
    // LD_A(MOBILEAPI_03);
    // JP(mFunction119e2b);
    Function119e2b(MOBILEAPI_03, &(mobile_api_data_s){.hl = wram->wMobilePasswordBuffer});
}

uint8_t* Function1188e7(void){
    // LD_DE(wc346);
    uint8_t* de = wram->wc346;
    // LD_A(BANK(s5_aa4a));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_aa4a));
    // LD_A_addr(s5_aa4a);
    uint8_t aa4a = gb_read(s5_aa4a);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // AND_A_A;
    // RET_Z ;
    if(aa4a == 0)
        return de;
    // SLA_A;
    // LD_C_A;
    uint8_t c = aa4a << 1;
    uint8_t a;

    do {
    // asm_1188fa:
        // LD_A_de;
        a = *(de++);
        // INC_DE;
        // AND_A_A;
        // IF_NZ goto asm_1188fa;
        // DEC_C;
        // IF_NZ goto asm_1188fa;
    } while(a != 0 && --c != 0);
    // RET;
    return de;
}

// StopPichuMobileAnimation
void Function118903(void){
    // LD_A_addr(wc3f0);
    // LD_addr_A(wc319);
    wram->wc319 = wram->wc3f0;
    // LD_C(0x1);
    // FARCALL(aFunction115e18);
    Function115e18(0x1);
    // LD_A(0x8);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x8;
    // CALL(aBattleTowerRoomMenu2);
    BattleTowerRoomMenu2();
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

}

void Function11891c(void){
    // CALL(aFunction118b42);
    Function118b42();
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

}

void BattleTowerRoomMenu_PickLevelMessage(void){
    // LD_A_addr(wcd38);
    // AND_A_A;
    // IF_NZ goto asm_11892d;
    // LD_HL(mText_WhatLevelDoYouWantToChallenge);
    // goto asm_118930;

// asm_11892d:
    // LD_HL(mText_CheckBattleRoomListByMaxLevel);
    const txt_cmd_s* msg = (wram->wcd38 == 0)? Text_WhatLevelDoYouWantToChallenge: Text_CheckBattleRoomListByMaxLevel;

// asm_118930:
    // CALL(aBattleTowerRoomMenu_SetMessage);
    BattleTowerRoomMenu_SetMessage(msg);
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_PlacePickLevelMenu();
}

void BattleTowerRoomMenu_PlacePickLevelMenu(void){
    // LD_A_addr(wc31a);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wc31a)
        return;
    // LD_HL(mMenuHeader_119cf7);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_119cf7);
    // CALL(aMenuBox);
    MenuBox();
    // CALL(aMenuBoxCoord2Tile);
    MenuBoxCoord2Tile();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // hlcoord(16, 8, wAttrmap);
    // LD_A(0x40);
    // OR_A_hl;
    // LD_hl_A;
    *coord(16, 8, wram->wAttrmap) |= 0x40;
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    UpdateSprites();
    // LD_A(0x1);
    // LD_addr_A(wcd4f);
    wram->wcd4f = 0x1;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
    // IF_NZ goto asm_11896b;
    const char** hl;
    uint8_t a;
    if(bit_test(wram->wStatusFlags, STATUSFLAGS_HALL_OF_FAME_F)) {
    // asm_11896b:
        // LD_HL(mStrings_L10ToL100);  // Address to list of strings with the choosable levels
        // LD_A(11);  // 10 levels to choose from, including 'Cancel'-option
        hl = Strings_L10ToL100;
        a = 11;
    }
    else {
        // LD_HL(mStrings_Ll0ToL40);  // Address to list of strings with the choosable levels
        // LD_A(5);  // 4 levels to choose from, including 'Cancel'-option
        // goto asm_118970;
        hl = Strings_Ll0ToL40;
        a = 5;
    }

// asm_118970:
    // LD_addr_A(wcd4a);
    wram->wcd4a = a;
    // LD_A_L;
    // LD_addr_A(wcd4b);
    // LD_A_H;
    // LD_addr_A(wcd4c);
    gMobileStringList = hl;
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_UpdatePickLevelMenu();
}

void BattleTowerRoomMenu_UpdatePickLevelMenu(void){
    // hlcoord(13, 8, wTilemap);
    // LD_DE(mString_119d07);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_119d07), coord(13, 8, wram->wTilemap));
    // hlcoord(13, 10, wTilemap);
    // LD_DE(mString_119d07);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_119d07), coord(13, 10, wram->wTilemap));
    // LD_A_addr(wcd4b);
    // LD_L_A;
    // LD_A_addr(wcd4c);
    // LD_H_A;
    const char** list = gMobileStringList;
    // LD_D(0x0);
    // LD_A_addr(wcd4f);
    // DEC_A;
    // RLCA;
    // RLCA;
    // RLCA;
    // LD_E_A;
    // ADD_HL_DE;
    uint8_t* hl = U82C(list[wram->wcd4f - 1]);
    // LD_A_L;
    // LD_E_A;
    // LD_A_H;
    // LD_D_A;
    uint8_t* de = hl;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_BC(wStringBuffer3);
    uint8_t* bc = wram->wStringBuffer3;

    uint8_t a;
    while(1){
    // asm_1189b5:
        // LD_A_hli;
        a = *(hl++);
        // CP_A(0x50);
        // IF_Z goto asm_1189c4;
        if(a == CHAR_TERM)
            break;
        // CP_A(0x7f);
        // IF_Z goto asm_1189c2;
        if(a == CHAR_SPACE)
            continue;
        // LD_bc_A;
        // INC_BC;
        *(bc++) = a;
        // goto asm_1189b5;
    }

// asm_1189c2:
    // LD_A(0x50);

// asm_1189c4:
    // LD_bc_A;
    *bc = 0x50;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // hlcoord(13, 9, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(13, 9, wram->wTilemap));
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto b_button;
    if(hram.hJoyPressed & B_BUTTON){
    // b_button:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // goto asm_118a3c;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto a_button;
    else if(hram.hJoyPressed & A_BUTTON){
    // a_button:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_A_addr(wcd4f);
        // LD_HL(wcd4a);
        // CP_A_hl;
        // IF_Z goto asm_118a3c;
        if(wram->wcd4f != wram->wcd4a){
            // DEC_A;
            // AND_A(0xfe);
            // SRL_A;
            // LD_addr_A(wcf65);
            wram->wcf65 = ((wram->wcd4f - 1) & 0xfe) >> 1;
            // LDH_A_addr(rSVBK);
            // PUSH_AF;
            // LD_A(0x1);
            // LDH_addr_A(rSVBK);
            // CALL(aCloseWindow);
            CloseWindow();
            // POP_AF;
            // LDH_addr_A(rSVBK);
            // LD_A_addr(wcd38);
            // AND_A_A;
            // IF_NZ goto asm_118a30;
            if(wram->wcd38 == 0){
                // CALL(aBattleTower_LevelCheck);
                // RET_C ;
                // if(BattleTower_LevelCheck())
                //     return;
                // CALL(aBattleTower_UbersCheck);
                // RET_C ;
                // if(BattleTower_UbersCheck())
                //     return;
            }

        // asm_118a30:
            if(gBattleTowerType == BATTLE_TOWER_LOCAL) {
                // LD_A_addr(wcd4f);
                // LD_addr_A(w3_d800);
                wram->w3_d800[0] = wram->wcd4f;
            }
            else {
                BattleTowerRoomMenu_SetMessage(Text_LinkingWithCenter);
            }
            // JP(mBattleTowerRoomMenu_IncrementJumptable);
            return BattleTowerRoomMenu_IncrementJumptable();
        }
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto d_down;
    else if(hram.hJoyPressed & D_DOWN){
    // d_down:
        // LD_HL(wcd4f);
        // DEC_hl;
        // IF_NZ goto asm_1189e5;
        if(--wram->wcd4f == 0){
            // LD_A_addr(wcd4a);
            // LD_hl_A;
            wram->wcd4f = wram->wcd4a;
        }
        // goto asm_1189e5;
        return;
    }
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto d_up;
    else if(hram.hJoyPressed & D_UP){
    // d_up:
        // LD_A_addr(wcd4a);
        // LD_HL(wcd4f);
        // INC_hl;
        // CP_A_hl;
        // IF_NC goto asm_1189e5;
        if(++wram->wcd4f > wram->wcd4a){
            // LD_A(0x1);
            // LD_hl_A;
            wram->wcd4f = 0x1;
        }
        // goto asm_1189e5;
        return;
    }
    else {
    // asm_1189e5:
        // RET;
        return;
    }

// asm_118a3c:
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // CALL(aCloseWindow);
    CloseWindow();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(0x7);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = 0x7;
    // LD_A(0x0);
    // LD_addr_A(wMobileInactivityTimerFrames);
    wram->wMobileInactivityTimerFrames = 0x0;
    // RET;
}

void BattleTowerRoomMenu_Mobile_03(void){ // 4A9A
    // ld a, [$c31a];$c340
    // and a
    // ret nz
    if(wram->wc31a != 0)
        return;

    // ld a, [wcd4f];$cd43
    // ld [$cd61], a ;$cd55
    wram->wcd61[0] = wram->wcd4f;
    // jp BattleTowerRoomMenu_IncrementJumptable
    return BattleTowerRoomMenu_IncrementJumptable();
}

// sort of validation of the battle room number
void BattleTowerRoomMenu_Mobile_15(void){
    // ld a, [wcd89];$cd7d
    // bit 0, a
    // jr nz, jr_046_4aba
    if(bit_test(wram->wcd89, 0)) {
        return SetMobileErrorCode(0xd3);
    }

    // ld hl, wc3ee
    // ld a, [hl+]
    // or [hl]
    uint8_t a = wram->wc3ee | wram->wc3ef;
    // jr z, jr_046_4abf
    if(a == 0) {
    // jr_046_4abf:
        // ld a, $d4
        // jp SetMobileErrorCode;Jump_046_484b
        return SetMobileErrorCode(0xd4);
    }

    // cp $0a
    // jr nc, jr_046_4ac4
    if(a < 0xa) {
    // jr_046_4aba:
        // ld a, $d3
        // jp SetMobileErrorCode;Jump_046_484b
        return SetMobileErrorCode(0xd3);
    }

// jr_046_4ac4:
    // ld a, [wcd38];$cd2c
    // and a
    // jr nz, jr_046_4acf

    // ld hl, Text_EnterWhichBattleRoom;$627b
    // jr jr_046_4ad2

// jr_046_4acf:
    // ld hl, Text_WhichBattleRoom;$6293

// jr_046_4ad2:
    const txt_cmd_s* text = (wram->wcd38 != 0)? Text_WhichBattleRoom: Text_EnterWhichBattleRoom;
    // call BattleTowerRoomMenu_SetMessage;Call_046_6ef1
    BattleTowerRoomMenu_SetMessage(text);
    // call BattleTowerRoomMenu_IncrementJumptable;Call_046_635f
    BattleTowerRoomMenu_IncrementJumptable();
    return BattleTowerRoomMenu_Mobile_16();
}

// initialize the menu for picking the battle room
// similar to the menu for picking the level (BattleTowerRoomMenu_PlacePickLevelMenu)
void BattleTowerRoomMenu_Mobile_16(void){
    // ld a, [$c31a];$c340
    // and a
    // ret nz
    if(wram->wc31a != 0)
        return;

    // ld hl, MenuData_119cff;$6189
	// call LoadMenuHeader;$1d00
    LoadMenuHeader(&MenuData_119cff);
	// call MenuBox;$1c86
    MenuBox();
	// call MenuBoxCoord2Tile;$1cc8
    MenuBoxCoord2Tile(); // Why?
	// call ApplyTilemap;$31e8
    ApplyTilemap();
    // ;hlcoord 17, 8, wAttrmap ; flip the upper arrow tile
	// hlcoord 16, 8, wAttrmap
    // ld a, $40
    // or [hl]
    // ld [hl], a
    *coord(16, 8, wram->wAttrmap) |= 0x40;
    // call WaitBGMap2;$31cc
    WaitBGMap2();
    // ld a, $01
    // ld [wcd4b], a;$cd3f
    wram->wcd4b = 0x1;
    // xor a
    // ld [wcd4c], a;$cd40
    wram->wcd4c = 0x0;
    // ld a, [$c3ee]
    // ldh [hDividend + 0], a;ldh [$b3], a
    // ld a, [$c3ef]
    // ldh [hDividend + 1], a;ldh [$b4], a
    uint16_t num = (wram->wc3ef) | (wram->wc3ee << 8);
    // ld a, $0a
    // ldh [hDivisor], a;ldh [$b7], a
    // ld b, $02
    // call Divide;$30f0
    uint16_t quot = (num / 10) + 1;
    // and a
    // ldh a, [hQuotient + 3];ldh a, [$b6]
    // add $01
    // ld [wcd4d], a;$cd41
    wram->wcd4d = LOW(quot);
    // ldh a, [hQuotient + 2];ldh a, [$b5]
    // adc $00
    // ld [wcd4e], a;$cd42
    wram->wcd4e = HIGH(quot);
    // call BattleTowerRoomMenu_IncrementJumptable;Call_046_635f
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_Mobile_17();
}

// run the menu
void BattleTowerRoomMenu_Mobile_17(void){
    // ld hl, $c54f;$c550
    // ld de, String_119d07 + 2;$6193
    // call PlaceString;$1057
    PlaceStringSimple(U82C(String_119d07_2), coord(15, 8, wram->wTilemap));
    // ld hl, $c577;$c578
    // ld de, String_119d07 + 2;$6193
    // call PlaceString;$1057
    PlaceStringSimple(U82C(String_119d07_2), coord(15, 10, wram->wTilemap));
    // ld a, [wcd4b];$cd3f
    // ld hl, wcd4d;$cd41
    // cp [hl]
    // jr nz, jr_046_4b51

    // ld a, [wcd4c];$cd40
    // inc hl
    // cp [hl]
    // jr nz, jr_046_4b51

    if(wram->wcd4b == wram->wcd4d && wram->wcd4c == wram->wcd4e) {
        // ld hl, $c561;$c564
        // ld de, BattleTowerCancelString ;$6216
        // call PlaceString;$1057
        PlaceStringSimple(U82C(BattleTowerCancelString), coord(13, 9, wram->wTilemap));
        // jr jr_046_4b79
    }
    else {
    // jr_046_4b51:
        //// blank the cancel text might have been displayed before
        // ld hl, $c561
        // ld de, String_blank
        // call PlaceString
        PlaceStringSimple(U82C("      "), coord(13, 9, wram->wTilemap));
        ////

        // ld hl, $c563;$c564
        tile_t* hl = coord(15, 9, wram->wTilemap);
        // push hl
        // ld de, wcd4b;$cd3f
        // ld bc, $8103
        // call PrintNum;$3164
        PrintNum(hl, &wram->wcd4b, PRINTNUM_LEADINGZEROS | 1, 3);
        // pop hl
        // ldh a, [rSVBK]
        // push af
        // ld a, $01
        // ldh [rSVBK], a
        // ld de, wStringBuffer4;$d07c
        uint8_t* de = wram->wStringBuffer4;
        // ld a, $03
        uint8_t a = 0x3;
    // save the current selection to wStringBuffer4 for later display in a textbox
        do {
        // jr_046_4b6b:
            // push af
            // ld a, [hl+]
            // ld [de], a
            // inc de
            *(de++) = *(hl++);
            // pop af
            // dec a
            // jr nz, jr_046_4b6b
        } while(--a != 0);

        // ld a, $50
        // ld [de], a
        *de = 0x50;
        // pop af
        // ldh [rSVBK], a
    }

// jr_046_4b79: ; keys pressed checks
    // ld hl, hJoyPressed;$ffa7
    // ld a, [hl]
    // and $01
    // jp nz, Jump_046_4c02
    if(hram.hJoyPressed & A_BUTTON) {
    // selection made
    // Jump_046_4c02:
        // xor a
        // ld [wcd8a], a;$cd7e
        wram->wcd8a = 0;
        // ld [wcd8b], a;$cd7f
        wram->wcd8b = 0;
        // call PlayClickSFX;$1fcc
        PlayClickSFX();
        // ld a, [wcd4b];$cd3f
        // ld hl, wcd4d;$cd41
        // cp [hl]
        // jr nz, jr_046_4c1c
    
        // inc hl
        // ld a, [wcd4c];$cd40
        // cp [hl]
        // jr z, jr_046_4c30
        if(wram->wcd4b == wram->wcd4d && wram->wcd4c == wram->wcd4e)
            goto jr_046_4c30; // cancel
    
    // jr_046_4c1c:
        // ldh a, [rSVBK]
        // push af
        // ld a, $01
        // ldh [rSVBK], a
        // call CloseWindow;$1be2
        CloseWindow();
        // pop af
        // ldh [rSVBK], a
        // call BattleTowerRoomMenu_IncrementJumptable;Call_046_635f
        BattleTowerRoomMenu_IncrementJumptable();
        // ret
        return;
    }

    // ld a, [hl]
    // and $80
    // jr nz, jr_046_4ba0
    else if(hram.hJoyPressed & D_DOWN) {
    jr_046_4ba0:
        // xor a
        // ld [wcd8a], a;$cd7e
        wram->wcd8a = 0;
        // ld [wcd8b], a;$cd7f
        wram->wcd8b = 0;
        // ld a, [wcd4b];$cd3f
        // ld l, a
        // ld a, [wcd4c];$cd40
        // ld h, a
        uint16_t hl = (wram->wcd4b) | (wram->wcd4c << 8);
        // ld de, $ffff
        hl--;
        // add hl, de
        // ld a, h
        // ld [wcd4c], a;$cd40
        wram->wcd4c = HIGH(hl);
        // ld a, l
        // ld [wcd4b], a;$cd3f
        wram->wcd4b = LOW(hl);
        // or h
        // jr nz, jr_046_4b9f
        if(hl == 0) {
            // ld a, [wcd4d];$cd41
            // ld [wcd4b], a;$cd3f
            wram->wcd4b = wram->wcd4d;
            // ld a, [wcd4e];$cd42
            // ld [wcd4c], a;$cd40
            wram->wcd4c = wram->wcd4e;
        }
        // goto jr_046_4b9f;
    }

    // ld a, [hl]
    // and $40
    // jr nz, jr_046_4bcc
    else if(hram.hJoyPressed & D_UP) {
    jr_046_4bcc:
        // xor a
        // ld [wcd8a], a;$cd7e
        wram->wcd8a = 0;
        // ld [wcd8b], a;$cd7f
        wram->wcd8b = 0;
        // ld a, [wcd4b];$cd3f
        // ld l, a
        // ld a, [wcd4c];$cd40
        // ld h, a
        uint16_t hl = (wram->wcd4b) | (wram->wcd4c << 8);
        // ld de, $0001
        // add hl, de
        hl++;
        // ld a, l
        // ld [wcd4b], a;$cd3f
        wram->wcd4b = LOW(hl);
        // ld a, h
        // ld [wcd4c], a;$cd40
        wram->wcd4c = HIGH(hl);
        // ld a, [wcd4e];$cd42
        // ld hl, wcd4c;$cd40
        // cp [hl]
        // jr nz, jr_046_4b9f
        uint16_t hl2 = (wram->wcd4d) | (wram->wcd4e << 8);
    
        // dec hl
        // ld a, [wcd4d];$cd41
        // cp [hl]
        // jr nc, jr_046_4b9f
        if(hl > hl2) {
            // ld a, $01
            // ld [wcd4b], a;$cd3f
            wram->wcd4b = 0x1;
            // xor a
            // ld [wcd4c], a;$cd40
            wram->wcd4c = 0;
        }
        // jr jr_046_4b9f
    }

    // ld a, [hl]
    // and $20
    // jr nz, jr_046_4ba0
    else if(hram.hJoyPressed & D_LEFT) {
        goto jr_046_4ba0;
    }

    // ld a, [hl]
    // and $10
    // jr nz, jr_046_4bcc
    else if(hram.hJoyPressed & D_RIGHT) {
        goto jr_046_4bcc;
    }

    // ld a, [hl]
    // and $02
    // jp nz, Jump_046_4c2d
    else if(hram.hJoyPressed & B_BUTTON) {
    // Jump_046_4c2d:
        // call PlayClickSFX;$1fcc
        PlayClickSFX();
    
    jr_046_4c30:
        // ldh a, [rSVBK]
        // push af
        // ld a, $01
        // ldh [rSVBK], a
        // call CloseWindow;$1be2
        CloseWindow();
        // pop af
        // ldh [rSVBK], a
        // ld a, $27
        // ld [wcf66], a;$cf5a
        wram->wcf66 = 0x27;
        // ld a, $15
        // ld [wMobileInactivityTimerFrames], a;$cd3a
        wram->wMobileInactivityTimerFrames = 0x15;
        // ld a, $1e
        // ld [wcd47], a;$cd3b
        wram->wcd47 = 0x27;
        // ret
        return;
    }

    // call Function11a9f0;Call_046_6f21

// jr_046_4b9f:
    // ret
    return;
}

void BattleTowerRoomMenu_Mobile_18(void){
    // xor a
    // ld b, a
    // ld c, a
    uint16_t bc = 0;
    // ld a, [wcd4f] // $$cd43
    uint8_t a = wram->wcd4f;
    // cp $0a
    // jr nz, jr_046_4c5a
    if(a == 0xa) {
        // ld c, $01
        bc = 1;
        // xor a
        a = 0;
    }

// jr_046_4c5a:
    // ld [$cd61], a;$cd55
    wram->wcd61[0] = a;
    // ld a, [wcd4b];$cd3f
    // ld l, a
    // ld a, [wcd4c];$cd40
    // ld h, a
    uint16_t hl = wram->wcd4b | (wram->wcd4c << 8);
    // ld de, $ffff
    // add hl, bc
    // add hl, de
    hl = (hl + bc) - 1;
    // ld a, l
    // and $0f
    // ldh [hDividend + 0], a;$b3
    hram.hMultiplicand[0] = hl & 0xf;
    // ld a, l
    // and $f0
    // swap a
    // ldh [hDividend + 1], a;$b4
    hram.hMultiplicand[1] = (hl & 0xf0) >> 4;
    // ld a, h
    // and $0f
    // ldh [hDividend + 2], a;$b5
    hram.hMultiplicand[2] = (hl & 0xf00) >> 8;
    // call Function11a80c;Call_046_6d3d
    Function11a80c();
    // call RemovedFunction12;Call_046_4e2b
    // ret c
    if(RemovedFunction12())
        return;

    // ld a, [wcd38];$cd2c
    // and a
    // jr nz, jr_046_4c92
    if(wram->wcd38 == 0) {
        // ld a, [wcd5b];$cd4f
        // ld l, a
        // ld a, [wcd5c];$cd50
        // ld h, a
        hl = (wram->wcd5b) | (wram->wcd5c << 8);
        // jr jr_046_4cae
    }
    else {
    // jr_046_4c92:
        // ld a, $01
        // ldh [rSVBK], a
        // ld hl, wStringBuffer3;$d071
        // ld de, wcd69;$cd5d
        // ld bc, $0016
        // call CopyBytes;$2ff2
        CopyBytes(wram->wcd69, wram->wStringBuffer3, 0x16);
        // ld a, $03
        // ldh [rSVBK], a
        // ld a, [wcd5f];$cd53
        // ld l, a
        // ld a, [wcd60];$cd54
        // ld h, a
        hl = (wram->wcd5f) | (wram->wcd60 << 8);
    }

// jr_046_4cae:
    // dec hl
    // dec hl
    // dec hl
    // dec hl
    // dec hl
    // dec hl
    // dec hl
    hl -= 7;
    uint8_t* hl2 = wram->wram3 + hl;
    // ld de, $cd61;$cd55
    const uint8_t* de = wram->wcd61;
    // ld a, $04
    a = 0x4;

    do {
    // jr_046_4cba:
        // push af
        // ld a, [de]
        // inc de
        // add $30
        // ld [hl-], a
        *(hl2--) = *(de++) + '0';
        // pop af
        // dec a
        // jr nz, jr_046_4cba
    } while(--a != 0);

    // ld hl, $dffc
    hl2 = wram->w3_dffc;
    // ld de, wcd64;$cd58
    de = wram->wcd64;
    // ld c, $04
    uint8_t c = 0x4;

    do {
    // jr_046_4ccc:
        // ld a, [de]
        // dec de
        // ld [hl+], a
        *(hl2++) = *(de--);
        // dec c
        // jr nz, jr_046_4ccc
    } while(--c != 0);

    // call BattleTowerRoomMenu_IncrementJumptable // Call_046_635f
    BattleTowerRoomMenu_IncrementJumptable();
    return BattleTowerRoomMenu_Mobile_19();
}

void BattleTowerRoomMenu_Mobile_19(void) {
    // ld hl, Text_ThisBattleRoomPleaseWait // $62a3
    // call BattleTowerRoomMenu_SetMessage // Call_046_6ef1
    BattleTowerRoomMenu_SetMessage(Text_ThisBattleRoomPleaseWait);
    // call BattleTowerRoomMenu_IncrementJumptable // Call_046_635f
    BattleTowerRoomMenu_IncrementJumptable();
    return BattleTowerRoomMenu_Mobile_1a();
}

void BattleTowerRoomMenu_Mobile_1a(void){
    // ld a, [$c31a];$c340
    // and a
    // ret nz
    if(wram->wc31a != 0)
        return;

    // ld a, [wcd38];$cd2c
    // and a
    // jr nz, jr_046_4cf3
    uint8_t* hl = wram->wram3;
    if(wram->wcd38 == 0) {
        // ld a, [wcd53] // $cd47
        // ld l, a
        // ld a, [wcd54] // $cd48
        // ld h, a
        hl += (wram->wcd53) | (wram->wcd54 << 8);
        // jr jr_046_4cfb
    }
    else {
    // jr_046_4cf3:
        // ld a, [wcd57];$cd4b
        // ld l, a
        // ld a, [wcd58];$cd4c
        // ld h, a
        hl += (wram->wcd57) | (wram->wcd58 << 8);
    }

// jr_046_4cfb:
    // call Function118e39;Call_046_515f
    Function118e39((const char*)hl);
    // ld a, $09
    // ld [wBattleTowerRoomMenu2JumptableIndex], a;$cd30
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x9;
    // ld a, $27
    // ld [wMobileInactivityTimerSeconds], a;$cd39
    wram->wMobileInactivityTimerSeconds = 0x27;
    // ld a, $15
    // ld [wMobileInactivityTimerFrames], a;$cd3a
    wram->wMobileInactivityTimerFrames = 0x15;
    // ld a, $1e
    // ld [wcd47], a;$cd3b
    wram->wcd47 = 0x1e;
    // call BattleTowerRoomMenu_IncrementJumptable;Call_046_635f
    BattleTowerRoomMenu_IncrementJumptable();
    return BattleTowerRoomMenu_Mobile_1b();
}

// RemovedFunction7
void BattleTowerRoomMenu_Mobile_1b(void){
    // call BattleTowerRoomMenu2 //Call_046_6409
    // ret c
    if(BattleTowerRoomMenu2())
        return;

    // call DelayFrame //$045a
    DelayFrame();
    // ld a, [wcd38]   //$cd2c
    // and a
    // jr nz, jr_046_4d2c
    uint8_t* hl = wram->wram3;
    if(wram->wcd38 == 0) {
        // ld a, [wcd53];$cd47
        // ld l, a
        // ld a, [wcd54];$cd48
        // ld h, a
        hl += (wram->wcd53) | (wram->wcd54 << 8);
        // jr jr_046_4d34
    }
    else {
    // jr_046_4d2c:
        // ld a, [wcd57];$cd4b
        // ld l, a
        // ld a, [wcd58];$cd4c
        // ld h, a
        hl += (wram->wcd57) | (wram->wcd58 << 8);
    }

// jr_046_4d34:
    // ld de, wBT_DownloadBuffer
    // ld bc, $0e00
    mobile_api_data_s data = {.hl = hl, .de = &wram->wBT_TrainerTextIndex, .bc = 0xe00};
    // jp HttpGet // Jump_046_4dcd
    return Function118ae4(&data);
}

void Function118a54(void){
//  //  unreferenced
    mobile_api_data_s data = {};
    // LD_A_addr(wcd55);
    // LD_L_A;
    // LD_A_addr(wcd56);
    // LD_H_A;
    data.hl = wram->wram3 + ((wram->wcd55) | (wram->wcd56 << 8));
    // LD_DE(wc3ec);
    data.de = &wram->wc3ec;
    // LD_BC(0x0004);
    data.bc = 0x0004;
    // JP(mFunction118ae4);
    return Function118ae4(&data);
}

void Function118a65(void){
//  //  unreferenced
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer) - 1, "http://%s%s",
        Mobile_GetServerHostname(),
        BattleDownloadURL);
    // LD_HL(mBattleDownloadURL);
    // LD_DE(wcc60);
    // LD_BC(0x80);
    // CALL(aCopyBytes);
    CopyBytes(wram->wcc60_str, buffer, 0x80);
    // LD_DE(w3_d000);
    // LD_BC(0x1000);
    // JP(mFunction118b10);
    Function118b10(wram->w3_d000, 0x1000);
}

void Function118a7a(void){
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer) - 1, "http://%s%s",
        Mobile_GetServerHostname(),
        BattleDownloadURL);
    // LD_HL(mBattleDownloadURL);
    // LD_DE(wcc60);
    // LD_BC(0x80);
    // CALL(aCopyBytes);
    CopyBytes(wram->wcc60_str, buffer, 0x80);
    // LD_DE(w3_d000);
    // LD_BC(0x1000);
    // JP(mFunction118b10);
    Function118b10(wram->w3_d000, 0x1000);
}

void Function118a8f(void){
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer) - 1, "http://%s%s",
        Mobile_GetServerHostname(),
        ExchangeDownloadURL);
    // LD_HL(mExchangeDownloadURL);
    // LD_DE(wcc60);
    // LD_BC(0x80);
    // CALL(aCopyBytes);
    CopyBytes(wram->wcc60_str, buffer, 0x80);
    // LD_DE(w3_d000);
    // LD_BC(0x1000);
    // JP(mFunction118b10);
    Function118b10(wram->w3_d000, 0x1000);
}

void Function118aa4(void){
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer) - 1, "http://%s%s",
        Mobile_GetServerHostname(),
        NewsDownloadURL);
    // LD_HL(mNewsDownloadURL);
    // LD_DE(wcc60);
    // LD_BC(0x80);
    // CALL(aCopyBytes);
    CopyBytes(wram->wcc60_str, buffer, 0x80);
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_DE(w3_d100);
    // LD_BC(0xe00);
    // JR(mFunction118b10);
    Function118b10(wram->w3_d100, 0xe00);
}

void Function118abc(void){
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer) - 1, "http://%s%s",
        Mobile_GetServerHostname(),
        MenuDownloadURL);
    // LD_HL(mMenuDownloadURL);
    // LD_DE(wcc60);
    // LD_BC(0x80);
    CopyBytes(wram->wcc60_str, buffer, 0x80);
    // CALL(aCopyBytes);
    // LD_DE(w3_d000);
    // LD_BC(0x1000);
    // JR(mFunction118b10);
    Function118b10(wram->w3_d000, 0x1000);
}

void Function118ad0(void){
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer) - 1, "http://%s%s",
        Mobile_GetServerHostname(),
        IndexDownloadURL);
    // LD_HL(mIndexDownloadURL);
    // LD_DE(wcc60);
    // LD_BC(0x80);
    // CALL(aCopyBytes);
    CopyBytes(wram->wcc60_str, buffer, 0x80);
    // LD_DE(w3_d000);
    // LD_BC(0x1000);
    // JR(mFunction118b10);
    Function118b10(wram->w3_d000, 0x1000);
}

void Function118ae4(mobile_api_data_s* data){
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // LD_A(0x8);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x8;
    // CALL(aBattleTowerRoomMenu2);
    BattleTowerRoomMenu2();
    // POP_HL;
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_DE(wcc60);
    uint8_t* de = (uint8_t*)wram->wcc60_str;
    uint8_t* hl = data->hl;
    uint8_t a;

    do {
    // asm_118af5:
        // LD_A_hli;
        a = *(hl++);
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        // AND_A_A;
        // IF_Z goto asm_118b06;
        if(a == 0) {
        // asm_118b06:
            // CALL(aFunction118b24);
            data->hl = Function118b24();
            // POP_DE;
            // POP_BC;
            // LD_A(MOBILEAPI_15);
            // JP(mFunction119e2b);
            return Function119e2b(MOBILEAPI_15, data);
        }
        // INC_C;
        // LD_A_C;
        // CP_A(0xa6);
        // IF_C goto asm_118af5;
    } while(++c < 0xa6);
    // LD_A(0xda);
    // JP(mSetMobileErrorCode);
    return SetMobileErrorCode(0xda);
}

void Function118b10(void* de, uint16_t bc){
    // PUSH_DE;
    // PUSH_BC;
    // LD_A(0x8);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x8;
    // CALL(aBattleTowerRoomMenu2);
    BattleTowerRoomMenu2();
    // CALL(aFunction118b24);
    uint8_t* hl = Function118b24();
    // POP_BC;
    // POP_DE;
    // LD_A(MOBILEAPI_15);
    // JP(mFunction119e2b);
    Function119e2b(MOBILEAPI_15, &(mobile_api_data_s){.bc = bc, .de = de, .hl = hl});
}

uint8_t* Function118b24(void){
    // LD_HL(wc346);
    // LD_A(0x8);
    // LD_hli_A;
    wram->wc346[0] = LOW(0xc708);
    // LD_A(0xc7);
    // LD_hli_A;
    wram->wc346[1] = HIGH(0xc708);
    // LD_A(0x60);
    // LD_hli_A;
    wram->wc346[2] = LOW(0xcc60);
    // LD_A(0xcc);
    // LD_hli_A;
    wram->wc346[3] = HIGH(0xcc60);
    // CALL(aFunction119eb4);
    // CALL(aFunction119ec2);
    Function119ec2(Function119eb4(wram->wc346 + 4));
    // LD_A(0x80);
    // LD_addr_A(wcd89);
    wram->wcd89 = 0x80;
    // LD_HL(wc346);
    // RET;
    return wram->wc346;
}

bool RemovedFunction12(void){
    // ld a, [wcd38] // $cd2c
    // and a
    // ret nz
    if(wram->wcd38 != 0)
        return false;

    // ld a, BANK(s5_aa5d)
    // call OpenSRAM;$2f9d
    OpenSRAM(MBANK(as5_aa5d));
    // ld a, [s5_aa5d]
    uint8_t c = gb_read(s5_aa5d);
    // and a
    // jr z, jr_046_4e63
    if(c != 0) {
        // ld c, a
        // ld hl, s5_aa5d + 1
        uint8_t* hl = GBToRAMAddr(s5_aa5d + 1);

        do {
        // jr_046_4e3f:
            // push hl
            uint8_t* hl2 = hl;
            // ld de, wcd64 // $cd58
            const uint8_t* de = wram->wcd64;
            // ld b, $04
            uint8_t b = 0x04;

            do {
            // jr_046_4e45:
                // ld a, [de]
                // dec de
                uint8_t a = *(de--);
                // cp [hl]
                // jr nz, jr_046_4e59
                if(a != *hl2)
                    goto jr_046_4e59;

                // inc hl
                hl2++;
                // dec b
                // jr nz, jr_046_4e45
            } while(--b != 0);

            // pop hl
            // call CloseSRAM;$2fad
            CloseSRAM();
            // ld a, $2f
            // ld [wcf66], a;$cf5a
            wram->wcf66 = 0x2f;
            // scf
            // ret
            return true;

        jr_046_4e59:
            // pop hl
            // push bc
            // ld bc, $0004
            // add hl, bc
            hl += 0x4;
            // pop bc
            // dec c
            // jr nz, jr_046_4e3f
        } while(--c != 0);
    }

// jr_046_4e63:
    // call CloseSRAM // $2fad
    CloseSRAM();
    // and a
    // ret
    return false;
}

void Function118b42(void){
    // LD_HL(wd002);
    uint16_t hl = 0x0002;
    // LD_A_L;
    // LD_addr_A(wcd51);
    wram->wcd51 = LOW(hl);
    // LD_A_H;
    // LD_addr_A(wcd52);
    wram->wcd52 = HIGH(hl);
    // CALL(aFunction118b8c);
    hl = Function118b8c(hl);
    // LD_A_L;
    // LD_addr_A(wcd55);
    wram->wcd55 = LOW(hl);
    // LD_addr_A(wcd59);
    wram->wcd59 = LOW(hl);
    // LD_A_H;
    // LD_addr_A(wcd56);
    wram->wcd56 = HIGH(hl);
    // LD_addr_A(wcd5a);
    wram->wcd5a = HIGH(hl);
    // CALL(aFunction118b8c);
    hl = Function118b8c(hl);
    // LD_A_L;
    // LD_addr_A(wcd53);
    wram->wcd53 = LOW(hl);
    // LD_addr_A(wcd5d);
    wram->wcd5d = LOW(hl);
    // LD_A_H;
    // LD_addr_A(wcd54);
    wram->wcd54 = HIGH(hl);
    // LD_addr_A(wcd5e);
    wram->wcd5e = HIGH(hl);
    // CALL(aFunction118b8c);
    hl = Function118b8c(hl);
    // LD_A_L;
    // LD_addr_A(wcd57);
    wram->wcd57 = LOW(hl);
    // LD_addr_A(wcd5b);
    wram->wcd5b = LOW(hl);
    // LD_A_H;
    // LD_addr_A(wcd58);
    wram->wcd58 = HIGH(hl);
    // LD_addr_A(wcd5c);
    wram->wcd5c = HIGH(hl);
    // CALL(aFunction118b8c);
    hl = Function118b8c(hl);
    // LD_A_L;
    // LD_addr_A(wcd5f);
    wram->wcd5f = LOW(hl);
    // LD_A_H;
    // LD_addr_A(wcd60);
    wram->wcd60 = HIGH(hl);
    // RET;
}

uint16_t Function118b8c(uint16_t hl){
    uint8_t a;
    do {
    // asm_118b8c:
        // CALL(aFunction118b9a);
        // RET_NC ;
        if(!Function118b9a(hl))
            return hl;
        // LD_A_hli;
        a = wram->wram3[hl++];
        // CP_A(0xd);
        // IF_NZ goto asm_118b8c;
    } while(a != '\r');
    // DEC_HL;
    --hl;
    // XOR_A_A;
    // LD_hli_A;
    wram->wram3[hl++] = 0x0;
    // LD_hli_A;
    wram->wram3[hl++] = 0x0;
    // RET;
    return hl;
}

bool Function118b9a(uint16_t hl){
    // LD_A_H;
    // CP_A(0xe0);
    // RET_C ;
    if(hl < 0x1000)
        return true;
    // LD_A(0xd3);
    // CALL(aSetMobileErrorCode);
    SetMobileErrorCode(0xd3);
    // AND_A_A;
    // RET;
    return false;
//pushc
//setcharmap ascii
}

#if defined(_CRYSTAL_JP)
#define REGION_CODE_STR "BXTJ"
#else
#define REGION_CODE_STR "BXTE"
#endif
const char ExchangeDownloadURL[] = "/cgb/download?name=/01/CGB-"REGION_CODE_STR"/exchange/index.txt";
const char BattleDownloadURL[] = "/cgb/download?name=/01/CGB-"REGION_CODE_STR"/battle/index.txt";
const char NewsDownloadURL[] = "/cgb/download?name=/01/CGB-"REGION_CODE_STR"/news/index.txt";
const char MenuDownloadURL[] = "/cgb/download?name=/01/CGB-"REGION_CODE_STR"/POKESTA/menu.cgb";
const char IndexDownloadURL[] = "/cgb/download?name=/01/CGB-"REGION_CODE_STR"/tamago/index.txt";

// popc

// ValidateBattleDownload
// validates the length of the received battle room (1428 bytes) or honor roll data (150 bytes)
void Function118d35(void){
//  //  unreferenced
    // LD_HL(0xd200);
    uint8_t* hl = &wram->wBT_TrainerTextIndex;
    uint16_t size = hl[0] | (hl[1] << 8);
    // LD_A_addr(wcd38);
    // AND_A_A;
    // IF_NZ goto asm_118d6e;
    if(wram->wcd38 == 0) {
        // LD_A_hli;
        // CP_A(0x94);
        // IF_NZ goto asm_118d7b;
        // LD_A_hl;
        // CP_A(0x5);
        // IF_NZ goto asm_118d7b;
        if(size != BATTLE_TOWER_STRUCT_LENGTH * BATTLETOWER_STREAK_LENGTH) {
        // asm_118d7b:
            printf("Battle Download Error: Expected size %d, got %d.\n", BATTLE_TOWER_STRUCT_LENGTH * BATTLETOWER_STREAK_LENGTH, size);
            // LD_A(0xd3);
            // JP(mSetMobileErrorCode);
            return SetMobileErrorCode(0xd3);
        }
        // LD_A_addr(wcd4f);
        // SLA_A;
        // LD_B_A;
        // SLA_A;
        // SLA_A;
        // ADD_A_B;
        // LD_B_A;
        uint8_t b = (wram->wcd4f << 1) + (wram->wcd4f << 3);
        // LD_A(BANK(s5_b2fb));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(as5_b2fb));
        // LD_A_B;
        // LD_addr_A(s5_b2fb);
        gb_write(s5_b2fb, b);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // FARCALL(aFunction170be4);
        Function170be4();
        // FARCALL(aFunction1700c4);
        Function1700c4();
        // goto asm_118d78;
    }
    else {
    // asm_118d6e:
        // LD_A_hli;
        // CP_A(0x96);
        // IF_NZ goto asm_118d7b;
        // LD_A_hl;
        // CP_A(0x0);
        // IF_NZ goto asm_118d7b;
        if(size != HONOR_ROLL_DATA_LENGTH) {
        // asm_118d7b:
            // LD_A(0xd3);
            // JP(mSetMobileErrorCode);
            return SetMobileErrorCode(0xd3);
        }
    }

// asm_118d78:
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    return BattleTowerRoomMenu_IncrementJumptable();

// asm_118d7b:
    // LD_A(0xd3);
    // JP(mSetMobileErrorCode);
}

void Function118d80(void){
    // CALL(aFunction118e06);
    Function118e06();
    // LD_A_addr(wcd38);
    // AND_A_A;
    // IF_Z goto asm_118d8e;
    if(wram->wcd38 != 0) {
        // CALL(aBattleTowerRoomMenu_IncrementJumptable);
        BattleTowerRoomMenu_IncrementJumptable();
        // JR(masm_118d9f);
        return asm_118d9f();
    }

// asm_118d8e:
    // LD_A(0x9);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x9;
    // LD_A(0x12);
    // LD_addr_A(wMobileInactivityTimerSeconds);
    wram->wMobileInactivityTimerSeconds = 0x12;
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

    return Function118d9b();
}

void Function118d9b(void){
    // CALL(aBattleTowerRoomMenu2);
    // RET_C ;
    if(BattleTowerRoomMenu2())
        return;

    return asm_118d9f();
}

void asm_118d9f(void){
    // LD_HL(wc608);
    // CALL(aFunction119940);
    Function119940(wram->wc608);
    // LD_A_addr(wcd38);
    // AND_A_A;
    // IF_NZ goto asm_118db2;
    if(wram->wcd38 == 0) {
        // LD_A(0x8f);
        // LD_addr_A(wcd3b);
        wram->wcd3b[0] = 0x8f;
        // goto asm_118db7;
    }
    else {
    // asm_118db2:
        // LD_A(0x26);
        // LD_addr_A(wcd3b);
        wram->wcd3b[0] = 0x26;
    }

// asm_118db7:
    // LD_HL(w3_d800);
    // LD_A(0x8);
    // LD_hli_A;
    wram->w3_d800[0] = LOW(0xc608);
    // LD_A(0xc6);
    // LD_hli_A;
    wram->w3_d800[1] = HIGH(0xc608);
    // LD_A_addr(wcd3b);
    // LD_hli_A;
    wram->w3_d800[2] = wram->wcd3b[0];
    // XOR_A_A;
    // LD_hli_A;
    wram->w3_d800[3] = 0;
    // LD_A(0x8);
    // LD_hli_A;
    wram->w3_d800[4] = LOW(0xc708);
    // LD_A(0xc7);
    // LD_hli_A;
    wram->w3_d800[5] = HIGH(0xc708);
    // LD_A_addr(wcd39);
    // LD_hli_A;
    wram->w3_d800[6] = wram->wcd39;
    // LD_A_addr(wcd3a);
    // LD_hli_A;
    wram->w3_d800[7] = wram->wcd3a;
    // CALL(aFunction119eb4);
    // CALL(aFunction119ec2);
    Function119ec2(Function119eb4(wram->w3_d800 + 8));
    // LD_A(0x40);
    // LD_addr_A(wcd89);
    wram->wcd89 = 0x40;
    // LD_HL(w3_d800);
    // LD_DE(w3_de00);
    // LD_BC(0x200);
    // LD_A(MOBILEAPI_16);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_16, &(mobile_api_data_s){.hl = wram->w3_d800, .de = wram->w3_de00, .bc = 0x200});
}

void Function118ded(void){
    // LD_A_addr(wcd38);
    // AND_A_A;
    // IF_Z goto asm_118e03;
    if(wram->wcd38 != 0) {
        // LDH_A_addr(rSVBK);
        // PUSH_AF;
        // LD_A(0x1);
        // LDH_addr_A(rSVBK);
        // FARCALL(aFunction11b93b);
        Function11b93b();
        // POP_AF;
        // LDH_addr_A(rSVBK);
    }

// asm_118e03:
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    return BattleTowerRoomMenu_IncrementJumptable();
}

void Function118e06(void){
    // LD_HL(wd002);
    uint16_t hl = 0x2;
    // LD_A_addr(wcd38);
    // AND_A_A;
    // IF_Z goto asm_118e1d;
    if(wram->wcd38 != 0) {
        do {
        // asm_118e0f:
            // CALL(aFunction118b9a);
            // RET_NC ;
            if(!Function118b9a(hl))
                return;
            // LD_A_hli;
            // CP_A(0xd);
            // IF_NZ goto asm_118e0f;
            if(wram->wram3[hl++] != '\r')
                continue;
            // LD_A_hli;
            // CP_A(0xa);
            // IF_NZ goto asm_118e0f;
        } while(wram->wram3[hl++] != '\n');
    }

// asm_118e1d:
    // LD_A_L;
    // LD_addr_A(wcd39);
    wram->wcd39 = LOW(w3_d000 + hl);
    // LD_A_H;
    // LD_addr_A(wcd3a);
    wram->wcd3a = HIGH(w3_d000 + hl);

    do {
    // asm_118e25:
        // CALL(aFunction118b9a);
        // RET_NC ;
        if(!Function118b9a(hl))
            return;
        // LD_A_hli;
        // CP_A(0xd);
        // IF_NZ goto asm_118e25;
        if(wram->wram3[hl++] != '\r')
            continue;
        // LD_A_hli;
        // CP_A(0xa);
        // IF_NZ goto asm_118e25;
    } while(wram->wram3[hl++] != '\n');
    // DEC_HL;
    hl -= 2;
    // XOR_A_A;
    // LD_hld_A;
    wram->wram3[hl + 1] = 0;
    // LD_hl_A;
    wram->wram3[hl + 0] = 0;
    // JR(masm_118e3e);
    return asm_118e3e((const char*)wram->wram3 + hl);
}

void Function118e39(const char* hl){
    char a;
    do {
        // LD_A_hli;
        a = *(hl++);
        // AND_A_A;
        // JR_NZ (mFunction118e39);
    } while(a != 0);
    // DEC_HL;
    --hl;

    return asm_118e3e(hl);
}

void asm_118e3e(const char* hl){
    char a;
    do {
        // LD_A_hld;
        a = *(hl--);
        // CP_A(0x2f);
        // JR_NZ (masm_118e3e);
    } while(a != '/');
    // INC_HL;
    // INC_HL;
    hl += 2;
    // LD_DE(wcd85);
    uint8_t* de = wram->wcd85;
    // LD_C(0x4);
    uint8_t c = 0x4;

    do {
    // asm_118e4a:
        // LD_A_hli;
        char ch = *(hl++);
        // CP_A(0x2e);
        // IF_Z goto asm_118e63;
        if(ch == '.')
            goto asm_118e63;
        // CP_A(0x30);
        // IF_C goto asm_118e67;
        // CP_A(0x3a);
        // IF_NC goto asm_118e67;
        if(ch < '0' || ch > '9') {
        // asm_118e67:
            // LD_A(0xf3);
            // LD_de_A;
            // INC_DE;
            *(de++) = 0xf3;
            goto asm_118e63;
        }
        // SUB_A(0x30);
        // ADD_A(0xf6);
        // LD_de_A;
        // INC_DE;
        *(de++) = (ch - '0') + 0xf6;
        // DEC_C;
        // IF_NZ goto asm_118e4a;
    } while(--c != 0);
    // LD_DE(wcd85);
    de = wram->wcd85;

asm_118e63:
    // LD_A(0x50);
    // LD_de_A;
    *de = 0x50;
    // RET;
}

// Mobile_EndCommunication
void Function118e6d(void){
    // XOR_A_A;
    // LD_addr_A(wcd65);
    wram->wcd65 = 0;
    // LD_A(MOBILEAPI_05);
    // JP(mFunction119e2b);
    Function119e2b(MOBILEAPI_05, &(mobile_api_data_s){});
}

void Function118e76(void){
// Call $c in BattleTowerRoomMenu2
    // LD_A(0xc);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0xc;
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    return BattleTowerRoomMenu_IncrementJumptable();
}

void Function118e7e(void){
    // CALL(aBattleTowerRoomMenu2);
    // RET_C ;
    if(BattleTowerRoomMenu2())
        return;
    // LD_A(MOBILEAPI_1B);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_1B, &(mobile_api_data_s){});
}

void BattleTowerRoomMenu_CallRoomMenu2(void){
    // CALL(aBattleTowerRoomMenu2);
    // RET_C ;
    if(BattleTowerRoomMenu2())
        return;
    // LD_A_addr(wcd33);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd33;
    // RET;
}

void Function118e92(void){
    // CALL(aFunction118440);
    Function118440();
    // CALL(aFunction1191d3);
    Function1191d3();
    // LD_A_addr(wcd53);
    // LD_L_A;
    // LD_A_addr(wcd54);
    // LD_H_A;
    uint16_t hl = (wram->wcd53) | (wram->wcd54 << 8);
    // LD_DE(wcc60);
    // CALL(aFunction1191ad);
    // RET_C ;
    if(Function1191ad(wram->wcc60_str, (char*)wram->wram3 + hl))
        return;
    // LD_DE(w3_d800);
    // LD_BC(0x0800);
    // JP(mFunction118b10);
    Function118b10(wram->w3_d800, 0x0800);
}

void Function118eb0(void){
    // CALL(aFunction118440);
    Function118440();
    // LD_HL(w3_d802);
    // LD_DE(wBGMapBuffer);
    // LD_BC(0x000c);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wcd20, wram->w3_d802, sizeof(wram->w3_d802));
    // CALL(aFunction1192cc);
    // RET_C ;
    if(Function1192cc())
        return;
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    return BattleTowerRoomMenu_IncrementJumptable();
}

void Function118ec6(void){
    // CALL(aFunction118440);
    Function118440();
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // LD_HL(w3_d80e);
    // LD_DE(wc320);
    // LD_BC(0x0026);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc320, &wram->w3_d80e, 0x0026);
    // XOR_A_A;
    // LD_addr_A(wc31f);
    wram->wc31f = 0;
    // LD_A(0x20);
    // LD_addr_A(wc31b);
    // LD_A(0xc3);
    // LD_addr_A(wc31c);
    gMobileMessagePtr = wram->wc320;
    // hlcoord(1, 14, wTilemap);
    // LD_A_L;
    // LD_addr_A(wc31d);
    // LD_A_H;
    // LD_addr_A(wc31e);
    gMobileMessageDestPtr = coord(1, 14, wram->wTilemap);
    // LD_A(0x2);
    // LD_addr_A(wc31a);
    wram->wc31a = 0x2;
    // LD_A(0x1d);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x1d;
    // LD_A(0x24);
    // LD_addr_A(wMobileInactivityTimerSeconds);
    wram->wMobileInactivityTimerSeconds = 0x24;
    // LD_A(0x11);
    // LD_addr_A(wMobileInactivityTimerFrames);
    wram->wMobileInactivityTimerFrames = 0x11;
    // LD_A(0x1c);
    // LD_addr_A(wcd47);
    wram->wcd47 = 0x1c;
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
}

void Function118f0d(void){
    // CALL(aBattleTowerRoomMenu2);
    // RET_C ;
    if(BattleTowerRoomMenu2())
        return;
    // CALL(aFunction118440);
    Function118440();

    return Function118f14();
}

// MobileNewsJumptable_SendSaveFile
void Function118f14(void){
    // CALL(aFunction118440);
    Function118440();
    // LD_A_addr(wcd51);
    // LD_L_A;
    // LD_A_addr(wcd52);
    // LD_H_A;
    const char* hl = (const char*)wram->wram3 + (wram->wcd51 | (wram->wcd52 << 8));
    // LD_DE(wcc60);
    // CALL(aFunction1191ad);
    // RET_C ;
    if(Function1191ad(wram->wcc60_str, hl))
        return;
    // LD_A_addr(wcc60);
    // AND_A_A;
    // IF_Z goto DontSendSaveFile;
    if(wram->wcc60 != 0) {
        // LD_HL(mText_SaveFileWillBeSent);
        // CALL(aBattleTowerRoomMenu_SetMessage);
        BattleTowerRoomMenu_SetMessage(Text_SaveFileWillBeSent);
    }

// DontSendSaveFile:
    // LD_A_addr(wcd57);
    // LD_L_A;
    // LD_A_addr(wcd58);
    // LD_H_A;
    hl = (const char*)wram->wram3 + (wram->wcd57 | (wram->wcd58 << 8));
    // LD_DE(wcc60);
    // CALL(aFunction1191ad);
    // RET_C ;
    if(Function1191ad(wram->wcc60_str, hl))
        return;
    // LD_HL(wcc60);
    // CALL(aFunction118e39);
    Function118e39(wram->wcc60_str);
    // LD_A(0x9);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x9;
    // LD_A(0x24);
    // LD_addr_A(wMobileInactivityTimerSeconds);
    wram->wMobileInactivityTimerSeconds = 0x24;
    // LD_A(0x13);
    // LD_addr_A(wMobileInactivityTimerFrames);
    wram->wMobileInactivityTimerFrames = 0x13;
    // LD_A(0x1c);
    // LD_addr_A(wcd47);
    wram->wcd47 = 0x1c;
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    return BattleTowerRoomMenu_IncrementJumptable();
}

void Function118f5e(void){
    // CALL(aBattleTowerRoomMenu2);
    // RET_C ;
    if(BattleTowerRoomMenu2())
        return;
    // CALL(aFunction118440);
    Function118440();
    // CALL(aDelayFrame);
    DelayFrame();

    return Function118f68();
}

void Function118f68(void){
    // CALL(aFunction119223);
    // RET_C ;
    if(Function119223())
        return;
    // CALL(aFunction118440);
    Function118440();
    // LD_A_addr(wcd51);
    // LD_L_A;
    // LD_A_addr(wcd52);
    // LD_H_A;
    const char* hl = (const char*)wram->wram3 + (wram->wcd51 | (wram->wcd52 << 8));
    // LD_DE(wcc60);
    // CALL(aFunction1191ad);
    // RET_C ;
    if(Function1191ad(wram->wcc60_str, hl))
        return;
    // LD_A_addr(wcc60);
    // AND_A_A;
    // IF_Z goto asm_118fba;
    if(wram->wcc60 != 0) {
        // LD_HL(wc346);
        // LD_A(LOW(0xc608));
        // LD_hli_A;
        wram->wc346[0] = LOW(0xc608);
        // LD_A(HIGH(0xc608));
        // LD_hli_A;
        wram->wc346[1] = HIGH(0xc608);
        // LD_A_addr(wcd4b);
        // LD_hli_A;
        wram->wc346[2] = wram->wcd4b;
        // LD_A_addr(wcd4c);
        // LD_hli_A;
        wram->wc346[3] = wram->wcd4c;
        // LD_A(LOW(0xc708));
        // LD_hli_A;
        wram->wc346[4] = LOW(0xc708);
        // LD_A(HIGH(0xc708));
        // LD_hli_A;
        wram->wc346[5] = HIGH(0xc708);
        // LD_A(0x60);
        // LD_hli_A;
        wram->wc346[6] = LOW(0xcc60);
        // LD_A(0xcc);
        // LD_hli_A;
        wram->wc346[7] = HIGH(0xcc60);
        // CALL(aFunction119eb4);
        // CALL(aFunction119ec2);
        Function119ec2(Function119eb4(wram->wc346 + 8));
        // LD_A(0x40);
        // LD_addr_A(wcd89);
        wram->wcd89 = 0x40;
        // LD_HL(wc346);
        // LD_DE(w3_de00);
        // LD_BC(0x200);
        // LD_A(MOBILEAPI_16);
        // JP(mFunction119e2b);
        return Function119e2b(MOBILEAPI_16, &(mobile_api_data_s){.de = wram->w3_de00, .hl = wram->wc346, .bc = 0x200});
    }

// asm_118fba:
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
}

void Function118fc0(void){
    // CALL(aFunction118440);
    Function118440();
    // LD_A_addr(wcd55);
    // LD_L_A;
    // LD_A_addr(wcd56);
    // LD_H_A;
    const char* hl = (const char*)wram->wram3 + (wram->wcd55 | (wram->wcd56 << 8));
    // LD_DE(wcc60);
    // CALL(aFunction1191ad);
    // RET_C ;
    if(Function1191ad(wram->wcc60_str, hl))
        return;
    // LD_A_addr(wcc60);
    // AND_A_A;
    // IF_Z goto asm_118ffa;
    if(wram->wcc60 == 0) {
    // asm_118ffa:
        // LD_HL(mText_ReadingNews);
        // CALL(aBattleTowerRoomMenu_SetMessage);
        BattleTowerRoomMenu_SetMessage(Text_ReadingNews);
        // CALL(aBattleTowerRoomMenu_IncrementJumptable);
        BattleTowerRoomMenu_IncrementJumptable();
        // CALL(aBattleTowerRoomMenu_IncrementJumptable);
        BattleTowerRoomMenu_IncrementJumptable();
        // JP(mBattleTowerRoomMenu_IncrementJumptable);
        BattleTowerRoomMenu_IncrementJumptable();
        return;
    }
    // LD_A_addr(wcd51);
    // LD_L_A;
    // LD_A_addr(wcd52);
    // LD_H_A;
    hl = (const char*)wram->wram3 + (wram->wcd51 | (wram->wcd52 << 8));
    // LD_DE(wcc60);
    // CALL(aFunction1191ad);
    // RET_C ;
    if(Function1191ad(wram->wcc60_str, hl))
        return;
    // LD_A_addr(wcc60);
    // AND_A_A;
    // IF_Z goto asm_118ff2;
    // LD_HL(mText_SentSaveFileReadingNews);
    // goto asm_118ff5;

// asm_118ff2:
    // LD_HL(mText_ReadingNews);

// asm_118ff5:
    // CALL(aBattleTowerRoomMenu_SetMessage);
    BattleTowerRoomMenu_SetMessage((wram->wcc60 == 0)? Text_ReadingNews: Text_SentSaveFileReadingNews);
    // JR(mFunction119009);
    return Function119009();
}

void Function119009(void){
    // CALL(aFunction118440);
    Function118440();
    // CALL(aFunction119300);
    Function119300();
    // LD_A_addr(wcd55);
    // LD_L_A;
    // LD_A_addr(wcd56);
    // LD_H_A;
    const char* hl = (const char*)wram->wram3 + (wram->wcd55 | (wram->wcd56 << 8));
    // LD_DE(wcc60);
    // CALL(aFunction1191ad);
    // RET_C ;
    if(Function1191ad(wram->wcc60_str, hl))
        return;
    // LD_HL(wc346);
    // LD_A(0x8);
    // LD_hli_A;
    wram->wc346[0] = LOW(0xc608);
    // LD_A(0xc6);
    // LD_hli_A;
    wram->wc346[1] = HIGH(0xc608);
    // LD_A_addr(wcd4b);
    // LD_hli_A;
    wram->wc346[2] = wram->wcd4b;
    // LD_A_addr(wcd4c);
    // LD_hli_A;
    wram->wc346[3] = wram->wcd4c;
    // LD_A(0x8);
    // LD_hli_A;
    wram->wc346[4] = LOW(0xc708);
    // LD_A(0xc7);
    // LD_hli_A;
    wram->wc346[5] = HIGH(0xc708);
    // LD_A(0x60);
    // LD_hli_A;
    wram->wc346[6] = LOW(0xcc60);
    // LD_A(0xcc);
    // LD_hli_A;
    wram->wc346[7] = HIGH(0xcc60);
    // CALL(aFunction119eb4);
    // CALL(aFunction119ec2);
    Function119ec2(Function119eb4(wram->wc346 + 8));
    // LD_A(0x40);
    // LD_addr_A(wcd89);
    wram->wcd89 = 0x40;
    // LD_HL(wc346);
    // LD_DE(w3_d000);
    // LD_BC(0x1000);
    // LD_A(MOBILEAPI_16);
    // JP(mFunction119e2b);
    Function119e2b(MOBILEAPI_16, &(mobile_api_data_s){.hl = wram->wc346, .de = wram->w3_d000, .bc = 0x1000});
}

void Function119054(void){
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(0x6);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as6_a000));
    // LD_HL(wd002);
    // LD_A_addr(wcd4f);
    // LD_E_A;
    // LD_A_addr(wcd50);
    // LD_D_A;
    uint16_t de = wram->wcd4f | (wram->wcd50 << 8);
    gb_write(rSVBK, 0x3);
    // LD_A_addr(w3_d000);
    // LD_C_A;
    // LD_A_addr(w3_d000 + 1);
    // LD_B_A;
    uint16_t bc = (wram->w3_d000[0] | (wram->w3_d001[0] << 8));
    // CALL(aFunction119192);
    // RET_C ;
    if(Function119192(de, wram->w3_d000 + 2, bc)) {
        gb_write(rSVBK, svbk);
        return;
    }
    // LD_A_addr(wcd89);
    // AND_A(0x1);
    // IF_Z goto asm_11908a;
    if(wram->wcd89 & 0x1) {
        // LD_A(0x6);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, 0x6);
        // LD_HL(wd002);
        // LD_A_addr(w3_d000);
        // LD_C_A;
        // LD_A_addr(w3_d000 + 1);
        // LD_B_A;
        uint16_t bc2 = (wram->w6_d000[0] | (wram->w6_d000[1] << 8));
        // CALL(aFunction119192);
        // RET_C ;
        if(Function119192(de + bc, wram->w6_d000 + 2, bc2)) {
            gb_write(rSVBK, svbk);
            return;
        }
    }

// asm_11908a:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(0x3);  // ???
    // LDH_addr_A(rSVBK);
    // LD_A(BANK(s5_b1b3));  // aka BANK(s5_b1b4) and BANK(s5_aa7f) and BANK(s5_b2f3) and BANK(s5_b2f4)
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_b1b3));
    // LD_A_addr(wcd4f);
    // LD_addr_A(s5_b1b3);
    gb_write(s5_b1b3, wram->wcd4f);
    // LD_A_addr(wcd50);
    // LD_addr_A(s5_b1b4);
    gb_write(s5_b1b4, wram->wcd50);
    // LD_HL(wcd20);
    // LD_DE(s5_aa7f);
    // LD_BC(12);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_aa7f), &wram->wEZChatSelection, 12);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wd474));  // aka BANK(wd475)
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wd474);
    // LD_addr_A(s5_b2f3);
    gb_write(s5_b2f3, wram->wPrefecture);
    // LD_HL(wd475);
    // LD_DE(s5_b2f4);
    // LD_BC(4);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b2f4), wram->wZipCode_Saved, ZIPCODE_LENGTH);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aCloseSRAM);
    CloseSRAM();
    gb_write(rSVBK, svbk);
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
}

void Function1190d0(void){
    // LD_A(BANK(w3_d000));
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wcd57);
    // LD_L_A;
    // LD_A_addr(wcd58);
    // LD_H_A;
    // LD_DE(wcc60);
    // CALL(aFunction1191ad);
    // RET_C ;
    if(Function1191ad(wram->wcc60_str, (const char*)wram->wram3 + (wram->wcd57 | (wram->wcd58 << 8))))
        return;
    // LD_DE(w3_d000);
    // LD_BC(0x1000);
    // JP(mFunction118b10);
    Function118b10(wram->w3_d000, 0x1000);
}

// Mobile_CopyNewsToSRAM
void Function1190ec(void){
    // LD_A(BANK(s5_aa73));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_aa73));
    // LD_HL(wBGMapBuffer);
    // LD_DE(s5_aa73);
    // LD_BC(12);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_aa73), &wram->wcd20, 12);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(BANK(s5_aa72));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_aa72));
    // LD_A(0x1);
    // LD_addr_A(s5_aa72);
    gb_write(s5_aa72, 0x1);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(BANK(s6_a000));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as6_a000));
    // LD_A_addr(w3_d000);
    // LD_C_A;
    // LD_A_addr(w3_d000 + 1);
    // LD_B_A;
    uint16_t bc = wram->wram3[0] | (wram->wram3[1] << 8);
    // LD_HL(wd002);
    // LD_DE(s6_a000);
    // CALL(aFunction119192);
    // RET_C ;
    if(Function119192(s6_a000, wram->w3_d002, bc))
        return;
    // LD_A_addr(wcd89);
    // AND_A(0x1);
    // IF_Z goto asm_11913e;
    if(wram->wcd89 & 0x1) {
        // LD_A(BANK(w6_d000));
        // LDH_addr_A(rSVBK);
        // LD_A_addr(w6_d000);
        // LD_C_A;
        // LD_A_addr(w6_d000 + 1);
        // LD_B_A;
        uint16_t bc2 = wram->w6_d000[0] | (wram->w6_d000[1] << 8);
        // LD_HL(w6_d000 + 2);
        // CALL(aFunction119192);
        // RET_C ;
        if(Function119192(s6_a000 + bc, wram->w6_d000 + 2, bc2))
            return;
    }

// asm_11913e:
    // LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    // LDH_addr_A(rSVBK);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_HL(mText_ReceivedNews);
    // CALL(aBattleTowerRoomMenu_SetMessage);
    BattleTowerRoomMenu_SetMessage(Text_ReceivedNews);
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
}

void Function11914e(void){
    // CALL(aBattleTowerRoomMenu2);
    // RET_C ;
    if(BattleTowerRoomMenu2())
        return;
    // LD_A(0x1c);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = 0x1c;
    // LD_A(0xa);
    // LD_addr_A(wMobileErrorCodeBuffer);
    wram->wMobileErrorCodeBuffer[0] = 0xa;
    // RET;
}

void Function11915d(void){
    // LD_HL(w3_d802);
    // LD_DE(wcd20);
    // LD_BC(12);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wcd20, wram->w3_d802, 12);
    // LD_A(BANK(s5_aa7f));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_aa7f));
    // LD_HL(wBGMapBuffer);
    const uint8_t* hl = &wram->wcd20;
    // LD_DE(s5_aa7f);
    const uint8_t* de = GBToRAMAddr(s5_aa7f);
    // LD_C(12);
    uint8_t c = 12;

    do {
    // asm_119176:
        // LD_A_de;
        // INC_DE;
        // CP_A_hl;
        // IF_NZ goto asm_119184;
        if(*(de++) != *(hl++)) {
        // asm_119184:
            // LD_A(0x16);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = 0x16;
            // LD_A(0xb);
            // LD_addr_A(wMobileErrorCodeBuffer);
            wram->wMobileErrorCodeBuffer[0] = 0xb;
            goto asm_11918e;
        }
        // INC_HL;
        // DEC_C;
        // IF_NZ goto asm_119176;
    } while(--c != 0);
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
    // goto asm_11918e;

asm_11918e:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

bool Function119192(uint16_t de, const void* hl_, uint16_t bc){
    const uint8_t* hl = hl_;
    // INC_B;
    // INC_C;
    bc++;
    // goto asm_11919e;
    while(--bc != 0) {
    // asm_119196:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        gb_write(de++, *(hl++));
        // LD_A(0xbf);
        // CP_A_D;
        // IF_C goto asm_1191a6;
        if(HIGH(de) >= 0xc0) {
        // asm_1191a6:
            // LD_A(0xd3);
            // CALL(aSetMobileErrorCode);
            SetMobileErrorCode(0xd3);
            // SCF;
            // RET;
            return true;
        }

    // asm_11919e:
        // DEC_C;
        // IF_NZ goto asm_119196;
        // DEC_B;
        // IF_NZ goto asm_119196;
    }
    // AND_A_A;
    // RET;
    return false;
}

bool Function1191ad(char* de, const char* hl){
    // PUSH_BC;
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);

    do {
    // asm_1191b4:
        // LD_A_hli;
        char ch = *(hl++);
        // LD_de_A;
        // INC_DE;
        *(de++) = ch;
        // AND_A_A;
        // IF_Z goto asm_1191cc;
        if(ch == 0) {
        // asm_1191cc:
            // LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
            // LDH_addr_A(rSVBK);
            // POP_BC;
            // AND_A_A;
            // RET;
            return false;
        }
        // INC_C;
        // LD_A_C;
        // CP_A(0xa6);
        // IF_C goto asm_1191b4;
    } while(++c < 0xa6);
    // LD_A(0xda);
    // CALL(aSetMobileErrorCode);
    SetMobileErrorCode(0xda);
    // LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    // LDH_addr_A(rSVBK);
    // POP_BC;
    // SCF;
    // RET;
    return true;
}

void Function1191d3(void){
    // LD_HL(w3_d100 + 2);
    uint16_t hl = 0x100 + 2;
    // LD_A_L;
    // LD_addr_A(wcd53);
    wram->wcd53 = LOW(hl);
    // LD_A_H;
    // LD_addr_A(wcd54);
    wram->wcd54 = HIGH(hl);
    // CALL(aFunction11920f);
    hl = Function11920f(hl);
    // LD_A_L;
    // LD_addr_A(wcd51);
    wram->wcd51 = LOW(hl);
    // LD_A_addr(wcd4a);
    // LD_A_H;
    // LD_addr_A(wcd52);
    wram->wcd52 = HIGH(hl);
    // CALL(aFunction11920f);
    hl = Function11920f(hl);
    // LD_A_L;
    // LD_addr_A(wcd55);
    wram->wcd55 = LOW(hl);
    // LD_A_addr(wcd4a);
    // LD_A_H;
    // LD_addr_A(wcd56);
    wram->wcd56 = HIGH(hl);
    // CALL(aFunction11920f);
    hl = Function11920f(hl);
    // LD_A_addr(wcd49);
    // LD_A_L;
    // LD_addr_A(wcd57);
    wram->wcd57 = LOW(hl);
    // LD_A_addr(wcd4a);
    // LD_A_H;
    // LD_addr_A(wcd58);
    wram->wcd58 = HIGH(hl);
    // CALL(aFunction11920f);
    hl = Function11920f(hl);
    // RET;
}

uint16_t Function11920f(uint16_t hl){
    while(1) {
    // asm_11920f:
        // CALL(aFunction118b9a);
        // RET_NC ;
        if(!Function118b9a(hl))
            return hl;
        // LD_A_hli;
        // CP_A(0xd);
        // IF_NZ goto asm_11920f;
        if(wram->wram3[hl++] != 0xd)
            continue;
        // LD_A_hli;
        // CP_A(0xa);
        // IF_NZ goto asm_11920f;
        if(wram->wram3[hl++] != 0xa)
            continue;
        break;
    }
    // DEC_HL;
    // XOR_A_A;
    // LD_hld_A;
    wram->wram3[hl - 1] = 0x0;
    // LD_hli_A;
    wram->wram3[hl - 2] = 0x0;
    // INC_HL;
    // RET;
    return hl;
}

bool Function119223(void){
    // XOR_A_A;
    // LD_addr_A(wcd4b);
    wram->wcd4b = 0;
    // LD_addr_A(wcd4c);
    wram->wcd4c = 0;
    // LD_A(BANK(s5_b092));  // aka BANK(s5_b1b1) and BANK(s5_b1b2) and BANK(s5_b1d3)
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_b092));
    // LD_HL(wc3cd);
    // LD_DE(s5_b092);
    // LD_BC(31);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b092), wram->wc3cd, 31);
    // DEC_DE;
    // XOR_A_A;
    // LD_de_A;
    gb_write(s5_b092 + 30, 0x0);
    // LD_HL(w3_d810);
    uint8_t* hl = wram->w3_d810;
    uint8_t a;

    do {
    // asm_119241:
        // LD_A_hli;
        a = *(hl++);
        // CP_A(0x50);
        // IF_NZ goto asm_119241;
    } while(a != 0x50);
    // LD_A_hli;
    // LD_addr_A(wcd4f);
    wram->wcd4f = *(hl++);
    // LD_A_hli;
    // LD_addr_A(wcd50);
    wram->wcd50 = *(hl++);
    // LD_A_hli;
    a = *(hl++);
    // LD_addr_A(s5_b1b1);
    gb_write(s5_b1b1, a);
    // LD_C_A;
    uint8_t c = a;
    // LD_A_hli;
    a = *(hl++);
    // LD_addr_A(s5_b1b2);
    gb_write(s5_b1b2, a);
    // LD_B_A;
    uint8_t b = a;
    uint16_t count = ((uint16_t)b << 8) | c;
    // LD_DE(s5_b1d3);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b1d3), hl, count);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_E_L;
    // LD_D_H;
    uint8_t* de = hl + count;
    // LD_HL(wc608);
    hl = wram->wc608;
    do {
    // asm_119266:
        // LD_A_de;
        // INC_DE;
        a = *(de++);
        // CP_A(0xff);
        // IF_Z goto asm_1192c2;
        if(a == 0xff) {
        // asm_1192c2:
            // LD_A_E;
            // LD_addr_A(wcd4d);
            // LD_A_D;
            // LD_addr_A(wcd4e);
            gMobile_wcd4d = de;
            // AND_A_A;
            // RET;
            return false;
        }
        // CP_A(0xfe);
        // IF_Z goto asm_1192a5;
        else if(a == 0xfe) {
        // asm_1192a5:
            // LD_A_addr(wcd4b);
            // LD_C_A;
            // LD_A_addr(wcd4c);
            // LD_B_A;
            uint16_t bc = wram->wcd4b | (wram->wcd4c << 8);
            // LD_A_de;
            a = *de;
            // INC_DE;
            de++;

            do {
            // asm_1192af:
                // PUSH_AF;
                // LD_A_de;
                // INC_DE;
                // LD_hli_A;
                *(hl++) = *(de++);
                // INC_BC;
                bc++;
                // POP_AF;
                // DEC_A;
                // IF_NZ goto asm_1192af;
            } while(--a != 0);
            // LD_A_C;
            // LD_addr_A(wcd4b);
            wram->wcd4b = LOW(bc);
            // LD_A_B;
            // LD_addr_A(wcd4c);
            wram->wcd4c = HIGH(bc);
            // goto asm_11929b;
        }
        else {
            // CALL(aOpenSRAM);
            OpenSRAM(a);
            // LD_A_de;
            // INC_DE;
            // LD_C_A;
            // LD_A_de;
            // INC_DE;
            // LD_B_A;
            uint8_t* bc2 = GBToRAMAddr(de[0] | (de[1] << 8));
            de += 2;
            // LD_A_de;
            // INC_DE;
            uint8_t a2 = *(de++);
            // PUSH_DE;
            // PUSH_AF;
            // LD_A_addr(wcd4b);
            // LD_E_A;
            // LD_A_addr(wcd4c);
            // LD_D_A;
            uint16_t de2 = wram->wcd4b | (wram->wcd4c << 8);
            // POP_AF;

            do {
            // asm_119286:
                // PUSH_AF;
                // LD_A_bc;
                // INC_BC;
                uint8_t ch = *(bc2++);
                // LD_hli_A;
                *(hl++) = ch;
                // INC_DE;
                de2++;
                // POP_AF;
                // DEC_A;
                // IF_NZ goto asm_119286;
            } while(--a2 != 0);
            // CALL(aCloseSRAM);
            CloseSRAM();
            // LD_A_E;
            // LD_addr_A(wcd4b);
            wram->wcd4b = LOW(de2);
            // LD_A_D;
            // LD_addr_A(wcd4c);
            wram->wcd4c = HIGH(de2);
            // POP_DE;
        }

    // asm_11929b:
        // AND_A_A;
        // IF_Z goto asm_119266;
    } while(a != 0);
    // LD_A(0xd3);
    // CALL(aSetMobileErrorCode);
    SetMobileErrorCode(0xd3);
    // SCF;
    // RET;
    return true;
}

bool Function1192cc(void){
    // LD_A(BANK(s5_aa73));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_aa73));
    // LD_HL(s5_aa73);
    // LD_DE(wc608);
    // LD_BC(12);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, GBToRAMAddr(s5_aa73), 12);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_HL(wc608);
    uint8_t* hl = wram->wc608;
    // LD_DE(wcd20);
    const uint8_t* de = &wram->wcd20;
    // LD_C(0xc);
    uint8_t c = 0xc;

    do {
    // asm_1192e8:
        // LD_A_de;
        // INC_DE;
        // LD_B_A;
        uint8_t b = *(de++);
        // LD_A_hli;
        // CP_A_B;
        uint8_t a = *(hl++);
        // IF_NZ goto asm_1192fe;
        if(a != b) {
        // asm_1192fe:
            // AND_A_A;
            // RET;
            return false;
        }
        // DEC_C;
        // IF_NZ goto asm_1192e8;
    } while(--c != 0);
    // LD_A(0x1f);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x1f;
    // LD_A(0x27);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = 0x27;
    // SCF;
    // RET;
    return true;
}

void Function119300(void){
    // XOR_A_A;
    // LD_addr_A(wcd4b);
    // LD_addr_A(wcd4c);
    wram->wcd4b = 0;
    wram->wcd4c = 0;
    // LD_A_addr(wcd4d);
    // LD_E_A;
    // LD_A_addr(wcd4e);
    // LD_D_A;
    const uint8_t* de = gMobile_wcd4d;
    // LD_HL(wc608);
    uint8_t* hl = wram->wc608;
    // LD_A_addr(wcd4b);
    // LD_C_A;
    // LD_A_addr(wcd4c);
    // LD_B_A;
    uint16_t bc = 0;

    do {
        while(1) {
        // asm_11931a:
            // LD_A_de;
            uint8_t a = *(de++);
            // INC_DE;
            // CP_A(0x50);
            // IF_Z goto asm_119324;
            if(a == 0x50)
                break;
            // LD_hli_A;
            *(hl++) = a;
            // INC_BC;
            bc++;
            // goto asm_11931a;
        }

    // asm_119324:
        // LD_A(0x3d);
        // LD_hli_A;
        *(hl++) = 0x3d;
        // INC_BC;
        bc++;
        // LD_A_C;
        // LD_addr_A(wcd4b);
        wram->wcd4b = LOW(bc);
        // LD_A_B;
        // LD_addr_A(wcd4c);
        wram->wcd4c = HIGH(bc);
        // LD_A_de;
        // INC_DE;
        uint8_t bank = *(de++);
        // CALL(aOpenSRAM);
        OpenSRAM(bank);
        // LD_A_de;
        // INC_DE;
        // LD_C_A;
        // LD_A_de;
        // INC_DE;
        // LD_B_A;
        uint8_t* bc2 = GBToRAMAddr(de[0] | (de[1] << 8));
        de += 2;
        // LD_A_de;
        // INC_DE;
        uint8_t a = *(de++);
        // PUSH_DE;
        // PUSH_AF;
        // LD_A_addr(wcd4b);
        // LD_E_A;
        // LD_A_addr(wcd4c);
        // LD_D_A;
        // POP_AF;

        do {
        // asm_119348:
            // PUSH_AF;
            // LD_A_bc;
            // AND_A(0xf0);
            // SWAP_A;
            // CALL(aFunction1197bf);
            // LD_hli_A;
            *(hl++) = Function1197bf((*bc2 >> 4) & 0xf);
            // INC_DE;
            bc++;
            // LD_A_bc;
            // INC_BC;
            // AND_A(0xf);
            // CALL(aFunction1197bf);
            // LD_hli_A;
            *(hl++) = Function1197bf(*(bc2++) & 0xf);
            // INC_DE;
            bc++;
            // POP_AF;
            // DEC_A;
            // IF_NZ goto asm_119348;
        } while(--a != 0);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // LD_A_E;
        // LD_addr_A(wcd4b);
        wram->wcd4b = LOW(bc);
        // LD_A_D;
        // LD_addr_A(wcd4c);
        wram->wcd4c = HIGH(bc);
        // POP_DE;
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto asm_11937f;
        if(*de == 0x50)
            break;
        // LD_A_addr(wcd4b);
        // LD_C_A;
        // LD_A_addr(wcd4c);
        // LD_B_A;
        // LD_A(0x26);
        // LD_hli_A;
        *(hl++) = 0x26;
        // INC_BC;
        bc++;
        // goto asm_11931a;
    } while(1);


// asm_11937f:
    // RET;

}

void Function119380(void){
    LD_A(0x80);
    LD_addr_A(wcd49);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119388(void){
    LD_HL(wcd49);
    DEC_hl;
    RET_NZ ;
    LD_HL(wcc60);
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x10);
    LD_addr_A(wMobileInactivityTimerSeconds);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function1193a0();
}

void Function1193a0(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aDelayFrame);
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    LD_HL(wc346);
    LD_A(LOW(w3_d000));
    LD_hli_A;
    LD_A(HIGH(w3_d000));
    LD_hli_A;
    LD_A_addr(wcd3b);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_A(LOW(wc708));
    LD_hli_A;
    LD_A(HIGH(wc708));
    LD_hli_A;
    LD_A(0x60);
    LD_hli_A;
    LD_A(0xcc);
    LD_hli_A;
    CALL(aFunction119eb4);
    CALL(aFunction119ec2);
    LD_A(0x40);
    LD_addr_A(wcd89);
    LD_HL(wc346);
    LD_DE(w3_de00);
    LD_BC(0x200);
    LD_A(MOBILEAPI_16);
    JP(mFunction119e2b);

}

void Function1193e3(void){
    LD_HL(wcd49);
    DEC_hl;
    RET_NZ ;
    LD_HL(wcc60);
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x11);
    LD_addr_A(wMobileInactivityTimerSeconds);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function1193fb();
}

void Function1193fb(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aDelayFrame);
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    JP(mFunction118b10);

}

void Function119413(void){
    LD_A(0x6);  // ???
    CALL(aOpenSRAM);
    LD_A_addr(w3_d000);
    LD_C_A;
    LD_A_addr(w3_d000 + 1);
    LD_B_A;
    DEC_BC;
    DEC_BC;
    LD_HL(wd002);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    CALL(aFunction119192);
    RET_C ;
    LD_A_addr(wcd89);
    AND_A(0x1);
    IF_Z goto asm_119447;
    LD_A(BANK(w6_d000));
    LDH_addr_A(rSVBK);
    LD_A_addr(w6_d000);
    LD_C_A;
    LD_A_addr(w6_d000 + 1);
    LD_B_A;
    LD_HL(w6_d000 + 2);
    CALL(aFunction119192);
    RET_C ;


asm_119447:
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    CALL(aCloseSRAM);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119451(void){
    LD_A_addr(wcd89);
    AND_A(0x1);
    IF_Z goto asm_11945d;
    LD_A(0xd3);
    JP(mSetMobileErrorCode);

asm_11945d:
    XOR_A_A;
    LD_addr_A(wcd50);
    CALL(aFunction119694);
    LD_A_B;
    LD_addr_A(wcd49);
    CALL(aFunction1196cd);
    LD_A_addr(wd002);
    LD_HL(wd003);

    return Function119471();
}

void Function119471(void){
    PUSH_AF;
    LD_A_hli;
    LD_addr_A(wc608);
    LD_A_hli;
    LD_addr_A(wc608 + 3);
    LD_A_hli;
    LD_addr_A(wc608 + 1);
    LD_A_hli;
    LD_addr_A(wc608 + 2);
    LD_A_hli;
    LD_addr_A(wc608 + 4);
    LD_A_hli;
    LD_addr_A(wc608 + 5);
    PUSH_HL;
    LD_A_addr(wc608);
    CP_A(0xff);
    IF_Z goto asm_1194a7;
    LD_A_addr(wc608 + 2);
    CP_A(0xff);
    IF_Z goto asm_1194a7;
    LD_A_addr(wc608 + 1);
    CP_A(0xff);
    IF_NZ goto asm_1194a7;
    CALL(aFunction119584);
    IF_C goto asm_11950c;
    goto asm_1194f0;

asm_1194a7:
    LD_HL(wc608);
    LD_DE(wc608 + 3);
    LD_C(0x3);

asm_1194af:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_C goto asm_1194f3;
    IF_Z goto asm_1194b9;
    IF_NC goto asm_1194bc;

asm_1194b9:
    DEC_C;
    IF_NZ goto asm_1194af;

asm_1194bc:
    LD_C(0x3);
    LD_HL(wcd49);
    LD_DE(wc608);

asm_1194c4:
    LD_A_de;
    INC_DE;
    CP_A(0xff);
    IF_Z goto asm_1194d1;
    CP_A_hl;
    IF_Z goto asm_1194d1;
    IF_C goto asm_1194d5;
    IF_NC goto asm_1194f0;

asm_1194d1:
    INC_HL;
    DEC_C;
    IF_NZ goto asm_1194c4;

asm_1194d5:
    LD_C(0x3);
    LD_HL(wcd49);
    LD_DE(wc608 + 3);

asm_1194dd:
    LD_A_de;
    INC_DE;
    CP_A(0xff);
    IF_Z goto asm_1194ea;
    CP_A_hl;
    IF_C goto asm_1194f0;
    IF_Z goto asm_1194ea;
    IF_NC goto asm_11950c;

asm_1194ea:
    INC_HL;
    DEC_C;
    IF_NZ goto asm_1194dd;
    goto asm_11950c;

asm_1194f0:
    POP_HL;
    goto asm_119557;

asm_1194f3:
    LD_C(0x3);
    LD_HL(wcd49);
    LD_DE(wc608);

asm_1194fb:
    LD_A_de;
    INC_DE;
    CP_A(0xff);
    IF_Z goto asm_119508;
    CP_A_hl;
    IF_C goto asm_11950c;
    IF_Z goto asm_119508;
    IF_NC goto asm_1194d5;

asm_119508:
    INC_HL;
    DEC_C;
    IF_NZ goto asm_1194fb;

asm_11950c:
    POP_HL;
    LD_A(0x1);
    LD_addr_A(wcd50);
    LD_A_L;
    LD_addr_A(wc608);
    LD_A_H;
    LD_addr_A(wc608 + 1);
    LD_DE(wcd69);
    LD_C(0x10);
    LD_B(0x0);

asm_119521:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto asm_119528;
    INC_B;

asm_119528:
    DEC_C;
    IF_NZ goto asm_119521;
    LD_A(0x10);
    CP_A_B;
    IF_Z goto asm_119536;
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
    goto asm_11957a;

asm_119536:
    LD_A_hli;
    CP_A(0x50);
    IF_NZ goto asm_119552;
    LD_A_hli;
    CP_A(0x33);
    IF_NZ goto asm_119553;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_A_addr(wcd83);
    CP_A_C;
    IF_NZ goto asm_119576;
    LD_A_addr(wcd84);
    CP_A_B;
    IF_NZ goto asm_119576;
    goto asm_11955b;

asm_119552:
    INC_HL;

asm_119553:
    INC_HL;
    INC_HL;
    goto asm_11955b;

asm_119557:
    LD_DE(0x14);
    ADD_HL_DE;

asm_11955b:
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    ADD_HL_DE;
    POP_AF;
    DEC_A;
    JP_NZ (mFunction119471);
    LD_A_addr(wcd50);
    AND_A_A;
    IF_Z goto asm_119571;
    LD_A(0x1a);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

asm_119571:
    LD_A(0xd8);
    JP(mSetMobileErrorCode);

asm_119576:
    LD_A(0x10);
    goto asm_11957c;

asm_11957a:
    LD_A(0xf);

asm_11957c:
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    POP_AF;
    CALL(aFunction1195c4);
    RET;

}

void Function119584(void){
    LD_A_addr(wc608);
    LD_B_A;
    LD_A_addr(wc608 + 3);
    LD_C_A;
    CP_A_B;
    IF_C goto asm_11959c;
    LD_A_addr(wcd49);
    CP_A_B;
    IF_C goto asm_1195c2;

asm_119595:
    CP_A_C;
    IF_C goto asm_1195a2;
    IF_Z goto asm_1195a2;
    goto asm_1195c2;

asm_11959c:
    LD_A_addr(wcd49);
    CP_A_B;
    IF_C goto asm_119595;

asm_1195a2:
    LD_A_addr(wc608 + 2);
    LD_B_A;
    LD_A_addr(wc608 + 5);
    LD_C_A;
    CP_A_B;
    IF_C goto asm_1195ba;
    LD_A_addr(wcd4b);
    CP_A_B;
    IF_C goto asm_1195c2;

asm_1195b3:
    CP_A_C;
    IF_C goto asm_1195c0;
    IF_Z goto asm_1195c0;
    goto asm_1195c2;

asm_1195ba:
    LD_A_addr(wcd4b);
    CP_A_B;
    IF_C goto asm_1195b3;

asm_1195c0:
    SCF;
    RET;

asm_1195c2:
    AND_A_A;
    RET;

}

void Function1195c4(void){
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_DE(0xa5);
    LD_A_B;
    CP_A_D;
    IF_C goto asm_1195d9;
    IF_Z goto asm_1195d3;
    IF_NC goto asm_1195f3;

asm_1195d3:
    LD_A_C;
    CP_A_E;
    IF_Z goto asm_1195d9;
    IF_NC goto asm_1195f3;

asm_1195d9:
    LD_DE(wcc60);
    CALL(aCopyBytes);
    XOR_A_A;
    LD_de_A;
    LD_A_addr(wc608);
    LD_L_A;
    LD_A_addr(wc608 + 1);
    LD_H_A;
    LD_DE(wcd69);
    LD_BC(0x10);
    CALL(aCopyBytes);
    RET;

asm_1195f3:
    LD_A(0xd8);
    JP(mSetMobileErrorCode);

}

void Function1195f8(void){
    LD_A(0x11);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x1c);
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A(0xf);
    LD_addr_A(wMobileInactivityTimerFrames);
    LD_A(0x14);
    LD_addr_A(wcd47);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119612(void){
    LD_A(0x14);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x1c);
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A(0x10);
    LD_addr_A(wMobileInactivityTimerFrames);
    LD_A(0x14);
    LD_addr_A(wcd47);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119629(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A(0x60);
    LD_L_A;
    LD_A(0xcc);
    LD_H_A;
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x1c);
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A(0x14);
    LD_addr_A(wcd47);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function119648();
}

void Function119648(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aDelayFrame);
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    CALL(aFunction118b24);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    LD_A(MOBILEAPI_15);
    JP(mFunction119e2b);

}

void Function119665(void){
    LD_A(0x1a);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function11966d();
}

void Function11966d(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A_addr(wcd47);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    RET;

}

void Function11967d(void){
    LD_A(0x18);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function119685();
}

void Function119685(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A(0x14);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    RET;

}

void Function119694(void){
    LD_B(0);
    LD_HL(mUnknown_1196b8);

asm_119699:
    LD_DE(wc708);
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto asm_1196af;
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto asm_1196b0;
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto asm_1196b1;
    RET;

asm_1196af:
    INC_HL;

asm_1196b0:
    INC_HL;

asm_1196b1:
    INC_B;
    LD_A_B;
    CP_A(0x7);
    IF_NZ goto asm_119699;
    RET;

// pushc
// setcharmap ascii
}

const char Unknown_1196b8[][4] = {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun",

// popc
};

void Function1196cd(void){
    LD_DE(wc719);
    CALL(aFunction1196de);
    LD_addr_A(wcd4a);
    INC_DE;
    CALL(aFunction1196de);
    LD_addr_A(wcd4b);
    RET;

}

void Function1196de(void){
    LD_A_de;
    INC_DE;
// b = ([de] - 48) * 2
// c = ([de] - 48) * 10
    SUB_A(0x30);
    SLA_A;
    LD_B_A;
    SLA_A;
    SLA_A;
    ADD_A_B;
    LD_C_A;
    ADD_HL_BC;
    LD_A_de;
    INC_DE;
    SUB_A(0x30);
    ADD_A_C;
    RET;

}

void Function1196f2(void){
    LD_HL(wd002);

asm_1196f5:
    CALL(aFunction118b9a);
    RET_NC ;
    LD_A_hli;
    CP_A(0xd);
    IF_NZ goto asm_1196f5;
    LD_A_hl;
    CP_A(0xa);
    IF_NZ goto asm_1196f5;
    XOR_A_A;
    LD_hld_A;
    LD_hli_A;
    LD_A_L;
    LD_addr_A(wcd5b);
    LD_A_H;
    LD_addr_A(wcd5c);
    INC_HL;
    LD_E_L;
    LD_D_H;
    LD_A_de;
    INC_DE;
    CP_A(0xd);
    IF_NZ goto asm_119722;
    LD_A_de;
    INC_DE;
    CP_A(0xa);
    IF_NZ goto asm_119722;
    LD_A(0xb);
    JP(mSetMobileErrorCode);


asm_119722:
    CALL(aRandom);
    LD_C(0x0);
    LD_B_C;

asm_119728:
    CALL(aFunction119798);
    LD_A_D;
    CP_A(0xff);
    IF_NZ goto asm_119735;
    LD_A_E;
    CP_A(0xff);
    IF_Z goto asm_11974c;


asm_119735:
    LDH_A_addr(hRandomSub);
    CP_A_D;
    IF_C goto asm_11974c;
    IF_Z goto asm_11973e;
    goto asm_119745;


asm_11973e:
    LDH_A_addr(hRandomAdd);
    CP_A_E;
    IF_C goto asm_11974c;
    IF_Z goto asm_11974c;


asm_119745:
    INC_BC;
    LD_A_C;
    OR_A_B;
    IF_Z goto asm_119770;
    goto asm_119728;


asm_11974c:
    LD_A_addr(wcd5b);
    LD_L_A;
    LD_A_addr(wcd5c);
    LD_H_A;

asm_119754:
    LD_A_hld;
    CP_A(0x58);
    IF_NZ goto asm_119754;
    LD_D(0x0);

asm_11975b:
    INC_D;
    LD_A_hld;
    CP_A(0x58);
    IF_Z goto asm_11975b;
    INC_HL;
    INC_HL;
    LD_A_D;
    DEC_A;
    IF_Z goto asm_11978e;
    DEC_A;
    IF_Z goto asm_119785;
    DEC_A;
    IF_Z goto asm_11977e;
    DEC_A;
    IF_Z goto asm_119775;


asm_119770:
    LD_A(0xd3);
    JP(mSetMobileErrorCode);


asm_119775:
    LD_A_B;
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction1197bf);
    LD_hli_A;


asm_11977e:
    LD_A_B;
    AND_A(0xf);
    CALL(aFunction1197bf);
    LD_hli_A;


asm_119785:
    LD_A_C;
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction1197bf);
    LD_hli_A;


asm_11978e:
    LD_A_C;
    AND_A(0xf);
    CALL(aFunction1197bf);
    LD_hli_A;
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119798(void){
    LD_D(0x0);
    LD_E_D;
    CALL(aFunction1197b4);
    SWAP_A;
    OR_A_D;
    LD_D_A;
    CALL(aFunction1197b4);
    OR_A_D;
    LD_D_A;
    CALL(aFunction1197b4);
    SWAP_A;
    OR_A_E;
    LD_E_A;
    CALL(aFunction1197b4);
    OR_A_E;
    LD_E_A;
    RET;

}

void Function1197b4(void){
    LD_A_hli;
    CP_A(0x61);
    IF_NC goto asm_1197bc;
    SUB_A(0x30);
    RET;


asm_1197bc:
    SUB_A(0x57);
    RET;

}

uint8_t Function1197bf(uint8_t a){
    // CP_A(0xa);
    // IF_NC goto asm_1197c6;
    if(a >= 0xa) {
    // asm_1197c6:
        // ADD_A(0x57);
        // RET;
        return a + 0x57;
    }
    else {
        // ADD_A(0x30);
        // RET;
        return a + 0x30;
    }
}

void Function1197c9(void){
    LD_HL(wd002);
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x12);
    LD_addr_A(wMobileInactivityTimerSeconds);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function1197dc();
}

void Function1197dc(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aDelayFrame);
    LD_HL(wd002);
    LD_DE(wcc60);
    LD_BC(0x0080);
    CALL(aCopyBytes);
    DEC_DE;
    XOR_A_A;
    LD_de_A;
    CALL(aFunction118b24);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    LD_A(MOBILEAPI_15);
    JP(mFunction119e2b);

}

void Function119800(void){
    LD_A(0xfd);
    LD_addr_A(wc6d0);
    LD_addr_A(wOTTrademonSpecies);
    LD_A_addr(wcd81);
    LD_addr_A(wc74e);
    LD_A_addr(wJumptableIndex);
    PUSH_AF;
    LD_A_addr(wcf64);
    PUSH_AF;
    LD_A_addr(wcf65);
    PUSH_AF;
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    CALL(aFadeToMenu);
    FARCALL(aFunction10803d);
    CALL(aFunction11a9ce);
    CALL(aRestartMapMusic);
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    POP_AF;
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    POP_AF;
    LD_addr_A(wcf65);
    POP_AF;
    LD_addr_A(wcf64);
    POP_AF;
    LD_addr_A(wJumptableIndex);
    FARCALL(aFunction115dc3);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

// StageOfferMonDataAndShowGTSAnimation
void Function11984e(void){
    // LD_A_addr(wcd80);
    // AND_A_A;
    // IF_NZ goto asm_1198a0;
    if(wram->wcd80 != 0) {
    // asm_1198a0:
        // LD_A(0xa);
        // LD_addr_A(wMobileErrorCodeBuffer);
        wram->wMobileErrorCodeBuffer[0] = 0xa;
        // JP(mBattleTowerRoomMenu_IncrementJumptable);
        return BattleTowerRoomMenu_IncrementJumptable();
    }
    // LD_A_addr(wcd38);
    // AND_A_A;
    // IF_NZ goto asm_1198a8;
    if(wram->wcd38 == 0) {
        // FARCALL(aFunction170000);
        Function170000();
        // LD_A_addr(wJumptableIndex);
        // PUSH_AF;
        uint8_t jumptableIndex = wram->wJumptableIndex;
        // LD_A_addr(wcf64);
        // PUSH_AF;
        uint8_t cf64 = wram->wcf64;
        // LD_A_addr(wcf65);
        // PUSH_AF;
        uint8_t cf65 = wram->wcf65;
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // PUSH_AF;
        uint8_t battleTowerRoomMenuJumptableIndex = wram->wBattleTowerRoomMenuJumptableIndex;
        // LD_A(0x1);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, 0x1);
        // CALL(aFadeToMenu);
        FadeToMenu();
        // FARCALL(aMobileTradeAnimation_SendGivemonToGTS);
        MobileTradeAnimation_SendGivemonToGTS();
        // CALL(aFunction11a9ce);
        Function11a9ce();
        // CALL(aRestartMapMusic);
        RestartMapMusic();
        // LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, MBANK(aw3_d000)); // BANK("Battle Tower RAM")
        // POP_AF;
        // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
        wram->wBattleTowerRoomMenuJumptableIndex = battleTowerRoomMenuJumptableIndex;
        // POP_AF;
        // LD_addr_A(wcf65);
        wram->wcf65 = cf65;
        // POP_AF;
        // LD_addr_A(wcf64);
        wram->wcf64 = cf64;
        // POP_AF;
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = jumptableIndex;
        // FARCALL(aFunction115dc3);
        Function115dc3();
        // JP(mBattleTowerRoomMenu_IncrementJumptable);
        return BattleTowerRoomMenu_IncrementJumptable();
    }
    else {
    // asm_1198a8:
        // FARCALL(aFunction17005a);
        Function17005a();
        // LD_A_addr(wJumptableIndex);
        // PUSH_AF;
        uint8_t jumptableIndex = wram->wJumptableIndex;
        // LD_A_addr(wcf64);
        // PUSH_AF;
        uint8_t cf64 = wram->wcf64;
        // LD_A_addr(wcf65);
        // PUSH_AF;
        uint8_t cf65 = wram->wcf65;
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // PUSH_AF;
        uint8_t battleTowerRoomMenuJumptableIndex = wram->wBattleTowerRoomMenuJumptableIndex;
        // LD_A(0x1);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, 0x1);
        // CALL(aFadeToMenu);
        FadeToMenu();
        // FARCALL(aMobileTradeAnimation_RetrieveGivemonFromGTS);
        MobileTradeAnimation_RetrieveGivemonFromGTS();
        // CALL(aFunction11a9ce);
        Function11a9ce();
        // CALL(aRestartMapMusic);
        RestartMapMusic();
        // LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, MBANK(aw3_d000)); // BANK("Battle Tower RAM")
        // POP_AF;
        // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
        wram->wBattleTowerRoomMenuJumptableIndex = battleTowerRoomMenuJumptableIndex;
        // POP_AF;
        // LD_addr_A(wcf65);
        wram->wcf65 = cf65;
        // POP_AF;
        // LD_addr_A(wcf64);
        wram->wcf64 = cf64;
        // POP_AF;
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = jumptableIndex;
        // FARCALL(aFunction115dc3);
        Function115dc3();
        // JP(mBattleTowerRoomMenu_IncrementJumptable);
        return BattleTowerRoomMenu_IncrementJumptable();
    }
}

void Function1198ee(void){
    // LD_HL(mText_RegisteringRecord);
    // CALL(aBattleTowerRoomMenu_SetMessage);
    BattleTowerRoomMenu_SetMessage(Text_RegisteringRecord);
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

    return Function1198f7();
}

void Function1198f7(void){
    // LD_A_addr(wc31a);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wc31a != 0)
        return;
    // LD_HL(wc608 + 2);
    // CALL(aFunction119940);
    Function119940(wram->wc608 + 2);
    // LD_HL(w3_d800);
    uint8_t* hl = wram->w3_d800;
    // LD_A(LOW(wc608));
    // LD_hli_A;
    *(hl++) = LOW(wc608);
    // LD_A(HIGH(wc608));
    // LD_hli_A;
    *(hl++) = HIGH(wc608);
    // LD_A(0xf6);
    // LD_hli_A;
    *(hl++) = LOW(BATTLE_TOWER_DATA_UPLOAD_LENGTH);
    // XOR_A_A;
    // LD_hli_A;
    *(hl++) = HIGH(BATTLE_TOWER_DATA_UPLOAD_LENGTH);
    // LD_A(LOW(wc708));
    // LD_hli_A;
    *(hl++) = LOW(wc708);
    // LD_A(HIGH(wc708));
    // LD_hli_A;
    *(hl++) = HIGH(wc708);
    // LD_A_addr(wcd51);
    // LD_hli_A;
    *(hl++) = LOW(w3_d000 + ((wram->wcd52 << 8) | wram->wcd51));
    // LD_A_addr(wcd52);
    // LD_hli_A;
    *(hl++) = HIGH(w3_d000 + ((wram->wcd52 << 8) | wram->wcd51));
    // CALL(aFunction119eb4);
    // CALL(aFunction119ec2);
    Function119ec2(Function119eb4(hl));
    // LD_A(0x40);
    // LD_addr_A(wcd89);
    wram->wcd89 = 0x40;
    // LD_HL(w3_d800);
    // LD_DE(w3_de00);
    // LD_BC(0x200);
    // LD_A(MOBILEAPI_16);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_16, &(mobile_api_data_s){.de = wram->w3_de00, .hl = wram->w3_d800, .bc = 0x200});
}

void Function119937(void){
    // FARCALL(aFunction1707f4);
    Function1707f4();
    // JP(mBattleTowerRoomMenu_IncrementJumptable);
    return BattleTowerRoomMenu_IncrementJumptable();
}

void Function119940(uint8_t* hl){
    // LD_DE(wc3cd);
    const uint8_t* de = wram->wc3cd;
    // LD_C(0x1e);
    uint8_t c = 0x1e;

    uint8_t a;
    do {
    // asm_119945:
        // LD_A_de;
        a = *(de++);
        // INC_DE;
        // LD_hli_A;
        *(hl++) = a;
        // DEC_C;
        // IF_Z goto asm_119953;
        if(--c == 0)
            return;
        // AND_A_A;
        // IF_NZ goto asm_119945;
    } while(a != 0);
    // XOR_A_A;

    do {
    // asm_11994f:
        // LD_hli_A;
        *(hl++) = 0;
        // DEC_C;
        // IF_NZ goto asm_11994f;
    } while(--c != 0);

// asm_119953:
    // RET;
}

void Function119954(void){
    // LD_A(0x1c);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x1c;
    // CALL(aBattleTowerRoomMenu2);
    BattleTowerRoomMenu2();
    // LD_HL(wc608);
    uint8_t* hl = wram->wc608;
    // LD_DE(wc3cd);
    const uint8_t* de = wram->wc3cd;

    uint8_t a;
    do {
    // asm_119962:
        // LD_A_de;
        // INC_DE;
        a = *(de++);
        // LD_hli_A;
        *(hl++) = a;
        // AND_A_A;
        // IF_NZ goto asm_119962;
    } while(a != 0);
    // CALL(aFunction119ec2);
    Function119ec2(hl);
    // LD_HL(wc608);
    // LD_A(MOBILEAPI_0F);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_0F, &(mobile_api_data_s){.hl = wram->wc608});
}

void Function119973(void){
    // LD_A(0x1);
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x1;
    // XOR_A_A;
    // LD_addr_A(wcf65);
    wram->wcf65 = 0x0;
    // LD_addr_A(w3_d090);
    wram->w3_d090[0] = 0;
    // LD_DE(w3_d000);
    // LD_A(MOBILEAPI_10);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_10, &(mobile_api_data_s){.de = wram->w3_d000});
}

void Function119987(void){
    // LD_HL(w3_d000 + 1);
    // LD_A_addr(w3_d000);
    // OR_A_hl;
    // IF_Z goto asm_1199a0;
    if((wram->w3_d001[0] | wram->w3_d000[0]) != 0) {
        // LD_A_addr(wcf64);
        // LD_L_A;
        // LD_A_addr(wcf65);
        // LD_H_A;
        // LD_DE(wBGPals2);
        mobile_api_data_s data = {.l = wram->wcf64, .h = wram->wcf65, .de = wram->w3_d080};
        // LD_A(MOBILEAPI_11);
        // JP(mFunction119e2b);
        return Function119e2b(MOBILEAPI_11, &data);
    }

// asm_1199a0:
    // LD_A_addr(w3_d090);
    // AND_A_A;
    // IF_Z goto asm_1199ae;
    else if(wram->w3_d090[0] != 0) {
        // LD_A(0x16);
        // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
        wram->wBattleTowerRoomMenuJumptableIndex = 0x16;
        // JP(mFunction119b0d);
        return Function119b0d();
    }
    else {
    // asm_1199ae:
        // LD_A(0x1b);
        // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
        wram->wBattleTowerRoomMenuJumptableIndex = 0x1b;
        // RET;
    }
}

void Function1199b4(void){
    uint16_t size = (wram->w3_d081[1] << 8) | wram->w3_d081[0];
    // LD_A_addr(w3_d081 + 1);
    // AND_A_A;
    // IF_NZ goto asm_1199c7;
    // LD_A_addr(w3_d081);
    // CP_A(0x7);
    // IF_NC goto asm_1199c7;
    if(size >= 0x7) {
    // asm_1199c7:
        // JP(mFunction119ac9);
        return Function119ac9();
    }
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
    // JP(mFunction1199ca);
    return Function1199ca();

}

void Function1199ca(void){
    // LD_A(0x20);
    // LD_addr_A(wcd89);
    wram->wcd89 = 0x20;
    // LD_A_addr(wcf64);
    // LD_L_A;
    // LD_A_addr(wcf65);
    // LD_H_A;
    // LD_DE(w3_d100);
    // LD_BC(0x0700);
    mobile_api_data_s data = {.l = wram->wcf64, .h = wram->wcf65, .de = wram->w3_d100, .bc = 0x0700};
    // LD_A(MOBILEAPI_14);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_14, &data);
}

static void Function1199e2_asm_119aa7(void){
    // LD_A(0x25);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = 0x25;
    // JP(mFunction119b45);
    return Function119b45();
}

void Function1199e2(void){
    // LD_C(0xc);
    // LD_DE(mXGameCodePrefix);
    // CALL(aFunction119e4f);
    u8_flag_s res = Function119e4f(XGameCodePrefix, 0xc);
    // JP_C (mFunction119ac9);
    if(res.flag)
        return Function119ac9();
    // LD_A_C;
    // CP_A(0x1);
    // JP_NZ (mFunction119ac9);
    if(res.a != 0x1)
        return Function119ac9();
    // LD_HL(w3_d880);
    const char* hl = (char*)wram->w3_d880;
    // LD_BC(mXGameCode);
    const char* bc = XGameCode;

    while(*bc != 0) {
    // loop:
        // LD_A_bc;
        // AND_A_A;
        // IF_Z goto game_result_prefix;
        // CP_A_hl;
        // JP_NZ (mFunction119ac9);
        if(*bc != *hl)
            return Function119ac9();
        // INC_BC;
        // INC_HL;
        bc++, hl++;
        // goto loop;
    }

// game_result_prefix:
    // LD_C(0x17);
    // LD_DE(mXGameResultPrefix);
    // CALL(aFunction119e4f);
    res = Function119e4f(XGameResultPrefix, 0x17);
    // JP_C (mFunction1199e2_asm_119aa7);
    // LD_A_C;
    // CP_A(0x1);
    // JP_NZ (mFunction1199e2_asm_119aa7);
    if(res.flag || res.a != 0x1)
        return Function1199e2_asm_119aa7();
    // LD_A_addr(w3_d880);
    // CP_A(0x31);
    // JP_NZ (mFunction1199e2_asm_119aa7);
    if(wram->w3_d880[0] != 0x31)
        return Function1199e2_asm_119aa7();
    // LD_A_addr(w3_d881);
    // CP_A(0x20);
    // JP_NZ (mFunction1199e2_asm_119aa7);
    if(wram->w3_d881[0] != 0x20)
        return Function1199e2_asm_119aa7();
    // LD_A_addr(w3_d88a);
    // CP_A(0x20);
    // JP_NZ (mFunction1199e2_asm_119aa7);
    if(wram->w3_d88a[0] != 0x20)
        return Function1199e2_asm_119aa7();
    // LD_A_addr(w3_d894);
    // CP_A(0x20);
    // JP_NZ (mFunction1199e2_asm_119aa7);
    if(wram->w3_d894[0] != 0x20)
        return Function1199e2_asm_119aa7();
    // XOR_A_A;
    // LD_addr_A(w3_d8a0);
    wram->w3_d8a0 = 0;
    // LD_addr_A(w3_d8a1);
    wram->w3_d8a1 = 0;
    // LD_addr_A(w3_d8a2);
    wram->w3_d8a2 = 0;
    // LD_addr_A(w3_d8a3);
    wram->w3_d8a3 = 0;
    // LD_HL(w3_d8a0);
    uint8_t* hl2 = &wram->w3_d8a0;
    // LD_BC(w3_d889);
    uint8_t* bc2 = wram->w3_d889;
    // CALL(aFunction119e98);
    Function119e98(hl2, bc2);
    // CALL(aFunction119e98);
    Function119e98(hl2 + 2, bc2 - 4);
    // LD_HL(w3_d8a0);
    // LD_A_addr(wcd2d);
    // CP_A_hl;
    // JR_NZ (mFunction119ac9);
    if(wram->w3_d8a0 != wram->wcd2d)
        return Function119ac9();
    // INC_HL;
    // LD_A_addr(wcd2c);
    // CP_A_hl;
    // JR_NZ (mFunction119ac9);
    if(wram->w3_d8a1 != wram->wcd2c)
        return Function119ac9();
    // INC_HL;
    // LD_A_addr(wcd2b);
    // CP_A_hl;
    // JR_NZ (mFunction119ac9);
    if(wram->w3_d8a2 != wram->wcd2b)
        return Function119ac9();
    // INC_HL;
    // LD_A_addr(wcd2a);
    // CP_A_hl;
    // JR_NZ (mFunction119ac9);
    if(wram->w3_d8a3 != wram->wcd2a)
        return Function119ac9();
    // XOR_A_A;
    // LD_addr_A(w3_d8a0);
    wram->w3_d8a0 = 0;
    // LD_addr_A(w3_d8a1);
    wram->w3_d8a1 = 0;
    // LD_addr_A(w3_d8a2);
    wram->w3_d8a2 = 0;
    // LD_addr_A(w3_d8a3);
    wram->w3_d8a3 = 0;
    // LD_HL(w3_d8a0);
    hl2 = &wram->w3_d8a0;
    // LD_BC(w3_d88e);
    // CALL(aFunction119e98);
    Function119e98(hl2, wram->w3_d88e);
    // LD_BC(w3_d893);
    // CALL(aFunction119e98);
    Function119e98(hl2 + 2, wram->w3_d893);
    // LD_HL(w3_d8a0);
    // LD_A_addr(wcd2f);
    // CP_A_hl;
    // IF_NZ goto asm_119aa7;
    if(wram->w3_d8a0 != wram->wcd2f)
        return Function1199e2_asm_119aa7();
    // INC_HL;
    // LD_A_addr(wcd2e);
    // CP_A_hl;
    // IF_NZ goto asm_119aa7;
    if(wram->w3_d8a1 != wram->wcd2e)
        return Function1199e2_asm_119aa7();
    // INC_HL;
    // LD_A_addr(wcd31);
    // CP_A_hl;
    // IF_NZ goto asm_119aa7;
    if(wram->w3_d8a2 != wram->wcd31)
        return Function1199e2_asm_119aa7();
    // INC_HL;
    // LD_A_addr(wcd30);
    // CP_A_hl;
    // IF_Z goto asm_119aaf;
    // goto asm_119aa7;
    if(wram->w3_d8a3 != wram->wcd30)
        return Function1199e2_asm_119aa7();

// asm_119aaf:
    // LD_A_addr(w3_d090);
    // AND_A_A;
    // IF_NZ goto asm_119aa7;
    if(wram->w3_d090[0] != 0)
        return Function1199e2_asm_119aa7();
    // LD_A_addr(w3_d895);
    // SUB_A(0x30);
    // LD_addr_A(w3_d090);
    wram->w3_d090[0] = wram->w3_d895[0] - 0x30;
    // LD_A_addr(wcf64);
    // LD_addr_A(w3_d090 + 1);
    wram->w3_d090[1] = wram->wcf64;
    // LD_A_addr(wcf65);
    // LD_addr_A(w3_d090 + 2);
    wram->w3_d090[2] = wram->wcf65;

    return Function119ac9();
}

void Function119ac9(void){
    // LD_A_addr(w3_d000);
    // LD_L_A;
    // LD_A_addr(w3_d000 + 1);
    // LD_H_A;
    uint16_t hl = wram->w3_d000[0] | (wram->w3_d001[0] << 8);
    // DEC_HL;
    --hl;
    // LD_A_L;
    // LD_addr_A(w3_d000);
    wram->w3_d000[0] = LOW(hl);
    // LD_A_H;
    // LD_addr_A(w3_d000 + 1);
    wram->w3_d001[0] = HIGH(hl);
    // LD_A_addr(wcf64);
    // LD_L_A;
    // LD_A_addr(wcf65);
    // LD_H_A;
    hl = wram->wcf64 | (wram->wcf65 << 8);
    // INC_HL;
    ++hl;
    // LD_A_L;
    // LD_addr_A(wcf64);
    wram->wcf64 = LOW(hl);
    // LD_A_H;
    // LD_addr_A(wcf65);
    wram->wcf65 = HIGH(hl);
    // LD_A(0x10);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = 0x10;
    // RET;

// pushc
// setcharmap ascii
}

#if defined(_CRYSTAL_JP)
const char XGameCode[] = "CGB-BXTJ-00""\0";
#else
const char XGameCode[] = "CGB-BXTE-00""\0";
#endif

//  //  unreferenced
const char XGameResult[] = "pokemon_crystal";

// popc

void Function119b0d(void){
    // LD_A(0x8);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0x8;
    // CALL(aBattleTowerRoomMenu2);
    BattleTowerRoomMenu2();
    // LD_A_addr(w3_d090);
    // CP_A(0x1);
    // IF_Z goto asm_119b23;
    if(wram->w3_d090[0] != 0x1) {
        // LD_A(0x19);
        // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
        wram->wBattleTowerRoomMenuJumptableIndex = 0x19;
        // JR(mFunction119b3b);
        return Function119b3b();
    }

// asm_119b23:
    // LD_A(0x10);
    // LD_addr_A(wcd89);
    wram->wcd89 = 0x10;
    // LD_A_addr(w3_d090 + 1);
    // LD_L_A;
    // LD_A_addr(w3_d090 + 2);
    // LD_H_A;
    // LD_DE(w3_d100);
    // LD_BC(0x0700);
    mobile_api_data_s data = {.bc = 0x0700, .de = wram->w3_d100, .l = wram->w3_d090[1], .h = wram->w3_d090[2]};
    // LD_A(MOBILEAPI_12);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_12, &data);
}

void Function119b3b(void){
    // LD_A_addr(w3_d090 + 1);
    // LD_L_A;
    // LD_A_addr(w3_d090 + 2);
    // LD_H_A;
    uint16_t hl = wram->w3_d090[1] | (wram->w3_d090[2] << 8);
    // JR(masm_119b4d);
    return asm_119b4d(hl);
}

void Function119b45(void){
    // LD_A_addr(wcf64);
    // LD_L_A;
    // LD_A_addr(wcf65);
    // LD_H_A;
    uint16_t hl = wram->wcf64 | (wram->wcf65 << 8);

    return asm_119b4d(hl);
}

void asm_119b4d(uint16_t hl){
    // LD_A(MOBILEAPI_13);
    // JP(mFunction119e2b);
    Function119e2b(MOBILEAPI_13, &(mobile_api_data_s){.l = LOW(hl), .h = HIGH(hl)});
}

void Function119b52(void){
    // LD_A_addr(w3_d090);
    // CP_A(0x1);
    // IF_NZ goto asm_119b66;
    if(wram->w3_d090[0] == 0) {
        // LD_A(BANK(s5_a800));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(as5_a800));
        // LD_A(0x4);
        // LD_addr_A(s5_a800);
        gb_write(s5_a800, 0x4);
        // CALL(aCloseSRAM);
        CloseSRAM();
    }

// asm_119b66:
    mobile_api_data_s data = {0};
    // LD_A(MOBILEAPI_0E);
    // JP(mFunction119e2b);
    return Function119e2b(MOBILEAPI_0E, &data);
}

static u8_flag_s Function119b6b_decodeBase64Character(char a){
    // CP_A('+');  // "+"
    // IF_C goto asm_119c68;
    // IF_Z goto asm_119c80;
    if(a == '+') return u8_flag(0x3e, false);
    // CP_A('/');  // "/"
    // IF_C goto asm_119c68;
    // IF_Z goto asm_119c84;
    if(a == '/') return u8_flag(0x3f, false);
    // CP_A('0');  // "0"
    // IF_C goto asm_119c68;
    // CP_A('9' + 1);  // "9" + 1
    // IF_C goto asm_119c88;
    if(a >= '0' && a <= '9') return u8_flag(a + 4, false); 
    // CP_A('=');  // "="
    // IF_C goto asm_119c68;
    // IF_Z goto asm_119c8c;
    if(a == '=') return u8_flag(0x0, false);
    // CP_A('A');  // "A"
    // IF_C goto asm_119c68;
    // CP_A('Z' + 1);  // "Z" + 1
    // IF_C goto asm_119c8f;
    if(a >= 'A' && a <= 'Z') return u8_flag(a - 0x41, false);
    // CP_A('a');  // "a"
    // IF_C goto asm_119c68;
    // CP_A('z' + 1);  // "z" + 1
    // IF_C goto asm_119c93;
    if(a >= 'a' && a <= 'z') return u8_flag(a - 0x47, false);
    // popc

// asm_119c68:
    // LD_A(0x19);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = 0x19;
    // LD_A(BANK(s5_a800));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_a800));
    // LD_A(0x1);
    // LD_addr_A(s5_a800);
    gb_write(s5_a800, 0x1);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // XOR_A_A;
    // LD_addr_A(w3_d090);
    wram->w3_d090[0] = 0;
    // SCF;
    // RET;
    return u8_flag(0, true);

// asm_119c80:
    // LD_A(0x3e);
    // AND_A_A;
    // RET;

// asm_119c84:
    // LD_A(0x3f);
    // AND_A_A;
    // RET;

// asm_119c88:
    // ADD_A(0x4);
    // AND_A_A;
    // RET;

// asm_119c8c:
    // XOR_A_A;
    // AND_A_A;
    // RET;

// asm_119c8f:
    // SUB_A(0x41);
    // AND_A_A;
    // RET;

// asm_119c93:
    // SUB_A(0x47);
    // AND_A_A;
    // RET;
}

void Function119b6b(void){
    // LD_A_addr(w3_d090);
    // CP_A(0x1);
    // IF_Z goto asm_119b75;
    if(wram->w3_d090[0] == 0x1) {
        // JP(mBattleTowerRoomMenu_IncrementJumptable);
        return BattleTowerRoomMenu_IncrementJumptable();
    }

// asm_119b75:
    // LD_A_addr(w3_d100);
    // LD_B_A;
    // LD_A_addr(w3_d100 + 1);
    // OR_A_B;
    // IF_Z goto asm_119be3;
    if((wram->w3_d100[0] | wram->w3_d100[1]) != 0) {
        // LD_HL(w3_d800);
        uint16_t hl = w3_d800;
        // LD_DE(w3_d100 + 2);
        char* de = (char*)wram->w3_d100 + 2;

        char a;
        do {
        // asm_119b85:
            // LD_A_de;
            // INC_DE;
            a = *(de++);
            // CP_A(0xd);
            // IF_NZ goto asm_119b85;
            if(a != '\r')
                continue;
            // INC_DE;
            de++;
            // LD_A_de;
            a = *de;
            // CP_A(0xd);
            // IF_NZ goto asm_119b85;
        } while(a != '\r');
        // INC_DE;
        // INC_DE;
        de += 2;

        do {
        asm_119b93:
            // LD_A_de;
            // INC_DE;
            a = *(de++);
            // CP_A(0xd);
            // IF_Z goto asm_119bfa;
            if(a == '\r') {
            // asm_119bfa:
                // INC_DE;
                de++;
                // LD_A_de;
                a = *de;
                // CP_A(0xd);
                // IF_NZ goto asm_119b93;
                if(a != '\r')
                    goto asm_119b93;
                // LD_A_L;
                // CP_A(LOW(w3_d869));
                // IF_NZ goto asm_119be3;
                // LD_A_H;
                // CP_A(HIGH(w3_d869));
                // IF_NZ goto asm_119be3;
                if(hl != w3_d869)
                    break;
                // LD_A(BANK(s5_b090));  // aka BANK(s5_b091) and BANK(s5_b023)
                // CALL(aOpenSRAM);
                OpenSRAM(MBANK(as5_b090));
                // LD_A_addr(wcf64);
                // LD_addr_A(s5_b090);
                gb_write(s5_b090, wram->wcf64);
                // LD_A_addr(wcf65);
                // LD_addr_A(s5_b091);
                gb_write(s5_b091, wram->wcf65);
                // LD_HL(w3_d800);
                // LD_DE(s5_b023);
                // LD_BC(105);
                // CALL(aCopyBytes);
                CopyBytes(GBToRAMAddr(s5_b023), wram->w3_d800, 105);
                // LD_A(0x3);
                // LD_addr_A(s5_a800);
                gb_write(s5_a800, 0x3);
                // CALL(aCloseSRAM);
                CloseSRAM();
                // LD_HL(w3_d800);
                // LD_DE(wc608);
                // LD_BC(105);
                // CALL(aCopyBytes);
                CopyBytes(wram->wc608, wram->w3_d800, 105);
                // JP(mBattleTowerRoomMenu_IncrementJumptable);
                return BattleTowerRoomMenu_IncrementJumptable();
            }
            // CALL(aFunction119b6b_decodeBase64Character);
            u8_flag_s res = Function119b6b_decodeBase64Character(a);
            // RET_C ;
            if(res.flag)
                return;
            // LD_hli_A;
            wram->w3_d800[hl + 0 - w3_d800] = res.a;
            // LD_A_de;
            // INC_DE;
            a = *(de++);
            // CALL(aFunction119b6b_decodeBase64Character);
            res = Function119b6b_decodeBase64Character(a);
            // RET_C ;
            if(res.flag)
                return;
            // LD_hli_A;
            wram->w3_d800[hl + 1 - w3_d800] = res.a;
            // LD_A_de;
            // INC_DE;
            a = *(de++);
            // CALL(aFunction119b6b_decodeBase64Character);
            res = Function119b6b_decodeBase64Character(a);
            // RET_C ;
            if(res.flag)
                return;
            // LD_hli_A;
            wram->w3_d800[hl + 2 - w3_d800] = res.a;
            // LD_A_de;
            // INC_DE;
            a = *(de++);
            // CALL(aFunction119b6b_decodeBase64Character);
            res = Function119b6b_decodeBase64Character(a);
            // RET_C ;
            if(res.flag)
                return;
            // LD_hl_A;
            wram->w3_d800[hl + 3 - w3_d800] = res.a;
            // PUSH_DE;
            uint8_t* hl2 = wram->w3_d800 + (hl - w3_d800);
            // LD_D_hl;
            // DEC_HL;
            // LD_C_hl;
            // DEC_HL;
            uint8_t c = hl2[2];
            // LD_B_hl;
            // DEC_HL;
            uint8_t b = hl2[1];
            // LD_A_hl;
            uint8_t a2 = hl2[0];
            // SLA_B;
            // SLA_B;
            // SLA_B;
            // RLA;
            // SLA_B;
            // RLA;
            uint16_t b2 = (b << 4) | ((a2 << 2) << 4);
            // LD_hli_A;
            hl2[0] = HIGH(b2);
            // LD_hl_B;
            hl2[1] = LOW(b2);
            // INC_HL;
            // RRC_C;
            // RRC_C;
            // LD_hl_C;
            hl2[2] = c >> 2;
            // DEC_HL;
            // LD_A(0xf);
            // AND_A_C;
            // OR_A_hl;
            // LD_hli_A;
            hl2[1] = (c & 0xf) | hl2[1];
            // LD_A_hli;
            // AND_A(0xc0);
            // OR_A_hl;
            // DEC_HL;
            // LD_hld_A;
            hl2[2] = ((hl2[2] & 0xc0) | hl2[3]);
            // DEC_HL;
            // POP_DE;
            // INC_HL;
            // INC_HL;
            // INC_HL;
            hl += 3;
            // LD_A_H;
            // CP_A(0xe0);
            // IF_C goto asm_119b93;
        } while(hl < 0xe000);
    }

asm_119be3:
    // LD_A(0x19);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = 0x19;
    // LD_A(BANK(s5_a800));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_a800));
    // LD_A(0x1);
    // LD_addr_A(s5_a800);
    gb_write(s5_a800, 0x1);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // XOR_A_A;
    // LD_addr_A(w3_d090);
    wram->w3_d090[0] = 0x0;
    // RET;
    return;

// pushc
// setcharmap ascii
}

void BattleTowerRoomMenu_Mobile_2f(void){
    // ld hl, Text_BattleRoomVisitLimit;$6081
    // call BattleTowerRoomMenu_SetMessage;Call_046_6ef1
    BattleTowerRoomMenu_SetMessage(Text_BattleRoomVisitLimit);
    // call BattleTowerRoomMenu_IncrementJumptable;Call_046_635f
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_Mobile_30();
}

void BattleTowerRoomMenu_Mobile_30(void){
    // ld a, [$c31a];$c340
    // and a
    // ret nz
    if(wram->wc31a != 0)
        return;

    // ld a, $80
    // ld [wcd50], a;$cd44
    wram->wcd50 = 0x80;
    // call BattleTowerRoomMenu_IncrementJumptable;Call_046_635f
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_Mobile_31();
}

void BattleTowerRoomMenu_Mobile_31(void){
    // ld hl, wcd50;$cd44
    // dec [hl]
    // ret nz
    if(--wram->wcd50 != 0)
        return;

    // ld a, $15
    // ld [wcf66], a;$cf5a
    wram->wcf66 = 0x15;
    // ret
}

void BattleTowerRoomMenu_UberRestrictionMessage(void){
    // LD_HL(mText_UberRestriction);
    // CALL(aBattleTowerRoomMenu_SetMessage);
    BattleTowerRoomMenu_SetMessage(Text_UberRestriction);
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();
    // JR(mBattleTowerRoomMenu_WaitForMessage);
    return BattleTowerRoomMenu_WaitForMessage();

}

void BattleTowerRoomMenu_PartyMonTopsThisLevelMessage(void){
    // LD_HL(mText_PartyMonTopsThisLevel);
    // CALL(aBattleTowerRoomMenu_SetMessage);
    BattleTowerRoomMenu_SetMessage(Text_PartyMonTopsThisLevel);
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_WaitForMessage();
}

void BattleTowerRoomMenu_WaitForMessage(void){
    // LD_A_addr(wc31a);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wc31a)
        return;
    // LD_A(0x80);
    // LD_addr_A(wcd50);
    wram->wcd50 = 0x80;
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_DelayRestartMenu();
}

// Loops while (--[wcd50] != 0),
//   to create some sort of "delay" after the message is written on the screen,
//   before starting the menu again.
void BattleTowerRoomMenu_DelayRestartMenu(void){
    // LD_HL(wcd50);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcd50 != 0)
        return;
    // LD_A(0x0);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = 0x0;
    // RET;
}

void BattleTowerRoomMenu_QuitMessage(void){
    PEEK("");
    // LD_A_addr(wcd38);
    // AND_A_A;
    // IF_Z goto asm_119cd1;
    if(wram->wcd38 == 0){
    // asm_119cd1:
        // LD_HL(mText_CancelBattleRoomChallenge);
        // goto asm_119cd9;
        BattleTowerRoomMenu_SetMessage(Text_CancelBattleRoomChallenge);
    }
    // DEC_A;
    // IF_Z goto asm_119cd6;
    else if(wram->wcd38 == 1){
    // asm_119cd6:
        // LD_HL(mText_ExitGymLeaderHonorRoll);
        BattleTowerRoomMenu_SetMessage(Text_ExitGymLeaderHonorRoll);
    }
    else {
        // LD_HL(mText_QuitReadingNews);
        // goto asm_119cd9;
        BattleTowerRoomMenu_SetMessage(Text_QuitReadingNews);
    }

// asm_119cd9:
    // CALL(aBattleTowerRoomMenu_SetMessage);
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_PlaceYesNoMenu();
}

void BattleTowerRoomMenu_PlaceYesNoMenu(void){
    PEEK("");
    // LD_A_addr(wc31a);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wc31a != 0)
        return;
    // LD_A(0xf);
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex = 0xf;
    // CALL(aBattleTowerRoomMenu_IncrementJumptable);
    BattleTowerRoomMenu_IncrementJumptable();

    return BattleTowerRoomMenu_UpdateYesNoMenu();
}

void BattleTowerRoomMenu_UpdateYesNoMenu(void){
// Only ever called when [wBattleTowerRoomMenu2JumptableIndex] is $10
    PEEK("");
    // CALL(aBattleTowerRoomMenu2);
    // RET_C ;
    if(BattleTowerRoomMenu2())
        return;
    // LD_A_addr(wMobileInactivityTimerFrames);
    // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    wram->wBattleTowerRoomMenuJumptableIndex = wram->wMobileInactivityTimerFrames;
    // RET;
}

const struct MenuHeader MenuHeader_119cf7 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(12, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = NULL,
    .defaultOption = 0,  // default option
};

const struct MenuHeader MenuData_119cff = {
//  //  unreferenced
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(12, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = NULL,
    .defaultOption = 0,  // default option
};

const char String_119d07[] = "   ▼";
const char String_119d07_2[] = " ▼";

const char* Strings_L10ToL100[] = {
    " L:10 ",
    " L:20 ",
    " L:30 ",
    " L:40 ",
    " L:50 ",
    " L:60 ",
    " L:70 ",
    " L:80 ",
    " L:90 ",
    " L:100",
    "CANCEL",
};

const char* Strings_Ll0ToL40[] = {
    " L:10 ",
    " L:20 ",
    " L:30 ",
    " L:40 ",
    "CANCEL",
};

const char BattleTowerCancelString[] = "CANCEL@";
//  //  unreferenced

bool BattleTower_LevelCheck(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wPartyMons));
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wcd4f);
    // LD_C(10);
    // CALL(aSimpleMultiply);
    // LD_HL(wcd50);
    // LD_hl_A;
    wram->wcd50 = wram->wcd4f * 10;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_DE(wPartyMon1Level);
    struct PartyMon* de = wram->wPartyMon;
    // LD_A_addr(wPartyCount);
    uint8_t a = wram->wPartyCount;

    do {
    // party_loop:
        // PUSH_AF;
        // LD_A_de;
        uint8_t level = de->mon.level;
        // PUSH_HL;
        // PUSH_DE;
        // POP_HL;
        // ADD_HL_BC;
        // PUSH_HL;
        // POP_DE;
        de++;
        // POP_HL;
        // CP_A_hl;
        // IF_Z goto equal;
        // IF_NC goto exceeds;
        if(level > wram->wcd50){
        // exceeds:
            // POP_AF;
            // LD_A(0x4);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = 0x4;
            // POP_AF;
            // LDH_addr_A(rSVBK);
            // SCF;
            // RET;
            return true;
        }

    // equal:
        // POP_AF;
        // DEC_A;
        // IF_NZ goto party_loop;
    } while(--a != 0);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // AND_A_A;
    // RET;
    return false;
}

bool BattleTower_UbersCheck(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A_addr(wcd4f);
    // CP_A(70 / 10);
    // IF_NC goto level_70_or_more;
    if(wram->wcd4f >= 70 / 10) {
        // goto level_70_or_more;
        return false;
    }
    // LD_A(BANK(wPartyMons));
    // LDH_addr_A(rSVBK);
    // LD_HL(wPartyMon1Level);
    struct PartyMon* hl = wram->wPartyMon;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_DE(wPartySpecies);
    species_t* de = wram->wPartySpecies;
    // LD_A_addr(wPartyCount);
    uint8_t a = wram->wPartyCount;

    do {
    // loop:
        // PUSH_AF;
        // LD_A_de;
        species_t sp = *de;
        // CP_A(MEWTWO);
        // IF_Z goto uber;
        // CP_A(MEW);
        // IF_Z goto uber;
        if(sp != MEWTWO && sp != MEW){
            // CP_A(LUGIA);
            // IF_C goto next;
            if(sp < LUGIA)
                continue;
            // CP_A(NUM_POKEMON + 1);
            // IF_NC goto next;
            if(sp >= NUM_POKEMON + 1)
                continue;
        }

    // uber:
        // LD_A_hl;
        // CP_A(70);
        // IF_C goto uber_under_70;
        if(hl->mon.level < 70){
        // uber_under_70:
            // POP_AF;
            // LD_A_de;
            // LD_addr_A(wNamedObjectIndex);
            // CALL(aGetPokemonName);
            // LD_HL(wStringBuffer1);
            // LD_DE(wcd49);
            // LD_BC(MON_NAME_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(&wram->wcd49, GetPokemonName(*de), MON_NAME_LENGTH);
            // LD_A(0xa);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = 0xa;
            // POP_AF;
            // LDH_addr_A(rSVBK);
            // SCF;
            // RET;
            return true;
        }

    // next:
        // ADD_HL_BC;
        // INC_DE;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(hl++, de++, --a != 0);

// level_70_or_more:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // AND_A_A;
    // RET;
    return false;
}

// CallMobileAPIAndIncrementBattleTowerRoomMenuJumptable
void Function119e2b(uint8_t a, mobile_api_data_s* data){
    // CALL(aMobileAPI);
    MobileAPI(a, data);

    return BattleTowerRoomMenu_IncrementJumptable();
}

void BattleTowerRoomMenu_IncrementJumptable(void){
    // LD_HL(wBattleTowerRoomMenuJumptableIndex);
    // INC_hl;
    wram->wBattleTowerRoomMenuJumptableIndex++;
    // RET;
}

// pushc
// setcharmap ascii
const char XGameCodePrefix[] = "X-Game-code:\n";
const char XGameResultPrefix[] = "X-Game-result:\n";

u8_flag_s Function119e4f(const char* de, uint8_t c){
    // PUSH_BC;
    // LD_HL(w3_d100);
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint16_t bc = wram->w3_d100[0] | (wram->w3_d100[1] << 8);
    const char* hl = (const char*)(wram->w3_d100 + 2);

    do {
    // loop:
        // LD_A_de;
        char a = *de;
        // CP_A_hl;
        // IF_Z goto found_equality;
        if(a == *hl) {
        // found_equality:
            // PUSH_DE;
            const char* de2 = de;
        
            do {
            // loop2:
                // LD_A_de;
                // INC_DE;
                char a = *(de2++);
                // CP_A('\n');  // "\n"
                // IF_Z goto newline;
                if(a == '\n') {
                // newline:
                    // POP_DE;
                    // POP_BC;
                    // INC_HL;
                    hl++;
                    // LD_DE(w3_d880);
                    char* de3 = (char*)(wram->w3_d880);
                
                    do {
                    // loop3:
                        // LD_A_hli;
                        char a = *(hl++);
                        // LD_de_A;
                        // INC_DE;
                        *(de3++) = a;
                        // CP_A(0xd);
                        // IF_Z goto finish;
                        if(a == '\r') {
                        // finish:
                            // AND_A_A;
                            // RET;       
                            return u8_flag(c, false);         
                        }
                        // DEC_C;
                        // IF_NZ goto loop3;
                    } while(--c != 0);
                    // SCF;
                    // RET;
                    return u8_flag(0, true);
                }
                // CP_A_hl;
                // IF_NZ goto unequal;
                if(a != *hl)
                    goto next;
                // INC_HL;
                hl++;
                // DEC_BC;
                // LD_A_B;
                // OR_A_C;
                // IF_NZ goto loop2;
            } while(--bc != 0);
            // POP_DE;
            goto return_carry;
        
        // unequal:
            // POP_DE;
            // goto next;
        }

    next:
        // INC_HL;
        hl++;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);

return_carry:
    // POP_BC;
    // SCF;
    // RET;
    return u8_flag(c, true);
}

uint8_t Function119e8e(uint8_t a){
    // CP_A(0x60);
    // IF_C goto less_than_0x60;
    if(a < 0x60) {
    // less_than_0x60:
        // SUB_A(0x30);
        // RET;
        return a - 0x30;
    }
    else {
        // SUB_A(0x57);
        // RET;
        return a - 0x57;
    }
}

void Function119e98(uint8_t* hl, const uint8_t* bc){
    // LD_A(0x2);
    uint8_t a = 0x2;

    do {
    // loop:
        // PUSH_AF;
        // LD_A_bc;
        // DEC_BC;
        // CALL(aFunction119e8e);
        uint8_t b = Function119e8e(*bc);
        --bc;
        // OR_A_hl;
        // LD_hl_A;
        *hl |= b;
        // LD_A_bc;
        // DEC_BC;
        // CALL(aFunction119e8e);
        b = Function119e8e(*bc);
        --bc;
        // RLCA;
        // RLCA;
        // RLCA;
        // RLCA;
        b = (b << 4) | (b >> 4);
        // OR_A_hl;
        // LD_hl_A;
        *hl |= b;
        // INC_HL;
        hl++;
        // POP_AF;
        // DEC_A;
        // AND_A_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // RET;
}

uint8_t* Function119eb4(uint8_t* hl){
    // XOR_A_A;
    // LD_addr_A(wc3cc);
    wram->wc3cc[0] = 0x0;
    // LD_DE(wc3ac);
    uint8_t* de = wram->wc3ac;
    uint8_t a;

    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        a = *(de++);
        // LD_hli_A;
        *(hl++) = a;
        // AND_A_A;
        // IF_NZ goto loop;
    } while(a != 0);
    // RET;
    return hl;
}

uint8_t* Function119ec2(uint8_t* hl){
    const char* set_password = Mobile_GetServerLoginPassword(8);
    if(set_password != NULL) {
        printf("Using password from server.json\n");
        for(const char* str = set_password; *str != 0; str++) {
            *(hl++) = *str;
        }
        *(hl++) = 0;
        return hl;
    }

    printf("Using stored password in SRAM\n");
// End
    // LD_A(BANK(sMobileLoginPassword));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMobileLoginPassword));
    // XOR_A_A;
    // LD_addr_A(sMobileLoginPassword + MOBILE_LOGIN_PASSWORD_LENGTH);
    gb_write(sMobileLoginPassword + MOBILE_LOGIN_PASSWORD_LENGTH, 0x0);
    // LD_DE(sMobileLoginPassword + 1);
    uint8_t* de = GBToRAMAddr(sMobileLoginPassword + 1);
    uint8_t a;

    do {
    // loop:
        // LD_A_de;
        a = *(de++);
        // INC_DE;
        // LD_hli_A;
        *(hl++) = a;
        // AND_A_A;
        // IF_NZ goto loop;
    } while(a != 0);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
    return hl;
}

bool BattleTowerRoomMenu2(void){
    // LDH_A_addr(rSVBK);
    // LD_addr_A(wcd8c);
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);

    bool result = false;
    // CALL(aBattleTowerRoomMenu2_RunJumptable);
    printf("Battle Tower Room Menu 2 (0x%02x)", wram->wBattleTowerRoomMenu2JumptableIndex);
    switch(wram->wBattleTowerRoomMenu2JumptableIndex){
    // RunJumptable:
        //jumptable ['.Jumptable', 'wBattleTowerRoomMenu2JumptableIndex']

    // Jumptable:
        case 0x00: result = Function119f3f(); break; //dw ['Function119f3f'];
        case 0x01: result = Function119f45(); break; //dw ['Function119f45'];
        case 0x02: result = Function119f56(); break; //dw ['Function119f56'];
        case 0x03: result = Function119f76(); break; //dw ['Function119f76'];
        case 0x04: result = Function119f98(); break; //dw ['Function119f98'];
        case 0x05: result = Function11a113(); break; //dw ['Function11a113'];
        case 0x06: result = Function11a129(); break; //dw ['Function11a129'];
        case 0x07: result = Function11a131(); break; //dw ['Function11a131'];
        case 0x08: result = Function11a13d(); break; //dw ['Function11a13d'];
        case 0x09: result = Function11a14b(); break; //dw ['Function11a14b'];
        case 0x0a: result = Function11a16d(); break; //dw ['Function11a16d'];
        case 0x0b: result = Function11a192(); break; //dw ['Function11a192'];
        case 0x0c: result = Function11a2e6(); break; //dw ['Function11a2e6'];
        case 0x0d: result = Function11a302(); break; //dw ['Function11a302'];
        case 0x0e: result = Function11a33a(); break; //dw ['Function11a33a'];
        case 0x0f: result = BattleTowerRoomMenu2_PlaceYesNoMenu(); break; //dw ['BattleTowerRoomMenu2_PlaceYesNoMenu'];
        case 0x10: result = BattleTowerRoomMenu2_UpdateYesNoMenu(); break; //dw ['BattleTowerRoomMenu2_UpdateYesNoMenu'];
        case 0x11: result = Function11a357(); break; //dw ['Function11a357'];
        case 0x12: result = Function11a36b(); break; //dw ['Function11a36b'];
        case 0x13: result = Function11a38d(); break; //dw ['Function11a38d'];
        case 0x14: result = Function11a3c5(); break; //dw ['Function11a3c5'];
        case 0x15: result = Function11a3d9(); break; //dw ['Function11a3d9'];
        case 0x16: result = Function11a3f9(); break; //dw ['Function11a3f9'];
        case 0x17: result = Function11a41b(); break; //dw ['Function11a41b'];
        case 0x18: result = Function11a452(); break; //dw ['Function11a452'];
        case 0x19: result = Function11a47a(); break; //dw ['Function11a47a'];
        case 0x1a: result = Function11a488(); break; //dw ['Function11a488'];
        case 0x1b: result = Function11a49e(); break; //dw ['Function11a49e'];
        case 0x1c: result = Function11a4db(); break; //dw ['Function11a4db'];
        case 0x1d: result = Function11a4e8(); break; //dw ['Function11a4e8'];
        case 0x1e: result = Function11a4fe(); break; //dw ['Function11a4fe'];
        case 0x1f: result = Function11a466(); break; //dw ['Function11a466'];
        case 0x20: result = Function11a47a(); break; //dw ['Function11a47a'];
    }

    // LD_A_addr(wcd8c);
    // LDH_addr_A(rSVBK);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
    return result;
}

bool Function119f3f(void){
    // CALL(aFunction11a5b9);
    Function11a5b9();
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();

}

bool Function119f45(void){
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a661);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a661), coord(4, 2, wram->wTilemap)); // "Dialing the MOBILE CENTER..."
    // LD_A(0x80);
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x80;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();

}

bool Function119f56(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_119f62;
    // DEC_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    // SCF;
    // RET;
    if(wram->wMobileInactivityTimerMinutes == 0) {
    // asm_119f62:
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a6aa);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a6aa), coord(4, 2, wram->wTilemap)); // Charges will apply
        // LD_A(0x80);
        // LD_addr_A(wMobileInactivityTimerMinutes);
        wram->wMobileInactivityTimerMinutes = 0x80;
        // JP(mBattleTowerRoomMenu2_IncrementJumptable);
        return BattleTowerRoomMenu2_IncrementJumptable();
    }

    --wram->wMobileInactivityTimerMinutes;
    return true;
}

bool Function119f76(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_119f82;
    if(wram->wMobileInactivityTimerMinutes == 0) {
    // asm_119f82:
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a679);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a679), coord(4, 2, wram->wTilemap));
        // CALL(aFunction11a5f5);
        Function11a5f5();
        // XOR_A_A;
        // LD_addr_A(wMobileInactivityTimerMinutes);
        // JP(mBattleTowerRoomMenu2_IncrementJumptable);
        return BattleTowerRoomMenu2_IncrementJumptable();
    }
    // DEC_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes--;
    // SCF;
    // RET;
    return true;
}

bool Function119f98(void){
    // CALL(aFunction11a536);
    // RET_C ;
    if(Function11a536())
        return true;
    // CALL(aPlayClickSFX);
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_NZ goto asm_119fef;
    if(wram->wMobileInactivityTimerMinutes != 0) {
    // asm_119fef:
        // CALL(aExitMenu);
        ExitMenu();
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_A_addr(wMobileInactivityTimerSeconds);
        // LD_addr_A(wcf66);
        wram->wcf66 = wram->wMobileInactivityTimerSeconds;
        // FARCALL(aFunction115dc3);
        Function115dc3();
        // LD_A(0xa);
        // LD_addr_A(wMobileErrorCodeBuffer);
        wram->wMobileErrorCodeBuffer[0] = 0xa;
        // SCF;
        // RET;
        return true;
    }
    // CALL(aExitMenu);
    ExitMenu();
    // CALL(aFunction11a63c);
    Function11a63c();
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x0;
    // CALL(aFunction11a00e);
    Function11a00e();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_Z goto asm_119fd4;
    if(wram->wScriptVar != 0) {
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // FARCALL(aFunction115dc3);
        Function115dc3();
        // LD_A_addr(wcd33);
        // LD_addr_A(wcf66);
        wram->wcf66 = wram->wcd33;
        // LD_A(0xa);
        // LD_addr_A(wMobileErrorCodeBuffer);
        wram->wMobileErrorCodeBuffer[0] = 0xa;
        // SCF;
        // RET;
        return true;
    }

// asm_119fd4:
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a692);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a692), coord(4, 2, wram->wTilemap));
    // LD_A(0x1);
    // LD_addr_A(wc30d);
    wram->wc30d = 0x1;
    // LD_A(0x1);
    // LD_addr_A(wc314);
    wram->wc314[0] = 0x1;
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // AND_A_A;
    // RET;
    return false;
}

void Function11a00e(void){
// If we have a password set in the server.json file, we don't
// need to enter one.
    const char* set_password = Mobile_GetServerLoginPassword(8);
    if(set_password != NULL) {
        return;
    }
// If we have a saved password in SRAM, we don't need to
// enter one.
    // LD_A(BANK(sMobileLoginPassword));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMobileLoginPassword));
    // LD_A_addr(sMobileLoginPassword);
    // AND_A_A;
    // IF_Z goto asm_11a02a;
    if(gb_read(sMobileLoginPassword) != 0) {
        // LD_A_addr(sMobileLoginPassword + 1);
        // CALL(aCloseSRAM);
        // AND_A_A;
        // RET_NZ ;
        if(gb_read(sMobileLoginPassword + 1) != 0) {
            CloseSRAM();
            return;
        }
        // LD_A(BANK(sMobileLoginPassword));
        // CALL(aOpenSRAM);
        // XOR_A_A;
        // LD_addr_A(sMobileLoginPassword);
        gb_write(sMobileLoginPassword, 0x0);
    }

// asm_11a02a:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A_addr(wBGMapPalBuffer);
    // AND_A_A;
    // IF_Z goto asm_11a039;
    if(wram->wcd48 == 0) {
    // asm_11a039:
        // LD_A(BANK(w3_d800));
        // LDH_addr_A(rSVBK);
        // LD_HL(wc608);
        // LD_DE(w3_d800);
        // LD_BC(246);
        // CALL(aCopyBytes);
        CopyBytes(wram->w3_d800, wram->wc608, 246);
        // LD_A(0x1);
        // LDH_addr_A(rSVBK);
        // CALL(aFadeToMenu);
        FadeToMenu();
        // FARCALL(aFunction11765d);
        Function11765d();
        // CALL(aFunction11a9ce);
        Function11a9ce();
        // LD_A(BANK(w3_d800));
        // LDH_addr_A(rSVBK);
        // LD_HL(w3_d800);
        // LD_DE(wc608);
        // LD_BC(246);
        // CALL(aCopyBytes);
        CopyBytes(wram->wc608, wram->w3_d800, 246);
        // LD_A(0x1);
        // LDH_addr_A(rSVBK);
        // FARCALL(aFunction115d99);
        Function115d99();
        // LD_C(0x0);
        // FARCALL(aFunction115e18);
        Function115e18(0x0);
        // LD_A(0x1);
        // LD_addr_A(wc305);
        wram->wc305 = 0x1;
        // RET;
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11a081;
    else if(wram->wcd48 == 1) {
    // asm_11a081:
        // XOR_A_A;
        // LD_addr_A(wMenuBorderLeftCoord);
        wram->wMenuBorderLeftCoord = 0;
        // LD_addr_A(wMenuBorderTopCoord);
        wram->wMenuBorderTopCoord = 0;
        // LD_A(0x13);
        // LD_addr_A(wMenuBorderRightCoord);
        wram->wMenuBorderRightCoord = 0x13;
        // LD_A(0x5);
        // LD_addr_A(wMenuBorderBottomCoord);
        wram->wMenuBorderBottomCoord = 0x5;
        // CALL(aPushWindow);
        PushWindow();
        // FARCALL(aFunction11765d);
        Function11765d();
        // FARCALL(aFunction117ab4);
        Function117ab4();
        // FARCALL(aStubbed_Function106462);
        // FARCALL(aFunction106464);
        Function106464();
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // FARCALL(aFunction115d99);
        Function115d99();
        // LD_C(0x0);
        // FARCALL(aFunction115e18);
        Function115e18(0x0);
        // LD_A(0x1);
        // LD_addr_A(wc305);
        wram->wc305 = 0x1;
        // RET;
        return;
    }
    // JP(mFunction11a0ca);
    return Function11a0ca();
}

void Function11a0ca(void){
    // XOR_A_A;
    // LD_addr_A(wMenuBorderLeftCoord);
    wram->wMenuBorderLeftCoord = 0;
    // LD_addr_A(wMenuBorderTopCoord);
    wram->wMenuBorderTopCoord = 0;
    // LD_A(0x13);
    // LD_addr_A(wMenuBorderRightCoord);
    wram->wMenuBorderRightCoord = 0x13;
    // LD_A(0x11);
    // LD_addr_A(wMenuBorderBottomCoord);
    wram->wMenuBorderBottomCoord = 0x11;
    // CALL(aPushWindow);
    PushWindow();
    // FARCALL(aFunction11765d);
    Function11765d();
    // FARCALL(aFunction17d3f6);
    Function17d3f6();
    // FARCALL(aStubbed_Function106462);
    // FARCALL(aFunction106464);
    Function106464();
    // CALL(aExitMenu);
    ExitMenu();
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // FARCALL(aFunction115d99);
    Function115d99();
    // LD_C(0x0);
    // FARCALL(aFunction115e18);
    Function115e18(0x0);
    // LD_A(0x1);
    // LD_addr_A(wc305);
    wram->wc305 = 0x1;
    // RET;
}

bool Function11a113(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // LD_C(0x1);
    // FARCALL(aFunction115e18);
    Function115e18(0x1);
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a6c8);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a6c8), coord(4, 2, wram->wTilemap));
    // AND_A_A;
    // RET;
    return false;
}

bool Function11a129(void){
    // LD_A(0x80);
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x80;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a131(void){
    // LD_HL(wMobileInactivityTimerMinutes);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wMobileInactivityTimerMinutes != 0)
        return false;
    // LD_A_addr(wBattleTowerRoomMenu2JumptableIndex);
    // INC_A;
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex++;

    return Function11a13d();
}

bool Function11a13d(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a6d2);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a6d2), coord(4, 2, wram->wTilemap));
    // AND_A_A;
    // RET;
    return false;
}

bool Function11a14b(void){
    // LD_HL(wcd85);
    // LD_A_hl;
    // CP_A(0xf3);
    // IF_NZ goto asm_11a155;
    if(wram->wcd85[0] != 0xf3) {
    // asm_11a155:
        // CALL(aFunction11a1d6);
        // RET_C ;
        if(Function11a1d6())
            return true;
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a6f1);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a6f1), coord(4, 2, wram->wTilemap));
        // LD_A(0x80);
        // LD_addr_A(wMobileInactivityTimerMinutes);
        wram->wMobileInactivityTimerMinutes = 0x80;
        // JP(mBattleTowerRoomMenu2_IncrementJumptable);
        return BattleTowerRoomMenu2_IncrementJumptable();
    }
    // AND_A_A;
    // RET;
    return false;
}

bool Function11a16d(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_11a179;
    if(wram->wMobileInactivityTimerMinutes == 0) {
    // asm_11a179:
        // CALL(aFunction11a63c);
        Function11a63c();
        // CALL(aFunction11a1e6);
        Function11a1e6();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(wc346);
        // CALL(aPlaceString);
        PlaceStringSimple(wram->wc346, coord(4, 2, wram->wTilemap));
        // CALL(aFunction11a5f5);
        Function11a5f5();
        // XOR_A_A;
        // LD_addr_A(wMobileInactivityTimerMinutes);
        wram->wMobileInactivityTimerMinutes = 0;
        // JP(mBattleTowerRoomMenu2_IncrementJumptable);
        return BattleTowerRoomMenu2_IncrementJumptable();
    }
    // DEC_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes--;
    // SCF;
    // RET;
    return true;
}

bool Function11a192(void){
    // CALL(aFunction11a536);
    // RET_C ;
    if(Function11a536())
        return true;
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_NZ goto asm_11a1b6;
    if(wram->wMobileInactivityTimerMinutes == 0) {
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a6d2);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a6d2), coord(4, 2, wram->wTilemap));
        // AND_A_A;
        // RET;
        return false;
    }
    else {
    // asm_11a1b6:
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_A_addr(wMobileInactivityTimerSeconds);
        // LD_addr_A(wcf66);
        wram->wcf66 = wram->wMobileInactivityTimerSeconds;
        // LD_addr_A(wcd80);
        wram->wcd80 = wram->wMobileInactivityTimerSeconds;
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a6d2);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a6d2), coord(4, 2, wram->wTilemap));
        // SCF;
        // RET;
        return true;
    }
}

bool Function11a1d6(void){
    // LD_A_addr(wcd85);
    // CP_A(0x50);
    // IF_NZ goto asm_11a1e4;
    if(wram->wcd85[0] == 0x50) {
        // LD_A(0xd3);
        // CALL(aSetMobileErrorCode);
        SetMobileErrorCode(0xd3);
        // SCF;
        // RET;
        return true;
    }

// asm_11a1e4:
    // AND_A_A;
    // RET;
    return false;
}

void Function11a1e6(void){
    // LD_HL(mString_11a706);
    // LD_DE(wc346);
    // CALL(aFunction11a1ff);
    uint8_t* de = Function11a1ff(wram->wc346, U82C(String_11a706));
    // LD_HL(wcd85);
    // CALL(aFunction11a1ff);
    // de = Function11a1ff(de, wram->wcd85);
    // LD_HL(mString_11a70b);
    // CALL(aFunction11a1ff);
    // de = Function11a1ff(de, U82C(String_11a70b));
    // LD_A(0x50);
    // LD_de_A;
    *de = 0x50;
    // RET;
}

// CrystalStringCopy?
uint8_t* Function11a1ff(uint8_t* de, const uint8_t* hl){
    while(1) {
    // asm_11a1ff:
        // LD_A_hli;
        uint8_t ch = *(hl++);
        // CP_A(0x50);
        // RET_Z ;
        if(ch == 0x50)
            return de;
        // LD_de_A;
        // INC_DE;
        *(de++) = ch;
        // goto asm_11a1ff;
    }
}

bool BattleTowerRoomMenu2_PlaceYesNoMenu(void){
    // LD_HL(mMenuHeader_11a2de);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_11a2de);
    // CALL(aMenuBox);
    MenuBox();
    // CALL(aMenuBoxCoord2Tile);
    MenuBoxCoord2Tile();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // hlcoord(16, 8, wTilemap);
    // LD_DE(mString_11a2cf);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a2cf), coord(16, 8, wram->wTilemap));
    // hlcoord(16, 10, wTilemap);
    // LD_DE(mString_11a2d3);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a2d3), coord(16, 10, wram->wTilemap));
    // hlcoord(15, 8, wTilemap);
    // LD_A(0xed);
    // LD_hl_A;
    *coord(15, 8, wram->wTilemap) = 0xed;
    // XOR_A_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x0;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool BattleTowerRoomMenu2_UpdateYesNoMenu(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto a_button;
    if(hram.hJoyPressed & A_BUTTON){
    // a_button:
        // XOR_A_A;
        // LD_addr_A(wcd8a);
        wram->wcd8a = 0x0;
        // LD_addr_A(wcd8b);
        wram->wcd8b = 0x0;
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_A_addr(wMobileInactivityTimerMinutes);
        // AND_A_A;
        // IF_NZ goto exit_no_carry;
        if(wram->wMobileInactivityTimerMinutes != 0)
            goto exit_no_carry;
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_A_addr(wMobileInactivityTimerFrames);
        // CP_A(0x0);
        // IF_Z goto asm_11a2b4;
        // LD_A_addr(wcd47);
        // goto exit_carry;

    // asm_11a2b4:
        // LD_A_addr(wcd33);

    // exit_carry:
        // LD_addr_A(wcf66);
        wram->wcf66 = (wram->wMobileInactivityTimerFrames == 0)? wram->wcd33: wram->wcd47;
        // LD_A(0xa);
        // LD_addr_A(wMobileErrorCodeBuffer);
        wram->wMobileErrorCodeBuffer[0] = 0xa;
        // SCF;
        // RET;
        return true;
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto b_button;
    else if(hram.hJoyPressed & B_BUTTON){
    // b_button:
        // CALL(aPlayClickSFX);
        PlayClickSFX();

    exit_no_carry:
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // AND_A_A;
        // RET;
        return false;
    }
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto d_up;
    else if(hram.hJoyPressed & D_UP){
    // d_up:
        // XOR_A_A;
        // LD_addr_A(wcd8a);
        wram->wcd8a = 0;
        // LD_addr_A(wcd8b);
        wram->wcd8b = 0;
        // LD_A_addr(wMobileInactivityTimerMinutes);
        // AND_A_A;
        // IF_Z goto asm_11a24c;
        if(wram->wMobileInactivityTimerMinutes != 0){
            // XOR_A_A;
            // LD_addr_A(wMobileInactivityTimerMinutes);
            wram->wMobileInactivityTimerMinutes = 0x0;
            // hlcoord(15, 8, wTilemap);
            // LD_A(0xed);
            // LD_hl_A;
            *coord(15, 8, wram->wTilemap) = CHAR_RIGHT_CURSOR;
            // hlcoord(15, 10, wTilemap);
            // LD_A(0x7f);
            // LD_hl_A;
            *coord(15, 10, wram->wTilemap) = CHAR_SPACE;
        }
        // goto asm_11a24c;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto d_down;
    else if(hram.hJoyPressed & D_DOWN){
    // d_down:
        // XOR_A_A;
        // LD_addr_A(wcd8a);
        wram->wcd8a = 0;
        // LD_addr_A(wcd8b);
        wram->wcd8b = 0;
        // LD_A_addr(wMobileInactivityTimerMinutes);
        // AND_A_A;
        // IF_NZ goto asm_11a24c;
        if(wram->wMobileInactivityTimerMinutes == 0){
            // INC_A;
            // LD_addr_A(wMobileInactivityTimerMinutes);
            wram->wMobileInactivityTimerMinutes = 0x1;
            // hlcoord(15, 8, wTilemap);
            // LD_A(0x7f);
            // LD_hl_A;
            *coord(15, 8, wram->wTilemap) = CHAR_SPACE;
            // hlcoord(15, 10, wTilemap);
            // LD_A(0xed);
            // LD_hl_A;
            *coord(15, 10, wram->wTilemap) = CHAR_RIGHT_CURSOR;
        }
        // goto asm_11a24c;
    }

// asm_11a24c:
    // CALL(aFunction11a9f0);
    // Function11a9f0();
    // SCF;
    // RET;
    return true;
}

const char String_11a2cf[] = "YES@";
const char String_11a2d3[] = "NO@";

void MenuHeader_11a2d6(void){
//  //  unreferenced
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['14', '6', 'SCREEN_WIDTH - 1', '10'];
    //dw ['NULL'];
    //db ['0'];  // default option
}

const struct MenuHeader MenuHeader_11a2de = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(14, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = NULL,
    .defaultOption = 0,  // default option
};

bool Function11a2e6(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // LD_C(0x2);
    // FARCALL(aFunction115e18);
    Function115e18(0x2);
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a71e);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a71e), coord(4, 2, wram->wTilemap));
    // LD_A(0x80);
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x80;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a302(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_11a30e;
    if(wram->wMobileInactivityTimerMinutes == 0) {
    // asm_11a30e:
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a72a);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a72a), coord(4, 2, wram->wTilemap));
        // hlcoord(9, 4, wTilemap);
        // LD_DE(wcd68);
        // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
        // CALL(aPrintNum);
        PrintNum(coord(4, 4, wram->wTilemap), &wram->wcd68, PRINTNUM_LEADINGZEROS | 1, 2);
        // hlcoord(14, 4, wTilemap);
        // LD_DE(wcd67);
        // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
        // CALL(aPrintNum);
        PrintNum(coord(12, 4, wram->wTilemap), &wram->wcd67, PRINTNUM_LEADINGZEROS | 1, 2);
        // LD_A(0x80);
        // LD_addr_A(wMobileInactivityTimerMinutes);
        wram->wMobileInactivityTimerMinutes = 0x80;
        // JP(mBattleTowerRoomMenu2_IncrementJumptable);
        return BattleTowerRoomMenu2_IncrementJumptable();
    }
    // DEC_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes--;
    // SCF;
    // RET;
    return true;
}

bool Function11a33a(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_11a346;
    if(wram->wMobileInactivityTimerMinutes == 0) {
    // asm_11a346:
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // FARCALL(aFunction115dc3);
        Function115dc3();
        // AND_A_A;
        // RET;
        return false;
    }
    // DEC_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes--;
    // SCF;
    // RET;
    return true;
}

bool Function11a357(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a743);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a743), coord(4, 2, wram->wTilemap));
    // LD_A(0x80);
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x80;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a36b(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_11a377;
    if(wram->wMobileInactivityTimerMinutes != 0) {
        // DEC_A;
        // LD_addr_A(wMobileInactivityTimerMinutes);
        wram->wMobileInactivityTimerMinutes--;
        // SCF;
        // RET;
        return true;
    }

// asm_11a377:
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a755);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a755), coord(4, 2, wram->wTilemap));
    // CALL(aFunction11a5f5);
    Function11a5f5();
    // XOR_A_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a38d(void){
    // CALL(aFunction11a536);
    // RET_C ;
    if(Function11a536())
        return true;
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_NZ goto asm_11a3b1;
    if(wram->wMobileInactivityTimerMinutes == 0) {
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a6d2);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a6d2), coord(4, 2, wram->wTilemap)); // "Communicating..."
        // AND_A_A;
        // RET;
        return false;
    }
    else {
    // asm_11a3b1:
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_A_addr(wMobileInactivityTimerSeconds);
        // LD_addr_A(wcf66);
        // LD_addr_A(wcd80);
        wram->wcd80 = wram->wcf66 = wram->wMobileInactivityTimerSeconds;
        // SCF;
        // RET;
        return true;
    }
}

bool Function11a3c5(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a762);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a762), coord(4, 2, wram->wTilemap)); // "Read the same data"
    // LD_A(0x80);
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x80;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a3d9(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_11a3e5;
    if(wram->wMobileInactivityTimerMinutes != 0) {
        // DEC_A;
        // LD_addr_A(wMobileInactivityTimerMinutes);
        wram->wMobileInactivityTimerMinutes--;
        // SCF;
        // RET;
        return true;
    }

// asm_11a3e5:
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a779);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a779), coord(4, 2, wram->wTilemap)); // "The data is corrupted"
    // LD_A(0x80);
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x80;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a3f9(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_11a405;
    if(wram->wMobileInactivityTimerMinutes != 0) {
        // DEC_A;
        // LD_addr_A(wMobileInactivityTimerMinutes);
        wram->wMobileInactivityTimerMinutes--;
        // SCF;
        // RET;
        return true;
    }

// asm_11a405:
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a755);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a755), coord(4, 2, wram->wTilemap)); // "Read the data?"
    // CALL(aFunction11a5f5);
    Function11a5f5();
    // XOR_A_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a41b(void){
    // CALL(aFunction11a536);
    // RET_C ;
    if(Function11a536())
        return true;
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_NZ goto asm_11a43f;
    if(wram->wMobileInactivityTimerMinutes == 0) {
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a6d2);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a6d2), coord(4, 2, wram->wTilemap)); // "Communicating..."
        // AND_A_A;
        // RET;
        return false;
    }
    else {
    // asm_11a43f:
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_A(0x1c);
        // LD_addr_A(wcf66);
        // LD_addr_A(wcd80);
        wram->wcd80 = wram->wcf66 = 0x1c;
        // SCF;
        // RET;
        return true;
    }
}

bool Function11a452(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a791);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a791), coord(4, 2, wram->wTilemap));
    // LD_A(0x80);
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x80;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a466(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a7c1);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a7c1), coord(4, 2, wram->wTilemap));
    // LD_A(0x80);
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0x80;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a47a(void){
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_Z goto asm_11a486;
    // DEC_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    if(wram->wMobileInactivityTimerMinutes == 0) {
    // asm_11a486:
        // AND_A_A;
        // RET;
        return false;
    }
    --wram->wMobileInactivityTimerMinutes;
    // SCF;
    // RET;
    return true;
}

bool Function11a488(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a7ac);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a7ac), coord(4, 2, wram->wTilemap));
    // CALL(aFunction11a5f5);
    Function11a5f5();
    // XOR_A_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a49e(void){
    // CALL(aFunction11a536);
    // RET_C ;
    if(Function11a536())
        return true;
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_NZ goto asm_11a4c7;
    if(wram->wMobileInactivityTimerMinutes == 0) {
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a6d2);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a6d2), coord(4, 2, wram->wTilemap)); // "Communicating..."
        // LD_A(0x14);
        // LD_addr_A(wcf66);
        wram->wcf66 = 0x14;
        // AND_A_A;
        // RET;
        return false;
    }
    else {
    // asm_11a4c7:
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_A_addr(wMobileInactivityTimerFrames);
        // LD_addr_A(wcf66);
        // LD_addr_A(wcd80);
        wram->wcd80 = wram->wcf66 = wram->wMobileInactivityTimerFrames;
        // SCF;
        // RET;
        return true;
    }
}

bool Function11a4db(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // LD_DE(mString_11a6db);
    // hlcoord(4, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a6db), coord(4, 2, wram->wTilemap));
    // RET;
    return false;
}

bool Function11a4e8(void){
    // CALL(aFunction11a63c);
    Function11a63c();
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a7d7);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a7d7), coord(4, 2, wram->wTilemap));
    // CALL(aFunction11a5f5);
    Function11a5f5();
    // XOR_A_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0;
    // JP(mBattleTowerRoomMenu2_IncrementJumptable);
    return BattleTowerRoomMenu2_IncrementJumptable();
}

bool Function11a4fe(void){
    // CALL(aFunction11a536);
    // RET_C ;
    if(Function11a536())
        return true;
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // AND_A_A;
    // IF_NZ goto asm_11a522;
    if(wram->wMobileInactivityTimerMinutes == 0) {
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // CALL(aFunction11a63c);
        Function11a63c();
        // hlcoord(4, 2, wTilemap);
        // LD_DE(mString_11a6d2);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_11a6d2), coord(4, 2, wram->wTilemap));
        // AND_A_A;
        // RET;
        return false;
    }
    else {
    // asm_11a522:
        // CALL(aExitMenu);
        ExitMenu();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // LD_A_addr(wMobileInactivityTimerSeconds);
        // LD_addr_A(wcf66);
        wram->wcf66 = wram->wMobileInactivityTimerSeconds;
        // LD_addr_A(wcd80);
        wram->wcd80 = wram->wMobileInactivityTimerSeconds;
        // SCF;
        // RET;
        return true;
    }
}

bool Function11a536(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto asm_11a5a7;
    if(hram.hJoyPressed & A_BUTTON) {
    asm_11a5a7:
        // XOR_A_A;
        // LD_addr_A(wcd8a);
        wram->wcd8a = 0x0;
        // LD_addr_A(wcd8b);
        wram->wcd8b = 0x0;
        // AND_A_A;
        // RET;
        return false;
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto asm_11a5a2;
    else if(hram.hJoyPressed & B_BUTTON) {
    // asm_11a5a2:
        // LD_A(0x1);
        // LD_addr_A(wMobileInactivityTimerMinutes);
        wram->wMobileInactivityTimerMinutes = 0x1;
        goto asm_11a5a7;
    }
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto asm_11a564;
    else if(hram.hJoyPressed & D_UP) {
    // asm_11a564:
        // XOR_A_A;
        // LD_addr_A(wcd8a);
        // LD_addr_A(wcd8b);
        // LD_A_addr(wMobileInactivityTimerMinutes);
        // AND_A_A;
        // IF_Z goto asm_11a54d;
        if(wram->wMobileInactivityTimerMinutes != 0) {
            // XOR_A_A;
            // LD_addr_A(wMobileInactivityTimerMinutes);
            wram->wMobileInactivityTimerMinutes = 0;
            // hlcoord(15, 7, wTilemap);
            // LD_A(0xed);
            // LD_hl_A;
            *coord(15, 7, wram->wTilemap) = 0xed;
            // hlcoord(15, 9, wTilemap);
            // LD_A(0x7f);
            // LD_hl_A;
            *coord(15, 9, wram->wTilemap) = 0x7f;
        }
        // goto asm_11a54d;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto asm_11a583;
    else if(hram.hJoyPressed & D_DOWN) {
    // asm_11a583:
        // XOR_A_A;
        // LD_addr_A(wcd8a);
        // LD_addr_A(wcd8b);
        wram->wcd8a = 0x0;
        wram->wcd8b = 0x0;
        // LD_A_addr(wMobileInactivityTimerMinutes);
        // AND_A_A;
        // IF_NZ goto asm_11a54d;
        if(wram->wMobileInactivityTimerMinutes == 0) {
            // INC_A;
            // LD_addr_A(wMobileInactivityTimerMinutes);
            wram->wMobileInactivityTimerMinutes++;
            // hlcoord(15, 7, wTilemap);
            // LD_A(0x7f);
            // LD_hl_A;
            *coord(15, 7, wram->wTilemap) = 0x7f;
            // hlcoord(15, 9, wTilemap);
            // LD_A(0xed);
            // LD_hl_A;
            *coord(15, 9, wram->wTilemap) = 0xed;
        }
        // goto asm_11a54d;
    }

// asm_11a54d:
    // LD_A_addr(wBattleTowerRoomMenu2JumptableIndex);
    // CP_A(0x4);
    // IF_Z goto asm_11a562;
    if(wram->wBattleTowerRoomMenu2JumptableIndex != 0x4) {
        // CALL(aFunction11a9f0);
        // IF_NZ goto asm_11a562;
        if(Function11a9f0() == 0) {
            // CALL(aExitMenu);
            ExitMenu();
            // FARCALL(aReloadMapPart);
            ReloadMapPart();
        }
    }

// asm_11a562:
    // SCF;
    // RET;
    return true;

}

bool BattleTowerRoomMenu2_IncrementJumptable(void){
    // LD_A_addr(wBattleTowerRoomMenu2JumptableIndex);
    // INC_A;
    // LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    wram->wBattleTowerRoomMenu2JumptableIndex++;
    // SCF;
    // RET;
    return true;
}

void Function11a5b9(void){
    // XOR_A_A;
    // LD_addr_A(wMenuBorderLeftCoord);
    wram->wMenuBorderLeftCoord = 0x0;
    // LD_addr_A(wMenuBorderTopCoord);
    wram->wMenuBorderTopCoord = 0x0;
    // LD_A(0x13);
    // LD_addr_A(wMenuBorderRightCoord);
    wram->wMenuBorderRightCoord = 0x13;
    // LD_A(0x5);
    // LD_addr_A(wMenuBorderBottomCoord);
    wram->wMenuBorderBottomCoord = 0x5;
    // CALL(aPushWindow);
    PushWindow();
    // hlcoord(0, 0, wAttrmap);
    // LD_B(0x6);
    // LD_C(0x14); // Why?
    // hlcoord(0, 0, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aFunction3eea);
    Function3eea(coord(0, 0, wram->wTilemap), 0x4, 0x12);
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // LD_C(0x0);
    // FARCALL(aFunction115e18);
    Function115e18(0x0);
    // LD_A(0x1);
    // LD_addr_A(wc305);
    wram->wc305 = 0x1;
    // RET;
}

void Function11a5f5(void){
    // LD_A(0xe);
    // LD_addr_A(wMenuBorderLeftCoord);
    wram->wMenuBorderLeftCoord = 0xe;
    // LD_A(0x13);
    // LD_addr_A(wMenuBorderRightCoord);
    wram->wMenuBorderRightCoord = 0x13;
    // LD_A(0x6);
    // LD_addr_A(wMenuBorderTopCoord);
    wram->wMenuBorderTopCoord = 0x6;
    // LD_A(0xa);
    // LD_addr_A(wMenuBorderBottomCoord);
    wram->wMenuBorderBottomCoord = 0xa;
    // CALL(aPushWindow);
    PushWindow();
    // hlcoord(14, 6, wAttrmap);
    // LD_B(0x5);
    // LD_C(0x6);
    // hlcoord(14, 6, wTilemap);
    // LD_B(0x3);
    // LD_C(0x4);
    // CALL(aFunction3eea);
    Function3eea(coord(14, 6, wram->wTilemap), 0x3, 0x4);
    // hlcoord(16, 7, wTilemap);
    // LD_DE(mString_11a2cf);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a2cf), coord(16, 7, wram->wTilemap));
    // hlcoord(16, 9, wTilemap);
    // LD_DE(mString_11a2d3);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a2d3), coord(16, 9, wram->wTilemap));
    // hlcoord(15, 7, wTilemap);
    // LD_A(0xed);
    // LD_hl_A;
    *coord(15, 7, wram->wTilemap) = 0xed;
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // RET;
}

// Clear first four lines of text
void Function11a63c(void){
    // hlcoord(4, 1, wTilemap);
    // LD_DE(mString_11a7f4);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a7f4), coord(4, 1, wram->wTilemap));
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_11a7f4);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a7f4), coord(4, 2, wram->wTilemap));
    // hlcoord(4, 3, wTilemap);
    // LD_DE(mString_11a7f4);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a7f4), coord(4, 3, wram->wTilemap));
    // hlcoord(4, 4, wTilemap);
    // LD_DE(mString_11a7f4);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11a7f4), coord(4, 4, wram->wTilemap));
    // RET;
}

const char String_11a661[] = 
            "Dialing the"      //db ['"これから\u3000モバイルセンターに"'];
	t_next  "MOBILE CENTER…@"; //next ['"でんわ<WO>かけます@"']

const char String_11a679[] = // Originally "Is the MOBILE ADAPTER ready?"
            "Are you ready"     //db ['"モバイルアダプタ<NO>じゅんびは"'];
	t_next  "to connect?";  //next ['"できて\u3000いますか？@"']

const char String_11a692[] =
            "Please wait"       //db ['"でんわ<WO>かけています"'];
    t_next  "a moment…@";       //next ['"しばらく\u3000おまちください@"']

const char String_11a6aa[] = // Originally "Charges will apply"
            "Please follow"  //db ['"でんわをかけると\u3000つうわりょう"'];
    t_next  "the rules.";      //next ['"せつぞくりょう<GA>かかります@"']

const char String_11a6c8[] = "Connected.@"; //db ['"せつぞく\u3000しました@"'];

const char String_11a6d2[] = "Communicating…@"; //db ['"つうしん\u3000ちゅう@"'];

const char String_11a6db[] =
            "Communication" //db ['"つうしん\u3000ちゅう"'];
    t_next  "canceled.@";   //next ['"セレクト\u3000エーでちゅうし@"']

const char String_11a6f1[] = 
            "This is a"         //db ['"この\u3000サービスには"'];
    t_next  "free service.@";   //next ['"つうわりょう<NO>ほかに@"']

const char String_11a706[] = "Download?"; // Originally "Cost:"  //db ['"おかね<GA>@"'];

void String_11a70b(void){
    //db ['"えん"'];
    //next ['"かかります\u3000よろしい\u3000ですか？@"']
}

const char String_11a71e[] = 
            "Communication" //db ['"つうしん\u3000しゅうりょう@"'];
    t_next  "ended.";

const char String_11a72a[] = 
            "CALL TIME"         //db ['"つないだ\u3000じかん"'];
    t_next  "   min.    sec."; //next ['"\u3000\u3000やく\u3000\u3000\u3000ふん\u3000\u3000\u3000びょう@"']

const char String_11a743[] =
            "There is no"       //db ['"もっていない\u3000データが"'];
    t_next  "stored data!";    //next ['"あります！@"']

const char String_11a755[] =
            "Read the data?"; //db ['"データ<WO>よみこみますか？@"'];

const char String_11a762[] =
            "Read the same" //db ['"おなじ\u3000データ<WO>よみこんだ"'];
    t_next  "data.";        //next ['"こと<GA>ありますが@"']

const char String_11a779[] =
            "The data is"   //db ['"そのデータ<WA>なくなっているか"'];
    t_next  "corrupted.";   //next ['"こわれて\u3000います@"']

const char String_11a791[] =
            "This data"         //db ['"もっている\u3000データと"'];
    t_next  "already exists!";  //next ['"おなじデータしか\u3000ありません！@"']

const char String_11a7ac[] = 
            "Quit reading"  //db ['"データ<NO>よみこみを"'];
    t_next  "data?";       //next ['"ちゅうし\u3000しますか？@"']

const char String_11a7c1[] =
            "There was no"  //db ['"あたらしい\u3000ニュースは"'];
    t_next  "more NEWS.";  //next ['"ありません\u3000でした@"']

const char String_11a7d7[] =
            "Receive the"       //db ['"あたらしいニュース<GA>あります"'];
    t_next  "latest NEWS?";    //next ['"ニュース<WO>よみこみますか？@"']

const char String_11a7f4[] = "               "; //db ['"\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000@"'];

void MenuHeader_11a804(void){
//  //  unreferenced
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', 'SCREEN_WIDTH - 1', '5'];
    //dw ['NULL'];
    //db ['0'];  // default option
}

void Function11a80c(void){
    // LD_DE(hDivisor);
    uint8_t* de = &hram.hDivisor;
    // LD_BC(hDividend);
    // LD_HL(mUnknown_11a89a);
    // CALL(aFunction11a88c);
    Function11a88c(de, hram.hMultiplicand, Unknown_11a89a);
    // LD_BC(hQuotient + 1);
    // LD_HL(mUnknown_11a8ba);
    // CALL(aFunction11a88c);
    Function11a88c(de + 2, hram.hMultiplicand + 1, Unknown_11a89a);
    // LD_BC(hPrintNumBuffer + 2);
    // LD_HL(mUnknown_11a8da);
    // CALL(aFunction11a88c);
    Function11a88c(de + 4, hram.hMultiplicand + 2, Unknown_11a89a);
    // XOR_A_A;
    // LD_B_A;
    uint8_t b = 0;
    // LDH_A_addr(hDivisor);
    // AND_A(0xf);
    // LD_E_A;
    // LDH_A_addr(hPrintNumBuffer + 6);
    // AND_A(0xf);
    // CALL(aFunction11a884);
    // LD_E_A;
    uint8_t e = Function11a884(hram.hPrintNumBuffer[6] & 0xf, hram.hPrintNumBuffer[4] & 0xf, &b);
    // LDH_A_addr(hPrintNumBuffer + 8);
    // AND_A(0xf);
    // CALL(aFunction11a884);
    // LD_addr_A(wcd62);
    wram->wcd62[0] = Function11a884(hram.hPrintNumBuffer[8] & 0xf, e, &b);
    // LD_E_B;
    e = b;
    // XOR_A_A;
    // LD_B_A;
    b = 0;
    // LDH_A_addr(hDivisor);
    // AND_A(0xf0);
    // SWAP_A;
    // CALL(aFunction11a884);
    // LD_E_A;
    e = Function11a884((hram.hPrintNumBuffer[4] & 0xf0) >> 8, e, &b);
    // LDH_A_addr(hPrintNumBuffer + 6);
    // AND_A(0xf0);
    // SWAP_A;
    // CALL(aFunction11a884);
    // LD_E_A;
    e = Function11a884((hram.hPrintNumBuffer[6] & 0xf0) >> 8, e, &b);
    // LDH_A_addr(hPrintNumBuffer + 8);
    // AND_A(0xf0);
    // SWAP_A;
    // CALL(aFunction11a884);
    // LD_addr_A(wcd63);
    wram->wcd63[0] = Function11a884((hram.hPrintNumBuffer[8] & 0xf0) >> 8, e, &b);
    // LD_E_B;
    e = b;
    // XOR_A_A;
    // LD_B_A;
    b = 0;
    // LDH_A_addr(hMathBuffer);
    // AND_A(0xf);
    // CALL(aFunction11a884);
    // LD_E_A;
    e = Function11a884((hram.hPrintNumBuffer[5] & 0xf), e, &b);
    // LDH_A_addr(hPrintNumBuffer + 7);
    // AND_A(0xf);
    // CALL(aFunction11a884);
    // LD_E_A;
    e = Function11a884((hram.hPrintNumBuffer[7] & 0xf), e, &b);
    // LDH_A_addr(hPrintNumBuffer + 9);
    // AND_A(0xf);
    // CALL(aFunction11a884);
    // LD_addr_A(wcd64);
    wram->wcd64[0] = Function11a884((hram.hPrintNumBuffer[9] & 0xf), e, &b);
    // RET;
}

uint8_t Function11a884(uint8_t a, uint8_t e, uint8_t* b){
    // ADD_A_E;
    // CP_A(0xa);
    // RET_C ;
    if(a + e < 0xa)
        return a + e;
    // SUB_A(0xa);
    a = (a + e) - 0xa;
    // INC_B;
    (*b)++;
    // RET;
    return a;
}

void Function11a88c(uint8_t* de, const uint8_t* bc, const uint8_t* hl){
    // LD_A_bc;
    uint8_t a = *bc;
    // SLA_A;
    // LD_C_A;
    // XOR_A_A;
    // LD_B_A;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_de_A;
    de[0] = hl[a*2 + 0];
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    de[1] = hl[a*2 + 1];
    // INC_DE;
    // RET;
}

#define BCD(x) (((x) >= 0xa)? (((x) - 0xa) + 0x10): (x))
#define BCD_2(x) BCD(x % 100), BCD(x / 100)
const uint8_t Unknown_11a89a[] = {
//     for(int x = 0; x < 16; x++){
//     //bcd ['x 0b 100', 'x / 100']
//     }
    BCD_2(0),
    BCD_2(1),
    BCD_2(2),
    BCD_2(3),
    BCD_2(4),
    BCD_2(5),
    BCD_2(6),
    BCD_2(7),
    BCD_2(8),
    BCD_2(9),
    BCD_2(10),
    BCD_2(11),
    BCD_2(12),
    BCD_2(13),
    BCD_2(14),
    BCD_2(15),
};

const uint8_t Unknown_11a8ba[] = {
//     for(int x = 0; x < 0, 16**2, 16; x++){
//     //bcd ['x 0b 100', 'x / 100']
//     }
    BCD_2(16*0),
    BCD_2(16*1),
    BCD_2(16*2),
    BCD_2(16*3),
    BCD_2(16*4),
    BCD_2(16*5),
    BCD_2(16*6),
    BCD_2(16*7),
    BCD_2(16*8),
    BCD_2(16*9),
    BCD_2(16*10),
    BCD_2(16*11),
    BCD_2(16*12),
    BCD_2(16*13),
    BCD_2(16*14),
    BCD_2(16*15),
};

const uint8_t Unknown_11a8da[] = {
//     for(int x = 0; x < 0, 16**3, 16**2; x++){
//     //bcd ['x 0b 100', 'x / 100']
//     }
    BCD_2(16*16*0),
    BCD_2(16*16*1),
    BCD_2(16*16*2),
    BCD_2(16*16*3),
    BCD_2(16*16*4),
    BCD_2(16*16*5),
    BCD_2(16*16*6),
    BCD_2(16*16*7),
    BCD_2(16*16*8),
    BCD_2(16*16*9),
    BCD_2(16*16*10),
    BCD_2(16*16*11),
    BCD_2(16*16*12),
    BCD_2(16*16*13),
    BCD_2(16*16*14),
    BCD_2(16*16*15),
};

void BattleTowerRoomMenu_WriteMessage(void){
    //jumptable ['.Jumptable', 'wc31a']
    switch(wram->wc31a) {
    // Jumptable:
        //dw ['BattleTowerRoomMenu_WriteMessage_DoNothing'];
        case 0: return BattleTowerRoomMenu_WriteMessage_DoNothing();
        //dw ['Function11a90f'];
        case 1: return Function11a90f();
        //dw ['Function11a971'];
        case 2: return Function11a971();
    }
}

void Function11a90f(void){
    uint8_t buf[0x008c];
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // LD_A(0x50);
    // LD_HL(wc320);
    // LD_BC(0x008c);
    // CALL(aByteFill);
    ByteFill(wram->wc320, 0x008c, CHAR_TERM);
    // LD_A_addr(wc31b);
    // LD_L_A;
    // LD_A_addr(wc31c);
    // LD_H_A;
    // const uint8_t* hl = gMobileMessagePtr;
    const struct TextCmd* cmd = gMobileTextPtr;
    // LD_DE(wc320);
    uint8_t* de = wram->wc320;

    uint8_t a;
    uint8_t* dst = buf;
    while(cmd->cmd != TX_END) {
        if(dst - buf >= (long)sizeof(buf)) {
            buf[sizeof(buf) - 1] = CHAR_TERM;
            break;
        }
        if(cmd->cmd == TX_START) {
            const uint8_t* src = U82C(cmd->text);
            while(*src != CHAR_TERM && (dst - buf) < (long)sizeof(buf)) {
                if(*src == CHAR_DONE) {
                    *dst = CHAR_DONE;
                    goto end_cmd_buf;
                }
                *(dst++) = *(src++);
            }
        } else if(cmd->cmd == TX_RAM) {
            uint8_t* p = cmd->ram;
            while(*p != CHAR_TERM && (dst - buf) < (long)sizeof(buf))
                *(dst++) = *(p++);
        }
        cmd++;
    }
end_cmd_buf:

    const uint8_t* hl = buf;

    while(1) {
    // asm_11a92c:
        // LD_A_hli;
        a = *(hl++);
        // CP_A(0x57);
        // IF_Z goto asm_11a94f;
        if(a == CHAR_DONE)
            break;
        // CP_A(0x0);
        // IF_Z goto asm_11a92c;
        // CP_A(0x50);
        // IF_Z goto asm_11a92c;
        if(a == CHAR_NULL || a == CHAR_TERM)
            continue;
        // CP_A(0x1);
        // IF_Z goto asm_11a941;
        // if(a != 0x1) {
            // LD_de_A;
            // INC_DE;
        *(de++) = a;
            // goto asm_11a92c;
        // }

    // asm_11a941:
        // LD_A_hli;
        // LD_C_A;
        // LD_A_hli;
        // LD_B_A;
        // const uint8_t* bc = GBToRAMAddr(hl[0] | (hl[1] << 8));

        // do {
        // // asm_11a945:
        //     // LD_A_bc;
        //     uint8_t n = *bc;
        //     // INC_BC;
        //     bc++;
        //     // CP_A(0x50);
        //     // IF_Z goto asm_11a92c;
        //     if(n == 0x50)
        //         goto asm_11a92c;
        //     // LD_de_A;
        //     *de = n;
        //     // INC_DE;
        //     de++;
        //     // goto asm_11a945;
        // } while(1);
    }

// asm_11a94f:
    // XOR_A_A;
    // LD_addr_A(wc31f);
    wram->wc31f = 0;
    // LD_A(LOW(wc320));
    // LD_addr_A(wc31b);
    // LD_A(HIGH(wc320));
    // LD_addr_A(wc31c);
    gMobileMessagePtr = wram->wc320;
    // hlcoord(1, 14, wTilemap);
    // LD_A_L;
    // LD_addr_A(wc31d);
    // LD_A_H;
    // LD_addr_A(wc31e);
    gMobileMessageDestPtr = coord(1, 14, wram->wTilemap);
    // LD_HL(wc31a);
    // INC_hl;
    wram->wc31a++;
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);

    return BattleTowerRoomMenu_WriteMessage_DoNothing();
}

void BattleTowerRoomMenu_WriteMessage_DoNothing(void){
    // RET;
}

void Function11a971(void){
    // LD_HL(wc31f);
    // LDH_A_addr(hJoyDown);
    // AND_A_A;
    // IF_NZ goto asm_11a97f;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto asm_11a97f;
    if(hram.hJoyDown != 0 || wram->wc31f == 0) {
    // asm_11a97f:
        // LD_A_addr(wOptions);
        // AND_A(0x7);
        // LD_hl_A;
        gOptions.options &= TEXT_DELAY_MASK;
        // LD_HL(wcd8d);
        uint8_t* hl = wram->wcd8d;
        // LD_A_addr(wc31b);
        // LD_E_A;
        // LD_A_addr(wc31c);
        // LD_D_A;
        // LD_A_de;
        // INC_DE;
        *(hl++) = *(gMobileMessagePtr++);
        // LD_hli_A;
        // LD_A_E;
        // LD_addr_A(wc31b);
        // LD_A_D;
        // LD_addr_A(wc31c);
        // LD_A(0x50);
        // LD_hl_A;
        *hl = 0x50;
        // LD_A_addr(wc31d);
        // LD_L_A;
        // LD_A_addr(wc31e);
        // LD_H_A;
        // LD_DE(wcd8d);
        struct TextPrintState st = {.de = wram->wcd8d, .hl = gMobileMessageDestPtr};
        // CALL(aPlaceString);
        PlaceString(&st, st.hl);
        // LD_A_C;
        // LD_addr_A(wc31d);
        // LD_A_B;
        // LD_addr_A(wc31e);
        gMobileMessageDestPtr = st.bc;
        // LD_A_addr(wcd8d);
        // CP_A(0x50);
        // IF_NZ goto asm_11a9bf;
        if(wram->wcd8d[0] == CHAR_TERM) {
            // XOR_A_A;
            // LD_addr_A(wc31a);
            wram->wc31a = 0;
        }

    // asm_11a9bf:
        // RET;
        return;
    }
    // DEC_hl;
    --wram->wc31f;
    // RET;
    return;
}

void BattleTowerRoomMenu_SetMessage(const txt_cmd_s* hl){
    // LD_A_L;
    // LD_addr_A(wc31b);
    // LD_A_H;
    // LD_addr_A(wc31c);
    gMobileTextPtr = hl;
    // LD_A(0x1);
    // LD_addr_A(wc31a);
    wram->wc31a = 0x1;
    // RET;
}

void Function11a9ce(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aReloadTilesetAndPalettes);
    ReloadTilesetAndPalettes();
    // CALL(aCall_ExitMenu);
    ExitMenu();
    // FARCALL(aStubbed_Function106462);
    Stubbed_Function106462();
    // FARCALL(aFunction106464);
    Function106464();
    // CALL(aGSReloadPalettes);
    // FARCALL(aFinishExitMenu);
    FinishExitMenu();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // RET;
}

uint8_t Function11a9f0(void){
    // LD_A(0x1);
    // AND_A_A;
    // RET;
    return 0x1;
}

void Function11a9f4(void){
//  //  unreferenced
    LD_A_addr(wcd8a);
    LD_L_A;
    LD_A_addr(wcd8b);
    LD_H_A;
    INC_HL;
    LD_A_L;
    LD_addr_A(wcd8a);
    LD_A_H;
    LD_addr_A(wcd8b);
    LD_DE(0xd5d0);
    ADD_HL_DE;
    BIT_H(7);
    RET_NZ ;
    LD_A(0xd6);
    CALL(aSetMobileErrorCode);
    AND_A_A;
    RET;

}

const txt_cmd_s Text_SaveFileWillBeSent[] = {
    text_start("SAVE FILE will be"
        t_line "sent."
        t_done )
};

const txt_cmd_s Text_SentSaveFileReadingNews[] = {
    text_start("Sent SAVE FILE."
        t_line "Reading NEWS…"
        t_done )
};

const txt_cmd_s Text_ReadingNews[] = {
    text_start("Reading NEWS…"
        t_done )
};

const txt_cmd_s Text_ReceivedNews[] = {
    text_start("Received NEWS!"
        t_done )
};

const txt_cmd_s Text_QuitReadingNews[] = {
    text_start("Quit reading NEWS?"
        t_done )
};

void Text_CanceledSendingSaveFile(void){
//  //  unreferenced
    //text ['"Canceled sending"']
    //line ['"SAVE FILE."']
    //done ['?']

    return Text_ReceivedOddEgg();
}

void Text_ReceivedOddEgg(void){
//  //  unreferenced
    //text ['"ODD EGG"']
    //line ['"was received!"']
    //done ['?']
}

const txt_cmd_s Text_RegisteringRecord[] = {
    text_start("Registering your"
        t_line "record…"
        t_done )
};

const txt_cmd_s Text_BattleRoomVisitLimit[] = {
//  //  unreferenced
    text_start("One visit per day"
        t_line "per BATTLE ROOM!"
        t_done )
};

const txt_cmd_s Text_PartyMonTopsThisLevel[] = {
    text_start("A party #MON"
        t_line "tops this level."
        t_done )
};

const txt_cmd_s Text_UberRestriction[] = {
    text_ram(wram_ptr(wcd49))
    text_start(" may go"
        t_line "only to BATTLE"

        t_para "ROOMS that are"
        t_line "Lv.70 or higher."
        t_done )
};

const txt_cmd_s Text_CancelBattleRoomChallenge[] = {
    text_start("Cancel your BATTLE"
        t_line "ROOM challenge?"
        t_done )
};

const txt_cmd_s Text_ExitGymLeaderHonorRoll[] = {
    text_start("Exit ROOM LEADER"
        t_line "HONOR ROLL?"
        t_done )
};

const txt_cmd_s Text_LinkingWithCenter[] = {
//  //  unreferenced
    text_start("Linking with the"
        t_line "CENTER…"
        t_done )
};

const txt_cmd_s Text_WhatLevelDoYouWantToChallenge[] = {
    text_start("What level do you"
        t_line "want to challenge?"
        t_done )
};

const txt_cmd_s Text_CheckBattleRoomListByMaxLevel[] = {
    text_start("Check BATTLE ROOM"
        t_line "list by max level?"
        t_done )
};

const txt_cmd_s Text_EnterWhichBattleRoom[] = {
//  //  unreferenced
    text_start("Enter which"
        t_line "BATTLE ROOM?"
        t_done )
};

const txt_cmd_s Text_WhichBattleRoom[] = {
//  //  unreferenced
    text_start("Which BATTLE ROOM?"
        t_done )
};

const txt_cmd_s Text_ThisBattleRoomPleaseWait[] = {
//  //  unreferenced
    text_ram(wram_ptr(wStringBuffer3))
    text_start("\'s ROOM ")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("?"
        t_line "Please wait…"
        t_done )
};

// Mobile_HaveWantScreenSpecial
void Function11ac3e(void){
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // CALL(aFadeToMenu);
    FadeToMenu();
    // CALLFAR(aClearSpriteAnims2);
    ClearSpriteAnims2();
    // CALL(aFunction11ac51);
    Function11ac51();
    // CALL(aCloseSubmenu);
    CloseSubmenu();
    // RET;
}

// Mobile_HaveWantScreenLoop
void Function11ac51(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = gOptions.options;
    // SET_hl(4);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram.hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram.hInMenu = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = 0;
    // LD_addr_A(wcd49);
    wram->wcd49 = 0;
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_addr_A(wcd4c);
    wram->wcd4c = 0;
    // LD_addr_A(wcd4d);
    wram->wcd4d = 0;
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0;
    // CALL(aFunction11ad1b);
    Function11ad1b();
    // CALL(aDelayFrame);
    DelayFrame();

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto asm_11aca8;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aFunction11b314);
        Function11b314();
        // CALL(aFunction11acb7);
        Function11acb7();
        // CALL(aFunction11ad6e);
        Function11ad6e();
        // LD_A(30 * SPRITEOAMSTRUCT_LENGTH);
        // LD_addr_A(wCurSpriteOAMAddr);
        wram->wCurSpriteOAMAddr = 30 * SPRITEOAMSTRUCT_LENGTH;
        // FARCALL(aDoNextFrameForAllSprites);
        DoNextFrameForAllSprites();
        // FARCALL(aReloadMapPart);
        ReloadMapPart();
        // goto loop;
    }

// asm_11aca8:
    // CALL(aClearSprites);
    ClearSprites();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram.hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // RET;
}

void Function11acb7(void){
    // LD_HL(mTilemapPack_11ba44);
    // LD_A_addr(wcd49);
    // LD_C_A;
    // LD_B(0);
    // SLA_C;
    // RL_B;
    // SLA_C;
    // RL_B;
    // SLA_C;
    // RL_B;
    // ADD_HL_BC;
    const uint8_t* hl = TilemapPack_11ba44 + (wram->wcd49 * 8);
    // decoord(6, 6, wTilemap);
    // LD_A_hli;
    // LD_de_A;
    *coord(1, 12, wram->wTilemap) = *(hl++);
    // decoord(0, 7, wTilemap);
    // LD_BC(7);
    // CALL(aCopyBytes);
    // CopyBytes(coord(2, 6, wram->wTilemap), hl, 7);
    for(int i = 0; i < 7; ++i) {
        *coord(2, 6 + i, wram->wTilemap) = hl[i];
    }
    hl += 7;
    // LD_A_addr(wcd49);
    // INC_A;
    // LD_addr_A(wcd49);
    wram->wcd49++;
    // LD_A_hl;
    // CP_A(0xff);
    // IF_NZ goto get_the_other;
    if(*hl == 0xff) {
        // XOR_A_A;
        // LD_addr_A(wcd49);
        wram->wcd49 = 0;
    }

// get_the_other:
    // LD_HL(mTilemapPack_11bb7d);
    // LD_A_addr(wcd4a);
    // LD_C_A;
    // LD_B(0);
    // SLA_C;
    // RL_B;
    // SLA_C;
    // RL_B;
    // SLA_C;
    // RL_B;
    // ADD_HL_BC;
    hl = TilemapPack_11bb7d + (wram->wcd4a * 8);
    // decoord(3, 9, wTilemap);
    // LD_BC(7);
    // CALL(aCopyBytes);
    // CopyBytes(coord(4, 8, wram->wTilemap), hl, 7);
    // vertical
    // ld a, [hli]
    // ld [de], a
    // decoord 4, 9
    // ld a, [hli]
    // ld [de], a
    // decoord 4, 10
    // ld a, [hli]
    // ld [de], a
    // decoord 4, 11
    // ld a, [hli]
    // ld [de], a
    // decoord 4, 12
    // ld a, [hli]
    // ld [de], a
    // decoord 4, 13
    // ld a, [hli]
    // ld [de], a
    // decoord 4, 14
    // ld a, [hli]
    // ld [de], a
    for(int i = 0; i < 7; ++i) {
        *coord(4, 8 + i, wram->wTilemap) = hl[i];
    }
    hl += 7;
    // LD_A_addr(wcd4a);
    // INC_A;
    // LD_addr_A(wcd4a);
    wram->wcd4a++;
    // INC_HL;
    hl++;
    // LD_A_hl;
    // CP_A(0xff);
    // RET_NZ ;
    if(*hl == 0xff) {
        // XOR_A_A;
        // LD_addr_A(wcd4a);
        wram->wcd4a = 0;
    }
    // RET;
}

void Function11ad1b(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // FARCALL(aFunction17c000);
    Function17c000();
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wcd82);
    wram->wcd82[0] = wram->wMenuCursorY;
    // DEC_A;
    // LDH_addr_A(hObjectStructIndex);
    hram.hObjectStructIndex = wram->wMenuCursorY - 1;
    // LD_A(0x10);
    // LD_addr_A(wCurIconTile);
    wram->wCurIconTile = 0x10;
    // LD_HL(mLoadMenuMonIcon);
    // LD_A(BANK(aLoadMenuMonIcon));
    // LD_E(MONICON_MOBILE1);
    // RST(aFarCall);
    LoadMenuMonIcon(MONICON_MOBILE1);
    // LD_HL(mLoadMenuMonIcon);
    // LD_A(BANK(aLoadMenuMonIcon));
    // LD_E(MONICON_MOBILE2);
    // RST(aFarCall);
    LoadMenuMonIcon(MONICON_MOBILE2);
    // LD_HL(wPokedexOrder);
    // LD_BC(0x0115);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wPokedexOrder, 0x115, 0);
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // LD_addr_A(wcf64);
    wram->wcf64 = 0;
    // LD_addr_A(wcf65);
    wram->wcf65 = 0;
    // LD_addr_A(wcf66);
    wram->wcf66 = 0;
    // LD_addr_A(wcd30);
    wram->wcd30 = 0;
    // LD_A(DEXMODE_ABC);
    // LD_addr_A(wCurDexMode);
    wram->wCurDexMode = DEXMODE_ABC;
    // FARCALL(aPokedex_OrderMonsByMode);
    Pokedex_OrderMonsByMode();
    // RET;
}

// Mobile_CallHaveWantScreenJumptable
void Function11ad6e(void){
    // LD_A_addr(wJumptableIndex);
    // LD_HL(mJumptable_11ad78);
    // CALL(aFunction11b239);
    // JP_hl;
    return Jumptable_11ad78(wram->wJumptableIndex);
}

// Mobile_HaveWantScreenJumptable
void Jumptable_11ad78(uint8_t a){
    switch(a) {
        case 0: Function11b082(); break;
        case 1: Function11b0ff(); break;
        case 2: Function11ad95(); break;
        case 3: Function11adc4(); break;
        case 4: Function11ae4e(); break;
        case 5: Function11ae98(); break;
        case 6: Function11ad8f(); break;
        case 7: Function11af04(); break;
        case 8: Function11af4e(); break;
    }
}

// Mobile_HaveWantScreenJumptable_Next
void Function11ad8a(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

// Mobile_HaveWantScreenJumptable_End
void Function11ad8f(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

void Function11ad95(void){
    // LD_HL(mMenuHeader_11ae38);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_11ae38);
    // CALL(aMenuBox);
    MenuBox();
    // hlcoord(12, 12, wTilemap);
    // LD_DE(mString_11ae40);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11ae40), coord(10, 12, wram->wTilemap));
    // hlcoord(10, 10, wAttrmap);
    // LD_BC((8 << 8) | 8);
    // CALL(aFunction11afd6);
    Function11afd6(coord(8, 10, wram->wAttrmap), 8, 10);
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // CALL(aFunction11ad8a);
    Function11ad8a();
    // LD_A(0x1);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 0x1;
    // LD_HL(mUnknown_11afcc);
    // CALL(aFunction11afb7);
    Function11afb7(Unknown_11afcc);

    return Function11adc4();
}

void Function11adc4(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(hram.hJoyPressed == 0)
        return;
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto asm_11ade6;
    uint8_t a;
    if(hram.hJoyPressed & D_UP) {
    // asm_11ade6:
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        a = wram->wMenuCursorY - 1;
        // RET_Z ;
        if(a == 0)
            return;
        goto asm_11adf4;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto asm_11aded;
    else if(hram.hJoyPressed & D_DOWN) {
    // asm_11aded:
        // LD_A_addr(wMenuCursorY);
        // INC_A;
        a = wram->wMenuCursorY + 1;
        // CP_A(0x4);
        // RET_Z ;
        if(a == 0x4)
            return;

    asm_11adf4:
        // PUSH_AF;
        // LD_HL(mUnknown_11afcc);
        // CALL(aFunction11afbb);
        Function11afbb(Unknown_11afcc);
        // POP_AF;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = a;
        // LD_HL(mUnknown_11afcc);
        // CALL(aFunction11afb7);
        Function11afb7(Unknown_11afcc);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto asm_11ae06;
    else if(hram.hJoyPressed & A_BUTTON) {
    // asm_11ae06:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        a = wram->wMenuCursorY - 1;
        // LD_HL(wcd30);
        // LD_hl_A;
        wram->wcd30 = a;
        // AND_A_A;
        // IF_Z goto asm_11ae28;
        if(a == 0) {
        // asm_11ae28:
            // LD_A(0x3);
            // LD_hl_A;
            wram->wcd30 = 0x3;
        }
        else {
            // hlcoord(2, 14, wTilemap);
            // LD_A_addr(wMenuCursorY);
            // CP_A(0x2);
            // IF_Z goto asm_11ae23;
            if(wram->wMenuCursorY == 0x2) {
            // asm_11ae23:
                // CALL(aFunction11b267);
                Function11b267(coord(6, 4, wram->wTilemap));
                // goto asm_11ae2b;
            }
            else {
                // CALL(aFunction11b272);
                Function11b272(coord(6, 4, wram->wTilemap));
                // goto asm_11ae2b;
            }
        }
    
    // asm_11ae2b:
        // CALL(aFunction11ad8a);
        Function11ad8a();
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // RET_Z ;
    else if(hram.hJoyPressed & B_BUTTON) {
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // XOR_A_A;
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0;
        // goto asm_11ae2e;
    }
    else 
        return;

// asm_11ae2e:
    // CALL(aExitMenu);
    ExitMenu();
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // RET;
}

const struct MenuHeader MenuHeader_11ae38 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(8, 10, 17, SCREEN_HEIGHT - 1),
    .data = NULL,
    .defaultOption = 0,  // default option
};

const char String_11ae40[] =
            "EITHER"   //db ['"どちらでも"'];
    t_next  "♂MALE"    //next ['"♂オス"']
    t_next  "♀FEMALE"; //next ['"♀メス"']
    //db ['"@"'];

void Function11ae4e(void){
    // LD_HL(mMenuHeader_11afe8);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_11afe8);
    // CALL(aMenuBox);
    MenuBox();
    // hlcoord(10, 14, wTilemap);
    // LD_DE(mString_11aff0);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11aff0), coord(8, 14, wram->wTilemap));
    // LD_HL(mMenuHeader_11b013);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_11b013);
    // CALL(aMenuBox);
    MenuBox();
    // hlcoord(16, 8, wTilemap);
    // LD_DE(mString_11b01b);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11b01b), coord(16, 8, wram->wTilemap));
    // hlcoord(14, 7, wAttrmap);
    // LD_BC((5 << 8) | 6);
    // CALL(aFunction11afd6);
    Function11afd6(coord(14, 7, wram->wAttrmap), 5, 6);
    // hlcoord(9, 12, wAttrmap);
    // LD_BC((6 << 8) | 11);
    // CALL(aFunction11afd6);
    Function11afd6(coord(7, 12, wram->wAttrmap), 6, 13);
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // CALL(aFunction11ad8a);
    Function11ad8a();
    // LD_A(0x1);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 0x1;
    // LD_HL(mUnknown_11afd2);
    // CALL(aFunction11afb7);
    Function11afb7(Unknown_11afd2);

    return Function11ae98();
}

void Function11ae98(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(hram.hJoyPressed == 0)
        return;
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto asm_11aec1;
    uint8_t a;
    if(hram.hJoyPressed & D_UP) {
    // asm_11aec1:
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        a = wram->wMenuCursorY - 1;
        // RET_Z ;
        if(a == 0)
            return;
        goto asm_11aecf;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto asm_11aec8;
    else if(hram.hJoyPressed & D_DOWN) {
    // asm_11aec8:
        // LD_A_addr(wMenuCursorY);
        // INC_A;
        a = wram->wMenuCursorY + 1;
        // CP_A(0x3);
        // RET_Z ;
        if(a == 0x3)
            return;

    asm_11aecf:
        // PUSH_AF;
        // LD_HL(mUnknown_11afd2);
        // CALL(aFunction11afbb);
        Function11afbb(Unknown_11afd2);
        // POP_AF;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = a;
        // LD_HL(mUnknown_11afd2);
        // CALL(aFunction11afb7);
        Function11afb7(Unknown_11afd2);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto asm_11aee1;
    else if(hram.hJoyPressed & A_BUTTON) {
    // asm_11aee1:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_A_addr(wMenuCursorY);
        // CP_A(0x2);
        // IF_Z goto asm_11aeb4;
        if(wram->wMenuCursorY == 0x2)
            goto asm_11aeb4;
        // LD_A_addr(wcd4b);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = wram->wcd4b;
        // CALL(aFunction11b022);
        Function11b022();
        // CALL(aFunction11ad8a);
        Function11ad8a();
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // RET_Z ;
    else if(hram.hJoyPressed & B_BUTTON) {
        // CALL(aPlayClickSFX);
        PlayClickSFX();

    asm_11aeb4:
        // hlcoord(2, 14, wTilemap);
        // LD_A(0x7f);
        // LD_hl_A;
        *coord(6, 4, wram->wTilemap) = 0x7f;
        // LD_A(0x1);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x1;
        // goto asm_11aef7;
    }
    else 
        return;

// asm_11aef7:
    // CALL(aExitMenu);
    ExitMenu();
    // CALL(aExitMenu);
    ExitMenu();
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // RET;
}

void Function11af04(void){
    // LD_HL(mMenuHeader_11afe8);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_11afe8);
    // CALL(aMenuBox);
    MenuBox();
    // hlcoord(10, 14, wTilemap);
    // LD_DE(mString_11b003);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11b003), coord(8, 14, wram->wTilemap));
    // LD_HL(mMenuHeader_11b013);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_11b013);
    // CALL(aMenuBox);
    MenuBox();
    // hlcoord(16, 8, wTilemap);
    // LD_DE(mString_11b01b);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11b01b), coord(16, 8, wram->wTilemap));
    // hlcoord(14, 7, wAttrmap);
    // LD_BC((5 << 8) | 6);
    // CALL(aFunction11afd6);
    Function11afd6(coord(14, 7, wram->wAttrmap), 5, 6);
    // hlcoord(9, 12, wAttrmap);
    // LD_BC((6 << 8) | 11);
    // CALL(aFunction11afd6);
    Function11afd6(coord(7, 12, wram->wAttrmap), 6, 13);
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // CALL(aFunction11ad8a);
    Function11ad8a();
    // LD_A(0x2);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 0x2;
    // LD_HL(mUnknown_11afd2);
    // CALL(aFunction11afb7);
    Function11afb7(Unknown_11afd2);

    return Function11af4e();
}

void Function11af4e(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(hram.hJoyPressed == 0)
        return;
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto asm_11af77;
    uint8_t a;
    if(hram.hJoyPressed & D_UP) {
    // asm_11af77:
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        a = wram->wMenuCursorY - 1;
        // RET_Z ;
        if(a == 0)
            return;
        goto asm_11af85;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto asm_11af7e;
    else if(hram.hJoyPressed & D_DOWN) {
    // asm_11af7e:
        // LD_A_addr(wMenuCursorY);
        // INC_A;
        a = wram->wMenuCursorY + 1;
        // CP_A(0x3);
        // RET_Z ;
        if(a == 0x3)
            return;
    
    asm_11af85:
        // PUSH_AF;
        // LD_HL(mUnknown_11afd2);
        // CALL(aFunction11afbb);
        Function11afbb(Unknown_11afd2);
        // POP_AF;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = a;
        // LD_HL(mUnknown_11afd2);
        // CALL(aFunction11afb7);
        Function11afb7(Unknown_11afd2);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto asm_11af97;
    else if(hram.hJoyPressed & A_BUTTON) {
    // asm_11af97:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_A_addr(wMenuCursorY);
        // CP_A(0x2);
        // IF_Z goto asm_11af6a;
        if(wram->wMenuCursorY == 0x2)
            goto asm_11af6a;
        // LD_A(0x6);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x6;
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0;
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // RET_Z ;
    else if(hram.hJoyPressed & B_BUTTON) {
        // CALL(aPlayClickSFX);
        PlayClickSFX();

    asm_11af6a:
        // hlcoord(2, 14, wTilemap);
        // LD_A(0x7f);
        // LD_hl_A;
        *coord(6, 14, wram->wTilemap) = 0x7f;
        // LD_A(0x1);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x1;
        // goto asm_11afaa;
    }
    else {
        return;
    }

// asm_11afaa:
    // CALL(aExitMenu);
    ExitMenu();
    // CALL(aExitMenu);
    ExitMenu();
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // RET;
}

void Function11afb7(const uint16_t* hl){
    // LD_E(0xed);
    // JR(masm_11afbd);
    return asm_11afbd(hl, 0xed);
}

void Function11afbb(const uint16_t* hl){
    // LD_E(0x7f);

    return asm_11afbd(hl, 0x7f);
}

void asm_11afbd(const uint16_t* hl, uint8_t e){
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_E;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // LD_de_A;
    wram->wTilemap[hl[wram->wMenuCursorY - 1]] = e;
    // RET;
}

const uint16_t Unknown_11afcc[] = {
    coord(9, 12, 0),
    coord(9, 14, 0),
    coord(9, 16, 0),
};

const uint16_t Unknown_11afd2[] = {
    coord(15, 8, 0),
    coord(15, 10, 0),
};

void Function11afd6(uint8_t* hl, uint8_t b, uint8_t c){
    // LD_DE(SCREEN_WIDTH);
    // LD_A(0x3);

    do {
    // row:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // col:
            // LD_hli_A;
            *(hl2++) = 0x3;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c2 != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

const struct MenuHeader MenuHeader_11afe8 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = NULL,
    .defaultOption = 0,  // default option
};

const char String_11aff0[] =
            "Is this OK?";  //db ['"この\u3000じょうけんで"'];
                            //next ['"よろしいですか?@"']

const char String_11b003[] =
            "Cancel the"    //db ['"こうかんを"'];
    t_next  "trade?";       //next ['"ちゅうししますか？@"']

const struct MenuHeader MenuHeader_11b013 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(14, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = NULL,
    .defaultOption = 1,  // default option
};

const char String_11b01b[] =
            "YES"   //db ['"はい"'];
    t_next  "NO";   //next ['"いいえ@"']

void Function11b022(void){
    // LD_A_addr(wcd2e);
    // AND_A_A;
    // IF_Z goto asm_11b02e;
    if(wram->wcd2e != 0) {
        // LD_HL(wStringBuffer3);
        // CALL(aFunction11b03d);
        Function11b03d(wram->wStringBuffer3, wram->wcd2e);
    }

// asm_11b02e:
    // LD_A_addr(wcd30);
    // AND_A_A;
    // RET_Z ;
    // CP_A(0x3);
    // RET_Z ;
    if(wram->wcd30 == 0 || wram->wcd30 == 0x3)
        return;
    // LD_HL(wStringBuffer4);
    // CALL(aFunction11b03d);
    Function11b03d(wram->wStringBuffer4, wram->wcd30);
    // RET;
}

void Function11b03d(uint8_t* hl, uint8_t a){
    static const char MaleString[] = "♂"; // db "オスの　"
    static const char FemaleString[] = "♀"; // db "メスの　"
    // PUSH_HL;
    uint8_t* hl2 = hl;
    // PUSH_AF;
    // LD_C(0x1);
    uint8_t c = 1;

    while(1) {
    // loop:
        // LD_A_hli;
        uint8_t a2 = hl2[0];
        // CP_A(0xef);
        // IF_Z goto gender;
        // CP_A(0xf5);
        // IF_Z goto gender;
        if(a2 == 0xef || a2 == 0xf5) {
        // gender:
            // DEC_HL;
            // LD_A(0x50);
            // LD_hli_A;
            *hl2 = 0x50;
            break;
        }
        // CP_A(0x50);
        // IF_Z goto done;
        else if(a2 == 0x50)
            break;
        // INC_C;
        c++, hl2++;
        // goto loop;
    }

// done:
    // DEC_HL;
    // PUSH_HL;
    // LD_E(4);
    // LD_D(0);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    uint8_t* de = hl2;
    // POP_HL;

// loop2:
    // LD_A_hld;
    // LD_de_A;
    // DEC_DE;
    // DEC_C;
    // IF_NZ goto loop2;
    // POP_AF;
    // POP_DE;
    // CP_A(0x1);
    // IF_NZ goto female;
    if(a == 0x1) {
        // LD_HL(mFunction11b03d_MaleString);
        // goto got_string;
        U82CB(de, 2, MaleString);
    }
    else {
    // female:
        // LD_HL(mFunction11b03d_FemaleString);
        U82CB(de, 2, FemaleString);
    }

// got_string:
    // LD_BC(4);  // string length
    // CALL(aCopyBytes);
    // RET;
}

void Function11b082(void){
    // CALL(aFunction11b242);
    Function11b242();
    // LD_A(0x7);
    // LD_addr_A(wc7d3);
    wram->wc7d3[0] = 0x4;
    // CALL(aFunction11b099);
    Function11b099();
    // CALL(aFunction11b295);
    Function11b295();
    // CALL(aFunction11b275);
    Function11b275();
    // CALL(aSetPalettes);
    SetPalettes();
    // JP(mFunction11ad8a);
    return Function11ad8a();
}

static void Function11b099_SetCaughtFlag(tile_t** hl){
    // CALL(aCheckCaughtMemMon);
    // IF_NZ goto okay;
    if(CheckCaughtMemMon()) {
    // okay:
        // LD_A(0x1);
        // LD_hli_A;
        **hl = 0x1;
        // RET;
    }
    // INC_HL;
    (*hl)++;
    // RET;
}

static bool Function11b099_CheckSeenFlag(tile_t** hl){
    static const char EmptySlot[] = "-----";//db ['"ーーーーー@"'];
    // CALL(aCheckSeenMemMon);
    // RET_NZ ;
    if(CheckSeenMemMon())
        return false;

    // INC_HL;
    (*hl)++;
    // LD_DE(mFunction11b099_EmptySlot);
    struct TextPrintState st = {.hl = *hl, .de = U82C(EmptySlot)};
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    *hl = st.hl;
    // SCF;
    // RET;
    return true;
}

static void Function11b099_PlaceMonNameOrPlaceholderString(tile_t* hl, species_t a){
    // AND_A_A;
    // RET_Z ;
    if(a == 0)
        return;

    // CALL(aFunction11b099_CheckSeenFlag);
    // RET_C ;
    if(Function11b099_CheckSeenFlag(&hl))
        return;

    // CALL(aFunction11b099_SetCaughtFlag);
    Function11b099_SetCaughtFlag(&hl);
    // PUSH_HL;
    // CALL(aGetPokemonName);
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(GetPokemonName(a), hl);
    // RET;
}

void Function11b099(void){
    // LD_C(0x6);
    // hlcoord(11, 1, wTilemap);
    // LD_A_addr(wc7d3);
    // ADD_A_A;
    // LD_B_A;
    // XOR_A_A;
    // CALL(aFunction11b236);
    Function11b236(coord(7, 7, wram->wTilemap), wram->wc7d3[0] * 2, 0xb, 0);
    // LD_A_addr(wc7d0);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPokedexOrder);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    uint8_t* de = wram->wPokedexOrder + wram->wc7d0[0];
    // hlcoord(11, 2, wTilemap);
    tile_t* hl = coord(7, 8, wram->wTilemap);
    // LD_A_addr(wc7d3);
    uint8_t a = wram->wc7d3[0];

    do {
    // loop:
        // PUSH_AF;
        // LD_A_de;
        // LD_addr_A(wTempSpecies);
        wram->wTempSpecies = *de;
        // PUSH_DE;
        // PUSH_HL;
        // CALL(aFunction11b099_PlaceMonNameOrPlaceholderString);
        Function11b099_PlaceMonNameOrPlaceholderString(hl, *de);
        // POP_HL;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_DE;
        de++;
        // INC_DE;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // RET;
}

void Function11b0ff(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto asm_11b141;
    if(hram.hJoyPressed & B_BUTTON) {
    // asm_11b141:
        // LD_HL(wJumptableIndex);
        // LD_A(0x7);
        // LD_hl_A;
        wram->wJumptableIndex = 0x7;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto asm_11b131;
    else if(hram.hJoyPressed & A_BUTTON) {
    // asm_11b131:
        // CALL(aFunction11b20b);
        Function11b20b();
        // CALL(aCheckSeenMemMon);
        bool seenMon = CheckSeenMemMon();
        // IF_Z goto asm_11b13d;
        // LD_A(0x1);
        // goto asm_11b148;
    
    // asm_11b13d:
        // LD_A(0x2);
        // goto asm_11b148;
    
    // asm_11b148:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_addr_A(wcd4b);
        wram->wcd4b = (seenMon)? 0x1: 0x2;
        // AND_A_A;
        // IF_Z goto asm_11b16c;
        // LD_A_addr(wcf65);
        // CP_A(0x0);
        // IF_Z goto asm_11b163;
        if(wram->wcf65 == 0)
            wram->wcd30 = 0x1;
        // CP_A(0xfe);
        // IF_Z goto asm_11b167;
        else if(wram->wcf65 == 0xfe)
            wram->wcd30 = 0x2;
        // CP_A(0xff);
        // IF_Z goto asm_11b16b;
        else if(wram->wcf65 == 0xff)
            wram->wcd30 = 0x0;
        else {
            // JP(mFunction11ad8a);
            return Function11ad8a();
        }
    
    // asm_11b163:
        // LD_A(0x1);
        // goto asm_11b16c;

    // asm_11b167:
        // LD_A(0x2);
        // goto asm_11b16c;
    
    // asm_11b16b:
        // XOR_A_A;
    
    // asm_11b16c:
        // LD_addr_A(wcd30);
        // LD_A(0x4);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x4;
        // RET;    
        return;
    }
    // CALL(aFunction11b175);
    // IF_NC goto asm_11b125;
    else if(Function11b175()) {
        // LD_A_addr(wcd4c);
        // INC_A;
        // AND_A(0x3);
        // LD_addr_A(wcd4c);
        wram->wcd4c = (wram->wcd4c + 1) & 0x3;
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_NONE;
        // CALL(aFunction11b099);
        Function11b099();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // RET;
    }
    else {
    // asm_11b125:
        // LD_A_addr(wcd4c);
        // AND_A_A;
        // RET_Z ;
        if(wram->wcd4c == 0)
            return;
        // INC_A;
        // AND_A(0x3);
        // LD_addr_A(wcd4c);
        wram->wcd4c = (wram->wcd4c + 1) & 0x3;
        // RET;
    }
}

bool Function11b175(void){
    // LD_A_addr(wc7d3);
    // LD_D_A;
    uint8_t d = wram->wc7d3[0];
    // LD_A_addr(wc7d2);
    // LD_E_A;
    uint8_t e = wram->wc7d2[0];
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto asm_11b19a;
    if(hram.hJoyLast & D_UP) {
    // asm_11b19a:
        // LD_HL(wc7d1);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto asm_11b1a4;
        if(wram->wc7d1[0] == 0) {
        // asm_11b1a4:
            // LD_HL(wc7d0);
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto asm_11b1ed;
            if(wram->wc7d0[0] == 0)
                return false;
            // DEC_hl;
            --wram->wc7d0[0];
            // goto asm_11b1ef;        
        }
        else {
            // DEC_hl;
            --wram->wc7d1[0];
            // goto asm_11b1ef;
        }
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto asm_11b1ae;
    else if(hram.hJoyLast & D_DOWN) {
    // asm_11b1ae:
        // LD_HL(wc7d1);
        // LD_A_hl;
        uint8_t a = wram->wc7d1[0] + 1;
        // INC_A;
        // CP_A_E;
        // IF_NC goto asm_11b1ed;
        if(a >= e)
            return false;
        // CP_A_D;
        // IF_NC goto asm_11b1bc;
        else if(a >= d) {
        // asm_11b1bc:
            // LD_HL(wc7d0);
            // ADD_A_hl;
            // CP_A_E;
            // IF_NC goto asm_11b1ed;
            if(wram->wc7d0[0] + a >= e)
                return false;
            // INC_hl;
            wram->wc7d0[0]++;
            // goto asm_11b1ef;
        }
        else {
            // INC_hl;
            wram->wc7d1[0]++;
        }
        // goto asm_11b1ef;
    }
    // LD_A_D;
    // CP_A_E;
    // IF_NC goto asm_11b1ed;
    else if(d >= e)
        return false;
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto asm_11b1c6;
    else if(hram.hJoyLast & D_LEFT) {
    // asm_11b1c6:
        // LD_HL(wc7d0);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto asm_11b1ed;
        if(wram->wc7d0[0] == 0)
            return false;
        // CP_A_D;
        // IF_NC goto asm_11b1d4;
        if(wram->wc7d0[0] >= d) {
        // asm_11b1d4:
            // SUB_A_D;
            // LD_hl_A;
            wram->wc7d0[0] -= d;
            // goto asm_11b1ef;
        }
        else {
            // XOR_A_A;
            // LD_hl_A;
            wram->wc7d0[0] = 0;
        }
        // goto asm_11b1ef;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto asm_11b1d8;
    else if(hram.hJoyLast & D_RIGHT) {
    // asm_11b1d8:
        // LD_HL(wc7d0);
        // LD_A_D;
        // ADD_A_A;
        // ADD_A_hl;
        uint8_t carry = 0;
        uint8_t a = AddCarry8(d * 2, wram->wc7d0[0], carry, &carry);
        // IF_C goto asm_11b1e3;
        // CP_A_E;
        // IF_C goto asm_11b1e8;
        if(carry || a >= e) {
        // asm_11b1e3:
            // LD_A_E;
            // SUB_A_D;
            // LD_hl_A;
            wram->wc7d0[0] = e - d;
            // goto asm_11b1ef;
        }
        else {
        // asm_11b1e8:
            // LD_A_hl;
            // ADD_A_D;
            // LD_hl_A;
            wram->wc7d0[0] += d;
        }
        // goto asm_11b1ef;
    }
    // goto asm_11b1ed;
    else {
    // asm_11b1ed:
        // AND_A_A;
        // RET;
        return false;
    }

// asm_11b1ef:
    // CALL(aFunction11b295);
    Function11b295();
    // CALL(aFunction11b275);
    Function11b275();
    // SCF;
    // RET;
    return true;
}

void FillScreenWithTile32(void){
//  //  unreferenced
    hlcoord(0, 0, wTilemap);
    LD_A(0x32);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    RET;

}

void CopyDataUntilFF(void){
//  //  unreferenced

loop:
    LD_A_de;
    CP_A(0xff);
    RET_Z ;
    INC_DE;
    LD_hli_A;
    goto loop;
}

void Function11b20b(void){
    // LD_A_addr(wc7d1);
    // LD_HL(wc7d0);
    // ADD_A_hl;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(0xc6d0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wTempSpecies);
    wram->wTempSpecies = wram->wc6d0[wram->wc7d0[0] + wram->wc7d1[0]];
    // RET;
}

bool CheckCaughtMemMon(void){
    // PUSH_DE;
    // PUSH_HL;
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // CALL(aCheckCaughtMon);
    // POP_HL;
    // POP_DE;
    // RET;
    return CheckCaughtMon(wram->wTempSpecies - 1);
}

bool CheckSeenMemMon(void){
    // PUSH_DE;
    // PUSH_HL;
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // CALL(aCheckSeenMon);
    // POP_HL;
    // POP_DE;
    // RET;
    return CheckSeenMon(wram->wTempSpecies - 1);
}

void Function11b236(uint8_t* hl, uint8_t b, uint8_t c, uint8_t a){
    // JP(mFillBoxWithByte);
    FillBoxWithByte(hl, c, b, a);
}

// DoJumptable?
void Function11b239(void){
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;
}

void Function11b242(void){
    // hlcoord(3, 4, wTilemap);
    // LD_DE(wStringBuffer3);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wStringBuffer3, coord(8, 2, wram->wTilemap));
    // XOR_A_A;
    // LD_addr_A(wMonType);
    // FARCALL(aGetGender);
    u8_flag_s res = GetGender(0);
    // hlcoord(1, 4, wTilemap);
    tile_t* hl = coord(6, 2, wram->wTilemap);
    // LD_A_addr(wCurPartySpecies);
    // LD_BC(wcd2f);
    uint8_t* bc = &wram->wcd2f;
    // LD_bc_A;
    *bc = wram->wCurPartySpecies;
    // DEC_BC;
    bc--;
    // JR_C (masm_11b26a);
    if(res.flag)
        return asm_11b26a(hl, bc);
    // JR_Z (masm_11b26f);
    else if(res.a == 0)
        return asm_11b26f(hl, bc);
    // LD_A(0x1);
    // LD_bc_A;
    *bc = 0x1;

    return Function11b267(hl);
}

void Function11b267(tile_t* hl){
    // LD_hl(0xef);
    *hl = 0xef;
    // RET;
}

void asm_11b26a(tile_t* hl, uint8_t* bc){
    // XOR_A_A;
    // LD_bc_A;
    *bc = 0;
    // LD_hl(0x7f);
    *hl = 0x7f;
    // RET;
}

void asm_11b26f(tile_t* hl, uint8_t* bc){
    // LD_A(0x2);
    // LD_bc_A;
    *bc = 0x2;

    return Function11b272(hl);
}

void Function11b272(tile_t* hl){
    // LD_hl(0xf5);
    *hl = 0xf5;
    // RET;
}

void Function11b275(void){
    // CALL(aFunction11b279);
    Function11b279();
    // RET;
}

void Function11b279(void){
    // LD_A_addr(wTempSpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wTempSpecies;
    // CALL(aCheckSeenMemMon);
    // IF_Z goto asm_11b28f;
    if(CheckSeenMemMon()) {
        // CALL(aGetBaseData);
        GetBaseData(wram->wCurSpecies);
        // LD_A_addr(wBaseGender);
        // LD_addr_A(wcf65);
        wram->wcf65 = wram->wBaseGender;
        // goto asm_11b294;
    }
    else {
    // asm_11b28f:
        // LD_A(0xff);
        // LD_addr_A(wcf65);
        wram->wcf65 = 0xff;
    }

// asm_11b294:
    // RET;
}

void Function11b295(void){
    // hlcoord(4, 13, wTilemap);
    // LD_DE(mString_11b308);
    // CALL(aPlaceString);
    // PlaceStringSimple(U82C(String_11b308), coord(4, 13, wram->wTilemap));
    // hlcoord(4, 14, wTilemap);
    // LD_DE(mString_11b308);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11b308), coord(8, 4, wram->wTilemap));
    // CALL(aFunction11b20b);
    Function11b20b();
    // CALL(aCheckSeenMemMon);
    // IF_Z goto asm_11b2d1;
    uint8_t* de;
    tile_t* hl;
    if(CheckSeenMemMon()) {
        // LD_A_addr(0xc608);
        // LD_C_A;
        // LD_A_addr(0xc608 + 1);
        // LD_B_A;
        uint8_t* bc = GBToRAMAddr(wram->wc608[0] | (wram->wc608[1] << 8));
        // LD_HL(0x0007);
        // ADD_HL_BC;
        // XOR_A_A;
        // LD_hl_A;
        bc[0x0007] = 0;
        // LD_HL(0x0003);
        // ADD_HL_BC;
        // LD_E_hl;
        // FARCALL(aFlyFunction_GetMonIcon);
        FlyFunction_GetMonIcon(bc[0x0003]);
        // hlcoord(4, 14, wTilemap);
        // PUSH_HL;
        hl = coord(8, 4, wram->wTilemap);
        // CALL(aGetPokemonName);
        de = GetPokemonName(wram->wTempSpecies);
        // goto asm_11b2e7;
    }
    else {
    // asm_11b2d1:
        // LD_A_addr(0xc608);
        // LD_C_A;
        // LD_A_addr(0xc608 + 1);
        // LD_B_A;
        uint8_t* bc = GBToRAMAddr(wram->wc608[0] | (wram->wc608[1] << 8));
        // LD_HL(0x0007);
        // ADD_HL_BC;
        // LD_A(0x50);
        // LD_hl_A;
        bc[0x0007] = 0x60;
        // hlcoord(4, 13, wTilemap);
        // PUSH_HL;
        hl = coord(8, 4, wram->wTilemap);
        // LD_DE(mString_11b30e);
        de = U82C(String_11b30e);
    }

// asm_11b2e7:
    // LD_A(0x6);
    uint8_t a = MON_NAME_LENGTH;
    // LD_BC(wStringBuffer4);
    uint8_t* bc = wram->wStringBuffer4;

    do {
    // asm_11b2ec:
        // PUSH_AF;
        // LD_A_de;
        // LD_bc_A;
        *bc = *de;
        // INC_DE;
        de++;
        // INC_BC;
        bc++;
        // POP_AF;
        // DEC_A;
        // AND_A_A;
        // IF_NZ goto asm_11b2ec;
    } while(--a != 0);
    // POP_HL;
    // LD_DE(wStringBuffer4);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wStringBuffer4, hl);
    // RET;
}

void String_11b2fe(void){
//  //  unreferenced
    //db ['"あげる#@"'];
}

void String_11b303(void){
//  //  unreferenced
    //db ['"ほしい#@"'];
}

const char String_11b308[] = "          "; //db ['"\u3000\u3000\u3000\u3000\u3000@"'];
const char String_11b30e[] = "?????"; //db ['"みはっけん@"'];

void Function11b314(void){
    // CALL(aFunction11b31b);
    Function11b31b();
    // CALL(aFunction11b3d9);
    Function11b3d9();
    // RET;
}

void Function11b31b(void){
    static const uint8_t Coords[] = {
        dbpixel4( 9,  7, 0, 7),  //  0
        dbpixel4( 9,  8, 0, 7),  //  1
        dbpixel4( 9,  9, 0, 6),  //  2

        dbpixel4( 9, 15, 0, 9),  //  3
        dbpixel4( 9, 17, 0, 0),  //  4
        dbpixel4( 9, 18, 0, 0),  //  5
        dbpixel4(10,  7, 6, 7),  //  6
        dbpixel4(10,  8, 6, 7),  //  7
        dbpixel4(10,  9, 6, 6),  //  8
        dbpixel4(10, 15, 6, 9),  //  9
        dbpixel4(10, 17, 6, 0),  // 10
        dbpixel4(10, 18, 6, 0),  // 11
        // dbpixel4(4, 16, 2, 6),  // 12
        // dbpixel4(4, 17, 2, 6),  // 13
        (uint8_t)-1,
    };
    
    static const uint8_t Tilemap1[] = {
    //   //  vtiles
        0x30,  //  0
        0x31,  //  1
        0x4c,  //  2
        0x4d,  //  3
        0x31,  //  4
        0x32,  //  5
        0x40,  //  6
        0x41,  //  7
        0x4e,  //  8
        0x4f,  //  9
        0x41,  // 10
        0x42,  // 11
        0x41,  // 12
        0x42,  // 13
    };
    
    static const uint8_t Tilemap2[] = {
    //   //  vtiles
        0x30,  //  0
        0x31,  //  1
        0x4c,  //  2
        0x39,  //  3
        0x39,  //  4
        0x39,  //  5
        0x40,  //  6
        0x41,  //  7
        0x4e,  //  8
        0x39,  //  9
        0x39,  // 10
        0x39,  // 11
        0x39,  // 12
        0x39,  // 13
    };
    
    static const uint8_t Tilemap3[] = {
    //   //  vtiles
        0x39,  //  0
        0x39,  //  1
        0x39,  //  2
        0x39,  //  3
        0x39,  //  4
        0x39,  //  5
        0x39,  //  6
        0x39,  //  7
        0x39,  //  8
        0x39,  //  9
        0x39,  // 10
        0x39,  // 11
        0x39,  // 12
        0x39,  // 13
    };
    // LD_HL(mFunction11b31b_Coords);
    const uint8_t* hl = Coords;
    const uint8_t* bc;
    // LD_A_addr(wJumptableIndex);
    // CP_A(2);
    // IF_C goto tilemap_1;
    if(wram->wJumptableIndex < 2)
        bc = Tilemap1;
    // LD_A_addr(wc7d1);
    // CP_A(4);
    // IF_NC goto tilemap_3;
    else if(wram->wc7d1[0] >= 4)
        bc = Tilemap3;
    // CP_A(3);
    // IF_C goto tilemap_1;
    else if(wram->wc7d1[0] < 3)
        bc = Tilemap1;
    // LD_A_addr(wJumptableIndex);
    // CP_A(2);
    // IF_Z goto tilemap_1;
    // CP_A(3);
    // IF_Z goto tilemap_1;
    // CP_A(6);
    // IF_Z goto tilemap_1;
    else if(wram->wJumptableIndex == 2
        ||  wram->wJumptableIndex == 3
        ||  wram->wJumptableIndex == 6) {
        bc = Tilemap1;
    }

    else {
        // LD_BC(mFunction11b31b_Tilemap2);
        // goto load_sprites;
        bc = Tilemap2;
    }

// tilemap_3:
    // LD_BC(mFunction11b31b_Tilemap3);
    // goto load_sprites;

// tilemap_1:
    // LD_BC(mFunction11b31b_Tilemap1);

// load_sprites:
    // CALL(aFunction11b397);
    Function11b397(hl, bc);
    // RET;
}

void Function11b397(const uint8_t* hl, const uint8_t* bc){
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;

    while(*hl != 0xff) {
    // loop:
        // LD_A_hl;
        // CP_A(0xff);
        // RET_Z ;
        // LD_A_addr(wc7d1);
        // AND_A(0x7);
        // SWAP_A;
        // ADD_A_hl;
        // INC_HL;
        // LD_de_A;  // y
        // INC_DE;
        de->yCoord = *hl + ((wram->wc7d1[0] & 0x7) << 4);
        hl++;

        // LD_A_hli;
        // LD_de_A;  // x
        // INC_DE;
        de->xCoord = *hl;
        hl++;

        // LD_A_bc;
        // INC_BC;
        // LD_de_A;  // tile id
        de->tileID = *(bc++);
        // INC_DE;
        // LD_A(0x5);
        // LD_de_A;  // attributes
        de->attributes = 0x5;
        // INC_DE;
        de++;
        // goto loop;
    }
}

void Function11b3b6(void){
//  //  unreferenced

loop:
    LD_A_hl;
    CP_A(-1);
    RET_Z ;
    LD_A_addr(wcd4d);
    AND_A(0x7);
    SWAP_A;
    ADD_A_hl;
    INC_HL;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    PUSH_HL;
    LD_L_C;
    LD_H_B;
    LD_A_addr(wcd4e);
    ADD_A_hl;
    INC_BC;
    LD_de_A;
    INC_DE;
    POP_HL;
    LD_A(0x5);
    LD_de_A;
    INC_DE;
    goto loop;
}

void Function11b3d9(void){
    // LD_DE(wVirtualOAMSprite28);
    // PUSH_DE;
    struct SpriteOAM* de = wram->wVirtualOAMSprite + 28;
    // LD_A_addr(wc7d2);
    // DEC_A;
    // LD_E_A;
    uint8_t e = wram->wc7d2[0] - 1;
    uint8_t b;
    // LD_A_addr(wc7d1);
    // LD_HL(wc7d0);
    // ADD_A_hl;
    uint8_t a = wram->wc7d1[0] + wram->wc7d0[0];
    // CP_A_E;
    // IF_Z goto skip;
    if(a != e) {
        // LD_HL(0);
        // LD_BC(0x70);
        // CALL(aAddNTimes);
        // LD_E_L;
        // LD_D_H;
        uint16_t de = 0x70 * a;
        // LD_B(0);
        b = 0;
        // LD_A_D;
        // OR_A_E;
        // IF_Z goto load_sprites;
        if(de != 0) {
            // LD_A_addr(wc7d2);
            // LD_C_A;

        // loop1:
            // LD_A_E;
            // SUB_A_C;
            // LD_E_A;
            // LD_A_D;
            // SBC_A(0x0);
            // LD_D_A;
            // IF_C goto load_sprites;
            // INC_B;
            // goto loop1;
            b = de / wram->wc7d2[0];
        }
    }
    else {
    // skip:
        // LD_B(14 * 8);
        b = 14 * 8;
    }

// load_sprites:
    // LD_A(2 * 8 + 5);
    // ADD_A_B;
    a = b + (2 * 8 + 5);
    // POP_HL;
    // LD_hli_A;
    de->yCoord = a;
    // CP_A(0x41);
    // IF_C goto version1;
    // LD_A_addr(wJumptableIndex);
    // CP_A(4);
    // IF_Z goto version2;
    // CP_A(5);
    // IF_Z goto version2;
    // CP_A(7);
    // IF_Z goto version2;
    // CP_A(8);
    // IF_Z goto version2;
    if(a >= 0x41
        && (wram->wJumptableIndex == 4
        ||  wram->wJumptableIndex == 5
        ||  wram->wJumptableIndex == 7
        ||  wram->wJumptableIndex == 8)) {
    // version2:
        // LD_A(19 * 8 + 3);
        // LD_hli_A;
        de->xCoord = 19 * 8 + 3;
        // LD_A(0x39);
        // LD_hli_A;
        de->tileID = 0x39;
        // XOR_A_A;
        // LD_hl_A;
        de->attributes = 0;
        // RET;
    }
    else {
    // version1:
        // LD_A(19 * 8 + 3);
        // LD_hli_A;
        de->xCoord = 19 * 8 + 3;
        // LD_A_addr(wcd4c);
        // ADD_A(0x3c);
        // LD_hli_A;
        de->tileID = wram->wcd4c + 0x3c;
        // LD_A_addr(wcd4c);
        // ADD_A(0x1);
        // LD_hl_A;
        de->attributes = wram->wcd4c + 0x1;
        // RET;
    }
}

// Mobile_SendGTSMonDataSpecial
void Function11b444(void){
//  special
    // CALL(aMobile46_InitJumptable);
    Mobile46_InitJumptable();
    // CALL(aMobile46_RunJumptable);
    Mobile46_RunJumptable();
    // RET;
}

void Mobile46_InitJumptable(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // LD_addr_A(wcf64);
    wram->wcf64 = 0;
    // LD_addr_A(wcf65);
    wram->wcf65 = 0;
    // LD_addr_A(wcf66);
    wram->wcf66 = 0;
    // CALL(aUpdateTime);
    UpdateTime();
    // RET;
}

void Mobile46_RunJumptable(void){
    do {
    // loop:
        // CALL(aMobile46_RunJumptable_IterateJumptable);
        switch(wram->wJumptableIndex) {
        // IterateJumptable:
            //jumptable ['.Jumptable', 'wJumptableIndex']
        // Jumptable:
            case 0x0: Function11b483(); break; //dw ['Function11b483'];
            case 0x1: Function11b570(); break; //dw ['Function11b570'];
            case 0x2: Function11b5c0(); break;
            case 0x3: Function11b5e0(); break;
            //dw ['Function11b5e7'];  // unused
        }
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wJumptableIndex);
        // CP_A(4);
        // IF_NZ goto loop;
    } while(wram->wJumptableIndex != 4);
    // RET;
}

static void Function11b483_InitRAM(void){
    // LD_BC(0xc626);
    // LD_A_addr(wPlayerID);
    // LD_addr_A(wcd2a);
    // LD_bc_A;
    // INC_BC;

    // LD_A_addr(wPlayerID + 1);
    // LD_addr_A(wcd2b);
    // LD_bc_A;
    // INC_BC;
    wram->wOfferTrainerID = wram->wPlayerID;

    // LD_A_addr(wSecretID);
    // LD_addr_A(wcd2c);
    // LD_bc_A;
    // INC_BC;

    // LD_A_addr(wSecretID + 1);
    // LD_addr_A(wcd2d);
    // LD_bc_A;
    // INC_BC;
    wram->wOfferSecretID = wram->wSecretID;

    // LD_A_addr(wcd2e);
    // LD_bc_A;
    // INC_BC;
    wram->wOfferGender = wram->wcd2e;

    // LD_A_addr(wcd2f);
    // LD_bc_A;
    // INC_BC;
    wram->wOfferSpecies = wram->wcd2f;

    // LD_A_addr(wcd30);
    // LD_bc_A;
    // INC_BC;
    wram->wOfferReqGender = wram->wcd30;

    // LD_A_addr(wd265);
    // LD_bc_A;
    // INC_BC;
    wram->wOfferReqSpecies = wram->wd265;
    // RET;
}

// TradeCornerHoldMon_PrepareForUpload
void Function11b483(void){
    // CALL(aFunction11b483_InitRAM);
    Function11b483_InitRAM();
    // LD_HL(wPlayerName);
    // LD_A(NAME_LENGTH_JAPANESE - 1);

// loop1:
    // PUSH_AF;
    // LD_A_hli;
    // LD_bc_A;
    // INC_BC;
    // POP_AF;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop1;
    CopyBytes(wram->wOfferMonSender, wram->wPlayerName, PLAYER_NAME_LENGTH - 1);

    // LD_DE(PARTYMON_STRUCT_LENGTH);
    // LD_HL(wPartyMon1Species);
    // LD_A_addr(wcd82);
    // DEC_A;
    // PUSH_AF;

// loop2:
    // AND_A_A;
    // IF_Z goto okay;
    // ADD_HL_DE;
    // DEC_A;
    // goto loop2;


// okay:
    // PUSH_BC;
    // LD_A(PARTYMON_STRUCT_LENGTH);

// loop3:
    // PUSH_AF;
    // LD_A_hli;
    // LD_bc_A;
    // INC_BC;
    // POP_AF;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop3;
    CopyBytes(&wram->wOfferMon, wram->wPartyMon + (wram->wcd82[0] - 1), sizeof(wram->wOfferMon));

    // POP_DE;
    // PUSH_BC;
    // LD_A_de;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wOfferMon.mon.species;
    // CALL(aGetBaseData);
    GetBaseData(wram->wOfferMon.mon.species);
    // LD_HL(MON_LEVEL);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = wram->wOfferMon.mon.level;
    // LD_HL(MON_MAXHP);
    // ADD_HL_DE;
    // PUSH_HL;
    // LD_HL(MON_STAT_EXP - 1);
    // ADD_HL_DE;
    // POP_DE;
    // PUSH_DE;
    // LD_B(TRUE);
    // PREDEF(pCalcMonStats);
    CalcMonStats_PartyMon(&wram->wOfferMon, TRUE);
    // POP_DE;
    // LD_H_D;
    // LD_L_E;
    // DEC_HL;
    // DEC_HL;
    // LD_A_de;
    // LD_hli_A;
    // INC_DE;
    // LD_A_de;
    // LD_hl_A;
    // POP_BC;
    // LD_DE(NAME_LENGTH);
    // LD_HL(wPartyMonOTs);
    // POP_AF;
    // PUSH_AF;

// loop4:
    // AND_A_A;
    // IF_Z goto okay2;
    // ADD_HL_DE;
    // DEC_A;
    // goto loop4;

// okay2:
    // LD_A(NAME_LENGTH - 1);

// loop5:
    // PUSH_AF;
    // LD_A_hli;
    // LD_bc_A;
    // INC_BC;
    // POP_AF;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop5;
    CopyBytes(wram->wOfferMonOT, wram->wPartyMonOT[wram->wcd82[0] - 1], PLAYER_NAME_LENGTH - 1);
    // LD_DE(NAME_LENGTH);
    // LD_HL(wPartyMonNicknames);
    // POP_AF;
    // PUSH_AF;

// loop6:
    // AND_A_A;
    // IF_Z goto okay3;
    // ADD_HL_DE;
    // DEC_A;
    // goto loop6;

// okay3:
    // LD_A(NAME_LENGTH - 1);

// loop7:
    // PUSH_AF;
    // LD_A_hli;
    // LD_bc_A;
    // INC_BC;
    // POP_AF;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop7;
    CopyBytes(wram->wOfferMonNick, wram->wPartyMonNickname[wram->wcd82[0] - 1], NAME_LENGTH - 1);
    // LD_DE(MAIL_STRUCT_LENGTH);
    // LD_HL(sPartyMail);
    // POP_AF;

// loop8:
    // AND_A_A;
    // IF_Z goto okay4;
    // ADD_HL_DE;
    // DEC_A;
    // goto loop8;

// okay4:
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asPartyMail));
    struct MailMsg* mail = (struct MailMsg*)GBToRAMAddr(sPartyMail);
    // LD_A(MAIL_STRUCT_LENGTH);

// loop9:
    // PUSH_AF;
    // LD_A_hli;
    // LD_bc_A;
    // INC_BC;
    // POP_AF;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop9;
    CopyBytes(&wram->wOfferMonMail, mail + (wram->wcd82[0] - 1), sizeof(wram->wOfferMonMail));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // JP(mFunction11ad8a);
    Function11ad8a();
}

static void Function11b570_SaveData(void){
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);

    // LD_HL(w3_d800);
    // LD_DE(0xc608);
    // LD_BC(w3_d88f - w3_d800);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, wram->w3_d800, 0x8f);

    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_A(BANK(s5_a800));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_a800));

    // LD_DE(s5_a800);
    // LD_A(0x1);
    // LD_de_A;
    gb_write(s5_a800, 1);
    // INC_DE;
    // LD_HL(0xc608);
    // LD_BC(w3_d88f - w3_d800);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_a800 + 1), wram->wc608, 0x8f);

    // PUSH_DE;
    // POP_HL;
    uint8_t* hl = GBToRAMAddr(s5_a800 + 0x90);

    // LDH_A_addr(hRTCMinutes);
    // LD_hli_A;
    *(hl++) = hram.hRTCMinutes;
    // LDH_A_addr(hRTCHours);
    // LD_hli_A;
    *(hl++) = hram.hRTCHours;
    // LDH_A_addr(hRTCDayLo);
    // LD_hli_A;
    *(hl++) = hram.hRTCDayLo;
    // LDH_A_addr(hRTCDayHi);
    // LD_hl_A;
    *(hl++) = hram.hRTCDayHi;

    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void Function11b570(void){
    // CALL(aFunction118007);
    Function118007();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_NZ goto exit;
    if(wram->wScriptVar == 0) {
        // CALL(aFunction11b570_SaveData);
        Function11b570_SaveData();
        // JP(mFunction11ad8a);
        return Function11ad8a();
    }
    else {
    // exit:
        // LD_A(0x4);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x4;
        // RET;
        return;
    }
}

// TradeCornerHoldMon_RemoveFromParty
void Function11b5c0(void){
    // LD_A_addr(wcd82);
    // DEC_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wcd82[0] - 1;
    // XOR_A_A;  // REMOVE_PARTY
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // FARCALL(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox(REMOVE_PARTY);
    // FARCALL(aFunction170807);
    Function170807();
    // FARCALL(aSaveAfterLinkTrade);
    SaveAfterLinkTrade();
    // JP(mFunction11ad8a);
    return Function11ad8a();
}

// TradeCornerHoldMon_Success
void Function11b5e0(void){
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // JP(mFunction11ad8a);
    return Function11ad8a();
}

// TradeCornerHoldMon_Noop
void Function11b5e7(void){
    // RET;
}

void Function11b5e8(void){
    // LD_A(0x0);
    // CALL(aOpenSRAM);
    OpenSRAM(0x0);
    // LD_HL(wRTC);
    // LD_DE(0xc608);
    // LD_BC(4);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, wram->wRTC, 4);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_b08c));
    // LD_HL(0xc608);
    // LD_DE(0xb08c);
    // LD_BC(4);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b08c), wram->wRTC, 4);
    // LD_A(0x2);
    // LD_addr_A(0xa800);
    gb_write(s5_a800, 0x2);
    // LD_A_addr(0xa81f);
    // LD_addr_A(wcd2a);
    // LD_A_addr(0xa820);
    // LD_addr_A(wcd2b);
    // LD_A_addr(0xa821);
    // LD_addr_A(wcd2c);
    // LD_A_addr(0xa822);
    // LD_addr_A(wcd2d);
    // LD_A_addr(0xa823);
    // LD_addr_A(wcd2e);
    // LD_A_addr(0xa824);
    // LD_addr_A(wcd2f);
    // LD_A_addr(0xa825);
    // LD_addr_A(wcd30);
    // LD_A_addr(0xa826);
    // LD_addr_A(wcd31);
    CopyBytes(&wram->wcd2a, GBToRAMAddr(s5_a800 + 0x1f), 8);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aMobile46_InitJumptable);
    Mobile46_InitJumptable();
    // CALL(aFunction11b5e8_loop);
    // RET;
    do {
    // loop:
        // CALL(aFunction11b5e8_RunJumptable);
        switch(wram->wJumptableIndex) {
        // RunJumptable:
            //jumptable ['.Jumptable', 'wJumptableIndex']
        // Jumptable:
            case 0: return Function11b66d();
            case 1: return Function11b6b3();
        }
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wJumptableIndex);
        // CP_A(0x1);
        // IF_NZ goto loop;
    } while(wram->wJumptableIndex != 0x1);
    // RET;
}

void Function11b66d(void){
    // CALL(aFunction1180b8);
    Function1180b8();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_NZ goto asm_11b6b0;
    if(wram->wScriptVar != 0)
        return Function11ad8a();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    // LD_A_addr(w3_d090);
    // LD_B_A;
    uint8_t b = wram->w3_d090[0];
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto asm_11b691;
    if(b != 0) {
        // CP_A(0x1);
        // IF_NZ goto asm_11b6b0;
        if(b == 0x1) {
            // CALL(aFunction11b6b4);
            Function11b6b4();
        }
        // goto asm_11b6b0;
        return Function11ad8a();
    }

// asm_11b691:
    // FARCALL(aFunction17081d);
    Function17081d();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_Z goto asm_11b6b0;
    if(wram->wScriptVar == 0)
        return Function11ad8a();
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);
    // LD_A(0x2);
    // LD_addr_A(w3_d090);
    wram->w3_d090[0] = 0x2;
    // POP_AF;
    // LDH_addr_A(rSVBK);

// asm_11b6b0:
    // JP(mFunction11ad8a);
    return Function11ad8a();
}

void Function11b6b3(void){
    // RET;

}

// SanitizeMobileMonAndAddItToParty
void Function11b6b4(void){
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    // LD_A_addr(wcd30);
    // LD_addr_A(0xc708);
    wram->wc708 = wram->wcd30;
    // LD_A_addr(wcd31);
    // LD_addr_A(0xc709);
    wram->wc709 = wram->wcd31;

    // LD_A(LOW(0xc708));  // Species
    // LD_addr_A(wMobileMonSpeciesPointer);
    // LD_A(HIGH(0xc708));
    // LD_addr_A(wMobileMonSpeciesPointer + 1);

    // LD_A(LOW(0xc60d));  // Partymon Struct
    // LD_addr_A(wMobileMonStructPointer);
    // LD_A(HIGH(0xc60d));
    // LD_addr_A(wMobileMonStructPointer + 1);

    // LD_A(LOW(0xc63d));  // OT
    // LD_addr_A(wMobileMonOTPointer);
    // LD_A(HIGH(0xc63d));
    // LD_addr_A(wMobileMonOTPointer + 1);

    // LD_A(LOW(0xc642));  // Nickname
    // LD_addr_A(wMobileMonNicknamePointer);
    // LD_A(HIGH(0xc642));
    // LD_addr_A(wMobileMonNicknamePointer + 1);

    // LD_A(LOW(0xc647));  // Mail
    // LD_addr_A(wMobileMonMailPointer);
    // LD_A(HIGH(0xc647));
    // LD_addr_A(wMobileMonMailPointer + 1);

    // LD_A(0x46);
    // LD_addr_A(0xc628);
    wram->wMobileMon.mon.happiness = BASE_HAPPINESS;

    // LD_DE(0xc63d);
    // LD_C(5);
    // FARCALL(aCheckStringForErrors);
    // IF_NC goto length_check_OT;
    if(CheckStringForErrors(wram->wMobileMonOT, PLAYER_NAME_LENGTH - 1)) {
        // FARCALL(aMobile_CopyDefaultOTName);
        Mobile_CopyDefaultOTName();
    }

// length_check_OT:
    // LD_DE(0xc63d);
    // LD_BC((1 << 8) | 5);
    // FARCALL(aCheckStringContainsLessThanBNextCharacters);
    // IF_NC goto error_check_nick;
    if(CheckStringContainsLessThanBNextCharacters(wram->wMobileMonOT, 1, PLAYER_NAME_LENGTH - 1).flag) {
        // FARCALL(aMobile_CopyDefaultOTName);
        Mobile_CopyDefaultOTName();
    }

// error_check_nick:
    // LD_DE(0xc642);
    // LD_C(5);
    // FARCALL(aCheckStringForErrors);
    // IF_NC goto length_check_nick;
    if(CheckStringForErrors(wram->wMobileMonName, MON_NAME_LENGTH - 1)) {
        // FARCALL(aMobile_CopyDefaultNickname);
        Mobile_CopyDefaultNickname();
    }

// length_check_nick:
    // LD_DE(0xc642);
    // LD_BC((1 << 8) | 5);
    // FARCALL(aCheckStringContainsLessThanBNextCharacters);
    // IF_NC goto error_check_mail;
    if(CheckStringContainsLessThanBNextCharacters(wram->wMobileMonName, 1, MON_NAME_LENGTH - 1).flag) {
        // FARCALL(aMobile_CopyDefaultNickname);
        Mobile_CopyDefaultNickname();
    }

// error_check_mail:
    // LD_DE(0xc647);
    // LD_C(MAIL_MSG_LENGTH + 1);
    // FARCALL(aCheckStringForErrors);
    // IF_NC goto length_check_mail;
    if(CheckStringForErrors(wram->wMobileMonMail.message, MAIL_MSG_LENGTH + 1)) {
        // FARCALL(aMobile_CopyDefaultMail);
        Mobile_CopyDefaultMail();
    }

// length_check_mail:
    // LD_DE(0xc647);
    // LD_BC((2 << 8) | (MAIL_MSG_LENGTH + 1));
    // FARCALL(aCheckStringContainsLessThanBNextCharacters);
    u8_flag_s res = CheckStringContainsLessThanBNextCharacters(wram->wMobileMonMail.message, 2, MAIL_MSG_LENGTH + 1);
    // IF_C goto fix_mail;
    // LD_A_B;
    // CP_A(0x2);
    // IF_NZ goto mail_ok;
    if(!res.flag && res.a == 0x2) {
    // fix_mail:
        // FARCALL(aMobile_CopyDefaultMail);
        Mobile_CopyDefaultMail();
    }

// mail_ok:
    // LD_DE(0xc668);
    // LD_C(0x5);
    // FARCALL(aCheckStringForErrors);
    // IF_NC goto length_check_author;
    if(CheckStringForErrors(wram->wMobileMonMail.author, PLAYER_NAME_LENGTH - 1)) {
        // FARCALL(aMobile_CopyDefaultMailAuthor);
        Mobile_CopyDefaultMailAuthor();
    }

// length_check_author:
    // LD_DE(0xc668);
    // LD_BC((1 << 8) | 5);
    // FARCALL(aCheckStringContainsLessThanBNextCharacters);
    // IF_NC goto author_okay;
    if(CheckStringContainsLessThanBNextCharacters(wram->wMobileMonName, 1, PLAYER_NAME_LENGTH - 1).flag) {
        // FARCALL(aMobile_CopyDefaultMailAuthor);
        Mobile_CopyDefaultMailAuthor();
    }

// author_okay:
    // LD_A_addr(0xc60e);
    // CP_A(-1);
    // IF_NZ goto item_okay;
    if(wram->wMobileMon.mon.item == (item_t)-1) {
        // XOR_A_A;
        // LD_addr_A(0xc60e);
        wram->wMobileMon.mon.item = NO_ITEM;
    }

// item_okay:
    // LD_A_addr(wcd31);
    // LD_addr_A(0xc60d);
    wram->wMobileMon.mon.species = wram->wcd31;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wcd31;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurSpecies);
    // LD_HL(0xc60d + MON_LEVEL);
    // LD_A_hl;
    // CP_A(MIN_LEVEL);
    // LD_A(MIN_LEVEL);
    // IF_C goto replace_level;
    if(wram->wMobileMon.mon.level < MIN_LEVEL)
        wram->wMobileMon.mon.level = MIN_LEVEL;
    // LD_A_hl;
    // CP_A(MAX_LEVEL);
    // IF_C goto done_level;
    else if(wram->wMobileMon.mon.level > MAX_LEVEL)
        wram->wMobileMon.mon.level = MAX_LEVEL;
    // LD_A(MAX_LEVEL);

// replace_level:
    // LD_hl_A;

// done_level:
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = wram->wMobileMon.mon.level;

    // LD_HL(0xc60d + MON_STAT_EXP - 1);
    // LD_DE(0xc60d + MON_MAXHP);
    // LD_B(TRUE);
    // PREDEF(pCalcMonStats);
    CalcMonStats_PartyMon(&wram->wMobileMon, TRUE);
    // LD_DE(0xc60d + MON_MAXHP);
    // LD_HL(0xc60d + MON_HP);
    // LD_A_de;
    // LD_hli_A;
    // INC_DE;
    // LD_A_de;
    // LD_hl_A;
    wram->wMobileMon.HP = wram->wMobileMon.maxHP;
    // CALL(aAddMobileMonToParty);
    AddMobileMonToParty(&wram->wMobileMon.mon.species, &wram->wMobileMon, wram->wMobileMonOT, wram->wMobileMonName, &wram->wMobileMonMail);
    // RET;
}

// ReceiveMonFromTradeCornerSpecial
void Function11b7e5(void){
    // LD_A_addr(0xc60d);  // species
    // LD_addr_A(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species = wram->wMobileMon.mon.species;
    // LD_A_addr(wcd81);
    // LD_addr_A(wc74e);
    wram->wc74e[0] = wram->wcd81[0];
    // LD_HL(0xc63d);  // OT
    // LD_DE(wOTTrademonOTName);
    // LD_BC(5);
    // CALL(aCopyBytes);
    CopyBytes(wram->wOTTrademon.otName, wram->wMobileMonOT, PLAYER_NAME_LENGTH - 1);
    // LD_A(0x50);
    // LD_de_A;
    wram->wMobileMonOT[PLAYER_NAME_LENGTH - 1] = 0x50;
    // LD_A_addr(0xc60d + MON_ID);  // id
    // LD_addr_A(wOTTrademonID);
    // LD_A_addr(0xc60d + MON_ID + 1);
    // LD_addr_A(wOTTrademonID + 1);
    wram->wOTTrademon.id = wram->wMobileMon.mon.id;
    // LD_HL(0xc60d + MON_DVS);  // dvs
    // LD_A_hli;
    // LD_addr_A(wOTTrademonDVs);
    // LD_A_hl;
    // LD_addr_A(wOTTrademonDVs + 1);
    wram->wOTTrademon.dvs = wram->wMobileMon.mon.DVs;
    // LD_BC(0xc60d);  // pokemon_data_start
    // FARCALL(aGetCaughtGender);
    // LD_A_C;
    // LD_addr_A(wOTTrademonCaughtData);
    wram->wOTTrademon.caughtData = GetCaughtGender(&wram->wMobileMon.mon);
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // CALL(aFadeToMenu);
    FadeToMenu();
    // FARCALL(aMobileTradeAnimation_ReceiveGetmonFromGTS);
    MobileTradeAnimation_ReceiveGetmonFromGTS();
    // FARCALL(aFunction17d1f1);
    Function17d1f1();
    // LD_A(0x1);
    // LD_addr_A(wForceEvolution);
    wram->wForceEvolution = TRUE;
    // LD_A(LINK_TRADECENTER);
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_TRADECENTER;
    // FARCALL(aEvolvePokemon);
    EvolvePokemon();
    // XOR_A_A;
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_NULL;
    // FARCALL(aSaveAfterLinkTrade);
    SaveAfterLinkTrade();
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_a800));
    // LD_A(0x5);
    // LD_addr_A(0xa800);
    gb_write(s5_a800, 0x5);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aGetMapSceneID);
    uint8_t* id = GetMapSceneID(wram->wMapGroup, wram->wMapNumber);
    // LD_A_D;
    // OR_A_E;
    // IF_Z goto asm_11b872;
    if(id) {
        // LD_A(0x1);
        // LD_de_A;
        *id = 0x1;
    }

// asm_11b872:
    // CALL(aCloseSubmenu);
    CloseSubmenu();
    // CALL(aRestartMapMusic);
    RestartMapMusic();
    // RET;
}

// Mobile_CheckTradeCornerStatusSpecial
//   - wScriptVar == 0x0 => No pokemon in trade corner
//   - wScriptVar == 0x1 => Pokemon left in trade corner a while ago
//   - wScriptVar == 0x2 => Pokemon left in trade corner recently
void Function11b879(void){
    // FARCALL(aBattleTower_CheckSaveFileExistsAndIsYours);
    BattleTower_CheckSaveFileExistsAndIsYours();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // RET_Z ;
    if(wram->wScriptVar == 0)
        return;
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_a800));
    // LD_A_addr(0xa800);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = gb_read(s5_a800);
    // LD_A_addr(0xa890);
    // LD_addr_A(wcd49);
    wram->wcd49 = gb_read(s5_a894 - 4);
    // LD_A_addr(0xa891);
    // LD_addr_A(wcd4a);
    wram->wcd4a = gb_read(s5_a894 - 3);
    // LD_A_addr(0xa892);
    // LD_addr_A(wcd4b);
    wram->wcd4b = gb_read(s5_a894 - 2);
    // LD_A_addr(0xa893);
    // LD_addr_A(wcd4c);
    wram->wcd4c = gb_read(s5_a894 - 1);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // RET_Z ;
    if(wram->wScriptVar == 0)
        return;
    // LD_HL(wcd4c);
    // LDH_A_addr(hRTCDayHi);
    // CP_A_hl;
    // RET_NZ ;
    if(hram.hRTCDayHi != wram->wcd4c)
        return;
    // DEC_HL;
    // LDH_A_addr(hRTCDayLo);
    // CP_A_hl;
    // RET_NZ ;
    if(hram.hRTCDayLo != wram->wcd4b)
        return;
    // LD_HL(wcd4a);
    // LDH_A_addr(hRTCHours);
    // CP_A_hl;
    // IF_NC goto asm_11b8d8;
    if(hram.hRTCHours < wram->wcd4a) {
        // LD_A(0x18);
        // SUB_A_hl;
        // LD_HL(hRTCHours);
        // ADD_A_hl;
        // LD_addr_A(wcd4c);
        wram->wcd4c = (24 - wram->wcd4a) + hram.hRTCHours;
        // LDH_A_addr(hRTCMinutes);
        // LD_addr_A(wcd4b);
        wram->wcd4b = hram.hRTCMinutes;
        // XOR_A_A;
        // LD_addr_A(wcd4a);
        wram->wcd4a = 0;
        // goto asm_11b8e2;
    }
    else {
    // asm_11b8d8:
        // LDH_A_addr(hRTCMinutes);
        // LD_addr_A(wcd4b);
        wram->wcd4b = hram.hRTCMinutes;
        // LDH_A_addr(hRTCHours);
        // LD_addr_A(wcd4c);
        wram->wcd4c = hram.hRTCHours;
    }

// asm_11b8e2:
    // XOR_A_A;
    // LD_L_A;
    // LD_H_A;
    // LD_B_A;
    // LD_D_A;
    // LD_A_addr(wcd4b);
    // LD_E_A;
    // LD_A_addr(wcd4c);
    // LD_C(0x3c);
    // CALL(aAddNTimes);
    // ADD_HL_DE;
    // PUSH_HL;
    uint16_t curr_mins = (wram->wcd4c * 60) + wram->wcd4b;
    // XOR_A_A;
    // LD_L_A;
    // LD_H_A;
    // LD_B_A;
    // LD_D_A;
    // LD_A_addr(wcd49);
    // LD_E_A;
    // LD_A_addr(wcd4a);
    // LD_C(0x3c);
    // CALL(aAddNTimes);
    // ADD_HL_DE;
    uint16_t deposited_mins = (wram->wcd4a * 60) + wram->wcd49;
    // LD_A_L;
    // CPL;
    // ADD_A(0x1);
    // LD_E_A;
    // LD_A_H;
    // CPL;
    // ADC_A(0);
    // LD_D_A;
    // POP_HL;
    // ADD_HL_DE;
    // LD_DE(0xff88);
    // ADD_HL_DE;
    int16_t diff = (int16_t)(curr_mins - deposited_mins);
    // BIT_H(7);
    // RET_Z ;
    if(diff < 120) {
        // LD_A(0x2);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x2;
    }
    // RET;
}

void Function11b920(void){
    // CALL(aMobile46_InitJumptable);
    Mobile46_InitJumptable();
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_a800));
    // LD_HL(0xa81f);
    // LD_DE(0xc626);
    // LD_BC(8);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wOfferTrainerID, GBToRAMAddr(s5_a800 + 0x1f), 8);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aFunction118000);
    Function118000();
    // RET;
}

void Function11b93b(void){
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as5_a800));
    // XOR_A_A;
    // LD_addr_A(0xa800);
    gb_write(s5_a800, 0);
    // LD_HL(0xa823);
    // LD_DE(0xc608);
    // LD_BC(0x008f);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wOfferGender, GBToRAMAddr(s5_a800 + 0x23), TRADE_CORNER_TRADE_REQUEST_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM();

    // LD_A(LOW(0xc608));
    // LD_addr_A(wMobileMonSpeciesPointer);
    // LD_A(HIGH(0xc608));
    // LD_addr_A(wMobileMonSpeciesPointer + 1);

    // LD_A(LOW(0xc611));
    // LD_addr_A(wMobileMonStructPointer);
    // LD_A(HIGH(0xc611));
    // LD_addr_A(wMobileMonStructPointer + 1);

    // LD_A(LOW(0xc641));
    // LD_addr_A(wMobileMonOTPointer);
    // LD_A(HIGH(0xc641));
    // LD_addr_A(wMobileMonOTPointer + 1);

    // LD_A(LOW(0xc646));
    // LD_addr_A(wMobileMonNicknamePointer);
    // LD_A(HIGH(0xc646));
    // LD_addr_A(wMobileMonNicknamePointer + 1);

    // LD_A(LOW(0xc64b));
    // LD_addr_A(wMobileMonMailPointer);
    // LD_A(HIGH(0xc64b));
    // LD_addr_A(wMobileMonMailPointer + 1);
    // CALL(aAddMobileMonToParty);
    AddMobileMonToParty(&wram->wOfferSpecies, &wram->wOfferMon, wram->wOfferMonOT, wram->wOfferMonNick, &wram->wOfferMonMail);
    // FARCALL(aSaveAfterLinkTrade);
    SaveAfterLinkTrade();
    // RET;
}

void AddMobileMonToParty(const species_t* species, const struct PartyMon* mobilemon, const uint8_t* ot, const uint8_t* nick, const struct MailMsg* mail){
    // LD_HL(wPartyCount);
    // LD_A_hl;
    // LD_E_A;
    // INC_hl;
    uint8_t e = wram->wPartyCount++;

    // LD_A_addr(wMobileMonSpeciesPointer);
    // LD_L_A;
    // LD_A_addr(wMobileMonSpeciesPointer + 1);
    // LD_H_A;
    // INC_HL;
    // LD_BC(wPartySpecies);
    species_t* bc = wram->wPartySpecies + e;
    // LD_D_E;

// loop1:
    // INC_BC;
    // DEC_D;
    // IF_NZ goto loop1;
    // LD_A_E;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = e;
    // LD_A_hl;
    // LD_bc_A;
    *bc = *species;
    // INC_BC;
    // LD_A(-1);
    // LD_bc_A;
    bc[1] = (species_t)-1;

    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    struct PartyMon* mon = wram->wPartyMon + e;
    // LD_A_E;
    // LD_addr_A(wMobileMonSpecies);
    wram->wMobileMonSpecies = e;

// loop2:
    // ADD_HL_BC;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop2;
    // LD_E_L;
    // LD_D_H;
    // LD_A_addr(wMobileMonStructPointer);
    // LD_L_A;
    // LD_A_addr(wMobileMonStructPointer + 1);
    // LD_H_A;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(mon, mobilemon, PARTYMON_STRUCT_LENGTH);

    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // LD_A_addr(wMobileMonSpecies);
    uint8_t* ot2 = wram->wPartyMonOT[e];

// loop3:
    // ADD_HL_BC;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop3;
    // LD_E_L;
    // LD_D_H;
    // LD_A_addr(wMobileMonOTPointer);
    // LD_L_A;
    // LD_A_addr(wMobileMonOTPointer + 1);
    // LD_H_A;
    // LD_BC(MON_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes(ot2, ot, MON_NAME_LENGTH - 1);
    // LD_A(0x50);
    // LD_de_A;
    ot2[MON_NAME_LENGTH - 1] = 0x50;

    // LD_HL(wPartyMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // LD_A_addr(wMobileMonSpecies);
    uint8_t* nickname2 = wram->wPartyMonNickname[e];

// loop4:
    // ADD_HL_BC;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop4;
    // LD_E_L;
    // LD_D_H;
    // LD_A_addr(wMobileMonNicknamePointer);
    // LD_L_A;
    // LD_A_addr(wMobileMonNicknamePointer + 1);
    // LD_H_A;
    // LD_BC(MON_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes(nickname2, nick, MON_NAME_LENGTH - 1);
    // LD_A(0x50);
    // LD_de_A;
    nickname2[MON_NAME_LENGTH - 1] = 0x50;

    // LD_HL(sPartyMail);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // LD_A_addr(wMobileMonSpecies);

// loop5:
    if(mail != NULL) {
        // ADD_HL_BC;
        // DEC_A;
        // AND_A_A;
        // IF_NZ goto loop5;
        // LD_A(BANK(sPartyMail));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asPartyMail));
        // LD_E_L;
        // LD_D_H;
        // LD_A_addr(wMobileMonMailPointer);
        // LD_L_A;
        // LD_A_addr(wMobileMonMailPointer + 1);
        // LD_H_A;
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(GBToRAMAddr(sPartyMail + MAIL_STRUCT_LENGTH * e), mail, MAIL_STRUCT_LENGTH);

        // CALL(aCloseSRAM);
        CloseSRAM();
    }
    // RET;
}

// Mobile_CheckCurPartyMonFainted
void Function11ba38(void){
    // FARCALL(aCheckCurPartyMonFainted);
    // RET_C ;
    if(CheckCurPartyMonFainted())
        return;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x0;
    // RET;

}

const uint8_t TilemapPack_11ba44[] = {
    0x47, 0x30, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x56,  // 00
    0x46, 0x2f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x55,  // 01
    0x45, 0x3d, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x54,  // 02
    0x44, 0x30, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x53,  // 03
    0x43, 0x2f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x52,  // 04
    0x4a, 0x3d, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x51,  // 05
    0x4a, 0x30, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x50,  // 06
    0x4a, 0x2f, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x4f,  // 07
    0x4a, 0x3d, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x4e,  // 08
    0x4a, 0x30, 0x0a, 0x0a, 0x0a, 0x0a, 0x4d, 0x42,  // 09
    0x4a, 0x2f, 0x0a, 0x0a, 0x0a, 0x0a, 0x6b, 0x58,  // 0a
    0x4a, 0x3d, 0x0a, 0x0a, 0x0a, 0x0a, 0x6a, 0x58,  // 0b
    0x4a, 0x30, 0x0a, 0x0a, 0x0a, 0x0a, 0x69, 0x58,  // 0c
    0x4a, 0x2f, 0x0a, 0x0a, 0x0a, 0x0a, 0x68, 0x58,  // 0d
    0x4a, 0x3d, 0x0a, 0x0a, 0x0a, 0x66, 0x67, 0x58,  // 0e
    0x4a, 0x30, 0x0a, 0x0a, 0x0a, 0x65, 0x0a, 0x58,  // 0f
    0x4a, 0x2f, 0x0a, 0x0a, 0x0a, 0x64, 0x0a, 0x58,  // 10
    0x4a, 0x3d, 0x0a, 0x0a, 0x0a, 0x63, 0x0a, 0x58,  // 11
    0x4a, 0x30, 0x0a, 0x0a, 0x61, 0x62, 0x0a, 0x58,  // 12
    0x4a, 0x2f, 0x0a, 0x0a, 0x5f, 0x60, 0x0a, 0x58,  // 13
    0x4a, 0x3d, 0x0a, 0x61, 0x62, 0x0a, 0x0a, 0x58,  // 14
    0x4a, 0x30, 0x0a, 0x63, 0x0a, 0x0a, 0x0a, 0x58,  // 15
    0x4a, 0x2f, 0x69, 0x0a, 0x0a, 0x0a, 0x0a, 0x58,  // 16
    0x4a, 0x3d, 0x81, 0x0a, 0x0a, 0x0a, 0x0a, 0x58,  // 17
    0x4a, 0x30, 0x80, 0x0a, 0x0a, 0x0a, 0x0a, 0x58,  // 18
    0x4a, 0x2f, 0x7f, 0x0a, 0x0a, 0x0a, 0x0a, 0x58,  // 19
    0x4a, 0x3d, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x58,  // 1a
    0x4a, 0x30, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x58,  // 1b
    0x4a, 0x2f, 0x68, 0x87, 0x88, 0x89, 0x0a, 0x58,  // 1c
    0x4a, 0x3d, 0x6e, 0x6f, 0x70, 0x75, 0x76, 0x58,  // 1d
    0x4a, 0x30, 0x75, 0x76, 0x5c, 0x5d, 0x5e, 0x58,  // 1e
    0x4a, 0x2f, 0x71, 0x72, 0x73, 0x74, 0x6d, 0x58,  // 1f
    0x4a, 0x3d, 0x75, 0x76, 0x77, 0x8a, 0x8b, 0x58,  // 20
    0x4a, 0x30, 0x66, 0x67, 0x65, 0x0a, 0x6a, 0x58,  // 21
    0x4a, 0x2f, 0x83, 0x84, 0x0a, 0x83, 0x84, 0x58,  // 22
    0x4a, 0x3d, 0x0a, 0x85, 0x82, 0x84, 0x0a, 0x58,  // 23
    0x4a, 0x30, 0x41, 0x80, 0x40, 0x0a, 0x0a, 0x58,  // 24
    0x4a, 0x2f, 0x83, 0x0a, 0x0a, 0x0a, 0x0a, 0x58,  // 25
    0x4a, 0x3d, 0x40, 0x0a, 0x0a, 0x0a, 0x0a, 0x58,  // 26
    (uint8_t)-1,
};

const uint8_t TilemapPack_11bb7d[] = {
    0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x16, 0x00,  // 00
    0x78, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x8c, 0x00,  // 01
    0x79, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x8d, 0x00,  // 02
    0x7a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x8e, 0x00,  // 03
    0x7b, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x8c, 0x00,  // 04
    0x7c, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x8d, 0x00,  // 05
    0x7d, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x8e, 0x00,  // 06
    0x2e, 0x7e, 0x0a, 0x0a, 0x0a, 0x0a, 0x8c, 0x00,  // 07
    0x2e, 0x80, 0x0a, 0x0a, 0x0a, 0x0a, 0x8d, 0x00,  // 08
    0x2e, 0x81, 0x0a, 0x0a, 0x0a, 0x0a, 0x8e, 0x00,  // 09
    0x2e, 0x82, 0x0a, 0x0a, 0x0a, 0x0a, 0x8c, 0x00,  // 0a
    0x2e, 0x69, 0x0a, 0x0a, 0x0a, 0x0a, 0x8d, 0x00,  // 0b
    0x2e, 0x6a, 0x0a, 0x0a, 0x0a, 0x0a, 0x8e, 0x00,  // 0c
    0x2e, 0x6b, 0x0a, 0x0a, 0x0a, 0x0a, 0x8c, 0x00,  // 0d
    0x2e, 0x0a, 0x68, 0x0a, 0x0a, 0x0a, 0x8d, 0x00,  // 0e
    0x2e, 0x0a, 0x69, 0x0a, 0x0a, 0x0a, 0x8e, 0x00,  // 0f
    0x2e, 0x0a, 0x0a, 0x6a, 0x0a, 0x0a, 0x8c, 0x00,  // 10
    0x2e, 0x0a, 0x0a, 0x6b, 0x0a, 0x0a, 0x8d, 0x00,  // 11
    0x2e, 0x0a, 0x0a, 0x0a, 0x80, 0x0a, 0x8e, 0x00,  // 12
    0x2e, 0x0a, 0x0a, 0x0a, 0x82, 0x0a, 0x8c, 0x00,  // 13
    0x2e, 0x0a, 0x0a, 0x0a, 0x6c, 0x0a, 0x8d, 0x00,  // 14
    0x2e, 0x0a, 0x0a, 0x0a, 0x0a, 0x83, 0x8e, 0x00,  // 15
    0x2e, 0x0a, 0x6b, 0x0a, 0x0a, 0x0a, 0x8c, 0x00,  // 16
    0x2e, 0x0a, 0x0a, 0x69, 0x0a, 0x0a, 0x8d, 0x00,  // 17
    0x2e, 0x0a, 0x0a, 0x6a, 0x0a, 0x0a, 0x8e, 0x00,  // 18
    0x2e, 0x0a, 0x0a, 0x0a, 0x68, 0x0a, 0x8c, 0x00,  // 19
    0x2e, 0x0a, 0x0a, 0x0a, 0x63, 0x0a, 0x8d, 0x00,  // 1a
    0x2e, 0x0a, 0x0a, 0x61, 0x62, 0x0a, 0x8e, 0x00,  // 1b
    0x2e, 0x0a, 0x0a, 0x0a, 0x5f, 0x60, 0x8c, 0x00,  // 1c
    0x2e, 0x0a, 0x0a, 0x0a, 0x63, 0x0a, 0x8d, 0x00,  // 1d
    0x2e, 0x0a, 0x0a, 0x0a, 0x0a, 0x69, 0x8c, 0x00,  // 1e
    0x2e, 0x0a, 0x0a, 0x0a, 0x0a, 0x6b, 0x8d, 0x00,  // 1f
    0x2e, 0x0a, 0x0a, 0x0a, 0x0a, 0x83, 0x8e, 0x00,  // 20
    0x2e, 0x0a, 0x0a, 0x0a, 0x0a, 0x86, 0x8c, 0x00,  // 21
    0x2e, 0x0a, 0x85, 0x0a, 0x0a, 0x0a, 0x8d, 0x00,  // 22
    0x2e, 0x0a, 0x0a, 0x84, 0x0a, 0x0a, 0x8e, 0x00,  // 23
    (uint8_t)-1
};
