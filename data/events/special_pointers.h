#pragma once

#define special_const(_n) SP_##_n

enum {
    special_const(WarpToSpawnPoint),
// Communications
    special_const(SetBitsForLinkTradeRequest),
    special_const(WaitForLinkedFriend),
    special_const(CheckLinkTimeout_Receptionist),
    special_const(TryQuickSave),
    special_const(CheckBothSelectedSameRoom),
    special_const(FailedLinkToPast),
    special_const(CloseLink),
    special_const(WaitForOtherPlayerToExit),
    special_const(SetBitsForBattleRequest),
    special_const(SetBitsForTimeCapsuleRequest),
    special_const(CheckTimeCapsuleCompatibility),
    special_const(EnterTimeCapsule),
    special_const(TradeCenter),
    special_const(Colosseum),
    special_const(TimeCapsule),
    special_const(CableClubCheckWhichChris),
    special_const(CheckMysteryGift),
    special_const(GetMysteryGiftItem),
    special_const(UnlockMysteryGift),
};

extern void (*const SpecialsPointers[])(void);