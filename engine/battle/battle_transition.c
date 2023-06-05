#include "../../constants.h"
#include "battle_transition.h"

//  BattleTransitionJumptable.Jumptable indexes
#define BATTLETRANSITION_CAVE     (0x01)
#define BATTLETRANSITION_CAVE_STRONGER (0x09)
#define BATTLETRANSITION_NO_CAVE (0x10)
#define BATTLETRANSITION_NO_CAVE_STRONGER (0x18)
#define BATTLETRANSITION_FINISH (0x20)
#define BATTLETRANSITION_END (0x80)

#define BATTLETRANSITION_SQUARE (0xFE)  //  $fe
#define BATTLETRANSITION_BLACK (0xFF)  //  $ff

void DoBattleTransition(void){
    CALL(aDoBattleTransition_InitGFX);
    LDH_A_addr(rBGP);
    LD_addr_A(wBGP);
    LDH_A_addr(rOBP0);
    LD_addr_A(wOBP0);
    LDH_A_addr(rOBP1);
    LD_addr_A(wOBP1);
    CALL(aDelayFrame);
    LD_HL(hVBlank);
    LD_A_hl;
    PUSH_AF;
    LD_hl(0x1);


loop:
    LD_A_addr(wJumptableIndex);
    BIT_A(7);  // BATTLETRANSITION_END?
    IF_NZ goto done;
    CALL(aBattleTransitionJumptable);
    CALL(aDelayFrame);
    goto loop;


done:
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);

    LD_HL(wBGPals1);
    LD_BC(8 * PALETTE_SIZE);
    XOR_A_A;
    CALL(aByteFill);

    POP_AF;
    LDH_addr_A(rSVBK);

    LD_A(0b11111111);
    LD_addr_A(wBGP);
    CALL(aDmgToCgbBGPals);
    CALL(aDelayFrame);
    XOR_A_A;
    LDH_addr_A(hLCDCPointer);
    LDH_addr_A(hLYOverrideStart);
    LDH_addr_A(hLYOverrideEnd);
    LDH_addr_A(hSCY);

    LD_A(0x1);  // unnecessary bankswitch?
    LDH_addr_A(rSVBK);
    POP_AF;
    LDH_addr_A(hVBlank);
    CALL(aDelayFrame);
    RET;


InitGFX:
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    IF_Z goto mobile;
    FARCALL(aReanchorBGMap_NoOAMUpdate);
    CALL(aUpdateSprites);
    CALL(aDelayFrame);
    CALL(aDoBattleTransition_NonMobile_LoadPokeballTiles);
    CALL(aBattleStart_CopyTilemapAtOnce);
    goto resume;


mobile:
    CALL(aLoadTrainerBattlePokeballTiles);


resume:
    LD_A(SCREEN_HEIGHT_PX);
    LDH_addr_A(hWY);
    CALL(aDelayFrame);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_HL(wJumptableIndex);
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    CALL(aWipeLYOverrides);
    RET;


NonMobile_LoadPokeballTiles:
    CALL(aLoadTrainerBattlePokeballTiles);
    hlbgcoord(0, 0, vBGMap0);
    CALL(aConvertTrainerBattlePokeballTilesTo2bpp);
    RET;

}

void LoadTrainerBattlePokeballTiles(void){
//  Load the tiles used in the Pokeball Graphic that fills the screen
//  at the start of every Trainer battle.
    LD_DE(mTrainerBattlePokeballTiles);
    LD_HL(vTiles0 + LEN_2BPP_TILE * BATTLETRANSITION_SQUARE);
    LD_B(BANK(aTrainerBattlePokeballTiles));
    LD_C(2);
    CALL(aRequest2bpp);

    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rVBK);

    LD_DE(mTrainerBattlePokeballTiles);
    LD_HL(vTiles3 + LEN_2BPP_TILE * BATTLETRANSITION_SQUARE);
    LD_B(BANK(aTrainerBattlePokeballTiles));
    LD_C(2);
    CALL(aRequest2bpp);

    POP_AF;
    LDH_addr_A(rVBK);
    RET;

}

void ConvertTrainerBattlePokeballTilesTo2bpp(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);
    PUSH_HL;
    LD_HL(wDecompressScratch);
    LD_BC(0x28 * LEN_2BPP_TILE);


loop:
    LD_hl(-1);
    INC_HL;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;

    POP_HL;
    LD_DE(wDecompressScratch);
    //LD_B(BANK(@));
    LD_C(0x28);
    CALL(aRequest2bpp);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void TrainerBattlePokeballTiles(void){
// INCBIN "gfx/overworld/trainer_battle_pokeball_tiles.2bpp"

    return BattleTransitionJumptable();
}

void BattleTransitionJumptable(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']
    fast_jumptable(mBattleTransitionJumptable_Jumptable, wJumptableIndex);


Jumptable:
    //dw ['StartTrainerBattle_DetermineWhichAnimation'];  // 00

// BATTLETRANSITION_CAVE
    //dw ['StartTrainerBattle_LoadPokeBallGraphics'];  // 01
    //dw ['StartTrainerBattle_SetUpBGMap'];  // 02
    //dw ['StartTrainerBattle_Flash'];  // 03
    //dw ['StartTrainerBattle_Flash'];  // 04
    //dw ['StartTrainerBattle_Flash'];  // 05
    //dw ['StartTrainerBattle_NextScene'];  // 06
    //dw ['StartTrainerBattle_SetUpForWavyOutro'];  // 07
    //dw ['StartTrainerBattle_SineWave'];  // 08

// BATTLETRANSITION_CAVE_STRONGER
    //dw ['StartTrainerBattle_LoadPokeBallGraphics'];  // 09
    //dw ['StartTrainerBattle_SetUpBGMap'];  // 0a
    //dw ['StartTrainerBattle_Flash'];  // 0b
    //dw ['StartTrainerBattle_Flash'];  // 0c
    //dw ['StartTrainerBattle_Flash'];  // 0d
    //dw ['StartTrainerBattle_NextScene'];  // 0e
// There is no setup for this one
    //dw ['StartTrainerBattle_ZoomToBlack'];  // 0f

// BATTLETRANSITION_NO_CAVE
    //dw ['StartTrainerBattle_LoadPokeBallGraphics'];  // 10
    //dw ['StartTrainerBattle_SetUpBGMap'];  // 11
    //dw ['StartTrainerBattle_Flash'];  // 12
    //dw ['StartTrainerBattle_Flash'];  // 13
    //dw ['StartTrainerBattle_Flash'];  // 14
    //dw ['StartTrainerBattle_NextScene'];  // 15
    //dw ['StartTrainerBattle_SetUpForSpinOutro'];  // 16
    //dw ['StartTrainerBattle_SpinToBlack'];  // 17

// BATTLETRANSITION_NO_CAVE_STRONGER
    //dw ['StartTrainerBattle_LoadPokeBallGraphics'];  // 18
    //dw ['StartTrainerBattle_SetUpBGMap'];  // 19
    //dw ['StartTrainerBattle_Flash'];  // 1a
    //dw ['StartTrainerBattle_Flash'];  // 1b
    //dw ['StartTrainerBattle_Flash'];  // 1c
    //dw ['StartTrainerBattle_NextScene'];  // 1d
    //dw ['StartTrainerBattle_SetUpForRandomScatterOutro'];  // 1e
    //dw ['StartTrainerBattle_SpeckleToBlack'];  // 1f

// BATTLETRANSITION_FINISH
    //dw ['StartTrainerBattle_Finish'];  // 20

//  transition animations
    //const_def ['?']
    //const ['TRANS_CAVE']
    //const ['TRANS_CAVE_STRONGER']
    //const ['TRANS_NO_CAVE']
    //const ['TRANS_NO_CAVE_STRONGER']

//  transition animation bits
#define TRANS_STRONGER_F (0)  //  bit set in TRANS_CAVE_STRONGER and TRANS_NO_CAVE_STRONGER
#define TRANS_NO_CAVE_F (1)  //  bit set in TRANS_NO_CAVE and TRANS_NO_CAVE_STRONGER

    return StartTrainerBattle_DetermineWhichAnimation();
}

void StartTrainerBattle_DetermineWhichAnimation(void){
//  The screen flashes a different number of times depending on the level of
//  your lead Pokemon relative to the opponent's.
//  BUG: wBattleMonLevel and wEnemyMonLevel are not set at this point, so whatever
//  values happen to be there will determine the animation.
    LD_DE(0);
    LD_A_addr(wBattleMonLevel);
    ADD_A(3);
    LD_HL(wEnemyMonLevel);
    CP_A_hl;
    IF_NC goto not_stronger;
    SET_E(TRANS_STRONGER_F);

not_stronger:
    LD_A_addr(wEnvironment);
    CP_A(CAVE);
    IF_Z goto cave;
    CP_A(ENVIRONMENT_5);
    IF_Z goto cave;
    CP_A(DUNGEON);
    IF_Z goto cave;
    SET_E(TRANS_NO_CAVE_F);

cave:
    LD_HL(mStartTrainerBattle_DetermineWhichAnimation_StartingPoints);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wJumptableIndex);
    RET;


StartingPoints:
//  entries correspond to TRANS_* constants
    //db ['BATTLETRANSITION_CAVE'];
    //db ['BATTLETRANSITION_CAVE_STRONGER'];
    //db ['BATTLETRANSITION_NO_CAVE'];
    //db ['BATTLETRANSITION_NO_CAVE_STRONGER'];

    return StartTrainerBattle_Finish();
}

void StartTrainerBattle_Finish(void){
    CALL(aClearSprites);
    LD_A(BATTLETRANSITION_END);
    LD_addr_A(wJumptableIndex);
    RET;

}

void StartTrainerBattle_NextScene(void){
    LD_HL(wJumptableIndex);
    INC_hl;
    RET;

}

void StartTrainerBattle_SetUpBGMap(void){
    CALL(aStartTrainerBattle_NextScene);
    XOR_A_A;
    LD_addr_A(wBattleTransitionCounter);
    LDH_addr_A(hBGMapMode);
    RET;

}

void StartTrainerBattle_Flash(void){
    CALL(aStartTrainerBattle_Flash_DoFlashAnimation);
    RET_NC ;
    CALL(aStartTrainerBattle_NextScene);
    RET;


DoFlashAnimation:
    LD_A_addr(wTimeOfDayPalset);
    CP_A(DARKNESS_PALSET);
    IF_Z goto done;
    LD_HL(wBattleTransitionCounter);
    LD_A_hl;
    INC_hl;
    SRL_A;
    LD_E_A;
    LD_D(0);
    LD_HL(mStartTrainerBattle_Flash_pals);
    ADD_HL_DE;
    LD_A_hl;
    CP_A(0b00000001);
    IF_Z goto done;
    LD_addr_A(wBGP);
    CALL(aDmgToCgbBGPals);
    AND_A_A;
    RET;


done:
    XOR_A_A;
    LD_addr_A(wBattleTransitionCounter);
    SCF;
    RET;


pals:
    //dc ['3', '3', '2', '1']
    //dc ['3', '3', '3', '2']
    //dc ['3', '3', '3', '3']
    //dc ['3', '3', '3', '2']
    //dc ['3', '3', '2', '1']
    //dc ['3', '2', '1', '0']
    //dc ['2', '1', '0', '0']
    //dc ['1', '0', '0', '0']
    //dc ['0', '0', '0', '0']
    //dc ['1', '0', '0', '0']
    //dc ['2', '1', '0', '0']
    //dc ['3', '2', '1', '0']
    //dc ['0', '0', '0', '1']

    return StartTrainerBattle_SetUpForWavyOutro();
}

void StartTrainerBattle_SetUpForWavyOutro(void){
    FARCALL(aRespawnPlayerAndOpponent);
    LD_A(MBANK(awLYOverrides));
    LDH_addr_A(rSVBK);
    CALL(aStartTrainerBattle_NextScene);

    LD_A(LOW(rSCX));
    LDH_addr_A(hLCDCPointer);
    XOR_A_A;
    LDH_addr_A(hLYOverrideStart);
    LD_A(0x90);
    LDH_addr_A(hLYOverrideEnd);
    XOR_A_A;
    LD_addr_A(wBattleTransitionCounter);
    LD_addr_A(wBattleTransitionSineWaveOffset);
    RET;

}

void StartTrainerBattle_SineWave(void){
    LD_A_addr(wBattleTransitionCounter);
    CP_A(0x60);
    IF_NC goto end;
    CALL(aStartTrainerBattle_SineWave_DoSineWave);
    RET;


end:
    LD_A(BATTLETRANSITION_FINISH);
    LD_addr_A(wJumptableIndex);
    RET;


DoSineWave:
    LD_HL(wBattleTransitionSineWaveOffset);
    LD_A_hl;
    INC_hl;
    LD_HL(wBattleTransitionCounter);
    LD_D_hl;
    ADD_A_hl;
    LD_hl_A;
    LD_A(wLYOverridesEnd - wLYOverrides);
    LD_BC(wLYOverrides);
    LD_E(0);


loop:
    PUSH_AF;
    PUSH_DE;
    LD_A_E;
    CALL(aStartTrainerBattle_DrawSineWave);
    LD_bc_A;
    INC_BC;
    POP_DE;
    LD_A_E;
    ADD_A(2);
    LD_E_A;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    RET;

}

void StartTrainerBattle_SetUpForSpinOutro(void){
    FARCALL(aRespawnPlayerAndOpponent);
    LD_A(MBANK(awLYOverrides));
    LDH_addr_A(rSVBK);
    CALL(aStartTrainerBattle_NextScene);
    XOR_A_A;
    LD_addr_A(wBattleTransitionCounter);
    RET;

}

void StartTrainerBattle_SpinToBlack(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A_addr(wBattleTransitionCounter);
    LD_E_A;
    LD_D(0);
    LD_HL(mStartTrainerBattle_SpinToBlack_spin_quadrants);
    for(int rept = 0; rept < 5; rept++){
    ADD_HL_DE;
    }
    LD_A_hli;
    CP_A(-1);
    IF_Z goto end;
    LD_addr_A(wBattleTransitionSineWaveOffset);
    CALL(aStartTrainerBattle_SpinToBlack_load);
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    LD_HL(wBattleTransitionCounter);
    INC_hl;
    RET;


end:
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(BATTLETRANSITION_FINISH);
    LD_addr_A(wJumptableIndex);
    RET;

//  quadrants
    //const_def ['?']
    //const ['UPPER_LEFT']
    //const ['UPPER_RIGHT']
    //const ['LOWER_LEFT']
    //const ['LOWER_RIGHT']

//  quadrant bits
#define RIGHT_QUADRANT_F (0)  //  bit set in UPPER_RIGHT and LOWER_RIGHT
#define LOWER_QUADRANT_F (1)  //  bit set in LOWER_LEFT and LOWER_RIGHT


spin_quadrants:
// spin_quadrant: MACRO
//     db \1
//     dw \2
//     dwcoord \3, \4
// ENDM
    //spin_quadrant ['UPPER_LEFT', '.wedge1', '1', '6']
    //spin_quadrant ['UPPER_LEFT', '.wedge2', '0', '3']
    //spin_quadrant ['UPPER_LEFT', '.wedge3', '1', '0']
    //spin_quadrant ['UPPER_LEFT', '.wedge4', '5', '0']
    //spin_quadrant ['UPPER_LEFT', '.wedge5', '9', '0']
    //spin_quadrant ['UPPER_RIGHT', '.wedge5', '10', '0']
    //spin_quadrant ['UPPER_RIGHT', '.wedge4', '14', '0']
    //spin_quadrant ['UPPER_RIGHT', '.wedge3', '18', '0']
    //spin_quadrant ['UPPER_RIGHT', '.wedge2', '19', '3']
    //spin_quadrant ['UPPER_RIGHT', '.wedge1', '18', '6']
    //spin_quadrant ['LOWER_RIGHT', '.wedge1', '18', '11']
    //spin_quadrant ['LOWER_RIGHT', '.wedge2', '19', '14']
    //spin_quadrant ['LOWER_RIGHT', '.wedge3', '18', '17']
    //spin_quadrant ['LOWER_RIGHT', '.wedge4', '14', '17']
    //spin_quadrant ['LOWER_RIGHT', '.wedge5', '10', '17']
    //spin_quadrant ['LOWER_LEFT', '.wedge5', '9', '17']
    //spin_quadrant ['LOWER_LEFT', '.wedge4', '5', '17']
    //spin_quadrant ['LOWER_LEFT', '.wedge3', '1', '17']
    //spin_quadrant ['LOWER_LEFT', '.wedge2', '0', '14']
    //spin_quadrant ['LOWER_LEFT', '.wedge1', '1', '11']
    //db ['-1'];


load:
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

loop:
    PUSH_HL;
    LD_A_de;
    LD_C_A;
    INC_DE;

loop1:
    LD_hl(BATTLETRANSITION_BLACK);
    LD_A_addr(wBattleTransitionSineWaveOffset);
    BIT_A(RIGHT_QUADRANT_F);
    IF_Z goto leftside;
    INC_HL;
    goto okay1;

leftside:
    DEC_HL;

okay1:
    DEC_C;
    IF_NZ goto loop1;
    POP_HL;
    LD_A_addr(wBattleTransitionSineWaveOffset);
    BIT_A(LOWER_QUADRANT_F);
    LD_BC(SCREEN_WIDTH);
    IF_Z goto upper;
    LD_BC(-SCREEN_WIDTH);

upper:
    ADD_HL_BC;
    LD_A_de;
    INC_DE;
    CP_A(-1);
    RET_Z ;
    AND_A_A;
    IF_Z goto loop;
    LD_C_A;

loop2:
    LD_A_addr(wBattleTransitionSineWaveOffset);
    BIT_A(RIGHT_QUADRANT_F);
    IF_Z goto leftside2;
    DEC_HL;
    goto okay2;

leftside2:
    INC_HL;

okay2:
    DEC_C;
    IF_NZ goto loop2;
    goto loop;


wedge1:
// db 2, 3, 5, 4, 9, -1

wedge2:
// db 1, 1, 2, 2, 4, 2, 4, 2, 3, -1

wedge3:
// db 2, 1, 3, 1, 4, 1, 4, 1, 4, 1, 3, 1, 2, 1, 1, 1, 1, -1

wedge4:
// db 4, 1, 4, 0, 3, 1, 3, 0, 2, 1, 2, 0, 1, -1

wedge5:
// db 4, 0, 3, 0, 3, 0, 2, 0, 2, 0, 1, 0, 1, 0, 1, -1

    return StartTrainerBattle_SetUpForRandomScatterOutro();
}

void StartTrainerBattle_SetUpForRandomScatterOutro(void){
    FARCALL(aRespawnPlayerAndOpponent);
    LD_A(MBANK(awLYOverrides));
    LDH_addr_A(rSVBK);
    CALL(aStartTrainerBattle_NextScene);
    LD_A(0x10);
    LD_addr_A(wBattleTransitionCounter);
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void StartTrainerBattle_SpeckleToBlack(void){
    LD_HL(wBattleTransitionCounter);
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    DEC_hl;
    LD_C(0xc);

loop:
    PUSH_BC;
    CALL(aStartTrainerBattle_SpeckleToBlack_BlackOutRandomTile);
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;


done:
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(BATTLETRANSITION_FINISH);
    LD_addr_A(wJumptableIndex);
    RET;


BlackOutRandomTile:

y_loop:
    CALL(aRandom);
    CP_A(SCREEN_HEIGHT);
    IF_NC goto y_loop;
    LD_B_A;


x_loop:
    CALL(aRandom);
    CP_A(SCREEN_WIDTH);
    IF_NC goto x_loop;
    LD_C_A;

    hlcoord(0, -1, wTilemap);
    LD_DE(SCREEN_WIDTH);
    INC_B;


row_loop:
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto row_loop;
    ADD_HL_BC;

//  If the tile has already been blacked out,
//  sample a new tile
    LD_A_hl;
    CP_A(BATTLETRANSITION_BLACK);
    IF_Z goto y_loop;
    LD_hl(BATTLETRANSITION_BLACK);
    RET;

}

void StartTrainerBattle_LoadPokeBallGraphics(void){
    LD_A_addr(wOtherTrainerClass);
    AND_A_A;
    JP_Z (mStartTrainerBattle_LoadPokeBallGraphics_nextscene);  // don't need to be here if wild

    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    INC_B;
    INC_C;
    goto enter_loop_midway;


pal_loop:
//  set all pals to 7
    LD_A_hl;
    OR_A(PAL_BG_TEXT);
    LD_hli_A;

enter_loop_midway:
    DEC_C;
    IF_NZ goto pal_loop;
    DEC_B;
    IF_NZ goto pal_loop;

    CALL(aStartTrainerBattle_LoadPokeBallGraphics_loadpokeballgfx);
    hlcoord(2, 1, wTilemap);

    LD_B(SCREEN_WIDTH - 4);

tile_loop:
    PUSH_HL;
    LD_C(2);

row_loop:
    PUSH_HL;
    LD_A_de;
    INC_DE;

col_loop:
//  Loading is done bit by bit
    AND_A_A;
    IF_Z goto done;
    SLA_A;
    IF_NC goto no_load;
    LD_hl(BATTLETRANSITION_SQUARE);

no_load:
    INC_HL;
    goto col_loop;


done:
    POP_HL;
    PUSH_BC;
    LD_BC((SCREEN_WIDTH - 4) / 2);
    ADD_HL_BC;
    POP_BC;
    DEC_C;
    IF_NZ goto row_loop;

    POP_HL;
    PUSH_BC;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto tile_loop;

    LDH_A_addr(hCGB);
    AND_A_A;
    IF_NZ goto cgb;
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    goto nextscene;


cgb:
    LD_HL(mStartTrainerBattle_LoadPokeBallGraphics_pals);
    LD_A_addr(wTimeOfDayPal);
    maskbits(NUM_DAYTIMES, 0);
    CP_A(DARKNESS_F);
    IF_NZ goto not_dark;
    LD_HL(mStartTrainerBattle_LoadPokeBallGraphics_darkpals);

not_dark:
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awBGPals1));
    LDH_addr_A(rSVBK);
    CALL(aStartTrainerBattle_LoadPokeBallGraphics_copypals);
    PUSH_HL;
    LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_HL;
    LD_DE(wBGPals2 + PALETTE_SIZE * PAL_BG_TEXT);
    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    CALL(aDelayFrame);
    CALL(aBattleStart_CopyTilemapAtOnce);


nextscene:
    CALL(aStartTrainerBattle_NextScene);
    RET;


copypals:
    LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    LD_DE(wBGPals2 + PALETTE_SIZE * PAL_BG_TEXT);
    CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    LD_DE(wOBPals1 + PALETTE_SIZE * PAL_OW_TREE);
    CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    LD_DE(wOBPals2 + PALETTE_SIZE * PAL_OW_TREE);
    CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    LD_DE(wOBPals1 + PALETTE_SIZE * PAL_OW_ROCK);
    CALL(aStartTrainerBattle_LoadPokeBallGraphics_copy);
    LD_DE(wOBPals2 + PALETTE_SIZE * PAL_OW_ROCK);


copy:
    PUSH_HL;
    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_HL;
    RET;


pals:
// INCLUDE "gfx/overworld/trainer_battle.pal"


darkpals:
// INCLUDE "gfx/overworld/trainer_battle_dark.pal"


loadpokeballgfx:
    LD_A_addr(wOtherTrainerClass);
    LD_DE(mPokeBallTransition);
    RET;

}

void PokeBallTransition(void){
//  16x16 overlay of a Poke Ball
//pusho
//opt b.X   //  . = 0, X = 1
    //bigdw ['0b......XXXX......']
    //bigdw ['0b....XXXXXXXX....']
    //bigdw ['0b..XXXX....XXXX..']
    //bigdw ['0b..XX........XX..']
    //bigdw ['0b.XX..........XX.']
    //bigdw ['0b.XX...XXXX...XX.']
    //bigdw ['0bXX...XX..XX...XX']
    //bigdw ['0bXXXXXX....XXXXXX']
    //bigdw ['0bXXXXXX....XXXXXX']
    //bigdw ['0bXX...XX..XX...XX']
    //bigdw ['0b.XX...XXXX...XX.']
    //bigdw ['0b.XX..........XX.']
    //bigdw ['0b..XX........XX..']
    //bigdw ['0b..XXXX....XXXX..']
    //bigdw ['0b....XXXXXXXX....']
    //bigdw ['0b......XXXX......']
//popo

    return WipeLYOverrides();
}

void WipeLYOverrides(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awLYOverrides));
    LDH_addr_A(rSVBK);

    LD_HL(wLYOverrides);
    CALL(aWipeLYOverrides_wipe);
    LD_HL(wLYOverridesBackup);
    CALL(aWipeLYOverrides_wipe);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


wipe:
    XOR_A_A;
    LD_C(SCREEN_HEIGHT_PX);

loop:
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void StartTrainerBattle_DrawSineWave(void){
    //calc_sine_wave ['?']

    return StartTrainerBattle_ZoomToBlack();
}

void StartTrainerBattle_ZoomToBlack(void){
    FARCALL(aRespawnPlayerAndOpponent);
    LD_DE(mStartTrainerBattle_ZoomToBlack_boxes);


loop:
    LD_A_de;
    CP_A(-1);
    IF_Z goto done;
    INC_DE;
    LD_C_A;
    LD_A_de;
    INC_DE;
    LD_B_A;
    LD_A_de;
    INC_DE;
    LD_L_A;
    LD_A_de;
    INC_DE;
    LD_H_A;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aStartTrainerBattle_ZoomToBlack_Copy);
    CALL(aWaitBGMap);
    goto loop;


done:
    LD_A(BATTLETRANSITION_FINISH);
    LD_addr_A(wJumptableIndex);
    RET;


boxes:
// zoombox: MACRO
// ; width, height, start y, start x
//     db \1, \2
//     dwcoord \3, \4
// ENDM
    //zoombox ['4', '2', '8', '8']
    //zoombox ['6', '4', '7', '7']
    //zoombox ['8', '6', '6', '6']
    //zoombox ['10', '8', '5', '5']
    //zoombox ['12', '10', '4', '4']
    //zoombox ['14', '12', '3', '3']
    //zoombox ['16', '14', '2', '2']
    //zoombox ['18', '16', '1', '1']
    //zoombox ['20', '18', '0', '0']
    //db ['-1'];


Copy:
    LD_A(BATTLETRANSITION_BLACK);

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

void UnusedWaitBGMapOnce(void){
//  //  unreferenced
    LD_A(1);
    LDH_addr_A(hBGMapMode);  // redundant
    CALL(aWaitBGMap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    RET;

}
