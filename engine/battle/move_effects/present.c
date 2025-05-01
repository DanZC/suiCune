#include "../../../constants.h"
#include "present.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../check_battle_scene.h"
#include "../ai/scoring.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/moves/present_power.h"
#include "../../../data/text/battle.h"

void BattleCommand_Present(void){
//  present

    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // IF_Z goto colosseum_skippush;
    // PUSH_BC;
    // PUSH_DE;

// colosseum_skippush:

    // CALL(aBattleCommand_Stab);
    BattleCommand_Stab();

    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // IF_Z goto colosseum_skippop;
    // POP_DE;
    // POP_BC;

// colosseum_skippop:

    // LD_A_addr(wTypeMatchup);
    // AND_A_A;
    // JP_Z (mAnimateFailedMove);
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mAnimateFailedMove);
    if(wram->wTypeMatchup == 0 || wram->wAttackMissed)
        return AnimateFailedMove();

    // PUSH_BC;
    // CALL(aBattleRandom);
    // LD_B_A;
    uint8_t b = v_BattleRandom_Conv();
    // LD_HL(mPresentPower);
    const uint8_t* hl = PresentPower;
    // LD_C(0);
    uint8_t c = 0;

    do {
    // next:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto heal_effect;
        if(hl[c << 1] == 0xff) {
        // heal_effect:
            // POP_BC;
            // LD_A(0x3);  // heal animation
            // LD_addr_A(wBattleAnimParam);
            wram->wBattleAnimParam = 0x3;
            // CALL(aAnimateCurrentMove);
            AnimateCurrentMove();
            // CALL(aBattleCommand_SwitchTurn);
            BattleCommand_SwitchTurn();
            // LD_HL(mAICheckPlayerMaxHP);
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_Z goto got_hp_fn_pointer;
            // LD_HL(mAICheckEnemyMaxHP);
            bool (*fn)(void) = (hram->hBattleTurn == TURN_PLAYER)? AICheckPlayerMaxHP_Conv: AICheckEnemyMaxHP_Conv;

        // got_hp_fn_pointer:
            // LD_A(BANK(aAICheckPlayerMaxHP));  // aka BANK(AICheckEnemyMaxHP)
            // RST(aFarCall);
            // IF_C goto already_fully_healed;

            if(!fn()) {
                // LD_HL(mGetQuarterMaxHP);
                // CALL(aCallBattleCore);
                uint16_t hp = GetQuarterMaxHP_Conv();
                // CALL(aBattleCommand_SwitchTurn);
                BattleCommand_SwitchTurn();
                // LD_HL(mRestoreHP);
                // CALL(aCallBattleCore);
                RestoreHP_Conv(hp);
                // CALL(aBattleCommand_SwitchTurn);
                BattleCommand_SwitchTurn();
                // LD_HL(mRegainedHealthText);
                // CALL(aStdBattleTextbox);
                StdBattleTextbox(RegainedHealthText);
                // CALL(aBattleCommand_SwitchTurn);
                BattleCommand_SwitchTurn();
                // CALL(aUpdateOpponentInParty);
                UpdateOpponentInParty();
                // goto do_animation;
            }
            else {
            // already_fully_healed:
                // CALL(aBattleCommand_SwitchTurn);
                BattleCommand_SwitchTurn();
                // CALL(av_CheckBattleScene);
                // IF_NC goto do_animation;
                if(!CheckBattleScene()) {
                    // CALL(aAnimateFailedMove);
                    AnimateFailedMove();
                    // LD_HL(mPresentFailedText);
                    // CALL(aStdBattleTextbox);
                    StdBattleTextbox(PresentFailedText);
                }
            }
        // do_animation:
            // JP(mEndMoveEffect);
            return EndMoveEffect();
        }
        // CP_A_B;
        // IF_NC goto got_power;
        if(hl[c << 1] >= b)
            break;
        // INC_C;
        // INC_HL;
        // goto next;
    } while(++c, 1);


// got_power:
    // LD_A_C;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = c;
    // CALL(aAnimateCurrentMoveEitherSide);
    AnimateCurrentMoveEitherSide();
    // LD_D_hl;
    gBattleCmdState.d = hl[(c << 1) + 1];
    // POP_BC;
    // RET;
    return;
}
