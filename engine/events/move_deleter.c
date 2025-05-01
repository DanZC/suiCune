#include "../../constants.h"
#include "move_deleter.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/map.h"
#include "../../home/names.h"
#include "../../home/audio.h"
#include "../pokemon/party_menu.h"
#include "../pokemon/mon_menu.h"
#include "../../data/text/common.h"

static void MoveDeletion_DeleteMove(uint8_t index) {
    // LD_A_B;
    // PUSH_BC;
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wPartyMon1Moves);
    // ADD_HL_BC;
    // LD_A_addr(wCurPartyMon);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    move_t* hl = wram->wPartyMon[wram->wCurPartyMon].mon.moves + index;
    // POP_BC;
    // PUSH_BC;
    // INC_B;
    uint8_t b = index + 1;

    while(b != NUM_MOVES) {
    // loop:
        // LD_A_B;
        // CP_A(NUM_MOVES + 1);
        // IF_Z goto okay;
        // INC_HL;
        // LD_A_hld;
        // LD_hl_A;
        hl[0] = hl[1];
        // INC_HL;
        hl++;
        // INC_B;
        b++;
        // goto loop;
    }


// okay:
    // XOR_A_A;
    // LD_hl_A;
    *hl = NO_MOVE;
    // POP_BC;

    // LD_A_B;
    // PUSH_BC;
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wPartyMon1PP);
    // ADD_HL_BC;
    // LD_A_addr(wCurPartyMon);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    uint8_t* pp = wram->wPartyMon[wram->wCurPartyMon].mon.PP + index;
    // POP_BC;
    // INC_B;
    b = index + 1;

    while(b != NUM_MOVES) {
    // loop2:
        // LD_A_B;
        // CP_A(NUM_MOVES + 1);
        // IF_Z goto done;
        // INC_HL;
        // LD_A_hld;
        // LD_hl_A;
        pp[0] = pp[1];
        // INC_HL;
        pp++;
        // INC_B;
        b++;
        // goto loop2;
    }


// done:
    // XOR_A_A;
    // LD_hl_A;
    *pp = 0;
    // RET;
}

void MoveDeletion(void){
    static const txt_cmd_s MoveKnowsOneText[] = {
        text_far(v_MoveKnowsOneText)
        text_end
    };
    static const txt_cmd_s AskDeleteMoveText[] = {
        text_far(v_AskDeleteMoveText)
        text_end
    };
    static const txt_cmd_s DeleterForgotMoveText[] = {
        text_far(v_DeleterForgotMoveText)
        text_end
    };
    static const txt_cmd_s MailEggText[] = {
        text_far(v_DeleterEggText)
        text_end
    };
    static const txt_cmd_s DeleterNoComeAgainText[] = {
        text_far(v_DeleterNoComeAgainText)
        text_end
    };
    static const txt_cmd_s DeleterAskWhichMoveText[] = {
        text_far(v_DeleterAskWhichMoveText)
        text_end
    };
    static const txt_cmd_s DeleterIntroText[] = {
        text_far(v_DeleterIntroText)
        text_end
    };
    static const txt_cmd_s DeleterAskWhichMonText[] = {
        text_far(v_DeleterAskWhichMonText)
        text_end
    };
    // LD_HL(mMoveDeletion_DeleterIntroText);
    // CALL(aPrintText);
    PrintText(DeleterIntroText);
    // CALL(aYesNoBox);
    // IF_C goto declined;
    if(YesNoBox()) {
        // LD_HL(mMoveDeletion_DeleterAskWhichMonText);
        // CALL(aPrintText);
        PrintText(DeleterAskWhichMonText);
        // FARCALL(aSelectMonFromParty);
        u8_flag_s res = SelectMonFromParty();
        // IF_C goto declined;
        if(res.flag)
            goto declined;
        // LD_A_addr(wCurPartySpecies);
        // CP_A(EGG);
        // IF_Z goto egg;
        if(wram->wCurPartySpecies == EGG) {
        // egg:
            // LD_HL(mMoveDeletion_MailEggText);
            // CALL(aPrintText);
            // RET;
            return PrintText(MailEggText);
        }
        // LD_A_addr(wCurPartyMon);
        // LD_HL(wPartyMon1Moves + 1);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto onlyonemove;
        if(wram->wPartyMon[wram->wCurPartyMon].mon.moves[1] == NO_MOVE) {
        // onlyonemove:
            // LD_HL(mMoveDeletion_MoveKnowsOneText);
            // CALL(aPrintText);
            // RET;
            return PrintText(MoveKnowsOneText);
        }
        // LD_HL(mMoveDeletion_DeleterAskWhichMoveText);
        // CALL(aPrintText);
        PrintText(DeleterAskWhichMoveText);
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader();
        // FARCALL(aChooseMoveToDelete);
        u8_flag_s res2 = ChooseMoveToDelete();
        // PUSH_AF;
        // CALL(aReturnToMapWithSpeechTextbox);
        ReturnToMapWithSpeechTextbox();
        // POP_AF;
        // IF_C goto declined;
        if(res2.flag)
            goto declined;
        // LD_A_addr(wMenuCursorY);
        // PUSH_AF;
        // LD_A_addr(wCurSpecies);
        move_t move = wram->wPartyMon[wram->wCurPartyMon].mon.moves[res2.a - 1];
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetMoveName);
        GetMoveName(move);
        // LD_HL(mMoveDeletion_AskDeleteMoveText);
        // CALL(aPrintText);
        PrintText(AskDeleteMoveText);
        // CALL(aYesNoBox);
        // POP_BC;
        // IF_C goto declined;
        if(YesNoBox()) {
            // CALL(aMoveDeletion_DeleteMove);
            MoveDeletion_DeleteMove(res2.a - 1);
            // CALL(aWaitSFX);
            WaitSFX();
            // LD_DE(SFX_MOVE_DELETED);
            // CALL(aPlaySFX);
            PlaySFX(SFX_MOVE_DELETED);
            // CALL(aWaitSFX);
            WaitSFX();
            // LD_HL(mMoveDeletion_DeleterForgotMoveText);
            // CALL(aPrintText);
            PrintText(DeleterForgotMoveText);
            // RET;
            return;
        }
    }

declined:
    // LD_HL(mMoveDeletion_DeleterNoComeAgainText);
    // CALL(aPrintText);
    PrintText(DeleterNoComeAgainText);
    // RET;
}
