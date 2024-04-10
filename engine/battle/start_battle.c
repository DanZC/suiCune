#include "../../constants.h"
#include "start_battle.h"
#include "core.h"
#include "trainer_huds.h"
#include "battle_transition.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/clear_sprites.h"
#include "../overworld/landmarks.h"

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

//  If we're not in a communications room,
//  we don't need to be here.
void ShowLinkBattleParticipants_Conv(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_Z ;
    if(wram->wLinkMode == 0)
        return;

    // FARCALL(av_ShowLinkBattleParticipants);
    v_ShowLinkBattleParticipants();
    // LD_C(150);
    // CALL(aDelayFrames);
    DelayFrames_Conv(150);
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // RET;
}

void FindFirstAliveMonAndStartBattle(void){
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0;
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_B(PARTY_LENGTH);
    // LD_HL(wPartyMon1HP);
    // LD_DE(PARTYMON_STRUCT_LENGTH - 1);

    struct PartyMon* hl = wram->wPartyMon;
    uint8_t lvl = 1;
    for(uint32_t i = 0; i < PARTY_LENGTH; ++i, ++hl) {
    // loop:
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto okay;
        if(hl->HP != 0) {
            lvl = hl->mon.level;
            break;
        }
        // ADD_HL_DE;
        // DEC_B;
        // IF_NZ goto loop;
    }

// okay:
    // LD_DE(MON_LEVEL - MON_HP);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wBattleMonLevel);
    wram->wBattleMon.level = lvl;
    // PREDEF(pDoBattleTransition);
    DoBattleTransition();
    // FARCALL(av_LoadBattleFontsHPBar);
    v_LoadBattleFontsHPBar();
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 1;
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // LDH_addr_A(hWY);
    hram->hWY = 0x0;
    // LDH_addr_A(rWY);
    gb_write(rWY, 0x0);
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = FALSE;
    // RET;
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

void PlayBattleMusic_Conv(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // XOR_A_A;
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0;
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aMaxVolume);
    MaxVolume_Conv();

    uint16_t de;
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_SUICUNE);
    // LD_DE(MUSIC_SUICUNE_BATTLE);
    // JP_Z (mPlayBattleMusic_done);
    // CP_A(BATTLETYPE_ROAMING);
    // JP_Z (mPlayBattleMusic_done);
    if(wram->wBattleType == BATTLETYPE_SUICUNE || wram->wBattleType == BATTLETYPE_ROAMING) {
        de = MUSIC_SUICUNE_BATTLE;
    }

// Are we fighting a trainer?
    // LD_A_addr(wOtherTrainerClass);
    // AND_A_A;
    // IF_NZ goto trainermusic;
    else if(wram->wOtherTrainerClass != 0) {
    // trainermusic:
        // LD_DE(MUSIC_CHAMPION_BATTLE);
        // CP_A(CHAMPION);
        // IF_Z goto done;
        // CP_A(RED);
        // IF_Z goto done;
        if(wram->wOtherTrainerClass == CHAMPION || wram->wOtherTrainerClass == RED) {
            de = MUSIC_CHAMPION_BATTLE;
        }

    // They should have included EXECUTIVEM, EXECUTIVEF, and SCIENTIST too...
        // LD_DE(MUSIC_ROCKET_BATTLE);
        // CP_A(GRUNTM);
        // IF_Z goto done;
        // CP_A(GRUNTF);
        // IF_Z goto done;
        else if(wram->wOtherTrainerClass == GRUNTM || wram->wOtherTrainerClass == GRUNTF
             || wram->wOtherTrainerClass == EXECUTIVEM || wram->wOtherTrainerClass == EXECUTIVEF) {
            de = MUSIC_ROCKET_BATTLE;
        }

        // LD_DE(MUSIC_KANTO_GYM_LEADER_BATTLE);
        // FARCALL(aIsKantoGymLeader);
        // IF_C goto done;
        else if(IsKantoGymLeader_Conv(wram->wOtherTrainerClass)) {
            de = MUSIC_KANTO_GYM_LEADER_BATTLE;
        }

    // IsGymLeader also counts CHAMPION, RED, and the Kanto gym leaders
    // but they have been taken care of before this
        // LD_DE(MUSIC_JOHTO_GYM_LEADER_BATTLE);
        // FARCALL(aIsGymLeader);
        // IF_C goto done;
        else if(IsGymLeader_Conv(wram->wOtherTrainerClass)) {
            de = MUSIC_JOHTO_GYM_LEADER_BATTLE;
        }

        // LD_DE(MUSIC_RIVAL_BATTLE);
        // LD_A_addr(wOtherTrainerClass);
        // CP_A(RIVAL1);
        // IF_Z goto done;
        else if(wram->wOtherTrainerClass == RIVAL1) {
            de = MUSIC_RIVAL_BATTLE;
        }
        // CP_A(RIVAL2);
        // IF_NZ goto othertrainer;

        // LD_A_addr(wOtherTrainerID);
        // CP_A(RIVAL2_2_CHIKORITA);  // Rival in Indigo Plateau
        // IF_C goto done;
        // LD_DE(MUSIC_CHAMPION_BATTLE);
        // goto done;
        else if(wram->wOtherTrainerClass == RIVAL2) {
            if(wram->wOtherTrainerID < RIVAL2_2_CHIKORITA) {
                de = MUSIC_RIVAL_BATTLE;
            }
            else {
                de = MUSIC_CHAMPION_BATTLE;
            }
        }


    // othertrainer:
        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // IF_NZ goto johtotrainer;
        else if(wram->wLinkMode != 0) {
            de = MUSIC_JOHTO_TRAINER_BATTLE;
        }

        // FARCALL(aRegionCheck);
        // LD_A_E;
        // AND_A_A;
        // IF_NZ goto kantotrainer;
        else if(RegionCheck_Conv() != 0) {
            de = MUSIC_KANTO_TRAINER_BATTLE;
        }


    // johtotrainer:
        // LD_DE(MUSIC_JOHTO_TRAINER_BATTLE);
        // goto done;
        else {
            de = MUSIC_JOHTO_TRAINER_BATTLE;
        }


    // kantotrainer:
        // LD_DE(MUSIC_KANTO_TRAINER_BATTLE);
    }

    // FARCALL(aRegionCheck);
    // LD_A_E;
    // AND_A_A;
    // IF_NZ goto kantowild;
    else if(RegionCheck_Conv() != JOHTO_REGION) {
    // kantowild:
        // LD_DE(MUSIC_KANTO_WILD_BATTLE);
        // goto done;
        de = MUSIC_KANTO_WILD_BATTLE;
    }

    // LD_DE(MUSIC_JOHTO_WILD_BATTLE);
    // LD_A_addr(wTimeOfDay);
    // CP_A(NITE_F);
    // IF_NZ goto done;
    else if(wram->wTimeOfDay != NITE_F) {
        de = MUSIC_JOHTO_WILD_BATTLE;
    }
    // LD_DE(MUSIC_JOHTO_WILD_BATTLE_NIGHT);
    // goto done;
    else {
        de = MUSIC_JOHTO_WILD_BATTLE_NIGHT;
    }


// done:
    // CALL(aPlayMusic);
    PlayMusic_Conv(de);

    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
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

void ClearBattleRAM_Conv(void){
    // XOR_A_A;
    // LD_addr_A(wBattlePlayerAction);
    // LD_addr_A(wBattleResult);
    wram->wBattlePlayerAction = 0;
    wram->wBattleResult = 0;

    // LD_HL(wPartyMenuCursor);
    // LD_hli_A;
    wram->wPartyMenuCursor = 0;
    // LD_hli_A;
    wram->wItemsPocketCursor = 0;
    // LD_hli_A;
    wram->wKeyItemsPocketCursor = 0;
    // LD_hl_A;
    wram->wBallsPocketCursor = 0;

    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = 0;
    // LD_addr_A(wCriticalHit);
    wram->wCriticalHit = 0;
    // LD_addr_A(wBattleMonSpecies);
    wram->wBattleMon.species = 0;
    // LD_addr_A(wBattleParticipantsNotFainted);
    wram->wBattleParticipantsNotFainted = 0;
    // LD_addr_A(wCurBattleMon);
    wram->wCurBattleMon = 0;
    // LD_addr_A(wForcedSwitch);
    wram->wForcedSwitch = 0;
    // LD_addr_A(wTimeOfDayPal);
    wram->wTimeOfDayPal = 0;
    // LD_addr_A(wPlayerTurnsTaken);
    wram->wPlayerTurnsTaken = 0;
    // LD_addr_A(wEnemyTurnsTaken);
    wram->wEnemyTurnsTaken = 0;
    // LD_addr_A(wEvolvableFlags);
    wram->wEvolvableFlags[0] = 0;

    // LD_HL(wPlayerHPPal);
    // LD_hli_A;
    wram->wPlayerHPPal = 0;
    // LD_hl_A;
    wram->wEnemyHPPal = 0;

    // LD_HL(wBattleMonDVs);
    // LD_hli_A;
    // LD_hl_A;
    wram->wBattleMon.dvs = 0;

    // LD_HL(wEnemyMonDVs);
    // LD_hli_A;
    // LD_hl_A;
    wram->wEnemyMon.dvs = 0;

//  Clear the entire BattleMons area
    // LD_HL(wBattle);
    // LD_BC(wBattleEnd - wBattle);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(&wram->wEnemyMoveStruct.animation, wBattleEnd - wBattle, 0);

    // CALLFAR(aResetEnemyStatLevels);
    ResetEnemyStatLevels_Conv();

    // CALL(aClearWindowData);
    ClearWindowData_Conv();

    // LD_HL(hBGMapAddress);
    // XOR_A_A;  // LOW(vBGMap0)
    // LD_hli_A;
    // LD_hl(HIGH(vBGMap0));
    hram->hBGMapAddress = vBGMap0;
    // RET;

}
