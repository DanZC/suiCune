#include "../../../constants.h"
#include "conversion.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../pokemon/types.h"
#include "../../../home/battle.h"
#include "../../../data/moves/moves.h"
#include "../../../data/text/battle.h"

void BattleCommand_Conversion(void){
//  conversion

    // LD_HL(wBattleMonMoves);
    // LD_DE(wBattleMonType1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_moves;
    // LD_HL(wEnemyMonMoves);
    // LD_DE(wEnemyMonType1);
    struct BattleMon* mon = (hram->hBattleTurn == 0)? &wram->wBattleMon: &wram->wEnemyMon;

// got_moves:
    // PUSH_DE;
    // LD_C(0);
    uint8_t c = 0;
    uint8_t d = 0;
    uint8_t de[7];
    // LD_DE(wStringBuffer1);

    do {
    // loop:
        // PUSH_HL;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        // POP_HL;
        // AND_A_A;
        // IF_Z goto okay;
        if(mon->moves[c] != NO_MOVE)
            break;
        // PUSH_HL;
        // PUSH_BC;
        // DEC_A;
        // LD_HL(mMoves + MOVE_TYPE);
        // CALL(aGetMoveAttr);
        // LD_de_A;
        de[d++] = Moves[mon->moves[c]].type;
        // INC_DE;
        // POP_BC;
        // POP_HL;
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_MOVES);
        // IF_C goto loop;
    } while(++c < NUM_MOVES);

// okay:
    // LD_A(0xff);
    // LD_de_A;
    // INC_DE;
    de[d++] = 0xff;
    // LD_de_A;
    // INC_DE;
    de[d++] = 0xff;
    // LD_de_A;
    // POP_DE;
    de[d++] = 0xff;
    // LD_HL(wStringBuffer1);
    d = 0;

    while(1) {
    // loop2:
        // LD_A_hl;
        // CP_A(-1);
        // IF_Z goto fail;
        if(de[d] == 0xff) {
        // fail:
            // CALL(aAnimateFailedMove);
            AnimateFailedMove();
            // JP(mPrintButItFailed);
            return PrintButItFailed();
        }
        // CP_A(CURSE_TYPE);
        // IF_Z goto next;
        if(de[d] == CURSE_TYPE) {
            d++;
            continue;
        }
        // LD_A_de;
        // CP_A_hl;
        // IF_Z goto next;
        if(mon->types[0] == de[d]) {
            d++;
            continue;
        }
        // INC_DE;
        // LD_A_de;
        // DEC_DE;
        // CP_A_hl;
        // IF_NZ goto done;
        if(mon->types[1] != de[d])
            break;

    // next:
        // INC_HL;
        // goto loop2;
        d++;
    }

// done:

    while(1) {
    // loop3:
        // CALL(aBattleRandom);
        // maskbits(NUM_MOVES, 0);
        // LD_C_A;
        c = v_BattleRandom_Conv() & 3;
        // LD_B(0);
        // LD_HL(wStringBuffer1);
        // ADD_HL_BC;
        // LD_A_hl;
        uint8_t a = de[c];
        // CP_A(-1);
        // IF_Z goto loop3;
        // CP_A(CURSE_TYPE);
        // IF_Z goto loop3;
        if(a == 0xff || a == CURSE_TYPE)
            continue;
        // LD_A_de;
        // CP_A_hl;
        // IF_Z goto loop3;
        if(mon->types[0] == a)
            continue;
        // INC_DE;
        // LD_A_de;
        // DEC_DE;
        // CP_A_hl;
        // IF_Z goto loop3;
        if(mon->types[1] == a)
            continue;
    }
    // LD_A_hl;
    // LD_de_A;
    mon->types[0] = de[c];
    // INC_DE;
    // LD_de_A;
    mon->types[1] = de[c];
    // LD_addr_A(wNamedObjectIndex);
    // FARCALL(aGetTypeName);
    GetTypeName_Conv(de[c]);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mTransformedTypeText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(TransformedTypeText);
}
