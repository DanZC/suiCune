#include "../../../constants.h"

const struct TextCmd BeverlyAskNumber1Text[] = {
    text_start("Your MARILL is so"
        t_line "cute and adorable!"
        t_para "You love #MON"
        t_line "just like I do!"
        t_para "Want to trade"
        t_line "phone numbers?"
        t_para "Let's chat! It'll"
        t_line "be so much fun!"
        t_done )
};
const struct TextCmd BeverlyAskNumber2Text[] = {
    text_start("Your MARILL is so"
        t_line "cute and adorable!"
        t_para "We should chat, it"
        t_line "will be fun."
        t_para "Can I have your"
        t_line "phone number?"
        t_done )
};
const struct TextCmd BeverlyNumberAcceptedText[] = {
    text_start("To be honest, I"
        t_line "want a MARILL."
        t_para "But I make do with"
        t_line "my cute SNUBBULL."
        t_done )
};
const struct TextCmd BeverlyNumberDeclinedText[] = {
    text_start("Oh… That's"
        t_line "disappointing…"
        t_para "Goodbye, MARILL…"
        t_done )
};
const struct TextCmd BeverlyPhoneFullText[] = {
    text_start("Oh? Your phone's"
        t_line "memory is full."
        t_done )
};
const struct TextCmd BeverlyGiftText[] = {
    text_start("Oh? <PLAYER>? "
        t_line "I waited here for"
        t_para "you. I brought you"
        t_line "a little gift."
        t_done )
};
const struct TextCmd BeverlyPackFullText[] = {
    text_start("Oh?"
        t_line "You have no room."
        t_para "Please come back"
        t_line "for it later."
        t_done )
};
