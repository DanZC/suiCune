#include "../../../constants.h"

const struct TextCmd AnthonyAskNumber1Text[] = {
    text_start("By the way, I'm a"
        t_line "HIKER, so I often"
        t_para "go to mountains"
        t_line "and caves."
        t_para "I occasionally see"
        t_line "rare #MON."
        t_para "I could call you"
        t_line "the next time I"
        t_cont "see one."
        t_para "Feel like swapping"
        t_line "phone numbers?"
        t_done )
};
const struct TextCmd AnthonyAskNumber2Text[] = {
    text_start("I could call you"
        t_line "when I see some"
        t_cont "rare #MON."
        t_para "Feel like swapping"
        t_line "phone numbers?"
        t_done )
};
const struct TextCmd AnthonyNumberAcceptedText[] = {
    text_start("Be patient. I'll"
        t_line "find some rare"
        t_cont "#MON for you!"
        t_done )
};
const struct TextCmd AnthonyNumberDeclinedText[] = {
    text_start("You're cold. I may"
        t_line "as well head to"
        t_cont "the mountains…"
        t_done )
};
const struct TextCmd AnthonyPhoneFullText[] = {
    text_start("Your phone's full."
        t_para "It can't register"
        t_line "my phone number."
        t_done )
};
const struct TextCmd AnthonyRematchText[] = {
    text_start("All righty, then!"
        t_para "My #MON and I"
        t_line "are raring to go!"
        t_done )
};
