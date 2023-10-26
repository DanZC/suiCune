#include "../../../constants.h"

const struct TextCmd MomPhoneGreetingText[] = {
    text_start("Hello?"
        t_para "Oh, hi, <PLAYER>!"
        t_line "Working hard?"
        t_done )
};
const struct TextCmd MomPhoneLandmarkText[] = {
    text_start("Oh, so you're in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("…"
        t_para "Isn't that where"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer4))
    text_start(
        t_para "is? Did you go"
        t_line "take a look?"
        t_done )
};
const struct TextCmd MomPhoneGenericAreaText[] = {
    text_start("Really, you're in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "I've never gone"
        t_line "there. That's kind"
        t_cont "of neat, <PLAYER>."
        t_done )
};
const struct TextCmd MomPhoneNewBarkText[] = {
    text_start("What? You're in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "Come see your MOM"
        t_line "sometime!"
        t_done )
};
const struct TextCmd MomPhoneCherrygroveText[] = {
    text_start("You're visiting"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "How about coming"
        t_line "home for a bit?"
        t_done )
};
const struct TextCmd MomOtherAreaText[] = {
    text_start("Wow, you're in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "Good luck on your"
        t_line "#MON quest!"
        t_done )
};
const struct TextCmd MomDeterminedText[] = {
    text_start("That sounds really"
        t_line "tough."
        t_para "But, <PLAYER>, I"
        t_line "know you're really"
        t_para "determined. You'll"
        t_line "be OK, right?"
        t_done )
};
const struct TextCmd MomCheckBalanceText[] = {
    text_start("By the way, you've"
        t_line "saved up ¥@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Do you want to"
        t_line "keep on saving?"
        t_done )
};
const struct TextCmd MomImportantToSaveText[] = {
    text_start("It's important to"
        t_line "save your money."
        t_done )
};
const struct TextCmd MomYoureNotSavingText[] = {
    text_start("Oh, <PLAYER>,"
        t_line "you're not saving"
        t_para "any money. Would"
        t_line "you like to save?"
        t_done )
};
const struct TextCmd MomYouveSavedText[] = {
    text_start("By the way, you've"
        t_line "saved up ¥@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Want to start"
        t_line "saving again?"
        t_done )
};
const struct TextCmd MomOKIllSaveText[] = {
    text_start("OK. I'll save your"
        t_line "money."
        t_done )
};
const struct TextCmd MomPhoneWontSaveMoneyText[] = {
    text_start("OK. I won't save"
        t_line "your money."
        t_done )
};
const struct TextCmd MomPhoneHangUpText[] = {
    text_start("<PLAYER>, keep it"
        t_line "up! I'm rooting"
        t_cont "for you, baby!"
        t_done )
};
const struct TextCmd MomPhoneNoPokemonText[] = {
    text_start("Hello?"
        t_para "Oh, hi, <PLAYER>!"
        t_line "Wasn't PROF.ELM"
        t_cont "waiting for you?"
        t_done )
};
const struct TextCmd MomPhoneNoPokedexText[] = {
    text_start("Hello?"
        t_para "Oh, hi, <PLAYER>!"
        t_line "You're on a big"
        t_para "mission for PROF."
        t_line "ELM? Be good!"
        t_done )
};
const struct TextCmd MomPhoneNoGymQuestText[] = {
    text_start("Hello?"
        t_para "Hi, <PLAYER>! If"
        t_line "you're done with"
        t_para "your errand come"
        t_line "on home, dear."
        t_done )
};
const struct TextCmd MomPhoneLectureText[] = {
    text_start("Hello?"
        t_para "…… <PLAYER>?"
        t_line "I heard from PROF."
        t_para "ELM that you went"
        t_line "on a long trip."
        t_para "I wish you would"
        t_line "have told me…"
        t_para "What about money?"
        t_line "Should I save it?"
        t_done )
};
