typedef struct ErrCode {
    uint16_t code;
    const char* text;
} errcode_s;
typedef struct ErrCodes {
    uint8_t count;
    errcode_s codes[];
} errcodes_s;
void Function17c000(void);
extern const char HaveWantGFX[];
extern const char MobileSelectGFX[];
extern const char HaveWantMap[];
extern const uint16_t HaveWantPals[];
void CheckStringForErrors(void);
bool CheckStringForErrors_Conv(const uint8_t* de, uint8_t c);
void CheckStringForErrors_IgnoreTerminator(void);
bool CheckStringForErrors_IgnoreTerminator_Conv(const uint8_t* de, uint8_t c);
void Function17d0f3(void);
void Mobile_CopyDefaultOTName(void);
extern const char Mobile5F_PlayersName[];
void Mobile_CopyDefaultNickname(void);
void Mobile_CopyDefaultMail(void);
void Mobile_CopyDefaultMailAuthor(void);
void CheckStringContainsLessThanBNextCharacters(void);
u8_flag_s CheckStringContainsLessThanBNextCharacters_Conv(const uint8_t* de, uint8_t b, uint8_t c);
void Function17d1f1(void);
void Menu_ChallengeExplanationCancel(void);
bool Call_05f_5261(void);
void Function17d246(void);
extern const struct MenuHeader MenuHeader_17d26a;
extern const struct MenuData MenuData_17d272;
extern const struct MenuHeader MenuHeader_ChallengeExplanationCancel;
extern const struct MenuData MenuData_ChallengeExplanationCancel;
extern const struct MenuHeader MenuHeader_ChallengeRegisterExplanationCancel;
extern const struct MenuData MenuData_ChallengeRegisterExplanationCancel;
void Function17d2b6(void);
void Function17d2c0(void);
void Function17d2ce(void);
bool Function17d314(void);
void Function17d370(void);
void Function17d3f6(void);
void Function17d405(void);
void Function17d45a(void);
void Function17d474(void);
void Jumptable_17d483(void);
void Function17d48d(void);
void Function17d5be(void);
void Function17d5c4(void);
void Function17d5f6(void);
void Function17d60b(void);
void Function17d6a1(void);
void Function17d6fd(void);
void Function17d711(uint8_t a);
void asm_17d721(void);
// void Jumptable17d72a(void);
void Function17d78c(void);
void Function17d78d(void);
void Function17d7b4(void);
void Function17d7c2(void);
void Function17d7d3(void);
void Function17d7e5(void);
void Function17d818(void);
void Function17d833(void);
void Function17d85d(void);
void Function17d902(void);
void Function17d93a(void);
void Function17d98b(void);
void Function17d9e3(void);
void Function17da31(void);
extern const uint8_t Unknown_17da8c[];
extern const uint8_t Unknown_17da94[];
void Function17da9c(void);
void Function17dadc(void);
void Function17db2d(void);
void Function17db56(void);
void Function17db77(void);
void Function17dbb1(void);
void Function17dbe9(void);
void Function17dc1f(void);
void MenuData_17dc96(void);
void Function17dc9f(void);
void Function17dca9(void);
void Function17dcaf(void);
void Function17dccf(void);
void Function17dd13(void);
void Function17dd30(void);
void Function17dd49(void);
void Function17ddcd(void);
void Function17de32(void);
void Function17de91(void);
void Function17ded9(void);
void Function17e026(void);
void asm_17e0ee(void);
void Function17e0fd(void);
void Function17e133(void);
void Function17e165(void);
void Function17e1a1(void);
void Function17e254(void);
void Function17e261(void);
void Function17e270(void);
void Function17e27f(void);
void Function17e293(void);
void Function17e2a7(void);
void Function17e309(void);
void Function17e32b(void);
void Function17e349(void);
void IncCrashCheckPointer_SaveGameData(void);
void IncCrashCheckPointer_SaveAfterLinkTrade(void);
void IncCrashCheckPointer_SaveBox(void);
void IncCrashCheckPointer_SaveChecksum(void);
void IncCrashCheckPointer_SaveTrainerRankingsChecksum(void);
void Function17e3e0(void);
void Function17e3f0(void);
void Function17e409(void);
void Function17e40f(uint16_t);
uint8_t* IncCrashCheckPointer(void);
uint8_t* HlToCrashCheckPointer(uint8_t* hl);
void Function17e427(void);
void Function17e438(void);
uint8_t* Function17e43d(uint16_t bc);
uint8_t* Function17e447(uint16_t de);
void Function17e451(void);
void Function17e4dd(void);
void Function17e51b(void);
void Function17e55b(void);
void Function17e566(void);
void Function17e571(uint8_t);
void Function17e5af(void);
uint8_t *Function17e600(uint8_t *hl, uint16_t bc, uint8_t a);
void Function17e613(const uint8_t *de);
void Function17e691(const uint8_t *de);
void Function17e6de(uint8_t a);
extern const char PokemonNewsGFX[];
extern const char PostalMarkGFX[];
extern const char PokemonNewsTileAttrmap[];
extern const char PokemonNewsPalettes[];
void RunMobileScript(struct TextPrintState* state);
bool v_RunMobileScript(struct TextPrintState* state);
bool Function17f081(struct TextPrintState* state, uint8_t* saved);
bool Function17f0f8(struct TextPrintState* state, uint8_t* saved);
bool Function17f154(struct TextPrintState* state, uint8_t* saved);
bool Function17f181(struct TextPrintState* state, uint8_t* saved);
void Function17f1d0(void);
bool Function17f220(struct TextPrintState* state, uint8_t* saved);
void Function17f27b(void);
bool Function17f2cb(struct TextPrintState* state, uint8_t* saved);
bool MobileScript_PlayerName(struct TextPrintState* state, uint8_t* saved);
bool MobileScript_Prefecture(struct TextPrintState* state, uint8_t* saved);
bool Function17f382(struct TextPrintState* state, uint8_t* saved);
bool Function17f3c9(struct TextPrintState* state, uint8_t* saved);
bool Function17f3f0(struct TextPrintState* state, uint8_t* saved);
void Function17f41d(void);
bool Function17f44f(struct TextPrintState* state, uint8_t* saved);
uint16_t Function17f4f6(void);
void Function17f50f(struct TextPrintState* state, uint8_t a);
bool Function17f524(void);
void BattleTowerMobileError(void);
void DisplayMobileError(void);
void Function17f5c3(void);
void Function17f5d2(void);
void Function17f5e4(void);
extern const char* const Table_17f699[];
void Palette_17f6af(void);
void Function17f6b7(tile_t* hl);
extern const char MobileCommunicationErrorText[];
void String_17f6e8(void);
extern const errcodes_s* MobileErrorCodeTable[];
extern const errcodes_s MobileErrorCodes_10;
extern const errcodes_s MobileErrorCodes_11;
extern const errcodes_s MobileErrorCodes_12;
extern const errcodes_s MobileErrorCodes_13;
extern const errcodes_s MobileErrorCodes_14;
extern const errcodes_s MobileErrorCodes_15;
extern const errcodes_s MobileErrorCodes_16;
extern const errcodes_s MobileErrorCodes_17;
extern const errcodes_s MobileErrorCodes_20;
extern const errcodes_s MobileErrorCodes_21;
extern const errcodes_s MobileErrorCodes_22;
extern const errcodes_s MobileErrorCodes_23;
extern const errcodes_s MobileErrorCodes_24;
extern const errcodes_s MobileErrorCodes_25;
extern const errcodes_s MobileErrorCodes_26;
extern const errcodes_s MobileErrorCodes_30;
extern const errcodes_s MobileErrorCodes_31;
extern const errcodes_s MobileErrorCodes_32;
extern const errcodes_s MobileErrorCodes_33;
extern const char MobileErrorCode_10_000_Text[];
#define MobileErrorCode_11_000_Text MobileErrorCode_13_000_Text
extern const char MobileErrorCode_13_000_Text[];
extern const char MobileErrorCode_12_000_Text[];
#define MobileErrorCode_15_000_Text MobileErrorCode_15_003_Text
#define MobileErrorCode_15_001_Text MobileErrorCode_15_003_Text
#define MobileErrorCode_15_002_Text MobileErrorCode_15_003_Text
extern const char MobileErrorCode_15_003_Text[];
extern const char MobileErrorCode_CommuncationErrorText[];
extern const char MobileErrorCode_22_000_Text[];
extern const char MobileErrorCode_23_000_Text[];
extern const char MobileErrorCode_ServerErrorText[];
#define MobileErrorCode_14_000_Text MobileErrorCode_25_000_Text
extern const char MobileErrorCode_25_000_Text[];
extern const char MobileErrorCode_32_503_Text[];
#define MobileErrorCode_30_450_Text MobileErrorCode_30_553_Text
#define MobileErrorCode_30_550_Text MobileErrorCode_30_553_Text
#define MobileErrorCode_30_551_Text MobileErrorCode_30_553_Text
extern const char MobileErrorCode_30_553_Text[];
extern const char MobileErrorCode_31_002_Text[];
#define MobileErrorCode_31_003_Text MobileErrorCode_33_201_Text
extern const char MobileErrorCode_33_201_Text[];
extern const char MobileErrorCode_ReadDataErrorText[];
#define MobileErrorCode_26_000_Text MobileErrorCode_32_408_Text
extern const char MobileErrorCode_32_408_Text[];
extern const char MobileErrorCode_33_101_Text[];
#define MobileErrorCode_33_102_Text MobileErrorCode_33_299_Text
extern const char MobileErrorCode_33_299_Text[];
extern const char MobileErrorCode_ServerConnectionFailedText[];
extern const char MobileErrorCode_33_103_Text[];
extern const char MobileErrorCode_33_106_Text[];
#define MobileErrorCode_33_104_Text MobileErrorCode_101_004_Text
#define MobileErrorCode_33_105_Text MobileErrorCode_101_004_Text
#define MobileErrorCode_33_203_Text MobileErrorCode_101_004_Text
#define MobileErrorCode_33_206_Text MobileErrorCode_101_004_Text
extern const char MobileErrorCode_101_004_Text[];
extern const char MobileErrorCode_101_006_Text[];
#define MobileErrorCode_101_001_Text MobileErrorCode_101_002_Text
extern const char MobileErrorCode_101_002_Text[];
#define MobileErrorCode_101_003_Text MobileErrorCode_101_009_Text
#define MobileErrorCode_101_008_Text MobileErrorCode_101_009_Text
extern const char MobileErrorCode_101_009_Text[];
extern const char MobileErrorCode_101_007_Text[];
extern const char MobileErrorCode_101_005_Text[];
void String_17fe9a(void);
extern const char MobileErrorCode_101_000_Text[];
void Function17ff23(void);
bool Function17ff3c(void);
extern const char String_17ff68[];
//#include "gfx/mobile/havewant.2bpp"
//#include "gfx/mobile/select.2bpp"
//#include "gfx/mobile/havewant_map.bin"
//#include "gfx/mobile/pokemon_news.2bpp"
//#include "gfx/font/postal_mark.2bpp"
//#include "gfx/mobile/pokemon_news.bin"
//#include "gfx/mobile/pokemon_news.pal"
