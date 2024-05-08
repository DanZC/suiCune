#include "../../constants.h"
#include "consume_held_item.h"
#include "effect_commands.h"
#include "../../data/battle/held_consumables.h"

void ConsumeHeldItem(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    struct PartyMon* pmon;
    struct BattleMon* bmon;
    uint8_t curMon;
    if(hram->hBattleTurn == 0) {
        // LD_HL(wOTPartyMon1Item);
        pmon = wram->wOTPartyMon;
        // LD_DE(wEnemyMonItem);
        bmon = &wram->wEnemyMon;
        // LD_A_addr(wCurOTMon);
        curMon = wram->wCurOTMon;
    }
    else {
        // IF_Z goto theirturn;
        // LD_HL(wPartyMon1Item);
        pmon = wram->wPartyMon;
        // LD_DE(wBattleMonItem);
        bmon = &wram->wBattleMon;
        // LD_A_addr(wCurBattleMon);
        curMon = wram->wCurBattleMon;
    }

// theirturn:
    // PUSH_HL;
    // PUSH_AF;
    // LD_A_de;
    // LD_B_A;
    item_t item = bmon->item;
    // FARCALL(aGetItemHeldEffect);
    uint8_t effect = HIGH(GetItemHeldEffect_Conv(item));
    // LD_HL(mConsumableEffects);
    const uint8_t* hl = ConsumableEffects;

    uint8_t a;
    do {
    // loop:
        // LD_A_hli;
        a = *(hl++);
        // CP_A_B;
        // IF_Z goto ok;
        if(a == effect) {
        // ok:
            // XOR_A_A;
            // LD_de_A;
            bmon->item = NO_ITEM;
            // POP_AF;
            // POP_HL;
            // CALL(aGetPartyLocation);
            // LDH_A_addr(hBattleTurn);
            // AND_A_A;
            // IF_NZ goto ourturn;
            // LD_A_addr(wBattleMode);
            // DEC_A;
            // IF_Z goto done;
            if(hram->hBattleTurn != 0 || wram->wBattleMode != WILD_BATTLE) {
            // ourturn:
                // LD_hl(NO_ITEM);
                pmon[curMon].mon.item = NO_ITEM;
            }

        // done:
            // POP_BC;
            // POP_DE;
            // POP_HL;
            // RET;
            return;
        }
        // INC_A;
        // IF_NZ goto loop;
    } while(a != 0xff);
    // POP_AF;
    // POP_HL;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return;

// INCLUDE "data/battle/held_consumables.asm"

}
