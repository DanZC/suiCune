void LoadWildMonData(void);
void FindNest(void);
void TryWildEncounter(void);
bool TryWildEncounter_Conv(void);
void GetMapEncounterRate(void);
void ApplyMusicEffectOnEncounterRate(void);
uint8_t ApplyMusicEffectOnEncounterRate_Conv(uint8_t b);
void ApplyCleanseTagEffectOnEncounterRate(void);
uint8_t ApplyCleanseTagEffectOnEncounterRate_Conv(uint8_t b);
void ChooseWildEncounter(void);
bool ChooseWildEncounter_Conv(void);
void CheckRepelEffect(void);
bool CheckRepelEffect_Conv(void);
void LoadWildMonDataPointer(void);
const struct WildGrassMons* LoadWildMonDataPointer_Conv(void);
void v_GrassWildmonLookup(void);
const struct WildGrassMons* v_GrassWildmonLookup_Conv(void);
void v_WaterWildmonLookup(void);
void v_JohtoWildmonCheck(void);
void v_SwarmWildmonCheck(void);
void v_NoSwarmWildmon(void);
void v_NormalWildmonOK(void);
const struct WildGrassMons* v_NormalWildmonOK_Conv(const struct WildGrassMons* hl);
void CopyCurrMapDE(void);
struct MapId CopyCurrMapDE_Conv(void);
void LookUpWildmonsForMapDE(void);
const struct WildGrassMons* LookUpWildmonsForMapDE_Conv(const struct WildGrassMons* hl, struct MapId de);
void InitRoamMons(void);
void CheckEncounterRoamMon(void);
void UpdateRoamMons(void);
void JumpRoamMons(void);
void JumpRoamMon(void);
struct MapId JumpRoamMon_Conv(void);
void v_BackUpMapIndices(void);
void ValidateTempWildMonSpecies(void);
bool ValidateTempWildMonSpecies_Conv(species_t a);
void RandomUnseenWildMon(void);
void RandomPhoneWildMon(void);
void RandomPhoneMon(void);
//#include "data/wild/probabilities.h"
//#include "data/wild/roammon_maps.h"
//#include "data/wild/johto_grass.h"
//#include "data/wild/johto_water.h"
//#include "data/wild/kanto_grass.h"
//#include "data/wild/kanto_water.h"
//#include "data/wild/swarm_grass.h"
//#include "data/wild/swarm_water.h"
