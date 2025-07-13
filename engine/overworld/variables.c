#include "../../constants.h"
#include "variables.h"
#include "../../home/pokedex_flags.h"
#include "../../home/sram.h"

static uint8_t* VarAction_loadstringbuffer2(uint8_t a);

static uint8_t* VarAction_CountCaughtMons(void);
static uint8_t* VarAction_CountBadges(void);
static uint8_t* VarAction_CountSeenMons(void);
static uint8_t* VarAction_PlayerFacing(void);
static uint8_t* VarAction_DayOfWeek(void);
static uint8_t* VarAction_UnownCaught(void);
static uint8_t* VarAction_BoxFreeSpace(void);
static uint8_t* VarAction_BattleResult(void);

struct VarAction {
    union {
        uint8_t* const var;
        uint8_t* (*const fun)(void);
    };
    uint8_t action;
};

static const struct VarAction VarActionTable[] = {
//  entries correspond to VAR_* constants
// RETVAR_STRBUF2: copy [de] to wStringBuffer2
// RETVAR_ADDR_DE: return address in de
// RETVAR_EXECUTE: call function
    [VAR_STRINGBUFFER2]     = {.var=wram_ptr(wStringBuffer2), RETVAR_STRBUF2},
    [VAR_PARTYCOUNT]        = {.var=&gPokemon.partyCount, RETVAR_STRBUF2},
    [VAR_BATTLERESULT]      = {.fun=VarAction_BattleResult, RETVAR_EXECUTE},
    [VAR_BATTLETYPE]        = {.var=wram_ptr(wBattleType), RETVAR_ADDR_DE},
    [VAR_TIMEOFDAY]         = {.var=wram_ptr(wTimeOfDay), RETVAR_STRBUF2},
    [VAR_DEXCAUGHT]         = {.fun=VarAction_CountCaughtMons, RETVAR_EXECUTE},
    [VAR_DEXSEEN]           = {.fun=VarAction_CountSeenMons, RETVAR_EXECUTE},
    [VAR_BADGES]            = {.fun=VarAction_CountBadges, RETVAR_EXECUTE},
    [VAR_MOVEMENT]          = {.var=wram_ptr(wPlayerState), RETVAR_ADDR_DE},
    [VAR_FACING]            = {.fun=VarAction_PlayerFacing, RETVAR_EXECUTE},
    [VAR_HOUR]              = {.var=&hram.hHours, RETVAR_STRBUF2},
    [VAR_WEEKDAY]           = {.fun=VarAction_DayOfWeek, RETVAR_EXECUTE},
    [VAR_MAPGROUP]          = {.var=&gCurMapData.mapGroup, RETVAR_STRBUF2},
    [VAR_MAPNUMBER]         = {.var=&gCurMapData.mapNumber, RETVAR_STRBUF2},
    [VAR_UNOWNCOUNT]        = {.fun=VarAction_UnownCaught, RETVAR_EXECUTE},
    [VAR_ENVIRONMENT]       = {.var=wram_ptr(wEnvironment), RETVAR_STRBUF2},
    [VAR_BOXSPACE]          = {.fun=VarAction_BoxFreeSpace, RETVAR_EXECUTE},
    [VAR_CONTESTMINUTES]    = {.var=wram_ptr(wBugContestMinsRemaining), RETVAR_STRBUF2},
    [VAR_XCOORD]            = {.var=&gCurMapData.xCoord, RETVAR_STRBUF2},
    [VAR_YCOORD]            = {.var=&gCurMapData.yCoord, RETVAR_STRBUF2},
    [VAR_SPECIALPHONECALL]  = {.var=wram_ptr(wSpecialPhoneCallID), RETVAR_STRBUF2},
    [VAR_BT_WIN_STREAK]     = {.var=wram_ptr(wNrOfBeatenBattleTowerTrainers), RETVAR_STRBUF2},
    [VAR_KURT_APRICORNS]    = {.var=wram_ptr(wKurtApricornQuantity), RETVAR_STRBUF2},
    [VAR_CALLERID]          = {.var=wram_ptr(wCurCaller), RETVAR_ADDR_DE},
    [VAR_BLUECARDBALANCE]   = {.var=wram_ptr(wBlueCardBalance), RETVAR_ADDR_DE},
    [VAR_BUENASPASSWORD]    = {.var=wram_ptr(wBuenasPassword), RETVAR_ADDR_DE},
    [VAR_KENJI_BREAK]       = {.var=wram_ptr(wKenjiBreakTimer), RETVAR_STRBUF2},
};

static_assert(lengthof(VarActionTable) == NUM_VARS, "");

uint8_t* v_GetVarAction(uint8_t c){
    // LD_A_C;
    // CP_A(NUM_VARS);
    // IF_C goto valid;
    // XOR_A_A;
    uint8_t var = (c < NUM_VARS)? c: 0;

// valid:
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mv_GetVarAction_VarActionTable);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // ADD_HL_BC;
    const struct VarAction* const hl = &VarActionTable[var];
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // INC_HL;
    // LD_B_hl;
    // LD_A_B;
    // AND_A(RETVAR_EXECUTE);
    // IF_NZ goto call;
    if(hl->action & RETVAR_EXECUTE)
        return hl->fun();
    // LD_A_B;
    // AND_A(RETVAR_ADDR_DE);
    // RET_NZ ;
    if(hl->action & RETVAR_ADDR_DE)
        return hl->var;
    // LD_A_de;
    // goto loadstringbuffer2;
    return VarAction_loadstringbuffer2(*hl->var);


// call:
    // CALL(av_de_);
    // RET;


// loadstringbuffer2:
    // LD_DE(wStringBuffer2);
    // LD_de_A;
    // RET;
}

static uint8_t* VarAction_loadstringbuffer2(uint8_t a) {
// loadstringbuffer2:
    // LD_DE(wStringBuffer2);
    // LD_de_A;
    wram->wStringBuffer2[0] = a;
    // RET;
    return wram->wStringBuffer2;
}

static uint8_t* VarAction_CountCaughtMons(void) {
//  Caught mons.
    // LD_HL(wPokedexCaught);
    // LD_B(wEndPokedexCaught - wPokedexCaught);
    // CALL(aCountSetBits);
    uint8_t a = CountSetBits(gPokemon.pokedexCaught, sizeof(gPokemon.pokedexCaught));
    // LD_A_addr(wNumSetBits);
    wram->wNumSetBits = a;
    // JP(mv_GetVarAction_loadstringbuffer2);
    return VarAction_loadstringbuffer2(a);
}

static uint8_t* VarAction_CountBadges(void) {
//  Number of owned badges.
    // LD_HL(wBadges);
    // LD_B(2);
    // CALL(aCountSetBits);
    uint8_t a = CountSetBits(wram->wJohtoBadges, 1) + CountSetBits(wram->wKantoBadges, 1);
    // LD_A_addr(wNumSetBits);
    wram->wNumSetBits = a;
    // JP(mv_GetVarAction_loadstringbuffer2);
    return VarAction_loadstringbuffer2(a);
}

static uint8_t* VarAction_CountSeenMons(void) {
// CountSeenMons:
//  Seen mons.
    // LD_HL(wPokedexSeen);
    // LD_B(wEndPokedexSeen - wPokedexSeen);
    // CALL(aCountSetBits);
    uint8_t a = CountSetBits(gPokemon.pokedexSeen, sizeof(gPokemon.pokedexSeen));
    // LD_A_addr(wNumSetBits);
    wram->wNumSetBits = a;
    // JP(mv_GetVarAction_loadstringbuffer2);
    return VarAction_loadstringbuffer2(a);
}

static uint8_t* VarAction_PlayerFacing(void) {
//  The direction the player is facing.
    // LD_A_addr(wPlayerDirection);
    // AND_A(0xc);
    // RRCA;
    // RRCA;
    // JP(mv_GetVarAction_loadstringbuffer2);
    return VarAction_loadstringbuffer2((wram->wPlayerStruct.facing & 0xc) >> 2);
}

static uint8_t* VarAction_DayOfWeek(void) {
//  The day of the week.
    // CALL(aGetWeekday);
    // JP(mv_GetVarAction_loadstringbuffer2);
    return VarAction_loadstringbuffer2(GetWeekday());
}

static uint8_t* VarAction_UnownCaught(void) {
//  Number of unique Unown caught.
    // CALL(av_GetVarAction_count_unown);
// count_unown:
    // LD_HL(wUnownDex);
    uint8_t* hl = gPokemon.unownDex;
    // LD_B(0);
    uint8_t a = 0;

    for(int i = 0; i < NUM_UNOWN; ++i) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // RET_Z ;
        if(hl[i] == 0)
            break;
        // INC_B;
        a++;
        // LD_A_B;
        // CP_A(NUM_UNOWN);
        // IF_C goto loop;
    }
    // RET;
    // LD_A_B;
    // JP(mv_GetVarAction_loadstringbuffer2);
    return VarAction_loadstringbuffer2(a);
}

static uint8_t* VarAction_BoxFreeSpace(void) {
//  Remaining slots in the current box.
    // LD_A(BANK(sBoxCount));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxCount));
    // LD_HL(sBoxCount);
    // LD_A(MONS_PER_BOX);
    // SUB_A_hl;
    // LD_B_A;
    uint8_t b = MONS_PER_BOX - gb_read(sBoxCount);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A_B;
    // JP(mv_GetVarAction_loadstringbuffer2);
    return VarAction_loadstringbuffer2(b);
}

static uint8_t* VarAction_BattleResult(void) {
    // LD_A_addr(wBattleResult);
    // AND_A(~BATTLERESULT_BITMASK);
    // JP(mv_GetVarAction_loadstringbuffer2);
    return VarAction_loadstringbuffer2(wram->wBattleResult & ~BATTLERESULT_BITMASK);
}