#include "../../constants.h"
#include "wildmons.h"
#include "../phone/phone.h"
#include "../../home/map_objects.h"
#include "../../home/random.h"
#include "../../home/region.h"
#include "../../home/copy.h"
#include "../../home/copy_name.h"
#include "../../home/pokedex_flags.h"
#include "../../home/names.h"
#include "../../home/map.h"
#include "../../home/text.h"
#include "../../data/wild/johto_grass.h"
#include "../../data/wild/kanto_grass.h"
#include "../../data/wild/johto_water.h"
#include "../../data/wild/kanto_water.h"
#include "../../data/wild/swarm_grass.h"
#include "../../data/wild/probabilities.h"
#include "../../data/trainers/parties.h"
#include "../../data/wild/roammon_maps.h"
#include "../../data/text/common.h"

void LoadWildMonData(void){
    // CALL(av_GrassWildmonLookup);
    const struct WildMons gmons = v_GrassWildmonLookup_Conv();
    // IF_C goto copy;
    if(gmons.grassMons == NULL) {
        // LD_HL(wMornEncounterRate);
        // XOR_A_A;
        // LD_hli_A;
        wram->wMornEncounterRate = 0;
        // LD_hli_A;
        wram->wDayEncounterRate = 0;
        // LD_hl_A;
        wram->wNiteEncounterRate = 0;
        // goto done_copy;
    }
    else {
    // copy:
        const struct WildGrassMons* const grass = gmons.grassMons;
        // INC_HL;
        // INC_HL;
        // LD_DE(wMornEncounterRate);
        wram->wMornEncounterRate = grass->encounterRates[MORN_F];
        wram->wDayEncounterRate = grass->encounterRates[DAY_F];
        wram->wNiteEncounterRate = grass->encounterRates[NITE_F];
        // LD_BC(3);
        // CALL(aCopyBytes);
    }

// done_copy:
    // CALL(av_WaterWildmonLookup);
    const struct WildMons wmons = v_WaterWildmonLookup_Conv();
    // LD_A(0);
    // IF_NC goto no_copy;
    if(wmons.waterMons == NULL) {
        wram->wWaterEncounterRate = 0;
    }
    else {
        // INC_HL;
        // INC_HL;
        // LD_A_hl;
        wram->wWaterEncounterRate = wmons.waterMons->encounterRate;
    }
// no_copy:
    // LD_addr_A(wWaterEncounterRate);
    // RET;
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

static u8_flag_s FindNest_AppendNest(uint8_t group, uint8_t map) {
    // PUSH_DE;
    // CALL(aGetWorldMapLocation);
    // LD_C_A;
    uint8_t c = GetWorldMapLocation_Conv2(group, map);
    // hlcoord(0, 0, wTilemap);
    tile_t* hl2 = coord(0, 0, wram->wTilemap);
    // LD_DE(SCREEN_WIDTH * SCREEN_HEIGHT);
    uint16_t de = SCREEN_WIDTH * SCREEN_HEIGHT;

    do {
    // AppendNestLoop:
        // LD_A_hli;
        tile_t a = *(hl2++);
        // CP_A_C;
        // IF_Z goto found_nest;
        if(a == c) {
        // found_nest:
            // POP_DE;
            // AND_A_A;
            // RET;
            return u8_flag(c, false);
        }
        // DEC_DE;
        // LD_A_E;
        // OR_A_D;
        // IF_NZ goto AppendNestLoop;
    } while(--de != 0);
    // LD_A_C;
    // POP_DE;
    // SCF;
    // RET;
    return u8_flag(c, true);
}

static u8_flag_s FindNest_SearchMapForGrassMon(const struct WildGrassMons* hl, species_t species) {
    // INC_HL;

    for(uint8_t i = 0; i < 3 * NUM_GRASSMON; ++i) {
    // ScanMapLoop:
        // PUSH_AF;
        // LD_A_addr(wNamedObjectIndex);
        // CP_A_hl;
        // IF_Z goto found;
        if(species == hl->mons[i >> 3][i & 7].species) {
        // found:
            // POP_AF;
            // JP(mFindNest_AppendNest);
            return FindNest_AppendNest(hl->mapGroup, hl->mapNumber);
        }
        // INC_HL;
        // INC_HL;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto ScanMapLoop;
    }
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

static u8_flag_s FindNest_SearchMapForWaterMon(const struct WildWaterMons* hl, species_t species) {
    // INC_HL;

    for(uint8_t i = 0; i < NUM_WATERMON; ++i) {
    // ScanMapLoop:
        // PUSH_AF;
        // LD_A_addr(wNamedObjectIndex);
        // CP_A_hl;
        // IF_Z goto found;
        if(species == hl->mons[i].species) {
        // found:
            // POP_AF;
            // JP(mFindNest_AppendNest);
            return FindNest_AppendNest(hl->mapGroup, hl->mapNumber);
        }
        // INC_HL;
        // INC_HL;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto ScanMapLoop;
    }
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

static tile_t* FindNest_FindGrass(tile_t* de, const struct WildGrassMons* hl, species_t species){
    while(hl->mapGroup != (uint8_t)GROUP_N_A) {
        // LD_A_hl;
        // CP_A(-1);
        // RET_Z ;
        // PUSH_HL;
        // LD_A_hli;
        // LD_B_A;
        // LD_A_hli;
        // LD_C_A;
        // INC_HL;
        // INC_HL;
        // INC_HL;
        // LD_A(NUM_GRASSMON * 3);
        // CALL(aFindNest_SearchMapForMon);
        u8_flag_s res = FindNest_SearchMapForGrassMon(hl, species);
        // IF_NC goto next_grass;
        if(res.flag) {
            // LD_de_A;
            // INC_DE;
            *(de++) = res.a;
        }

    // next_grass:
        // POP_HL;
        // LD_BC(GRASS_WILDDATA_LENGTH);
        // ADD_HL_BC;
        hl++;
        // goto FindGrass;
    }
    return de;
}

static tile_t* FindNest_FindWater(tile_t* de, const struct WildWaterMons* hl, species_t species) {
    while(hl->mapGroup != (uint8_t)GROUP_N_A) {
        // LD_A_hl;
        // CP_A(-1);
        // RET_Z ;
        // PUSH_HL;
        // LD_A_hli;
        // LD_B_A;
        // LD_A_hli;
        // LD_C_A;
        // INC_HL;
        // LD_A(NUM_WATERMON);
        // CALL(aFindNest_SearchMapForMon);
        u8_flag_s res = FindNest_SearchMapForWaterMon(hl, species);
        // IF_NC goto next_water;
        if(res.flag) {
            // LD_de_A;
            // INC_DE;
            *(de++) = res.a;
        }

    // next_water:
        // POP_HL;
        // LD_BC(WATER_WILDDATA_LENGTH);
        // ADD_HL_BC;
        hl++;
        // goto FindWater;
    }
    return de;
}

static tile_t* FindNest_RoamMon1(tile_t* de, species_t species) {
    // LD_A_addr(wRoamMon1Species);
    // LD_B_A;
    // LD_A_addr(wNamedObjectIndex);
    // CP_A_B;
    // RET_NZ ;
    if(wram->wRoamMon1.species != species)
        return de;
    // LD_A_addr(wRoamMon1MapGroup);
    // LD_B_A;
    // LD_A_addr(wRoamMon1MapNumber);
    // LD_C_A;
    // CALL(aFindNest_AppendNest);
    u8_flag_s res = FindNest_AppendNest(wram->wRoamMon1.mapId.mapGroup, wram->wRoamMon1.mapId.mapNumber);
    // RET_NC ;
    if(res.flag) {
        // LD_de_A;
        // INC_DE;
        *(de++) = res.a;
    }
    // RET;
    return de;
}

static tile_t* FindNest_RoamMon2(tile_t* de, species_t species) {
    // LD_A_addr(wRoamMon2Species);
    // LD_B_A;
    // LD_A_addr(wNamedObjectIndex);
    // CP_A_B;
    // RET_NZ ;
    if(wram->wRoamMon2.species != species)
        return de;
    // LD_A_addr(wRoamMon2MapGroup);
    // LD_B_A;
    // LD_A_addr(wRoamMon2MapNumber);
    // LD_C_A;
    // CALL(aFindNest_AppendNest);
    u8_flag_s res = FindNest_AppendNest(wram->wRoamMon2.mapId.mapGroup, wram->wRoamMon2.mapId.mapNumber);
    // RET_NC ;
    if(res.flag) {
        // LD_de_A;
        // INC_DE;
        *(de++) = res.a;
    }
    // RET;
    return de;
}

//  Parameters:
//  e: 0 = Johto, 1 = Kanto
//  wNamedObjectIndex: species
void FindNest_Conv(uint8_t e, species_t species){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x0);
    // LD_A_E;
    // AND_A_A;
    // IF_NZ goto kanto;
    if(e == JOHTO_REGION) {
        // decoord(0, 0, wTilemap);
        tile_t* de = coord(0, 0, wram->wTilemap);
        // LD_HL(mJohtoGrassWildMons);
        // CALL(aFindNest_FindGrass);
        de = FindNest_FindGrass(de, JohtoGrassWildMons, species);
        // LD_HL(mJohtoWaterWildMons);
        // CALL(aFindNest_FindWater);
        de = FindNest_FindWater(de, JohtoWaterWildMons, species);
        // CALL(aFindNest_RoamMon1);
        de = FindNest_RoamMon1(de, species);
        // CALL(aFindNest_RoamMon2);
        de = FindNest_RoamMon2(de, species);
        // RET;
        return;
    }
    else {
    // kanto:
        // decoord(0, 0, wTilemap);
        tile_t* de = coord(0, 0, wram->wTilemap);
        // LD_HL(mKantoGrassWildMons);
        // CALL(aFindNest_FindGrass);
        de = FindNest_FindGrass(de, KantoGrassWildMons, species);
        // LD_HL(mKantoWaterWildMons);
        // JP(mFindNest_FindWater);
        FindNest_FindWater(de, KantoWaterWildMons, species);
        return;
    }
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

uint8_t GetMapEncounterRate_Conv(void){
    // LD_HL(wMornEncounterRate);
    uint8_t* hl = &wram->wMornEncounterRate;
    // CALL(aCheckOnWater);
    // LD_A(wWaterEncounterRate - wMornEncounterRate);
    uint8_t a = wWaterEncounterRate - wMornEncounterRate;
    // IF_Z goto ok;
    if(!CheckOnWater_Conv()) {
        // LD_A_addr(wTimeOfDay);
        a = wram->wTimeOfDay;
    }
// ok:
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_B_hl;
    // RET;
    return hl[a];
}

static bool TryWildEncounter_EncounterRate(void) {
    // CALL(aGetMapEncounterRate);
    uint8_t b = GetMapEncounterRate_Conv();
    // CALL(aApplyMusicEffectOnEncounterRate);
    b = ApplyMusicEffectOnEncounterRate_Conv(b);
    // CALL(aApplyCleanseTagEffectOnEncounterRate);
    b = ApplyCleanseTagEffectOnEncounterRate_Conv(b);
    // CALL(aRandom);
    uint8_t a = Random_Conv();
    // CP_A_B;
    return a < b;
    // RET;
}

//  Try to trigger a wild encounter.
bool TryWildEncounter_Conv(void){
    // CALL(aTryWildEncounter_EncounterRate);
    // IF_NC goto no_battle;
    if(TryWildEncounter_EncounterRate() && ChooseWildEncounter_Conv() && !CheckRepelEffect_Conv() && !bit_test(hram->hJoyDown, B_BUTTON_F))
        return true;
    // CALL(aChooseWildEncounter);
    // IF_NZ goto no_battle;
    // CALL(aCheckRepelEffect);
    // IF_NC goto no_battle;
    // XOR_A_A;
    // RET;

// no_battle:
    // XOR_A_A;  // BATTLETYPE_NORMAL
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = 0;
    // LD_addr_A(wBattleType);
    wram->wBattleType = BATTLETYPE_NORMAL;
    // LD_A(1);
    // AND_A_A;
    // RET;
    return false;
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

//  Pokemon March and Ruins of Alph signal double encounter rate.
//  Pokemon Lullaby halves encounter rate.
uint8_t ApplyMusicEffectOnEncounterRate_Conv(uint8_t b){
    // LD_A_addr(wMapMusic);
    uint8_t mus = wram->wMapMusic;
    // CP_A(MUSIC_POKEMON_MARCH);
    // IF_Z goto double_;
    // CP_A(MUSIC_RUINS_OF_ALPH_RADIO);
    // IF_Z goto double_;
    if(mus == MUSIC_POKEMON_MARCH || mus == MUSIC_RUINS_OF_ALPH_RADIO)
        return b << 1;
    // CP_A(MUSIC_POKEMON_LULLABY);
    // RET_NZ ;
    // SRL_B;
    if(mus == MUSIC_POKEMON_LULLABY)
        return b >> 1;
    // RET;
    return b;

// double_:
    // SLA_B;
    // RET;
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

//  Cleanse Tag halves encounter rate.
uint8_t ApplyCleanseTagEffectOnEncounterRate_Conv(uint8_t b){
    // LD_HL(wPartyMon1Item);
    struct PartyMon* hl = wram->wPartyMon;
    // LD_DE(PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wPartyCount);
    // LD_C_A;

    for(uint8_t c = 0; c < wram->wPartyCount; ++c) {
    // loop:
        // LD_A_hl;
        // CP_A(CLEANSE_TAG);
        // IF_Z goto cleansetag;
        if(hl[c].mon.item == CLEANSE_TAG)
            return b >> 1;
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
    return b;

// cleansetag:
    // SRL_B;
    // RET;
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

bool ChooseWildEncounter_Conv(void){
    // CALL(aLoadWildMonDataPointer);
    // JP_NC (mChooseWildEncounter_nowildbattle);
    const struct WildMons hl = LoadWildMonDataPointer_Conv();
    if(hl.grassMons == NULL)
        return false;
    // CALL(aCheckEncounterRoamMon);
    // JP_C (mChooseWildEncounter_startwildbattle);

    // INC_HL;
    // INC_HL;
    // INC_HL;
    // CALL(aCheckOnWater);
    // LD_DE(mWaterMonProbTable);
    // IF_Z goto watermon;
    // INC_HL;
    // INC_HL;
    // LD_A_addr(wTimeOfDay);
    // LD_BC(NUM_GRASSMON * 2);
    // CALL(aAddNTimes);
    // LD_DE(mGrassMonProbTable);
    const uint8_t* de = (CheckOnWater_Conv())? WaterMonProbTable: GrassMonProbTable;

// watermon:
//  hl contains the pointer to the wild mon data, let's save that to the stack
    // PUSH_HL;

    uint8_t a;
    do {
    // randomloop:
        // CALL(aRandom);
        a = Random_Conv();
        // CP_A(100);
        // IF_NC goto randomloop;
    } while(a >= 100);
    // INC_A;  // 1 <= a <= 100
    ++a;
    // LD_B_A;
    // LD_H_D;
    // LD_L_E;
//  This next loop chooses which mon to load up.

    uint8_t i;
    for(i = 0; de[i] <= a; ++i) {
    // prob_bracket_loop:
        // LD_A_hli;
        // CP_A_B;
        // IF_NC goto got_it;
        // INC_HL;
        // goto prob_bracket_loop;
    }

// got_it:
    // LD_C_hl;
    // LD_B(0);
    // POP_HL;
    // ADD_HL_BC;  // this selects our mon
    // LD_A_hli;
    // LD_B_A;
    uint8_t level = (hl.type == 1)? hl.waterMons->mons[i].level: hl.grassMons->mons[wram->wTimeOfDay][i].level;
//  If the Pokemon is encountered by surfing, we need to give the levels some variety.
    // CALL(aCheckOnWater);
    // IF_NZ goto ok;
    if(CheckOnWater_Conv()) {
    //  Check if we buff the wild mon, and by how much.
        // CALL(aRandom);
        uint8_t r = Random_Conv();
        // CP_A(35 percent);
        // IF_C goto ok;
        if(r >= 35 percent) {
            // INC_B;
            ++level;
            // CP_A(65 percent);
            // IF_C goto ok;
            if(r >= 65 percent) {
                // INC_B;
                ++level;
                // CP_A(85 percent);
                // IF_C goto ok;
                if(r >= 85 percent) {
                    // INC_B;
                    ++level;
                    // CP_A(95 percent);
                    // IF_C goto ok;
                    if(r >= 95 percent)
                        ++level;
                    // INC_B;
                }
            }
        }
    }
//  Store the level

// ok:
    // LD_A_B;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = level;
    // LD_B_hl;
    species_t s = (hl.type == 1)? hl.waterMons->mons[i].species: hl.grassMons->mons[wram->wTimeOfDay][i].species;
// ld a, b
    // CALL(aValidateTempWildMonSpecies);
    // IF_C goto nowildbattle;
    if(!ValidateTempWildMonSpecies_Conv(s))
        return false;

    // LD_A_B;  // This is in the wrong place.
    // CP_A(UNOWN);
    // IF_NZ goto done;

    // LD_A_addr(wUnlockedUnowns);
    // AND_A_A;
    // IF_Z goto nowildbattle;
    if(s == UNOWN && wram->wUnlockedUnowns == FALSE)
        return false;

// done:
    // goto loadwildmon;

// nowildbattle:
    // LD_A(1);
    // AND_A_A;
    // RET;

// loadwildmon:
    // LD_A_B;
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = s;


// startwildbattle:
    // XOR_A_A;
    // RET;
    return true;

// INCLUDE "data/wild/probabilities.asm"

    // return CheckRepelEffect();
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

bool CheckRepelEffect_Conv(void){
//  If there is no active Repel, there's no need to be here.
    // LD_A_addr(wRepelEffect);
    // AND_A_A;
    // IF_Z goto encounter;
    if(wram->wRepelEffect == 0)
        return false;
//  Get the first Pokemon in your party that isn't fainted.
    // LD_HL(wPartyMon1HP);
    // LD_BC(PARTYMON_STRUCT_LENGTH - 1);
    uint8_t i;
    for(i = 0; i < PARTYMON_STRUCT_LENGTH - 1; ++i) {
    // loop:
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto ok;
        if(wram->wPartyMon[i].HP != 0)
            break;
        // ADD_HL_BC;
        // goto loop;
    }


// ok:
//  to PartyMonLevel
    // for(int rept = 0; rept < 4; rept++){
    // DEC_HL;
    // }

    // LD_A_addr(wCurPartyLevel);
    // CP_A_hl;
    // IF_NC goto encounter;
    if(wram->wCurPartyLevel >= wram->wPartyMon[i].mon.level)
        return false;
    // AND_A_A;
    // RET;
    return true;

// encounter:
    // SCF;
    // RET;
}

void LoadWildMonDataPointer(void){
    CALL(aCheckOnWater);
    JR_Z (mv_WaterWildmonLookup);

    return v_GrassWildmonLookup();
}

struct WildMons LoadWildMonDataPointer_Conv(void){
    // CALL(aCheckOnWater);
    // JR_Z (mv_WaterWildmonLookup);
    if(CheckOnWater_Conv())
        return v_WaterWildmonLookup_Conv();
    // return v_GrassWildmonLookup();
    return v_GrassWildmonLookup_Conv();
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

struct WildMons v_GrassWildmonLookup_Conv(void){
    // LD_HL(mSwarmGrassWildMons);
    // LD_BC(GRASS_WILDDATA_LENGTH);
    // CALL(av_SwarmWildmonCheck);
    struct WildMons mons = v_SwarmWildmonCheck_Conv((struct WildMons){.type = 0, .grassMons = SwarmGrassWildMons});
    // RET_C ;
    if(mons.grassMons != NULL)
        return mons;
    // LD_HL(mJohtoGrassWildMons);
    // LD_DE(mKantoGrassWildMons);
    const struct WildGrassMons* hl = (IsInJohto_Conv() == JOHTO_REGION)? JohtoGrassWildMons: KantoGrassWildMons;
    // CALL(av_JohtoWildmonCheck);
    // LD_BC(GRASS_WILDDATA_LENGTH);
    // JR(mv_NormalWildmonOK);
    return v_NormalWildmonOK_Conv((struct WildMons){.type = 0, .grassMons = hl});
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

struct WildMons v_WaterWildmonLookup_Conv(void){
    // LD_HL(mSwarmWaterWildMons);
    // LD_BC(WATER_WILDDATA_LENGTH);
    // CALL(av_SwarmWildmonCheck);
    // RET_C ;
    // LD_HL(mJohtoWaterWildMons);
    // LD_DE(mKantoWaterWildMons);
    // CALL(av_JohtoWildmonCheck);
    const struct WildWaterMons* hl = (IsInJohto_Conv() == JOHTO_REGION)? JohtoWaterWildMons: KantoWaterWildMons;
    // LD_BC(WATER_WILDDATA_LENGTH);
    // JR(mv_NormalWildmonOK);
    return v_NormalWildmonOK_Conv((struct WildMons){.type = 1, .waterMons = hl});
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

struct WildMons v_SwarmWildmonCheck_Conv(struct WildMons mons){
    // CALL(aCopyCurrMapDE);
    struct MapId map = CopyCurrMapDE_Conv();
    // PUSH_HL;
    // LD_HL(wSwarmFlags);
    // BIT_hl(SWARMFLAGS_DUNSPARCE_SWARM_F);
    // POP_HL;
    // IF_Z goto CheckYanma;
    // LD_A_addr(wDunsparceMapGroup);
    // CP_A_D;
    // IF_NZ goto CheckYanma;
    // LD_A_addr(wDunsparceMapNumber);
    // CP_A_E;
    // IF_NZ goto CheckYanma;
    if(bit_test(wram->wSwarmFlags, SWARMFLAGS_DUNSPARCE_SWARM_F) 
    && wram->wDunsparceMapGroup == map.mapGroup
    && wram->wDunsparceMapNumber == map.mapNumber) {
        // CALL(aLookUpWildmonsForMapDE);
        mons = LookUpWildmonsForMapDE_Conv(mons, map);
        // JR_NC (mv_NoSwarmWildmon);
        // SCF;
        // RET;
        return mons;
    }

// CheckYanma:
    // PUSH_HL;
    // LD_HL(wSwarmFlags);
    // BIT_hl(SWARMFLAGS_YANMA_SWARM_F);
    // POP_HL;
    // JR_Z (mv_NoSwarmWildmon);
    // LD_A_addr(wYanmaMapGroup);
    // CP_A_D;
    // JR_NZ (mv_NoSwarmWildmon);
    // LD_A_addr(wYanmaMapNumber);
    // CP_A_E;
    // JR_NZ (mv_NoSwarmWildmon);
    if(bit_test(wram->wSwarmFlags, SWARMFLAGS_YANMA_SWARM_F) 
    && wram->wYanmaMapGroup == map.mapGroup
    && wram->wYanmaMapNumber == map.mapNumber) {
        // CALL(aLookUpWildmonsForMapDE);
        // JR_NC (mv_NoSwarmWildmon);
        // SCF;
        // RET;
        return LookUpWildmonsForMapDE_Conv(mons, map);
    }
    return (struct WildMons){.type = 0xff, .grassMons = NULL};
}

void v_NoSwarmWildmon(void){
    AND_A_A;
    RET;

}

void v_NormalWildmonOK(void){
    CALL(aCopyCurrMapDE);
    JR(mLookUpWildmonsForMapDE);

}

struct WildMons v_NormalWildmonOK_Conv(struct WildMons hl){
    // CALL(aCopyCurrMapDE);
    struct MapId mapId = CopyCurrMapDE_Conv();
    // JR(mLookUpWildmonsForMapDE);
    return LookUpWildmonsForMapDE_Conv(hl, mapId);
}

void CopyCurrMapDE(void){
    LD_A_addr(wMapGroup);
    LD_D_A;
    LD_A_addr(wMapNumber);
    LD_E_A;
    RET;

}

struct MapId CopyCurrMapDE_Conv(void){
    // LD_A_addr(wMapGroup);
    // LD_D_A;
    // LD_A_addr(wMapNumber);
    // LD_E_A;
    // RET;
    return (struct MapId) {.mapNumber = wram->wMapNumber, .mapGroup = wram->wMapGroup};
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

struct WildMons LookUpWildmonsForMapDE_Conv(struct WildMons wm, struct MapId de){
    if(wm.type == 0) {
        const struct WildGrassMons* hl = wm.grassMons;
        do {
        // loop:
            // PUSH_HL;
            // LD_A_hl;
            // INC_A;
            // IF_Z goto nope;
            if(hl->mapNumber == 0xff)
                return (struct WildMons){.type = 0xff, .grassMons = NULL};
            // LD_A_D;
            // CP_A_hl;
            // IF_NZ goto next;
            if(hl->mapNumber == de.mapNumber && hl->mapGroup == de.mapGroup)
                return (struct WildMons){.type = 0, .grassMons = hl};
            // INC_HL;
            // LD_A_E;
            // CP_A_hl;
            // IF_Z goto yup;

        // next:
            // POP_HL;
            // ADD_HL_BC;
            // goto loop;
            hl++;
        } while(1);
    }
    else {
        const struct WildWaterMons* hl = wm.waterMons;
        do {
        // loop:
            // PUSH_HL;
            // LD_A_hl;
            // INC_A;
            // IF_Z goto nope;
            if(hl->mapNumber == 0xff)
                return (struct WildMons){.type = 0xff, .waterMons = NULL};
            // LD_A_D;
            // CP_A_hl;
            // IF_NZ goto next;
            if(hl->mapNumber == de.mapNumber && hl->mapGroup == de.mapGroup)
                return (struct WildMons){.type = 1, .waterMons = hl};
            // INC_HL;
            // LD_A_E;
            // CP_A_hl;
            // IF_Z goto yup;

        // next:
            // POP_HL;
            // ADD_HL_BC;
            // goto loop;
            hl++;
        } while(1);
    }

// nope:
    // POP_HL;
    // AND_A_A;
    // RET;

// yup:
    // POP_HL;
    // SCF;
    // RET;
}

//  initialize wRoamMon structs
void InitRoamMons(void){

//  species
    // LD_A(RAIKOU);
    // LD_addr_A(wRoamMon1Species);
    wram->wRoamMon1.species = RAIKOU;
    // LD_A(ENTEI);
    // LD_addr_A(wRoamMon2Species);
    wram->wRoamMon2.species = ENTEI;

//  level
    // LD_A(40);
    // LD_addr_A(wRoamMon1Level);
    wram->wRoamMon1.level = 40;
    // LD_addr_A(wRoamMon2Level);
    wram->wRoamMon2.level = 40;

//  raikou starting map
    // LD_A(GROUP_ROUTE_42);
    // LD_addr_A(wRoamMon1MapGroup);
    // LD_A(MAP_ROUTE_42);
    // LD_addr_A(wRoamMon1MapNumber);
    wram->wRoamMon1.mapId = MAP_ID_(ROUTE_42);

//  entei starting map
    // LD_A(GROUP_ROUTE_37);
    // LD_addr_A(wRoamMon2MapGroup);
    // LD_A(MAP_ROUTE_37);
    // LD_addr_A(wRoamMon2MapNumber);
    wram->wRoamMon2.mapId = MAP_ID_(ROUTE_37);

//  hp
    // XOR_A_A;  // generate new stats
    // LD_addr_A(wRoamMon1HP);
    // LD_addr_A(wRoamMon2HP);
    wram->wRoamMon1.HP = 0;
    wram->wRoamMon2.HP = 0;

    // RET;
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

static struct MapId UpdateRoamMons_Update(uint8_t mapGroup, uint8_t mapNumber) {
// Update:
    // LD_HL(mRoamMaps);

    for(uint32_t i = 0; i < NUM_ROAMMON_MAPS; ++i) {
    loop:
    //  Are we at the end of the table?
        // LD_A_hl;
        // CP_A(-1);
        // RET_Z ;
    //  Is this the correct entry?
        // LD_A_B;
        // CP_A_hl;
        // IF_NZ goto next;
        // INC_HL;
        // LD_A_C;
        // CP_A_hl;
        // IF_Z goto yes;
        if(RoamMaps[i].src.mapGroup == mapGroup 
        && RoamMaps[i].src.mapNumber == mapNumber) {
        //  We have the correct entry now, so let's choose a random map from it.
        // yes:
            // INC_HL;
            // LD_D_H;
            // LD_E_L;
            const struct MapId* de = RoamMaps[i].maps;

            uint8_t a;
            do {
                do {
                // update_loop:
                    // LD_H_D;
                    // LD_L_E;
                //  Choose which map to warp to.
                    // CALL(aRandom);
                    // AND_A(0b00011111);  // 1/8n chance it moves to a completely random map, where n is the number of roaming connections from the current map.
                    a = Random_Conv() & 0b00011111;
                    // JR_Z (mJumpRoamMon);
                    if(a == 0)
                        return JumpRoamMon_Conv();
                    // AND_A(0b11);
                    // CP_A_hl;
                    // IF_NC goto update_loop;  // invalid index, try again
                } while((a & 0b11) >= RoamMaps[i].count);
                // INC_HL;
                // LD_C_A;
                // LD_B(0);
                // ADD_HL_BC;
                // ADD_HL_BC;
                // LD_A_addr(wRoamMons_LastMapGroup);
                // CP_A_hl;
                // IF_NZ goto done;
                // INC_HL;
                // LD_A_addr(wRoamMons_LastMapNumber);
                // CP_A_hl;
                // IF_Z goto update_loop;
            } while(de[a - 1].mapGroup == wram->wRoamMons_LastMapGroup
                 && de[a - 1].mapNumber == wram->wRoamMons_LastMapNumber);
            // DEC_HL;


        // done:
            // LD_A_hli;
            // LD_B_A;
            // LD_C_hl;
            // RET;
            return de[a - 1];
        }
    //  We don't have the correct entry yet, so let's continue.  A 0 terminates each entry.

    // next:
        // LD_A_hli;
        // AND_A_A;
        // IF_NZ goto next;
        // goto loop;
    }
    return (struct MapId){GROUP_N_A, MAP_N_A};
}

void UpdateRoamMons(void){
    // LD_A_addr(wRoamMon1MapGroup);
    // CP_A(GROUP_N_A);
    // IF_Z goto SkipRaikou;
    if(wram->wRoamMon1.mapId.mapGroup != (uint8_t)GROUP_N_A) {
        // LD_B_A;
        // LD_A_addr(wRoamMon1MapNumber);
        // LD_C_A;
        // CALL(aUpdateRoamMons_Update);
        struct MapId new_map = UpdateRoamMons_Update(wram->wRoamMon1.mapId.mapGroup, wram->wRoamMon1.mapId.mapNumber);
        // LD_A_B;
        // LD_addr_A(wRoamMon1MapGroup);
        wram->wRoamMon1.mapId = new_map;
        // LD_A_C;
        // LD_addr_A(wRoamMon1MapNumber);
    }

// SkipRaikou:
    // LD_A_addr(wRoamMon2MapGroup);
    // CP_A(GROUP_N_A);
    // IF_Z goto SkipEntei;
    if(wram->wRoamMon2.mapId.mapGroup != (uint8_t)GROUP_N_A) {
        // LD_B_A;
        // LD_A_addr(wRoamMon2MapNumber);
        // LD_C_A;
        // CALL(aUpdateRoamMons_Update);
        struct MapId new_map = UpdateRoamMons_Update(wram->wRoamMon2.mapId.mapGroup, wram->wRoamMon2.mapId.mapNumber);
        // LD_A_B;
        // LD_addr_A(wRoamMon2MapGroup);
        wram->wRoamMon2.mapId = new_map;
        // LD_A_C;
        // LD_addr_A(wRoamMon2MapNumber);
    }

// SkipEntei:
    // LD_A_addr(wRoamMon3MapGroup);
    // CP_A(GROUP_N_A);
    // IF_Z goto Finished;
    if(wram->wRoamMon3.mapId.mapGroup != (uint8_t)GROUP_N_A) {
        // LD_B_A;
        // LD_A_addr(wRoamMon3MapNumber);
        // LD_C_A;
        // CALL(aUpdateRoamMons_Update);
        struct MapId new_map = UpdateRoamMons_Update(wram->wRoamMon3.mapId.mapGroup, wram->wRoamMon3.mapId.mapNumber);
        // LD_A_B;
        // LD_addr_A(wRoamMon3MapGroup);
        wram->wRoamMon3.mapId = new_map;
        // LD_A_C;
        // LD_addr_A(wRoamMon3MapNumber);
    }

// Finished:
    // JP(mv_BackUpMapIndices);
    return v_BackUpMapIndices();
}

void JumpRoamMons(void){
    // LD_A_addr(wRoamMon1MapGroup);
    // CP_A(GROUP_N_A);
    // IF_Z goto SkipRaikou;
    if(wram->wRoamMon1.mapId.mapGroup != (uint8_t)GROUP_N_A) {
        // CALL(aJumpRoamMon);
        struct MapId new_map = JumpRoamMon_Conv();
        // LD_A_B;
        // LD_addr_A(wRoamMon1MapGroup);
        wram->wRoamMon1.mapId = new_map;
        // LD_A_C;
        // LD_addr_A(wRoamMon1MapNumber);
    }


// SkipRaikou:
    // LD_A_addr(wRoamMon2MapGroup);
    // CP_A(GROUP_N_A);
    // IF_Z goto SkipEntei;
    if(wram->wRoamMon2.mapId.mapGroup != (uint8_t)GROUP_N_A) {
        // CALL(aJumpRoamMon);
        struct MapId new_map = JumpRoamMon_Conv();
        // LD_A_B;
        // LD_addr_A(wRoamMon2MapGroup);
        wram->wRoamMon2.mapId = new_map;
        // LD_A_C;
        // LD_addr_A(wRoamMon2MapNumber);
    }


// SkipEntei:
    // LD_A_addr(wRoamMon3MapGroup);
    // CP_A(GROUP_N_A);
    // IF_Z goto Finished;
    if(wram->wRoamMon3.mapId.mapGroup != (uint8_t)GROUP_N_A) {
        // CALL(aJumpRoamMon);
        struct MapId new_map = JumpRoamMon_Conv();
        // LD_A_B;
        // LD_addr_A(wRoamMon3MapGroup);
        wram->wRoamMon3.mapId = new_map;
        // LD_A_C;
        // LD_addr_A(wRoamMon3MapNumber);
    }

// Finished:
    // JP(mv_BackUpMapIndices);
    return v_BackUpMapIndices();
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

struct MapId JumpRoamMon_Conv(void){

    uint8_t a;
    do {
    // loop:
        // LD_HL(mRoamMaps);

    // innerloop1:
    // 0-15 are all valid indexes into RoamMaps,
    // so this retry loop is unnecessary
    // since NUM_ROAMMON_MAPS happens to be 16
        // CALL(aRandom);
        // maskbits(NUM_ROAMMON_MAPS, 0);
        // CP_A(NUM_ROAMMON_MAPS);
        // IF_NC goto innerloop1;
        a = Random_Conv() & 0xf;
        // INC_A;
        // LD_B_A;

    // innerloop2:
    //   //  Loop to get hl to the address of the chosen roam map.
        // DEC_B;
        // IF_Z goto ok;

    // innerloop3:
    //   //  Loop to skip the current roam map, which is terminated by a 0.
        // LD_A_hli;
        // AND_A_A;
        // IF_NZ goto innerloop3;
        // goto innerloop2;
    //  Check to see if the selected map is the one the player is currently in.  If so, try again.

    // ok:
        // LD_A_addr(wMapGroup);
        // CP_A_hl;
        // IF_NZ goto done;
        // INC_HL;
        // LD_A_addr(wMapNumber);
        // CP_A_hl;
        // IF_Z goto loop;
    } while(RoamMaps[a].src.mapGroup == wram->wMapGroup
         && RoamMaps[a].src.mapNumber == wram->wMapNumber);
    // DEC_HL;
//  Return the map group and number in bc.

// done:
    // LD_A_hli;
    // LD_B_A;
    // LD_C_hl;
    // RET;
    return RoamMaps[a].src;
}

void v_BackUpMapIndices(void){
    // LD_A_addr(wRoamMons_CurMapNumber);
    // LD_addr_A(wRoamMons_LastMapNumber);
    wram->wRoamMons_LastMapNumber = wram->wRoamMons_CurMapNumber;
    // LD_A_addr(wRoamMons_CurMapGroup);
    // LD_addr_A(wRoamMons_LastMapGroup);
    wram->wRoamMons_LastMapGroup = wram->wRoamMons_CurMapGroup;
    // LD_A_addr(wMapNumber);
    // LD_addr_A(wRoamMons_CurMapNumber);
    wram->wRoamMons_CurMapNumber = wram->wMapNumber;
    // LD_A_addr(wMapGroup);
    // LD_addr_A(wRoamMons_CurMapGroup);
    wram->wRoamMons_CurMapGroup = wram->wMapGroup;
    // RET;

// INCLUDE "data/wild/roammon_maps.asm"
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

//  Due to a development oversight, this function is called with the wild Pokemon's level, not its species, in a.
bool ValidateTempWildMonSpecies_Conv(species_t a){
    // AND_A_A;
    // IF_Z goto nowildmon;  // = 0
    if(a == 0)
        return false;
    // CP_A(NUM_POKEMON + 1);  // 252
    // IF_NC goto nowildmon;  // >= 252
    if(a >= NUM_POKEMON + 1)
        return false;
    // AND_A_A;  // 1 <= Species <= 251
    // RET;
    return true;
// nowildmon:
    // SCF;
    // RET;
}

void RandomUnseenWildMon(void){
    static const txt_cmd_s JustSawSomeRareMonText[] = {
        text_far(v_JustSawSomeRareMonText)
        text_end
    };
    // FARCALL(aGetCallerLocation);
    // LD_D_B;
    // LD_E_C;
    struct CallerLocation loc = GetCallerLocation_Conv();
    // LD_HL(mJohtoGrassWildMons);
    // LD_BC(GRASS_WILDDATA_LENGTH);
    // CALL(aLookUpWildmonsForMapDE);
    struct WildMons mons = LookUpWildmonsForMapDE_Conv((struct WildMons){.grassMons = JohtoGrassWildMons, .type=0}, (struct MapId){loc.mgroup, loc.mnum});
    // IF_C goto GetGrassmon;
    // LD_HL(mKantoGrassWildMons);
    // CALL(aLookUpWildmonsForMapDE);
    // IF_NC goto done;
    if(mons.grassMons == NULL) {
        mons = LookUpWildmonsForMapDE_Conv(
            (struct WildMons){.grassMons = KantoGrassWildMons, .type=0}, (struct MapId){loc.mgroup, loc.mnum});
        if(mons.grassMons == NULL){
            wram->wScriptVar = 0x1;
            return;
        }
    }

// GetGrassmon:
    // PUSH_HL;
    // LD_BC(5 + 4 * 2);  // Location of the level of the 5th wild Pokemon in that map
    // ADD_HL_BC;
    // LD_A_addr(wTimeOfDay);
    // LD_BC(NUM_GRASSMON * 2);
    // CALL(aAddNTimes);

    uint8_t a;
    do {
    // randloop1:
        // CALL(aRandom);
        // AND_A(0b11);
        a = Random_Conv() & 0b11;
        // IF_Z goto randloop1;
    } while(a == 0);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    uint8_t idx = 5 + a;
//  We now have the pointer to one of the last (rarest) three wild Pokemon found in that area.
    // INC_HL;
    // LD_C_hl;  // Contains the species index of this rare Pokemon
    species_t rare = mons.grassMons->mons[wram->wTimeOfDay][idx].species;
    // POP_HL;
    // LD_DE(5 + 0 * 2);
    // ADD_HL_DE;
    // INC_HL;  // Species index of the most common Pokemon on that route
    uint8_t idx2 = 0;
    // LD_B(4);

    while(idx2 < 4){
    // loop2:
        // LD_A_hli;
        // CP_A_C;  // Compare this most common Pokemon with the rare one stored in c.
        // IF_Z goto done;
        if(mons.grassMons->mons[wram->wTimeOfDay][idx2].species == rare){
            wram->wScriptVar = 0x1;
            return;
        }
        // INC_HL;
        idx2++;
        // DEC_B;
        // IF_NZ goto loop2;
    }
//  This Pokemon truly is rare.
    // PUSH_BC;
    // DEC_C;
    // LD_A_C;
    // CALL(aCheckSeenMon);
    // POP_BC;
    // IF_NZ goto done;
    if(CheckSeenMon_Conv(rare - 1)){
        wram->wScriptVar = 0x1;
        return;
    }
//  Since we haven't seen it, have the caller tell us about it.
    // LD_DE(wStringBuffer1);
    // CALL(aCopyName1);
    CopyName1_Conv2(wram->wStringBuffer1);
    // LD_A_C;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName_Conv2(rare);
    // LD_HL(mRandomUnseenWildMon_JustSawSomeRareMonText);
    // CALL(aPrintText);
    PrintText_Conv2(JustSawSomeRareMonText);
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x0;
    // RET;
    return;

// done:
    // LD_A(0x1);
    // LD_addr_A(wScriptVar);
    // RET;
}

void RandomPhoneWildMon(void){
    // FARCALL(aGetCallerLocation);
    // LD_D_B;
    // LD_E_C;
    struct CallerLocation loc = GetCallerLocation_Conv();
    // LD_HL(mJohtoGrassWildMons);
    // LD_BC(GRASS_WILDDATA_LENGTH);
    // CALL(aLookUpWildmonsForMapDE);
    // IF_C goto ok;
    // LD_HL(mKantoGrassWildMons);
    // CALL(aLookUpWildmonsForMapDE);
    struct WildMons mons = LookUpWildmonsForMapDE_Conv(
        (struct WildMons){.grassMons = JohtoGrassWildMons, .type=0}, (struct MapId){loc.mgroup, loc.mnum});

    if(mons.grassMons == NULL)
        mons = LookUpWildmonsForMapDE_Conv(
            (struct WildMons){.grassMons = KantoGrassWildMons, .type=0}, (struct MapId){loc.mgroup, loc.mnum});

// ok:
    // LD_BC(5 + 0 * 2);
    // ADD_HL_BC;
    // LD_A_addr(wTimeOfDay);
    // INC_A;
    // LD_BC(NUM_GRASSMON * 2);

// loop:
    // DEC_A;
    // IF_Z goto done;
    // ADD_HL_BC;
    // goto loop;


// done:
    // CALL(aRandom);
    // AND_A(0b11);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // INC_HL;
    // LD_A_hl;
    species_t s = mons.grassMons->mons[wram->wTimeOfDay][Random_Conv() & 0b11].species;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wStringBuffer4);
    // LD_BC(MON_NAME_LENGTH);
    // JP(mCopyBytes);
    return CopyBytes_Conv2(wram->wStringBuffer4,
        GetPokemonName_Conv2(s), MON_NAME_LENGTH);
}

//  Get a random monster owned by the trainer who's calling.
void RandomPhoneMon(void){
    // FARCALL(aGetCallerLocation);
    struct CallerLocation loc = GetCallerLocation_Conv();
    // LD_HL(mTrainerGroups);
    // LD_A_D;
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A(BANK(aTrainerGroups));
    // CALL(aGetFarWord);
    const struct TrainerParty* party = TrainerGroups[loc.tclass - 1].parties + loc.tid;


// skip_trainer:
    // DEC_E;
    // IF_Z goto skipped;

// skip:
    // LD_A(BANK(aTrainers));
    // CALL(aGetFarByte);
    // INC_HL;
    // CP_A(-1);
    // IF_NZ goto skip;
    // goto skip_trainer;

// skipped:


// skip_name:
    // LD_A(BANK(aTrainers));
    // CALL(aGetFarByte);
    // INC_HL;
    // CP_A(0x50);
    // IF_NZ goto skip_name;

    // LD_A(BANK(aTrainers));
    // CALL(aGetFarByte);
    // INC_HL;
    // LD_BC(2);  // level, species
    // CP_A(TRAINERTYPE_NORMAL);
    // IF_Z goto got_mon_length;
    // LD_BC(2 + NUM_MOVES);  // level, species, moves
    // CP_A(TRAINERTYPE_MOVES);
    // IF_Z goto got_mon_length;
    // LD_BC(2 + 1);  // level, species, item
    // CP_A(TRAINERTYPE_ITEM);
    // IF_Z goto got_mon_length;
// TRAINERTYPE_ITEM_MOVES
    // LD_BC(2 + 1 + NUM_MOVES);  // level, species, item, moves

// got_mon_length:

    // LD_E(0);
    // PUSH_HL;

// count_mon:
    // INC_E;
    // ADD_HL_BC;
    // LD_A(BANK(aTrainers));
    // CALL(aGetFarByte);
    // CP_A(-1);
    // IF_NZ goto count_mon;
    // POP_HL;

    uint8_t a;
    do {
    // rand:
        // CALL(aRandom);
        // maskbits(PARTY_LENGTH, 0);
        a = Random_Conv() & 7;
        // CP_A_E;
        // IF_NC goto rand;
    } while(a >= party->size);

    // INC_A;

// get_mon:
    // DEC_A;
    // IF_Z goto got_mon;
    // ADD_HL_BC;
    // goto get_mon;

// got_mon:
    // INC_HL;  // species
    // LD_A(BANK(aTrainers));
    // CALL(aGetFarByte);
    species_t s;
    switch(party->trainer_type) {
        case TRAINERTYPE_ITEM:      s = party->pitem[a].species; break;
        case TRAINERTYPE_ITEM_MOVES:s = party->pitemmoves[a].species; break;
        case TRAINERTYPE_MOVES:     s = party->pmoves[a].species; break;
        default:
        case TRAINERTYPE_NORMAL:    s = party->pnormal[a].species; break;
    }
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wStringBuffer4);
    // LD_BC(MON_NAME_LENGTH);
    // JP(mCopyBytes);
    CopyBytes_Conv2(wram->wStringBuffer4, GetPokemonName_Conv2(s), MON_NAME_LENGTH);

// INCLUDE "data/wild/johto_grass.asm"
// INCLUDE "data/wild/johto_water.asm"
// INCLUDE "data/wild/kanto_grass.asm"
// INCLUDE "data/wild/kanto_water.asm"
// INCLUDE "data/wild/swarm_grass.asm"
// INCLUDE "data/wild/swarm_water.asm"

}
