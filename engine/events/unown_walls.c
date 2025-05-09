#include "../../constants.h"
#include "unown_walls.h"
#include "../../home/map.h"
#include "../../home/flag.h"
#include "../../home/menu.h"
#include "../../home/map_objects.h"
#include "../../home/tilemap.h"
#include "../../home/joypad.h"
#include "../../home/audio.h"
#include "../../home/item.h"
#include "../../data/maps/attributes.h"
#include "../../data/events/unown_walls.h"

void HoOhChamber(void){
    // LD_HL(wPartySpecies);
    // LD_A_hl;
    // CP_A(HO_OH);  // is Ho-oh the first Pokémon in the party?
    // IF_NZ goto done;  // if not, we're done
    if(wram->wPartySpecies[0] == HO_OH) {
        // CALL(aGetMapAttributesPointer);  // pointless?
        // LD_DE(EVENT_WALL_OPENED_IN_HO_OH_CHAMBER);
        // LD_B(SET_FLAG);
        // CALL(aEventFlagAction);
        EventFlagAction(EVENT_WALL_OPENED_IN_HO_OH_CHAMBER, SET_FLAG);
    }

// done:
    // RET;
}

void OmanyteChamber(void){
    // CALL(aGetMapAttributesPointer);  // pointless?
    // LD_DE(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER);
    // LD_B(CHECK_FLAG);
    // CALL(aEventFlagAction);
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto nope;
    if(EventFlagAction(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER, CHECK_FLAG))
        return;

    // LD_A(WATER_STONE);
    // LD_addr_A(wCurItem);
    // LD_HL(wNumItems);
    // CALL(aCheckItem);
    // IF_C goto open;
    if(!CheckItem(GetItemPocket(ITEM_POCKET), WATER_STONE)) {
        // LD_A_addr(wPartyCount);
        // LD_B_A;
        // INC_B;
        uint8_t b = wram->wPartyCount + 1;

        item_t item;
        do {
        // loop:
            // DEC_B;
            --b;
            // IF_Z goto nope;
            if(b == 0)
                return;
            // LD_A_B;
            // DEC_A;
            // LD_addr_A(wCurPartyMon);
            // PUSH_BC;
            // LD_A(MON_ITEM);
            // CALL(aGetPartyParamLocation);
            // POP_BC;
            // LD_A_hl;
            item = wram->wPartyMon[b - 1].mon.item;
            // CP_A(WATER_STONE);
            // IF_NZ goto loop;
        } while(item != WATER_STONE);
    }

// open:
    // CALL(aGetMapAttributesPointer);  // pointless?
    // LD_DE(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER);
    // LD_B(SET_FLAG);
    // CALL(aEventFlagAction);
    EventFlagAction(EVENT_WALL_OPENED_IN_OMANYTE_CHAMBER, SET_FLAG);

// nope:
    // RET;
}

bool SpecialAerodactylChamber(void){
    // PUSH_DE;
    // PUSH_BC;

    // CALL(aGetMapAttributesPointer);
    const struct MapAttr* attr = GetMapAttributesPointer();
    // LD_A_H;
    // CP_A(HIGH(aRuinsOfAlphAerodactylChamber_MapAttributes));
    // IF_NZ goto nope;
    // LD_A_L;
    // CP_A(LOW(aRuinsOfAlphAerodactylChamber_MapAttributes));
    // IF_NZ goto nope;
    if(attr != &RuinsOfAlphAerodactylChamber_MapAttributes)
        return false;

    // LD_DE(EVENT_WALL_OPENED_IN_AERODACTYL_CHAMBER);
    // LD_B(SET_FLAG);
    // CALL(aEventFlagAction);
    EventFlagAction(EVENT_WALL_OPENED_IN_AERODACTYL_CHAMBER, SET_FLAG);

    // SCF;
    // goto done;


// nope:
    // AND_A_A;


// done:
    // POP_BC;
    // POP_DE;
    // RET;
    return true;
}

void SpecialKabutoChamber(void){
    // PUSH_HL;
    // PUSH_DE;

    // CALL(aGetMapAttributesPointer);
    const struct MapAttr* attr = GetMapAttributesPointer();
    // LD_A_H;
    // CP_A(HIGH(aRuinsOfAlphKabutoChamber_MapAttributes));
    // IF_NZ goto done;
    // LD_A_L;
    // CP_A(LOW(aRuinsOfAlphKabutoChamber_MapAttributes));
    // IF_NZ goto done;
    if(attr == &RuinsOfAlphKabutoChamber_MapAttributes) {
        // LD_DE(EVENT_WALL_OPENED_IN_KABUTO_CHAMBER);
        // LD_B(SET_FLAG);
        // CALL(aEventFlagAction);
        EventFlagAction(EVENT_WALL_OPENED_IN_KABUTO_CHAMBER, SET_FLAG);
    }

// done:
    // POP_DE;
    // POP_HL;
    // RET;
}

void DisplayUnownWords(void){
    // LD_A_addr(wScriptVar);
    // LD_HL(mMenuHeaders_UnownWalls);
    // AND_A_A;
    // IF_Z goto load;

    // LD_D(0x0);
    // LD_E(0x5);
    const struct MenuHeader* hdr = MenuHeaders_UnownWalls + wram->wScriptVar;

// loop:
    // ADD_HL_DE;
    // DEC_A;
    // IF_NZ goto loop;


// load:
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(hdr);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aMenuBox);
    MenuBox();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // CALL(aMenuBoxCoord2Tile);
    tile_t* hl = MenuBoxCoord2Tile();
    // INC_HL;
    // LD_D(0);
    // LD_E(SCREEN_WIDTH);
    // ADD_HL_DE;
    // ADD_HL_DE;
    hl += 2*SCREEN_WIDTH + 1;
    // LD_A_addr(wScriptVar);
    // LD_C_A;
    // LD_DE(mUnownWalls);
    const uint8_t* de = UnownWalls[wram->wScriptVar];
    // AND_A_A;
    // IF_Z goto copy;

// loop2:
    // LD_A_de;
    // INC_DE;
    // CP_A(-1);
    // IF_NZ goto loop2;
    // DEC_C;
    // IF_NZ goto loop2;

// copy:
    // CALL(av_DisplayUnownWords_CopyWord);
    v_DisplayUnownWords_CopyWord(hl, de);
    // LD_BC(wAttrmap - wTilemap);
    // ADD_HL_BC;
    hl += wAttrmap - wTilemap;
    // CALL(av_DisplayUnownWords_FillAttr);
    v_DisplayUnownWords_FillAttr(hl, de);
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // CALL(aCloseWindow);
    CloseWindow();
    // RET;
// INCLUDE "data/events/unown_walls.asm"
}

static void v_DisplayUnownWords_FillAttr_PlaceSquare(uint8_t* hl, uint8_t a) {
    // PUSH_HL;
    // LD_hli_A;
    hl[0] = a;
    // LD_hld_A;
    hl[1] = a;
    // LD_B(0);
    // LD_C(SCREEN_WIDTH);
    // ADD_HL_BC;
    // LD_hli_A;
    hl[SCREEN_WIDTH] = a;
    // LD_hl_A;
    hl[SCREEN_WIDTH + 1] = a;
    // POP_HL;
    // RET;
}

void v_DisplayUnownWords_FillAttr(uint8_t* hl, const uint8_t* de){
    while(*de != 0xff) {
        // LD_A_de;
        // CP_A(0xff);
        // RET_Z ;
        // CP_A(0x60);
        // LD_A(VRAM_BANK_1 | PAL_BG_BROWN);
        // IF_C goto got_pal;
        // LD_A(PAL_BG_BROWN);
        uint8_t a = (*de < 0x60)? VRAM_BANK_1 | PAL_BG_BROWN: PAL_BG_BROWN;

    // got_pal:
        // CALL(av_DisplayUnownWords_FillAttr_PlaceSquare);
        v_DisplayUnownWords_FillAttr_PlaceSquare(hl, a);
        // INC_HL;
        // INC_HL;
        hl += 2;
        // INC_DE;
        de++;
        // JR(mv_DisplayUnownWords_FillAttr);
    }

}

static void v_DisplayUnownWords_CopyWord_ConvertChar(uint8_t* hl, uint8_t c) {
    // PUSH_HL;
    // LD_A_C;
    // CP_A(0x60);
    // IF_Z goto Tile60;
    if(c == 0x60) {
    // Tile60:
        // LD_hl(0x5b);
        hl[0] = 0x5b;
        // INC_HL;
        // LD_hl(0x5c);
        hl[1] = 0x5c;
        // LD_BC(SCREEN_WIDTH - 1);
        // ADD_HL_BC;
        // LD_hl(0x4d);
        hl[SCREEN_WIDTH] = 0x4d;
        // INC_HL;
        // LD_hl(0x5d);
        hl[SCREEN_WIDTH + 1] = 0x5d;
        // POP_HL;
        // RET;
        return;
    }
    // CP_A(0x62);
    // IF_Z goto Tile62;
    else if(c == 0x62) {
    // Tile62:
        // LD_hl(0x4e);
        hl[0] = 0x4e;
        // INC_HL;
        // LD_hl(0x4f);
        hl[1] = 0x4f;
        // LD_BC(SCREEN_WIDTH - 1);
        // ADD_HL_BC;
        // LD_hl(0x5e);
        hl[SCREEN_WIDTH] = 0x5e;
        // INC_HL;
        // LD_hl(0x5f);
        hl[SCREEN_WIDTH + 1] = 0x5f;
        // POP_HL;
        // RET;
        return;
    }
    // CP_A(0x64);
    // IF_Z goto Tile64;
    else if(c == 0x64) {
    // Tile64:
        // LD_hl(0x2);
        hl[0] = 0x2;
        // INC_HL;
        // LD_hl(0x3);
        hl[1] = 0x3;
        // LD_BC(SCREEN_WIDTH - 1);
        // ADD_HL_BC;
        // LD_hl(0x3);
        hl[SCREEN_WIDTH] = 0x3;
        // INC_HL;
        // LD_hl(0x2);
        hl[SCREEN_WIDTH + 1] = 0x2;
        // POP_HL;
        // RET;
        return;
    }
    // LD_hli_A;
    hl[0] = c;
    // INC_A;
    // LD_hld_A;
    hl[1] = c + 1;
    // DEC_A;
    // LD_B(0);
    // LD_C(SCREEN_WIDTH);
    // ADD_HL_BC;
    // LD_C(0x10);
    // ADD_A_C;
    // LD_hli_A;
    hl[SCREEN_WIDTH] = c + 0x10;
    // INC_A;
    // LD_hl_A;
    hl[SCREEN_WIDTH + 1] = c + 0x11;
    // POP_HL;
    // RET;
}

void v_DisplayUnownWords_CopyWord(uint8_t* hl, const uint8_t* de){
    // PUSH_HL;
    // PUSH_DE;

    while(*de != 0xff) {
    // word_loop:
        // LD_A_de;
        // CP_A(0xff);
        // IF_Z goto word_done;
        // LD_C_A;
        // CALL(av_DisplayUnownWords_CopyWord_ConvertChar);
        v_DisplayUnownWords_CopyWord_ConvertChar(hl, *de);
        // INC_HL;
        // INC_HL;
        hl += 2;
        // INC_DE;
        de++;
        // goto word_loop;
    }


// word_done:
    // POP_DE;
    // POP_HL;
    // RET;
}
