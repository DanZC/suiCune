#include "../../constants.h"
#include "player_movement.h"
#include "../../home/map_objects.h"
#include "../../home/audio.h"
#include "../../home/gfx.h"
#include "../../home/map.h"
#include "npc_movement.h"
#include "warp_connection.h"

static void DoPlayerMovement_GetDPad(void);
static uint8_t DoPlayerMovement_TranslateIntoMovement(void);
static u8_flag_s DoPlayerMovement_CheckTile(void);
static u8_flag_s DoPlayerMovement_CheckTurning(void);
static u8_flag_s DoPlayerMovement_TryStep(void);
static u8_flag_s DoPlayerMovement_TrySurf(void);
static u8_flag_s DoPlayerMovement_ExitWater(void);
static uint8_t DoPlayerMovement_CheckNPC(void);
static uint8_t DoPlayerMovement_CheckSurfPerms(void);
static uint8_t DoPlayerMovement_CheckSurfable(uint8_t a);
static bool DoPlayerMovement_BikeCheck(void);
static u8_flag_s DoPlayerMovement_TryJump(void);
static u8_flag_s DoPlayerMovement_CheckWarp(void);
static uint8_t DoPlayerMovement_DoStep(uint8_t a);
static uint8_t DoPlayerMovement_StandInPlace(void);
static uint8_t DoPlayerMovement_WalkInPlace(void);
static void DoPlayerMovement_CheckForced(void);
static void DoPlayerMovement_GetAction(void);
static bool DoPlayerMovement_CheckStrengthBoulder(struct Object* bc);
static bool DoPlayerMovement_CheckLandPerms(void);
static bool DoPlayerMovement_CheckWalkable(uint8_t a);
static bool DoPlayerMovement_BumpSound(void);
static void DoPlayerMovement_GetOutOfWater(void);

static void DoPlayerMovement_GetDPad(void) {
    // LDH_A_addr(hJoyDown);
    // LD_addr_A(wCurInput);
    wram->wCurInput = hram.hJoyDown;

//  Standing downhill instead moves down.

    // LD_HL(wBikeFlags);
    // BIT_hl(BIKEFLAGS_DOWNHILL_F);
    // RET_Z ;
    if(!bit_test(gPlayer.bikeFlags, BIKEFLAGS_DOWNHILL_F))
        return;

    // LD_C_A;
    // AND_A(D_PAD);
    // RET_NZ ;
    if(wram->wCurInput & (D_PAD))
        return;

    // LD_A_C;
    // OR_A(D_DOWN);
    // LD_addr_A(wCurInput);
    // RET;
    wram->wCurInput |= D_DOWN;
}

static uint8_t DoPlayerMovement_TranslateIntoMovement(void) {
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_NORMAL);
    // IF_Z goto Normal;
    u8_flag_s res;
    switch(gPlayer.playerState) {
    // CP_A(PLAYER_SURF);
    // IF_Z goto Surf;
    // CP_A(PLAYER_SURF_PIKA);
    // IF_Z goto Surf;
    case PLAYER_SURF:
    case PLAYER_SURF_PIKA:
    // Surf:
        // CALL(aDoPlayerMovement_CheckForced);
        DoPlayerMovement_CheckForced();
        // CALL(aDoPlayerMovement_GetAction);
        DoPlayerMovement_GetAction();
        // CALL(aDoPlayerMovement_CheckTile);
        // RET_C ;
        res = DoPlayerMovement_CheckTile();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_CheckTurning);
        // RET_C ;
        res = DoPlayerMovement_CheckTurning();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_TrySurf);
        // RET_C ;
        res = DoPlayerMovement_TrySurf();
        if(res.flag) return res.a;
        // goto NotMoving;
        break;
    // CP_A(PLAYER_BIKE);
    // IF_Z goto Normal;
    // CP_A(PLAYER_SKATE);
    // IF_Z goto Ice;
    case PLAYER_SKATE:
    // Ice:
        // CALL(aDoPlayerMovement_CheckForced);
        DoPlayerMovement_CheckForced();
        // CALL(aDoPlayerMovement_GetAction);
        DoPlayerMovement_GetAction();
        // CALL(aDoPlayerMovement_CheckTile);
        // RET_C ;
        res = DoPlayerMovement_CheckTile();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_CheckTurning);
        // RET_C ;
        res = DoPlayerMovement_CheckTurning();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_TryStep);
        // RET_C ;
        res = DoPlayerMovement_TryStep();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_TryJump);
        // RET_C ;
        res = DoPlayerMovement_TryJump();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_CheckWarp);
        // RET_C ;
        res = DoPlayerMovement_CheckWarp();
        if(res.flag) return res.a;
        // LD_A_addr(wWalkingDirection);
        // CP_A(STANDING);
        // IF_Z goto HitWall;
        if(wram->wWalkingDirection != STANDING)
            // CALL(aDoPlayerMovement_BumpSound);
            DoPlayerMovement_BumpSound();
    // HitWall:
        // CALL(aDoPlayerMovement_StandInPlace);
        DoPlayerMovement_StandInPlace();
        // XOR_A_A;
        // RET;
        return 0;
    default:
    case PLAYER_NORMAL:
    case PLAYER_BIKE:
    // Normal:
        // CALL(aDoPlayerMovement_CheckForced);
        DoPlayerMovement_CheckForced();
        // CALL(aDoPlayerMovement_GetAction);
        DoPlayerMovement_GetAction();
        // CALL(aDoPlayerMovement_CheckTile);
        // RET_C ;
        res = DoPlayerMovement_CheckTile();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_CheckTurning);
        // RET_C ;
        res = DoPlayerMovement_CheckTurning();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_TryStep);
        // RET_C ;
        res = DoPlayerMovement_TryStep();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_TryJump);
        // RET_C ;
        res = DoPlayerMovement_TryJump();
        if(res.flag) return res.a;
        // CALL(aDoPlayerMovement_CheckWarp);
        // RET_C ;
        res = DoPlayerMovement_CheckWarp();
        if(res.flag) return res.a;
        break;
        // goto NotMoving;
    }


// NotMoving:
    // LD_A_addr(wWalkingDirection);
    // CP_A(STANDING);
    // IF_Z goto Standing;
    if(wram->wWalkingDirection == STANDING) {
    // Standing:
        // CALL(aDoPlayerMovement_StandInPlace);
        // XOR_A_A;
        // RET;
        DoPlayerMovement_StandInPlace();
        return 0;
    }

//  Walking into an edge warp won't bump.
    // LD_A_addr(wWalkingIntoEdgeWarp);
    // AND_A_A;
    // IF_NZ goto CantMove;
    if(wram->wWalkingIntoEdgeWarp == 0)
    // CALL(aDoPlayerMovement_BumpSound);
        DoPlayerMovement_BumpSound();

// CantMove:
    // CALL(aDoPlayerMovement__WalkInPlace);
    // XOR_A_A;
    // RET;
    DoPlayerMovement_WalkInPlace();
    return 0;
}

//  Tiles such as waterfalls and warps move the player
//  in a given direction, overriding input.
static u8_flag_s DoPlayerMovement_CheckTile(void) {
    static const uint8_t water_table[] = {
        RIGHT,  // COLL_WATERFALL_RIGHT
        LEFT,  // COLL_WATERFALL_LEFT
        UP,  // COLL_WATERFALL_UP
        DOWN,  // COLL_WATERFALL
    };

    static const int8_t land1_table[] = {
        STANDING,  // COLL_BRAKE
        RIGHT,  // COLL_WALK_RIGHT
        LEFT,  // COLL_WALK_LEFT
        UP,  // COLL_WALK_UP
        DOWN,  // COLL_WALK_DOWN
        STANDING,  // COLL_BRAKE_45
        STANDING,  // COLL_BRAKE_46
        STANDING,  // COLL_BRAKE_47
    };

    static const int8_t land2_table[] = {
        RIGHT,  // COLL_WALK_RIGHT_ALT
        LEFT,  // COLL_WALK_LEFT_ALT
        UP,  // COLL_WALK_UP_ALT
        DOWN,  // COLL_WALK_DOWN_ALT
        STANDING,  // COLL_BRAKE_ALT
        STANDING,  // COLL_BRAKE_55
        STANDING,  // COLL_BRAKE_56
        STANDING,  // COLL_BRAKE_57
    };
    // LD_A_addr(wPlayerStandingTile);
    // LD_C_A;
    // CALL(aCheckWhirlpoolTile);
    // IF_C goto not_whirlpool;
    if(CheckWhirlpoolTile(gPlayer.playerStruct.nextTile))
        return u8_flag(PLAYERMOVEMENT_FORCE_TURN, true);
    // LD_A(PLAYERMOVEMENT_FORCE_TURN);
    // SCF;
    // RET;

    uint8_t c = gPlayer.playerStruct.nextTile;
// not_whirlpool:
    // AND_A(0xf0);
    switch(c & 0xf0) {
        // CP_A(HI_NYBBLE_CURRENT);
        // IF_Z goto water;
        case HI_NYBBLE_CURRENT:
        // water:
            // LD_A_C;
            // maskbits(NUM_DIRECTIONS, 0);
            // LD_C_A;
            // LD_B(0);
            // LD_HL(mDoPlayerMovement_water_table);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_addr_A(wWalkingDirection);
            wram->wWalkingDirection = water_table[c & 3];
            // goto continue_walk;
            break;
        // CP_A(HI_NYBBLE_WALK);
        // IF_Z goto land1;
        case HI_NYBBLE_WALK:
        // land1:
            // LD_A_C;
            // AND_A(7);
            // LD_C_A;
            // LD_B(0);
            // LD_HL(mDoPlayerMovement_land1_table);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(STANDING);
            // IF_Z goto no_walk;
            if(land1_table[c & 7] == STANDING)
                return u8_flag(0, false);
            // LD_addr_A(wWalkingDirection);
            wram->wWalkingDirection = land1_table[c & 7];
            // goto continue_walk;
            break;
        // CP_A(HI_NYBBLE_WALK_ALT);
        // IF_Z goto land2;
        case HI_NYBBLE_WALK_ALT:
        // land2:
            // LD_A_C;
            // AND_A(7);
            // LD_C_A;
            // LD_B(0);
            // LD_HL(mDoPlayerMovement_land2_table);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(STANDING);
            // IF_Z goto no_walk;
            if(land2_table[c & 7] == STANDING)
                return u8_flag(0, false);
            // LD_addr_A(wWalkingDirection);
            wram->wWalkingDirection = land2_table[c & 7];
            // goto continue_walk;
            break;
        // CP_A(HI_NYBBLE_WARPS);
        // IF_Z goto warps;
        case HI_NYBBLE_WARPS:
        // warps:
            // LD_A_C;
            // CP_A(COLL_DOOR);
            // IF_Z goto down;
            // CP_A(COLL_DOOR_79);
            // IF_Z goto down;
            // CP_A(COLL_STAIRCASE);
            // IF_Z goto down;
            // CP_A(COLL_CAVE);
            // IF_NZ goto no_walk;
            if(c == COLL_DOOR || c == COLL_DOOR_79 || c == COLL_STAIRCASE || c == COLL_CAVE) {
            // down:
                // LD_A(DOWN);
                // LD_addr_A(wWalkingDirection);
                wram->wWalkingDirection = DOWN;
                // goto continue_walk;
                break;
            }
            // goto no_walk;
            return u8_flag(0, false);
        default:
            return u8_flag(0, false);
    }


// no_walk:
    // XOR_A_A;
    // RET;
    // return (u8_flag_s){.a = 0, .flag = false};


// continue_walk:
    // LD_A(STEP_WALK);
    // CALL(aDoPlayerMovement_DoStep);
    DoPlayerMovement_DoStep(STEP_WALK);
    // LD_A(PLAYERMOVEMENT_CONTINUE);
    // SCF;
    // RET;
    return u8_flag(PLAYERMOVEMENT_CONTINUE, true);
}

//  If the player is turning, change direction first. This also lets
//  the player change facing without moving by tapping a direction.
static u8_flag_s DoPlayerMovement_CheckTurning(void) {
    // LD_A_addr(wPlayerTurningDirection);
    // CP_A(0);
    // IF_NZ goto not_turning;
    if(wram->wPlayerTurningDirection != 0)
        return u8_flag(0, false);
    // LD_A_addr(wWalkingDirection);
    // CP_A(STANDING);
    // IF_Z goto not_turning;
    if(wram->wWalkingDirection == STANDING)
        return u8_flag(0, false);

    // LD_E_A;
    int8_t e = wram->wWalkingDirection;
    // LD_A_addr(wPlayerDirection);
    // RRCA;
    // RRCA;
    // maskbits(NUM_DIRECTIONS, 0);
    // CP_A_E;
    // IF_Z goto not_turning;
    if(((gPlayer.playerStruct.facing >> 2) & 3) == e)
        return u8_flag(0, false);

    // LD_A(STEP_TURN);
    // CALL(aDoPlayerMovement_DoStep);
    DoPlayerMovement_DoStep(STEP_TURN);
    // LD_A(PLAYERMOVEMENT_TURN);
    // SCF;
    // RET;
    return u8_flag(PLAYERMOVEMENT_TURN, true);


// not_turning:
    // XOR_A_A;
    // RET;
}

static bool DoPlayerMovement_CheckFacingOffEdgeOfMap(void) {
    return CheckFacingOffEdgeOfMap();
}

static u8_flag_s DoPlayerMovement_TryStep(void) {
//  Surfing actually calls .TrySurf directly instead of passing through here.
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_SURF);
    // IF_Z goto TrySurf;
    // CP_A(PLAYER_SURF_PIKA);
    // IF_Z goto TrySurf;
    if(gPlayer.playerState == PLAYER_SURF || gPlayer.playerState == PLAYER_SURF_PIKA)
        return DoPlayerMovement_TrySurf();
    
    // Athletic, wall phasing, blazing speed, running shoes.
    if(hram.hJoyDown & B_BUTTON) {
        uint8_t npc = DoPlayerMovement_CheckNPC();
        if(npc == 0 || npc == 2)
            return (u8_flag_s) {.a = 0, .flag = false};
        u8_flag_s res = DoPlayerMovement_CheckWarp();
        if(res.flag)
            return res;
        // Stop the player from walking off the edge of the map where there isn't a map connection.
        if(DoPlayerMovement_CheckFacingOffEdgeOfMap())
            return u8_flag(0, false);
        return (u8_flag_s) {.a = DoPlayerMovement_DoStep(STEP_BIKE), .flag = true};
    }

    // CALL(aDoPlayerMovement_CheckLandPerms);
    // IF_C goto bump;
    if(!DoPlayerMovement_CheckLandPerms())
        return (u8_flag_s) {.a = 0, .flag = false};
    
    // CALL(aDoPlayerMovement_CheckNPC);
    // AND_A_A;
    // IF_Z goto bump;
    // CP_A(2);
    // IF_Z goto bump;
    uint8_t npc = DoPlayerMovement_CheckNPC();
    if(npc == 0 || npc == 2)
        return (u8_flag_s) {.a = 0, .flag = false};

    // LD_A_addr(wPlayerStandingTile);
    // CALL(aCheckIceTile);
    // IF_NC goto ice;
    if(CheckIceTile(gPlayer.playerStruct.nextTile))
        return (u8_flag_s) {.a = DoPlayerMovement_DoStep(STEP_ICE), .flag = true};

//  Downhill riding is slower when not moving down.
    // CALL(aDoPlayerMovement_BikeCheck);
    // IF_NZ goto walk;
    if(!DoPlayerMovement_BikeCheck())
        return (u8_flag_s) {.a = DoPlayerMovement_DoStep(STEP_WALK), .flag = true};

    // LD_HL(wBikeFlags);
    // BIT_hl(BIKEFLAGS_DOWNHILL_F);
    // IF_Z goto fast;
    if(!bit_test(gPlayer.bikeFlags, BIKEFLAGS_DOWNHILL_F))
        return (u8_flag_s) {.a = DoPlayerMovement_DoStep(STEP_BIKE), .flag = true};

    // LD_A_addr(wWalkingDirection);
    // CP_A(DOWN);
    // IF_Z goto fast;
    if(wram->wWalkingDirection == DOWN)
        return (u8_flag_s) {.a = DoPlayerMovement_DoStep(STEP_BIKE), .flag = true};

    // LD_A(STEP_WALK);
    // CALL(aDoPlayerMovement_DoStep);
    // SCF;
    // RET;
    return (u8_flag_s) {.a = DoPlayerMovement_DoStep(STEP_WALK), .flag = true};


// fast:
    // LD_A(STEP_BIKE);
    // CALL(aDoPlayerMovement_DoStep);
    // SCF;
    // RET;


// walk:
    // LD_A(STEP_WALK);
    // CALL(aDoPlayerMovement_DoStep);
    // SCF;
    // RET;


// ice:
    // LD_A(STEP_ICE);
    // CALL(aDoPlayerMovement_DoStep);
    // SCF;
    // RET;


// unused:
//   //  unreferenced
    // XOR_A_A;
    // RET;

// bump:
    // XOR_A_A;
    // RET;
}

static u8_flag_s DoPlayerMovement_TrySurf(void) {
    // CALL(aDoPlayerMovement_CheckSurfPerms);
    // LD_addr_A(wWalkingIntoLand);
    wram->wWalkingIntoLand = DoPlayerMovement_CheckSurfPerms();
    // IF_C goto surf_bump;
    if(wram->wWalkingIntoLand == 0xff) {
        wram->wWalkingIntoLand = wram->wTilePermissions & wram->wFacingDirection;
        return (u8_flag_s) {.a=0, .flag=false};
    }

    // CALL(aDoPlayerMovement_CheckNPC);
    // LD_addr_A(wWalkingIntoNPC);
    wram->wWalkingIntoNPC = DoPlayerMovement_CheckNPC();
    // AND_A_A;
    // IF_Z goto surf_bump;
    // CP_A(2);
    // IF_Z goto surf_bump;
    if(wram->wWalkingIntoNPC == 0 || wram->wWalkingIntoNPC == 2)
        return (u8_flag_s) {.a=0, .flag=false};

    // LD_A_addr(wWalkingIntoLand);
    // AND_A_A;
    // IF_NZ goto ExitWater;
    if(wram->wWalkingIntoLand != 0)
        return DoPlayerMovement_ExitWater();

    // LD_A(STEP_WALK);
    // CALL(aDoPlayerMovement_DoStep);
    // SCF;
    // RET;
    return u8_flag(DoPlayerMovement_DoStep(STEP_WALK), true);

// surf_bump:
    // XOR_A_A;
    // RET;
}

static u8_flag_s DoPlayerMovement_ExitWater(void) {
    // CALL(aDoPlayerMovement_GetOutOfWater);
    DoPlayerMovement_GetOutOfWater();
    // CALL(aPlayMapMusic);
    PlayMapMusic();
    // LD_A(STEP_WALK);
    // CALL(aDoPlayerMovement_DoStep);
    DoPlayerMovement_DoStep(STEP_WALK);
    // LD_A(PLAYERMOVEMENT_EXIT_WATER);
    // SCF;
    // RET;
    return u8_flag(PLAYERMOVEMENT_EXIT_WATER, true);
}

//  Returns 0 if there is an NPC in front that you can't move
//  Returns 1 if there is no NPC in front
//  Returns 2 if there is a movable NPC in front
static uint8_t DoPlayerMovement_CheckNPC(void) {
    // LD_A(0);
    // LDH_addr_A(hMapObjectIndex);
    hram.hMapObjectIndex = 0;
//  Load the next X coordinate into d
    // LD_A_addr(wPlayerStandingMapX);
    // LD_D_A;
    // LD_A_addr(wWalkingX);
    // ADD_A_D;
    // LD_D_A;
    uint8_t d = gPlayer.playerStruct.nextMapX + wram->wWalkingX;
//  Load the next Y coordinate into e
    // LD_A_addr(wPlayerStandingMapY);
    // LD_E_A;
    // LD_A_addr(wWalkingY);
    // ADD_A_E;
    // LD_E_A;
    uint8_t e = gPlayer.playerStruct.nextMapY + wram->wWalkingY;
//  Find an object struct with coordinates equal to d,e
    // LD_BC(wObjectStructs);  // redundant
    struct Object* bc = IsNPCAtCoord(d, e);
    // FARCALL(aIsNPCAtCoord);
    // IF_NC return 1;
    if(bc == NULL)
        return 1;
    // CALL(aDoPlayerMovement_CheckStrengthBoulder);
    // IF_C return 2;
    if(DoPlayerMovement_CheckStrengthBoulder(bc))
        return 2;

    // XOR_A_A;
    // RET;
    return 0;
// is_npc:
    // LD_A(1);
    // RET;
// no_bump:
    // LD_A(2);
    // RET;
}

//  Return 0 if moving in water, or 1 if moving onto land.
//  Otherwise, return carry.
static uint8_t DoPlayerMovement_CheckSurfPerms(void) {
    // LD_A_addr(wTilePermissions);
    // LD_D_A;
    // LD_A_addr(wFacingDirection);
    // AND_A_D;
    // IF_NZ goto NotSurfable;
    if(wram->wTilePermissions & wram->wFacingDirection)
        return 0xff;

    // LD_A_addr(wWalkingTile);
    // CALL(aDoPlayerMovement_CheckSurfable);
    // IF_C goto NotSurfable;

    // AND_A_A;
    // RET;
    return DoPlayerMovement_CheckSurfable(wram->wWalkingTile);

// NotSurfable:
    // SCF;
    // RET;
}

//  Return 0 if tile a is water, or 1 if land.
//  Otherwise, return carry.
static uint8_t DoPlayerMovement_CheckSurfable(uint8_t a) {
    // CALL(aGetTileCollision);
    // CP_A(WATER_TILE);
    // IF_Z goto Water;
    uint8_t col = GetTileCollision(a);
    if(col == WATER_TILE)
        return 0;

//  Can walk back onto land from water.
    // AND_A_A;  // LAND_TILE
    // IF_Z goto Land;
    if(col == LAND_TILE)
        return 1;

    // goto Neither;

// Water:
    // XOR_A_A;
    // RET;

// Land:
    // LD_A(1);
    // AND_A_A;
    // RET;

// Neither:
    // SCF;
    // RET;
    return 0xff;
}

static bool DoPlayerMovement_BikeCheck(void) {
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_BIKE);
    // RET_Z ;
    // CP_A(PLAYER_SKATE);
    // RET;
    return (gPlayer.playerState == PLAYER_BIKE || gPlayer.playerState == PLAYER_SKATE);
}

static u8_flag_s DoPlayerMovement_TryJump(void) {
    static const uint8_t ledge_table[] = {
        //db ['FACE_RIGHT'];  // COLL_HOP_RIGHT
        FACE_RIGHT,
        //db ['FACE_LEFT'];  // COLL_HOP_LEFT
        FACE_LEFT,
        //db ['FACE_UP'];  // COLL_HOP_UP
        FACE_UP,
        //db ['FACE_DOWN'];  // COLL_HOP_DOWN
        FACE_DOWN,
        //db ['FACE_RIGHT | FACE_DOWN'];  // COLL_HOP_DOWN_RIGHT
        FACE_RIGHT | FACE_DOWN,
        //db ['FACE_DOWN | FACE_LEFT'];  // COLL_HOP_DOWN_LEFT
        FACE_DOWN | FACE_LEFT,
        //db ['FACE_UP | FACE_RIGHT'];  // COLL_HOP_UP_RIGHT
        FACE_UP | FACE_RIGHT,
        //db ['FACE_UP | FACE_LEFT'];  // COLL_HOP_UP_LEFT
        FACE_UP | FACE_LEFT
    };

    // LD_A_addr(wPlayerStandingTile);
    // LD_E_A;
    uint8_t e = gPlayer.playerStruct.nextTile;
    // AND_A(0xf0);
    // CP_A(HI_NYBBLE_LEDGES);
    // IF_NZ goto DontJump;
    if((e & 0xf0) != HI_NYBBLE_LEDGES)
        return (u8_flag_s){.a = 0, .flag = false};

    // LD_A_E;
    // AND_A(7);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mDoPlayerMovement_ledge_table);
    // ADD_HL_DE;
    // LD_A_addr(wFacingDirection);
    // AND_A_hl;
    // IF_Z goto DontJump;
    if((wram->wFacingDirection & ledge_table[e & 7]) == 0)
        return (u8_flag_s){.a = 0, .flag = false};

    // LD_DE(SFX_JUMP_OVER_LEDGE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_JUMP_OVER_LEDGE);
    // LD_A(STEP_LEDGE);
    // CALL(aDoPlayerMovement_DoStep);
    DoPlayerMovement_DoStep(STEP_LEDGE);
    // LD_A(PLAYERMOVEMENT_JUMP);
    // SCF;
    // RET;
    return (u8_flag_s){.a = PLAYERMOVEMENT_JUMP, .flag = true};


// DontJump:
    // XOR_A_A;
    // RET;


// ledge_table:
    //db ['FACE_RIGHT'];  // COLL_HOP_RIGHT
    //db ['FACE_LEFT'];  // COLL_HOP_LEFT
    //db ['FACE_UP'];  // COLL_HOP_UP
    //db ['FACE_DOWN'];  // COLL_HOP_DOWN
    //db ['FACE_RIGHT | FACE_DOWN'];  // COLL_HOP_DOWN_RIGHT
    //db ['FACE_DOWN | FACE_LEFT'];  // COLL_HOP_DOWN_LEFT
    //db ['FACE_UP | FACE_RIGHT'];  // COLL_HOP_UP_RIGHT
    //db ['FACE_UP | FACE_LEFT'];  // COLL_HOP_UP_LEFT
}

static u8_flag_s DoPlayerMovement_CheckWarp(void) {
    static const uint8_t EdgeWarps[] = {
        COLL_WARP_CARPET_DOWN,
        COLL_WARP_CARPET_UP,
        COLL_WARP_CARPET_LEFT,
        COLL_WARP_CARPET_RIGHT,
    };

//  Bug: Since no case is made for STANDING here, it will check
//  [.EdgeWarps + $ff]. This resolves to $3e.
//  This causes wWalkingIntoEdgeWarp to be nonzero when standing on tile $3e,
//  making bumps silent.

    // LD_A_addr(wWalkingDirection);
    int8_t a = wram->wWalkingDirection;
// cp STANDING
// jr z, .not_warp
    if(a == STANDING)
        return u8_flag(PLAYERMOVEMENT_NORMAL, false);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mDoPlayerMovement_EdgeWarps);
    // ADD_HL_DE;
    // LD_A_addr(wPlayerStandingTile);
    // CP_A_hl;
    // IF_NZ goto not_warp;
    if(gPlayer.playerStruct.nextTile != EdgeWarps[a])
        return u8_flag(PLAYERMOVEMENT_NORMAL, false);

    // LD_A(TRUE);
    // LD_addr_A(wWalkingIntoEdgeWarp);
    wram->wWalkingIntoEdgeWarp = TRUE;
    // LD_A_addr(wWalkingDirection);
// This is in the wrong place.
    // CP_A(STANDING);
    // IF_Z goto not_warp;

    // LD_E_A;
    // LD_A_addr(wPlayerDirection);
    // RRCA;
    // RRCA;
    // maskbits(NUM_DIRECTIONS, 0);
    // CP_A_E;
    // IF_NZ goto not_warp;
    if(((gPlayer.playerStruct.facing >> 2) & 3) != wram->wWalkingDirection)
        return u8_flag(PLAYERMOVEMENT_NORMAL, false);

    // CALL(aWarpCheck);
    // IF_NC goto not_warp;
    if(!WarpCheck())
        return u8_flag(PLAYERMOVEMENT_NORMAL, false);

    // CALL(aDoPlayerMovement_StandInPlace);
    DoPlayerMovement_StandInPlace();
    // SCF;
    // LD_A(PLAYERMOVEMENT_WARP);
    // RET;
    return u8_flag(PLAYERMOVEMENT_WARP, true);


// not_warp:
    // XOR_A_A;  // PLAYERMOVEMENT_NORMAL
    // RET;
}

static uint8_t DoPlayerMovement_DoStep(uint8_t a) {
    static const uint8_t Steps[][4] = {
    //  entries correspond to STEP_* constants (see constants/map_object_constants.asm)
        //table_width ['2', 'DoPlayerMovement.Steps']
        //dw ['.SlowStep']; SlowStep:
        [STEP_SLOW] = {
            slow_step(DOWN),
            slow_step(UP),
            slow_step(LEFT),
            slow_step(RIGHT),
        },
        //dw ['.NormalStep'];NormalStep:
        [STEP_WALK] = {
            step(DOWN),
            step(UP),
            step(LEFT),
            step(RIGHT),
        },
        //dw ['.FastStep'];FastStep:
        [STEP_BIKE] = {
            big_step(DOWN),
            big_step(UP),
            big_step(LEFT),
            big_step(RIGHT),
        },
        //dw ['.JumpStep'];JumpStep:
        [STEP_LEDGE] = {
            jump_step(DOWN),
            jump_step(UP),
            jump_step(LEFT),
            jump_step(RIGHT),
        },
        //dw ['.SlideStep'];SlideStep:
        [STEP_ICE] = {
            fast_slide_step(DOWN),
            fast_slide_step(UP),
            fast_slide_step(LEFT),
            fast_slide_step(RIGHT),
        },
        //dw ['.TurningStep'];TurningStep:
        [STEP_TURN] = {
            turn_step(DOWN),
            turn_step(UP),
            turn_step(LEFT),
            turn_step(RIGHT),
        },
        //dw ['.BackJumpStep'];BackJumpStep:
        [STEP_BACK_LEDGE] = {
            jump_step(UP),
            jump_step(DOWN),
            jump_step(RIGHT),
            jump_step(LEFT),
        },
        //dw ['.FinishFacing'];FinishFacing:
        [STEP_WALK_IN_PLACE] = {
            0x80 | DOWN,
            0x80 | UP,
            0x80 | LEFT,
            0x80 | RIGHT,
        },
        //assert_table_length ['NUM_STEPS']
    };
    static_assert(lengthof(Steps) == NUM_STEPS, "");

    // LD_E_A;
    // LD_D(0);
    // LD_HL(mDoPlayerMovement_Steps);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;

    // LD_A_addr(wWalkingDirection);
    // LD_E_A;
    // CP_A(STANDING);
    // JP_Z (mDoPlayerMovement_StandInPlace);
    if(wram->wWalkingDirection == STANDING)
        return DoPlayerMovement_StandInPlace();

    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wMovementAnimation);
    wram->wMovementAnimation = Steps[a][wram->wWalkingDirection];

    // LD_HL(mDoPlayerMovement_FinishFacing);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wPlayerTurningDirection);
    wram->wPlayerTurningDirection = Steps[STEP_WALK_IN_PLACE][wram->wWalkingDirection];

    // LD_A(PLAYERMOVEMENT_FINISH);
    // RET;
    return PLAYERMOVEMENT_FINISH;
}

static uint8_t DoPlayerMovement_StandInPlace(void) {
    // LD_A(0);
    // LD_addr_A(wPlayerTurningDirection);
    wram->wPlayerTurningDirection = 0;
    // LD_A(movement_step_sleep);
    // LD_addr_A(wMovementAnimation);
    wram->wMovementAnimation = movement_step_sleep;
    // XOR_A_A;
    // RET;
    return 0;
}

static uint8_t DoPlayerMovement_WalkInPlace(void) {
    // LD_A(0);
    // LD_addr_A(wPlayerTurningDirection);
    wram->wPlayerTurningDirection = 0;
    // LD_A(movement_step_bump);
    // LD_addr_A(wMovementAnimation);
    wram->wMovementAnimation = movement_step_bump;
    // XOR_A_A;
    // RET;
    return 0;
}

//  When sliding on ice, input is forced to remain in the same direction.
static void DoPlayerMovement_CheckForced(void) {
    static const uint8_t forced_dpad[] = {
        D_DOWN, D_UP, D_LEFT, D_RIGHT
    };
    //db ['D_DOWN', 'D_UP', 'D_LEFT', 'D_RIGHT'];

    // CALL(aCheckStandingOnIce);
    // RET_NC ;
    if(!CheckStandingOnIce())
        return;

    // LD_A_addr(wPlayerTurningDirection);
    // CP_A(0);
    // RET_Z ;
    if(wram->wPlayerTurningDirection == 0)
        return;

    // maskbits(NUM_DIRECTIONS, 0);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mDoPlayerMovement_forced_dpad);
    // ADD_HL_DE;
    // LD_A_addr(wCurInput);
    // AND_A(BUTTONS);
    // OR_A_hl;
    // LD_addr_A(wCurInput);
    wram->wCurInput = (wram->wCurInput & (BUTTONS)) | forced_dpad[wram->wPlayerTurningDirection & 3];
    // RET;
}

struct PlayerAction {
    int8_t dir;
    uint8_t facing;
    uint8_t xMove;
    uint8_t yMove;
    uint8_t* const ptr;
};

#define player_action(_walk, _face, _x, _y, _ptr) {.dir=_walk, .facing=_face, .xMove=_x, .yMove=_y, .ptr=wram_ptr(_ptr)}
//: MACRO
// ; walk direction, facing, x movement, y movement, tile collision pointer
//     db \1, \2, \3, \4
//     dw \5
// ENDM

//  Poll player input and update movement info.
static void DoPlayerMovement_GetAction(void) {
    static const struct PlayerAction action_table[] = {
    // action_table_1:
        player_action(STANDING, FACE_CURRENT, 0, 0, wPlayerStandingTile),

    // action_table_1_end:
        player_action(RIGHT, FACE_RIGHT, 1, 0, wTileRight),
        player_action(LEFT, FACE_LEFT, -1, 0, wTileLeft),
        player_action(UP, FACE_UP, 0, -1, wTileUp),
        player_action(DOWN, FACE_DOWN, 0, 1, wTileDown),
    };

    // LD_HL(mDoPlayerMovement_action_table);
    // LD_DE(mDoPlayerMovement_action_table_1_end - mDoPlayerMovement_action_table_1);
    // LD_A_addr(wCurInput);
    // BIT_A(D_DOWN_F);
    // IF_NZ goto d_down;
    const struct PlayerAction* hl;
    if(bit_test(wram->wCurInput, D_DOWN_F))
        hl = action_table + 4;
    // BIT_A(D_UP_F);
    // IF_NZ goto d_up;
    else if(bit_test(wram->wCurInput, D_UP_F))
        hl = action_table + 3;
    // BIT_A(D_LEFT_F);
    // IF_NZ goto d_left;
    else if(bit_test(wram->wCurInput, D_LEFT_F))
        hl = action_table + 2;
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto d_right;
    else if(bit_test(wram->wCurInput, D_RIGHT_F))
        hl = action_table + 1;
//  Standing
    else
        hl = action_table;
    // goto update;


// d_down:
    // ADD_HL_DE;

// d_up:
    // ADD_HL_DE;

// d_left:
    // ADD_HL_DE;

// d_right:
    // ADD_HL_DE;

// update:
    // LD_A_hli;
    // LD_addr_A(wWalkingDirection);
    wram->wWalkingDirection = hl->dir;
    // LD_A_hli;
    // LD_addr_A(wFacingDirection);
    wram->wFacingDirection = hl->facing;
    // LD_A_hli;
    // LD_addr_A(wWalkingX);
    wram->wWalkingX = hl->xMove;
    // LD_A_hli;
    // LD_addr_A(wWalkingY);
    wram->wWalkingY = hl->yMove;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_hl;
    // LD_addr_A(wWalkingTile);
    wram->wWalkingTile = *hl->ptr;
    // RET;

// player_action: MACRO
// ; walk direction, facing, x movement, y movement, tile collision pointer
//     db \1, \2, \3, \4
//     dw \5
// ENDM
}

static bool DoPlayerMovement_CheckStrengthBoulder(struct Object* bc) {
    // LD_HL(wBikeFlags);
    // BIT_hl(BIKEFLAGS_STRENGTH_ACTIVE_F);
    // IF_Z goto not_boulder;
    if(!bit_test(gPlayer.bikeFlags, BIKEFLAGS_STRENGTH_ACTIVE_F))
        return false;

    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(STANDING);
    // IF_NZ goto not_boulder;
    if(bc->dirWalking != (uint8_t)STANDING)
        return false;

    // LD_HL(OBJECT_PALETTE);
    // ADD_HL_BC;
    // BIT_hl(STRENGTH_BOULDER_F);
    // IF_Z goto not_boulder;
    if(!bit_test(bc->palette, STRENGTH_BOULDER_F))
        return false;

    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // SET_hl(2);
    bit_set(bc->flags2, 2);

    // LD_A_addr(wWalkingDirection);
    // LD_D_A;
    // LD_HL(OBJECT_RANGE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0b11111100);
    // OR_A_D;
    // LD_hl_A;
    bc->range = (bc->range & 0b11111100) | wram->wWalkingDirection;

    // SCF;
    // RET;
    return true;

// not_boulder:
    // XOR_A_A;
    // RET;
}

//  Return true if walking onto land and tile permissions allow it.
//  Otherwise, return false.
static bool DoPlayerMovement_CheckLandPerms(void) {
    // LD_A_addr(wTilePermissions);
    // LD_D_A;
    // LD_A_addr(wFacingDirection);
    // AND_A_D;
    // IF_NZ goto NotWalkable;
    if(wram->wTilePermissions & wram->wFacingDirection)
        return false;

    // LD_A_addr(wWalkingTile);
    // CALL(aDoPlayerMovement_CheckWalkable);
    // IF_C return false;
    return DoPlayerMovement_CheckWalkable(wram->wWalkingTile);

    // XOR_A_A;
    // RET;

// NotWalkable:
    // SCF;
    // RET;
}

//  Return true if tile a is land. Otherwise, return false.
static bool DoPlayerMovement_CheckWalkable(uint8_t a) {
    // CALL(aGetTileCollision);
    // AND_A_A;  // LAND_TILE
    // RET_Z ;
    // SCF;
    // RET;
    return GetTileCollision(a) == LAND_TILE;
}

static bool DoPlayerMovement_BumpSound(void) {
    // CALL(aCheckSFX);
    // RET_C ;
    if(CheckSFX())
        return false;
    // LD_DE(SFX_BUMP);
    // CALL(aPlaySFX);
    PlaySFX(SFX_BUMP);
    // RET;
    return true;
}

static void DoPlayerMovement_GetOutOfWater(void) {
    // PUSH_BC;
    // LD_A(PLAYER_NORMAL);
    // LD_addr_A(wPlayerState);
    gPlayer.playerState = PLAYER_NORMAL;
    // CALL(aUpdatePlayerSprite);  // UpdateSprites
    UpdatePlayerSprite();
    // POP_BC;
    // RET;
}

uint8_t DoPlayerMovement(void){
    // CALL(aDoPlayerMovement_GetDPad);
    DoPlayerMovement_GetDPad();
    // LD_A(movement_step_sleep);
    // LD_addr_A(wMovementAnimation);
    wram->wMovementAnimation = movement_step_sleep;
    // XOR_A_A;
    // LD_addr_A(wWalkingIntoEdgeWarp);
    wram->wWalkingIntoEdgeWarp = 0;
    // CALL(aDoPlayerMovement_TranslateIntoMovement);
    // LD_C_A;
    uint8_t c = DoPlayerMovement_TranslateIntoMovement();
    // LD_A_addr(wMovementAnimation);
    // LD_addr_A(wPlayerNextMovement);
    wram->wPlayerNextMovement = wram->wMovementAnimation;
    // RET;
    return c;
}

bool CheckStandingOnIce(void){
    // LD_A_addr(wPlayerTurningDirection);
    // CP_A(0);
    // IF_Z goto not_ice;
    // CP_A(0xf0);
    // IF_Z goto not_ice;
    if(wram->wPlayerTurningDirection == 0 || wram->wPlayerTurningDirection == 0xf0)
        return false;
    // LD_A_addr(wPlayerStandingTile);
    // CALL(aCheckIceTile);
    // IF_NC goto yep;
    if(CheckIceTile(gPlayer.playerStruct.nextTile))
        return true;
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_SKATE);
    // IF_NZ goto not_ice;
    if(gPlayer.playerState != PLAYER_SKATE)
        return false;

// yep:
    // SCF;
    // RET;
    return true;

// not_ice:
    // AND_A_A;
    // RET;
}

void StopPlayerForEvent(void){
    // LD_HL(wPlayerNextMovement);
    // LD_A(movement_step_sleep);
    // CP_A_hl;
    // RET_Z ;
    if(wram->wPlayerNextMovement != movement_step_sleep) {
        // LD_hl_A;
        wram->wPlayerNextMovement = movement_step_sleep;
        // LD_A(0);
        // LD_addr_A(wPlayerTurningDirection);
        wram->wPlayerTurningDirection = 0;
    }
    // RET;
}
