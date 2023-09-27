#include "../../constants.h"
#include "item_effects.h"
#include "../../data/moves/moves.h"

void v_DoItemEffect(void){
    LD_A_addr(wCurItem);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    CALL(aCopyName1);
    LD_A(1);
    LD_addr_A(wItemEffectSucceeded);
    LD_A_addr(wCurItem);
    DEC_A;
    LD_HL(mItemEffects);
    RST(aJumpTable);
    RET;

}

void ItemEffects(void){
//  entries correspond to item ids (see constants/item_constants.asm)
    //table_width ['2', 'ItemEffects']
    //dw ['PokeBallEffect'];  // MASTER_BALL
    //dw ['PokeBallEffect'];  // ULTRA_BALL
    //dw ['NoEffect'];  // BRIGHTPOWDER
    //dw ['PokeBallEffect'];  // GREAT_BALL
    //dw ['PokeBallEffect'];  // POKE_BALL
    //dw ['TownMapEffect'];  // TOWN_MAP
    //dw ['BicycleEffect'];  // BICYCLE
    //dw ['EvoStoneEffect'];  // MOON_STONE
    //dw ['StatusHealingEffect'];  // ANTIDOTE
    //dw ['StatusHealingEffect'];  // BURN_HEAL
    //dw ['StatusHealingEffect'];  // ICE_HEAL
    //dw ['StatusHealingEffect'];  // AWAKENING
    //dw ['StatusHealingEffect'];  // PARLYZ_HEAL
    //dw ['FullRestoreEffect'];  // FULL_RESTORE
    //dw ['RestoreHPEffect'];  // MAX_POTION
    //dw ['RestoreHPEffect'];  // HYPER_POTION
    //dw ['RestoreHPEffect'];  // SUPER_POTION
    //dw ['RestoreHPEffect'];  // POTION
    //dw ['EscapeRopeEffect'];  // ESCAPE_ROPE
    //dw ['RepelEffect'];  // REPEL
    //dw ['RestorePPEffect'];  // MAX_ELIXER
    //dw ['EvoStoneEffect'];  // FIRE_STONE
    //dw ['EvoStoneEffect'];  // THUNDERSTONE
    //dw ['EvoStoneEffect'];  // WATER_STONE
    //dw ['NoEffect'];  // ITEM_19
    //dw ['VitaminEffect'];  // HP_UP
    //dw ['VitaminEffect'];  // PROTEIN
    //dw ['VitaminEffect'];  // IRON
    //dw ['VitaminEffect'];  // CARBOS
    //dw ['NoEffect'];  // LUCKY_PUNCH
    //dw ['VitaminEffect'];  // CALCIUM
    //dw ['RareCandyEffect'];  // RARE_CANDY
    //dw ['XAccuracyEffect'];  // X_ACCURACY
    //dw ['EvoStoneEffect'];  // LEAF_STONE
    //dw ['NoEffect'];  // METAL_POWDER
    //dw ['NoEffect'];  // NUGGET
    //dw ['PokeDollEffect'];  // POKE_DOLL
    //dw ['StatusHealingEffect'];  // FULL_HEAL
    //dw ['ReviveEffect'];  // REVIVE
    //dw ['ReviveEffect'];  // MAX_REVIVE
    //dw ['GuardSpecEffect'];  // GUARD_SPEC
    //dw ['SuperRepelEffect'];  // SUPER_REPEL
    //dw ['MaxRepelEffect'];  // MAX_REPEL
    //dw ['DireHitEffect'];  // DIRE_HIT
    //dw ['NoEffect'];  // ITEM_2D
    //dw ['RestoreHPEffect'];  // FRESH_WATER
    //dw ['RestoreHPEffect'];  // SODA_POP
    //dw ['RestoreHPEffect'];  // LEMONADE
    //dw ['XItemEffect'];  // X_ATTACK
    //dw ['NoEffect'];  // ITEM_32
    //dw ['XItemEffect'];  // X_DEFEND
    //dw ['XItemEffect'];  // X_SPEED
    //dw ['XItemEffect'];  // X_SPECIAL
    //dw ['CoinCaseEffect'];  // COIN_CASE
    //dw ['ItemfinderEffect'];  // ITEMFINDER
    //dw ['PokeFluteEffect'];  // POKE_FLUTE
    //dw ['NoEffect'];  // EXP_SHARE
    //dw ['OldRodEffect'];  // OLD_ROD
    //dw ['GoodRodEffect'];  // GOOD_ROD
    //dw ['NoEffect'];  // SILVER_LEAF
    //dw ['SuperRodEffect'];  // SUPER_ROD
    //dw ['RestorePPEffect'];  // PP_UP
    //dw ['RestorePPEffect'];  // ETHER
    //dw ['RestorePPEffect'];  // MAX_ETHER
    //dw ['RestorePPEffect'];  // ELIXER
    //dw ['NoEffect'];  // RED_SCALE
    //dw ['NoEffect'];  // SECRETPOTION
    //dw ['NoEffect'];  // S_S_TICKET
    //dw ['NoEffect'];  // MYSTERY_EGG
    //dw ['NoEffect'];  // CLEAR_BELL
    //dw ['NoEffect'];  // SILVER_WING
    //dw ['RestoreHPEffect'];  // MOOMOO_MILK
    //dw ['NoEffect'];  // QUICK_CLAW
    //dw ['StatusHealingEffect'];  // PSNCUREBERRY
    //dw ['NoEffect'];  // GOLD_LEAF
    //dw ['NoEffect'];  // SOFT_SAND
    //dw ['NoEffect'];  // SHARP_BEAK
    //dw ['StatusHealingEffect'];  // PRZCUREBERRY
    //dw ['StatusHealingEffect'];  // BURNT_BERRY
    //dw ['StatusHealingEffect'];  // ICE_BERRY
    //dw ['NoEffect'];  // POISON_BARB
    //dw ['NoEffect'];  // KINGS_ROCK
    //dw ['BitterBerryEffect'];  // BITTER_BERRY
    //dw ['StatusHealingEffect'];  // MINT_BERRY
    //dw ['NoEffect'];  // RED_APRICORN
    //dw ['NoEffect'];  // TINYMUSHROOM
    //dw ['NoEffect'];  // BIG_MUSHROOM
    //dw ['NoEffect'];  // SILVERPOWDER
    //dw ['NoEffect'];  // BLU_APRICORN
    //dw ['NoEffect'];  // ITEM_5A
    //dw ['NoEffect'];  // AMULET_COIN
    //dw ['NoEffect'];  // YLW_APRICORN
    //dw ['NoEffect'];  // GRN_APRICORN
    //dw ['NoEffect'];  // CLEANSE_TAG
    //dw ['NoEffect'];  // MYSTIC_WATER
    //dw ['NoEffect'];  // TWISTEDSPOON
    //dw ['NoEffect'];  // WHT_APRICORN
    //dw ['NoEffect'];  // BLACKBELT_I
    //dw ['NoEffect'];  // BLK_APRICORN
    //dw ['NoEffect'];  // ITEM_64
    //dw ['NoEffect'];  // PNK_APRICORN
    //dw ['NoEffect'];  // BLACKGLASSES
    //dw ['NoEffect'];  // SLOWPOKETAIL
    //dw ['NoEffect'];  // PINK_BOW
    //dw ['NoEffect'];  // STICK
    //dw ['NoEffect'];  // SMOKE_BALL
    //dw ['NoEffect'];  // NEVERMELTICE
    //dw ['NoEffect'];  // MAGNET
    //dw ['StatusHealingEffect'];  // MIRACLEBERRY
    //dw ['NoEffect'];  // PEARL
    //dw ['NoEffect'];  // BIG_PEARL
    //dw ['NoEffect'];  // EVERSTONE
    //dw ['NoEffect'];  // SPELL_TAG
    //dw ['RestoreHPEffect'];  // RAGECANDYBAR
    //dw ['NoEffect'];  // GS_BALL
    //dw ['BlueCardEffect'];  // BLUE_CARD
    //dw ['NoEffect'];  // MIRACLE_SEED
    //dw ['NoEffect'];  // THICK_CLUB
    //dw ['NoEffect'];  // FOCUS_BAND
    //dw ['NoEffect'];  // ITEM_78
    //dw ['EnergypowderEffect'];  // ENERGYPOWDER
    //dw ['EnergyRootEffect'];  // ENERGY_ROOT
    //dw ['HealPowderEffect'];  // HEAL_POWDER
    //dw ['RevivalHerbEffect'];  // REVIVAL_HERB
    //dw ['NoEffect'];  // HARD_STONE
    //dw ['NoEffect'];  // LUCKY_EGG
    //dw ['CardKeyEffect'];  // CARD_KEY
    //dw ['NoEffect'];  // MACHINE_PART
    //dw ['NoEffect'];  // EGG_TICKET
    //dw ['NoEffect'];  // LOST_ITEM
    //dw ['NoEffect'];  // STARDUST
    //dw ['NoEffect'];  // STAR_PIECE
    //dw ['BasementKeyEffect'];  // BASEMENT_KEY
    //dw ['NoEffect'];  // PASS
    //dw ['NoEffect'];  // ITEM_87
    //dw ['NoEffect'];  // ITEM_88
    //dw ['NoEffect'];  // ITEM_89
    //dw ['NoEffect'];  // CHARCOAL
    //dw ['RestoreHPEffect'];  // BERRY_JUICE
    //dw ['NoEffect'];  // SCOPE_LENS
    //dw ['NoEffect'];  // ITEM_8D
    //dw ['NoEffect'];  // ITEM_8E
    //dw ['NoEffect'];  // METAL_COAT
    //dw ['NoEffect'];  // DRAGON_FANG
    //dw ['NoEffect'];  // ITEM_91
    //dw ['NoEffect'];  // LEFTOVERS
    //dw ['NoEffect'];  // ITEM_93
    //dw ['NoEffect'];  // ITEM_94
    //dw ['NoEffect'];  // ITEM_95
    //dw ['RestorePPEffect'];  // MYSTERYBERRY
    //dw ['NoEffect'];  // DRAGON_SCALE
    //dw ['NoEffect'];  // BERSERK_GENE
    //dw ['NoEffect'];  // ITEM_99
    //dw ['NoEffect'];  // ITEM_9A
    //dw ['NoEffect'];  // ITEM_9B
    //dw ['SacredAshEffect'];  // SACRED_ASH
    //dw ['PokeBallEffect'];  // HEAVY_BALL
    //dw ['NoEffect'];  // FLOWER_MAIL
    //dw ['PokeBallEffect'];  // LEVEL_BALL
    //dw ['PokeBallEffect'];  // LURE_BALL
    //dw ['PokeBallEffect'];  // FAST_BALL
    //dw ['NoEffect'];  // ITEM_A2
    //dw ['NoEffect'];  // LIGHT_BALL
    //dw ['PokeBallEffect'];  // FRIEND_BALL
    //dw ['PokeBallEffect'];  // MOON_BALL
    //dw ['PokeBallEffect'];  // LOVE_BALL
    //dw ['NormalBoxEffect'];  // NORMAL_BOX
    //dw ['GorgeousBoxEffect'];  // GORGEOUS_BOX
    //dw ['EvoStoneEffect'];  // SUN_STONE
    //dw ['NoEffect'];  // POLKADOT_BOW
    //dw ['NoEffect'];  // ITEM_AB
    //dw ['NoEffect'];  // UP_GRADE
    //dw ['RestoreHPEffect'];  // BERRY
    //dw ['RestoreHPEffect'];  // GOLD_BERRY
    //dw ['SquirtbottleEffect'];  // SQUIRTBOTTLE
    //dw ['NoEffect'];  // ITEM_B0
    //dw ['PokeBallEffect'];  // PARK_BALL
    //dw ['NoEffect'];  // RAINBOW_WING
    //dw ['NoEffect'];  // ITEM_B3
    //assert_table_length ['ITEM_B3']
//  The items past ITEM_B3 do not have effect entries:
//     BRICK_PIECE
//     SURF_MAIL
//     LITEBLUEMAIL
//     PORTRAITMAIL
//     LOVELY_MAIL
//     EON_MAIL
//     MORPH_MAIL
//     BLUESKY_MAIL
//     MUSIC_MAIL
//     MIRAGE_MAIL
//     ITEM_BE
//  They all have the ITEMMENU_NOUSE attribute so they can't be used anyway.
//  NoEffect would be appropriate, with the table then being NUM_ITEMS long.

    return PokeBallEffect();
}

void PokeBallEffect(void){
    LD_A_addr(wBattleMode);
    DEC_A;
    JP_NZ (mUseBallInTrainerBattle);

    LD_A_addr(wPartyCount);
    CP_A(PARTY_LENGTH);
    IF_NZ goto room_in_party;

    LD_A(BANK(sBoxCount));
    CALL(aOpenSRAM);
    LD_A_addr(sBoxCount);
    CP_A(MONS_PER_BOX);
    CALL(aCloseSRAM);
    JP_Z (mBall_BoxIsFullMessage);


room_in_party:
    XOR_A_A;
    LD_addr_A(wWildMon);
    LD_A_addr(wCurItem);
    CP_A(PARK_BALL);
    CALL_NZ (aReturnToBattle_UseBall);

    LD_HL(wOptions);
    RES_hl(NO_TEXT_SCROLL);
    LD_HL(mItemUsedText);
    CALL(aPrintText);

    LD_A_addr(wEnemyMonCatchRate);
    LD_B_A;
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    JP_Z (mPokeBallEffect_catch_without_fail);
    LD_A_addr(wCurItem);
    CP_A(MASTER_BALL);
    JP_Z (mPokeBallEffect_catch_without_fail);
    LD_A_addr(wCurItem);
    LD_C_A;
    LD_HL(mBallMultiplierFunctionTable);


get_multiplier_loop:
    LD_A_hli;
    CP_A(0xff);
    IF_Z goto skip_or_return_from_ball_fn;
    CP_A_C;
    IF_Z goto call_ball_function;
    INC_HL;
    INC_HL;
    goto get_multiplier_loop;


call_ball_function:
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(mPokeBallEffect_skip_or_return_from_ball_fn);
    PUSH_DE;
    JP_hl;


skip_or_return_from_ball_fn:
    LD_A_addr(wCurItem);
    CP_A(LEVEL_BALL);
    LD_A_B;
    JP_Z (mPokeBallEffect_skip_hp_calc);

    LD_A_B;
    LDH_addr_A(hMultiplicand + 2);

    LD_HL(wEnemyMonHP);
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    INC_HL;
    LD_D_hl;
    INC_HL;
    LD_E_hl;
    SLA_C;
    RL_B;

    LD_H_D;
    LD_L_E;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    LD_A_D;
    AND_A_A;
    IF_Z goto okay_1;

    SRL_D;
    RR_E;
    SRL_D;
    RR_E;
    SRL_B;
    RR_C;
    SRL_B;
    RR_C;

    LD_A_C;
    AND_A_A;
    IF_NZ goto okay_1;
    LD_C(0x1);

okay_1:
    LD_B_E;

    PUSH_BC;
    LD_A_B;
    SUB_A_C;
    LDH_addr_A(hMultiplier);
    XOR_A_A;
    LDH_addr_A(hDividend + 0);
    LDH_addr_A(hMultiplicand + 0);
    LDH_addr_A(hMultiplicand + 1);
    CALL(aMultiply);
    POP_BC;

    LD_A_B;
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);

    LDH_A_addr(hQuotient + 3);
    AND_A_A;
    IF_NZ goto statuscheck;
    LD_A(1);

statuscheck:
//  This routine is buggy. It was intended that SLP and FRZ provide a higher
//  catch rate than BRN/PSN/PAR, which in turn provide a higher catch rate than
//  no status effect at all. But instead, it makes BRN/PSN/PAR provide no
//  benefit.
//  Uncomment the line below to fix this.
    LD_B_A;
    LD_A_addr(wEnemyMonStatus);
    AND_A(1 << FRZ | SLP);
    LD_C(10);
    IF_NZ goto addstatus;
// ld a, [wEnemyMonStatus]
    AND_A_A;
    LD_C(5);
    IF_NZ goto addstatus;
    LD_C(0);

addstatus:
    LD_A_B;
    ADD_A_C;
    IF_NC goto max_1;
    LD_A(0xff);

max_1:

// BUG: farcall overwrites a, and GetItemHeldEffect takes b anyway.
// This is probably the reason the HELD_CATCH_CHANCE effect is never used.
// Uncomment the line below to fix.
    LD_D_A;
    PUSH_DE;
    LD_A_addr(wBattleMonItem);
// ld b, a
    FARCALL(aGetItemHeldEffect);
    LD_A_B;
    CP_A(HELD_CATCH_CHANCE);
    POP_DE;
    LD_A_D;
    IF_NZ goto max_2;
    ADD_A_C;
    IF_NC goto max_2;
    LD_A(0xff);

max_2:


skip_hp_calc:
    LD_B_A;
    LD_addr_A(wFinalCatchRate);
    CALL(aRandom);

    CP_A_B;
    LD_A(0);
    IF_Z goto catch_without_fail;
    IF_NC goto fail_to_catch;


catch_without_fail:
    LD_A_addr(wEnemyMonSpecies);


fail_to_catch:
    LD_addr_A(wWildMon);
    LD_C(20);
    CALL(aDelayFrames);

    LD_A_addr(wCurItem);
    CP_A(POKE_BALL + 1);  // Assumes Master/Ultra/Great come before
    IF_C goto not_kurt_ball;
    LD_A(POKE_BALL);

not_kurt_ball:
    LD_addr_A(wBattleAnimParam);

    LD_DE(ANIM_THROW_POKE_BALL);
    LD_A_E;
    LD_addr_A(wFXAnimID);
    LD_A_D;
    LD_addr_A(wFXAnimID + 1);
    XOR_A_A;
    LDH_addr_A(hBattleTurn);
    LD_addr_A(wThrownBallWobbleCount);
    LD_addr_A(wNumHits);
    PREDEF(pPlayBattleAnim);

    LD_A_addr(wWildMon);
    AND_A_A;
    IF_NZ goto caught;
    LD_A_addr(wThrownBallWobbleCount);
    CP_A(1);
    LD_HL(mBallBrokeFreeText);
    JP_Z (mPokeBallEffect_shake_and_break_free);
    CP_A(2);
    LD_HL(mBallAppearedCaughtText);
    JP_Z (mPokeBallEffect_shake_and_break_free);
    CP_A(3);
    LD_HL(mBallAlmostHadItText);
    JP_Z (mPokeBallEffect_shake_and_break_free);
    CP_A(4);
    LD_HL(mBallSoCloseText);
    JP_Z (mPokeBallEffect_shake_and_break_free);


caught:
    LD_HL(wEnemyMonStatus);
    LD_A_hli;
    PUSH_AF;
    INC_HL;
    LD_A_hli;
    PUSH_AF;
    LD_A_hl;
    PUSH_AF;
    PUSH_HL;
    LD_HL(wEnemyMonItem);
    LD_A_hl;
    PUSH_AF;
    PUSH_HL;
    LD_HL(wEnemySubStatus5);
    LD_A_hl;
    PUSH_AF;
    SET_hl(SUBSTATUS_TRANSFORMED);

//  This code is buggy. Any wild Pokémon that has Transformed will be
//  caught as a Ditto, even if it was something else like Mew.
//  To fix, do not set [wTempEnemyMonSpecies] to DITTO.
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_NZ goto ditto;
    goto not_ditto;


ditto:
    LD_A(DITTO);
    LD_addr_A(wTempEnemyMonSpecies);
    goto load_data;


not_ditto:
    SET_hl(SUBSTATUS_TRANSFORMED);
    LD_HL(wEnemyBackupDVs);
    LD_A_addr(wEnemyMonDVs);
    LD_hli_A;
    LD_A_addr(wEnemyMonDVs + 1);
    LD_hl_A;


load_data:
    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A_addr(wEnemyMonLevel);
    LD_addr_A(wCurPartyLevel);
    FARCALL(aLoadEnemyMon);

    POP_AF;
    LD_addr_A(wEnemySubStatus5);

    POP_HL;
    POP_AF;
    LD_hl_A;
    POP_HL;
    POP_AF;
    LD_hld_A;
    POP_AF;
    LD_hld_A;
    DEC_HL;
    POP_AF;
    LD_hl_A;

    LD_HL(wEnemySubStatus5);
    BIT_hl(SUBSTATUS_TRANSFORMED);
    IF_NZ goto Transformed;
    LD_HL(wWildMonMoves);
    LD_DE(wEnemyMonMoves);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);

    LD_HL(wWildMonPP);
    LD_DE(wEnemyMonPP);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);


Transformed:
    LD_A_addr(wEnemyMonSpecies);
    LD_addr_A(wWildMon);
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wTempSpecies);
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    JP_Z (mPokeBallEffect_FinishTutorial);

    FARCALL(aStubbedTrainerRankings_WildMonsCaught);

    LD_HL(mText_GotchaMonWasCaught);
    CALL(aPrintText);

    CALL(aClearSprites);

    LD_A_addr(wTempSpecies);
    DEC_A;
    CALL(aCheckCaughtMon);

    LD_A_C;
    PUSH_AF;
    LD_A_addr(wTempSpecies);
    DEC_A;
    CALL(aSetSeenAndCaughtMon);
    POP_AF;
    AND_A_A;
    IF_NZ goto skip_pokedex;

    CALL(aCheckReceivedDex);
    IF_Z goto skip_pokedex;

    LD_HL(mNewDexDataText);
    CALL(aPrintText);

    CALL(aClearSprites);

    LD_A_addr(wEnemyMonSpecies);
    LD_addr_A(wTempSpecies);
    PREDEF(pNewPokedexEntry);


skip_pokedex:
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_CONTEST);
    JP_Z (mPokeBallEffect_catch_bug_contest_mon);
    CP_A(BATTLETYPE_CELEBI);
    IF_NZ goto not_celebi;
    LD_HL(wBattleResult);
    SET_hl(BATTLERESULT_CAUGHT_CELEBI);

not_celebi:

    LD_A_addr(wPartyCount);
    CP_A(PARTY_LENGTH);
    IF_Z goto SendToPC;

    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    CALL(aClearSprites);

    PREDEF(pTryAddMonToParty);

    FARCALL(aSetCaughtData);

    LD_A_addr(wCurItem);
    CP_A(FRIEND_BALL);
    IF_NZ goto SkipPartyMonFriendBall;

    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1Happiness);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);

    LD_A(FRIEND_BALL_HAPPINESS);
    LD_hl_A;


SkipPartyMonFriendBall:
    LD_HL(mAskGiveNicknameText);
    CALL(aPrintText);

    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);

    CALL(aYesNoBox);
    JP_C (mPokeBallEffect_return_from_capture);

    LD_A_addr(wPartyCount);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    CALL(aAddNTimes);

    LD_D_H;
    LD_E_L;
    PUSH_DE;
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    LD_B(NAME_MON);
    FARCALL(aNamingScreen);

    CALL(aRotateThreePalettesRight);

    CALL(aLoadStandardFont);

    POP_HL;
    LD_DE(wStringBuffer1);
    CALL(aInitName);

    JP(mPokeBallEffect_return_from_capture);


SendToPC:
    CALL(aClearSprites);

    PREDEF(pSendMonIntoBox);

    FARCALL(aSetBoxMonCaughtData);

    LD_A(BANK(sBoxCount));
    CALL(aOpenSRAM);

    LD_A_addr(sBoxCount);
    CP_A(MONS_PER_BOX);
    IF_NZ goto BoxNotFullYet;
    LD_HL(wBattleResult);
    SET_hl(BATTLERESULT_BOX_FULL);

BoxNotFullYet:
    LD_A_addr(wCurItem);
    CP_A(FRIEND_BALL);
    IF_NZ goto SkipBoxMonFriendBall;
// The captured mon is now first in the box
    LD_A(FRIEND_BALL_HAPPINESS);
    LD_addr_A(sBoxMon1Happiness);

SkipBoxMonFriendBall:
    CALL(aCloseSRAM);

    LD_HL(mAskGiveNicknameText);
    CALL(aPrintText);

    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);

    CALL(aYesNoBox);
    IF_C goto SkipBoxMonNickname;

    XOR_A_A;
    LD_addr_A(wCurPartyMon);
    LD_A(BOXMON);
    LD_addr_A(wMonType);
    LD_DE(wMonOrItemNameBuffer);
    LD_B(NAME_MON);
    FARCALL(aNamingScreen);

    LD_A(BANK(sBoxMonNicknames));
    CALL(aOpenSRAM);

    LD_HL(wMonOrItemNameBuffer);
    LD_DE(sBoxMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);

    LD_HL(sBoxMonNicknames);
    LD_DE(wStringBuffer1);
    CALL(aInitName);

    CALL(aCloseSRAM);


SkipBoxMonNickname:
    LD_A(BANK(sBoxMonNicknames));
    CALL(aOpenSRAM);

    LD_HL(sBoxMonNicknames);
    LD_DE(wMonOrItemNameBuffer);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);

    CALL(aCloseSRAM);

    LD_HL(mBallSentToPCText);
    CALL(aPrintText);

    CALL(aRotateThreePalettesRight);
    CALL(aLoadStandardFont);
    goto return_from_capture;


catch_bug_contest_mon:
    FARCALL(aBugContest_SetCaughtContestMon);
    goto return_from_capture;


FinishTutorial:
    LD_HL(mText_GotchaMonWasCaught);


shake_and_break_free:
    CALL(aPrintText);
    CALL(aClearSprites);


return_from_capture:
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    RET_Z ;
    CP_A(BATTLETYPE_DEBUG);
    RET_Z ;
    CP_A(BATTLETYPE_CONTEST);
    IF_Z goto used_park_ball;

    LD_A_addr(wWildMon);
    AND_A_A;
    IF_Z goto toss;

    CALL(aClearBGPalettes);
    CALL(aClearTilemap);


toss:
    LD_HL(wNumItems);
    INC_A;
    LD_addr_A(wItemQuantityChange);
    JP(mTossItem);


used_park_ball:
    LD_HL(wParkBallsRemaining);
    DEC_hl;
    RET;

}

void BallMultiplierFunctionTable(void){
//  table of routines that increase or decrease the catch rate based on
//  which ball is used in a certain situation.
    //dbw ['ULTRA_BALL', 'UltraBallMultiplier']
    //dbw ['GREAT_BALL', 'GreatBallMultiplier']
    //dbw ['SAFARI_BALL', 'SafariBallMultiplier']  // Safari Ball, leftover from RBY
    //dbw ['HEAVY_BALL', 'HeavyBallMultiplier']
    //dbw ['LEVEL_BALL', 'LevelBallMultiplier']
    //dbw ['LURE_BALL', 'LureBallMultiplier']
    //dbw ['FAST_BALL', 'FastBallMultiplier']
    //dbw ['MOON_BALL', 'MoonBallMultiplier']
    //dbw ['LOVE_BALL', 'LoveBallMultiplier']
    //dbw ['PARK_BALL', 'ParkBallMultiplier']
    //db ['-1'];  // end

    return UltraBallMultiplier();
}

void UltraBallMultiplier(void){
//  multiply catch rate by 2
    SLA_B;
    RET_NC ;
    LD_B(0xff);
    RET;

}

void SafariBallMultiplier(void){
    return GreatBallMultiplier();
}

void GreatBallMultiplier(void){
    return ParkBallMultiplier();
}

void ParkBallMultiplier(void){
//  multiply catch rate by 1.5
    LD_A_B;
    SRL_A;
    ADD_A_B;
    LD_B_A;
    RET_NC ;
    LD_B(0xff);
    RET;

}

void GetPokedexEntryBank(void){
//  This function is buggy.
//  It gets the wrong bank for Kadabra (64), Tauros (128), and Sunflora (192).
//  Uncomment the line below to fix this.
    PUSH_HL;
    PUSH_DE;
    LD_A_addr(wEnemyMonSpecies);
// dec a
    RLCA;
    RLCA;
    maskbits(NUM_DEX_ENTRY_BANKS, 0);
    LD_HL(mGetPokedexEntryBank_PokedexEntryBanks);
    LD_D(0);
    LD_E_A;
    ADD_HL_DE;
    LD_A_hl;
    POP_DE;
    POP_HL;
    RET;


PokedexEntryBanks:
    //db ['BANK("Pokedex Entries 001-064")'];
    //db ['BANK("Pokedex Entries 065-128")'];
    //db ['BANK("Pokedex Entries 129-192")'];
    //db ['BANK("Pokedex Entries 193-251")'];

    return HeavyBallMultiplier();
}

void HeavyBallMultiplier(void){
//  subtract 20 from catch rate if weight < 102.4 kg
//  else add 0 to catch rate if weight < 204.8 kg
//  else add 20 to catch rate if weight < 307.2 kg
//  else add 30 to catch rate if weight < 409.6 kg
//  else add 40 to catch rate (never happens)
    LD_A_addr(wEnemyMonSpecies);
    LD_HL(mPokedexDataPointerTable);
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A(BANK(aPokedexDataPointerTable));
    CALL(aGetFarWord);


SkipText:
    CALL(aGetPokedexEntryBank);
    CALL(aGetFarByte);
    INC_HL;
    CP_A(0x50);
    IF_NZ goto SkipText;

    CALL(aGetPokedexEntryBank);
    PUSH_BC;
    INC_HL;
    INC_HL;
    CALL(aGetFarWord);

    SRL_H;
    RR_L;
    LD_B_H;
    LD_C_L;

    for(int rept = 0; rept < 4; rept++){
    SRL_B;
    RR_C;
    }
    CALL(aHeavyBallMultiplier_subbc);

    SRL_B;
    RR_C;
    CALL(aHeavyBallMultiplier_subbc);

    LD_A_H;
    POP_BC;
    goto compare;


subbc:
// subtract bc from hl
    PUSH_BC;
    LD_A_B;
    CPL;
    LD_B_A;
    LD_A_C;
    CPL;
    LD_C_A;
    INC_BC;
    ADD_HL_BC;
    POP_BC;
    RET;


compare:
    LD_C_A;
    CP_A(HIGH(1024));  // 102.4 kg
    IF_C goto lightmon;

    LD_HL(mHeavyBallMultiplier_WeightsTable);

lookup:
    LD_A_C;
    CP_A_hl;
    IF_C goto heavymon;
    INC_HL;
    INC_HL;
    goto lookup;


heavymon:
    INC_HL;
    LD_A_B;
    ADD_A_hl;
    LD_B_A;
    RET_NC ;
    LD_B(0xff);
    RET;


lightmon:
    LD_A_B;
    SUB_A(20);
    LD_B_A;
    RET_NC ;
    LD_B(0x1);
    RET;


WeightsTable:
//  weight factor, boost
    //db ['HIGH(2048)', '0'];
    //db ['HIGH(3072)', '20'];
    //db ['HIGH(4096)', '30'];
    //db ['HIGH(65280)', '40'];

    return LureBallMultiplier();
}

void LureBallMultiplier(void){
//  multiply catch rate by 3 if this is a fishing rod battle
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_FISH);
    RET_NZ ;

    LD_A_B;
    ADD_A_A;
    IF_C goto max;

    ADD_A_B;
    IF_NC goto done;

max:
    LD_A(0xff);

done:
    LD_B_A;
    RET;

}

void MoonBallMultiplier(void){
//  This function is buggy.
//  Intent:  multiply catch rate by 4 if mon evolves with moon stone
//  Reality: no boost
    PUSH_BC;
    LD_A_addr(wTempEnemyMonSpecies);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mEvosAttacksPointers);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A(BANK(aEvosAttacksPointers));
    CALL(aGetFarWord);
    POP_BC;

    PUSH_BC;
    // LD_A(BANK("Evolutions and Attacks"));
    CALL(aGetFarByte);
    CP_A(EVOLVE_ITEM);
    POP_BC;
    RET_NZ ;

    INC_HL;
    INC_HL;
    INC_HL;

//  Moon Stone's constant from Pokémon Red is used.
//  No Pokémon evolve with Burn Heal,
//  so Moon Balls always have a catch rate of 1×.
    PUSH_BC;
    // LD_A(BANK("Evolutions and Attacks"));
    CALL(aGetFarByte);
    CP_A(MOON_STONE_RED);  // BURN_HEAL
    POP_BC;
    RET_NZ ;

    SLA_B;
    IF_C goto max;
    SLA_B;
    IF_NC goto done;

max:
    LD_B(0xff);

done:
    RET;

}

void LoveBallMultiplier(void){
//  This function is buggy.
//  Intent:  multiply catch rate by 8 if mons are of same species, different sex
//  Reality: multiply catch rate by 8 if mons are of same species, same sex

// does species match?
    LD_A_addr(wTempEnemyMonSpecies);
    LD_C_A;
    LD_A_addr(wTempBattleMonSpecies);
    CP_A_C;
    RET_NZ ;

// check player mon species
    PUSH_BC;
    LD_A_addr(wTempBattleMonSpecies);
    LD_addr_A(wCurPartySpecies);
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    LD_A_addr(wCurBattleMon);
    LD_addr_A(wCurPartyMon);
    FARCALL(aGetGender);
    IF_C goto done1;  // no effect on genderless

    LD_D(0);  // male
    IF_NZ goto playermale;
    INC_D;  // female

playermale:

// check wild mon species
    PUSH_DE;
    LD_A_addr(wTempEnemyMonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A(WILDMON);
    LD_addr_A(wMonType);
    FARCALL(aGetGender);
    IF_C goto done2;  // no effect on genderless

    LD_D(0);  // male
    IF_NZ goto wildmale;
    INC_D;  // female

wildmale:

    LD_A_D;
    POP_DE;
    CP_A_D;
    POP_BC;
    RET_NZ ;  // for the intended effect, this should be "ret z"

    SLA_B;
    IF_C goto max;
    SLA_B;
    IF_C goto max;
    SLA_B;
    RET_NC ;

max:
    LD_B(0xff);
    RET;


done2:
    POP_DE;


done1:
    POP_BC;
    RET;

}

void FastBallMultiplier(void){
//  This function is buggy.
//  Intent:  multiply catch rate by 4 if enemy mon is in one of the three
//           FleeMons tables.
//  Reality: multiply catch rate by 4 if enemy mon is one of the first three in
//           the first FleeMons table.
    LD_A_addr(wTempEnemyMonSpecies);
    LD_C_A;
    LD_HL(mFleeMons);
    LD_D(3);


loop:
    LD_A(BANK(aFleeMons));
    CALL(aGetFarByte);

    INC_HL;
    CP_A(-1);
    IF_Z goto next;
    CP_A_C;
    IF_NZ goto next;  // for the intended effect, this should be "jr nz, .loop"
    SLA_B;
    IF_C goto max;

    SLA_B;
    RET_NC ;


max:
    LD_B(0xff);
    RET;


next:
    DEC_D;
    IF_NZ goto loop;
    RET;

}

void LevelBallMultiplier(void){
//  multiply catch rate by 8 if player mon level / 4 > enemy mon level
//  multiply catch rate by 4 if player mon level / 2 > enemy mon level
//  multiply catch rate by 2 if player mon level > enemy mon level
    LD_A_addr(wBattleMonLevel);
    LD_C_A;
    LD_A_addr(wEnemyMonLevel);
    CP_A_C;
    RET_NC ;  // if player is lower level, we're done here
    SLA_B;
    IF_C goto max;

    SRL_C;
    CP_A_C;
    RET_NC ;  // if player/2 is lower level, we're done here
    SLA_B;
    IF_C goto max;

    SRL_C;
    CP_A_C;
    RET_NC ;  // if player/4 is lower level, we're done here
    SLA_B;
    RET_NC ;


max:
    LD_B(0xff);
    RET;

//  BallDodgedText and BallMissedText were used in Gen 1.

    return BallDodgedText();
}

void BallDodgedText(void){
//  //  unreferenced
    //text_far ['_BallDodgedText']
    //text_end ['?']

    return BallMissedText();
}

void BallMissedText(void){
//  //  unreferenced
    //text_far ['_BallMissedText']
    //text_end ['?']

    return BallBrokeFreeText();
}

void BallBrokeFreeText(void){
    //text_far ['_BallBrokeFreeText']
    //text_end ['?']

    return BallAppearedCaughtText();
}

void BallAppearedCaughtText(void){
    //text_far ['_BallAppearedCaughtText']
    //text_end ['?']

    return BallAlmostHadItText();
}

void BallAlmostHadItText(void){
    //text_far ['_BallAlmostHadItText']
    //text_end ['?']

    return BallSoCloseText();
}

void BallSoCloseText(void){
    //text_far ['_BallSoCloseText']
    //text_end ['?']

    return Text_GotchaMonWasCaught();
}

void Text_GotchaMonWasCaught(void){
// Gotcha! @ was caught!@ @
    //text_far ['Text_BallCaught']
    //text_asm ['?']
    CALL(aWaitSFX);
    PUSH_BC;
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    CALL(aDelayFrame);
    LD_DE(MUSIC_CAPTURE);
    CALL(aPlayMusic);
    POP_BC;
    LD_HL(mWaitButtonText);
    RET;

}

void WaitButtonText(void){
    //text_far ['_WaitButtonText']
    //text_end ['?']

    return BallSentToPCText();
}

void BallSentToPCText(void){
    //text_far ['_BallSentToPCText']
    //text_end ['?']

    return NewDexDataText();
}

void NewDexDataText(void){
    //text_far ['_NewDexDataText']
    //text_end ['?']

    return AskGiveNicknameText();
}

void AskGiveNicknameText(void){
    //text_far ['_AskGiveNicknameText']
    //text_end ['?']

    return ReturnToBattle_UseBall();
}

void ReturnToBattle_UseBall(void){
    FARCALL(av_ReturnToBattle_UseBall);
    RET;

}

void TownMapEffect(void){
    FARCALL(aPokegearMap);
    RET;

}

void BicycleEffect(void){
    FARCALL(aBikeFunction);
    RET;

}

void EvoStoneEffect(void){
    LD_B(PARTYMENUACTION_EVO_STONE);
    CALL(aUseItem_SelectMon);

    JP_C (mEvoStoneEffect_DecidedNotToUse);

    LD_A(MON_ITEM);
    CALL(aGetPartyParamLocation);

    LD_A_hl;
    CP_A(EVERSTONE);
    IF_Z goto NoEffect;

    LD_A(TRUE);
    LD_addr_A(wForceEvolution);
    FARCALL(aEvolvePokemon);

    LD_A_addr(wMonTriedToEvolve);
    AND_A_A;
    IF_Z goto NoEffect;

    JP(mUseDisposableItem);


NoEffect:
    CALL(aWontHaveAnyEffectMessage);


DecidedNotToUse:
    XOR_A_A;
    LD_addr_A(wItemEffectSucceeded);
    RET;

}

void VitaminEffect(void){
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);

    JP_C (mRareCandy_StatBooster_ExitMenu);

    CALL(aRareCandy_StatBooster_GetParameters);

    CALL(aGetStatExpRelativePointer);

    LD_A(MON_STAT_EXP);
    CALL(aGetPartyParamLocation);

    ADD_HL_BC;
    LD_A_hl;
    CP_A(100);
    JR_NC (mNoEffectMessage);

    ADD_A(10);
    LD_hl_A;
    CALL(aUpdateStatsAfterItem);

    CALL(aGetStatExpRelativePointer);

    LD_HL(mStatStrings);
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wStringBuffer2);
    LD_BC(ITEM_NAME_LENGTH);
    CALL(aCopyBytes);

    CALL(aPlay_SFX_FULL_HEAL);

    LD_HL(mItemStatRoseText);
    CALL(aPrintText);

    LD_C(HAPPINESS_USEDITEM);
    FARCALL(aChangeHappiness);

    JP(mUseDisposableItem);

}

void NoEffectMessage(void){
    LD_HL(mItemWontHaveEffectText);
    CALL(aPrintText);
    JP(mClearPalettes);

}

void UpdateStatsAfterItem(void){
    LD_A(MON_MAXHP);
    CALL(aGetPartyParamLocation);
    LD_D_H;
    LD_E_L;
    LD_A(MON_STAT_EXP - 1);
    CALL(aGetPartyParamLocation);
    LD_B(TRUE);
    PREDEF_JUMP(pCalcMonStats);

    return RareCandy_StatBooster_ExitMenu();
}

void RareCandy_StatBooster_ExitMenu(void){
    XOR_A_A;
    LD_addr_A(wItemEffectSucceeded);
    JP(mClearPalettes);

}

void ItemStatRoseText(void){
    //text_far ['_ItemStatRoseText']
    //text_end ['?']

    return StatStrings();
}

void StatStrings(void){
    //dw ['.health'];
    //dw ['.attack'];
    //dw ['.defense'];
    //dw ['.speed'];
    //dw ['.special'];


health:
//  db "HEALTH@"

attack:
//  db "ATTACK@"

defense:
// db "DEFENSE@"

speed:
//   db "SPEED@"

special:
// db "SPECIAL@"

    return GetStatExpRelativePointer();
}

void GetStatExpRelativePointer(void){
    LD_A_addr(wCurItem);
    LD_HL(mStatExpItemPointerOffsets);

next:
    CP_A_hl;
    INC_HL;
    IF_Z goto got_it;
    INC_HL;
    goto next;


got_it:
    LD_A_hl;
    LD_C_A;
    LD_B(0);
    RET;

}

void StatExpItemPointerOffsets(void){
    //db ['HP_UP', 'MON_HP_EXP - MON_STAT_EXP'];
    //db ['PROTEIN', 'MON_ATK_EXP - MON_STAT_EXP'];
    //db ['IRON', 'MON_DEF_EXP - MON_STAT_EXP'];
    //db ['CARBOS', 'MON_SPD_EXP - MON_STAT_EXP'];
    //db ['CALCIUM', 'MON_SPC_EXP - MON_STAT_EXP'];

    return RareCandy_StatBooster_GetParameters();
}

void RareCandy_StatBooster_GetParameters(void){
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    LD_addr_A(wTempSpecies);
    LD_A(MON_LEVEL);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    LD_addr_A(wCurPartyLevel);
    CALL(aGetBaseData);
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    CALL(aGetNickname);
    RET;

}

void RareCandyEffect(void){
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);

    JP_C (mRareCandy_StatBooster_ExitMenu);

    CALL(aRareCandy_StatBooster_GetParameters);

    LD_A(MON_LEVEL);
    CALL(aGetPartyParamLocation);

    LD_A_hl;
    CP_A(MAX_LEVEL);
    JP_NC (mNoEffectMessage);

    INC_A;
    LD_hl_A;
    LD_addr_A(wCurPartyLevel);
    PUSH_DE;
    LD_D_A;
    FARCALL(aCalcExpAtLevel);

    POP_DE;
    LD_A(MON_EXP);
    CALL(aGetPartyParamLocation);

    LDH_A_addr(hMultiplicand + 0);
    LD_hli_A;
    LDH_A_addr(hMultiplicand + 1);
    LD_hli_A;
    LDH_A_addr(hMultiplicand + 2);
    LD_hl_A;

    LD_A(MON_MAXHP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_B_A;
    LD_C_hl;
    PUSH_BC;
    CALL(aUpdateStatsAfterItem);

    LD_A(MON_MAXHP + 1);
    CALL(aGetPartyParamLocation);

    POP_BC;
    LD_A_hld;
    SUB_A_C;
    LD_C_A;
    LD_A_hl;
    SBC_A_B;
    LD_B_A;
    DEC_HL;
    LD_A_hl;
    ADD_A_C;
    LD_hld_A;
    LD_A_hl;
    ADC_A_B;
    LD_hl_A;
    FARCALL(aLevelUpHappinessMod);

    LD_A(PARTYMENUTEXT_LEVEL_UP);
    CALL(aItemActionText);

    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    PREDEF(pCopyMonToTempMon);

    hlcoord(9, 0, wTilemap);
    LD_B(10);
    LD_C(9);
    CALL(aTextbox);

    hlcoord(11, 1, wTilemap);
    LD_BC(4);
    PREDEF(pPrintTempMonStats);

    CALL(aWaitPressAorB_BlinkCursor);

    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wTempSpecies);
    PREDEF(pLearnLevelMoves);

    XOR_A_A;
    LD_addr_A(wForceEvolution);
    FARCALL(aEvolvePokemon);

    JP(mUseDisposableItem);

}

void HealPowderEffect(void){
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);

    JP_C (mStatusHealer_ExitMenu);

    CALL(aUseStatusHealer);
    CP_A(FALSE);
    IF_NZ goto not_used;

    LD_C(HAPPINESS_BITTERPOWDER);
    FARCALL(aChangeHappiness);
    CALL(aLooksBitterMessage);

    LD_A(0x0);


not_used:
    JP(mStatusHealer_Jumptable);

}

void StatusHealingEffect(void){
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);
    JP_C (mStatusHealer_ExitMenu);

    return FullyHealStatus();
}

void FullyHealStatus(void){
    CALL(aUseStatusHealer);
    JP(mStatusHealer_Jumptable);

}

void UseStatusHealer(void){
    CALL(aIsMonFainted);
    LD_A(TRUE);
    RET_Z ;
    CALL(aGetItemHealingAction);
    LD_A(MON_STATUS);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    AND_A_C;
    IF_NZ goto good;
    CALL(aIsItemUsedOnConfusedMon);
    LD_A(TRUE);
    RET_NC ;
    LD_B(PARTYMENUTEXT_HEAL_CONFUSION);

good:
    XOR_A_A;
    LD_hl_A;
    LD_A_B;
    LD_addr_A(wPartyMenuActionText);
    CALL(aHealStatus);
    CALL(aPlay_SFX_FULL_HEAL);
    CALL(aItemActionTextWaitButton);
    CALL(aUseDisposableItem);
    LD_A(FALSE);
    RET;

}

void IsItemUsedOnConfusedMon(void){
    CALL(aIsItemUsedOnBattleMon);
    IF_NC goto nope;
    LD_A_addr(wPlayerSubStatus3);
    BIT_A(SUBSTATUS_CONFUSED);
    IF_Z goto nope;
    LD_A_C;
    CP_A(0xff);
    IF_NZ goto nope;
    SCF;
    RET;


nope:
    AND_A_A;
    RET;

}

void BattlemonRestoreHealth(void){
    CALL(aIsItemUsedOnBattleMon);
    RET_NC ;
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_addr_A(wBattleMonHP);
    LD_A_hld;
    LD_addr_A(wBattleMonHP + 1);
    RET;

}

void HealStatus(void){
    CALL(aIsItemUsedOnBattleMon);
    RET_NC ;
    XOR_A_A;
    LD_addr_A(wBattleMonStatus);
    LD_HL(wPlayerSubStatus5);
    RES_hl(SUBSTATUS_TOXIC);
    LD_HL(wPlayerSubStatus1);
    RES_hl(SUBSTATUS_NIGHTMARE);
    CALL(aGetItemHealingAction);
    LD_A_C;
    CP_A(0b11111111);
    IF_NZ goto not_full_heal;
    LD_HL(wPlayerSubStatus3);
    RES_hl(SUBSTATUS_CONFUSED);

not_full_heal:
    PUSH_BC;
    FARCALL(aCalcPlayerStats);
    POP_BC;
    RET;

}

void GetItemHealingAction(void){
    PUSH_HL;
    LD_A_addr(wCurItem);
    LD_HL(mStatusHealingActions);
    LD_BC(3);

next:
    CP_A_hl;
    IF_Z goto found_it;
    ADD_HL_BC;
    goto next;


found_it:
    INC_HL;
    LD_B_hl;
    INC_HL;
    LD_A_hl;
    LD_C_A;
    CP_A(0b11111111);
    POP_HL;
    RET;

// INCLUDE "data/items/heal_status.asm"

    return StatusHealer_Jumptable();
}

void StatusHealer_Jumptable(void){
    LD_HL(mStatusHealer_Jumptable_dw);
    RST(aJumpTable);
    RET;


dw:
    //dw ['StatusHealer_ClearPalettes'];
    //dw ['StatusHealer_NoEffect'];
    //dw ['StatusHealer_ExitMenu'];

    return RevivalHerbEffect();
}

void RevivalHerbEffect(void){
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);
    JP_C (mStatusHealer_ExitMenu);

    CALL(aRevivePokemon);
    CP_A(FALSE);
    IF_NZ goto not_used;

    LD_C(HAPPINESS_REVIVALHERB);
    FARCALL(aChangeHappiness);
    CALL(aLooksBitterMessage);

    LD_A(0x0);


not_used:
    JP(mStatusHealer_Jumptable);

}

void ReviveEffect(void){
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);
    JP_C (mStatusHealer_ExitMenu);

    CALL(aRevivePokemon);
    JP(mStatusHealer_Jumptable);

}

void RevivePokemon(void){
    CALL(aIsMonFainted);
    LD_A(TRUE);
    RET_NZ ;
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_Z goto skip_to_revive;

    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_D(0);
    LD_HL(wBattleParticipantsIncludingFainted);
    LD_B(CHECK_FLAG);
    PREDEF(pSmallFarFlagAction);
    LD_A_C;
    AND_A_A;
    IF_Z goto skip_to_revive;

    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_HL(wBattleParticipantsNotFainted);
    LD_B(SET_FLAG);
    PREDEF(pSmallFarFlagAction);


skip_to_revive:
    XOR_A_A;
    LD_addr_A(wLowHealthAlarm);
    LD_A_addr(wCurItem);
    CP_A(REVIVE);
    IF_Z goto revive_half_hp;

    CALL(aReviveFullHP);
    goto finish_revive;


revive_half_hp:
    CALL(aReviveHalfHP);


finish_revive:
    CALL(aHealHP_SFX_GFX);
    LD_A(PARTYMENUTEXT_REVIVE);
    LD_addr_A(wPartyMenuActionText);
    CALL(aItemActionTextWaitButton);
    CALL(aUseDisposableItem);
    LD_A(FALSE);
    RET;

}

void FullRestoreEffect(void){
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);
    JP_C (mStatusHealer_ExitMenu);

    CALL(aIsMonFainted);
    JP_Z (mStatusHealer_NoEffect);

    CALL(aIsMonAtFullHealth);
    IF_C goto NotAtFullHealth;

    JP(mFullyHealStatus);


NotAtFullHealth:
    CALL(aFullRestoreEffect_FullRestore);
    JP(mStatusHealer_Jumptable);


FullRestore:
    XOR_A_A;
    LD_addr_A(wLowHealthAlarm);
    CALL(aReviveFullHP);
    LD_A(MON_STATUS);
    CALL(aGetPartyParamLocation);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    CALL(aHealStatus);
    CALL(aBattlemonRestoreHealth);
    CALL(aHealHP_SFX_GFX);
    LD_A(PARTYMENUTEXT_HEAL_HP);
    LD_addr_A(wPartyMenuActionText);
    CALL(aItemActionTextWaitButton);
    CALL(aUseDisposableItem);
    LD_A(0);
    RET;

}

void BitterBerryEffect(void){
    LD_HL(wPlayerSubStatus3);
    BIT_hl(SUBSTATUS_CONFUSED);
    LD_A(1);
    IF_Z goto done;

    RES_hl(SUBSTATUS_CONFUSED);
    XOR_A_A;
    LDH_addr_A(hBattleTurn);
    CALL(aUseItemText);

    LD_HL(mConfusedNoMoreText);
    CALL(aStdBattleTextbox);

    LD_A(0);


done:
    JP(mStatusHealer_Jumptable);

}

void RestoreHPEffect(void){
    CALL(aItemRestoreHP);
    JP(mStatusHealer_Jumptable);

}

void EnergypowderEffect(void){
    LD_C(HAPPINESS_BITTERPOWDER);
    JR(mEnergypowderEnergyRootCommon);

}

void EnergyRootEffect(void){
    LD_C(HAPPINESS_ENERGYROOT);

    return EnergypowderEnergyRootCommon();
}

void EnergypowderEnergyRootCommon(void){
    PUSH_BC;
    CALL(aItemRestoreHP);
    POP_BC;
    CP_A(0);
    IF_NZ goto skip_happiness;

    FARCALL(aChangeHappiness);
    CALL(aLooksBitterMessage);
    LD_A(0);


skip_happiness:
    JP(mStatusHealer_Jumptable);

}

void ItemRestoreHP(void){
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);
    LD_A(2);
    RET_C ;

    CALL(aIsMonFainted);
    LD_A(1);
    RET_Z ;

    CALL(aIsMonAtFullHealth);
    LD_A(1);
    RET_NC ;

    XOR_A_A;
    LD_addr_A(wLowHealthAlarm);
    CALL(aGetHealingItemAmount);
    CALL(aRestoreHealth);
    CALL(aBattlemonRestoreHealth);
    CALL(aHealHP_SFX_GFX);
    LD_A(PARTYMENUTEXT_HEAL_HP);
    LD_addr_A(wPartyMenuActionText);
    CALL(aItemActionTextWaitButton);
    CALL(aUseDisposableItem);
    LD_A(0);
    RET;

}

void HealHP_SFX_GFX(void){
    PUSH_DE;
    LD_DE(SFX_POTION);
    CALL(aWaitPlaySFX);
    POP_DE;
    LD_A_addr(wCurPartyMon);
    hlcoord(11, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * 2);
    CALL(aAddNTimes);
    LD_A(0x2);
    LD_addr_A(wWhichHPBar);
    PREDEF_JUMP(pAnimateHPBar);

    return UseItem_SelectMon();
}

void UseItem_SelectMon(void){
    CALL(aUseItem_SelectMon_SelectMon);
    RET_C ;

    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_NZ goto not_egg;

    CALL(aCantUseOnEggMessage);
    SCF;
    RET;


not_egg:
    AND_A_A;
    RET;


SelectMon:
    LD_A_B;
    LD_addr_A(wPartyMenuActionText);
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aClearBGPalettes);
    CALL(aChooseMonToUseItemOn);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void ChooseMonToUseItemOn(void){
    FARCALL(aLoadPartyMenuGFX);
    FARCALL(aInitPartyMenuWithCancel);
    FARCALL(aInitPartyMenuGFX);
    FARCALL(aWritePartyMenuTilemap);
    FARCALL(aPrintPartyMenuText);
    CALL(aWaitBGMap);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    FARCALL(aPartyMenuSelect);
    RET;

}

void ItemActionText(void){
    LD_addr_A(wPartyMenuActionText);
    LD_A_addr(wCurPartySpecies);
    PUSH_AF;
    LD_A_addr(wCurPartyMon);
    PUSH_AF;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    FARCALL(aWritePartyMenuTilemap);
    FARCALL(aPrintPartyMenuActionText);
    CALL(aWaitBGMap);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    POP_BC;
    POP_DE;
    POP_HL;
    POP_AF;
    LD_addr_A(wCurPartyMon);
    POP_AF;
    LD_addr_A(wCurPartySpecies);
    RET;

}

void ItemActionTextWaitButton(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    hlcoord(0, 0, wTilemap);
    LD_BC(wTilemapEnd - wTilemap);
    LD_A(0x7f);
    CALL(aByteFill);
    LD_A_addr(wPartyMenuActionText);
    CALL(aItemActionText);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    LD_C(50);
    CALL(aDelayFrames);
    JP(mWaitPressAorB_BlinkCursor);

}

void StatusHealer_NoEffect(void){
    CALL(aWontHaveAnyEffectMessage);
    JR(mStatusHealer_ClearPalettes);

}

void StatusHealer_ExitMenu(void){
    XOR_A_A;
    LD_addr_A(wItemEffectSucceeded);
    return StatusHealer_ClearPalettes();
}

void StatusHealer_ClearPalettes(void){
    CALL(aClearPalettes);
    RET;

}

void IsItemUsedOnBattleMon(void){
    LD_A_addr(wBattleMode);
    AND_A_A;
    RET_Z ;
    LD_A_addr(wCurPartyMon);
    PUSH_HL;
    LD_HL(wCurBattleMon);
    CP_A_hl;
    POP_HL;
    IF_NZ goto nope;
    SCF;
    RET;


nope:
    XOR_A_A;
    RET;

}

void ReviveHalfHP(void){
    CALL(aLoadHPFromBuffer1);
    SRL_D;
    RR_E;
    JR(mContinueRevive);

}

void ReviveFullHP(void){
    CALL(aLoadHPFromBuffer1);
    return ContinueRevive();
}

void ContinueRevive(void){
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_hl_D;
    INC_HL;
    LD_hl_E;
    JP(mLoadCurHPIntoBuffer3);

}

void RestoreHealth(void){
    LD_A(MON_HP + 1);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    ADD_A_E;
    LD_hld_A;
    LD_A_hl;
    ADC_A_D;
    LD_hl_A;
    IF_C goto full_hp;
    CALL(aLoadCurHPIntoBuffer3);
    LD_A(MON_HP + 1);
    CALL(aGetPartyParamLocation);
    LD_D_H;
    LD_E_L;
    LD_A(MON_MAXHP + 1);
    CALL(aGetPartyParamLocation);
    LD_A_de;
    SUB_A_hl;
    DEC_DE;
    DEC_HL;
    LD_A_de;
    SBC_A_hl;
    IF_C goto finish;

full_hp:
    CALL(aReviveFullHP);

finish:
    RET;

}

void RemoveHP(void){
    LD_A(MON_HP + 1);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    SUB_A_E;
    LD_hld_A;
    LD_A_hl;
    SBC_A_D;
    LD_hl_A;
    IF_NC goto okay;
    XOR_A_A;
    LD_hld_A;
    LD_hl_A;

okay:
    CALL(aLoadCurHPIntoBuffer3);
    RET;

}

void IsMonFainted(void){
    PUSH_DE;
    CALL(aLoadMaxHPIntoBuffer1);
    CALL(aLoadCurHPIntoBuffer2);
    CALL(aLoadHPFromBuffer2);
    LD_A_D;
    OR_A_E;
    POP_DE;
    RET;

}

void IsMonAtFullHealth(void){
    CALL(aLoadHPFromBuffer2);
    LD_H_D;
    LD_L_E;
    CALL(aLoadHPFromBuffer1);
    LD_A_L;
    SUB_A_E;
    LD_A_H;
    SBC_A_D;
    RET;

}

void LoadCurHPIntoBuffer3(void){
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_addr_A(wHPBuffer3 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer3);
    RET;

}

void LoadHPIntoBuffer3(void){
//  //  unreferenced
    LD_A_D;
    LD_addr_A(wHPBuffer3 + 1);
    LD_A_E;
    LD_addr_A(wHPBuffer3);
    RET;

}

void LoadHPFromBuffer3(void){
//  //  unreferenced
    LD_A_addr(wHPBuffer3 + 1);
    LD_D_A;
    LD_A_addr(wHPBuffer3);
    LD_E_A;
    RET;

}

void LoadCurHPIntoBuffer2(void){
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_addr_A(wHPBuffer2 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer2);
    RET;

}

void LoadHPFromBuffer2(void){
    LD_A_addr(wHPBuffer2 + 1);
    LD_D_A;
    LD_A_addr(wHPBuffer2);
    LD_E_A;
    RET;

}

void LoadMaxHPIntoBuffer1(void){
    PUSH_HL;
    LD_A(MON_MAXHP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    POP_HL;
    RET;

}

void LoadHPFromBuffer1(void){
    LD_A_addr(wHPBuffer1 + 1);
    LD_D_A;
    LD_A_addr(wHPBuffer1);
    LD_E_A;
    RET;

}

void GetOneFifthMaxHP(void){
    PUSH_BC;
    LD_A(MON_MAXHP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LDH_addr_A(hDividend + 0);
    LD_A_hl;
    LDH_addr_A(hDividend + 1);
    LD_A(5);
    LDH_addr_A(hDivisor);
    LD_B(2);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 2);
    LD_D_A;
    LDH_A_addr(hQuotient + 3);
    LD_E_A;
    POP_BC;
    RET;

}

void GetHealingItemAmount(void){
    PUSH_HL;
    LD_A_addr(wCurItem);
    LD_HL(mHealingHPAmounts);
    LD_D_A;

next:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto NotFound;
    CP_A_D;
    IF_Z goto done;
    INC_HL;
    INC_HL;
    goto next;


NotFound:
    SCF;

done:
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    POP_HL;
    RET;

// INCLUDE "data/items/heal_hp.asm"

    return Softboiled_MilkDrinkFunction();
}

void Softboiled_MilkDrinkFunction(void){
//  Softboiled/Milk Drink in the field
    LD_A_addr(wPartyMenuCursor);
    DEC_A;
    LD_B_A;
    CALL(aSoftboiled_MilkDrinkFunction_SelectMilkDrinkRecipient);  // select pokemon
    IF_C goto skip;
    LD_A_B;
    LD_addr_A(wCurPartyMon);
    CALL(aIsMonFainted);
    CALL(aGetOneFifthMaxHP);
    CALL(aRemoveHP);
    PUSH_BC;
    CALL(aHealHP_SFX_GFX);
    POP_BC;
    CALL(aGetOneFifthMaxHP);
    LD_A_C;
    LD_addr_A(wCurPartyMon);
    CALL(aIsMonFainted);
    CALL(aRestoreHealth);
    CALL(aHealHP_SFX_GFX);
    LD_A(PARTYMENUTEXT_HEAL_HP);
    CALL(aItemActionText);
    CALL(aJoyWaitAorB);

skip:
    LD_A_B;
    INC_A;
    LD_addr_A(wPartyMenuCursor);
    RET;


SelectMilkDrinkRecipient:

loop:
    PUSH_BC;
    LD_A(PARTYMENUACTION_HEALING_ITEM);
    LD_addr_A(wPartyMenuActionText);
    CALL(aChooseMonToUseItemOn);
    POP_BC;
    IF_C goto set_carry;
    LD_A_addr(wPartyMenuCursor);
    DEC_A;
    LD_C_A;
    LD_A_B;
    CP_A_C;
    IF_Z goto cant_use;  // chose the same mon as user
    LD_A_C;
    LD_addr_A(wCurPartyMon);
    CALL(aIsMonFainted);
    IF_Z goto cant_use;
    CALL(aIsMonAtFullHealth);
    IF_NC goto cant_use;
    XOR_A_A;
    RET;


set_carry:
    SCF;
    RET;


cant_use:
    PUSH_BC;
    LD_HL(mSoftboiled_MilkDrinkFunction_ItemCantUseOnMonText);
    CALL(aMenuTextboxBackup);
    POP_BC;
    goto loop;


ItemCantUseOnMonText:
    //text_far ['_ItemCantUseOnMonText']
    //text_end ['?']

    return EscapeRopeEffect();
}

void EscapeRopeEffect(void){
    XOR_A_A;
    LD_addr_A(wItemEffectSucceeded);
    FARCALL(aEscapeRopeFunction);

    LD_A_addr(wItemEffectSucceeded);
    CP_A(1);
    CALL_Z (aUseDisposableItem);
    RET;

}

void SuperRepelEffect(void){
    LD_B(200);
    JR(mUseRepel);

}

void MaxRepelEffect(void){
    LD_B(250);
    JR(mUseRepel);

}

void RepelEffect(void){
    LD_B(100);

    return UseRepel();
}

void UseRepel(void){
    LD_A_addr(wRepelEffect);
    AND_A_A;
    LD_HL(mRepelUsedEarlierIsStillInEffectText);
    JP_NZ (mPrintText);

    LD_A_B;
    LD_addr_A(wRepelEffect);
    JP(mUseItemText);

}

void RepelUsedEarlierIsStillInEffectText(void){
    //text_far ['_RepelUsedEarlierIsStillInEffectText']
    //text_end ['?']

    return XAccuracyEffect();
}

void XAccuracyEffect(void){
    LD_HL(wPlayerSubStatus4);
    BIT_hl(SUBSTATUS_X_ACCURACY);
    JP_NZ (mWontHaveAnyEffect_NotUsedMessage);
    SET_hl(SUBSTATUS_X_ACCURACY);
    JP(mUseItemText);

}

void PokeDollEffect(void){
    LD_A_addr(wBattleMode);
    DEC_A;  // WILD_BATTLE?
    IF_NZ goto not_wild;
    INC_A;  // TRUE
    LD_addr_A(wForcedSwitch);
    LD_A_addr(wBattleResult);
    AND_A(BATTLERESULT_BITMASK);
    OR_A(DRAW);
    LD_addr_A(wBattleResult);
    JP(mUseItemText);


not_wild:
    XOR_A_A;
    LD_addr_A(wItemEffectSucceeded);
    RET;

}

void GuardSpecEffect(void){
    LD_HL(wPlayerSubStatus4);
    BIT_hl(SUBSTATUS_MIST);
    JP_NZ (mWontHaveAnyEffect_NotUsedMessage);
    SET_hl(SUBSTATUS_MIST);
    JP(mUseItemText);

}

void DireHitEffect(void){
    LD_HL(wPlayerSubStatus4);
    BIT_hl(SUBSTATUS_FOCUS_ENERGY);
    JP_NZ (mWontHaveAnyEffect_NotUsedMessage);
    SET_hl(SUBSTATUS_FOCUS_ENERGY);
    JP(mUseItemText);

}

void XItemEffect(void){
    CALL(aUseItemText);

    LD_A_addr(wCurItem);
    LD_HL(mXItemStats);


loop:
    CP_A_hl;
    IF_Z goto got_it;
    INC_HL;
    INC_HL;
    goto loop;


got_it:
    INC_HL;
    LD_B_hl;
    XOR_A_A;
    LDH_addr_A(hBattleTurn);
    LD_addr_A(wAttackMissed);
    LD_addr_A(wEffectFailed);
    FARCALL(aRaiseStat);
    CALL(aWaitSFX);

    FARCALL(aBattleCommand_StatUpMessage);
    FARCALL(aBattleCommand_StatUpFailText);

    LD_A_addr(wCurBattleMon);
    LD_addr_A(wCurPartyMon);
    LD_C(HAPPINESS_USEDXITEM);
    FARCALL(aChangeHappiness);
    RET;

// INCLUDE "data/items/x_stats.asm"

    return PokeFluteEffect();
}

void PokeFluteEffect(void){
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_NZ goto in_battle;
// overworld flute code was dummied out here


in_battle:
    XOR_A_A;
    LD_addr_A(wPokeFluteCuredSleep);

    LD_B(~SLP);

    LD_HL(wPartyMon1Status);
    CALL(aPokeFluteEffect_CureSleep);

    LD_A_addr(wBattleMode);
    CP_A(WILD_BATTLE);
    IF_Z goto skip_otrainer;
    LD_HL(wOTPartyMon1Status);
    CALL(aPokeFluteEffect_CureSleep);

skip_otrainer:

    LD_HL(wBattleMonStatus);
    LD_A_hl;
    AND_A_B;
    LD_hl_A;
    LD_HL(wEnemyMonStatus);
    LD_A_hl;
    AND_A_B;
    LD_hl_A;

    LD_A_addr(wPokeFluteCuredSleep);
    AND_A_A;
    LD_HL(mPokeFluteEffect_PlayedFluteText);
    JP_Z (mPrintText);
    LD_HL(mPokeFluteEffect_PlayedTheFlute);
    CALL(aPrintText);

    LD_A_addr(wLowHealthAlarm);
    AND_A(1 << DANGER_ON_F);
    IF_NZ goto dummy;
// more code was dummied out here

dummy:
    LD_HL(mPokeFluteEffect_FluteWakeUpText);
    JP(mPrintText);


CureSleep:
    LD_DE(PARTYMON_STRUCT_LENGTH);
    LD_C(PARTY_LENGTH);

loop:
    LD_A_hl;
    PUSH_AF;
    AND_A(SLP);
    IF_Z goto not_asleep;
    LD_A(TRUE);
    LD_addr_A(wPokeFluteCuredSleep);

not_asleep:
    POP_AF;
    AND_A_B;
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;


PlayedFluteText:
    //text_far ['_PlayedFluteText']
    //text_end ['?']


FluteWakeUpText:
    //text_far ['_FluteWakeUpText']
    //text_end ['?']


PlayedTheFlute:
// played the # FLUTE.@ @
    //text_far ['Text_PlayedPokeFlute']
    //text_asm ['?']
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_NZ goto battle;

    PUSH_DE;
    LD_DE(SFX_POKEFLUTE);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    POP_DE;


battle:
    JP(mPokeFluteTerminator);

}

void BlueCardEffect(void){
    LD_HL(mBlueCardEffect_BlueCardBalanceText);
    JP(mMenuTextboxWaitButton);


BlueCardBalanceText:
    //text_far ['_BlueCardBalanceText']
    //text_end ['?']

    return CoinCaseEffect();
}

void CoinCaseEffect(void){
    LD_HL(mCoinCaseEffect_CoinCaseCountText);
    JP(mMenuTextboxWaitButton);


CoinCaseCountText:
    //text_far ['_CoinCaseCountText']
    //text_end ['?']

    return OldRodEffect();
}

void OldRodEffect(void){
    LD_E(0x0);
    JR(mUseRod);

}

void GoodRodEffect(void){
    LD_E(0x1);
    JR(mUseRod);

}

void SuperRodEffect(void){
    LD_E(0x2);
    JR(mUseRod);

}

void UseRod(void){
    FARCALL(aFishFunction);
    RET;

}

void ItemfinderEffect(void){
    FARCALL(aItemFinder);
    RET;

}

void RestorePPEffect(void){
    LD_A_addr(wCurItem);
    LD_addr_A(wTempRestorePPItem);


loop:
// Party Screen opens to choose on which mon to use the Item
    LD_B(PARTYMENUACTION_HEALING_ITEM);
    CALL(aUseItem_SelectMon);
    JP_C (mPPRestoreItem_Cancel);


loop2:
    LD_A_addr(wTempRestorePPItem);
    CP_A(MAX_ELIXER);
    JP_Z (mElixer_RestorePPofAllMoves);
    CP_A(ELIXER);
    JP_Z (mElixer_RestorePPofAllMoves);

    LD_HL(mRaiseThePPOfWhichMoveText);
    LD_A_addr(wTempRestorePPItem);
    CP_A(PP_UP);
    IF_Z goto ppup;
    LD_HL(mRestoreThePPOfWhichMoveText);


ppup:
    CALL(aPrintText);

    LD_A_addr(wCurMoveNum);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wCurMoveNum);
    LD_A(0x2);
    LD_addr_A(wMoveSelectionMenuType);
    FARCALL(aMoveSelectionScreen);
    POP_BC;

    LD_A_B;
    LD_addr_A(wCurMoveNum);
    IF_NZ goto loop;
    LD_HL(wPartyMon1Moves);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aGetMthMoveOfNthPartymon);

    PUSH_HL;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetMoveName);
    CALL(aCopyName1);
    POP_HL;

    LD_A_addr(wTempRestorePPItem);
    CP_A(PP_UP);
    JP_NZ (mNot_PP_Up);

    LD_A_hl;
    CP_A(SKETCH);
    IF_Z goto CantUsePPUpOnSketch;

    LD_BC(MON_PP - MON_MOVES);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(PP_UP_MASK);
    IF_C goto do_ppup;


CantUsePPUpOnSketch:
    LD_HL(mPPIsMaxedOutText);
    CALL(aPrintText);
    goto loop2;


do_ppup:
    LD_A_hl;
    ADD_A(PP_UP_ONE);
    LD_hl_A;
    LD_A(TRUE);
    LD_addr_A(wUsePPUp);
    CALL(aApplyPPUp);
    CALL(aPlay_SFX_FULL_HEAL);

    LD_HL(mPPsIncreasedText);
    CALL(aPrintText);

    return FinishPPRestore();
}

void FinishPPRestore(void){
    CALL(aClearPalettes);
    JP(mUseDisposableItem);

}

void BattleRestorePP(void){
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_Z goto not_in_battle;
    LD_A_addr(wCurPartyMon);
    LD_B_A;
    LD_A_addr(wCurBattleMon);
    CP_A_B;
    IF_NZ goto not_in_battle;
    LD_A_addr(wPlayerSubStatus5);
    BIT_A(SUBSTATUS_TRANSFORMED);
    IF_NZ goto not_in_battle;
    CALL(aBattleRestorePP_UpdateBattleMonPP);


not_in_battle:
    CALL(aPlay_SFX_FULL_HEAL);
    LD_HL(mPPRestoredText);
    CALL(aPrintText);
    JR(mFinishPPRestore);


UpdateBattleMonPP:
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1Moves);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_DE(wBattleMonMoves);
    LD_B(NUM_MOVES);

loop:
    LD_A_de;
    AND_A_A;
    IF_Z goto done;
    CP_A_hl;
    IF_NZ goto next;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    for(int rept = 0; rept < NUM_MOVES + 2; rept++){  //  wBattleMonPP - wBattleMonMoves
    INC_DE;
    }
    LD_BC(MON_PP - MON_MOVES);
    ADD_HL_BC;
    LD_A_hl;
    LD_de_A;
    POP_BC;
    POP_DE;
    POP_HL;


next:
    INC_HL;
    INC_DE;
    DEC_B;
    IF_NZ goto loop;


done:
    RET;

}

void Not_PP_Up(void){
    CALL(aRestorePP);
    JR_NZ (mBattleRestorePP);
    JP(mPPRestoreItem_NoEffect);

}

void Elixer_RestorePPofAllMoves(void){
    XOR_A_A;
    LD_HL(wMenuCursorY);
    LD_hli_A;
    LD_hl_A;
    LD_B(NUM_MOVES);

moveLoop:
    PUSH_BC;
    LD_HL(wPartyMon1Moves);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aGetMthMoveOfNthPartymon);
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;

    CALL(aRestorePP);
    IF_Z goto next;
    LD_HL(wMenuCursorX);
    INC_hl;


next:
    LD_HL(wMenuCursorY);
    INC_hl;
    POP_BC;
    DEC_B;
    IF_NZ goto moveLoop;
    LD_A_addr(wMenuCursorX);
    AND_A_A;
    JP_NZ (mBattleRestorePP);

    return PPRestoreItem_NoEffect();
}

void PPRestoreItem_NoEffect(void){
    CALL(aWontHaveAnyEffectMessage);

    return PPRestoreItem_Cancel();
}

void PPRestoreItem_Cancel(void){
    CALL(aClearPalettes);
    XOR_A_A;
    LD_addr_A(wItemEffectSucceeded);
    RET;

}

void RestorePP(void){
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    CALL(aGetMaxPPOfMove);
    LD_HL(wPartyMon1PP);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aGetMthMoveOfNthPartymon);
    LD_A_addr(wTempPP);
    LD_B_A;
    LD_A_hl;
    AND_A(PP_MASK);
    CP_A_B;
    IF_NC goto dont_restore;

    LD_A_addr(wTempRestorePPItem);
    CP_A(MAX_ELIXER);
    IF_Z goto restore_all;
    CP_A(MAX_ETHER);
    IF_Z goto restore_all;

    LD_C(5);
    CP_A(MYSTERYBERRY);
    IF_Z goto restore_some;

    LD_C(10);


restore_some:
    LD_A_hl;
    AND_A(PP_MASK);
    ADD_A_C;
    CP_A_B;
    IF_NC goto restore_all;
    LD_B_A;


restore_all:
    LD_A_hl;
    AND_A(PP_UP_MASK);
    OR_A_B;
    LD_hl_A;
    RET;


dont_restore:
    XOR_A_A;
    RET;

}

void RaiseThePPOfWhichMoveText(void){
    //text_far ['_RaiseThePPOfWhichMoveText']
    //text_end ['?']

    return RestoreThePPOfWhichMoveText();
}

void RestoreThePPOfWhichMoveText(void){
    //text_far ['_RestoreThePPOfWhichMoveText']
    //text_end ['?']

    return PPIsMaxedOutText();
}

void PPIsMaxedOutText(void){
    //text_far ['_PPIsMaxedOutText']
    //text_end ['?']

    return PPsIncreasedText();
}

void PPsIncreasedText(void){
    //text_far ['_PPsIncreasedText']
    //text_end ['?']

    return PPRestoredText();
}

void PPRestoredText(void){
    //text_far ['_PPRestoredText']
    //text_end ['?']

    return SquirtbottleEffect();
}

void SquirtbottleEffect(void){
    FARCALL(av_Squirtbottle);
    RET;

}

void CardKeyEffect(void){
    FARCALL(av_CardKey);
    RET;

}

void BasementKeyEffect(void){
    FARCALL(av_BasementKey);
    RET;

}

void SacredAshEffect(void){
    FARCALL(av_SacredAsh);
    LD_A_addr(wItemEffectSucceeded);
    CP_A(0x1);
    RET_NZ ;
    CALL(aUseDisposableItem);
    RET;

}

void NormalBoxEffect(void){
    LD_C(DECOFLAG_SILVER_TROPHY_DOLL);
    JR(mOpenBox);

}

void GorgeousBoxEffect(void){
    LD_C(DECOFLAG_GOLD_TROPHY_DOLL);
    return OpenBox();
}

void OpenBox(void){
    FARCALL(aSetSpecificDecorationFlag);

    LD_HL(mOpenBox_SentTrophyHomeText);
    CALL(aPrintText);

    JP(mUseDisposableItem);


SentTrophyHomeText:
    //text_far ['_SentTrophyHomeText']
    //text_end ['?']

    return NoEffect();
}

void NoEffect(void){
    JP(mIsntTheTimeMessage);

}

void Play_SFX_FULL_HEAL(void){
    PUSH_DE;
    LD_DE(SFX_FULL_HEAL);
    CALL(aWaitPlaySFX);
    POP_DE;
    RET;

}

void UseItemText(void){
    LD_HL(mItemUsedText);
    CALL(aPrintText);
    CALL(aPlay_SFX_FULL_HEAL);
    CALL(aWaitPressAorB_BlinkCursor);
    return UseDisposableItem();
}

void UseDisposableItem(void){
    LD_HL(wNumItems);
    LD_A(1);
    LD_addr_A(wItemQuantityChange);
    JP(mTossItem);

}

void UseBallInTrainerBattle(void){
    CALL(aReturnToBattle_UseBall);
    LD_DE(ANIM_THROW_POKE_BALL);
    LD_A_E;
    LD_addr_A(wFXAnimID);
    LD_A_D;
    LD_addr_A(wFXAnimID + 1);
    XOR_A_A;
    LD_addr_A(wBattleAnimParam);
    LDH_addr_A(hBattleTurn);
    LD_addr_A(wNumHits);
    PREDEF(pPlayBattleAnim);
    LD_HL(mBallBlockedText);
    CALL(aPrintText);
    LD_HL(mBallDontBeAThiefText);
    CALL(aPrintText);
    JR(mUseDisposableItem);

}

void WontHaveAnyEffect_NotUsedMessage(void){
    LD_HL(mItemWontHaveEffectText);
    CALL(aPrintText);

// Item wasn't used.
    LD_A(0x2);
    LD_addr_A(wItemEffectSucceeded);
    RET;

}

void LooksBitterMessage(void){
    LD_HL(mItemLooksBitterText);
    JP(mPrintText);

}

void Ball_BoxIsFullMessage(void){
    LD_HL(mBallBoxFullText);
    CALL(aPrintText);

// Item wasn't used.
    LD_A(0x2);
    LD_addr_A(wItemEffectSucceeded);
    RET;

}

void CantUseOnEggMessage(void){
    LD_HL(mItemCantUseOnEggText);
    JR(mCantUseItemMessage);

}

void IsntTheTimeMessage(void){
    LD_HL(mItemOakWarningText);
    JR(mCantUseItemMessage);

}

void WontHaveAnyEffectMessage(void){
    LD_HL(mItemWontHaveEffectText);
    JR(mCantUseItemMessage);

}

void BelongsToSomeoneElseMessage(void){
//  //  unreferenced
    LD_HL(mItemBelongsToSomeoneElseText);
    JR(mCantUseItemMessage);

}

void CyclingIsntAllowedMessage(void){
//  //  unreferenced
    LD_HL(mNoCyclingText);
    JR(mCantUseItemMessage);

}

void CantGetOnYourBikeMessage(void){
//  //  unreferenced
    LD_HL(mItemCantGetOnText);
// fallthrough

    return CantUseItemMessage();
}

void CantUseItemMessage(void){
//  Item couldn't be used.
    XOR_A_A;
    LD_addr_A(wItemEffectSucceeded);
    JP(mPrintText);

}

// void ItemLooksBitterText(void){
    //text_far ['_ItemLooksBitterText']
    //text_end ['?']

    // return ItemCantUseOnEggText();
// }

void ItemCantUseOnEggText(void){
    //text_far ['_ItemCantUseOnEggText']
    //text_end ['?']

    return ItemOakWarningText();
}

void ItemOakWarningText(void){
    //text_far ['_ItemOakWarningText']
    //text_end ['?']

    return ItemBelongsToSomeoneElseText();
}

void ItemBelongsToSomeoneElseText(void){
    //text_far ['_ItemBelongsToSomeoneElseText']
    //text_end ['?']

    return ItemWontHaveEffectText();
}

void ItemWontHaveEffectText(void){
    //text_far ['_ItemWontHaveEffectText']
    //text_end ['?']

    return BallBlockedText();
}

void BallBlockedText(void){
    //text_far ['_BallBlockedText']
    //text_end ['?']

    return BallDontBeAThiefText();
}

void BallDontBeAThiefText(void){
    //text_far ['_BallDontBeAThiefText']
    //text_end ['?']

    return NoCyclingText();
}

void NoCyclingText(void){
    //text_far ['_NoCyclingText']
    //text_end ['?']

    return ItemCantGetOnText();
}

void ItemCantGetOnText(void){
    //text_far ['_ItemCantGetOnText']
    //text_end ['?']

    return BallBoxFullText();
}

void BallBoxFullText(void){
    //text_far ['_BallBoxFullText']
    //text_end ['?']

    return ItemUsedText();
}

void ItemUsedText(void){
    //text_far ['_ItemUsedText']
    //text_end ['?']

    return ItemGotOnText();
}

void ItemGotOnText(void){
//  //  unreferenced
    //text_far ['_ItemGotOnText']
    //text_end ['?']

    return ItemGotOffText();
}

void ItemGotOffText(void){
//  //  unreferenced
    //text_far ['_ItemGotOffText']
    //text_end ['?']

    return ApplyPPUp();
}

void ApplyPPUp(void){
    LD_A(MON_MOVES);
    CALL(aGetPartyParamLocation);
    PUSH_HL;
    LD_DE(wPPUpPPBuffer);
    PREDEF(pFillPP);
    POP_HL;
    LD_BC(MON_PP - MON_MOVES);
    ADD_HL_BC;
    LD_DE(wPPUpPPBuffer);
    LD_B(0);

loop:
    INC_B;
    LD_A_B;
    CP_A(NUM_MOVES + 1);
    RET_Z ;
    LD_A_addr(wUsePPUp);
    DEC_A;  // FALSE?
    IF_NZ goto use;
    LD_A_addr(wMenuCursorY);
    INC_A;
    CP_A_B;
    IF_NZ goto skip;


use:
    LD_A_hl;
    AND_A(PP_UP_MASK);
    LD_A_de;  // wasted cycle
    CALL_NZ (aComputeMaxPP);


skip:
    INC_HL;
    INC_DE;
    goto loop;

    return ComputeMaxPP();
}

void ComputeMaxPP(void){
    PUSH_BC;
// Divide the base PP by 5.
    LD_A_de;
    LDH_addr_A(hDividend + 3);
    XOR_A_A;
    LDH_addr_A(hDividend);
    LDH_addr_A(hDividend + 1);
    LDH_addr_A(hDividend + 2);
    LD_A(5);
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
// Get the number of PP, which are bits 6 and 7 of the PP value stored in RAM.
    LD_A_hl;
    LD_B_A;
    SWAP_A;
    AND_A(0xf);
    SRL_A;
    SRL_A;
    LD_C_A;
// If this value is 0, we are done
    AND_A_A;
    IF_Z goto NoPPUp;


loop:
// Normally, a move with 40 PP would have 64 PP with three PP Ups.
// Since this would overflow into bit 6, we prevent that from happening
// by decreasing the extra amount of PP each PP Up provides, resulting
// in a maximum of 61.
    LDH_A_addr(hQuotient + 3);
    CP_A(0x8);
    IF_C goto okay;
    LD_A(0x7);


okay:
    ADD_A_B;
    LD_B_A;
    LD_A_addr(wTempPP);
    DEC_A;
    IF_Z goto NoPPUp;
    DEC_C;
    IF_NZ goto loop;


NoPPUp:
    LD_hl_B;
    POP_BC;
    RET;

}

uint8_t ComputeMaxPP_Conv(uint8_t pp, uint8_t base){
    // PUSH_BC;
// Divide the base PP by 5.
    // LD_A_de;
    // LDH_addr_A(hDividend + 3);
    // XOR_A_A;
    // LDH_addr_A(hDividend);
    // LDH_addr_A(hDividend + 1);
    // LDH_addr_A(hDividend + 2);
    // LD_A(5);
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    base /= 5;
// Get the number of PP, which are bits 6 and 7 of the PP value stored in RAM.
    // LD_A_hl;
    // LD_B_A;
    // SWAP_A;
    // AND_A(0xf);
    // SRL_A;
    // SRL_A;
    // LD_C_A;
    uint8_t ppup_count = (pp & PP_UP_MASK) >> 6;
// If this value is 0, we are done
    // AND_A_A;
    // IF_Z goto NoPPUp;
    if(ppup_count == 0) {
    // NoPPUp:
        // LD_hl_B;
        // POP_BC;
        // RET;
        return pp;
    }

    uint8_t b = pp;
    uint8_t c = ppup_count;
    do {
    // loop:
    // Normally, a move with 40 PP would have 64 PP with three PP Ups.
    // Since this would overflow into bit 6, we prevent that from happening
    // by decreasing the extra amount of PP each PP Up provides, resulting
    // in a maximum of 61.
        // LDH_A_addr(hQuotient + 3);
        uint8_t a = base;
        // CP_A(0x8);
        // IF_C goto okay;
        if(a >= 0x8) 
        // LD_A(0x7);
            a = 0x7;

    // okay:
        // ADD_A_B;
        // LD_B_A;
        b += a;
        // LD_A_addr(wTempPP);
        // DEC_A;
        // IF_Z goto NoPPUp;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);


// NoPPUp:
    // LD_hl_B;
    // POP_BC;
    // RET;
    return b;
}

void RestoreAllPP(void){
    LD_A(MON_PP);
    CALL(aGetPartyParamLocation);
    PUSH_HL;
    LD_A(MON_MOVES);
    CALL(aGetPartyParamLocation);
    POP_DE;
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMenuCursorY);
    LD_addr_A(wMonType);
    LD_C(NUM_MOVES);

loop:
    LD_A_hli;
    AND_A_A;
    RET_Z ;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aGetMaxPPOfMove);
    POP_BC;
    POP_DE;
    LD_A_de;
    AND_A(PP_UP_MASK);
    LD_B_A;
    LD_A_addr(wTempPP);
    ADD_A_B;
    LD_de_A;
    INC_DE;
    LD_HL(wMenuCursorY);
    INC_hl;
    POP_HL;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void RestoreAllPP_Conv(struct PartyMon* pmon){
    // LD_A(MON_PP);
    // CALL(aGetPartyParamLocation);
    // PUSH_HL;
    // LD_A(MON_MOVES);
    // CALL(aGetPartyParamLocation);
    // POP_DE;
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMenuCursorY);
    // LD_addr_A(wMonType);
    // LD_C(NUM_MOVES);
    move_t* hl = pmon->mon.moves;
    uint8_t* de = pmon->mon.PP;

    for(size_t i = 0; i < NUM_MOVES; ++i) {
    // loop:
        // LD_A_hli;
        move_t a = hl[i];
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // CALL(aGetMaxPPOfMove);
        uint8_t maxpp = GetMaxPPOfMove_Conv(pmon, PARTYMON, i);
        // POP_BC;
        // POP_DE;
        // LD_A_de;
        // AND_A(PP_UP_MASK);
        // LD_B_A;
        // LD_A_addr(wTempPP);
        // ADD_A_B;
        // LD_de_A;
        de[i] = (de[i] & PP_UP_MASK) + maxpp;
        // INC_DE;
        // LD_HL(wMenuCursorY);
        // INC_hl;
        // POP_HL;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

void GetMaxPPOfMove(void){
    LD_A_addr(wStringBuffer1 + 0);
    PUSH_AF;
    LD_A_addr(wStringBuffer1 + 1);
    PUSH_AF;

    LD_A_addr(wMonType);
    AND_A_A;

    LD_HL(wPartyMon1Moves);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    IF_Z goto got_partymon;  // PARTYMON

    LD_HL(wOTPartyMon1Moves);
    DEC_A;
    IF_Z goto got_partymon;  // OTPARTYMON

    LD_HL(wTempMonMoves);
    DEC_A;
    IF_Z goto got_nonpartymon;  // BOXMON

    LD_HL(wTempMonMoves);  // Wasted cycles
    DEC_A;
    IF_Z goto got_nonpartymon;  // TEMPMON

    LD_HL(wBattleMonMoves);  // WILDMON


got_nonpartymon:
//   //  BOXMON, TEMPMON, WILDMON
    CALL(aGetMthMoveOfCurrentMon);
    goto gotdatmove;


got_partymon:
//   //  PARTYMON, OTPARTYMON
    CALL(aGetMthMoveOfNthPartymon);


gotdatmove:
    LD_A_hl;
    DEC_A;

    PUSH_HL;
    LD_HL(mMoves + MOVE_PP);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    LD_B_A;
    LD_DE(wStringBuffer1);
    LD_de_A;
    POP_HL;

    PUSH_BC;
    LD_BC(MON_PP - MON_MOVES);
    LD_A_addr(wMonType);
    CP_A(WILDMON);
    IF_NZ goto notwild;
    LD_BC(wEnemyMonPP - wEnemyMonMoves);

notwild:
    ADD_HL_BC;
    LD_A_hl;
    AND_A(PP_UP_MASK);
    POP_BC;

    OR_A_B;
    LD_HL(wStringBuffer1 + 1);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wTempPP);
    LD_A_B;  // this gets lost anyway
    CALL(aComputeMaxPP);
    LD_A_hl;
    AND_A(PP_MASK);
    LD_addr_A(wTempPP);

    POP_AF;
    LD_addr_A(wStringBuffer1 + 1);
    POP_AF;
    LD_addr_A(wStringBuffer1 + 0);
    RET;

}

uint8_t GetMaxPPOfMove_Conv(void* mon, uint8_t montype, uint8_t n){
    // LD_A_addr(wStringBuffer1 + 0);
    // PUSH_AF;
    // LD_A_addr(wStringBuffer1 + 1);
    // PUSH_AF;
    move_t* move;
    uint8_t* mpp;

    // LD_A_addr(wMonType);
    // AND_A_A;

    // LD_HL(wPartyMon1Moves);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // IF_Z goto got_partymon;  // PARTYMON
    switch(montype) {
    case PARTYMON:
    case OTPARTYMON:
    // got_partymon:
    //   //  PARTYMON, OTPARTYMON
        // CALL(aGetMthMoveOfNthPartymon);
        move = ((struct PartyMon*)mon)->mon.moves + n;
        mpp = ((struct PartyMon*)mon)->mon.PP + n;
        break;
    // LD_HL(wOTPartyMon1Moves);
    // DEC_A;
    // IF_Z goto got_partymon;  // OTPARTYMON

    // LD_HL(wTempMonMoves);
    // DEC_A;
    // IF_Z goto got_nonpartymon;  // BOXMON
    case BOXMON:
    case TEMPMON:
    // got_nonpartymon:
    //   //  BOXMON, TEMPMON, WILDMON
        // CALL(aGetMthMoveOfCurrentMon);
        move = ((struct BoxMon*)mon)->moves + n;
        mpp = ((struct BoxMon*)mon)->PP + n;
        break;
        // goto gotdatmove;

    // LD_HL(wTempMonMoves);  // Wasted cycles
    // DEC_A;
    // IF_Z goto got_nonpartymon;  // TEMPMON

    default:
    case WILDMON:
        // LD_HL(wBattleMonMoves);  // WILDMON
        move = wram->wBattleMon.moves + n;
        mpp = wram->wBattleMon.pp + n;
        break;
    }

// gotdatmove:
    // LD_A_hl;
    // DEC_A;

    // PUSH_HL;
    // LD_HL(mMoves + MOVE_PP);
    // LD_BC(MOVE_LENGTH);
    // CALL(aAddNTimes);
    // LD_A(BANK(aMoves));
    // CALL(aGetFarByte);
    // LD_B_A;
    uint8_t pp = Moves[*move - 1].pp;
    // LD_DE(wStringBuffer1);
    // LD_de_A;
    // POP_HL;

    // PUSH_BC;
    // LD_BC(MON_PP - MON_MOVES);
    // LD_A_addr(wMonType);
    // CP_A(WILDMON);
    // IF_NZ goto notwild;
    // LD_BC(wEnemyMonPP - wEnemyMonMoves);

// notwild:
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(PP_UP_MASK);
    // POP_BC;

    // OR_A_B;
    uint8_t pp2 = pp | (*mpp & PP_UP_MASK);
    // LD_HL(wStringBuffer1 + 1);
    // LD_hl_A;
    // XOR_A_A;
    // LD_addr_A(wTempPP);
    // LD_A_B;  // this gets lost anyway
    // CALL(aComputeMaxPP);
    // LD_A_hl;
    // AND_A(PP_MASK);
    // LD_addr_A(wTempPP);
    return ComputeMaxPP_Conv(pp2, pp) & PP_MASK;

    // POP_AF;
    // LD_addr_A(wStringBuffer1 + 1);
    // POP_AF;
    // LD_addr_A(wStringBuffer1 + 0);
    // RET;

}

void GetMthMoveOfNthPartymon(void){
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);

    return GetMthMoveOfCurrentMon();
}

void GetMthMoveOfCurrentMon(void){
    LD_A_addr(wMenuCursorY);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    RET;

}
