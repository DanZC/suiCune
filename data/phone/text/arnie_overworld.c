#include "../../../constants.h"

const struct TextCmd ArnieAskNumber1Text[] = {
    text_start("Do you get the"
        t_line "feeling that there"
        t_para "are more rare"
        t_line "#MON around?"
        t_para "I'm positive there"
        t_line "are, so I look all"
        t_cont "the time."
        t_para "If I find one, I"
        t_line "want to share the"
        t_para "good news with"
        t_line "everyone I know."
        t_para "I know! Give me"
        t_line "your phone number."
        t_done )
};
const struct TextCmd ArnieAskNumber2Text[] = {
    text_start("I want to let"
        t_line "people know if I"
        t_cont "see rare #MON."
        t_para "Please give me"
        t_line "your phone number!"
        t_done )
};
const struct TextCmd ArnieNumberAcceptedText[] = {
    text_start("If I spot any"
        t_line "awesome #MON,"
        t_para "I'll be sure to"
        t_line "give you a call!"
        t_done )
};
const struct TextCmd ArnieNumberDeclinedText[] = {
    text_start("Aww! I want to"
        t_line "tell someone about"
        t_cont "my discoveries!"
        t_done )
};
const struct TextCmd ArniePhoneFullText[] = {
    text_start("There's no space"
        t_line "for my number."
        t_para "If you make room,"
        t_line "register me!"
        t_done )
};
const struct TextCmd ArnieRematchText[] = {
    text_start("It's my turn to"
        t_line "win now!"
        t_para "I've turned over a"
        t_line "new leaf!"
        t_done )
};
