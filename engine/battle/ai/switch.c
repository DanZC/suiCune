#include "../../../constants.h"
#include "switch.h"
#include "../../../data/moves/moves.h"
#include "../effect_commands.h"

void CheckPlayerMoveTypeMatchups(void){
//  Check how well the moves you've already used
//  fare against the enemy's Pokemon.  Used to
//  score a potential switch.
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A(BASE_AI_SWITCH_SCORE);
    LD_addr_A(wEnemyAISwitchScore);
    LD_HL(wPlayerUsedMoves);
    LD_A_hl;
    AND_A_A;
    IF_Z goto unknown_moves;

    LD_D(NUM_MOVES);
    LD_E(0);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto exit;
    PUSH_HL;
    DEC_A;
    LD_HL(mMoves + MOVE_POWER);
    CALL(aGetMoveAttr);
    AND_A_A;
    IF_Z goto next;

    INC_HL;
    CALL(aGetMoveByte);
    LD_HL(wEnemyMonType);
    CALL(aCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE + 1);  // 1.0 + 0.1
    IF_NC goto super_effective;
    AND_A_A;
    IF_Z goto next;
    CP_A(EFFECTIVE);  // 1.0
    IF_NC goto neutral;

//  not very effective
    LD_A_E;
    CP_A(1);  // 0.1
    IF_NC goto next;
    LD_E(1);
    goto next;


neutral:
    LD_E(2);
    goto next;


super_effective:
    CALL(aCheckPlayerMoveTypeMatchups_DecreaseScore);
    POP_HL;
    goto done;


next:
    POP_HL;
    DEC_D;
    IF_NZ goto loop;


exit:
    LD_A_E;
    CP_A(2);
    IF_Z goto done;
    CALL(aCheckPlayerMoveTypeMatchups_IncreaseScore);
    LD_A_E;
    AND_A_A;
    IF_NZ goto done;
    CALL(aCheckPlayerMoveTypeMatchups_IncreaseScore);
    goto done;


unknown_moves:
    LD_A_addr(wBattleMonType1);
    LD_B_A;
    LD_HL(wEnemyMonType1);
    CALL(aCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE + 1);  // 1.0 + 0.1
    IF_C goto ok;
    CALL(aCheckPlayerMoveTypeMatchups_DecreaseScore);

ok:
    LD_A_addr(wBattleMonType2);
    CP_A_B;
    IF_Z goto ok2;
    CALL(aCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE + 1);  // 1.0 + 0.1
    IF_C goto ok2;
    CALL(aCheckPlayerMoveTypeMatchups_DecreaseScore);

ok2:


done:
    CALL(aCheckPlayerMoveTypeMatchups_CheckEnemyMoveMatchups);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;


CheckEnemyMoveMatchups:
    LD_DE(wEnemyMonMoves);
    LD_B(NUM_MOVES + 1);
    LD_C(0);

    LD_A_addr(wTypeMatchup);
    PUSH_AF;

loop2:
    DEC_B;
    IF_Z goto exit2;

    LD_A_de;
    AND_A_A;
    IF_Z goto exit2;

    INC_DE;
    DEC_A;
    LD_HL(mMoves + MOVE_POWER);
    CALL(aGetMoveAttr);
    AND_A_A;
    IF_Z goto loop2;

    INC_HL;
    CALL(aGetMoveByte);
    LD_HL(wBattleMonType1);
    CALL(aCheckTypeMatchup);

    LD_A_addr(wTypeMatchup);
// immune
    AND_A_A;
    IF_Z goto loop2;

// not very effective
    INC_C;
    CP_A(EFFECTIVE);
    IF_C goto loop2;

// neutral
    INC_C;
    INC_C;
    INC_C;
    INC_C;
    INC_C;
    CP_A(EFFECTIVE);
    IF_Z goto loop2;

// super effective
    LD_C(100);
    goto loop2;


exit2:
    POP_AF;
    LD_addr_A(wTypeMatchup);

    LD_A_C;
    AND_A_A;
    IF_Z goto doubledown;  // double down
    CP_A(5);
    IF_C goto DecreaseScore;  // down
    CP_A(100);
    RET_C ;
    goto IncreaseScore;  // up


doubledown:
    CALL(aCheckPlayerMoveTypeMatchups_DecreaseScore);

DecreaseScore:
    LD_A_addr(wEnemyAISwitchScore);
    DEC_A;
    LD_addr_A(wEnemyAISwitchScore);
    RET;


IncreaseScore:
    LD_A_addr(wEnemyAISwitchScore);
    INC_A;
    LD_addr_A(wEnemyAISwitchScore);
    RET;

}

static void CheckPlayerMoveTypeMatchups_CheckEnemyMoveMatchups(uint8_t matchup) {
    // LD_DE(wEnemyMonMoves);
    move_t* de = wram->wEnemyMon.moves;
    // LD_B(NUM_MOVES + 1);
    uint8_t b = NUM_MOVES + 1;
    // LD_C(0);
    uint8_t c = 0;

    // LD_A_addr(wTypeMatchup);
    // PUSH_AF;

    while(--b != 0) {
    // loop2:
        // DEC_B;
        // IF_Z goto exit2;

        // LD_A_de;
        move_t a = *de;
        // AND_A_A;
        // IF_Z goto exit2;
        if(a == NO_MOVE)
            break;

        // INC_DE;
        de++;
        // DEC_A;
        // LD_HL(mMoves + MOVE_POWER);
        uint8_t power = Moves[a].power;
        // CALL(aGetMoveAttr);
        // AND_A_A;
        // IF_Z goto loop2;
        if(power == 0)
            continue;

        // INC_HL;
        // CALL(aGetMoveByte);
        // LD_HL(wBattleMonType1);
        // CALL(aCheckTypeMatchup);
        uint8_t matchup2 = CheckTypeMatchup_Conv(Moves[a].type, wram->wBattleMon.types);

        // LD_A_addr(wTypeMatchup);
    // immune
        // AND_A_A;
        // IF_Z goto loop2;
        if(matchup2 == 0)
            continue;

    // not very effective
        // INC_C;
        ++c;
        // CP_A(EFFECTIVE);
        // IF_C goto loop2;
        if(matchup2 < EFFECTIVE)
            continue;

    // neutral
        // INC_C;
        // INC_C;
        // INC_C;
        // INC_C;
        // INC_C;
        c += 5;
        // CP_A(EFFECTIVE);
        // IF_Z goto loop2;
        if(matchup2 == EFFECTIVE)
            continue;

    // super effective
        // LD_C(100);
        // goto loop2;
        c = 100;
    }

// exit2:
    // POP_AF;
    // LD_addr_A(wTypeMatchup);
    wram->wTypeMatchup = matchup;

    // LD_A_C;
    // AND_A_A;
    // IF_Z goto doubledown;  // double down
    if(c == 0) {
        --wram->wEnemyAISwitchScore;
        --wram->wEnemyAISwitchScore;
    }
    // CP_A(5);
    // IF_C goto DecreaseScore;  // down
    else if(c < 5) {
        --wram->wEnemyAISwitchScore;
    }
    // CP_A(100);
    // RET_C ;
    else if(c >= 100) {
        // goto IncreaseScore;  // up
        ++wram->wEnemyAISwitchScore;
    }
    else {
        return;
    }

// doubledown:
    // CALL(aCheckPlayerMoveTypeMatchups_DecreaseScore);

// DecreaseScore:
    // LD_A_addr(wEnemyAISwitchScore);
    // DEC_A;
    // LD_addr_A(wEnemyAISwitchScore);
    // RET;

// IncreaseScore:
    // LD_A_addr(wEnemyAISwitchScore);
    // INC_A;
    // LD_addr_A(wEnemyAISwitchScore);
    // RET;
}

uint8_t CheckPlayerMoveTypeMatchups_Conv(void){
//  Check how well the moves you've already used
//  fare against the enemy's Pokemon.  Used to
//  score a potential switch.
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A(BASE_AI_SWITCH_SCORE);
    // LD_addr_A(wEnemyAISwitchScore);
    wram->wEnemyAISwitchScore = BASE_AI_SWITCH_SCORE;
    uint8_t matchup = EFFECTIVE;
    // LD_HL(wPlayerUsedMoves);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto unknown_moves;
    if(wram->wPlayerUsedMoves[0] == NO_MOVE) {
    // unknown_moves:
        // LD_A_addr(wBattleMonType1);
        // LD_B_A;
        uint8_t type = wram->wBattleMon.type1;
        // LD_HL(wEnemyMonType1);
        // CALL(aCheckTypeMatchup);
        matchup = CheckTypeMatchup_Conv(type, wram->wEnemyMon.types);
        // LD_A_addr(wTypeMatchup);
        // CP_A(EFFECTIVE + 1);  // 1.0 + 0.1
        // IF_C goto ok;
        if(matchup >= EFFECTIVE + 1) {
            // CALL(aCheckPlayerMoveTypeMatchups_DecreaseScore);
            --wram->wEnemyAISwitchScore;
        }
    // ok:
        // LD_A_addr(wBattleMonType2);
        // CP_A_B;
        // IF_Z goto ok2;
        // CALL(aCheckTypeMatchup);
        // LD_A_addr(wTypeMatchup);
        // CP_A(EFFECTIVE + 1);  // 1.0 + 0.1
        // IF_C goto ok2;
        if(wram->wBattleMon.type2 != type
        && (matchup = CheckTypeMatchup_Conv(wram->wBattleMon.type2, wram->wEnemyMon.types), matchup >= EFFECTIVE + 1)) {
            // CALL(aCheckPlayerMoveTypeMatchups_DecreaseScore);
            --wram->wEnemyAISwitchScore;
        }
    // ok2:

    }
    else {
        move_t* hl = wram->wPlayerUsedMoves;
        // LD_D(NUM_MOVES);
        uint8_t d = NUM_MOVES;
        // LD_E(0);
        uint8_t e = 0;

        do {
        // loop:
            // LD_A_hli;
            move_t a = *(hl++);
            // AND_A_A;
            // IF_Z goto exit;
            if(a == NO_MOVE) {
            // exit:
                // LD_A_E;
                // CP_A(2);
                // IF_Z goto done;
                if(e == 2)
                    break;
                // CALL(aCheckPlayerMoveTypeMatchups_IncreaseScore);
                ++wram->wEnemyAISwitchScore;
                // LD_A_E;
                // AND_A_A;
                // IF_NZ goto done;
                if(e != 0)
                    break;
                // CALL(aCheckPlayerMoveTypeMatchups_IncreaseScore);
                ++wram->wEnemyAISwitchScore;
                break;
            }
            // PUSH_HL;
            // DEC_A;
            // LD_HL(mMoves + MOVE_POWER);
            // CALL(aGetMoveAttr);
            uint8_t power = Moves[a].power;
            // AND_A_A;
            // IF_Z goto next;
            if(power == 0)
                continue;

            // INC_HL;
            // CALL(aGetMoveByte);
            uint8_t type = Moves[a].type;
            // LD_HL(wEnemyMonType);
            // CALL(aCheckTypeMatchup);
            matchup = CheckTypeMatchup_Conv(type, wram->wEnemyMon.types);
            // LD_A_addr(wTypeMatchup);
            // CP_A(EFFECTIVE + 1);  // 1.0 + 0.1
            // IF_NC goto super_effective;
            if(matchup >= EFFECTIVE + 1) {
            // super_effective:
                // CALL(aCheckPlayerMoveTypeMatchups_DecreaseScore);
                --wram->wEnemyAISwitchScore;
                // POP_HL;
                break;
            }
            // AND_A_A;
            // IF_Z goto next;
            else if(matchup == 0) 
                continue;
            // CP_A(EFFECTIVE);  // 1.0
            // IF_NC goto neutral;
            else if(matchup >= EFFECTIVE) {
            // neutral:
                // LD_E(2);
                e = 2;
                // goto next;
                continue;
            }

        //  not very effective
            else {
                // LD_A_E;
                // CP_A(1);  // 0.1
                // IF_NC goto next;
                if(e < 1) {
                    // LD_E(1);
                    e = 1;
                }
                // goto next;
                continue;
            }

        // next:
            // POP_HL;
            // DEC_D;
            // IF_NZ goto loop;
        } while(--d != 0);
    }
// done:
    // CALL(aCheckPlayerMoveTypeMatchups_CheckEnemyMoveMatchups);
    CheckPlayerMoveTypeMatchups_CheckEnemyMoveMatchups(matchup);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return wram->wEnemyAISwitchScore;
}

void CheckAbleToSwitch(void){
    XOR_A_A;
    LD_addr_A(wEnemySwitchMonParam);
    CALL(aFindAliveEnemyMons);
    RET_C ;

    LD_A_addr(wEnemySubStatus1);
    BIT_A(SUBSTATUS_PERISH);
    IF_Z goto no_perish;

    LD_A_addr(wEnemyPerishCount);
    CP_A(1);
    IF_NZ goto no_perish;

// Perish count is 1

    CALL(aFindAliveEnemyMons);
    CALL(aFindEnemyMonsWithAtLeastQuarterMaxHP);
    CALL(aFindEnemyMonsThatResistPlayer);
    CALL(aFindAliveEnemyMonsWithASuperEffectiveMove);

    LD_A_E;
    CP_A(2);
    IF_NZ goto not_2;

    LD_A_addr(wEnemyAISwitchScore);
    ADD_A(0x30);  // maximum chance
    LD_addr_A(wEnemySwitchMonParam);
    RET;


not_2:
    CALL(aFindAliveEnemyMons);
    SLA_C;
    SLA_C;
    LD_B(0xff);


loop1:
    INC_B;
    SLA_C;
    IF_NC goto loop1;

    LD_A_B;
    ADD_A(0x30);  // maximum chance
    LD_addr_A(wEnemySwitchMonParam);
    RET;


no_perish:
    CALL(aCheckPlayerMoveTypeMatchups);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(11);
    RET_NC ;

    LD_A_addr(wLastPlayerCounterMove);
    AND_A_A;
    IF_Z goto no_last_counter_move;

    CALL(aFindEnemyMonsImmuneToLastCounterMove);
    LD_A_addr(wEnemyAISwitchScore);
    AND_A_A;
    IF_Z goto no_last_counter_move;

    LD_C_A;
    CALL(aFindEnemyMonsWithASuperEffectiveMove);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(0xff);
    RET_Z ;

    LD_B_A;
    LD_A_E;
    CP_A(2);
    IF_Z goto not_2_again;

    CALL(aCheckPlayerMoveTypeMatchups);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(10);
    RET_NC ;

    LD_A_B;
    ADD_A(0x10);
    LD_addr_A(wEnemySwitchMonParam);
    RET;


not_2_again:
    LD_C(0x10);
    CALL(aCheckPlayerMoveTypeMatchups);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(10);
    IF_NC goto okay;
    LD_C(0x20);


okay:
    LD_A_B;
    ADD_A_C;
    LD_addr_A(wEnemySwitchMonParam);
    RET;


no_last_counter_move:
    CALL(aCheckPlayerMoveTypeMatchups);
    LD_A_addr(wEnemyAISwitchScore);
    CP_A(10);
    RET_NC ;

    CALL(aFindAliveEnemyMons);
    CALL(aFindEnemyMonsWithAtLeastQuarterMaxHP);
    CALL(aFindEnemyMonsThatResistPlayer);
    CALL(aFindAliveEnemyMonsWithASuperEffectiveMove);

    LD_A_E;
    CP_A(0x2);
    RET_NZ ;

    LD_A_addr(wEnemyAISwitchScore);
    ADD_A(0x10);
    LD_addr_A(wEnemySwitchMonParam);
    RET;

}

void FindAliveEnemyMons(void){
    LD_A_addr(wOTPartyCount);
    CP_A(2);
    IF_C goto only_one;

    LD_D_A;
    LD_E(0);
    LD_B(1 << (PARTY_LENGTH - 1));
    LD_C(0);
    LD_HL(wOTPartyMon1HP);


loop:
    LD_A_addr(wCurOTMon);
    CP_A_E;
    IF_Z goto next;

    PUSH_BC;
    LD_B_hl;
    INC_HL;
    LD_A_hld;
    OR_A_B;
    POP_BC;
    IF_Z goto next;

    LD_A_C;
    OR_A_B;
    LD_C_A;


next:
    SRL_B;
    PUSH_BC;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    INC_E;
    DEC_D;
    IF_NZ goto loop;

    LD_A_C;
    AND_A_A;
    IF_NZ goto more_than_one;


only_one:
    SCF;
    RET;


more_than_one:
    AND_A_A;
    RET;

}

// Return carry if enemy only has 1 mon left.
bool FindAliveEnemyMons_Conv(void){
    // LD_A_addr(wOTPartyCount);
    // CP_A(2);
    // IF_C goto only_one;
    if(wram->wOTPartyCount < 2)
        return true;

    // LD_D_A;
    uint8_t d = wram->wOTPartyCount;
    // LD_E(0);
    uint8_t e = 0;
    // LD_B(1 << (PARTY_LENGTH - 1));
    uint8_t b = 1 << (PARTY_LENGTH - 1);
    // LD_C(0);
    uint8_t c = 0;
    // LD_HL(wOTPartyMon1HP);
    struct PartyMon* hl = wram->wOTPartyMon;

    do {
    // loop:
        // LD_A_addr(wCurOTMon);
        // CP_A_E;
        // IF_Z goto next;
        if(wram->wCurOTMon == e)
            continue;

        // PUSH_BC;
        // LD_B_hl;
        // INC_HL;
        // LD_A_hld;
        // OR_A_B;
        // POP_BC;
        // IF_Z goto next;
        if(hl->HP == 0)
            continue;

        // LD_A_C;
        // OR_A_B;
        // LD_C_A;
        c |= b;

    // next:
        // SRL_B;
        // PUSH_BC;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        // POP_BC;
        // INC_E;
        // DEC_D;
        // IF_NZ goto loop;
    } while(b >>= 1, ++hl, ++e, --d != 0);

    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto more_than_one;
    if(c != 0)
        return false;


// only_one:
    // SCF;
    // RET;
    return true;

// more_than_one:
    // AND_A_A;
    // RET;
}

void FindEnemyMonsImmuneToLastCounterMove(void){
    LD_HL(wOTPartyMon1);
    LD_A_addr(wOTPartyCount);
    LD_B_A;
    LD_C(1 << (PARTY_LENGTH - 1));
    LD_D(0);
    XOR_A_A;
    LD_addr_A(wEnemyAISwitchScore);


loop:
    LD_A_addr(wCurOTMon);
    CP_A_D;
    PUSH_HL;
    IF_Z goto next;

    PUSH_HL;
    PUSH_BC;

// If the Pokemon has at least 1 HP...
    LD_BC(MON_HP);
    ADD_HL_BC;
    POP_BC;
    LD_A_hli;
    OR_A_hl;
    POP_HL;
    IF_Z goto next;

    LD_A_hl;
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);

// the player's last move is damaging...
    LD_A_addr(wLastPlayerCounterMove);
    DEC_A;
    LD_HL(mMoves + MOVE_POWER);
    CALL(aGetMoveAttr);
    AND_A_A;
    IF_Z goto next;

// and the Pokemon is immune to it...
    INC_HL;
    CALL(aGetMoveByte);
    LD_HL(wBaseType);
    CALL(aCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    AND_A_A;
    IF_NZ goto next;

// ... encourage that Pokemon.
    LD_A_addr(wEnemyAISwitchScore);
    OR_A_C;
    LD_addr_A(wEnemyAISwitchScore);

next:
    POP_HL;
    DEC_B;
    RET_Z ;

    PUSH_BC;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;

    INC_D;
    SRL_C;
    goto loop;

    return FindAliveEnemyMonsWithASuperEffectiveMove();
}

void FindAliveEnemyMonsWithASuperEffectiveMove(void){
    PUSH_BC;
    LD_A_addr(wOTPartyCount);
    LD_E_A;
    LD_HL(wOTPartyMon1HP);
    LD_B(1 << (PARTY_LENGTH - 1));
    LD_C(0);

loop:
    LD_A_hli;
    OR_A_hl;
    IF_Z goto next;

    LD_A_B;
    OR_A_C;
    LD_C_A;


next:
    SRL_B;
    PUSH_BC;
    LD_BC(wPartyMon2HP - (wPartyMon1HP + 1));
    ADD_HL_BC;
    POP_BC;
    DEC_E;
    IF_NZ goto loop;

    LD_A_C;
    POP_BC;

    AND_A_C;
    LD_C_A;
// fallthrough

    return FindEnemyMonsWithASuperEffectiveMove();
}

void FindEnemyMonsWithASuperEffectiveMove(void){
    LD_A(-1);
    LD_addr_A(wEnemyAISwitchScore);
    LD_HL(wOTPartyMon1Moves);
    LD_B(1 << (PARTY_LENGTH - 1));
    LD_D(0);
    LD_E(0);

loop:
    LD_A_B;
    AND_A_C;
    IF_Z goto next;

    PUSH_HL;
    PUSH_BC;
// for move on mon:
    LD_B(NUM_MOVES);
    LD_C(0);

loop3:
// if move is None: break
    LD_A_hli;
    AND_A_A;
    PUSH_HL;
    IF_Z goto break3;

// if move has no power: continue
    DEC_A;
    LD_HL(mMoves + MOVE_POWER);
    CALL(aGetMoveAttr);
    AND_A_A;
    IF_Z goto nope;

// check type matchups
    INC_HL;
    CALL(aGetMoveByte);
    LD_HL(wBattleMonType1);
    CALL(aCheckTypeMatchup);

// if immune or not very effective: continue
    LD_A_addr(wTypeMatchup);
    CP_A(10);
    IF_C goto nope;

// if neutral: load 1 and continue
    LD_E(1);
    CP_A(EFFECTIVE + 1);
    IF_C goto nope;

// if super-effective: load 2 and break
    LD_E(2);
    goto break3;


nope:
    POP_HL;
    DEC_B;
    IF_NZ goto loop3;

    goto done;


break3:
    POP_HL;

done:
    LD_A_E;
    POP_BC;
    POP_HL;
    CP_A(2);
    IF_Z goto done2;  // at least one move is super-effective
    CP_A(1);
    IF_NZ goto next;  // no move does more than half damage

// encourage this pokemon
    LD_A_D;
    OR_A_B;
    LD_D_A;
    goto next;  // such a long jump


next:
// next pokemon?
    PUSH_BC;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    SRL_B;
    IF_NC goto loop;

// if no pokemon has a super-effective move: return
    LD_A_D;
    LD_B_A;
    AND_A_A;
    RET_Z ;


done2:
// convert the bit flag to an int and return
    PUSH_BC;
    SLA_B;
    SLA_B;
    LD_C(0xff);

loop2:
    INC_C;
    SLA_B;
    IF_NC goto loop2;

    LD_A_C;
    LD_addr_A(wEnemyAISwitchScore);
    POP_BC;
    RET;

}

void FindEnemyMonsThatResistPlayer(void){
    PUSH_BC;
    LD_HL(wOTPartySpecies);
    LD_B(1 << (PARTY_LENGTH - 1));
    LD_C(0);


loop:
    LD_A_hli;
    CP_A(0xff);
    IF_Z goto done;

    PUSH_HL;
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A_addr(wLastPlayerCounterMove);
    AND_A_A;
    IF_Z goto skip_move;

    DEC_A;
    LD_HL(mMoves + MOVE_POWER);
    CALL(aGetMoveAttr);
    AND_A_A;
    IF_Z goto skip_move;

    INC_HL;
    CALL(aGetMoveByte);
    goto check_type;


skip_move:
    LD_A_addr(wBattleMonType1);
    LD_HL(wBaseType);
    CALL(aCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    CP_A(10 + 1);
    IF_NC goto dont_choose_mon;
    LD_A_addr(wBattleMonType2);


check_type:
    LD_HL(wBaseType);
    CALL(aCheckTypeMatchup);
    LD_A_addr(wTypeMatchup);
    CP_A(EFFECTIVE + 1);
    IF_NC goto dont_choose_mon;

    LD_A_B;
    OR_A_C;
    LD_C_A;


dont_choose_mon:
    SRL_B;
    POP_HL;
    goto loop;


done:
    LD_A_C;
    POP_BC;
    AND_A_C;
    LD_C_A;
    RET;

}

void FindEnemyMonsWithAtLeastQuarterMaxHP(void){
    PUSH_BC;
    LD_DE(wOTPartySpecies);
    LD_B(1 << (PARTY_LENGTH - 1));
    LD_C(0);
    LD_HL(wOTPartyMon1HP);


loop:
    LD_A_de;
    INC_DE;
    CP_A(0xff);
    IF_Z goto done;

    PUSH_HL;
    PUSH_BC;
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    INC_HL;
    INC_HL;
//  hl = MaxHP + 1
//  bc = [CurHP] * 4
    SRL_C;
    RL_B;
    SRL_C;
    RL_B;
//  if bc >= [hl], encourage
    LD_A_hld;
    CP_A_C;
    LD_A_hl;
    SBC_A_B;
    POP_BC;
    IF_NC goto next;

    LD_A_B;
    OR_A_C;
    LD_C_A;


next:
    SRL_B;
    POP_HL;
    PUSH_BC;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    goto loop;


done:
    LD_A_C;
    POP_BC;
    AND_A_C;
    LD_C_A;
    RET;

}
