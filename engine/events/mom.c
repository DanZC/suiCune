#include "../../constants.h"
#include "mom.h"
#include "money.h"
#include "../../home/text.h"
#include "../../home/copy.h"
#include "../../home/menu.h"
#include "../../home/print_text.h"
#include "../../home/tilemap.h"
#include "../../home/map_objects.h"
#include "../../home/delay.h"
#include "../../home/joypad.h"
#include "../../home/audio.h"
#include "../../data/text/common.h"

enum {
    BANKOFMOM_CHECK_IF_BANK_INIT,
    BANKOFMOM_INIT_BANK,
    BANKOFMOM_IS_THIS_ABOUT_YOUR_MONEY,
    BANKOFMOM_ACCESS_BANK_OF_MOM,
    BANKOFMOM_STORE_MONEY,
    BANKOFMOM_TAKE_MONEY,
    BANKOFMOM_STOP_OR_START_SAVING_MONEY,
    BANKOFMOM_JUST_DO_WHAT_YOU_CAN,
    BANKOFMOM_EXIT,
};

static const struct MenuHeader BankOfMom_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 10, 10),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 4,  // items
            .options = (const char*[]) {
                "GET@",
                "SAVE@",
                "CHANGE@",
                "CANCEL@",
            }
        },
    },
    .defaultOption = 1,  // default option
};

void BankOfMom(void){
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;

    while(!bit_test(wram->wJumptableIndex, 7)) {
    // loop:
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        // CALL(aBankOfMom_RunJumptable);
        switch(wram->wJumptableIndex) {
        // RunJumptable:
            //jumptable ['.dw', 'wJumptableIndex']

        // dw:
            //dw ['.CheckIfBankInitialized'];
            case BANKOFMOM_CHECK_IF_BANK_INIT:
            // CheckIfBankInitialized:
                // LD_A_addr(wMomSavingMoney);
                // BIT_A(MOM_ACTIVE_F);
                // IF_NZ goto savingmoneyalready;
                if(bit_test(wram->wMomSavingMoney, MOM_ACTIVE_F)) {
                    wram->wJumptableIndex = BANKOFMOM_IS_THIS_ABOUT_YOUR_MONEY;
                }
                else {
                    // SET_A(MOM_ACTIVE_F);
                    // LD_addr_A(wMomSavingMoney);
                    bit_set(wram->wMomSavingMoney, MOM_ACTIVE_F);
                    // LD_A(0x1);
                    // goto done_0;
                    wram->wJumptableIndex = BANKOFMOM_INIT_BANK;
                }

            // savingmoneyalready:
                // LD_A(0x2);

            // done_0:
                // LD_addr_A(wJumptableIndex);
                // RET;
                break;
            //dw ['.InitializeBank'];
            case BANKOFMOM_INIT_BANK:
            // InitializeBank:
                // LD_HL(mMomLeavingText1);
                // CALL(aPrintText);
                PrintText_Conv2(MomLeavingText1);
                // CALL(aYesNoBox);
                // IF_C goto DontSaveMoney;
                if(YesNoBox()) {
                    // LD_HL(mMomLeavingText2);
                    // CALL(aPrintText);
                    PrintText_Conv2(MomLeavingText2);
                    // LD_A((1 << MOM_ACTIVE_F) | (1 << MOM_SAVING_SOME_MONEY_F));
                    // goto done_1;
                    wram->wMomSavingMoney = (1 << MOM_ACTIVE_F) | (1 << MOM_SAVING_SOME_MONEY_F);
                }
                else {
                // DontSaveMoney:
                    // LD_A(1 << MOM_ACTIVE_F);
                    wram->wMomSavingMoney = 1 << MOM_ACTIVE_F;
                }


            // done_1:
                // LD_addr_A(wMomSavingMoney);
                // LD_HL(mMomLeavingText3);
                // CALL(aPrintText);
                PrintText_Conv2(MomLeavingText3);
                // LD_A(0x8);
                // LD_addr_A(wJumptableIndex);
                wram->wJumptableIndex = BANKOFMOM_EXIT;
                // RET;
                break;
            //dw ['.IsThisAboutYourMoney'];
            case BANKOFMOM_IS_THIS_ABOUT_YOUR_MONEY:
            // IsThisAboutYourMoney:
                // LD_HL(mMomIsThisAboutYourMoneyText);
                // CALL(aPrintText);
                PrintText_Conv2(MomIsThisAboutYourMoneyText);
                // CALL(aYesNoBox);
                // IF_C goto nope;
                if(YesNoBox()) {
                    // LD_A(0x3);
                    // goto done_2;
                    wram->wJumptableIndex = BANKOFMOM_ACCESS_BANK_OF_MOM;
                }
                else {
                // nope:
                    // CALL(aDSTChecks);
                    DSTChecks();
                    // LD_A(0x7);
                    wram->wJumptableIndex = BANKOFMOM_JUST_DO_WHAT_YOU_CAN;
                }

            // done_2:
                // LD_addr_A(wJumptableIndex);
                // RET;
                break;
            //dw ['.AccessBankOfMom'];
            case BANKOFMOM_ACCESS_BANK_OF_MOM:
            // AccessBankOfMom:
                // LD_HL(mMomBankWhatDoYouWantToDoText);
                // CALL(aPrintText);
                PrintText_Conv2(MomBankWhatDoYouWantToDoText);
                // CALL(aLoadStandardMenuHeader);
                LoadStandardMenuHeader();
                // LD_HL(mBankOfMom_MenuHeader);
                // CALL(aCopyMenuHeader);
                CopyMenuHeader(&BankOfMom_MenuHeader);
                // CALL(aVerticalMenu);
                bool nocancel = VerticalMenu();
                // CALL(aCloseWindow);
                CloseWindow();
                // IF_C goto cancel;
                if(!nocancel)
                    goto cancel;
                // LD_A_addr(wMenuCursorY);
                // CP_A(0x1);
                // IF_Z goto withdraw;
                // CP_A(0x2);
                // IF_Z goto deposit;
                // CP_A(0x3);
                // IF_Z goto stopsaving;
                switch(wram->wMenuCursorY) {
                default:
                cancel:
                    // LD_A(0x7);
                    // goto done_3;
                    wram->wJumptableIndex = BANKOFMOM_JUST_DO_WHAT_YOU_CAN;
                    break;

                case 0x1: // withdraw
                // withdraw:
                    // LD_A(0x5);
                    // goto done_3;
                    wram->wJumptableIndex = BANKOFMOM_TAKE_MONEY;
                    break;

                case 0x2: // deposit
                // deposit:
                    // LD_A(0x4);
                    // goto done_3;
                    wram->wJumptableIndex = BANKOFMOM_STORE_MONEY;
                    break;

                case 0x3: // stopsaving
                // stopsaving:
                    // LD_A(0x6);
                    wram->wJumptableIndex = BANKOFMOM_STOP_OR_START_SAVING_MONEY;
                    break;
                }

            // done_3:
                // LD_addr_A(wJumptableIndex);
                // RET;
                break;
            //dw ['.StoreMoney'];
            case BANKOFMOM_STORE_MONEY: {
            // StoreMoney:
                // LD_HL(mMomStoreMoneyText);
                // CALL(aPrintText);
                PrintText_Conv2(MomStoreMoneyText);
                // XOR_A_A;
                // LD_HL(wStringBuffer2);
                // LD_hli_A;
                wram->wStringBuffer2[0] = 0;
                // LD_hli_A;
                wram->wStringBuffer2[1] = 0;
                // LD_hl_A;
                wram->wStringBuffer2[2] = 0;
                // LD_A(5);
                // LD_addr_A(wMomBankDigitCursorPosition);
                wram->wMomBankDigitCursorPosition = 5;
                // CALL(aLoadStandardMenuHeader);
                LoadStandardMenuHeader();
                // CALL(aMom_SetUpDepositMenu);
                Mom_SetUpDepositMenu();
                // CALL(aMom_Wait10Frames);
                Mom_Wait10Frames();
                // CALL(aMom_WithdrawDepositMenuJoypad);
                bool cancel = Mom_WithdrawDepositMenuJoypad();
                // CALL(aCloseWindow);
                CloseWindow();
                // IF_C goto CancelDeposit;
                // LD_HL(wStringBuffer2);
                // LD_A_hli;
                // OR_A_hl;
                // INC_HL;
                // OR_A_hl;
                // IF_Z goto CancelDeposit;
                if(!cancel && (wram->wStringBuffer2[0] | wram->wStringBuffer2[1] | wram->wStringBuffer2[2]) != 0) {
                    // LD_DE(wMoney);
                    // LD_BC(wStringBuffer2);
                    // FARCALL(aCompareMoney);
                    u8_flag_s res = CompareMoney_Conv(wram->wStringBuffer2, wram->wMoney);
                    // IF_C goto InsufficientFundsInWallet;
                    if(res.flag) {
                    // InsufficientFundsInWallet:
                        // LD_HL(mMomInsufficientFundsInWalletText);
                        // CALL(aPrintText);
                        PrintText_Conv2(MomInsufficientFundsInWalletText);
                        // RET;
                        break;
                    }
                    // LD_HL(wStringBuffer2);
                    // LD_DE(wStringBuffer2 + 3);
                    // LD_BC(3);
                    // CALL(aCopyBytes);
                    CopyBytes(wram->wStringBuffer2 + 3, wram->wStringBuffer2, 3);
                    // LD_BC(wMomsMoney);
                    // LD_DE(wStringBuffer2);
                    // FARCALL(aGiveMoney);
                    bool noroom = GiveMoney_Conv(wram->wStringBuffer2, wram->wMomsMoney);
                    // IF_C goto NotEnoughRoomInBank;
                    if(noroom) {
                    // NotEnoughRoomInBank:
                        // LD_HL(mMomNotEnoughRoomInBankText);
                        // CALL(aPrintText);
                        PrintText_Conv2(MomNotEnoughRoomInBankText);
                        // RET;
                        break;
                    }
                    // LD_BC(wStringBuffer2 + 3);
                    // LD_DE(wMoney);
                    // FARCALL(aTakeMoney);
                    TakeMoney_Conv(wram->wMoney, wram->wStringBuffer2 + 3);
                    // LD_HL(wStringBuffer2);
                    // LD_DE(wMomsMoney);
                    // LD_BC(3);
                    // CALL(aCopyBytes);
                    CopyBytes(wram->wMomsMoney, wram->wStringBuffer2, 3);
                    // LD_DE(SFX_TRANSACTION);
                    // CALL(aPlaySFX);
                    PlaySFX(SFX_TRANSACTION);
                    // CALL(aWaitSFX);
                    WaitSFX();
                    // LD_HL(mMomStoredMoneyText);
                    // CALL(aPrintText);
                    PrintText_Conv2(MomStoredMoneyText);
                    // LD_A(0x8);
                    // goto done_4;
                    wram->wJumptableIndex = BANKOFMOM_EXIT;
                }
                else {
                // CancelDeposit:
                    // LD_A(0x7);
                    wram->wJumptableIndex = BANKOFMOM_JUST_DO_WHAT_YOU_CAN;
                }
            // done_4:
                // LD_addr_A(wJumptableIndex);
                // RET;
            } break;
            //dw ['.TakeMoney'];
            case BANKOFMOM_TAKE_MONEY: {
            // TakeMoney:
                // LD_HL(mMomTakeMoneyText);
                // CALL(aPrintText);
                PrintText_Conv2(MomTakeMoneyText);
                // XOR_A_A;
                // LD_HL(wStringBuffer2);
                // LD_hli_A;
                wram->wStringBuffer2[0] = 0;
                // LD_hli_A;
                wram->wStringBuffer2[1] = 0;
                // LD_hl_A;
                wram->wStringBuffer2[2] = 0;
                // LD_A(5);
                // LD_addr_A(wMomBankDigitCursorPosition);
                wram->wMomBankDigitCursorPosition = 5;
                // CALL(aLoadStandardMenuHeader);
                LoadStandardMenuHeader();
                // CALL(aMom_SetUpWithdrawMenu);
                Mom_SetUpWithdrawMenu();
                // CALL(aMom_Wait10Frames);
                Mom_Wait10Frames();
                // CALL(aMom_WithdrawDepositMenuJoypad);
                bool cancel = Mom_WithdrawDepositMenuJoypad();
                // CALL(aCloseWindow);
                CloseWindow();
                // IF_C goto CancelWithdraw;
                // LD_HL(wStringBuffer2);
                // LD_A_hli;
                // OR_A_hl;
                // INC_HL;
                // OR_A_hl;
                // IF_Z goto CancelWithdraw;
                if(!cancel && (wram->wStringBuffer2[0] | wram->wStringBuffer2[1] | wram->wStringBuffer2[2]) != 0) {
                    // LD_HL(wStringBuffer2);
                    // LD_DE(wStringBuffer2 + 3);
                    // LD_BC(3);
                    // CALL(aCopyBytes);
                    CopyBytes(wram->wStringBuffer2 + 3, wram->wStringBuffer2, 3);
                    // LD_DE(wMomsMoney);
                    // LD_BC(wStringBuffer2);
                    // FARCALL(aCompareMoney);
                    u8_flag_s res = CompareMoney_Conv(wram->wStringBuffer2, wram->wMomsMoney);
                    // IF_C goto InsufficientFundsInBank;
                    if(res.flag) {
                    // InsufficientFundsInBank:
                        // LD_HL(mMomHaventSavedThatMuchText);
                        // CALL(aPrintText);
                        PrintText_Conv2(MomHaventSavedThatMuchText);
                        // RET;
                        break;
                    }
                    // LD_BC(wMoney);
                    // LD_DE(wStringBuffer2);
                    // FARCALL(aGiveMoney);
                    bool noroom = GiveMoney_Conv(wram->wStringBuffer2, wram->wMoney);
                    // IF_C goto NotEnoughRoomInWallet;
                    if(noroom) {
                    // NotEnoughRoomInWallet:
                        // LD_HL(mMomNotEnoughRoomInWalletText);
                        // CALL(aPrintText);
                        PrintText_Conv2(MomNotEnoughRoomInWalletText);
                        // RET;
                        break;
                    }
                    // LD_BC(wStringBuffer2 + 3);
                    // LD_DE(wMomsMoney);
                    // FARCALL(aTakeMoney);
                    TakeMoney_Conv(wram->wMomsMoney, wram->wStringBuffer2 + 3);
                    // LD_HL(wStringBuffer2);
                    // LD_DE(wMoney);
                    // LD_BC(3);
                    // CALL(aCopyBytes);
                    CopyBytes(wram->wMoney, wram->wStringBuffer2, 3);
                    // LD_DE(SFX_TRANSACTION);
                    // CALL(aPlaySFX);
                    PlaySFX(SFX_TRANSACTION);
                    // CALL(aWaitSFX);
                    WaitSFX();
                    // LD_HL(mMomTakenMoneyText);
                    // CALL(aPrintText);
                    PrintText_Conv2(MomTakenMoneyText);
                    // LD_A(0x8);
                    wram->wJumptableIndex = BANKOFMOM_EXIT;
                    // goto done_5;
                }
                else {
                // CancelWithdraw:
                    // LD_A(0x7);
                    wram->wJumptableIndex = BANKOFMOM_JUST_DO_WHAT_YOU_CAN;
                }
            // done_5:
                // LD_addr_A(wJumptableIndex);
                // RET;
            } break;
            //dw ['.StopOrStartSavingMoney'];
            case BANKOFMOM_STOP_OR_START_SAVING_MONEY:
            // StopOrStartSavingMoney:
                // LD_HL(mMomSaveMoneyText);
                // CALL(aPrintText);
                PrintText_Conv2(MomSaveMoneyText);
                // CALL(aYesNoBox);
                // IF_C goto StopSavingMoney;
                if(YesNoBox()) {
                    // LD_A((1 << MOM_ACTIVE_F) | (1 << MOM_SAVING_SOME_MONEY_F));
                    // LD_addr_A(wMomSavingMoney);
                    wram->wMomSavingMoney = (1 << MOM_ACTIVE_F) | (1 << MOM_SAVING_SOME_MONEY_F);
                    // LD_HL(mMomStartSavingMoneyText);
                    // CALL(aPrintText);
                    PrintText_Conv2(MomStartSavingMoneyText);
                    // LD_A(0x8);
                    // LD_addr_A(wJumptableIndex);
                    wram->wJumptableIndex = BANKOFMOM_EXIT;
                    // RET;
                }
                else {
                // StopSavingMoney:
                    // LD_A(1 << MOM_ACTIVE_F);
                    // LD_addr_A(wMomSavingMoney);
                    wram->wMomSavingMoney = (1 << MOM_ACTIVE_F);
                    // LD_A(0x7);
                    // LD_addr_A(wJumptableIndex);
                    wram->wJumptableIndex = BANKOFMOM_JUST_DO_WHAT_YOU_CAN;
                    // RET;
                }
                break;
            //dw ['.JustDoWhatYouCan'];
            case BANKOFMOM_JUST_DO_WHAT_YOU_CAN:
            // JustDoWhatYouCan:
                // LD_HL(mMomJustDoWhatYouCanText);
                // CALL(aPrintText);
                PrintText_Conv2(MomJustDoWhatYouCanText);
                fallthrough;
            //dw ['.AskDST'];
            case BANKOFMOM_EXIT:
            // AskDST:
                // LD_HL(wJumptableIndex);
                // SET_hl(7);
                bit_set(wram->wJumptableIndex, 7);
                // RET;
                break;
        }
        // goto loop;
    }

// done:
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // RET;
    return;
}

static void DSTChecks_ClearBox(void) {
    // hlcoord(1, 14, wTilemap);
    // LD_BC((3 << 8) | 18);
    // CALL(aClearBox);
    ClearBox(coord(1, 14, wram->wTilemap), 18, 3);
    // RET;
}

static void DSTChecks_SetClockForward(void) {
    // LD_A_addr(wStartHour);
    // ADD_A(1);
    uint8_t hour = wram->wStartHour + 1;
    // SUB_A(24);
    uint8_t carry = 0;
    // IF_NC goto DontLoopHourForward;
    // ADD_A(24);
    if(hour >= 24) {
        hour -= 24;
        carry = 1;
    }

// DontLoopHourForward:
    // LD_addr_A(wStartHour);
    wram->wStartHour = hour;
    // CCF;
    // LD_A_addr(wStartDay);
    // ADC_A(0);
    // LD_addr_A(wStartDay);
    wram->wStartDay += carry;
    // RET;
}

static void DSTChecks_SetClockBack(void) {
    uint8_t borrow;
    // LD_A_addr(wStartHour);
    // SUB_A(1);
    // IF_NC goto DontLoopHourBack;
    // ADD_A(24);
    if(wram->wStartHour < 1) {
        wram->wStartHour = (wram->wStartHour - 1) + 24;
        borrow = 1;
    }
    else {
        wram->wStartHour -= 1;
        borrow = 0;
    }

// DontLoopHourBack:
    // LD_addr_A(wStartHour);
    // LD_A_addr(wStartDay);
    // SBC_A(0);
    // IF_NC goto DontLoopDayBack;
    if(wram->wStartDay < borrow) {
        // ADD_A(7);
        wram->wStartDay = 7 - borrow;
    }

// DontLoopDayBack:
    // LD_addr_A(wStartDay);
    // RET;
}

//  check the time
void DSTChecks(void){
    static const txt_cmd_s TimesetAskAdjustDSTText[] = {
        text_far(v_TimesetAskAdjustDSTText)
        text_end
    };

    static const txt_cmd_s MomLostGearBookletText[] = {
        text_far(v_MomLostGearBookletText)
        text_end
    };

    static const txt_cmd_s TimesetAskDSTText[] = {
        text_far(v_TimesetAskDSTText)
        text_end
    };

    static const txt_cmd_s TimesetDSTText[] = {
        text_far(v_TimesetDSTText)
        text_end
    };

    static const txt_cmd_s TimesetAskNotDSTText[] = {
        text_far(v_TimesetAskNotDSTText)
        text_end
    };

    static const txt_cmd_s TimesetNotDSTText[] = {
        text_far(v_TimesetNotDSTText)
        text_end
    };
    // LD_A_addr(wDST);
    // BIT_A(7);
    // LDH_A_addr(hHours);
    // IF_Z goto NotDST;
    // AND_A_A;  // within one hour of 00:00?
    // IF_Z goto LostBooklet;
    // goto loop;


// NotDST:
    // CP_A(23);  // within one hour of 23:00?
    // IF_NZ goto loop;
// fallthrough

    if((!bit_test(wram->wDST, 7) && hram->hHours == 23)    // within one hour of 23:00 outside of DST?
    || ( bit_test(wram->wDST, 7) && hram->hHours == 0))    // within one hour of 00:00 in DST?
    {
    // LostBooklet:
        // CALL(aDSTChecks_ClearBox);
        DSTChecks_ClearBox();
        // bccoord(1, 14, wTilemap);
        // LD_HL(mDSTChecks_TimesetAskAdjustDSTText);
        // CALL(aPlaceHLTextAtBC);
        PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), TimesetAskAdjustDSTText);
        // CALL(aYesNoBox);
        // RET_C ;
        if(!YesNoBox())
            return;
        // CALL(aDSTChecks_ClearBox);
        DSTChecks_ClearBox();
        // bccoord(1, 14, wTilemap);
        // LD_HL(mDSTChecks_MomLostGearBookletText);
        // CALL(aPlaceHLTextAtBC);
        PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), MomLostGearBookletText);
        // RET;
        return;
    }

// loop:
    // CALL(aDSTChecks_ClearBox);
    DSTChecks_ClearBox();
    // bccoord(1, 14, wTilemap);
    // LD_A_addr(wDST);
    // BIT_A(7);
    // IF_Z goto SetDST;
    if(!bit_test(wram->wDST, 7)) {
    // SetDST:
        // LD_HL(mDSTChecks_TimesetAskDSTText);
        // CALL(aPlaceHLTextAtBC);
        PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), TimesetAskDSTText);
        // CALL(aYesNoBox);
        // RET_C ;
        if(!YesNoBox())
            return;
        // LD_A_addr(wDST);
        // SET_A(7);
        // LD_addr_A(wDST);
        bit_set(wram->wDST, 7);
        // CALL(aDSTChecks_SetClockForward);
        DSTChecks_SetClockForward();
        // CALL(aDSTChecks_ClearBox);
        DSTChecks_ClearBox();
        // bccoord(1, 14, wTilemap);
        // LD_HL(mDSTChecks_TimesetDSTText);
        // CALL(aPlaceHLTextAtBC);
        PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), TimesetDSTText);
        // RET;
        return;
    }
    // LD_HL(mDSTChecks_TimesetAskNotDSTText);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), TimesetAskNotDSTText);
    // CALL(aYesNoBox);
    // RET_C ;
    if(!YesNoBox())
        return;
    // LD_A_addr(wDST);
    // RES_A(7);
    // LD_addr_A(wDST);
    bit_reset(wram->wDST, 7);
    // CALL(aDSTChecks_SetClockBack);
    DSTChecks_SetClockBack();
    // CALL(aDSTChecks_ClearBox);
    DSTChecks_ClearBox();
    // bccoord(1, 14, wTilemap);
    // LD_HL(mDSTChecks_TimesetNotDSTText);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), TimesetNotDSTText);
    // RET;
    return;

// ClearBox:
    // hlcoord(1, 14, wTilemap);
    // LD_BC((3 << 8) | 18);
    // CALL(aClearBox);
    // RET;
}

void Mom_SetUpWithdrawMenu(void){
    // LD_DE(mMon_WithdrawString);
    // JR(mMom_ContinueMenuSetup);
    return Mom_ContinueMenuSetup(Mon_WithdrawString);
}

void Mom_SetUpDepositMenu(void){
    // LD_DE(mMom_DepositString);
    return Mom_ContinueMenuSetup(Mom_DepositString);
}

void Mom_ContinueMenuSetup(const char* de){
    // PUSH_DE;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 0, wTilemap);
    // LD_BC((6 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 0, wram->wTilemap), 6, 18);
    // hlcoord(1, 2, wTilemap);
    // LD_DE(mMom_SavedString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Mom_SavedString), coord(1, 2, wram->wTilemap));
    // hlcoord(12, 2, wTilemap);
    // LD_DE(wMomsMoney);
    // LD_BC((PRINTNUM_MONEY | 3 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(12, 2, wram->wTilemap), wram->wMomsMoney, PRINTNUM_MONEY | 3, 6);
    // hlcoord(1, 4, wTilemap);
    // LD_DE(mMom_HeldString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Mom_HeldString), coord(1, 4, wram->wTilemap));
    // hlcoord(12, 4, wTilemap);
    // LD_DE(wMoney);
    // LD_BC((PRINTNUM_MONEY | 3 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(12, 4, wram->wTilemap), wram->wMoney, PRINTNUM_MONEY | 3, 6);
    // hlcoord(1, 6, wTilemap);
    // POP_DE;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(de), coord(1, 6, wram->wTilemap));
    // hlcoord(12, 6, wTilemap);
    // LD_DE(wStringBuffer2);
    // LD_BC((PRINTNUM_MONEY | PRINTNUM_LEADINGZEROS | 3 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(12, 6, wram->wTilemap), wram->wStringBuffer2, PRINTNUM_MONEY | PRINTNUM_LEADINGZEROS | 3, 6);
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aCGBOnly_CopyTilemapAtOnce);
    CGBOnly_CopyTilemapAtOnce();
    // RET;
}

void Mom_Wait10Frames(void){
    // LD_C(10);
    // CALL(aDelayFrames);
    // RET;
    return DelayFrames(10);
}

static void Mom_WithdrawDepositMenuJoypad_getdigitquantity(uint8_t* dest, uint8_t pos) {
    static const uint32_t DigitQuantities[] = {
        100000,
        10000,
        1000,
        100,
        10,
        1,

        100000,
        10000,
        1000,
        100,
        10,
        1,

        900000,
        90000,
        9000,
        900,
        90,
        9,
    };
    // LD_A_addr(wMomBankDigitCursorPosition);
    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // POP_DE;
    uint32_t amount = DigitQuantities[pos];
    dest[0] = amount >> 16;
    dest[1] = amount >> 8;
    dest[2] = amount & 0xff;
    // RET;
}

static void Mom_WithdrawDepositMenuJoypad_dpadaction(void) {
    uint8_t temp[4];
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto incrementdigit;
    if(hram->hJoyLast & D_UP) {
    // incrementdigit:
        // LD_HL(mMom_WithdrawDepositMenuJoypad_DigitQuantities);
        // CALL(aMom_WithdrawDepositMenuJoypad_getdigitquantity);
        Mom_WithdrawDepositMenuJoypad_getdigitquantity(temp, wram->wMomBankDigitCursorPosition);
        // LD_C_L;
        // LD_B_H;
        // LD_DE(wStringBuffer2);
        // FARCALL(aGiveMoney);
        GiveMoney_Conv(wram->wStringBuffer2, temp);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto decrementdigit;
    else if(hram->hJoyLast & D_DOWN) {
    // decrementdigit:
        // LD_HL(mMom_WithdrawDepositMenuJoypad_DigitQuantities);
        // CALL(aMom_WithdrawDepositMenuJoypad_getdigitquantity);
        Mom_WithdrawDepositMenuJoypad_getdigitquantity(temp, wram->wMomBankDigitCursorPosition);
        // LD_C_L;
        // LD_B_H;
        // LD_DE(wStringBuffer2);
        // FARCALL(aTakeMoney);
        TakeMoney_Conv(wram->wStringBuffer2, temp);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto movecursorleft;
    else if(hram->hJoyLast & D_LEFT) {
    // movecursorleft:
        // LD_HL(wMomBankDigitCursorPosition);
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wMomBankDigitCursorPosition == 0)
            return;
        // DEC_hl;
        --wram->wMomBankDigitCursorPosition;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto movecursorright;
    else if(hram->hJoyLast & D_RIGHT) {
    // movecursorright:
        // LD_HL(wMomBankDigitCursorPosition);
        // LD_A_hl;
        // CP_A(5);
        // RET_NC ;
        if(wram->wMomBankDigitCursorPosition >= 5)
            return;
        // INC_hl;
        ++wram->wMomBankDigitCursorPosition;
        // RET;
        return;
    }
    // AND_A_A;
    // RET;
    return;
}

bool Mom_WithdrawDepositMenuJoypad(void){

    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto pressedB;
        if(hram->hJoyPressed & B_BUTTON) {
        // pressedB:
            // SCF;
            // RET;
            return true;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON);
        // IF_NZ goto pressedA;
        if(hram->hJoyPressed & A_BUTTON) {
        // pressedA:
            // AND_A_A;
            // RET;
            return false;
        }
        // CALL(aMom_WithdrawDepositMenuJoypad_dpadaction);
        Mom_WithdrawDepositMenuJoypad_dpadaction();
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // hlcoord(12, 6, wTilemap);
        // LD_BC(7);
        // LD_A(0x7f);
        // CALL(aByteFill);
        ByteFill(coord(12, 6, wram->wTilemap), 7, 0x7f);
        // hlcoord(12, 6, wTilemap);
        // LD_DE(wStringBuffer2);
        // LD_BC((PRINTNUM_MONEY | PRINTNUM_LEADINGZEROS | 3 << 8) | 6);
        // CALL(aPrintNum);
        PrintNum_Conv2(coord(12, 6, wram->wTilemap), wram->wStringBuffer2, PRINTNUM_MONEY | PRINTNUM_LEADINGZEROS | 3, 6);
        // LDH_A_addr(hVBlankCounter);
        // AND_A(0x10);
        // IF_NZ goto skip;
        if((hram->hVBlankCounter & 0x10) == 0) {
            // hlcoord(13, 6, wTilemap);
            // LD_A_addr(wMomBankDigitCursorPosition);
            // LD_C_A;
            // LD_B(0);
            // ADD_HL_BC;
            // LD_hl(0x7f);
            coord(13, 6, wram->wTilemap)[wram->wMomBankDigitCursorPosition] = 0x7f;
        }


    // skip:
        // CALL(aWaitBGMap);
        // goto loop;
    } while(WaitBGMap(), 1);
}

const txt_cmd_s MomLeavingText1[] = {
    text_far(v_MomLeavingText1)
    text_end
};

const txt_cmd_s MomLeavingText2[] = {
    text_far(v_MomLeavingText2)
    text_end
};

const txt_cmd_s MomLeavingText3[] = {
    text_far(v_MomLeavingText3)
    text_end
};

const txt_cmd_s MomIsThisAboutYourMoneyText[] = {
    text_far(v_MomIsThisAboutYourMoneyText)
    text_end
};

const txt_cmd_s MomBankWhatDoYouWantToDoText[] = {
    text_far(v_MomBankWhatDoYouWantToDoText)
    text_end
};

const txt_cmd_s MomStoreMoneyText[] = {
    text_far(v_MomStoreMoneyText)
    text_end
};

const txt_cmd_s MomTakeMoneyText[] = {
    text_far(v_MomTakeMoneyText)
    text_end
};

const txt_cmd_s MomSaveMoneyText[] = {
    text_far(v_MomSaveMoneyText)
    text_end
};

const txt_cmd_s MomHaventSavedThatMuchText[] = {
    text_far(v_MomHaventSavedThatMuchText)
    text_end
};

const txt_cmd_s MomNotEnoughRoomInWalletText[] = {
    text_far(v_MomNotEnoughRoomInWalletText)
    text_end
};

const txt_cmd_s MomInsufficientFundsInWalletText[] = {
    text_far(v_MomInsufficientFundsInWalletText)
    text_end
};

const txt_cmd_s MomNotEnoughRoomInBankText[] = {
    text_far(v_MomNotEnoughRoomInBankText)
    text_end
};

const txt_cmd_s MomStartSavingMoneyText[] = {
    text_far(v_MomStartSavingMoneyText)
    text_end
};

const txt_cmd_s MomStoredMoneyText[] = {
    text_far(v_MomStoredMoneyText)
    text_end
};

const txt_cmd_s MomTakenMoneyText[] = {
    text_far(v_MomTakenMoneyText)
    text_end
};

const txt_cmd_s MomJustDoWhatYouCanText[] = {
    text_far(v_MomJustDoWhatYouCanText)
    text_end
};

const char Mom_SavedString[] = "SAVED@";
const char Mon_WithdrawString[] = "WITHDRAW@";
const char Mom_DepositString[] = "DEPOSIT@";
const char Mom_HeldString[] = "HELD@";
