#include "../../constants.h"
#include "mon_menu.h"
#include "mon_submenu.h"
#include "tempmon.h"
#include "mon_stats.h"
#include "mail.h"
#include "mail_2.h"
#include "types.h"
#include "party_menu.h"
#include "print_move_description.h"
#include "stats_screen.h"
#include "switchpartymons.h"
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
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/sram.h"
#include "../gfx/load_font.h"
#include "../gfx/sprites.h"
#include "../gfx/mon_icons.h"
#include "../items/items.h"
#include "../items/buy_sell_toss.h"
#include "../items/item_effects.h"
#include "../items/pack.h"
#include "../events/overworld.h"
#include "../events/sweet_scent.h"
#include "../menus/naming_screen.h"
#include "../../data/text/common.h"
#include "../../data/moves/moves.h"
#include "../../mobile/mobile_41.h"

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
    CopyName1(GetItemName(item));
    // RET;
}

u8_pair_s CancelPokemonAction(void){
    // FARCALL(aInitPartyMenuWithCancel);
    InitPartyMenuWithCancel();
    // FARCALL(aUnfreezeMonIcons);
    UnfreezeMonIcons_Conv();
    // LD_A(1);
    // RET;
    return u8_pair(0x1, 0x0);
}

u8_pair_s PokemonActionSubmenu(void){
    // hlcoord(1, 15, wTilemap);
    // LD_BC((2 << 8) | 18);
    // CALL(aClearBox);
    ClearBox(coord(1, 15, wram->wTilemap), 18, 2);
    // FARCALL(aMonSubmenu);
    MonSubmenu();
    // CALL(aGetCurNickname);
    GetCurNickname_Conv();
    // LD_A_addr(wMenuSelection);
    // LD_HL(mPokemonActionSubmenu_Actions);
    // LD_DE(3);
    // CALL(aIsInArray);
    // IF_NC goto nothing;

// Actions:
    switch(wram->wMenuSelection) {
        case MONMENUITEM_CUT:       return MonMenu_Cut();
        case MONMENUITEM_FLY:       return MonMenu_Fly();
        case MONMENUITEM_SURF:      return MonMenu_Surf();
        case MONMENUITEM_STRENGTH:  return MonMenu_Strength();
        case MONMENUITEM_FLASH:     return MonMenu_Flash();
        case MONMENUITEM_WHIRLPOOL: return MonMenu_Whirlpool();
        case MONMENUITEM_DIG:       return MonMenu_Dig();
        case MONMENUITEM_TELEPORT:  return MonMenu_Teleport();
        case MONMENUITEM_SOFTBOILED:return MonMenu_Softboiled_MilkDrink();
        case MONMENUITEM_MILKDRINK: return MonMenu_Softboiled_MilkDrink();
        case MONMENUITEM_HEADBUTT:  return MonMenu_Headbutt();
        case MONMENUITEM_WATERFALL: return MonMenu_Waterfall();
        case MONMENUITEM_ROCKSMASH: return MonMenu_RockSmash();
        case MONMENUITEM_SWEETSCENT:return MonMenu_SweetScent();
        case MONMENUITEM_STATS:     return OpenPartyStats();
        case MONMENUITEM_SWITCH:    return SwitchPartyMons();
        case MONMENUITEM_ITEM:      return GiveTakePartyMonItem();
        case MONMENUITEM_CANCEL:    return CancelPokemonAction();
        case MONMENUITEM_MOVE:      return ManagePokemonMoves();
        case MONMENUITEM_MAIL:      return MonMailAction();
        default:
        // nothing:
            // LD_A(0);
            // RET;
            return u8_pair(0, 0);
    }

    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
}

//  Don't try if there's nothing to switch!
u8_pair_s SwitchPartyMons(void){
    // LD_A_addr(wPartyCount);
    // CP_A(2);
    // IF_C goto DontSwitch;
    if(wram->wPartyCount >= 2) {
        // LD_A_addr(wCurPartyMon);
        // INC_A;
        // LD_addr_A(wSwitchMon);
        wram->wSwitchMon = wram->wCurPartyMon + 1;

        // FARCALL(aHoldSwitchmonIcon);
        HoldSwitchmonIcon_Conv();
        // FARCALL(aInitPartyMenuNoCancel);
        InitPartyMenuNoCancel();

        // LD_A(PARTYMENUACTION_MOVE);
        // LD_addr_A(wPartyMenuActionText);
        wram->wPartyMenuActionText = PARTYMENUACTION_MOVE;
        // FARCALL(aWritePartyMenuTilemap);
        WritePartyMenuTilemap();
        // FARCALL(aPrintPartyMenuText);
        PrintPartyMenuText();

        // hlcoord(0, 1, wTilemap);
        // LD_BC(SCREEN_WIDTH * 2);
        // LD_A_addr(wSwitchMon);
        // DEC_A;
        // CALL(aAddNTimes);
        // LD_hl(0xec);
        coord(0, 1, wram->wTilemap)[SCREEN_WIDTH * 2 * (wram->wSwitchMon - 1)] = 0xec;
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aSetPalettes);
        SetPalettes();
        // CALL(aDelayFrame);
        DelayFrame();

        // FARCALL(aPartyMenuSelect);
        u8_flag_s res = PartyMenuSelect();
        // BIT_B(1);
        // IF_C goto DontSwitch;
        if(!res.flag){
            // FARCALL(av_SwitchPartyMons);
            v_SwitchPartyMons();

            // XOR_A_A;
            // LD_addr_A(wPartyMenuActionText);
            wram->wPartyMenuActionText = 0x0;

            // FARCALL(aLoadPartyMenuGFX);
            LoadPartyMenuGFX();
            // FARCALL(aInitPartyMenuWithCancel);
            InitPartyMenuWithCancel();
            // FARCALL(aInitPartyMenuGFX);
            InitPartyMenuGFX();

            // LD_A(1);
            // RET;
            return u8_pair(1, 0);
        }
    }

// DontSwitch:
    // XOR_A_A;
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = 0x0;
    // CALL(aCancelPokemonAction);
    // RET;
    return CancelPokemonAction();
}

static void GiveTakePartyMonItem_GiveItem(void){
    // FARCALL(aDepositSellInitPackBuffers);
    DepositSellInitPackBuffers();

    while(1) {
    // loop:
        // FARCALL(aDepositSellPack);
        DepositSellPack();

        // LD_A_addr(wPackUsedItem);
        // AND_A_A;
        // IF_Z goto quit;
        if(wram->wPackUsedItem == NO_ITEM)
            break;

        // LD_A_addr(wCurPocket);
        // CP_A(KEY_ITEM_POCKET);
        // IF_Z goto next;
        if(wram->wCurPocket != KEY_ITEM_POCKET) {
            // CALL(aCheckTossableItem);
            // LD_A_addr(wItemAttributeValue);
            // AND_A_A;
            // IF_NZ goto next;
            if(CheckTossableItem_Conv(wram->wCurItem)) {
                // CALL(aTryGiveItemToPartymon);
                TryGiveItemToPartymon();
                // goto quit;
                break;
            }
        }

    // next:
        // LD_HL(mItemCantHeldText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(ItemCantHeldText);
        // goto loop;
    }

// quit:
    // RET;
}

u8_pair_s GiveTakePartyMonItem(void){
//  Eggs can't hold items!
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto cancel;
    if(wram->wCurPartySpecies == EGG)
        goto cancel;

    // LD_HL(mGiveTakeItemMenuData);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&GiveTakeItemMenuData);
    // CALL(aVerticalMenu);
    bool quit = !VerticalMenu_Conv();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // IF_C goto cancel;
    if(quit)
        goto cancel;

    // CALL(aGetCurNickname);
    // LD_HL(wStringBuffer1);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wMonOrItemNameBuffer, GetCurNickname_Conv(), MON_NAME_LENGTH);
    // LD_A_addr(wMenuCursorY);
    // CP_A(1);
    // IF_NZ goto take;
    if(wram->wMenuCursorY == 1) {
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader_Conv();
        // CALL(aClearPalettes);
        ClearPalettes();
        // CALL(aGiveTakePartyMonItem_GiveItem);
        GiveTakePartyMonItem_GiveItem();
        // CALL(aClearPalettes);
        ClearPalettes();
        // CALL(aLoadFontsBattleExtra);
        LoadFontsBattleExtra_Conv();
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // LD_A(0);
        // RET;
        return u8_pair(0, 0);
    }
    else {
    // take:
        // CALL(aTakePartyItem);
        TakePartyItem();
        // LD_A(3);
        // RET;
        return u8_pair(3, 0);
    }

cancel:
    // LD_A(3);
    // RET;
    return u8_pair(3, 0);
}

void TryGiveItemToPartymon(void){
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // CALL(aPartyMonItemName);
    PartyMonItemName_Conv(wram->wCurItem);
    // CALL(aGetPartyItemLocation);
    item_t* itm = GetPartyItemLocation();
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto give_item_to_mon;
    if(*itm == NO_ITEM) {
    // give_item_to_mon:
        // CALL(aGiveItemToPokemon);
        GiveItemToPokemon(wram->wCurItem);
        // LD_HL(mPokemonHoldItemText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(PokemonHoldItemText);
        // CALL(aGivePartyItem);
        GivePartyItem(wram->wCurItem);
        // RET;
        return;
    }
    // PUSH_HL;
    // LD_D_A;
    // FARCALL(aItemIsMail);
    // POP_HL;
    // IF_C goto please_remove_mail;
    else if(ItemIsMail_Conv(*itm)) {
    // please_remove_mail:
        // LD_HL(mPokemonRemoveMailText);
        // CALL(aMenuTextboxBackup);
        MenuTextbox_Conv(PokemonRemoveMailText);
        // RET;
        return;
    }
    // LD_A_hl;
    // goto already_holding_item;

// already_holding_item:
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    GetItemName(*itm);
    // LD_HL(mPokemonAskSwapItemText);
    // CALL(aStartMenuYesNo);
    // IF_C goto abort;
    if(StartMenuYesNo_Conv(PokemonAskSwapItemText)) {
        // CALL(aGiveItemToPokemon);
        GiveItemToPokemon(wram->wCurItem);
        // LD_A_addr(wNamedObjectIndex);
        // PUSH_AF;
        // LD_A_addr(wCurItem);
        // LD_addr_A(wNamedObjectIndex);
        // POP_AF;
        // LD_addr_A(wCurItem);
        // CALL(aReceiveItemFromPokemon);
        // IF_NC goto bag_full;
        if(ReceiveItemFromPokemon(*itm)) {
            // LD_HL(mPokemonSwapItemText);
            // CALL(aMenuTextboxBackup);
            MenuTextboxBackup_Conv(PokemonSwapItemText);
            // LD_A_addr(wNamedObjectIndex);
            // LD_addr_A(wCurItem);
            // CALL(aGivePartyItem);
            GivePartyItem(wram->wCurItem);
            // RET;
            return;
        }

    // bag_full:
        // LD_A_addr(wNamedObjectIndex);
        // LD_addr_A(wCurItem);
        // CALL(aReceiveItemFromPokemon);
        ReceiveItemFromPokemon(wram->wCurItem);
        // LD_HL(mItemStorageFullText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(ItemStorageFullText);
    }

// abort:
    // RET;
}

void GivePartyItem(item_t item){
    // CALL(aGetPartyItemLocation);
    // LD_A_addr(wCurItem);
    // LD_hl_A;
    *GetPartyItemLocation() = item;
    // LD_D_A;
    // FARCALL(aItemIsMail);
    // IF_NC goto done;
    if(ItemIsMail_Conv(item)) {
        // CALL(aComposeMailMessage);
        ComposeMailMessage();
    }

// done:
    // RET;
}

void TakePartyItem(void){
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // CALL(aGetPartyItemLocation);
    item_t* itm = GetPartyItemLocation();
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto not_holding_item;
    if(*itm != NO_ITEM) {
        // LD_addr_A(wCurItem);
        // CALL(aReceiveItemFromPokemon);
        // IF_NC goto item_storage_full;
        if(ReceiveItemFromPokemon(*itm)) {
            // FARCALL(aItemIsMail);
            // CALL(aGetPartyItemLocation);
            // LD_A_hl;
            item_t item = *itm;
            // LD_addr_A(wNamedObjectIndex);
            // LD_hl(NO_ITEM);
            *itm = NO_ITEM;
            // CALL(aGetItemName);
            GetItemName(item);
            // LD_HL(mPokemonTookItemText);
            // CALL(aMenuTextboxBackup);
            MenuTextboxBackup_Conv(PokemonTookItemText);
            // goto done;
        }
        else {
        // item_storage_full:
            // LD_HL(mItemStorageFullText);
            // CALL(aMenuTextboxBackup);
            MenuTextboxBackup_Conv(ItemStorageFullText);
        }
    }
    else {
    // not_holding_item:
        // LD_HL(mPokemonNotHoldingText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(PokemonNotHoldingText);
        // goto done;
    }


// done:
    // RET;
}

const struct MenuHeader GiveTakeItemMenuData = {
    .flags = MENU_SPRITE_ANIMS | MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(12, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    //dw ['.Items'];
    .data = &(struct MenuData) {
    // Items:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 2,  // # items
            .options = (const char*[]) {
                "GIVE@",
                "TAKE@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

const txt_cmd_s PokemonSwapItemText[] = {
    text_far(v_PokemonSwapItemText)
    text_end
};

const txt_cmd_s PokemonHoldItemText[] = {
    text_far(v_PokemonHoldItemText)
    text_end
};

const txt_cmd_s PokemonRemoveMailText[] = {
    text_far(v_PokemonRemoveMailText)
    text_end
};

const txt_cmd_s PokemonNotHoldingText[] = {
    text_far(v_PokemonNotHoldingText)
    text_end
};

const txt_cmd_s ItemStorageFullText[] = {
    text_far(v_ItemStorageFullText)
    text_end
};

const txt_cmd_s PokemonTookItemText[] = {
    text_far(v_PokemonTookItemText)
    text_end
};

const txt_cmd_s PokemonAskSwapItemText[] = {
    text_far(v_PokemonAskSwapItemText)
    text_end
};

const txt_cmd_s ItemCantHeldText[] = {
    text_far(v_ItemCantHeldText)
    text_end
};

item_t* GetPartyItemLocation(void){
    // PUSH_AF;
    // LD_A(MON_ITEM);
    // CALL(aGetPartyParamLocation);
    // POP_AF;
    // RET;
    return &wram->wPartyMon[wram->wCurPartyMon].mon.item;
}

bool ReceiveItemFromPokemon(item_t item){
    // LD_A(1);
    // LD_addr_A(wItemQuantityChange);
    // LD_HL(wNumItems);
    // JP(mReceiveItem);
    return ReceiveItem_Conv((item_pocket_s*)&wram->wNumItems, item, 1);
}

void GiveItemToPokemon(item_t item){
    // LD_A(1);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = 1;
    // LD_HL(wNumItems);
    // JP(mTossItem);
    TossItem_Conv((item_pocket_s*)&wram->wNumItems, item);
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
    // LD_DE(wTempMailMessage);
    // FARCALL(av_ComposeMailMessage);
    v_ComposeMailMessage(wram->wTempMail.message);
    // LD_HL(wPlayerName);
    // LD_DE(wTempMailAuthor);
    // LD_BC(NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes(wram->wTempMail.author, wram->wPlayerName, NAME_LENGTH - 1);
    // LD_HL(wPlayerID);
    // LD_BC(2);
    // CALL(aCopyBytes);
    wram->wTempMail.authorID = wram->wPlayerID;
    // LD_A_addr(wCurPartySpecies);
    // LD_de_A;
    wram->wTempMail.species = wram->wCurPartySpecies;
    // INC_DE;
    // LD_A_addr(wCurItem);
    // LD_de_A;
    wram->wTempMail.type = wram->wCurItem;
    // LD_A_addr(wCurPartyMon);
    // LD_HL(sPartyMail);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    OpenSRAM_Conv(MBANK(asPartyMail));
    struct MailMsg* de = ((struct MailMsg*)GBToRAMAddr(sPartyMail)) + wram->wCurPartyMon;
    // LD_HL(wTempMail);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    // CALL(aCopyBytes);
    CopyBytes(de, &wram->wTempMail, sizeof(*de));
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

static const struct MenuHeader MonMailAction_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(12, 10, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 3,  // items
            .options = (const char*[]){
                "READ@",
                "TAKE@",
                "QUIT@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

static u8_pair_s MonMailAction_read(void) {
// read:
    // FARCALL(aReadPartyMonMail);
    ReadPartyMonMail();
    // LD_A(0x0);
    // RET;
    return u8_pair(0x0, 0x0);
}

u8_pair_s MonMailAction(void){
    static const txt_cmd_s MailLoseMessageText[] = {
        text_far(v_MailLoseMessageText)
        text_end
    };

    static const txt_cmd_s MailDetachedText[] = {
        text_far(v_MailDetachedText)
        text_end
    };

    static const txt_cmd_s MailNoSpaceText[] = {
        text_far(v_MailNoSpaceText)
        text_end
    };

    static const txt_cmd_s MailAskSendToPCText[] = {
        text_far(v_MailAskSendToPCText)
        text_end
    };

    static const txt_cmd_s MailboxFullText[] = {
        text_far(v_MailboxFullText)
        text_end
    };

    static const txt_cmd_s MailSentToPCText[] = {
        text_far(v_MailSentToPCText)
        text_end
    };
//  If in the time capsule or trade center,
//  selecting the mail only allows you to
//  read the mail.
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_TIMECAPSULE);
    // IF_Z goto read;
    // CP_A(LINK_TRADECENTER);
    // IF_Z goto read;
    if(wram->wLinkMode == LINK_TIMECAPSULE || wram->wLinkMode == LINK_TRADECENTER)
        return MonMailAction_read();

//  Show the READ/TAKE/QUIT menu.
    // LD_HL(mMonMailAction_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MonMailAction_MenuHeader);
    // CALL(aVerticalMenu);
    bool cancel = !VerticalMenu_Conv();
    // CALL(aExitMenu);
    ExitMenu_Conv2();

//  Interpret the menu.
    // JP_C (mMonMailAction_done);
    if(!cancel) {
        // LD_A_addr(wMenuCursorY);
        // CP_A(0x1);
        // IF_Z goto read;
        // CP_A(0x2);
        // IF_Z goto take;
        // JP(mMonMailAction_done);
        switch(wram->wMenuCursorY){
        case 0x1:
            return MonMailAction_read();

        case 0x2:
        // take:
            // LD_HL(mMonMailAction_MailAskSendToPCText);
            // CALL(aStartMenuYesNo);
            // IF_C goto RemoveMailToBag;
            if(!StartMenuYesNo_Conv(MailAskSendToPCText)) {
            // RemoveMailToBag:
                // LD_HL(mMonMailAction_MailLoseMessageText);
                // CALL(aStartMenuYesNo);
                // IF_C goto done;
                if(StartMenuYesNo_Conv(MailLoseMessageText)) {
                    // CALL(aGetPartyItemLocation);
                    // LD_A_hl;
                    // LD_addr_A(wCurItem);
                    // CALL(aReceiveItemFromPokemon);
                    // IF_NC goto BagIsFull;
                    if(ReceiveItemFromPokemon(*GetPartyItemLocation())) {
                        // CALL(aGetPartyItemLocation);
                        // LD_hl(0x0);
                        *GetPartyItemLocation() = NO_ITEM;
                        // CALL(aGetCurNickname);
                        GetCurNickname_Conv();
                        // LD_HL(mMonMailAction_MailDetachedText);
                        // CALL(aMenuTextboxBackup);
                        MenuTextboxBackup_Conv(MailDetachedText);
                        // goto done;
                    }
                    else {
                    // BagIsFull:
                        // LD_HL(mMonMailAction_MailNoSpaceText);
                        // CALL(aMenuTextboxBackup);
                        MenuTextboxBackup_Conv(MailNoSpaceText);
                        // goto done;
                    }
                }
            }
            else {
                // LD_A_addr(wCurPartyMon);
                // LD_B_A;
                // FARCALL(aSendMailToPC);
                bool full = SendMailToPC(wram->wCurPartyMon);
                // IF_C goto MailboxFull;
                if(full) {
                // MailboxFull:
                    // LD_HL(mMonMailAction_MailboxFullText);
                    // CALL(aMenuTextboxBackup);
                    MenuTextboxBackup_Conv(MailboxFullText);
                    // goto done;
                }
                else {
                    // LD_HL(mMonMailAction_MailSentToPCText);
                    // CALL(aMenuTextboxBackup);
                    MenuTextboxBackup_Conv(MailSentToPCText);
                    // goto done;
                }
            }
            break;
        }
    }

// done:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s OpenPartyStats(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // CALL(aClearSprites);
    ClearSprites();
//  PartyMon
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // CALL(aLowVolume);
    LowVolume();
    // PREDEF(pStatsScreenInit);
    StatsScreenInit();
    // CALL(aMaxVolume);
    MaxVolume();
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // LD_A(0);
    // RET;
    return u8_pair(0, 0);
}

u8_pair_s MonMenu_Cut(void){
    // FARCALL(aCutFunction);
    CutFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x1);
    // IF_NZ goto Fail;
    if(wram->wFieldMoveSucceeded == 0x1){
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_Fly(void){
    // FARCALL(aFlyFunction);
    FlyFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x2);
    // IF_Z goto Fail;
    if(wram->wFieldMoveSucceeded == 0x2) {
    // Fail:
        // LD_A(0x3);
        // RET;
        return u8_pair(0x3, 0x0);
    }
    // CP_A(0x0);
    // IF_Z goto Error;
    if(wram->wFieldMoveSucceeded == 0x0) {
    // Error:
        // LD_A(0x0);
        // RET;
        return u8_pair(0x0, 0x0);
    }
    // FARCALL(aStubbedTrainerRankings_Fly);
    StubbedTrainerRankings_Fly();
    // LD_B(0x4);
    // LD_A(0x2);
    // RET;
    return u8_pair(0x2, 0x4);

// NoReload:
//   //  unreferenced
    // LD_A(0x1);
    // RET;
}

u8_pair_s MonMenu_Flash(void){
    // FARCALL(aFlashFunction);
    FlashFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x1);
    // IF_NZ goto Fail;
    if(wram->wFieldMoveSucceeded == 0x1) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_Strength(void){
    // FARCALL(aStrengthFunction);
    StrengthFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x1);
    // IF_NZ goto Fail;
    if(wram->wFieldMoveSucceeded == 0x1) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_Whirlpool(void){
    // FARCALL(aWhirlpoolFunction);
    WhirlpoolFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x1);
    // IF_NZ goto Fail;
    if(wram->wFieldMoveSucceeded == 0x1) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_Waterfall(void){
    // FARCALL(aWaterfallFunction);
    WaterfallFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x1);
    // IF_NZ goto Fail;
    if(wram->wFieldMoveSucceeded == 0x1) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_Teleport(void){
    // FARCALL(aTeleportFunction);
    TeleportFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // AND_A_A;
    // IF_Z goto Fail;
    if(wram->wFieldMoveSucceeded != 0x0) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_Surf(void){
    // FARCALL(aSurfFunction);
    SurfFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // AND_A_A;
    // IF_Z goto Fail;
    if(wram->wFieldMoveSucceeded != 0x0) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_Dig(void){
    // FARCALL(aDigFunction);
    DigFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x1);
    // IF_NZ goto Fail;
    if(wram->wFieldMoveSucceeded == 0x1) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

static bool MonMenu_Softboiled_MilkDrink_CheckMonHasEnoughHP(void){
//  Need to have at least (MaxHP / 5) HP left.
    // LD_A(MON_MAXHP);
    // CALL(aGetPartyParamLocation);
    // LD_A_hli;
    // LDH_addr_A(hDividend + 0);
    // LD_A_hl;
    // LDH_addr_A(hDividend + 1);
    // LD_A(5);
    // LDH_addr_A(hDivisor);
    // LD_B(2);
    // CALL(aDivide);
    uint16_t amt = BigEndianToNative16(wram->wPartyMon[wram->wCurPartyMon].maxHP) / 5;
    // LD_A(MON_HP + 1);
    // CALL(aGetPartyParamLocation);
    // LDH_A_addr(hQuotient + 3);
    // SUB_A_hl;
    // DEC_HL;
    // LDH_A_addr(hQuotient + 2);
    // SBC_A_hl;
    // RET;
    return BigEndianToNative16(wram->wPartyMon[wram->wCurPartyMon].HP) >= amt;
}

u8_pair_s MonMenu_Softboiled_MilkDrink(void){
    static const txt_cmd_s PokemonNotEnoughHPText[] = {
        text_far(v_PokemonNotEnoughHPText)
        text_end
    };
    // CALL(aMonMenu_Softboiled_MilkDrink_CheckMonHasEnoughHP);
    // IF_NC goto NotEnoughHP;
    if(MonMenu_Softboiled_MilkDrink_CheckMonHasEnoughHP()) {
        // FARCALL(aSoftboiled_MilkDrinkFunction);
        Softboiled_MilkDrinkFunction();
        // goto finish;
    }
    else {
    // NotEnoughHP:
        // LD_HL(mMonMenu_Softboiled_MilkDrink_PokemonNotEnoughHPText);
        // CALL(aPrintText);
        PrintText_Conv2(PokemonNotEnoughHPText);
    }

// finish:
    // XOR_A_A;
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = 0x0;
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_Headbutt(void){
    // FARCALL(aHeadbuttFunction);
    HeadbuttFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x1);
    // IF_NZ goto Fail;
    if(wram->wFieldMoveSucceeded == 0x1) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_RockSmash(void){
    // FARCALL(aRockSmashFunction);
    RockSmashFunction();
    // LD_A_addr(wFieldMoveSucceeded);
    // CP_A(0x1);
    // IF_NZ goto Fail;
    if(wram->wFieldMoveSucceeded == 0x1) {
        // LD_B(0x4);
        // LD_A(0x2);
        // RET;
        return u8_pair(0x2, 0x4);
    }

// Fail:
    // LD_A(0x3);
    // RET;
    return u8_pair(0x3, 0x0);
}

u8_pair_s MonMenu_SweetScent(void){
    // FARCALL(aSweetScentFromMenu);
    SweetScentFromMenu();
    // LD_B(0x4);
    // LD_A(0x2);
    // RET;
    return u8_pair(0x2, 0x4);
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
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
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
    ClearBGPalettes();
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

u8_pair_s ManagePokemonMoves(void){
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto egg;
    if(wram->wCurPartySpecies != EGG) {
        // LD_HL(wOptions);
        // LD_A_hl;
        // PUSH_AF;
        uint8_t options = wram->wOptions;
        // SET_hl(NO_TEXT_SCROLL);
        bit_set(wram->wOptions, NO_TEXT_SCROLL);
        // CALL(aMoveScreenLoop);
        MoveScreenLoop();
        // POP_AF;
        // LD_addr_A(wOptions);
        wram->wOptions = options;
        // CALL(aClearBGPalettes);
        ClearBGPalettes();
    }

// egg:
    // LD_A(0x0);
    // RET;
    return u8_pair(0x0, 0x0);
}

static void MoveScreenLoop_copy_move(move_t* hl){
    // PUSH_HL;
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    move_t* de = hl + (wram->wMenuCursorY - 1);
    // POP_HL;
    // LD_A_addr(wSwappingMove);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    hl = hl + (wram->wSwappingMove - 1);
    // LD_A_de;
    move_t a = *de;
    // LD_B_hl;
    move_t b = *hl;
    // LD_hl_A;
    *hl = a;
    // LD_A_B;
    // LD_de_A;
    *de = b;
    // RET;
}

static void MoveScreenLoop_copy_pp(uint8_t* hl){
    // PUSH_HL;
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    uint8_t* de = hl + (wram->wMenuCursorY - 1);
    // POP_HL;
    // LD_A_addr(wSwappingMove);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    hl = hl + (wram->wSwappingMove - 1);
    // LD_A_de;
    uint8_t a = *de;
    // LD_B_hl;
    uint8_t b = *hl;
    // LD_hl_A;
    *hl = a;
    // LD_A_B;
    // LD_de_A;
    *de = b;
    // RET;
}

static void MoveScreenLoop_cycle(int dir) {
    uint8_t c;
    switch(dir) {
    case 0:
    cycle_right:
        // LD_A_addr(wCurPartyMon);
        // INC_A;
        // LD_addr_A(wCurPartyMon);
        c = ++wram->wCurPartyMon;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(wPartySpecies);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(-1);
        // IF_Z goto cycle_left;
        if(wram->wPartySpecies[c] == (species_t)-1)
            goto cycle_left;
        // CP_A(EGG);
        // RET_NZ ;
        if(wram->wPartySpecies[c] != EGG)
            return;
        goto cycle_right;

    case 1:
    cycle_left:
        // LD_A_addr(wCurPartyMon);
        // AND_A_A;
        // RET_Z ;
        if(wram->wCurPartyMon == 0)
            return;

    cycle_left_loop:
        // LD_A_addr(wCurPartyMon);
        // DEC_A;
        // LD_addr_A(wCurPartyMon);
        // LD_C_A;
        c = --wram->wCurPartyMon;
        // LD_B(0);
        // LD_HL(wPartySpecies);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(EGG);
        // RET_NZ ;
        if(wram->wPartySpecies[c] != EGG)
            return;
        // LD_A_addr(wCurPartyMon);
        // AND_A_A;
        // IF_Z goto cycle_right;
        if(wram->wCurPartyMon == 0)
            goto cycle_right;
        goto cycle_left_loop;
    }
}

// TODO: Fix gotos in this function and all subfunctions
void MoveScreenLoop(void){
    uint8_t a;
Loop:
    // LD_A_addr(wCurPartyMon);
    // INC_A;
    // LD_addr_A(wPartyMenuCursor);
    wram->wPartyMenuCursor = wram->wCurPartyMon + 1;
    // CALL(aSetUpMoveScreenBG);
    SetUpMoveScreenBG();
    // CALL(aPlaceMoveScreenArrows);
    PlaceMoveScreenArrows();
    // LD_DE(mMoveScreen2DMenuData);
    // CALL(aLoad2DMenuData);
    Load2DMenuData_Conv(MoveScreen2DMenuData);

loop:
    // CALL(aSetUpMoveList);
    SetUpMoveList();
    // LD_HL(w2DMenuFlags1);
    // SET_hl(6);
    bit_set(wram->w2DMenuFlags1, 6);
    goto skip_joy;


joy_loop:
    // CALL(aScrollingMenuJoypad);
    a = ScrollingMenuJoypad_Conv();
    // BIT_A(1);
    // JP_NZ (mMoveScreenLoop_b_button);
    if(bit_test(a, B_BUTTON_F)) {
    // b_button:
        // CALL(aPlayClickSFX);
        PlayClickSFX_Conv();
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_A_addr(wSwappingMove);
        // AND_A_A;
        // JP_Z (mMoveScreenLoop_exit);
        if(wram->wSwappingMove == 0)
            goto exit;

        // LD_A_addr(wSwappingMove);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = wram->wSwappingMove;
        // XOR_A_A;
        // LD_addr_A(wSwappingMove);
        wram->wSwappingMove = 0;
        // hlcoord(1, 2, wTilemap);
        // LD_BC((8 << 8) | (SCREEN_WIDTH - 2));
        // CALL(aClearBox);
        ClearBox(coord(1, 2, wram->wTilemap), SCREEN_WIDTH - 2, 8);
        // JP(mMoveScreenLoop_loop);
        goto loop;
    }
    // BIT_A(0);
    // JP_NZ (mMoveScreenLoop_a_button);
    if(bit_test(a, A_BUTTON_F)) {
    // a_button:
        // CALL(aPlayClickSFX);
        PlayClickSFX_Conv();
        // CALL(aWaitSFX);
        // LD_A_addr(wSwappingMove);
        // AND_A_A;
        // IF_NZ goto place_move;
        if(wram->wSwappingMove == 0) {
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wSwappingMove);
            wram->wSwappingMove = wram->wMenuCursorY;
            // CALL(aPlaceHollowCursor);
            PlaceHollowCursor_Conv();
            // JP(mMoveScreenLoop_moving_move);
            goto moving_move;
        }

    // place_move:
        // LD_HL(wPartyMon1Moves);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_addr(wCurPartyMon);
        // CALL(aAddNTimes);
        struct PartyMon* mon = wram->wPartyMon + wram->wCurPartyMon;
        // PUSH_HL;
        // CALL(aMoveScreenLoop_copy_move);
        MoveScreenLoop_copy_move(mon->mon.moves);
        // POP_HL;
        // LD_BC(wPartyMon1PP - wPartyMon1Moves);
        // ADD_HL_BC;
        // CALL(aMoveScreenLoop_copy_move);
        MoveScreenLoop_copy_pp(mon->mon.PP);
        // LD_A_addr(wBattleMode);
        // IF_Z goto swap_moves;
        if(wram->wBattleMode != 0) {
            // LD_HL(wBattleMonMoves);
            // LD_BC(wBattleMonStructEnd - wBattleMon);
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // PUSH_HL;
            // CALL(aMoveScreenLoop_copy_move);
            MoveScreenLoop_copy_move(wram->wBattleMon.moves);
            // POP_HL;
            // LD_BC(wBattleMonPP - wBattleMonMoves);
            // ADD_HL_BC;
            // CALL(aMoveScreenLoop_copy_move);
            MoveScreenLoop_copy_pp(wram->wBattleMon.pp);
        }

    // swap_moves:
        // LD_DE(SFX_SWITCH_POKEMON);
        // CALL(aPlaySFX);
        PlaySFX(SFX_SWITCH_POKEMON);
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_DE(SFX_SWITCH_POKEMON);
        // CALL(aPlaySFX);
        PlaySFX(SFX_SWITCH_POKEMON);
        // CALL(aWaitSFX);
        WaitSFX();
        // hlcoord(1, 2, wTilemap);
        // LD_BC((8 << 8) | 18);
        // CALL(aClearBox);
        ClearBox(coord(1, 2, wram->wTilemap), 18, 8);
        // hlcoord(10, 10, wTilemap);
        // LD_BC((1 << 8) | 9);
        // CALL(aClearBox);
        ClearBox(coord(10, 10, wram->wTilemap), 9, 1);
        // JP(mMoveScreenLoop_loop);
        goto loop;
    }
    // BIT_A(4);
    // JP_NZ (mMoveScreenLoop_d_right);
    if(bit_test(a, D_RIGHT_F)) {
    // d_right:
        // LD_A_addr(wSwappingMove);
        // AND_A_A;
        // JP_NZ (mMoveScreenLoop_joy_loop);
        if(wram->wSwappingMove != 0)
            goto joy_loop;

        // LD_A_addr(wCurPartyMon);
        // LD_B_A;
        uint8_t b = wram->wCurPartyMon;
        // PUSH_BC;
        // CALL(aMoveScreenLoop_cycle_right);
        MoveScreenLoop_cycle(0);
        // POP_BC;
        // LD_A_addr(wCurPartyMon);
        // CP_A_B;
        // JP_Z (mMoveScreenLoop_joy_loop);
        if(wram->wCurPartyMon == b)
            goto joy_loop;
        // JP(mMoveScreenLoop);
        goto Loop;
    }
    // BIT_A(5);
    // JP_NZ (mMoveScreenLoop_d_left);
    if(bit_test(a, D_LEFT_F)) {
    // d_left:
        // LD_A_addr(wSwappingMove);
        // AND_A_A;
        // JP_NZ (mMoveScreenLoop_joy_loop);
        if(wram->wSwappingMove != 0)
            goto joy_loop;
        // LD_A_addr(wCurPartyMon);
        // LD_B_A;
        uint8_t b = wram->wCurPartyMon;
        // PUSH_BC;
        // CALL(aMoveScreenLoop_cycle_left);
        MoveScreenLoop_cycle(1);
        // POP_BC;
        // LD_A_addr(wCurPartyMon);
        // CP_A_B;
        // JP_Z (mMoveScreenLoop_joy_loop);
        if(wram->wCurPartyMon == b)
            goto joy_loop;
        // JP(mMoveScreenLoop);
        goto Loop;
    }

skip_joy:
    // CALL(aPrepareToPlaceMoveData);
    PrepareToPlaceMoveData();
    // LD_A_addr(wSwappingMove);
    // AND_A_A;
    // IF_NZ goto moving_move;
    if(wram->wSwappingMove == 0) {
        // CALL(aPlaceMoveData);
        PlaceMoveData();
        // JP(mMoveScreenLoop_joy_loop);
        goto joy_loop;
    }

moving_move:
    // LD_A(0x7f);
    // hlcoord(1, 11, wTilemap);
    // LD_BC(5);
    // CALL(aByteFill);
    ByteFill(coord(1, 11, wram->wTilemap), 5, 0x7f);
    // hlcoord(1, 12, wTilemap);
    // LD_BC((5 << 8) | (SCREEN_WIDTH - 2));
    // CALL(aClearBox);
    ClearBox(coord(1, 12, wram->wTilemap), SCREEN_WIDTH - 2, 5);
    // hlcoord(1, 12, wTilemap);
    // LD_DE(mString_MoveWhere);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_MoveWhere), coord(1, 12, wram->wTilemap));
    // JP(mMoveScreenLoop_joy_loop);
    goto joy_loop;

exit:
    // XOR_A_A;
    // LD_addr_A(wSwappingMove);
    wram->wSwappingMove = 0x0;
    // LD_HL(w2DMenuFlags1);
    // RES_hl(6);
    bit_reset(wram->w2DMenuFlags1, 6);
    // CALL(aClearSprites);
    ClearSprites();
    // JP(mClearTilemap);
    ClearTilemap();
}

const uint8_t MoveScreen2DMenuData[] = {
    3, 1,  // cursor start y, x
    3, 1,  // rows, columns
    0x40, 0x00,  // flags
    (2 << 4) | 0,  // cursor offsets
    D_UP | D_DOWN | D_LEFT | D_RIGHT | A_BUTTON | B_BUTTON,  // accepted buttons
};

const char String_MoveWhere[] = "Where?@";

void SetUpMoveScreenBG(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aClearSprites);
    ClearSprites();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
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
    Textbox(coord(0, 1, wram->wTilemap), 9, 18);
    // hlcoord(0, 11, wTilemap);
    // LD_B(5);
    // LD_C(18);
    // CALL(aTextbox);
    Textbox(coord(0, 11, wram->wTilemap), 5, 18);
    // hlcoord(2, 0, wTilemap);
    // LD_BC((2 << 8) | 3);
    // CALL(aClearBox);
    ClearBox(coord(2, 0, wram->wTilemap), 3, 2);
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
    uint16_t bc = BigEndianToNative16(wram->wPartyMon[wram->wCurPartyMon].HP);
    uint16_t de = BigEndianToNative16(wram->wPartyMon[wram->wCurPartyMon].maxHP);
    uint8_t e = bc * (6 * 8) / de;
    SetHPPal_Conv(&wram->wPlayerHPPal, e);
    // LD_B(SCGB_MOVE_LIST);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_MOVE_LIST);
    // hlcoord(16, 0, wTilemap);
    // LD_BC((1 << 8) | 3);
    // JP(mClearBox);
    return ClearBox(coord(16, 0, wram->wTilemap), 3, 1);
}

void SetUpMoveList(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_addr_A(wSwappingMove);
    wram->wSwappingMove = 0;
    // LD_addr_A(wMonType);
    wram->wMonType = 0;
    // PREDEF(pCopyMonToTempMon);
    CopyMonToTempMon_Conv();
    // LD_HL(wTempMonMoves);
    // LD_DE(wListMoves_MoveIndicesBuffer);
    // LD_BC(NUM_MOVES);
    // CALL(aCopyBytes);
    CopyBytes(wram->wListMoves_MoveIndicesBuffer, wram->wTempMon.mon.moves, sizeof(wram->wTempMon.mon.moves));
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
    WaitBGMap();
    // CALL(aSetPalettes);
    SetPalettes();
    // LD_A_addr(wNumMoves);
    // INC_A;
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wNumMoves + 1;
    // hlcoord(0, 11, wTilemap);
    // LD_B(5);
    // LD_C(18);
    // JP(mTextbox);
    return Textbox(coord(0, 11, wram->wTilemap), 5, 18);
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
    return ClearBox(coord(1, 12, wram->wTilemap), 18, 5);
}

void PlaceMoveData(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
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
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

const char String_MoveType_Top[]    = "┌─────┐";
const char String_MoveType_Bottom[] = "│TYPE/└";
const char String_MoveAtk[]         =  "ATK/";
const char String_MoveNoPower[]     =  "---";

void PlaceMoveScreenArrows(void){
    // CALL(aPlaceMoveScreenLeftArrow);
    PlaceMoveScreenLeftArrow();
    // CALL(aPlaceMoveScreenRightArrow);
    PlaceMoveScreenRightArrow();
    // RET;
}

void PlaceMoveScreenLeftArrow(void){
    // LD_A_addr(wCurPartyMon);
    // AND_A_A;
    // RET_Z ;
    if(wram->wCurPartyMon == 0)
        return;
    // LD_C_A;
    uint8_t c = wram->wCurPartyMon;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPartyCount);
    // ADD_HL_DE;
    species_t* species = wram->wPartySpecies + c - 1;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto prev;
        // CP_A(EGG);
        // IF_Z goto prev;
        // CP_A(NUM_POKEMON + 1);
        // IF_C goto legal;
        if(*species != 0 && *species != EGG && *species < NUM_POKEMON + 1) {
        // legal:
            // hlcoord(16, 0, wTilemap);
            // LD_hl(0x71);
            *coord(16, 0, wram->wTilemap) = 0x71;
            // RET;
            return;
        }

    // prev:
        // DEC_HL;
        --species;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void PlaceMoveScreenRightArrow(void){
    // LD_A_addr(wCurPartyMon);
    // INC_A;
    // LD_C_A;
    uint8_t c = wram->wCurPartyMon + 1;
    // LD_A_addr(wPartyCount);
    // CP_A_C;
    // RET_Z ;
    if(c == wram->wPartyCount)
        return;
    // LD_E_C;
    // LD_D(0);
    // LD_HL(wPartySpecies);
    // ADD_HL_DE;
    species_t* hl = wram->wPartySpecies + c;

    while(*hl != (species_t)-1) {
    // loop:
        // LD_A_hl;
        // CP_A(-1);
        // RET_Z ;
        // AND_A_A;
        // IF_Z goto next;
        // CP_A(EGG);
        // IF_Z goto next;
        // CP_A(NUM_POKEMON + 1);
        // IF_C goto legal;
        if(*hl != 0 && *hl != EGG && *hl <= NUM_POKEMON) {
        // legal:
            // hlcoord(18, 0, wTilemap);
            // LD_hl(0xed);
            *coord(18, 0, wram->wTilemap) = 0xed;
            // RET;
            return;
        }

    // next:
        // INC_HL;
        hl++;
        // goto loop;
    }

}
