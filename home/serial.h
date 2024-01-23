void Serial(void);
void Serial_ExchangeBytes(void);
uint8_t* Serial_ExchangeBytes_Conv(void* de_, const void* hl_, uint16_t bc);
void Serial_ExchangeByte(void);
uint8_t Serial_ExchangeByte_Conv(const uint8_t* hl);
void CheckLinkTimeoutFramesNonzero(void);
bool CheckLinkTimeoutFramesNonzero_Conv(void);
void SerialDisconnected(void);
uint8_t SerialDisconnected_Conv(uint8_t a);
void Serial_ExchangeSyncBytes(void);
void Serial_PrintWaitingTextAndSyncAndExchangeNybble(void);
void Serial_SyncAndExchangeNybble(void);
void WaitLinkTransfer(void);
void LinkTransfer(void);
void LinkDataReceived(void);
void SetBitsForTimeCapsuleRequestIfNotLinked(void);
