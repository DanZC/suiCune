typedef void (*mobile_comm_fn_t)(void);
uint8_t Function100000(uint8_t d, uint8_t e, const mobile_comm_fn_t *bc);
void Function100022(uint8_t d, uint8_t e, const mobile_comm_fn_t* bc);
void Function100057(void);
void SetRAMStateForMobile(void);
void EnableMobile(void);
void DisableMobile(void);
void Function1000ba(void);
void Function1000e8(void);
void Function1000fa(void);
void Function100144(void);
void Function100163(void);
void Function10016f(void);
void Function10020b(void);
void Function100232(const char* de);
extern const char String10024d[];
extern const char String10025e[];
uint8_t Function100276(void);
void Function1002c9(void);
void Function1002dc(void);
void Function1002ed(void);
void Function100301(void);
void Function100320(void);
void Function100327(void);
u8_flag_s Function10032e(void);
u8_flag_s Function100337(void);
u8_flag_s Function10034d(void);
void Function100382(void);
uint8_t Function10038a(void);
void Function100393(void);
void Function10039c(void);
void Function1003ab(void);
void Function1003ba(void);
void Function1003c9(void);
void Function1003d8(void);
void Function1003f5(void);
bool Function100406(void);
uint16_t Function10043a(uint8_t* hl, uint16_t bc);
void Jumptable_10044e(void);
void Function10046a(void);
void Function10047c(void);
void Function100493(void);
void Function100495(void);
void asm_100497(void);
bool Function1004a4(void);
void Function1004ba(void);
void Function1004ce(void);
void Function1004de(void);
void Function1004e9(void);
void Function1004f4(void);
void Function100504(uint8_t* de);
void Function100513(void);
bool Function100522(void);
void Jumptable_10052a(void);
void Function100534(void);
void Function100545(void);
bool Function10054d(void);
void Function100579(void);
void Jumptable_100581(void);
void Function100585(void);
void Function100597(void);
extern const struct MenuHeader MenuHeader_1005b2;
extern const struct MenuData MenuData_1005ba;
void Function1005c3(void);
void Jumptable_1005cb(void);
void Function1005cf(void);
void Function1005e1(void);
extern const struct MenuHeader MenuHeader_1005fc;
extern const struct MenuData MenuData_100604;
void Mobile_CommunicationStandby(void);
bool AdvanceMobileInactivityTimerAndCheckExpired(uint8_t c, uint8_t b);
void StartMobileInactivityTimer(void);
void IncrementMobileInactivityTimerBy1Frame(void);
void IncrementMobileInactivityTimerByCFrames(uint8_t c);
void Function100665(void);
void Function100675(void);
void Function100681(void);
void Function100697(void);
extern const char String1006c2[];
extern const char String1006c6[];
extern const char String1006ca[];
void Function1006d3(void);
void Function1006dc(uint8_t* de, const uint8_t* hl);
void MobileBattleResetTimer(void);
void MobileBattleFixTimer(void);
void Function100720(void);
void Function100754(void);
void Function100772(void);
void Function10079c(void);
void Function1007f6(void);
void Function100826(void);
void Function100846(void);
extern const char String_10088e[];
extern const char String_10089f[];
u8_pair_s MobileBattleGetRemainingTime(void);
void Function1008e0(void);
void Function100902(void);
void Function100970(void);
void Function100989(void);
void Function1009a5(void);
void Function1009ae(void);
void Function1009d2(void);
void Function1009f3(void);
void v_LinkBattleSendReceiveAction(void);
void Function100acf(void);
void Function100ae7(void);
extern const char Unknown_100b0a[];
void Mobile_LoadBattleMenu(void);
void Function100b45(void);
void Function100b7a(void);
void Mobile_MoveSelectionScreen(void);
void Function100c98(void);
void Mobile_PartyMenuSelect(void);
void MobileBattleMonMenu(void);
void Function100d67(void);
void Function100da5(void);
bool Function100db0(void);
bool Function100dc0(void);
void Mobile_SetOverworldDelay(void);
void Function100dd8(void);
void MobileComms_CheckInactivityTimer(void);
void Function100e2d(void);
void Function100e63(uint8_t e);
void Function100e72(void);
void Function100e84(void);
void Jumptable_100e8c(void);
void Function100ea2(void);
void Function100eae(void);
void Function100eb4(void);
void asm_100eb8(void);
void Function100ec4(void);
void Function100ec5(void);
void Function100eca(void);
void Function100ed4(void);
void Function100edf(void);
void Function100ee6(void);
void Function100eed(void);
void Function100ef4(void);
void Function100efb(void);
void Function100f02(void);
void Function100f3d(void);
void Function100f8d(void);
void Unknown_100fc0(void);
void Unknown_100feb(void);
void Unknown_100ff3(void);
void Unknown_10102c(void);
void Function101050(void);
void Function10107d(void);
void Function1010de(void);
void LoadSelectedPartiesForColosseum(void);
void Function1011f1(void);
void Function101220(void);
void Function101225(void);
void Function101231(void);
void Function10123d(uint8_t c);
extern const mobile_comm_fn_t Jumptable_101247[];
void Function101251(void);
void Function101265(void);
void Function10126c(void);
void Function10127c(void);
void Function10127d(void);
void Function10127e(void);
extern const mobile_comm_fn_t Jumptable_101297[];
void Function10138b(void);
void Function1013aa(void);
void Function1013c0(void);
void Function1013d6(void);
void Function1013dd(void);
void Function1013e1(void);
void Function1013f5(void);
void Function101400(void);
void Function101406(void);
void asm_101416(void);
bool Function101418(void);
void Function10142c(uint8_t c);
void Function101438(void);
void Jumptable_101457(void);
void Function10145b(void);
void Function101467(void);
void Function101475(void);
void Jumptable_101494(void);
void Function10149a(void);
void Function1014a6(void);
void Function1014b7(void);
void Function1014ce(void);
void Function1014e2(void);
void Function1014f4(void);
void Function101507(void);
void Function10151d(void);
void Function10152a(void);
void Function101537(void);
void Function101544(void);
void Function101557(void);
void Function10156d(void);
void Function101571(void);
void Function10158a(void);
void Function10159d(void);
void Function1015be(void);
void Function1015df(void);
void Function101600(void);
void Function10161f(void);
void Function10162a(void);
void MobileCopyTransferData(const void* hl);
void MobileCopyTransferData2(void* hl);
void Function101649(void);
void Function10165a(void);
void Function101663(void);
void Function101674(void);
void Function10167d(void);
void Function10168a(void);
void Function10168e(void);
void Jumptable_1016c3(void);
void Function1016cf(void);
void Function1016de(void);
void Function1016f8(void);
void Function101705(void);
void Function101719(void);
void Function101724(void);
void Unknown_10173a(void);
void Function10173b(void);
void Function10174c(void);
void Function10176f(void);
void Function10177b(void);
void Function1017b0(void);
void Function1017c7(void);
void Function1017e4(void);
void Function1017f1(void);
void Function1017f5(void);
void Function101826(void);
void Unknown_10186f(void);
void Unknown_101882(void);
void Unknown_101895(void);
void Function1018a8(void);
void Function1018d6(void);
void Function1018e1(void);
void Function1018ec(void);
void Function1018fb(void);
void Function101913(void);
void Function10194b(void);
void v_SelectMonsForMobileBattle(void);
void v_StartMobileBattle(void);
void StartMobileBattle(void);
void Function101a4f(void);
void CopyOtherPlayersBattleMonSelection(void);
void Function101a97(void);
void Function101ab4(void);
void Function101ac6(void);
void Function101aed(void);
void Function101b0f(void);
void Function101b2b(void);
void Function101b59(void);
void Function101b70(void);
void Function101b8f(void);
void Function101bc8(void);
void Function101be5(void);
void Function101c11(void);
void Function101c2b(void);
void Function101c42(void);
void Function101c50(void);
void Function101c62(void);
void Function101c92(void);
void Function101ca0(void);
void Function101cbc(void);
void Function101cc2(void);
void Function101cc8(void);
void Function101cdf(void);
void Function101cf6(void);
void Function101d03(void);
void Function101d10(void);
void Function101d1e(void);
void Function101d2a(void);
void Jumptable_101d4d(void);
void Function101d51(void);
void Function101d5d(void);
void Function101d6b(void);
void Function101d7b(void);
void Unknown_101d8d(void);
void Function101d95(void);
void Function101db2(void);
void Function101dd0(void);
void Function101de3(void);
void Function101e09(void);
void Function101e31(void);
void Function101e39(void);
void Function101e4f(void);
void Function101e64(void);
void Function101e82(void);
void Function101e8d(void);
void Function101e98(void);
bool Function101ead(void);
void Function101ecc(void);
void Function101ed3(void);
void Function101ee2(void);
void Function101ee4(uint8_t e);
extern const char* const Unknown_101ef5[];
extern const char String_101f13[];
extern const char String_101f14[];
extern const char String_101f32[];
extern const char String_101f4f[];
extern const char String_101f69[];
extern const char String_101f81[];
extern const char String_101f93[];
extern const char String_101faa[];
extern const char String_101fc5[];
extern const char String_101fd2[];
extern const char String_101fe1[];
extern const char String_101fef[];
extern const char String_102000[];
extern const char String_10200c[];
extern const char String_102014[];
void Function10202c(void);
void Function102048(void);
void Function10204c(void);
void Function102068(const uint8_t* de);
bool Function102080(uint8_t a, uint8_t* hl);
void Function10208e(const void* de);
void Function10209c(void);
void Function1020a8(void);
void Function1020bf(void);
bool Function1020ea(void);
uint8_t Function102112(void);
void Function102142(void);
void Function102180(void);
void Function10218d(void);
void Function10219f(void);
void Function1021b8(void);
extern const txt_cmd_s NewCardArrivedText[];
extern const txt_cmd_s PutCardInCardFolderText[];
extern const txt_cmd_s CardWasListedText[];
void Function1021e0(const txt_cmd_s* txt);
void StartingLinkText(void);
extern const txt_cmd_s LinkTerminatedText[];
extern const txt_cmd_s ClosingLinkText[];
void Function1021f9(void);
void Function102233(void);
void Function102241(void);
void Function10224b(void);
void Function10226a(void);
void Function102274(void);
void Function102283(void);
void Function10228e(void);
void Function102298(void);
void Function1022ca(void);
void Function1022d0(void);
void Jumptable_1022f5(void);
void Function10234b(void);
void Function102361(void);
void Function10236e(void);
void Function102387(void);
void Function1023a1(void);
void Function1023b5(void);
void Function1023c6(void);
void Function102416(void);
void Function102423(void);
void Function10244b(void);
void Function10246a(void);
void Function102480(void);
void Function10248d(void);
void Function102496(void);
void Function1024a8(void);
void Function1024af(void);
void Jumptable_1024ba(void);
void Function1024c0(void);
void Function1024cb(void);
void Function1024de(void);
void Function1024f6(void);
void Function10250c(void);
void Function102591(void);
void Function1025b0(void);
void Function1025bd(void);
void Function1025c7(void);
void Function1025dc(void);
void Function1025e9(void);
void Function1025ff(void);
void Function102652(void);
void Function10266b(void);
void Function1026b7(void);
void Function1026c8(void);
void Jumptable_1026da(void);
void Function1026de(void);
void Function1026f3(void);
void Function102738(void);
void Function102754(void);
void Jumptable_102766(void);
void Function102770(void);
void Function102775(void);
void Function10278c(void);
void Function1027a0(void);
void Function1027b7(void);
void asm_1027c6(void);
void asm_1027d1(void);
void asm_1027e2(void);
void Function1027eb(void);
void Function102814(void);
void Function10283c(void);
void Function102862(void);
void Function10286f(void);
void Function1028a5(void);
void Function1028ab(void);
void Function1028bf(void);
void Function1028c6(void);
void Function1028d3(void);
void Function1028da(void);
void Function1028e8(void);
void Function1028fc(void);
void Jumptable_102917(void);
void Function102921(void);
void Jumptable_10292f(void);
void Function102933(void);
void Function10294f(void);
void Function10295d(void);
void Function10296e(void);
void Function102984(void);
void Function102996(void);
void Function10299e(void);
void Function1029af(void);
void MenuHeader_1029bb(void);
void Function1029c3(void);
void Jumptable_1029cb(void);
void Function1029cf(void);
void Function1029fe(void);
void String_102a26(void);
void MenuData3_102a33(void);
void Function102a3b(void);
void Function102b12(void);
void Function102b32(void);
void Function102b4e(void);
void Function102b68(void);
void MenuData_102b73(void);
void Function102b7b(void);
void MenuData_102b94(void);
void Function102b9c(void);
void Function102bac(void);
void Function102bdc(void);
void Function102c07(void);
void Function102c14(void);
void Function102c21(void);
void Function102c2e(void);
void Function102c3b(void);
void Function102c48(void);
void Function102c71(void);
void Function102c87(void);
void Function102cee(void);
void Function102d34(void);
void Function102d3e(void);
void Function102d48(void);
void Function102d9a(void);
void Function102db7(void);
void Function102dc3(void);
void Function102dd3(void);
void Function102dec(void);
void Function102e07(void);
void Function102e3e(void);
void Function102e4f(void);
void Function102ea8(void);
void TradingMonForOTMonText(void);
void Function102ee7(void);
extern const char String_102ef4[];
void Function102f15(void);
void Function102f32(void);
void Function102f50(void);
void Function102f6d(void);
void Function102f85(void);
void String_102fb2(void);
void String_102fcc(void);
void Function102fce(void);
extern const char String_102fdb[];
void Function102ff5(void);
void String_103002(void);
void Function103021(void);
void String_10302e(void);
void Function10304f(void);
void Function10305d(void);
void Function10306e(void);
void Function10307f(void);
void Function103094(void);
void Function1030cd(void);
void Unknown_103112(void);
void Unknown_10327a(void);
extern const char MobileTradeLightsGFX[];
void MobileTradeLightsPalettes(void);
void Function103302(void);
void Function103309(void);
void Function103362(void);
void Function10339a(void);
void Function1033af(void);
void Function10342c(void);
void Function10343c(void);
void Function103487(void);
void Function103490(void);
void Function1034a7(void);
void Function1034be(void);
void Function1034e0(void);
void Function1034f1(void);
void Function1034f7(void);
void Function10350f(void);
// void Unknown_103522(void);
extern const char String_103545[];
extern const char String_103546[];
extern const char String_10354f[];
extern const char String_103557[];
extern const char String_10355f[];
extern const char String_103571[];
extern const char String_103585[];
extern const char String_103598[];
extern const char String_1035a0[];
extern const char String_1035a8[];
extern const char String_1035b1[];
extern const char String_1035ba[];
extern const char String_1035bd[];
extern const char String_1035c1[];
void Function1035c6(void);
void Unknown_1035d7(void);
void Unknown_1035e7(void);
void Unknown_1035f3(void);
void Unknown_1035fe(void);
void Unknown_103608(void);
void AskMobileOrCable(void);
extern const struct MenuHeader MenuHeader_103640;
extern const struct MenuData MenuData_103648;
uint8_t Function103654(void);
void Mobile_SelectThreeMons(void);
void Function1036f9(void);
bool Function103700(void);
extern const struct MenuHeader MenuHeader_103747;
extern const struct MenuData MenuData_10374f;
extern const txt_cmd_s MobileBattleMustPickThreeMonText[];
extern const txt_cmd_s MobileBattleMoreInfoText[];
extern const txt_cmd_s MobileBattleRulesText[];
extern const txt_cmd_s WouldYouLikeToMobileBattleText[];
extern const txt_cmd_s WantAQuickMobileBattleText[];
extern const txt_cmd_s WantToRushThroughAMobileBattleText[];
extern const txt_cmd_s PleaseTryAgainTomorrowText[];
void Function103780(void);
void Function10378c(void);
void Function1037c2(void);
extern const txt_cmd_s TryAgainUsingSameSettingsText[];
void Function1037eb(void);
extern const txt_cmd_s MobileBattleLessThanOneMinuteLeftText[];
extern const txt_cmd_s MobileBattleNoTimeLeftForLinkingText[];
bool MobileCheckRemainingBattleTime(void);
void Function10383c(void);
extern const txt_cmd_s PickThreeMonForMobileBattleText[];
void Function10387b(void);
extern const txt_cmd_s MobileBattleRemainingTimeText[];
//#include "gfx/mobile/mobile_trade_lights.2bpp"
//#include "gfx/mobile/mobile_trade_lights.pal"
