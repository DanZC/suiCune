#include "../../../constants.h"
#include "selfdestruct.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../check_battle_scene.h"
#include "../../../home/delay.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../home/tilemap.h"
#include "../../../mobile/mobile_41.h"

void BattleCommand_Selfdestruct(void){
    // FARCALL(aStubbedTrainerRankings_Selfdestruct);
    StubbedTrainerRankings_Selfdestruct();
    // LD_A(BATTLEANIM_PLAYER_DAMAGE);
    // LD_addr_A(wNumHits);
    wram->wNumHits = BATTLEANIM_PLAYER_DAMAGE;
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr_Conv(BATTLE_VARS_STATUS);
    // XOR_A_A;
    // LD_hli_A;
    hl[0] = 0;
    // INC_HL;
    // LD_hli_A;
    hl[2] = 0;
    // LD_hl_A;
    hl[3] = 0;
    // LD_A(0x1);
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0x1;
    // CALL(aBattleCommand_LowerSub);
    BattleCommand_LowerSub();
    // CALL(aLoadMoveAnim);
    LoadMoveAnim();
    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_LEECH_SEED);
    bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_LEECH_SEED);
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_DESTINY_BOND);
    bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_DESTINY_BOND);
    // CALL(av_CheckBattleScene);
    // RET_NC ;
    if(CheckBattleScene_Conv())
        return;
    // FARCALL(aDrawPlayerHUD);
    DrawPlayerHUD_Conv();
    // FARCALL(aDrawEnemyHUD);
    DrawEnemyHUD_Conv();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // JP(mRefreshBattleHuds);
    return RefreshBattleHuds_Conv();
}
