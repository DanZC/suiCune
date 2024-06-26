bool CheckForMobileBattleRules(void);
bool v_CheckForBattleTowerRules(void);
extern const txt_cmd_s ExcuseMeYoureNotReadyText[];
void BattleTower_PleaseReturnWhenReady(void);
extern const txt_cmd_s NeedAtLeastThreeMonText[];
extern const txt_cmd_s EggDoesNotQualifyText[];
extern const txt_cmd_s OnlyThreeMonMayBeEnteredText[];
extern const txt_cmd_s TheMonMustAllBeDifferentKindsText[];
extern const txt_cmd_s TheMonMustNotHoldTheSameItemsText[];
extern const txt_cmd_s YouCantTakeAnEggText[];
// bool BattleTower_ExecuteJumptable(void);
bool BattleTower_CheckPartyLengthIs3(void);
bool BattleTower_CheckPartyHasThreeMonsThatAreNotEggs(void);
bool CheckBTRule_PartyCountEq3(void);
bool CheckBTRule_PartySpeciesAreUnique(void);
bool CheckPartyValueIsUnique(const struct PartyMon* hl, const species_t* de, uint8_t count);
bool CheckPartyItemIsUnique(const struct PartyMon* hl, const species_t* de, uint8_t count);
bool CheckBTRule_PartyItemsAreUnique(void);
bool CheckBTRule_HasPartyAnEgg(void);
