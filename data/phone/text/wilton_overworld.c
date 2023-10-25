#include "../../../constants.h"

const struct TextCmd WiltonAskNumber1Text[] = {
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
const struct TextCmd WiltonAskNumber2Text[] = {
    text_start("If I snag an item"
        t_line "while I'm fishing,"
        t_para "it's yours. What's"
        t_line "your number?"
        t_done )
};
const struct TextCmd WiltonNumberAcceptedText[] = {
    text_start("If I snag anything"
        t_line "good, I'll be sure"
        t_cont "to let you know."
        t_done )
};
const struct TextCmd WiltonNumberDeclinedText[] = {
    text_start("All right… Come"
        t_line "back if you have a"
        t_cont "change of heart."
        t_done )
};
const struct TextCmd WiltonPhoneFullText[] = {
    text_start("You can't register"
        t_line "another number."
        t_done )
};
const struct TextCmd WiltonRematchText[] = {
    text_start("Argh! You startled"
        t_line "POLIWAG into"
        t_cont "fleeing again!"
        t_done )
};
const struct TextCmd WiltonGiftText[] = {
    text_start("So here you are."
        t_para "See this?"
        t_line "I snagged it just"
        t_para "a little while"
        t_line "ago. It's yours."
        t_done )
};
const struct TextCmd WiltonPackFullText[] = {
    text_start("Your PACK's full?"
        t_para "I'll give it to"
        t_line "you later."
        t_done )
};
