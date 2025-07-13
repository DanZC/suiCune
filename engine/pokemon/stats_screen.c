#include "../../constants.h"
#include "../../charmap.h"
#include "../../home/audio.h"
#include "../../home/map_objects.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/names.h"
#include "../../home/pokemon.h"
#include "../../home/joypad.h"
#include "../../home/sram.h"
#include "../../home/print_text.h"
#include "../../mobile/mobile_40.h"
#include "../battle/core.h"
#include "../gfx/load_font.h"
#include "../gfx/load_pics.h"
#include "../gfx/dma_transfer.h"
#include "../gfx/color.h"
#include "../gfx/pic_animation.h"
#include "../link/link.h"
#include "bills_pc.h"
#include "stats_screen.h"
#include "tempmon.h"
#include "mon_stats.h"
#include "health.h"
#include "experience.h"
#include "types.h"

enum {
    PINK_PAGE = 1,  // 1
    GREEN_PAGE,     // 2
    BLUE_PAGE,      // 3
};
#define NUM_STAT_PAGES BLUE_PAGE

#define STAT_PAGE_MASK (0b00000011)

void (*const StatsScreenPointerTable[])(void);

static void StatsScreen_WaitAnim(void);
static void StatsScreen_SetJumptableIndex(uint8_t h);
static void StatsScreen_Exit(void);
static void MonStatsInit(void);
static void EggStatsInit(void);
static void EggStatsJoypad(void);
static void StatsScreen_LoadPage(void);
static void MonStatsJoypad(void);

static void StatsScreenWaitCry(void);
static void StatsScreen_CopyToTempMon(void);
static bool StatsScreen_GetJoypad(uint8_t* a);
static void StatsScreen_JoypadAction(uint8_t a);
static void StatsScreen_InitUpperHalf(void);
static void StatsScreen_PlaceHorizontalDivider(void);
static void StatsScreen_PlacePageSwitchArrows(void);
static void StatsScreen_PlaceShinyIcon(void);
static void StatsScreen_LoadGFX(void);
static void LoadPinkPage(void);
static void LoadGreenPage(void);
static void LoadBluePage(void);

static void StatsScreen_PlaceFrontpic(void);
static u8_flag_s StatsScreen_GetAnimationParam(void);

static void StatsScreen_AnimateEgg(void);
static void StatsScreen_LoadPageIndicators(uint8_t c);
static uint8_t* CopyNickname(uint8_t* hl);
static uint8_t* GetNicknamenamePointer(void);
static uint8_t* GetNicknamenamePointer2(void);

void BattleStatsScreenInit(void){
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // JR_NZ (mStatsScreenInit);
    if(wram->wLinkMode != LINK_MOBILE)
        return StatsScreenInit();

    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // JR_Z (mStatsScreenInit);
    if(wram->wBattleMode == 0)
        return StatsScreenInit();
    // JR(mv_MobileStatsScreenInit);
    return v_MobileStatsScreenInit();
}

void StatsScreenInit(void){
    // LD_HL(mStatsScreenMain);
    // JR(mStatsScreenInit_gotaddress);
    return StatsScreenInit_Common(StatsScreenMain);
}

void v_MobileStatsScreenInit(void){
    // LD_HL(mStatsScreenMobile);
    // JR(mStatsScreenInit_gotaddress);
    return StatsScreenInit_Common(StatsScreenMobile);
}

void StatsScreenInit_gotaddress(void){
    LDH_A_addr(hMapAnims);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hMapAnims);  // disable overworld tile animations
    LD_A_addr(wBoxAlignment);  // whether sprite is to be mirrorred
    PUSH_AF;
    LD_A_addr(wJumptableIndex);
    LD_B_A;
    LD_A_addr(wStatsScreenFlags);
    LD_C_A;

    PUSH_BC;
    PUSH_HL;
    CALL(aClearBGPalettes);
    CALL(aClearTilemap);
    CALL(aUpdateSprites);
    FARCALL(aStatsScreen_LoadFont);
    POP_HL;
    CALL(av_hl_);
    CALL(aClearBGPalettes);
    CALL(aClearTilemap);
    POP_BC;

// restore old values
    LD_A_B;
    LD_addr_A(wJumptableIndex);
    LD_A_C;
    LD_addr_A(wStatsScreenFlags);
    POP_AF;
    LD_addr_A(wBoxAlignment);
    POP_AF;
    LDH_addr_A(hMapAnims);
    RET;

}

void StatsScreenInit_Common(void (*hl)(void)){
    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    uint8_t mapanims = hram.hMapAnims;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);  // disable overworld tile animations
    hram.hMapAnims = 0;  // disable overworld tile animations
    // LD_A_addr(wBoxAlignment);  // whether sprite is to be mirrorred
    // PUSH_AF;
    uint8_t box_align = wram->wBoxAlignment;
    // LD_A_addr(wJumptableIndex);
    // LD_B_A;
    uint8_t b = wram->wJumptableIndex;
    // LD_A_addr(wStatsScreenFlags);
    // LD_C_A;
    uint8_t c = wram->wStatsScreenFlags;

    // PUSH_BC;
    // PUSH_HL;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // FARCALL(aStatsScreen_LoadFont);
    StatsScreen_LoadFont();
    // POP_HL;
    // CALL(av_hl_);
    hl();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // POP_BC;

// restore old values
    // LD_A_B;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = b;
    // LD_A_C;
    // LD_addr_A(wStatsScreenFlags);
    wram->wStatsScreenFlags = c;
    // POP_AF;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = box_align;
    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = mapanims;
    // RET;
}

void StatsScreenMain(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
//  ???
    // LD_addr_A(wStatsScreenFlags);
    wram->wStatsScreenFlags = 0;
    // LD_A_addr(wStatsScreenFlags);
    // AND_A(~STAT_PAGE_MASK);
    // OR_A(PINK_PAGE);  // first_page
    // LD_addr_A(wStatsScreenFlags);
    wram->wStatsScreenFlags = (wram->wStatsScreenFlags & ~STAT_PAGE_MASK) | PINK_PAGE;

    do {
    // loop:
        // LD_A_addr(wJumptableIndex);
        // AND_A(~(1 << 7));
        // LD_HL(mStatsScreenPointerTable);
        // RST(aJumpTable);
        StatsScreenPointerTable[wram->wJumptableIndex & 0x7f]();
        // CALL(aStatsScreen_WaitAnim);
        StatsScreen_WaitAnim();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_Z goto loop;
    } while((wram->wJumptableIndex & 0x80) == 0);
    // RET;

}

void StatsScreenMobile(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
//  ???
    // LD_addr_A(wStatsScreenFlags);
    wram->wStatsScreenFlags = 0;
    // LD_A_addr(wStatsScreenFlags);
    // AND_A(~STAT_PAGE_MASK);
    // OR_A(PINK_PAGE);  // first_page
    // LD_addr_A(wStatsScreenFlags);
    wram->wStatsScreenFlags = (wram->wStatsScreenFlags & ~STAT_PAGE_MASK) | PINK_PAGE;

    do {
    // loop:
        // FARCALL(aMobile_SetOverworldDelay);
        Mobile_SetOverworldDelay();
        // LD_A_addr(wJumptableIndex);
        // AND_A(0x7f);
        // LD_HL(mStatsScreenPointerTable);
        // RST(aJumpTable);
        StatsScreenPointerTable[wram->wJumptableIndex & 0x7f]();
        // CALL(aStatsScreen_WaitAnim);
        StatsScreen_WaitAnim();
        // FARCALL(aMobileComms_CheckInactivityTimer);
        // IF_C goto exit;
        if(MobileComms_CheckInactivityTimer())
            return;
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_Z goto loop;
    } while(!bit_test(wram->wJumptableIndex, 7));

// exit:
    // RET;
}

enum {
    JT_MON_STATS_INIT,
    JT_EGG_STATS_INIT,
    JT_WAIT_CRY,
    JT_EGG_STATS_JOYPAD,
    JT_LOAD_PAGE,
    JT_WAIT_CRY2,
    JT_MON_STATS_JOYPAD,
    JT_EXIT,
};

// void StatsScreenPointerTable(void){
    //dw ['MonStatsInit'];  // regular pokémon
    //dw ['EggStatsInit'];  // egg
    //dw ['StatsScreenWaitCry'];
    //dw ['EggStatsJoypad'];
    //dw ['StatsScreen_LoadPage'];
    //dw ['StatsScreenWaitCry'];
    //dw ['MonStatsJoypad'];
    //dw ['StatsScreen_Exit'];

    // return StatsScreen_WaitAnim();
// }

void (*const StatsScreenPointerTable[])(void) = {
    [JT_MON_STATS_INIT]     = MonStatsInit,
    [JT_EGG_STATS_INIT]     = EggStatsInit,
    [JT_WAIT_CRY]           = StatsScreenWaitCry,
    [JT_EGG_STATS_JOYPAD]   = EggStatsJoypad,
    [JT_LOAD_PAGE]          = StatsScreen_LoadPage,
    [JT_WAIT_CRY2]          = StatsScreenWaitCry,
    [JT_MON_STATS_JOYPAD]   = MonStatsJoypad,
    [JT_EXIT]               = StatsScreen_Exit,
};

static void StatsScreen_WaitAnim(void){
    // LD_HL(wStatsScreenFlags);
    // BIT_hl(6);
    // IF_NZ goto try_anim;
    if(bit_test(wram->wStatsScreenFlags, 6)) {
    // try_anim:
        // FARCALL(aSetUpPokeAnim);
        // IF_NC goto finish;
        if(SetUpPokeAnim()) {
            // LD_HL(wStatsScreenFlags);
            // RES_hl(6);
            bit_reset(wram->wStatsScreenFlags, 6);
        }
    }
    // BIT_hl(5);
    // IF_NZ goto finish;
    else if(!bit_test(wram->wStatsScreenFlags, 5)) {
        // CALL(aDelayFrame);
        // RET;
        DelayFrame();
        return;
    }

// finish:
    // LD_HL(wStatsScreenFlags);
    // RES_hl(5);
    bit_reset(wram->wStatsScreenFlags, 5);
    // FARCALL(aHDMATransferTilemapToWRAMBank3);
    HDMATransferTilemapToWRAMBank3();
    // RET;
}

static void StatsScreen_SetJumptableIndex(uint8_t h){
    // LD_A_addr(wJumptableIndex);
    // AND_A(0x80);
    // OR_A_H;
    // LD_addr_A(wJumptableIndex);
    // RET;
    wram->wJumptableIndex = (wram->wJumptableIndex & 0x80) | h;
}

static void StatsScreen_Exit(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    // RET;
    bit_set(wram->wJumptableIndex, 7);
}

static void MonStatsInit(void){
    // LD_HL(wStatsScreenFlags);
    // RES_hl(6);
    bit_reset(wram->wStatsScreenFlags, 6);
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // FARCALL(aHDMATransferTilemapToWRAMBank3);
    HDMATransferTilemapToWRAMBank3();
    // CALL(aStatsScreen_CopyToTempMon);
    StatsScreen_CopyToTempMon();
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto egg;
    if(wram->wCurPartySpecies == EGG) {
    // egg:
        // LD_H(1);
        // CALL(aStatsScreen_SetJumptableIndex);
        // RET;
        return StatsScreen_SetJumptableIndex(JT_EGG_STATS_INIT);
    }
    // CALL(aStatsScreen_InitUpperHalf);
    StatsScreen_InitUpperHalf();
    // LD_HL(wStatsScreenFlags);
    // SET_hl(4);
    bit_set(wram->wStatsScreenFlags, 4);
    // LD_H(4);
    // CALL(aStatsScreen_SetJumptableIndex);
    // RET;
    return StatsScreen_SetJumptableIndex(JT_LOAD_PAGE);
}

static void EggStatsInit(void){
    // CALL(aEggStatsScreen);
    EggStatsScreen();
    // LD_A_addr(wJumptableIndex);
    // INC_A;
    // LD_addr_A(wJumptableIndex);
    // RET;
    wram->wJumptableIndex++;
}

static void EggStatsJoypad(void){
    uint8_t a = 0;
    // CALL(aStatsScreen_GetJoypad);
    // IF_NC goto check;
    if(StatsScreen_GetJoypad(&a)) {
        // LD_H(0);
        // CALL(aStatsScreen_SetJumptableIndex);
        // RET;
        StatsScreen_SetJumptableIndex(JT_MON_STATS_INIT);
        return;
    }

// check:
    // BIT_A(A_BUTTON_F);
    // IF_NZ goto quit;
    if(!bit_test(a, A_BUTTON_F)) {
#if defined(_DEBUG) && 0
static const char HatchSoonString[] = "▶HATCH SOON!";
        // CP_A(START);
        // IF_Z goto hatch;
        if(a == START) {
        // hatch:
            // LD_A_addr(wMonType);
            // OR_A_A;
            // IF_NZ goto skip;
            if(wram->wMonType == TEMPMON) {
                // PUSH_BC;
                // PUSH_DE;
                // PUSH_HL;
                // LD_A_addr(wCurPartyMon);
                // LD_BC(PARTYMON_STRUCT_LENGTH);
                // LD_HL(wPartyMon1Happiness);
                // CALL(aAddNTimes);
                // LD_hl(1);
                gPokemon.partyMon[wram->wCurPartyMon].mon.happiness = 1;
                // LD_A(1);
                // LD_addr_A(wTempMonHappiness);
                wram->wTempMon.mon.happiness = 1;
                // LD_A(127);
                // LD_addr_A(wStepCount);
                wram->wStepCount = 127;
                // LD_DE(HatchSoonString);
                // hlcoord(8, 17, wTilemap);
                // CALL(aPlaceString);
                PlaceStringSimple(U82C(HatchSoonString), coord(8, 17, wram->wTilemap));
                // LD_HL(wStatsScreenFlags);
                // SET_hl(5);
                bit_set(wram->wStatsScreenFlags, 5);
                // POP_HL;
                // POP_DE;
                // POP_BC;
            }

        // skip:
            // XOR_A_A;
            // JP(mStatsScreen_JoypadAction);
            return StatsScreen_JoypadAction(0);
        }
#endif
        // AND_A(D_DOWN | D_UP | A_BUTTON | B_BUTTON);
        // JP(mStatsScreen_JoypadAction);
        return StatsScreen_JoypadAction(a & (D_DOWN | D_UP | A_BUTTON | B_BUTTON));
    }

// quit:
    // LD_H(7);
    // CALL(aStatsScreen_SetJumptableIndex);
    // RET;
    StatsScreen_SetJumptableIndex(JT_EXIT);
    return;
}

static void StatsScreen_LoadPage(void){
    // CALL(aStatsScreen_LoadGFX);
    StatsScreen_LoadGFX();
    // LD_HL(wStatsScreenFlags);
    // RES_hl(4);
    bit_reset(wram->wStatsScreenFlags, 4);
    // LD_A_addr(wJumptableIndex);
    // INC_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex++;
    // RET;
}

static void MonStatsJoypad(void){
    uint8_t a;
    // CALL(aStatsScreen_GetJoypad);
    // IF_NC goto next;
    if(StatsScreen_GetJoypad(&a)) {
        // LD_H(0);
        // CALL(aStatsScreen_SetJumptableIndex);
        // RET;
        return StatsScreen_SetJumptableIndex(JT_MON_STATS_INIT);
    }


// next:
    // AND_A(D_DOWN | D_UP | D_LEFT | D_RIGHT | A_BUTTON | B_BUTTON);
    // JP(mStatsScreen_JoypadAction);
    return StatsScreen_JoypadAction(a & (D_DOWN | D_UP | D_LEFT | D_RIGHT | A_BUTTON | B_BUTTON));
}

static void StatsScreenWaitCry(void){
    // CALL(aIsSFXPlaying);
    // RET_NC ;
    if(IsSFXPlaying())
        return;
    
    // LD_A_addr(wJumptableIndex);
    // INC_A;
    // LD_addr_A(wJumptableIndex);
    // RET;
    wram->wJumptableIndex++;
}

static void StatsScreen_CopyToTempMon(void){
    // LD_A_addr(wMonType);
    // CP_A(TEMPMON);
    // IF_NZ goto not_tempmon;
    if(wram->wMonType == TEMPMON) {
        // LD_A_addr(wBufferMonSpecies);
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = wram->wBufferMon.mon.species;
        // CALL(aGetBaseData);
        GetBaseData(wram->wBufferMon.mon.species);
        // LD_HL(wBufferMon);
        // LD_DE(wTempMon);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(&wram->wTempMon, &wram->wBufferMon, sizeof(wram->wBufferMon));
        // goto done;
    }
    else {

    // not_tempmon:
        // FARCALL(aCopyMonToTempMon);
        CopyMonToTempMon();
        // LD_A_addr(wCurPartySpecies);
        // CP_A(EGG);
        // IF_Z goto done;
        // LD_A_addr(wMonType);
        // CP_A(BOXMON);
        // IF_C goto done;
        if(wram->wCurPartySpecies != EGG && wram->wMonType >= BOXMON) {
            // FARCALL(aCalcTempmonStats);
            CalcTempmonStats();
        }
    }

// done:
    // AND_A_A;
    // RET;
}

static bool StatsScreen_GetJoypad(uint8_t* a){
    // CALL(aGetJoypad);
    GetJoypad();
    // LD_A_addr(wMonType);
    // CP_A(TEMPMON);
    // IF_NZ goto not_tempmon;
    if(wram->wMonType != TEMPMON) {
    // not_tempmon:
        // LDH_A_addr(hJoyPressed);
        *a = hram.hJoyPressed;
    }
    else {
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // FARCALL(aStatsScreenDPad);
        // POP_BC;
        // POP_DE;
        // POP_HL;
        StatsScreenDPad();
        // LD_A_addr(wMenuJoypad);
        // AND_A(D_DOWN | D_UP);
        // IF_NZ goto set_carry;
        if(wram->wMenuJoypad & (D_DOWN | D_UP)) {
        // set_carry:
            // SCF;
            // RET;
            return true;
        }
        // LD_A_addr(wMenuJoypad);
        // goto clear_carry;
        *a = wram->wMenuJoypad;
    }
// clear_carry:
    // AND_A_A;
    // RET;
    return false;
}

static void StatsScreen_JoypadAction(uint8_t a){
    // PUSH_AF;
    // LD_A_addr(wStatsScreenFlags);
    // maskbits(NUM_STAT_PAGES, 0);
    // LD_C_A;
    // POP_AF;
    uint8_t c = wram->wStatsScreenFlags & NUM_STAT_PAGES;
    // BIT_A(B_BUTTON_F);
    // JP_NZ (mStatsScreen_JoypadAction_b_button);
    if(bit_test(a, B_BUTTON_F)) {
    // b_button:
        // LD_H(7);
        // CALL(aStatsScreen_SetJumptableIndex);
        // RET;
        return StatsScreen_SetJumptableIndex(JT_EXIT);
    }
    // BIT_A(D_LEFT_F);
    // IF_NZ goto d_left;
    else if(bit_test(a, D_LEFT_F)) {
    // d_left:
        // DEC_C;
        // IF_NZ goto set_page;
        if(--c == 0) c = BLUE_PAGE;  // last page
        // LD_C(BLUE_PAGE);  // last page
        goto set_page;
    }
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto d_right;
    else if(bit_test(a, D_RIGHT_F)) {
    d_right:
        // INC_C;
        // LD_A(BLUE_PAGE);  // last page
        // CP_A_C;
        // IF_NC goto set_page;
        if(++c > BLUE_PAGE)
            c = PINK_PAGE;
        // LD_C(PINK_PAGE);  // first page
        // goto set_page;
    set_page:
        // LD_A_addr(wStatsScreenFlags);
        // AND_A(~STAT_PAGE_MASK);
        // OR_A_C;
        // LD_addr_A(wStatsScreenFlags);
        wram->wStatsScreenFlags = (wram->wStatsScreenFlags & ~STAT_PAGE_MASK) | c;
        // LD_H(4);
        // CALL(aStatsScreen_SetJumptableIndex);
        // RET;
        return StatsScreen_SetJumptableIndex(JT_LOAD_PAGE);
    }
    // BIT_A(A_BUTTON_F);
    // IF_NZ goto a_button;
    else if(bit_test(a, A_BUTTON_F)) {
    // a_button:
        // LD_A_C;
        // CP_A(BLUE_PAGE);  // last page
        // IF_Z goto b_button;
        if(c == BLUE_PAGE)
            return StatsScreen_SetJumptableIndex(JT_EXIT);
        goto d_right;
    }
    // BIT_A(D_UP_F);
    // IF_NZ goto d_up;
    else if(bit_test(a, D_UP_F)) {
    // d_up:
        // LD_A_addr(wCurPartyMon);
        // AND_A_A;
        // IF_Z goto done;
        if(wram->wCurPartyMon == 0)
            return;
        // DEC_A;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon--;
        // LD_B_A;
        // LD_A_addr(wMonType);
        // AND_A_A;
        // IF_NZ goto load_mon;
        if(wram->wMonType == PARTYMON) {
            // LD_A_B;
            // INC_A;
            // LD_addr_A(wPartyMenuCursor);
            wram->wPartyMenuCursor = wram->wCurPartyMon + 1;
        }
        // goto load_mon;
    // load_mon:
        // LD_H(0);
        // CALL(aStatsScreen_SetJumptableIndex);
        // RET;
        return StatsScreen_SetJumptableIndex(JT_MON_STATS_INIT);
    }
    // BIT_A(D_DOWN_F);
    // IF_NZ goto d_down;
    else if(bit_test(a, D_DOWN_F)) {
    // d_down:
        // LD_A_addr(wMonType);
        // CP_A(BOXMON);
        // IF_NC goto done;
        if(wram->wMonType >= BOXMON)
            return;
        // AND_A_A;
        // LD_A_addr(wPartyCount);
        // IF_Z goto next_mon;
        // LD_A_addr(wOTPartyCount);

    // next_mon:
        // LD_B_A;
        uint8_t b = (wram->wMonType == PARTYMON)? gPokemon.partyCount: wram->wOTPartyCount;
        // LD_A_addr(wCurPartyMon);
        // INC_A;
        // CP_A_B;
        // IF_Z goto done;
        if(wram->wCurPartyMon + 1 == b)
            return;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon++;
        // LD_B_A;
        // LD_A_addr(wMonType);
        // AND_A_A;
        // IF_NZ goto load_mon;
        if(wram->wMonType == PARTYMON) {
            // LD_A_B;
            // INC_A;
            // LD_addr_A(wPartyMenuCursor);
            wram->wPartyMenuCursor = wram->wCurPartyMon;
        }
        // goto load_mon;
    // load_mon:
        // LD_H(0);
        // CALL(aStatsScreen_SetJumptableIndex);
        // RET;
        return StatsScreen_SetJumptableIndex(JT_MON_STATS_INIT);
    }
    // goto done;
    else {
        return;
    }


// done:
    // RET;
}

static void StatsScreen_PlaceHPBar(void) {
    // LD_HL(wTempMonHP);
    // LD_A_hli;
    // LD_B_A;
    // LD_C_hl;
    // LD_HL(wTempMonMaxHP);
    // LD_A_hli;
    // LD_D_A;
    // LD_E_hl;
    // FARCALL(aComputeHPBarPixels);
    // LD_HL(wCurHPPal);
    // CALL(aSetHPPal);
    SetHPPal(&wram->wCurHPPal, ComputeHPBarPixels(BigEndianToNative16(wram->wTempMon.HP), BigEndianToNative16(wram->wTempMon.maxHP)));
    // LD_B(SCGB_STATS_SCREEN_HP_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_STATS_SCREEN_HP_PALS);
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

static void StatsScreen_PlaceGenderChar(uint8_t* hl) {
    // PUSH_HL;
    // FARCALL(aGetGender);
    u8_flag_s res = GetGender(wram->wMonType);
    // POP_HL;
    // RET_C ;
    if(res.flag)
        return;
    // LD_A(0xef);
    // IF_NZ goto got_gender;
    // LD_A(0xf5);

// got_gender:
    // LD_hl_A;
    *hl = (res.a == 0)? CHAR_FEMALE_ICON: CHAR_MALE_ICON;
    // RET;
}

static void StatsScreen_InitUpperHalf(void){
    // CALL(aStatsScreen_InitUpperHalf_PlaceHPBar);
    StatsScreen_PlaceHPBar();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // LD_A_addr(wBaseDexNo);
    // LD_addr_A(wTextDecimalByte);
    wram->wTextDecimalByte = wram->wBaseDexNo;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wBaseDexNo;
    // hlcoord(8, 0, wTilemap);
    // LD_hl(0x74);
    *coord(8, 0, wram->wTilemap) = 0x74;
    // INC_HL;
    // LD_hl(0xe8);
    *coord(9, 0, wram->wTilemap) = 0xe8;
    // INC_HL;
    // hlcoord(10, 0, wTilemap);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
    // LD_DE(wTextDecimalByte);
    // CALL(aPrintNum);
    PrintNum(coord(10, 0, wram->wTilemap), &wram->wTextDecimalByte, PRINTNUM_LEADINGZEROS | 1, 3);
    // hlcoord(14, 0, wTilemap);
    // CALL(aPrintLevel);
    PrintLevel(coord(14, 0, wram->wTilemap), wram->wTempMon.mon.level);
    // LD_HL(mStatsScreen_InitUpperHalf_NicknamePointers);
    // CALL(aGetNicknamenamePointer);
    // CALL(aCopyNickname);
    // hlcoord(8, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(CopyNickname(GetNicknamenamePointer2()), coord(8, 2, wram->wTilemap));
    // hlcoord(18, 0, wTilemap);
    // CALL(aStatsScreen_InitUpperHalf_PlaceGenderChar);
    StatsScreen_PlaceGenderChar(coord(18, 0, wram->wTilemap));
    // hlcoord(9, 4, wTilemap);
    // LD_A(0xf3);
    // LD_hli_A;
    *coord(9, 4, wram->wTilemap) = CHAR_FWD_SLASH;
    // LD_A_addr(wBaseDexNo);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // CALL(aPlaceString);
    PlaceStringSimple(GetPokemonName(wram->wBaseDexNo), coord(9, 4, wram->wTilemap) + 1);
    // CALL(aStatsScreen_PlaceHorizontalDivider);
    StatsScreen_PlaceHorizontalDivider();
    // CALL(aStatsScreen_PlacePageSwitchArrows);
    StatsScreen_PlacePageSwitchArrows();

    //  CALL(aStatsScreen_PlaceShinyIcon);
    StatsScreen_PlaceShinyIcon();
    // RET;
    return;


// NicknamePointers:
    //dw ['wPartyMonNicknames'];
    //dw ['wOTPartyMonNicknames'];
    //dw ['sBoxMonNicknames'];
    //dw ['wBufferMonNickname'];
}

void StatsScreen_PlaceVerticalDivider(void){
//  //  unreferenced
//  The Japanese stats screen has a vertical divider.
    hlcoord(7, 0, wTilemap);
    LD_BC(SCREEN_WIDTH);
    LD_D(SCREEN_HEIGHT);

loop:
    LD_A(0x31);  // vertical divider
    LD_hl_A;
    ADD_HL_BC;
    DEC_D;
    IF_NZ goto loop;
    RET;

}

static void StatsScreen_PlaceHorizontalDivider(void){
    // hlcoord(0, 7, wTilemap);
    // LD_B(SCREEN_WIDTH);
    // LD_A(0x62);  // horizontal divider (empty HP/exp bar)

    for(uint8_t i = 0; i < SCREEN_WIDTH; i++) {
    // loop:
        // LD_hli_A;
        *coord(i, 7, wram->wTilemap) = 0x62;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // RET;
}

static void StatsScreen_PlacePageSwitchArrows(void){
    // hlcoord(12, 6, wTilemap);
    // LD_hl(0x71);
    *coord(12, 6, wram->wTilemap) = CHAR_LEFT_CURSOR;
    // hlcoord(19, 6, wTilemap);
    // LD_hl(0xed);
    *coord(19, 6, wram->wTilemap) = CHAR_RIGHT_CURSOR;
    // RET;
}

static void StatsScreen_PlaceShinyIcon(void){
    // LD_BC(wTempMonDVs);
    // FARCALL(aCheckShininess);
    // RET_NC ;
    if(!CheckShininess(wram->wTempMon.mon.DVs))
        return;
    // hlcoord(19, 0, wTilemap);
    // LD_hl(0x3f);
    // RET;
    *coord(19, 0, wram->wTilemap) = CHAR_SHINY_ICON;
}

static void StatsScreen_LoadGFX_ClearBox(void) {
    // LD_A_addr(wStatsScreenFlags);
    // maskbits(NUM_STAT_PAGES, 0);
    // LD_C_A;
    // CALL(aStatsScreen_LoadPageIndicators);
    StatsScreen_LoadPageIndicators(wram->wStatsScreenFlags & NUM_STAT_PAGES);
    // hlcoord(0, 8, wTilemap);
    // LD_BC((10 << 8) | 20);
    // CALL(aClearBox);
    ClearBox(coord(0, 8, wram->wTilemap), 20, 10);
    // RET;
}

static void StatsScreen_LoadGFX_LoadPals(void) {
    // LD_A_addr(wStatsScreenFlags);
    // maskbits(NUM_STAT_PAGES, 0);
    // LD_C_A;
    // FARCALL(aLoadStatsScreenPals);
    LoadStatsScreenPals(wram->wStatsScreenFlags & NUM_STAT_PAGES);

    // CALL(aDelayFrame);
    DelayFrame();
    // LD_HL(wStatsScreenFlags);
    // SET_hl(5);
    // RET;
    bit_set(wram->wStatsScreenFlags, 5);
}

static void StatsScreen_LoadGFX_PageTilemap(void) {
    static void (*const Jumptable[])(void) = {
    //  entries correspond to *_PAGE constants
        [PINK_PAGE-1]  = LoadPinkPage,
        [GREEN_PAGE-1] = LoadGreenPage,
        [BLUE_PAGE-1]  = LoadBluePage,
    };
    //dw ['LoadPinkPage'];
    //dw ['LoadGreenPage'];
    //dw ['LoadBluePage'];
    static_assert(lengthof(Jumptable) == NUM_STAT_PAGES, "");
    // LD_A_addr(wStatsScreenFlags);
    // maskbits(NUM_STAT_PAGES, 0);
    // DEC_A;
    // LD_HL(mStatsScreen_LoadGFX_Jumptable);
    // RST(aJumpTable);
    Jumptable[(wram->wStatsScreenFlags - 1) & NUM_STAT_PAGES]();
    // RET;
}

static void StatsScreen_LoadGFX(void){
    // LD_A_addr(wBaseDexNo);
    // LD_addr_A(wTempSpecies);
    wram->wTempSpecies = wram->wBaseDexNo;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wBaseDexNo;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aStatsScreen_LoadGFX_ClearBox);
    StatsScreen_LoadGFX_ClearBox();
    // CALL(aStatsScreen_LoadGFX_PageTilemap);
    StatsScreen_LoadGFX_PageTilemap();
    // CALL(aStatsScreen_LoadGFX_LoadPals);
    StatsScreen_LoadGFX_LoadPals();

    // LD_HL(wStatsScreenFlags);
    // BIT_hl(4);
    // IF_NZ goto place_frontpic;
    if(bit_test(wram->wStatsScreenFlags, 4)) {
    // place_frontpic:
        // CALL(aStatsScreen_PlaceFrontpic);
        StatsScreen_PlaceFrontpic();
        // RET;
        return;
    }
    // CALL(aSetPalettes);
    SetPalettes();
    // RET;
    return;
}

static void LoadPinkPage_PrintNextLevel(uint8_t* hl) {
    // LD_A_addr(wTempMonLevel);
    // PUSH_AF;
    uint8_t a = wram->wTempMon.mon.level;
    // CP_A(MAX_LEVEL);
    // IF_Z goto AtMaxLevel;
    if(a != MAX_LEVEL) {
        // INC_A;
        // LD_addr_A(wTempMonLevel);
        ++wram->wTempMon.mon.level;
    }
// AtMaxLevel:
    // CALL(aPrintLevel);
    PrintLevel(hl, wram->wTempMon.mon.level);
    // POP_AF;
    // LD_addr_A(wTempMonLevel);
    wram->wTempMon.mon.level = a;
    // RET;
}

void LoadPinkPage_CalcExpToNextLevel(void) {
    // LD_A_addr(wTempMonLevel);
    // CP_A(MAX_LEVEL);
    // IF_Z goto AlreadyAtMaxLevel;
    if(wram->wTempMon.mon.level == MAX_LEVEL) {
    // AlreadyAtMaxLevel:
        // LD_HL(wExpToNextLevel);
        // XOR_A_A;
        // LD_hli_A;
        wram->wExpToNextLevel[0] = 0;
        // LD_hli_A;
        wram->wExpToNextLevel[1] = 0;
        // LD_hl_A;
        wram->wExpToNextLevel[2] = 0;
        // RET;
        return;
    }
    // INC_A;
    // LD_D_A;
    // SAVE_REGS;
    // REG_D = wram->wTempMon.mon.level + 1;
    // FARCALL(aCalcExpAtLevel);
    // RESTORE_REGS;
    uint32_t xp = CalcExpAtLevel(wram->wTempMon.mon.level + 1);
    uint32_t cur_xp = (uint32_t)wram->wTempMon.mon.exp[2] + 
        ((uint32_t)wram->wTempMon.mon.exp[1] << 8) +
        ((uint32_t)wram->wTempMon.mon.exp[0] << 16);
    uint32_t diff = xp - cur_xp;
    // LD_HL(wTempMonExp + 2);
    // LD_HL(wTempMonExp + 2);
    // LDH_A_addr(hQuotient + 3);
    // SUB_A_hl;
    // DEC_HL;
    // LD_addr_A(wExpToNextLevel + 2);
    wram->wExpToNextLevel[0] = (diff >> 16) & 0xff;
    // LDH_A_addr(hQuotient + 2);
    // SBC_A_hl;
    // DEC_HL;
    // LD_addr_A(wExpToNextLevel + 1);
    wram->wExpToNextLevel[1] = (diff >> 8) & 0xff;
    // LDH_A_addr(hQuotient + 1);
    // SBC_A_hl;
    // LD_addr_A(wExpToNextLevel);
    wram->wExpToNextLevel[2] = diff & 0xff;
    // RET;
}

static void LoadPinkPage(void){
    static const char Status_Type[] = "STATUS/" \
        t_next "TYPE/@";
    static const char OK_str[] = "OK @";
    static const char ExpPointStr[] = "EXP POINTS@";
    static const char LevelUpStr[] = "LEVEL UP@";
    static const char ToStr[] = "TO@";
    static const char PkrsStr[] = "#RUS@";

    // hlcoord(0, 9, wTilemap);
    // LD_B(0x0);
    // PREDEF(pDrawPlayerHP);
    DrawPlayerHP(coord(0, 9, wram->wTilemap), 0x0);
    // hlcoord(8, 9, wTilemap);
    // LD_hl(0x41);  // right HP/exp bar end cap
    *coord(8, 9, wram->wTilemap) = 0x41;
    // LD_DE(mLoadPinkPage_Status_Type);
    // hlcoord(0, 12, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Status_Type), coord(0, 12, wram->wTilemap));
    // LD_A_addr(wTempMonPokerusStatus);
    // LD_B_A;
    // AND_A(0xf);
    // IF_NZ goto HasPokerus;
    if(wram->wTempMon.mon.pokerusStatus & 0xf) {
    // HasPokerus:
        // LD_DE(mLoadPinkPage_PkrsStr);
        // hlcoord(1, 13, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(PkrsStr), coord(1, 13, wram->wTilemap));
        // goto done_status;
    }
    else {
        // LD_A_B;
        // AND_A(0xf0);
        // IF_Z goto NotImmuneToPkrs;
        if(wram->wTempMon.mon.pokerusStatus & 0xf0) {
            // hlcoord(8, 8, wTilemap);
            // LD_hl(0xe8);  // Pokérus immunity dot
            *coord(8, 8, wram->wTilemap) = 0xe8;
        }
    // NotImmuneToPkrs:
        // LD_A_addr(wMonType);
        // CP_A(BOXMON);
        // IF_Z goto StatusOK;
        // hlcoord(6, 13, wTilemap);
        // PUSH_HL;
        // LD_DE(wTempMonStatus);
        // PREDEF(pPlaceStatusString);
        // POP_HL;
        // IF_NZ goto done_status;
        if(wram->wMonType == BOXMON || !PlaceStatusString(coord(6, 13, wram->wTilemap), &wram->wTempMon)) {
        // goto StatusOK;

        // StatusOK:
            // LD_DE(mLoadPinkPage_OK_str);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(OK_str), coord(6, 13, wram->wTilemap));
        }
    }

// done_status:
    // hlcoord(1, 15, wTilemap);
    // PREDEF(pPrintMonTypes);
    PrintMonTypes(coord(1, 15, wram->wTilemap));
    // hlcoord(9, 8, wTilemap);
    // LD_DE(SCREEN_WIDTH);
    // LD_B(10);
    // LD_A(0x31);  // vertical divider

    for(uint8_t b = 0; b < 10; b++) {
    // vertical_divider:
        // LD_hl_A;
        *coord(9, 8 + b, wram->wTilemap) = 0x31;
        // ADD_HL_DE;
        // DEC_B;
        // IF_NZ goto vertical_divider;
    }
    // LD_DE(mLoadPinkPage_ExpPointStr);
    // hlcoord(10, 9, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(ExpPointStr), coord(10, 9, wram->wTilemap));
    // hlcoord(17, 14, wTilemap);
    // CALL(aLoadPinkPage_PrintNextLevel);
    LoadPinkPage_PrintNextLevel(coord(17, 14, wram->wTilemap));
    // hlcoord(13, 10, wTilemap);
    // LD_BC((3 << 8) | 7);
    // LD_DE(wTempMonExp);
    // CALL(aPrintNum);
    PrintNum(coord(13, 10, wram->wTilemap), wram->wTempMon.mon.exp, 3, 7);
    // CALL(aLoadPinkPage_CalcExpToNextLevel);
    LoadPinkPage_CalcExpToNextLevel();
    // hlcoord(13, 13, wTilemap);
    // LD_BC((3 << 8) | 7);
    // LD_DE(wExpToNextLevel);
    // CALL(aPrintNum);
    PrintNum(coord(13, 13, wram->wTilemap), wram->wExpToNextLevel, 3, 7);
    // LD_DE(mLoadPinkPage_LevelUpStr);
    // hlcoord(10, 12, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(LevelUpStr), coord(10, 12, wram->wTilemap));
    // LD_DE(mLoadPinkPage_ToStr);
    // hlcoord(14, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(ToStr), coord(14, 14, wram->wTilemap));
    // hlcoord(11, 16, wTilemap);
    // LD_A_addr(wTempMonLevel);
    // LD_B_A;
    // LD_DE(wTempMonExp + 2);
    // PREDEF(pFillInExpBar);
    FillInExpBar(coord(11, 16, wram->wTilemap), wram->wTempMon.mon.level, wram->wTempMon.mon.exp + 2);
    // hlcoord(10, 16, wTilemap);
    // LD_hl(0x40);  // left exp bar end cap
    *coord(10, 16, wram->wTilemap) = 0x40;
    // hlcoord(19, 16, wTilemap);
    // LD_hl(0x41);  // right exp bar end cap
    *coord(19, 16, wram->wTilemap) = 0x41;
    // RET;
    return;
}

static uint8_t* LoadGreenPage_GetItemName(void) {
    // LD_DE(mLoadGreenPage_ThreeDashes);
    // LD_A_addr(wTempMonItem);
    // AND_A_A;
    // RET_Z ;
    if(wram->wTempMon.mon.item == NO_ITEM)
        return U82C("---@");
    // LD_B_A;
    // FARCALL(aTimeCapsule_ReplaceTeruSama);
    item_t item = TimeCapsule_ReplaceTeruSama(wram->wTempMon.mon.item);
    // LD_A_B;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    // RET;
    return GetItemName(item);
}

static void LoadGreenPage(void){
    // LD_DE(mLoadGreenPage_Item);
    // hlcoord(0, 8, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("ITEM@"), coord(0, 8, wram->wTilemap));
    // CALL(aLoadGreenPage_GetItemName);
    // hlcoord(8, 8, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(LoadGreenPage_GetItemName(), coord(8, 8, wram->wTilemap));
    // LD_DE(mLoadGreenPage_Move);
    // hlcoord(0, 10, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("MOVE@"), coord(0, 10, wram->wTilemap));
    // LD_HL(wTempMonMoves);
    // LD_DE(wListMoves_MoveIndicesBuffer);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(wram->wListMoves_MoveIndicesBuffer, wram->wTempMon.mon.moves, NUM_MOVES);
    // hlcoord(8, 10, wTilemap);
    // LD_A(SCREEN_WIDTH * 2);
    // LD_addr_A(wListMovesLineSpacing);
    wram->wListMovesLineSpacing = SCREEN_WIDTH * 2;
    // PREDEF(pListMoves);
    ListMoves(coord(8, 10, wram->wTilemap));
    // hlcoord(12, 11, wTilemap);
    // LD_A(SCREEN_WIDTH * 2);
    // LD_addr_A(wListMovesLineSpacing);
    wram->wListMovesLineSpacing = SCREEN_WIDTH * 2;
    // PREDEF(pListMovePP);
    ListMovePP(coord(12, 11, wram->wTilemap));
    // RET;
    return;
}

// void IDNoString(void){
    //db ['"<ID>№.@"'];

    // return OTString();
// }
static const char IDNoString[] = "<ID>№.@";
static const char OTString[] = "OT/@";

// void OTString(void){
    //db ['"OT/@"'];

    // return StatsScreen_PlaceFrontpic();
// }

static void LoadBluePage_PlaceOTInfo(void) {
    // LD_DE(mIDNoString);
    // hlcoord(0, 9, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(IDNoString), coord(0, 9, wram->wTilemap));
    // LD_DE(mOTString);
    // hlcoord(0, 12, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(OTString), coord(0, 12, wram->wTilemap));
    // hlcoord(2, 10, wTilemap);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // LD_DE(wTempMonID);
    // CALL(aPrintNum);
    PrintNum(coord(2, 10, wram->wTilemap), &wram->wTempMon.mon.id, PRINTNUM_LEADINGZEROS | 2, 5);
    // LD_HL(mLoadBluePage_OTNamePointers);
    // CALL(aGetNicknamenamePointer);
    // CALL(aCopyNickname);
    // FARCALL(aCorrectNickErrors);
    // hlcoord(2, 13, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(CopyNickname(GetNicknamenamePointer()), coord(2, 13, wram->wTilemap));
    // LD_A_addr(wTempMonCaughtGender);
    uint8_t genloc = wram->wTempMon.mon.caughtGenderLocation;
    // AND_A_A;
    // IF_Z goto done;
    // CP_A(0x7f);
    // IF_Z goto done;
    if(genloc == 0
    || genloc == 0x7f) {
        return;
    }
    // AND_A(CAUGHT_GENDER_MASK);
    // LD_A(0xef);
    // IF_Z goto got_gender;
    // LD_A(0xf5);

// got_gender:
    // hlcoord(9, 13, wTilemap);
    // LD_hl_A;
    *coord(9, 13, wram->wTilemap) = ((genloc & CAUGHT_GENDER_MASK) == 0)? CHAR_MALE_ICON: CHAR_FEMALE_ICON;

// done:
    // RET;
}

static void LoadBluePage(void){
    // CALL(aLoadBluePage_PlaceOTInfo);
    LoadBluePage_PlaceOTInfo();
    // hlcoord(10, 8, wTilemap);
    // LD_DE(SCREEN_WIDTH);
    // LD_B(10);
    // LD_A(0x31);  // vertical divider

    for(uint8_t i = 0; i < 10; i++) {
    // vertical_divider:
        // LD_hl_A;
        // ADD_HL_DE;
        *coord(10, 8 + i, wram->wTilemap) = 0x31;  // vertical divider
        // DEC_B;
        // IF_NZ goto vertical_divider;
    }
    // hlcoord(11, 8, wTilemap);
    // LD_BC(6);
    // PREDEF(pPrintTempMonStats);
    PrintTempMonStats(coord(11, 8, wram->wTilemap), 6);
    // RET;
    return;


// OTNamePointers:
    //dw ['wPartyMonOTs'];
    //dw ['wOTPartyMonOTs'];
    //dw ['sBoxMonOTs'];
    //dw ['wBufferMonOT'];

    // return IDNoString();
}

static void StatsScreen_PlaceFrontpic_AnimateMon(void) {
    // LD_HL(wStatsScreenFlags);
    // SET_hl(5);
    bit_set(wram->wStatsScreenFlags, 5);
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_Z goto unown;
    if(wram->wCurPartySpecies == UNOWN) {
    // unown:
        // XOR_A_A;
        // LD_addr_A(wBoxAlignment);
        wram->wBoxAlignment = 0;
        // hlcoord(0, 0, wTilemap);
        // CALL(av_PrepMonFrontpic);
        return v_PrepMonFrontpic(coord(0, 0, wram->wTilemap));
        // RET;
    }
    // hlcoord(0, 0, wTilemap);
    // CALL(aPrepMonFrontpic);
    return PrepMonFrontpic(coord(0, 0, wram->wTilemap));
    // RET;
}

static void StatsScreen_PlaceFrontpic_get_animation(void) {
    // LD_A_addr(wCurPartySpecies);
    // CALL(aIsAPokemon);
    // RET_C ;
    if(!IsAPokemon(wram->wCurPartySpecies))
        return;
    // CALL(aStatsScreen_LoadTextboxSpaceGFX);
    StatsScreen_LoadTextboxSpaceGFX();
    //  LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    //  PREDEF(pGetAnimatedFrontpic);
    GetAnimatedFrontpic(vram->vTiles2 + LEN_2BPP_TILE * 0x00, 0);
    //  hlcoord(0, 0, wTilemap);
    //  LD_D(0x0);
    //  LD_E(ANIM_MON_MENU);
    //  PREDEF(pLoadMonAnimation);
    LoadMonAnimation(coord(0, 0, wram->wTilemap), 0x0, ANIM_MON_MENU);
    // LD_HL(wStatsScreenFlags);
    // SET_hl(6);
    bit_set(wram->wStatsScreenFlags, 6);
    // RET;
}

static void StatsScreen_PlaceFrontpic_AnimateEgg(void) {
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_Z goto unownegg;
    if(wram->wCurPartySpecies == UNOWN) {
    // unownegg:
        // XOR_A_A;
        // LD_addr_A(wBoxAlignment);
        wram->wBoxAlignment = 0;
        // CALL(aStatsScreen_PlaceFrontpic_get_animation);
        // RET;
        return StatsScreen_PlaceFrontpic_get_animation();
    }
    // LD_A(TRUE);
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = TRUE;
    // CALL(aStatsScreen_PlaceFrontpic_get_animation);
    // RET;
    return StatsScreen_PlaceFrontpic_get_animation();
}

static void StatsScreen_PlaceFrontpic(void){
    // LD_HL(wTempMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter(wram->wTempMon.mon.DVs);
    // CALL(aStatsScreen_GetAnimationParam);
    u8_flag_s res = StatsScreen_GetAnimationParam();
    // IF_C goto egg;
    if(res.flag) {
    // egg:
        // CALL(aStatsScreen_PlaceFrontpic_AnimateEgg);
        StatsScreen_PlaceFrontpic_AnimateEgg();
        // LD_A_addr(wCurPartySpecies);
        // CALL(aPlayMonCry2);
        PlayMonCry2(wram->wCurPartySpecies);
        // CALL(aSetPalettes);
        SetPalettes();
        // RET;
        return;
    }
    // AND_A_A;
    // IF_Z goto no_cry;
    if(res.a == 0) {
    // no_cry:
        // CALL(aStatsScreen_PlaceFrontpic_AnimateMon);
        StatsScreen_PlaceFrontpic_AnimateMon();
        // CALL(aSetPalettes);
        SetPalettes();
        // RET;
        return;
    }

    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aStatsScreen_PlaceFrontpic_AnimateMon);
    StatsScreen_PlaceFrontpic_AnimateMon();
    // LD_A_addr(wCurPartySpecies);
    // CALL(aPlayMonCry2);
    PlayMonCry2(wram->wCurPartySpecies);
    // RET;
    return;


// AnimateMon:
    // LD_HL(wStatsScreenFlags);
    // SET_hl(5);
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_Z goto unown;
    // hlcoord(0, 0, wTilemap);
    // CALL(aPrepMonFrontpic);
    // RET;


// unown:
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    // hlcoord(0, 0, wTilemap);
    // CALL(av_PrepMonFrontpic);
    // RET;


// AnimateEgg:
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_Z goto unownegg;
    // LD_A(TRUE);
    // LD_addr_A(wBoxAlignment);
    // CALL(aStatsScreen_PlaceFrontpic_get_animation);
    // RET;


// unownegg:
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    // CALL(aStatsScreen_PlaceFrontpic_get_animation);
    // RET;


// get_animation:
    // LD_A_addr(wCurPartySpecies);
    // CALL(aIsAPokemon);
    // RET_C ;
    // CALL(aStatsScreen_LoadTextboxSpaceGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // PREDEF(pGetAnimatedFrontpic);
    // hlcoord(0, 0, wTilemap);
    // LD_D(0x0);
    // LD_E(ANIM_MON_MENU);
    // PREDEF(pLoadMonAnimation);
    // LD_HL(wStatsScreenFlags);
    // SET_hl(6);
    // RET;

}

static u8_flag_s StatsScreen_GetAnimationParam(void){
    // LD_A_addr(wMonType);
    // LD_HL(mStatsScreen_GetAnimationParam_Jumptable);
    // RST(aJumpTable);
    // RET;


// Jumptable:
    //dw ['.PartyMon'];
    //dw ['.OTPartyMon'];
    //dw ['.BoxMon'];
    //dw ['.Tempmon'];
    //dw ['.Wildmon'];
    struct PartyMon* bc;
    switch(wram->wMonType) {
        case PARTYMON:
        // PartyMon:
            // LD_A_addr(wCurPartyMon);
            // LD_HL(wPartyMon1);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // CALL(aAddNTimes);
            // LD_B_H;
            // LD_C_L;
            bc = gPokemon.partyMon + wram->wCurPartyMon;
            // goto CheckEggFaintedFrzSlp;
        // CheckEggFaintedFrzSlp:
            // LD_A_addr(wCurPartySpecies);
            // CP_A(EGG);
            // IF_Z goto egg;
            // CALL(aCheckFaintedFrzSlp);
            // IF_C goto FaintedFrzSlp;
            if(wram->wCurPartySpecies == EGG || !CheckFaintedFrzSlp(bc)) {
            // egg:
                // XOR_A_A;
                // SCF;
                // RET;
                return (u8_flag_s){.flag = true, .a = 0};
            }
        // FaintedFrzSlp:
            // XOR_A_A;
            // RET;
            return (u8_flag_s){.flag = false, .a = 0};
        case OTPARTYMON: 
        // OTPartyMon:
            // XOR_A_A;
            // RET;
            return (u8_flag_s){.flag=false, .a = 0};
        case BOXMON: {
        // BoxMon:
            // LD_HL(sBoxMons);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // LD_B_H;
            // LD_C_L;
            // LD_A(BANK(sBoxMons));
            // CALL(aOpenSRAM);
            OpenSRAM(MBANK(asBoxMons));
            struct PartyMon* bc = GBToRAMAddr(sBoxMons + (wram->wCurPartyMon * PARTYMON_STRUCT_LENGTH));
            // CALL(aStatsScreen_GetAnimationParam_CheckEggFaintedFrzSlp);
            u8_flag_s res;
            if(wram->wCurPartySpecies == EGG || !CheckFaintedFrzSlp(bc)) {
            // egg:
                // XOR_A_A;
                // SCF;
                // RET;
                res = (u8_flag_s){.flag = true, .a = 0};
            }
            else {
                res = (u8_flag_s){.flag = false, .a = 0};
            }
            // PUSH_AF;
            // CALL(aCloseSRAM);
            CloseSRAM();
            // POP_AF;
            // RET;
            return res;
        }
        case TEMPMON:
        // Tempmon:
            // LD_BC(wTempMonSpecies);
            bc = &wram->wTempMon;
        // CheckEggFaintedFrzSlp:
            // LD_A_addr(wCurPartySpecies);
            // CP_A(EGG);
            // IF_Z goto egg;
            // CALL(aCheckFaintedFrzSlp);
            // IF_C goto FaintedFrzSlp;
            if(wram->wCurPartySpecies == EGG || !CheckFaintedFrzSlp(bc)) {
            // egg:
                // XOR_A_A;
                // SCF;
                // RET;
                return (u8_flag_s){.flag = true, .a = 0};
            }
        // FaintedFrzSlp:
            // XOR_A_A;
            // RET;
            return (u8_flag_s){.flag = false, .a = 0};
        case WILDMON: 
        // Wildmon:
            // LD_A(0x1);
            // AND_A_A;
            // RET;
            return (u8_flag_s){.flag=false, .a = 1};
    }
    return (u8_flag_s){.flag = false, .a = 0};
}

void StatsScreen_LoadTextboxSpaceGFX(void){
    // NOP;
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // PUSH_AF;
    // CALL(aDelayFrame);
    DelayFrame();
    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_DE(mTextboxSpaceGFX);
    // LD_BC((BANK(aTextboxSpaceGFX) << 8) | 1);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_SPACE);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles5 + LEN_2BPP_TILE * CHAR_SPACE, "gfx/font/space.png", 0, 1);
    // POP_AF;
    // LDH_addr_A(rVBK);
    // POP_AF;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void StatsScreenSpaceGFX(void){
//  //  unreferenced
// INCBIN "gfx/font/space.2bpp"
}

void EggStatsScreen(void){
    static const char EggString[] = "EGG@";
    static const char FiveQMarkString[] = "?????@";

    static const char EggSoonString[] = 
                "It's making sounds"
        t_next  "inside. It's going"
        t_next  "to hatch soon!@";

    static const char EggCloseString[] = 
                "It moves around"
        t_next  "inside sometimes."
        t_next  "It must be close"
        t_next  "to hatching.@";

    static const char EggMoreTimeString[] = 
                "Wonder what's"
        t_next  "inside? It needs"
        t_next  "more time, though.@";

    static const char EggALotMoreTimeString[] = 
                "This EGG needs a"
        t_next  "lot more time to"
        t_next  "hatch.@";
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // LD_HL(wCurHPPal);
    // CALL(aSetHPPal);
    SetHPPal(&wram->wCurHPPal, wram->wStatsScreenFlags);
    // LD_B(SCGB_STATS_SCREEN_HP_PALS);
    // CALL(aGetSGBLayout);
    // CALL(aStatsScreen_PlaceHorizontalDivider);
    StatsScreen_PlaceHorizontalDivider();
    // LD_DE(mEggString);
    // hlcoord(8, 1, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(Utf8ToCrystal(EggString), coord(8, 1, wram->wTilemap));
    // LD_DE(mIDNoString);
    // hlcoord(8, 3, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(Utf8ToCrystal(IDNoString), coord(8, 3, wram->wTilemap));
    // LD_DE(mOTString);
    // hlcoord(8, 5, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(Utf8ToCrystal(OTString), coord(8, 5, wram->wTilemap));
    // LD_DE(mFiveQMarkString);
    // hlcoord(11, 3, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(Utf8ToCrystal(FiveQMarkString), coord(11, 3, wram->wTilemap));
    // LD_DE(mFiveQMarkString);
    // hlcoord(11, 5, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(Utf8ToCrystal(FiveQMarkString), coord(11, 5, wram->wTilemap));
#if defined(_DEBUG)
    // LD_DE(EggStatsScreen_PushStartString);
    // hlcoord(8, 17, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(Utf8ToCrystal("▶PUSH START.@"), coord(8, 17, wram->wTilemap));
    // goto placed_push_start;


// PushStartString:
    //db ['"▶PUSH START.@"'];


// placed_push_start:
#endif
    // LD_A_addr(wTempMonHappiness);  // egg status
    uint8_t a = wram->wTempMon.mon.happiness;
    const char* de;
    // LD_DE(mEggSoonString);
    // CP_A(0x6);
    // IF_C goto picked;
    if(a < 0x6) {
        de = EggSoonString;
    }
    // LD_DE(mEggCloseString);
    // CP_A(0xb);
    // IF_C goto picked;
    else if(a < 0xb) {
        de = EggCloseString;
    }
    // LD_DE(mEggMoreTimeString);
    // CP_A(0x29);
    // IF_C goto picked;
    else if(a < 0x29) {
        de = EggMoreTimeString;
    }
    else {
        // LD_DE(mEggALotMoreTimeString);
        de = EggALotMoreTimeString;
    }

// picked:
    // hlcoord(1, 9, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(Utf8ToCrystal(de), coord(1, 9, wram->wTilemap));
    // LD_HL(wStatsScreenFlags);
    // SET_hl(5);
    bit_set(wram->wStatsScreenFlags, 5);
    // CALL(aSetPalettes);  // pals
    SetPalettes();
    // CALL(aDelayFrame);
    DelayFrame();
    // hlcoord(0, 0, wTilemap);
    // CALL(aPrepMonFrontpic);
    PrepMonFrontpic(coord(0, 0, wram->wTilemap));
    // FARCALL(aHDMATransferTilemapToWRAMBank3);
    HDMATransferTilemapToWRAMBank3();
    // CALL(aStatsScreen_AnimateEgg);
    StatsScreen_AnimateEgg();

    // LD_A_addr(wTempMonHappiness);
    // CP_A(6);
    // RET_NC ;
    if(wram->wTempMon.mon.happiness >= 6)
        return;
    // LD_DE(SFX_2_BOOPS);
    // CALL(aPlaySFX);
    // RET;
    PlaySFX(SFX_2_BOOPS);
}

static void StatsScreen_AnimateEgg(void){
    // CALL(aStatsScreen_GetAnimationParam);
    u8_flag_s res = StatsScreen_GetAnimationParam();
    // RET_NC ;
    if(!res.flag)
        return;
    // LD_A_addr(wTempMonHappiness);
    // LD_E(0x7);
    uint8_t e;
    if(wram->wTempMon.mon.happiness < 6)
        e = 0x7;
    // CP_A(6);
    // IF_C goto animate;
    // LD_E(0x8);
    // CP_A(11);
    // IF_C goto animate;
    else if(wram->wTempMon.mon.happiness < 11)
        e = 0x8;
    else
        // RET;
        return;

// animate:
    // PUSH_DE;
    // LD_A(0x1);
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x1;
    // CALL(aStatsScreen_LoadTextboxSpaceGFX);
    StatsScreen_LoadTextboxSpaceGFX();
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // PREDEF(pGetAnimatedFrontpic);
    GetAnimatedFrontpic(vram->vTiles2 + LEN_2BPP_TILE * 0x00, 0);
    // POP_DE;
    // hlcoord(0, 0, wTilemap);
    // LD_D(0x0);
    // PREDEF(pLoadMonAnimation);
    LoadMonAnimation(coord(0, 0, wram->wTilemap), 0x0, e);
    // LD_HL(wStatsScreenFlags);
    // SET_hl(6);
    bit_set(wram->wStatsScreenFlags, 6);
    // RET;
}

static void StatsScreen_LoadPageIndicators_load_square(uint8_t* hl, uint8_t a) {
// load_square:
    // PUSH_BC;
    // LD_hli_A;
    hl[0] = a;
    // INC_A;
    // LD_hld_A;
    hl[1] = a + 1;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    // INC_A;
    // LD_hli_A;
    hl[SCREEN_WIDTH] = a + 2;
    // INC_A;
    // LD_hl_A;
    hl[SCREEN_WIDTH + 1] = a + 3;
    // POP_BC;
    // RET;
}

static void StatsScreen_LoadPageIndicators(uint8_t c){
    // hlcoord(13, 5, wTilemap);
    // LD_A(0x36);  // first of 4 small square tiles
    // CALL(aStatsScreen_LoadPageIndicators_load_square);
    StatsScreen_LoadPageIndicators_load_square(coord(13, 5, wram->wTilemap), 0x36);  // first of 4 small square tiles
    // hlcoord(15, 5, wTilemap);
    // LD_A(0x36);  // " " " "
    // CALL(aStatsScreen_LoadPageIndicators_load_square);
    StatsScreen_LoadPageIndicators_load_square(coord(15, 5, wram->wTilemap), 0x36);  // " " " "
    // hlcoord(17, 5, wTilemap);
    // LD_A(0x36);  // " " " "
    // CALL(aStatsScreen_LoadPageIndicators_load_square);
    StatsScreen_LoadPageIndicators_load_square(coord(17, 5, wram->wTilemap), 0x36);  // " " " "
    // LD_A_C;
    // CP_A(GREEN_PAGE);
    switch(c)
    {
        // LD_A(0x3a);  // first of 4 large square tiles
        // hlcoord(13, 5, wTilemap);  // PINK_PAGE (< GREEN_PAGE)
        // IF_C goto load_square;
        case PINK_PAGE: return StatsScreen_LoadPageIndicators_load_square(coord(13, 5, wram->wTilemap), 0x3a);  // first of 4 large square tiles
        // hlcoord(15, 5, wTilemap);  // GREEN_PAGE (= GREEN_PAGE)
        // IF_Z goto load_square;
        case GREEN_PAGE: return StatsScreen_LoadPageIndicators_load_square(coord(15, 5, wram->wTilemap), 0x3a);  // first of 4 large square tiles
        // hlcoord(17, 5, wTilemap);  // BLUE_PAGE (> GREEN_PAGE)
        default:
            return StatsScreen_LoadPageIndicators_load_square(coord(17, 5, wram->wTilemap), 0x3a);  // first of 4 large square tiles
    }
}

static uint8_t* CopyNickname(uint8_t* hl){
    // LD_DE(wStringBuffer1);
    // LD_BC(MON_NAME_LENGTH);
    // goto okay;  // utterly pointless

// okay:
    // LD_A_addr(wMonType);
    // CP_A(BOXMON);
    // IF_NZ goto partymon;
    if(wram->wMonType == BOXMON) {
        // LD_A(BANK(sBoxMonNicknames));
        // CALL(aOpenSRAM);
        // PUSH_DE;
        // CALL(aCopyBytes);
        // POP_DE;
        // CALL(aCloseSRAM);
        // RET;
        return wram->wStringBuffer1;
    }
    else {
    // partymon:
        // PUSH_DE;
        // CALL(aCopyBytes);
        // POP_DE;
        // RET;
        CopyBytes(wram->wStringBuffer1, hl, MON_NAME_LENGTH);
        return wram->wStringBuffer1;
    }

}

static uint8_t* GetNicknamenamePointer(void){
    // LD_A_addr(wMonType);
    // ADD_A_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    switch(wram->wMonType) {
        case PARTYMON:
            return gPokemon.partyMonOT[wram->wCurPartyMon];
        case OTPARTYMON:
            return wram->wOTPartyMonOT[wram->wCurPartyMon];
        case BOXMON: {
            OpenSRAM(MBANK(asBoxMonOTs));
            CopyBytes(wram->wStringBuffer1, GBToRAMAddr(sBoxMonOTs + (wram->wCurPartyMon * NAME_LENGTH)), NAME_LENGTH);
            CloseSRAM();
            return wram->wStringBuffer1;
        }
        case TEMPMON:
            return wram->wBufferMonOT;
    }
    return NULL;
    // LD_A_addr(wMonType);
    // CP_A(TEMPMON);
    // RET_Z ;
    // LD_A_addr(wCurPartyMon);
    // JP(mSkipNames);

}

static uint8_t* GetNicknamenamePointer2(void){
    // LD_A_addr(wMonType);
    // ADD_A_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    switch(wram->wMonType) {
        case PARTYMON:
            return gPokemon.partyMonNickname[wram->wCurPartyMon];
        case OTPARTYMON:
            return wram->wOTPartyMonNickname[wram->wCurPartyMon];
        case BOXMON: {
            OpenSRAM(MBANK(asBoxMonNicknames));
            CopyBytes(wram->wStringBuffer1, GBToRAMAddr(sBoxMonNicknames), MON_NAME_LENGTH);
            CloseSRAM();
            return wram->wStringBuffer1;
        }
        case TEMPMON:
            return wram->wBufferMonNickname;
    }
    return NULL;
    // LD_A_addr(wMonType);
    // CP_A(TEMPMON);
    // RET_Z ;
    // LD_A_addr(wCurPartyMon);
    // JP(mSkipNames);

}

bool CheckFaintedFrzSlp(struct PartyMon* bc){
    // LD_HL(MON_HP);
    // ADD_HL_BC;
    // LD_A_hli;
    // OR_A_hl;
    // IF_Z goto fainted_frz_slp;
    if((bc->HP | bc->maxHP) == 0) 
        return true;
    // LD_HL(MON_STATUS);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(1 << FRZ | SLP);
    // IF_NZ goto fainted_frz_slp;
    if(bc->status & (1 << FRZ | SLP))
        return true;
    // AND_A_A;
    // RET;
    return false;

// fainted_frz_slp:
    // SCF;
    // RET;
}
