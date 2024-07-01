#include "../../constants.h"
#include "trademon_frontpic.h"
#include "load_pics.h"
#include "pic_animation.h"
#include "../../home/pokemon.h"
#include "../../home/tilemap.h"
#include "../../home/palettes.h"
#include "../movie/trade_animation.h"

void GetTrademonFrontpic(void){
    // LD_A_addr(wOTTrademonSpecies);
    // LD_HL(wOTTrademonDVs);
    // LD_DE(vTiles2);
    // PUSH_DE;
    // PUSH_AF;
    // PREDEF(pGetUnownLetter);
    GetUnownLetter_Conv(wram->wOTTrademon.dvs);
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wOTTrademon.species);
    // POP_DE;
    // PREDEF(pGetAnimatedFrontpic);
    GetAnimatedFrontpic_Conv(vram->vTiles2, 0);
    // RET;
}

void AnimateTrademonFrontpic(void){
    // LD_A_addr(wOTTrademonSpecies);
    // CALL(aIsAPokemon);
    // RET_C ;
    if(!IsAPokemon_Conv(wram->wOTTrademon.species))
        return;
    // FARCALL(aShowOTTrademonStats);
    ShowOTTrademonStats();
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species;
    // LD_A_addr(wOTTrademonDVs);
    // LD_addr_A(wTempMonDVs);
    // LD_A_addr(wOTTrademonDVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = wram->wOTTrademon.dvs;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // FARCALL(aTradeAnim_ShowGetmonFrontpic);
    TradeAnim_ShowGetmonFrontpic();
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species;
    // hlcoord(7, 2, wTilemap);
    // LD_D(0x0);
    // LD_E(ANIM_MON_TRADE);
    // PREDEF(pAnimateFrontpic);
    AnimateFrontpic_Conv(coord(7, 2, wram->wTilemap), 0x0, ANIM_MON_TRADE);
    // RET;
}
