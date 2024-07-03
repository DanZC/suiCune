#pragma once

#define NETWORKING_SUPPORT

#define NETWORK_XCHG_ERROR_SEND -1
#define NETWORK_XCHG_ERROR_RECV -2
#define NETWORK_XCHG_TIMEOUT -3
#define NETWORK_XCHG_NO_CONNECTION -4
#define NETWORK_XCHG_OK 0

typedef struct {
    uint32_t address;
    uint32_t uid;
    uint8_t name[11];
    uint16_t trainerId;
    uint8_t gender;
} LANClient;

bool NetworkInit(void);
bool NetworkBroadcastLAN(const uint8_t* name, uint16_t id, uint8_t gender);
bool NetworkTryJoinLAN(uint8_t which, const uint8_t* name, uint16_t id, uint8_t gender);
bool NetworkCheckLAN(void);
void NetworkClearLANCache(void);
LANClient* NetworkGetLANCandidate(uint8_t which);
uint32_t NetworkGetLANCandidateCount(void);
bool NetworkLANDirectConnect(uint32_t which);
bool NetworkAcceptLANConnection(void);
void NetworkCloseConnection(void);
void NetworkStartJoining(void);
void NetworkDeinit(void);

int Network_ExchangeByte(uint8_t* rx, uint8_t tx);
int Network_ExchangeBytes(void* rx, const void* tx, int len);
bool Network_SafeExchangeBytes(void* rx, const void* tx, int len);
