#include "../../constants.h"
#include "trainer_huds.h"
#include "../../home/copy.h"
#include "../../home/pokedex_flags.h"
#include "../../home/gfx.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"

static void StageBallTilesData(uint8_t count, const struct PartyMon* hl);
static void PlaceHUDBorderTiles(tile_t* hl, int16_t de);
static void LoadTrainerHudOAM(struct SpriteOAM* hl, uint8_t y, uint8_t x, int8_t dir);

void BattleStart_TrainerHuds(void){
    // LD_A(0xe4);
    // LDH_addr_A(rOBP0);
    gb_write(rOBP0, 0xe4);
    // CALL(aLoadBallIconGFX);
    LoadBallIconGFX();
    // CALL(aShowPlayerMonsRemaining);
    ShowPlayerMonsRemaining();
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // RET_Z ;
    if(wram->wBattleMode == WILD_BATTLE)
        return;
    // JP(mShowOTTrainerMonsRemaining);
    return ShowOTTrainerMonsRemaining();
}

void EnemySwitch_TrainerHud(void){
    // LD_A(0xe4);
    // LDH_addr_A(rOBP0);
    gb_write(rOBP0, 0xe4);
    // CALL(aLoadBallIconGFX);
    LoadBallIconGFX();
    // JP(mShowOTTrainerMonsRemaining);
    return ShowOTTrainerMonsRemaining();
}

void ShowPlayerMonsRemaining(void){
    // CALL(aDrawPlayerPartyIconHUDBorder);
    DrawPlayerPartyIconHUDBorder();
    // LD_HL(wPartyMon1HP);
    // LD_DE(wPartyCount);
    // CALL(aStageBallTilesData);
    StageBallTilesData(gPokemon.partyCount, gPokemon.partyMon);
// ldpixel wPlaceBallsX, 12, 12
    // LD_A(12 * 8);
    uint8_t a = 12 * 8;
    // LD_HL(wPlaceBallsX);
    // LD_hli_A;
    // LD_hl_A;
    // LD_A(8);
    // LD_addr_A(wPlaceBallsDirection);
    // LD_HL(wVirtualOAMSprite00);
    // JP(mLoadTrainerHudOAM);
    return LoadTrainerHudOAM(wram->wVirtualOAMSprite, a, a, 8);
}

void ShowOTTrainerMonsRemaining(void){
    // CALL(aDrawEnemyHUDBorder);
    DrawEnemyHUDBorder();
    // LD_HL(wOTPartyMon1HP);
    // LD_DE(wOTPartyCount);
    // CALL(aStageBallTilesData);
    StageBallTilesData(wram->wOTPartyCount, wram->wOTPartyMon);
// ldpixel wPlaceBallsX, 9, 4
    // LD_HL(wPlaceBallsX);
    // LD_A(9 * 8);
    // LD_hli_A;
    // LD_hl(4 * 8);
    // LD_A(-8);
    // LD_addr_A(wPlaceBallsDirection);
    // LD_HL(wVirtualOAMSprite00 + PARTY_LENGTH * SPRITEOAMSTRUCT_LENGTH);
    // JP(mLoadTrainerHudOAM);
    return LoadTrainerHudOAM(wram->wVirtualOAMSprite + PARTY_LENGTH, 4 * 8, 9 * 8, -8);
}

static const struct PartyMon* StageBallTilesData_GetHUDTile(tile_t* de, const struct PartyMon* hl) {
    uint8_t b;
    // LD_A_hli;
    // AND_A_A;
    // IF_NZ goto got_hp;
    if(hl->HP == 0) {
        // LD_A_hl;
        // AND_A_A;
        // LD_B(0x33);  // fainted
        b = 0x33;
        // IF_Z goto fainted;
    // fainted:
        // DEC_HL;
        // DEC_HL;
        // DEC_HL;
    }
    else {
    // got_hp:
        // DEC_HL;
        // DEC_HL;
        // DEC_HL;
        // LD_A_hl;
        // AND_A_A;
        // LD_B(0x32);  // statused
        b = 0x32;
        // IF_NZ goto load;
        if(hl->status == 0) {
            // DEC_B;  // normal
            b = 0x31;
        }
        // goto load;
    }

// load:
    // LD_A_B;
    // LD_de_A;
    *de = b;
    // LD_BC(PARTYMON_STRUCT_LENGTH + MON_HP - MON_STATUS);
    // ADD_HL_BC;
    hl++;
    // RET;
    return hl;
}

static void StageBallTilesData(uint8_t count, const struct PartyMon* hl){
    // LD_A_de;
    // PUSH_AF;
    // LD_DE(wBattleHUDTiles);
    tile_t* de = wram->wBattleHUDTiles;
    // LD_C(PARTY_LENGTH);
    uint8_t c = PARTY_LENGTH;
    // LD_A(0x34);  // empty slot
    tile_t a = 0x34;

    do {
    // loop1:
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        // DEC_C;
        // IF_NZ goto loop1;
    } while(--c != 0);
    // POP_AF;

    // LD_DE(wBattleHUDTiles);
    de = wram->wBattleHUDTiles;
    if(count > PARTY_LENGTH) count = PARTY_LENGTH;

    while(count-- != 0) {
    // loop2:
        // PUSH_AF;
        // CALL(aStageBallTilesData_GetHUDTile);
        hl = StageBallTilesData_GetHUDTile(de, hl);
        // INC_DE;
        de++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop2;
    }
    // RET;
}

void DrawPlayerHUDBorder(void){
    static const uint8_t tiles[] = {
        0x73,  // right side
        0x77,  // bottom right
        0x6f,  // bottom left
        0x76,  // bottom side
    };
    // LD_HL(mDrawPlayerHUDBorder_tiles);
    // LD_DE(wTrainerHUDTiles);
    // LD_BC(mDrawPlayerHUDBorder_tiles_end - mDrawPlayerHUDBorder_tiles);
    // CALL(aCopyBytes);
    CopyBytes(wram->wTrainerHUDTiles, tiles, sizeof(tiles));
    // hlcoord(18, 10, wTilemap);
    // LD_DE(-1);  // start on right
    // JR(mPlaceHUDBorderTiles);
    return PlaceHUDBorderTiles(coord(18, 10, wram->wTilemap), -1);
// tiles_end:
}

void DrawPlayerPartyIconHUDBorder(void){
    static const uint8_t tiles[] = {
        0x73,  // right side
        0x5c,  // bottom right
        0x6f,  // bottom left
        0x76,  // bottom side
    };
    // LD_HL(mDrawPlayerPartyIconHUDBorder_tiles);
    // LD_DE(wTrainerHUDTiles);
    // LD_BC(mDrawPlayerPartyIconHUDBorder_tiles_end - mDrawPlayerPartyIconHUDBorder_tiles);
    // CALL(aCopyBytes);
    CopyBytes(wram->wTrainerHUDTiles, tiles, sizeof(tiles));
    // hlcoord(18, 10, wTilemap);
    // LD_DE(-1);  // start on right
    // JR(mPlaceHUDBorderTiles);
    return PlaceHUDBorderTiles(coord(18, 10, wram->wTilemap), -1);

// tiles_end:
}

void DrawEnemyHUDBorder(void){
    static const uint8_t tiles[] = {
        0x6d,  // left side
        0x74,  // bottom left
        0x78,  // bottom right
        0x76,  // bottom side
    };
    // LD_HL(mDrawEnemyHUDBorder_tiles);
    // LD_DE(wTrainerHUDTiles);
    // LD_BC(mDrawEnemyHUDBorder_tiles_end - mDrawEnemyHUDBorder_tiles);
    // CALL(aCopyBytes);
    CopyBytes(wram->wTrainerHUDTiles, tiles, sizeof(tiles));
    // hlcoord(1, 2, wTilemap);
    // LD_DE(1);  // start on left
    // CALL(aPlaceHUDBorderTiles);
    PlaceHUDBorderTiles(coord(1, 2, wram->wTilemap), 1);
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // RET_NZ ;
    if(wram->wBattleMode != WILD_BATTLE)
        return;
    // LD_A_addr(wTempEnemyMonSpecies);
    // DEC_A;
    // CALL(aCheckCaughtMon);
    // RET_Z ;
    if(!CheckCaughtMon(wram->wTempEnemyMonSpecies))
        return;
    // hlcoord(1, 1, wTilemap);
    // LD_hl(0x5d);
    *coord(1, 1, wram->wTilemap) = 0x5d;
    // RET;

// tiles_end:

}

static void PlaceHUDBorderTiles(tile_t* hl, int16_t de){
    // LD_A_addr(wTrainerHUDTiles + 0);
    // LD_hl_A;
    *hl = wram->wTrainerHUDTiles[0];
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    hl += SCREEN_WIDTH;
    // LD_A_addr(wTrainerHUDTiles + 1);
    // LD_hl_A;
    *hl = wram->wTrainerHUDTiles[1];
    // LD_B(8);
    uint8_t b = 8;

    do {
    // loop:
        // ADD_HL_DE;
        hl += de;
        // LD_A_addr(wTrainerHUDTiles + 3);
        // LD_hl_A;
        *hl = wram->wTrainerHUDTiles[3];
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // ADD_HL_DE;
    hl += de;
    // LD_A_addr(wTrainerHUDTiles + 2);
    // LD_hl_A;
    *hl = wram->wTrainerHUDTiles[2];
    // RET;
}

void LinkBattle_TrainerHuds(void){
    // CALL(aLoadBallIconGFX);
    LoadBallIconGFX();
    // LD_HL(wPartyMon1HP);
    // LD_DE(wPartyCount);
    // CALL(aStageBallTilesData);
    StageBallTilesData(gPokemon.partyCount, gPokemon.partyMon);
    // LD_HL(wPlaceBallsX);
    // LD_A(10 * 8);
    // LD_hli_A;
    // LD_hl(8 * 8);
    // LD_A(8);
    // LD_addr_A(wPlaceBallsDirection);
    // LD_HL(wVirtualOAMSprite00);
    // CALL(aLoadTrainerHudOAM);
    LoadTrainerHudOAM(wram->wVirtualOAMSprite, 8 * 8, 10 * 8, 8);

    // LD_HL(wOTPartyMon1HP);
    // LD_DE(wOTPartyCount);
    // CALL(aStageBallTilesData);
    StageBallTilesData(wram->wOTPartyCount, wram->wOTPartyMon);
    // LD_HL(wPlaceBallsX);
    // LD_A(10 * 8);
    // LD_hli_A;
    // LD_hl(13 * 8);
    // LD_HL(wVirtualOAMSprite00 + PARTY_LENGTH * SPRITEOAMSTRUCT_LENGTH);
    // JP(mLoadTrainerHudOAM);
    LoadTrainerHudOAM(wram->wVirtualOAMSprite + PARTY_LENGTH, 13 * 8, 10 * 8, 8);
}

static void LoadTrainerHudOAM(struct SpriteOAM* hl, uint8_t y, uint8_t x, int8_t dir){
    // LD_DE(wBattleHUDTiles);
    // LD_C(PARTY_LENGTH);

    for(uint8_t i = 0; i < PARTY_LENGTH; ++i) {
    // loop:
        // LD_A_addr(wPlaceBallsY);
        // LD_hli_A;  // y
        hl[i].yCoord = y;
        // LD_A_addr(wPlaceBallsX);
        // LD_hli_A;  // x
        hl[i].xCoord = x;
        // LD_A_de;
        // LD_hli_A;  // tile id
        hl[i].tileID = wram->wBattleHUDTiles[i];
        // LD_A(PAL_BATTLE_OB_YELLOW);
        // LD_hli_A;  // attributes
        hl[i].attributes = PAL_BATTLE_OB_YELLOW;
        // LD_A_addr(wPlaceBallsX);
        // LD_B_A;
        // LD_A_addr(wPlaceBallsDirection);
        // ADD_A_B;
        // LD_addr_A(wPlaceBallsX);
        x += dir;
        // INC_DE;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;

}

void LoadBallIconGFX(void){
    static const char gfx[] = "gfx/battle/balls.png";
    // LD_DE(mLoadBallIconGFX_gfx);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x31);
    // LD_BC((BANK(aLoadBallIconGFX) << 8) | 4);
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x31, gfx, 0, 4);
    // RET;
}

void v_ShowLinkBattleParticipants(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // hlcoord(2, 3, wTilemap);
    // LD_B(9);
    // LD_C(14);
    // CALL(aTextbox);
    Textbox(coord(2, 3, wram->wTilemap), 9, 14);
    // hlcoord(4, 5, wTilemap);
    // LD_DE(wPlayerName);
    // CALL(aPlaceString);
    PlaceStringSimple(gPlayer.playerName, coord(4, 5, wram->wTilemap));
    // hlcoord(4, 10, wTilemap);
    // LD_DE(wOTPlayerName);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wOTPlayerName, coord(4, 10, wram->wTilemap));
    // hlcoord(9, 8, wTilemap);
    tile_t* hl = coord(9, 8, wram->wTilemap);
    // LD_A(0x69);
    // LD_hli_A;
    hl[0] = 0x69;
    // LD_hl(0x6a);
    hl[1] = 0x6a;
    // FARCALL(aLinkBattle_TrainerHuds);  // no need to farcall
    LinkBattle_TrainerHuds();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_DIPLOMA);
    // CALL(aSetPalettes);
    SetPalettes();
    // LD_A(0xe4);
    // LDH_addr_A(rOBP0);
    gb_write(rOBP0, 0xe4);
    // RET;
}
