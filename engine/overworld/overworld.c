#include "../../constants.h"
#include "overworld.h"
#include "../../home/copy.h"
#include "../../home/map.h"
#include "../gfx/mon_icons.h"
#include "../../data/sprites/player_sprites.h"
#include "../../data/sprites/emotes.h"
#include "../../data/sprites/sprite_mons.h"
#include "../../data/sprites/sprites.h"
#include "../../data/maps/outdoor_sprites.h"

static void GetPlayerSprite(void);
static void AddMapSprites(void);
static void AddIndoorSprites(void);
static void AddOutdoorSprites(void);
static void LoadMiscTiles(void);
static struct SpriteLoadData SafeGetSprite(uint8_t a);
static struct SpriteLoadData GetSprite(uint8_t a);
static struct SpriteLoadData GetMonSprite(uint8_t a);

static void LoadAndSortSprites(void);
static bool AddSpriteGFX(uint8_t a);
static void LoadSpriteGFX(void);
static void SortUsedSprites(void);
static void ArrangeUsedSprites(void);
static uint8_t GetSpriteLength(uint8_t a);
static void GetUsedSprites(void);

void GetEmote2bpp(void){
    LD_A(0x1);
    LDH_addr_A(rVBK);
    CALL(aGet2bpp);
    XOR_A_A;
    LDH_addr_A(rVBK);
    RET;

}

void v_UpdatePlayerSprite(void){
    // CALL(aGetPlayerSprite);
    GetPlayerSprite();
    // LD_A_addr(wUsedSprites);
    // LDH_addr_A(hUsedSpriteIndex);
    hram.hUsedSpriteIndex = wram->wUsedSprites[0];
    // LD_A_addr(wUsedSprites + 1);
    // LDH_addr_A(hUsedSpriteTile);
    hram.hUsedSpriteTile = wram->wUsedSprites[1];
    // CALL(aGetUsedSprite);
    GetUsedSprite();
    // RET;
}

void v_RefreshSprites(void){
//  //  mobile
    // LD_HL(wSpriteFlags);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t spriteFlags = wram->wSpriteFlags;
    // RES_hl(7);
    bit_reset(wram->wSpriteFlags, 7);
    // SET_hl(6);
    bit_set(wram->wSpriteFlags, 6);
    // CALL(aLoadUsedSpritesGFX);
    LoadUsedSpritesGFX();
    // POP_AF;
    // LD_addr_A(wSpriteFlags);
    wram->wSpriteFlags = spriteFlags;
    // RET;
}

void v_ClearSprites(void){
//  //  mobile
    // LD_HL(wSpriteFlags);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t spriteFlags = wram->wSpriteFlags;
    // SET_hl(7);
    bit_set(wram->wSpriteFlags, 7);
    // RES_hl(6);
    bit_reset(wram->wSpriteFlags, 6);
    // CALL(aLoadUsedSpritesGFX);
    LoadUsedSpritesGFX();
    // POP_AF;
    // LD_addr_A(wSpriteFlags);
    wram->wSpriteFlags = spriteFlags;
    // RET;

}

static void RefreshSprites_Refresh(void) {
// Refresh:
    // XOR_A_A;
    // LD_BC(wUsedSpritesEnd - wUsedSprites);
    // LD_HL(wUsedSprites);
    // CALL(aByteFill);
    ByteFill(wram->wUsedSprites, sizeof(wram->wUsedSprites), 0);
    // CALL(aGetPlayerSprite);
    GetPlayerSprite();
    // CALL(aAddMapSprites);
    AddMapSprites();
    // CALL(aLoadAndSortSprites);
    LoadAndSortSprites();
    // RET;
}

void RefreshSprites(void){
    // CALL(aRefreshSprites_Refresh);
    RefreshSprites_Refresh();
    // CALL(aLoadUsedSpritesGFX);
    LoadUsedSpritesGFX();
    // RET;
}

//  Get Chris or Kris's sprite.
static void GetPlayerSprite(void){
    const uint8_t (*hl)[2];
    // LD_HL(mChrisStateSprites);
    // LD_A_addr(wPlayerSpriteSetupFlags);
    // BIT_A(PLAYERSPRITESETUP_FEMALE_TO_MALE_F);
    // IF_NZ goto go;
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto go;
    if(bit_test(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_FEMALE_TO_MALE_F)
    || !bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F)) {
        hl = ChrisStateSprites;
    }
    else {
        hl = KrisStateSprites;
    }
    // LD_HL(mKrisStateSprites);


// go:
    // LD_A_addr(wPlayerState);
    // LD_C_A;
    uint8_t c = wram->wPlayerState;

    do {
    // loop:
        // LD_A_hli;
        // CP_A_C;
        // IF_Z goto good;
        if((*hl)[0] == c) {
            wram->wUsedSprites[0] = (*hl)[1];
            wram->wPlayerStruct.sprite = (*hl)[1];
            wram->wPlayerObject.sprite = (*hl)[1];
            return;
        }
        // INC_HL;
        hl++;
        // CP_A(-1);
        // IF_NZ goto loop;
    } while((*hl)[0] != 0xff);

//  Any player state not in the array defaults to Chris's sprite.
    // XOR_A_A;  // ld a, PLAYER_NORMAL
    // LD_addr_A(wPlayerState);
    // LD_A(SPRITE_CHRIS);
    wram->wPlayerState = PLAYER_NORMAL;
    wram->wUsedSprites[0] = SPRITE_CHRIS;
    wram->wPlayerStruct.sprite = SPRITE_CHRIS;
    wram->wPlayerObject.sprite = SPRITE_CHRIS;
    // goto finish;
    return;


// good:
    // LD_A_hl;


// finish:
    // LD_addr_A(wUsedSprites + 0);
    // LD_addr_A(wPlayerSprite);
    // LD_addr_A(wPlayerObjectSprite);
    // RET;

// INCLUDE "data/sprites/player_sprites.asm"
}

static void AddMapSprites(void){
    // CALL(aGetMapEnvironment);
    // CALL(aCheckOutdoorMap);
    // IF_Z goto outdoor;
    if(!CheckOutdoorMap(GetMapEnvironment())) {
        // CALL(aAddIndoorSprites);
        AddIndoorSprites();
        // RET;
        return;
    }
// outdoor:
    // CALL(aAddOutdoorSprites);
    AddOutdoorSprites();
    // RET;
}

static void AddIndoorSprites(void){
    // LD_HL(wMap1ObjectSprite);
    // LD_A(1);

    for(uint8_t a = 0; a < NUM_OBJECTS - 1; ++a) {
    // loop:
        // PUSH_AF;
        // LD_A_hl;
        // CALL(aAddSpriteGFX);
        AddSpriteGFX(wram->wMapObject[a].sprite);
        // LD_DE(MAPOBJECT_LENGTH);
        // ADD_HL_DE;
        // POP_AF;
        // INC_A;
        // CP_A(NUM_OBJECTS);
        // IF_NZ goto loop;
    }
    // RET;
}

static void AddOutdoorSprites(void){
    // LD_A_addr(wMapGroup);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mOutdoorSprites);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const uint8_t* hl = OutdoorSprites[gCurMapData.mapGroup - 1];
    // LD_C(MAX_OUTDOOR_SPRITES);

    for(uint8_t c = 0; c < MAX_OUTDOOR_SPRITES; c++) {
    // loop:
        // PUSH_BC;
        // LD_A_hli;
        // CALL(aAddSpriteGFX);
        AddSpriteGFX(hl[c]);
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

void LoadUsedSpritesGFX(void){
    // LD_A(MAPCALLBACK_SPRITES);
    // CALL(aRunMapCallback);
    RunMapCallback(MAPCALLBACK_SPRITES);
    // CALL(aGetUsedSprites);
    GetUsedSprites();
    // CALL(aLoadMiscTiles);
    LoadMiscTiles();
    // RET;
}

static void LoadMiscTiles(void){
    // LD_A_addr(wSpriteFlags);
    // BIT_A(6);
    // RET_NZ ;
    if(bit_test(wram->wSpriteFlags, 6))
        return;

    // LD_C(EMOTE_SHADOW);
    // FARCALL(aLoadEmote);
    LoadEmote(EMOTE_SHADOW);
    // CALL(aGetMapEnvironment);
    // CALL(aCheckOutdoorMap);
    // LD_C(EMOTE_GRASS_RUSTLE);
    // IF_Z goto outdoor;
    // LD_C(EMOTE_BOULDER_DUST);
    uint8_t c = CheckOutdoorMap(GetMapEnvironment())? EMOTE_GRASS_RUSTLE: EMOTE_BOULDER_DUST;

// outdoor:
    // FARCALL(aLoadEmote);
    // RET;
    LoadEmote(c);
}

static struct SpriteLoadData SafeGetSprite(uint8_t a){
    // PUSH_HL;
    // CALL(aGetSprite);
    // POP_HL;
    // RET;
    return GetSprite(a);
}

static struct SpriteLoadData GetSprite(uint8_t a){
    // CALL(aGetMonSprite);
    // RET_C ;
    struct SpriteLoadData res = GetMonSprite(a);
    if(res.flag)
        return res;

    if(res.type == 0) {
        const struct OverworldSprite* hl = &OverworldSprites[0];
        return (struct SpriteLoadData){.path=hl->path, .length=hl->length, .type=hl->type};
    }
    // LD_HL(mOverworldSprites + SPRITEDATA_ADDR);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_A(NUM_SPRITEDATA_FIELDS);
    // CALL(aAddNTimes);
    const struct OverworldSprite* hl = &OverworldSprites[res.type - 1];
// load the address into de
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
// load the length into c
    // LD_A_hli;
    // SWAP_A;
    // LD_C_A;
// load the sprite bank into both b and h
    // LD_B_hl;
    // LD_A_hli;
// load the sprite type into l
    // LD_L_hl;
    // LD_H_A;
    // RET;
    return (struct SpriteLoadData){.path=hl->path, .length=hl->length, .type=hl->type};
}

//  Return carry if a monster sprite was loaded.
static struct SpriteLoadData GetMonSprite(uint8_t a){
    // CP_A(SPRITE_POKEMON);
    // IF_C goto Normal;
    if(a < SPRITE_POKEMON) {
    // Normal:
        // AND_A_A;
        // RET;
        return (struct SpriteLoadData){.flag=false, .type=a};
    }
    // CP_A(SPRITE_DAY_CARE_MON_1);
    // IF_Z goto BreedMon1;
    uint8_t e;
    if(a == SPRITE_DAY_CARE_MON_1) {
    // BreedMon1:
        // LD_A_addr(wBreedMon1Species);
        // goto Mon;
        e = wram->wBreedMon1.species;
    }
    // CP_A(SPRITE_DAY_CARE_MON_2);
    // IF_Z goto BreedMon2;
    else if(a == SPRITE_DAY_CARE_MON_2) {
    // BreedMon2:
        // LD_A_addr(wBreedMon2Species);
        e = wram->wBreedMon2.species;
    }
    // CP_A(SPRITE_VARS);
    // IF_NC goto Variable;
    else if(a >= SPRITE_VARS) {
    // Variable:
        // SUB_A(SPRITE_VARS);
        // LD_E_A;
        e = a - SPRITE_VARS;
        // LD_D(0);
        // LD_HL(wVariableSprites);
        // ADD_HL_DE;
        // LD_A_hl;
        a = wram->wVariableSprites[e];
        // AND_A_A;
        // JP_NZ (mGetMonSprite);
        if(a != 0)
            return GetMonSprite(a);
        return (struct SpriteLoadData){.flag=false, .type=WALKING_SPRITE};
    }

    else {
    // Icon:
        // SUB_A(SPRITE_POKEMON);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mSpriteMons);
        // ADD_HL_DE;
        // LD_A_hl;
        e = SpriteMons[a-SPRITE_POKEMON];
        // goto Mon;
    }

// Mon:
    // LD_E_A;
    // AND_A_A;
    // IF_Z goto NoBreedmon;
    if(e != 0) {
        // FARCALL(aLoadOverworldMonIcon);
        struct IconData icn = LoadOverworldMonIcon(e);

        // LD_L(WALKING_SPRITE);
        // LD_H(0);
        // SCF;
        // RET;
        return (struct SpriteLoadData){.flag=true, .type=WALKING_SPRITE, .path=icn.path, .length=icn.c};
    }


// NoBreedmon:
    // LD_A(WALKING_SPRITE);
    // LD_L(WALKING_SPRITE);
    // LD_H(0);
    // AND_A_A;
    // RET;
    return (struct SpriteLoadData){.flag=false, .type=WALKING_SPRITE};
}

//  Checks to see whether we can apply a facing to a sprite.
//  Returns true unless the sprite is a Pokemon or a Still Sprite.
bool v_DoesSpriteHaveFacings(uint8_t a){
    // CP_A(SPRITE_POKEMON);
    // IF_NC goto only_down;
    if(a >= SPRITE_POKEMON)
        return false;

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
    a = OverworldSprites[a-1].type;
    // CP_A(STILL_SPRITE);
    // IF_NZ goto only_down;
    return (a != STILL_SPRITE);
    // SCF;
    // RET;

// only_down:
    // AND_A_A;
    // RET;
}

uint8_t v_GetSpritePalette(uint8_t c){
    // LD_A_C;
    // CALL(aGetMonSprite);
    // IF_C goto is_pokemon;
    struct SpriteLoadData res = GetMonSprite(c);
    if(res.flag) {
    // is_pokemon:
        // XOR_A_A;
        // LD_C_A;
        // RET;
        return 0;
    }

    // LD_HL(mOverworldSprites + SPRITEDATA_PALETTE);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_A(NUM_SPRITEDATA_FIELDS);
    // CALL(aAddNTimes);
    // LD_C_hl;
    // RET;
    return OverworldSprites[res.type - 1].pal;
}

static void LoadAndSortSprites(void){
    // CALL(aLoadSpriteGFX);
    LoadSpriteGFX();
    // CALL(aSortUsedSprites);
    SortUsedSprites();
    // CALL(aArrangeUsedSprites);
    ArrangeUsedSprites();
    // RET;
}

//  Add any new sprite ids to a list of graphics to be loaded.
//  Return true if the list is full.
static bool AddSpriteGFX(uint8_t a){
    // PUSH_HL;
    // PUSH_BC;
    // LD_B_A;
    // LD_HL(wUsedSprites + 2);
    uint8_t* hl = wram->wUsedSprites + 2;
    // LD_C(SPRITE_GFX_LIST_CAPACITY - 1);
    uint8_t c = SPRITE_GFX_LIST_CAPACITY - 1;

    do {
    // loop:
        // LD_A_hl;
        // CP_A_B;
        // IF_Z goto exists;
        if(*hl == a) {
        // exists:
            // POP_BC;
            // POP_HL;
            // AND_A_A;
            // RET;
            return false;
        }
        // AND_A_A;
        // IF_Z goto new;
        if(*hl == 0) {
        // new:
            // LD_hl_B;
            *hl = a;
            // POP_BC;
            // POP_HL;
            // AND_A_A;
            // RET;
            return false;
        }
        // INC_HL;
        // INC_HL;
        hl += 2;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

    // POP_BC;
    // POP_HL;
    // SCF;
    // RET;
    return true;
}

static uint8_t LoadSpriteGFX_LoadSprite(uint8_t a) {
// push bc
    // CALL(aGetSprite);
    struct SpriteLoadData data = GetSprite(a);
// pop bc
    // LD_A_L;
    return data.type;
    // RET;
}

static void LoadSpriteGFX(void){
//  Bug: b is not preserved, so it's useless as a next count.
//  Uncomment the lines below to fix.

    // LD_HL(wUsedSprites);
    uint8_t* hl = wram->wUsedSprites;
    // LD_B(SPRITE_GFX_LIST_CAPACITY);

    for(uint8_t b = 0; b < SPRITE_GFX_LIST_CAPACITY; b++) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto done;
        if(hl[2*b] == 0)
            return;
        // PUSH_HL;
        // CALL(aLoadSpriteGFX_LoadSprite);
        // POP_HL;
        // LD_hli_A;
        hl[2*b + 1] = LoadSpriteGFX_LoadSprite(hl[2*b]);
        // DEC_B;
        // IF_NZ goto loop;
    }


// done:
    // RET;
}

//  Bubble-sort sprites by type.
static void SortUsedSprites(void){
//  Run backwards through wUsedSprites to find the last one.
    // LD_C(SPRITE_GFX_LIST_CAPACITY);
    uint8_t c = SPRITE_GFX_LIST_CAPACITY;
    // LD_DE(wUsedSprites + (SPRITE_GFX_LIST_CAPACITY - 1) * 2);
    uint8_t* de = wram->wUsedSprites + (SPRITE_GFX_LIST_CAPACITY - 1) * 2;

    do {
    // FindLastSprite:
        // LD_A_de;
        // AND_A_A;
        // IF_NZ goto FoundLastSprite;
        if(*de != 0)
            break;
        // DEC_DE;
        // DEC_DE;
        de -= 2;
        // DEC_C;
        // IF_NZ goto FindLastSprite;
    } while(--c != 0);

// FoundLastSprite:
    // DEC_C;
    // IF_Z goto quit;
    if(--c == 0)
        return;

//  If the length of the current sprite is
//  higher than a later one, swap them.

    // INC_DE;
    de++;
    // LD_HL(wUsedSprites + 1);
    uint8_t* hl = wram->wUsedSprites + 1;

    do {
    // CheckSprite:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_DE;
        uint8_t* de2 = de;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // CheckFollowing:
            // LD_A_de;
            // CP_A_hl;
            // IF_NC goto loop;

        //  Swap the two sprites.
            if(*de2 < *hl2){
                // LD_B_A;
                uint8_t temp = *hl2;
                // LD_A_hl;
                // LD_hl_B;
                *hl2 = *de2;
                // LD_de_A;
                *de2 = temp;
                // DEC_DE;
                --de2;
                // DEC_HL;
                --hl2;
                // LD_A_de;
                // LD_B_A;
                // LD_A_hl;
                temp = *hl2;
                // LD_hl_B;
                *hl2 = *de2;
                // LD_de_A;
                *de2 = temp;
                // INC_DE;
                ++de2;
                // INC_HL;
                ++hl2;
            }
        //  Keep doing this until everything's in order.

        // loop:
            // DEC_DE;
            // DEC_DE;
            de2 -= 2;
            // DEC_C;
            // IF_NZ goto CheckFollowing;
        } while(--c2 != 0);

        // POP_HL;
        // INC_HL;
        // INC_HL;
        hl += 2;
        // POP_DE;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto CheckSprite;
    } while(--c != 0);

// quit:
    // RET;
}

//  Get the length of each sprite and space them out in VRAM.
//  Crystal introduces a second table in VRAM bank 0.
static void ArrangeUsedSprites(void){
    // LD_HL(wUsedSprites);
    uint8_t* hl = wram->wUsedSprites;
    // LD_C(SPRITE_GFX_LIST_CAPACITY);
    uint8_t c = SPRITE_GFX_LIST_CAPACITY;
    // LD_B(0);
    uint8_t b = 0;

    do {
    // FirstTableLength:
    //  Keep going until the end of the list.
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto quit;
        if(*hl == 0)
            return;

        hl++;
        // LD_A_hl;
        // CALL(aGetSpriteLength);
        uint8_t a = GetSpriteLength(*hl);

    //  Spill over into the second table after $80 tiles.
        // ADD_A_B;
        // CP_A(0x80);
        // IF_Z goto loop;
        // IF_NC goto SecondTable;
        if(a + b > 0x80)
            break;

        // printf("1: %d, %d, %d\n", *hl, a, b);
    // loop:
        // LD_hl_B;
        *hl = b;
        // INC_HL;
        hl++;
        // LD_B_A;
        b += a;

    //  Assumes the next table will be reached before c hits 0.
        // DEC_C;
        // IF_NZ goto FirstTableLength;
    } while(--c != 0);

// SecondTable:
//  The second tile table starts at tile $80.
    // LD_B(0x80);
    b = 0x80;
    // DEC_HL;
    --hl;

    do {
    // SecondTableLength:
    //  Keep going until the end of the list.
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto quit;
        if(*hl == 0)
            return;

        hl++;
        // LD_A_hl;
        // CALL(aGetSpriteLength);
        uint8_t a = GetSpriteLength(*hl);

    //  There are only two tables, so don't go any further than that.
        // ADD_A_B;
        // IF_C goto quit;
        if(a + b > 255)
            return;

        // printf("2: %d, %d, %d\n", *hl, a, b);
        // LD_hl_B;
        *hl = b;
        // LD_B_A;
        b += a;
        // INC_HL;
        hl++;

        // DEC_C;
        // IF_NZ goto SecondTableLength;
    } while(--c != 0);

// quit:
    // RET;
}

//  Return the length of sprite type a in tiles.
static uint8_t GetSpriteLength(uint8_t a){
    switch(a) {
        // CP_A(WALKING_SPRITE);
        // IF_Z goto AnyDirection;
        // CP_A(STANDING_SPRITE);
        // IF_Z goto AnyDirection;
        case WALKING_SPRITE:
        case STANDING_SPRITE:
        // AnyDirection:
            // LD_A(12);
            // RET;
            return 12;
        // CP_A(STILL_SPRITE);
        // IF_Z goto OneDirection;
        case STILL_SPRITE:
        // OneDirection:
            // LD_A(4);
            // RET;
            return 4;
        default: 
            // LD_A(12);
            // RET;
            return 12;
    }
}

static void GetUsedSprites(void){
    // LD_HL(wUsedSprites);
    uint8_t* hl = wram->wUsedSprites;
    // LD_C(SPRITE_GFX_LIST_CAPACITY);
    uint8_t c = SPRITE_GFX_LIST_CAPACITY;

    do {
    // loop:
        // LD_A_addr(wSpriteFlags);
        // RES_A(5);
        // LD_addr_A(wSpriteFlags);
        bit_reset(wram->wSpriteFlags, 5);

        // LD_A_hli;
        uint8_t a = *(hl++);
        // AND_A_A;
        // IF_Z goto done;
        if(a == 0)
            break;
        // LDH_addr_A(hUsedSpriteIndex);
        hram.hUsedSpriteIndex = a;

        // LD_A_hli;
        a = *(hl++);
        // LDH_addr_A(hUsedSpriteTile);
        hram.hUsedSpriteTile = a;

        // BIT_A(7);
        // IF_Z goto dont_set;
        if(bit_test(a, 7)) {
            // LD_A_addr(wSpriteFlags);
            // SET_A(5);  // load VBank0
            // LD_addr_A(wSpriteFlags);
            bit_set(wram->wSpriteFlags, 5);
        }

    // dont_set:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aGetUsedSprite);
        GetUsedSprite();
        // POP_HL;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// done:
    // RET;
}

//  Return the address of tile (a) in (hl).
static uint8_t* GetUsedSprite_GetTileAddr(uint8_t a) {
    // AND_A(0x7f);
    // LD_L_A;
    // LD_H(0);
    // for(int rept = 0; rept < 4; rept++){
    //     ADD_HL_HL;
    // }
    // LD_A_L;
    // ADD_A(LOW(vTiles0));
    // LD_L_A;
    // LD_A_H;
    // ADC_A(HIGH(vTiles0));
    // LD_H_A;
    return vram->vTiles0 + ((a & 0x7f) << 4);
    // RET;
}

void GetUsedSprite_CopyToVram(struct SpriteLoadData* sd, uint8_t* hl, uint16_t start) {
    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A_addr(wSpriteFlags);
    // BIT_A(5);
    if(!bit_test(wram->wSpriteFlags, 5)) {
        hl += VRAM_BANK_SIZE;
    }
    // LD_A(0x1);
    // IF_Z goto bankswitch;
    // LD_A(0x0);


// bankswitch:
    // LDH_addr_A(rVBK);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(hl, sd->path, start, sd->length);
    // POP_AF;
    // LDH_addr_A(rVBK);
    // RET;
}

void GetUsedSprite(void){
    // LDH_A_addr(hUsedSpriteIndex);
    // CALL(aSafeGetSprite);
    struct SpriteLoadData sd = SafeGetSprite(hram.hUsedSpriteIndex);
    // LDH_A_addr(hUsedSpriteTile);
    // CALL(aGetUsedSprite_GetTileAddr);
    uint8_t* hl = GetUsedSprite_GetTileAddr(hram.hUsedSpriteTile);
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wSpriteFlags);
    // BIT_A(7);
    // IF_NZ goto skip;
    if(!bit_test(wram->wSpriteFlags, 7)) {
        // CALL(aGetUsedSprite_CopyToVram);
        GetUsedSprite_CopyToVram(&sd, hl, 0);
    }

// skip:
    // POP_BC;
    // LD_L_C;
    // LD_H(0x0);
    // for(int rept = 0; rept < 4; rept++){
    // ADD_HL_HL;
    // }
    // POP_DE;
    // ADD_HL_DE;
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    uint16_t de = sd.length;

    // LD_A_addr(wSpriteFlags);
    // BIT_A(5);
    // IF_NZ goto done;
    // BIT_A(6);
    // IF_NZ goto done;

    // LDH_A_addr(hUsedSpriteIndex);
    // CALL(av_DoesSpriteHaveFacings);
    // IF_C goto done;
    if(!(wram->wSpriteFlags & ((1 << 6) | (1 << 5)))
    && v_DoesSpriteHaveFacings(hram.hUsedSpriteIndex)) {
        // LD_A_H;
        // ADD_A(HIGH(vTiles1 - vTiles0));
        // LD_H_A;
        // CALL(aGetUsedSprite_CopyToVram);
        GetUsedSprite_CopyToVram(&sd, hl + sizeof(vram->vTiles0), de);
    }

done:;
    // RET;
}

void LoadEmote(uint8_t c){
//  Get the address of the pointer to emote c.
    // LD_A_C;
    // LD_BC(EMOTE_LENGTH);
    // LD_HL(mEmotes);
    // CALL(aAddNTimes);
    const struct Emote* hl = Emotes + c;
//  Load the emote address into de
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    const char* path = hl->graphicsPath;
//  load the length of the emote (in tiles) into c
    // INC_HL;
    // LD_C_hl;
    // SWAP_C;
    uint8_t size = hl->length << 4;
//  load the emote pointer bank into b
    // INC_HL;
    // LD_B_hl;
//  load the VRAM destination into hl
    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t tile = hl->startingTile;
//  if the emote has a length of 0, do not proceed (error handling)
    // LD_A_C;
    // AND_A_A;
    // RET_Z ;
    if(size == 0)
        return;
    // CALL(aGetEmote2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles3 + tile * LEN_2BPP_TILE, path, 0, size);
    // RET;

// INCLUDE "data/sprites/emotes.asm"

// INCLUDE "data/sprites/sprite_mons.asm"

// INCLUDE "data/maps/outdoor_sprites.asm"

// INCLUDE "data/sprites/sprites.asm"

}