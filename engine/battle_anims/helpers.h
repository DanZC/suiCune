void ReinitBattleAnimFrameset(void);
void ReinitBattleAnimFrameset_Conv(struct BattleAnim* bc, uint8_t a);
void GetBattleAnimFrame(void);
uint8_t GetBattleAnimFrame_Conv(struct BattleAnim* bc);
void GetBattleAnimOAMPointer(void);
const struct BattleOAMData* GetBattleAnimOAMPointer_Conv(uint8_t a);
void LoadBattleAnimGFX(void);
uint8_t LoadBattleAnimGFX_Conv(uint8_t* de, uint8_t a);
//#include "data/battle_anims/framesets.h"
//#include "data/battle_anims/oam.h"
//#include "data/battle_anims/object_gfx.h"
