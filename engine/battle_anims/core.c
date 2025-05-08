#include "../../constants.h"
#include "core.h"
#include "helpers.h"
#include "bg_effects.h"
#include "../../data/battle_anims/objects.h"

static void InitBattleAnimation(struct BattleAnim* bc);
static void InitBattleAnimBuffer(struct BattleAnim* bc);
static uint8_t GetBattleAnimTileOffset(uint8_t a);

bool QueueBattleAnimation(void){
    // LD_HL(wActiveAnimObjects);
    // LD_E(NUM_ANIM_OBJECTS);
    struct BattleAnim* hl = wram->wAnimObject;
    uint8_t e = NUM_ANIM_OBJECTS;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done;
        if(hl->index == 0) {
        // done:
            // LD_C_L;
            // LD_B_H;
            // LD_HL(wLastAnimObjectIndex);
            // INC_hl;
            wram->wLastAnimObjectIndex++;
            // CALL(aInitBattleAnimation);
            InitBattleAnimation(hl);
            // RET;
            return false;
        }
        // LD_BC(BATTLEANIMSTRUCT_LENGTH);
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    } while(hl++, --e != 0);
    // SCF;
    // RET;
    return true;
}

void DeinitBattleAnimation(struct BattleAnim* bc){
    // LD_HL(BATTLEANIMSTRUCT_INDEX);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->index = 0x0;
    // RET;
}

static void InitBattleAnimation(struct BattleAnim* bc){
    // LD_A_addr(wBattleObjectTempID);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mBattleAnimObjects);
    // for(int rept = 0; rept < BATTLEANIMOBJ_LENGTH; rept++){
    // ADD_HL_DE;
    // }
    // LD_E_L;
    // LD_D_H;
    const struct BattleAnimObj* de = BattleAnimObjects + wram->wBattleObjectTempID;
    // LD_HL(BATTLEANIMSTRUCT_INDEX);
    // ADD_HL_BC;
    // LD_A_addr(wLastAnimObjectIndex);
    // LD_hli_A;  // BATTLEANIMSTRUCT_INDEX
    bc->index = wram->wLastAnimObjectIndex;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;  // BATTLEANIMSTRUCT_OAMFLAGS
    bc->oamFlags = de->flags;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;  // BATTLEANIMSTRUCT_FIX_Y
    bc->fixY = de->enemyAnim;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;  // BATTLEANIMSTRUCT_FRAMESET_ID
    bc->framesetId = de->videoSeq;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;  // BATTLEANIMSTRUCT_FUNCTION
    bc->function = de->callback;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;  // BATTLEANIMSTRUCT_PALETTE
    bc->palette = de->palette;
    // LD_A_de;
    // CALL(aGetBattleAnimTileOffset);
    // LD_hli_A;  // BATTLEANIMSTRUCT_TILEID
    bc->tileId = GetBattleAnimTileOffset(de->tileOffset);
    // LD_A_addr(wBattleObjectTempXCoord);
    // LD_hli_A;  // BATTLEANIMSTRUCT_XCOORD
    bc->xCoord = wram->wBattleObjectTempXCoord;
    // LD_A_addr(wBattleObjectTempYCoord);
    // LD_hli_A;  // BATTLEANIMSTRUCT_YCOORD
    bc->yCoord = wram->wBattleObjectTempYCoord;
    // XOR_A_A;
    // LD_hli_A;  // BATTLEANIMSTRUCT_XOFFSET
    bc->xOffset = 0;
    // LD_hli_A;  // BATTLEANIMSTRUCT_YOFFSET
    bc->yOffset = 0;
    // LD_A_addr(wBattleObjectTempParam);
    // LD_hli_A;  // BATTLEANIMSTRUCT_PARAM
    bc->param = wram->wBattleObjectTempParam;
    // XOR_A_A;
    // LD_hli_A;  // BATTLEANIMSTRUCT_DURATION
    bc->duration = 0;
    // DEC_A;
    // LD_hli_A;  // BATTLEANIMSTRUCT_FRAME
    bc->frame = (uint8_t)-1;
    // XOR_A_A;
    // LD_hli_A;  // BATTLEANIMSTRUCT_JUMPTABLE_INDEX
    bc->jumptableIndex = 0;
    // LD_hli_A;  // BATTLEANIMSTRUCT_VAR1
    bc->var1 = 0;
    // LD_hl_A;  // BATTLEANIMSTRUCT_VAR2
    bc->var2 = 0;
    // RET;
}

// #define delanim_command 0xFC
// #define dowait_command 0xFD

bool BattleAnimOAMUpdate(struct BattleAnim* bc, uint8_t* oamIndex){
    // CALL(aInitBattleAnimBuffer);
    InitBattleAnimBuffer(bc);
    // CALL(aGetBattleAnimFrame);
    uint8_t a = GetBattleAnimFrame(bc);
    // CP_A(dowait_command);
    // JP_Z (mBattleAnimOAMUpdate_done);
    if(a == dowait_command)
        return false;
    // CP_A(delanim_command);
    // JP_Z (mBattleAnimOAMUpdate_delete);
    if(a == delanim_command) {
    // delete:
        // CALL(aDeinitBattleAnimation);
        DeinitBattleAnimation(bc);

    // done:
        // AND_A_A;
        // RET;
        return false;
    }

    // PUSH_AF;
    // LD_HL(wBattleAnimTempOAMFlags);
    // LD_A_addr(wBattleAnimTempFrameOAMFlags);
    // XOR_A_hl;
    // AND_A(PRIORITY | Y_FLIP | X_FLIP);
    // LD_hl_A;
    wram->wBattleAnimTempOAMFlags = (wram->wBattleAnimTempOAMFlags ^ wram->wBattleAnimTempFrameOAMFlags) & (PRIORITY | Y_FLIP | X_FLIP);
    // POP_AF;

    // PUSH_BC;
    // CALL(aGetBattleAnimOAMPointer);
    const struct BattleOAMData* oam = GetBattleAnimOAMPointer(a);
    // LD_A_addr(wBattleAnimTempTileID);
    // ADD_A_hl;  // tile offset
    // LD_addr_A(wBattleAnimTempTileID);
    wram->wBattleAnimTempTileID += (int8_t)oam->vtile_offset;
    // INC_HL;
    // LD_A_hli;  // oam data length
    // LD_C_A;
    uint8_t c = oam->data_length;
    // LD_A_hli;  // oam data pointer
    // LD_H_hl;
    // LD_L_A;
    const uint8_t* hl = oam->ptr;
    // LD_A_addr(wBattleAnimOAMPointerLo);
    // LD_E_A;
    // LD_D(HIGH(wVirtualOAM));
    struct SpriteOAM* de = wram->wVirtualOAMSprite + *oamIndex;

    do {
    // loop:
    // Y Coord
        // LD_A_addr(wBattleAnimTempYCoord);
        // LD_B_A;
        // LD_A_addr(wBattleAnimTempYOffset);
        // ADD_A_B;
        // LD_B_A;
        uint8_t b = wram->wBattleAnimTempYCoord + wram->wBattleAnimTempYOffset;
        // PUSH_HL;
        // LD_A_hl;
        uint8_t y = *(hl++);
        // LD_HL(wBattleAnimTempOAMFlags);
        // BIT_hl(OAM_Y_FLIP);
        // IF_Z goto no_yflip;
        if(bit_test(wram->wBattleAnimTempOAMFlags, OAM_Y_FLIP)) {
            // ADD_A(0x8);
            // XOR_A(0xff);
            // INC_A;
            y = -(y + 0x8);
        }

    // no_yflip:
        // POP_HL;
        // ADD_A_B;
        // LD_de_A;
        de->yCoord = y + b;

    // X Coord
        // INC_HL;
        // INC_DE;
        // LD_A_addr(wBattleAnimTempXCoord);
        // LD_B_A;
        // LD_A_addr(wBattleAnimTempXOffset);
        // ADD_A_B;
        // LD_B_A;
        b = wram->wBattleAnimTempXCoord + wram->wBattleAnimTempXOffset;
        // PUSH_HL;
        // LD_A_hl;
        uint8_t x = *(hl++);
        // LD_HL(wBattleAnimTempOAMFlags);
        // BIT_hl(OAM_X_FLIP);
        // IF_Z goto no_xflip;
        if(bit_test(wram->wBattleAnimTempOAMFlags, OAM_X_FLIP)) {
            // ADD_A(0x8);
            // XOR_A(0xff);
            // INC_A;
            x = -(x + 0x8);
        }

    // no_xflip:
        // POP_HL;
        // ADD_A_B;
        // LD_de_A;
        de->xCoord = x + b;

    // Tile ID
        // INC_HL;
        // INC_DE;
        uint8_t tileID = *(hl++);
        // LD_A_addr(wBattleAnimTempTileID);
        // ADD_A(BATTLEANIM_BASE_TILE);
        // ADD_A_hl;
        // LD_de_A;
        de->tileID = wram->wBattleAnimTempTileID + BATTLEANIM_BASE_TILE + tileID;

    // Attributes
        // INC_HL;
        // INC_DE;
        // LD_A_addr(wBattleAnimTempOAMFlags);
        // LD_B_A;
        // LD_A_hl;
        uint8_t attr = *(hl++);
        // XOR_A_B;
        // AND_A(PRIORITY | Y_FLIP | X_FLIP);
        // LD_B_A;
        // LD_A_hl;
        // AND_A(OBP_NUM);
        // OR_A_B;
        // LD_B_A;
        // LD_A_addr(wBattleAnimTempPalette);
        // AND_A(PALETTE_MASK | VRAM_BANK_1);
        // OR_A_B;
        // LD_de_A;
        de->attributes = ((attr ^ wram->wBattleAnimTempOAMFlags) & (PRIORITY | Y_FLIP | X_FLIP)) | (attr & OBP_NUM) | (wram->wBattleAnimTempPalette & (PALETTE_MASK | VRAM_BANK_1));

        // INC_HL;
        // INC_DE;
        de++;
        // LD_A_E;
        // LD_addr_A(wBattleAnimOAMPointerLo);
        (*oamIndex)++;
        // CP_A(LOW(wVirtualOAMEnd));
        // IF_NC goto exit_set_carry;
        if(*oamIndex >= NUM_SPRITE_OAM_STRUCTS) {
        // exit_set_carry:
            // POP_BC;
            // SCF;
            // RET;
            return true;
        }
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // POP_BC;
    // goto done;

// delete:
    // CALL(aDeinitBattleAnimation);

// done:
    // AND_A_A;
    // RET;
    return false;
}

static void InitBattleAnimBuffer(struct BattleAnim* bc){
    // LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
    // ADD_HL_BC;
    // LD_A_hl;

    // AND_A(PRIORITY);
    // LD_addr_A(wBattleAnimTempOAMFlags);
    wram->wBattleAnimTempOAMFlags = bc->oamFlags & PRIORITY;
    // XOR_A_A;
    // LD_addr_A(wBattleAnimTempFrameOAMFlags);
    wram->wBattleAnimTempFrameOAMFlags = 0;
    // LD_HL(BATTLEANIMSTRUCT_PALETTE);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wBattleAnimTempPalette);
    wram->wBattleAnimTempPalette = bc->palette;
    // LD_HL(BATTLEANIMSTRUCT_FIX_Y);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wBattleAnimTempFixY);
    wram->wBattleAnimTempFixY = bc->fixY;
    // LD_HL(BATTLEANIMSTRUCT_TILEID);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_addr_A(wBattleAnimTempTileID);
    wram->wBattleAnimTempTileID = bc->tileId;
    // LD_A_hli;
    // LD_addr_A(wBattleAnimTempXCoord);
    wram->wBattleAnimTempXCoord = bc->xCoord;
    // LD_A_hli;
    // LD_addr_A(wBattleAnimTempYCoord);
    wram->wBattleAnimTempYCoord = bc->yCoord;
    // LD_A_hli;
    // LD_addr_A(wBattleAnimTempXOffset);
    wram->wBattleAnimTempXOffset = bc->xOffset;
    // LD_A_hli;
    // LD_addr_A(wBattleAnimTempYOffset);
    wram->wBattleAnimTempYOffset = bc->yOffset;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // RET_Z ;
    if(hram->hBattleTurn == TURN_PLAYER)
        return;

    // LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wBattleAnimTempOAMFlags);
    wram->wBattleAnimTempOAMFlags = bc->oamFlags;
    // BIT_hl(0);
    // RET_Z ;
    if(!bit_test(bc->oamFlags, 0))
        return;

    // LD_HL(BATTLEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_D_A;
    // LD_A((-10 * 8) + 4);
    // SUB_A_D;
    // LD_addr_A(wBattleAnimTempXCoord);
    wram->wBattleAnimTempXCoord = (uint8_t)(((-10 * 8) + 4) - bc->xCoord);
    // LD_A_hli;
    // LD_D_A;
    // LD_A_addr(wBattleAnimTempFixY);
    // CP_A(0xff);
    // IF_NZ goto check_kinesis_softboiled_milkdrink;
    if(wram->wBattleAnimTempFixY != 0xff) {
    // check_kinesis_softboiled_milkdrink:
        // SUB_A_D;
        // PUSH_AF;
        uint8_t d = wram->wBattleAnimTempFixY - bc->yCoord;
        // LD_A_addr(wFXAnimID + 1);
        // OR_A_A;
        // IF_NZ goto no_sub;
        // LD_A_addr(wFXAnimID);
        // CP_A(KINESIS);
        // IF_Z goto do_sub;
        // CP_A(SOFTBOILED);
        // IF_Z goto do_sub;
        // CP_A(MILK_DRINK);
        // IF_NZ goto no_sub;
        if(wram->wFXAnimID == KINESIS || wram->wFXAnimID == SOFTBOILED || wram->wFXAnimID == MILK_DRINK) {
        // do_sub:
            // POP_AF;
            // SUB_A(1 * 8);
            wram->wBattleAnimTempYCoord = d - (1 * 8);
            // goto done;
        }
        else {
        // no_sub:
            // POP_AF;
            wram->wBattleAnimTempYCoord = d;
        }
    }
    else {
        // LD_A(5 * 8);
        // ADD_A_D;
        // goto done;
        wram->wBattleAnimTempYCoord = bc->yCoord + (5 * 8);
    }

// done:
    // LD_addr_A(wBattleAnimTempYCoord);
    // LD_A_hli;
    // XOR_A(0xff);
    // INC_A;
    // LD_addr_A(wBattleAnimTempXOffset);
    wram->wBattleAnimTempXOffset = -bc->xOffset;
    // RET;
}

static uint8_t GetBattleAnimTileOffset(uint8_t a){
    // PUSH_HL;
    // PUSH_BC;
    // LD_HL(wBattleAnimTileDict);
    uint8_t* hl = wram->wBattleAnimTileDict;
    // LD_B_A;
    // LD_C(NUM_BATTLEANIMTILEDICT_ENTRIES);
    uint8_t c = NUM_BATTLEANIMTILEDICT_ENTRIES;

    do {
    // loop:
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto load;
        if(hl[0] == a) {
        // load:
            // LD_A_hl;
            return hl[1];
        }
        // INC_HL;
        hl += 2;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // XOR_A_A;
    // goto done;

// done:
    // POP_BC;
    // POP_HL;
    // RET;
    return 0;
}

void v_ExecuteBGEffects(void){
    // CALLFAR(aExecuteBGEffects);
    // RET;
    ExecuteBGEffects();
}

bool v_QueueBGEffect(void){
    // CALLFAR(aQueueBGEffect);
    // RET;
    return QueueBGEffect();
}
