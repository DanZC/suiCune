#include "../../constants.h"
#include "reset_password.h"
#include "../../home/audio.h"
#include "../../home/tilemap.h"
#include "../../home/gfx.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/sram.h"
#include "../overworld/player_object.h"
#include "../../data/text/common.h"

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
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // LD_DE(MUSIC_MAIN_MENU);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_MAIN_MENU);
    // LD_HL(mv_ResetClock_PasswordAskResetClockText);
    // CALL(aPrintText);
    PrintText_Conv2(PasswordAskResetClockText);
    // LD_HL(mv_ResetClock_NoYes_MenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&NoYes_MenuHeader);
    // CALL(aVerticalMenu);
    // RET_C ;
    // LD_A_addr(wMenuCursorY);
    // CP_A(1);
    // RET_Z ;
    if(!VerticalMenu_Conv() || wram->wMenuCursorY == 1)
        return;
// TODO: Actually convert clock reset password system.
// For now, the system is automatically bypassed.
    // CALL(aClockResetPassword);
    // IF_C goto wrongpassword;
    // LD_A(BANK(sRTCStatusFlags));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asRTCStatusFlags));
    // LD_A(0x80);
    // LD_addr_A(sRTCStatusFlags);
    gb_write(sRTCStatusFlags, 0x80);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_HL(mv_ResetClock_PasswordAskResetText);
    // CALL(aPrintText);
    PrintText_Conv2(PasswordAskResetText);
    // RET;
    return;

wrongpassword:
    // LD_HL(mv_ResetClock_PasswordWrongText);
    // CALL(aPrintText);
    PrintText_Conv2(PasswordWrongText);
    // RET;
    return;
}

void ClockResetPassword(void){
    CALL(aClockResetPassword_CalculatePassword);
    PUSH_DE;
    LD_HL(wStringBuffer2);
    LD_BC(5);
    XOR_A_A;
    CALL(aByteFill);
    LD_A(4);
    LD_addr_A(wStringBuffer2 + 5);
    LD_HL(mClockResetPassword_PasswordAskEnterText);
    CALL(aPrintText);

loop:
    CALL(aClockResetPassword_updateIDdisplay);

loop2:
    CALL(aJoyTextDelay);
    LDH_A_addr(hJoyLast);
    LD_B_A;
    AND_A(A_BUTTON);
    IF_NZ goto confirm;
    LD_A_B;
    AND_A(D_PAD);
    IF_Z goto loop2;
    CALL(aClockResetPassword_dpadinput);
    LD_C(3);
    CALL(aDelayFrames);
    goto loop;


confirm:
    CALL(aClockResetPassword_ConvertDecIDToBytes);
    POP_DE;
    LD_A_E;
    CP_A_L;
    IF_NZ goto nope;
    LD_A_D;
    CP_A_H;
    IF_NZ goto nope;
    AND_A_A;
    RET;


nope:
    SCF;
    RET;


PasswordAskEnterText:
    //text_far ['_PasswordAskEnterText']
    //text_end ['?']


updateIDdisplay:
    hlcoord(14, 15, wTilemap);
    LD_DE(wStringBuffer2);
    LD_C(5);

loop3:
    LD_A_de;
    ADD_A(0xf6);
    LD_hli_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop3;
    hlcoord(14, 16, wTilemap);
    LD_BC(5);
    LD_A(0x7f);
    CALL(aByteFill);
    hlcoord(14, 16, wTilemap);
    LD_A_addr(wStringBuffer2 + 5);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_hl(0x61);
    RET;


dpadinput:
    LD_A_B;
    AND_A(D_LEFT);
    IF_NZ goto left;
    LD_A_B;
    AND_A(D_RIGHT);
    IF_NZ goto right;
    LD_A_B;
    AND_A(D_UP);
    IF_NZ goto up;
    LD_A_B;
    AND_A(D_DOWN);
    IF_NZ goto down;
    RET;


left:
    LD_A_addr(wStringBuffer2 + 5);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wStringBuffer2 + 5);
    RET;


right:
    LD_A_addr(wStringBuffer2 + 5);
    CP_A(4);
    RET_Z ;
    INC_A;
    LD_addr_A(wStringBuffer2 + 5);
    RET;


up:
    CALL(aClockResetPassword_getcurrentdigit);
    LD_A_hl;
    CP_A(9);
    IF_Z goto wraparound_up;
    INC_A;
    LD_hl_A;
    RET;


wraparound_up:
    LD_hl(0);
    RET;


down:
    CALL(aClockResetPassword_getcurrentdigit);
    LD_A_hl;
    AND_A_A;
    IF_Z goto wraparound_down;
    DEC_A;
    LD_hl_A;
    RET;


wraparound_down:
    LD_hl(9);
    RET;


getcurrentdigit:
    LD_A_addr(wStringBuffer2 + 5);
    LD_E_A;
    LD_D(0);
    LD_HL(wStringBuffer2);
    ADD_HL_DE;
    RET;


ConvertDecIDToBytes:
    LD_HL(0);
    LD_DE(wStringBuffer2 + 4);
    LD_BC(1);
    CALL(aClockResetPassword_ConvertToBytes);
    LD_BC(10);
    CALL(aClockResetPassword_ConvertToBytes);
    LD_BC(100);
    CALL(aClockResetPassword_ConvertToBytes);
    LD_BC(1000);
    CALL(aClockResetPassword_ConvertToBytes);
    LD_BC(10000);

ConvertToBytes:
    LD_A_de;
    DEC_DE;
    PUSH_HL;
    LD_HL(0);
    CALL(aAddNTimes);
    LD_C_L;
    LD_B_H;
    POP_HL;
    ADD_HL_BC;
    RET;


CalculatePassword:
    LD_A(BANK(sPlayerData));
    CALL(aOpenSRAM);
    LD_DE(0);
    LD_HL(sPlayerData + (wPlayerID - wPlayerData));
    LD_C(2);
    CALL(aClockResetPassword_ComponentFromNumber);
    LD_HL(sPlayerData + (wPlayerName - wPlayerData));
    LD_C(NAME_LENGTH_JAPANESE - 1);
    CALL(aClockResetPassword_ComponentFromString);
    LD_HL(sPlayerData + (wMoney - wPlayerData));
    LD_C(3);
    CALL(aClockResetPassword_ComponentFromNumber);
    CALL(aCloseSRAM);
    RET;


ComponentFromNumber:
    LD_A_hli;
    ADD_A_E;
    LD_E_A;
    LD_A(0);
    ADC_A_D;
    LD_D_A;
    DEC_C;
    IF_NZ goto ComponentFromNumber;
    RET;


ComponentFromString:
    LD_A_hli;
    CP_A(0x50);
    RET_Z ;
    ADD_A_E;
    LD_E_A;
    LD_A(0);
    ADC_A_D;
    LD_D_A;
    DEC_C;
    IF_NZ goto ComponentFromString;
    RET;

}
