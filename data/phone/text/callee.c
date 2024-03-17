#include "../../../constants.h"
#include "callee.h"

//// alan_callee.c

const txt_cmd_s AlanAnswerPhoneText[] = {
    text_start("Yup, it's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Is this <PLAY_G>?"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s AlanAnswerPhoneDayText[] = {
    text_start("Yup, it's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Is that <PLAY_G>?"
        t_done )
};
const txt_cmd_s AlanAnswerPhoneNiteText[] = {
    text_start("Yup, it's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Is that <PLAY_G>?"
        t_line "Good evening!"
        t_done )
};
const txt_cmd_s AlanGreetText[] = {
    text_start("Hello! It's me,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s AlanGreetDayText[] = {
    text_start("Hello! It's me,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s AlanGreetNiteText[] = {
    text_start("Hello! It's me,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s AlanGenericText[] = {
    text_start("<PLAY_G>, are you"
        t_line "raising your"
        t_cont "#MON properly?"
        t_para "I read in a book"
        t_line "that you should"
        t_para "raise any #MON"
        t_line "you catch with"
        t_cont "love and care."
        t_done )
};

//// anthony_callee.c

const txt_cmd_s AnthonyAnswerPhoneText[] = {
    text_start("Yeah, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" the"
        t_line "HIKER here."
        t_para "Ah, <PLAYER>!"
        t_done )
};
const txt_cmd_s AnthonyAnswerPhoneDayText[] = {
    text_start("Yeah, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" the"
        t_line "HIKER here."
        t_para "Ah, <PLAYER>,"
        t_line "right?"
        t_done )
};
const txt_cmd_s AnthonyAnswerPhoneNiteText[] = {
    text_start("Yeah, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" the"
        t_line "HIKER here."
        t_para "Ah, <PLAYER>, isn't"
        t_line "it?"
        t_done )
};
const txt_cmd_s AnthonyGreetText[] = {
    text_start("Yo, <PLAYER>?"
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "the HIKER!"
        t_done )
};
const txt_cmd_s AnthonyGreetDayText[] = {
    text_start("Hey, is this"
        t_line "<PLAYER>?"
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "the HIKER!"
        t_done )
};
const txt_cmd_s AnthonyGreetNiteText[] = {
    text_start("<PLAYER>, you still"
        t_line "awake?"
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "the HIKER!"
        t_done )
};
const txt_cmd_s AnthonyGenericText[] = {
    text_start("Are your #MON"
        t_line "as feisty as ever?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and"
        t_line "me--we have energy"
        t_para "to burn. We hike"
        t_line "up mountains every"
        t_para "day to work out"
        t_line "all our energy."
        t_done )
};

//// arnie_callee.c

const txt_cmd_s ArnieAnswerPhoneText[] = {
    text_start("Yeah, hello."
        t_line "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "…Huh, <PLAY_G>? Yo!"
        t_done )
};
const txt_cmd_s ArnieAnswerPhoneDayText[] = {
    text_start("Yeah, hello, you"
        t_line "got @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "…Huh, <PLAY_G>? Yo!"
        t_done )
};
const txt_cmd_s ArnieAnswerPhoneNiteText[] = {
    text_start("Yeah, hello, you"
        t_line "got @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "…Huh, <PLAY_G>? Yo!"
        t_done )
};
const txt_cmd_s ArnieGreetText[] = {
    text_start("Yeah, hello?"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" calling."
        t_para "What are you up"
        t_line "to, <PLAY_G>?"
        t_done )
};
const txt_cmd_s ArnieGreetDayText[] = {
    text_start("Yeah, hello?"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" calling."
        t_para "Where are you now,"
        t_line "<PLAY_G>?"
        t_done )
};
const txt_cmd_s ArnieGreetNiteText[] = {
    text_start("Yeah, hello?"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" calling."
        t_para "Are you awake now,"
        t_line "<PLAY_G>?"
        t_done )
};
const txt_cmd_s ArnieGenericText[] = {
    text_start("I bet your #MON"
        t_line "are a lot stronger"
        t_cont "than before."
        t_done )
};

//// beth_callee.c

const txt_cmd_s BethAnswerPhoneText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh, <PLAY_G>."
        t_line "Good morning."
        t_para ""
        t_done )
};
const txt_cmd_s BethAnswerPhoneDayText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh. Hi, <PLAY_G>."
        t_done )
};
const txt_cmd_s BethAnswerPhoneNiteText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh, <PLAY_G>."
        t_line "Good evening."
        t_done )
};
const txt_cmd_s BethGreetText[] = {
    text_start("Good morning,"
        t_line "<PLAY_G>!"
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Were you sleeping?"
        t_done )
};
const txt_cmd_s BethGreetDayText[] = {
    text_start("<PLAY_G>, hi!"
        t_line "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Do you have some"
        t_line "time?"
        t_done )
};
const txt_cmd_s BethGreetNiteText[] = {
    text_start("Hi, <PLAY_G>."
        t_line "Good evening."
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "I hope you were"
        t_line "awake."
        t_done )
};
const txt_cmd_s BethGenericText[] = {
    text_start("Are you the kind"
        t_line "of person who goes"
        t_para "to #MON CENTERS"
        t_line "often?"
        t_para "I go every day."
        t_line "Watching out for"
        t_para "the health of your"
        t_line "#MON is a basic"
        t_para "part of being a"
        t_line "#MON trainer."
        t_done )
};

//// beverly_callee.c

const txt_cmd_s BeverlyAnswerPhoneText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh! Good morning,"
        t_line "<PLAYER>."
        t_done )
};
const txt_cmd_s BeverlyAnswerPhoneDayText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh! Good day,"
        t_line "<PLAYER>."
        t_done )
};
const txt_cmd_s BeverlyAnswerPhoneNiteText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh! Good evening,"
        t_line "<PLAYER>."
        t_done )
};
const txt_cmd_s BeverlyGreetText[] = {
    text_start("Hello, <PLAYER>."
        t_line "Good morning."
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Were you asleep?"
        t_done )
};
const txt_cmd_s BeverlyGreetDayText[] = {
    text_start("Hi, <PLAYER>."
        t_line "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "How are you doing?"
        t_done )
};
const txt_cmd_s BeverlyGreetNiteText[] = {
    text_start("Hi, <PLAYER>."
        t_line "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Were you awake?"
        t_done )
};
const txt_cmd_s BeverlyGenericText[] = {
    text_start("Keeping your"
        t_line "#MON happy?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is"
        t_line "healthy. It eats a"
        t_cont "lot every day."
        t_done )
};

//// brent_callee.c

const txt_cmd_s BrentAnswerPhoneText[] = {
    text_start("Yes? @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "Ah, <PLAYER>. What"
        t_line "can I do for you?"
        t_done )
};
const txt_cmd_s BrentAnswerPhoneDayText[] = {
    text_start("Yes? @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "Ah, <PLAYER>. What"
        t_line "can I do for you?"
        t_done )
};
const txt_cmd_s BrentAnswerPhoneNiteText[] = {
    text_start("Yes? @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "Ah, <PLAYER>. What"
        t_line "can I do for you?"
        t_done )
};
const txt_cmd_s BrentGreetText[] = {
    text_start("Hiya, <PLAYER>. How"
        t_line "are you doing?"
        t_para "Hey! It's me,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s BrentGreetDayText[] = {
    text_start("Hiya, <PLAYER>, how"
        t_line "are you doing?"
        t_para "Hey, it's me,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s BrentGreetNiteText[] = {
    text_start("Hiya, <PLAYER>, how"
        t_line "are you doing?"
        t_para "Hey, it's me,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s BrentGenericText[] = {
    text_start("Oh yeah, I saw you"
        t_line "coming out of a"
        t_para "#MON CENTER the"
        t_line "other day."
        t_para "You heal your"
        t_line "#MON regularly,"
        t_para "don't you?"
        t_line "I'm impressed."
        t_para "Heh, my @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_line "is so tough, it"
        t_para "doesn't need to go"
        t_line "to #MON CENTERS"
        t_cont "often. Heheh!"
        t_done )
};

//// chad_callee.c

const txt_cmd_s ChadAnswerPhoneText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Hi, <PLAY_G>!"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s ChadAnswerPhoneDayText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Hi, <PLAY_G>, good"
        t_line "day!"
        t_done )
};
const txt_cmd_s ChadAnswerPhoneNiteText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Hi, <PLAY_G>, good"
        t_line "evening!"
        t_done )
};
const txt_cmd_s ChadGreetText[] = {
    text_start("Hi, <PLAY_G>, good"
        t_line "morning!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "How are you?"
        t_done )
};
const txt_cmd_s ChadGreetDayText[] = {
    text_start("Hi, <PLAY_G>, good"
        t_line "day!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "How are you?"
        t_done )
};
const txt_cmd_s ChadGreetNiteText[] = {
    text_start("Hi, <PLAY_G>, good"
        t_line "evening!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "How are you?"
        t_done )
};
const txt_cmd_s ChadGenericText[] = {
    text_start("How are your"
        t_line "#MON doing?"
        t_para "You know PROF.OAK,"
        t_line "so of course your"
        t_cont "#MON are fine!"
        t_para "My #MON are"
        t_line "doing well too."
        t_para "But then, I am"
        t_line "trying to become a"
        t_para "#MON professor,"
        t_line "so that shouldn't"
        t_cont "be a big surprise."
        t_done )
};

//// dana_callee.c

const txt_cmd_s DanaAnswerPhoneText[] = {
    text_start("Hi, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" on the"
        t_line "line."
        t_para "Hey! It's <PLAY_G>!"
        t_done )
};
const txt_cmd_s DanaAnswerPhoneDayText[] = {
    text_start("Hi, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" on the"
        t_line "line."
        t_para "I know!"
        t_line "It's <PLAY_G>!"
        t_done )
};
const txt_cmd_s DanaAnswerPhoneNiteText[] = {
    text_start("Hi, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" on the"
        t_line "line."
        t_para "<PLAY_G>?"
        t_line "What's up?"
        t_done )
};
const txt_cmd_s DanaGreetText[] = {
    text_start("Uh, <PLAY_G>?"
        t_para "It's me!"
        t_line "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s DanaGreetDayText[] = {
    text_start("Uh, <PLAY_G>?"
        t_para "It's me!"
        t_line "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s DanaGreetNiteText[] = {
    text_start("Uh, <PLAY_G>?"
        t_para "It's me!"
        t_line "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s DanaGenericText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is"
        t_line "so full of energy,"
        t_para "it's a little"
        t_line "scary."
        t_para "How are your"
        t_line "#MON doing?"
        t_done )
};

//// derek_callee.c

const txt_cmd_s DerekAnswerPhoneText[] = {
    text_start("Hi, <PLAY_G>?"
        t_para "Good morning pika."
        t_line "What's up pika?"
        t_done )
};
const txt_cmd_s DerekAnswerPhoneDayText[] = {
    text_start("Hi, <PLAY_G>?"
        t_para "Good day pika,"
        t_line "what's up pika?"
        t_done )
};
const txt_cmd_s DerekAnswerPhoneNiteText[] = {
    text_start("Hi, <PLAY_G>?"
        t_para "Good evening pika,"
        t_line "what's up pika?"
        t_done )
};
const txt_cmd_s DerekGreetText[] = {
    text_start("<PLAY_G> pika, good"
        t_line "morning!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(", how"
        t_line "pika are you?"
        t_done )
};
const txt_cmd_s DerekGreetDayText[] = {
    text_start("<PLAY_G> pika, good"
        t_line "pika day!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(", how"
        t_line "pika are you?"
        t_done )
};
const txt_cmd_s DerekGreetNiteText[] = {
    text_start("<PLAY_G> pika, good"
        t_line "evening!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(". Were"
        t_line "you pika awake?"
        t_done )
};
const txt_cmd_s DerekGenericText[] = {
    text_start("You have to hear"
        t_line "this! My lovable"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" looked"
        t_line "at me and grinned!"
        t_para "It must be because"
        t_line "our hearts beat"
        t_cont "together as one!"
        t_done )
};

//// erin_callee.c

const txt_cmd_s ErinAnswerPhoneText[] = {
    text_start("Yes, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh. Hi, <PLAY_G>!"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s ErinAnswerPhoneDayText[] = {
    text_start("Yes, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, hi, <PLAY_G>!"
        t_line "Yahoo!"
        t_done )
};
const txt_cmd_s ErinAnswerPhoneNiteText[] = {
    text_start("Yes, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, hi, <PLAY_G>!"
        t_done )
};
const txt_cmd_s ErinGreetText[] = {
    text_start("<PLAY_G>!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s ErinGreetDayText[] = {
    text_start("<PLAY_G>!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "Working hard?"
        t_done )
};
const txt_cmd_s ErinGreetNiteText[] = {
    text_start("<PLAY_G>!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "Were you up?"
        t_done )
};
const txt_cmd_s ErinGenericText[] = {
    text_start("Are you raising"
        t_line "your #MON?"
        t_para "Hey, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("'s"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is"
        t_cont "looking good!"
        t_done )
};

//// gaven_callee.c

const txt_cmd_s GavenAnswerPhoneText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking…"
        t_para "Hi, <PLAY_G>!"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s GavenAnswerPhoneDayText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking…"
        t_para "Hi, <PLAY_G>!"
        t_done )
};
const txt_cmd_s GavenAnswerPhoneNiteText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking…"
        t_para "Hi, <PLAY_G>!"
        t_line "Good evening!"
        t_done )
};
const txt_cmd_s GavenGreetText[] = {
    text_start("<PLAY_G>, good"
        t_line "morning!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "How are you doing?"
        t_done )
};
const txt_cmd_s GavenGreetDayText[] = {
    text_start("Hi, <PLAY_G>!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "How are you doing?"
        t_done )
};
const txt_cmd_s GavenGreetNiteText[] = {
    text_start("<PLAY_G>, good"
        t_line "evening!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "How are you doing?"
        t_done )
};
const txt_cmd_s GavenGenericText[] = {
    text_start("How are your"
        t_line "#MON doing?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "doing as great as"
        t_cont "ever."
        t_para "Let's keep at it"
        t_line "and become #MON"
        t_cont "CHAMPS!"
        t_done )
};

//// gina_callee.c

const txt_cmd_s GinaAnswerPhoneText[] = {
    text_start("Hello? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, <PLAY_G>!"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s GinaAnswerPhoneDayText[] = {
    text_start("Hello? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, <PLAY_G>!"
        t_line "Hi, how are you?"
        t_done )
};
const txt_cmd_s GinaAnswerPhoneNiteText[] = {
    text_start("Hello? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, <PLAY_G>!"
        t_line "Good evening!"
        t_done )
};
const txt_cmd_s GinaGreetText[] = {
    text_start("<PLAY_G>?"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s GinaGreetDayText[] = {
    text_start("<PLAY_G>?"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(". Is"
        t_line "this a bad time?"
        t_done )
};
const txt_cmd_s GinaGreetNiteText[] = {
    text_start("<PLAY_G>?"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Got time to chat?"
        t_done )
};
const txt_cmd_s GinaGenericText[] = {
    text_start("Are your #MON"
        t_line "still tough?"
        t_para "I train every day"
        t_line "with @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("."
        t_done )
};

//// huey_callee.c

const txt_cmd_s HueyAnswerPhoneText[] = {
    text_start("Yeah, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Huh? What's up,"
        t_line "<PLAYER>?"
        t_done )
};
const txt_cmd_s HueyAnswerPhoneDayText[] = {
    text_start("Yeah, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Huh? What's up"
        t_line "<PLAYER>?"
        t_done )
};
const txt_cmd_s HueyAnswerPhoneNiteText[] = {
    text_start("Yeah, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Huh? What's up"
        t_line "<PLAYER>?"
        t_done )
};
const txt_cmd_s HueyGreetText[] = {
    text_start("Yo, <PLAYER>!"
        t_line "You awake?"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "How's it going?"
        t_done )
};
const txt_cmd_s HueyGreetDayText[] = {
    text_start("Yo, <PLAYER>! You"
        t_line "free right now?"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "How's it going?"
        t_done )
};
const txt_cmd_s HueyGreetNiteText[] = {
    text_start("Yo, <PLAYER>!"
        t_line "Were you asleep?"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "How's it going?"
        t_done )
};

//// irwin_callee.c

const txt_cmd_s IrwinAnswerPhoneText[] = {
    text_start("Hello? @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "here…"
        t_para "Hey, <PLAY_G>!"
        t_done )
};
const txt_cmd_s IrwinAnswerPhoneDayText[] = {
    text_start("Hello? @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "here…"
        t_para "Wow, <PLAY_G>!"
        t_done )
};
const txt_cmd_s IrwinAnswerPhoneNiteText[] = {
    text_start("Hello? @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "here…"
        t_para "Yippee, <PLAY_G>!"
        t_done )
};
const txt_cmd_s IrwinGreetText[] = {
    text_start("Uh, hello."
        t_line "<PLAY_G>?"
        t_para "It's your pal,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s IrwinGreetDayText[] = {
    text_start("Uh, hello,"
        t_line "<PLAY_G>?"
        t_para "It's your buddy"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s IrwinGreetNiteText[] = {
    text_start("Uh, hello,"
        t_line "<PLAY_G>?"
        t_para "It's your sidekick"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};

//// jack_callee.c

const txt_cmd_s JackAnswerPhoneText[] = {
    text_start("Hello. This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Good morning,"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s JackAnswerPhoneDayText[] = {
    text_start("Hello. This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "How's it going,"
        t_line "<PLAY_G>?"
        t_done )
};
const txt_cmd_s JackAnswerPhoneNiteText[] = {
    text_start("Hello. This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Good evening,"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s JackGreetText[] = {
    text_start("<PLAY_G>, good"
        t_line "morning!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "How are you doing?"
        t_done )
};
const txt_cmd_s JackGreetDayText[] = {
    text_start("<PLAY_G>, howdy!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Isn't it nice out?"
        t_done )
};
const txt_cmd_s JackGreetNiteText[] = {
    text_start("<PLAY_G>, good"
        t_line "evening!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Got a minute?"
        t_done )
};
const txt_cmd_s JackGenericText[] = {
    text_start("How are your"
        t_line "#MON doing?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is"
        t_line "so curious, it's a"
        t_para "problem. Maybe"
        t_line "it's like me…"
        t_done )
};

//// joey_callee.c

const txt_cmd_s JoeyAnswerPhoneText[] = {
    text_start("Hi, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here!"
        t_para "Oh, <PLAYER>? You"
        t_line "doing well?"
        t_done )
};
const txt_cmd_s JoeyAnswerPhoneDayText[] = {
    text_start("Hi, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here!"
        t_para "Oh, <PLAYER>? You"
        t_line "doing well?"
        t_done )
};
const txt_cmd_s JoeyAnswerPhoneNiteText[] = {
    text_start("Hi, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here!"
        t_para "Oh, <PLAYER>? You"
        t_line "doing well?"
        t_done )
};
const txt_cmd_s JoeyGreetText[] = {
    text_start("Yo, <PLAYER>!"
        t_line "How're you doing?"
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(","
        t_line "got a minute?"
        t_done )
};
const txt_cmd_s JoeyGreetDayText[] = {
    text_start("Yo, <PLAYER>! How's"
        t_line "it going?"
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Got a minute?"
        t_done )
};
const txt_cmd_s JoeyGreetNiteText[] = {
    text_start("Yo, <PLAYER>!"
        t_line "How're you doing?"
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(","
        t_line "got a minute?"
        t_done )
};
const txt_cmd_s JoeyGenericText[] = {
    text_start("How are your"
        t_line "#MON doing?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "raring to go, just"
        t_cont "like always."
        t_para "It's the only one"
        t_line "I have. I'm going"
        t_para "to become a great"
        t_line "trainer with it!"
        t_done )
};

//// jose_callee.c

const txt_cmd_s JoseAnswerPhoneText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, <PLAY_G>?"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s JoseAnswerPhoneDayText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, <PLAY_G>? Hi!"
        t_done )
};
const txt_cmd_s JoseAnswerPhoneNiteText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, <PLAY_G>?"
        t_line "Good evening!"
        t_done )
};
const txt_cmd_s JoseGreetText[] = {
    text_start("Oh, <PLAY_G>?"
        t_para "Tweet! Yeah, it's"
        t_line "me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s JoseGreetDayText[] = {
    text_start("Oh, <PLAY_G>?"
        t_para "Tweet! Yeah, it's"
        t_line "me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s JoseGreetNiteText[] = {
    text_start("Oh, <PLAY_G>?"
        t_para "Tweet! Yeah, it's"
        t_line "me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s JoseGenericText[] = {
    text_start("Are your #MON"
        t_line "still cooking?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" has"
        t_line "too much energy."
        t_para "Once it takes off,"
        t_line "it won't come back"
        t_cont "for a while."
        t_done )
};

//// kenji_callee.c

const txt_cmd_s KenjiAnswerPhoneText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "<PLAYER>! Beautiful"
        t_line "morning, hey?"
        t_done )
};
const txt_cmd_s KenjiAnswerPhoneDayText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "<PLAYER>! Beautiful"
        t_line "weather, hey?"
        t_done )
};
const txt_cmd_s KenjiAnswerPhoneNiteText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "<PLAYER>! Beautiful"
        t_line "moonlight, hey?"
        t_done )
};
const txt_cmd_s KenjiGreetText[] = {
    text_start("Hey, <PLAYER>!"
        t_line "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s KenjiGreetDayText[] = {
    text_start("Hey, <PLAYER>!"
        t_line "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s KenjiGreetNiteText[] = {
    text_start("Hey, <PLAYER>!"
        t_line "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};

//// liz_callee.c

const txt_cmd_s LizAnswerPhoneText[] = {
    text_start("Hello, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "speaking."
        t_para "Oh, <PLAY_G>."
        t_line "Good morning."
        t_done )
};
const txt_cmd_s LizAnswerPhoneDayText[] = {
    text_start("Hello, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "speaking."
        t_para "Oh, <PLAY_G>."
        t_line "How are you?"
        t_done )
};
const txt_cmd_s LizAnswerPhoneNiteText[] = {
    text_start("Hello, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_line "speaking."
        t_para "Oh, <PLAY_G>."
        t_line "Good evening."
        t_done )
};
const txt_cmd_s LizGreetText[] = {
    text_start("Good morning,"
        t_line "<PLAY_G>."
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Were you sleeping?"
        t_done )
};
const txt_cmd_s LizGreetDayText[] = {
    text_start("Hi, <PLAY_G>."
        t_line "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "How are things"
        t_line "going for you?"
        t_done )
};
const txt_cmd_s LizGreetNiteText[] = {
    text_start("Good evening,"
        t_line "<PLAY_G>."
        t_para "This is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Are you awake?"
        t_done )
};
const txt_cmd_s LizGenericText[] = {
    text_start("I had some time,"
        t_line "so I called you."
        t_para "So anyway, how are"
        t_line "your #MON?"
        t_para "Me, I take my"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" to the"
        t_para "#MON CENTER in"
        t_line "VIOLET every day,"
        t_para "so it's doing just"
        t_line "fantastic!"
        t_para "I'm friends with"
        t_line "the receptionist!"
        t_done )
};

//// parry_callee.c

const txt_cmd_s ParryAnswerPhoneText[] = {
    text_start("Yup, yup!"
        t_line "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Hah, and here's"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s ParryAnswerPhoneDayText[] = {
    text_start("Yup, yup!"
        t_line "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Hah, and here's"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s ParryAnswerPhoneNiteText[] = {
    text_start("Yup, yup!"
        t_line "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Hah, and here's"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s ParryGreetText[] = {
    text_start("<PLAY_G>, it's"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Have you had a"
        t_line "proper breakfast?"
        t_done )
};
const txt_cmd_s ParryGreetDayText[] = {
    text_start("<PLAY_G>, it's"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Have you had a"
        t_line "proper lunch?"
        t_done )
};
const txt_cmd_s ParryGreetNiteText[] = {
    text_start("<PLAY_G>, it's"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_para "Have you had a"
        t_line "proper dinner?"
        t_done )
};
const txt_cmd_s ParryGenericText[] = {
    text_start("Are your #MON"
        t_line "looking good?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and"
        t_line "me--we're looking"
        t_para "mighty dandy!"
        t_line "Hahahah!"
        t_done )
};

//// ralph_callee.c

const txt_cmd_s RalphAnswerPhoneText[] = {
    text_start("Yes? Ah, <PLAY_G>."
        t_para "You're courteous"
        t_line "enough to state"
        t_para "your name when you"
        t_line "call on the phone."
        t_done )
};
const txt_cmd_s RalphAnswerPhoneDayText[] = {
    text_start("Yes? Ah, <PLAY_G>."
        t_para "You're courteous"
        t_line "enough to state"
        t_para "your name when you"
        t_line "call on the phone."
        t_done )
};
const txt_cmd_s RalphAnswerPhoneNiteText[] = {
    text_start("Yes? Ah, <PLAY_G>."
        t_para "You're courteous"
        t_line "enough to state"
        t_para "your name when you"
        t_line "call on the phone."
        t_done )
};
const txt_cmd_s RalphGreetText[] = {
    text_start("Hiya, it's Uncle"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s RalphGreetDayText[] = {
    text_start("Hiya, it's Uncle"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s RalphGreetNiteText[] = {
    text_start("Hiya, it's Uncle"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s RalphGenericText[] = {
    text_start("Are you taking"
        t_line "good care of your"
        t_para "#MON? You have"
        t_line "to be good to your"
        t_cont "partners!"
        t_done )
};

//// reena_callee.c

const txt_cmd_s ReenaAnswerPhoneText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh. Hi, <PLAYER>."
        t_line "What's up?"
        t_done )
};
const txt_cmd_s ReenaAnswerPhoneDayText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, hi, <PLAYER>,"
        t_line "what's up?"
        t_done )
};
const txt_cmd_s ReenaAnswerPhoneNiteText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, hi, <PLAYER>,"
        t_line "what's up?"
        t_done )
};
const txt_cmd_s ReenaGreetText[] = {
    text_start("You're slow! Hurry"
        t_line "up and answer!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s ReenaGreetDayText[] = {
    text_start("You're slow! Hurry"
        t_line "up and answer!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s ReenaGreetNiteText[] = {
    text_start("You're slow! Hurry"
        t_line "up and answer!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_done )
};
const txt_cmd_s ReenaGenericText[] = {
    text_start("Hey, how are your"
        t_line "#MON doing?"
        t_para "What? Great?"
        t_line "I see…"
        t_para "What? My #MON?"
        t_para "Of course they're"
        t_line "doing great! What"
        t_para "kind of a question"
        t_line "is that?"
        t_done )
};

//// tiffany_callee.c

const txt_cmd_s TiffanyAnswerPhoneText[] = {
    text_start("Yes? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh, <PLAY_G>."
        t_line "Good morning."
        t_done )
};
const txt_cmd_s TiffanyAnswerPhoneDayText[] = {
    text_start("Yes? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh, <PLAY_G>."
        t_line "Hello."
        t_done )
};
const txt_cmd_s TiffanyAnswerPhoneNiteText[] = {
    text_start("Yes? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Oh, <PLAY_G>, good"
        t_line "evening."
        t_done )
};
const txt_cmd_s TiffanyGreetText[] = {
    text_start("Is this <PLAY_G>?"
        t_para "Good morning. This"
        t_line "is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s TiffanyGreetDayText[] = {
    text_start("Is this <PLAY_G>?"
        t_para "Hi, it's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s TiffanyGreetNiteText[] = {
    text_start("Is this <PLAY_G>?"
        t_para "Good evening. This"
        t_line "is @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_done )
};
const txt_cmd_s TiffanyGenericText[] = {
    text_start("Are your #MON"
        t_line "doing well?"
        t_para "I hope you take"
        t_line "them to a #MON"
        t_cont "CENTER every day."
        t_para "Don't push them"
        t_line "too hard."
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is"
        t_line "cute and lively"
        t_para "precisely because"
        t_line "I take it to a"
        t_para "#MON CENTER"
        t_line "every day."
        t_done )
};

//// todd_callee.c

const txt_cmd_s ToddAnswerPhoneText[] = {
    text_start("Yes? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking."
        t_para "Hey, <PLAY_G>!"
        t_done )
};
const txt_cmd_s ToddAnswerPhoneDayText[] = {
    text_start("Yes? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking."
        t_para "This must be"
        t_line "<PLAY_G>."
        t_done )
};
const txt_cmd_s ToddAnswerPhoneNiteText[] = {
    text_start("Yes? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking."
        t_para "Ah, <PLAY_G>!"
        t_done )
};
const txt_cmd_s ToddGreetText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "<PLAY_G>, right?"
        t_done )
};
const txt_cmd_s ToddGreetDayText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "<PLAY_G>, what are"
        t_line "you doing?"
        t_done )
};
const txt_cmd_s ToddGreetNiteText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "<PLAY_G>, sorry to"
        t_line "call you so late."
        t_done )
};
const txt_cmd_s ToddGenericText[] = {
    text_start("How do you raise"
        t_line "your #MON?"
        t_para "I do all sorts"
        t_line "of things, like"
        t_para "leaving them in"
        t_line "DAY-CARE and"
        t_para "toughening them up"
        t_line "with items."
        t_done )
};

//// tully_callee.c

const txt_cmd_s TullyAnswerPhoneText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Oh, Good morning,"
        t_line "<PLAY_G>."
        t_done )
};
const txt_cmd_s TullyAnswerPhoneDayText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "That voice…"
        t_line "<PLAY_G>, right?"
        t_done )
};
const txt_cmd_s TullyAnswerPhoneNiteText[] = {
    text_start("Hello, this is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "This must be"
        t_line "<PLAY_G>!"
        t_done )
};
const txt_cmd_s TullyGreetText[] = {
    text_start("Hello!"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "Good morning! The"
        t_line "weather's great!"
        t_done )
};
const txt_cmd_s TullyGreetDayText[] = {
    text_start("Hello!"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "What a perfect day"
        t_line "for fishing!"
        t_done )
};
const txt_cmd_s TullyGreetNiteText[] = {
    text_start("Hello!"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here…"
        t_para "It's a great night"
        t_line "for fishing!"
        t_done )
};
const txt_cmd_s TullyGenericText[] = {
    text_start("How's your trip"
        t_line "coming along?"
        t_para "I can't complain"
        t_line "about my fishing!"
        t_done )
};

//// unknown_callee.c

const txt_cmd_s UnknownGenericText[] = {
    text_start("How are your"
        t_line "#MON doing?"
        t_para "My #MON are a"
        t_line "bit too energetic."
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(","
        t_line "especially."
        t_para "Every time it"
        t_line "spots a trainer,"
        t_cont "it has to battle."
        t_para "It gets to be a"
        t_line "bit much for me!"
        t_done )
};
const txt_cmd_s UnknownTougherThanEverText[] = {
    text_start("My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start("'s"
        t_line "looking tougher"
        t_cont "than ever."
        t_para "It looks even"
        t_line "tougher than me!"
        t_done )
};

//// vance_callee.c

const txt_cmd_s VanceAnswerPhoneText[] = {
    text_start("Yes, hello?"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here!"
        t_para "Morning, <PLAY_G>!"
        t_para "Are you using bird"
        t_line "#MON?"
        t_done )
};
const txt_cmd_s VanceAnswerPhoneDayText[] = {
    text_start("Yes, hello?"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here!"
        t_para "Hi, <PLAY_G>!"
        t_para "Are your bird"
        t_line "#MON flying?"
        t_done )
};
const txt_cmd_s VanceAnswerPhoneNiteText[] = {
    text_start("Yes, hello?"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" here!"
        t_para "Evening, <PLAY_G>!"
        t_line "Are you letting"
        t_para "your bird #MON"
        t_line "see some action?"
        t_done )
};
const txt_cmd_s VanceGreetText[] = {
    text_start("Good morning,"
        t_line "<PLAY_G>!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s VanceGreetDayText[] = {
    text_start("Hi, <PLAY_G>!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "Remember me?"
        t_done )
};
const txt_cmd_s VanceGreetNiteText[] = {
    text_start("Good evening,"
        t_line "<PLAY_G>!"
        t_para "It's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("!"
        t_line "Are you free now?"
        t_done )
};
const txt_cmd_s VanceGenericText[] = {
    text_start("Are you and your"
        t_line "#MON fine?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_line "looks like it will"
        t_para "get tough enough"
        t_line "to face and beat"
        t_para "the legendary bird"
        t_line "#MON!"
        t_done )
};

//// wade_callee.c

const txt_cmd_s WadeAnswerPhoneText[] = {
    text_start("Hello? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking."
        t_para "Oh. Hi, <PLAY_G>!"
        t_line "Good morning!"
        t_done )
};
const txt_cmd_s WadeAnswerPhoneDayText[] = {
    text_start("Hello? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking."
        t_para "Oh, hi, <PLAY_G>!"
        t_done )
};
const txt_cmd_s WadeAnswerPhoneNiteText[] = {
    text_start("Hello? This is"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" speaking."
        t_para "Oh, hi, <PLAY_G>!"
        t_line "Good evening!"
        t_done )
};
const txt_cmd_s WadeGreetText[] = {
    text_start("<PLAY_G>, good"
        t_line "morning!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Isn't it nice out?"
        t_done )
};
const txt_cmd_s WadeGreetDayText[] = {
    text_start("<PLAY_G>, howdy!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Isn't it nice out?"
        t_done )
};
const txt_cmd_s WadeGreetNiteText[] = {
    text_start("Good evening,"
        t_line "<PLAY_G>!"
        t_para "It's me, @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_line "Were you awake?"
        t_done )
};
const txt_cmd_s WadeGenericText[] = {
    text_start("How are your"
        t_line "#MON doing?"
        t_para "My #MON have"
        t_line "too much energy to"
        t_para "burn. It gets to"
        t_line "be a problem."
        t_para "Of all my #MON,"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" is the"
        t_cont "hardest to handle."
        t_para "Working with it is"
        t_line "exhausting."
        t_done )
};

//// wilton_callee.c

const txt_cmd_s WiltonAnswerPhoneText[] = {
    text_start("Hello, you have"
        t_line "reached @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Ah, <PLAY_G>."
        t_done )
};
const txt_cmd_s WiltonAnswerPhoneDayText[] = {
    text_start("Hello, you have"
        t_line "reached @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Ah, <PLAY_G>, is"
        t_line "it?"
        t_done )
};
const txt_cmd_s WiltonAnswerPhoneNiteText[] = {
    text_start("Hello, you have"
        t_line "reached @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Ah, if it isn't"
        t_line "<PLAY_G>."
        t_done )
};
const txt_cmd_s WiltonGreetText[] = {
    text_start("Ah, it's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Have you got a"
        t_line "moment?"
        t_done )
};
const txt_cmd_s WiltonGreetDayText[] = {
    text_start("Ah, it's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Can you talk now?"
        t_done )
};
const txt_cmd_s WiltonGreetNiteText[] = {
    text_start("Ah, it's @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Sorry for calling"
        t_line "so late."
        t_done )
};
const txt_cmd_s WiltonGenericText[] = {
    text_start("Have your #MON"
        t_line "grown any?"
        t_para "My @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" has"
        t_line "grown quite a bit."
        t_done )
};

