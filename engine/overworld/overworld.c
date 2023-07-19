#include "../../constants.h"
#include "overworld.h"

void GetEmote2bpp(void){
    LD_A(0x1);
    LDH_addr_A(rVBK);
    CALL(aGet2bpp);
    XOR_A_A;
    LDH_addr_A(rVBK);
    RET;

}

void v_UpdatePlayerSprite(void){
    CALL(aGetPlayerSprite);
    LD_A_addr(wUsedSprites);
    LDH_addr_A(hUsedSpriteIndex);
    LD_A_addr(wUsedSprites + 1);
    LDH_addr_A(hUsedSpriteTile);
    CALL(aGetUsedSprite);
    RET;

}

void v_RefreshSprites(void){
//  //  mobile
    LD_HL(wSpriteFlags);
    LD_A_hl;
    PUSH_AF;
    RES_hl(7);
    SET_hl(6);
    CALL(aLoadUsedSpritesGFX);
    POP_AF;
    LD_addr_A(wSpriteFlags);
    RET;

}

void v_ClearSprites(void){
//  //  mobile
    LD_HL(wSpriteFlags);
    LD_A_hl;
    PUSH_AF;
    SET_hl(7);
    RES_hl(6);
    CALL(aLoadUsedSpritesGFX);
    POP_AF;
    LD_addr_A(wSpriteFlags);
    RET;

}

void RefreshSprites(void){
    CALL(aRefreshSprites_Refresh);
    CALL(aLoadUsedSpritesGFX);
    RET;


Refresh:
    XOR_A_A;
    LD_BC(wUsedSpritesEnd - wUsedSprites);
    LD_HL(wUsedSprites);
    CALL(aByteFill);
    CALL(aGetPlayerSprite);
    CALL(aAddMapSprites);
    CALL(aLoadAndSortSprites);
    RET;

}

void GetPlayerSprite(void){
//  Get Chris or Kris's sprite.
    LD_HL(mChrisStateSprites);
    LD_A_addr(wPlayerSpriteSetupFlags);
    BIT_A(PLAYERSPRITESETUP_FEMALE_TO_MALE_F);
    IF_NZ goto go;
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto go;
    LD_HL(mKrisStateSprites);


go:
    LD_A_addr(wPlayerState);
    LD_C_A;

loop:
    LD_A_hli;
    CP_A_C;
    IF_Z goto good;
    INC_HL;
    CP_A(-1);
    IF_NZ goto loop;

//  Any player state not in the array defaults to Chris's sprite.
    XOR_A_A;  // ld a, PLAYER_NORMAL
    LD_addr_A(wPlayerState);
    LD_A(SPRITE_CHRIS);
    goto finish;


good:
    LD_A_hl;


finish:
    LD_addr_A(wUsedSprites + 0);
    LD_addr_A(wPlayerSprite);
    LD_addr_A(wPlayerObjectSprite);
    RET;

// INCLUDE "data/sprites/player_sprites.asm"

    return AddMapSprites();
}

void AddMapSprites(void){
    CALL(aGetMapEnvironment);
    CALL(aCheckOutdoorMap);
    IF_Z goto outdoor;
    CALL(aAddIndoorSprites);
    RET;


outdoor:
    CALL(aAddOutdoorSprites);
    RET;

}

void AddIndoorSprites(void){
    LD_HL(wMap1ObjectSprite);
    LD_A(1);

loop:
    PUSH_AF;
    LD_A_hl;
    CALL(aAddSpriteGFX);
    LD_DE(MAPOBJECT_LENGTH);
    ADD_HL_DE;
    POP_AF;
    INC_A;
    CP_A(NUM_OBJECTS);
    IF_NZ goto loop;
    RET;

}

void AddOutdoorSprites(void){
    LD_A_addr(wMapGroup);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mOutdoorSprites);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_C(MAX_OUTDOOR_SPRITES);

loop:
    PUSH_BC;
    LD_A_hli;
    CALL(aAddSpriteGFX);
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void LoadUsedSpritesGFX(void){
    LD_A(MAPCALLBACK_SPRITES);
    CALL(aRunMapCallback);
    CALL(aGetUsedSprites);
    CALL(aLoadMiscTiles);
    RET;

}

void LoadMiscTiles(void){
    LD_A_addr(wSpriteFlags);
    BIT_A(6);
    RET_NZ ;

    LD_C(EMOTE_SHADOW);
    FARCALL(aLoadEmote);
    CALL(aGetMapEnvironment);
    CALL(aCheckOutdoorMap);
    LD_C(EMOTE_GRASS_RUSTLE);
    IF_Z goto outdoor;
    LD_C(EMOTE_BOULDER_DUST);

outdoor:
    FARCALL(aLoadEmote);
    RET;

}

void SafeGetSprite(void){
    PUSH_HL;
    CALL(aGetSprite);
    POP_HL;
    RET;

}

void GetSprite(void){
    CALL(aGetMonSprite);
    RET_C ;

    LD_HL(mOverworldSprites + SPRITEDATA_ADDR);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_A(NUM_SPRITEDATA_FIELDS);
    CALL(aAddNTimes);
// load the address into de
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
// load the length into c
    LD_A_hli;
    SWAP_A;
    LD_C_A;
// load the sprite bank into both b and h
    LD_B_hl;
    LD_A_hli;
// load the sprite type into l
    LD_L_hl;
    LD_H_A;
    RET;

}

void GetMonSprite(void){
//  Return carry if a monster sprite was loaded.

    CP_A(SPRITE_POKEMON);
    IF_C goto Normal;
    CP_A(SPRITE_DAY_CARE_MON_1);
    IF_Z goto BreedMon1;
    CP_A(SPRITE_DAY_CARE_MON_2);
    IF_Z goto BreedMon2;
    CP_A(SPRITE_VARS);
    IF_NC goto Variable;
    goto Icon;


Normal:
    AND_A_A;
    RET;


Icon:
    SUB_A(SPRITE_POKEMON);
    LD_E_A;
    LD_D(0);
    LD_HL(mSpriteMons);
    ADD_HL_DE;
    LD_A_hl;
    goto Mon;


BreedMon1:
    LD_A_addr(wBreedMon1Species);
    goto Mon;


BreedMon2:
    LD_A_addr(wBreedMon2Species);


Mon:
    LD_E_A;
    AND_A_A;
    IF_Z goto NoBreedmon;

    FARCALL(aLoadOverworldMonIcon);

    LD_L(WALKING_SPRITE);
    LD_H(0);
    SCF;
    RET;


Variable:
    SUB_A(SPRITE_VARS);
    LD_E_A;
    LD_D(0);
    LD_HL(wVariableSprites);
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    JP_NZ (mGetMonSprite);


NoBreedmon:
    LD_A(WALKING_SPRITE);
    LD_L(WALKING_SPRITE);
    LD_H(0);
    AND_A_A;
    RET;

}

void v_DoesSpriteHaveFacings(void){
//  Checks to see whether we can apply a facing to a sprite.
//  Returns carry unless the sprite is a Pokemon or a Still Sprite.
    CP_A(SPRITE_POKEMON);
    IF_NC goto only_down;

    PUSH_HL;
    PUSH_BC;
    LD_HL(mOverworldSprites + SPRITEDATA_TYPE);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_A(NUM_SPRITEDATA_FIELDS);
    CALL(aAddNTimes);
    LD_A_hl;
    POP_BC;
    POP_HL;
    CP_A(STILL_SPRITE);
    IF_NZ goto only_down;
    SCF;
    RET;


only_down:
    AND_A_A;
    RET;

}

//  Checks to see whether we can apply a facing to a sprite.
//  Returns true unless the sprite is a Pokemon or a Still Sprite.
bool v_DoesSpriteHaveFacings_Conv(uint8_t a){
    // CP_A(SPRITE_POKEMON);
    // IF_NC goto only_down;
    if(a >= SPRITE_POKEMON)
        return true;

    // PUSH_HL;
    // PUSH_BC;
    // LD_HL(mOverworldSprites + SPRITEDATA_TYPE);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_A(NUM_SPRITEDATA_FIELDS);
    // CALL(aAddNTimes);
    // LD_A_hl;
    // POP_BC;
    // POP_HL;
    bank_push(BANK(aOverworldSprites));
    a = gb_read((mOverworldSprites + SPRITEDATA_TYPE) + (a - 1) * NUM_SPRITEDATA_FIELDS);
    bank_pop;
    // CP_A(STILL_SPRITE);
    // IF_NZ goto only_down;
    if(a != STILL_SPRITE) 
        return true;
    // SCF;
    // RET;
    return false;

// only_down:
    // AND_A_A;
    // RET;
}

void v_GetSpritePalette(void){
    LD_A_C;
    CALL(aGetMonSprite);
    IF_C goto is_pokemon;

    LD_HL(mOverworldSprites + SPRITEDATA_PALETTE);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_A(NUM_SPRITEDATA_FIELDS);
    CALL(aAddNTimes);
    LD_C_hl;
    RET;


is_pokemon:
    XOR_A_A;
    LD_C_A;
    RET;

}

void LoadAndSortSprites(void){
    CALL(aLoadSpriteGFX);
    CALL(aSortUsedSprites);
    CALL(aArrangeUsedSprites);
    RET;

}

void AddSpriteGFX(void){
//  Add any new sprite ids to a list of graphics to be loaded.
//  Return carry if the list is full.

    PUSH_HL;
    PUSH_BC;
    LD_B_A;
    LD_HL(wUsedSprites + 2);
    LD_C(SPRITE_GFX_LIST_CAPACITY - 1);

loop:
    LD_A_hl;
    CP_A_B;
    IF_Z goto exists;
    AND_A_A;
    IF_Z goto new;
    INC_HL;
    INC_HL;
    DEC_C;
    IF_NZ goto loop;

    POP_BC;
    POP_HL;
    SCF;
    RET;


exists:
    POP_BC;
    POP_HL;
    AND_A_A;
    RET;


new:
    LD_hl_B;
    POP_BC;
    POP_HL;
    AND_A_A;
    RET;

}

void LoadSpriteGFX(void){
//  Bug: b is not preserved, so it's useless as a next count.
//  Uncomment the lines below to fix.

    LD_HL(wUsedSprites);
    LD_B(SPRITE_GFX_LIST_CAPACITY);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto done;
    PUSH_HL;
    CALL(aLoadSpriteGFX_LoadSprite);
    POP_HL;
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;


done:
    RET;


LoadSprite:
// push bc
    CALL(aGetSprite);
// pop bc
    LD_A_L;
    RET;

}

void SortUsedSprites(void){
//  Bubble-sort sprites by type.

//  Run backwards through wUsedSprites to find the last one.

    LD_C(SPRITE_GFX_LIST_CAPACITY);
    LD_DE(wUsedSprites + (SPRITE_GFX_LIST_CAPACITY - 1) * 2);

FindLastSprite:
    LD_A_de;
    AND_A_A;
    IF_NZ goto FoundLastSprite;
    DEC_DE;
    DEC_DE;
    DEC_C;
    IF_NZ goto FindLastSprite;

FoundLastSprite:
    DEC_C;
    IF_Z goto quit;

//  If the length of the current sprite is
//  higher than a later one, swap them.

    INC_DE;
    LD_HL(wUsedSprites + 1);


CheckSprite:
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;


CheckFollowing:
    LD_A_de;
    CP_A_hl;
    IF_NC goto loop;

//  Swap the two sprites.

    LD_B_A;
    LD_A_hl;
    LD_hl_B;
    LD_de_A;
    DEC_DE;
    DEC_HL;
    LD_A_de;
    LD_B_A;
    LD_A_hl;
    LD_hl_B;
    LD_de_A;
    INC_DE;
    INC_HL;

//  Keep doing this until everything's in order.


loop:
    DEC_DE;
    DEC_DE;
    DEC_C;
    IF_NZ goto CheckFollowing;

    POP_HL;
    INC_HL;
    INC_HL;
    POP_DE;
    POP_BC;
    DEC_C;
    IF_NZ goto CheckSprite;


quit:
    RET;

}

void ArrangeUsedSprites(void){
//  Get the length of each sprite and space them out in VRAM.
//  Crystal introduces a second table in VRAM bank 0.

    LD_HL(wUsedSprites);
    LD_C(SPRITE_GFX_LIST_CAPACITY);
    LD_B(0);

FirstTableLength:
//  Keep going until the end of the list.
    LD_A_hli;
    AND_A_A;
    IF_Z goto quit;

    LD_A_hl;
    CALL(aGetSpriteLength);

//  Spill over into the second table after $80 tiles.
    ADD_A_B;
    CP_A(0x80);
    IF_Z goto loop;
    IF_NC goto SecondTable;


loop:
    LD_hl_B;
    INC_HL;
    LD_B_A;

//  Assumes the next table will be reached before c hits 0.
    DEC_C;
    IF_NZ goto FirstTableLength;


SecondTable:
//  The second tile table starts at tile $80.
    LD_B(0x80);
    DEC_HL;

SecondTableLength:
//  Keep going until the end of the list.
    LD_A_hli;
    AND_A_A;
    IF_Z goto quit;

    LD_A_hl;
    CALL(aGetSpriteLength);

//  There are only two tables, so don't go any further than that.
    ADD_A_B;
    IF_C goto quit;

    LD_hl_B;
    LD_B_A;
    INC_HL;

    DEC_C;
    IF_NZ goto SecondTableLength;


quit:
    RET;

}

void GetSpriteLength(void){
//  Return the length of sprite type a in tiles.

    CP_A(WALKING_SPRITE);
    IF_Z goto AnyDirection;
    CP_A(STANDING_SPRITE);
    IF_Z goto AnyDirection;
    CP_A(STILL_SPRITE);
    IF_Z goto OneDirection;

    LD_A(12);
    RET;


AnyDirection:
    LD_A(12);
    RET;


OneDirection:
    LD_A(4);
    RET;

}

void GetUsedSprites(void){
    LD_HL(wUsedSprites);
    LD_C(SPRITE_GFX_LIST_CAPACITY);


loop:
    LD_A_addr(wSpriteFlags);
    RES_A(5);
    LD_addr_A(wSpriteFlags);

    LD_A_hli;
    AND_A_A;
    IF_Z goto done;
    LDH_addr_A(hUsedSpriteIndex);

    LD_A_hli;
    LDH_addr_A(hUsedSpriteTile);

    BIT_A(7);
    IF_Z goto dont_set;

    LD_A_addr(wSpriteFlags);
    SET_A(5);  // load VBank0
    LD_addr_A(wSpriteFlags);


dont_set:
    PUSH_BC;
    PUSH_HL;
    CALL(aGetUsedSprite);
    POP_HL;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;


done:
    RET;

}

void GetUsedSprite(void){
    LDH_A_addr(hUsedSpriteIndex);
    CALL(aSafeGetSprite);
    LDH_A_addr(hUsedSpriteTile);
    CALL(aGetUsedSprite_GetTileAddr);
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A_addr(wSpriteFlags);
    BIT_A(7);
    IF_NZ goto skip;
    CALL(aGetUsedSprite_CopyToVram);


skip:
    POP_BC;
    LD_L_C;
    LD_H(0x0);
    for(int rept = 0; rept < 4; rept++){
    ADD_HL_HL;
    }
    POP_DE;
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    POP_HL;

    LD_A_addr(wSpriteFlags);
    BIT_A(5);
    IF_NZ goto done;
    BIT_A(6);
    IF_NZ goto done;

    LDH_A_addr(hUsedSpriteIndex);
    CALL(av_DoesSpriteHaveFacings);
    IF_C goto done;

    LD_A_H;
    ADD_A(HIGH(vTiles1 - vTiles0));
    LD_H_A;
    CALL(aGetUsedSprite_CopyToVram);


done:
    RET;


GetTileAddr:
//  Return the address of tile (a) in (hl).
    AND_A(0x7f);
    LD_L_A;
    LD_H(0);
    for(int rept = 0; rept < 4; rept++){
    ADD_HL_HL;
    }
    LD_A_L;
    ADD_A(LOW(vTiles0));
    LD_L_A;
    LD_A_H;
    ADC_A(HIGH(vTiles0));
    LD_H_A;
    RET;


CopyToVram:
    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A_addr(wSpriteFlags);
    BIT_A(5);
    LD_A(0x1);
    IF_Z goto bankswitch;
    LD_A(0x0);


bankswitch:
    LDH_addr_A(rVBK);
    CALL(aGet2bpp);
    POP_AF;
    LDH_addr_A(rVBK);
    RET;

}

void LoadEmote(void){
//  Get the address of the pointer to emote c.
    LD_A_C;
    LD_BC(EMOTE_LENGTH);
    LD_HL(mEmotes);
    CALL(aAddNTimes);
//  Load the emote address into de
    LD_E_hl;
    INC_HL;
    LD_D_hl;
//  load the length of the emote (in tiles) into c
    INC_HL;
    LD_C_hl;
    SWAP_C;
//  load the emote pointer bank into b
    INC_HL;
    LD_B_hl;
//  load the VRAM destination into hl
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
//  if the emote has a length of 0, do not proceed (error handling)
    LD_A_C;
    AND_A_A;
    RET_Z ;
    CALL(aGetEmote2bpp);
    RET;

// INCLUDE "data/sprites/emotes.asm"

// INCLUDE "data/sprites/sprite_mons.asm"

// INCLUDE "data/maps/outdoor_sprites.asm"

// INCLUDE "data/sprites/sprites.asm"

}
