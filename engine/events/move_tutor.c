#include "../../constants.h"
#include "move_tutor.h"
#include "../../home/map.h"
#include "../../home/tilemap.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/copy_name.h"
#include "../../home/names.h"
#include "../../home/menu.h"
#include "../../home/audio.h"
#include "../../home/pokemon.h"
#include "../items/tmhm.h"
#include "../items/tmhm2.h"
#include "../pokemon/knows_move.h"
#include "../pokemon/learn.h"

static move_t MoveTutor_GetMoveTutorMove(void){
    // LD_A_addr(wScriptVar);
    switch(wram->wScriptVar) {
        case MOVETUTOR_FLAMETHROWER: return MT01_MOVE;
        case MOVETUTOR_THUNDERBOLT:  return MT02_MOVE;
        default:
        case MOVETUTOR_ICE_BEAM:     return MT03_MOVE;
    }
    // CP_A(MOVETUTOR_FLAMETHROWER);
    // IF_Z goto flamethrower;
    // CP_A(MOVETUTOR_THUNDERBOLT);
    // IF_Z goto thunderbolt;
// MOVETUTOR_ICE_BEAM
    // LD_A(MT03_MOVE);  // ICE_BEAM
    // RET;

// flamethrower:
    // LD_A(MT01_MOVE);  // FLAMETHROWER
    // RET;

// thunderbolt:
    // LD_A(MT02_MOVE);  // THUNDERBOLT
    // RET;
}

void MoveTutor(void){
    // CALL(aFadeToMenu);
    FadeToMenu();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearScreen);
    ClearScreen();
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_B(SCGB_PACKPALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PACKPALS);
    // XOR_A_A;
    // LD_addr_A(wItemAttributeValue);
    wram->wItemAttributeValue = 0x0;
    // CALL(aMoveTutor_GetMoveTutorMove);
    // LD_addr_A(wNamedObjectIndex);
    // LD_addr_A(wPutativeTMHMMove);
    wram->wPutativeTMHMMove = MoveTutor_GetMoveTutorMove();
    // CALL(aGetMoveName);
    // CALL(aCopyName1);
    CopyName1(GetMoveName(wram->wPutativeTMHMMove));
    // FARCALL(aChooseMonToLearnTMHM);
    // IF_C goto cancel;
    u8_flag_s res = ChooseMonToLearnTMHM();
    if(res.flag) {
        wram->wScriptVar = -1;
    }
    else {
        // goto enter_loop;

        while(!CheckCanLearnMoveTutorMove(res.a, wram->wPutativeTMHMMove)) {
        // loop:
            // FARCALL(aChooseMonToLearnTMHM_NoRefresh);
            u8_flag_s res2 = ChooseMonToLearnTMHM_NoRefresh();
            // IF_C goto cancel;
            if(res2.flag) {
            // cancel:
                // LD_A(-1);
                // LD_addr_A(wScriptVar);
                wram->wScriptVar = -1;
                goto quit;
            }
        }

    // enter_loop:
        // CALL(aCheckCanLearnMoveTutorMove);
        // IF_NC goto loop;
        // XOR_A_A;  // FALSE
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = FALSE;
        // goto quit;
    }

quit:
    // CALL(aCloseSubmenu);
    CloseSubmenu();
    // RET;
}

static const struct MenuHeader CheckCanLearnMoveTutorMove_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = NULL,
    .defaultOption = 1,
};

bool CheckCanLearnMoveTutorMove(uint8_t curMon, move_t move){
    // LD_HL(mCheckCanLearnMoveTutorMove_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&CheckCanLearnMoveTutorMove_MenuHeader);

    // PREDEF(pCanLearnTMHMMove);
    uint8_t canLearn = CanLearnTMHMMove_Conv(wram->wCurPartySpecies, move);

    // PUSH_BC;
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetNickname);
    GetNickname(wram->wPartyMonNickname[0], curMon);
    // POP_BC;

    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto can_learn;
    if(canLearn) {
    // can_learn:
        // CALLFAR(aKnowsMove);
        // IF_C goto didnt_learn;
        // PREDEF(pLearnMove);
        // LD_A_B;
        // AND_A_A;
        // IF_Z goto didnt_learn;
        if(!KnowsMove_Conv(&wram->wPartyMon[curMon].mon, move) && LearnMove(move)) {
            // LD_C(HAPPINESS_LEARNMOVE);
            // CALLFAR(aChangeHappiness);
            // goto learned;
        // learned:
            // CALL(aExitMenu);
            ExitMenu();
            // SCF;
            // RET;
            return true;
        }
    }
    else {
        // PUSH_DE;
        // LD_DE(SFX_WRONG);
        // CALL(aPlaySFX);
        PlaySFX(SFX_WRONG);
        // POP_DE;
        // LD_A(BANK(aTMHMNotCompatibleText));
        // LD_HL(mTMHMNotCompatibleText);
        // CALL(aFarPrintText);
        PrintText(TMHMNotCompatibleText);
        // goto didnt_learn;
    }

// didnt_learn:
    // CALL(aExitMenu);
    ExitMenu();
    // AND_A_A;
    // RET;
    return false;
}
