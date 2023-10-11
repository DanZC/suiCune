#include "../../constants.h"

const struct TextCmd BattleText_PlayerPickedUpPayDayMoney[] = {
    text_start("<PLAYER> picked up"
        t_line "¥@"
        )
    text_decimal(wram_ptr(wPayDayMoney), 3, 6)
    text_start("!"
        t_prompt )

};

const struct TextCmd WildPokemonAppearedText[] = {
    text_start("Wild @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_line "appeared!"
        t_prompt )

};

const struct TextCmd HookedPokemonAttackedText[] = {
    text_start("The hooked"
        t_line "@"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_cont "attacked!"
        t_prompt )

};

const struct TextCmd PokemonFellFromTreeText[] = {
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(" fell"
        t_line "out of the tree!"
        t_prompt )

};

const struct TextCmd WildCelebiAppearedText[] = {
    text_start("Wild @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_line "appeared!"
        t_prompt )

};

const struct TextCmd WantsToBattleText[] = {
    text_start("<ENEMY>"
        t_line "wants to battle!"
        t_prompt )

};

const struct TextCmd BattleText_WildFled[] = {
    text_start("Wild @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_line "fled!"
        t_prompt )

};

const struct TextCmd BattleText_EnemyFled[] = {
    text_start("Enemy @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_line "fled!"
        t_prompt )

};

const struct TextCmd HurtByPoisonText[] = {
    text_start("<USER>"
        t_line "is hurt by poison!"
        t_prompt )

};

const struct TextCmd HurtByBurnText[] = {
    text_start("<USER>'s"
        t_line "hurt by its burn!"
        t_prompt )

};

const struct TextCmd LeechSeedSapsText[] = {
    text_start("LEECH SEED saps"
        t_line "<USER>!"
        t_prompt )

};

const struct TextCmd HasANightmareText[] = {
    text_start("<USER>"
        t_line "has a NIGHTMARE!"
        t_prompt )

};

const struct TextCmd HurtByCurseText[] = {
    text_start("<USER>'s"
        t_line "hurt by the CURSE!"
        t_prompt )

};

const struct TextCmd SandstormHitsText[] = {
    text_start("The SANDSTORM hits"
        t_line "<USER>!"
        t_prompt )

};

const struct TextCmd PerishCountText[] = {
    text_start("<USER>'s"
        t_line "PERISH count is @"
        )
    text_decimal(wram_ptr(wTextDecimalByte), 1, 1)
    text_start("!"
        t_prompt )

};

const struct TextCmd BattleText_TargetRecoveredWithItem[] = {
    text_start("<TARGET>"
        t_line "recovered with"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd BattleText_UserRecoveredPPUsing[] = {
    text_start("<USER>"
        t_line "recovered PP using"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd BattleText_TargetWasHitByFutureSight[] = {
    text_start("<TARGET>"
        t_line "was hit by FUTURE"
        t_cont "SIGHT!"
        t_prompt )

};

const struct TextCmd BattleText_SafeguardFaded[] = {
    text_start("<USER>'s"
        t_line "SAFEGUARD faded!"
        t_prompt )

};

const struct TextCmd BattleText_MonsLightScreenFell[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" #MON's"
        t_line "LIGHT SCREEN fell!"
        t_prompt )

};

const struct TextCmd BattleText_MonsReflectFaded[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" #MON's"
        t_line "REFLECT faded!"
        t_prompt )

};

const struct TextCmd BattleText_RainContinuesToFall[] = {
    text_start("Rain continues to"
        t_line "fall."
        t_prompt )

};

const struct TextCmd BattleText_TheSunlightIsStrong[] = {
    text_start("The sunlight is"
        t_line "strong."
        t_prompt )

};

const struct TextCmd BattleText_TheSandstormRages[] = {
    text_start("The SANDSTORM"
        t_line "rages."
        t_prompt )

};

const struct TextCmd BattleText_TheRainStopped[] = {
    text_start("The rain stopped."
        t_prompt )

};

const struct TextCmd BattleText_TheSunlightFaded[] = {
    text_start("The sunlight"
        t_line "faded."
        t_prompt )

};

const struct TextCmd BattleText_TheSandstormSubsided[] = {
    text_start("The SANDSTORM"
        t_line "subsided."
        t_prompt )

};

const struct TextCmd BattleText_EnemyMonFainted[] = {
    text_start("Enemy @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_line "fainted!"
        t_prompt )

};

const struct TextCmd GotMoneyForWinningText[] = {
    text_start("<PLAYER> got ¥@"
        )
    text_decimal(wram_ptr(wBattleReward), 3, 6)
    text_start(
        t_line "for winning!"
        t_prompt )

};

const struct TextCmd BattleText_EnemyWasDefeated[] = {
    text_start("<ENEMY>"
        t_line "was defeated!"
        t_prompt )

};

const struct TextCmd TiedAgainstText[] = {
    text_start("Tied against"
        t_line "<ENEMY>!"
        t_prompt )

};

const struct TextCmd SentSomeToMomText[] = {
    text_start("<PLAYER> got ¥@"
        )
    text_decimal(wram_ptr(wBattleReward), 3, 6)
    text_start(
        t_line "for winning!"
        t_cont "Sent some to MOM!"
        t_prompt )

};

const struct TextCmd SentHalfToMomText[] = {
    text_start("Sent half to MOM!"
        t_prompt )

};

const struct TextCmd SentAllToMomText[] = {
    text_start("Sent all to MOM!"
        t_prompt )

};

const struct TextCmd UnusedRivalLossText[] = {
    text_start("<RIVAL>: Huh? I"
        t_line "should've chosen"
        t_cont "your #MON!"
        t_prompt )

};

const struct TextCmd BattleText_MonFainted[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(
        t_line "fainted!"
        t_prompt )

};

const struct TextCmd BattleText_UseNextMon[] = {
    text_start("Use next #MON?"
        t_done )

};

const struct TextCmd UnusedRivalWinText[] = {
    text_start("<RIVAL>: Yes!"
        t_line "I guess I chose a"
        t_cont "good #MON!"
        t_prompt )

};

const struct TextCmd LostAgainstText[] = {
    text_start("Lost against"
        t_line "<ENEMY>!"
        t_prompt )

};

const struct TextCmd BattleText_EnemyIsAboutToUseWillPlayerChangeMon[] = {
    text_start("<ENEMY>"
        t_line "is about to use"
        t_cont "@"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start("."

        t_para "Will <PLAYER>"
        t_line "change #MON?"
        t_done )

};

const struct TextCmd BattleText_EnemySentOut[] = {
    text_start("<ENEMY>"
        t_line "sent out"
        t_cont "@"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start("!"
        t_done )

};

const struct TextCmd BattleText_TheresNoWillToBattle[] = {
    text_start("There's no will to"
        t_line "battle!"
        t_prompt )

};

const struct TextCmd BattleText_AnEGGCantBattle[] = {
    text_start("An EGG can't"
        t_line "battle!"
        t_prompt )

};

const struct TextCmd BattleText_CantEscape2[] = {
    text_start("Can't escape!"
        t_prompt )

};

const struct TextCmd BattleText_TheresNoEscapeFromTrainerBattle[] = {
    text_start("No! There's no"
        t_line "running from a"
        t_cont "trainer battle!"
        t_prompt )

};

const struct TextCmd BattleText_GotAwaySafely[] = {
    text_start("Got away safely!"
        t_prompt )

};

const struct TextCmd BattleText_UserFledUsingAStringBuffer1[] = {
    text_start("<USER>"
        t_line "fled using a"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd BattleText_CantEscape[] = {
    text_start("Can't escape!"
        t_prompt )

};

const struct TextCmd BattleText_UserHurtBySpikes[] = {
    text_start("<USER>'s"
        t_line "hurt by SPIKES!"
        t_prompt )

};

const struct TextCmd RecoveredUsingText[] = {
    text_start("<TARGET>"
        t_line "recovered using a"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd BattleText_UsersStringBuffer1Activated[] = {
    text_start("<USER>'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_cont "activated!"
        t_prompt )

};

const struct TextCmd BattleText_ItemsCantBeUsedHere[] = {
    text_start("Items can't be"
        t_line "used here."
        t_prompt )

};

const struct TextCmd BattleText_MonIsAlreadyOut[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(
        t_line "is already out."
        t_prompt )

};

const struct TextCmd BattleText_MonCantBeRecalled[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(
        t_line "can't be recalled!"
        t_prompt )

};

const struct TextCmd BattleText_TheresNoPPLeftForThisMove[] = {
    text_start("There's no PP left"
        t_line "for this move!"
        t_prompt )

};

const struct TextCmd BattleText_TheMoveIsDisabled[] = {
    text_start("The move is"
        t_line "DISABLED!"
        t_prompt )

};

const struct TextCmd BattleText_MonHasNoMovesLeft[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(
        t_line "has no moves left!"
        t_done )

};

const struct TextCmd BattleText_TargetsEncoreEnded[] = {
    text_start("<TARGET>'s"
        t_line "ENCORE ended!"
        t_prompt )

};

const struct TextCmd BattleText_StringBuffer1GrewToLevel[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" grew to"
        t_line "level @"
        )
    text_decimal(wram_ptr(wCurPartyLevel), 1, 3)
    text_start("!@"
        )
    sound_dex_fanfare_50_79
    text_end

    text_end

};

const struct TextCmd BattleText_WildMonIsEating[] = {
    text_start("Wild @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_line "is eating!"
        t_prompt )

};

const struct TextCmd BattleText_WildMonIsAngry[] = {
    text_start("Wild @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_line "is angry!"
        t_prompt )

};

const struct TextCmd FastAsleepText[] = {
    text_start("<USER>"
        t_line "is fast asleep!"
        t_prompt )

};

const struct TextCmd WokeUpText[] = {
    text_start("<USER>"
        t_line "woke up!"
        t_prompt )

};

const struct TextCmd FrozenSolidText[] = {
    text_start("<USER>"
        t_line "is frozen solid!"
        t_prompt )

};

const struct TextCmd FlinchedText[] = {
    text_start("<USER>"
        t_line "flinched!"
        t_prompt )

};

const struct TextCmd MustRechargeText[] = {
    text_start("<USER>"
        t_line "must recharge!"
        t_prompt )

};

const struct TextCmd DisabledNoMoreText[] = {
    text_start("<USER>'s"
        t_line "disabled no more!"
        t_prompt )

};

const struct TextCmd IsConfusedText[] = {
    text_start("<USER>"
        t_line "is confused!"
        t_prompt )

};

const struct TextCmd HurtItselfText[] = {
    text_start("It hurt itself in"
        t_line "its confusion!"
        t_prompt )

};

const struct TextCmd ConfusedNoMoreText[] = {
    text_start("<USER>'s"
        t_line "confused no more!"
        t_prompt )

};

const struct TextCmd BecameConfusedText[] = {
    text_start("<TARGET>"
        t_line "became confused!"
        t_prompt )

};

const struct TextCmd BattleText_ItemHealedConfusion[] = {
    text_start("A @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" rid"
        t_line "<TARGET>"
        t_cont "of its confusion."
        t_prompt )

};

const struct TextCmd AlreadyConfusedText[] = {
    text_start("<TARGET>'s"
        t_line "already confused!"
        t_prompt )

};

const struct TextCmd BattleText_UsersHurtByStringBuffer1[] = {
    text_start("<USER>'s"
        t_line "hurt by"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd BattleText_UserWasReleasedFromStringBuffer1[] = {
    text_start("<USER>"
        t_line "was released from"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd UsedBindText[] = {
    text_start("<USER>"
        t_line "used BIND on"
        t_cont "<TARGET>!"
        t_prompt )

};

const struct TextCmd WhirlpoolTrapText[] = {
    text_start("<TARGET>"
        t_line "was trapped!"
        t_prompt )

};

const struct TextCmd FireSpinTrapText[] = {
    text_start("<TARGET>"
        t_line "was trapped!"
        t_prompt )

};

const struct TextCmd WrappedByText[] = {
    text_start("<TARGET>"
        t_line "was WRAPPED by"
        t_cont "<USER>!"
        t_prompt )

};

const struct TextCmd ClampedByText[] = {
    text_start("<TARGET>"
        t_line "was CLAMPED by"
        t_cont "<USER>!"
        t_prompt )

};

const struct TextCmd StoringEnergyText[] = {
    text_start("<USER>"
        t_line "is storing energy!"
        t_prompt )

};

const struct TextCmd UnleashedEnergyText[] = {
    text_start("<USER>"
        t_line "unleashed energy!"
        t_prompt )

};

const struct TextCmd HungOnText[] = {
    text_start("<TARGET>"
        t_line "hung on with"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd EnduredText[] = {
    text_start("<TARGET>"
        t_line "ENDURED the hit!"
        t_prompt )

};

const struct TextCmd InLoveWithText[] = {
    text_start("<USER>"
        t_line "is in love with"
        t_cont "<TARGET>!"
        t_prompt )

};

const struct TextCmd InfatuationText[] = {
    text_start("<USER>'s"
        t_line "infatuation kept"
        t_cont "it from attacking!"
        t_prompt )

};

const struct TextCmd DisabledMoveText[] = {
    text_start("<USER>'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" is"
        t_cont "DISABLED!"
        t_prompt )

};

const struct TextCmd LoafingAroundText[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(" is"
        t_line "loafing around."
        t_prompt )

};

const struct TextCmd BeganToNapText[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(" began"
        t_line "to nap!"
        t_prompt )

};

const struct TextCmd WontObeyText[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(" won't"
        t_line "obey!"
        t_prompt )

};

const struct TextCmd TurnedAwayText[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(" turned"
        t_line "away!"
        t_prompt )

};

const struct TextCmd IgnoredOrdersText[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(" ignored"
        t_line "orders!"
        t_prompt )

};

const struct TextCmd IgnoredSleepingText[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(" ignored"
        t_line "orders…sleeping!"
        t_prompt )

};

const struct TextCmd NoPPLeftText[] = {
    text_start("But no PP is left"
        t_line "for the move!"
        t_prompt )

};

const struct TextCmd HasNoPPLeftText[] = {
    text_start("<USER>"
        t_line "has no PP left for"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("!"
        t_prompt )

};

const struct TextCmd WentToSleepText[] = {
    text_start("<USER>"
        t_line "went to sleep!"
        t_done )

};

const struct TextCmd RestedText[] = {
    text_start("<USER>"
        t_line "fell asleep and"
        t_cont "became healthy!"
        t_done )

};

const struct TextCmd RegainedHealthText[] = {
    text_start("<USER>"
        t_line "regained health!"
        t_prompt )

};

const struct TextCmd AttackMissedText[] = {
    text_start("<USER>'s"
        t_line "attack missed!"
        t_prompt )

};

const struct TextCmd AttackMissed2Text[] = {
    text_start("<USER>'s"
        t_line "attack missed!"
        t_prompt )

};

const struct TextCmd CrashedText[] = {
    text_start("<USER>"
        t_line "kept going and"
        t_cont "crashed!"
        t_prompt )

};

const struct TextCmd UnaffectedText[] = {
    text_start("<TARGET>'s"
        t_line "unaffected!"
        t_prompt )

};

const struct TextCmd DoesntAffectText[] = {
    text_start("It doesn't affect"
        t_line "<TARGET>!"
        t_prompt )

};

const struct TextCmd CriticalHitText[] = {
    text_start("A critical hit!"
        t_prompt )

};

const struct TextCmd OneHitKOText[] = {
    text_start("It's a one-hit KO!"
        t_prompt )

};

const struct TextCmd SuperEffectiveText[] = {
    text_start("It's super-"
        t_line "effective!"
        t_prompt )

};

const struct TextCmd NotVeryEffectiveText[] = {
    text_start("It's not very"
        t_line "effective…"
        t_prompt )

};

const struct TextCmd TookDownWithItText[] = {
    text_start("<TARGET>"
        t_line "took down with it,"
        t_cont "<USER>!"
        t_prompt )

};

const struct TextCmd RageBuildingText[] = {
    text_start("<USER>'s"
        t_line "RAGE is building!"
        t_prompt )

};

const struct TextCmd GotAnEncoreText[] = {
    text_start("<TARGET>"
        t_line "got an ENCORE!"
        t_prompt )

};

const struct TextCmd SharedPainText[] = {
    text_start("The battlers"
        t_line "shared pain!"
        t_prompt )

};

const struct TextCmd TookAimText[] = {
    text_start("<USER>"
        t_line "took aim!"
        t_prompt )

};

const struct TextCmd SketchedText[] = {
    text_start("<USER>"
        t_line "SKETCHED"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd DestinyBondEffectText[] = {
    text_start("<USER>'s"
        t_line "trying to take its"
        t_cont "opponent with it!"
        t_prompt )

};

const struct TextCmd SpiteEffectText[] = {
    text_start("<TARGET>'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" was"
        t_cont "reduced by @"
        )
    text_decimal(wram_ptr(wTextDecimalByte), 1, 1)
    text_start("!"
        t_prompt )

};

const struct TextCmd BellChimedText[] = {
    text_start("A bell chimed!"
        t_line ""
        t_prompt )

};

const struct TextCmd FellAsleepText[] = {
    text_start("<TARGET>"
        t_line "fell asleep!"
        t_prompt )

};

const struct TextCmd AlreadyAsleepText[] = {
    text_start("<TARGET>'s"
        t_line "already asleep!"
        t_prompt )

};

const struct TextCmd WasPoisonedText[] = {
    text_start("<TARGET>"
        t_line "was poisoned!"
        t_prompt )

};

const struct TextCmd BadlyPoisonedText[] = {
    text_start("<TARGET>'s"
        t_line "badly poisoned!"
        t_prompt )

};

const struct TextCmd AlreadyPoisonedText[] = {
    text_start("<TARGET>'s"
        t_line "already poisoned!"
        t_prompt )

};

const struct TextCmd SuckedHealthText[] = {
    text_start("Sucked health from"
        t_line "<TARGET>!"
        t_prompt )

};

const struct TextCmd DreamEatenText[] = {
    text_start("<TARGET>'s"
        t_line "dream was eaten!"
        t_prompt )

};

const struct TextCmd WasBurnedText[] = {
    text_start("<TARGET>"
        t_line "was burned!"
        t_prompt )

};

const struct TextCmd DefrostedOpponentText[] = {
    text_start("<TARGET>"
        t_line "was defrosted!"
        t_prompt )

};

const struct TextCmd WasFrozenText[] = {
    text_start("<TARGET>"
        t_line "was frozen solid!"
        t_prompt )

};

const struct TextCmd WontRiseAnymoreText[] = {
    text_start("<USER>'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" won't"
        t_cont "rise anymore!"
        t_prompt )

};

const struct TextCmd WontDropAnymoreText[] = {
    text_start("<TARGET>'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" won't"
        t_cont "drop anymore!"
        t_prompt )

};

const struct TextCmd FledFromBattleText[] = {
    text_start("<USER>"
        t_line "fled from battle!"
        t_prompt )

};

const struct TextCmd FledInFearText[] = {
    text_start("<TARGET>"
        t_line "fled in fear!"
        t_prompt )

};

const struct TextCmd BlownAwayText[] = {
    text_start("<TARGET>"
        t_line "was blown away!"
        t_prompt )

};

const struct TextCmd PlayerHitTimesText[] = {
    text_start("Hit @"
        )
    text_decimal(wram_ptr(wPlayerDamageTaken), 1, 1)
    text_start(" times!"
        t_prompt )

};

const struct TextCmd EnemyHitTimesText[] = {
    text_start("Hit @"
        )
    text_decimal(wram_ptr(wEnemyDamageTaken), 1, 1)
    text_start(" times!"
        t_prompt )

};

const struct TextCmd MistText[] = {
    text_start("<USER>'s"
        t_line "shrouded in MIST!"
        t_prompt )

};

const struct TextCmd ProtectedByMistText[] = {
    text_start("<TARGET>'s"
        t_line "protected by MIST."
        t_prompt )

};

const struct TextCmd GettingPumpedText[] = {
    text_pause
    text_start("<USER>'s"
        t_line "getting pumped!"
        t_prompt )

};

const struct TextCmd RecoilText[] = {
    text_start("<USER>'s"
        t_line "hit with recoil!"
        t_prompt )

};

const struct TextCmd MadeSubstituteText[] = {
    text_start("<USER>"
        t_line "made a SUBSTITUTE!"
        t_prompt )

};

const struct TextCmd HasSubstituteText[] = {
    text_start("<USER>"
        t_line "has a SUBSTITUTE!"
        t_prompt )

};

const struct TextCmd TooWeakSubText[] = {
    text_start("Too weak to make"
        t_line "a SUBSTITUTE!"
        t_prompt )

};

const struct TextCmd SubTookDamageText[] = {
    text_start("The SUBSTITUTE"
        t_line "took damage for"
        t_cont "<TARGET>!"
        t_prompt )

};

const struct TextCmd SubFadedText[] = {
    text_start("<TARGET>'s"
        t_line "SUBSTITUTE faded!"
        t_prompt )

};

const struct TextCmd MimicLearnedMoveText[] = {
    text_start("<USER>"
        t_line "learned"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd WasSeededText[] = {
    text_start("<TARGET>"
        t_line "was seeded!"
        t_prompt )

};

const struct TextCmd EvadedText[] = {
    text_start("<TARGET>"
        t_line "evaded the attack!"
        t_prompt )

};

const struct TextCmd WasDisabledText[] = {
    text_start("<TARGET>'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" was"
        t_cont "DISABLED!"
        t_prompt )

};

const struct TextCmd CoinsScatteredText[] = {
    text_start("Coins scattered"
        t_line "everywhere!"
        t_prompt )

};

const struct TextCmd TransformedTypeText[] = {
    text_start("<USER>"
        t_line "transformed into"
        t_cont "the @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("-type!"
        t_prompt )

};

const struct TextCmd EliminatedStatsText[] = {
    text_start("All stat changes"
        t_line "were eliminated!"
        t_prompt )

};

const struct TextCmd TransformedText[] = {
    text_start("<USER>"
        t_line "TRANSFORMED into"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd LightScreenEffectText[] = {
    text_start("<USER>'s"
        t_line "SPCL.DEF rose!"
        t_prompt )

};

const struct TextCmd ReflectEffectText[] = {
    text_start("<USER>'s"
        t_line "DEFENSE rose!"
        t_prompt )

};

const struct TextCmd NothingHappenedText[] = {
    text_start("But nothing"
        t_line "happened."
        t_prompt )

};

const struct TextCmd ButItFailedText[] = {
    text_start("But it failed!"
        t_prompt )

};

const struct TextCmd ItFailedText[] = {
    text_start("It failed!"
        t_prompt )

};

const struct TextCmd DidntAffect1Text[] = {
    text_start("It didn't affect"
        t_line "<TARGET>!"
        t_prompt )

};

const struct TextCmd DidntAffect2Text[] = {
    text_start("It didn't affect"
        t_line "<TARGET>!"
        t_prompt )

};

const struct TextCmd HPIsFullText[] = {
    text_start("<USER>'s"
        t_line "HP is full!"
        t_prompt )

};

const struct TextCmd DraggedOutText[] = {
    text_start("<USER>"
        t_line "was dragged out!"
        t_prompt )

};

const struct TextCmd ParalyzedText[] = {
    text_start("<TARGET>'s"
        t_line "paralyzed! Maybe"
        t_cont "it can't attack!"
        t_prompt )

};

const struct TextCmd FullyParalyzedText[] = {
    text_start("<USER>'s"
        t_line "fully paralyzed!"
        t_prompt )

};

const struct TextCmd AlreadyParalyzedText[] = {
    text_start("<TARGET>'s"
        t_line "already paralyzed!"
        t_prompt )

};

const struct TextCmd ProtectedByText[] = {
    text_start("<TARGET>'s"
        t_line "protected by"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd MirrorMoveFailedText[] = {
    text_start("The MIRROR MOVE"
        t_next "failed!"
        t_prompt )

};

const struct TextCmd StoleText[] = {
    text_start("<USER>"
        t_line "stole @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_cont "from its foe!"
        t_prompt )

};

const struct TextCmd CantEscapeNowText[] = {
    text_start("<TARGET>"
        t_line "can't escape now!"
        t_prompt )

};

const struct TextCmd StartedNightmareText[] = {
    text_start("<TARGET>"
        t_line "started to have a"
        t_cont "NIGHTMARE!"
        t_prompt )

};

const struct TextCmd WasDefrostedText[] = {
    text_start("<USER>"
        t_line "was defrosted!"
        t_prompt )

};

const struct TextCmd PutACurseText[] = {
    text_start("<USER>"
        t_line "cut its own HP and"

        t_para "put a CURSE on"
        t_line "<TARGET>!"
        t_prompt )

};

const struct TextCmd ProtectedItselfText[] = {
    text_start("<USER>"
        t_line "PROTECTED itself!"
        t_prompt )

};

const struct TextCmd ProtectingItselfText[] = {
    text_start("<TARGET>'s"
        t_line "PROTECTING itself!"
        t_done )

};

const struct TextCmd SpikesText[] = {
    text_start("SPIKES scattered"
        t_line "all around"
        t_cont "<TARGET>!"
        t_prompt )

};

const struct TextCmd IdentifiedText[] = {
    text_start("<USER>"
        t_line "identified"
        t_cont "<TARGET>!"
        t_prompt )

};

const struct TextCmd StartPerishText[] = {
    text_start("Both #MON will"
        t_line "faint in 3 turns!"
        t_prompt )

};

const struct TextCmd SandstormBrewedText[] = {
    text_start("A SANDSTORM"
        t_line "brewed!"
        t_prompt )

};

const struct TextCmd BracedItselfText[] = {
    text_start("<USER>"
        t_line "braced itself!"
        t_prompt )

};

const struct TextCmd FellInLoveText[] = {
    text_start("<TARGET>"
        t_line "fell in love!"
        t_prompt )

};

const struct TextCmd CoveredByVeilText[] = {
    text_start("<USER>'s"
        t_line "covered by a veil!"
        t_prompt )

};

const struct TextCmd SafeguardProtectText[] = {
    text_start("<TARGET>"
        t_line "is protected by"
        t_cont "SAFEGUARD!"
        t_prompt )

};

const struct TextCmd MagnitudeText[] = {
    text_start("Magnitude @"
        )
    text_decimal(wram_ptr(wTextDecimalByte), 1, 1)
    text_start("!"
        t_prompt )

};

const struct TextCmd ReleasedByText[] = {
    text_start("<USER>"
        t_line "was released by"
        t_cont "<TARGET>!"
        t_prompt )

};

const struct TextCmd ShedLeechSeedText[] = {
    text_start("<USER>"
        t_line "shed LEECH SEED!"
        t_prompt )

};

const struct TextCmd BlewSpikesText[] = {
    text_start("<USER>"
        t_line "blew away SPIKES!"
        t_prompt )

};

const struct TextCmd DownpourText[] = {
    text_start("A downpour"
        t_line "started!"
        t_prompt )

};

const struct TextCmd SunGotBrightText[] = {
    text_start("The sunlight got"
        t_line "bright!"
        t_prompt )

};

const struct TextCmd BellyDrumText[] = {
    text_start("<USER>"
        t_line "cut its HP and"
        t_cont "maximized ATTACK!"
        t_prompt )

};

const struct TextCmd CopiedStatsText[] = {
    text_start("<USER>"
        t_line "copied the stat"

        t_para "changes of"
        t_line "<TARGET>!"
        t_prompt )

};

const struct TextCmd ForesawAttackText[] = {
    text_start("<USER>"
        t_line "foresaw an attack!"
        t_prompt )

};

const struct TextCmd BeatUpAttackText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s"
        t_line "attack!"
        t_done )

};

const struct TextCmd PresentFailedText[] = {
    text_start("<TARGET>"
        t_line "refused the gift!"
        t_prompt )

};

const struct TextCmd IgnoredOrders2Text[] = {
    text_start("<USER>"
        t_line "ignored orders!"
        t_prompt )

};

const struct TextCmd BattleText_LinkErrorBattleCanceled[] = {
    text_start("Link error…"

        t_para "The battle has"
        t_line "been canceled…"
        t_prompt )

};

const struct TextCmd BattleText_NoTimeLeftToday[] = {
    text_start("There is no time"
        t_line "left today!"
        t_done )
};
