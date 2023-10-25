#include "../../../constants.h"

const struct TextCmd VanceAskNumber1Text[] = {
    text_start("You know, you are"
        t_line "really strong."
        t_para "But I don't want"
        t_line "to just slink off…"
        t_para "I know! Could I"
        t_line "get your number?"
        t_para "Let's meet up for"
        t_line "more battles!"
        t_done )
};
const struct TextCmd VanceAskNumber2Text[] = {
    text_start("I want to battle"
        t_line "tough trainers as"
        t_cont "often as I can!"
        t_para "Could I get your"
        t_line "number?"
        t_para "Let's meet up for"
        t_line "more battles!"
        t_done )
};
const struct TextCmd VanceNumberAcceptedText[] = {
    text_start("Don't forget to"
        t_line "come see me when I"
        t_cont "challenge you!"
        t_done )
};
const struct TextCmd VanceNumberDeclinedText[] = {
    text_start("A bird-user friend"
        t_line "isn't a bad thing"
        t_cont "to have, I think…"
        t_para "Won't you"
        t_line "reconsider?"
        t_done )
};
const struct TextCmd VancePhoneFullText[] = {
    text_start("Your phone's out"
        t_line "of memory. Delete"
        t_cont "a number for me!"
        t_done )
};
const struct TextCmd VanceRematchText[] = {
    text_start("Am I happy to see"
        t_line "you! I won't lose!"
        t_done )
};
const struct TextCmd VancePackFullText[] = {
    text_start("Oh, too bad. You"
        t_line "don't have room."
        t_para "I'll give it to"
        t_line "you next time!"
        t_done )
};
const struct TextCmd VanceRematchGiftText[] = {
    text_start("You are really,"
        t_line "really strong!"
        t_para "Thanks for taking"
        t_line "me on so often--I"
        t_para "learned a whole"
        t_line "lot from you."
        t_para "I know! This will"
        t_line "do as my thanks!"
        t_done )
};
