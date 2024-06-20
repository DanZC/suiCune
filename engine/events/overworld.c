#include "../../constants.h"
#include "overworld.h"
#include "engine_flags.h"
#include "field_moves.h"
#include "fishing_gfx.h"
#include "unown_walls.h"
#include "misc_scripts.h"
#include "treemons.h"
#include "fish.h"
#include "../overworld/map_setup.h"
#include "../overworld/map_objects.h"
#include "../overworld/npc_movement.h"
#include "../overworld/tile_events.h"
#include "../gfx/load_overworld_font.h"
#include "../../home/audio.h"
#include "../../home/copy.h"
#include "../../home/copy_name.h"
#include "../../home/clear_sprites.h"
#include "../../home/array.h"
#include "../../home/delay.h"
#include "../../home/map.h"
#include "../../home/map_objects.h"
#include "../../home/menu.h"
#include "../../home/gfx.h"
#include "../../home/pokemon.h"
#include "../../home/queue_script.h"
#include "../../home/tilemap.h"
#include "../../data/text/common.h"
#include "../../data/collision/field_move_blocks.h"
#include "../../util/scripting.h"

// field move data
static struct FieldMoveData {
    //union wFieldMoveData
    uint8_t jumptableIndex;
    union {
        uint8_t escapeRopeOrDigType;
        uint8_t surfingPlayerState;
        uint8_t fishingRodUsed;
    };
    tile_t* cutWhirlpoolOverworldBlockAddr;
    uint8_t cutWhirlpoolReplacementBlock;
    union {
        uint8_t cutWhirlpoolAnimationType;
        species_t strengthSpecies;
        uint8_t fishingResult;
    };
} sFieldMoveData;

struct OverworldTileRes {
    uint8_t b;
    uint8_t c;
    bool flag;
};

struct OverworldTileRes CheckOverworldTileArrays_Conv(const struct BlockPointer* hl, tile_t c);

void FieldMoveJumptableReset(void){
    // XOR_A_A;
    // LD_HL(wFieldMoveData);
    // LD_BC(wFieldMoveDataEnd - wFieldMoveData);
    // CALL(aByteFill);
    ByteFill_Conv2(&sFieldMoveData, sizeof(sFieldMoveData), 0);
    // RET;
}

void FieldMoveJumptable(void){
    LD_A_addr(wFieldMoveJumptableIndex);
    RST(aJumpTable);
    LD_addr_A(wFieldMoveJumptableIndex);
    BIT_A(7);
    IF_NZ goto okay;
    AND_A_A;
    RET;


okay:
    AND_A(0x7f);
    SCF;
    RET;

}

typedef uint8_t (*field_move_fn_t)(void);

u8_flag_s FieldMoveJumptable_Conv(const field_move_fn_t jumptable[]){
    // LD_A_addr(wFieldMoveJumptableIndex);
    // RST(aJumpTable);
    // LD_addr_A(wFieldMoveJumptableIndex);
    sFieldMoveData.jumptableIndex = jumptable[sFieldMoveData.jumptableIndex]();
    // BIT_A(7);
    // IF_NZ goto okay;
    if(bit_test(sFieldMoveData.jumptableIndex, 7)) {
    // okay:
        // AND_A(0x7f);
        // SCF;
        // RET;
        return u8_flag(sFieldMoveData.jumptableIndex & 0x7f, true);
    }
    // AND_A_A;
    // RET;
    return u8_flag(sFieldMoveData.jumptableIndex, false);
}

void GetPartyNickname(void){
//  write wCurPartyMon nickname to wStringBuffer1-3
    // LD_HL(wPartyMonNicknames);
    // LD_A(BOXMON);
    // LD_addr_A(wMonType);
    wram->wMonType = BOXMON;
    // LD_A_addr(wCurPartyMon);
    // CALL(aGetNickname);
    // CALL(aCopyName1);
    CopyName1_Conv2(wram->wPartyMonNickname[wram->wCurPartyMon]);
//  copy text from wStringBuffer2 to wStringBuffer3
    // LD_DE(wStringBuffer2);
    // LD_HL(wStringBuffer3);
    // CALL(aCopyName2);
    CopyName2_Conv2(wram->wStringBuffer3, wram->wStringBuffer2);
    // RET;
}

void CheckEngineFlag(void){
//  Check engine flag de
//  Return carry if flag is not set
    LD_B(CHECK_FLAG);
    FARCALL(aEngineFlagAction);
    LD_A_C;
    AND_A_A;
    IF_NZ goto isset;
    SCF;
    RET;

isset:
    XOR_A_A;
    RET;

}

//  Check engine flag de
//  Return carry (false) if flag is not set
bool CheckEngineFlag_Conv(uint16_t de){
    // LD_B(CHECK_FLAG);
    // FARCALL(aEngineFlagAction);
    bool isset = EngineFlagAction_Conv(de, CHECK_FLAG);
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto isset;
    // SCF;
    // RET;

// isset:
    // XOR_A_A;
    // RET;
    return isset;
}

void CheckBadge(void){
//  Check engine flag a (ENGINE_ZEPHYRBADGE thru ENGINE_EARTHBADGE)
//  Display "Badge required" text and return carry if the badge is not owned
    CALL(aCheckEngineFlag);
    RET_NC ;
    LD_HL(mCheckBadge_BadgeRequiredText);
    CALL(aMenuTextboxBackup);  // push text to queue
    SCF;
    RET;


BadgeRequiredText:
    //text_far ['_BadgeRequiredText']
    //text_end ['?']

    return CheckPartyMove();
}

//  Check engine flag a (ENGINE_ZEPHYRBADGE thru ENGINE_EARTHBADGE)
//  Display "Badge required" text and return carry if the badge is not owned
bool CheckBadge_Conv(uint16_t de){
    // CALL(aCheckEngineFlag);
    // RET_NC ;
    if(CheckEngineFlag_Conv(de))
        return true;
    // LD_HL(mCheckBadge_BadgeRequiredText);
    // CALL(aMenuTextboxBackup);  // push text to queue
    MenuTextboxBackup_Conv((struct TextCmd[]) {
        text_far(v_BadgeRequiredText)
        text_end
    });
    // SCF;
    // RET;
    return false;

// BadgeRequiredText:
    // return CheckPartyMove();
}

void CheckPartyMove(void){
//  Check if a monster in your party has move d.

    LD_E(0);
    XOR_A_A;
    LD_addr_A(wCurPartyMon);

loop:
    LD_C_E;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto no;
    CP_A(-1);
    IF_Z goto no;
    CP_A(EGG);
    IF_Z goto next;

    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1Moves);
    LD_A_E;
    CALL(aAddNTimes);
    LD_B(NUM_MOVES);

check:
    LD_A_hli;
    CP_A_D;
    IF_Z goto yes;
    DEC_B;
    IF_NZ goto check;


next:
    INC_E;
    goto loop;


yes:
    LD_A_E;
    LD_addr_A(wCurPartyMon);  // which mon has the move
    XOR_A_A;
    RET;

no:
    SCF;
    RET;

}

//  Check if a monster in your party has move d.
//  Returns carry (false) if no monster has the move.
bool CheckPartyMove_Conv(move_t d){
    // LD_E(0);
    uint8_t e;
    // XOR_A_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = 0;

    for(e = 0; e < wram->wPartyCount; e++) {
    // loop:
        // LD_C_E;
        // LD_B(0);
        // LD_HL(wPartySpecies);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto no;
        // CP_A(-1);
        // IF_Z goto no;
        if(wram->wPartySpecies[e] == 0 || wram->wPartySpecies[e] == 0xff)
            return false;
        // CP_A(EGG);
        // IF_Z goto next;
        if(wram->wPartySpecies[e] == EGG)
            continue;

        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_HL(wPartyMon1Moves);
        // LD_A_E;
        // CALL(aAddNTimes);
        // LD_B(NUM_MOVES);

        for(uint8_t b = 0; b < NUM_MOVES && wram->wPartyMon[e].mon.moves[b] != NO_MOVE; ++b) {
        // check:
            // LD_A_hli;
            // CP_A_D;
            // IF_Z goto yes;
            if(wram->wPartyMon[e].mon.moves[b] == d) {
            // yes:
                // LD_A_E;
                // LD_addr_A(wCurPartyMon);  // which mon has the move
                wram->wCurPartyMon = e;
                // XOR_A_A;
                // RET;
                return true;
            }
            // DEC_B;
            // IF_NZ goto check;
        }


    // next:
        // INC_E;
        // goto loop;
    }
    return false;

// no:
    // SCF;
    // RET;
}

void FieldMoveFailed(void){
    // LD_HL(mFieldMoveFailed_CantUseItemText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv((struct TextCmd[]) {
        text_far(v_CantUseItemText)
        text_end
    });
    // RET;

// CantUseItemText:
    //text_far ['_CantUseItemText']
    //text_end ['?']
}

static uint8_t CutFunction_CheckAble(void) {
    // LD_DE(ENGINE_HIVEBADGE);
    // CALL(aCheckBadge);
    // IF_C goto nohivebadge;
    if(!CheckBadge_Conv(ENGINE_HIVEBADGE)) {
    // nohivebadge:
        // LD_A(0x80);
        // RET;
        return 0x80;
    }
    // CALL(aCheckMapForSomethingToCut);
    // IF_C goto nothingtocut;
    if(!CheckMapForSomethingToCut_Conv()) {
    // nothingtocut:
        // LD_A(0x2);
        // RET;
        return 0x2;
    }
    // LD_A(0x1);
    // RET;
    return 0x1;
}


static uint8_t CutFunction_DoCut(void) {
    // LD_HL(mScript_CutFromMenu);
    // CALL(aQueueScript);
    QueueScript_Conv2(Script_CutFromMenu);
    // LD_A(0x81);
    // RET;
    return 0x81;
}

static uint8_t CutFunction_FailCut(void) {
    // LD_HL(mCutNothingText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(CutNothingText);
    // LD_A(0x80);
    // RET;
    return 0x80;
}

void CutFunction(void){
    static const field_move_fn_t Jumptable[] = {
        CutFunction_CheckAble,
        CutFunction_DoCut,
        CutFunction_FailCut,
    };
    // CALL(aFieldMoveJumptableReset);
    FieldMoveJumptableReset();

    u8_flag_s res;
    do {
    // loop:
        // LD_HL(mCutFunction_Jumptable);
        // CALL(aFieldMoveJumptable);
        res = FieldMoveJumptable_Conv(Jumptable);
        // IF_NC goto loop;
    } while(!res.flag);
    // AND_A(0x7f);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = res.a & 0x7f;
    // RET;
    return;
}

const txt_cmd_s UseCutText[] = {
    text_far(v_UseCutText)
    text_end
};

const txt_cmd_s CutNothingText[] = {
    text_far(v_CutNothingText)
    text_end
};

void CheckMapForSomethingToCut(void){
// Does the collision data of the facing tile permit cutting?
    CALL(aGetFacingTileCoord);
    LD_C_A;
    PUSH_DE;
    FARCALL(aCheckCutCollision);
    POP_DE;
    IF_NC goto fail;
// Get the location of the current block in wOverworldMapBlocks.
    CALL(aGetBlockLocation);
    LD_C_hl;
// See if that block contains something that can be cut.
    PUSH_HL;
    LD_HL(mCutTreeBlockPointers);
    CALL(aCheckOverworldTileArrays);
    POP_HL;
    IF_NC goto fail;
// Save the Cut field move data
    LD_A_L;
    LD_addr_A(wCutWhirlpoolOverworldBlockAddr);
    LD_A_H;
    LD_addr_A(wCutWhirlpoolOverworldBlockAddr + 1);
    LD_A_B;
    LD_addr_A(wCutWhirlpoolReplacementBlock);
    LD_A_C;
    LD_addr_A(wCutWhirlpoolAnimationType);
    XOR_A_A;
    RET;


fail:
    SCF;
    RET;

}

bool CheckMapForSomethingToCut_Conv(void){
// Does the collision data of the facing tile permit cutting?
    // CALL(aGetFacingTileCoord);
    struct CoordsTileId cid = GetFacingTileCoord_Conv();
    // LD_C_A;
    // PUSH_DE;
    // FARCALL(aCheckCutCollision);
    // POP_DE;
    // IF_NC goto fail;
    if(!CheckCutCollision_Conv(cid.tileId))
        return false;
// Get the location of the current block in wOverworldMapBlocks.
    // CALL(aGetBlockLocation);
    // LD_C_hl;
    uint8_t* hl = GetBlockLocation_Conv((uint8_t)cid.x, (uint8_t)cid.y);
// See if that block contains something that can be cut.
    // PUSH_HL;
    // LD_HL(mCutTreeBlockPointers);
    // CALL(aCheckOverworldTileArrays);
    struct OverworldTileRes res = CheckOverworldTileArrays_Conv(CutTreeBlockPointers, *hl);
    // POP_HL;
    // IF_NC goto fail;
    if(!res.flag)
        return false;
// Save the Cut field move data
    // LD_A_L;
    // LD_addr_A(wCutWhirlpoolOverworldBlockAddr);
    // LD_A_H;
    // LD_addr_A(wCutWhirlpoolOverworldBlockAddr + 1);
    sFieldMoveData.cutWhirlpoolOverworldBlockAddr = hl;
    // LD_A_B;
    // LD_addr_A(wCutWhirlpoolReplacementBlock);
    sFieldMoveData.cutWhirlpoolReplacementBlock = res.b;
    // LD_A_C;
    // LD_addr_A(wCutWhirlpoolAnimationType);
    sFieldMoveData.cutWhirlpoolAnimationType = res.c;
    // XOR_A_A;
    // RET;
    return true;

// fail:
    // SCF;
    // RET;
}

bool Script_CutFromMenu(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)
    SCRIPT_FALLTHROUGH(Script_Cut)
}

bool Script_Cut(script_s* s){
    SCRIPT_BEGIN
    GetPartyNickname();
    writetext(UseCutText)
    reloadmappart
    CutDownTreeOrGrass();
    closetext
    s_end
    SCRIPT_END
}

void CutDownTreeOrGrass(void){
    // LD_HL(wCutWhirlpoolOverworldBlockAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wCutWhirlpoolReplacementBlock);
    // LD_hl_A;
    *sFieldMoveData.cutWhirlpoolOverworldBlockAddr = sFieldMoveData.cutWhirlpoolReplacementBlock;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A_addr(wCutWhirlpoolAnimationType);
    // LD_E_A;
    // FARCALL(aOWCutAnimation);
    OWCutAnimation_Conv(sFieldMoveData.cutWhirlpoolAnimationType);
    // CALL(aBufferScreen);
    BufferScreen_Conv();
    // CALL(aGetMovementPermissions);
    GetMovementPermissions();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // RET;
}

void CheckOverworldTileArrays(void){
// Input: c contains the tile you're facing
// Output: Replacement tile in b and effect on wild encounters in c, plus carry set.
//         Carry is not set if the facing tile cannot be replaced, or if the tileset
//         does not contain a tile you can replace.

// Dictionary lookup for pointer to tile replacement table
    PUSH_BC;
    LD_A_addr(wMapTileset);
    LD_DE(3);
    CALL(aIsInArray);
    POP_BC;
    IF_NC goto nope;
// Load the pointer
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
// Look up the tile you're facing
    LD_DE(3);
    LD_A_C;
    CALL(aIsInArray);
    IF_NC goto nope;
// Load the replacement to b
    INC_HL;
    LD_B_hl;
// Load the animation type parameter to c
    INC_HL;
    LD_C_hl;
    SCF;
    RET;


nope:
    XOR_A_A;
    RET;

// INCLUDE "data/collision/field_move_blocks.asm"

    return FlashFunction();
}

// Input: c contains the tile you're facing
// Output: Replacement tile in b and effect on wild encounters in c, plus carry set.
//         Carry is not set if the facing tile cannot be replaced, or if the tileset
//         does not contain a tile you can replace.
struct OverworldTileRes CheckOverworldTileArrays_Conv(const struct BlockPointer* hl, tile_t c){
// Dictionary lookup for pointer to tile replacement table
    // PUSH_BC;
    // LD_A_addr(wMapTileset);
    // LD_DE(3);
    // CALL(aIsInArray);
    const struct BlockPointer* found = ArrayFindStructBlockPointer(hl, wram->wMapTileset);
    // POP_BC;
    // IF_NC goto nope;
    if(!found)
        return (struct OverworldTileRes){.flag = false};
// Load the pointer
    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
// Look up the tile you're facing
    // LD_DE(3);
    // LD_A_C;
    // CALL(aIsInArray);
    // IF_NC goto nope;
    for(uint32_t i = 0; found->list[i] != 0xff; i += 3) {
        if(found->list[i] == c) {
        // Load the replacement to b
            // INC_HL;
            // LD_B_hl;
        // Load the animation type parameter to c
            // INC_HL;
            // LD_C_hl;
            // SCF;
            // RET;
            return (struct OverworldTileRes){.b = found->list[i+1], .c = found->list[i+2], .flag = true};
        }
    }


// nope:
    // XOR_A_A;
    // RET;
    return (struct OverworldTileRes){.flag = false};
// INCLUDE "data/collision/field_move_blocks.asm"
}

static uint8_t FlashFunction_CheckUseFlash(void) {
//  Flash
    // LD_DE(ENGINE_ZEPHYRBADGE);
    // FARCALL(aCheckBadge);
    // IF_C goto nozephyrbadge;
    if(!CheckBadge_Conv(ENGINE_ZEPHYRBADGE)) {
    // nozephyrbadge:
        // LD_A(0x80);
        // RET;
        return 0x80;
    }
    // PUSH_HL;
    // FARCALL(aSpecialAerodactylChamber);
    // POP_HL;
    // IF_C goto useflash;
    if(!SpecialAerodactylChamber_Conv() && wram->wTimeOfDayPalset != DARKNESS_PALSET) {
        // LD_A_addr(wTimeOfDayPalset);
        // CP_A(DARKNESS_PALSET);
        // IF_NZ goto notadarkcave;
    // notadarkcave:
        // CALL(aFieldMoveFailed);
        FieldMoveFailed();
        // LD_A(0x80);
        // RET;
        return 0x80;
    }

// useflash:
    // CALL(aUseFlash);
    UseFlash();
    // LD_A(0x81);
    // RET;
    return 0x81;
}

void FlashFunction(void){
    // CALL(aFlashFunction_CheckUseFlash);
    // AND_A(0x7f);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = FlashFunction_CheckUseFlash() & 0x7f;
    // RET;
}

void UseFlash(void){
    // LD_HL(mScript_UseFlash);
    // JP(mQueueScript);
    QueueScript_Conv2(Script_UseFlash);
}

bool Script_UseFlash(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)
    writetext((struct TextCmd[]) {
        text_far(v_BlindingFlashText)
        text_asm(UseFlashTextScript)
    })
    BlindingFlash();
    closetext
    s_end
    SCRIPT_END
}

void UseFlashTextScript(struct TextCmdState* state){
    (void)state;
    static const txt_cmd_s BlankText[] = {
        text_end
    };
    //text_far ['_BlindingFlashText']
    //text_asm ['?']
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_DE(SFX_FLASH);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_FLASH);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_HL(mUseFlashTextScript_BlankText);
    state->hl = BlankText;
    // RET;
}

static uint8_t SurfFunction_TrySurf(void) {
    // LD_DE(ENGINE_FOGBADGE);
    // CALL(aCheckBadge);
    // IF_C goto nofogbadge;
    if(!CheckBadge_Conv(ENGINE_FOGBADGE)) {
    // nofogbadge:
        // LD_A(0x80);
        // RET;
        return 0x80;
    }
    // LD_HL(wBikeFlags);
    // BIT_hl(BIKEFLAGS_ALWAYS_ON_BIKE_F);
    // IF_NZ goto cannotsurf;
    if(bit_test(wram->wBikeFlags, BIKEFLAGS_ALWAYS_ON_BIKE_F)) {
    // cannotsurf:
        // LD_A(0x2);
        // RET;
        return 0x2;
    }
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_SURF);
    // IF_Z goto alreadyfail;
    // CP_A(PLAYER_SURF_PIKA);
    // IF_Z goto alreadyfail;
    if(wram->wPlayerState == PLAYER_SURF || wram->wPlayerState == PLAYER_SURF_PIKA) {
    // alreadyfail:
        // LD_A(0x3);
        // RET;
        return 0x3;
    }
    // CALL(aGetFacingTileCoord);
    // CALL(aGetTileCollision);
    uint8_t col = GetTileCollision_Conv(GetFacingTileCoord_Conv().tileId);
    // CP_A(WATER_TILE);
    // IF_NZ goto cannotsurf;
    // CALL(aCheckDirection);
    // IF_C goto cannotsurf;
    // FARCALL(aCheckFacingObject);
    // IF_C goto cannotsurf;
    if(col == WATER_TILE && !CheckDirection_Conv() && CheckFacingObject_Conv() == NULL) {
        // LD_A(0x1);
        // RET;
        return 0x1;
    }
    return 0x2;
}

static uint8_t SurfFunction_DoSurf(void) {
    // CALL(aGetSurfType);
    // LD_addr_A(wSurfingPlayerState);
    wram->wSurfingPlayerState = GetSurfType_Conv();
    // CALL(aGetPartyNickname);
    GetPartyNickname();
    // LD_HL(mSurfFromMenuScript);
    // CALL(aQueueScript);
    QueueScript_Conv2(SurfFromMenuScript);
    // LD_A(0x81);
    // RET;
    return 0x81;
}

static uint8_t SurfFunction_FailSurf(void) {
    // LD_HL(mCantSurfText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(CantSurfText);
    // LD_A(0x80);
    // RET;
    return 0x80;
}

static uint8_t SurfFunction_AlreadySurfing(void) {
    // LD_HL(mAlreadySurfingText);
    // CALL(aMenuTextboxBackup);
    MenuTextboxBackup_Conv(AlreadySurfingText);
    // LD_A(0x80);
    // RET;
    return 0x80;
}

void SurfFunction(void){
    static const field_move_fn_t Jumptable[] = {
        SurfFunction_TrySurf,
        SurfFunction_DoSurf,
        SurfFunction_FailSurf,
        SurfFunction_AlreadySurfing,
    };
    // CALL(aFieldMoveJumptableReset);
    FieldMoveJumptableReset();

    u8_flag_s res;
    do {
    // loop:
        // LD_HL(mSurfFunction_Jumptable);
        // CALL(aFieldMoveJumptable);
        res = FieldMoveJumptable_Conv(Jumptable);
        // IF_NC goto loop;
    } while(!res.flag);
    // AND_A(0x7f);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = res.a & 0x7f;
    // RET;
}

bool SurfFromMenuScript(script_s* s){
    SCRIPT_BEGIN
    special(UpdateTimePals)

    SCRIPT_FALLTHROUGH(UsedSurfScript)
}

static void UsedSurfScript_stubbed_fn(void) {
    // FARCALL(aStubbedTrainerRankings_Surf);
    // RET;
}

bool UsedSurfScript(script_s* s){
    SCRIPT_BEGIN
    writetext(UsedSurfText)  // "used SURF!"
    waitbutton
    closetext

    UsedSurfScript_stubbed_fn();

    readmem(wram_ptr(wSurfingPlayerState))
    writevar(VAR_MOVEMENT)

    special(UpdatePlayerSprite)
    special(PlayMapMusic)
//  step into the water (slow_step DIR, step_end)
    special(SurfStartStep)
    applymovement(PLAYER, wram->wMovementBuffer)
    s_end
    SCRIPT_END

}

const txt_cmd_s UsedSurfText[] = {
    text_far(v_UsedSurfText)
    text_end
};

const txt_cmd_s CantSurfText[] = {
    text_far(v_CantSurfText)
    text_end
};

const txt_cmd_s AlreadySurfingText[] = {
    text_far(v_AlreadySurfingText)
    text_end
};

void GetSurfType(void){
//  Surfing on Pikachu uses an alternate sprite.
//  This is done by using a separate movement type.

    LD_A_addr(wCurPartyMon);
    LD_E_A;
    LD_D(0);
    LD_HL(wPartySpecies);
    ADD_HL_DE;

    LD_A_hl;
    CP_A(PIKACHU);
    LD_A(PLAYER_SURF_PIKA);
    RET_Z ;
    LD_A(PLAYER_SURF);
    RET;

}

//  Surfing on Pikachu uses an alternate sprite.
//  This is done by using a separate movement type.
uint8_t GetSurfType_Conv(void){
    // LD_A_addr(wCurPartyMon);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPartySpecies);
    // ADD_HL_DE;

    species_t sp = wram->wPartySpecies[wram->wCurPartyMon];
    // LD_A_hl;
    // CP_A(PIKACHU);
    // LD_A(PLAYER_SURF_PIKA);
    // RET_Z ;
    // LD_A(PLAYER_SURF);
    // RET;
    return (sp == PIKACHU)? PLAYER_SURF_PIKA: PLAYER_SURF;
}

void CheckDirection(void){
//  Return carry if a tile permission prevents you
//  from moving in the direction you're facing.

//  Get player direction
    LD_A_addr(wPlayerDirection);
    AND_A(0b00001100);  // bits 2 and 3 contain direction
    RRCA;
    RRCA;
    LD_E_A;
    LD_D(0);
    LD_HL(mCheckDirection_Directions);
    ADD_HL_DE;

//  Can you walk in this direction?
    LD_A_addr(wTilePermissions);
    AND_A_hl;
    IF_NZ goto quit;
    XOR_A_A;
    RET;


quit:
    SCF;
    RET;


Directions:
    //db ['FACE_DOWN'];
    //db ['FACE_UP'];
    //db ['FACE_LEFT'];
    //db ['FACE_RIGHT'];

    return TrySurfOW();
}

bool CheckDirection_Conv(void){
    const uint8_t Directions[] = {
        FACE_DOWN,
        FACE_UP,
        FACE_LEFT,
        FACE_RIGHT,
    };
//  Return carry if a tile permission prevents you
//  from moving in the direction you're facing.

//  Get player direction
    // LD_A_addr(wPlayerDirection);
    // AND_A(0b00001100);  // bits 2 and 3 contain direction
    // RRCA;
    // RRCA;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mCheckDirection_Directions);
    // ADD_HL_DE;
    uint8_t dir = Directions[(wram->wPlayerStruct.facing & 0b00001100) >> 2];

//  Can you walk in this direction?
    // LD_A_addr(wTilePermissions);
    // AND_A_hl;
    // IF_NZ goto quit;
    if((wram->wTilePermissions & dir) == 0) {
        // XOR_A_A;
        // RET;
        return false;
    }

// quit:
    // SCF;
    // RET;
    return true;
}

void TrySurfOW(void){
//  Checking a tile in the overworld.
//  Return carry if fail is allowed.

//  Don't ask to surf if already fail.
    LD_A_addr(wPlayerState);
    CP_A(PLAYER_SURF_PIKA);
    IF_Z goto quit;
    CP_A(PLAYER_SURF);
    IF_Z goto quit;

//  Must be facing water.
    LD_A_addr(wFacingTileID);
    CALL(aGetTileCollision);
    CP_A(WATER_TILE);
    IF_NZ goto quit;

//  Check tile permissions.
    CALL(aCheckDirection);
    IF_C goto quit;

    LD_DE(ENGINE_FOGBADGE);
    CALL(aCheckEngineFlag);
    IF_C goto quit;

    LD_D(SURF);
    CALL(aCheckPartyMove);
    IF_C goto quit;

    LD_HL(wBikeFlags);
    BIT_hl(BIKEFLAGS_ALWAYS_ON_BIKE_F);
    IF_NZ goto quit;

    CALL(aGetSurfType);
    LD_addr_A(wSurfingPlayerState);
    CALL(aGetPartyNickname);

    LD_A(BANK(aAskSurfScript));
    LD_HL(mAskSurfScript);
    CALL(aCallScript);

    SCF;
    RET;


quit:
    XOR_A_A;
    RET;

}

//  Checking a tile in the overworld.
//  Return carry if fail is allowed.
bool TrySurfOW_Conv(void){
//  Don't ask to surf if already fail.
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_SURF_PIKA);
    // IF_Z goto quit;
    // CP_A(PLAYER_SURF);
    // IF_Z goto quit;
    if(wram->wPlayerState == PLAYER_SURF_PIKA || wram->wPlayerState == PLAYER_SURF)
        return false;

//  Must be facing water.
    // LD_A_addr(wFacingTileID);
    // CALL(aGetTileCollision);
    // CP_A(WATER_TILE);
    // IF_NZ goto quit;
    if(GetTileCollision_Conv(wram->wFacingTileID) != WATER_TILE)
        return false;

//  Check tile permissions.
    // CALL(aCheckDirection);
    // IF_C goto quit;
    if(CheckDirection_Conv())
        return false;

    // LD_DE(ENGINE_FOGBADGE);
    // CALL(aCheckEngineFlag);
    // IF_C goto quit;
    if(!CheckEngineFlag_Conv(ENGINE_FOGBADGE))
        return false;

    // LD_D(SURF);
    // CALL(aCheckPartyMove);
    // IF_C goto quit;
    if(!CheckPartyMove_Conv(SURF))
        return false;

    // LD_HL(wBikeFlags);
    // BIT_hl(BIKEFLAGS_ALWAYS_ON_BIKE_F);
    // IF_NZ goto quit;
    if(bit_test(wram->wBikeFlags, BIKEFLAGS_ALWAYS_ON_BIKE_F))
        return false;

    // CALL(aGetSurfType);
    // LD_addr_A(wSurfingPlayerState);
    wram->wSurfingPlayerState = GetSurfType_Conv();
    // CALL(aGetPartyNickname);
    GetPartyNickname();

    // LD_A(BANK(aAskSurfScript));
    // LD_HL(mAskSurfScript);
    // CALL(aCallScript);
    CallScript_Conv2(AskSurfScript);

    // SCF;
    // RET;
    return true;

// quit:
    // XOR_A_A;
    // RET;
}

bool AskSurfScript(script_s* s){
    SCRIPT_BEGIN
    opentext
    writetext(AskSurfText)
    yesorno
    iftrue_jump(UsedSurfScript)
    closetext
    s_end
    SCRIPT_END
}

const txt_cmd_s AskSurfText[] = {
    text_far(v_AskSurfText)
    text_end
};

static uint8_t FlyFunction_TryFly(void) {
//  Fly
    // LD_DE(ENGINE_STORMBADGE);
    // CALL(aCheckBadge);
    // IF_C goto nostormbadge;
    if(CheckBadge_Conv(ENGINE_STORMBADGE)) {
    // nostormbadge:
        // LD_A(0x82);
        // RET;
        return 0x82;
    }
    // CALL(aGetMapEnvironment);
    // CALL(aCheckOutdoorMap);
    // IF_Z goto outdoors;
    if(CheckOutdoorMap_Conv(GetMapEnvironment_Conv2())) {
    // outdoors:
        // XOR_A_A;
        // LDH_addr_A(hMapAnims);
        hram->hMapAnims = 0;
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader_Conv();
        // CALL(aClearSprites);
        ClearSprites_Conv();
        // FARCALL(av_FlyMap);
        struct cpu_registers_s regs = SafeCallGBAutoRet(av_FlyMap);
        // LD_A_E;
        // CP_A(-1);
        // IF_Z goto illegal;
        // CP_A(NUM_SPAWNS);
        // IF_NC goto illegal;
        if(regs.e == 0xff || regs.e >= NUM_SPAWNS) {
        // illegal:
            // CALL(aCloseWindow);
            CloseWindow_Conv2();
            // CALL(aWaitBGMap);
            WaitBGMap_Conv();
            // LD_A(0x80);
            // RET;
            return 0x80;
        }

        // LD_addr_A(wDefaultSpawnpoint);
        wram->wDefaultSpawnpoint = regs.e;
        // CALL(aCloseWindow);
        CloseWindow_Conv2();
        // LD_A(0x1);
        // RET;
        return 0x1;
    }
    // goto indoors;

// indoors:
    // LD_A(0x2);
    // RET;
    return 0x2;
}

static bool FlyFunction_FlyScript(script_s* s) {
    SCRIPT_BEGIN
    reloadmappart
    HideSprites_Conv();
    special(UpdateTimePals)
    FlyFromAnim();
    scall(Script_AbortBugContest)
    special(WarpToSpawnPoint)
    SkipUpdateMapSprites();
    loadvar(VAR_MOVEMENT, PLAYER_NORMAL)
    newloadmap(MAPSETUP_FLY)
    FlyToAnim();
    special(WaitSFX)
    //callasm ['.ReturnFromFly']
    {
    // ReturnFromFly:
        // FARCALL(aRespawnPlayer);
        RespawnPlayer_Conv();
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aUpdatePlayerSprite);
        UpdatePlayerSprite_Conv();
        // FARCALL(aLoadOverworldFont);
        LoadOverworldFont_Conv();
        // RET;
    }
    s_end
    SCRIPT_END
}

static uint8_t FlyFunction_DoFly(void) {
    // LD_HL(mFlyFunction_FlyScript);
    // CALL(aQueueScript);
    QueueScript_Conv2(FlyFunction_FlyScript);
    // LD_A(0x81);
    // RET;
    return 0x81;
}

static uint8_t FlyFunction_FailFly(void) {
    // CALL(aFieldMoveFailed);
    FieldMoveFailed();
    // LD_A(0x82);
    // RET;
    return 0x82;
}

void FlyFunction(void){
    const field_move_fn_t Jumptable[] = {
        FlyFunction_TryFly,
        FlyFunction_DoFly,
        FlyFunction_FailFly,
    };
    // CALL(aFieldMoveJumptableReset);
    FieldMoveJumptableReset();

    u8_flag_s res;
    do {
    // loop:
        // LD_HL(mFlyFunction_Jumptable);
        // CALL(aFieldMoveJumptable);
        res = FieldMoveJumptable_Conv(Jumptable);
        // IF_NC goto loop;
    } while(!res.flag);
    // AND_A(0x7f);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = res.a & 0x7f;
    // RET;
    return;
}

void WaterfallFunction(void){
    CALL(aWaterfallFunction_TryWaterfall);
    AND_A(0x7f);
    LD_addr_A(wFieldMoveSucceeded);
    RET;


TryWaterfall:
//  Waterfall
    LD_DE(ENGINE_RISINGBADGE);
    FARCALL(aCheckBadge);
    LD_A(0x80);
    RET_C ;
    CALL(aCheckMapCanWaterfall);
    IF_C goto failed;
    LD_HL(mScript_WaterfallFromMenu);
    CALL(aQueueScript);
    LD_A(0x81);
    RET;


failed:
    CALL(aFieldMoveFailed);
    LD_A(0x80);
    RET;

}

void CheckMapCanWaterfall(void){
    LD_A_addr(wPlayerDirection);
    AND_A(0xc);
    CP_A(FACE_UP);
    IF_NZ goto failed;
    LD_A_addr(wTileUp);
    CALL(aCheckWaterfallTile);
    IF_NZ goto failed;
    XOR_A_A;
    RET;


failed:
    SCF;
    RET;

}

bool CheckMapCanWaterfall_Conv(void){
    // LD_A_addr(wPlayerDirection);
    // AND_A(0xc);
    // CP_A(FACE_UP);
    // IF_NZ goto failed;
    // LD_A_addr(wTileUp);
    // CALL(aCheckWaterfallTile);
    // IF_NZ goto failed;
    // XOR_A_A;
    // RET;


// failed:
    // SCF;
    // RET;
    return ((wram->wPlayerStruct.facing & 0xc) == FACE_UP && CheckWaterfallTile_Conv(wram->wTileUp))? true: false;
}

bool Script_WaterfallFromMenu(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)

    SCRIPT_FALLTHROUGH(Script_UsedWaterfall);
}

static void CheckContinueWaterfall(void) {
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // LD_A_addr(wPlayerStandingTile);
    // CALL(aCheckWaterfallTile);
    // RET_Z ;
    if(CheckWaterfallTile_Conv(wram->wPlayerStruct.nextTile))
        return;
    // FARCALL(aStubbedTrainerRankings_Waterfall);
    // LD_A(0x1);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

bool Script_UsedWaterfall(script_s* s){
    static const uint8_t WaterfallStep[] = {
        turn_waterfall(UP),
        movement_step_end
    };

    static const txt_cmd_s UseWaterfallText[] = {
        text_far(v_UseWaterfallText)
        text_end
    };
    SCRIPT_BEGIN
    GetPartyNickname();
    writetext(UseWaterfallText)
    waitbutton
    closetext
    playsound(SFX_BUBBLEBEAM)

loop:
    applymovement(PLAYER, WaterfallStep)
    CheckContinueWaterfall();
    iffalse(loop)
    s_end
    SCRIPT_END
}

void TryWaterfallOW(void){
    LD_D(WATERFALL);
    CALL(aCheckPartyMove);
    IF_C goto failed;
    LD_DE(ENGINE_RISINGBADGE);
    CALL(aCheckEngineFlag);
    IF_C goto failed;
    CALL(aCheckMapCanWaterfall);
    IF_C goto failed;
    LD_A(BANK(aScript_AskWaterfall));
    LD_HL(mScript_AskWaterfall);
    CALL(aCallScript);
    SCF;
    RET;


failed:
    LD_A(BANK(aScript_CantDoWaterfall));
    LD_HL(mScript_CantDoWaterfall);
    CALL(aCallScript);
    SCF;
    RET;

}

bool TryWaterfallOW_Conv(void){
    // LD_D(WATERFALL);
    // CALL(aCheckPartyMove);
    // IF_C goto failed;
    // LD_DE(ENGINE_RISINGBADGE);
    // CALL(aCheckEngineFlag);
    // IF_C goto failed;
    // CALL(aCheckMapCanWaterfall);
    // IF_C goto failed;
    if(CheckPartyMove_Conv(WATERFALL)
    && CheckEngineFlag_Conv(ENGINE_RISINGBADGE)
    && CheckMapCanWaterfall_Conv()) {
        // LD_A(BANK(aScript_AskWaterfall));
        // LD_HL(mScript_AskWaterfall);
        // CALL(aCallScript);
        CallScript_Conv2(Script_AskWaterfall);
        // SCF;
        // RET;
        return true;
    }

// failed:
    // LD_A(BANK(aScript_CantDoWaterfall));
    // LD_HL(mScript_CantDoWaterfall);
    // CALL(aCallScript);
    CallScript_Conv2(Script_CantDoWaterfall);
    // SCF;
    // RET;
    return true;
}

bool Script_CantDoWaterfall(script_s* s){
    static const txt_cmd_s HugeWaterfallText[] = {
        text_far(v_HugeWaterfallText)
        text_end
    };
    SCRIPT_BEGIN
    jumptext(HugeWaterfallText)
    SCRIPT_END
}

bool Script_AskWaterfall(script_s* s){
    const txt_cmd_s AskWaterfallText[] = {
        text_far(v_AskWaterfallText)
        text_end
    };
    SCRIPT_BEGIN
    opentext
    writetext(AskWaterfallText)
    yesorno
    iftrue_jump(Script_UsedWaterfall)
    closetext
    s_end
    SCRIPT_END
}

void EscapeRopeFunction(void){
    CALL(aFieldMoveJumptableReset);
    LD_A(0x1);
    JR(mEscapeRopeOrDig);

}

void DigFunction(void){
    CALL(aFieldMoveJumptableReset);
    LD_A(0x2);

    return EscapeRopeOrDig();
}

void EscapeRopeOrDig(void){
    LD_addr_A(wEscapeRopeOrDigType);

loop:
    LD_HL(mEscapeRopeOrDig_DigTable);
    CALL(aFieldMoveJumptable);
    IF_NC goto loop;
    AND_A(0x7f);
    LD_addr_A(wFieldMoveSucceeded);
    RET;


DigTable:
    //dw ['.CheckCanDig'];
    //dw ['.DoDig'];
    //dw ['.FailDig'];


CheckCanDig:
    CALL(aGetMapEnvironment);
    CP_A(CAVE);
    IF_Z goto incave;
    CP_A(DUNGEON);
    IF_Z goto incave;

fail:
    LD_A(0x2);
    RET;


incave:
    LD_HL(wDigWarpNumber);
    LD_A_hli;
    AND_A_A;
    IF_Z goto fail;
    LD_A_hli;
    AND_A_A;
    IF_Z goto fail;
    LD_A_hl;
    AND_A_A;
    IF_Z goto fail;
    LD_A(0x1);
    RET;


DoDig:
    LD_HL(wDigWarpNumber);
    LD_DE(wNextWarp);
    LD_BC(3);
    CALL(aCopyBytes);
    CALL(aGetPartyNickname);
    LD_A_addr(wEscapeRopeOrDigType);
    CP_A(0x2);
    IF_NZ goto escaperope;
    LD_HL(mEscapeRopeOrDig_UsedDigScript);
    CALL(aQueueScript);
    LD_A(0x81);
    RET;


escaperope:
    FARCALL(aSpecialKabutoChamber);
    LD_HL(mEscapeRopeOrDig_UsedEscapeRopeScript);
    CALL(aQueueScript);
    LD_A(0x81);
    RET;


FailDig:
    LD_A_addr(wEscapeRopeOrDigType);
    CP_A(0x2);
    IF_NZ goto failescaperope;
    LD_HL(mEscapeRopeOrDig_CantUseDigText);
    CALL(aMenuTextbox);
    CALL(aWaitPressAorB_BlinkCursor);
    CALL(aCloseWindow);


failescaperope:
    LD_A(0x80);
    RET;


UseDigText:
    //text_far ['_UseDigText']
    //text_end ['?']


UseEscapeRopeText:
    //text_far ['_UseEscapeRopeText']
    //text_end ['?']


CantUseDigText:
    //text_far ['_CantUseDigText']
    //text_end ['?']


UsedEscapeRopeScript:
    //reloadmappart ['?']
    //special ['UpdateTimePals']
    //writetext ['.UseEscapeRopeText']
    //sjump ['.UsedDigOrEscapeRopeScript']


UsedDigScript:
    //reloadmappart ['?']
    //special ['UpdateTimePals']
    //writetext ['.UseDigText']


UsedDigOrEscapeRopeScript:
    //waitbutton ['?']
    //closetext ['?']
    //playsound ['SFX_WARP_TO']
    //applymovement ['PLAYER', '.DigOut']
    //farscall ['Script_AbortBugContest']
    //special ['WarpToSpawnPoint']
    //loadvar ['VAR_MOVEMENT', 'PLAYER_NORMAL']
    //newloadmap ['MAPSETUP_DOOR']
    //playsound ['SFX_WARP_FROM']
    //applymovement ['PLAYER', '.DigReturn']
    //end ['?']


DigOut:
    //step_dig ['32']
    //hide_object ['?']
    //step_end ['?']


DigReturn:
    //show_object ['?']
    //return_dig ['32']
    //step_end ['?']

    return TeleportFunction();
}

void TeleportFunction(void){
    CALL(aFieldMoveJumptableReset);

loop:
    LD_HL(mTeleportFunction_Jumptable);
    CALL(aFieldMoveJumptable);
    IF_NC goto loop;
    AND_A(0x7f);
    LD_addr_A(wFieldMoveSucceeded);
    RET;


Jumptable:
    //dw ['.TryTeleport'];
    //dw ['.DoTeleport'];
    //dw ['.FailTeleport'];


TryTeleport:
    CALL(aGetMapEnvironment);
    CALL(aCheckOutdoorMap);
    IF_Z goto CheckIfSpawnPoint;
    goto nope;


CheckIfSpawnPoint:
    LD_A_addr(wLastSpawnMapGroup);
    LD_D_A;
    LD_A_addr(wLastSpawnMapNumber);
    LD_E_A;
    FARCALL(aIsSpawnPoint);
    IF_NC goto nope;
    LD_A_C;
    LD_addr_A(wDefaultSpawnpoint);
    LD_A(0x1);
    RET;


nope:
    LD_A(0x2);
    RET;


DoTeleport:
    CALL(aGetPartyNickname);
    LD_HL(mTeleportFunction_TeleportScript);
    CALL(aQueueScript);
    LD_A(0x81);
    RET;


FailTeleport:
    LD_HL(mTeleportFunction_CantUseTeleportText);
    CALL(aMenuTextboxBackup);
    LD_A(0x80);
    RET;


TeleportReturnText:
    //text_far ['_TeleportReturnText']
    //text_end ['?']


CantUseTeleportText:
    //text_far ['_CantUseTeleportText']
    //text_end ['?']


TeleportScript:
    //reloadmappart ['?']
    //special ['UpdateTimePals']
    //writetext ['.TeleportReturnText']
    //pause ['60']
    //reloadmappart ['?']
    //closetext ['?']
    //playsound ['SFX_WARP_TO']
    //applymovement ['PLAYER', '.TeleportFrom']
    //farscall ['Script_AbortBugContest']
    //special ['WarpToSpawnPoint']
    //loadvar ['VAR_MOVEMENT', 'PLAYER_NORMAL']
    //newloadmap ['MAPSETUP_TELEPORT']
    //playsound ['SFX_WARP_FROM']
    //applymovement ['PLAYER', '.TeleportTo']
    //end ['?']


TeleportFrom:
    //teleport_from ['?']
    //step_end ['?']


TeleportTo:
    //teleport_to ['?']
    //step_end ['?']

    return StrengthFunction();
}

void StrengthFunction(void){
    CALL(aStrengthFunction_TryStrength);
    AND_A(0x7f);
    LD_addr_A(wFieldMoveSucceeded);
    RET;


TryStrength:
//  Strength
    LD_DE(ENGINE_PLAINBADGE);
    CALL(aCheckBadge);
    IF_C goto Failed;
    goto UseStrength;


AlreadyUsingStrength:
//   //  unreferenced
    LD_HL(mStrengthFunction_AlreadyUsingStrengthText);
    CALL(aMenuTextboxBackup);
    LD_A(0x80);
    RET;


AlreadyUsingStrengthText:
    //text_far ['_AlreadyUsingStrengthText']
    //text_end ['?']


Failed:
    LD_A(0x80);
    RET;


UseStrength:
    LD_HL(mScript_StrengthFromMenu);
    CALL(aQueueScript);
    LD_A(0x81);
    RET;

}

void SetStrengthFlag(void){
    // LD_HL(wBikeFlags);
    // SET_hl(BIKEFLAGS_STRENGTH_ACTIVE_F);
    bit_set(wram->wBikeFlags, BIKEFLAGS_STRENGTH_ACTIVE_F);
    // LD_A_addr(wCurPartyMon);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPartySpecies);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wStrengthSpecies);
    wram->wStrengthSpecies = wram->wPartySpecies[wram->wCurPartyMon];
    // CALL(aGetPartyNickname);
    GetPartyNickname();
    // RET;
}

bool Script_StrengthFromMenu(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)

    SCRIPT_FALLTHROUGH(Script_UsedStrength)
}

bool Script_UsedStrength(script_s* s){
    SCRIPT_BEGIN
    SetStrengthFlag();
    writetext((struct TextCmd[]) {
        text_far(v_UseStrengthText)
        text_end
    })
    readmem(wram_ptr(wStrengthSpecies))
    playcry(0)  // plays [wStrengthSpecies] cry
    pause(3)
    writetext((struct TextCmd[]) {
        text_far(v_MoveBoulderText)
        text_end
    })
    closetext
    s_end
    SCRIPT_END

// UseStrengthText:
    //text_far ['_UseStrengthText']
    //text_end ['?']


// MoveBoulderText:
    //text_far ['_MoveBoulderText']
    //text_end ['?']
}

bool AskStrengthScript(script_s* s){
    SCRIPT_BEGIN
    TryStrengthOW();
    iffalse(AskStrength)
    ifequal(0x1, DontMeetRequirements)
    //sjump(AlreadyUsedStrength)
AlreadyUsedStrength:
    jumptext(BouldersMoveText)

DontMeetRequirements:
    jumptext(BouldersMayMoveText)

AskStrength:
    opentext
    writetext(AskStrengthText)
    yesorno
    iftrue_jump(Script_UsedStrength)
    closetext
    s_end
    SCRIPT_END
}

const txt_cmd_s AskStrengthText[] = {
    text_far(v_AskStrengthText)
    text_end
};

const txt_cmd_s BouldersMoveText[] = {
    text_far(v_BouldersMoveText)
    text_end
};

const txt_cmd_s BouldersMayMoveText[] = {
    text_far(v_BouldersMayMoveText)
    text_end
};

void TryStrengthOW(void){
    // LD_D(STRENGTH);
    // CALL(aCheckPartyMove);
    // IF_C goto nope;

    // LD_DE(ENGINE_PLAINBADGE);
    // CALL(aCheckEngineFlag);
    // IF_C goto nope;
    if(!CheckPartyMove_Conv(STRENGTH) || !CheckEngineFlag_Conv(ENGINE_PLAINBADGE)) {
        wram->wScriptVar = 1;
        return;
    }

    // LD_HL(wBikeFlags);
    // BIT_hl(BIKEFLAGS_STRENGTH_ACTIVE_F);
    // IF_Z goto already_using;
    if(bit_test(wram->wBikeFlags, BIKEFLAGS_STRENGTH_ACTIVE_F)) {
        // LD_A(2);
        // goto done;
        wram->wScriptVar = 2;
        return;
    }
    else {
    // already_using:
        // XOR_A_A;
        // goto done;
        wram->wScriptVar = 0;
        return;
    }

// nope:
    // LD_A(1);
    // goto done;

// done:
    // LD_addr_A(wScriptVar);
    // RET;
}

void WhirlpoolFunction(void){
    CALL(aFieldMoveJumptableReset);

loop:
    LD_HL(mWhirlpoolFunction_Jumptable);
    CALL(aFieldMoveJumptable);
    IF_NC goto loop;
    AND_A(0x7f);
    LD_addr_A(wFieldMoveSucceeded);
    RET;


Jumptable:
    //dw ['.TryWhirlpool'];
    //dw ['.DoWhirlpool'];
    //dw ['.FailWhirlpool'];


TryWhirlpool:
    LD_DE(ENGINE_GLACIERBADGE);
    CALL(aCheckBadge);
    IF_C goto noglacierbadge;
    CALL(aTryWhirlpoolMenu);
    IF_C goto failed;
    LD_A(0x1);
    RET;


failed:
    LD_A(0x2);
    RET;


noglacierbadge:
    LD_A(0x80);
    RET;


DoWhirlpool:
    LD_HL(mScript_WhirlpoolFromMenu);
    CALL(aQueueScript);
    LD_A(0x81);
    RET;


FailWhirlpool:
    CALL(aFieldMoveFailed);
    LD_A(0x80);
    RET;

}

const txt_cmd_s UseWhirlpoolText[] = {
    text_far(v_UseWhirlpoolText)
    text_end
};

void TryWhirlpoolMenu(void){
    CALL(aGetFacingTileCoord);
    LD_C_A;
    PUSH_DE;
    CALL(aCheckWhirlpoolTile);
    POP_DE;
    IF_C goto failed;
    CALL(aGetBlockLocation);
    LD_C_hl;
    PUSH_HL;
    LD_HL(mWhirlpoolBlockPointers);
    CALL(aCheckOverworldTileArrays);
    POP_HL;
    IF_NC goto failed;
// Save the Whirlpool field move data
    LD_A_L;
    LD_addr_A(wCutWhirlpoolOverworldBlockAddr);
    LD_A_H;
    LD_addr_A(wCutWhirlpoolOverworldBlockAddr + 1);
    LD_A_B;
    LD_addr_A(wCutWhirlpoolReplacementBlock);
    LD_A_C;
    LD_addr_A(wCutWhirlpoolAnimationType);
    XOR_A_A;
    RET;


failed:
    SCF;
    RET;

}

bool TryWhirlpoolMenu_Conv(void){
    // CALL(aGetFacingTileCoord);
    struct CoordsTileId cid = GetFacingTileCoord_Conv();
    // LD_C_A;
    // PUSH_DE;
    // CALL(aCheckWhirlpoolTile);
    // POP_DE;
    // IF_C goto failed;
    if(!CheckWhirlpoolTile_Conv(cid.tileId))
        return false;
    // CALL(aGetBlockLocation);
    uint8_t* hl = GetBlockLocation_Conv(cid.x, cid.y);
    // LD_C_hl;
    // PUSH_HL;
    // LD_HL(mWhirlpoolBlockPointers);
    // CALL(aCheckOverworldTileArrays);
    struct OverworldTileRes res = CheckOverworldTileArrays_Conv(WhirlpoolBlockPointers, *hl);
    // POP_HL;
    // IF_NC goto failed;
    if(!res.flag)
        return false;
// Save the Whirlpool field move data
    // LD_A_L;
    // LD_addr_A(wCutWhirlpoolOverworldBlockAddr);
    // LD_A_H;
    // LD_addr_A(wCutWhirlpoolOverworldBlockAddr + 1);
    sFieldMoveData.cutWhirlpoolOverworldBlockAddr = hl;
    // LD_A_B;
    // LD_addr_A(wCutWhirlpoolReplacementBlock);
    sFieldMoveData.cutWhirlpoolReplacementBlock = res.b;
    // LD_A_C;
    // LD_addr_A(wCutWhirlpoolAnimationType);
    sFieldMoveData.cutWhirlpoolAnimationType = res.c;
    // XOR_A_A;
    // RET;
    return true;

// failed:
    // SCF;
    // RET;
}

bool Script_WhirlpoolFromMenu(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)

    SCRIPT_FALLTHROUGH(Script_UsedWhirlpool)
}

bool Script_UsedWhirlpool(script_s* s){
    SCRIPT_BEGIN
    GetPartyNickname();
    writetext(UseWhirlpoolText)
    reloadmappart
    DisappearWhirlpool();
    closetext
    s_end
    SCRIPT_END
}

void DisappearWhirlpool(void){
    // LD_HL(wCutWhirlpoolOverworldBlockAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wCutWhirlpoolReplacementBlock);
    // LD_hl_A;
    *sFieldMoveData.cutWhirlpoolOverworldBlockAddr = sFieldMoveData.cutWhirlpoolReplacementBlock;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch_Conv();
    // LD_A_addr(wCutWhirlpoolAnimationType);
    // LD_E_A;
    // FARCALL(aPlayWhirlpoolSound);
    PlayWhirlpoolSound();
    // CALL(aBufferScreen);
    BufferScreen_Conv();
    // CALL(aGetMovementPermissions);
    GetMovementPermissions();
    // RET;
}

void TryWhirlpoolOW(void){
    LD_D(WHIRLPOOL);
    CALL(aCheckPartyMove);
    IF_C goto failed;
    LD_DE(ENGINE_GLACIERBADGE);
    CALL(aCheckEngineFlag);
    IF_C goto failed;
    CALL(aTryWhirlpoolMenu);
    IF_C goto failed;
    LD_A(BANK(aScript_AskWhirlpoolOW));
    LD_HL(mScript_AskWhirlpoolOW);
    CALL(aCallScript);
    SCF;
    RET;


failed:
    LD_A(BANK(aScript_MightyWhirlpool));
    LD_HL(mScript_MightyWhirlpool);
    CALL(aCallScript);
    SCF;
    RET;

}

bool TryWhirlpoolOW_Conv(void){
    // LD_D(WHIRLPOOL);
    // CALL(aCheckPartyMove);
    // IF_C goto failed;
    // LD_DE(ENGINE_GLACIERBADGE);
    // CALL(aCheckEngineFlag);
    // IF_C goto failed;
    // CALL(aTryWhirlpoolMenu);
    // IF_C goto failed;
    if(CheckPartyMove_Conv(WHIRLPOOL)
    && CheckEngineFlag_Conv(ENGINE_GLACIERBADGE)
    && TryWhirlpoolMenu_Conv()) {
        // LD_A(BANK(aScript_AskWhirlpoolOW));
        // LD_HL(mScript_AskWhirlpoolOW);
        // CALL(aCallScript);
        CallScript_Conv2(Script_AskWhirlpoolOW);
        // SCF;
        // RET;
        return true;
    }

// failed:
    // LD_A(BANK(aScript_MightyWhirlpool));
    // LD_HL(mScript_MightyWhirlpool);
    // CALL(aCallScript);
    CallScript_Conv2(Script_MightyWhirlpool);
    // SCF;
    // RET;
    return true;
}

bool Script_MightyWhirlpool(script_s* s){
    static const txt_cmd_s MayPassWhirlpoolText[] = {
        text_far(v_MayPassWhirlpoolText)
        text_end
    };
    SCRIPT_BEGIN
    jumptext(MayPassWhirlpoolText)
    SCRIPT_END
}

bool Script_AskWhirlpoolOW(script_s* s){
    SCRIPT_BEGIN
    opentext
    writetext(AskWhirlpoolText)
    yesorno
    iftrue_jump(Script_UsedWhirlpool)
    closetext
    s_end
    SCRIPT_END
}

const txt_cmd_s AskWhirlpoolText[] = {
    text_far(v_AskWhirlpoolText)
    text_end
};

void HeadbuttFunction(void){
    // CALL(aTryHeadbuttFromMenu);
    // AND_A(0x7f);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = TryHeadbuttFromMenu_Conv() & 0x7f;
    // RET;
}

void TryHeadbuttFromMenu(void){
    CALL(aGetFacingTileCoord);
    CALL(aCheckHeadbuttTreeTile);
    IF_NZ goto no_tree;

    LD_HL(mHeadbuttFromMenuScript);
    CALL(aQueueScript);
    LD_A(0x81);
    RET;


no_tree:
    CALL(aFieldMoveFailed);
    LD_A(0x80);
    RET;

}

uint8_t TryHeadbuttFromMenu_Conv(void){
    // CALL(aGetFacingTileCoord);
    struct CoordsTileId cid = GetFacingTileCoord_Conv();
    // CALL(aCheckHeadbuttTreeTile);
    // IF_NZ goto no_tree;
    if(!CheckHeadbuttTreeTile_Conv(cid.tileId)) {
    // no_tree:
        // CALL(aFieldMoveFailed);
        FieldMoveFailed();
        // LD_A(0x80);
        // RET;
        return 0x80;
    }

    // LD_HL(mHeadbuttFromMenuScript);
    // CALL(aQueueScript);
    QueueScript_Conv2(HeadbuttFromMenuScript);
    // LD_A(0x81);
    // RET;
    return 0x81;
}

const txt_cmd_s UseHeadbuttText[] = {
    text_far(v_UseHeadbuttText)
    text_end
};

const txt_cmd_s HeadbuttNothingText[] = {
    text_far(v_HeadbuttNothingText)
    text_end
};

bool HeadbuttFromMenuScript(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)

    SCRIPT_FALLTHROUGH(HeadbuttScript)
}

bool HeadbuttScript(script_s* s){
    SCRIPT_BEGIN
    GetPartyNickname();
    writetext(UseHeadbuttText)

    reloadmappart
    ShakeHeadbuttTree();

    //callasm ['TreeMonEncounter']
    TreeMonEncounter();
    wram->wScriptVar = FALSE;
    iffalse(no_battle)
    closetext
    randomwildmon
    startbattle
    reloadmapafterbattle
    s_end


no_battle:
    writetext(HeadbuttNothingText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}

void TryHeadbuttOW(void){
    LD_D(HEADBUTT);
    CALL(aCheckPartyMove);
    IF_C goto no;

    LD_A(BANK(aAskHeadbuttScript));
    LD_HL(mAskHeadbuttScript);
    CALL(aCallScript);
    SCF;
    RET;


no:
    XOR_A_A;
    RET;

}

bool TryHeadbuttOW_Conv(void){
    // LD_D(HEADBUTT);
    // CALL(aCheckPartyMove);
    // IF_C goto no;
    if(CheckPartyMove_Conv(HEADBUTT)) {
        // LD_A(BANK(aAskHeadbuttScript));
        // LD_HL(mAskHeadbuttScript);
        // CALL(aCallScript);
        CallScript_Conv2(AskHeadbuttScript);
        // SCF;
        // RET;
        return true;
    }

// no:
    // XOR_A_A;
    // RET;
    return false;
}

bool AskHeadbuttScript(script_s* s){
    SCRIPT_BEGIN
    opentext
    writetext(AskHeadbuttText)
    yesorno
    iftrue_jump(HeadbuttScript)
    closetext
    s_end
    SCRIPT_END
}

const txt_cmd_s AskHeadbuttText[] = {
    text_far(v_AskHeadbuttText)
    text_end
};

void RockSmashFunction(void){
    // CALL(aTryRockSmashFromMenu);
    // AND_A(0x7f);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = TryRockSmashFromMenu_Conv() & 0x7f;
    // RET;
}

void TryRockSmashFromMenu(void){
    CALL(aGetFacingObject);
    IF_C goto no_rock;
    LD_A_D;
    CP_A(SPRITEMOVEDATA_SMASHABLE_ROCK);
    IF_NZ goto no_rock;

    LD_HL(mRockSmashFromMenuScript);
    CALL(aQueueScript);
    LD_A(0x81);
    RET;


no_rock:
    CALL(aFieldMoveFailed);
    LD_A(0x80);
    RET;

}

uint8_t TryRockSmashFromMenu_Conv(void){
    // CALL(aGetFacingObject);
    // IF_C goto no_rock;
    u8_flag_s res = GetFacingObject_Conv();
    // LD_A_D;
    // CP_A(SPRITEMOVEDATA_SMASHABLE_ROCK);
    // IF_NZ goto no_rock;
    if(!res.flag || res.a != SPRITEMOVEDATA_SMASHABLE_ROCK) {
    // no_rock:
        // CALL(aFieldMoveFailed);
        FieldMoveFailed();
        // LD_A(0x80);
        // RET;
        return 0x80;
    }

    // LD_HL(mRockSmashFromMenuScript);
    // CALL(aQueueScript);
    QueueScript_Conv2(RockSmashFromMenuScript);
    // LD_A(0x81);
    // RET;
    return 0x81;
}

void GetFacingObject(void){
    FARCALL(aCheckFacingObject);
    IF_NC goto fail;

    LDH_A_addr(hObjectStructIndex);
    CALL(aGetObjectStruct);
    LD_HL(OBJECT_MAP_OBJECT_INDEX);
    ADD_HL_BC;
    LD_A_hl;
    LDH_addr_A(hLastTalked);
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_MOVEMENT);
    ADD_HL_BC;
    LD_A_hl;
    LD_D_A;
    AND_A_A;
    RET;


fail:
    SCF;
    RET;

}

u8_flag_s GetFacingObject_Conv(void){
    // FARCALL(aCheckFacingObject);
    // IF_NC goto fail;
    struct Object* bc = CheckFacingObject_Conv();
    if(bc == NULL)
        return u8_flag(0, false);

    // LDH_A_addr(hObjectStructIndex);
    // CALL(aGetObjectStruct);
    // LD_HL(OBJECT_MAP_OBJECT_INDEX);
    // ADD_HL_BC;
    // LD_A_hl;
    // LDH_addr_A(hLastTalked);
    hram->hLastTalked = bc->mapObjectIndex;
    // CALL(aGetMapObject);
    // LD_HL(MAPOBJECT_MOVEMENT);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_D_A;
    // AND_A_A;
    // RET;
    return u8_flag(GetMapObject_Conv(bc->mapObjectIndex)->objectMovement, true);

// fail:
    // SCF;
    // RET;
}

bool RockSmashFromMenuScript(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)

    SCRIPT_FALLTHROUGH(RockSmashScript)
}

bool RockSmashScript(script_s* s){
    SCRIPT_BEGIN
    GetPartyNickname();
    writetext(UseRockSmashText)
    closetext
    special(WaitSFX)
    playsound(SFX_STRENGTH)
    earthquake(84)
    applymovementlasttalked(MovementData_RockSmash)
    disappear(-2)

    //callasm ['RockMonEncounter']
    RockMonEncounter();
    readmem(wram_ptr(wTempWildMonSpecies))
    iffalse(done)
    randomwildmon
    startbattle
    reloadmapafterbattle

done:
    s_end
    SCRIPT_END
}

const uint8_t MovementData_RockSmash[] = {
    rock_smash(10),
    movement_step_end
};

const txt_cmd_s UseRockSmashText[] = {
    text_far(v_UseRockSmashText)
    text_end
};

bool AskRockSmashScript(script_s* s){
    SCRIPT_BEGIN
    HasRockSmash();
    ifequal(1, no)

    opentext
    writetext(AskRockSmashText)
    yesorno
    iftrue_jump(RockSmashScript)
    closetext
    s_end

no:
    jumptext(MaySmashText)
    SCRIPT_END
}

const txt_cmd_s MaySmashText[] = {
    text_far(v_MaySmashText)
    text_end
};

const txt_cmd_s AskRockSmashText[] = {
    text_far(v_AskRockSmashText)
    text_end
};

void HasRockSmash(void){
    // LD_D(ROCK_SMASH);
    // CALL(aCheckPartyMove);
    // IF_NC goto yes;
//  no
    // LD_A(1);
    // goto done;

// yes:
    // XOR_A_A;
    // goto done;

// done:
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = (CheckPartyMove_Conv(ROCK_SMASH))? 0: 1;
}

void FishFunction(void){
    return FishFunction_Conv(REG_E);
}

static uint8_t FishFunction_TryFish(void) {
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_SURF);
    // IF_Z goto fail;
    // CP_A(PLAYER_SURF_PIKA);
    // IF_Z goto fail;
    // CALL(aGetFacingTileCoord);
    // CALL(aGetTileCollision);
    // CP_A(WATER_TILE);
    // IF_Z goto facingwater;
    if(wram->wPlayerState == PLAYER_SURF || wram->wPlayerState == PLAYER_SURF_PIKA
    || GetTileCollision_Conv(GetFacingTileCoord_Conv().tileId) != WATER_TILE) {
    // fail:
        // LD_A(0x3);
        // RET;
        return 0x3;
    }

// facingwater:
    // CALL(aGetFishingGroup);
    uint8_t fishGroup = GetFishingGroup_Conv2();
    // AND_A_A;
    // IF_NZ goto goodtofish;
    if(fishGroup == 0) {
        // LD_A(0x4);
        // RET;
        return 0x4;
    }

// goodtofish:
    // LD_D_A;
    // LD_A_addr(wFishingRodUsed);
    // LD_E_A;
    // FARCALL(aFish);
    struct SpeciesLevel fishMon = Fish_Conv(sFieldMoveData.fishingRodUsed, fishGroup);
    // LD_A_D;
    // AND_A_A;
    // IF_Z goto nonibble;
    if(fishMon.species == 0) {
    // nonibble:
        // LD_A(0x1);
        // RET;
        return 0x1;
    }
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = fishMon.species;
    // LD_A_E;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = fishMon.level;
    // LD_A(BATTLETYPE_FISH);
    // LD_addr_A(wBattleType);
    wram->wBattleType = BATTLETYPE_FISH;
    // LD_A(0x2);
    // RET;
    return 0x2;
}


static uint8_t FishFunction_FailFish(void) {
    // LD_A(0x80);
    // RET;
    return 0x80;
}


static uint8_t FishFunction_FishGotSomething(void) {
    // LD_A(0x1);
    // LD_addr_A(wFishingResult);
    // sFieldMoveData.fishingResult = 0x1; // Never read
    // LD_HL(mScript_GotABite);
    // CALL(aQueueScript);
    QueueScript_Conv2(Script_GotABite);
    // LD_A(0x81);
    // RET;
    return 0x81;
}


static uint8_t FishFunction_FishNoBite(void) {
    // LD_A(0x2);
    // LD_addr_A(wFishingResult);
    // sFieldMoveData.fishingResult = 0x2; // Never read
    // LD_HL(mScript_NotEvenANibble);
    // CALL(aQueueScript);
    QueueScript_Conv2(Script_NotEvenANibble);
    // LD_A(0x81);
    // RET;
    return 0x81;
}

static uint8_t FishFunction_FishNoFish(void) {
    // LD_A(0x0);
    // LD_addr_A(wFishingResult);
    // sFieldMoveData.fishingResult = 0x0; // Never read
    // LD_HL(mScript_NotEvenANibble2);
    // CALL(aQueueScript);
    QueueScript_Conv2(Script_NotEvenANibble2);
    // LD_A(0x81);
    // RET;
    return 0x81;
}

void FishFunction_Conv(uint8_t rod){
    const field_move_fn_t Jumptable[] = {
        FishFunction_TryFish,
        FishFunction_FishNoBite,
        FishFunction_FishGotSomething,
        FishFunction_FailFish,
        FishFunction_FishNoFish,
    };
    // LD_A_E;
    // PUSH_AF;
    // CALL(aFieldMoveJumptableReset);
    FieldMoveJumptableReset();
    // POP_AF;
    // LD_addr_A(wFishingRodUsed);
    sFieldMoveData.fishingRodUsed = rod;
    u8_flag_s res;

    do {
    // loop:
        // LD_HL(mFishFunction_FishTable);
        // CALL(aFieldMoveJumptable);
        res = FieldMoveJumptable_Conv(Jumptable);
        // IF_NC goto loop;
    } while(!res.flag);
    // AND_A(0x7f);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = res.a & 0x7f;
    // RET;


// FishTable:
    //dw ['.TryFish'];
    //dw ['.FishNoBite'];
    //dw ['.FishGotSomething'];
    //dw ['.FailFish'];
    //dw ['.FishNoFish'];

}

bool Script_NotEvenANibble(script_s* s){
    SCRIPT_BEGIN
    scall(Script_FishCastRod)
    writetext(RodNothingText)
    sjump(Script_NotEvenANibble_FallThrough)
    SCRIPT_END
}

bool Script_NotEvenANibble2(script_s* s){
    SCRIPT_BEGIN
    scall(Script_FishCastRod)
    writetext(RodNothingText)

    SCRIPT_FALLTHROUGH(Script_NotEvenANibble_FallThrough)
}

bool Script_NotEvenANibble_FallThrough(script_s* s){
    SCRIPT_BEGIN
    loademote(EMOTE_SHADOW)
    PutTheRodAway();
    closetext
    s_end
    SCRIPT_END
}

bool Script_GotABite(script_s* s){
static const uint8_t Movement_NotFacingUp[] = {
    movement_fish_got_bite,
    movement_fish_got_bite,
    movement_fish_got_bite,
    movement_fish_got_bite,
    movement_show_emote,
    movement_step_end
};

static const uint8_t Movement_FacingUp[] = {
    movement_fish_got_bite,
    movement_fish_got_bite,
    movement_fish_got_bite,
    movement_fish_got_bite,
    step_sleep(1),
    movement_show_emote,
    movement_step_end,
};

static const uint8_t Movement_RestoreRod[] = {
    movement_hide_emote,
    movement_fish_cast_rod,
    movement_step_end,
};
    SCRIPT_BEGIN
    scall(Script_FishCastRod)
    Fishing_CheckFacingUp();
    iffalse(NotFacingUp)
    applymovement(PLAYER, Movement_FacingUp)
    goto FightTheHookedPokemon;

NotFacingUp:
    applymovement(PLAYER, Movement_NotFacingUp)

FightTheHookedPokemon:
    pause(40)
    applymovement(PLAYER, Movement_RestoreRod)
    writetext(RodBiteText)
    PutTheRodAway();
    closetext
    randomwildmon
    startbattle
    reloadmapafterbattle
    s_end
    SCRIPT_END
}

void Fishing_CheckFacingUp(void){
    // LD_A_addr(wPlayerDirection);
    // AND_A(0xc);
    // CP_A(OW_UP);
    // LD_A(0x1);
    // IF_Z goto up;
    // XOR_A_A;


// up:
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = ((wram->wPlayerStruct.facing & 0xc) == OW_UP)? TRUE: FALSE;
}

bool Script_FishCastRod(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    loadmem(hram_ptr(hBGMapMode), 0x0)
    special(UpdateTimePals)
    loademote(EMOTE_ROD)
    LoadFishingGFX();
    loademote(EMOTE_SHOCK)
    applymovement(PLAYER, MovementData_CastRod)
    pause(40)
    s_end
    SCRIPT_END
}

const uint8_t MovementData_CastRod[] = {
    movement_fish_cast_rod,
    movement_step_end
};

void PutTheRodAway(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // LD_A(0x1);
    // LD_addr_A(wPlayerAction);
    wram->wPlayerStruct.action = 0x1;
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aUpdatePlayerSprite);
    UpdatePlayerSprite_Conv();
    // RET;
}

const txt_cmd_s RodBiteText[] = {
    text_far(v_RodBiteText)
    text_end
};

const txt_cmd_s RodNothingText[] = {
    text_far(v_RodNothingText)
    text_end
};

//  //  unreferenced
const txt_cmd_s UnusedNothingHereText[] ={
    text_far(v_UnusedNothingHereText)
    text_end
};

static bool BikeFunction_CheckEnvironment(void) {
    // CALL(aGetMapEnvironment);
    uint8_t env = GetMapEnvironment_Conv2();
    // CALL(aCheckOutdoorMap);
    // IF_Z goto ok;
    // CP_A(CAVE);
    // IF_Z goto ok;
    // CP_A(GATE);
    // IF_Z goto ok;
    // goto nope;
    if(CheckOutdoorMap_Conv(env)
    || env == CAVE
    || env == GATE) {
    // ok:
        // CALL(aGetPlayerStandingTile);
        // AND_A(0xf);  // lo nybble only
        // IF_NZ goto nope;  // not FLOOR_TILE
        if((GetPlayerStandingTile_Conv() & 0xf) == 0) {
            // XOR_A_A;
            // RET;
            return true;
        }

    // nope:
        // SCF;
        // RET;
    }
    return false;
}

static Script_fn_t BikeFunction_CheckIfRegistered(Script_fn_t no_select, Script_fn_t select) {
    // LD_A_addr(wUsingItemWithSelect);
    // AND_A_A;
    // RET_Z ;
    if(wram->wUsingItemWithSelect == 0)
        return no_select;
    // LD_H_D;
    // LD_L_E;
    // RET;
    return select;
}

static uint8_t BikeFunction_TryBike(void) {
    // CALL(aBikeFunction_CheckEnvironment);
    // IF_C goto CannotUseBike;
    if(!BikeFunction_CheckEnvironment())
        return 0x0;
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_NORMAL);
    // IF_Z goto GetOnBike;
    if(wram->wPlayerState == PLAYER_NORMAL) {
    // GetOnBike:
        // LD_HL(mScript_GetOnBike);
        // LD_DE(mScript_GetOnBike_Register);
        // CALL(aBikeFunction_CheckIfRegistered);
        // CALL(aQueueScript);
        QueueScript_Conv2(BikeFunction_CheckIfRegistered(Script_GetOnBike, Script_GetOnBike_Register));
        // XOR_A_A;
        // LD_addr_A(wMusicFade);
        wram->wMusicFade = 0x0;
        // LD_DE(MUSIC_NONE);
        // CALL(aPlayMusic);
        PlayMusic_Conv(MUSIC_NONE);
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aMaxVolume);
        MaxVolume_Conv();
        // LD_DE(MUSIC_BICYCLE);
        // LD_A_E;
        // LD_addr_A(wMapMusic);
        wram->wMapMusic = MUSIC_BICYCLE;
        // CALL(aPlayMusic);
        PlayMusic_Conv(MUSIC_BICYCLE);
        // LD_A(0x1);
        // RET;
        return 0x1;
    }
    // CP_A(PLAYER_BIKE);
    // IF_Z goto GetOffBike;
    else if(wram->wPlayerState == PLAYER_BIKE) {
    // GetOffBike:
        // LD_HL(wBikeFlags);
        // BIT_hl(BIKEFLAGS_ALWAYS_ON_BIKE_F);
        // IF_NZ goto CantGetOffBike;
        Script_fn_t script;
        if(!bit_test(wram->wBikeFlags, BIKEFLAGS_ALWAYS_ON_BIKE_F)) {
            // LD_HL(mScript_GetOffBike);
            // LD_DE(mScript_GetOffBike_Register);
            // CALL(aBikeFunction_CheckIfRegistered);
            script = BikeFunction_CheckIfRegistered(Script_GetOffBike, Script_GetOffBike_Register);
            // LD_A(BANK(aScript_GetOffBike));
            // goto done;
        }
        else {
        // CantGetOffBike:
            // LD_HL(mScript_CantGetOffBike);
            // goto done;
            script = Script_CantGetOffBike;
        }

    // done:
        // CALL(aQueueScript);
        QueueScript_Conv2(script);
        // LD_A(0x1);
        // RET;
        return 0x1;
    }
    // goto CannotUseBike;
    else {
    // CannotUseBike:
        // LD_A(0x0);
        // RET;
        return 0x0;
    }
}

void BikeFunction(void){
    // CALL(aBikeFunction_TryBike);
    // AND_A(0x7f);
    // LD_addr_A(wFieldMoveSucceeded);
    wram->wFieldMoveSucceeded = BikeFunction_TryBike() & 0x7f;
    // RET;
}

bool Script_GetOnBike(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)
    loadvar(VAR_MOVEMENT, PLAYER_BIKE)
    writetext(GotOnBikeText)
    waitbutton
    closetext
    special(UpdatePlayerSprite)
    s_end
    SCRIPT_END
}

bool Script_GetOnBike_Register(script_s* s){
    SCRIPT_BEGIN
    loadvar(VAR_MOVEMENT, PLAYER_BIKE)
    closetext
    special(UpdatePlayerSprite)
    s_end
    SCRIPT_END
}

void Overworld_DummyFunction(void){
//  //  unreferenced
    NOP;
    RET;

}

bool Script_GetOffBike(script_s* s){
    SCRIPT_BEGIN
    reloadmappart
    special(UpdateTimePals)
    loadvar(VAR_MOVEMENT, PLAYER_NORMAL)
    writetext(GotOffBikeText)
    waitbutton

    SCRIPT_FALLTHROUGH(FinishGettingOffBike)
}

bool FinishGettingOffBike(script_s* s){
    SCRIPT_BEGIN
    closetext
    special(UpdatePlayerSprite)
    special(PlayMapMusic)
    s_end
    SCRIPT_END
}

bool Script_GetOffBike_Register(script_s* s){
    SCRIPT_BEGIN
    loadvar(VAR_MOVEMENT, PLAYER_NORMAL)
    sjump(FinishGettingOffBike)
    SCRIPT_END
}

bool Script_CantGetOffBike(script_s* s){
    const txt_cmd_s CantGetOffBikeText[] = {
        text_far(v_CantGetOffBikeText)
        text_end
    };
    SCRIPT_BEGIN
    writetext(CantGetOffBikeText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}

const txt_cmd_s GotOnBikeText[] = {
    text_far(v_GotOnBikeText)
    text_end
};

const txt_cmd_s GotOffBikeText[] = {
    text_far(v_GotOffBikeText)
    text_end
};

void TryCutOW(void){
    LD_D(CUT);
    CALL(aCheckPartyMove);
    IF_C goto cant_cut;

    LD_DE(ENGINE_HIVEBADGE);
    CALL(aCheckEngineFlag);
    IF_C goto cant_cut;

    LD_A(BANK(aAskCutScript));
    LD_HL(mAskCutScript);
    CALL(aCallScript);
    SCF;
    RET;


cant_cut:
    LD_A(BANK(aCantCutScript));
    LD_HL(mCantCutScript);
    CALL(aCallScript);
    SCF;
    RET;

}

u8_flag_s TryCutOW_Conv(void){
    // LD_D(CUT);
    // CALL(aCheckPartyMove);
    // IF_C goto cant_cut;

    // LD_DE(ENGINE_HIVEBADGE);
    // CALL(aCheckEngineFlag);
    // IF_C goto cant_cut;

    if(CheckPartyMove_Conv(CUT) && CheckEngineFlag_Conv(ENGINE_HIVEBADGE)) {
        // LD_A(BANK(aAskCutScript));
        // LD_HL(mAskCutScript);
        // CALL(aCallScript);
        // SCF;
        // RET;
        return u8_flag(CallScript_Conv2(AskCutScript), true);
    }

// cant_cut:
    // LD_A(BANK(aCantCutScript));
    // LD_HL(mCantCutScript);
    // CALL(aCallScript);
    // SCF;
    // RET;
    return u8_flag(CallScript_Conv2(CantCutScript), true);
}

static void AskCutScript_CheckMap(void) {
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // CALL(aCheckMapForSomethingToCut);
    // RET_C ;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = (CheckMapForSomethingToCut_Conv())? TRUE: FALSE;
}

bool AskCutScript(script_s* s){
    SCRIPT_BEGIN
    opentext
    writetext(AskCutText)
    yesorno
    iffalse(declined)
    AskCutScript_CheckMap();
    iftrue_jump(Script_Cut)

declined:
    closetext
    s_end
    SCRIPT_END
}

const txt_cmd_s AskCutText[] = {
    text_far(v_AskCutText)
    text_end
};

bool CantCutScript(script_s* s){
    SCRIPT_BEGIN
    jumptext(CanCutText)
    SCRIPT_END
}

const txt_cmd_s CanCutText[] = {
    text_far(v_CanCutText)
    text_end
};
