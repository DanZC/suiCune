#include "../../../constants.h"

const struct TextCmd AlanAskNumber1Text[] = {
    text_start("Reading textbooks"
        t_line "is worthwhile"
        t_cont "every so often."
        t_para "When I'm reading"
        t_line "and walking, I"
        t_cont "have to look down."
        t_para "So I notice items"
        t_line "on the ground."
        t_para "Next time I find"
        t_line "something, I'll"
        t_cont "give it to you."
        t_para "May I have your"
        t_line "phone number?"
        t_done )
};
const struct TextCmd AlanAskNumber2Text[] = {
    text_start("If I find some-"
        t_line "thing, it's yours."
        t_para "So may I have your"
        t_line "phone number?"
        t_done )
};
const struct TextCmd AlanNumberAcceptedText[] = {
    text_start("I'll call you as"
        t_line "soon as I find"
        t_para "something. You can"
        t_line "count on it!"
        t_done )
};
const struct TextCmd AlanNumberDeclinedText[] = {
    text_start("Oh… I thought it"
        t_line "would be a good"
        t_para "break to call you"
        t_line "when I'm studying…"
        t_done )
};
const struct TextCmd AlanPhoneFullText[] = {
    text_start("There's no room"
        t_line "for my number."
        t_done )
};
const struct TextCmd AlanRematchText[] = {
    text_start("I waited around"
        t_line "for you!"
        t_para "I'm thoroughly"
        t_line "prepared today!"
        t_done )
};
const struct TextCmd AlanGiftText[] = {
    text_start("This, this! This"
        t_line "is yours! Ta-da!"
        t_done )
};
const struct TextCmd AlanPackFullText[] = {
    text_start("Whoops!"
        t_para "You can't carry"
        t_line "any more items!"
        t_para "I'll hold it until"
        t_line "next time."
        t_done )
};
