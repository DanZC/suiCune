#include "../../../constants.h"

const struct TextCmd WadeAskNumber1Text[] = {
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
const struct TextCmd WadeAskNumber2Text[] = {
    text_start("When I'm in the"
        t_line "grass, I find all"
        t_cont "kinds of BERRIES."
        t_para "If you'd like,"
        t_line "I'll share some."
        t_para "Could I get your"
        t_line "phone number?"
        t_done )
};
const struct TextCmd WadeNumberAcceptedText[] = {
    text_start("You'll hear from"
        t_line "me as soon as I"
        t_para "find anything that"
        t_line "you might like."
        t_done )
};
const struct TextCmd WadeNumberDeclinedText[] = {
    text_start("Oh well. Don't be"
        t_line "shy if you want to"
        t_cont "get my number."
        t_done )
};
const struct TextCmd WadePhoneFullText[] = {
    text_start("Your phone list"
        t_line "has no room for my"
        t_cont "number."
        t_done )
};
const struct TextCmd WadeRematchText[] = {
    text_start("I was waiting for"
        t_line "you. Let's battle!"
        t_done )
};
const struct TextCmd WadeGiftText[] = {
    text_start("Good to see you!"
        t_line "See? This is what"
        t_para "I found."
        t_line "It's for you!"
        t_done )
};
const struct TextCmd WadePackFullText[] = {
    text_start("Oops, your PACK's"
        t_line "full. Too bad."
        t_para "You should come"
        t_line "back for it later."
        t_done )
};
