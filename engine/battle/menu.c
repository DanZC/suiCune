#include "../../constants.h"
#include "menu.h"
#include "../../home/menu.h"
#include "../../home/print_text.h"

void LoadBattleMenu(void){
    LD_HL(mBattleMenuHeader);
    CALL(aLoadMenuHeader);
    LD_A_addr(wBattleMenuCursorPosition);
    LD_addr_A(wMenuCursorPosition);
    CALL(aInterpretBattleMenu);
    LD_A_addr(wMenuCursorPosition);
    LD_addr_A(wBattleMenuCursorPosition);
    CALL(aExitMenu);
    RET;

}

static const struct MenuHeader BattleMenuHeader = {
    .flags = MENU_BACKUP_TILES,
    .coord = menu_coords(8, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = &(struct MenuData) {
        .flags = STATICMENU_CURSOR | STATICMENU_DISABLE_B,
        .type = 0,
        ._2dMenu = {
            .rows = 2, .cols = 2,
            .spacing = 6,
            .options = (const char*[]){
                "FIGHT@",
                "<PKMN>@",
                "PACK@",
                "RUN@",
            }
        },
        .function = NULL,
    }
};

void LoadBattleMenu_Conv(void){
    // LD_HL(mBattleMenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&BattleMenuHeader);
    // LD_A_addr(wBattleMenuCursorPosition);
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wBattleMenuCursorPosition;
    // CALL(aInterpretBattleMenu);
    InterpretBattleMenu_Conv();
    // LD_A_addr(wMenuCursorPosition);
    // LD_addr_A(wBattleMenuCursorPosition);
    wram->wBattleMenuCursorPosition = wram->wMenuCursorPosition;
    // CALL(aExitMenu);
    ExitMenu_Conv();
    // RET;
}

void SafariBattleMenu(void){
//  //  unreferenced
    LD_HL(mSafariBattleMenuHeader);
    CALL(aLoadMenuHeader);
    JR(mCommonBattleMenu);

}

void ContestBattleMenu(void){
    LD_HL(mContestBattleMenuHeader);
    CALL(aLoadMenuHeader);
// fallthrough

    return CommonBattleMenu();
}

void CommonBattleMenu(void){
    LD_A_addr(wBattleMenuCursorPosition);
    LD_addr_A(wMenuCursorPosition);
    CALL(av_2DMenu);
    LD_A_addr(wMenuCursorPosition);
    LD_addr_A(wBattleMenuCursorPosition);
    CALL(aExitMenu);
    RET;

}

// void BattleMenuHeader(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['8', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


// MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_DISABLE_B'];  // flags
    //dn ['2', '2'];  // rows, columns
    //db ['6'];  // spacing
    //dba ['.Text']
    //dbw ['BANK(@)', 'NULL']


// Text:
    //db ['"FIGHT@"'];
    //db ['"<PKMN>@"'];
    //db ['"PACK@"'];
    //db ['"RUN@"'];

    // return SafariBattleMenuHeader();
// }

void SafariBattleMenuHeader(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_DISABLE_B'];  // flags
    //dn ['2', '2'];  // rows, columns
    //db ['11'];  // spacing
    //dba ['.Text']
    //dba ['.PrintSafariBallsRemaining']


Text:
    //db ['"サファりボール×\u3000\u3000@"'];  // "SAFARI BALL×  @"
    //db ['"エサをなげる@"'];  // "THROW BAIT"
    //db ['"いしをなげる@"'];  // "THROW ROCK"
    //db ['"にげる@"'];  // "RUN"


PrintSafariBallsRemaining:
    hlcoord(17, 13, wTilemap);
    LD_DE(wSafariBallsRemaining);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    RET;

}

// static void PrintParkBallsRemaining(void) {
//     // hlcoord(13, 16, wTilemap);
//     // LD_DE(wParkBallsRemaining);
//     // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
//     // CALL(aPrintNum);
//     // RET;
//     PrintNum_Conv2(coord(13, 16, wram->wTilemap), &wram->wParkBallsRemaining, PRINTNUM_LEADINGZEROS | 1, 2);
// }

// static const struct MenuHeader ContestBattleMenuHeader = {
//     .flags = MENU_BACKUP_TILES,  // flags
//     .coord = menu_coords(2, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
//     .defaultOption = 1,  // default option
//     .data = &(struct MenuData) {
//         .flags = STATICMENU_CURSOR | STATICMENU_DISABLE_B,  // flags
//         ._2dMenu = {
//             .rows=2, .cols=2,  // rows, columns
//             .spacing=12,  // spacing
//             .options = (const char*[]) {
//                 "FIGHT@",
//                 "<PKMN>@",
//                 "PARKBALL×  @",
//                 "RUN@",
//             }
//         },
//         .function = PrintParkBallsRemaining,
//     }
// };
