#include "../../constants.h"
const txt_cmd_s NurseMornText[] = {
    text_start("Good morning!"
        t_line "Welcome to our"
        t_cont "#MON CENTER."
        t_done )

};

const txt_cmd_s NurseDayText[] = {
    text_start("Hello!"
        t_line "Welcome to our"
        t_cont "#MON CENTER."
        t_done )

};

const txt_cmd_s NurseNiteText[] = {
    text_start("Good evening!"
        t_line "You're out late."

        t_para "Welcome to our"
        t_line "#MON CENTER."
        t_done )

};

const txt_cmd_s PokeComNurseMornText[] = {
    text_start("Good morning!"

        t_para "This is the #-"
        t_line "MON COMMUNICATION"

        t_para "CENTER--or the"
        t_line "#COM CENTER."
        t_done )

};

const txt_cmd_s PokeComNurseDayText[] = {
    text_start("Hello!"

        t_para "This is the #-"
        t_line "MON COMMUNICATION"

        t_para "CENTER--or the"
        t_line "#COM CENTER."
        t_done )

};

const txt_cmd_s PokeComNurseNiteText[] = {
    text_start("Good to see you"
        t_line "working so late."

        t_para "This is the #-"
        t_line "MON COMMUNICATION"

        t_para "CENTER--or the"
        t_line "#COM CENTER."
        t_done )

};

const txt_cmd_s NurseAskHealText[] = {
    text_start("We can heal your"
        t_line "#MON to perfect"
        t_cont "health."

        t_para "Shall we heal your"
        t_line "#MON?"
        t_done )

};

const txt_cmd_s NurseTakePokemonText[] = {
    text_start("OK, may I see your"
        t_line "#MON?"
        t_done )

};

const txt_cmd_s NurseReturnPokemonText[] = {
    text_start("Thank you for"
        t_line "waiting."

        t_para "Your #MON are"
        t_line "fully healed."
        t_done )

};

const txt_cmd_s NurseGoodbyeText[] = {
    text_start("We hope to see you"
        t_line "again."
        t_done )


    text_start("We hope to see you"
        t_line "again."
        t_done )

};

const txt_cmd_s NursePokerusText[] = {
    text_start("Your #MON"
        t_line "appear to be"

        t_para "infected by tiny"
        t_line "life forms."

        t_para "Your #MON are"
        t_line "healthy and seem"
        t_cont "to be fine."

        t_para "But we can't tell"
        t_line "you anything more"

        t_para "at a #MON"
        t_line "CENTER."
        t_done )

};

const txt_cmd_s PokeComNursePokerusText[] = {
    text_start("Your #MON"
        t_line "appear to be"

        t_para "infected by tiny"
        t_line "life forms."

        t_para "Your #MON are"
        t_line "healthy and seem"
        t_cont "to be fine."

        t_para "But we can't tell"
        t_line "you anything more."
        t_done )

};

const txt_cmd_s DifficultBookshelfText[] = {
    text_start("It's full of"
        t_line "difficult books."
        t_done )

};

const txt_cmd_s PictureBookshelfText[] = {
    text_start("A whole collection"
        t_line "of #MON picture"
        t_cont "books!"
        t_done )

};

const txt_cmd_s MagazineBookshelfText[] = {
    text_start("#MON magazines…"
        t_line "#MON PAL,"

        t_para "#MON HANDBOOK,"
        t_line "#MON GRAPH…"
        t_done )

};

const txt_cmd_s TeamRocketOathText[] = {
    text_start("TEAM ROCKET OATH"

        t_para "Steal #MON for"
        t_line "profit!"

        t_para "Exploit #MON"
        t_line "for profit!"

        t_para "All #MON exist"
        t_line "for the glory of"
        t_cont "TEAM ROCKET!"
        t_done )

};

const txt_cmd_s IncenseBurnerText[] = {
    text_start("What is this?"

        t_para "Oh, it's an"
        t_line "incense burner!"
        t_done )

};

const txt_cmd_s MerchandiseShelfText[] = {
    text_start("Lots of #MON"
        t_line "merchandise!"
        t_done )

};

const txt_cmd_s LookTownMapText[] = {
    text_start("It's the TOWN MAP."
        t_done )

};

const txt_cmd_s WindowText[] = {
    text_start("My reflection!"
        t_line "Lookin' good!"
        t_done )

};

const txt_cmd_s TVText[] = {
    text_start("It's a TV."
        t_done )

};

const txt_cmd_s HomepageText[] = {
    text_start("#MON JOURNAL"
        t_line "HOME PAGE…"

        t_para "It hasn't been"
        t_line "updated…"
        t_done )


    text_start("#MON RADIO!"

        t_para "Call in with your"
        t_line "requests now!"
        t_done )

};

const txt_cmd_s TrashCanText[] = {
    text_start("There's nothing in"
        t_line "here…"
        t_done )


    text_start("A #MON may be"
        t_line "able to move this."
        t_done )


    text_start("Maybe a #MON"
        t_line "can break this."
        t_done )

};

const txt_cmd_s PokecenterSignText[] = {
    text_start("Heal Your #MON!"
        t_line "#MON CENTER"
        t_done )

};

const txt_cmd_s MartSignText[] = {
    text_start("For All Your"
        t_line "#MON Needs"

        t_para "#MON MART"
        t_done )

};

const txt_cmd_s ContestResults_ReadyToJudgeText[] = {
    text_start("We will now judge"
        t_line "the #MON you've"
        t_cont "caught."

        t_para "<……>"
        t_line "<……>"

        t_para "We have chosen the"
        t_line "winners!"

        t_para "Are you ready for"
        t_line "this?"
        t_done )

};

const txt_cmd_s ContestResults_PlayerWonAPrizeText[] = {
    text_start("<PLAYER>, the No.@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "finisher, wins"
        t_cont "@"
        )
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_done )

};

const txt_cmd_s ReceivedItemText[] = {
    text_start("<PLAYER> received"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_done )

};

const txt_cmd_s ContestResults_JoinUsNextTimeText[] = {
    text_start("Please join us for"
        t_line "the next Contest!"
        t_done )

};

const txt_cmd_s ContestResults_ConsolationPrizeText[] = {
    text_start("Everyone else gets"
        t_line "a BERRY as a con-"
        t_cont "solation prize!"
        t_done )

};

const txt_cmd_s ContestResults_DidNotWinText[] = {
    text_start("We hope you do"
        t_line "better next time."
        t_done )

};

const txt_cmd_s ContestResults_ReturnPartyText[] = {
    text_start("We'll return the"
        t_line "#MON we kept"

        t_para "for you."
        t_line "Here you go!"
        t_done )

};

const txt_cmd_s ContestResults_PartyFullText[] = {
    text_start("Your party's full,"
        t_line "so the #MON was"

        t_para "sent to your BOX"
        t_line "in BILL's PC."
        t_done )

};

const txt_cmd_s GymStatue_CityGymText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "#MON GYM"
        t_done )

};

const txt_cmd_s GymStatue_WinningTrainersText[] = {
    text_start("LEADER: @"
        )
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "WINNING TRAINERS:"
        t_line "<PLAYER>"
        t_done )

};

const txt_cmd_s CoinVendor_WelcomeText[] = {
    text_start("Welcome to the"
        t_line "GAME CORNER."
        t_done )

};

const txt_cmd_s CoinVendor_NoCoinCaseText[] = {
    text_start("Do you need game"
        t_line "coins?"

        t_para "Oh, you don't have"
        t_line "a COIN CASE for"
        t_cont "your coins."
        t_done )

};

const txt_cmd_s CoinVendor_IntroText[] = {
    text_start("Do you need some"
        t_line "game coins?"

        t_para "It costs ¥1000 for"
        t_line "50 coins. Do you"
        t_cont "want some?"
        t_done )

};

const txt_cmd_s CoinVendor_Buy50CoinsText[] = {
    text_start("Thank you!"
        t_line "Here are 50 coins."
        t_done )

};

const txt_cmd_s CoinVendor_Buy500CoinsText[] = {
    text_start("Thank you! Here"
        t_line "are 500 coins."
        t_done )

};

const txt_cmd_s CoinVendor_NotEnoughMoneyText[] = {
    text_start("You don't have"
        t_line "enough money."
        t_done )

};

const txt_cmd_s CoinVendor_CoinCaseFullText[] = {
    text_start("Whoops! Your COIN"
        t_line "CASE is full."
        t_done )

};

const txt_cmd_s CoinVendor_CancelText[] = {
    text_start("No coins for you?"
        t_line "Come again!"
        t_done )

};

const txt_cmd_s BugContestPrizeNoRoomText[] = {
    text_start("Oh? Your PACK is"
        t_line "full."

        t_para "We'll keep this"
        t_line "for you today, so"

        t_para "come back when you"
        t_line "make room for it."
        t_done )

};

const txt_cmd_s HappinessText3[] = {
    text_start("Wow! You and your"
        t_line "#MON are really"
        t_cont "close!"
        t_done )

};

const txt_cmd_s HappinessText2[] = {
    text_start("#MON get more"
        t_line "friendly if you"

        t_para "spend time with"
        t_line "them."
        t_done )

};

const txt_cmd_s HappinessText1[] = {
    text_start("You haven't tamed"
        t_line "your #MON."

        t_para "If you aren't"
        t_line "nice, it'll pout."
        t_done )

};

const txt_cmd_s RegisteredNumber1Text[] = {
    text_start("<PLAYER> registered"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("'s number."
        t_done )

};

const txt_cmd_s RegisteredNumber2Text[] = {
    text_start("<PLAYER> registered"
        t_line "@"
        )
    text_ram(wram_ptr(wStringBuffer3))
    text_start("'s number."
        t_done )
};
