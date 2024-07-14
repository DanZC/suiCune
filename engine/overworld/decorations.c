#include "../../constants.h"
#include "decorations.h"
#include "../../home/names.h"
#include "../../home/copy_name.h"
#include "../../home/map.h"
#include "../../home/flag.h"
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

void v_PlayerDecorationMenu(void){
    LD_A_addr(wWhichIndexSet);
    PUSH_AF;
    LD_HL(mv_PlayerDecorationMenu_MenuHeader);
    CALL(aLoadMenuHeader);
    XOR_A_A;  // FALSE
    LD_addr_A(wChangedDecorations);
    LD_A(0x1);  // bed
    LD_addr_A(wCurDecorationCategory);

top_loop:
    LD_A_addr(wCurDecorationCategory);
    LD_addr_A(wMenuCursorPosition);
    CALL(av_PlayerDecorationMenu_FindCategoriesWithOwnedDecos);
    CALL(aDoNthMenu);
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wCurDecorationCategory);
    IF_C goto exit_menu;
    LD_A_addr(wMenuSelection);
    LD_HL(mv_PlayerDecorationMenu_category_pointers);
    CALL(aMenuJumptable);
    IF_NC goto top_loop;


exit_menu:
    CALL(aExitMenu);
    POP_AF;
    LD_addr_A(wWhichIndexSet);
    LD_A_addr(wChangedDecorations);
    LD_C_A;
    RET;


MenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['5', '0', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_WRAP'];  // flags
    //db ['0'];  // items
    //dw ['wNumOwnedDecoCategories'];
    //dw ['PlaceNthMenuStrings'];
    //dw ['.category_pointers'];


category_pointers:
    //table_width ['2 + 2', '_PlayerDecorationMenu.category_pointers']
    //dw ['DecoBedMenu', '.bed'];
    //dw ['DecoCarpetMenu', '.carpet'];
    //dw ['DecoPlantMenu', '.plant'];
    //dw ['DecoPosterMenu', '.poster'];
    //dw ['DecoConsoleMenu', '.game'];
    //dw ['DecoOrnamentMenu', '.ornament'];
    //dw ['DecoBigDollMenu', '.big_doll'];
    //dw ['DecoExitMenu', '.exit'];
    //assert_table_length ['NUM_DECO_CATEGORIES + 1']


bed:
//      db "BED@"

carpet:
//   db "CARPET@"

plant:
//    db "PLANT@"

poster:
//   db "POSTER@"

game:
//     db "GAME CONSOLE@"

ornament:
// db "ORNAMENT@"

big_doll:
// db "BIG DOLL@"

exit:
//     db "EXIT@"


FindCategoriesWithOwnedDecos:
    XOR_A_A;
    LD_addr_A(wWhichIndexSet);
    CALL(av_PlayerDecorationMenu_ClearStringBuffer2);
    CALL(av_PlayerDecorationMenu_FindOwnedDecos);
    LD_A(7);
    CALL(av_PlayerDecorationMenu_AppendToStringBuffer2);
    LD_HL(wStringBuffer2);
    LD_DE(wDecoNameBuffer);
    LD_BC(ITEM_NAME_LENGTH);
    CALL(aCopyBytes);
    RET;


ClearStringBuffer2:
    LD_HL(wStringBuffer2);
    XOR_A_A;
    LD_hli_A;
    LD_BC(ITEM_NAME_LENGTH - 1);
    LD_A(-1);
    CALL(aByteFill);
    RET;


AppendToStringBuffer2:
    LD_HL(wStringBuffer2);
    INC_hl;
    LD_E_hl;
    LD_D(0);
    ADD_HL_DE;
    LD_hl_A;
    RET;


FindOwnedDecos:
    LD_HL(mv_PlayerDecorationMenu_owned_pointers);

loop:
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    OR_A_E;
    IF_Z goto done;
    PUSH_HL;
    CALL(av_de_);
    POP_HL;
    IF_NC goto next;
    LD_A_hl;
    PUSH_HL;
    CALL(av_PlayerDecorationMenu_AppendToStringBuffer2);
    POP_HL;

next:
    INC_HL;
    goto loop;

done:
    RET;


owned_pointers:
    //table_width ['3', '_PlayerDecorationMenu.owned_pointers']
    //dwb ['FindOwnedBeds', '0']  // bed
    //dwb ['FindOwnedCarpets', '1']  // carpet
    //dwb ['FindOwnedPlants', '2']  // plant
    //dwb ['FindOwnedPosters', '3']  // poster
    //dwb ['FindOwnedConsoles', '4']  // game console
    //dwb ['FindOwnedOrnaments', '5']  // ornament
    //dwb ['FindOwnedBigDolls', '6']  // big doll
    //assert_table_length ['NUM_DECO_CATEGORIES']
    //dw ['0'];  // end

    return Deco_FillTempWithMinusOne();
}

void Deco_FillTempWithMinusOne(void){
    XOR_A_A;
    LD_HL(wNumOwnedDecoCategories);
    LD_hli_A;
    //assert ['wNumOwnedDecoCategories + 1 == wOwnedDecoCategories'];
    LD_A(-1);
    LD_BC(16);
    CALL(aByteFill);
    RET;

}

void CheckAllDecorationFlags(void){

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    PUSH_HL;
    PUSH_AF;
    LD_B(CHECK_FLAG);
    CALL(aDecorationFlagAction);
    LD_A_C;
    AND_A_A;
    POP_BC;
    LD_A_B;
    CALL_NZ (aAppendDecoIndex);
    POP_HL;
    goto loop;


done:
    RET;

}

void AppendDecoIndex(void){
    LD_HL(wNumOwnedDecoCategories);
    INC_hl;
    //assert ['wNumOwnedDecoCategories + 1 == wOwnedDecoCategories'];
    LD_E_hl;
    LD_D(0);
    ADD_HL_DE;
    LD_hl_A;
    RET;

}

void FindOwnedDecosInCategory(void){
    PUSH_BC;
    PUSH_HL;
    CALL(aDeco_FillTempWithMinusOne);
    POP_HL;
    CALL(aCheckAllDecorationFlags);
    POP_BC;
    LD_A_addr(wNumOwnedDecoCategories);
    AND_A_A;
    RET_Z ;

    LD_A_C;
    CALL(aAppendDecoIndex);
    LD_A(0);
    CALL(aAppendDecoIndex);
    SCF;
    RET;

}

void DecoBedMenu(void){
    CALL(aFindOwnedBeds);
    CALL(aPopulateDecoCategoryMenu);
    XOR_A_A;
    RET;

}

void FindOwnedBeds(void){
    LD_HL(mFindOwnedBeds_beds);
    LD_C(BEDS);
    JP(mFindOwnedDecosInCategory);


beds:
    //db ['DECO_FEATHERY_BED'];  // 2
    //db ['DECO_PINK_BED'];  // 3
    //db ['DECO_POLKADOT_BED'];  // 4
    //db ['DECO_PIKACHU_BED'];  // 5
    //db ['-1'];

    return DecoCarpetMenu();
}

void DecoCarpetMenu(void){
    CALL(aFindOwnedCarpets);
    CALL(aPopulateDecoCategoryMenu);
    XOR_A_A;
    RET;

}

void FindOwnedCarpets(void){
    LD_HL(mFindOwnedCarpets_carpets);
    LD_C(CARPETS);
    JP(mFindOwnedDecosInCategory);


carpets:
    //db ['DECO_RED_CARPET'];  // 7
    //db ['DECO_BLUE_CARPET'];  // 8
    //db ['DECO_YELLOW_CARPET'];  // 9
    //db ['DECO_GREEN_CARPET'];  // a
    //db ['-1'];

    return DecoPlantMenu();
}

void DecoPlantMenu(void){
    CALL(aFindOwnedPlants);
    CALL(aPopulateDecoCategoryMenu);
    XOR_A_A;
    RET;

}

void FindOwnedPlants(void){
    LD_HL(mFindOwnedPlants_plants);
    LD_C(PLANTS);
    JP(mFindOwnedDecosInCategory);


plants:
    //db ['DECO_MAGNAPLANT'];  // c
    //db ['DECO_TROPICPLANT'];  // d
    //db ['DECO_JUMBOPLANT'];  // e
    //db ['-1'];

    return DecoPosterMenu();
}

void DecoPosterMenu(void){
    CALL(aFindOwnedPosters);
    CALL(aPopulateDecoCategoryMenu);
    XOR_A_A;
    RET;

}

void FindOwnedPosters(void){
    LD_HL(mFindOwnedPosters_posters);
    LD_C(POSTERS);
    JP(mFindOwnedDecosInCategory);


posters:
    //db ['DECO_TOWN_MAP'];  // 10
    //db ['DECO_PIKACHU_POSTER'];  // 11
    //db ['DECO_CLEFAIRY_POSTER'];  // 12
    //db ['DECO_JIGGLYPUFF_POSTER'];  // 13
    //db ['-1'];

    return DecoConsoleMenu();
}

void DecoConsoleMenu(void){
    CALL(aFindOwnedConsoles);
    CALL(aPopulateDecoCategoryMenu);
    XOR_A_A;
    RET;

}

void FindOwnedConsoles(void){
    LD_HL(mFindOwnedConsoles_consoles);
    LD_C(CONSOLES);
    JP(mFindOwnedDecosInCategory);


consoles:
    //db ['DECO_FAMICOM'];  // 15
    //db ['DECO_SNES'];  // 16
    //db ['DECO_N64'];  // 17
    //db ['DECO_VIRTUAL_BOY'];  // 18
    //db ['-1'];

    return DecoOrnamentMenu();
}

void DecoOrnamentMenu(void){
    CALL(aFindOwnedOrnaments);
    CALL(aPopulateDecoCategoryMenu);
    XOR_A_A;
    RET;

}

void FindOwnedOrnaments(void){
    LD_HL(mFindOwnedOrnaments_ornaments);
    LD_C(DOLLS);
    JP(mFindOwnedDecosInCategory);


ornaments:
    //db ['DECO_PIKACHU_DOLL'];  // 1e
    //db ['DECO_SURF_PIKACHU_DOLL'];  // 1f
    //db ['DECO_CLEFAIRY_DOLL'];  // 20
    //db ['DECO_JIGGLYPUFF_DOLL'];  // 21
    //db ['DECO_BULBASAUR_DOLL'];  // 22
    //db ['DECO_CHARMANDER_DOLL'];  // 23
    //db ['DECO_SQUIRTLE_DOLL'];  // 24
    //db ['DECO_POLIWAG_DOLL'];  // 25
    //db ['DECO_DIGLETT_DOLL'];  // 26
    //db ['DECO_STARMIE_DOLL'];  // 27
    //db ['DECO_MAGIKARP_DOLL'];  // 28
    //db ['DECO_ODDISH_DOLL'];  // 29
    //db ['DECO_GENGAR_DOLL'];  // 2a
    //db ['DECO_SHELLDER_DOLL'];  // 2b
    //db ['DECO_GRIMER_DOLL'];  // 2c
    //db ['DECO_VOLTORB_DOLL'];  // 2d
    //db ['DECO_WEEDLE_DOLL'];  // 2e
    //db ['DECO_UNOWN_DOLL'];  // 2f
    //db ['DECO_GEODUDE_DOLL'];  // 30
    //db ['DECO_MACHOP_DOLL'];  // 31
    //db ['DECO_TENTACOOL_DOLL'];  // 32
    //db ['DECO_GOLD_TROPHY_DOLL'];  // 33
    //db ['DECO_SILVER_TROPHY_DOLL'];  // 34
    //db ['-1'];

    return DecoBigDollMenu();
}

void DecoBigDollMenu(void){
    CALL(aFindOwnedBigDolls);
    CALL(aPopulateDecoCategoryMenu);
    XOR_A_A;
    RET;

}

void FindOwnedBigDolls(void){
    LD_HL(mFindOwnedBigDolls_big_dolls);
    LD_C(BIG_DOLLS);
    JP(mFindOwnedDecosInCategory);


big_dolls:
    //db ['DECO_BIG_SNORLAX_DOLL'];  // 1a
    //db ['DECO_BIG_ONIX_DOLL'];  // 1b
    //db ['DECO_BIG_LAPRAS_DOLL'];  // 1c
    //db ['-1'];

    return DecoExitMenu();
}

void DecoExitMenu(void){
    SCF;
    RET;

}

void PopulateDecoCategoryMenu(void){
    LD_A_addr(wNumOwnedDecoCategories);
    AND_A_A;
    IF_Z goto empty;
    CP_A(8);
    IF_NC goto beyond_eight;
    XOR_A_A;
    LD_addr_A(wWhichIndexSet);
    LD_HL(mPopulateDecoCategoryMenu_NonscrollingMenuHeader);
    CALL(aLoadMenuHeader);
    CALL(aDoNthMenu);
    IF_C goto no_action_1;
    CALL(aDoDecorationAction2);


no_action_1:
    CALL(aExitMenu);
    RET;


beyond_eight:
    LD_HL(wNumOwnedDecoCategories);
    LD_E_hl;
    DEC_hl;
    //assert ['wNumOwnedDecoCategories + 1 == wOwnedDecoCategories'];
    LD_D(0);
    ADD_HL_DE;
    LD_hl(-1);
    CALL(aLoadStandardMenuHeader);
    LD_HL(mPopulateDecoCategoryMenu_ScrollingMenuHeader);
    CALL(aCopyMenuHeader);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aInitScrollingMenu);
    XOR_A_A;
    LD_addr_A(wMenuScrollPosition);
    CALL(aScrollingMenu);
    LD_A_addr(wMenuJoypad);
    CP_A(2);
    IF_Z goto no_action_2;
    CALL(aDoDecorationAction2);


no_action_2:
    CALL(aExitMenu);
    RET;


empty:
    LD_HL(mPopulateDecoCategoryMenu_NothingToChooseText);
    CALL(aMenuTextboxBackup);
    RET;


NothingToChooseText:
    //text_far ['_NothingToChooseText']
    //text_end ['?']


NonscrollingMenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.NonscrollingMenuData'];
    //db ['1'];  // default option


NonscrollingMenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_WRAP'];  // flags
    //db ['0'];  // items
    //dw ['wDecoNameBuffer'];
    //dw ['DecorationMenuFunction'];
    //dw ['DecorationAttributes'];


ScrollingMenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['1', '1', 'SCREEN_WIDTH - 2', 'SCREEN_HEIGHT - 2'];
    //dw ['.ScrollingMenuData'];
    //db ['1'];  // default option


ScrollingMenuData:
    //db ['SCROLLINGMENU_DISPLAY_ARROWS'];  // flags
    //db ['8', '0'];  // rows, columns
    //db ['SCROLLINGMENU_ITEMS_NORMAL'];  // item format
    //dbw ['0', 'wNumOwnedDecoCategories']
    //dba ['DecorationMenuFunction']
    //dbw ['0', 'NULL']
    //dbw ['0', 'NULL']

    return GetDecorationData();
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
    CopyName2_Conv2(hl, de);
    // RET;
}

void DecorationMenuFunction(void){
    LD_A_addr(wMenuSelection);
    PUSH_DE;
    CALL(aGetDecorationData);
    CALL(aGetDecoName);
    POP_HL;
    CALL(aPlaceString);
    RET;

}

void DoDecorationAction2(void){
    LD_A_addr(wMenuSelection);
    CALL(aGetDecorationData);
    LD_DE(DECOATTR_ACTION);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(mDoDecorationAction2_DecoActions);
    RST(aJumpTable);
    RET;

// DecoActions:
    //table_width ['2', 'DoDecorationAction2.DecoActions']
    //dw ['DecoAction_nothing'];
    //dw ['DecoAction_setupbed'];
    //dw ['DecoAction_putawaybed'];
    //dw ['DecoAction_setupcarpet'];
    //dw ['DecoAction_putawaycarpet'];
    //dw ['DecoAction_setupplant'];
    //dw ['DecoAction_putawayplant'];
    //dw ['DecoAction_setupposter'];
    //dw ['DecoAction_putawayposter'];
    //dw ['DecoAction_setupconsole'];
    //dw ['DecoAction_putawayconsole'];
    //dw ['DecoAction_setupbigdoll'];
    //dw ['DecoAction_putawaybigdoll'];
    //dw ['DecoAction_setupornament'];
    //dw ['DecoAction_putawayornament'];
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
    return EventFlagAction_Conv2(GetDecorationFlag(c), b);
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
    uint8_t* hl = CopyName2_Conv2(bc, de);
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
    return GetDecoName_copy(bc, GetPokemonName_Conv2(a));
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
    SCF;
    RET;

}

void DecoAction_setupbed(void){
    LD_HL(wDecoBed);
    JP(mDecoAction_TrySetItUp);

}

void DecoAction_putawaybed(void){
    LD_HL(wDecoBed);
    JP(mDecoAction_TryPutItAway);

}

void DecoAction_setupcarpet(void){
    LD_HL(wDecoCarpet);
    JP(mDecoAction_TrySetItUp);

}

void DecoAction_putawaycarpet(void){
    LD_HL(wDecoCarpet);
    JP(mDecoAction_TryPutItAway);

}

void DecoAction_setupplant(void){
    LD_HL(wDecoPlant);
    JP(mDecoAction_TrySetItUp);

}

void DecoAction_putawayplant(void){
    LD_HL(wDecoPlant);
    JP(mDecoAction_TryPutItAway);

}

void DecoAction_setupposter(void){
    LD_HL(wDecoPoster);
    JP(mDecoAction_TrySetItUp);

}

void DecoAction_putawayposter(void){
    LD_HL(wDecoPoster);
    JP(mDecoAction_TryPutItAway);

}

void DecoAction_setupconsole(void){
    LD_HL(wDecoConsole);
    JP(mDecoAction_TrySetItUp);

}

void DecoAction_putawayconsole(void){
    LD_HL(wDecoConsole);
    JP(mDecoAction_TryPutItAway);

}

void DecoAction_setupbigdoll(void){
    LD_HL(wDecoBigDoll);
    JP(mDecoAction_TrySetItUp);

}

void DecoAction_putawaybigdoll(void){
    LD_HL(wDecoBigDoll);
    JP(mDecoAction_TryPutItAway);

}

void DecoAction_TrySetItUp(void){
    LD_A_hl;
    LD_addr_A(wCurDecoration);
    PUSH_HL;
    CALL(aDecoAction_SetItUp);
    IF_C goto failed;
    LD_A(TRUE);
    LD_addr_A(wChangedDecorations);
    POP_HL;
    LD_A_addr(wMenuSelection);
    LD_hl_A;
    XOR_A_A;
    RET;


failed:
    POP_HL;
    XOR_A_A;
    RET;

}

void DecoAction_SetItUp(void){
//  See if there's anything of the same type already out
    LD_A_addr(wCurDecoration);
    AND_A_A;
    IF_Z goto nothingthere;
//  See if that item is already out
    LD_B_A;
    LD_A_addr(wMenuSelection);
    CP_A_B;
    IF_Z goto alreadythere;
//  Put away the item that's already out, and set up the new one
    LD_A_addr(wMenuSelection);
    LD_HL(wStringBuffer4);
    CALL(aGetDecorationName);
    LD_A_addr(wCurDecoration);
    LD_HL(wStringBuffer3);
    CALL(aGetDecorationName);
    LD_HL(mPutAwayAndSetUpText);
    CALL(aMenuTextboxBackup);
    XOR_A_A;
    RET;


nothingthere:
    LD_A_addr(wMenuSelection);
    LD_HL(wStringBuffer3);
    CALL(aGetDecorationName);
    LD_HL(mSetUpTheDecoText);
    CALL(aMenuTextboxBackup);
    XOR_A_A;
    RET;


alreadythere:
    LD_HL(mAlreadySetUpText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;

}

void DecoAction_TryPutItAway(void){
//  If there is no item of that type already set, there is nothing to put away.
    LD_A_hl;
    LD_addr_A(wCurDecoration);
    XOR_A_A;
    LD_hl_A;
    LD_A_addr(wCurDecoration);
    AND_A_A;
    IF_Z goto nothingthere;
//  Put it away.
    LD_A(TRUE);
    LD_addr_A(wChangedDecorations);
    LD_A_addr(wCurDecoration);
    LD_addr_A(wMenuSelection);
    LD_HL(wStringBuffer3);
    CALL(aGetDecorationName);
    LD_HL(mPutAwayTheDecoText);
    CALL(aMenuTextboxBackup);
    XOR_A_A;
    RET;


nothingthere:
    LD_HL(mNothingToPutAwayText);
    CALL(aMenuTextboxBackup);
    XOR_A_A;
    RET;

}

void DecoAction_setupornament(void){
    LD_HL(mWhichSidePutOnText);
    CALL(aDecoAction_AskWhichSide);
    IF_C goto cancel;
    CALL(aDecoAction_SetItUp_Ornament);
    IF_C goto cancel;
    LD_A(TRUE);
    LD_addr_A(wChangedDecorations);
    JR(mDecoAction_FinishUp_Ornament);


cancel:
    XOR_A_A;
    RET;

}

void DecoAction_putawayornament(void){
    LD_HL(mWhichSidePutAwayText);
    CALL(aDecoAction_AskWhichSide);
    IF_NC goto incave;
    XOR_A_A;
    RET;


incave:
    CALL(aDecoAction_PutItAway_Ornament);

    return DecoAction_FinishUp_Ornament();
}

void DecoAction_FinishUp_Ornament(void){
    CALL(aQueryWhichSide);
    LD_A_addr(wSelectedDecoration);
    LD_hl_A;
    LD_A_addr(wOtherDecoration);
    LD_de_A;
    XOR_A_A;
    RET;

}

void DecoAction_SetItUp_Ornament(void){
    LD_A_addr(wSelectedDecoration);
    AND_A_A;
    IF_Z goto nothingthere;
    LD_B_A;
    LD_A_addr(wMenuSelection);
    CP_A_B;
    IF_Z goto failed;
    LD_A_B;
    LD_HL(wStringBuffer3);
    CALL(aGetDecorationName);
    LD_A_addr(wMenuSelection);
    LD_HL(wStringBuffer4);
    CALL(aGetDecorationName);
    LD_A_addr(wMenuSelection);
    LD_addr_A(wSelectedDecoration);
    CALL(aDecoAction_SetItUp_Ornament_getwhichside);
    LD_HL(mPutAwayAndSetUpText);
    CALL(aMenuTextboxBackup);
    XOR_A_A;
    RET;


nothingthere:
    LD_A_addr(wMenuSelection);
    LD_addr_A(wSelectedDecoration);
    CALL(aDecoAction_SetItUp_Ornament_getwhichside);
    LD_A_addr(wMenuSelection);
    LD_HL(wStringBuffer3);
    CALL(aGetDecorationName);
    LD_HL(mSetUpTheDecoText);
    CALL(aMenuTextboxBackup);
    XOR_A_A;
    RET;


failed:
    LD_HL(mAlreadySetUpText);
    CALL(aMenuTextboxBackup);
    SCF;
    RET;


getwhichside:
    LD_A_addr(wMenuSelection);
    LD_B_A;
    LD_A_addr(wOtherDecoration);
    CP_A_B;
    RET_NZ ;
    XOR_A_A;
    LD_addr_A(wOtherDecoration);
    RET;

}

void WhichSidePutOnText(void){
    //text_far ['_WhichSidePutOnText']
    //text_end ['?']

    return DecoAction_PutItAway_Ornament();
}

void DecoAction_PutItAway_Ornament(void){
    LD_A_addr(wSelectedDecoration);
    AND_A_A;
    IF_Z goto nothingthere;
    LD_HL(wStringBuffer3);
    CALL(aGetDecorationName);
    LD_A(TRUE);
    LD_addr_A(wChangedDecorations);
    XOR_A_A;
    LD_addr_A(wSelectedDecoration);
    LD_HL(mPutAwayTheDecoText);
    CALL(aMenuTextboxBackup);
    XOR_A_A;
    RET;


nothingthere:
    LD_HL(mNothingToPutAwayText);
    CALL(aMenuTextboxBackup);
    XOR_A_A;
    RET;

}

void WhichSidePutAwayText(void){
    //text_far ['_WhichSidePutAwayText']
    //text_end ['?']

    return DecoAction_AskWhichSide();
}

void DecoAction_AskWhichSide(void){
    CALL(aMenuTextbox);
    LD_HL(mDecoSideMenuHeader);
    CALL(aGetMenu2);
    CALL(aExitMenu);
    CALL(aCopyMenuData);
    IF_C goto nope;
    LD_A_addr(wMenuCursorY);
    CP_A(3);  // cancel
    IF_Z goto nope;
    LD_addr_A(wSelectedDecorationSide);
    CALL(aQueryWhichSide);
    LD_A_hl;
    LD_addr_A(wSelectedDecoration);
    LD_A_de;
    LD_addr_A(wOtherDecoration);
    XOR_A_A;
    RET;


nope:
    SCF;
    RET;

}

void QueryWhichSide(void){
    LD_HL(wDecoRightOrnament);
    LD_DE(wDecoLeftOrnament);
    LD_A_addr(wSelectedDecorationSide);
    CP_A(1);  // right side
    RET_Z ;
// left side, swap hl and de
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    POP_DE;
    RET;

}

void DecoSideMenuHeader(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', '13', '7'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR'];  // flags
    //db ['3'];  // items
    //db ['"RIGHT SIDE@"'];
    //db ['"LEFT SIDE@"'];
    //db ['"CANCEL@"'];

    return PutAwayTheDecoText();
}

void PutAwayTheDecoText(void){
    //text_far ['_PutAwayTheDecoText']
    //text_end ['?']

    return NothingToPutAwayText();
}

void NothingToPutAwayText(void){
    //text_far ['_NothingToPutAwayText']
    //text_end ['?']

    return SetUpTheDecoText();
}

void SetUpTheDecoText(void){
    //text_far ['_SetUpTheDecoText']
    //text_end ['?']

    return PutAwayAndSetUpText();
}

void PutAwayAndSetUpText(void){
    //text_far ['_PutAwayAndSetUpText']
    //text_end ['?']

    return AlreadySetUpText();
}

void AlreadySetUpText(void){
    //text_far ['_AlreadySetUpText']
    //text_end ['?']

    return GetDecorationName_c_de();
}

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

void DecorationFlagAction_c(void){
    LD_A_C;
    JP(mDecorationFlagAction);

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
    EventFlagAction_Conv2(EVENT_PLAYERS_ROOM_POSTER, b);
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
        EventFlagAction_Conv2(de, SET_FLAG);
        return;
    }
    // CALL(av_GetDecorationSprite);
    // LD_hl_A;
    *hl = v_GetDecorationSprite_Conv(a);
    // LD_B(RESET_FLAG);
    // JP(mEventFlagAction);
    EventFlagAction_Conv2(de, RESET_FLAG);
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
