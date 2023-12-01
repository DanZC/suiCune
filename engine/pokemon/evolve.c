#include "../../constants.h"
#include "evolve.h"
#include "../../data/pokemon/evos_attacks_pointers.h"
#include "../../data/moves/moves.h"

void EvolvePokemon(void){
    LD_HL(wEvolvableFlags);
    XOR_A_A;
    LD_hl_A;
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(SET_FLAG);
    CALL(aEvoFlagAction);
    return EvolveAfterBattle();
}

void EvolveAfterBattle(void){
    XOR_A_A;
    LD_addr_A(wMonTriedToEvolve);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    PUSH_HL;
    PUSH_BC;
    PUSH_DE;
    LD_HL(wPartyCount);

    PUSH_HL;

    return EvolveAfterBattle_MasterLoop();
}

void EvolveAfterBattle_MasterLoop(void){
    LD_HL(wCurPartyMon);
    INC_hl;

    POP_HL;

    INC_HL;
    LD_A_hl;
    CP_A(0xff);
    JP_Z (mEvolveAfterBattle_MasterLoop_ReturnToMap);

    LD_addr_A(wEvolutionOldSpecies);

    PUSH_HL;
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_HL(wEvolvableFlags);
    LD_B(CHECK_FLAG);
    CALL(aEvoFlagAction);
    LD_A_C;
    AND_A_A;
    JP_Z (mEvolveAfterBattle_MasterLoop);

    LD_A_addr(wEvolutionOldSpecies);
    DEC_A;
    LD_B(0);
    LD_C_A;
    LD_HL(mEvosAttacksPointers);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    PUSH_HL;
    XOR_A_A;
    LD_addr_A(wMonType);
    PREDEF(pCopyMonToTempMon);
    POP_HL;


loop:
    LD_A_hli;
    AND_A_A;
    JR_Z (mEvolveAfterBattle_MasterLoop);

    LD_B_A;

    CP_A(EVOLVE_TRADE);
    IF_Z goto trade;

    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

    LD_A_B;
    CP_A(EVOLVE_ITEM);
    JP_Z (mEvolveAfterBattle_MasterLoop_item);

    LD_A_addr(wForceEvolution);
    AND_A_A;
    JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

    LD_A_B;
    CP_A(EVOLVE_LEVEL);
    JP_Z (mEvolveAfterBattle_MasterLoop_level);

    CP_A(EVOLVE_HAPPINESS);
    IF_Z goto happiness;

//  EVOLVE_STAT
    LD_A_addr(wTempMonLevel);
    CP_A_hl;
    JP_C (mEvolveAfterBattle_MasterLoop_dont_evolve_1);

    CALL(aIsMonHoldingEverstone);
    JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_1);

    PUSH_HL;
    LD_DE(wTempMonAttack);
    LD_HL(wTempMonDefense);
    LD_C(2);
    CALL(aCompareBytes);
    LD_A(ATK_EQ_DEF);
    IF_Z goto got_tyrogue_evo;
    LD_A(ATK_LT_DEF);
    IF_C goto got_tyrogue_evo;
    LD_A(ATK_GT_DEF);

got_tyrogue_evo:
    POP_HL;

    INC_HL;
    CP_A_hl;
    JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

    INC_HL;
    goto proceed;


happiness:
    LD_A_addr(wTempMonHappiness);
    CP_A(HAPPINESS_TO_EVOLVE);
    JP_C (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

    CALL(aIsMonHoldingEverstone);
    JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

    LD_A_hli;
    CP_A(TR_ANYTIME);
    IF_Z goto proceed;
    CP_A(TR_MORNDAY);
    IF_Z goto happiness_daylight;

//  TR_NITE
    LD_A_addr(wTimeOfDay);
    CP_A(NITE_F);
    JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
    goto proceed;


happiness_daylight:
    LD_A_addr(wTimeOfDay);
    CP_A(NITE_F);
    JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
    goto proceed;


trade:
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

    CALL(aIsMonHoldingEverstone);
    JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

    LD_A_hli;
    LD_B_A;
    INC_A;
    IF_Z goto proceed;

    LD_A_addr(wLinkMode);
    CP_A(LINK_TIMECAPSULE);
    JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_3);

    LD_A_addr(wTempMonItem);
    CP_A_B;
    JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_3);

    XOR_A_A;
    LD_addr_A(wTempMonItem);
    goto proceed;


item:
    LD_A_hli;
    LD_B_A;
    LD_A_addr(wCurItem);
    CP_A_B;
    JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_3);

    LD_A_addr(wForceEvolution);
    AND_A_A;
    JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
    goto proceed;


level:
    LD_A_hli;
    LD_B_A;
    LD_A_addr(wTempMonLevel);
    CP_A_B;
    JP_C (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
    CALL(aIsMonHoldingEverstone);
    JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_3);


proceed:
    LD_A_addr(wTempMonLevel);
    LD_addr_A(wCurPartyLevel);
    LD_A(0x1);
    LD_addr_A(wMonTriedToEvolve);

    PUSH_HL;

    LD_A_hl;
    LD_addr_A(wEvolutionNewSpecies);
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    CALL(aGetNickname);
    CALL(aCopyName1);
    LD_HL(mEvolvingText);
    CALL(aPrintText);

    LD_C(50);
    CALL(aDelayFrames);

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    hlcoord(0, 0, wTilemap);
    LD_BC((12 << 8) | 20);
    CALL(aClearBox);

    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aClearSprites);

    FARCALL(aEvolutionAnimation);

    PUSH_AF;
    CALL(aClearSprites);
    POP_AF;
    JP_C (mCancelEvolution);

    LD_HL(mCongratulationsYourPokemonText);
    CALL(aPrintText);

    POP_HL;

    LD_A_hl;
    LD_addr_A(wCurSpecies);
    LD_addr_A(wTempMonSpecies);
    LD_addr_A(wEvolutionNewSpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);

    PUSH_HL;
    LD_HL(mEvolvedIntoText);
    CALL(aPrintTextboxText);
    FARCALL(aStubbedTrainerRankings_MonsEvolved);

    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    LD_DE(SFX_CAUGHT_MON);
    CALL(aPlaySFX);
    CALL(aWaitSFX);

    LD_C(40);
    CALL(aDelayFrames);

    CALL(aClearTilemap);
    CALL(aUpdateSpeciesNameIfNotNicknamed);
    CALL(aGetBaseData);

    LD_HL(wTempMonExp + 2);
    LD_DE(wTempMonMaxHP);
    LD_B(TRUE);
    PREDEF(pCalcMonStats);

    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMons);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    LD_BC(MON_MAXHP);
    ADD_HL_BC;
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    LD_HL(wTempMonMaxHP + 1);
    LD_A_hld;
    SUB_A_C;
    LD_C_A;
    LD_A_hl;
    SBC_A_B;
    LD_B_A;
    LD_HL(wTempMonHP + 1);
    LD_A_hl;
    ADD_A_C;
    LD_hld_A;
    LD_A_hl;
    ADC_A_B;
    LD_hl_A;

    LD_HL(wTempMonSpecies);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);

    LD_A_addr(wCurSpecies);
    LD_addr_A(wTempSpecies);
    XOR_A_A;
    LD_addr_A(wMonType);
    CALL(aLearnLevelMoves);
    LD_A_addr(wTempSpecies);
    DEC_A;
    CALL(aSetSeenAndCaughtMon);

    LD_A_addr(wTempSpecies);
    CP_A(UNOWN);
    IF_NZ goto skip_unown;

    LD_HL(wTempMonDVs);
    PREDEF(pGetUnownLetter);
    CALLFAR(aUpdateUnownDex);


skip_unown:
    POP_DE;
    POP_HL;
    LD_A_addr(wTempMonSpecies);
    LD_hl_A;
    PUSH_HL;
    LD_L_E;
    LD_H_D;
    JP(mEvolveAfterBattle_MasterLoop);


dont_evolve_1:
    INC_HL;

dont_evolve_2:
    INC_HL;

dont_evolve_3:
    INC_HL;
    JP(mEvolveAfterBattle_MasterLoop_loop);


UnusedReturnToMap:
//   //  unreferenced
    POP_HL;

ReturnToMap:
    POP_DE;
    POP_BC;
    POP_HL;
    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wBattleMode);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wMonTriedToEvolve);
    AND_A_A;
    CALL_NZ (aRestartMapMusic);
    RET;

}

void UpdateSpeciesNameIfNotNicknamed(void){
    LD_A_addr(wCurSpecies);
    PUSH_AF;
    LD_A_addr(wBaseDexNo);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    POP_AF;
    LD_addr_A(wCurSpecies);
    LD_HL(wStringBuffer1);
    LD_DE(wStringBuffer2);

loop:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    RET_NZ ;
    CP_A(0x50);
    IF_NZ goto loop;

    LD_A_addr(wCurPartyMon);
    LD_BC(MON_NAME_LENGTH);
    LD_HL(wPartyMonNicknames);
    CALL(aAddNTimes);
    PUSH_HL;
    LD_A_addr(wCurSpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    POP_DE;
    LD_BC(MON_NAME_LENGTH);
    JP(mCopyBytes);

}

void CancelEvolution(void){
    LD_HL(mStoppedEvolvingText);
    CALL(aPrintText);
    CALL(aClearTilemap);
    POP_HL;
    JP(mEvolveAfterBattle_MasterLoop);

}

void IsMonHoldingEverstone(void){
    PUSH_HL;
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hl;
    CP_A(EVERSTONE);
    POP_HL;
    RET;

}

void CongratulationsYourPokemonText(void){
    //text_far ['_CongratulationsYourPokemonText']
    //text_end ['?']

    return EvolvedIntoText();
}

void EvolvedIntoText(void){
    //text_far ['_EvolvedIntoText']
    //text_end ['?']

    return StoppedEvolvingText();
}

void StoppedEvolvingText(void){
    //text_far ['_StoppedEvolvingText']
    //text_end ['?']

    return EvolvingText();
}

void EvolvingText(void){
    //text_far ['_EvolvingText']
    //text_end ['?']

    return LearnLevelMoves();
}

void LearnLevelMoves(void){
    LD_A_addr(wTempSpecies);
    LD_addr_A(wCurPartySpecies);
    DEC_A;
    LD_B(0);
    LD_C_A;
    LD_HL(mEvosAttacksPointers);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;


skip_evos:
    LD_A_hli;
    AND_A_A;
    IF_NZ goto skip_evos;


find_move:
    LD_A_hli;
    AND_A_A;
    IF_Z goto done;

    LD_B_A;
    LD_A_addr(wCurPartyLevel);
    CP_A_B;
    LD_A_hli;
    IF_NZ goto find_move;

    PUSH_HL;
    LD_D_A;
    LD_HL(wPartyMon1Moves);
    LD_A_addr(wCurPartyMon);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);

    LD_B(NUM_MOVES);

check_move:
    LD_A_hli;
    CP_A_D;
    IF_Z goto has_move;
    DEC_B;
    IF_NZ goto check_move;
    goto learn;

has_move:

    POP_HL;
    goto find_move;


learn:
    LD_A_D;
    LD_addr_A(wPutativeTMHMMove);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetMoveName);
    CALL(aCopyName1);
    PREDEF(pLearnMove);
    POP_HL;
    goto find_move;


done:
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wTempSpecies);
    RET;

}

void FillMoves(void){
//  Fill in moves at de for wCurPartySpecies at wCurPartyLevel

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_HL(mEvosAttacksPointers);
    LD_B(0);
    LD_A_addr(wCurPartySpecies);
    DEC_A;
    ADD_A_A;
    RL_B;
    LD_C_A;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

GoToAttacks:
    LD_A_hli;
    AND_A_A;
    IF_NZ goto GoToAttacks;
    goto GetLevel;


NextMove:
    POP_DE;

GetMove:
    INC_HL;

GetLevel:
    LD_A_hli;
    AND_A_A;
    JP_Z (mFillMoves_done);
    LD_B_A;
    LD_A_addr(wCurPartyLevel);
    CP_A_B;
    JP_C (mFillMoves_done);
    LD_A_addr(wSkipMovesBeforeLevelUp);
    AND_A_A;
    IF_Z goto CheckMove;
    LD_A_addr(wPrevPartyLevel);
    CP_A_B;
    IF_NC goto GetMove;


CheckMove:
    PUSH_DE;
    LD_C(NUM_MOVES);

CheckRepeat:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_Z goto NextMove;
    DEC_C;
    IF_NZ goto CheckRepeat;
    POP_DE;
    PUSH_DE;
    LD_C(NUM_MOVES);

CheckSlot:
    LD_A_de;
    AND_A_A;
    IF_Z goto LearnMove;
    INC_DE;
    DEC_C;
    IF_NZ goto CheckSlot;
    POP_DE;
    PUSH_DE;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    CALL(aShiftMoves);
    LD_A_addr(wEvolutionOldSpecies);
    AND_A_A;
    IF_Z goto ShiftedMove;
    PUSH_DE;
    LD_BC(wPartyMon1PP - (wPartyMon1Moves + NUM_MOVES - 1));
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    CALL(aShiftMoves);
    POP_DE;


ShiftedMove:
    POP_HL;


LearnMove:
    LD_A_hl;
    LD_de_A;
    LD_A_addr(wEvolutionOldSpecies);
    AND_A_A;
    IF_Z goto NextMove;
    PUSH_HL;
    LD_A_hl;
    LD_HL(MON_PP - MON_MOVES);
    ADD_HL_DE;
    PUSH_HL;
    DEC_A;
    LD_HL(mMoves + MOVE_PP);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    POP_HL;
    LD_hl_A;
    POP_HL;
    goto NextMove;


done:
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

//  Fill in moves at de for wCurPartySpecies at wCurPartyLevel
void FillMoves_Conv(move_t* de, uint8_t* pp, species_t species, uint8_t level){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_HL(mEvosAttacksPointers);
    // LD_B(0);
    // LD_A_addr(wCurPartySpecies);
    // DEC_A;
    // ADD_A_A;
    // RL_B;
    // LD_C_A;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct EvoMoves* const hl = EvosAttacksPointers[species - 1];

// GoToAttacks:
    // LD_A_hli;
    // AND_A_A;
    // IF_NZ goto GoToAttacks;
    // goto GetLevel;
    const struct LevelMove* moves = hl->learnset;

    for(uint8_t i = 0; moves[i].level != 0xff && level >= moves[i].level; i++) {
    // GetLevel:
        // LD_A_hli;
        // AND_A_A;
        // JP_Z (mFillMoves_done);
        // LD_B_A;
        uint8_t b = moves[i].level;
        // LD_A_addr(wCurPartyLevel);
        // CP_A_B;
        // JP_C (mFillMoves_done);
        // LD_A_addr(wSkipMovesBeforeLevelUp);
        // AND_A_A;
        // IF_Z goto CheckMove;
        if(wram->wSkipMovesBeforeLevelUp) {
            // LD_A_addr(wPrevPartyLevel);
            // CP_A_B;
            // IF_NC goto GetMove;
            if(wram->wPrevPartyLevel >= b)
                continue;
        }
    // CheckMove:
        // PUSH_DE;
        // LD_C(NUM_MOVES);

        for(uint8_t c = 0; c < NUM_MOVES; c++) {
        // CheckRepeat:
            // LD_A_de;
            // INC_DE;
            // CP_A_hl;
            // IF_Z goto NextMove;
            if(de[c] == moves[i].move)
                goto NextMove;
            // DEC_C;
            // IF_NZ goto CheckRepeat;
        }
        // POP_DE;
        // PUSH_DE;
        // LD_C(NUM_MOVES);

        uint8_t c = 0;
        for(; c < NUM_MOVES; ++c) {
        // CheckSlot:
            // LD_A_de;
            // AND_A_A;
            // IF_Z goto LearnMove;
            if(de[c] == NO_MOVE)
                goto LearnMove;
            // INC_DE;
            // DEC_C;
            // IF_NZ goto CheckSlot;
        }
        // POP_DE;
        // PUSH_DE;
        // PUSH_HL;
        // LD_H_D;
        // LD_L_E;
        // CALL(aShiftMoves);
        ShiftMoves_Conv(de);
        c = NUM_MOVES - 1;
        // LD_A_addr(wEvolutionOldSpecies);
        // AND_A_A;
        // IF_Z goto ShiftedMove;
        if(wram->wEvolutionOldSpecies != 0) {
            // PUSH_DE;
            // LD_BC(wPartyMon1PP - (wPartyMon1Moves + NUM_MOVES - 1));
            // ADD_HL_BC;
            // LD_D_H;
            // LD_E_L;
            // CALL(aShiftMoves);
        //  Inlined this because move_t could be uint16_t in the future.
            for(uint8_t n = 0; n < NUM_MOVES - 1; ++n) {
            // loop:
                // INC_DE;
                // LD_A_de;
                // LD_hli_A;
                pp[n] = pp[n + 1];
                // DEC_C;
                // IF_NZ goto loop;
            }
            // POP_DE;
        }

    // ShiftedMove:
        // POP_HL;


    LearnMove:
        // LD_A_hl;
        // LD_de_A;
        de[c] = moves[i].move;
        // LD_A_addr(wEvolutionOldSpecies);
        // AND_A_A;
        // IF_Z goto NextMove;
        if(wram->wEvolutionOldSpecies != 0) {
            // PUSH_HL;
            // LD_A_hl;
            // LD_HL(MON_PP - MON_MOVES);
            // ADD_HL_DE;
            // PUSH_HL;
            // DEC_A;
            // LD_HL(mMoves + MOVE_PP);
            // LD_BC(MOVE_LENGTH);
            // CALL(aAddNTimes);
            // LD_A(BANK(aMoves));
            // CALL(aGetFarByte);
            // POP_HL;
            // LD_hl_A;
            pp[c] = Moves[moves[i].move].pp;
            // POP_HL;
        }
        // goto NextMove;

    NextMove:;
        // POP_DE;

    // GetMove:
        // INC_HL;
    }

// done:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void ShiftMoves(void){
    LD_C(NUM_MOVES - 1);

loop:
    INC_DE;
    LD_A_de;
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void ShiftMoves_Conv(move_t* hl){
    // LD_C(NUM_MOVES - 1);

    for(uint8_t c = 0; c < NUM_MOVES - 1; ++c) {
    // loop:
        // INC_DE;
        // LD_A_de;
        // LD_hli_A;
        hl[c] = hl[c + 1];
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

void EvoFlagAction(void){
    PUSH_DE;
    LD_D(0x0);
    PREDEF(pSmallFarFlagAction);
    POP_DE;
    RET;

}

void GetPreEvolution(void){
//  Find the first mon to evolve into wCurPartySpecies.

//  Return carry and the new species in wCurPartySpecies
//  if a pre-evolution is found.

    LD_C(0);

loop:
//   //  For each Pokemon...
    LD_HL(mEvosAttacksPointers);
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

loop2:
//   //  For each evolution...
    LD_A_hli;
    AND_A_A;
    IF_Z goto no_evolve;  // If we jump, this Pokemon does not evolve into wCurPartySpecies.
    CP_A(EVOLVE_STAT);  // This evolution type has the extra parameter of stat comparison.
    IF_NZ goto not_tyrogue;
    INC_HL;


not_tyrogue:
    INC_HL;
    LD_A_addr(wCurPartySpecies);
    CP_A_hl;
    IF_Z goto found_preevo;
    INC_HL;
    LD_A_hl;
    AND_A_A;
    IF_NZ goto loop2;


no_evolve:
    INC_C;
    LD_A_C;
    CP_A(NUM_POKEMON);
    IF_C goto loop;
    AND_A_A;
    RET;


found_preevo:
    INC_C;
    LD_A_C;
    LD_addr_A(wCurPartySpecies);
    SCF;
    RET;

}
