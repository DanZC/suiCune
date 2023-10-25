#include "../../../constants.h"

const struct TextCmd BethAskNumber1Text[] = {
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
const struct TextCmd BethAskNumber2Text[] = {
    text_start("By challenging a"
        t_line "tough trainer like"
        t_para "you, I think I can"
        t_line "get better too."
        t_para "So how about it?"
        t_para "Would you give me"
        t_line "your phone number?"
        t_done )
};
const struct TextCmd BethNumberAcceptedText[] = {
    text_start("Let's battle again"
        t_line "sometime!"
        t_done )
};
const struct TextCmd BethNumberDeclinedText[] = {
    text_start("That's too bad…"
        t_para "Let me know if you"
        t_line "change your mind."
        t_done )
};
const struct TextCmd BethPhoneFullText[] = {
    text_start("Oh no. Your phone"
        t_line "is out of memory."
        t_done )
};
const struct TextCmd BethRematchText[] = {
    text_start("You sure kept me"
        t_line "waiting! Let's go!"
        t_done )
};
