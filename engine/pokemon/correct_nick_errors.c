#include "../../constants.h"
#include "correct_nick_errors.h"
#include "../../charmap.h"

//  error-check monster nick before use
//  must be a peace offering to gamesharkers
void CorrectNickErrors(void){

    // static const uint8_t textcommands[] = {
        //  table defining which characters are actually text commands
        //  format:
        //      ≥           <
            //db ['"<NULL>"', '"ガ"'];
            //db ['"<PLAY_G>"', '"<JP_18>" + 1'];
            //db ['"<NI>"', '"<NO>"    + 1'];
            //db ['"<ROUTE>"', '"<GREEN>" + 1'];
            //db ['"<ENEMY>"', '"<ENEMY>" + 1'];
            //db ['"<MOM>"', '"<TM>"    + 1'];
            //db ['"<ROCKET>"', '"┘"       + 1'];
            //db ['-1'];  // end
    // };

//  input: de = nick location

    PUSH_BC;
    PUSH_DE;
    LD_B(MON_NAME_LENGTH);


checkchar:
//  end of nick?
    LD_A_de;
    CP_A(0x50);  // terminator
    IF_Z goto end;

//  check if this char is a text command
    LD_HL(mCorrectNickErrors_textcommands);
    DEC_HL;

loop:
//  next entry
    INC_HL;
//  reached end of commands table?
    LD_A_hl;
    CP_A(-1);
    IF_Z goto done;

//  is the current char between this value (inclusive)...
    LD_A_de;
    CP_A_hl;
    INC_HL;
    IF_C goto loop;
//  ...and this one?
    CP_A_hl;
    IF_NC goto loop;

//  replace it with a "?"
    LD_A(0xe6);
    LD_de_A;
    goto loop;


done:
//  next char
    INC_DE;
//  reached end of nick without finding a terminator?
    DEC_B;
    IF_NZ goto checkchar;

//  change nick to "?@"
    POP_DE;
    PUSH_DE;
    LD_A(0xe6);
    LD_de_A;
    INC_DE;
    LD_A(0x50);
    LD_de_A;

end:
//  if the nick has any errors at this point it's out of our hands
    POP_DE;
    POP_BC;
    RET;

}

//  error-check monster nick before use
//  must be a peace offering to gamesharkers
void CorrectNickErrors_Conv(uint8_t* de){

    static const uint8_t textcommands[] = {
        //  table defining which characters are actually text commands
        //  format:
        //      ≥           <
            //db ['"<NULL>"', '"ガ"'];
            CHAR_NULL,      CHAR_JP_05,
            //db ['"<PLAY_G>"', '"<JP_18>" + 1'];
            CHAR_PLAY_G,    CHAR_JP_18 + 1,
            //db ['"<NI>"', '"<NO>"    + 1'];
            CHAR_JP_NI,     CHAR_JP_NO + 1,
            //db ['"<ROUTE>"', '"<GREEN>" + 1'];
            CHAR_ROUTE,     CHAR_GREEN + 1,
            //db ['"<ENEMY>"', '"<ENEMY>" + 1'];
            CHAR_ENEMY,     CHAR_ENEMY + 1,
            //db ['"<MOM>"', '"<TM>"    + 1'];
            CHAR_MOM,       CHAR_TM + 1,
            //db ['"<ROCKET>"', '"┘"       + 1'];
            CHAR_ROCKET,    CHAR_FRAME_BOTTOM_RIGHT + 1,
            //db ['-1'];  // end
            (uint8_t)-1,    0,
    };

//  input: de = nick location

    // PUSH_BC;
    // PUSH_DE;
    uint8_t* de2 = de;
    // LD_B(MON_NAME_LENGTH);
    uint8_t b = MON_NAME_LENGTH;

    while(*de != CHAR_TERM) {
    // checkchar:
    //  end of nick?
        // LD_A_de;
        // CP_A(0x50);  // terminator
        // IF_Z goto end;

    //  check if this char is a text command
        // LD_HL(mCorrectNickErrors_textcommands);
        // DEC_HL;
        const uint8_t* hl = textcommands;

        while(1) {
        // loop:
        //  next entry
            // INC_HL;
        //  reached end of commands table?
            // LD_A_hl;
            // CP_A(-1);
            // IF_Z goto done;
            if(hl[0] == 0xff)
                break;

        //  is the current char between this value (inclusive)...
            // LD_A_de;
            // CP_A_hl;
            // INC_HL;
            // IF_C goto loop;
            if(*de < hl[0]) {
                hl += 2;
                continue;
            }
        //  ...and this one?
            // CP_A_hl;
            // IF_NC goto loop;
            if(*de >= hl[1]) {
                hl += 2;
                continue;
            }

        //  replace it with a "?"
            // LD_A(0xe6);
            // LD_de_A;
            *de = CHAR_QMARK;
            // goto loop;
        }


    // done:
    //  next char
        // INC_DE;
        de++;
    //  reached end of nick without finding a terminator?
        // DEC_B;
        // IF_NZ goto checkchar;
        if(--b != 0)
            continue;

    //  change nick to "?@"
        // POP_DE;
        // PUSH_DE;
        // LD_A(0xe6);
        // LD_de_A;
        de2[0] = CHAR_QMARK;
        // INC_DE;
        // LD_A(0x50);
        // LD_de_A;
        de2[1] = CHAR_TERM;
    }

// end:
//  if the nick has any errors at this point it's out of our hands
    // POP_DE;
    // POP_BC;
    // RET;
}
