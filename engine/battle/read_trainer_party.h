void ReadTrainerParty(void);
// void TrainerTypes(void);
void TrainerType1(void);
void TrainerType1_Conv(const struct TrainerParty* de);
void TrainerType2(void);
void TrainerType2_Conv(const struct TrainerParty* de);
void TrainerType3(void);
void TrainerType3_Conv(const struct TrainerParty* de);
void TrainerType4(void);
void TrainerType4_Conv(const struct TrainerParty* de);
void ComputeTrainerReward(void);
void Battle_GetTrainerName(void);
uint8_t* Battle_GetTrainerName_Conv(void);
void GetTrainerName(void);
uint8_t* GetTrainerName_Conv(uint8_t tid, uint8_t tclass);
void CopyTrainerName(void);
uint8_t* CopyTrainerName_Conv(const uint8_t* hl);
void IncompleteCopyNameFunction(void);
//#include "data/trainers/parties.h"
