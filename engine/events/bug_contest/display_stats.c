#include "../../../constants.h"
#include "display_stats.h"
#include "../../../home/names.h"
#include "../../../home/text.h"
#include "../../../home/print_text.h"
#include "../../../home/tilemap.h"
#include "../../../home/gfx.h"
#include "../../../home/clear_sprites.h"
#include "../../../home/pokemon.h"
#include "../../../data/text/common.h"

void DisplayCaughtContestMonStats(void){
    static const char Health[] = "HEALTH@";
    static const char Stock[] = " STOCK <PKMN> @";
    static const char This[] = " THIS <PKMN>  @";
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra();

    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);

    // hlcoord(0, 0, wTilemap);
    // LD_B(4);
    // LD_C(13);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 0, wram->wTilemap), 4, 13);

    // hlcoord(0, 6, wTilemap);
    // LD_B(4);
    // LD_C(13);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 6, wram->wTilemap), 4, 13);

    // hlcoord(2, 0, wTilemap);
    // LD_DE(mDisplayCaughtContestMonStats_Stock);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Stock), coord(2, 0, wram->wTilemap));

    // hlcoord(2, 6, wTilemap);
    // LD_DE(mDisplayCaughtContestMonStats_This);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(This), coord(2, 6, wram->wTilemap));

    // hlcoord(5, 4, wTilemap);
    // LD_DE(mDisplayCaughtContestMonStats_Health);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Health), coord(5, 4, wram->wTilemap));

    // hlcoord(5, 10, wTilemap);
    // LD_DE(mDisplayCaughtContestMonStats_Health);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Health), coord(5, 10, wram->wTilemap));

    // LD_A_addr(wContestMon);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_DE(wStringBuffer1);
    // hlcoord(1, 2, wTilemap);
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl = coord(1, 2, wram->wTilemap), .de = GetPokemonName(wram->wContestMon.mon.species)};
    PlaceString_Conv(&st, st.hl);

    // LD_H_B;
    // LD_L_C;
    // LD_A_addr(wContestMonLevel);
    // LD_addr_A(wTempMonLevel);
    // CALL(aPrintLevel);
    PrintLevel_Conv(st.bc, wram->wContestMon.mon.level);

    // LD_DE(wEnemyMonNickname);
    st.de = wram->wEnemyMonNickname;
    // hlcoord(1, 8, wTilemap);
    st.hl = coord(1, 8, wram->wTilemap);
    // CALL(aPlaceString);
    PlaceString_Conv(&st, st.hl);

    // LD_H_B;
    // LD_L_C;
    // LD_A_addr(wEnemyMonLevel);
    // LD_addr_A(wTempMonLevel);
    // CALL(aPrintLevel);
    PrintLevel_Conv(st.bc, wram->wEnemyMon.level);

    // hlcoord(11, 4, wTilemap);
    // LD_DE(wContestMonMaxHP);
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(11, 4, wram->wTilemap), &wram->wContestMon.maxHP, 2, 3);

    // hlcoord(11, 10, wTilemap);
    // LD_DE(wEnemyMonMaxHP);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(11, 10, wram->wTilemap), &wram->wEnemyMon.maxHP, 2, 3);

    // LD_HL(mContestAskSwitchText);
    // CALL(aPrintText);
    PrintText_Conv2(ContestAskSwitchText);

    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;

    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // RET;
}

const txt_cmd_s ContestAskSwitchText[] = {
    text_far(v_ContestAskSwitchText)
    text_end
};

void DisplayAlreadyCaughtText(species_t a){
    static const txt_cmd_s ContestAlreadyCaughtText[] = {
        text_far(v_ContestAlreadyCaughtText)
        text_end
    };
    // CALL(aGetPokemonName);
    GetPokemonName(a);
    // LD_HL(mDisplayAlreadyCaughtText_ContestAlreadyCaughtText);
    // JP(mPrintText);
    PrintText_Conv2(ContestAlreadyCaughtText);
}

// void DummyPredef2F(void){
//     return DummyPredef38();
// }

// void DummyPredef38(void){
//     return DummyPredef39();
// }

// void DummyPredef39(void){
//     RET;
// }
