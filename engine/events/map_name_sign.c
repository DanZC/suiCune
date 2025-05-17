#include "../../constants.h"
#include "map_name_sign.h"
#include "../../home/map.h"
#include "../overworld/landmarks.h"
#include "../../charmap.h"
#include "../../home/text.h"
#include "../gfx/dma_transfer.h"

#define MAP_NAME_SIGN_START (0x60)

static void LoadMapNameSignGFX(void);
static void InitMapNameFrame(void);
static void PlaceMapNameCenterAlign(void);
static void InitMapSignAttrmap(tile_t* tm, uint8_t b, uint8_t c);
static void PlaceMapNameFrame(void);

static bool InitMapNameSign_CheckNationalParkGate(void) {
    // LD_A_addr(wMapGroup);
    // CP_A(GROUP_ROUTE_35_NATIONAL_PARK_GATE);
    // RET_NZ ;
    if(wram->wMapGroup != GROUP_ROUTE_35_NATIONAL_PARK_GATE)
        return false;
    // LD_A_addr(wMapNumber);
    // CP_A(MAP_ROUTE_35_NATIONAL_PARK_GATE);
    // RET_Z ;
    // CP_A(MAP_ROUTE_36_NATIONAL_PARK_GATE);
    // RET;
    return wram->wMapNumber == MAP_ROUTE_35_NATIONAL_PARK_GATE || wram->wMapNumber == MAP_ROUTE_36_NATIONAL_PARK_GATE;
}

static bool InitMapNameSign_CheckMovingWithinLandmark(void) {
    // LD_A_addr(wCurLandmark);
    // LD_C_A;
    // LD_A_addr(wPrevLandmark);
    // CP_A_C;
    // RET_Z ;
    if(wram->wCurLandmark == wram->wPrevLandmark)
        return true;
    // CP_A(LANDMARK_SPECIAL);
    // RET;
    return wram->wPrevLandmark == LANDMARK_SPECIAL;
}

static bool InitMapNameSign_CheckSpecialMap(uint8_t a) {
//  These landmarks do not get pop-up signs.
    // CP_A(-1);
    // RET_Z ;
    if(a == 0xff)
        return true;
    // CP_A(LANDMARK_SPECIAL);  // redundant check
    // RET_Z ;
    if(a == LANDMARK_SPECIAL)
        return true;
    // CP_A(LANDMARK_RADIO_TOWER);
    // RET_Z ;
    if(a == LANDMARK_RADIO_TOWER)
        return true;
    // CP_A(LANDMARK_LAV_RADIO_TOWER);
    // RET_Z ;
    if(a == LANDMARK_LAV_RADIO_TOWER)
        return true;
    // CP_A(LANDMARK_UNDERGROUND_PATH);
    // RET_Z ;
    if(a == LANDMARK_UNDERGROUND_PATH)
        return true;
    // CP_A(LANDMARK_INDIGO_PLATEAU);
    // RET_Z ;
    if(a == LANDMARK_INDIGO_PLATEAU)
        return true;
    // CP_A(LANDMARK_POWER_PLANT);
    // RET_Z ;
    if(a == LANDMARK_POWER_PLANT)
        return true;
    // LD_A(1);
    // AND_A_A;
    // RET;
    return false;
}

void InitMapNameSign(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // FARCALL(aInitMapNameSign_inefficient_farcall);  // this is a waste of 6 ROM bytes and 6 stack bytes
    // RET;

//  should have just been a fallthrough

// inefficient_farcall:
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aGetWorldMapLocation);
    uint8_t loc = GetWorldMapLocation(wram->wMapGroup, wram->wMapNumber);

    // LD_addr_A(wCurLandmark);
    wram->wCurLandmark = loc;
    // CALL(aInitMapNameSign_CheckNationalParkGate);
    // IF_Z goto gate;

    // CALL(aGetMapEnvironment);
    // CP_A(GATE);
    // IF_NZ goto not_gate;
    if(InitMapNameSign_CheckNationalParkGate() || GetMapEnvironment() == GATE) {
    // gate:
        // LD_A(-1);
        // LD_addr_A(wCurLandmark);
        wram->wCurLandmark = 0xff;
    }


// not_gate:
    // LD_HL(wEnteredMapFromContinue);
    // BIT_hl(1);
    uint8_t map_from_cont = bit_test(wram->wEnteredMapFromContinue, 1);
    // RES_hl(1);
    bit_reset(wram->wEnteredMapFromContinue, 1);
    // IF_NZ goto dont_do_map_sign;

    // CALL(aInitMapNameSign_CheckMovingWithinLandmark);
    // IF_Z goto dont_do_map_sign;
    // LD_A_addr(wCurLandmark);
    // LD_addr_A(wPrevLandmark);

    // CALL(aInitMapNameSign_CheckSpecialMap);
    // IF_Z goto dont_do_map_sign;
    if(!map_from_cont 
    && !InitMapNameSign_CheckMovingWithinLandmark()
    && !(wram->wPrevLandmark = wram->wCurLandmark, InitMapNameSign_CheckSpecialMap(wram->wCurLandmark))) {
    //  Display for 60 frames
        // LD_A(60);
        // LD_addr_A(wLandmarkSignTimer);
        wram->wLandmarkSignTimer = 60;
        // CALL(aLoadMapNameSignGFX);
        LoadMapNameSignGFX();
        // CALL(aInitMapNameFrame);
        InitMapNameFrame();
        // FARCALL(aHDMATransfer_OnlyTopFourRows);
        HDMATransfer_OnlyTopFourRows();
        // RET;
        return;
    }


// dont_do_map_sign:
    // LD_A_addr(wCurLandmark);
    // LD_addr_A(wPrevLandmark);
    wram->wPrevLandmark = wram->wCurLandmark;
    // LD_A(0x90);
    // LDH_addr_A(rWY);
    gb_write(rWY, 0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    // RET;
    hram.hLCDCPointer = 0;
}

void PlaceMapNameSign(void){
    // LD_HL(wLandmarkSignTimer);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto disappear;
    uint8_t a = wram->wLandmarkSignTimer;
    if(a != 0) {
        // DEC_hl;
        wram->wLandmarkSignTimer--;
        // CP_A(60);
        // RET_Z ;
        if(a == 60)
            return;
        // CP_A(59);
        // IF_NZ goto already_initialized;
        if(a == 59) {
            // CALL(aInitMapNameFrame);
            InitMapNameFrame();
            // CALL(aPlaceMapNameCenterAlign);
            PlaceMapNameCenterAlign();
            // FARCALL(aHDMATransfer_OnlyTopFourRows);
            HDMATransfer_OnlyTopFourRows();
        }

    // already_initialized:
        // LD_A(0x80);
        // LD_A(0x70);
        // LDH_addr_A(rWY);
        gb_write(rWY, 0x70);
        // LDH_addr_A(hWY);
        hram.hWY = 0x70;
        // RET;
        return;
    }

// disappear:
    // LD_A(0x90);
    // LDH_addr_A(rWY);
    gb_write(rWY, 0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram.hLCDCPointer = 0;
    // RET;
}

static void LoadMapNameSignGFX(void){
    // LD_DE(mMapEntryFrameGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * MAP_NAME_SIGN_START);
    // LD_BC((BANK(aMapEntryFrameGFX) << 8) | 14);
    // CALL(aGet2bpp);
    // RET;
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * MAP_NAME_SIGN_START, "gfx/frames/map_entry_sign.png", 0, 14);
}

static void InitMapNameFrame(void){
    // hlcoord(0, 0, wTilemap);
    // LD_B(2);
    // LD_C(18);
    // CALL(aInitMapSignAttrmap);
    InitMapSignAttrmap(wram->wTilemap + coordidx(0, 0), 2, 18);
    // CALL(aPlaceMapNameFrame);
    PlaceMapNameFrame();
    // RET;
}

uint8_t PlaceMapNameCenterAlign_GetNameLength(void) {
    // LD_C(0);
    uint8_t c = 0;
    // PUSH_HL;
    // LD_HL(wStringBuffer1);
    uint8_t* hl = wram->wStringBuffer1;

    do {
    // loop:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(0x50);
        // IF_Z goto stop;
        if(a == CHAR_TERM)
            break;
        // CP_A(0xf6, 0xa1);
        // IF_Z goto loop;
        if(a == CHAR_LM_SLB)
            continue;
        // INC_C;
        c++;
        // goto loop;
    } while(1);

// stop:
    // POP_HL;
    // RET;
    return c;
}

static void PlaceMapNameCenterAlign(void){
    // LD_A_addr(wCurLandmark);
    // LD_E_A;
    // FARCALL(aGetLandmarkName);
    GetLandmarkName(wram->wCurLandmark);
    // CALL(aPlaceMapNameCenterAlign_GetNameLength);
    // LD_A(SCREEN_WIDTH);
    // SUB_A_C;
    // SRL_A;
    uint8_t a = (SCREEN_WIDTH - PlaceMapNameCenterAlign_GetNameLength()) >> 1;
    // LD_B(0);
    // LD_C_A;
    // hlcoord(0, 2, wTilemap);
    // ADD_HL_BC;
    // LD_DE(wStringBuffer1);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wStringBuffer1, coord(0, 2, wram->wTilemap) + a);
    // RET;
}

static void InitMapSignAttrmap(tile_t* tm, uint8_t b, uint8_t c){
    // LD_DE(wAttrmap - wTilemap);
    // ADD_HL_DE;
    uint8_t* hl = wram->wAttrmap + (tm - wram->wTilemap);
    // INC_B;
    // INC_B;
    b += 2;
    // INC_C;
    // INC_C;
    c += 2;
    // LD_A(PAL_BG_TEXT | PRIORITY);

    do {
    // loop:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // inner_loop:
            // LD_hli_A;
            *(hl++) = PAL_BG_TEXT | PRIORITY;
            // DEC_C;
            // IF_NZ goto inner_loop;
        } while(--c != 0);
        // POP_HL;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        hl = hl2 + SCREEN_WIDTH;
        // POP_BC;
        c = c2;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

static tile_t* PlaceMapNameFrame_FillTopBottom(tile_t* hl, uint8_t a) {
    // LD_C((SCREEN_WIDTH - 2) / 4 + 1);
    uint8_t c = (SCREEN_WIDTH - 2) / 4 + 1;
    // goto enterloop;

    while(1) {
    // enterloop:
        // INC_A;
        a++;
        // LD_hli_A;
        // LD_hli_A;
        *(hl++) = a;
        *(hl++) = a;
        // DEC_A;
        --a;
        // DEC_C;
        // IF_NZ goto continueloop;
        if(--c == 0) 
            break;
    // continueloop:
        // LD_hli_A;
        // LD_hli_A;
        *(hl++) = a;
        *(hl++) = a;
    }
    // RET;
    return hl;
}

static tile_t* PlaceMapNameFrame_FillMiddle(tile_t* hl) {
    // LD_C(SCREEN_WIDTH - 2);
    uint8_t c = SCREEN_WIDTH - 2;
    // LD_A(MAP_NAME_SIGN_START + 13);

    do {
    // loop:
        // LD_hli_A;
        *(hl++) = MAP_NAME_SIGN_START + 13;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
    return hl;
}

static void PlaceMapNameFrame(void){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
// top left
    // LD_A(MAP_NAME_SIGN_START + 1);
    // LD_hli_A;
    *(hl++) = MAP_NAME_SIGN_START + 1;
// top row
    // LD_A(MAP_NAME_SIGN_START + 2);
    // CALL(aPlaceMapNameFrame_FillTopBottom);
    hl = PlaceMapNameFrame_FillTopBottom(hl, MAP_NAME_SIGN_START + 2);
// top right
    // LD_A(MAP_NAME_SIGN_START + 4);
    // LD_hli_A;
    *(hl++) = MAP_NAME_SIGN_START + 4;
// left, first line
    // LD_A(MAP_NAME_SIGN_START + 5);
    // LD_hli_A;
    *(hl++) = MAP_NAME_SIGN_START + 5;
// first line
    // CALL(aPlaceMapNameFrame_FillMiddle);
    hl = PlaceMapNameFrame_FillMiddle(hl);
// right, first line
    // LD_A(MAP_NAME_SIGN_START + 11);
    // LD_hli_A;
    *(hl++) = MAP_NAME_SIGN_START + 11;
// left, second line
    // LD_A(MAP_NAME_SIGN_START + 6);
    // LD_hli_A;
    *(hl++) = MAP_NAME_SIGN_START + 6;
// second line
    // CALL(aPlaceMapNameFrame_FillMiddle);
    hl = PlaceMapNameFrame_FillMiddle(hl);
// right, second line
    // LD_A(MAP_NAME_SIGN_START + 12);
    // LD_hli_A;
    *(hl++) = MAP_NAME_SIGN_START + 12;
// bottom left
    // LD_A(MAP_NAME_SIGN_START + 7);
    // LD_hli_A;
    *(hl++) = MAP_NAME_SIGN_START + 7;
// bottom
    // LD_A(MAP_NAME_SIGN_START + 8);
    // CALL(aPlaceMapNameFrame_FillTopBottom);
    hl = PlaceMapNameFrame_FillTopBottom(hl, MAP_NAME_SIGN_START + 8);
// bottom right
    // LD_A(MAP_NAME_SIGN_START + 10);
    // LD_hl_A;
    *hl = MAP_NAME_SIGN_START + 10;
    // RET;
}
