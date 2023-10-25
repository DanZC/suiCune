#include "../../../constants.h"

const struct TextCmd IrwinAskNumber1Text[] = {
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
const struct TextCmd IrwinAskNumber2Text[] = {
    text_start("You will tell me"
        t_line "your phone number?"
        t_done )
};
const struct TextCmd IrwinNumberAcceptedText[] = {
    text_start("Wow! Gee, thanks!"
        t_line "Now I can call you"
        t_para "anytime, whether"
        t_line "anything's up or"
        t_para "not. You know,"
        t_line "just to chat!"
        t_done )
};
const struct TextCmd IrwinNumberDeclinedText[] = {
    text_start("Oh, but…"
        t_line "I'm not dangerous!"
        t_para "I just want to"
        t_line "call and chat"
        t_para "about everything"
        t_line "and nothing!"
        t_done )
};
const struct TextCmd IrwinPhoneFullText[] = {
    text_start("Your phone list is"
        t_line "already full…"
        t_para "You must be really"
        t_line "popular…"
        t_done )
};
