#include "../../constants.h"
#include "specials.h"
#include "pokecenter_pc.h"
#include "name_rater.h"
#include "diploma.h"
#include "bug_contest/judging.h"
#include "pokerus/check_pokerus.h"
#include "../menus/naming_screen.h"
#include "../../data/events/special_pointers.h"
#include "../overworld/map_objects.h"
#include "../overworld/time.h"
#include "../menus/intro_menu.h"
#include "../pokegear/pokegear.h"
#include "../pokemon/search2.h"
#include "../printer/printer.h"
#include "../games/unown_puzzle.h"
#include "../../home/sram.h"
#include "../../home/map.h"
#include "../../home/pokemon.h"
#include "../../home/string.h"
#include "../../home/item.h"
#include "../../home/names.h"
#include "../../home/text.h"
#include "../../data/text/common.h"

void Special(void){
//  Run script special de.
    LD_HL(mSpecialsPointers);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_B_hl;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_B;
    RST(aFarCall);
    RET;

// INCLUDE "data/events/special_pointers.asm"

    return UnusedDummySpecial();
}

void Special_Conv(uint16_t de){
//  Run script special de.
    // LD_HL(mSpecialsPointers);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_B_hl;
    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_B;
    // RST(aFarCall);
    // RET;

// INCLUDE "data/events/special_pointers.asm"
    if(SpecialsPointers[de] == NULL) {
        printf("special %d is undefined.\n", de);
        return;
    }

    return SpecialsPointers[de]();
}

void UnusedDummySpecial(void){
    RET;

}

void SetPlayerPalette(void){
    // LD_A_addr(wScriptVar);
    // LD_D_A;
    // FARCALL(av_SetPlayerPalette);
    v_SetPlayerPalette_Conv(wram->wScriptVar);
    // RET;
}

void GameCornerPrizeMonCheckDex(void){
    LD_A_addr(wScriptVar);
    DEC_A;
    CALL(aCheckCaughtMon);
    RET_NZ ;
    LD_A_addr(wScriptVar);
    DEC_A;
    CALL(aSetSeenAndCaughtMon);
    CALL(aFadeToMenu);
    LD_A_addr(wScriptVar);
    LD_addr_A(wNamedObjectIndex);
    FARCALL(aNewPokedexEntry);
    CALL(aExitAllMenus);
    RET;

}

void UnusedSetSeenMon(void){
    LD_A_addr(wScriptVar);
    DEC_A;
    CALL(aSetSeenMon);
    RET;

}

void FindPartyMonAboveLevel(void){
    LD_A_addr(wScriptVar);
    LD_B_A;
    FARCALL(av_FindPartyMonAboveLevel);
    JR_Z (mFoundNone);
    JR(mFoundOne);

}

void FindPartyMonAtLeastThatHappy(void){
    LD_A_addr(wScriptVar);
    LD_B_A;
    FARCALL(av_FindPartyMonAtLeastThatHappy);
    JR_Z (mFoundNone);
    JR(mFoundOne);

}

void FindPartyMonThatSpecies(void){
    // LD_A_addr(wScriptVar);
    // LD_B_A;
    // FARCALL(av_FindPartyMonThatSpecies);
    u8_flag_s res = v_FindPartyMonThatSpecies(wram->wScriptVar);
    // JR_Z (mFoundNone);
    if(!res.flag)
        return FoundNone();
    // JR(mFoundOne);
    return FoundOne();
}

void FindPartyMonThatSpeciesYourTrainerID(void){
    // LD_A_addr(wScriptVar);
    // LD_B_A;
    // FARCALL(av_FindPartyMonThatSpeciesYourTrainerID);
    if(!v_FindPartyMonThatSpeciesYourTrainerID(wram->wScriptVar)) {
        // JR_Z (mFoundNone);
        return FoundNone();
    }
    // JR(mFoundOne);
    return FoundOne();
}

void FoundOne(void){
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

void FoundNone(void){
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // RET;
}

void NameRival(void){
    static const char DefaultName[] = "SILVER@";
    // LD_B(NAME_RIVAL);
    // LD_DE(wRivalName);
    // FARCALL(av_NamingScreen);
    v_NamingScreen_Conv(wram->wRivalName, NAME_RIVAL);
    // LD_HL(wRivalName);
    // LD_DE(mNameRival_DefaultName);
    // CALL(aInitName);
    InitName_Conv2(wram->wRivalName, U82C(DefaultName));
    // RET;
}

void NameRater(void){
    // FARCALL(av_NameRater);
    // RET;
    return v_NameRater();
}

void OverworldTownMap(void){
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(av_TownMap);
    v_TownMap();
    // CALL(aExitAllMenus);
    ExitAllMenus_Conv();
    // RET;
}

void UnownPrinter(void){
    CALL(aFadeToMenu);
    FARCALL(av_UnownPrinter);
    CALL(aExitAllMenus);
    RET;

}

void DisplayLinkRecord(void){
    CALL(aFadeToMenu);
    FARCALL(av_DisplayLinkRecord);
    CALL(aExitAllMenus);
    RET;

}

void PlayersHousePC(void){
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // FARCALL(av_PlayersHousePC);
    // LD_A_C;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (v_PlayersHousePC())? TRUE: FALSE;
    // RET;
}

void CheckMysteryGift(void){
    // LD_A(BANK(sMysteryGiftItem));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMysteryGiftItem));
    // LD_A_addr(sMysteryGiftItem);
    // AND_A_A;
    // IF_Z goto no;
    // INC_A;
// no:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (gb_read(sMysteryGiftItem) == 0)? FALSE: gb_read(sMysteryGiftItem) + 1;
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void GetMysteryGiftItem(void){
    static const txt_cmd_s ReceiveItemText[] = {
        text_far(v_ReceiveItemText)
        text_end
    };
    // LD_A(BANK(sMysteryGiftItem));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMysteryGiftItem));
    // LD_A_addr(sMysteryGiftItem);
    // LD_addr_A(wCurItem);
    wram->wCurItem = gb_read(sMysteryGiftItem);
    // LD_A(1);
    // LD_addr_A(wItemQuantityChange);
    // LD_HL(wNumItems);
    // CALL(aReceiveItem);
    // IF_NC goto no_room;
    if(!ReceiveItem_Conv((item_pocket_s*)&wram->wNumItems, wram->wCurItem, 1)) {
    // no_room:
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = FALSE;
        // RET;
        return;
    }
    // XOR_A_A;
    // LD_addr_A(sMysteryGiftItem);
    gb_write(sMysteryGiftItem, NO_ITEM);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A_addr(wCurItem);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    GetItemName_Conv2(wram->wCurItem);
    // LD_HL(mGetMysteryGiftItem_ReceiveItemText);
    // CALL(aPrintText);
    PrintText_Conv2(ReceiveItemText);
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

void BugContestJudging(void){
    // FARCALL(av_BugContestJudging);
    // LD_A_B;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = v_BugContestJudging();
    // RET;
}

void MapRadio(void){
    // LD_A_addr(wScriptVar);
    // LD_E_A;
    // FARCALL(aPlayRadio);
    PlayRadio_Conv(wram->wScriptVar);
    // RET;
}

void UnownPuzzle(void){
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(av_UnownPuzzle);
    v_UnownPuzzle();
    // LD_A_addr(wSolvedUnownPuzzle);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wSolvedUnownPuzzle;
    // CALL(aExitAllMenus);
    ExitAllMenus_Conv();
    // RET;
}

void SlotMachine(void){
    CALL(aCheckCoinsAndCoinCase);
    RET_C ;
    LD_A(BANK(av_SlotMachine));
    LD_HL(mv_SlotMachine);
    CALL(aStartGameCornerGame);
    RET;

}

void CardFlip(void){
    CALL(aCheckCoinsAndCoinCase);
    RET_C ;
    LD_A(BANK(av_CardFlip));
    LD_HL(mv_CardFlip);
    CALL(aStartGameCornerGame);
    RET;

}

void UnusedMemoryGame(void){
    CALL(aCheckCoinsAndCoinCase);
    RET_C ;
    LD_A(BANK(av_MemoryGame));
    LD_HL(mv_MemoryGame);
    CALL(aStartGameCornerGame);
    RET;

}

void StartGameCornerGame(void){
    CALL(aFarQueueScript);
    CALL(aFadeToMenu);
    LD_HL(wQueuedScriptBank);
    LD_A_hli;
    PUSH_AF;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_AF;
    RST(aFarCall);
    CALL(aExitAllMenus);
    RET;

}

void CheckCoinsAndCoinCase(void){
    LD_HL(wCoins);
    LD_A_hli;
    OR_A_hl;
    IF_Z goto no_coins;
    LD_A(COIN_CASE);
    LD_addr_A(wCurItem);
    LD_HL(wNumItems);
    CALL(aCheckItem);
    IF_NC goto no_coin_case;
    AND_A_A;
    RET;


no_coins:
    LD_HL(mCheckCoinsAndCoinCase_NoCoinsText);
    goto print;


no_coin_case:
    LD_HL(mCheckCoinsAndCoinCase_NoCoinCaseText);


print:
    CALL(aPrintText);
    SCF;
    RET;


NoCoinsText:
    //text_far ['_NoCoinsText']
    //text_end ['?']


NoCoinCaseText:
    //text_far ['_NoCoinCaseText']
    //text_end ['?']

    return ClearBGPalettesBufferScreen();
}

void ClearBGPalettesBufferScreen(void){
    CALL(aClearBGPalettes);
    CALL(aBufferScreen);
    RET;

}

void ScriptReturnCarry(void){
    IF_C goto carry;
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;

carry:
    LD_A(1);
    LD_addr_A(wScriptVar);
    RET;

}

void ScriptReturnCarry_Conv(bool carry){
    // IF_C goto carry;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // RET;

// carry:
    // LD_A(1);
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = (carry)? 1: 0;
}

void UnusedCheckUnusedTwoDayTimer(void){
    FARCALL(aCheckUnusedTwoDayTimer);
    LD_A_addr(wUnusedTwoDayTimer);
    LD_addr_A(wScriptVar);
    RET;

}

void ActivateFishingSwarm(void){
    // LD_A_addr(wScriptVar);
    // LD_addr_A(wFishingSwarmFlag);
    wram->wFishingSwarmFlag = wram->wScriptVar;
    // RET;
}

void StoreSwarmMapIndices(void){
    LD_A_C;
    AND_A_A;
    IF_NZ goto yanma;
//  swarm dark cave violet entrance
    LD_A_D;
    LD_addr_A(wDunsparceMapGroup);
    LD_A_E;
    LD_addr_A(wDunsparceMapNumber);
    RET;


yanma:
    LD_A_D;
    LD_addr_A(wYanmaMapGroup);
    LD_A_E;
    LD_addr_A(wYanmaMapNumber);
    RET;

}

void CheckPokerus(void){
//  Check if a monster in your party has Pokerus
    // FARCALL(av_CheckPokerus);
    // JP(mScriptReturnCarry);
    return ScriptReturnCarry_Conv(v_CheckPokerus());
}

void ResetLuckyNumberShowFlag(void){
    // FARCALL(aRestartLuckyNumberCountdown);
    RestartLuckyNumberCountdown();
    // LD_HL(wLuckyNumberShowFlag);
    // RES_hl(LUCKYNUMBERSHOW_GAME_OVER_F);
    bit_reset(wram->wLuckyNumberShowFlag, LUCKYNUMBERSHOW_GAME_OVER_F);
    // FARCALL(aLoadOrRegenerateLuckyIDNumber);
    LoadOrRegenerateLuckyIDNumber();
    // RET;
}

void CheckLuckyNumberShowFlag(void){
    // FARCALL(av_CheckLuckyNumberShowFlag);
    bool flag = v_CheckLuckyNumberShowFlag_Conv();
    // JP(mScriptReturnCarry);
    return ScriptReturnCarry_Conv(flag);
}

void SnorlaxAwake(void){
//  Check if the Poké Flute channel is playing, and if the player is standing
//  next to Snorlax.

//  outputs:
//  wScriptVar is 1 if the conditions are met, otherwise 0.

//  check background music
    LD_A_addr(wMapMusic);
    CP_A(MUSIC_POKE_FLUTE_CHANNEL);
    IF_NZ goto nope;

    LD_A_addr(wXCoord);
    LD_B_A;
    LD_A_addr(wYCoord);
    LD_C_A;

    LD_HL(mSnorlaxAwake_ProximityCoords);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto nope;
    CP_A_B;
    IF_NZ goto nextcoord;
    LD_A_hli;
    CP_A_C;
    IF_NZ goto loop;

    LD_A(TRUE);
    goto done;


nextcoord:
    INC_HL;
    goto loop;


nope:
    XOR_A_A;

done:
    LD_addr_A(wScriptVar);
    RET;


ProximityCoords:
//   x,  y
    //db ['33', '8'];  // left
    //db ['34', '10'];  // below
    //db ['35', '10'];  // below
    //db ['36', '8'];  // right
    //db ['36', '9'];  // right
    //db ['-1'];

    return PlayCurMonCry();
}

void PlayCurMonCry(void){
    // LD_A_addr(wCurPartySpecies);
    // JP(mPlayMonCry);
    PlayMonCry_Conv(wram->wCurPartySpecies);
}

void GameboyCheck(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    if(hram->hCGB != 0) {
    // cgb:
        // LD_A(GBCHECK_CGB);
        wram->wScriptVar = GBCHECK_CGB;
    }
    // LDH_A_addr(hSGB);
    // AND_A_A;
    // IF_NZ goto sgb;
    else if(hram->hSGB != 0) {
    // sgb:
        // LD_A(GBCHECK_SGB);
        // goto done;
        wram->wScriptVar = GBCHECK_SGB;
    }
    else {
    //  gb
        // XOR_A_A;  // GBCHECK_GB
        // goto done;
        wram->wScriptVar = GBCHECK_GB;
    }

// done:
    // LD_addr_A(wScriptVar);
    // RET;
}

void FadeOutMusic(void){
    // LD_A(LOW(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID);
    // LD_A(HIGH(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_A(0x2);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x2;
    // RET;
}

void Diploma(void){
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(av_Diploma);
    v_Diploma();
    // CALL(aExitAllMenus);
    ExitAllMenus_Conv();
    // RET;
}

void PrintDiploma(void){
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(av_PrintDiploma);
    v_PrintDiploma();
    // CALL(aExitAllMenus);
    ExitAllMenus_Conv();
    // RET;
}

void TrainerHouse(void){
    // LD_A(BANK(sMysteryGiftTrainerHouseFlag));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMysteryGiftTrainerHouseFlag));
    // LD_A_addr(sMysteryGiftTrainerHouseFlag);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = gb_read(sMysteryGiftTrainerHouseFlag);
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}
