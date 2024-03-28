void TreeMonEncounter(void);
void RockMonEncounter(void);
void GetTreeMonSet(void);
u8_flag_s GetTreeMonSet_Conv(const struct TreeMonMap table[], size_t table_size);
void GetTreeMons(void);
const uint8_t* GetTreeMons_Conv(uint8_t a);
void GetTreeMon(void);
bool GetTreeMon_Conv(const uint8_t* hl);
bool SelectTreeMon(const uint8_t* hl);
bool NoTreeMon(void);
void GetTreeScore(void);
uint8_t GetTreeScore_Conv(void);
//#include "data/wild/treemon_maps.h"
//#include "data/wild/treemons.h"
