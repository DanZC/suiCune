#include "../../constants.h"
#include "heal_machine_anim.h"
#include "../../home/palettes.h"
#include "../../home/tilemap.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/audio.h"

//  HealMachineAnim.Jumptable indexes
enum {
    HEALMACHINESTATE_LOADGFX,
    HEALMACHINESTATE_PCLOADBALLS,
    HEALMACHINESTATE_HOFLOADBALLS,
    HEALMACHINESTATE_PLAYMUSIC,
    HEALMACHINESTATE_HOFPLAYSFX,
    HEALMACHINESTATE_FINISH,
};

static void HealMachineAnim_DoJumptableFunctions(void);
static void HealMachineAnim_LoadPalettes(void);
static void HealMachineAnim_LoadGFX(void);
static void HealMachineAnim_PlaceHealingMachineTile(struct SpriteOAM* hl, const struct SpriteOAM* de);
static void HealMachineAnim_LoadBallsOntoMachine(struct SpriteOAM* hl, const struct SpriteOAM* de);
static void HealMachineAnim_FlashPalettes(void);
static void HealMachineAnim_FlashPalettes8Times(void);

void HealMachineAnim(void){
// If you have no Pokemon, don't change the buffer.  This can lead to some glitchy effects if you have no Pokemon.
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(wram->wPartyCount == 0)
        return;
// The location of the healing machine relative to the player is stored in wScriptVar.
// 0: Up and left (Pokemon Center)
// 1: Left (Elm's Lab)
// 2: Up (Hall of Fame)
    // LD_A_addr(wScriptVar);
    // LD_addr_A(wHealMachineAnimType);
    wram->wHealMachineAnimType = wram->wScriptVar;
    // LDH_A_addr(rOBP1);
    // LD_addr_A(wHealMachineTempOBP1);
    wram->wHealMachineTempOBP1 = gb_read(rOBP1);
    // CALL(aHealMachineAnim_DoJumptableFunctions);
    HealMachineAnim_DoJumptableFunctions();
    // LD_A_addr(wHealMachineTempOBP1);
    // CALL(aDmgToCgbObjPal1);
    DmgToCgbObjPal1_Conv(wram->wHealMachineTempOBP1);
    // RET;
    return;
}

static void HealMachineAnim_DoJumptableFunctions(void) {
    static const struct SpriteOAM PC_ElmsLab_OAM[] = {
        dbspriteoam(4, 4, 2, 0, 0x7c, PAL_OW_TREE | OBP_NUM),
        dbspriteoam(4, 4, 6, 0, 0x7c, PAL_OW_TREE | OBP_NUM),
        dbspriteoam(4, 4, 0, 6, 0x7d, PAL_OW_TREE | OBP_NUM),
        dbspriteoam(5, 4, 0, 6, 0x7d, PAL_OW_TREE | OBP_NUM | X_FLIP),
        dbspriteoam(4, 5, 0, 3, 0x7d, PAL_OW_TREE | OBP_NUM),
        dbspriteoam(5, 5, 0, 3, 0x7d, PAL_OW_TREE | OBP_NUM | X_FLIP),
        dbspriteoam(4, 6, 0, 0, 0x7d, PAL_OW_TREE | OBP_NUM),
        dbspriteoam(5, 6, 0, 0, 0x7d, PAL_OW_TREE | OBP_NUM | X_FLIP),
    };

    static const struct SpriteOAM HOF_OAM[] = {
        dbspriteoam(10, 7, 1, 4, 0x7d, PAL_OW_TREE | OBP_NUM),
        dbspriteoam(10, 7, 6, 4, 0x7d, PAL_OW_TREE | OBP_NUM),
        dbspriteoam( 9, 7, 5, 3, 0x7d, PAL_OW_TREE | OBP_NUM),
        dbspriteoam(11, 7, 2, 3, 0x7d, PAL_OW_TREE | OBP_NUM),
        dbspriteoam( 9, 7, 1, 1, 0x7d, PAL_OW_TREE | OBP_NUM),
        dbspriteoam(11, 7, 5, 1, 0x7d, PAL_OW_TREE | OBP_NUM)
    };

static const uint8_t Pokecenter[] = {HEALMACHINESTATE_LOADGFX, HEALMACHINESTATE_PCLOADBALLS, HEALMACHINESTATE_PLAYMUSIC, HEALMACHINESTATE_FINISH};
static const uint8_t ElmsLab[] = {HEALMACHINESTATE_LOADGFX, HEALMACHINESTATE_PCLOADBALLS, HEALMACHINESTATE_PLAYMUSIC, HEALMACHINESTATE_FINISH};
static const uint8_t HallOfFame[] = {HEALMACHINESTATE_LOADGFX, HEALMACHINESTATE_HOFLOADBALLS, HEALMACHINESTATE_HOFPLAYSFX, HEALMACHINESTATE_FINISH};

static const uint8_t* const Pointers[] = {
//  entries correspond to HEALMACHINE_* constants
    [HEALMACHINE_POKECENTER]    = Pokecenter,
    [HEALMACHINE_ELMS_LAB]      = ElmsLab,
    [HEALMACHINE_HALL_OF_FAME]  = HallOfFame,
};

    // XOR_A_A;
    // LD_addr_A(wHealMachineAnimState);
    wram->wHealMachineAnimState = 0;

    while(1) {
    // jumptable_loop:
        // LD_A_addr(wHealMachineAnimType);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mHealMachineAnim_Pointers);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_A_addr(wHealMachineAnimState);
        // LD_E_A;
        // INC_A;
        // LD_addr_A(wHealMachineAnimState);
        // ADD_HL_DE;
        uint8_t state = Pointers[wram->wHealMachineAnimType][wram->wHealMachineAnimState++];
        // LD_A_hl;
        // CP_A(HEALMACHINESTATE_FINISH);
        // IF_Z goto finish;
        if(state == HEALMACHINESTATE_FINISH)
            break;
        // LD_HL(mHealMachineAnim_Jumptable);
        // RST(aJumpTable);
//  entries correspond to HEALMACHINESTATE_* constants
        switch(state) {
            //dw ['.LoadGFX'];
            case HEALMACHINESTATE_LOADGFX: HealMachineAnim_LoadGFX(); break;
            //dw ['.PC_LoadBallsOntoMachine'];
            case HEALMACHINESTATE_PCLOADBALLS: {
            // PC_LoadBallsOntoMachine:
                // LD_HL(wVirtualOAMSprite32);
                struct SpriteOAM* hl = wram->wVirtualOAMSprite + 32;
                // LD_DE(mHealMachineAnim_PC_ElmsLab_OAM);
                const struct SpriteOAM* de = PC_ElmsLab_OAM;
                // CALL(aHealMachineAnim_PlaceHealingMachineTile);
                HealMachineAnim_PlaceHealingMachineTile(hl++, de++);
                // CALL(aHealMachineAnim_PlaceHealingMachineTile);
                HealMachineAnim_PlaceHealingMachineTile(hl++, de++);
                // goto LoadBallsOntoMachine;
                HealMachineAnim_LoadBallsOntoMachine(hl, de);
            } break;
            //dw ['.HOF_LoadBallsOntoMachine'];
            case HEALMACHINESTATE_HOFLOADBALLS: {
            // HOF_LoadBallsOntoMachine:
                // LD_HL(wVirtualOAMSprite32);
                struct SpriteOAM* hl = wram->wVirtualOAMSprite + 32;
                // LD_DE(mHealMachineAnim_HOF_OAM);
                const struct SpriteOAM* de = HOF_OAM;
                HealMachineAnim_LoadBallsOntoMachine(hl, de);
            } break;
            //dw ['.PlayHealMusic'];
            case HEALMACHINESTATE_PLAYMUSIC: {
            // PlayHealMusic:
                // LD_DE(MUSIC_HEAL);
                // CALL(aPlayMusic);
                PlayMusic_Conv(MUSIC_HEAL);
                // JP(mHealMachineAnim_FlashPalettes8Times);
                HealMachineAnim_FlashPalettes8Times();
            } break;
            //dw ['.HOF_PlaySFX'];
            case HEALMACHINESTATE_HOFPLAYSFX: {
            // HOF_PlaySFX:
                // LD_DE(SFX_GAME_FREAK_LOGO_GS);
                // CALL(aPlaySFX);
                PlaySFX_Conv(SFX_GAME_FREAK_LOGO_GS);
                // CALL(aHealMachineAnim_FlashPalettes8Times);
                HealMachineAnim_FlashPalettes8Times();
                // CALL(aWaitSFX);
                WaitSFX_Conv();
                // LD_DE(SFX_BOOT_PC);
                // CALL(aPlaySFX);
                PlaySFX_Conv(SFX_BOOT_PC);
                // RET;
            } break;
            //dw ['.dummy_5'];  // never encountered
            case HEALMACHINESTATE_FINISH:
                break;
        }
        // goto jumptable_loop;
    }


// finish:
    // RET;
    return;

// healmachineanimseq: MACRO
// rept _NARG
//     db HEALMACHINESTATE_\1
//     shift
// endr
// ENDM


// Jumptable:
//  entries correspond to HEALMACHINESTATE_* constants
    //dw ['.LoadGFX'];
    //dw ['.PC_LoadBallsOntoMachine'];
    //dw ['.HOF_LoadBallsOntoMachine'];
    //dw ['.PlayHealMusic'];
    //dw ['.HOF_PlaySFX'];
    //dw ['.dummy_5'];  // never encountered

// dummy_5:
    // RET;
}

static void HealMachineAnim_LoadPalettes(void) {
    static const char palettesPath[] = "gfx/overworld/heal_machine.pal";
    uint16_t buf[16];
    // CALL(aIsCGB);
    // IF_NZ goto cgb;
    if(!IsCGB_Conv()) {
        // LD_A(0b11100000);
        // LDH_addr_A(rOBP1);
        gb_write(rOBP1, 0b11100000);
        // RET;
        return;
    }

// cgb:
    LoadPaletteAssetColorsToArray(buf, palettesPath, 0, NUM_PAL_COLORS);
    // LD_HL(mHealMachineAnim_palettes);
    // LD_DE(wOBPals2 + PALETTE_SIZE * PAL_OW_TREE);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(wOBPals2));
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(wram->wOBPals2 + PALETTE_SIZE * PAL_OW_TREE, buf, PALETTE_SIZE);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hCGBPalUpdate = TRUE;
    // RET;
}

static void HealMachineAnim_LoadGFX(void){
    static const char HealMachineGFX[] = "gfx/overworld/heal_machine.png";
    // CALL(aHealMachineAnim_LoadPalettes);
    HealMachineAnim_LoadPalettes();
    // LD_DE(mHealMachineAnim_HealMachineGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x7c);
    // LD_BC((BANK(aHealMachineAnim_HealMachineGFX) << 8) | 2);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x7c, HealMachineGFX, 0, 2);
    // RET;
}

static void HealMachineAnim_PlaceHealingMachineTile(struct SpriteOAM* hl, const struct SpriteOAM* de){
    // PUSH_BC;
    // LD_A_addr(wHealMachineAnimType);
    // bcpixel2(2, 4);
    // CP_A(HEALMACHINE_ELMS_LAB);
    // IF_Z goto okay;
    // bcpixel2(0, 0);
    union Register bc = {.reg = (wram->wHealMachineAnimType == HEALMACHINE_ELMS_LAB)
        ? pixel2(2, 4)
        : pixel2(0, 0)};


// okay:
    // LD_A_de;
    // ADD_A_C;
    // INC_DE;
    // LD_hli_A;  // y
    hl->yCoord = de->yCoord + bc.lo;
    // LD_A_de;
    // ADD_A_B;
    // INC_DE;
    // LD_hli_A;  // x
    hl->xCoord = de->xCoord + bc.hi;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;  // tile id
    hl->tileID = de->tileID;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;  // attributes
    hl->attributes = de->attributes;
    // POP_BC;
    // RET;
}

static void HealMachineAnim_LoadBallsOntoMachine(struct SpriteOAM* hl, const struct SpriteOAM* de) {
    // LD_A_addr(wPartyCount);
    // LD_B_A;
    uint8_t b = wram->wPartyCount;

    do {
    // party_loop:
        // CALL(aHealMachineAnim_PlaceHealingMachineTile);
        HealMachineAnim_PlaceHealingMachineTile(hl++, de++);
        // PUSH_DE;
        // LD_DE(SFX_SECOND_PART_OF_ITEMFINDER);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_SECOND_PART_OF_ITEMFINDER);
        // POP_DE;
        // LD_C(30);
        // CALL(aDelayFrames);
        DelayFrames_Conv(25);
        // DEC_B;
        // IF_NZ goto party_loop;
    } while(--b != 0);
    // RET;
}

static void HealMachineAnim_FlashPalettes(void){
    // CALL(aIsCGB);
    // IF_NZ goto go;
    if(!IsCGB_Conv()) {
        // LDH_A_addr(rOBP1);
        // XOR_A(0b00101000);
        // LDH_addr_A(rOBP1);
        gb_write(rOBP1, gb_read(rOBP1) ^ 0b00101000);
        // RET;
        return;
    }

// go:
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wOBPals2));
    // LDH_addr_A(rSVBK);

    // LD_HL(wOBPals2 + PALETTE_SIZE * PAL_OW_TREE);
    uint8_t* hl = wram->wOBPals2 + PALETTE_SIZE * PAL_OW_TREE;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // PUSH_DE;
    uint16_t de = (hl[0]) | (hl[1] << 8);
    hl += 2;
    // LD_C(0x3);
    uint8_t c = 0x3;

    do {
    // palette_loop_2:
        // LD_A_hli;
        // LD_E_A;
        uint8_t e = hl[0];
        // LD_A_hld;
        // LD_D_A;
        uint8_t d = hl[1];
        // DEC_HL;
        // LD_A_D;
        // LD_hld_A;
        hl[-1] = d;
        // LD_A_E;
        // LD_hli_A;
        hl[-2] = e;
        // INC_HL;
        // INC_HL;
        // INC_HL;
        hl += 2;
        // DEC_C;
        // IF_NZ goto palette_loop_2;
    } while(--c != 0);
    // POP_DE;
    // DEC_HL;
    // LD_A_D;
    // LD_hld_A;
    hl[-1] = HIGH(de);
    // LD_A_E;
    // LD_hl_A;
    hl[-2] = LOW(de);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hCGBPalUpdate = TRUE;
    // RET;
}

static void HealMachineAnim_FlashPalettes8Times(void){
    // LD_C(8);
    uint8_t c = 8;

    do {
    // palette_loop:
        // PUSH_BC;
        // CALL(aHealMachineAnim_FlashPalettes);
        HealMachineAnim_FlashPalettes();
        // LD_C(10);
        // CALL(aDelayFrames);
        DelayFrames_Conv(10);
        // POP_BC;
        // DEC_C;
        // IF_NZ goto palette_loop;
    } while(--c != 0);
    // RET;
}
