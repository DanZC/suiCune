#include "../../constants.h"
#include "decorations.h"
#include "../../home/names.h"
#include "../../home/copy_name.h"
#include "../../home/map.h"
#include "../../home/flag.h"
#include "../../home/menu.h"
#include "../../home/copy.h"
#include "../../home/scrolling_menu.h"
#include "../../home/text.h"
#include "../../data/decorations/attributes.h"
#include "../../data/decorations/decorations.h"
#include "../../data/decorations/names.h"
#include "../../data/text/common.h"
#include "../../util/scripting.h"

void InitDecorations(void){
    // LD_A(DECO_FEATHERY_BED);
    // LD_addr_A(wDecoBed);
    wram->wDecoBed = DECO_FEATHERY_BED;
    // LD_A(DECO_TOWN_MAP);
    // LD_addr_A(wDecoPoster);
    wram->wDecoPoster = DECO_TOWN_MAP;
    // RET;
}

static void DecorationMenuFunction2(const struct MenuData* data, tile_t* de);

static const struct LabeledMenuItem v_PlayerDecorationMenu_category_pointers[] = {
    //table_width ['2 + 2', '_PlayerDecorationMenu.category_pointers']
    {DecoBedMenu, "BED"},
    {DecoCarpetMenu, "CARPET"},
    {DecoPlantMenu, "PLANT"},
    {DecoPosterMenu, "POSTER"},
    {DecoConsoleMenu, "GAME CONSOLE"},
    {DecoOrnamentMenu, "ORNAMENT"},
    {DecoBigDollMenu, "BIG DOLL"},
    {DecoExitMenu, "EXIT"},
};
static_assert(lengthof(v_PlayerDecorationMenu_category_pointers) == NUM_DECO_CATEGORIES + 1, "");

static const struct MenuHeader v_PlayerDecorationMenu_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(5, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
        .setupMenu = {
            .count = 0,  // items
            .itemList = (const uint8_t*[]) { wram_ptr(wNumOwnedDecoCategories) },
            .displayFunction = PlaceNthMenuStrings_Conv,
            .labelList = v_PlayerDecorationMenu_category_pointers,
        },
    },
    .defaultOption = 1,  // default option
};

struct OwnedPointer {
    bool (*function)(void);
    uint8_t n;
};

static void v_PlayerDecorationMenu_ClearStringBuffer2(void){
    // LD_HL(wStringBuffer2);
    // XOR_A_A;
    // LD_hli_A;
    wram->wStringBuffer2[0] = 0;
    // LD_BC(ITEM_NAME_LENGTH - 1);
    // LD_A(-1);
    // CALL(aByteFill);
    ByteFill(wram->wStringBuffer2 + 1, ITEM_NAME_LENGTH - 1, 0xff);
    // RET;
}

static void v_PlayerDecorationMenu_AppendToStringBuffer2(uint8_t a){
    // LD_HL(wStringBuffer2);
    // INC_hl;
    uint8_t l = ++wram->wStringBuffer2[0];
    // LD_E_hl;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_hl_A;
    wram->wStringBuffer2[l] = a;
    // RET;
}

static void v_PlayerDecorationMenu_FindOwnedDecos(void){
    static const struct OwnedPointer owned_pointers[] = {
        //table_width ['3', '_PlayerDecorationMenu.owned_pointers']
        {FindOwnedBeds, 0},  // bed
        {FindOwnedCarpets, 1},  // carpet
        {FindOwnedPlants, 2},  // plant
        {FindOwnedPosters, 3},  // poster
        {FindOwnedConsoles, 4},  // game console
        {FindOwnedOrnaments, 5},  // ornament
        {FindOwnedBigDolls, 6},  // big doll
        //dw ['0'];  // end
        {0},
    };
    static_assert(lengthof(owned_pointers) == NUM_DECO_CATEGORIES + 1, "");
    // LD_HL(mv_PlayerDecorationMenu_owned_pointers);
    const struct OwnedPointer* hl = owned_pointers;

    while(hl->function != NULL) {
    // loop:
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        // OR_A_E;
        // IF_Z goto done;
        // PUSH_HL;
        // CALL(av_de_);
        // POP_HL;
        // IF_NC goto next;
        if(hl->function()) {
            // LD_A_hl;
            // PUSH_HL;
            // CALL(av_PlayerDecorationMenu_AppendToStringBuffer2);
            v_PlayerDecorationMenu_AppendToStringBuffer2(hl->n);
            // POP_HL;
        }

    // next:
        // INC_HL;
        hl++;
        // goto loop;
    }

// done:
    // RET;
}

static void v_PlayerDecorationMenu_FindCategoriesWithOwnedDecos(void){
    // XOR_A_A;
    // LD_addr_A(wWhichIndexSet);
    wram->wWhichIndexSet = 0;
    // CALL(av_PlayerDecorationMenu_ClearStringBuffer2);
    v_PlayerDecorationMenu_ClearStringBuffer2();
    // CALL(av_PlayerDecorationMenu_FindOwnedDecos);
    v_PlayerDecorationMenu_FindOwnedDecos();
    // LD_A(7);
    // CALL(av_PlayerDecorationMenu_AppendToStringBuffer2);
    v_PlayerDecorationMenu_AppendToStringBuffer2(7);
    // LD_HL(wStringBuffer2);
    // LD_DE(wDecoNameBuffer);
    // LD_BC(ITEM_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wDecoNameBuffer, wram->wStringBuffer2, ITEM_NAME_LENGTH);
    // RET;
}

uint8_t v_PlayerDecorationMenu(void){
    // LD_A_addr(wWhichIndexSet);
    // PUSH_AF;
    uint8_t index = wram->wWhichIndexSet;
    // LD_HL(mv_PlayerDecorationMenu_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&v_PlayerDecorationMenu_MenuHeader);
    // XOR_A_A;  // FALSE
    // LD_addr_A(wChangedDecorations);
    wram->wChangedDecorations = FALSE;
    // LD_A(0x1);  // bed
    // LD_addr_A(wCurDecorationCategory);
    wram->wCurDecorationCategory = 0x1;

    u8_flag_s res;
    do {
    // top_loop:
        // LD_A_addr(wCurDecorationCategory);
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = wram->wCurDecorationCategory;
        // CALL(av_PlayerDecorationMenu_FindCategoriesWithOwnedDecos);
        v_PlayerDecorationMenu_FindCategoriesWithOwnedDecos();
        // CALL(aDoNthMenu);
        res = DoNthMenu_Conv();
        // LD_A_addr(wMenuCursorY);
        // LD_addr_A(wCurDecorationCategory);
        wram->wCurDecorationCategory = wram->wMenuCursorY;
        // IF_C goto exit_menu;
        if(res.flag)
            break;
        // LD_A_addr(wMenuSelection);
        // LD_HL(mv_PlayerDecorationMenu_category_pointers);
        // CALL(aMenuJumptable);
        res = MenuJumptable_Conv();
        // IF_NC goto top_loop;
    } while(!res.flag);

// exit_menu:
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // POP_AF;
    // LD_addr_A(wWhichIndexSet);
    wram->wWhichIndexSet = index;
    // LD_A_addr(wChangedDecorations);
    // LD_C_A;
    // RET;
    return wram->wChangedDecorations;
}

void Deco_FillTempWithMinusOne(void){
    // XOR_A_A;
    // LD_HL(wNumOwnedDecoCategories);
    // LD_hli_A;
    wram->wNumOwnedDecoCategories = 0x0;
    //assert ['wNumOwnedDecoCategories + 1 == wOwnedDecoCategories'];
    // LD_A(-1);
    // LD_BC(16);
    // CALL(aByteFill);
    ByteFill(wram->wOwnedDecoCategories, sizeof(wram->wOwnedDecoCategories), 0xff);
    // RET;
}

void CheckAllDecorationFlags(const uint8_t* hl){
    while(1) {
    // loop:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff)
            break;
        // PUSH_HL;
        // PUSH_AF;
        // LD_B(CHECK_FLAG);
        // CALL(aDecorationFlagAction);
        uint8_t c = DecorationFlagAction(a, CHECK_FLAG);
        // LD_A_C;
        // AND_A_A;
        // POP_BC;
        // LD_A_B;
        // CALL_NZ (aAppendDecoIndex);
        if(c != 0) {
            AppendDecoIndex(a);
        }
        // POP_HL;
        // goto loop;
    }

// done:
    // RET;
}

void AppendDecoIndex(uint8_t a){
    // LD_HL(wNumOwnedDecoCategories);
    // INC_hl;
    uint8_t l = wram->wNumOwnedDecoCategories++;
    //assert ['wNumOwnedDecoCategories + 1 == wOwnedDecoCategories'];
    // LD_E_hl;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_hl_A;
    wram->wOwnedDecoCategories[l] = a;
    // RET;
}

bool FindOwnedDecosInCategory(const uint8_t* hl, uint8_t c){
    // PUSH_BC;
    // PUSH_HL;
    // CALL(aDeco_FillTempWithMinusOne);
    Deco_FillTempWithMinusOne();
    // POP_HL;
    // CALL(aCheckAllDecorationFlags);
    CheckAllDecorationFlags(hl);
    // POP_BC;
    // LD_A_addr(wNumOwnedDecoCategories);
    // AND_A_A;
    // RET_Z ;
    if(wram->wNumOwnedDecoCategories == 0)
        return false;

    // LD_A_C;
    // CALL(aAppendDecoIndex);
    AppendDecoIndex(c);
    // LD_A(0);
    // CALL(aAppendDecoIndex);
    AppendDecoIndex(0);
    // SCF;
    // RET;
    return true;
}

u8_flag_s DecoBedMenu(void){
    // CALL(aFindOwnedBeds);
    FindOwnedBeds();
    // CALL(aPopulateDecoCategoryMenu);
    PopulateDecoCategoryMenu();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

bool FindOwnedBeds(void){
    static const uint8_t beds[] = {
        DECO_FEATHERY_BED,  // 2
        DECO_PINK_BED,  // 3
        DECO_POLKADOT_BED,  // 4
        DECO_PIKACHU_BED,  // 5
        -1,
    };
    // LD_HL(mFindOwnedBeds_beds);
    // LD_C(BEDS);
    // JP(mFindOwnedDecosInCategory);
    return FindOwnedDecosInCategory(beds, BEDS);
}

u8_flag_s DecoCarpetMenu(void){
    // CALL(aFindOwnedCarpets);
    FindOwnedCarpets();
    // CALL(aPopulateDecoCategoryMenu);
    PopulateDecoCategoryMenu();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

bool FindOwnedCarpets(void){
    static const uint8_t carpets[] = {
        DECO_RED_CARPET,  // 7
        DECO_BLUE_CARPET,  // 8
        DECO_YELLOW_CARPET,  // 9
        DECO_GREEN_CARPET,  // a
        -1,
    };
    // LD_HL(mFindOwnedCarpets_carpets);
    // LD_C(CARPETS);
    // JP(mFindOwnedDecosInCategory);
    return FindOwnedDecosInCategory(carpets, CARPETS);
}

u8_flag_s DecoPlantMenu(void){
    // CALL(aFindOwnedPlants);
    FindOwnedPlants();
    // CALL(aPopulateDecoCategoryMenu);
    PopulateDecoCategoryMenu();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

bool FindOwnedPlants(void){
    static const uint8_t plants[] = {
        DECO_MAGNAPLANT,  // c
        DECO_TROPICPLANT,  // d
        DECO_JUMBOPLANT,  // e
        -1,
    };
    // LD_HL(mFindOwnedPlants_plants);
    // LD_C(PLANTS);
    // JP(mFindOwnedDecosInCategory);
    return FindOwnedDecosInCategory(plants, PLANTS);
}

u8_flag_s DecoPosterMenu(void){
    // CALL(aFindOwnedPosters);
    FindOwnedPosters();
    // CALL(aPopulateDecoCategoryMenu);
    PopulateDecoCategoryMenu();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

bool FindOwnedPosters(void){
    static const uint8_t posters[] = {
        DECO_TOWN_MAP,  // 10
        DECO_PIKACHU_POSTER,  // 11
        DECO_CLEFAIRY_POSTER,  // 12
        DECO_JIGGLYPUFF_POSTER,  // 13
        -1,
    };
    // LD_HL(mFindOwnedPosters_posters);
    // LD_C(POSTERS);
    // JP(mFindOwnedDecosInCategory);
    return FindOwnedDecosInCategory(posters, POSTERS);
}

u8_flag_s DecoConsoleMenu(void){
    // CALL(aFindOwnedConsoles);
    FindOwnedConsoles();
    // CALL(aPopulateDecoCategoryMenu);
    PopulateDecoCategoryMenu();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

bool FindOwnedConsoles(void){
    static const uint8_t consoles[] = {
        DECO_FAMICOM,  // 15
        DECO_SNES,  // 16
        DECO_N64,  // 17
        DECO_VIRTUAL_BOY,  // 18
        -1,
    };
    // LD_HL(mFindOwnedConsoles_consoles);
    // LD_C(CONSOLES);
    // JP(mFindOwnedDecosInCategory);
    return FindOwnedDecosInCategory(consoles, CONSOLES);
}

u8_flag_s DecoOrnamentMenu(void){
    // CALL(aFindOwnedOrnaments);
    FindOwnedOrnaments();
    // CALL(aPopulateDecoCategoryMenu);
    PopulateDecoCategoryMenu();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

bool FindOwnedOrnaments(void){
    static const uint8_t ornaments[] = {
        DECO_PIKACHU_DOLL,  // 1e
        DECO_SURF_PIKACHU_DOLL,  // 1f
        DECO_CLEFAIRY_DOLL,  // 20
        DECO_JIGGLYPUFF_DOLL,  // 21
        DECO_BULBASAUR_DOLL,  // 22
        DECO_CHARMANDER_DOLL,  // 23
        DECO_SQUIRTLE_DOLL,  // 24
        DECO_POLIWAG_DOLL,  // 25
        DECO_DIGLETT_DOLL,  // 26
        DECO_STARMIE_DOLL,  // 27
        DECO_MAGIKARP_DOLL,  // 28
        DECO_ODDISH_DOLL,  // 29
        DECO_GENGAR_DOLL,  // 2a
        DECO_SHELLDER_DOLL,  // 2b
        DECO_GRIMER_DOLL,  // 2c
        DECO_VOLTORB_DOLL,  // 2d
        DECO_WEEDLE_DOLL,  // 2e
        DECO_UNOWN_DOLL,  // 2f
        DECO_GEODUDE_DOLL,  // 30
        DECO_MACHOP_DOLL,  // 31
        DECO_TENTACOOL_DOLL,  // 32
        DECO_GOLD_TROPHY_DOLL,  // 33
        DECO_SILVER_TROPHY_DOLL,  // 34
        -1,
    };
    // LD_HL(mFindOwnedOrnaments_ornaments);
    // LD_C(DOLLS);
    // JP(mFindOwnedDecosInCategory);
    return FindOwnedDecosInCategory(ornaments, DOLLS);
}

u8_flag_s DecoBigDollMenu(void){
    // CALL(aFindOwnedBigDolls);
    FindOwnedBigDolls();
    // CALL(aPopulateDecoCategoryMenu);
    PopulateDecoCategoryMenu();
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

bool FindOwnedBigDolls(void){
    static const uint8_t big_dolls[] = {
        DECO_BIG_SNORLAX_DOLL,  // 1a
        DECO_BIG_ONIX_DOLL,  // 1b
        DECO_BIG_LAPRAS_DOLL,  // 1c
        -1,
    };
    // LD_HL(mFindOwnedBigDolls_big_dolls);
    // LD_C(BIG_DOLLS);
    // JP(mFindOwnedDecosInCategory);
    return FindOwnedDecosInCategory(big_dolls, BIG_DOLLS);
}

u8_flag_s DecoExitMenu(void){
    // SCF;
    // RET;
    return u8_flag(0, true);
}

static const struct MenuHeader NonscrollingMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = &(struct MenuData){ //dw ['.NonscrollingMenuData'];
    // NonscrollingMenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
        .setupMenu = {
            .count = 0,  // items
            .itemList = (const uint8_t*[]) { wram_ptr(wDecoNameBuffer) },
            .displayFunction = DecorationMenuFunction,
            //dw ['DecorationAttributes'];
        },
    },
    .defaultOption = 1,  // default option
};

static const struct MenuHeader ScrollingMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(1, 1, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2),
    //dw ['.ScrollingMenuData'];
    .data = &(struct MenuData) {
    // ScrollingMenuData:
        .flags = SCROLLINGMENU_DISPLAY_ARROWS,  // flags
        .scrollingMenu = {
            .rows = 8, .cols = 0,  // rows, columns
            .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
            .list = wram_ptr(wNumOwnedDecoCategories),
            .func1 = DecorationMenuFunction2,
            .func2 = NULL,
            .func3 = NULL,
        },
    },
    .defaultOption = 1,  // default option
};

void PopulateDecoCategoryMenu(void){
    static const txt_cmd_s NothingToChooseText[] = {
        text_far(v_NothingToChooseText)
        text_end
    };
    // LD_A_addr(wNumOwnedDecoCategories);
    // AND_A_A;
    // IF_Z goto empty;
    if(wram->wNumOwnedDecoCategories == 0) {
    // empty:
        // LD_HL(mPopulateDecoCategoryMenu_NothingToChooseText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(NothingToChooseText);
        // RET;
        return;
    }
    // CP_A(8);
    // IF_NC goto beyond_eight;
    else if(wram->wNumOwnedDecoCategories < 8) {
        // XOR_A_A;
        // LD_addr_A(wWhichIndexSet);
        wram->wWhichIndexSet = 0x0;
        // LD_HL(mPopulateDecoCategoryMenu_NonscrollingMenuHeader);
        // CALL(aLoadMenuHeader);
        LoadMenuHeader_Conv2(&NonscrollingMenuHeader);
        // CALL(aDoNthMenu);
        u8_flag_s res = DoNthMenu_Conv();
        // IF_C goto no_action_1;
        if(!res.flag) {
            // CALL(aDoDecorationAction2);
            DoDecorationAction2();
        }

    // no_action_1:
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // RET;
        return;
    }

// beyond_eight:
    // LD_HL(wNumOwnedDecoCategories);
    // LD_E_hl;
    // DEC_hl;
    uint8_t e = --wram->wNumOwnedDecoCategories;
    //assert ['wNumOwnedDecoCategories + 1 == wOwnedDecoCategories'];
    // LD_D(0);
    // ADD_HL_DE;
    // LD_hl(-1);
    wram->wOwnedDecoCategories[e] = 0xff;
    // CALL(aLoadStandardMenuHeader);
    // LD_HL(mPopulateDecoCategoryMenu_ScrollingMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&ScrollingMenuHeader);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aInitScrollingMenu);
    InitScrollingMenu_Conv();
    // XOR_A_A;
    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = 0x0;
    // CALL(aScrollingMenu);
    ScrollingMenu_Conv();
    // LD_A_addr(wMenuJoypad);
    // CP_A(2);
    // IF_Z goto no_action_2;
    if(wram->wMenuJoypad != 2) {
        // CALL(aDoDecorationAction2);
        DoDecorationAction2();
    }

// no_action_2:
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
}

void GetDecorationData(void){
    LD_HL(mDecorationAttributes);
    LD_BC(DECOATTR_STRUCT_LENGTH);
    CALL(aAddNTimes);
    RET;

}

const struct Decoration* GetDecorationData_Conv(uint8_t a){
    // LD_HL(mDecorationAttributes);
    // LD_BC(DECOATTR_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // RET;
    return DecorationAttributes + a + 1;
}

void GetDecorationName(void){
    PUSH_HL;
    CALL(aGetDecorationData);
    CALL(aGetDecoName);
    POP_HL;
    CALL(aCopyName2);
    RET;

}

void GetDecorationName_Conv(uint8_t* hl, uint8_t a){
    // PUSH_HL;
    // CALL(aGetDecorationData);
    const struct Decoration* deco = GetDecorationData_Conv(a);
    // CALL(aGetDecoName);
    const uint8_t* de = GetDecoName_Conv(deco);
    // POP_HL;
    // CALL(aCopyName2);
    CopyName2(hl, de);
    // RET;
}

void DecorationMenuFunction(const char** str, uint8_t* de, uint8_t a){
    (void)str;
    // LD_A_addr(wMenuSelection);
    // PUSH_DE;
    // CALL(aGetDecorationData);
    const struct Decoration* deco = GetDecorationData_Conv(a);
    // CALL(aGetDecoName);
    uint8_t* s = (uint8_t*)GetDecoName_Conv(deco);
    // POP_HL;
    // CALL(aPlaceString);
    // RET;
    PlaceStringSimple(s, de);
}

static void DecorationMenuFunction2(const struct MenuData* data, tile_t* de){
    (void)data;
    const struct Decoration* deco = GetDecorationData_Conv(wram->wMenuSelection);
    uint8_t* s = (uint8_t*)GetDecoName_Conv(deco);
    PlaceStringSimple(s, de);
}

void DoDecorationAction2(void){
    // LD_A_addr(wMenuSelection);
    // CALL(aGetDecorationData);
    const struct Decoration* deco = GetDecorationData_Conv(wram->wMenuSelection);
    // LD_DE(DECOATTR_ACTION);
    // ADD_HL_DE;
    // LD_A_hl;
    uint8_t action = deco->action;
    // LD_HL(mDoDecorationAction2_DecoActions);
    // RST(aJumpTable);
    // RET;

// DecoActions:
    //table_width ['2', 'DoDecorationAction2.DecoActions']
    switch(action) {
        case 0:                 return DecoAction_nothing();
        case SET_UP_BED:        return DecoAction_setupbed();
        case PUT_AWAY_BED:      return DecoAction_putawaybed();
        case SET_UP_CARPET:     return DecoAction_setupcarpet();
        case PUT_AWAY_CARPET:   return DecoAction_putawaycarpet();
        case SET_UP_PLANT:      return DecoAction_setupplant();
        case PUT_AWAY_PLANT:    return DecoAction_putawayplant();
        case SET_UP_POSTER:     return DecoAction_setupposter();
        case PUT_AWAY_POSTER:   return DecoAction_putawayposter();
        case SET_UP_CONSOLE:    return DecoAction_setupconsole();
        case PUT_AWAY_CONSOLE:  return DecoAction_putawayconsole();
        case SET_UP_BIG_DOLL:   return DecoAction_setupbigdoll();
        case PUT_AWAY_BIG_DOLL: return DecoAction_putawaybigdoll();
        case SET_UP_DOLL:       return DecoAction_setupornament();
        case PUT_AWAY_DOLL:     return DecoAction_putawayornament();
    }
    //assert_table_length ['NUM_DECO_ACTIONS + 1']
}

uint16_t GetDecorationFlag(uint8_t c){
    // CALL(aGetDecorationData);
    const struct Decoration* hl = GetDecorationData_Conv(c);
    // LD_DE(DECOATTR_EVENT_FLAG);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // RET;
    return hl->event_flag;
}

uint8_t DecorationFlagAction(uint8_t c, uint8_t b){
    // PUSH_BC;
    // CALL(aGetDecorationFlag);
    // POP_BC;
    // CALL(aEventFlagAction);
    return EventFlagAction(GetDecorationFlag(c), b);
    // RET;
}

void GetDecorationSprite(void){
    LD_A_C;
    CALL(aGetDecorationData);
    LD_DE(DECOATTR_SPRITE);
    ADD_HL_DE;
    LD_A_hl;
    LD_C_A;
    RET;

// INCLUDE "data/decorations/attributes.asm"

// INCLUDE "data/decorations/names.asm"
}

uint8_t GetDecorationSprite_Conv(uint8_t c){
    // LD_A_C;
    // CALL(aGetDecorationData);
    const struct Decoration* hl = GetDecorationData_Conv(c);
    // LD_DE(DECOATTR_SPRITE);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_C_A;
    // RET;
    return hl->tile;
}

void GetDecoName(void){
    LD_A_hli;  // DECOATTR_TYPE
    LD_E_hl;  // DECOATTR_NAME
    LD_BC(wStringBuffer2);
    PUSH_BC;
    LD_HL(mGetDecoName_NameFunctions);
    RST(aJumpTable);
    POP_DE;
    RET;


NameFunctions:
    //table_width ['2', 'GetDecoName.NameFunctions']
    //dw ['.invalid'];
    //dw ['.plant'];
    //dw ['.bed'];
    //dw ['.carpet'];
    //dw ['.poster'];
    //dw ['.doll'];
    //dw ['.bigdoll'];
    //assert_table_length ['NUM_DECO_TYPES + 1']


invalid:
    RET;


plant:
    LD_A_E;
    goto getdeconame;


bed:
    CALL(aGetDecoName_plant);
    LD_A(_BED);
    goto getdeconame;


carpet:
    CALL(aGetDecoName_plant);
    LD_A(_CARPET);
    goto getdeconame;


poster:
    LD_A_E;
    CALL(aGetDecoName_getpokename);
    LD_A(_POSTER);
    goto getdeconame;


doll:
    LD_A_E;
    CALL(aGetDecoName_getpokename);
    LD_A(_DOLL);
    goto getdeconame;


bigdoll:
    PUSH_DE;
    LD_A(BIG_);
    CALL(aGetDecoName_getdeconame);
    POP_DE;
    LD_A_E;
    goto getpokename;


unused:
//   //  unreferenced
    PUSH_DE;
    CALL(aGetDecoName_getdeconame);
    POP_DE;
    LD_A_E;
    goto getdeconame;


getpokename:
    PUSH_BC;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    POP_BC;
    goto copy;


getdeconame:
    CALL(aGetDecoName__getdeconame);
    goto copy;


_getdeconame:
    PUSH_BC;
    LD_HL(mDecorationNames);
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    POP_BC;
    RET;


copy:
    LD_H_B;
    LD_L_C;
    CALL(aCopyName2);
    DEC_HL;
    LD_B_H;
    LD_C_L;
    RET;

}

static const char* GetDecoName__getdeconame_Conv(uint8_t a) {
    // PUSH_BC;
    // LD_HL(mDecorationNames);
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // POP_BC;
    // RET;
    return DecorationNames[a];
}

static uint8_t* GetDecoName_copy(uint8_t* bc, const uint8_t* de) {
    // LD_H_B;
    // LD_L_C;
    // CALL(aCopyName2);
    uint8_t* hl = CopyName2(bc, de);
    // DEC_HL;
    // LD_B_H;
    // LD_C_L;
    // RET;
    return hl - 1;
}

static uint8_t* GetDecoName_getdeconame(uint8_t* bc, uint8_t a) {
    uint8_t buffer[16];
    // CALL(aGetDecoName__getdeconame);
    // goto copy;
    return GetDecoName_copy(bc, U82CA(buffer, GetDecoName__getdeconame_Conv(a)));
}

static uint8_t* GetDecoName_getpokename(uint8_t* bc, species_t a) {
    // PUSH_BC;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // POP_BC;
    // goto copy;
    return GetDecoName_copy(bc, GetPokemonName(a));
}

const uint8_t* GetDecoName_Conv(const struct Decoration* hl){
    // LD_A_hli;  // DECOATTR_TYPE
    uint8_t a = hl->type_id;
    // LD_E_hl;  // DECOATTR_NAME
    uint8_t e = hl->name_id;
    // LD_BC(wStringBuffer2);
    // PUSH_BC;
    // LD_HL(mGetDecoName_NameFunctions);
    // RST(aJumpTable);
    // POP_DE;
    // RET;

    switch(a) {
    // NameFunctions:
        //table_width ['2', 'GetDecoName.NameFunctions']
        //dw ['.invalid'];
        default:
        case 0: return wram->wStringBuffer2;
        //dw ['.plant'];
        case DECO_PLANT:
        // plant:
            // LD_A_E;
            // goto getdeconame;
            return GetDecoName_getdeconame(wram->wStringBuffer2, e);
        //dw ['.bed'];
        case DECO_BED:
        // bed:
            // CALL(aGetDecoName_plant);
            // LD_A(_BED);
            // goto getdeconame;
            return GetDecoName_getdeconame(GetDecoName_getdeconame(wram->wStringBuffer2, e), _BED);
        //dw ['.carpet'];
        case DECO_CARPET:
        // carpet:
            // CALL(aGetDecoName_plant);
            // LD_A(_CARPET);
            // goto getdeconame;
            return GetDecoName_getdeconame(GetDecoName_getdeconame(wram->wStringBuffer2, e), _CARPET);
        //dw ['.poster'];
        case DECO_POSTER:
        // poster:
            // LD_A_E;
            // CALL(aGetDecoName_getpokename);
            // LD_A(_POSTER);
            // goto getdeconame;
            return GetDecoName_getdeconame(GetDecoName_getpokename(wram->wStringBuffer2, e), _POSTER);
        //dw ['.doll'];
        case DECO_DOLL:
        // doll:
            // LD_A_E;
            // CALL(aGetDecoName_getpokename);
            // LD_A(_DOLL);
            // goto getdeconame;
            return GetDecoName_getdeconame(GetDecoName_getpokename(wram->wStringBuffer2, e), _DOLL);
        //dw ['.bigdoll'];
        case DECO_BIGDOLL:
        // bigdoll:
            // PUSH_DE;
            // LD_A(BIG_);
            // CALL(aGetDecoName_getdeconame);
            // POP_DE;
            // LD_A_E;
            // goto getpokename;
            return GetDecoName_getpokename(GetDecoName_getdeconame(wram->wStringBuffer2, BIG_), e);
    }
    //assert_table_length ['NUM_DECO_TYPES + 1']


// invalid:
    // RET;


// unused:
//   //  unreferenced
    // PUSH_DE;
    // CALL(aGetDecoName_getdeconame);
    // POP_DE;
    // LD_A_E;
    // goto getdeconame;


// getdeconame:
    // CALL(aGetDecoName__getdeconame);
    // goto copy;


// _getdeconame:
    // PUSH_BC;
    // LD_HL(mDecorationNames);
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // POP_BC;
    // RET;
}

void DecoAction_nothing(void){
    // SCF;
    // RET;
    return;
}

void DecoAction_setupbed(void){
    // LD_HL(wDecoBed);
    // JP(mDecoAction_TrySetItUp);
    DecoAction_TrySetItUp(&wram->wDecoBed);

}

void DecoAction_putawaybed(void){
    // LD_HL(wDecoBed);
    // JP(mDecoAction_TryPutItAway);
    DecoAction_TryPutItAway(&wram->wDecoBed);
}

void DecoAction_setupcarpet(void){
    // LD_HL(wDecoCarpet);
    // JP(mDecoAction_TrySetItUp);
    DecoAction_TrySetItUp(&wram->wDecoCarpet);

}

void DecoAction_putawaycarpet(void){
    // LD_HL(wDecoCarpet);
    // JP(mDecoAction_TryPutItAway);
    DecoAction_TryPutItAway(&wram->wDecoCarpet);

}

void DecoAction_setupplant(void){
    // LD_HL(wDecoPlant);
    // JP(mDecoAction_TrySetItUp);
    DecoAction_TrySetItUp(&wram->wDecoPlant);

}

void DecoAction_putawayplant(void){
    // LD_HL(wDecoPlant);
    // JP(mDecoAction_TryPutItAway);
    DecoAction_TryPutItAway(&wram->wDecoPlant);
}

void DecoAction_setupposter(void){
    // LD_HL(wDecoPoster);
    // JP(mDecoAction_TrySetItUp);
    DecoAction_TrySetItUp(&wram->wDecoPoster);

}

void DecoAction_putawayposter(void){
    // LD_HL(wDecoPoster);
    // JP(mDecoAction_TryPutItAway);
    DecoAction_TryPutItAway(&wram->wDecoPoster);
}

void DecoAction_setupconsole(void){
    // LD_HL(wDecoConsole);
    // JP(mDecoAction_TrySetItUp);
    DecoAction_TrySetItUp(&wram->wDecoConsole);
}

void DecoAction_putawayconsole(void){
    // LD_HL(wDecoConsole);
    // JP(mDecoAction_TryPutItAway);
    DecoAction_TryPutItAway(&wram->wDecoConsole);

}

void DecoAction_setupbigdoll(void){
    // LD_HL(wDecoBigDoll);
    // JP(mDecoAction_TrySetItUp);
    DecoAction_TrySetItUp(&wram->wDecoBigDoll);
}

void DecoAction_putawaybigdoll(void){
    // LD_HL(wDecoBigDoll);
    // JP(mDecoAction_TryPutItAway);
    DecoAction_TryPutItAway(&wram->wDecoBigDoll);

}

bool DecoAction_TrySetItUp(uint8_t* hl){
    // LD_A_hl;
    // LD_addr_A(wCurDecoration);
    wram->wCurDecoration = *hl;
    // PUSH_HL;
    // CALL(aDecoAction_SetItUp);
    bool fail = DecoAction_SetItUp();
    // IF_C goto failed;
    if(fail) {
    // failed:
        // POP_HL;
        // XOR_A_A;
        // RET;
        return false;
    }
    // LD_A(TRUE);
    // LD_addr_A(wChangedDecorations);
    wram->wChangedDecorations = TRUE;
    // POP_HL;
    // LD_A_addr(wMenuSelection);
    // LD_hl_A;
    *hl = wram->wMenuSelection;
    // XOR_A_A;
    // RET;
    return false;
}

bool DecoAction_SetItUp(void){
//  See if there's anything of the same type already out
    // LD_A_addr(wCurDecoration);
    // AND_A_A;
    // IF_Z goto nothingthere;
    if(wram->wCurDecoration == 0) {
    // nothingthere:
        // LD_A_addr(wMenuSelection);
        // LD_HL(wStringBuffer3);
        // CALL(aGetDecorationName);
        GetDecorationName_Conv(wram->wStringBuffer3, wram->wMenuSelection);
        // LD_HL(mSetUpTheDecoText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(SetUpTheDecoText);
        // XOR_A_A;
        // RET;
        return false;
    }
//  See if that item is already out
    // LD_B_A;
    // LD_A_addr(wMenuSelection);
    // CP_A_B;
    // IF_Z goto alreadythere;
    if(wram->wCurDecoration == wram->wMenuSelection) {
    // alreadythere:
        // LD_HL(mAlreadySetUpText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(AlreadySetUpText);
        // SCF;
        // RET;
        return true;
    }
//  Put away the item that's already out, and set up the new one
    // LD_A_addr(wMenuSelection);
    // LD_HL(wStringBuffer4);
    // CALL(aGetDecorationName);
    GetDecorationName_Conv(wram->wStringBuffer4, wram->wMenuSelection);
    // LD_A_addr(wCurDecoration);
    // LD_HL(wStringBuffer3);
    // CALL(aGetDecorationName);
    GetDecorationName_Conv(wram->wStringBuffer3, wram->wCurDecoration);
    // LD_HL(mPutAwayAndSetUpText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(PutAwayAndSetUpText);
    // XOR_A_A;
    // RET;
    return false;
}

bool DecoAction_TryPutItAway(uint8_t* hl){
//  If there is no item of that type already set, there is nothing to put away.
    // LD_A_hl;
    // LD_addr_A(wCurDecoration);
    wram->wCurDecoration = *hl;
    // XOR_A_A;
    // LD_hl_A;
    *hl = 0x0;
    // LD_A_addr(wCurDecoration);
    // AND_A_A;
    // IF_Z goto nothingthere;
    if(wram->wCurDecoration == 0) {
    // nothingthere:
        // LD_HL(mNothingToPutAwayText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(NothingToPutAwayText);
        // XOR_A_A;
        // RET;
        return false;
    }
//  Put it away.
    // LD_A(TRUE);
    // LD_addr_A(wChangedDecorations);
    wram->wChangedDecorations = TRUE;
    // LD_A_addr(wCurDecoration);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = wram->wCurDecoration;
    // LD_HL(wStringBuffer3);
    // CALL(aGetDecorationName);
    GetDecorationName_Conv(wram->wStringBuffer3, wram->wCurDecoration);
    // LD_HL(mPutAwayTheDecoText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(PutAwayTheDecoText);
    // XOR_A_A;
    // RET;
    return false;
}

void DecoAction_setupornament(void){
    // LD_HL(mWhichSidePutOnText);
    // CALL(aDecoAction_AskWhichSide);
    // IF_C goto cancel;
    // CALL(aDecoAction_SetItUp_Ornament);
    // IF_C goto cancel;
    if(DecoAction_AskWhichSide(WhichSidePutOnText) || DecoAction_SetItUp_Ornament()) {
    // cancel:
        // XOR_A_A;
        // RET;
        return;
    }
    // LD_A(TRUE);
    // LD_addr_A(wChangedDecorations);
    wram->wChangedDecorations = TRUE;
    // JR(mDecoAction_FinishUp_Ornament);
    DecoAction_FinishUp_Ornament();
}

void DecoAction_putawayornament(void){
    // LD_HL(mWhichSidePutAwayText);
    // CALL(aDecoAction_AskWhichSide);
    // IF_NC goto incave;
    if(DecoAction_AskWhichSide(WhichSidePutAwayText)) {
        // XOR_A_A;
        // RET;
        return;
    }

// incave:
    // CALL(aDecoAction_PutItAway_Ornament);
    DecoAction_PutItAway_Ornament();

    DecoAction_FinishUp_Ornament();
}

bool DecoAction_FinishUp_Ornament(void){
    // CALL(aQueryWhichSide);
    u8_ptr_pair_s pair = QueryWhichSide();
    // LD_A_addr(wSelectedDecoration);
    // LD_hl_A;
    *pair.hl = wram->wSelectedDecoration;
    // LD_A_addr(wOtherDecoration);
    // LD_de_A;
    *pair.de = wram->wOtherDecoration;
    // XOR_A_A;
    // RET;
    return false;
}

static void DecoAction_SetItUp_Ornament_getwhichside(void) {
    // LD_A_addr(wMenuSelection);
    // LD_B_A;
    // LD_A_addr(wOtherDecoration);
    // CP_A_B;
    // RET_NZ ;
    if(wram->wMenuSelection == wram->wOtherDecoration) {
        // XOR_A_A;
        // LD_addr_A(wOtherDecoration);
        wram->wOtherDecoration = 0;
        // RET;
    }
}

bool DecoAction_SetItUp_Ornament(void){
    // LD_A_addr(wSelectedDecoration);
    // AND_A_A;
    // IF_Z goto nothingthere;
    if(wram->wSelectedDecoration == 0) {
    // nothingthere:
        // LD_A_addr(wMenuSelection);
        // LD_addr_A(wSelectedDecoration);
        wram->wSelectedDecoration = wram->wMenuSelection;
        // CALL(aDecoAction_SetItUp_Ornament_getwhichside);
        DecoAction_SetItUp_Ornament_getwhichside();
        // LD_A_addr(wMenuSelection);
        // LD_HL(wStringBuffer3);
        // CALL(aGetDecorationName);
        GetDecorationName_Conv(wram->wStringBuffer3, wram->wMenuSelection);
        // LD_HL(mSetUpTheDecoText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(SetUpTheDecoText);
        // XOR_A_A;
        // RET;
        return false;
    }
    // LD_B_A;
    // LD_A_addr(wMenuSelection);
    // CP_A_B;
    // IF_Z goto failed;
    if(wram->wSelectedDecoration == wram->wMenuSelection) {
    // failed:
        // LD_HL(mAlreadySetUpText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(AlreadySetUpText);
        // SCF;
        // RET;
        return true;
    }
    // LD_A_B;
    // LD_HL(wStringBuffer3);
    // CALL(aGetDecorationName);
    GetDecorationName_Conv(wram->wStringBuffer3, wram->wSelectedDecoration);
    // LD_A_addr(wMenuSelection);
    // LD_HL(wStringBuffer4);
    // CALL(aGetDecorationName);
    GetDecorationName_Conv(wram->wStringBuffer4, wram->wMenuSelection);
    // LD_A_addr(wMenuSelection);
    // LD_addr_A(wSelectedDecoration);
    wram->wSelectedDecoration = wram->wMenuSelection;
    // CALL(aDecoAction_SetItUp_Ornament_getwhichside);
    DecoAction_SetItUp_Ornament_getwhichside();
    // LD_HL(mPutAwayAndSetUpText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(PutAwayAndSetUpText);
    // XOR_A_A;
    // RET;
    return false;
}

const txt_cmd_s WhichSidePutOnText[] = {
    text_far(v_WhichSidePutOnText)
    text_end
};

bool DecoAction_PutItAway_Ornament(void){
    // LD_A_addr(wSelectedDecoration);
    // AND_A_A;
    // IF_Z goto nothingthere;
    if(wram->wSelectedDecoration == 0) {
    // nothingthere:
        // LD_HL(mNothingToPutAwayText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(NothingToPutAwayText);
        // XOR_A_A;
        // RET;
        return false;
    }
    // LD_HL(wStringBuffer3);
    // CALL(aGetDecorationName);
    GetDecorationName_Conv(wram->wStringBuffer3, wram->wSelectedDecoration);
    // LD_A(TRUE);
    // LD_addr_A(wChangedDecorations);
    wram->wChangedDecorations = TRUE;
    // XOR_A_A;
    // LD_addr_A(wSelectedDecoration);
    wram->wSelectedDecoration = 0;
    // LD_HL(mPutAwayTheDecoText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(PutAwayTheDecoText);
    // XOR_A_A;
    // RET;
    return false;
}

const txt_cmd_s WhichSidePutAwayText[] = {
    text_far(v_WhichSidePutAwayText)
    text_end
};

bool DecoAction_AskWhichSide(const txt_cmd_s* hl){
    // CALL(aMenuTextbox);
    MenuTextbox_Conv(hl);
    // LD_HL(mDecoSideMenuHeader);
    // CALL(aGetMenu2);
    u8_flag_s res = GetMenu2_Conv(&DecoSideMenuHeader);
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // CALL(aCopyMenuData);
    // IF_C goto nope;
    // LD_A_addr(wMenuCursorY);
    // CP_A(3);  // cancel
    // IF_Z goto nope;
    if(res.flag || wram->wMenuCursorY == 3) {
    // nope:
        // SCF;
        // RET;
        return true;
    }
    // LD_addr_A(wSelectedDecorationSide);
    wram->wSelectedDecorationSide = wram->wMenuCursorY;
    // CALL(aQueryWhichSide);
    u8_ptr_pair_s pair = QueryWhichSide();
    // LD_A_hl;
    // LD_addr_A(wSelectedDecoration);
    wram->wSelectedDecoration = *pair.hl;
    // LD_A_de;
    // LD_addr_A(wOtherDecoration);
    wram->wOtherDecoration = *pair.de;
    // XOR_A_A;
    // RET;
    return false;
}

u8_ptr_pair_s QueryWhichSide(void){
    // LD_HL(wDecoRightOrnament);
    uint8_t* hl = &wram->wDecoRightOrnament;
    // LD_DE(wDecoLeftOrnament);
    uint8_t* de = &wram->wDecoLeftOrnament;
    // LD_A_addr(wSelectedDecorationSide);
    // CP_A(1);  // right side
    // RET_Z ;
    if(wram->wSelectedDecorationSide == 1)
        return (u8_ptr_pair_s){.hl = hl, .de = de};
// left side, swap hl and de
    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // POP_DE;
    // RET;
    return (u8_ptr_pair_s){.hl = de, .de = hl};
}

const struct MenuHeader DecoSideMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 13, 7),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 3,  // items
            .options = (const char*[]) {
                "RIGHT SIDE",
                "LEFT SIDE",
                "CANCEL",
            },
        },
    },
    .defaultOption = 1,  // default option
};

const txt_cmd_s PutAwayTheDecoText[] = {
    text_far(v_PutAwayTheDecoText)
    text_end
};

const txt_cmd_s NothingToPutAwayText[] = {
    text_far(v_NothingToPutAwayText)
    text_end
};

const txt_cmd_s SetUpTheDecoText[] = {
    text_far(v_SetUpTheDecoText)
    text_end
};

const txt_cmd_s PutAwayAndSetUpText[] = {
    text_far(v_PutAwayAndSetUpText)
    text_end
};

const txt_cmd_s AlreadySetUpText[] = {
    text_far(v_AlreadySetUpText)
    text_end
};

void GetDecorationName_c_de(void){
    LD_A_C;
    LD_H_D;
    LD_L_E;
    CALL(aGetDecorationName);
    RET;

}

void GetDecorationName_c_de_Conv(uint8_t* de, uint8_t c){
    // LD_A_C;
    // LD_H_D;
    // LD_L_E;
    // CALL(aGetDecorationName);
    // RET;
    return GetDecorationName_Conv(de, c);
}

uint8_t DecorationFlagAction_c(uint8_t c, uint8_t b){
    // LD_A_C;
    // JP(mDecorationFlagAction);
    return DecorationFlagAction(c, b);
}

uint8_t* GetDecorationName_c(uint8_t c){
    // LD_A_C;
    // CALL(aGetDecorationID);
    // LD_HL(wStringBuffer1);
    // PUSH_HL;
    // CALL(aGetDecorationName);
    // POP_DE;
    // RET;
    GetDecorationName_Conv(wram->wStringBuffer1, GetDecorationID(c));
    return wram->wStringBuffer1;
}

void SetSpecificDecorationFlag(void){
    LD_A_C;
    CALL(aGetDecorationID);
    LD_B(SET_FLAG);
    CALL(aDecorationFlagAction);
    RET;

}

void SetSpecificDecorationFlag_Conv(uint8_t c){
    // LD_A_C;
    // CALL(aGetDecorationID);
    // LD_B(SET_FLAG);
    // CALL(aDecorationFlagAction);
    DecorationFlagAction(GetDecorationID(c), SET_FLAG);
    // RET;
}

uint8_t GetDecorationID(uint8_t c){
    // PUSH_HL;
    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mDecorationIDs);
    // ADD_HL_DE;
    // LD_A_hl;
    // POP_DE;
    // POP_HL;
    // RET;
    return DecorationIDs[c];
}

void SetAllDecorationFlags(void){
//  //  unreferenced
    LD_HL(mDecorationIDs);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    PUSH_HL;
    LD_B(SET_FLAG);
    CALL(aDecorationFlagAction);
    POP_HL;
    goto loop;


done:
    RET;

// INCLUDE "data/decorations/decorations.asm"

    return DescribeDecoration();
}

void DescribeDecoration(void){
    LD_A_B;
    LD_HL(mDescribeDecoration_Jumptable);
    RST(aJumpTable);
    RET;


// Jumptable:
//  entries correspond to DECODESC_* constants
    //table_width ['2', 'DescribeDecoration.Jumptable']
    //dw ['DecorationDesc_Poster'];
    //dw ['DecorationDesc_LeftOrnament'];
    //dw ['DecorationDesc_RightOrnament'];
    //dw ['DecorationDesc_GiantOrnament'];
    //dw ['DecorationDesc_Console'];
    //assert_table_length ['NUM_DECODESCS']
}

Script_fn_t DescribeDecoration_Conv(uint8_t b){
    // LD_A_B;
    // LD_HL(mDescribeDecoration_Jumptable);
    // RST(aJumpTable);
    // RET;

// Jumptable:
//  entries correspond to DECODESC_* constants
    //table_width ['2', 'DescribeDecoration.Jumptable']
    switch(b) {
        //dw ['DecorationDesc_Poster'];
        case DECODESC_POSTER: return DecorationDesc_Poster_Conv(wram->wDecoPoster);
        //dw ['DecorationDesc_LeftOrnament'];
        case DECODESC_LEFT_DOLL: return DecorationDesc_LeftOrnament_Conv();
        //dw ['DecorationDesc_RightOrnament'];
        case DECODESC_RIGHT_DOLL: return DecorationDesc_RightOrnament_Conv();
        //dw ['DecorationDesc_GiantOrnament'];
        case DECODESC_BIG_DOLL: return DecorationDesc_GiantOrnament_Conv();
        //dw ['DecorationDesc_Console'];
        case DECODESC_CONSOLE: return DecorationDesc_Console_Conv();
    }
    //assert_table_length ['NUM_DECODESCS']
    return NULL;
}

struct DecorationDescPointer {
    uint8_t id;
    Script_fn_t script;
};

const struct DecorationDescPointer DecorationDesc_PosterPointers[] = {
    {DECO_TOWN_MAP,             DecorationDesc_TownMapPoster},
    {DECO_PIKACHU_POSTER,       DecorationDesc_PikachuPoster},
    {DECO_CLEFAIRY_POSTER,      DecorationDesc_ClefairyPoster},
    {DECO_JIGGLYPUFF_POSTER,    DecorationDesc_JigglypuffPoster},
    //db ['-1'];
};

void DecorationDesc_Poster(void){
    LD_A_addr(wDecoPoster);
    LD_HL(mDecorationDesc_PosterPointers);
    LD_DE(3);
    CALL(aIsInArray);
    IF_C goto nope;
    LD_DE(mDecorationDesc_NullPoster);
    LD_B(BANK(aDecorationDesc_NullPoster));
    RET;


nope:
    LD_B(BANK(aDecorationDesc_TownMapPoster));
    INC_HL;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    RET;

}

Script_fn_t DecorationDesc_Poster_Conv(uint8_t poster){
    // LD_A_addr(wDecoPoster);
    // LD_HL(mDecorationDesc_PosterPointers);
    // LD_DE(3);
    // CALL(aIsInArray);
    // IF_C goto nope;
    for(uint32_t i = 0; i < lengthof(DecorationDesc_PosterPointers); ++i) {
        if(DecorationDesc_PosterPointers[i].id == poster) {
        // nope:
            // LD_B(BANK(aDecorationDesc_TownMapPoster));
            // INC_HL;
            // LD_A_hli;
            // LD_D_hl;
            // LD_E_A;
            // RET;
            return DecorationDesc_PosterPointers[i].script;
        }
    }
    // LD_DE(mDecorationDesc_NullPoster);
    // LD_B(BANK(aDecorationDesc_NullPoster));
    // RET;
    return DecorationDesc_NullPoster;
}

bool DecorationDesc_TownMapPoster(script_s* s){
    static const txt_cmd_s LookTownMapText[] = {
        text_far(v_LookTownMapText)
        text_end
    };
    SCRIPT_BEGIN
    opentext
    writetext(LookTownMapText)
    waitbutton
    special(OverworldTownMap)
    closetext
    s_end
    SCRIPT_END
}

bool DecorationDesc_PikachuPoster(script_s* s){
    static const txt_cmd_s LookPikachuPosterText[] = {
        text_far(v_LookPikachuPosterText)
        text_end
    };
    SCRIPT_BEGIN
    jumptext(LookPikachuPosterText)
    SCRIPT_END
}

bool DecorationDesc_ClefairyPoster(script_s* s){
    static const txt_cmd_s LookClefairyPosterText[] = {
        text_far(v_LookClefairyPosterText)
        text_end
    };
    SCRIPT_BEGIN
    jumptext(LookClefairyPosterText)
    SCRIPT_END
}

bool DecorationDesc_JigglypuffPoster(script_s* s){
    static const txt_cmd_s LookJigglypuffPosterText[] = {
        text_far(v_LookJigglypuffPosterText)
        text_end
    };
    SCRIPT_BEGIN
    jumptext(LookJigglypuffPosterText)
    SCRIPT_END
}

bool DecorationDesc_NullPoster(script_s* s){
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}

void DecorationDesc_LeftOrnament(void){
    LD_A_addr(wDecoLeftOrnament);
    JR(mDecorationDesc_OrnamentOrConsole);

}

Script_fn_t DecorationDesc_LeftOrnament_Conv(void){
    // LD_A_addr(wDecoLeftOrnament);
    // JR(mDecorationDesc_OrnamentOrConsole);
    return DecorationDesc_OrnamentOrConsole_Conv(wram->wDecoLeftOrnament);
}

void DecorationDesc_RightOrnament(void){
    LD_A_addr(wDecoRightOrnament);
    JR(mDecorationDesc_OrnamentOrConsole);

}

Script_fn_t DecorationDesc_RightOrnament_Conv(void){
    // LD_A_addr(wDecoRightOrnament);
    // JR(mDecorationDesc_OrnamentOrConsole);
    return DecorationDesc_OrnamentOrConsole_Conv(wram->wDecoRightOrnament);
}

void DecorationDesc_Console(void){
    LD_A_addr(wDecoConsole);
    JR(mDecorationDesc_OrnamentOrConsole);

}

Script_fn_t DecorationDesc_Console_Conv(void){
    // LD_A_addr(wDecoConsole);
    // JR(mDecorationDesc_OrnamentOrConsole);
    return DecorationDesc_OrnamentOrConsole_Conv(wram->wDecoConsole);
}

void DecorationDesc_OrnamentOrConsole(void){
    LD_C_A;
    LD_DE(wStringBuffer3);
    CALL(aGetDecorationName_c_de);
    LD_B(BANK(aDecorationDesc_OrnamentOrConsole_OrnamentConsoleScript));
    LD_DE(mDecorationDesc_OrnamentOrConsole_OrnamentConsoleScript);
    RET;


OrnamentConsoleScript:
    //jumptext ['.LookAdorableDecoText']


LookAdorableDecoText:
    //text_far ['_LookAdorableDecoText']
    //text_end ['?']

    return DecorationDesc_GiantOrnament();
}

static bool DecorationDesc_OrnamentOrConsole_OrnamentConsoleScript(script_s* s) {
    static const txt_cmd_s LookAdorableDecoText[] = {
        text_far(v_LookAdorableDecoText)
        text_end
    };
    SCRIPT_BEGIN
    jumptext(LookAdorableDecoText)
    SCRIPT_END
}

Script_fn_t DecorationDesc_OrnamentOrConsole_Conv(uint8_t c){
    // LD_C_A;
    // LD_DE(wStringBuffer3);
    // CALL(aGetDecorationName_c_de);
    GetDecorationName_c_de_Conv(wram->wStringBuffer3, c);
    // LD_B(BANK(aDecorationDesc_OrnamentOrConsole_OrnamentConsoleScript));
    // LD_DE(mDecorationDesc_OrnamentOrConsole_OrnamentConsoleScript);
    // RET;
    return DecorationDesc_OrnamentOrConsole_OrnamentConsoleScript;
}

void DecorationDesc_GiantOrnament(void){
    LD_B(BANK(aDecorationDesc_GiantOrnament_BigDollScript));
    LD_DE(mDecorationDesc_GiantOrnament_BigDollScript);
    RET;


BigDollScript:
    //jumptext ['.LookGiantDecoText']


LookGiantDecoText:
    //text_far ['_LookGiantDecoText']
    //text_end ['?']

    return ToggleMaptileDecorations();
}

static bool BigDollScript(script_s* s) {
    static const txt_cmd_s LookGiantDecoText[] = {
        text_far(v_LookGiantDecoText)
        text_end
    };
    SCRIPT_BEGIN
    jumptext(LookGiantDecoText)
    SCRIPT_END
}

Script_fn_t DecorationDesc_GiantOrnament_Conv(void){
    // LD_B(BANK(aDecorationDesc_GiantOrnament_BigDollScript));
    // LD_DE(mDecorationDesc_GiantOrnament_BigDollScript);
    // RET;
    return BigDollScript;
}

void ToggleMaptileDecorations(void){
// tile coordinates work the same way as for changeblock
    // LD_DE((0 << 8) | 4);  // bed coordinates
    // LD_A_addr(wDecoBed);
    // CALL(aSetDecorationTile);
    SetDecorationTile_Conv(wram->wDecoBed, 0, 4);
    // LD_DE((7 << 8) | 4);  // plant coordinates
    // LD_A_addr(wDecoPlant);
    // CALL(aSetDecorationTile);
    SetDecorationTile_Conv(wram->wDecoPlant, 7, 4);
    // LD_DE((6 << 8) | 0);  // poster coordinates
    // LD_A_addr(wDecoPoster);
    // CALL(aSetDecorationTile);
    SetDecorationTile_Conv(wram->wDecoPoster, 6, 0);
    // CALL(aSetPosterVisibility);
    SetPosterVisibility();
    // LD_DE((0 << 8) | 0);  // carpet top-left coordinates
    // CALL(aPadCoords_de);
    uint8_t* hl = PadCoords_de_Conv(0, 0);
    // LD_A_addr(wDecoCarpet);
    // AND_A_A;
    // RET_Z ;
    if(wram->wDecoCarpet == 0)
        return;
    // CALL(av_GetDecorationSprite);
    uint8_t sprite = v_GetDecorationSprite_Conv(wram->wDecoCarpet);
    // LD_hl_A;
    *hl = sprite;
    // PUSH_AF;
    // LD_DE((0 << 8) | 2);  // carpet bottom-left coordinates
    // CALL(aPadCoords_de);
    hl = PadCoords_de_Conv(0, 2);
    // POP_AF;
    // INC_A;
    // LD_hli_A;  // carpet bottom-left block
    *(hl++) = ++sprite;
    // INC_A;
    // LD_hli_A;  // carpet bottom-middle block
    *(hl++) = ++sprite;
    // DEC_A;
    // LD_hl_A;  // carpet bottom-right block
    *hl = --sprite;
    // RET;
}

void SetPosterVisibility(void){
    // LD_B(SET_FLAG);
    // LD_A_addr(wDecoPoster);
    // AND_A_A;
    // IF_NZ goto ok;
    // LD_B(RESET_FLAG);
    uint8_t b = (wram->wDecoPoster != 0)? SET_FLAG: RESET_FLAG;

// ok:
    // LD_DE(EVENT_PLAYERS_ROOM_POSTER);
    // JP(mEventFlagAction);
    EventFlagAction(EVENT_PLAYERS_ROOM_POSTER, b);
}

void SetDecorationTile(void){
    PUSH_AF;
    CALL(aPadCoords_de);
    POP_AF;
    AND_A_A;
    RET_Z ;
    CALL(av_GetDecorationSprite);
    LD_hl_A;
    RET;

}

void SetDecorationTile_Conv(uint8_t a, uint8_t d, uint8_t e){
    // PUSH_AF;
    // CALL(aPadCoords_de);
    // POP_AF;
    uint8_t* hl = PadCoords_de_Conv(d, e);
    // AND_A_A;
    // RET_Z ;
    if(a == 0)
        return;
    // CALL(av_GetDecorationSprite);
    // LD_hl_A;
    *hl = v_GetDecorationSprite_Conv(a);
    // RET;
}

void ToggleDecorationsVisibility(void){
    // LD_DE(EVENT_PLAYERS_HOUSE_2F_CONSOLE);
    // LD_HL(wVariableSprites + SPRITE_CONSOLE - SPRITE_VARS);
    // LD_A_addr(wDecoConsole);
    // CALL(aToggleDecorationVisibility);
    ToggleDecorationVisibility_Conv(wram->wVariableSprites + (SPRITE_CONSOLE - SPRITE_VARS), EVENT_PLAYERS_HOUSE_2F_CONSOLE, wram->wDecoConsole);
    // LD_DE(EVENT_PLAYERS_HOUSE_2F_DOLL_1);
    // LD_HL(wVariableSprites + SPRITE_DOLL_1 - SPRITE_VARS);
    // LD_A_addr(wDecoLeftOrnament);
    // CALL(aToggleDecorationVisibility);
    ToggleDecorationVisibility_Conv(wram->wVariableSprites + (SPRITE_DOLL_1 - SPRITE_VARS), EVENT_PLAYERS_HOUSE_2F_DOLL_1, wram->wDecoLeftOrnament);
    // LD_DE(EVENT_PLAYERS_HOUSE_2F_DOLL_2);
    // LD_HL(wVariableSprites + SPRITE_DOLL_2 - SPRITE_VARS);
    // LD_A_addr(wDecoRightOrnament);
    // CALL(aToggleDecorationVisibility);
    ToggleDecorationVisibility_Conv(wram->wVariableSprites + (SPRITE_DOLL_2 - SPRITE_VARS), EVENT_PLAYERS_HOUSE_2F_DOLL_2, wram->wDecoRightOrnament);
    // LD_DE(EVENT_PLAYERS_HOUSE_2F_BIG_DOLL);
    // LD_HL(wVariableSprites + SPRITE_BIG_DOLL - SPRITE_VARS);
    // LD_A_addr(wDecoBigDoll);
    // CALL(aToggleDecorationVisibility);
    ToggleDecorationVisibility_Conv(wram->wVariableSprites + (SPRITE_BIG_DOLL - SPRITE_VARS), EVENT_PLAYERS_HOUSE_2F_BIG_DOLL, wram->wDecoBigDoll);
    // RET;
}

void ToggleDecorationVisibility(void){
    AND_A_A;
    IF_Z goto hide;
    CALL(av_GetDecorationSprite);
    LD_hl_A;
    LD_B(RESET_FLAG);
    JP(mEventFlagAction);


hide:
    LD_B(SET_FLAG);
    JP(mEventFlagAction);

}

void ToggleDecorationVisibility_Conv(uint8_t* hl, uint16_t de, uint8_t a){
    // AND_A_A;
    // IF_Z goto hide;
    if(a == 0) {
    // hide:
        // LD_B(SET_FLAG);
        // JP(mEventFlagAction);
        EventFlagAction(de, SET_FLAG);
        return;
    }
    // CALL(av_GetDecorationSprite);
    // LD_hl_A;
    *hl = v_GetDecorationSprite_Conv(a);
    // LD_B(RESET_FLAG);
    // JP(mEventFlagAction);
    EventFlagAction(de, RESET_FLAG);
}

void v_GetDecorationSprite(void){
    LD_C_A;
    PUSH_DE;
    PUSH_HL;
    FARCALL(aGetDecorationSprite);
    POP_HL;
    POP_DE;
    LD_A_C;
    RET;

}

uint8_t v_GetDecorationSprite_Conv(uint8_t a) {
    return GetDecorationSprite_Conv(a);
}

void PadCoords_de(void){
//  adjusts coordinates, the same way as Script_changeblock
    LD_A_D;
    ADD_A(4);
    LD_D_A;
    LD_A_E;
    ADD_A(4);
    LD_E_A;
    CALL(aGetBlockLocation);
    RET;

}

uint8_t* PadCoords_de_Conv(uint8_t d, uint8_t e){
//  adjusts coordinates, the same way as Script_changeblock
    // LD_A_D;
    // ADD_A(4);
    // LD_D_A;
    // LD_A_E;
    // ADD_A(4);
    // LD_E_A;
    // CALL(aGetBlockLocation);
    // RET;
    return GetBlockLocation_Conv(d + 4, e + 4);
}
