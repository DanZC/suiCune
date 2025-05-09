#include "../../constants.h"
#include "treemons.h"
#include "../../data/wild/treemons.h"
#include "../../data/wild/treemon_maps.h"
#include "../../home/map.h"
#include "../../home/random.h"
#include "../../mobile/mobile_41.h"

static u8_flag_s GetTreeMonSet(const struct TreeMonMap table[], size_t table_size);
static const uint8_t* GetTreeMons(uint8_t a);
static bool GetTreeMon(const uint8_t* hl);
static bool SelectTreeMon(const uint8_t* hl);
static bool NoTreeMon(void);
static uint8_t GetTreeScore(void);

void TreeMonEncounter(void){
    // FARCALL(aStubbedTrainerRankings_TreeEncounters);
    StubbedTrainerRankings_TreeEncounters();

    // XOR_A_A;
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = 0;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = 0;

    // LD_HL(mTreeMonMaps);
    // CALL(aGetTreeMonSet);
    u8_flag_s res = GetTreeMonSet(TreeMonMaps, TreeMonMaps_Size);
    // IF_NC goto no_battle;
    if(!res.flag) {
        wram->wScriptVar = FALSE;
        return;
    }

    // CALL(aGetTreeMons);
    // IF_NC goto no_battle;
    const uint8_t* hl = GetTreeMons(res.a);
    if(hl == NULL) {
        wram->wScriptVar = FALSE;
        return;
    }

    // CALL(aGetTreeMon);
    // IF_NC goto no_battle;
    if(!GetTreeMon(hl)) {
        wram->wScriptVar = FALSE;
        return;
    }

    // LD_A(BATTLETYPE_TREE);
    // LD_addr_A(wBattleType);
    wram->wBattleType = BATTLETYPE_TREE;
    // LD_A(1);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
    return;

// no_battle:
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // RET;
}

void RockMonEncounter(void){
    // XOR_A_A;
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = 0;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = 0;

    // LD_HL(mRockMonMaps);
    // CALL(aGetTreeMonSet);
    u8_flag_s res = GetTreeMonSet(RockMonMaps, RockMonMaps_Size);
    // IF_NC goto no_battle;
    if(!res.flag) {
        return;
    }

    // CALL(aGetTreeMons);
    // IF_NC goto no_battle;
    const uint8_t* hl = GetTreeMons(res.a);
    if(hl == NULL) {
        return;
    }

// 40% chance of an encounter
    // LD_A(10);
    // CALL(aRandomRange);
    // CP_A(4);
    // IF_NC goto no_battle;
    if(RandomRange(10) >= 4) {
        return;
    }

    // CALL(aSelectTreeMon);
    // IF_NC goto no_battle;
    if(!SelectTreeMon(hl))
        return;

    // RET;
    return;

// no_battle:
    // XOR_A_A;
    // RET;

    //db ['0x05'];  // ????

}

//  Return carry and treemon set in a
//  if the current map is in table hl.
static u8_flag_s GetTreeMonSet(const struct TreeMonMap table[], size_t table_size){
    // LD_A_addr(wMapNumber);
    // LD_E_A;
    // LD_A_addr(wMapGroup);
    // LD_D_A;

    for(size_t i = 0; i < table_size; ++i) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto not_in_table;

        // CP_A_D;
        // IF_NZ goto skip2;

        // LD_A_hli;
        // CP_A_E;
        // IF_NZ goto skip1;

        // goto in_table;
        if(wram->wMapGroup == table[i].mapGroup
        && wram->wMapNumber == table[i].mapNumber) {
        // in_table:
            // LD_A_hl;
            // SCF;
            // RET;
            return u8_flag(table[i].set, true);
        }


    // skip2:
        // INC_HL;

    // skip1:
        // INC_HL;
        // goto loop;
    }

// not_in_table:
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);

// INCLUDE "data/wild/treemon_maps.asm"
}

//  Return the address of TreeMon table a in hl.
//  Return nc if table a doesn't exist.
static const uint8_t* GetTreeMons(uint8_t a){
    // CP_A(NUM_TREEMON_SETS);
    // IF_NC goto quit;

    // AND_A_A;
    // IF_Z goto quit;
    if(a >= NUM_TREEMON_SETS || a == 0) {
        return NULL;
    }

    // LD_E_A;
    // LD_D(0);
    // LD_HL(mTreeMons);
    // ADD_HL_DE;
    // ADD_HL_DE;

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

    // SCF;
    // RET;


// quit:
    // XOR_A_A;
    // RET;
    return TreeMons[a];
// INCLUDE "data/wild/treemons.asm"
}

static bool GetTreeMon(const uint8_t* hl){
    // PUSH_HL;
    // CALL(aGetTreeScore);
    // POP_HL;
    // AND_A_A;  // TREEMON_SCORE_BAD
    // IF_Z goto bad;
    // CP_A(TREEMON_SCORE_GOOD);
    // IF_Z goto good;
    // CP_A(TREEMON_SCORE_RARE);
    // IF_Z goto rare;
    // RET;
    switch(GetTreeScore()) {
    case TREEMON_SCORE_BAD:
    // bad:
    // 10% chance of an encounter
        // LD_A(10);
        // CALL(aRandomRange);
        // AND_A_A;
        // JR_NZ (mNoTreeMon);
        if(RandomRange(10))
            return NoTreeMon();
        // JR(mSelectTreeMon);
        return SelectTreeMon(hl);

    case TREEMON_SCORE_GOOD:
    // good:
    // 50% chance of an encounter
        // LD_A(10);
        // CALL(aRandomRange);
        // CP_A(5);
        // JR_NC (mNoTreeMon);
        if(RandomRange(10) >= 5)
            return NoTreeMon();
        // JR(mSelectTreeMon);
        return SelectTreeMon(hl);

    case TREEMON_SCORE_RARE:
    // rare:
    // 80% chance of an encounter
        // LD_A(10);
        // CALL(aRandomRange);
        // CP_A(8);
        // JR_NC (mNoTreeMon);
        if(RandomRange(10) >= 8)
            return NoTreeMon();
        // goto skip;

        while(*(hl++) != 0xff)
        {
        // skip:
            // LD_A_hli;
            // CP_A(-1);
            // IF_NZ goto skip;
        }
        // CALL(aSelectTreeMon);
        return SelectTreeMon(hl);
        // RET;
    }
    return false;
}

//  Read a TreeMons table and pick one monster at random.
static bool SelectTreeMon(const uint8_t* hl){
    // LD_A(100);
    // CALL(aRandomRange);
    uint8_t a = RandomRange(100);

    while(a >= *hl) {
    // loop:
        // SUB_A_hl;
        // IF_C goto ok;
        // INC_HL;
        // INC_HL;
        // INC_HL;
        // goto loop;
        hl += 3;
    }


// ok:
    // LD_A_hli;
    // CP_A(-1);
    // JR_Z (mNoTreeMon);
    if(*hl == 0xff) {
        return NoTreeMon();
    }

    // LD_A_hli;
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = hl[1];
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = hl[2];
    // SCF;
    // RET;
    return true;
}

static bool NoTreeMon(void){
    // XOR_A_A;
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = 0;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = 0;
    // RET;
    return false;
}

static uint8_t GetTreeScore_CoordScore(void) {
    // CALL(aGetFacingTileCoord);
    struct CoordsTileId cid = GetFacingTileCoord();
    // LD_HL(0);
    // LD_C_E;
    // LD_B(0);
    // LD_A_D;

    // AND_A_A;
    // IF_Z goto next;
// loop:
    // ADD_HL_BC;
    // DEC_A;
    // IF_NZ goto loop;

// next:

    // ADD_HL_BC;
    // LD_C_D;
    // ADD_HL_BC;
    uint32_t hl = cid.y * (cid.x + 1) + cid.x;
    // LD_A_H;
    // LDH_addr_A(hDividend);
    // LD_A_L;
    // LDH_addr_A(hDividend + 1);
    // LD_A(5);
    // LDH_addr_A(hDivisor);
    // LD_B(2);
    // CALL(aDivide);
    hl /= 5;

    // LDH_A_addr(hQuotient + 2);
    // LDH_addr_A(hDividend);
    // LDH_A_addr(hQuotient + 3);
    // LDH_addr_A(hDividend + 1);
    // LD_A(10);
    // LDH_addr_A(hDivisor);
    // LD_B(2);
    // CALL(aDivide);
    hl /= 10;

    // LDH_A_addr(hRemainder);
    // RET;
    return (uint8_t)hl;
}

static uint8_t GetTreeScore_OTIDScore(void) {
    // LD_A_addr(wPlayerID);
    // LDH_addr_A(hDividend);
    // LD_A_addr(wPlayerID + 1);
    // LDH_addr_A(hDividend + 1);
    // LD_A(10);
    // LDH_addr_A(hDivisor);
    // LD_B(2);
    // CALL(aDivide);
    // LDH_A_addr(hRemainder);
    // RET;
    return (uint8_t)(BigEndianToNative16(wram->wPlayerID) / 10);
}

static uint8_t GetTreeScore(void){
    // CALL(aGetTreeScore_CoordScore);
    // LD_addr_A(wTreeMonCoordScore);
    wram->wTreeMonCoordScore = GetTreeScore_CoordScore();
    // CALL(aGetTreeScore_OTIDScore);
    // LD_addr_A(wTreeMonOTIDScore);
    wram->wTreeMonOTIDScore = GetTreeScore_OTIDScore();
    // LD_C_A;
    uint8_t c = wram->wTreeMonOTIDScore;
    // LD_A_addr(wTreeMonCoordScore);
    uint8_t a = wram->wTreeMonCoordScore;
    // SUB_A_C;
    // IF_Z goto rare;
    if(a == c) {
    // rare:
        // LD_A(TREEMON_SCORE_RARE);
        // RET;
        return TREEMON_SCORE_RARE;
    }
    // IF_NC goto ok;
    if(a < c) {
        // ADD_A(10);
        a += 10;
    }
    a -= c;

// ok:
    // CP_A(5);
    // IF_C goto good;
    if(a >= 5) {
    //  bad
        // XOR_A_A;  // TREEMON_SCORE_BAD
        // RET;
        return TREEMON_SCORE_BAD;
    }
    else {
    // good:
        // LD_A(TREEMON_SCORE_GOOD);
        // RET;
        return TREEMON_SCORE_GOOD;
    }
}
