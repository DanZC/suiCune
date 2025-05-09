#include "../../constants.h"
#include "options_menu.h"
#include "../../home/delay.h"
#include "../../home/audio.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/gfx.h"
#include "../../home/joypad.h"

//  GetOptionPointer.Pointers indexes
enum {
    OPT_TEXT_SPEED,  // 0
    OPT_BATTLE_SCENE,  // 1
    OPT_BATTLE_STYLE,  // 2
    OPT_SOUND,  // 3
    OPT_PRINT,  // 4
    OPT_MENU_ACCOUNT,  // 5
    OPT_FRAME,  // 6
    OPT_CANCEL,  // 7
};
#define NUM_OPTIONS (OPT_CANCEL + 1)  //  8

struct OptionRes {
    uint8_t c;
    uint8_t d;
    uint8_t e;
};

static bool Options_TextSpeed(void);
static bool GetOptionPointer(void);
static struct OptionRes GetTextSpeed(void);
static struct OptionRes GetPrinterSetting(void);
static bool Options_Cancel(void);
static bool OptionsControl(void);

void v_Option(void){
#if BUGFIX_OPTIONS_MENU_JOYPAD
    ClearJoypad();
#endif
    // LD_HL(hInMenu);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_hl(TRUE);
    hram->hInMenu = TRUE;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // hlcoord(0, 0, wTilemap);
    // LD_B(SCREEN_HEIGHT - 2);
    // LD_C(SCREEN_WIDTH - 2);
    // CALL(aTextbox);
    Textbox(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT - 2, SCREEN_WIDTH - 2);
    // hlcoord(2, 2, wTilemap);
    // LD_DE(mStringOptions);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(StringOptions), coord(2, 2, wram->wTilemap));
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;

//  display the settings of each option when the menu is opened
    // LD_C(NUM_OPTIONS - 2);  // omit frame type, the last option
    uint8_t c = NUM_OPTIONS - 2;

    do {
    // print_text_loop:
        // PUSH_BC;
        // XOR_A_A;
        // LDH_addr_A(hJoyLast);
        hram->hJoyLast = 0;
        // CALL(aGetOptionPointer);
        GetOptionPointer();
        // POP_BC;
        // LD_HL(wJumptableIndex);
        // INC_hl;
        wram->wJumptableIndex++;
        // DEC_C;
        // IF_NZ goto print_text_loop;
    } while(--c != 0);
    // CALL(aUpdateFrame);  // display the frame type
    UpdateFrame();

    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // INC_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_DIPLOMA);
    // CALL(aSetPalettes);
    SetPalettes();

    while(1) {
    // joypad_loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LDH_A_addr(hJoyPressed);
        // AND_A(START | B_BUTTON);
        // IF_NZ goto ExitOptions;
        if(hram->hJoyPressed & (START | B_BUTTON))
            break;
        // CALL(aOptionsControl);
        // IF_C goto dpad;
        if(OptionsControl() || !GetOptionPointer()) {
        // dpad:
            // CALL(aOptions_UpdateCursorPosition);
            Options_UpdateCursorPosition();
            // LD_C(3);
            // CALL(aDelayFrames);
            DelayFrames(3);
            // goto joypad_loop;
            continue;
        }
        // CALL(aGetOptionPointer);
        // IF_C goto ExitOptions;
        break;

    // dpad:
        // CALL(aOptions_UpdateCursorPosition);
        // LD_C(3);
        // CALL(aDelayFrames);
        // goto joypad_loop;
    }


// ExitOptions:
    // LD_DE(SFX_TRANSACTION);
    // CALL(aPlaySFX);
    PlaySFX(SFX_TRANSACTION);
    // CALL(aWaitSFX);
    WaitSFX();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // RET;
}

const char StringOptions[] =
    "TEXT SPEED<LF>"
    "        :<LF>"
    "BATTLE SCENE<LF>"
    "        :<LF>"
    "BATTLE STYLE<LF>"
    "        :<LF>"
    "SOUND<LF>"
    "        :<LF>"
    "PRINT<LF>"
    "        :<LF>"
    "MENU ACCOUNT<LF>"
    "        :<LF>"
    "FRAME<LF>"
    "        :TYPE<LF>"
    "CANCEL@";

static bool GetOptionPointer(void){
    //jumptable ['.Pointers', 'wJumptableIndex']

    switch(wram->wJumptableIndex) {
    // Pointers:
    //  entries correspond to OPT_* constants
        //dw ['Options_TextSpeed'];
        case OPT_TEXT_SPEED: return Options_TextSpeed();
        //dw ['Options_BattleScene'];
        case OPT_BATTLE_SCENE: return Options_BattleScene();
        //dw ['Options_BattleStyle'];
        case OPT_BATTLE_STYLE: return Options_BattleStyle();
        //dw ['Options_Sound'];
        case OPT_SOUND: return Options_Sound();
        //dw ['Options_Print'];
        case OPT_PRINT: return Options_Print();
        //dw ['Options_MenuAccount'];
        case OPT_MENU_ACCOUNT: return Options_MenuAccount();
        //dw ['Options_Frame'];
        case OPT_FRAME: return Options_Frame();
        //dw ['Options_Cancel'];
        default:
        case OPT_CANCEL: return Options_Cancel();
    }
}

enum {
    OPT_TEXT_SPEED_FAST,  // 0
    OPT_TEXT_SPEED_MED,  // 1
    OPT_TEXT_SPEED_SLOW,  // 2
    OPT_TEXT_SPEED_INSTANT,  // 3
};

static bool Options_TextSpeed(void){
    static const char* Strings[] = {
    //  entries correspond to OPT_TEXT_SPEED_* constants
        //dw ['.Fast'];
        // Fast:
        [OPT_TEXT_SPEED_FAST]       = "FAST   @",
        //dw ['.Mid'];
        // Mid:
        [OPT_TEXT_SPEED_MED]        = "MID    @",
        //dw ['.Slow'];
        // Slow:
        [OPT_TEXT_SPEED_SLOW]       = "SLOW   @",
        [OPT_TEXT_SPEED_INSTANT]    = "INSTANT@",
    };
    // CALL(aGetTextSpeed);
    struct OptionRes res = GetTextSpeed();
    // LDH_A_addr(hJoyPressed);
    // BIT_A(D_LEFT_F);
    // IF_NZ goto LeftPressed;
    if(bit_test(hram->hJoyPressed, D_LEFT_F)) {
    // LeftPressed:
        // LD_A_C;
        // AND_A_A;
        // IF_NZ goto Decrease;
        if(res.c == OPT_TEXT_SPEED_FAST) {
            // LD_C(OPT_TEXT_SPEED_SLOW + 1);
            res.c = OPT_TEXT_SPEED_INSTANT;
        }
        else {
        // Decrease:
            // DEC_C;
            res.c--;
        }
        // LD_A_D;
        wram->wOptions = (wram->wOptions & 0xf0) | res.d;
    }
    // BIT_A(D_RIGHT_F);
    // IF_Z goto NonePressed;
    else if(bit_test(hram->hJoyPressed, D_RIGHT_F)) {
        // LD_A_C;  // right pressed
        // CP_A(OPT_TEXT_SPEED_SLOW);
        // IF_C goto Increase;
        if(res.c == OPT_TEXT_SPEED_INSTANT) {
            // LD_C(OPT_TEXT_SPEED_FAST - 1);
            res.c = OPT_TEXT_SPEED_FAST;
        }
        else {
        // Increase:
            // INC_C;
            res.c++;
        }
        // LD_A_E;
        // goto Save;
    // Save:
        // LD_B_A;
        // LD_A_addr(wOptions);
        // AND_A(0xf0);
        // OR_A_B;
        // LD_addr_A(wOptions);
        wram->wOptions = (wram->wOptions & 0xf0) | res.e;
    }

// NonePressed:
    // LD_B(0);
    // LD_HL(mOptions_TextSpeed_Strings);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // hlcoord(11, 3, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Strings[res.c]), coord(11, 3, wram->wTilemap));
    // AND_A_A;
    // RET;
    return false;
}

//  converts TEXT_DELAY_* value in a to OPT_TEXT_SPEED_* value in c,
//  with previous/next TEXT_DELAY_* values in d/e
static struct OptionRes GetTextSpeed(void){
    // LD_A_addr(wOptions);
    // AND_A(TEXT_DELAY_MASK);
    // CP_A(TEXT_DELAY_SLOW);
    // IF_Z goto slow;
    if((wram->wOptions & TEXT_DELAY_MASK) == TEXT_DELAY_SLOW) {
    // slow:
        // LD_C(OPT_TEXT_SPEED_SLOW);
        // LD_DE((TEXT_DELAY_MED << 8) | TEXT_DELAY_FAST);
        // RET;
        return (struct OptionRes){.c=OPT_TEXT_SPEED_SLOW, .d=TEXT_DELAY_MED, .e=TEXT_DELAY_INSTANT};
    }
    // CP_A(TEXT_DELAY_FAST);
    // IF_Z goto fast;
    if((wram->wOptions & TEXT_DELAY_MASK) == TEXT_DELAY_FAST) {
    // fast:
        // LD_C(OPT_TEXT_SPEED_FAST);
        // LD_DE((TEXT_DELAY_SLOW << 8) | TEXT_DELAY_MED);
        // RET;
        return (struct OptionRes){.c=OPT_TEXT_SPEED_FAST, .d=TEXT_DELAY_INSTANT, .e=TEXT_DELAY_MED};
    }

    if((wram->wOptions & TEXT_DELAY_MASK) == TEXT_DELAY_INSTANT) {
        return (struct OptionRes){.c=OPT_TEXT_SPEED_INSTANT, .d=TEXT_DELAY_SLOW, .e=TEXT_DELAY_FAST};
    }
// none of the above
    // LD_C(OPT_TEXT_SPEED_MED);
    // LD_DE((TEXT_DELAY_FAST << 8) | TEXT_DELAY_SLOW);
    // RET;
    return (struct OptionRes){.c=OPT_TEXT_SPEED_MED, .d=TEXT_DELAY_FAST, .e=TEXT_DELAY_SLOW};
}

bool Options_BattleScene(void){
    static const char On[] = "ON @";
    static const char Off[] = "OFF@";
    // LD_HL(wOptions);
    // LDH_A_addr(hJoyPressed);
    // BIT_A(D_LEFT_F);
    // IF_NZ goto LeftPressed;
    if(bit_test(hram->hJoyPressed, D_LEFT_F) || bit_test(hram->hJoyPressed, D_RIGHT_F)) {
        bit_toggle(wram->wOptions, BATTLE_SCENE);
    }
    // BIT_A(D_RIGHT_F);
    // IF_Z goto NonePressed;
    // BIT_hl(BATTLE_SCENE);
    // IF_NZ goto ToggleOn;
    // goto ToggleOff;


// LeftPressed:
    // BIT_hl(BATTLE_SCENE);
    // IF_Z goto ToggleOff;
    // goto ToggleOn;


// NonePressed:
    // BIT_hl(BATTLE_SCENE);
    // IF_Z goto ToggleOn;
    // goto ToggleOff;


// ToggleOn:
    // RES_hl(BATTLE_SCENE);
    // LD_DE(mOptions_BattleScene_On);
    // goto Display;


// ToggleOff:
    // SET_hl(BATTLE_SCENE);
    // LD_DE(mOptions_BattleScene_Off);


// Display:
    // hlcoord(11, 5, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C((bit_test(wram->wOptions, BATTLE_SCENE))? Off: On), coord(11, 5, wram->wTilemap));
    // AND_A_A;
    // RET;
    return false;
}

bool Options_BattleStyle(void){
    static const char Shift[] = "SHIFT@";
    static const char Set[] = "SET  @";
    // LD_HL(wOptions);
    // LDH_A_addr(hJoyPressed);
    // BIT_A(D_LEFT_F);
    // IF_NZ goto LeftPressed;
    if(bit_test(hram->hJoyPressed, D_LEFT_F) || bit_test(hram->hJoyPressed, D_RIGHT_F)) {
    // LeftPressed:
        // BIT_hl(BATTLE_SHIFT);
        // IF_Z goto ToggleSet;
        // goto ToggleShift;
        bit_toggle(wram->wOptions, BATTLE_SHIFT);
    }
    // BIT_A(D_RIGHT_F);
    // IF_Z goto NonePressed;
    // BIT_hl(BATTLE_SHIFT);
    // IF_NZ goto ToggleShift;
    // goto ToggleSet;


// NonePressed:
    // BIT_hl(BATTLE_SHIFT);
    // IF_NZ goto ToggleSet;


// ToggleShift:
    // RES_hl(BATTLE_SHIFT);
    // LD_DE(mOptions_BattleStyle_Shift);
    // goto Display;


// ToggleSet:
    // SET_hl(BATTLE_SHIFT);
    // LD_DE(mOptions_BattleStyle_Set);


// Display:
    // hlcoord(11, 7, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C((bit_test(wram->wOptions, BATTLE_SHIFT))? Set: Shift), coord(11, 7, wram->wTilemap));
    // AND_A_A;
    // RET;
    return false;
}

bool Options_Sound(void){
    static const char Mono[] = "MONO  @";
    static const char Stereo[] = "STEREO@";
    // LD_HL(wOptions);
    // LDH_A_addr(hJoyPressed);
    // BIT_A(D_LEFT_F);
    // IF_NZ goto LeftPressed;
    if(bit_test(hram->hJoyPressed, D_LEFT_F) || bit_test(hram->hJoyPressed, D_RIGHT_F)) {
    // LeftPressed:
        // BIT_hl(STEREO);
        // IF_Z goto SetStereo;
        // goto SetMono;
        bit_toggle(wram->wOptions, STEREO);
        RestartMapMusic();
    }
    // BIT_A(D_RIGHT_F);
    // IF_Z goto NonePressed;
    // BIT_hl(STEREO);
    // IF_NZ goto SetMono;
    // goto SetStereo;

// NonePressed:
    // BIT_hl(STEREO);
    // IF_NZ goto ToggleStereo;
    // goto ToggleMono;


// SetMono:
    // RES_hl(STEREO);
    // CALL(aRestartMapMusic);


// ToggleMono:
    // LD_DE(mOptions_Sound_Mono);
    // goto Display;


// SetStereo:
    // SET_hl(STEREO);
    // CALL(aRestartMapMusic);


// ToggleStereo:
    // LD_DE(mOptions_Sound_Stereo);


// Display:
    // hlcoord(11, 9, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C((bit_test(wram->wOptions, STEREO))? Stereo: Mono), coord(11, 9, wram->wTilemap));
    // AND_A_A;
    // RET;
    return false;
}

enum {
    OPT_PRINT_LIGHTEST,  // 0
    OPT_PRINT_LIGHTER,  // 1
    OPT_PRINT_NORMAL,  // 2
    OPT_PRINT_DARKER,  // 3
    OPT_PRINT_DARKEST,  // 4
};

bool Options_Print(void){
    static const char* Strings[] = {
    //  entries correspond to OPT_PRINT_* constants
        //dw ['.Lightest'];
        [OPT_PRINT_LIGHTEST]= "LIGHTEST@",
        //dw ['.Lighter'];
        [OPT_PRINT_LIGHTER] = "LIGHTER @",
        //dw ['.Normal'];
        [OPT_PRINT_NORMAL]  = "NORMAL  @",
        //dw ['.Darker'];
        [OPT_PRINT_DARKER]  = "DARKER  @",
        //dw ['.Darkest'];
        [OPT_PRINT_DARKEST] = "DARKEST @",
    };
    // CALL(aGetPrinterSetting);
    struct OptionRes res = GetPrinterSetting();
    // LDH_A_addr(hJoyPressed);
    // BIT_A(D_LEFT_F);
    // IF_NZ goto LeftPressed;
    if(bit_test(hram->hJoyPressed, D_LEFT_F)) {
    // LeftPressed:
        // LD_A_C;
        // AND_A_A;
        // IF_NZ goto Decrease;
        if(res.c == OPT_PRINT_LIGHTEST) {
            // LD_C(OPT_PRINT_DARKEST + 1);
            res.c = OPT_PRINT_DARKEST;
        }
        else {
        // Decrease:
            // DEC_C;
            res.c--;
        }
        // LD_A_D;
        wram->wGBPrinterBrightness = res.d;
    }
    // BIT_A(D_RIGHT_F);
    // IF_Z goto NonePressed;
    else if(bit_test(hram->hJoyPressed, D_RIGHT_F)) {
        // LD_A_C;
        // CP_A(OPT_PRINT_DARKEST);
        // IF_C goto Increase;
        if(res.c >= OPT_PRINT_DARKEST) {
            // LD_C(OPT_PRINT_LIGHTEST - 1);
            res.c = OPT_PRINT_LIGHTEST;
        }

        else {
        // Increase:
            // INC_C;
            res.c++;
        }
        // LD_A_E;
        // goto Save;
        wram->wGBPrinterBrightness = res.e;
    }

// Save:
    // LD_B_A;
    // LD_addr_A(wGBPrinterBrightness);


// NonePressed:
    // LD_B(0);
    // LD_HL(mOptions_Print_Strings);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // hlcoord(11, 11, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Strings[res.c]), coord(11, 11, wram->wTilemap));
    // AND_A_A;
    // RET;
    return false;
}

//  converts GBPRINTER_* value in a to OPT_PRINT_* value in c,
//  with previous/next GBPRINTER_* values in d/e
static struct OptionRes GetPrinterSetting(void){
    // LD_A_addr(wGBPrinterBrightness);
    switch(wram->wGBPrinterBrightness) {
    // AND_A_A;
    // IF_Z goto IsLightest;
    case GBPRINTER_LIGHTEST:
    // IsLightest:
        // LD_C(OPT_PRINT_LIGHTEST);
        // LD_DE((GBPRINTER_DARKEST << 8) | GBPRINTER_LIGHTER);
        // RET;
        return (struct OptionRes){.c=OPT_PRINT_LIGHTEST, .d=GBPRINTER_DARKEST, .e=GBPRINTER_LIGHTER};
    // CP_A(GBPRINTER_LIGHTER);
    // IF_Z goto IsLight;
    case GBPRINTER_LIGHTER:
    // IsLight:
        // LD_C(OPT_PRINT_LIGHTER);
        // LD_DE((GBPRINTER_LIGHTEST << 8) | GBPRINTER_NORMAL);
        // RET;
        return (struct OptionRes){.c=OPT_PRINT_LIGHTER, .d=GBPRINTER_LIGHTEST, .e=GBPRINTER_NORMAL};
    // CP_A(GBPRINTER_DARKER);
    // IF_Z goto IsDark;
    case GBPRINTER_DARKER:
    // IsDark:
        // LD_C(OPT_PRINT_DARKER);
        // LD_DE((GBPRINTER_NORMAL << 8) | GBPRINTER_DARKEST);
        // RET;
        return (struct OptionRes){.c=OPT_PRINT_DARKER, .d=GBPRINTER_NORMAL, .e=GBPRINTER_DARKEST};
    // CP_A(GBPRINTER_DARKEST);
    // IF_Z goto IsDarkest;
    case GBPRINTER_DARKEST:
    // IsDarkest:
        // LD_C(OPT_PRINT_DARKEST);
        // LD_DE((GBPRINTER_DARKER << 8) | GBPRINTER_LIGHTEST);
        // RET;
        return (struct OptionRes){.c=OPT_PRINT_DARKEST, .d=GBPRINTER_DARKER, .e=GBPRINTER_LIGHTEST};
// none of the above
    default:
    case GBPRINTER_NORMAL:
        // LD_C(OPT_PRINT_NORMAL);
        // LD_DE((GBPRINTER_LIGHTER << 8) | GBPRINTER_DARKER);
        // RET;
        return (struct OptionRes){.c=OPT_PRINT_NORMAL, .d=GBPRINTER_LIGHTER, .e=GBPRINTER_DARKER};
    }
}

bool Options_MenuAccount(void){
    static const char Off[] = "OFF@";
    static const char On[] = "ON @";

    // LD_HL(wOptions2);
    // LDH_A_addr(hJoyPressed);
    // BIT_A(D_LEFT_F);
    // IF_NZ goto LeftPressed;
    if(bit_test(hram->hJoyPressed, D_LEFT_F) || bit_test(hram->hJoyPressed, D_RIGHT_F)) {
        bit_toggle(wram->wOptions2, MENU_ACCOUNT);
    }
    // BIT_A(D_RIGHT_F);
    // IF_Z goto NonePressed;
    // BIT_hl(MENU_ACCOUNT);
    // IF_NZ goto ToggleOff;
    // goto ToggleOn;


// LeftPressed:
    // BIT_hl(MENU_ACCOUNT);
    // IF_Z goto ToggleOn;
    // goto ToggleOff;


// NonePressed:
    // BIT_hl(MENU_ACCOUNT);
    // IF_NZ goto ToggleOn;


// ToggleOff:
    // RES_hl(MENU_ACCOUNT);
    // LD_DE(mOptions_MenuAccount_Off);
    // goto Display;


// ToggleOn:
    // SET_hl(MENU_ACCOUNT);
    // LD_DE(mOptions_MenuAccount_On);


// Display:
    // hlcoord(11, 13, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C((bit_test(wram->wOptions2, MENU_ACCOUNT))? On: Off), coord(11, 13, wram->wTilemap));
    // AND_A_A;
    // RET;
    return false;
}

bool Options_Frame(void){
    // LD_HL(wTextboxFrame);
    // LDH_A_addr(hJoyPressed);
    // BIT_A(D_LEFT_F);
    // IF_NZ goto LeftPressed;
    if(bit_test(hram->hJoyPressed, D_LEFT_F)) {
    // LeftPressed:
        // LD_A_hl;
        // DEC_A;
    // Save:
        // maskbits(NUM_FRAMES, 0);
        // LD_hl_A;
        wram->wTextboxFrame = (wram->wTextboxFrame - 1) & 7;
        return UpdateFrame();
    }
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto RightPressed;
    else if(bit_test(hram->hJoyPressed, D_RIGHT_F)) {
    // RightPressed:
        // LD_A_hl;
        // INC_A;
        // goto Save;

    // Save:
        // maskbits(NUM_FRAMES, 0);
        // LD_hl_A;
        wram->wTextboxFrame = (wram->wTextboxFrame + 1) & 7;
        return UpdateFrame();
    }
    // AND_A_A;
    // RET;

    return false;
}

bool UpdateFrame(void){
    // LD_A_addr(wTextboxFrame);
    // hlcoord(16, 15, wTilemap);  // where on the screen the number is drawn
    // ADD_A(0xf7);
    // LD_hl_A;
    *coord(16, 15, wram->wTilemap) = 0xf7 + wram->wTextboxFrame;
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // AND_A_A;
    // RET;
    return false;
}

static bool Options_Cancel(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON);
    // IF_NZ goto Exit;
    if(hram->hJoyPressed & A_BUTTON) {
    // Exit:
        // SCF;
        // RET;
        return true;
    }
    // AND_A_A;
    // RET;
    return false;
}

static bool OptionsControl(void){
    // LD_HL(wJumptableIndex);
    // LDH_A_addr(hJoyLast);
    // CP_A(D_DOWN);
    // IF_Z goto DownPressed;
    if(hram->hJoyLast == D_DOWN) {
    // DownPressed:
        // LD_A_hl;
        // CP_A(OPT_CANCEL);  // maximum option index
        // IF_NZ goto CheckMenuAccount;
        if(wram->wJumptableIndex != OPT_CANCEL) {
        // CheckMenuAccount:
        //   //  I have no idea why this exists...
            // CP_A(OPT_MENU_ACCOUNT);
            // IF_NZ goto Increase;
            // LD_hl(OPT_MENU_ACCOUNT);
            if(wram->wJumptableIndex == OPT_MENU_ACCOUNT)
                wram->wJumptableIndex = OPT_MENU_ACCOUNT;

        // Increase:
            // INC_hl;
            wram->wJumptableIndex++;
            // SCF;
            // RET;
            return true;
        }
        else {
            // LD_hl(OPT_TEXT_SPEED);  // first option
            wram->wJumptableIndex = OPT_TEXT_SPEED;
            // SCF;
            // RET;
            return true;
        }
    }
    // CP_A(D_UP);
    // IF_Z goto UpPressed;
    else if(hram->hJoyLast == D_UP) {
    // UpPressed:
        // LD_A_hl;

    //  Another thing where I'm not sure why it exists
        // CP_A(OPT_FRAME);
        // IF_NZ goto NotFrame;
        if(wram->wJumptableIndex == OPT_FRAME) {
            // LD_hl(OPT_MENU_ACCOUNT);
            wram->wJumptableIndex = OPT_MENU_ACCOUNT;
            // SCF;
            // RET;
            return true;
        }

    // NotFrame:
        // AND_A_A;  // OPT_TEXT_SPEED, minimum option index
        // IF_NZ goto Decrease;
        if(wram->wJumptableIndex == OPT_TEXT_SPEED) {
            // LD_hl(NUM_OPTIONS);  // decrements to OPT_CANCEL, maximum option index
            wram->wJumptableIndex = NUM_OPTIONS;
        }

    // Decrease:
        // DEC_hl;
        wram->wJumptableIndex--;
        // SCF;
        // RET;
        return true;
    }
    // AND_A_A;
    // RET;
    return false;
}

void Options_UpdateCursorPosition(void){
    // hlcoord(1, 1, wTilemap);
    // LD_DE(SCREEN_WIDTH);
    // LD_C(SCREEN_HEIGHT - 2);

    for(uint32_t c = 0; c < SCREEN_HEIGHT - 2; ++c) {
    // loop:
        // LD_hl(0x7f);
        *coord(1, 1 + c, wram->wTilemap) = 0x7f;
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // hlcoord(1, 2, wTilemap);
    // LD_BC(2 * SCREEN_WIDTH);
    // LD_A_addr(wJumptableIndex);
    // CALL(aAddNTimes);
    // LD_hl(0xed);
    *coord(1, 2 + (2 * wram->wJumptableIndex), wram->wTilemap) = 0xed;
    // RET;
}
