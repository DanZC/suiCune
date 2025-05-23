#include "../../constants.h"
#include "delete_save.h"
#include "empty_sram.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/audio.h"
#include "../../home/gfx.h"
#include "../overworld/player_object.h"
#include "../../data/text/common.h"

static const struct MenuHeader NoYesMenuHeader = {
    .flags=0,  // flags
    .coord = menu_coords(14, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
        .verticalMenu = {
            .count = 2,  // items
            .options = (const char*[]) {
                "NO@",
                "YES@",
            },
        },
    },
    .defaultOption=1,  // default option
};

void v_DeleteSaveData(void){
    static const txt_cmd_s ClearAllSaveDataText[] = {
        text_far(v_ClearAllSaveDataText)
        text_end
    };
    // FARCALL(aBlankScreen);
    BlankScreen();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_DIPLOMA);
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // LD_DE(MUSIC_MAIN_MENU);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_MAIN_MENU);
    // LD_HL(mv_DeleteSaveData_ClearAllSaveDataText);
    // CALL(aPrintText);
    PrintText(ClearAllSaveDataText);
    // LD_HL(mv_DeleteSaveData_NoYesMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&NoYesMenuHeader);
    // CALL(aVerticalMenu);
    // RET_C ;
    // LD_A_addr(wMenuCursorY);
    // CP_A(1);
    // RET_Z ;
    if(VerticalMenu() || wram->wMenuCursorY == 1)
        return;
    // FARCALL(aEmptyAllSRAMBanks);
    EmptyAllSRAMBanks();
    // RET;
}
