#include "../../../constants.h"

const struct TextCmd ChadAskNumber1Text[] = {
    text_start("Huh? Is that thing"
        t_line "a #DEX? Have"
        t_cont "you met PROF.OAK?"
        t_para "Huh? You have? "
        t_line "That's way cool!"
        t_para "I have a dream of"
        t_line "becoming a #MON"
        t_para "researcher like"
        t_line "PROF.OAK."
        t_para "May I please have"
        t_line "your phone number?"
        t_para "We should chat"
        t_line "about PROF.OAK."
        t_para "I'm sure it will"
        t_line "be loads of fun!"
        t_done )
};
const struct TextCmd ChadAskNumber2Text[] = {
    text_start("May I please have"
        t_line "your phone number?"
        t_para "We should chat"
        t_line "about PROF.OAK."
        t_para "I'm sure it will"
        t_line "be loads of fun!"
        t_done )
};
const struct TextCmd ChadNumberAcceptedText[] = {
    text_start("You must listen to"
        t_line "PROF.OAK'S #MON"
        t_cont "TALK, right?"
        t_done )
};
const struct TextCmd ChadNumberDeclinedText[] = {
    text_start("Oh… I wish I had a"
        t_line "chance to meet"
        t_cont "PROF.OAK…"
        t_done )
};
const struct TextCmd ChadPhoneFullText[] = {
    text_start("Your phone list is"
        t_line "completely full!"
        t_done )
};
const struct TextCmd ChadRematchText[] = {
    text_start("I've been waiting!"
        t_line "Let's battle now!"
        t_done )
};
