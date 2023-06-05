#include "../../constants.h"
#include "start_battle.h"

void ShowLinkBattleParticipants(void){
//  If we're not in a communications room,
//  we don't need to be here.
    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_Z ;

    FARCALL(av_ShowLinkBattleParticipants);
    LD_C(150);
    CALL(aDelayFrames);
    CALL(aClearTilemap);
    CALL(aClearSprites);
    RET;

}

void FindFirstAliveMonAndStartBattle(void){
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    CALL(aDelayFrame);
    LD_B(PARTY_LENGTH);
    LD_HL(wPartyMon1HP);
    LD_DE(PARTYMON_STRUCT_LENGTH - 1);


loop:
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto okay;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop;


okay:
    LD_DE(MON_LEVEL - MON_HP);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wBattleMonLevel);
    PREDEF(pDoBattleTransition);
    FARCALL(av_LoadBattleFontsHPBar);
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LDH_addr_A(hWY);
    LDH_addr_A(rWY);
    LDH_addr_A(hMapAnims);
    RET;

}

void PlayBattleMusic(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    XOR_A_A;
    LD_addr_A(wMusicFade);
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    CALL(aDelayFrame);
    CALL(aMaxVolume);

    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_SUICUNE);
    LD_DE(MUSIC_SUICUNE_BATTLE);
    JP_Z (mPlayBattleMusic_done);
    CP_A(BATTLETYPE_ROAMING);
    JP_Z (mPlayBattleMusic_done);

// Are we fighting a trainer?
    LD_A_addr(wOtherTrainerClass);
    AND_A_A;
    IF_NZ goto trainermusic;

    FARCALL(aRegionCheck);
    LD_A_E;
    AND_A_A;
    IF_NZ goto kantowild;

    LD_DE(MUSIC_JOHTO_WILD_BATTLE);
    LD_A_addr(wTimeOfDay);
    CP_A(NITE_F);
    IF_NZ goto done;
    LD_DE(MUSIC_JOHTO_WILD_BATTLE_NIGHT);
    goto done;


kantowild:
    LD_DE(MUSIC_KANTO_WILD_BATTLE);
    goto done;


trainermusic:
    LD_DE(MUSIC_CHAMPION_BATTLE);
    CP_A(CHAMPION);
    IF_Z goto done;
    CP_A(RED);
    IF_Z goto done;

// They should have included EXECUTIVEM, EXECUTIVEF, and SCIENTIST too...
    LD_DE(MUSIC_ROCKET_BATTLE);
    CP_A(GRUNTM);
    IF_Z goto done;
    CP_A(GRUNTF);
    IF_Z goto done;

    LD_DE(MUSIC_KANTO_GYM_LEADER_BATTLE);
    FARCALL(aIsKantoGymLeader);
    IF_C goto done;

// IsGymLeader also counts CHAMPION, RED, and the Kanto gym leaders
// but they have been taken care of before this
    LD_DE(MUSIC_JOHTO_GYM_LEADER_BATTLE);
    FARCALL(aIsGymLeader);
    IF_C goto done;

    LD_DE(MUSIC_RIVAL_BATTLE);
    LD_A_addr(wOtherTrainerClass);
    CP_A(RIVAL1);
    IF_Z goto done;
    CP_A(RIVAL2);
    IF_NZ goto othertrainer;

    LD_A_addr(wOtherTrainerID);
    CP_A(RIVAL2_2_CHIKORITA);  // Rival in Indigo Plateau
    IF_C goto done;
    LD_DE(MUSIC_CHAMPION_BATTLE);
    goto done;


othertrainer:
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto johtotrainer;

    FARCALL(aRegionCheck);
    LD_A_E;
    AND_A_A;
    IF_NZ goto kantotrainer;


johtotrainer:
    LD_DE(MUSIC_JOHTO_TRAINER_BATTLE);
    goto done;


kantotrainer:
    LD_DE(MUSIC_KANTO_TRAINER_BATTLE);


done:
    CALL(aPlayMusic);

    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void ClearBattleRAM(void){
    XOR_A_A;
    LD_addr_A(wBattlePlayerAction);
    LD_addr_A(wBattleResult);

    LD_HL(wPartyMenuCursor);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;

    LD_addr_A(wMenuScrollPosition);
    LD_addr_A(wCriticalHit);
    LD_addr_A(wBattleMonSpecies);
    LD_addr_A(wBattleParticipantsNotFainted);
    LD_addr_A(wCurBattleMon);
    LD_addr_A(wForcedSwitch);
    LD_addr_A(wTimeOfDayPal);
    LD_addr_A(wPlayerTurnsTaken);
    LD_addr_A(wEnemyTurnsTaken);
    LD_addr_A(wEvolvableFlags);

    LD_HL(wPlayerHPPal);
    LD_hli_A;
    LD_hl_A;

    LD_HL(wBattleMonDVs);
    LD_hli_A;
    LD_hl_A;

    LD_HL(wEnemyMonDVs);
    LD_hli_A;
    LD_hl_A;

//  Clear the entire BattleMons area
    LD_HL(wBattle);
    LD_BC(wBattleEnd - wBattle);
    XOR_A_A;
    CALL(aByteFill);

    CALLFAR(aResetEnemyStatLevels);

    CALL(aClearWindowData);

    LD_HL(hBGMapAddress);
    XOR_A_A;  // LOW(vBGMap0)
    LD_hli_A;
    LD_hl(HIGH(vBGMap0));
    RET;

}
