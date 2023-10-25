#include "../../../constants.h"

const struct TextCmd ParryAskNumber1Text[] = {
    text_start("Sheesh, the way"
        t_line "you attacked! That"
        t_para "was something! We"
        t_line "should meet again!"
        t_para "How about giving"
        t_line "me your number?"
        t_done )
};
const struct TextCmd ParryAskNumber2Text[] = {
    text_start("So you want to"
        t_line "register my phone"
        t_para "number for a re-"
        t_line "match, huh?"
        t_done )
};
const struct TextCmd ParryNumberAcceptedText[] = {
    text_start("I'll call you"
        t_line "whenever I feel"
        t_cont "like battling!"
        t_done )
};
const struct TextCmd ParryNumberDeclinedText[] = {
    text_start("No? That's fine."
        t_para "A definite no is"
        t_line "easy to take!"
        t_para "I'll be right here"
        t_line "when you're ready"
        t_cont "for a rematch."
        t_done )
};
const struct TextCmd ParryPhoneFullText[] = {
    text_start("Oh? There's no"
        t_line "room to register"
        t_cont "my phone number."
        t_done )
};
const struct TextCmd ParryRematchText[] = {
    text_start("Hey, here comes"
        t_line "the kid! Let's go!"
        t_para "Ready for my usual"
        t_line "no-brainer, all-"
        t_cont "out offense?"
        t_done )
};
const struct TextCmd ParryPackFullText[] = {
    text_start("Your PACK looks"
        t_line "stuffed full!"
        t_para "You can't have"
        t_line "this now."
        t_done )
};
const struct TextCmd ParryRematchGiftText[] = {
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
