#include "../../../constants.h"

const struct TextCmd KenjiAskNumber1Text[] = {
    text_start("Our battle was"
        t_line "remarkable!"
        t_para "I wish for some-"
        t_line "thing to remember"
        t_cont "you by!"
        t_para "Perhaps your phone"
        t_line "number will do?"
        t_para "My training makes"
        t_line "it impossible to"
        t_cont "chat much, but…"
        t_done )
};
const struct TextCmd KenjiAskNumber2Text[] = {
    text_start("My training makes"
        t_line "chatting tough,"
        t_para "but will you take"
        t_line "down my number?"
        t_done )
};
const struct TextCmd KenjiNumberAcceptedText[] = {
    text_start("I must train"
        t_line "harder to become"
        t_cont "the mightiest!"
        t_done )
};
const struct TextCmd KenjiNumberDeclinedText[] = {
    text_start("If you decide you"
        t_line "want my number,"
        t_cont "come see me."
        t_done )
};
const struct TextCmd KenjiPhoneFullText[] = {
    text_start("Your phone appears"
        t_line "to be full."
        t_para "Come back later!"
        t_done )
};
const struct TextCmd KenjiGiftText[] = {
    text_start("I wish to thank"
        t_line "you, <PLAYER>!"
        t_para "I've been training"
        t_line "all alone…"
        t_para "I was happy that"
        t_line "you cared to call…"
        t_para "I want you to have"
        t_line "this!"
        t_done )
};
const struct TextCmd KenjiPackFullText[] = {
    text_start("Your strength will"
        t_line "not let you carry"
        t_para "another thing!"
        t_line "I will hold this"
        t_para "till you lighten"
        t_line "your PACK!"
        t_done )
};
