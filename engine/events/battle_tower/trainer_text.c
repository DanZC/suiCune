#include "../../../constants.h"
#include "trainer_text.h"
#include "../../../home/text.h"
#include "../../../home/sram.h"
#include "../../../home/copy.h"
#include "../../../data/battle_tower/trainer_text.h"
#include "../../../data/trainers/genders.h"
#include "../../../mobile/fixed_words.h"

struct TrainerTexts {
    const txt_cmd_s** greetings;
    const txt_cmd_s** playerLost;
    const txt_cmd_s** playerWon;
};

const struct TrainerTexts BTMaleTrainerTexts = {
    //dw ['.Greetings'];
    .greetings = (const txt_cmd_s*[]) {
    // Greetings:
        BTGreetingM1Text,
        BTGreetingM2Text,
        BTGreetingM3Text,
        BTGreetingM4Text,
        BTGreetingM5Text,
        BTGreetingM6Text,
        BTGreetingM7Text,
        BTGreetingM8Text,
        BTGreetingM9Text,
        BTGreetingM10Text,
        BTGreetingM11Text,
        BTGreetingM12Text,
        BTGreetingM13Text,
        BTGreetingM14Text,
        BTGreetingM15Text,
        BTGreetingM16Text,
        BTGreetingM17Text,
        BTGreetingM18Text,
        BTGreetingM19Text,
        BTGreetingM20Text,
        BTGreetingM21Text,
        BTGreetingM22Text,
        BTGreetingM23Text,
        BTGreetingM24Text,
        BTGreetingM25Text,
    },
    //dw ['.PlayerLost'];
    .playerLost = (const txt_cmd_s*[]) {
    // PlayerLost:
        BTLossM1Text,
        BTLossM2Text,
        BTLossM3Text,
        BTLossM4Text,
        BTLossM5Text,
        BTLossM6Text,
        BTLossM7Text,
        BTLossM8Text,
        BTLossM9Text,
        BTLossM10Text,
        BTLossM11Text,
        BTLossM12Text,
        BTLossM13Text,
        BTLossM14Text,
        BTLossM15Text,
        BTLossM16Text,
        BTLossM17Text,
        BTLossM18Text,
        BTLossM19Text,
        BTLossM20Text,
        BTLossM21Text,
        BTLossM22Text,
        BTLossM23Text,
        BTLossM24Text,
        BTLossM25Text,
    },
    //dw ['.PlayerWon'];
    .playerWon = (const txt_cmd_s*[]) {
    // PlayerWon:
        BTWinM1Text,
        BTWinM2Text,
        BTWinM3Text,
        BTWinM4Text,
        BTWinM5Text,
        BTWinM6Text,
        BTWinM7Text,
        BTWinM8Text,
        BTWinM9Text,
        BTWinM10Text,
        BTWinM11Text,
        BTWinM12Text,
        BTWinM13Text,
        BTWinM14Text,
        BTWinM15Text,
        BTWinM16Text,
        BTWinM17Text,
        BTWinM18Text,
        BTWinM19Text,
        BTWinM20Text,
        BTWinM21Text,
        BTWinM22Text,
        BTWinM23Text,
        BTWinM24Text,
        BTWinM25Text,
    },
};

const struct TrainerTexts BTFemaleTrainerTexts = {
    //dw ['.Greetings'];
    .greetings = (const txt_cmd_s*[]) {
    // Greetings:
        BTGreetingF1Text,
        BTGreetingF2Text,
        BTGreetingF3Text,
        BTGreetingF4Text,
        BTGreetingF5Text,
        BTGreetingF6Text,
        BTGreetingF7Text,
        BTGreetingF8Text,
        BTGreetingF9Text,
        BTGreetingF10Text,
        BTGreetingF11Text,
        BTGreetingF12Text,
        BTGreetingF13Text,
        BTGreetingF14Text,
        BTGreetingF15Text,
    },
    //dw ['.PlayerLost'];
    .playerLost = (const txt_cmd_s*[]) {
    // PlayerLost:
        BTLossF1Text,
        BTLossF2Text,
        BTLossF3Text,
        BTLossF4Text,
        BTLossF5Text,
        BTLossF6Text,
        BTLossF7Text,
        BTLossF8Text,
        BTLossF9Text,
        BTLossF10Text,
        BTLossF11Text,
        BTLossF12Text,
        BTLossF13Text,
        BTLossF14Text,
        BTLossF15Text,
    },
    //dw ['.PlayerWon'];
    .playerWon = (const txt_cmd_s*[]) {
    // PlayerWon:
        BTWinF1Text,
        BTWinF2Text,
        BTWinF3Text,
        BTWinF4Text,
        BTWinF5Text,
        BTWinF6Text,
        BTWinF7Text,
        BTWinF8Text,
        BTWinF9Text,
        BTWinF10Text,
        BTWinF11Text,
        BTWinF12Text,
        BTWinF13Text,
        BTWinF14Text,
        BTWinF15Text,
    },
};

struct EZChatAddr {
    uint8_t* hl;
    uint8_t a;
};

// Call_047_4033
// get address of easy chat data
struct EZChatAddr BattleTowerText_GetEZChatAddress(uint8_t a) {
    // dec a
    uint8_t i = gb_read(sNrOfBeatenBattleTowerTrainers);
    // sla a
    // sla a
    //	ld c, a
    // sla a
    //	add c
    // ld c, a
    // ld b, $00
    // ld de, -BATTLE_TOWER_STRUCT_LENGTH
    // ld hl, s5_aa8e + BATTLE_TOWER_STRUCT_LENGTH * (BATTLETOWER_STREAK_LENGTH - 1) + (BATTLE_TOWER_STRUCT_LENGTH - EASY_CHAT_MESSAGE_LENGTH * 3);$affe easy chat data for trainer
    // add hl, bc
    // ld a, [sNrOfBeatenBattleTowerTrainers];$aa3f
    // ret
    return (struct EZChatAddr){
        .a = i, 
        .hl = (((struct BattleTowerData*)GBToRAMAddr(s5_aa8e)) + (BATTLETOWER_STREAK_LENGTH - 1 - i))->trainerData + (EASY_CHAT_MESSAGE_LENGTH * (a - 1)),
    };
}

void BattleTowerText(uint8_t c){
//  Print text c for trainer [wBT_OTTrainerClass]
//  1: Intro text
//  2: Player lost
//  3: Player won
    // ld a, $05
    // call OpenSRAM;$2f9d
    OpenSRAM_Conv(MBANK(as5_a800));
    struct EZChatAddr addr = BattleTowerText_GetEZChatAddress(c);
    // ld a, c
    // cp $01
    // jr nz, jr_047_400f
    // call Call_047_4033
    // jr jr_047_4016
    // jr_047_400f:
    // call Call_047_4033
    // and a
    // jr z, jr_047_401d
    // dec a
    // jr_047_4016:
    // and a
    // jr z, jr_047_401d

    // dec a
    // add hl, de
    // jr jr_047_4016

// jr_047_401d:
    // ld de, $c688
    // ld bc, EASY_CHAT_MESSAGE_LENGTH
    // call CopyBytes;$2ff2
    CopyBytes(wram->wc688, addr.hl, EASY_CHAT_MESSAGE_LENGTH);
    // call CloseSRAM;$2fad
    CloseSRAM_Conv();
    // ld de, $c5b9
    // ld bc, $c688
    // call PrintEZChatBattleMessage;Call_047_40b3
    PrintEZChatBattleMessage(coord(1, 14, wram->wTilemap), wram->wc688);
    // ret
    return;
#if 0
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBT_OTTrainerClass));
    // LDH_addr_A(rSVBK);
#if defined(_CRYSTAL11)
    // LD_HL(wBT_OTTrainerClass);
    uint8_t a = wram->wBT_OTTrainer.trainerClass;
#else
//  BUG ALERT
//  Instead of loading the Trainer Class, this routine
//  loads the 6th character in the Trainer's name, then
//  uses it to get the gender of the trainer.
//  As a consequence, the enemy trainer's dialog will
//  always be sampled from the female array.
    // LD_HL(wBT_OTName + NAME_LENGTH_JAPANESE - 1);
    uint8_t a = wram->wBT_OTTrainer.name[NAME_LENGTH_JAPANESE - 1];
#endif
    // LD_A_hl;
    // DEC_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mBTTrainerClassGenders);
    // ADD_HL_DE;
    // LD_A_hl;
    uint8_t gender = BTTrainerClassGenders[a - 1];
    // AND_A_A;
    // IF_NZ goto female;
    const struct TrainerTexts* hl;
    if(gender != 0) {
    // generate a random number between 0 and 24
        // LDH_A_addr(hRandomAdd);
        // AND_A(0x1f);
        a = hram->hRandomAdd & 0x1f;
        // CP_A(25);
        // IF_C goto okay0;
        if(a >= 25) {
            // SUB_A(25);
            a -= 25;
        }

    // okay0:
        // LD_HL(mBTMaleTrainerTexts);
        hl = &BTMaleTrainerTexts;
        // goto proceed;
    }
    else {
    // female:
    // generate a random number between 0 and 14
        // LDH_A_addr(hRandomAdd);
        // AND_A(0xf);
        a = hram->hRandomAdd & 0xf;
        // CP_A(15);
        // IF_C goto okay1;
        if(a >= 15) {
            // SUB_A(15);
            a -= 15;
        }

    // okay1:
        // LD_HL(mBTFemaleTrainerTexts);
        hl = &BTFemaleTrainerTexts;
    }

// proceed:
    // LD_B(0);
    // DEC_C;
    // IF_NZ goto restore;
    if(--c == 0) {
        // LD_addr_A(wBT_TrainerTextIndex);
        wram->wBT_TrainerTextIndex = a;
        // goto okay2;
    }
    else {
    // restore:
        // LD_A_addr(wBT_TrainerTextIndex);
        a = wram->wBT_TrainerTextIndex;
    }

// okay2:
    // PUSH_AF;
    // ADD_HL_BC;
    // ADD_HL_BC;
    const txt_cmd_s* txt;
    switch(c) {
    default:
    case 0: txt = hl->greetings[a]; break;
    case 1: txt = hl->playerLost[a]; break;
    case 2: txt = hl->playerWon[a]; break;
    }
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hl;
    // LD_H_A;
    // LD_L_C;
    // POP_AF;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hl;
    // LD_L_C;
    // LD_H_A;
    // bccoord(1, 14, wTilemap);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), txt);
    // RET;
#endif
// INCLUDE "mobile/fixed_words.asm"

// INCLUDE "data/trainers/genders.asm"
}

const txt_cmd_s BTGreetingM1Text[] = {
    text_far(v_BTGreetingM1Text)
    text_end
};

const txt_cmd_s BTLossM1Text[] = {
    text_far(v_BTLossM1Text)
    text_end
};

const txt_cmd_s BTWinM1Text[] = {
    text_far(v_BTWinM1Text)
    text_end
};

const txt_cmd_s BTGreetingM2Text[] = {
    text_far(v_BTGreetingM2Text)
    text_end
};

const txt_cmd_s BTLossM2Text[] = {
    text_far(v_BTLossM2Text)
    text_end
};

const txt_cmd_s BTWinM2Text[] = {
    text_far(v_BTWinM2Text)
    text_end
};

const txt_cmd_s BTGreetingM3Text[] = {
    text_far(v_BTGreetingM3Text)
    text_end
};

const txt_cmd_s BTLossM3Text[] = {
    text_far(v_BTLossM3Text)
    text_end
};

const txt_cmd_s BTWinM3Text[] = {
    text_far(v_BTWinM3Text)
    text_end
};

const txt_cmd_s BTGreetingM4Text[] = {
    text_far(v_BTGreetingM4Text)
    text_end
};

const txt_cmd_s BTLossM4Text[] = {
    text_far(v_BTLossM4Text)
    text_end
};

const txt_cmd_s BTWinM4Text[] = {
    text_far(v_BTWinM4Text)
    text_end
};

const txt_cmd_s BTGreetingM5Text[] = {
    text_far(v_BTGreetingM5Text)
    text_end
};

const txt_cmd_s BTLossM5Text[] = {
    text_far(v_BTLossM5Text)
    text_end
};

const txt_cmd_s BTWinM5Text[] = {
    text_far(v_BTWinM5Text)
    text_end
};

const txt_cmd_s BTGreetingM6Text[] = {
    text_far(v_BTGreetingM6Text)
    text_end
};

const txt_cmd_s BTLossM6Text[] = {
    text_far(v_BTLossM6Text)
    text_end
};

const txt_cmd_s BTWinM6Text[] = {
    text_far(v_BTWinM6Text)
    text_end
};

const txt_cmd_s BTGreetingM7Text[] = {
    text_far(v_BTGreetingM7Text)
    text_end
};

const txt_cmd_s BTLossM7Text[] = {
    text_far(v_BTLossM7Text)
    text_end
};

const txt_cmd_s BTWinM7Text[] = {
    text_far(v_BTWinM7Text)
    text_end
};

const txt_cmd_s BTGreetingM8Text[] = {
    text_far(v_BTGreetingM8Text)
    text_end
};

const txt_cmd_s BTLossM8Text[] = {
    text_far(v_BTLossM8Text)
    text_end
};

const txt_cmd_s BTWinM8Text[] = {
    text_far(v_BTWinM8Text)
    text_end
};

const txt_cmd_s BTGreetingM9Text[] = {
    text_far(v_BTGreetingM9Text)
    text_end
};

const txt_cmd_s BTLossM9Text[] = {
    text_far(v_BTLossM9Text)
    text_end
};

const txt_cmd_s BTWinM9Text[] = {
    text_far(v_BTWinM9Text)
    text_end
};

const txt_cmd_s BTGreetingM10Text[] = {
    text_far(v_BTGreetingM10Text)
    text_end
};

const txt_cmd_s BTLossM10Text[] = {
    text_far(v_BTLossM10Text)
    text_end
};

const txt_cmd_s BTWinM10Text[] = {
    text_far(v_BTWinM10Text)
    text_end
};

const txt_cmd_s BTGreetingM11Text[] = {
    text_far(v_BTGreetingM11Text)
    text_end
};

const txt_cmd_s BTLossM11Text[] = {
    text_far(v_BTLossM11Text)
    text_end
};

const txt_cmd_s BTWinM11Text[] = {
    text_far(v_BTWinM11Text)
    text_end
};

const txt_cmd_s BTGreetingM12Text[] = {
    text_far(v_BTGreetingM12Text)
    text_end
};

const txt_cmd_s BTLossM12Text[] = {
    text_far(v_BTLossM12Text)
    text_end
};

const txt_cmd_s BTWinM12Text[] = {
    text_far(v_BTWinM12Text)
    text_end
};

const txt_cmd_s BTGreetingM13Text[] = {
    text_far(v_BTGreetingM13Text)
    text_end
};

const txt_cmd_s BTLossM13Text[] = {
    text_far(v_BTLossM13Text)
    text_end
};

const txt_cmd_s BTWinM13Text[] = {
    text_far(v_BTWinM13Text)
    text_end
};

const txt_cmd_s BTGreetingM14Text[] = {
    text_far(v_BTGreetingM14Text)
    text_end
};

const txt_cmd_s BTLossM14Text[] = {
    text_far(v_BTLossM14Text)
    text_end
};

const txt_cmd_s BTWinM14Text[] = {
    text_far(v_BTWinM14Text)
    text_end
};

const txt_cmd_s BTGreetingM15Text[] = {
    text_far(v_BTGreetingM15Text)
    text_end
};

const txt_cmd_s BTLossM15Text[] = {
    text_far(v_BTLossM15Text)
    text_end
};

const txt_cmd_s BTWinM15Text[] = {
    text_far(v_BTWinM15Text)
    text_end
};

const txt_cmd_s BTGreetingM16Text[] = {
    text_far(v_BTGreetingM16Text)
    text_end
};

const txt_cmd_s BTLossM16Text[] = {
    text_far(v_BTLossM16Text)
    text_end
};

const txt_cmd_s BTWinM16Text[] = {
    text_far(v_BTWinM16Text)
    text_end
};

const txt_cmd_s BTGreetingM17Text[] = {
    text_far(v_BTGreetingM17Text)
    text_end
};

const txt_cmd_s BTLossM17Text[] = {
    text_far(v_BTLossM17Text)
    text_end
};

const txt_cmd_s BTWinM17Text[] = {
    text_far(v_BTWinM17Text)
    text_end
};

const txt_cmd_s BTGreetingM18Text[] = {
    text_far(v_BTGreetingM18Text)
    text_end
};

const txt_cmd_s BTLossM18Text[] = {
    text_far(v_BTLossM18Text)
    text_end
};

const txt_cmd_s BTWinM18Text[] = {
    text_far(v_BTWinM18Text)
    text_end
};

const txt_cmd_s BTGreetingM19Text[] = {
    text_far(v_BTGreetingM19Text)
    text_end
};

const txt_cmd_s BTLossM19Text[] = {
    text_far(v_BTLossM19Text)
    text_end
};

const txt_cmd_s BTWinM19Text[] = {
    text_far(v_BTWinM19Text)
    text_end
};

const txt_cmd_s BTGreetingM20Text[] = {
    text_far(v_BTGreetingM20Text)
    text_end
};

const txt_cmd_s BTLossM20Text[] = {
    text_far(v_BTLossM20Text)
    text_end
};

const txt_cmd_s BTWinM20Text[] = {
    text_far(v_BTWinM20Text)
    text_end
};

const txt_cmd_s BTGreetingM21Text[] = {
    text_far(v_BTGreetingM21Text)
    text_end
};

const txt_cmd_s BTLossM21Text[] = {
    text_far(v_BTLossM21Text)
    text_end
};

const txt_cmd_s BTWinM21Text[] = {
    text_far(v_BTWinM21Text)
    text_end
};

const txt_cmd_s BTGreetingM22Text[] = {
    text_far(v_BTGreetingM22Text)
    text_end
};

const txt_cmd_s BTLossM22Text[] = {
    text_far(v_BTLossM22Text)
    text_end
};

const txt_cmd_s BTWinM22Text[] = {
    text_far(v_BTWinM22Text)
    text_end
};

const txt_cmd_s BTGreetingM23Text[] = {
    text_far(v_BTGreetingM23Text)
    text_end
};

const txt_cmd_s BTLossM23Text[] = {
    text_far(v_BTLossM23Text)
    text_end
};

const txt_cmd_s BTWinM23Text[] = {
    text_far(v_BTWinM23Text)
    text_end
};

const txt_cmd_s BTGreetingM24Text[] = {
    text_far(v_BTGreetingM24Text)
    text_end
};

const txt_cmd_s BTLossM24Text[] = {
    text_far(v_BTLossM24Text)
    text_end
};

const txt_cmd_s BTWinM24Text[] = {
    text_far(v_BTWinM24Text)
    text_end
};

const txt_cmd_s BTGreetingM25Text[] = {
    text_far(v_BTGreetingM25Text)
    text_end
};

const txt_cmd_s BTLossM25Text[] = {
    text_far(v_BTLossM25Text)
    text_end
};

const txt_cmd_s BTWinM25Text[] = {
    text_far(v_BTWinM25Text)
    text_end
};

const txt_cmd_s BTGreetingF1Text[] = {
    text_far(v_BTGreetingF1Text)
    text_end
};

const txt_cmd_s BTLossF1Text[] = {
    text_far(v_BTLossF1Text)
    text_end
};

const txt_cmd_s BTWinF1Text[] = {
    text_far(v_BTWinF1Text)
    text_end
};

const txt_cmd_s BTGreetingF2Text[] = {
    text_far(v_BTGreetingF2Text)
    text_end
};

const txt_cmd_s BTLossF2Text[] = {
    text_far(v_BTLossF2Text)
    text_end
};

const txt_cmd_s BTWinF2Text[] = {
    text_far(v_BTWinF2Text)
    text_end
};

const txt_cmd_s BTGreetingF3Text[] = {
    text_far(v_BTGreetingF3Text)
    text_end
};

const txt_cmd_s BTLossF3Text[] = {
    text_far(v_BTLossF3Text)
    text_end
};

const txt_cmd_s BTWinF3Text[] = {
    text_far(v_BTWinF3Text)
    text_end
};

const txt_cmd_s BTGreetingF4Text[] = {
    text_far(v_BTGreetingF4Text)
    text_end
};

const txt_cmd_s BTLossF4Text[] = {
    text_far(v_BTLossF4Text)
    text_end
};

const txt_cmd_s BTWinF4Text[] = {
    text_far(v_BTWinF4Text)
    text_end
};

const txt_cmd_s BTGreetingF5Text[] = {
    text_far(v_BTGreetingF5Text)
    text_end
};

const txt_cmd_s BTLossF5Text[] = {
    text_far(v_BTLossF5Text)
    text_end
};

const txt_cmd_s BTWinF5Text[] = {
    text_far(v_BTWinF5Text)
    text_end
};

const txt_cmd_s BTGreetingF6Text[] = {
    text_far(v_BTGreetingF6Text)
    text_end
};

const txt_cmd_s BTLossF6Text[] = {
    text_far(v_BTLossF6Text)
    text_end
};

const txt_cmd_s BTWinF6Text[] = {
    text_far(v_BTWinF6Text)
    text_end
};

const txt_cmd_s BTGreetingF7Text[] = {
    text_far(v_BTGreetingF7Text)
    text_end
};

const txt_cmd_s BTLossF7Text[] = {
    text_far(v_BTLossF7Text)
    text_end
};

const txt_cmd_s BTWinF7Text[] = {
    text_far(v_BTWinF7Text)
    text_end
};

const txt_cmd_s BTGreetingF8Text[] = {
    text_far(v_BTGreetingF8Text)
    text_end
};

const txt_cmd_s BTLossF8Text[] = {
    text_far(v_BTLossF8Text)
    text_end
};

const txt_cmd_s BTWinF8Text[] = {
    text_far(v_BTWinF8Text)
    text_end
};

const txt_cmd_s BTGreetingF9Text[] = {
    text_far(v_BTGreetingF9Text)
    text_end
};

const txt_cmd_s BTLossF9Text[] = {
    text_far(v_BTLossF9Text)
    text_end
};

const txt_cmd_s BTWinF9Text[] = {
    text_far(v_BTWinF9Text)
    text_end
};

const txt_cmd_s BTGreetingF10Text[] = {
    text_far(v_BTGreetingF10Text)
    text_end
};

const txt_cmd_s BTLossF10Text[] = {
    text_far(v_BTLossF10Text)
    text_end
};

const txt_cmd_s BTWinF10Text[] = {
    text_far(v_BTWinF10Text)
    text_end
};

const txt_cmd_s BTGreetingF11Text[] = {
    text_far(v_BTGreetingF11Text)
    text_end
};

const txt_cmd_s BTLossF11Text[] = {
    text_far(v_BTLossF11Text)
    text_end
};

const txt_cmd_s BTWinF11Text[] = {
    text_far(v_BTWinF11Text)
    text_end
};

const txt_cmd_s BTGreetingF12Text[] = {
    text_far(v_BTGreetingF12Text)
    text_end
};

const txt_cmd_s BTLossF12Text[] = {
    text_far(v_BTLossF12Text)
    text_end
};

const txt_cmd_s BTWinF12Text[] = {
    text_far(v_BTWinF12Text)
    text_end
};

const txt_cmd_s BTGreetingF13Text[] = {
    text_far(v_BTGreetingF13Text)
    text_end
};

const txt_cmd_s BTLossF13Text[] = {
    text_far(v_BTLossF13Text)
    text_end
};

const txt_cmd_s BTWinF13Text[] = {
    text_far(v_BTWinF13Text)
    text_end
};

const txt_cmd_s BTGreetingF14Text[] = {
    text_far(v_BTGreetingF14Text)
    text_end
};

const txt_cmd_s BTLossF14Text[] = {
    text_far(v_BTLossF14Text)
    text_end
};

const txt_cmd_s BTWinF14Text[] = {
    text_far(v_BTWinF14Text)
    text_end
};

const txt_cmd_s BTGreetingF15Text[] = {
    text_far(v_BTGreetingF15Text)
    text_end
};

const txt_cmd_s BTLossF15Text[] = {
    text_far(v_BTLossF15Text)
    text_end
};

const txt_cmd_s BTWinF15Text[] = {
    text_far(v_BTWinF15Text)
    text_end

};
