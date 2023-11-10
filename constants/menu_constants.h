// MenuHeader flags
enum {
    MENU_RESTORE_TILES = 1,  // Will be set if MENU_BACKUP_TILES(_2) is set.
    MENU_UNUSED_1 = 2,
    MENU_UNUSED_2 = 4,
    MENU_NO_CLICK_SFX = 8,
    MENU_SPRITE_ANIMS = 16,
    MENU_UNUSED_3 = 32,
    MENU_BACKUP_TILES = 64,
    MENU_BACKUP_TILES_2 = 128,
};

// MenuHeader bit flags
enum {
    MENU_RESTORE_TILES_F,  // Will be set if MENU_BACKUP_TILES(_2) is set.
    MENU_UNUSED_1_F,
    MENU_UNUSED_2_F,
    MENU_NO_CLICK_SFX_F,
    MENU_SPRITE_ANIMS_F,
    MENU_UNUSED_3_F,
    MENU_BACKUP_TILES_F,
    MENU_BACKUP_TILES_2_F,
};

// VerticalMenu/DoNthMenu/SetUpMenu/_2DMenu MenuData flags
// Per flag the comment specifies which menus actually implement it
enum {
    STATICMENU_DISABLE_B = 1,          // VerticalMenu/_2DMenu
    STATICMENU_ENABLE_SELECT = 2,      // VerticalMenu/_2DMenu
    STATICMENU_ENABLE_LEFT_RIGHT = 4,  // DoNthMenu/SetUpMenu
    STATICMENU_ENABLE_START = 8,       // DoNthMenu/SetUpMenu
    STATICMENU_PLACE_TITLE = 16,       // VerticalMenu
    STATICMENU_WRAP = 32,              // All
    STATICMENU_NO_TOP_SPACING = 64,    // VerticalMenu/_2DMenu
    STATICMENU_CURSOR = 128,           // VerticalMenu/_2DMenu
};

// VerticalMenu/DoNthMenu/SetUpMenu/_2DMenu MenuData bit flags
// Per flag the comment specifies which menus actually implement it
enum {
    STATICMENU_DISABLE_B_F,          // VerticalMenu/_2DMenu
    STATICMENU_ENABLE_SELECT_F,      // VerticalMenu/_2DMenu
    STATICMENU_ENABLE_LEFT_RIGHT_F,  // DoNthMenu/SetUpMenu
    STATICMENU_ENABLE_START_F,       // DoNthMenu/SetUpMenu
    STATICMENU_PLACE_TITLE_F,        // VerticalMenu
    STATICMENU_WRAP_F,               // All
    STATICMENU_NO_TOP_SPACING_F,     // VerticalMenu/_2DMenu
    STATICMENU_CURSOR_F,             // VerticalMenu/_2DMenu
};

// ScrollingMenu MenuData flags
enum {
    SCROLLINGMENU_CALL_FUNCTION1_CANCEL = 1,
    SCROLLINGMENU_CALL_FUNCTION3_NO_SWITCH = 2,
    SCROLLINGMENU_ENABLE_LEFT = 4,
    SCROLLINGMENU_ENABLE_RIGHT = 8,
    SCROLLINGMENU_DISPLAY_ARROWS = 16,
    SCROLLINGMENU_ENABLE_FUNCTION3 = 32,
    SCROLLINGMENU_ENABLE_START = 64,
    SCROLLINGMENU_ENABLE_SELECT = 128,
};

// ScrollingMenu items structure format
enum {
    SCROLLINGMENU_ITEMS_NORMAL,
    SCROLLINGMENU_ITEMS_QUANTITY,
};

// MonMenuOptions indexes (see data/mon_menu.asm)
// used by PokemonActionSubmenu (see engine/pokemon/mon_menu.asm)
enum {
    // moves
    MONMENUITEM_CUT = 1,     // 1
    MONMENUITEM_FLY,         // 2
    MONMENUITEM_SURF,        // 3
    MONMENUITEM_STRENGTH,    // 4
    MONMENUITEM_WATERFALL,   // 5
    MONMENUITEM_FLASH,       // 6
    MONMENUITEM_WHIRLPOOL,   // 7
    MONMENUITEM_DIG,         // 8
    MONMENUITEM_TELEPORT,    // 9
    MONMENUITEM_SOFTBOILED,  // 10
    MONMENUITEM_HEADBUTT,    // 11
    MONMENUITEM_ROCKSMASH,   // 12
    MONMENUITEM_MILKDRINK,   // 13
    MONMENUITEM_SWEETSCENT,  // 14
    // options
    MONMENUITEM_STATS,   // 15
    MONMENUITEM_SWITCH,  // 16
    MONMENUITEM_ITEM,    // 17
    MONMENUITEM_CANCEL,  // 18
    MONMENUITEM_MOVE,    // 19
    MONMENUITEM_MAIL,    // 20
    MONMENUITEM_ERROR,   // 21
};
#define NUM_MONMENUITEMS MONMENUITEM_ERROR

// MonMenuOptions categories
#define MONMENU_FIELD_MOVE 0
#define MONMENU_MENUOPTION 1

#define NUM_MONMENU_ITEMS 8

// start/select menu return values
#define HMENURETURN_SCRIPT 0b10000000
#define HMENURETURN_ASM 0b11111111

// PartyMenuQualityPointers indexes (see data/party_menu_qualities.asm)
enum {
    PARTYMENUACTION_CHOOSE_POKEMON,
    PARTYMENUACTION_HEALING_ITEM,
    PARTYMENUACTION_SWITCH,
    PARTYMENUACTION_TEACH_TMHM,
    PARTYMENUACTION_MOVE,
    PARTYMENUACTION_EVO_STONE,
    PARTYMENUACTION_GIVE_MON,
    PARTYMENUACTION_GIVE_MON_FEMALE,  // unused
    PARTYMENUACTION_GIVE_ITEM,
    PARTYMENUACTION_MOBILE,
    NUM_PARTYMENUACTIONS,
    // PrintPartyMenuActionText arguments (see engine/pokemon/party_menu.asm)
    PARTYMENUTEXT_HEAL_PSN = 0xF0,
    PARTYMENUTEXT_HEAL_BRN,
    PARTYMENUTEXT_HEAL_FRZ,
    PARTYMENUTEXT_HEAL_SLP,
    PARTYMENUTEXT_HEAL_PAR,
    PARTYMENUTEXT_HEAL_HP,
    PARTYMENUTEXT_HEAL_ALL,
    PARTYMENUTEXT_REVIVE,
    PARTYMENUTEXT_LEVEL_UP,
    PARTYMENUTEXT_HEAL_CONFUSION,
};

// Naming types (see engine/menus/naming_screen.asm)
enum {
    NAME_MON,
    NAME_PLAYER,
    NAME_RIVAL,
    NAME_MOM,
    NAME_BOX,
    NAME_FRIEND,
    NAME_6,  // duplicate of NAME_MON
    NAME_7,  // duplicate of NAME_MON
    NUM_NAME_TYPES,
};

// 2D Menu Flags 1
enum {
    MENU2D_HORIZONTAL_WRAP_F = 4,
    MENU2D_VERTICAL_WRAP_F = 5,
    MENU2D_DISABLE_MENU_FILTER_F = 7,
};
