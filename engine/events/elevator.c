#include "../../constants.h"
#include "elevator.h"
#include "../../home/copy.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/scrolling_menu.h"
#include "../../home/map_objects.h"
#include "../../data/text/common.h"
#include "../../data/events/elevator_floors.h"

static const struct ElevatorData* sElevatorPointer;

static void Elevator_LoadFloors(void);
static void Elevator_LoadPointer(const struct ElevatorData* de);
static u8_flag_s Elevator_FindCurrentFloor(void);
static void Elevator_GoToFloor(uint8_t a);
static u8_flag_s Elevator_AskWhichFloor(void);

bool Elevator(const struct ElevatorData* de){
    u8_flag_s res;
    // CALL(aElevator_LoadPointer);
    Elevator_LoadPointer(de);
    // CALL(aElevator_FindCurrentFloor);
    res = Elevator_FindCurrentFloor();
    // IF_C goto quit;
    if(res.flag)
        return true;
    // LD_addr_A(wElevatorOriginFloor);
    wram->wElevatorOriginFloor = res.a;
    // CALL(aElevator_AskWhichFloor);
    res = Elevator_AskWhichFloor();
    // IF_C goto quit;
    if(res.flag)
        return true;
    // LD_HL(wElevatorOriginFloor);
    // CP_A_hl;
    // IF_Z goto quit;
    if(wram->wElevatorOriginFloor == res.a)
        return true;
    // CALL(aElevator_GoToFloor);
    Elevator_GoToFloor(res.a);
    // AND_A_A;
    // RET;
    return false;

// quit:
    // SCF;
    // RET;
}

static void Elevator_LoadPointer(const struct ElevatorData* de) {
    // LD_A_B;
    // LD_addr_A(wElevatorPointerBank);
    // LD_A_E;
    // LD_addr_A(wElevatorPointer);
    // LD_A_D;
    // LD_addr_A(wElevatorPointer + 1);
    sElevatorPointer = de;
    // CALL(aElevator_LoadFloors);
    Elevator_LoadFloors();
    // RET;
}

static void Elevator_LoadFloors(void) {
    // LD_DE(wCurElevatorCount);
    // LD_BC(wElevatorDataEnd - wElevatorData);
    // LD_HL(wElevatorPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wElevatorPointerBank);
    // CALL(aGetFarByte);
    // INC_HL;
    // LD_de_A;
    // INC_DE;
    wram->wCurElevatorCount = sElevatorPointer->count;
    //assert ['wCurElevatorCount + 1 == wCurElevatorFloors'];

    for(uint32_t i = 0; i < wram->wCurElevatorCount; ++i) {
    // loop:
        // LD_A_addr(wElevatorPointerBank);
        // CALL(aGetFarByte);
        // LD_de_A;
        wram->wCurElevatorFloors[i] = sElevatorPointer->floorData[i].floor;
        // INC_DE;
        // ADD_HL_BC;
        // CP_A(-1);
        // IF_NZ goto loop;
    }
    // RET;
    return;
}

static u8_flag_s Elevator_FindCurrentFloor(void) {
    // LD_HL(wElevatorPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wElevatorPointerBank);
    // CALL(aGetFarByte);
    // LD_C_A;
    uint8_t c = sElevatorPointer->count;
    // INC_HL;
    // LD_A_addr(wBackupMapGroup);
    // LD_D_A;
    uint8_t d = gCurMapData.backupMapGroup;
    // LD_A_addr(wBackupMapNumber);
    // LD_E_A;
    uint8_t e = gCurMapData.backupMapNumber;
    // LD_B(0);

    for(uint32_t i = 0; i < c; ++i) {
    // loop2:
        // LD_A_addr(wElevatorPointerBank);
        // CALL(aGetFarByte);
        // CP_A(-1);
        // IF_Z goto fail;
        // INC_HL;
        // INC_HL;
        // LD_A_addr(wElevatorPointerBank);
        // CALL(aGetFarByte);
        // INC_HL;
        // CP_A_D;
        // IF_NZ goto next1;
        // LD_A_addr(wElevatorPointerBank);
        // CALL(aGetFarByte);
        // INC_HL;
        // CP_A_E;
        // IF_NZ goto next2;
        // goto done;
        if(sElevatorPointer->floorData[i].mapGroup == d && sElevatorPointer->floorData[i].mapNum == e) {
        // done:
            // XOR_A_A;
            // LD_A_B;
            // RET;
            return u8_flag((uint8_t)i, false);
        }

    // next1:
        // INC_HL;

    // next2:
        // INC_B;
        // goto loop2;
    }


// fail:
    // SCF;
    // RET;
    return u8_flag(0, true);
}

static void Elevator_GoToFloor(uint8_t a){
    // PUSH_AF;
    // LD_HL(wElevatorPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // INC_HL;
    // POP_AF;
    // LD_BC(wElevatorDataEnd - wElevatorData);
    // CALL(aAddNTimes);
    // INC_HL;
    // LD_DE(wBackupWarpNumber);
    // LD_A_addr(wElevatorPointerBank);
    // LD_BC(wElevatorDataEnd - wElevatorData - 1);
    // CALL(aFarCopyBytes);
    gCurMapData.backupWarpNumber = sElevatorPointer->floorData[a].warpNum;
    gCurMapData.backupMapGroup = sElevatorPointer->floorData[a].mapGroup;
    gCurMapData.backupMapNumber = sElevatorPointer->floorData[a].mapNum;
    // RET;
}

static const txt_cmd_s AskFloorElevatorText[] = {
    text_far(v_AskFloorElevatorText)
    text_end
};

static u8_flag_s Elevator_AskWhichFloor(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // LD_HL(mAskFloorElevatorText);
    // CALL(aPrintText);
    PrintText(AskFloorElevatorText);
    // CALL(aElevator_GetCurrentFloorText);
    Elevator_GetCurrentFloorText();
    // LD_HL(mElevator_MenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&Elevator_MenuHeader);
    // CALL(aInitScrollingMenu);
    InitScrollingMenu();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // XOR_A_A;
    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = 0;
    // CALL(aScrollingMenu);
    uint8_t joypad = ScrollingMenu();
    // CALL(aCloseWindow);
    CloseWindow();
    // LD_A_addr(wMenuJoypad);
    // CP_A(B_BUTTON);
    // IF_Z goto cancel;
    if(joypad == B_BUTTON) {
    // cancel:
        // SCF;
        // RET;
        return u8_flag(0x0, true);
    }
    // XOR_A_A;
    // LD_A_addr(wScrollingMenuCursorPosition);
    // RET;
    return u8_flag(wram->wScrollingMenuCursorPosition, false);
}

void Elevator_GetCurrentFloorText(void){
    static const char Elevator_CurrentFloorText[] = "Now on:@";
    // LD_HL(wOptions);
    // LD_A_hl;
    uint8_t options = gOptions.options;
    // PUSH_AF;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // hlcoord(0, 0, wTilemap);
    // LD_B(4);
    // LD_C(8);
    // CALL(aTextbox);
    Textbox(coord(0, 0, wram->wTilemap), 4, 8);
    // hlcoord(1, 2, wTilemap);
    // LD_DE(mElevator_CurrentFloorText);
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = U82C(Elevator_CurrentFloorText), .hl = coord(1, 2, wram->wTilemap)};
    PlaceString(&st, st.hl);
    // hlcoord(4, 4, wTilemap);
    // CALL(aElevator_GetCurrentFloorString);
    Elevator_GetCurrentFloorString(coord(4, 4, wram->wTilemap));
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // RET;
}

void Elevator_GetCurrentFloorString(tile_t* hl){
    // PUSH_HL;
    // LD_A_addr(wElevatorOriginFloor);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wCurElevatorFloors);
    // ADD_HL_DE;
    // LD_A_hl;
    // POP_DE;
    // CALL(aGetFloorString);
    // RET;
    return GetFloorString(hl, wram->wCurElevatorFloors[wram->wElevatorOriginFloor]);
}

const struct MenuHeader Elevator_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(12, 1, 18, 9),
    .data = &(struct MenuData) {
    // Elevator_MenuData
        .flags = SCROLLINGMENU_DISPLAY_ARROWS,  // flags
        .scrollingMenu = {
            .rows = 4, .cols = 0,  // rows, columns
            .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
            //dbw ['0', 'wCurElevatorCount']
            .list = wram_ptr(wCurElevatorCount),
            //dba ['GetElevatorFloorStrings']
            .func1 = GetElevatorFloorStrings,
            //dba ['NULL']
            .func2 = NULL,
            //dba ['NULL']
            .func3 = NULL,
        },
    },
    .defaultOption = 1  // default option
};

void GetElevatorFloorStrings(const struct MenuData* data, tile_t* de){
    // LD_A_addr(wMenuSelection);
    (void)data;
    return GetFloorString(de, wram->wMenuSelection);
}

void GetFloorString(tile_t* de, uint8_t a){
    // PUSH_DE;
    // CALL(aFloorToString);
    // LD_D_H;
    // LD_E_L;
    const char* str = FloorToString(a);
    // POP_HL;
    // JP(mPlaceString);
    PlaceStringSimple(U82C(str), de);
}

const char* FloorToString(uint8_t a){
    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mElevatorFloorNames);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_DE;
    // RET;
    return ElevatorFloorNames[a];
// INCLUDE "data/events/elevator_floors.asm"

}
