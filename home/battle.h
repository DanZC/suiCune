uint16_t GetPartyParamLocation(uint8_t a);
struct PartyMon* GetPartyLocation(struct PartyMon* hl, uint8_t a);
uint16_t GetPartyLocation_GB(uint16_t hl, uint8_t a);
void GetDexNumber(void);
uint16_t UserPartyAttr(uint8_t a);
struct PartyMon* UserPartyMon(void);
uint16_t OpponentPartyAttr(uint8_t a);
struct PartyMon* OpponentPartyMon(void);
uint16_t BattlePartyAttr(uint8_t a);
uint16_t OTPartyAttr(uint8_t a);
void ResetDamage(void);
void SetPlayerTurn(void);
void SetEnemyTurn(void);
void UpdateOpponentInParty(void);
void UpdateUserInParty(void);
void UpdateBattleMonInParty(void);
void UpdateBattleMon(uint8_t a);
void UpdateEnemyMonInParty(void);
void UpdateEnemyMonInParty(void);
void RefreshBattleHuds(void);
void UpdateBattleHuds(void);
void FarCopyRadioText(void);
void MobileTextBorder(void);
void BattleTextbox(const struct TextCmd* hl);
void StdBattleTextbox(const struct TextCmd* hl);
void GetBattleAnimPointer(uint16_t hl);
uint8_t GetBattleAnimByte(void);
void PushLYOverrides(void);
#include "battle_vars.h"
