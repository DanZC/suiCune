#include "../../constants.h"
#include "reset_password.h"
#include "../../home/audio.h"
#include "../../home/tilemap.h"
#include "../../home/gfx.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../home/joypad.h"
#include "../../home/delay.h"
#include "../overworld/player_object.h"
#include "../../data/text/common.h"
#include "../../util/serialize.h"
#include "../../charmap.h"

// Set this value to 1 to bypass clock password system
#define BYPASS_CLOCK_PASSWORD 0

static const struct MenuHeader NoYes_MenuHeader = {
    .flags = 0,  // flags
    .coord = menu_coords(14, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.NoYes_MenuData'];
    .data = &(struct MenuData){
    // NoYes_MenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
        .verticalMenu = {
            .count = 2,  // items
            .options = (const char*[]){
                "NO@",
                "YES@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

void v_ResetClock(void){
    static const txt_cmd_s PasswordAskResetText[] = {
        text_far(v_PasswordAskResetText)
        text_end
    };

    static const txt_cmd_s PasswordWrongText[] = {
        text_far(v_PasswordWrongText)
        text_end
    };

    static const txt_cmd_s PasswordAskResetClockText[] = {
        text_far(v_PasswordAskResetClockText)
        text_end
    };
    // FARCALL(aBlankScreen);
    BlankScreen();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_DIPLOMA);
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // LD_DE(MUSIC_MAIN_MENU);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_MAIN_MENU);
    // LD_HL(mv_ResetClock_PasswordAskResetClockText);
    // CALL(aPrintText);
    PrintText(PasswordAskResetClockText);
    // LD_HL(mv_ResetClock_NoYes_MenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&NoYes_MenuHeader);
    // CALL(aVerticalMenu);
    // RET_C ;
    // LD_A_addr(wMenuCursorY);
    // CP_A(1);
    // RET_Z ;
    if(VerticalMenu() || wram->wMenuCursorY == 1)
        return;
    // CALL(aClockResetPassword);
    // IF_C goto wrongpassword;
#if !BYPASS_CLOCK_PASSWORD
    if(!ClockResetPassword()) {
    // wrongpassword:
        // LD_HL(mv_ResetClock_PasswordWrongText);
        // CALL(aPrintText);
        PrintText(PasswordWrongText);
        // RET;
        return;
    }
#endif
    // LD_A(BANK(sRTCStatusFlags));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asRTCStatusFlags));
    // LD_A(0x80);
    // LD_addr_A(sRTCStatusFlags);
    gb_write(sRTCStatusFlags, 0x80);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_HL(mv_ResetClock_PasswordAskResetText);
    // CALL(aPrintText);
    PrintText(PasswordAskResetText);
    // RET;
    return;
}

#define CLOCK_RESET_PASSWORD_LENGTH 4
#define CLOCK_RESET_CURSOR CLOCK_RESET_PASSWORD_LENGTH + 1

static void ClockResetPassword_updateIDdisplay(void){
    // hlcoord(14, 15, wTilemap);
    tile_t* hl = coord(14, 15, wram->wTilemap);
    // LD_DE(wStringBuffer2);
    // LD_C(5);

    for(uint32_t i = 0; i < CLOCK_RESET_CURSOR; ++i) {
    // loop3:
        // LD_A_de;
        // ADD_A(0xf6);
        // LD_hli_A;
        hl[i] = wram->wStringBuffer2[i] + CHAR_0;
        // INC_DE;
        // DEC_C;
        // IF_NZ goto loop3;
    }
    // hlcoord(14, 16, wTilemap);
    // LD_BC(5);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(14, 16, wram->wTilemap), CLOCK_RESET_CURSOR, CHAR_SPACE);
    // hlcoord(14, 16, wTilemap);
    // LD_A_addr(wStringBuffer2 + 5);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_hl(0x61);
    coord(14, 16, wram->wTilemap)[wram->wStringBuffer2[CLOCK_RESET_CURSOR]] = 0x61;
    // RET;
}

static void ClockResetPassword_ComponentFromNumber(uint16_t* de, void* hl_, uint8_t c){
    uint8_t* hl = hl_;
    do {
        // LD_A_hli;
        // ADD_A_E;
        // LD_E_A;
        // LD_A(0);
        // ADC_A_D;
        // LD_D_A;
        *de += *hl;
        hl++;
        // DEC_C;
        // IF_NZ goto ComponentFromNumber;
    } while(--c != 0);
    // RET;
}

static void ClockResetPassword_ComponentFromString(uint16_t* de, uint8_t* hl, uint8_t c){
    do {
        // LD_A_hli;
        // CP_A(0x50);
        // RET_Z ;
        uint8_t ch = *(hl++);
        if(ch == CHAR_TERM)
            return;
        // ADD_A_E;
        // LD_E_A;
        // LD_A(0);
        // ADC_A_D;
        // LD_D_A;
        *de += ch;
        // DEC_C;
        // IF_NZ goto ComponentFromString;
    } while(--c != 0);
    // RET;
}

static uint16_t ClockResetPassword_CalculatePassword(void){
    // LD_A(BANK(sPlayerData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asPlayerData));
    // LD_DE(0);
    struct PlayerData pd;
    Deserialize_PlayerData(&pd, (const uint8_t *)GBToRAMAddr(sPlayerData));
    uint16_t de = 0;
    // LD_HL(sPlayerData + (wPlayerID - wPlayerData));
    // LD_C(2);
    // CALL(aClockResetPassword_ComponentFromNumber);
    ClockResetPassword_ComponentFromNumber(&de, &pd.playerID, 2);
    // LD_HL(sPlayerData + (wPlayerName - wPlayerData));
    // LD_C(NAME_LENGTH_JAPANESE - 1);
    // CALL(aClockResetPassword_ComponentFromString);
    ClockResetPassword_ComponentFromString(&de, pd.playerName, NAME_LENGTH_JAPANESE - 1);
    // LD_HL(sPlayerData + (wMoney - wPlayerData));
    // LD_C(3);
    // CALL(aClockResetPassword_ComponentFromNumber);
    ClockResetPassword_ComponentFromNumber(&de, pd.money, 3);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
    return de;
}

static inline void ClockResetPassword_ConvertToBytes(uint16_t* hl, uint16_t bc, uint8_t a){
    // LD_A_de;
    // DEC_DE;
    // PUSH_HL;
    // LD_HL(0);
    // CALL(aAddNTimes);
    // LD_C_L;
    // LD_B_H;
    // POP_HL;
    // ADD_HL_BC;
    *hl += bc * a;
    // RET;
}

static uint16_t ClockResetPassword_ConvertDecIDToBytes(void){
    // LD_HL(0);
    uint16_t hl = 0;
    // LD_DE(wStringBuffer2 + 4);
    // LD_BC(1);
    // CALL(aClockResetPassword_ConvertToBytes);
    ClockResetPassword_ConvertToBytes(&hl, 1, wram->wStringBuffer2[4]);
    // LD_BC(10);
    // CALL(aClockResetPassword_ConvertToBytes);
    ClockResetPassword_ConvertToBytes(&hl, 10, wram->wStringBuffer2[3]);
    // LD_BC(100);
    // CALL(aClockResetPassword_ConvertToBytes);
    ClockResetPassword_ConvertToBytes(&hl, 100, wram->wStringBuffer2[2]);
    // LD_BC(1000);
    // CALL(aClockResetPassword_ConvertToBytes);
    ClockResetPassword_ConvertToBytes(&hl, 1000, wram->wStringBuffer2[1]);
    // LD_BC(10000);
    ClockResetPassword_ConvertToBytes(&hl, 10000, wram->wStringBuffer2[0]);
    return hl;
}

static inline uint8_t* ClockResetPassword_getcurrentdigit(void){
    // LD_A_addr(wStringBuffer2 + 5);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wStringBuffer2);
    // ADD_HL_DE;
    // RET;
    return wram->wStringBuffer2 + wram->wStringBuffer2[CLOCK_RESET_CURSOR];
}
static void ClockResetPassword_dpadinput(uint8_t input){
    // LD_A_B;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(input & D_LEFT) {
    // left:
        // LD_A_addr(wStringBuffer2 + 5);
        // AND_A_A;
        // RET_Z ;
        if(wram->wStringBuffer2[CLOCK_RESET_CURSOR] == 0)
            return;
        // DEC_A;
        // LD_addr_A(wStringBuffer2 + 5);
        wram->wStringBuffer2[CLOCK_RESET_CURSOR]--;
        // RET;
        return;
    }
    // LD_A_B;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    else if(input & D_RIGHT) {
    // right:
        // LD_A_addr(wStringBuffer2 + 5);
        // CP_A(4);
        // RET_Z ;
        if(wram->wStringBuffer2[CLOCK_RESET_CURSOR] == CLOCK_RESET_PASSWORD_LENGTH)
            return;
        // INC_A;
        // LD_addr_A(wStringBuffer2 + 5);
        wram->wStringBuffer2[CLOCK_RESET_CURSOR]++;
        // RET;
    }
    // LD_A_B;
    // AND_A(D_UP);
    // IF_NZ goto up;
    else if(input & D_UP) {
    // up:
        // CALL(aClockResetPassword_getcurrentdigit);
        uint8_t* digit = ClockResetPassword_getcurrentdigit();
        // LD_A_hl;
        // CP_A(9);
        // IF_Z goto wraparound_up;
        if(*digit == 9) {
        // wraparound_up:
            // LD_hl(0);
            *digit = 0;
            // RET;
            return;
        }
        // INC_A;
        // LD_hl_A;
        (*digit)++;
        // RET;
        return;
    }
    // LD_A_B;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(input & D_DOWN) {
    // down:
        // CALL(aClockResetPassword_getcurrentdigit);
        uint8_t* digit = ClockResetPassword_getcurrentdigit();
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto wraparound_down;
        if(*digit == 0) {
        // wraparound_down:
            // LD_hl(9);
            *digit = 9;
            // RET;
            return;
        }
        // DEC_A;
        // LD_hl_A;
        (*digit)--;
        // RET;
        return;
    }
    // RET;
}

bool ClockResetPassword(void){
    static const txt_cmd_s PasswordAskEnterText[] = {
        text_far(v_PasswordAskEnterText)
        text_end
    };
    // CALL(aClockResetPassword_CalculatePassword);
    // PUSH_DE;
    uint16_t password = ClockResetPassword_CalculatePassword();
    // LD_HL(wStringBuffer2);
    // LD_BC(5);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wStringBuffer2, CLOCK_RESET_CURSOR, 0);
    // LD_A(4);
    // LD_addr_A(wStringBuffer2 + 5);
    wram->wStringBuffer2[CLOCK_RESET_CURSOR] = CLOCK_RESET_PASSWORD_LENGTH;
    // LD_HL(mClockResetPassword_PasswordAskEnterText);
    // CALL(aPrintText);
    PrintText(PasswordAskEnterText);

    while(1) {
    // loop:
        // CALL(aClockResetPassword_updateIDdisplay);
        ClockResetPassword_updateIDdisplay();

        do {
        // loop2:
            // CALL(aJoyTextDelay);
            JoyTextDelay();
            // LDH_A_addr(hJoyLast);
            // LD_B_A;
            // AND_A(A_BUTTON);
            // IF_NZ goto confirm;
            if(hram.hJoyLast & A_BUTTON) {
            // confirm:
                // CALL(aClockResetPassword_ConvertDecIDToBytes);
                uint16_t entered = ClockResetPassword_ConvertDecIDToBytes();
                // POP_DE;
                // LD_A_E;
                // CP_A_L;
                // IF_NZ goto nope;
                // LD_A_D;
                // CP_A_H;
                // IF_NZ goto nope;
                if(entered == password) {
                    // AND_A_A;
                    // RET;
                    return true;
                }
                else {
                // nope:
                    // SCF;
                    // RET;
                    return false;
                }
            }
            // LD_A_B;
            // AND_A(D_PAD);
            // IF_Z goto loop2;
        } while((hram.hJoyLast & (D_PAD)) == 0);
        // CALL(aClockResetPassword_dpadinput);
        ClockResetPassword_dpadinput(hram.hJoyLast);
        // LD_C(3);
        // CALL(aDelayFrames);
        DelayFrames(3);
        // goto loop;
    }
}
