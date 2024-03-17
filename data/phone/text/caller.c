#include "../../../constants.h"
#include "caller.h"

//// alan_caller.c

const txt_cmd_s AlanGettingStrongerText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "getting stronger,"
        t_para "exactly as I"
        t_line "calculated!"
        t_done )
};
const txt_cmd_s AlanDefeatedMonText[] = {
    text_start("By the way, we"
        t_line "knocked out a wild"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" just"
        t_line "the other day."
        t_para "Studying up in"
        t_line "advance worked!"
        t_done )
};
const txt_cmd_s AlanLostAMonText[] = {
    text_start("By the way, a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" escaped"
        t_cont "on me yesterday."
        t_para "A computational"
        t_line "error on my part…"
        t_done )
};
const txt_cmd_s AlanBattleRematchText[] = {
    text_start("I've studied quite"
        t_line "a bit since then,"
        t_para "and I've gotten a"
        t_line "lot better!"
        t_para "I'm hanging out on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "Can you come down"
        t_line "for a battle?"
        t_done )
};
const txt_cmd_s AlanHangUpText[] = {
    text_start("See you later!"
        t_done )
};
const txt_cmd_s AlanFoundItemText[] = {
    text_start("Hehehe, I picked"
        t_line "up something nice!"
        t_para "You can have it!"
        t_line "Why don't you come"
        t_para "to @")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(
        t_line "and pick it up?"
        t_done )
};
const txt_cmd_s AlanHaventPickedUpAnythingText[] = {
    text_start("I haven't picked"
        t_line "up anything yet."
        t_para "I'll call you if I"
        t_line "find something."
        t_done )
};
const txt_cmd_s AlanReminderText[] = {
    text_start("If we don't battle"
        t_line "soon, I'll forget"
        t_cont "my strategy!"
        t_para "I'm waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s AlanComePickUpGiftText[] = {
    text_start("I have to do my"
        t_line "homework, so can"
        t_para "you come get your"
        t_line "gift right away?"
        t_para "I'm waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};

//// anthony_caller.c

const txt_cmd_s AnthonyMonAteSomeBerriesText[] = {
    text_start("The other day, I"
        t_line "was watching my"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" eat"
        t_line "some BERRIES."
        t_para "It looked like it"
        t_line "was enjoying its"
        t_para "meal, so I decided"
        t_line "to try some."
        t_para "I'm not sure if"
        t_line "people should eat"
        t_para "that stuff, but it"
        t_line "was delicious!"
        t_done )
};
const txt_cmd_s AnthonyDefeatedMonText[] = {
    text_start("Lately, I've been"
        t_line "running across"
        t_para "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_line "quite often."
        t_para "They're easily"
        t_line "taken care of."
        t_done )
};
const txt_cmd_s AnthonyLostAMonText[] = {
    text_start("Oh yeah, I was"
        t_line "battling this"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" the"
        t_line "other day…"
        t_para "It took off when I"
        t_line "got distracted by"
        t_cont "a passing BEAUTY."
        t_para "Learn from my"
        t_line "mistake--always"
        t_para "stay focused on"
        t_line "the job at hand!"
        t_done )
};
const txt_cmd_s AnthonyBattleRematchText[] = {
    text_start("Come on--let's"
        t_line "battle right now!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(" is"
        t_line "where I am."
        t_para "Come on down if"
        t_line "you feel up to it!"
        t_done )
};
const txt_cmd_s AnthonyHangUpText[] = {
    text_start("All right then!"
        t_line "Be good!"
        t_done )
};
const txt_cmd_s AnthonySwarmText[] = {
    text_start("<PLAYER>! It's"
        t_line "mind-blowing!"
        t_para "I took a hike in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(
        t_cont "yesterday, see?"
        t_para "Well, there were"
        t_line "tons of @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "around! You have"
        t_line "to see it!"
        t_para "I get this feeling"
        t_line "that @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "may be timid."
        t_line "I didn't see any"
        t_para "where there are"
        t_line "strong #MON."
        t_done )
};
const txt_cmd_s AnthonyWasntPayingAttentionText[] = {
    text_start("Rare #MON?"
        t_para "Hey, sorry! I was"
        t_line "too focused on my"
        t_para "hike, so I wasn't"
        t_line "paying attention."
        t_done )
};
const txt_cmd_s AnthonyReminderText[] = {
    text_start("Hello! You haven't"
        t_line "forgotten about"
        t_para "our battle, have"
        t_line "you?"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_line "I'm waiting!"
        t_done )
};
const txt_cmd_s AnthonyHurryText[] = {
    text_start("Hello? What? Where"
        t_line "is DUNSPARCE?"
        t_para "DARK CAVE! Hurry!"
        t_para "I know I've said"
        t_line "it before, but"
        t_para "DUNSPARCE don't"
        t_line "appear when there"
        t_para "are strong #MON"
        t_line "around."
        t_done )
};

//// arnie_caller.c

const txt_cmd_s ArnieMonIsSoCuteText[] = {
    text_start("I'm always with my"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_para "It's so cute!"
        t_line "I just love it!"
        t_done )
};
const txt_cmd_s ArnieDefeatedMonText[] = {
    text_start("Changing the topic"
        t_line "here, I saw this"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" for the"
        t_line "first time."
        t_para "It was easy to"
        t_line "beat, actually."
        t_done )
};
const txt_cmd_s ArnieLostAMonText[] = {
    text_start("I was wondering,"
        t_line "do you happen to"
        t_cont "have @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("?"
        t_para "I can't seem to"
        t_line "catch one. What is"
        t_para "its weakness, I"
        t_line "wonder."
        t_done )
};
const txt_cmd_s ArnieBattleRematchText[] = {
    text_start("Hey, let's battle"
        t_line "our #MON!"
        t_para "I won't lose to"
        t_line "you battling or in"
        t_para "the Bug-Catching"
        t_line "Contest!"
        t_para "I'll be here on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s ArnieHangUpText[] = {
    text_start("Let's talk again,"
        t_line "huh?"
        t_done )
};
const txt_cmd_s ArnieSwarmText[] = {
    text_start("Boy, am I glad I"
        t_line "caught you!"
        t_para "A whole bunch of"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" have"
        t_para "appeared around"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_para "You have to see"
        t_line "this!"
        t_done )
};
const txt_cmd_s ArnieHaventSeenRareMonText[] = {
    text_start("I haven't had any"
        t_line "luck seeing rare"
        t_cont "#MON lately…"
        t_para "But I know they're"
        t_line "out there!"
        t_done )
};
const txt_cmd_s ArnieReminderText[] = {
    text_start("Hey, where are you"
        t_line "now?"
        t_para "Let's battle. I'll"
        t_line "be waiting for you"
        t_cont "on @")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s ArnieHurryText[] = {
    text_start("Hello? Are you"
        t_line "coming or what?"
        t_para "You're missing out"
        t_line "on seeing YANMA!"
        t_para "Get down to ROUTE"
        t_line "35 right now!"
        t_done )
};

//// beth_caller.c

const txt_cmd_s BethExhilaratingRideText[] = {
    text_start("Do you remember my"
        t_line "sweet @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("?"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" runs"
        t_line "very fast."
        t_para "It's exhilarating"
        t_line "to ride on its"
        t_para "back when it"
        t_line "really gets going."
        t_done )
};
const txt_cmd_s BethDefeatedMonText[] = {
    text_start("Oh, have you ever"
        t_line "seen a @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_cont "before?"
        t_para "I just battled"
        t_line "one…"
        t_para "It was much faster"
        t_line "than I expected."
        t_para "I was a little"
        t_line "shocked."
        t_para "I still won, of"
        t_line "course."
        t_done )
};
const txt_cmd_s BethLostAMonText[] = {
    text_start("Oh, I just saw a"
        t_line "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "I was trying to"
        t_line "catch it when I"
        t_para "noticed that I was"
        t_line "all out of #"
        t_cont "BALLS."
        t_para "If you don't check"
        t_line "your items, you"
        t_para "may run out at the"
        t_line "worst time."
        t_para "I hope you learn"
        t_line "from my mistake."
        t_done )
};
const txt_cmd_s BethBattleRematchText[] = {
    text_start("Do you want to"
        t_line "battle? I'm going"
        t_cont "to win this time!"
        t_para "I'll be waiting"
        t_line "for you around"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_line "Look for me, OK?"
        t_done )
};
const txt_cmd_s BethHangUpText[] = {
    text_start("OK, bye-bye!"
        t_done )
};
const txt_cmd_s BethLetsBattleAgainSometimeText[] = {
    text_start("Let's battle again"
        t_line "sometime!"
        t_done )
};
const txt_cmd_s BethReminderText[] = {
    text_start("Um… <PLAY_G>?"
        t_line "What's wrong?"
        t_para "Did you forget our"
        t_line "deal?"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "That's where I'm"
        t_line "waiting."
        t_done )
};

//// beverly_caller.c

const txt_cmd_s BeverlyMadeMonEvenCuterText[] = {
    text_start("I fancied up my"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and"
        t_para "made it even cuter"
        t_line "than before!"
        t_done )
};
const txt_cmd_s BeverlyDefeatedMonText[] = {
    text_start("I happened to come"
        t_line "across a wild"
        t_cont "SNUBBULL recently."
        t_para "My SNUBBULL, I"
        t_line "assure you, was"
        t_para "far cuter than the"
        t_line "wild one."
        t_done )
};
const txt_cmd_s BeverlyLostAMonText[] = {
    text_start("I happened to see"
        t_line "a wild MARILL the"
        t_para "other day."
        t_line "Or so I thought."
        t_para "A closer look"
        t_line "showed it was"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(". I was"
        t_line "quite miffed."
        t_done )
};
const txt_cmd_s BeverlyHangUpText[] = {
    text_start("You can expect a"
        t_line "call from me."
        t_done )
};
const txt_cmd_s BeverlyFoundItemText[] = {
    text_start("My husband got"
        t_line "some NUGGETS."
        t_para "If you'd like, you"
        t_line "could have one as"
        t_para "thanks for helping"
        t_line "me out."
        t_para "I'll be at"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "Please come see me"
        t_line "when you can."
        t_done )
};
const txt_cmd_s BeverlyLetsChatAboutMonAgainText[] = {
    text_start("Are your #MON"
        t_line "in prime form?"
        t_para "Let's chat about"
        t_line "#MON again."
        t_done )
};
const txt_cmd_s BeverlyComePickUpText[] = {
    text_start("Pardon?"
        t_line "Oh, the NUGGET?"
        t_para "There's no need to"
        t_line "hurry. Come see me"
        t_para "in @")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(
        t_line "when you can."
        t_done )
};

//// brent_caller.c

const txt_cmd_s BrentRareTradeText[] = {
    text_start("Oh yeah, I got an"
        t_line "extremely rare"
        t_para "#MON in a trade"
        t_line "a while back."
        t_para "Do you want to"
        t_line "know what it is?"
        t_para "Hehe, I'm keeping"
        t_line "it a secret!"
        t_done )
};
const txt_cmd_s BrentDefeatedMonText[] = {
    text_start("Oh yeah, I took"
        t_line "down this wild"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_line "It wasn't rare"
        t_para "enough to bother"
        t_line "catching."
        t_done )
};
const txt_cmd_s BrentLostAMonText[] = {
    text_start("Oh yeah, I saw a"
        t_line "rare #MON about"
        t_cont "an hour ago."
        t_para "It was my first"
        t_line "sighting. But I"
        t_para "didn't have any"
        t_line "# BALLS…"
        t_para "Would BILL laugh"
        t_line "at my mistakes?"
        t_done )
};
const txt_cmd_s BrentBattleRematchText[] = {
    text_start("You've got time"
        t_line "like usual, right?"
        t_para "Feel like having a"
        t_line "battle?"
        t_para "It'll be a chance"
        t_line "to see my rare"
        t_para "#MON. It'll be"
        t_line "worth your time!"
        t_para "You know where--"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s BrentHangUpText[] = {
    text_start("So that's it then."
        t_done )
};
const txt_cmd_s BrentFatherGossipText[] = {
    text_start("Did you know…?"
        t_line "BILL's father is"
        t_para "supposed to be a"
        t_line "great #MANIAC."
        t_done )
};
const txt_cmd_s BrentGrandpaGossipText[] = {
    text_start("Did you know…?"
        t_line "Apparently BILL's"
        t_para "grandpa isn't a"
        t_line "#MANIAC."
        t_done )
};
const txt_cmd_s BrentGoldenrodGossipText[] = {
    text_start("Did you know…?"
        t_line "BILL's originally"
        t_cont "from GOLDENROD."
        t_done )
};
const txt_cmd_s BrentRoute25GossipText[] = {
    text_start("Did you know…?"
        t_line "BILL evidently"
        t_para "lives on ROUTE 25"
        t_line "in KANTO."
        t_done )
};
const txt_cmd_s BrentAbraGossipText[] = {
    text_start("Did you know…?"
        t_line "ABRA was the first"
        t_para "#MON that BILL"
        t_line "ostensibly caught."
        t_done )
};
const txt_cmd_s BrentSisterGossipText[] = {
    text_start("Did you know…?"
        t_line "BILL's younger"
        t_para "sister apparently"
        t_line "can't wink."
        t_done )
};
const txt_cmd_s BrentMilkGossipText[] = {
    text_start("Did you know…?"
        t_line "BILL supposedly"
        t_para "hates milk and"
        t_line "can't drink it."
        t_done )
};
const txt_cmd_s BrentBattlingGossipText[] = {
    text_start("Did you know…?"
        t_line "Evidently, BILL"
        t_para "isn't very good at"
        t_line "battling."
        t_done )
};
const txt_cmd_s BrentFlowerShopGossipText[] = {
    text_start("Did you know…?"
        t_line "BILL appears to"
        t_para "like the lady at"
        t_line "the FLOWER SHOP."
        t_done )
};
const txt_cmd_s BrentKimonoGirlGossipText[] = {
    text_start("Did you know…?"
        t_line "BILL's mother is"
        t_para "said to have been"
        t_line "a KIMONO GIRL."
        t_done )
};
const txt_cmd_s BrentSorryImTooBusyText[] = {
    text_start("You wanted to hear"
        t_line "about BILL?"
        t_para "Sorry, but I'm too"
        t_line "busy for you."
        t_para "I'll call when I"
        t_line "have time."
        t_done )
};
const txt_cmd_s BrentReminderText[] = {
    text_start("You want to see my"
        t_line "rare #MON."
        t_para "Hurry over to"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};

//// chad_caller.c

const txt_cmd_s ChadObservingWildText[] = {
    text_start("I recently began"
        t_line "observing wild"
        t_cont "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "I've been learning"
        t_line "all sorts of new"
        t_para "things through my"
        t_line "observations."
        t_para "I wish I could"
        t_line "become a #MON"
        t_para "researcher like"
        t_line "PROF.OAK soon."
        t_done )
};
const txt_cmd_s ChadDefeatedMonText[] = {
    text_start("Oh yes, I managed"
        t_line "to knock out a"
        t_para "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" a"
        t_line "while back."
        t_para "Well, considering"
        t_line "all the studying I"
        t_para "do every day, it"
        t_line "was inevitable."
        t_done )
};
const txt_cmd_s ChadLostAMonText[] = {
    text_start("Oh yes, I came"
        t_line "close to catching"
        t_para "a wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(","
        t_line "but it got away."
        t_para "For the longest"
        t_line "time, I've been"
        t_para "wanting to observe"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(". Rats…"
        t_done )
};
const txt_cmd_s ChadBattleRematchText[] = {
    text_start("Want to battle?"
        t_line "I have to battle"
        t_para "every so often to"
        t_line "avoid rusting out."
        t_para "I'll be on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s ChadHangUpText[] = {
    text_start("See you later!"
        t_done )
};
const txt_cmd_s ChadBlueGossipText[] = {
    text_start("Do you know BLUE?"
        t_para "He's PROF.OAK's"
        t_line "grandson and a"
        t_para "former #MON"
        t_line "LEAGUE CHAMPION!"
        t_para "He's one super"
        t_line "#MON trainer!"
        t_done )
};
const txt_cmd_s ChadDaisyGossipText[] = {
    text_start("PROF.OAK has a"
        t_line "granddaughter"
        t_cont "named DAISY."
        t_para "When she's around,"
        t_line "even the most"
        t_para "ferocious #MON"
        t_line "calm right down."
        t_done )
};
const txt_cmd_s ChadProfElmGossipText[] = {
    text_start("Everyone's talking"
        t_line "about PROF.ELM."
        t_para "He used to be an"
        t_line "assistant to the"
        t_cont "great PROF.OAK!"
        t_para "That is so cool!"
        t_line "I envy him!"
        t_done )
};
const txt_cmd_s ChadProfOaksDreamGossipText[] = {
    text_start("PROF.OAK's dream"
        t_line "is to compile a"
        t_para "comprehensive"
        t_line "#DEX."
        t_para "I envy you for"
        t_line "taking part in"
        t_cont "that project…"
        t_done )
};
const txt_cmd_s ChadKurtGossipText[] = {
    text_start("Do you know KURT,"
        t_line "the BALL creator?"
        t_para "He and PROF.OAK go"
        t_line "back a long way."
        t_para "I guess great"
        t_line "people attract one"
        t_cont "another!"
        t_done )
};
const txt_cmd_s ChadLeagueGossipText[] = {
    text_start("#MON LEAGUE is"
        t_line "the great gather-"
        t_cont "ing place for all"
        t_para "trainers who wish"
        t_line "to become CHAMP."
        t_para "PROF.OAK acts as"
        t_line "an advisor to the"
        t_para "#MON LEAGUE's"
        t_line "headquarters."
        t_para "He really is a"
        t_line "great man."
        t_done )
};
const txt_cmd_s ChadPokemonTalkGossipText[] = {
    text_start("PROF.OAK'S #MON"
        t_line "TALK is a popular"
        t_cont "radio show, right?"
        t_para "Did you know that"
        t_line "he was going to"
        t_para "turn down the show"
        t_line "at first?"
        t_para "But MARY's energy"
        t_line "and persistence"
        t_cont "wore him down."
        t_para "So we have MARY to"
        t_line "thank for it!"
        t_done )
};
const txt_cmd_s ChadProfOakTrainerGossipText[] = {
    text_start("PROF.OAK used to"
        t_line "be a trainer a"
        t_cont "long time ago."
        t_para "But rather than"
        t_line "battling, he found"
        t_para "#MON themselves"
        t_line "to be interesting."
        t_para "So he abandoned"
        t_line "his training to"
        t_para "focus on becoming"
        t_line "a researcher."
        t_done )
};
const txt_cmd_s ChadDaisyTeaGossipText[] = {
    text_start("PROF.OAK has a"
        t_line "granddaughter"
        t_cont "named DAISY."
        t_para "She has tea every"
        t_line "day for an hour"
        t_para "from three in the"
        t_line "afternoon."
        t_para "I wish I could"
        t_line "join her for tea"
        t_para "and chat about"
        t_line "PROF.OAK."
        t_done )
};
const txt_cmd_s ChadProfOakTravelingGossipText[] = {
    text_start("Did you know?"
        t_line "PROF.OAK traveled"
        t_para "all over the world"
        t_line "when he was young."
        t_para "While traveling,"
        t_line "he must've learned"
        t_para "about #MON"
        t_line "naturally."
        t_para "I envy him…"
        t_line "I'd like to travel"
        t_para "and learn about"
        t_line "things too…"
        t_done )
};
const txt_cmd_s ChadGoingToStudyHardText[] = {
    text_start("I'm going to study"
        t_line "hard so PROF.OAK"
        t_para "will make me his"
        t_line "assistant!"
        t_done )
};
const txt_cmd_s ChadReminderText[] = {
    text_start("Do you remember"
        t_line "about our battle?"
        t_para "The place is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "Hurry over--I'm"
        t_line "waiting."
        t_done )
};

//// dana_caller.c

const txt_cmd_s DanaTakingPhotosText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is"
        t_line "getting prettier!"
        t_para "I've been taking"
        t_line "photos galore!"
        t_done )
};
const txt_cmd_s DanaDefeatedMonText[] = {
    text_start("It took only an"
        t_line "instant to KO a"
        t_cont "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "It must be because"
        t_line "you gave me some"
        t_para "battling tips last"
        t_line "time."
        t_done )
};
const txt_cmd_s DanaLostAMonText[] = {
    text_start("You know what?"
        t_line "A wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "got away from me"
        t_line "again."
        t_para "It was so close!"
        t_line "Really, just a"
        t_para "little bit more,"
        t_line "and I would've…"
        t_done )
};
const txt_cmd_s DanaBattleRematchText[] = {
    text_start("Right now, I'm on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "If you're close"
        t_line "by, let's battle!"
        t_para "I'll be waiting"
        t_line "for you!"
        t_done )
};
const txt_cmd_s DanaHangUpText[] = {
    text_start("See you!"
        t_done )
};
const txt_cmd_s DanaFoundItemText[] = {
    text_start("You know what?"
        t_line "I got a good gift!"
        t_para "As I promised,"
        t_line "it's yours!"
        t_para "I'm sure you'd"
        t_line "like it. Come get"
        t_para "it! I'm waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s DanaCanYouWaitABitLongerText[] = {
    text_start("Oh! You wanted a"
        t_line "gift, right?"
        t_para "I got one, but I"
        t_line "want to keep this."
        t_para "Can you wait a bit"
        t_line "longer?"
        t_done )
};
const txt_cmd_s DanaReminderText[] = {
    text_start("Hi! You haven't"
        t_line "forgotten about"
        t_para "your promise to"
        t_line "battle me?"
        t_para "I'm waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s DanaComePickUpText[] = {
    text_start("Hello?"
        t_para "If you don't come"
        t_line "get your present"
        t_para "soon, I'll give it"
        t_line "to someone else."
        t_para "I'm waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};

//// derek_caller.c

const txt_cmd_s DerekCheekPinchingText[] = {
    text_start("Listen to this."
        t_line "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "grins happily when"
        t_line "I pinch its cheek."
        t_para "But it never grins"
        t_line "for anyone else."
        t_para "I must be special."
        t_done )
};
const txt_cmd_s DerekDefeatedMonText[] = {
    text_start("Oh, and recently,"
        t_line "my PIKACHU beat a"
        t_cont "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_para "A wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(","
        t_line "I tell you!"
        t_para "Don't you think"
        t_line "that's astounding?"
        t_para "My PIKACHU is"
        t_line "awesome!"
        t_para "My PIKACHU is the"
        t_line "greatest!"
        t_done )
};
const txt_cmd_s DerekLostAMonText[] = {
    text_start("Oh, and I saw a"
        t_line "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" a"
        t_cont "little while ago."
        t_para "But it wasn't very"
        t_line "cute, so I left"
        t_para "it…"
        t_line "#MON have to be"
        t_para "cute. They're no"
        t_line "good otherwise."
        t_done )
};
const txt_cmd_s DerekHangUpText[] = {
    text_start("Well, let's talk"
        t_line "again!"
        t_done )
};
const txt_cmd_s DerekBugCatchingContestText[] = {
    text_start("Did you remember?"
        t_line "The Bug-Catching"
        t_cont "Contest is today."
        t_para "You're going to"
        t_line "go, aren't you?"
        t_para "I think I'll"
        t_line "participate with"
        t_para "PIKACHU to show"
        t_line "off its cuteness."
        t_done )
};
const txt_cmd_s DerekFoundItemText[] = {
    text_start("I'd like you to"
        t_line "have a NUGGET."
        t_para "My PIKACHU just"
        t_line "loves it."
        t_para "I'm certain your"
        t_line "PIKACHU will love"
        t_cont "it too!"
        t_done )
};
const txt_cmd_s DerekLetsGetTogetherText[] = {
    text_start("How is your"
        t_line "PIKACHU doing?"
        t_para "Let's get together"
        t_line "and brag about our"
        t_cont "PIKACHU!"
        t_done )
};
const txt_cmd_s DerekComePickUpText[] = {
    text_start("What's wrong?"
        t_para "I'm waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "Come pick this up"
        t_line "anytime."
        t_done )
};

//// erin_caller.c

const txt_cmd_s ErinMonIsMuchStrongerText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start("'s @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_line "is much stronger"
        t_cont "than before!"
        t_done )
};
const txt_cmd_s ErinDefeatedMonText[] = {
    text_start("And, and…"
        t_line "I just battled and"
        t_cont "beat @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_para "I've raised my"
        t_line "#MON properly!"
        t_done )
};
const txt_cmd_s ErinLostAMonText[] = {
    text_start("But, but…"
        t_para "A wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_line "got away from me"
        t_para "again. It's just"
        t_line "not fair!"
        t_done )
};
const txt_cmd_s ErinBattleRematchText[] = {
    text_start("I'm ERIN. Want to"
        t_line "battle me again?"
        t_para "I won't lose this"
        t_line "time!"
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s ErinHangUpText[] = {
    text_start("See you. Bye-bye!"
        t_done )
};
const txt_cmd_s ErinWorkingHardText[] = {
    text_start("I'm working hard"
        t_line "to raise my"
        t_cont "#MON!"
        t_para "Come back for"
        t_line "another battle!"
        t_done )
};
const txt_cmd_s ErinComeBattleText[] = {
    text_start("Oh, <PLAY_G>!"
        t_line "Come battle ERIN!"
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};

//// gaven_caller.c

const txt_cmd_s GavenMonGreaterThanImaginedText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_line "might be greater"
        t_cont "than I imagined."
        t_para "I doubt I'll see a"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" that's"
        t_cont "better than mine."
        t_done )
};
const txt_cmd_s GavenDefeatedMonText[] = {
    text_start("Oh, and I managed"
        t_line "to barely defeat"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" the"
        t_line "other day."
        t_para "I've never seen a"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" get"
        t_cont "that strong…"
        t_para "You shouldn't let"
        t_line "your guard down,"
        t_para "even against a"
        t_line "#MON you're"
        t_cont "used to seeing."
        t_done )
};
const txt_cmd_s GavenLostAMonText[] = {
    text_start("And a while back,"
        t_line "I tried to catch a"
        t_cont "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "But it managed to"
        t_line "elude me."
        t_para "One wrong decision"
        t_line "could mean total"
        t_para "failure… You ought"
        t_line "to be careful too."
        t_done )
};
const txt_cmd_s GavenBattleRematchText[] = {
    text_start("Let's battle!"
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "Give me a shout"
        t_line "when you're close."
        t_done )
};
const txt_cmd_s GavenHangUpText[] = {
    text_start("OK, I'll talk to"
        t_line "you soon!"
        t_done )
};
const txt_cmd_s GavenHangUpNotThursdayText[] = {
    text_start("I obsess over how"
        t_line "to beat you."
        t_done )
};
const txt_cmd_s GavenReminderText[] = {
    text_start("<PLAY_G>, why"
        t_line "aren't you here?"
        t_para "I'll take you down"
        t_line "with @")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};

//// gina_caller.c

const txt_cmd_s GinaGettingInSyncWithMonText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and"
        t_line "I are getting more"
        t_para "in sync with each"
        t_line "other."
        t_done )
};
const txt_cmd_s GinaDefeatedMonText[] = {
    text_start("We battled a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and"
        t_para "managed to drop it"
        t_line "in a close match."
        t_para "We're getting into"
        t_line "the groove!"
        t_done )
};
const txt_cmd_s GinaLostAMonText[] = {
    text_start("But, you know?"
        t_para "I still haven't"
        t_line "caught @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "It's getting past"
        t_line "frustrating…"
        t_done )
};
const txt_cmd_s GinaBattleRematchText[] = {
    text_start("Would you be my"
        t_line "practice partner"
        t_cont "again sometime?"
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "…Could you take it"
        t_line "a little easier on"
        t_cont "me next time?"
        t_done )
};
const txt_cmd_s GinaHangUpText[] = {
    text_start("Bye! Let's chat"
        t_line "again!"
        t_done )
};
const txt_cmd_s GinaRocketTakeoverRumorText[] = {
    text_start("Have you heard"
        t_line "about TEAM ROCKET?"
        t_para "They've taken over"
        t_line "the RADIO TOWER in"
        t_cont "GOLDENROD."
        t_para "Are the people"
        t_line "inside safe?"
        t_done )
};
const txt_cmd_s GinaFoundItemText[] = {
    text_start("I picked up some-"
        t_line "thing nice today."
        t_para "I want you to have"
        t_line "it, so I called!"
        t_para "You will come for"
        t_line "it, won't you?"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(" is"
        t_line "where I am."
        t_done )
};
const txt_cmd_s GinaHaventFoundAnythingYetText[] = {
    text_start("Sorry, I haven't"
        t_line "found anything"
        t_para "useful yet…"
        t_line "I promise, if I"
        t_para "find anything, you"
        t_line "can have it!"
        t_done )
};
const txt_cmd_s GinaReminderText[] = {
    text_start("Oh, <PLAY_G>!"
        t_line "How soon can I"
        t_para "expect to see you"
        t_line "for our battle?"
        t_para "Don't forget,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s GinaComePickUpText[] = {
    text_start("I'm getting really"
        t_line "impatient, waiting"
        t_para "to give you my"
        t_line "present!"
        t_para "Hurry over to"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};

//// huey_caller.c

const txt_cmd_s HueyBattleRematchText[] = {
    text_start("Hey, I challenge"
        t_line "you to a battle!"
        t_para "It won't be like"
        t_line "last time!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("'s"
        t_line "where I'm waiting"
        t_para "for you. Hustle"
        t_line "over here pronto!"
        t_done )
};
const txt_cmd_s HueyHangUpText[] = {
    text_start("See ya!"
        t_done )
};
const txt_cmd_s HueyWeHaveToBattleAgainSometimeText[] = {
    text_start("We have to battle"
        t_line "again sometime."
        t_para "You can bet I'm"
        t_line "going to keep"
        t_para "challenging you"
        t_line "till I win."
        t_done )
};
const txt_cmd_s HueyReminderText[] = {
    text_start("Hey, you'd better"
        t_line "not have forgotten"
        t_cont "about our battle!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_para "Hustle over quick!"
        t_line "I'm waiting!"
        t_done )
};

//// irwin_caller.c

const txt_cmd_s IrwinHangUpText[] = {
    text_start("I hate having to"
        t_line "hang up on you!"
        t_para "Call you later!"
        t_done )
};
const txt_cmd_s IrwinRocketTakeoverRumorText[] = {
    text_start("<PLAY_G>, have you"
        t_line "heard?"
        t_para "GOLDENROD's RADIO"
        t_line "TOWER has been"
        t_para "taken over by TEAM"
        t_line "ROCKET!"
        t_para "…Um… What's TEAM"
        t_line "ROCKET?"
        t_done )
};
const txt_cmd_s IrwinPlainBadgeGossipText[] = {
    text_start("<PLAY_G>, I heard!"
        t_para "You defeated that"
        t_line "WHITNEY?"
        t_para "It makes me proud"
        t_line "to be your friend!"
        t_done )
};
const txt_cmd_s IrwinJasmineReturnedGossipText[] = {
    text_start("Hey, I heard about"
        t_line "you!"
        t_para "You saved that"
        t_line "#MON at the"
        t_para "LIGHTHOUSE, didn't"
        t_line "you?"
        t_para "<PLAY_G>, I wish"
        t_line "you'd come see me"
        t_para "when I'm sick in"
        t_line "bed with a cold!"
        t_done )
};
const txt_cmd_s IrwinRocketHideoutGossipText[] = {
    text_start("I heard, I heard,"
        t_line "I heard!"
        t_para "You smashed TEAM"
        t_line "ROCKET's hideout!"
        t_para "You're like a"
        t_line "movie hero, even!"
        t_para "But um… What was"
        t_line "TEAM ROCKET?"
        t_done )
};
const txt_cmd_s IrwinRadioTowerGossipText[] = {
    text_start("I heard, I heard,"
        t_line "I heard!"
        t_para "About your heroic"
        t_line "liberation of the"
        t_para "RADIO TOWER! You"
        t_line "rock so hard!"
        t_done )
};
const txt_cmd_s IrwinRisingBadgeGossipText[] = {
    text_start("I saw, I saw!"
        t_para "I saw you go into"
        t_line "the DRAGON'S DEN!"
        t_para "I'm certain you"
        t_line "passed! Aww, no"
        t_para "need to be modest!"
        t_line "You can't fail!"
        t_done )
};
const txt_cmd_s IrwinEliteFourGossipText[] = {
    text_start("Yesterday, I went"
        t_line "out to NEW BARK"
        t_para "TOWN.  There was a"
        t_line "lady who looked a"
        t_para "lot like you,"
        t_line "<PLAY_G>."
        t_para "What? That lady"
        t_line "was your mom?"
        t_para "Aww, I should've"
        t_line "introduced myself!"
        t_para "I bet your mom's"
        t_line "really proud of"
        t_para "all that you've"
        t_line "accomplished."
        t_para "Heh, put it this"
        t_line "way. I'd be proud"
        t_para "if I were your"
        t_line "mom, believe me!"
        t_done )
};
const txt_cmd_s IrwinVermilionCityGossipText[] = {
    text_start("I saw, I saw,"
        t_line "I saw!"
        t_para "You striding onto"
        t_line "a ship, <PLAY_G>!"
        t_para "I can't get over"
        t_line "how good you look"
        t_para "with the sea as"
        t_line "your backdrop!"
        t_done )
};
const txt_cmd_s IrwinTrainPassGossipText[] = {
    text_start("I heard, I heard!"
        t_para "You got a MAGNET"
        t_line "TRAIN PASS!"
        t_para "When I saw you"
        t_line "departing on the"
        t_para "ship, I felt sad"
        t_line "that I wouldn't be"
        t_para "able to see you"
        t_line "for a while."
        t_para "But since you have"
        t_line "that PASS, you can"
        t_para "zip back anytime!"
        t_line "That's reassuring!"
        t_para "What? You can FLY"
        t_line "back anytime?"
        t_para "What do you mean"
        t_line "by FLY?"
        t_done )
};
const txt_cmd_s IrwinSnorlaxGossipText[] = {
    text_start("I saw, I saw!"
        t_para "You waking up"
        t_line "SNORLAX!"
        t_para "I was watching you"
        t_line "from afar, so I"
        t_para "couldn't tell what"
        t_line "you did exactly."
        t_para "Did you play a"
        t_line "flute to wake it?"
        t_para "Wow! That's like"
        t_line "magic!"
        t_done )
};
const txt_cmd_s IrwinMtSilverGossipText[] = {
    text_start("I hear rumors"
        t_line "about you all over"
        t_cont "the place."
        t_para "It just makes me"
        t_line "sigh, <PLAY_G>."
        t_para "How did you get so"
        t_line "strong?"
        t_para "Go for the world"
        t_line "championship now!"
        t_para "I'll always be"
        t_line "cheering you on!"
        t_done )
};
const txt_cmd_s IrwinCalledRightAwayText[] = {
    text_start("Hehe, I called"
        t_line "right away!"
        t_para "I think we can be"
        t_line "good friends!"
        t_done )
};
const txt_cmd_s IrwinFogBadgeGossipText[] = {
    text_start("I saw, I heard!"
        t_para "You beat MORTY of"
        t_line "ECRUTEAK GYM!"
        t_para "Th-that's just"
        t_line "incredible!"
        t_para "I actually went to"
        t_line "the GYM's entrance"
        t_para "to cheer you on."
        t_line "Did you know that?"
        t_para "But everyone was"
        t_line "floating, and"
        t_para "there were ghosts"
        t_line "all over! So I"
        t_para "chickened out and"
        t_line "took off for home…"
        t_done )
};
const txt_cmd_s IrwinMarshBadgeGossipText[] = {
    text_start("<PLAY_G>, I heard!"
        t_para "You're kicking up"
        t_line "a mighty ruckus"
        t_para "over in KANTO!"
        t_line "What a glorious"
        t_para "rampage it must"
        t_line "be!"
        t_para "You so rock!"
        t_done )
};
const txt_cmd_s IrwinYourEscapadesRockText[] = {
    text_start("Hearing about your"
        t_line "escapades rocks my"
        t_para "soul!"
        t_line "It sure does!"
        t_done )
};
const txt_cmd_s IrwinGoodMatchText[] = {
    text_start("I'm so glad you"
        t_line "called!"
        t_para "I was just about"
        t_line "to call you too!"
        t_para "I guess we must be"
        t_line "a good match!"
        t_done )
};
const txt_cmd_s IrwinSoMuchToChatAboutText[] = {
    text_start("How are you?"
        t_para "What are you"
        t_line "doing?"
        t_para "Where are you?"
        t_para "How many BADGES do"
        t_line "you have now?"
        t_para "How much money"
        t_line "have you saved?"
        t_para "How's your mom?"
        t_para "Have you got lots"
        t_line "of #MON?"
        t_para "Is it going to be"
        t_line "sunny tomorrow?"
        t_para "Arrgh, there's so"
        t_line "much I want to"
        t_para "chat about! This"
        t_line "is going nowhere!"
        t_done )
};

//// jack_caller.c

const txt_cmd_s JackIntelligenceKeepsRisingText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "intelligence keeps"
        t_para "rising. It might"
        t_line "be smarter than"
        t_cont "yours!"
        t_done )
};
const txt_cmd_s JackDefeatedMonText[] = {
    text_start("The other day, I"
        t_line "easily defeated a"
        t_cont "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "I think swapping"
        t_line "tips with you is"
        t_cont "starting to help."
        t_done )
};
const txt_cmd_s JackLostAMonText[] = {
    text_start("Oh, and listen."
        t_line "I missed catching"
        t_para "a @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" by"
        t_line "just a tiny bit."
        t_para "If I'd been a bit"
        t_line "more informed, I'm"
        t_para "sure I would've"
        t_line "caught it…"
        t_done )
};
const txt_cmd_s JackBattleRematchText[] = {
    text_start("Do you want to"
        t_line "battle? I'll show"
        t_para "you how to battle"
        t_line "logically."
        t_para "I'll be in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "Give me a shout if"
        t_line "you're nearby."
        t_done )
};
const txt_cmd_s JackHangUpText[] = {
    text_start("See you later!"
        t_done )
};
const txt_cmd_s JackThunderTriviaText[] = {
    text_start("Did you know?"
        t_para "When it's raining,"
        t_line "THUNDER is sure to"
        t_cont "strike."
        t_done )
};
const txt_cmd_s JackRolloutTriviaText[] = {
    text_start("Did you know…?"
        t_para "If you use DEFENSE"
        t_line "CURL, ROLLOUT's"
        t_para "power goes way up"
        t_line "past normal."
        t_done )
};
const txt_cmd_s JackSolarbeamTriviaText[] = {
    text_start("Did you know…?"
        t_para "If the sunlight is"
        t_line "harsh, SOLARBEAM"
        t_para "doesn't need to be"
        t_line "charged up."
        t_done )
};
const txt_cmd_s JackStompTriviaText[] = {
    text_start("Did you know…?"
        t_para "If the opponent"
        t_line "uses MINIMIZE,"
        t_para "your STOMP becomes"
        t_line "more powerful."
        t_done )
};
const txt_cmd_s JackGustTriviaText[] = {
    text_start("Did you know…?"
        t_para "If your opponent"
        t_line "is FLYing, your"
        t_para "GUST becomes much"
        t_line "more powerful."
        t_done )
};
const txt_cmd_s JackTwisterTriviaText[] = {
    text_start("Did you know…?"
        t_para "If your opponent"
        t_line "is FLYing, your"
        t_para "TWISTER becomes"
        t_line "more powerful."
        t_done )
};
const txt_cmd_s JackEarthquakeTriviaText[] = {
    text_start("Did you know…?"
        t_para "If your opponent"
        t_line "uses DIG, your"
        t_para "EARTHQUAKE becomes"
        t_line "more powerful."
        t_done )
};
const txt_cmd_s JackMagnitudeTriviaText[] = {
    text_start("Did you know…?"
        t_para "If your opponent"
        t_line "uses DIG, your"
        t_para "MAGNITUDE becomes"
        t_line "more powerful."
        t_done )
};
const txt_cmd_s JackSandstormTriviaText[] = {
    text_start("Did you know…?"
        t_para "The rock, ground"
        t_line "and steel types"
        t_para "can't be hurt by"
        t_line "SANDSTORM."
        t_done )
};
const txt_cmd_s JackSunnyDayTriviaText[] = {
    text_start("Did you know…?"
        t_para "If the sunlight is"
        t_line "harsh, water-type"
        t_para "moves become much"
        t_line "weaker."
        t_done )
};
const txt_cmd_s JackRainDanceTriviaText[] = {
    text_start("Did you know…?"
        t_para "When it's raining,"
        t_line "fire-type moves"
        t_para "become much weaker"
        t_line "than usual."
        t_done )
};
const txt_cmd_s JackHeardSomeGreatTipsText[] = {
    text_start("My friend heard"
        t_line "some great tips."
        t_para "He's going to let"
        t_line "me in on some."
        t_para "When he tells me,"
        t_line "I'll call right"
        t_cont "away and tell you."
        t_done )
};
const txt_cmd_s JackReminderText[] = {
    text_start("Hey, <PLAY_G>!"
        t_para "Do you remember"
        t_line "your promise?"
        t_para "We have to battle"
        t_line "soon!"
        t_para "I'll be at"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};

//// joey_caller.c

const txt_cmd_s JoeyMonLookingSharperText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "looking sharper"
        t_cont "than before!"
        t_para "I doubt there's a"
        t_line "#MON as cool as"
        t_para "this guy in your"
        t_line "party!"
        t_done )
};
const txt_cmd_s JoeyDefeatedMonText[] = {
    text_start("Oh yeah, I took"
        t_line "down a @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "in the wild the"
        t_line "other day."
        t_para "It was a cakewalk."
        t_line "Well, I guess it"
        t_para "can't be helped,"
        t_line "us being so tough."
        t_done )
};
const txt_cmd_s JoeyLostAMonText[] = {
    text_start("Oh yeah, I saw a"
        t_line "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_para "I thought about"
        t_line "going for it, but"
        t_para "I decided to work"
        t_line "with my one-and-"
        t_para "only right to the"
        t_line "extreme end."
        t_done )
};
const txt_cmd_s JoeyBattleRematchText[] = {
    text_start("Let's get together"
        t_line "and battle!"
        t_para "I promise things"
        t_line "will be different!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("'s"
        t_line "where I'll be."
        t_para "Give me a shout"
        t_line "when you come."
        t_done )
};
const txt_cmd_s JoeyHangUpText[] = {
    text_start("All right. Later!"
        t_done )
};
const txt_cmd_s JoeyDevisingStrategiesText[] = {
    text_start("I'm checking out"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s moves"
        t_para "and devising some"
        t_line "strategies."
        t_para "When I come up"
        t_line "with a good one,"
        t_cont "let's battle!"
        t_done )
};
const txt_cmd_s JoeyReminderText[] = {
    text_start("What's keeping"
        t_line "you, <PLAYER>!"
        t_para "Let's get down and"
        t_line "battle already!"
        t_para "I'm waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};

//// jose_caller.c

const txt_cmd_s JoseMonsStickHasADeliciousAromaText[] = {
    text_start("Hey listen, my"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s stick"
        t_para "has this really"
        t_line "delicious aroma."
        t_para "That aroma gets my"
        t_line "appetite going!"
        t_done )
};
const txt_cmd_s JoseDefeatedMonText[] = {
    text_start("A while ago, my"
        t_line "FARFETCH'D KO'd"
        t_cont "this @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "You should have"
        t_line "seen FARFETCH'D"
        t_para "wield that stick."
        t_line "Amazing stuff!"
        t_done )
};
const txt_cmd_s JoseLostAMonText[] = {
    text_start("I ran into a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("…"
        t_para "I was trying to"
        t_line "catch it, but it"
        t_para "took off faster"
        t_line "than I thought it"
        t_para "would. It was a"
        t_line "bit disappointing."
        t_done )
};
const txt_cmd_s JoseBattleRematchText[] = {
    text_start("Want to battle"
        t_line "again?"
        t_para "For some reason,"
        t_line "my FARFETCH'D is"
        t_para "all worked up and"
        t_line "raring to go."
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("'s"
        t_line "where I'm at."
        t_para "Keep an eye out"
        t_line "for me, OK?"
        t_done )
};
const txt_cmd_s JoseHangUpText[] = {
    text_start("Be seeing you!"
        t_done )
};
const txt_cmd_s JoseFoundItemText[] = {
    text_start("My FARFETCH'D had"
        t_line "something pretty"
        t_cont "in its beak."
        t_para "Like I promised,"
        t_line "you can have it."
        t_para "Catch up to me on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(","
        t_para "and I'll let you"
        t_line "have it."
        t_done )
};
const txt_cmd_s JoseHaventGottenItemYetText[] = {
    text_start("I haven't gotten"
        t_line "what I promised"
        t_cont "you yet."
        t_para "I'll call you as"
        t_line "soon as I get it,"
        t_para "so could you wait"
        t_line "a little longer?"
        t_done )
};
const txt_cmd_s JoseReminderText[] = {
    text_start("<PLAY_G>, could you"
        t_line "hurry over?"
        t_para "FARFETCH'D is"
        t_line "agitated."
        t_para "If you don't come"
        t_line "soon, it might"
        t_para "smack me with its"
        t_line "stick!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_para "Please come as"
        t_line "soon as you can!"
        t_done )
};
const txt_cmd_s JoseComePickUpText[] = {
    text_start("What's wrong?"
        t_para "Don't you want"
        t_line "this gift?"
        t_para "Catch up to me on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(","
        t_para "and I'll let you"
        t_line "have it."
        t_done )
};

//// kenji_caller.c

const txt_cmd_s KenjiHangUpText[] = {
    text_start("Anyway, we'll chat"
        t_line "again!"
        t_done )
};
const txt_cmd_s KenjiRemainDedicatedText[] = {
    text_start("Are you still on"
        t_line "your journey?"
        t_para "I remain dedicated"
        t_line "to my training."
        t_para "Oooooaaarrrgh!"
        t_done )
};
const txt_cmd_s KenjiCallMeBackAnotherTimeText[] = {
    text_start("I'm in training"
        t_line "now. I apologize,"
        t_para "but call me back"
        t_line "another time."
        t_para "Oooooaaarrrgh!"
        t_done )
};
const txt_cmd_s KenjiIllHaveTimeToChatTomorrowText[] = {
    text_start("I apologize, but I"
        t_line "don't have time to"
        t_para "chat while I am in"
        t_line "training!"
        t_para "I'll have time to"
        t_line "chat tomorrow!"
        t_para "Yiiihah!"
        t_done )
};
const txt_cmd_s KenjiHangUpMorningText[] = {
    text_start("I plan to take a"
        t_line "lunch break, so"
        t_para "come see me then!"
        t_line "Ayiiiyah!"
        t_done )
};
const txt_cmd_s KenjiTakingABreakText[] = {
    text_start("I'm taking a break"
        t_line "on ROUTE 45!"
        t_para "Why not drop by if"
        t_line "you are free?"
        t_done )
};
const txt_cmd_s KenjiHangUpNightText[] = {
    text_start("I rested up over"
        t_line "my lunch break."
        t_para "Now it's time to"
        t_line "resume training!"
        t_para "Oooryaah!"
        t_done )
};

//// liz_caller.c

const txt_cmd_s LizMonAlwaysWantsToNuzzleText[] = {
    text_start("Oh, you have to"
        t_line "hear this."
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is"
        t_line "so adorable!"
        t_para "It always wants to"
        t_line "nuzzle me!"
        t_done )
};
const txt_cmd_s LizDefeatedMonText[] = {
    text_start("And, and! Um…"
        t_para "We beat a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" with"
        t_para "just one hit a"
        t_line "little while ago."
        t_para "We felt sorry for"
        t_line "it, though."
        t_done )
};
const txt_cmd_s LizLostAMonText[] = {
    text_start("And, and! Uh…"
        t_para "We just saw a"
        t_line "really gorgeous"
        t_cont "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "But I was on the"
        t_line "phone, so it got"
        t_para "away. It made us"
        t_line "really angry!"
        t_done )
};
const txt_cmd_s LizBattleRematchText[] = {
    text_start("Hi! Do you have"
        t_line "some free time?"
        t_para "I've got all sorts"
        t_line "of time. If you're"
        t_para "free, would you"
        t_line "like to battle?"
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "Let me know when"
        t_line "you get here!"
        t_done )
};
const txt_cmd_s LizWrongNumberText[] = {
    text_start("Hi, TANIA. How are"
        t_line "you? This is LIZ."
        t_para "I'm fine, but I'm"
        t_line "bored silly!"
        t_para "Huh… Wrong number?"
        t_line "Oops! Sorry!"
        t_done )
};
const txt_cmd_s LizHangUpText[] = {
    text_start("OK, I'll call you"
        t_line "later!"
        t_done )
};
const txt_cmd_s LizRuinsOfAlphGossipText[] = {
    text_start("Listen, listen!"
        t_para "I was listening to"
        t_line "the radio in the"
        t_para "RUINS OF ALPH when"
        t_line "an odd broadcast"
        t_para "suddenly cut it on"
        t_line "the regular show."
        t_para "I wonder what it"
        t_line "was. So strange!"
        t_done )
};
const txt_cmd_s LizFalknerGossipText[] = {
    text_start("Listen, listen!"
        t_para "Don't you think"
        t_line "FALKNER of VIOLET"
        t_para "GYM is cool and"
        t_line "handsome?"
        t_para "But they say his"
        t_line "dad, who's out"
        t_para "training on the"
        t_line "road, is even more"
        t_para "cool and handsome"
        t_line "than FALKNER."
        t_para "I wish I could"
        t_line "meet him!"
        t_done )
};
const txt_cmd_s LizEarlGossipText[] = {
    text_start("Listen, listen!"
        t_para "Do you know EARL,"
        t_line "the teacher who"
        t_para "runs the #MON"
        t_line "ACADEMY in VIOLET?"
        t_para "I saw him doing"
        t_line "pirouettes while"
        t_para "he was running. It"
        t_line "was wildly funny!"
        t_done )
};
const txt_cmd_s LizSurfPikachuGossipText[] = {
    text_start("Listen, listen!"
        t_para "I collect #MON"
        t_line "plush dolls."
        t_para "But I can't seem"
        t_line "to get a hold of a"
        t_para "SURF PIKACHU DOLL."
        t_line "None of my friends"
        t_para "have it. It must"
        t_line "be totally rare!"
        t_para "You could really"
        t_line "brag about it if"
        t_cont "you had one."
        t_done )
};
const txt_cmd_s LizMooMooMilkGossipText[] = {
    text_start("Listen, listen!"
        t_para "Do you know about"
        t_line "MOOMOO MILK?"
        t_para "You can buy it at"
        t_line "MOOMOO FARM."
        t_para "It's supposed to"
        t_line "be good for health"
        t_para "and beauty."
        t_line "I really want to"
        t_para "try some. I bet"
        t_line "it's delicious!"
        t_done )
};
const txt_cmd_s LizSalonGossipText[] = {
    text_start("Listen, listen!"
        t_para "There's a #MON"
        t_line "SALON in GOLDENROD"
        t_para "that's run by two"
        t_line "brothers."
        t_para "The older brother"
        t_line "is good, but the"
        t_para "younger one really"
        t_line "isn't."
        t_para "But sometimes the"
        t_line "younger one does a"
        t_para "better job than"
        t_line "his brother."
        t_para "Every time I go, I"
        t_line "have a hard time"
        t_para "trying to decide"
        t_line "whom I should use…"
        t_done )
};
const txt_cmd_s LizWhitneyGossipText[] = {
    text_start("Listen, listen!"
        t_para "GOLDENROD GYM's"
        t_line "WHITNEY began"
        t_para "battling only a"
        t_line "little while ago!"
        t_para "But the #MON"
        t_line "LEAGUE chose her"
        t_cont "as a GYM LEADER!"
        t_para "I bet she must be"
        t_line "totally talented."
        t_done )
};
const txt_cmd_s LizBugCatchingContestGossipText[] = {
    text_start("Listen, listen!"
        t_para "Have you ever"
        t_line "taken part in a"
        t_para "Bug-Catching"
        t_line "Contest at the"
        t_cont "NATIONAL PARK?"
        t_para "I did once, but"
        t_line "all I could catch"
        t_cont "was a CATERPIE."
        t_para "But guess what!"
        t_para "I won with that"
        t_line "CATERPIE. Isn't"
        t_cont "that great?"
        t_done )
};
const txt_cmd_s LizBeautifulTrainerGossipText[] = {
    text_start("Listen, listen!"
        t_para "I saw a beautiful"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_para "I wish I could"
        t_line "become a beautiful"
        t_cont "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" too."
        t_done )
};
const txt_cmd_s LizForgotGossipText[] = {
    text_start("Listen, listen!"
        t_para "Uh… Um… Whoops!"
        t_para "I forgot what I"
        t_line "was going to say!"
        t_done )
};
const txt_cmd_s LizFawningOverMonText[] = {
    text_start("Listen, listen!"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("…"
        t_line "it… so pretty…"
        t_para "and… giggle… so"
        t_line "awesome… yes… but…"
        t_para "very much… eeek!"
        t_line "And… lovely…"
        t_para "Just ravishing…"
        t_line "Oh, too much!"
        t_para "…Hug it… sleeping…"
        t_line "That's right…"
        t_para "pretty… sigh… So"
        t_line "nice… Cute…"
        t_para "…Oops! Look at the"
        t_line "time! I chatted"
        t_cont "too long!"
        t_para "I'm sorry I took"
        t_line "so much of your"
        t_para "time!"
        t_line "I love chatting!"
        t_done )
};
const txt_cmd_s LizReminderText[] = {
    text_start("I've got too much"
        t_line "time on my hands!"
        t_para "Let's battle right"
        t_line "away!"
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};

//// parry_caller.c

const txt_cmd_s ParryNothingCanMatchText[] = {
    text_start("Nothing can match"
        t_line "my @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" now."
        t_done )
};
const txt_cmd_s ParryDefeatedMonText[] = {
    text_start("Yeah, we KO'd a"
        t_line "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_para "That was OK, but I"
        t_line "wanted to get it…"
        t_done )
};
const txt_cmd_s ParryLostAMonText[] = {
    text_start("And yesterday, we"
        t_line "spotted a wild"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_line "We were debating"
        t_para "whether to catch"
        t_line "it or beat it."
        t_para "When along came"
        t_line "another guy who"
        t_para "caught it!"
        t_line "How about that!"
        t_done )
};
const txt_cmd_s ParryBattleRematchText[] = {
    text_start("You're thinking"
        t_line "you'd like to"
        t_para "battle me. Am I"
        t_line "right or what?"
        t_para "Yep! We'll meet on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s ParryHangUpText[] = {
    text_start("OK, give me a call"
        t_line "again!"
        t_done )
};
const txt_cmd_s ParryBattleWithMeText[] = {
    text_start("You'll battle with"
        t_line "me again, right?"
        t_done )
};
const txt_cmd_s ParryHaventYouGottenToText[] = {
    text_start("Haven't you gotten"
        t_line "to @")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("?"
        t_para "Waiting here isn't"
        t_line "bad, but I'd sure"
        t_cont "like to battle!"
        t_done )
};

//// ralph_caller.c

const txt_cmd_s RalphNeglectingKidsText[] = {
    text_start("I've been spending"
        t_line "more time with my"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" than I"
        t_line "have with my kids."
        t_para "That's a bit sad,"
        t_line "actually."
        t_done )
};
const txt_cmd_s RalphDefeatedMonText[] = {
    text_start("I just beat a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "I told my kid, but"
        t_line "he scoffed that he"
        t_para "could do the same"
        t_line "thing easily."
        t_para "Boy, has he gotten"
        t_line "cocky…"
        t_done )
};
const txt_cmd_s RalphLostAMonText[] = {
    text_start("Yesterday a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" slipped"
        t_para "away from me, in"
        t_line "front of my kid."
        t_para "I was feeling down"
        t_line "about it until he"
        t_para "shared his #"
        t_line "BALLS with me."
        t_para "Hahah, that sure"
        t_line "made my day!"
        t_done )
};
const txt_cmd_s RalphBattleRematchText[] = {
    text_start("What do you say to"
        t_line "a battle with me?"
        t_para "Good, you're going"
        t_line "to do it!"
        t_para "For a kid, you're"
        t_line "quite agreeable."
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(" is"
        t_line "the spot!"
        t_done )
};
const txt_cmd_s RalphHangUpText[] = {
    text_start("You call your mom"
        t_line "sometimes too!"
        t_done )
};
const txt_cmd_s RalphItemText[] = {
    text_start("Listen, I… Yowch!"
        t_para "Uh, sorry! See,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" are"
        t_para "biting like there"
        t_line "is no tomorrow"
        t_para "over here on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_para "Aiyee! Ouch!"
        t_line "One jabbed me!"
        t_para "Heh, they're some"
        t_line "kind of feisty!"
        t_para "<PLAY_G>, you have"
        t_line "to see this rare"
        t_para "sight! Get ready"
        t_line "to fish!"
        t_done )
};
const txt_cmd_s RalphNoItemText[] = {
    text_start("Yeah, I know."
        t_para "You're looking for"
        t_line "rare #MON."
        t_para "Recently, all I've"
        t_line "been catching are"
        t_cont "MAGIKARP, though…"
        t_done )
};
const txt_cmd_s RalphReminderText[] = {
    text_start("So where are you?"
        t_line "I'm waiting for"
        t_para "you to show up on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "You shouldn't make"
        t_line "your elders wait!"
        t_done )
};
const txt_cmd_s RalphHurryText[] = {
    text_start("Hey, what's the"
        t_line "matter with you?"
        t_para "Aren't you coming"
        t_line "over to fish for"
        t_cont "QWILFISH?"
        t_para "I'm on ROUTE 32,"
        t_line "so hurry up!"
        t_done )
};

//// reena_caller.c

const txt_cmd_s ReenaMonsIsAPerfectMatchText[] = {
    text_start("Listen, dear…"
        t_para "Do you recall my"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("?"
        t_para "Yes, exactly. That"
        t_line "lovely @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "Wouldn't you agree"
        t_line "it's a perfect"
        t_cont "match for me?"
        t_done )
};
const txt_cmd_s ReenaDefeatedMonText[] = {
    text_start("Have I ever faced"
        t_line "a wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("?"
        t_para "You need to ask?"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" I've"
        t_line "beaten on numerous"
        t_cont "occasions!"
        t_done )
};
const txt_cmd_s ReenaLostAMonText[] = {
    text_start("Have I ever failed"
        t_line "to catch a wild"
        t_cont "#MON?"
        t_para "You need to ask?"
        t_para "I would never fail"
        t_line "to catch a wild"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("…"
        t_line "Oh! Never mind!"
        t_done )
};
const txt_cmd_s ReenaBattleRematchText[] = {
    text_start("We are going to"
        t_line "battle!"
        t_para "The place shall be"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_para "Don't make me"
        t_line "wait! Got it?"
        t_done )
};
const txt_cmd_s ReenaHangUpText[] = {
    text_start("Fine, you may go."
        t_done )
};
const txt_cmd_s ReenaForwardText[] = {
    text_start("Don't be too proud"
        t_line "just because you"
        t_para "happened to beat"
        t_line "me… "
        t_para "It was a fluke!"
        t_done )
};
const txt_cmd_s ReenaHurryText[] = {
    text_start("What are you"
        t_line "doing?"
        t_para "I told you that"
        t_line "the place was"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_line "Don't try to run!"
        t_done )
};

//// tiffany_caller.c

const txt_cmd_s TiffanyMonIsAdorableText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "adorable, don't"
        t_para "you think so?"
        t_line "I always sleep"
        t_para "with it--it's so"
        t_line "fluffy and warm!"
        t_done )
};
const txt_cmd_s TiffanyDefeatedMonText[] = {
    text_start("Oh, and we had to"
        t_line "battle a wild"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" a while"
        t_line "ago…"
        t_para "My CLEFAIRY came"
        t_line "close to fainting!"
        t_para "Isn't that awful?"
        t_para "I hate those nasty"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_done )
};
const txt_cmd_s TiffanyLostAMonText[] = {
    text_start("Oh, and we had to"
        t_line "battle a wild"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" a while"
        t_line "ago…"
        t_para "My CLEFAIRY got"
        t_line "frightened, so we"
        t_para "ran away as fast"
        t_line "as we could!"
        t_para "I just can't help"
        t_line "feeling protective"
        t_cont "of my CLEFAIRY."
        t_done )
};
const txt_cmd_s TiffanyBattleRematchText[] = {
    text_start("I know this might"
        t_line "surprise you, but"
        t_para "would you like to"
        t_line "battle?"
        t_para "I'll be waiting"
        t_line "with CLEFAIRY on"
        t_cont "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s TiffanyItsAwfulText[] = {
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_para "It's awful."
        t_line "My CLEFAIRY…"
        t_para "Huh? <PLAY_G>?"
        t_para "Oh, sorry! I was"
        t_line "in a hurry, and I…"
        t_para "I have to go!"
        t_line "Bye-bye!"
        t_done )
};
const txt_cmd_s TiffanyHangUpText[] = {
    text_start("Bye-bye!"
        t_done )
};
const txt_cmd_s TiffanyFoundItemText[] = {
    text_start("I bought some PINK"
        t_line "BOWS at GOLDENROD"
        t_para "DEPT.STORE for my"
        t_line "CLEFAIRY."
        t_para "I got too many, so"
        t_line "I'll give you one!"
        t_para "Come collect it on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s TiffanyNoItemText[] = {
    text_start("I love dressing up"
        t_line "my CLEFAIRY!"
        t_done )
};
const txt_cmd_s TiffanyAsleepText[] = {
    text_start("What's wrong?"
        t_line "Can't you visit?"
        t_para "CLEFAIRY got tired"
        t_line "and fell asleep."
        t_para "I'm not sure if I"
        t_line "can wake it up…"
        t_para "Please hurry to"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};
const txt_cmd_s TiffanyHurryText[] = {
    text_start("What's wrong?"
        t_line "Can't you visit?"
        t_para "I'm sure this will"
        t_line "look good on your"
        t_cont "CLEFAIRY."
        t_para "Please hurry to"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_done )
};

//// todd_caller.c

const txt_cmd_s ToddLooksCuteLikeMeText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is"
        t_line "looking more and"
        t_para "more like me. It's"
        t_line "getting cuter!"
        t_done )
};
const txt_cmd_s ToddDefeatedMonText[] = {
    text_start("And, you know?"
        t_para "Now we can KO"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" easily."
        t_para "I should challenge"
        t_line "the GOLDENROD GYM."
        t_done )
};
const txt_cmd_s ToddLostAMonText[] = {
    text_start("And, you know?"
        t_line "We just failed to"
        t_para "beat @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" by"
        t_line "a tiny margin."
        t_para "I'm guessing my"
        t_line "#MON's levels"
        t_para "aren't high enough"
        t_line "yet…"
        t_done )
};
const txt_cmd_s ToddBattleRematchText[] = {
    text_start("You must be a lot"
        t_line "better now, huh?"
        t_para "How about showing"
        t_line "me your technique"
        t_para "in a real battle"
        t_line "with me?"
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s ToddHangUpText[] = {
    text_start("See you later!"
        t_done )
};
const txt_cmd_s ToddDepartmentStoreBargainSaleText[] = {
    text_start("This is it--the"
        t_line "one we've all been"
        t_cont "waiting for!"
        t_para "GOLDENROD DEPT."
        t_line "STORE's bargain"
        t_cont "sale is on now!"
        t_para "Want it cheap?"
        t_line "Want it lots?"
        t_para "Don't miss this"
        t_line "GOLDENROD chance!"
        t_para "Huh? I sound like"
        t_line "a huckster?"
        t_para "Well, yeah. I was"
        t_line "mimicking them…"
        t_para "Anyway, you've got"
        t_line "to get there as"
        t_cont "soon as you can!"
        t_done )
};
const txt_cmd_s ToddSavingUpForBargainSaleText[] = {
    text_start("I'm saving up for"
        t_line "the next bargain"
        t_para "sale. When's the"
        t_line "next one?"
        t_done )
};
const txt_cmd_s ToddLookingForwardToBattleText[] = {
    text_start("Where are you?"
        t_para "Let's have our"
        t_line "battle soon!"
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s ToddHaveYouGoneToDepartmentStoreText[] = {
    text_start("Haven't you gone"
        t_line "to GOLDENROD DEPT."
        t_para "STORE? I've scoped"
        t_line "it out already!"
        t_para "They had some real"
        t_line "bargains."
        t_para "You should get"
        t_line "there quickly."
        t_done )
};

//// tully_caller.c

const txt_cmd_s TullyMonHasGrownText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" has"
        t_line "grown again."
        t_para "It was only about"
        t_line "so big when I"
        t_para "caught it, but now"
        t_line "it's way bigger."
        t_done )
};
const txt_cmd_s TullyDefeatedMonText[] = {
    text_start("Oh yeah, I KO'd a"
        t_line "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "It was huge, like"
        t_line "this big even."
        t_para "Heh, I guess you"
        t_line "can't tell over"
        t_cont "the phone…"
        t_done )
};
const txt_cmd_s TullyLostAMonText[] = {
    text_start("Oh yeah, I lost a"
        t_line "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "It was huge, like"
        t_line "this big even."
        t_para "Heh, I guess you"
        t_line "can't tell over"
        t_cont "the phone…"
        t_done )
};
const txt_cmd_s TullyBattleRematchText[] = {
    text_start("We should get a"
        t_line "battle going!"
        t_para "I'll be fishing on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "Swing by if you"
        t_line "have the time."
        t_done )
};
const txt_cmd_s TullyHangUpText[] = {
    text_start("Well, I'll be"
        t_line "seeing you."
        t_done )
};
const txt_cmd_s TullyFoundItemText[] = {
    text_start("I picked up a good"
        t_line "little thing at"
        t_cont "the water's edge."
        t_para "Like I promised,"
        t_line "it's yours."
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s TullyNoItemText[] = {
    text_start("Have I found"
        t_line "anything good?"
        t_para "Nope, not yet."
        t_para "It's like fishing,"
        t_line "you need patience."
        t_done )
};
const txt_cmd_s TullyForwardText[] = {
    text_start("Yup, TULLY here…"
        t_para "<PLAY_G>? What?"
        t_line "You're lost?"
        t_para "Our battle will be"
        t_line "on @")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s TullyHurryText[] = {
    text_start("I've got something"
        t_line "good for you."
        t_para "Hustle over to"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};

//// vance_caller.c

const txt_cmd_s VanceMonHasBecomeTougherText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "become tougher."
        t_para "We've achieved"
        t_line "liftoff!"
        t_done )
};
const txt_cmd_s VanceDefeatedMonText[] = {
    text_start("We can easily beat"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("!"
        t_para "…Huh? You too?"
        t_line "Isn't that great?"
        t_done )
};
const txt_cmd_s VanceLostAMonText[] = {
    text_start("But get this, a"
        t_line "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "just barely eluded"
        t_line "us."
        t_para "I wanted to FLY"
        t_line "after it…"
        t_done )
};
const txt_cmd_s VanceBattleRematchText[] = {
    text_start("Right now, I'm on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_para "You know, where I"
        t_line "first met you?"
        t_para "Want to battle?"
        t_line "I'll wait here."
        t_done )
};
const txt_cmd_s VanceHangUpText[] = {
    text_start("OK, bye for now!"
        t_done )
};
const txt_cmd_s VanceLookingForwardText[] = {
    text_start("I'll be looking"
        t_line "forward to our"
        t_cont "next battle!"
        t_done )
};
const txt_cmd_s VanceHurryHurryText[] = {
    text_start("Oh, <PLAY_G>!"
        t_line "Hurry, hurry!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("!"
        t_line "FLY over now!"
        t_done )
};

//// wade_caller.c

const txt_cmd_s WadeAreYourMonGrowingText[] = {
    text_start("Are your #MON"
        t_line "growing?"
        t_para "My #MON are"
        t_line "growing a bit too"
        t_para "quickly for me."
        t_line "It's overwhelming!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s grow-"
        t_line "ing especially"
        t_para "quickly. I think"
        t_line "it'll get tough."
        t_done )
};
const txt_cmd_s WadeDefeatedMonText[] = {
    text_start("Oh yeah, we KO'd a"
        t_line "wild @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "with one hit a"
        t_line "while back."
        t_para "It went down so"
        t_line "easily, I felt a"
        t_para "little sorry for"
        t_line "the poor thing."
        t_done )
};
const txt_cmd_s WadeLostAMonText[] = {
    text_start("Oh yeah, a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" got"
        t_para "away from me at"
        t_line "the last second."
        t_para "I know it's a"
        t_line "common #MON…"
        t_para "But it does annoy"
        t_line "me that it got"
        t_para "away when I almost"
        t_line "had it."
        t_done )
};
const txt_cmd_s WadeBattleRematchText[] = {
    text_start("Do you feel like a"
        t_line "#MON battle?"
        t_para "It won't be like"
        t_line "last time!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("'s"
        t_line "where I'll be."
        t_para "Let me know when"
        t_line "you get there."
        t_done )
};
const txt_cmd_s WadeHangUpText[] = {
    text_start("See you later!"
        t_done )
};
const txt_cmd_s WadeBugCatchingContestText[] = {
    text_start("The Bug-Catching"
        t_line "Contest is at the"
        t_para "NATIONAL PARK"
        t_line "today."
        t_para "Are you going,"
        t_line "<PLAY_G>?"
        t_para "I'm trying to make"
        t_line "up my mind."
        t_done )
};
const txt_cmd_s WadeFoundItemText[] = {
    text_start("I found all kinds"
        t_line "of BERRIES. If you"
        t_para "want, I'll share"
        t_line "some with you."
        t_para "I'll be waiting on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s WadeNoBerriesText[] = {
    text_start("Huh? BERRIES?"
        t_para "Sorry, I haven't"
        t_line "found any yet."
        t_para "I'll call you if I"
        t_line "find any. Will you"
        t_cont "please wait?"
        t_done )
};
const txt_cmd_s WadeQuickBattleText[] = {
    text_start("Let's battle"
        t_line "already!"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(" is"
        t_line "where I am."
        t_para "Please get here as"
        t_line "soon as you can!"
        t_done )
};
const txt_cmd_s WadeComeQuickText[] = {
    text_start("How come you're"
        t_line "not here yet?"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(" is"
        t_line "where I am."
        t_para "Please get here as"
        t_line "soon as you can!"
        t_done )
};

//// wilton_caller.c

const txt_cmd_s WiltonMonHasGrownText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "grown impressive!"
        t_para "My fishing skills"
        t_line "have improved too!"
        t_done )
};
const txt_cmd_s WiltonDefeatedMonText[] = {
    text_start("We beat a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("…"
        t_para "You know, I have"
        t_line "more fun fishing"
        t_para "than beating wild"
        t_line "#MON."
        t_done )
};
const txt_cmd_s WiltonLostAMonText[] = {
    text_start("But a while back,"
        t_line "we came this close"
        t_para "to landing a wild"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_para "I tell you, it was"
        t_line "huge. Believe me."
        t_done )
};
const txt_cmd_s WiltonBattleRematchText[] = {
    text_start("I'm fishing on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start(","
        t_para "but nothing's"
        t_line "biting today."
        t_para "Help me while my"
        t_line "time away, come"
        t_cont "over for a battle."
        t_done )
};
const txt_cmd_s WiltonHangUpText[] = {
    text_start("All right, later."
        t_done )
};
const txt_cmd_s WiltonFoundItemText[] = {
    text_start("I snagged an item"
        t_line "while fishing."
        t_para "Come pick it up on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("."
        t_done )
};
const txt_cmd_s WiltonHaventFoundAnythingText[] = {
    text_start("Nah, I haven't"
        t_line "found anything"
        t_para "that's worth your"
        t_line "time."
        t_para "You have to have"
        t_line "patience."
        t_done )
};
const txt_cmd_s WiltonNotBitingText[] = {
    text_start("Sigh…"
        t_line "They're not biting"
        t_para "like before on"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("…"
        t_para "You have to come"
        t_line "for a battle!"
        t_done )
};
const txt_cmd_s WiltonWantThisText[] = {
    text_start("Don't you want"
        t_line "this item?"
        t_para "Hah? You don't"
        t_line "know where?"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer5))
    text_start("…"
        t_line "Just head from"
        t_para "MAHOGANY toward"
        t_line "BLACKTHORN!"
        t_done )
};

