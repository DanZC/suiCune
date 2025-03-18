#include "../../constants.h"
#include "evolve.h"
#include "learn.h"
#include "tempmon.h"
#include "move_mon.h"
#include "../smallflag.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/names.h"
#include "../../home/copy_name.h"
#include "../../home/pokemon.h"
#include "../../home/text.h"
#include "../../home/delay.h"
#include "../../home/clear_sprites.h"
#include "../../home/pokedex_flags.h"
#include "../gfx/load_pics.h"
#include "../pokedex/unown_dex.h"
#include "../movie/evolution_animation.h"
#include "../../mobile/mobile_41.h"
#include "../../data/text/common.h"
#include "../../data/pokemon/evos_attacks_pointers.h"
#include "../../data/moves/moves.h"
#include <stddef.h>

void EvolvePokemon(void){
    // LD_HL(wEvolvableFlags);
    // XOR_A_A;
    // LD_hl_A;
    wram->wEvolvableFlags[0] = 0;
    // LD_A_addr(wCurPartyMon);
    // LD_C_A;
    // LD_B(SET_FLAG);
    // CALL(aEvoFlagAction);
    EvoFlagAction(wram->wEvolvableFlags, wram->wCurPartyMon, SET_FLAG);
    return EvolveAfterBattle();
}

void EvolveAfterBattle(void){
    // XOR_A_A;
    // LD_addr_A(wMonTriedToEvolve);
    wram->wMonTriedToEvolve = 0;
    // DEC_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = 0xff;
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;
    // LD_HL(wPartyCount);

    // PUSH_HL;

    return EvolveAfterBattle_MasterLoop(wram->wPartySpecies - 1);
}

void EvolveAfterBattle_MasterLoop(species_t* species){
MasterLoop:
    // LD_HL(wCurPartyMon);
    // INC_hl;
    wram->wCurPartyMon++;

    // POP_HL;

    // INC_HL;
    species++;
    // LD_A_hl;
    // CP_A(0xff);
    // JP_Z (mEvolveAfterBattle_MasterLoop_ReturnToMap);
    if(*species == (species_t)-1) {
    // ReturnToMap:
        // POP_DE;
        // POP_BC;
        // POP_HL;
        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wLinkMode != LINK_NULL)
            return;
        // LD_A_addr(wBattleMode);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wBattleMode != 0)
            return;
        // LD_A_addr(wMonTriedToEvolve);
        // AND_A_A;
        // CALL_NZ (aRestartMapMusic);
        if(wram->wMonTriedToEvolve)
            RestartMapMusic_Conv();
        // RET;
        return;
    }

    // LD_addr_A(wEvolutionOldSpecies);
    wram->wEvolutionOldSpecies = *species;

    // PUSH_HL;
    // LD_A_addr(wCurPartyMon);
    // LD_C_A;
    // LD_HL(wEvolvableFlags);
    // LD_B(CHECK_FLAG);
    // CALL(aEvoFlagAction);
    // LD_A_C;
    // AND_A_A;
    // JP_Z (mEvolveAfterBattle_MasterLoop);
    if(!EvoFlagAction(wram->wEvolvableFlags, wram->wCurPartyMon, CHECK_FLAG))
        goto MasterLoop;

    // LD_A_addr(wEvolutionOldSpecies);
    // DEC_A;
    // LD_B(0);
    // LD_C_A;
    // LD_HL(mEvosAttacksPointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct EvoData* evos = EvosAttacksPointers[wram->wEvolutionOldSpecies - 1]->evolutions;

    // PUSH_HL;
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // PREDEF(pCopyMonToTempMon);
    CopyMonToTempMon_Conv();
    // POP_HL;

    while(1) {
    loop:
        // LD_A_hli;
        // AND_A_A;
        // JR_Z (mEvolveAfterBattle_MasterLoop);
        if(evos->type == 0)
            goto MasterLoop;

        // LD_B_A;

        // CP_A(EVOLVE_TRADE);
        // IF_Z goto trade;
        if(evos->type == EVOLVE_TRADE) {
        // trade:
            // LD_A_addr(wLinkMode);
            // AND_A_A;
            // JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

            // CALL(aIsMonHoldingEverstone);
            // JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_2);
            if(wram->wLinkMode == LINK_NULL || IsMonHoldingEverstone())
                goto dont_evolve_2;

            // LD_A_hli;
            // LD_B_A;
            item_t trade_item = evos->trade.heldItem;
            // INC_A;
            // IF_Z goto proceed;
            if(trade_item != (item_t)-1) {
                // LD_A_addr(wLinkMode);
                // CP_A(LINK_TIMECAPSULE);
                // JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_3);

                // LD_A_addr(wTempMonItem);
                // CP_A_B;
                // JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
                if(wram->wLinkMode == LINK_TIMECAPSULE || wram->wTempMon.mon.item != trade_item)
                    goto dont_evolve_3;

                // XOR_A_A;
                // LD_addr_A(wTempMonItem);
                wram->wTempMon.mon.item = NO_ITEM; // Consume item
            }
            // goto proceed;
        }

        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_2);
        else if(wram->wLinkMode != LINK_NULL) {
            goto dont_evolve_2;
        }

        // LD_A_B;
        // CP_A(EVOLVE_ITEM);
        // JP_Z (mEvolveAfterBattle_MasterLoop_item);
        else if(evos->type == EVOLVE_ITEM) {
        // item:
            // LD_A_hli;
            // LD_B_A;
            item_t ev_item = evos->item.useItem;
            // LD_A_addr(wCurItem);
            // CP_A_B;
            // JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
            if(wram->wCurItem != ev_item)
                goto dont_evolve_3;

            // LD_A_addr(wForceEvolution);
            // AND_A_A;
            // JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
            // LD_A_addr(wLinkMode);
            // AND_A_A;
            // JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
            if(wram->wForceEvolution == 0 || wram->wLinkMode != LINK_NULL)
                goto dont_evolve_3;
            // goto proceed;
        }

        // LD_A_addr(wForceEvolution);
        // AND_A_A;
        // JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_2);
        else if(wram->wForceEvolution != 0) {
            goto dont_evolve_2;
        }

        // LD_A_B;
        // CP_A(EVOLVE_LEVEL);
        // JP_Z (mEvolveAfterBattle_MasterLoop_level);
        else if(evos->type == EVOLVE_LEVEL) {
        // level:
            // LD_A_hli;
            // LD_B_A;
            uint8_t lvl = evos->lvl.level;
            // LD_A_addr(wTempMonLevel);
            // CP_A_B;
            // JP_C (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
            // CALL(aIsMonHoldingEverstone);
            // JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
            if(wram->wTempMon.mon.level < lvl || IsMonHoldingEverstone())
                goto dont_evolve_3;
        }

        // CP_A(EVOLVE_HAPPINESS);
        // IF_Z goto happiness;
        else if(evos->type == EVOLVE_HAPPINESS) {
        // happiness:
            // LD_A_addr(wTempMonHappiness);
            // CP_A(HAPPINESS_TO_EVOLVE);
            // JP_C (mEvolveAfterBattle_MasterLoop_dont_evolve_2);

            // CALL(aIsMonHoldingEverstone);
            // JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_2);
            if(wram->wTempMon.mon.happiness < HAPPINESS_TO_EVOLVE || IsMonHoldingEverstone())
                goto dont_evolve_2;

            // LD_A_hli;
            // CP_A(TR_ANYTIME);
            // IF_Z goto proceed;
            // CP_A(TR_MORNDAY);
            // IF_Z goto happiness_daylight;
            if(evos->happiness.timeOfDay == TR_MORNDAY) {
            // happiness_daylight:
                // LD_A_addr(wTimeOfDay);
                // CP_A(NITE_F);
                // JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
                // goto proceed;
                if(wram->wTimeOfDay == NITE_F)
                    goto dont_evolve_3;
            }
        //  TR_NITE
            else if(evos->happiness.timeOfDay == TR_NITE) {
                // LD_A_addr(wTimeOfDay);
                // CP_A(NITE_F);
                // JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_3);
                if(wram->wTimeOfDay != NITE_F)
                    goto dont_evolve_3;
                // goto proceed;
            }
            // goto proceed;
        }

    //  EVOLVE_STAT
        else if(evos->type == EVOLVE_STAT) {
            // LD_A_addr(wTempMonLevel);
            // CP_A_hl;
            // JP_C (mEvolveAfterBattle_MasterLoop_dont_evolve_1);

            // CALL(aIsMonHoldingEverstone);
            // JP_Z (mEvolveAfterBattle_MasterLoop_dont_evolve_1);
            if(wram->wTempMon.mon.level < evos->stat.level || IsMonHoldingEverstone())
                goto dont_evolve_1;

            // PUSH_HL;
            // LD_DE(wTempMonAttack);
            uint16_t atk = BigEndianToNative16(wram->wTempMon.attack);
            // LD_HL(wTempMonDefense);
            uint16_t def = BigEndianToNative16(wram->wTempMon.defense);
            // LD_C(2);
            // CALL(aCompareBytes);
            // LD_A(ATK_EQ_DEF);
            // IF_Z goto got_tyrogue_evo;
            // LD_A(ATK_LT_DEF);
            // IF_C goto got_tyrogue_evo;
            // LD_A(ATK_GT_DEF);
            uint8_t state = (atk == def)? ATK_EQ_DEF: (atk < def)? ATK_LT_DEF: ATK_GT_DEF;

        // got_tyrogue_evo:
            // POP_HL;

            // INC_HL;
            // CP_A_hl;
            // JP_NZ (mEvolveAfterBattle_MasterLoop_dont_evolve_2);
            if(evos->stat.atkDefCmp != state)
                goto dont_evolve_2;

            // INC_HL;
            // goto proceed;
        }
        else {
        }

    // proceed:
        // LD_A_addr(wTempMonLevel);
        // LD_addr_A(wCurPartyLevel);
        wram->wCurPartyLevel = wram->wTempMon.mon.level;
        // LD_A(0x1);
        // LD_addr_A(wMonTriedToEvolve);
        wram->wMonTriedToEvolve = 0x1;

        // PUSH_HL;

        // LD_A_hl;
        // LD_addr_A(wEvolutionNewSpecies);
        wram->wEvolutionNewSpecies = evos->species;
        // LD_A_addr(wCurPartyMon);
        // LD_HL(wPartyMonNicknames);
        // CALL(aGetNickname);
        // CALL(aCopyName1);
        CopyName1(GetCurNickname_Conv());
        // LD_HL(mEvolvingText);
        // CALL(aPrintText);
        PrintText_Conv2(EvolvingText);

        // LD_C(50);
        // CALL(aDelayFrames);
        DelayFrames(50);

        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        // hlcoord(0, 0, wTilemap);
        // LD_BC((12 << 8) | 20);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(0, 0, wram->wTilemap), 20, 12);

        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // CALL(aClearSprites);
        ClearSprites();

        // FARCALL(aEvolutionAnimation);
        bool cancel = EvolutionAnimation_Conv();

        // PUSH_AF;
        // CALL(aClearSprites);
        ClearSprites();
        // POP_AF;
        // JP_C (mCancelEvolution);
        if(cancel) {
        // Inlined CancelEvolution to reduce stack smashing. 
            // LD_HL(mStoppedEvolvingText);
            // CALL(aPrintText);
            PrintText_Conv2(StoppedEvolvingText);
            // CALL(aClearTilemap);
            ClearTilemap_Conv2();
            // POP_HL;
            // JP(mEvolveAfterBattle_MasterLoop);
            goto MasterLoop;
        }

        // LD_HL(mCongratulationsYourPokemonText);
        // CALL(aPrintText);
        PrintText_Conv2(CongratulationsYourPokemonText);

        // POP_HL;

        // LD_A_hl;
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = evos->species;
        // LD_addr_A(wTempMonSpecies);
        wram->wTempMon.mon.species = evos->species;
        // LD_addr_A(wEvolutionNewSpecies);
        wram->wEvolutionNewSpecies = evos->species;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        GetPokemonName(evos->species);

        // PUSH_HL;
        // LD_HL(mEvolvedIntoText);
        // CALL(aPrintTextboxText);
        PrintTextboxText_Conv2(EvolvedIntoText);
        // FARCALL(aStubbedTrainerRankings_MonsEvolved);
        StubbedTrainerRankings_MonsEvolved();

        // LD_DE(MUSIC_NONE);
        // CALL(aPlayMusic);
        PlayMusic_Conv(MUSIC_NONE);
        // LD_DE(SFX_CAUGHT_MON);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_CAUGHT_MON);
        // CALL(aWaitSFX);
        WaitSFX_Conv();

        // LD_C(40);
        // CALL(aDelayFrames);
        DelayFrames(40);

        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // CALL(aUpdateSpeciesNameIfNotNicknamed);
        UpdateSpeciesNameIfNotNicknamed();
        // CALL(aGetBaseData);
        GetBaseData_Conv2(wram->wCurSpecies);

#if !defined(_MSC_VER)
        // MSVC doesn't like this
        const uint16_t* statxp = (uint16_t*)((uint8_t*)&wram->wTempMon + offsetof(struct BoxMon, statExp));
        uint16_t* stats = (uint16_t*)((uint8_t*)&wram->wTempMon + offsetof(struct PartyMon, maxHP));
#else
        // GCC doesn't like this
        const uint16_t* statxp = ((const struct BoxMon*)&wram->wTempMon)->statExp;
        uint16_t* stats = &(((struct PartyMon*)&wram->wTempMon)->maxHP);
#endif
        // LD_HL(wTempMonExp + 2);
        // LD_DE(wTempMonMaxHP);
        // LD_B(TRUE);
        // PREDEF(pCalcMonStats);
        CalcMonStats_Conv(stats, statxp, wram->wTempMon.mon.DVs, TRUE);

        // LD_A_addr(wCurPartyMon);
        // LD_HL(wPartyMons);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        struct PartyMon* mon = wram->wPartyMon + wram->wCurPartyMon;
        // LD_E_L;
        // LD_D_H;
        // LD_BC(MON_MAXHP);
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_B_A;
        // LD_C_hl;
        uint16_t maxHP = BigEndianToNative16(mon->maxHP);
        // LD_HL(wTempMonMaxHP + 1);
        // LD_A_hld;
        // SUB_A_C;
        // LD_C_A;
        // LD_A_hl;
        // SBC_A_B;
        // LD_B_A;
        uint16_t bc = BigEndianToNative16(wram->wTempMon.maxHP) - maxHP;
        // LD_HL(wTempMonHP + 1);
        // LD_A_hl;
        // ADD_A_C;
        // LD_hld_A;
        // LD_A_hl;
        // ADC_A_B;
        // LD_hl_A;
        wram->wTempMon.HP = NativeToBigEndian16(BigEndianToNative16(wram->wTempMon.HP) + bc);

        // LD_HL(wTempMonSpecies);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(mon, &wram->wTempMon, sizeof(*mon));

        // LD_A_addr(wCurSpecies);
        // LD_addr_A(wTempSpecies);
        // XOR_A_A;
        // LD_addr_A(wMonType);
        // CALL(aLearnLevelMoves);
        LearnLevelMoves_Conv(mon, mon->mon.level, wram->wCurSpecies);
        // LD_A_addr(wTempSpecies);
        // DEC_A;
        // CALL(aSetSeenAndCaughtMon);
        SetSeenAndCaughtMon_Conv(wram->wCurSpecies - 1);

        // LD_A_addr(wTempSpecies);
        // CP_A(UNOWN);
        // IF_NZ goto skip_unown;

        if(wram->wCurSpecies == UNOWN) {
            // LD_HL(wTempMonDVs);
            // PREDEF(pGetUnownLetter);
            // CALLFAR(aUpdateUnownDex);
            UpdateUnownDex_Conv(GetUnownLetter_Conv(wram->wTempMon.mon.DVs));
        }

    // skip_unown:
        // POP_DE;
        // POP_HL;
        // LD_A_addr(wTempMonSpecies);
        // LD_hl_A;
        *species = wram->wTempMon.mon.species;
        // PUSH_HL;
        // LD_L_E;
        // LD_H_D;
        // JP(mEvolveAfterBattle_MasterLoop);
        goto MasterLoop;

    dont_evolve_1:
        // INC_HL;

    dont_evolve_2:
        // INC_HL;

    dont_evolve_3:
        // INC_HL;
        evos++;
        // JP(mEvolveAfterBattle_MasterLoop_loop);
    }

// UnusedReturnToMap:
//   //  unreferenced
    // POP_HL;
}

void UpdateSpeciesNameIfNotNicknamed(void){
    // LD_A_addr(wCurSpecies);
    // PUSH_AF;
    species_t curSpecies = wram->wCurSpecies;
    // LD_A_addr(wBaseDexNo);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wBaseDexNo);
    // POP_AF;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = curSpecies;
    // LD_HL(wStringBuffer1);
    uint8_t* hl = wram->wStringBuffer1;
    // LD_DE(wStringBuffer2);
    uint8_t* de = wram->wStringBuffer2;

    uint8_t a;
    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        a = *(de++);
        // CP_A_hl;
        // INC_HL;
        // RET_NZ ;
        if(a != *hl)
            return;
        hl++;
        // CP_A(0x50);
        // IF_NZ goto loop;
    } while(a != 0x50);

    // LD_A_addr(wCurPartyMon);
    // LD_BC(MON_NAME_LENGTH);
    // LD_HL(wPartyMonNicknames);
    // CALL(aAddNTimes);
    // PUSH_HL;
    // LD_A_addr(wCurSpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // POP_DE;
    // LD_BC(MON_NAME_LENGTH);
    // JP(mCopyBytes);
    CopyBytes(wram->wPartyMonNickname[wram->wCurPartyMon], GetPokemonName(wram->wCurSpecies), MON_NAME_LENGTH);
}

void CancelEvolution(void){
    LD_HL(mStoppedEvolvingText);
    CALL(aPrintText);
    CALL(aClearTilemap);
    POP_HL;
    JP(mEvolveAfterBattle_MasterLoop);

}

bool IsMonHoldingEverstone(void){
    // PUSH_HL;
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1Item);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_A_hl;
    // CP_A(EVERSTONE);
    // POP_HL;
    // RET;
    return wram->wPartyMon[wram->wCurPartyMon].mon.item == EVERSTONE;
}

const txt_cmd_s CongratulationsYourPokemonText[] = {
    text_far(v_CongratulationsYourPokemonText)
    text_end
};

const txt_cmd_s EvolvedIntoText[] = {
    text_far(v_EvolvedIntoText)
    text_end
};

const txt_cmd_s StoppedEvolvingText[] = {
    text_far(v_StoppedEvolvingText)
    text_end
};

const txt_cmd_s EvolvingText[] = {
    text_far(v_EvolvingText)
    text_end
};

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

void LearnLevelMoves_Conv(struct PartyMon* mon, uint8_t level, species_t species){
    // LD_A_addr(wTempSpecies);
    // LD_addr_A(wCurPartySpecies);
    // DEC_A;
    // LD_B(0);
    // LD_C_A;
    // LD_HL(mEvosAttacksPointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

// skip_evos:
    // LD_A_hli;
    // AND_A_A;
    // IF_NZ goto skip_evos;
    const struct LevelMove* hl = EvosAttacksPointers[species - 1]->learnset;

    while(1) {
    find_move:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto done;
        if(hl->level == 0)
            break;

        // LD_B_A;
        // LD_A_addr(wCurPartyLevel);
        // CP_A_B;
        // LD_A_hli;
        // IF_NZ goto find_move;
        if(hl->level != level) {
            hl++;
            continue;
        }

        // PUSH_HL;
        // LD_D_A;
        move_t to_learn = hl->move;
        // LD_HL(wPartyMon1Moves);
        // LD_A_addr(wCurPartyMon);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        move_t* moves = mon->mon.moves;

        // LD_B(NUM_MOVES);
        uint8_t b = NUM_MOVES;

        do {
        // check_move:
            // LD_A_hli;
            // CP_A_D;
            // IF_Z goto has_move;
            if(*moves == to_learn) {
                hl++;
                goto find_move;
            }
            // DEC_B;
            // IF_NZ goto check_move;
        } while(--b != 0);
        // goto learn;

    // has_move:
        // POP_HL;
        // goto find_move;

    // learn:
        // LD_A_D;
        // LD_addr_A(wPutativeTMHMMove);
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetMoveName);
        // CALL(aCopyName1);
        CopyName1(GetMoveName(to_learn));
        // PREDEF(pLearnMove);
        LearnMove(to_learn);
        // POP_HL;
        hl++;
        // goto find_move;
    }

// done:
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wTempSpecies);
    wram->wTempSpecies = wram->wCurPartySpecies;
    // RET;
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
        printf("Filled move #%d with move %02X\n", c, de[c]);
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

uint8_t EvoFlagAction(uint8_t* hl, uint8_t c, uint8_t b){
    // PUSH_DE;
    // LD_D(0x0);
    // PREDEF(pSmallFarFlagAction);
    // POP_DE;
    // RET;
    return SmallFarFlagAction_Conv(hl, c, b);
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

//  Find the first mon to evolve into wCurPartySpecies.
//  Return the new species if a pre-evolution is found.
//  species otherwise.
species_t GetPreEvolution_Conv(species_t species){
    // LD_C(0);
    species_t c = 0;

    do {
    // loop:
    //   //  For each Pokemon...
        // LD_HL(mEvosAttacksPointers);
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        const struct EvoData* evo = EvosAttacksPointers[c]->evolutions;

        while(evo->type != 0) {
        // loop2:
        //   //  For each evolution...
            // LD_A_hli;
            // AND_A_A;
            // IF_Z goto no_evolve;  // If we jump, this Pokemon does not evolve into wCurPartySpecies.
            // CP_A(EVOLVE_STAT);  // This evolution type has the extra parameter of stat comparison.
            // IF_NZ goto not_tyrogue;
            // INC_HL;


        // not_tyrogue:
            // INC_HL;
            // LD_A_addr(wCurPartySpecies);
            // CP_A_hl;
            // IF_Z goto found_preevo;
            if(evo->species == species) {
            // found_preevo:
                // INC_C;
                // LD_A_C;
                // LD_addr_A(wCurPartySpecies);
                // SCF;
                // RET;
                return c;
            }
            // INC_HL;
            evo++;
            // LD_A_hl;
            // AND_A_A;
            // IF_NZ goto loop2;
        }


    // no_evolve:
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_POKEMON);
        // IF_C goto loop;
    } while(++c < NUM_POKEMON);
    // AND_A_A;
    // RET;
    return species;
}

