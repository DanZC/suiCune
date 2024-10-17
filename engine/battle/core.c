#include "../../constants.h"
#include "core.h"
#include "effect_commands.h"
#include "check_battle_scene.h"
#include "consume_held_item.h"
#include "read_trainer_party.h"
#include "read_trainer_attributes.h"
#include "read_trainer_dvs.h"
#include "trainer_huds.h"
#include "start_battle.h"
#include "sliding_intro.h"
#include "menu.h"
#include "link_result.h"
#include "ai/items.h"
#include "ai/move.h"
#include "../../home/battle.h"
#include "../../home/audio.h"
#include "../../home/array.h"
#include "../../home/copy.h"
#include "../../home/copy_name.h"
#include "../../home/compare.h"
#include "../../home/clear_sprites.h"
#include "../../home/delay.h"
#include "../../home/pokemon.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/copy_tilemap.h"
#include "../../home/menu.h"
#include "../../home/random.h"
#include "../../home/names.h"
#include "../../home/gfx.h"
#include "../../home/map_objects.h"
#include "../../home/sprite_updates.h"
#include "../../home/lcd.h"
#include "../../home/print_text.h"
#include "../../home/trainers.h"
#include "../../home/joypad.h"
#include "../../home/sram.h"
#include "../../home/item.h"
#include "../../data/trainers/leaders.h"
#include "../pokemon/experience.h"
#include "../pokemon/health.h"
#include "../pokemon/level_up_happiness.h"
#include "../gfx/pic_animation.h"
#include "../gfx/load_font.h"
#include "../gfx/load_pics.h"
#include "../gfx/color.h"
#include "../gfx/player_gfx.h"
#include "../gfx/place_graphic.h"
#include "../gfx/mon_icons.h"
#include "../gfx/sprites.h"
#include "../../gfx/misc.h"
#include "../smallflag.h"
#include "../pokemon/bills_pc_top.h"
#include "../pokemon/stats_screen.h"
#include "../pokemon/tempmon.h"
#include "../pokemon/mon_stats.h"
#include "../pokemon/move_mon.h"
#include "../pokemon/evolve.h"
#include "../pokemon/party_menu.h"
#include "../pokemon/mon_submenu.h"
#include "../pokemon/types.h"
#include "../items/pack.h"
#include "../items/items.h"
#include "../items/item_effects.h"
#include "../overworld/wildmons.h"
#include "../../mobile/mobile_40.h"
#include "../../mobile/mobile_41.h"
#include "../../data/text/battle.h"
#include "../../data/text/common.h"
#include "../../data/wild/treemons_asleep.h"
#include "../../data/wild/unlocked_unowns.h"
#include "../../data/wild/flee_mons.h"
#include "../../data/battle/held_heal_status.h"
#include "../../data/moves/effects_priorities.h"
#include "../../data/moves/moves.h"
#include "../../data/battle/stat_multipliers_2.h"
#include "../../data/battle/held_stat_up.h"
#include "../../data/pokemon/base_stats.h"
#include "../battle_anims/anim_commands.h"
#include "../events/catch_tutorial_input.h"
#include "../events/happiness_egg.h"
#include "../events/magikarp.h"
#include "../events/battle_tower/trainer_text.h"
#include "../events/pokerus/pokerus.h"
#include "../../charmap.h"
#include <stddef.h>

//  Core components of the battle engine.

void DoBattle(void){
    PEEK("");
    // XOR_A_A;
    // LD_addr_A(wBattleParticipantsNotFainted);
    wram->wBattleParticipantsNotFainted = 0;
    // LD_addr_A(wBattleParticipantsIncludingFainted);
    wram->wBattleParticipantsIncludingFainted = 0;
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = 0;
    // LD_addr_A(wBattleEnded);
    wram->wBattleEnded = FALSE;
    // INC_A;
    // LD_addr_A(wBattleHasJustStarted);
    wram->wBattleHasJustStarted = TRUE;
    // LD_HL(wOTPartyMon1HP);
    struct PartyMon* ot = wram->wOTPartyMon;
    // LD_BC(PARTYMON_STRUCT_LENGTH - 1);
    // LD_D(BATTLEACTION_SWITCH1 - 1);
    uint8_t d = BATTLEACTION_SWITCH1 - 1;

    while(1) {
    // loop:
        // INC_D;
        d++;
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto alive;
        if(ot->HP != 0)
            break;
        // ADD_HL_BC;
        ot++;
        // goto loop;
    }

// alive:
    // LD_A_D;
    // LD_addr_A(wBattleAction);
    wram->wBattleAction = d;
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;

    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_INTERNAL_CLOCK);
    // IF_Z goto player_2;
    if(wram->wLinkMode == LINK_NULL || hram->hSerialConnectionStatus != USING_INTERNAL_CLOCK) {
    // not_linked:
        // LD_A_addr(wBattleMode);
        printf("wBattleMode = %s\n", (wram->wBattleMode == TRAINER_BATTLE)? "trainer": "wild");
        // DEC_A;
        // IF_Z goto wild;
        if(wram->wBattleMode != WILD_BATTLE) {
            // XOR_A_A;
            // LD_addr_A(wEnemySwitchMonIndex);
            wram->wEnemySwitchMonIndex = 0;
            // CALL(aNewEnemyMonStatus);
            NewEnemyMonStatus_Conv();
            // CALL(aResetEnemyStatLevels);
            ResetEnemyStatLevels_Conv();
            // CALL(aBreakAttraction);
            BreakAttraction();
            // CALL(aEnemySwitch);
            EnemySwitch();
        }


    // wild:
        // LD_C(40);
        // CALL(aDelayFrames);
        DelayFrames_Conv(40);
    }


// player_2:
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // CALL(aCheckPlayerPartyForFitMon);
    // LD_A_D;
    // AND_A_A;
    // JP_Z (mLostBattle);
    if(!CheckPlayerPartyForFitMon_Conv()) {
        return LostBattle();
    }
    // CALL(aSafeLoadTempTilemapToTilemap);
    SafeLoadTempTilemapToTilemap_Conv();
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_DEBUG);
    // JP_Z (mDoBattle_tutorial_debug);
    // CP_A(BATTLETYPE_TUTORIAL);
    // JP_Z (mDoBattle_tutorial_debug);
    if(wram->wBattleType == BATTLETYPE_DEBUG || wram->wBattleType == BATTLETYPE_TUTORIAL) {
        // JP(aBattleMenu);
        // CALL(aBattleMenu);
        BattleMenu();
        return;
    }
    // XOR_A_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = 0;

    while(!CheckIfCurPartyMonIsFitToFight_Conv()) {
    // loop2:
        // CALL(aCheckIfCurPartyMonIsFitToFight);
        // IF_NZ goto alive2;
        // LD_HL(wCurPartyMon);
        // INC_hl;
        wram->wCurPartyMon++;
        // goto loop2;
    }


// alive2:
    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wLastPlayerMon);
    wram->wLastPlayerMon = wram->wCurBattleMon;
    // LD_A_addr(wCurPartyMon);
    // LD_addr_A(wCurBattleMon);
    wram->wCurBattleMon = wram->wCurPartyMon;
    // INC_A;
    // LD_HL(wPartySpecies - 1);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wPartySpecies[wram->wCurPartyMon];
    // LD_addr_A(wTempBattleMonSpecies);
    wram->wTempBattleMonSpecies = wram->wPartySpecies[wram->wCurPartyMon];
    // hlcoord(1, 5, wTilemap);
    // LD_A(9);
    // CALL(aSlideBattlePicOut);
    SlideBattlePicOut_Conv(coord(1, 5, wram->wTilemap), 9);
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // CALL(aResetBattleParticipants);
    ResetBattleParticipants();
    // CALL(aInitBattleMon);
    InitBattleMon();
    // CALL(aResetPlayerStatLevels);
    ResetPlayerStatLevels();
    // CALL(aSendOutMonText);
    SendOutMonText();
    // CALL(aNewBattleMonStatus);
    NewBattleMonStatus();
    // CALL(aBreakAttraction);
    BreakAttraction();
    // CALL(aSendOutPlayerMon);
    SendOutPlayerMon();
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // CALL(aSpikesDamage);
    SpikesDamage();
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked_2;
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_INTERNAL_CLOCK);
    // IF_NZ goto not_linked_2;
    if(wram->wLinkMode != LINK_NULL && hram->hSerialConnectionStatus == USING_INTERNAL_CLOCK) {
        // XOR_A_A;
        // LD_addr_A(wEnemySwitchMonIndex);
        wram->wEnemySwitchMonIndex = 0;
        // CALL(aNewEnemyMonStatus);
        NewEnemyMonStatus_Conv();
        // CALL(aResetEnemyStatLevels);
        ResetEnemyStatLevels_Conv();
        // CALL(aBreakAttraction);
        BreakAttraction();
        // CALL(aEnemySwitch);
        EnemySwitch();
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALL(aSpikesDamage);
        SpikesDamage();
    }

// not_linked_2:
    // CALL(aBattleTurn);
    BattleTurn();
    // RET;


// tutorial_debug:
    // JP(mBattleMenu);
}

void WildFled_EnemyFled_LinkBattleCanceled(void){
    // CALL(aSafeLoadTempTilemapToTilemap);
    SafeLoadTempTilemapToTilemap_Conv();
    // LD_A_addr(wBattleResult);
    // AND_A(BATTLERESULT_BITMASK);
    // ADD_A(DRAW);
    // LD_addr_A(wBattleResult);
    wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) + DRAW;
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // LD_HL(mBattleText_WildFled);
    // IF_Z goto print_text;
    if(wram->wLinkMode == 0) {
        StdBattleTextbox_Conv2(BattleText_WildFled);
    }
    else {
        // LD_A_addr(wBattleResult);
        // AND_A(BATTLERESULT_BITMASK);
        // LD_addr_A(wBattleResult);  // WIN
        wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) + WIN;
        // LD_HL(mBattleText_EnemyFled);
        // CALL(aCheckMobileBattleError);
        // IF_NC goto print_text;
        if(!CheckMobileBattleError_Conv()) {
            StdBattleTextbox_Conv2(BattleText_EnemyFled);
        }
        else {
            // LD_HL(wcd2a);
            // BIT_hl(4);
            // IF_NZ goto skip_text;
            if(!bit_test(wram->wcd2a, 4)) {
                // LD_HL(mBattleText_LinkErrorBattleCanceled);
                StdBattleTextbox_Conv2(BattleText_LinkErrorBattleCanceled);
            }
        }
    }

// print_text:
    // CALL(aStdBattleTextbox);


// skip_text:
    // CALL(aStopDangerSound);
    StopDangerSound();
    // CALL(aCheckMobileBattleError);
    // IF_C goto skip_sfx;
    if(!CheckMobileBattleError_Conv()) {
        // LD_DE(SFX_RUN);
        // CALL(aPlaySFX);
        //PlaySFX_Conv(SFX_RUN);
        WaitPlaySFX_Conv(SFX_RUN);
    }

// skip_sfx:
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // LD_A(1);
    // LD_addr_A(wBattleEnded);
    wram->wBattleEnded = TRUE;
    // RET;
}

void BattleTurn(void){
    do {
    // loop:
        // SET_PC(aBattleTurn);
        // CALL(aStubbed_Increments5_a89a);
        // CALL(aCheckContestBattleOver);
        // JP_C (mBattleTurn_quit);
        if(CheckContestBattleOver_Conv())
            break;

        // XOR_A_A;
        // LD_addr_A(wPlayerIsSwitching);
        wram->wPlayerIsSwitching = FALSE;
        // LD_addr_A(wEnemyIsSwitching);
        wram->wEnemyIsSwitching = FALSE;
        // LD_addr_A(wBattleHasJustStarted);
        wram->wBattleHasJustStarted = FALSE;
        // LD_addr_A(wPlayerJustGotFrozen);
        wram->wPlayerJustGotFrozen = FALSE;
        // LD_addr_A(wEnemyJustGotFrozen);
        wram->wEnemyJustGotFrozen = FALSE;
        // LD_addr_A(wCurDamage);
        // LD_addr_A(wCurDamage + 1);
        wram->wCurDamage = 0;

        // CALL(aHandleBerserkGene);
        HandleBerserkGene();
        // CALL(aUpdateBattleMonInParty);
        UpdateBattleMonInParty_Conv();
        // FARCALL(aAIChooseMove);
        AIChooseMove();

        // CALL(aIsMobileBattle);
        // IF_NZ goto not_disconnected;
        if(IsMobileBattle_Conv()) {
            // FARCALL(aFunction100da5);
            Function100da5();
            // FARCALL(aStartMobileInactivityTimer);
            StartMobileInactivityTimer();
            // FARCALL(aFunction100dd8);
            // JP_C (mBattleTurn_quit);
            if(SafeCallGBAutoRet(aFunction100dd8).f_bits.c)
                goto quit;
        }

    // not_disconnected:
        // CALL(aCheckPlayerLockedIn);
        // IF_C goto skip_iteration;
        if(CheckPlayerLockedIn_Conv())
            goto skip_iteration;

        do {
        // loop1:
            // CALL(aBattleMenu);
            // IF_C goto quit;
            if(BattleMenu())
                goto quit;
            // LD_A_addr(wBattleEnded);
            // AND_A_A;
            // IF_NZ goto quit;
            // LD_A_addr(wForcedSwitch);  // roared/whirlwinded/teleported
            // AND_A_A;
            // IF_NZ goto quit;
            if(wram->wBattleEnded || wram->wForcedSwitch)
                goto quit;

        skip_iteration:;
            // CALL(aParsePlayerAction);
            // IF_NZ goto loop1;
        } while(!ParsePlayerAction_Conv());

        // CALL(aEnemyTriesToFlee);
        // IF_C goto quit;
        if(EnemyTriesToFlee())
            goto quit;

        // CALL(aDetermineMoveOrder);
        bool playerFirst = DetermineMoveOrder();
        // IF_C goto _false;
        if(playerFirst) {
        // _false:
            // CALL(aBattle_PlayerFirst);
            Battle_PlayerFirst();
        }
        else {
            // CALL(aBattle_EnemyFirst);
            Battle_EnemyFirst();
            // goto proceed;
        }

    // proceed:
        // CALL(aCheckMobileBattleError);
        // IF_C goto quit;

        // LD_A_addr(wForcedSwitch);
        // AND_A_A;
        // IF_NZ goto quit;

        // LD_A_addr(wBattleEnded);
        // AND_A_A;
        // IF_NZ goto quit;
        if(CheckMobileBattleError_Conv() || wram->wForcedSwitch || wram->wBattleEnded)
            goto quit;

        // CALL(aHandleBetweenTurnEffects);
        HandleBetweenTurnEffects();
        // LD_A_addr(wBattleEnded);
        // AND_A_A;
        // IF_NZ goto quit;
        // JP(mBattleTurn_loop);
    } while(wram->wBattleEnded == 0);

quit:
    return;
    // RET;
}

void Stubbed_Increments5_a89a(void){
    RET;
    LD_A(MBANK(as5_a89a));  // MBC30 bank used by JP Crystal// inaccessible by MBC3
    CALL(aOpenSRAM);
    LD_HL(s5_a89a + 1);  // address of MBC30 bank
    INC_hl;
    IF_NZ goto finish;
    DEC_HL;
    INC_hl;
    IF_NZ goto finish;
    DEC_hl;
    INC_HL;
    DEC_hl;


finish:
    CALL(aCloseSRAM);
    RET;

}

void HandleBetweenTurnEffects(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto CheckEnemyFirst;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK) {
    // CheckEnemyFirst:
        // CALL(aCheckFaint_EnemyThenPlayer);
        // RET_C ;
        if(CheckFaint_EnemyThenPlayer())
            return;
        // CALL(aHandleFutureSight);
        HandleFutureSight();
        // CALL(aCheckFaint_EnemyThenPlayer);
        // RET_C ;
        if(CheckFaint_EnemyThenPlayer())
            return;
        // CALL(aHandleWeather);
        HandleWeather();
        // CALL(aCheckFaint_EnemyThenPlayer);
        // RET_C ;
        if(CheckFaint_EnemyThenPlayer())
            return;
        // CALL(aHandleWrap);
        HandleWrap();
        // CALL(aCheckFaint_EnemyThenPlayer);
        // RET_C ;
        if(CheckFaint_EnemyThenPlayer())
            return;
        // CALL(aHandlePerishSong);
        HandlePerishSong();
        // CALL(aCheckFaint_EnemyThenPlayer);
        // RET_C ;
        if(CheckFaint_EnemyThenPlayer())
            return;
    }
    else {
        // CALL(aCheckFaint_PlayerThenEnemy);
        // RET_C ;
        if(CheckFaint_PlayerThenEnemy())
            return;
        // CALL(aHandleFutureSight);
        HandleFutureSight();
        // CALL(aCheckFaint_PlayerThenEnemy);
        // RET_C ;
        if(CheckFaint_PlayerThenEnemy())
            return;
        // CALL(aHandleWeather);
        HandleWeather();
        // CALL(aCheckFaint_PlayerThenEnemy);
        // RET_C ;
        if(CheckFaint_PlayerThenEnemy())
            return;
        // CALL(aHandleWrap);
        HandleWrap();
        // CALL(aCheckFaint_PlayerThenEnemy);
        // RET_C ;
        if(CheckFaint_PlayerThenEnemy())
            return;
        // CALL(aHandlePerishSong);
        HandlePerishSong();
        // CALL(aCheckFaint_PlayerThenEnemy);
        // RET_C ;
        if(CheckFaint_PlayerThenEnemy())
            return;
        // goto NoMoreFaintingConditions;
    }

// NoMoreFaintingConditions:
    // CALL(aHandleLeftovers);
    HandleLeftovers();
    // CALL(aHandleMysteryberry);
    HandleMysteryberry();
    // CALL(aHandleDefrost);
    HandleDefrost();
    // CALL(aHandleSafeguard);
    HandleSafeguard();
    // CALL(aHandleScreens);
    HandleScreens();
    // CALL(aHandleStatBoostingHeldItems);
    HandleStatBoostingHeldItems();
    // CALL(aHandleHealingItems);
    HandleHealingItems();
    // CALL(aUpdateBattleMonInParty);
    UpdateBattleMonInParty_Conv();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // JP(mHandleEncore);
    return HandleEncore();
}

bool CheckFaint_PlayerThenEnemy(void){
    // CALL(aHasPlayerFainted);
    // IF_NZ goto PlayerNotFainted;
    if(HasPlayerFainted_Conv()) {
        // CALL(aHandlePlayerMonFaint);
        HandlePlayerMonFaint();
        // LD_A_addr(wBattleEnded);
        // AND_A_A;
        // IF_NZ goto BattleIsOver;
        if(wram->wBattleEnded)
            return true;
    }

// PlayerNotFainted:
    // CALL(aHasEnemyFainted);
    // IF_NZ goto BattleContinues;
    if(HasEnemyFainted_Conv()) {
        // CALL(aHandleEnemyMonFaint);
        HandleEnemyMonFaint();
        // LD_A_addr(wBattleEnded);
        // AND_A_A;
        // IF_NZ goto BattleIsOver;
        if(wram->wBattleEnded)
            return true;
    }

// BattleContinues:
    // AND_A_A;
    // RET;
    return false;

// BattleIsOver:
    // SCF;
    // RET;
}

bool CheckFaint_EnemyThenPlayer(void){
    // CALL(aHasEnemyFainted);
    // IF_NZ goto EnemyNotFainted;
    if(HasEnemyFainted_Conv()) {
        // CALL(aHandleEnemyMonFaint);
        HandleEnemyMonFaint();
        // LD_A_addr(wBattleEnded);
        // AND_A_A;
        // IF_NZ goto BattleIsOver;
        if(wram->wBattleEnded)
            return true;
    }

// EnemyNotFainted:
    // CALL(aHasPlayerFainted);
    // IF_NZ goto BattleContinues;
    if(HasPlayerFainted_Conv()) {
        // CALL(aHandlePlayerMonFaint);
        HandlePlayerMonFaint();
        // LD_A_addr(wBattleEnded);
        // AND_A_A;
        // IF_NZ goto BattleIsOver;
        if(wram->wBattleEnded)
            return true;
    }

// BattleContinues:
    // AND_A_A;
    // RET;
    return false;

// BattleIsOver:
    // SCF;
    // RET;
}

static void HandleBerserkGene_go(struct PartyMon* hl) {
    // PUSH_DE;
    // PUSH_BC;
    // CALLFAR(aGetUserItem);
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // SUB_A(BERSERK_GENE);
    // POP_BC;
    // POP_DE;
    // RET_NZ ;
    if(hl->mon.item != BERSERK_GENE)
        return;

    // LD_hl_A;
    hl->mon.item = NO_ITEM;

    // LD_H_D;
    // LD_L_E;
    // LD_A_B;
    // CALL(aGetPartyLocation);
    // XOR_A_A;
    // LD_hl_A;
    hl->mon.item = NO_ITEM;
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss3 = GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS3);
    // PUSH_AF;
    uint8_t ss3Backup = *ss3;
    // SET_hl(SUBSTATUS_CONFUSED);
    bit_set(*ss3, SUBSTATUS_CONFUSED);
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVarAddr);
    uint8_t* move = GetBattleVarAddr_Conv(BATTLE_VARS_MOVE_ANIM);
    // PUSH_HL;
    // PUSH_AF;
    uint8_t moveBackup = *move;
    // XOR_A_A;
    // LD_hl_A;
    *move = 0;
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = FALSE;
    // LD_addr_A(wEffectFailed);
    wram->wEffectFailed = FALSE;
    // FARCALL(aBattleCommand_AttackUp2);
    BattleCommand_AttackUp2();
    // POP_AF;
    // POP_HL;
    // LD_hl_A;
    *move = moveBackup;
    // CALL(aGetItemName);
    GetItemName_Conv2(moveBackup);
    // LD_HL(mBattleText_UsersStringBuffer1Activated);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_UsersStringBuffer1Activated);
    // CALLFAR(aBattleCommand_StatUpMessage);
    BattleCommand_StatUpMessage();
    // POP_AF;
    // BIT_A(SUBSTATUS_CONFUSED);
    // RET_NZ ;
    if(bit_test(ss3Backup, SUBSTATUS_CONFUSED))
        return;
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_DE(ANIM_CONFUSED);
    // CALL(aCall_PlayBattleAnim_OnlyIfVisible);
    Call_PlayBattleAnim_OnlyIfVisible_Conv(ANIM_CONFUSED);
    // CALL(aSwitchTurnCore);
    SwitchTurnCore();
    // LD_HL(mBecameConfusedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BecameConfusedText);
}

static void HandleBerserkGene_player(void) {
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // LD_DE(wPartyMon1Item);
    // LD_A_addr(wCurBattleMon);
    // LD_B_A;
    // goto go;
    return HandleBerserkGene_go(wram->wPartyMon + wram->wCurBattleMon);
}

static void HandleBerserkGene_enemy(void) {
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // LD_DE(wOTPartyMon1Item);
    // LD_A_addr(wCurOTMon);
    // LD_B_A;
// fallthrough
    return HandleBerserkGene_go(wram->wOTPartyMon + wram->wCurOTMon);
}

void HandleBerserkGene(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto reverse;

    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK) {
        HandleBerserkGene_enemy();
        HandleBerserkGene_player();
    }
    else {
        HandleBerserkGene_player();
        HandleBerserkGene_enemy();
    }
    // CALL(aHandleBerserkGene_player);
    // goto enemy;


// reverse:
    // CALL(aHandleBerserkGene_enemy);
// fallthrough


// player:
    // CALL(aSetPlayerTurn);
    // LD_DE(wPartyMon1Item);
    // LD_A_addr(wCurBattleMon);
    // LD_B_A;
    // goto go;

// enemy:
    // CALL(aSetEnemyTurn);
    // LD_DE(wOTPartyMon1Item);
    // LD_A_addr(wCurOTMon);
    // LD_B_A;
// fallthrough
}

bool EnemyTriesToFlee(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;
    // LD_A_addr(wBattleAction);
    // CP_A(BATTLEACTION_FORFEIT);
    // IF_Z goto forfeit;
    if(wram->wLinkMode == 0 || wram->wBattleAction != BATTLEACTION_FORFEIT) {
    // not_linked:
        // AND_A_A;
        // RET;
        return false;
    }

// forfeit:
    // CALL(aWildFled_EnemyFled_LinkBattleCanceled);
    WildFled_EnemyFled_LinkBattleCanceled();
    // SCF;
    // RET;
    return true;
}

// Returns true (c) if the player goes first.
bool DetermineMoveOrder(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto use_move;
    // LD_A_addr(wBattleAction);
    // CP_A(BATTLEACTION_STRUGGLE);
    // IF_Z goto use_move;
    // CP_A(BATTLEACTION_SKIPTURN);
    // IF_Z goto use_move;
    // SUB_A(BATTLEACTION_SWITCH1);
    // IF_C goto use_move;
    if(wram->wLinkMode == 0
    || wram->wBattleAction == BATTLEACTION_STRUGGLE
    || wram->wBattleAction == BATTLEACTION_SKIPTURN
    || wram->wBattleAction <  BATTLEACTION_SWITCH1) {
    // use_move:
        // LD_A_addr(wBattlePlayerAction);
        // AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
        // JP_NZ (mDetermineMoveOrder_player_first);
        if(wram->wBattlePlayerAction != BATTLEPLAYERACTION_USEMOVE)
            return true;
        // CALL(aCompareMovePriority);
        int priority = CompareMovePriority_Conv();
        // IF_Z goto equal_priority;
        if(priority != 0) {
            // JP_C (mDetermineMoveOrder_player_first);  // player goes first
            // JP(mDetermineMoveOrder_enemy_first);
            printf("DetermineMoveOrder: priority %s\n", (priority > 0)? "player": "enemy");
            return priority > 0; // True if player has higher priority, false otherwise
        }

    // equal_priority:
        item_t userItem, enemyItem;
        uint16_t userEff, enemyEff;
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALLFAR(aGetUserItem);
        userEff = GetUserItem_Conv(&userItem);
        // PUSH_BC;
        // CALLFAR(aGetOpponentItem);
        enemyEff = GetOpponentItem_Conv(&enemyItem);
        // POP_DE;
        // LD_A_D;
        // CP_A(HELD_QUICK_CLAW);
        // IF_NZ goto player_no_quick_claw;
        // LD_A_B;
        // CP_A(HELD_QUICK_CLAW);
        // IF_Z goto both_have_quick_claw;
        if(HIGH(userEff) == HELD_QUICK_CLAW && HIGH(enemyEff) == HELD_QUICK_CLAW) {
        // both_have_quick_claw:
            // LDH_A_addr(hSerialConnectionStatus);
            // CP_A(USING_INTERNAL_CLOCK);
            // IF_Z goto player_2b;
            if(hram->hSerialConnectionStatus == USING_INTERNAL_CLOCK) {
            // player_2b:
                // CALL(aBattleRandom);
                // CP_A_E;
                // JP_C (mDetermineMoveOrder_player_first);
                if(BattleRandom_Conv() < LOW(userEff))
                    return true;
                // CALL(aBattleRandom);
                // CP_A_C;
                // JP_C (mDetermineMoveOrder_enemy_first);
                if(BattleRandom_Conv() < LOW(enemyEff))
                    return false;
                // goto speed_check;
            }
            else {
                // CALL(aBattleRandom);
                // CP_A_C;
                // JP_C (mDetermineMoveOrder_enemy_first);
                if(BattleRandom_Conv() < LOW(enemyEff))
                    return false;
                // CALL(aBattleRandom);
                // CP_A_E;
                // JP_C (mDetermineMoveOrder_player_first);
                if(BattleRandom_Conv() < LOW(userEff))
                    return true;
                // goto speed_check;
            }
        }
        else if(HIGH(userEff) != HELD_QUICK_CLAW) {
        // player_no_quick_claw:
            // LD_A_B;
            // CP_A(HELD_QUICK_CLAW);
            // IF_NZ goto speed_check;
            if(HIGH(enemyEff) == HELD_QUICK_CLAW) {
                // CALL(aBattleRandom);
                // CP_A_C;
                // IF_NC goto speed_check;
                // JP(mDetermineMoveOrder_enemy_first);
                if(BattleRandom_Conv() < LOW(enemyEff))
                    return false;
            }
        }
        // CALL(aBattleRandom);
        // CP_A_E;
        // IF_NC goto speed_check;
        // JP(mDetermineMoveOrder_player_first);
        else if(BattleRandom_Conv() < LOW(userEff))
            return true;

    // speed_check:
        // LD_DE(wBattleMonSpeed);
        // LD_HL(wEnemyMonSpeed);
        // LD_C(2);
        // CALL(aCompareBytes);
        int cmp_speed = CompareBytes_Conv2(wram->wBattleMon.speed, wram->wEnemyMon.speed, 2);
        // IF_Z goto speed_tie;
        if(cmp_speed != 0) {
            // JP_NC (mDetermineMoveOrder_player_first);
            // JP(mDetermineMoveOrder_enemy_first);
            printf("DetermineMoveOrder: speed %s\n", (cmp_speed > 0)? "player": "enemy");
            printf("   player: %d\n   enemy: %d\n", wram->wBattleMon.speed[0] << 8 | wram->wBattleMon.speed[1], wram->wEnemyMon.speed[0] << 8 | wram->wEnemyMon.speed[1]);
            return cmp_speed > 0; // true if player's speed is higher, false otherwise.
        }

    // speed_tie:
        // LDH_A_addr(hSerialConnectionStatus);
        // CP_A(USING_INTERNAL_CLOCK);
        // IF_Z goto player_2c;
        if(hram->hSerialConnectionStatus != USING_INTERNAL_CLOCK) {
            // CALL(aBattleRandom);
            // CP_A(50 percent + 1);
            // JP_C (mDetermineMoveOrder_player_first);
            if(BattleRandom_Conv() < 50 percent + 1)
                return true;
            // JP(mDetermineMoveOrder_enemy_first);
            return false;
        }
        else {
        // player_2c:
            // CALL(aBattleRandom);
            // CP_A(50 percent + 1);
            // JP_C (mDetermineMoveOrder_enemy_first);
            if(BattleRandom_Conv() < 50 percent + 1)
                return false;
        }

    // player_first:
        // SCF;
        // RET;
        return true;

    // enemy_first:
        // AND_A_A;
        // RET;
    }
    // LD_A_addr(wBattlePlayerAction);
    // CP_A(BATTLEPLAYERACTION_SWITCH);
    // IF_NZ goto switch_;
    if(wram->wBattlePlayerAction == BATTLEPLAYERACTION_SWITCH) {
        // LDH_A_addr(hSerialConnectionStatus);
        // CP_A(USING_INTERNAL_CLOCK);
        // IF_Z goto player_2;
        if(hram->hSerialConnectionStatus == USING_INTERNAL_CLOCK) {
        // player_2:
            // CALL(aBattleRandom);
            // CP_A(50 percent + 1);
            // JP_C (mDetermineMoveOrder_enemy_first);
            if(BattleRandom_Conv() < 50 percent + 1)
                return false;
            // JP(mDetermineMoveOrder_player_first);
            return true;
        }
        else {
            // CALL(aBattleRandom);
            // CP_A(50 percent + 1);
            // JP_C (mDetermineMoveOrder_player_first);
            if(BattleRandom_Conv() < 50 percent + 1)
                return true;
            // JP(mDetermineMoveOrder_enemy_first);
            return false;
        }
    }

// switch_:
    // CALLFAR(aAI_Switch);
    AI_Switch();
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // CALL(aSpikesDamage);
    SpikesDamage();
    // JP(mDetermineMoveOrder_enemy_first);
    return false;
}

void CheckContestBattleOver(void){
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_CONTEST);
    IF_NZ goto contest_not_over;
    LD_A_addr(wParkBallsRemaining);
    AND_A_A;
    IF_NZ goto contest_not_over;
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    ADD_A(DRAW);
    LD_addr_A(wBattleResult);
    SCF;
    RET;


contest_not_over:
    AND_A_A;
    RET;

}

bool CheckContestBattleOver_Conv(void){
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_CONTEST);
    // IF_NZ goto contest_not_over;
    if(wram->wBattleType != BATTLETYPE_CONTEST)
        return false;
    // LD_A_addr(wParkBallsRemaining);
    // AND_A_A;
    // IF_NZ goto contest_not_over;
    if(wram->wParkBallsRemaining != 0)
        return false;
    // LD_A_addr(wBattleResult);
    // AND_A(BATTLERESULT_BITMASK);
    // ADD_A(DRAW);
    // LD_addr_A(wBattleResult);
    wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) + DRAW;
    // SCF;
    // RET;
    return true;

// contest_not_over:
    // AND_A_A;
    // RET;
}

void CheckPlayerLockedIn(void){
    LD_A_addr(wPlayerSubStatus4);
    AND_A(1 << SUBSTATUS_RECHARGE);
    JP_NZ (mCheckPlayerLockedIn_quit);

    LD_HL(wEnemySubStatus3);
    RES_hl(SUBSTATUS_FLINCHED);
    LD_HL(wPlayerSubStatus3);
    RES_hl(SUBSTATUS_FLINCHED);

    LD_A_hl;
    AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE);
    JP_NZ (mCheckPlayerLockedIn_quit);

    LD_HL(wPlayerSubStatus1);
    BIT_hl(SUBSTATUS_ROLLOUT);
    JP_NZ (mCheckPlayerLockedIn_quit);

    AND_A_A;
    RET;


quit:
    SCF;
    RET;

}

bool CheckPlayerLockedIn_Conv(void){
    // LD_A_addr(wPlayerSubStatus4);
    // AND_A(1 << SUBSTATUS_RECHARGE);
    // JP_NZ (mCheckPlayerLockedIn_quit);
    if(wram->wPlayerSubStatus4 & (1 << SUBSTATUS_RECHARGE))
        return true;

    // LD_HL(wEnemySubStatus3);
    // RES_hl(SUBSTATUS_FLINCHED);
    bit_reset(wram->wEnemySubStatus3, SUBSTATUS_FLINCHED);
    // LD_HL(wPlayerSubStatus3);
    // RES_hl(SUBSTATUS_FLINCHED);
    bit_reset(wram->wPlayerSubStatus3, SUBSTATUS_FLINCHED);

    // LD_A_hl;
    // AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE);
    // JP_NZ (mCheckPlayerLockedIn_quit);
    if(wram->wPlayerSubStatus3 & (1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE))
        return true;

    // LD_HL(wPlayerSubStatus1);
    // BIT_hl(SUBSTATUS_ROLLOUT);
    // JP_NZ (mCheckPlayerLockedIn_quit);
    if(bit_test(wram->wPlayerSubStatus1, SUBSTATUS_ROLLOUT))
        return true;

    // AND_A_A;
    // RET;
    return false;

// quit:
    // SCF;
    // RET;
}

void ParsePlayerAction(void){
    CALL(aCheckPlayerLockedIn);
    JP_C (mParsePlayerAction_locked_in);
    LD_HL(wPlayerSubStatus5);
    BIT_hl(SUBSTATUS_ENCORED);
    IF_Z goto not_encored;
    LD_A_addr(wLastPlayerMove);
    LD_addr_A(wCurPlayerMove);
    goto encored;


not_encored:
    LD_A_addr(wBattlePlayerAction);
    CP_A(BATTLEPLAYERACTION_SWITCH);
    IF_Z goto reset_rage;
    AND_A_A;
    IF_NZ goto reset_bide;
    LD_A_addr(wPlayerSubStatus3);
    AND_A(1 << SUBSTATUS_BIDE);
    IF_NZ goto locked_in;
    XOR_A_A;
    LD_addr_A(wMoveSelectionMenuType);
    INC_A;  // POUND
    LD_addr_A(wFXAnimID);
    CALL(aMoveSelectionScreen);
    PUSH_AF;
    CALL(aSafeLoadTempTilemapToTilemap);
    CALL(aUpdateBattleHuds);
    LD_A_addr(wCurPlayerMove);
    CP_A(STRUGGLE);
    IF_Z goto struggle;
    CALL(aPlayClickSFX);


struggle:
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    POP_AF;
    RET_NZ ;


encored:
    CALL(aSetPlayerTurn);
    CALLFAR(aUpdateMoveData);
    XOR_A_A;
    LD_addr_A(wPlayerCharging);
    LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_FURY_CUTTER);
    IF_Z goto continue_fury_cutter;
    XOR_A_A;
    LD_addr_A(wPlayerFuryCutterCount);


continue_fury_cutter:
    LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_RAGE);
    IF_Z goto continue_rage;
    LD_HL(wPlayerSubStatus4);
    RES_hl(SUBSTATUS_RAGE);
    XOR_A_A;
    LD_addr_A(wPlayerRageCounter);


continue_rage:
    LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    CP_A(EFFECT_PROTECT);
    IF_Z goto continue_protect;
    CP_A(EFFECT_ENDURE);
    IF_Z goto continue_protect;
    XOR_A_A;
    LD_addr_A(wPlayerProtectCount);
    goto continue_protect;


reset_bide:
    LD_HL(wPlayerSubStatus3);
    RES_hl(SUBSTATUS_BIDE);


locked_in:
    XOR_A_A;
    LD_addr_A(wPlayerFuryCutterCount);
    LD_addr_A(wPlayerProtectCount);
    LD_addr_A(wPlayerRageCounter);
    LD_HL(wPlayerSubStatus4);
    RES_hl(SUBSTATUS_RAGE);


continue_protect:
    CALL(aParseEnemyAction);
    XOR_A_A;
    RET;


reset_rage:
    XOR_A_A;
    LD_addr_A(wPlayerFuryCutterCount);
    LD_addr_A(wPlayerProtectCount);
    LD_addr_A(wPlayerRageCounter);
    LD_HL(wPlayerSubStatus4);
    RES_hl(SUBSTATUS_RAGE);
    XOR_A_A;
    RET;

}

bool ParsePlayerAction_Conv(void){
    // CALL(aCheckPlayerLockedIn);
    // JP_C (mParsePlayerAction_locked_in);
    if(CheckPlayerLockedIn_Conv())
        goto locked_in;
    // LD_HL(wPlayerSubStatus5);
    // BIT_hl(SUBSTATUS_ENCORED);
    // IF_Z goto not_encored;
    if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_ENCORED)) {
        // LD_A_addr(wLastPlayerMove);
        // LD_addr_A(wCurPlayerMove);
        wram->wCurPlayerMove = wram->wLastPlayerMove;
        goto encored;
    }

not_encored:
    // LD_A_addr(wBattlePlayerAction);
    // CP_A(BATTLEPLAYERACTION_SWITCH);
    // IF_Z goto reset_rage;
    if(wram->wBattlePlayerAction == BATTLEPLAYERACTION_SWITCH)
        goto reset_rage;
    // AND_A_A;
    // IF_NZ goto reset_bide;
    if(wram->wBattlePlayerAction != 0)
        goto reset_bide;
    // LD_A_addr(wPlayerSubStatus3);
    // AND_A(1 << SUBSTATUS_BIDE);
    // IF_NZ goto locked_in;
    if(wram->wPlayerSubStatus3 & (1 << SUBSTATUS_BIDE))
        goto locked_in;
    // XOR_A_A;
    // LD_addr_A(wMoveSelectionMenuType);
    wram->wMoveSelectionMenuType = 0;
    // INC_A;  // POUND
    // LD_addr_A(wFXAnimID);
    wram->wFXAnimID = POUND;

    // CALL(aMoveSelectionScreen);
    bool selected = MoveSelectionScreen();
    // PUSH_AF;
    // CALL(aSafeLoadTempTilemapToTilemap);
    SafeLoadTempTilemapToTilemap_Conv();
    // CALL(aUpdateBattleHuds);
    UpdateBattleHuds();
    // LD_A_addr(wCurPlayerMove);
    // CP_A(STRUGGLE);
    // IF_Z goto struggle;
    if(wram->wCurPlayerMove != STRUGGLE) {
        // CALL(aPlayClickSFX);
        PlayClickSFX_Conv();
    }

// struggle:
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // POP_AF;
    // RET_NZ ;
    if(selected)
        return false;


encored:
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // CALLFAR(aUpdateMoveData);
    UpdateMoveData();
    // XOR_A_A;
    // LD_addr_A(wPlayerCharging);
    wram->wPlayerCharging = FALSE;
    // LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    // CP_A(EFFECT_FURY_CUTTER);
    // IF_Z goto continue_fury_cutter;
    if(wram->wPlayerMoveStruct.effect != EFFECT_FURY_CUTTER) {
        // XOR_A_A;
        // LD_addr_A(wPlayerFuryCutterCount);
        wram->wPlayerFuryCutterCount = 0;
    }

// continue_fury_cutter:
    // LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    // CP_A(EFFECT_RAGE);
    // IF_Z goto continue_rage;
    if(wram->wPlayerMoveStruct.effect != EFFECT_RAGE) {
        // LD_HL(wPlayerSubStatus4);
        // RES_hl(SUBSTATUS_RAGE);
        bit_reset(wram->wPlayerSubStatus4, SUBSTATUS_RAGE);
        // XOR_A_A;
        // LD_addr_A(wPlayerRageCounter);
        wram->wPlayerRageCounter = 0;
    }

// continue_rage:
    // LD_A_addr(wPlayerMoveStruct + MOVE_EFFECT);
    // CP_A(EFFECT_PROTECT);
    // IF_Z goto continue_protect;
    // CP_A(EFFECT_ENDURE);
    // IF_Z goto continue_protect;
    if(wram->wPlayerMoveStruct.effect != EFFECT_PROTECT 
    && wram->wPlayerMoveStruct.effect != EFFECT_ENDURE) {
        // XOR_A_A;
        // LD_addr_A(wPlayerProtectCount);
        wram->wPlayerProtectCount = 0;
    }
    goto continue_protect;


reset_bide:
    // LD_HL(wPlayerSubStatus3);
    // RES_hl(SUBSTATUS_BIDE);
    bit_reset(wram->wPlayerSubStatus3, SUBSTATUS_BIDE);


locked_in:
    // XOR_A_A;
    // LD_addr_A(wPlayerFuryCutterCount);
    wram->wPlayerFuryCutterCount = 0;
    // LD_addr_A(wPlayerProtectCount);
    wram->wPlayerProtectCount = 0;
    // LD_addr_A(wPlayerRageCounter);
    wram->wPlayerRageCounter = 0;
    // LD_HL(wPlayerSubStatus4);
    // RES_hl(SUBSTATUS_RAGE);
    bit_reset(wram->wPlayerSubStatus4, SUBSTATUS_RAGE);


continue_protect:
    // CALL(aParseEnemyAction);
    ParseEnemyAction();
    // XOR_A_A;
    // RET;
    return true;


reset_rage:
    // XOR_A_A;
    // LD_addr_A(wPlayerFuryCutterCount);
    wram->wPlayerFuryCutterCount = 0;
    // LD_addr_A(wPlayerProtectCount);
    wram->wPlayerProtectCount = 0;
    // LD_addr_A(wPlayerRageCounter);
    wram->wPlayerRageCounter = 0;
    // LD_HL(wPlayerSubStatus4);
    // RES_hl(SUBSTATUS_RAGE);
    bit_reset(wram->wPlayerSubStatus4, SUBSTATUS_RAGE);
    // XOR_A_A;
    // RET;
    return true;
}

static void HandleEncore_do_player(void){
    // LD_HL(wPlayerSubStatus5);
    // BIT_hl(SUBSTATUS_ENCORED);
    // RET_Z ;
    if(!bit_test(wram->wPlayerSubStatus5, SUBSTATUS_ENCORED))
        return;
    // LD_A_addr(wPlayerEncoreCount);
    // DEC_A;
    // LD_addr_A(wPlayerEncoreCount);
    // IF_Z goto end_player_encore;
    if(--wram->wPlayerEncoreCount != 0) {
        // LD_HL(wBattleMonPP);
        // LD_A_addr(wCurMoveNum);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(PP_MASK);
        // RET_NZ ;
        if((wram->wBattleMon.pp[wram->wCurMoveNum] & PP_MASK) != 0)
            return;
    }

// end_player_encore:
    // LD_HL(wPlayerSubStatus5);
    // RES_hl(SUBSTATUS_ENCORED);
    bit_reset(wram->wPlayerSubStatus5, SUBSTATUS_ENCORED);
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // LD_HL(mBattleText_TargetsEncoreEnded);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BattleText_TargetsEncoreEnded);
}

static void HandleEncore_do_enemy(void){
    // LD_HL(wEnemySubStatus5);
    // BIT_hl(SUBSTATUS_ENCORED);
    // RET_Z ;
    if(!bit_test(wram->wEnemySubStatus5, SUBSTATUS_ENCORED))
        return;
    // LD_A_addr(wEnemyEncoreCount);
    // DEC_A;
    // LD_addr_A(wEnemyEncoreCount);
    // IF_Z goto end_enemy_encore;
    if(--wram->wEnemyEncoreCount != 0) {
        // LD_HL(wEnemyMonPP);
        // LD_A_addr(wCurEnemyMoveNum);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(PP_MASK);
        // RET_NZ ;
        if((wram->wEnemyMon.pp[wram->wCurMoveNum] & PP_MASK) != 0)
            return;
    }

// end_enemy_encore:
    // LD_HL(wEnemySubStatus5);
    // RES_hl(SUBSTATUS_ENCORED);
    bit_reset(wram->wEnemySubStatus5, SUBSTATUS_ENCORED);
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // LD_HL(mBattleText_TargetsEncoreEnded);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BattleText_TargetsEncoreEnded);
}

void HandleEncore(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto player_1;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK) {
    // player_1:
        // CALL(aHandleEncore_do_enemy);
        HandleEncore_do_enemy();
        return HandleEncore_do_player();
    }
    else {
        // CALL(aHandleEncore_do_player);
        HandleEncore_do_player();
        // goto do_enemy;
        return HandleEncore_do_enemy();
    }
}

void TryEnemyFlee(void){
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto Stay;

    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    IF_NZ goto Stay;

    LD_A_addr(wEnemyWrapCount);
    AND_A_A;
    IF_NZ goto Stay;

    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << FRZ | SLP);
    IF_NZ goto Stay;

    LD_A_addr(wTempEnemyMonSpecies);
    LD_DE(1);
    LD_HL(mAlwaysFleeMons);
    CALL(aIsInArray);
    IF_C goto Flee;

    CALL(aBattleRandom);
    LD_B_A;
    CP_A(50 percent + 1);
    IF_NC goto Stay;

    PUSH_BC;
    LD_A_addr(wTempEnemyMonSpecies);
    LD_DE(1);
    LD_HL(mOftenFleeMons);
    CALL(aIsInArray);
    POP_BC;
    IF_C goto Flee;

    LD_A_B;
    CP_A(10 percent + 1);
    IF_NC goto Stay;

    LD_A_addr(wTempEnemyMonSpecies);
    LD_DE(1);
    LD_HL(mSometimesFleeMons);
    CALL(aIsInArray);
    IF_C goto Flee;


Stay:
    AND_A_A;
    RET;


Flee:
    SCF;
    RET;

// INCLUDE "data/wild/flee_mons.asm"
}

bool TryEnemyFlee_Conv(void){
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_NZ goto Stay;
    if(wram->wBattleMode != WILD_BATTLE)
        return false;

    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_CANT_RUN);
    // IF_NZ goto Stay;
    if(bit_test(wram->wPlayerSubStatus5, SUBSTATUS_CANT_RUN))
        return false;

    // LD_A_addr(wEnemyWrapCount);
    // AND_A_A;
    // IF_NZ goto Stay;
    if(wram->wEnemyWrapCount != 0)
        return false;

    // LD_A_addr(wEnemyMonStatus);
    // AND_A(1 << FRZ | SLP);
    // IF_NZ goto Stay;
    if(wram->wEnemyMon.status[0] & ((1 << FRZ) | SLP))
        return false;

    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_DE(1);
    // LD_HL(mAlwaysFleeMons);
    // CALL(aIsInArray);
    // IF_C goto Flee;
    for(uint32_t i = 0; AlwaysFleeMons[i] != (species_t)-1; ++i) {
        if(AlwaysFleeMons[i] == wram->wTempEnemyMonSpecies)
            return true;
    }

    // CALL(aBattleRandom);
    // LD_B_A;
    uint8_t b = BattleRandom_Conv();
    // CP_A(50 percent + 1);
    // IF_NC goto Stay;
    if(b >= 50 percent + 1)
        return false;

    // PUSH_BC;
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_DE(1);
    // LD_HL(mOftenFleeMons);
    // CALL(aIsInArray);
    // POP_BC;
    // IF_C goto Flee;
    for(uint32_t i = 0; OftenFleeMons[i] != (species_t)-1; ++i) {
        if(OftenFleeMons[i] == wram->wTempEnemyMonSpecies)
            return true;
    }

    // LD_A_B;
    // CP_A(10 percent + 1);
    // IF_NC goto Stay;
    if(b >= 10 percent + 1)
        return false;

    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_DE(1);
    // LD_HL(mSometimesFleeMons);
    // CALL(aIsInArray);
    // IF_C goto Flee;
    for(uint32_t i = 0; SometimesFleeMons[i] != (species_t)-1; ++i) {
        if(SometimesFleeMons[i] == wram->wTempEnemyMonSpecies)
            return true;
    }

// Stay:
    // AND_A_A;
    // RET;
    return false;

// Flee:
    // SCF;
    // RET;

// INCLUDE "data/wild/flee_mons.asm"
}

void CompareMovePriority(void){
//  Compare the priority of the player and enemy's moves.
//  Return carry if the player goes first, or z if they match.

    LD_A_addr(wCurPlayerMove);
    CALL(aGetMovePriority);
    LD_B_A;
    PUSH_BC;
    LD_A_addr(wCurEnemyMove);
    CALL(aGetMovePriority);
    POP_BC;
    CP_A_B;
    RET;

}

//  Compare the priority of the player and enemy's moves.
//  Return carry (1) if the player goes first, or z (0) if they match.
int CompareMovePriority_Conv(void){
    // LD_A_addr(wCurPlayerMove);
    // CALL(aGetMovePriority);
    // LD_B_A;
    // PUSH_BC;
    // LD_A_addr(wCurEnemyMove);
    // CALL(aGetMovePriority);
    // POP_BC;
    // CP_A_B;
    // RET;
    uint8_t a = GetMovePriority_Conv(wram->wCurPlayerMove);
    uint8_t b = GetMovePriority_Conv(wram->wCurEnemyMove);

    if(a == b)
        return 0;
    if(a > b)
        return 1;
    return -1;
}

void GetMovePriority(void){
//  Return the priority (0-3) of move a.

    LD_B_A;

// Vital Throw goes last.
    CP_A(VITAL_THROW);
    LD_A(0);
    RET_Z ;

    CALL(aGetMoveEffect);
    LD_HL(mMoveEffectPriorities);

loop:
    LD_A_hli;
    CP_A_B;
    IF_Z goto done;
    INC_HL;
    CP_A(-1);
    IF_NZ goto loop;

    LD_A(BASE_PRIORITY);
    RET;


done:
    LD_A_hl;
    RET;

// INCLUDE "data/moves/effects_priorities.asm"

    return GetMoveEffect();
}

uint8_t GetMovePriority_Conv(move_t a){
//  Return the priority (0-3) of move a.

    // LD_B_A;

// Vital Throw goes last.
    // CP_A(VITAL_THROW);
    // LD_A(0);
    // RET_Z ;
    if(a == VITAL_THROW)
        return 0;

    // CALL(aGetMoveEffect);
    // LD_HL(mMoveEffectPriorities);
    uint8_t effect = GetMoveEffect_Conv(a);

    for(int i = 0; MoveEffectPriorities[i] != 0xff; i += 2) {
    // loop:
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto done;
        if(MoveEffectPriorities[i] == effect) {
            return MoveEffectPriorities[i+1];
        }
        // INC_HL;
        // CP_A(-1);
        // IF_NZ goto loop;
    }

    // LD_A(BASE_PRIORITY);
    // RET;
    return BASE_PRIORITY;

// done:
    // LD_A_hl;
    // RET;

// INCLUDE "data/moves/effects_priorities.asm"
}

void GetMoveEffect(void){
    LD_A_B;
    DEC_A;
    LD_HL(mMoves + MOVE_EFFECT);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    LD_B_A;
    RET;

}

uint8_t GetMoveEffect_Conv(move_t b){
    if(b == 0)
        return EFFECT_SPLASH;
    // LD_A_B;
    // DEC_A;
    // LD_HL(mMoves + MOVE_EFFECT);
    // LD_BC(MOVE_LENGTH);
    // CALL(aAddNTimes);
    // LD_A(BANK(aMoves));
    // CALL(aGetFarByte);
    // LD_B_A;
    // RET;
    return Moves[b-1].effect;
}

void Battle_EnemyFirst(void){
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // CALL(aTryEnemyFlee);
    // JP_C (mWildFled_EnemyFled_LinkBattleCanceled);
    if(TryEnemyFlee_Conv())
        return WildFled_EnemyFled_LinkBattleCanceled();
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // LD_A(0x1);
    // LD_addr_A(wEnemyGoesFirst);
    wram->wEnemyGoesFirst = 0x1;
    // CALLFAR(aAI_SwitchOrTryItem);
    // IF_C goto switch_item;
    if(!AI_SwitchOrTryItem()){
        // CALL(aEnemyTurn_EndOpponentProtectEndureDestinyBond);
        EnemyTurn_EndOpponentProtectEndureDestinyBond();
        // CALL(aCheckMobileBattleError);
        // RET_C ;
        if(CheckMobileBattleError_Conv())
            return;
        // LD_A_addr(wForcedSwitch);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wForcedSwitch)
            return;
        // CALL(aHasPlayerFainted);
        // JP_Z (mHandlePlayerMonFaint);
        if(HasPlayerFainted_Conv())
            return HandlePlayerMonFaint();
        // CALL(aHasEnemyFainted);
        // JP_Z (mHandleEnemyMonFaint);
        if(HasEnemyFainted_Conv())
            return HandleEnemyMonFaint();
    }

// switch_item:
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // CALL(aResidualDamage);
    // JP_Z (mHandleEnemyMonFaint);
    if(ResidualDamage())
        return HandleEnemyMonFaint();
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds_Conv();
    // CALL(aPlayerTurn_EndOpponentProtectEndureDestinyBond);
    PlayerTurn_EndOpponentProtectEndureDestinyBond();
    // CALL(aCheckMobileBattleError);
    // RET_C ;
    if(CheckMobileBattleError_Conv())
        return;
    // LD_A_addr(wForcedSwitch);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wForcedSwitch)
        return;
    // CALL(aHasEnemyFainted);
    // JP_Z (mHandleEnemyMonFaint);
    if(HasEnemyFainted_Conv())
        return HandleEnemyMonFaint();
    // CALL(aHasPlayerFainted);
    // JP_Z (mHandlePlayerMonFaint);
    if(HasPlayerFainted_Conv())
        return HandlePlayerMonFaint();
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // CALL(aResidualDamage);
    // JP_Z (mHandlePlayerMonFaint);
    if(ResidualDamage())
        return HandlePlayerMonFaint();
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds_Conv();
    // XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEMOVE;
    // RET;
}

void Battle_PlayerFirst(void){
    // XOR_A_A;
    // LD_addr_A(wEnemyGoesFirst);
    wram->wEnemyGoesFirst = FALSE;
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // CALLFAR(aAI_SwitchOrTryItem);
    // PUSH_AF;
    bool switchedOrItem = AI_SwitchOrTryItem();
    // CALL(aPlayerTurn_EndOpponentProtectEndureDestinyBond);
    PlayerTurn_EndOpponentProtectEndureDestinyBond();
    // POP_BC;
    // LD_A_addr(wForcedSwitch);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wForcedSwitch)
        return;
    // CALL(aCheckMobileBattleError);
    // RET_C ;
    if(CheckMobileBattleError_Conv())
        return;
    // CALL(aHasEnemyFainted);
    // JP_Z (mHandleEnemyMonFaint);
    if(HasEnemyFainted_Conv())
        return HandleEnemyMonFaint();
    // CALL(aHasPlayerFainted);
    // JP_Z (mHandlePlayerMonFaint);
    if(HasPlayerFainted_Conv())
        return HandlePlayerMonFaint();
    // PUSH_BC;
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // CALL(aResidualDamage);
    // POP_BC;
    // JP_Z (mHandlePlayerMonFaint);
    if(ResidualDamage())
        return HandlePlayerMonFaint();
    // PUSH_BC;
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds_Conv();
    // POP_AF;
    // IF_C goto switched_or_used_item;
    if(!switchedOrItem){
        // CALL(aLoadTilemapToTempTilemap);
        // CALL(aTryEnemyFlee);
        // JP_C (mWildFled_EnemyFled_LinkBattleCanceled);
        if(TryEnemyFlee_Conv())
            return WildFled_EnemyFled_LinkBattleCanceled();
        // CALL(aEnemyTurn_EndOpponentProtectEndureDestinyBond);
        EnemyTurn_EndOpponentProtectEndureDestinyBond();
        // CALL(aCheckMobileBattleError);
        // RET_C ;
        if(CheckMobileBattleError_Conv())
            return;
        // LD_A_addr(wForcedSwitch);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wForcedSwitch)
            return;
        // CALL(aHasPlayerFainted);
        // JP_Z (mHandlePlayerMonFaint);
        if(HasPlayerFainted_Conv())
            return HandlePlayerMonFaint();
        // CALL(aHasEnemyFainted);
        // JP_Z (mHandleEnemyMonFaint);
        if(HasEnemyFainted_Conv())
            return HandleEnemyMonFaint();
    }

// switched_or_used_item:
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // CALL(aResidualDamage);
    // JP_Z (mHandleEnemyMonFaint);
    if(ResidualDamage())
        return HandleEnemyMonFaint();
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds_Conv();
    // XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEMOVE;
    // RET;
}

void PlayerTurn_EndOpponentProtectEndureDestinyBond(void){
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // CALL(aEndUserDestinyBond);
    EndUserDestinyBond();
    // CALLFAR(aDoPlayerTurn);
    DoPlayerTurn();
    // JP(mEndOpponentProtectEndureDestinyBond);
    return EndOpponentProtectEndureDestinyBond();
}

void EnemyTurn_EndOpponentProtectEndureDestinyBond(void){
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // CALL(aEndUserDestinyBond);
    EndUserDestinyBond();
    // CALLFAR(aDoEnemyTurn);
    DoEnemyTurn();
    // JP(mEndOpponentProtectEndureDestinyBond);
    return EndOpponentProtectEndureDestinyBond();

}

void EndOpponentProtectEndureDestinyBond(void){
    // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS1_OPP);
    // RES_hl(SUBSTATUS_PROTECT);
    bit_reset(*hl, SUBSTATUS_PROTECT);
    // RES_hl(SUBSTATUS_ENDURE);
    bit_reset(*hl, SUBSTATUS_ENDURE);
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_DESTINY_BOND);
    bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_DESTINY_BOND);
    // RET;
}

void EndUserDestinyBond(void){
    // LD_A(BATTLE_VARS_SUBSTATUS5);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_DESTINY_BOND);
    bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS5), SUBSTATUS_DESTINY_BOND);
    // RET;
}

void HasUserFainted(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    JR_Z (mHasPlayerFainted);
    return HasEnemyFainted();
}

bool HasUserFainted_Conv(void){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // JR_Z (mHasPlayerFainted);
    if(hram->hBattleTurn == 0)
        return HasPlayerFainted_Conv();
    return HasEnemyFainted_Conv();
}

void HasEnemyFainted(void){
    LD_HL(wEnemyMonHP);
    JR(mCheckIfHPIsZero);

}

bool HasEnemyFainted_Conv(void){
    // LD_HL(wEnemyMonHP);
    // JR(mCheckIfHPIsZero);
    return wram->wEnemyMon.hp == 0;
}

void HasPlayerFainted(void){
    LD_HL(wBattleMonHP);

    return CheckIfHPIsZero();
}

bool HasPlayerFainted_Conv(void){
    // LD_HL(wBattleMonHP);
    // return CheckIfHPIsZero();
    return wram->wBattleMon.hp == 0;
}

void CheckIfHPIsZero(void){
    LD_A_hli;
    OR_A_hl;
    RET;

}

//  Return true (z) if the user fainted before
//  or as a result of residual damage.
//  For Sandstorm damage, see HandleWeather.
bool ResidualDamage(void){
    // CALL(aHasUserFainted);
    // RET_Z ;
    if(HasUserFainted_Conv()) {
        return true;
    }

    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVar);
    uint8_t status = GetBattleVar_Conv(BATTLE_VARS_STATUS);
    // AND_A(1 << PSN | 1 << BRN);
    // IF_Z goto did_psn_brn;
    if(status & (1 << PSN | 1 << BRN)) {
        // LD_HL(mHurtByPoisonText);
        // LD_DE(ANIM_PSN);
        // AND_A(1 << BRN);
        // IF_Z goto got_anim;
        const txt_cmd_s* text = (status & (1 << BRN))? HurtByBurnText: HurtByPoisonText;
        uint16_t anim = (status & (1 << BRN))? ANIM_BRN: ANIM_PSN;
        // LD_HL(mHurtByBurnText);
        // LD_DE(ANIM_BRN);

    // got_anim:
        // PUSH_DE;
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(text);
        // POP_DE;

        // XOR_A_A;
        // LD_addr_A(wNumHits);
        wram->wNumHits = 0x0;
        // CALL(aCall_PlayBattleAnim_OnlyIfVisible);
        Call_PlayBattleAnim_OnlyIfVisible_Conv(anim);
        // CALL(aGetEighthMaxHP);
        uint16_t amount = GetEighthMaxHP_Conv();
        // LD_DE(wPlayerToxicCount);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto check_toxic;
        // LD_DE(wEnemyToxicCount);
        uint8_t* toxicCount = (hram->hBattleTurn == 0)? &wram->wPlayerToxicCount: &wram->wEnemyToxicCount;

    // check_toxic:
        // LD_A(BATTLE_VARS_SUBSTATUS5);
        // CALL(aGetBattleVar);
        // BIT_A(SUBSTATUS_TOXIC);
        // IF_Z goto did_toxic;
        if(bit_test(GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS5), SUBSTATUS_TOXIC)){
            // CALL(aGetSixteenthMaxHP);
            // LD_A_de;
            // INC_A;
            // LD_de_A;
            uint8_t count = ++*toxicCount;
            // LD_HL(0);

        // add:
            // ADD_HL_BC;
            // DEC_A;
            // IF_NZ goto add;
            // LD_B_H;
            // LD_C_L;
            amount = GetSixteenthMaxHP_Conv() * count;
        }

    // did_toxic:
        // CALL(aSubtractHPFromUser);
        SubtractHPFromUser_Conv(amount);
    }

// did_psn_brn:
    // CALL(aHasUserFainted);
    // JP_Z (mResidualDamage_fainted);
    if(HasUserFainted_Conv()){
    // fainted:
        // CALL(aRefreshBattleHuds);
        RefreshBattleHuds_Conv();
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);
        // XOR_A_A;
        // RET;
        return true;
    }

    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    // BIT_hl(SUBSTATUS_LEECH_SEED);
    // IF_Z goto not_seeded;
    if(bit_test(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_LEECH_SEED)){
        // CALL(aSwitchTurnCore);
        SwitchTurnCore();
        // XOR_A_A;
        // LD_addr_A(wNumHits);
        wram->wNumHits = 0x0;
        // LD_DE(ANIM_SAP);
        // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
        // CALL(aGetBattleVar);
        // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
        // CALL_Z (aCall_PlayBattleAnim_OnlyIfVisible);
        if((GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS3_OPP) & ((1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND))) == 0)
            Call_PlayBattleAnim_OnlyIfVisible_Conv(ANIM_SAP);
        // CALL(aSwitchTurnCore);
        SwitchTurnCore();

        // CALL(aGetEighthMaxHP);
        uint16_t amount = GetEighthMaxHP_Conv();
        // CALL(aSubtractHPFromUser);
        SubtractHPFromUser_Conv(amount);
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // CALL(aRestoreHP);
        RestoreHP_Conv(amount);
        // LD_HL(mLeechSeedSapsText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(LeechSeedSapsText);
    }

// not_seeded:
    // CALL(aHasUserFainted);
    // IF_Z goto fainted;
    if(HasUserFainted_Conv()){
    // fainted:
        // CALL(aRefreshBattleHuds);
        RefreshBattleHuds_Conv();
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);
        // XOR_A_A;
        // RET;
        return true;
    }

    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVarAddr);
    // BIT_hl(SUBSTATUS_NIGHTMARE);
    // IF_Z goto not_nightmare;
    if(bit_test(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_NIGHTMARE)){
        // XOR_A_A;
        // LD_addr_A(wNumHits);
        wram->wNumHits = 0x0;
        // LD_DE(ANIM_IN_NIGHTMARE);
        // CALL(aCall_PlayBattleAnim_OnlyIfVisible);
        Call_PlayBattleAnim_OnlyIfVisible_Conv(ANIM_IN_NIGHTMARE);
        // CALL(aGetQuarterMaxHP);
        // CALL(aSubtractHPFromUser);
        SubtractHPFromUser_Conv(GetQuarterMaxHP_Conv());
        // LD_HL(mHasANightmareText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(HasANightmareText);
    }

// not_nightmare:
    // CALL(aHasUserFainted);
    // IF_Z goto fainted;
    if(HasUserFainted_Conv()){
    // fainted:
        // CALL(aRefreshBattleHuds);
        RefreshBattleHuds_Conv();
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);
        // XOR_A_A;
        // RET;
        return true;
    }

    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVarAddr);
    // BIT_hl(SUBSTATUS_CURSE);
    // IF_Z goto not_cursed;
    if(bit_test(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_CURSE)){
        PEEK("cursed");
        // XOR_A_A;
        // LD_addr_A(wNumHits);
        wram->wNumHits = 0x0;
        // LD_DE(ANIM_IN_NIGHTMARE);
        // CALL(aCall_PlayBattleAnim_OnlyIfVisible);
        Call_PlayBattleAnim_OnlyIfVisible_Conv(ANIM_IN_NIGHTMARE);
        // CALL(aGetQuarterMaxHP);
        // CALL(aSubtractHPFromUser);
        SubtractHPFromUser_Conv(GetQuarterMaxHP_Conv());
        // LD_HL(mHurtByCurseText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(HurtByCurseText);
    }

// not_cursed:
    // LD_HL(wBattleMonHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto check_fainted;
    // LD_HL(wEnemyMonHP);
    uint16_t hp = (hram->hBattleTurn == 0)? wram->wBattleMon.hp: wram->wEnemyMon.hp;

// check_fainted:
    // LD_A_hli;
    // OR_A_hl;
    // RET_NZ ;

    if(hp == 0){
    // fainted:
        // CALL(aRefreshBattleHuds);
        RefreshBattleHuds_Conv();
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);
        // XOR_A_A;
        // RET;
        return true;
    }
    return false;
}

static void HandlePerishSong_do_it(void){
    // LD_HL(wPlayerPerishCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_count;
    // LD_HL(wEnemyPerishCount);
    uint8_t* hl = (hram->hBattleTurn == 0)? &wram->wPlayerPerishCount: &wram->wEnemyPerishCount;

// got_count:
    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_PERISH);
    // RET_Z ;
    if(!bit_test(GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_PERISH))
        return;
    // DEC_hl;
    (*hl)--;
    // LD_A_hl;
    // LD_addr_A(wTextDecimalByte);
    wram->wTextDecimalByte = *hl;
    // PUSH_AF;
    // LD_HL(mPerishCountText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(PerishCountText);
    // POP_AF;
    // RET_NZ ;
    if(*hl != 0)
        return;
    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_PERISH);
    bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_PERISH);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto kill_enemy;
    if(hram->hBattleTurn == 0) {
        // LD_HL(wBattleMonHP);
        // XOR_A_A;
        // LD_hli_A;
        // LD_hl_A;
        wram->wBattleMon.hp = 0;
        // LD_HL(wPartyMon1HP);
        // LD_A_addr(wCurBattleMon);
        // CALL(aGetPartyLocation);
        // XOR_A_A;
        // LD_hli_A;
        // LD_hl_A;
        wram->wPartyMon[wram->wCurBattleMon].HP = 0;
        // RET;
        return;
    } 
    else {
    // kill_enemy:
        // LD_HL(wEnemyMonHP);
        // XOR_A_A;
        // LD_hli_A;
        // LD_hl_A;
        wram->wEnemyMon.hp = 0;
        // LD_A_addr(wBattleMode);
        // DEC_A;
        // RET_Z ;
        if(wram->wBattleMode == WILD_BATTLE) {
            // LD_HL(wOTPartyMon1HP);
            // LD_A_addr(wCurOTMon);
            // CALL(aGetPartyLocation);
            // XOR_A_A;
            // LD_hli_A;
            // LD_hl_A;
            wram->wOTPartyMon[wram->wCurOTMon].HP = 0;
            // RET;
        }
        return;
    }
}

void HandlePerishSong(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto EnemyFirst;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK) {
    // EnemyFirst:
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALL(aHandlePerishSong_do_it);
        HandlePerishSong_do_it();
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        return HandlePerishSong_do_it();
    }
    else {
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALL(aHandlePerishSong_do_it);
        HandlePerishSong_do_it();
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // JP(mHandlePerishSong_do_it);
        return HandlePerishSong_do_it();
    }
}

static void HandleWrap_do_it(void){
    // LD_HL(wPlayerWrapCount);
    // LD_DE(wPlayerTrappingMove);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_addrs;
    // LD_HL(wEnemyWrapCount);
    // LD_DE(wEnemyTrappingMove);
    uint8_t* wrapCount = (hram->hBattleTurn == 0)? &wram->wPlayerWrapCount: &wram->wEnemyWrapCount;
    move_t* trappingMove = (hram->hBattleTurn == 0)? &wram->wPlayerTrappingMove: &wram->wEnemyTrappingMove;

// got_addrs:
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(*wrapCount == 0)
        return;

    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // RET_NZ ;
    if(bit_test(GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_SUBSTITUTE))
        return;

    // LD_A_de;
    // LD_addr_A(wNamedObjectIndex);
    // LD_addr_A(wFXAnimID);
    wram->wFXAnimID = *trappingMove;
    // CALL(aGetMoveName);
    GetMoveName_Conv2(*trappingMove);
    // DEC_hl;
    // IF_Z goto release_from_bounds;
    if(--*wrapCount != 0){
        // LD_A(BATTLE_VARS_SUBSTATUS3);
        // CALL(aGetBattleVar);
        // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
        // IF_NZ goto skip_anim;
        if((GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS3) & ((1 << SUBSTATUS_FLYING) | (1 << SUBSTATUS_UNDERGROUND))) == 0) {
            // CALL(aSwitchTurnCore);
            SwitchTurnCore();
            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // LD_addr_A(wFXAnimID + 1);
            wram->wFXAnimID &= 0xff;
            // PREDEF(pPlayBattleAnim);
            PlayBattleAnim();
            // CALL(aSwitchTurnCore);
            SwitchTurnCore();
        }

    // skip_anim:
        // CALL(aGetSixteenthMaxHP);
        // CALL(aSubtractHPFromUser);
        SubtractHPFromUser_Conv(GetSixteenthMaxHP_Conv());
        // LD_HL(mBattleText_UsersHurtByStringBuffer1);
        // goto print_text;
        return StdBattleTextbox_Conv2(BattleText_UsersHurtByStringBuffer1);
    }

// release_from_bounds:
    // LD_HL(mBattleText_UserWasReleasedFromStringBuffer1);
    return StdBattleTextbox_Conv2(BattleText_UserWasReleasedFromStringBuffer1);

// print_text:
    // JP(mStdBattleTextbox);
}

void HandleWrap(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto EnemyFirst;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK){
    // EnemyFirst:
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALL(aHandleWrap_do_it);
        HandleWrap_do_it();
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        return HandleWrap_do_it();
    }
    else {
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALL(aHandleWrap_do_it);
        HandleWrap_do_it();
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // JP(mHandleWrap_do_it);
        return HandleWrap_do_it();
    }
}

void SwitchTurnCore(void){
    // LDH_A_addr(hBattleTurn);
    // XOR_A(1);
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn ^= 1;
    // RET;
}

static void HandleLeftovers_do_it(void) {
    item_t item;
    // CALLFAR(aGetUserItem);
    // LD_A_hl;
    uint16_t effect = GetUserItem_Conv(&item);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    GetItemName_Conv2(item);
    // LD_A_B;
    // CP_A(HELD_LEFTOVERS);
    // RET_NZ ;
    if(HIGH(effect) != HELD_LEFTOVERS)
        return;

    // LD_HL(wBattleMonHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_hp;
    // LD_HL(wEnemyMonHP);


// got_hp:
    uint16_t hp = ReverseEndian16((hram->hBattleTurn == 0)? wram->wBattleMon.hp: wram->wEnemyMon.hp);
    uint16_t maxHP = ReverseEndian16((hram->hBattleTurn == 0)? wram->wBattleMon.maxHP: wram->wEnemyMon.maxHP);
//  Don't restore if we're already at max HP
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // CP_A_B;
    // IF_NZ goto restore;
    // LD_A_hl;
    // CP_A_C;
    // RET_Z ;
    if(hp == maxHP)
        return;

// restore:
    // CALL(aGetSixteenthMaxHP);
    hp = GetSixteenthMaxHP_Conv();
    // CALL(aSwitchTurnCore);
    SwitchTurnCore();
    // CALL(aRestoreHP);
    RestoreHP_Conv(hp);
    // LD_HL(mBattleText_TargetRecoveredWithItem);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BattleText_TargetRecoveredWithItem);
}

void HandleLeftovers(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto DoEnemyFirst;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK) {
    // DoEnemyFirst:
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALL(aHandleLeftovers_do_it);
        HandleLeftovers_do_it();
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        return HandleLeftovers_do_it();
    }
    else {
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALL(aHandleLeftovers_do_it);
        HandleLeftovers_do_it();
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // JP(mHandleLeftovers_do_it);
        return HandleLeftovers_do_it();
    }
}

static void HandleMysteryberry_do_it(void){
    item_t userItem;
    // CALLFAR(aGetUserItem);
    uint16_t itemEffect = GetUserItem_Conv(&userItem);
    // LD_A_B;
    // CP_A(HELD_RESTORE_PP);
    // IF_NZ goto quit;
    if(HIGH(itemEffect) != HELD_RESTORE_PP)
        return;
    // LD_HL(wPartyMon1PP);
    // LD_A_addr(wCurBattleMon);
    // CALL(aGetPartyLocation);
    // LD_D_H;
    // LD_E_L;
    uint8_t* pp;
    move_t* moves;
    if(hram->hBattleTurn == 0) {
        // LD_HL(wPartyMon1Moves);
        pp = wram->wPartyMon[wram->wCurBattleMon].mon.PP;
        moves = wram->wPartyMon[wram->wCurBattleMon].mon.moves;
        // LD_A_addr(wCurBattleMon);
        // CALL(aGetPartyLocation);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto wild;
    }
    else if(wram->wBattleMode == WILD_BATTLE){
        // LD_DE(wWildMonPP);
        // LD_HL(wWildMonMoves);
        pp = wram->wWildMonPP;
        moves = wram->wWildMonMoves;
        // LD_A_addr(wBattleMode);
        // DEC_A;
        // IF_Z goto wild;
    }
    else {
        // LD_HL(wOTPartyMon1PP);
        // LD_A_addr(wCurOTMon);
        // CALL(aGetPartyLocation);
        // LD_D_H;
        // LD_E_L;
        // LD_HL(wOTPartyMon1Moves);
        // LD_A_addr(wCurOTMon);
        // CALL(aGetPartyLocation);
        pp = wram->wOTPartyMon[wram->wCurBattleMon].mon.PP;
        moves = wram->wOTPartyMon[wram->wCurBattleMon].mon.moves;
    }

// wild:
    // LD_C(0x0);
    uint8_t c = 0x0;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto quit;
        if(moves[c] == NO_MOVE)
            break;
        // LD_A_de;
        // AND_A(PP_MASK);
        // IF_Z goto restore;
        if((pp[c] & PP_MASK) == 0) {
        // restore:
        // lousy hack
            // LD_A_hl;
            // CP_A(SKETCH);
            // LD_B(1);
            // IF_Z goto sketch;
            // LD_B(5);
            uint8_t b = (moves[c] == SKETCH)? 1: 5;

        // sketch:
            // LD_A_de;
            // ADD_A_B;
            // LD_de_A;
            pp[c] += b;
            // PUSH_BC;
            // PUSH_BC;
            // LD_A_hl;
            // LD_addr_A(wTempByteValue);
            // LD_DE(wBattleMonMoves - 1);
            // LD_HL(wBattleMonPP);
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_Z goto player_pp;
            // LD_DE(wEnemyMonMoves - 1);
            // LD_HL(wEnemyMonPP);
            uint8_t* pp2;
            move_t* moves2;
            if(hram->hBattleTurn == 0){
                moves2 = wram->wBattleMon.moves;
                pp2 = wram->wBattleMon.pp;
            }
            else {
                moves2 = wram->wEnemyMon.moves;
                pp2 = wram->wEnemyMon.pp;
            }

        // player_pp:
            // INC_DE;
            // POP_BC;
            // LD_B(0);
            // ADD_HL_BC;
            // PUSH_HL;
            // LD_H_D;
            // LD_L_E;
            // ADD_HL_BC;
            // POP_DE;
            // POP_BC;

            // LD_A_addr(wTempByteValue);
            // CP_A_hl;
            // IF_NZ goto skip_checks;
            if(moves[c] == moves2[c]){
                // LDH_A_addr(hBattleTurn);
                // AND_A_A;
                // LD_A_addr(wPlayerSubStatus5);
                // IF_Z goto check_transform;
                // LD_A_addr(wEnemySubStatus5);
                uint8_t ss5 = (hram->hBattleTurn == 0)? wram->wPlayerSubStatus5: wram->wEnemySubStatus5;

            // check_transform:
                // BIT_A(SUBSTATUS_TRANSFORMED);
                // IF_NZ goto skip_checks;
                if(!bit_test(ss5, SUBSTATUS_TRANSFORMED)){
                    // LD_A_de;
                    // ADD_A_B;
                    // LD_de_A;
                    pp2[c] += b;
                }
            }

        // skip_checks:
            // CALLFAR(aGetUserItem);
            item_t* userItem = (hram->hBattleTurn == 0)? &wram->wBattleMon.item: &wram->wEnemyMon.item;
            // LD_A_hl;
            // LD_addr_A(wNamedObjectIndex);
            item_t temp = *userItem;
            // XOR_A_A;
            // LD_hl_A;
            *userItem = NO_ITEM;
            // CALL(aGetPartymonItem);
            item_t* partyItem = (hram->hBattleTurn == 0)? &wram->wPartyMon[wram->wCurBattleMon].mon.item: &wram->wOTPartyMon[wram->wCurOTMon].mon.item;
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_Z goto consume_item;
            // LD_A_addr(wBattleMode);
            // DEC_A;
            // IF_Z goto skip_consumption;
            if(hram->hBattleTurn == 0 || wram->wBattleMode != WILD_BATTLE){
                // CALL(aGetOTPartymonItem);

            // consume_item:
                // XOR_A_A;
                // LD_hl_A;
                *partyItem = NO_ITEM;
            }

        // skip_consumption:
            // CALL(aGetItemName);
            GetItemName_Conv2(temp);
            // CALL(aSwitchTurnCore);
            SwitchTurnCore();
            // CALL(aItemRecoveryAnim);
            ItemRecoveryAnim();
            // CALL(aSwitchTurnCore);
            SwitchTurnCore();
            // LD_HL(mBattleText_UserRecoveredPPUsing);
            // JP(mStdBattleTextbox);
            return StdBattleTextbox_Conv2(BattleText_UserRecoveredPPUsing);
        }
        // INC_HL;
        // INC_DE;
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_MOVES);
        // IF_NZ goto loop;
    } while(++c != NUM_MOVES);

// quit:
    // RET;
    return;
}

void HandleMysteryberry(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto DoEnemyFirst;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK){
    // DoEnemyFirst:
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALL(aHandleMysteryberry_do_it);
        HandleMysteryberry_do_it();
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        return HandleMysteryberry_do_it();
    }
    else {
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALL(aHandleMysteryberry_do_it);
        HandleMysteryberry_do_it();
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // JP(mHandleMysteryberry_do_it);
        return HandleMysteryberry_do_it();
    }
}

static void HandleFutureSight_do_it(void){
    // LD_HL(wPlayerFutureSightCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto okay;
    // LD_HL(wEnemyFutureSightCount);
    uint8_t* hl = (hram->hBattleTurn == 0)? &wram->wPlayerFutureSightCount: &wram->wEnemyFutureSightCount;

// okay:
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(*hl == 0)
        return;
    // DEC_A;
    // LD_hl_A;
    // CP_A(0x1);
    // RET_NZ ;
    if(--*hl != 0x1)
        return;

    // LD_HL(mBattleText_TargetWasHitByFutureSight);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_TargetWasHitByFutureSight);

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVarAddr);
    // PUSH_AF;
    move_t move = *GetBattleVarAddr_Conv(BATTLE_VARS_MOVE);
    // LD_A(FUTURE_SIGHT);
    // LD_hl_A;
    *GetBattleVarAddr_Conv(BATTLE_VARS_MOVE) = FUTURE_SIGHT;

    // CALLFAR(aUpdateMoveData);
    UpdateMoveData();
    // XOR_A_A;
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = FALSE;
    // LD_addr_A(wAlreadyDisobeyed);
    wram->wAlreadyDisobeyed = FALSE;
    // LD_A(EFFECTIVE);
    // LD_addr_A(wTypeModifier);
    wram->wTypeModifier = EFFECTIVE;
    // CALLFAR(aDoMove);
    DoMove();
    // XOR_A_A;
    // LD_addr_A(wCurDamage);
    // LD_addr_A(wCurDamage + 1);
    wram->wCurDamage = 0;

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVarAddr);
    // POP_AF;
    // LD_hl_A;
    *GetBattleVarAddr_Conv(BATTLE_VARS_MOVE) = move;

    // CALL(aUpdateBattleMonInParty);
    UpdateBattleMonInParty_Conv();
    // JP(mUpdateEnemyMonInParty);
    return UpdateEnemyMonInParty_Conv();
}

void HandleFutureSight(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto enemy_first;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK) {
    // enemy_first:
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALL(aHandleFutureSight_do_it);
        HandleFutureSight_do_it();
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        return HandleFutureSight_do_it();
    }
    else {
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALL(aHandleFutureSight_do_it);
        HandleFutureSight_do_it();
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // JP(mHandleFutureSight_do_it);
        return HandleFutureSight_do_it();
    }
}

static void HandleDefrost_do_player_turn(void){
    // LD_A_addr(wBattleMonStatus);
    // BIT_A(FRZ);
    // RET_Z ;
    if(!bit_test(wram->wBattleMon.status[0], FRZ))
        return;

    // LD_A_addr(wPlayerJustGotFrozen);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wPlayerJustGotFrozen)
        return;

    // CALL(aBattleRandom);
    // CP_A(10 percent);
    // RET_NC ;
    if(BattleRandom_Conv() >= 10 percent)
        return;
    // XOR_A_A;
    // LD_addr_A(wBattleMonStatus);
    wram->wBattleMon.status[0] = 0;
    // LD_A_addr(wCurBattleMon);
    // LD_HL(wPartyMon1Status);
    // CALL(aGetPartyLocation);
    // LD_hl(0);
    wram->wPartyMon[wram->wCurBattleMon].status = 0;
    // CALL(aUpdateBattleHuds);
    UpdateBattleHuds();
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // LD_HL(mDefrostedOpponentText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(DefrostedOpponentText);
}

static void HandleDefrost_do_enemy_turn(void){
    // LD_A_addr(wEnemyMonStatus);
    // BIT_A(FRZ);
    // RET_Z ;
    // LD_A_addr(wEnemyJustGotFrozen);
    // AND_A_A;
    // RET_NZ ;
    if(!bit_test(wram->wEnemyMon.status[0], FRZ) || wram->wEnemyJustGotFrozen)
        return;
    // CALL(aBattleRandom);
    // CP_A(10 percent);
    // RET_NC ;
    if(BattleRandom_Conv() >= 10 percent)
        return;
    // XOR_A_A;
    // LD_addr_A(wEnemyMonStatus);
    wram->wEnemyMon.status[0] = 0;

    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_Z goto wild;
    if(wram->wBattleMode != WILD_BATTLE) {
        // LD_A_addr(wCurOTMon);
        // LD_HL(wOTPartyMon1Status);
        // CALL(aGetPartyLocation);
        // LD_hl(0);
        wram->wOTPartyMon[wram->wCurOTMon].status = 0;
    }
// wild:
    // CALL(aUpdateBattleHuds);
    UpdateBattleHuds();
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // LD_HL(mDefrostedOpponentText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(DefrostedOpponentText);
}

void HandleDefrost(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto enemy_first;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK) {
    // enemy_first:
        // CALL(aHandleDefrost_do_enemy_turn);
        HandleDefrost_do_enemy_turn();
        HandleDefrost_do_player_turn();
    }
    else {
        // CALL(aHandleDefrost_do_player_turn);
        HandleDefrost_do_player_turn();
        // goto do_enemy_turn;
        HandleDefrost_do_enemy_turn();
    }
}

static void HandleSafeguard_print(uint8_t a){
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = a;
    // LD_HL(mBattleText_SafeguardFaded);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BattleText_SafeguardFaded);
}

static void HandleSafeguard_CheckPlayer(void){
    // LD_A_addr(wPlayerScreens);
    // BIT_A(SCREENS_SAFEGUARD);
    // RET_Z ;
    if(!bit_test(wram->wPlayerScreens, SCREENS_SAFEGUARD))
        return;
    // LD_HL(wPlayerSafeguardCount);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wPlayerSafeguardCount != 0)
        return;
    // RES_A(SCREENS_SAFEGUARD);
    // LD_addr_A(wPlayerScreens);
    bit_reset(wram->wPlayerScreens, SCREENS_SAFEGUARD);
    // XOR_A_A;
    // goto print;
    return HandleSafeguard_print(0x0);
}

static void HandleSafeguard_CheckEnemy(void){
    // LD_A_addr(wEnemyScreens);
    // BIT_A(SCREENS_SAFEGUARD);
    // RET_Z ;
    if(!bit_test(wram->wEnemyScreens, SCREENS_SAFEGUARD))
        return;
    // LD_HL(wEnemySafeguardCount);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wEnemySafeguardCount != 0)
        return;
    // RES_A(SCREENS_SAFEGUARD);
    // LD_addr_A(wEnemyScreens);
    bit_reset(wram->wEnemyScreens, SCREENS_SAFEGUARD);
    // LD_A(0x1);
    return HandleSafeguard_print(0x1);
}

void HandleSafeguard(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto player1;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK){
    // player1:
        // CALL(aHandleSafeguard_CheckEnemy);
        HandleSafeguard_CheckEnemy();
        return HandleSafeguard_CheckPlayer();
    }
    else {
        // CALL(aHandleSafeguard_CheckPlayer);
        HandleSafeguard_CheckPlayer();
        // goto CheckEnemy;
        return HandleSafeguard_CheckEnemy();
    }
}

static void HandleScreens_Copy(uint8_t* de){
    // LD_HL(wStringBuffer1);
    // JP(mCopyName2);
    CopyName2_Conv2(wram->wStringBuffer1, de);
}

static void HandleScreens_ReflectTick(uint8_t* hl, uint8_t* de){
    // INC_DE;
    // LD_A_de;
    // DEC_A;
    // LD_de_A;
    // RET_NZ ;
    if(--de[1] != 0)
        return;
    // RES_hl(SCREENS_REFLECT);
    bit_reset(*hl, SCREENS_REFLECT);
    // LD_HL(mBattleText_MonsReflectFaded);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BattleText_MonsReflectFaded);
}

static void HandleScreens_LightScreenTick(uint8_t* hl, uint8_t* de){
    // LD_A_de;
    // DEC_A;
    // LD_de_A;
    // RET_NZ ;
    if(--*de != 0)
        return;
    // RES_hl(SCREENS_LIGHT_SCREEN);
    bit_reset(*hl, SCREENS_LIGHT_SCREEN);
    // PUSH_HL;
    // PUSH_DE;
    // LD_HL(mBattleText_MonsLightScreenFell);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_MonsLightScreenFell);
    // POP_DE;
    // POP_HL;
    // RET;
    return;
}

static void HandleScreens_TickScreens(uint8_t* hl, uint8_t* de){
    // BIT_hl(SCREENS_LIGHT_SCREEN);
    // CALL_NZ (aHandleScreens_LightScreenTick);
    if(bit_test(*hl, SCREENS_LIGHT_SCREEN))
        return HandleScreens_LightScreenTick(hl, de);
    // BIT_hl(SCREENS_REFLECT);
    // CALL_NZ (aHandleScreens_ReflectTick);
    if(bit_test(*hl, SCREENS_REFLECT))
        return HandleScreens_ReflectTick(hl, de);
    // RET;
}

static void HandleScreens_CheckPlayer(void){
    static const char Your[] = "Your@";
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // LD_DE(mHandleScreens_Your);
    // CALL(aHandleScreens_Copy);
    HandleScreens_Copy(U82C(Your));
    // LD_HL(wPlayerScreens);
    // LD_DE(wPlayerLightScreenCount);
    // goto TickScreens;
    return HandleScreens_TickScreens(&wram->wPlayerScreens, &wram->wPlayerLightScreenCount);
}

static void HandleScreens_CheckEnemy(void){
    static const char Enemy[] = "Enemy@";
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // LD_DE(mHandleScreens_Enemy);
    // CALL(aHandleScreens_Copy);
    HandleScreens_Copy(U82C(Enemy));
    // LD_HL(wEnemyScreens);
    // LD_DE(wEnemyLightScreenCount);
    return HandleScreens_TickScreens(&wram->wEnemyScreens, &wram->wEnemyLightScreenCount);
}

void HandleScreens(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto Both;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK){
    // Both:
        // CALL(aHandleScreens_CheckEnemy);
        HandleScreens_CheckEnemy();
        return HandleScreens_CheckPlayer();
    }
    else {
        // CALL(aHandleScreens_CheckPlayer);
        HandleScreens_CheckPlayer();
        // goto CheckEnemy;
        return HandleScreens_CheckEnemy();
    }
}

static void HandleWeather_SandstormDamage(void) {
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_UNDERGROUND);
    // RET_NZ ;
    if(bit_test(GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS3), SUBSTATUS_UNDERGROUND))
        return;

    // LD_HL(wBattleMonType1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyMonType1);
    uint8_t* types = (hram->hBattleTurn == 0)? wram->wBattleMon.types: wram->wEnemyMon.types;

// ok:
    // LD_A_hli;
    // CP_A(ROCK);
    // RET_Z ;
    // CP_A(GROUND);
    // RET_Z ;
    // CP_A(STEEL);
    // RET_Z ;
    if(types[0] == ROCK || types[0] == GROUND || types[0] == STEEL)
        return;

    // LD_A_hl;
    // CP_A(ROCK);
    // RET_Z ;
    // CP_A(GROUND);
    // RET_Z ;
    // CP_A(STEEL);
    // RET_Z ;
    if(types[1] == ROCK || types[1] == GROUND || types[1] == STEEL)
        return;

    // CALL(aSwitchTurnCore);
    SwitchTurnCore();
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_DE(ANIM_IN_SANDSTORM);
    // CALL(aCall_PlayBattleAnim);
    Call_PlayBattleAnim_Conv(ANIM_IN_SANDSTORM);
    // CALL(aSwitchTurnCore);
    SwitchTurnCore();
    // CALL(aGetEighthMaxHP);
    // CALL(aSubtractHPFromUser);
    SubtractHPFromUser_Conv(GetEighthMaxHP_Conv());

    // LD_HL(mSandstormHitsText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(SandstormHitsText);
}

void HandleWeather(void){
    static const struct TextCmd* WeatherMessages[] = {
    //  entries correspond to WEATHER_* constants
        [WEATHER_RAIN-1]        = BattleText_RainContinuesToFall,
        [WEATHER_SUN-1]         = BattleText_TheSunlightIsStrong,
        [WEATHER_SANDSTORM-1]   = BattleText_TheSandstormRages,
    };

    static const struct TextCmd* WeatherEndedMessages[] = {
    //  entries correspond to WEATHER_* constants
        [WEATHER_RAIN-1]        = BattleText_TheRainStopped,
        [WEATHER_SUN-1]         = BattleText_TheSunlightFaded,
        [WEATHER_SANDSTORM-1]   = BattleText_TheSandstormSubsided,
    };

    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_NONE);
    // RET_Z ;
    if(wram->wBattleWeather == WEATHER_NONE)
        return;

    // LD_HL(wWeatherCount);
    // DEC_hl;
    // IF_Z goto ended;
    if(--wram->wWeatherCount == 0) {
    // ended:
        // LD_HL(mHandleWeather_WeatherEndedMessages);
        // CALL(aHandleWeather_PrintWeatherMessage);
    // PrintWeatherMessage:
        // LD_A_addr(wBattleWeather);
        // DEC_A;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // JP(mStdBattleTextbox);
        StdBattleTextbox_Conv2(WeatherEndedMessages[wram->wBattleWeather - 1]);
        // XOR_A_A;
        // LD_addr_A(wBattleWeather);
        wram->wBattleWeather = 0;
        // RET;
        return;
    }

    // LD_HL(mHandleWeather_WeatherMessages);
    // CALL(aHandleWeather_PrintWeatherMessage);
    StdBattleTextbox_Conv2(WeatherMessages[wram->wBattleWeather - 1]);

    // LD_A_addr(wBattleWeather);
    // CP_A(WEATHER_SANDSTORM);
    // RET_NZ ;
    if(wram->wBattleWeather == WEATHER_SANDSTORM) { // Do sandstorm damage.
        // LDH_A_addr(hSerialConnectionStatus);
        // CP_A(USING_EXTERNAL_CLOCK);
        // IF_Z goto enemy_first;
        if(hram->hSerialConnectionStatus != USING_EXTERNAL_CLOCK) {
        //  player first
            // CALL(aSetPlayerTurn);
            SetPlayerTurn_Conv();
            // CALL(aHandleWeather_SandstormDamage);
            HandleWeather_SandstormDamage();
            // CALL(aSetEnemyTurn);
            SetEnemyTurn_Conv();
            // goto SandstormDamage;
            return HandleWeather_SandstormDamage();
        }
        else {
        // enemy_first:
            // CALL(aSetEnemyTurn);
            SetEnemyTurn_Conv();
            // CALL(aHandleWeather_SandstormDamage);
            HandleWeather_SandstormDamage();
            // CALL(aSetPlayerTurn);
            SetPlayerTurn_Conv();
            return HandleWeather_SandstormDamage();
        }
    }
}

void SubtractHPFromTarget(void){
    CALL(aSubtractHP);
    JP(mUpdateHPBar);

}

void SubtractHPFromUser(void){
//  Subtract HP from mon
    CALL(aSubtractHP);
    JP(mUpdateHPBarBattleHuds);

}

void SubtractHPFromUser_Conv(uint16_t hp){
//  Subtract HP from mon
    // CALL(aSubtractHP);
    SubtractHP_Conv(hp);
    // JP(mUpdateHPBarBattleHuds);
    return UpdateHPBarBattleHuds();
}

void SubtractHP(void){
    LD_HL(wBattleMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonHP);

ok:
    INC_HL;
    LD_A_hl;
    LD_addr_A(wHPBuffer2);
    SUB_A_C;
    LD_hld_A;
    LD_addr_A(wHPBuffer3);
    LD_A_hl;
    LD_addr_A(wHPBuffer2 + 1);
    SBC_A_B;
    LD_hl_A;
    LD_addr_A(wHPBuffer3 + 1);
    RET_NC ;

    LD_A_addr(wHPBuffer2);
    LD_C_A;
    LD_A_addr(wHPBuffer2 + 1);
    LD_B_A;
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LD_addr_A(wHPBuffer3);
    LD_addr_A(wHPBuffer3 + 1);
    RET;

}

void SubtractHP_Conv(uint16_t bc){
    // LD_HL(wBattleMonHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyMonHP);
    uint16_t* hp = (uint16_t*)((hram->hBattleTurn == 0)? wram_ptr(wBattleMonHP): wram_ptr(wEnemyMonHP));

// ok:
    // INC_HL;
    // LD_A_hl;
    // LD_addr_A(wHPBuffer2);
    wram->wHPBuffer2 = ReverseEndian16(*hp);
    uint32_t temp = wram->wHPBuffer2 - bc;
    // SUB_A_C;
    // LD_hld_A;
    // LD_addr_A(wHPBuffer3);
    // LD_A_hl;
    // LD_addr_A(wHPBuffer2 + 1);
    // SBC_A_B;
    // LD_hl_A;
    // LD_addr_A(wHPBuffer3 + 1);
    wram->wHPBuffer3 = (uint16_t)temp;
    *hp = ReverseEndian16((uint16_t)temp);
    // RET_NC ;
    if(temp & 0xffff0000) {
        // LD_A_addr(wHPBuffer2);
        // LD_C_A;
        // LD_A_addr(wHPBuffer2 + 1);
        // LD_B_A;
        // XOR_A_A;
        // LD_hli_A;
        // LD_hl_A;
        *hp = ReverseEndian16(0);
        // LD_addr_A(wHPBuffer3);
        // LD_addr_A(wHPBuffer3 + 1);
        wram->wHPBuffer3 = ReverseEndian16(0);
    }
    // RET;
}

void GetSixteenthMaxHP(void){
    CALL(aGetQuarterMaxHP);
//  quarter result
    SRL_C;
    SRL_C;
//  at least 1
    LD_A_C;
    AND_A_A;
    IF_NZ goto ok;
    INC_C;

ok:
    RET;

}

uint16_t GetSixteenthMaxHP_Conv(void){
    // CALL(aGetQuarterMaxHP);
    uint16_t hp = GetQuarterMaxHP_Conv();
//  quarter result
    // SRL_C;
    // SRL_C;
    hp >>= 2;
//  at least 1
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto ok;
    // INC_C;
    if(hp == 0)
        hp = 1;

// ok:
    // RET;
    return hp;
}

void GetEighthMaxHP(void){
//  output: bc
    CALL(aGetQuarterMaxHP);
//  assumes nothing can have 1024 or more hp
//  halve result
    SRL_C;
//  at least 1
    LD_A_C;
    AND_A_A;
    IF_NZ goto end;
    INC_C;

end:
    RET;

}

uint16_t GetEighthMaxHP_Conv(void){
//  output: bc
    // CALL(aGetQuarterMaxHP);
    uint16_t hp = GetQuarterMaxHP_Conv();
//  assumes nothing can have 1024 or more hp
//  halve result
    // SRL_C;
    hp >>= 1;
//  at least 1
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto end;
    // INC_C;
    if(hp == 0)
        hp = 1;

// end:
    // RET;
    return hp;
}

void GetQuarterMaxHP(void){
//  output: bc
    CALL(aGetMaxHP);

//  quarter result
    SRL_B;
    RR_C;
    SRL_B;
    RR_C;

//  assumes nothing can have 1024 or more hp
//  at least 1
    LD_A_C;
    AND_A_A;
    IF_NZ goto end;
    INC_C;

end:
    RET;

}

uint16_t GetQuarterMaxHP_Conv(void){
//  output: bc
    // CALL(aGetMaxHP);
    uint16_t hp = GetMaxHP_Conv();

//  quarter result
    // SRL_B;
    // RR_C;
    // SRL_B;
    // RR_C;
    hp >>= 2;

//  assumes nothing can have 1024 or more hp
//  at least 1
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto end;
    // INC_C;
    if(hp == 0)
        hp = 1;

// end:
    // RET;
    return hp;
}

void GetHalfMaxHP(void){
//  output: bc
    CALL(aGetMaxHP);

//  halve result
    SRL_B;
    RR_C;

//  at least 1
    LD_A_C;
    OR_A_B;
    IF_NZ goto end;
    INC_C;

end:
    RET;

}

uint16_t GetHalfMaxHP_Conv(void){
//  output: bc
    // CALL(aGetMaxHP);
    uint16_t hp = GetMaxHP_Conv();

//  halve result
    // SRL_B;
    // RR_C;
    hp >>= 1;

//  at least 1
    // LD_A_C;
    // OR_A_B;
    // IF_NZ goto end;
    // INC_C;
    if(hp == 0)
        hp = 1;

// end:
    // RET;
    return hp;
}

void GetMaxHP(void){
//  output: bc, wHPBuffer1

    LD_HL(wBattleMonMaxHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonMaxHP);

ok:
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_B_A;

    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    LD_C_A;
    RET;

}

uint16_t GetMaxHP_Conv(void){
//  output: bc, wHPBuffer1

    // LD_HL(wBattleMonMaxHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyMonMaxHP);
    uint16_t hp = ReverseEndian16((hram->hBattleTurn == 0)? wram->wBattleMon.maxHP: wram->wEnemyMon.maxHP);

// ok:
    // LD_A_hli;
    // LD_addr_A(wHPBuffer1 + 1);
    // LD_B_A;

    // LD_A_hl;
    // LD_addr_A(wHPBuffer1);
    // LD_C_A;
    wram->wHPBuffer1 = hp;
    // RET;
    return hp;
}

void GetHalfHP(void){
//  //  unreferenced
    LD_HL(wBattleMonHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonHP);

ok:
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_C_A;
    SRL_B;
    RR_C;
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    RET;

}

void CheckUserHasEnoughHP(void){
    LD_HL(wBattleMonHP + 1);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wEnemyMonHP + 1);

ok:
    LD_A_C;
    SUB_A_hl;
    DEC_HL;
    LD_A_B;
    SBC_A_hl;
    RET;

}

// Returns true (c) if the user has enough HP.
bool CheckUserHasEnoughHP_Conv(uint16_t bc){
    // LD_HL(wBattleMonHP + 1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyMonHP + 1);
    uint16_t hp = ReverseEndian16((hram->hBattleTurn == 0)? wram->wBattleMon.hp: wram->wEnemyMon.hp);
// ok:
    // LD_A_C;
    // SUB_A_hl;
    // DEC_HL;
    // LD_A_B;
    // SBC_A_hl;
    // RET;
    return hp >= bc;
}

void RestoreHP(void){
    LD_HL(wEnemyMonMaxHP);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto ok;
    LD_HL(wBattleMonMaxHP);

ok:
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hld;
    LD_addr_A(wHPBuffer1);
    DEC_HL;
    LD_A_hl;
    LD_addr_A(wHPBuffer2);
    ADD_A_C;
    LD_hld_A;
    LD_addr_A(wHPBuffer3);
    LD_A_hl;
    LD_addr_A(wHPBuffer2 + 1);
    ADC_A_B;
    LD_hli_A;
    LD_addr_A(wHPBuffer3 + 1);

    LD_A_addr(wHPBuffer1);
    LD_C_A;
    LD_A_hld;
    SUB_A_C;
    LD_A_addr(wHPBuffer1 + 1);
    LD_B_A;
    LD_A_hl;
    SBC_A_B;
    IF_C goto overflow;
    LD_A_B;
    LD_hli_A;
    LD_addr_A(wHPBuffer3 + 1);
    LD_A_C;
    LD_hl_A;
    LD_addr_A(wHPBuffer3);

overflow:

    CALL(aSwitchTurnCore);
    CALL(aUpdateHPBarBattleHuds);
    JP(mSwitchTurnCore);

}

void RestoreHP_Conv(uint16_t bc){
    // LD_HL(wEnemyMonMaxHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wBattleMonMaxHP);
    uint16_t* maxhp = (uint16_t*)((hram->hBattleTurn == 0)? wram_ptr(wEnemyMonMaxHP): wram_ptr(wBattleMonMaxHP));
    uint16_t*    hp = (uint16_t*)((hram->hBattleTurn == 0)? wram_ptr(wEnemyMonHP): wram_ptr(wBattleMonHP));

ok:
    // LD_A_hli;
    // LD_addr_A(wHPBuffer1 + 1);
    // LD_A_hld;
    // LD_addr_A(wHPBuffer1);
    // DEC_HL;
    wram->wHPBuffer1 = ReverseEndian16(*maxhp);
    // LD_A_hl;
    // LD_addr_A(wHPBuffer2);
    // ADD_A_C;
    // LD_hld_A;
    // LD_addr_A(wHPBuffer3);
    // LD_A_hl;
    // LD_addr_A(wHPBuffer2 + 1);
    // ADC_A_B;
    // LD_hli_A;
    // LD_addr_A(wHPBuffer3 + 1);
    wram->wHPBuffer2 = ReverseEndian16(*hp);

    // LD_A_addr(wHPBuffer1);
    // LD_C_A;
    // LD_A_hld;
    // SUB_A_C;
    // LD_A_addr(wHPBuffer1 + 1);
    // LD_B_A;
    // LD_A_hl;
    // SBC_A_B;
    // IF_C goto overflow;
    if(wram->wHPBuffer2 + bc > wram->wHPBuffer1) {
        wram->wHPBuffer3 = wram->wHPBuffer1;
        *hp = ReverseEndian16(wram->wHPBuffer1);
    }
    else {
        // LD_A_B;
        // LD_hli_A;
        // LD_addr_A(wHPBuffer3 + 1);
        // LD_A_C;
        // LD_hl_A;
        // LD_addr_A(wHPBuffer3);
        wram->wHPBuffer3 = wram->wHPBuffer2 + bc;
        *hp = ReverseEndian16(wram->wHPBuffer2 + bc);
    }

// overflow:

    // CALL(aSwitchTurnCore);
    SwitchTurnCore();
    // CALL(aUpdateHPBarBattleHuds);
    UpdateHPBarBattleHuds();
    // JP(mSwitchTurnCore);
    SwitchTurnCore();
}

void UpdateHPBarBattleHuds(void){
    // CALL(aUpdateHPBar);
    UpdateHPBar();
    // JP(mUpdateBattleHuds);
    return UpdateBattleHuds();

}

void UpdateHPBar(void){
    if(hram->hBattleTurn == 0) {
        // hlcoord(10, 9, wTilemap);
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // LD_A(1);
        AnimateHPBar_Conv(coord(10, 9, wram->wTilemap), 1);
        // IF_Z goto ok;
    }
    else {
        // hlcoord(2, 2, wTilemap);
        // XOR_A_A;
        AnimateHPBar_Conv(coord(2, 2, wram->wTilemap), 0);
    }
// ok:
    // PUSH_BC;
    // LD_addr_A(wWhichHPBar);
    // PREDEF(pAnimateHPBar);
    // POP_BC;
    // RET;
}

void HandleEnemyMonFaint(void){
    PEEK("");
    // CALL(aFaintEnemyPokemon);
    FaintEnemyPokemon();
    // LD_HL(wBattleMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // CALL_Z (aFaintYourPokemon);
    if(wram->wBattleMon.hp == 0)
        FaintYourPokemon();
    // XOR_A_A;
    // LD_addr_A(wWhichMonFaintedFirst);
    wram->wWhichMonFaintedFirst = 0;
    // CALL(aUpdateBattleStateAndExperienceAfterEnemyFaint);
    UpdateBattleStateAndExperienceAfterEnemyFaint();
    // CALL(aCheckPlayerPartyForFitMon);
    // LD_A_D;
    // AND_A_A;
    // JP_Z (mLostBattle);
    if(!CheckPlayerPartyForFitMon_Conv())
        return LostBattle();

    // LD_HL(wBattleMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // CALL_NZ (aUpdatePlayerHUD);
    if(wram->wBattleMon.hp != 0)
        UpdatePlayerHUD();

    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // LD_C(60);
    // CALL(aDelayFrames);
    DelayFrames_Conv(60);

    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_NZ goto trainer;
    if(wram->wBattleMode == WILD_BATTLE) {
        // LD_A(1);
        // LD_addr_A(wBattleEnded);
        wram->wBattleEnded = TRUE;
        // RET;
        return;
    }
    else {
    // trainer:
        // CALL(aCheckEnemyTrainerDefeated);
        // JP_Z (mWinTrainerBattle);
        if(CheckEnemyTrainerDefeated_Conv())
            return WinTrainerBattle();

        // LD_HL(wBattleMonHP);
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto player_mon_not_fainted;
        if(wram->wBattleMon.hp == 0) {
            // CALL(aAskUseNextPokemon);
            // IF_NC goto dont_flee;
            if(AskUseNextPokemon_Conv()) {
                // LD_A(1);
                // LD_addr_A(wBattleEnded);
                wram->wBattleEnded = 1;
                // RET;
                return;
            }
        // dont_flee:
            // CALL(aForcePlayerMonChoice);
            ForcePlayerMonChoice();
            // CALL(aCheckMobileBattleError);
            // JP_C (mWildFled_EnemyFled_LinkBattleCanceled);
            if(CheckMobileBattleError_Conv())
                return WildFled_EnemyFled_LinkBattleCanceled();

            // LD_A(BATTLEPLAYERACTION_USEITEM);
            // LD_addr_A(wBattlePlayerAction);
            wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEITEM;
            // CALL(aHandleEnemySwitch);
            uint8_t a = HandleEnemySwitch_Conv();
            // JP_Z (mWildFled_EnemyFled_LinkBattleCanceled);
            if(a == 0)
                return WildFled_EnemyFled_LinkBattleCanceled();
            // JR(mDoubleSwitch);
            return DoubleSwitch();
        }
        else {
        // player_mon_not_fainted:
            // LD_A(BATTLEPLAYERACTION_USEITEM);
            // LD_addr_A(wBattlePlayerAction);
            wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEITEM;
            // CALL(aHandleEnemySwitch);
            uint8_t a = HandleEnemySwitch_Conv();
            // JP_Z (mWildFled_EnemyFled_LinkBattleCanceled);
            if(a == 0)
                return WildFled_EnemyFled_LinkBattleCanceled();
            // XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
            // LD_addr_A(wBattlePlayerAction);
            wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEMOVE;
            // RET;
            return;
        }
    }
}

void DoubleSwitch(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto player_1;
    if(hram->hSerialConnectionStatus != USING_EXTERNAL_CLOCK) {
        // CALL(aClearSprites);
        ClearSprites_Conv();
        // hlcoord(1, 0, wTilemap);
        // LD_BC((4 << 8) | 10);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(1, 0, wram->wTilemap), 10, 4);
        // CALL(aPlayerPartyMonEntrance);
        PlayerPartyMonEntrance();
        // LD_A(0x1);
        // CALL(aEnemyPartyMonEntrance);
        EnemyPartyMonEntrance_Conv(true);
        // goto done;
    }
    else {
    // player_1:
        // LD_A_addr(wCurPartyMon);
        // PUSH_AF;
        uint8_t cur = wram->wCurPartyMon;
        // LD_A(0x1);
        // CALL(aEnemyPartyMonEntrance);
        EnemyPartyMonEntrance_Conv(true);
        // CALL(aClearSprites);
        ClearSprites_Conv();
        // CALL(aLoadTilemapToTempTilemap);
        LoadTilemapToTempTilemap_Conv();
        // POP_AF;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = cur;
        // CALL(aPlayerPartyMonEntrance);
        PlayerPartyMonEntrance();
    }

// done:
    // XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEMOVE;
    // RET;
}

void UpdateBattleStateAndExperienceAfterEnemyFaint(void){
    // CALL(aUpdateBattleMonInParty);
    UpdateBattleMonInParty_Conv();
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_Z goto wild;
    if(wram->wBattleMode != WILD_BATTLE) {
        // LD_A_addr(wCurOTMon);
        // LD_HL(wOTPartyMon1HP);
        // CALL(aGetPartyLocation);
        struct PartyMon* hl = wram->wOTPartyMon + wram->wCurOTMon;
        // XOR_A_A;
        // LD_hli_A;
        // LD_hl_A;
        hl->HP = 0;
    }

// wild:
    // LD_HL(wPlayerSubStatus3);
    // RES_hl(SUBSTATUS_IN_LOOP);
    bit_reset(wram->wPlayerSubStatus3, SUBSTATUS_IN_LOOP);
    // XOR_A_A;
    // LD_HL(wEnemyDamageTaken);
    // LD_hli_A;
    // LD_hl_A;
    wram->wEnemyDamageTaken = 0;
    // CALL(aNewEnemyMonStatus);
    NewEnemyMonStatus_Conv();
    // CALL(aBreakAttraction);
    BreakAttraction();
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_Z goto wild2;
    if(wram->wBattleMode == WILD_BATTLE) {
    // wild2:
        // CALL(aStopDangerSound);
        StopDangerSound();
        // LD_A(0x1);
        // LD_addr_A(wBattleLowHealthAlarm);
        wram->wBattleLowHealthAlarm = 0x1;
    }
    // goto trainer;

// trainer:
    // LD_HL(wBattleMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // IF_NZ goto player_mon_did_not_faint;
    // LD_A_addr(wWhichMonFaintedFirst);
    // AND_A_A;
    // IF_NZ goto player_mon_did_not_faint;
    if(wram->wBattleMon.hp == 0 && wram->wWhichMonFaintedFirst == 0) {
        // CALL(aUpdateFaintedPlayerMon);
        UpdateFaintedPlayerMon();
    }

// player_mon_did_not_faint:
    // CALL(aCheckPlayerPartyForFitMon);
    // LD_A_D;
    // AND_A_A;
    // RET_Z ;
    if(!CheckPlayerPartyForFitMon_Conv())
        return;
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // CALL_Z (aPlayVictoryMusic);
    if(wram->wBattleMode == WILD_BATTLE)
        PlayVictoryMusic();
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // LD_A_addr(wBattleResult);
    // AND_A(BATTLERESULT_BITMASK);
    // LD_addr_A(wBattleResult);  // WIN
    wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) + WIN;
    // CALL(aIsAnyMonHoldingExpShare);
    uint8_t d = IsAnyMonHoldingExpShare_Conv();
    // IF_Z goto skip_exp;
    if(d) {
        // LD_HL(wEnemyMonBaseStats);
        // LD_B(wEnemyMonEnd - wEnemyMonBaseStats);
        for(uint8_t i = 0; i < lengthof(wram->wEnemyMonBaseStats); ++i) {
        // loop:
            // SRL_hl;
            wram->wEnemyMonBaseStats[i] >>= 1;
            // INC_HL;
            // DEC_B;
            // IF_NZ goto loop;
        }
    }

// skip_exp:
    // LD_HL(wEnemyMonBaseStats);
    // LD_DE(wBackupEnemyMonBaseStats);
    // LD_BC(wEnemyMonEnd - wEnemyMonBaseStats);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wBackupEnemyMonBaseStats, wram->wEnemyMonBaseStats, sizeof(wram->wEnemyMonBaseStats));
    // XOR_A_A;
    // LD_addr_A(wGivingExperienceToExpShareHolders);
    wram->wGivingExperienceToExpShareHolders = FALSE;
    // CALL(aGiveExperiencePoints);
    GiveExperiencePoints();
    // CALL(aIsAnyMonHoldingExpShare);
    // RET_Z ;
    if(!d)
        return;

    // LD_A_addr(wBattleParticipantsNotFainted);
    // PUSH_AF;
    uint8_t notFainted = wram->wBattleParticipantsNotFainted;
    // LD_A_D;
    // LD_addr_A(wBattleParticipantsNotFainted);
    wram->wBattleParticipantsNotFainted = d;
    // LD_HL(wBackupEnemyMonBaseStats);
    // LD_DE(wEnemyMonBaseStats);
    // LD_BC(wEnemyMonEnd - wEnemyMonBaseStats);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wEnemyMonBaseStats, wram->wBackupEnemyMonBaseStats, sizeof(wram->wEnemyMonBaseStats));
    // LD_A(0x1);
    // LD_addr_A(wGivingExperienceToExpShareHolders);
    wram->wGivingExperienceToExpShareHolders = TRUE;
    // CALL(aGiveExperiencePoints);
    GiveExperiencePoints();
    // POP_AF;
    // LD_addr_A(wBattleParticipantsNotFainted);
    wram->wBattleParticipantsNotFainted = notFainted;
    // RET;
}

void IsAnyMonHoldingExpShare(void){
    LD_A_addr(wPartyCount);
    LD_B_A;
    LD_HL(wPartyMon1);
    LD_C(1);
    LD_D(0);

loop:
    PUSH_HL;
    PUSH_BC;
    LD_BC(MON_HP);
    ADD_HL_BC;
    LD_A_hli;
    OR_A_hl;
    POP_BC;
    POP_HL;
    IF_Z goto next;

    PUSH_HL;
    PUSH_BC;
    LD_BC(MON_ITEM);
    ADD_HL_BC;
    POP_BC;
    LD_A_hl;
    POP_HL;

    CP_A(EXP_SHARE);
    IF_NZ goto next;
    LD_A_D;
    OR_A_C;
    LD_D_A;


next:
    SLA_C;
    PUSH_DE;
    LD_DE(PARTYMON_STRUCT_LENGTH);
    ADD_HL_DE;
    POP_DE;
    DEC_B;
    IF_NZ goto loop;

    LD_A_D;
    LD_E(0);
    LD_B(PARTY_LENGTH);

loop2:
    SRL_A;
    IF_NC goto okay;
    INC_E;


okay:
    DEC_B;
    IF_NZ goto loop2;
    LD_A_E;
    AND_A_A;
    RET;

}

uint8_t IsAnyMonHoldingExpShare_Conv(void){
    // LD_A_addr(wPartyCount);
    // LD_B_A;
    const uint8_t b = wram->wPartyCount;
    // LD_HL(wPartyMon1);
    // LD_C(1);
    uint8_t c = 1;
    // LD_D(0);
    uint8_t d = 0;

    for(uint8_t i = 0; i < b; ++i, c <<= 1) {
    // loop:
        // PUSH_HL;
        // PUSH_BC;
        // LD_BC(MON_HP);
        // ADD_HL_BC;
        // LD_A_hli;
        // OR_A_hl;
        // POP_BC;
        // POP_HL;
        // IF_Z goto next;
        if(wram->wPartyMon[i].HP == 0)
            continue;

        // PUSH_HL;
        // PUSH_BC;
        // LD_BC(MON_ITEM);
        // ADD_HL_BC;
        // POP_BC;
        // LD_A_hl;
        // POP_HL;
        item_t a = wram->wPartyMon[i].mon.item;

        // CP_A(EXP_SHARE);
        // IF_NZ goto next;
        if(a != EXP_SHARE)
            continue;
        // LD_A_D;
        // OR_A_C;
        // LD_D_A;
        d |= c;

    // next:
        // SLA_C;
        // PUSH_DE;
        // LD_DE(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_DE;
        // POP_DE;
        // DEC_B;
        // IF_NZ goto loop;
    }

    // LD_A_D;
    // uint8_t a = d;
    // LD_E(0);
    // uint8_t e = 0;
    // LD_B(PARTY_LENGTH);

    // for(uint8_t i = 0; i < PARTY_LENGTH; ++i) {
    // loop2:
        // SRL_A;
        // IF_NC goto okay;
        // INC_E;
        // if(a & 1) {
        //     e++;
        // }
        // a >>= 1;


    // okay:
        // DEC_B;
        // IF_NZ goto loop2;
    // }
    // LD_A_E;
    // AND_A_A;
    // RET;
    return d;
}

void StopDangerSound(void){
    // XOR_A_A;
    // LD_addr_A(wLowHealthAlarm);
    // RET;
    wram->wLowHealthAlarm = 0;
}

void FaintYourPokemon(void){
    // CALL(aStopDangerSound);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_A(0xf0);
    // LD_addr_A(wCryTracks);
    wram->wCryTracks = 0xf0;
    // LD_A_addr(wBattleMonSpecies);
    // CALL(aPlayStereoCry);
    PlayStereoCry_Conv(wram->wBattleMon.species);
    // CALL(aPlayerMonFaintedAnimation);
    PlayerMonFaintedAnimation();
    // hlcoord(9, 7, wTilemap);
    // LD_BC((5 << 8) | 11);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(9, 7, wram->wTilemap), 11, 5);
    // LD_HL(mBattleText_MonFainted);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BattleText_MonFainted);
}

void FaintEnemyPokemon(void){
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_DE(SFX_KINESIS);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_KINESIS);
    // CALL(aEnemyMonFaintedAnimation);
    EnemyMonFaintedAnimation();
    // LD_DE(SFX_FAINT);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_FAINT);
    // hlcoord(1, 0, wTilemap);
    // LD_BC((4 << 8) | 10);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 0, wram->wTilemap), 10, 4);
    // LD_HL(mBattleText_EnemyMonFainted);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(BattleText_EnemyMonFainted);
}

void CheckEnemyTrainerDefeated(void){
    LD_A_addr(wOTPartyCount);
    LD_B_A;
    XOR_A_A;
    LD_HL(wOTPartyMon1HP);
    LD_DE(PARTYMON_STRUCT_LENGTH);


loop:
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    DEC_HL;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop;

    AND_A_A;
    RET;

}

bool CheckEnemyTrainerDefeated_Conv(void){
    // LD_A_addr(wOTPartyCount);
    // LD_B_A;
    // XOR_A_A;
    // LD_HL(wOTPartyMon1HP);
    // LD_DE(PARTYMON_STRUCT_LENGTH);


// loop:
    // OR_A_hl;
    // INC_HL;
    // OR_A_hl;
    // DEC_HL;
    // ADD_HL_DE;
    // DEC_B;
    // IF_NZ goto loop;

    // AND_A_A;
    // RET;
    for(uint8_t i = 0; i < wram->wOTPartyCount; ++i) {
        if(wram->wOTPartyMon[i].HP > 0)
            return false;
    }
    return true;
}

void HandleEnemySwitch(void){
    PEEK("");
    LD_HL(wEnemyHPPal);
    LD_E(HP_BAR_LENGTH_PX);
    CALL(aUpdateHPPal);
    CALL(aWaitBGMap);
    FARCALL(aEnemySwitch_TrainerHud);
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;

    CALL(aLinkBattleSendReceiveAction);
    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_FORFEIT);
    RET_Z ;

    CALL(aSafeLoadTempTilemapToTilemap);


not_linked:
    LD_HL(wBattleMonHP);
    LD_A_hli;
    OR_A_hl;
    LD_A(0x0);
    JR_NZ (mEnemyPartyMonEntrance);
    INC_A;
    RET;

}

uint8_t HandleEnemySwitch_Conv(void){
    PEEK("");
    // LD_HL(wEnemyHPPal);
    // LD_E(HP_BAR_LENGTH_PX);
    // CALL(aUpdateHPPal);
    UpdateHPPal_Conv(&wram->wEnemyHPPal, HP_BAR_LENGTH_PX);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // FARCALL(aEnemySwitch_TrainerHud);
    EnemySwitch_TrainerHud();
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;
    if(wram->wLinkMode != 0) {
        // CALL(aLinkBattleSendReceiveAction);
        LinkBattleSendReceiveAction();
        // LD_A_addr(wBattleAction);
        // CP_A(BATTLEACTION_FORFEIT);
        // RET_Z ;
        if(wram->wBattleAction == BATTLEACTION_FORFEIT)
            return 0;

        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap_Conv();
    }

// not_linked:
    // LD_HL(wBattleMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // LD_A(0x0);
    // JR_NZ (mEnemyPartyMonEntrance);
    if(wram->wBattleMon.hp != 0) {
        return EnemyPartyMonEntrance_Conv(false);
    }
    // INC_A;
    // RET;
    return 1;
}

void EnemyPartyMonEntrance(void){
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wEnemySwitchMonIndex);
    CALL(aNewEnemyMonStatus);
    CALL(aResetEnemyStatLevels);
    CALL(aBreakAttraction);
    POP_AF;
    AND_A_A;
    IF_NZ goto set;
    CALL(aEnemySwitch);
    goto done_switch;


set:
    CALL(aEnemySwitch_SetMode);

done_switch:
    CALL(aResetBattleParticipants);
    CALL(aSetEnemyTurn);
    CALL(aSpikesDamage);
    XOR_A_A;
    LD_addr_A(wEnemyMoveStruct + MOVE_ANIM);
    LD_addr_A(wBattlePlayerAction);
    INC_A;
    RET;

}

uint8_t EnemyPartyMonEntrance_Conv(bool set){
    // PUSH_AF;
    // XOR_A_A;
    // LD_addr_A(wEnemySwitchMonIndex);
    wram->wEnemySwitchMonIndex = 0;
    // CALL(aNewEnemyMonStatus);
    NewEnemyMonStatus_Conv();
    // CALL(aResetEnemyStatLevels);
    ResetEnemyStatLevels_Conv();
    // CALL(aBreakAttraction);
    BreakAttraction();
    // POP_AF;
    // AND_A_A;
    // IF_NZ goto set;
    if(!set) {
        // CALL(aEnemySwitch);
        EnemySwitch();
        // goto done_switch;
    }
    else {
    // set:
        // CALL(aEnemySwitch_SetMode);
        EnemySwitch_SetMode();
    }

// done_switch:
    // CALL(aResetBattleParticipants);
    ResetBattleParticipants();
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // CALL(aSpikesDamage);
    SpikesDamage();
    // XOR_A_A;
    // LD_addr_A(wEnemyMoveStruct + MOVE_ANIM);
    wram->wEnemyMoveStruct.animation = 0;
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = 0;
    // INC_A;
    // RET;
    return 1;
}

static void WinTrainerBattle_DoubleReward(void){
    uint32_t reward = (wram->wBattleReward[0] << 16) | (wram->wBattleReward[1] << 8) | wram->wBattleReward[2];
    // LD_HL(wBattleReward + 2);
    // SLA_hl;
    // DEC_HL;
    // RL_hl;
    // DEC_HL;
    // RL_hl;
    // RET_NC ;
    if(reward * 2 >= 0xffffff) {
        // LD_A(0xff);
        // LD_hli_A;
        // LD_hli_A;
        // LD_hl_A;
        reward = 0xffffff;
    }
    else {
        reward *= 2;
    }
    wram->wBattleReward[0] = HIGH(reward >> 8);
    wram->wBattleReward[1] = HIGH(reward);
    wram->wBattleReward[2] = LOW(reward);
    // RET;
}

static bool WinTrainerBattle_CheckMaxedOutMomMoney(void){
    // LD_HL(wMomsMoney + 2);
    // LD_A_hld;
    // CP_A(LOW(MAX_MONEY));
    // LD_A_hld;
    // SBC_A(HIGH(MAX_MONEY));  // mid
    // LD_A_hl;
    // SBC_A(HIGH(MAX_MONEY >> 8));
    uint32_t money = (wram->wMomsMoney[2]) | (wram->wMomsMoney[1] << 8) | (wram->wMomsMoney[0] << 16);
    // RET;
    return money >= MAX_MONEY;
}

static void WinTrainerBattle_AddMoneyToMom(void){
    // PUSH_BC;
    // LD_HL(wBattleReward + 2);
    // LD_DE(wMomsMoney + 2);
    // CALL(aAddBattleMoneyToAccount);
    AddBattleMoneyToAccount(wram->wMomsMoney, wram->wBattleReward);
    // POP_BC;
    // RET;
}

static void WinTrainerBattle_AddMoneyToWallet(void){
    // PUSH_BC;
    // LD_HL(wBattleReward + 2);
    // LD_DE(wMoney + 2);
    // CALL(aAddBattleMoneyToAccount);
    AddBattleMoneyToAccount(wram->wMoney, wram->wBattleReward);
    // POP_BC;
    // RET;
}

void WinTrainerBattle(void){
//  Player won the battle
    PEEK("");
    // CALL(aStopDangerSound);
    StopDangerSound();
    // LD_A(0x1);
    // LD_addr_A(wBattleLowHealthAlarm);
    wram->wBattleLowHealthAlarm = 0x1;
    // LD_addr_A(wBattleEnded);
    wram->wBattleEnded = 0x1;
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // LD_A_B;
    // CALL_Z (aPlayVictoryMusic);
    if(wram->wLinkMode == 0x0)
        PlayVictoryMusic();
    // CALLFAR(aBattle_GetTrainerName);
    Battle_GetTrainerName_Conv();
    // LD_HL(mBattleText_EnemyWasDefeated);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_EnemyWasDefeated);

    // CALL(aIsMobileBattle);
    // IF_Z goto mobile;
    if(IsMobileBattle_Conv()){
    // mobile:
        // CALL(aBattleWinSlideInEnemyTrainerFrontpic);
        BattleWinSlideInEnemyTrainerFrontpic();
        // LD_C(40);
        // CALL(aDelayFrames);
        DelayFrames_Conv(40);
        //  TODO: Convert Mobile_PrintOpponentBattleMessage
        // LD_C(0x4);  // win
        // FARCALL(aMobile_PrintOpponentBattleMessage);
        // RET;
        return;
    }
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wLinkMode != 0)
        return;

    // LD_A_addr(wInBattleTowerBattle);
    // BIT_A(0);
    // IF_NZ goto battle_tower;
    if(bit_test(wram->wInBattleTowerBattle, 0)){
    // battle_tower:
        // CALL(aBattleWinSlideInEnemyTrainerFrontpic);
        BattleWinSlideInEnemyTrainerFrontpic();
        // LD_C(40);
        // CALL(aDelayFrames);
        DelayFrames_Conv(40);
        // CALL(aEmptyBattleTextbox);
        EmptyBattleTextbox();
        // LD_C(BATTLETOWERTEXT_LOSS_TEXT);
        // FARCALL(aBattleTowerText);
        BattleTowerText(BATTLETOWERTEXT_LOSS_TEXT);
        // CALL(aWaitPressAorB_BlinkCursor);
        WaitPressAorB_BlinkCursor_Conv();
        // LD_HL(wPayDayMoney);
        // LD_A_hli;
        // OR_A_hl;
        // INC_HL;
        // OR_A_hl;
        // RET_NZ ;
        if(wram->wPayDayMoney[0] | wram->wPayDayMoney[1] | wram->wPayDayMoney[2])
            return;
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // CALL(aClearBGPalettes);
        ClearBGPalettes_Conv();
        // RET;
        return;
    }

    // CALL(aBattleWinSlideInEnemyTrainerFrontpic);
    BattleWinSlideInEnemyTrainerFrontpic();
    // LD_C(40);
    // CALL(aDelayFrames);
    DelayFrames_Conv(40);

    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_CANLOSE);
    // IF_NZ goto skip_heal;
    if(wram->wBattleType == BATTLETYPE_CANLOSE){
        // PREDEF(pHealParty);
        HealParty_Conv();
    }

// skip_heal:
    // LD_A_addr(wDebugFlags);
    // BIT_A(DEBUG_BATTLE_F);
    // IF_NZ goto skip_win_loss_text;
    if(!bit_test(wram->wDebugFlags, DEBUG_BATTLE_F)){
        // CALL(aPrintWinLossText);
        PrintWinLossText_Conv();
    }

// skip_win_loss_text:
    // JP(mWinTrainerBattle_give_money);
    // goto give_money;

// give_money:
    PEEK("give_money");
    
    printf("reward %d\n", (wram->wBattleReward[0] << 16) | (wram->wBattleReward[1] << 8) | wram->wBattleReward[2]);
    // LD_A_addr(wAmuletCoin);
    // AND_A_A;
    // CALL_NZ (aWinTrainerBattle_DoubleReward);
    if(wram->wAmuletCoin)
        WinTrainerBattle_DoubleReward();
    // CALL(aWinTrainerBattle_CheckMaxedOutMomMoney);
    // PUSH_AF;
    bool isMaxedOut = WinTrainerBattle_CheckMaxedOutMomMoney();
    // LD_A(FALSE);
    uint8_t b = FALSE;
    // IF_NC goto okay;
    if(!isMaxedOut){
        // LD_A_addr(wMomSavingMoney);
        // AND_A(MOM_SAVING_MONEY_MASK);
        // CP_A((1 << MOM_SAVING_SOME_MONEY_F) | (1 << MOM_SAVING_HALF_MONEY_F));
        // IF_NZ goto okay;
        if((wram->wMomSavingMoney & MOM_SAVING_MONEY_MASK) == ((1 << MOM_SAVING_SOME_MONEY_F) | (1 << MOM_SAVING_HALF_MONEY_F))) {
        // INC_A;  // TRUE
            b = TRUE;
        }
        else {
            b = wram->wMomSavingMoney & MOM_SAVING_MONEY_MASK;
        }
    }

// okay:
    // LD_B_A;
    // LD_C(4);
    uint8_t c = 4;

    while(b) {
    // loop:
        // LD_A_B;
        // AND_A_A;
        // IF_Z goto loop2;
        // CALL(aWinTrainerBattle_AddMoneyToMom);
        WinTrainerBattle_AddMoneyToMom();
        // DEC_C;
        --c;
        // DEC_B;
        --b;
        // goto loop;
    }

    while(c){
    // loop2:
        // LD_A_C;
        // AND_A_A;
        // IF_Z goto done;
        // CALL(aWinTrainerBattle_AddMoneyToWallet);
        WinTrainerBattle_AddMoneyToWallet();
        // DEC_C;
        --c;
        // goto loop2;
    }

// done:
    // CALL(aWinTrainerBattle_DoubleReward);
    WinTrainerBattle_DoubleReward();
    // CALL(aWinTrainerBattle_DoubleReward);
    WinTrainerBattle_DoubleReward();
    // POP_AF;
    // IF_NC goto KeepItAll;
    // LD_A_addr(wMomSavingMoney);
    // AND_A(MOM_SAVING_MONEY_MASK);
    // IF_Z goto KeepItAll;
    if(!isMaxedOut && (wram->wMomSavingMoney & MOM_SAVING_MONEY_MASK) != 0){
        static const txt_cmd_s* SentToMomTexts[] = {
        //  entries correspond to MOM_SAVING_* constants
            SentSomeToMomText,
            SentHalfToMomText,
            SentAllToMomText,
        };
        // LD_HL(mWinTrainerBattle_SentToMomTexts);
        // DEC_A;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // JP(mStdBattleTextbox);
        return StdBattleTextbox_Conv2(SentToMomTexts[(wram->wMomSavingMoney & MOM_SAVING_MONEY_MASK) - 1]);
    }

// KeepItAll:
    PEEK("KeepItAll");
    // LD_HL(mGotMoneyForWinningText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(GotMoneyForWinningText);
}

void AddBattleMoneyToAccount(uint8_t* de, const uint8_t* hl){
    // LD_C(3);
    // AND_A_A;
    // PUSH_DE;
    // PUSH_HL;
    // PUSH_BC;
    // LD_B_H;
    // LD_C_L;
    // FARCALL(aStubbedTrainerRankings_AddToBattlePayouts);
    // POP_BC;
    // POP_HL;
    uint8_t c = 3;
    uint8_t carry = 0;

    do {
    // loop:
        // LD_A_de;
        // ADC_A_hl;
        // LD_de_A;
        de[c-1] = AddCarry8(de[c-1], hl[c-1], carry, &carry);
        // DEC_DE;
        // DEC_HL;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // POP_HL;
    uint32_t money = de[2] | (de[1] << 8) | (de[0] << 16);
    // LD_A_hld;
    // CP_A(LOW(MAX_MONEY));
    // LD_A_hld;
    // SBC_A(HIGH(MAX_MONEY));  // mid
    // LD_A_hl;
    // SBC_A(HIGH(MAX_MONEY >> 8));
    // RET_C ;
    if(money < MAX_MONEY)
        return;
    // LD_hl(HIGH(MAX_MONEY >> 8));
    de[0] = HIGH(MAX_MONEY >> 8);
    // INC_HL;
    // LD_hl(HIGH(MAX_MONEY));  // mid
    de[1] = HIGH(MAX_MONEY);
    // INC_HL;
    // LD_hl(LOW(MAX_MONEY));
    de[2] = LOW(MAX_MONEY);
    // RET;
}

void PlayVictoryMusic(void){
    // PUSH_DE;
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_DE(MUSIC_WILD_VICTORY);
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_NZ goto trainer_victory;
    if(wram->wBattleMode == TRAINER_BATTLE) {
    // trainer_victory:
        // LD_DE(MUSIC_GYM_VICTORY);
        // CALL(aIsGymLeader);
        if(IsGymLeader_Conv(wram->wOtherTrainerClass)) {
            PlayMusic_Conv(MUSIC_GYM_VICTORY);
            return;
        }
        // IF_C goto play_music;
        // LD_DE(MUSIC_TRAINER_VICTORY);
        else {
            PlayMusic_Conv(MUSIC_TRAINER_VICTORY);
            return;
        }
    }
    // PUSH_DE;
    // CALL(aIsAnyMonHoldingExpShare);
    // POP_DE;
    // IF_NZ goto play_music;
    // LD_HL(wPayDayMoney);
    // LD_A_hli;
    // OR_A_hl;
    // IF_NZ goto play_music;
    // LD_A_addr(wBattleParticipantsNotFainted);
    // AND_A_A;
    // IF_Z goto lost;
    if(IsAnyMonHoldingExpShare_Conv() == 0 && (wram->wPayDayMoney[0] | wram->wPayDayMoney[1]) == 0 && wram->wBattleParticipantsNotFainted == 0)
        return;
    // goto play_music;


// play_music:
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_WILD_VICTORY);
    return;


// lost:
    // POP_DE;
    // RET;
}

void IsKantoGymLeader(void){
    LD_HL(mKantoGymLeaders);
    JR(mIsGymLeaderCommon);

}

bool IsKantoGymLeader_Conv(uint8_t a){
    // LD_HL(mKantoGymLeaders);
    // JR(mIsGymLeaderCommon);
    for(uint8_t i = 0; KantoGymLeaders[i] != 0xff; ++i) {
        if(a == KantoGymLeaders[i])
            return true;
    }
    return false;
}

void IsGymLeader(void){
    LD_HL(mGymLeaders);
    return IsGymLeaderCommon();
}

bool IsGymLeader_Conv(uint8_t a){
    // LD_HL(mGymLeaders);
    // JR(mIsGymLeaderCommon);
    for(uint8_t i = 0; GymLeaders[i] != 0xff; ++i) {
        if(a == GymLeaders[i])
            return true;
    }
    return false;
}

void IsGymLeaderCommon(void){
    PUSH_DE;
    LD_A_addr(wOtherTrainerClass);
    LD_DE(1);
    CALL(aIsInArray);
    POP_DE;
    RET;

// INCLUDE "data/trainers/leaders.asm"
}

void HandlePlayerMonFaint(void){
    // CALL(aFaintYourPokemon);
    FaintYourPokemon();
    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // CALL_Z (aFaintEnemyPokemon);
    if(wram->wEnemyMon.hp == 0)
        FaintEnemyPokemon();
    // LD_A(0x1);
    // LD_addr_A(wWhichMonFaintedFirst);
    wram->wWhichMonFaintedFirst = 0x1;
    // CALL(aUpdateFaintedPlayerMon);
    UpdateFaintedPlayerMon();
    // CALL(aCheckPlayerPartyForFitMon);
    // LD_A_D;
    // AND_A_A;
    // JP_Z (mLostBattle);
    if(!CheckPlayerPartyForFitMon_Conv())
        return LostBattle();
    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // IF_NZ goto notfainted;
    if(wram->wEnemyMon.hp == 0) {
        // CALL(aUpdateBattleStateAndExperienceAfterEnemyFaint);
        UpdateBattleStateAndExperienceAfterEnemyFaint();
        // LD_A_addr(wBattleMode);
        // DEC_A;
        // IF_NZ goto trainer;
        if(wram->wBattleMode == WILD_BATTLE) {
            // LD_A(0x1);
            // LD_addr_A(wBattleEnded);
            wram->wBattleEnded = 0x1;
            // RET;
            return;
        }
        else {
        // trainer:
            // CALL(aCheckEnemyTrainerDefeated);
            // JP_Z (mWinTrainerBattle);
            if(CheckEnemyTrainerDefeated_Conv())
                return WinTrainerBattle();
        }
    }

// notfainted:
    // CALL(aAskUseNextPokemon);
    // IF_NC goto switch_;
    if(AskUseNextPokemon_Conv()){
        // LD_A(0x1);
        // LD_addr_A(wBattleEnded);
        wram->wBattleEnded = 0x1;
        // RET;
        return;
    }

// switch_:
    // CALL(aForcePlayerMonChoice);
    uint8_t c = ForcePlayerMonChoice();
    // CALL(aCheckMobileBattleError);
    // JP_C (mWildFled_EnemyFled_LinkBattleCanceled);
    if(CheckMobileBattleError_Conv())
        return WildFled_EnemyFled_LinkBattleCanceled();
    // LD_A_C;
    // AND_A_A;
    // RET_NZ ;
    if(c != 0x0)
        return;
    // LD_A(BATTLEPLAYERACTION_USEITEM);
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEITEM;
    // CALL(aHandleEnemySwitch);
    // JP_Z (mWildFled_EnemyFled_LinkBattleCanceled);
    if(HandleEnemySwitch_Conv())
        return WildFled_EnemyFled_LinkBattleCanceled();
    // JP(mDoubleSwitch);
    return DoubleSwitch();
}

void UpdateFaintedPlayerMon(void){
    // LD_A_addr(wCurBattleMon);
    // LD_C_A;
    // LD_HL(wBattleParticipantsNotFainted);
    // LD_B(RESET_FLAG);
    // PREDEF(pSmallFarFlagAction);
    SmallFarFlagAction_Conv(&wram->wBattleParticipantsNotFainted, wram->wCurBattleMon, RESET_FLAG);
    // LD_HL(wEnemySubStatus3);
    // RES_hl(SUBSTATUS_IN_LOOP);
    bit_reset(wram->wEnemySubStatus3, SUBSTATUS_IN_LOOP);
    // XOR_A_A;
    // LD_addr_A(wLowHealthAlarm);
    wram->wLowHealthAlarm = 0;
    // LD_HL(wPlayerDamageTaken);
    // LD_hli_A;
    // LD_hl_A;
    wram->wPlayerDamageTaken = 0;
    // LD_addr_A(wBattleMonStatus);
    wram->wBattleMon.status[0] = 0;
    // CALL(aUpdateBattleMonInParty);
    UpdateBattleMonInParty_Conv();
    // LD_C(HAPPINESS_FAINTED);
// If TheirLevel > (YourLevel + 30), use a different parameter
    // LD_A_addr(wBattleMonLevel);
    // ADD_A(30);
    // LD_B_A;
    // LD_A_addr(wEnemyMonLevel);
    // CP_A_B;
    // IF_C goto got_param;
    // LD_C(HAPPINESS_BEATENBYSTRONGFOE);
    uint8_t c = (wram->wEnemyMon.level > wram->wBattleMon.level + 30)? HAPPINESS_BEATENBYSTRONGFOE: HAPPINESS_FAINTED;

// got_param:
    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wCurBattleMon;
    // CALLFAR(aChangeHappiness);
    ChangeHappiness_Conv(c);
    // LD_A_addr(wBattleResult);
    // AND_A(BATTLERESULT_BITMASK);
    // ADD_A(LOSE);
    // LD_addr_A(wBattleResult);
    wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) + LOSE;
    // LD_A_addr(wWhichMonFaintedFirst);
    // AND_A_A;
    // RET_Z ;
    if(wram->wWhichMonFaintedFirst == 0)
        return;
// code was probably dummied out here
    // RET;
    return;
}

void AskUseNextPokemon(void){
    CALL(aEmptyBattleTextbox);
    CALL(aLoadTilemapToTempTilemap);
//  We don't need to be here if we're in a Trainer battle,
//  as that decision is made for us.
    LD_A_addr(wBattleMode);
    AND_A_A;
    DEC_A;
    RET_NZ ;

    LD_HL(mBattleText_UseNextMon);
    CALL(aStdBattleTextbox);

loop:
    LD_BC((1 << 8) | 7);
    CALL(aPlaceYesNoBox);
    LD_A_addr(wMenuCursorY);
    IF_C goto pressed_b;
    AND_A_A;
    RET;


pressed_b:
    LD_A_addr(wMenuCursorY);
    CP_A(0x1);  // YES
    IF_Z goto loop;
    LD_HL(wPartyMon1Speed);
    LD_DE(wEnemyMonSpeed);
    JP(mTryToRunAwayFromBattle);

}

bool AskUseNextPokemon_Conv(void){
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
//  We don't need to be here if we're in a Trainer battle,
//  as that decision is made for us.
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // DEC_A;
    // RET_NZ ;
    if(wram->wBattleMode == TRAINER_BATTLE)
        return false;

    // LD_HL(mBattleText_UseNextMon);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_UseNextMon);

    do {
    // loop:
        // LD_BC((1 << 8) | 7);
        // CALL(aPlaceYesNoBox);
        bool yes = v_YesNoBox_Conv(1, 7);
        // LD_A_addr(wMenuCursorY);
        // IF_C goto pressed_b;
        if(yes) {
            // AND_A_A;
            // RET;
            return false;
        }


    // pressed_b:
        // LD_A_addr(wMenuCursorY);
        // CP_A(0x1);  // YES
        // IF_Z goto loop;
    } while(wram->wMenuCursorY == 0x1);
    // LD_HL(wPartyMon1Speed);
    // LD_DE(wEnemyMonSpeed);
    // JP(mTryToRunAwayFromBattle);
    return TryToRunAwayFromBattle_Conv(&wram->wBattleMon, &wram->wEnemyMon);
}

uint8_t ForcePlayerMonChoice(void){
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // CALL(aSetUpBattlePartyMenu);
    SetUpBattlePartyMenu();
    // CALL(aForcePickPartyMonInBattle);
    ForcePickPartyMonInBattle();
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto skip_link;
    if(wram->wLinkMode != 0) {
        // LD_A(BATTLEPLAYERACTION_USEITEM);
        // LD_addr_A(wBattlePlayerAction);
        wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEITEM;
        // CALL(aLinkBattleSendReceiveAction);
        LinkBattleSendReceiveAction();
    }

// skip_link:
    // XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEMOVE;
    // CALL(aCheckMobileBattleError);
    // IF_C goto enemy_fainted_mobile_error;
    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // IF_NZ goto send_out_pokemon;
    if(CheckMobileBattleError_Conv() || wram->wEnemyMon.hp == 0){
    // enemy_fainted_mobile_error:
        // CALL(aClearSprites);
        ClearSprites_Conv();
        // CALL(aClearBGPalettes);
        ClearBGPalettes_Conv();
        // CALL(av_LoadHPBar);
        v_LoadHPBar_Conv();
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // CALL(aLoadTilemapToTempTilemap);
        LoadTilemapToTempTilemap_Conv();
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // CALL(aGetMemSGBLayout);
        GetMemSGBLayout_Conv();
        // CALL(aSetPalettes);
        SetPalettes_Conv();
        // XOR_A_A;
        // LD_C_A;
        // RET;
        return 0x0;
    }

// send_out_pokemon:
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wLastPlayerMon);
    wram->wLastPlayerMon = wram->wCurBattleMon;
    // LD_A_addr(wCurPartyMon);
    // LD_addr_A(wCurBattleMon);
    wram->wCurBattleMon = wram->wCurPartyMon;
    // CALL(aAddBattleParticipant);
    AddBattleParticipant();
    // CALL(aInitBattleMon);
    InitBattleMon();
    // CALL(aResetPlayerStatLevels);
    ResetPlayerStatLevels();
    // CALL(aClearPalettes);
    ClearPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(av_LoadHPBar);
    v_LoadHPBar_Conv();
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // CALL(aGetMemSGBLayout);
    GetMemSGBLayout_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aSendOutMonText);
    SendOutMonText();
    // CALL(aNewBattleMonStatus);
    NewBattleMonStatus();
    // CALL(aBreakAttraction);
    BreakAttraction();
    // CALL(aSendOutPlayerMon);
    SendOutPlayerMon();
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // CALL(aSpikesDamage);
    SpikesDamage();
    // LD_A(0x1);
    // AND_A_A;
    // LD_C_A;
    // RET;
    return 0x1;
}

void PlayerPartyMonEntrance(void){
    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wLastPlayerMon);
    wram->wLastPlayerMon = wram->wCurBattleMon;
    // LD_A_addr(wCurPartyMon);
    // LD_addr_A(wCurBattleMon);
    wram->wCurBattleMon = wram->wCurPartyMon;
    // CALL(aAddBattleParticipant);
    AddBattleParticipant();
    // CALL(aInitBattleMon);
    InitBattleMon();
    // CALL(aResetPlayerStatLevels);
    ResetPlayerStatLevels();
    // CALL(aSendOutMonText);
    SendOutMonText();
    // CALL(aNewBattleMonStatus);
    NewBattleMonStatus();
    // CALL(aBreakAttraction);
    BreakAttraction();
    // CALL(aSendOutPlayerMon);
    SendOutPlayerMon();
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // JP(mSpikesDamage);
    SpikesDamage();
}

void CheckMobileBattleError(void){
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    IF_NZ goto not_mobile;  // It's not a mobile battle

    LD_A_addr(wcd2b);
    AND_A_A;
    IF_Z goto not_mobile;

//  We have a mobile battle and something else happened
    SCF;
    RET;


not_mobile:
    XOR_A_A;
    RET;

}

bool CheckMobileBattleError_Conv(void){
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // IF_NZ goto not_mobile;  // It's not a mobile battle
    if(wram->wLinkMode != LINK_MOBILE)
        return false;

    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_Z goto not_mobile;
    if(wram->wcd2b == 0)
        return false;

//  We have a mobile battle and something else happened
    // SCF;
    // RET;
    return true;

// not_mobile:
    // XOR_A_A;
    // RET;
}

void IsMobileBattle(void){
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    RET;

}

bool IsMobileBattle_Conv(void){
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // RET;
    return wram->wLinkMode == LINK_MOBILE;
}

void SetUpBattlePartyMenu(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    return SetUpBattlePartyMenu_Loop();
}

void SetUpBattlePartyMenu_Loop(void){
//  //  switch to fullscreen menu?
    // FARCALL(aLoadPartyMenuGFX);
    LoadPartyMenuGFX();
    // FARCALL(aInitPartyMenuWithCancel);
    InitPartyMenuWithCancel();
    // FARCALL(aInitPartyMenuBGPal7);
    InitPartyMenuBGPal7();
    // FARCALL(aInitPartyMenuGFX);
    InitPartyMenuGFX();
    // RET;
}

void JumpToPartyMenuAndPrintText(void){
    // FARCALL(aWritePartyMenuTilemap);
    WritePartyMenuTilemap();
    // FARCALL(aPrintPartyMenuText);
    PrintPartyMenuText();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

u8_flag_s SelectBattleMon(void){
    // CALL(aIsMobileBattle);
    // IF_Z goto mobile;
    if(IsMobileBattle_Conv()) {
    // mobile:
        // FARCALL(aMobile_PartyMenuSelect);
        // RET;
        return u8_flag(0, false);
    }
    // FARCALL(aPartyMenuSelect);
    u8_flag_s res = PartyMenuSelect();
    // RET;
    return res;
}

bool PickPartyMonInBattle(void){

    do {
    // loop:
        // LD_A(PARTYMENUACTION_SWITCH);  // Which PKMN?
        // LD_addr_A(wPartyMenuActionText);
        wram->wPartyMenuActionText = PARTYMENUACTION_SWITCH;
        // CALL(aJumpToPartyMenuAndPrintText);
        JumpToPartyMenuAndPrintText();
        // CALL(aSelectBattleMon);
        u8_flag_s res = SelectBattleMon();
        // RET_C ;
        if(res.flag)
            return true;
        // CALL(aCheckIfCurPartyMonIsFitToFight);
        // IF_Z goto loop;
    } while(!CheckIfCurPartyMonIsFitToFight_Conv());
    // XOR_A_A;
    // RET;
    return false;
}

bool SwitchMonAlreadyOut(void){
    // LD_HL(wCurBattleMon);
    // LD_A_addr(wCurPartyMon);
    // CP_A_hl;
    // IF_NZ goto notout;
    if(wram->wCurBattleMon != wram->wCurPartyMon)
        return false;

    // LD_HL(mBattleText_MonIsAlreadyOut);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_MonIsAlreadyOut);
    // SCF;
    // RET;
    return true;

// notout:
    // XOR_A_A;
    // RET;
}

bool ForcePickPartyMonInBattle(void){
//  Can't back out.
    while(1) {
    // pick:
        // CALL(aPickPartyMonInBattle);
        // RET_NC ;
        if(!PickPartyMonInBattle())
            return false;
        // CALL(aCheckMobileBattleError);
        // RET_C ;
        if(CheckMobileBattleError_Conv())
            return true;

        // LD_DE(SFX_WRONG);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_WRONG);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // goto pick;
    }
}

bool PickSwitchMonInBattle(void){
    do {
    // pick:
        // CALL(aPickPartyMonInBattle);
        // RET_C ;
        if(PickPartyMonInBattle())
            return true;
        // CALL(aSwitchMonAlreadyOut);
        // IF_C goto pick;
    } while(SwitchMonAlreadyOut());
    // XOR_A_A;
    // RET;
    return false;
}

bool ForcePickSwitchMonInBattle(void){
//  Can't back out.

    do {
    // pick:
        // CALL(aForcePickPartyMonInBattle);
        ForcePickPartyMonInBattle();
        // CALL(aCheckMobileBattleError);
        // RET_C ;
        if(CheckMobileBattleError_Conv())
            return true;
        // CALL(aSwitchMonAlreadyOut);
        // IF_C goto pick;
    } while(SwitchMonAlreadyOut());

    // XOR_A_A;
    // RET;
    return false;
}

void LostBattle(void){
    // LD_A(1);
    // LD_addr_A(wBattleEnded);
    wram->wBattleEnded = 1;

    // LD_A_addr(wInBattleTowerBattle);
    // BIT_A(0);
    // IF_NZ goto battle_tower;
    if(bit_test(wram->wInBattleTowerBattle, 0)) {
    // battle_tower:
    //  Remove the enemy from the screen.
        // hlcoord(0, 0, wTilemap);
        // LD_BC((8 << 8) | 21);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(0, 0, wram->wTilemap), 21, 8);
        // CALL(aBattleWinSlideInEnemyTrainerFrontpic);
        BattleWinSlideInEnemyTrainerFrontpic();

        // LD_C(40);
        // CALL(aDelayFrames);
        DelayFrames_Conv(40);

        // CALL(aEmptyBattleTextbox);
        EmptyBattleTextbox();
        // LD_C(BATTLETOWERTEXT_WIN_TEXT);
        // FARCALL(aBattleTowerText);
        BattleTowerText(BATTLETOWERTEXT_WIN_TEXT);
        // CALL(aWaitPressAorB_BlinkCursor);
        WaitPressAorB_BlinkCursor_Conv();
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // CALL(aClearBGPalettes);
        ClearBGPalettes_Conv();
        // RET;
        return;
    }

    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_CANLOSE);
    // IF_NZ goto not_canlose;
    if(wram->wBattleType == BATTLETYPE_CANLOSE) {
    //  Remove the enemy from the screen.
        // hlcoord(0, 0, wTilemap);
        // LD_BC((8 << 8) | 21);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(0, 0, wram->wTilemap), 21, 8);
        // CALL(aBattleWinSlideInEnemyTrainerFrontpic);
        BattleWinSlideInEnemyTrainerFrontpic();

        // LD_C(40);
        // CALL(aDelayFrames);
        DelayFrames_Conv(40);

        // LD_A_addr(wDebugFlags);
        // BIT_A(DEBUG_BATTLE_F);
        // IF_NZ goto skip_win_loss_text;
        if(!bit_test(wram->wDebugFlags, DEBUG_BATTLE_F)) {
            // CALL(aPrintWinLossText);
            PrintWinLossText_Conv();
        }

    // skip_win_loss_text:
        // RET;
        return;
    }

// not_canlose:
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto LostLinkBattle;
    if(wram->wLinkMode != 0) {
    // LostLinkBattle:
        // CALL(aUpdateEnemyMonInParty);
        UpdateEnemyMonInParty_Conv();
        // CALL(aCheckEnemyTrainerDefeated);
        // IF_NZ goto not_tied;
        if(CheckEnemyTrainerDefeated_Conv()) {
            // LD_HL(mTiedAgainstText);
            // LD_A_addr(wBattleResult);
            // AND_A(BATTLERESULT_BITMASK);
            // ADD_A(DRAW);
            // LD_addr_A(wBattleResult);
            wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) | DRAW;
            // goto text;
            StdBattleTextbox_Conv2(TiedAgainstText);
        }
        else {
        // not_tied:
            // LD_HL(mLostAgainstText);
            // CALL(aIsMobileBattle);
            // IF_Z goto mobile;
            if(IsMobileBattle_Conv()) {
            // mobile:
            //  Remove the enemy from the screen.
                // hlcoord(0, 0, wTilemap);
                // LD_BC((8 << 8) | 21);
                // CALL(aClearBox);
                ClearBox_Conv2(coord(0, 0, wram->wTilemap), 21, 8);
                // CALL(aBattleWinSlideInEnemyTrainerFrontpic);
                BattleWinSlideInEnemyTrainerFrontpic();

                // LD_C(40);
                // CALL(aDelayFrames);
                DelayFrames_Conv(40);

                //  TODO: Print Mobile battle text
                // LD_C(0x3);  // lost
                // FARCALL(aMobile_PrintOpponentBattleMessage);
                // SCF;
                // RET;
                return;
            }

        // text:
            // CALL(aStdBattleTextbox);
            StdBattleTextbox_Conv2(LostAgainstText);
        }
    }
    else {
    //  Grayscale
        // LD_B(SCGB_BATTLE_GRAYSCALE);
        // CALL(aGetSGBLayout);
        GetSGBLayout_Conv(SCGB_BATTLE_GRAYSCALE);
        // CALL(aSetPalettes);
        SetPalettes_Conv();
        // goto end;
    }

// end:
    // SCF;
    // RET;
}

void EnemyMonFaintedAnimation(void){
    // hlcoord(12, 5, wTilemap);
    // decoord(12, 6, wTilemap);
    // JP(mMonFaintedAnimation);
    return MonFaintedAnimation_Conv(coord(12, 6, wram->wTilemap), coord(12, 5, wram->wTilemap));
}

void PlayerMonFaintedAnimation(void){
    // hlcoord(1, 10, wTilemap);
    // decoord(1, 11, wTilemap);
    // JP(mMonFaintedAnimation);
    return MonFaintedAnimation_Conv(coord(1, 11, wram->wTilemap), coord(1, 10, wram->wTilemap));
}

void MonFaintedAnimation(void){
    LD_A_addr(wJoypadDisable);
    PUSH_AF;
    SET_A(JOYPAD_DISABLE_MON_FAINT_F);
    LD_addr_A(wJoypadDisable);

    LD_B(7);


OuterLoop:
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_B(6);


InnerLoop:
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    LD_BC(7);
    CALL(aCopyBytes);
    POP_DE;
    POP_HL;
    LD_BC(-SCREEN_WIDTH);
    ADD_HL_BC;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    POP_HL;
    POP_BC;
    DEC_B;
    IF_NZ goto InnerLoop;

    LD_BC(20);
    ADD_HL_BC;
    LD_DE(mMonFaintedAnimation_Spaces);
    CALL(aPlaceString);
    LD_C(2);
    CALL(aDelayFrames);
    POP_HL;
    POP_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto OuterLoop;

    POP_AF;
    LD_addr_A(wJoypadDisable);
    RET;


Spaces:
    //db ['"\t   @"'];

    return SlideBattlePicOut();
}

void MonFaintedAnimation_Conv(tile_t* de, tile_t* hl){
    static const char Spaces[] = "       @";
    uint8_t buf[16];
    // LD_A_addr(wJoypadDisable);
    // PUSH_AF;
    uint8_t disable = wram->wJoypadDisable;
    // SET_A(JOYPAD_DISABLE_MON_FAINT_F);
    // LD_addr_A(wJoypadDisable);
    bit_set(wram->wJoypadDisable, JOYPAD_DISABLE_MON_FAINT_F);

    U82CA(buf, Spaces);

    // LD_B(7);
    uint8_t b = 7;

    do {
    // OuterLoop:
        // PUSH_BC;
        // PUSH_DE;
        tile_t* de2 = de;
        // PUSH_HL;
        tile_t* hl2 = hl;
        // LD_B(6);
        uint8_t b2 = 6;

        do {
        // InnerLoop:
            // PUSH_BC;
            // PUSH_HL;
            // PUSH_DE;
            // LD_BC(7);
            // CALL(aCopyBytes);
            CopyBytes_Conv2(de, hl, 7);
            // POP_DE;
            // POP_HL;
            // LD_BC(-SCREEN_WIDTH);
            // ADD_HL_BC;
            // PUSH_HL;
            hl -= SCREEN_WIDTH;
            // LD_H_D;
            // LD_L_E;
            // ADD_HL_BC;
            // LD_D_H;
            // LD_E_L;
            de -= SCREEN_WIDTH;
            // POP_HL;
            // POP_BC;
            // DEC_B;
            // IF_NZ goto InnerLoop;
        } while(--b2 != 0);

        // LD_BC(20);
        // ADD_HL_BC;
        // LD_DE(mMonFaintedAnimation_Spaces);
        // CALL(aPlaceString);
        PlaceStringSimple(buf, hl + 20);
        // LD_C(2);
        // CALL(aDelayFrames);
        DelayFrames_Conv(2);
        // POP_HL;
        hl = hl2;
        // POP_DE;
        de = de2;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto OuterLoop;
    } while(--b != 0);

    // POP_AF;
    // LD_addr_A(wJoypadDisable);
    wram->wJoypadDisable = disable;
    // RET;
}

void SlideBattlePicOut(void){
    LDH_addr_A(hMapObjectIndex);
    LD_C_A;

loop:
    PUSH_BC;
    PUSH_HL;
    LD_B(0x7);

loop2:
    PUSH_HL;
    CALL(aSlideBattlePicOut_DoFrame);
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop2;
    LD_C(2);
    CALL(aDelayFrames);
    POP_HL;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;


DoFrame:
    LDH_A_addr(hMapObjectIndex);
    LD_C_A;
    CP_A(0x8);
    IF_NZ goto back;

forward:
    LD_A_hli;
    LD_hld_A;
    DEC_HL;
    DEC_C;
    IF_NZ goto forward;
    RET;


back:
    LD_A_hld;
    LD_hli_A;
    INC_HL;
    DEC_C;
    IF_NZ goto back;
    RET;

}

static void SlideBattlePicOut_DoFrame(uint8_t* hl) {
    // LDH_A_addr(hMapObjectIndex);
    // LD_C_A;
    uint8_t c = hram->hMapObjectIndex;
    // CP_A(0x8);
    // IF_NZ goto back;
    if(c == 0x8) {
        do {
        // forward:
            // LD_A_hli;
            uint8_t a = *(hl++);
            // LD_hld_A;
            *(hl--) = a;
            // DEC_HL;
            hl--;
            // DEC_C;
            // IF_NZ goto forward;
        } while(--c != 0);
        // RET;
        return;
    }
    else {
        do {
        // back:
            // LD_A_hld;
            uint8_t a = *(hl--);
            // LD_hli_A;
            *(hl++) = a;
            // INC_HL;
            hl++;
            // DEC_C;
            // IF_NZ goto back;
        } while(--c != 0);
        // RET;
        return;
    }
}

void SlideBattlePicOut_Conv(uint8_t* hl, uint8_t a){
    // LDH_addr_A(hMapObjectIndex);
    hram->hMapObjectIndex = a;
    // LD_C_A;
    uint8_t c = a;

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_B(0x7);
        uint8_t b = 0x7;

        do {
        // loop2:
            // PUSH_HL;
            // CALL(aSlideBattlePicOut_DoFrame);
            SlideBattlePicOut_DoFrame(hl);
            // POP_HL;
            // LD_DE(SCREEN_WIDTH);
            // ADD_HL_DE;
            hl += SCREEN_WIDTH;
            // DEC_B;
            // IF_NZ goto loop2;
        } while(--b != 0);
        // LD_C(2);
        // CALL(aDelayFrames);
        DelayFrames_Conv(2);
        // POP_HL;
        hl = hl2;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void ForceEnemySwitch(void){
    // CALL(aResetEnemyBattleVars);
    ResetEnemyBattleVars();
    // LD_A_addr(wEnemySwitchMonIndex);
    // DEC_A;
    // LD_B_A;
    // CALL(aLoadEnemyMonToSwitchTo);
    LoadEnemyMonToSwitchTo_Conv(wram->wEnemySwitchMonIndex - 1);
    // CALL(aClearEnemyMonBox);
    ClearEnemyMonBox_Conv();
    // CALL(aNewEnemyMonStatus);
    NewEnemyMonStatus_Conv();
    // CALL(aResetEnemyStatLevels);
    ResetEnemyStatLevels_Conv();
    // CALL(aShowSetEnemyMonAndSendOutAnimation);
    ShowSetEnemyMonAndSendOutAnimation();
    // CALL(aBreakAttraction);
    BreakAttraction();
    // CALL(aResetBattleParticipants);
    ResetBattleParticipants();
    // RET;
}

void EnemySwitch(void){
    // CALL(aCheckWhetherToAskSwitch);
    // JR_NC (mEnemySwitch_SetMode);
    if(!CheckWhetherToAskSwitch_Conv()) {
        return EnemySwitch_SetMode();
        // RET;
    }
// Shift Mode
    // CALL(aResetEnemyBattleVars);
    ResetEnemyBattleVars();
    // CALL(aCheckWhetherSwitchmonIsPredetermined);
    u8_flag_s res = CheckWhetherSwitchmonIsPredetermined_Conv();
    // IF_C goto skip;
    if(!res.flag) {
        // CALL(aFindMonInOTPartyToSwitchIntoBattle);
        res.a = FindMonInOTPartyToSwitchIntoBattle();
    }

// skip:
// 'b' contains the PartyNr of the mon the AI will switch to
    // CALL(aLoadEnemyMonToSwitchTo);
    LoadEnemyMonToSwitchTo_Conv(res.a);
    // CALL(aOfferSwitch);
    // PUSH_AF;
    bool switched = OfferSwitch_Conv();
    // CALL(aClearEnemyMonBox);
    ClearEnemyMonBox_Conv();
    // CALL(aShowBattleTextEnemySentOut);
    ShowBattleTextEnemySentOut();
    // CALL(aShowSetEnemyMonAndSendOutAnimation);
    ShowSetEnemyMonAndSendOutAnimation();
    // POP_AF;
    // RET_C ;
    if(!switched)
        return;
// If we're here, then we're switching too
    // XOR_A_A;
    // LD_addr_A(wBattleParticipantsNotFainted);
    wram->wBattleParticipantsNotFainted = 0;
    // LD_addr_A(wBattleParticipantsIncludingFainted);
    wram->wBattleParticipantsIncludingFainted = 0;
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = 0;
    // INC_A;
    // LD_addr_A(wEnemyIsSwitching);
    wram->wEnemyIsSwitching = 0xff;
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // JP(mPlayerSwitch);
    PlayerSwitch();
    return;
}

void EnemySwitch_SetMode(void){
    // CALL(aResetEnemyBattleVars);
    ResetEnemyBattleVars();
    // CALL(aCheckWhetherSwitchmonIsPredetermined);
    // IF_C goto skip;
    u8_flag_s res = CheckWhetherSwitchmonIsPredetermined_Conv();
    if(!res.flag) {
        // CALL(aFindMonInOTPartyToSwitchIntoBattle);
        res.a = FindMonInOTPartyToSwitchIntoBattle();
    }

// skip:
// 'b' contains the PartyNr of the mon the AI will switch to
    // CALL(aLoadEnemyMonToSwitchTo);
    LoadEnemyMonToSwitchTo_Conv(res.a);
    // LD_A(1);
    // LD_addr_A(wEnemyIsSwitching);
    wram->wEnemyIsSwitching = 1;
    // CALL(aClearEnemyMonBox);
    ClearEnemyMonBox_Conv();
    // CALL(aShowBattleTextEnemySentOut);
    ShowBattleTextEnemySentOut();
    // JP(mShowSetEnemyMonAndSendOutAnimation);
    return ShowSetEnemyMonAndSendOutAnimation();
}

void CheckWhetherSwitchmonIsPredetermined(void){
//  returns the enemy switchmon index in b, or
//  returns carry if the index is not yet determined.
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_Z goto not_linked;

    LD_A_addr(wBattleAction);
    SUB_A(BATTLEACTION_SWITCH1);
    LD_B_A;
    goto return_carry;


not_linked:
    LD_A_addr(wEnemySwitchMonIndex);
    AND_A_A;
    IF_Z goto check_wBattleHasJustStarted;

    DEC_A;
    LD_B_A;
    goto return_carry;


check_wBattleHasJustStarted:
    LD_A_addr(wBattleHasJustStarted);
    AND_A_A;
    LD_B(0);
    IF_NZ goto return_carry;

    AND_A_A;
    RET;


return_carry:
    SCF;
    RET;

}

//  returns the enemy switchmon index in b, or
//  returns carry if the index is not yet determined.
u8_flag_s CheckWhetherSwitchmonIsPredetermined_Conv(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;
    if(wram->wLinkMode != 0) {
        // LD_A_addr(wBattleAction);
        // SUB_A(BATTLEACTION_SWITCH1);
        // LD_B_A;
        // goto return_carry;
        return u8_flag(wram->wBattleAction - BATTLEACTION_SWITCH1, true);
    }

// not_linked:
    // LD_A_addr(wEnemySwitchMonIndex);
    // AND_A_A;
    // IF_Z goto check_wBattleHasJustStarted;
    if(wram->wEnemySwitchMonIndex != 0) {
        // DEC_A;
        // LD_B_A;
        // goto return_carry;
        return u8_flag(wram->wEnemySwitchMonIndex - 1, true);
    }


// check_wBattleHasJustStarted:
    // LD_A_addr(wBattleHasJustStarted);
    // AND_A_A;
    // LD_B(0);
    // IF_NZ goto return_carry;
    if(wram->wBattleHasJustStarted != 0) {
        return u8_flag(0, true);
    }

    // AND_A_A;
    // RET;
    return u8_flag(0, false);


// return_carry:
    // SCF;
    // RET;
}

void ResetEnemyBattleVars(void){
//  and draw empty Textbox
    // XOR_A_A;
    // LD_addr_A(wLastPlayerCounterMove);
    wram->wLastPlayerCounterMove = 0;
    // LD_addr_A(wLastEnemyCounterMove);
    wram->wLastEnemyCounterMove = 0;
    // LD_addr_A(wLastEnemyMove);
    wram->wLastEnemyMove = 0;
    // LD_addr_A(wCurEnemyMove);
    wram->wCurEnemyMove = 0;
    // DEC_A;
    // LD_addr_A(wEnemyItemState);
    wram->wEnemyItemState = 0xff;
    // XOR_A_A;
    // LD_addr_A(wPlayerWrapCount);
    wram->wPlayerWrapCount = 0;
    // hlcoord(18, 0, wTilemap);
    // LD_A(8);
    // CALL(aSlideBattlePicOut);
    SlideBattlePicOut_Conv(coord(18, 0, wram->wTilemap), 8);
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // JP(mLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();

}

void ResetBattleParticipants(void){
    // XOR_A_A;
    // LD_addr_A(wBattleParticipantsNotFainted);
    wram->wBattleParticipantsNotFainted = 0;
    // LD_addr_A(wBattleParticipantsIncludingFainted);
    wram->wBattleParticipantsIncludingFainted = 0;
    return AddBattleParticipant();
}

void AddBattleParticipant(void){
    // LD_A_addr(wCurBattleMon);
    // LD_C_A;
    uint8_t c = wram->wCurBattleMon;
    // LD_HL(wBattleParticipantsNotFainted);
    // LD_B(SET_FLAG);
    // PUSH_BC;
    // PREDEF(pSmallFarFlagAction);
    SmallFarFlagAction_Conv(&wram->wBattleParticipantsNotFainted, c, SET_FLAG);
    // POP_BC;
    // LD_HL(wBattleParticipantsIncludingFainted);
    // PREDEF_JUMP(pSmallFarFlagAction);
    return SmallFarFlagAction_Conv(&wram->wBattleParticipantsIncludingFainted, c, SET_FLAG), (void)0;
}

uint8_t FindMonInOTPartyToSwitchIntoBattle(void){
    // LD_B(-1);
    uint8_t b = 0xff;
    // LD_A(0b000001);
    // LD_addr_A(wEnemyEffectivenessVsPlayerMons);
    wram->wEnemyEffectivenessVsPlayerMons[0] = 0b000001;
    // LD_addr_A(wPlayerEffectivenessVsEnemyMons);
    wram->wPlayerEffectivenessVsEnemyMons[0] = 0b000001;

    while(1) {
    // loop:
        // LD_HL(wEnemyEffectivenessVsPlayerMons);
        // SLA_hl;
        wram->wEnemyEffectivenessVsPlayerMons[0] <<= 1;
        // INC_HL;  // wPlayerEffectivenessVsEnemyMons
        // SLA_hl;
        wram->wPlayerEffectivenessVsEnemyMons[0] <<= 1;
        // INC_B;
        ++b;
        // LD_A_addr(wOTPartyCount);
        // CP_A_B;
        // JP_Z (mScoreMonTypeMatchups);
        if(wram->wOTPartyCount == b)
            return ScoreMonTypeMatchups();
        // LD_A_addr(wCurOTMon);
        // CP_A_B;
        // IF_Z goto discourage;
        if(wram->wCurOTMon != b) {
            // LD_HL(wOTPartyMon1HP);
            // PUSH_BC;
            // LD_A_B;
            // CALL(aGetPartyLocation);
            // LD_A_hli;
            // LD_C_A;
            // LD_A_hl;
            // OR_A_C;
            // POP_BC;
            // IF_Z goto discourage;
            if(wram->wOTPartyMon[b].HP != 0) {
                // CALL(aLookUpTheEffectivenessOfEveryMove);
                LookUpTheEffectivenessOfEveryMove(b);
                // CALL(aIsThePlayerMonTypesEffectiveAgainstOTMon);
                IsThePlayerMonTypesEffectiveAgainstOTMon(b);
                // goto loop;
                continue;
            }
        }

    // discourage:
        // LD_HL(wPlayerEffectivenessVsEnemyMons);
        // SET_hl(0);
        bit_set(wram->wPlayerEffectivenessVsEnemyMons[0], 0);
        // goto loop;
    }
}

void LookUpTheEffectivenessOfEveryMove(uint8_t b){
    // PUSH_BC;
    // LD_HL(wOTPartyMon1Moves);
    // LD_A_B;
    // CALL(aGetPartyLocation);
    move_t* moves = wram->wOTPartyMon[b].mon.moves;
    // POP_BC;
    // LD_E(NUM_MOVES + 1);
    uint8_t e = NUM_MOVES + 1;
    uint8_t matchup;

    do {
    // loop:
        // DEC_E;
        // IF_Z goto done;
        if(--e != 0)
            return;
        // LD_A_hli;
        move_t move = *(moves++);
        // AND_A_A;
        // IF_Z goto done;
        if(move == NO_MOVE)
            return;
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // DEC_A;
        // LD_HL(mMoves);
        // LD_BC(MOVE_LENGTH);
        // CALL(aAddNTimes);
        // LD_DE(wEnemyMoveStruct);
        // LD_A(BANK(aMoves));
        // CALL(aFarCopyBytes);
        CopyBytes_Conv2(&wram->wEnemyMoveStruct, Moves + move, sizeof(wram->wEnemyMoveStruct));
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALLFAR(aBattleCheckTypeMatchup);
        matchup = BattleCheckTypeMatchup_Conv();
        // POP_BC;
        // POP_DE;
        // POP_HL;
        // LD_A_addr(wTypeMatchup);
        // CP_A(EFFECTIVE + 1);
        // IF_C goto loop;
    } while(matchup <= EFFECTIVE);
    // LD_HL(wEnemyEffectivenessVsPlayerMons);
    // SET_hl(0);
    bit_set(wram->wEnemyEffectivenessVsPlayerMons[0], 0);
    // RET;
    return;

// done:
    // RET;
}

void IsThePlayerMonTypesEffectiveAgainstOTMon(uint8_t b){
//  Calculates the effectiveness of the types of the PlayerMon
//  against the OTMon
    // PUSH_BC;
    // LD_HL(wOTPartyCount);
    // LD_A_B;
    // INC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // DEC_A;
    species_t species = wram->wOTPartySpecies[b];
    // LD_HL(mBaseData + BASE_TYPES);
    // LD_BC(BASE_DATA_SIZE);
    // CALL(aAddNTimes);
    // LD_DE(wEnemyMonType);
    // LD_BC(BASE_CATCH_RATE - BASE_TYPES);
    // LD_A(BANK(aBaseData));
    // CALL(aFarCopyBytes);
    CopyBytes_Conv2(wram->wEnemyMon.types, BasePokemonData + (species - 1), BASE_CATCH_RATE - BASE_TYPES);
    // LD_A_addr(wBattleMonType1);
    // LD_addr_A(wPlayerMoveStruct + MOVE_TYPE);
    wram->wPlayerMoveStruct.type = wram->wBattleMon.type1;
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // CALLFAR(aBattleCheckTypeMatchup);
    uint8_t matchup = BattleCheckTypeMatchup_Conv();
    // LD_A_addr(wTypeMatchup);
    // CP_A(EFFECTIVE + 1);
    // IF_NC goto super_effective;
    if(matchup <= EFFECTIVE) {
        // LD_A_addr(wBattleMonType2);
        // LD_addr_A(wPlayerMoveStruct + MOVE_TYPE);
        wram->wPlayerMoveStruct.type = wram->wBattleMon.type2;
        // CALLFAR(aBattleCheckTypeMatchup);
        matchup = BattleCheckTypeMatchup_Conv();
        // LD_A_addr(wTypeMatchup);
        // CP_A(EFFECTIVE + 1);
        // IF_NC goto super_effective;
        // POP_BC;
        // RET;
        if(matchup <= EFFECTIVE)
            return;
    }

// super_effective:
    // POP_BC;
    // LD_HL(wEnemyEffectivenessVsPlayerMons);
    // BIT_hl(0);
    // IF_NZ goto reset;
    if(!bit_test(wram->wEnemyEffectivenessVsPlayerMons[0], 0)) {
        // INC_HL;  // wPlayerEffectivenessVsEnemyMons
        // SET_hl(0);
        bit_set(wram->wPlayerEffectivenessVsEnemyMons[0], 0);
        // RET;
        return;
    }
    else {
    // reset:
        // RES_hl(0);
        bit_reset(wram->wEnemyEffectivenessVsPlayerMons[0], 0);
        // RET;
        return;
    }
}

uint8_t ScoreMonTypeMatchups(void){
    uint8_t temp;
    do {
    // loop1:
        // LD_HL(wEnemyEffectivenessVsPlayerMons);
        // SLA_hl;
        wram->wEnemyEffectivenessVsPlayerMons[0] <<= 1;
        // INC_HL;  // wPlayerEffectivenessVsEnemyMons
        // SLA_hl;
        temp = (wram->wPlayerEffectivenessVsEnemyMons[0] >> 7);
        wram->wPlayerEffectivenessVsEnemyMons[0] <<= 1;
        // IF_NC goto loop1;
    } while(!temp);
    // LD_A_addr(wOTPartyCount);
    // LD_B_A;
    uint8_t b = wram->wOTPartyCount;
    // LD_C_hl;
    uint8_t c = wram->wPlayerEffectivenessVsEnemyMons[0];

    while(1) {
    // loop2:
        // SLA_C;
        temp = c >> 7;
        c <<= 1;
        // IF_NC goto okay;
        if(!temp)
            break;
        // DEC_B;
        // IF_Z goto loop5;
        if(--b == 0) {
            uint8_t a;
            do {
            // loop5:
                // LD_A_addr(wOTPartyCount);
                // LD_B_A;
                // CALL(aBattleRandom);
                // AND_A(0x7);
                a = BattleRandom_Conv() & 0x7;
                // CP_A_B;
                // IF_NC goto loop5;
                // LD_B_A;
                // LD_A_addr(wCurOTMon);
                // CP_A_B;
                // IF_Z goto loop5;
                // LD_HL(wOTPartyMon1HP);
                // PUSH_BC;
                // LD_A_B;
                // CALL(aGetPartyLocation);
                // POP_BC;
                // LD_A_hli;
                // LD_C_A;
                // LD_A_hl;
                // OR_A_C;
                // IF_Z goto loop5;
            } while(a >= wram->wOTPartyCount || a == wram->wCurOTMon || wram->wOTPartyMon[a].HP == 0);
            return a;
        }
        // goto loop2;
    }

// okay:
    // LD_A_addr(wEnemyEffectivenessVsPlayerMons);
    // AND_A_A;
    // IF_Z goto okay2;
    if(wram->wEnemyEffectivenessVsPlayerMons[0] != 0) {
        // LD_B(-1);
        b = 0xff;
        // LD_C_A;
        c = wram->wEnemyEffectivenessVsPlayerMons[0];

        do {
        // loop3:
            // INC_B;
            b++;
            // SLA_C;
            temp = (c >> 7);
            c <<= 1;
            // IF_NC goto loop3;
        } while(!temp);
        // goto quit;
        return b;
    }
    else {
    // okay2:
        // LD_B(-1);
        b = 0xff;
        // LD_A_addr(wPlayerEffectivenessVsEnemyMons);
        // LD_C_A;
        c = wram->wPlayerEffectivenessVsEnemyMons[0];

        do {
        // loop4:
            // INC_B;
            b++;
            // SLA_C;
            temp = (c >> 7);
            c <<= 1;
            // IF_C goto loop4;
        } while(temp);
        // goto quit;
        return b;
    }


// quit:
    // RET;
}

void LoadEnemyMonToSwitchTo(void){
// 'b' contains the PartyNr of the mon the AI will switch to
    LD_A_B;
    LD_addr_A(wCurPartyMon);
    LD_HL(wOTPartyMon1Level);
    CALL(aGetPartyLocation);
    LD_A_hl;
    LD_addr_A(wCurPartyLevel);
    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_HL(wOTPartyCount);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempEnemyMonSpecies);
    LD_addr_A(wCurPartySpecies);
    CALL(aLoadEnemyMon);

    LD_A_addr(wCurPartySpecies);
    CP_A(UNOWN);
    IF_NZ goto skip_unown;
    LD_A_addr(wFirstUnownSeen);
    AND_A_A;
    IF_NZ goto skip_unown;
    LD_HL(wEnemyMonDVs);
    PREDEF(pGetUnownLetter);
    LD_A_addr(wUnownLetter);
    LD_addr_A(wFirstUnownSeen);

skip_unown:

    LD_HL(wEnemyMonHP);
    LD_A_hli;
    LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch);
    LD_A_hl;
    LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch + 1);
    RET;

}

void LoadEnemyMonToSwitchTo_Conv(uint8_t b){
// 'b' contains the PartyNr of the mon the AI will switch to
    // LD_A_B;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = b;
    // LD_HL(wOTPartyMon1Level);
    // CALL(aGetPartyLocation);
    struct PartyMon* hl = wram->wOTPartyMon + b;
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = hl->mon.level;
    // LD_A_addr(wCurPartyMon);
    // INC_A;
    // LD_HL(wOTPartyCount);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempEnemyMonSpecies);
    wram->wTempEnemyMonSpecies = wram->wOTPartySpecies[b];
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTPartySpecies[b];
    // CALL(aLoadEnemyMon);
    LoadEnemyMon();

    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_NZ goto skip_unown;
    // LD_A_addr(wFirstUnownSeen);
    // AND_A_A;
    // IF_NZ goto skip_unown;
    if(wram->wCurPartySpecies == UNOWN && wram->wFirstUnownSeen == 0) {
        // LD_HL(wEnemyMonDVs);
        // PREDEF(pGetUnownLetter);
        // LD_A_addr(wUnownLetter);
        // LD_addr_A(wFirstUnownSeen);
        wram->wFirstUnownSeen = GetUnownLetter_Conv(wram->wEnemyMon.dvs);
    }

// skip_unown:
    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch);
    // LD_A_hl;
    // LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch + 1);
    wram->wEnemyHPAtTimeOfPlayerSwitch = wram->wEnemyMon.hp;
    // RET;
}

void CheckWhetherToAskSwitch(void){
    LD_A_addr(wBattleHasJustStarted);
    DEC_A;
    JP_Z (mCheckWhetherToAskSwitch_return_nc);
    LD_A_addr(wPartyCount);
    DEC_A;
    JP_Z (mCheckWhetherToAskSwitch_return_nc);
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mCheckWhetherToAskSwitch_return_nc);
    LD_A_addr(wOptions);
    BIT_A(BATTLE_SHIFT);
    IF_NZ goto return_nc;
    LD_A_addr(wCurPartyMon);
    PUSH_AF;
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wCurPartyMon);
    FARCALL(aCheckCurPartyMonFainted);
    POP_BC;
    LD_A_B;
    LD_addr_A(wCurPartyMon);
    IF_C goto return_nc;
    SCF;
    RET;


return_nc:
    AND_A_A;
    RET;

}

bool CheckWhetherToAskSwitch_Conv(void){
    // LD_A_addr(wBattleHasJustStarted);
    // DEC_A;
    // JP_Z (mCheckWhetherToAskSwitch_return_nc);
    if(wram->wBattleHasJustStarted == TRUE)
        return false;
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // JP_Z (mCheckWhetherToAskSwitch_return_nc);
    if(wram->wPartyCount <= 1)
        return false;
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // JP_NZ (mCheckWhetherToAskSwitch_return_nc);
    if(wram->wLinkMode != 0)
        return false;
    // LD_A_addr(wOptions);
    // BIT_A(BATTLE_SHIFT);
    // IF_NZ goto return_nc;
    if(bit_test(wram->wOptions, BATTLE_SHIFT))
        return false;
    // LD_A_addr(wCurPartyMon);
    // PUSH_AF;
    uint8_t partyMon = wram->wCurPartyMon;
    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wCurBattleMon;
    // FARCALL(aCheckCurPartyMonFainted);
    bool res = CheckCurPartyMonFainted_Conv();
    // POP_BC;
    // LD_A_B;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = partyMon;
    // IF_C goto return_nc;
    if(res) return false;
    // SCF;
    // RET;
    return true;


// return_nc:
    // AND_A_A;
    // RET;
}

void OfferSwitch(void){
    LD_A_addr(wCurPartyMon);
    PUSH_AF;
    CALLFAR(aBattle_GetTrainerName);
    LD_HL(mBattleText_EnemyIsAboutToUseWillPlayerChangeMon);
    CALL(aStdBattleTextbox);
    LD_BC((1 << 8) | 7);
    CALL(aPlaceYesNoBox);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    IF_NZ goto said_no;
    CALL(aSetUpBattlePartyMenu);
    CALL(aPickSwitchMonInBattle);
    IF_C goto canceled_switch;
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wLastPlayerMon);
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadHPBar);
    POP_AF;
    LD_addr_A(wCurPartyMon);
    XOR_A_A;
    LD_addr_A(wCurEnemyMove);
    LD_addr_A(wCurPlayerMove);
    AND_A_A;
    RET;


canceled_switch:
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadHPBar);


said_no:
    POP_AF;
    LD_addr_A(wCurPartyMon);
    SCF;
    RET;

}

// Returns false if player refused or cancelled switch.
bool OfferSwitch_Conv(void){
    // LD_A_addr(wCurPartyMon);
    // PUSH_AF;
    uint8_t cur = wram->wCurPartyMon;
    // CALLFAR(aBattle_GetTrainerName);
    Battle_GetTrainerName_Conv();
    // LD_HL(mBattleText_EnemyIsAboutToUseWillPlayerChangeMon);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_EnemyIsAboutToUseWillPlayerChangeMon);
    // LD_BC((1 << 8) | 7);
    // CALL(aPlaceYesNoBox);
    v_YesNoBox_Conv(1, 7);
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // IF_NZ goto said_no;

    if(wram->wMenuCursorY == 1) {
        // CALL(aSetUpBattlePartyMenu);
        SetUpBattlePartyMenu();
        // CALL(aPickSwitchMonInBattle);
        // IF_C goto canceled_switch;
        bool cancel = PickSwitchMonInBattle();
        if(!cancel) {
            // LD_A_addr(wCurBattleMon);
            // LD_addr_A(wLastPlayerMon);
            wram->wLastPlayerMon = wram->wCurBattleMon;
            // LD_A_addr(wCurPartyMon);
            // LD_addr_A(wCurBattleMon);
            wram->wCurBattleMon = wram->wCurPartyMon;
            // CALL(aClearPalettes);
            ClearPalettes_Conv();
            // CALL(aDelayFrame);
            DelayFrame();
            // CALL(av_LoadHPBar);
            v_LoadHPBar_Conv();
            // POP_AF;
            // LD_addr_A(wCurPartyMon);
            wram->wCurPartyMon = cur;
            // XOR_A_A;
            // LD_addr_A(wCurEnemyMove);
            wram->wCurEnemyMove = NO_MOVE;
            // LD_addr_A(wCurPlayerMove);
            wram->wCurPlayerMove = NO_MOVE;
            // AND_A_A;
            // RET;
            return true;
        }

    // canceled_switch:
        // CALL(aClearPalettes);
        ClearPalettes_Conv();
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(av_LoadHPBar);
        v_LoadHPBar_Conv();
    }

// said_no:
    // POP_AF;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = cur;
    // SCF;
    // RET;
    return false;
}

void ClearEnemyMonBox(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aExitMenu);
    CALL(aClearSprites);
    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 10);
    CALL(aClearBox);
    CALL(aWaitBGMap);
    JP(mFinishBattleAnim);

}

void ClearEnemyMonBox_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // hlcoord(1, 0, wTilemap);
    // LD_BC((4 << 8) | 10);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 0, wram->wTilemap), 10, 4);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // JP(mFinishBattleAnim);
    return FinishBattleAnim();
}

void ShowBattleTextEnemySentOut(void){
    PEEK("");
    // CALLFAR(aBattle_GetTrainerName);
    Battle_GetTrainerName_Conv();
    // LD_HL(mBattleText_EnemySentOut);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_EnemySentOut);
    // JP(mWaitBGMap);
    return WaitBGMap_Conv();

}

void ShowSetEnemyMonAndSendOutAnimation(void){
    PEEK("");
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempEnemyMonSpecies;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wTempEnemyMonSpecies;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wTempEnemyMonSpecies);
    // LD_A(OTPARTYMON);
    // LD_addr_A(wMonType);
    wram->wMonType = OTPARTYMON;
    // PREDEF(pCopyMonToTempMon);
    CopyMonToTempMon_Conv();
    // CALL(aGetEnemyMonFrontpic);
    GetEnemyMonFrontpic();

    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0;
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // LD_DE(ANIM_SEND_OUT_MON);
    // CALL(aCall_PlayBattleAnim);
    Call_PlayBattleAnim_Conv(ANIM_SEND_OUT_MON);

    // CALL(aBattleCheckEnemyShininess);
    // IF_NC goto not_shiny;
    if(BattleCheckEnemyShininess_Conv()) {
        // LD_A(1);  // shiny anim
        // LD_addr_A(wBattleAnimParam);
        wram->wBattleAnimParam = 1;
        // LD_DE(ANIM_SEND_OUT_MON);
        // CALL(aCall_PlayBattleAnim);
        Call_PlayBattleAnim_Conv(ANIM_SEND_OUT_MON);
    }

// not_shiny:
    // LD_BC(wTempMonSpecies);
    // FARCALL(aCheckFaintedFrzSlp);
    // IF_C goto skip_cry;
    if(!CheckFaintedFrzSlp_Conv(&wram->wTempMon)) {
        // FARCALL(aCheckBattleScene);
        // IF_C goto cry_no_anim;
        if(CheckBattleScene_Conv()) {

            // hlcoord(12, 0, wTilemap);
            // LD_D(0x0);
            // LD_E(ANIM_MON_SLOW);
            // PREDEF(pAnimateFrontpic);
            AnimateFrontpic_Conv(coord(12, 0, wram->wTilemap), 0x0, ANIM_MON_SLOW);
            // goto skip_cry;
        }
        else {
        // cry_no_anim:
            // LD_A(0xf);
            // LD_addr_A(wCryTracks);
            wram->wCryTracks = 0xf;
            // LD_A_addr(wTempEnemyMonSpecies);
            // CALL(aPlayStereoCry);
            PlayStereoCry_Conv(wram->wTempEnemyMonSpecies);
        }
    }

// skip_cry:
    // CALL(aUpdateEnemyHUD);
    UpdateEnemyHUD();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // RET;
}

void NewEnemyMonStatus(void){
    XOR_A_A;
    LD_addr_A(wLastPlayerCounterMove);
    LD_addr_A(wLastEnemyCounterMove);
    LD_addr_A(wLastEnemyMove);
    LD_HL(wEnemySubStatus1);
    for(int rept = 0; rept < 4; rept++){
    LD_hli_A;
    }
    LD_hl_A;
    LD_addr_A(wEnemyDisableCount);
    LD_addr_A(wEnemyFuryCutterCount);
    LD_addr_A(wEnemyProtectCount);
    LD_addr_A(wEnemyRageCounter);
    LD_addr_A(wEnemyDisabledMove);
    LD_addr_A(wEnemyMinimized);
    LD_addr_A(wPlayerWrapCount);
    LD_addr_A(wEnemyWrapCount);
    LD_addr_A(wEnemyTurnsTaken);
    LD_HL(wPlayerSubStatus5);
    RES_hl(SUBSTATUS_CANT_RUN);
    RET;

}

void NewEnemyMonStatus_Conv(void){
    // XOR_A_A;
    // LD_addr_A(wLastPlayerCounterMove);
    wram->wLastPlayerCounterMove = NO_MOVE;
    // LD_addr_A(wLastEnemyCounterMove);
    wram->wLastEnemyCounterMove = NO_MOVE;
    // LD_addr_A(wLastEnemyMove);
    wram->wLastEnemyMove = NO_MOVE;
    // LD_HL(wEnemySubStatus1);
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    wram->wEnemySubStatus1 = 0;
    wram->wEnemySubStatus2 = 0;
    wram->wEnemySubStatus3 = 0;
    wram->wEnemySubStatus4 = 0;
    // LD_hl_A;
    wram->wEnemySubStatus5 = 0;
    // LD_addr_A(wEnemyDisableCount);
    wram->wEnemyDisableCount = 0;
    // LD_addr_A(wEnemyFuryCutterCount);
    wram->wEnemyFuryCutterCount = 0;
    // LD_addr_A(wEnemyProtectCount);
    wram->wEnemyProtectCount = 0;
    // LD_addr_A(wEnemyRageCounter);
    wram->wEnemyRageCounter = 0;
    // LD_addr_A(wEnemyDisabledMove);
    wram->wEnemyDisabledMove = NO_MOVE;
    // LD_addr_A(wEnemyMinimized);
    wram->wEnemyMinimized = FALSE;
    // LD_addr_A(wPlayerWrapCount);
    wram->wPlayerWrapCount = 0;
    // LD_addr_A(wEnemyWrapCount);
    wram->wEnemyWrapCount = 0;
    // LD_addr_A(wEnemyTurnsTaken);
    wram->wEnemyTurnsTaken = 0;
    // LD_HL(wPlayerSubStatus5);
    // RES_hl(SUBSTATUS_CANT_RUN);
    bit_reset(wram->wPlayerSubStatus5, SUBSTATUS_CANT_RUN);
    // RET;
}

void ResetEnemyStatLevels(void){
    LD_A(BASE_STAT_LEVEL);
    LD_B(NUM_LEVEL_STATS);
    LD_HL(wEnemyStatLevels);

loop:
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void ResetEnemyStatLevels_Conv(void){
    // LD_A(BASE_STAT_LEVEL);
    // LD_B(NUM_LEVEL_STATS);
    // LD_HL(wEnemyStatLevels);

    for(int i = 0; i < NUM_LEVEL_STATS; ++i) {
    // loop:
        // LD_hli_A;
        // DEC_B;
        // IF_NZ goto loop;
        wram->wEnemyStatLevels[i] = BASE_STAT_LEVEL;
    }
    // RET;
}

void CheckPlayerPartyForFitMon(void){
//  Has the player any mon in his Party that can fight?
    LD_A_addr(wPartyCount);
    LD_E_A;
    XOR_A_A;
    LD_HL(wPartyMon1HP);
    LD_BC(PARTYMON_STRUCT_LENGTH - 1);

loop:
    OR_A_hl;
    INC_HL;  // + 1
    OR_A_hl;
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    LD_D_A;
    RET;

}

//  Has the player any mon in his Party that can fight?
bool CheckPlayerPartyForFitMon_Conv(void){
    // LD_A_addr(wPartyCount);
    // LD_E_A;
    uint8_t e = wram->wPartyCount;
    // XOR_A_A;
    // LD_HL(wPartyMon1HP);
    struct PartyMon* hl = wram->wPartyMon;
    // LD_BC(PARTYMON_STRUCT_LENGTH - 1);
    uint16_t a = 0;

    do {
    // loop:
        // OR_A_hl;
        // INC_HL;  // + 1
        // OR_A_hl;
        a |= hl->HP;
        // ADD_HL_BC;
        hl++;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // LD_D_A;
    // RET;
    return a != 0;
}

void CheckIfCurPartyMonIsFitToFight(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1HP);
    CALL(aGetPartyLocation);
    LD_A_hli;
    OR_A_hl;
    RET_NZ ;

    LD_A_addr(wBattleHasJustStarted);
    AND_A_A;
    IF_NZ goto finish_fail;
    LD_HL(wPartySpecies);
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(EGG);
    LD_HL(mBattleText_AnEGGCantBattle);
    IF_Z goto print_textbox;

    LD_HL(mBattleText_TheresNoWillToBattle);


print_textbox:
    CALL(aStdBattleTextbox);


finish_fail:
    XOR_A_A;
    RET;

}

bool CheckIfCurPartyMonIsFitToFight_Conv(void){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1HP);
    // CALL(aGetPartyLocation);
    // LD_A_hli;
    // OR_A_hl;
    // RET_NZ ;
    if(wram->wPartyMon[wram->wCurPartyMon].HP != 0 && wram->wPartySpecies[wram->wCurPartyMon] != EGG)
        return true;

    // LD_A_addr(wBattleHasJustStarted);
    // AND_A_A;
    // IF_NZ goto finish_fail;
    if(wram->wBattleHasJustStarted != 0)
        return false;

    // LD_HL(wPartySpecies);
    // LD_A_addr(wCurPartyMon);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(EGG);
    // LD_HL(mBattleText_AnEGGCantBattle);
    // IF_Z goto print_textbox;
    if(wram->wPartySpecies[wram->wCurPartyMon] == EGG) {
        StdBattleTextbox_Conv2(BattleText_AnEGGCantBattle);
    }
    else {
        // LD_HL(mBattleText_TheresNoWillToBattle);
        StdBattleTextbox_Conv2(BattleText_TheresNoWillToBattle);
    }

// print_textbox:
    // CALL(aStdBattleTextbox);


// finish_fail:
    // XOR_A_A;
    // RET;
    return false;
}

void TryToRunAwayFromBattle(void){
//  Run away from battle, with or without item
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_DEBUG);
    JP_Z (mTryToRunAwayFromBattle_can_escape);
    CP_A(BATTLETYPE_CONTEST);
    JP_Z (mTryToRunAwayFromBattle_can_escape);
    CP_A(BATTLETYPE_TRAP);
    JP_Z (mTryToRunAwayFromBattle_cant_escape);
    CP_A(BATTLETYPE_CELEBI);
    JP_Z (mTryToRunAwayFromBattle_cant_escape);
    CP_A(BATTLETYPE_SHINY);
    JP_Z (mTryToRunAwayFromBattle_cant_escape);
    CP_A(BATTLETYPE_SUICUNE);
    JP_Z (mTryToRunAwayFromBattle_cant_escape);

    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mTryToRunAwayFromBattle_can_escape);

    LD_A_addr(wBattleMode);
    DEC_A;
    JP_NZ (mTryToRunAwayFromBattle_cant_run_from_trainer);

    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    JP_NZ (mTryToRunAwayFromBattle_cant_escape);

    LD_A_addr(wPlayerWrapCount);
    AND_A_A;
    JP_NZ (mTryToRunAwayFromBattle_cant_escape);

    PUSH_HL;
    PUSH_DE;
    LD_A_addr(wBattleMonItem);
    LD_addr_A(wNamedObjectIndex);
    LD_B_A;
    CALLFAR(aGetItemHeldEffect);
    LD_A_B;
    CP_A(HELD_ESCAPE);
    POP_DE;
    POP_HL;
    IF_NZ goto no_flee_item;

    CALL(aSetPlayerTurn);
    CALL(aGetItemName);
    LD_HL(mBattleText_UserFledUsingAStringBuffer1);
    CALL(aStdBattleTextbox);
    JP(mTryToRunAwayFromBattle_can_escape);


no_flee_item:
    LD_A_addr(wNumFleeAttempts);
    INC_A;
    LD_addr_A(wNumFleeAttempts);
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hl;
    LDH_addr_A(hMultiplicand + 2);
    LD_A_de;
    INC_DE;
    LDH_addr_A(hEnemyMonSpeed + 0);
    LD_A_de;
    LDH_addr_A(hEnemyMonSpeed + 1);
    CALL(aSafeLoadTempTilemapToTilemap);
    LD_DE(hMultiplicand + 1);
    LD_HL(hEnemyMonSpeed);
    LD_C(2);
    CALL(aCompareBytes);
    IF_NC goto can_escape;

    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A(32);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LDH_A_addr(hProduct + 2);
    LDH_addr_A(hDividend + 0);
    LDH_A_addr(hProduct + 3);
    LDH_addr_A(hDividend + 1);
    LDH_A_addr(hEnemyMonSpeed + 0);
    LD_B_A;
    LDH_A_addr(hEnemyMonSpeed + 1);
    SRL_B;
    RR_A;
    SRL_B;
    RR_A;
    AND_A_A;
    IF_Z goto can_escape;
    LDH_addr_A(hDivisor);
    LD_B(2);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 2);
    AND_A_A;
    IF_NZ goto can_escape;
    LD_A_addr(wNumFleeAttempts);
    LD_C_A;

loop:
    DEC_C;
    IF_Z goto cant_escape_2;
    LD_B(30);
    LDH_A_addr(hQuotient + 3);
    ADD_A_B;
    LDH_addr_A(hQuotient + 3);
    IF_C goto can_escape;
    goto loop;


cant_escape_2:
    CALL(aBattleRandom);
    LD_B_A;
    LDH_A_addr(hQuotient + 3);
    CP_A_B;
    IF_NC goto can_escape;
    LD_A(BATTLEPLAYERACTION_USEITEM);
    LD_addr_A(wBattlePlayerAction);
    LD_HL(mBattleText_CantEscape2);
    goto print_inescapable_text;


cant_escape:
    LD_HL(mBattleText_CantEscape);
    goto print_inescapable_text;


cant_run_from_trainer:
    LD_HL(mBattleText_TheresNoEscapeFromTrainerBattle);


print_inescapable_text:
    CALL(aStdBattleTextbox);
    LD_A(TRUE);
    LD_addr_A(wFailedToFlee);
    CALL(aLoadTilemapToTempTilemap);
    AND_A_A;
    RET;


can_escape:
    LD_A_addr(wLinkMode);
    AND_A_A;
    LD_A(DRAW);
    IF_Z goto fled;
    CALL(aLoadTilemapToTempTilemap);
    XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
    LD_addr_A(wBattlePlayerAction);
    LD_A(0xf);
    LD_addr_A(wCurMoveNum);
    XOR_A_A;
    LD_addr_A(wCurPlayerMove);
    CALL(aLinkBattleSendReceiveAction);
    CALL(aSafeLoadTempTilemapToTilemap);
    CALL(aCheckMobileBattleError);
    IF_C goto mobile;

// Got away safely
    LD_A_addr(wBattleAction);
    CP_A(BATTLEACTION_FORFEIT);
    LD_A(DRAW);
    IF_Z goto fled;
    DEC_A;  // LOSE

fled:
    LD_B_A;
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    ADD_A_B;
    LD_addr_A(wBattleResult);
    CALL(aStopDangerSound);
    PUSH_DE;
    LD_DE(SFX_RUN);
    CALL(aWaitPlaySFX);
    POP_DE;
    CALL(aWaitSFX);
    LD_HL(mBattleText_GotAwaySafely);
    CALL(aStdBattleTextbox);
    CALL(aWaitSFX);
    CALL(aLoadTilemapToTempTilemap);
    SCF;
    RET;


mobile:
    CALL(aStopDangerSound);
    LD_HL(wcd2a);
    BIT_hl(4);
    IF_NZ goto skip_link_error;
    LD_HL(mBattleText_LinkErrorBattleCanceled);
    CALL(aStdBattleTextbox);


skip_link_error:
    CALL(aWaitSFX);
    CALL(aLoadTilemapToTempTilemap);
    SCF;
    RET;

}

static bool TryToRunAwayFromBattle_print_inescapable_text(const struct TextCmd* hl) {
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(hl);
    // LD_A(TRUE);
    // LD_addr_A(wFailedToFlee);
    wram->wFailedToFlee = TRUE;
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // AND_A_A;
    // RET;
    return false;
}

static bool TryToRunAwayFromBattle_cant_escape(void) {
// cant_escape:
    // LD_HL(mBattleText_CantEscape);
    // goto print_inescapable_text;
    return TryToRunAwayFromBattle_print_inescapable_text(BattleText_CantEscape);
}

static bool TryToRunAwayFromBattle_cant_run_from_trainer(void) {
    // LD_HL(mBattleText_TheresNoEscapeFromTrainerBattle);
    return TryToRunAwayFromBattle_print_inescapable_text(BattleText_TheresNoEscapeFromTrainerBattle);
}

static bool TryToRunAwayFromBattle_can_escape(void) {
// can_escape:
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // LD_A(DRAW);
    // IF_Z goto fled;
    uint8_t result = DRAW;
    if(wram->wLinkMode != 0) {
        // CALL(aLoadTilemapToTempTilemap);
        LoadTilemapToTempTilemap_Conv();
        // XOR_A_A;  // BATTLEPLAYERACTION_USEMOVE
        // LD_addr_A(wBattlePlayerAction);
        wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEMOVE;
        // LD_A(0xf);
        // LD_addr_A(wCurMoveNum);
        wram->wCurMoveNum = 0xf;
        // XOR_A_A;
        // LD_addr_A(wCurPlayerMove);
        wram->wCurPlayerMove = 0;
        // CALL(aLinkBattleSendReceiveAction);
        LinkBattleSendReceiveAction();
        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap_Conv();
        // CALL(aCheckMobileBattleError);
        // IF_C goto mobile;
        if(CheckMobileBattleError_Conv()) {
        // mobile:
            // CALL(aStopDangerSound);
            StopDangerSound();
            // LD_HL(wcd2a);
            // BIT_hl(4);
            // IF_NZ goto skip_link_error;
            if(!bit_test(wram->wcd2a, 4)) {
                // LD_HL(mBattleText_LinkErrorBattleCanceled);
                // CALL(aStdBattleTextbox);
                StdBattleTextbox_Conv2(BattleText_LinkErrorBattleCanceled);
            }
        // skip_link_error:
            // CALL(aWaitSFX);
            WaitSFX_Conv();
            // CALL(aLoadTilemapToTempTilemap);
            LoadTilemapToTempTilemap_Conv();
            // SCF;
            // RET;
            return true;
        }

    // Got away safely
        // LD_A_addr(wBattleAction);
        // CP_A(BATTLEACTION_FORFEIT);
        // LD_A(DRAW);
        // IF_Z goto fled;
        // DEC_A;  // LOSE
        result = (wram->wBattleAction == BATTLEACTION_FORFEIT)? DRAW: LOSE;
    }
// fled:
    // LD_B_A;
    // LD_A_addr(wBattleResult);
    // AND_A(BATTLERESULT_BITMASK);
    // ADD_A_B;
    // LD_addr_A(wBattleResult);
    wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) + result;
    // CALL(aStopDangerSound);
    StopDangerSound();
    // PUSH_DE;
    // LD_DE(SFX_RUN);
    // CALL(aWaitPlaySFX);
    WaitPlaySFX_Conv(SFX_RUN);
    // POP_DE;
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_HL(mBattleText_GotAwaySafely);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_GotAwaySafely);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // SCF;
    // RET;
    return true;
}

//  Run away from battle, with or without item
//  Returns true if escape was successful.
bool TryToRunAwayFromBattle_Conv(const struct BattleMon* hl, const struct BattleMon* de){
    // LD_A_addr(wBattleType);
    switch(wram->wBattleType) {
        // CP_A(BATTLETYPE_DEBUG);
        // JP_Z (mTryToRunAwayFromBattle_can_escape);
        // CP_A(BATTLETYPE_CONTEST);
        // JP_Z (mTryToRunAwayFromBattle_can_escape);
        case BATTLETYPE_DEBUG:
        case BATTLETYPE_CONTEST:
            return TryToRunAwayFromBattle_can_escape();
        // CP_A(BATTLETYPE_TRAP);
        // JP_Z (mTryToRunAwayFromBattle_cant_escape);
        // CP_A(BATTLETYPE_CELEBI);
        // JP_Z (mTryToRunAwayFromBattle_cant_escape);
        // CP_A(BATTLETYPE_SHINY);
        // JP_Z (mTryToRunAwayFromBattle_cant_escape);
        // CP_A(BATTLETYPE_SUICUNE);
        // JP_Z (mTryToRunAwayFromBattle_cant_escape);
        case BATTLETYPE_TRAP:
        case BATTLETYPE_CELEBI:
        case BATTLETYPE_SHINY:
        case BATTLETYPE_SUICUNE:
            return TryToRunAwayFromBattle_cant_escape();
        
        default:
            break;
    }

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // JP_NZ (mTryToRunAwayFromBattle_can_escape);
    if(wram->wLinkMode != 0)
        return TryToRunAwayFromBattle_can_escape();

    // LD_A_addr(wBattleMode);
    // DEC_A;
    // JP_NZ (mTryToRunAwayFromBattle_cant_run_from_trainer);
    if(wram->wBattleMode == TRAINER_BATTLE)
        return TryToRunAwayFromBattle_cant_run_from_trainer();

    // LD_A_addr(wEnemySubStatus5);
    // BIT_A(SUBSTATUS_CANT_RUN);
    // JP_NZ (mTryToRunAwayFromBattle_cant_escape);

    // LD_A_addr(wPlayerWrapCount);
    // AND_A_A;
    // JP_NZ (mTryToRunAwayFromBattle_cant_escape);
    if(bit_test(wram->wEnemySubStatus5, SUBSTATUS_CANT_RUN) || wram->wPlayerWrapCount != 0)
        return TryToRunAwayFromBattle_cant_escape();

    // PUSH_HL;
    // PUSH_DE;
    // LD_A_addr(wBattleMonItem);
    // LD_addr_A(wNamedObjectIndex);
    // LD_B_A;
    // CALLFAR(aGetItemHeldEffect);
    uint16_t effect = GetItemHeldEffect_Conv(wram->wBattleMon.item);
    // LD_A_B;
    // CP_A(HELD_ESCAPE);
    // POP_DE;
    // POP_HL;
    // IF_NZ goto no_flee_item;
    if(HIGH(effect) == HELD_ESCAPE) {
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALL(aGetItemName);
        GetItemName_Conv2(wram->wBattleMon.item);
        // LD_HL(mBattleText_UserFledUsingAStringBuffer1);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(BattleText_UserFledUsingAStringBuffer1);
        // JP(mTryToRunAwayFromBattle_can_escape);
        return TryToRunAwayFromBattle_can_escape();
    }

// no_flee_item:
    // LD_A_addr(wNumFleeAttempts);
    // INC_A;
    // LD_addr_A(wNumFleeAttempts);
    wram->wNumFleeAttempts++;
    // LD_A_hli;
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hl;
    // LDH_addr_A(hMultiplicand + 2);
    // LD_A_de;
    // INC_DE;
    // LDH_addr_A(hEnemyMonSpeed + 0);
    // LD_A_de;
    // LDH_addr_A(hEnemyMonSpeed + 1);
    // CALL(aSafeLoadTempTilemapToTilemap);
    SafeLoadTempTilemapToTilemap_Conv();
    uint16_t a_speed = hl->speed[1] | (hl->speed[0] << 8);
    uint16_t b_speed = de->speed[1] | (de->speed[0] << 8);
    // LD_DE(hMultiplicand + 1);
    // LD_HL(hEnemyMonSpeed);
    // LD_C(2);
    // CALL(aCompareBytes);
    // IF_NC goto can_escape;
    if(a_speed >= b_speed)
        return TryToRunAwayFromBattle_can_escape();

    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LD_A(32);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    a_speed *= 32;
    // LDH_A_addr(hProduct + 2);
    // LDH_addr_A(hDividend + 0);
    // LDH_A_addr(hProduct + 3);
    // LDH_addr_A(hDividend + 1);
    // LDH_A_addr(hEnemyMonSpeed + 0);
    // LD_B_A;
    // LDH_A_addr(hEnemyMonSpeed + 1);
    // SRL_B;
    // RR_A;
    // SRL_B;
    // RR_A;
    b_speed /= 4;
    // AND_A_A;
    // IF_Z goto can_escape;
    if(b_speed == 0)
        return TryToRunAwayFromBattle_can_escape();
    // LDH_addr_A(hDivisor);
    // LD_B(2);
    // CALL(aDivide);
    uint16_t odds = a_speed / b_speed;
    // LDH_A_addr(hQuotient + 2);
    // AND_A_A;
    // IF_NZ goto can_escape;
    if(odds > 255)
        return TryToRunAwayFromBattle_can_escape();
    // LD_A_addr(wNumFleeAttempts);
    // LD_C_A;
    uint8_t c = wram->wNumFleeAttempts;

    while(--c != 0) {
    // loop:
        // DEC_C;
        // IF_Z goto cant_escape_2;
        // LD_B(30);
        // LDH_A_addr(hQuotient + 3);
        // ADD_A_B;
        // LDH_addr_A(hQuotient + 3);
        odds += 30;
        // IF_C goto can_escape;
        if(odds > 255)
            return TryToRunAwayFromBattle_can_escape();
        // goto loop;
    }


// cant_escape_2:
    // CALL(aBattleRandom);
    // LD_B_A;
    // LDH_A_addr(hQuotient + 3);
    // CP_A_B;
    // IF_NC goto can_escape;
    if(BattleRandom_Conv() < odds)
        return TryToRunAwayFromBattle_can_escape();
    // LD_A(BATTLEPLAYERACTION_USEITEM);
    // LD_addr_A(wBattlePlayerAction);
    wram->wBattlePlayerAction = BATTLEPLAYERACTION_USEITEM;
    // LD_HL(mBattleText_CantEscape2);
    return TryToRunAwayFromBattle_print_inescapable_text(BattleText_CantEscape2);
}

void InitBattleMon(void){
    // LD_A(MON_SPECIES);
    // CALL(aGetPartyParamLocation);
    struct PartyMon* const hl = &wram->wPartyMon[wram->wCurPartyMon];
    // LD_DE(wBattleMonSpecies);
    // LD_BC(MON_ID);
    // CALL(aCopyBytes);
    wram->wBattleMon.species = hl->mon.species;
    wram->wBattleMon.item = hl->mon.item;
    CopyBytes_Conv2(&wram->wBattleMon.moves, &hl->mon.moves, NUM_MOVES * sizeof(move_t));
    // LD_BC(MON_DVS - MON_ID);
    // ADD_HL_BC;
    // LD_DE(wBattleMonDVs);
    // LD_BC(MON_POKERUS - MON_DVS);
    // CALL(aCopyBytes);
    wram->wBattleMon.dvs = wram->wPartyMon[wram->wCurPartyMon].mon.DVs;
    CopyBytes_Conv2(&wram->wBattleMon.pp, &wram->wPartyMon[wram->wCurPartyMon].mon.PP, NUM_MOVES);
    wram->wBattleMon.happiness = wram->wPartyMon[wram->wCurPartyMon].mon.happiness;
    // INC_HL;
    // INC_HL;
    // INC_HL;
    // LD_DE(wBattleMonLevel);
    // LD_BC(PARTYMON_STRUCT_LENGTH - MON_LEVEL);
    // CALL(aCopyBytes);
    wram->wBattleMon.level = hl->mon.level;
    wram->wBattleMon.status[0] = hl->status;
    wram->wBattleMon.status[1] = hl->unused;
    wram->wBattleMon.hp = hl->HP;
    wram->wBattleMon.maxHP = hl->maxHP;
    CopyBytes_Conv2(wram->wBattleMon.stats, hl->stats, sizeof(wram->wBattleMon.stats));
    // LD_A_addr(wBattleMonSpecies);
    // LD_addr_A(wTempBattleMonSpecies);
    wram->wTempBattleMonSpecies = wram->wBattleMon.species;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wBattleMon.species;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wBattleMon.species;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wBattleMon.species);
    // LD_A_addr(wBaseType1);
    // LD_addr_A(wBattleMonType1);
    wram->wBattleMon.type1 = wram->wBaseType1;
    // LD_A_addr(wBaseType2);
    // LD_addr_A(wBattleMonType2);
    wram->wBattleMon.type2 = wram->wBaseType2;
    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wCurBattleMon);
    // CALL(aSkipNames);
    // LD_DE(wBattleMonNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wBattleMonNickname, wram->wPartyMonNickname[wram->wCurBattleMon], MON_NAME_LENGTH);
    // LD_HL(wBattleMonAttack);
    // LD_DE(wPlayerStats);
    // LD_BC(PARTYMON_STRUCT_LENGTH - MON_ATK);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wPlayerAttack, &wram->wBattleMon.attack, PARTYMON_STRUCT_LENGTH - MON_ATK);
    // CALL(aApplyStatusEffectOnPlayerStats);
    ApplyStatusEffectOnPlayerStats();
    // CALL(aBadgeStatBoosts);
    BadgeStatBoosts();
    // RET;
}

void BattleCheckPlayerShininess(void){
    CALL(aGetPartyMonDVs);
    JR(mBattleCheckShininess);

}

bool BattleCheckPlayerShininess_Conv(void){
    // CALL(aGetPartyMonDVs);
    // JR(mBattleCheckShininess);
    return BattleCheckShininess_Conv(GetPartyMonDVs_Conv());
}

void BattleCheckEnemyShininess(void){
    CALL(aGetEnemyMonDVs);

    return BattleCheckShininess();
}

bool BattleCheckEnemyShininess_Conv(void){
    // CALL(aGetEnemyMonDVs);

    return BattleCheckShininess_Conv(GetEnemyMonDVs_Conv());
}

void BattleCheckShininess(void){
    LD_B_H;
    LD_C_L;
    CALLFAR(aCheckShininess);
    RET;

}

bool BattleCheckShininess_Conv(uint16_t dvs){
    // LD_B_H;
    // LD_C_L;
    // CALLFAR(aCheckShininess);
    // RET;
    return CheckShininess_Conv(dvs);
}

void GetPartyMonDVs(void){
    LD_HL(wBattleMonDVs);
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    RET_Z ;
    LD_HL(wPartyMon1DVs);
    LD_A_addr(wCurBattleMon);
    JP(mGetPartyLocation);

}

uint16_t GetPartyMonDVs_Conv(void){
    // LD_HL(wBattleMonDVs);
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_TRANSFORMED);
    // RET_Z ;
    if(!bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TRANSFORMED))
        return wram->wBattleMon.dvs;
    // LD_HL(wPartyMon1DVs);
    // LD_A_addr(wCurBattleMon);
    // JP(mGetPartyLocation);
    return wram->wPartyMon[wram->wCurBattleMon].mon.DVs;
}

void GetEnemyMonDVs(void){
    LD_HL(wEnemyMonDVs);
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    RET_Z ;
    LD_HL(wEnemyBackupDVs);
    LD_A_addr(wBattleMode);
    DEC_A;
    RET_Z ;
    LD_HL(wOTPartyMon1DVs);
    LD_A_addr(wCurOTMon);
    JP(mGetPartyLocation);

}

uint16_t GetEnemyMonDVs_Conv(void){
    // LD_HL(wEnemyMonDVs);
    // LD_A_addr(wEnemySubStatus5);
    // BIT_A(SUBSTATUS_TRANSFORMED);
    // RET_Z ;
    if(!bit_test(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED))
        return wram->wEnemyMon.dvs;
    // LD_HL(wEnemyBackupDVs);
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // RET_Z ;
    if(wram->wBattleMode == WILD_BATTLE)
        return wram->wEnemyBackupDVs;
    // LD_HL(wOTPartyMon1DVs);
    // LD_A_addr(wCurOTMon);
    // JP(mGetPartyLocation);
    return wram->wOTPartyMon[wram->wCurOTMon].mon.DVs;
}

void ResetPlayerStatLevels(void){
    // LD_A(BASE_STAT_LEVEL);
    // LD_B(NUM_LEVEL_STATS);
    // LD_HL(wPlayerStatLevels);

    for(uint8_t i = 0; i < NUM_LEVEL_STATS; ++i) {
    // loop:
        // LD_hli_A;
        wram->wPlayerStatLevels[i] = BASE_STAT_LEVEL;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // RET;
}

void InitEnemyMon(void){
    PEEK("");
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wOTPartyMon1Species);
    // CALL(aGetPartyLocation);
    // LD_DE(wEnemyMonSpecies);
    // LD_BC(MON_ID);
    // CALL(aCopyBytes);
    wram->wEnemyMon.species = wram->wOTPartyMon[wram->wCurPartyMon].mon.species;
    wram->wEnemyMon.item = wram->wOTPartyMon[wram->wCurPartyMon].mon.item;
    CopyBytes_Conv2(wram->wEnemyMon.moves, &wram->wOTPartyMon[wram->wCurPartyMon].mon.moves, NUM_MOVES * sizeof(move_t));
    for(int i = 0; i < NUM_MOVES; ++i) {
        printf("Move %d = %02X\n", i, wram->wEnemyMon.moves[i]);
    }
    // LD_BC(MON_DVS - MON_ID);
    // ADD_HL_BC;
    // LD_DE(wEnemyMonDVs);
    // LD_BC(MON_POKERUS - MON_DVS);
    // CALL(aCopyBytes);
    wram->wEnemyMon.dvs = wram->wOTPartyMon[wram->wCurPartyMon].mon.DVs;
    CopyBytes_Conv2(wram->wEnemyMon.pp, wram->wOTPartyMon[wram->wCurPartyMon].mon.PP, NUM_MOVES * sizeof(move_t));
    wram->wEnemyMon.happiness = wram->wOTPartyMon[wram->wCurPartyMon].mon.happiness;
    // INC_HL;
    // INC_HL;
    // INC_HL;
    // LD_DE(wEnemyMonLevel);
    // LD_BC(PARTYMON_STRUCT_LENGTH - MON_LEVEL);
    // CALL(aCopyBytes);
    wram->wEnemyMon.level = wram->wOTPartyMon[wram->wCurPartyMon].mon.level;
    CopyBytes_Conv2(wram->wEnemyMon.status, &wram->wOTPartyMon[wram->wCurPartyMon].status, PARTYMON_STRUCT_LENGTH - MON_STATUS);
    // LD_A_addr(wEnemyMonSpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wEnemyMon.species;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wEnemyMon.species);
    // LD_HL(wOTPartyMonNicknames);
    // LD_A_addr(wCurPartyMon);
    // CALL(aSkipNames);
    // LD_DE(wEnemyMonNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wEnemyMonNickname, wram->wOTPartyMonNickname[wram->wCurPartyMon], MON_NAME_LENGTH);
    // LD_HL(wEnemyMonAttack);
    // LD_DE(wEnemyStats);
    // LD_BC(PARTYMON_STRUCT_LENGTH - MON_ATK);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wEnemyStats, wram->wEnemyMon.stats, sizeof(wram->wEnemyStats));
    // CALL(aApplyStatusEffectOnEnemyStats);
    ApplyStatusEffectOnEnemyStats();
    // LD_HL(wBaseType1);
    // LD_DE(wEnemyMonType1);
    // LD_A_hli;
    // LD_de_A;
    wram->wEnemyMon.type1 = wram->wBaseType1;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    wram->wEnemyMon.type2 = wram->wBaseType2;
// The enemy mon's base Sp. Def isn't needed since its base
// Sp. Atk is also used to calculate Sp. Def stat experience.
    // LD_HL(wBaseStats);
    // LD_DE(wEnemyMonBaseStats);
    // LD_B(NUM_STATS - 1);
    for(uint8_t b = 0; b < NUM_STATS - 1; ++b) {
    // loop:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        wram->wEnemyMonBaseStats[b] = wram->wBaseStats[b];
        // DEC_B;
        // IF_NZ goto loop;
    }
    // LD_A_addr(wCurPartyMon);
    // LD_addr_A(wCurOTMon);
    wram->wCurOTMon = wram->wCurPartyMon;
    // RET;
}

void SwitchPlayerMon(void){
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wLastPlayerMon);
    wram->wLastPlayerMon = wram->wCurBattleMon;
    // LD_A_addr(wCurPartyMon);
    // LD_addr_A(wCurBattleMon);
    wram->wCurBattleMon = wram->wCurPartyMon;
    // CALL(aAddBattleParticipant);
    AddBattleParticipant();
    // CALL(aInitBattleMon);
    InitBattleMon();
    // CALL(aResetPlayerStatLevels);
    ResetPlayerStatLevels();
    // CALL(aNewBattleMonStatus);
    NewBattleMonStatus();
    // CALL(aBreakAttraction);
    BreakAttraction();
    // CALL(aSendOutPlayerMon);
    SendOutPlayerMon();
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // RET;
}

void SendOutPlayerMon(void){
    // LD_HL(wBattleMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter_Conv(wram->wBattleMon.dvs);
    // hlcoord(1, 5, wTilemap);
    // LD_B(7);
    // LD_C(8);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 5, wram->wTilemap), 8, 7);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aGetBattleMonBackpic);
    GetBattleMonBackpic();
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0;
    // LD_addr_A(wBattleMenuCursorPosition);
    wram->wBattleMenuCursorPosition = 0;
    // LD_addr_A(wCurMoveNum);
    wram->wCurMoveNum = 0;
    // LD_addr_A(wTypeModifier);
    wram->wTypeModifier = 0;
    // LD_addr_A(wPlayerMoveStruct + MOVE_ANIM);
    wram->wPlayerMoveStruct.animation = 0;
    // LD_addr_A(wLastPlayerCounterMove);
    wram->wLastPlayerCounterMove = 0;
    // LD_addr_A(wLastEnemyCounterMove);
    wram->wLastEnemyCounterMove = 0;
    // LD_addr_A(wLastPlayerMove);
    wram->wLastPlayerMove = 0;
    // CALL(aCheckAmuletCoin);
    CheckAmuletCoin_Conv();
    // CALL(aFinishBattleAnim);
    FinishBattleAnim();
    // XOR_A_A;
    // LD_addr_A(wEnemyWrapCount);
    wram->wEnemyWrapCount = 0;
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0;
    // LD_DE(ANIM_SEND_OUT_MON);
    // CALL(aCall_PlayBattleAnim);
    Call_PlayBattleAnim_Conv(ANIM_SEND_OUT_MON);
    // CALL(aBattleCheckPlayerShininess);
    // IF_NC goto not_shiny;
    if(BattleCheckPlayerShininess_Conv()) {
        // LD_A(1);
        // LD_addr_A(wBattleAnimParam);
        wram->wBattleAnimParam = 1;
        // LD_DE(ANIM_SEND_OUT_MON);
        // CALL(aCall_PlayBattleAnim);
        Call_PlayBattleAnim_Conv(ANIM_SEND_OUT_MON);
    }
// not_shiny:
    // LD_A(MON_SPECIES);
    // CALL(aGetPartyParamLocation);
    struct PartyMon* bc = &wram->wPartyMon[wram->wCurPartyMon];
    // LD_B_H;
    // LD_C_L;
    // FARCALL(aCheckFaintedFrzSlp);
    // IF_C goto statused;
    if(!CheckFaintedFrzSlp_Conv(bc)) {
        // LD_A(0xf0);
        // LD_addr_A(wCryTracks);
        wram->wCryTracks = 0xf0;
        // LD_A_addr(wCurPartySpecies);
        // CALL(aPlayStereoCry);
        PlayStereoCry_Conv(wram->wCurPartySpecies);
    }


// statused:
    // CALL(aUpdatePlayerHUD);
    UpdatePlayerHUD();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // RET;
}

void NewBattleMonStatus(void){
    // XOR_A_A;
    // LD_addr_A(wLastPlayerCounterMove);
    wram->wLastPlayerCounterMove = 0;
    // LD_addr_A(wLastEnemyCounterMove);
    wram->wLastEnemyCounterMove = 0;
    // LD_addr_A(wLastPlayerMove);
    wram->wLastPlayerMove = 0;
    // LD_HL(wPlayerSubStatus1);
    wram->wPlayerSubStatus1 = 0;
    wram->wPlayerSubStatus2 = 0;
    wram->wPlayerSubStatus3 = 0;
    wram->wPlayerSubStatus4 = 0;
    wram->wPlayerSubStatus5 = 0;
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    // LD_hl_A;
    // LD_HL(wPlayerUsedMoves);
    // LD_hli_A;
    wram->wPlayerUsedMoves[0] = 0;
    // LD_hli_A;
    wram->wPlayerUsedMoves[1] = 0;
    // LD_hli_A;
    wram->wPlayerUsedMoves[2] = 0;
    // LD_hl_A;
    wram->wPlayerUsedMoves[3] = 0;
    // LD_addr_A(wPlayerDisableCount);
    wram->wPlayerDisableCount = 0;
    // LD_addr_A(wPlayerFuryCutterCount);
    wram->wPlayerFuryCutterCount = 0;
    // LD_addr_A(wPlayerProtectCount);
    wram->wPlayerProtectCount = 0;
    // LD_addr_A(wPlayerRageCounter);
    wram->wPlayerRageCounter = 0;
    // LD_addr_A(wDisabledMove);
    wram->wDisabledMove = 0;
    // LD_addr_A(wPlayerMinimized);
    wram->wPlayerMinimized = 0;
    // LD_addr_A(wEnemyWrapCount);
    wram->wEnemyWrapCount = 0;
    // LD_addr_A(wPlayerWrapCount);
    wram->wPlayerWrapCount = 0;
    // LD_addr_A(wPlayerTurnsTaken);
    wram->wPlayerTurnsTaken = 0;
    // LD_HL(wEnemySubStatus5);
    // RES_hl(SUBSTATUS_CANT_RUN);
    bit_reset(wram->wEnemySubStatus5, SUBSTATUS_CANT_RUN);
    // RET;
}

void BreakAttraction(void){
    // LD_HL(wPlayerSubStatus1);
    // RES_hl(SUBSTATUS_IN_LOVE);
    bit_reset(wram->wPlayerSubStatus1, SUBSTATUS_IN_LOVE);
    // LD_HL(wEnemySubStatus1);
    // RES_hl(SUBSTATUS_IN_LOVE);
    bit_reset(wram->wEnemySubStatus1, SUBSTATUS_IN_LOVE);
    // RET;
}

void SpikesDamage(void){
    // LD_HL(wPlayerScreens);
    uint8_t* hl;
    // LD_DE(wBattleMonType);
    uint8_t* de;
    // LD_BC(mUpdatePlayerHUD);
    void (*bc)(void);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    if(hram->hBattleTurn == 0) {
        hl = &wram->wPlayerScreens;
        de = wram->wBattleMon.types;
        bc = UpdatePlayerHUD;
    }
    // LD_HL(wEnemyScreens);
    // LD_DE(wEnemyMonType);
    // LD_BC(mUpdateEnemyHUD);
    else {
        hl = &wram->wEnemyScreens;
        de = wram->wEnemyMon.types;
        bc = UpdateEnemyHUD;
    }

// ok:

    // BIT_hl(SCREENS_SPIKES);
    // RET_Z ;
    if(!bit_test(*hl, SCREENS_SPIKES))
        return;

// Flying-types aren't affected by Spikes.
    // LD_A_de;
    // CP_A(FLYING);
    // RET_Z ;
    // INC_DE;
    // LD_A_de;
    // CP_A(FLYING);
    // RET_Z ;
    if(de[0] == FLYING || de[1] == FLYING)
        return;

    // PUSH_BC;

    // LD_HL(mBattleText_UserHurtBySpikes);  // "hurt by SPIKES!"
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_UserHurtBySpikes);

    // CALL(aGetEighthMaxHP);
    // CALL(aSubtractHPFromTarget);

    // POP_HL;
    // CALL(aSpikesDamage_hl);
    bc();

    // JP(mWaitBGMap);
    WaitBGMap_Conv();


// hl:
    // JP_hl;
}

bool PursuitSwitch(void){
    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVar);
    // LD_B_A;
    // CALL(aGetMoveEffect);
    // LD_A_B;
    // CP_A(EFFECT_PURSUIT);
    // IF_NZ goto done;
    if(HIGH(GetMoveEffect_Conv(GetBattleVar_Conv(BATTLE_VARS_MOVE))) != EFFECT_PURSUIT)
        return false;

    // LD_A_addr(wCurBattleMon);
    // PUSH_AF;
    uint8_t curBattleMon = wram->wCurBattleMon;

    // LD_HL(mDoPlayerTurn);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto do_turn;
    // LD_HL(mDoEnemyTurn);
    // LD_A_addr(wLastPlayerMon);
    // LD_addr_A(wCurBattleMon);
    if(hram->hBattleTurn != 0) {
        wram->wCurBattleMon = wram->wLastPlayerMon;
        DoEnemyTurn();
    }
    else {
        DoPlayerTurn();
    }

// do_turn:
    // LD_A(BANK(aDoPlayerTurn));  // aka BANK(DoEnemyTurn)
    // RST(aFarCall);

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVarAddr);
    // LD_A(0xff);
    // LD_hl_A;
    *GetBattleVarAddr_Conv(BATTLE_VARS_MOVE) = 0xff;

    // POP_AF;
    // LD_addr_A(wCurBattleMon);
    wram->wCurBattleMon = curBattleMon;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto check_enemy_fainted;
    if(hram->hBattleTurn != 0) {
        // LD_A_addr(wLastPlayerMon);
        // CALL(aUpdateBattleMon);
        UpdateBattleMon_Conv(wram->wLastPlayerMon);
        // LD_HL(wBattleMonHP);
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto done;
        if(wram->wBattleMon.hp != 0)
            return false;

        // LD_A(0xf0);
        // LD_addr_A(wCryTracks);
        wram->wCryTracks = 0xf0;
        // LD_A_addr(wBattleMonSpecies);
        // CALL(aPlayStereoCry);
        // LD_A_addr(wLastPlayerMon);
        // LD_C_A;
        // LD_HL(wBattleParticipantsNotFainted);
        // LD_B(RESET_FLAG);
        // PREDEF(pSmallFarFlagAction);
        SmallFarFlagAction_Conv(&wram->wBattleParticipantsNotFainted, wram->wLastPlayerMon, RESET_FLAG);
        // CALL(aPlayerMonFaintedAnimation);
        PlayerMonFaintedAnimation();
        // LD_HL(mBattleText_MonFainted);
        // goto done_fainted;
        StdBattleTextbox_Conv2(BattleText_MonFainted);
    }
    else {
    // check_enemy_fainted:
        // LD_HL(wEnemyMonHP);
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto done;
        if(wram->wEnemyMon.hp != 0)
            return false;

        // LD_DE(SFX_KINESIS);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_KINESIS);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // LD_DE(SFX_FAINT);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_FAINT);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // CALL(aEnemyMonFaintedAnimation);
        EnemyMonFaintedAnimation();
        // LD_HL(mBattleText_EnemyMonFainted);
        StdBattleTextbox_Conv2(BattleText_EnemyMonFainted);
    }

// done_fainted:
    // CALL(aStdBattleTextbox);
    // SCF;
    // RET;
    return true;

// done:
    // AND_A_A;
    // RET;
}

void RecallPlayerMon(void){
    // LDH_A_addr(hBattleTurn);
    // PUSH_AF;
    uint8_t turn = hram->hBattleTurn;
    // XOR_A_A;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = 0;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_DE(ANIM_RETURN_MON);
    // CALL(aCall_PlayBattleAnim);
    Call_PlayBattleAnim_Conv(ANIM_RETURN_MON);
    // POP_AF;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = turn;
    // RET;
}

void HandleHealingItems(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto player_1;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK){
    // player_1:
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALL(aHandleHPHealingItem);
        HandleHPHealingItem();
        // CALL(aUseHeldStatusHealingItem);
        UseHeldStatusHealingItem();
        // CALL(aUseConfusionHealingItem);
        UseConfusionHealingItem();
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALL(aHandleHPHealingItem);
        HandleHPHealingItem();
        // CALL(aUseHeldStatusHealingItem);
        UseHeldStatusHealingItem();
        // JP(mUseConfusionHealingItem);
        return UseConfusionHealingItem();
    }
    else {
        // CALL(aSetPlayerTurn);
        SetPlayerTurn_Conv();
        // CALL(aHandleHPHealingItem);
        HandleHPHealingItem();
        // CALL(aUseHeldStatusHealingItem);
        UseHeldStatusHealingItem();
        // CALL(aUseConfusionHealingItem);
        UseConfusionHealingItem();
        // CALL(aSetEnemyTurn);
        SetEnemyTurn_Conv();
        // CALL(aHandleHPHealingItem);
        HandleHPHealingItem();
        // CALL(aUseHeldStatusHealingItem);
        UseHeldStatusHealingItem();
        // JP(mUseConfusionHealingItem);
        return UseConfusionHealingItem();
    }
}

void HandleHPHealingItem(void){
    item_t item;
    // CALLFAR(aGetOpponentItem);
    uint16_t itemEffect = GetOpponentItem_Conv(&item);
    // LD_A_B;
    // CP_A(HELD_BERRY);
    // RET_NZ ;
    if(itemEffect != HELD_BERRY)
        return;
    // LD_DE(wEnemyMonHP + 1);
    // LD_HL(wEnemyMonMaxHP);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto go;
    // LD_DE(wBattleMonHP + 1);
    // LD_HL(wBattleMonMaxHP);
    uint8_t* hp_    = (uint8_t*)((hram->hBattleTurn == 0)? &wram->wEnemyMon.hp    : &wram->wBattleMon.hp);
    uint8_t* maxhp_ = (uint8_t*)((hram->hBattleTurn == 0)? &wram->wEnemyMon.maxHP : &wram->wBattleMon.maxHP);

// go:
//  If, and only if, Pokemon's HP is less than half max, use the item.
//  Store current HP in Buffer 3/4
    uint16_t hp    = (hp_[0]    << 8) | hp_[1];
    uint16_t maxhp = (maxhp_[0] << 8) | maxhp_[1];
    // PUSH_BC;
    // LD_A_de;
    // LD_addr_A(wHPBuffer2);
    // ADD_A_A;
    // LD_C_A;
    // DEC_DE;
    // LD_A_de;
    // INC_DE;
    // LD_addr_A(wHPBuffer2 + 1);
    wram->wHPBuffer2 = hp;
    // ADC_A_A;
    // LD_B_A;
    // LD_A_B;
    // CP_A_hl;
    // LD_A_C;
    // POP_BC;
    // IF_Z goto equal;
    // IF_C goto less;
    // RET;

// equal:
    // INC_HL;
    // CP_A_hl;
    // DEC_HL;
    // RET_NC ;
    if(hp * 2 >= maxhp)
        return;

// less:
    // CALL(aItemRecoveryAnim);
    ItemRecoveryAnim();
// store max HP in wHPBuffer1
    // LD_A_hli;
    // LD_addr_A(wHPBuffer1 + 1);
    // LD_A_hl;
    // LD_addr_A(wHPBuffer1);
    wram->wHPBuffer1 = maxhp;
    // LD_A_de;
    // ADD_A_C;
    // LD_addr_A(wHPBuffer3);
    // LD_C_A;
    // DEC_DE;
    // LD_A_de;
    // ADC_A(0);
    // LD_addr_A(wHPBuffer3 + 1);
    wram->wHPBuffer3 = hp;
    // LD_B_A;
    // LD_A_hld;
    // CP_A_C;
    // LD_A_hl;
    // SBC_A_B;
    // IF_NC goto okay;
    if(hp >= maxhp){
        // LD_A_hli;
        // LD_addr_A(wHPBuffer3 + 1);
        // LD_A_hl;
        // LD_addr_A(wHPBuffer3);
        wram->wHPBuffer3 = maxhp;
    }

// okay:
    // LD_A_addr(wHPBuffer3 + 1);
    // LD_de_A;
    hp_[0] = HIGH(wram->wHPBuffer3);
    // INC_DE;
    // LD_A_addr(wHPBuffer3);
    // LD_de_A;
    hp_[1] = LOW(wram->wHPBuffer3);
    // LDH_A_addr(hBattleTurn);
    // LD_addr_A(wWhichHPBar);
    // AND_A_A;
    // hlcoord(2, 2, wTilemap);
    // IF_Z goto got_hp_bar_coords;
    // hlcoord(10, 9, wTilemap);
    uint8_t* hl = (hram->hBattleTurn == 0)?  coord(2, 2, wram->wTilemap): coord(10, 9, wram->wTilemap);

// got_hp_bar_coords:
    // LD_addr_A(wWhichHPBar);
    // PREDEF(pAnimateHPBar);
    AnimateHPBar_Conv(hl, hram->hBattleTurn);
    return UseOpponentItem();
}

void UseOpponentItem(void){
    item_t item;
    // CALL(aRefreshBattleHuds);
    RefreshBattleHuds_Conv();
    // CALLFAR(aGetOpponentItem);
    GetOpponentItem_Conv(&item);
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    GetItemName_Conv2(item);
    // CALLFAR(aConsumeHeldItem);
    ConsumeHeldItem();
    // LD_HL(mRecoveredUsingText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(RecoveredUsingText);
}

void ItemRecoveryAnim(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // LD_A(RECOVER);
    // LD_addr_A(wFXAnimID);
    wram->wFXAnimID = RECOVER;
    // CALL(aSwitchTurnCore);
    SwitchTurnCore();
    // XOR_A_A;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID &= 0xff;
    // PREDEF(pPlayBattleAnim);
    PlayBattleAnim();
    // CALL(aSwitchTurnCore);
    SwitchTurnCore();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

bool UseHeldStatusHealingItem(void){
    // CALLFAR(aGetOpponentItem);
    uint16_t item_effect = GetOpponentItem_Conv(NULL);
    // LD_HL(mHeldStatusHealingEffects);
    const uint8_t* hl = HeldStatusHealingEffects;

    uint8_t a;
    do {
    // loop:
        // LD_A_hli;
        a = *(hl++);
        // CP_A(0xff);
        // RET_Z ;
        if(a == 0xff)
            return false;
        // INC_HL;
        hl++;
        // CP_A_B;
        // IF_NZ goto loop;
    } while(a != HIGH(item_effect));
    // DEC_HL;
    hl--;
    // LD_B_hl;
    uint8_t b = *hl;
    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* stat = GetBattleVarAddr_Conv(BATTLE_VARS_STATUS_OPP);
    // AND_A_B;
    // RET_Z ;
    if((*stat & b) == 0)
        return false;
    // XOR_A_A;
    // LD_hl_A;
    *stat = 0;
    // PUSH_BC;
    // CALL(aUpdateOpponentInParty);
    UpdateOpponentInParty();
    // POP_BC;
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    // AND_A_hl;
    // RES_hl(SUBSTATUS_TOXIC);
    bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_TOXIC);
    // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    // CALL(aGetBattleVarAddr);
    // AND_A_hl;
    // RES_hl(SUBSTATUS_NIGHTMARE);
    bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS1_OPP), SUBSTATUS_NIGHTMARE);
    // LD_A_B;
    // CP_A(ALL_STATUS);
    // IF_NZ goto skip_confuse;
    if(b == ALL_STATUS) {
        // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
        // CALL(aGetBattleVarAddr);
        // RES_hl(SUBSTATUS_CONFUSED);
        bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS3_OPP), SUBSTATUS_CONFUSED);
    }

// skip_confuse:
    // LD_HL(mCalcEnemyStats);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_pointer;
    // LD_HL(mCalcPlayerStats);

// got_pointer:
    // CALL(aSwitchTurnCore);
    // LD_A(BANK(aCalcPlayerStats));  // aka BANK(CalcEnemyStats)
    // RST(aFarCall);
    if(hram->hBattleTurn == 0) {
        SwitchTurnCore();
        CalcEnemyStats();
        SwitchTurnCore();
    }
    else {
        SwitchTurnCore();
        CalcPlayerStats();
        SwitchTurnCore();
    }
    // CALL(aSwitchTurnCore);
    // CALL(aItemRecoveryAnim);
    ItemRecoveryAnim();
    // CALL(aUseOpponentItem);
    UseOpponentItem();
    // LD_A(0x1);
    // AND_A_A;
    // RET;
    return true;
// INCLUDE "data/battle/held_heal_status.asm"

}

void UseConfusionHealingItem(void){
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_CONFUSED);
    // RET_Z ;
    if(!bit_test(GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS3_OPP), SUBSTATUS_CONFUSED))
        return;
    // CALLFAR(aGetOpponentItem);
    item_t item;
    uint16_t effect = GetOpponentItem_Conv(&item);
    // LD_A_B;
    // CP_A(HELD_HEAL_CONFUSION);
    // IF_Z goto heal_status;
    // CP_A(HELD_HEAL_STATUS);
    // RET_NZ ;
    if(HIGH(effect) != HELD_HEAL_CONFUSION && HIGH(effect) != HELD_HEAL_STATUS)
        return;

// heal_status:
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // LD_A(BATTLE_VARS_SUBSTATUS3_OPP);
    // CALL(aGetBattleVarAddr);
    // RES_hl(SUBSTATUS_CONFUSED);
    bit_reset(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS3_OPP), SUBSTATUS_CONFUSED);
    // CALL(aGetItemName);
    GetItemName_Conv2(item);
    // CALL(aItemRecoveryAnim);
    ItemRecoveryAnim();
    // LD_HL(mBattleText_ItemHealedConfusion);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_ItemHealedConfusion);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto do_partymon;
    if(hram->hBattleTurn == 0) {
        item_t *hl, *bc;
        // CALL(aGetOTPartymonItem);
        GetOTPartymonItem_Conv(&hl, &bc);
        // XOR_A_A;
        // LD_bc_A;
        *bc = NO_ITEM;
        // LD_A_addr(wBattleMode);
        // DEC_A;
        // RET_Z ;
        if(wram->wBattleMode != WILD_BATTLE) {
            // LD_hl(0x0);
            *hl = NO_ITEM;
        }
        // RET;
        return;
    }
    else {
    // do_partymon:
        item_t *hl, *bc;
        // CALL(aGetPartymonItem);
        GetPartymonItem_Conv(&hl, &bc);
        // XOR_A_A;
        // LD_bc_A;
        *bc = NO_ITEM;
        // LD_hl_A;
        *hl = NO_ITEM;
        // RET;
        return;
    }
}

static void HandleStatBoostingHeldItems_HandleItem(item_t* hl, item_t* bc, uint8_t a){
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = a;
    // LD_D_H;
    // LD_E_L;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_bc;
    // LD_B_A;
    // CALLFAR(aGetItemHeldEffect);
    uint16_t effect = HIGH(GetItemHeldEffect_Conv(*bc));
    // LD_HL(mHeldStatUpItems);
    const struct EffectFunc* list = HeldStatUpItems;

    while(list->effect != effect) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto finish;
        if(list->effect == (uint8_t)-1)
            return;
        // INC_HL;
        // INC_HL;
        // CP_A_B;
        list++;
        // IF_NZ goto loop;
    }
    // POP_BC;
    // LD_A_bc;
    // LD_addr_A(wNamedObjectIndex);
    item_t itm = *bc;
    // PUSH_BC;
    // DEC_HL;
    // DEC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A(BANK(aBattleCommand_AttackUp));
    // RST(aFarCall);
    list->func();
    // POP_BC;
    // POP_DE;
    // LD_A_addr(wFailedMessage);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wFailedMessage)
        return;
    // XOR_A_A;
    // LD_bc_A;
    *bc = NO_ITEM;
    // LD_de_A;
    *hl = NO_ITEM;
    // CALL(aGetItemName);
    GetItemName_Conv2(itm);
    // LD_HL(mBattleText_UsersStringBuffer1Activated);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_UsersStringBuffer1Activated);
    // CALLFAR(aBattleCommand_StatUpMessage);
    BattleCommand_StatUpMessage();
    // RET;

// finish:
    // POP_BC;
    // POP_DE;
    // RET;
}

static void HandleStatBoostingHeldItems_DoPlayer(void){
    item_t *hl, *bc;
    // CALL(aGetPartymonItem);
    GetPartymonItem_Conv(&hl, &bc);
    // LD_A(0x0);
    // JP(mHandleStatBoostingHeldItems_HandleItem);
    return HandleStatBoostingHeldItems_HandleItem(hl, bc, 0x0);
}

static void HandleStatBoostingHeldItems_DoEnemy(void){
    item_t *hl, *bc;
    // CALL(aGetOTPartymonItem);
    GetPartymonItem_Conv(&hl, &bc);
    // LD_A(0x1);
    return HandleStatBoostingHeldItems_HandleItem(hl, bc, 0x1);
}

//  The effects handled here are not used in-game.
void HandleStatBoostingHeldItems(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto player_1;
    if(hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK){
    // player_1:
        // CALL(aHandleStatBoostingHeldItems_DoEnemy);
        HandleStatBoostingHeldItems_DoEnemy();
        // JP(mHandleStatBoostingHeldItems_DoPlayer);
        return HandleStatBoostingHeldItems_DoPlayer();
    }
    else {
        // CALL(aHandleStatBoostingHeldItems_DoPlayer);
        HandleStatBoostingHeldItems_DoPlayer();
        // JP(mHandleStatBoostingHeldItems_DoEnemy);
        return HandleStatBoostingHeldItems_DoEnemy();
    }

// INCLUDE "data/battle/held_stat_up.asm"
}

void GetPartymonItem(void){
    LD_HL(wPartyMon1Item);
    LD_A_addr(wCurBattleMon);
    CALL(aGetPartyLocation);
    LD_BC(wBattleMonItem);
    RET;

}

void GetPartymonItem_Conv(item_t** hl, item_t** bc){
    // LD_HL(wPartyMon1Item);
    // LD_A_addr(wCurBattleMon);
    // CALL(aGetPartyLocation);
    *hl = &wram->wPartyMon[wram->wCurBattleMon].mon.item;
    // LD_BC(wBattleMonItem);
    *bc = &wram->wBattleMon.item;
    // RET;
}

void GetOTPartymonItem(void){
    LD_HL(wOTPartyMon1Item);
    LD_A_addr(wCurOTMon);
    CALL(aGetPartyLocation);
    LD_BC(wEnemyMonItem);
    RET;

}

void GetOTPartymonItem_Conv(item_t** hl, item_t** bc){
    // LD_HL(wOTPartyMon1Item);
    // LD_A_addr(wCurOTMon);
    // CALL(aGetPartyLocation);
    *hl = &wram->wOTPartyMon[wram->wCurOTMon].mon.item;
    // LD_BC(wEnemyMonItem);
    *bc = &wram->wEnemyMon.item;
    // RET;
}

void UpdateBattleHUDs(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aDrawPlayerHUD);
    uint8_t e = DrawPlayerHUD_Conv();
    // LD_HL(wPlayerHPPal);
    // CALL(aSetHPPal);
    SetHPPal_Conv(&wram->wPlayerHPPal, e);
    // CALL(aCheckDanger);
    CheckDanger();
    // CALL(aDrawEnemyHUD);
    e = DrawEnemyHUD_Conv();
    // LD_HL(wEnemyHPPal);
    // CALL(aSetHPPal);
    SetHPPal_Conv(&wram->wEnemyHPPal, e);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;

}

void UpdatePlayerHUD(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aDrawPlayerHUD);
    uint8_t e = DrawPlayerHUD_Conv();
    // CALL(aUpdatePlayerHPPal);
    UpdatePlayerHPPal_Conv(e);
    // CALL(aCheckDanger);
    CheckDanger();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void DrawPlayerHUD(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;

// Clear the area
    // hlcoord(9, 7, wTilemap);
    // LD_BC((5 << 8) | 11);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(9, 7, wram->wTilemap), 11, 5);

    FARCALL(aDrawPlayerHUDBorder);

    // hlcoord(18, 9, wTilemap);
    // LD_hl(0x73);  // vertical bar
    *coord(18, 9, wram->wTilemap) = 0x73;
    // CALL(aPrintPlayerHUD);
    PrintPlayerHUD();

// HP bar
    hlcoord(10, 9, wTilemap);
    LD_B(1);
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    PREDEF(pDrawPlayerHP);

// Exp bar
    PUSH_DE;
    LD_A_addr(wCurBattleMon);
    LD_HL(wPartyMon1Exp + 2);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;

    hlcoord(10, 11, wTilemap);
    LD_A_addr(wTempMonLevel);
    LD_B_A;
    CALL(aFillInExpBar);
    POP_DE;
    RET;

}

uint8_t DrawPlayerHUD_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;

// Clear the area
    // hlcoord(9, 7, wTilemap);
    // LD_BC((5 << 8) | 11);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(9, 7, wram->wTilemap), 11, 5);

    // FARCALL(aDrawPlayerHUDBorder);
    DrawPlayerHUDBorder();

    // hlcoord(18, 9, wTilemap);
    // LD_hl(0x73);  // vertical bar
    *coord(18, 9, wram->wTilemap) = 0x73;
    // CALL(aPrintPlayerHUD);
    PrintPlayerHUD();

// HP bar
    // hlcoord(10, 9, wTilemap);
    // LD_B(1);
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // PREDEF(pDrawPlayerHP);
    uint8_t e = DrawPlayerHP_Conv(coord(10, 9, wram->wTilemap), 1);

// Exp bar
    // PUSH_DE;
    // LD_A_addr(wCurBattleMon);
    // LD_HL(wPartyMon1Exp + 2);
    // CALL(aGetPartyLocation);
    // LD_D_H;
    // LD_E_L;
    struct PartyMon* de = wram->wPartyMon + wram->wCurBattleMon;

    // hlcoord(10, 11, wTilemap);
    // LD_A_addr(wTempMonLevel);
    // LD_B_A;
    // CALL(aFillInExpBar);
    FillInExpBar_Conv(coord(10, 11, wram->wTilemap), wram->wTempMon.mon.level, de->mon.exp + 2);
    // POP_DE;
    // RET;
    return e;
}

void UpdatePlayerHPPal(void){
    LD_HL(wPlayerHPPal);
    JP(mUpdateHPPal);
}

void UpdatePlayerHPPal_Conv(uint8_t e){
    // LD_HL(wPlayerHPPal);
    // JP(mUpdateHPPal);
    return UpdateHPPal_Conv(&wram->wPlayerHPPal, e);
}

void CheckDanger(void){
    // LD_HL(wBattleMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // IF_Z goto no_danger;
    if(wram->wBattleMon.hp == 0) {
        bit_reset(wram->wLowHealthAlarm, DANGER_ON_F);
        return;
    }
    // LD_A_addr(wBattleLowHealthAlarm);
    // AND_A_A;
    // IF_NZ goto done;
    else if(wram->wBattleLowHealthAlarm != 0)
        return;
    // LD_A_addr(wPlayerHPPal);
    // CP_A(HP_RED);
    // IF_Z goto danger;
    else if(wram->wPlayerHPPal == HP_RED) {
        bit_set(wram->wLowHealthAlarm, DANGER_ON_F);
        return;
    }
    else {
    // no_danger:
        // LD_HL(wLowHealthAlarm);
        // RES_hl(DANGER_ON_F);
        // goto done;
        bit_reset(wram->wLowHealthAlarm, DANGER_ON_F);
        return;
    }

// danger:
    // LD_HL(wLowHealthAlarm);
    // SET_hl(DANGER_ON_F);

// done:
    // RET;
}

void PrintPlayerHUD(void){
    // LD_DE(wBattleMonNickname);
    // hlcoord(10, 7, wTilemap);
    // CALL(aBattle_DummyFunction);
    Battle_DummyFunction();
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl = coord(10, 7, wram->wTilemap), .de = wram->wBattleMonNickname};
    PlaceString_Conv(&st, st.hl);

    // PUSH_BC;

    // LD_A_addr(wCurBattleMon);
    // LD_HL(wPartyMon1DVs);
    // CALL(aGetPartyLocation);
    struct PartyMon* hl = wram->wPartyMon + wram->wCurBattleMon;
    // LD_DE(wTempMonDVs);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    wram->wTempMon.mon.DVs = hl->mon.DVs;
    // LD_HL(wBattleMonLevel);
    // LD_DE(wTempMonLevel);
    // LD_BC(wTempMonStructEnd - wTempMonLevel);
    // CALL(aCopyBytes);  // battle_struct and party_struct end with the same data
    CopyBytes_Conv2(&wram->wTempMon.mon.level, &wram->wBattleMon.level, (wTempMonStructEnd - wTempMonLevel));
    // LD_A_addr(wCurBattleMon);
    // LD_HL(wPartyMon1Species);
    // CALL(aGetPartyLocation);
    // LD_A_hl;
    species_t a = hl->mon.species;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = a;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = a;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(a);

    // POP_HL;
    // DEC_HL;

    // LD_A(TEMPMON);
    // LD_addr_A(wMonType);
    wram->wMonType = TEMPMON;
    // CALLFAR(aGetGender);
    u8_flag_s temp = GetGender_Conv(TEMPMON);
    // LD_A(0x7f);
    // IF_C goto got_gender_char;
    if(temp.flag) {
        *coord(17, 8, wram->wTilemap) = CHAR_SPACE;
    }
    else if(temp.a != 0) {
        // LD_A(0xef);
        // IF_NZ goto got_gender_char;
        *coord(17, 8, wram->wTilemap) = CHAR_MALE_ICON;
        // LD_A(0xf5);
    }
    else {
        *coord(17, 8, wram->wTilemap) = CHAR_FEMALE_ICON;
    }

// got_gender_char:
    // hlcoord(17, 8, wTilemap);
    // LD_hl_A;
    // hlcoord(14, 8, wTilemap);
    // PUSH_AF;  // back up gender
    // PUSH_HL;
    uint8_t* hl2 = coord(14, 8, wram->wTilemap);
    // LD_DE(wBattleMonStatus);
    // PREDEF(pPlaceNonFaintStatus);
    bool c_ = PlaceNonFaintStatus2_Conv(hl2, wram->wBattleMon.status[0]);
    // POP_HL;
    // POP_BC;
    // RET_NZ ;
    if(c_)
        return;
    // LD_A_B;
    // CP_A(0x7f);
    // IF_NZ goto copy_level;  // male or female
    // DEC_HL;  // genderless
    if(temp.flag)
        hl2 -= 1;


// copy_level:
    // LD_A_addr(wBattleMonLevel);
    // LD_addr_A(wTempMonLevel);
    // JP(mPrintLevel);
    PrintLevel_Conv(hl2, wram->wBattleMon.level);
}

void UpdateEnemyHUD(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aDrawEnemyHUD);
    uint8_t e = DrawEnemyHUD_Conv();
    // CALL(aUpdateEnemyHPPal);
    UpdateEnemyHPPal_Conv(e);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void DrawEnemyHUD(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    hlcoord(1, 0, wTilemap);
    LD_BC((4 << 8) | 11);
    CALL(aClearBox);

    FARCALL(aDrawEnemyHUDBorder);

    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wCurSpecies);
    LD_addr_A(wCurPartySpecies);
    CALL(aGetBaseData);
    LD_DE(wEnemyMonNickname);
    hlcoord(1, 0, wTilemap);
    CALL(aBattle_DummyFunction);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    DEC_HL;

    LD_HL(wEnemyMonDVs);
    LD_DE(wTempMonDVs);
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_Z goto ok;
    LD_HL(wEnemyBackupDVs);

ok:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;

    LD_A(TEMPMON);
    LD_addr_A(wMonType);
    CALLFAR(aGetGender);
    LD_A(0x7f);
    IF_C goto got_gender;
    LD_A(0xef);
    IF_NZ goto got_gender;
    LD_A(0xf5);


got_gender:
    hlcoord(9, 1, wTilemap);
    LD_hl_A;

    hlcoord(6, 1, wTilemap);
    PUSH_AF;
    PUSH_HL;
    LD_DE(wEnemyMonStatus);
    PREDEF(pPlaceNonFaintStatus);
    POP_HL;
    POP_BC;
    IF_NZ goto skip_level;
    LD_A_B;
    CP_A(0x7f);
    IF_NZ goto print_level;
    DEC_HL;

print_level:
    LD_A_addr(wEnemyMonLevel);
    LD_addr_A(wTempMonLevel);
    CALL(aPrintLevel);

skip_level:

    LD_HL(wEnemyMonHP);
    LD_A_hli;
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hld;
    LDH_addr_A(hMultiplicand + 2);
    OR_A_hl;
    IF_NZ goto not_fainted;

    LD_C_A;
    LD_E_A;
    LD_D(HP_BAR_LENGTH);
    JP(mDrawEnemyHUD_draw_bar);


not_fainted:
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A(HP_BAR_LENGTH_PX);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_HL(wEnemyMonMaxHP);
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    LDH_addr_A(hMultiplier);
    LD_A_B;
    AND_A_A;
    IF_Z goto less_than_256_max;
    LDH_A_addr(hMultiplier);
    SRL_B;
    RR_A;
    SRL_B;
    RR_A;
    LDH_addr_A(hDivisor);
    LDH_A_addr(hProduct + 2);
    LD_B_A;
    SRL_B;
    LDH_A_addr(hProduct + 3);
    RR_A;
    SRL_B;
    RR_A;
    LDH_addr_A(hProduct + 3);
    LD_A_B;
    LDH_addr_A(hProduct + 2);


less_than_256_max:
    LDH_A_addr(hProduct + 2);
    LDH_addr_A(hDividend + 0);
    LDH_A_addr(hProduct + 3);
    LDH_addr_A(hDividend + 1);
    LD_A(2);
    LD_B_A;
    CALL(aDivide);
    LDH_A_addr(hQuotient + 3);
    LD_E_A;
    LD_A(HP_BAR_LENGTH);
    LD_D_A;
    LD_C_A;


draw_bar:
    XOR_A_A;
    LD_addr_A(wWhichHPBar);
    hlcoord(2, 2, wTilemap);
    LD_B(0);
    CALL(aDrawBattleHPBar);
    RET;
}

static uint8_t DrawEnemyHUD_draw_bar(uint8_t c, uint8_t e, uint8_t d) {
    printf("%d tiles, %d pixels\n", d, e);
    // XOR_A_A;
    // LD_addr_A(wWhichHPBar);
    wram->wWhichHPBar = 0;
    // hlcoord(2, 2, wTilemap);
    // LD_B(0);
    // CALL(aDrawBattleHPBar);
    DrawBattleHPBar_Conv(coord(2, 2, wram->wTilemap), d, e, 0, c);
    // RET;
    return e;
}

uint8_t DrawEnemyHUD_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;

    // hlcoord(1, 0, wTilemap);
    // LD_BC((4 << 8) | 11);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 0, wram->wTilemap), 11, 4);

    // FARCALL(aDrawEnemyHUDBorder);
    DrawEnemyHUDBorder();

    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wTempEnemyMonSpecies;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempEnemyMonSpecies;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wTempEnemyMonSpecies);
    // LD_DE(wEnemyMonNickname);
    // hlcoord(1, 0, wTilemap);
    // CALL(aBattle_DummyFunction);
    Battle_DummyFunction();
    // CALL(aPlaceString);
    struct TextPrintState state = {.hl = coord(1, 0, wram->wTilemap), .de = wram->wEnemyMonNickname};
    PlaceString_Conv(&state, state.hl);
    // LD_H_B;
    // LD_L_C;
    // DEC_HL;

    // LD_HL(wEnemyMonDVs);
    // LD_DE(wTempMonDVs);
    // LD_A_addr(wEnemySubStatus5);
    // BIT_A(SUBSTATUS_TRANSFORMED);
    // IF_Z goto ok;
    // LD_HL(wEnemyBackupDVs);
    uint16_t dvs = (bit_test(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED))? wram->wEnemyBackupDVs: wram->wEnemyMon.dvs;

// ok:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    wram->wTempMon.mon.DVs = dvs;

    // LD_A(TEMPMON);
    // LD_addr_A(wMonType);
    wram->wMonType = TEMPMON;
    // CALLFAR(aGetGender);
    u8_flag_s gender = GetGender_Conv(TEMPMON);
    // LD_A(0x7f);
    // IF_C goto got_gender;
    if(gender.flag) 
        *coord(9, 1, wram->wTilemap) = CHAR_SPACE;
    // LD_A(0xef);
    // IF_NZ goto got_gender;
    else if(gender.a != 0) 
        *coord(9, 1, wram->wTilemap) = CHAR_MALE_ICON;
    // LD_A(0xf5);
    else 
        *coord(9, 1, wram->wTilemap) = CHAR_FEMALE_ICON;


// got_gender:
    // hlcoord(9, 1, wTilemap);
    // LD_hl_A;

    // hlcoord(6, 1, wTilemap);
    // PUSH_AF;
    // PUSH_HL;
    // LD_DE(wEnemyMonStatus);
    // PREDEF(pPlaceNonFaintStatus);
    bool f = PlaceNonFaintStatus2_Conv(coord(6, 1, wram->wTilemap), wram->wEnemyMon.status[0]);
    // POP_HL;
    // POP_BC;
    // IF_NZ goto skip_level;
    if(!f) {
        // LD_A_B;
        // CP_A(0x7f);
        // IF_NZ goto print_level;
        // DEC_HL;

    // print_level:
        // LD_A_addr(wEnemyMonLevel);
        // LD_addr_A(wTempMonLevel);
        // CALL(aPrintLevel);
        PrintLevel_Conv(coord(6, 1, wram->wTilemap) - ((gender.flag)? 1: 0), wram->wEnemyMon.level);
    }

// skip_level:

    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hld;
    // LDH_addr_A(hMultiplicand + 2);
    // OR_A_hl;
    // IF_NZ goto not_fainted;
    if(wram->wEnemyMon.hp == 0 || wram->wEnemyMon.maxHP == 0) {
        // LD_C_A;
        // LD_E_A;
        // LD_D(HP_BAR_LENGTH);
        // JP(mDrawEnemyHUD_draw_bar);
        return DrawEnemyHUD_draw_bar(0, 0, HP_BAR_LENGTH);
    }

// not_fainted:
    uint16_t HP = BigEndianToNative16(wram->wEnemyMon.hp);
    uint16_t maxHP = BigEndianToNative16(wram->wEnemyMon.maxHP);
    printf("%d HP / %d maxHP\n", HP, maxHP);
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LD_A(HP_BAR_LENGTH_PX);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    uint32_t m1 = (uint32_t)HP * HP_BAR_LENGTH_PX;
    // LD_HL(wEnemyMonMaxHP);
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hl;
    // LDH_addr_A(hMultiplier);
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto less_than_256_max;
    if(maxHP > 255) {
        // LDH_A_addr(hMultiplier);
        // SRL_B;
        // RR_A;
        // SRL_B;
        // RR_A;
        // LDH_addr_A(hDivisor);
        // LDH_A_addr(hProduct + 2);
        // LD_B_A;
        // SRL_B;
        // LDH_A_addr(hProduct + 3);
        // RR_A;
        // SRL_B;
        // RR_A;
        // LDH_addr_A(hProduct + 3);
        // LD_A_B;
        // LDH_addr_A(hProduct + 2);
        m1 /= 4;
        maxHP /= 4;
    }

// less_than_256_max:
    // LDH_A_addr(hProduct + 2);
    // LDH_addr_A(hDividend + 0);
    // LDH_A_addr(hProduct + 3);
    // LDH_addr_A(hDividend + 1);
    // LD_A(2);
    // LD_B_A;
    // CALL(aDivide);
    // LDH_A_addr(hQuotient + 3);
    // LD_E_A;
    uint8_t e = (uint8_t)(m1 / maxHP);
    // LD_A(HP_BAR_LENGTH);
    // LD_D_A;
    // LD_C_A;
    return DrawEnemyHUD_draw_bar(HP_BAR_LENGTH, e, HP_BAR_LENGTH);

// draw_bar:
    // XOR_A_A;
    // LD_addr_A(wWhichHPBar);
    // hlcoord(2, 2, wTilemap);
    // LD_B(0);
    // CALL(aDrawBattleHPBar);
    // RET;
}

void UpdateEnemyHPPal(void){
    LD_HL(wEnemyHPPal);
    CALL(aUpdateHPPal);
    RET;

}

void UpdateEnemyHPPal_Conv(uint8_t e){
    // LD_HL(wEnemyHPPal);
    // CALL(aUpdateHPPal);
    // RET;
    printf("SET ENEMY HP PAL(e=%d)\n", e);
    return UpdateHPPal_Conv(&wram->wEnemyHPPal, e);
}

void UpdateHPPal(void){
    LD_B_hl;
    CALL(aSetHPPal);
    LD_A_hl;
    CP_A_B;
    RET_Z ;
    JP(mFinishBattleAnim);

}

void UpdateHPPal_Conv(uint8_t* hl, uint8_t e){
    // LD_B_hl;
    uint8_t b = *hl;
    // CALL(aSetHPPal);
    SetHPPal_Conv(hl, e);
    // LD_A_hl;
    // CP_A_B;
    // RET_Z ;
    if(*hl == b)
        return;
    // JP(mFinishBattleAnim);
    return FinishBattleAnim();
}

//  called before placing either battler's nickname in the HUD
void Battle_DummyFunction(void){
    // RET;
}

static bool BattleMenu_PKMN_GetMenu(void) {
    // CALL(aIsMobileBattle);
    // IF_Z goto mobile;
    if(IsMobileBattle_Conv()) {
    // mobile:
        // FARCALL(aMobileBattleMonMenu);
        return SafeCallGBAutoRet(aMobileBattleMonMenu).f_bits.c != 0;
        // RET;
    }
    // FARCALL(aBattleMonMenu);
    return BattleMonMenu();
    // RET;
}

bool BattleMenu(void){
BattleMenu_begin:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aLoadTempTilemapToTilemap);
    LoadTempTilemapToTilemap_Conv();

    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_DEBUG);
    // IF_Z goto ok;
    // CP_A(BATTLETYPE_TUTORIAL);
    // IF_Z goto ok;
    if(wram->wBattleType != BATTLETYPE_DEBUG && wram->wBattleType != BATTLETYPE_TUTORIAL) {
        // CALL(aEmptyBattleTextbox);
        EmptyBattleTextbox();
        // CALL(aUpdateBattleHuds);
        UpdateBattleHuds();
        // CALL(aEmptyBattleTextbox);
        EmptyBattleTextbox();
        // CALL(aLoadTilemapToTempTilemap);
        LoadTilemapToTempTilemap_Conv();
    }
// ok:

    while(1) {
    // loop:
        // LD_A_addr(wBattleType);
        // CP_A(BATTLETYPE_CONTEST);
        // IF_NZ goto not_contest;
        if(wram->wBattleType != BATTLETYPE_CONTEST) {
        // not_contest:

        // Auto input: choose "ITEM"
            // LD_A_addr(wInputType);
            // OR_A_A;
            // IF_Z goto skip_dude_pack_select;
            if(wram->wInputType != 0)
                // FARCALL(av_DudeAutoInput_DownA);
                v_DudeAutoInput_DownA();

        // skip_dude_pack_select:
            // CALL(aLoadBattleMenu2);
            // RET_C ;
            if(LoadBattleMenu2())
                return true;
        }
        else {
            // FARCALL(aContestBattleMenu);
            ContestBattleMenu();
            // goto next;
        }

    // next:
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // LD_A_addr(wBattleMenuCursorPosition);
        // CP_A(0x1);
        // JP_Z (mBattleMenu_Fight);
        // CP_A(0x3);
        // JP_Z (mBattleMenu_Pack);
        // CP_A(0x2);
        // JP_Z (mBattleMenu_PKMN);
        // CP_A(0x4);
        // JP_Z (mBattleMenu_Run);
        switch(wram->wBattleMenuCursorPosition) {
            case 0x1: {
            // BattleMenu_Fight:
                // XOR_A_A;
                // LD_addr_A(wNumFleeAttempts);
                wram->wNumFleeAttempts = 0;
                // CALL(aSafeLoadTempTilemapToTilemap);
                SafeLoadTempTilemapToTilemap_Conv();
                // AND_A_A;
                // RET;
                return false;
            }
            case 0x3: {
            // BattleMenu_Pack:
                // LD_A_addr(wLinkMode);
                // AND_A_A;
                // JP_NZ (mBattleMenu_Pack_ItemsCantBeUsed);

                // LD_A_addr(wInBattleTowerBattle);
                // AND_A_A;
                // JP_NZ (mBattleMenu_Pack_ItemsCantBeUsed);
                if(wram->wLinkMode != 0 || wram->wInBattleTowerBattle) {
                // ItemsCantBeUsed:
                    // LD_HL(mBattleText_ItemsCantBeUsedHere);
                    // CALL(aStdBattleTextbox);
                    StdBattleTextbox_Conv2(BattleText_ItemsCantBeUsedHere);
                    // JP(mBattleMenu);
                    goto BattleMenu_begin;
                }

                // CALL(aLoadStandardMenuHeader);
                LoadStandardMenuHeader_Conv();

                // LD_A_addr(wBattleType);
                // CP_A(BATTLETYPE_TUTORIAL);
                // IF_Z goto tutorial;
                // CP_A(BATTLETYPE_CONTEST);
                // IF_Z goto contest;
                switch(wram->wBattleType) {
                    default:
                        // FARCALL(aBattlePack);
                        BattlePack();
                        // LD_A_addr(wBattlePlayerAction);
                        // AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
                        // IF_Z goto didnt_use_item;
                        if(wram->wBattlePlayerAction == BATTLEPLAYERACTION_USEMOVE) {
                        // didnt_use_item:
                            // CALL(aClearPalettes);
                            ClearPalettes_Conv();
                            // CALL(aDelayFrame);
                            DelayFrame();
                            // CALL(av_LoadBattleFontsHPBar);
                            v_LoadBattleFontsHPBar();
                            // CALL(aGetBattleMonBackpic);
                            GetBattleMonBackpic();
                            // CALL(aGetEnemyMonFrontpic);
                            GetEnemyMonFrontpic();
                            // CALL(aExitMenu);
                            ExitMenu_Conv2();
                            // CALL(aWaitBGMap);
                            WaitBGMap_Conv();
                            // CALL(aFinishBattleAnim);
                            FinishBattleAnim();
                            // CALL(aLoadTilemapToTempTilemap);
                            LoadTilemapToTempTilemap_Conv();
                            // JP(mBattleMenu);
                            goto BattleMenu_begin;
                        }
                        // goto got_item;
                        break;
                    case BATTLETYPE_TUTORIAL:
                    // tutorial:
                        // FARCALL(aTutorialPack);
                        TutorialPack();
                        // LD_A(POKE_BALL);
                        // LD_addr_A(wCurItem);
                        wram->wCurItem = POKE_BALL;
                        // CALL(aDoItemEffect);
                        DoItemEffect();
                        // goto got_item;
                        break;
                    case BATTLETYPE_CONTEST:
                    // contest:
                        // LD_A(PARK_BALL);
                        // LD_addr_A(wCurItem);
                        wram->wCurItem = PARK_BALL;
                        // CALL(aDoItemEffect);
                        DoItemEffect();
                        break;
                }

            // got_item:
                // CALL(aBattleMenu_Pack_UseItem);
                // RET;
            // UseItem:
                // LD_A_addr(wWildMon);
                // AND_A_A;
                // IF_NZ goto run;
                if(wram->wWildMon != 0) {
                // run:
                    // XOR_A_A;
                    // LD_addr_A(wWildMon);
                    wram->wWildMon = 0;
                    // LD_A_addr(wBattleResult);
                    // AND_A(BATTLERESULT_BITMASK);
                    // LD_addr_A(wBattleResult);  // WIN
                    wram->wBattleResult &= BATTLERESULT_BITMASK;
                    // CALL(aClearWindowData);
                    ClearWindowData_Conv2();
                    // CALL(aSetPalettes);
                    SetPalettes_Conv();
                    // SCF;
                    // RET;
                    return true;
                }
                // CALLFAR(aCheckItemPocket);
                // LD_A_addr(wItemAttributeValue);
                // CP_A(BALL);
                // IF_Z goto ball;
                if(CheckItemPocket_Conv(wram->wCurItem) != BALL) {
                    // CALL(aClearBGPalettes);
                    ClearBGPalettes_Conv();
                }

            // ball:
                // XOR_A_A;
                // LDH_addr_A(hBGMapMode);
                hram->hBGMapMode = 0;
                // CALL(av_LoadBattleFontsHPBar);
                v_LoadBattleFontsHPBar();
                // CALL(aClearSprites);
                ClearSprites_Conv();
                // LD_A_addr(wBattleType);
                // CP_A(BATTLETYPE_TUTORIAL);
                // IF_Z goto tutorial2;
                if(wram->wBattleType != BATTLETYPE_TUTORIAL) {
                    // CALL(aGetBattleMonBackpic);
                    GetBattleMonBackpic();
                }

            // tutorial2:
                // CALL(aGetEnemyMonFrontpic);
                GetEnemyMonFrontpic();
                // LD_A(0x1);
                // LD_addr_A(wMenuCursorY);
                wram->wMenuCursorY = 0x1;
                // CALL(aExitMenu);
                ExitMenu_Conv2();
                // CALL(aUpdateBattleHUDs);
                UpdateBattleHUDs();
                // CALL(aWaitBGMap);
                WaitBGMap_Conv();
                // CALL(aLoadTilemapToTempTilemap);
                LoadTilemapToTempTilemap_Conv();
                // CALL(aClearWindowData);
                ClearWindowData_Conv2();
                // CALL(aFinishBattleAnim);
                FinishBattleAnim();
                // AND_A_A;
                // RET;
                return false;
            } break;
            case 0x2: {
            // BattleMenu_PKMN:
                // CALL(aLoadStandardMenuHeader);
                LoadStandardMenuHeader_Conv();

            BattleMenuPKMN_ReturnFromStats:
                // CALL(aExitMenu);
                ExitMenu_Conv2();
                // CALL(aLoadStandardMenuHeader);
                LoadStandardMenuHeader_Conv();
                // CALL(aClearBGPalettes);
                ClearBGPalettes_Conv();

                while(1) {
                BattleMenuPKMN_Loop:
                    // CALL(aSetUpBattlePartyMenu_Loop);
                    SetUpBattlePartyMenu_Loop();
                    // XOR_A_A;
                    // LD_addr_A(wPartyMenuActionText);
                    wram->wPartyMenuActionText = 0;
                    // CALL(aJumpToPartyMenuAndPrintText);
                    JumpToPartyMenuAndPrintText();
                    // CALL(aSelectBattleMon);
                    u8_flag_s res = SelectBattleMon();
                    // IF_C goto Cancel;
                    if(res.flag)
                        goto Cancel;

                    while(1) {
                    // loop:
                        // FARCALL(aFreezeMonIcons);
                        FreezeMonIcons_Conv();
                        // CALL(aBattleMenuPKMN_Loop_GetMenu);
                        // IF_C goto PressedB;
                        if(BattleMenu_PKMN_GetMenu())
                            break;
                        // CALL(aPlaceHollowCursor);
                        PlaceHollowCursor_Conv();
                        // LD_A_addr(wMenuCursorY);
                        switch(wram->wMenuCursorY) {
                            // CP_A(0x1);  // SWITCH
                            // JP_Z (mTryPlayerSwitch);
                            case 0x1: {  // SWITCH
                            // TryPlayerSwitch:
                                // LD_A_addr(wCurBattleMon);
                                // LD_D_A;
                                // LD_A_addr(wCurPartyMon);
                                // CP_A_D;
                                // IF_NZ goto check_trapped;
                                if(wram->wCurBattleMon == wram->wCurPartyMon) {
                                    // LD_HL(mBattleText_MonIsAlreadyOut);
                                    // CALL(aStdBattleTextbox);
                                    StdBattleTextbox_Conv2(BattleText_MonIsAlreadyOut);
                                    // JP(mBattleMenuPKMN_Loop);
                                    goto BattleMenuPKMN_Loop;
                                }

                            // check_trapped:
                                // LD_A_addr(wPlayerWrapCount);
                                // AND_A_A;
                                // IF_NZ goto trapped;
                                // LD_A_addr(wEnemySubStatus5);
                                // BIT_A(SUBSTATUS_CANT_RUN);
                                // IF_Z goto try_switch;
                                if(wram->wPlayerWrapCount != 0 || bit_test(wram->wEnemySubStatus5, SUBSTATUS_CANT_RUN)) {
                                // trapped:
                                    // LD_HL(mBattleText_MonCantBeRecalled);
                                    // CALL(aStdBattleTextbox);
                                    StdBattleTextbox_Conv2(BattleText_MonCantBeRecalled);
                                    // JP(mBattleMenuPKMN_Loop);
                                    goto BattleMenuPKMN_Loop;
                                }

                            // try_switch:
                                // CALL(aCheckIfCurPartyMonIsFitToFight);
                                // JP_Z (mBattleMenuPKMN_Loop);
                                if(!CheckIfCurPartyMonIsFitToFight_Conv())
                                    goto BattleMenuPKMN_Loop;
                                // LD_A_addr(wCurBattleMon);
                                // LD_addr_A(wLastPlayerMon);
                                wram->wLastPlayerMon = wram->wCurBattleMon;
                                // LD_A(BATTLEPLAYERACTION_SWITCH);
                                // LD_addr_A(wBattlePlayerAction);
                                wram->wBattlePlayerAction = BATTLEPLAYERACTION_SWITCH;
                                // CALL(aClearPalettes);
                                ClearPalettes_Conv();
                                // CALL(aDelayFrame);
                                DelayFrame();
                                // CALL(aClearSprites);
                                ClearSprites_Conv();
                                // CALL(av_LoadHPBar);
                                v_LoadHPBar_Conv();
                                // CALL(aCloseWindow);
                                CloseWindow_Conv2();
                                // CALL(aGetMemSGBLayout);
                                GetMemSGBLayout_Conv();
                                // CALL(aSetPalettes);
                                SetPalettes_Conv();
                                // LD_A_addr(wCurPartyMon);
                                // LD_addr_A(wCurBattleMon);
                                wram->wCurBattleMon = wram->wCurPartyMon;
                                return PlayerSwitch();
                            } break;
                            // CP_A(0x2);  // STATS
                            // IF_Z goto Stats;
                            case 0x2:  // STATS
                            // Stats:
                                // CALL(aBattle_StatsScreen);
                                Battle_StatsScreen();
                                // CALL(aCheckMobileBattleError);
                                // IF_C goto Cancel;
                                if(CheckMobileBattleError_Conv())
                                    goto Cancel;
                                // JP(mBattleMenuPKMN_ReturnFromStats);
                                goto BattleMenuPKMN_ReturnFromStats;
                            // CP_A(0x3);  // CANCEL
                            // IF_Z goto Cancel;
                            case 0x3:  // CANCEL
                                goto Cancel;
                        }
                        // goto loop;
                    }


                // PressedB:
                    // CALL(aCheckMobileBattleError);
                    // IF_C goto Cancel;
                    // JR(mBattleMenuPKMN_Loop);
                    if(CheckMobileBattleError_Conv()) {
                    Cancel:
                        // CALL(aClearSprites);
                        ClearSprites_Conv();
                        // CALL(aClearPalettes);
                        ClearPalettes_Conv();
                        // CALL(aDelayFrame);
                        DelayFrame();
                        // CALL(av_LoadHPBar);
                        v_LoadHPBar_Conv();
                        // CALL(aCloseWindow);
                        CloseWindow_Conv2();
                        // CALL(aLoadTilemapToTempTilemap);
                        LoadTilemapToTempTilemap_Conv();
                        // CALL(aGetMemSGBLayout);
                        GetMemSGBLayout_Conv();
                        // CALL(aSetPalettes);
                        SetPalettes_Conv();
                        // JP(mBattleMenu);
                        goto BattleMenu_begin;
                    }
                    continue;
                }
            } break;
            case 0x4: {
            // BattleMenu_Run:
                // CALL(aSafeLoadTempTilemapToTilemap);
                SafeLoadTempTilemapToTilemap_Conv();
                // LD_A(0x3);
                // LD_addr_A(wMenuCursorY);
                wram->wMenuCursorY = 0x3;
                // LD_HL(wBattleMonSpeed);
                // LD_DE(wEnemyMonSpeed);
                // CALL(aTryToRunAwayFromBattle);
                bool success = TryToRunAwayFromBattle_Conv(&wram->wBattleMon, &wram->wEnemyMon);
                // LD_A(FALSE);
                // LD_addr_A(wFailedToFlee);
                wram->wFailedToFlee = FALSE;
                // RET_C ;
                if(success)
                    return true;
                // LD_A_addr(wBattlePlayerAction);
                // AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
                // RET_NZ ;
                if(wram->wBattlePlayerAction != 0)
                    return false;
                // JP(mBattleMenu);
            } goto BattleMenu_begin;
            default: break;
        }
        // goto loop;
    }
}

void BattleMenu_Fight(void){
    XOR_A_A;
    LD_addr_A(wNumFleeAttempts);
    CALL(aSafeLoadTempTilemapToTilemap);
    AND_A_A;
    RET;
}

bool LoadBattleMenu2(void){
    // CALL(aIsMobileBattle);
    // IF_Z goto mobile;
    if(!IsMobileBattle_Conv()) {
        // FARCALL(aLoadBattleMenu);
        LoadBattleMenu_Conv();
        // AND_A_A;
        // RET;
        return false;
    }

// mobile:
    // FARCALL(aMobile_LoadBattleMenu);
    //  TODO: Mobile_LoadBattleMenu stuff
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd2b == 0)
        return false;

    // LD_HL(wcd2a);
    // BIT_hl(4);
    // IF_NZ goto error;
    if(!bit_test(wram->wcd2a, 4)) {
        // LD_HL(mBattleText_LinkErrorBattleCanceled);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(BattleText_LinkErrorBattleCanceled);
        // LD_C(60);
        // CALL(aDelayFrames);
        DelayFrames_Conv(60);
    }

// error:
    // SCF;
    // RET;
    return true;
}

void BattleMenu_Pack(void){
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_NZ (mBattleMenu_Pack_ItemsCantBeUsed);

    LD_A_addr(wInBattleTowerBattle);
    AND_A_A;
    JP_NZ (mBattleMenu_Pack_ItemsCantBeUsed);

    CALL(aLoadStandardMenuHeader);

    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    IF_Z goto tutorial;
    CP_A(BATTLETYPE_CONTEST);
    IF_Z goto contest;

    FARCALL(aBattlePack);
    LD_A_addr(wBattlePlayerAction);
    AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    IF_Z goto didnt_use_item;
    goto got_item;


tutorial:
    FARCALL(aTutorialPack);
    LD_A(POKE_BALL);
    LD_addr_A(wCurItem);
    CALL(aDoItemEffect);
    goto got_item;


contest:
    LD_A(PARK_BALL);
    LD_addr_A(wCurItem);
    CALL(aDoItemEffect);


got_item:
    CALL(aBattleMenu_Pack_UseItem);
    RET;


didnt_use_item:
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadBattleFontsHPBar);
    CALL(aGetBattleMonBackpic);
    CALL(aGetEnemyMonFrontpic);
    CALL(aExitMenu);
    CALL(aWaitBGMap);
    CALL(aFinishBattleAnim);
    CALL(aLoadTilemapToTempTilemap);
    JP(mBattleMenu);


ItemsCantBeUsed:
    LD_HL(mBattleText_ItemsCantBeUsedHere);
    CALL(aStdBattleTextbox);
    JP(mBattleMenu);


UseItem:
    LD_A_addr(wWildMon);
    AND_A_A;
    IF_NZ goto run;
    CALLFAR(aCheckItemPocket);
    LD_A_addr(wItemAttributeValue);
    CP_A(BALL);
    IF_Z goto ball;
    CALL(aClearBGPalettes);


ball:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(av_LoadBattleFontsHPBar);
    CALL(aClearSprites);
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    IF_Z goto tutorial2;
    CALL(aGetBattleMonBackpic);


tutorial2:
    CALL(aGetEnemyMonFrontpic);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    CALL(aExitMenu);
    CALL(aUpdateBattleHUDs);
    CALL(aWaitBGMap);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aClearWindowData);
    CALL(aFinishBattleAnim);
    AND_A_A;
    RET;


run:
    XOR_A_A;
    LD_addr_A(wWildMon);
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    LD_addr_A(wBattleResult);  // WIN
    CALL(aClearWindowData);
    CALL(aSetPalettes);
    SCF;
    RET;

}

void BattleMenu_PKMN(void){
    CALL(aLoadStandardMenuHeader);
    return BattleMenuPKMN_ReturnFromStats();
}

void BattleMenuPKMN_ReturnFromStats(void){
    CALL(aExitMenu);
    CALL(aLoadStandardMenuHeader);
    CALL(aClearBGPalettes);
    return BattleMenuPKMN_Loop();
}

void BattleMenuPKMN_Loop(void){
    CALL(aSetUpBattlePartyMenu_Loop);
    XOR_A_A;
    LD_addr_A(wPartyMenuActionText);
    CALL(aJumpToPartyMenuAndPrintText);
    CALL(aSelectBattleMon);
    IF_C goto Cancel;

loop:
    FARCALL(aFreezeMonIcons);
    CALL(aBattleMenuPKMN_Loop_GetMenu);
    IF_C goto PressedB;
    CALL(aPlaceHollowCursor);
    LD_A_addr(wMenuCursorY);
    CP_A(0x1);  // SWITCH
    JP_Z (mTryPlayerSwitch);
    CP_A(0x2);  // STATS
    IF_Z goto Stats;
    CP_A(0x3);  // CANCEL
    IF_Z goto Cancel;
    goto loop;


PressedB:
    CALL(aCheckMobileBattleError);
    IF_C goto Cancel;
    JR(mBattleMenuPKMN_Loop);


Stats:
    CALL(aBattle_StatsScreen);
    CALL(aCheckMobileBattleError);
    IF_C goto Cancel;
    JP(mBattleMenuPKMN_ReturnFromStats);


Cancel:
    CALL(aClearSprites);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(av_LoadHPBar);
    CALL(aCloseWindow);
    CALL(aLoadTilemapToTempTilemap);
    CALL(aGetMemSGBLayout);
    CALL(aSetPalettes);
    JP(mBattleMenu);


GetMenu:
    CALL(aIsMobileBattle);
    IF_Z goto mobile;
    FARCALL(aBattleMonMenu);
    RET;


mobile:
    FARCALL(aMobileBattleMonMenu);
    RET;

}

void Battle_StatsScreen(void){
    // CALL(aDisableLCD);
    DisableLCD();

    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(vTiles0);
    // LD_BC(0x11 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(vram->vTiles0, vram->vTiles2 + LEN_2BPP_TILE * 0x31, 0x11 * LEN_2BPP_TILE);

    // LD_HL(vTiles2);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x11);
    // LD_BC(0x31 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(vram->vTiles0 + LEN_2BPP_TILE * 0x11, vram->vTiles2, 0x31 * LEN_2BPP_TILE);

    // CALL(aEnableLCD);
    EnableLCD();

    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aLowVolume);
    LowVolume_Conv();
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // FARCALL(aBattleStatsScreenInit);
    BattleStatsScreenInit();
    // CALL(aMaxVolume);
    MaxVolume_Conv();

    // CALL(aDisableLCD);
    DisableLCD();

    // LD_HL(vTiles0);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_BC(0x11 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, vram->vTiles0, 0x11 * LEN_2BPP_TILE);

    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x11);
    // LD_DE(vTiles2);
    // LD_BC(0x31 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(vram->vTiles2, vram->vTiles0 + LEN_2BPP_TILE * 0x11, 0x31 * LEN_2BPP_TILE);

    // CALL(aEnableLCD);
    EnableLCD();
    // RET;
}

void TryPlayerSwitch(void){
    LD_A_addr(wCurBattleMon);
    LD_D_A;
    LD_A_addr(wCurPartyMon);
    CP_A_D;
    IF_NZ goto check_trapped;
    LD_HL(mBattleText_MonIsAlreadyOut);
    CALL(aStdBattleTextbox);
    JP(mBattleMenuPKMN_Loop);


check_trapped:
    LD_A_addr(wPlayerWrapCount);
    AND_A_A;
    IF_NZ goto trapped;
    LD_A_addr(wEnemySubStatus5);
    BIT_A(SUBSTATUS_CANT_RUN);
    IF_Z goto try_switch;


trapped:
    LD_HL(mBattleText_MonCantBeRecalled);
    CALL(aStdBattleTextbox);
    JP(mBattleMenuPKMN_Loop);


try_switch:
    CALL(aCheckIfCurPartyMonIsFitToFight);
    JP_Z (mBattleMenuPKMN_Loop);
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wLastPlayerMon);
    LD_A(BATTLEPLAYERACTION_SWITCH);
    LD_addr_A(wBattlePlayerAction);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(aClearSprites);
    CALL(av_LoadHPBar);
    CALL(aCloseWindow);
    CALL(aGetMemSGBLayout);
    CALL(aSetPalettes);
    LD_A_addr(wCurPartyMon);
    LD_addr_A(wCurBattleMon);
    // return PlayerSwitch();
}

bool PlayerSwitch(void){
    // LD_A(1);
    // LD_addr_A(wPlayerIsSwitching);
    wram->wPlayerIsSwitching = 1;
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;
    if(wram->wLinkMode != 0) {
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader_Conv();
        // CALL(aLinkBattleSendReceiveAction);
        LinkBattleSendReceiveAction();
        // CALL(aCloseWindow);
        CloseWindow_Conv2();
    }

// not_linked:
    // CALL(aParseEnemyAction);
    ParseEnemyAction();
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto linked;

    if(wram->wLinkMode == 0){
    // switch_:
        // CALL(aBattleMonEntrance);
        BattleMonEntrance();
        // AND_A_A;
        // RET;
        return false;
    }

// linked:
    // LD_A_addr(wBattleAction);
    // CP_A(BATTLEACTION_STRUGGLE);
    // JP_Z (mPlayerSwitch_switch);
    if(wram->wBattleAction == BATTLEACTION_STRUGGLE
    || wram->wBattleAction == BATTLEACTION_SKIPTURN
    || wram->wBattleAction <  BATTLEACTION_SWITCH1) {
    // switch_:
        // CALL(aBattleMonEntrance);
        BattleMonEntrance();
        // AND_A_A;
        // RET;
        return false;
    }
    // CP_A(BATTLEACTION_SKIPTURN);
    // JP_Z (mPlayerSwitch_switch);
    // CP_A(BATTLEACTION_SWITCH1);
    // JP_C (mPlayerSwitch_switch);
    // CP_A(BATTLEACTION_FORFEIT);
    // IF_NZ goto dont_run;
    if(wram->wBattleAction == BATTLEACTION_FORFEIT){
        // CALL(aWildFled_EnemyFled_LinkBattleCanceled);
        WildFled_EnemyFled_LinkBattleCanceled();
        // RET;
        return true;
    }

// dont_run:
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // IF_Z goto player_1;
    if(hram->hSerialConnectionStatus != USING_EXTERNAL_CLOCK){
        // CALL(aBattleMonEntrance);
        BattleMonEntrance();
        // CALL(aEnemyMonEntrance);
        EnemyMonEntrance();
        // AND_A_A;
        // RET;
        return false;
    }
    else {
    // player_1:
        // CALL(aEnemyMonEntrance);
        EnemyMonEntrance();
        // CALL(aBattleMonEntrance);
        BattleMonEntrance();
        // AND_A_A;
        // RET;
        return false;
    }
}

void EnemyMonEntrance(void){
    // CALLFAR(aAI_Switch);
    AI_Switch();
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // JP(mSpikesDamage);
    return SpikesDamage();
}

void BattleMonEntrance(void){
    // CALL(aWithdrawMonText);
    WithdrawMonText();

    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames_Conv(50);

    // LD_HL(wPlayerSubStatus4);
    // RES_hl(SUBSTATUS_RAGE);
    bit_reset(wram->wPlayerSubStatus4, SUBSTATUS_RAGE);

    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // CALL(aPursuitSwitch);
    // IF_C goto ok;
    if(!PursuitSwitch()){
        // CALL(aRecallPlayerMon);
        RecallPlayerMon();
    }

// ok:
    // hlcoord(9, 7, wTilemap);
    // LD_BC((5 << 8) | 11);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(9, 7, wram->wTilemap), 11, 5);

    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wCurBattleMon;
    // CALL(aAddBattleParticipant);
    AddBattleParticipant();
    // CALL(aInitBattleMon);
    InitBattleMon();
    // CALL(aResetPlayerStatLevels);
    ResetPlayerStatLevels();
    // CALL(aSendOutMonText);
    SendOutMonText();
    // CALL(aNewBattleMonStatus);
    NewBattleMonStatus();
    // CALL(aBreakAttraction);
    BreakAttraction();
    // CALL(aSendOutPlayerMon);
    SendOutPlayerMon();
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // CALL(aSpikesDamage);
    SpikesDamage();
    // LD_A(0x2);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 0x2;
    // RET;
}

void PassedBattleMonEntrance(void){
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames_Conv(50);

    // hlcoord(9, 7, wTilemap);
    // LD_BC((5 << 8) | 11);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(9, 7, wram->wTilemap), 5, 11);

    // LD_A_addr(wCurPartyMon);
    // LD_addr_A(wCurBattleMon);
    wram->wCurBattleMon = wram->wCurPartyMon;
    // CALL(aAddBattleParticipant);
    AddBattleParticipant();
    // CALL(aInitBattleMon);
    InitBattleMon();
    // XOR_A_A;  // FALSE
    // LD_addr_A(wApplyStatLevelMultipliersToEnemy);
    wram->wApplyStatLevelMultipliersToEnemy = FALSE;
    // CALL(aApplyStatLevelMultiplierOnAllStats);
    ApplyStatLevelMultiplierOnAllStats();
    // CALL(aSendOutPlayerMon);
    SendOutPlayerMon();
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // JP(mSpikesDamage);
    return SpikesDamage();
}

void BattleMenu_Run(void){
    CALL(aSafeLoadTempTilemapToTilemap);
    LD_A(0x3);
    LD_addr_A(wMenuCursorY);
    LD_HL(wBattleMonSpeed);
    LD_DE(wEnemyMonSpeed);
    CALL(aTryToRunAwayFromBattle);
    LD_A(FALSE);
    LD_addr_A(wFailedToFlee);
    RET_C ;
    LD_A_addr(wBattlePlayerAction);
    AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    RET_NZ ;
    JP(mBattleMenu);

}

void CheckAmuletCoin(void){
    LD_A_addr(wBattleMonItem);
    LD_B_A;
    CALLFAR(aGetItemHeldEffect);
    LD_A_B;
    CP_A(HELD_AMULET_COIN);
    RET_NZ ;
    LD_A(1);
    LD_addr_A(wAmuletCoin);
    RET;

}

void CheckAmuletCoin_Conv(void){
    // LD_A_addr(wBattleMonItem);
    // LD_B_A;
    // CALLFAR(aGetItemHeldEffect);
    // LD_A_B;
    // CP_A(HELD_AMULET_COIN);
    // RET_NZ ;
    if(HIGH(GetItemHeldEffect_Conv(wram->wBattleMon.item)) == HELD_AMULET_COIN) {
        // LD_A(1);
        // LD_addr_A(wAmuletCoin);
        wram->wAmuletCoin = TRUE;
    }
    // RET;
}

static void MoveSelectionScreen_swap(void* hl, size_t size) {
    // PUSH_HL;
    // LD_A_addr(wSwappingMove);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    uint8_t* a = ((uint8_t*)hl) + (wram->wSwappingMove - 1) * size;
    // POP_HL;
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_de;
    // LD_B_hl;
    // LD_hl_A;
    // LD_A_B;
    // LD_de_A;
    uint8_t* b = ((uint8_t*)hl) + (wram->wMenuCursorY - 1) * size;
    // RET;
    MemSwap(a, b, size);
}

bool MoveSelectionScreen(void){
    static const char empty_string[] = "@";
MoveSelectionScreen:
    // CALL(aIsMobileBattle);
    // IF_NZ goto not_mobile;
    // FARCALL(aMobile_MoveSelectionScreen);
    // RET;
    if(IsMobileBattle_Conv()) {
    // TODO: Convert Mobile_MoveSelectionScreen
        // FARCALL(aMobile_MoveSelectionScreen);
        // RET;
        return false;
    }

// not_mobile:
    // LD_HL(wEnemyMonMoves);
    move_t* moves = wram->wEnemyMon.moves;
    // LD_A_addr(wMoveSelectionMenuType);
    // DEC_A;
    // IF_Z goto got_menu_type;
    if(wram->wMoveSelectionMenuType == 0x1) {}
    // DEC_A;
    // IF_Z goto ether_elixer_menu;
    else if(wram->wMoveSelectionMenuType == 0x2) {
    // ether_elixer_menu:
        // LD_A(MON_MOVES);
        // CALL(aGetPartyParamLocation);
        moves = wram->wPartyMon[wram->wCurPartyMon].mon.moves;
    }
    // CALL(aCheckPlayerHasUsableMoves);
    // RET_Z ;  // use Struggle
    else if(!CheckPlayerHasUsableMoves())
        return false;  // use Struggle
    else {
        // LD_HL(wBattleMonMoves);
        moves = wram->wBattleMon.moves;
        // goto got_menu_type;
    }

// got_menu_type:
    // LD_DE(wListMoves_MoveIndicesBuffer);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wListMoves_MoveIndicesBuffer, moves, sizeof(*moves) * NUM_MOVES);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;

    tile_t* hl;
    uint8_t b;
    uint8_t c;
    if(wram->wMoveSelectionMenuType != 0x2) {
        // hlcoord(4, 17 - NUM_MOVES - 1, wTilemap);
        hl = coord(4, 17 - NUM_MOVES - 1, wram->wTilemap);
        // LD_B(4);
        b = 4;
        // LD_C(14);
        c = 14;
        // LD_A_addr(wMoveSelectionMenuType);
        // CP_A(0x2);
        // IF_NZ goto got_dims;
    }
    else {
        // hlcoord(4, 17 - NUM_MOVES - 1 - 4, wTilemap);
        hl = coord(4, 17 - NUM_MOVES - 1 - 4, wram->wTilemap);
        // LD_B(4);
        b = 4;
        // LD_C(14);
        c = 14;
    }

// got_dims:
    // CALL(aTextbox);
    Textbox_Conv2(hl, b, c);

    // hlcoord(6, 17 - NUM_MOVES, wTilemap);
    // LD_A_addr(wMoveSelectionMenuType);
    // CP_A(0x2);
    // IF_NZ goto got_start_coord;
    // hlcoord(6, 17 - NUM_MOVES - 4, wTilemap);
    hl = (wram->wMoveSelectionMenuType == 0x2)? coord(6, 17 - NUM_MOVES - 4, wram->wTilemap): coord(6, 17 - NUM_MOVES, wram->wTilemap);

// got_start_coord:
    // LD_A(SCREEN_WIDTH);
    // LD_addr_A(wListMovesLineSpacing);
    wram->wListMovesLineSpacing = SCREEN_WIDTH;
    // PREDEF(pListMoves);
    ListMoves_Conv(hl);

    if(wram->wMoveSelectionMenuType != 0x2) {
        // LD_B(5);
        wram->w2DMenuCursorInitX = 5;
        // LD_A_addr(wMoveSelectionMenuType);
        // CP_A(0x2);
        // LD_A(17 - NUM_MOVES);
        wram->w2DMenuCursorInitY = 17 - NUM_MOVES;
        // IF_NZ goto got_default_coord;
    }
    else {
        // LD_B(5);
        wram->w2DMenuCursorInitX = 5;
        // LD_A(17 - NUM_MOVES - 4);
        wram->w2DMenuCursorInitY = 17 - NUM_MOVES - 4;
    }

// got_default_coord:
    // LD_addr_A(w2DMenuCursorInitY);
    // LD_A_B;
    // LD_addr_A(w2DMenuCursorInitX);
    // LD_A_addr(wMoveSelectionMenuType);
    // CP_A(0x1);
    // IF_Z goto skip_inc;
    if(wram->wMoveSelectionMenuType != 0x1) {
        // LD_A_addr(wCurMoveNum);
        // INC_A;
        wram->wMenuCursorY = wram->wCurMoveNum + 1;
    }
    else {
        wram->wMenuCursorY = 0x1;
    }

// skip_inc:
    // LD_addr_A(wMenuCursorY);
    // LD_A(1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // LD_A_addr(wNumMoves);
    // INC_A;
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wNumMoves + 1;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_C(STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP);
    c = STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP;
    // LD_A_addr(wMoveSelectionMenuType);
    // DEC_A;
    if(wram->wMoveSelectionMenuType == 0x1) {
        // LD_B(D_DOWN | D_UP | A_BUTTON);
        wram->wMenuJoypadFilter = D_DOWN | D_UP | A_BUTTON;
        // IF_Z goto okay;
    }
    // DEC_A;
    else if(wram->wMoveSelectionMenuType == 0x2 || wram->wLinkMode != 0) {
        // LD_B(D_DOWN | D_UP | A_BUTTON | B_BUTTON);
        wram->wMenuJoypadFilter = D_DOWN | D_UP | A_BUTTON | B_BUTTON;
        // IF_Z goto okay;
        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // IF_NZ goto okay;
    }
    else {
        // LD_B(D_DOWN | D_UP | A_BUTTON | B_BUTTON | SELECT);
        wram->wMenuJoypadFilter = D_DOWN | D_UP | A_BUTTON | B_BUTTON | SELECT;
    }

// okay:
    // LD_A_B;
    // LD_addr_A(wMenuJoypadFilter);
    // LD_A_C;
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = c;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0x0;
    // LD_A(0x10);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = 0x10;

    while(1) {
    // menu_loop:
        // LD_A_addr(wMoveSelectionMenuType);
        // AND_A_A;
        // IF_Z goto battle_player_moves;
        if(wram->wMoveSelectionMenuType != 0x0) {
            // DEC_A;
            // IF_NZ goto interpret_joypad;
            if(wram->wMoveSelectionMenuType == 0x1) {
                // hlcoord(11, 14, wTilemap);
                // LD_DE(mMoveSelectionScreen_empty_string);
                // CALL(aPlaceString);
                PlaceStringSimple(U82C(empty_string), coord(11, 14, wram->wTilemap)); // Dummied out text?
            }
            // goto interpret_joypad;
        }
        else {
        // battle_player_moves:
            // CALL(aMoveInfoBox);
            MoveInfoBox();
            // LD_A_addr(wSwappingMove);
            // AND_A_A;
            // IF_Z goto interpret_joypad;
            if(wram->wSwappingMove) {
                // hlcoord(5, 13, wTilemap);
                // LD_BC(SCREEN_WIDTH);
                // DEC_A;
                // CALL(aAddNTimes);
                // LD_hl(0xec);
                coord(5, 13, wram->wTilemap)[wram->wSwappingMove - 1] = 0xec;
            }
        }

    // interpret_joypad:
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // CALL(aScrollingMenuJoypad);
        uint8_t joypad = ScrollingMenuJoypad_Conv();
        // BIT_A(D_UP_F);
        // JP_NZ (mMoveSelectionScreen_pressed_up);
        if(bit_test(joypad, D_UP_F)) {
        // pressed_up:
            // LD_A_addr(wMenuCursorY);
            // AND_A_A;
            // JP_NZ (mMoveSelectionScreen_menu_loop);
            if(wram->wMenuCursorY != 0)
                continue;
            // LD_A_addr(wNumMoves);
            // INC_A;
            // LD_addr_A(wMenuCursorY);
            wram->wMenuCursorY = wram->wNumMoves + 1;
            // JP(mMoveSelectionScreen_menu_loop);
            continue;
        }
        // BIT_A(D_DOWN_F);
        // JP_NZ (mMoveSelectionScreen_pressed_down);
        else if(bit_test(joypad, D_DOWN_F)) {
        // pressed_down:
            // LD_A_addr(wMenuCursorY);
            // LD_B_A;
            // LD_A_addr(wNumMoves);
            // INC_A;
            // INC_A;
            // CP_A_B;
            // JP_NZ (mMoveSelectionScreen_menu_loop);
            if(wram->wMenuCursorY != wram->wNumMoves + 2)
                continue;
            // LD_A(0x1);
            // LD_addr_A(wMenuCursorY);
            wram->wMenuCursorY = 0x1;
            // JP(mMoveSelectionScreen_menu_loop);
            continue;
        }
        // BIT_A(SELECT_F);
        // JP_NZ (mMoveSelectionScreen_pressed_select);
        else if(bit_test(joypad, SELECT_F)) {
        // pressed_select:
            // LD_A_addr(wSwappingMove);
            // AND_A_A;
            // IF_Z goto start_swap;
            if(!wram->wSwappingMove) {
            // start_swap:
                // LD_A_addr(wMenuCursorY);
                // LD_addr_A(wSwappingMove);
                wram->wSwappingMove = wram->wMenuCursorY;
                // JP(mMoveSelectionScreen);
                goto MoveSelectionScreen;
            }
            // LD_HL(wBattleMonMoves);
            // CALL(aMoveSelectionScreen_swap_bytes);
            MoveSelectionScreen_swap(wram->wBattleMon.moves, sizeof(wram->wBattleMon.moves[0]));
            // LD_HL(wBattleMonPP);
            // CALL(aMoveSelectionScreen_swap_bytes);
            MoveSelectionScreen_swap(wram->wBattleMon.pp, sizeof(wram->wBattleMon.pp[0]));
            // LD_HL(wPlayerDisableCount);
            // LD_A_hl;
            // SWAP_A;
            // AND_A(0xf);
            // LD_B_A;
            // LD_A_addr(wMenuCursorY);
            // CP_A_B;
            // IF_NZ goto not_swapping_disabled_move;
            if(((wram->wPlayerDisableCount >> 4) & 0xf) == wram->wMenuCursorY) {
                // LD_A_hl;
                // AND_A(0xf);
                // LD_B_A;
                // LD_A_addr(wSwappingMove);
                // SWAP_A;
                // ADD_A_B;
                // LD_hl_A;
                wram->wPlayerDisableCount = (wram->wPlayerDisableCount & 0xf) | (wram->wSwappingMove << 4);
                // goto swap_moves_in_party_struct;
            }
        // not_swapping_disabled_move:
            // LD_A_addr(wSwappingMove);
            // CP_A_B;
            // IF_NZ goto swap_moves_in_party_struct;
            else if(((wram->wPlayerDisableCount >> 4) & 0xf) == wram->wSwappingMove) {
                // LD_A_hl;
                // AND_A(0xf);
                // LD_B_A;
                // LD_A_addr(wMenuCursorY);
                // SWAP_A;
                // ADD_A_B;
                // LD_hl_A;
                wram->wPlayerDisableCount = (wram->wPlayerDisableCount & 0xf) | (wram->wMenuCursorY << 4);
            }

        // swap_moves_in_party_struct:
        //  Fixes the COOLTRAINER glitch
            // LD_A_addr(wPlayerSubStatus5);
            // BIT_A(SUBSTATUS_TRANSFORMED);
            // IF_NZ goto transformed;
            if(!bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TRANSFORMED)) {
                // LD_HL(wPartyMon1Moves);
                // LD_A_addr(wCurBattleMon);
                // CALL(aGetPartyLocation);
                // PUSH_HL;
                // CALL(aMoveSelectionScreen_swap_bytes);
                MoveSelectionScreen_swap(wram->wPartyMon[wram->wCurBattleMon].mon.moves, sizeof(wram->wPartyMon[wram->wCurBattleMon].mon.moves[0]));
                // POP_HL;
                // LD_BC(MON_PP - MON_MOVES);
                // ADD_HL_BC;
                // CALL(aMoveSelectionScreen_swap_bytes);
                MoveSelectionScreen_swap(wram->wPartyMon[wram->wCurBattleMon].mon.PP, sizeof(wram->wPartyMon[wram->wCurBattleMon].mon.PP[0]));
            }

        // transformed:
            // XOR_A_A;
            // LD_addr_A(wSwappingMove);
            wram->wSwappingMove = 0;
            // JP(mMoveSelectionScreen);
            goto MoveSelectionScreen;
        }
        // BIT_A(B_BUTTON_F);
    // A button
        // PUSH_AF;
        const uint8_t bPressed = bit_test(joypad, B_BUTTON_F);

        // XOR_A_A;
        // LD_addr_A(wSwappingMove);
        wram->wSwappingMove = 0;
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY--;
        // LD_B_A;
        // LD_A_addr(wMoveSelectionMenuType);
        // DEC_A;
        // IF_NZ goto not_enemy_moves_process_b;
        if(wram->wMoveSelectionMenuType == 0x1) {
            // POP_AF;
            // RET;
            return bPressed != 0;
        }

    // not_enemy_moves_process_b:
        // DEC_A;
        // LD_A_B;
        // LD_addr_A(wCurMoveNum);
        wram->wCurMoveNum = wram->wMenuCursorY;
        // IF_NZ goto use_move;
        if(wram->wMoveSelectionMenuType == 0x2) {
            // POP_AF;
            // RET;
            return bPressed != 0;
        }

    // use_move:
        // POP_AF;
        // RET_NZ ;
        if(bPressed)
            return true;

        // LD_HL(wBattleMonPP);
        // LD_A_addr(wMenuCursorY);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A(PP_MASK);
        // IF_Z goto no_pp_left;
        if((wram->wBattleMon.pp[wram->wMenuCursorY] & PP_MASK) == 0) {
        // no_pp_left:
            // LD_HL(mBattleText_TheresNoPPLeftForThisMove);
        // place_textbox_start_over:
            // CALL(aStdBattleTextbox);
            StdBattleTextbox_Conv2(BattleText_TheresNoPPLeftForThisMove);
            // CALL(aSafeLoadTempTilemapToTilemap);
            SafeLoadTempTilemapToTilemap_Conv();
            // JP(mMoveSelectionScreen);
            goto MoveSelectionScreen;
        }
        // LD_A_addr(wPlayerDisableCount);
        // SWAP_A;
        // AND_A(0xf);
        // DEC_A;
        // CP_A_C;
        // IF_Z goto move_disabled;
        if((((wram->wPlayerDisableCount >> 4) & 0xf) - 1) == wram->wMenuCursorY) {
        // move_disabled:
            // LD_HL(mBattleText_TheMoveIsDisabled);
            // goto place_textbox_start_over;
        // place_textbox_start_over:
            // CALL(aStdBattleTextbox);
            StdBattleTextbox_Conv2(BattleText_TheMoveIsDisabled);
            // CALL(aSafeLoadTempTilemapToTilemap);
            SafeLoadTempTilemapToTilemap_Conv();
            // JP(mMoveSelectionScreen);
            goto MoveSelectionScreen;
        }
        // LD_A_addr(wUnusedPlayerLockedMove);
        // AND_A_A;
        // IF_NZ goto skip2;
        if(wram->wUnusedPlayerLockedMove != NO_MOVE) {
            wram->wCurPlayerMove = wram->wUnusedPlayerLockedMove;
        }
        else {
            // LD_A_addr(wMenuCursorY);
            // LD_HL(wBattleMonMoves);
            // LD_C_A;
            // LD_B(0);
            // ADD_HL_BC;
            // LD_A_hl;
            wram->wCurPlayerMove = wram->wBattleMon.moves[wram->wMenuCursorY];
        }

    // skip2:
        // LD_addr_A(wCurPlayerMove);
        // XOR_A_A;
        // RET;
        return false;
    }

}

static void MoveInfoBox_PrintPP(uint8_t pp, uint8_t maxpp){
    // hlcoord(5, 11, wTilemap);
    // LD_A_addr(wLinkMode);  // What's the point of this check?
    // CP_A(LINK_MOBILE);
    // IF_C goto ok;
    // hlcoord(5, 11, wTilemap);
    tile_t* hl = coord(5, 11, wram->wTilemap);

// ok:
    // PUSH_HL;
    // LD_DE(wStringBuffer1);
    // LD_BC((1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, &pp, 1, 2);
    // POP_HL;
    // INC_HL;
    // INC_HL;
    hl += 2;
    // LD_hl(0xf3);
    // INC_HL;
    *(hl++) = 0xf3;
    // LD_DE(wNamedObjectIndex);
    // LD_BC((1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, &maxpp, 1, 2);
    // RET;
}

void MoveInfoBox(void){
    static const char Disabled[] = "Disabled!@";
    static const char Type[] = "TYPE/";
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;

    // hlcoord(0, 8, wTilemap);
    // LD_B(3);
    // LD_C(9);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 8, wram->wTilemap), 3, 9);
    // CALL(aMobileTextBorder);
    MobileTextBorder_Conv();

    // LD_A_addr(wPlayerDisableCount);
    // AND_A_A;
    // IF_Z goto not_disabled;

    if(wram->wPlayerDisableCount != 0) {
        // SWAP_A;
        // AND_A(0xf);
        uint8_t which = (wram->wPlayerDisableCount >> 4) & 0xf;
        // LD_B_A;
        // LD_A_addr(wMenuCursorY);
        // CP_A_B;
        // IF_NZ goto not_disabled;
        if(which == wram->wMenuCursorY) {
            // hlcoord(1, 10, wTilemap);
            // LD_DE(mMoveInfoBox_Disabled);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(Disabled), coord(1, 10, wram->wTilemap));
            // goto done;
            return;
        }
    }

// not_disabled:
    // LD_HL(wMenuCursorY);
    // DEC_hl;
    wram->wMenuCursorY--;
    // CALL(aSetPlayerTurn);
    SetPlayerTurn_Conv();
    // LD_HL(wBattleMonMoves);
    // LD_A_addr(wMenuCursorY);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wCurPlayerMove);
    wram->wCurPlayerMove = wram->wBattleMon.moves[wram->wMenuCursorY];

    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wCurBattleMon;
    // LD_A(WILDMON);
    // LD_addr_A(wMonType);
    // CALLFAR(aGetMaxPPOfMove);
    uint8_t maxpp = GetMaxPPOfMove_Conv(wram->wPartyMon + wram->wCurPartyMon, WILDMON, wram->wMenuCursorY);

    // LD_HL(wMenuCursorY);
    // LD_C_hl;
    // INC_hl;
    // LD_B(0);
    // LD_HL(wBattleMonPP);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(PP_MASK);
    // LD_addr_A(wStringBuffer1);
    // CALL(aMoveInfoBox_PrintPP);
    MoveInfoBox_PrintPP(wram->wBattleMon.pp[wram->wMenuCursorY], maxpp);
    wram->wMenuCursorY++;

    // hlcoord(1, 9, wTilemap);
    // LD_DE(mMoveInfoBox_Type);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Type), coord(1, 9, wram->wTilemap));

    // hlcoord(7, 11, wTilemap);
    // LD_hl(0xf3);
    *coord(7, 11, wram->wTilemap) = 0xf3;

    // CALLFAR(aUpdateMoveData);
    UpdateMoveData();
    // LD_A_addr(wPlayerMoveStruct + MOVE_ANIM);
    // LD_B_A;
    // hlcoord(2, 10, wTilemap);
    // PREDEF(pPrintMoveType);
    PrintMoveType_Conv(coord(2, 10, wram->wTilemap), wram->wPlayerMoveStruct.animation);

// done:
    // RET;
}

bool CheckPlayerHasUsableMoves(void){
    // LD_A(STRUGGLE);
    // LD_addr_A(wCurPlayerMove);
    wram->wCurPlayerMove = STRUGGLE;
    // LD_A_addr(wPlayerDisableCount);
    // AND_A_A;
    // LD_HL(wBattleMonPP);
    uint8_t* pp = wram->wBattleMon.pp;
    // IF_NZ goto disabled;
    if(wram->wPlayerDisableCount == 0) {
        // LD_A_hli;
        // OR_A_hl;
        // INC_HL;
        // OR_A_hl;
        // INC_HL;
        // OR_A_hl;
        // AND_A(PP_MASK);
        // RET_NZ ;
        if((pp[0] | pp[1] | pp[2] | pp[3]) & PP_MASK)
            return true;
        // goto force_struggle;
    }
    else {
    // disabled:
        // SWAP_A;
        // AND_A(0xf);
        // LD_B_A;
        uint8_t b = (wram->wPlayerDisableCount >> 4) & 0xf;
        // LD_D(NUM_MOVES + 1);
        uint8_t d = NUM_MOVES + 1;
        // XOR_A_A;
        uint8_t a = 0;

        while(--d != 0) {
        // loop:
            // DEC_D;
            // IF_Z goto done;
            // LD_C_hl;
            // INC_HL;
            uint8_t c = *(pp++);
            // DEC_B;
            // IF_Z goto loop;
            if(--b == 0)
                continue;
            // OR_A_C;
            a |= c;
            // goto loop;
        }


    // done:
    // Bug: this will result in a move with PP Up confusing the game.
#if BUGFIX_CHECK_PLAYER_USABLE_MOVES
        if((a & PP_MASK) != 0)
#else
        // AND_A_A;  // should be "and PP_MASK"
        // RET_NZ ;
        if(a != 0)
#endif
            return true;
    }

// force_struggle:
    // LD_HL(mBattleText_MonHasNoMovesLeft);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_MonHasNoMovesLeft);
    // LD_C(60);
    // CALL(aDelayFrames);
    DelayFrames_Conv(60);
    // XOR_A_A;
    // RET;
    return false;
}

void ParseEnemyAction(void){
    move_t curMove;
    // LD_A_addr(wEnemyIsSwitching);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wEnemyIsSwitching)
        return;
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;
    if(wram->wLinkMode != 0) {
        // CALL(aEmptyBattleTextbox);
        EmptyBattleTextbox();
        // CALL(aLoadTilemapToTempTilemap);
        LoadTilemapToTempTilemap_Conv();
        // LD_A_addr(wBattlePlayerAction);
        // AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
        // CALL_Z (aLinkBattleSendReceiveAction);
        if(wram->wBattlePlayerAction == BATTLEPLAYERACTION_USEMOVE)
            LinkBattleSendReceiveAction();
        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap_Conv();
        // LD_A_addr(wBattleAction);
        // CP_A(BATTLEACTION_STRUGGLE);
        // JP_Z (mParseEnemyAction_struggle);
        if(wram->wBattleAction == BATTLEACTION_STRUGGLE) {
            curMove = STRUGGLE;
            goto finish;
        }
        // CP_A(BATTLEACTION_SKIPTURN);
        // JP_Z (mParseEnemyAction_skip_turn);
        if(wram->wBattleAction == BATTLEACTION_SKIPTURN) {
            curMove = (move_t)-1;
            goto finish;
        }
        // CP_A(BATTLEACTION_SWITCH1);
        // JP_NC (mResetVarsForSubstatusRage);
        if(wram->wBattleAction >= BATTLEACTION_SWITCH1)
            return ResetVarsForSubstatusRage(); 
        // LD_addr_A(wCurEnemyMoveNum);
        wram->wCurEnemyMoveNum = wram->wBattleAction;
        // LD_C_A;
        uint8_t c = wram->wBattleAction;
        // LD_A_addr(wEnemySubStatus1);
        // BIT_A(SUBSTATUS_ROLLOUT);
        // JP_NZ (mParseEnemyAction_skip_load);
        if(bit_test(wram->wEnemySubStatus1, SUBSTATUS_ROLLOUT))
            goto skip_load;
        // LD_A_addr(wEnemySubStatus3);
        // AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_BIDE);
        // JP_NZ (mParseEnemyAction_skip_load);
        if((wram->wEnemySubStatus3 & ((1 << SUBSTATUS_CHARGED) | (1 << SUBSTATUS_RAMPAGE) | (1 << SUBSTATUS_BIDE))) != 0)
            goto skip_load;

        // LD_HL(wEnemySubStatus5);
        // BIT_hl(SUBSTATUS_ENCORED);
        // LD_A_addr(wLastEnemyMove);
        // JP_NZ (mParseEnemyAction_finish);
        if(bit_test(wram->wEnemySubStatus5, SUBSTATUS_ENCORED)) {
            curMove = wram->wLastEnemyMove;
            goto finish;
        }
        // LD_HL(wEnemyMonMoves);
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        curMove = wram->wEnemyMon.moves[c];
        // JP(mParseEnemyAction_finish);
        goto finish;
    }
    else {
    // not_linked:
        // LD_HL(wEnemySubStatus5);
        // BIT_hl(SUBSTATUS_ENCORED);
        // IF_Z goto skip_encore;
        if(bit_test(wram->wEnemySubStatus5, SUBSTATUS_ENCORED)) {
            // LD_A_addr(wLastEnemyMove);
            curMove = wram->wLastEnemyMove;
            // JP(mParseEnemyAction_finish);
            goto finish;
        }
    // skip_encore:
        // CALL(aCheckEnemyLockedIn);
        // JP_NZ (mResetVarsForSubstatusRage);
        if(CheckEnemyLockedIn_Conv())
            return ResetVarsForSubstatusRage();
        // goto continue_;
    // continue_:
        // LD_HL(wEnemyMonMoves);
        const move_t* moves = wram->wEnemyMon.moves;
        for(int i = 0; i < NUM_MOVES; ++i) {
            printf("MOVE %d = %02X\n", i, moves[i]);
        }
        // LD_DE(wEnemyMonPP);
        const uint8_t* pp = wram->wEnemyMon.pp;
        // LD_B(NUM_MOVES);
        uint8_t b = NUM_MOVES;

        do {
        // loop:
            // LD_A_hl;
            move_t move = *moves;
            // AND_A_A;
            // JP_Z (mParseEnemyAction_struggle);
            if(move == NO_MOVE) {
                curMove = STRUGGLE;
                goto finish;
            }
            // LD_A_addr(wEnemyDisabledMove);
            // CP_A_hl;
            // IF_Z goto disabled;
            // LD_A_de;
            // AND_A(PP_MASK);
            // IF_NZ goto enough_pp;
            if(move != wram->wEnemyDisabledMove && (*pp & PP_MASK) != 0) {
            // enough_pp:
                // LD_A_addr(wBattleMode);
                // DEC_A;
                // IF_NZ goto skip_load;
                if(wram->wBattleMode != WILD_BATTLE)
                    goto skip_load;
            //  wild
                move_t b;
                uint8_t c;
                do {
                    const move_t* moves2 = wram->wEnemyMon.moves;
                    do {
                    // loop2:
                        // LD_HL(wEnemyMonMoves);
                        // CALL(aBattleRandom);
                        // maskbits(NUM_MOVES, 0);
                        // LD_C_A;
                        c = BattleRandom_Conv() & 3;
                        // LD_B(0);
                        // ADD_HL_BC;
                        // LD_A_addr(wEnemyDisableCount);
                        // SWAP_A;
                        // AND_A(0xf);
                        // DEC_A;
                        // CP_A_C;
                        // IF_Z goto loop2;
                        // LD_A_hl;
                        // AND_A_A;
                        // IF_Z goto loop2;
                    } while(((wram->wEnemyDisableCount >> 4) & 0xf) - 1 == c || moves2[c] == NO_MOVE);
                    // LD_HL(wEnemyMonPP);
                    // ADD_HL_BC;
                    // LD_B_A;
                    b = moves2[c];
                    // LD_A_hl;
                    // AND_A(PP_MASK);
                    // IF_Z goto loop2;
                } while((wram->wEnemyMon.pp[c] & PP_MASK) == 0);
                // LD_A_C;
                // LD_addr_A(wCurEnemyMoveNum);
                wram->wCurEnemyMoveNum = c;
                // LD_A_B;
                curMove = b;
                goto finish;
            }

        // disabled:
            // INC_HL;
            moves++;
            // INC_DE;
            pp++;
            // DEC_B;
            // IF_NZ goto loop;
        } while(--b != NUM_MOVES);
        // goto struggle;
        curMove = STRUGGLE;
        goto finish;
    }


// skip_turn:
    // LD_A(0xff);
    // curMove = (move_t)-1;
    // goto finish;


finish:
    // LD_addr_A(wCurEnemyMove);
    wram->wCurEnemyMove = curMove;
    printf("Chosen move %02X (moves[%d])\n", curMove, wram->wCurEnemyMoveNum);

skip_load:
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // CALLFAR(aUpdateMoveData);
    UpdateMoveData();
    // CALL(aCheckEnemyLockedIn);
    // IF_NZ goto raging;
    if(!CheckEnemyLockedIn_Conv()) {
        // XOR_A_A;
        // LD_addr_A(wEnemyCharging);
        wram->wEnemyCharging = FALSE;
    }

// raging:
    // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    // CP_A(EFFECT_FURY_CUTTER);
    // IF_Z goto fury_cutter;
    if(wram->wEnemyMoveStruct.effect != EFFECT_FURY_CUTTER) {
        // XOR_A_A;
        // LD_addr_A(wEnemyFuryCutterCount);
        wram->wEnemyFuryCutterCount = 0x0;
    }

// fury_cutter:
    // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    // CP_A(EFFECT_RAGE);
    // IF_Z goto no_rage;
    if(wram->wEnemyMoveStruct.effect != EFFECT_RAGE) {
        // LD_HL(wEnemySubStatus4);
        // RES_hl(SUBSTATUS_RAGE);
        bit_reset(wram->wEnemySubStatus4, SUBSTATUS_RAGE);
        // XOR_A_A;
        // LD_addr_A(wEnemyRageCounter);
        wram->wEnemyRageCounter = 0x0;
    }

// no_rage:
    // LD_A_addr(wEnemyMoveStruct + MOVE_EFFECT);
    // CP_A(EFFECT_PROTECT);
    // RET_Z ;
    // CP_A(EFFECT_ENDURE);
    // RET_Z ;
    if(wram->wEnemyMoveStruct.effect != EFFECT_PROTECT && wram->wEnemyMoveStruct.effect != EFFECT_ENDURE) {
        // XOR_A_A;
        // LD_addr_A(wEnemyProtectCount);
        wram->wEnemyProtectCount = 0x0;
        // RET;
    }
    return;

// struggle:
    // LD_A(STRUGGLE);
    // goto finish;
}

void ResetVarsForSubstatusRage(void){
    // XOR_A_A;
    // LD_addr_A(wEnemyFuryCutterCount);
    wram->wEnemyFuryCutterCount = 0;
    // LD_addr_A(wEnemyProtectCount);
    wram->wEnemyProtectCount = 0;
    // LD_addr_A(wEnemyRageCounter);
    wram->wEnemyRageCounter = 0;
    // LD_HL(wEnemySubStatus4);
    // RES_hl(SUBSTATUS_RAGE);
    bit_reset(wram->wEnemySubStatus4, SUBSTATUS_RAGE);
    // RET;

}

void CheckEnemyLockedIn(void){
    LD_A_addr(wEnemySubStatus4);
    AND_A(1 << SUBSTATUS_RECHARGE);
    RET_NZ ;

    LD_HL(wEnemySubStatus3);
    LD_A_hl;
    AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_BIDE);
    RET_NZ ;

    LD_HL(wEnemySubStatus1);
    BIT_hl(SUBSTATUS_ROLLOUT);
    RET;

}

// Returns true (nz) if locked in.
bool CheckEnemyLockedIn_Conv(void){
    // LD_A_addr(wEnemySubStatus4);
    // AND_A(1 << SUBSTATUS_RECHARGE);
    // RET_NZ ;
    if(wram->wEnemySubStatus4 & (1 << SUBSTATUS_RECHARGE))
        return true;

    // LD_HL(wEnemySubStatus3);
    // LD_A_hl;
    // AND_A(1 << SUBSTATUS_CHARGED | 1 << SUBSTATUS_RAMPAGE | 1 << SUBSTATUS_BIDE);
    // RET_NZ ;
    if(wram->wEnemySubStatus3 & ((1 << SUBSTATUS_CHARGED) | (1 << SUBSTATUS_RAMPAGE) | (1 << SUBSTATUS_BIDE)))
        return true;

    // LD_HL(wEnemySubStatus1);
    // BIT_hl(SUBSTATUS_ROLLOUT);
    // RET;
    return bit_test(wram->wEnemySubStatus1, SUBSTATUS_ROLLOUT) != 0;
}

void LinkBattleSendReceiveAction(void){
    // FARCALL(av_LinkBattleSendReceiveAction);
    v_LinkBattleSendReceiveAction();
    // RET;
}

//  Initialize enemy monster parameters
//  To do this we pull the species from wTempEnemyMonSpecies
void LoadEnemyMon(void){
//  Notes:
//    BattleRandom is used to ensure sync between Game Boys
    PEEK("");
//  Clear the whole enemy mon struct (wEnemyMon)
    // XOR_A_A;
    // LD_HL(wEnemyMonSpecies);
    // LD_BC(wEnemyMonEnd - wEnemyMon);
    // CALL(aByteFill);
    ByteFill_Conv2(&wram->wEnemyMon, sizeof(wram->wEnemyMon), 0);

//  We don't need to be here if we're in a link battle
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // JP_NZ (mInitEnemyMon);
    if(wram->wLinkMode != 0) {
        return InitEnemyMon();
        // RET;
    }

//  and also not in a BattleTower-Battle
    // LD_A_addr(wInBattleTowerBattle);
    // BIT_A(0);
    // JP_NZ (mInitEnemyMon);
    if(bit_test(wram->wInBattleTowerBattle, 0)) {
        return InitEnemyMon();
        // RET;
    }

//  Make sure everything knows what species we're working with
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wEnemyMonSpecies);
    wram->wEnemyMon.species = wram->wTempEnemyMonSpecies;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wTempEnemyMonSpecies;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempEnemyMonSpecies;

//  Grab the BaseData for this species
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wTempEnemyMonSpecies);

//  Let's get the item:

//  Is the item predetermined?
    item_t a;
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_Z goto WildItem;
    if(wram->wBattleMode == WILD_BATTLE) {
    // WildItem:
    //  In a wild battle, we pull from the item slots in BaseData

    //  Force Item1
    //  Used for Ho-Oh, Lugia and Snorlax encounters
        // LD_A_addr(wBattleType);
        // CP_A(BATTLETYPE_FORCEITEM);
        // LD_A_addr(wBaseItem1);
        // IF_Z goto UpdateItem;
        if(wram->wBattleType == BATTLETYPE_FORCEITEM) {
            a = wram->wBaseItem1;
        }

    //  Failing that, it's all up to chance
    //   Effective chances:
    //     75% None
    //     23% Item1
    //      2% Item2

    //  25% chance of getting an item
        // CALL(aBattleRandom);
        // CP_A(75 percent + 1);
        // LD_A(NO_ITEM);
        // IF_C goto UpdateItem;
        else if(BattleRandom_Conv() < (75 percent + 1)) {
            a = NO_ITEM;
        }

    //  From there, an 8% chance for Item2
        // CALL(aBattleRandom);
        // CP_A(8 percent);  // 8% of 25% = 2% Item2
        // LD_A_addr(wBaseItem1);
        // IF_NC goto UpdateItem;
        // LD_A_addr(wBaseItem2);
        else if(BattleRandom_Conv() < (8 percent)) {   // 8% of 25% = 2% Item2
            a = wram->wBaseItem2;
        }
        else {
            a = wram->wBaseItem1;
        }
    }
    else {
    //  If we're in a trainer battle, the item is in the party struct
        // LD_A_addr(wCurPartyMon);
        // LD_HL(wOTPartyMon1Item);
        // CALL(aGetPartyLocation);  // bc = PartyMon[wCurPartyMon] - wPartyMons
        // LD_A_hl;
        a = wram->wOTPartyMon[wram->wCurPartyMon].mon.item;
        // goto UpdateItem;
    }

// UpdateItem:
    // LD_addr_A(wEnemyMonItem);
    wram->wEnemyMon.item = a;

//  Initialize DVs

//  If we're in a trainer battle, DVs are predetermined
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // IF_Z goto InitDVs;
    if(wram->wBattleMode != 0) {
        // LD_A_addr(wEnemySubStatus5);
        // BIT_A(SUBSTATUS_TRANSFORMED);
        // IF_Z goto InitDVs;

        if(bit_test(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED)) {
        //  Unknown
            // LD_HL(wEnemyBackupDVs);
            // LD_DE(wEnemyMonDVs);
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            // LD_A_hl;
            // LD_de_A;
            wram->wEnemyMon.dvs = wram->wEnemyBackupDVs;
            // JP(mLoadEnemyMon_Happiness);
            goto Happiness;
        }
    }

InitDVs:
//  Trainer DVs

//  All trainers have preset DVs, determined by class
//  See GetTrainerDVs for more on that
    // FARCALL(aGetTrainerDVs);
    uint16_t bc = GetTrainerDVs_Conv(wram->wOtherTrainerClass);
//  These are the DVs we'll use if we're actually in a trainer battle
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_NZ goto UpdateDVs;
    if(wram->wBattleMode == WILD_BATTLE) {
    //  Wild DVs
    //  Here's where the fun starts

    //  Roaming monsters (Entei, Raikou) work differently
    //  They have their own structs, which are shorter than normal
        // LD_A_addr(wBattleType);
        // CP_A(BATTLETYPE_ROAMING);
        // IF_NZ goto NotRoaming;
        if(wram->wBattleType == BATTLETYPE_ROAMING) {

        //  Grab HP
            // CALL(aGetRoamMonHP);
            // LD_A_hl;
        //  Check if the HP has been initialized
            // AND_A_A;
        //  We'll do something with the result in a minute
            // PUSH_AF;
            uint8_t hp = *GetRoamMonHP_Conv(wram->wTempEnemyMonSpecies);

        //  Grab DVs
            // CALL(aGetRoamMonDVs);
            // INC_HL;
            // LD_A_hld;
            // LD_C_A;
            // LD_B_hl;
            bc = *GetRoamMonDVs_Conv(wram->wTempEnemyMonSpecies);

        //  Get back the result of our check
            // POP_AF;
        //  If the RoamMon struct has already been initialized, we're done
            // IF_NZ goto UpdateDVs;
            if(hp == 0) {

            //  If it hasn't, we need to initialize the DVs
            //  (HP is initialized at the end of the battle)
                // CALL(aGetRoamMonDVs);
                uint16_t* dvs = GetRoamMonDVs_Conv(wram->wTempEnemyMonSpecies);
                // INC_HL;
                // CALL(aBattleRandom);
                uint8_t lo = BattleRandom_Conv();
                uint8_t hi = BattleRandom_Conv();
                // LD_hld_A;
                // LD_C_A;
                // CALL(aBattleRandom);
                // LD_hl_A;
                // LD_B_A;
                *dvs = lo | (hi << 8);
                bc = *dvs;
            //  We're done with DVs
                // goto UpdateDVs;
            }
        }
        else {
        // NotRoaming:
        //  Register a contains wBattleType

        //  Forced shiny battle type
        //  Used by Red Gyarados at Lake of Rage
            // CP_A(BATTLETYPE_SHINY);
            // IF_NZ goto GenerateDVs;
            if(wram->wBattleType == BATTLETYPE_SHINY) {

                // LD_B(ATKDEFDV_SHINY);  // $ea
                // LD_C(SPDSPCDV_SHINY);  // $aa
                // goto UpdateDVs;
                bc = (ATKDEFDV_SHINY << 8) | SPDSPCDV_SHINY;
            }
            else {
            GenerateDVs:
            //  Generate new random DVs
                // CALL(aBattleRandom);
                uint8_t lo = BattleRandom_Conv();
                // LD_B_A;
                // CALL(aBattleRandom);
                uint8_t hi = BattleRandom_Conv();
                // LD_C_A;
                bc = (hi << 8) | lo;
            }
        }
    }

// UpdateDVs:
//  Input DVs in register bc
    // LD_HL(wEnemyMonDVs);
    // LD_A_B;
    // LD_hli_A;
    // LD_hl_C;
    wram->wEnemyMon.dvs = bc;

//  We've still got more to do if we're dealing with a wild monster
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_NZ goto Happiness;
    if(wram->wBattleMode == WILD_BATTLE) {
    //  Species-specfic:

    //  Unown
        // LD_A_addr(wTempEnemyMonSpecies);
        // CP_A(UNOWN);
        // IF_NZ goto Magikarp;
        if(wram->wTempEnemyMonSpecies == UNOWN) {
        //  Get letter based on DVs
            // LD_HL(wEnemyMonDVs);
            // PREDEF(pGetUnownLetter);
            unown_letter_t letter = GetUnownLetter_Conv(wram->wEnemyMon.dvs);
        //  Can't use any letters that haven't been unlocked
        //  If combined with forced shiny battletype, causes an infinite loop
            // CALL(aCheckUnownLetter);
            // IF_C goto GenerateDVs;  // try again
            if(CheckUnownLetter_Conv(letter))
                goto GenerateDVs; // No cleaner way to this without duplicating code.
        }

    // Magikarp:
    //  These filters are untranslated.
    //  They expect at wMagikarpLength a 2-byte value in mm,
    //  but the value is in feet and inches (one byte each).

    //  The first filter is supposed to make very large Magikarp even rarer,
    //  by targeting those 1600 mm (= 5'3") or larger.
    //  After the conversion to feet, it is unable to target any,
    //  since the largest possible Magikarp is 5'3", and $0503 = 1283 mm.
        // LD_A_addr(wTempEnemyMonSpecies);
        // CP_A(MAGIKARP);
        // IF_NZ goto Happiness;
        if(wram->wTempEnemyMonSpecies == MAGIKARP) {

        //  Get Magikarp's length
            // LD_DE(wEnemyMonDVs);
            // LD_BC(wPlayerID);
            // CALLFAR(aCalcMagikarpLength);
            CalcMagikarpLength_Conv(wram->wEnemyMon.dvs, wram->wPlayerID);

        //  No reason to keep going if length > 1536 mm (i.e. if HIGH(length) > 6 feet)
            // LD_A_addr(wMagikarpLength);
            // CP_A(HIGH(1536));  // should be "cp 5", since 1536 mm = 5'0", but HIGH(1536) = 6
            // IF_NZ goto CheckMagikarpArea;

        //  5% chance of skipping both size checks
            // CALL(aRandom);
            // CP_A(5 percent);
            // IF_C goto CheckMagikarpArea;
            if(LOW(wram->wMagikarpLength) == HIGH(1536) && Random_Conv() >= 5 percent) {
            //  Try again if length >= 1616 mm (i.e. if LOW(length) >= 4 inches)
                // LD_A_addr(wMagikarpLength + 1);
                // CP_A(LOW(1616));  // should be "cp 4", since 1616 mm = 5'4", but LOW(1616) = 80
                // IF_NC goto GenerateDVs;

            //  20% chance of skipping this check
                // CALL(aRandom);
                // CP_A(20 percent - 1);
                // IF_C goto CheckMagikarpArea;
            //  Try again if length >= 1600 mm (i.e. if LOW(length) >= 3 inches)
                // LD_A_addr(wMagikarpLength + 1);
                // CP_A(LOW(1600));  // should be "cp 3", since 1600 mm = 5'3", but LOW(1600) = 64
                // IF_NC goto GenerateDVs;
                if(HIGH(wram->wMagikarpLength) >= LOW(1616) || ((Random_Conv() >= 20 percent - 1) && HIGH(wram->wMagikarpLength) >= LOW(1600)))
                    goto GenerateDVs;
            }

        // CheckMagikarpArea:
        //  The "jr z" checks are supposed to be "jr nz".

        //  Instead, all maps in GROUP_LAKE_OF_RAGE (Mahogany area)
        //  and Routes 20 and 44 are treated as Lake of Rage.

        //  This also means Lake of Rage Magikarp can be smaller than ones
        //  caught elsewhere rather than the other way around.

        //  Intended behavior enforces a minimum size at Lake of Rage.
        //  The real behavior prevents a minimum size in the Lake of Rage area.

        //  Moreover, due to the check not being translated to feet+inches, all Magikarp
        //  smaller than 4'0" may be caught by the filter, a lot more than intended.
            // LD_A_addr(wMapGroup);
            // CP_A(GROUP_LAKE_OF_RAGE);
            // IF_Z goto Happiness;
            // LD_A_addr(wMapNumber);
            // CP_A(MAP_LAKE_OF_RAGE);
            // IF_Z goto Happiness;
        //  40% chance of not flooring
            // CALL(aRandom);
            // CP_A(39 percent + 1);
            // IF_C goto Happiness;
            if(wram->wMapGroup != GROUP_LAKE_OF_RAGE 
            && wram->wMapGroup != MAP_LAKE_OF_RAGE
            && Random_Conv() >= 39 percent + 1) {
            //  Try again if length < 1024 mm (i.e. if HIGH(length) < 3 feet)
                // LD_A_addr(wMagikarpLength);
                // CP_A(HIGH(1024));  // should be "cp 3", since 1024 mm = 3'4", but HIGH(1024) = 4
                // IF_C goto GenerateDVs;  // try again
                if(wram->wMagikarpLength == HIGH(1024))
                    goto GenerateDVs; // No cleaner way to this without duplicating code.
            }
        }

    //  Finally done with DVs
    }

Happiness:
//  Set happiness
    // LD_A(BASE_HAPPINESS);
    // LD_addr_A(wEnemyMonHappiness);
    wram->wEnemyMon.happiness = BASE_HAPPINESS;
//  Set level
    // LD_A_addr(wCurPartyLevel);
    // LD_addr_A(wEnemyMonLevel);
    wram->wEnemyMon.level = wram->wCurPartyLevel;
//  Fill stats
    // LD_DE(wEnemyMonMaxHP);
    uint16_t* monStats = (uint16_t*)((uint8_t*)&wram->wEnemyMon + offsetof(struct BattleMon, maxHP));
    // LD_B(FALSE);
    // LD_HL(wEnemyMonDVs - (MON_DVS - MON_STAT_EXP + 1));
    // PREDEF(pCalcMonStats);
    CalcMonStats_Conv(monStats, NULL, wram->wEnemyMon.dvs, FALSE);

//  If we're in a trainer battle,
//  get the rest of the parameters from the party struct
    // LD_A_addr(wBattleMode);
    // CP_A(TRAINER_BATTLE);
    // IF_Z goto OpponentParty;
    if(wram->wBattleMode == TRAINER_BATTLE) {
    // OpponentParty:
    //  Get HP from the party struct
        // LD_HL((wOTPartyMon1HP + 1));
        // LD_A_addr(wCurPartyMon);
        // CALL(aGetPartyLocation);
        // LD_A_hld;
        // LD_addr_A(wEnemyMonHP + 1);
        // LD_A_hld;
        // LD_addr_A(wEnemyMonHP);
        wram->wEnemyMon.hp = wram->wOTPartyMon[wram->wCurPartyMon].HP;
        wram->wEnemyMon.maxHP = wram->wOTPartyMon[wram->wCurPartyMon].maxHP;

    //  Make sure everything knows which monster the opponent is using
        // LD_A_addr(wCurPartyMon);
        // LD_addr_A(wCurOTMon);
        wram->wCurOTMon = wram->wCurPartyMon;

    //  Get status from the party struct
        // DEC_HL;
        // LD_A_hl;  // OTPartyMonStatus
        // LD_addr_A(wEnemyMonStatus);
        wram->wEnemyMon.status[0] = wram->wOTPartyMon[wram->wCurPartyMon].status;
    }
    else {
    //  If we're in a wild battle, check wild-specific stuff
        // AND_A_A;
        // IF_Z goto TreeMon;
        // LD_A_addr(wEnemySubStatus5);
        // BIT_A(SUBSTATUS_TRANSFORMED);
        // JP_NZ (mLoadEnemyMon_Moves);
        if(wram->wBattleMode == 0 || !bit_test(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED)) {
        // TreeMon:
        //  If we're headbutting trees, some monsters enter battle asleep
            // CALL(aCheckSleepingTreeMon);
            // LD_A(TREEMON_SLEEP_TURNS);
            // IF_C goto UpdateStatus;
        //  Otherwise, no status
            // XOR_A_A;

        // UpdateStatus:
            // LD_HL(wEnemyMonStatus);
            // LD_hli_A;
            wram->wEnemyMon.status[0] = (CheckSleepingTreeMon_Conv(wram->wTempWildMonSpecies))? TREEMON_SLEEP_TURNS: 0;

        //  Unused byte
            // XOR_A_A;
            // LD_hli_A;
            wram->wEnemyMon.status[1] = 0;

        //  Full HP..
            // LD_A_addr(wEnemyMonMaxHP);
            // LD_hli_A;
            // LD_A_addr(wEnemyMonMaxHP + 1);
            // LD_hl_A;
            wram->wEnemyMon.hp = wram->wEnemyMon.maxHP;

        //  ..unless it's a RoamMon
            // LD_A_addr(wBattleType);
            // CP_A(BATTLETYPE_ROAMING);
            // IF_NZ goto Moves;
            if(wram->wBattleType == BATTLETYPE_ROAMING) {
            //  Grab HP
                // CALL(aGetRoamMonHP);
                uint8_t* roamHP = GetRoamMonHP_Conv(wram->wTempEnemyMonSpecies);
                // LD_A_hl;
            //  Check if it's been initialized again
                // AND_A_A;
                // IF_Z goto InitRoamHP;
                if(*roamHP == 0) {
                // InitRoamHP:
                //  HP only uses the lo byte in the RoamMon struct since
                //  Raikou and Entei will have < 256 hp at level 40
                    // LD_A_addr(wEnemyMonHP + 1);
                    // LD_hl_A;
                    *roamHP = LOW(wram->wEnemyMon.hp);
                    // goto Moves;
                }
                else {
                //  Update from the struct if it has
                    // LD_A_hl;
                    // LD_addr_A(wEnemyMonHP + 1);
                    wram->wEnemyMon.hp = (*roamHP << 8);
                    // goto Moves;
                }
            }
        }
    }

// Moves:
    // LD_HL(wBaseType1);
    // LD_DE(wEnemyMonType1);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    wram->wEnemyMon.type1 = wram->wBaseType1;
    // LD_A_hl;
    // LD_de_A;
    wram->wEnemyMon.type2 = wram->wBaseType2;

//  Get moves
    // LD_DE(wEnemyMonMoves);
    move_t* moves = wram->wEnemyMon.moves;
//  Are we in a trainer battle?
    // LD_A_addr(wBattleMode);
    // CP_A(TRAINER_BATTLE);
    // IF_NZ goto WildMoves;
    if(wram->wBattleMode == TRAINER_BATTLE) {
    //  Then copy moves from the party struct
        // LD_HL(wOTPartyMon1Moves);
        // LD_A_addr(wCurPartyMon);
        // CALL(aGetPartyLocation);
        // LD_BC(NUM_MOVES);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(moves, &wram->wOTPartyMon[wram->wCurPartyMon].mon.moves, NUM_MOVES * sizeof(move_t));
        for(int i = 0; i < NUM_MOVES; ++i) {
            printf("Move %d = %02X\n", i, moves[i]);
        }
        // goto PP;
    }
    else {
    // WildMoves:
    //  Clear wEnemyMonMoves
        // XOR_A_A;
        // LD_H_D;
        // LD_L_E;
        // LD_hli_A;
        // LD_hli_A;
        // LD_hli_A;
        // LD_hl_A;
        ByteFill_Conv2(moves, 0, 4 * sizeof(move_t));
        // LD_addr_A(wSkipMovesBeforeLevelUp);
        wram->wSkipMovesBeforeLevelUp = FALSE;
        printf("wSkipMovesBeforeLevelUp = %d\n", wram->wSkipMovesBeforeLevelUp);
    //  Fill moves based on level
        // PREDEF(pFillMoves);
        FillMoves_Conv(moves, wram->wEnemyMon.pp, wram->wEnemyMon.species, wram->wEnemyMon.level);
        for(int i = 0; i < NUM_MOVES; ++i) {
            printf("Move %d = %02X\n", i, moves[i]);
        }
    }

// PP:
//  Trainer battle?
    // LD_A_addr(wBattleMode);
    // CP_A(TRAINER_BATTLE);
    // IF_Z goto TrainerPP;
    if(wram->wBattleMode == TRAINER_BATTLE) {
    // TrainerPP:
    //  Copy PP from the party struct
        // LD_HL(wOTPartyMon1PP);
        // LD_A_addr(wCurPartyMon);
        // CALL(aGetPartyLocation);
        // LD_DE(wEnemyMonPP);
        // LD_BC(NUM_MOVES);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(wram->wEnemyMon.pp, wram->wOTPartyMon[wram->wCurPartyMon].mon.PP, NUM_MOVES);
    }
    else {
    //  Fill wild PP
        // LD_HL(wEnemyMonMoves);
        // LD_DE(wEnemyMonPP);
        // PREDEF(pFillPP);
        FillPP_Conv(wram->wEnemyMon.pp, wram->wEnemyMon.moves);
        // goto Finish;
    }

// Finish:
//  Copy the first five base stats (the enemy mon's base Sp. Atk
//  is also used to calculate Sp. Def stat experience)
    // LD_HL(wBaseStats);
    // LD_DE(wEnemyMonBaseStats);
    // LD_B(NUM_STATS - 1);
    for(uint8_t i = 0; i < NUM_STATS - 1; ++i) {
    // loop:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        wram->wEnemyMonBaseStats[i] = wram->wBaseStats[i];
        // DEC_B;
        // IF_NZ goto loop;
    }

    // LD_A_addr(wBaseCatchRate);
    // LD_de_A;
    // INC_DE;
    wram->wEnemyMonCatchRate = wram->wBaseCatchRate;

    // LD_A_addr(wBaseExp);
    // LD_de_A;
    wram->wEnemyMonBaseExp = wram->wBaseExp;

    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wNamedObjectIndex);

    // CALL(aGetPokemonName);
    GetPokemonName_Conv2(wram->wTempEnemyMonSpecies);

//  Did we catch it?
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // RET_Z ;
    if(wram->wBattleMode == 0)
        // RET;
        return;

//  Update enemy nickname
    // LD_HL(wStringBuffer1);
    // LD_DE(wEnemyMonNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wEnemyMonNickname, wram->wStringBuffer1, MON_NAME_LENGTH);

//  Saw this mon
    // LD_A_addr(wTempEnemyMonSpecies);
    // DEC_A;
    // LD_C_A;
    // LD_B(SET_FLAG);
    // LD_HL(wPokedexSeen);
    // PREDEF(pSmallFarFlagAction);
    SmallFarFlagAction_Conv(wram->wPokedexSeen, wram->wTempEnemyMonSpecies - 1, SET_FLAG);

    // LD_HL(wEnemyMonStats);
    // LD_DE(wEnemyStats);
    // LD_BC(NUM_EXP_STATS * 2);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wEnemyAttack, wram->wEnemyMon.attack, NUM_EXP_STATS * sizeof(uint16_t));

    // RET;
}

//  Return carry if species is in the list
//  for the current time of day
void CheckSleepingTreeMon(void){
//  Don't do anything if this isn't a tree encounter
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TREE);
    IF_NZ goto NotSleeping;

//  Get list for the time of day
    LD_HL(mAsleepTreeMonsMorn);
    LD_A_addr(wTimeOfDay);
    CP_A(DAY_F);
    IF_C goto Check;
    LD_HL(mAsleepTreeMonsDay);
    IF_Z goto Check;
    LD_HL(mAsleepTreeMonsNite);


Check:
    LD_A_addr(wTempEnemyMonSpecies);
    LD_DE(1);  // length of species id
    CALL(aIsInArray);
//  If it's a match, the opponent is asleep
    RET_C ;


NotSleeping:
    AND_A_A;
    RET;

// INCLUDE "data/wild/treemons_asleep.asm"

    return CheckUnownLetter();
}

//  Return carry if species is in the list
//  for the current time of day
bool CheckSleepingTreeMon_Conv(species_t species){
//  Don't do anything if this isn't a tree encounter
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TREE);
    // IF_NZ goto NotSleeping;
    if(wram->wBattleType != BATTLETYPE_TREE)
        return false;

//  Get list for the time of day
    // LD_HL(mAsleepTreeMonsMorn);
    // LD_A_addr(wTimeOfDay);
    // CP_A(DAY_F);
    // IF_C goto Check;
    const species_t* hl;
    if(wram->wTimeOfDay < DAY_F) {
        hl = AsleepTreeMonsMorn;
    }
    // LD_HL(mAsleepTreeMonsDay);
    // IF_Z goto Check;
    else if(wram->wTimeOfDay == DAY_F) {
        hl = AsleepTreeMonsDay;
    }
    // LD_HL(mAsleepTreeMonsNite);
    else {
        hl = AsleepTreeMonsNite;
    }

// Check:
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_DE(1);  // length of species id
    // CALL(aIsInArray);
//  If it's a match, the opponent is asleep
    // RET_C ;
    for(size_t i = 0; hl[i] != (species_t)-1; ++i) {
        if(hl[i] == species) {
            return true;
        }
    }


// NotSleeping:
    // AND_A_A;
    // RET;
    return false;

// INCLUDE "data/wild/treemons_asleep.asm"
}

void CheckUnownLetter(void){
//  Return carry if the Unown letter hasn't been unlocked yet

    LD_A_addr(wUnlockedUnowns);
    LD_C_A;
    LD_DE(0);


loop:

//  Don't check this set unless it's been unlocked
    SRL_C;
    IF_NC goto next;

//  Is our letter in the set?
    LD_HL(mUnlockedUnownLetterSets);
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    PUSH_DE;
    LD_A_addr(wUnownLetter);
    LD_DE(1);
    PUSH_BC;
    CALL(aIsInArray);
    POP_BC;
    POP_DE;

    IF_C goto match;


next:
//  Make sure we haven't gone past the end of the table
    INC_E;
    INC_E;
    LD_A_E;
    CP_A(aUnlockedUnownLetterSets_End - aUnlockedUnownLetterSets);
    IF_C goto loop;

//  Hasn't been unlocked, or the letter is invalid
    SCF;
    RET;


match:
//  Valid letter
    AND_A_A;
    RET;

// INCLUDE "data/wild/unlocked_unowns.asm"

    return SwapBattlerLevels();
}

//  Return carry if the Unown letter hasn't been unlocked yet
bool CheckUnownLetter_Conv(unown_letter_t a){

    // LD_A_addr(wUnlockedUnowns);
    // LD_C_A;
    // LD_DE(0);
    uint8_t c = wram->wUnlockedUnowns;

    for(uint8_t i = 0; i < UnlockedUnownLetterSetsCount; ++i) {
    // loop:
    //  Don't check this set unless it's been unlocked
        // SRL_C;
        // IF_NC goto next;
        if(c & (1 << i)) {

        //  Is our letter in the set?
            // LD_HL(mUnlockedUnownLetterSets);
            // ADD_HL_DE;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            const unown_letter_t* hl = UnlockedUnownLetterSets[i];

            // PUSH_DE;
            // LD_A_addr(wUnownLetter);
            // LD_DE(1);
            // PUSH_BC;
            // CALL(aIsInArray);
            // POP_BC;
            // POP_DE;
            for(uint8_t j = 0; hl[j] != (unown_letter_t)-1; ++j) {
                if(hl[j] == a)
                    return true;
            }

            // IF_C goto match;
        }

    // next:
    //  Make sure we haven't gone past the end of the table
        // INC_E;
        // INC_E;
        // LD_A_E;
        // CP_A(aUnlockedUnownLetterSets_End - aUnlockedUnownLetterSets);
        // IF_C goto loop;
    }

//  Hasn't been unlocked, or the letter is invalid
    // SCF;
    // RET;
    return false;

// match:
//  Valid letter
    // AND_A_A;
    // RET;

// INCLUDE "data/wild/unlocked_unowns.asm"
}

void SwapBattlerLevels(void){
//  //  unreferenced
    PUSH_BC;
    LD_A_addr(wBattleMonLevel);
    LD_B_A;
    LD_A_addr(wEnemyMonLevel);
    LD_addr_A(wBattleMonLevel);
    LD_A_B;
    LD_addr_A(wEnemyMonLevel);
    POP_BC;
    RET;

}

static void BattleWinSlideInEnemyTrainerFrontpic_CopyColumn(tile_t* hl, uint8_t d){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_E(7);
    uint8_t e = 7;

    do {
    // loop:
        // LD_hl_D;
        *hl = d;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // INC_D;
        d += 7;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);

    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void BattleWinSlideInEnemyTrainerFrontpic(void){
    // XOR_A_A;
    // LD_addr_A(wTempEnemyMonSpecies);
    wram->wTempEnemyMonSpecies = 0x0;
    // CALL(aFinishBattleAnim);
    FinishBattleAnim();
    // LD_A_addr(wOtherTrainerClass);
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = wram->wOtherTrainerClass;
    // LD_DE(vTiles2);
    // CALLFAR(aGetTrainerPic);
    GetTrainerPic_Conv(vram->vTiles2, wram->wTrainerClass);
    // hlcoord(19, 0, wTilemap);
    tile_t* hl = coord(19, 0, wram->wTilemap);
    // LD_C(0);
    uint8_t c = 0;

    while((++c & 7) != 0) {
    // outer_loop:
        // INC_C;
        // LD_A_C;
        // CP_A(7);
        // RET_Z ;
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
        // LDH_addr_A(hBGMapThird);
        hram->hBGMapThird = 0x0;
        // LD_D(0x0);
        uint8_t d = 0x0;
        // PUSH_BC;
        // PUSH_HL;
        uint8_t c2 = c;
        tile_t* hl2 = hl;
        do {
        // inner_loop:
            // CALL(aBattleWinSlideInEnemyTrainerFrontpic_CopyColumn);
            BattleWinSlideInEnemyTrainerFrontpic_CopyColumn(hl2, d);
            // INC_HL;
            hl2++;
            // LD_A(7);
            // ADD_A_D;
            // LD_D_A;
            d++;
            // DEC_C;
            // IF_NZ goto inner_loop;
        } while(--c2 != 0);

        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // LD_C(4);
        // CALL(aDelayFrames);
        DelayFrames_Conv(4);
        // POP_HL;
        // POP_BC;
        // DEC_HL;
        --hl;
        // goto outer_loop;
    }
}

void ApplyStatusEffectOnPlayerStats(void){
    // LD_A(1);
    // JR(mApplyStatusEffectOnStats);
    return ApplyStatusEffectOnStats_Conv(1);
}

void ApplyStatusEffectOnEnemyStats(void){
    // XOR_A_A;

    return ApplyStatusEffectOnStats_Conv(0);
}

void ApplyStatusEffectOnStats(void){
    LDH_addr_A(hBattleTurn);
    CALL(aApplyPrzEffectOnSpeed);
    JP(mApplyBrnEffectOnAttack);

}

void ApplyStatusEffectOnStats_Conv(uint8_t turn){
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = turn;
    // CALL(aApplyPrzEffectOnSpeed);
    ApplyPrzEffectOnSpeed_Conv(turn);
    // JP(mApplyBrnEffectOnAttack);
    ApplyBrnEffectOnAttack_Conv(turn);

}

void ApplyPrzEffectOnSpeed(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto enemy;
    LD_A_addr(wBattleMonStatus);
    AND_A(1 << PAR);
    RET_Z ;
    LD_HL(wBattleMonSpeed + 1);
    LD_A_hld;
    LD_B_A;
    LD_A_hl;
    SRL_A;
    RR_B;
    SRL_A;
    RR_B;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto player_ok;
    LD_B(0x1);  // min speed


player_ok:
    LD_hl_B;
    RET;


enemy:
    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << PAR);
    RET_Z ;
    LD_HL(wEnemyMonSpeed + 1);
    LD_A_hld;
    LD_B_A;
    LD_A_hl;
    SRL_A;
    RR_B;
    SRL_A;
    RR_B;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto enemy_ok;
    LD_B(0x1);  // min speed


enemy_ok:
    LD_hl_B;
    RET;

}

void ApplyPrzEffectOnSpeed_Conv(uint8_t turn){
    PEEK("");
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto enemy;
    if(turn != 0) {
        // LD_A_addr(wBattleMonStatus);
        // AND_A(1 << PAR);
        // RET_Z ;
        if(!(wram->wBattleMon.status[0] & (1 << PAR)))
            return;
        // LD_HL(wBattleMonSpeed + 1);
        // LD_A_hld;
        // LD_B_A;
        // LD_A_hl;
        // SRL_A;
        // RR_B;
        // SRL_A;
        // RR_B;
        uint16_t speed = ((wram->wBattleMon.speed[0] << 8) | wram->wBattleMon.speed[1]) >> 2;
        // LD_hli_A;
        // OR_A_B;
        // IF_NZ goto player_ok;
        // LD_B(0x1);  // min speed
        if(speed == 0)
            speed = 1;

    // player_ok:
        // LD_hl_B;
        // RET;
        wram->wBattleMon.speed[0] = HIGH(speed);
        wram->wBattleMon.speed[1] = LOW(speed);
        return;
    }
    else {
    // enemy:
        // LD_A_addr(wEnemyMonStatus);
        // AND_A(1 << PAR);
        // RET_Z ;
        if(!(wram->wEnemyMon.status[0] & (1 << PAR)))
            return;
        // LD_HL(wEnemyMonSpeed + 1);
        // LD_A_hld;
        // LD_B_A;
        // LD_A_hl;
        // SRL_A;
        // RR_B;
        // SRL_A;
        // RR_B;
        uint16_t speed = ((wram->wEnemyMon.speed[0] << 8) | wram->wEnemyMon.speed[1]) >> 2;
        // LD_hli_A;
        // OR_A_B;
        // IF_NZ goto enemy_ok;
        if(speed == 0)
            speed = 0x1;
        // LD_B(0x1);  // min speed


    // enemy_ok:
        // LD_hl_B;
        // RET;
        wram->wEnemyMon.speed[0] = HIGH(speed);
        wram->wEnemyMon.speed[1] = LOW(speed);
        return;
    }
}

void ApplyBrnEffectOnAttack(void){
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto enemy;
    LD_A_addr(wBattleMonStatus);
    AND_A(1 << BRN);
    RET_Z ;
    LD_HL(wBattleMonAttack + 1);
    LD_A_hld;
    LD_B_A;
    LD_A_hl;
    SRL_A;
    RR_B;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto player_ok;
    LD_B(0x1);  // min attack


player_ok:
    LD_hl_B;
    RET;


enemy:
    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << BRN);
    RET_Z ;
    LD_HL(wEnemyMonAttack + 1);
    LD_A_hld;
    LD_B_A;
    LD_A_hl;
    SRL_A;
    RR_B;
    LD_hli_A;
    OR_A_B;
    IF_NZ goto enemy_ok;
    LD_B(0x1);  // min attack


enemy_ok:
    LD_hl_B;
    RET;

}

void ApplyBrnEffectOnAttack_Conv(uint8_t turn){
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto enemy;
    if(turn != 0) {
        // LD_A_addr(wBattleMonStatus);
        // AND_A(1 << BRN);
        // RET_Z ;
        if(!(wram->wBattleMon.status[0] & (1 << BRN)))
            return;
        // LD_HL(wBattleMonAttack + 1);
        // LD_A_hld;
        // LD_B_A;
        // LD_A_hl;
        // SRL_A;
        // RR_B;
        uint16_t attack = ((wram->wBattleMon.attack[0] << 8) | wram->wBattleMon.attack[1]) >> 2;
        // LD_hli_A;
        // OR_A_B;
        // IF_NZ goto player_ok;
        // LD_B(0x1);  // min attack
        if(attack == 0)
            attack = 0x1;


    // player_ok:
        // LD_hl_B;
        // RET;
        wram->wBattleMon.attack[0] = HIGH(attack);
        wram->wBattleMon.attack[1] = LOW(attack);
        return;
    }
    else {
    // enemy:
        // LD_A_addr(wEnemyMonStatus);
        // AND_A(1 << BRN);
        // RET_Z ;
        if(!(wram->wEnemyMon.status[0] & (1 << BRN)))
            return;
        // LD_HL(wEnemyMonAttack + 1);
        // LD_A_hld;
        // LD_B_A;
        // LD_A_hl;
        // SRL_A;
        // RR_B;
        uint16_t attack = ((wram->wEnemyMon.attack[0] << 8) | wram->wEnemyMon.attack[1]) >> 2;
        // LD_hli_A;
        // OR_A_B;
        // IF_NZ goto enemy_ok;
        // LD_B(0x1);  // min attack
        if(attack == 0)
            attack = 0x1;

    // enemy_ok:
        // LD_hl_B;
        // RET;
        wram->wEnemyMon.attack[0] = HIGH(attack);
        wram->wEnemyMon.attack[1] = LOW(attack);
        return;
    }
}

void ApplyStatLevelMultiplierOnAllStats(void){
//  Apply StatLevelMultipliers on all 5 Stats
    // LD_C(0);
    uint8_t c = 0;

    do {
    // stat_loop:
        // CALL(aApplyStatLevelMultiplier);
        ApplyStatLevelMultiplier_Conv(c);
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_BATTLE_STATS);
        // IF_NZ goto stat_loop;
    } while(++c != NUM_BATTLE_STATS);
    // RET;
}

void ApplyStatLevelMultiplier(void){
    PUSH_BC;
    PUSH_BC;
    LD_A_addr(wApplyStatLevelMultipliersToEnemy);
    AND_A_A;
    LD_A_C;
    LD_HL(wBattleMonAttack);
    LD_DE(wPlayerStats);
    LD_BC(wPlayerAtkLevel);
    IF_Z goto got_pointers;
    LD_HL(wEnemyMonAttack);
    LD_DE(wEnemyStats);
    LD_BC(wEnemyAtkLevel);


got_pointers:
    ADD_A_C;
    LD_C_A;
    IF_NC goto okay;
    INC_B;

okay:
    LD_A_bc;
    POP_BC;
    LD_B_A;
    PUSH_BC;
    SLA_C;
    LD_B(0);
    ADD_HL_BC;
    LD_A_C;
    ADD_A_E;
    LD_E_A;
    IF_NC goto okay2;
    INC_D;

okay2:
    POP_BC;
    PUSH_HL;
    LD_HL(mStatLevelMultipliers_Applied);
    DEC_B;
    SLA_B;
    LD_C_B;
    LD_B(0);
    ADD_HL_BC;
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A_de;
    LDH_addr_A(hMultiplicand + 1);
    INC_DE;
    LD_A_de;
    LDH_addr_A(hMultiplicand + 2);
    LD_A_hli;
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LD_A_hl;
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
    POP_HL;

//  Cap at 999.
    LDH_A_addr(hQuotient + 3);
    SUB_A(LOW(MAX_STAT_VALUE));
    LDH_A_addr(hQuotient + 2);
    SBC_A(HIGH(MAX_STAT_VALUE));
    JP_C (mApplyStatLevelMultiplier_okay3);

    LD_A(HIGH(MAX_STAT_VALUE));
    LDH_addr_A(hQuotient + 2);
    LD_A(LOW(MAX_STAT_VALUE));
    LDH_addr_A(hQuotient + 3);


okay3:
    LDH_A_addr(hQuotient + 2);
    LD_hli_A;
    LD_B_A;
    LDH_A_addr(hQuotient + 3);
    LD_hl_A;
    OR_A_B;
    IF_NZ goto okay4;
    INC_hl;


okay4:
    POP_BC;
    RET;

// INCLUDE "data/battle/stat_multipliers_2.asm"

    return BadgeStatBoosts();
}

void ApplyStatLevelMultiplier_Conv(uint8_t c){
    // PUSH_BC;
    // PUSH_BC;
    // LD_A_addr(wApplyStatLevelMultipliersToEnemy);
    // AND_A_A;
    // LD_A_C;
    // LD_HL(wBattleMonAttack);
    uint8_t (*hl)[2] = (!wram->wApplyStatLevelMultipliersToEnemy)? wram->wBattleMon.stats: wram->wEnemyMon.stats;
    // LD_DE(wPlayerStats);
    uint16_t* de = (uint16_t*)((!wram->wApplyStatLevelMultipliersToEnemy)? wram_ptr(wPlayerStats): wram_ptr(wEnemyStats));
    // LD_BC(wPlayerAtkLevel);
    uint8_t* bc = (!wram->wApplyStatLevelMultipliersToEnemy)? &wram->wPlayerAtkLevel: &wram->wEnemyAtkLevel;
    // IF_Z goto got_pointers;
    // LD_HL(wEnemyMonAttack);
    // LD_DE(wEnemyStats);
    // LD_BC(wEnemyAtkLevel);


// got_pointers:
    // ADD_A_C;
    // LD_C_A;
    // IF_NC goto okay;
    // INC_B;

// okay:
    // LD_A_bc;
    // POP_BC;
    // LD_B_A;
    uint8_t b = bc[c];
    // PUSH_BC;
    // SLA_C;
    // LD_B(0);
    // ADD_HL_BC;
    uint8_t* hl2 = hl[c];
    // LD_A_C;
    // ADD_A_E;
    // LD_E_A;
    // IF_NC goto okay2;
    // INC_D;
    de += c;

// okay2:
    // POP_BC;
    // PUSH_HL;
    // LD_HL(mStatLevelMultipliers_Applied);
    // DEC_B;
    // SLA_B;
    // LD_C_B;
    // LD_B(0);
    // ADD_HL_BC;
    const uint8_t* mul = StatLevelMultipliers_Applied[(b - 1) << 1];
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LD_A_de;
    // LDH_addr_A(hMultiplicand + 1);
    // INC_DE;
    // LD_A_de;
    // LDH_addr_A(hMultiplicand + 2);
    uint32_t n = ReverseEndian16(*de);
    // LD_A_hli;
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    n *= mul[0];
    // LD_A_hl;
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    n /= mul[1];
    // POP_HL;

//  Cap at 999.
    // LDH_A_addr(hQuotient + 3);
    // SUB_A(LOW(MAX_STAT_VALUE));
    // LDH_A_addr(hQuotient + 2);
    // SBC_A(HIGH(MAX_STAT_VALUE));
    // JP_C (mApplyStatLevelMultiplier_okay3);
    if(n > MAX_STAT_VALUE) {
        // LD_A(HIGH(MAX_STAT_VALUE));
        // LDH_addr_A(hQuotient + 2);
        // LD_A(LOW(MAX_STAT_VALUE));
        // LDH_addr_A(hQuotient + 3);
        n = MAX_STAT_VALUE;
    }

// okay3:
    // LDH_A_addr(hQuotient + 2);
    // LD_hli_A;
    // LD_B_A;
    // LDH_A_addr(hQuotient + 3);
    // LD_hl_A;
    // OR_A_B;
    // IF_NZ goto okay4;
    hl2[0] = HIGH(n);
    hl2[1] = LOW(n);
    if((n & 0xffff) != 0) {
        // INC_hl;
        hl2[1]++;
    }


// okay4:
    // POP_BC;
    // RET;

// INCLUDE "data/battle/stat_multipliers_2.asm"
}

//  Raise the stats of the battle mon in wBattleMon
//  depending on which badges have been obtained.
//  Every other badge boosts a stat, starting from the first.
//  GlacierBadge also boosts Special Defense, although the relevant code is buggy (see below).
//      ZephyrBadge:  Attack
//      PlainBadge:   Speed
//      MineralBadge: Defense
//      GlacierBadge: Special Attack and Special Defense
//  The boosted stats are in order, except PlainBadge and MineralBadge's boosts are swapped.
void BadgeStatBoosts(void){

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wLinkMode != 0)
        return;

    // LD_A_addr(wInBattleTowerBattle);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wInBattleTowerBattle != 0)
        return;

    // LD_A_addr(wJohtoBadges);
    uint8_t badges = wram->wJohtoBadges[0];

//  Swap badges 3 (PlainBadge) and 5 (MineralBadge).
    // LD_D_A;
    // AND_A((1 << PLAINBADGE));
    // ADD_A_A;
    // ADD_A_A;
    // LD_B_A;
    uint8_t b = (badges & (1 << PLAINBADGE)) << (MINERALBADGE - PLAINBADGE);
    // LD_A_D;
    // AND_A((1 << MINERALBADGE));
    // RRCA;
    // RRCA;
    // LD_C_A;
    uint8_t c = (badges & (1 << MINERALBADGE)) >> (MINERALBADGE - PLAINBADGE);
    // LD_A_D;
    // AND_A(((1 << ZEPHYRBADGE) | (1 << HIVEBADGE) | (1 << FOGBADGE) | (1 << STORMBADGE) | (1 << GLACIERBADGE) | (1 << RISINGBADGE)));
    // OR_A_B;
    // OR_A_C;
    // LD_B_A;
    b = (badges & ((1 << ZEPHYRBADGE) | (1 << HIVEBADGE) | (1 << FOGBADGE) | (1 << STORMBADGE) | (1 << GLACIERBADGE) | (1 << RISINGBADGE))) | b | c;

    // LD_HL(wBattleMonAttack);
    uint8_t stat = 0;
    uint8_t* hl = wram->wBattleMon.stats[stat];
    // LD_C(4);
    c = 4;
    uint8_t a = 0;

    do {
    // CheckBadge:
        // LD_A_B;
        a = b;
        // SRL_B;
        if(a & 1)
            a = BoostStat_Conv(hl);
        // CALL_C (aBoostStat);
        // INC_HL;
        // INC_HL;
        hl = wram->wBattleMon.stats[++stat];
    //  Check every other badge.
        // SRL_B;
        b >>= 2;
        // DEC_C;
        // IF_NZ goto CheckBadge;
    } while(--c != 0);
//  Check GlacierBadge again for Special Defense.
//  This check is buggy because it assumes that a is set by the "ld a, b" in the above loop,
//  but it can actually be overwritten by the call to BoostStat.
    // SRL_A;
    // CALL_C (aBoostStat);
    if(a & 1)
        BoostStat_Conv(hl);
    // RET;
}

void BoostStat(void){
//  Raise stat at hl by 1/8.

    LD_A_hli;
    LD_D_A;
    LD_E_hl;
    SRL_D;
    RR_E;
    SRL_D;
    RR_E;
    SRL_D;
    RR_E;
    LD_A_hl;
    ADD_A_E;
    LD_hld_A;
    LD_A_hl;
    ADC_A_D;
    LD_hli_A;

//  Cap at 999.
    LD_A_hld;
    SUB_A(LOW(MAX_STAT_VALUE));
    LD_A_hl;
    SBC_A(HIGH(MAX_STAT_VALUE));
    RET_C ;
    LD_A(HIGH(MAX_STAT_VALUE));
    LD_hli_A;
    LD_A(LOW(MAX_STAT_VALUE));
    LD_hld_A;
    RET;

}

//  Raise stat at hl by 1/8.
uint8_t BoostStat_Conv(uint8_t* hl){
    // LD_A_hli;
    // LD_D_A;
    // LD_E_hl;
    uint16_t stat = (hl[0] << 8) | hl[1];
    // SRL_D;
    // RR_E;
    // SRL_D;
    // RR_E;
    // SRL_D;
    // RR_E;
    // LD_A_hl;
    // ADD_A_E;
    // LD_hld_A;
    // LD_A_hl;
    // ADC_A_D;
    // LD_hli_A;

    //stat = stat + (stat / 8)
    stat += (stat >> 3);

//  Cap at 999.
    // LD_A_hld;
    // SUB_A(LOW(MAX_STAT_VALUE));
    // LD_A_hl;
    // SBC_A(HIGH(MAX_STAT_VALUE));
    // RET_C ;
    if(stat > MAX_STAT_VALUE) {
        stat = MAX_STAT_VALUE;
    }
    // LD_A(HIGH(MAX_STAT_VALUE));
    // LD_hli_A;
    // LD_A(LOW(MAX_STAT_VALUE));
    // LD_hld_A;
    hl[0] = HIGH(stat);
    hl[1] = LOW(stat);
    // RET;
    return LOW(stat);
}

void v_LoadBattleFontsHPBar(void){
    // CALLFAR(aLoadBattleFontsHPBar);
    LoadBattleFontsHPBar_Conv();
    // RET;
}

void v_LoadHPBar(void){
    CALLFAR(aLoadHPBar);
    RET;

}

void v_LoadHPBar_Conv(void){
    // CALLFAR(aLoadHPBar);
    // RET;
    return LoadHPBar_Conv();
}

void LoadHPExpBarGFX(void){
//  //  unreferenced
    LD_DE(mEnemyHPBarBorderGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x6c);
    LD_BC((BANK(aEnemyHPBarBorderGFX) << 8) | 4);
    CALL(aGet1bpp);
    LD_DE(mHPExpBarBorderGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x73);
    LD_BC((BANK(aHPExpBarBorderGFX) << 8) | 6);
    CALL(aGet1bpp);
    LD_DE(mExpBarGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x55);
    LD_BC((BANK(aExpBarGFX) << 8) | 8);
    JP(mGet2bpp);

}

void EmptyBattleTextbox(void){
    static const txt_cmd_s empty[] = {
        text_end
    };
    //text_end ['?']
    // LD_HL(mEmptyBattleTextbox_empty);
    // JP(mBattleTextbox);
    return BattleTextbox_Conv2(empty);
}

//  If the normal RNG is used in a link battle it'll desync.
//  To circumvent this a shared PRNG is used instead.
void v_BattleRandom(void){
//  But if we're in a non-link battle we're safe to use it
    LD_A_addr(wLinkMode);
    AND_A_A;
    JP_Z (mRandom);

//  The PRNG operates in streams of 10 values.

//  Which value are we trying to pull?
    PUSH_HL;
    PUSH_BC;
    LD_A_addr(wLinkBattleRNCount);
    LD_C_A;
    LD_B(0);
    LD_HL(wLinkBattleRNs);
    ADD_HL_BC;
    INC_A;
    LD_addr_A(wLinkBattleRNCount);

//  If we haven't hit the end yet, we're good
    CP_A(10 - 1);  // Exclude last value. See the closing comment
    LD_A_hl;
    POP_BC;
    POP_HL;
    RET_C ;

//  If we have, we have to generate new pseudorandom data
//  Instead of having multiple PRNGs, ten seeds are used
    PUSH_HL;
    PUSH_BC;
    PUSH_AF;

//  Reset count to 0
    XOR_A_A;
    LD_addr_A(wLinkBattleRNCount);
    LD_HL(wLinkBattleRNs);
    LD_B(10);  // number of seeds

//  Generate next number in the sequence for each seed
//  a[n+1] = (a[n] * 5 + 1) % 256

loop:
// get last #
    LD_A_hl;

// a * 5 + 1
    LD_C_A;
    ADD_A_A;
    ADD_A_A;
    ADD_A_C;
    INC_A;

// update #
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;

//  This has the side effect of pulling the last value first,
//  then wrapping around. As a result, when we check to see if
//  we've reached the end, we check the one before it.

    POP_AF;
    POP_BC;
    POP_HL;
    RET;

}

//  If the normal RNG is used in a link battle it'll desync.
//  To circumvent this a shared PRNG is used instead.
uint8_t v_BattleRandom_Conv(void){
//  But if we're in a non-link battle we're safe to use it
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // JP_Z (mRandom);
    if(wram->wLinkMode == 0)
        return Random_Conv();

//  The PRNG operates in streams of 10 values.

//  Which value are we trying to pull?
    // PUSH_HL;
    // PUSH_BC;
    // LD_A_addr(wLinkBattleRNCount);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wLinkBattleRNs);
    // ADD_HL_BC;
    uint8_t* hl = wram->wLinkBattleRNs + wram->wLinkBattleRNCount;
    // INC_A;
    // LD_addr_A(wLinkBattleRNCount);
    uint8_t a = ++wram->wLinkBattleRNCount;

//  If we haven't hit the end yet, we're good
    // CP_A(10 - 1);  // Exclude last value. See the closing comment
    // LD_A_hl;
    // POP_BC;
    // POP_HL;
    // RET_C ;
    if(a < 10 - 1) {
        return *hl;
    }

//  If we have, we have to generate new pseudorandom data
//  Instead of having multiple PRNGs, ten seeds are used
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_AF;
    a = *hl;

//  Reset count to 0
    // XOR_A_A;
    // LD_addr_A(wLinkBattleRNCount);
    wram->wLinkBattleRNCount = 0;
    // LD_HL(wLinkBattleRNs);
    hl = wram->wLinkBattleRNs;
    // LD_B(10);  // number of seeds
    uint8_t b = 10;

//  Generate next number in the sequence for each seed
//  a[n+1] = (a[n] * 5 + 1) % 256
    do {
    // loop:
    // get last #
        // LD_A_hl;

    // a * 5 + 1
        // LD_C_A;
        // ADD_A_A;
        // ADD_A_A;
        // ADD_A_C;
        // INC_A;

    // update #
        // LD_hli_A;
        *hl = *hl * 5 + 1;
        hl++;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);

//  This has the side effect of pulling the last value first,
//  then wrapping around. As a result, when we check to see if
//  we've reached the end, we check the one before it.

    // POP_AF;
    // POP_BC;
    // POP_HL;
    // RET;
    return a;
}

void Call_PlayBattleAnim_OnlyIfVisible(void){
    LD_A(BATTLE_VARS_SUBSTATUS3);
    CALL(aGetBattleVar);
    AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    RET_NZ ;

    return Call_PlayBattleAnim();
}

void Call_PlayBattleAnim_OnlyIfVisible_Conv(uint16_t de){
    // LD_A(BATTLE_VARS_SUBSTATUS3);
    // CALL(aGetBattleVar);
    // AND_A(1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND);
    // RET_NZ ;
    if(GetBattleVar_Conv(BATTLE_VARS_SUBSTATUS3) & (1 << SUBSTATUS_FLYING | 1 << SUBSTATUS_UNDERGROUND))
        return;

    return Call_PlayBattleAnim_Conv(de);
}

void Call_PlayBattleAnim(void){
    LD_A_E;
    LD_addr_A(wFXAnimID);
    LD_A_D;
    LD_addr_A(wFXAnimID + 1);
    CALL(aWaitBGMap);
    PREDEF_JUMP(pPlayBattleAnim);

    return FinishBattleAnim();
}

void Call_PlayBattleAnim_Conv(uint16_t de){
    // LD_A_E;
    // LD_addr_A(wFXAnimID);
    // LD_A_D;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID = de;
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // PREDEF_JUMP(pPlayBattleAnim);
    PlayBattleAnim();
}

void FinishBattleAnim(void){
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // LD_B(SCGB_BATTLE_COLORS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_BATTLE_COLORS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    // RET;
}

static void GiveExperiencePoints_EvenlyDivideExpAmongParticipants(void){
//  count number of battle participants
    // LD_A_addr(wBattleParticipantsNotFainted);
    // LD_B_A;
    uint8_t b = wram->wBattleParticipantsNotFainted;
    // LD_C(PARTY_LENGTH);
    uint8_t c = PARTY_LENGTH;
    // LD_D(0);
    uint8_t d = 0;

    do {
    // count_loop:
        // XOR_A_A;
        uint8_t cy = b & 1;
        // SRL_B;
        b >>= 1;
        // ADC_A_D;
        // LD_D_A;
        d += cy;
        // DEC_C;
        // IF_NZ goto count_loop;
    } while(--c != 0);
    // CP_A(2);
    // RET_C ;
    if(d < 2)
        return;

    // LD_addr_A(wTempByteValue);
    // LD_HL(wEnemyMonBaseStats);
    uint8_t* hl = wram->wEnemyMonBaseStats;
    // LD_C(wEnemyMonEnd - wEnemyMonBaseStats);
    c = wEnemyMonEnd - wEnemyMonBaseStats;

    do {
    // base_stat_division_loop:
        // XOR_A_A;
        // LDH_addr_A(hDividend + 0);
        // LD_A_hl;
        // LDH_addr_A(hDividend + 1);
        // LD_A_addr(wTempByteValue);
        // LDH_addr_A(hDivisor);
        // LD_B(2);
        // CALL(aDivide);
        // LDH_A_addr(hQuotient + 3);
        // LD_hli_A;
        *(hl++) /= d;
        // DEC_C;
        // IF_NZ goto base_stat_division_loop;
    } while(--c != 0);
    // RET;
}

//  Give experience.
//  Don't give experience if linked or in the Battle Tower.
void GiveExperiencePoints(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wLinkMode != 0)
        return;

    // LD_A_addr(wInBattleTowerBattle);
    // BIT_A(0);
    // RET_NZ ;
    if(bit_test(wram->wInBattleTowerBattle, 0))
        return;

    // CALL(aGiveExperiencePoints_EvenlyDivideExpAmongParticipants);
    GiveExperiencePoints_EvenlyDivideExpAmongParticipants();
    // XOR_A_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = 0x0;
    // LD_BC(wPartyMon1Species);
    struct PartyMon* bc = wram->wPartyMon;

    while(1){
    // loop:
        // LD_HL(MON_HP);
        // ADD_HL_BC;
        // LD_A_hli;
        // OR_A_hl;
        // JP_Z (mGiveExperiencePoints_next_mon);  // fainted
        if(bc->HP == 0)
            goto next_mon;

        // PUSH_BC;
        // LD_HL(wBattleParticipantsNotFainted);
        // LD_A_addr(wCurPartyMon);
        // LD_C_A;
        // LD_B(CHECK_FLAG);
        // LD_D(0);
        // PREDEF(pSmallFarFlagAction);
        // LD_A_C;
        // AND_A_A;
        // POP_BC;
        // JP_Z (mGiveExperiencePoints_next_mon);
        if(SmallFarFlagAction_Conv(&wram->wBattleParticipantsNotFainted, wram->wCurPartyMon, CHECK_FLAG) == 0)
            goto next_mon;

    //  give stat exp
        // LD_HL(MON_STAT_EXP + 1);
        // ADD_HL_BC;
        // LD_D_H;
        // LD_E_L;
        // LD_HL(wEnemyMonBaseStats - 1);
        uint8_t* baseStats = wram->wEnemyMonBaseStats;
        // PUSH_BC;
        // LD_C(NUM_EXP_STATS);
        uint8_t c = NUM_EXP_STATS;
        uint8_t b;
        uint8_t i = 0;

        do {
        // stat_exp_loop:
            // INC_HL;
            // LD_A_de;
            // ADD_A_hl;
            // LD_de_A;
            uint16_t xp = BigEndianToNative16(bc->mon.statExp[i]);
            // IF_NC goto no_carry_stat_exp;
            // DEC_DE;
            // LD_A_de;
            // INC_A;
            // IF_Z goto stat_exp_maxed_out;
            if(xp + baseStats[i] > 0xffff)
                goto stat_exp_maxed_out;
            // LD_de_A;
            // INC_DE;
            xp += baseStats[i];

        // no_carry_stat_exp:
            // PUSH_HL;
            // PUSH_BC;
            // LD_A(MON_POKERUS);
            // CALL(aGetPartyParamLocation);
            // LD_A_hl;
            // AND_A_A;
            // POP_BC;
            // POP_HL;
            // IF_Z goto stat_exp_awarded;
            if(bc->mon.pokerusStatus != 0){
                // LD_A_de;
                // ADD_A_hl;
                // LD_de_A;
                // IF_NC goto stat_exp_awarded;
                // DEC_DE;
                // LD_A_de;
                // INC_A;
                // IF_Z goto stat_exp_maxed_out;
                // LD_de_A;
                // INC_DE;
                // goto stat_exp_awarded;
                if(xp + baseStats[i] > 0xffff){
                stat_exp_maxed_out:
                    // LD_A(0xff);
                    // LD_de_A;
                    // INC_DE;
                    // LD_de_A;
                    xp = 0xffff;
                }
                else {
                    xp += baseStats[i];
                }
            }

            bc->mon.statExp[i] = NativeToBigEndian16(xp);
            // goto stat_exp_awarded;


        // stat_exp_awarded:
            // INC_DE;
            // INC_DE;
            i++;
            // DEC_C;
            // IF_NZ goto stat_exp_loop;
        } while(--c != 0);
        // XOR_A_A;
        // LDH_addr_A(hMultiplicand + 0);
        // LDH_addr_A(hMultiplicand + 1);
        // LD_A_addr(wEnemyMonBaseExp);
        // LDH_addr_A(hMultiplicand + 2);
        // LD_A_addr(wEnemyMonLevel);
        // LDH_addr_A(hMultiplier);
        // CALL(aMultiply);
        // LD_A(7);
        // LDH_addr_A(hDivisor);
        // LD_B(4);
        // CALL(aDivide);
        uint16_t bExp = (wram->wEnemyMonBaseExp * wram->wEnemyMon.level) / 7;
    //  Boost Experience for traded Pokemon
        // POP_BC;
        // LD_HL(MON_ID);
        // ADD_HL_BC;
        // LD_A_addr(wPlayerID);
        // CP_A_hl;
        // IF_NZ goto boosted;
        // INC_HL;
        // LD_A_addr(wPlayerID + 1);
        // CP_A_hl;
        // LD_A(0);
        uint8_t a = 0;
        // IF_Z goto no_boost;
        if(bc->mon.id != wram->wPlayerID){
        // boosted:
            // CALL(aBoostExp);
            bExp = BoostExp_Conv(bExp);
            // LD_A(1);
            a = 1;
        }

    // no_boost:
    //  Boost experience for a Trainer Battle
        // LD_addr_A(wStringBuffer2 + 2);
        wram->wStringBuffer2[2] = a;
        // LD_A_addr(wBattleMode);
        // DEC_A;
        // CALL_NZ (aBoostExp);
        if(wram->wBattleMode != WILD_BATTLE)
            bExp = BoostExp_Conv(bExp);
    //  Boost experience for Lucky Egg
        // PUSH_BC;
        // LD_A(MON_ITEM);
        // CALL(aGetPartyParamLocation);
        // LD_A_hl;
        // CP_A(LUCKY_EGG);
        // CALL_Z (aBoostExp);
        if(bc->mon.item == LUCKY_EGG)
            bExp = BoostExp_Conv(bExp);
        // LDH_A_addr(hQuotient + 3);
        // LD_addr_A(wStringBuffer2 + 1);
        wram->wStringBuffer2[1] = LOW(bExp);
        // LDH_A_addr(hQuotient + 2);
        // LD_addr_A(wStringBuffer2);
        wram->wStringBuffer2[0] = HIGH(bExp);
        // LD_A_addr(wCurPartyMon);
        // LD_HL(wPartyMonNicknames);
        // CALL(aGetNickname);
        GetNickname_Conv2(wram->wPartyMonNickname[0], wram->wCurPartyMon);
        // LD_HL(mText_MonGainedExpPoint);
        // CALL(aBattleTextbox);
        BattleTextbox_Conv2(Text_MonGainedExpPoint);
        // LD_A_addr(wStringBuffer2 + 1);
        // LDH_addr_A(hQuotient + 3);
        // LD_A_addr(wStringBuffer2);
        // LDH_addr_A(hQuotient + 2);
        // POP_BC;
        // CALL(aAnimateExpBar);
        AnimateExpBar(bExp);
        // PUSH_BC;
        // CALL(aLoadTilemapToTempTilemap);
        LoadTilemapToTempTilemap_Conv();
        // POP_BC;
        // LD_HL(MON_EXP + 2);
        uint32_t bcExp = (bc->mon.exp[0] << 16) | (bc->mon.exp[1] << 8) | bc->mon.exp[2];
        // ADD_HL_BC;
        // LD_D_hl;
        // LDH_A_addr(hQuotient + 3);
        // ADD_A_D;
        // LD_hld_A;
        // LD_D_hl;
        // LDH_A_addr(hQuotient + 2);
        // ADC_A_D;
        // LD_hl_A;
        if(bcExp + bExp > 0xffffff){
            // IF_NC goto no_exp_overflow;
            // DEC_HL;
            // INC_hl;
            // IF_NZ goto no_exp_overflow;
            // LD_A(0xff);
            bcExp = 0xffffff;
            // LD_hli_A;
            // LD_hli_A;
            // LD_hl_A;
        }
        else {
            bcExp += bExp;
        }

        bc->mon.exp[2] = LOW(bcExp);
        bc->mon.exp[1] = HIGH(bcExp);
        bc->mon.exp[0] = HIGH(bcExp >> 8);

    // no_exp_overflow:
        // LD_A_addr(wCurPartyMon);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(wPartySpecies);
        // ADD_HL_DE;
        // LD_A_hl;
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = wram->wPartySpecies[wram->wCurPartyMon];
        // CALL(aGetBaseData);
        GetBaseData_Conv2(wram->wCurSpecies);
        // PUSH_BC;
        // LD_D(MAX_LEVEL);
        // CALLFAR(aCalcExpAtLevel);
        uint32_t maxExp = CalcExpAtLevel_Conv(MAX_LEVEL);
        // POP_BC;
        // LD_HL(MON_EXP + 2);
        // ADD_HL_BC;
        // PUSH_BC;
        // LDH_A_addr(hQuotient + 1);
        // LD_B_A;
        // LDH_A_addr(hQuotient + 2);
        // LD_C_A;
        // LDH_A_addr(hQuotient + 3);
        // LD_D_A;
        // LD_A_hld;
        // SUB_A_D;
        // LD_A_hld;
        // SBC_A_C;
        // LD_A_hl;
        // SBC_A_B;
        // IF_C goto not_max_exp;
        if(bcExp > maxExp){
            // LD_A_B;
            // LD_hli_A;
            // LD_A_C;
            // LD_hli_A;
            // LD_A_D;
            // LD_hld_A;
            bcExp = maxExp;
            bc->mon.exp[2] = LOW(bcExp);
            bc->mon.exp[1] = HIGH(bcExp);
            bc->mon.exp[0] = HIGH(bcExp >> 8);
        }

    // not_max_exp:
    //  Check if the mon leveled up
        // XOR_A_A;  // PARTYMON
        // LD_addr_A(wMonType);
        wram->wMonType = PARTYMON;
        // PREDEF(pCopyMonToTempMon);
        CopyMonToTempMon_Conv();
        // CALLFAR(aCalcLevel);
        uint8_t d = CalcLevel_Conv(&wram->wTempMon);
        // POP_BC;
        // LD_HL(MON_LEVEL);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(MAX_LEVEL);
        // JP_NC (mGiveExperiencePoints_next_mon);
        // CP_A_D;
        // JP_Z (mGiveExperiencePoints_next_mon);
        if(bc->mon.level < MAX_LEVEL && bc->mon.level != d){
        //  <NICKNAME> grew to level ##!
            // LD_addr_A(wTempLevel);
            wram->wTempLevel = bc->mon.level;
            // LD_A_addr(wCurPartyLevel);
            // PUSH_AF;
            uint8_t lvl = wram->wCurPartyLevel;
            // LD_A_D;
            // LD_addr_A(wCurPartyLevel);
            wram->wCurPartyLevel = d;
            // LD_hl_A;
            bc->mon.level = d;
            // LD_HL(MON_SPECIES);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_addr_A(wCurSpecies);
            wram->wCurSpecies = bc->mon.species;
            // LD_addr_A(wTempSpecies);  // unused?
            // CALL(aGetBaseData);
            GetBaseData_Conv2(wram->wCurSpecies);
            // LD_HL(MON_MAXHP + 1);
            // ADD_HL_BC;
            // LD_A_hld;
            // LD_E_A;
            // LD_D_hl;
            // PUSH_DE;
            uint16_t maxHP = BigEndianToNative16(bc->maxHP);
            // LD_HL(MON_MAXHP);
            // ADD_HL_BC;
            // LD_D_H;
            // LD_E_L;
            // LD_HL(MON_STAT_EXP - 1);
            // ADD_HL_BC;
            // PUSH_BC;
            // LD_B(TRUE);
            // PREDEF(pCalcMonStats);
#if !defined(_MSC_VER)
            // MSVC doesn't like this
            const uint16_t* statxp = (uint16_t*)((uint8_t*)bc + offsetof(struct BoxMon, statExp));
            uint16_t* stats = (uint16_t*)((uint8_t*)bc + offsetof(struct PartyMon, maxHP));
#else
            // GCC doesn't like this
            const uint16_t* statxp = ((const struct BoxMon*)bc)->statExp;
            uint16_t* stats = ((const struct PartyMon*)bc)->maxHP;
#endif
            CalcMonStats_Conv(stats, statxp, bc->mon.DVs, TRUE);
            // POP_BC;
            // POP_DE;
            // LD_HL(MON_MAXHP + 1);
            // ADD_HL_BC;
            // LD_A_hld;
            // SUB_A_E;
            // LD_E_A;
            // LD_A_hl;
            // SBC_A_D;
            // LD_D_A;
            maxHP = BigEndianToNative16(bc->maxHP) - maxHP;
            // DEC_HL;
            // LD_A_hl;
            // ADD_A_E;
            // LD_hld_A;
            // LD_A_hl;
            // ADC_A_D;
            // LD_hl_A;
            bc->HP = NativeToBigEndian16(BigEndianToNative16(bc->HP) + maxHP);
            // LD_A_addr(wCurBattleMon);
            // LD_D_A;
            // LD_A_addr(wCurPartyMon);
            // CP_A_D;
            // IF_NZ goto skip_active_mon_update;
            if(wram->wCurPartyMon == wram->wCurBattleMon){
                // LD_DE(wBattleMonHP);
                // LD_A_hli;
                // LD_de_A;
                // INC_DE;
                // LD_A_hli;
                // LD_de_A;
                wram->wBattleMon.hp = bc->HP;
                // LD_DE(wBattleMonMaxHP);
                // PUSH_BC;
                // LD_BC(PARTYMON_STRUCT_LENGTH - MON_MAXHP);
                // CALL(aCopyBytes);
                CopyBytes_Conv2(wram->wBattleMon.stats, bc->stats, PARTYMON_STRUCT_LENGTH - MON_MAXHP);
                // POP_BC;
                // LD_HL(MON_LEVEL);
                // ADD_HL_BC;
                // LD_A_hl;
                // LD_addr_A(wBattleMonLevel);
                wram->wBattleMon.level = bc->mon.level;
                // LD_A_addr(wPlayerSubStatus5);
                // BIT_A(SUBSTATUS_TRANSFORMED);
                // IF_NZ goto transformed;
                if(!bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TRANSFORMED)){
                    // LD_HL(MON_ATK);
                    // ADD_HL_BC;
                    // LD_DE(wPlayerStats);
                    // LD_BC(PARTYMON_STRUCT_LENGTH - MON_ATK);
                    // CALL(aCopyBytes);
                    CopyBytes_Conv2(wram->wPlayerStats, bc->stats, PARTYMON_STRUCT_LENGTH - MON_ATK);
                }

            // transformed:
                // XOR_A_A;  // FALSE
                // LD_addr_A(wApplyStatLevelMultipliersToEnemy);
                wram->wApplyStatLevelMultipliersToEnemy = FALSE;
                // CALL(aApplyStatLevelMultiplierOnAllStats);
                ApplyStatLevelMultiplierOnAllStats();
                // CALLFAR(aApplyStatusEffectOnPlayerStats);
                ApplyStatusEffectOnPlayerStats();
                // CALLFAR(aBadgeStatBoosts);
                BadgeStatBoosts();
                // CALLFAR(aUpdatePlayerHUD);
                UpdatePlayerHUD();
                // CALL(aEmptyBattleTextbox);
                EmptyBattleTextbox();
                // CALL(aLoadTilemapToTempTilemap);
                LoadTilemapToTempTilemap_Conv();
                // LD_A(0x1);
                // LDH_addr_A(hBGMapMode);
                hram->hBGMapMode = 0x1;
            }

        // skip_active_mon_update:
            // FARCALL(aLevelUpHappinessMod);
            LevelUpHappinessMod();
            // LD_A_addr(wCurBattleMon);
            // LD_B_A;
            // LD_A_addr(wCurPartyMon);
            // CP_A_B;
            // IF_Z goto skip_exp_bar_animation;
            if(wram->wCurPartyMon != wram->wCurBattleMon){
                // LD_DE(SFX_HIT_END_OF_EXP_BAR);
                // CALL(aPlaySFX);
                PlaySFX_Conv(SFX_HIT_END_OF_EXP_BAR);
                // CALL(aWaitSFX);
                WaitSFX_Conv();
                // LD_HL(mBattleText_StringBuffer1GrewToLevel);
                // CALL(aStdBattleTextbox);
                StdBattleTextbox_Conv2(BattleText_StringBuffer1GrewToLevel);
                // CALL(aLoadTilemapToTempTilemap);
                LoadTilemapToTempTilemap_Conv();
            }

        // skip_exp_bar_animation:
            // XOR_A_A;  // PARTYMON
            // LD_addr_A(wMonType);
            wram->wMonType = PARTYMON;
            // PREDEF(pCopyMonToTempMon);
            CopyMonToTempMon_Conv();
            // hlcoord(9, 0, wTilemap);
            // LD_B(10);
            // LD_C(9);
            // CALL(aTextbox);
            Textbox_Conv2(coord(9, 0, wram->wTilemap), 10, 9);
            // hlcoord(11, 1, wTilemap);
            // LD_BC(4);
            // PREDEF(pPrintTempMonStats);
            PrintTempMonStats_Conv(coord(11, 1, wram->wTilemap), 4);
            // LD_C(30);
            // CALL(aDelayFrames);
            DelayFrames_Conv(30);
            // CALL(aWaitPressAorB_BlinkCursor);
            WaitPressAorB_BlinkCursor_Conv();
            // CALL(aSafeLoadTempTilemapToTilemap);
            SafeLoadTempTilemapToTilemap_Conv();
            // XOR_A_A;  // PARTYMON
            // LD_addr_A(wMonType);
            wram->wMonType = PARTYMON;
            // LD_A_addr(wCurSpecies);
            // LD_addr_A(wTempSpecies);  // unused?
            // LD_A_addr(wCurPartyLevel);
            // PUSH_AF;
            // LD_C_A;
            c = wram->wCurPartyLevel;
            // LD_A_addr(wTempLevel);
            // LD_B_A;
            b = wram->wTempLevel;

            do {
            // level_loop:
                // INC_B;
                // LD_A_B;
                // LD_addr_A(wCurPartyLevel);
                wram->wCurPartyLevel = ++b;
                // PUSH_BC;
                // PREDEF(pLearnLevelMoves);
                LearnLevelMoves_Conv(bc, wram->wCurPartyLevel, wram->wCurPartySpecies);
                // POP_BC;
                // LD_A_B;
                // CP_A_C;
                // IF_NZ goto level_loop;
            } while(b != c);
            // POP_AF;
            // LD_addr_A(wCurPartyLevel);
            wram->wCurPartyLevel = c;
            // LD_HL(wEvolvableFlags);
            // LD_A_addr(wCurPartyMon);
            // LD_C_A;
            // LD_B(SET_FLAG);
            // PREDEF(pSmallFarFlagAction);
            SmallFarFlagAction_Conv(wram->wEvolvableFlags, wram->wCurPartyMon, SET_FLAG);
            // POP_AF;
            // LD_addr_A(wCurPartyLevel);
            wram->wCurPartyLevel = lvl;
        }

    next_mon:
        // LD_A_addr(wPartyCount);
        // LD_B_A;
        // LD_A_addr(wCurPartyMon);
        // INC_A;
        // CP_A_B;
        // IF_Z goto done;
        if(wram->wCurPartyMon + 1 == wram->wPartyCount)
            break;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon++;
        // LD_A(MON_SPECIES);
        // CALL(aGetPartyParamLocation);
        // LD_B_H;
        // LD_C_L;
        bc = wram->wPartyMon + wram->wCurPartyMon;
        // JP(mGiveExperiencePoints_loop);
    }

done:
    // JP(mResetBattleParticipants);
    return ResetBattleParticipants();
}

void BoostExp(void){
//  Multiply experience by 1.5x
    PUSH_BC;
//  load experience value
    LDH_A_addr(hProduct + 2);
    LD_B_A;
    LDH_A_addr(hProduct + 3);
    LD_C_A;
//  halve it
    SRL_B;
    RR_C;
//  add it back to the whole exp value
    ADD_A_C;
    LDH_addr_A(hProduct + 3);
    LDH_A_addr(hProduct + 2);
    ADC_A_B;
    LDH_addr_A(hProduct + 2);
    POP_BC;
    RET;

}

uint16_t BoostExp_Conv(uint16_t exp){
//  Multiply experience by 1.5x
    // PUSH_BC;
//  load experience value
    // LDH_A_addr(hProduct + 2);
    // LD_B_A;
    // LDH_A_addr(hProduct + 3);
    // LD_C_A;
//  halve it
    // SRL_B;
    // RR_C;
//  add it back to the whole exp value
    // ADD_A_C;
    // LDH_addr_A(hProduct + 3);
    // LDH_A_addr(hProduct + 2);
    // ADC_A_B;
    // LDH_addr_A(hProduct + 2);
    // POP_BC;
    // RET;
    return exp + (exp / 2);
}

static void Text_MonGainedExpPoint_Func(struct TextCmdState* state){
    // LD_HL(mExpPointsText);
    // LD_A_addr(wStringBuffer2 + 2);  // IsTradedMon
    // AND_A_A;
    // RET_Z ;

    // LD_HL(mBoostedExpPointsText);
    // RET;
    state->hl = (wram->wStringBuffer2[2] == 0)? ExpPointsText: BoostedExpPointsText;
}

const txt_cmd_s Text_MonGainedExpPoint[] = {
    text_far(v_Text_Gained)
    text_asm(Text_MonGainedExpPoint_Func)
};

const txt_cmd_s BoostedExpPointsText[] = {
    text_far(v_BoostedExpPointsText)
    text_end
};

const txt_cmd_s ExpPointsText[] = {
    text_far(v_ExpPointsText)
    text_end
};

static void AnimateExpBar_PlayExpBarSound(void){
    // PUSH_BC;
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_DE(SFX_EXP_BAR);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_EXP_BAR);
    // LD_C(10);
    // CALL(aDelayFrames);
    DelayFrames_Conv(10);
    // POP_BC;
    // RET;
}

static void AnimateExpBar_LoopBarAnimation(uint8_t b, uint8_t c){
    // LD_D(3);
    uint8_t d = 3;
    // DEC_B;
    --b;

    do {
    // anim_loop:
        // INC_B;
        ++b;
        // PUSH_BC;
        // PUSH_DE;
        // hlcoord(17, 11, wTilemap);
        // CALL(aPlaceExpBar);
        PlaceExpBar_Conv(coord(17, 11, wram->wTilemap), b);
        // POP_DE;
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // LD_C_D;
        // CALL(aDelayFrames);
        DelayFrames_Conv(d);
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
        // POP_BC;
        // LD_A_C;
        // CP_A_B;
        // IF_Z goto end_animation;
        if(c == b)
            break;
        // INC_B;
        ++b;
        // PUSH_BC;
        // PUSH_DE;
        // hlcoord(17, 11, wTilemap);
        // CALL(aPlaceExpBar);
        PlaceExpBar_Conv(coord(17, 11, wram->wTilemap), b);
        // POP_DE;
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x1;
        // LD_C_D;
        // CALL(aDelayFrames);
        DelayFrames_Conv(d);
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
        // DEC_D;
        // IF_NZ goto min_number_of_frames;
        // LD_D(1);
        if(--d == 0)
            d = 1;

    // min_number_of_frames:
        // POP_BC;
        // LD_A_C;
        // CP_A_B;
        // IF_NZ goto anim_loop;
    } while(c != b);

// end_animation:
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // RET;
}

void AnimateExpBar(uint16_t exp){
    // PUSH_BC;

    // LD_HL(wCurPartyMon);
    // LD_A_addr(wCurBattleMon);
    // CP_A_hl;
    // JP_NZ (mAnimateExpBar_finish);
    if(wram->wCurPartyMon != wram->wCurBattleMon)
        return;

    // LD_A_addr(wBattleMonLevel);
    // CP_A(MAX_LEVEL);
    // JP_NC (mAnimateExpBar_finish);
    if(wram->wBattleMon.level >= MAX_LEVEL)
        return;

    // LDH_A_addr(hProduct + 3);
    // LD_addr_A(wExperienceGained + 2);
    // PUSH_AF;
    // LDH_A_addr(hProduct + 2);
    // LD_addr_A(wExperienceGained + 1);
    // PUSH_AF;
    // XOR_A_A;
    // LD_addr_A(wExperienceGained);
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // PREDEF(pCopyMonToTempMon);
    CopyMonToTempMon_Conv();
    // LD_A_addr(wTempMonLevel);
    // LD_B_A;
    // LD_E_A;
    uint8_t e = wram->wTempMon.mon.level;
    // PUSH_DE;
    // LD_DE(wTempMonExp + 2);
    // CALL(aCalcExpBar);
    uint8_t b = CalcExpBar_Conv(wram->wTempMon.mon.level, wram->wTempMon.mon.exp + 2);
    // PUSH_BC;
    uint32_t bExp = (wram->wTempMon.mon.exp[0] << 16) | (wram->wTempMon.mon.exp[1] << 8) | (wram->wTempMon.mon.exp[2]);
    // LD_HL(wTempMonExp + 2);
    // LD_A_addr(wExperienceGained + 2);
    // ADD_A_hl;
    // LD_hld_A;
    // LD_A_addr(wExperienceGained + 1);
    // ADC_A_hl;
    // LD_hld_A;
    // IF_NC goto NoOverflow;
    // INC_hl;
    // IF_NZ goto NoOverflow;
    if(bExp + exp > 0xffffff){
        // LD_A(0xff);
        // LD_hli_A;
        // LD_hli_A;
        // LD_hl_A;
        bExp = 0xffffff;
    }
    else {
        bExp += exp;
    }

    wram->wTempMon.mon.exp[2] = LOW(bExp);
    wram->wTempMon.mon.exp[1] = HIGH(bExp);
    wram->wTempMon.mon.exp[0] = HIGH(bExp >> 8);

// NoOverflow:
    // LD_D(MAX_LEVEL);
    // CALLFAR(aCalcExpAtLevel);
    uint32_t maxExp = CalcExpAtLevel_Conv(MAX_LEVEL);
    // LDH_A_addr(hProduct + 1);
    // LD_B_A;
    // LDH_A_addr(hProduct + 2);
    // LD_C_A;
    // LDH_A_addr(hProduct + 3);
    // LD_D_A;
    // LD_HL(wTempMonExp + 2);
    // LD_A_hld;
    // SUB_A_D;
    // LD_A_hld;
    // SBC_A_C;
    // LD_A_hl;
    // SBC_A_B;
    // IF_C goto AlreadyAtMaxExp;
    if(bExp > maxExp){
        // LD_A_B;
        // LD_hli_A;
        // LD_A_C;
        // LD_hli_A;
        // LD_A_D;
        // LD_hld_A;
        bExp = maxExp; 
    }

    wram->wTempMon.mon.exp[2] = LOW(bExp);
    wram->wTempMon.mon.exp[1] = HIGH(bExp);
    wram->wTempMon.mon.exp[0] = HIGH(bExp >> 8);

// AlreadyAtMaxExp:
    // CALLFAR(aCalcLevel);
    // LD_A_D;
    uint8_t d = CalcLevel_Conv(&wram->wTempMon);
    // POP_BC;
    // POP_DE;
    // LD_D_A;
    // CP_A_E;
    // IF_NC goto LoopLevels;
    if(d < e){
        // LD_A_E;
        // LD_D_A;
        d = e;
    }

    while(e < MAX_LEVEL && e != d){
    // LoopLevels:
        // LD_A_E;
        // CP_A(MAX_LEVEL);
        // IF_NC goto FinishExpBar;
        // CP_A_D;
        // IF_Z goto FinishExpBar;
        // INC_A;
        // LD_addr_A(wTempMonLevel);
        wram->wTempMon.mon.level = e + 1;
        // LD_addr_A(wCurPartyLevel);
        wram->wCurPartyLevel = e + 1;
        // LD_addr_A(wBattleMonLevel);
        wram->wBattleMon.level = e + 1;
        // PUSH_DE;
        // CALL(aAnimateExpBar_PlayExpBarSound);
        AnimateExpBar_PlayExpBarSound();
        // LD_C(0x40);
        // CALL(aAnimateExpBar_LoopBarAnimation);
        AnimateExpBar_LoopBarAnimation(b, 0x40);
        // CALL(aPrintPlayerHUD);
        PrintPlayerHUD();
        // LD_HL(wBattleMonNickname);
        // LD_DE(wStringBuffer1);
        // LD_BC(MON_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(wram->wStringBuffer1, wram->wBattleMonNickname, MON_NAME_LENGTH);
        // CALL(aTerminateExpBarSound);
        TerminateExpBarSound_Conv();
        // LD_DE(SFX_HIT_END_OF_EXP_BAR);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_HIT_END_OF_EXP_BAR);
        // FARCALL(aAnimateEndOfExpBar);
        AnimateEndOfExpBar_Conv();
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // LD_HL(mBattleText_StringBuffer1GrewToLevel);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(BattleText_StringBuffer1GrewToLevel);
        // POP_DE;
        // INC_E;
        e++;
        // LD_B(0x0);
        b = 0x0;
        // goto LoopLevels;
    }

// FinishExpBar:
    // PUSH_BC;
    // LD_B_D;
    // LD_DE(wTempMonExp + 2);
    // CALL(aCalcExpBar);
    uint8_t c = CalcExpBar_Conv(d, wram->wTempMon.mon.exp + 2);
    // LD_A_B;
    // POP_BC;
    // LD_C_A;
    // CALL(aAnimateExpBar_PlayExpBarSound);
    AnimateExpBar_PlayExpBarSound();
    // CALL(aAnimateExpBar_LoopBarAnimation);
    AnimateExpBar_LoopBarAnimation(b, c);
    // CALL(aTerminateExpBarSound);
    TerminateExpBarSound_Conv();
    // POP_AF;
    // LDH_addr_A(hProduct + 2);
    // POP_AF;
    // LDH_addr_A(hProduct + 3);

// finish:
    // POP_BC;
    // RET;
}

void SendOutMonText(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;
    if(wram->wLinkMode != 0) {

    //  If we're in a LinkBattle print just "Go <PlayerMon>"
    //  unless DoBattle already set [wBattleHasJustStarted]
        // LD_HL(mGoMonText);
        // LD_A_addr(wBattleHasJustStarted);
        // AND_A_A;
        // IF_NZ goto skip_to_textbox;
        if(wram->wBattleHasJustStarted != 0)
            return BattleTextbox_Conv2(GoMonText);
    }


// not_linked:
//  Depending on the HP of the enemy mon, the game prints a different text
    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // OR_A_hl;
    // LD_HL(mGoMonText);
    // IF_Z goto skip_to_textbox;
    if(wram->wEnemyMon.hp == 0) {
        return BattleTextbox_Conv2(GoMonText);
    }

// compute enemy health remaining as a percentage
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LD_HL(wEnemyMonHP);
    // LD_A_hli;
    // LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch);
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hl;
    // LD_addr_A(wEnemyHPAtTimeOfPlayerSwitch + 1);
    wram->wEnemyHPAtTimeOfPlayerSwitch = wram->wEnemyMon.hp;
    uint16_t hp = (LOW(wram->wEnemyMon.hp) << 8) | HIGH(wram->wEnemyMon.hp);
    uint16_t max_hp = (LOW(wram->wEnemyMon.maxHP) << 8) | HIGH(wram->wEnemyMon.maxHP);
    // LDH_addr_A(hMultiplicand + 2);
    // LD_A(25);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    uint16_t hp_a = (hp * 25);
    // LD_HL(wEnemyMonMaxHP);
    // LD_A_hli;
    // LD_B_hl;
    // SRL_A;
    // RR_B;
    // SRL_A;
    // RR_B;
    // LD_A_B;
    uint16_t hp_b = (max_hp >> 2);
    // LD_B(4);
    // LDH_addr_A(hDivisor);
    // CALL(aDivide);
    uint16_t hp_p = 100;
    if(hp_b != 0)
        hp_p = hp_a / hp_b;

    // LDH_A_addr(hQuotient + 3);
    // LD_HL(mGoMonText);
    // CP_A(70);
    // IF_NC goto skip_to_textbox;
    if(hp_p >= 70) { // >= 70%
        return BattleTextbox_Conv2(GoMonText);
    }

    // LD_HL(mDoItMonText);
    // CP_A(40);
    // IF_NC goto skip_to_textbox;
    else if(hp_p >= 40) { // 40-69%
        return BattleTextbox_Conv2(DoItMonText);
    }

    // LD_HL(mGoForItMonText);
    // CP_A(10);
    // IF_NC goto skip_to_textbox;
    else if(hp_p >= 10) { // 10-39%
        return BattleTextbox_Conv2(GoForItMonText);
    }

    // LD_HL(mYourFoesWeakGetmMonText);

    else { // 1-9%
        return BattleTextbox_Conv2(YourFoesWeakGetmMonText);
    }

// skip_to_textbox:
    // JP(mBattleTextbox);

}

const txt_cmd_s GoMonText[] = {
    text_far(v_GoMonText)
    text_asm(PrepareBattleMonNicknameText_Conv)
    // JR(mPrepareBattleMonNicknameText);
};

const txt_cmd_s DoItMonText[] = {
    text_far(v_DoItMonText)
    text_asm(PrepareBattleMonNicknameText_Conv)
    // JR(mPrepareBattleMonNicknameText);
};

const txt_cmd_s GoForItMonText[] = {
    text_far(v_GoForItMonText)
    text_asm(PrepareBattleMonNicknameText_Conv)
    // JR(mPrepareBattleMonNicknameText);
};

const txt_cmd_s YourFoesWeakGetmMonText[] = {
    text_far(v_YourFoesWeakGetmMonText)
    text_asm(PrepareBattleMonNicknameText_Conv)
    // JR(mPrepareBattleMonNicknameText);
};

void PrepareBattleMonNicknameText(void){
    LD_HL(mBattleMonNicknameText);
    RET;

}

void PrepareBattleMonNicknameText_Conv(struct TextCmdState* state){
    // LD_HL(mBattleMonNicknameText);
    // RET;
    state->hl = BattleMonNicknameText;
}

const txt_cmd_s BattleMonNicknameText[] = {
    text_far(v_BattleMonNicknameText)
    text_end
};

static void WithdrawMonText_WithdrawMonText_Function(struct TextCmdState* state);
const txt_cmd_s WithdrawMonText_WithdrawMonText[] = {
    text_far(v_BattleMonNickCommaText)
    text_asm(WithdrawMonText_WithdrawMonText_Function)
};

static void WithdrawMonText_WithdrawMonText_Function(struct TextCmdState* state){
//  Depending on the HP lost since the enemy mon was sent out, the game prints a different text
    // PUSH_DE;
    // PUSH_BC;
// compute enemy health lost as a percentage
    // LD_HL(wEnemyMonHP + 1);
    // LD_DE(wEnemyHPAtTimeOfPlayerSwitch + 1);
    // LD_B_hl;
    // DEC_HL;
    // LD_A_de;
    // SUB_A_B;
    // LDH_addr_A(hMultiplicand + 2);
    // DEC_DE;
    // LD_B_hl;
    // LD_A_de;
    // SBC_A_B;
    // LDH_addr_A(hMultiplicand + 1);
    uint16_t hpLost = BigEndianToNative16(wram->wEnemyHPAtTimeOfPlayerSwitch) - BigEndianToNative16(wram->wEnemyMon.hp);
    // LD_A(25);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    // LD_HL(wEnemyMonMaxHP);
    // LD_A_hli;
    // LD_B_hl;
    // SRL_A;
    // RR_B;
    // SRL_A;
    // RR_B;
    // LD_A_B;
    // LD_B(4);
    // LDH_addr_A(hDivisor);
    // CALL(aDivide);
    uint16_t n = (hpLost * 25) / (BigEndianToNative16(wram->wEnemyMon.maxHP) >> 2);
    // POP_BC;
    // POP_DE;
    // LDH_A_addr(hQuotient + 3);
    // LD_HL(mThatsEnoughComeBackText);
    // AND_A_A;
    // RET_Z ;
    if(n == 0){
        state->hl = ThatsEnoughComeBackText;
        return;
    }

    // LD_HL(mComeBackText);
    // CP_A(30);
    // RET_C ;
    else if(n < 30){
        state->hl = ComeBackText;
        return;
    }

    // LD_HL(mOKComeBackText);
    // CP_A(70);
    // RET_C ;
    else if(n < 70){
        state->hl = OKComeBackText;
        return;
    }

    else {
        // LD_HL(mGoodComeBackText);
        state->hl = GoodComeBackText;
        // RET;
        return;
    }
}

void WithdrawMonText(void){
    // LD_HL(mWithdrawMonText_WithdrawMonText);
    // JP(mBattleTextbox);
    return BattleTextbox_Conv2(WithdrawMonText_WithdrawMonText);
}

const txt_cmd_s ThatsEnoughComeBackText[] = {
    text_far(v_ThatsEnoughComeBackText)
    text_end
};

const txt_cmd_s OKComeBackText[] = {
    text_far(v_OKComeBackText)
    text_end
};

const txt_cmd_s GoodComeBackText[] = {
    text_far(v_GoodComeBackText)
    text_end
};

void TextJump_ComeBack(void){
//  //  unreferenced
    LD_HL(mComeBackText);
    RET;

}

const txt_cmd_s ComeBackText[] = {
    text_far(v_ComeBackText)
    text_end
};

void HandleSafariAngerEatingStatus(void){
//  //  unreferenced
    LD_HL(wSafariMonEating);
    LD_A_hl;
    AND_A_A;
    IF_Z goto angry;
    DEC_hl;
    LD_HL(mBattleText_WildMonIsEating);
    goto finish;


angry:
    DEC_HL;
    //assert ['wSafariMonEating - 1 == wSafariMonAngerCount'];
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    LD_HL(mBattleText_WildMonIsAngry);
    IF_NZ goto finish;
    PUSH_HL;
    LD_A_addr(wEnemyMonSpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A_addr(wBaseCatchRate);
    LD_addr_A(wEnemyMonCatchRate);
    POP_HL;


finish:
    PUSH_HL;
    CALL(aSafeLoadTempTilemapToTilemap);
    POP_HL;
    JP(mStdBattleTextbox);

}

void FillInExpBar(void){
    PUSH_HL;
    CALL(aCalcExpBar);
    POP_HL;
    LD_DE(7);
    ADD_HL_DE;
    JP(mPlaceExpBar);

}

void FillInExpBar_Conv(uint8_t* hl, uint8_t b, const uint8_t* de) {
    uint8_t pct = CalcExpBar_Conv(b, de);
    PlaceExpBar_Conv(hl + 7, pct);
}

void CalcExpBar(void){
//  Calculate the percent exp between this level and the next
//  Level in b
    PUSH_DE;
    LD_D_B;
    PUSH_DE;
    CALLFAR(aCalcExpAtLevel);
    POP_DE;
//  exp at current level gets pushed to the stack
    LD_HL(hMultiplicand);
    LD_A_hli;
    PUSH_AF;
    LD_A_hli;
    PUSH_AF;
    LD_A_hl;
    PUSH_AF;
//  next level
    INC_D;
    CALLFAR(aCalcExpAtLevel);
//  back up the next level exp, and subtract the two levels
    LD_HL(hMultiplicand + 2);
    LD_A_hl;
    LDH_addr_A(hMathBuffer + 2);
    POP_BC;
    SUB_A_B;
    LD_hld_A;
    LD_A_hl;
    LDH_addr_A(hMathBuffer + 1);
    POP_BC;
    SBC_A_B;
    LD_hld_A;
    LD_A_hl;
    LDH_addr_A(hMathBuffer);
    POP_BC;
    SBC_A_B;
    LD_hl_A;
    POP_DE;

    LD_HL(hMultiplicand + 1);
    LD_A_hli;
    PUSH_AF;
    LD_A_hl;
    PUSH_AF;

//  get the amount of exp remaining to the next level
    LD_A_de;
    DEC_DE;
    LD_C_A;
    LDH_A_addr(hMathBuffer + 2);
    SUB_A_C;
    LD_hld_A;
    LD_A_de;
    DEC_DE;
    LD_B_A;
    LDH_A_addr(hMathBuffer + 1);
    SBC_A_B;
    LD_hld_A;
    LD_A_de;
    LD_C_A;
    LDH_A_addr(hMathBuffer);
    SBC_A_C;
    LD_hld_A;
    XOR_A_A;
    LD_hl_A;
    LD_A(64);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    POP_AF;
    LD_C_A;
    POP_AF;
    LD_B_A;

loop:
    LD_A_B;
    AND_A_A;
    IF_Z goto done;
    SRL_B;
    RR_C;
    LD_HL(hProduct);
    SRL_hl;
    INC_HL;
    RR_hl;
    INC_HL;
    RR_hl;
    INC_HL;
    RR_hl;
    goto loop;


done:
    LD_A_C;
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 3);
    LD_B_A;
    LD_A(0x40);
    SUB_A_B;
    LD_B_A;
    RET;

}

//  Calculate the percent exp between this level and the next
uint8_t CalcExpBar_Conv(uint8_t b, const uint8_t* de){
//  Level in b
    // PUSH_DE;
    // LD_D_B;
    // PUSH_DE;
    // CALLFAR(aCalcExpAtLevel);
    uint32_t exp = CalcExpAtLevel_Conv(b);
    // POP_DE;
//  exp at current level gets pushed to the stack
    // LD_HL(hMultiplicand);
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hl;
    // PUSH_AF;
//  next level
    // INC_D;
    // CALLFAR(aCalcExpAtLevel);
    uint32_t next = CalcExpAtLevel_Conv(b + 1);
//  back up the next level exp, and subtract the two levels
    // LD_HL(hMultiplicand + 2);
    // LD_A_hl;
    // LDH_addr_A(hMathBuffer + 2);
    // POP_BC;
    // SUB_A_B;
    // LD_hld_A;
    // LD_A_hl;
    // LDH_addr_A(hMathBuffer + 1);
    // POP_BC;
    // SBC_A_B;
    // LD_hld_A;
    // LD_A_hl;
    // LDH_addr_A(hMathBuffer);
    // POP_BC;
    // SBC_A_B;
    // LD_hl_A;
    // POP_DE;

    // LD_HL(hMultiplicand + 1);
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hl;
    // PUSH_AF;
    uint32_t l = next - exp;

//  get the amount of exp remaining to the next level
    uint32_t cur_exp = (de[0])
        + (de[-1] << 8)
        + (de[-2] << 16);

    uint32_t h = cur_exp - exp;
    // LD_A_de;
    // DEC_DE;
    // LD_C_A;
    // LDH_A_addr(hMathBuffer + 2);
    // SUB_A_C;
    // LD_hld_A;
    // LD_A_de;
    // DEC_DE;
    // LD_B_A;
    // LDH_A_addr(hMathBuffer + 1);
    // SBC_A_B;
    // LD_hld_A;
    // LD_A_de;
    // LD_C_A;
    // LDH_A_addr(hMathBuffer);
    // SBC_A_C;
    // LD_hld_A;
    // XOR_A_A;
    // LD_hl_A;
    // LD_A(64);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    // POP_AF;
    // LD_C_A;
    // POP_AF;
    // LD_B_A;

// loop:
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto done;
    // SRL_B;
    // RR_C;
    // LD_HL(hProduct);
    // SRL_hl;
    // INC_HL;
    // RR_hl;
    // INC_HL;
    // RR_hl;
    // INC_HL;
    // RR_hl;
    // goto loop;


// done:
    // LD_A_C;
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    // LDH_A_addr(hQuotient + 3);
    // LD_B_A;
    // LD_A(0x40);
    // SUB_A_B;
    // LD_B_A;
    // RET;

    return (uint8_t)((64 * h) / l);
}

void PlaceExpBar(void){
    LD_C(0x8);  // number of tiles

loop1:
    LD_A_B;
    SUB_A(0x8);
    IF_C goto next;
    LD_B_A;
    LD_A(0x6a);  // full bar
    LD_hld_A;
    DEC_C;
    IF_Z goto finish;
    goto loop1;


next:
    ADD_A(0x8);
    IF_Z goto loop2;
    ADD_A(0x54);  // tile to the left of small exp bar tile
    goto skip;


loop2:
    LD_A(0x62);  // empty bar


skip:
    LD_hld_A;
    LD_A(0x62);  // empty bar
    DEC_C;
    IF_NZ goto loop2;


finish:
    RET;

}

void PlaceExpBar_Conv(uint8_t* hl, uint8_t b){
    // LD_C(0x8);  // number of tiles
    uint8_t c = 0x8;

    while(1)
    {
    // loop1:
        // LD_A_B;
        // SUB_A(0x8);
        // IF_C goto next;
        if(b < 0x8)
            break;
        // LD_B_A;
        b -= 0x8;
        // LD_A(0x6a);  // full bar
        // LD_hld_A;
        *(hl--) = 0x6a;
        // DEC_C;
        // IF_Z goto finish;
        if(--c == 0)
            return;
        // goto loop1;
    }


// next:
    // ADD_A(0x8);
    // IF_Z goto loop2;
    uint8_t a;
    if(b != 0x0) {
        // ADD_A(0x54);  // tile to the left of small exp bar tile
        a = b + 0x54;
    }
    else {
        a = 0x62;
    }
    // goto skip;


    do {
    // loop2:
        // LD_A(0x62);  // empty bar

    // skip:
        // LD_hld_A;
        *(hl--) = a;
        // LD_A(0x62);  // empty bar
        a = 0x62;
        // DEC_C;
        // IF_NZ goto loop2;
    } while(--c != 0);


// finish:
    // RET;
}

void GetBattleMonBackpic(void){
    // LD_A_addr(wPlayerSubStatus4);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // LD_HL(mBattleAnimCmd_RaiseSub);
    // JR_NZ (mGetBattleMonBackpic_DoAnim);  // substitute
    if(bit_test(wram->wPlayerSubStatus4, SUBSTATUS_SUBSTITUTE)) {
        return GetBattleMonBackpic_DoAnim_Conv(BattleAnimCmd_RaiseSub);
    }

    return DropPlayerSub();
}

void DropPlayerSub(void){
    // LD_A_addr(wPlayerMinimized);
    // AND_A_A;
    // LD_HL(mBattleAnimCmd_MinimizeOpp);
    // JR_NZ (mGetBattleMonBackpic_DoAnim);
    if(wram->wPlayerMinimized != 0)
        return GetBattleMonBackpic_DoAnim_Conv(BattleAnimCmd_MinimizeOpp);
    // LD_A_addr(wCurPartySpecies);
    // PUSH_AF;
    species_t species = wram->wCurPartySpecies;
    // LD_A_addr(wBattleMonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wBattleMon.species;
    // LD_HL(wBattleMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter_Conv(wram->wBattleMon.dvs);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // PREDEF(pGetMonBackpic);
    GetMonBackpic_Conv(vram->vTiles2 + LEN_2BPP_TILE * 0x31, wram->wCurPartySpecies);
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // RET;
}

void GetBattleMonBackpic_DoAnim(void){
    LDH_A_addr(hBattleTurn);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBattleTurn);
    LD_A(BANK(aBattleAnimCommands));
    RST(aFarCall);
    POP_AF;
    LDH_addr_A(hBattleTurn);
    RET;

}

void GetBattleMonBackpic_DoAnim_Conv(void (*hl)(void)){
    // LDH_A_addr(hBattleTurn);
    // PUSH_AF;
    uint8_t turn = hram->hBattleTurn;
    // XOR_A_A;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = 0;
    // LD_A(BANK(aBattleAnimCommands));
    // RST(aFarCall);
    hl();
    // POP_AF;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = turn;
    // RET;
}

void GetEnemyMonFrontpic(void){
    // LD_A_addr(wEnemySubStatus4);
    // BIT_A(SUBSTATUS_SUBSTITUTE);
    // LD_HL(mBattleAnimCmd_RaiseSub);
    // JR_NZ (mGetEnemyMonFrontpic_DoAnim);
    if(bit_test(wram->wEnemySubStatus4, SUBSTATUS_SUBSTITUTE)) {
        return GetEnemyMonFrontpic_DoAnim_Conv(BattleAnimCmd_RaiseSub);
    }

    return DropEnemySub();
}

void DropEnemySub(void){
    // LD_A_addr(wEnemyMinimized);
    // AND_A_A;
    // LD_HL(mBattleAnimCmd_MinimizeOpp);
    // JR_NZ (mGetEnemyMonFrontpic_DoAnim);
    if(wram->wEnemyMinimized != 0)
        return GetEnemyMonFrontpic_DoAnim_Conv(BattleAnimCmd_MinimizeOpp);

    // LD_A_addr(wCurPartySpecies);
    // PUSH_AF;
    species_t species = wram->wCurPartySpecies;
    // LD_A_addr(wEnemyMonSpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wEnemyMon.species;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wEnemyMon.species;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wEnemyMon.species);
    // LD_HL(wEnemyMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter_Conv(wram->wEnemyMon.dvs);
    // LD_DE(vTiles2);
    // PREDEF(pGetAnimatedFrontpic);
    GetAnimatedFrontpic_Conv(vram->vTiles2, 0);
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // RET;
}

void GetEnemyMonFrontpic_DoAnim(void){
    LDH_A_addr(hBattleTurn);
    PUSH_AF;
    CALL(aSetEnemyTurn);
    LD_A(BANK(aBattleAnimCommands));
    RST(aFarCall);
    POP_AF;
    LDH_addr_A(hBattleTurn);
    RET;

}

void GetEnemyMonFrontpic_DoAnim_Conv(void (*hl)(void)){
    // LDH_A_addr(hBattleTurn);
    // PUSH_AF;
    uint8_t turn = hram->hBattleTurn;
    // CALL(aSetEnemyTurn);
    SetEnemyTurn_Conv();
    // LD_A(BANK(aBattleAnimCommands));
    // RST(aFarCall);
    hl();
    // POP_AF;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = turn;
    // RET;
}

void StartBattle(void){
//  This check prevents you from entering a battle without any Pokemon.
//  Those using walk-through-walls to bypass getting a Pokemon experience
//  the effects of this check.
    PEEK("");
    LD_A_addr(wPartyCount);
    AND_A_A;
    RET_Z ;

    LD_A_addr(wTimeOfDayPal);
    PUSH_AF;
    // CALL(aBattleIntro);
    BattleIntro();
    {
        bank_push(BANK(aDoBattle));
        CALL(aDoBattle);
        bank_pop;
    }
    {
        bank_push(BANK(aExitBattle));
        CALL(aExitBattle);
        bank_pop;
    }
    POP_AF;
    LD_addr_A(wTimeOfDayPal);
    SCF;
    RET;

}

bool StartBattle_Conv(void){
//  This check prevents you from entering a battle without any Pokemon.
//  Those using walk-through-walls to bypass getting a Pokemon experience
//  the effects of this check.
    PEEK("");
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(wram->wPartyCount == 0)
        return false;

    // LD_A_addr(wTimeOfDayPal);
    // PUSH_AF;
    uint8_t pal = wram->wTimeOfDayPal;
    // CALL(aBattleIntro);
    BattleIntro();
    // CALL(aDoBattle);
    DoBattle();
    // CALL(aExitBattle);
    ExitBattle();
    // POP_AF;
    // LD_addr_A(wTimeOfDayPal);
    wram->wTimeOfDayPal = pal;
    // SCF;
    // RET;
    return true;
}

void CallDoBattle(void){
//  //  unreferenced
    CALL(aDoBattle);
    RET;

}

void BattleIntro(void){
    // FARCALL(aStubbedTrainerRankings_Battles);  // mobile
    StubbedTrainerRankings_Battles();
    // CALL(aLoadTrainerOrWildMonPic);
    LoadTrainerOrWildMonPic();
    // XOR_A_A;
    // LD_addr_A(wTempBattleMonSpecies);
    wram->wTempBattleMonSpecies = 0;
    // LD_addr_A(wBattleMenuCursorPosition);
    wram->wBattleMenuCursorPosition = 0;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = FALSE;
    // FARCALL(aPlayBattleMusic);
    PlayBattleMusic_Conv();
    // FARCALL(aShowLinkBattleParticipants);
    ShowLinkBattleParticipants_Conv();
    // FARCALL(aFindFirstAliveMonAndStartBattle);
    FindFirstAliveMonAndStartBattle();
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates_Conv();
    // FARCALL(aClearBattleRAM);
    ClearBattleRAM_Conv();
    // CALL(aInitEnemy);
    InitEnemy();
    // CALL(aBackUpBGMap2);
    BackUpBGMap2();
    // LD_B(SCGB_BATTLE_GRAYSCALE);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_BATTLE_GRAYSCALE);
    // LD_HL(rLCDC);
    // RES_hl(rLCDC_WINDOW_TILEMAP);  // select vBGMap0/vBGMap2
    gb_write(rLCDC, gb_read(rLCDC) & ((1 << rLCDC_WINDOW_TILEMAP) ^ 0xff));
    // CALL(aInitBattleDisplay);
    InitBattleDisplay();
    // CALL(aBattleStartMessage);
    BattleStartMessage();
    // LD_HL(rLCDC);
    // SET_hl(rLCDC_WINDOW_TILEMAP);  // select vBGMap1/vBGMap3
    gb_write(rLCDC, gb_read(rLCDC) | (1 << rLCDC_WINDOW_TILEMAP));
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aEmptyBattleTextbox);
    EmptyBattleTextbox();
    // hlcoord(9, 7, wTilemap);
    // LD_BC((5 << 8) | 11);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(9, 7, wram->wTilemap), 11, 5);
    // hlcoord(1, 0, wTilemap);
    // LD_BC((4 << 8) | 10);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 0, wram->wTilemap), 10, 4);
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // LD_A_addr(wBattleMode);
    // CP_A(WILD_BATTLE);
    // CALL_Z (aUpdateEnemyHUD);
    if(wram->wBattleMode == WILD_BATTLE)
        UpdateEnemyHUD();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // RET;
}

void LoadTrainerOrWildMonPic(void){
    // LD_A_addr(wOtherTrainerClass);
    // AND_A_A;
    // IF_NZ goto Trainer;
    if(wram->wOtherTrainerClass == 0) {
        // LD_A_addr(wTempWildMonSpecies);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = wram->wTempWildMonSpecies;
        wram->wTempEnemyMonSpecies = wram->wTempWildMonSpecies;
    }
    else {
    // Trainer:
        // LD_addr_A(wTempEnemyMonSpecies);
        wram->wTempEnemyMonSpecies = wram->wOtherTrainerClass;
        // RET;
    }
}

void InitEnemy(void){
    // LD_A_addr(wOtherTrainerClass);
    // AND_A_A;
    // JP_NZ (mInitEnemyTrainer);  // trainer
    // JP(mInitEnemyWildmon);  // wild
    if(wram->wOtherTrainerClass != 0) {
        // REG_A = wram->wOtherTrainerClass;
        // CALL(aInitEnemyTrainer);
        return InitEnemyTrainer_Conv(wram->wOtherTrainerClass);
        // RET;
    }
    return InitEnemyWildmon();

}

void BackUpBGMap2(void){
    PEEK("");
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awDecompressScratch));
    // LDH_addr_A(rSVBK);
    wbank_push(MBANK(awDecompressScratch));
    // LD_HL(wDecompressScratch);
    // LD_BC(0x40 * LEN_2BPP_TILE);  // vBGMap3 - vBGMap2
    // LD_A(0x2);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wDecompressScratch, 0x40 * LEN_2BPP_TILE, 0x2);
    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_DE(wDecompressScratch);
    // hlbgcoord(0, 0, vBGMap0);  // vBGMap2
    // LD_BC((BANK(aBackUpBGMap2) << 8) | 0x40);
    // CALL(aRequest2bpp);
    // POP_AF;
    CopyBytes_Conv2(bgcoord(0, 0, vram->vBGMap2), wram->wDecompressScratch, 0x40 * LEN_2BPP_TILE);
    // LDH_addr_A(rVBK);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    wbank_pop;
}

void InitEnemyTrainer(void){
    PEEK("");
    LD_addr_A(wTrainerClass);
    FARCALL(aStubbedTrainerRankings_TrainerBattles);
    XOR_A_A;
    LD_addr_A(wTempEnemyMonSpecies);
    CALLFAR(aGetTrainerAttributes);
    CALLFAR(aReadTrainerParty);

// RIVAL1's first mon has no held item
    LD_A_addr(wTrainerClass);
    CP_A(RIVAL1);
    IF_NZ goto ok;
    XOR_A_A;
    LD_addr_A(wOTPartyMon1Item);


ok:
    LD_DE(vTiles2);
    CALLFAR(aGetTrainerPic);
    XOR_A_A;
    LDH_addr_A(hGraphicStartTile);
    DEC_A;
    LD_addr_A(wEnemyItemState);
    hlcoord(12, 0, wTilemap);
    LD_BC((7 << 8) | 7);
    PREDEF(pPlaceGraphic);
    LD_A(-1);
    LD_addr_A(wCurOTMon);
    LD_A(TRAINER_BATTLE);
    LD_addr_A(wBattleMode);

    CALL(aIsGymLeader);
    IF_NC goto done;
    XOR_A_A;
    LD_addr_A(wCurPartyMon);
    LD_A_addr(wPartyCount);
    LD_B_A;

partyloop:
    PUSH_BC;
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    OR_A_hl;
    IF_Z goto skipfaintedmon;
    LD_C(HAPPINESS_GYMBATTLE);
    CALLFAR(aChangeHappiness);

skipfaintedmon:
    POP_BC;
    DEC_B;
    IF_Z goto done;
    LD_HL(wCurPartyMon);
    INC_hl;
    goto partyloop;

done:
    RET;

}

void InitEnemyTrainer_Conv(uint8_t tclass){
    PEEK("");
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = tclass;
    // FARCALL(aStubbedTrainerRankings_TrainerBattles);
    StubbedTrainerRankings_TrainerBattles();
    // XOR_A_A;
    // LD_addr_A(wTempEnemyMonSpecies);
    wram->wTempEnemyMonSpecies = 0;
    // CALLFAR(aGetTrainerAttributes);
    GetTrainerAttributes_Conv(tclass);
    // CALLFAR(aReadTrainerParty);
    ReadTrainerParty();

// RIVAL1's first mon has no held item
    // LD_A_addr(wTrainerClass);
    // CP_A(RIVAL1);
    // IF_NZ goto ok;
    if(tclass == RIVAL1) {
        // XOR_A_A;
        // LD_addr_A(wOTPartyMon1Item);
        wram->wOTPartyMon[0].mon.item = NO_ITEM;
    }


// ok:
    // LD_DE(vTiles2);
    // CALLFAR(aGetTrainerPic);
    GetTrainerPic_Conv(vram->vTiles2, tclass);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0;
    // DEC_A;
    // LD_addr_A(wEnemyItemState);
    wram->wEnemyItemState = 0xff;
    // hlcoord(12, 0, wTilemap);
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(12, 0, wram->wTilemap), 7, 7);
    // LD_A(-1);
    // LD_addr_A(wCurOTMon);
    wram->wCurOTMon = 0xff;
    // LD_A(TRAINER_BATTLE);
    // LD_addr_A(wBattleMode);
    wram->wBattleMode = TRAINER_BATTLE;

    // CALL(aIsGymLeader);
    // IF_NC goto done;
    if(IsGymLeader_Conv(tclass)) {
        // XOR_A_A;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = 0;
        // LD_A_addr(wPartyCount);
        // LD_B_A;
        uint8_t b = wram->wPartyCount;

        while(1) {
        // partyloop:
            // PUSH_BC;
            // LD_A(MON_HP);
            // CALL(aGetPartyParamLocation);
            // LD_A_hli;
            // OR_A_hl;
            // IF_Z goto skipfaintedmon;
            if(wram->wPartyMon[wram->wCurPartyMon].HP != 0) {
                // LD_C(HAPPINESS_GYMBATTLE);
                // CALLFAR(aChangeHappiness);
                ChangeHappiness_Conv(HAPPINESS_GYMBATTLE);
            }

        // skipfaintedmon:
            // POP_BC;
            // DEC_B;
            // IF_Z goto done;
            if(--b == 0)
                break;
            // LD_HL(wCurPartyMon);
            // INC_hl;
            ++wram->wCurPartyMon;
            // goto partyloop;
        }
    }

// done:
    // RET;
}

void InitEnemyWildmon(void){
    // LD_A(WILD_BATTLE);
    // LD_addr_A(wBattleMode);
    wram->wBattleMode = WILD_BATTLE;
    // FARCALL(aStubbedTrainerRankings_WildBattles);
    StubbedTrainerRankings_WildBattles();
    // CALL(aLoadEnemyMon);
    LoadEnemyMon();
    // LD_HL(wEnemyMonMoves);
    // LD_DE(wWildMonMoves);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wWildMonMoves, wram->wEnemyMon.moves, NUM_MOVES * sizeof(move_t));
    // LD_HL(wEnemyMonPP);
    // LD_DE(wWildMonPP);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wWildMonPP, wram->wEnemyMon.pp, NUM_MOVES);
    // LD_HL(wEnemyMonDVs);
    // PREDEF(pGetUnownLetter);
    uint8_t letter = GetUnownLetter_Conv(wram->wEnemyMon.dvs);
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_NZ goto skip_unown;
    // LD_A_addr(wFirstUnownSeen);
    // AND_A_A;
    // IF_NZ goto skip_unown;
    if(wram->wCurPartySpecies == UNOWN && wram->wFirstUnownSeen == 0) {
        // LD_A_addr(wUnownLetter);
        // LD_addr_A(wFirstUnownSeen);
        wram->wFirstUnownSeen = letter;
    }

// skip_unown:
    // LD_DE(vTiles2);
    // PREDEF(pGetAnimatedFrontpic);
    GetAnimatedFrontpic_Conv(vram->vTiles2, 0);
    // XOR_A_A;
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = 0;
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0;
    // hlcoord(12, 0, wTilemap);
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(12, 0, wram->wTilemap), 7, 7);
    // RET;
}

void FillEnemyMovesFromMoveIndicesBuffer(void){
//  //  unreferenced
    LD_HL(wEnemyMonMoves);
    LD_DE(wListMoves_MoveIndicesBuffer);
    LD_B(NUM_MOVES);

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    AND_A_A;
    IF_Z goto clearpp;

    PUSH_BC;
    PUSH_HL;

    PUSH_HL;
    DEC_A;
    LD_HL(mMoves + MOVE_PP);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    POP_HL;

    LD_BC(wEnemyMonPP - (wEnemyMonMoves + 1));
    ADD_HL_BC;
    LD_hl_A;

    POP_HL;
    POP_BC;

    DEC_B;
    IF_NZ goto loop;
    RET;


clear:
    XOR_A_A;
    LD_hli_A;


clearpp:
    PUSH_BC;
    PUSH_HL;
    LD_BC(wEnemyMonPP - (wEnemyMonMoves + 1));
    ADD_HL_BC;
    XOR_A_A;
    LD_hl_A;
    POP_HL;
    POP_BC;
    DEC_B;
    IF_NZ goto clear;
    RET;

}

static void ExitBattle_HandleEndOfBattle(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;
    if(wram->wLinkMode != LINK_NULL) {
        // CALL(aShowLinkBattleParticipantsAfterEnd);
        ShowLinkBattleParticipantsAfterEnd();
        // LD_C(150);
        // CALL(aDelayFrames);
        DelayFrames_Conv(150);
        // CALL(aDisplayLinkBattleResult);
        DisplayLinkBattleResult();
        // RET;
        return;
    }

// not_linked:
    // LD_A_addr(wBattleResult);
    // AND_A(0xf);
    // RET_NZ ;
    if((wram->wBattleResult & 0xf) != WIN)
        return;
    // CALL(aCheckPayDay);
    CheckPayDay();
    // XOR_A_A;
    // LD_addr_A(wForceEvolution);
    wram->wForceEvolution = FALSE;
    // PREDEF(pEvolveAfterBattle);
    EvolveAfterBattle();
    // FARCALL(aGivePokerusAndConvertBerries);
    GivePokerusAndConvertBerries();
    // RET;
}

void ExitBattle(void){
    // CALL(aExitBattle_HandleEndOfBattle);
    ExitBattle_HandleEndOfBattle();
    // CALL(aCleanUpBattleRAM);
    CleanUpBattleRAM();
    // RET;
}

void CleanUpBattleRAM(void){
    // CALL(aBattleEnd_HandleRoamMons);
    BattleEnd_HandleRoamMons();
    // XOR_A_A;
    // LD_addr_A(wLowHealthAlarm);
    wram->wLowHealthAlarm = 0x0;
    // LD_addr_A(wBattleMode);
    wram->wBattleMode = 0;
    // LD_addr_A(wBattleType);
    wram->wBattleType = 0;
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = FALSE;
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = 0;
    // LD_addr_A(wOtherTrainerClass);
    wram->wOtherTrainerClass = 0;
    // LD_addr_A(wFailedToFlee);
    wram->wFailedToFlee = FALSE;
    // LD_addr_A(wNumFleeAttempts);
    wram->wNumFleeAttempts = 0;
    // LD_addr_A(wForcedSwitch);
    wram->wForcedSwitch = 0;
    // LD_addr_A(wPartyMenuCursor);
    wram->wPartyMenuCursor = 0;
    // LD_addr_A(wKeyItemsPocketCursor);
    wram->wKeyItemsPocketCursor = 0;
    // LD_addr_A(wItemsPocketCursor);
    wram->wItemsPocketCursor = 0;
    // LD_addr_A(wBattleMenuCursorPosition);
    wram->wBattleMenuCursorPosition = 0;
    // LD_addr_A(wCurMoveNum);
    wram->wCurMoveNum = 0;
    // LD_addr_A(wBallsPocketCursor);
    wram->wBallsPocketCursor = 0;
    // LD_addr_A(wLastPocket);
    wram->wLastPocket = 0;
    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = 0;
    // LD_addr_A(wKeyItemsPocketScrollPosition);
    wram->wKeyItemsPocketScrollPosition = 0;
    // LD_addr_A(wItemsPocketScrollPosition);
    wram->wItemsPocketScrollPosition = 0;
    // LD_addr_A(wBallsPocketScrollPosition);
    wram->wBallsPocketScrollPosition = 0;
    // LD_HL(wPlayerSubStatus1);
    uint8_t* hl = &wram->wPlayerSubStatus1;
    // LD_B(wEnemyFuryCutterCount - wPlayerSubStatus1);
    uint8_t b = wEnemyFuryCutterCount - wPlayerSubStatus1;

    do {
    // loop:
        // LD_hli_A;
        *(hl++) = 0;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // RET;
}

void CheckPayDay(void){
    // LD_HL(wPayDayMoney);
    // LD_A_hli;
    // OR_A_hl;
    // INC_HL;
    // OR_A_hl;
    // RET_Z ;
    if((wram->wPayDayMoney[0] | wram->wPayDayMoney[1] | wram->wPayDayMoney[2]) == 0)
        return;
    // LD_A_addr(wAmuletCoin);
    // AND_A_A;
    // IF_Z goto okay;
    if(wram->wAmuletCoin) {
        uint8_t carry = wram->wPayDayMoney[2] & 0x80;
        // LD_HL(wPayDayMoney + 2);
        // SLA_hl;
        wram->wPayDayMoney[2] <<= 1;
        // DEC_HL;
        // RL_hl;
        wram->wPayDayMoney[1] = RotateLeft8(wram->wPayDayMoney[1], carry, &carry);
        // DEC_HL;
        // RL_hl;
        wram->wPayDayMoney[0] = RotateLeft8(wram->wPayDayMoney[0], carry, &carry);
        // IF_NC goto okay;
        if(carry) {
            // LD_A(0xff);
            // LD_hli_A;
            wram->wPayDayMoney[0] = 0xff;
            // LD_hli_A;
            wram->wPayDayMoney[1] = 0xff;
            // LD_hl_A;
            wram->wPayDayMoney[2] = 0xff;
        }
    }

// okay:
    // LD_HL(wPayDayMoney + 2);
    // LD_DE(wMoney + 2);
    // CALL(aAddBattleMoneyToAccount);
    AddBattleMoneyToAccount(wram->wMoney, wram->wPayDayMoney);
    // LD_HL(mBattleText_PlayerPickedUpPayDayMoney);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(BattleText_PlayerPickedUpPayDayMoney);
    // LD_A_addr(wInBattleTowerBattle);
    // BIT_A(0);
    // RET_Z ;
    if(!bit_test(wram->wInBattleTowerBattle, 0))
        return;
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // RET;
}

void ShowLinkBattleParticipantsAfterEnd(void){
    // FARCALL(aStubbedTrainerRankings_LinkBattles);
    StubbedTrainerRankings_LinkBattles();
    // FARCALL(aBackupMobileEventIndex);
    BackupMobileEventIndex();
    // LD_A_addr(wCurOTMon);
    // LD_HL(wOTPartyMon1Status);
    // CALL(aGetPartyLocation);
    // LD_A_addr(wEnemyMonStatus);
    // LD_hl_A;
    wram->wOTPartyMon[wram->wCurOTMon].status = wram->wEnemyMon.status[0];
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // FARCALL(av_ShowLinkBattleParticipants);
    v_ShowLinkBattleParticipants();
    // RET;
}

static void DisplayLinkBattleResult_Mobile_InvalidBattle(void){
    static const char InvalidBattle[] = "INVALID BATTLE@";
    // hlcoord(6, 8, wTilemap);
    // LD_DE(mDisplayLinkBattleResult_InvalidBattle);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(InvalidBattle), coord(6, 8, wram->wTilemap));
    // LD_C(200);
    // CALL(aDelayFrames);
    DelayFrames_Conv(200);
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // RET;
}

void DisplayLinkBattleResult(void){
    static const char YouWin[] = "YOU WIN@";
    static const char YouLose[] = "YOU LOSE@";
    static const char Draw[] = "  DRAW@";
    // FARCALL(aCheckMobileBattleError);
    // JP_C (mDisplayLinkBattleResult_Mobile_InvalidBattle);
    if(CheckMobileBattleError_Conv())
        return DisplayLinkBattleResult_Mobile_InvalidBattle();
    // CALL(aIsMobileBattle2);
    // IF_NZ goto proceed;
    if(IsMobileBattle2_Conv() && bit_test(wram->wcd2a, 4)) {
        // LD_HL(wcd2a);
        // BIT_hl(4);
        // IF_Z goto proceed;
        // FARCALL(aDetermineLinkBattleResult);
        DetermineLinkBattleResult();
    }

// proceed:
    // LD_A_addr(wBattleResult);
    // AND_A(0xf);
    // CP_A(LOSE);
    // IF_C goto win;  // WIN
    if((wram->wBattleResult & 0xf) == WIN) {
    // win:
        // FARCALL(aStubbedTrainerRankings_ColosseumWins);
        StubbedTrainerRankings_ColosseumWins();
        // LD_DE(mDisplayLinkBattleResult_YouWin);
        // goto store_result;
        PlaceStringSimple(U82C(YouWin), coord(6, 8, wram->wTilemap));
    }
    // IF_Z goto lose;  // LOSE
    else if((wram->wBattleResult & 0xf) == LOSE) {
    // lose:
        // FARCALL(aStubbedTrainerRankings_ColosseumLosses);
        StubbedTrainerRankings_ColosseumLosses();
        // LD_DE(mDisplayLinkBattleResult_YouLose);
        // goto store_result;
        PlaceStringSimple(U82C(YouLose), coord(6, 8, wram->wTilemap));
    }
    else {
    // DRAW
        // FARCALL(aStubbedTrainerRankings_ColosseumDraws);
        StubbedTrainerRankings_ColosseumDraws();
        // LD_DE(mDisplayLinkBattleResult_Draw);
        // goto store_result;
        PlaceStringSimple(U82C(Draw), coord(6, 8, wram->wTilemap));
    }

// store_result:
    // hlcoord(6, 8, wTilemap);
    // CALL(aPlaceString);
    // FARCALL(aBackupMobileEventIndex);
    BackupMobileEventIndex();
    // LD_C(200);
    // CALL(aDelayFrames);
    DelayFrames_Conv(200);

    // LD_A(MBANK(asLinkBattleStats));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asLinkBattleStats));

    // CALL(aAddLastLinkBattleToLinkRecord);
    //  TODO: Convert AddLastLinkBattleToLinkRecord
    AddLastLinkBattleToLinkRecord();
    // CALL(aReadAndPrintLinkBattleRecord);
    ReadAndPrintLinkBattleRecord();


    // CALL(aCloseSRAM);
    CloseSRAM_Conv();

    // CALL(aIsMobileBattle2);
    // IF_Z goto mobile;
    if(IsMobileBattle2_Conv()) {
    // mobile:
        // LD_C(200);
        // CALL(aDelayFrames);
        DelayFrames_Conv(200);
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // RET;
        return;
    }
    else {
        // CALL(aWaitPressAorB_BlinkCursor);
        WaitPressAorB_BlinkCursor_Conv();
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // RET;
        return;
    }
}

void IsMobileBattle2(void){
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    RET;

}

bool IsMobileBattle2_Conv(void){
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // RET;
    return wram->wLinkMode == LINK_MOBILE;
}

void v_DisplayLinkRecord(void){
    // LD_A(MBANK(asLinkBattleStats));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asLinkBattleStats));

    // CALL(aReadAndPrintLinkBattleRecord);
    ReadAndPrintLinkBattleRecord();

    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // hlcoord(0, 0, wAttrmap);
    // XOR_A_A;
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x0);
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames_Conv(8);
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor_Conv();
    // RET;
}

static bool ReadAndPrintLinkBattleRecord_PrintZerosIfNoSaveFileExists(tile_t* hl){
    static const char Scores[] = "   0    0    0";
    // LD_A_addr(wSavedAtLeastOnce);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wSavedAtLeastOnce)
        return false;
    // LD_DE(mReadAndPrintLinkBattleRecord_Scores);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Scores), hl);
    // SCF;
    // RET;
    return true;
}

static void ReadAndPrintLinkBattleRecord_PrintBattleRecord(void){
    static const char Record[] = "<PLAYER>\'s RECORD";
    static const char Result[] = "RESULT WIN LOSE DRAW";
    static const char Total[] = "TOTAL  WIN LOSE DRAW";
    // hlcoord(1, 0, wTilemap);
    // LD_DE(mReadAndPrintLinkBattleRecord_Record);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Record), coord(1, 0, wram->wTilemap));

    // hlcoord(0, 6, wTilemap);
    // LD_DE(mReadAndPrintLinkBattleRecord_Result);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Result), coord(0, 6, wram->wTilemap));

    // hlcoord(0, 2, wTilemap);
    // LD_DE(mReadAndPrintLinkBattleRecord_Total);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Total), coord(0, 2, wram->wTilemap));

    // hlcoord(6, 4, wTilemap);
    // LD_DE(sLinkBattleWins);
    // CALL(aReadAndPrintLinkBattleRecord_PrintZerosIfNoSaveFileExists);
    // IF_C goto quit;
    if(ReadAndPrintLinkBattleRecord_PrintZerosIfNoSaveFileExists(coord(6, 4, wram->wTilemap)))
        return;

    // LD_BC((2 << 8) | 4);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(6, 4, wram->wTilemap), GBToRAMAddr(sLinkBattleWins), 2, 4);

    // hlcoord(11, 4, wTilemap);
    // LD_DE(sLinkBattleLosses);
    // CALL(aReadAndPrintLinkBattleRecord_PrintZerosIfNoSaveFileExists);

    // LD_BC((2 << 8) | 4);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(11, 4, wram->wTilemap), GBToRAMAddr(sLinkBattleLosses), 2, 4);

    // hlcoord(16, 4, wTilemap);
    // LD_DE(sLinkBattleDraws);
    // CALL(aReadAndPrintLinkBattleRecord_PrintZerosIfNoSaveFileExists);

    // LD_BC((2 << 8) | 4);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(16, 4, wram->wTilemap), GBToRAMAddr(sLinkBattleDraws), 2, 4);

// quit:
    // RET;
    return;
}

void ReadAndPrintLinkBattleRecord(void){
    static const char Format[] = "  ---  <LF>"
        "         -    -    -";
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aReadAndPrintLinkBattleRecord_PrintBattleRecord);
    ReadAndPrintLinkBattleRecord_PrintBattleRecord();
    // hlcoord(0, 8, wTilemap);
    tile_t* hl = coord(0, 8, wram->wTilemap);
    // LD_B(NUM_LINK_BATTLE_RECORDS);
    uint8_t b = NUM_LINK_BATTLE_RECORDS;
    // LD_DE(sLinkBattleRecord1Name);
    const struct LinkBattleRecord* de = (const struct LinkBattleRecord*)GBToRAMAddr(sLinkBattleRecord1);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        tile_t* hl2 = hl;
        // PUSH_DE;
        // LD_A_de;
        // AND_A_A;
        // IF_Z goto PrintFormatString;
        // LD_A_addr(wSavedAtLeastOnce);
        // AND_A_A;
        // IF_Z goto PrintFormatString;
        if(de->name[0] == 0 || !wram->wSavedAtLeastOnce) {
        // PrintFormatString:
            // LD_DE(mReadAndPrintLinkBattleRecord_Format);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(Format), hl);
        }
        else {
            // PUSH_HL;
            // PUSH_HL;
            // LD_H_D;
            // LD_L_E;
            // LD_DE(wLinkBattleRecordName);
            // LD_BC(NAME_LENGTH - 1);
            // CALL(aCopyBytes);
            CopyBytes_Conv2(wram->wLinkBattleRecordName, de->name, NAME_LENGTH - 1);
            // LD_A(0x50);
            // LD_de_A;
            wram->wLinkBattleRecordName[NAME_LENGTH - 1] = 0x50;
            // INC_DE;  // wLinkBattleRecordWins
            // LD_BC(6);
            // CALL(aCopyBytes);
            wram->wLinkBattleRecordWins = de->wins;
            wram->wLinkBattleRecordLosses = de->losses;
            wram->wLinkBattleRecordDraws = de->draws;
            // LD_DE(wLinkBattleRecordName);
            // POP_HL;
            // CALL(aPlaceString);
            PlaceStringSimple(wram->wLinkBattleRecordName, hl2);
            // POP_HL;
            // LD_DE(26);
            // ADD_HL_DE;
            hl2 += 26;
            // PUSH_HL;
            // LD_DE(wLinkBattleRecordWins);
            // LD_BC((2 << 8) | 4);
            // CALL(aPrintNum);
            PrintNum_Conv2(hl2, &wram->wLinkBattleRecordWins, 2, 4);
            // POP_HL;
            // LD_DE(5);
            // ADD_HL_DE;
            hl2 += 5;
            // PUSH_HL;
            // LD_DE(wLinkBattleRecordLosses);
            // LD_BC((2 << 8) | 4);
            // CALL(aPrintNum);
            PrintNum_Conv2(hl2, &wram->wLinkBattleRecordLosses, 2, 4);
            // POP_HL;
            // LD_DE(5);
            // ADD_HL_DE;
            hl2 += 5;
            // LD_DE(wLinkBattleRecordDraws);
            // LD_BC((2 << 8) | 4);
            // CALL(aPrintNum);
            PrintNum_Conv2(hl2, &wram->wLinkBattleRecordDraws, 2, 4);
            // goto next;
        }

    // next:
        // POP_HL;
        // LD_BC(LINK_BATTLE_RECORD_LENGTH);
        // ADD_HL_BC;
        // LD_D_H;
        // LD_E_L;
        // POP_HL;
        // LD_BC(2 * SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void BattleEnd_HandleRoamMons(void){
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_ROAMING);
    // IF_NZ goto not_roaming;
    if(wram->wBattleType == BATTLETYPE_ROAMING) {
        const species_t roamer = wram->wTempEnemyMonSpecies;
        // LD_A_addr(wBattleResult);
        // AND_A(0xf);
        // IF_Z goto caught_or_defeated_roam_mon;  // WIN
        if((wram->wBattleResult & 0xf) == WIN) {
        // caught_or_defeated_roam_mon:
            // CALL(aGetRoamMonHP);
            // LD_hl(0);
            *GetRoamMonHP_Conv(roamer) = 0;
            // CALL(aGetRoamMonMapGroup);
            // LD_hl(GROUP_N_A);
            *GetRoamMonMapGroup_Conv(roamer) = GROUP_N_A;
            // CALL(aGetRoamMonMapNumber);
            // LD_hl(MAP_N_A);
            *GetRoamMonMapNumber_Conv(roamer) = MAP_N_A;
            // CALL(aGetRoamMonSpecies);
            // LD_hl(0);
            *GetRoamMonSpecies_Conv(roamer) = 0;
            // RET;
            return;
        }
        // CALL(aGetRoamMonHP);
        // LD_A_addr(wEnemyMonHP + 1);
        // LD_hl_A;
        *GetRoamMonHP_Conv(roamer) = (uint8_t)ReverseEndian16(wram->wEnemyMon.hp);
        // goto update_roam_mons;
    }
    else {
    // not_roaming:
        // CALL(aBattleRandom);
        // AND_A(0xf);
        // RET_NZ ;
        if((BattleRandom_Conv() & 0xf) != 0x0)
            return;
    }

// update_roam_mons:
    // CALLFAR(aUpdateRoamMons);
    UpdateRoamMons();
    // RET;
}

void GetRoamMonMapGroup(void){
    LD_A_addr(wTempEnemyMonSpecies);
    LD_B_A;
    LD_A_addr(wRoamMon1Species);
    CP_A_B;
    LD_HL(wRoamMon1MapGroup);
    RET_Z ;
    LD_A_addr(wRoamMon2Species);
    CP_A_B;
    LD_HL(wRoamMon2MapGroup);
    RET_Z ;
    LD_HL(wRoamMon3MapGroup);
    RET;

}

uint8_t* GetRoamMonMapGroup_Conv(species_t a){
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_B_A;
    // LD_A_addr(wRoamMon1Species);
    // CP_A_B;
    // LD_HL(wRoamMon1MapGroup);
    // RET_Z ;
    if(a == wram->wRoamMon1.species) {
        return &wram->wRoamMon1.mapId.mapGroup;
    }
    // LD_A_addr(wRoamMon2Species);
    // CP_A_B;
    // LD_HL(wRoamMon2MapGroup);
    // RET_Z ;
    else if(a == wram->wRoamMon2.species) {
        return &wram->wRoamMon2.mapId.mapGroup;
    }
    // LD_HL(wRoamMon3MapGroup);
    // RET;
    return &wram->wRoamMon3.mapId.mapGroup;
}

void GetRoamMonMapNumber(void){
    LD_A_addr(wTempEnemyMonSpecies);
    LD_B_A;
    LD_A_addr(wRoamMon1Species);
    CP_A_B;
    LD_HL(wRoamMon1MapNumber);
    RET_Z ;
    LD_A_addr(wRoamMon2Species);
    CP_A_B;
    LD_HL(wRoamMon2MapNumber);
    RET_Z ;
    LD_HL(wRoamMon3MapNumber);
    RET;

}

uint8_t* GetRoamMonMapNumber_Conv(species_t a){
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_B_A;
    // LD_A_addr(wRoamMon1Species);
    // CP_A_B;
    // LD_HL(wRoamMon1MapNumber);
    // RET_Z ;
    if(a == wram->wRoamMon1.species) {
        return &wram->wRoamMon1.mapId.mapNumber;
    }
    // LD_A_addr(wRoamMon2Species);
    // CP_A_B;
    // LD_HL(wRoamMon2MapNumber);
    // RET_Z ;
    if(a == wram->wRoamMon2.species) {
        return &wram->wRoamMon2.mapId.mapNumber;
    }
    // LD_HL(wRoamMon3MapNumber);
    // RET;
    return &wram->wRoamMon3.mapId.mapNumber;
}

void GetRoamMonHP(void){
//  output: hl = wRoamMonHP
    LD_A_addr(wTempEnemyMonSpecies);
    LD_B_A;
    LD_A_addr(wRoamMon1Species);
    CP_A_B;
    LD_HL(wRoamMon1HP);
    RET_Z ;
    LD_A_addr(wRoamMon2Species);
    CP_A_B;
    LD_HL(wRoamMon2HP);
    RET_Z ;
    LD_HL(wRoamMon3HP);
    RET;

}

uint8_t* GetRoamMonHP_Conv(species_t a){
//  output: hl = wRoamMonHP
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_B_A;
    // LD_A_addr(wRoamMon1Species);
    // CP_A_B;
    // LD_HL(wRoamMon1HP);
    // RET_Z ;
    if(a == wram->wRoamMon1.species)
        return &wram->wRoamMon1.HP;
    // LD_A_addr(wRoamMon2Species);
    // CP_A_B;
    // LD_HL(wRoamMon2HP);
    // RET_Z ;
    else if(a == wram->wRoamMon2.species)
        return &wram->wRoamMon2.HP;
    // LD_HL(wRoamMon3HP);
    // RET;
    return &wram->wRoamMon3.HP;
}

void GetRoamMonDVs(void){
//  output: hl = wRoamMonDVs
    LD_A_addr(wTempEnemyMonSpecies);
    LD_B_A;
    LD_A_addr(wRoamMon1Species);
    CP_A_B;
    LD_HL(wRoamMon1DVs);
    RET_Z ;
    LD_A_addr(wRoamMon2Species);
    CP_A_B;
    LD_HL(wRoamMon2DVs);
    RET_Z ;
    LD_HL(wRoamMon3DVs);
    RET;

}

//  output: hl = wRoamMonDVs
uint16_t* GetRoamMonDVs_Conv(species_t a){
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_B_A;
    // LD_A_addr(wRoamMon1Species);
    // CP_A_B;
    // LD_HL(wRoamMon1DVs);
    // RET_Z ;
    if(a == wram->wRoamMon1.species)
        // return &wram->wRoamMon1.DVs;
        return (uint16_t*)(((uint8_t*)&wram->wRoamMon1) + offsetof(struct Roamer, DVs));
    // LD_A_addr(wRoamMon2Species);
    // CP_A_B;
    // LD_HL(wRoamMon2DVs);
    // RET_Z ;
    else if(a == wram->wRoamMon2.species)
        // return &wram->wRoamMon2.DVs;
        return (uint16_t*)(((uint8_t*)&wram->wRoamMon2) + offsetof(struct Roamer, DVs));
    // LD_HL(wRoamMon3DVs);
    // RET;
    // return &wram->wRoamMon3.DVs;
    return (uint16_t*)(((uint8_t*)&wram->wRoamMon3) + offsetof(struct Roamer, DVs));
}

void GetRoamMonSpecies(void){
    LD_A_addr(wTempEnemyMonSpecies);
    LD_HL(wRoamMon1Species);
    CP_A_hl;
    RET_Z ;
    LD_HL(wRoamMon2Species);
    CP_A_hl;
    RET_Z ;
    LD_HL(wRoamMon3Species);
    RET;

}

species_t* GetRoamMonSpecies_Conv(species_t a){
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_HL(wRoamMon1Species);
    // CP_A_hl;
    // RET_Z ;
    if(a == wram->wRoamMon1.species)
        return &wram->wRoamMon1.species;
    // LD_HL(wRoamMon2Species);
    // CP_A_hl;
    // RET_Z ;
    else if(a == wram->wRoamMon2.species)
        return &wram->wRoamMon2.species;
    // LD_HL(wRoamMon3Species);
    // RET;
    return &wram->wRoamMon3.species;
}

static bool AddLastLinkBattleToLinkRecord_CheckOverflow(uint8_t* hl){
    // DEC_HL;
    // LD_A_hl;
    // INC_HL;
    // CP_A(HIGH(MAX_LINK_RECORD));
    // RET_C ;
    // LD_A_hl;
    // CP_A(LOW(MAX_LINK_RECORD));
    uint16_t record = (hl[0] << 8) | hl[1];
    // RET;
    return record >= MAX_LINK_RECORD;
}

static void AddLastLinkBattleToLinkRecord_StoreResult(uint8_t* hl){
    uint16_t bc;
    // LD_A_addr(wBattleResult);
    // AND_A(0xf);
    uint8_t result = wram->wBattleResult & 0xf;
    // CP_A(LOSE);
    // LD_BC((sLinkBattleRecord1Wins - sLinkBattleRecord1) + 1);
    // IF_C goto okay;  // WIN
    if(result < LOSE)
        bc = (sLinkBattleRecord1Wins - sLinkBattleRecord1);
    // LD_BC((sLinkBattleRecord1Losses - sLinkBattleRecord1) + 1);
    // IF_Z goto okay;  // LOSE
    else if(result == LOSE)
        bc = (sLinkBattleRecord1Losses - sLinkBattleRecord1);
// DRAW
    // LD_BC((sLinkBattleRecord1Draws - sLinkBattleRecord1) + 1);
    else
        bc = (sLinkBattleRecord1Draws - sLinkBattleRecord1);

// okay:
    // ADD_HL_BC;
    hl += bc;
    // CALL(aAddLastLinkBattleToLinkRecord_CheckOverflow);
    // RET_NC ;
    if(AddLastLinkBattleToLinkRecord_CheckOverflow(hl))
        return;
    uint16_t record = (hl[0] << 8) | hl[1];
    // INC_hl;
    ++record;
    // RET_NZ ;
    hl[1] = LOW(record);
    // DEC_HL;
    // INC_hl;
    hl[0] = HIGH(record);
    // RET;
}

struct LinkRecordPtrResult {
    uint16_t bc;
    uint8_t e;
};

static struct LinkRecordPtrResult AddLastLinkBattleToLinkRecord_LoadPointer(uint8_t* hl){
    // LD_E(0x0);
    uint8_t e = 0x0;
    // LD_A_hld;
    // LD_C_A;
    // LD_A_hld;
    // LD_B_A;
    uint16_t bc = hl[5] | (hl[4] << 8);
    uint16_t bc2 = hl[3] | (hl[2] << 8);
    // LD_A_hld;
    // ADD_A_C;
    // LD_C_A;
    // LD_A_hld;
    // ADC_A_B;
    // LD_B_A;
    // IF_NC goto okay2;
    // INC_E;
    if(bc + bc2 > 0xffff)
        e++;
    bc += bc2;

// okay2:
    uint16_t bc3 = hl[1] | (hl[0] << 8);
    // LD_A_hld;
    // ADD_A_C;
    // LD_C_A;
    // LD_A_hl;
    // ADC_A_B;
    // LD_B_A;
    // RET_NC ;
    if(bc + bc3 > 0xffff)
        e++;
    // INC_E;
    // RET;
    return (struct LinkRecordPtrResult){.bc = bc + bc3, .e = e};
}

static void AddLastLinkBattleToLinkRecord_FindOpponentAndAppendRecord(void){
    // LD_B(NUM_LINK_BATTLE_RECORDS);
    uint8_t b = NUM_LINK_BATTLE_RECORDS;
    // LD_HL(sLinkBattleRecord1End - 1);
    uint8_t* hl = GBToRAMAddr(sLinkBattleRecord1End - 6);
    // LD_DE(wLinkBattleRecordBuffer);
    uint8_t* de = wram->wLinkBattleRecordName;

    do {
    // loop3:
        // PUSH_BC;
        // PUSH_DE;
        // PUSH_HL;
        // CALL(aAddLastLinkBattleToLinkRecord_LoadPointer);
        struct LinkRecordPtrResult res = AddLastLinkBattleToLinkRecord_LoadPointer(hl);
        // POP_HL;
        // LD_A_E;
        // POP_DE;
        // LD_de_A;
        *de = res.e;
        // INC_DE;
        de++;
        // LD_A_B;
        // LD_de_A;
        *(de++) = HIGH(res.bc);
        // INC_DE;
        // LD_A_C;
        // LD_de_A;
        *(de++) = LOW(res.bc);
        // INC_DE;
        // LD_BC(LINK_BATTLE_RECORD_LENGTH);
        // ADD_HL_BC;
        // POP_BC;
        hl += LINK_BATTLE_RECORD_LENGTH;
        // DEC_B;
        // IF_NZ goto loop3;
    } while(--b != 0);
    // LD_B(0x0);
    b = 0x0;
    // LD_C(0x1);
    uint8_t c = 0x1;

    do {
        do {
        // loop4:
            // LD_A_B;
            // ADD_A_B;
            // ADD_A_B;
            // LD_E_A;
            // LD_D(0);
            // LD_HL(wLinkBattleRecordBuffer);
            // ADD_HL_DE;
            uint8_t* hl = wram->wLinkBattleRecordName + (b * 3);
            // PUSH_HL;
            // LD_A_C;
            // ADD_A_C;
            // ADD_A_C;
            // LD_E_A;
            // LD_D(0);
            // LD_HL(wLinkBattleRecordBuffer);
            // ADD_HL_DE;
            // LD_D_H;
            // LD_E_L;
            uint8_t* de = wram->wLinkBattleRecordName + (c * 3);
            // POP_HL;
            // PUSH_BC;
            // LD_C(3);
            // CALL(aCompareBytes);
            int cmp = CompareBytes_Conv2(de, hl, 3);
            // POP_BC;
            // IF_Z goto equal;
            // IF_NC goto done2;
            if(cmp > 0){
            // done2:
                // PUSH_BC;
                // LD_A_B;
                // LD_BC(LINK_BATTLE_RECORD_LENGTH);
                // LD_HL(sLinkBattleRecord);
                // CALL(aAddNTimes);
                // PUSH_HL;
                uint8_t* hl = GBToRAMAddr(sLinkBattleRecord + LINK_BATTLE_RECORD_LENGTH * b);
                // LD_DE(wLinkBattleRecordBuffer);
                // LD_BC(LINK_BATTLE_RECORD_LENGTH);
                // CALL(aCopyBytes);
                CopyBytes_Conv2(wram->wLinkBattleRecordName, hl, LINK_BATTLE_RECORD_LENGTH);
                // POP_HL;
                // POP_BC;
                // PUSH_HL;
                // LD_A_C;
                // LD_BC(LINK_BATTLE_RECORD_LENGTH);
                // LD_HL(sLinkBattleRecord);
                // CALL(aAddNTimes);
                // POP_DE;
                // PUSH_HL;
                // LD_BC(LINK_BATTLE_RECORD_LENGTH);
                // CALL(aCopyBytes);
                uint8_t* de = GBToRAMAddr(sLinkBattleRecord + LINK_BATTLE_RECORD_LENGTH * c);
                // LD_HL(wLinkBattleRecordBuffer);
                // LD_BC(LINK_BATTLE_RECORD_LENGTH);
                // POP_DE;
                // CALL(aCopyBytes);
                CopyBytes_Conv2(de, wram->wLinkBattleRecordName, LINK_BATTLE_RECORD_LENGTH);
                // RET;
                return;
            }

        // equal:
            // INC_C;
            // LD_A_C;
            // CP_A(0x5);
            // IF_NZ goto loop4;
        } while(++c != 0x5);
        // INC_B;
        c = ++b;
        // LD_C_B;
        // INC_C;
        c++;
        // LD_A_B;
        // CP_A(0x4);
        // IF_NZ goto loop4;
    } while(b != 0x4);
    // RET;
}

void AddLastLinkBattleToLinkRecord(void){
    // LD_HL(wOTPlayerID);
    // LD_DE(wStringBuffer1);
    // LD_BC(2);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wStringBuffer1, &wram->wOTPlayerID, 2);
    // LD_HL(wOTPlayerName);
    // LD_BC(NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wStringBuffer1 + 2, wram->wOTPlayerName, NAME_LENGTH - 1);
    // LD_HL(sLinkBattleStats - (LINK_BATTLE_RECORD_LENGTH - 6));
    // CALL(aAddLastLinkBattleToLinkRecord_StoreResult);
    AddLastLinkBattleToLinkRecord_StoreResult(GBToRAMAddr(sLinkBattleStats - (LINK_BATTLE_RECORD_LENGTH - 6)));
    // LD_HL(sLinkBattleRecord);
    uint8_t* hl = GBToRAMAddr(sLinkBattleStats - (LINK_BATTLE_RECORD_LENGTH - 6));
    // LD_D(NUM_LINK_BATTLE_RECORDS);
    uint8_t d = NUM_LINK_BATTLE_RECORDS;

    do {
    // loop:
        // PUSH_HL;
        // INC_HL;
        // INC_HL;
        // LD_A_hl;
        uint8_t a = hl[2];
        // DEC_HL;
        // DEC_HL;
        // AND_A_A;
        // IF_Z goto copy;
        if(a == 0)
            goto copy;
        // PUSH_DE;
        // LD_BC(LINK_BATTLE_RECORD_LENGTH - 6);
        // LD_DE(wStringBuffer1);
        // CALL(aCompareBytesLong);
        int cmp = CompareBytes_Conv2(wram->wStringBuffer1, hl, LINK_BATTLE_RECORD_LENGTH - 6);
        // POP_DE;
        // POP_HL;
        // IF_C goto done;
        if(cmp < 0)
            goto done;
        // LD_BC(LINK_BATTLE_RECORD_LENGTH);
        // ADD_HL_BC;
        hl += LINK_BATTLE_RECORD_LENGTH;
        // DEC_D;
        // IF_NZ goto loop;
    } while(--d != 0);
    // LD_BC(-LINK_BATTLE_RECORD_LENGTH);
    // ADD_HL_BC;
    // PUSH_HL;
    hl -= LINK_BATTLE_RECORD_LENGTH;
    uint8_t* de;

copy:
    // LD_D_H;
    // LD_E_L;
    de = hl;
    // LD_HL(wStringBuffer1);
    // LD_BC(LINK_BATTLE_RECORD_LENGTH - 6);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, wram->wStringBuffer1, LINK_BATTLE_RECORD_LENGTH - 6);
    // LD_B(6);
    uint8_t b = 6;
    // XOR_A_A;

    do {
    // loop2:
        // LD_de_A;
        *de = 0;
        // INC_DE;
        de++;
        // DEC_B;
        // IF_NZ goto loop2;
    } while(--b != 0);
    // POP_HL;

done:
    // CALL(aAddLastLinkBattleToLinkRecord_StoreResult);
    AddLastLinkBattleToLinkRecord_StoreResult(hl);
    // CALL(aAddLastLinkBattleToLinkRecord_FindOpponentAndAppendRecord);
    AddLastLinkBattleToLinkRecord_FindOpponentAndAppendRecord();
    // RET;
}

static void InitBattleDisplay_InitBackPic(void) {
    // CALL(aGetTrainerBackpic);
    GetTrainerBackpic();
    // CALL(aCopyBackpic);
    CopyBackpic();
    // RET;
}

static void InitBattleDisplay_BlankBGMap(void) {
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awDecompressScratch));
    // LDH_addr_A(rSVBK);

    // LD_HL(wDecompressScratch);
    // LD_BC(BG_MAP_WIDTH * BG_MAP_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wDecompressScratch, BG_MAP_WIDTH * BG_MAP_HEIGHT, CHAR_SPACE);

    // LD_DE(wDecompressScratch);
    // hlbgcoord(0, 0, vBGMap0);
    // //LD_BC((BANK(@) << 8) | (BG_MAP_WIDTH * BG_MAP_HEIGHT) / LEN_2BPP_TILE);
    // LD_BC((BANK(aInitBattleDisplay_BlankBGMap) << 8) | (BG_MAP_WIDTH * BG_MAP_HEIGHT) / LEN_2BPP_TILE);
    // CALL(aRequest2bpp);
    CopyBytes_Conv2(bgcoord(0, 0, vram->vBGMap0), wram->wDecompressScratch, BG_MAP_WIDTH * BG_MAP_HEIGHT);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void InitBattleDisplay(void){
    // CALL(aInitBattleDisplay_InitBackPic);
    InitBattleDisplay_InitBackPic();
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
    // FARCALL(aMobileTextBorder);
    MobileTextBorder_Conv();
    // hlcoord(1, 5, wTilemap);
    // LD_BC((3 << 8) | 7);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 5, wram->wTilemap), 7, 3);
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(av_LoadBattleFontsHPBar);
    v_LoadBattleFontsHPBar();
    // CALL(aInitBattleDisplay_BlankBGMap);
    InitBattleDisplay_BlankBGMap();
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // LDH_addr_A(rWY);
    gb_write(rWY, 0x90);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // FARCALL(aBattleIntroSlidingPics);
    BattleIntroSlidingPics();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // LD_A(0x31);
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0x31;
    // hlcoord(2, 6, wTilemap);
    // LD_BC((6 << 8) | 6);
    // PREDEF(pPlaceGraphic);
    PlaceGraphic_Conv(coord(2, 6, wram->wTilemap), 6, 6);
    // XOR_A_A;
    // LDH_addr_A(hWY);
    hram->hWY = 0;
    // LDH_addr_A(rWY);
    gb_write(rWY, 0x0);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aHideSprites);
    HideSprites_Conv();
    // LD_B(SCGB_BATTLE_COLORS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_BATTLE_COLORS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // RET;
    return;

}

void GetTrainerBackpic(void){
//  Load the player character's backpic (6x6) into VRAM starting from vTiles2 tile $31.

//  Special exception for Dude.
    // LD_B(BANK(aDudeBackpic));
    // LD_HL(mDudeBackpic);
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);
    // IF_Z goto Decompress;
    if(wram->wBattleType == BATTLETYPE_TUTORIAL) {
        // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
        // LD_C(7 * 7);
        // PREDEF(pDecompressGet2bpp);
        // RET;
        return LoadPNG2bppAssetToVRAMByColumn(vram->vTiles2 + LEN_2BPP_TILE * 0x31, DudeBackpic);
    }

//  What gender are we?
    // LD_A_addr(wPlayerSpriteSetupFlags);
    // BIT_A(PLAYERSPRITESETUP_FEMALE_TO_MALE_F);
    // IF_NZ goto Chris;
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto Chris;
    if(!bit_test(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_FEMALE_TO_MALE_F) && bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F)) {
    //  It's a girl.
        // FARCALL(aGetKrisBackpic);
        // RET;
        return GetKrisBackpic();
    }

// Chris:
//  It's a boy.
    // LD_B(BANK(aChrisBackpic));
    // LD_HL(mChrisBackpic);

// Decompress:
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_C(7 * 7);
    // PREDEF(pDecompressGet2bpp);
    // RET;
    return LoadPNG2bppAssetToVRAMByColumn(vram->vTiles2 + LEN_2BPP_TILE * 0x31, ChrisBackpic);

}

static void CopyBackpic_LoadTrainerBackpicAsOAM(void) {
    // LD_HL(wVirtualOAMSprite00);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;
    // XOR_A_A;
    // LDH_addr_A(hMapObjectIndex);
    uint8_t idx = 0;
    // LD_B(6);
    uint8_t b = 6;
    // LD_E((SCREEN_WIDTH + 1) * TILE_WIDTH);
    uint8_t e = (SCREEN_WIDTH + 1) * TILE_WIDTH;
    do {
    // outer_loop:
        // LD_C(3);
        uint8_t c = 3;
        // LD_D(8 * TILE_WIDTH);
        uint8_t d = 8 * TILE_WIDTH;

        do {
        // inner_loop:
            // LD_hl_D;  // y
            // INC_HL;
            hl->yCoord = d;
            // LD_hl_E;  // x
            // INC_HL;
            hl->xCoord = e;
            // LDH_A_addr(hMapObjectIndex);
            // LD_hli_A;  // tile id
            // INC_A;
            // LDH_addr_A(hMapObjectIndex);
            hl->tileID = idx++;
            // LD_A(PAL_BATTLE_OB_PLAYER);
            // LD_hli_A;  // attributes
            hl->attributes = PAL_BATTLE_OB_PLAYER;
            // LD_A_D;
            // ADD_A(1 * TILE_WIDTH);
            // LD_D_A;
            d += 1 * TILE_WIDTH;
            // DEC_C;
            // IF_NZ goto inner_loop;
            hl++;
        } while(--c != 0);
        // LDH_A_addr(hMapObjectIndex);
        // ADD_A(0x3);
        // LDH_addr_A(hMapObjectIndex);
        idx += 0x3;
        // LD_A_E;
        // ADD_A(1 * TILE_WIDTH);
        // LD_E_A;
        e += 1 * TILE_WIDTH;
        // DEC_B;
        // IF_NZ goto outer_loop;
    } while(--b != 0);
    // RET;
}

void CopyBackpic(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awDecompressScratch));
    // LDH_addr_A(rSVBK);
    // LD_HL(vTiles0);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LDH_A_addr(hROMBank);
    // LD_B_A;
    // LD_C(7 * 7);
    // CALL(aGet2bpp);
    CopyBytes_Conv2(vram->vTiles0, vram->vTiles2 + LEN_2BPP_TILE * 0x31, 7 * 7 * LEN_2BPP_TILE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aCopyBackpic_LoadTrainerBackpicAsOAM);
    CopyBackpic_LoadTrainerBackpicAsOAM();
    // LD_A(0x31);
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0x31;
    // hlcoord(2, 6, wTilemap);
    // LD_BC((6 << 8) | 6);
    // PREDEF(pPlaceGraphic);
    PlaceGraphic_Conv(coord(2, 6, wram->wTilemap), 6, 6);
    // RET;
}

void BattleStartMessage(void){
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_Z goto wild;
    const struct TextCmd* hl;
    if(wram->wBattleMode != WILD_BATTLE) {
        // LD_DE(SFX_SHINE);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_SHINE);
        // CALL(aWaitSFX);
        WaitSFX_Conv();

        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);

        // FARCALL(aBattle_GetTrainerName);
        Battle_GetTrainerName_Conv();

        // LD_HL(mWantsToBattleText);
        // goto PlaceBattleStartText;
        hl = WantsToBattleText;
    }
    else {
    // wild:
        // CALL(aBattleCheckEnemyShininess);
        // IF_NC goto not_shiny;
        if(BattleCheckEnemyShininess_Conv()) {
            // XOR_A_A;
            // LD_addr_A(wNumHits);
            wram->wNumHits = 0;
            // LD_A(1);
            // LDH_addr_A(hBattleTurn);
            hram->hBattleTurn = 1;
            // LD_A(1);
            // LD_addr_A(wBattleAnimParam);
            wram->wBattleAnimParam = 1;
            // LD_DE(ANIM_SEND_OUT_MON);
            // CALL(aCall_PlayBattleAnim);
            Call_PlayBattleAnim_Conv(ANIM_SEND_OUT_MON);
        }

    // not_shiny:
        // FARCALL(aCheckSleepingTreeMon);
        // IF_C goto skip_cry;
        if(!CheckSleepingTreeMon_Conv(wram->wTempWildMonSpecies)) {
            // FARCALL(aCheckBattleScene);
            // IF_C goto cry_no_anim;
            if(CheckBattleScene_Conv()) {
                // hlcoord(12, 0, wTilemap);
                // LD_D(0x0);
                // LD_E(ANIM_MON_NORMAL);
                // PREDEF(pAnimateFrontpic);
                AnimateFrontpic_Conv(coord(12, 0, wram->wTilemap), 0x0, ANIM_MON_NORMAL);
                // goto skip_cry;  // cry is played during the animation
            }
            else {
            // cry_no_anim:
                // LD_A(0xf);
                // LD_addr_A(wCryTracks);
                wram->wCryTracks = 0xf;
                // LD_A_addr(wTempEnemyMonSpecies);
                // CALL(aPlayStereoCry);
                PlayStereoCry_Conv(wram->wTempEnemyMonSpecies);
            }
        }
    // skip_cry:
        // LD_A_addr(wBattleType);
        // CP_A(BATTLETYPE_FISH);
        // IF_NZ goto NotFishing;
        if(wram->wBattleType == BATTLETYPE_FISH) {
            // FARCALL(aStubbedTrainerRankings_HookedEncounters);
            StubbedTrainerRankings_HookedEncounters();
            // LD_HL(mHookedPokemonAttackedText);
            hl = HookedPokemonAttackedText;
            // goto PlaceBattleStartText;
        }
        else {
        // NotFishing:
            // LD_HL(mPokemonFellFromTreeText);
            // CP_A(BATTLETYPE_TREE);
            // IF_Z goto PlaceBattleStartText;
            if(wram->wBattleType == BATTLETYPE_TREE) {
                hl = PokemonFellFromTreeText;
            }
            // LD_HL(mWildCelebiAppearedText);
            // CP_A(BATTLETYPE_CELEBI);
            // IF_Z goto PlaceBattleStartText;
            else if(wram->wBattleType == BATTLETYPE_CELEBI) {
                hl = WildCelebiAppearedText;
            }
            // LD_HL(mWildPokemonAppearedText);
            else {
                hl = WildPokemonAppearedText;
            }
        }
    }

// PlaceBattleStartText:
    // PUSH_HL;
    // FARCALL(aBattleStart_TrainerHuds);
    BattleStart_TrainerHuds();
    // POP_HL;
    // CALL(aStdBattleTextbox);
    StdBattleTextbox_Conv2(hl);

    // CALL(aIsMobileBattle2);
    // RET_NZ ;
    if(!IsMobileBattle2_Conv())
        return;

    // LD_C(0x2);  // start
    // FARCALL(aMobile_PrintOpponentBattleMessage);

    // RET;
}
