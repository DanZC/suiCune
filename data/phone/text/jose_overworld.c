#include "../../../constants.h"

const struct TextCmd JoseAskNumber1Text[] = {
    text_start("If my @")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_line "sees anything"
        t_para "pretty, it goes"
        t_line "and gets it."
        t_para "Do you like pretty"
        t_line "things?"
        t_para "I could share if"
        t_line "it gets some more."
        t_para "What's your phone"
        t_line "number? I'll call."
        t_para "Don't expect a"
        t_line "whole lot, OK?"
        t_done )
};
const struct TextCmd JoseAskNumber2Text[] = {
    text_start("Do you like pretty"
        t_line "things?"
        t_para "I could share if"
        t_line "FARFETCH'D goes"
        t_cont "and gets more."
        t_para "What's your phone"
        t_line "number? I'll call."
        t_done )
};
const struct TextCmd JoseNumberAcceptedText[] = {
    text_start("I'll call you as"
        t_line "soon as I get"
        t_cont "something pretty."
        t_done )
};
const struct TextCmd JoseNumberDeclinedText[] = {
    text_start("You sure? Well,"
        t_line "tell me if you"
        t_cont "change your mind."
        t_done )
};
const struct TextCmd JosePhoneFullText[] = {
    text_start("Huh? Your phone"
        t_line "list is full."
        t_done )
};
const struct TextCmd JoseRematchText[] = {
    text_start("Tweet! Tweeeet!"
        t_para "Kept me waiting!"
        t_line "Go, FARFETCH'D!"
        t_done )
};
const struct TextCmd JoseGiftText[] = {
    text_start("Kept me waiting!"
        t_line "Look, this is it!"
        t_para "See? Isn't it some"
        t_line "kind of pretty?"
        t_done )
};
const struct TextCmd JosePackFullText[] = {
    text_start("Huh? You don't"
        t_line "have anywhere to"
        t_para "put this. Better"
        t_line "come back for it."
        t_done )
};
