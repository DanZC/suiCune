#include "../../constants.h"
#include "tileset_palettes.h"
#include "../../home/copy.h"

bool LoadSpecialMapPalette(void){
    // LD_A_addr(wMapTileset);
    switch(wram->wMapTileset) {
    // CP_A(TILESET_POKECOM_CENTER);
    // IF_Z goto pokecom_2f;
    case TILESET_POKECOM_CENTER:
    // pokecom_2f:
        // CALL(aLoadPokeComPalette);
        LoadPokeComPalette();
        // SCF;
        // RET;
        return true;
    // CP_A(TILESET_BATTLE_TOWER_INSIDE);
    // IF_Z goto battle_tower_inside;
    case TILESET_BATTLE_TOWER_INSIDE:
    // battle_tower_inside:
        // CALL(aLoadBattleTowerInsidePalette);
        LoadBattleTowerInsidePalette();
        // SCF;
        // RET;
        return true;
    // CP_A(TILESET_ICE_PATH);
    // IF_Z goto ice_path;
    case TILESET_ICE_PATH:
    // ice_path:
        // LD_A_addr(wEnvironment);
        // AND_A(0x7);
        // CP_A(INDOOR);  // Hall of Fame
        // IF_Z goto do_nothing;
        if((wram->wEnvironment & 0x7) == INDOOR)
            return false;
        // CALL(aLoadIcePathPalette);
        LoadIcePathPalette();
        // SCF;
        // RET;
        return true;
    // CP_A(TILESET_HOUSE);
    // IF_Z goto house;
    case TILESET_HOUSE:
    // house:
        // CALL(aLoadHousePalette);
        LoadHousePalette();
        // SCF;
        // RET;
        return true;
    // CP_A(TILESET_RADIO_TOWER);
    // IF_Z goto radio_tower;
    case TILESET_RADIO_TOWER:
    // radio_tower:
        // CALL(aLoadRadioTowerPalette);
        LoadRadioTowerPalette();
        // SCF;
        // RET;
        return true;
    // CP_A(TILESET_MANSION);
    // IF_Z goto mansion_mobile;
    case TILESET_MANSION:
    // mansion_mobile:
        // CALL(aLoadMansionPalette);
        LoadMansionPalette();
        // SCF;
        // RET;
        return true;
    // goto do_nothing;
    default:
    // do_nothing:
        // AND_A_A;
        // RET;
        return false;
    }
}

void LoadPokeComPalette(void){
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1);
    // LD_HL(mPokeComPalette);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1, PokeComPalette, 8 * PALETTE_SIZE);
    // RET;
}

const uint16_t PokeComPalette[] = {
// INCLUDE "gfx/tilesets/pokecom_center.pal"
// gray
	rgb(30, 28, 26),
	rgb(19, 19, 19),
	rgb(13, 13, 13),
	rgb(07, 07, 07),
// red
	rgb(30, 28, 26),
	rgb(31, 19, 24),
	rgb(30, 10, 06),
	rgb(07, 07, 07),
// green
	rgb(18, 24,  9),
	rgb(15, 20,  1),
	rgb( 9, 13,  0),
	rgb( 7,  7,  7),
// water (blue)
	rgb(30, 28, 26),
	rgb(17, 19, 31),
	rgb(14, 16, 31),
	rgb(07, 07, 07),
// yellow
	rgb(31, 26, 21),
	rgb(31, 20,  1),
	rgb(14, 16, 31),
	rgb( 7,  7,  7),
// brown
	rgb(21, 17,  7),
	rgb(17, 19, 31),
	rgb(16, 13,  3),
	rgb( 7,  7,  7),
// roof
	rgb( 5,  5, 16),
	rgb( 8, 19, 28),
	rgb( 0,  0,  0),
	rgb(31, 31, 31),
// text
	rgb(31, 31, 16),
	rgb(31, 31, 16),
	rgb(14,  9,  0),
	rgb( 0,  0,  0),
};

void LoadBattleTowerInsidePalette(void){
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1);
    // LD_HL(mBattleTowerInsidePalette);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1, BattleTowerInsidePalette, 8 * PALETTE_SIZE);
    // RET;

}

const uint16_t BattleTowerInsidePalette[] = {
// INCLUDE "gfx/tilesets/battle_tower_inside.pal"
// gray
    rgb(30, 28, 26),
    rgb(19, 19, 19),
    rgb(13, 13, 13),
    rgb(07, 07, 07),
// red
    rgb(30, 28, 26),
    rgb(31, 19, 24),
    rgb(30, 10, 06),
    rgb(07, 07, 07),
// green
    rgb(18, 24,  9),
    rgb(15, 20,  1),
    rgb( 9, 13,  0),
    rgb( 7,  7,  7),
// water (blue)
    rgb(30, 28, 26),
    rgb(15, 16, 31),
    rgb( 9,  9, 31),
    rgb(07, 07, 07),
// yellow
    rgb(30, 28, 26),
    rgb(31, 31, 07),
    rgb(31, 16, 01),
    rgb(07, 07, 07),
// brown
    rgb(26, 24, 17),
    rgb(21, 17, 07),
    rgb(16, 13, 03),
    rgb(07, 07, 07),
// roof
    rgb(05, 05, 16),
    rgb( 8, 19, 28),
    rgb(00, 00, 00),
    rgb(31, 31, 31),
// text
    rgb(31, 31, 16),
    rgb(31, 31, 16),
    rgb(14,  9, 00),
    rgb(00, 00, 00),
};

void LoadIcePathPalette(void){
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1);
    // LD_HL(mIcePathPalette);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1, IcePathPalette, 8 * PALETTE_SIZE);
    // RET;

}

const uint16_t IcePathPalette[] = {
// INCLUDE "gfx/tilesets/ice_path.pal"
// gray
	rgb(15, 14, 24),
	rgb(11, 11, 19),
	rgb(07, 07, 12),
	rgb(00, 00, 00),
// red
	rgb(15, 14, 24),
	rgb(14, 07, 17),
	rgb(13, 00,  8),
	rgb(00, 00, 00),
// green (ice)
	rgb(22, 29, 31),
	rgb(10, 27, 31),
	rgb(31, 31, 31),
	rgb( 5, 00,  9),
// water
	rgb(15, 14, 24),
	rgb(05, 05, 17),
	rgb(03, 03, 10),
	rgb(00, 00, 00),
// yellow
	rgb(30, 30, 11),
	rgb(16, 14, 18),
	rgb(16, 14, 10),
	rgb(00, 00, 00),
// brown
	rgb(15, 14, 24),
	rgb(12,  9, 15),
	rgb( 8, 04, 05),
	rgb(00, 00, 00),
// roof (snow)
	rgb(25, 31, 31),
	rgb( 9, 28, 31),
	rgb(16, 11, 31),
	rgb( 5,  0,  9),
// text
	rgb(31, 31, 16),
	rgb(31, 31, 16),
	rgb(14,  9,  0),
	rgb( 0,  0,  0),
};

void LoadHousePalette(void){
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1);
    // LD_HL(mHousePalette);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1, HousePalette, 8 * PALETTE_SIZE);
    // RET;

}

const uint16_t HousePalette[] = {
// INCLUDE "gfx/tilesets/house.pal"
// gray
    rgb(30, 28, 26),
    rgb(19, 19, 19),
    rgb(13, 13, 13),
    rgb(07, 07, 07),
// red
    rgb(30, 28, 26),
    rgb(31, 19, 24),
    rgb(30, 10, 06),
    rgb(07, 07, 07),
// green
    rgb(30, 28, 26),
    rgb(15, 20,  1),
    rgb( 9, 13,  0),
    rgb( 7,  7,  7),
// water (blue)
    rgb(30, 28, 26),
    rgb(15, 16, 31),
    rgb( 9,  9, 31),
    rgb( 7,  7,  7),
// yellow
    rgb(30, 28, 26),
    rgb(31, 31,  7),
    rgb(31, 16,  1),
    rgb( 7,  7,  7),
// brown
    rgb(26, 24, 17),
    rgb(21, 17,  7),
    rgb(16, 13,  3),
    rgb( 7,  7,  7),
// roof (glass)
    rgb(30, 28, 26),
    rgb(31, 19, 24),
    rgb(16, 13, 03),
    rgb( 7,  7,  7),
// text
    rgb(31, 31, 16),
    rgb(31, 31, 16),
    rgb(14,  9,  0),
    rgb( 0,  0,  0),
};

void LoadRadioTowerPalette(void){
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1);
    // LD_HL(mRadioTowerPalette);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1, RadioTowerPalette, 8 * PALETTE_SIZE);
    // RET;

}

const uint16_t RadioTowerPalette[] = {
// INCLUDE "gfx/tilesets/radio_tower.pal"
    rgb(27, 31, 27),
    rgb(21, 21, 21),
    rgb(13, 13, 13),
    rgb(07, 07, 07),

    rgb(27, 31, 27),
    rgb(31, 19, 24),
    rgb(30, 10, 06),
    rgb(07, 07, 07),

    rgb( 8, 12, 31),
    rgb(12, 25, 01),
    rgb(05, 14, 00),
    rgb(07, 07, 07),

    rgb(31, 31, 31),
    rgb( 8, 12, 31),
    rgb(01, 04, 31),
    rgb(07, 07, 07),

    rgb(27, 31, 27),
    rgb(12, 25, 01),
    rgb(05, 14, 00),
    rgb(07, 07, 07),

    rgb(27, 31, 27),
    rgb(24, 18, 07),
    rgb(20, 15, 03),
    rgb(07, 07, 07),

    rgb(27, 31, 27),
    rgb(15, 31, 31),
    rgb(05, 17, 31),
    rgb(07, 07, 07),

    rgb(31, 31, 16),
    rgb(31, 31, 16),
    rgb(14,  9,  0),
    rgb( 0,  0,  0),
};

const uint16_t MansionPalette1[] = {
// INCLUDE "gfx/tilesets/mansion_1.pal"
    rgb(30, 28, 26),
    rgb(19, 19, 19),
    rgb(13, 13, 13),
    rgb(07, 07, 07),

    rgb(30, 28, 26),
    rgb(31, 19, 24),
    rgb(30, 10, 06),
    rgb(07, 07, 07),

    rgb(18, 24,  9),
    rgb(15, 20,  1),
    rgb( 9, 13,  0),
    rgb( 7,  7,  7),

    rgb(30, 28, 26),
    rgb(15, 16, 31),
    rgb( 9,  9, 31),
    rgb( 7,  7,  7),

    rgb(30, 28, 26),
    rgb(31, 31, 07),
    rgb(31, 16, 01),
    rgb(07, 07, 07),

    rgb(26, 24, 17),
    rgb(21, 17, 07),
    rgb(16, 13, 03),
    rgb(07, 07, 07),

	rgb(30, 28, 26),
	rgb(17, 19, 31),
	rgb(14, 16, 31),
	rgb(07, 07, 07),

	rgb(31, 31, 16),
	rgb(31, 31, 16),
	rgb(14,  9,  0),
	rgb( 0,  0,  0),

	rgb( 5,  5, 16),
	rgb( 8, 19, 28),
	rgb( 0,  0,  0),
	rgb(31, 31, 31),
};

void LoadMansionPalette(void){
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1);
    // LD_HL(mMansionPalette1);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1, MansionPalette1, 8 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_YELLOW);
    // LD_HL(mMansionPalette2);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_YELLOW, MansionPalette2, 1 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_WATER);
    // LD_HL(mMansionPalette1 + PALETTE_SIZE * 6);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_WATER, MansionPalette1 + NUM_PAL_COLORS * 6, 1 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_ROOF);
    // LD_HL(mMansionPalette1 + PALETTE_SIZE * 8);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_ROOF, MansionPalette1 + NUM_PAL_COLORS * 8, 1 * PALETTE_SIZE);
    // RET;

}

const uint16_t MansionPalette2[] = {
// INCLUDE "gfx/tilesets/mansion_2.pal"
    rgb(25, 24, 23),
    rgb(20, 19, 19),
    rgb(14, 16, 31),
    rgb(07, 07, 07),
};
