void v_NamingScreen(uint8_t* de, uint8_t b);
void NamingScreen(uint8_t* de, uint8_t b);
bool NamingScreen_IsTargetBox(void);
void NamingScreen_InitText(void);
void NamingScreen_ApplyTextInputMode(const char* de);
bool NamingScreenJoypadLoop(void);
uint8_t NamingScreen_GetCursorPosition(struct SpriteAnim* bc);
void NamingScreen_AnimateCursor(struct SpriteAnim* bc);
bool NamingScreen_TryAddCharacter(void);
bool MailComposition_TryAddCharacter(void);
bool NamingScreen_LoadNextCharacter(uint8_t a);
bool NamingScreen_AdvanceCursor_CheckEndOfString(void);
void AddDakutenToCharacter(void);
void NamingScreen_DeleteCharacter(void);
uint8_t* NamingScreen_GetTextCursorPosition(void);
void NamingScreen_InitNameEntry(void);
void NamingScreen_StoreEntry(void);
void NamingScreen_GetLastCharacter(void);
void LoadNamingScreenGFX(void);
extern const char NamingScreenGFX_Border[];
extern const char NamingScreenGFX_Cursor[];
void NamingScreenGFX_End(void);
extern const char NamingScreenGFX_MiddleLine[];
extern const char NamingScreenGFX_UnderLine[];
void v_ComposeMailMessage(uint8_t* dest);
void ComposeMail_AnimateCursor(struct SpriteAnim* bc);
uint8_t NamingScreen_PressedA_GetCursorCommand(void);
uint8_t ComposeMail_GetCursorPosition(struct SpriteAnim* bc);
bool MailComposition_TryAddLastCharacter(void);
//#include "data/text/unused_dakutens.h"
//#include "gfx/naming_screen/border.2bpp"
//#include "gfx/naming_screen/cursor.2bpp"
//#include "data/text/name_input_chars.h"
//#include "gfx/naming_screen/end.1bpp"
//#include "gfx/naming_screen/middle_line.1bpp"
//#include "gfx/naming_screen/underline.1bpp"
//#include "gfx/icons/mail_big.2bpp"
//#include "data/text/mail_input_chars.h"
