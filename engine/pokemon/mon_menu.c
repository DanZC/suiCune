#include "../../constants.h"
#include "mon_menu.h"
#include "tempmon.h"
#include "mon_stats.h"
#include "types.h"
#include "print_move_description.h"
#include "../../home/names.h"
#include "../../home/copy_name.h"
#include "../../home/menu.h"
#include "../../home/item.h"
#include "../../home/gfx.h"
#include "../../home/copy.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/text.h"
#include "../../home/print_text.h"
#include "../../home/pokemon.h"
#include "../gfx/load_font.h"
#include "../gfx/sprites.h"
#include "../gfx/mon_icons.h"
#include "../items/items.h"
#include "../items/buy_sell_toss.h"
#include "../../data/text/common.h"
#include "../../data/moves/moves.h"

void HasNoItems(void){
    LD_A_addr(wNumItems);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wNumKeyItems);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wNumBalls);
    AND_A_A;
    RET_NZ ;
    LD_HL(wTMsHMs);
    LD_B(NUM_TMS + NUM_HMS);

loop:
    LD_A_hli;
    AND_A_A;
    IF_NZ goto done;
    DEC_B;
    IF_NZ goto loop;
    SCF;
    RET;

done:
    AND_A_A;
    RET;

}

bool HasNoItems_Conv(void){
    // LD_A_addr(wNumItems);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wNumItems != 0)
        return false;
    // LD_A_addr(wNumKeyItems);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wNumKeyItems != 0)
        return false;
    // LD_A_addr(wNumBalls);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wNumBalls != 0)
        return false;
    // LD_HL(wTMsHMs);
    uint8_t* hl = wram->wTMsHMs;
    // LD_B(NUM_TMS + NUM_HMS);
    uint8_t b = NUM_TMS + NUM_HMS;

    do {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_NZ goto done;
        if(*(hl++) != 0) {
        // done:
            // AND_A_A;
            // RET;
            return false;
        }
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // SCF;
    // RET;
    return true;
}

void TossItemFromPC(void){
    PUSH_DE;
    CALL(aPartyMonItemName);
    FARCALL(av_CheckTossableItem);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto key_item;
    LD_HL(mTossItemFromPC_ItemsTossOutHowManyText);
    CALL(aMenuTextbox);
    FARCALL(aSelectQuantityToToss);
    PUSH_AF;
    CALL(aCloseWindow);
    CALL(aExitMenu);
    POP_AF;
    IF_C goto quit;
    LD_HL(mTossItemFromPC_ItemsThrowAwayText);
    CALL(aMenuTextbox);
    CALL(aYesNoBox);
    PUSH_AF;
    CALL(aExitMenu);
    POP_AF;
    IF_C goto quit;
    POP_HL;
    LD_A_addr(wCurItemQuantity);
    CALL(aTossItem);
    CALL(aPartyMonItemName);
    LD_HL(mTossItemFromPC_ItemsDiscardedText);
    CALL(aMenuTextbox);
    CALL(aExitMenu);
    AND_A_A;
    RET;


key_item:
    CALL(aTossItemFromPC_CantToss);

quit:
    POP_HL;
    SCF;
    RET;


ItemsTossOutHowManyText:
    //text_far ['_ItemsTossOutHowManyText']
    //text_end ['?']


ItemsThrowAwayText:
    //text_far ['_ItemsThrowAwayText']
    //text_end ['?']


ItemsDiscardedText:
    //text_far ['_ItemsDiscardedText']
    //text_end ['?']


CantToss:
    LD_HL(mTossItemFromPC_ItemsTooImportantText);
    CALL(aMenuTextboxBackup);
    RET;


ItemsTooImportantText:
    //text_far ['_ItemsTooImportantText']
    //text_end ['?']

    return CantUseItem();
}

static void TossItemFromPC_CantToss(void) {
    static const txt_cmd_s ItemsTooImportantText[] = {
        text_far(v_ItemsTooImportantText)
        text_end
    };
    // LD_HL(mTossItemFromPC_ItemsTooImportantText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(ItemsTooImportantText);
    // RET;
}

bool TossItemFromPC_Conv(item_pocket_s* de){
    static const txt_cmd_s ItemsTossOutHowManyText[] = {
        text_far(v_ItemsTossOutHowManyText)
        text_end
    };

    static const txt_cmd_s ItemsThrowAwayText[] = {
        text_far(v_ItemsThrowAwayText)
        text_end
    };

    static const txt_cmd_s ItemsDiscardedText[] = {
        text_far(v_ItemsDiscardedText)
        text_end
    };
    // PUSH_DE;
    // CALL(aPartyMonItemName);
    PartyMonItemName_Conv(wram->wCurItem);
    // FARCALL(av_CheckTossableItem);
    // LD_A_addr(wItemAttributeValue);
    // AND_A_A;
    // IF_NZ goto key_item;
    if(!v_CheckTossableItem_Conv(wram->wCurItem)) {
    // key_item:
        // CALL(aTossItemFromPC_CantToss);
        TossItemFromPC_CantToss();

    // quit:
        // POP_HL;
        // SCF;
        // RET;
        return true;
    }
    // LD_HL(mTossItemFromPC_ItemsTossOutHowManyText);
    // CALL(aMenuTextbox);
    MenuTextbox_Conv(ItemsTossOutHowManyText);
    // FARCALL(aSelectQuantityToToss);
    bool quit = SelectQuantityToToss();
    // PUSH_AF;
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // POP_AF;
    // IF_C goto quit;
    if(quit)
        return true;
    // LD_HL(mTossItemFromPC_ItemsThrowAwayText);
    // CALL(aMenuTextbox);
    MenuTextbox_Conv(ItemsThrowAwayText);
    // CALL(aYesNoBox);
    bool yes = YesNoBox_Conv();
    // PUSH_AF;
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // POP_AF;
    // IF_C goto quit;
    if(yes) {
        // POP_HL;
        // LD_A_addr(wCurItemQuantity);
        // CALL(aTossItem);
        TossItem_Conv(de, wram->wCurItem);
        // CALL(aPartyMonItemName);
        PartyMonItemName_Conv(wram->wCurItem);
        // LD_HL(mTossItemFromPC_ItemsDiscardedText);
        // CALL(aMenuTextbox);
        MenuTextbox_Conv(ItemsDiscardedText);
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // AND_A_A;
        // RET;
        return false;
    }
    else {
    // key_item:
        // CALL(aTossItemFromPC_CantToss);

    // quit:
        // POP_HL;
        // SCF;
        // RET;
        return true;
    }
}

void CantUseItem(void){
    // LD_HL(mItemsOakWarningText);
    // CALL(aMenuTextboxWaitButton);
    // RET;
    MenuTextboxWaitButton(ItemsOakWarningText);
}

const txt_cmd_s ItemsOakWarningText[] = {
    text_far(v_ItemsOakWarningText)
    text_end
};

void PartyMonItemName(void){
    LD_A_addr(wCurItem);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    CALL(aCopyName1);
    RET;

}

void PartyMonItemName_Conv(item_t item){
    // LD_A_addr(wCurItem);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    // CALL(aCopyName1);
    CopyName1_Conv2(GetItemName_Conv2(item));
    // RET;
}

void CancelPokemonAction(void){
    FARCALL(aInitPartyMenuWithCancel);
    FARCALL(aUnfreezeMonIcons);
    LD_A(1);
    RET;

}

void PokemonActionSubmenu(void){
    hlcoord(1, 15, wTilemap);
    LD_BC((2 << 8) | 18);
    CALL(aClearBox);
    FARCALL(aMonSubmenu);
    CALL(aGetCurNickname);
    LD_A_addr(wMenuSelection);
    LD_HL(mPokemonActionSubmenu_Actions);
    LD_DE(3);
    CALL(aIsInArray);
    IF_NC goto nothing;

    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


nothing:
    LD_A(0);
    RET;


Actions:
    //dbw ['MONMENUITEM_CUT', 'MonMenu_Cut']
    //dbw ['MONMENUITEM_FLY', 'MonMenu_Fly']
    //dbw ['MONMENUITEM_SURF', 'MonMenu_Surf']
    //dbw ['MONMENUITEM_STRENGTH', 'MonMenu_Strength']
    //dbw ['MONMENUITEM_FLASH', 'MonMenu_Flash']
    //dbw ['MONMENUITEM_WHIRLPOOL', 'MonMenu_Whirlpool']
    //dbw ['MONMENUITEM_DIG', 'MonMenu_Dig']
    //dbw ['MONMENUITEM_TELEPORT', 'MonMenu_Teleport']
    //dbw ['MONMENUITEM_SOFTBOILED', 'MonMenu_Softboiled_MilkDrink']
    //dbw ['MONMENUITEM_MILKDRINK', 'MonMenu_Softboiled_MilkDrink']
    //dbw ['MONMENUITEM_HEADBUTT', 'MonMenu_Headbutt']
    //dbw ['MONMENUITEM_WATERFALL', 'MonMenu_Waterfall']
    //dbw ['MONMENUITEM_ROCKSMASH', 'MonMenu_RockSmash']
    //dbw ['MONMENUITEM_SWEETSCENT', 'MonMenu_SweetScent']
    //dbw ['MONMENUITEM_STATS', 'OpenPartyStats']
    //dbw ['MONMENUITEM_SWITCH', 'SwitchPartyMons']
    //dbw ['MONMENUITEM_ITEM', 'GiveTakePartyMonItem']
    //dbw ['MONMENUITEM_CANCEL', 'CancelPokemonAction']
    //dbw ['MONMENUITEM_MOVE', 'ManagePokemonMoves']
    //dbw ['MONMENUITEM_MAIL', 'MonMailAction']

    return SwitchPartyMons();
}

void SwitchPartyMons(void){
//  Don't try if there's nothing to switch!
    LD_A_addr(wPartyCount);
    CP_A(2);
    IF_C goto DontSwitch;

    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_addr_A(wSwitchMon);

    FARCALL(aHoldSwitchmonIcon);
    FARCALL(aInitPartyMenuNoCancel);

    LD_A(PARTYMENUACTION_MOVE);
    LD_addr_A(wPartyMenuActionText);
    FARCALL(aWritePartyMenuTilemap);
    FARCALL(aPrintPartyMenuText);

    hlcoord(0, 1, wTilemap);
    LD_BC(SCREEN_WIDTH * 2);
    LD_A_addr(wSwitchMon);
    DEC_A;
    CALL(aAddNTimes);
    LD_hl(0xec);
    CALL(aWaitBGMap);
    CALL(aSetPalettes);
    CALL(aDelayFrame);

    FARCALL(aPartyMenuSelect);
    BIT_B(1);
    IF_C goto DontSwitch;

    FARCALL(av_SwitchPartyMons);

    XOR_A_A;
    LD_addr_A(wPartyMenuActionText);

    FARCALL(aLoadPartyMenuGFX);
    FARCALL(aInitPartyMenuWithCancel);
    FARCALL(aInitPartyMenuGFX);

    LD_A(1);
    RET;


DontSwitch:
    XOR_A_A;
    LD_addr_A(wPartyMenuActionText);
    CALL(aCancelPokemonAction);
    RET;

}

void GiveTakePartyMonItem(void){
//  Eggs can't hold items!
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto cancel;

    LD_HL(mGiveTakeItemMenuData);
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    CALL(aExitMenu);
    IF_C goto cancel;

    CALL(aGetCurNickname);
    LD_HL(wStringBuffer1);
    LD_DE(wMonOrItemNameBuffer);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wMenuCursorY);
    CP_A(1);
    IF_NZ goto take;

    CALL(aLoadStandardMenuHeader);
    CALL(aClearPalettes);
    CALL(aGiveTakePartyMonItem_GiveItem);
    CALL(aClearPalettes);
    CALL(aLoadFontsBattleExtra);
    CALL(aExitMenu);
    LD_A(0);
    RET;


take:
    CALL(aTakePartyItem);
    LD_A(3);
    RET;


cancel:
    LD_A(3);
    RET;


GiveItem:
    FARCALL(aDepositSellInitPackBuffers);


loop:
    FARCALL(aDepositSellPack);

    LD_A_addr(wPackUsedItem);
    AND_A_A;
    IF_Z goto quit;

    LD_A_addr(wCurPocket);
    CP_A(KEY_ITEM_POCKET);
    IF_Z goto next;

    CALL(aCheckTossableItem);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto next;

    CALL(aTryGiveItemToPartymon);
    goto quit;


next:
    LD_HL(mItemCantHeldText);
    CALL(aMenuTextboxBackup);
    goto loop;


quit:
    RET;

}

void TryGiveItemToPartymon(void){
    CALL(aSpeechTextbox);
    CALL(aPartyMonItemName);
    CALL(aGetPartyItemLocation);
    LD_A_hl;
    AND_A_A;
    IF_Z goto give_item_to_mon;

    PUSH_HL;
    LD_D_A;
    FARCALL(aItemIsMail);
    POP_HL;
    IF_C goto please_remove_mail;
    LD_A_hl;
    goto already_holding_item;


give_item_to_mon:
    CALL(aGiveItemToPokemon);
    LD_HL(mPokemonHoldItemText);
    CALL(aMenuTextboxBackup);
    CALL(aGivePartyItem);
    RET;


please_remove_mail:
    LD_HL(mPokemonRemoveMailText);
    CALL(aMenuTextboxBackup);
    RET;


already_holding_item:
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    LD_HL(mPokemonAskSwapItemText);
    CALL(aStartMenuYesNo);
    IF_C goto abort;

    CALL(aGiveItemToPokemon);
    LD_A_addr(wNamedObjectIndex);
    PUSH_AF;
    LD_A_addr(wCurItem);
    LD_addr_A(wNamedObjectIndex);
    POP_AF;
    LD_addr_A(wCurItem);
    CALL(aReceiveItemFromPokemon);
    IF_NC goto bag_full;

    LD_HL(mPokemonSwapItemText);
    CALL(aMenuTextboxBackup);
    LD_A_addr(wNamedObjectIndex);
    LD_addr_A(wCurItem);
    CALL(aGivePartyItem);
    RET;


bag_full:
    LD_A_addr(wNamedObjectIndex);
    LD_addr_A(wCurItem);
    CALL(aReceiveItemFromPokemon);
    LD_HL(mItemStorageFullText);
    CALL(aMenuTextboxBackup);


abort:
    RET;

}

void GivePartyItem(void){
    CALL(aGetPartyItemLocation);
    LD_A_addr(wCurItem);
    LD_hl_A;
    LD_D_A;
    FARCALL(aItemIsMail);
    IF_NC goto done;
    CALL(aComposeMailMessage);


done:
    RET;

}

void TakePartyItem(void){
    CALL(aSpeechTextbox);
    CALL(aGetPartyItemLocation);
    LD_A_hl;
    AND_A_A;
    IF_Z goto not_holding_item;

    LD_addr_A(wCurItem);
    CALL(aReceiveItemFromPokemon);
    IF_NC goto item_storage_full;

    FARCALL(aItemIsMail);
    CALL(aGetPartyItemLocation);
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    LD_hl(NO_ITEM);
    CALL(aGetItemName);
    LD_HL(mPokemonTookItemText);
    CALL(aMenuTextboxBackup);
    goto done;


not_holding_item:
    LD_HL(mPokemonNotHoldingText);
    CALL(aMenuTextboxBackup);
    goto done;


item_storage_full:
    LD_HL(mItemStorageFullText);
    CALL(aMenuTextboxBackup);


done:
    RET;

}

void GiveTakeItemMenuData(void){
    //db ['MENU_SPRITE_ANIMS | MENU_BACKUP_TILES'];  // flags
    //menu_coords ['12', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.Items'];
    //db ['1'];  // default option


Items:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['2'];  // # items
    //db ['"GIVE@"'];
    //db ['"TAKE@"'];

    return PokemonSwapItemText();
}

void PokemonSwapItemText(void){
    //text_far ['_PokemonSwapItemText']
    //text_end ['?']

    return PokemonHoldItemText();
}

void PokemonHoldItemText(void){
    //text_far ['_PokemonHoldItemText']
    //text_end ['?']

    return PokemonRemoveMailText();
}

void PokemonRemoveMailText(void){
    //text_far ['_PokemonRemoveMailText']
    //text_end ['?']

    return PokemonNotHoldingText();
}

void PokemonNotHoldingText(void){
    //text_far ['_PokemonNotHoldingText']
    //text_end ['?']

    return ItemStorageFullText();
}

void ItemStorageFullText(void){
    //text_far ['_ItemStorageFullText']
    //text_end ['?']

    return PokemonTookItemText();
}

void PokemonTookItemText(void){
    //text_far ['_PokemonTookItemText']
    //text_end ['?']

    return PokemonAskSwapItemText();
}

void PokemonAskSwapItemText(void){
    //text_far ['_PokemonAskSwapItemText']
    //text_end ['?']

    return ItemCantHeldText();
}

void ItemCantHeldText(void){
    //text_far ['_ItemCantHeldText']
    //text_end ['?']

    return GetPartyItemLocation();
}

void GetPartyItemLocation(void){
    PUSH_AF;
    LD_A(MON_ITEM);
    CALL(aGetPartyParamLocation);
    POP_AF;
    RET;

}

void ReceiveItemFromPokemon(void){
    LD_A(1);
    LD_addr_A(wItemQuantityChange);
    LD_HL(wNumItems);
    JP(mReceiveItem);

}

void GiveItemToPokemon(void){
    LD_A(1);
    LD_addr_A(wItemQuantityChange);
    LD_HL(wNumItems);
    JP(mTossItem);

}

void StartMenuYesNo(void){
    CALL(aMenuTextbox);
    CALL(aYesNoBox);
    JP(mExitMenu);

}

bool StartMenuYesNo_Conv(const struct TextCmd* hl){
    // CALL(aMenuTextbox);
    MenuTextbox_Conv(hl);
    // CALL(aYesNoBox);
    bool res = YesNoBox_Conv();
    // JP(mExitMenu);
    ExitMenu_Conv2();
    return res;
}

void ComposeMailMessage(void){
    LD_DE(wTempMailMessage);
    FARCALL(av_ComposeMailMessage);
    LD_HL(wPlayerName);
    LD_DE(wTempMailAuthor);
    LD_BC(NAME_LENGTH - 1);
    CALL(aCopyBytes);
    LD_HL(wPlayerID);
    LD_BC(2);
    CALL(aCopyBytes);
    LD_A_addr(wCurPartySpecies);
    LD_de_A;
    INC_DE;
    LD_A_addr(wCurItem);
    LD_de_A;
    LD_A_addr(wCurPartyMon);
    LD_HL(sPartyMail);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_HL(wTempMail);
    LD_BC(MAIL_STRUCT_LENGTH);
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void MonMailAction(void){
//  If in the time capsule or trade center,
//  selecting the mail only allows you to
//  read the mail.
    LD_A_addr(wLinkMode);
    CP_A(LINK_TIMECAPSULE);
    IF_Z goto read;
    CP_A(LINK_TRADECENTER);
    IF_Z goto read;

//  Show the READ/TAKE/QUIT menu.
    LD_HL(mMonMailAction_MenuHeader);
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    CALL(aExitMenu);

//  Interpret the menu.
    JP_C (mMonMailAction_done);
    LD_A_addr(wMenuCursorY);
    CP_A(0x1);
    IF_Z goto read;
    CP_A(0x2);
    IF_Z goto take;
    JP(mMonMailAction_done);


read:
    FARCALL(aReadPartyMonMail);
    LD_A(0x0);
    RET;


take:
    LD_HL(mMonMailAction_MailAskSendToPCText);
    CALL(aStartMenuYesNo);
    IF_C goto RemoveMailToBag;
    LD_A_addr(wCurPartyMon);
    LD_B_A;
    FARCALL(aSendMailToPC);
    IF_C goto MailboxFull;
    LD_HL(mMonMailAction_MailSentToPCText);
    CALL(aMenuTextboxBackup);
    goto done;


MailboxFull:
    LD_HL(mMonMailAction_MailboxFullText);
    CALL(aMenuTextboxBackup);
    goto done;


RemoveMailToBag:
    LD_HL(mMonMailAction_MailLoseMessageText);
    CALL(aStartMenuYesNo);
    IF_C goto done;
    CALL(aGetPartyItemLocation);
    LD_A_hl;
    LD_addr_A(wCurItem);
    CALL(aReceiveItemFromPokemon);
    IF_NC goto BagIsFull;
    CALL(aGetPartyItemLocation);
    LD_hl(0x0);
    CALL(aGetCurNickname);
    LD_HL(mMonMailAction_MailDetachedText);
    CALL(aMenuTextboxBackup);
    goto done;


BagIsFull:
    LD_HL(mMonMailAction_MailNoSpaceText);
    CALL(aMenuTextboxBackup);
    goto done;


done:
    LD_A(0x3);
    RET;


MenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['12', '10', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['3'];  // items
    //db ['"READ@"'];
    //db ['"TAKE@"'];
    //db ['"QUIT@"'];


MailLoseMessageText:
    //text_far ['_MailLoseMessageText']
    //text_end ['?']


MailDetachedText:
    //text_far ['_MailDetachedText']
    //text_end ['?']


MailNoSpaceText:
    //text_far ['_MailNoSpaceText']
    //text_end ['?']


MailAskSendToPCText:
    //text_far ['_MailAskSendToPCText']
    //text_end ['?']


MailboxFullText:
    //text_far ['_MailboxFullText']
    //text_end ['?']


MailSentToPCText:
    //text_far ['_MailSentToPCText']
    //text_end ['?']

    return OpenPartyStats();
}

void OpenPartyStats(void){
    CALL(aLoadStandardMenuHeader);
    CALL(aClearSprites);
//  PartyMon
    XOR_A_A;
    LD_addr_A(wMonType);
    CALL(aLowVolume);
    PREDEF(pStatsScreenInit);
    CALL(aMaxVolume);
    CALL(aCall_ExitMenu);
    LD_A(0);
    RET;

}

void MonMenu_Cut(void){
    FARCALL(aCutFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x1);
    IF_NZ goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_Fly(void){
    FARCALL(aFlyFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x2);
    IF_Z goto Fail;
    CP_A(0x0);
    IF_Z goto Error;
    FARCALL(aStubbedTrainerRankings_Fly);
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;


Error:
    LD_A(0x0);
    RET;


NoReload:
//   //  unreferenced
    LD_A(0x1);
    RET;

}

void MonMenu_Flash(void){
    FARCALL(aFlashFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x1);
    IF_NZ goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_Strength(void){
    FARCALL(aStrengthFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x1);
    IF_NZ goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_Whirlpool(void){
    FARCALL(aWhirlpoolFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x1);
    IF_NZ goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_Waterfall(void){
    FARCALL(aWaterfallFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x1);
    IF_NZ goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_Teleport(void){
    FARCALL(aTeleportFunction);
    LD_A_addr(wFieldMoveSucceeded);
    AND_A_A;
    IF_Z goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_Surf(void){
    FARCALL(aSurfFunction);
    LD_A_addr(wFieldMoveSucceeded);
    AND_A_A;
    IF_Z goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_Dig(void){
    FARCALL(aDigFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x1);
    IF_NZ goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_Softboiled_MilkDrink(void){
    CALL(aMonMenu_Softboiled_MilkDrink_CheckMonHasEnoughHP);
    IF_NC goto NotEnoughHP;
    FARCALL(aSoftboiled_MilkDrinkFunction);
    goto finish;


NotEnoughHP:
    LD_HL(mMonMenu_Softboiled_MilkDrink_PokemonNotEnoughHPText);
    CALL(aPrintText);


finish:
    XOR_A_A;
    LD_addr_A(wPartyMenuActionText);
    LD_A(0x3);
    RET;


PokemonNotEnoughHPText:
    //text_far ['_PokemonNotEnoughHPText']
    //text_end ['?']


CheckMonHasEnoughHP:
//  Need to have at least (MaxHP / 5) HP left.
    LD_A(MON_MAXHP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LDH_addr_A(hDividend + 0);
    LD_A_hl;
    LDH_addr_A(hDividend + 1);
    LD_A(5);
    LDH_addr_A(hDivisor);
    LD_B(2);
    CALL(aDivide);
    LD_A(MON_HP + 1);
    CALL(aGetPartyParamLocation);
    LDH_A_addr(hQuotient + 3);
    SUB_A_hl;
    DEC_HL;
    LDH_A_addr(hQuotient + 2);
    SBC_A_hl;
    RET;

}

void MonMenu_Headbutt(void){
    FARCALL(aHeadbuttFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x1);
    IF_NZ goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_RockSmash(void){
    FARCALL(aRockSmashFunction);
    LD_A_addr(wFieldMoveSucceeded);
    CP_A(0x1);
    IF_NZ goto Fail;
    LD_B(0x4);
    LD_A(0x2);
    RET;


Fail:
    LD_A(0x3);
    RET;

}

void MonMenu_SweetScent(void){
    FARCALL(aSweetScentFromMenu);
    LD_B(0x4);
    LD_A(0x2);
    RET;

}

void ChooseMoveToDelete(void){
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    CALL(aLoadFontsBattleExtra);
    CALL(aChooseMoveToDelete_ChooseMoveToDelete);
    POP_BC;
    LD_A_B;
    LD_addr_A(wOptions);
    PUSH_AF;
    CALL(aClearBGPalettes);
    POP_AF;
    RET;


ChooseMoveToDelete:
    CALL(aSetUpMoveScreenBG);
    LD_DE(mDeleteMoveScreen2DMenuData);
    CALL(aLoad2DMenuData);
    CALL(aSetUpMoveList);
    LD_HL(w2DMenuFlags1);
    SET_hl(6);
    goto enter_loop;


loop:
    CALL(aScrollingMenuJoypad);
    BIT_A(B_BUTTON_F);
    JP_NZ (mChooseMoveToDelete_b_button);
    BIT_A(A_BUTTON_F);
    JP_NZ (mChooseMoveToDelete_a_button);


enter_loop:
    CALL(aPrepareToPlaceMoveData);
    CALL(aPlaceMoveData);
    JP(mChooseMoveToDelete_loop);


a_button:
    AND_A_A;
    goto finish;


b_button:
    SCF;


finish:
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wSwitchMon);
    LD_HL(w2DMenuFlags1);
    RES_hl(6);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    POP_AF;
    RET;

}

static bool ChooseMoveToDelete_ChooseMoveToDelete(void){
    // CALL(aSetUpMoveScreenBG);
    SetUpMoveScreenBG();
    // LD_DE(mDeleteMoveScreen2DMenuData);
    // CALL(aLoad2DMenuData);
    Load2DMenuData_Conv(DeleteMoveScreen2DMenuData);
    // CALL(aSetUpMoveList);
    SetUpMoveList();
    // LD_HL(w2DMenuFlags1);
    // SET_hl(6);
    bit_set(wram->w2DMenuFlags1, 6);
    // goto enter_loop;

    bool quit;
    while(1) {
    // enter_loop:
        // CALL(aPrepareToPlaceMoveData);
        PrepareToPlaceMoveData();
        // CALL(aPlaceMoveData);
        PlaceMoveData();
        // JP(mChooseMoveToDelete_loop);

    // loop:
        // CALL(aScrollingMenuJoypad);
        uint8_t pad = ScrollingMenuJoypad_Conv();
        // BIT_A(B_BUTTON_F);
        // JP_NZ (mChooseMoveToDelete_b_button);
        if(bit_test(pad, B_BUTTON_F)) {
        // b_button:
            // SCF;
            quit = true;
            break;
        }
        // BIT_A(A_BUTTON_F);
        // JP_NZ (mChooseMoveToDelete_a_button);
        if(bit_test(pad, A_BUTTON_F)) {
        // a_button:
            // AND_A_A;
            // goto finish;
            quit = false;
            break;
        }
    }

// finish:
    // PUSH_AF;
    // XOR_A_A;
    // LD_addr_A(wSwitchMon);
    wram->wSwitchMon = 0;
    // LD_HL(w2DMenuFlags1);
    // RES_hl(6);
    bit_reset(wram->w2DMenuFlags1, 6);
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // POP_AF;
    // RET;
    return quit;
}

u8_flag_s ChooseMoveToDelete_Conv(void){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();
    // CALL(aChooseMoveToDelete_ChooseMoveToDelete);
    bool quit = ChooseMoveToDelete_ChooseMoveToDelete();
    // POP_BC;
    // LD_A_B;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // PUSH_AF;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // POP_AF;
    // RET;
    return u8_flag(wram->wMenuCursorY, quit);
}

const uint8_t DeleteMoveScreen2DMenuData[] = {
    3, 1,  // cursor start y, x
    3, 1,  // rows, columns
    0x40, 0x00,  // flags
    (2 << 4) | 0,  // cursor offset
    D_UP | D_DOWN | A_BUTTON | B_BUTTON,  // accepted buttons
};

void ManagePokemonMoves(void){
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto egg;
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(NO_TEXT_SCROLL);
    CALL(aMoveScreenLoop);
    POP_AF;
    LD_addr_A(wOptions);
    CALL(aClearBGPalettes);


egg:
    LD_A(0x0);
    RET;

}

void MoveScreenLoop(void){
    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_addr_A(wPartyMenuCursor);
    CALL(aSetUpMoveScreenBG);
    CALL(aPlaceMoveScreenArrows);
    LD_DE(mMoveScreen2DMenuData);
    CALL(aLoad2DMenuData);

loop:
    CALL(aSetUpMoveList);
    LD_HL(w2DMenuFlags1);
    SET_hl(6);
    goto skip_joy;


joy_loop:
    CALL(aScrollingMenuJoypad);
    BIT_A(1);
    JP_NZ (mMoveScreenLoop_b_button);
    BIT_A(0);
    JP_NZ (mMoveScreenLoop_a_button);
    BIT_A(4);
    JP_NZ (mMoveScreenLoop_d_right);
    BIT_A(5);
    JP_NZ (mMoveScreenLoop_d_left);


skip_joy:
    CALL(aPrepareToPlaceMoveData);
    LD_A_addr(wSwappingMove);
    AND_A_A;
    IF_NZ goto moving_move;
    CALL(aPlaceMoveData);
    JP(mMoveScreenLoop_joy_loop);


moving_move:
    LD_A(0x7f);
    hlcoord(1, 11, wTilemap);
    LD_BC(5);
    CALL(aByteFill);
    hlcoord(1, 12, wTilemap);
    LD_BC((5 << 8) | (SCREEN_WIDTH - 2));
    CALL(aClearBox);
    hlcoord(1, 12, wTilemap);
    LD_DE(mString_MoveWhere);
    CALL(aPlaceString);
    JP(mMoveScreenLoop_joy_loop);

b_button:
    CALL(aPlayClickSFX);
    CALL(aWaitSFX);
    LD_A_addr(wSwappingMove);
    AND_A_A;
    JP_Z (mMoveScreenLoop_exit);

    LD_A_addr(wSwappingMove);
    LD_addr_A(wMenuCursorY);
    XOR_A_A;
    LD_addr_A(wSwappingMove);
    hlcoord(1, 2, wTilemap);
    LD_BC((8 << 8) | (SCREEN_WIDTH - 2));
    CALL(aClearBox);
    JP(mMoveScreenLoop_loop);


d_right:
    LD_A_addr(wSwappingMove);
    AND_A_A;
    JP_NZ (mMoveScreenLoop_joy_loop);

    LD_A_addr(wCurPartyMon);
    LD_B_A;
    PUSH_BC;
    CALL(aMoveScreenLoop_cycle_right);
    POP_BC;
    LD_A_addr(wCurPartyMon);
    CP_A_B;
    JP_Z (mMoveScreenLoop_joy_loop);
    JP(mMoveScreenLoop);


d_left:
    LD_A_addr(wSwappingMove);
    AND_A_A;
    JP_NZ (mMoveScreenLoop_joy_loop);
    LD_A_addr(wCurPartyMon);
    LD_B_A;
    PUSH_BC;
    CALL(aMoveScreenLoop_cycle_left);
    POP_BC;
    LD_A_addr(wCurPartyMon);
    CP_A_B;
    JP_Z (mMoveScreenLoop_joy_loop);
    JP(mMoveScreenLoop);


cycle_right:
    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_addr_A(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(-1);
    IF_Z goto cycle_left;
    CP_A(EGG);
    RET_NZ ;
    goto cycle_right;


cycle_left:
    LD_A_addr(wCurPartyMon);
    AND_A_A;
    RET_Z ;

cycle_left_loop:
    LD_A_addr(wCurPartyMon);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(EGG);
    RET_NZ ;
    LD_A_addr(wCurPartyMon);
    AND_A_A;
    IF_Z goto cycle_right;
    goto cycle_left_loop;


a_button:
    CALL(aPlayClickSFX);
    CALL(aWaitSFX);
    LD_A_addr(wSwappingMove);
    AND_A_A;
    IF_NZ goto place_move;
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wSwappingMove);
    CALL(aPlaceHollowCursor);
    JP(mMoveScreenLoop_moving_move);


place_move:
    LD_HL(wPartyMon1Moves);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    PUSH_HL;
    CALL(aMoveScreenLoop_copy_move);
    POP_HL;
    LD_BC(wPartyMon1PP - wPartyMon1Moves);
    ADD_HL_BC;
    CALL(aMoveScreenLoop_copy_move);
    LD_A_addr(wBattleMode);
    IF_Z goto swap_moves;
    LD_HL(wBattleMonMoves);
    LD_BC(wBattleMonStructEnd - wBattleMon);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    PUSH_HL;
    CALL(aMoveScreenLoop_copy_move);
    POP_HL;
    LD_BC(wBattleMonPP - wBattleMonMoves);
    ADD_HL_BC;
    CALL(aMoveScreenLoop_copy_move);


swap_moves:
    LD_DE(SFX_SWITCH_POKEMON);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    LD_DE(SFX_SWITCH_POKEMON);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    hlcoord(1, 2, wTilemap);
    LD_BC((8 << 8) | 18);
    CALL(aClearBox);
    hlcoord(10, 10, wTilemap);
    LD_BC((1 << 8) | 9);
    CALL(aClearBox);
    JP(mMoveScreenLoop_loop);


copy_move:
    PUSH_HL;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_A_addr(wSwappingMove);
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    LD_B_hl;
    LD_hl_A;
    LD_A_B;
    LD_de_A;
    RET;


exit:
    XOR_A_A;
    LD_addr_A(wSwappingMove);
    LD_HL(w2DMenuFlags1);
    RES_hl(6);
    CALL(aClearSprites);
    JP(mClearTilemap);

}

void MoveScreen2DMenuData(void){
    //db ['3', '1'];  // cursor start y, x
    //db ['3', '1'];  // rows, columns
    //db ['0x40', '0x00'];  // flags
    //dn ['2', '0'];  // cursor offsets
    //db ['D_UP | D_DOWN | D_LEFT | D_RIGHT | A_BUTTON | B_BUTTON'];  // accepted buttons

    return String_MoveWhere();
}

void String_MoveWhere(void){
    //db ['"Where?@"'];

    return SetUpMoveScreenBG();
}

void SetUpMoveScreenBG(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // FARCALL(aLoadStatsScreenPageTilesGFX);
    LoadStatsScreenPageTilesGFX_Conv();
    // FARCALL(aClearSpriteAnims2);
    ClearSpriteAnims2_Conv();
    // LD_A_addr(wCurPartyMon);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPartySpecies);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wTempIconSpecies);
    wram->wTempIconSpecies = wram->wPartySpecies[wram->wCurPartyMon];
    // LD_E(MONICON_MOVES);
    // FARCALL(aLoadMenuMonIcon);
    LoadMenuMonIcon_Conv(MONICON_MOVES);
    // hlcoord(0, 1, wTilemap);
    // LD_B(9);
    // LD_C(18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 1, wram->wTilemap), 9, 18);
    // hlcoord(0, 11, wTilemap);
    // LD_B(5);
    // LD_C(18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 11, wram->wTilemap), 5, 18);
    // hlcoord(2, 0, wTilemap);
    // LD_BC((2 << 8) | 3);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(2, 0, wram->wTilemap), 3, 2);
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = 0;
    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wCurPartyMon);
    // CALL(aGetNickname);
    // hlcoord(5, 1, wTilemap);
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = wram->wPartyMonNickname[wram->wCurPartyMon], .hl = coord(5, 1, wram->wTilemap)};
    PlaceString_Conv(&st, st.hl);
    // PUSH_BC;
    // FARCALL(aCopyMonToTempMon);
    CopyMonToTempMon_Conv();
    // POP_HL;
    // CALL(aPrintLevel);
    PrintLevel_Conv(st.bc, wram->wTempMon.mon.level);
    // LD_HL(wPlayerHPPal);
    // CALL(aSetHPPal);
    uint16_t bc = ReverseEndian16(wram->wPartyMon[wram->wCurPartyMon].HP);
    uint16_t de = ReverseEndian16(wram->wPartyMon[wram->wCurPartyMon].maxHP);
    uint8_t e = bc * (6 * 8) / de;
    SetHPPal_Conv(&wram->wPlayerHPPal, e);
    // LD_B(SCGB_MOVE_LIST);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_MOVE_LIST);
    // hlcoord(16, 0, wTilemap);
    // LD_BC((1 << 8) | 3);
    // JP(mClearBox);
    return ClearBox_Conv2(coord(16, 0, wram->wTilemap), 3, 1);
}

void SetUpMoveList(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // LD_addr_A(wSwappingMove);
    wram->wSwappingMove = 0;
    // LD_addr_A(wMonType);
    wram->wMonType = 0;
    // PREDEF(pCopyMonToTempMon);
    // LD_HL(wTempMonMoves);
    // LD_DE(wListMoves_MoveIndicesBuffer);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wListMoves_MoveIndicesBuffer, wram->wTempMon.mon.moves, sizeof(wram->wTempMon.mon.moves));
    // LD_A(SCREEN_WIDTH * 2);
    // LD_addr_A(wListMovesLineSpacing);
    wram->wListMovesLineSpacing = SCREEN_WIDTH * 2;
    // hlcoord(2, 3, wTilemap);
    // PREDEF(pListMoves);
    ListMoves_Conv(coord(2, 3, wram->wTilemap));
    // hlcoord(10, 4, wTilemap);
    // PREDEF(pListMovePP);
    ListMovePP_Conv(coord(10, 4, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LD_A_addr(wNumMoves);
    // INC_A;
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wNumMoves + 1;
    // hlcoord(0, 11, wTilemap);
    // LD_B(5);
    // LD_C(18);
    // JP(mTextbox);
    return Textbox_Conv2(coord(0, 11, wram->wTilemap), 5, 18);
}

void PrepareToPlaceMoveData(void){
    // LD_HL(wPartyMon1Moves);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wPartyMon[wram->wCurPartyMon].mon.moves[wram->wMenuCursorY - 1]; // weird. is this correct?
    // hlcoord(1, 12, wTilemap);
    // LD_BC((5 << 8) | 18);
    // JP(mClearBox);
    return ClearBox_Conv2(coord(1, 12, wram->wTilemap), 18, 5);
}

void PlaceMoveData(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // hlcoord(0, 10, wTilemap);
    // LD_DE(mString_MoveType_Top);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_MoveType_Top), coord(0, 10, wram->wTilemap));
    // hlcoord(0, 11, wTilemap);
    // LD_DE(mString_MoveType_Bottom);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_MoveType_Bottom), coord(0, 11, wram->wTilemap));
    // hlcoord(12, 12, wTilemap);
    // LD_DE(mString_MoveAtk);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_MoveAtk), coord(12, 12, wram->wTilemap));
    // LD_A_addr(wCurSpecies);
    // LD_B_A;
    // hlcoord(2, 12, wTilemap);
    // PREDEF(pPrintMoveType);
    PrintMoveType_Conv(coord(2, 12, wram->wTilemap), wram->wCurSpecies);
    // LD_A_addr(wCurSpecies);
    // DEC_A;
    // LD_HL(mMoves + MOVE_POWER);
    // LD_BC(MOVE_LENGTH);
    // CALL(aAddNTimes);
    // LD_A(BANK(aMoves));
    // CALL(aGetFarByte);
    // hlcoord(16, 12, wTilemap);
    // CP_A(2);
    // IF_C goto no_power;
    uint8_t power = Moves[wram->wCurSpecies].power;
    if(power < 2) {
    // no_power:
        // LD_DE(mString_MoveNoPower);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_MoveNoPower), coord(16, 12, wram->wTilemap));
    }
    else {
        // LD_addr_A(wTextDecimalByte);
        // LD_DE(wTextDecimalByte);
        // LD_BC((1 << 8) | 3);
        // CALL(aPrintNum);
        PrintNum_Conv2(coord(16, 12, wram->wTilemap), &power, 1, 3);
        // goto description;
    }

// description:
    // hlcoord(1, 14, wTilemap);
    // PREDEF(pPrintMoveDescription);
    PrintMoveDescription_Conv(coord(1, 14, wram->wTilemap), wram->wCurSpecies);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // RET;
}

const char String_MoveType_Top[]    = "┌─────┐";
const char String_MoveType_Bottom[] = "│TYPE/└";
const char String_MoveAtk[]         =  "ATK/";
const char String_MoveNoPower[]     =  "---";

void PlaceMoveScreenArrows(void){
    CALL(aPlaceMoveScreenLeftArrow);
    CALL(aPlaceMoveScreenRightArrow);
    RET;

}

void PlaceMoveScreenLeftArrow(void){
    LD_A_addr(wCurPartyMon);
    AND_A_A;
    RET_Z ;
    LD_C_A;
    LD_E_A;
    LD_D(0);
    LD_HL(wPartyCount);
    ADD_HL_DE;

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto prev;
    CP_A(EGG);
    IF_Z goto prev;
    CP_A(NUM_POKEMON + 1);
    IF_C goto legal;


prev:
    DEC_HL;
    DEC_C;
    IF_NZ goto loop;
    RET;


legal:
    hlcoord(16, 0, wTilemap);
    LD_hl(0x71);
    RET;

}

void PlaceMoveScreenRightArrow(void){
    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_C_A;
    LD_A_addr(wPartyCount);
    CP_A_C;
    RET_Z ;
    LD_E_C;
    LD_D(0);
    LD_HL(wPartySpecies);
    ADD_HL_DE;

loop:
    LD_A_hl;
    CP_A(-1);
    RET_Z ;
    AND_A_A;
    IF_Z goto next;
    CP_A(EGG);
    IF_Z goto next;
    CP_A(NUM_POKEMON + 1);
    IF_C goto legal;


next:
    INC_HL;
    goto loop;


legal:
    hlcoord(18, 0, wTilemap);
    LD_hl(0xed);
    RET;

}
