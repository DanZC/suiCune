bool QueueBattleAnimation(void);
void DeinitBattleAnimation(struct BattleAnim* bc);
// void InitBattleAnimation(struct BattleAnim* bc);
bool BattleAnimOAMUpdate(struct BattleAnim* bc, uint8_t* oamIndex);
// void InitBattleAnimBuffer(struct BattleAnim* bc);
// uint8_t GetBattleAnimTileOffset(uint8_t a);
void v_ExecuteBGEffects(void);
bool v_QueueBGEffect(void);
//#include "data/battle_anims/objects.h"
