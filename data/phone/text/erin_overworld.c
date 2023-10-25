#include "../../../constants.h"

const struct TextCmd ErinAskNumber1Text[] = {
    text_start("It really made me"
        t_line "angry to lose."
        t_para "I'll have to train"
        t_line "much harder…"
        t_para "Here's my number."
        t_line "I'm ERIN--don't"
        t_para "forget! Want to"
        t_line "battle me again?"
        t_done )
};
const struct TextCmd ErinAskNumber2Text[] = {
    text_start("I want to battle"
        t_line "with you again."
        t_para "Do you want to"
        t_line "exchange numbers?"
        t_done )
};
const struct TextCmd ErinNumberAcceptedText[] = {
    text_start("I'll remember to"
        t_line "call when I want"
        t_cont "to battle again!"
        t_done )
};
const struct TextCmd ErinNumberDeclinedText[] = {
    text_start("Oh… I'm sad…"
        t_line "If you do want to"
        t_para "battle, come see"
        t_line "ERIN--that's me!"
        t_done )
};
const struct TextCmd ErinPhoneFullText[] = {
    text_start("Oh no. Your phone"
        t_line "is all filled up."
        t_done )
};
const struct TextCmd ErinRematchText[] = {
    text_start("Yay! I waited!"
        t_line "Let's start now!"
        t_done )
};
const struct TextCmd ErinPackFullText[] = {
    text_start("That's too bad!"
        t_line "You have no room…"
        t_para "I'll give it to"
        t_line "you another time."
        t_done )
};
const struct TextCmd ErinRematchGiftText[] = {
    text_start("Aww… I lost again!"
        t_para "I wonder how many"
        t_line "times that is…"
        t_para "Thanks for coming!"
        t_line "Here's a present!"
        t_done )
};
