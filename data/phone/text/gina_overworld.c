#include "../../../constants.h"

const struct TextCmd GinaAskNumber1Text[] = {
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
const struct TextCmd GinaAskNumber2Text[] = {
    text_start("If I find an item,"
        t_line "you can have it!"
        t_para "Want to give me"
        t_line "your number?"
        t_done )
};
const struct TextCmd GinaNumberAcceptedText[] = {
    text_start("I'll call as soon"
        t_line "as I get anything!"
        t_done )
};
const struct TextCmd GinaNumberDeclinedText[] = {
    text_start("Is that so? Well,"
        t_line "I'll still be"
        t_cont "rooting for you!"
        t_done )
};
const struct TextCmd GinaPhoneFullText[] = {
    text_start("But your phone is"
        t_line "all filled up!"
        t_done )
};
const struct TextCmd GinaRematchText[] = {
    text_start("I've been waiting!"
        t_para "I've gotten a bit"
        t_line "better at this!"
        t_done )
};
const struct TextCmd GinaGiftText[] = {
    text_start("So you're finally"
        t_line "here!"
        t_para "I think this will"
        t_line "make you happy."
        t_done )
};
const struct TextCmd GinaPackFullText[] = {
    text_start("Your PACK looks"
        t_line "completely full."
        t_para "I'll have to hold"
        t_line "on to this."
        t_done )
};
