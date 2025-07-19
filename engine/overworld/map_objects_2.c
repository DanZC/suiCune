#include "../../constants.h"
#include "map_objects_2.h"
#include "../../home/copy.h"
#include "../../home/map_objects.h"
#include "../../home/flag.h"

static uint8_t CheckObjectFlag(struct MapObject* bc);
static uint8_t GetObjectTimeMask(struct MapObject* bc);

void LoadObjectMasks(void){
    // LD_HL(wObjectMasks);
    // XOR_A_A;
    // LD_BC(NUM_OBJECTS);
    // CALL(aByteFill);
    ByteFill(gPlayer.objectMasks, NUM_OBJECTS, 0);
    // NOP;
    // LD_BC(wMapObjects);
    struct MapObject* bc = &gPlayer.playerObject;
    // LD_DE(wObjectMasks);
    uint8_t* de = gPlayer.objectMasks;
    // XOR_A_A;

    for(uint32_t a = 0; a < NUM_OBJECTS; ++a) {
    // loop:
        // PUSH_AF;
        // PUSH_BC;
        // PUSH_DE;
        // CALL(aGetObjectTimeMask);
        uint8_t a2 = GetObjectTimeMask(bc + a);
        // IF_C goto next;
        if(a2 != 0xff) {
            // CALL(aCheckObjectFlag);
            a2 = CheckObjectFlag(bc + a);
        }

    // next:
        // POP_DE;
        // LD_de_A;
        de[a] = a2;
        // INC_DE;
        // POP_BC;
        // LD_HL(MAPOBJECT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        // POP_AF;
        // INC_A;
        // CP_A(NUM_OBJECTS);
        // IF_NZ goto loop;
    }
    // RET;
}

static uint8_t CheckObjectFlag(struct MapObject* bc){
    // LD_HL(MAPOBJECT_SPRITE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto masked;
    if(bc->sprite == 0)
        return 0xff;
    // LD_HL(MAPOBJECT_EVENT_FLAG);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hl;
    // LD_D_A;
    // CP_A(-1);
    // IF_NZ goto check;
    if(HIGH(bc->objectEventFlag) != 0xff) {
    // check:
        // LD_B(CHECK_FLAG);
        // CALL(aEventFlagAction);
        // LD_A_C;
        // AND_A_A;
        // IF_NZ goto masked;
        if(EventFlagAction(bc->objectEventFlag, CHECK_FLAG) != 0)
            return 0xff;
        return 0;
    }
    // LD_A_E;
    // CP_A(-1);
    // IF_Z goto unmasked;
    else if(LOW(bc->objectEventFlag) == 0xff)
        return 0;
    // goto masked;
    else
        return 0xff;

// unmasked:
    // XOR_A_A;
    // RET;
    return 0;


// masked:
    // LD_A(-1);
    // SCF;
    // RET;
}

static uint8_t GetObjectTimeMask(struct MapObject* bc){
    // CALL(aCheckObjectTime);
    // LD_A(-1);
    // RET_C ;
    if(CheckObjectTime(bc))
        return 0xff;
    // XOR_A_A;
    // RET;
    return 0;
}
