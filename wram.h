#pragma once
#include "constants.h"

#pragma pack(push, 1)

// A struct representing WRAM.
struct wram_s
{
    // bank 0
    union {
        uint8_t wram0[0x1000];
        struct {
            // Stack
            struct {
                // WRAM0
                uint8_t wStackBottom[0x100 - 1];
                uint8_t wStackTop[1];
            };
            // Audio RAM
            struct {
                // WRAM0
                // nonzero if playing
                uint8_t wMusicPlaying;
                // wChannel1 - wChannel8
                //union wAudio
                // for n, 1, NUM_CHANNELS + 1
                // wChannel1 - wChannel8
                struct Channel_ wChannel[(NUM_CHANNELS + 1) - 1];
                uint8_t skip_0[1];
                uint8_t wCurTrackDuty;
                uint8_t wCurTrackVolumeEnvelope;
                uint16_t wCurTrackFrequency;
                uint8_t wUnusedBCDNumber;
                // BCD value, dummied out
                uint8_t wCurNoteDuration;
                // used in MusicE0 and LoadNote
                uint8_t wCurMusicByte;
                uint8_t wCurChannel;
                // corresponds to rNR50
                // Channel control / ON-OFF / Volume (R/W)
                //   bit 7 - Vin->SO2 ON/OFF
                //   bit 6-4 - SO2 output level (volume) (# 0-7)
                //   bit 3 - Vin->SO1 ON/OFF
                //   bit 2-0 - SO1 output level (volume) (# 0-7)
                uint8_t wVolume;
                // corresponds to rNR51
                // bit 4-7: ch1-4 so2 on/off
                // bit 0-3: ch1-4 so1 on/off
                uint8_t wSoundOutput;
                // corresponds to rNR10
                // bit 7:   unused
                // bit 4-6: sweep time
                // bit 3:   sweep direction
                // but 0-2: sweep shift
                uint8_t wPitchSweep;
                uint16_t wMusicID;
                uint8_t wMusicBank;
                uint16_t wNoiseSampleAddress;
                uint8_t wNoiseSampleDelay;
                uint8_t skip_1[1];
                uint8_t wMusicNoiseSampleSet;
                uint8_t wSFXNoiseSampleSet;
                // bit 7: on/off
                // bit 4: pitch
                // bit 0-3: counter
                uint8_t wLowHealthAlarm;
                // fades volume over x frames
                // bit 7: fade in/out
                // bit 0-5: number of frames for each volume level
                // $00 = none (default)
                uint8_t wMusicFade;
                uint8_t wMusicFadeCount;
                uint16_t wMusicFadeID;
                uint8_t skip_2[5];
                uint16_t wCryPitch;
                uint16_t wCryLength;
                uint8_t wLastVolume;
                uint8_t wUnusedMusicF9Flag;
                // if nonzero, turn off music when playing sfx
                uint8_t wSFXPriority;
                uint8_t skip_3[1];
                uint8_t wChannel1JumpCondition;
                uint8_t wChannel2JumpCondition;
                uint8_t wChannel3JumpCondition;
                uint8_t wChannel4JumpCondition;
                uint8_t wStereoPanningMask;
                // plays only in left or right track depending on what side the monster is on
                // both tracks active outside of battle
                uint8_t wCryTracks;
                uint8_t wSFXDuration;
                // id of sfx currently playing
                uint8_t wCurSFX;
                //union wAudioEnd
                uint8_t wMapMusic;
                uint8_t wDontPlayMapMusicOnReload;
            };
            // WRAM
            struct {
                // WRAM0
                uint16_t wLZAddress; // unused
                uint8_t wLZBank; // unused
                uint8_t skip_4[1];
                uint8_t wBoxAlignment;
                uint8_t wInputType;
                uint16_t wAutoInputAddress;
                uint8_t wAutoInputBank;
                uint8_t wAutoInputLength;
                uint8_t wDebugFlags;
                uint8_t wGameLogicPaused;
                uint8_t wSpriteUpdatesEnabled;
                uint8_t wUnusedScriptByte;
                uint8_t wMapTimeOfDay;
                uint8_t skip_5[3];
                uint8_t wPrinterConnectionOpen;
                uint8_t wPrinterOpcode;
                uint8_t wPrevDexEntry;
                uint8_t wDisableTextAcceleration;
                uint8_t wPrevLandmark;
                uint8_t wCurLandmark;
                uint16_t wLandmarkSignTimer;
                // a LINK_* value for the link type
                uint8_t wLinkMode;
                uint8_t wScriptVar;
                uint8_t wPlayerNextMovement;
                uint8_t wPlayerMovement;
                uint8_t skip_6[2];
                uint8_t wMovementObject;
                uint8_t wMovementDataBank;
                uint16_t wMovementDataAddress;
                uint16_t wIndexedMovement2Pointer;
                uint8_t skip_7[2];
                uint8_t wMovementByteWasControlSwitch;
                union {
                    struct {
                        uint8_t wObjectPriorities[NUM_OBJECT_STRUCTS];
                    };
                    struct {
                        uint16_t wMovementPointer;
                        uint8_t skip_8[3];
                        uint8_t wTempObjectCopyMapObjectIndex;
                        uint8_t wTempObjectCopySprite;
                        uint8_t wTempObjectCopySpriteVTile;
                        uint8_t wTempObjectCopyPalette;
                        uint8_t wTempObjectCopyMovement;
                        uint8_t wTempObjectCopyRange;
                        uint8_t wTempObjectCopyX;
                        uint8_t wTempObjectCopyY;
                        uint8_t wTempObjectCopyRadius;
                    };
                };
                uint8_t skip_9[1];
                uint8_t wTileDown;
                uint8_t wTileUp;
                uint8_t wTileLeft;
                uint8_t wTileRight;
                // set if tile behavior prevents
                // you from walking in that direction
                // bit 3: down
                // bit 2: up
                // bit 1: left
                // bit 0: right
                uint8_t wTilePermissions;
            };
            uint8_t section_pad_0[1]; // Padding for WRAM
            // wSpriteAnims
            struct {
                // WRAM0
                union {
                    struct {
                        //union wSpriteAnimData
                        // wSpriteAnimDict pairs keys with values
                        // keys: SPRITE_ANIM_DICT_* indexes (taken from SpriteAnimSeqData)
                        // values: vTiles0 offsets
                        uint8_t wSpriteAnimDict[NUM_SPRITEANIMDICT_ENTRIES * 2];
                        // wSpriteAnim1 - wSpriteAnim10
                        //union wSpriteAnimationStructs
                        // for n, 1, NUM_SPRITE_ANIM_STRUCTS + 1
                        // field  0:   index
                        // fields 1-3: loaded from SpriteAnimSeqData
                        // wSpriteAnim1 - wSpriteAnim10
                        struct SpriteAnim wSpriteAnim[(NUM_SPRITE_ANIM_STRUCTS + 1) - 1];
                        //void wSpriteAnimationStructsEnd
                    };
                    struct {
                        // mobile data
                        //union wMobileWRAM
                        uint8_t wMobileErrorCodeBuffer[3];
                        uint8_t wc303[2];
                        uint8_t wc305;
                        uint8_t wc306;
                        uint8_t wc307;
                        uint8_t wc308;
                        uint8_t wc309;
                        uint8_t wc30a;
                        uint8_t wc30b;
                        uint8_t wc30c;
                        uint8_t wc30d;
                        uint8_t wc30e;
                        uint8_t wc30f;
                        uint8_t wc310;
                        uint8_t wc311;
                        uint8_t wc312;
                        uint8_t wc313;
                        uint8_t wc314[5];
                        uint8_t wc319;
                        uint8_t wc31a;
                        uint8_t wc31b;
                        uint8_t wc31c;
                        uint8_t wc31d;
                        uint8_t wc31e;
                        uint8_t wc31f;
                        uint8_t wc320[38];
                        uint8_t wc346[102];
                        uint8_t wc3ac[8];
                    };
                };
                uint8_t wSpriteAnimCount;
                uint8_t wCurSpriteOAMAddr;
                uint8_t wCurIcon;
                uint8_t wCurIconTile;
                union {
                    struct {
                        union {
                            uint8_t wSpriteAnimID;
                            uint8_t wCurSpriteOAMFlags;
                        };
                    };
                    struct {
                        uint16_t wSpriteAnimAddrBackup;
                    };
                };
                uint8_t wCurAnimVTile;
                uint8_t wCurAnimXCoord;
                uint8_t wCurAnimYCoord;
                uint8_t wCurAnimXOffset;
                uint8_t wCurAnimYOffset;
                uint8_t wGlobalAnimYOffset;
                uint8_t wGlobalAnimXOffset;
                uint8_t wSpriteAnimDataEnd[11];
                // mobile data
                uint8_t wc3cc[1];
                uint8_t wc3cd[31];
                uint8_t wc3ec;
                uint8_t wc3ed;
                uint8_t wc3ee;
                uint8_t wc3ef;
                uint8_t wc3f0;
                uint8_t wc3f1;
                uint8_t wc3f2;
                uint8_t wc3f3;
                uint8_t wc3f4;
                uint8_t wc3f5;
                uint8_t wc3f6;
                uint8_t wc3f7;
                uint8_t wc3f8;
                uint8_t wc3f9;
                uint8_t wc3fa;
                uint8_t wc3fb;
                uint8_t wc3fc;
                uint8_t skip_10[3];
                //void wMobileWRAMEnd
            };
            // Sprites
            struct {
                // WRAM0
                // wVirtualOAMSprite00 - wVirtualOAMSprite39
                //union wVirtualOAM
                // for n, NUM_SPRITE_OAM_STRUCTS
                // wVirtualOAMSprite00 - wVirtualOAMSprite39
                struct SpriteOAM wVirtualOAMSprite[NUM_SPRITE_OAM_STRUCTS];
                //void wVirtualOAMEnd
            };
            // Tilemap
            struct {
                // WRAM0
                // 20x18 grid of 8x8 tiles
                tile_t wTilemap[SCREEN_WIDTH * SCREEN_HEIGHT];
                // This union spans 480 bytes.
                //void wTilemapEnd
            };
            // Miscellaneous
            struct {
                union {
                    struct {
                        // WRAM0
                        // surrounding tiles
                        // This buffer determines the size for the rest of the union;
                        // it uses exactly 480 bytes.
                        tile_t wSurroundingTiles[SURROUNDING_WIDTH * SURROUNDING_HEIGHT];
                    };
                    struct {
                        // WRAM0
                        // box save buffer
                        // SaveBoxAddress uses this buffer in three steps because it
                        // needs more space than the buffer can hold.
                        uint8_t wBoxPartialData[480];
                        //void wBoxPartialDataEnd
                    };
                    struct {
                        // WRAM0
                        // battle tower temp struct
                        struct BattleTowerData wBT_OTTemp;
                    };
                    struct {
                        // WRAM0
                        // battle data
                        //union wBattle
                        struct Move wEnemyMoveStruct;
                        struct Move wPlayerMoveStruct;
                        uint8_t wEnemyMonNickname[MON_NAME_LENGTH];
                        uint8_t wBattleMonNickname[MON_NAME_LENGTH];
                        struct BattleMon wBattleMon;
                        uint8_t skip_11[2];
                        uint8_t wWildMon;
                        uint8_t skip_12[1];
                        uint8_t wEnemyTrainerItem1;
                        uint8_t wEnemyTrainerItem2;
                        uint8_t wEnemyTrainerBaseReward;
                        uint8_t wEnemyTrainerAIFlags[3];
                        uint8_t wOTClassName[TRAINER_CLASS_NAME_LENGTH];
                        uint8_t wCurOTMon;
                        // Bit array.  Bits 0 - 5 correspond to party members 1 - 6.
                        // Bit set if the mon appears in battle.
                        // Bit cleared if the mon faints.
                        // Backed up if the enemy switches.
                        // All bits cleared if the enemy faints.
                        uint8_t wBattleParticipantsNotFainted;
                        // >10: super-effective
                        //  10: normal
                        // <10: not very effective
                        // bit 7: stab
                        uint8_t wTypeModifier;
                        // 0 if not critical
                        // 1 for a critical hit
                        // 2 for a OHKO
                        uint8_t wCriticalHit;
                        // nonzero for a miss
                        uint8_t wAttackMissed;
                        uint8_t wPlayerSubStatus1;
                        uint8_t wPlayerSubStatus2;
                        uint8_t wPlayerSubStatus3;
                        uint8_t wPlayerSubStatus4;
                        uint8_t wPlayerSubStatus5;
                        uint8_t wEnemySubStatus1;
                        uint8_t wEnemySubStatus2;
                        uint8_t wEnemySubStatus3;
                        uint8_t wEnemySubStatus4;
                        uint8_t wEnemySubStatus5;
                        uint8_t wPlayerRolloutCount;
                        uint8_t wPlayerConfuseCount;
                        uint8_t wPlayerToxicCount;
                        uint8_t wPlayerDisableCount;
                        uint8_t wPlayerEncoreCount;
                        uint8_t wPlayerPerishCount;
                        uint8_t wPlayerFuryCutterCount;
                        uint8_t wPlayerProtectCount;
                        uint8_t wEnemyRolloutCount;
                        uint8_t wEnemyConfuseCount;
                        uint8_t wEnemyToxicCount;
                        uint8_t wEnemyDisableCount;
                        uint8_t wEnemyEncoreCount;
                        uint8_t wEnemyPerishCount;
                        uint8_t wEnemyFuryCutterCount;
                        uint8_t wEnemyProtectCount;
                        uint16_t wPlayerDamageTaken;
                        uint16_t wEnemyDamageTaken;
                        uint8_t wBattleReward[3];
                        uint8_t wBattleAnimParam;
                        uint8_t wBattleScriptBuffer[40];
                        uint16_t wBattleScriptBufferAddress;
                        uint8_t wTurnEnded;
                        uint8_t skip_13[1];
                        union {
                            uint16_t wPlayerStats[5];
                            struct {
                                uint16_t wPlayerAttack;
                                uint16_t wPlayerDefense;
                                uint16_t wPlayerSpeed;
                                uint16_t wPlayerSpAtk;
                                uint16_t wPlayerSpDef;
                            };
                        };
                        uint8_t skip_14[1];
                        union {
                            uint16_t wEnemyStats[5];
                            struct {
                                uint16_t wEnemyAttack;
                                uint16_t wEnemyDefense;
                                uint16_t wEnemySpeed;
                                uint16_t wEnemySpAtk;
                                uint16_t wEnemySpDef;
                            };
                        };
                        uint8_t skip_15[1];
                        //union wPlayerStatLevels
                        union {
                            uint8_t wPlayerStatLevels[NUM_LEVEL_STATS];
                            struct {
                                uint8_t wPlayerAtkLevel;
                                uint8_t wPlayerDefLevel;
                                uint8_t wPlayerSpdLevel;
                                uint8_t wPlayerSAtkLevel;
                                uint8_t wPlayerSDefLevel;
                                uint8_t wPlayerAccLevel;
                                uint8_t wPlayerEvaLevel;
                                uint8_t skip_16[1];
                            };
                        };
                        union {
                        //union wEnemyStatLevels
                            uint8_t wEnemyStatLevels[NUM_LEVEL_STATS];
                            struct {
                                uint8_t wEnemyAtkLevel;
                                uint8_t wEnemyDefLevel;
                                uint8_t wEnemySpdLevel;
                                uint8_t wEnemySAtkLevel;
                                uint8_t wEnemySDefLevel;
                                uint8_t wEnemyAccLevel;
                                uint8_t wEnemyEvaLevel;
                                uint8_t skip_17[1];
                            };
                        };
                        uint8_t wEnemyTurnsTaken;
                        uint8_t wPlayerTurnsTaken;
                        uint8_t skip_18[1];
                        uint8_t wPlayerSubstituteHP;
                        uint8_t wEnemySubstituteHP;
                        uint8_t wUnusedPlayerLockedMove;
                        uint8_t skip_19[1];
                        uint8_t wCurPlayerMove;
                        uint8_t wCurEnemyMove;
                        // how far through the prng stream
                        uint8_t wLinkBattleRNCount;
                        uint8_t wEnemyItemState;
                        uint8_t skip_20[2];
                        uint8_t wCurEnemyMoveNum;
                        uint16_t wEnemyHPAtTimeOfPlayerSwitch;
                        uint8_t wPayDayMoney[3];
                        uint8_t wSafariMonAngerCount;
                        // unreferenced
                        uint8_t wSafariMonEating;
                        uint8_t skip_21[1];
                        uint16_t wEnemyBackupDVs;
                        // used when enemy is transformed
                        uint8_t wAlreadyDisobeyed;
                        uint8_t wDisabledMove;
                        uint8_t wEnemyDisabledMove;
                        uint8_t wWhichMonFaintedFirst;
                        // exists so you can't counter on switch
                        uint8_t wLastPlayerCounterMove;
                        uint8_t wLastEnemyCounterMove;
                        uint8_t wEnemyMinimized;
                        uint8_t wAlreadyFailed;
                        uint8_t wBattleParticipantsIncludingFainted;
                        uint8_t wBattleLowHealthAlarm;
                        uint8_t wPlayerMinimized;
                        // bit
                        // 0 spikes
                        // 1
                        // 2 safeguard
                        // 3 light screen
                        // 4 reflect
                        // 5-7 unused
                        uint8_t wPlayerScreens;
                        // see wPlayerScreens
                        uint8_t wEnemyScreens;
                        uint8_t wPlayerSafeguardCount;
                        uint8_t wPlayerLightScreenCount;
                        uint8_t wPlayerReflectCount;
                        uint8_t skip_22[1];
                        uint8_t wEnemySafeguardCount;
                        uint8_t wEnemyLightScreenCount;
                        uint8_t wEnemyReflectCount;
                        uint8_t skip_23[1];
                        uint8_t skip_24[1];
                        // 00 normal
                        // 01 rain
                        // 02 sun
                        // 03 sandstorm
                        // 04 rain stopped
                        // 05 sunliight faded
                        // 06 sandstorm subsided
                        uint8_t wBattleWeather;
                        // # turns remaining
                        uint8_t wWeatherCount;
                        uint8_t wLoweredStat;
                        uint8_t wEffectFailed;
                        uint8_t wFailedMessage;
                        uint8_t wEnemyGoesFirst;
                        uint8_t wPlayerIsSwitching;
                        uint8_t wEnemyIsSwitching;
                        // add a move that has been used once by the player
                        // added in order of use
                        uint8_t wPlayerUsedMoves[NUM_MOVES];
                        uint8_t wEnemyAISwitchScore;
                        uint8_t wEnemySwitchMonParam;
                        uint8_t wEnemySwitchMonIndex;
                        uint8_t wTempLevel;
                        uint8_t wLastPlayerMon;
                        uint8_t wLastPlayerMove;
                        uint8_t wLastEnemyMove;
                        uint8_t wPlayerFutureSightCount;
                        uint8_t wEnemyFutureSightCount;
                        uint8_t wGivingExperienceToExpShareHolders;
                        uint8_t wBackupEnemyMonBaseStats[NUM_EXP_STATS];
                        uint8_t wBackupEnemyMonCatchRate;
                        uint8_t wBackupEnemyMonBaseExp;
                        uint16_t wPlayerFutureSightDamage;
                        uint16_t wEnemyFutureSightDamage;
                        uint8_t wPlayerRageCounter;
                        uint8_t wEnemyRageCounter;
                        uint8_t wBeatUpHitAtLeastOnce;
                        uint8_t wPlayerTrappingMove;
                        uint8_t wEnemyTrappingMove;
                        uint8_t wPlayerWrapCount;
                        uint8_t wEnemyWrapCount;
                        uint8_t wPlayerCharging;
                        uint8_t wEnemyCharging;
                        uint8_t wBattleEnded;
                        uint8_t wWildMonMoves[NUM_MOVES];
                        uint8_t wWildMonPP[NUM_MOVES];
                        uint8_t wAmuletCoin;
                        uint8_t wSomeoneIsRampaging;
                        uint8_t wPlayerJustGotFrozen;
                        uint8_t wEnemyJustGotFrozen;
                        //void wBattleEnd
                    };
                    struct {
                        // WRAM0
                        // link patch lists
                        uint8_t wPlayerPatchLists[200];
                        uint8_t wOTPatchLists[200];
                    };
                    struct {
                        // WRAM0
                        // mobile
                        uint8_t wMobileTransferData[480];
                    };
                    struct {
                        // WRAM0
                        // This union spans 200 bytes.
                        union {
                            struct {
                                // timeset temp storage
                                uint8_t wTimeSetBuffer[20];
                                uint8_t wInitHourBuffer;
                                uint8_t skip_25[9];
                                uint8_t wInitMinuteBuffer;
                                uint8_t skip_26[19];
                                //void wTimeSetBufferEnd
                            };
                            struct {
                                // hall of fame temp struct
                                struct HallOfFameData wHallOfFameTemp;
                            };
                            struct {
                                // odd egg
                                struct PartyMon wOddEgg;
                                uint8_t wOddEggName[MON_NAME_LENGTH];
                                uint8_t wOddEggOT[NAME_LENGTH];
                            };
                            struct {
                                // debug mon color picker
                                //union wDebugMiddleColors
                                uint8_t wDebugLightColor[2];
                                uint8_t wDebugDarkColor[2];
                                uint8_t skip_27[6];
                                uint8_t wDebugRedChannel;
                                uint8_t wDebugGreenChannel;
                                uint8_t wDebugBlueChannel;
                            };
                            struct {
                                // debug tileset color picker
                                //union wDebugPalette
                                uint8_t wDebugWhiteTileColor[2];
                                uint8_t wDebugLightTileColor[2];
                                uint8_t wDebugDarkTileColor[2];
                                uint8_t wDebugBlackTileColor[2];
                            };
                            struct {
                                uint8_t wc608[16];
                                uint8_t wc618[37];
                                uint8_t wc63d[5];
                                uint8_t wc642[5];
                                uint8_t wc647[1];
                                uint8_t wc648[2];
                                uint8_t wc64a[30];
                                uint8_t wc668[32];
                                uint8_t wc688[2];
                                uint8_t wc68a[30];
                                uint8_t wc6a8[40];
                            };
                        };
                        // This union spans 280 bytes.
                        union {
                            struct {
                                // pokedex
                                //union wPokedexDataStart
                                uint8_t wPokedexOrder[0x100];
                                // >= NUM_POKEMON
                                //union wPokedexOrderEnd
                                uint8_t wDexListingScrollOffset;
                                // offset of the first displayed entry from the start
                                uint8_t wDexListingCursor;
                                // Dex cursor
                                uint8_t wDexListingEnd;
                                // Last mon to display
                                uint8_t wDexListingHeight;
                                // number of entries displayed at once in the dex listing
                                uint8_t wCurDexMode;
                                // Pokedex Mode
                                uint8_t wDexSearchMonType1;
                                // first type to search
                                uint8_t wDexSearchMonType2;
                                // second type to search
                                uint8_t wDexSearchResultCount;
                                uint8_t wDexArrowCursorPosIndex;
                                uint8_t wDexArrowCursorDelayCounter;
                                uint8_t wDexArrowCursorBlinkCounter;
                                uint8_t wDexSearchSlowpokeFrame;
                                uint8_t wUnlockedUnownMode;
                                uint8_t wDexCurUnownIndex;
                                uint8_t wDexUnownCount;
                                uint8_t wDexConvertedMonType;
                                // mon type converted from dex search mon type
                                uint8_t wDexListingScrollOffsetBackup;
                                uint8_t wDexListingCursorBackup;
                                uint8_t wBackupDexListingCursor;
                                uint8_t wBackupDexListingPage;
                                uint8_t wDexCurLocation;
                                // if
                                // DEF
                                // (
                                // _CRYSTAL11
                                // )
                                // uint8_t wPokedexStatus;
                                //union wPokedexDataEnd
                                // else
                                uint8_t wPokedexDataEnd[1];
                                // endc
                                uint8_t skip_28[2];
                            };
                            struct {
                                // pokegear
                                uint8_t wPokegearPhoneDisplayPosition;
                                uint8_t wPokegearPhoneCursorPosition;
                                uint8_t wPokegearPhoneScrollPosition;
                                uint8_t wPokegearPhoneSelectedPerson;
                                uint8_t wPokegearPhoneSubmenuCursor;
                                uint16_t wPokegearMapCursorObjectPointer;
                                uint8_t wPokegearMapCursorLandmark;
                                uint8_t wPokegearMapPlayerIconLandmark;
                                uint8_t wPokegearRadioChannelBank;
                                uint16_t wPokegearRadioChannelAddr;
                                uint8_t wPokegearRadioMusicPlaying;
                            };
                            struct {
                                // trade
                                struct TradeMon wPlayerTrademon;
                                struct TradeMon wOTTrademon;
                                uint16_t wTradeAnimAddress;
                                uint8_t wLinkPlayer1Name[NAME_LENGTH];
                                uint8_t wLinkPlayer2Name[NAME_LENGTH];
                                uint8_t wLinkTradeSendmonSpecies;
                                uint8_t wLinkTradeGetmonSpecies;
                            };
                            struct {
                                // naming screen
                                uint16_t wNamingScreenDestinationPointer;
                                uint8_t wNamingScreenCurNameLength;
                                uint8_t wNamingScreenMaxNameLength;
                                uint8_t wNamingScreenType;
                                uint16_t wNamingScreenCursorObjectPointer;
                                uint8_t wNamingScreenLastCharacter;
                                uint16_t wNamingScreenStringEntryCoord;
                            };
                            struct {
                                // slot machine
                                //union wSlots
                                struct SlotReel wReel1;
                                struct SlotReel wReel2;
                                struct SlotReel wReel3;
                                uint8_t wReel1Stopped[3];
                                uint8_t wReel2Stopped[3];
                                uint8_t wReel3Stopped[3];
                                uint8_t wSlotBias;
                                uint8_t wSlotBet;
                                uint8_t wFirstTwoReelsMatching;
                                uint8_t wFirstTwoReelsMatchingSevens;
                                uint8_t wSlotMatched;
                                uint8_t wCurReelStopped[3];
                                uint16_t wPayout;
                                uint8_t wCurReelXCoord;
                                uint8_t wCurReelYCoord;
                                uint8_t skip_29[2];
                                uint8_t wSlotBuildingMatch;
                                uint8_t wSlotsDataEnd[28];
                                //void wSlotsEnd
                            };
                            struct {
                                // card flip
                                uint8_t wDeck[4 * 6];
                                //union wDeckEnd
                                uint8_t wCardFlipNumCardsPlayed;
                                uint8_t wCardFlipFaceUpCard;
                                uint8_t wDiscardPile[4 * 6];
                                // beta poker game
                                //union wDiscardPileEnd
                                uint16_t wBetaPokerSGBPals;
                                uint8_t skip_30[1];
                                uint8_t wBetaPokerSGBAttr;
                                uint8_t wBetaPokerSGBCol;
                                uint8_t wBetaPokerSGBRow;
                            };
                            struct {
                                // unused memory game
                                uint8_t wMemoryGameCards[9 * 5];
                                //union wMemoryGameCardsEnd
                                uint8_t wMemoryGameLastCardPicked;
                                uint8_t wMemoryGameCard1;
                                uint8_t wMemoryGameCard2;
                                uint8_t wMemoryGameCard1Location;
                                uint8_t wMemoryGameCard2Location;
                                uint8_t wMemoryGameNumberTriesRemaining;
                                uint8_t wMemoryGameLastMatches[5];
                                uint8_t wMemoryGameCounter;
                                uint8_t wMemoryGameNumCardsMatched;
                            };
                            struct {
                                // unown puzzle
                                uint8_t wPuzzlePieces[6 * 6];
                            };
                            struct {
                                // mobile data
                                uint8_t wc6d0[56];
                                uint8_t wc708;
                                uint8_t wc709;
                                uint8_t wc70a;
                                uint8_t wc70b;
                                uint8_t wc70c;
                                uint8_t wc70d;
                                uint8_t wc70e;
                                uint8_t wc70f;
                                uint8_t wc710;
                                uint8_t wc711;
                                uint8_t wc712[7];
                                uint8_t wc719[53];
                                uint8_t wc74e[107];
                                uint8_t wc7b9[1];
                                uint8_t wc7ba[1];
                                uint8_t wc7bb[2];
                                uint8_t wc7bd[19];
                                uint8_t wc7d0[1];
                                uint8_t wc7d1[1];
                                uint8_t wc7d2[1];
                                uint8_t wc7d3[2];
                            };
                        };
                    };
                };
            };
            // Unused Map Buffer
            struct {
                // WRAM0
                // This was a buffer for map-related pointers in the 1997 G/S prototype.
                // See wMapBuffer in pokegold-spaceworld's wram.asm.
                uint8_t wUnusedMapBuffer[24];
                //void wUnusedMapBufferEnd
            };
            // Overworld Map
            struct {
                union {
                    struct {
                        // WRAM0
                        // overworld map blocks
                        uint8_t wOverworldMapBlocks[1300];
                        //void wOverworldMapBlocksEnd
                    };
                    struct {
                        // WRAM0
                        // GB Printer data
                        //union wGameboyPrinterRAM
                        uint8_t wGameboyPrinter2bppSource[40 * LEN_2BPP_TILE];
                        //union wGameboyPrinter2bppSourceEnd
                        uint8_t wUnusedGameboyPrinterSafeCancelFlag;
                        uint8_t wPrinterRowIndex;
                        // Printer data
                        uint8_t wPrinterData[4];
                        uint16_t wPrinterChecksum;
                        uint8_t wPrinterHandshake;
                        // bit 7: set if error 1 (battery low)
                        // bit 6: set if error 4 (too hot or cold)
                        // bit 5: set if error 3 (paper jammed or empty)
                        // if this and the previous byte are both $ff: error 2 (connection error)
                        uint8_t wPrinterStatusFlags;
                        uint8_t wHandshakeFrameDelay;
                        uint8_t wPrinterSerialFrameDelay;
                        uint16_t wPrinterSendByteOffset;
                        uint16_t wPrinterSendByteCounter;
                        // tilemap backup?
                        uint8_t wPrinterTilemapBuffer[SCREEN_HEIGHT * SCREEN_WIDTH];
                        uint8_t wPrinterStatus;
                        uint8_t skip_31[1];
                        // High nibble is for margin before the image, low nibble is for after.
                        uint8_t wPrinterMargins;
                        uint8_t wPrinterExposureTime;
                        uint8_t skip_32[16];
                        //void wGameboyPrinterRAMEnd
                    };
                    struct {
                        // WRAM0
                        // bill's pc data
                        //union wBillsPCData
                        // (species, box number, list index) x30
                        struct BillsPCMonEntry wBillsPCPokemonList[30];
                        uint8_t skip_33[720];
                        uint8_t wBillsPC_ScrollPosition;
                        uint8_t wBillsPC_CursorPosition;
                        uint8_t wBillsPC_NumMonsInBox;
                        uint8_t wBillsPC_NumMonsOnScreen;
                        uint8_t wBillsPC_LoadedBox;
                        // 0 if party, 1 - 14 if box, 15 if active box
                        uint8_t wBillsPC_BackupScrollPosition;
                        uint8_t wBillsPC_BackupCursorPosition;
                        uint8_t wBillsPC_BackupLoadedBox;
                        uint8_t wBillsPC_MonHasMail;
                        uint8_t skip_34[5];
                        //void wBillsPCDataEnd
                    };
                    struct {
                        // WRAM0
                        // Hall of Fame data
                        struct HallOfFameData wHallOfFamePokemonList;
                    };
                    struct {
                        // WRAM0
                        // debug color picker
                        uint8_t wDebugOriginalColors[256 * 4];
                    };
                    struct {
                        // WRAM0
                        // raw link data
                        uint8_t wLinkData[1300];
                        //void wLinkDataEnd
                    };
                    struct {
                        // WRAM0
                        // link data members
                        uint8_t wLinkPlayerName[NAME_LENGTH];
                        uint8_t wLinkPartyCount;
                        uint8_t wLinkPartySpecies[PARTY_LENGTH];
                        uint8_t wLinkPartyEnd;
                        // older code doesn't check PartyCount
                        union {
                            struct {
                                // link player data
                                // wLinkPlayerPartyMon1 - wLinkPlayerPartyMon6
                                //union wLinkPlayerData
                                // for n, 1, PARTY_LENGTH + 1
                                // wLinkPlayerPartyMon1 - wLinkPlayerPartyMon6
                                struct PartyMon wLinkPlayerPartyMon[(PARTY_LENGTH + 1) - 1];
                                // wLinkPlayerPartyMon1OT - wLinkPlayerPartyMon6OT
                                //union wLinkPlayerPartyMonOTs
                                // for n, 1, PARTY_LENGTH + 1
                                uint8_t wLinkPlayerPartyMonOT[(PARTY_LENGTH + 1) - 1][NAME_LENGTH];
                                // wLinkPlayerPartyMon1Nickname - wLinkPlayerPartyMon6Nickname
                                //union wLinkPlayerPartyMonNicknames
                                // for n, 1, PARTY_LENGTH + 1
                                uint8_t wLinkPlayerPartyMonNickname[(PARTY_LENGTH + 1) - 1][MON_NAME_LENGTH];
                            };
                            struct {
                                // time capsule party data
                                // wTimeCapsulePartyMon1 - wTimeCapsulePartyMon6
                                //union wTimeCapsulePlayerData
                                // for n, 1, PARTY_LENGTH + 1
                                // wTimeCapsulePartyMon1 - wTimeCapsulePartyMon6
                                struct RedPartyMon wTimeCapsulePartyMon[(PARTY_LENGTH + 1) - 1];
                                // wTimeCapsulePartyMon1OT - wTimeCapsulePartyMon6OT
                                //union wTimeCapsulePartyMonOTs
                                // for n, 1, PARTY_LENGTH + 1
                                uint8_t wTimeCapsulePartyMonOT[(PARTY_LENGTH + 1) - 1][NAME_LENGTH];
                                // wTimeCapsulePartyMon1Nickname - wTimeCapsulePartyMon6Nickname
                                //union wTimeCapsulePartyMonNicknames
                                // for n, 1, PARTY_LENGTH + 1
                                uint8_t wTimeCapsulePartyMonNickname[(PARTY_LENGTH + 1) - 1][MON_NAME_LENGTH];
                            };
                            struct {
                                // link patch lists
                                uint8_t wLinkPatchList1[SERIAL_PATCH_LIST_LENGTH];
                                uint8_t wLinkPatchList2[SERIAL_PATCH_LIST_LENGTH];
                            };
                        };
                    };
                    struct {
                        // WRAM0
                        // link data prep
                        uint8_t skip_35[1000];
                        uint16_t wCurLinkOTPartyMonTypePointer;
                        // wLinkOTPartyMon1Type - wLinkOTPartyMon6Type
                        //union wLinkOTPartyMonTypes
                        // for n, 1, PARTY_LENGTH + 1
                        uint16_t wLinkOTPartyMonType[PARTY_LENGTH];
                    };
                    struct {
                        // WRAM0
                        // link mail data
                        uint8_t skip_36[500];
                        //union wLinkPlayerMail
                        uint8_t wLinkPlayerMailPreamble[SERIAL_MAIL_PREAMBLE_LENGTH];
                        uint8_t wLinkPlayerMailMessages[(MAIL_MSG_LENGTH + 1) * PARTY_LENGTH];
                        uint8_t wLinkPlayerMailMetadata[(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1)) * PARTY_LENGTH];
                        uint8_t wLinkPlayerMailPatchSet[103];
                        uint8_t wLinkPlayerMailEnd[10];
                        //union wLinkOTMail
                        uint8_t wLinkOTMailMessages[(MAIL_MSG_LENGTH + 1) * PARTY_LENGTH];
                        uint8_t wLinkOTMailMetadata[(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1)) * PARTY_LENGTH];
                        uint8_t wOTPlayerMailPatchSet[103 + SERIAL_MAIL_PREAMBLE_LENGTH];
                        uint8_t wLinkOTMailEnd[10];
                    };
                    struct {
                        // WRAM0
                        // received link mail data
                        uint8_t skip_37[500];
                        uint8_t wLinkReceivedMail[MAIL_STRUCT_LENGTH * PARTY_LENGTH];
                        uint8_t wLinkReceivedMailEnd;
                    };
                    struct {
                        // WRAM0
                        // mystery gift data
                        uint8_t wMysteryGiftStaging[80];
                        union {
                            struct {
                                uint8_t wMysteryGiftTrainer[1 + (1 + 1 + NUM_MOVES) * PARTY_LENGTH + 1];
                                //void wMysteryGiftTrainerEnd
                            };
                            struct {
                                uint8_t wNameCardData[NAME_LENGTH + 2 + 2 + 1 + 8 + 12];
                                //void wNameCardDataEnd
                            };
                            struct {
                                uint8_t wMysteryGiftCardHolderName[PLAYER_NAME_LENGTH];
                            };
                        };
                        uint8_t skip_38[138];
                        //union wMysteryGiftPartnerData
                        uint8_t wMysteryGiftGameVersion;
                        uint16_t wMysteryGiftPartnerID;
                        uint8_t wMysteryGiftPartnerName[NAME_LENGTH];
                        uint8_t wMysteryGiftPartnerDexCaught;
                        uint8_t wMysteryGiftPartnerSentDeco;
                        uint8_t wMysteryGiftPartnerWhichItem;
                        uint8_t wMysteryGiftPartnerWhichDeco;
                        uint8_t wMysteryGiftPartnerBackupItem;
                        uint8_t skip_39[1];
                        uint8_t wMysteryGiftPartnerDataEnd[60];
                        uint8_t wMysteryGiftPlayerData[1];
                        uint16_t wMysteryGiftPlayerID;
                        uint8_t wMysteryGiftPlayerName[NAME_LENGTH];
                        uint8_t wMysteryGiftPlayerDexCaught;
                        uint8_t wMysteryGiftPlayerSentDeco;
                        uint8_t wMysteryGiftPlayerWhichItem;
                        uint8_t wMysteryGiftPlayerWhichDeco;
                        uint8_t wMysteryGiftPlayerBackupItem;
                        uint8_t skip_40[1];
                        //void wMysteryGiftPlayerDataEnd
                    };
                    struct {
                        // WRAM0
                        uint8_t skip_41[0x200];
                        // mystery gift data
                        uint8_t wUnusedMysteryGiftStagedDataLength;
                        uint8_t wMysteryGiftMessageCount;
                        uint8_t wMysteryGiftStagedDataLength;
                    };
                    struct {
                        // WRAM0
                        uint8_t skip_42[0x200];
                        // blank credits tile buffer
                        uint8_t wCreditsBlankFrame2bpp[4 * 4 * LEN_2BPP_TILE];
                        //void wCreditsBlankFrame2bppEnd
                    };
                    struct {
                        // WRAM0
                        // mobile
                        uint8_t wc800;
                        uint8_t wc801;
                        uint8_t wc802;
                        uint8_t wc803;
                        uint8_t wc804;
                        uint8_t wc805;
                        uint8_t wc806;
                        uint8_t wc807;
                        uint16_t wc808;
                        uint8_t wc80a;
                        uint8_t wc80b;
                        uint16_t wc80c;
                        uint8_t wc80e;
                        uint8_t wc80f;
                        uint8_t wc810;
                        uint8_t wc811;
                        uint16_t wMobileSDK_PacketChecksum;
                        uint8_t wc814;
                        uint8_t wc815;
                        uint16_t wc816;
                        uint8_t wMobileSDK_AdapterType;
                        uint8_t wc819;
                        uint8_t wc81a;
                        uint8_t wc81b;
                        uint8_t wc81c;
                        uint8_t wc81d;
                        uint8_t wMobileSDK_SendCommandID;
                        uint8_t wc81f;
                        uint8_t wc820;
                        uint8_t wc821;
                        uint8_t wc822;
                        uint8_t wc823[4];
                        uint16_t wc827;
                        uint8_t wc829;
                        uint8_t wc82a;
                        uint8_t wc82b;
                        uint8_t wc82c;
                        uint8_t wc82d;
                        uint8_t wc82e;
                        uint8_t wc82f[3];
                        uint8_t wc832;
                        uint8_t wc833;
                        uint8_t wc834;
                        uint8_t wc835;
                        uint8_t wc836[8];
                        uint8_t wc83e[20];
                        uint8_t wc852[20];
                        uint8_t wc866[4];
                        uint8_t wc86a;
                        uint8_t wc86b;
                        uint8_t wc86c;
                        uint8_t wc86d;
                        uint8_t wc86e;
                        uint8_t wc86f;
                        uint8_t wc870;
                        uint8_t wc871;
                        uint8_t wc872;
                        uint8_t wc873;
                        uint8_t wc874;
                        uint8_t wc875;
                        uint8_t wc876;
                        uint8_t wc877;
                        uint16_t wc878;
                        uint8_t wc87a;
                        uint8_t wc87b;
                        uint8_t wc87c;
                        uint8_t wc87d;
                        uint8_t wc87e;
                        uint8_t wc87f;
                        uint8_t wc880;
                        uint8_t wc881;
                        uint8_t wc882;
                        uint8_t wc883;
                        uint8_t wc884[8];
                        uint8_t wc88c[32];
                        uint8_t wc8ac[26];
                        uint8_t wc8c6;
                        uint8_t wc8c7;
                        uint8_t wc8c8;
                        uint8_t wc8c9;
                        uint8_t wc8ca[44];
                        uint8_t wc8f6[8];
                        uint8_t wc8fe;
                        uint8_t wc8ff[15];
                        uint8_t wc90e[8];
                        uint8_t wc916[16];
                        uint8_t wc926[8];
                        uint8_t wc92e[75];
                        uint8_t wc979;
                        uint8_t wc97a[5];
                        uint8_t wc97f;
                        uint8_t wc980;
                        uint8_t wc981;
                        uint8_t wc982;
                        uint16_t wc983;
                        uint8_t wc985;
                        uint8_t wc986;
                        uint8_t wc987;
                        uint8_t wMobileAPIIndex;
                        uint8_t wc989;
                        uint8_t wc98a;
                        uint8_t wc98b;
                        uint8_t wc98c;
                        uint8_t wc98d;
                        uint8_t wc98e;
                        uint8_t wc98f;
                        uint8_t wc990;
                        uint8_t wc991;
                        uint8_t wc992;
                        uint8_t wc993;
                        uint8_t wc994;
                        uint8_t wc995[16];
                        uint8_t wc9a5[5];
                        uint8_t wc9aa;
                        uint8_t wc9ab;
                        uint8_t wc9ac;
                        uint8_t wc9ad;
                        uint8_t wc9ae;
                        uint16_t wc9af;
                        uint8_t wc9b1;
                        uint8_t wc9b2[3];
                        uint8_t wc9b5;
                        uint8_t wc9b6[121];
                        uint8_t wMobileSDK_ReceivePacketBufferAlt[11];
                        uint16_t wMobileSDK_ReceivedBytes;
                        uint8_t wMobileSDK_ReceivePacketBuffer[250];
                        uint8_t wcb36;
                        uint8_t skip_43[16];
                        uint8_t wMobileSDK_PacketBuffer[281];
                        uint8_t wcc60[1];
                        uint8_t wcc61[1];
                        uint8_t wcc62[2];
                        uint8_t wcc64[1];
                        uint8_t wcc65[57];
                        uint8_t skip_44[22];
                        uint8_t wccb4[1];
                        uint8_t wccb5[3];
                        uint8_t wccb8[1];
                        uint8_t wccb9[1];
                        uint8_t wccba[90];
                        // if
                        // DEF
                        // (
                        // _DEBUG
                        // )
                    };
                    // struct {
                        // // WRAM0
                        // // debug room RTC values
                        // uint8_t wDebugRoomRTCSec;
                        // uint8_t wDebugRoomRTCMin;
                        // uint8_t wDebugRoomRTCHour;
                        // uint16_t wDebugRoomRTCDay;
                        // uint8_t wDebugRoomRTCCurSec;
                        // uint8_t wDebugRoomRTCCurMin;
                        // uint8_t wDebugRoomRTCCurHour;
                        // uint16_t wDebugRoomRTCCurDay;
                        // // debug room paged values
                        // uint8_t wDebugRoomCurPage;
                        // uint8_t wDebugRoomCurValue;
                        // uint16_t wDebugRoomAFunction;
                        // uint16_t wDebugRoomStartFunction;
                        // uint16_t wDebugRoomSelectFunction;
                        // uint16_t wDebugRoomAutoFunction;
                        // uint8_t wDebugRoomPageCount;
                        // uint16_t wDebugRoomPagesPointer;
                        // uint16_t wDebugRoomROMChecksum;
                        // uint8_t wDebugRoomCurChecksumBank;
                        // union {
                        //     struct {
                        //         // debug room new item values
                        //         uint8_t wDebugRoomItemID;
                        //         uint8_t wDebugRoomItemQuantity;
                        //     };
                        //     struct {
                        //         // debug room new pokemon values
                        //         struct BoxMon wDebugRoomMon;
                        //         uint8_t wDebugRoomMonBox;
                        //     };
                        //     struct {
                        //         // debug room GB ID values
                        //         uint16_t wDebugRoomGBID;
                        //     };
                        // };
                        // endc
                    // };
                };
            };
            uint8_t section_pad_1[12]; // Padding for Overworld Map
            // Video
            struct {
                // WRAM0
                union {
                    struct {
                        // bg map
                        uint8_t wBGMapBuffer[40];
                        uint8_t wBGMapPalBuffer[40];
                        uint8_t wBGMapBufferPointers[20 * 2];
                        //void wBGMapBufferEnd
                    };
                    struct {
                        // credits
                        uint16_t wCreditsPos;
                        uint8_t wCreditsTimer;
                    };
                    struct {
                        // mobile data
                        uint16_t wMobileMonSpeciesPointer;
                        uint16_t wMobileMonStructPointer;
                        uint16_t wMobileMonOTPointer;
                        uint16_t wMobileMonNicknamePointer;
                        uint16_t wMobileMonMailPointer;
                    };
                    struct {
                        // more mobile data
                        uint8_t wcd20[1];
                        uint8_t wcd21[1];
                        uint8_t wcd22[1];
                        uint8_t wcd23[1];
                        uint8_t wcd24[1];
                        uint8_t wMobileCommsJumptableIndex[1];
                        uint8_t wcd26[1];
                        uint8_t wcd27[1];
                        uint8_t wcd28[1];
                        uint8_t wcd29[1];
                        union {
                            uint8_t wMobileMonSpecies;
                            uint8_t wcd2a;
                        };
                        union {
                            struct {
                                uint8_t wTempOddEggNickname[MON_NAME_LENGTH];
                            };
                            struct {
                                uint8_t wcd2b;
                                uint8_t wcd2c;
                                uint8_t wcd2d;
                                uint8_t wcd2e;
                                uint8_t wcd2f;
                                uint8_t wcd30;
                                uint8_t wcd31;
                                uint8_t wcd32;
                                uint8_t wcd33;
                                uint8_t wcd34;
                                uint8_t wcd35;
                            };
                        };
                        // current time for link/mobile?
                        uint8_t wcd36;
                        // hours
                        uint8_t wcd37;
                        // mins
                        uint8_t wcd38;
                        // secs
                        uint8_t wcd39[1];
                        uint8_t wcd3a[1];
                        uint8_t wcd3b[1];
                        uint8_t wBattleTowerRoomMenu2JumptableIndex[1];
                        uint8_t wcd3d[1];
                        uint8_t wcd3e[1];
                        uint8_t wcd3f[1];
                        uint8_t wcd40[1];
                        uint8_t wcd41[1];
                        uint8_t wcd42[1];
                        uint8_t wcd43[1];
                        // some sort of timer in link battles
                        uint8_t wMobileInactivityTimerMinutes;
                        // mins
                        uint8_t wMobileInactivityTimerSeconds;
                        // secs
                        uint8_t wMobileInactivityTimerFrames;
                        // frames
                        uint8_t wcd47[1];
                        uint8_t skip_45[1];
                        //union wBTTempOTSprite
                        uint8_t wcd49;
                        uint8_t wcd4a[1];
                        uint8_t wcd4b[1];
                        union {
                            uint8_t wEZChatCursorXCoord;
                            uint8_t wcd4c;
                        };
                        union {
                            uint8_t wEZChatCursorYCoord;
                            uint8_t wcd4d;
                        };
                        uint8_t wcd4e[1];
                        uint8_t wcd4f[1];
                        uint8_t wcd50[1];
                        uint8_t wcd51[1];
                        uint8_t wcd52[1];
                        // ds 12
                        //union wMobileOpponentBattleMessage
                        uint8_t wcd53[1];
                        uint8_t wcd54[1];
                        uint8_t wcd55[1];
                        uint8_t wcd56[1];
                        uint8_t wcd57[1];
                        uint8_t wcd58[1];
                        uint8_t wcd59[1];
                        uint8_t wcd5a[1];
                        uint8_t wcd5b[1];
                        uint8_t wcd5c[1];
                        uint8_t wcd5d[1];
                        uint8_t wcd5e[1];
                        uint8_t wcd5f[1];
                        uint8_t wcd60[2];
                        uint8_t wcd62[1];
                        uint8_t wcd63[1];
                        uint8_t wcd64[1];
                        uint8_t wcd65;
                        uint8_t wcd66;
                        uint8_t wcd67;
                        uint8_t wcd68;
                        uint8_t wcd69[1];
                        uint8_t wcd6a[1];
                        uint8_t wcd6b[1];
                        uint8_t wcd6c[1];
                        uint8_t wcd6d[1];
                        uint8_t wcd6e[1];
                        uint8_t wcd6f[1];
                        uint8_t wcd70[1];
                        uint8_t wcd71[1];
                        uint8_t wcd72[1];
                        uint8_t wcd73[1];
                        uint8_t wcd74[1];
                        uint8_t wOTMonSelection[2];
                        // ds BATTLETOWER_PARTY_LENGTH
                        uint8_t wcd77[1];
                        uint16_t wMobileCrashCheckPointer;
                        uint8_t wcd7a[2];
                        uint8_t wcd7c[3];
                        uint8_t wcd7f;
                        uint8_t wcd80;
                        uint8_t wcd81[1];
                        uint8_t wcd82[1];
                        uint8_t wcd83[1];
                        uint8_t wcd84[1];
                        uint8_t wcd85[4];
                        uint8_t wcd89;
                        uint8_t wcd8a;
                        uint8_t wcd8b;
                        uint8_t wcd8c[1];
                        uint8_t wcd8d[11];
                    };
                };
                uint8_t wDefaultSGBLayout;
                uint8_t wPlayerHPPal;
                uint8_t wEnemyHPPal;
                uint8_t wHPPals[PARTY_LENGTH];
                uint8_t wCurHPPal;
                uint8_t skip_46[7];
                uint8_t wSGBPals[48];
                // 20x18 grid of bg tile attributes for 8x8 tiles
                // read horizontally from the top row
                //		bit 7: priority
                //		bit 6: y flip
                //		bit 5: x flip
                //		bit 4: pal # (non-cgb)
                //		bit 3: vram bank (cgb only)
                //		bit 2-0: pal # (cgb only)
                uint8_t wAttrmap[SCREEN_WIDTH * SCREEN_HEIGHT];
                //void wAttrmapEnd
                union {
                    struct {
                        // addresses dealing with serial comms
                        uint8_t skip_47[1];
                        uint8_t wcf42;
                        uint8_t skip_48[1];
                        uint8_t wcf44;
                        uint8_t wcf45;
                    };
                    struct {
                        uint8_t wTileAnimBuffer[1 * LEN_2BPP_TILE];
                    };
                };
                // link data
                union {
                    struct {
                        uint8_t wOtherPlayerLinkMode;
                        uint8_t wOtherPlayerLinkAction;
                        uint8_t skip_49[3];
                        uint8_t wPlayerLinkAction;
                        uint8_t wUnusedLinkAction;
                        uint8_t skip_50[3];
                    };
                    struct {
                        uint8_t wLinkReceivedSyncBuffer[5];
                        uint8_t wLinkPlayerSyncBuffer[5];
                    };
                };
                uint16_t wLinkTimeoutFrames;
                uint16_t wLinkByteTimeout;
                uint8_t wMonType;
                uint8_t wCurSpecies;
                uint8_t wNamedObjectType;
                uint8_t skip_51[1];
                union {
                    uint8_t wJumptableIndex;
                    uint8_t wBattleTowerBattleEnded;
                };
                union {
                    struct {
                        // intro data
                        uint8_t wIntroSceneFrameCounter;
                        uint8_t wIntroSceneTimer;
                    };
                    struct {
                        // title data
                        uint8_t wTitleScreenSelectedOption;
                        uint16_t wTitleScreenTimer;
                    };
                    struct {
                        // credits data
                        uint8_t wCreditsBorderFrame;
                        uint8_t wCreditsBorderMon;
                        uint8_t wCreditsLYOverride;
                    };
                    struct {
                        // pokedex
                        uint8_t wPrevDexEntryJumptableIndex;
                        // if
                        // DEF
                        // (
                        // _CRYSTAL11
                        // )
                        union {
                            uint8_t wPrevDexEntryBackup;
                            // else
                            //union wPrevDexEntryBackup
                            uint8_t wPokedexStatus;
                        };
                        // endc
                        uint8_t wUnusedPokedexByte;
                    };
                    struct {
                        // pokegear
                        uint8_t wPokegearCard;
                        uint8_t wPokegearMapRegion;
                        uint8_t wUnusedPokegearByte;
                    };
                    struct {
                        // pack
                        uint8_t wPackJumptableIndex;
                        uint8_t wCurPocket;
                        uint8_t wPackUsedItem;
                    };
                    struct {
                        // trainer card badges
                        uint8_t wTrainerCardBadgeFrameCounter;
                        uint8_t wTrainerCardBadgeTileID;
                        uint8_t wTrainerCardBadgeAttributes;
                    };
                    struct {
                        // slot machine
                        uint8_t wSlotsDelay;
                        uint8_t skip_52[1];
                        uint8_t wUnusedSlotReelIconDelay;
                    };
                    struct {
                        // card flip
                        uint8_t wCardFlipCursorY;
                        uint8_t wCardFlipCursorX;
                        uint8_t wCardFlipWhichCard;
                    };
                    struct {
                        // unused memory game
                        uint8_t wMemoryGameCardChoice;
                    };
                    struct {
                        // magnet train
                        uint8_t wMagnetTrainOffset;
                        uint8_t wMagnetTrainPosition;
                        uint8_t wMagnetTrainWaitCounter;
                    };
                    struct {
                        // unown puzzle data
                        uint8_t wHoldingUnownPuzzlePiece;
                        uint8_t wUnownPuzzleCursorPosition;
                        uint8_t wUnownPuzzleHeldPiece;
                    };
                    struct {
                        // battle transitions
                        uint8_t wBattleTransitionCounter;
                        union {
                            uint8_t wBattleTransitionSineWaveOffset;
                            uint8_t wBattleTransitionSpinQuadrant;
                        };
                    };
                    struct {
                        // bill's pc
                        uint8_t wUnusedBillsPCData[3];
                    };
                    struct {
                        // debug mon color picker
                        uint8_t wDebugColorRGBJumptableIndex;
                        uint8_t wDebugColorCurColor;
                        uint8_t wDebugColorCurMon;
                    };
                    struct {
                        // debug tileset color picker
                        uint8_t wDebugTilesetCurPalette;
                        uint8_t wDebugTilesetRGBJumptableIndex;
                        uint8_t wDebugTilesetCurColor;
                    };
                    struct {
                        // stats screen
                        uint8_t wStatsScreenFlags;
                    };
                    struct {
                        // battle tower
                        uint8_t wNrOfBeatenBattleTowerTrainers;
                        uint8_t skip_53[1];
                        uint8_t wBattleTowerRoomMenuJumptableIndex;
                    };
                    struct {
                        // miscellaneous
                        union {
                            uint8_t wFrameCounter;
                            uint8_t wMomBankDigitCursorPosition;
                            uint8_t wNamingScreenLetterCase;
                            uint8_t wHallOfFameMonCounter;
                            uint8_t wTradeDialog;
                        };
                        union {
                            uint8_t wFrameCounter2;
                            uint8_t wPrinterQueueLength;
                            uint8_t wUnusedSGB1eColorOffset;
                        };
                        uint8_t wUnusedTradeAnimPlayEvolutionMusic;
                    };
                    struct {
                        // mobile
                        uint8_t wcf64;
                        uint8_t wcf65;
                        uint8_t wcf66;
                    };
                };
                uint8_t wRequested2bppSize;
                uint16_t wRequested2bppSource;
                uint16_t wRequested2bppDest;
                uint8_t wRequested1bppSize;
                uint16_t wRequested1bppSource;
                uint16_t wRequested1bppDest;
                //union wMenuMetadata
                uint16_t wWindowStackPointer;
                uint8_t wMenuJoypad;
                uint8_t wMenuSelection;
                uint8_t wMenuSelectionQuantity;
                uint8_t wWhichIndexSet;
                uint8_t wScrollingMenuCursorPosition;
                uint8_t wWindowStackSize;
                uint8_t skip_54[8];
                // menu header
                //union wMenuMetadataEnd
                //union wMenuHeader
                uint8_t wMenuFlags;
                uint8_t wMenuBorderTopCoord;
                uint8_t wMenuBorderLeftCoord;
                uint8_t wMenuBorderBottomCoord;
                uint8_t wMenuBorderRightCoord;
                uint16_t wMenuDataPointer;
                uint8_t wMenuCursorPosition;
                uint8_t skip_55[1];
                uint8_t wMenuDataBank;
                uint8_t skip_56[6];
                //union wMenuHeaderEnd
                //union wMenuData
                uint8_t wMenuDataFlags;
                union {
                    struct {
                        // Vertical Menu/DoNthMenu/SetUpMenu
                        uint8_t wMenuDataItems;
                        uint16_t wMenuDataIndicesPointer;
                        uint16_t wMenuDataDisplayFunctionPointer;
                        uint16_t wMenuDataPointerTableAddr;
                    };
                    struct {
                        // 2D Menu
                        uint8_t wMenuData_2DMenuDimensions;
                        uint8_t wMenuData_2DMenuSpacing;
                        uint8_t wMenuData_2DMenuItemStringsBank;
                        uint16_t wMenuData_2DMenuItemStringsAddr;
                        uint8_t wMenuData_2DMenuFunctionBank;
                        uint16_t wMenuData_2DMenuFunctionAddr;
                    };
                    struct {
                        // Scrolling Menu
                        uint8_t wMenuData_ScrollingMenuHeight;
                        uint8_t wMenuData_ScrollingMenuWidth;
                        uint8_t wMenuData_ScrollingMenuItemFormat;
                        uint8_t wMenuData_ItemsPointerBank;
                        uint16_t wMenuData_ItemsPointerAddr;
                        uint8_t wMenuData_ScrollingMenuFunction1[3];
                        uint8_t wMenuData_ScrollingMenuFunction2[3];
                        uint8_t wMenuData_ScrollingMenuFunction3[3];
                    };
                };
                //union wMenuDataEnd
                //union wMoreMenuData
                //union w2DMenuData
                uint8_t w2DMenuCursorInitY;
                uint8_t w2DMenuCursorInitX;
                uint8_t w2DMenuNumRows;
                uint8_t w2DMenuNumCols;
                // bit 7: Disable checking of wMenuJoypadFilter
                // bit 6: Enable sprite animations
                // bit 5: Wrap around vertically
                // bit 4: Wrap around horizontally
                // bit 3: Set bit 7 in w2DMenuFlags2 and exit the loop if bit 5 is disabled and we tried to go too far down
                // bit 2: Set bit 7 in w2DMenuFlags2 and exit the loop if bit 5 is disabled and we tried to go too far up
                // bit 1: Set bit 7 in w2DMenuFlags2 and exit the loop if bit 4 is disabled and we tried to go too far left
                // bit 0: Set bit 7 in w2DMenuFlags2 and exit the loop if bit 4 is disabled and we tried to go too far right
                uint8_t w2DMenuFlags1;
                uint8_t w2DMenuFlags2;
                uint8_t w2DMenuCursorOffsets;
                uint8_t wMenuJoypadFilter;
                //union w2DMenuDataEnd
                uint8_t wMenuCursorY;
                uint8_t wMenuCursorX;
                uint8_t wCursorOffCharacter;
                uint16_t wCursorCurrentTile;
                uint8_t skip_57[3];
                //union wMoreMenuDataEnd
                uint8_t wOverworldDelay;
                uint8_t wTextDelayFrames;
                uint8_t wVBlankOccurred;
                uint8_t wPredefID;
                uint16_t wPredefHL;
                uint16_t wPredefAddress;
                uint16_t wFarCallBC;
                uint8_t wUnusedLinkCommunicationByte;
                // bit 0: game timer paused
                // bit 7: something mobile
                uint8_t wGameTimerPaused;
                uint8_t skip_58[1];
                // bits 4, 6, or 7 can be used to disable joypad input
                // bit 4
                // bit 6: ongoing mon faint animation
                // bit 7: ongoing sgb data transfer
                uint8_t wJoypadDisable;
                uint8_t skip_59[1];
                // 0 not in BattleTower-Battle
                // 1 BattleTower-Battle
                uint8_t wInBattleTowerBattle;
                uint8_t skip_60[1];
                uint16_t wFXAnimID;
                uint8_t wPlaceBallsX;
                uint8_t wPlaceBallsY;
                uint8_t wTileAnimationTimer;
                // palette backups?
                uint8_t wBGP;
                uint8_t wOBP0;
                uint8_t wOBP1;
                uint8_t wNumHits;
                uint8_t skip_61[1];
                // bit 0-2: number of frames to delay when printing text
                //   fast 1; mid 3; slow 5
                // bit 3: ?
                // bit 4: no text delay
                // bit 5: stereo off/on
                // bit 6: battle style shift/set
                // bit 7: battle scene off/on
                uint8_t wOptions;
                uint8_t wSaveFileExists;
                // bits 0-2: textbox frame 0-7
                uint8_t wTextboxFrame;
                // bit 0: 1-frame text delay
                // bit 4: no text delay
                uint8_t wTextboxFlags;
                // bit 0-6: brightness
                //   lightest: $00
                //   lighter:  $20
                //   normal:   $40 (default)
                //   darker:   $60
                //   darkest:  $7F
                uint8_t wGBPrinterBrightness;
                // bit 1: menu account off/on
                uint8_t wOptions2;
                uint8_t skip_62[2];
                // Time buffer, for counting the amount of time since
                // an event began.
                //union wOptionsEnd
                uint8_t wSecondsSince;
                uint8_t wMinutesSince;
                uint8_t wHoursSince;
                uint8_t wDaysSince;
            };
        };
    };
    // bank 1
    union {
        uint8_t wram1[0x1000];
        struct {
            // WRAM 1
            struct {
                // WRAMX
                // a $540-byte buffer that continues past this SECTION
                //union wGBCOnlyDecompressBuffer
                // This selected the title screen animation (fire/notes) in pokegold-spaceworld.
                uint8_t wBetaTitleSequenceOpeningType;
                uint8_t wDefaultSpawnpoint;
            };
            // Miscellaneous WRAM 1
            struct {
                union {
                    struct {
                        // WRAMX
                        // mon buffer
                        uint8_t wBufferMonNickname[MON_NAME_LENGTH];
                        uint8_t wBufferMonOT[NAME_LENGTH];
                        struct PartyMon wBufferMon;
                        uint8_t skip_63[8];
                        uint8_t wMonOrItemNameBuffer[NAME_LENGTH];
                        uint8_t skip_64[NAME_LENGTH];
                    };
                    struct {
                        // WRAMX
                        // poke seer
                        uint8_t wSeerAction;
                        uint8_t wSeerNickname[MON_NAME_LENGTH];
                        uint8_t wSeerCaughtLocation[17];
                        uint8_t wSeerTimeOfDay[NAME_LENGTH];
                        uint8_t wSeerOT[NAME_LENGTH];
                        uint8_t wSeerOTGrammar;
                        uint8_t wSeerCaughtLevelString[4];
                        uint8_t wSeerCaughtLevel;
                        uint8_t wSeerCaughtData;
                        uint8_t wSeerCaughtGender;
                    };
                    struct {
                        // WRAMX
                        // mail temp storage
                        //union wTempMail
                        struct MailMsg wTempMail;
                        // mailmsg
                        // wTempMail
                    };
                    struct {
                        // WRAMX
                        // bug-catching contest
                        // struct BugContestWinner wBugContestResults;
                        // bugcontestwinner
                        // wBugContestSecondPlace
                        // bugcontestwinner
                        // wBugContestThirdPlace
                        struct BugContestWinner wBugContestWinners[3];
                        // union wBugContestWinnersEnd;
                        struct BugContestWinner wBugContestTemp;
                        uint8_t skip_65[4];
                        uint8_t wBugContestWinnerName[NAME_LENGTH];
                    };
                    struct {
                        // WRAMX
                        // mart items
                        uint8_t wMartItem1BCD[3];
                        uint8_t wMartItem2BCD[3];
                        uint8_t wMartItem3BCD[3];
                        uint8_t wMartItem4BCD[3];
                        uint8_t wMartItem5BCD[3];
                        uint8_t wMartItem6BCD[3];
                        uint8_t wMartItem7BCD[3];
                        uint8_t wMartItem8BCD[3];
                        uint8_t wMartItem9BCD[3];
                        uint8_t wMartItem10BCD[3];
                    };
                    struct {
                        // WRAMX
                        // town map data
                        uint8_t wTownMapPlayerIconLandmark;
                        union {
                            struct {
                                uint8_t wTownMapCursorLandmark;
                                uint16_t wTownMapCursorObjectPointer;
                            };
                            struct {
                                uint16_t wTownMapCursorCoordinates;
                                uint8_t wStartFlypoint;
                                uint8_t wEndFlypoint;
                            };
                        };
                    };
                    struct {
                        // WRAMX
                        // phone call data
                        uint8_t wPhoneScriptBank;
                        uint16_t wPhoneCaller;
                    };
                    struct {
                        // WRAMX
                        // radio data
                        uint8_t wCurRadioLine;
                        uint8_t wNextRadioLine;
                        uint8_t wRadioTextDelay;
                        uint8_t wNumRadioLinesPrinted;
                        uint8_t wOaksPKMNTalkSegmentCounter;
                        uint8_t skip_66[5];
                        uint8_t wRadioText[2 * SCREEN_WIDTH];
                    };
                    struct {
                        // WRAMX
                        // lucky number show
                        uint8_t wLuckyNumberDigitsBuffer[5];
                    };
                    struct {
                        // WRAMX
                        // movement buffer data
                        uint8_t wMovementBufferCount;
                        uint8_t wMovementBufferObject;
                        uint8_t wUnusedMovementBufferBank;
                        uint16_t wUnusedMovementBufferPointer;
                        uint8_t wMovementBuffer[55];
                    };
                    struct {
                        // WRAMX
                        // box printing
                        uint8_t wWhichBoxMonToPrint;
                        uint8_t wFinishedPrintingBox;
                        uint16_t wAddrOfBoxToPrint;
                        uint8_t wBankOfBoxToPrint;
                        uint8_t wWhichBoxToPrint;
                    };
                    struct {
                        // WRAMX
                        // Unown printing
                        uint8_t wPrintedUnownTileSource[1 * LEN_2BPP_TILE];
                        uint8_t wPrintedUnownTileDest[1 * LEN_2BPP_TILE];
                    };
                    struct {
                        // WRAMX
                        // trainer HUD data
                        uint8_t skip_67[1];
                        uint8_t wPlaceBallsDirection;
                        uint8_t wTrainerHUDTiles[4];
                    };
                    struct {
                        // WRAMX
                        // mobile participant nicknames
                        uint8_t skip_68[4];
                        uint8_t wMobileParticipant1Nickname[NAME_LENGTH_JAPANESE];
                        uint8_t wMobileParticipant2Nickname[NAME_LENGTH_JAPANESE];
                        uint8_t wMobileParticipant3Nickname[NAME_LENGTH_JAPANESE];
                    };
                    struct {
                        // WRAMX
                        // battle exp gain
                        uint8_t wExperienceGained[3];
                    };
                    struct {
                        // WRAMX
                        // earthquake data buffer
                        uint8_t wEarthquakeMovementDataBuffer[5];
                    };
                    struct {
                        // WRAMX
                        // switching items in pack
                        uint8_t wSwitchItemBuffer[2];
                        // may store 1 or 2 bytes
                    };
                    struct {
                        // WRAMX
                        // switching pokemon in party
                        // may store NAME_LENGTH, PARTYMON_STRUCT_LENGTH, or MAIL_STRUCT_LENGTH bytes
                        uint8_t wSwitchMonBuffer[48];
                    };
                    struct {
                        // WRAMX
                        // giving pokemon mail
                        uint8_t wMonMailMessageBuffer[MAIL_MSG_LENGTH + 1];
                    };
                    struct {
                        // WRAMX
                        // bill's pc
                        union {
                            struct {
                                uint8_t wBoxNameBuffer[BOX_NAME_LENGTH];
                            };
                            struct {
                                uint8_t skip_69[1];
                                uint8_t wBillsPCTempListIndex;
                                uint8_t wBillsPCTempBoxCount;
                            };
                        };
                    };
                    struct {
                        // WRAMX
                        // prof. oak's pc
                        uint8_t wTempPokedexSeenCount;
                        uint8_t wTempPokedexCaughtCount;
                    };
                    struct {
                        // WRAMX
                        // player's room pc
                        union {
                            struct {
                                uint8_t wDecoNameBuffer[ITEM_NAME_LENGTH];
                            };
                            struct {
                                uint8_t wNumOwnedDecoCategories;
                                uint8_t wOwnedDecoCategories[16];
                            };
                        };
                    };
                    struct {
                        // WRAMX
                        // trade
                        uint8_t wCurTradePartyMon;
                        uint8_t wCurOTTradePartyMon;
                        uint8_t wBufferTrademonNickname[MON_NAME_LENGTH];
                    };
                    struct {
                        // WRAMX
                        // link battle record data
                        //union wLinkBattleRecordBuffer
                        uint8_t wLinkBattleRecordName[NAME_LENGTH];
                        uint16_t wLinkBattleRecordWins;
                        uint16_t wLinkBattleRecordLosses;
                        uint16_t wLinkBattleRecordDraws;
                    };
                    struct {
                        // WRAMX
                        // miscellaneous
                        union {
                            uint8_t wTempDayOfWeek;
                            uint8_t wPrevPartyLevel;
                            uint8_t wCurBeatUpPartyMon;
                            uint8_t wUnownPuzzleCornerTile;
                            uint8_t wKeepSevenBiasChance;
                            uint8_t wPokeFluteCuredSleep;
                            uint8_t wTempRestorePPItem;
                            uint8_t wApricorns;
                            uint8_t wSuicuneFrame;
                        };
                    };
                    struct {
                        // WRAMX
                        // debug color picker
                        uint8_t wDebugColorIsTrainer;
                        uint8_t wDebugColorIsShiny;
                        uint8_t wDebugColorCurTMHM;
                    };
                    struct {
                        // WRAMX
                        // mobile?
                        uint8_t wd002[1];
                        uint8_t wd003[1];
                        uint8_t wd004[1];
                        uint8_t skip_70[3];
                        uint8_t wd008[2];
                        uint8_t skip_71[6];
                        uint8_t wd010[1];
                        uint8_t wd011[1];
                        uint8_t wd012[1];
                        uint8_t wd013[1];
                        uint8_t wd014[2];
                        uint8_t skip_72[1];
                        uint8_t wd017[1];
                        uint8_t wd018[1];
                        uint8_t wd019[1];
                        uint8_t skip_73[19];
                        uint8_t wd02d[1];
                        uint8_t wd02e[1];
                        uint8_t wd02f[1];
                        uint8_t wd030[1];
                        uint8_t wd031[1];
                        uint8_t wd032[1];
                        uint8_t wd033[1];
                        uint8_t wd034[2];
                        uint8_t wd036[2];
                    };
                    struct {
                        // WRAMX
                        // Every previous SECTION UNION takes up 60 or fewer bytes,
                        // except the initial "mon buffer" one.
                        uint8_t skip_74[60];
                        union {
                            struct {
                                // trainer data
                                uint8_t wSeenTrainerBank;
                                uint8_t wSeenTrainerDistance;
                                uint8_t wSeenTrainerDirection;
                                //union wTempTrainer
                                uint16_t wTempTrainerEventFlag;
                                uint8_t wTempTrainerClass;
                                uint8_t wTempTrainerID;
                                uint16_t wSeenTextPointer;
                                uint16_t wWinTextPointer;
                                uint16_t wLossTextPointer;
                                uint16_t wScriptAfterPointer;
                                uint8_t wRunningTrainerBattleScript;
                                //void wTempTrainerEnd
                            };
                            struct {
                                // menu items list
                                uint8_t wMenuItemsList[16];
                                //void wMenuItemsListEnd
                            };
                            struct {
                                // fruit tree data
                                uint8_t wCurFruitTree;
                                uint8_t wCurFruit;
                            };
                            struct {
                                // item ball data
                                //union wItemBallData
                                uint8_t wItemBallItemID;
                                uint8_t wItemBallQuantity;
                                //void wItemBallDataEnd
                            };
                            struct {
                                // hidden item data
                                //union wHiddenItemData
                                uint16_t wHiddenItemEvent;
                                uint8_t wHiddenItemID;
                                //void wHiddenItemDataEnd
                            };
                            struct {
                                // elevator data
                                //union wElevatorData
                                uint8_t wElevatorPointerBank;
                                uint16_t wElevatorPointer;
                                uint8_t wElevatorOriginFloor;
                                //void wElevatorDataEnd
                            };
                            struct {
                                // coord event data
                                //union wCurCoordEvent
                                uint8_t wCurCoordEventSceneID;
                                uint8_t wCurCoordEventMapY;
                                uint8_t wCurCoordEventMapX;
                                uint8_t skip_75[1];
                                uint16_t wCurCoordEventScriptAddr;
                            };
                            struct {
                                // BG event data
                                //union wCurBGEvent
                                uint8_t wCurBGEventYCoord;
                                uint8_t wCurBGEventXCoord;
                                uint8_t wCurBGEventType;
                                uint16_t wCurBGEventScriptAddr;
                            };
                            struct {
                                // mart data
                                uint8_t wMartType;
                                uint8_t wMartPointerBank;
                                uint16_t wMartPointer;
                                uint8_t wMartJumptableIndex;
                                uint8_t wBargainShopFlags;
                            };
                            struct {
                                // player movement data
                                union {
                                    uint8_t wCurInput;
                                    uint8_t wFacingTileID;
                                };
                                uint8_t wWalkingIntoNPC;
                                uint8_t wWalkingIntoLand;
                                uint8_t wWalkingIntoEdgeWarp;
                                uint8_t wMovementAnimation;
                                int8_t wWalkingDirection;
                                uint8_t wFacingDirection;
                                int8_t wWalkingX;
                                int8_t wWalkingY;
                                uint8_t wWalkingTile;
                                uint8_t skip_76[6];
                                uint8_t wPlayerTurningDirection;
                            };
                            struct {
                                // std script buffer
                                uint8_t skip_77[1];
                                uint8_t wJumpStdScriptBuffer[3];
                            };
                            struct {
                                // phone script data
                                uint8_t wCheckedTime;
                                uint8_t wPhoneListIndex;
                                uint8_t wNumAvailableCallers;
                                uint8_t wAvailableCallers[CONTACT_LIST_SIZE];
                            };
                            struct {
                                // phone caller contact
                                uint8_t skip_78[1];
                                uint8_t wCallerContact[PHONE_CONTACT_SIZE];
                            };
                            struct {
                                // backup menu data
                                uint8_t skip_79[7];
                                uint8_t wMenuCursorPositionBackup;
                                uint8_t wMenuScrollPositionBackup;
                            };
                            struct {
                                // poison step data
                                //union wPoisonStepData
                                uint8_t wPoisonStepFlagSum;
                                uint8_t wPoisonStepPartyFlags[PARTY_LENGTH];
                                //void wPoisonStepDataEnd
                            };
                        };
                        uint8_t skip_80[23];
                    };
                };
            };
            // More WRAM 1
            struct {
                // WRAMX
                uint8_t wTMHMMoveNameBackup[MOVE_NAME_LENGTH];
                uint8_t wStringBuffer1[STRING_BUFFER_LENGTH];
                uint8_t wStringBuffer2[STRING_BUFFER_LENGTH];
                uint8_t wStringBuffer3[STRING_BUFFER_LENGTH];
                uint8_t wStringBuffer4[STRING_BUFFER_LENGTH];
                uint8_t wStringBuffer5[STRING_BUFFER_LENGTH];
                uint8_t wBattleMenuCursorPosition;
                uint8_t skip_81[1];
                uint8_t wCurBattleMon;
                uint8_t wCurMoveNum;
                uint8_t wLastPocket;
                uint8_t wPCItemsCursor;
                uint8_t wPartyMenuCursor;
                uint8_t wItemsPocketCursor;
                uint8_t wKeyItemsPocketCursor;
                uint8_t wBallsPocketCursor;
                uint8_t wTMHMPocketCursor;
                uint8_t wPCItemsScrollPosition;
                uint8_t skip_82[1];
                uint8_t wItemsPocketScrollPosition;
                uint8_t wKeyItemsPocketScrollPosition;
                uint8_t wBallsPocketScrollPosition;
                uint8_t wTMHMPocketScrollPosition;
                union {
                    uint8_t wSwitchMon;
                    uint8_t wSwitchItem;
                    uint8_t wSwappingMove;
                    // mobile
                    uint8_t wd0e3;
                };
                uint8_t wMenuScrollPosition;
                uint8_t wMenuScrollPosition_skip[3];
                uint8_t wQueuedScriptBank;
                uint16_t wQueuedScriptAddr;
                uint8_t wNumMoves;
                union {
                    uint8_t wFieldMoveSucceeded;
                    uint8_t wItemEffectSucceeded;
                    // 0 - use move
                    // 1 - use item
                    // 2 - switch
                    uint8_t wBattlePlayerAction;
                    uint8_t wSolvedUnownPuzzle;
                };
                // bit 0: overworld sprite updating on/off
                // bit 1: something to do with sprite updates
                // bit 6: something to do with text
                // bit 7: on when surf initiates
                //        flickers when climbing waterfall
                uint8_t wVramState;
                // WIN, LOSE, or DRAW
                // bit 6: caught celebi
                // bit 7: box full
                uint8_t wBattleResult;
                uint8_t wUsingItemWithSelect;
                union {
                    struct {
                        // mart data
                        uint8_t wCurMartCount;
                        uint8_t wCurMartItems[15];
                    };
                    struct {
                        // elevator data
                        uint8_t wCurElevatorCount;
                        uint8_t wCurElevatorFloors[15];
                    };
                    struct {
                        // mailbox data
                        uint8_t wCurMessageScrollPosition;
                        uint8_t wCurMessageIndex;
                        uint8_t wMailboxCount;
                        uint8_t wMailboxItems[MAILBOX_CAPACITY];
                    };
                };
                uint16_t wListPointer;
                uint16_t wUnusedNamesPointer;
                uint16_t wItemAttributesPointer;
                uint8_t wCurItem;
                union {
                    uint8_t wCurItemQuantity;
                    uint8_t wMartItemID;
                };
                uint8_t wCurPartySpecies;
                // contains which monster in a party
                // is being dealt with at the moment
                // 0-5
                uint8_t wCurPartyMon;
                // 0: Enemy
                // 1: Player
                // 2: Party Menu
                uint8_t wWhichHPBar;
                // 0: Take from PC
                // 1: Put into PC
                // 2: Take from Day-Care
                // 3: Put into Day-Care
                uint8_t wPokemonWithdrawDepositParameter;
                uint8_t wItemQuantityChange;
                uint8_t wItemQuantity;
                struct PartyMon wTempMon;
                uint8_t wSpriteFlags;
                uint8_t wHandlePlayerStep;
                uint8_t skip_83[1];
                uint8_t wPartyMenuActionText;
                uint8_t wItemAttributeValue;
                uint8_t wCurPartyLevel;
                uint8_t wScrollingMenuListSize;
                uint8_t skip_84[1];
                // used when following a map warp
                uint8_t wNextWarp;
                uint8_t wNextMapGroup;
                uint8_t wNextMapNumber;
                uint8_t wPrevWarp;
                uint8_t wPrevMapGroup;
                uint8_t wPrevMapNumber;
                uint8_t wPlayerBGMapOffsetX;
                // used in FollowNotExact; unit is pixels
                uint8_t wPlayerBGMapOffsetY;
                // used in FollowNotExact; unit is pixels
                // Player movement
                uint8_t wPlayerStepVectorX;
                uint8_t wPlayerStepVectorY;
                uint8_t wPlayerStepFlags;
                uint8_t wPlayerStepDirection;
                uint16_t wBGMapAnchor;
                union {
                    struct {
                        uint8_t wUsedSprites[SPRITE_GFX_LIST_CAPACITY * 2];
                        //void wUsedSpritesEnd
                    };
                    struct {
                        uint8_t skip_85[31];
                        uint8_t wd173;
                        // related to command queue type 3
                    };
                };
                uint16_t wOverworldMapAnchor;
                uint8_t wMetatileStandingY;
                uint8_t wMetatileStandingX;
                //union wMapPartial
                union {
                    uint8_t wMapPartial;
                    uint8_t wMapAttributesBank;
                };
                uint8_t wMapTileset;
                uint8_t wEnvironment;
                uint16_t wMapAttributesPointer;
                //union wMapPartialEnd
                //union wMapAttributes
                uint8_t wMapBorderBlock;
                // width/height are in blocks (2x2 walkable tiles, 4x4 graphics tiles)
                uint8_t wMapHeight;
                uint8_t wMapWidth;
                uint8_t wMapBlocksBank;
                uint16_t wMapBlocksPointer;
                uint8_t wMapScriptsBank;
                uint16_t wMapScriptsPointer;
                uint16_t wMapEventsPointer;
                // bit set
                uint8_t wMapConnections;
                //union wMapAttributesEnd
                struct MapConnection wNorthMapConnection;
                struct MapConnection wSouthMapConnection;
                struct MapConnection wWestMapConnection;
                struct MapConnection wEastMapConnection;
                //union wTileset
                uint8_t wTilesetBank;
                uint16_t wTilesetAddress;
                uint8_t wTilesetBlocksBank;
                uint16_t wTilesetBlocksAddress;
                uint8_t wTilesetCollisionBank;
                uint16_t wTilesetCollisionAddress;
                uint16_t wTilesetAnim;
                // bank 3f
                uint8_t skip_86[2];
                // unused
                uint16_t wTilesetPalettes;
                // bank 3f
                //union wTilesetEnd
                // assert
                // wTilesetEnd
                // -
                // wTileset
                // TILESET_LENGTH
                uint8_t wEvolvableFlags[((PARTY_LENGTH) + 7) / 8];
                uint8_t wForceEvolution;
                union {
                    struct {
                        // general-purpose HP buffers
                        uint16_t wHPBuffer1;
                        uint16_t wHPBuffer2;
                        uint16_t wHPBuffer3;
                    };
                    struct {
                        // HP bar animations
                        uint16_t wCurHPAnimMaxHP;
                        uint16_t wCurHPAnimOldHP;
                        uint16_t wCurHPAnimNewHP;
                        uint8_t wCurHPAnimPal;
                        uint8_t wCurHPBarPixels;
                        uint8_t wNewHPBarPixels;
                        uint16_t wCurHPAnimDeltaHP;
                        uint8_t wCurHPAnimLowHP;
                        uint8_t wCurHPAnimHighHP;
                    };
                    struct {
                        // move AI
                        uint8_t wEnemyAIMoveScores[NUM_MOVES];
                    };
                    struct {
                        // switch AI
                        uint8_t wEnemyEffectivenessVsPlayerMons[((PARTY_LENGTH) + 7) / 8];
                        uint8_t wPlayerEffectivenessVsEnemyMons[((PARTY_LENGTH) + 7) / 8];
                    };
                    struct {
                        // battle HUD
                        uint8_t wBattleHUDTiles[PARTY_LENGTH];
                    };
                    struct {
                        // thrown ball data
                        uint8_t wFinalCatchRate;
                        uint8_t wThrownBallWobbleCount;
                    };
                    struct {
                        // evolution data
                        uint8_t wEvolutionOldSpecies;
                        uint8_t wEvolutionNewSpecies;
                        uint8_t wEvolutionPicOffset;
                        uint8_t wEvolutionCanceled;
                    };
                    struct {
                        // experience
                        uint8_t wExpToNextLevel[3];
                    };
                    struct {
                        // PP Up
                        uint8_t wPPUpPPBuffer[NUM_MOVES];
                    };
                    struct {
                        // lucky number show
                        uint8_t wMonIDDigitsBuffer[5];
                    };
                    struct {
                        // mon submenu
                        uint8_t wMonSubmenuCount;
                        uint8_t wMonSubmenuItems[NUM_MONMENU_ITEMS + 1];
                    };
                    struct {
                        // field move data
                        //union wFieldMoveData
                        uint8_t wFieldMoveJumptableIndex;
                        union {
                            uint8_t wEscapeRopeOrDigType;
                            uint8_t wSurfingPlayerState;
                            uint8_t wFishingRodUsed;
                        };
                        uint16_t wCutWhirlpoolOverworldBlockAddr;
                        uint8_t wCutWhirlpoolReplacementBlock;
                        union {
                            uint8_t wCutWhirlpoolAnimationType;
                            uint8_t wStrengthSpecies;
                            uint8_t wFishingResult;
                        };
                        uint8_t skip_87[1];
                        //void wFieldMoveDataEnd
                    };
                    struct {
                        // hidden items
                        uint8_t wCurMapScriptBank;
                        uint8_t wRemainingBGEventCount;
                        uint8_t wBottomRightYCoord;
                        uint8_t wBottomRightXCoord;
                    };
                    struct {
                        // heal machine anim
                        uint8_t wHealMachineAnimType;
                        uint8_t wHealMachineTempOBP1;
                        uint8_t wHealMachineAnimState;
                    };
                    struct {
                        // decorations
                        uint8_t wCurDecoration;
                        uint8_t wSelectedDecorationSide;
                        uint8_t wSelectedDecoration;
                        uint8_t wOtherDecoration;
                        uint8_t wChangedDecorations;
                        uint8_t wCurDecorationCategory;
                    };
                    struct {
                        // withdraw/deposit items
                        uint8_t wPCItemQuantityChange;
                        uint8_t wPCItemQuantity;
                    };
                    struct {
                        // mail
                        uint16_t wCurMailAuthorID;
                        uint8_t wCurMailIndex;
                    };
                    struct {
                        // kurt
                        uint8_t wKurtApricornCount;
                        uint8_t wKurtApricornItems[10];
                    };
                    struct {
                        // tree mons
                        uint8_t wTreeMonCoordScore;
                        uint8_t wTreeMonOTIDScore;
                    };
                    struct {
                        // restart clock
                        uint8_t wRestartClockCurDivision;
                        uint8_t wRestartClockPrevDivision;
                        uint8_t wRestartClockUpArrowYCoord;
                        uint8_t wRestartClockDay;
                        uint8_t wRestartClockHour;
                        uint8_t wRestartClockMin;
                    };
                    struct {
                        // link
                        uint8_t skip_88[9];
                        uint8_t wLinkBattleRNPreamble[SERIAL_RN_PREAMBLE_LENGTH];
                        uint8_t wLinkBattleRNs[SERIAL_RNS_LENGTH];
                    };
                    struct {
                        // mobile
                        uint8_t wd1ea[1];
                        uint8_t wd1eb[1];
                        uint8_t wd1ec[1];
                        uint8_t wd1ed[1];
                        uint8_t wd1ee[1];
                        uint8_t wd1ef[1];
                        uint8_t wd1f0[1];
                        uint8_t wd1f1[1];
                        uint8_t wd1f2[1];
                        uint8_t wd1f3[1];
                        uint8_t skip_89[6];
                    };
                    struct {
                        // miscellaneous bytes
                        union {
                            uint8_t wSkipMovesBeforeLevelUp;
                            uint8_t wRegisteredPhoneNumbers;
                            uint8_t wListMovesLineSpacing;
                        };
                        uint8_t wSwitchMonTo;
                        uint8_t wSwitchMonFrom;
                        uint8_t skip_90[4];
                        uint8_t wCurEnemyItem;
                    };
                    struct {
                        // miscellaneous words
                        union {
                            uint16_t wBuySellItemPrice;
                            uint16_t wTempMysteryGiftTimer;
                            uint16_t wMagikarpLength;
                        };
                    };
                };
                uint8_t wTempEnemyMonSpecies;
                uint8_t wTempBattleMonSpecies;
                struct BattleMon wEnemyMon;
                uint8_t wEnemyMonBaseStats[NUM_EXP_STATS];
                uint8_t wEnemyMonCatchRate;
                uint8_t wEnemyMonBaseExp;
                //union wEnemyMonEnd
                // 0: overworld
                // 1: wild battle
                // 2: trainer battle
                uint8_t wBattleMode;
                uint8_t wTempWildMonSpecies;
                // class (Youngster, Bug Catcher, etc.) of opposing trainer
                // 0 if opponent is a wild Pokémon, not a trainer
                uint8_t wOtherTrainerClass;
                // BATTLETYPE_* values
                uint8_t wBattleType;
                // which trainer of the class that you're fighting
                // (Joey, Mikey, Albert, etc.)
                uint8_t wOtherTrainerID;
                uint8_t wForcedSwitch;
                uint8_t wTrainerClass;
                uint8_t wUnownLetter;
                uint8_t wMoveSelectionMenuType;
                // corresponds to the data/pokemon/base_stats/*.asm contents
                //union wCurBaseData
                uint8_t wBaseDexNo;
                union {
                    uint8_t wBaseStats[6];
                    struct {
                        uint8_t wBaseHP;
                        uint8_t wBaseAttack;
                        uint8_t wBaseDefense;
                        uint8_t wBaseSpeed;
                        uint8_t wBaseSpecialAttack;
                        uint8_t wBaseSpecialDefense;
                    };
                };
                //union wBaseType
                uint8_t wBaseType1;
                uint8_t wBaseType2;
                uint8_t wBaseCatchRate;
                uint8_t wBaseExp;
                //union wBaseItems
                uint8_t wBaseItem1;
                uint8_t wBaseItem2;
                uint8_t wBaseGender;
                uint8_t wBaseUnknown1;
                uint8_t wBaseEggSteps;
                uint8_t wBaseUnknown2;
                uint8_t wBasePicSize;
                uint16_t wBaseUnusedFrontpic;
                uint16_t wBaseUnusedBackpic;
                uint8_t wBaseGrowthRate;
                uint8_t wBaseEggGroups;
                uint8_t wBaseTMHM[((NUM_TM_HM_TUTOR) + 7) / 8];
                //union wCurBaseDataEnd
                // assert
                // wCurBaseDataEnd
                // -
                // wCurBaseData
                // BASE_DATA_SIZE
                uint16_t wCurDamage;
                uint8_t skip_91[2];
                uint8_t wMornEncounterRate;
                uint8_t wDayEncounterRate;
                uint8_t wNiteEncounterRate;
                uint8_t wWaterEncounterRate;
                uint8_t wListMoves_MoveIndicesBuffer[NUM_MOVES];
                uint8_t wPutativeTMHMMove;
                uint8_t wInitListType;
                uint8_t wBattleHasJustStarted;
                union {
                    uint8_t wNamedObjectIndex;
                    uint8_t wTextDecimalByte;
                    uint8_t wTempByteValue;
                    uint8_t wNumSetBits;
                    uint8_t wTypeMatchup;
                    uint8_t wCurType;
                    uint8_t wTempSpecies;
                    uint8_t wTempIconSpecies;
                    uint8_t wTempTMHM;
                    uint8_t wTempPP;
                    uint8_t wNextBoxOrPartyIndex;
                    uint8_t wChosenCableClubRoom;
                    uint8_t wBreedingCompatibility;
                    uint8_t wMoveGrammar;
                    uint8_t wApplyStatLevelMultipliersToEnemy;
                    uint8_t wUsePPUp;
                    // mobile
                    uint8_t wd265;
                };
                uint8_t wFailedToFlee;
                uint8_t wNumFleeAttempts;
                uint8_t wMonTriedToEvolve;
                uint8_t wTimeOfDay;
                uint8_t skip_92[1];
            };
            // Enemy Party
            struct {
                // WRAMX
                union {
                    struct {
                        uint16_t wPokedexShowPointerAddr;
                        uint8_t wPokedexShowPointerBank;
                        uint8_t skip_93[3];
                        uint16_t wd271;
                        // mobile
                    };
                    struct {
                        uint8_t wUnusedEggHatchFlag;
                    };
                    struct {
                        // enemy party
                        //union wOTPartyData
                        uint8_t wOTPlayerName[NAME_LENGTH];
                        uint16_t wOTPlayerID;
                        uint8_t skip_94[8];
                        uint8_t wOTPartyCount;
                        uint8_t wOTPartySpecies[PARTY_LENGTH];
                        uint8_t wOTPartyEnd;
                        // older code doesn't check PartyCount
                    };
                };
                union {
                    struct {
                        // ot party mons
                        // wOTPartyMon1 - wOTPartyMon6
                        //union wOTPartyMons
                        // for n, 1, PARTY_LENGTH + 1
                        // wOTPartyMon1 - wOTPartyMon6
                        struct PartyMon wOTPartyMon[(PARTY_LENGTH + 1) - 1];
                        // wOTPartyMon1OT - wOTPartyMon6OT
                        //union wOTPartyMonOTs
                        // for n, 1, PARTY_LENGTH + 1
                        uint8_t wOTPartyMonOT[(PARTY_LENGTH + 1) - 1][NAME_LENGTH];
                        // wOTPartyMon1Nickname - wOTPartyMon6Nickname
                        //union wOTPartyMonNicknames
                        // for n, 1, PARTY_LENGTH + 1
                        uint8_t wOTPartyMonNickname[(PARTY_LENGTH + 1) - 1][MON_NAME_LENGTH];
                        //void wOTPartyDataEnd
                    };
                    struct {
                        // catch tutorial dude pack
                        uint8_t wDudeNumItems;
                        uint8_t wDudeItems[2 * 4 + 1];
                        uint8_t wDudeNumKeyItems;
                        uint8_t wDudeKeyItems[18 + 1];
                        uint8_t wDudeNumBalls;
                        uint8_t wDudeBalls[2 * 4 + 1];
                    };
                };
                uint8_t skip_95[4];
                union {
                    // mobile
                    uint8_t wd430;
                    uint8_t wBattleAction;
                };
                uint8_t wLinkBattleSentAction;
                uint8_t wMapStatus;
                uint8_t wMapEventStatus;
                // bit 3: run deferred script
                uint8_t wScriptFlags;
                uint8_t skip_96[1];
                // bit 0: count steps
                // bit 1: coord events
                // bit 2: warps and connections
                // bit 4: wild encounters
                // bit 5: unknown
                uint8_t wScriptFlags2;
                uint8_t wScriptMode;
                uint8_t wScriptRunning;
                uint8_t wScriptBank;
                uint16_t wScriptPos;
                uint8_t wScriptStackSize;
                uint8_t wScriptStack[3 * 5];
                uint8_t skip_97[1];
                uint8_t wScriptDelay;
                union {
                    uint8_t wDeferredScriptBank;
                    uint8_t wScriptTextBank;
                };
                union {
                    uint16_t wDeferredScriptAddr;
                    uint16_t wScriptTextAddr;
                };
                uint8_t skip_98[1];
                uint8_t wWildEncounterCooldown;
                uint16_t wXYComparePointer;
                uint8_t skip_99[4];
                uint8_t wBattleScriptFlags;
                uint8_t skip_100[1];
                // bit 7: if set, cancel wPlayerAction
                // bit 6: RefreshMapSprites doesn't reload player sprite
                // bit 5: if set, set facing according to bits 0-1
                // bit 2: female player has been transformed into male
                // bits 0-1: direction facing
                uint8_t wPlayerSpriteSetupFlags;
                uint8_t wMapReentryScriptQueueFlag;
                uint8_t wMapReentryScriptBank;
                uint16_t wMapReentryScriptAddress;
                uint8_t skip_101[4];
                uint8_t wTimeCyclesSinceLastCall;
                uint8_t wReceiveCallDelay_MinsRemaining;
                uint8_t wReceiveCallDelay_StartTime[3];
                uint8_t skip_102[3];
                uint8_t wBugContestMinsRemaining;
                uint8_t wBugContestSecsRemaining;
                uint8_t skip_103[2];
                uint8_t wMapStatusEnd[2];
                //union wCrystalData
                // bit 0:
                //	0 male
                //	1 female
                uint8_t wPlayerGender;
                uint8_t wd473[1];
                uint8_t wd474[1];
                uint8_t wd475[1];
                uint8_t wd476[1];
                uint8_t wd477[1];
                uint8_t wd478[1];
                //union wCrystalDataEnd
                uint8_t wd479[2];
                //union wGameData
                //union wPlayerData
                uint16_t wPlayerID;
                uint8_t wPlayerName[NAME_LENGTH];
                uint8_t wMomsName[NAME_LENGTH];
                uint8_t wRivalName[NAME_LENGTH];
                uint8_t wRedsName[NAME_LENGTH];
                uint8_t wGreensName[NAME_LENGTH];
                uint8_t wSavedAtLeastOnce;
                uint8_t wSpawnAfterChampion;
                // init time set at newgame
                uint8_t wStartDay;
                uint8_t wStartHour;
                uint8_t wStartMinute;
                uint8_t wStartSecond;
                uint8_t wRTC[4];
                uint8_t skip_104[4];
                // bit 7: dst
                uint8_t wDST;
                // used only for BANK(wGameTime)
                //union wGameTime
                uint8_t wGameTimeCap;
                uint16_t wGameTimeHours;
                uint8_t wGameTimeMinutes;
                uint8_t wGameTimeSeconds;
                uint8_t wGameTimeFrames;
                uint8_t skip_105[2];
                uint8_t wCurDay;
                uint8_t skip_106[1];
                uint8_t wObjectFollow_Leader;
                uint8_t wObjectFollow_Follower;
                uint8_t wCenteredObject;
                uint8_t wFollowerMovementQueueLength;
                uint8_t wFollowMovementQueue[5];
                //union wObjectStructs
                struct Object wPlayerStruct;
                // player is object struct 0
                // wObjectStruct1 - wObjectStruct12
                // for n, 1, NUM_OBJECT_STRUCTS
                struct Object wObjectStruct[(NUM_OBJECT_STRUCTS) - 1];
                uint8_t wCmdQueue[CMDQUEUE_CAPACITY * CMDQUEUE_ENTRY_SIZE];
                uint8_t skip_107[40];
                //union wMapObjects
                struct MapObject wPlayerObject;
                // player is map object 0
                // wMap1Object - wMap15Object
                // for n, 1, NUM_OBJECTS
                struct MapObject wMapObject[(NUM_OBJECTS) - 1];
                uint8_t wObjectMasks[NUM_OBJECTS];
                uint8_t wVariableSprites[0x100 - SPRITE_VARS];
                uint8_t wEnteredMapFromContinue;
                uint8_t skip_108[2];
                uint8_t wTimeOfDayPal;
                uint8_t skip_109[4];
                uint8_t wTimeOfDayPalFlags;
                uint8_t wTimeOfDayPalset;
                uint8_t wCurTimeOfDay;
                uint8_t skip_110[1];
                uint16_t wSecretID;
                // bit 0: pokedex
                // bit 1: unown dex
                // bit 2: flash
                // bit 3: caught pokerus
                // bit 4: rocket signal
                // bit 5: wild encounters on/off
                // bit 6: hall of fame
                // bit 7: bug contest on
                uint8_t wStatusFlags;
                // bit 0: rockets
                // bit 1: safari game (unused)
                // bit 2: bug contest timer
                // bit 3: unused
                // bit 4: bike shop call
                // bit 5: can use sweet scent
                // bit 6: reached goldenrod
                // bit 7: rockets in mahogany
                uint8_t wStatusFlags2;
                uint8_t wMoney[3];
                uint8_t wMomsMoney[3];
                // bit 0: saving some money
                // bit 1: saving half money (unused)
                // bit 2: saving all money (unused)
                // bit 7: active
                uint8_t wMomSavingMoney;
                uint16_t wCoins;
                //union wBadges
                uint8_t wJohtoBadges[((NUM_JOHTO_BADGES) + 7) / 8];
                uint8_t wKantoBadges[((NUM_KANTO_BADGES) + 7) / 8];
                uint8_t wTMsHMs[NUM_TMS + NUM_HMS];
                uint8_t wNumItems;
                item_t wItems[MAX_ITEMS * 2 + 1];
                uint8_t wNumKeyItems;
                item_t wKeyItems[MAX_KEY_ITEMS + 1];
                uint8_t wNumBalls;
                item_t wBalls[MAX_BALLS * 2 + 1];
                uint8_t wNumPCItems;
                item_t wPCItems[MAX_PC_ITEMS * 2 + 1];
                // bit 0: map
                // bit 1: radio
                // bit 2: phone
                // bit 3: expn
                // bit 7: on/off
                uint8_t wPokegearFlags;
                uint8_t wRadioTuningKnob;
                uint8_t wLastDexMode;
                uint8_t skip_111[1];
                uint8_t wWhichRegisteredItem;
                uint8_t wRegisteredItem;
                uint8_t wPlayerState;
                uint8_t wHallOfFameCount;
                uint8_t skip_112[1];
                uint8_t wTradeFlags[((NUM_NPC_TRADES) + 7) / 8];
                uint8_t skip_113[1];
                uint8_t wMooMooBerries;
                uint8_t wUndergroundSwitchPositions;
                uint8_t wFarfetchdPosition;
                uint8_t skip_114[13];
                // map scene ids
                uint8_t wPokecenter2FSceneID;
                uint8_t wTradeCenterSceneID;
                uint8_t wColosseumSceneID;
                uint8_t wTimeCapsuleSceneID;
                uint8_t wPowerPlantSceneID;
                uint8_t wCeruleanGymSceneID;
                uint8_t wRoute25SceneID;
                uint8_t wTrainerHouseB1FSceneID;
                uint8_t wVictoryRoadGateSceneID;
                uint8_t wSaffronMagnetTrainStationSceneID;
                uint8_t wRoute16GateSceneID;
                uint8_t wRoute17Route18GateSceneID;
                uint8_t wIndigoPlateauPokecenter1FSceneID;
                uint8_t wWillsRoomSceneID;
                uint8_t wKogasRoomSceneID;
                uint8_t wBrunosRoomSceneID;
                uint8_t wKarensRoomSceneID;
                uint8_t wLancesRoomSceneID;
                uint8_t wHallOfFameSceneID;
                uint8_t wRoute27SceneID;
                uint8_t wNewBarkTownSceneID;
                uint8_t wElmsLabSceneID;
                uint8_t wPlayersHouse1FSceneID;
                uint8_t wRoute29SceneID;
                uint8_t wCherrygroveCitySceneID;
                uint8_t wMrPokemonsHouseSceneID;
                uint8_t wRoute32SceneID;
                uint8_t wRoute35NationalParkGateSceneID;
                uint8_t wRoute36SceneID;
                uint8_t wRoute36NationalParkGateSceneID;
                uint8_t wAzaleaTownSceneID;
                uint8_t wGoldenrodGymSceneID;
                uint8_t wGoldenrodMagnetTrainStationSceneID;
                uint8_t wGoldenrodPokecenter1FSceneID;
                uint8_t wOlivineCitySceneID;
                uint8_t wRoute34SceneID;
                uint8_t wRoute34IlexForestGateSceneID;
                uint8_t wEcruteakTinTowerEntranceSceneID;
                uint8_t wWiseTriosRoomSceneID;
                uint8_t wEcruteakPokecenter1FSceneID;
                uint8_t wEcruteakGymSceneID;
                uint8_t wMahoganyTownSceneID;
                uint8_t wRoute42SceneID;
                uint8_t wCianwoodCitySceneID;
                uint8_t wBattleTower1FSceneID;
                uint8_t wBattleTowerBattleRoomSceneID;
                uint8_t wBattleTowerElevatorSceneID;
                uint8_t wBattleTowerHallwaySceneID;
                uint8_t wBattleTowerOutsideSceneID;
                uint8_t wRoute43GateSceneID;
                uint8_t wMountMoonSceneID;
                uint8_t wSproutTower3FSceneID;
                uint8_t wTinTower1FSceneID;
                uint8_t wBurnedTower1FSceneID;
                uint8_t wBurnedTowerB1FSceneID;
                uint8_t wRadioTower5FSceneID;
                uint8_t wRuinsOfAlphOutsideSceneID;
                uint8_t wRuinsOfAlphResearchCenterSceneID;
                uint8_t wRuinsOfAlphHoOhChamberSceneID;
                uint8_t wRuinsOfAlphKabutoChamberSceneID;
                uint8_t wRuinsOfAlphOmanyteChamberSceneID;
                uint8_t wRuinsOfAlphAerodactylChamberSceneID;
                uint8_t wRuinsOfAlphInnerChamberSceneID;
                uint8_t wMahoganyMart1FSceneID;
                uint8_t wTeamRocketBaseB1FSceneID;
                uint8_t wTeamRocketBaseB2FSceneID;
                uint8_t wTeamRocketBaseB3FSceneID;
                uint8_t wGoldenrodUndergroundSwitchRoomEntrancesSceneID;
                uint8_t wSilverCaveRoom3SceneID;
                uint8_t wVictoryRoadSceneID;
                uint8_t wDragonsDenB1FSceneID;
                uint8_t wDragonShrineSceneID;
                uint8_t wOlivinePortSceneID;
                uint8_t wVermilionPortSceneID;
                uint8_t wFastShip1FSceneID;
                uint8_t wFastShipB1FSceneID;
                uint8_t wMountMoonSquareSceneID;
                uint8_t wMobileTradeRoomSceneID;
                uint8_t wMobileBattleRoomSceneID;
                uint8_t skip_115[49];
                // fight counts
                uint8_t wJackFightCount;
                uint8_t wBeverlyFightCount;
                // unreferenced
                uint8_t wHueyFightCount;
                uint8_t wGavenFightCount;
                uint8_t wBethFightCount;
                uint8_t wJoseFightCount;
                uint8_t wReenaFightCount;
                uint8_t wJoeyFightCount;
                uint8_t wWadeFightCount;
                uint8_t wRalphFightCount;
                uint8_t wLizFightCount;
                uint8_t wAnthonyFightCount;
                uint8_t wToddFightCount;
                uint8_t wGinaFightCount;
                uint8_t wIrwinFightCount;
                // unreferenced
                uint8_t wArnieFightCount;
                uint8_t wAlanFightCount;
                uint8_t wDanaFightCount;
                uint8_t wChadFightCount;
                uint8_t wDerekFightCount;
                // unreferenced
                uint8_t wTullyFightCount;
                uint8_t wBrentFightCount;
                uint8_t wTiffanyFightCount;
                uint8_t wVanceFightCount;
                uint8_t wWiltonFightCount;
                uint8_t wKenjiFightCount;
                // unreferenced
                uint8_t wParryFightCount;
                uint8_t wErinFightCount;
                uint8_t skip_116[100];
                uint8_t wEventFlags[((NUM_EVENTS) + 7) / 8];
                uint8_t wCurBox;
                uint8_t skip_117[2];
                uint8_t wBoxNames[BOX_NAME_LENGTH * NUM_BOXES];
                // bit 2: forest is restless
                uint8_t wCelebiEvent;
                uint8_t skip_118[1];
                // bit 0: using strength
                // bit 1: always on bike
                // bit 2: downhill
                uint8_t wBikeFlags;
                uint8_t skip_119[1];
                // cleared along with wBikeFlags by ResetBikeFlags
                uint16_t wCurMapSceneScriptPointer;
                uint16_t wCurCaller;
                uint8_t wCurMapWarpCount;
                uint16_t wCurMapWarpsPointer;
                uint8_t wCurMapCoordEventCount;
                uint16_t wCurMapCoordEventsPointer;
                uint8_t wCurMapBGEventCount;
                uint16_t wCurMapBGEventsPointer;
                uint8_t wCurMapObjectEventCount;
                uint16_t wCurMapObjectEventsPointer;
                uint8_t wCurMapSceneScriptCount;
                uint16_t wCurMapSceneScriptsPointer;
                uint8_t wCurMapCallbackCount;
                uint16_t wCurMapCallbacksPointer;
                uint8_t skip_120[2];
                // Sprite id of each decoration
                uint8_t wDecoBed;
                uint8_t wDecoCarpet;
                uint8_t wDecoPlant;
                uint8_t wDecoPoster;
                uint8_t wDecoConsole;
                uint8_t wDecoLeftOrnament;
                uint8_t wDecoRightOrnament;
                uint8_t wDecoBigDoll;
                // Items bought from Mom
                uint8_t wWhichMomItem;
                uint8_t wWhichMomItemSet;
                uint8_t wMomItemTriggerBalance[3];
                uint16_t wDailyResetTimer;
                uint8_t wDailyFlags1;
                uint8_t wDailyFlags2;
                uint8_t wSwarmFlags;
                uint8_t skip_121[2];
                uint8_t wTimerEventStartDay;
                uint8_t skip_122[3];
                uint8_t wFruitTreeFlags[((NUM_FRUIT_TREES) + 7) / 8];
                uint8_t skip_123[2];
                uint16_t wLuckyNumberDayTimer;
                uint8_t skip_124[2];
                uint16_t wSpecialPhoneCallID;
                uint8_t skip_125[2];
                uint8_t wBugContestStartTime[4];
                // day, hour, min, sec
                uint8_t wUnusedTwoDayTimerOn;
                uint8_t wUnusedTwoDayTimer;
                uint8_t wUnusedTwoDayTimerStartDate;
                uint8_t skip_126[4];
                uint8_t wMobileOrCable_LastSelection;
                uint8_t wdc41[1];
                uint8_t wdc42[8];
                uint8_t wBuenasPassword;
                uint8_t wBlueCardBalance;
                uint8_t wDailyRematchFlags[4];
                uint8_t wDailyPhoneItemFlags[4];
                uint8_t wDailyPhoneTimeOfDayFlags[4];
                uint8_t wKenjiBreakTimer[2];
                // Kenji
                uint8_t wYanmaMapGroup;
                uint8_t wYanmaMapNumber;
                uint8_t wPlayerMonSelection[3];
                uint8_t wdc5f;
                uint8_t wdc60;
                uint8_t skip_127[18];
                uint8_t wStepCount;
                uint8_t wPoisonStepCount;
                uint8_t skip_128[2];
                uint8_t wHappinessStepCount;
                uint8_t skip_129[1];
                union {
                    uint8_t wParkBallsRemaining;
                    uint8_t wSafariBallsRemaining;
                };
                uint16_t wSafariTimeRemaining;
                uint8_t wPhoneList[CONTACT_LIST_SIZE + 1];
                uint8_t skip_130[22];
                uint8_t wLuckyNumberShowFlag;
                uint8_t skip_131[1];
                uint16_t wLuckyIDNumber;
                uint8_t wRepelEffect;
                // If a Repel is in use, it contains the nr of steps it's still active
                uint16_t wBikeStep;
                uint8_t wKurtApricornQuantity;
                //union wPlayerDataEnd
                //union wCurMapData
                uint8_t wVisitedSpawns[((NUM_SPAWNS) + 7) / 8];
                uint8_t wDigWarpNumber;
                uint8_t wDigMapGroup;
                uint8_t wDigMapNumber;
                // used on maps like second floor pokécenter, which are reused, so we know which
                // map to return to
                uint8_t wBackupWarpNumber;
                uint8_t wBackupMapGroup;
                uint8_t wBackupMapNumber;
                uint8_t skip_132[3];
                uint8_t wLastSpawnMapGroup;
                uint8_t wLastSpawnMapNumber;
                uint8_t wWarpNumber;
                uint8_t wMapGroup;
                uint8_t wMapNumber;
                uint8_t wYCoord;
                uint8_t wXCoord;
                uint8_t wScreenSave[SCREEN_META_WIDTH * SCREEN_META_HEIGHT];
                //void wCurMapDataEnd
            };
            // Party
            struct {
                // WRAMX
                //union wPokemonData
                uint8_t wPartyCount;
                species_t wPartySpecies[PARTY_LENGTH];
                uint8_t wPartyEnd;
                // older code doesn't check wPartyCount
                // wPartyMon1 - wPartyMon6
                //union wPartyMons
                // for n, 1, PARTY_LENGTH + 1
                // wPartyMon1 - wPartyMon6
                struct PartyMon wPartyMon[(PARTY_LENGTH + 1) - 1];
                // wPartyMon1OT - wPartyMon6OT
                //union wPartyMonOTs
                // for n, 1, PARTY_LENGTH + 1
                uint8_t wPartyMonOT[(PARTY_LENGTH + 1) - 1][NAME_LENGTH];
                // wPartyMon1Nickname - wPartyMon6Nickname
                //union wPartyMonNicknames
                // for n, 1, PARTY_LENGTH + 1
                uint8_t wPartyMonNickname[(PARTY_LENGTH + 1) - 1][MON_NAME_LENGTH];
                uint8_t wPartyMonNicknamesEnd[22];
                uint8_t wPokedexCaught[((NUM_POKEMON) + 7) / 8];
                //union wEndPokedexCaught
                uint8_t wPokedexSeen[((NUM_POKEMON) + 7) / 8];
                //union wEndPokedexSeen
                uint8_t wUnownDex[NUM_UNOWN];
                uint8_t wUnlockedUnowns;
                uint8_t wFirstUnownSeen;
                // bit 7: active
                // bit 6: egg ready
                // bit 5: monsters are compatible
                // bit 0: monster 1 in day-care
                uint8_t wDayCareMan;
                uint8_t wBreedMon1Nickname[MON_NAME_LENGTH];
                uint8_t wBreedMon1OT[NAME_LENGTH];
                struct BoxMon wBreedMon1;
                // bit 7: active
                // bit 0: monster 2 in day-care
                uint8_t wDayCareLady;
                uint8_t wStepsToEgg;
                //  z: yes
                // nz: no
                uint8_t wBreedMotherOrNonDitto;
                uint8_t wBreedMon2Nickname[MON_NAME_LENGTH];
                uint8_t wBreedMon2OT[NAME_LENGTH];
                struct BoxMon wBreedMon2;
                uint8_t wEggMonNickname[MON_NAME_LENGTH];
                uint8_t wEggMonOT[NAME_LENGTH];
                struct BoxMon wEggMon;
                uint8_t wBugContestSecondPartySpecies;
                struct PartyMon wContestMon;
                uint8_t wDunsparceMapGroup;
                uint8_t wDunsparceMapNumber;
                uint8_t wFishingSwarmFlag;
                struct Roamer wRoamMon1;
                struct Roamer wRoamMon2;
                struct Roamer wRoamMon3;
                uint8_t wRoamMons_CurMapNumber;
                uint8_t wRoamMons_CurMapGroup;
                uint8_t wRoamMons_LastMapNumber;
                uint8_t wRoamMons_LastMapGroup;
                uint8_t wBestMagikarpLengthFeet;
                uint8_t wBestMagikarpLengthInches;
                uint8_t wMagikarpRecordHoldersName[NAME_LENGTH];
                //union wPokemonDataEnd
                //void wGameDataEnd
            };
        };
    };
    // bank 2
    union {
        uint8_t wram2[0x1000];
        struct {
            // Pic Animations
            struct {
                // WRAMX
                // 20x18 grid of 8x8 tiles
                uint8_t wTempTilemap[SCREEN_WIDTH * SCREEN_HEIGHT];
                // PokeAnim data
                //union wPokeAnimStruct
                uint8_t wPokeAnimSceneIndex;
                uint16_t wPokeAnimPointer;
                uint8_t wPokeAnimSpecies;
                uint8_t wPokeAnimUnownLetter;
                uint8_t wPokeAnimSpeciesOrUnown;
                uint8_t wPokeAnimGraphicStartTile;
                uint16_t wPokeAnimCoord;
                uint8_t wPokeAnimFrontpicHeight;
                uint8_t wPokeAnimIdleFlag;
                uint8_t wPokeAnimSpeed;
                uint8_t wPokeAnimPointerBank;
                uint16_t wPokeAnimPointerAddr;
                uint8_t wPokeAnimFramesBank;
                uint16_t wPokeAnimFramesAddr;
                uint8_t wPokeAnimBitmaskBank;
                uint16_t wPokeAnimBitmaskAddr;
                uint8_t wPokeAnimFrame;
                uint8_t wPokeAnimJumptableIndex;
                uint8_t wPokeAnimRepeatTimer;
                uint8_t wPokeAnimCurBitmask;
                uint8_t wPokeAnimWaitCounter;
                uint8_t wPokeAnimCommand;
                uint8_t wPokeAnimParameter;
                uint8_t skip_133[1];
                uint8_t wPokeAnimBitmaskCurCol;
                uint8_t wPokeAnimBitmaskCurRow;
                uint8_t wPokeAnimBitmaskCurBit;
                uint8_t wPokeAnimBitmaskBuffer[7];
                uint8_t skip_134[2];
                //void wPokeAnimStructEnd
            };
        };
    };
    // bank 3
    union {
        uint8_t wram3[0x1000];
        struct {
            // Battle Tower RAM
            struct {
                // WRAMX
                uint8_t w3_d000[1];
                uint8_t w3_d001[1];
                uint8_t w3_d002[16];
                uint8_t w3_d012[0x6e];
                uint8_t w3_d080[1];
                uint8_t w3_d081[0xf];
                uint8_t w3_d090[0x70];
                //union w3_d100
                struct BattleTowerData wBT_OTTrainer;
                uint8_t skip_135[0x20];
                uint8_t wBT_TrainerTextIndex;
                uint8_t skip_136[1];
                struct BattleTowerData w3_d202;
                struct BattleTowerData w3_d2e2;
                struct BattleTowerData w3_d3c2;
                struct BattleTowerData w3_d4a2;
                struct BattleTowerData w3_d582;
                struct BattleTowerData w3_d662;
                union {
                    struct {
                        struct BattleTowerData w3_d742;
                    };
                    struct {
                        uint8_t skip_137[0xbe];
                        uint8_t w3_d800[BG_MAP_WIDTH * SCREEN_HEIGHT];
                    };
                    struct {
                        uint8_t skip_138[0xbe];
                        uint8_t wBTChoiceOfLvlGroup;
                        uint8_t skip_139[0x1];
                        uint8_t w3_d802[12];
                        uint8_t w3_d80e;
                        uint8_t skip_140[0x1];
                        uint8_t w3_d810[0x59];
                        uint8_t w3_d869[0x17];
                        uint8_t w3_d880[1];
                        uint8_t w3_d881[8];
                        uint8_t w3_d889[1];
                        uint8_t w3_d88a[4];
                        uint8_t w3_d88e[1];
                        uint8_t w3_d88f[4];
                        uint8_t w3_d893[1];
                        uint8_t w3_d894[1];
                        uint8_t w3_d895[11];
                        uint8_t w3_d8a0[1];
                        uint8_t w3_d8a1[1];
                        uint8_t w3_d8a2[1];
                        uint8_t w3_d8a3[1];
                    };
                };
                uint8_t skip_141[0x1c0];
                uint8_t w3_dc00[SCREEN_WIDTH * SCREEN_HEIGHT];
                union {
                    struct {
                        uint8_t w3_dd68[SCREEN_WIDTH * SCREEN_HEIGHT];
                        uint8_t skip_142[0x11c];
                        uint8_t w3_dfec[0x10];
                        uint8_t w3_dffc[4];
                    };
                    struct {
                        uint8_t skip_143[0x98];
                        uint8_t w3_de00[0x200];
                    };
                };
            };
        };
    };
    // bank 4
    union {
        uint8_t wram4[0x1000];
        struct {
            uint8_t dummy_w4_c000;
        };
    };
    // bank 5
    union {
        uint8_t wram5[0x1000];
        struct {
            // GBC Video
            struct {
                // WRAMX
                // ,
                // ALIGN
                // 8
                // LCD expects wLYOverrides to have an alignment of $100
                // eight 4-color palettes each
                // used only for BANK(wGBCPalettes)
                //union wGBCPalettes
                uint8_t wBGPals1[8 * PALETTE_SIZE];
                uint8_t wOBPals1[8 * PALETTE_SIZE];
                uint8_t wBGPals2[8 * PALETTE_SIZE];
                uint8_t wOBPals2[8 * PALETTE_SIZE];
                uint8_t wLYOverrides[SCREEN_HEIGHT_PX];
                uint8_t wLYOverridesEnd[1];
                // used only for BANK(wMagnetTrain)
                //union wMagnetTrain
                uint8_t wMagnetTrainDirection;
                uint8_t wMagnetTrainInitPosition;
                uint8_t wMagnetTrainHoldPosition;
                uint8_t wMagnetTrainFinalPosition;
                uint8_t wMagnetTrainPlayerSpriteInitX;
                uint8_t skip_144[106];
                uint8_t wLYOverridesBackup[SCREEN_HEIGHT_PX];
                //void wLYOverridesBackupEnd
            };
            uint8_t section_pad_2[112]; // Padding for GBC Video
            // Battle Animations
            struct {
                // WRAMX
                // wBattleAnimTileDict pairs keys with values
                // keys: ANIM_GFX_* indexes (taken from anim_*gfx arguments)
                // values: vTiles0 offsets
                uint8_t wBattleAnimTileDict[NUM_BATTLEANIMTILEDICT_ENTRIES * 2];
                // wAnimObject1 - wAnimObject10
                //union wActiveAnimObjects
                // for n, 1, NUM_ANIM_OBJECTS + 1
                // wAnimObject1 - wAnimObject10
                struct BattleAnim wAnimObject[(NUM_ANIM_OBJECTS + 1) - 1];
                // wBGEffect1 - wBGEffect5
                //union wActiveBGEffects
                // for n, 1, NUM_BG_EFFECTS + 1
                // wBGEffect1 - wBGEffect5
                struct BattleBGEffect wBGEffect[(NUM_BG_EFFECTS + 1) - 1];
                uint8_t wLastAnimObjectIndex;
                uint8_t wBattleAnimFlags;
                uint16_t wBattleAnimAddress;
                uint8_t wBattleAnimDelay;
                uint16_t wBattleAnimParent;
                uint8_t wBattleAnimLoops;
                uint8_t wBattleAnimVar;
                uint8_t wBattleAnimByte;
                uint8_t wBattleAnimOAMPointerLo;
                union {
                    struct {
                        uint8_t wBattleObjectTempID;
                        uint8_t wBattleObjectTempXCoord;
                        uint8_t wBattleObjectTempYCoord;
                        uint8_t wBattleObjectTempParam;
                    };
                    struct {
                        uint8_t wBattleBGEffectTempID;
                        uint8_t wBattleBGEffectTempJumptableIndex;
                        uint8_t wBattleBGEffectTempTurn;
                        uint8_t wBattleBGEffectTempParam;
                    };
                    struct {
                        uint8_t wBattleAnimTempOAMFlags;
                        uint8_t wBattleAnimTempFixY;
                        uint8_t wBattleAnimTempTileID;
                        uint8_t wBattleAnimTempXCoord;
                        uint8_t wBattleAnimTempYCoord;
                        uint8_t wBattleAnimTempXOffset;
                        uint8_t wBattleAnimTempYOffset;
                        uint8_t wBattleAnimTempFrameOAMFlags;
                        uint8_t wBattleAnimTempPalette;
                    };
                    struct {
                        union {
                            uint8_t wBattleAnimGFXTempTileID;
                            uint8_t wBattleAnimGFXTempPicHeight;
                        };
                    };
                    struct {
                        uint8_t wBattleSineWaveTempProgress;
                        uint8_t wBattleSineWaveTempOffset;
                        uint8_t wBattleSineWaveTempAmplitude;
                        uint8_t wBattleSineWaveTempTimer;
                    };
                    struct {
                        uint8_t wBattlePicResizeTempBaseTileID;
                        uint16_t wBattlePicResizeTempPointer;
                    };
                };
                union {
                    struct {
                        uint8_t skip_145[50];
                        //void wBattleAnimEnd
                    };
                    struct {
                        uint8_t wSurfWaveBGEffect[0x40];
                        //void wSurfWaveBGEffectEnd
                    };
                };
            };
            uint8_t section_pad_3[926]; // Padding for Battle Animations
            // Mobile RAM
            struct {
                // WRAMX
                uint8_t w5_d800[0x200];
                uint8_t w5_da00[0x200];
                uint8_t w5_dc00[0xd];
                uint8_t w5_dc0d[4];
                uint8_t w5_dc11[9];
                uint8_t w5_MobileOpponentBattleMessages[0xc];
                uint8_t w5_MobileOpponentBattleStartMessage[0xc];
                uint8_t w5_MobileOpponentBattleWinMessage[0xc];
                uint8_t w5_MobileOpponentBattleLossMessage[0xc];
            };
        };
    };
    // bank 6
    union {
        uint8_t wram6[0x1000];
        struct {
            // Scratch RAM
            struct {
                // WRAMX
                union {
                    struct {
                        uint8_t wScratchTilemap[BG_MAP_WIDTH * BG_MAP_HEIGHT];
                        uint8_t wScratchAttrmap[BG_MAP_WIDTH * BG_MAP_HEIGHT];
                    };
                    struct {
                        uint8_t wDecompressScratch[0x80 * LEN_2BPP_TILE];
                        uint8_t wDecompressEnemyFrontpic[0x80 * LEN_2BPP_TILE];
                    };
                    struct {
                        // unidentified uses
                        uint8_t w6_d000[0x1000];
                    };
                };
            };
        };
    };
    // bank 7
    union {
        uint8_t wram7[0x1000];
        struct {
            // Stack RAM
            struct {
                // WRAMX
                uint8_t wWindowStack[0x1000 - 1];
                uint8_t wWindowStackBottom[1];
            };
        };
    };
};

#pragma pack(pop)