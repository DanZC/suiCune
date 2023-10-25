#include "../../../constants.h"

const struct TextCmd RalphAskNumber1Text[] = {
    text_start("Don't young people"
        t_line "fish anymore?"
        t_para "I've seen rare"
        t_line "#MON while I've"
        t_cont "been fishing…"
        t_para "You young people"
        t_line "like that, right?"
        t_para "Want to trade"
        t_line "phone numbers?"
        t_para "I'll let you know"
        t_line "if I see anything."
        t_done )
};
const struct TextCmd RalphAskNumber2Text[] = {
    text_start("Hm? So you do want"
        t_line "me to phone if I"
        t_cont "see rare #MON?"
        t_done )
};
const struct TextCmd RalphNumberAcceptedText[] = {
    text_start("Yep, phone if I"
        t_line "see rare #MON."
        t_para "Don't worry, I"
        t_line "won't forget!"
        t_done )
};
const struct TextCmd RalphNumberDeclinedText[] = {
    text_start("Oh…"
        t_line "My own kids won't"
        t_para "even give me their"
        t_line "phone numbers…"
        t_para "Is that how young"
        t_line "people are today?"
        t_done )
};
const struct TextCmd RalphPhoneFullText[] = {
    text_start("Your phone's"
        t_line "memory is full."
        t_para "It seems that"
        t_line "young people all"
        t_cont "have #GEAR."
        t_done )
};
const struct TextCmd RalphRematchText[] = {
    text_start("Hey, kid!"
        t_para "No losing for me"
        t_line "this day!"
        t_done )
};
