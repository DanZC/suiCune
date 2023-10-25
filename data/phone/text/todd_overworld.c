#include "../../../constants.h"

const struct TextCmd ToddAskNumber1Text[] = {
    text_start("From here, I can"
        t_line "see GOLDENROD's"
        t_para "DEPT.STORE. They"
        t_line "have bargain sales"
        t_para "up on the rooftop"
        t_line "every so often."
        t_para "Could I get your"
        t_line "phone number?"
        t_para "I'll call you when"
        t_line "they have a sale."
        t_done )
};
const struct TextCmd ToddAskNumber2Text[] = {
    text_start("If you give me"
        t_line "your number, I'll"
        t_para "call you when they"
        t_line "have a sale."
        t_done )
};
const struct TextCmd ToddNumberAcceptedText[] = {
    text_start("I check GOLDENROD"
        t_line "DEPT.STORE every"
        t_para "day, so I know"
        t_line "when there's a"
        t_cont "sale."
        t_done )
};
const struct TextCmd ToddNumberDeclinedText[] = {
    text_start("Anyway…"
        t_para "If you're short on"
        t_line "money, take down"
        t_cont "my number."
        t_para "I'll call you when"
        t_line "there's a sale."
        t_done )
};
const struct TextCmd ToddPhoneFullText[] = {
    text_start("Your phone doesn't"
        t_line "have enough memory"
        t_cont "for more numbers."
        t_done )
};
const struct TextCmd ToddRematchText[] = {
    text_start("I waited for you!"
        t_line "I even cut back my"
        t_para "shopping to raise"
        t_line "my #MON better!"
        t_done )
};
// This is a duplicate of CamperToddSaleText in maps/Route34.asm.
const struct TextCmd ToddSaleText[] = {
    text_start("Shopping under the"
        t_line "sky!"
        t_para "It feels so nice"
        t_line "up on a rooftop."
        t_done )
};
