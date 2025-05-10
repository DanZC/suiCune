#include "../../constants.h"
#include "european_mail.h"

//  return 1 if French
//  return 2 if German
//  return 3 if Italian
//  return 4 if Spanish
//  return 0 if none of the above
uint8_t IsMailEuropean(const struct MailMsg* de){
    // LD_C(0x0);
    // LD_HL(sPartyMon1MailNationality - sPartyMon1Mail);
    // ADD_HL_DE;
    // LD_A_hli;
    // CP_A(0x84);
    // RET_NZ ;
    if((de->nationality & 0xff) != 0x84)
        return 0x0;
    // LD_A_hli;
    uint8_t a = (de->nationality >> 8);
    // INC_C;
    // CP_A(0x85);
    // RET_Z ;
    if(a == 0x85)
        return 0x1;
    // INC_C;
    // CP_A(0x86);
    // RET_Z ;
    if(a == 0x86)
        return 0x2;
    // INC_C;
    // CP_A(0x88);
    // RET_Z ;
    if(a == 0x88)
        return 0x3;
    // INC_C;
    // CP_A(0x92);
    // RET_Z ;
    if(a == 0x92)
        return 0x4;
    // LD_C(0x0);
    // RET;
    return 0x0;
}

//  The regular font.
const char StandardEnglishFont[] = "gfx/font/english.png";

//  An extended font.
const char FrenchGermanFont[] = "gfx/font/french_german.png";

//  An even more extended font.
const char SpanishItalianFont[] = "gfx/font/spanish_italian.png";

//  Called if mail is French or German
//  Converts 's 't 'v from French/German character set to English
void ConvertFrenchGermanMailToEnglish(struct MailMsg* de){
    // LD_B(sPartyMon1MailAuthor - sPartyMon1Mail);
    uint8_t b = sizeof(de->author);
    // LD_H_D;
    // LD_L_E;
    uint8_t* hl = de->author;

    do {
    // loop:
        // LD_A_hl;
        // CP_A(0xdc);  // 's in French/German font
        // IF_NZ goto check_intermediate_chars;
        if(*hl == 0xdc) {
            // LD_A(0xd4);
            // goto replace;
            *hl = 0xd4;
        }
        else {
        // check_intermediate_chars:
            // SUB_A(0xd4);
            // IF_C goto dont_replace;
            // CP_A(0xd6 - 0xd4 + 1);
            // IF_NC goto dont_replace;
            if(*hl >= 0xd4 && *hl - 0xd4 < 0xd6 - 0xd4 + 1) {
                // ADD_A(0xcd);
                *hl = (*hl - 0xd4) + 0xcd;
            }
        }

    // replace:
        // LD_hl_A;

    // dont_replace:
        // INC_HL;
        hl++;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

//  Called if mail is English and game is French or German
//  Converts 's 't 'v from English character set to French/German
void ConvertEnglishMailToFrenchGerman(struct MailMsg* de){
    // LD_B(sPartyMon1MailAuthor - sPartyMon1Mail);
    uint8_t b = sizeof(de->author);
    // LD_H_D;
    // LD_L_E;
    uint8_t* hl = de->author;

    do {
    // loop:
        // LD_A_hl;
        // CP_A(0xd4);
        // IF_NZ goto check_intermediate_chars;
        if(*hl == 0xd4) {
            // LD_A(0xdc);  // 's in French/German font
            // goto replace;
            *hl = 0xdc;
        }
        else {
        // check_intermediate_chars:
            // SUB_A(0xcd);
            // IF_C goto dont_replace;
            // CP_A(0xd6 - 0xd4 + 1);
            // IF_NC goto dont_replace;
            if(*hl >= 0xcd && *hl - 0xcd < 0xd6 - 0xd4 + 1) {
                // ADD_A(0xd4);

            // replace:
                // LD_hl_A;
                *hl = (*hl - 0xcd) + 0xd4;
            }
        }

    // dont_replace:
        // INC_HL;
        hl++;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

//  Called if mail is Spanish or Italian
//  Converts 'd 'l 'm 'r 's 't 'v from Spanish/Italian character set to English
void ConvertSpanishItalianMailToEnglish(struct MailMsg* de){
    return ConvertEnglishMailToSpanishItalian(de);
}

//  Called if mail is English and game is Spanish or Italian
//  Converts 'd 'l 'm 'r 's 't 'v from English character set to Spanish/Italian
void ConvertEnglishMailToSpanishItalian(struct MailMsg* de){
    // LD_B(sPartyMon1MailAuthor - sPartyMon1Mail);
    uint8_t b = sizeof(de->author);
    // LD_H_D;
    // LD_L_E;
    uint8_t* hl = de->author;

    do {
    // loop:
        // LD_A_hl;
        // AND_A(0xf0);
        // CP_A(0xd0);
        // IF_NZ goto dont_replace;
        if((*hl & 0xf0) == 0xd0) {
            // LD_A_hl;
            // ADD_A(0x8);
            // AND_A(0xf);
            // OR_A(0xd0);
            // LD_hl_A;
            *hl = ((*hl + 0x8) & 0xf) | 0xd0;
        }

    // dont_replace:
        // INC_HL;
        hl++;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    RET;

}
