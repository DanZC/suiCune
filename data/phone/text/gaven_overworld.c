#include "../../../constants.h"

const struct TextCmd GavenAskNumber1Text[] = {
    text_start("Wow, you're tough."
        t_line "I haven't battled"
        t_para "that seriously in"
        t_line "a long time."
        t_para "Could I get your"
        t_line "phone number?"
        t_para "I'd like to battle"
        t_line "again when I heal"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and the"
        t_line "rest of my team."
        t_done )
};
const struct TextCmd GavenAskNumber2Text[] = {
    text_start("Could I get your"
        t_line "phone number?"
        t_para "I'd like to battle"
        t_line "again when I heal"
        t_para "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(" and the"
        t_line "rest of my team."
        t_done )
};
const struct TextCmd GavenNumberAcceptedText[] = {
    text_start("How should I beat"
        t_line "you? I'm tormented"
        t_para "by those thoughts"
        t_line "all the time…"
        t_done )
};
const struct TextCmd GavenNumberDeclinedText[] = {
    text_start("OK… I understand…"
        t_line "But if you change"
        t_para "your mind, give me"
        t_line "a shout anytime."
        t_done )
};
const struct TextCmd GavenPhoneFullText[] = {
    text_start("Your phone's"
        t_line "memory is full."
        t_para "You can't register"
        t_line "my number."
        t_done )
};
const struct TextCmd GavenRematchText[] = {
    text_start("Hi! I've been"
        t_line "waiting for you!"
        t_para "This time, I'm"
        t_line "going to win!"
        t_done )
};
