#include "../../constants.h"
const txt_cmd_s v_FruitBearingTreeText[] = {
    text_start("It's a fruit-"
        t_line "bearing tree."
        t_done )

};

const txt_cmd_s v_HeyItsFruitText[] = {
    text_start("Hey! It's"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )

};

const txt_cmd_s v_ObtainedFruitText[] = {
    text_start("Obtained"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )

};

const txt_cmd_s v_FruitPackIsFullText[] = {
    text_start("But the PACK is"
        t_line "full…"
        t_done )

};

const txt_cmd_s v_NothingHereText[] = {
    text_start("There's nothing"
        t_line "here…"
        t_done )

};

const txt_cmd_s v_WhichApricornText[] = {
    text_start("Which APRICORN"
        t_line "should I use?"
        t_done )

};

const txt_cmd_s v_HowManyShouldIMakeText[] = {
    text_start("How many should I"
        t_line "make?"
        t_done )

};

const txt_cmd_s v_RecoveredSomeHPText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "recovered @"
        )
    text_decimal(wram_ptr(wCurHPAnimDeltaHP), 2, 3)
    text_start("HP!"
        t_done )

};

const txt_cmd_s v_CuredOfPoisonText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s"
        t_line "cured of poison."
        t_done )

};

const txt_cmd_s v_RidOfParalysisText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s"
        t_line "rid of paralysis."
        t_done )

};

const txt_cmd_s v_BurnWasHealedText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s"
        t_line "burn was healed."
        t_done )

};

const txt_cmd_s v_WasDefrostedText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "was defrosted."
        t_done )

};

const txt_cmd_s v_WokeUpText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "woke up."
        t_done )

};

const txt_cmd_s v_HealthReturnedText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s"
        t_line "health returned."
        t_done )

};

const txt_cmd_s v_RevitalizedText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "is revitalized."
        t_done )

};

const txt_cmd_s v_GrewToLevelText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" grew to"
        t_line "level @"
        )
    text_decimal(wram_ptr(wCurPartyLevel), 1, 3)
    text_start("!@"
        )
    sound_dex_fanfare_50_79 // plays SFX_DEX_FANFARE_50_79, identical to SFX_LEVEL_UP
    text_promptbutton
    text_end

    text_end

};

const txt_cmd_s v_CameToItsSensesText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" came"
        t_line "to its senses."
        t_done )

};

const txt_cmd_s v_EnterNewPasscodeText[] = {
    text_start("Please enter any"
        t_line "four-digit number."
        t_done )

};

const txt_cmd_s v_ConfirmPasscodeText[] = {
    text_start("Enter the same"
        t_line "number to confirm."
        t_done )

};

const txt_cmd_s v_PasscodesNotSameText[] = {
    text_start("That's not the"
        t_line "same number."
        t_done )

};

const txt_cmd_s v_PasscodeSetText[] = {
    text_start("Your PASSCODE has"
        t_line "been set."

        t_para "Enter this number"
        t_line "next time to open"
        t_cont "the CARD FOLDER."

        t_para ""
        t_done )

};

const txt_cmd_s v_FourZerosInvalidText[] = {
    text_start("0000 is invalid!"

        t_para ""
        t_done )

};

const txt_cmd_s v_EnterPasscodeText[] = {
    text_start("Enter the CARD"
        t_next "FOLDER PASSCODE."
        t_done )

};

const txt_cmd_s v_IncorrectPasscodeText[] = {
    text_start("Incorrect"
        t_line "PASSCODE!"

        t_para ""
        t_done )

};

const txt_cmd_s v_CardFolderOpenText[] = {
    text_start("CARD FOLDER open.@"
        )
    text_end

};

const txt_cmd_s v_OakTimeWokeUpText[] = {
    text_start("<……><……><……><……><……><……>"
        t_line "<……><……><……><……><……><……>"

        t_para "Zzz… Hm? Wha…?"
        t_line "You woke me up!"

        t_para "Will you check the"
        t_line "clock for me?"
        t_prompt )

};

const txt_cmd_s v_OakTimeWhatTimeIsItText[] = {
    text_start("What time is it?"
        t_done )

};

const txt_cmd_s v_OakTimeWhatHoursText[] = {
    text_start("What?@"
        )
    text_end

};

const txt_cmd_s v_OakTimeHoursQuestionMarkText[] = {
    text_start("?"
        t_done )

};

const txt_cmd_s v_OakTimeHowManyMinutesText[] = {
    text_start("How many minutes?"
        t_done )

};

const txt_cmd_s v_OakTimeWhoaMinutesText[] = {
    text_start("Whoa!@"
        )
    text_end

};

const txt_cmd_s v_OakTimeMinutesQuestionMarkText[] = {
    text_start("?"
        t_done )

};

const txt_cmd_s v_OakTimeOversleptText[] = {
    text_start("!"
        t_line "I overslept!"
        t_done )

};

const txt_cmd_s v_OakTimeYikesText[] = {
    text_start("!"
        t_line "Yikes! I over-"
        t_cont "slept!"
        t_done )

};

const txt_cmd_s v_OakTimeSoDarkText[] = {
    text_start("!"
        t_line "No wonder it's so"
        t_cont "dark!"
        t_done )

};

const txt_cmd_s v_OakTimeWhatDayIsItText[] = {
    text_start("What day is it?"
        t_done )

};

const txt_cmd_s v_OakTimeIsItText[] = {
    text_start(", is it?"
        t_done )



};

const txt_cmd_s v_ThereIsNothingConnectedText[] = {
    text_start("There is nothing"
        t_line "connected."
        t_done )

};

const txt_cmd_s v_CheckCellPhoneAdapterText[] = {
    text_start("Check cell phone"
        t_line "adapter."
        t_done )

};

const txt_cmd_s v_CheckCDMAAdapterText[] = {
    text_start("Check CDMA"
        t_line "adapter."
        t_done )

};

const txt_cmd_s v_CheckDOCOMOPHSAdapterText[] = {
    text_start("Check DOCOMO PHS"
        t_line "adapter."
        t_done )

};

const txt_cmd_s v_CheckDDIPHSAdapterText[] = {
    text_start("Check DDI PHS"
        t_line "adapter."
        t_done )

};

const txt_cmd_s v_CheckMobileAdapterText[] = {
    text_start("Check unlimited"
        t_line "battle mobile"
        t_cont "adapter."
        t_done )



};

const txt_cmd_s v_ThePasswordIsText[] = {
    text_start("The password is:"
        t_line ""
        t_done )

};

const txt_cmd_s v_IsThisOKText[] = {
    text_start("Is this OK?"
        t_done )

};

const txt_cmd_s v_EnterTheIDNoText[] = {
    text_start("Enter the"
        t_line "ID no."
        t_done )

};

const txt_cmd_s v_EnterTheAmountText[] = {
    text_start("Enter the"
        t_line "amount."
        t_done )

};

const txt_cmd_s v_NothingToChooseText[] = {
    text_start("There's nothing to"
        t_line "choose."
        t_prompt )

};

const txt_cmd_s v_WhichSidePutOnText[] = {
    text_start("Which side do you"
        t_line "want to put it on?"
        t_done )

};

const txt_cmd_s v_WhichSidePutAwayText[] = {
    text_start("Which side do you"
        t_line "want to put away?"
        t_done )

};

const txt_cmd_s v_PutAwayTheDecoText[] = {
    text_start("Put away the"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_NothingToPutAwayText[] = {
    text_start("There's nothing to"
        t_line "put away."
        t_prompt )

};

const txt_cmd_s v_SetUpTheDecoText[] = {
    text_start("Set up the"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_PutAwayAndSetUpText[] = {
    text_start("Put away the"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start(

        t_para "and set up the"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_AlreadySetUpText[] = {
    text_start("That's already set"
        t_line "up."
        t_prompt )

};

const txt_cmd_s v_LookTownMapText[] = {
    text_start("It's the TOWN MAP."
        t_done )

};

const txt_cmd_s v_LookPikachuPosterText[] = {
    text_start("It's a poster of a"
        t_line "cute PIKACHU."
        t_done )

};

const txt_cmd_s v_LookClefairyPosterText[] = {
    text_start("It's a poster of a"
        t_line "cute CLEFAIRY."
        t_done )

};

const txt_cmd_s v_LookJigglypuffPosterText[] = {
    text_start("It's a poster of a"
        t_line "cute JIGGLYPUFF."
        t_done )

};

const txt_cmd_s v_LookAdorableDecoText[] = {
    text_start("It's an adorable"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )

};

const txt_cmd_s v_LookGiantDecoText[] = {
    text_start("A giant doll! It's"
        t_line "fluffy and cuddly."
        t_done )

};

const txt_cmd_s v_MomHiHowAreYouText[] = {
    text_start("Hi, <PLAYER>!"
        t_line "How are you?"
        t_prompt )

};

const txt_cmd_s v_MomFoundAnItemText[] = {
    text_start("I found a useful"
        t_line "item shopping, so"
        t_prompt )

};

const txt_cmd_s v_MomBoughtWithYourMoneyText[] = {
    text_start("I bought it with"
        t_line "your money. Sorry!"
        t_prompt )

};

const txt_cmd_s v_MomItsInPCText[] = {
    text_start("It's in your PC."
        t_line "You'll like it!"
        t_done )

};

const txt_cmd_s v_MomFoundADollText[] = {
    text_start("While shopping"
        t_line "today, I saw this"
        t_cont "adorable doll, so"
        t_prompt )

};

const txt_cmd_s v_MomItsInYourRoomText[] = {
    text_start("It's in your room."
        t_line "You'll love it!"
        t_done )

};

const txt_cmd_s v_MonWasSentToText[] = {
    text_ram(wram_ptr(wPlayerTrademonSpeciesName))
    text_start(" was"
        t_line "sent to @"
        )
    text_ram(wram_ptr(wOTTrademonSenderName))
    text_start("."
        t_done )

};

const txt_cmd_s v_MonNameSentToText[] = {
    text_start(
        t_done )

};

const txt_cmd_s v_BidsFarewellToMonText[] = {
    text_ram(wram_ptr(wOTTrademonSenderName))
    text_start(" bids"
        t_line "farewell to"
        t_done )

};

const txt_cmd_s v_MonNameBidsFarewellText[] = {
    text_ram(wram_ptr(wOTTrademonSpeciesName))
    text_start("."
        t_done )

};

const txt_cmd_s v_TakeGoodCareOfMonText[] = {
    text_start("Take good care of"
        t_line "@"
        )
    text_ram(wram_ptr(wOTTrademonSpeciesName))
    text_start("."
        t_done )

};

const txt_cmd_s v_ForYourMonSendsText[] = {
    text_start("For @"
        )
    text_ram(wram_ptr(wPlayerTrademonSenderName))
    text_start("'s"
        t_line "@"
        )
    text_ram(wram_ptr(wPlayerTrademonSpeciesName))
    text_start(","
        t_done )

};

const txt_cmd_s v_OTSendsText[] = {
    text_ram(wram_ptr(wOTTrademonSenderName))
    text_start(" sends"
        t_line "@"
        )
    text_ram(wram_ptr(wOTTrademonSpeciesName))
    text_start("."
        t_done )

};

const txt_cmd_s v_WillTradeText[] = {
    text_ram(wram_ptr(wOTTrademonSenderName))
    text_start(" will"
        t_line "trade @"
        )
    text_ram(wram_ptr(wOTTrademonSpeciesName))
    text_end

    text_end

};

const txt_cmd_s v_ForYourMonWillTradeText[] = {
    text_start("for @"
        )
    text_ram(wram_ptr(wPlayerTrademonSenderName))
    text_start("'s"
        t_line "@"
        )
    text_ram(wram_ptr(wPlayerTrademonSpeciesName))
    text_start("."
        t_done )

};

const txt_cmd_s v_MobilePlayerWillTradeMonText[] = {
    text_ram(wram_ptr(wPlayerTrademonSenderName))
    text_start(" will"
        t_line "trade @"
        )
    text_ram(wram_ptr(wPlayerTrademonSpeciesName))
    text_end

    text_end

};

const txt_cmd_s v_MobileForPartnersMonText[] = {
    text_start("for @"
        )
    text_ram(wram_ptr(wOTTrademonSenderName))
    text_start("'s"
        t_line "@"
        )
    text_ram(wram_ptr(wOTTrademonSpeciesName))
    text_start("."
        t_done )

};

const txt_cmd_s v_MobilePlayersMonTradeText[] = {
    text_ram(wram_ptr(wPlayerTrademonSenderName))
    text_start("'s"
        t_line "@"
        )
    text_ram(wram_ptr(wPlayerTrademonSpeciesName))
    text_start(" trade…"
        t_done )

};

const txt_cmd_s v_MobileTakeGoodCareOfMonText[] = {
    text_start("Take good care of"
        t_line "@"
        )
    text_ram(wram_ptr(wOTTrademonSpeciesName))
    text_start("."
        t_done )

};

const txt_cmd_s v_MobilePlayersMonTrade2Text[] = {
    text_ram(wram_ptr(wPlayerTrademonSenderName))
    text_start("'s"
        t_line "@"
        )
    text_ram(wram_ptr(wPlayerTrademonSpeciesName))
    text_start(" trade…"
        t_done )

};

const txt_cmd_s v_MobileTakeGoodCareOfText[] = {
    text_start("Take good care of"
        t_line "@"
        )
    text_ram(wram_ptr(wOTTrademonSpeciesName))
    text_start("."
        t_done )

};

const txt_cmd_s v_MobileTradeCameBackText[] = {
    text_ram(wram_ptr(wOTTrademonSpeciesName))
    text_start(" came"
        t_line "back!"
        t_done )



};

const txt_cmd_s v_OPT_IntroText1[] = {
    text_start(
        t_line "MARY: PROF.OAK'S"
        t_done )

};

const txt_cmd_s v_OPT_IntroText2[] = {
    text_start(
        t_line "#MON TALK!"
        t_done )

};

const txt_cmd_s v_OPT_IntroText3[] = {
    text_start(
        t_line "With me, MARY!"
        t_done )

};

const txt_cmd_s v_OPT_OakText1[] = {
    text_start(
        t_line "OAK: @"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_end

    text_end

};

const txt_cmd_s v_OPT_OakText2[] = {
    text_start(
        t_line "may be seen around"
        t_done )

};

const txt_cmd_s v_OPT_OakText3[] = {
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_done )

};

const txt_cmd_s v_OPT_MaryText1[] = {
    text_start(
        t_line "MARY: @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s"
        t_done )

};

const txt_cmd_s v_OPT_SweetAdorablyText[] = {
    text_start(
        t_line "sweet and adorably"
        t_done )

};

const txt_cmd_s v_OPT_WigglySlicklyText[] = {
    text_start(
        t_line "wiggly and slickly"
        t_done )

};

const txt_cmd_s v_OPT_AptlyNamedText[] = {
    text_start(
        t_line "aptly named and"
        t_done )

};

const txt_cmd_s v_OPT_UndeniablyKindOfText[] = {
    text_start(
        t_line "undeniably kind of"
        t_done )

};

const txt_cmd_s v_OPT_UnbearablyText[] = {
    text_start(
        t_line "so, so unbearably"
        t_done )

};

const txt_cmd_s v_OPT_WowImpressivelyText[] = {
    text_start(
        t_line "wow, impressively"
        t_done )

};

const txt_cmd_s v_OPT_AlmostPoisonouslyText[] = {
    text_start(
        t_line "almost poisonously"
        t_done )

};

const txt_cmd_s v_OPT_SensuallyText[] = {
    text_start(
        t_line "ooh, so sensually"
        t_done )

};

const txt_cmd_s v_OPT_MischievouslyText[] = {
    text_start(
        t_line "so mischievously"
        t_done )

};

const txt_cmd_s v_OPT_TopicallyText[] = {
    text_start(
        t_line "so very topically"
        t_done )

};

const txt_cmd_s v_OPT_AddictivelyText[] = {
    text_start(
        t_line "sure addictively"
        t_done )

};

const txt_cmd_s v_OPT_LooksInWaterText[] = {
    text_start(
        t_line "looks in water is"
        t_done )

};

const txt_cmd_s v_OPT_EvolutionMustBeText[] = {
    text_start(
        t_line "evolution must be"
        t_done )

};

const txt_cmd_s v_OPT_ProvocativelyText[] = {
    text_start(
        t_line "provocatively"
        t_done )

};

const txt_cmd_s v_OPT_FlippedOutText[] = {
    text_start(
        t_line "so flipped out and"
        t_done )

};

const txt_cmd_s v_OPT_HeartMeltinglyText[] = {
    text_start(
        t_line "heart-meltingly"
        t_done )

};

const txt_cmd_s v_OPT_CuteText[] = {
    text_start(
        t_line "cute."
        t_done )

};

const txt_cmd_s v_OPT_WeirdText[] = {
    text_start(
        t_line "weird."
        t_done )

};

const txt_cmd_s v_OPT_PleasantText[] = {
    text_start(
        t_line "pleasant."
        t_done )

};

const txt_cmd_s v_OPT_BoldSortOfText[] = {
    text_start(
        t_line "bold, sort of."
        t_done )

};

const txt_cmd_s v_OPT_FrighteningText[] = {
    text_start(
        t_line "frightening."
        t_done )

};

const txt_cmd_s v_OPT_SuaveDebonairText[] = {
    text_start(
        t_line "suave & debonair!"
        t_done )

};

const txt_cmd_s v_OPT_PowerfulText[] = {
    text_start(
        t_line "powerful."
        t_done )

};

const txt_cmd_s v_OPT_ExcitingText[] = {
    text_start(
        t_line "exciting."
        t_done )

};

const txt_cmd_s v_OPT_GroovyText[] = {
    text_start(
        t_line "groovy!"
        t_done )

};

const txt_cmd_s v_OPT_InspiringText[] = {
    text_start(
        t_line "inspiring."
        t_done )

};

const txt_cmd_s v_OPT_FriendlyText[] = {
    text_start(
        t_line "friendly."
        t_done )

};

const txt_cmd_s v_OPT_HotHotHotText[] = {
    text_start(
        t_line "hot, hot, hot!"
        t_done )

};

const txt_cmd_s v_OPT_StimulatingText[] = {
    text_start(
        t_line "stimulating."
        t_done )

};

const txt_cmd_s v_OPT_GuardedText[] = {
    text_start(
        t_line "guarded."
        t_done )

};

const txt_cmd_s v_OPT_LovelyText[] = {
    text_start(
        t_line "lovely."
        t_done )

};

const txt_cmd_s v_OPT_SpeedyText[] = {
    text_start(
        t_line "speedy."
        t_done )

};

const txt_cmd_s v_OPT_PokemonChannelText[] = {
    text_start("#MON"
        t_done )

};

const txt_cmd_s v_PokedexShowText[] = {
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_end

    text_end



};

const txt_cmd_s v_BenIntroText1[] = {
    text_start(
        t_line "BEN: #MON MUSIC"
        t_done )

};

const txt_cmd_s v_BenIntroText2[] = {
    text_start(
        t_line "CHANNEL!"
        t_done )

};

const txt_cmd_s v_BenIntroText3[] = {
    text_start(
        t_line "It's me, DJ BEN!"
        t_done )

};

const txt_cmd_s v_FernIntroText1[] = {
    text_start(
        t_line "FERN: #MUSIC!"
        t_done )

};

const txt_cmd_s v_FernIntroText2[] = {
    text_start(
        t_line "With DJ FERN!"
        t_done )

};

const txt_cmd_s v_BenFernText1[] = {
    text_start(
        t_line "Today's @"
        )
    text_today
    text_start(","
        t_done )

};

const txt_cmd_s v_BenFernText2A[] = {
    text_start(
        t_line "so let us jam to"
        t_done )

};

const txt_cmd_s v_BenFernText2B[] = {
    text_start(
        t_line "so chill out to"
        t_done )

};

const txt_cmd_s v_BenFernText3A[] = {
    text_start(
        t_line "#MON March!"
        t_done )

};

const txt_cmd_s v_BenFernText3B[] = {
    text_start(
        t_line "#MON Lullaby!"
        t_done )



};

const txt_cmd_s v_LC_Text1[] = {
    text_start(
        t_line "REED: Yeehaw! How"
        t_done )

};

const txt_cmd_s v_LC_Text2[] = {
    text_start(
        t_line "y'all doin' now?"
        t_done )

};

const txt_cmd_s v_LC_Text3[] = {
    text_start(
        t_line "Whether you're up"
        t_done )

};

const txt_cmd_s v_LC_Text4[] = {
    text_start(
        t_line "or way down low,"
        t_done )

};

const txt_cmd_s v_LC_Text5[] = {
    text_start(
        t_line "don't you miss the"
        t_done )

};

const txt_cmd_s v_LC_Text6[] = {
    text_start(
        t_line "LUCKY NUMBER SHOW!"
        t_done )

};

const txt_cmd_s v_LC_Text7[] = {
    text_start(
        t_line "This week's Lucky"
        t_done )

};

const txt_cmd_s v_LC_Text8[] = {
    text_start(
        t_line "Number is @"
        )
    text_pause
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_done )

};

const txt_cmd_s v_LC_Text9[] = {
    text_start(
        t_line "I'll repeat that!"
        t_done )

};

const txt_cmd_s v_LC_Text10[] = {
    text_start(
        t_line "Match it and go to"
        t_done )

};

const txt_cmd_s v_LC_Text11[] = {
    text_start(
        t_line "the RADIO TOWER!"
        t_done )

};

const txt_cmd_s v_LC_DragText1[] = {
    text_start(
        t_line "…Repeating myself"
        t_done )

};

const txt_cmd_s v_LC_DragText2[] = {
    text_start(
        t_line "gets to be a drag…"
        t_done )



};

const txt_cmd_s v_PnP_Text1[] = {
    text_start(
        t_line "PLACES AND PEOPLE!"
        t_done )

};

const txt_cmd_s v_PnP_Text2[] = {
    text_start(
        t_line "Brought to you by"
        t_done )

};

const txt_cmd_s v_PnP_Text3[] = {
    text_start(
        t_line "me, DJ LILY!"
        t_done )

};

const txt_cmd_s v_PnP_Text4[] = {
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_end

    text_end

};

const txt_cmd_s v_PnP_CuteText[] = {
    text_start(
        t_line "is cute."
        t_done )

};

const txt_cmd_s v_PnP_LazyText[] = {
    text_start(
        t_line "is sort of lazy."
        t_done )

};

const txt_cmd_s v_PnP_HappyText[] = {
    text_start(
        t_line "is always happy."
        t_done )

};

const txt_cmd_s v_PnP_NoisyText[] = {
    text_start(
        t_line "is quite noisy."
        t_done )

};

const txt_cmd_s v_PnP_PrecociousText[] = {
    text_start(
        t_line "is precocious."
        t_done )

};

const txt_cmd_s v_PnP_BoldText[] = {
    text_start(
        t_line "is somewhat bold."
        t_done )

};

const txt_cmd_s v_PnP_PickyText[] = {
    text_start(
        t_line "is too picky!"
        t_done )

};

const txt_cmd_s v_PnP_SortOfOKText[] = {
    text_start(
        t_line "is sort of OK."
        t_done )

};

const txt_cmd_s v_PnP_SoSoText[] = {
    text_start(
        t_line "is just so-so."
        t_done )

};

const txt_cmd_s v_PnP_GreatText[] = {
    text_start(
        t_line "is actually great."
        t_done )

};

const txt_cmd_s v_PnP_MyTypeText[] = {
    text_start(
        t_line "is just my type."
        t_done )

};

const txt_cmd_s v_PnP_CoolText[] = {
    text_start(
        t_line "is so cool, no?"
        t_done )

};

const txt_cmd_s v_PnP_InspiringText[] = {
    text_start(
        t_line "is inspiring!"
        t_done )

};

const txt_cmd_s v_PnP_WeirdText[] = {
    text_start(
        t_line "is kind of weird."
        t_done )

};

const txt_cmd_s v_PnP_RightForMeText[] = {
    text_start(
        t_line "is right for me?"
        t_done )

};

const txt_cmd_s v_PnP_OddText[] = {
    text_start(
        t_line "is definitely odd!"
        t_done )

};

const txt_cmd_s v_PnP_Text5[] = {
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_end

    text_end

};

const txt_cmd_s v_RocketRadioText1[] = {
    text_start(
        t_line "… …Ahem, we are"
        t_done )

};

const txt_cmd_s v_RocketRadioText2[] = {
    text_start(
        t_line "TEAM ROCKET!"
        t_done )

};

const txt_cmd_s v_RocketRadioText3[] = {
    text_start(
        t_line "After three years"
        t_done )

};

const txt_cmd_s v_RocketRadioText4[] = {
    text_start(
        t_line "of preparation, we"
        t_done )

};

const txt_cmd_s v_RocketRadioText5[] = {
    text_start(
        t_line "have risen again"
        t_done )

};

const txt_cmd_s v_RocketRadioText6[] = {
    text_start(
        t_line "from the ashes!"
        t_done )

};

const txt_cmd_s v_RocketRadioText7[] = {
    text_start(
        t_line "GIOVANNI! @"
        )
    text_pause
    text_start("Can you"
        t_done )

};

const txt_cmd_s v_RocketRadioText8[] = {
    text_start(
        t_line "hear?@"
        )
    text_pause
    text_start(" We did it!"
        t_done )

};

const txt_cmd_s v_RocketRadioText9[] = {
    text_start(
        t_line "@"
        )
    text_pause
    text_start("Where is our boss?"
        t_done )

};

const txt_cmd_s v_RocketRadioText10[] = {
    text_start(
        t_line "@"
        )
    text_pause
    text_start("Is he listening?"
        t_done )

};

const txt_cmd_s v_BuenaRadioText1[] = {
    text_start(
        t_line "BUENA: BUENA here!"
        t_done )

};

const txt_cmd_s v_BuenaRadioText2[] = {
    text_start(
        t_line "Today's password!"
        t_done )

};

const txt_cmd_s v_BuenaRadioText3[] = {
    text_start(
        t_line "Let me think… It's"
        t_done )

};

const txt_cmd_s v_BuenaRadioText4[] = {
    text_start(
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_done )

};

const txt_cmd_s v_BuenaRadioText5[] = {
    text_start(
        t_line "Don't forget it!"
        t_done )

};

const txt_cmd_s v_BuenaRadioText6[] = {
    text_start(
        t_line "I'm in GOLDENROD's"
        t_done )

};

const txt_cmd_s v_BuenaRadioText7[] = {
    text_start(
        t_line "RADIO TOWER!"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText1[] = {
    text_start(
        t_line "BUENA: Oh my…"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText2[] = {
    text_start(
        t_line "It's midnight! I"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText3[] = {
    text_start(
        t_line "have to shut down!"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText4[] = {
    text_start(
        t_line "Thanks for tuning"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText5[] = {
    text_start(
        t_line "in to the end! But"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText6[] = {
    text_start(
        t_line "don't stay up too"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText7[] = {
    text_start(
        t_line "late! Presented to"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText8[] = {
    text_start(
        t_line "you by DJ BUENA!"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText9[] = {
    text_start("I'm outta here!"
        t_done )

};

const txt_cmd_s v_BuenaRadioMidnightText10[] = {
    text_start("…"
        t_done )

};

const txt_cmd_s v_BuenaOffTheAirText[] = {
    text_start(
        t_line ""
        t_done )

};

const txt_cmd_s v_EnemyWithdrewText[] = {
    text_start("<ENEMY>"
        t_line "withdrew"
        t_cont "@"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start("!"
        t_prompt )

};

const txt_cmd_s v_EnemyUsedOnText[] = {
    text_start("<ENEMY>"
        t_line "used @"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(
        t_cont "on @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start("!"
        t_prompt )

};

const txt_cmd_s v_ThatCantBeUsedRightNowText[] = {
    text_start("That can't be used"
        t_line "right now."
        t_prompt )

};

const txt_cmd_s v_ThatItemCantBePutInThePackText[] = {
    text_start("That item can't be"
        t_line "put in the PACK."
        t_done )

};

const txt_cmd_s v_TheItemWasPutInThePackText[] = {
    text_start("The @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "was put in the"
        t_cont "PACK."
        t_done )

};

const txt_cmd_s v_RemainingTimeText[] = {
    text_start("Remaining Time"
        t_done )

};

const txt_cmd_s v_YourMonsHPWasHealedText[] = {
    text_start("Your #MON's HP"
        t_line "was healed."
        t_prompt )

};

const txt_cmd_s v_WarpingText[] = {
    text_start("Warping…"
        t_done )

};

const txt_cmd_s v_ChangeWhichNumberText[] = {
    text_start("Which number"
        t_line "should be changed?"
        t_done )

};

const txt_cmd_s v_WillYouPlayWithMonText[] = {
    text_start("Will you play with"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("?"
        t_done )

};

const txt_cmd_s v_YouNeedTwoMonForBreedingText[] = {
    text_start("You need two #-"
        t_line "MON for breeding."
        t_prompt )

};

const txt_cmd_s v_BreedingIsNotPossibleText[] = {
    text_start("Breeding is not"
        t_line "possible."
        t_prompt )

};

const txt_cmd_s v_CompatibilityShouldTheyBreedText[] = {
    text_start("The compatibility"
        t_line "is @"
        )
    text_decimal(wram_ptr(wBreedingCompatibility), 1, 3)
    text_start("."
        t_cont "Should they breed?"
        t_done )

};

const txt_cmd_s v_ThereIsNoEggText[] = {
    text_start("There is no EGG."
        t_line ""
        t_prompt )

};

const txt_cmd_s v_ItsGoingToHatchText[] = {
    text_start("It's going to"
        t_line "hatch!"
        t_prompt )

};

const txt_cmd_s v_TestEventText[] = {
    text_start("Test event"
        t_line "@"
        )
    text_decimal(wram_ptr(wStringBuffer2), 1, 2)
    text_start("?"
        t_done )

};

const txt_cmd_s v_StartText[] = {
    text_start("Start!"
        t_done )

};

const txt_cmd_s v_EndText[] = {
    text_start("End!"
        t_done )

};

const txt_cmd_s v_ForABoyText[] = {
    text_start("For a boy!"
        t_done )

};

const txt_cmd_s v_ForAGirlText[] = {
    text_start("For a girl!"
        t_done )

};

const txt_cmd_s v_DoesntConcernABoyText[] = {
    text_start("This doesn't"
        t_line "concern a boy!"
        t_done )

};

const txt_cmd_s v_TheBoxIsFullText[] = {
    text_start("The BOX is full!"
        t_done )



};

const txt_cmd_s v_NewCardArrivedText[] = {
    text_start("A new CARD arrived"
        t_line "from @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_done )

};

const txt_cmd_s v_PutCardInCardFolderText[] = {
    text_start("Put this CARD in"
        t_line "the CARD FOLDER?"
        t_done )

};

const txt_cmd_s v_CardWasListedText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start("'s CARD was"
        t_line "listed as no.@"
        )
    text_decimal(wram_ptr(wStringBuffer1), 1, 2)
    text_start("."
        t_prompt )

};

const txt_cmd_s v_StartingLinkText[] = {
    text_start("Starting link."
        t_done )

};

const txt_cmd_s v_LinkTerminatedText[] = {
    text_start("Link terminated."
        t_done )

};

const txt_cmd_s v_ClosingLinkText[] = {
    text_start("Closing link."
        t_done )

};

const txt_cmd_s v_ClearTimeLimitText[] = {
    text_start("Clear the time"
        t_line "limit?"
        t_done )

};

const txt_cmd_s v_TimeLimitWasClearedText[] = {
    text_start("The time limit was"
        t_line "cleared."
        t_done )

};

const txt_cmd_s v_PickErrorPacketText[] = {
    text_start("Pick which packet"
        t_line "as an error?"
        t_done )

};

const txt_cmd_s v_TradingMonForOTMonText[] = {
    text_start("Trading @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(
        t_line "for @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("…"
        t_done )



};

const txt_cmd_s v_ObtainedTheVoltorbBadgeText[] = {
    text_start("Obtained the"
        t_line "VOLTORBBADGE!"
        t_done )

};

const txt_cmd_s v_AskFloorElevatorText[] = {
    text_start("Which floor?"
        t_done )

};

const txt_cmd_s v_BugCatchingContestTimeUpText[] = {
    text_start("ANNOUNCER: BEEEP!"

        t_para "Time's up!"
        t_done )

};

const txt_cmd_s v_BugCatchingContestIsOverText[] = {
    text_start("ANNOUNCER: The"
        t_line "Contest is over!"
        t_done )

};

const txt_cmd_s v_RepelWoreOffText[] = {
    text_start("REPEL's effect"
        t_line "wore off."
        t_done )

};

const txt_cmd_s v_PlayerFoundItemText[] = {
    text_start("<PLAYER> found"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )

};

const txt_cmd_s v_ButNoSpaceText[] = {
    text_start("But <PLAYER> has"
        t_line "no space left…"
        t_done )

};

const txt_cmd_s v_JustSawSomeRareMonText[] = {
    text_start("I just saw some"
        t_line "rare @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" in"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."

        t_para "I'll call you if I"
        t_line "see another rare"
        t_cont "#MON, OK?"
        t_prompt )

};

const txt_cmd_s v_SavingRecordText[] = {
    text_start("SAVING RECORD…"
        t_line "DON'T TURN OFF!"
        t_done )

};

const txt_cmd_s v_ReceiveItemText[] = {
    text_ram(wram_ptr(wPlayerName))
    text_start(" received"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!@"
        )
    sound_item
    text_promptbutton
    text_end

    text_end

};

const txt_cmd_s v_NoCoinsText[] = {
    text_start("You have no coins."
        t_prompt )

};

const txt_cmd_s v_NoCoinCaseText[] = {
    text_start("You don't have a"
        t_line "COIN CASE."
        t_prompt )

};

const txt_cmd_s v_NPCTradeCableText[] = {
    text_start("OK, connect the"
        t_line "Game Link Cable."
        t_prompt )

};

const txt_cmd_s v_Text_NPCTraded[] = {
    text_start("<PLAYER> traded"
        t_line "@"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(" for"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(".@"
        )
    text_end

};

const txt_cmd_s v_NPCTradeFanfareText[] = {
    sound_dex_fanfare_80_109
    text_pause
    text_end

    text_end

};

const txt_cmd_s v_NPCTradeIntroText1[] = {
    text_start("I collect #MON."
        t_line "Do you have"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"

        t_para "Want to trade it"
        t_line "for my @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("?"
        t_done )

};

const txt_cmd_s v_NPCTradeCancelText1[] = {
    text_start("You don't want to"
        t_line "trade? Aww…"
        t_done )

};

const txt_cmd_s v_NPCTradeWrongText1[] = {
    text_start("Huh? That's not"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(". "
        t_cont "What a letdown…"
        t_done )

};

const txt_cmd_s v_NPCTradeCompleteText1[] = {
    text_start("Yay! I got myself"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_cont "Thanks!"
        t_done )

};

const txt_cmd_s v_NPCTradeAfterText1[] = {
    text_start("Hi, how's my old"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" doing?"
        t_done )

};

const txt_cmd_s v_NPCTradeIntroText2[] = {
    text_start("Hi, I'm looking"
        t_line "for this #MON."

        t_para "If you have"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(", would"

        t_para "you trade it for"
        t_line "my @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("?"
        t_done )

};

const txt_cmd_s v_NPCTradeCancelText2[] = {
    text_start("You don't have"
        t_line "one either?"

        t_para "Gee, that's really"
        t_line "disappointing…"
        t_done )

};

const txt_cmd_s v_NPCTradeWrongText2[] = {
    text_start("You don't have"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("? That's"
        t_cont "too bad, then."
        t_done )

};

const txt_cmd_s v_NPCTradeCompleteText2[] = {
    text_start("Great! Thank you!"

        t_para "I finally got"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_done )

};

const txt_cmd_s v_NPCTradeAfterText2[] = {
    text_start("Hi! The @"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(
        t_line "you traded me is"
        t_cont "doing great!"
        t_done )

};

const txt_cmd_s v_NPCTradeIntroText3[] = {
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start("'s cute,"
        t_line "but I don't have"

        t_para "it. Do you have"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"

        t_para "Want to trade it"
        t_line "for my @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("?"
        t_done )

};

const txt_cmd_s v_NPCTradeCancelText3[] = {
    text_start("You don't want to"
        t_line "trade? Oh, darn…"
        t_done )

};

const txt_cmd_s v_NPCTradeWrongText3[] = {
    text_start("That's not"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."

        t_para "Please trade with"
        t_line "me if you get one."
        t_done )

};

const txt_cmd_s v_NPCTradeCompleteText3[] = {
    text_start("Wow! Thank you!"
        t_line "I always wanted"
        t_cont "@"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start("!"
        t_done )

};

const txt_cmd_s v_NPCTradeAfterText3[] = {
    text_start("How is that"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" I"
        t_cont "traded you doing?"

        t_para "Your @"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start("'s"
        t_line "so cute!"
        t_done )

};

const txt_cmd_s v_NPCTradeCompleteText4[] = {
    text_start("Uh? What happened?"
        t_done )

};

const txt_cmd_s v_NPCTradeAfterText4[] = {
    text_start("Trading is so odd…"

        t_para "I still have a lot"
        t_line "to learn about it."
        t_done )

};

const txt_cmd_s v_MomLeavingText1[] = {
    text_start("Wow, that's a cute"
        t_line "#MON."

        t_para "Where did you get"
        t_line "it?"

        t_para "…"

        t_para "So, you're leaving"
        t_line "on an adventure…"

        t_para "OK!"
        t_line "I'll help too."

        t_para "But what can I do"
        t_line "for you?"

        t_para "I know! I'll save"
        t_line "money for you."

        t_para "On a long journey,"
        t_line "money's important."

        t_para "Do you want me to"
        t_line "save your money?"
        t_done )

};

const txt_cmd_s v_MomLeavingText2[] = {
    text_start("OK, I'll take care"
        t_line "of your money."

        t_para "<……><……><……>"
        t_prompt )

};

const txt_cmd_s v_MomLeavingText3[] = {
    text_start("Be careful."

        t_para "#MON are your"
        t_line "friends. You need"
        t_cont "to work as a team."

        t_para "Now, go on!"
        t_done )

};

const txt_cmd_s v_MomIsThisAboutYourMoneyText[] = {
    text_start("Hi! Welcome home!"
        t_line "You're trying very"
        t_cont "hard, I see."

        t_para "I've kept your"
        t_line "room tidy."

        t_para "Or is this about"
        t_line "your money?"
        t_done )

};

const txt_cmd_s v_MomBankWhatDoYouWantToDoText[] = {
    text_start("What do you want"
        t_line "to do?"
        t_done )

};

const txt_cmd_s v_MomStoreMoneyText[] = {
    text_start("How much do you"
        t_line "want to save?"
        t_done )

};

const txt_cmd_s v_MomTakeMoneyText[] = {
    text_start("How much do you"
        t_line "want to take?"
        t_done )

};

const txt_cmd_s v_MomSaveMoneyText[] = {
    text_start("Do you want to"
        t_line "save some money?"
        t_done )

};

const txt_cmd_s v_MomHaventSavedThatMuchText[] = {
    text_start("You haven't saved"
        t_line "that much."
        t_prompt )

};

const txt_cmd_s v_MomNotEnoughRoomInWalletText[] = {
    text_start("You can't take"
        t_line "that much."
        t_prompt )

};

const txt_cmd_s v_MomInsufficientFundsInWalletText[] = {
    text_start("You don't have"
        t_line "that much."
        t_prompt )

};

const txt_cmd_s v_MomNotEnoughRoomInBankText[] = {
    text_start("You can't save"
        t_line "that much."
        t_prompt )

};

const txt_cmd_s v_MomStartSavingMoneyText[] = {
    text_start("OK, I'll save your"
        t_line "money. Trust me!"

        t_para "<PLAYER>, stick"
        t_line "with it!"
        t_done )

};

const txt_cmd_s v_MomStoredMoneyText[] = {
    text_start("Your money's safe"
        t_line "here! Get going!"
        t_done )

};

const txt_cmd_s v_MomTakenMoneyText[] = {
    text_start("<PLAYER>, don't"
        t_line "give up!"
        t_done )

};

const txt_cmd_s v_MomJustDoWhatYouCanText[] = {
    text_start("Just do what"
        t_line "you can."
        t_done )

};

const txt_cmd_s v_DaycareDummyText[] = {
    text_start(
        t_done )

};

const txt_cmd_s v_DayCareManIntroText[] = {
    text_start("I'm the DAY-CARE"
        t_line "MAN. Want me to"
        t_cont "raise a #MON?"
        t_done )

};

const txt_cmd_s v_DayCareManIntroEggText[] = {
    text_start("I'm the DAY-CARE"
        t_line "MAN. Do you know"
        t_cont "about EGGS?"

        t_para "I was raising"
        t_line "#MON with my"
        t_cont "wife, you see."

        t_para "We were shocked to"
        t_line "find an EGG!"

        t_para "How incredible is"
        t_line "that?"

        t_para "So, want me to"
        t_line "raise a #MON?"
        t_done )

};

const txt_cmd_s v_DayCareLadyIntroText[] = {
    text_start("I'm the DAY-CARE"
        t_line "LADY."

        t_para "Should I raise a"
        t_line "#MON for you?"
        t_done )

};

const txt_cmd_s v_DayCareLadyIntroEggText[] = {
    text_start("I'm the DAY-CARE"
        t_line "LADY. Do you know"
        t_cont "about EGGS?"

        t_para "My husband and I"
        t_line "were raising some"
        t_cont "#MON, you see."

        t_para "We were shocked to"
        t_line "find an EGG!"

        t_para "How incredible"
        t_line "could that be?"

        t_para "Should I raise a"
        t_line "#MON for you?"
        t_done )

};

const txt_cmd_s v_WhatShouldIRaiseText[] = {
    text_start("What should I"
        t_line "raise for you?"
        t_prompt )

};

const txt_cmd_s v_OnlyOneMonText[] = {
    text_start("Oh? But you have"
        t_line "just one #MON."
        t_prompt )

};

const txt_cmd_s v_CantAcceptEggText[] = {
    text_start("Sorry, but I can't"
        t_line "accept an EGG."
        t_prompt )

};

const txt_cmd_s v_RemoveMailText[] = {
    text_start("Remove MAIL before"
        t_line "you come see me."
        t_prompt )

};

const txt_cmd_s v_LastHealthyMonText[] = {
    text_start("If you give me"
        t_line "that, what will"
        t_cont "you battle with?"
        t_prompt )

};

const txt_cmd_s v_IllRaiseYourMonText[] = {
    text_start("OK. I'll raise"
        t_line "your @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_ComeBackLaterText[] = {
    text_start("Come back for it"
        t_line "later."
        t_done )

};

const txt_cmd_s v_AreWeGeniusesText[] = {
    text_start("Are we geniuses or"
        t_line "what? Want to see"
        t_cont "your @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"
        t_done )

};

const txt_cmd_s v_YourMonHasGrownText[] = {
    text_start("Your @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_line "has grown a lot."

        t_para "By level, it's"
        t_line "grown by @"
        )
    text_decimal(wram_ptr(wStringBuffer2 + 1), 1, 3)
    text_start("."

        t_para "If you want your"
        t_line "#MON back, it"
        t_cont "will cost ¥@"
        )
    text_decimal(wram_ptr(wStringBuffer2 + 2), 3, 4)
    text_start("."
        t_done )

};

const txt_cmd_s v_PerfectHeresYourMonText[] = {
    text_start("Perfect! Here's"
        t_line "your #MON."
        t_prompt )

};

const txt_cmd_s v_GotBackMonText[] = {
    text_start("<PLAYER> got back"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_BackAlreadyText[] = {
    text_start("Huh? Back already?"
        t_line "Your @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(
        t_para "needs a little"
        t_line "more time with us."

        t_para "If you want your"
        t_line "#MON back, it"
        t_cont "will cost ¥100."
        t_done )

};

const txt_cmd_s v_HaveNoRoomText[] = {
    text_start("You have no room"
        t_line "for it."
        t_prompt )

};

const txt_cmd_s v_NotEnoughMoneyText[] = {
    text_start("You don't have"
        t_line "enough money."
        t_prompt )

};

const txt_cmd_s v_OhFineThenText[] = {
    text_start("Oh, fine then."
        t_prompt )

};

const txt_cmd_s v_ComeAgainText[] = {
    text_start("Come again."
        t_done )

};

const txt_cmd_s v_NotYetText[] = {
    text_start("Not yet…"
        t_done )

};

const txt_cmd_s v_FoundAnEggText[] = {
    text_start("Ah, it's you!"

        t_para "We were raising"
        t_line "your #MON, and"

        t_para "my goodness, were"
        t_line "we surprised!"

        t_para "Your #MON had"
        t_line "an EGG!"

        t_para "We don't know how"
        t_line "it got there, but"

        t_para "your #MON had"
        t_line "it. You want it?"
        t_done )

};

const txt_cmd_s v_ReceivedEggText[] = {
    text_start("<PLAYER> received"
        t_line "the EGG!"
        t_done )

};

const txt_cmd_s v_TakeGoodCareOfEggText[] = {
    text_start("Take good care of"
        t_line "it."
        t_done )

};

const txt_cmd_s v_IllKeepItThanksText[] = {
    text_start("Well then, I'll"
        t_line "keep it. Thanks!"
        t_done )

};

const txt_cmd_s v_NoRoomForEggText[] = {
    text_start("You have no room"
        t_line "in your party."
        t_cont "Come back later."
        t_done )

};

const txt_cmd_s v_WhichMonPhotoText[] = {
    text_start("Which #MON"
        t_line "should I photo-"
        t_cont "graph?"
        t_prompt )

};

const txt_cmd_s v_HoldStillText[] = {
    text_start("All righty. Hold"
        t_line "still for a bit."
        t_prompt )

};

const txt_cmd_s v_PrestoAllDoneText[] = {
    text_start("Presto! All done."
        t_line "Come again, OK?"
        t_done )
};
