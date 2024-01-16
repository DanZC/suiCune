void AddPhoneNumber(void);
bool AddPhoneNumber_Conv(uint8_t c);
bool AddPhoneNumber_Conv2(uint8_t c);
void DelCellNum(void);
bool DelCellNum_Conv(uint8_t c);
bool DelCellNum_Conv2(uint8_t c);
void CheckCellNum(void);
void v_CheckCellNum(void);
uint16_t v_CheckCellNum_Conv(uint8_t c);
uint8_t* v_CheckCellNum_Conv2(uint8_t c);
void Phone_FindOpenSlot(void);
uint16_t Phone_FindOpenSlot_Conv(uint8_t c);
uint8_t* Phone_FindOpenSlot_Conv2(uint8_t c);
void GetRemainingSpaceInPhoneList(void);
uint8_t GetRemainingSpaceInPhoneList_Conv(uint8_t c);
uint8_t GetRemainingSpaceInPhoneList_Conv2(uint8_t c);
void BrokenPlaceFarString(void);
void CheckPhoneCall(void);
u8_flag_s CheckPhoneCall_Conv(void);
void CheckPhoneContactTimeOfDay(void);
void ChooseRandomCaller(void);
u8_flag_s ChooseRandomCaller_Conv(void);
void GetAvailableCallers(void);
void GetAvailableCallers_Conv(void);
void CheckSpecialPhoneCall(void);
bool CheckSpecialPhoneCall_Conv(void);
void SpecialCallOnlyWhenOutside(void);
bool SpecialCallOnlyWhenOutside_Conv(void);
void SpecialCallWhereverYouAre(void);
bool SpecialCallWhereverYouAre_Conv(void);
void MakePhoneCallFromPokegear(void);
void MakePhoneCallFromPokegear_Conv(uint8_t caller);
bool LoadPhoneScriptBank(script_s* s);
bool LoadOutOfAreaScript(script_s* s);
void LoadCallerScript(void);
void LoadCallerScript_Conv(uint8_t caller);
// void WrongNumber(void);
extern const struct PhoneContact WrongNumber;
bool Script_ReceivePhoneCall(script_s* s);
bool Script_SpecialBillCall(script_s* s);
void Script_SpecialBillCall_LoadBillScript(void);
bool Script_SpecialElmCall(script_s* s);
void Script_SpecialElmCall_LoadElmScript(void);
void RingTwice_StartCall(void);
void PhoneCall(void);
void PhoneCall_Conv(Script_fn_t de);
void Phone_NoSignal(void);
void HangUp(void);
void Phone_CallEnd(void);
void HangUp_ShutDown(void);
void HangUp_Beep(void);
extern const struct TextCmd PhoneClickText[];
void HangUp_BoopOn(void);
extern const struct TextCmd PhoneEllipseText[];
void HangUp_BoopOff(void);
void Phone_StartRinging(void);
void HangUp_Wait20Frames(void);
void Phone_Wait20Frames(void);
void Phone_TextboxWithName(void);
void Phone_TextboxWithName_Conv(uint8_t caller);
void Phone_CallerTextbox(void);
void Phone_CallerTextbox_Conv(void);
void GetCallerClassAndName(void);
void GetCallerClassAndName_Conv(uint8_t* de, uint8_t b);
void CheckCanDeletePhoneNumber(void);
bool CheckCanDeletePhoneNumber_Conv(uint8_t c);
void GetCallerTrainerClass(void);
struct TrainerId GetCallerTrainerClass_Conv(uint8_t caller);
void GetCallerName(void);
void GetCallerName_Conv(uint8_t* hl, struct TrainerId c);
void Phone_GetTrainerName(void);
void Phone_GetTrainerClassName(void);
void GetCallerLocation(void);
struct CallerLocation GetCallerLocation_Conv(void);
bool PhoneOutOfAreaScript(script_s* s);
extern const struct TextCmd PhoneOutOfAreaText[];
bool PhoneScript_JustTalkToThem(script_s* s);
extern const struct TextCmd PhoneJustTalkToThemText[];
bool PhoneThankYouTextScript(script_s* s);
extern const struct TextCmd PhoneThankYouText[];
//#include "data/phone/permanent_numbers.h"
//#include "data/phone/non_trainer_names.h"
//#include "data/phone/phone_contacts.h"
//#include "data/phone/special_calls.h"
extern struct PhoneContact gCallerContact;
