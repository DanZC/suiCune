#include "../constants.h"
#include "print_opp_message.h"
#include "fixed_words.h"
#include "../home/delay.h"
#include "../home/text.h"
#include "../home/battle.h"
#include "../home/copy.h"

void Mobile_PrintOpponentBattleMessage(uint8_t c){
    // LD_A_C;
    // PUSH_AF;
    // CALL(aSpeechTextbox);
    SpeechTextbox_Conv2();
    // CALL(aMobileTextBorder);
    MobileTextBorder();
    // POP_AF;
    // DEC_A;
    // LD_BC(0xc);
    // LD_HL(w5_MobileOpponentBattleMessages);
    // CALL(aAddNTimes);
    // LD_DE(wMobileOpponentBattleMessage);
    // LD_BC(0xc);
    // LD_A(BANK(w5_MobileOpponentBattleMessages));
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(wram->wMobileOpponentBattleMessage, wram->w5_MobileOpponentBattleMessages + 12 * (c - 1), 12);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);

    // LD_BC(wMobileOpponentBattleMessage);
    // decoord(1, 14, wTilemap);
    // FARCALL(aPrintEZChatBattleMessage);
    PrintEZChatBattleMessage(coord(1, 14, wram->wTilemap), wram->wMobileOpponentBattleMessage);

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // LD_C(180);
    // CALL(aDelayFrames);
    DelayFrames_Conv(180);
    // RET;
}
