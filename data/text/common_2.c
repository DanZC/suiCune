#include "../../constants.h"
const struct TextCmd v_NoPhotoText[] = {
    text_start("Oh, no picture?"
        t_line "Come again, OK?"
        t_done )

};

const struct TextCmd v_EggPhotoText[] = {
    text_start("An EGG? My talent"
        t_line "is worth more…"
        t_done )

};

const struct TextCmd v_NameRaterHelloText[] = {
    text_start("Hello, hello! I'm"
        t_line "the NAME RATER."

        t_para "I rate the names"
        t_line "of #MON."

        t_para "Would you like me"
        t_line "to rate names?"
        t_done )

};

const struct TextCmd v_NameRaterWhichMonText[] = {
    text_start("Which #MON's"
        t_line "nickname should I"
        t_cont "rate for you?"
        t_prompt )

};

const struct TextCmd v_NameRaterBetterNameText[] = {
    text_start("Hm… @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("…"
        t_line "That's a fairly"
        t_cont "decent name."

        t_para "But, how about a"
        t_line "slightly better"
        t_cont "nickname?"

        t_para "Want me to give it"
        t_line "a better name?"
        t_done )

};

const struct TextCmd v_NameRaterWhatNameText[] = {
    text_start("All right. What"
        t_line "name should we"
        t_cont "give it, then?"
        t_prompt )

};

const struct TextCmd v_NameRaterFinishedText[] = {
    text_start("That's a better"
        t_line "name than before!"

        t_para "Well done!"
        t_done )

};

const struct TextCmd v_NameRaterComeAgainText[] = {
    text_start("OK, then. Come"
        t_line "again sometime."
        t_done )

};

const struct TextCmd v_NameRaterPerfectNameText[] = {
    text_start("Hm… @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"
        t_line "What a great name!"
        t_cont "It's perfect."

        t_para "Treat @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "with loving care."
        t_done )

};

const struct TextCmd v_NameRaterEggText[] = {
    text_start("Whoa… That's just"
        t_line "an EGG."
        t_done )

};

const struct TextCmd v_NameRaterSameNameText[] = {
    text_start("It might look the"
        t_line "same as before,"

        t_para "but this new name"
        t_line "is much better!"

        t_para "Well done!"
        t_done )

};

const struct TextCmd v_NameRaterNamedText[] = {
    text_start("All right. This"
        t_line "#MON is now"
        t_cont "named @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_Text_Gained[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" gained@"
        )
    text_end

};

const struct TextCmd v_BoostedExpPointsText[] = {
    text_start(
        t_line "a boosted"
        t_cont "@"
        )
    text_decimal(wram_ptr(wStringBuffer2), 2, 4)
    text_start(" EXP. Points!"
        t_prompt )

};

const struct TextCmd v_ExpPointsText[] = {
    text_start(
        t_line "@"
        )
    text_decimal(wram_ptr(wStringBuffer2), 2, 4)
    text_start(" EXP. Points!"
        t_prompt )

};

const struct TextCmd v_GoMonText[] = {
    text_start("Go! @"
        )
    text_end

};

const struct TextCmd v_DoItMonText[] = {
    text_start("Do it! @"
        )
    text_end

};

const struct TextCmd v_GoForItMonText[] = {
    text_start("Go for it,"
        t_line "@"
        )
    text_end

};

const struct TextCmd v_YourFoesWeakGetmMonText[] = {
    text_start("Your foe's weak!"
        t_line "Get'm, @"
        )
    text_end

};

const struct TextCmd v_BattleMonNicknameText[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start("!"
        t_done )

};

const struct TextCmd v_BattleMonNickCommaText[] = {
    text_ram(wram_ptr(wBattleMonNickname))
    text_start(",@"
        )
    text_end

};

const struct TextCmd v_ThatsEnoughComeBackText[] = {
    text_start(" that's"
        t_line "enough! Come back!@"
        )
    text_end

};

const struct TextCmd v_OKComeBackText[] = {
    text_start(" OK!"
        t_line "Come back!@"
        )
    text_end

};

const struct TextCmd v_GoodComeBackText[] = {
    text_start(" good!"
        t_line "Come back!@"
        )
    text_end

};

const struct TextCmd v_ComeBackText[] = {
    text_start(" come"
        t_line "back!"
        t_done )

};

const struct TextCmd v_BootedTMText[] = {
    text_start("Booted up a TM."
        t_prompt )

};

const struct TextCmd v_BootedHMText[] = {
    text_start("Booted up an HM."
        t_prompt )

};

const struct TextCmd v_ContainedMoveText[] = {
    text_start("It contained"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."

        t_para "Teach @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(
        t_line "to a #MON?"
        t_done )

};

const struct TextCmd v_TMHMNotCompatibleText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" is"
        t_line "not compatible"
        t_cont "with @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."

        t_para "It can't learn"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )

};

const struct TextCmd v_NoRoomTMHMText[] = {
    text_start("You have no room"
        t_line "for any more"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("S."
        t_prompt )

};

const struct TextCmd v_ReceivedTMHMText[] = {
    text_start("You received"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd v_MysteryGiftCanceledText[] = {
    text_start("The link has been"
        t_line "cancelled."
        t_prompt )

};

const struct TextCmd v_MysteryGiftCommErrorText[] = {
    text_start("Communication"
        t_line "error."
        t_prompt )

};

const struct TextCmd v_RetrieveMysteryGiftText[] = {
    text_start("Must retrieve GIFT"
        t_line "at #MON CENTER."
        t_prompt )

};

const struct TextCmd v_YourFriendIsNotReadyText[] = {
    text_start("Your friend isn't"
        t_line "ready."
        t_prompt )

};

const struct TextCmd v_MysteryGiftFiveADayText[] = {
    text_start("Sorry--only five"
        t_line "GIFTS a day."
        t_prompt )

};

const struct TextCmd v_MysteryGiftOneADayText[] = {
    text_start("Sorry. One GIFT"
        t_line "a day per person."
        t_prompt )

};

const struct TextCmd v_MysteryGiftSentText[] = {
    text_ram(wram_ptr(wMysteryGiftPartnerName))
    text_start(" sent"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_MysteryGiftSentHomeText[] = {
    text_ram(wram_ptr(wMysteryGiftPartnerName))
    text_start(" sent"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_cont "to @"
        )
    text_ram(wram_ptr(wMysteryGiftPlayerName))
    text_start("'s home."
        t_prompt )

};

const struct TextCmd v_NameCardReceivedCardText[] = {
    text_start("Received"
        t_line "@"
        )
    text_ram(wram_ptr(wMysteryGiftCardHolderName))
    text_start("'s CARD."
        t_prompt )

};

const struct TextCmd v_NameCardListedCardText[] = {
    text_ram(wram_ptr(wMysteryGiftCardHolderName))
    text_start("'s CARD was"
        t_line "listed as no.@"
        )
    text_decimal(wram_ptr(wTextDecimalByte), 1, 2)
    text_start("."
        t_prompt )

};

const struct TextCmd v_NameCardNotRegisteredCardText[] = {
    text_start("The CARD was not"
        t_line "registered."
        t_prompt )

};

const struct TextCmd v_NameCardLinkCancelledText[] = {
    text_start("The link has been"
        t_line "cancelled."
        t_prompt )

};

const struct TextCmd v_NameCardLinkCommErrorText[] = {
    text_start("Communication"
        t_line "error."
        t_prompt )

};

const struct TextCmd v_BadgeRequiredText[] = {
    text_start("Sorry! A new BADGE"
        t_line "is required."
        t_prompt )

};

const struct TextCmd v_CantUseItemText[] = {
    text_start("Can't use that"
        t_line "here."
        t_prompt )

};

const struct TextCmd v_UseCutText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" used"
        t_line "CUT!"
        t_prompt )

};

const struct TextCmd v_CutNothingText[] = {
    text_start("There's nothing to"
        t_line "CUT here."
        t_prompt )

};

const struct TextCmd v_BlindingFlashText[] = {
    text_start("A blinding FLASH"
        t_line "lights the area!@"
        )
    text_promptbutton
    text_end

    text_end

};

const struct TextCmd v_UsedSurfText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" used"
        t_line "SURF!"
        t_done )

};

const struct TextCmd v_CantSurfText[] = {
    text_start("You can't SURF"
        t_line "here."
        t_prompt )

};

const struct TextCmd v_AlreadySurfingText[] = {
    text_start("You're already"
        t_line "SURFING."
        t_prompt )

};

const struct TextCmd v_AskSurfText[] = {
    text_start("The water is calm."
        t_line "Want to SURF?"
        t_done )

};

const struct TextCmd v_UseWaterfallText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" used"
        t_line "WATERFALL!"
        t_done )

};

const struct TextCmd v_HugeWaterfallText[] = {
    text_start("Wow, it's a huge"
        t_line "waterfall."
        t_done )

};

const struct TextCmd v_AskWaterfallText[] = {
    text_start("Do you want to use"
        t_line "WATERFALL?"
        t_done )

};

const struct TextCmd v_UseDigText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" used"
        t_line "DIG!"
        t_done )

};

const struct TextCmd v_UseEscapeRopeText[] = {
    text_start("<PLAYER> used an"
        t_line "ESCAPE ROPE."
        t_done )

};

const struct TextCmd v_CantUseDigText[] = {
    text_start("Can't use that"
        t_line "here."
        t_done )

};

const struct TextCmd v_TeleportReturnText[] = {
    text_start("Return to the last"
        t_line "#MON CENTER."
        t_done )

};

const struct TextCmd v_CantUseTeleportText[] = {
    text_start("Can't use that"
        t_line "here."

        t_para ""
        t_done )

};

const struct TextCmd v_AlreadyUsingStrengthText[] = {
    text_start("A #MON is using"
        t_line "STRENGTH already."
        t_prompt )

};

const struct TextCmd v_UseStrengthText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" used"
        t_line "STRENGTH!"
        t_done )

};

const struct TextCmd v_MoveBoulderText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" can"
        t_line "move boulders."
        t_prompt )

};

const struct TextCmd v_AskStrengthText[] = {
    text_start("A #MON may be"
        t_line "able to move this."

        t_para "Want to use"
        t_line "STRENGTH?"
        t_done )

};

const struct TextCmd v_BouldersMoveText[] = {
    text_start("Boulders may now"
        t_line "be moved!"
        t_done )

};

const struct TextCmd v_BouldersMayMoveText[] = {
    text_start("A #MON may be"
        t_line "able to move this."
        t_done )

};

const struct TextCmd v_UseWhirlpoolText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" used"
        t_line "WHIRLPOOL!"
        t_prompt )

};

const struct TextCmd v_MayPassWhirlpoolText[] = {
    text_start("It's a vicious"
        t_line "whirlpool!"

        t_para "A #MON may be"
        t_line "able to pass it."
        t_done )

};

const struct TextCmd v_AskWhirlpoolText[] = {
    text_start("A whirlpool is in"
        t_line "the way."

        t_para "Want to use"
        t_line "WHIRLPOOL?"
        t_done )

};

const struct TextCmd v_UseHeadbuttText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" did a"
        t_line "HEADBUTT!"
        t_prompt )

};

const struct TextCmd v_HeadbuttNothingText[] = {
    text_start("Nope. Nothing…"
        t_done )

};

const struct TextCmd v_AskHeadbuttText[] = {
    text_start("A #MON could be"
        t_line "in this tree."

        t_para "Want to HEADBUTT"
        t_line "it?"
        t_done )

};

const struct TextCmd v_UseRockSmashText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" used"
        t_line "ROCK SMASH!"
        t_prompt )

};

const struct TextCmd v_MaySmashText[] = {
    text_start("Maybe a #MON"
        t_line "can break this."
        t_done )

};

const struct TextCmd v_AskRockSmashText[] = {
    text_start("This rock looks"
        t_line "breakable."

        t_para "Want to use ROCK"
        t_line "SMASH?"
        t_done )

};

const struct TextCmd v_RodBiteText[] = {
    text_start("Oh!"
        t_line "A bite!"
        t_prompt )

};

const struct TextCmd v_RodNothingText[] = {
    text_start("Not even a nibble!"
        t_prompt )

};

const struct TextCmd v_UnusedNothingHereText[] = {
    text_start("Looks like there's"
        t_line "nothing here."
        t_prompt )

};

const struct TextCmd v_CantGetOffBikeText[] = {
    text_start("You can't get off"
        t_line "here!"
        t_done )

};

const struct TextCmd v_GotOnBikeText[] = {
    text_start("<PLAYER> got on the"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_done )

};

const struct TextCmd v_GotOffBikeText[] = {
    text_start("<PLAYER> got off"
        t_line "the @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_done )

};

const struct TextCmd v_AskCutText[] = {
    text_start("This tree can be"
        t_line "CUT!"

        t_para "Want to use CUT?"
        t_done )

};

const struct TextCmd v_CanCutText[] = {
    text_start("This tree can be"
        t_line "CUT!"
        t_done )

};

const struct TextCmd v_FoundItemText[] = {
    text_start("<PLAYER> found"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )

};

const struct TextCmd v_CantCarryItemText[] = {
    text_start("But <PLAYER> can't"
        t_line "carry any more"
        t_cont "items."
        t_done )

};

const struct TextCmd v_WhitedOutText[] = {
    text_start("<PLAYER> is out of"
        t_line "useable #MON!"

        t_para "<PLAYER> whited"
        t_line "out!"
        t_done )

};

const struct TextCmd v_ItemfinderItemNearbyText[] = {
    text_start("Yes! ITEMFINDER"
        t_line "indicates there's"
        t_cont "an item nearby."
        t_prompt )

};

const struct TextCmd v_ItemfinderNopeText[] = {
    text_start("Nope! ITEMFINDER"
        t_line "isn't responding."
        t_prompt )

};

const struct TextCmd v_PoisonFaintText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "fainted!"
        t_prompt )

};

const struct TextCmd v_PoisonWhiteoutText[] = {
    text_start("<PLAYER> is out of"
        t_line "useable #MON!"

        t_para "<PLAYER> whited"
        t_line "out!"
        t_prompt )

};

const struct TextCmd v_UseSweetScentText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" used"
        t_line "SWEET SCENT!"
        t_done )

};

const struct TextCmd v_SweetScentNothingText[] = {
    text_start("Looks like there's"
        t_line "nothing here…"
        t_done )

};

const struct TextCmd v_SquirtbottleNothingText[] = {
    text_start("<PLAYER> sprinkled"
        t_line "water."

        t_para "But nothing"
        t_line "happened…"
        t_done )

};

const struct TextCmd v_UseSacredAshText[] = {
    text_start("<PLAYER>'s #MON"
        t_line "were all healed!"
        t_done )

};

const struct TextCmd v_AnEggCantHoldAnItemText[] = {
    text_start("An EGG can't hold"
        t_line "an item."
        t_prompt )

};

const struct TextCmd v_PackNoItemText[] = {
    text_start("No items."
        t_done )

};

const struct TextCmd v_AskThrowAwayText[] = {
    text_start("Throw away how"
        t_line "many?"
        t_done )

};

const struct TextCmd v_AskQuantityThrowAwayText[] = {
    text_start("Throw away @"
        )
    text_decimal(wram_ptr(wItemQuantityChange), 1, 2)
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)?"
        t_done )

};

const struct TextCmd v_ThrewAwayText[] = {
    text_start("Threw away"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)."
        t_prompt )

};

const struct TextCmd v_OakThisIsntTheTimeText[] = {
    text_start("OAK: <PLAYER>!"
        t_line "This isn't the"
        t_cont "time to use that!"
        t_prompt )

};

const struct TextCmd v_YouDontHaveAMonText[] = {
    text_start("You don't have a"
        t_line "#MON!"
        t_prompt )

};

const struct TextCmd v_RegisteredItemText[] = {
    text_start("Registered the"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )

};

const struct TextCmd v_CantRegisterText[] = {
    text_start("You can't register"
        t_line "that item."
        t_prompt )

};

const struct TextCmd v_AskItemMoveText[] = {
    text_start("Where should this"
        t_line "be moved to?"
        t_done )

};

const struct TextCmd v_PackEmptyText[] = {
    text_start(
        t_done )

};

const struct TextCmd v_YouCantUseItInABattleText[] = {
    text_start("You can't use it"
        t_line "in a battle."
        t_prompt )

};

const struct TextCmd v_AreYouABoyOrAreYouAGirlText[] = {
    text_start("Are you a boy?"
        t_line "Or are you a girl?"
        t_done )

};

const struct TextCmd v_Text_BattleEffectActivate[] = {
    text_start("<USER>'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_end

    text_end

};

const struct TextCmd v_BattleStatWentWayUpText[] = {
    text_pause
    text_start("<SCROLL>went way up!"
        t_prompt )

};

const struct TextCmd v_BattleStatWentUpText[] = {
    text_start(" went up!"
        t_prompt )

};

const struct TextCmd v_Text_BattleFoeEffectActivate[] = {
    text_start("<TARGET>'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_end

    text_end

};

const struct TextCmd v_BattleStatSharplyFellText[] = {
    text_pause
    text_start("<SCROLL>sharply fell!"
        t_prompt )

};

const struct TextCmd v_BattleStatFellText[] = {
    text_start(" fell!"
        t_prompt )

};

const struct TextCmd v_Text_BattleUser[] = {
    text_start("<USER>@"
        )
    text_end

};

const struct TextCmd v_BattleMadeWhirlwindText[] = {
    text_start(
        t_line "made a whirlwind!"
        t_prompt )

};

const struct TextCmd v_BattleTookSunlightText[] = {
    text_start(
        t_line "took in sunlight!"
        t_prompt )

};

const struct TextCmd v_BattleLoweredHeadText[] = {
    text_start(
        t_line "lowered its head!"
        t_prompt )

};

const struct TextCmd v_BattleGlowingText[] = {
    text_start(
        t_line "is glowing!"
        t_prompt )

};

const struct TextCmd v_BattleFlewText[] = {
    text_start(
        t_line "flew up high!"
        t_prompt )

};

const struct TextCmd v_BattleDugText[] = {
    text_start(
        t_line "dug a hole!"
        t_prompt )

};

const struct TextCmd v_ActorNameText[] = {
    text_start("<USER>@"
        )
    text_end

};

const struct TextCmd v_UsedMove1Text[] = {
    text_start(
        t_line "used @"
        )
    text_end

};

const struct TextCmd v_UsedMove2Text[] = {
    text_start(
        t_line "used @"
        )
    text_end

};

const struct TextCmd v_UsedInsteadText[] = {
    text_start("instead,"
        t_cont "@"
        )
    text_end

};

const struct TextCmd v_MoveNameText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_end

    // text_end

};

const struct TextCmd v_EndUsedMove1Text[] = {
    text_start("!"
        t_done )

};

const struct TextCmd v_EndUsedMove2Text[] = {
    text_start("!"
        t_done )

};

const struct TextCmd v_EndUsedMove3Text[] = {
    text_start("!"
        t_done )

};

const struct TextCmd v_EndUsedMove4Text[] = {
    text_start("!"
        t_done )

};

const struct TextCmd v_EndUsedMove5Text[] = {
    text_start("!"
        t_done )

};

const struct TextCmd v_Text_BreedHuh[] = {
    text_start("Huh?"

        t_para "@"
        )
    text_end

};

const struct TextCmd v_BreedClearboxText[] = {
    text_start(
        t_done )

};

const struct TextCmd v_BreedEggHatchText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" came"
        t_line "out of its EGG!@"
        )
    sound_caught_mon
    text_promptbutton
    text_end

    text_end

};

const struct TextCmd v_BreedAskNicknameText[] = {
    text_start("Give a nickname to"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"
        t_done )

};

const struct TextCmd v_LeftWithDayCareLadyText[] = {
    text_start("It's @"
        )
    text_ram(wram_ptr(wBreedMon2Nickname))
    text_start(
        t_line "that was left with"
        t_cont "the DAY-CARE LADY."
        t_done )

};

const struct TextCmd v_LeftWithDayCareManText[] = {
    text_start("It's @"
        )
    text_ram(wram_ptr(wBreedMon1Nickname))
    text_start(
        t_line "that was left with"
        t_cont "the DAY-CARE MAN."
        t_done )

};

const struct TextCmd v_BreedBrimmingWithEnergyText[] = {
    text_start("It's brimming with"
        t_line "energy."
        t_prompt )

};

const struct TextCmd v_BreedNoInterestText[] = {
    text_start("It has no interest"
        t_line "in @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_BreedAppearsToCareForText[] = {
    text_start("It appears to care"
        t_line "for @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_BreedFriendlyText[] = {
    text_start("It's friendly with"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_BreedShowsInterestText[] = {
    text_start("It shows interest"
        t_line "in @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_EmptyMailboxText[] = {
    text_start("There's no MAIL"
        t_line "here."
        t_prompt )

};

const struct TextCmd v_MailClearedPutAwayText[] = {
    text_start("The cleared MAIL"
        t_line "was put away."
        t_prompt )

};

const struct TextCmd v_MailPackFullText[] = {
    text_start("The PACK is full."
        t_prompt )

};

const struct TextCmd v_MailMessageLostText[] = {
    text_start("The MAIL's message"
        t_line "will be lost. OK?"
        t_done )

};

const struct TextCmd v_MailAlreadyHoldingItemText[] = {
    text_start("It's already hold-"
        t_line "ing an item."
        t_prompt )

};

const struct TextCmd v_MailEggText[] = {
    text_start("An EGG can't hold"
        t_line "any MAIL."
        t_prompt )

};

const struct TextCmd v_MailMovedFromBoxText[] = {
    text_start("The MAIL was moved"
        t_line "from the MAILBOX."
        t_prompt )

};

const struct TextCmd v_YesPromptText[] = {
    text_start("Yes"
        t_prompt )

};

const struct TextCmd v_NoPromptText[] = {
    text_start("No"
        t_prompt )

};

const struct TextCmd v_AnimationTypeText[] = {
    text_decimal(wram_ptr(wcf64), 1, 3)
    text_start(" @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "Animation type @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_end

    text_end

};

const struct TextCmd v_MonNumberText[] = {
    text_start("#MON number?"
        t_done )

};

const struct TextCmd v_WasSentToBillsPCText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" was"
        t_line "sent to BILL's PC."
        t_prompt )

};

const struct TextCmd v_PCGottaHavePokemonText[] = {
    text_start("You gotta have"
        t_line "#MON to call!"
        t_prompt )

};

const struct TextCmd v_PCWhatText[] = {
    text_start("What?"
        t_done )

};

const struct TextCmd v_PCMonHoldingMailText[] = {
    text_start("There is a #MON"
        t_line "holding MAIL."

        t_para "Please remove the"
        t_line "MAIL."
        t_prompt )

};

const struct TextCmd v_PCNoSingleMonText[] = {
    text_start("You don't have a"
        t_line "single #MON!"
        t_prompt )

};

const struct TextCmd v_PCCantDepositLastMonText[] = {
    text_start("You can't deposit"
        t_line "your last #MON!"
        t_prompt )

};

const struct TextCmd v_PCCantTakeText[] = {
    text_start("You can't take any"
        t_line "more #MON."
        t_prompt )

};

const struct TextCmd v_ContestCaughtMonText[] = {
    text_start("Caught @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_prompt )

};

const struct TextCmd v_ContestAskSwitchText[] = {
    text_start("Switch #MON?"
        t_done )

};

const struct TextCmd v_ContestAlreadyCaughtText[] = {
    text_start("You already caught"
        t_line "a @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_ContestJudging_FirstPlaceText[] = {
    text_start("This Bug-Catching"
        t_line "Contest winner is@"
        )
    text_pause
    text_start("…"

        t_para "@"
        )
    text_ram(wram_ptr(wBugContestWinnerName))
    text_start(","
        t_line "who caught a"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!@"
        )
    text_end

};

const struct TextCmd v_ContestJudging_FirstPlaceScoreText[] = {
    text_start(

        t_para "The winning score"
        t_line "was @"
        )
    text_decimal(wram_ptr(wBugContestFirstPlaceScore), 2, 3)
    text_start(" points!"
        t_prompt )

};

const struct TextCmd v_ContestJudging_SecondPlaceText[] = {
    text_start("Placing second was"
        t_line "@"
        )
    text_ram(wram_ptr(wBugContestWinnerName))
    text_start(","

        t_para "who caught a"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!@"
        )
    text_end

};

const struct TextCmd v_ContestJudging_SecondPlaceScoreText[] = {
    text_start(

        t_para "The score was"
        t_line "@"
        )
    text_decimal(wram_ptr(wBugContestSecondPlaceScore), 2, 3)
    text_start(" points!"
        t_prompt )

};

const struct TextCmd v_ContestJudging_ThirdPlaceText[] = {
    text_start("Placing third was"
        t_line "@"
        )
    text_ram(wram_ptr(wBugContestWinnerName))
    text_start(","

        t_para "who caught a"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!@"
        )
    text_end

};

const struct TextCmd v_ContestJudging_ThirdPlaceScoreText[] = {
    text_start(

        t_para "The score was"
        t_line "@"
        )
    text_decimal(wram_ptr(wBugContestThirdPlaceScore), 2, 3)
    text_start(" points!"
        t_prompt )

};

const struct TextCmd v_MagikarpGuruMeasureText[] = {
    text_start("Let me measure"
        t_line "that MAGIKARP."

        t_para "…Hm, it measures"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_KarpGuruRecordText[] = {
    text_start("CURRENT RECORD"

        t_para "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" caught by"
        t_line "@"
        )
    text_ram(wram_ptr(wMagikarpRecordHoldersName))
    text_promptbutton
    text_end

    text_end

};

const struct TextCmd v_LuckyNumberMatchPartyText[] = {
    text_start("Congratulations!"

        t_para "We have a match"
        t_line "with the ID number"

        t_para "of @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" in"
        t_line "your party."
        t_prompt )

};

const struct TextCmd v_LuckyNumberMatchPCText[] = {
    text_start("Congratulations!"

        t_para "We have a match"
        t_line "with the ID number"

        t_para "of @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" in"
        t_line "your PC BOX."
        t_prompt )

};

const struct TextCmd v_CaughtAskNicknameText[] = {
    text_start("Give a nickname to"
        t_line "the @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" you"
        t_cont "received?"
        t_done )

};

const struct TextCmd v_PokecenterPCCantUseText[] = {
    text_start("Bzzzzt! You must"
        t_line "have a #MON to"
        t_cont "use this!"
        t_prompt )

};

const struct TextCmd v_PlayersPCTurnOnText[] = {
    text_start("<PLAYER> turned on"
        t_line "the PC."
        t_prompt )

};

const struct TextCmd v_PlayersPCAskWhatDoText[] = {
    text_start("What do you want"
        t_line "to do?"
        t_done )

};

const struct TextCmd v_PlayersPCHowManyWithdrawText[] = {
    text_start("How many do you"
        t_line "want to withdraw?"
        t_done )

};

const struct TextCmd v_PlayersPCWithdrewItemsText[] = {
    text_start("Withdrew @"
        )
    text_decimal(wram_ptr(wItemQuantityChange), 1, 2)
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)."
        t_prompt )

};

const struct TextCmd v_PlayersPCNoRoomWithdrawText[] = {
    text_start("There's no room"
        t_line "for more items."
        t_prompt )

};

const struct TextCmd v_PlayersPCNoItemsText[] = {
    text_start("No items here!"
        t_prompt )

};

const struct TextCmd v_PlayersPCHowManyDepositText[] = {
    text_start("How many do you"
        t_line "want to deposit?"
        t_done )

};

const struct TextCmd v_PlayersPCDepositItemsText[] = {
    text_start("Deposited @"
        )
    text_decimal(wram_ptr(wItemQuantityChange), 1, 2)
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)."
        t_prompt )

};

const struct TextCmd v_PlayersPCNoRoomDepositText[] = {
    text_start("There's no room to"
        t_line "store items."
        t_prompt )

};

const struct TextCmd v_PokecenterPCTurnOnText[] = {
    text_start("<PLAYER> turned on"
        t_line "the PC."
        t_prompt )

};

const struct TextCmd v_PokecenterPCWhoseText[] = {
    text_start("Access whose PC?"
        t_done )

};

const struct TextCmd v_PokecenterBillsPCText[] = {
    text_start("BILL's PC"
        t_line "accessed."

        t_para "#MON Storage"
        t_line "System opened."
        t_prompt )

};

const struct TextCmd v_PokecenterPlayersPCText[] = {
    text_start("Accessed own PC."

        t_para "Item Storage"
        t_line "System opened."
        t_prompt )

};

const struct TextCmd v_PokecenterOaksPCText[] = {
    text_start("PROF.OAK's PC"
        t_line "accessed."

        t_para "#DEX Rating"
        t_line "System opened."
        t_prompt )

};

const struct TextCmd v_PokecenterPCOaksClosedText[] = {
    text_start("…"
        t_line "Link closed…"
        t_done )

};

const struct TextCmd v_OakPCText1[] = {
    text_start("Want to get your"
        t_line "#DEX rated?"
        t_done )

};

const struct TextCmd v_OakPCText2[] = {
    text_start("Current #DEX"
        t_line "completion level:"
        t_prompt )

};

const struct TextCmd v_OakPCText3[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" #MON seen"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" #MON owned"

        t_para "PROF.OAK's"
        t_line "Rating:"
        t_done )

};

const struct TextCmd v_OakRating01[] = {
    text_start("Look for #MON"
        t_line "in grassy areas!"
        t_done )

};

const struct TextCmd v_OakRating02[] = {
    text_start("Good. I see you"
        t_line "understand how to"
        t_cont "use # BALLS."
        t_done )

};

const struct TextCmd v_OakRating03[] = {
    text_start("You're getting"
        t_line "good at this."

        t_para "But you have a"
        t_line "long way to go."
        t_done )

};

const struct TextCmd v_OakRating04[] = {
    text_start("You need to fill"
        t_line "up the #DEX."

        t_para "Catch different"
        t_line "kinds of #MON!"
        t_done )

};

const struct TextCmd v_OakRating05[] = {
    text_start("You're trying--I"
        t_line "can see that."

        t_para "Your #DEX is"
        t_line "coming together."
        t_done )

};

const struct TextCmd v_OakRating06[] = {
    text_start("To evolve, some"
        t_line "#MON grow,"

        t_para "others use the"
        t_line "effects of STONES."
        t_done )

};

const struct TextCmd v_OakRating07[] = {
    text_start("Have you gotten a"
        t_line "fishing ROD? You"

        t_para "can catch #MON"
        t_line "by fishing."
        t_done )

};

const struct TextCmd v_OakRating08[] = {
    text_start("Excellent! You"
        t_line "seem to like col-"
        t_cont "lecting things!"
        t_done )

};

const struct TextCmd v_OakRating09[] = {
    text_start("Some #MON only"
        t_line "appear during"

        t_para "certain times of"
        t_line "the day."
        t_done )

};

const struct TextCmd v_OakRating10[] = {
    text_start("Your #DEX is"
        t_line "filling up. Keep"
        t_cont "up the good work!"
        t_done )

};

const struct TextCmd v_OakRating11[] = {
    text_start("I'm impressed."
        t_line "You're evolving"

        t_para "#MON, not just"
        t_line "catching them."
        t_done )

};

const struct TextCmd v_OakRating12[] = {
    text_start("Have you met KURT?"
        t_line "His custom BALLS"
        t_cont "should help."
        t_done )

};

const struct TextCmd v_OakRating13[] = {
    text_start("Wow. You've found"
        t_line "more #MON than"

        t_para "the last #DEX"
        t_line "research project."
        t_done )

};

const struct TextCmd v_OakRating14[] = {
    text_start("Are you trading"
        t_line "your #MON?"

        t_para "It's tough to do"
        t_line "this alone!"
        t_done )

};

const struct TextCmd v_OakRating15[] = {
    text_start("Wow! You've hit"
        t_line "200! Your #DEX"
        t_cont "is looking great!"
        t_done )

};

const struct TextCmd v_OakRating16[] = {
    text_start("You've found so"
        t_line "many #MON!"

        t_para "You've really"
        t_line "helped my studies!"
        t_done )

};

const struct TextCmd v_OakRating17[] = {
    text_start("Magnificent! You"
        t_line "could become a"

        t_para "#MON professor"
        t_line "right now!"
        t_done )

};

const struct TextCmd v_OakRating18[] = {
    text_start("Your #DEX is"
        t_line "amazing! You're"

        t_para "ready to turn"
        t_line "professional!"
        t_done )

};

const struct TextCmd v_OakRating19[] = {
    text_start("Whoa! A perfect"
        t_line "#DEX! I've"

        t_para "dreamt about this!"
        t_line "Congratulations!"
        t_done )

};

const struct TextCmd v_OakPCText4[] = {
    text_start("The link to PROF."
        t_line "OAK's PC closed."
        t_done )

};

const struct TextCmd v_TrainerRankingExplanationText[] = {
    text_start("Triple-theme"
        t_line "trainer ranking!"

        t_para "The SAVE file you"
        t_line "just sent might"
        t_cont "make the rankings!"

        t_para ""
        t_done )

};

const struct TextCmd v_TrainerRankingNoDataText[] = {
    text_start("There is no"
        t_line "ranking data."

        t_para "Link to obtain"
        t_line "ranking data."

        t_para ""
        t_done )

};

const struct TextCmd v_MemoryGameYeahText[] = {
    text_start(" , yeah!"
        t_done )

};

const struct TextCmd v_MemoryGameDarnText[] = {
    text_start("Darn…"
        t_done )

};

const struct TextCmd v_StartMenuContestEndText[] = {
    text_start("Would you like to"
        t_line "end the Contest?"
        t_done )

};

const struct TextCmd v_ItemsTossOutHowManyText[] = {
    text_start("Toss out how many"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)?"
        t_done )

};

const struct TextCmd v_ItemsThrowAwayText[] = {
    text_start("Throw away @"
        )
    text_decimal(wram_ptr(wItemQuantityChange), 1, 2)
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)?"
        t_done )

};

const struct TextCmd v_ItemsDiscardedText[] = {
    text_start("Discarded"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("(S)."
        t_prompt )

};

const struct TextCmd v_ItemsTooImportantText[] = {
    text_start("That's too impor-"
        t_line "tant to toss out!"
        t_prompt )

};

const struct TextCmd v_ItemsOakWarningText[] = {
    text_start("OAK: <PLAYER>!"
        t_line "This isn't the"
        t_cont "time to use that!"
        t_done )

};

const struct TextCmd v_PokemonSwapItemText[] = {
    text_start("Took @"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start("'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" and"

        t_para "made it hold"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )

};

const struct TextCmd v_PokemonHoldItemText[] = {
    text_start("Made @"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(
        t_line "hold @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )

};

const struct TextCmd v_PokemonRemoveMailText[] = {
    text_start("Please remove the"
        t_line "MAIL first."
        t_prompt )

};

const struct TextCmd v_PokemonNotHoldingText[] = {
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(" isn't"
        t_line "holding anything."
        t_prompt )

};

const struct TextCmd v_ItemStorageFullText[] = {
    text_start("Item storage space"
        t_line "full."
        t_prompt )

};

const struct TextCmd v_PokemonTookItemText[] = {
    text_start("Took @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "from @"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start("."
        t_prompt )

};

const struct TextCmd v_PokemonAskSwapItemText[] = {
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(" is"
        t_line "already holding"

        t_para "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_line "Switch items?"
        t_done )

};

const struct TextCmd v_ItemCantHeldText[] = {
    text_start("This item can't be"
        t_line "held."
        t_prompt )

};

const struct TextCmd v_MailLoseMessageText[] = {
    text_start("The MAIL will lose"
        t_line "its message. OK?"
        t_done )

};

const struct TextCmd v_MailDetachedText[] = {
    text_start("MAIL detached from"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const struct TextCmd v_MailNoSpaceText[] = {
    text_start("There's no space"
        t_line "for removing MAIL."
        t_prompt )

};

const struct TextCmd v_MailAskSendToPCText[] = {
    text_start("Send the removed"
        t_line "MAIL to your PC?"
        t_done )

};

const struct TextCmd v_MailboxFullText[] = {
    text_start("Your PC's MAILBOX"
        t_line "is full."
        t_prompt )

};

const struct TextCmd v_MailSentToPCText[] = {
    text_start("The MAIL was sent"
        t_line "to your PC."
        t_prompt )

};

const struct TextCmd v_PokemonNotEnoughHPText[] = {
    text_start("Not enough HP!"
        t_prompt )

};

const struct TextCmd v_MayRegisterItemText[] = {
    text_start("An item in your"
        t_line "PACK may be"

        t_para "registered for use"
        t_line "on SELECT Button."
        t_done )

};

const struct TextCmd v_OakText1[] = {
    text_start("Hello! Sorry to"
        t_line "keep you waiting!"

        t_para "Welcome to the"
        t_line "world of #MON!"

        t_para "My name is OAK."

        t_para "People call me the"
        t_line "#MON PROF."
        t_prompt )

};

const struct TextCmd v_OakText2[] = {
    text_start("This world is in-"
        t_line "habited by crea-"
        t_cont "tures that we call"
        t_cont "#MON.@"
        )
    text_end

};

const struct TextCmd v_OakText3[] = {
    text_promptbutton
    text_end

    text_end

};

const struct TextCmd v_OakText4[] = {
    text_start("People and #MON"
        t_line "live together by"

        t_para "supporting each"
        t_line "other."

        t_para "Some people play"
        t_line "with #MON, some"
        t_cont "battle with them."
        t_prompt )

};

const struct TextCmd v_OakText5[] = {
    text_start("But we don't know"
        t_line "everything about"
        t_cont "#MON yet."

        t_para "There are still"
        t_line "many mysteries to"
        t_cont "solve."

        t_para "That's why I study"
        t_line "#MON every day."
        t_prompt )
};
