#include "../../../constants.h"

const struct TextCmd JoeyAskNumber1Text[] = {
    text_start("Listen, can I get"
        t_line "your phone number?"
        t_para "I'll ring you for"
        t_line "some battles."
        t_para "I'm a rookie too, "
        t_line "so I think it'd be"
        t_cont "a good motivator."
        t_done )
};
const struct TextCmd JoeyAskNumber2Text[] = {
    text_start("Can I get your"
        t_line "phone number?"
        t_para "I don't want to"
        t_line "lose against you!"
        t_para "We have to battle"
        t_line "again, OK?"
        t_done )
};
const struct TextCmd JoeyNumberAcceptedText[] = {
    text_start("I'll ring you"
        t_line "whenever I get the"
        t_cont "urge to battle!"
        t_done )
};
const struct TextCmd JoeyNumberDeclinedText[] = {
    text_start("Oh, all right…"
        t_para "But I won't lose"
        t_line "to you again!"
        t_done )
};
const struct TextCmd JoeyPhoneFullText[] = {
    text_start("Huh, what? Your"
        t_line "phone's full."
        t_done )
};
const struct TextCmd JoeyRematchText[] = {
    text_start("I've been waiting!"
        t_line "Let's battle now!"
        t_done )
};
const struct TextCmd JoeyPackFullText[] = {
    text_start("Hey, wait! Your"
        t_line "PACK is stuffed!"
        t_para "Well, we'll leave"
        t_line "it till next time."
        t_done )
};
const struct TextCmd JoeyRematchGiftText[] = {
    text_start("And yet another"
        t_line "loss…"
        t_para "No doubt about"
        t_line "it--you're tough."
        t_para "Being beaten this"
        t_line "often actually"
        t_cont "feels good now!"
        t_para "Here, take this. "
        t_line "Use it to get even"
        t_para "tougher. That will"
        t_line "toughen me up too!"
        t_done )
};
