#include "../../../constants.h"
#include "thief.h"
#include "../../../home/battle.h"
#include "../../../home/names.h"
#include "../../pokemon/mail_2.h"
#include "../../../data/text/battle.h"

static void BattleCommand_Thief_playeritem(item_t** de, item_t** hl) {
    // LD_A(1);
    // CALL(aBattlePartyAttr);
    // LD_D_H;
    // LD_E_L;
    if(de)
        *de = &wram->wPartyMon[wram->wCurPartyMon].mon.item;
    // LD_HL(wBattleMonItem);
    if(hl)
        *hl = &wram->wEnemyMon.item;
    // RET;
}


static void BattleCommand_Thief_enemyitem(item_t** de, item_t** hl) {
    // LD_A(1);
    // CALL(aOTPartyAttr);
    // LD_D_H;
    // LD_E_L;
    if(de)
        *de = &wram->wOTPartyMon[wram->wCurOTMon].mon.item;
    // LD_HL(wEnemyMonItem);
    if(hl)
        *hl = &wram->wEnemyMon.item;
    // RET;
}


void BattleCommand_Thief(void){
//  thief

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto enemy;
    item_t* hl;
    item_t* de;
    item_t itm;
    if(hram->hBattleTurn == 0) {
    //  The player needs to be able to steal an item.

        // CALL(aBattleCommand_Thief_playeritem);
        BattleCommand_Thief_playeritem(NULL, &hl);
        // LD_A_hl;
        // AND_A_A;
        // RET_NZ ;
        if(*hl != NO_ITEM)
            return;

    //  The enemy needs to have an item to steal.

        // CALL(aBattleCommand_Thief_enemyitem);
        BattleCommand_Thief_enemyitem(NULL, &hl);
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(*hl == NO_ITEM)
            return;

    //  Can't steal mail.

        // LD_addr_A(wNamedObjectIndex);
        itm = *hl;
        // LD_D_A;
        // FARCALL(aItemIsMail);
        // RET_C ;
        if(ItemIsMail_Conv(itm))
            return;

        // LD_A_addr(wEffectFailed);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wEffectFailed)
            return;

        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // IF_Z goto stealenemyitem;
        if(wram->wLinkMode != 0) {

            // LD_A_addr(wBattleMode);
            // DEC_A;
            // RET_Z ;

            // ??? There's no instance where a player is in a wild battle while link mode is not zero.
            if(wram->wBattleMode == WILD_BATTLE)
                return;
        }
    // stealenemyitem:
        // CALL(aBattleCommand_Thief_enemyitem);
        BattleCommand_Thief_enemyitem(&de, &hl);
        // XOR_A_A;
        // LD_hl_A;
        *hl = NO_ITEM;
        // LD_de_A;
        *de = NO_ITEM;

        // CALL(aBattleCommand_Thief_playeritem);
        BattleCommand_Thief_playeritem(&de, &hl);
        // LD_A_addr(wNamedObjectIndex);
        // LD_hl_A;
        *hl = itm;
        // LD_de_A;
        *de = itm;
        // goto stole;
    }
    else {
    // enemy:

    //  The enemy can't already have an item.

        // CALL(aBattleCommand_Thief_enemyitem);
        BattleCommand_Thief_enemyitem(NULL, &hl);
        // LD_A_hl;
        // AND_A_A;
        // RET_NZ ;
        if(*hl != NO_ITEM)
            return;

    //  The player must have an item to steal.

        // CALL(aBattleCommand_Thief_playeritem);
        BattleCommand_Thief_playeritem(NULL, &hl);
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(*hl == NO_ITEM)
            return;

    //  Can't steal mail!

        // LD_addr_A(wNamedObjectIndex);
        itm = *hl;
        // LD_D_A;
        // FARCALL(aItemIsMail);
        // RET_C ;
        if(ItemIsMail_Conv(itm))
            return;

        // LD_A_addr(wEffectFailed);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wEffectFailed)
            return;

    //  If the enemy steals your item,
    //  it's gone for good if you don't get it back.

        // CALL(aBattleCommand_Thief_playeritem);
        BattleCommand_Thief_playeritem(&de, &hl);
        // XOR_A_A;
        // LD_hl_A;
        *hl = NO_ITEM;
        // LD_de_A;
        *de = NO_ITEM;

        // CALL(aBattleCommand_Thief_enemyitem);
        BattleCommand_Thief_enemyitem(&de, &hl);
        // LD_A_addr(wNamedObjectIndex);
        // LD_hl_A;
        *hl = itm;
        // LD_de_A;
        *de = itm;
    }

// stole:
    // CALL(aGetItemName);
    GetItemName_Conv2(itm);
    // LD_HL(mStoleText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(StoleText);
}
