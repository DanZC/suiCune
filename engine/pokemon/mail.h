bool SendMailToPC(uint8_t b);
void DeleteMailFromPC(uint8_t b);
void ReadMailMessage(uint8_t b);
void MoveMailFromPCToParty(uint8_t b);
uint8_t GetMailboxCount(void);
void CheckPokeMail(void);
void CheckPokeMail_Conv(const char* message);
void GivePokeMail(void);
void GivePokeMail_Conv(const struct Pokemail* mail);
void BackupPartyMonMail(void);
void RestorePartyMonMail(void);
void DeletePartyMonMail(void);
void IsAnyMonHoldingMail(void);
bool IsAnyMonHoldingMail_Conv(void);
void v_PlayerMailBoxMenu(void);
void InitMail(void);
bool InitMail_Conv(void);
uint8_t* MailboxPC_GetMailAuthor(uint8_t a);
void MailboxPC_PrintMailAuthor(const struct MenuData* data, tile_t* tile);
void MailboxPC(void);
