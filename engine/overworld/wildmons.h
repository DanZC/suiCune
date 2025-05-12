void LoadWildMonData(void);
void FindNest(uint8_t e, species_t species);
bool TryWildEncounter(void);
uint8_t GetMapEncounterRate(void);
uint8_t ApplyMusicEffectOnEncounterRate(uint8_t b);
uint8_t ApplyCleanseTagEffectOnEncounterRate(uint8_t b);
bool ChooseWildEncounter(void);
bool CheckRepelEffect(void);
struct WildMons LoadWildMonDataPointer(void);
struct WildMons v_GrassWildmonLookup(void);
struct WildMons v_WaterWildmonLookup(void);
void v_JohtoWildmonCheck(void);
struct WildMons v_SwarmWildmonCheck(struct WildMons mons);
void v_NoSwarmWildmon(void);
struct WildMons v_NormalWildmonOK(struct WildMons hl);
struct MapId CopyCurrMapDE(void);
struct WildMons LookUpWildmonsForMapDE(struct WildMons hl, struct MapId de);
void InitRoamMons(void);
bool CheckEncounterRoamMon(void);
void UpdateRoamMons(void);
void JumpRoamMons(void);
struct MapId JumpRoamMon(void);
void v_BackUpMapIndices(void);
bool ValidateTempWildMonSpecies(species_t a);
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
