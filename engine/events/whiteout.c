#include "../../constants.h"
#include "whiteout.h"
#include "std_scripts.h"
#include "../overworld/spawn_points.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/clear_sprites.h"
#include "../../home/fade.h"
#include "../../util/scripting.h"
#include "../../mobile/mobile_41.h"
#include "../../data/text/common.h"
#include "misc_scripts.h"

bool Script_BattleWhiteout(script_s* s){
    SCRIPT_BEGIN
    BattleBGMap();
    sjump(Script_Whiteout)
    SCRIPT_END
}

bool OverworldWhiteoutScript(script_s* s){
    SCRIPT_BEGIN
    refreshscreen
    OverworldBGMap();
    sjump(Script_Whiteout)
    SCRIPT_END
}

bool Script_Whiteout(script_s* s){
    static const txt_cmd_s WhitedOutText[] = {
        text_far(v_WhitedOutText)
        text_end
    };
    SCRIPT_BEGIN
    writetext(WhitedOutText)
    waitbutton
    special(FadeOutPalettes)
    pause(40)
    special(HealParty)
    checkflag(ENGINE_BUG_CONTEST_TIMER)
    iftrue(bug_contest)
    HalveMoney();
    GetWhiteoutSpawn();
    scall(Script_AbortBugContest)
    special(WarpToSpawnPoint)
    newloadmap(MAPSETUP_WARP)
    s_endall


bug_contest:
    jumpstd(BugContestResultsWarpScript)
    SCRIPT_END
}

void OverworldBGMap(void){
    // CALL(aClearPalettes);
    ClearPalettes();
    // CALL(aClearScreen);
    ClearScreen();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // CALL(aHideSprites);
    HideSprites();
    // CALL(aRotateThreePalettesLeft);
    RotateThreePalettesLeft();
    // RET;
}

void BattleBGMap(void){
    // LD_B(SCGB_BATTLE_GRAYSCALE);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_BATTLE_GRAYSCALE);
    // CALL(aSetPalettes);
    SetPalettes();
    // RET;
}

void HalveMoney(void){
    // FARCALL(aStubbedTrainerRankings_WhiteOuts);
    StubbedTrainerRankings_WhiteOuts();

//  Halve the player's money.
    // LD_HL(wMoney);
    uint32_t money = (gPlayer.money[0] << 16) | (gPlayer.money[1] << 8) | (gPlayer.money[2]);
    // LD_A_hl;
    // SRL_A;
    // LD_hli_A;
    money /= 2;
    gPlayer.money[0] = (money >> 16) & 0xff;
    // LD_A_hl;
    // RRA;
    // LD_hli_A;
    gPlayer.money[1] = (money >> 8) & 0xff;
    // LD_A_hl;
    // RRA;
    // LD_hl_A;
    gPlayer.money[2] = money & 0xff;
    // RET;
}

void GetWhiteoutSpawn(void){
    // LD_A_addr(wLastSpawnMapGroup);
    // LD_D_A;
    // LD_A_addr(wLastSpawnMapNumber);
    // LD_E_A;
    // FARCALL(aIsSpawnPoint);
    u8_flag_s res = IsSpawnPoint(gCurMapData.lastSpawnMapGroup, gCurMapData.lastSpawnMapNumber);
    // LD_A_C;
    // IF_C goto yes;
    // XOR_A_A;  // SPAWN_HOME

// yes:
    // LD_addr_A(wDefaultSpawnpoint);
    wram->wDefaultSpawnpoint = (res.flag)? res.a: SPAWN_HOME;
    // RET;
}
