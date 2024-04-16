#include "../../constants.h"
#include "specials.h"
#include "../../data/events/special_pointers.h"
#include "../overworld/map_objects.h"
#include "../overworld/time.h"
#include "../menus/intro_menu.h"
#include "../pokegear/pokegear.h"
#include "../../home/sram.h"
#include "../../home/map.h"
#include "../../home/pokemon.h"

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
    LD_A_addr(wScriptVar);
    LD_B_A;
    FARCALL(av_FindPartyMonThatSpecies);
    JR_Z (mFoundNone);
    JR(mFoundOne);

}

void FindPartyMonThatSpeciesYourTrainerID(void){
    LD_A_addr(wScriptVar);
    LD_B_A;
    FARCALL(av_FindPartyMonThatSpeciesYourTrainerID);
    JR_Z (mFoundNone);
    JR(mFoundOne);

}

void FoundOne(void){
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void FoundNone(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;

}

void NameRival(void){
    LD_B(NAME_RIVAL);
    LD_DE(wRivalName);
    FARCALL(av_NamingScreen);
    LD_HL(wRivalName);
    LD_DE(mNameRival_DefaultName);
    CALL(aInitName);
    RET;


DefaultName:
    //db ['"SILVER@"'];

    return NameRater();
}

void NameRater(void){
    FARCALL(av_NameRater);
    RET;

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
    XOR_A_A;
    LD_addr_A(wScriptVar);
    FARCALL(av_PlayersHousePC);
    LD_A_C;
    LD_addr_A(wScriptVar);
    RET;

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
    LD_A(BANK(sMysteryGiftItem));
    CALL(aOpenSRAM);
    LD_A_addr(sMysteryGiftItem);
    LD_addr_A(wCurItem);
    LD_A(1);
    LD_addr_A(wItemQuantityChange);
    LD_HL(wNumItems);
    CALL(aReceiveItem);
    IF_NC goto no_room;
    XOR_A_A;
    LD_addr_A(sMysteryGiftItem);
    CALL(aCloseSRAM);
    LD_A_addr(wCurItem);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    LD_HL(mGetMysteryGiftItem_ReceiveItemText);
    CALL(aPrintText);
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;


no_room:
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;


ReceiveItemText:
    //text_far ['_ReceiveItemText']
    //text_end ['?']

    return BugContestJudging();
}

void BugContestJudging(void){
    FARCALL(av_BugContestJudging);
    LD_A_B;
    LD_addr_A(wScriptVar);
    RET;

}

void MapRadio(void){
    // LD_A_addr(wScriptVar);
    // LD_E_A;
    // FARCALL(aPlayRadio);
    PlayRadio_Conv(wram->wScriptVar);
    // RET;
}

void UnownPuzzle(void){
    CALL(aFadeToMenu);
    FARCALL(av_UnownPuzzle);
    LD_A_addr(wSolvedUnownPuzzle);
    LD_addr_A(wScriptVar);
    CALL(aExitAllMenus);
    RET;

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
    LD_A_addr(wScriptVar);
    LD_addr_A(wFishingSwarmFlag);
    RET;

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
    FARCALL(av_CheckPokerus);
    JP(mScriptReturnCarry);

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
    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto cgb;
    LDH_A_addr(hSGB);
    AND_A_A;
    IF_NZ goto sgb;
//  gb
    XOR_A_A;  // GBCHECK_GB
    goto done;


sgb:
    LD_A(GBCHECK_SGB);
    goto done;


cgb:
    LD_A(GBCHECK_CGB);

done:
    LD_addr_A(wScriptVar);
    RET;

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
    CALL(aFadeToMenu);
    FARCALL(av_Diploma);
    CALL(aExitAllMenus);
    RET;

}

void PrintDiploma(void){
    CALL(aFadeToMenu);
    FARCALL(av_PrintDiploma);
    CALL(aExitAllMenus);
    RET;

}

void TrainerHouse(void){
    LD_A(BANK(sMysteryGiftTrainerHouseFlag));
    CALL(aOpenSRAM);
    LD_A_addr(sMysteryGiftTrainerHouseFlag);
    LD_addr_A(wScriptVar);
    JP(mCloseSRAM);

}
