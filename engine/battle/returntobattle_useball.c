#include "../../constants.h"
#include "returntobattle_useball.h"
#include "core.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/menu.h"

void v_ReturnToBattle_UseBall(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);
    // IF_Z goto gettutorialbackpic;
    if(wram->wBattleType == BATTLETYPE_TUTORIAL) {
    // gettutorialbackpic:
        // FARCALL(aGetTrainerBackpic);
        GetTrainerBackpic();
    }
    else {
        // FARCALL(aGetBattleMonBackpic);
        GetBattleMonBackpic();
        // goto continue_;
    }

// continue_:
    // FARCALL(aGetEnemyMonFrontpic);
    GetEnemyMonFrontpic();
    // FARCALL(av_LoadBattleFontsHPBar);
    v_LoadBattleFontsHPBar();
    // CALL(aGetMemSGBLayout);
    GetMemSGBLayout_Conv();
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // JP(mSetPalettes);
    SetPalettes_Conv();

}
