#include "../../../constants.h"

const struct TextCmd BillPhoneMornGreetingText[] = {
    text_start("Good morning!"
        t_para "This is the #-"
        t_line "MON STORAGE SYSTEM"
        t_para "ADMINISTRATION"
        t_line "SERVICE."
        t_done )
};
const struct TextCmd BillPhoneDayGreetingText[] = {
    text_start("Good day!"
        t_para "This is the #-"
        t_line "MON STORAGE SYSTEM"
        t_para "ADMINISTRATION"
        t_line "SERVICE."
        t_done )
};
const struct TextCmd BillPhoneNiteGreetingText[] = {
    text_start("Good evening!"
        t_para "This is the #-"
        t_line "MON STORAGE SYSTEM"
        t_para "ADMINISTRATION"
        t_line "SERVICE."
        t_done )
};
const struct TextCmd BillPhoneGenericText[] = {
    text_start("Who's calling?"
        t_para "<PLAY_G>, is it?"
        t_line "Hang on a sec…"
        t_para "<……>"
        t_line "<……>"
        t_done )
};
const struct TextCmd BillPhoneNotFullText[] = {
    text_start("Thanks for"
        t_line "waiting!"
        t_para "<PLAY_G>, your BOX"
        t_line "has room for @")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(
        t_cont "more #MON."
        t_para "Get out there and"
        t_line "fill it up!"
        t_done )
};
const struct TextCmd BillPhoneNearlyFullText[] = {
    text_start("Thanks for"
        t_line "waiting!"
        t_para "<PLAY_G>, your BOX"
        t_line "has room for only"
        t_cont "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" more #MON."
        t_para "Maybe you should"
        t_line "switch your BOX."
        t_done )
};
const struct TextCmd BillPhoneFullText[] = {
    text_start("Thanks for"
        t_line "waiting!"
        t_para "<PLAY_G>, your BOX"
        t_line "is full!"
        t_para "You'll have to"
        t_line "switch BOXES if"
        t_para "you want to catch"
        t_line "more #MON."
        t_done )
};
const struct TextCmd BillPhoneNewlyFullText[] = {
    text_start("Hi, <PLAY_G>?"
        t_line "It's me, BILL!"
        t_para "Thanks for using"
        t_line "my STORAGE SYSTEM."
        t_para "That last #MON"
        t_line "you sent filled"
        t_cont "your BOX up."
        t_para "You'll have to"
        t_line "switch BOXES if"
        t_para "you want to catch"
        t_line "more #MON."
        t_para "Bye now!"
        t_done )
};
