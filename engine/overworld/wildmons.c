#include "../../constants.h"
#include "wildmons.h"

void LoadWildMonData(void){
    CALL(av_GrassWildmonLookup);
    IF_C goto copy;
    LD_HL(wMornEncounterRate);
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    goto done_copy;


copy:
    INC_HL;
    INC_HL;
    LD_DE(wMornEncounterRate);
    LD_BC(3);
    CALL(aCopyBytes);

done_copy:
    CALL(av_WaterWildmonLookup);
    LD_A(0);
    IF_NC goto no_copy;
    INC_HL;
    INC_HL;
    LD_A_hl;

no_copy:
    LD_addr_A(wWaterEncounterRate);
    RET;

}

void FindNest(void){
//  Parameters:
//  e: 0 = Johto, 1 = Kanto
//  wNamedObjectIndex: species
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    XOR_A_A;
    CALL(aByteFill);
    LD_A_E;
    AND_A_A;
    IF_NZ goto kanto;
    decoord(0, 0, wTilemap);
    LD_HL(mJohtoGrassWildMons);
    CALL(aFindNest_FindGrass);
    LD_HL(mJohtoWaterWildMons);
    CALL(aFindNest_FindWater);
    CALL(aFindNest_RoamMon1);
    CALL(aFindNest_RoamMon2);
    RET;


kanto:
    decoord(0, 0, wTilemap);
    LD_HL(mKantoGrassWildMons);
    CALL(aFindNest_FindGrass);
    LD_HL(mKantoWaterWildMons);
    JP(mFindNest_FindWater);


FindGrass:
    LD_A_hl;
    CP_A(-1);
    RET_Z ;
    PUSH_HL;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_C_A;
    INC_HL;
    INC_HL;
    INC_HL;
    LD_A(NUM_GRASSMON * 3);
    CALL(aFindNest_SearchMapForMon);
    IF_NC goto next_grass;
    LD_de_A;
    INC_DE;


next_grass:
    POP_HL;
    LD_BC(GRASS_WILDDATA_LENGTH);
    ADD_HL_BC;
    goto FindGrass;


FindWater:
    LD_A_hl;
    CP_A(-1);
    RET_Z ;
    PUSH_HL;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_C_A;
    INC_HL;
    LD_A(NUM_WATERMON);
    CALL(aFindNest_SearchMapForMon);
    IF_NC goto next_water;
    LD_de_A;
    INC_DE;


next_water:
    POP_HL;
    LD_BC(WATER_WILDDATA_LENGTH);
    ADD_HL_BC;
    goto FindWater;


SearchMapForMon:
    INC_HL;

ScanMapLoop:
    PUSH_AF;
    LD_A_addr(wNamedObjectIndex);
    CP_A_hl;
    IF_Z goto found;
    INC_HL;
    INC_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto ScanMapLoop;
    AND_A_A;
    RET;


found:
    POP_AF;
    JP(mFindNest_AppendNest);


AppendNest:
    PUSH_DE;
    CALL(aGetWorldMapLocation);
    LD_C_A;
    hlcoord(0, 0, wTilemap);
    LD_DE(SCREEN_WIDTH * SCREEN_HEIGHT);

AppendNestLoop:
    LD_A_hli;
    CP_A_C;
    IF_Z goto found_nest;
    DEC_DE;
    LD_A_E;
    OR_A_D;
    IF_NZ goto AppendNestLoop;
    LD_A_C;
    POP_DE;
    SCF;
    RET;


found_nest:
    POP_DE;
    AND_A_A;
    RET;


RoamMon1:
    LD_A_addr(wRoamMon1Species);
    LD_B_A;
    LD_A_addr(wNamedObjectIndex);
    CP_A_B;
    RET_NZ ;
    LD_A_addr(wRoamMon1MapGroup);
    LD_B_A;
    LD_A_addr(wRoamMon1MapNumber);
    LD_C_A;
    CALL(aFindNest_AppendNest);
    RET_NC ;
    LD_de_A;
    INC_DE;
    RET;


RoamMon2:
    LD_A_addr(wRoamMon2Species);
    LD_B_A;
    LD_A_addr(wNamedObjectIndex);
    CP_A_B;
    RET_NZ ;
    LD_A_addr(wRoamMon2MapGroup);
    LD_B_A;
    LD_A_addr(wRoamMon2MapNumber);
    LD_C_A;
    CALL(aFindNest_AppendNest);
    RET_NC ;
    LD_de_A;
    INC_DE;
    RET;

}

void TryWildEncounter(void){
//  Try to trigger a wild encounter.
    CALL(aTryWildEncounter_EncounterRate);
    IF_NC goto no_battle;
    CALL(aChooseWildEncounter);
    IF_NZ goto no_battle;
    CALL(aCheckRepelEffect);
    IF_NC goto no_battle;
    XOR_A_A;
    RET;


no_battle:
    XOR_A_A;  // BATTLETYPE_NORMAL
    LD_addr_A(wTempWildMonSpecies);
    LD_addr_A(wBattleType);
    LD_A(1);
    AND_A_A;
    RET;


EncounterRate:
    CALL(aGetMapEncounterRate);
    CALL(aApplyMusicEffectOnEncounterRate);
    CALL(aApplyCleanseTagEffectOnEncounterRate);
    CALL(aRandom);
    CP_A_B;
    RET;

}

void GetMapEncounterRate(void){
    LD_HL(wMornEncounterRate);
    CALL(aCheckOnWater);
    LD_A(wWaterEncounterRate - wMornEncounterRate);
    IF_Z goto ok;
    LD_A_addr(wTimeOfDay);

ok:
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_B_hl;
    RET;

}

void ApplyMusicEffectOnEncounterRate(void){
//  Pokemon March and Ruins of Alph signal double encounter rate.
//  Pokemon Lullaby halves encounter rate.
    LD_A_addr(wMapMusic);
    CP_A(MUSIC_POKEMON_MARCH);
    IF_Z goto double_;
    CP_A(MUSIC_RUINS_OF_ALPH_RADIO);
    IF_Z goto double_;
    CP_A(MUSIC_POKEMON_LULLABY);
    RET_NZ ;
    SRL_B;
    RET;


double_:
    SLA_B;
    RET;

}

void ApplyCleanseTagEffectOnEncounterRate(void){
//  Cleanse Tag halves encounter rate.
    LD_HL(wPartyMon1Item);
    LD_DE(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wPartyCount);
    LD_C_A;

loop:
    LD_A_hl;
    CP_A(CLEANSE_TAG);
    IF_Z goto cleansetag;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;


cleansetag:
    SRL_B;
    RET;

}

void ChooseWildEncounter(void){
    CALL(aLoadWildMonDataPointer);
    JP_NC (mChooseWildEncounter_nowildbattle);
    CALL(aCheckEncounterRoamMon);
    JP_C (mChooseWildEncounter_startwildbattle);

    INC_HL;
    INC_HL;
    INC_HL;
    CALL(aCheckOnWater);
    LD_DE(mWaterMonProbTable);
    IF_Z goto watermon;
    INC_HL;
    INC_HL;
    LD_A_addr(wTimeOfDay);
    LD_BC(NUM_GRASSMON * 2);
    CALL(aAddNTimes);
    LD_DE(mGrassMonProbTable);


watermon:
//  hl contains the pointer to the wild mon data, let's save that to the stack
    PUSH_HL;

randomloop:
    CALL(aRandom);
    CP_A(100);
    IF_NC goto randomloop;
    INC_A;  // 1 <= a <= 100
    LD_B_A;
    LD_H_D;
    LD_L_E;
//  This next loop chooses which mon to load up.

prob_bracket_loop:
    LD_A_hli;
    CP_A_B;
    IF_NC goto got_it;
    INC_HL;
    goto prob_bracket_loop;


got_it:
    LD_C_hl;
    LD_B(0);
    POP_HL;
    ADD_HL_BC;  // this selects our mon
    LD_A_hli;
    LD_B_A;
//  If the Pokemon is encountered by surfing, we need to give the levels some variety.
    CALL(aCheckOnWater);
    IF_NZ goto ok;
//  Check if we buff the wild mon, and by how much.
    CALL(aRandom);
    CP_A(35 percent);
    IF_C goto ok;
    INC_B;
    CP_A(65 percent);
    IF_C goto ok;
    INC_B;
    CP_A(85 percent);
    IF_C goto ok;
    INC_B;
    CP_A(95 percent);
    IF_C goto ok;
    INC_B;
//  Store the level

ok:
    LD_A_B;
    LD_addr_A(wCurPartyLevel);
    LD_B_hl;
// ld a, b
    CALL(aValidateTempWildMonSpecies);
    IF_C goto nowildbattle;

    LD_A_B;  // This is in the wrong place.
    CP_A(UNOWN);
    IF_NZ goto done;

    LD_A_addr(wUnlockedUnowns);
    AND_A_A;
    IF_Z goto nowildbattle;


done:
    goto loadwildmon;


nowildbattle:
    LD_A(1);
    AND_A_A;
    RET;


loadwildmon:
    LD_A_B;
    LD_addr_A(wTempWildMonSpecies);


startwildbattle:
    XOR_A_A;
    RET;

// INCLUDE "data/wild/probabilities.asm"

    return CheckRepelEffect();
}

void CheckRepelEffect(void){
//  If there is no active Repel, there's no need to be here.
    LD_A_addr(wRepelEffect);
    AND_A_A;
    IF_Z goto encounter;
//  Get the first Pokemon in your party that isn't fainted.
    LD_HL(wPartyMon1HP);
    LD_BC(PARTYMON_STRUCT_LENGTH - 1);

loop:
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto ok;
    ADD_HL_BC;
    goto loop;


ok:
//  to PartyMonLevel
    for(int rept = 0; rept < 4; rept++){
    DEC_HL;
    }

    LD_A_addr(wCurPartyLevel);
    CP_A_hl;
    IF_NC goto encounter;
    AND_A_A;
    RET;


encounter:
    SCF;
    RET;

}

void LoadWildMonDataPointer(void){
    CALL(aCheckOnWater);
    JR_Z (mv_WaterWildmonLookup);

    return v_GrassWildmonLookup();
}

void v_GrassWildmonLookup(void){
    LD_HL(mSwarmGrassWildMons);
    LD_BC(GRASS_WILDDATA_LENGTH);
    CALL(av_SwarmWildmonCheck);
    RET_C ;
    LD_HL(mJohtoGrassWildMons);
    LD_DE(mKantoGrassWildMons);
    CALL(av_JohtoWildmonCheck);
    LD_BC(GRASS_WILDDATA_LENGTH);
    JR(mv_NormalWildmonOK);

}

void v_WaterWildmonLookup(void){
    LD_HL(mSwarmWaterWildMons);
    LD_BC(WATER_WILDDATA_LENGTH);
    CALL(av_SwarmWildmonCheck);
    RET_C ;
    LD_HL(mJohtoWaterWildMons);
    LD_DE(mKantoWaterWildMons);
    CALL(av_JohtoWildmonCheck);
    LD_BC(WATER_WILDDATA_LENGTH);
    JR(mv_NormalWildmonOK);

}

void v_JohtoWildmonCheck(void){
    CALL(aIsInJohto);
    AND_A_A;
    RET_Z ;
    LD_H_D;
    LD_L_E;
    RET;

}

void v_SwarmWildmonCheck(void){
    CALL(aCopyCurrMapDE);
    PUSH_HL;
    LD_HL(wSwarmFlags);
    BIT_hl(SWARMFLAGS_DUNSPARCE_SWARM_F);
    POP_HL;
    IF_Z goto CheckYanma;
    LD_A_addr(wDunsparceMapGroup);
    CP_A_D;
    IF_NZ goto CheckYanma;
    LD_A_addr(wDunsparceMapNumber);
    CP_A_E;
    IF_NZ goto CheckYanma;
    CALL(aLookUpWildmonsForMapDE);
    JR_NC (mv_NoSwarmWildmon);
    SCF;
    RET;


CheckYanma:
    PUSH_HL;
    LD_HL(wSwarmFlags);
    BIT_hl(SWARMFLAGS_YANMA_SWARM_F);
    POP_HL;
    JR_Z (mv_NoSwarmWildmon);
    LD_A_addr(wYanmaMapGroup);
    CP_A_D;
    JR_NZ (mv_NoSwarmWildmon);
    LD_A_addr(wYanmaMapNumber);
    CP_A_E;
    JR_NZ (mv_NoSwarmWildmon);
    CALL(aLookUpWildmonsForMapDE);
    JR_NC (mv_NoSwarmWildmon);
    SCF;
    RET;

}

void v_NoSwarmWildmon(void){
    AND_A_A;
    RET;

}

void v_NormalWildmonOK(void){
    CALL(aCopyCurrMapDE);
    JR(mLookUpWildmonsForMapDE);

}

void CopyCurrMapDE(void){
    LD_A_addr(wMapGroup);
    LD_D_A;
    LD_A_addr(wMapNumber);
    LD_E_A;
    RET;

}

void LookUpWildmonsForMapDE(void){

loop:
    PUSH_HL;
    LD_A_hl;
    INC_A;
    IF_Z goto nope;
    LD_A_D;
    CP_A_hl;
    IF_NZ goto next;
    INC_HL;
    LD_A_E;
    CP_A_hl;
    IF_Z goto yup;


next:
    POP_HL;
    ADD_HL_BC;
    goto loop;


nope:
    POP_HL;
    AND_A_A;
    RET;


yup:
    POP_HL;
    SCF;
    RET;

}

void InitRoamMons(void){
//  initialize wRoamMon structs

//  species
    LD_A(RAIKOU);
    LD_addr_A(wRoamMon1Species);
    LD_A(ENTEI);
    LD_addr_A(wRoamMon2Species);

//  level
    LD_A(40);
    LD_addr_A(wRoamMon1Level);
    LD_addr_A(wRoamMon2Level);

//  raikou starting map
    LD_A(GROUP_ROUTE_42);
    LD_addr_A(wRoamMon1MapGroup);
    LD_A(MAP_ROUTE_42);
    LD_addr_A(wRoamMon1MapNumber);

//  entei starting map
    LD_A(GROUP_ROUTE_37);
    LD_addr_A(wRoamMon2MapGroup);
    LD_A(MAP_ROUTE_37);
    LD_addr_A(wRoamMon2MapNumber);

//  hp
    XOR_A_A;  // generate new stats
    LD_addr_A(wRoamMon1HP);
    LD_addr_A(wRoamMon2HP);

    RET;

}

void CheckEncounterRoamMon(void){
    PUSH_HL;
//  Don't trigger an encounter if we're on water.
    CALL(aCheckOnWater);
    IF_Z goto DontEncounterRoamMon;
//  Load the current map group and number to de
    CALL(aCopyCurrMapDE);
//  Randomly select a beast.
    CALL(aRandom);
    CP_A(100);  // 25/64 chance
    IF_NC goto DontEncounterRoamMon;
    AND_A(0b00000011);  // Of that, a 3/4 chance.  Running total: 75/256, or around 29.3%.
    IF_Z goto DontEncounterRoamMon;
    DEC_A;  // 1/3 chance that it's Entei, 1/3 chance that it's Raikou
//  Compare its current location with yours
    LD_HL(wRoamMon1MapGroup);
    LD_C_A;
    LD_B(0);
    LD_A(7);  // length of the roam_struct
    CALL(aAddNTimes);
    LD_A_D;
    CP_A_hl;
    IF_NZ goto DontEncounterRoamMon;
    INC_HL;
    LD_A_E;
    CP_A_hl;
    IF_NZ goto DontEncounterRoamMon;
//  We've decided to take on a beast, so stage its information for battle.
    DEC_HL;
    DEC_HL;
    DEC_HL;
    LD_A_hli;
    LD_addr_A(wTempWildMonSpecies);
    LD_A_hl;
    LD_addr_A(wCurPartyLevel);
    LD_A(BATTLETYPE_ROAMING);
    LD_addr_A(wBattleType);

    POP_HL;
    SCF;
    RET;


DontEncounterRoamMon:
    POP_HL;
    AND_A_A;
    RET;

}

void UpdateRoamMons(void){
    LD_A_addr(wRoamMon1MapGroup);
    CP_A(GROUP_N_A);
    IF_Z goto SkipRaikou;
    LD_B_A;
    LD_A_addr(wRoamMon1MapNumber);
    LD_C_A;
    CALL(aUpdateRoamMons_Update);
    LD_A_B;
    LD_addr_A(wRoamMon1MapGroup);
    LD_A_C;
    LD_addr_A(wRoamMon1MapNumber);


SkipRaikou:
    LD_A_addr(wRoamMon2MapGroup);
    CP_A(GROUP_N_A);
    IF_Z goto SkipEntei;
    LD_B_A;
    LD_A_addr(wRoamMon2MapNumber);
    LD_C_A;
    CALL(aUpdateRoamMons_Update);
    LD_A_B;
    LD_addr_A(wRoamMon2MapGroup);
    LD_A_C;
    LD_addr_A(wRoamMon2MapNumber);


SkipEntei:
    LD_A_addr(wRoamMon3MapGroup);
    CP_A(GROUP_N_A);
    IF_Z goto Finished;
    LD_B_A;
    LD_A_addr(wRoamMon3MapNumber);
    LD_C_A;
    CALL(aUpdateRoamMons_Update);
    LD_A_B;
    LD_addr_A(wRoamMon3MapGroup);
    LD_A_C;
    LD_addr_A(wRoamMon3MapNumber);


Finished:
    JP(mv_BackUpMapIndices);


Update:
    LD_HL(mRoamMaps);

loop:
//  Are we at the end of the table?
    LD_A_hl;
    CP_A(-1);
    RET_Z ;
//  Is this the correct entry?
    LD_A_B;
    CP_A_hl;
    IF_NZ goto next;
    INC_HL;
    LD_A_C;
    CP_A_hl;
    IF_Z goto yes;
//  We don't have the correct entry yet, so let's continue.  A 0 terminates each entry.

next:
    LD_A_hli;
    AND_A_A;
    IF_NZ goto next;
    goto loop;

//  We have the correct entry now, so let's choose a random map from it.

yes:
    INC_HL;
    LD_D_H;
    LD_E_L;

update_loop:
    LD_H_D;
    LD_L_E;
//  Choose which map to warp to.
    CALL(aRandom);
    AND_A(0b00011111);  // 1/8n chance it moves to a completely random map, where n is the number of roaming connections from the current map.
    JR_Z (mJumpRoamMon);
    AND_A(0b11);
    CP_A_hl;
    IF_NC goto update_loop;  // invalid index, try again
    INC_HL;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_addr(wRoamMons_LastMapGroup);
    CP_A_hl;
    IF_NZ goto done;
    INC_HL;
    LD_A_addr(wRoamMons_LastMapNumber);
    CP_A_hl;
    IF_Z goto update_loop;
    DEC_HL;


done:
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    RET;

}

void JumpRoamMons(void){
    LD_A_addr(wRoamMon1MapGroup);
    CP_A(GROUP_N_A);
    IF_Z goto SkipRaikou;
    CALL(aJumpRoamMon);
    LD_A_B;
    LD_addr_A(wRoamMon1MapGroup);
    LD_A_C;
    LD_addr_A(wRoamMon1MapNumber);


SkipRaikou:
    LD_A_addr(wRoamMon2MapGroup);
    CP_A(GROUP_N_A);
    IF_Z goto SkipEntei;
    CALL(aJumpRoamMon);
    LD_A_B;
    LD_addr_A(wRoamMon2MapGroup);
    LD_A_C;
    LD_addr_A(wRoamMon2MapNumber);


SkipEntei:
    LD_A_addr(wRoamMon3MapGroup);
    CP_A(GROUP_N_A);
    IF_Z goto Finished;
    CALL(aJumpRoamMon);
    LD_A_B;
    LD_addr_A(wRoamMon3MapGroup);
    LD_A_C;
    LD_addr_A(wRoamMon3MapNumber);


Finished:
    JP(mv_BackUpMapIndices);

}

void JumpRoamMon(void){

loop:
    LD_HL(mRoamMaps);

innerloop1:
// 0-15 are all valid indexes into RoamMaps,
// so this retry loop is unnecessary
// since NUM_ROAMMON_MAPS happens to be 16
    CALL(aRandom);
    maskbits(NUM_ROAMMON_MAPS, 0);
    CP_A(NUM_ROAMMON_MAPS);
    IF_NC goto innerloop1;
    INC_A;
    LD_B_A;

innerloop2:
//   //  Loop to get hl to the address of the chosen roam map.
    DEC_B;
    IF_Z goto ok;

innerloop3:
//   //  Loop to skip the current roam map, which is terminated by a 0.
    LD_A_hli;
    AND_A_A;
    IF_NZ goto innerloop3;
    goto innerloop2;
//  Check to see if the selected map is the one the player is currently in.  If so, try again.

ok:
    LD_A_addr(wMapGroup);
    CP_A_hl;
    IF_NZ goto done;
    INC_HL;
    LD_A_addr(wMapNumber);
    CP_A_hl;
    IF_Z goto loop;
    DEC_HL;
//  Return the map group and number in bc.

done:
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    RET;

}

void v_BackUpMapIndices(void){
    LD_A_addr(wRoamMons_CurMapNumber);
    LD_addr_A(wRoamMons_LastMapNumber);
    LD_A_addr(wRoamMons_CurMapGroup);
    LD_addr_A(wRoamMons_LastMapGroup);
    LD_A_addr(wMapNumber);
    LD_addr_A(wRoamMons_CurMapNumber);
    LD_A_addr(wMapGroup);
    LD_addr_A(wRoamMons_CurMapGroup);
    RET;

// INCLUDE "data/wild/roammon_maps.asm"

    return ValidateTempWildMonSpecies();
}

void ValidateTempWildMonSpecies(void){
//  Due to a development oversight, this function is called with the wild Pokemon's level, not its species, in a.
    AND_A_A;
    IF_Z goto nowildmon;  // = 0
    CP_A(NUM_POKEMON + 1);  // 252
    IF_NC goto nowildmon;  // >= 252
    AND_A_A;  // 1 <= Species <= 251
    RET;


nowildmon:
    SCF;
    RET;

//  Finds a rare wild Pokemon in the route of the trainer calling, then checks if it's been Seen already.
//  The trainer will then tell you about the Pokemon if you haven't seen it.
    return RandomUnseenWildMon();
}

void RandomUnseenWildMon(void){
    FARCALL(aGetCallerLocation);
    LD_D_B;
    LD_E_C;
    LD_HL(mJohtoGrassWildMons);
    LD_BC(GRASS_WILDDATA_LENGTH);
    CALL(aLookUpWildmonsForMapDE);
    IF_C goto GetGrassmon;
    LD_HL(mKantoGrassWildMons);
    CALL(aLookUpWildmonsForMapDE);
    IF_NC goto done;


GetGrassmon:
    PUSH_HL;
    LD_BC(5 + 4 * 2);  // Location of the level of the 5th wild Pokemon in that map
    ADD_HL_BC;
    LD_A_addr(wTimeOfDay);
    LD_BC(NUM_GRASSMON * 2);
    CALL(aAddNTimes);

randloop1:
    CALL(aRandom);
    AND_A(0b11);
    IF_Z goto randloop1;
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
//  We now have the pointer to one of the last (rarest) three wild Pokemon found in that area.
    INC_HL;
    LD_C_hl;  // Contains the species index of this rare Pokemon
    POP_HL;
    LD_DE(5 + 0 * 2);
    ADD_HL_DE;
    INC_HL;  // Species index of the most common Pokemon on that route
    LD_B(4);

loop2:
    LD_A_hli;
    CP_A_C;  // Compare this most common Pokemon with the rare one stored in c.
    IF_Z goto done;
    INC_HL;
    DEC_B;
    IF_NZ goto loop2;
//  This Pokemon truly is rare.
    PUSH_BC;
    DEC_C;
    LD_A_C;
    CALL(aCheckSeenMon);
    POP_BC;
    IF_NZ goto done;
//  Since we haven't seen it, have the caller tell us about it.
    LD_DE(wStringBuffer1);
    CALL(aCopyName1);
    LD_A_C;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(mRandomUnseenWildMon_JustSawSomeRareMonText);
    CALL(aPrintText);
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;


done:
    LD_A(0x1);
    LD_addr_A(wScriptVar);
    RET;


JustSawSomeRareMonText:
    //text_far ['_JustSawSomeRareMonText']
    //text_end ['?']

    return RandomPhoneWildMon();
}

void RandomPhoneWildMon(void){
    FARCALL(aGetCallerLocation);
    LD_D_B;
    LD_E_C;
    LD_HL(mJohtoGrassWildMons);
    LD_BC(GRASS_WILDDATA_LENGTH);
    CALL(aLookUpWildmonsForMapDE);
    IF_C goto ok;
    LD_HL(mKantoGrassWildMons);
    CALL(aLookUpWildmonsForMapDE);


ok:
    LD_BC(5 + 0 * 2);
    ADD_HL_BC;
    LD_A_addr(wTimeOfDay);
    INC_A;
    LD_BC(NUM_GRASSMON * 2);

loop:
    DEC_A;
    IF_Z goto done;
    ADD_HL_BC;
    goto loop;


done:
    CALL(aRandom);
    AND_A(0b11);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    INC_HL;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wStringBuffer4);
    LD_BC(MON_NAME_LENGTH);
    JP(mCopyBytes);

}

void RandomPhoneMon(void){
//  Get a random monster owned by the trainer who's calling.
    FARCALL(aGetCallerLocation);
    LD_HL(mTrainerGroups);
    LD_A_D;
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A(BANK(aTrainerGroups));
    CALL(aGetFarWord);


skip_trainer:
    DEC_E;
    IF_Z goto skipped;

skip:
    LD_A(BANK(aTrainers));
    CALL(aGetFarByte);
    INC_HL;
    CP_A(-1);
    IF_NZ goto skip;
    goto skip_trainer;

skipped:


skip_name:
    LD_A(BANK(aTrainers));
    CALL(aGetFarByte);
    INC_HL;
    CP_A(0x50);
    IF_NZ goto skip_name;

    LD_A(BANK(aTrainers));
    CALL(aGetFarByte);
    INC_HL;
    LD_BC(2);  // level, species
    CP_A(TRAINERTYPE_NORMAL);
    IF_Z goto got_mon_length;
    LD_BC(2 + NUM_MOVES);  // level, species, moves
    CP_A(TRAINERTYPE_MOVES);
    IF_Z goto got_mon_length;
    LD_BC(2 + 1);  // level, species, item
    CP_A(TRAINERTYPE_ITEM);
    IF_Z goto got_mon_length;
// TRAINERTYPE_ITEM_MOVES
    LD_BC(2 + 1 + NUM_MOVES);  // level, species, item, moves

got_mon_length:

    LD_E(0);
    PUSH_HL;

count_mon:
    INC_E;
    ADD_HL_BC;
    LD_A(BANK(aTrainers));
    CALL(aGetFarByte);
    CP_A(-1);
    IF_NZ goto count_mon;
    POP_HL;


rand:
    CALL(aRandom);
    maskbits(PARTY_LENGTH, 0);
    CP_A_E;
    IF_NC goto rand;

    INC_A;

get_mon:
    DEC_A;
    IF_Z goto got_mon;
    ADD_HL_BC;
    goto get_mon;

got_mon:

    INC_HL;  // species
    LD_A(BANK(aTrainers));
    CALL(aGetFarByte);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wStringBuffer4);
    LD_BC(MON_NAME_LENGTH);
    JP(mCopyBytes);

// INCLUDE "data/wild/johto_grass.asm"
// INCLUDE "data/wild/johto_water.asm"
// INCLUDE "data/wild/kanto_grass.asm"
// INCLUDE "data/wild/kanto_water.asm"
// INCLUDE "data/wild/swarm_grass.asm"
// INCLUDE "data/wild/swarm_water.asm"

}
