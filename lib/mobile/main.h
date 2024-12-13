void* MobileSDK_CopyBytes(void* de, const void* hl, uint8_t b);
char* MobileSDK_CopyString(char* de, const char* hl, uint16_t* bc);
char* MobileSDK_CopyStringLen(char* de, const char* hl, uint16_t* bc, uint8_t a);
void ResetReceivePacketBuffer(void);
void v_MobileAPI(mobile_api_data_s *api);
bool Function1100b4(void);
void MobileAPI_SetTimer(mobile_api_data_s *);
void Function110115(mobile_api_data_s *);
void Function110226(void);
void Function110228(uint8_t a);
void Function110231(void);
void Function110235(mobile_api_data_s *);
void Function110236(mobile_api_data_s *);
void Function110291(mobile_api_data_s *);
void Function11032c(void);
void Function110393(void);
bool Function11039a(const uint8_t* hl, uint8_t c);
void Function1103ac(mobile_api_data_s *);
void Function110432(void);
void Function110438(mobile_api_data_s *);
void Function110485(void);
void Function1104b0(void);
void Function1104c6(void);
void Function110578(void);
void Function110582(void);
void Function11058c(void);
void Function110596(void);
void Function1105dd(void);
void Function110615(void);
void Function1106ef(void);
void Function110757(void);
void Function1107ff(void);
void Function110899(void);
void Function1108a3(void);
void Function1108ab(void);
void Function110905(void);
void Function1109a4(void);
void Function1109f9(void);
void Function110a5b(void);
void Function110af4(void);
void Function110c3c(void);
void Function110c9e(void);
void Function110d37(void);
void Function110ddd(void);
void Function110f07(void);
extern const char URIPrefix[];
extern const char HTTPDownloadURL[];
extern const char HTTPUploadURL[];
extern const char HTTPUtilityURL[];
extern const char HTTPRankingURL[];
void Function111044(void);
void Function11115f(void);
void Function1111ca(void);
void Function1111d7(void);
void Function1111fe(void);
void Function111335(void);
void Function1113ea(void);
void Function1113f7(void);
void Function1113f8(void);
void Function1113fe(mobile_api_data_s *);
void Function11148c(void);
void Function111540(mobile_api_data_s *);
void Function111541(mobile_api_data_s *);
void Function111596(void);
void Function1115e4(void);
void Function111610(void);
void Function11162d(mobile_api_data_s *);
void Function11164f(void);
void Function111664(uint8_t c);
void Function111686(void);
void Function1116a0(void);
void Function1116a4(uint8_t* hl);
void Function1116a9(uint8_t a);
void v_MobileReceive(void);
void Function11177c(void);
void Function111796(void);
void asm_11179a(uint8_t* hl);
void Function1117a0(void);
void asm_1117a2(uint8_t b);
void Function1117e7(void);
void Function11186e(void);
void Function111884(void);
void Function111892(void);
void Function1118bc(void);
void Function1118c2(void);
void v_Timer(void);
void Function1119f0(void);
void Function111a0b(uint8_t a);
void Function111a2a(void);
void asm_111a40(void);
void Function111a42(uint8_t a);
void asm_111a47(void);
void Function111ab9(void);
void Function111abd(void);
void Function111b21(void);
void Function111b2e(void);
void Function111b3b(void);
void Function111b3c(void);
void Function111c06(void);
void Function111c17(void);
void Function111cc2(void);
void Function111d07(void);
void Function111d23(void);
void ParseResponse_BeginSession(void);
void Function111d65(void);
void Function111d70(void);
uint8_t Function111dd9(uint8_t a, uint8_t b);
void Function111e15(uint8_t b);
void Function111e28(void);
void GetErrorCode(void);
void Function111ef8(void);
bool PacketSendEmptyBody(const uint8_t* bytes, uint8_t id);
bool Function111f02(const uint8_t* bytes, uint16_t size, uint8_t id);
bool PacketSendBytes(const uint8_t* bytes, uint16_t size, uint8_t b);
uint16_t Function111f63(void* de, uint8_t b);
void Function111f8d(uint8_t** de, uint16_t* hl, uint8_t* b);
bool Function111f97(void);
extern const uint8_t MobilePacket_Idle[];
extern const uint8_t MobilePacket_BeginSession[];
extern const uint8_t MobilePacket_EndSession[];
extern const uint8_t MobilePacket_DialTelephone[];
extern const uint8_t MobilePacket_HangUpTelephone[];
extern const uint8_t MobilePacket_TelephoneStatus[];
extern const uint8_t MobilePacket_ISPLogin[];
extern const uint8_t MobilePacket_ISPLogout[];
extern const uint8_t MobilePacket_ReadConfigurationDataPart1[];
extern const uint8_t MobilePacket_ReadConfigurationDataPart2[];
extern const uint8_t MobilePacket_WriteConfigurationData[];
extern const uint8_t MobilePacket_DNSQuery[];
extern const uint8_t MobilePacket_WaitForTelephoneCall[];
extern const uint8_t MobilePacket_TransferData[];
extern const uint8_t MobilePacket_OpenTCPConnection[];
extern const uint8_t MobilePacket_CloseTCPConnection[];
extern const uint8_t Unknown_112089[];
extern const char Unknown_11209e[];
extern const char Unknown_1120a4[];
extern const char Unknown_1120b0[];
extern const char Unknown_1120ba[];
extern const char Unknown_1120c1[];
extern const char Unknown_1120c8[];
extern const char Unknown_1120ce[];
extern const char Unknown_1120d4[];
extern const char Unknown_1120db[];
extern const char Unknown_1120e8[];
extern const char Unknown_1120f5[];
extern const char Unknown_112102[];
extern const char Unknown_112110[];
extern const char Unknown_112115[];
extern const char Unknown_112121[];
extern const char Unknown_112132[];
extern const char Unknown_112137[];
extern const char Unknown_11213d[];
void Function11214e(void);
typedef void (*Jumptable_1121ac_t)(uint8_t*, uint8_t);
extern const Jumptable_1121ac_t Jumptable_1121ac[];
void Function1121f6(uint8_t* hl, uint8_t a);
void Function112251(void);
uint8_t* Function11225d(uint8_t a);
bool Function112269(void);
void Function112271(uint8_t* hl, uint8_t a);
void Function11234b(uint8_t b);
void Function11235a(void);
bool Function11236b(const uint8_t* hl);
void Function112373(uint8_t* hl, uint8_t a);
void Function1123b6(uint8_t* hl, uint8_t a);
void Function1123e1(void);
void Function112430(void);
void Function112451(void);
void Function112534(void);
void Function112566(void);
void Function112597(void);
void Function1125bf(void);
void Function1125c7(void);
void Function11261c(void);
void Function11264e(void);
void Function112654(void);
char* Function11269b(char* de, uint16_t* bc);
const char* Function1126ac(void);
char* Function1126b0(char* de, uint16_t* bc);
char* Function1126b6(char* de, uint16_t* bc);
char* Function1126e6(char* de, uint16_t* bc);
void Function112715(void);
void Function112724(void);
void Function112729(void);
void Function11273a(void);
void Function1127c5(const uint8_t* bytes);
void Function1127cd(void);
bool Function1127e1(void);
bool Function1127e7(char* hl);
bool Function1127f3(void);
void Function112807(void);
void Function112840(void);
void Function1128bd(void);
void Function1128d3(void);
void Function1128db(void);
void Function11295e(void);
void Function112969(void);
void Function11299c(void);
void Function112a2c(uint16_t de);
void Function112a42(void);
void Function112a56(void);
void Function112aac(void);
uint16_t Function112b11(const char* hl);
u8_flag_s Function112b60(char** de, const char** hl, uint8_t* b);
void Function112b71(void);
void Function112bbb(uint8_t* hl, uint8_t a);
void Function112bec(uint8_t* hl, uint8_t a);
void Function112d20(void);
void Function112d33(uint8_t* hl, uint8_t a);
uint8_t Function112f61(void);
char* Function112fd5(char* hl);
extern const char Unknown_113001[];
char* Function113008(char* hl);
char* Function113026(char* hl);
char* Function113054(char* hl);
void Function11306b(void);
void Function113072(char* hl, uint8_t b);
void Function113089(void);
void Function113095(char* hl, uint8_t b);
char* Function113167(char* hl);
char* Function113180(char* hl);
void Function113197(char* hl, uint8_t b);
void Function1131a9(void);
void Function113206(void);
void Function113245(uint8_t* de, const uint8_t* hl, uint8_t b, uint8_t e);
u8_flag_s Function113268(char** hl, uint8_t b);
bool Function113273(char** hl, const char* de);
bool Function113281(char** hl, const char* de);
uint8_t Function11329d(uint8_t a);
extern const char Unknown_1132a6[];
extern const char Unknown_1132b2[];
extern const char Unknown_1132bf[];
extern const char Unknown_1132dd[];
extern const char Unknown_1132ff[];
extern const char Unknown_11330c[];
void Function113317(void);
extern const char Unknown_113372[];
void Function113386(void);
char* Function1133de(char* de, uint16_t* bc);
void Function1133fe(void);
void Function113482(void);
void Function1134cb(uint8_t* hl, uint8_t a);
void Function113519(void);
void Function113592(char* de, uint8_t b);
char* Function11359d(char* de, uint16_t* bc);
char* Function1135ad(char* de, uint16_t* bc);
void Function1135ba(void);
void Function1135eb(void);
uint8_t Function113620(void);
uint8_t Function113623(void);
void Function113626(uint8_t* hl, uint8_t a);
void Function113672(void);
void Function1136c1(void);
void Function113909(void);
void Function11391e(void);
void Function11392f(void);
void Function113973(void);
void Function1139b7(void);
void Function1139de(void);
void Function113a0b(void);
void Function113a15(void);
void Function113a1f(void);
void Function113a28(void);
void Function113a32(void);
void Function113a40(void);
void Unknown_113a55(void);
void Unknown_113a70(void);
void Unknown_113b70(void);
void Unknown_113b7e(void);
void MD5_K_Table(void);
void Function113c8e(void);
void Function113d47(void);
void Function113d66(void);
void Function113e42(void);
void Function113eb8(void);
void Function113ec7(void);
void Function113ef2(void);
void Function113f2d(void);
//#include "macros/const.h"
//#include "constants/hardware_constants.h"
//#include "constants/mobile_constants.h"
