#include "../../constants.h"
#include "used_move_text.h"
#include "../../home/battle.h"
#include "../../home/tilemap.h"
#include "../../data/text/common.h"
#include "../../data/text/battle.h"
#include "effect_commands.h"

static void UpdateUsedMoves(move_t a);

void DisplayUsedMoveText(void){
    // LD_HL(mUsedMoveText);
    // CALL(aBattleTextbox);
    BattleTextbox(UsedMoveText);
    // JP(mWaitBGMap);
    return WaitBGMap();
}

const txt_cmd_s UsedMoveText[] = {
    text_far(v_ActorNameText)
    text_asm(UsedMoveText_Function)
};

void UsedMoveText_Function(struct TextCmdState* state) {
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto start;
    if(hram->hBattleTurn == TURN_PLAYER) {
        // LD_A_addr(wPlayerMoveStruct + MOVE_ANIM);
        // CALL(aUpdateUsedMoves);
        UpdateUsedMoves(wram->wPlayerMoveStruct.animation);
    }

// start:
    // LD_A(BATTLE_VARS_LAST_MOVE);
    // CALL(aGetBattleVarAddr);
    // LD_D_H;
    // LD_E_L;
    uint8_t* de = GetBattleVarAddr(BATTLE_VARS_LAST_MOVE);

    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_LAST_COUNTER_MOVE);

    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVar);
    // LD_addr_A(wMoveGrammar);
    wram->wMoveGrammar = GetBattleVar(BATTLE_VARS_MOVE_ANIM);

    // PUSH_HL;
    // FARCALL(aCheckUserIsCharging);
    // POP_HL;
    // IF_NZ goto grammar;
    if(!CheckUserIsCharging()) {

    // update last move
        // LD_A_addr(wMoveGrammar);
        // LD_hl_A;
        // LD_de_A;
        *hl = wram->wMoveGrammar;
        *de = wram->wMoveGrammar;
    }

// grammar:
    // CALL(aGetMoveGrammar);  // convert move id to grammar index

    // Redundant in the english translation.
    wram->wMoveGrammar = 0;


//  everything except 'CheckObedience' made redundant in localization

// check obedience
    // LD_A_addr(wAlreadyDisobeyed);
    // AND_A_A;
    // LD_HL(mUsedMove2Text);
    // RET_NZ ;
    if(wram->wAlreadyDisobeyed != 0) {
        state->hl = UsedMove2Text;
        return;
    }

// check move grammar
    // LD_A_addr(wMoveGrammar);
    // CP_A(0x3);
    // LD_HL(mUsedMove2Text);
    // RET_C ;
    if(wram->wMoveGrammar < 0x3) {
        state->hl = UsedMove2Text;
    }
    else {
        // LD_HL(mUsedMove1Text);
        state->hl = UsedMove1Text;
    }
    // RET;

}

const txt_cmd_s UsedMove1Text[] = {
    text_far(v_UsedMove1Text)
    text_asm(UsedMoveText_CheckObedience)
};

const txt_cmd_s UsedMove2Text[] = {
    text_far(v_UsedMove2Text)
    text_asm(UsedMoveText_CheckObedience)
};

static void UsedMoveText_CheckObedience_GetMoveNameText(struct TextCmdState* state);

static const txt_cmd_s UsedInsteadText[] = {
    text_far(v_UsedInsteadText)
    text_asm(UsedMoveText_CheckObedience_GetMoveNameText)
};

void UsedMoveText_CheckObedience(struct TextCmdState* state){
//  check obedience
    // LD_A_addr(wAlreadyDisobeyed);
    // AND_A_A;
    // IF_Z goto GetMoveNameText;
    if(wram->wAlreadyDisobeyed == 0)
        return UsedMoveText_CheckObedience_GetMoveNameText(state);
//  print "instead,"
    // LD_HL(mUsedMoveText_CheckObedience_UsedInsteadText);
    // RET;
    state->hl = UsedInsteadText;
}

static void UsedMoveText_CheckObedience_GetMoveNameText(struct TextCmdState* state) {
    // LD_HL(mMoveNameText);
    // RET;
    state->hl = MoveNameText;
}

const txt_cmd_s MoveNameText[] = {
    text_far(v_MoveNameText)
    text_asm(MoveNameText_Function)
};

void MoveNameText_Function(struct TextCmdState* state){
    static const struct TextCmd* endusedmovetexts[] = {
    //  entries correspond to MoveGrammar sets
        EndUsedMove1Text,
        EndUsedMove2Text,
        EndUsedMove3Text,
        EndUsedMove4Text,
        EndUsedMove5Text,
    };

//  get start address
    // LD_HL(mMoveNameText_endusedmovetexts);

//  get move id
    // LD_A_addr(wMoveGrammar);

//  2-byte pointer
    // ADD_A_A;

//  seek
    // PUSH_BC;
    // LD_B(0);
    // LD_C_A;
    // ADD_HL_BC;
    // POP_BC;

//  get pointer to usedmovetext ender
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;
    state->hl = endusedmovetexts[wram->wMoveGrammar];
}

const txt_cmd_s EndUsedMove1Text[] = {
    text_far(v_EndUsedMove1Text)
    text_end
};

const txt_cmd_s EndUsedMove2Text[] = {
    text_far(v_EndUsedMove2Text)
    text_end
};

const txt_cmd_s EndUsedMove3Text[] = {
    text_far(v_EndUsedMove3Text)
    text_end
};

const txt_cmd_s EndUsedMove4Text[] = {
    text_far(v_EndUsedMove4Text)
    text_end
};

const txt_cmd_s EndUsedMove5Text[] = {
    text_far(v_EndUsedMove5Text)
    text_end
};

void GetMoveGrammar(void){
//  store move grammar type in wMoveGrammar

    PUSH_BC;
//  wMoveGrammar contains move id
    LD_A_addr(wMoveGrammar);
    LD_C_A;  // move id
    LD_B(0);  // grammar index

//  read grammar table
    LD_HL(mMoveGrammar);

loop:
    LD_A_hli;
//  end of table?
    CP_A(-1);
    IF_Z goto end;
//  match?
    CP_A_C;
    IF_Z goto end;
//  advance grammar type at 0
    AND_A_A;
    IF_NZ goto loop;
//  next grammar type
    INC_B;
    goto loop;


end:
//  wMoveGrammar now contains move grammar
    LD_A_B;
    LD_addr_A(wMoveGrammar);

//  we're done
    POP_BC;
    RET;

// INCLUDE "data/moves/grammar.asm"

    // return UpdateUsedMoves();
}

//  append move a to wPlayerUsedMoves unless it has already been used
static void UpdateUsedMoves(move_t a){
    // PUSH_BC;
//  start of list
    // LD_HL(wPlayerUsedMoves);
    move_t* hl = wram->wPlayerUsedMoves;
//  get move id
    // LD_B_A;
//  next count
    // LD_C(NUM_MOVES);
    uint8_t c = 0;

    do {
    // loop:
    //  get move from the list
        // LD_A_hli;
        move_t move = hl[c];
    //  not used yet?
        // AND_A_A;
        // IF_Z goto add;
        if(move == NO_MOVE) {
        // add:
        //  go back to the byte we just inced from
            // DEC_HL;
        //  add the new move
            // LD_hl_B;
            hl[c] = a;
        }
    //  already used?
        // CP_A_B;
        // IF_Z goto quit;
        else if(move != a) {
            continue;
        }
        return;
    //  next byte
        // DEC_C;
        // IF_NZ goto loop;
    } while(++c != NUM_MOVES);

//  if the list is full and the move hasn't already been used
//  shift the list back one byte, deleting the first move used
//  this can occur with struggle or a new learned move
    // LD_HL(wPlayerUsedMoves + 1);
    hl = wram->wPlayerUsedMoves;
//  1 = 2
    // LD_A_hld;
    // LD_hli_A;
    hl[0] = hl[1];
//  2 = 3
    // INC_HL;
    // LD_A_hld;
    // LD_hli_A;
    hl[1] = hl[2];
//  3 = 4
    // INC_HL;
    // LD_A_hld;
    // LD_hl_A;
    hl[2] = hl[3];
//  4 = new move
    // LD_A_B;
    // LD_addr_A(wPlayerUsedMoves + 3);
    hl[3] = a;
    // goto quit;

// quit:
//  list updated
    // POP_BC;
    // RET;
}
