#include "../../constants.h"
#include "mon_icons.h"
#include "../../gfx/icons.h"
#include "../pokemon/mail_2.h"
#include "../pokemon/party_menu.h"
#include "../../data/pokemon/menu_icons.h"
#include "../../data/icon_pointers.h"
#include "../../home/tilemap.h"
#include "sprites.h"

// void HeldItemIcons(void){
// INCBIN "gfx/icons/mail.2bpp"
// INCBIN "gfx/icons/item.2bpp"

    // return GetIcon_de();
// }

static const char *HeldItemIcons[] = {
    "gfx/icons/mail.png",
    "gfx/icons/item.png"
};

void LoadOverworldMonIcon(void){
    LD_A_E;
    CALL(aReadMonMenuIcon);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    LD_DE(mIconPointers);
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    LD_B(BANK(aIcons));
    LD_C(8);
    RET;

}

struct IconData {
    const char* path;
    uint8_t c;
};

struct IconData LoadOverworldMonIcon_Conv(species_t e){
    // LD_A_E;
    // CALL(aReadMonMenuIcon);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // LD_DE(mIconPointers);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // LD_B(BANK(aIcons));
    // LD_C(8);
    // RET;
    return (struct IconData){.path=IconPointers[e], 8};
}

void LoadMenuMonIcon(void){
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aLoadMenuMonIcon_LoadIcon);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;


LoadIcon:
    LD_D(0);
    LD_HL(mLoadMenuMonIcon_Jumptable);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


Jumptable:
//  entries correspond to MONICON_* constants
    //dw ['PartyMenu_InitAnimatedMonIcon'];  // MONICON_PARTYMENU
    //dw ['NamingScreen_InitAnimatedMonIcon'];  // MONICON_NAMINGSCREEN
    //dw ['MoveList_InitAnimatedMonIcon'];  // MONICON_MOVES
    //dw ['Trade_LoadMonIconGFX'];  // MONICON_TRADE
    //dw ['Mobile_InitAnimatedMonIcon'];  // MONICON_MOBILE1
    //dw ['Mobile_InitPartyMenuBGPal71'];  // MONICON_MOBILE2
    //dw ['Unused_GetPartyMenuMonIcon'];  // MONICON_UNUSED

    return Unused_GetPartyMenuMonIcon();
}

void LoadMenuMonIcon_Conv(uint8_t e){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aLoadMenuMonIcon_LoadIcon);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;

    switch(e) {
        case MONICON_PARTYMENU: PartyMenu_InitAnimatedMonIcon_Conv(); return;
        case MONICON_NAMINGSCREEN: NamingScreen_InitAnimatedMonIcon_Conv(); return;
        case MONICON_MOVES: MoveList_InitAnimatedMonIcon_Conv(); return;
        case MONICON_TRADE: Trade_LoadMonIconGFX_Conv(); return;
        case MONICON_MOBILE1: Mobile_InitAnimatedMonIcon_Conv(); return;
        case MONICON_MOBILE2: Mobile_InitPartyMenuBGPal71_Conv(); return;
        case MONICON_UNUSED: return;
    }

// LoadIcon:
    // LD_D(0);
    // LD_HL(mLoadMenuMonIcon_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;


// Jumptable:
//  entries correspond to MONICON_* constants
    //dw ['PartyMenu_InitAnimatedMonIcon'];  // MONICON_PARTYMENU
    //dw ['NamingScreen_InitAnimatedMonIcon'];  // MONICON_NAMINGSCREEN
    //dw ['MoveList_InitAnimatedMonIcon'];  // MONICON_MOVES
    //dw ['Trade_LoadMonIconGFX'];  // MONICON_TRADE
    //dw ['Mobile_InitAnimatedMonIcon'];  // MONICON_MOBILE1
    //dw ['Mobile_InitPartyMenuBGPal71'];  // MONICON_MOBILE2
    //dw ['Unused_GetPartyMenuMonIcon'];  // MONICON_UNUSED
}

void Unused_GetPartyMenuMonIcon(void){
    CALL(aInitPartyMenuIcon);
    CALL(aUnused_GetPartyMenuMonIcon_GetPartyMonItemGFX);
    CALL(aSetPartyMonIconAnimSpeed);
    RET;


GetPartyMonItemGFX:
    PUSH_BC;
    LDH_A_addr(hObjectStructIndex);
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    POP_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto no_item;
    PUSH_HL;
    PUSH_BC;
    LD_D_A;
    CALLFAR(aItemIsMail);
    POP_BC;
    POP_HL;
    IF_C goto not_mail;
    LD_A(0x06);
    goto got_tile;

not_mail:
    LD_A(0x05);
// fallthrough


no_item:
    LD_A(0x04);

got_tile:
    LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void Mobile_InitAnimatedMonIcon(void){
    CALL(aPartyMenu_InitAnimatedMonIcon);
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_A(SPRITE_ANIM_SEQ_NULL);
    LD_hl_A;
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A(9 * 8);
    LD_hl_A;
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A(9 * 8);
    LD_hl_A;
    RET;

}

struct SpriteAnim* Mobile_InitAnimatedMonIcon_Conv(void){
    // CALL(aPartyMenu_InitAnimatedMonIcon);
    struct SpriteAnim* bc = PartyMenu_InitAnimatedMonIcon_Conv();
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_A(SPRITE_ANIM_SEQ_NULL);
    // LD_hl_A;
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A(9 * 8);
    // LD_hl_A;
    bc->xCoord = 9 * 8;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A(9 * 8);
    // LD_hl_A;
    bc->yCoord = 9 * 8;
    // RET;
    return bc;
}

void Mobile_InitPartyMenuBGPal71(void){
    CALL(aInitPartyMenuIcon);
    CALL(aSetPartyMonIconAnimSpeed);
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_A(SPRITE_ANIM_SEQ_NULL);
    LD_hl_A;
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A(3 * 8);
    LD_hl_A;
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A(12 * 8);
    LD_hl_A;
    LD_A_C;
    LD_addr_A(wc608);
    LD_A_B;
    LD_addr_A(wc608 + 1);
    RET;

}

void Mobile_InitPartyMenuBGPal71_Conv(void){
    // CALL(aInitPartyMenuIcon);
    struct SpriteAnim* bc = InitPartyMenuIcon_Conv();
    // CALL(aSetPartyMonIconAnimSpeed);
    SetPartyMonIconAnimSpeed_Conv(bc);
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_A(SPRITE_ANIM_SEQ_NULL);
    // LD_hl_A;
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A(3 * 8);
    // LD_hl_A;
    bc->xCoord = 3 * 8;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A(12 * 8);
    // LD_hl_A;
    bc->yCoord = 12 * 8;
    // LD_A_C;
    // LD_addr_A(wc608);
    // LD_A_B;
    // LD_addr_A(wc608 + 1);
    uint16_t addr_bc = RAMAddrToGB(bc);
    wram->wc608[0] = LOW(addr_bc);
    wram->wc608[1] = HIGH(addr_bc);
    // RET;
}

void PartyMenu_InitAnimatedMonIcon(void){
    CALL(aInitPartyMenuIcon);
    CALL(aPartyMenu_InitAnimatedMonIcon_SpawnItemIcon);
    CALL(aSetPartyMonIconAnimSpeed);
    RET;


SpawnItemIcon:
    PUSH_BC;
    LDH_A_addr(hObjectStructIndex);
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    POP_BC;
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    PUSH_HL;
    PUSH_BC;
    LD_D_A;
    CALLFAR(aItemIsMail);
    POP_BC;
    POP_HL;
    IF_C goto mail;
    LD_A(SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_ITEM);
    goto okay;


mail:
    LD_A(SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_MAIL);

okay:
    LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

static void PartyMenu_InitAnimatedMonIcon_SpawnItemIcon_Conv(struct SpriteAnim* bc) {
    // PUSH_BC;
    // LDH_A_addr(hObjectStructIndex);
    // LD_HL(wPartyMon1Item);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // POP_BC;
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(!wram->wPartyMon[hram->hObjectStructIndex].mon.item)
        return;
    // PUSH_HL;
    // PUSH_BC;
    // LD_D_A;
    // CALLFAR(aItemIsMail);
    // POP_BC;
    // POP_HL;
    // IF_C goto mail;
    if(ItemIsMail_Conv(wram->wPartyMon[hram->hObjectStructIndex].mon.item)) {
        bc->framesetID = SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_MAIL;
    }
    else {
        bc->framesetID = SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_ITEM;
    }
    // LD_A(SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_ITEM);
    // goto okay;
    // mail:
        // LD_A(SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_MAIL);

    // okay:
        // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // LD_hl_A;
        // RET;
}

struct SpriteAnim* PartyMenu_InitAnimatedMonIcon_Conv(void){
    // CALL(aInitPartyMenuIcon);
    struct SpriteAnim* bc = InitPartyMenuIcon_Conv();
    // CALL(aPartyMenu_InitAnimatedMonIcon_SpawnItemIcon);
    PartyMenu_InitAnimatedMonIcon_SpawnItemIcon_Conv(bc);
    // CALL(aSetPartyMonIconAnimSpeed);
    SetPartyMonIconAnimSpeed_Conv(bc);
    // RET;
    return bc;
}

void InitPartyMenuIcon(void){
    LD_A_addr(wCurIconTile);
    PUSH_AF;
    LDH_A_addr(hObjectStructIndex);
    LD_HL(wPartySpecies);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    CALL(aReadMonMenuIcon);
    LD_addr_A(wCurIcon);
    CALL(aGetMemIconGFX);
    LDH_A_addr(hObjectStructIndex);
//  y coord
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    ADD_A(0x1c);
    LD_D_A;
//  x coord
    LD_E(0x10);
//  type is partymon icon
    LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    CALL(av_InitSpriteAnimStruct);
    POP_AF;
    LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

struct SpriteAnim* InitPartyMenuIcon_Conv(void){
    // LD_A_addr(wCurIconTile);
    // PUSH_AF;
    uint8_t curTile = wram->wCurIconTile;
    // LDH_A_addr(hObjectStructIndex);
    // LD_HL(wPartySpecies);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    species_t a = wram->wPartySpecies[hram->hObjectStructIndex];
    // CALL(aReadMonMenuIcon);
    // LD_addr_A(wCurIcon);
    wram->wCurIcon = ReadMonMenuIcon_Conv(a);
    // CALL(aGetMemIconGFX);
    GetMemIconGFX_Conv();
    // LDH_A_addr(hObjectStructIndex);
//  y coord
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A(0x1c);
    // LD_D_A;
    uint8_t y = (hram->hObjectStructIndex << 4) + 0x1c;
//  x coord
    // LD_E(0x10);
    uint8_t x = 0x10;
//  type is partymon icon
    // LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    // CALL(av_InitSpriteAnimStruct);
    struct SpriteAnim* bc = v_InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_PARTY_MON, (y << 8) | x);
    // POP_AF;
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->tileID = curTile;
    // RET;
    return bc;
}

void SetPartyMonIconAnimSpeed(void){
    PUSH_BC;
    LDH_A_addr(hObjectStructIndex);
    LD_B_A;
    CALL(aSetPartyMonIconAnimSpeed_getspeed);
    LD_A_B;
    POP_BC;
    LD_HL(SPRITEANIMSTRUCT_DURATIONOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RLCA;
    RLCA;
    LD_HL(SPRITEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_A;
    RET;


getspeed:
    FARCALL(aPlacePartymonHPBar);
    CALL(aGetHPPal);
    LD_E_D;
    LD_D(0);
    LD_HL(mSetPartyMonIconAnimSpeed_speeds);
    ADD_HL_DE;
    LD_B_hl;
    RET;


speeds:
    //db ['0x00'];  // HP_GREEN
    //db ['0x40'];  // HP_YELLOW
    //db ['0x80'];  // HP_RED

    return NamingScreen_InitAnimatedMonIcon();
}

void SetPartyMonIconAnimSpeed_Conv(struct SpriteAnim* bc){
    static const uint8_t speeds[] = {
        0x00,  // HP_GREEN
        0x40,  // HP_YELLOW
        0x80,  // HP_RED
    };
    // PUSH_BC;
    // LDH_A_addr(hObjectStructIndex);
    // LD_B_A;
    // CALL(aSetPartyMonIconAnimSpeed_getspeed);
    uint8_t a;
    {
    // getspeed:
        // FARCALL(aPlacePartymonHPBar);
        uint8_t e = PlacePartymonHPBar_Conv(hram->hObjectStructIndex);
        // CALL(aGetHPPal);
        // LD_E_D;
        // LD_D(0);
        // LD_HL(mSetPartyMonIconAnimSpeed_speeds);
        // ADD_HL_DE;
        // LD_B_hl;
        a = speeds[GetHPPal_Conv(e)];
        // RET;
    }
    // LD_A_B;
    // POP_BC;
    // LD_HL(SPRITEANIMSTRUCT_DURATIONOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->durationOffset = a;
    // RLCA;
    a = (a << 1) | (a >> 7);
    // RLCA;
    a = (a << 1) | (a >> 7);
    // LD_HL(SPRITEANIMSTRUCT_VAR2);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->var2 = a;
    // RET;
}

void NamingScreen_InitAnimatedMonIcon(void){
    LD_A_addr(wTempIconSpecies);
    CALL(aReadMonMenuIcon);
    LD_addr_A(wCurIcon);
    XOR_A_A;
    CALL(aGetIconGFX);
    depixel4(4, 4, 4, 0);
    LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    CALL(av_InitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_hl(SPRITE_ANIM_SEQ_NULL);
    RET;

}

void NamingScreen_InitAnimatedMonIcon_Conv(void){
    // LD_A_addr(wTempIconSpecies);
    // CALL(aReadMonMenuIcon);
    // LD_addr_A(wCurIcon);
    wram->wCurIcon = ReadMonMenuIcon_Conv(wram->wTempIconSpecies);
    // XOR_A_A;
    // CALL(aGetIconGFX);
    GetIconGFX_Conv(0);
    // depixel4(4, 4, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    // CALL(av_InitSpriteAnimStruct);
    struct SpriteAnim* bc = v_InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_PARTY_MON, pixel4(4, 4, 4, 0));
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_NULL);
    // RET;
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
}

void MoveList_InitAnimatedMonIcon(void){
    LD_A_addr(wTempIconSpecies);
    CALL(aReadMonMenuIcon);
    LD_addr_A(wCurIcon);
    XOR_A_A;
    CALL(aGetIconGFX);
    LD_D(3 * 8 + 2);  // depixel 3, 4, 2, 4
    LD_E(4 * 8 + 4);
    LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    CALL(av_InitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_hl(SPRITE_ANIM_SEQ_NULL);
    RET;

}

void MoveList_InitAnimatedMonIcon_Conv(void){
    // LD_A_addr(wTempIconSpecies);
    // CALL(aReadMonMenuIcon);
    // LD_addr_A(wCurIcon);
    wram->wCurIcon = ReadMonMenuIcon_Conv(wram->wTempIconSpecies);
    // XOR_A_A;
    // CALL(aGetIconGFX);
    GetIconGFX_Conv(0);
    // LD_D(3 * 8 + 2);  // depixel 3, 4, 2, 4
    // LD_E(4 * 8 + 4);
    // LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    // CALL(av_InitSpriteAnimStruct);
    struct SpriteAnim* bc = v_InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_PARTY_MON, pixel4(3, 4, 2, 4));
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_NULL);
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
    // RET;
}

void Trade_LoadMonIconGFX(void){
    LD_A_addr(wTempIconSpecies);
    CALL(aReadMonMenuIcon);
    LD_addr_A(wCurIcon);
    LD_A(0x62);
    LD_addr_A(wCurIconTile);
    CALL(aGetMemIconGFX);
    RET;

}

void Trade_LoadMonIconGFX_Conv(void){
    // LD_A_addr(wTempIconSpecies);
    // CALL(aReadMonMenuIcon);
    // LD_addr_A(wCurIcon);
    wram->wCurIcon = ReadMonMenuIcon_Conv(wram->wTempIconSpecies);
    // LD_A(0x62);
    // LD_addr_A(wCurIconTile);
    wram->wCurIconTile = 0x62;
    // CALL(aGetMemIconGFX);
    // RET;
    GetMemIconGFX_Conv();
}

void GetSpeciesIcon(void){
//  Load species icon into VRAM at tile a
    PUSH_DE;
    LD_A_addr(wTempIconSpecies);
    CALL(aReadMonMenuIcon);
    LD_addr_A(wCurIcon);
    POP_DE;
    LD_A_E;
    CALL(aGetIconGFX);
    RET;

}

//  Load species icon into VRAM at tile a
void GetSpeciesIcon_Conv(uint16_t de){
    // PUSH_DE;
    // LD_A_addr(wTempIconSpecies);
    // CALL(aReadMonMenuIcon);
    // LD_addr_A(wCurIcon);
    wram->wCurIcon = ReadMonMenuIcon_Conv(wram->wTempIconSpecies);
    // POP_DE;
    // LD_A_E;
    // CALL(aGetIconGFX);
    // RET;
    GetIconGFX_Conv(LOW(de));
}

void FlyFunction_GetMonIcon(void){
    PUSH_DE;
    LD_A_addr(wTempIconSpecies);
    CALL(aReadMonMenuIcon);
    LD_addr_A(wCurIcon);
    POP_DE;
    LD_A_E;
    CALL(aGetIcon_a);
    RET;

}

uint8_t* FlyFunction_GetMonIcon_Conv(uint16_t de){
    // PUSH_DE;
    // LD_A_addr(wTempIconSpecies);
    // CALL(aReadMonMenuIcon);
    // LD_addr_A(wCurIcon);
    wram->wCurIcon = ReadMonMenuIcon_Conv(wram->wTempIconSpecies);
    // POP_DE;
    // LD_A_E;
    // CALL(aGetIcon_a);
    return GetIcon_a_Conv(LOW(de));
    // RET;
}

void GetMonIconDE(void){
//  //  unreferenced
    PUSH_DE;
    LD_A_addr(wTempIconSpecies);
    CALL(aReadMonMenuIcon);
    LD_addr_A(wCurIcon);
    POP_DE;
    CALL(aGetIcon_de);
    RET;

}

void GetMemIconGFX(void){
    LD_A_addr(wCurIconTile);
    return GetIconGFX();
}

void GetMemIconGFX_Conv(void){
    // LD_A_addr(wCurIconTile);
    // return GetIconGFX();
    return GetIconGFX_Conv(wram->wCurIconTile);
}

void GetIconGFX(void){
    CALL(aGetIcon_a);
    LD_DE(8 * LEN_2BPP_TILE);
    ADD_HL_DE;
    LD_DE(mHeldItemIcons);
    LD_BC((BANK(aHeldItemIcons) << 8) | 2);
    CALL(aGetGFXUnlessMobile);
    LD_A_addr(wCurIconTile);
    ADD_A(10);
    LD_addr_A(wCurIconTile);
    RET;

}

void GetIconGFX_Conv(uint8_t a){
    // CALL(aGetIcon_a);
    // LD_DE(8 * LEN_2BPP_TILE);
    // ADD_HL_DE;
    uint8_t* hl = GetIcon_a_Conv(a) + 8 * LEN_2BPP_TILE;
    // LD_DE(mHeldItemIcons);
    // LD_BC((BANK(aHeldItemIcons) << 8) | 2);
    // CALL(aGetGFXUnlessMobile);
    GetGFXUnlessMobile_Conv(hl, HeldItemIcons[0], 2);
    // LD_A_addr(wCurIconTile);
    // ADD_A(10);
    // LD_addr_A(wCurIconTile);
    wram->wCurIconTile += 10;
    // RET;
}

void GetIcon_de(void){
//  Load icon graphics into VRAM starting from tile de.
    LD_L_E;
    LD_H_D;
    JR(mGetIcon);

}

//  Load icon graphics into VRAM starting from tile de.
uint8_t* GetIcon_de_Conv(uint16_t de){
    // LD_L_A;
    // LD_H(0);

    return GetIcon_Conv(de);
}

void GetIcon_a(void){
//  Load icon graphics into VRAM starting from tile a.
    LD_L_A;
    LD_H(0);

    return GetIcon();
}

//  Load icon graphics into VRAM starting from tile a.
uint8_t* GetIcon_a_Conv(uint8_t a){
    // LD_L_A;
    // LD_H(0);

    return GetIcon_Conv((uint16_t)a);
}

void GetIcon(void){
//  Load icon graphics into VRAM starting from tile hl.

//  One tile is 16 bytes long.
    for(int rept = 0; rept < 4; rept++){
    ADD_HL_HL;
    }

    LD_DE(vTiles0);
    ADD_HL_DE;
    PUSH_HL;

//  The icons are contiguous, in order and of the same
//  size, so the pointer table is somewhat redundant.
    LD_A_addr(wCurIcon);
    PUSH_HL;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    LD_DE(mIconPointers);
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    POP_HL;

    LD_BC((BANK(aIcons) << 8) | 8);
    CALL(aGetGFXUnlessMobile);

    POP_HL;
    RET;

}

//  Load icon graphics into VRAM starting from tile hl.
uint8_t* GetIcon_Conv(uint16_t hl){
//  One tile is 16 bytes long.
    // for(int rept = 0; rept < 4; rept++){
    // ADD_HL_HL;
    // }

    // LD_DE(vTiles0);
    // ADD_HL_DE;
    // PUSH_HL;
    uint8_t* hl_ = vram->vTiles0 + (hl << 4);

//  The icons are contiguous, in order and of the same
//  size, so the pointer table is somewhat redundant.
    // LD_A_addr(wCurIcon);
    // PUSH_HL;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // LD_DE(mIconPointers);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // POP_HL;
    const char* de = IconPointers[wram->wCurIcon];

    // LD_BC((BANK(aIcons) << 8) | 8);
    // CALL(aGetGFXUnlessMobile);
    GetGFXUnlessMobile_Conv(hl_, de, 8);

    // POP_HL;
    // RET;
    return hl_;
}

void GetGFXUnlessMobile(void){
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    JP_NZ (mRequest2bpp);
    JP(mGet2bppViaHDMA);

}

void GetGFXUnlessMobile_Conv(uint8_t* hl, const char* de, uint8_t c){
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // JP_NZ (mRequest2bpp);
    if(wram->wLinkMode != LINK_MOBILE) {
        LoadPNG2bppAssetSectionToVRAM(hl, de, 0, c);
    }
    // JP(mGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(hl, de, 0, c);
}

void FreezeMonIcons(void){
    LD_HL(wSpriteAnimationStructs);
    LD_E(PARTY_LENGTH);
    LD_A_addr(wMenuCursorY);
    LD_D_A;

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    CP_A_D;
    IF_Z goto loadwithtwo;
    LD_A(SPRITE_ANIM_SEQ_NULL);
    goto ok;


loadwithtwo:
    LD_A(SPRITE_ANIM_SEQ_PARTY_MON_SWITCH);


ok:
    PUSH_HL;
    LD_C_L;
    LD_B_H;
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_hl_A;
    POP_HL;


next:
    LD_BC(0x10);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    RET;

}

void FreezeMonIcons_Conv(void){
    // LD_HL(wSpriteAnimationStructs);
    struct SpriteAnim* hl = wram->wSpriteAnim;
    // LD_E(PARTY_LENGTH);
    uint8_t e = PARTY_LENGTH;
    // LD_A_addr(wMenuCursorY);
    uint8_t d = wram->wMenuCursorY;
    // LD_D_A;
    uint8_t a;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(hl->index == 0)
            continue;
        // CP_A_D;
        // IF_Z goto loadwithtwo;
        if(hl->index != d)
            a = SPRITE_ANIM_SEQ_NULL;
            // LD_A(SPRITE_ANIM_SEQ_NULL);
            // goto ok;
        else
        // loadwithtwo:
            // LD_A(SPRITE_ANIM_SEQ_PARTY_MON_SWITCH);
            a = SPRITE_ANIM_SEQ_PARTY_MON_SWITCH;

    // ok:
        // PUSH_HL;
        // LD_C_L;
        // LD_B_H;
        // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
        // ADD_HL_BC;
        // LD_hl_A;
        hl->animSeqID = a;
        // POP_HL;


    // next:
        // LD_BC(0x10);
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    } while(hl++, --e != 0);
    // RET;
}

void UnfreezeMonIcons(void){
    LD_HL(wSpriteAnimationStructs);
    LD_E(PARTY_LENGTH);

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    PUSH_HL;
    LD_C_L;
    LD_B_H;
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_hl(SPRITE_ANIM_SEQ_PARTY_MON);
    POP_HL;

next:
    LD_BC(0x10);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    RET;

}

void UnfreezeMonIcons_Conv(void){
    // LD_HL(wSpriteAnimationStructs);
    struct SpriteAnim* hl = wram->wSpriteAnim;
    // LD_E(PARTY_LENGTH);
    uint8_t e = PARTY_LENGTH;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(hl->index == 0)
            continue;
        // PUSH_HL;
        // LD_C_L;
        // LD_B_H;
        // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
        // ADD_HL_BC;
        // LD_hl(SPRITE_ANIM_SEQ_PARTY_MON);
        hl->animSeqID = SPRITE_ANIM_SEQ_PARTY_MON;
        // POP_HL;

    // next:
        // LD_BC(0x10);
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    } while(hl++, --e != 0);
    // RET;
}

void HoldSwitchmonIcon(void){
    LD_HL(wSpriteAnimationStructs);
    LD_E(PARTY_LENGTH);
    LD_A_addr(wSwitchMon);
    LD_D_A;

loop:
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    CP_A_D;
    IF_Z goto is_switchmon;
    LD_A(SPRITE_ANIM_SEQ_PARTY_MON_SELECTED);
    goto join_back;


is_switchmon:
    LD_A(SPRITE_ANIM_SEQ_PARTY_MON_SWITCH);

join_back:
    PUSH_HL;
    LD_C_L;
    LD_B_H;
    LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    ADD_HL_BC;
    LD_hl_A;
    POP_HL;

next:
    LD_BC(0x10);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto loop;
    RET;

}

void HoldSwitchmonIcon_Conv(void){
    // LD_HL(wSpriteAnimationStructs);
    struct SpriteAnim* hl = wram->wSpriteAnim;
    // LD_E(PARTY_LENGTH);
    uint8_t e = PARTY_LENGTH;
    // LD_A_addr(wSwitchMon);
    // LD_D_A;
    uint8_t d = wram->wSwitchMon;

    uint8_t a;
    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(hl->index == 0)
            continue;
        // CP_A_D;
        // IF_Z goto is_switchmon;
        if(hl->index != d)
            // LD_A(SPRITE_ANIM_SEQ_PARTY_MON_SELECTED);
            // goto join_back;
            a = SPRITE_ANIM_SEQ_PARTY_MON_SELECTED;

        else
        // is_switchmon:
            // LD_A(SPRITE_ANIM_SEQ_PARTY_MON_SWITCH);
            a = SPRITE_ANIM_SEQ_PARTY_MON_SWITCH;

    // join_back:
        // PUSH_HL;
        // LD_C_L;
        // LD_B_H;
        // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
        // ADD_HL_BC;
        // LD_hl_A;
        hl->animSeqID = a;
        // POP_HL;

    // next:
        // LD_BC(0x10);
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    } while(hl++, --e != 0);
    // RET;
}

void ReadMonMenuIcon(void){
    CP_A(EGG);
    IF_Z goto egg;
    DEC_A;
    LD_HL(mMonMenuIcons);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    RET;

egg:
    LD_A(ICON_EGG);
    RET;

// INCLUDE "data/pokemon/menu_icons.asm"

// INCLUDE "data/icon_pointers.asm"

// INCLUDE "gfx/icons.asm"

}

uint8_t ReadMonMenuIcon_Conv(species_t a){
    // CP_A(EGG);
    // IF_Z goto egg;
    if(a == EGG) {
    // egg:
        // LD_A(ICON_EGG);
        // RET;
        return ICON_EGG;
    }
    // DEC_A;
    // LD_HL(mMonMenuIcons);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    return MonMenuIcons[a - 1];
    // RET;
}
