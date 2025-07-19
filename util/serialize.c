#include "../constants.h"
#include "misc.h"
#include "serialize.h"
#include "../home/copy.h"
#include "../home/sram.h"
#include <memory.h>
#include <assert.h>
#include <stddef.h>

// Serialization functions
// Serializes runtime structs so that they match the layout of sram structs.
// This will allow us to reorder fields, add new fields, and make our runtime
// data unpacked, so that suiCune can support processors which can't read or
// write unaligned values.

// Some structs are still packed so that the wram struct is correctly sized.
// Serialization will hopefully make struct packing unnecessary.

enum FieldType {
    TY_U8,
    TY_U16LE,
    TY_U16BE,
    TY_SPECIES,
    TY_ITEM,
    TY_MOVE,
    TY_MAPID,
    TY_ITEMQUANTITY,
    TY_SKIP,
    TY_STRUCT = (1 << 8),
};

struct SerialField {
    int type;
    uint32_t offset;
    uint32_t count;
};

enum {
    STRUC_U8ITEM,
    STRUC_BOXMON,
    STRUC_PARTYMON,
    STRUC_NICKNAMEDMON,
    STRUC_TRADEMON,
    STRUC_ROAMER,
    STRUC_BATTLETOWERPARTYMON,
    STRUC_BATTLETOWERDATA,
    STRUC_OBJECT,
    STRUC_MAPOBJECT,
    STRUC_BOX,
    STRUC_MAILMSG,
    STRUC_OPTIONSDATA,
    STRUC_CURMAPDATA,
    STRUC_PLAYERDATA,
    STRUC_POKEMONDATA,
};

#define FLD_TYPE struct U8Item
#define FLD(ty, fld) {.type=ty, .offset=offsetof(FLD_TYPE, fld), .count = 1}
#define FLD_ARR(ty, fld, cnt) {.type=ty, .offset=offsetof(FLD_TYPE, fld), .count = cnt}
#define FLD_ARR_(ty, fld) {.type=ty, .offset=offsetof(FLD_TYPE, fld), .count = lengthof(((FLD_TYPE*)0)->fld)}
#define FLD_STR(struc, fld) {.type=TY_STRUCT | struc, .offset=offsetof(FLD_TYPE, fld), .count = 1}
#define FLD_STR_ARR(struc, fld, cnt) {.type=TY_STRUCT | struc, .offset=offsetof(FLD_TYPE, fld), .count = cnt}
#define FLD_STR_ARR_(struc, fld) {.type=TY_STRUCT | struc, .offset=offsetof(FLD_TYPE, fld), .count = lengthof(((FLD_TYPE*)0)->fld)}
#define FLD_OFFSET(ty, fld, off) {.type=ty, .offset=offsetof(FLD_TYPE, fld) + off, .count = 1}
const struct SerialField Struc_U8Item[] = {
    FLD(TY_U8, value),
    FLD(TY_ITEM, item),
};
#undef FLD_TYPE

#define FLD_TYPE struct BoxMon
const struct SerialField Struc_BoxMon[] = {
    FLD(TY_SPECIES, species),
    FLD(TY_ITEM, item),
    FLD_ARR_(TY_MOVE, moves),
    FLD(TY_U16LE, id),
    FLD_ARR_(TY_U8, exp),
    FLD_ARR_(TY_U16LE, statExp),
    FLD(TY_U16LE, DVs),
    FLD_ARR_(TY_U8, PP),
    FLD(TY_U8, happiness),
    FLD(TY_U8, pokerusStatus),
    FLD(TY_U8, caughtTimeLevel), // Crystal uses caught data, all in 2 bytes
    FLD(TY_U8, caughtGenderLocation), 
    FLD(TY_U8, level), 
};
#undef FLD_TYPE

#define FLD_TYPE struct PartyMon
const struct SerialField Struc_PartyMon[] = {
    FLD_STR(STRUC_BOXMON, mon),
    FLD(TY_U8, status),
    FLD(TY_U8, unused),
    FLD(TY_U16LE, HP),
    FLD(TY_U16LE, maxHP),
    FLD_ARR_(TY_U16LE, stats)
};
#undef FLD_TYPE

#define FLD_TYPE struct NicknamedMon
const struct SerialField Struc_NicknamedMon[] = {
    FLD_STR(STRUC_PARTYMON, pmon),
    FLD_ARR_(TY_U8, nickname),
};
#undef FLD_TYPE

#define FLD_TYPE struct TradeMon
const struct SerialField Struc_TradeMon[] = {
    FLD(TY_SPECIES, species),
    FLD_ARR_(TY_U8, speciesName),
    FLD_ARR_(TY_U8, nickname),
    FLD_ARR_(TY_U8, senderName),
    FLD_ARR_(TY_U8, otName),
    FLD(TY_U16LE, dvs),
    FLD(TY_U16LE, id),
    FLD(TY_U8, caughtData),
};
#undef FLD_TYPE

#define FLD_TYPE struct Roamer
const struct SerialField Struc_Roamer[] = {
    FLD(TY_SPECIES, species),
    FLD(TY_U8, level),
    FLD(TY_U8, mapId.mapGroup),
    FLD(TY_U8, mapId.mapNumber),
    FLD(TY_U8, HP),
    FLD(TY_U16LE, DVs),
};
#undef FLD_TYPE

#define FLD_TYPE struct BattleTowerPartyMon
const struct SerialField Struc_BattleTowerPartyMon[] = {
    FLD_STR(STRUC_PARTYMON, mon),
    FLD_ARR_(TY_U8, monName),
};
#undef FLD_TYPE

#define FLD_TYPE struct BattleTowerData
const struct SerialField Struc_BattleTowerData[] = {
    FLD_ARR_(TY_U8, name),
    FLD(TY_U8, trainerClass),
    FLD_STR_ARR_(STRUC_BATTLETOWERPARTYMON, party),
    FLD_ARR_(TY_U8, trainerData),
};
#undef FLD_TYPE

#define FLD_TYPE struct Object
const struct SerialField Struc_Object[] = {
    FLD(TY_U8, sprite),
    FLD(TY_U8, mapObjectIndex),
    FLD(TY_U8, spriteTile),
    FLD(TY_U8, movementType),
    FLD(TY_U8, flags1),
    FLD(TY_U8, flags2),
    FLD(TY_U8, palette),
    FLD(TY_U8, dirWalking),
    FLD(TY_U8, facing),
    FLD(TY_U8, stepType),
    FLD(TY_U8, stepDuration),
    FLD(TY_U8, action),
    FLD(TY_U8, stepFrame),
    FLD(TY_U8, facingStep),
    FLD(TY_U8, nextTile),
    FLD(TY_U8, standingTile),
    FLD(TY_U8, nextMapX),
    FLD(TY_U8, nextMapY),
    FLD(TY_U8, mapX),
    FLD(TY_U8, mapY),
    FLD(TY_U8, initX),
    FLD(TY_U8, initY),
    FLD(TY_U8, radius),
    FLD(TY_U8, spriteX),
    FLD(TY_U8, spriteY),
    FLD(TY_U8, spriteXOffset),
    FLD(TY_U8, spriteYOffset),
    FLD(TY_U8, movementByteIndex),
    FLD(TY_U8, field_1C),
    FLD(TY_U8, field_1D),
    FLD(TY_U8, field_1E),
    FLD(TY_U8, field_1F),
    FLD(TY_U8, range),
    FLD_ARR_(TY_U8, padding),
};
#undef FLD_TYPE

#define FLD_TYPE struct MapObject
const struct SerialField Struc_MapObject[] = {
    FLD(TY_U8, structId),
    FLD(TY_U8, sprite),
    FLD(TY_U8, objectYCoord),
    FLD(TY_U8, objectXCoord),
    FLD(TY_U8, objectMovement),
    FLD(TY_U8, objectRadius),
    FLD(TY_U8, objectHour),
    FLD(TY_U8, objectTimeOfDay),
    FLD(TY_U8, objectColor),
    FLD(TY_U8, objectRange),
    FLD(TY_U16LE, objectScript),
    FLD(TY_U16LE, objectEventFlag),
    FLD_ARR_(TY_U8, padding),
};
#undef FLD_TYPE

#define FLD_TYPE struct Box
const struct SerialField Struc_Box[] = {
    FLD(TY_U8, count),
    FLD_ARR_(TY_SPECIES, species),
    FLD_STR_ARR_(STRUC_BOXMON, mons),
    FLD_ARR(TY_U8, monOT, MONS_PER_BOX * NAME_LENGTH),
    FLD_ARR(TY_U8, monNicknames, MONS_PER_BOX * MON_NAME_LENGTH),
};
#undef FLD_TYPE

#define FLD_TYPE struct MailMsg
const struct SerialField Struc_MailMsg[] = {
    FLD_ARR_(TY_U8, message),
    FLD_ARR_(TY_U8, author),
    FLD(TY_U16LE, nationality),
    FLD(TY_U16LE, authorID),
    FLD(TY_SPECIES, species),
    FLD(TY_U8, type),
};
#undef FLD_TYPE

#define FLD_TYPE struct OptionsData
const struct SerialField Struc_OptionsData[] = {
    FLD(TY_U8, options),
    FLD(TY_U8, saveFileExists),
    FLD(TY_U8, textboxFrame),
    FLD(TY_U8, textboxFlags),
    FLD(TY_U8, GBPrinterBrightness),
    FLD(TY_U8, options2),
    FLD_ARR_(TY_U8, unused),
};
#undef FLD_TYPE

#define FLD_TYPE struct CurMapData
const struct SerialField Struc_CurMapData[] = {
    FLD_ARR_(TY_U8, visitedSpawns),
    FLD(TY_U8, digWarpNumber),
    FLD(TY_U8, digMapGroup),
    FLD(TY_U8, digMapNumber),
    FLD(TY_U8, backupWarpNumber),
    FLD(TY_U8, backupMapGroup),
    FLD(TY_U8, backupMapNumber),
    FLD_ARR_(TY_SKIP, unused), // skip 3 bytes
    FLD(TY_U8, lastSpawnMapGroup),
    FLD(TY_U8, lastSpawnMapNumber),
    FLD(TY_U8, warpNumber),
    FLD(TY_U8, mapGroup),
    FLD(TY_U8, mapNumber),
    FLD(TY_U8, yCoord),
    FLD(TY_U8, xCoord),
    FLD_ARR_(TY_U8, screenSave),
};
#undef FLD_TYPE

enum { x = offsetof(struct PlayerData, skip_110)};

#define FLD_TYPE struct PlayerData
const struct SerialField Struc_PlayerData[] = {
    FLD(TY_U16LE, playerID),
    FLD_ARR_(TY_U8, playerName),
    FLD_ARR_(TY_U8, momsName),
    FLD_ARR_(TY_U8, rivalName),
    FLD_ARR_(TY_U8, redsName),
    FLD_ARR_(TY_U8, greensName),
    FLD(TY_U8, savedAtLeastOnce),
    FLD(TY_U8, spawnAfterChampion),
    // init time set at newgame
    FLD(TY_U8, startDay),
    FLD(TY_U8, startHour),
    FLD(TY_U8, startMinute),
    FLD(TY_U8, startSecond),
    FLD_ARR_(TY_U8, RTC),
    FLD_ARR_(TY_U8, skip_104),
    // bit 7: dst
    FLD(TY_U8, DST),
    // used only for BANK(wGameTime)
    //union wGameTime
    FLD(TY_U8, gameTimeCap),
    FLD(TY_U16LE, gameTimeHours),
    FLD(TY_U8, gameTimeMinutes),
    FLD(TY_U8, gameTimeSeconds),
    FLD(TY_U8, gameTimeFrames),
    FLD_ARR_(TY_U8, skip_105),
    FLD(TY_U8, curDay),
    FLD_ARR_(TY_U8, skip_106),
    FLD(TY_U8, objectFollow_Leader),
    FLD(TY_U8, objectFollow_Follower),
    FLD(TY_U8, centeredObject),
    FLD(TY_U8, followerMovementQueueLength),
    FLD_ARR_(TY_U8, followMovementQueue),
    FLD_STR(STRUC_OBJECT, playerStruct),
    // player is object struct 0
    // wObjectStruct1 - wObjectStruct12
    // for n, 1, NUM_OBJECT_STRUCTS
    FLD_STR_ARR_(STRUC_OBJECT, objectStruct),
    FLD_ARR_(TY_U8, cmdQueue),
    FLD_ARR_(TY_U8, zipCode_Saved),
    FLD_ARR_(TY_U8, skip_107),
    //union wMapObjects
    FLD_STR(STRUC_MAPOBJECT, playerObject),
    // player is map object 0
    // wMap1Object - wMap15Object
    // for n, 1, NUM_OBJECTS
    FLD_STR_ARR_(STRUC_MAPOBJECT, mapObject),
    FLD_ARR_(TY_U8, objectMasks),
    FLD_ARR_(TY_U8, variableSprites),
    FLD(TY_U8, enteredMapFromContinue),
    FLD_ARR_(TY_U8, skip_108),
    FLD(TY_U8, timeOfDayPal),
    FLD_ARR_(TY_U8, skip_109),
    FLD(TY_U8, timeOfDayPalFlags),
    FLD(TY_U8, timeOfDayPalset),
    FLD(TY_U8, curTimeOfDay),
    FLD(TY_U8, skip_110[0]),
    FLD(TY_U16LE, secretID),
    FLD(TY_U8, statusFlags),
    FLD(TY_U8, statusFlags2),
    FLD_ARR_(TY_U8, money),
    FLD_ARR_(TY_U8, momsMoney),
    FLD(TY_U8, momSavingMoney),
    FLD(TY_U16LE, coins),
    FLD_ARR_(TY_U8, badges),
    FLD_ARR_(TY_U8, TMsHMs),
    FLD(TY_U8, numItems),
    // for(int i = 0; i < MAX_ITEMS * 2; i += 2) {
    //     dest = Serialize_Item(dest, data->items[i]);
    //     *(dest++) = (uint8_t)data->items[i + 1];
    // }
    FLD_ARR(TY_ITEMQUANTITY, items, MAX_ITEMS),
    // dest = Serialize_Item(dest, data->items[MAX_ITEMS * 2]);
    FLD_OFFSET(TY_ITEM, items, MAX_ITEMS * 2),
    FLD(TY_U8, numKeyItems),
    FLD_ARR_(TY_ITEM, keyItems),
    FLD(TY_U8, numBalls),
    // for(int i = 0; i < MAX_BALLS * 2; i += 2) {
    //     dest = Serialize_Item(dest, data->balls[i]);
    //     *(dest++) = (uint8_t)data->balls[i + 1];
    // }
    FLD_ARR(TY_ITEMQUANTITY, balls, MAX_BALLS),
    // dest = Serialize_Item(dest, data->balls[MAX_BALLS * 2]);
    FLD_OFFSET(TY_ITEM, balls, MAX_BALLS * 2),
    FLD(TY_U8, numPCItems),
    // for(int i = 0; i < MAX_PC_ITEMS * 2; i += 2) {
    //     dest = Serialize_Item(dest, data->PCItems[i]);
    //     *(dest++) = (uint8_t)data->PCItems[i + 1];
    // }
    FLD_ARR(TY_ITEMQUANTITY, PCItems, MAX_PC_ITEMS),
    // dest = Serialize_Item(dest, data->PCItems[MAX_PC_ITEMS * 2]);
    FLD_OFFSET(TY_ITEM, PCItems, MAX_PC_ITEMS * 2),
    FLD(TY_U8, pokegearFlags),
    FLD(TY_U8, radioTuningKnob),
    FLD(TY_U8, lastDexMode),
    // uint8_t skip_111[1];
    FLD_ARR_(TY_SKIP, skip_111),
    FLD(TY_U8, whichRegisteredItem),
    FLD(TY_U8, registeredItem),
    FLD(TY_U8, playerState),
    FLD(TY_U8, hallOfFameCount),
    // uint8_t skip_112[1];
    FLD_ARR_(TY_SKIP, skip_112),
    FLD_ARR_(TY_U8, tradeFlags),
    // uint8_t skip_113[1];
    FLD_ARR_(TY_SKIP, skip_113),
    FLD(TY_U8, mooMooBerries),
    FLD(TY_U8, undergroundSwitchPositions),
    FLD(TY_U8, farfetchdPosition),
    // uint8_t skip_114[13];
    FLD_ARR_(TY_U8, skip_114),
    // map scene ids
    FLD(TY_U8, Pokecenter2FSceneID),
    FLD(TY_U8, TradeCenterSceneID),
    FLD(TY_U8, ColosseumSceneID),
    FLD(TY_U8, TimeCapsuleSceneID),
    FLD(TY_U8, PowerPlantSceneID),
    FLD(TY_U8, CeruleanGymSceneID),
    FLD(TY_U8, Route25SceneID),
    FLD(TY_U8, TrainerHouseB1FSceneID),
    FLD(TY_U8, VictoryRoadGateSceneID),
    FLD(TY_U8, SaffronMagnetTrainStationSceneID),
    FLD(TY_U8, Route16GateSceneID),
    FLD(TY_U8, Route17Route18GateSceneID),
    FLD(TY_U8, IndigoPlateauPokecenter1FSceneID),
    FLD(TY_U8, WillsRoomSceneID),
    FLD(TY_U8, KogasRoomSceneID),
    FLD(TY_U8, BrunosRoomSceneID),
    FLD(TY_U8, KarensRoomSceneID),
    FLD(TY_U8, LancesRoomSceneID),
    FLD(TY_U8, HallOfFameSceneID),
    FLD(TY_U8, Route27SceneID),
    FLD(TY_U8, NewBarkTownSceneID),
    FLD(TY_U8, ElmsLabSceneID),
    FLD(TY_U8, PlayersHouse1FSceneID),
    FLD(TY_U8, Route29SceneID),
    FLD(TY_U8, CherrygroveCitySceneID),
    FLD(TY_U8, MrPokemonsHouseSceneID),
    FLD(TY_U8, Route32SceneID),
    FLD(TY_U8, Route35NationalParkGateSceneID),
    FLD(TY_U8, Route36SceneID),
    FLD(TY_U8, Route36NationalParkGateSceneID),
    FLD(TY_U8, AzaleaTownSceneID),
    FLD(TY_U8, GoldenrodGymSceneID),
    FLD(TY_U8, GoldenrodMagnetTrainStationSceneID),
    FLD(TY_U8, GoldenrodPokecenter1FSceneID),
    FLD(TY_U8, OlivineCitySceneID),
    FLD(TY_U8, Route34SceneID),
    FLD(TY_U8, Route34IlexForestGateSceneID),
    FLD(TY_U8, EcruteakTinTowerEntranceSceneID),
    FLD(TY_U8, WiseTriosRoomSceneID),
    FLD(TY_U8, EcruteakPokecenter1FSceneID),
    FLD(TY_U8, EcruteakGymSceneID),
    FLD(TY_U8, MahoganyTownSceneID),
    FLD(TY_U8, Route42SceneID),
    FLD(TY_U8, CianwoodCitySceneID),
    FLD(TY_U8, BattleTower1FSceneID),
    FLD(TY_U8, BattleTowerBattleRoomSceneID),
    FLD(TY_U8, BattleTowerElevatorSceneID),
    FLD(TY_U8, BattleTowerHallwaySceneID),
    FLD(TY_U8, BattleTowerOutsideSceneID),
    FLD(TY_U8, Route43GateSceneID),
    FLD(TY_U8, MountMoonSceneID),
    FLD(TY_U8, SproutTower3FSceneID),
    FLD(TY_U8, TinTower1FSceneID),
    FLD(TY_U8, BurnedTower1FSceneID),
    FLD(TY_U8, BurnedTowerB1FSceneID),
    FLD(TY_U8, RadioTower5FSceneID),
    FLD(TY_U8, RuinsOfAlphOutsideSceneID),
    FLD(TY_U8, RuinsOfAlphResearchCenterSceneID),
    FLD(TY_U8, RuinsOfAlphHoOhChamberSceneID),
    FLD(TY_U8, RuinsOfAlphKabutoChamberSceneID),
    FLD(TY_U8, RuinsOfAlphOmanyteChamberSceneID),
    FLD(TY_U8, RuinsOfAlphAerodactylChamberSceneID),
    FLD(TY_U8, RuinsOfAlphInnerChamberSceneID),
    FLD(TY_U8, MahoganyMart1FSceneID),
    FLD(TY_U8, TeamRocketBaseB1FSceneID),
    FLD(TY_U8, TeamRocketBaseB2FSceneID),
    FLD(TY_U8, TeamRocketBaseB3FSceneID),
    FLD(TY_U8, GoldenrodUndergroundSwitchRoomEntrancesSceneID),
    FLD(TY_U8, SilverCaveRoom3SceneID),
    FLD(TY_U8, VictoryRoadSceneID),
    FLD(TY_U8, DragonsDenB1FSceneID),
    FLD(TY_U8, DragonShrineSceneID),
    FLD(TY_U8, OlivinePortSceneID),
    FLD(TY_U8, VermilionPortSceneID),
    FLD(TY_U8, FastShip1FSceneID),
    FLD(TY_U8, FastShipB1FSceneID),
    FLD(TY_U8, MountMoonSquareSceneID),
    FLD(TY_U8, MobileTradeRoomSceneID),
    FLD(TY_U8, MobileBattleRoomSceneID),
//     uint8_t skip_115[49];
    FLD_ARR_(TY_SKIP, skip_115),
//     // fight counts
    FLD(TY_U8, JackFightCount),
    FLD(TY_U8, BeverlyFightCount),
//     // unreferenced
    FLD(TY_U8, HueyFightCount),
    FLD(TY_U8, GavenFightCount),
    FLD(TY_U8, BethFightCount),
    FLD(TY_U8, JoseFightCount),
    FLD(TY_U8, ReenaFightCount),
    FLD(TY_U8, JoeyFightCount),
    FLD(TY_U8, WadeFightCount),
    FLD(TY_U8, RalphFightCount),
    FLD(TY_U8, LizFightCount),
    FLD(TY_U8, AnthonyFightCount),
    FLD(TY_U8, ToddFightCount),
    FLD(TY_U8, GinaFightCount),
    FLD(TY_U8, IrwinFightCount),
//     // unreferenced
    FLD(TY_U8, ArnieFightCount),
    FLD(TY_U8, AlanFightCount),
    FLD(TY_U8, DanaFightCount),
    FLD(TY_U8, ChadFightCount),
    FLD(TY_U8, DerekFightCount),
//     // unreferenced
    FLD(TY_U8, TullyFightCount),
    FLD(TY_U8, BrentFightCount),
    FLD(TY_U8, TiffanyFightCount),
    FLD(TY_U8, VanceFightCount),
    FLD(TY_U8, WiltonFightCount),
    FLD(TY_U8, KenjiFightCount),
//     // unreferenced
    FLD(TY_U8, ParryFightCount),
    FLD(TY_U8, ErinFightCount),
//     uint8_t skip_116[100];
    FLD_ARR_(TY_SKIP, skip_116),
    FLD_ARR_(TY_U8, eventFlags),
    FLD(TY_U8, curBox),
    // uint8_t skip_117[2];
    FLD_ARR_(TY_SKIP, skip_117),
    FLD_ARR_(TY_U8, boxNames),
    FLD(TY_U8, celebiEvent),
    // uint8_t skip_118[1];
    FLD_ARR_(TY_SKIP, skip_118),
    FLD(TY_U8, bikeFlags),
    // uint8_t skip_119[1];
    FLD_ARR_(TY_SKIP, skip_119),
    FLD(TY_U16LE, curMapSceneScriptPointer),
    FLD(TY_U16LE, curCaller),
    FLD(TY_U8, curMapWarpCount),
    FLD(TY_U16LE, curMapWarpsPointer),
    FLD(TY_U8, curMapCoordEventCount),
    FLD(TY_U16LE, curMapCoordEventsPointer),
    FLD(TY_U8, curMapBGEventCount),
    FLD(TY_U16LE, curMapBGEventsPointer),
    FLD(TY_U8, curMapObjectEventCount),
    FLD(TY_U16LE, curMapObjectEventsPointer),
    FLD(TY_U8, curMapSceneScriptCount),
    FLD(TY_U16LE, curMapSceneScriptsPointer),
    FLD(TY_U8, curMapCallbackCount),
    FLD(TY_U16LE, curMapCallbacksPointer),
    // uint8_t skip_120[2];
    FLD_ARR_(TY_SKIP, skip_120),
    // Sprite id of each decoration
    FLD(TY_U8, decoBed),
    FLD(TY_U8, decoCarpet),
    FLD(TY_U8, decoPlant),
    FLD(TY_U8, decoPoster),
    FLD(TY_U8, decoConsole),
    FLD(TY_U8, decoLeftOrnament),
    FLD(TY_U8, decoRightOrnament),
    FLD(TY_U8, decoBigDoll),
    // Items bought from Mom
    FLD(TY_U8, whichMomItem), // Should be item_t?
    FLD(TY_U8, whichMomItemSet),
    FLD_ARR_(TY_U8, momItemTriggerBalance),
    FLD(TY_U16LE, dailyResetTimer),
    FLD(TY_U8, dailyFlags1),
    FLD(TY_U8, dailyFlags2),
    FLD(TY_U8, swarmFlags),
    // uint8_t skip_121[2];
    FLD_ARR_(TY_SKIP, skip_121),
    FLD(TY_U8, timerEventStartDay),
    // uint8_t skip_122[3];
    FLD_ARR_(TY_SKIP, skip_122),
    FLD_ARR_(TY_U8, fruitTreeFlags),
    // uint8_t skip_123[2];
    FLD_ARR_(TY_SKIP, skip_123),
    FLD(TY_U16LE, luckyNumberDayTimer),
    // uint8_t skip_124[2];
    FLD_ARR_(TY_SKIP, skip_124),
    FLD(TY_U16LE, specialPhoneCallID),
    // uint8_t skip_125[2];
    FLD_ARR_(TY_SKIP, skip_125),
    FLD_ARR_(TY_U8, bugContestStartTime),
    // day, hour, min, sec
    FLD(TY_U8, unusedTwoDayTimerOn),
    FLD(TY_U8, unusedTwoDayTimer),
    FLD(TY_U8, unusedTwoDayTimerStartDate),
    // uint8_t skip_126[4];
    FLD_ARR_(TY_SKIP, skip_126),
    FLD(TY_U8, mobileOrCable_LastSelection),
    FLD(TY_U8, wdc41),
    FLD_ARR_(TY_U8, wdc42),
    FLD(TY_U8, buenasPassword),
    FLD(TY_U8, blueCardBalance),
    FLD_ARR_(TY_U8, dailyRematchFlags),
    FLD_ARR_(TY_U8, dailyPhoneItemFlags),
    FLD_ARR_(TY_U8, dailyPhoneTimeOfDayFlags),
    FLD_ARR_(TY_U8, wKenjiBreakTimer),
    // Kenji
    FLD(TY_U8, yanmaMapGroup),
    FLD(TY_U8, yanmaMapNumber),
    FLD_ARR_(TY_U8, playerMonSelection),
    FLD(TY_U8, wdc5f),
    FLD(TY_U8, wdc60),
    // uint8_t skip_127[18];
    FLD_ARR_(TY_SKIP, skip_127),
    FLD(TY_U8, stepCount),
    FLD(TY_U8, poisonStepCount),
    // uint8_t skip_128[2];
    FLD_ARR_(TY_SKIP, skip_128),
    FLD(TY_U8, happinessStepCount),
    // uint8_t skip_129[1];
    FLD_ARR_(TY_SKIP, skip_129),
    FLD(TY_U8, parkBallsRemaining),
    FLD(TY_U16LE, safariTimeRemaining),
    FLD_ARR_(TY_U8, phoneList),
    // uint8_t skip_130[22];
    FLD_ARR_(TY_SKIP, skip_130),
    FLD(TY_U8, luckyNumberShowFlag),
    // uint8_t skip_131[1];
    FLD_ARR_(TY_SKIP, skip_131),
    FLD(TY_U16LE, luckyIDNumber),
    FLD(TY_U8, repelEffect),
    FLD(TY_U16LE, bikeStep),
    FLD(TY_U8, kurtApricornQuantity),
};
#undef FLD_TYPE

#define FLD_TYPE struct PokemonData
const struct SerialField Struc_PokemonData[] = {
    FLD(TY_U8, partyCount),
    FLD_ARR_(TY_SPECIES, partySpecies),
    FLD(TY_U8, partyEnd), // unused
    // older code doesn't check wPartyCount
    // wPartyMon1 - wPartyMon6
    //union wPartyMons
    // for n, 1, PARTY_LENGTH + 1
    // wPartyMon1 - wPartyMon6
    FLD_STR_ARR_(STRUC_PARTYMON, partyMon),
    // wPartyMon1OT - wPartyMon6OT
    //union wPartyMonOTs
    // for n, 1, PARTY_LENGTH + 1
    FLD_ARR(TY_U8, partyMonOT, PARTY_LENGTH * NAME_LENGTH),
    // wPartyMon1Nickname - wPartyMon6Nickname
    //union wPartyMonNicknames
    // for n, 1, PARTY_LENGTH + 1
    FLD_ARR(TY_U8, partyMonNickname, PARTY_LENGTH * MON_NAME_LENGTH),
    // uint8_t partyMonNicknamesEnd[22];
    FLD_ARR_(TY_SKIP, partyMonNicknamesEnd),
    FLD_ARR_(TY_U8, pokedexCaught),
    FLD_ARR_(TY_U8, pokedexSeen),
    FLD_ARR_(TY_U8, unownDex),
    FLD(TY_U8, unlockedUnowns),
    FLD(TY_U8, firstUnownSeen),
    // bit 7: active
    // bit 6: egg ready
    // bit 5: monsters are compatible
    // bit 0: monster 1 in day-care
    FLD(TY_U8, dayCareMan),
    FLD_ARR_(TY_U8, breedMon1Nickname),
    FLD_ARR_(TY_U8, breedMon1OT),
    FLD_STR(STRUC_BOXMON, breedMon1),
    // bit 7: active
    // bit 0: monster 2 in day-care
    FLD(TY_U8, dayCareLady),
    FLD(TY_U8, stepsToEgg),
    //  z: yes
    // nz: no
    FLD(TY_U8, breedMotherOrNonDitto),
    FLD_ARR_(TY_U8, breedMon2Nickname),
    FLD_ARR_(TY_U8, breedMon2OT),
    FLD_STR(STRUC_BOXMON, breedMon2),
    FLD_ARR_(TY_U8, eggMonNickname),
    FLD_ARR_(TY_U8, eggMonOT),
    FLD_STR(STRUC_BOXMON, eggMon),
    FLD(TY_SPECIES, bugContestSecondPartySpecies),
    FLD_STR(STRUC_PARTYMON, contestMon),
    FLD(TY_U8, dunsparceMapGroup),
    FLD(TY_U8, dunsparceMapNumber),
    FLD(TY_U8, fishingSwarmFlag),
    FLD_STR(STRUC_ROAMER, roamMon1),
    FLD_STR(STRUC_ROAMER, roamMon2),
    FLD_STR(STRUC_ROAMER, roamMon3),
    FLD(TY_U8, roamMons_CurMapNumber),
    FLD(TY_U8, roamMons_CurMapGroup),
    FLD(TY_U8, roamMons_LastMapNumber),
    FLD(TY_U8, roamMons_LastMapGroup),
    FLD(TY_U8, bestMagikarpLengthFeet),
    FLD(TY_U8, bestMagikarpLengthInches),
    FLD_ARR_(TY_U8, magikarpRecordHoldersName),
};
#undef FLD_TYPE

struct SerialStruct {
    uint32_t struct_size;
    size_t field_count;
    const struct SerialField* fields;
};

#define serial_struct(id, name) [id] = {sizeof(struct name), lengthof(Struc_##name), Struc_##name}

const struct SerialStruct Structs[] = {
    serial_struct(STRUC_U8ITEM, U8Item),
    serial_struct(STRUC_BOXMON, BoxMon),
    serial_struct(STRUC_PARTYMON, PartyMon),
    serial_struct(STRUC_NICKNAMEDMON, NicknamedMon),
    serial_struct(STRUC_TRADEMON, TradeMon),
    serial_struct(STRUC_ROAMER, Roamer),
    serial_struct(STRUC_BATTLETOWERPARTYMON, BattleTowerPartyMon),
    serial_struct(STRUC_BATTLETOWERDATA, BattleTowerData),
    serial_struct(STRUC_OBJECT, Object),
    serial_struct(STRUC_MAPOBJECT, MapObject),
    serial_struct(STRUC_BOX, Box),
    serial_struct(STRUC_MAILMSG, MailMsg),
    serial_struct(STRUC_OPTIONSDATA, OptionsData),
    serial_struct(STRUC_CURMAPDATA, CurMapData),
    serial_struct(STRUC_PLAYERDATA, PlayerData),
    serial_struct(STRUC_POKEMONDATA, PokemonData),
};

uint8_t* Serialize_Struct(uint8_t* dest, const struct SerialStruct* struc, const void* data);

#define FLD_PTR(data, offset, type) ((type*)((char*)data + offset))
#define FLD_PTR_IDX(data, offset, i, type) ((type*)((char*)data + offset + (i) * sizeof(type)))
uint8_t* Serialize_Field(uint8_t* dst, const struct SerialField* fld, const void* data) {
    switch(fld->type) {
        case TY_U8: 
            if(fld->count > 1) {
                return Serialize_ByteBuffer(dst, FLD_PTR(data, fld->offset, uint8_t), fld->count);
            } else {
                *(dst++) = *FLD_PTR(data, fld->offset, uint8_t);
                return dst;
            }
            break;
        case TY_U16LE: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                dst = Serialize_U16_LE(dst, *FLD_PTR_IDX(data, fld->offset, i, uint16_t)); 
            return dst;
        case TY_U16BE:
            for(uint32_t i = 0; i < fld->count; ++i) 
                dst = Serialize_U16_BE(dst, *FLD_PTR_IDX(data, fld->offset, i, uint16_t));
            return dst;
        case TY_SPECIES: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                dst = Serialize_Species(dst, *FLD_PTR_IDX(data, fld->offset, i, species_t)); 
            return dst;
        case TY_ITEM: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                dst = Serialize_Item(dst, *FLD_PTR_IDX(data, fld->offset, i, item_t)); 
            return dst;
        case TY_MOVE: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                dst = Serialize_Move(dst, *FLD_PTR_IDX(data, fld->offset, i, move_t)); 
            return dst;
        case TY_MAPID: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                dst = Serialize_MapId(dst, *FLD_PTR_IDX(data, fld->offset, i, struct MapId)); 
            return dst;
        case TY_ITEMQUANTITY: 
            for(uint32_t i = 0; i < fld->count; ++i)
                dst = Serialize_ItemQuantity(dst, *FLD_PTR_IDX(data, fld->offset, i, item_quantity_pocket_en_s)); 
            return dst;
        case TY_SKIP: dst += fld->count; return dst;
        default:
            if(fld->type & 0x100) {
                const struct SerialStruct* struc = Structs + (fld->type & 0xff);
                for(uint32_t i = 0; i < fld->count; ++i) 
                    dst = Serialize_Struct(dst, struc, FLD_PTR(data, fld->offset + (i * struc->struct_size), void));
                return dst;
            }
    }
    return dst;
}

uint8_t* Serialize_U16_LE(uint8_t* dest, uint16_t value) {
    dest[0] = LOW(value);
    dest[1] = HIGH(value);
    return dest + 2;
}

uint8_t* Serialize_U16_BE(uint8_t* dest, uint16_t value) {
    dest[0] = HIGH(value);
    dest[1] = LOW(value);
    return dest + 2;
}

uint8_t* Serialize_U16_Native(uint8_t* dest, uint16_t value) {
    if(IsLittleEndian()) 
        return Serialize_U16_LE(dest, value);
    return Serialize_U16_BE(dest, value);
}

uint8_t* Serialize_Species(uint8_t* dest, species_t src) {
    dest[0] = src;
    return dest + 1;
}

uint8_t* Serialize_Item(uint8_t* dest, item_t itm) {
    dest[0] = itm;
    return dest + 1;
}

uint8_t* Serialize_Move(uint8_t* dest, move_t move) {
    dest[0] = move;
    return dest + 1;
}

uint8_t* Serialize_ItemQuantity(uint8_t* dest, item_quantity_pocket_en_s en) {
    dest = Serialize_Item(dest, en.item);
    *(dest++) = en.quantity;
    return dest;
}

uint8_t* Serialize_ByteBuffer(uint8_t* dest, const uint8_t* src, size_t size) {
    memcpy(dest, src, size);
    return dest + size;
}

uint8_t* Serialize_Struct(uint8_t* dest, const struct SerialStruct* struc, const void* data) {
    for(uint32_t j = 0; j < struc->field_count; ++j) {
        dest = Serialize_Field(dest, struc->fields + j, data); 
    }
    return dest;
}

#define Serialize_ByteArray(dest, src) Serialize_ByteBuffer(dest, src, sizeof(src))
#define Serialize_Skip(dest, src) dest += sizeof(src)

uint8_t* Serialize_BoxMon(uint8_t* dest, const struct BoxMon* src) {
    return Serialize_Struct(dest, Structs + (STRUC_BOXMON), src);
}

uint8_t* Serialize_PartyMon(uint8_t* dest, const struct PartyMon* mon) {
    return Serialize_Struct(dest, Structs + (STRUC_PARTYMON), mon);
}

uint8_t* Serialize_NicknamedMon(uint8_t* dest, const struct NicknamedMon* mon) {
    return Serialize_Struct(dest, Structs + (STRUC_NICKNAMEDMON), mon);
}

uint8_t* Serialize_TradeMon(uint8_t* dest, const struct TradeMon* mon) {
    return Serialize_Struct(dest, Structs + (STRUC_TRADEMON), mon);
}

uint8_t* Serialize_Roamer(uint8_t* dest, const struct Roamer* roamer) {
    return Serialize_Struct(dest, Structs + (STRUC_ROAMER), roamer);
}

uint8_t* Serialize_BattleTowerPartyMon(uint8_t* dest, const struct BattleTowerPartyMon* mon) {
    return Serialize_Struct(dest, Structs + (STRUC_BATTLETOWERPARTYMON), mon);
}

uint8_t* Serialize_BattleTowerData(uint8_t* dest, const struct BattleTowerData* data) {
    return Serialize_Struct(dest, Structs + (STRUC_BATTLETOWERDATA), data);
}

uint8_t* Serialize_MapId(uint8_t* dest, struct MapId mapId) {
    dest[0] = mapId.mapGroup;
    dest[1] = mapId.mapNumber;
    return dest + 2;
}

uint8_t* Serialize_Object(uint8_t* dest, const struct Object* bc) {
    return Serialize_Struct(dest, Structs + (STRUC_OBJECT), bc);
}

uint8_t* Serialize_MapObject(uint8_t* dest, const struct MapObject* bc) {
    return Serialize_Struct(dest, Structs + (STRUC_MAPOBJECT), bc);
}

uint8_t* Serialize_Box(uint8_t* dest, const struct Box* box) {
    return Serialize_Struct(dest, Structs + (STRUC_BOX), box);
}

uint8_t* Serialize_MailMsg(uint8_t* dest, const struct MailMsg* mail) {
    return Serialize_Struct(dest, Structs + (STRUC_MAILMSG), mail);
}

uint8_t* Serialize_OptionsData(uint8_t* dest, const struct OptionsData* data) {
    return Serialize_Struct(dest, Structs + (STRUC_OPTIONSDATA), data);
}

uint8_t* Serialize_CurMapData(uint8_t* dest, const struct CurMapData* data) {
    return Serialize_Struct(dest, Structs + (STRUC_CURMAPDATA), data);
}

uint8_t* Serialize_PlayerData(uint8_t* dest, const struct PlayerData* data) {
    return Serialize_Struct(dest, Structs + STRUC_PLAYERDATA, data);
}

uint8_t* Serialize_PokemonData(uint8_t* dest, const struct PokemonData* data) {
    return Serialize_Struct(dest, Structs + STRUC_POKEMONDATA, data);
}

const uint8_t* Deserialize_Struct(void* data, const struct SerialStruct* struc, const uint8_t* src);

const uint8_t* Deserialize_Field(void* data, const struct SerialField* fld, const uint8_t* src) {
    switch(fld->type) {
        case TY_U8: 
            if(fld->count > 1) {
                return Deserialize_ByteBuffer(FLD_PTR(data, fld->offset, uint8_t), src, fld->count);
            } else {
                *FLD_PTR(data, fld->offset, uint8_t) = *(src++);
                return src;
            }
            break;
        case TY_U16LE: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                src = Deserialize_U16_LE(FLD_PTR_IDX(data, fld->offset, i, uint16_t), src); 
            return src;
        case TY_U16BE:
            for(uint32_t i = 0; i < fld->count; ++i) 
                src = Deserialize_U16_BE(FLD_PTR_IDX(data, fld->offset, i, uint16_t), src);
            return src;
        case TY_SPECIES: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                src = Deserialize_Species(FLD_PTR_IDX(data, fld->offset, i, species_t), src); 
            return src;
        case TY_ITEM: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                src = Deserialize_Item(FLD_PTR_IDX(data, fld->offset, i, item_t), src); 
            return src;
        case TY_MOVE: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                src = Deserialize_Move(FLD_PTR_IDX(data, fld->offset, i, move_t), src); 
            return src;
        case TY_MAPID: 
            for(uint32_t i = 0; i < fld->count; ++i) 
                src = Deserialize_MapId(FLD_PTR_IDX(data, fld->offset, i, struct MapId), src); 
            return src;
        case TY_ITEMQUANTITY: 
            for(uint32_t i = 0; i < fld->count; ++i)
                src = Deserialize_ItemQuantity(FLD_PTR_IDX(data, fld->offset, i, item_quantity_pocket_en_s), src); 
            return src;
        case TY_SKIP: src += fld->count; return src;
        default:
            if(fld->type & 0x100) {
                const struct SerialStruct* struc = Structs + (fld->type & 0xff);
                for(uint32_t i = 0; i < fld->count; ++i) 
                    src = Deserialize_Struct(FLD_PTR(data, fld->offset + (i * struc->struct_size), void), struc, src);
                return src;
            }
    }
    return src;
}

const uint8_t* Deserialize_Struct(void* data, const struct SerialStruct* struc, const uint8_t* src) {
    for(uint32_t j = 0; j < struc->field_count; ++j) {
        src = Deserialize_Field(data, struc->fields + j, src); 
    }
    return src;
}

const uint8_t* Deserialize_U16_LE(uint16_t* dest, const uint8_t* src) {
    uint16_t value = (src[0]) | (src[1] << 8);
    *dest = value;
    return src + 2;
}

const uint8_t* Deserialize_U16_BE(uint16_t* dest, const uint8_t* src) {
    uint16_t value = (src[1]) | (src[0] << 8);
    *dest = value;
    return src + 2;
}

const uint8_t* Deserialize_U16_Native(uint16_t* dest, const uint8_t* src) {
    if(IsLittleEndian()) 
        return Deserialize_U16_LE(dest, src);
    return Deserialize_U16_BE(dest, src);
}

const uint8_t* Deserialize_Species(species_t* dest, const uint8_t* src) {
    *dest = *src;
    return src + 1;
}

const uint8_t* Deserialize_Item(item_t* dest, const uint8_t* src) {
    *dest = *src;
    return src + 1;
}

const uint8_t* Deserialize_Move(move_t* dest, const uint8_t* src) {
    *dest = *src;
    return src + 1;
}

const uint8_t* Deserialize_ItemQuantity(item_quantity_pocket_en_s *en, const uint8_t* src) {
    src = Deserialize_Item(&en->item, src);
    en->quantity = *(src++);
    return src;
}

const uint8_t* Deserialize_ByteBuffer(uint8_t* dest, const uint8_t* src, size_t size) {
    memcpy(dest, src, size);
    return src + size;
}

#define Deserialize_ByteArray(dest, src) Deserialize_ByteBuffer(dest, src, sizeof(dest))

const uint8_t* Deserialize_BoxMon(struct BoxMon* dest, const uint8_t* src) {
    return Deserialize_Struct(dest, Structs + STRUC_BOXMON, src);
}

const uint8_t* Deserialize_PartyMon(struct PartyMon* mon, const uint8_t* src) {
    return Deserialize_Struct(mon, Structs + STRUC_PARTYMON, src);
}

const uint8_t* Deserialize_NicknamedMon(struct NicknamedMon* mon, const uint8_t* src) {
    return Deserialize_Struct(mon, Structs + STRUC_NICKNAMEDMON, src);
}

const uint8_t* Deserialize_TradeMon(struct TradeMon* mon, const uint8_t* src) {
    return Deserialize_Struct(mon, Structs + STRUC_TRADEMON, src);
}

const uint8_t* Deserialize_Roamer(struct Roamer* roamer, const uint8_t* src) {
    return Deserialize_Struct(roamer, Structs + STRUC_ROAMER, src);
}

const uint8_t* Deserialize_BattleTowerPartyMon(struct BattleTowerPartyMon* mon, const uint8_t* src) {
    return Deserialize_Struct(mon, Structs + STRUC_BATTLETOWERPARTYMON, src);
}

const uint8_t* Deserialize_BattleTowerData(struct BattleTowerData* data, const uint8_t* src) {
    return Deserialize_Struct(data, Structs + STRUC_BATTLETOWERDATA, src);
}

const uint8_t* Deserialize_MapId(struct MapId* mapId, const uint8_t* src) {
    mapId->mapGroup = src[0];
    mapId->mapNumber = src[1];
    return src + 2;
}

const uint8_t* Deserialize_Object(struct Object* bc, const uint8_t* src) {
    return Deserialize_Struct(bc, Structs + STRUC_OBJECT, src);
}

const uint8_t* Deserialize_MapObject(struct MapObject* bc, const uint8_t* src) {
    return Deserialize_Struct(bc, Structs + STRUC_MAPOBJECT, src);
}

const uint8_t* Deserialize_Box(struct Box* box, const uint8_t* src) {
    return Deserialize_Struct(box, Structs + STRUC_BOX, src);
}

const uint8_t* Deserialize_MailMsg(struct MailMsg* mail, const uint8_t* src) {
    return Deserialize_Struct(mail, Structs + STRUC_MAILMSG, src);
}

const uint8_t* Deserialize_OptionsData(struct OptionsData* data, const uint8_t* src) {
    return Deserialize_Struct(data, Structs + STRUC_OPTIONSDATA, src);
}

const uint8_t* Deserialize_CurMapData(struct CurMapData* data, const uint8_t* src) {
    return Deserialize_Struct(data, Structs + STRUC_CURMAPDATA, src);
}

const uint8_t* Deserialize_PlayerData(struct PlayerData* data, const uint8_t* src) {
    return Deserialize_Struct(data, Structs + STRUC_PLAYERDATA, src);
}

const uint8_t* Deserialize_PokemonData(struct PokemonData* data, const uint8_t* src) {
    return Deserialize_Struct(data, Structs + STRUC_POKEMONDATA, src);
}

int Test_Serialize_PlayerData(void) {
    int result = 0;
    struct PlayerData data = {0};
    uint8_t buffer[wPlayerDataEnd - wPlayerData] = {0};
    OpenSRAM(MBANK(asPlayerData));

    CopyBytes_GB(wPlayerData, sPlayerData, wPlayerDataEnd - wPlayerData);
    const uint8_t* sram = GBToRAMAddr(sPlayerData);
    const uint8_t* start = sram;
    const uint8_t* end = Deserialize_PlayerData(&data, start);
    if(end - start != wPlayerDataEnd - wPlayerData) {
        fprintf(stderr, "[%s - FAILED] Failed to deserialize player data. Expected size %d, got %d\n",
            __func__,
            wPlayerDataEnd - wPlayerData,
            (int)(end - start));
        result = -1;
        goto quit;
    }
    
    start = buffer;
    end = Serialize_PlayerData(buffer, &data);
    if(end - start != wPlayerDataEnd - wPlayerData) {
        fprintf(stderr, "[%s - FAILED] Failed to serialize player data. Expected size %d, got %d\n",
            __func__,
            wPlayerDataEnd - wPlayerData,
            (int)(end - start));
        result = -1;
        goto quit;
    }

    if(memcmp(buffer, sram, wPlayerDataEnd - wPlayerData) != 0) {
        fprintf(stderr, "[%s - FAILED] Failed to produce matching serialized player data\n",
            __func__);
        FILE* f;
        f = fopen("player_data_gen.bin", "wb");
        fwrite(buffer, 1, wPlayerDataEnd - wPlayerData, f);
        fclose(f);
        f = fopen("player_data_base.bin", "wb");
        fwrite(sram, 1, wPlayerDataEnd - wPlayerData, f);
        fclose(f);
        result = -1;
        goto quit;
    }

    printf("[%s - SUCCESS]\n", __func__);

quit:
    CloseSRAM();
    return result;
}


int Test_Serialize_PokemonData(void) {
    int result = 0;
    struct PokemonData data = {0};
    uint8_t buffer[wPokemonDataEnd - wPokemonData] = {0};
    OpenSRAM(MBANK(asPokemonData));

    CopyBytes_GB(wPokemonData, sPokemonData, wPokemonDataEnd - wPokemonData);
    const uint8_t* sram = GBToRAMAddr(sPokemonData);
    const uint8_t* start = sram;
    const uint8_t* end = Deserialize_PokemonData(&data, start);
    if(end - start != wPokemonDataEnd - wPokemonData) {
        fprintf(stderr, "[%s - FAILED] Failed to deserialize player data. Expected size %d, got %d\n",
            __func__,
            wPokemonDataEnd - wPokemonData,
            (int)(end - start));
        result = -1;
        goto quit;
    }
    
    start = buffer;
    end = Serialize_PokemonData(buffer, &data);
    if(end - start != wPokemonDataEnd - wPokemonData) {
        fprintf(stderr, "[%s - FAILED] Failed to serialize player data. Expected size %d, got %d\n",
            __func__,
            wPokemonDataEnd - wPokemonData,
            (int)(end - start));
        result = -1;
        goto quit;
    }

    if(memcmp(buffer, sram, wPokemonDataEnd - wPokemonData) != 0) {
        fprintf(stderr, "[%s - FAILED] Failed to produce matching serialized player data\n",
            __func__);
        FILE* f;
        f = fopen("pokemon_data_gen.bin", "wb");
        fwrite(buffer, 1, wPokemonDataEnd - wPokemonData, f);
        fclose(f);
        f = fopen("pokemon_data_base.bin", "wb");
        fwrite(sram, 1, wPokemonDataEnd - wPokemonData, f);
        fclose(f);
        result = -1;
        goto quit;
    }

    printf("[%s - SUCCESS]\n", __func__);

quit:
    CloseSRAM();
    return result;
}

int Test_Serialize_CurMapData(void) {
    int result = 0;
    struct CurMapData data = {0};
    uint8_t buffer[wCurMapDataEnd - wCurMapData] = {0};
    OpenSRAM(MBANK(asCurMapData));

    CopyBytes_GB(wCurMapData, sCurMapData, wCurMapDataEnd - wCurMapData);
    const uint8_t* sram = GBToRAMAddr(sCurMapData);
    const uint8_t* start = sram;
    const uint8_t* end = Deserialize_CurMapData(&data, start);
    if(end - start != wCurMapDataEnd - wCurMapData) {
        fprintf(stderr, "[%s - FAILED] Failed to deserialize map data. Expected size %d, got %d\n",
            __func__,
            wCurMapDataEnd - wCurMapData,
            (int)(end - start));
        result = -1;
        goto quit;
    }

    // if(Check_PokemonData(&data) < 0) {
    //     result = -1;
    //     goto quit;
    // }
    
    start = buffer;
    end = Serialize_CurMapData(buffer, &data);
    if(end - start != wCurMapDataEnd - wCurMapData) {
        fprintf(stderr, "[%s - FAILED] Failed to serialize map data. Expected size %d, got %d\n",
            __func__,
            wCurMapDataEnd - wCurMapData,
            (int)(end - start));
        result = -1;
        goto quit;
    }

    if(memcmp(buffer, sram, wCurMapDataEnd - wCurMapData) != 0) {
        fprintf(stderr, "[%s - FAILED] Failed to produce matching serialized map data\n",
            __func__);
        FILE* f;
        f = fopen("map_data_gen.bin", "wb");
        fwrite(buffer, 1, wCurMapDataEnd - wCurMapData, f);
        fclose(f);
        f = fopen("map_data_base.bin", "wb");
        fwrite(sram, 1, wCurMapDataEnd - wCurMapData, f);
        fclose(f);
        result = -1;
        goto quit;
    }

    printf("[%s - SUCCESS]\n", __func__);

quit:
    CloseSRAM();
    return result;
}

int Test_Serialize_OptionsData(void) {
    int result = 0;
    struct OptionsData data = {0};
    uint8_t buffer[wOptionsEnd - wOptions] = {0};
    OpenSRAM(MBANK(asOptions));

    CopyBytes_GB(wOptions, sOptions, wOptionsEnd - wOptions);
    const uint8_t* sram = GBToRAMAddr(sOptions);
    const uint8_t* start = sram;
    const uint8_t* end = Deserialize_OptionsData(&data, start);
    if(end - start != wOptionsEnd - wOptions) {
        fprintf(stderr, "[%s - FAILED] Failed to deserialize options data. Expected size %d, got %d\n",
            __func__,
            wOptionsEnd - wOptions,
            (int)(end - start));
        result = -1;
        goto quit;
    }

    // if(Check_PokemonData(&data) < 0) {
    //     result = -1;
    //     goto quit;
    // }
    
    start = buffer;
    end = Serialize_OptionsData(buffer, &data);
    if(end - start != wOptionsEnd - wOptions) {
        fprintf(stderr, "[%s - FAILED] Failed to serialize options data. Expected size %d, got %d\n",
            __func__,
            wOptionsEnd - wOptions,
            (int)(end - start));
        result = -1;
        goto quit;
    }

    if(memcmp(buffer, sram, wOptionsEnd - wOptions) != 0) {
        fprintf(stderr, "[%s - FAILED] Failed to produce matching serialized options data\n",
            __func__);
        FILE* f;
        f = fopen("options_data_gen.bin", "wb");
        fwrite(buffer, 1, wOptionsEnd - wOptions, f);
        fclose(f);
        f = fopen("options_data_base.bin", "wb");
        fwrite(sram, 1, wOptionsEnd - wOptions, f);
        fclose(f);
        result = -1;
        goto quit;
    }

    printf("[%s - SUCCESS]\n", __func__);

quit:
    CloseSRAM();
    return result;
}

int Test_Serialize_Box(void) {
    int result = 0;
    struct Box data = {0};
    uint8_t buffer[sBoxEnd - sBox] = {0};
    OpenSRAM(MBANK(asBox));

    const uint32_t size = sBoxEnd - sBox;
    const uint8_t* sram = GBToRAMAddr(sBox);
    const uint8_t* start = sram;
    const uint8_t* end = Deserialize_Box(&data, start);
    if(end - start != size) {
        fprintf(stderr, "[%s - FAILED] Failed to deserialize box data. Expected size %d, got %d\n",
            __func__,
            size,
            (int)(end - start));
        result = -1;
        goto quit;
    }
    
    start = buffer;
    end = Serialize_Box(buffer, &data);
    if(end - start != size) {
        fprintf(stderr, "[%s - FAILED] Failed to serialize box data. Expected size %d, got %d\n",
            __func__,
            size,
            (int)(end - start));
        result = -1;
        goto quit;
    }

    if(memcmp(buffer, sram, size) != 0) {
        fprintf(stderr, "[%s - FAILED] Failed to produce matching serialized box data\n",
            __func__);
        FILE* f;
        f = fopen("box_data_gen.bin", "wb");
        fwrite(buffer, 1, size, f);
        fclose(f);
        f = fopen("box_data_base.bin", "wb");
        fwrite(sram, 1, size, f);
        fclose(f);
        result = -1;
        goto quit;
    }

    printf("[%s - SUCCESS]\n", __func__);

quit:
    CloseSRAM();
    return result;
}

int Test_Serialization(void) {
    int res = 0;
    res |= Test_Serialize_PlayerData();
    res |= Test_Serialize_PokemonData();
    res |= Test_Serialize_CurMapData();
    res |= Test_Serialize_OptionsData();
    res |= Test_Serialize_Box();
    if(res < 0)
        return FALSE;
    return TRUE;
}


