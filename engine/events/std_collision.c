#include "../../constants.h"
#include "std_collision.h"
#include "../../home/map.h"
#include "../../data/collision/collision_stdscripts.h"
#include "../../util/scripting.h"

static uint16_t sJumpStdScriptBuffer;

//  Checks to see if the tile you're facing has a std script associated with it.  If so, executes the script and returns carry.
bool CheckFacingTileForStdScript(uint8_t c){
    // LD_A_C;
    // LD_DE(3);
    // LD_HL(mTileCollisionStdScripts);
    // CALL(aIsInArray);
    // IF_NC goto notintable;
    for(uint32_t i = 0; TileCollisionStdScripts[i].coll != 0xff; i++) {
        if(TileCollisionStdScripts[i].coll == c) {
            // LD_A(jumpstd_command);
            // LD_addr_A(wJumpStdScriptBuffer);
            // INC_HL;
            // LD_A_hli;
            // LD_addr_A(wJumpStdScriptBuffer + 1);
            // LD_A_hli;
            // LD_addr_A(wJumpStdScriptBuffer + 2);
            sJumpStdScriptBuffer = TileCollisionStdScripts[i].script;
            // LD_A(BANK(aScript_JumpStdFromRAM));
            // LD_HL(mScript_JumpStdFromRAM);
            // CALL(aCallScript);
            CallScript(Script_JumpStdFromRAM);
            // SCF;
            // RET;
            return true;
        }
    }

// notintable:
    // XOR_A_A;
    // RET;
    return false;
// INCLUDE "data/collision/collision_stdscripts.asm"
}

bool Script_JumpStdFromRAM(script_s* s){
    SCRIPT_BEGIN
    //sjump ['wJumpStdScriptBuffer']
    jumpstd2(sJumpStdScriptBuffer)
    SCRIPT_END
}
