#pragma once

#define NETWORKING_SUPPORT

bool NetworkInit(void);
void NetworkBroadcastLAN(const uint8_t* name, uint16_t id, uint8_t gender);
bool NetworkCheckLAN(void);
void NetworkDeinit(void);

typedef struct {
    uint32_t address;
    uint8_t name[11];
    uint16_t trainerId;
    uint8_t gender;
} LANClient;

extern LANClient gLANClientCandidates[16];
extern uint32_t gLANClientCandidateCount;
