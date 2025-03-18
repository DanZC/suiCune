#include "../../constants.h"
#include "mail.h"
#include "mail_2.h"
#include "party_menu.h"
#include "bills_pc_top.h"
#include "move_mon.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../home/menu.h"
#include "../../home/scrolling_menu.h"
#include "../../home/map_objects.h"
#include "../../home/map.h"
#include "../../home/item.h"
#include "../../home/tilemap.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../data/text/common.h"

bool SendMailToPC(uint8_t b){
    // LD_A(MON_ITEM);
    // CALL(aGetPartyParamLocation);
    // LD_D_hl;
    item_t itm = wram->wPartyMon[b].mon.item;
    // FARCALL(aItemIsMail);
    // IF_NC goto full;
    if(ItemIsMail_Conv(itm)) {
        // CALL(aGetMailboxCount);
        uint8_t count = GetMailboxCount();
        // CP_A(MAILBOX_CAPACITY);
        // IF_NC goto full;
        if(count < MAILBOX_CAPACITY) {
            // LD_BC(MAIL_STRUCT_LENGTH);
            // LD_HL(sMailboxes);
            // CALL(aAddNTimes);
            uint16_t dest = sMailboxes + MAIL_STRUCT_LENGTH * count;
            // LD_D_H;
            // LD_E_L;
            // LD_A_addr(wCurPartyMon);
            // LD_BC(MAIL_STRUCT_LENGTH);
            // LD_HL(sPartyMail);
            // CALL(aAddNTimes);
            // PUSH_HL;
            uint16_t source = sPartyMail + MAIL_STRUCT_LENGTH * b;
            // LD_A(BANK(sMailboxCount));
            // CALL(aOpenSRAM);
            OpenSRAM_Conv(MBANK(asMailboxCount));
            // LD_BC(MAIL_STRUCT_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(GBToRAMAddr(dest), GBToRAMAddr(source), MAIL_STRUCT_LENGTH);
            // POP_HL;
            // XOR_A_A;
            // LD_BC(MAIL_STRUCT_LENGTH);
            // CALL(aByteFill);
            ByteFill(GBToRAMAddr(source), MAIL_STRUCT_LENGTH, 0);
            // LD_A(MON_ITEM);
            // CALL(aGetPartyParamLocation);
            // LD_hl(0);
            wram->wPartyMon[b].mon.item = NO_ITEM;
            // LD_HL(sMailboxCount);
            // INC_hl;
            gb_write(sMailboxCount, gb_read(sMailboxCount) + 1);
            // CALL(aCloseSRAM);
            CloseSRAM_Conv();
            // XOR_A_A;
            // RET;
            return false;
        }
    }

// full:
    // SCF;
    // RET;
    return true;
}

//  Shift all mail messages in the mailbox
void DeleteMailFromPC(uint8_t b){
    // LD_A(BANK(sMailboxCount));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMailboxCount));
    // LD_A_B;
    // PUSH_BC;
    // LD_HL(sMailboxes);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // PUSH_HL;
    struct MailMsg* de = ((struct MailMsg*)GBToRAMAddr(sMailboxes)) + b;
    // ADD_HL_BC;
    const struct MailMsg* hl = de + 1;
    // POP_DE;
    // POP_BC;

    while(b != MAILBOX_CAPACITY - 1) {
    // loop:
        // LD_A_B;
        // CP_A(MAILBOX_CAPACITY - 1);
        // IF_Z goto done;
        // PUSH_BC;
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(de, hl, sizeof(*de));
        de++, hl++;
        // POP_BC;
        // INC_B;
        b++;
        // goto loop;
    }

// done:
    // LD_H_D;
    // LD_L_E;
    // XOR_A_A;
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aByteFill);
    ByteFill(de, sizeof(*de), 0x0);
    // LD_HL(sMailboxCount);
    // DEC_hl;
    gb_write(sMailboxCount, gb_read(sMailboxCount) - 1);
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void ReadMailMessage(uint8_t b){
    OpenSRAM_Conv(MBANK(asMailboxes));
    // LD_A_B;
    // LD_HL(sMailboxes);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // FARCALL(aReadAnyMail);
    ReadAnyMail_Conv(GBToRAMAddr(sMailboxes + MAIL_STRUCT_LENGTH * b));
    // RET;
    CloseSRAM_Conv();
}

void MoveMailFromPCToParty(uint8_t b){
    // LD_A(BANK(sMailboxCount));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMailboxCount));
    // PUSH_BC;
    // LD_A_B;
    // LD_BC(MAIL_STRUCT_LENGTH);
    // LD_HL(sMailboxes);
    // CALL(aAddNTimes);
    // PUSH_HL;
    struct MailMsg* hl = ((struct MailMsg*)GBToRAMAddr(sMailboxes)) + b;
    // LD_A_addr(wCurPartyMon);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // LD_HL(sPartyMail);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    struct MailMsg* de = ((struct MailMsg*)GBToRAMAddr(sPartyMail)) + wram->wCurPartyMon;
    // POP_HL;
    // PUSH_HL;
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(de, hl, sizeof(*de));
    // POP_HL;
    // LD_DE(PARTYMON_STRUCT_LENGTH - MON_MOVES);
    // ADD_HL_DE;
    // LD_D_hl;
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1Item);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_hl_D;
    wram->wPartyMon[wram->wCurPartyMon].mon.item = hl->type;
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // POP_BC;
    // JP(mDeleteMailFromPC);
    return DeleteMailFromPC(b);
}

uint8_t GetMailboxCount(void){
    // LD_A(BANK(sMailboxCount));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMailboxCount));
    // LD_A_addr(sMailboxCount);
    // LD_C_A;
    uint8_t c = gb_read(sMailboxCount);
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
    return c;
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

void CheckPokeMail_Conv(const char* message){
    // PUSH_BC;
    // PUSH_DE;
    // FARCALL(aSelectMonFromParty);
    u8_flag_s res = SelectMonFromParty();
    // LD_A(POKEMAIL_REFUSED);
    // IF_C goto pop_return;
    if(res.flag) {
        wram->wScriptVar = POKEMAIL_REFUSED;
        return;
    }

    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1Item);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_D_hl;
    // FARCALL(aItemIsMail);
    // LD_A(POKEMAIL_NO_MAIL);
    // IF_NC goto pop_return;
    if(!ItemIsMail_Conv(wram->wPartyMon[wram->wCurPartyMon].mon.item)) {
        wram->wScriptVar = POKEMAIL_NO_MAIL;
        return;
    }

    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asPartyMail));
    // LD_A_addr(wCurPartyMon);
    // LD_HL(sPartyMail);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    struct MailMsg* de = (struct MailMsg*)GBToRAMAddr(sPartyMail + MAIL_STRUCT_LENGTH * wram->wCurPartyMon);
    // LD_D_H;
    // LD_E_L;
    uint8_t* tmsg = U82C(message);
    uint8_t* smsg = de->message;
    // POP_HL;
    // POP_BC;

//  Compare the mail message, byte for byte, with the expected message.
    // LD_A(MAIL_MSG_LENGTH);
    // LD_addr_A(wTempByteValue);
    uint8_t a = MAIL_MSG_LENGTH;

    do {
    // loop:
        // LD_A_de;
        // LD_C_A;
        uint8_t c = *tmsg;
        // LD_A_B;
        // CALL(aGetFarByte);
        uint8_t b = *smsg;
        // CP_A(0x50);
        // IF_Z goto done;
        if(b == 0x50)
            break;
        // CP_A_C;
        // LD_A(POKEMAIL_WRONG_MAIL);
        // IF_NZ goto close_sram_return;
        if(b != c) {
            CloseSRAM_Conv();
            wram->wScriptVar = POKEMAIL_WRONG_MAIL;
            return;
        }
        // INC_HL;
        // INC_DE;
        tmsg++, smsg++;
        // LD_A_addr(wTempByteValue);
        // DEC_A;
        // LD_addr_A(wTempByteValue);
        // IF_NZ goto loop;
    } while(--a != 0);

// done:
    // FARCALL(aCheckCurPartyMonFainted);
    // LD_A(POKEMAIL_LAST_MON);
    // IF_C goto close_sram_return;
    if(CheckCurPartyMonFainted_Conv()) {
        CloseSRAM_Conv();
        wram->wScriptVar = POKEMAIL_LAST_MON;
        return;
    }
    // XOR_A_A;  // REMOVE_PARTY
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // FARCALL(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox_Conv(REMOVE_PARTY);
    // LD_A(POKEMAIL_CORRECT);

// close_sram_return:
    // CALL(aCloseSRAM);
    // goto l_return;

// pop_return:
    // POP_DE;
    // POP_BC;

// l_return:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = POKEMAIL_CORRECT;
    // RET;
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
    CopyBytes(de->message, wram->wMonMailMessageBuffer, MAIL_MSG_LENGTH + 1);
    // POP_AF;
    // PUSH_AF;
    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // CALL(aAddNTimes);
    // LD_BC(NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes(de->author, wram->wPartyMonOT[a], NAME_LENGTH - 1);
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
    CopyBytes_GB(sPartyMailBackup, sPartyMail, PARTY_LENGTH * MAIL_STRUCT_LENGTH);
    // LD_HL(sMailboxCount);
    // LD_DE(sMailboxCountBackup);
    // LD_BC(1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_GB(sMailboxCountBackup, sMailboxCount, 1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
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
    CopyBytes_GB(sPartyMail, sPartyMailBackup, PARTY_LENGTH * MAIL_STRUCT_LENGTH);
    // LD_HL(sMailboxCountBackup);
    // LD_DE(sMailboxCount);
    // LD_BC(1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_GB(sMailboxCount, sMailboxCountBackup, 1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
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
    ByteFill_GB(sPartyMail, PARTY_LENGTH * MAIL_STRUCT_LENGTH, 0);
    // XOR_A_A;
    // LD_HL(sMailboxCount);
    // LD_BC(1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH);
    // CALL(aByteFill);
    ByteFill_GB(sMailboxCount, 1 + MAILBOX_CAPACITY * MAIL_STRUCT_LENGTH, 0);
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

bool IsAnyMonHoldingMail_Conv(void){
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // IF_Z goto no_mons;
    if(wram->wPartyCount == 0)
        return false;
    // LD_E_A;
    uint8_t e = wram->wPartyCount;
    // LD_HL(wPartyMon1Item);
    struct PartyMon* hl = wram->wPartyMon;

    do {
    // loop:
        // LD_D_hl;
        // PUSH_HL;
        // PUSH_DE;
        // FARCALL(aItemIsMail);
        // POP_DE;
        // POP_HL;
        // RET_C ;
        if(ItemIsMail_Conv(hl->mon.item))
            return true;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    } while(hl++, --e != 0);


// no_mons:
    // AND_A_A;
    // RET;
    return false;
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
    // CALL(aMailboxPC);
    MailboxPC();
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
    OpenSRAM_Conv(MBANK(asMailboxCount));
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

uint8_t* MailboxPC_GetMailAuthor(uint8_t a){
    // DEC_A;
    // LD_HL(sMailbox1Author);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_A(BANK(sMailboxCount));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMailboxCount));
    struct MailMsg* hl = ((struct MailMsg*)GBToRAMAddr(sMailbox1)) + (a - 1);
    // LD_DE(wStringBuffer2);
    // PUSH_DE;
    // LD_BC(NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes(wram->wStringBuffer1, hl->author, NAME_LENGTH - 1);
    // LD_A(0x50);
    // LD_de_A;
    wram->wStringBuffer1[NAME_LENGTH - 1] = 0x50;
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // POP_DE;
    // RET;
    return wram->wStringBuffer1;
}

void MailboxPC_PrintMailAuthor(const struct MenuData* data, tile_t* tile){
    (void)data;
    // PUSH_DE;
    // LD_A_addr(wMenuSelection);
    // CALL(aMailboxPC_GetMailAuthor);
    // POP_HL;
    // JP(mPlaceString);
    PlaceStringSimple(MailboxPC_GetMailAuthor(wram->wMenuSelection), tile);
}

static const struct MenuHeader MailboxPC_TopMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(8, 1, SCREEN_WIDTH - 2, 10),
    .data = &(struct MenuData){ //dw ['.TopMenuData'];
    //TopMenuData:
        .flags = SCROLLINGMENU_DISPLAY_ARROWS,  // flags
        .scrollingMenu = {
            .rows = 4, .cols = 0,  // rows, columns
            .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
            //dbw ['0', 'wMailboxCount']
            .list = wram_ptr(wMailboxCount),
            .func1 = MailboxPC_PrintMailAuthor,
            .func2 = NULL,
            .func3 = NULL,
        },
    },
    .defaultOption = 1,  // default option
};

static const struct MenuHeader MailboxPC_SubMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 13, 9),
    .data = &(struct MenuData) { //dw ['.SubMenuData'];
    //SubMenuData:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 4,  // items
            .options = (const char*[]) {
                "READ MAIL@",
                "PUT IN PACK@",
                "ATTACH MAIL@",
                "CANCEL@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

static item_t MailboxPC_GetMailType(uint8_t sel) {
    // PUSH_AF;
    // LD_A(BANK(sMailboxCount));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMailboxCount));
    // POP_AF;
    // LD_HL(sMailbox1Type);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_A_hl;
    // LD_addr_A(wCurItem);
    wram->wCurItem = gb_read(sMailbox1Type + MAIL_STRUCT_LENGTH * sel);
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
    return wram->wCurItem;
}

static void MailboxPC_Submenu(void){
    static const txt_cmd_s MailMessageLostText[] = {
        text_far(v_MailMessageLostText)
        text_end
    };
    static const txt_cmd_s MailPackFullText[] = {
        text_far(v_MailPackFullText)
        text_end
    };
    static const txt_cmd_s MailClearedPutAwayText[] = {
        text_far(v_MailClearedPutAwayText)
        text_end
    };
    static const txt_cmd_s MailAlreadyHoldingItemText[] = {
        text_far(v_MailAlreadyHoldingItemText)
        text_end
    };
    static const txt_cmd_s MailEggText[] = {
        text_far(v_MailEggText)
        text_end
    };
    static const txt_cmd_s MailMovedFromBoxText[] = {
        text_far(v_MailMovedFromBoxText)
        text_end
    };
    // LD_HL(mMailboxPC_SubMenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MailboxPC_SubMenuHeader);
    // CALL(aVerticalMenu);
    bool cancel = VerticalMenu_Conv();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // IF_C goto subexit;
    if(!cancel) {
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // LD_HL(mMailboxPC_Jumptable);
        // RST(aJumpTable);
        switch(wram->wMenuCursorY - 1) {
        // Jumptable:
            //dw ['.ReadMail'];
            case 0: 
            // ReadMail:
                // CALL(aFadeToMenu);
                FadeToMenu_Conv();
                // LD_A_addr(wMenuSelection);
                // DEC_A;
                // LD_B_A;
                // CALL(aReadMailMessage);
                ReadMailMessage(wram->wMenuSelection - 1);
                // JP(mCloseSubmenu);
                return CloseSubmenu_Conv();
            //dw ['.PutInPack'];
            case 1: {
            // PutInPack:
                // LD_HL(mMailboxPC_MailMessageLostText);
                // CALL(aMenuTextbox);
                MenuTextbox_Conv(MailMessageLostText);
                // CALL(aYesNoBox);
                bool cancel = !YesNoBox_Conv();
                // CALL(aExitMenu);
                ExitMenu_Conv2();
                // RET_C ;
                if(cancel)
                    return;
                // LD_A_addr(wMenuSelection);
                // DEC_A;
                // CALL(aMailboxPC_GetMailType);
                item_t item = MailboxPC_GetMailType(wram->wMenuSelection - 1);
                // LD_A(1);
                // LD_addr_A(wItemQuantityChange);
                wram->wItemQuantityChange = 1;
                // LD_HL(wNumItems);
                // CALL(aReceiveItem);
                // IF_C goto put_in_bag;
                if(!ReceiveItem_Conv((item_pocket_s*)&wram->wNumItems, item, 1)) {
                    // LD_HL(mMailboxPC_MailPackFullText);
                    // JP(mMenuTextboxBackup);
                    return MenuTextboxBackup_Conv(MailPackFullText);
                }

            // put_in_bag:
                // LD_A_addr(wMenuSelection);
                // DEC_A;
                // LD_B_A;
                // CALL(aDeleteMailFromPC);
                DeleteMailFromPC(wram->wMenuSelection - 1);
                // LD_HL(mMailboxPC_MailClearedPutAwayText);
                // JP(mMenuTextboxBackup);
                return MenuTextboxBackup_Conv(MailClearedPutAwayText);
            }
            //dw ['.AttachMail'];
            case 2: {
            // AttachMail:
                // CALL(aFadeToMenu);
                FadeToMenu_Conv();
                // XOR_A_A;
                // LD_addr_A(wPartyMenuActionText);
                wram->wPartyMenuActionText = 0x0;
                // CALL(aClearBGPalettes);
                ClearBGPalettes_Conv();

                while(1) {
                // try_again:
                    // FARCALL(aLoadPartyMenuGFX);
                    LoadPartyMenuGFX();
                    // FARCALL(aInitPartyMenuWithCancel);
                    InitPartyMenuWithCancel();
                    // FARCALL(aInitPartyMenuGFX);
                    InitPartyMenuGFX();
                    // FARCALL(aWritePartyMenuTilemap);
                    WritePartyMenuTilemap();
                    // FARCALL(aPrintPartyMenuText);
                    PrintPartyMenuText();
                    // CALL(aWaitBGMap);
                    WaitBGMap_Conv();
                    // CALL(aSetPalettes);
                    SetPalettes_Conv();
                    // CALL(aDelayFrame);
                    DelayFrame();
                    // FARCALL(aPartyMenuSelect);
                    u8_flag_s res = PartyMenuSelect();
                    // IF_C goto exit2;
                    if(res.flag)
                        return CloseSubmenu_Conv();
                    // LD_A_addr(wCurPartySpecies);
                    // CP_A(EGG);
                    // IF_Z goto egg;
                    if(wram->wCurPartySpecies == EGG) {
                    // egg:
                        // LD_HL(mMailboxPC_MailEggText);
                        // CALL(aPrintText);
                        PrintText_Conv2(MailEggText);
                        // goto try_again;
                        continue;
                    }
                    // LD_A(MON_ITEM);
                    // CALL(aGetPartyParamLocation);
                    // LD_A_hl;
                    // AND_A_A;
                    // IF_Z goto attach_mail;
                    if(wram->wPartyMon[wram->wCurPartyMon].mon.item == NO_ITEM)
                        break;
                    // LD_HL(mMailboxPC_MailAlreadyHoldingItemText);
                    // CALL(aPrintText);
                    PrintText_Conv2(MailAlreadyHoldingItemText);
                    // goto try_again;
                }

            // attach_mail:
                // LD_A_addr(wMenuSelection);
                // DEC_A;
                // LD_B_A;
                // CALL(aMoveMailFromPCToParty);
                MoveMailFromPCToParty(wram->wMenuSelection - 1);
                // LD_HL(mMailboxPC_MailMovedFromBoxText);
                // CALL(aPrintText);
                PrintText_Conv2(MailMovedFromBoxText);

            // exit2:
                // JP(mCloseSubmenu);
                return CloseSubmenu_Conv();
            }
            //dw ['.Cancel'];
            default:
            // Cancel:
                // RET;
                return;
        }
    }

// subexit:
    // RET;
}

void MailboxPC(void){
    // XOR_A_A;
    // LD_addr_A(wCurMessageScrollPosition);
    wram->wCurMessageScrollPosition = 0;
    // LD_A(1);
    // LD_addr_A(wCurMessageIndex);
    wram->wCurMessageIndex = 1;

    while(1) {
    // loop:
        // CALL(aInitMail);
        InitMail_Conv();
        // LD_HL(mMailboxPC_TopMenuHeader);
        // CALL(aCopyMenuHeader);
        CopyMenuHeader_Conv2(&MailboxPC_TopMenuHeader);
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
        // CALL(aInitScrollingMenu);
        InitScrollingMenu_Conv();
        // CALL(aUpdateSprites);
        UpdateSprites_Conv();

        // LD_A_addr(wCurMessageIndex);
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = wram->wCurMessageIndex;
        // LD_A_addr(wCurMessageScrollPosition);
        // LD_addr_A(wMenuScrollPosition);
        wram->wMenuScrollPosition = wram->wCurMessageScrollPosition;
        // CALL(aScrollingMenu);
        ScrollingMenu_Conv();
        // LD_A_addr(wMenuScrollPosition);
        // LD_addr_A(wCurMessageScrollPosition);
        wram->wCurMessageScrollPosition = wram->wMenuScrollPosition;
        // LD_A_addr(wMenuCursorY);
        // LD_addr_A(wCurMessageIndex);
        wram->wCurMessageIndex = wram->wMenuCursorY;

        // LD_A_addr(wMenuJoypad);
        // CP_A(B_BUTTON);
        // IF_Z goto exit;
        if(wram->wMenuJoypad == B_BUTTON)
            break;
        // CALL(aMailboxPC_Submenu);
        MailboxPC_Submenu();
        // goto loop;
    }

// exit:
    // XOR_A_A;
    // RET;
    return;
}
