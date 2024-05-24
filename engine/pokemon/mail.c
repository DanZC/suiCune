#include "../../constants.h"
#include "mail.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../home/menu.h"
#include "../../data/text/common.h"

void SendMailToPC(void){
    LD_A(MON_ITEM);
    CALL(aGetPartyParamLocation);
    LD_D_hl;
    FARCALL(aItemIsMail);
    IF_NC goto full;
    CALL(aGetMailboxCount);
    CP_A(MAILBOX_CAPACITY);
    IF_NC goto full;
    LD_BC(MAIL_STRUCT_LENGTH);
    LD_HL(sMailboxes);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_A_addr(wCurPartyMon);
    LD_BC(MAIL_STRUCT_LENGTH);
    LD_HL(sPartyMail);
    CALL(aAddNTimes);
    PUSH_HL;
    LD_A(BANK(sMailboxCount));
    CALL(aOpenSRAM);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aCopyBytes);
    POP_HL;
    XOR_A_A;
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aByteFill);
    LD_A(MON_ITEM);
    CALL(aGetPartyParamLocation);
    LD_hl(0);
    LD_HL(sMailboxCount);
    INC_hl;
    CALL(aCloseSRAM);
    XOR_A_A;
    RET;


full:
    SCF;
    RET;

}

void DeleteMailFromPC(void){
//  Shift all mail messages in the mailbox
    LD_A(BANK(sMailboxCount));
    CALL(aOpenSRAM);
    LD_A_B;
    PUSH_BC;
    LD_HL(sMailboxes);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    PUSH_HL;
    ADD_HL_BC;
    POP_DE;
    POP_BC;

loop:
    LD_A_B;
    CP_A(MAILBOX_CAPACITY - 1);
    IF_Z goto done;
    PUSH_BC;
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aCopyBytes);
    POP_BC;
    INC_B;
    goto loop;

done:
    LD_H_D;
    LD_L_E;
    XOR_A_A;
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aByteFill);
    LD_HL(sMailboxCount);
    DEC_hl;
    JP(mCloseSRAM);

}

void ReadMailMessage(void){
    LD_A_B;
    LD_HL(sMailboxes);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    FARCALL(aReadAnyMail);
    RET;

}

void MoveMailFromPCToParty(void){
    LD_A(BANK(sMailboxCount));
    CALL(aOpenSRAM);
    PUSH_BC;
    LD_A_B;
    LD_BC(MAIL_STRUCT_LENGTH);
    LD_HL(sMailboxes);
    CALL(aAddNTimes);
    PUSH_HL;
    LD_A_addr(wCurPartyMon);
    LD_BC(MAIL_STRUCT_LENGTH);
    LD_HL(sPartyMail);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    POP_HL;
    PUSH_HL;
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aCopyBytes);
    POP_HL;
    LD_DE(PARTYMON_STRUCT_LENGTH - MON_MOVES);
    ADD_HL_DE;
    LD_D_hl;
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_hl_D;
    CALL(aCloseSRAM);
    POP_BC;
    JP(mDeleteMailFromPC);

}

void GetMailboxCount(void){
    LD_A(BANK(sMailboxCount));
    CALL(aOpenSRAM);
    LD_A_addr(sMailboxCount);
    LD_C_A;
    JP(mCloseSRAM);

}

void CheckPokeMail(void){
    PUSH_BC;
    PUSH_DE;
    FARCALL(aSelectMonFromParty);
    LD_A(POKEMAIL_REFUSED);
    IF_C goto pop_return;

    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_hl;
    FARCALL(aItemIsMail);
    LD_A(POKEMAIL_NO_MAIL);
    IF_NC goto pop_return;

    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    LD_A_addr(wCurPartyMon);
    LD_HL(sPartyMail);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    POP_HL;
    POP_BC;

//  Compare the mail message, byte for byte, with the expected message.
    LD_A(MAIL_MSG_LENGTH);
    LD_addr_A(wTempByteValue);

loop:
    LD_A_de;
    LD_C_A;
    LD_A_B;
    CALL(aGetFarByte);
    CP_A(0x50);
    IF_Z goto done;
    CP_A_C;
    LD_A(POKEMAIL_WRONG_MAIL);
    IF_NZ goto close_sram_return;
    INC_HL;
    INC_DE;
    LD_A_addr(wTempByteValue);
    DEC_A;
    LD_addr_A(wTempByteValue);
    IF_NZ goto loop;


done:
    FARCALL(aCheckCurPartyMonFainted);
    LD_A(POKEMAIL_LAST_MON);
    IF_C goto close_sram_return;
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    LD_A(POKEMAIL_CORRECT);


close_sram_return:
    CALL(aCloseSRAM);
    goto l_return;


pop_return:
    POP_DE;
    POP_BC;


l_return:
    LD_addr_A(wScriptVar);
    RET;

}

void GivePokeMail(void){
    LD_A_addr(wPartyCount);
    DEC_A;
    PUSH_AF;
    PUSH_BC;
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    POP_BC;
    LD_hl_B;
    POP_AF;
    PUSH_BC;
    PUSH_AF;
    LD_HL(sPartyMail);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_HL(wMonMailMessageBuffer);
    LD_BC(MAIL_MSG_LENGTH + 1);
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    CALL(aCopyBytes);
    POP_AF;
    PUSH_AF;
    LD_HL(wPartyMonOTs);
    LD_BC(NAME_LENGTH);
    CALL(aAddNTimes);
    LD_BC(NAME_LENGTH - 1);
    CALL(aCopyBytes);
    POP_AF;
    LD_HL(wPartyMon1ID);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    INC_DE;
    LD_A_addr(wCurPartySpecies);
    LD_de_A;
    INC_DE;
    POP_BC;
    LD_A_B;
    LD_de_A;
    JP(mCloseSRAM);

}

void GivePokeMail_Conv(const struct Pokemail* mail){
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // PUSH_AF;
    uint8_t a = wram->wPartyCount - 1;
    // PUSH_BC;
    // LD_HL(wPartyMon1Item);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // POP_BC;
    // LD_hl_B;
    wram->wPartyMon[a].mon.item = mail->item;
    // POP_AF;
    // PUSH_BC;
    // PUSH_AF;
    // LD_HL(sPartyMail);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    uint16_t partyMail = sPartyMail + (a * MAIL_STRUCT_LENGTH);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wMonMailMessageBuffer);
    // LD_BC(MAIL_MSG_LENGTH + 1);
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asPartyMail));
    // CALL(aCopyBytes);
    struct MailMsg* de = (struct MailMsg*)GBToRAMAddr(partyMail);
    CopyBytes_Conv2(de->message, wram->wMonMailMessageBuffer, MAIL_MSG_LENGTH + 1);
    // POP_AF;
    // PUSH_AF;
    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // CALL(aAddNTimes);
    // LD_BC(NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de->author, wram->wPartyMonOT[a], NAME_LENGTH - 1);
    // POP_AF;
    // LD_HL(wPartyMon1ID);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    de->authorID = wram->wPartyMon[a].mon.id;
    // INC_DE;
    // LD_A_addr(wCurPartySpecies);
    // LD_de_A;
    // INC_DE;
    de->species = wram->wCurPartySpecies;
    // POP_BC;
    // LD_A_B;
    // LD_de_A;
    de->type = mail->item;
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void BackupPartyMonMail(void){
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asPartyMail));
    // LD_HL(sPartyMail);
    // LD_DE(sPartyMailBackup);
    // LD_BC(PARTY_LENGTH * MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv(sPartyMailBackup, sPartyMail, PARTY_LENGTH * MAIL_STRUCT_LENGTH);
    // LD_HL(sMailboxCount);
    // LD_DE(sMailboxCountBackup);
    // LD_BC(1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv(sMailboxCountBackup, sMailboxCount, 1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void RestorePartyMonMail(void){
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asPartyMail));
    // LD_HL(sPartyMailBackup);
    // LD_DE(sPartyMail);
    // LD_BC(PARTY_LENGTH * MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv(sPartyMail, sPartyMailBackup, PARTY_LENGTH * MAIL_STRUCT_LENGTH);
    // LD_HL(sMailboxCountBackup);
    // LD_DE(sMailboxCount);
    // LD_BC(1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv(sMailboxCount, sMailboxCountBackup, 1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void DeletePartyMonMail(void){
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asPartyMail));
    // XOR_A_A;
    // LD_HL(sPartyMail);
    // LD_BC(PARTY_LENGTH * MAIL_STRUCT_LENGTH);
    // CALL(aByteFill);
    ByteFill_Conv(sPartyMail, PARTY_LENGTH * MAIL_STRUCT_LENGTH, 0);
    // XOR_A_A;
    // LD_HL(sMailboxCount);
    // LD_BC(1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
    // CALL(aByteFill);
    ByteFill_Conv(sMailboxCount, 1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH, 0);
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void IsAnyMonHoldingMail(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    IF_Z goto no_mons;
    LD_E_A;
    LD_HL(wPartyMon1Item);

loop:
    LD_D_hl;
    PUSH_HL;
    PUSH_DE;
    FARCALL(aItemIsMail);
    POP_DE;
    POP_HL;
    RET_C ;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;


no_mons:
    AND_A_A;
    RET;

}

void v_PlayerMailBoxMenu(void){
    static const txt_cmd_s EmptyMailboxText[] = {
        text_far(v_EmptyMailboxText)
        text_end
    };
    // CALL(aInitMail);
    // IF_Z goto nomail;
    if(!InitMail_Conv()) {
    // nomail:
        // LD_HL(mv_PlayerMailBoxMenu_EmptyMailboxText);
        // JP(mMenuTextboxBackup);
        return MenuTextboxBackup_Conv(EmptyMailboxText);
    }
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    CALL(aMailboxPC);
    // JP(mCloseWindow);
    CloseWindow_Conv2();
}

void InitMail(void){
//  return z if no mail
    LD_A(BANK(sMailboxCount));
    CALL(aOpenSRAM);
    LD_A_addr(sMailboxCount);
    CALL(aCloseSRAM);

//  initialize wMailboxCount from sMailboxCount
    LD_HL(wMailboxCount);
    LD_hli_A;
    //assert ['wMailboxCount + 1 == wMailboxItems'];
    AND_A_A;
    IF_Z goto done;  // if no mail, we're done

//  initialize wMailboxItems with incrementing values starting at 1
    LD_B_A;
    LD_A(1);

loop:
    LD_hli_A;
    INC_A;
    DEC_B;
    IF_NZ goto loop;


done:
    LD_hl(-1);  // terminate

    LD_A_addr(wMailboxCount);
    AND_A_A;
    RET;

}

//  return false (z) if no mail
bool InitMail_Conv(void){
    // LD_A(BANK(sMailboxCount));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(sMailboxCount));
    // LD_A_addr(sMailboxCount);
    uint8_t mailboxCount = gb_read(sMailboxCount);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();

//  initialize wMailboxCount from sMailboxCount
    // LD_HL(wMailboxCount);
    // LD_hli_A;
    wram->wMailboxCount = mailboxCount;
    //assert ['wMailboxCount + 1 == wMailboxItems'];
    uint8_t i = 0;
    // AND_A_A;
    // IF_Z goto done;  // if no mail, we're done
    if(mailboxCount != 0) {
    //  initialize wMailboxItems with incrementing values starting at 1
        // LD_B_A;
        uint8_t b = mailboxCount;
        // LD_A(1);
        uint8_t a = 1;

        do {
        // loop:
            // LD_hli_A;
            wram->wMailboxItems[i++] = a++;
            // INC_A;
            // DEC_B;
            // IF_NZ goto loop;
        } while(--b != 0);
    }

// done:
    // LD_hl(-1);  // terminate
    wram->wMailboxItems[i] = (uint8_t)-1;

    // LD_A_addr(wMailboxCount);
    // AND_A_A;
    // RET;
    return wram->wMailboxCount != 0;
}

void MailboxPC_GetMailAuthor(void){
    DEC_A;
    LD_HL(sMailbox1Author);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(sMailboxCount));
    CALL(aOpenSRAM);
    LD_DE(wStringBuffer2);
    PUSH_DE;
    LD_BC(NAME_LENGTH - 1);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    CALL(aCloseSRAM);
    POP_DE;
    RET;

}

void MailboxPC_PrintMailAuthor(void){
    PUSH_DE;
    LD_A_addr(wMenuSelection);
    CALL(aMailboxPC_GetMailAuthor);
    POP_HL;
    JP(mPlaceString);

}

void MailboxPC(void){
    XOR_A_A;
    LD_addr_A(wCurMessageScrollPosition);
    LD_A(1);
    LD_addr_A(wCurMessageIndex);

loop:
    CALL(aInitMail);
    LD_HL(mMailboxPC_TopMenuHeader);
    CALL(aCopyMenuHeader);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aInitScrollingMenu);
    CALL(aUpdateSprites);

    LD_A_addr(wCurMessageIndex);
    LD_addr_A(wMenuCursorPosition);
    LD_A_addr(wCurMessageScrollPosition);
    LD_addr_A(wMenuScrollPosition);
    CALL(aScrollingMenu);
    LD_A_addr(wMenuScrollPosition);
    LD_addr_A(wCurMessageScrollPosition);
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wCurMessageIndex);

    LD_A_addr(wMenuJoypad);
    CP_A(B_BUTTON);
    IF_Z goto exit;
    CALL(aMailboxPC_Submenu);
    goto loop;


exit:
    XOR_A_A;
    RET;


Submenu:
    LD_HL(mMailboxPC_SubMenuHeader);
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    CALL(aExitMenu);
    IF_C goto subexit;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_HL(mMailboxPC_Jumptable);
    RST(aJumpTable);


subexit:
    RET;


Jumptable:
    //dw ['.ReadMail'];
    //dw ['.PutInPack'];
    //dw ['.AttachMail'];
    //dw ['.Cancel'];


ReadMail:
    CALL(aFadeToMenu);
    LD_A_addr(wMenuSelection);
    DEC_A;
    LD_B_A;
    CALL(aReadMailMessage);
    JP(mCloseSubmenu);


PutInPack:
    LD_HL(mMailboxPC_MailMessageLostText);
    CALL(aMenuTextbox);
    CALL(aYesNoBox);
    CALL(aExitMenu);
    RET_C ;
    LD_A_addr(wMenuSelection);
    DEC_A;
    CALL(aMailboxPC_GetMailType);
    LD_A(1);
    LD_addr_A(wItemQuantityChange);
    LD_HL(wNumItems);
    CALL(aReceiveItem);
    IF_C goto put_in_bag;
    LD_HL(mMailboxPC_MailPackFullText);
    JP(mMenuTextboxBackup);


put_in_bag:
    LD_A_addr(wMenuSelection);
    DEC_A;
    LD_B_A;
    CALL(aDeleteMailFromPC);
    LD_HL(mMailboxPC_MailClearedPutAwayText);
    JP(mMenuTextboxBackup);


MailClearedPutAwayText:
    //text_far ['_MailClearedPutAwayText']
    //text_end ['?']


MailPackFullText:
    //text_far ['_MailPackFullText']
    //text_end ['?']


MailMessageLostText:
    //text_far ['_MailMessageLostText']
    //text_end ['?']


GetMailType:
    PUSH_AF;
    LD_A(BANK(sMailboxCount));
    CALL(aOpenSRAM);
    POP_AF;
    LD_HL(sMailbox1Type);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wCurItem);
    JP(mCloseSRAM);


AttachMail:
    CALL(aFadeToMenu);
    XOR_A_A;
    LD_addr_A(wPartyMenuActionText);
    CALL(aClearBGPalettes);

try_again:
    FARCALL(aLoadPartyMenuGFX);
    FARCALL(aInitPartyMenuWithCancel);
    FARCALL(aInitPartyMenuGFX);
    FARCALL(aWritePartyMenuTilemap);
    FARCALL(aPrintPartyMenuText);
    CALL(aWaitBGMap);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    FARCALL(aPartyMenuSelect);
    IF_C goto exit2;
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto egg;
    LD_A(MON_ITEM);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    AND_A_A;
    IF_Z goto attach_mail;
    LD_HL(mMailboxPC_MailAlreadyHoldingItemText);
    CALL(aPrintText);
    goto try_again;


egg:
    LD_HL(mMailboxPC_MailEggText);
    CALL(aPrintText);
    goto try_again;


attach_mail:
    LD_A_addr(wMenuSelection);
    DEC_A;
    LD_B_A;
    CALL(aMoveMailFromPCToParty);
    LD_HL(mMailboxPC_MailMovedFromBoxText);
    CALL(aPrintText);


exit2:
    JP(mCloseSubmenu);


MailAlreadyHoldingItemText:
    //text_far ['_MailAlreadyHoldingItemText']
    //text_end ['?']


MailEggText:
    //text_far ['_MailEggText']
    //text_end ['?']


MailMovedFromBoxText:
    //text_far ['_MailMovedFromBoxText']
    //text_end ['?']


Cancel:
    RET;


//TopMenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['8', '1', 'SCREEN_WIDTH - 2', '10'];
    //dw ['.TopMenuData'];
    //db ['1'];  // default option


//TopMenuData:
    //db ['SCROLLINGMENU_DISPLAY_ARROWS'];  // flags
    //db ['4', '0'];  // rows, columns
    //db ['SCROLLINGMENU_ITEMS_NORMAL'];  // item format
    //dbw ['0', 'wMailboxCount']
    //dba ['MailboxPC_PrintMailAuthor']
    //dba ['NULL']
    //dba ['NULL']


//SubMenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', '13', '9'];
    //dw ['.SubMenuData'];
    //db ['1'];  // default option


//SubMenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['4'];  // items
    //db ['"READ MAIL@"'];
    //db ['"PUT IN PACK@"'];
    //db ['"ATTACH MAIL@"'];
    //db ['"CANCEL@"'];

}
