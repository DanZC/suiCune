#include "../../constants.h"
#include "pic_animation.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/text.h"
#include "dma_transfer.h"
#include "../gfx/load_pics.h"
#include "../../gfx/pokemon/anims.h"
#include "../../gfx/pokemon/idles.h"
#include "../../gfx/pokemon/unown_anims.h"
#include "../../gfx/pokemon/unown_idles.h"
#include <stddef.h>

//  Pic animation arrangement.
#pragma pack(push, 1)
struct PokeAnim {
    uint8_t sceneIndex;
    uint16_t pointer;
    species_t species;
    uint8_t unownLetter;
    uint8_t speciesOrUnown;
    uint8_t graphicStartTile;
    uint16_t coord;
    uint8_t frontpicHeight;
    uint8_t idleFlag;
    uint8_t speed;
    uint8_t pointerBank;
    uint16_t pointerAddr;
    uint8_t framesBank;
    uint16_t framesAddr;
    uint8_t bitmaskBank;
    uint16_t bitmaskAddr;
    uint8_t frame;
    uint8_t jumptableIndex;
    uint8_t repeatTimer;
    uint8_t curBitmask;
    uint8_t waitCounter;
    uint8_t command;
    uint8_t parameter;
    uint8_t unused[1];
    uint8_t bitmaskCurCol;
    uint8_t bitmaskCurRow;
    uint8_t bitmaskCurBit;
    uint8_t bitmaskBuffer[7];
    uint8_t unused2[2];
};
#pragma pack(pop)

#define get_wram_raw_offset_ptr(_x) (gb.wram + ((WRAM_BANK_SIZE * MBANK(a##_x)) + _x - WRAM_1_ADDR))
struct PokeAnim* const pokeAnim = (struct PokeAnim*)get_wram_raw_offset_ptr(wPokeAnimStruct);

static const uint8_t* lPokeAnimPointer;
static uint8_t* lPokeAnimCoord;
static const uint8_t* lPokeAnimPointerAddr;

void Unused_AnimateMon_Slow_Normal(void){
    hlcoord(12, 0, wTilemap);
    LD_A_addr(wBattleMode);
    CP_A(WILD_BATTLE);
    IF_Z goto wild;
    LD_E(ANIM_MON_SLOW);
    LD_D(0x0);
    CALL(aAnimateFrontpic);
    RET;


wild:
    LD_E(ANIM_MON_NORMAL);
    LD_D(0x0);
    CALL(aAnimateFrontpic);
    RET;

}

void AnimateMon_Menu(void){
    LD_E(ANIM_MON_MENU);
    LD_D(0x0);
    CALL(aAnimateFrontpic);
    RET;

}

void AnimateMon_Menu_Conv(uint8_t* hl){
    // LD_E(ANIM_MON_MENU);
    // LD_D(0x0);
    // CALL(aAnimateFrontpic);
    // RET;
    return AnimateFrontpic_Conv(hl, 0x0, ANIM_MON_MENU);
}

void AnimateMon_Trade(void){
    LD_E(ANIM_MON_TRADE);
    LD_D(0x0);
    CALL(aAnimateFrontpic);
    RET;

}

void AnimateMon_Trade_Conv(uint8_t* hl){
    // LD_E(ANIM_MON_TRADE);
    // LD_D(0x0);
    // CALL(aAnimateFrontpic);
    // RET;
    return AnimateFrontpic_Conv(hl, 0x0, ANIM_MON_TRADE);
}

void AnimateMon_Evolve(void){
    LD_E(ANIM_MON_EVOLVE);
    LD_D(0x0);
    CALL(aAnimateFrontpic);
    RET;

}

void AnimateMon_Evolve_Conv(uint8_t* hl){
    // LD_E(ANIM_MON_EVOLVE);
    // LD_D(0x0);
    // CALL(aAnimateFrontpic);
    // RET;
    return AnimateFrontpic_Conv(hl, 0x0, ANIM_MON_EVOLVE);
}

void AnimateMon_Hatch(void){
    LD_E(ANIM_MON_HATCH);
    LD_D(0x0);
    CALL(aAnimateFrontpic);
    RET;

}

void AnimateMon_Hatch_Conv(uint8_t* hl){
    // LD_E(ANIM_MON_HATCH);
    // LD_D(0x0);
    // CALL(aAnimateFrontpic);
    // RET;
    return AnimateFrontpic_Conv(hl, 0x0, ANIM_MON_HATCH);
}

void AnimateMon_HOF(void){
    LD_E(ANIM_MON_HOF);
    LD_D(0x0);
    CALL(aAnimateFrontpic);
    RET;
}

#define setup_command(_x) _x##_SetupCommand
#define add_setup_command(_x) [_x##_SetupCommand] = _x

enum {
    setup_command(PokeAnim_Finish),
    setup_command(PokeAnim_BasePic),
    setup_command(PokeAnim_SetWait),
    setup_command(PokeAnim_Wait),
    setup_command(PokeAnim_Setup),
    setup_command(PokeAnim_Setup2),
    setup_command(PokeAnim_Idle),
    setup_command(PokeAnim_Play),
    setup_command(PokeAnim_Play2),
    setup_command(PokeAnim_Cry),
    setup_command(PokeAnim_CryNoWait),
    setup_command(PokeAnim_StereoCry),
};

void (*const PokeAnim_SetupCommands[])(void) = {
    add_setup_command(PokeAnim_Finish),
    add_setup_command(PokeAnim_BasePic),
    add_setup_command(PokeAnim_SetWait),
    add_setup_command(PokeAnim_Wait),
    add_setup_command(PokeAnim_Setup),
    add_setup_command(PokeAnim_Setup2),
    add_setup_command(PokeAnim_Idle),
    add_setup_command(PokeAnim_Play),
    add_setup_command(PokeAnim_Play2),
    add_setup_command(PokeAnim_Cry),
    add_setup_command(PokeAnim_CryNoWait),
    add_setup_command(PokeAnim_StereoCry),
};

// pokeanim: MACRO
// rept _NARG
//     db (PokeAnim_\1_SetupCommand - PokeAnim_SetupCommands) / 2
//     shift
// endr
//     db (PokeAnim_Finish_SetupCommand - PokeAnim_SetupCommands) / 2
// ENDM

#define pokeanim1(_x) PokeAnim_##_x##_SetupCommand
#define pokeanim2(_1, _2) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand
#define pokeanim3(_1, _2, _3) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand, PokeAnim_##_3##_SetupCommand
#define pokeanim4(_1, _2, _3, _4) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand, PokeAnim_##_3##_SetupCommand, PokeAnim_##_4##_SetupCommand
#define pokeanim5(_1, _2, _3, _4, _5) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand, PokeAnim_##_3##_SetupCommand, PokeAnim_##_4##_SetupCommand, PokeAnim_##_5##_SetupCommand
#define pokeanim6(_1, _2, _3, _4, _5, _6) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand, PokeAnim_##_3##_SetupCommand, PokeAnim_##_4##_SetupCommand, PokeAnim_##_5##_SetupCommand, PokeAnim_##_6##_SetupCommand
#define pokeanim7(_1, _2, _3, _4, _5, _6, _7) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand, PokeAnim_##_3##_SetupCommand, PokeAnim_##_4##_SetupCommand, PokeAnim_##_5##_SetupCommand, PokeAnim_##_6##_SetupCommand, PokeAnim_##_7##_SetupCommand
#define pokeanim8(_1, _2, _3, _4, _5, _6, _7, _8) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand, PokeAnim_##_3##_SetupCommand, PokeAnim_##_4##_SetupCommand, PokeAnim_##_5##_SetupCommand, PokeAnim_##_6##_SetupCommand, PokeAnim_##_7##_SetupCommand, PokeAnim_##_8##_SetupCommand
#define pokeanim9(_1, _2, _3, _4, _5, _6, _7, _8, _9) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand, PokeAnim_##_3##_SetupCommand, PokeAnim_##_4##_SetupCommand, PokeAnim_##_5##_SetupCommand, PokeAnim_##_6##_SetupCommand, PokeAnim_##_7##_SetupCommand, PokeAnim_##_8##_SetupCommand, PokeAnim_##_9##_SetupCommand
#define pokeanim10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) PokeAnim_##_1##_SetupCommand, PokeAnim_##_2##_SetupCommand, PokeAnim_##_3##_SetupCommand, PokeAnim_##_4##_SetupCommand, PokeAnim_##_5##_SetupCommand, PokeAnim_##_6##_SetupCommand, PokeAnim_##_7##_SetupCommand, PokeAnim_##_8##_SetupCommand, PokeAnim_##_9##_SetupCommand, PokeAnim_##_10##_SetupCommand
#define overloadselect10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME
#define pokeanim(...) overloadselect10(__VA_ARGS__, pokeanim10, pokeanim9, pokeanim8, pokeanim7, pokeanim6, pokeanim5, pokeanim4, pokeanim3, pokeanim2, pokeanim1)(__VA_ARGS__), PokeAnim_Finish_SetupCommand


const uint8_t* PokeAnims[] = {
    [ANIM_MON_SLOW] = (uint8_t[]){PokeAnim_StereoCry_SetupCommand, PokeAnim_Setup2_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand},
    [ANIM_MON_NORMAL] = (uint8_t[]){PokeAnim_StereoCry_SetupCommand, PokeAnim_Setup_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand},
    [ANIM_MON_MENU] = (uint8_t[]){PokeAnim_CryNoWait_SetupCommand, PokeAnim_Setup_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_SetWait_SetupCommand, PokeAnim_Wait_SetupCommand, PokeAnim_Idle_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand},
    [ANIM_MON_TRADE] = (uint8_t[]){PokeAnim_Idle_SetupCommand, PokeAnim_Play2_SetupCommand, PokeAnim_Idle_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_SetWait_SetupCommand, PokeAnim_Wait_SetupCommand, PokeAnim_Cry_SetupCommand, PokeAnim_Setup_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand},
    [ANIM_MON_EVOLVE] = (uint8_t[]){PokeAnim_Idle_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_SetWait_SetupCommand, PokeAnim_Wait_SetupCommand, PokeAnim_CryNoWait_SetupCommand, PokeAnim_Setup_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand},
    [ANIM_MON_HATCH] = (uint8_t[]){PokeAnim_Idle_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_CryNoWait_SetupCommand, PokeAnim_Setup_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_SetWait_SetupCommand, PokeAnim_Wait_SetupCommand, PokeAnim_Idle_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand},
    [ANIM_MON_HOF] = (uint8_t[]){PokeAnim_CryNoWait_SetupCommand, PokeAnim_Setup_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_SetWait_SetupCommand, PokeAnim_Wait_SetupCommand, PokeAnim_Idle_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand},
    [ANIM_MON_EGG1] = (uint8_t[]){PokeAnim_Setup_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand},
    [ANIM_MON_EGG2] = (uint8_t[]){PokeAnim_Idle_SetupCommand, PokeAnim_Play_SetupCommand, PokeAnim_Finish_SetupCommand}
};

// void PokeAnims(void){
// //  entries correspond to ANIM_MON_* constants
//     //dw ['.Slow'];
//     //dw ['.Normal'];
//     //dw ['.Menu'];
//     //dw ['.Trade'];
//     //dw ['.Evolve'];
//     //dw ['.Hatch'];
//     //dw ['.HOF'];
//     //dw ['.Egg1'];
//     //dw ['.Egg2'];


// Slow:
// //   pokeanim StereoCry, Setup2, Play

// Normal:
// // pokeanim StereoCry, Setup, Play

// Menu:
// //   pokeanim CryNoWait, Setup, Play, SetWait, Wait, Idle, Play

// Trade:
// //  pokeanim Idle, Play2, Idle, Play, SetWait, Wait, Cry, Setup, Play

// Evolve:
// // pokeanim Idle, Play, SetWait, Wait, CryNoWait, Setup, Play

// Hatch:
// //  pokeanim Idle, Play, CryNoWait, Setup, Play, SetWait, Wait, Idle, Play

// HOF:    pokeanim:
// // CryNoWait, Setup, Play, SetWait, Wait, Idle, Play

// Egg1:
// //   pokeanim Setup, Play

// Egg2:
// //   pokeanim Idle, Play

//     return AnimateFrontpic();
// }

void AnimateFrontpic(void){
    CALL(aAnimateMon_CheckIfPokemon);
    RET_C ;
    CALL(aLoadMonAnimation);

loop:
    CALL(aSetUpPokeAnim);
    PUSH_AF;
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    POP_AF;
    IF_NC goto loop;
    RET;

}

void AnimateFrontpic_Conv(uint8_t* hl, uint8_t d, uint8_t e){
    // CALL(aAnimateMon_CheckIfPokemon);
    // RET_C ;
    if(!AnimateMon_CheckIfPokemon_Conv())
        return;
    // CALL(aLoadMonAnimation);
    LoadMonAnimation_Conv(hl, d, e);

    bool done = false;
    do {
    // loop:
        // CALL(aSetUpPokeAnim);
        done = SetUpPokeAnim_Conv();
        // PUSH_AF;
        // FARCALL(aHDMATransferTilemapToWRAMBank3);
        // POP_AF;
        HDMATransferTilemapToWRAMBank3_Conv();
        // IF_NC goto loop;
    } while(!done);
    // RET;
}

void LoadMonAnimation(void){
    PUSH_HL;
    LD_C_E;
    LD_B(0);
    LD_HL(mPokeAnims);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_B_hl;
    LD_C_A;
    POP_HL;
    CALL(aPokeAnim_InitPicAttributes);
    RET;

}

void LoadMonAnimation_Conv(uint8_t* hl, uint8_t d, uint8_t e){
    // PUSH_HL;
    // LD_C_E;
    // LD_B(0);
    // LD_HL(mPokeAnims);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_B_hl;
    // LD_C_A;
    const uint8_t* bc = PokeAnims[e];
    // POP_HL;
    // CALL(aPokeAnim_InitPicAttributes);
    PokeAnim_InitPicAttributes_Conv(bc, hl, d);
    // RET;
}

void SetUpPokeAnim(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awPokeAnimStruct));
    LDH_addr_A(rSVBK);
    LD_A_addr(wPokeAnimSceneIndex);
    LD_C_A;
    LD_B(0);
    LD_HL(wPokeAnimPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(mPokeAnim_SetupCommands);
    RST(aJumpTable);
    LD_A_addr(wPokeAnimSceneIndex);
    LD_C_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A_C;
    AND_A(0x80);
    RET_Z ;
    SCF;
    RET;

// add_setup_command: MACRO
// \1_SetupCommand:
//     dw \1
// ENDM

}

bool SetUpPokeAnim_Conv(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wPokeAnimStruct));
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wPokeAnimSceneIndex);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wPokeAnimPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(mPokeAnim_SetupCommands);
    // RST(aJumpTable);
    PokeAnim_SetupCommands[lPokeAnimPointer[pokeAnim->sceneIndex]]();
    // LD_A_addr(wPokeAnimSceneIndex);
    // LD_C_A;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A_C;
    // AND_A(0x80);
    // RET_Z ;
    // SCF;
    // RET;
    return (pokeAnim->sceneIndex & 0x80) != 0;
}

void PokeAnim_SetWait(void){
    // LD_A(18);
    // LD_addr_A(wPokeAnimWaitCounter);
    pokeAnim->waitCounter = 18;
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;

    return PokeAnim_Wait();
}

void PokeAnim_Wait(void){
    // LD_HL(wPokeAnimWaitCounter);
    // DEC_hl;
    // RET_NZ ;
    if(--pokeAnim->waitCounter != 0)
        return;
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_Setup(void){
    // LD_C(FALSE);
    // LD_B(0);
    // CALL(aPokeAnim_InitAnim);
    PokeAnim_InitAnim_Conv(0, FALSE);
    // CALL(aPokeAnim_SetVBank1);
    PokeAnim_SetVBank1_Conv();
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_Setup2(void){
    // LD_C(FALSE);
    // LD_B(4);
    // CALL(aPokeAnim_InitAnim);
    PokeAnim_InitAnim_Conv(4, FALSE);
    // CALL(aPokeAnim_SetVBank1);
    PokeAnim_SetVBank1_Conv();
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_Idle(void){
    // LD_C(TRUE);
    // LD_B(0);
    // CALL(aPokeAnim_InitAnim);
    PokeAnim_InitAnim_Conv(0, TRUE);
    // CALL(aPokeAnim_SetVBank1);
    PokeAnim_SetVBank1_Conv();
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_Play(void){
    // CALL(aPokeAnim_DoAnimScript);
    PokeAnim_DoAnimScript_Conv();
    // LD_A_addr(wPokeAnimJumptableIndex);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(pokeAnim->jumptableIndex, 7))
        return;
    // CALL(aPokeAnim_PlaceGraphic);
    PokeAnim_PlaceGraphic_Conv();
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_Play2(void){
    // CALL(aPokeAnim_DoAnimScript);
    PokeAnim_DoAnimScript_Conv();
    // LD_A_addr(wPokeAnimJumptableIndex);
    // BIT_A(7);
    // RET_Z ;
    if(!bit_test(pokeAnim->jumptableIndex, 7))
        return;
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_BasePic(void){
    // CALL(aPokeAnim_DeinitFrames);
    PokeAnim_DeinitFrames();
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_Finish(void){
    // CALL(aPokeAnim_DeinitFrames);
    PokeAnim_DeinitFrames();
    // LD_HL(wPokeAnimSceneIndex);
    // SET_hl(7);
    bit_set(pokeAnim->sceneIndex, 7);
    // RET;
}

void PokeAnim_Cry(void){
    // LD_A_addr(wPokeAnimSpecies);
    // CALL(av_PlayMonCry);
    v_PlayMonCry(pokeAnim->species);
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_CryNoWait(void){
    // LD_A_addr(wPokeAnimSpecies);
    // CALL(aPlayMonCry2);
    PlayMonCry2(pokeAnim->species);
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_StereoCry(void){
    // LD_A(0xf);
    // LD_addr_A(wCryTracks);
    wram->wCryTracks = 0xf;
    // LD_A_addr(wPokeAnimSpecies);
    // CALL(aPlayStereoCry2);
    PlayStereoCry2(pokeAnim->species);
    // LD_A_addr(wPokeAnimSceneIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimSceneIndex);
    pokeAnim->sceneIndex++;
    // RET;
}

void PokeAnim_DeinitFrames(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wPokeAnimCoord));
    // LDH_addr_A(rSVBK);
    GetAnimatedFrontpic_Conv(vram->vTiles2 + LEN_2BPP_TILE * 0x00, 0);
    // CALL(aPokeAnim_PlaceGraphic);
    PokeAnim_PlaceGraphic_Conv();
    // FARCALL(aHDMATransferTilemapToWRAMBank3);
    HDMATransferTilemapToWRAMBank3_Conv();
    // CALL(aPokeAnim_SetVBank0);
    PokeAnim_SetVBank0_Conv();
    // FARCALL(aHDMATransferAttrmapToWRAMBank3);
    HDMATransferTilemapToWRAMBank3_Conv();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void AnimateMon_CheckIfPokemon(void){
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto fail;
    CALL(aIsAPokemon);
    IF_C goto fail;
    AND_A_A;
    RET;


fail:
    SCF;
    RET;

}

bool AnimateMon_CheckIfPokemon_Conv(void){
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto fail;
    if(wram->wCurPartySpecies == EGG)
        return false;
    // CALL(aIsAPokemon);
    // IF_C goto fail;
    return IsAPokemon(wram->wCurPartySpecies);
    // AND_A_A;
    // RET;

// fail:
    // SCF;
    // RET;
}

void PokeAnim_InitPicAttributes(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awPokeAnimStruct));
    LDH_addr_A(rSVBK);

    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_HL(wPokeAnimStruct);
    LD_BC(wPokeAnimStructEnd - wPokeAnimStruct);
    XOR_A_A;
    CALL(aByteFill);
    POP_HL;
    POP_DE;
    POP_BC;

//  bc contains anim pointer
    LD_A_C;
    LD_addr_A(wPokeAnimPointer);
    LD_A_B;
    LD_addr_A(wPokeAnimPointer + 1);
//  hl contains tilemap coords
    LD_A_L;
    LD_addr_A(wPokeAnimCoord);
    LD_A_H;
    LD_addr_A(wPokeAnimCoord + 1);
//  d = start tile
    LD_A_D;
    LD_addr_A(wPokeAnimGraphicStartTile);

    LD_A(MBANK(awCurPartySpecies));
    LD_HL(wCurPartySpecies);
    CALL(aGetFarWRAMByte);
    LD_addr_A(wPokeAnimSpecies);

    LD_A(MBANK(awUnownLetter));
    LD_HL(wUnownLetter);
    CALL(aGetFarWRAMByte);
    LD_addr_A(wPokeAnimUnownLetter);

    CALL(aPokeAnim_GetSpeciesOrUnown);
    LD_addr_A(wPokeAnimSpeciesOrUnown);

    CALL(aPokeAnim_GetFrontpicDims);
    LD_A_C;
    LD_addr_A(wPokeAnimFrontpicHeight);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void PokeAnim_InitPicAttributes_Conv(const uint8_t* bc, uint8_t* hl, uint8_t d){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wPokeAnimStruct));
    // LDH_addr_A(rSVBK);

    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // LD_HL(wPokeAnimStruct);
    // LD_BC(wPokeAnimStructEnd - wPokeAnimStruct);
    // XOR_A_A;
    // CALL(aByteFill);
    // POP_HL;
    // POP_DE;
    // POP_BC;
    ByteFill(pokeAnim, sizeof(*pokeAnim), 0);

//  bc contains anim pointer
    // LD_A_C;
    // LD_addr_A(wPokeAnimPointer);
    // LD_A_B;
    // LD_addr_A(wPokeAnimPointer + 1);
    lPokeAnimPointer = bc;
//  hl contains tilemap coords
    // LD_A_L;
    // LD_addr_A(wPokeAnimCoord);
    // LD_A_H;
    // LD_addr_A(wPokeAnimCoord + 1);
    lPokeAnimCoord = hl;
//  d = start tile
    // LD_A_D;
    // LD_addr_A(wPokeAnimGraphicStartTile);
    pokeAnim->graphicStartTile = d;

    // LD_A(BANK(wCurPartySpecies));
    // LD_HL(wCurPartySpecies);
    // CALL(aGetFarWRAMByte);
    // LD_addr_A(wPokeAnimSpecies);
    pokeAnim->species = wram->wCurPartySpecies;

    // LD_A(BANK(wUnownLetter));
    // LD_HL(wUnownLetter);
    // CALL(aGetFarWRAMByte);
    // LD_addr_A(wPokeAnimUnownLetter);
    pokeAnim->unownLetter = wram->wUnownLetter;

    // CALL(aPokeAnim_GetSpeciesOrUnown);
    // LD_addr_A(wPokeAnimSpeciesOrUnown);
    pokeAnim->speciesOrUnown = PokeAnim_GetSpeciesOrUnown_Conv(pokeAnim->species);

    // CALL(aPokeAnim_GetFrontpicDims);
    // LD_A_C;
    // LD_addr_A(wPokeAnimFrontpicHeight);
    pokeAnim->frontpicHeight = PokeAnim_GetFrontpicDims_Conv();

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void PokeAnim_InitAnim(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awPokeAnimIdleFlag));
    LDH_addr_A(rSVBK);
    PUSH_BC;
    LD_HL(wPokeAnimIdleFlag);
    LD_BC(wPokeAnimStructEnd - wPokeAnimIdleFlag);
    XOR_A_A;
    CALL(aByteFill);
    POP_BC;
    LD_A_B;
    LD_addr_A(wPokeAnimSpeed);
    LD_A_C;
    LD_addr_A(wPokeAnimIdleFlag);
    CALL(aGetMonAnimPointer);
    CALL(aGetMonFramesPointer);
    CALL(aGetMonBitmaskPointer);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void PokeAnim_InitAnim_Conv(uint8_t b, uint8_t c){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wPokeAnimIdleFlag));
    // LDH_addr_A(rSVBK);
    // PUSH_BC;
    // LD_HL(wPokeAnimIdleFlag);
    // LD_BC(wPokeAnimStructEnd - wPokeAnimIdleFlag);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(((uint8_t*)pokeAnim) + offsetof(struct PokeAnim, idleFlag), 
        (uint16_t)(((uint8_t*)(pokeAnim + 1)) - (((uint8_t*)pokeAnim) + offsetof(struct PokeAnim, idleFlag))), 
        0);
    // POP_BC;
    // LD_A_B;
    // LD_addr_A(wPokeAnimSpeed);
    pokeAnim->speed = b;
    // LD_A_C;
    // LD_addr_A(wPokeAnimIdleFlag);
    pokeAnim->idleFlag = c;
    // CALL(aGetMonAnimPointer);
    GetMonAnimPointer_Conv();
    // CALL(aGetMonFramesPointer);
    // CALL(aGetMonBitmaskPointer);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void PokeAnim_DoAnimScript(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

loop:
    LD_A_addr(wPokeAnimJumptableIndex);
    AND_A(0x7f);
    LD_HL(mPokeAnim_DoAnimScript_Jumptable);
    RST(aJumpTable);
    RET;


Jumptable:
    //dw ['.RunAnim'];
    //dw ['.WaitAnim'];


RunAnim:
    CALL(aPokeAnim_GetPointer);
    LD_A_addr(wPokeAnimCommand);
    CP_A(endanim_command);
    JR_Z (mPokeAnim_End);
    CP_A(setrepeat_command);
    IF_Z goto SetRepeat;
    CP_A(dorepeat_command);
    IF_Z goto DoRepeat;
    CALL(aPokeAnim_GetFrame);
    LD_A_addr(wPokeAnimParameter);
    CALL(aPokeAnim_GetDuration);
    LD_addr_A(wPokeAnimWaitCounter);
    CALL(aPokeAnim_StartWaitAnim);

WaitAnim:
    LD_A_addr(wPokeAnimWaitCounter);
    DEC_A;
    LD_addr_A(wPokeAnimWaitCounter);
    RET_NZ ;
    CALL(aPokeAnim_StopWaitAnim);
    RET;


SetRepeat:
    LD_A_addr(wPokeAnimParameter);
    LD_addr_A(wPokeAnimRepeatTimer);
    goto loop;


DoRepeat:
    LD_A_addr(wPokeAnimRepeatTimer);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wPokeAnimRepeatTimer);
    RET_Z ;
    LD_A_addr(wPokeAnimParameter);
    LD_addr_A(wPokeAnimFrame);
    goto loop;

    return PokeAnim_End();
}

void PokeAnim_DoAnimScript_Conv(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;

    while(1) {
    // loop:
        // LD_A_addr(wPokeAnimJumptableIndex);
        // AND_A(0x7f);
        // LD_HL(mPokeAnim_DoAnimScript_Jumptable);
        // RST(aJumpTable);
        // RET;


    // Jumptable:
        //dw ['.RunAnim'];
        //dw ['.WaitAnim'];
        uint8_t a;
        switch(pokeAnim->jumptableIndex & 0x7f) {
            case 0:
            // RunAnim:
                // CALL(aPokeAnim_GetPointer);
                PokeAnim_GetPointer_Conv();
                // LD_A_addr(wPokeAnimCommand);
                a = pokeAnim->command;
                // CP_A(endanim_command);
                // JR_Z (mPokeAnim_End);
                if(a == endanim_command)
                    return PokeAnim_End();
                // CP_A(setrepeat_command);
                // IF_Z goto SetRepeat;
                if(a == setrepeat_command) {
                // SetRepeat:
                    // LD_A_addr(wPokeAnimParameter);
                    // LD_addr_A(wPokeAnimRepeatTimer);
                    pokeAnim->repeatTimer = pokeAnim->parameter;
                    continue;
                }
                // CP_A(dorepeat_command);
                // IF_Z goto DoRepeat;
                if(a == dorepeat_command) {
                // DoRepeat:
                    // LD_A_addr(wPokeAnimRepeatTimer);
                    // AND_A_A;
                    // RET_Z ;
                    if(pokeAnim->repeatTimer == 0)
                        return;
                    // DEC_A;
                    // LD_addr_A(wPokeAnimRepeatTimer);
                    // RET_Z ;
                    if(--pokeAnim->repeatTimer == 0)
                        return;
                    // LD_A_addr(wPokeAnimParameter);
                    // LD_addr_A(wPokeAnimFrame);
                    pokeAnim->frame = pokeAnim->parameter;
                    continue;
                }
                // CALL(aPokeAnim_GetFrame);
                PokeAnim_GetFrame();
                // LD_A_addr(wPokeAnimParameter);
                // CALL(aPokeAnim_GetDuration);
                // LD_addr_A(wPokeAnimWaitCounter);
                pokeAnim->waitCounter = PokeAnim_GetDuration_Conv(pokeAnim->parameter);
                // CALL(aPokeAnim_StartWaitAnim);
                PokeAnim_StartWaitAnim();
                // fallthrough
            case 1:
            // WaitAnim:
                // LD_A_addr(wPokeAnimWaitCounter);
                // DEC_A;
                // LD_addr_A(wPokeAnimWaitCounter);
                // RET_NZ ;
                if(--pokeAnim->waitCounter != 0)
                    return;
                // CALL(aPokeAnim_StopWaitAnim);
                PokeAnim_StopWaitAnim();
                // RET;
                return;
        }
    }
    // return PokeAnim_End();
}

void PokeAnim_End(void){
    // LD_HL(wPokeAnimJumptableIndex);
    // SET_hl(7);
    // RET;
    pokeAnim->jumptableIndex |= (1 << 7);
}

void PokeAnim_GetDuration(void){
//  a * (1 + [wPokeAnimSpeed] / 16)
    LD_C_A;
    LD_B(0);
    LD_HL(0);
    LD_A_addr(wPokeAnimSpeed);
    CALL(aAddNTimes);
    LD_A_H;
    SWAP_A;
    AND_A(0xf0);
    LD_H_A;
    LD_A_L;
    SWAP_A;
    AND_A(0xf);
    OR_A_H;
    ADD_A_C;
    RET;

}

//  a * (1 + [wPokeAnimSpeed] / 16)
uint8_t PokeAnim_GetDuration_Conv(uint8_t a){
    // LD_C_A;
    // LD_B(0);
    // LD_HL(0);
    // LD_A_addr(wPokeAnimSpeed);
    // CALL(aAddNTimes);
    // LD_A_H;
    // SWAP_A;
    // AND_A(0xf0);
    // LD_H_A;
    // LD_A_L;
    // SWAP_A;
    // AND_A(0xf);
    // OR_A_H;
    // ADD_A_C;
    // RET;
    return a * (1 + pokeAnim->speed / 16);
}

void PokeAnim_GetFrame(void){
    // CALL(aPokeAnim_PlaceGraphic);
    PokeAnim_PlaceGraphic_Conv();
    // LD_A_addr(wPokeAnimCommand);
    // AND_A_A;
    // RET_Z ;
    // if(pokeAnim->command == 0)
        // return;
    // CALL(aPokeAnim_GetBitmaskIndex);
    // PUSH_HL;
    // CALL(aPokeAnim_CopyBitmaskToBuffer);
    // POP_HL;
    // CALL(aPokeAnim_ConvertAndApplyBitmask);
    GetAnimatedFrontpic_Conv(vram->vTiles2 + LEN_2BPP_TILE * 0x00, pokeAnim->command);
    // RET;

}

void PokeAnim_StartWaitAnim(void){
    // LD_A_addr(wPokeAnimJumptableIndex);
    // INC_A;
    // LD_addr_A(wPokeAnimJumptableIndex);
    pokeAnim->jumptableIndex++;
    // RET;
}

void PokeAnim_StopWaitAnim(void){
    // LD_A_addr(wPokeAnimJumptableIndex);
    // DEC_A;
    // LD_addr_A(wPokeAnimJumptableIndex);
    pokeAnim->jumptableIndex--;
    // RET;
}

void PokeAnim_IsUnown(void){
    LD_A_addr(wPokeAnimSpecies);
    CP_A(UNOWN);
    RET;

}

bool PokeAnim_IsUnown_Conv(species_t a){
    // LD_A_addr(wPokeAnimSpecies);
    // CP_A(UNOWN);
    // RET;
    return a == UNOWN;
}

void PokeAnim_IsEgg(void){
    LD_A_addr(wPokeAnimSpecies);
    CP_A(EGG);
    RET;

}

bool PokeAnim_IsEgg_Conv(void){
    // LD_A_addr(wPokeAnimSpecies);
    // CP_A(EGG);
    // RET;
    return pokeAnim->species == EGG;
}

void PokeAnim_GetPointer(void){
    PUSH_HL;
    LD_A_addr(wPokeAnimFrame);
    LD_E_A;
    LD_D(0);
    LD_HL(wPokeAnimPointerAddr);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_addr(wPokeAnimPointerBank);
    CALL(aGetFarWord);
    LD_A_L;
    LD_addr_A(wPokeAnimCommand);
    LD_A_H;
    LD_addr_A(wPokeAnimParameter);
    LD_HL(wPokeAnimFrame);
    INC_hl;
    POP_HL;
    RET;

}

void PokeAnim_GetPointer_Conv(void){
    // PUSH_HL;
    // LD_A_addr(wPokeAnimFrame);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPokeAnimPointerAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_addr(wPokeAnimPointerBank);
    // CALL(aGetFarWord);
    // LD_A_L;
    // LD_addr_A(wPokeAnimCommand);
    pokeAnim->command = lPokeAnimPointerAddr[pokeAnim->frame * 2 + 0];
    // LD_A_H;
    // LD_addr_A(wPokeAnimParameter);
    pokeAnim->parameter = lPokeAnimPointerAddr[pokeAnim->frame * 2 + 1];
    // LD_HL(wPokeAnimFrame);
    // INC_hl;
    pokeAnim->frame++;
    // POP_HL;
    // RET;
}

void PokeAnim_GetBitmaskIndex(void){
    LD_A_addr(wPokeAnimCommand);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wPokeAnimFramesAddr);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_addr(wPokeAnimFramesBank);
    CALL(aGetFarWord);
    LD_A_addr(wPokeAnimFramesBank);
    CALL(aGetFarByte);
    LD_addr_A(wPokeAnimCurBitmask);
    INC_HL;
    RET;
}

uint16_t PokeAnim_GetBitmaskIndex_Conv(void) {
    // LD_A_addr(wPokeAnimCommand);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wPokeAnimFramesAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_addr(wPokeAnimFramesBank);
    // CALL(aGetFarWord);
    uint16_t hl = GetFarWord(pokeAnim->framesBank, pokeAnim->framesAddr + (pokeAnim->command << 1));
    // LD_A_addr(wPokeAnimFramesBank);
    // CALL(aGetFarByte);
    // LD_addr_A(wPokeAnimCurBitmask);
    pokeAnim->curBitmask = GetFarByte(pokeAnim->framesBank, hl);
    // INC_HL;
    // RET;
    return ++hl;
}

void PokeAnim_CopyBitmaskToBuffer(void){
    CALL(aPokeAnim_CopyBitmaskToBuffer_GetSize);
    PUSH_BC;
    LD_HL(wPokeAnimBitmaskAddr);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wPokeAnimCurBitmask);
    CALL(aAddNTimes);
    POP_BC;
    LD_DE(wPokeAnimBitmaskBuffer);
    LD_A_addr(wPokeAnimBitmaskBank);
    CALL(aFarCopyBytes);
    RET;


GetSize:
    PUSH_HL;
    LD_A_addr(wPokeAnimFrontpicHeight);
    SUB_A(5);  // to get a number 0, 1, or 2
    LD_C_A;
    LD_B(0);
    LD_HL(mPokeAnim_CopyBitmaskToBuffer_Sizes);
    ADD_HL_BC;
    LD_C_hl;
    LD_B(0);
    POP_HL;
    RET;


Sizes:
// db 4, 5, 7

// poke_anim_box: MACRO
// for y, 1, \1 + 1
// for x, 7 - \1, 7
//     db y * 7 + x
// endr
// endr
// ENDM

    return PokeAnim_ConvertAndApplyBitmask();
}

void PokeAnim_ConvertAndApplyBitmask(void){
    XOR_A_A;
    LD_addr_A(wPokeAnimBitmaskCurBit);
    LD_addr_A(wPokeAnimBitmaskCurRow);
    LD_addr_A(wPokeAnimBitmaskCurCol);

loop:
    PUSH_HL;
    CALL(aPokeAnim_ConvertAndApplyBitmask_IsCurBitSet);
    POP_HL;
    LD_A_B;
    AND_A_A;
    IF_Z goto next;

    LD_A_addr(wPokeAnimFramesBank);
    CALL(aGetFarByte);
    INC_HL;
    PUSH_HL;
    CALL(aPokeAnim_ConvertAndApplyBitmask_ApplyFrame);
    POP_HL;


next:
    PUSH_HL;
    CALL(aPokeAnim_ConvertAndApplyBitmask_NextBit);
    POP_HL;
    IF_NC goto loop;
    RET;


IsCurBitSet:
//  which byte
    LD_A_addr(wPokeAnimBitmaskCurBit);
    AND_A(0xf8);
    RRCA;
    RRCA;
    RRCA;
    LD_E_A;
    LD_D(0);
    LD_HL(wPokeAnimBitmaskBuffer);
    ADD_HL_DE;
    LD_B_hl;
//  which bit
    LD_A_addr(wPokeAnimBitmaskCurBit);
    AND_A(0x7);
    IF_Z goto skip;

    LD_C_A;
    LD_A_B;

loop2:
    RRCA;
    DEC_C;
    IF_NZ goto loop2;
    LD_B_A;


skip:
    XOR_A_A;
    BIT_B(0);
    IF_Z goto finish;
    LD_A(1);


finish:
    LD_B_A;
    LD_HL(wPokeAnimBitmaskCurBit);
    INC_hl;
    RET;


ApplyFrame:
    PUSH_AF;
    CALL(aPokeAnim_ConvertAndApplyBitmask_GetCoord);
    POP_AF;
    PUSH_HL;
    CALL(aPokeAnim_ConvertAndApplyBitmask_GetTilemap);
    LD_HL(wPokeAnimGraphicStartTile);
    ADD_A_hl;
    POP_HL;
    LD_hl_A;
    RET;


GetCoord:
    CALL(aPokeAnim_ConvertAndApplyBitmask_GetStartCoord);
    LD_A_addr(wPokeAnimBitmaskCurRow);
    LD_BC(SCREEN_WIDTH);
    CALL(aAddNTimes);
    LD_A_addr(wBoxAlignment);
    AND_A_A;
    IF_NZ goto subtract;
// hl += [wPokeAnimBitmaskCurCol]
    LD_A_addr(wPokeAnimBitmaskCurCol);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    goto done;


subtract:
// hl -= [wPokeAnimBitmaskCurCol]
    LD_A_addr(wPokeAnimBitmaskCurCol);
    LD_E_A;
    LD_A_L;
    SUB_A_E;
    LD_L_A;
    LD_A_H;
    SBC_A(0);
    LD_H_A;


done:
    RET;


UnusedSizeData:
//   //  unreferenced
    //db ['6', '5', '4'];


GetTilemap:
    PUSH_AF;
    LD_A_addr(wPokeAnimFrontpicHeight);
    CP_A(5);
    IF_Z goto check_add_24;
    CP_A(6);
    IF_Z goto check_add_13;
    POP_AF;
    RET;


check_add_24:
    POP_AF;
    CP_A(5 * 5);
    IF_NC goto add_24;
    PUSH_HL;
    PUSH_DE;
    LD_HL(mPokeAnim_ConvertAndApplyBitmask__5by5);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    POP_DE;
    POP_HL;
    RET;


add_24:
    ADD_A(24);
    RET;


check_add_13:
    POP_AF;
    CP_A(6 * 6);
    IF_NC goto add_13;
    PUSH_HL;
    PUSH_DE;
    LD_HL(mPokeAnim_ConvertAndApplyBitmask__6by6);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    POP_DE;
    POP_HL;
    RET;


add_13:
    ADD_A(13);
    RET;


_5by5:
    //poke_anim_box ['5']
// db  9, 10, 11, 12, 13
// db 16, 17, 18, 19, 20
// db 23, 24, 25, 26, 27
// db 30, 31, 32, 33, 34
// db 37, 38, 39, 40, 41


_6by6:
    //poke_anim_box ['6']
// db  8,  9, 10, 11, 12, 13
// db 15, 16, 17, 18, 19, 20
// db 22, 23, 24, 25, 26, 27
// db 29, 30, 31, 32, 33, 34
// db 36, 37, 38, 39, 40, 41
// db 43, 44, 45, 46, 47, 48


GetStartCoord:
    LD_HL(wPokeAnimCoord);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    LD_A_addr(wPokeAnimFrontpicHeight);
    LD_DE(0);
    LD_BC(6);
    CP_A(7);
    IF_Z goto okay;
    LD_DE(SCREEN_WIDTH + 1);
    LD_BC(SCREEN_WIDTH + 5);
    CP_A(6);
    IF_Z goto okay;
    LD_DE(2 * SCREEN_WIDTH + 1);
    LD_BC(2 * SCREEN_WIDTH + 5);

okay:

    LD_A_addr(wBoxAlignment);
    AND_A_A;
    IF_NZ goto add_bc;
    ADD_HL_DE;
    RET;


add_bc:
    ADD_HL_BC;
    RET;


NextBit:
    LD_A_addr(wPokeAnimBitmaskCurRow);
    INC_A;
    LD_addr_A(wPokeAnimBitmaskCurRow);
    LD_C_A;
    LD_A_addr(wPokeAnimFrontpicHeight);
    CP_A_C;
    IF_NZ goto no_carry;
    XOR_A_A;
    LD_addr_A(wPokeAnimBitmaskCurRow);
    LD_A_addr(wPokeAnimBitmaskCurCol);
    INC_A;
    LD_addr_A(wPokeAnimBitmaskCurCol);
    LD_C_A;
    LD_A_addr(wPokeAnimFrontpicHeight);
    CP_A_C;
    IF_NZ goto no_carry;
    SCF;
    RET;


no_carry:
    XOR_A_A;
    RET;

}

void PokeAnim_PlaceGraphic(void){
    CALL(aPokeAnim_PlaceGraphic_ClearBox);
    LD_A_addr(wBoxAlignment);
    AND_A_A;
    IF_NZ goto flipped;
    LD_DE(1);
    LD_BC(0);
    goto okay;


flipped:
    LD_DE(-1);
    LD_BC(6);


okay:
    LD_HL(wPokeAnimCoord);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_BC;
    LD_C(7);
    LD_B(7);
    LD_A_addr(wPokeAnimGraphicStartTile);

loop:
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    LD_DE(SCREEN_WIDTH);

loop2:
    LD_hl_A;
    INC_A;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop2;
    POP_DE;
    POP_HL;
    ADD_HL_DE;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;


ClearBox:
    LD_HL(wPokeAnimCoord);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_B(7);
    LD_C(7);
    CALL(aClearBox);
    RET;

}

static void PokeAnim_PlaceGraphic_ClearBox(void) {
    // LD_HL(wPokeAnimCoord);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_B(7);
    // LD_C(7);
    // CALL(aClearBox);
    // RET;
    return ClearBox(lPokeAnimCoord, 7, 7);
}

void PokeAnim_PlaceGraphic_Conv(void){
    // CALL(aPokeAnim_PlaceGraphic_ClearBox);
    PokeAnim_PlaceGraphic_ClearBox();
    // LD_A_addr(wBoxAlignment);
    // AND_A_A;
    // IF_NZ goto flipped;
    int16_t de;
    int16_t bc;
    if(wram->wBoxAlignment == 0) {
        // LD_DE(1);
        de = 1;
        // LD_BC(0);
        bc = 0;
        // goto okay;
    } 
    else {
    // flipped:
        // LD_DE(-1);
        de = -1;
        // LD_BC(6);
        bc = 6;
    }


// okay:
    // LD_HL(wPokeAnimCoord);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_BC;
    uint8_t* hl = lPokeAnimCoord + bc;
    // LD_C(7);
    // LD_B(7);
    // LD_A_addr(wPokeAnimGraphicStartTile);
    uint8_t a = pokeAnim->graphicStartTile;

    for(uint8_t c = 0; c < 7; c++) {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_DE;
        // LD_DE(SCREEN_WIDTH);
        for(uint8_t b = 0; b < 7; b++) {
        // loop2:
            // LD_hl_A;
            hl[b*de] = a++;
            // INC_A;
            // ADD_HL_DE;
            // DEC_B;
            // IF_NZ goto loop2;
        }
        // POP_DE;
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

void PokeAnim_SetVBank1(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wPokeAnimCoord));
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPokeAnim_SetVBank1_SetFlag);
    FARCALL(aHDMATransferAttrmapToWRAMBank3);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


SetFlag:
    CALL(aPokeAnim_GetAttrmapCoord);
    LD_B(7);
    LD_C(7);
    LD_DE(SCREEN_WIDTH);

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_A_hl;
    OR_A(8);
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    INC_HL;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

static void PokeAnim_SetVBank1_SetFlag(void) {
// SetFlag:
    // CALL(aPokeAnim_GetAttrmapCoord);
    uint8_t* hl = PokeAnim_GetAttrmapCoord_Conv();
    // LD_B(7);
    uint8_t b = 7;
    // LD_C(7);
    uint8_t c = 7;
    // LD_DE(SCREEN_WIDTH);

    do {
    // row:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // col:
            // LD_A_hl;
            // OR_A(8);
            // LD_hl_A;
            (*hl) |= 8;
            // ADD_HL_DE;
            hl += SCREEN_WIDTH;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // POP_HL;
        // INC_HL;
        hl = hl2 + 1;
        // POP_BC;
        c = c2;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void PokeAnim_SetVBank1_Conv(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wPokeAnimCoord));
    // LDH_addr_A(rSVBK);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aPokeAnim_SetVBank1_SetFlag);
    PokeAnim_SetVBank1_SetFlag();

    // FARCALL(aHDMATransferAttrmapToWRAMBank3);
    HDMATransferAttrmapToWRAMBank3_Conv();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void PokeAnim_SetVBank0(void){
    CALL(aPokeAnim_GetAttrmapCoord);
    LD_B(7);
    LD_C(7);
    LD_DE(SCREEN_WIDTH);

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_A_hl;
    AND_A(0xf7);
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    INC_HL;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

void PokeAnim_SetVBank0_Conv(void){
    // CALL(aPokeAnim_GetAttrmapCoord);
    uint8_t* hl = PokeAnim_GetAttrmapCoord_Conv();
    // LD_B(7);
    // LD_C(7);
    // LD_DE(SCREEN_WIDTH);

    for(uint8_t b = 0; b < 7; b++) {
    // row:
        // PUSH_BC;
        // PUSH_HL;

        for(uint8_t c = 0; c < 7; c++) {
        // col:
            // LD_A_hl;
            // AND_A(0xf7);
            // LD_hl_A;
            hl[c*SCREEN_WIDTH] &= 0xf7;
            // ADD_HL_DE;
            // DEC_C;
            // IF_NZ goto col;
        }
        // POP_HL;
        // INC_HL;
        hl++;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    }
    // RET;
}

void PokeAnim_GetAttrmapCoord(void){
    LD_HL(wPokeAnimCoord);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wAttrmap - wTilemap);
    ADD_HL_DE;
    RET;

}

uint8_t* PokeAnim_GetAttrmapCoord_Conv(void){
    // LD_HL(wPokeAnimCoord);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(wAttrmap - wTilemap);
    // ADD_HL_DE;
    // RET;
    return lPokeAnimCoord + (wAttrmap - wTilemap);
}

void GetMonAnimPointer(void){
    CALL(aPokeAnim_IsEgg);
    IF_Z goto egg;

    LD_C(BANK(aUnownAnimationPointers));  // aka BANK(UnownAnimationIdlePointers)
    LD_HL(mUnownAnimationPointers);
    LD_DE(mUnownAnimationIdlePointers);
    CALL(aPokeAnim_IsUnown);
    IF_Z goto unown;
    LD_C(BANK(aAnimationPointers));  // aka BANK(AnimationIdlePointers)
    LD_HL(mAnimationPointers);
    LD_DE(mAnimationIdlePointers);

unown:

    LD_A_addr(wPokeAnimIdleFlag);
    AND_A_A;
    IF_Z goto idles;
    LD_H_D;
    LD_L_E;

idles:

    LD_A_addr(wPokeAnimSpeciesOrUnown);
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_C;
    LD_addr_A(wPokeAnimPointerBank);
    CALL(aGetFarWord);
    LD_A_L;
    LD_addr_A(wPokeAnimPointerAddr);
    LD_A_H;
    LD_addr_A(wPokeAnimPointerAddr + 1);
    RET;


egg:
    LD_HL(mEggAnimation);
    LD_C(BANK(aEggAnimation));
    LD_A_addr(wPokeAnimIdleFlag);
    AND_A_A;
    IF_Z goto idles_egg;
    LD_HL(mEggAnimationIdle);
    LD_C(BANK(aEggAnimationIdle));

idles_egg:

    LD_A_C;
    LD_addr_A(wPokeAnimPointerBank);
    LD_A_L;
    LD_addr_A(wPokeAnimPointerAddr);
    LD_A_H;
    LD_addr_A(wPokeAnimPointerAddr + 1);
    RET;

}

void GetMonAnimPointer_Conv(void){
    // CALL(aPokeAnim_IsEgg);
    // IF_Z goto egg;
    if(PokeAnim_IsEgg_Conv()) {
    // egg:
        // LD_HL(mEggAnimation);
        // LD_C(BANK(aEggAnimation));
        // LD_A_addr(wPokeAnimIdleFlag);
        // AND_A_A;
        // IF_Z goto idles_egg;
        if(pokeAnim->idleFlag) {
            // LD_HL(mEggAnimationIdle);
            // LD_C(BANK(aEggAnimationIdle));
            lPokeAnimPointerAddr = EggAnimationIdle;
        }
        else {
            lPokeAnimPointerAddr = EggAnimation;
        }

    // idles_egg:

        // LD_A_C;
        // LD_addr_A(wPokeAnimPointerBank);
        // LD_A_L;
        // LD_addr_A(wPokeAnimPointerAddr);
        // LD_A_H;
        // LD_addr_A(wPokeAnimPointerAddr + 1);
        // RET;
        return;
    }

    // LD_C(BANK(aUnownAnimationPointers));  // aka BANK(UnownAnimationIdlePointers)
    // LD_HL(mUnownAnimationPointers);
    // LD_DE(mUnownAnimationIdlePointers);
    // CALL(aPokeAnim_IsUnown);
    // IF_Z goto unown;
    const uint8_t** hl;
    const uint8_t** de;
    if(PokeAnim_IsUnown_Conv(pokeAnim->species)) {
        hl = UnownAnimationPointers;
        de = UnownAnimationIdlePointers;
    }
    // LD_C(BANK(aAnimationPointers));  // aka BANK(AnimationIdlePointers)
    // LD_HL(mAnimationPointers);
    // LD_DE(mAnimationIdlePointers);
    else {
        hl = AnimationPointers;
        de = AnimationIdlePointers;
    }

// unown:

    // LD_A_addr(wPokeAnimIdleFlag);
    // AND_A_A;
    // IF_Z goto idles;
    // LD_H_D;
    // LD_L_E;
    if(pokeAnim->idleFlag)
        hl = de;

// idles:

    // LD_A_addr(wPokeAnimSpeciesOrUnown);
    // DEC_A;
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_C;
    // LD_addr_A(wPokeAnimPointerBank);
    // CALL(aGetFarWord);
    // LD_A_L;
    // LD_addr_A(wPokeAnimPointerAddr);
    // LD_A_H;
    // LD_addr_A(wPokeAnimPointerAddr + 1);
    lPokeAnimPointerAddr = hl[pokeAnim->speciesOrUnown - 1];
    // RET;
}

void PokeAnim_GetFrontpicDims(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wCurPartySpecies));
    LDH_addr_A(rSVBK);
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A_addr(wBasePicSize);
    AND_A(0xf);
    LD_C_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

uint8_t PokeAnim_GetFrontpicDims_Conv(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wCurPartySpecies));
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurSpecies);
    // LD_A_addr(wBasePicSize);
    // AND_A(0xf);
    // LD_C_A;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    return wram->wBasePicSize & 0xf;
}

void GetMonFramesPointer(void){
    CALL(aPokeAnim_IsEgg);
    IF_Z goto egg;

    CALL(aPokeAnim_IsUnown);
    LD_B(BANK(aUnownFramesPointers));
    LD_C(BANK(aUnownsFrames));
    LD_HL(mUnownFramesPointers);
    IF_Z goto got_frames;
    LD_A_addr(wPokeAnimSpecies);
    CP_A(JOHTO_POKEMON);
    LD_B(BANK(aFramesPointers));
    LD_C(BANK(aKantoFrames));
    LD_HL(mFramesPointers);
    IF_C goto got_frames;
    LD_C(BANK(aJohtoFrames));

got_frames:
    LD_A_C;
    LD_addr_A(wPokeAnimFramesBank);

    LD_A_addr(wPokeAnimSpeciesOrUnown);
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_B;
    CALL(aGetFarWord);
    LD_A_L;
    LD_addr_A(wPokeAnimFramesAddr);
    LD_A_H;
    LD_addr_A(wPokeAnimFramesAddr + 1);
    RET;


egg:
    LD_HL(mEggFrames);
    LD_C(BANK(aEggFrames));
    LD_A_C;
    LD_addr_A(wPokeAnimFramesBank);
    LD_A_L;
    LD_addr_A(wPokeAnimFramesAddr);
    LD_A_H;
    LD_addr_A(wPokeAnimFramesAddr + 1);
    RET;

}

void GetMonBitmaskPointer(void){
    CALL(aPokeAnim_IsEgg);
    IF_Z goto egg;

    CALL(aPokeAnim_IsUnown);
    LD_A(BANK(aUnownBitmasksPointers));
    LD_HL(mUnownBitmasksPointers);
    IF_Z goto unown;
    LD_A(BANK(aBitmasksPointers));
    LD_HL(mBitmasksPointers);

unown:
    LD_addr_A(wPokeAnimBitmaskBank);

    LD_A_addr(wPokeAnimSpeciesOrUnown);
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_addr(wPokeAnimBitmaskBank);
    CALL(aGetFarWord);
    LD_A_L;
    LD_addr_A(wPokeAnimBitmaskAddr);
    LD_A_H;
    LD_addr_A(wPokeAnimBitmaskAddr + 1);
    RET;


egg:
    LD_C(BANK(aEggBitmasks));
    LD_HL(mEggBitmasks);
    LD_A_C;
    LD_addr_A(wPokeAnimBitmaskBank);
    LD_A_L;
    LD_addr_A(wPokeAnimBitmaskAddr);
    LD_A_H;
    LD_addr_A(wPokeAnimBitmaskAddr + 1);
    RET;

}

void PokeAnim_GetSpeciesOrUnown(void){
    CALL(aPokeAnim_IsUnown);
    IF_Z goto unown;
    LD_A_addr(wPokeAnimSpecies);
    RET;


unown:
    LD_A_addr(wPokeAnimUnownLetter);
    RET;

}

uint8_t PokeAnim_GetSpeciesOrUnown_Conv(species_t a){
    // CALL(aPokeAnim_IsUnown);
    // IF_Z goto unown;
    // LD_A_addr(wPokeAnimSpecies);
    // RET;


// unown:
    // LD_A_addr(wPokeAnimUnownLetter);
    // RET;
    return PokeAnim_IsUnown_Conv(a)? pokeAnim->unownLetter: pokeAnim->species;
}

void Unused_HOF_AnimateAlignedFrontpic(void){
    LD_A(0x1);
    LD_addr_A(wBoxAlignment);

    return HOF_AnimateFrontpic();
}

void HOF_AnimateFrontpic(void){
    CALL(aAnimateMon_CheckIfPokemon);
    IF_C goto fail;
    LD_H_D;
    LD_L_E;
    PUSH_BC;
    PUSH_HL;
    LD_DE(vTiles2);
    PREDEF(pGetAnimatedFrontpic);
    POP_HL;
    POP_BC;
    LD_D(0);
    LD_E_C;
    CALL(aAnimateFrontpic);
    XOR_A_A;
    LD_addr_A(wBoxAlignment);
    RET;


fail:
    XOR_A_A;
    LD_addr_A(wBoxAlignment);
    INC_A;
    LD_addr_A(wCurPartySpecies);
    RET;

}

void HOF_AnimateFrontpic_Conv(uint8_t* de, uint8_t c){
    // CALL(aAnimateMon_CheckIfPokemon);
    // IF_C goto fail;
    if(!AnimateMon_CheckIfPokemon_Conv()) {
    // fail:
        // XOR_A_A;
        // LD_addr_A(wBoxAlignment);
        wram->wBoxAlignment = 0x0;
        // INC_A;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = BULBASAUR;
        // RET;
        return;
    }
    // LD_H_D;
    // LD_L_E;
    // PUSH_BC;
    // PUSH_HL;
    // LD_DE(vTiles2);
    // PREDEF(pGetAnimatedFrontpic);
    GetAnimatedFrontpic_Conv(vram->vTiles2, 0);
    // POP_HL;
    // POP_BC;
    // LD_D(0);
    // LD_E_C;
    // CALL(aAnimateFrontpic);
    AnimateFrontpic_Conv(de, 0, c);
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x0;
    // RET;
}
