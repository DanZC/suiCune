#include "../../../constants.h"

const txt_cmd_s MomPhoneGreetingText[] = {
    text_start("Hello?"
        t_para "Oh, hi, <PLAYER>!"
        t_line "Working hard?"
        t_done )
};
const txt_cmd_s MomPhoneLandmarkText[] = {
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
const txt_cmd_s MomPhoneGenericAreaText[] = {
    text_start("Really, you're in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "I've never gone"
        t_line "there. That's kind"
        t_cont "of neat, <PLAYER>."
        t_done )
};
const txt_cmd_s MomPhoneNewBarkText[] = {
    text_start("What? You're in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "Come see your MOM"
        t_line "sometime!"
        t_done )
};
const txt_cmd_s MomPhoneCherrygroveText[] = {
    text_start("You're visiting"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "How about coming"
        t_line "home for a bit?"
        t_done )
};
const txt_cmd_s MomOtherAreaText[] = {
    text_start("Wow, you're in"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("?"
        t_para "Good luck on your"
        t_line "#MON quest!"
        t_done )
};
const txt_cmd_s MomDeterminedText[] = {
    text_start("That sounds really"
        t_line "tough."
        t_para "But, <PLAYER>, I"
        t_line "know you're really"
        t_para "determined. You'll"
        t_line "be OK, right?"
        t_done )
};
const txt_cmd_s MomCheckBalanceText[] = {
    text_start("By the way, you've"
        t_line "saved up ¥@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Do you want to"
        t_line "keep on saving?"
        t_done )
};
const txt_cmd_s MomImportantToSaveText[] = {
    text_start("It's important to"
        t_line "save your money."
        t_done )
};
const txt_cmd_s MomYoureNotSavingText[] = {
    text_start("Oh, <PLAYER>,"
        t_line "you're not saving"
        t_para "any money. Would"
        t_line "you like to save?"
        t_done )
};
const txt_cmd_s MomYouveSavedText[] = {
    text_start("By the way, you've"
        t_line "saved up ¥@")
    text_ram(wram_ptr(wStringBuffer3))
    text_start("."
        t_para "Want to start"
        t_line "saving again?"
        t_done )
};
const txt_cmd_s MomOKIllSaveText[] = {
    text_start("OK. I'll save your"
        t_line "money."
        t_done )
};
const txt_cmd_s MomPhoneWontSaveMoneyText[] = {
    text_start("OK. I won't save"
        t_line "your money."
        t_done )
};
const txt_cmd_s MomPhoneHangUpText[] = {
    text_start("<PLAYER>, keep it"
        t_line "up! I'm rooting"
        t_cont "for you, baby!"
        t_done )
};
const txt_cmd_s MomPhoneNoPokemonText[] = {
    text_start("Hello?"
        t_para "Oh, hi, <PLAYER>!"
        t_line "Wasn't PROF.ELM"
        t_cont "waiting for you?"
        t_done )
};
const txt_cmd_s MomPhoneNoPokedexText[] = {
    text_start("Hello?"
        t_para "Oh, hi, <PLAYER>!"
        t_line "You're on a big"
        t_para "mission for PROF."
        t_line "ELM? Be good!"
        t_done )
};
const txt_cmd_s MomPhoneNoGymQuestText[] = {
    text_start("Hello?"
        t_para "Hi, <PLAYER>! If"
        t_line "you're done with"
        t_para "your errand come"
        t_line "on home, dear."
        t_done )
};
const txt_cmd_s MomPhoneLectureText[] = {
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
