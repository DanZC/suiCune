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

// This crap is needed so gcc doesn't freak out about unaligned pointers. 
// Some structs are still packed so that the wram struct is correctly sized.
// Serialization will hopefully make struct packing unnecessary.
#define UNALIGNED_FIELD_PTR(base, struct, field, type) (type*)((uint8_t*)base + offsetof(struct, field))

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

uint8_t* Serialize_ByteBuffer(uint8_t* dest, const uint8_t* src, size_t size) {
    memcpy(dest, src, size);
    return dest + size;
}

#define Serialize_ByteArray(dest, src) Serialize_ByteBuffer(dest, src, sizeof(src))
#define Serialize_Skip(dest, src) dest += sizeof(src)

uint8_t* Serialize_BoxMon(uint8_t* dest, const struct BoxMon* src) {
    Serialize_Species(dest + MON_SPECIES, src->species);
    Serialize_Item(dest + MON_ITEM, src->item);
    for(int i = 0; i < NUM_MOVES; ++i) {
        Serialize_Move(dest + MON_MOVES + i, src->moves[i]);
    }
    Serialize_U16_LE(dest + MON_ID, src->id);
    Serialize_ByteArray(dest + MON_EXP, src->exp);
    for(int i = 0; i < (MON_DVS - MON_STAT_EXP) / 2; i++) {
        Serialize_U16_Native(dest + MON_STAT_EXP + (i * 2), src->statExp[i]);
    }
    Serialize_U16_LE(dest + MON_DVS, src->DVs);
    for(int i = 0; i < NUM_MOVES; ++i) {
        dest[MON_PP + i] = src->PP[i];
    }
    dest[MON_HAPPINESS] = src->happiness;
    dest[MON_POKERUS] = src->pokerusStatus;
    dest[MON_CAUGHTTIME] = src->caughtTimeLevel;// Crystal uses caught data, all in 2 bytes
    dest[MON_CAUGHTGENDER] = src->caughtGenderLocation;
    dest[MON_LEVEL] = src->level;
    return dest + BOXMON_STRUCT_LENGTH;
}

uint8_t* Serialize_PartyMon(uint8_t* dest, const struct PartyMon* mon) {
    Serialize_BoxMon(dest, &mon->mon);
    dest[MON_STATUS] = mon->status;
    dest[MON_STATUS + 1] = mon->unused;
    Serialize_U16_Native(dest + MON_HP, mon->HP);
    Serialize_U16_Native(dest + MON_MAXHP, mon->maxHP);
    Serialize_U16_Native(dest + MON_ATK, mon->attack);
    Serialize_U16_Native(dest + MON_DEF, mon->defense);
    Serialize_U16_Native(dest + MON_SPD, mon->speed);
    Serialize_U16_Native(dest + MON_SAT, mon->spclAtk);
    Serialize_U16_Native(dest + MON_SDF, mon->spclDef);
    return dest + PARTYMON_STRUCT_LENGTH;
}

uint8_t* Serialize_NicknamedMon(uint8_t* dest, const struct NicknamedMon* mon) {
    Serialize_PartyMon(dest, &mon->pmon);
    Serialize_ByteArray(dest + PARTYMON_STRUCT_LENGTH, mon->nickname);
    return dest + NICKNAMED_MON_STRUCT_LENGTH;
}

uint8_t* Serialize_Roamer(uint8_t* dest, const struct Roamer* roamer) {
    dest = Serialize_Species(dest, roamer->species);
    *(dest++) = roamer->level;
    *(dest++) = roamer->mapId.mapGroup;
    *(dest++) = roamer->mapId.mapNumber;
    *(dest++) = roamer->HP;
    dest = Serialize_U16_LE(dest, roamer->DVs);
    return dest;
}

uint8_t* Serialize_BattleTowerPartyMon(uint8_t* dest, const struct BattleTowerPartyMon* mon) {
    Serialize_PartyMon(dest, &mon->mon);
    dest = Serialize_ByteArray(dest + PARTYMON_STRUCT_LENGTH, mon->monName);
    return dest;
}

uint8_t* Serialize_BattleTowerData(uint8_t* dest, const struct BattleTowerData* data) {
    dest = Serialize_ByteArray(dest, data->name);
    *(dest++) = data->trainerClass;
    for(int i = 0; i < BATTLETOWER_PARTY_LENGTH; ++i)
        dest = Serialize_BattleTowerPartyMon(dest, &data->party[i]);
    dest = Serialize_ByteArray(dest, data->trainerData);
    return dest;
}

uint8_t* Serialize_MapId(uint8_t* dest, struct MapId mapId) {
    dest[0] = mapId.mapGroup;
    dest[1] = mapId.mapNumber;
    return dest + 2;
}

uint8_t* Serialize_Object(uint8_t* dest, const struct Object* bc) {
    dest[OBJECT_SPRITE] = bc->sprite;
    dest[OBJECT_MAP_OBJECT_INDEX] = bc->mapObjectIndex;
    dest[OBJECT_SPRITE_TILE] = bc->spriteTile;
    dest[OBJECT_MOVEMENTTYPE] = bc->movementType;
    dest[OBJECT_FLAGS1] = bc->flags1;
    dest[OBJECT_FLAGS2] = bc->flags2;
    dest[OBJECT_PALETTE] = bc->palette;
    dest[OBJECT_DIRECTION_WALKING] = bc->dirWalking;
    dest[OBJECT_FACING] = bc->facing;
    dest[OBJECT_STEP_TYPE] = bc->stepType;
    dest[OBJECT_STEP_DURATION] = bc->stepDuration;
    dest[OBJECT_ACTION] = bc->action;
    dest[OBJECT_STEP_FRAME] = bc->stepFrame;
    dest[OBJECT_FACING_STEP] = bc->facingStep;
    dest[OBJECT_NEXT_TILE] = bc->nextTile;
    dest[OBJECT_STANDING_TILE] = bc->standingTile;
    dest[OBJECT_NEXT_MAP_X] = bc->nextMapX;
    dest[OBJECT_NEXT_MAP_Y] = bc->nextMapY;
    dest[OBJECT_MAP_X] = bc->mapX;
    dest[OBJECT_MAP_Y] = bc->mapY;
    dest[OBJECT_INIT_X] = bc->initX;
    dest[OBJECT_INIT_Y] = bc->initY;
    dest[OBJECT_RADIUS] = bc->radius;
    dest[OBJECT_SPRITE_X] = bc->spriteX;
    dest[OBJECT_SPRITE_Y] = bc->spriteY;
    dest[OBJECT_SPRITE_X_OFFSET] = bc->spriteXOffset;
    dest[OBJECT_SPRITE_Y_OFFSET] = bc->spriteYOffset;
    dest[OBJECT_MOVEMENT_BYTE_INDEX] = bc->movementByteIndex;
    dest[OBJECT_1C] = bc->field_1C;
    dest[OBJECT_1D] = bc->field_1D;
    dest[OBJECT_1E] = bc->field_1E;
    dest[OBJECT_1F] = bc->field_1F;
    dest[OBJECT_RANGE] = bc->range;
    return dest + OBJECT_LENGTH;
}

uint8_t* Serialize_MapObject(uint8_t* dest, const struct MapObject* bc) {
    dest[MAPOBJECT_OBJECT_STRUCT_ID] = bc->structId;
    dest[MAPOBJECT_SPRITE] = bc->sprite;
    dest[MAPOBJECT_Y_COORD] = bc->objectYCoord;
    dest[MAPOBJECT_X_COORD] = bc->objectXCoord;
    dest[MAPOBJECT_MOVEMENT] = bc->objectMovement;
    dest[MAPOBJECT_RADIUS] = bc->objectRadius;
    dest[MAPOBJECT_HOUR] = bc->objectHour;
    dest[MAPOBJECT_TIMEOFDAY] = bc->objectTimeOfDay;
    dest[MAPOBJECT_COLOR] = bc->objectColor;
    dest[MAPOBJECT_RANGE] = bc->objectRange;
    Serialize_U16_LE(dest + MAPOBJECT_SCRIPT_POINTER, bc->objectScript);
    Serialize_U16_LE(dest + MAPOBJECT_EVENT_FLAG, bc->objectEventFlag);
    Serialize_ByteArray(dest + MAPOBJECT_EVENT_FLAG + 2, bc->padding);
    return dest + MAPOBJECT_LENGTH;
}

uint8_t* Serialize_Box(uint8_t* dest, const struct Box* box) {
    *(dest++) = box->count;
    for(int i = 0; i < MONS_PER_BOX + 1; ++i)
        dest = Serialize_Species(dest, box->species[i]);
    for(int i = 0; i < MONS_PER_BOX; ++i)
        dest = Serialize_BoxMon(dest, &box->mons[i]);
    for(int i = 0; i < MONS_PER_BOX; ++i)
        dest = Serialize_ByteArray(dest, box->monOT[i]);
    for(int i = 0; i < MONS_PER_BOX; ++i)
        dest = Serialize_ByteArray(dest, box->monNicknames[i]);
    return dest;
}

uint8_t* Serialize_OptionsData(uint8_t* dest, const struct OptionsData* data) {
    dest[0] = data->options;
    dest[1] = data->saveFileExists;
    dest[2] = data->textboxFrame;
    dest[3] = data->textboxFlags;
    dest[4] = data->GBPrinterBrightness;
    dest[5] = data->options2;
    Serialize_ByteArray(dest + 6, data->unused);
    return dest + 8;
}

uint8_t* Serialize_CurMapData(uint8_t* dest, const struct CurMapData* data) {
    dest = Serialize_ByteArray(dest, data->visitedSpawns);
    *(dest++) = data->digWarpNumber;
    *(dest++) = data->digMapGroup;
    *(dest++) = data->digMapNumber;
    *(dest++) = data->backupWarpNumber;
    *(dest++) = data->backupMapGroup;
    *(dest++) = data->backupMapNumber;
    dest += 3; // skip 3 bytes
    *(dest++) = data->lastSpawnMapGroup;
    *(dest++) = data->lastSpawnMapNumber;
    *(dest++) = data->warpNumber;
    *(dest++) = data->mapGroup;
    *(dest++) = data->mapNumber;
    *(dest++) = data->yCoord;
    *(dest++) = data->xCoord;
    dest = Serialize_ByteArray(dest, data->screenSave);
    return dest;
}

uint8_t* Serialize_PlayerData(uint8_t* dest, const struct PlayerData* data) {
    dest = Serialize_U16_LE(dest, data->playerID);
    dest = Serialize_ByteArray(dest, data->playerName);
    dest = Serialize_ByteArray(dest, data->momsName);
    dest = Serialize_ByteArray(dest, data->rivalName);
    dest = Serialize_ByteArray(dest, data->redsName);
    dest = Serialize_ByteArray(dest, data->greensName);
    *(dest++) = data->savedAtLeastOnce;
    *(dest++) = data->spawnAfterChampion;
    // init time set at newgame
    *(dest++) = data->startDay;
    *(dest++) = data->startHour;
    *(dest++) = data->startMinute;
    *(dest++) = data->startSecond;
    dest = Serialize_ByteArray(dest, data->RTC);
    dest = Serialize_ByteArray(dest, data->skip_104);
    // bit 7: dst
    *(dest++) = data->DST;
    // used only for BANK(wGameTime)
    //union wGameTime
    *(dest++) = data->gameTimeCap;
    dest = Serialize_U16_LE(dest, data->gameTimeHours);
    *(dest++) = data->gameTimeMinutes;
    *(dest++) = data->gameTimeSeconds;
    *(dest++) = data->gameTimeFrames;
    dest = Serialize_ByteArray(dest, data->skip_105);
    *(dest++) = data->curDay;
    dest = Serialize_ByteArray(dest, data->skip_106);
    *(dest++) = data->objectFollow_Leader;
    *(dest++) = data->objectFollow_Follower;
    *(dest++) = data->centeredObject;
    *(dest++) = data->followerMovementQueueLength;
    dest = Serialize_ByteArray(dest, data->followMovementQueue);
    dest = Serialize_Object(dest, &data->playerStruct);
    // player is object struct 0
    // wObjectStruct1 - wObjectStruct12
    // for n, 1, NUM_OBJECT_STRUCTS
    for(int i = 0; i < (NUM_OBJECT_STRUCTS) - 1; ++i)
        dest = Serialize_Object(dest, data->objectStruct + i);
    dest = Serialize_ByteArray(dest, data->cmdQueue);
    dest = Serialize_ByteArray(dest, data->zipCode_Saved);
    dest = Serialize_ByteArray(dest, data->skip_107);
    //union wMapObjects
    dest = Serialize_MapObject(dest, &data->playerObject);
    // player is map object 0
    // wMap1Object - wMap15Object
    // for n, 1, NUM_OBJECTS
    for(int i = 0; i < (NUM_OBJECTS) - 1; ++i)
        dest = Serialize_MapObject(dest, data->mapObject + i);
    dest = Serialize_ByteArray(dest, data->objectMasks);
    dest = Serialize_ByteArray(dest, data->variableSprites);
    *(dest++) = data->enteredMapFromContinue;
    dest = Serialize_ByteArray(dest, data->skip_108);
    *(dest++) = data->timeOfDayPal;
    dest = Serialize_ByteArray(dest, data->skip_109);
    *(dest++) = data->timeOfDayPalFlags;
    *(dest++) = data->timeOfDayPalset;
    *(dest++) = data->curTimeOfDay;
    *(dest++) = data->skip_110[0];
    dest = Serialize_U16_LE(dest, data->secretID);
    *(dest++) = data->statusFlags;
    *(dest++) = data->statusFlags2;
    dest = Serialize_ByteArray(dest, data->money);
    dest = Serialize_ByteArray(dest, data->momsMoney);
    *(dest++) = data->momSavingMoney;
    dest = Serialize_U16_LE(dest, data->coins);
    dest = Serialize_ByteArray(dest, data->badges);
    dest = Serialize_ByteArray(dest, data->TMsHMs);
    *(dest++) = data->numItems;
    for(int i = 0; i < MAX_ITEMS * 2; i += 2) {
        dest = Serialize_Item(dest, data->items[i]);
        *(dest++) = (uint8_t)data->items[i + 1];
    }
    dest = Serialize_Item(dest, data->items[MAX_ITEMS * 2]);
    *(dest++) = data->numKeyItems;
    for(int i = 0; i < MAX_KEY_ITEMS + 1; ++i)
        dest = Serialize_Item(dest, data->keyItems[i]);
    *(dest++) = data->numBalls;
    for(int i = 0; i < MAX_BALLS * 2; i += 2) {
        dest = Serialize_Item(dest, data->balls[i]);
        *(dest++) = (uint8_t)data->balls[i + 1];
    }
    dest = Serialize_Item(dest, data->balls[MAX_BALLS * 2]);
    *(dest++) = data->numPCItems;
    for(int i = 0; i < MAX_PC_ITEMS * 2; i += 2) {
        dest = Serialize_Item(dest, data->PCItems[i]);
        *(dest++) = (uint8_t)data->PCItems[i + 1];
    }
    dest = Serialize_Item(dest, data->PCItems[MAX_PC_ITEMS * 2]);
    *(dest++) = data->pokegearFlags;
    *(dest++) = data->radioTuningKnob;
    *(dest++) = data->lastDexMode;
    // uint8_t skip_111[1];
    Serialize_Skip(dest, data->skip_111);
    *(dest++) = data->whichRegisteredItem;
    *(dest++) = data->registeredItem;
    *(dest++) = data->playerState;
    *(dest++) = data->hallOfFameCount;
    // uint8_t skip_112[1];
    Serialize_Skip(dest, data->skip_112);
    dest = Serialize_ByteArray(dest, data->tradeFlags);
    // uint8_t skip_113[1];
    Serialize_Skip(dest, data->skip_113);
    *(dest++) = data->mooMooBerries;
    *(dest++) = data->undergroundSwitchPositions;
    *(dest++) = data->farfetchdPosition;
    // uint8_t skip_114[13];
    dest = Serialize_ByteArray(dest, data->skip_114);
    // map scene ids
    *(dest++) = data->Pokecenter2FSceneID;
    *(dest++) = data->TradeCenterSceneID;
    *(dest++) = data->ColosseumSceneID;
    *(dest++) = data->TimeCapsuleSceneID;
    *(dest++) = data->PowerPlantSceneID;
    *(dest++) = data->CeruleanGymSceneID;
    *(dest++) = data->Route25SceneID;
    *(dest++) = data->TrainerHouseB1FSceneID;
    *(dest++) = data->VictoryRoadGateSceneID;
    *(dest++) = data->SaffronMagnetTrainStationSceneID;
    *(dest++) = data->Route16GateSceneID;
    *(dest++) = data->Route17Route18GateSceneID;
    *(dest++) = data->IndigoPlateauPokecenter1FSceneID;
    *(dest++) = data->WillsRoomSceneID;
    *(dest++) = data->KogasRoomSceneID;
    *(dest++) = data->BrunosRoomSceneID;
    *(dest++) = data->KarensRoomSceneID;
    *(dest++) = data->LancesRoomSceneID;
    *(dest++) = data->HallOfFameSceneID;
    *(dest++) = data->Route27SceneID;
    *(dest++) = data->NewBarkTownSceneID;
    *(dest++) = data->ElmsLabSceneID;
    *(dest++) = data->PlayersHouse1FSceneID;
    *(dest++) = data->Route29SceneID;
    *(dest++) = data->CherrygroveCitySceneID;
    *(dest++) = data->MrPokemonsHouseSceneID;
    *(dest++) = data->Route32SceneID;
    *(dest++) = data->Route35NationalParkGateSceneID;
    *(dest++) = data->Route36SceneID;
    *(dest++) = data->Route36NationalParkGateSceneID;
    *(dest++) = data->AzaleaTownSceneID;
    *(dest++) = data->GoldenrodGymSceneID;
    *(dest++) = data->GoldenrodMagnetTrainStationSceneID;
    *(dest++) = data->GoldenrodPokecenter1FSceneID;
    *(dest++) = data->OlivineCitySceneID;
    *(dest++) = data->Route34SceneID;
    *(dest++) = data->Route34IlexForestGateSceneID;
    *(dest++) = data->EcruteakTinTowerEntranceSceneID;
    *(dest++) = data->WiseTriosRoomSceneID;
    *(dest++) = data->EcruteakPokecenter1FSceneID;
    *(dest++) = data->EcruteakGymSceneID;
    *(dest++) = data->MahoganyTownSceneID;
    *(dest++) = data->Route42SceneID;
    *(dest++) = data->CianwoodCitySceneID;
    *(dest++) = data->BattleTower1FSceneID;
    *(dest++) = data->BattleTowerBattleRoomSceneID;
    *(dest++) = data->BattleTowerElevatorSceneID;
    *(dest++) = data->BattleTowerHallwaySceneID;
    *(dest++) = data->BattleTowerOutsideSceneID;
    *(dest++) = data->Route43GateSceneID;
    *(dest++) = data->MountMoonSceneID;
    *(dest++) = data->SproutTower3FSceneID;
    *(dest++) = data->TinTower1FSceneID;
    *(dest++) = data->BurnedTower1FSceneID;
    *(dest++) = data->BurnedTowerB1FSceneID;
    *(dest++) = data->RadioTower5FSceneID;
    *(dest++) = data->RuinsOfAlphOutsideSceneID;
    *(dest++) = data->RuinsOfAlphResearchCenterSceneID;
    *(dest++) = data->RuinsOfAlphHoOhChamberSceneID;
    *(dest++) = data->RuinsOfAlphKabutoChamberSceneID;
    *(dest++) = data->RuinsOfAlphOmanyteChamberSceneID;
    *(dest++) = data->RuinsOfAlphAerodactylChamberSceneID;
    *(dest++) = data->RuinsOfAlphInnerChamberSceneID;
    *(dest++) = data->MahoganyMart1FSceneID;
    *(dest++) = data->TeamRocketBaseB1FSceneID;
    *(dest++) = data->TeamRocketBaseB2FSceneID;
    *(dest++) = data->TeamRocketBaseB3FSceneID;
    *(dest++) = data->GoldenrodUndergroundSwitchRoomEntrancesSceneID;
    *(dest++) = data->SilverCaveRoom3SceneID;
    *(dest++) = data->VictoryRoadSceneID;
    *(dest++) = data->DragonsDenB1FSceneID;
    *(dest++) = data->DragonShrineSceneID;
    *(dest++) = data->OlivinePortSceneID;
    *(dest++) = data->VermilionPortSceneID;
    *(dest++) = data->FastShip1FSceneID;
    *(dest++) = data->FastShipB1FSceneID;
    *(dest++) = data->MountMoonSquareSceneID;
    *(dest++) = data->MobileTradeRoomSceneID;
    *(dest++) = data->MobileBattleRoomSceneID;
//     uint8_t skip_115[49];
    Serialize_Skip(dest, data->skip_115);
//     // fight counts
    *(dest++) = data->JackFightCount;
    *(dest++) = data->BeverlyFightCount;
//     // unreferenced
    *(dest++) = data->HueyFightCount;
    *(dest++) = data->GavenFightCount;
    *(dest++) = data->BethFightCount;
    *(dest++) = data->JoseFightCount;
    *(dest++) = data->ReenaFightCount;
    *(dest++) = data->JoeyFightCount;
    *(dest++) = data->WadeFightCount;
    *(dest++) = data->RalphFightCount;
    *(dest++) = data->LizFightCount;
    *(dest++) = data->AnthonyFightCount;
    *(dest++) = data->ToddFightCount;
    *(dest++) = data->GinaFightCount;
    *(dest++) = data->IrwinFightCount;
//     // unreferenced
    *(dest++) = data->ArnieFightCount;
    *(dest++) = data->AlanFightCount;
    *(dest++) = data->DanaFightCount;
    *(dest++) = data->ChadFightCount;
    *(dest++) = data->DerekFightCount;
//     // unreferenced
    *(dest++) = data->TullyFightCount;
    *(dest++) = data->BrentFightCount;
    *(dest++) = data->TiffanyFightCount;
    *(dest++) = data->VanceFightCount;
    *(dest++) = data->WiltonFightCount;
    *(dest++) = data->KenjiFightCount;
//     // unreferenced
    *(dest++) = data->ParryFightCount;
    *(dest++) = data->ErinFightCount;
//     uint8_t skip_116[100];
    Serialize_Skip(dest, data->skip_116);
    dest = Serialize_ByteArray(dest, data->eventFlags);
    *(dest++) = data->curBox;
    // uint8_t skip_117[2];
    Serialize_Skip(dest, data->skip_117);
    dest = Serialize_ByteArray(dest, data->boxNames);
    *(dest++) = data->celebiEvent;
    // uint8_t skip_118[1];
    Serialize_Skip(dest, data->skip_118);
    *(dest++) = data->bikeFlags;
    // uint8_t skip_119[1];
    Serialize_Skip(dest, data->skip_119);
    dest = Serialize_U16_LE(dest, data->curMapSceneScriptPointer);
    dest = Serialize_U16_LE(dest, data->curCaller);
    *(dest++) = data->curMapWarpCount;
    dest = Serialize_U16_LE(dest, data->curMapWarpsPointer);
    *(dest++) = data->curMapCoordEventCount;
    dest = Serialize_U16_LE(dest, data->curMapCoordEventsPointer);
    *(dest++) = data->curMapBGEventCount;
    dest = Serialize_U16_LE(dest, data->curMapBGEventsPointer);
    *(dest++) = data->curMapObjectEventCount;
    dest = Serialize_U16_LE(dest, data->curMapObjectEventsPointer);
    *(dest++) = data->curMapSceneScriptCount;
    dest = Serialize_U16_LE(dest, data->curMapSceneScriptsPointer);
    *(dest++) = data->curMapCallbackCount;
    dest = Serialize_U16_LE(dest, data->curMapCallbacksPointer);
    // uint8_t skip_120[2];
    Serialize_Skip(dest, data->skip_120);
    // Sprite id of each decoration
    *(dest++) = data->decoBed;
    *(dest++) = data->decoCarpet;
    *(dest++) = data->decoPlant;
    *(dest++) = data->decoPoster;
    *(dest++) = data->decoConsole;
    *(dest++) = data->decoLeftOrnament;
    *(dest++) = data->decoRightOrnament;
    *(dest++) = data->decoBigDoll;
    // Items bought from Mom
    *(dest++) = data->whichMomItem;
    *(dest++) = data->whichMomItemSet;
    dest = Serialize_ByteArray(dest, data->momItemTriggerBalance);
    dest = Serialize_U16_LE(dest, data->dailyResetTimer);
    *(dest++) = data->dailyFlags1;
    *(dest++) = data->dailyFlags2;
    *(dest++) = data->swarmFlags;
    // uint8_t skip_121[2];
    Serialize_Skip(dest, data->skip_121);
    *(dest++) = data->timerEventStartDay;
    // uint8_t skip_122[3];
    Serialize_Skip(dest, data->skip_122);
    dest = Serialize_ByteArray(dest, data->fruitTreeFlags);
    // uint8_t skip_123[2];
    Serialize_Skip(dest, data->skip_123);
    dest = Serialize_U16_LE(dest, data->luckyNumberDayTimer);
    // uint8_t skip_124[2];
    Serialize_Skip(dest, data->skip_124);
    dest = Serialize_U16_LE(dest, data->specialPhoneCallID);
    // uint8_t skip_125[2];
    Serialize_Skip(dest, data->skip_125);
    dest = Serialize_ByteArray(dest, data->bugContestStartTime);
    // day, hour, min, sec
    *(dest++) = data->unusedTwoDayTimerOn;
    *(dest++) = data->unusedTwoDayTimer;
    *(dest++) = data->unusedTwoDayTimerStartDate;
    // uint8_t skip_126[4];
    Serialize_Skip(dest, data->skip_126);
    *(dest++) = data->mobileOrCable_LastSelection;
    *(dest++) = data->wdc41;
    dest = Serialize_ByteArray(dest, data->wdc42);
    *(dest++) = data->buenasPassword;
    *(dest++) = data->blueCardBalance;
    dest = Serialize_ByteArray(dest, data->dailyRematchFlags);
    dest = Serialize_ByteArray(dest, data->dailyPhoneItemFlags);
    dest = Serialize_ByteArray(dest, data->dailyPhoneTimeOfDayFlags);
    dest = Serialize_ByteArray(dest, data->wKenjiBreakTimer);
    // Kenji
    *(dest++) = data->yanmaMapGroup;
    *(dest++) = data->yanmaMapNumber;
    dest = Serialize_ByteArray(dest, data->playerMonSelection);
    *(dest++) = data->wdc5f;
    *(dest++) = data->wdc60;
    // uint8_t skip_127[18];
    Serialize_Skip(dest, data->skip_127);
    *(dest++) = data->stepCount;
    *(dest++) = data->poisonStepCount;
    // uint8_t skip_128[2];
    Serialize_Skip(dest, data->skip_128);
    *(dest++) = data->happinessStepCount;
    // uint8_t skip_129[1];
    Serialize_Skip(dest, data->skip_129);
    *(dest++) = data->parkBallsRemaining;
    dest = Serialize_U16_LE(dest, data->safariTimeRemaining);
    dest = Serialize_ByteArray(dest, data->phoneList);
    // uint8_t skip_130[22];
    Serialize_Skip(dest, data->skip_130);
    *(dest++) = data->luckyNumberShowFlag;
    // uint8_t skip_131[1];
    Serialize_Skip(dest, data->skip_131);
    dest = Serialize_U16_LE(dest, data->luckyIDNumber);
    *(dest++) = data->repelEffect;
    dest = Serialize_U16_LE(dest, data->bikeStep);
    *(dest++) = data->kurtApricornQuantity;
    return dest;
}

uint8_t* Serialize_PokemonData(uint8_t* dest, const struct PokemonData* data) {
    *(dest++) = data->partyCount;
    for(int i = 0; i < PARTY_LENGTH; ++i)
        dest = Serialize_Species(dest, data->partySpecies[i]);
    *(dest++) = data->partyEnd; // unused
    // older code doesn't check wPartyCount
    // wPartyMon1 - wPartyMon6
    //union wPartyMons
    // for n, 1, PARTY_LENGTH + 1
    // wPartyMon1 - wPartyMon6
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        dest = Serialize_PartyMon(dest, data->partyMon + i);
    }
    // wPartyMon1OT - wPartyMon6OT
    //union wPartyMonOTs
    // for n, 1, PARTY_LENGTH + 1
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        dest = Serialize_ByteArray(dest, data->partyMonOT[i]);
    }
    // wPartyMon1Nickname - wPartyMon6Nickname
    //union wPartyMonNicknames
    // for n, 1, PARTY_LENGTH + 1
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        dest = Serialize_ByteArray(dest, data->partyMonNickname[i]);
    }
    // uint8_t partyMonNicknamesEnd[22];
    Serialize_Skip(dest, data->partyMonNicknamesEnd);
    dest = Serialize_ByteArray(dest, data->pokedexCaught);
    dest = Serialize_ByteArray(dest, data->pokedexSeen);
    dest = Serialize_ByteArray(dest, data->unownDex);
    *(dest++) = data->unlockedUnowns;
    *(dest++) = data->firstUnownSeen;
    // bit 7: active
    // bit 6: egg ready
    // bit 5: monsters are compatible
    // bit 0: monster 1 in day-care
    *(dest++) = data->dayCareMan;
    dest = Serialize_ByteArray(dest, data->breedMon1Nickname);
    dest = Serialize_ByteArray(dest, data->breedMon1OT);
    dest = Serialize_BoxMon(dest, &data->breedMon1);
    // bit 7: active
    // bit 0: monster 2 in day-care
    *(dest++) = data->dayCareLady;
    *(dest++) = data->stepsToEgg;
    //  z: yes
    // nz: no
    *(dest++) = data->breedMotherOrNonDitto;
    dest = Serialize_ByteArray(dest, data->breedMon2Nickname);
    dest = Serialize_ByteArray(dest, data->breedMon2OT);
    dest = Serialize_BoxMon(dest, &data->breedMon2);
    dest = Serialize_ByteArray(dest, data->eggMonNickname);
    dest = Serialize_ByteArray(dest, data->eggMonOT);
    dest = Serialize_BoxMon(dest, &data->eggMon);
    *(dest++) = data->bugContestSecondPartySpecies;
    dest = Serialize_PartyMon(dest, &data->contestMon);
    *(dest++) = data->dunsparceMapGroup;
    *(dest++) = data->dunsparceMapNumber;
    *(dest++) = data->fishingSwarmFlag;
    dest = Serialize_Roamer(dest, &data->roamMon1);
    dest = Serialize_Roamer(dest, &data->roamMon2);
    dest = Serialize_Roamer(dest, &data->roamMon3);
    *(dest++) = data->roamMons_CurMapNumber;
    *(dest++) = data->roamMons_CurMapGroup;
    *(dest++) = data->roamMons_LastMapNumber;
    *(dest++) = data->roamMons_LastMapGroup;
    *(dest++) = data->bestMagikarpLengthFeet;
    *(dest++) = data->bestMagikarpLengthInches;
    dest = Serialize_ByteArray(dest, data->magikarpRecordHoldersName);
    return dest;
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

const uint8_t* Deserialize_ByteBuffer(uint8_t* dest, const uint8_t* src, size_t size) {
    memcpy(dest, src, size);
    return src + size;
}

#define Deserialize_ByteArray(dest, src) Deserialize_ByteBuffer(dest, src, sizeof(dest))

const uint8_t* Deserialize_BoxMon(struct BoxMon* dest, const uint8_t* src) {
    Deserialize_Species(&dest->species, src + MON_SPECIES);
    Deserialize_Item(&dest->item, src + MON_ITEM);
    for(int i = 0; i < NUM_MOVES; ++i) {
        Deserialize_Move(&dest->moves[i], src + MON_MOVES + i);
    }
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(dest, struct BoxMon, id, uint16_t), src + MON_ID);
    Deserialize_ByteArray(dest->exp, src + MON_EXP);
    for(int i = 0; i < (MON_DVS - MON_STAT_EXP) / 2; i++) {
        Deserialize_U16_Native(UNALIGNED_FIELD_PTR(dest, struct BoxMon, statExp, uint16_t) + i, src + MON_STAT_EXP + (i * 2));
    }
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(dest, struct BoxMon, DVs, uint16_t), src + MON_DVS);
    for(int i = 0; i < NUM_MOVES; ++i) {
        dest->PP[i] = src[MON_PP + i];
    }
    dest->happiness = src[MON_HAPPINESS];
    dest->pokerusStatus = src[MON_POKERUS];
    dest->caughtTimeLevel = src[MON_CAUGHTTIME]; // Crystal uses caught data, all in 2 bytes
    dest->caughtGenderLocation = src[MON_CAUGHTGENDER];
    dest->level = src[MON_LEVEL];
    return src + BOXMON_STRUCT_LENGTH;
}

const uint8_t* Deserialize_PartyMon(struct PartyMon* mon, const uint8_t* src) {
    Deserialize_BoxMon(&mon->mon, src);
    mon->status = src[MON_STATUS];
    mon->unused = src[MON_STATUS + 1];
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(mon, struct PartyMon, HP, uint16_t), src + MON_HP);
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(mon, struct PartyMon, maxHP, uint16_t), src + MON_MAXHP);
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(mon, struct PartyMon, attack, uint16_t), src + MON_ATK);
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(mon, struct PartyMon, defense, uint16_t), src + MON_DEF);
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(mon, struct PartyMon, speed, uint16_t), src + MON_SPD);
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(mon, struct PartyMon, spclAtk, uint16_t), src + MON_SAT);
    Deserialize_U16_LE(UNALIGNED_FIELD_PTR(mon, struct PartyMon, spclDef, uint16_t), src + MON_SDF);
    return src + PARTYMON_STRUCT_LENGTH;
}

const uint8_t* Deserialize_NicknamedMon(struct NicknamedMon* mon, const uint8_t* src) {
    Deserialize_PartyMon(&mon->pmon, src);
    Deserialize_ByteArray(mon->nickname, src + PARTYMON_STRUCT_LENGTH);
    return src + NICKNAMED_MON_STRUCT_LENGTH;
}

const uint8_t* Deserialize_Roamer(struct Roamer* roamer, const uint8_t* src) {
    src = Deserialize_Species(&roamer->species, src);
    roamer->level = *(src++);
    roamer->mapId.mapGroup = *(src++);
    roamer->mapId.mapNumber = *(src++);
    roamer->HP = *(src++);
    src = Deserialize_U16_LE(UNALIGNED_FIELD_PTR(roamer, struct Roamer, DVs, uint16_t), src);
    return src;
}

const uint8_t* Deserialize_BattleTowerPartyMon(struct BattleTowerPartyMon* mon, const uint8_t* src) {
    Deserialize_PartyMon(&mon->mon, src);
    src = Deserialize_ByteArray(mon->monName, src + PARTYMON_STRUCT_LENGTH);
    return src;
}

const uint8_t* Deserialize_BattleTowerData(struct BattleTowerData* data, const uint8_t* src) {
    src = Deserialize_ByteArray(data->name, src);
    data->trainerClass = *(src++);
    for(int i = 0; i < BATTLETOWER_PARTY_LENGTH; ++i)
        src = Deserialize_BattleTowerPartyMon(&data->party[i], src);
    src = Deserialize_ByteArray(data->trainerData, src);
    return src;
}

const uint8_t* Deserialize_MapId(struct MapId* mapId, const uint8_t* src) {
    mapId->mapGroup = src[0];
    mapId->mapNumber = src[1];
    return src + 2;
}

const uint8_t* Deserialize_Object(struct Object* bc, const uint8_t* src) {
    bc->sprite = src[OBJECT_SPRITE];
    bc->mapObjectIndex = src[OBJECT_MAP_OBJECT_INDEX];
    bc->spriteTile = src[OBJECT_SPRITE_TILE];
    bc->movementType = src[OBJECT_MOVEMENTTYPE];
    bc->flags1 = src[OBJECT_FLAGS1];
    bc->flags2 = src[OBJECT_FLAGS2];
    bc->palette = src[OBJECT_PALETTE];
    bc->dirWalking = src[OBJECT_DIRECTION_WALKING];
    bc->facing = src[OBJECT_FACING];
    bc->stepType = src[OBJECT_STEP_TYPE];
    bc->stepDuration = src[OBJECT_STEP_DURATION];
    bc->action = src[OBJECT_ACTION];
    bc->stepFrame = src[OBJECT_STEP_FRAME];
    bc->facingStep = src[OBJECT_FACING_STEP];
    bc->nextTile = src[OBJECT_NEXT_TILE];
    bc->standingTile = src[OBJECT_STANDING_TILE];
    bc->nextMapX = src[OBJECT_NEXT_MAP_X];
    bc->nextMapY = src[OBJECT_NEXT_MAP_Y];
    bc->mapX = src[OBJECT_MAP_X];
    bc->mapY = src[OBJECT_MAP_Y];
    bc->initX = src[OBJECT_INIT_X];
    bc->initY = src[OBJECT_INIT_Y];
    bc->radius = src[OBJECT_RADIUS];
    bc->spriteX = src[OBJECT_SPRITE_X];
    bc->spriteY = src[OBJECT_SPRITE_Y];
    bc->spriteXOffset = src[OBJECT_SPRITE_X_OFFSET];
    bc->spriteYOffset = src[OBJECT_SPRITE_Y_OFFSET];
    bc->movementByteIndex = src[OBJECT_MOVEMENT_BYTE_INDEX];
    bc->field_1C = src[OBJECT_1C];
    bc->field_1D = src[OBJECT_1D];
    bc->field_1E = src[OBJECT_1E];
    bc->field_1F = src[OBJECT_1F];
    bc->range = src[OBJECT_RANGE];
    return src + OBJECT_LENGTH;
}

const uint8_t* Deserialize_MapObject(struct MapObject* bc, const uint8_t* src) {
    bc->structId = src[MAPOBJECT_OBJECT_STRUCT_ID];
    bc->sprite = src[MAPOBJECT_SPRITE];
    bc->objectYCoord = src[MAPOBJECT_Y_COORD];
    bc->objectXCoord = src[MAPOBJECT_X_COORD];
    bc->objectMovement = src[MAPOBJECT_MOVEMENT];
    bc->objectRadius = src[MAPOBJECT_RADIUS];
    bc->objectHour = src[MAPOBJECT_HOUR];
    bc->objectTimeOfDay = src[MAPOBJECT_TIMEOFDAY];
    bc->objectColor = src[MAPOBJECT_COLOR];
    bc->objectRange = src[MAPOBJECT_RANGE];
    Deserialize_U16_LE(&bc->objectScript, src + MAPOBJECT_SCRIPT_POINTER);
    Deserialize_U16_LE(&bc->objectEventFlag, src + MAPOBJECT_EVENT_FLAG);
    Deserialize_ByteArray(bc->padding, src + MAPOBJECT_EVENT_FLAG + 2);
    return src + MAPOBJECT_LENGTH;
}

const uint8_t* Deserialize_Box(struct Box* box, const uint8_t* src) {
    box->count = *(src++);
    for(int i = 0; i < MONS_PER_BOX + 1; ++i)
        src = Deserialize_Species(&box->species[i], src);
    for(int i = 0; i < MONS_PER_BOX; ++i)
        src = Deserialize_BoxMon(&box->mons[i], src);
    for(int i = 0; i < MONS_PER_BOX; ++i)
        src = Deserialize_ByteArray(box->monOT[i], src);
    for(int i = 0; i < MONS_PER_BOX; ++i)
        src = Deserialize_ByteArray(box->monNicknames[i], src);
    return src;
}

const uint8_t* Deserialize_OptionsData(struct OptionsData* data, const uint8_t* src) {
    data->options = src[0];
    data->saveFileExists = src[1];
    data->textboxFrame = src[2];
    data->textboxFlags = src[3];
    data->GBPrinterBrightness = src[4];
    data->options2 = src[5];
    Deserialize_ByteArray(data->unused, src + 6);
    return src + 8;
}

const uint8_t* Deserialize_CurMapData(struct CurMapData* data, const uint8_t* src) {
    src = Deserialize_ByteArray(data->visitedSpawns, src);
    data->digWarpNumber = *(src++);
    data->digMapGroup = *(src++);
    data->digMapNumber = *(src++);
    data->backupWarpNumber = *(src++);
    data->backupMapGroup = *(src++);
    data->backupMapNumber = *(src++);
    src += 3; // skip 3 bytes
    data->lastSpawnMapGroup = *(src++);
    data->lastSpawnMapNumber = *(src++);
    data->warpNumber = *(src++);
    data->mapGroup = *(src++);
    data->mapNumber = *(src++);
    data->yCoord = *(src++);
    data->xCoord = *(src++);
    src = Deserialize_ByteArray(data->screenSave, src);
    return src;
}

const uint8_t* Deserialize_PlayerData(struct PlayerData* data, const uint8_t* src) {
    src = Deserialize_U16_LE(&data->playerID, src);
    src = Deserialize_ByteArray(data->playerName, src);
    src = Deserialize_ByteArray(data->momsName, src);
    src = Deserialize_ByteArray(data->rivalName, src);
    src = Deserialize_ByteArray(data->redsName, src);
    src = Deserialize_ByteArray(data->greensName, src);
    data->savedAtLeastOnce = *(src++);
    data->spawnAfterChampion = *(src++);
    data->startDay = *(src++);
    data->startHour = *(src++);
    data->startMinute = *(src++);
    data->startSecond = *(src++);
    src = Deserialize_ByteArray(data->RTC, src);
    src = Deserialize_ByteArray(data->skip_104, src);
    data->DST = *(src++);
    data->gameTimeCap = *(src++);
    src = Deserialize_U16_LE(&data->gameTimeHours, src);
    data->gameTimeMinutes = *(src++);
    data->gameTimeSeconds = *(src++);
    data->gameTimeFrames = *(src++);
    src = Deserialize_ByteArray(data->skip_105, src);
    data->curDay = *(src++);
    src = Deserialize_ByteArray(data->skip_106, src);
    data->objectFollow_Leader = *(src++);
    data->objectFollow_Follower = *(src++);
    data->centeredObject = *(src++);
    data->followerMovementQueueLength = *(src++);
    src = Deserialize_ByteArray(data->followMovementQueue, src);
    src = Deserialize_Object(&data->playerStruct, src);
    for(int i = 0; i < (NUM_OBJECT_STRUCTS) - 1; ++i)
        src = Deserialize_Object(data->objectStruct + i, src);
    src = Deserialize_ByteArray(data->cmdQueue, src);
    src = Deserialize_ByteArray(data->zipCode_Saved, src);
    src = Deserialize_ByteArray(data->skip_107, src);
    src = Deserialize_MapObject(&data->playerObject, src);
    for(int i = 0; i < (NUM_OBJECTS) - 1; ++i)
        src = Deserialize_MapObject(data->mapObject + i, src);
    src = Deserialize_ByteArray(data->objectMasks, src);
    src = Deserialize_ByteArray(data->variableSprites, src);
    data->enteredMapFromContinue = *(src++);
    src = Deserialize_ByteArray(data->skip_108, src);
    data->timeOfDayPal = *(src++);
    src = Deserialize_ByteArray(data->skip_109, src);
    data->timeOfDayPalFlags = *(src++);
    data->timeOfDayPalset = *(src++);
    data->curTimeOfDay = *(src++);
    Serialize_Skip(src, data->skip_110);
    src = Deserialize_U16_LE(&data->secretID, src);
    data->statusFlags = *(src++);
    data->statusFlags2 = *(src++);
    src = Deserialize_ByteArray(data->money, src);
    src = Deserialize_ByteArray(data->momsMoney, src);
    data->momSavingMoney = *(src++);
    src = Deserialize_U16_LE(&data->coins, src);
    src = Deserialize_ByteArray(data->badges, src);
    src = Deserialize_ByteArray(data->TMsHMs, src);
    data->numItems = *(src++);
    for(int i = 0; i < MAX_ITEMS * 2; i += 2) {
        src = Deserialize_Item(&data->items[i], src);
        data->items[i + 1] = *(src++);
    }
    src = Deserialize_Item(&data->items[MAX_ITEMS * 2], src);
    data->numKeyItems = *(src++);
    for(int i = 0; i < MAX_KEY_ITEMS + 1; ++i)
        src = Deserialize_Item(data->keyItems + i, src);
    data->numBalls = *(src++);
    for(int i = 0; i < MAX_BALLS * 2; i += 2) {
        src = Deserialize_Item(&data->balls[i], src);
        data->balls[i + 1] = *(src++);
    }
    src = Deserialize_Item(&data->balls[MAX_BALLS * 2], src);
    data->numPCItems = *(src++);
    for(int i = 0; i < MAX_PC_ITEMS * 2; i += 2) {
        src = Deserialize_Item(&data->PCItems[i], src);
        data->PCItems[i + 1] = *(src++);
    }
    src = Deserialize_Item(&data->PCItems[MAX_PC_ITEMS * 2], src);
    data->pokegearFlags = *(src++);
    data->radioTuningKnob = *(src++);
    data->lastDexMode = *(src++);
    // uint8_t skip_111[1];
    Serialize_Skip(src, data->skip_111);
    data->whichRegisteredItem = *(src++);
    data->registeredItem = *(src++);
    data->playerState = *(src++);
    data->hallOfFameCount = *(src++);
    // uint8_t skip_112[1];
    Serialize_Skip(src, data->skip_112);
    src = Deserialize_ByteArray(data->tradeFlags, src);
    // uint8_t skip_113[1];
    Serialize_Skip(src, data->skip_113);
    data->mooMooBerries = *(src++);
    data->undergroundSwitchPositions = *(src++);
    data->farfetchdPosition = *(src++);
    // uint8_t skip_114[13];
    src = Deserialize_ByteArray(data->skip_114, src);
    // map scene ids
    data->Pokecenter2FSceneID = *(src++);
    data->TradeCenterSceneID = *(src++);
    data->ColosseumSceneID = *(src++);
    data->TimeCapsuleSceneID = *(src++);
    data->PowerPlantSceneID = *(src++);
    data->CeruleanGymSceneID = *(src++);
    data->Route25SceneID = *(src++);
    data->TrainerHouseB1FSceneID = *(src++);
    data->VictoryRoadGateSceneID = *(src++);
    data->SaffronMagnetTrainStationSceneID = *(src++);
    data->Route16GateSceneID = *(src++);
    data->Route17Route18GateSceneID = *(src++);
    data->IndigoPlateauPokecenter1FSceneID = *(src++);
    data->WillsRoomSceneID = *(src++);
    data->KogasRoomSceneID = *(src++);
    data->BrunosRoomSceneID = *(src++);
    data->KarensRoomSceneID = *(src++);
    data->LancesRoomSceneID = *(src++);
    data->HallOfFameSceneID = *(src++);
    data->Route27SceneID = *(src++);
    data->NewBarkTownSceneID = *(src++);
    data->ElmsLabSceneID = *(src++);
    data->PlayersHouse1FSceneID = *(src++);
    data->Route29SceneID = *(src++);
    data->CherrygroveCitySceneID = *(src++);
    data->MrPokemonsHouseSceneID = *(src++);
    data->Route32SceneID = *(src++);
    data->Route35NationalParkGateSceneID = *(src++);
    data->Route36SceneID = *(src++);
    data->Route36NationalParkGateSceneID = *(src++);
    data->AzaleaTownSceneID = *(src++);
    data->GoldenrodGymSceneID = *(src++);
    data->GoldenrodMagnetTrainStationSceneID = *(src++);
    data->GoldenrodPokecenter1FSceneID = *(src++);
    data->OlivineCitySceneID = *(src++);
    data->Route34SceneID = *(src++);
    data->Route34IlexForestGateSceneID = *(src++);
    data->EcruteakTinTowerEntranceSceneID = *(src++);
    data->WiseTriosRoomSceneID = *(src++);
    data->EcruteakPokecenter1FSceneID = *(src++);
    data->EcruteakGymSceneID = *(src++);
    data->MahoganyTownSceneID = *(src++);
    data->Route42SceneID = *(src++);
    data->CianwoodCitySceneID = *(src++);
    data->BattleTower1FSceneID = *(src++);
    data->BattleTowerBattleRoomSceneID = *(src++);
    data->BattleTowerElevatorSceneID = *(src++);
    data->BattleTowerHallwaySceneID = *(src++);
    data->BattleTowerOutsideSceneID = *(src++);
    data->Route43GateSceneID = *(src++);
    data->MountMoonSceneID = *(src++);
    data->SproutTower3FSceneID = *(src++);
    data->TinTower1FSceneID = *(src++);
    data->BurnedTower1FSceneID = *(src++);
    data->BurnedTowerB1FSceneID = *(src++);
    data->RadioTower5FSceneID = *(src++);
    data->RuinsOfAlphOutsideSceneID = *(src++);
    data->RuinsOfAlphResearchCenterSceneID = *(src++);
    data->RuinsOfAlphHoOhChamberSceneID = *(src++);
    data->RuinsOfAlphKabutoChamberSceneID = *(src++);
    data->RuinsOfAlphOmanyteChamberSceneID = *(src++);
    data->RuinsOfAlphAerodactylChamberSceneID = *(src++);
    data->RuinsOfAlphInnerChamberSceneID = *(src++);
    data->MahoganyMart1FSceneID = *(src++);
    data->TeamRocketBaseB1FSceneID = *(src++);
    data->TeamRocketBaseB2FSceneID = *(src++);
    data->TeamRocketBaseB3FSceneID = *(src++);
    data->GoldenrodUndergroundSwitchRoomEntrancesSceneID = *(src++);
    data->SilverCaveRoom3SceneID = *(src++);
    data->VictoryRoadSceneID = *(src++);
    data->DragonsDenB1FSceneID = *(src++);
    data->DragonShrineSceneID = *(src++);
    data->OlivinePortSceneID = *(src++);
    data->VermilionPortSceneID = *(src++);
    data->FastShip1FSceneID = *(src++);
    data->FastShipB1FSceneID = *(src++);
    data->MountMoonSquareSceneID = *(src++);
    data->MobileTradeRoomSceneID = *(src++);
    data->MobileBattleRoomSceneID = *(src++);
//     uint8_t skip_115[49];
    Serialize_Skip(src, data->skip_115);
//     // fight counts
    data->JackFightCount = *(src++);
    data->BeverlyFightCount = *(src++);
//     // unreferenced
    data->HueyFightCount = *(src++);
    data->GavenFightCount = *(src++);
    data->BethFightCount = *(src++);
    data->JoseFightCount = *(src++);
    data->ReenaFightCount = *(src++);
    data->JoeyFightCount = *(src++);
    data->WadeFightCount = *(src++);
    data->RalphFightCount = *(src++);
    data->LizFightCount = *(src++);
    data->AnthonyFightCount = *(src++);
    data->ToddFightCount = *(src++);
    data->GinaFightCount = *(src++);
    data->IrwinFightCount = *(src++);
//     // unreferenced
    data->ArnieFightCount = *(src++);
    data->AlanFightCount = *(src++);
    data->DanaFightCount = *(src++);
    data->ChadFightCount = *(src++);
    data->DerekFightCount = *(src++);
//     // unreferenced
    data->TullyFightCount = *(src++);
    data->BrentFightCount = *(src++);
    data->TiffanyFightCount = *(src++);
    data->VanceFightCount = *(src++);
    data->WiltonFightCount = *(src++);
    data->KenjiFightCount = *(src++);
//     // unreferenced
    data->ParryFightCount = *(src++);
    data->ErinFightCount = *(src++);
//     uint8_t skip_116[100];
    Serialize_Skip(src, data->skip_116);
    src = Deserialize_ByteArray(data->eventFlags, src);
    data->curBox = *(src++);
    // uint8_t skip_117[2];
    Serialize_Skip(src, data->skip_117);
    src = Deserialize_ByteArray(data->boxNames, src);
    data->celebiEvent = *(src++);
    // uint8_t skip_118[1];
    Serialize_Skip(src, data->skip_118);
    data->bikeFlags = *(src++);
    // uint8_t skip_119[1];
    Serialize_Skip(src, data->skip_119);
    src = Deserialize_U16_LE(&data->curMapSceneScriptPointer, src);
    src = Deserialize_U16_LE(&data->curCaller, src);
    data->curMapWarpCount = *(src++);
    src = Deserialize_U16_LE(&data->curMapWarpsPointer, src);
    data->curMapCoordEventCount = *(src++);
    src = Deserialize_U16_LE(&data->curMapCoordEventsPointer, src);
    data->curMapBGEventCount = *(src++);
    src = Deserialize_U16_LE(&data->curMapBGEventsPointer, src);
    data->curMapObjectEventCount = *(src++);
    src = Deserialize_U16_LE(&data->curMapObjectEventsPointer, src);
    data->curMapSceneScriptCount = *(src++);
    src = Deserialize_U16_LE(&data->curMapSceneScriptsPointer, src);
    data->curMapCallbackCount = *(src++);
    src = Deserialize_U16_LE(&data->curMapCallbacksPointer, src);
    // uint8_t skip_120[2];
    Serialize_Skip(src, data->skip_120);
    // Sprite id of each decoration
    data->decoBed = *(src++);
    data->decoCarpet = *(src++);
    data->decoPlant = *(src++);
    data->decoPoster = *(src++);
    data->decoConsole = *(src++);
    data->decoLeftOrnament = *(src++);
    data->decoRightOrnament = *(src++);
    data->decoBigDoll = *(src++);
    // Items bought from Mom
    data->whichMomItem = *(src++);
    data->whichMomItemSet = *(src++);
    src = Deserialize_ByteArray(data->momItemTriggerBalance, src);
    src = Deserialize_U16_LE(&data->dailyResetTimer, src);
    data->dailyFlags1 = *(src++);
    data->dailyFlags2 = *(src++);
    data->swarmFlags = *(src++);
    // uint8_t skip_121[2];
    Serialize_Skip(src, data->skip_121);
    data->timerEventStartDay = *(src++);
    // uint8_t skip_122[3];
    Serialize_Skip(src, data->skip_122);
    src = Deserialize_ByteArray(data->fruitTreeFlags, src);
    // uint8_t skip_123[2];
    Serialize_Skip(src, data->skip_123);
    src = Deserialize_U16_LE(&data->luckyNumberDayTimer, src);
    // uint8_t skip_124[2];
    Serialize_Skip(src, data->skip_124);
    src = Deserialize_U16_LE(&data->specialPhoneCallID, src);
    // uint8_t skip_125[2];
    Serialize_Skip(src, data->skip_125);
    src = Deserialize_ByteArray(data->bugContestStartTime, src);
    // day, hour, min, sec
    data->unusedTwoDayTimerOn = *(src++);
    data->unusedTwoDayTimer = *(src++);
    data->unusedTwoDayTimerStartDate = *(src++);
    // uint8_t skip_126[4];
    Serialize_Skip(src, data->skip_126);
    data->mobileOrCable_LastSelection = *(src++);
    data->wdc41 = *(src++);
    src = Deserialize_ByteArray(data->wdc42, src);
    data->buenasPassword = *(src++);
    data->blueCardBalance = *(src++);
    src = Deserialize_ByteArray(data->dailyRematchFlags, src);
    src = Deserialize_ByteArray(data->dailyPhoneItemFlags, src);
    src = Deserialize_ByteArray(data->dailyPhoneTimeOfDayFlags, src);
    src = Deserialize_ByteArray(data->wKenjiBreakTimer, src);
    // Kenji
    data->yanmaMapGroup = *(src++);
    data->yanmaMapNumber = *(src++);
    src = Deserialize_ByteArray(data->playerMonSelection, src);
    data->wdc5f = *(src++);
    data->wdc60 = *(src++);
    // uint8_t skip_127[18];
    Serialize_Skip(src, data->skip_127);
    data->stepCount = *(src++);
    data->poisonStepCount = *(src++);
    // uint8_t skip_128[2];
    Serialize_Skip(src, data->skip_128);
    data->happinessStepCount = *(src++);
    // uint8_t skip_129[1];
    Serialize_Skip(src, data->skip_129);
    data->parkBallsRemaining = *(src++);
    src = Deserialize_U16_LE(&data->safariTimeRemaining, src);
    src = Deserialize_ByteArray(data->phoneList, src);
    // uint8_t skip_130[22];
    Serialize_Skip(src, data->skip_130);
    data->luckyNumberShowFlag = *(src++);
    // uint8_t skip_131[1];
    Serialize_Skip(src, data->skip_131);
    src = Deserialize_U16_LE(&data->luckyIDNumber, src);
    data->repelEffect = *(src++);
    src = Deserialize_U16_LE(&data->bikeStep, src);
    data->kurtApricornQuantity = *(src++);
    return src;
}

const uint8_t* Deserialize_PokemonData(struct PokemonData* data, const uint8_t* src) {
    data->partyCount = *(src++);
    for(int i = 0; i < PARTY_LENGTH; ++i)
        src = Deserialize_Species(&data->partySpecies[i], src);
    data->partyEnd = *(src++); // unused
    // older code doesn't check wPartyCount
    // wPartyMon1 - wPartyMon6
    //union wPartyMons
    // for n, 1, PARTY_LENGTH + 1
    // wPartyMon1 - wPartyMon6
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        src = Deserialize_PartyMon(data->partyMon + i, src);
    }
    // wPartyMon1OT - wPartyMon6OT
    //union wPartyMonOTs
    // for n, 1, PARTY_LENGTH + 1
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        src = Deserialize_ByteArray(data->partyMonOT[i], src);
    }
    // wPartyMon1Nickname - wPartyMon6Nickname
    //union wPartyMonNicknames
    // for n, 1, PARTY_LENGTH + 1
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        src = Deserialize_ByteArray(data->partyMonNickname[i], src);
    }
    // uint8_t partyMonNicknamesEnd[22];
    Serialize_Skip(src, data->partyMonNicknamesEnd);
    src = Deserialize_ByteArray(data->pokedexCaught, src);
    src = Deserialize_ByteArray(data->pokedexSeen, src);
    src = Deserialize_ByteArray(data->unownDex, src);
    data->unlockedUnowns = *(src++);
    data->firstUnownSeen = *(src++);
    // bit 7: active
    // bit 6: egg ready
    // bit 5: monsters are compatible
    // bit 0: monster 1 in day-care
    data->dayCareMan = *(src++);
    src = Deserialize_ByteArray(data->breedMon1Nickname, src);
    src = Deserialize_ByteArray(data->breedMon1OT, src);
    src = Deserialize_BoxMon(&data->breedMon1, src);
    // bit 7: active
    // bit 0: monster 2 in day-care
    data->dayCareLady = *(src++);
    data->stepsToEgg = *(src++);
    //  z: yes
    // nz: no
    data->breedMotherOrNonDitto = *(src++);
    src = Deserialize_ByteArray(data->breedMon2Nickname, src);
    src = Deserialize_ByteArray(data->breedMon2OT, src);
    src = Deserialize_BoxMon(&data->breedMon2, src);
    src = Deserialize_ByteArray(data->eggMonNickname, src);
    src = Deserialize_ByteArray(data->eggMonOT, src);
    src = Deserialize_BoxMon(&data->eggMon, src);
    data->bugContestSecondPartySpecies = *(src++);
    src = Deserialize_PartyMon(&data->contestMon, src);
    data->dunsparceMapGroup = *(src++);
    data->dunsparceMapNumber = *(src++);
    data->fishingSwarmFlag = *(src++);
    src = Deserialize_Roamer(&data->roamMon1, src);
    src = Deserialize_Roamer(&data->roamMon2, src);
    src = Deserialize_Roamer(&data->roamMon3, src);
    data->roamMons_CurMapNumber = *(src++);
    data->roamMons_CurMapGroup = *(src++);
    data->roamMons_LastMapNumber = *(src++);
    data->roamMons_LastMapGroup = *(src++);
    data->bestMagikarpLengthFeet = *(src++);
    data->bestMagikarpLengthInches = *(src++);
    src = Deserialize_ByteArray(data->magikarpRecordHoldersName, src);
    return src;
}

#define CHECK_INT(X, Y) do { if(X != Y) { fprintf(stderr, "%s does not match %s. Expected %d, got %d\n", #X, #Y, X, Y); return -1; } } while(0)
#define CHECK_IDX(X, Y, N) do { if(X[N] != Y[N]) { fprintf(stderr, "%s[%d] does not match %s[%d]. Expected %d, got %d\n", #X, N, #Y, N, X[N], Y[N]); return -1; } } while(0)
#define CHECK_STR(X, Y, N) do { if(memcmp(X, Y, N) != 0) { fprintf(stderr, "%s does not match %s.\n", #X, #Y); return -1; } } while(0)
#define CHECK_ARR(X, Y) do { if(memcmp(X, Y, sizeof(Y)) != 0) { fprintf(stderr, "%s does not match %s.\n", #X, #Y); return -1; } } while(0)

static int Check_BoxMon(const struct BoxMon* a, const struct BoxMon* b) {
    CHECK_INT(a->species, b->species);
    CHECK_INT(a->item, b->item);
    for(unsigned int i = 0; i < NUM_MOVES; ++i) {
        CHECK_IDX(a->moves, b->moves, i);
    }
    CHECK_INT(a->id, b->id);
    for(unsigned int i = 0; i < sizeof(a->exp); ++i) {
        CHECK_IDX(a->exp, b->exp, i);
    }
    for(unsigned int i = 0; i < lengthof(a->statExp); ++i) {
        CHECK_IDX(a->statExp, b->statExp, i);
    }
    CHECK_INT(a->DVs, b->DVs);
    for(unsigned int i = 0; i < sizeof(a->PP); ++i) {
        CHECK_IDX(a->PP, b->PP, i);
    }
    CHECK_INT(a->happiness, b->happiness);
    CHECK_INT(a->pokerusStatus, b->pokerusStatus);
    CHECK_INT(a->caughtGenderLocation, b->caughtGenderLocation);
    CHECK_INT(a->caughtTimeLevel, b->caughtTimeLevel);
    CHECK_INT(a->level, b->level);
    return 0;
}

static int Check_PartyMon(const struct PartyMon* a, const struct PartyMon* b) {
    if(Check_BoxMon(&a->mon, &b->mon) < 0)
        return -1;
    CHECK_INT(a->status, b->status);
    CHECK_INT(a->unused, b->unused);
    CHECK_INT(a->HP, b->HP);
    CHECK_INT(a->maxHP, b->maxHP);
    CHECK_INT(a->attack, b->attack);
    CHECK_INT(a->defense, b->defense);
    CHECK_INT(a->speed, b->speed);
    CHECK_INT(a->spclAtk, b->spclAtk);
    CHECK_INT(a->spclDef, b->spclDef);
    return 0;
}

static int Check_PokemonData(const struct PokemonData* data) {
    CHECK_INT(wram->wPartyCount, data->partyCount);
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        CHECK_IDX(wram->wPartySpecies, data->partySpecies, i);
    }
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        if(Check_PartyMon(wram->wPartyMon + i, data->partyMon + i) < 0)
            return -1;
    }
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        CHECK_STR(wram->wPartyMonOT[i], data->partyMonOT[i], sizeof(data->partyMonOT[i]));
    }
    for(int i = 0; i < PARTY_LENGTH; ++i) {
        CHECK_STR(wram->wPartyMonNickname[i], data->partyMonNickname[i], sizeof(data->partyMonNickname[i]));
    }
    CHECK_ARR(wram->wPokedexCaught, data->pokedexCaught);
    CHECK_ARR(wram->wPokedexSeen, data->pokedexSeen);
    CHECK_ARR(wram->wUnownDex, data->unownDex);
    CHECK_INT(wram->wUnlockedUnowns, data->unlockedUnowns);
    CHECK_INT(wram->wFirstUnownSeen, data->firstUnownSeen);
    CHECK_ARR(wram->wBreedMon1Nickname, data->breedMon1Nickname);
    CHECK_ARR(wram->wBreedMon1OT, data->breedMon1OT);
    if(Check_BoxMon(&wram->wBreedMon1, &data->breedMon1) < 0)
        return -1;
    
    CHECK_ARR(wram->wBreedMon2Nickname, data->breedMon2Nickname);
    CHECK_ARR(wram->wBreedMon2OT, data->breedMon2OT);
    if(Check_BoxMon(&wram->wBreedMon2, &data->breedMon2) < 0)
        return -1;
    return 0;
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

    printf("[%s - SUCCESS]", __func__);

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

    if(Check_PokemonData(&data) < 0) {
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

    printf("[%s - SUCCESS]", __func__);

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

    printf("[%s - SUCCESS]", __func__);

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

    printf("[%s - SUCCESS]", __func__);

quit:
    CloseSRAM();
    return result;
}

int Test_Serialization(void) {
    int res = 0;
    res |= Test_Serialize_PlayerData();
    res |= Test_Serialize_PokemonData();
    res |= Test_Serialize_CurMapData();
    if(res < 0)
        return FALSE;
    return TRUE;
}


