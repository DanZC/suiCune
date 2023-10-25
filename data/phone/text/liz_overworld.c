#include "../../../constants.h"

const struct TextCmd LizAskNumber1Text[] = {
    text_start("Oh? You're on a"
        t_line "big journey to see"
        t_cont "the sights? Neat!"
        t_para "Let's be friends!"
        t_line "Can I have your"
        t_cont "phone number?"
        t_para "I want to hear"
        t_line "about everything"
        t_cont "you've seen!"
        t_done )
};
const struct TextCmd LizAskNumber2Text[] = {
    text_start("Let's be friends!"
        t_line "Can I have your"
        t_cont "phone number?"
        t_para "I want to hear"
        t_line "about everything"
        t_cont "you've seen!"
        t_done )
};
const struct TextCmd LizNumberAcceptedText[] = {
    text_start("I'll telephone you"
        t_line "if I hear anything"
        t_cont "interesting."
        t_done )
};
const struct TextCmd LizNumberDeclinedText[] = {
    text_start("Aww… You won't be"
        t_line "my friend?"
        t_done )
};
const struct TextCmd LizPhoneFullText[] = {
    text_start("Wait! Your phone"
        t_line "list is filled up!"
        t_done )
};
const struct TextCmd LizRematchText[] = {
    text_start("You're late! Let's"
        t_line "get started now!"
        t_done )
};
