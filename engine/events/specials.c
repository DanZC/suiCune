#include "../../constants.h"
#include "specials.h"
#include "pokecenter_pc.h"
#include "name_rater.h"
#include "diploma.h"
#include "print_unown.h"
#include "bug_contest/judging.h"
#include "pokerus/check_pokerus.h"
#include "../menus/naming_screen.h"
#include "../../data/events/special_pointers.h"
#include "../overworld/map_objects.h"
#include "../overworld/time.h"
#include "../menus/intro_menu.h"
#include "../pokegear/pokegear.h"
#include "../pokemon/search2.h"
#include "../pokedex/new_pokedex_entry.h"
#include "../printer/printer.h"
#include "../games/slot_machine.h"
#include "../games/card_flip.h"
#include "../games/unown_puzzle.h"
#include "../battle/core.h"
#include "../../home/sram.h"
#include "../../home/map.h"
#include "../../home/pokemon.h"
#include "../../home/string.h"
#include "../../home/item.h"
#include "../../home/names.h"
#include "../../home/text.h"
#include "../../home/pokedex_flags.h"
#include "../../home/tilemap.h"
#include "../../data/text/common.h"

//  Run script special de.
void Special(uint16_t de){
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
    // RET;

}

void SetPlayerPalette(void){
    // LD_A_addr(wScriptVar);
    // LD_D_A;
    // FARCALL(av_SetPlayerPalette);
    v_SetPlayerPalette(wram->wScriptVar);
    // RET;
}

void GameCornerPrizeMonCheckDex(void){
    // LD_A_addr(wScriptVar);
    // DEC_A;
    // CALL(aCheckCaughtMon);
    // RET_NZ ;
    if(CheckCaughtMon(wram->wScriptVar - 1))
        return;
    // LD_A_addr(wScriptVar);
    // DEC_A;
    // CALL(aSetSeenAndCaughtMon);
    SetSeenAndCaughtMon(wram->wScriptVar - 1);
    // CALL(aFadeToMenu);
    FadeToMenu();
    // LD_A_addr(wScriptVar);
    // LD_addr_A(wNamedObjectIndex);
    wram->wNamedObjectIndex = wram->wScriptVar;
    // FARCALL(aNewPokedexEntry);
    NewPokedexEntry();
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // RET;
}

void UnusedSetSeenMon(void){
    // LD_A_addr(wScriptVar);
    // DEC_A;
    // CALL(aSetSeenMon);
    SetSeenMon(wram->wScriptVar - 1);
    // RET;
}

void FindPartyMonAboveLevel(void){
    // LD_A_addr(wScriptVar);
    // LD_B_A;
    uint8_t level = wram->wScriptVar;
    // FARCALL(av_FindPartyMonAboveLevel);
    // JR_Z (mFoundNone);
    if(v_FindPartyMonAboveLevel(level) == 0)
        return FoundNone();
    // JR(mFoundOne);
    return FoundOne();
}

void FindPartyMonAtLeastThatHappy(void){
    // LD_A_addr(wScriptVar);
    // LD_B_A;
    uint8_t happiness = wram->wScriptVar;
    // FARCALL(av_FindPartyMonAtLeastThatHappy);
    // JR_Z (mFoundNone);
    if(v_FindPartyMonAtLeastThatHappy(happiness) == 0)
        return FoundNone();
    // JR(mFoundOne);
    return FoundOne();
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
    v_NamingScreen(gPlayer.rivalName, NAME_RIVAL);
    // LD_HL(wRivalName);
    // LD_DE(mNameRival_DefaultName);
    // CALL(aInitName);
    InitName(gPlayer.rivalName, U82C(DefaultName));
    // RET;
}

void NameRater(void){
    // FARCALL(av_NameRater);
    // RET;
    return v_NameRater();
}

void OverworldTownMap(void){
    // CALL(aFadeToMenu);
    FadeToMenu();
    // FARCALL(av_TownMap);
    v_TownMap();
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // RET;
}

void UnownPrinter(void){
    // CALL(aFadeToMenu);
    FadeToMenu();
    // FARCALL(av_UnownPrinter);
    v_UnownPrinter();
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // RET;
}

void DisplayLinkRecord(void){
    // CALL(aFadeToMenu);
    FadeToMenu();
    // FARCALL(av_DisplayLinkRecord);
    v_DisplayLinkRecord();
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // RET;
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
    OpenSRAM(MBANK(asMysteryGiftItem));
    // LD_A_addr(sMysteryGiftItem);
    // AND_A_A;
    // IF_Z goto no;
    // INC_A;
// no:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (gb_read(sMysteryGiftItem) == 0)? FALSE: gb_read(sMysteryGiftItem) + 1;
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void GetMysteryGiftItem(void){
    static const txt_cmd_s ReceiveItemText[] = {
        text_far(v_ReceiveItemText)
        text_end
    };
    // LD_A(BANK(sMysteryGiftItem));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMysteryGiftItem));
    // LD_A_addr(sMysteryGiftItem);
    // LD_addr_A(wCurItem);
    wram->wCurItem = gb_read(sMysteryGiftItem);
    // LD_A(1);
    // LD_addr_A(wItemQuantityChange);
    // LD_HL(wNumItems);
    // CALL(aReceiveItem);
    // IF_NC goto no_room;
    if(!ReceiveItem(GetItemPocket(ITEM_POCKET), wram->wCurItem, 1)) {
    // no_room:
        // CALL(aCloseSRAM);
        CloseSRAM();
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
    CloseSRAM();
    // LD_A_addr(wCurItem);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    GetItemName(wram->wCurItem);
    // LD_HL(mGetMysteryGiftItem_ReceiveItemText);
    // CALL(aPrintText);
    PrintText(ReceiveItemText);
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
    PlayRadio(wram->wScriptVar);
    // RET;
}

void UnownPuzzle(void){
    // CALL(aFadeToMenu);
    FadeToMenu();
    // FARCALL(av_UnownPuzzle);
    v_UnownPuzzle();
    // LD_A_addr(wSolvedUnownPuzzle);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wSolvedUnownPuzzle;
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // RET;
}

void SlotMachine(void){
    // CALL(aCheckCoinsAndCoinCase);
    // RET_C ;
    if(!CheckCoinsAndCoinCase())
        return;
    // LD_A(BANK(av_SlotMachine));
    // LD_HL(mv_SlotMachine);
    // CALL(aStartGameCornerGame);
    StartGameCornerGame(v_SlotMachine);
    // RET;
}

void CardFlip(void){
    // CALL(aCheckCoinsAndCoinCase);
    // RET_C ;
    if(!CheckCoinsAndCoinCase())
        return;
    // LD_A(BANK(av_CardFlip));
    // LD_HL(mv_CardFlip);
    // CALL(aStartGameCornerGame);
    StartGameCornerGame(v_CardFlip);
    // RET;
}

void UnusedMemoryGame(void){
    // CALL(aCheckCoinsAndCoinCase);
    // RET_C ;
    if(!CheckCoinsAndCoinCase())
        return;
    // LD_A(BANK(av_MemoryGame));
    // LD_HL(mv_MemoryGame);
    // CALL(aStartGameCornerGame);
    // StartGameCornerGame(v_MemoryGame); // TODO: Convert beta memory game?
    // RET;

}

void StartGameCornerGame(void (*func)(void)){
    // CALL(aFarQueueScript);
    // CALL(aFadeToMenu);
    FadeToMenu();
    // LD_HL(wQueuedScriptBank);
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_AF;
    // RST(aFarCall);
    func();
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // RET;
}

bool CheckCoinsAndCoinCase(void){
    static const txt_cmd_s NoCoinsText[] = {
        text_far(v_NoCoinsText)
        text_end
    };
    static const txt_cmd_s NoCoinCaseText[] = {
        text_far(v_NoCoinCaseText)
        text_end
    };
    // LD_HL(wCoins);
    // LD_A_hli;
    // OR_A_hl;
    // IF_Z goto no_coins;
    if(gPlayer.coins == 0) {
    // no_coins:
        // LD_HL(mCheckCoinsAndCoinCase_NoCoinsText);
        // goto print;
    // print:
        // CALL(aPrintText);
        PrintText(NoCoinsText);
        // SCF;
        // RET;
        return false;
    }
    // LD_A(COIN_CASE);
    // LD_addr_A(wCurItem);
    // LD_HL(wNumItems);
    // CALL(aCheckItem);
    // IF_NC goto no_coin_case;
    if(!CheckItem(GetItemPocket(ITEM_POCKET), COIN_CASE)) {
    // no_coin_case:
        // LD_HL(mCheckCoinsAndCoinCase_NoCoinCaseText);
    // print:
        // CALL(aPrintText);
        PrintText(NoCoinCaseText);
        // SCF;
        // RET;
        return false;
    }
    // AND_A_A;
    // RET;
    return true;
}

void ClearBGPalettesBufferScreen(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aBufferScreen);
    BufferScreen();
    // RET;
}

void ScriptReturnCarry(bool carry){
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
    // FARCALL(aCheckUnusedTwoDayTimer);
    CheckUnusedTwoDayTimer();
    // LD_A_addr(wUnusedTwoDayTimer);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = gPlayer.unusedTwoDayTimer;
    // RET;
}

void ActivateFishingSwarm(void){
    // LD_A_addr(wScriptVar);
    // LD_addr_A(wFishingSwarmFlag);
    gPokemon.fishingSwarmFlag = wram->wScriptVar;
    // RET;
}

void StoreSwarmMapIndices(uint8_t flag, uint8_t group, uint8_t number){
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto yanma;
    if(flag == 0){
    //  swarm dark cave violet entrance
        // LD_A_D;
        // LD_addr_A(wDunsparceMapGroup);
        gPokemon.dunsparceMapGroup = group;
        // LD_A_E;
        // LD_addr_A(wDunsparceMapNumber);
        gPokemon.dunsparceMapNumber = number;
        // RET;
    }
    else {
    // yanma:
        // LD_A_D;
        // LD_addr_A(wYanmaMapGroup);
        gPlayer.yanmaMapGroup = group;
        // LD_A_E;
        // LD_addr_A(wYanmaMapNumber);
        gPlayer.yanmaMapNumber = number;
        // RET;
    }
}

void CheckPokerus(void){
//  Check if a monster in your party has Pokerus
    // FARCALL(av_CheckPokerus);
    // JP(mScriptReturnCarry);
    return ScriptReturnCarry(v_CheckPokerus());
}

void ResetLuckyNumberShowFlag(void){
    // FARCALL(aRestartLuckyNumberCountdown);
    RestartLuckyNumberCountdown();
    // LD_HL(wLuckyNumberShowFlag);
    // RES_hl(LUCKYNUMBERSHOW_GAME_OVER_F);
    bit_reset(gPlayer.luckyNumberShowFlag, LUCKYNUMBERSHOW_GAME_OVER_F);
    // FARCALL(aLoadOrRegenerateLuckyIDNumber);
    LoadOrRegenerateLuckyIDNumber();
    // RET;
}

void CheckLuckyNumberShowFlag(void){
    // FARCALL(av_CheckLuckyNumberShowFlag);
    bool flag = v_CheckLuckyNumberShowFlag();
    // JP(mScriptReturnCarry);
    return ScriptReturnCarry(flag);
}

//  Check if the Poké Flute channel is playing, and if the player is standing
//  next to Snorlax.
//  
//  outputs:
//  wScriptVar is 1 if the conditions are met, otherwise 0.
void SnorlaxAwake(void){
    static const uint8_t ProximityCoords[] = {
    //   x,  y
        33,  8,  // left
        34, 10,  // below
        35, 10,  // below
        36,  8,  // right
        36,  9,  // right
        (uint8_t)-1,
    };
//  check background music
    // LD_A_addr(wMapMusic);
    // CP_A(MUSIC_POKE_FLUTE_CHANNEL);
    // IF_NZ goto nope;
    if(wram->wMapMusic == MUSIC_POKE_FLUTE_CHANNEL){
        // LD_A_addr(wXCoord);
        // LD_B_A;
        uint8_t b = gCurMapData.xCoord;
        // LD_A_addr(wYCoord);
        // LD_C_A;
        uint8_t c = gCurMapData.yCoord;

        // LD_HL(mSnorlaxAwake_ProximityCoords);
        const uint8_t* hl = ProximityCoords;

        while(*hl != (uint8_t)-1){
        // loop:
            // LD_A_hli;
            // CP_A(-1);
            // IF_Z goto nope;
            // CP_A_B;
            // IF_NZ goto nextcoord;

            // LD_A_hli;
            // CP_A_C;
            // IF_NZ goto loop;
            if(hl[0] == b && hl[1] == c){
                // LD_A(TRUE);
                // goto done;
                wram->wScriptVar = TRUE;
                return;
            }

        // nextcoord:
            // INC_HL;
            hl += 2;
            // goto loop;
        }
    }

// nope:
    // XOR_A_A;

// done:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // RET;
}

void PlayCurMonCry(void){
    // LD_A_addr(wCurPartySpecies);
    // JP(mPlayMonCry);
    PlayMonCry(wram->wCurPartySpecies);
}

void GameboyCheck(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    if(hram.hCGB != 0) {
    // cgb:
        // LD_A(GBCHECK_CGB);
        wram->wScriptVar = GBCHECK_CGB;
    }
    // LDH_A_addr(hSGB);
    // AND_A_A;
    // IF_NZ goto sgb;
    else if(hram.hSGB != 0) {
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
    FadeToMenu();
    // FARCALL(av_Diploma);
    v_Diploma();
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // RET;
}

void PrintDiploma(void){
    // CALL(aFadeToMenu);
    FadeToMenu();
    // FARCALL(av_PrintDiploma);
    v_PrintDiploma();
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // RET;
}

void TrainerHouse(void){
    // LD_A(BANK(sMysteryGiftTrainerHouseFlag));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMysteryGiftTrainerHouseFlag));
    // LD_A_addr(sMysteryGiftTrainerHouseFlag);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = gb_read(sMysteryGiftTrainerHouseFlag);
    // JP(mCloseSRAM);
    CloseSRAM();
}
