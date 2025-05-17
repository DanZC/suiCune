#include "../constants.h"
#include "trainers.h"
#include "map_objects.h"
#include "flag.h"
#include "map.h"
#include "copy.h"
#include "gfx.h"
#include "text.h"
#include "tilemap.h"
#include "joypad.h"

const struct TextCmd* gSeenTextPointer = NULL;
const struct TextCmd* gWinTextPointer = NULL;
const struct TextCmd* gLossTextPointer = NULL;
Script_fn_t gScriptAfterPointer = NULL;

bool CheckTrainerBattle(void){
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    uint8_t oldBank = hram.hROMBank;

    // CALL(aSwitchToMapScriptsBank);
    SwitchToMapScriptsBank();
    // CALL(av_CheckTrainerBattle);
    bool b = v_CheckTrainerBattle();

    // POP_BC;
    // LD_A_B;
    // RST(aBankswitch);
    Bankswitch(oldBank);
    // RET;
    return b;
}

//  Check if any trainer on the map sees the player and wants to battle.
bool v_CheckTrainerBattle(void){
//  Skip the player object.
    // LD_A(1);
    // LD_DE(wMap1Object);
    uint8_t a = 1;


    // loop:
    do {
        struct MapObject* de = wram->wMapObject + (a - 1);
    //  Start a battle if the object:
        // PUSH_AF;
        // PUSH_DE;

    //  Has a sprite
        // LD_HL(MAPOBJECT_SPRITE);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(de->sprite == 0)
            continue;

    //  Is a trainer
        // LD_HL(MAPOBJECT_COLOR);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A(0xf);
        // CP_A(OBJECTTYPE_TRAINER);
        // IF_NZ goto next;
        if((de->objectColor & 0xf) != OBJECTTYPE_TRAINER)
            continue;

    //  Is visible on the map
        // LD_HL(MAPOBJECT_OBJECT_STRUCT_ID);
        // ADD_HL_DE;
        // LD_A_hl;
        // CP_A(-1);
        // IF_Z goto next;
        if(de->structId == 0xff)
            continue;

    //  Is facing the player...
        // CALL(aGetObjectStruct);
        struct Object* obj = GetObjectStruct(de->structId);
        // CALL(aFacingPlayerDistance_bc);
        struct FacingDist fdist = FacingPlayerDistance_bc(obj);
        // IF_NC goto next;
        if(!fdist.facing)
            continue;

    //  ...within their sight range
        // LD_HL(MAPOBJECT_RANGE);
        // ADD_HL_DE;
        // LD_A_hl;
        // CP_A_B;
        // IF_C goto next;
        if(de->objectRange < fdist.dist)
            continue;

    //  And hasn't already been beaten
        // PUSH_BC;
        // PUSH_DE;
        // LD_HL(MAPOBJECT_SCRIPT_POINTER);
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_E_hl;
        // INC_HL;
        // LD_D_hl;
        // LD_B(CHECK_FLAG);
        // CALL(aEventFlagAction);
        uint16_t eventFlag;
        if(de->objectScript <= NUM_OBJECTS)
            eventFlag = gCurMapObjectEventsPointer[de->objectScript].trainer->event_flag;
        else if(convertedFunc[(GetMapScriptsBank() << 14) | (de->objectScript & 0x3fff)]){
            eventFlag = ((struct TrainerObj*)convertedFunc[(GetMapScriptsBank() << 14) | (de->objectScript & 0x3fff)])->event_flag;
        }
        else {
            eventFlag = *(uint16_t*)AbsGBROMToRAMAddr((GetMapScriptsBank() << 14) | (de->objectScript & 0x3fff));
        }
        // LD_A_C;
        // POP_DE;
        // POP_BC;
        // AND_A_A;
        // IF_Z goto startbattle;
        if(!EventFlagAction(eventFlag, CHECK_FLAG)) {
        // startbattle:
            // POP_DE;
            // POP_AF;
            // LDH_addr_A(hLastTalked);
            hram.hLastTalked = a;
            // LD_A_B;
            // LD_addr_A(wSeenTrainerDistance);
            wram->wSeenTrainerDistance = fdist.dist;
            // LD_A_C;
            // LD_addr_A(wSeenTrainerDirection);
            wram->wSeenTrainerDirection = fdist.dir;
            // JR(mLoadTrainer_continue);
            return LoadTrainer_continue();
        }


    // next:
        // POP_DE;
        // LD_HL(MAPOBJECT_LENGTH);
        // ADD_HL_DE;
        // LD_D_H;
        // LD_E_L;

        // POP_AF;
        // INC_A;
        // CP_A(NUM_OBJECTS);
        // IF_NZ goto loop;
    } while(++a != NUM_OBJECTS);
    // XOR_A_A;
    // RET;
    return false;
}

bool TalkToTrainer(void){
    // LD_A(1);
    // LD_addr_A(wSeenTrainerDistance);
    wram->wSeenTrainerDistance = 1;
    // LD_A(-1);
    // LD_addr_A(wSeenTrainerDirection);
    wram->wSeenTrainerDirection = 0xff;

    return LoadTrainer_continue();
}

bool LoadTrainer_continue(void){
    // CALL(aGetMapScriptsBank);
    // LD_addr_A(wSeenTrainerBank);
    wram->wSeenTrainerBank = GetMapScriptsBank();

    // LDH_A_addr(hLastTalked);
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject(hram.hLastTalked);

    // LD_HL(MAPOBJECT_SCRIPT_POINTER);
    // ADD_HL_BC;
    if(bc->objectScript <= NUM_OBJECTS) {
        const struct TrainerObj* hl = gCurMapObjectEventsPointer[bc->objectScript].trainer;
        wram->wTempTrainerEventFlag = hl->event_flag;
        wram->wTempTrainerClass = hl->tclass;
        wram->wTempTrainerID = hl->tid;
        gSeenTextPointer = hl->seenText;
        gWinTextPointer = hl->winText;
        gLossTextPointer = hl->lossText;
        gScriptAfterPointer = hl->script;
    }
    else {
        if(convertedFunc[(GetMapScriptsBank() << 14) | (bc->objectScript & 0x3fff)]) {
            const struct TrainerObj* hl = (const struct TrainerObj*)convertedFunc[(GetMapScriptsBank() << 14) | (bc->objectScript & 0x3fff)];
            wram->wTempTrainerEventFlag = hl->event_flag;
            wram->wTempTrainerClass = hl->tclass;
            wram->wTempTrainerID = hl->tid;
            gSeenTextPointer = hl->seenText;
            gWinTextPointer = hl->winText;
            gLossTextPointer = hl->lossText;
            gScriptAfterPointer = hl->script;
        }
        else {
            // LD_A_addr(wSeenTrainerBank);
            // CALL(aGetFarWord);
            // LD_DE(wTempTrainer);
            // LD_BC(wTempTrainerEnd - wTempTrainer);
            // LD_A_addr(wSeenTrainerBank);
            // CALL(aFarCopyBytes);
            gSeenTextPointer = NULL;
            gWinTextPointer = NULL;
            gLossTextPointer = NULL;
            gScriptAfterPointer = NULL;
            CopyBytes(&wram->wTempTrainerEventFlag, AbsGBToRAMAddr((wram->wSeenTrainerBank << 14) | bc->objectScript), (&wram->wRunningTrainerBattleScript - (uint8_t*)&wram->wTempTrainerEventFlag));
        }
    }
    // XOR_A_A;
    // LD_addr_A(wRunningTrainerBattleScript);
    wram->wRunningTrainerBattleScript = 0;
    // SCF;
    // RET;
    return true;
}

struct FacingDist FacingPlayerDistance_bc(struct Object* bc){
    // PUSH_DE;
    // CALL(aFacingPlayerDistance);
    // LD_B_D;
    // LD_C_E;
    // POP_DE;
    // RET;
    return FacingPlayerDistance(bc);
}

//  Return carry if the sprite at bc is facing the player,
//  its distance in d, and its direction in e.
struct FacingDist FacingPlayerDistance(struct Object* bc){
    // LD_HL(OBJECT_NEXT_MAP_X);  // x
    // ADD_HL_BC;
    // LD_D_hl;
    uint8_t d = bc->nextMapX;

    // LD_HL(OBJECT_NEXT_MAP_Y);  // y
    // ADD_HL_BC;
    // LD_E_hl;
    uint8_t e = bc->nextMapY;

    // LD_A_addr(wPlayerStandingMapX);
    // CP_A_D;
    // IF_Z goto CheckY;
    if(wram->wPlayerStruct.nextMapX == d) {
    // CheckY:
        // LD_A_addr(wPlayerStandingMapY);
        // SUB_A_E;
        // IF_Z goto NotFacing;
        if(wram->wPlayerStruct.nextMapY == e)
            return (struct FacingDist){.facing = false, .dist = d, .dir = e};
        // IF_NC goto Above;
        else if(wram->wPlayerStruct.nextMapY < e) {
        //  Below
            // CPL;
            // INC_A;
            // LD_D_A;
            // LD_E(OW_UP);
            d = ((wram->wPlayerStruct.nextMapY - e) ^ 0xff) + 1;
            e = OW_UP;
        }
        else {


        // Above:
            // LD_D_A;
            d = wram->wPlayerStruct.nextMapY - e;
            // LD_E(OW_DOWN);
            e = OW_DOWN;
        }
    }

    // LD_A_addr(wPlayerStandingMapY);
    // CP_A_E;
    // IF_Z goto CheckX;
    else if(wram->wPlayerStruct.nextMapY == e) {
    // CheckX:
        // LD_A_addr(wPlayerStandingMapX);
        // SUB_A_D;
        // IF_Z goto NotFacing;
        if(wram->wPlayerStruct.nextMapX == d) 
            return (struct FacingDist){.facing = false, .dist = d, .dir = e};
        // IF_NC goto Left;
        if(wram->wPlayerStruct.nextMapX < d) { 
            //  Right
            // CPL;
            // INC_A;
            // LD_D_A;
            // LD_E(OW_LEFT);
            d = ((wram->wPlayerStruct.nextMapX - d) ^ 0xff) + 1;
            e = OW_LEFT;
        }
        else {

        // Left:
            // LD_D_A;
            // LD_E(OW_RIGHT);
            d = wram->wPlayerStruct.nextMapX - d;
            e = OW_RIGHT;
        }
    }
    else {
        // AND_A_A;
        // RET;
        return (struct FacingDist){.facing = false, .dist = d, .dir = e};
    }


// CheckFacing:
    // CALL(aGetSpriteDirection);
    // CP_A_E;
    // IF_NZ goto NotFacing;
    if(GetSpriteDirection(bc) != e)
        return (struct FacingDist){.facing = false, .dist = d, .dir = e};
    else
        return (struct FacingDist){.facing = true, .dist = d, .dir = e};
    // SCF;
    // RET;


// NotFacing:
    // AND_A_A;
    // RET;
}

//  //  unreferenced
bool CheckTrainerFlag(struct Object* bc){
    // PUSH_BC;
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aGetMapObject);
    struct MapObject* mbc = GetMapObject(bc->mapObjectIndex);
    // LD_HL(MAPOBJECT_SCRIPT_POINTER);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aGetMapScriptsBank);
    // CALL(aGetFarWord);
    // LD_D_H;
    // LD_E_L;
    // PUSH_DE;
    // LD_B(CHECK_FLAG);
    // CALL(aEventFlagAction);
    uint8_t c = EventFlagAction(mbc->objectScript, CHECK_FLAG);
    // POP_DE;
    // LD_A_C;
    // AND_A_A;
    // POP_BC;
    // RET;
    return c != 0;
}

void PrintWinLossText(void){
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_CANLOSE);
// code was probably dummied out here
    // goto canlose;

//  unused
    // LD_HL(wWinTextPointer);
    // goto ok;


// canlose:
    // LD_A_addr(wBattleResult);
    // LD_HL(wWinTextPointer);
    // AND_A(0xf);  // WIN?
    // IF_Z goto ok;
    // LD_HL(wLossTextPointer);
    const struct TextCmd* textPtr = ((wram->wBattleResult & 0xf) == 0)? gWinTextPointer: gLossTextPointer;


// ok:
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aGetMapScriptsBank);
    // CALL(aFarPrintText);
    PrintText(textPtr);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor();
    // RET;
}
