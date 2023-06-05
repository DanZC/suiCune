#pragma once
#include "constants.h"

#if defined(__cplusplus) || defined(_MSC_VER)
#pragma pack(push, 1)
#endif

#if defined(__cplusplus) || defined(_MSC_VER)
struct hram_s
#else
// A struct representing HRAM.
struct __attribute__((packed)) hram_s
#endif
{
    uint8_t padding[hROMBankBackup - 0xff80];
    // 0
    uint8_t hROMBankBackup;
    // 1
    union {
        uint8_t hFarByte;
        uint8_t hTempBank;
    };
    // 2
    uint8_t hSRAMBank;
    // 3
    uint8_t hRTCDayHi;
    // 4
    uint8_t hRTCDayLo;
    // 5
    uint8_t hRTCHours;
    // 6
    uint8_t hRTCMinutes;
    // 7
    uint8_t hRTCSeconds;
    // 8
    uint16_t unused_8;
    // 10
    uint8_t hHours;
    // 11
    uint8_t unused_11;
    // 12
    uint8_t hMinutes;
    // 13
    uint8_t unused_13;
    // 14
    uint8_t hSeconds;
    // 15
    uint8_t unused_15;
    // 16
    uint8_t unused_16;
    // 17
    uint8_t hVBlankCounter;
    // 18
    uint8_t unused_18;
    // 19
    uint8_t hROMBank;
    // 20
    uint8_t hVBlank;
    // 21
    uint8_t hMapEntryMethod;
    // 22
    uint8_t hMenuReturn;
    // 23
    uint8_t hUnusedByte;
    // 24
    uint8_t hJoypadReleased;
    // 25
    uint8_t hJoypadPressed;
    // 26
    uint8_t hJoypadDown;
    // 27
    uint8_t hJoypadSum;
    // 28
    uint8_t hJoyReleased;
    // 29
    uint8_t hJoyPressed;
    // 30
    uint8_t hJoyDown;
    // 31
    uint8_t hJoyLast;
    // 32
    uint8_t hInMenu;
    // 33
    uint8_t unused_33;
    // 34
    uint8_t hPrinter;
    // 35
    uint8_t hGraphicStartTile;
    // 36
    uint8_t hMoveMon;
#if defined(__cplusplus) || defined(_MSC_VER)
    // 37
    union {
        struct {
            // 37
            uint8_t hMapObjectIndex;
            // 38
            uint8_t hObjectStructIndex;
        };
        struct  {
            // 37
            uint8_t hConnectionStripLength;
            // 38
            uint8_t hConnectedMapWidth;
        };
    };
#else
    // 37
    union {
        struct __attribute__((packed)) {
            // 37
            uint8_t hMapObjectIndex;
            // 38
            uint8_t hObjectStructIndex;
        };
        struct __attribute__((packed)) {
            // 37
            uint8_t hConnectionStripLength;
            // 38
            uint8_t hConnectedMapWidth;
        };
    };
#endif
    // 39
    uint16_t hEnemyMonSpeed;
#if defined(__cplusplus) || defined(_MSC_VER)
    // 41
    union {
        struct {
            // 41
            union {
                struct {
                    // 41
                    uint8_t unused_41;
                    // 42
                    uint8_t hMultiplicand[3];
                    // 45
                    uint8_t hMultiplier;
                };
                struct {
                    // 41
                    uint32_t hProduct;
                };
                struct {
                    // 41
                    uint32_t hDividend;
                    // 45
                    uint8_t hDivisor;
                };
                struct {
                    // 41
                    uint32_t hQuotient;
                    // 45
                    uint8_t hRemainder;
                };
            };
            // 46
            uint8_t hMathBuffer[5];
        };
        struct {
            // 41
            uint8_t hPrintNumBuffer[10];
        };
        struct {
            // 41
            uint8_t hMGExchangedByte;
            // 42
            uint16_t hMGExchangedWord;
            // 44
            uint8_t hMGNumBits;
            // 45
            uint16_t hMGChecksum;
            // 47
            uint8_t unused_47;
            // 48
            uint8_t hMGUnusedMsgLength;
            // 49
            uint8_t hMGRole;
            // 50
            uint8_t hMGStatusFlags;
        };
    };
    // 51
    union {
        struct {
            // 51
            uint8_t hUsedSpriteIndex;
            // 52
            uint8_t hUsedSpriteTile;
        };
        struct {
            // 51
            uint8_t hCurSpriteXCoord;
            // 52
            uint8_t hCurSpriteYCoord;
            // 53
            uint8_t hCurSpriteXPixel;
            // 54
            uint8_t hCurSpriteYPixel;
            // 55
            uint8_t hCurSpriteTile;
            // 56
            uint8_t hCurSpriteOAMFlags;
        };
    };
    // 57
    union {
        struct {
            // 57
            uint8_t hMoneyTemp[3];
        };
        struct {
            // 57
            uint8_t hMGJoypadPressed;
            // 58
            uint8_t hMGJoypadReleased;
            // 59
            uint8_t hMGPrevTIMA;
        };
    };
#else
    // 41
    union {
        struct __attribute__((packed)) {
            // 41
            union {
                struct __attribute__((packed)) {
                    // 41
                    uint8_t unused_41;
                    // 42
                    uint8_t hMultiplicand[3];
                    // 45
                    uint8_t hMultiplier;
                };
                struct __attribute__((packed)) {
                    // 41
                    uint32_t hProduct;
                };
                struct __attribute__((packed)) {
                    // 41
                    uint32_t hDividend;
                    // 45
                    uint8_t hDivisor;
                };
                struct __attribute__((packed)) {
                    // 41
                    uint32_t hQuotient;
                    // 45
                    uint8_t hRemainder;
                };
            };
            // 46
            uint8_t hMathBuffer[5];
        };
        struct __attribute__((packed)) {
            // 41
            uint8_t hPrintNumBuffer[10];
        };
        struct __attribute__((packed)) {
            // 41
            uint8_t hMGExchangedByte;
            // 42
            uint16_t hMGExchangedWord;
            // 44
            uint8_t hMGNumBits;
            // 45
            uint16_t hMGChecksum;
            // 47
            uint8_t unused_47;
            // 48
            uint8_t hMGUnusedMsgLength;
            // 49
            uint8_t hMGRole;
            // 50
            uint8_t hMGStatusFlags;
        };
    };
    // 51
    union {
        struct __attribute__((packed)) {
            // 51
            uint8_t hUsedSpriteIndex;
            // 52
            uint8_t hUsedSpriteTile;
        };
        struct __attribute__((packed)) {
            // 51
            uint8_t hCurSpriteXCoord;
            // 52
            uint8_t hCurSpriteYCoord;
            // 53
            uint8_t hCurSpriteXPixel;
            // 54
            uint8_t hCurSpriteYPixel;
            // 55
            uint8_t hCurSpriteTile;
            // 56
            uint8_t hCurSpriteOAMFlags;
        };
    };
    // 57
    union {
        struct __attribute__((packed)) {
            // 57
            uint8_t hMoneyTemp[3];
        };
        struct __attribute__((packed)) {
            // 57
            uint8_t hMGJoypadPressed;
            // 58
            uint8_t hMGJoypadReleased;
            // 59
            uint8_t hMGPrevTIMA;
        };
    };
#endif
    // 60
    uint8_t hLCDCPointer;
    // 61
    uint8_t hLYOverrideStart;
    // 62
    uint8_t hLYOverrideEnd;
    // 63
    uint8_t hMobileReceive;
    // 64
    uint8_t hSerialReceivedNewData;
    // 65
    uint8_t hSerialConnectionStatus;
    // 66
    uint8_t hSerialIgnoringInitialData;
    // 67
    uint8_t hSerialSend;
    // 68
    uint8_t hSerialReceive;
    // 69
    uint8_t hSCX;
    // 70
    uint8_t hSCY;
    // 71
    uint8_t hWX;
    // 72
    uint8_t hWY;
    // 73
    uint8_t hTilesPerCycle;
    // 74
    uint8_t hBGMapMode;
    // 75
    uint8_t hBGMapThird;
    // 76
    uint16_t hBGMapAddress;
    // 78
    uint8_t hOAMUpdate;
    // 79
    uint16_t hSPBuffer;
    // 81
    uint8_t hBGMapUpdate;
    // 82
    uint8_t hBGMapTileCount;
    // 83
    uint8_t unused_83;
    // 84
    uint8_t hMapAnims;
    // 85
    uint8_t hTileAnimFrame;
    // 86
    uint8_t hLastTalked;
    // 87
    uint8_t hRandomAdd;
    // 88
    uint8_t hRandomSub;
    // 89
    uint8_t hUnusedBackup;
    // 90
    uint8_t hBattleTurn;
    // 91
    uint8_t hCGBPalUpdate;
    // 92
    uint8_t hCGB;
    // 93
    uint8_t hSGB;
    // 94
    uint8_t hDMATransfer;
    // 95
    uint8_t hMobile;
    // 96
    uint8_t hSystemBooted;
    // 97
    uint8_t hClockResetTrigger;
    // 98
    uint8_t unused_98[19];
};

#if defined(__cplusplus) || defined(_MSC_VER)
#pragma pack(pop)
#endif

extern struct hram_s* hram;

#define _s_impl(_x) #_x
#define _s(_x) _s_impl(_x)

#define CHECK_HRAM_FLD(_fld) do {\
        if((uint8_t*)&hram->_fld != &gb.hram[_fld - HRAM_Begin]) {\
            printf("Bad casted field %s ptr %p != %p\n", _s(_fld), (uint8_t*)&hram->_fld, &gb.hram[_fld - HRAM_Begin]);\
        }\
    } while(0)
