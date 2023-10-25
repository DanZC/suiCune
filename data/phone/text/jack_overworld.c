#include "../../../constants.h"

const struct TextCmd JackAskNumber1Text[] = {
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
const struct TextCmd JackAskNumber2Text[] = {
    text_start("Want to trade"
        t_line "battle tips?"
        t_para "I'll phone if I"
        t_line "get good info."
        t_para "Would you tell me"
        t_line "your number?"
        t_done )
};
const struct TextCmd JackNumberAcceptedText[] = {
    text_start("I'll call you if I"
        t_line "hear anything!"
        t_done )
};
const struct TextCmd JackNumberDeclinedText[] = {
    text_start("Oh, OK. Too bad…"
        t_para "Well, if you ever"
        t_line "want my number,"
        t_cont "come see me, OK?"
        t_done )
};
const struct TextCmd JackPhoneFullText[] = {
    text_start("Oh?"
        t_line "Your phone's full."
        t_para "It can't register"
        t_line "my number."
        t_done )
};
const struct TextCmd JackRematchText[] = {
    text_start("Hi, I was waiting"
        t_line "for you to show!"
        t_para "Let's get started"
        t_line "right away!"
        t_done )
};
