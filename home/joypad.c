#include "../constants.h"
#include "joypad.h"
#include "delay.h"
#include "audio.h"
#include "tilemap.h"
#include "../charmap.h"
#include "time_palettes.h"
#include "../engine/events/catch_tutorial_input.h"

const uint8_t* gAutoInputAddress = NULL;

void Joypad(void) {
        //  Replaced by UpdateJoypad, called from VBlank instead of the useless
    //  joypad interrupt.

    //  This is a placeholder in case the interrupt is somehow enabled.
    RET;
}

void ClearJoypad(void) {
    //  Pressed this frame (delta)
    hram->hJoyPressed = 0;
    //  Currently pressed
    hram->hJoyDown = 0;
}

void UpdateJoypad(void) {
        //  This is called automatically every frame in VBlank.
    //  Read the joypad register and translate it to something more
    //  workable for use in-game. There are 8 buttons, so we can use
    //  one byte to contain all player input.

    //  Updates:

    //  hJoypadReleased: released this frame (delta)
    //  hJoypadPressed: pressed this frame (delta)
    //  hJoypadDown: currently pressed
    //  hJoypadSum: pressed so far

    //  Any of these three bits can be used to disable input.
    LD_A_addr(wJoypadDisable);
    AND_A((1 << JOYPAD_DISABLE_MON_FAINT_F) | (1 << JOYPAD_DISABLE_SGB_TRANSFER_F) | (1 << 4));
    RET_NZ;

    //  If we're saving, input is disabled.
    LD_A_addr(wGameLogicPaused);
    AND_A_A;
    RET_NZ;

    //  We can only get four inputs at a time.
    //  We take d-pad first for no particular reason.
    LD_A(R_DPAD);
    LDH_addr_A(rJOYP);
    //  Read twice to give the request time to take.
    LDH_A_addr(rJOYP);
    LDH_A_addr(rJOYP);

    //  The Joypad register output is in the lo nybble (inversed).
    //  We make the hi nybble of our new container d-pad input.
    CPL;
    AND_A(0xf);
    SWAP_A;

    //  We'll keep this in b for now.
    LD_B_A;

    //  Buttons make 8 total inputs (A, B, Select, Start).
    //  We can fit this into one byte.
    LD_A(R_BUTTONS);
    LDH_addr_A(rJOYP);
    //  Wait for input to stabilize.
    for (int rept = 0; rept < 6; rept++) {
        LDH_A_addr(rJOYP);
    }
    //  Buttons take the lo nybble.
    CPL;
    AND_A(0xf);
    OR_A_B;
    LD_B_A;

    //  Reset the joypad register since we're done with it.
    LD_A(0x30);
    LDH_addr_A(rJOYP);

    //  To get the delta we xor the last frame's input with the new one.
    LDH_A_addr(hJoypadDown);  // last frame
    LD_E_A;
    XOR_A_B;
    LD_D_A;
    //  Released this frame:
    AND_A_E;
    LDH_addr_A(hJoypadReleased);
    //  Pressed this frame:
    LD_A_D;
    AND_A_B;
    LDH_addr_A(hJoypadPressed);

    //  Add any new presses to the list of collective presses:
    LD_C_A;
    LDH_A_addr(hJoypadSum);
    OR_A_C;
    LDH_addr_A(hJoypadSum);

    //  Currently pressed:
    LD_A_B;
    LDH_addr_A(hJoypadDown);

    //  Now that we have the input, we can do stuff with it.

    //  For example, soft reset:
    // AND_A(A_BUTTON | B_BUTTON | SELECT | START);
    // CP_A(A_BUTTON | B_BUTTON | SELECT | START);
    // JP_Z (mReset);

    RET;
}

//  This is called automatically every frame in VBlank.
//  Read the joypad register and translate it to something more
//  workable for use in-game. There are 8 buttons, so we can use
//  one byte to contain all player input.
void UpdateJoypad_Conv(void) {
    //  Updates:

    //  hJoypadReleased: released this frame (delta)
    //  hJoypadPressed: pressed this frame (delta)
    //  hJoypadDown: currently pressed
    //  hJoypadSum: pressed so far

    //  Any of these three bits can be used to disable input.
    uint8_t disable = gb_read(wJoypadDisable);
    if((disable & ((1 << JOYPAD_DISABLE_MON_FAINT_F) | (1 << JOYPAD_DISABLE_SGB_TRANSFER_F) | (1 << 4))) != 0)
        return;

    //  If we're saving, input is disabled.
    if(gb_read(wGameLogicPaused) != 0)
        return;

    //  We can only get four inputs at a time.
    //  We take d-pad first for no particular reason.
    gb_write(rJOYP, R_DPAD);

    //  Read twice to give the request time to take.
    gb_read(rJOYP);
    uint8_t dpad = gb_read(rJOYP);

    //  The Joypad register output is in the lo nybble (inversed).
    //  We make the hi nybble of our new container d-pad input.
    dpad = (dpad ^ 0xFF) & 0xF;
    uint16_t temp = ((dpad << 4) | (dpad >> 4));
    dpad = (uint8_t)temp;

    //  We'll keep this in b for now.

    //  Buttons make 8 total inputs (A, B, Select, Start).
    //  We can fit this into one byte.
    gb_write(rJOYP, R_BUTTONS);

    //  Wait for input to stabilize.
    uint8_t buttons;
    for (int rept = 0; rept < 6; rept++) {
        buttons = gb_read(rJOYP);
    }
    //  Buttons take the lo nybble.
    buttons = (buttons ^ 0xFF) & 0xF;
    uint8_t input = (buttons | dpad);

    //  Reset the joypad register since we're done with it.
    gb_write(rJOYP, 0x30);

    //  To get the delta we xor the last frame's input with the new one.
    uint8_t last_frame = hram->hJoypadDown;  // last frame
    uint8_t last_changed = last_frame ^ input;

    //  Released this frame:
    hram->hJoypadReleased = last_changed & last_frame;
    //  Pressed this frame:
    hram->hJoypadPressed =  last_changed & input;

    //  Add any new presses to the list of collective presses:
    hram->hJoypadSum |= (last_changed & input);

    //  Currently pressed:
    hram->hJoypadDown = input;

    //  Now that we have the input, we can do stuff with it.

    //  For example, soft reset:
    // AND_A(A_BUTTON | B_BUTTON | SELECT | START);
    // CP_A(A_BUTTON | B_BUTTON | SELECT | START);
    // JP_Z (mReset);

    // RET;
}

void GetJoypad(void) {
        //  Update mirror joypad input from hJoypadDown (real input)

    //  hJoyReleased: released this frame (delta)
    //  hJoyPressed: pressed this frame (delta)
    //  hJoyDown: currently pressed

    //  bit 0 A
    //      1 B
    //      2 SELECT
    //      3 START
    //      4 RIGHT
    //      5 LEFT
    //      6 UP
    //      7 DOWN

    PUSH_AF;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    //  The player input can be automated using an input stream.
    //  See more below.
    LD_A_addr(wInputType);
    CP_A(AUTO_INPUT);
    IF_Z goto l_auto;

    //  To get deltas, take this and last frame's input.
    LDH_A_addr(hJoypadDown);  // real input
    LD_B_A;
    LDH_A_addr(hJoyDown);  // last frame mirror
    LD_E_A;

    //  Released this frame:
    XOR_A_B;
    LD_D_A;
    AND_A_E;
    LDH_addr_A(hJoyReleased);

    //  Pressed this frame:
    LD_A_D;
    AND_A_B;
    LDH_addr_A(hJoyPressed);

    //  It looks like the collective presses got commented out here.
    LD_C_A;

    //  Currently pressed:
    LD_A_B;
    LDH_addr_A(hJoyDown);  // frame input

quit:
        POP_BC;
    POP_DE;
    POP_HL;
    POP_AF;
    RET;

l_auto:
        //  Use a predetermined input stream (used in the catching tutorial).

    //  Stream format: [input][duration]
    //  A value of $ff will immediately end the stream.

    //  Read from the input stream.
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_addr(wAutoInputBank);
    RST(aBankswitch);

    LD_HL(wAutoInputAddress);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    //  We only update when the input duration has expired.
    LD_A_addr(wAutoInputLength);
    AND_A_A;
    IF_Z goto updateauto;

    //  Until then, don't change anything.
    DEC_A;
    LD_addr_A(wAutoInputLength);
    POP_AF;
    RST(aBankswitch);
    goto quit;

updateauto:
        //  An input of $ff will end the stream.
    LD_A_hli;
    CP_A(-1);
    IF_Z goto stopauto;
    LD_B_A;

    //  A duration of $ff will end the stream indefinitely.
    LD_A_hli;
    LD_addr_A(wAutoInputLength);
    CP_A(-1);
    IF_NZ goto next;

    //  The current input is overwritten.
    DEC_HL;
    DEC_HL;
    LD_B(NO_INPUT);
    goto finishauto;

next:
        //  On to the next input...
    LD_A_L;
    LD_addr_A(wAutoInputAddress);
    LD_A_H;
    LD_addr_A(wAutoInputAddress + 1);
    goto finishauto;

stopauto:
        CALL(aStopAutoInput);
    LD_B(NO_INPUT);

finishauto:
        POP_AF;
    RST(aBankswitch);
    LD_A_B;
    LDH_addr_A(hJoyPressed);  // pressed
    LDH_addr_A(hJoyDown);     // input
    goto quit;

    return StartAutoInput();
}

void GetJoypad_Conv(void) {
        //  Update mirror joypad input from hJoypadDown (real input)

    //  hJoyReleased: released this frame (delta)
    //  hJoyPressed: pressed this frame (delta)
    //  hJoyDown: currently pressed

    //  bit 0 A
    //      1 B
    //      2 SELECT
    //      3 START
    //      4 RIGHT
    //      5 LEFT
    //      6 UP
    //      7 DOWN

    //PUSH_AF;
    //PUSH_HL;
    //PUSH_DE;
    //PUSH_BC;

    //  The player input can be automated using an input stream.
    //  See more below.
    uint8_t inputType = wram->wInputType;
    if(inputType == AUTO_INPUT)
    {
        //  Use a predetermined input stream (used in the catching tutorial).
        //  Stream format: [input][duration]
        //  A value of $ff will immediately end the stream.

        //  Read from the input stream.
        uint8_t oldBank = hram->hROMBank;
        uint8_t autoInputBank = wram->wAutoInputBank;
        Bankswitch(autoInputBank);

        uint16_t hl = gb_read16(wAutoInputAddress);

        //  We only update when the input duration has expired.
        uint8_t len = wram->wAutoInputLength;
        if(len == 0)
        {
            //  An input of $ff will end the stream.
            uint8_t input = gb_read(hl++);
            if(input == 0xFF) 
            {
                StopAutoInput_Conv();
                input = NO_INPUT;
            }
            else 
            {
                //  A duration of $ff will end the stream indefinitely.
                uint8_t duration = gb_read(hl++);
                wram->wAutoInputLength = duration;
                if(duration != 0xFF)
                {
                    //  On to the next input...
                    gb_write16(wAutoInputAddress, hl);
                }
                else 
                {
                    //  The current input is overwritten.
                    hl -= 2;
                    input = NO_INPUT;
                }
            }
            Bankswitch(oldBank);
            hram->hJoyPressed = input;  // pressed
            hram->hJoyDown = input;     // input
        }
        else 
        {
            //  Until then, don't change anything.
            wram->wAutoInputLength = --len;
            Bankswitch(oldBank);
        }
        return;
    }
    else 
    {

        //  To get deltas, take this and last frame's input.
        uint8_t real_input = hram->hJoypadDown;  // real input
        uint8_t last_input = hram->hJoyDown;  // last frame mirror
        //LDH_A_addr(hJoypadDown);  // real input
        //LD_B_A;
        //LDH_A_addr(hJoyDown);  // last frame mirror
        //LD_E_A;

        //  Released this frame:
        hram->hJoyReleased = (real_input ^ last_input) & last_input;
        //XOR_A_B;
        //LD_D_A;
        //AND_A_E;
        //LDH_addr_A(hJoyReleased);

        //  Pressed this frame:
        //LD_A_D;
        //AND_A_B;
        //LDH_addr_A(hJoyPressed);
        hram->hJoyPressed = (real_input ^ last_input) & real_input;

        //  It looks like the collective presses got commented out here.
        //LD_C_A;

        //  Currently pressed:
        hram->hJoyDown = real_input;  // frame input
        //LD_A_B;
        //LDH_addr_A(hJoyDown);  // frame input
    }
    //POP_BC;
    //POP_DE;
    //POP_HL;
    //POP_AF;
    //RET;

    //return StartAutoInput();
}

//  Update mirror joypad input from hJoypadDown (real input)
void GetJoypad_Conv2(void) {
    //  hJoyReleased: released this frame (delta)
    //  hJoyPressed: pressed this frame (delta)
    //  hJoyDown: currently pressed

    //  bit 0 A
    //      1 B
    //      2 SELECT
    //      3 START
    //      4 RIGHT
    //      5 LEFT
    //      6 UP
    //      7 DOWN

    //PUSH_AF;
    //PUSH_HL;
    //PUSH_DE;
    //PUSH_BC;

    //  The player input can be automated using an input stream.
    //  See more below.
    uint8_t inputType = wram->wInputType;
    if(inputType == AUTO_INPUT)
    {
        //  Use a predetermined input stream (used in the catching tutorial).
        //  Stream format: [input][duration]
        //  A value of $ff will immediately end the stream.

        //  Read from the input stream.
        const uint8_t* hl = gAutoInputAddress;

        //  We only update when the input duration has expired.
        uint8_t len = wram->wAutoInputLength;
        if(len == 0)
        {
            //  An input of $ff will end the stream.
            uint8_t input = *(hl++);
            if(input == 0xFF) 
            {
                StopAutoInput_Conv2();
                input = NO_INPUT;
            }
            else 
            {
                //  A duration of $ff will end the stream indefinitely.
                uint8_t duration = *(hl++);
                wram->wAutoInputLength = duration;
                if(duration != 0xFF)
                {
                    //  On to the next input...
                    gAutoInputAddress = hl;
                }
                else 
                {
                    //  The current input is overwritten.
                    hl -= 2;
                    input = NO_INPUT;
                }
            }
            hram->hJoyPressed = input;  // pressed
            hram->hJoyDown = input;     // input
        }
        else 
        {
            //  Until then, don't change anything.
            wram->wAutoInputLength = --len;
        }
        return;
    }
    else 
    {

        //  To get deltas, take this and last frame's input.
        uint8_t real_input = hram->hJoypadDown;  // real input
        uint8_t last_input = hram->hJoyDown;  // last frame mirror
        //LDH_A_addr(hJoypadDown);  // real input
        //LD_B_A;
        //LDH_A_addr(hJoyDown);  // last frame mirror
        //LD_E_A;

        //  Released this frame:
        hram->hJoyReleased = (real_input ^ last_input) & last_input;
        //XOR_A_B;
        //LD_D_A;
        //AND_A_E;
        //LDH_addr_A(hJoyReleased);

        //  Pressed this frame:
        //LD_A_D;
        //AND_A_B;
        //LDH_addr_A(hJoyPressed);
        hram->hJoyPressed = (real_input ^ last_input) & real_input;

        //  It looks like the collective presses got commented out here.
        //LD_C_A;

        //  Currently pressed:
        hram->hJoyDown = real_input;  // frame input
        //LD_A_B;
        //LDH_addr_A(hJoyDown);  // frame input
    }
    //POP_BC;
    //POP_DE;
    //POP_HL;
    //POP_AF;
    //RET;

    //return StartAutoInput();
}

void StartAutoInput(void) {
        //  Start reading automated input stream at a:hl.

    LD_addr_A(wAutoInputBank);
    LD_A_L;
    LD_addr_A(wAutoInputAddress);
    LD_A_H;
    LD_addr_A(wAutoInputAddress + 1);
    //  Start reading the stream immediately.
    XOR_A_A;
    LD_addr_A(wAutoInputLength);
    //  Reset input mirrors.
    XOR_A_A;
    LDH_addr_A(hJoyPressed);   // pressed this frame
    LDH_addr_A(hJoyReleased);  // released this frame
    LDH_addr_A(hJoyDown);      // currently pressed

    LD_A(AUTO_INPUT);
    LD_addr_A(wInputType);
    RET;
}

void StartAutoInput_Conv(uint16_t hl, uint8_t a) {
    //  Start reading automated input stream at a:hl.
    gb_write(wAutoInputBank, a);
    gb_write16(wAutoInputAddress, hl);
    //  Start reading the stream immediately.
    gb_write(wAutoInputLength, 0);
    //  Reset input mirrors.
    hram->hJoyPressed = 0;   // pressed this frame
    hram->hJoyReleased = 0;  // released this frame
    hram->hJoyDown = 0;      // currently pressed

    gb_write(wInputType, AUTO_INPUT);
}

//  Start reading automated input stream at hl.
void StartAutoInput_Conv2(const uint8_t* hl) {
    gAutoInputAddress = hl;
    //  Start reading the stream immediately.
    wram->wAutoInputLength = 0;
    //  Reset input mirrors.
    hram->hJoyPressed = 0;   // pressed this frame
    hram->hJoyReleased = 0;  // released this frame
    hram->hJoyDown = 0;      // currently pressed

    wram->wInputType = AUTO_INPUT;
}

void StopAutoInput(void) {
        //  Clear variables related to automated input.
    XOR_A_A;
    LD_addr_A(wAutoInputBank);
    LD_addr_A(wAutoInputAddress);
    LD_addr_A(wAutoInputAddress + 1);
    LD_addr_A(wAutoInputLength);
    //  Back to normal input.
    LD_addr_A(wInputType);
    RET;
}

void StopAutoInput_Conv(void) {
    //  Clear variables related to automated input.
    gb_write(wAutoInputBank, 0);
    gb_write(wAutoInputAddress, 0);
    gb_write(wAutoInputAddress + 1, 0);
    gb_write(wAutoInputLength, 0);
    //  Back to normal input.
    gb_write(wInputType, 0);
}

void StopAutoInput_Conv2(void) {
    //  Clear variables related to automated input.
    gAutoInputAddress = NULL;
    wram->wAutoInputLength = 0;
    //  Back to normal input.
    wram->wInputType = 0;
}

void JoyTitleScreenInput(void) {
        //  //  unreferenced

loop:
        CALL(aDelayFrame);

    PUSH_BC;
    CALL(aJoyTextDelay);
    POP_BC;

    //  Save data can be deleted by pressing Up + B + Select.
    LDH_A_addr(hJoyDown);
    CP_A(D_UP | SELECT | B_BUTTON);
    IF_Z goto keycombo;

    //  Press Start or A to start the game.
    LDH_A_addr(hJoyLast);
    AND_A(START | A_BUTTON);
    IF_NZ goto keycombo;

    DEC_C;
    IF_NZ goto loop;

    AND_A_A;
    RET;

keycombo:
        SCF;
    RET;
}

void JoyWaitAorB(void) {
    
loop:
        CALL(aDelayFrame);
    CALL(aGetJoypad);
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON | B_BUTTON);
    RET_NZ;
    CALL(aUpdateTimeAndPals);
    goto loop;

    return WaitButton();
}

void JoyWaitAorB_Conv(void) {
    do {
        // CALL(aDelayFrame);
        DelayFrame();

        // CALL(aGetJoypad);
        GetJoypad_Conv2();

        // LDH_A_addr(hJoyPressed);
        // AND_A(A_BUTTON | B_BUTTON);
        // RET_NZ;
        if((hram->hJoyPressed & (A_BUTTON | B_BUTTON)) != 0)
            break;
        
        // CALL(aUpdateTimeAndPals);
        UpdateTimeAndPals();

        // goto loop;
    } while(1);
}

void WaitButton(void) {
        LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(1);
    LDH_addr_A(hOAMUpdate);
    CALL(aWaitBGMap);
    CALL(aJoyWaitAorB);
    POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;
}

void WaitButton_Conv(void) {
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t tempOAMUpdate = hram->hOAMUpdate;

    // LD_A(1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 1;

    // CALL(aWaitBGMap);
    WaitBGMap();

    // CALL(aJoyWaitAorB);
    JoyWaitAorB_Conv();

    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = tempOAMUpdate;
    
    // RET;
}

void JoyTextDelay(void) {
        CALL(aGetJoypad);
    LDH_A_addr(hInMenu);
    AND_A_A;
    LDH_A_addr(hJoyPressed);
    IF_Z goto ok;
    LDH_A_addr(hJoyDown);

ok:
        LDH_addr_A(hJoyLast);
    LDH_A_addr(hJoyPressed);
    AND_A_A;
    IF_Z goto checkframedelay;
    LD_A(15);
    LD_addr_A(wTextDelayFrames);
    RET;

checkframedelay:
        LD_A_addr(wTextDelayFrames);
    AND_A_A;
    IF_Z goto restartframedelay;
    XOR_A_A;
    LDH_addr_A(hJoyLast);
    RET;

restartframedelay:
        LD_A(5);
    LD_addr_A(wTextDelayFrames);
    RET;
}

void JoyTextDelay_Conv(void) {
    // CALL(aGetJoypad);
    GetJoypad_Conv2();

    // LDH_A_addr(hInMenu);
    // AND_A_A;
    // LDH_A_addr(hJoyPressed);
    // IF_Z goto ok;
    if(hram->hInMenu != 0)
    {
        // LDH_A_addr(hJoyDown);
        // LDH_addr_A(hJoyLast);
        hram->hJoyLast = hram->hJoyDown;
    }
    else 
    {
        // LDH_addr_A(hJoyLast);
        hram->hJoyLast = hram->hJoyPressed;
    }

    // LDH_A_addr(hJoyPressed);
    // AND_A_A;
    // IF_Z goto checkframedelay;
    if(hram->hJoyPressed == 0)
    {
// checkframedelay:
        // LD_A_addr(wTextDelayFrames);
        // AND_A_A;
        // IF_Z goto restartframedelay;
        if(wram->wTextDelayFrames == 0)
        {
    // restartframedelay:
            // LD_A(5);
            // LD_addr_A(wTextDelayFrames);
            wram->wTextDelayFrames = 5;

            // RET;
            return;
        }

        // XOR_A_A;
        // LDH_addr_A(hJoyLast);
        hram->hJoyLast = 0;

        // RET;
        return;
    }
    
    // LD_A(15);
    // LD_addr_A(wTextDelayFrames);
    wram->wTextDelayFrames = 15;

    // RET;
    return;
}

void WaitPressAorB_BlinkCursor(void) {
        //  Show a blinking cursor in the lower right-hand
    //  corner of a textbox and wait until A or B is
    //  pressed.
    //
    //  NOTE: The cursor has to be shown before calling
    //  this function or no cursor will be shown at all.
    LDH_A_addr(hMapObjectIndex);
    PUSH_AF;
    LDH_A_addr(hObjectStructIndex);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hMapObjectIndex);
    LD_A(6);
    LDH_addr_A(hObjectStructIndex);

loop:
    CALL(aDelayFrame);
        PUSH_HL;
    hlcoord(18, 17, wTilemap);
    CALL(aBlinkCursor);
    POP_HL;

    CALL(aJoyTextDelay);
    LDH_A_addr(hJoyLast);
    AND_A(A_BUTTON | B_BUTTON);
    IF_Z goto loop;

    POP_AF;
    LDH_addr_A(hObjectStructIndex);
    POP_AF;
    LDH_addr_A(hMapObjectIndex);
    RET;
}

//  Show a blinking cursor in the lower right-hand
//  corner of a textbox and wait until A or B is
//  pressed.
//
//  NOTE: The cursor has to be shown before calling
//  this function or no cursor will be shown at all.
void WaitPressAorB_BlinkCursor_Conv(void) {
    // LDH_A_addr(hMapObjectIndex);
    // PUSH_AF;
    uint8_t mapObjIdx = hram->hMapObjectIndex;

    // LDH_A_addr(hObjectStructIndex);
    // PUSH_AF;
    uint8_t objStructIdx = hram->hObjectStructIndex;

    // XOR_A_A;
    // LDH_addr_A(hMapObjectIndex);
    hram->hMapObjectIndex = 0;

    // LD_A(6);
    // LDH_addr_A(hObjectStructIndex);
    hram->hObjectStructIndex = 6;

    do {
        DelayFrame();
        // PUSH_HL;
        // hlcoord(18, 17, wTilemap);
        // CALL(aBlinkCursor);
        // POP_HL;
        BlinkCursor_Conv2(coord(18, 17, wram->wTilemap));

        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();

        // LDH_A_addr(hJoyLast);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_Z goto loop;
    } while((hram->hJoyLast & (A_BUTTON | B_BUTTON)) == 0);

    // POP_AF;
    // LDH_addr_A(hObjectStructIndex);
    hram->hObjectStructIndex = objStructIdx;

    // POP_AF;
    // LDH_addr_A(hMapObjectIndex);
    hram->hMapObjectIndex = mapObjIdx;

    // RET;
    return;
}

void SimpleWaitPressAorB(void) {
    
loop:
        CALL(aJoyTextDelay);
    LDH_A_addr(hJoyLast);
    AND_A(A_BUTTON | B_BUTTON);
    IF_Z goto loop;
    RET;
}

void SimpleWaitPressAorB_Conv(void) {
    
    do {
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        DelayFrame();
        // LDH_A_addr(hJoyLast);
        // AND_A(A_BUTTON | B_BUTTON);
    } while((hram->hJoyLast & (A_BUTTON | B_BUTTON)) == 0);
    // IF_Z goto loop;
    // RET;
}

void PromptButton(void) {
        //  Show a blinking cursor in the lower right-hand
    //  corner of a textbox and wait until A or B is
    //  pressed, afterwards, play a sound.
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto link;
    CALL(aPromptButton_wait_input);
    PUSH_DE;
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    POP_DE;
    RET;

link:
        LD_C(65);
    JP(mDelayFrames);

wait_input:
        LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);
    LD_A_addr(wInputType);
    OR_A_A;
    IF_Z goto input_wait_loop;
    FARCALL(av_DudeAutoInput_A);

input_wait_loop:
        CALL(aPromptButton_blink_cursor);
    CALL(aJoyTextDelay);
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON | B_BUTTON);
    IF_NZ goto received_input;
    CALL(aUpdateTimeAndPals);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    goto input_wait_loop;

received_input:
        POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;

blink_cursor:
        LDH_A_addr(hVBlankCounter);
    AND_A(0b00010000);  // bit 4, a
    IF_Z goto cursor_off;
    LD_A(0xee);
    goto load_cursor_state;

cursor_off:
        lda_coord(17, 17, wTilemap);

load_cursor_state:
        ldcoord_a(18, 17, wTilemap);
    RET;
}

void PromptButton_wait_input_Conv(void) {
    // PEEK("");
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t temp = hram->hOAMUpdate;

    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 1;

    // LD_A_addr(wInputType);
    // OR_A_A;
    // IF_Z goto input_wait_loop;
    if(wram->wInputType != 0)
    {
        // FARCALL(av_DudeAutoInput_A);
        v_DudeAutoInput_A();
    }
    // input_wait_loop:
    do {
        // CALL(aPromptButton_blink_cursor);

        do {
        // blink_cursor:
            // LDH_A_addr(hVBlankCounter);
            // AND_A(0b00010000);  // bit 4, a
            // IF_Z goto cursor_off;
            if((hram->hVBlankCounter & 0b00010000) == 0)
            {
            // cursor_off:
                // lda_coord(17, 17, wTilemap);
                // ldcoord_a(18, 17, wTilemap);
                *coord(18, 17, wram->wTilemap) = *coord(17, 17, wram->wTilemap);
            }
            else 
            {
                // LD_A(0xee);
                // ldcoord_a(18, 17, wTilemap);
                *coord(18, 17, wram->wTilemap) = CHAR_DOWN_CURSOR;
            }

            // RET;
        } while(0);

        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();

        // LDH_A_addr(hJoyPressed);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto received_input;
        if((hram->hJoyPressed & (A_BUTTON | B_BUTTON)) != 0)
        {
            // PEEK("received_input");
        // received_input:
            // POP_AF;
            // LDH_addr_A(hOAMUpdate);
            hram->hOAMUpdate = temp;

            // RET;
            return;
        }

        // CALL(aUpdateTimeAndPals);
        UpdateTimeAndPals();

        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;

        // CALL(aDelayFrame);
        DelayFrame();

        // goto input_wait_loop;
    } while(1);
}

//  Show a blinking cursor in the lower right-hand
//  corner of a textbox and wait until A or B is
//  pressed, afterwards, play a sound.
void PromptButton_Conv(void) {
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto link;
    if(wram->wLinkMode != LINK_NULL)
    {
        // LD_C(65);
        // JP(mDelayFrames);
        return DelayFrames(65);
    }
    
    // CALL(aPromptButton_wait_input);
    PromptButton_wait_input_Conv();

    // PEEK("after");
    // PUSH_DE;
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    // POP_DE;
    PlaySFX(SFX_READ_TEXT_2);
    // RET;
}

void BlinkCursor(void) {
        PUSH_BC;
    LD_A_hl;
    LD_B_A;
    LD_A(0xee);
    CP_A_B;
    POP_BC;
    IF_NZ goto place_arrow;
    LDH_A_addr(hMapObjectIndex);
    DEC_A;
    LDH_addr_A(hMapObjectIndex);
    RET_NZ;
    LDH_A_addr(hObjectStructIndex);
    DEC_A;
    LDH_addr_A(hObjectStructIndex);
    RET_NZ;
    LD_A(0x7a);
    LD_hl_A;
    LD_A(-1);
    LDH_addr_A(hMapObjectIndex);
    LD_A(6);
    LDH_addr_A(hObjectStructIndex);
    RET;

place_arrow:
        LDH_A_addr(hMapObjectIndex);
    AND_A_A;
    RET_Z;
    DEC_A;
    LDH_addr_A(hMapObjectIndex);
    RET_NZ;
    DEC_A;
    LDH_addr_A(hMapObjectIndex);
    LDH_A_addr(hObjectStructIndex);
    DEC_A;
    LDH_addr_A(hObjectStructIndex);
    RET_NZ;
    LD_A(6);
    LDH_addr_A(hObjectStructIndex);
    LD_A(0xee);
    LD_hl_A;
    RET;
}

void BlinkCursor_Conv(uint16_t hl) {
    uint8_t idx;

    // PUSH_BC;
    // LD_A_hl;
    // LD_B_A;
    // LD_A(0xee);
    // CP_A_B;
    // POP_BC;
    // IF_NZ goto place_arrow;
    if(gb_read(hl) != CHAR_DOWN_CURSOR)
    {
// place_arrow:
        // LDH_A_addr(hMapObjectIndex);
        // AND_A_A;
        // RET_Z;
        idx = hram->hMapObjectIndex;
        if(idx == 0)
            return;
        
        // DEC_A;
        // LDH_addr_A(hMapObjectIndex);
        hram->hMapObjectIndex = --idx;

        // RET_NZ;
        if(idx != 0)
            return;
        
        // DEC_A;
        // LDH_addr_A(hMapObjectIndex);
        hram->hMapObjectIndex = --idx;

        // LDH_A_addr(hObjectStructIndex);
        // DEC_A;
        // LDH_addr_A(hObjectStructIndex);
        idx = hram->hObjectStructIndex;
        hram->hObjectStructIndex = --idx;

        // RET_NZ;
        if(idx != 0)
            return;
        
        // LD_A(6);
        // LDH_addr_A(hObjectStructIndex);
        hram->hObjectStructIndex = 6;

        // LD_A(0xee);
        // LD_hl_A;
        gb_write(hl, CHAR_DOWN_CURSOR);

        // RET;
        return;
    }

    // LDH_A_addr(hMapObjectIndex);
    // DEC_A;
    // LDH_addr_A(hMapObjectIndex);
    idx = hram->hMapObjectIndex;
    hram->hMapObjectIndex = --idx;

    // RET_NZ;
    if(idx != 0)
        return;
    
    // LDH_A_addr(hObjectStructIndex);
    // DEC_A;
    // LDH_addr_A(hObjectStructIndex);
    idx = hram->hObjectStructIndex;
    hram->hObjectStructIndex = --idx;

    // RET_NZ;
    if(idx != 0)
        return;

    // LD_A(0x7a);
    // LD_hl_A;
    gb_write(hl, CHAR_FRAME_TOP);

    // LD_A(-1);
    // LDH_addr_A(hMapObjectIndex);
    hram->hMapObjectIndex = 0xff;

    // LD_A(6);
    // LDH_addr_A(hObjectStructIndex);
    hram->hObjectStructIndex = 6;
    
    // RET;
    return;
}

void BlinkCursor_Conv2(uint8_t* hl) {
    uint8_t idx;

    // PUSH_BC;
    // LD_A_hl;
    // LD_B_A;
    // LD_A(0xee);
    // CP_A_B;
    // POP_BC;
    // IF_NZ goto place_arrow;
    if(*hl != CHAR_DOWN_CURSOR)
    {
// place_arrow:
        // LDH_A_addr(hMapObjectIndex);
        // AND_A_A;
        // RET_Z;
        idx = hram->hMapObjectIndex;
        if(idx == 0)
            return;
        
        // DEC_A;
        // LDH_addr_A(hMapObjectIndex);
        hram->hMapObjectIndex = --idx;

        // RET_NZ;
        if(idx != 0)
            return;
        
        // DEC_A;
        // LDH_addr_A(hMapObjectIndex);
        hram->hMapObjectIndex = --idx;

        // LDH_A_addr(hObjectStructIndex);
        // DEC_A;
        // LDH_addr_A(hObjectStructIndex);
        idx = hram->hObjectStructIndex;
        hram->hObjectStructIndex = --idx;

        // RET_NZ;
        if(idx != 0)
            return;
        
        // LD_A(6);
        // LDH_addr_A(hObjectStructIndex);
        hram->hObjectStructIndex = 6;

        // LD_A(0xee);
        // LD_hl_A;
        *hl = CHAR_DOWN_CURSOR;

        // RET;
        return;
    }

    // LDH_A_addr(hMapObjectIndex);
    // DEC_A;
    // LDH_addr_A(hMapObjectIndex);
    idx = hram->hMapObjectIndex;
    hram->hMapObjectIndex = --idx;

    // RET_NZ;
    if(idx != 0)
        return;
    
    // LDH_A_addr(hObjectStructIndex);
    // DEC_A;
    // LDH_addr_A(hObjectStructIndex);
    idx = hram->hObjectStructIndex;
    hram->hObjectStructIndex = --idx;

    // RET_NZ;
    if(idx != 0)
        return;

    // LD_A(0x7a);
    // LD_hl_A;
    *hl = CHAR_FRAME_TOP;

    // LD_A(-1);
    // LDH_addr_A(hMapObjectIndex);
    hram->hMapObjectIndex = 0xff;

    // LD_A(6);
    // LDH_addr_A(hObjectStructIndex);
    hram->hObjectStructIndex = 6;
    
    // RET;
    return;
}
