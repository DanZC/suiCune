#include "../../../constants.h"

const struct TextCmd ReenaAskNumber1Text[] = {
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
const struct TextCmd ReenaAskNumber2Text[] = {
    text_start("Give me your phone"
        t_line "number!"
        t_para "You are going to"
        t_line "be my practice"
        t_cont "partner!"
        t_done )
};
const struct TextCmd ReenaNumberAcceptedText[] = {
    text_start("Don't be too proud"
        t_line "about beating me!"
        t_para "It was a fluke!"
        t_done )
};
const struct TextCmd ReenaNumberDeclinedText[] = {
    text_start("I don't believe"
        t_line "it! You're going"
        t_cont "to regret this!"
        t_done )
};
const struct TextCmd ReenaPhoneFullText[] = {
    text_start("What? Your phone"
        t_line "list has no room!"
        t_done )
};
const struct TextCmd ReenaRematchText[] = {
    text_start("What took you?"
        t_line "Start right away!"
        t_done )
};
