#include "../../constants.h"
extern uint8_t gMobileParticipant1Nickname[MON_NAME_LENGTH];
extern uint8_t gMobileParticipant2Nickname[MON_NAME_LENGTH];
extern uint8_t gMobileParticipant3Nickname[MON_NAME_LENGTH];

const txt_cmd_s v_OakText6[] = {
    text_start("Now, what did you"
        t_line "say your name was?"
        t_prompt )

};

const txt_cmd_s v_OakText7[] = {
    text_start("<PLAYER>, are you"
        t_line "ready?"

        t_para "Your very own"
        t_line "#MON story is"
        t_cont "about to unfold."

        t_para "You'll face fun"
        t_line "times and tough"
        t_cont "challenges."

        t_para "A world of dreams"
        t_line "and adventures"

        t_para "with #MON"
        t_line "awaits! Let's go!"

        t_para "I'll be seeing you"
        t_line "later!"
        t_done )

};

const txt_cmd_s v_ClockTimeMayBeWrongText[] = {
    text_start("The clock's time"
        t_line "may be wrong."

        t_para "Please reset the"
        t_line "time."
        t_prompt )

};

const txt_cmd_s v_ClockSetWithControlPadText[] = {
    text_start("Set with the"
        t_line "Control Pad."

        t_para "Confirm: A Button"
        t_line "Cancel:  B Button"
        t_done )

};

const txt_cmd_s v_ClockIsThisOKText[] = {
    text_start("Is this OK?"
        t_done )

};

const txt_cmd_s v_ClockHasResetText[] = {
    text_start("The clock has been"
        t_line "reset."
        t_done )

};

const txt_cmd_s v_LinkTimeoutText[] = {
    text_start("Too much time has"
        t_line "elapsed. Please"
        t_cont "try again."
        t_prompt )

};

const txt_cmd_s v_LinkTradeCantBattleText[] = {
    text_start("If you trade that"
        t_line "#MON, you won't"
        t_cont "be able to battle."
        t_prompt )

};

const txt_cmd_s v_LinkAbnormalMonText[] = {
    text_start("Your friend's"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" appears"
        t_cont "to be abnormal!"
        t_prompt )

};

const txt_cmd_s v_LinkAskTradeForText[] = {
    text_start("Trade @"
        )
    text_ram(wram_ptr(wBufferTrademonNickname))
    text_start(
        t_line "for @"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"
        t_done )

};

const txt_cmd_s v_MobileBattleMustPickThreeMonText[] = {
    text_start("To enter a mobile"
        t_line "battle, you must"

        t_para "pick a team of"
        t_line "three #MON."

        t_para "Is that OK?"
        t_done )

};

const txt_cmd_s v_MobileBattleMoreInfoText[] = {
    text_start("Need more info on"
        t_line "mobile battles?"
        t_done )

};

const txt_cmd_s v_MobileBattleRulesText[] = {
    text_start("For a mobile"
        t_line "battle, choose"
        t_cont "three #MON."

        t_para "The maximum daily"
        t_line "play time is ten"

        t_para "minutes for each"
        t_line "linked player."

        t_para "If a battle isn't"
        t_line "finished within"

        t_para "the time limit,"
        t_line "the player with"

        t_para "the fewest fainted"
        t_line "#MON wins."

        t_para "If tied, the team"
        t_line "that lost the"

        t_para "least amount of HP"
        t_line "wins."
        t_done )

};

const txt_cmd_s v_WouldYouLikeToMobileBattleText[] = {
    text_start("Today's remaining"
        t_line "time is @"
        )
    text_decimal(wram_ptr(wStringBuffer2), 1, 2)
    text_start(" min."

        t_para "Would you like to"
        t_line "battle?"
        t_done )

};

const txt_cmd_s v_WantAQuickMobileBattleText[] = {
    text_start("There are only @"
        )
    text_decimal(wram_ptr(wStringBuffer2), 1, 2)
    text_start(
        t_line "min. left today."

        t_para "Want a quick"
        t_line "battle?"
        t_done )

};

const txt_cmd_s v_WantToRushThroughAMobileBattleText[] = {
    text_start("There is only"
        t_line "1 min. left today!"

        t_para "Want to rush"
        t_line "through a battle?"
        t_done )

};

const txt_cmd_s v_PleaseTryAgainTomorrowText[] = {
    text_start("There is less than"
        t_line "1 min. left today!"

        t_para "Please try again"
        t_line "tomorrow."
        t_done )

};

const txt_cmd_s v_TryAgainUsingSameSettingsText[] = {
    text_start("Try again using"
        t_line "the same settings?"
        t_done )

};

const txt_cmd_s v_MobileBattleLessThanOneMinuteLeftText[] = {
    text_start("There is less than"
        t_line "1 min. left today!"
        t_done )

};

const txt_cmd_s v_MobileBattleNoTimeLeftForLinkingText[] = {
    text_start("No time left for"
        t_line "linking today."
        t_done )

};

const txt_cmd_s v_PickThreeMonForMobileBattleText[] = {
    text_start("Pick three #MON"
        t_line "for battle."
        t_done )

};

const txt_cmd_s v_MobileBattleRemainingTimeText[] = {
    text_start("Today's remaining"
        t_line "time is @"
        )
    text_decimal(wram_ptr(wStringBuffer2), 1, 2)
    text_start(" min."
        t_done )

};

const txt_cmd_s v_WouldYouLikeToSaveTheGameText[] = {
    text_start("Would you like to"
        t_line "save the game?"
        t_done )

};

const txt_cmd_s v_SavingDontTurnOffThePowerText[] = {
    text_start("SAVING… DON'T TURN"
        t_line "OFF THE POWER."
        t_done )

};

const txt_cmd_s v_SavedTheGameText[] = {
    text_start("<PLAYER> saved"
        t_line "the game."
        t_done )

};

const txt_cmd_s v_AlreadyASaveFileText[] = {
    text_start("There is already a"
        t_line "save file. Is it"
        t_cont "OK to overwrite?"
        t_done )

};

const txt_cmd_s v_AnotherSaveFileText[] = {
    text_start("There is another"
        t_line "save file. Is it"
        t_cont "OK to overwrite?"
        t_done )

};

const txt_cmd_s v_SaveFileCorruptedText[] = {
    text_start("The save file is"
        t_line "corrupted!"
        t_prompt )

};

const txt_cmd_s v_ChangeBoxSaveText[] = {
    text_start("When you change a"
        t_line "#MON BOX, data"
        t_cont "will be saved. OK?"
        t_done )

};

const txt_cmd_s v_MoveMonWOMailSaveText[] = {
    text_start("Each time you move"
        t_line "a #MON, data"
        t_cont "will be saved. OK?"
        t_done )

};

const txt_cmd_s v_WindowAreaExceededErrorText[] = {
    text_start("The window save"
        t_line "area was exceeded."
        t_done )

};

const txt_cmd_s v_WindowPoppingErrorText[] = {
    text_start("No windows avail-"
        t_line "able for popping."
        t_done )

};

const txt_cmd_s v_CorruptedEventText[] = {
    text_start("Corrupted event!"
        t_prompt )

};

const txt_cmd_s v_ObjectEventText[] = {
    text_start("Object event"
        t_done )

};

const txt_cmd_s v_BGEventText[] = {
    text_start("BG event"
        t_done )

};

const txt_cmd_s v_CoordinatesEventText[] = {
    text_start("Coordinates event"
        t_done )

};

const txt_cmd_s v_ReceivedItemText[] = {
    text_start("<PLAYER> received"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_done )

};

const txt_cmd_s v_PutItemInPocketText[] = {
    text_start("<PLAYER> put the"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" in"
        t_cont "the @"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_PocketIsFullText[] = {
    text_start("The @"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "is full…"
        t_prompt )

};

const txt_cmd_s v_SeerSeeAllText[] = {
    text_start("I see all."
        t_line "I know all…"

        t_para "Certainly, I know"
        t_line "of your #MON!"
        t_done )

};

const txt_cmd_s v_SeerCantTellAThingText[] = {
    text_start("Whaaaat? I can't"
        t_line "tell a thing!"

        t_para "How could I not"
        t_line "know of this?"
        t_done )

};

const txt_cmd_s v_SeerNameLocationText[] = {
    text_start("Hm… I see you met"
        t_line "@"
        )
    text_ram(wram_ptr(wSeerNickname))
    text_start(" here:"
        t_cont "@"
        )
    text_ram(wram_ptr(wSeerCaughtLocation))
    text_start("!"
        t_prompt )

};

const txt_cmd_s v_SeerTimeLevelText[] = {
    text_start("The time was"
        t_line "@"
        )
    text_ram(wram_ptr(wSeerTimeOfDay))
    text_start("!"

        t_para "Its level was @"
        )
    text_ram(wram_ptr(wSeerCaughtLevelString))
    text_start("!"

        t_para "Am I good or what?"
        t_prompt )

};

const txt_cmd_s v_SeerTradeText[] = {
    text_start("Hm… @"
        )
    text_ram(wram_ptr(wSeerNickname))
    text_start(
        t_line "came from @"
        )
    text_ram(wram_ptr(wSeerOT))
    text_start(
        t_cont "in a trade?"

        t_para "@"
        )
    text_ram(wram_ptr(wSeerCaughtLocation))
    text_start(
        t_line "was where @"
        )
    text_ram(wram_ptr(wSeerOT))
    text_start(
        t_cont "met @"
        )
    text_ram(wram_ptr(wSeerNickname))
    text_start("!"
        t_prompt )

};

const txt_cmd_s v_SeerNoLocationText[] = {
    text_start("What!? Incredible!"

        t_para "I don't understand"
        t_line "how, but it is"

        t_para "incredible!"
        t_line "You are special."

        t_para "I can't tell where"
        t_line "you met it, but it"
        t_cont "was at level @"
        )
    text_ram(wram_ptr(wSeerCaughtLevelString))
    text_start("."

        t_para "Am I good or what?"
        t_prompt )

};

const txt_cmd_s v_SeerEggText[] = {
    text_start("Hey!"

        t_para "That's an EGG!"

        t_para "You can't say that"
        t_line "you've met it yet…"
        t_done )

};

const txt_cmd_s v_SeerDoNothingText[] = {
    text_start("Fufufu! I saw that"
        t_line "you'd do nothing!"
        t_done )

};

const txt_cmd_s v_SeerMoreCareText[] = {
    text_start("Incidentally…"

        t_para "It would be wise"
        t_line "to raise your"

        t_para "#MON with a"
        t_line "little more care."
        t_done )

};

const txt_cmd_s v_SeerMoreConfidentText[] = {
    text_start("Incidentally…"

        t_para "It seems to have"
        t_line "grown a little."

        t_para "@"
        )
    text_ram(wram_ptr(wSeerNickname))
    text_start(" seems"
        t_line "to be becoming"
        t_cont "more confident."
        t_done )

};

const txt_cmd_s v_SeerMuchStrengthText[] = {
    text_start("Incidentally…"

        t_para "@"
        )
    text_ram(wram_ptr(wSeerNickname))
    text_start(" has"
        t_line "grown. It's gained"
        t_cont "much strength."
        t_done )

};

const txt_cmd_s v_SeerMightyText[] = {
    text_start("Incidentally…"

        t_para "It certainly has"
        t_line "grown mighty!"

        t_para "This @"
        )
    text_ram(wram_ptr(wSeerNickname))
    text_start(
        t_line "must have come"

        t_para "through numerous"
        t_line "#MON battles."

        t_para "It looks brimming"
        t_line "with confidence."
        t_done )

};

const txt_cmd_s v_SeerImpressedText[] = {
    text_start("Incidentally…"

        t_para "I'm impressed by"
        t_line "your dedication."

        t_para "It's been a long"
        t_line "time since I've"

        t_para "seen a #MON as"
        t_line "mighty as this"
        t_cont "@"
        )
    text_ram(wram_ptr(wSeerNickname))
    text_start("."

        t_para "I'm sure that"
        t_line "seeing @"
        )
    text_ram(wram_ptr(wSeerNickname))
    text_start(

        t_para "in battle would"
        t_line "excite anyone."
        t_done )

};

const txt_cmd_s v_CongratulationsYourPokemonText[] = {
    text_start("Congratulations!"
        t_line "Your @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_end

    text_end

};

const txt_cmd_s v_EvolvedIntoText[] = {
    text_start(

        t_para "evolved into"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("!"
        t_done )

};

const txt_cmd_s v_StoppedEvolvingText[] = {
    text_start("Huh? @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(
        t_line "stopped evolving!"
        t_prompt )

};

const txt_cmd_s v_EvolvingText[] = {
    text_start("What? @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(
        t_line "is evolving!"
        t_done )

};

const txt_cmd_s v_MartHowManyText[] = {
    text_start("How many?"
        t_done )

};

const txt_cmd_s v_MartFinalPriceText[] = {
    text_decimal(wram_ptr(wItemQuantityChange), 1, 2)
    text_start(" @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)"
        t_line "will be ¥@"
        )
    text_decimal(&hMoneyTemp, 3, 6)
    text_start("."
        t_done )

};

const txt_cmd_s v_HerbShopLadyIntroText[] = {
    text_start("Hello, dear."

        t_para "I sell inexpensive"
        t_line "herbal medicine."

        t_para "They're good, but"
        t_line "a trifle bitter."

        t_para "Your #MON may"
        t_line "not like them."

        t_para "Hehehehe…"
        t_done )

};

const txt_cmd_s v_HerbalLadyHowManyText[] = {
    text_start("How many?"
        t_done )

};

const txt_cmd_s v_HerbalLadyFinalPriceText[] = {
    text_decimal(wram_ptr(wItemQuantityChange), 1, 2)
    text_start(" @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)"
        t_line "will be ¥@"
        )
    text_decimal(&hMoneyTemp, 3, 6)
    text_start("."
        t_done )

};

const txt_cmd_s v_HerbalLadyThanksText[] = {
    text_start("Thank you, dear."
        t_line "Hehehehe…"
        t_done )

};

const txt_cmd_s v_HerbalLadyPackFullText[] = {
    text_start("Oh? Your PACK is"
        t_line "full, dear."
        t_done )

};

const txt_cmd_s v_HerbalLadyNoMoneyText[] = {
    text_start("Hehehe… You don't"
        t_line "have the money."
        t_done )

};

const txt_cmd_s v_HerbalLadyComeAgainText[] = {
    text_start("Come again, dear."
        t_line "Hehehehe…"
        t_done )

};

const txt_cmd_s v_BargainShopIntroText[] = {
    text_start("Hiya! Care to see"
        t_line "some bargains?"

        t_para "I sell rare items"
        t_line "that nobody else"

        t_para "carries--but only"
        t_line "one of each item."
        t_done )

};

const txt_cmd_s v_BargainShopFinalPriceText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" costs"
        t_line "¥@"
        )
    text_decimal(&hMoneyTemp, 3, 6)
    text_start(". Want it?"
        t_done )

};

const txt_cmd_s v_BargainShopThanksText[] = {
    text_start("Thanks."
        t_done )

};

const txt_cmd_s v_BargainShopPackFullText[] = {
    text_start("Uh-oh, your PACK"
        t_line "is chock-full."
        t_done )

};

const txt_cmd_s v_BargainShopSoldOutText[] = {
    text_start("You bought that"
        t_line "already. I'm all"
        t_cont "sold out of it."
        t_done )

};

const txt_cmd_s v_BargainShopNoFundsText[] = {
    text_start("Uh-oh, you're"
        t_line "short on funds."
        t_done )

};

const txt_cmd_s v_BargainShopComeAgainText[] = {
    text_start("Come by again"
        t_line "sometime."
        t_done )

};

const txt_cmd_s v_PharmacyIntroText[] = {
    text_start("What's up? Need"
        t_line "some medicine?"
        t_done )

};

const txt_cmd_s v_PharmacyHowManyText[] = {
    text_start("How many?"
        t_done )

};

const txt_cmd_s v_PharmacyFinalPriceText[] = {
    text_decimal(wram_ptr(wItemQuantityChange), 1, 2)
    text_start(" @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)"
        t_line "will cost ¥@"
        )
    text_decimal(&hMoneyTemp, 3, 6)
    text_start("."
        t_done )

};

const txt_cmd_s v_PharmacyThanksText[] = {
    text_start("Thanks much!"
        t_done )

};

const txt_cmd_s v_PharmacyPackFullText[] = {
    text_start("You don't have any"
        t_line "more space."
        t_done )

};

const txt_cmd_s v_PharmacyNoMoneyText[] = {
    text_start("Huh? That's not"
        t_line "enough money."
        t_done )

};

const txt_cmd_s v_PharmacyComeAgainText[] = {
    text_start("All right."
        t_line "See you around."
        t_done )

};

const txt_cmd_s v_NothingToSellText[] = {
    text_start("You don't have"
        t_line "anything to sell."
        t_prompt )

};

const txt_cmd_s v_MartSellHowManyText[] = {
    text_start("How many?"
        t_done )

};

const txt_cmd_s v_MartSellPriceText[] = {
    text_start("I can pay you"
        t_line "¥@"
        )
    text_decimal(&hMoneyTemp, 3, 6)
    text_start("."

        t_para "Is that OK?"
        t_done )

};

const txt_cmd_s v_MartWelcomeText[] = {
    text_start("Welcome! How may I"
        t_line "help you?"
        t_done )

};

const txt_cmd_s v_MartThanksText[] = {
    text_start("Here you are."
        t_line "Thank you!"
        t_done )

};

const txt_cmd_s v_MartNoMoneyText[] = {
    text_start("You don't have"
        t_line "enough money."
        t_done )

};

const txt_cmd_s v_MartPackFullText[] = {
    text_start("You can't carry"
        t_line "any more items."
        t_done )

};

const txt_cmd_s v_MartCantBuyText[] = {
    text_start("Sorry, I can't buy"
        t_line "that from you."
        t_prompt )

};

const txt_cmd_s v_MartComeAgainText[] = {
    text_start("Please come again!"
        t_done )

};

const txt_cmd_s v_MartAskMoreText[] = {
    text_start("Can I do anything"
        t_line "else for you?"
        t_done )

};

const txt_cmd_s v_MartBoughtText[] = {
    text_start("Got ¥@"
        )
    text_decimal(&hMoneyTemp, 3, 6)
    text_start(" for"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("(S)."
        t_done )

};

const txt_cmd_s v_SlotsBetHowManyCoinsText[] = {
    text_start("Bet how many"
        t_line "coins?"
        t_done )

};

const txt_cmd_s v_SlotsStartText[] = {
    text_start("Start!"
        t_done )

};

const txt_cmd_s v_SlotsNotEnoughCoinsText[] = {
    text_start("Not enough"
        t_line "coins."
        t_prompt )

};

const txt_cmd_s v_SlotsRanOutOfCoinsText[] = {
    text_start("Darn… Ran out of"
        t_line "coins…"
        t_done )

};

const txt_cmd_s v_SlotsPlayAgainText[] = {
    text_start("Play again?"
        t_done )

};

const txt_cmd_s v_SlotsLinedUpText[] = {
    text_start("lined up!"
        t_line "Won @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" coins!"
        t_done )

};

const txt_cmd_s v_SlotsDarnText[] = {
    text_start("Darn!"
        t_done )

};

const txt_cmd_s v_MobileStadiumEntryText[] = {
    text_start("Data for use in"
        t_line "the MOBILE STADIUM"

        t_para "of the N64 #MON"
        t_line "STADIUM 2 can be"
        t_cont "read here."

        t_para "Read the data?"
        t_done )

};

const txt_cmd_s v_MobileStadiumSuccessText[] = {
    text_start("Data transfer is"
        t_line "complete."

        t_para "We hope you enjoy"
        t_line "MOBILE STADIUM"

        t_para "battles in the N64"
        t_line "#MON STADIUM 2."

        t_para ""
        t_done )

};

const txt_cmd_s v_MainMenuTimeUnknownText[] = {
    text_start("Clock time unknown"
        t_done )

};

const txt_cmd_s v_DeleteSavedLoginPasswordText[] = {
    text_start("Delete the saved"
        t_line "LOG-IN PASSWORD?"
        t_done )

};

const txt_cmd_s v_DeletedTheLoginPasswordText[] = {
    text_start("Deleted the LOG-IN"
        t_line "PASSWORD."
        t_done )

};

const txt_cmd_s v_MobilePickThreeMonForBattleText[] = {
    text_start("Pick three #MON"
        t_line "for battle."
        t_prompt )

};

const txt_cmd_s v_MobileUseTheseThreeMonText[] = {
    text_ram(gMobileParticipant1Nickname)
    text_start(","
        t_line "@"
        )
    text_ram(gMobileParticipant2Nickname)
    text_start(" and"
        t_cont "@"
        )
    text_ram(gMobileParticipant3Nickname)
    text_start("."

        t_para "Use these three?"
        t_done )

};

const txt_cmd_s v_MobileOnlyThreeMonMayEnterText[] = {
    text_start("Only three #MON"
        t_line "may enter."
        t_prompt )

};

const txt_cmd_s v_MobileCardFolderIntro1Text[] = {
    text_start("The CARD FOLDER"
        t_line "stores your and"

        t_para "your friends'"
        t_line "CARDS."

        t_para "A CARD contains"
        t_line "information like"

        t_para "the person's name,"
        t_line "phone number and"
        t_cont "profile."

        t_para ""
        t_done )

};

const txt_cmd_s v_MobileCardFolderIntro2Text[] = {
    text_start("This is your CARD."

        t_para "Once you've"
        t_line "entered your phone"

        t_para "number, you can"
        t_line "trade CARDS with"
        t_cont "your friends."

        t_para ""
        t_done )

};

const txt_cmd_s v_MobileCardFolderIntro3Text[] = {
    text_start("If you have your"
        t_line "friend's CARD, you"

        t_para "can use it to make"
        t_line "a call from a"

        t_para "mobile phone on"
        t_line "the 2nd floor of a"
        t_cont "#MON CENTER."

        t_para ""
        t_done )

};

const txt_cmd_s v_MobileCardFolderIntro4Text[] = {
    text_start("To safely store"
        t_line "your collection of"

        t_para "CARDS, you must"
        t_line "set a PASSCODE for"
        t_cont "your CARD FOLDER."

        t_para ""
        t_done )

};

const txt_cmd_s v_MobileCardFolderAskDeleteText[] = {
    text_start("If the CARD FOLDER"
        t_line "is deleted, all"

        t_para "its CARDS and the"
        t_line "PASSCODE will also"
        t_cont "be deleted."

        t_para "Beware--a deleted"
        t_line "CARD FOLDER can't"
        t_cont "be restored."

        t_para "Want to delete"
        t_line "your CARD FOLDER?"
        t_done )

};

const txt_cmd_s v_MobileCardFolderDeleteAreYouSureText[] = {
    text_start("Are you sure you"
        t_line "want to delete it?"
        t_done )

};

const txt_cmd_s v_MobileCardFolderDeletedText[] = {
    text_start("The CARD FOLDER"
        t_line "has been deleted."

        t_para ""
        t_done )

};

const txt_cmd_s v_MobileCardFolderAskOpenOldText[] = {
    text_start("There is an older"
        t_line "CARD FOLDER from a"
        t_cont "previous journey."

        t_para "Do you want to"
        t_line "open it?"
        t_done )

};

const txt_cmd_s v_MobileCardFolderAskDeleteOldText[] = {
    text_start("Delete the old"
        t_line "CARD FOLDER?"
        t_done )

};

const txt_cmd_s v_MobileCardFolderFinishRegisteringCardsText[] = {
    text_start("Finish registering"
        t_line "CARDS?"
        t_done )

};

const txt_cmd_s v_PhoneWrongNumberText[] = {
    text_start("Huh? Sorry, wrong"
        t_line "number!"
        t_done )

};

const txt_cmd_s v_PhoneClickText[] = {
    text_start("Click!"
        t_done )

};

const txt_cmd_s v_PhoneEllipseText[] = {
    text_start("<……>"
        t_done )

};

const txt_cmd_s v_PhoneOutOfAreaText[] = {
    text_start("That number is out"
        t_line "of the area."
        t_done )

};

const txt_cmd_s v_PhoneJustTalkToThemText[] = {
    text_start("Just go talk to"
        t_line "that person!"
        t_done )

};

const txt_cmd_s v_PhoneThankYouText[] = {
    text_start("Thank you!"
        t_done )

};

const txt_cmd_s v_SpaceSpaceColonText[] = {
    text_start("  :"
        t_done )

};

const txt_cmd_s v_PasswordAskResetText[] = {
    text_start("Password OK."
        t_line "Select CONTINUE &"
        t_cont "reset settings."
        t_prompt )

};

const txt_cmd_s v_PasswordWrongText[] = {
    text_start("Wrong password!"
        t_prompt )

};

const txt_cmd_s v_PasswordAskResetClockText[] = {
    text_start("Reset the clock?"
        t_done )

};

const txt_cmd_s v_PasswordAskEnterText[] = {
    text_start("Please enter the"
        t_line "password."
        t_done )

};

const txt_cmd_s v_ClearAllSaveDataText[] = {
    text_start("Clear all save"
        t_line "data?"
        t_done )

};

const txt_cmd_s v_LearnedMoveText[] = {
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(" learned"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("!@"
        )
    sound_dex_fanfare_50_79
    text_promptbutton
    text_end

    text_end

};

const txt_cmd_s v_MoveAskForgetText[] = {
    text_start("Which move should"
        t_next "be forgotten?"
        t_done )

};

const txt_cmd_s v_StopLearningMoveText[] = {
    text_start("Stop learning"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("?"
        t_done )

};

const txt_cmd_s v_DidNotLearnMoveText[] = {
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(
        t_line "did not learn"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_AskForgetMoveText[] = {
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(" is"
        t_line "trying to learn"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."

        t_para "But @"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(
        t_line "can't learn more"
        t_cont "than four moves."

        t_para "Delete an older"
        t_line "move to make room"
        t_cont "for @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("?"
        t_done )

};

const txt_cmd_s v_Text_MoveForgetCount[] = {
    text_start("1, 2 and…@"
        )
    text_pause
    text_end

    text_end

};

const txt_cmd_s v_MoveForgotText[] = {
    text_start(" Poof!@"
        )
    text_pause
    text_start(

        t_para "@"
        )
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(" forgot"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("."

        t_para "And…"
        t_prompt )

};

const txt_cmd_s v_MoveCantForgetHMText[] = {
    text_start("HM moves can't be"
        t_line "forgotten now."
        t_prompt )

};

const txt_cmd_s v_CardFlipPlayWithThreeCoinsText[] = {
    text_start("Play with three"
        t_line "coins?"
        t_done )

};

const txt_cmd_s v_CardFlipNotEnoughCoinsText[] = {
    text_start("Not enough coins…"
        t_prompt )

};

const txt_cmd_s v_CardFlipChooseACardText[] = {
    text_start("Choose a card."
        t_done )

};

const txt_cmd_s v_CardFlipPlaceYourBetText[] = {
    text_start("Place your bet."
        t_done )

};

const txt_cmd_s v_CardFlipPlayAgainText[] = {
    text_start("Want to play"
        t_line "again?"
        t_done )

};

const txt_cmd_s v_CardFlipShuffledText[] = {
    text_start("The cards have"
        t_line "been shuffled."
        t_prompt )

};

const txt_cmd_s v_CardFlipYeahText[] = {
    text_start("Yeah!"
        t_done )

};

const txt_cmd_s v_CardFlipDarnText[] = {
    text_start("Darn…"
        t_done )

};

const txt_cmd_s v_GearTodayText[] = {
    text_today
    text_end

    text_end

};

const txt_cmd_s v_GearEllipseText[] = {
    text_start("<……>"
        t_done )

};

const txt_cmd_s v_GearOutOfServiceText[] = {
    text_start("You're out of the"
        t_line "service area."
        t_prompt )

};

const txt_cmd_s v_PokegearAskWhoCallText[] = {
    text_start("Whom do you want"
        t_line "to call?"
        t_done )

};

const txt_cmd_s v_PokegearPressButtonText[] = {
    text_start("Press any button"
        t_line "to exit."
        t_done )

};

const txt_cmd_s v_PokegearAskDeleteText[] = {
    text_start("Delete this stored"
        t_line "phone number?"
        t_done )

};

const txt_cmd_s v_BuenaAskWhichPrizeText[] = {
    text_start("Which prize would"
        t_line "you like?"
        t_done )

};

const txt_cmd_s v_BuenaIsThatRightText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"
        t_line "Is that right?"
        t_done )

};

const txt_cmd_s v_BuenaHereYouGoText[] = {
    text_start("Here you go!"

        t_para ""
        t_done )

};

const txt_cmd_s v_BuenaNotEnoughPointsText[] = {
    text_start("You don't have"
        t_line "enough points."

        t_para ""
        t_done )

};

const txt_cmd_s v_BuenaNoRoomText[] = {
    text_start("You have no room"
        t_line "for it."

        t_para ""
        t_done )

};

const txt_cmd_s v_BuenaComeAgainText[] = {
    text_start("Oh. Please come"
        t_line "back again!"
        t_done )

};

const txt_cmd_s v_BTExcuseMeText[] = {
    text_start("Excuse me!"

        t_para ""
        t_done )

};

const txt_cmd_s v_ExcuseMeYoureNotReadyText[] = {
    text_start("Excuse me."
        t_line "You're not ready."

        t_para ""
        t_done )

};

const txt_cmd_s v_BattleTowerReturnWhenReadyText[] = {
    text_start("Please return when"
        t_line "you're ready."
        t_done )

};

const txt_cmd_s v_NeedAtLeastThreeMonText[] = {
    text_start("You need at least"
        t_line "three #MON."

        t_para ""
        t_done )

};

const txt_cmd_s v_EggDoesNotQualifyText[] = {
    text_start("Sorry, an EGG"
        t_line "doesn't qualify."

        t_para ""
        t_done )

};

const txt_cmd_s v_OnlyThreeMonMayBeEnteredText[] = {
    text_start("Only three #MON"
        t_line "may be entered."

        t_para ""
        t_done )

};

const txt_cmd_s v_TheMonMustAllBeDifferentKindsText[] = {
    text_start("The @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" #MON"
        t_line "must all be"
        t_cont "different kinds."

        t_para ""
        t_done )

};

const txt_cmd_s v_TheMonMustNotHoldTheSameItemsText[] = {
    text_start("The @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" #MON"
        t_line "must not hold the"
        t_cont "same items."

        t_para ""
        t_done )

};

const txt_cmd_s v_YouCantTakeAnEggText[] = {
    text_start("You can't take an"
        t_line "EGG!"

        t_para ""
        t_done )

};

const txt_cmd_s v_BallDodgedText[] = {
    text_start("It dodged the"
        t_line "thrown BALL!"

        t_para "This #MON"
        t_line "can't be caught!"
        t_prompt )

};

const txt_cmd_s v_BallMissedText[] = {
    text_start("You missed the"
        t_line "#MON!"
        t_prompt )

};

const txt_cmd_s v_BallBrokeFreeText[] = {
    text_start("Oh no! The #MON"
        t_line "broke free!"
        t_prompt )

};

const txt_cmd_s v_BallAppearedCaughtText[] = {
    text_start("Aww! It appeared"
        t_line "to be caught!"
        t_prompt )

};

const txt_cmd_s v_BallAlmostHadItText[] = {
    text_start("Aargh!"
        t_line "Almost had it!"
        t_prompt )

};

const txt_cmd_s v_BallSoCloseText[] = {
    text_start("Shoot! It was so"
        t_line "close too!"
        t_prompt )

};

const txt_cmd_s v_Text_BallCaught[] = {
    text_start("Gotcha! @"
        )
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start(
        t_line "was caught!@"
        )
    sound_caught_mon
    text_end

    text_end

};

const txt_cmd_s v_WaitButtonText[] = {
    text_promptbutton
    text_end

    text_end

};

const txt_cmd_s v_BallSentToPCText[] = {
    text_ram(wram_ptr(wMonOrItemNameBuffer))
    text_start(" was"
        t_line "sent to BILL's PC."
        t_prompt )

};

const txt_cmd_s v_NewDexDataText[] = {
    text_ram(wram_ptr(wEnemyMonNickname))
    text_start("'s data"
        t_line "was newly added to"
        t_cont "the #DEX.@"
        )
    sound_slot_machine_start
    text_promptbutton
    text_end

    text_end

};

const txt_cmd_s v_AskGiveNicknameText[] = {
    text_start("Give a nickname to"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"
        t_done )

};

const txt_cmd_s v_ItemStatRoseText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start(" rose."
        t_prompt )

};

const txt_cmd_s v_ItemCantUseOnMonText[] = {
    text_start("That can't be used"
        t_line "on this #MON."
        t_prompt )

};

const txt_cmd_s v_RepelUsedEarlierIsStillInEffectText[] = {
    text_start("The REPEL used"
        t_line "earlier is still"
        t_cont "in effect."
        t_prompt )

};

const txt_cmd_s v_PlayedFluteText[] = {
    text_start("Played the #"
        t_line "FLUTE."

        t_para "Now, that's a"
        t_line "catchy tune!"
        t_prompt )

};

const txt_cmd_s v_FluteWakeUpText[] = {
    text_start("All sleeping"
        t_line "#MON woke up."
        t_prompt )

};

const txt_cmd_s v_Text_PlayedPokeFlute[] = {
    text_start("<PLAYER> played the"
        t_line "# FLUTE.@"
        )
    text_promptbutton
    text_end

    text_end

};

const txt_cmd_s v_BlueCardBalanceText[] = {
    text_start("You now have"
        t_line "@"
        )
    text_decimal(wram_ptr(wBlueCardBalance), 1, 2)
    text_start(" points."
        t_done )

};

const txt_cmd_s v_CoinCaseCountText[] = {
    text_start("Coins:"
        t_line "@"
        )
    text_decimal(wram_ptr(wCoins), 2, 4)
    text_end

    text_end

};

const txt_cmd_s v_RaiseThePPOfWhichMoveText[] = {
    text_start("Raise the PP of"
        t_line "which move?"
        t_done )

};

const txt_cmd_s v_RestoreThePPOfWhichMoveText[] = {
    text_start("Restore the PP of"
        t_line "which move?"
        t_done )

};

const txt_cmd_s v_PPIsMaxedOutText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start("'s PP"
        t_line "is maxed out."
        t_prompt )

};

const txt_cmd_s v_PPsIncreasedText[] = {
    text_ram(wram_ptr(wStringBuffer2))
    text_start("'s PP"
        t_line "increased."
        t_prompt )

};

const txt_cmd_s v_PPRestoredText[] = {
    text_start("PP was restored."
        t_prompt )

};

const txt_cmd_s v_SentTrophyHomeText[] = {
    text_start("There was a trophy"
        t_line "inside!@"
        )
    sound_dex_fanfare_50_79
    text_start(

        t_para "@"
        )
    text_ram(wram_ptr(wPlayerName))
    text_start(" sent the"
        t_line "trophy home."
        t_prompt )

};

const txt_cmd_s v_ItemLooksBitterText[] = {
    text_start("It looks bitter…"
        t_prompt )

};

const txt_cmd_s v_ItemCantUseOnEggText[] = {
    text_start("That can't be used"
        t_line "on an EGG."
        t_prompt )

};

const txt_cmd_s v_ItemOakWarningText[] = {
    text_start("OAK: <PLAYER>!"
        t_line "This isn't the"
        t_cont "time to use that!"
        t_prompt )

};

const txt_cmd_s v_ItemBelongsToSomeoneElseText[] = {
    text_start("That belongs to"
        t_line "someone else!"
        t_prompt )

};

const txt_cmd_s v_ItemWontHaveEffectText[] = {
    text_start("It won't have any"
        t_line "effect."
        t_prompt )

};

const txt_cmd_s v_BallBlockedText[] = {
    text_start("The trainer"
        t_line "blocked the BALL!"
        t_prompt )

};

const txt_cmd_s v_BallDontBeAThiefText[] = {
    text_start("Don't be a thief!"
        t_prompt )

};

const txt_cmd_s v_NoCyclingText[] = {
    text_start("Cycling isn't"
        t_line "allowed here."
        t_prompt )

};

const txt_cmd_s v_ItemCantGetOnText[] = {
    text_start("Can't get on your"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" now."
        t_prompt )

};

const txt_cmd_s v_BallBoxFullText[] = {
    text_start("The #MON BOX"
        t_line "is full. That"
        t_cont "can't be used now."
        t_prompt )

};

const txt_cmd_s v_ItemUsedText[] = {
    text_start("<PLAYER> used the@"
        )
    text_low
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_done )

};

const txt_cmd_s v_ItemGotOnText[] = {
    text_start("<PLAYER> got on the@"
        )
    text_low
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_ItemGotOffText[] = {
    text_start("<PLAYER> got off@"
        )
    text_low
    text_start("the @"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_KnowsMoveText[] = {
    text_ram(wram_ptr(wStringBuffer1))
    text_start(" knows"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer2))
    text_start("."
        t_prompt )

};

const txt_cmd_s v_MoveKnowsOneText[] = {
    text_start("That #MON knows"
        t_line "only one move."
        t_done )

};

const txt_cmd_s v_AskDeleteMoveText[] = {
    text_start("Oh, make it forget"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?"
        t_done )

};

const txt_cmd_s v_DeleterForgotMoveText[] = {
    text_start("Done! Your #MON"
        t_line "forgot the move."
        t_done )

};

const txt_cmd_s v_DeleterEggText[] = {
    text_start("An EGG doesn't"
        t_line "know any moves!"
        t_done )

};

const txt_cmd_s v_DeleterNoComeAgainText[] = {
    text_start("No? Come visit me"
        t_line "again."
        t_done )

};

const txt_cmd_s v_DeleterAskWhichMoveText[] = {
    text_start("Which move should"
        t_line "it forget, then?"
        t_prompt )

};

const txt_cmd_s v_DeleterIntroText[] = {
    text_start("Um… Oh, yes, I'm"
        t_line "the MOVE DELETER."

        t_para "I can make #MON"
        t_line "forget moves."

        t_para "Shall I make a"
        t_line "#MON forget?"
        t_done )

};

const txt_cmd_s v_DeleterAskWhichMonText[] = {
    text_start("Which #MON?"
        t_prompt )

};

const txt_cmd_s v_DSTIsThatOKText[] = {
    text_start(" DST,"
        t_line "is that OK?"
        t_done )

};

const txt_cmd_s v_TimeAskOkayText[] = {
    text_start(","
        t_line "is that OK?"
        t_done )

};

const txt_cmd_s v_TimesetAskDSTText[] = {
    text_start("Do you want to"
        t_line "switch to Daylight"
        t_cont "Saving Time?"
        t_done )

};

const txt_cmd_s v_TimesetDSTText[] = {
    text_start("I set the clock"
        t_line "forward by one"
        t_cont "hour."
        t_prompt )

};

const txt_cmd_s v_TimesetAskNotDSTText[] = {
    text_start("Is Daylight Saving"
        t_line "Time over?"
        t_done )

};

const txt_cmd_s v_TimesetNotDSTText[] = {
    text_start("I put the clock"
        t_line "back one hour."
        t_prompt )

};

const txt_cmd_s v_TimesetAskAdjustDSTText[] = {
    text_start("Do you want to"
        t_line "adjust your clock"

        t_para "for Daylight"
        t_line "Saving Time?"
        t_done )

};

const txt_cmd_s v_MomLostGearBookletText[] = {
    text_start("I lost the in-"
        t_line "struction booklet"
        t_cont "for the #GEAR."

        t_para "Come back again in"
        t_line "a while."
        t_prompt )
};
