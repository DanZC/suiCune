#include "../../constants.h"
#include "learn.h"
#include "mon_stats.h"
#include "../../home/copy_tilemap.h"
#include "../../home/copy.h"
#include "../../home/pokemon.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/hm_moves.h"
#include "../../home/names.h"
#include "../../home/audio.h"
#include "../../data/moves/moves.h"
#include "../../data/text/common.h"

uint8_t LearnMove(move_t toLearn){
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap();
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetNickname);
    // LD_HL(wStringBuffer1);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wMonOrItemNameBuffer, wram->wPartyMonNickname[wram->wCurPartyMon], MON_NAME_LENGTH);

    do {
    // loop:
        // LD_HL(wPartyMon1Moves);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_addr(wCurPartyMon);
        // CALL(aAddNTimes);
        move_t* moves = wram->wPartyMon[wram->wCurPartyMon].mon.moves;
        uint8_t* pp = wram->wPartyMon[wram->wCurPartyMon].mon.PP;
        // LD_D_H;
        // LD_E_L;
        // LD_B(NUM_MOVES);
        uint8_t idx = 0;
    //  Get the first empty move slot.  This routine also serves to
    //  determine whether the Pokemon learning the moves already has
    //  all four slots occupied, in which case one would need to be
    //  deleted.

        for(idx = 0; idx < NUM_MOVES; ++idx) {
        // next:
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto learn;
            if(moves[idx] == NO_MOVE)
                goto learn;
            // INC_HL;
            // DEC_B;
            // IF_NZ goto next;
        }
    //  If we're here, we enter the routine for forgetting a move
    //  to make room for the new move we're trying to learn.
        // PUSH_DE;
        // CALL(aForgetMove);
        u8_flag_s res = ForgetMove(&wram->wPartyMon[wram->wCurPartyMon]);
        // POP_DE;
        // JP_C (mLearnMove_cancel);
        if(res.flag)
            goto cancel;
        idx = res.a;

        // PUSH_HL;
        // PUSH_DE;
        // LD_addr_A(wNamedObjectIndex);

        // LD_B_A;
        // LD_A_addr(wBattleMode);
        // AND_A_A;
        // IF_Z goto not_disabled;
        // LD_A_addr(wDisabledMove);
        // CP_A_B;
        // IF_NZ goto not_disabled;
        if(wram->wBattleMode != 0 && wram->wDisabledMove == moves[idx]) {
            // XOR_A_A;
            // LD_addr_A(wDisabledMove);
            wram->wDisabledMove = NO_MOVE;
            // LD_addr_A(wPlayerDisableCount);
            wram->wPlayerDisableCount = 0;
        }

    // not_disabled:
        // CALL(aGetMoveName);
        GetMoveName(moves[idx]);
        // LD_HL(mText_1_2_and_Poof);  // 1, 2 and…
        // CALL(aPrintText);
        PrintText_Conv2(Text_1_2_and_Poof);
        // POP_DE;
        // POP_HL;

    learn:
        // LD_A_addr(wPutativeTMHMMove);
        // LD_hl_A;
        moves[idx] = toLearn;
        // LD_BC(MON_PP - MON_MOVES);
        // ADD_HL_BC;

        // PUSH_HL;
        // PUSH_DE;
        // DEC_A;
        // LD_HL(mMoves + MOVE_PP);
        // LD_BC(MOVE_LENGTH);
        // CALL(aAddNTimes);
        // LD_A(BANK(aMoves));
        // CALL(aGetFarByte);
        // POP_DE;
        // POP_HL;

        // LD_hl_A;
        pp[idx] = Moves[toLearn].pp;

        // LD_A_addr(wBattleMode);
        // AND_A_A;
        // JP_Z (mLearnMove_learned);
        // LD_A_addr(wCurPartyMon);
        // LD_B_A;
        // LD_A_addr(wCurBattleMon);
        // CP_A_B;
        // JP_NZ (mLearnMove_learned);

        // LD_A_addr(wPlayerSubStatus5);
        // BIT_A(SUBSTATUS_TRANSFORMED);
        // JP_NZ (mLearnMove_learned);

        if(wram->wBattleMode != 0 && wram->wCurPartyMon == wram->wCurBattleMon && !bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TRANSFORMED)) {
            // LD_H_D;
            // LD_L_E;
            // LD_DE(wBattleMonMoves);
            // LD_BC(NUM_MOVES);
            // CALL(aCopyBytes);
            CopyBytes(wram->wBattleMon.moves, moves, sizeof(wram->wBattleMon.moves));
            // LD_BC(wPartyMon1PP - (wPartyMon1Moves + NUM_MOVES));
            // ADD_HL_BC;
            // LD_DE(wBattleMonPP);
            // LD_BC(NUM_MOVES);
            // CALL(aCopyBytes);
            CopyBytes(wram->wBattleMon.pp, pp, sizeof(wram->wBattleMon.moves));
        }
        // JP(mLearnMove_learned);
    // learned:
        // LD_HL(mLearnedMoveText);
        // CALL(aPrintText);
        PrintText_Conv2(LearnedMoveText);
        // LD_B(1);
        // RET;
        return 1;

    cancel:
        // LD_HL(mStopLearningMoveText);
        // CALL(aPrintText);
        PrintText_Conv2(StopLearningMoveText);
        // CALL(aYesNoBox);
        // JP_C (mLearnMove_loop);
    } while(!YesNoBox_Conv());

    // LD_HL(mDidNotLearnMoveText);
    // CALL(aPrintText);
    PrintText_Conv2(DidNotLearnMoveText);
    // LD_B(0);
    // RET;
    return 0;
}

u8_flag_s ForgetMove(struct PartyMon* mon){
    // PUSH_HL;
    // LD_HL(mAskForgetMoveText);
    // CALL(aPrintText);
    PrintText_Conv2(AskForgetMoveText);
    // CALL(aYesNoBox);
    // POP_HL;
    // RET_C ;
    if(!YesNoBox_Conv())
        return u8_flag(0, true);
    // LD_BC(-NUM_MOVES);
    // ADD_HL_BC;
    // PUSH_HL;
    move_t* moves = mon->mon.moves;
    // LD_DE(wListMoves_MoveIndicesBuffer);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(wram->wListMoves_MoveIndicesBuffer, moves, NUM_MOVES * sizeof(*moves));
    // POP_HL;

    while(1) {
    // loop:
        // PUSH_HL;
        // LD_HL(mMoveAskForgetText);
        // CALL(aPrintText);
        PrintText_Conv2(MoveAskForgetText);
        // hlcoord(5, 2, wTilemap);
        // LD_B(NUM_MOVES * 2);
        // LD_C(MOVE_NAME_LENGTH);
        // CALL(aTextbox);
        Textbox_Conv2(coord(5, 2, wram->wTilemap), NUM_MOVES * 2, MOVE_NAME_LENGTH);
        // hlcoord(5 + 2, 2 + 2, wTilemap);
        // LD_A(SCREEN_WIDTH * 2);
        // LD_addr_A(wListMovesLineSpacing);
        wram->wListMovesLineSpacing = SCREEN_WIDTH * 2;
        // PREDEF(pListMoves);
        ListMoves_Conv(coord(5 + 2, 2 + 2, wram->wTilemap));
    // w2DMenuData
        // LD_A(0x4);
        // LD_addr_A(w2DMenuCursorInitY);
        wram->w2DMenuCursorInitY = 0x4;
        // LD_A(0x6);
        // LD_addr_A(w2DMenuCursorInitX);
        wram->w2DMenuCursorInitX = 0x6;
        // LD_A_addr(wNumMoves);
        // INC_A;
        // LD_addr_A(w2DMenuNumRows);
        wram->w2DMenuNumRows = wram->wNumMoves + 1;
        // LD_A(0x1);
        // LD_addr_A(w2DMenuNumCols);
        wram->w2DMenuNumCols = 0x1;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 0x1;
        // LD_addr_A(wMenuCursorX);
        wram->wMenuCursorX = 0x1;
        // LD_A(0x3);
        // LD_addr_A(wMenuJoypadFilter);
        wram->wMenuJoypadFilter = 0x3;
        // LD_A(0x20);
        // LD_addr_A(w2DMenuFlags1);
        wram->w2DMenuFlags1 = 0x20;
        // XOR_A_A;
        // LD_addr_A(w2DMenuFlags2);
        wram->w2DMenuFlags2 = 0x0;
        // LD_A(0x20);
        // LD_addr_A(w2DMenuCursorOffsets);
        wram->w2DMenuCursorOffsets = 0x0;
        // CALL(aStaticMenuJoypad);
        uint8_t res = StaticMenuJoypad_Conv();
        // PUSH_AF;
        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap();
        // POP_AF;
        // POP_HL;
        // BIT_A(1);
        // IF_NZ goto cancel;
        if(bit_test(res, 1))
            return u8_flag(0, true);
        // PUSH_HL;
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        const uint8_t c = wram->wMenuCursorY - 1;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        // PUSH_AF;
        // PUSH_BC;
        // CALL(aIsHMMove);
        bool is_hm = IsHMMove(moves[c]);
        // POP_BC;
        // POP_DE;
        // LD_A_D;
        // IF_C goto hmmove;
        if(!is_hm) {
            // POP_HL;
            // ADD_HL_BC;
            // AND_A_A;
            // RET;
            return u8_flag(c, false);
        }

    // hmmove:
        // LD_HL(mMoveCantForgetHMText);
        // CALL(aPrintText);
        PrintText_Conv2(MoveCantForgetHMText);
        // POP_HL;
        // goto loop;
    }

// cancel:
    // SCF;
    // RET;
}

const txt_cmd_s LearnedMoveText[] = {
    text_far(v_LearnedMoveText)
    text_end
};

const txt_cmd_s MoveAskForgetText[] = {
    text_far(v_MoveAskForgetText)
    text_end
};

const txt_cmd_s StopLearningMoveText[] = {
    text_far(v_StopLearningMoveText)
    text_end
};

const txt_cmd_s DidNotLearnMoveText[] = {
    text_far(v_DidNotLearnMoveText)
    text_end
};

const txt_cmd_s AskForgetMoveText[] = {
    text_far(v_AskForgetMoveText)
    text_end
};

static void Text_1_2_and_Poof_Function(struct TextCmdState* state);
const txt_cmd_s Text_1_2_and_Poof[] = {
    text_far(v_Text_MoveForgetCount)  // 1, 2 and…
    text_asm(Text_1_2_and_Poof_Function)
};

static void Text_1_2_and_Poof_Function(struct TextCmdState* state) {
    static const txt_cmd_s MoveForgotText[] = {
        text_far(v_MoveForgotText)
        text_end
    };
    // PUSH_DE;
    // LD_DE(SFX_SWITCH_POKEMON);
    // CALL(aPlaySFX);
    PlaySFX(SFX_SWITCH_POKEMON);
    // POP_DE;
    // LD_HL(mText_1_2_and_Poof_MoveForgotText);
    state->hl = MoveForgotText;
    // RET;
}

const txt_cmd_s MoveCantForgetHMText[] = {
    text_far(v_MoveCantForgetHMText)
    text_end
};
