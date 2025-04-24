#include "../../constants.h"
#include "pokecenter_pc.h"
#include "prof_oaks_pc.h"
#include "halloffame.h"
#include "../../home/menu.h"
#include "../../home/audio.h"
#include "../../home/tilemap.h"
#include "../../home/time_palettes.h"
#include "../../home/map.h"
#include "../../home/flag.h"
#include "../../home/map_objects.h"
#include "../../home/text.h"
#include "../../home/item.h"
#include "../../home/sprite_updates.h"
#include "../../home/scrolling_menu.h"
#include "../menus/scrolling_menu.h"
#include "../menus/menu_2.h"
#include "../items/update_item_description.h"
#include "../items/items.h"
#include "../items/pack.h"
#include "../items/buy_sell_toss.h"
#include "../items/switch_items.h"
#include "../pokemon/bills_pc_top.h"
#include "../pokemon/mon_menu.h"
#include "../pokemon/mail.h"
#include "../overworld/select_menu.h"
#include "../overworld/decorations.h"
#include "../../data/text/common.h"

// PokemonCenterPC.WhichPC indexes
enum {
    PCPC_BEFORE_POKEDEX,  // 0
    PCPC_BEFORE_HOF,  // 1
    PCPC_POSTGAME,  // 2
};

// PokemonCenterPC.Jumptable indexes
enum {
    PCPCITEM_PLAYERS_PC,  // 0
    PCPCITEM_BILLS_PC,  // 1
    PCPCITEM_OAKS_PC,  // 2
    PCPCITEM_HALL_OF_FAME,  // 3
    PCPCITEM_TURN_OFF,  // 4
};

static uint8_t PokemonCenterPC_ChooseWhichPCListToUse(void) {
    // CALL(aCheckReceivedDex);
    // IF_NZ goto got_dex;
    if(!CheckReceivedDex()) {
        // LD_A(PCPC_BEFORE_POKEDEX);
        // RET;
        return PCPC_BEFORE_POKEDEX;
    }

// got_dex:
    // LD_A_addr(wHallOfFameCount);
    // AND_A_A;
    // LD_A(PCPC_BEFORE_HOF);
    // RET_Z ;
    else if(wram->wHallOfFameCount == 0)
        return PCPC_BEFORE_HOF;
    // LD_A(PCPC_POSTGAME);
    // RET;
    return PCPC_POSTGAME;
}

static const struct MenuHeader PokemonCenterPC_TopMenu = {
    .flags = MENU_BACKUP_TILES | MENU_NO_CLICK_SFX,  // flags
    .coord = menu_coords(0, 0, 15, 12),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
        .setupMenu = {
            .count = 0,  // items
            //dw ['.WhichPC'];
            .itemList = (const uint8_t*[]) {
                // WhichPC:
                //  entries correspond to PCPC_* constants
                [PCPC_BEFORE_POKEDEX] = (uint8_t[]){
                    3,
                    PCPCITEM_BILLS_PC,
                    PCPCITEM_PLAYERS_PC,
                    PCPCITEM_TURN_OFF,
                    (uint8_t)-1,  // end
                },

                [PCPC_BEFORE_HOF] = (uint8_t[]){
                    4,
                    PCPCITEM_BILLS_PC,
                    PCPCITEM_PLAYERS_PC,
                    PCPCITEM_OAKS_PC,
                    PCPCITEM_TURN_OFF,
                    (uint8_t)-1,  // end
                },

                [PCPC_POSTGAME] = (uint8_t[]){
                    5,
                    PCPCITEM_BILLS_PC,
                    PCPCITEM_PLAYERS_PC,
                    PCPCITEM_OAKS_PC,
                    PCPCITEM_HALL_OF_FAME,
                    PCPCITEM_TURN_OFF,
                    -1,  // end
                },
            },
            //dw ['PlaceNthMenuStrings'];
            .displayFunction = PlaceNthMenuStrings_Conv,
            //dw ['.Jumptable'];
            .labelList = (struct LabeledMenuItem[]){
            // Jumptable:
            //  entries correspond to PCPCITEM_* constants
                [PCPCITEM_PLAYERS_PC]   = {PlayersPC, "<PLAYER>'s PC@"},
                [PCPCITEM_BILLS_PC]     = {BillsPC, "BILL's PC@"},
                [PCPCITEM_OAKS_PC]      = {OaksPC, "PROF.OAK's PC@"},
                [PCPCITEM_HALL_OF_FAME] = {HallOfFamePC, "HALL OF FAME@"},
                [PCPCITEM_TURN_OFF]     = {TurnOffPC, "TURN OFF@"},
            },
        },
    },
    .defaultOption = 1,  // default option
};


// static const char String_PlayersPC[] = "<PLAYER>'s PC@";
// static const char String_BillsPC[] = "BILL's PC@";
// static const char String_OaksPC[] = "PROF.OAK's PC@";
// static const char String_HallOfFame[] = "HALL OF FAME@";
// static const char String_TurnOff[] = "TURN OFF@";

void PokemonCenterPC(void){
    // CALL(aPC_CheckPartyForPokemon);
    // RET_C ;
    if(!PC_CheckPartyForPokemon())
        return;
    // CALL(aPC_PlayBootSound);
    PC_PlayBootSound();
    // LD_HL(mPokecenterPCTurnOnText);
    // CALL(aPC_DisplayText);
    PC_DisplayText_Conv(PokecenterPCTurnOnText);
    // LD_HL(mPokecenterPCWhoseText);
    // CALL(aPC_DisplayTextWaitMenu);
    PC_DisplayTextWaitMenu_Conv(PokecenterPCWhoseText);
    // LD_HL(mPokemonCenterPC_TopMenu);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&PokemonCenterPC_TopMenu);

    u8_flag_s res;
    do {
    // loop:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aPokemonCenterPC_ChooseWhichPCListToUse);
        // LD_addr_A(wWhichIndexSet);
        wram->wWhichIndexSet = PokemonCenterPC_ChooseWhichPCListToUse();
        // CALL(aDoNthMenu);
        // IF_C goto shutdown;
        res = DoNthMenu_Conv();
        if(res.flag)
            break;
        // LD_A_addr(wMenuSelection);
        // LD_HL(mPokemonCenterPC_Jumptable);
        // CALL(aMenuJumptable);
        res = MenuJumptable_Conv();
        // IF_NC goto loop;
    } while(!res.flag);

// shutdown:
    // CALL(aPC_PlayShutdownSound);
    PC_PlayShutdownSound();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // RET;
    return;
}

bool PC_CheckPartyForPokemon(void){
    static const txt_cmd_s PokecenterPCCantUseText[] = {
        text_far(v_PokecenterPCCantUseText)
        text_end
    };

    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wPartyCount != 0)
        return true;
    // LD_DE(SFX_CHOOSE_PC_OPTION);
    // CALL(aPlaySFX);
    PlaySFX(SFX_CHOOSE_PC_OPTION);
    // LD_HL(mPC_CheckPartyForPokemon_PokecenterPCCantUseText);
    // CALL(aPC_DisplayText);
    PC_DisplayText_Conv(PokecenterPCCantUseText);
    // SCF;
    // RET;
    return false;
}

// PlayersPCMenuData.WhichPC indexes
enum {
    PLAYERSPC_NORMAL,  // 0
    PLAYERSPC_HOUSE,  // 1
};

// PlayersPCMenuData.PlayersPCMenuPointers indexes
enum {
    PLAYERSPCITEM_WITHDRAW_ITEM,  // 0
    PLAYERSPCITEM_DEPOSIT_ITEM,  // 1
    PLAYERSPCITEM_TOSS_ITEM,  // 2
    PLAYERSPCITEM_MAIL_BOX,  // 3
    PLAYERSPCITEM_DECORATION,  // 4
    PLAYERSPCITEM_LOG_OFF,  // 5
    PLAYERSPCITEM_TURN_OFF,  // 6
};

u8_flag_s BillsPC(void){
    // CALL(aPC_PlayChoosePCSound);
    PC_PlayChoosePCSound();
    // LD_HL(mPokecenterBillsPCText);
    // CALL(aPC_DisplayText);
    PC_DisplayText_Conv(PokecenterBillsPCText);
    // FARCALL(av_BillsPC);
    v_BillsPC();
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

u8_flag_s PlayersPC(void){
    // CALL(aPC_PlayChoosePCSound);
    PC_PlayChoosePCSound();
    // LD_HL(mPokecenterPlayersPCText);
    // CALL(aPC_DisplayText);
    PC_DisplayText_Conv(PokecenterPlayersPCText);
    // LD_B(PLAYERSPC_NORMAL);
    // CALL(av_PlayersPC);
    u8_flag_s res = v_PlayersPC(PLAYERSPC_NORMAL);
    // AND_A_A;
    // RET;
    return res;
}

u8_flag_s OaksPC(void){
    // CALL(aPC_PlayChoosePCSound);
    PC_PlayChoosePCSound();
    // LD_HL(mPokecenterOaksPCText);
    // CALL(aPC_DisplayText);
    PC_DisplayText_Conv(PokecenterOaksPCText);
    // FARCALL(aProfOaksPC);
    ProfOaksPC();
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

u8_flag_s HallOfFamePC(void){
    // CALL(aPC_PlayChoosePCSound);
    PC_PlayChoosePCSound();
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(av_HallOfFamePC);
    v_HallOfFamePC();
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

u8_flag_s TurnOffPC(void){
    // LD_HL(mPokecenterPCOaksClosedText);
    // CALL(aPrintText);
    PrintText_Conv2(PokecenterPCOaksClosedText);
    // SCF;
    // RET;
    return u8_flag(0, true);
}

void PC_PlayBootSound(void){
    // LD_DE(SFX_BOOT_PC);
    // JR(mPC_WaitPlaySFX);
    return PC_WaitPlaySFX_Conv(SFX_BOOT_PC);
}

void PC_PlayShutdownSound(void){
    // LD_DE(SFX_SHUT_DOWN_PC);
    // CALL(aPC_WaitPlaySFX);
    PC_WaitPlaySFX_Conv(SFX_SHUT_DOWN_PC);
    // CALL(aWaitSFX);
    WaitSFX();
    // RET;
}

void PC_PlayChoosePCSound(void){
    // LD_DE(SFX_CHOOSE_PC_OPTION);
    // JR(mPC_WaitPlaySFX);
    return PC_WaitPlaySFX_Conv(SFX_CHOOSE_PC_OPTION);
}

void PC_PlaySwapItemsSound(void){
    // LD_DE(SFX_SWITCH_POKEMON);
    // CALL(aPC_WaitPlaySFX);
    PC_WaitPlaySFX_Conv(SFX_SWITCH_POKEMON);
    // LD_DE(SFX_SWITCH_POKEMON);

    return PC_WaitPlaySFX_Conv(SFX_SWITCH_POKEMON);
}

void PC_WaitPlaySFX(void){
    PUSH_DE;
    CALL(aWaitSFX);
    POP_DE;
    CALL(aPlaySFX);
    RET;

}

void PC_WaitPlaySFX_Conv(uint16_t sfx){
    // PUSH_DE;
    // CALL(aWaitSFX);
    WaitSFX();
    // POP_DE;
    // CALL(aPlaySFX);
    PlaySFX(sfx);
    // RET;
}

bool v_PlayersHousePC(void){
    // CALL(aPC_PlayBootSound);
    PC_PlayBootSound();
    // LD_HL(mPlayersPCTurnOnText);
    // CALL(aPC_DisplayText);
    PC_DisplayText_Conv(PlayersPCTurnOnText);
    // LD_B(PLAYERSPC_HOUSE);
    // CALL(av_PlayersPC);
    // AND_A_A;
    // IF_NZ goto changed_deco_tiles;
    if(v_PlayersPC(PLAYERSPC_HOUSE).a != 0) {
    // changed_deco_tiles:
        // CALL(aClearBGPalettes);
        ClearBGPalettes();
        // LD_C(TRUE);
        // RET;
        return true;
    }
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch_Conv();
    // CALL(aApplyTilemap);
    ApplyTilemap_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aPC_PlayShutdownSound);
    PC_PlayShutdownSound();
    // LD_C(FALSE);
    // RET;
    return false;
}

const txt_cmd_s PlayersPCTurnOnText[] = {
    text_far(v_PlayersPCTurnOnText)
    text_end
};

static u8_flag_s v_PlayersPC_PlayersPC(void) {
    // XOR_A_A;
    // LD_addr_A(wPCItemsCursor);
    wram->wPCItemsCursor = 0;
    // LD_addr_A(wPCItemsScrollPosition);
    wram->wPCItemsScrollPosition = 0;
    // LD_HL(mPlayersPCMenuData);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&PlayersPCMenuData);

    u8_flag_s jumptableRes;
    do {
    // loop:
        // CALL(aUpdateTimePals);
        UpdateTimePals();
        // CALL(aDoNthMenu);
        u8_flag_s res = DoNthMenu_Conv();
        // IF_C goto turn_off;
        if(res.flag) {
        // turn_off:
            // XOR_A_A;
            ExitMenu_Conv2();
            return u8_flag(0, false);
        }
        // CALL(aMenuJumptable);
        jumptableRes = MenuJumptable_Conv();
        // IF_NC goto loop;
    } while(!jumptableRes.flag);
    // goto done;

// done:
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
    return jumptableRes;
}

u8_flag_s v_PlayersPC(uint8_t b){
    // LD_A_B;
    // LD_addr_A(wWhichIndexSet);
    wram->wWhichIndexSet = b;
    // LD_HL(mPlayersPCAskWhatDoText);
    // CALL(aPC_DisplayTextWaitMenu);
    PC_DisplayTextWaitMenu_Conv(PlayersPCAskWhatDoText);
    // CALL(av_PlayersPC_PlayersPC);
    u8_flag_s res = v_PlayersPC_PlayersPC();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
    return res;
}

static const char WithdrawItem[] = "WITHDRAW ITEM@";
static const char DepositItem[] = "DEPOSIT ITEM@";
static const char TossItem_[] = "TOSS ITEM@";
static const char MailBox[] = "MAIL BOX@";
static const char Decoration[] = "DECORATION@";
static const char TurnOff[] = "TURN OFF@";
static const char LogOff[] = "LOG OFF@";

static const struct LabeledMenuItem PlayersPCMenuPointers[] = {
//  entries correspond to PLAYERSPCITEM_* constants
    {PlayerWithdrawItemMenu, WithdrawItem},
    {PlayerDepositItemMenu, DepositItem},
    {PlayerTossItemMenu, TossItem_},
    {PlayerMailBoxMenu, MailBox},
    {PlayerDecorationMenu, Decoration},
    {PlayerLogOffMenu, LogOff},
    {PlayerLogOffMenu, TurnOff},
};

static const uint8_t* PlayersPCMenuData_WhichPC[] = {
    (const uint8_t[]){
        5,
        PLAYERSPCITEM_WITHDRAW_ITEM,
        PLAYERSPCITEM_DEPOSIT_ITEM,
        PLAYERSPCITEM_TOSS_ITEM,
        PLAYERSPCITEM_MAIL_BOX,
        PLAYERSPCITEM_LOG_OFF,
        (uint8_t)-1,
    },
    (const uint8_t[]){
        6,
        PLAYERSPCITEM_WITHDRAW_ITEM,
        PLAYERSPCITEM_DEPOSIT_ITEM,
        PLAYERSPCITEM_TOSS_ITEM,
        PLAYERSPCITEM_MAIL_BOX,
        PLAYERSPCITEM_DECORATION,
        PLAYERSPCITEM_TURN_OFF,
        (uint8_t)-1,
    }
};

const struct MenuHeader PlayersPCMenuData = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 15, 12),
    //dw ['.PlayersPCMenuData'];
    .data = &(struct MenuData) {
    // PlayersPCMenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
        .setupMenu = {
            .count = 0,  // # items?
            //dw ['.WhichPC'];
            .itemList = PlayersPCMenuData_WhichPC,
            .displayFunction = PlaceNthMenuStrings_Conv,
            .labelList = PlayersPCMenuPointers,
        },
    },
    .defaultOption = 1,  // default selected option


// WhichPC:
//  entries correspond to PLAYERSPC_* constants

// PLAYERSPC_NORMAL
    //db ['5'];
    //db ['PLAYERSPCITEM_WITHDRAW_ITEM'];
    //db ['PLAYERSPCITEM_DEPOSIT_ITEM'];
    //db ['PLAYERSPCITEM_TOSS_ITEM'];
    //db ['PLAYERSPCITEM_MAIL_BOX'];
    //db ['PLAYERSPCITEM_LOG_OFF'];
    //db ['-1'];  // end

// PLAYERSPC_HOUSE
    //db ['6'];
    //db ['PLAYERSPCITEM_WITHDRAW_ITEM'];
    //db ['PLAYERSPCITEM_DEPOSIT_ITEM'];
    //db ['PLAYERSPCITEM_TOSS_ITEM'];
    //db ['PLAYERSPCITEM_MAIL_BOX'];
    //db ['PLAYERSPCITEM_DECORATION'];
    //db ['PLAYERSPCITEM_TURN_OFF'];
    //db ['-1'];  // end
};

void PC_DisplayTextWaitMenu(void){
    LD_A_addr(wOptions);
    PUSH_AF;
    SET_A(NO_TEXT_SCROLL);
    LD_addr_A(wOptions);
    CALL(aMenuTextbox);
    POP_AF;
    LD_addr_A(wOptions);
    RET;

}

void PC_DisplayTextWaitMenu_Conv(const txt_cmd_s* hl){
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_A(NO_TEXT_SCROLL);
    // LD_addr_A(wOptions);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aMenuTextbox);
    MenuTextbox_Conv(hl);
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;
}

const txt_cmd_s PlayersPCAskWhatDoText[] = {
    text_far(v_PlayersPCAskWhatDoText)
    text_end
};

static void PlayerWithdrawItemMenu_Submenu(void) {
    static const txt_cmd_s PlayersPCHowManyWithdrawText[] = {
        text_far(v_PlayersPCHowManyWithdrawText)
        text_end
    };

    static const txt_cmd_s PlayersPCWithdrewItemsText[] = {
        text_far(v_PlayersPCWithdrewItemsText)
        text_end
    };

    static const txt_cmd_s PlayersPCNoRoomWithdrawText[] = {
        text_far(v_PlayersPCNoRoomWithdrawText)
        text_end
    };
// check if the item has a quantity
    // FARCALL(av_CheckTossableItem);
    // LD_A_addr(wItemAttributeValue);
    // AND_A_A;
    // IF_Z goto askquantity;
    if(!v_CheckTossableItem_Conv(wram->wCurItem)) {
    // items without quantity are always ×1
        // LD_A(1);
        // LD_addr_A(wItemQuantityChange);
        wram->wItemQuantityChange = 1;
        // goto withdraw;
    }
    else {
    // askquantity:
        // LD_HL(mPlayerWithdrawItemMenu_PlayersPCHowManyWithdrawText);
        // CALL(aMenuTextbox);
        MenuTextbox_Conv(PlayersPCHowManyWithdrawText);
        // FARCALL(aSelectQuantityToToss);
        bool quit = SelectQuantityToToss();
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // IF_C goto done;
        if(quit)
            return;
    }

// withdraw:
    // LD_A_addr(wItemQuantityChange);
    // LD_addr_A(wPCItemQuantityChange);
    wram->wPCItemQuantityChange = wram->wItemQuantityChange;
    // LD_A_addr(wCurItemQuantity);
    // LD_addr_A(wPCItemQuantity);
    wram->wPCItemQuantity = wram->wCurItemQuantity;
    // LD_HL(wNumItems);
    // CALL(aReceiveItem);
    bool ok = ReceiveItem_Conv((item_pocket_s*)&wram->wNumItems, wram->wCurItem, wram->wCurItemQuantity);
    // IF_NC goto PackFull;
    if(!ok) {
    // PackFull:
        // LD_HL(mPlayerWithdrawItemMenu_PlayersPCNoRoomWithdrawText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(PlayersPCNoRoomWithdrawText);
        // RET;
        return;
    }
    // LD_A_addr(wPCItemQuantityChange);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = wram->wPCItemQuantityChange;
    // LD_A_addr(wPCItemQuantity);
    // LD_addr_A(wCurItemQuantity);
    wram->wCurItemQuantity = wram->wPCItemQuantity;
    // LD_HL(wNumPCItems);
    // CALL(aTossItem);
    TossItem_Conv((item_pocket_s*)&wram->wNumPCItems, wram->wCurItem);
    // PREDEF(pPartyMonItemName);
    PartyMonItemName_Conv(wram->wCurItem);
    // LD_HL(mPlayerWithdrawItemMenu_PlayersPCWithdrewItemsText);
    // CALL(aMenuTextbox);
    MenuTextbox_Conv(PlayersPCWithdrewItemsText);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
    return;

// done:
    // RET;
}

u8_flag_s PlayerWithdrawItemMenu(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // FARCALL(aClearPCItemScreen);
    ClearPCItemScreen();

    while(1) {
    // loop:
        // CALL(aPCItemsJoypad);
        bool quit = PCItemsJoypad();
        // IF_C goto quit;
        if(quit)
            break;
        // CALL(aPlayerWithdrawItemMenu_Submenu);
        PlayerWithdrawItemMenu_Submenu();
        // goto loop;
    }

// quit:
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

u8_flag_s PlayerTossItemMenu(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // FARCALL(aClearPCItemScreen);
    ClearPCItemScreen();

    while(1) {
    // loop:
        // CALL(aPCItemsJoypad);
        bool quit = PCItemsJoypad();
        // IF_C goto quit;
        if(quit)
            break;
        // LD_DE(wNumPCItems);
        // FARCALL(aTossItemFromPC);
        TossItemFromPC_Conv((item_pocket_s*)&wram->wNumPCItems);
        // goto loop;
    }


// quit:
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

u8_flag_s PlayerDecorationMenu(void){
    // FARCALL(av_PlayerDecorationMenu);
    uint8_t c = v_PlayerDecorationMenu();
    // LD_A_C;
    // AND_A_A;
    // RET_Z ;
    if(c == 0)
        return u8_flag(0, false);
    // SCF;
    // RET;
    return u8_flag(c, true);
}

u8_flag_s PlayerLogOffMenu(void){
    // XOR_A_A;
    // SCF;
    // RET;
    return u8_flag(0, true);
}

static bool PlayerDepositItemMenu_CheckItemsInBag(void) {
    static const txt_cmd_s PlayersPCNoItemsText[] = {
        text_far(v_PlayersPCNoItemsText)
        text_end
    };
    // FARCALL(aHasNoItems);
    // RET_NC ;
    if(!HasNoItems_Conv())
        return true;
    // LD_HL(mPlayerDepositItemMenu_PlayersPCNoItemsText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(PlayersPCNoItemsText);
    // SCF;
    // RET;
    return false;
}

static void PlayerDepositItemMenu_DepositItem(void) {
    static const txt_cmd_s PlayersPCHowManyDepositText[] = {
        text_far(v_PlayersPCHowManyDepositText)
        text_end
    };

    static const txt_cmd_s PlayersPCDepositItemsText[] = {
        text_far(v_PlayersPCDepositItemsText)
        text_end
    };

    static const txt_cmd_s PlayersPCNoRoomDepositText[] = {
        text_far(v_PlayersPCNoRoomDepositText)
        text_end
    };
    // FARCALL(av_CheckTossableItem);
    // LD_A_addr(wItemAttributeValue);
    // AND_A_A;
    // IF_Z goto AskQuantity;
    if(!v_CheckTossableItem_Conv(wram->wCurItem)) {
        // LD_A(1);
        // LD_addr_A(wItemQuantityChange);
        wram->wItemQuantityChange = 1;
        // goto ContinueDeposit;
    }
    else {
    // AskQuantity:
        // LD_HL(mPlayerDepositItemMenu_PlayersPCHowManyDepositText);
        // CALL(aMenuTextbox);
        MenuTextbox_Conv(PlayersPCHowManyDepositText);
        // FARCALL(aSelectQuantityToToss);
        bool quit = SelectQuantityToToss();
        // PUSH_AF;
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // POP_AF;
        // IF_C goto DeclinedToDeposit;
        if(quit) {
        // DeclinedToDeposit:
            // AND_A_A;
            // RET;
            return;
        }
    }

// ContinueDeposit:
    // LD_A_addr(wItemQuantityChange);
    // LD_addr_A(wPCItemQuantityChange);
    wram->wPCItemQuantityChange = wram->wItemQuantityChange;
    // LD_A_addr(wCurItemQuantity);
    // LD_addr_A(wPCItemQuantity);
    wram->wPCItemQuantity = wram->wCurItemQuantity;
    // LD_HL(wNumPCItems);
    // CALL(aReceiveItem);
    bool ok = ReceiveItem_Conv((item_pocket_s*)&wram->wNumPCItems, wram->wCurItem, wram->wItemQuantityChange);
    // IF_NC goto NoRoomInPC;
    if(!ok) {
    // NoRoomInPC:
        // LD_HL(mPlayerDepositItemMenu_PlayersPCNoRoomDepositText);
        // CALL(aPrintText);
        PrintText_Conv2(PlayersPCNoRoomDepositText);
        // RET;
        return;
    }
    // LD_A_addr(wPCItemQuantityChange);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = wram->wPCItemQuantityChange;
    // LD_A_addr(wPCItemQuantity);
    // LD_addr_A(wCurItemQuantity);
    wram->wCurItemQuantity = wram->wPCItemQuantity;
    // LD_HL(wNumItems);
    // CALL(aTossItem);
    TossItem_Conv((item_pocket_s*)&wram->wNumItems, wram->wCurItem);
    // PREDEF(pPartyMonItemName);
    PartyMonItemName_Conv(wram->wCurItem);
    // LD_HL(mPlayerDepositItemMenu_PlayersPCDepositItemsText);
    // CALL(aPrintText);
    PrintText_Conv2(PlayersPCDepositItemsText);
    // RET;
}

static void PlayerDepositItemMenu_TryDepositItem(void) {
    // LD_A_addr(wSpriteUpdatesEnabled);
    // PUSH_AF;
    uint8_t spriteUpdates = wram->wSpriteUpdatesEnabled;
    // LD_A(FALSE);
    // LD_addr_A(wSpriteUpdatesEnabled);
    wram->wSpriteUpdatesEnabled = FALSE;
    // FARCALL(aCheckItemMenu);
    uint8_t menu = CheckItemMenu_Conv(wram->wCurItem);
    // LD_A_addr(wItemAttributeValue);
    // LD_HL(mPlayerDepositItemMenu_dw);
    // RST(aJumpTable);
    switch(menu) {
    // dw:
    //  entries correspond to ITEMMENU_* constants
        //dw ['.tossable'];  // ITEMMENU_CURRENT
        case ITEMMENU_CURRENT:
        //dw ['.tossable'];  // ITEMMENU_PARTY
        case ITEMMENU_PARTY:
        //dw ['.tossable'];  // ITEMMENU_CLOSE
        case ITEMMENU_CLOSE:
        //dw ['.tossable'];  // ITEMMENU_NOUSE
        case ITEMMENU_NOUSE: {
        // tossable:
            // LD_A_addr(wPCItemQuantityChange);
            // PUSH_AF;
            uint8_t pcItemQuantityChange = wram->wPCItemQuantityChange;
            // LD_A_addr(wPCItemQuantity);
            // PUSH_AF;
            uint8_t pcItemQuantity = wram->wPCItemQuantity;
            // CALL(aPlayerDepositItemMenu_DepositItem);
            PlayerDepositItemMenu_DepositItem();
            // POP_AF;
            // LD_addr_A(wPCItemQuantity);
            wram->wPCItemQuantity = pcItemQuantity;
            // POP_AF;
            // LD_addr_A(wPCItemQuantityChange);
            wram->wPCItemQuantityChange = pcItemQuantityChange;
            // RET;
        } break;
        //dw ['.no_toss'];
        //dw ['.no_toss'];
        //dw ['.no_toss'];
        default:
        // no_toss:
            // RET;
            break;
    }
    // POP_AF;
    // LD_addr_A(wSpriteUpdatesEnabled);
    wram->wSpriteUpdatesEnabled = spriteUpdates;
    // RET;
    return;
}

u8_flag_s PlayerDepositItemMenu(void){
    // CALL(aPlayerDepositItemMenu_CheckItemsInBag);
    // IF_C goto nope;
    if(PlayerDepositItemMenu_CheckItemsInBag()) {
        // CALL(aDisableSpriteUpdates);
        DisableSpriteUpdates();
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader_Conv();
        // FARCALL(aDepositSellInitPackBuffers);
        DepositSellInitPackBuffers();

        while(1) {
        // loop:
            // FARCALL(aDepositSellPack);
            DepositSellPack();
            // LD_A_addr(wPackUsedItem);
            // AND_A_A;
            // IF_Z goto close;
            if(wram->wPackUsedItem == NO_ITEM)
                break;
            // CALL(aPlayerDepositItemMenu_TryDepositItem);
            PlayerDepositItemMenu_TryDepositItem();
            // FARCALL(aCheckRegisteredItem);
            CheckRegisteredItem();
            // goto loop;
        }

    // close:
        // CALL(aCloseSubmenu);
        CloseSubmenu_Conv();
    }

// nope:
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

u8_flag_s PlayerMailBoxMenu(void){
    // FARCALL(av_PlayerMailBoxMenu);
    v_PlayerMailBoxMenu();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

const struct MenuHeader PCItemsMenuData = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(4, 1, 18, 10),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags=SCROLLINGMENU_ENABLE_SELECT | SCROLLINGMENU_ENABLE_FUNCTION3 | SCROLLINGMENU_DISPLAY_ARROWS,  // flags
        .scrollingMenu = {
            .rows=4, .cols=8,  // rows, columns
            .format=SCROLLINGMENU_ITEMS_QUANTITY,  // item format
            //dbw ['0', 'wNumPCItems']
            .list = wram_ptr(wNumPCItems),
            //dba ['PlaceMenuItemName']
            .func1 = PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2 = PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3 = UpdateItemDescription,
        },
    },
    .defaultOption = 1,  // default option
};

bool PCItemsJoypad(void){
    // XOR_A_A;
    // LD_addr_A(wSwitchItem);
    wram->wSwitchItem = NO_ITEM;

    while(1) {
    // loop:
        // LD_A_addr(wSpriteUpdatesEnabled);
        // PUSH_AF;
        uint8_t spriteUpdates = wram->wSpriteUpdatesEnabled;
        // LD_A(FALSE);
        // LD_addr_A(wSpriteUpdatesEnabled);
        wram->wSpriteUpdatesEnabled = FALSE;
        // LD_HL(mPCItemsJoypad_PCItemsMenuData);
        // CALL(aCopyMenuHeader);
        CopyMenuHeader_Conv2(&PCItemsMenuData);
        // hlcoord(0, 0, wTilemap);
        // LD_B(10);
        // LD_C(18);
        // CALL(aTextbox);
        Textbox(coord(0, 0, wram->wTilemap), 10, 18);
        // LD_A_addr(wPCItemsCursor);
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = wram->wPCItemsCursor;
        // LD_A_addr(wPCItemsScrollPosition);
        // LD_addr_A(wMenuScrollPosition);
        wram->wMenuScrollPosition = wram->wPCItemsScrollPosition;
        // CALL(aScrollingMenu);
        uint8_t joypad = ScrollingMenu_Conv();
        // LD_A_addr(wMenuScrollPosition);
        // LD_addr_A(wPCItemsScrollPosition);
        wram->wPCItemsScrollPosition = wram->wMenuScrollPosition;
        // LD_A_addr(wMenuCursorY);
        // LD_addr_A(wPCItemsCursor);
        wram->wPCItemsCursor = wram->wMenuCursorY;
        // POP_AF;
        // LD_addr_A(wSpriteUpdatesEnabled);
        wram->wSpriteUpdatesEnabled = spriteUpdates;
        // LD_A_addr(wSwitchItem);
        // AND_A_A;
        // IF_NZ goto moving_stuff_around;
        if(wram->wSwitchItem != NO_ITEM) {
        // moving_stuff_around:
            // LD_A_addr(wMenuJoypad);
            // CP_A(B_BUTTON);
            // IF_Z goto b_2;
            if(joypad == B_BUTTON) {
            // b_2:
                // XOR_A_A;
                // LD_addr_A(wSwitchItem);
                wram->wSwitchItem = NO_ITEM;
                // goto next;
                continue;
            }
            // CP_A(A_BUTTON);
            // IF_Z goto a_select_2;
            // CP_A(SELECT);
            // IF_Z goto a_select_2;
            else if(joypad == A_BUTTON || joypad == SELECT) 
                goto a_select_2;
            else {
                continue;
                // goto next;
            }
        }
        else {
            // LD_A_addr(wMenuJoypad);
            // CP_A(B_BUTTON);
            // IF_Z goto b_1;
            if(joypad == B_BUTTON) {
            // b_1:
                // SCF;
                // RET;
                return true;
            }
            // CP_A(A_BUTTON);
            // IF_Z goto a_1;
            if(joypad == A_BUTTON) {
            // a_1:
                // FARCALL(aScrollingMenu_ClearLeftColumn);
                ScrollingMenu_ClearLeftColumn_Conv();
                // CALL(aPlaceHollowCursor);
                PlaceHollowCursor_Conv();
                // AND_A_A;
                // RET;
                return false;
            }
            // CP_A(SELECT);
            // IF_Z goto select_1;
            if(joypad == SELECT)
                goto select_1;
            // goto next;
            continue;
        }

    a_select_2:
        // CALL(aPC_PlaySwapItemsSound);
        PC_PlaySwapItemsSound();

    select_1:
        // FARCALL(aSwitchItemsInBag);
        SwitchItemsInBag();

    // next:
        // JP(mPCItemsJoypad_loop);
    }
}

void PC_DisplayText(void){
    CALL(aMenuTextbox);
    CALL(aExitMenu);
    RET;

}

void PC_DisplayText_Conv(const struct TextCmd* hl) {
    // CALL(aMenuTextbox);
    MenuTextbox_Conv(hl);
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
}

const txt_cmd_s PokecenterPCTurnOnText[] = {
    text_far(v_PokecenterPCTurnOnText)
    text_end
};

const txt_cmd_s PokecenterPCWhoseText[] = {
    text_far(v_PokecenterPCWhoseText)
    text_end
};

const txt_cmd_s PokecenterBillsPCText[] = {
    text_far(v_PokecenterBillsPCText)
    text_end
};

const txt_cmd_s PokecenterPlayersPCText[] = {
    text_far(v_PokecenterPlayersPCText)
    text_end
};

const txt_cmd_s PokecenterOaksPCText[] = {
    text_far(v_PokecenterOaksPCText)
    text_end
};

const txt_cmd_s PokecenterPCOaksClosedText[] = {
    text_far(v_PokecenterPCOaksClosedText)
    text_end
};
