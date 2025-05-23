#include "../../constants.h"
#include "sprites.h"
#include "../../home/sine.h"
#include "../../home/delay.h"
#include "../../home/clear_sprites.h"
#include "../../data/sprite_anims/framesets.h"
#include "../../data/sprite_anims/oam.h"
#include "../../data/sprite_anims/sequences.h"

static const struct OAMData* GetFrameOAMPointer(uint8_t a);

void ClearSpriteAnims(void){
    // LD_HL(wSpriteAnimData);
    // LD_BC(wSpriteAnimDataEnd - wSpriteAnimData);
    uint8_t* hl = wram->wSpriteAnimDict;
    uint16_t bc = wSpriteAnimDataEnd - wSpriteAnimData;

    do {
        // LD_hl(0);
        *(hl++) = 0;
        // INC_HL;
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto loop;
    } while(--bc != 0);
}

void PlaySpriteAnimationsAndDelayFrame(void){
    // CALL(aPlaySpriteAnimations);
    PlaySpriteAnimations();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void PlaySpriteAnimations(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // PUSH_AF;

    // LD_A(LOW(wVirtualOAM));
    // LD_addr_A(wCurSpriteOAMAddr);
    wram->wCurSpriteOAMAddr = LOW(wVirtualOAM);
    // CALL(aDoNextFrameForAllSprites);
    DoNextFrameForAllSprites();

    // POP_AF;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void DoNextFrameForAllSprites(void){
    // LD_HL(wSpriteAnimationStructs);
    struct SpriteAnim* hl = wram->wSpriteAnim;
    // LD_E(NUM_SPRITE_ANIM_STRUCTS);
    uint8_t e = NUM_SPRITE_ANIM_STRUCTS;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;  // This struct is deinitialized.
        if(hl->index == 0)  // This struct is deinitialized.
            continue;
        // LD_C_L;
        // LD_B_H;
        // REG_BC = SPRITEANIMSTRUCT_LENGTH*(hl - wram->wSpriteAnim) + wSpriteAnimationStructs;
        // PUSH_HL;
        // PUSH_DE;
        // CALL(aDoAnimFrame);  // Uses a massive dw
        DoAnimFrame(hl);
        // CALL(aUpdateAnimFrame);
        // POP_DE;
        // POP_HL;
        // IF_C return;
        if(UpdateAnimFrame(hl))
            return;


    // next:
        // LD_BC(SPRITEANIMSTRUCT_LENGTH);
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    } while(++hl, --e != 0);

    // LD_A_addr(wCurSpriteOAMAddr);
    // LD_L_A;
    // LD_H(HIGH(wVirtualOAM));
    uint16_t hl2 = (wVirtualOAM & 0xff00) | wram->wCurSpriteOAMAddr;

    while(LOW(hl2) < LOW(wVirtualOAMEnd)) {
    // loop2:
    //   //  Clear (wVirtualOAM + [wCurSpriteOAMAddr] --> wVirtualOAMEnd)
        // LD_A_L;
        // CP_A(LOW(wVirtualOAMEnd));
        // IF_NC goto done;
        // XOR_A_A;
        // LD_hli_A;
        gb_write(hl2++, 0);
        // goto loop2;
    }


// done:
    // RET;
}

void DoNextFrameForFirst16Sprites(void){
    // LD_HL(wSpriteAnimationStructs);
    struct SpriteAnim* hl = wram->wSpriteAnim;
    // LD_E(NUM_SPRITE_ANIM_STRUCTS);
    uint8_t e = NUM_SPRITE_ANIM_STRUCTS;

    do {
    // loop:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(hl->index != 0) {
            // LD_C_L;
            // LD_B_H;
            // PUSH_HL;
            // PUSH_DE;
            // CALL(aDoAnimFrame);  // Uses a massive dw
            DoAnimFrame(hl);
            // CALL(aUpdateAnimFrame);
            // POP_DE;
            // POP_HL;
            // IF_C goto done;
            if(UpdateAnimFrame(hl))
                return;
        }

    // next:
        // LD_BC(SPRITEANIMSTRUCT_LENGTH);
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    } while(hl++, --e != 0);

    // LD_A_addr(wCurSpriteOAMAddr);
    // LD_L_A;
    // LD_H(HIGH(wVirtualOAMSprite16));
    uint16_t hl2 = (wVirtualOAMSprite16 & 0xff00) | wram->wCurSpriteOAMAddr;

    while(LOW(hl2) < LOW(wVirtualOAMSprite16)) {
    // loop2:
    //   //  Clear (wVirtualOAM + [wCurSpriteOAMAddr] --> Sprites + $40)
        // LD_A_L;
        // CP_A(LOW(wVirtualOAMSprite16));
        // IF_NC goto done;
        // XOR_A_A;
        // LD_hli_A;
        gb_write(hl2++, 0x0);
        // goto loop2;
    }

// done:
    // RET;
}

//  Initialize animation a at pixel x=e, y=d
//  Find if there's any room in the wSpriteAnimationStructs array, which is 10x16
struct SpriteAnim* v_InitSpriteAnimStruct(uint8_t a, uint16_t de){
    // PUSH_DE;
    // PUSH_AF;
    // LD_HL(wSpriteAnimationStructs);
    // LD_E(NUM_SPRITE_ANIM_STRUCTS);
    struct SpriteAnim* hl = wram->wSpriteAnim;
    uint8_t e = NUM_SPRITE_ANIM_STRUCTS;

// loop:
    do {
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto found;
        if(hl->index == 0) {
        //  Back up the structure address to bc.
            // LD_C_L;
            // LD_B_H;
            struct SpriteAnim* bc = hl;

        //  Increment [wSpriteAnimCount], skipping a 0 value.
            // LD_HL(wSpriteAnimCount);
            // INC_hl;
            // LD_A_hl;
            // AND_A_A;
            // IF_NZ goto nonzero;
            // INC_hl;
            if(++wram->wSpriteAnimCount == 0)
                wram->wSpriteAnimCount++;
        
        //  Get row a of SpriteAnimSeqData, copy the pointer into de
            // POP_AF;
            // LD_E_A;
            // LD_D(0);
            // LD_HL(mSpriteAnimSeqData);
            // ADD_HL_DE;
            // ADD_HL_DE;
            // ADD_HL_DE;
            // LD_E_L;
            // LD_D_H;
            const struct SpriteSeqData *de2 = SpriteAnimSeqData + a;
        //  Set hl to the first field (field 0) in the current structure.
            // LD_HL(SPRITEANIMSTRUCT_INDEX);
            // ADD_HL_BC;
        //  Load the index.
            // LD_A_addr(wSpriteAnimCount);
            // LD_hli_A;  // SPRITEANIMSTRUCT_INDEX
            bc->index = wram->wSpriteAnimCount;
        //  Copy the table entry to the next two fields.
            // LD_A_de;
            // LD_hli_A;  // SPRITEANIMSTRUCT_FRAMESET_ID
            // INC_DE;
            bc->framesetID = de2->frameset;
            // LD_A_de;
            // LD_hli_A;  // SPRITEANIMSTRUCT_ANIM_SEQ_ID
            // INC_DE;
            bc->animSeqID = de2->sequence;
        //  Look up the third field in the wSpriteAnimDict mapping.
        //  Take the mapped value and load it in.
            // LD_A_de;
            // CALL(aGetSpriteAnimVTile);
            // LD_hli_A;  // SPRITEANIMSTRUCT_TILE_ID
            bc->tileID = GetSpriteAnimVTile(de2->tile);
            // POP_DE;
        //  Set hl to field 4 (X coordinate).  Kinda pointless, because we're presumably already here.
            // LD_HL(SPRITEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
        //  Load the original value of de into here.
            // LD_A_E;
            // LD_hli_A;  // SPRITEANIMSTRUCT_XCOORD
            // LD_A_D;
            // LD_hli_A;  // SPRITEANIMSTRUCT_YCOORD
            bc->xCoord = LOW(de);
            bc->yCoord = HIGH(de);
        //  load 0 into the next four fields
            // XOR_A_A;
            // LD_hli_A;  // SPRITEANIMSTRUCT_XOFFSET
            // LD_hli_A;  // SPRITEANIMSTRUCT_YOFFSET
            bc->xOffset = 0;
            bc->yOffset = 0;
            // XOR_A_A;
            // LD_hli_A;  // SPRITEANIMSTRUCT_DURATION
            // LD_hli_A;  // SPRITEANIMSTRUCT_DURATIONOFFSET
            bc->duration = 0;
            bc->durationOffset = 0;
        //  load -1 into the next field
            // DEC_A;
            // LD_hli_A;  // SPRITEANIMSTRUCT_FRAME
            bc->frameIndex = 0xff; // -1
        //  load 0 into the last five fields
            // XOR_A_A;
            // LD_hli_A;  // SPRITEANIMSTRUCT_JUMPTABLE_INDEX
            // LD_hli_A;  // SPRITEANIMSTRUCT_VAR1
            // LD_hli_A;  // SPRITEANIMSTRUCT_VAR2
            // LD_hli_A;  // SPRITEANIMSTRUCT_VAR3
            // LD_hl_A;  // SPRITEANIMSTRUCT_VAR4
            bc->jumptableIndex = 0;
            bc->var1 = 0;
            bc->var2 = 0;
            bc->var3 = 0;
            bc->var4 = 0;
        //  back up the address of the first field to wSpriteAnimAddrBackup
            // LD_A_C;
            // LD_addr_A(wSpriteAnimAddrBackup);
            // LD_A_B;
            // LD_addr_A(wSpriteAnimAddrBackup + 1);
            wram->wSpriteAnimAddrBackup = wSpriteAnimationStructs + ((int)(bc - wram->wSpriteAnim) * SPRITEANIMSTRUCT_LENGTH);
            return bc;
            // RET;
        }
        // LD_BC(SPRITEANIMSTRUCT_LENGTH);
        // ADD_HL_BC;
        hl++;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
//  We've reached the end.  There is no more room here.
//  Return carry.
    // POP_AF;
    // POP_DE;
    // SCF;
    // RET;
    return NULL;
}

//  Clear the index field of the struct in bc.
void DeinitializeSprite(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_INDEX);
    // ADD_HL_BC;
    // LD_hl(0);
    // RET;
    bc->index = 0;
}

//  Clear the index field of every struct in the wSpriteAnimationStructs array.
void DeinitializeAllSprites(void){
    // LD_HL(wSpriteAnimationStructs);
    // LD_BC(SPRITEANIMSTRUCT_LENGTH);
    // LD_E(NUM_SPRITE_ANIM_STRUCTS);
    // XOR_A_A;

    for(uint8_t e = 0; e < NUM_SPRITE_ANIM_STRUCTS; ++e) {
    // loop:
        // LD_hl_A;
        wram->wSpriteAnim[e].index = 0;
        // ADD_HL_BC;
        // DEC_E;
        // IF_NZ goto loop;
    }
    // RET;

}

bool UpdateAnimFrame(struct SpriteAnim* bc){
    // CALL(aInitSpriteAnimBuffer);  // init WRAM
    InitSpriteAnimBuffer(bc);
    // CALL(aGetSpriteAnimFrame);  // read from a memory array
    uint8_t a = GetSpriteAnimFrame(bc);
    // CP_A(dowait_command);
    // IF_Z goto done;
    if(a == dowait_command)
        return false; // and a, a 
                      // ret
    // CP_A(delanim_command);
    // IF_Z goto delete;
    if(a == delanim_command) {
    // delete:
        // CALL(aDeinitializeSprite);
        DeinitializeSprite(bc);

    // done:
        // AND_A_A;
        // RET;
        return false;
    }
    // CALL(aGetFrameOAMPointer);
    const struct OAMData* oam = GetFrameOAMPointer(a);
// add byte to [wCurAnimVTile]
    // LD_A_addr(wCurAnimVTile);
    // ADD_A_hl;
    // LD_addr_A(wCurAnimVTile);
    // INC_HL;
    wram->wCurAnimVTile += oam->vtile_offset;
// load pointer into hl
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const uint8_t* hl = oam->ptr;
    // PUSH_BC;
    // LD_A_addr(wCurSpriteOAMAddr);
    // LD_E_A;
    // LD_D(HIGH(wVirtualOAM));
    uint16_t de = (wVirtualOAM & 0xff00) | wram->wCurSpriteOAMAddr;
    // LD_A_hli;
    // LD_C_A;  // number of objects
    uint8_t c = *(hl++);

    do {
    // loop:
    // first byte: y (px)
    // [de] = [wCurAnimYCoord] + [wCurAnimYOffset] + [wGlobalAnimYOffset] + AddOrSubtractY([hl])
        // LD_A_addr(wCurAnimYCoord);
        // LD_B_A;
        // LD_A_addr(wCurAnimYOffset);
        // ADD_A_B;
        // LD_B_A;
        // LD_A_addr(wGlobalAnimYOffset);
        // ADD_A_B;
        // LD_B_A;
        // CALL(aAddOrSubtractY);
        // ADD_A_B;
        // LD_de_A;
        gb_write(de++, wram->wCurAnimYCoord + wram->wCurAnimYOffset + wram->wGlobalAnimYOffset + AddOrSubtractY(hl++));
        // INC_HL;
        // INC_DE;
    // second byte: x (px)
    // [de] = [wCurAnimXCoord] + [wCurAnimXOffset] + [wGlobalAnimXOffset] + AddOrSubtractX([hl])
        // LD_A_addr(wCurAnimXCoord);
        // LD_B_A;
        // LD_A_addr(wCurAnimXOffset);
        // ADD_A_B;
        // LD_B_A;
        // LD_A_addr(wGlobalAnimXOffset);
        // ADD_A_B;
        // LD_B_A;
        // CALL(aAddOrSubtractX);
        // ADD_A_B;
        // LD_de_A;
        gb_write(de++, wram->wCurAnimXCoord + wram->wCurAnimXOffset + wram->wGlobalAnimXOffset + AddOrSubtractX(hl++));
        // INC_HL;
        // INC_DE;
    // third byte: vtile
    // [de] = [wCurAnimVTile] + [hl]
        // LD_A_addr(wCurAnimVTile);
        // ADD_A_hl;
        // LD_de_A;
        gb_write(de++, wram->wCurAnimVTile + *(hl++));
        // INC_HL;
        // INC_DE;
    // fourth byte: attributes
    // [de] = GetSpriteOAMAttr([hl])
        // CALL(aGetSpriteOAMAttr);
        // LD_de_A;
        gb_write(de++, GetSpriteOAMAttr(hl++));
        // INC_HL;
        // INC_DE;
        // LD_A_E;
        // LD_addr_A(wCurSpriteOAMAddr);
        wram->wCurSpriteOAMAddr = LOW(de);
        // CP_A(LOW(wVirtualOAMEnd));
        // IF_NC goto reached_the_end;
        if(LOW(de) >= LOW(wVirtualOAMEnd)) {
        // reached_the_end:
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
    return false;
}

uint8_t AddOrSubtractY(const uint8_t* hl){
    // PUSH_HL;
    // LD_A_hl;
    uint8_t a = *hl;
    // LD_HL(wCurSpriteOAMFlags);
    // BIT_hl(OAM_Y_FLIP);
    // IF_Z goto ok;
    if(!bit_test(wram->wCurSpriteOAMFlags, OAM_Y_FLIP))
        return a;
// -8 - a
    // ADD_A(8);
    // XOR_A(0xff);
    // INC_A;
    a = ((a + 8) ^ 0xff) + 1;

// ok:
    // POP_HL;
    // RET;
    return a;
}

uint8_t AddOrSubtractX(const uint8_t* hl){
    // PUSH_HL;
    // LD_A_hl;
    uint8_t a = *hl;
    // LD_HL(wCurSpriteOAMFlags);
    // BIT_hl(OAM_X_FLIP);
    // IF_Z goto ok;
    if(!bit_test(wram->wCurSpriteOAMFlags, OAM_X_FLIP))
        return a;
// -8 - a
    // ADD_A(8);
    // XOR_A(0xff);
    // INC_A;
    a = ((a + 8) ^ 0xff) + 1;

// ok:
    // POP_HL;
    // RET;
    return a;
}

uint8_t GetSpriteOAMAttr(const uint8_t* hl){
    // LD_A_addr(wCurSpriteOAMFlags);
    // LD_B_A;
    // LD_A_hl;
    // XOR_A_B;
    // AND_A(PRIORITY | Y_FLIP | X_FLIP);
    // LD_B_A;
    // LD_A_hl;
    // AND_A(~(PRIORITY | Y_FLIP | X_FLIP));
    // OR_A_B;
    // RET;
    return ((wram->wCurSpriteOAMFlags ^ (*hl)) & (PRIORITY | Y_FLIP | X_FLIP)) | ((*hl) & ~(PRIORITY | Y_FLIP | X_FLIP));
}

void InitSpriteAnimBuffer(struct SpriteAnim* bc){
    // XOR_A_A;
    // LD_addr_A(wCurSpriteOAMFlags);
    wram->wCurSpriteOAMFlags = 0;
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_addr_A(wCurAnimVTile);
    wram->wCurAnimVTile = bc->tileID;
    // LD_A_hli;
    // LD_addr_A(wCurAnimXCoord);
    wram->wCurAnimXCoord = bc->xCoord;
    // LD_A_hli;
    // LD_addr_A(wCurAnimYCoord);
    wram->wCurAnimYCoord = bc->yCoord;
    // LD_A_hli;
    // LD_addr_A(wCurAnimXOffset);
    wram->wCurAnimXOffset = bc->xOffset;
    // LD_A_hli;
    // LD_addr_A(wCurAnimYOffset);
    wram->wCurAnimYOffset = bc->yOffset;
    // RET;
}

//  a = wSpriteAnimDict[a] if a in wSpriteAnimDict else vtile offset $00
uint8_t GetSpriteAnimVTile(uint8_t a){
    // PUSH_HL;
    // PUSH_BC;
    // LD_HL(wSpriteAnimDict);
    // LD_B_A;
    // LD_C(NUM_SPRITEANIMDICT_ENTRIES);
    uint8_t* hl = wram->wSpriteAnimDict;
    uint8_t c = NUM_SPRITEANIMDICT_ENTRIES;

// loop:
    do {
        // LD_A_hli;
        uint8_t key = *(hl++);
        // CP_A_B;
        // IF_Z goto ok;
        if(key == a) {
            // LD_A_hl;
            return *hl;
        }
        // INC_HL;
        hl++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // XOR_A_A;
    return 0;
// done:
    // POP_BC;
    // POP_HL;
    // RET;
}

void v_ReinitSpriteAnimFrame(struct SpriteAnim* bc, uint8_t a){
    // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->framesetID = a;
    // LD_HL(SPRITEANIMSTRUCT_DURATION);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->duration = 0;
    // LD_HL(SPRITEANIMSTRUCT_FRAME);
    // ADD_HL_BC;
    // LD_hl(-1);
    bc->frameIndex = 0xff; // -1
}

static const uint8_t* GetSpriteAnimFrame_GetPointer(struct SpriteAnim* bc) {
    // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mSpriteAnimFrameData);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // uint16_t de = gb_read16(mSpriteAnimFrameData + 2*bc->framesetID);
    const uint8_t* de = SpriteAnimFrameData[bc->framesetID];
    // printf("SpriteAnimFrame: %02X:%02X vs %02X:%02X\n", 
    //     gb_read(de + 2*bc->frameIndex), 
    //     gb_read(de + 2*bc->frameIndex + 1), 
    //     SpriteAnimFrameData[bc->framesetID][2*bc->frameIndex],
    //     SpriteAnimFrameData[bc->framesetID][2*bc->frameIndex + 1]);
    // LD_HL(SPRITEANIMSTRUCT_FRAME);
    // ADD_HL_BC;
    // LD_L_hl;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_DE;
    // RET;
    return de + 2*bc->frameIndex;
}

uint8_t GetSpriteAnimFrame(struct SpriteAnim* bc){
    const uint8_t* hl;
    uint8_t a;
// loop:
    while(1)
    {
        // LD_HL(SPRITEANIMSTRUCT_DURATION);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next_frame;
        if(bc->duration == 0) {
        // next_frame:
            // LD_HL(SPRITEANIMSTRUCT_FRAME);
            // ADD_HL_BC;
            // INC_hl;
            bc->frameIndex++;
            // CALL(aGetSpriteAnimFrame_GetPointer);
            hl = GetSpriteAnimFrame_GetPointer(bc);
            // LD_A_hli;
            a = *(hl++);
            // CP_A(dorestart_command);
            // IF_Z goto restart;
            if(a == dorestart_command) {
            // restart:
                // XOR_A_A;
                // LD_HL(SPRITEANIMSTRUCT_DURATION);
                // ADD_HL_BC;
                // LD_hl_A;
                bc->duration = 0;

                // DEC_A;
                // LD_HL(SPRITEANIMSTRUCT_FRAME);
                // ADD_HL_BC;
                // LD_hl_A;
                bc->frameIndex = 0xff;
                // goto loop;
                continue;
            }
            // CP_A(endanim_command);
            // IF_Z goto repeat_last;
            if(a == endanim_command) {
            // repeat_last:
                // XOR_A_A;
                // LD_HL(SPRITEANIMSTRUCT_DURATION);
                // ADD_HL_BC;
                // LD_hl_A;
                bc->duration = 0;

                // LD_HL(SPRITEANIMSTRUCT_FRAME);
                // ADD_HL_BC;
                // DEC_hl;
                // DEC_hl;
                bc->frameIndex -= 2;
                continue;
                // goto loop;
            }

            // PUSH_AF;
            // LD_A_hl;
            uint8_t a2 = *(hl);
            // PUSH_HL;
            // AND_A(~(Y_FLIP << 1 | X_FLIP << 1));
            // LD_HL(SPRITEANIMSTRUCT_DURATIONOFFSET);
            // ADD_HL_BC;
            // ADD_A_hl;
            // LD_HL(SPRITEANIMSTRUCT_DURATION);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->duration = (a2 & ~(Y_FLIP << 1 | X_FLIP << 1)) + bc->durationOffset;
            // POP_HL;
        }
        else {
            // DEC_hl;
            bc->duration--;
            // CALL(aGetSpriteAnimFrame_GetPointer);
            // LD_A_hli;
            hl = GetSpriteAnimFrame_GetPointer(bc);
            a = *(hl++);
            // PUSH_AF;
            // goto okay;
        }

    // okay:
        // LD_A_hl;
        // AND_A(Y_FLIP << 1 | X_FLIP << 1);  // The << 1 is compensated in the "frame" macro
        // SRL_A;
        // LD_addr_A(wCurSpriteOAMFlags);
        wram->wCurSpriteOAMFlags = (*(hl) & (Y_FLIP << 1 | X_FLIP << 1)) >> 1;
        // POP_AF;
        // RET;
        return a;
    }
}

static const struct OAMData* GetFrameOAMPointer(uint8_t a){
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSpriteAnimOAMData);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // RET;
    return SpriteAnimOAMData + a;
}

void UnusedLoadSpriteAnimGFX(void){
//  //  unreferenced
    PUSH_HL;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mUnusedSpriteAnimGFX);
    ADD_HL_DE;
    LD_C_hl;
    INC_HL;
    LD_B_hl;
    INC_HL;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    POP_HL;
    PUSH_BC;
    CALL(aRequest2bpp);
    POP_BC;
    RET;

// INCLUDE "data/sprite_anims/sequences.asm"

// INCLUDE "engine/gfx/sprite_anims.asm"

// INCLUDE "data/sprite_anims/framesets.asm"

// INCLUDE "data/sprite_anims/oam.asm"

// INCLUDE "data/sprite_anims/unused_gfx.asm"

}

static void AnimateEndOfExpBar_AnimateFrame(uint8_t d){
    // LD_HL(wVirtualOAMSprite00);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;
    // LD_C(8);  // number of animated circles
    uint8_t c = 8;

    while(c != 0){
    // anim_loop:
        // LD_A_C;
        // AND_A_A;
        // RET_Z ;
        // DEC_C;
        // LD_A_C;
        uint8_t a = --c;
    //  multiply by 8
        // SLA_A;
        // SLA_A;
        // SLA_A;
        // PUSH_AF;
        a <<= 3;

        // PUSH_DE;
        // PUSH_HL;
        // CALL(aSprites_Sine);
        // POP_HL;
        // POP_DE;
        // ADD_A(13 * TILE_WIDTH);
        // LD_hli_A;  // y
        hl->yCoord = Sine(a, d) + (13 * TILE_WIDTH);

        // POP_AF;
        // PUSH_DE;
        // PUSH_HL;
        // CALL(aSprites_Cosine);
        // POP_HL;
        // POP_DE;
        // ADD_A(10 * TILE_WIDTH + 4);
        // LD_hli_A;  // x
        hl->xCoord = Cosine(a, d) + (10 * TILE_WIDTH + 4);

        // LD_A(0x0);
        // LD_hli_A;  // tile id
        hl->tileID = 0x0;
        // LD_A(PAL_BATTLE_OB_BLUE);
        // LD_hli_A;  // attributes
        hl->attributes = PAL_BATTLE_OB_BLUE;
        hl++;
        // goto anim_loop;
    }
}

void AnimateEndOfExpBar(void){
    // LDH_A_addr(hSGB);
    // LD_DE(mEndOfExpBarGFX);
    // AND_A_A;
    // IF_Z goto load;
    // LD_DE(mSGBEndOfExpBarGFX);
    const char* de = (hram.hSGB == 0)? EndOfExpBarGFX: SGBEndOfExpBarGFX;

// load:
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    // LD_BC((BANK(aEndOfExpBarGFX) << 8) | 1);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, de, 0, 1);
    // LD_C(8);
    uint8_t c = 8;
    // LD_D(0);
    uint8_t d = 0;

    do {
    // loop:
        // PUSH_BC;
        // CALL(aAnimateEndOfExpBar_AnimateFrame);
        AnimateEndOfExpBar_AnimateFrame(d);
        // CALL(aDelayFrame);
        DelayFrame();
        // POP_BC;
        // INC_D;
        // INC_D;
        d += 2;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // CALL(aClearSprites);
    ClearSprites();
    // RET;
}

const char EndOfExpBarGFX[] = "gfx/battle/expbarend.png";
const char SGBEndOfExpBarGFX[] = "gfx/battle/expbarend_sgb.png";

void ClearSpriteAnims2(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // PUSH_AF;
    // LD_HL(wSpriteAnimData);
    // LD_BC(wSpriteAnimDataEnd - wSpriteAnimData);
    uint8_t* hl = wram->wSpriteAnimDict;
    uint32_t i = 0;

// loop:
    do {
        // LD_hl(0);
        hl[i] = 0;
        // INC_HL;
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto loop;
    } while(++i != wSpriteAnimDataEnd - wSpriteAnimData);
    // POP_AF;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}
