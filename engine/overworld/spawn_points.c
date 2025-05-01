#include "../../constants.h"
#include "spawn_points.h"

#include "../../data/maps/spawn_points.h"

void EnterMapSpawnPoint(void){
// loads the spawn point in wDefaultSpawnpoint
    // PUSH_HL;
    // PUSH_DE;
    // LD_A_addr(wDefaultSpawnpoint);
    // CP_A(SPAWN_N_A);
    // IF_Z goto spawn_n_a;
    if(wram->wDefaultSpawnpoint != (uint8_t)SPAWN_N_A) {
        // LD_L_A;
        // LD_H(0);
        // ADD_HL_HL;
        // ADD_HL_HL;
        // LD_DE(mSpawnPoints);
        // ADD_HL_DE;
        struct Spawn spawn = SpawnPoints[wram->wDefaultSpawnpoint];
        // LD_A_hli;
        // LD_addr_A(wMapGroup);
        wram->wMapGroup = spawn.mapGroup;
        // LD_A_hli;
        // LD_addr_A(wMapNumber);
        wram->wMapNumber = spawn.mapId;
        // LD_A_hli;
        // LD_addr_A(wXCoord);
        wram->wXCoord = (uint8_t)spawn.coord.x;
        // LD_A_hli;
        // LD_addr_A(wYCoord);
        wram->wYCoord = (uint8_t)spawn.coord.y;
    }
// spawn_n_a:
    // POP_DE;
    // POP_HL;
    // RET;
}

//  Checks if the map loaded in de is a spawn point.  Returns carry if it's a spawn point and the spawn point index.
u8_flag_s IsSpawnPoint(uint8_t d, uint8_t e){
    // LD_HL(mSpawnPoints);
    const struct Spawn* hl = SpawnPoints;
    // LD_C(0);
    uint8_t c = 0;

    while(hl[c].mapGroup != (uint8_t)SPAWN_N_A) {
    // loop:
        // LD_A_hl;
        // CP_A(SPAWN_N_A);
        // IF_Z goto nope;
        // CP_A_D;
        // IF_NZ goto next;
        // INC_HL;
        // LD_A_hld;
        // CP_A_E;
        // IF_Z goto yes;
        if(hl[c].mapGroup == d && hl[c].mapId == e) {
        // yes:
            // SCF;
            // RET;
            return u8_flag(c, true);
        }


    // next:
        // PUSH_BC;
        // LD_BC(4);  // length of a spawn table entry
        // ADD_HL_BC;
        // POP_BC;
        // INC_C;
        c++;
        // goto loop;
    }


// nope:
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}
