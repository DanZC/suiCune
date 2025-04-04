void BattleTowerRoomMenu(void);
void BattleTowerRoomMenu_Mobile(void);
void Function1700ba(void);
void Function1700c4(void);
void Function170114(void);
void Function170139(void);
void BattleTowerBattle(void);
void UnusedBattleTowerDummySpecial1(void);
void InitBattleTowerChallengeRAM(void);
void v_BattleTowerBattle(void);
void RunBattleTowerTrainer(void);
void ReadBTTrainerParty(void);
void ValidateBTParty(void);
extern const char BT_ChrisName[];
void Function17042c(void);
void CopyBTTrainer_FromBT_OT_TowBT_OTTemp(void);
void SkipBattleTowerTrainer(void);
struct BattleTowerData* Function1704ca(void);
void Function1704e1(void);
void BattleTowerAction(void);
void ResetBattleTowerTrainersSRAM(void);
void BattleTower_GiveReward(void);
void Function17071b(void);
void Function170729(void);
void BattleTower_SaveOptions(void);
void BattleTower_RandomlyChooseReward(void);
void BattleTowerAction_CheckExplanationRead(void);
void BattleTowerAction_GetChallengeState(void);
void BattleTowerAction_SetExplanationRead(void);
void BattleTowerAction_SetByteToQuickSaveChallenge(void);
void BattleTowerAction_SetByteToCancelChallenge(void);
void SetBattleTowerChallengeState(uint8_t c);
void Function1707ac(void);
void Function1707f4(void);
void Function170807(void);
void Function17081d(void);
void SaveBattleTowerLevelGroup(void);
void LoadBattleTowerLevelGroup(void);
void BattleTower_CheckSaveFileExistsAndIsYours(void);
void Function1708b1(void);
void CheckMobileEventIndex(void);
void Function1708c8(void);
void Function1708f0(void);
void Function170923(void);
void BattleTowerAction_EggTicket(void);
extern const char String_MysteryJP[];
void Function1709aa(void);
void Function1709bb(void);
void Function170a9c(void);
void Function170aa0(void);
void Set_s5_aa8d(uint8_t c);
void Function170aaf(void);
void Function170abe(void);
void Function170ad7(void);
void BattleTowerAction_LevelCheck(void);
void BattleTowerAction_UbersCheck(void);
void LoadOpponentTrainerAndPokemonWithOTSprite(void);
void UnusedBattleTowerDummySpecial2(void);
void CheckForBattleTowerRules(void);

extern uint8_t gBattleTowerType;
enum {
    BATTLE_TOWER_LOCAL,
    BATTLE_TOWER_MOBILE,
};
//#include "data/battle_tower/unknown_levels.h"
//#include "data/trainers/sprites.h"
