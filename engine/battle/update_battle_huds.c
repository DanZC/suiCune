#include "../../constants.h"
#include "update_battle_huds.h"
#include "core.h"
#include "../../home/tilemap.h"

void v_UpdateBattleHUDs(void){
    // FARCALL(aDrawPlayerHUD);
    // LD_HL(wPlayerHPPal);
    // CALL(aSetHPPal);
    SetHPPal(&wram->wPlayerHPPal, DrawPlayerHUD_Conv());
    // FARCALL(aDrawEnemyHUD);
    // LD_HL(wEnemyHPPal);
    // CALL(aSetHPPal);
    SetHPPal(&wram->wEnemyHPPal, DrawEnemyHUD_Conv());
    // FARCALL(aFinishBattleAnim);
    FinishBattleAnim();
    // RET;

}
