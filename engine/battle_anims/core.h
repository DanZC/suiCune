void QueueBattleAnimation(void);
bool QueueBattleAnimation_Conv(void);
void DeinitBattleAnimation(void);
void DeinitBattleAnimation_Conv(struct BattleAnim* bc);
void InitBattleAnimation(void);
void InitBattleAnimation_Conv(struct BattleAnim* bc);
void BattleAnimOAMUpdate(void);
bool BattleAnimOAMUpdate_Conv(struct BattleAnim* bc, uint8_t* oamIndex);
void InitBattleAnimBuffer(void);
void InitBattleAnimBuffer_Conv(struct BattleAnim* bc);
void GetBattleAnimTileOffset(void);
uint8_t GetBattleAnimTileOffset_Conv(uint8_t a);
void v_ExecuteBGEffects(void);
void v_ExecuteBGEffects_Conv(void);
void v_QueueBGEffect(void);
bool v_QueueBGEffect_Conv(void);
//#include "data/battle_anims/objects.h"
