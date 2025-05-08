#include "../../constants.h"
#include "update_battle_huds.h"
#include "core.h"
#include "../../home/tilemap.h"

void v_UpdateBattleHUDs(void){
    // FARCALL(aDrawPlayerHUD);
    // LD_HL(wPlayerHPPal);
    // CALL(aSetHPPal);
    SetHPPal(&wram->wPlayerHPPal, DrawPlayerHUD());
    // FARCALL(aDrawEnemyHUD);
    // LD_HL(wEnemyHPPal);
    // CALL(aSetHPPal);
    SetHPPal(&wram->wEnemyHPPal, DrawEnemyHUD());
    // FARCALL(aFinishBattleAnim);
    FinishBattleAnim();
    // RET;

}
