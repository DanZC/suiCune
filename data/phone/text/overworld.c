#include "../../../constants.h"
#include "overworld.h"

//// alan_overworld.c
const txt_cmd_s AlanAskNumber1Text[] = {
    text_start("Reading textbooks"
        t_line "is worthwhile"
        t_cont "every so often."
        t_para "When I'm reading"
        t_line "and walking, I"
        t_cont "have to look down."
        t_para "So I notice items"
        t_line "on the ground."
        t_para "Next time I find"
        t_line "something, I'll"
        t_cont "give it to you."
        t_para "May I have your"
        t_line "phone number?"
        t_done )
};
const txt_cmd_s AlanAskNumber2Text[] = {
    text_start("If I find some-"
        t_line "thing, it's yours."
        t_para "So may I have your"
        t_line "phone number?"
        t_done )
};
const txt_cmd_s AlanNumberAcceptedText[] = {
    text_start("I'll call you as"
        t_line "soon as I find"
        t_para "something. You can"
        t_line "count on it!"
        t_done )
};
const txt_cmd_s AlanNumberDeclinedText[] = {
    text_start("Oh… I thought it"
        t_line "would be a good"
        t_para "break to call you"
        t_line "when I'm studying…"
        t_done )
};
const txt_cmd_s AlanPhoneFullText[] = {
    text_start("There's no room"
        t_line "for my number."
        t_done )
};
const txt_cmd_s AlanRematchText[] = {
    text_start("I waited around"
        t_line "for you!"
        t_para "I'm thoroughly"
        t_line "prepared today!"
        t_done )
};
const txt_cmd_s AlanGiftText[] = {
    text_start("This, this! This"
        t_line "is yours! Ta-da!"
        t_done )
};
const txt_cmd_s AlanPackFullText[] = {
    text_start("Whoops!"
        t_para "You can't carry"
        t_line "any more items!"
        t_para "I'll hold it until"
        t_line "next time."
        t_done )
};

//// anthony_overworld.c
const txt_cmd_s AnthonyAskNumber1Text[] = {
    text_start("By the way, I'm a"
        t_line "HIKER, so I often"
        t_para "go to mountains"
        t_line "and caves."
        t_para "I occasionally see"
        t_line "rare #MON."
        t_para "I could call you"
        t_line "the next time I"
        t_cont "see one."
        t_para "Feel like swapping"
        t_line "phone numbers?"
        t_done )
};
const txt_cmd_s AnthonyAskNumber2Text[] = {
    text_start("I could call you"
        t_line "when I see some"
        t_cont "rare #MON."
        t_para "Feel like swapping"
        t_line "phone numbers?"
        t_done )
};
const txt_cmd_s AnthonyNumberAcceptedText[] = {
    text_start("Be patient. I'll"
        t_line "find some rare"
        t_cont "#MON for you!"
        t_done )
};
const txt_cmd_s AnthonyNumberDeclinedText[] = {
    text_start("You're cold. I may"
        t_line "as well head to"
        t_cont "the mountains…"
        t_done )
};
const txt_cmd_s AnthonyPhoneFullText[] = {
    text_start("Your phone's full."
        t_para "It can't register"
        t_line "my phone number."
        t_done )
};
const txt_cmd_s AnthonyRematchText[] = {
    text_start("All righty, then!"
        t_para "My #MON and I"
        t_line "are raring to go!"
        t_done )
};

//// arnie_overworld.c
const txt_cmd_s ArnieAskNumber1Text[] = {
    text_start("Do you get the"
        t_line "feeling that there"
        t_para "are more rare"
        t_line "#MON around?"
        t_para "I'm positive there"
        t_line "are, so I look all"
        t_cont "the time."
        t_para "If I find one, I"
        t_line "want to share the"
        t_para "good news with"
        t_line "everyone I know."
        t_para "I know! Give me"
        t_line "your phone number."
        t_done )
};
const txt_cmd_s ArnieAskNumber2Text[] = {
    text_start("I want to let"
        t_line "people know if I"
        t_cont "see rare #MON."
        t_para "Please give me"
        t_line "your phone number!"
        t_done )
};
const txt_cmd_s ArnieNumberAcceptedText[] = {
    text_start("If I spot any"
        t_line "awesome #MON,"
        t_para "I'll be sure to"
        t_line "give you a call!"
        t_done )
};
const txt_cmd_s ArnieNumberDeclinedText[] = {
    text_start("Aww! I want to"
        t_line "tell someone about"
        t_cont "my discoveries!"
        t_done )
};
const txt_cmd_s ArniePhoneFullText[] = {
    text_start("There's no space"
        t_line "for my number."
        t_para "If you make room,"
        t_line "register me!"
        t_done )
};
const txt_cmd_s ArnieRematchText[] = {
    text_start("It's my turn to"
        t_line "win now!"
        t_para "I've turned over a"
        t_line "new leaf!"
        t_done )
};

//// beth_overworld.c
const txt_cmd_s BethAskNumber1Text[] = {
    text_start("It's been a while"
        t_line "since I lost…"
        t_para "You're very good"
        t_line "at battling."
        t_para "We should battle"
        t_line "again sometime."
        t_para "By challenging a"
        t_line "tough trainer like"
        t_para "you, I think I can"
        t_line "get better too."
        t_para "So how about it?"
        t_para "Would you give me"
        t_line "your phone number?"
        t_done )
};
const txt_cmd_s BethAskNumber2Text[] = {
    text_start("By challenging a"
        t_line "tough trainer like"
        t_para "you, I think I can"
        t_line "get better too."
        t_para "So how about it?"
        t_para "Would you give me"
        t_line "your phone number?"
        t_done )
};
const txt_cmd_s BethNumberAcceptedText[] = {
    text_start("Let's battle again"
        t_line "sometime!"
        t_done )
};
const txt_cmd_s BethNumberDeclinedText[] = {
    text_start("That's too bad…"
        t_para "Let me know if you"
        t_line "change your mind."
        t_done )
};
const txt_cmd_s BethPhoneFullText[] = {
    text_start("Oh no. Your phone"
        t_line "is out of memory."
        t_done )
};
const txt_cmd_s BethRematchText[] = {
    text_start("You sure kept me"
        t_line "waiting! Let's go!"
        t_done )
};

//// beverly_overworld.c
const txt_cmd_s BeverlyAskNumber1Text[] = {
    text_start("Your MARILL is so"
        t_line "cute and adorable!"
        t_para "You love #MON"
        t_line "just like I do!"
        t_para "Want to trade"
        t_line "phone numbers?"
        t_para "Let's chat! It'll"
        t_line "be so much fun!"
        t_done )
};
const txt_cmd_s BeverlyAskNumber2Text[] = {
    text_start("Your MARILL is so"
        t_line "cute and adorable!"
        t_para "We should chat, it"
        t_line "will be fun."
        t_para "Can I have your"
        t_line "phone number?"
        t_done )
};
const txt_cmd_s BeverlyNumberAcceptedText[] = {
    text_start("To be honest, I"
        t_line "want a MARILL."
        t_para "But I make do with"
        t_line "my cute SNUBBULL."
        t_done )
};
const txt_cmd_s BeverlyNumberDeclinedText[] = {
    text_start("Oh… That's"
        t_line "disappointing…"
        t_para "Goodbye, MARILL…"
        t_done )
};
const txt_cmd_s BeverlyPhoneFullText[] = {
    text_start("Oh? Your phone's"
        t_line "memory is full."
        t_done )
};
const txt_cmd_s BeverlyGiftText[] = {
    text_start("Oh? <PLAYER>? "
        t_line "I waited here for"
        t_para "you. I brought you"
        t_line "a little gift."
        t_done )
};
const txt_cmd_s BeverlyPackFullText[] = {
    text_start("Oh?"
        t_line "You have no room."
        t_para "Please come back"
        t_line "for it later."
        t_done )
};

//// brent_overworld.c
const txt_cmd_s BrentAskNumber1Text[] = {
    text_start("By the way, you're"
        t_line "a #MANIAC…"
        t_para "I can tell."
        t_line "Yes, you are."
        t_para "But your knowledge"
        t_line "is shallow still!"
        t_para "Do you know BILL?"
        t_line "He's an incredible"
        t_para "#MANIAC."
        t_line "I revere him."
        t_para "I'll teach you all"
        t_line "I know about BILL,"
        t_para "so leave me your"
        t_line "phone number."
        t_done )
};
const txt_cmd_s BrentAskNumber2Text[] = {
    text_start("I'll teach you all"
        t_line "I know about BILL,"
        t_para "so leave me your"
        t_line "phone number."
        t_done )
};
const txt_cmd_s BrentNumberAcceptedText[] = {
    text_start("BILL--he's more"
        t_line "than amazing!"
        t_para "To be a #MANIAC"
        t_line "like him someday…"
        t_para "That's my dream."
        t_done )
};
const txt_cmd_s BrentNumberDeclinedText[] = {
    text_start("You're going to"
        t_line "regret it…"
        t_para "And I won't care…"
        t_done )
};
const txt_cmd_s BrentPhoneFullText[] = {
    text_start("Huh? Your phone"
        t_line "list's full."
        t_para "A #MANIAC has"
        t_line "to be more tidy!"
        t_done )
};
const txt_cmd_s BrentRematchText[] = {
    text_start("I've been waiting."
        t_para "Look, check out my"
        t_line "#MON!"
        t_done )
};

//// chad_overworld.c
const txt_cmd_s ChadAskNumber1Text[] = {
    text_start("Huh? Is that thing"
        t_line "a #DEX? Have"
        t_cont "you met PROF.OAK?"
        t_para "Huh? You have? "
        t_line "That's way cool!"
        t_para "I have a dream of"
        t_line "becoming a #MON"
        t_para "researcher like"
        t_line "PROF.OAK."
        t_para "May I please have"
        t_line "your phone number?"
        t_para "We should chat"
        t_line "about PROF.OAK."
        t_para "I'm sure it will"
        t_line "be loads of fun!"
        t_done )
};
const txt_cmd_s ChadAskNumber2Text[] = {
    text_start("May I please have"
        t_line "your phone number?"
        t_para "We should chat"
        t_line "about PROF.OAK."
        t_para "I'm sure it will"
        t_line "be loads of fun!"
        t_done )
};
const txt_cmd_s ChadNumberAcceptedText[] = {
    text_start("You must listen to"
        t_line "PROF.OAK'S #MON"
        t_cont "TALK, right?"
        t_done )
};
const txt_cmd_s ChadNumberDeclinedText[] = {
    text_start("Oh… I wish I had a"
        t_line "chance to meet"
        t_cont "PROF.OAK…"
        t_done )
};
const txt_cmd_s ChadPhoneFullText[] = {
    text_start("Your phone list is"
        t_line "completely full!"
        t_done )
};
const txt_cmd_s ChadRematchText[] = {
    text_start("I've been waiting!"
        t_line "Let's battle now!"
        t_done )
};

//// dana_overworld.c
const txt_cmd_s DanaAskNumber1Text[] = {
    text_start("You're really good"
        t_line "at #MON!"
        t_para "Boys give me items"
        t_line "after battles, but"
        t_para "sometimes they"
        t_line "give me too much."
        t_para "Next time, I can"
        t_line "share some if you"
        t_para "want. Let me get"
        t_line "your phone number."
        t_done )
};
const txt_cmd_s DanaAskNumber2Text[] = {
    text_start("I'll share my"
        t_line "gifts with you."
        t_para "Let me get your"
        t_line "phone number."
        t_done )
};
const txt_cmd_s DanaNumberAcceptedText[] = {
    text_start("Next time a boy"
        t_line "gives me something"
        t_para "after a battle,"
        t_line "I'll share some!"
        t_para "Does that make me"
        t_line "bad?"
        t_done )
};
const txt_cmd_s DanaNumberDeclinedText[] = {
    text_start("Aww, you don't"
        t_line "want anything?"
        t_para "But it's all for"
        t_line "free…"
        t_done )
};
const txt_cmd_s DanaPhoneFullText[] = {
    text_start("But your phone's"
        t_line "out of memory!"
        t_done )
};
const txt_cmd_s DanaRematchText[] = {
    text_start("You're really"
        t_line "late!"
        t_para "I'm eager to get"
        t_line "going!"
        t_done )
};
const txt_cmd_s DanaGiftText[] = {
    text_start("Hi! Are you here"
        t_line "for your gift?"
        t_para "This should really"
        t_line "make your day!"
        t_done )
};
const txt_cmd_s DanaPackFullText[] = {
    text_start("Where are you"
        t_line "going to put this?"
        t_para "I'll keep it, so"
        t_line "come get it later!"
        t_done )
};

//// derek_overworld.c
const txt_cmd_s DerekAskNumber1Text[] = {
    text_start("Oh, wow! PIKACHU!"
        t_line "It's so soft and"
        t_cont "furry! How cute!"
        t_para "Let's be friends!"
        t_line "PIKACHU-lovers are"
        t_cont "never bad people!"
        t_para "Let's chat about"
        t_line "PIKACHU!"
        t_para "Can I get your"
        t_line "phone number?"
        t_done )
};
const txt_cmd_s DerekAskNumber2Text[] = {
    text_start("Let's chat about"
        t_line "PIKACHU!"
        t_para "Can I get your"
        t_line "phone number?"
        t_done )
};
const txt_cmd_s DerekNumberAcceptedText[] = {
    text_start("PIKACHU is the"
        t_line "one! If anything"
        t_para "comes up, I'll"
        t_line "give you a jingle."
        t_done )
};
const txt_cmd_s DerekNumberDeclinedText[] = {
    text_start("You…"
        t_para "I bet you don't"
        t_line "even like PIKACHU…"
        t_done )
};
const txt_cmd_s DerekPhoneFullText[] = {
    text_start("Wait a sec! Your"
        t_line "phone list's full!"
        t_done )
};
const txt_cmd_s DerekGiftText[] = {
    text_start("I've been looking"
        t_line "for you! Here, see"
        t_cont "this? This is it!"
        t_para "I'm certain your"
        t_line "PIKACHU will love"
        t_cont "my gift too!"
        t_done )
};
const txt_cmd_s DerekPackFullText[] = {
    text_start("Uh-oh, too bad."
        t_line "You don't have any"
        t_para "room. Be sure to"
        t_line "get it later."
        t_done )
};

//// erin_overworld.c
const txt_cmd_s ErinAskNumber1Text[] = {
    text_start("It really made me"
        t_line "angry to lose."
        t_para "I'll have to train"
        t_line "much harder…"
        t_para "Here's my number."
        t_line "I'm ERIN--don't"
        t_para "forget! Want to"
        t_line "battle me again?"
        t_done )
};
const txt_cmd_s ErinAskNumber2Text[] = {
    text_start("I want to battle"
        t_line "with you again."
        t_para "Do you want to"
        t_line "exchange numbers?"
        t_done )
};
const txt_cmd_s ErinNumberAcceptedText[] = {
    text_start("I'll remember to"
        t_line "call when I want"
        t_cont "to battle again!"
        t_done )
};
const txt_cmd_s ErinNumberDeclinedText[] = {
    text_start("Oh… I'm sad…"
        t_line "If you do want to"
        t_para "battle, come see"
        t_line "ERIN--that's me!"
        t_done )
};
const txt_cmd_s ErinPhoneFullText[] = {
    text_start("Oh no. Your phone"
        t_line "is all filled up."
        t_done )
};
const txt_cmd_s ErinRematchText[] = {
    text_start("Yay! I waited!"
        t_line "Let's start now!"
        t_done )
};
const txt_cmd_s ErinPackFullText[] = {
    text_start("That's too bad!"
        t_line "You have no room…"
        t_para "I'll give it to"
        t_line "you another time."
        t_done )
};
const txt_cmd_s ErinRematchGiftText[] = {
    text_start("Aww… I lost again!"
        t_para "I wonder how many"
        t_line "times that is…"
        t_para "Thanks for coming!"
        t_line "Here's a present!"
        t_done )
};

//// gaven_overworld.c
const txt_cmd_s GavenAskNumber1Text[] = {
    text_start("Wow, you're tough."
        t_line "I haven't battled"
        t_para "that seriously in"
        t_line "a long time."
        t_para "Could I get your"
        t_line "phone number?"
        t_para "I'd like to battle"
        t_line "again when I heal"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and the"
        t_line "rest of my team."
        t_done )
};
const txt_cmd_s GavenAskNumber2Text[] = {
    text_start("Could I get your"
        t_line "phone number?"
        t_para "I'd like to battle"
        t_line "again when I heal"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and the"
        t_line "rest of my team."
        t_done )
};
const txt_cmd_s GavenNumberAcceptedText[] = {
    text_start("How should I beat"
        t_line "you? I'm tormented"
        t_para "by those thoughts"
        t_line "all the time…"
        t_done )
};
const txt_cmd_s GavenNumberDeclinedText[] = {
    text_start("OK… I understand…"
        t_line "But if you change"
        t_para "your mind, give me"
        t_line "a shout anytime."
        t_done )
};
const txt_cmd_s GavenPhoneFullText[] = {
    text_start("Your phone's"
        t_line "memory is full."
        t_para "You can't register"
        t_line "my number."
        t_done )
};
const txt_cmd_s GavenRematchText[] = {
    text_start("Hi! I've been"
        t_line "waiting for you!"
        t_para "This time, I'm"
        t_line "going to win!"
        t_done )
};

//// gina_overworld.c
const txt_cmd_s GinaAskNumber1Text[] = {
    text_start("Whenever I see a"
        t_line "strong trainer, I"
        t_para "want to be their"
        t_line "cheerleader."
        t_para "When I'm on my"
        t_line "walk, I sometimes"
        t_cont "pick up items."
        t_para "If I get anything,"
        t_line "you can have it!"
        t_para "Want to give me"
        t_line "your number?"
        t_para "I'll call as soon"
        t_line "as I get anything."
        t_done )
};
const txt_cmd_s GinaAskNumber2Text[] = {
    text_start("If I find an item,"
        t_line "you can have it!"
        t_para "Want to give me"
        t_line "your number?"
        t_done )
};
const txt_cmd_s GinaNumberAcceptedText[] = {
    text_start("I'll call as soon"
        t_line "as I get anything!"
        t_done )
};
const txt_cmd_s GinaNumberDeclinedText[] = {
    text_start("Is that so? Well,"
        t_line "I'll still be"
        t_cont "rooting for you!"
        t_done )
};
const txt_cmd_s GinaPhoneFullText[] = {
    text_start("But your phone is"
        t_line "all filled up!"
        t_done )
};
const txt_cmd_s GinaRematchText[] = {
    text_start("I've been waiting!"
        t_para "I've gotten a bit"
        t_line "better at this!"
        t_done )
};
const txt_cmd_s GinaGiftText[] = {
    text_start("So you're finally"
        t_line "here!"
        t_para "I think this will"
        t_line "make you happy."
        t_done )
};
const txt_cmd_s GinaPackFullText[] = {
    text_start("Your PACK looks"
        t_line "completely full."
        t_para "I'll have to hold"
        t_line "on to this."
        t_done )
};

//// huey_overworld.c
const txt_cmd_s HueyAskNumber1Text[] = {
    text_start("Cool! That's the"
        t_line "first time I've"
        t_cont "lost in a while!"
        t_para "Hey, give me your"
        t_line "phone number."
        t_para "You'd be fun to"
        t_line "battle, so I'll"
        t_para "call you when I"
        t_line "get stronger!"
        t_done )
};
const txt_cmd_s HueyAskNumber2Text[] = {
    text_start("Hey, give me your"
        t_line "phone number."
        t_para "You'd be fun to"
        t_line "battle, so I'll"
        t_para "call you when I"
        t_line "get stronger!"
        t_done )
};
const txt_cmd_s HueyNumberAcceptedText[] = {
    text_start("Hey, let's battle"
        t_line "again!"
        t_done )
};
const txt_cmd_s HueyNumberDeclinedText[] = {
    text_start("Looks like you're"
        t_line "a wimp…"
        t_done )
};
const txt_cmd_s HueyPhoneFullText[] = {
    text_start("Hey! Your phone's"
        t_line "already full!"
        t_done )
};
const txt_cmd_s HueyRematchText[] = {
    text_start("Hey! I'm tired of"
        t_line "waiting for you!"
        t_done )
};
const txt_cmd_s HueyPackFullText[] = {
    text_start("Oh… Your PACK's"
        t_line "full. I'll give it"
        t_cont "to you later."
        t_done )
};
const txt_cmd_s HueyRematchGiftText[] = {
    text_start("Man! You're as"
        t_line "tough as ever!"
        t_para "I've battled you"
        t_line "over and over, but"
        t_para "<PLAYER>, I haven't"
        t_line "won once."
        t_para "I bought tons of"
        t_line "items to toughen"
        t_para "up my #MON, but"
        t_line "to no avail…"
        t_para "Items alone aren't"
        t_line "the answer."
        t_para "That must be what"
        t_line "it is…"
        t_para "Here, take this,"
        t_line "<PLAYER>."
        t_para "I won't be needing"
        t_line "it anymore…"
        t_done )
};

//// irwin_overworld.c
const txt_cmd_s IrwinAskNumber1Text[] = {
    text_start("You're the best"
        t_line "I've ever battled!"
        t_para "Huh? You're the"
        t_line "one who saved all"
        t_cont "the SLOWPOKE?"
        t_para "Well, no wonder I"
        t_line "couldn't beat you!"
        t_para "Would it be OK to"
        t_line "get your number?"
        t_para "I don't want to"
        t_line "miss anything you"
        t_cont "do from now on!"
        t_done )
};
const txt_cmd_s IrwinAskNumber2Text[] = {
    text_start("You will tell me"
        t_line "your phone number?"
        t_done )
};
const txt_cmd_s IrwinNumberAcceptedText[] = {
    text_start("Wow! Gee, thanks!"
        t_line "Now I can call you"
        t_para "anytime, whether"
        t_line "anything's up or"
        t_para "not. You know,"
        t_line "just to chat!"
        t_done )
};
const txt_cmd_s IrwinNumberDeclinedText[] = {
    text_start("Oh, but…"
        t_line "I'm not dangerous!"
        t_para "I just want to"
        t_line "call and chat"
        t_para "about everything"
        t_line "and nothing!"
        t_done )
};
const txt_cmd_s IrwinPhoneFullText[] = {
    text_start("Your phone list is"
        t_line "already full…"
        t_para "You must be really"
        t_line "popular…"
        t_done )
};

//// jack_overworld.c
const txt_cmd_s JackAskNumber1Text[] = {
    text_start("Your knowledge is"
        t_line "impressive!"
        t_para "I like that!"
        t_para "Want to trade"
        t_line "battle tips?"
        t_para "I'll phone if I"
        t_line "get good info."
        t_para "Would you tell me"
        t_line "your number?"
        t_done )
};
const txt_cmd_s JackAskNumber2Text[] = {
    text_start("Want to trade"
        t_line "battle tips?"
        t_para "I'll phone if I"
        t_line "get good info."
        t_para "Would you tell me"
        t_line "your number?"
        t_done )
};
const txt_cmd_s JackNumberAcceptedText[] = {
    text_start("I'll call you if I"
        t_line "hear anything!"
        t_done )
};
const txt_cmd_s JackNumberDeclinedText[] = {
    text_start("Oh, OK. Too bad…"
        t_para "Well, if you ever"
        t_line "want my number,"
        t_cont "come see me, OK?"
        t_done )
};
const txt_cmd_s JackPhoneFullText[] = {
    text_start("Oh?"
        t_line "Your phone's full."
        t_para "It can't register"
        t_line "my number."
        t_done )
};
const txt_cmd_s JackRematchText[] = {
    text_start("Hi, I was waiting"
        t_line "for you to show!"
        t_para "Let's get started"
        t_line "right away!"
        t_done )
};

//// joey_overworld.c
const txt_cmd_s JoeyAskNumber1Text[] = {
    text_start("Listen, can I get"
        t_line "your phone number?"
        t_para "I'll ring you for"
        t_line "some battles."
        t_para "I'm a rookie too, "
        t_line "so I think it'd be"
        t_cont "a good motivator."
        t_done )
};
const txt_cmd_s JoeyAskNumber2Text[] = {
    text_start("Can I get your"
        t_line "phone number?"
        t_para "I don't want to"
        t_line "lose against you!"
        t_para "We have to battle"
        t_line "again, OK?"
        t_done )
};
const txt_cmd_s JoeyNumberAcceptedText[] = {
    text_start("I'll ring you"
        t_line "whenever I get the"
        t_cont "urge to battle!"
        t_done )
};
const txt_cmd_s JoeyNumberDeclinedText[] = {
    text_start("Oh, all right…"
        t_para "But I won't lose"
        t_line "to you again!"
        t_done )
};
const txt_cmd_s JoeyPhoneFullText[] = {
    text_start("Huh, what? Your"
        t_line "phone's full."
        t_done )
};
const txt_cmd_s JoeyRematchText[] = {
    text_start("I've been waiting!"
        t_line "Let's battle now!"
        t_done )
};
const txt_cmd_s JoeyPackFullText[] = {
    text_start("Hey, wait! Your"
        t_line "PACK is stuffed!"
        t_para "Well, we'll leave"
        t_line "it till next time."
        t_done )
};
const txt_cmd_s JoeyRematchGiftText[] = {
    text_start("And yet another"
        t_line "loss…"
        t_para "No doubt about"
        t_line "it--you're tough."
        t_para "Being beaten this"
        t_line "often actually"
        t_cont "feels good now!"
        t_para "Here, take this. "
        t_line "Use it to get even"
        t_para "tougher. That will"
        t_line "toughen me up too!"
        t_done )
};

//// jose_overworld.c
const txt_cmd_s JoseAskNumber1Text[] = {
    text_start("If my @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_line "sees anything"
        t_para "pretty, it goes"
        t_line "and gets it."
        t_para "Do you like pretty"
        t_line "things?"
        t_para "I could share if"
        t_line "it gets some more."
        t_para "What's your phone"
        t_line "number? I'll call."
        t_para "Don't expect a"
        t_line "whole lot, OK?"
        t_done )
};
const txt_cmd_s JoseAskNumber2Text[] = {
    text_start("Do you like pretty"
        t_line "things?"
        t_para "I could share if"
        t_line "FARFETCH'D goes"
        t_cont "and gets more."
        t_para "What's your phone"
        t_line "number? I'll call."
        t_done )
};
const txt_cmd_s JoseNumberAcceptedText[] = {
    text_start("I'll call you as"
        t_line "soon as I get"
        t_cont "something pretty."
        t_done )
};
const txt_cmd_s JoseNumberDeclinedText[] = {
    text_start("You sure? Well,"
        t_line "tell me if you"
        t_cont "change your mind."
        t_done )
};
const txt_cmd_s JosePhoneFullText[] = {
    text_start("Huh? Your phone"
        t_line "list is full."
        t_done )
};
const txt_cmd_s JoseRematchText[] = {
    text_start("Tweet! Tweeeet!"
        t_para "Kept me waiting!"
        t_line "Go, FARFETCH'D!"
        t_done )
};
const txt_cmd_s JoseGiftText[] = {
    text_start("Kept me waiting!"
        t_line "Look, this is it!"
        t_para "See? Isn't it some"
        t_line "kind of pretty?"
        t_done )
};
const txt_cmd_s JosePackFullText[] = {
    text_start("Huh? You don't"
        t_line "have anywhere to"
        t_para "put this. Better"
        t_line "come back for it."
        t_done )
};

//// kenji_overworld.c
const txt_cmd_s KenjiAskNumber1Text[] = {
    text_start("Our battle was"
        t_line "remarkable!"
        t_para "I wish for some-"
        t_line "thing to remember"
        t_cont "you by!"
        t_para "Perhaps your phone"
        t_line "number will do?"
        t_para "My training makes"
        t_line "it impossible to"
        t_cont "chat much, but…"
        t_done )
};
const txt_cmd_s KenjiAskNumber2Text[] = {
    text_start("My training makes"
        t_line "chatting tough,"
        t_para "but will you take"
        t_line "down my number?"
        t_done )
};
const txt_cmd_s KenjiNumberAcceptedText[] = {
    text_start("I must train"
        t_line "harder to become"
        t_cont "the mightiest!"
        t_done )
};
const txt_cmd_s KenjiNumberDeclinedText[] = {
    text_start("If you decide you"
        t_line "want my number,"
        t_cont "come see me."
        t_done )
};
const txt_cmd_s KenjiPhoneFullText[] = {
    text_start("Your phone appears"
        t_line "to be full."
        t_para "Come back later!"
        t_done )
};
const txt_cmd_s KenjiGiftText[] = {
    text_start("I wish to thank"
        t_line "you, <PLAYER>!"
        t_para "I've been training"
        t_line "all alone…"
        t_para "I was happy that"
        t_line "you cared to call…"
        t_para "I want you to have"
        t_line "this!"
        t_done )
};
const txt_cmd_s KenjiPackFullText[] = {
    text_start("Your strength will"
        t_line "not let you carry"
        t_para "another thing!"
        t_line "I will hold this"
        t_para "till you lighten"
        t_line "your PACK!"
        t_done )
};

//// liz_overworld.c
const txt_cmd_s LizAskNumber1Text[] = {
    text_start("Oh? You're on a"
        t_line "big journey to see"
        t_cont "the sights? Neat!"
        t_para "Let's be friends!"
        t_line "Can I have your"
        t_cont "phone number?"
        t_para "I want to hear"
        t_line "about everything"
        t_cont "you've seen!"
        t_done )
};
const txt_cmd_s LizAskNumber2Text[] = {
    text_start("Let's be friends!"
        t_line "Can I have your"
        t_cont "phone number?"
        t_para "I want to hear"
        t_line "about everything"
        t_cont "you've seen!"
        t_done )
};
const txt_cmd_s LizNumberAcceptedText[] = {
    text_start("I'll telephone you"
        t_line "if I hear anything"
        t_cont "interesting."
        t_done )
};
const txt_cmd_s LizNumberDeclinedText[] = {
    text_start("Aww… You won't be"
        t_line "my friend?"
        t_done )
};
const txt_cmd_s LizPhoneFullText[] = {
    text_start("Wait! Your phone"
        t_line "list is filled up!"
        t_done )
};
const txt_cmd_s LizRematchText[] = {
    text_start("You're late! Let's"
        t_line "get started now!"
        t_done )
};

//// parry_overworld.c
const txt_cmd_s ParryAskNumber1Text[] = {
    text_start("Sheesh, the way"
        t_line "you attacked! That"
        t_para "was something! We"
        t_line "should meet again!"
        t_para "How about giving"
        t_line "me your number?"
        t_done )
};
const txt_cmd_s ParryAskNumber2Text[] = {
    text_start("So you want to"
        t_line "register my phone"
        t_para "number for a re-"
        t_line "match, huh?"
        t_done )
};
const txt_cmd_s ParryNumberAcceptedText[] = {
    text_start("I'll call you"
        t_line "whenever I feel"
        t_cont "like battling!"
        t_done )
};
const txt_cmd_s ParryNumberDeclinedText[] = {
    text_start("No? That's fine."
        t_para "A definite no is"
        t_line "easy to take!"
        t_para "I'll be right here"
        t_line "when you're ready"
        t_cont "for a rematch."
        t_done )
};
const txt_cmd_s ParryPhoneFullText[] = {
    text_start("Oh? There's no"
        t_line "room to register"
        t_cont "my phone number."
        t_done )
};
const txt_cmd_s ParryRematchText[] = {
    text_start("Hey, here comes"
        t_line "the kid! Let's go!"
        t_para "Ready for my usual"
        t_line "no-brainer, all-"
        t_cont "out offense?"
        t_done )
};
const txt_cmd_s ParryPackFullText[] = {
    text_start("Your PACK looks"
        t_line "stuffed full!"
        t_para "You can't have"
        t_line "this now."
        t_done )
};
const txt_cmd_s ParryRematchGiftText[] = {
    text_start("Well, you're"
        t_line "special all right."
        t_para "If only I'd begun"
        t_line "#MON when I was"
        t_cont "a tad younger…"
        t_para "I want you to work"
        t_line "and succeed for"
        t_para "the both of us."
        t_line "So take this, OK?"
        t_done )
};

//// ralph_overworld.c
const txt_cmd_s RalphAskNumber1Text[] = {
    text_start("Don't young people"
        t_line "fish anymore?"
        t_para "I've seen rare"
        t_line "#MON while I've"
        t_cont "been fishing…"
        t_para "You young people"
        t_line "like that, right?"
        t_para "Want to trade"
        t_line "phone numbers?"
        t_para "I'll let you know"
        t_line "if I see anything."
        t_done )
};
const txt_cmd_s RalphAskNumber2Text[] = {
    text_start("Hm? So you do want"
        t_line "me to phone if I"
        t_cont "see rare #MON?"
        t_done )
};
const txt_cmd_s RalphNumberAcceptedText[] = {
    text_start("Yep, phone if I"
        t_line "see rare #MON."
        t_para "Don't worry, I"
        t_line "won't forget!"
        t_done )
};
const txt_cmd_s RalphNumberDeclinedText[] = {
    text_start("Oh…"
        t_line "My own kids won't"
        t_para "even give me their"
        t_line "phone numbers…"
        t_para "Is that how young"
        t_line "people are today?"
        t_done )
};
const txt_cmd_s RalphPhoneFullText[] = {
    text_start("Your phone's"
        t_line "memory is full."
        t_para "It seems that"
        t_line "young people all"
        t_cont "have #GEAR."
        t_done )
};
const txt_cmd_s RalphRematchText[] = {
    text_start("Hey, kid!"
        t_para "No losing for me"
        t_line "this day!"
        t_done )
};

//// reena_overworld.c
const txt_cmd_s ReenaAskNumber1Text[] = {
    text_start("Not bad…"
        t_line "It's something to"
        t_para "beat me, even by"
        t_line "an unlikely fluke…"
        t_para "I like you! Give"
        t_line "me your number!"
        t_para "You can be my"
        t_line "practice partner!"
        t_done )
};
const txt_cmd_s ReenaAskNumber2Text[] = {
    text_start("Give me your phone"
        t_line "number!"
        t_para "You are going to"
        t_line "be my practice"
        t_cont "partner!"
        t_done )
};
const txt_cmd_s ReenaNumberAcceptedText[] = {
    text_start("Don't be too proud"
        t_line "about beating me!"
        t_para "It was a fluke!"
        t_done )
};
const txt_cmd_s ReenaNumberDeclinedText[] = {
    text_start("I don't believe"
        t_line "it! You're going"
        t_cont "to regret this!"
        t_done )
};
const txt_cmd_s ReenaPhoneFullText[] = {
    text_start("What? Your phone"
        t_line "list has no room!"
        t_done )
};
const txt_cmd_s ReenaRematchText[] = {
    text_start("What took you?"
        t_line "Start right away!"
        t_done )
};

//// tiffany_overworld.c
const txt_cmd_s TiffanyAskNumber1Text[] = {
    text_start("Hi! You like"
        t_line "CLEFAIRY too?"
        t_para "They're so very"
        t_line "cute, aren't they?"
        t_para "I think we can be"
        t_line "good friends!"
        t_para "I want to know"
        t_line "your phone number!"
        t_para "Let's talk about"
        t_line "CLEFAIRY!"
        t_done )
};
const txt_cmd_s TiffanyAskNumber2Text[] = {
    text_start("I want to know"
        t_line "your phone number!"
        t_para "Let's talk about"
        t_line "CLEFAIRY!"
        t_done )
};
const txt_cmd_s TiffanyNumberAcceptedText[] = {
    text_start("Isn't my CLEFAIRY"
        t_line "super-adorable?"
        t_done )
};
const txt_cmd_s TiffanyNumberDeclinedText[] = {
    text_start("Aww… Oh well."
        t_line "Look for me if you"
        t_para "want to talk about"
        t_line "CLEFAIRY."
        t_done )
};
const txt_cmd_s TiffanyPhoneFullText[] = {
    text_start("Oh? Your phone"
        t_line "registry is full."
        t_done )
};
const txt_cmd_s TiffanyRematchText[] = {
    text_start("There you are!"
        t_para "CLEFAIRY, I want"
        t_line "you to try hard!"
        t_done )
};
const txt_cmd_s TiffanyGiftText[] = {
    text_start("You took a long"
        t_line "time. See this?"
        t_para "Isn't it cute?"
        t_line "It's a PINK BOW."
        t_done )
};
const txt_cmd_s TiffanyPackFullText[] = {
    text_start("Uh-oh. Your PACK"
        t_line "is crammed full."
        t_done )
};

//// todd_overworld.c
const txt_cmd_s ToddAskNumber1Text[] = {
    text_start("From here, I can"
        t_line "see GOLDENROD's"
        t_para "DEPT.STORE. They"
        t_line "have bargain sales"
        t_para "up on the rooftop"
        t_line "every so often."
        t_para "Could I get your"
        t_line "phone number?"
        t_para "I'll call you when"
        t_line "they have a sale."
        t_done )
};
const txt_cmd_s ToddAskNumber2Text[] = {
    text_start("If you give me"
        t_line "your number, I'll"
        t_para "call you when they"
        t_line "have a sale."
        t_done )
};
const txt_cmd_s ToddNumberAcceptedText[] = {
    text_start("I check GOLDENROD"
        t_line "DEPT.STORE every"
        t_para "day, so I know"
        t_line "when there's a"
        t_cont "sale."
        t_done )
};
const txt_cmd_s ToddNumberDeclinedText[] = {
    text_start("Anyway…"
        t_para "If you're short on"
        t_line "money, take down"
        t_cont "my number."
        t_para "I'll call you when"
        t_line "there's a sale."
        t_done )
};
const txt_cmd_s ToddPhoneFullText[] = {
    text_start("Your phone doesn't"
        t_line "have enough memory"
        t_cont "for more numbers."
        t_done )
};
const txt_cmd_s ToddRematchText[] = {
    text_start("I waited for you!"
        t_line "I even cut back my"
        t_para "shopping to raise"
        t_line "my #MON better!"
        t_done )
};
// This is a duplicate of CamperToddSaleText in maps/Route34.asm.
const txt_cmd_s ToddSaleText[] = {
    text_start("Shopping under the"
        t_line "sky!"
        t_para "It feels so nice"
        t_line "up on a rooftop."
        t_done )
};

//// tully_overworld.c
const txt_cmd_s TullyAskNumber1Text[] = {
    text_start("Hey, you're trying"
        t_line "to be the ultimate"
        t_para "trainer too? Then"
        t_line "we're comrades!"
        t_para "If I find any more"
        t_line "items by the"
        t_para "water, I'll give"
        t_line "you some."
        t_para "Just give me your"
        t_line "phone number."
        t_done )
};
const txt_cmd_s TullyAskNumber2Text[] = {
    text_start("If I find any more"
        t_line "items by the"
        t_para "water, I'll give"
        t_line "you some."
        t_para "Just give me your"
        t_line "phone number."
        t_done )
};
const txt_cmd_s TullyNumberAcceptedText[] = {
    text_start("You'll be hearing"
        t_line "from me if I find"
        t_cont "something good."
        t_done )
};
const txt_cmd_s TullyNumberDeclinedText[] = {
    text_start("Is that so? Then"
        t_line "I'll just have to"
        t_cont "use them myself."
        t_done )
};
const txt_cmd_s TullyPhoneFullText[] = {
    text_start("Your phone list is"
        t_line "all filled up."
        t_para "Come back if you"
        t_line "make room for me."
        t_done )
};
const txt_cmd_s TullyRematchText[] = {
    text_start("I've been doing"
        t_line "more than just"
        t_para "fishing since we"
        t_line "last met."
        t_para "You're in for a"
        t_line "big surprise!"
        t_done )
};
const txt_cmd_s TullyGiftText[] = {
    text_start("Hey, there you"
        t_line "are!"
        t_para "Here's a gift, as"
        t_line "promised!"
        t_done )
};
const txt_cmd_s TullyPackFullText[] = {
    text_start("Your PACK's full?"
        t_para "Come back later--"
        t_line "that'll do it."
        t_done )
};

//// vance_overworld.c
const txt_cmd_s VanceAskNumber1Text[] = {
    text_start("You know, you are"
        t_line "really strong."
        t_para "But I don't want"
        t_line "to just slink off…"
        t_para "I know! Could I"
        t_line "get your number?"
        t_para "Let's meet up for"
        t_line "more battles!"
        t_done )
};
const txt_cmd_s VanceAskNumber2Text[] = {
    text_start("I want to battle"
        t_line "tough trainers as"
        t_cont "often as I can!"
        t_para "Could I get your"
        t_line "number?"
        t_para "Let's meet up for"
        t_line "more battles!"
        t_done )
};
const txt_cmd_s VanceNumberAcceptedText[] = {
    text_start("Don't forget to"
        t_line "come see me when I"
        t_cont "challenge you!"
        t_done )
};
const txt_cmd_s VanceNumberDeclinedText[] = {
    text_start("A bird-user friend"
        t_line "isn't a bad thing"
        t_cont "to have, I think…"
        t_para "Won't you"
        t_line "reconsider?"
        t_done )
};
const txt_cmd_s VancePhoneFullText[] = {
    text_start("Your phone's out"
        t_line "of memory. Delete"
        t_cont "a number for me!"
        t_done )
};
const txt_cmd_s VanceRematchText[] = {
    text_start("Am I happy to see"
        t_line "you! I won't lose!"
        t_done )
};
const txt_cmd_s VancePackFullText[] = {
    text_start("Oh, too bad. You"
        t_line "don't have room."
        t_para "I'll give it to"
        t_line "you next time!"
        t_done )
};
const txt_cmd_s VanceRematchGiftText[] = {
    text_start("You are really,"
        t_line "really strong!"
        t_para "Thanks for taking"
        t_line "me on so often--I"
        t_para "learned a whole"
        t_line "lot from you."
        t_para "I know! This will"
        t_line "do as my thanks!"
        t_done )
};

//// wade_overworld.c
const txt_cmd_s WadeAskNumber1Text[] = {
    text_start("You're awesome!"
        t_line "I like you!"
        t_para "I look for #MON"
        t_line "here every day."
        t_para "When I'm in the"
        t_line "grass, I find all"
        t_cont "kinds of BERRIES."
        t_para "If you'd like,"
        t_line "I'll share some."
        t_para "Could I get your"
        t_line "phone number?"
        t_done )
};
const txt_cmd_s WadeAskNumber2Text[] = {
    text_start("When I'm in the"
        t_line "grass, I find all"
        t_cont "kinds of BERRIES."
        t_para "If you'd like,"
        t_line "I'll share some."
        t_para "Could I get your"
        t_line "phone number?"
        t_done )
};
const txt_cmd_s WadeNumberAcceptedText[] = {
    text_start("You'll hear from"
        t_line "me as soon as I"
        t_para "find anything that"
        t_line "you might like."
        t_done )
};
const txt_cmd_s WadeNumberDeclinedText[] = {
    text_start("Oh well. Don't be"
        t_line "shy if you want to"
        t_cont "get my number."
        t_done )
};
const txt_cmd_s WadePhoneFullText[] = {
    text_start("Your phone list"
        t_line "has no room for my"
        t_cont "number."
        t_done )
};
const txt_cmd_s WadeRematchText[] = {
    text_start("I was waiting for"
        t_line "you. Let's battle!"
        t_done )
};
const txt_cmd_s WadeGiftText[] = {
    text_start("Good to see you!"
        t_line "See? This is what"
        t_para "I found."
        t_line "It's for you!"
        t_done )
};
const txt_cmd_s WadePackFullText[] = {
    text_start("Oops, your PACK's"
        t_line "full. Too bad."
        t_para "You should come"
        t_line "back for it later."
        t_done )
};

//// wilton_overworld.c
const txt_cmd_s WiltonAskNumber1Text[] = {
    text_start("Eh, our battle was"
        t_line "fun, I'd say…"
        t_para "When I'm fishing,"
        t_line "I sometimes snag"
        t_para "items that people"
        t_line "have dropped."
        t_para "Do you want them?"
        t_line "What's the number?"
        t_done )
};
const txt_cmd_s WiltonAskNumber2Text[] = {
    text_start("If I snag an item"
        t_line "while I'm fishing,"
        t_para "it's yours. What's"
        t_line "your number?"
        t_done )
};
const txt_cmd_s WiltonNumberAcceptedText[] = {
    text_start("If I snag anything"
        t_line "good, I'll be sure"
        t_cont "to let you know."
        t_done )
};
const txt_cmd_s WiltonNumberDeclinedText[] = {
    text_start("All right… Come"
        t_line "back if you have a"
        t_cont "change of heart."
        t_done )
};
const txt_cmd_s WiltonPhoneFullText[] = {
    text_start("You can't register"
        t_line "another number."
        t_done )
};
const txt_cmd_s WiltonRematchText[] = {
    text_start("Argh! You startled"
        t_line "POLIWAG into"
        t_cont "fleeing again!"
        t_done )
};
const txt_cmd_s WiltonGiftText[] = {
    text_start("So here you are."
        t_para "See this?"
        t_line "I snagged it just"
        t_para "a little while"
        t_line "ago. It's yours."
        t_done )
};
const txt_cmd_s WiltonPackFullText[] = {
    text_start("Your PACK's full?"
        t_para "I'll give it to"
        t_line "you later."
        t_done )
};

