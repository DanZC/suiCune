#include "../../../constants.h"

const struct TextCmd TullyAskNumber1Text[] = {
    text_start("Hey, you're trying"
        t_line "to be the ultimate"
        t_para "trainer too? Then"
        t_line "we're comrades!"
        t_para "If I find any more"
        t_line "items by the"
        t_para "water, I'll give"
        t_line "you some."
        t_para "Just give me your"
        t_line "phone number."
        t_done )
};
const struct TextCmd TullyAskNumber2Text[] = {
    text_start("If I find any more"
        t_line "items by the"
        t_para "water, I'll give"
        t_line "you some."
        t_para "Just give me your"
        t_line "phone number."
        t_done )
};
const struct TextCmd TullyNumberAcceptedText[] = {
    text_start("You'll be hearing"
        t_line "from me if I find"
        t_cont "something good."
        t_done )
};
const struct TextCmd TullyNumberDeclinedText[] = {
    text_start("Is that so? Then"
        t_line "I'll just have to"
        t_cont "use them myself."
        t_done )
};
const struct TextCmd TullyPhoneFullText[] = {
    text_start("Your phone list is"
        t_line "all filled up."
        t_para "Come back if you"
        t_line "make room for me."
        t_done )
};
const struct TextCmd TullyRematchText[] = {
    text_start("I've been doing"
        t_line "more than just"
        t_para "fishing since we"
        t_line "last met."
        t_para "You're in for a"
        t_line "big surprise!"
        t_done )
};
const struct TextCmd TullyGiftText[] = {
    text_start("Hey, there you"
        t_line "are!"
        t_para "Here's a gift, as"
        t_line "promised!"
        t_done )
};
const struct TextCmd TullyPackFullText[] = {
    text_start("Your PACK's full?"
        t_para "Come back later--"
        t_line "that'll do it."
        t_done )
};
