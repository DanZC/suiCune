#include "../../../constants.h"
#include "../../../util/scripting_macros.h"

const struct TextCmd BuenaPhoneMorningAnswerText[] = {
    text_start("Hi, this is BUENA…"
        t_para "Oh! Good morning,"
        t_line "<PLAY_G>!"
        t_para "I'm kind of foggy"
        t_line "in the morning…"
        t_done )
};
const struct TextCmd BuenaPhoneDayAnswerText[] = {
    text_start("Hi, this is BUENA…"
        t_line "Oh! Hi, <PLAY_G>!"
        t_para "Do you tune into"
        t_line "BUENA's show?"
        t_done )
};
const struct TextCmd BuenaPhoneMidnightAnswerText[] = {
    text_start("This is BUENA."
        t_line "I can't come to"
        t_para "the phone right"
        t_line "now."
        t_para "If you want to"
        t_line "chat, tune into"
        t_para "BUENA's PASSWORD"
        t_line "on the radio and"
        t_para "give me a call"
        t_line "after midnight!"
        t_done )
};
const struct TextCmd BuenaPhoneNiteAnswerText[] = {
    text_start("Hi, this is BUENA…"
        t_line "Oh! Hi, <PLAY_G>!"
        t_para "I just got off"
        t_line "work. "
        t_para "Let me tell you,"
        t_line "I'm exhausted!"
        t_done )
};
const struct TextCmd BuenaPhoneMorningText[] = {
    text_start("<PLAY_G>!"
        t_line "Hi, it's BUENA!"
        t_para "I got up early, so"
        t_line "I decided to call!"
        t_done )
};
const struct TextCmd BuenaPhoneDayText[] = {
    text_start("<PLAY_G>!"
        t_line "Hi, it's BUENA!"
        t_para "I needed someone"
        t_line "to chat with!"
        t_done )
};
const struct TextCmd BuenaPhoneMidnightText[] = {
    text_start("<PLAY_G>!"
        t_line "Hi, it's BUENA!"
        t_para "I'm just on my"
        t_line "break."
        t_done )
};
const struct TextCmd BuenaPhoneNiteText[] = {
    text_start("<PLAY_G>!"
        t_line "Hi, it's BUENA!"
        t_para "I couldn't sleep,"
        t_line "so I called you."
        t_done )
};
const struct TextCmd BuenaPhoneRocketText[] = {
    text_start("Oh. Hi, <PLAY_G>!"
        t_para "You are how?"
        t_para "Aiyee! This isn't"
        t_line "the time for me to"
        t_para "be cracking silly"
        t_line "gag greetings!"
        t_para "The RADIO TOWER is"
        t_line "in deep trouble!"
        t_para "<PLAY_G>, you'd"
        t_line "better be careful!"
        t_done )
};
const struct TextCmd BuenaPhoneWentOutWithBenText[] = {
    text_start("The other day, I"
        t_line "went out to eat"
        t_para "with DJ BEN!"
        t_line "Isn't it great?"
        t_para "Not only that, he"
        t_line "said the music on"
        t_para "my program is"
        t_line "cool!"
        t_para "Oh, wow! Like,"
        t_line "what should I do?"
        t_para "…Oops, I have to"
        t_line "get ready for my"
        t_para "show! I'll catch"
        t_line "you later!"
        t_done )
};
const struct TextCmd BuenaPhoneReceptionistText[] = {
    text_start("You know the"
        t_line "receptionist at"
        t_cont "the RADIO TOWER?"
        t_para "'Welcome,' is all"
        t_line "she ever says."
        t_para "But she's really"
        t_line "the chattiest"
        t_para "person at the"
        t_line "RADIO TOWER."
        t_para "So she must be"
        t_line "holding back."
        t_para "Isn't that fun to"
        t_line "know?"
        t_para "Catch you later!"
        t_done )
};
const struct TextCmd BuenaPhoneLuckyNumberShowText[] = {
    text_start("Tell me, <PLAY_G>."
        t_line "Have you ever won"
        t_para "a prize on the"
        t_line "LUCKY NUMBER SHOW?"
        t_para "REED moans that"
        t_line "he's never won, so"
        t_para "he vows to keep"
        t_line "the show on the"
        t_cont "air till he does."
        t_para "Let's chat again!"
        t_done )
};
const struct TextCmd BuenaPhoneStressedFromWorkText[] = {
    text_start("You know, last"
        t_line "night…"
        t_para "I was so stressed"
        t_line "out from work, I"
        t_para "ate a ton of junk"
        t_line "food!"
        t_para "MARY and I have"
        t_line "this deal about"
        t_cont "losing weight…"
        t_para "This won't do…"
        t_para "Huh? What's the"
        t_line "weight?"
        t_para "This has to be a"
        t_line "total secret!"
        t_para "MARY weighs…"
        t_para "Aiyee! M-MARY!"
        t_para "Uh… Um… I… Sorry,"
        t_line "wrong number!"
        t_done )
};
const struct TextCmd BuenaPhoneProfessorOakText[] = {
    text_start("Yesterday, PROF."
        t_line "OAK was in the"
        t_para "studio to tape his"
        t_line "show."
        t_para "So I went over and"
        t_line "introduced myself."
        t_para "Get this--he tunes"
        t_line "in to my program!"
        t_para "Oh! Here comes"
        t_line "PROF.OAK again!"
        t_para "I'm going to chat"
        t_line "him up again!"
        t_para "Catch you later!"
        t_done )
};
const struct TextCmd BuenaPhoneGotAColdText[] = {
    text_start("…Cough, cough!"
        t_para "Uhm sorry uh got"
        t_line "uh code dite now."
        t_para "Buh uma pro so uh"
        t_line "hav to cover id ub"
        t_para "so no un notice"
        t_line "while uhm on air."
        t_para "Uh fidz muh voice"
        t_line "now."
        t_para "I'll catch you on"
        t_line "the fly. This has"
        t_cont "been BUENA!"
        t_done )
};
const struct TextCmd BuenaPhoneRadioCardQuestionsText[] = {
    text_start("Hey, <PLAY_G>."
        t_line "You won that RADIO"
        t_para "CARD by beating"
        t_line "the quiz at the"
        t_para "reception desk,"
        t_line "didn't you?"
        t_para "Guess what? I made"
        t_line "up the questions!"
        t_para "…Were they too"
        t_line "easy for you?"
        t_para "Well, let's chat"
        t_line "again!"
        t_done )
};
const struct TextCmd BuenaPhonePikachuFanClubText[] = {
    text_start("I'm elated that"
        t_line "more people are"
        t_para "taking part in my"
        t_line "PASSWORD show."
        t_para "But when PIKACHU"
        t_line "was the password,"
        t_para "it was uh… whew…"
        t_line "overwhelming."
        t_para "FAN CLUB people"
        t_line "came in out in"
        t_para "droves, shouting"
        t_line "'PIKACHU!' over"
        t_para "and over. I mean,"
        t_line "they were loud."
        t_para "Anyone tuning in"
        t_line "around then must"
        t_para "have been shocked"
        t_line "by the racket!"
        t_para "Anyway, back to"
        t_line "work for me!"
        t_para "Let's chat again!"
        t_done )
};
const struct TextCmd BuenaPhoneRadioTowerDirectorText[] = {
    text_start("Guess what?"
        t_line "The RADIO TOWER's"
        t_para "DIRECTOR is a big"
        t_line "fan of TV!"
        t_para "A while ago, a"
        t_line "fashion show on TV"
        t_para "said that black"
        t_line "suits were in."
        t_para "Now all he wears"
        t_line "are black suits."
        t_para "But it's a secret"
        t_line "that our DIRECTOR"
        t_para "is a TV fan, so if"
        t_line "you see him, don't"
        t_para "you dare mention"
        t_line "it!"
        t_para "Oh! The DIRECTOR"
        t_line "will be here soon!"
        t_para "Later! Tune into"
        t_line "my show!"
        t_done )
};
const struct TextCmd BuenaPhoneWhenDoYouRelaxText[] = {
    text_start("<PLAY_G>, tell me."
        t_para "When do you relax"
        t_line "the most?"
        t_para "For me, it has to"
        t_line "be in the studio"
        t_para "right after my"
        t_line "show, enjoying a"
        t_para "nice cup of tea."
        t_line "It's so pleasant"
        t_para "that it gradually"
        t_line "makes me drowsy…"
        t_para "<……> <……> <……>"
        t_para "<……> <……> <……>Zzz"
        t_para "Oops, I drifted"
        t_line "off just thinking"
        t_para "about it! How, uh…"
        t_line "embarrassing!"
        t_para "Please forget this"
        t_line "happened! Later!"
        t_done )
};
const struct TextCmd BuenaPhoneStarterPokemonText[] = {
    text_start("<PLAY_G>, what was"
        t_line "the first #MON"
        t_cont "you ever caught?"
        t_para "…Oh, really?"
        t_para "I've seen lots of"
        t_line "#MON around,"
        t_para "but I've never"
        t_line "caught one."
        t_para "I should give it a"
        t_line "try sometime."
        t_para "Did you know that"
        t_line "the first #MON"
        t_para "MARY caught was a"
        t_line "DROWZEE?"
        t_para "Isn't that so out"
        t_line "of character?"
        t_para "But MARY's DROWZEE"
        t_line "kept making her"
        t_para "fall asleep on the"
        t_line "job, so she traded"
        t_para "with a fan for a"
        t_line "MEOWTH."
        t_para "Let's chat about"
        t_line "#MON again!"
        t_para "Bye-bye!"
        t_done )
};
const struct TextCmd BuenaPhoneCompanyVacationText[] = {
    text_start("Guess what? All of"
        t_line "us from the RADIO"
        t_para "TOWER are going on"
        t_line "a company vacation"
        t_para "to the RADIO TOWER"
        t_line "in LAVENDER."
        t_para "We're wasting our"
        t_line "vacation on a trip"
        t_para "to another RADIO"
        t_line "TOWER?"
        t_para "I'd much rather go"
        t_line "to the beach!"
        t_para "<PLAY_G>, I hope"
        t_line "you have enough"
        t_para "fun for both of us"
        t_line "on your journey!"
        t_para "Bye-bye!"
        t_done )
};
const struct TextCmd BuenaPhoneBenAndFernText[] = {
    text_start("Did you know…?"
        t_para "BEN and FERN talk"
        t_line "on the phone for"
        t_para "hours about what"
        t_line "#MON music they"
        t_para "should play on"
        t_line "different days of"
        t_cont "the week."
        t_para "One time, FERN's"
        t_line "rapping style kind"
        t_para "of rubbed off on"
        t_line "BEN weirdly."
        t_para "So we ended up"
        t_line "enduring BEN's"
        t_para "silly, chilly, a"
        t_line "willy-nilly jive-"
        t_cont "talking shtick for"
        t_cont "a while."
        t_para "Let's chat again!"
        t_done )
};
const struct TextCmd BuenaPhoneGoingShoppingText[] = {
    text_start("I'm going shopping"
        t_line "with MARY and LILY"
        t_cont "soon."
        t_para "It'll be great if"
        t_line "GOLDENROD DEPT."
        t_para "STORE has a sale"
        t_line "on when we go…"
        t_para "<PLAY_G>, maybe we"
        t_line "can hook up too!"
        t_para "Catch you later!"
        t_done )
};
const struct TextCmd BuenaPhoneFavoriteSlotMachineAnswerText[] = {
    text_start("I'm thinking of"
        t_line "going to the GAME"
        t_para "CORNER tomorrow."
        t_line "It's been a while."
    #if defined(_CRYSTAL_AU)
        t_para "Some machines pays"
        t_line "out a lot."
    #else
        t_para "You see, I have my"
        t_line "favorite machine…"
        t_para "It pays out a lot,"
        t_line "I kid you not!"
    #endif
        t_para "Huh? Nuh-uh, it's"
        t_line "my secret!"
        t_para "You have to find"
        t_line "it yourself!"
        t_para "Catch you later!"
        t_done )
};
const struct TextCmd BuenaPhonePokegearAnswerText[] = {
    text_start("Hey, <PLAY_G>. You"
        t_line "use your #GEAR"
        t_para "to listen to the"
        t_line "radio, right?"
        t_para "I heard that you"
        t_line "can even display"
        t_para "town maps with"
        t_line "#GEAR."
        t_para "I have a bad sense"
        t_line "of direction, so"
        t_para "#GEAR would be"
        t_line "handy…"
        t_para "Anyway, thanks for"
        t_line "calling! Later!"
        t_done )
};
const struct TextCmd BuenaPhoneCoopedUpInRadioTowerAnswerText[] = {
    text_start("Is it sunny"
        t_line "outside today?"
        t_para "When you're cooped"
        t_line "up in the RADIO"
        t_para "TOWER as much as I"
        t_line "am, you lose touch"
        t_para "with the outside."
        t_line "It can be boring."
        t_para "Please call again!"
        t_done )
};
