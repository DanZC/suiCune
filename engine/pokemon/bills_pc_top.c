#include "../../constants.h"
#include "bills_pc_top.h"
#include "bills_pc.h"
#include "mail.h"
#include "../../home/copy.h"
#include "../../home/sram.h"
#include "../../home/clear_sprites.h"
#include "../../home/tilemap.h"
#include "../../home/sprite_updates.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/gfx.h"
#include "../../home/map.h"
#include "../../util/serialize.h"
#include "../menus/save.h"
#include "../../data/text/common.h"

static bool v_BillsPC_Jumptable(uint8_t sel);

static bool v_BillsPC_CheckCanUsePC(void) {
    static const txt_cmd_s PCGottaHavePokemonText[] = {
        text_far(v_PCGottaHavePokemonText)
        text_end
    };
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_NZ ;
    if(gPokemon.partyCount != 0)
        return true;
    // LD_HL(mv_BillsPC_PCGottaHavePokemonText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup(PCGottaHavePokemonText);
    // SCF;
    // RET;
    return false;
}

static void v_BillsPC_LogIn(void) {
    static txt_cmd_s PCWhatText[] = {
        text_far(v_PCWhatText)
        text_end
    };
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aClearPCItemScreen);
    ClearPCItemScreen();
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = gOptions.options;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // LD_HL(mv_BillsPC_PCWhatText);
    // CALL(aPrintText);
    PrintText(PCWhatText);
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra();
    // RET;
}

static void v_BillsPC_LogOut(void) {
    // CALL(aCloseSubmenu);
    CloseSubmenu();
    // RET;
}

static const struct MenuHeader v_BillsPC_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR,  // flags
        .setupMenu = {
            .count = 0,  // items
            //dw ['.items'];
            .itemList = (const uint8_t*[]) {
                (const uint8_t[]){
                    5,  // # items
                    0,  // WITHDRAW
                    1,  // DEPOSIT
                    2,  // CHANGE BOX
                    3,  // MOVE PKMN
                    4,  // SEE YA!
                    (uint8_t)-1,
                }
            },
            //dw ['PlaceMenuStrings'];
            .displayFunction = PlaceMenuStrings,
            //dw ['.strings'];
            .stringsList = (const char*[]) {
            // strings:
                "WITHDRAW <PK><MN>@",
                "DEPOSIT <PK><MN>@",
                "CHANGE BOX@",
                "MOVE <PK><MN> W/O MAIL@",
                "SEE YA!@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

static void v_BillsPC_UseBillsPC(void) {
    // LD_HL(mv_BillsPC_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&v_BillsPC_MenuHeader);
    // LD_A(0x1);
    uint8_t a = 0x1;

    bool quit;
    do {
    // loop:
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = a;
        // CALL(aSetPalettes);
        // XOR_A_A;
        // LD_addr_A(wWhichIndexSet);
        wram->wWhichIndexSet = 0;
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_NONE;
        // CALL(aDoNthMenu);
        u8_flag_s menuRes = DoNthMenu();
        // IF_C goto cancel;
        if(menuRes.flag)
            break;
        // LD_A_addr(wMenuCursorPosition);
        // PUSH_AF;
        a = wram->wMenuCursorPosition;
        // LD_A_addr(wMenuSelection);
        // LD_HL(mv_BillsPC_Jumptable);
        // RST(aJumpTable);
        quit = v_BillsPC_Jumptable(wram->wMenuSelection);
        // POP_BC;
        // LD_A_B;
        // IF_NC goto loop;
    } while(!quit);

// cancel:
    // CALL(aCloseWindow);
    CloseWindow();
    // RET;
}

void v_BillsPC(void){
    // CALL(av_BillsPC_CheckCanUsePC);
    // RET_C ;
    if(!v_BillsPC_CheckCanUsePC())
        return;
    // CALL(av_BillsPC_LogIn);
    v_BillsPC_LogIn();
    // CALL(av_BillsPC_UseBillsPC);
    v_BillsPC_UseBillsPC();
    // JP(mv_BillsPC_LogOut);
    return v_BillsPC_LogOut();
}

static bool v_BillsPC_Jumptable(uint8_t sel) {
    switch(sel) {
    case 0:
        //dw ['BillsPC_WithdrawMenu'];
        return BillsPC_WithdrawMenu();
    case 1:
    //     //dw ['BillsPC_DepositMenu'];
        return BillsPC_DepositMenu();
    case 2:
        //dw ['BillsPC_ChangeBoxMenu'];
        return BillsPC_ChangeBoxMenu();
    case 3:
    //     //dw ['BillsPC_MovePKMNMenu'];
        // return BillsPC_MovePKMNMenu();
    default:
        //dw ['BillsPC_SeeYa'];
        return BillsPC_SeeYa();
    }
}

bool BillsPC_SeeYa(void){
    // SCF;
    // RET;
    return true;
}

bool BillsPC_MovePKMNMenu(void){
    static const txt_cmd_s PCMonHoldingMailText[] = {
        text_far(v_PCMonHoldingMailText)
        text_end
    };
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // FARCALL(aIsAnyMonHoldingMail);
    // IF_NC goto no_mail;
    if(IsAnyMonHoldingMail()) {
        // LD_HL(mBillsPC_MovePKMNMenu_PCMonHoldingMailText);
        // CALL(aPrintText);
        PrintText(PCMonHoldingMailText);
        // goto quit;
    }
    else {
    // no_mail:
        // FARCALL(aStartMoveMonWOMail_SaveGame);
        // IF_C goto quit;
        if(StartMoveMonWOMail_SaveGame()) {
            // FARCALL(av_MovePKMNWithoutMail);
            v_MovePKMNWithoutMail();
            // CALL(aReturnToMapFromSubmenu);
            ReturnToMapFromSubmenu();
            // CALL(aClearPCItemScreen);
            ClearPCItemScreen();
        }
    }

// quit:
    // CALL(aCloseWindow);
    CloseWindow();
    // AND_A_A;
    // RET;
    return false;
}

bool BillsPC_DepositMenu(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // FARCALL(av_DepositPKMN);
    v_DepositPKMN();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // CALL(aClearPCItemScreen);
    ClearPCItemScreen();
    // CALL(aCloseWindow);
    CloseWindow();
    // AND_A_A;
    // RET;
    return false;
}

void BillsPC_Deposit_CheckPartySize(void){
//  //  unreferenced
    LD_A_addr(wPartyCount);
    AND_A_A;
    IF_Z goto no_mon;
    CP_A(2);
    IF_C goto only_one_mon;
    AND_A_A;
    RET;


no_mon:
    LD_HL(mBillsPC_Deposit_CheckPartySize_PCNoSingleMonText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;


only_one_mon:
    LD_HL(mBillsPC_Deposit_CheckPartySize_PCCantDepositLastMonText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;


// PCNoSingleMonText:
    //text_far ['_PCNoSingleMonText']
    //text_end ['?']


// PCCantDepositLastMonText:
    //text_far ['_PCCantDepositLastMonText']
    //text_end ['?']

    // return CheckCurPartyMonFainted();
}

bool CheckCurPartyMonFainted(void){
    if(wram->wCurPartyMon >= gPokemon.partyCount)
        return true;
    // LD_HL(wPartyMon1HP);
    struct PartyMon* hl = gPokemon.partyMon;
    // LD_DE(PARTYMON_STRUCT_LENGTH);
    // LD_B(0x0);
    uint8_t b = 0x0;

    do {
    // loop:
        // LD_A_addr(wCurPartyMon);
        // CP_A_B;
        // IF_Z goto skip;
        if(wram->wCurPartyMon != b) {
            // LD_A_hli;
            // OR_A_hl;
            // IF_NZ goto notfainted;
            if(hl[b].HP != 0) {
            // notfainted:
                // AND_A_A;
                // RET;
                return false;
            }
            // DEC_HL;
        }

    // skip:
        // INC_B;
        // LD_A_addr(wPartyCount);
        // CP_A_B;
        // IF_Z goto done;
        // ADD_HL_DE;
        // goto loop;
    } while(++b != gPokemon.partyCount);

// done:
    // SCF;
    // RET;
    return true;
}

bool BillsPC_WithdrawMenu(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // FARCALL(av_WithdrawPKMN);
    v_WithdrawPKMN();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // CALL(aClearPCItemScreen);
    ClearPCItemScreen();
    // CALL(aCloseWindow);
    CloseWindow();
    // AND_A_A;
    // RET;
    return false;
}

void BillsPC_Withdraw_CheckPartySize(void){
//  //  unreferenced
    LD_A_addr(wPartyCount);
    CP_A(PARTY_LENGTH);
    IF_NC goto party_full;
    AND_A_A;
    RET;


party_full:
    LD_HL(mPCCantTakeText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;

}

void PCCantTakeText(void){
    //text_far ['_PCCantTakeText']
    //text_end ['?']
}

bool BillsPC_ChangeBoxMenu(void){
    // FARCALL(av_ChangeBox);
    v_ChangeBox();
    // AND_A_A;
    // RET;
    return false;
}

void ClearPCItemScreen(void){
    // CALL(aDisableSpriteUpdates);
    // XOR_A_A;
    DisableSpriteUpdates();
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x7f);
    // hlcoord(0, 0, wTilemap);
    // LD_BC((10 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 0, wram->wTilemap), 10, 18);
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 4, 18);
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // CALL(aSetPalettes);  // load regular palettes?
    SetPalettes();
    // RET;
}

void CopyBoxmonToTempMon(void){
    struct Box box;
    // LD_A_addr(wCurPartyMon);
    // LD_HL(sBoxMon1Species);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_DE(wTempMonSpecies);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // LD_A(BANK(sBoxMon1Species));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxMon1Species));
    Deserialize_Box(&box, GBToRAMAddr(sBox));
    // CALL(aCopyBytes);
    CopyBytes(&wram->wTempMon.mon, box.mons + wram->wCurPartyMon, sizeof(box.mons[0]));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void LoadBoxMonListing(void){
//  //  unreferenced
    LD_A_addr(wCurBox);
    CP_A_B;
    IF_Z goto same_box;
    LD_A_B;
    LD_HL(mLoadBoxMonListing_BoxAddresses);
    LD_BC(3);
    CALL(aAddNTimes);
    LD_A_hli;
    PUSH_AF;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_AF;
    goto okay;


same_box:
    LD_A(BANK(sBoxCount));
    LD_HL(sBoxCount);


okay:
    CALL(aOpenSRAM);
    LD_A_hl;
    LD_BC(sBoxMons - sBox);
    ADD_HL_BC;
    LD_B_A;
    LD_C(0x0);
    LD_DE(wBoxPartialData);
    LD_A_B;
    AND_A_A;
    IF_Z goto empty_box;

loop:
    PUSH_HL;
    PUSH_BC;
    LD_A_C;
    LD_BC(sBoxMon1Species - sBoxMons);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hl;
    LD_de_A;
    INC_DE;
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    POP_BC;
    POP_HL;

    PUSH_HL;
    PUSH_BC;
    LD_A_C;
    LD_BC(sBoxMonNicknames - sBoxMons);
    ADD_HL_BC;
    CALL(aSkipNames);
    CALL(aCopyBytes);
    POP_BC;
    POP_HL;

    PUSH_HL;
    PUSH_BC;
    LD_A_C;
    LD_BC(MON_LEVEL);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hl;
    LD_de_A;
    INC_DE;
    POP_BC;
    POP_HL;

    PUSH_HL;
    PUSH_BC;
    LD_A_C;
    LD_BC(MON_DVS);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_hli;
    AND_A(0xf0);
    LD_B_A;
    LD_A_hl;
    AND_A(0xf0);
    SWAP_A;
    OR_A_B;
    LD_B_A;
    LD_A_addr(wBaseGender);
    CP_A_B;
    LD_A(0x1);
    IF_C goto okay2;
    XOR_A_A;

okay2:
    LD_de_A;
    INC_DE;
    POP_BC;
    POP_HL;

    INC_C;
    DEC_B;
    IF_NZ goto loop;

empty_box:
    CALL(aCloseSRAM);
    RET;


//BoxAddresses:
    //table_width ['3', 'LoadBoxMonListing.BoxAddresses']
    //dba ['sBox1']
    //dba ['sBox2']
    //dba ['sBox3']
    //dba ['sBox4']
    //dba ['sBox5']
    //dba ['sBox6']
    //dba ['sBox7']
    //dba ['sBox8']
    //dba ['sBox9']
    //dba ['sBox10']
    //dba ['sBox11']
    //dba ['sBox12']
    //dba ['sBox13']
    //dba ['sBox14']
    //assert_table_length ['NUM_BOXES']

}
