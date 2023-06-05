#include "../../constants.h"
#include "functions.h"

void DoBattleAnimFrame(void) {
    SET_PC(aDoBattleAnimFrame);
    LD_HL(BATTLEANIMSTRUCT_FUNCTION);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    LD_HL(mDoBattleAnimFrame_Jumptable);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;

Jumptable:

    //  entries correspond to BATTLEANIMFUNC_* constants
    // dw ['BattleAnimFunction_Null'];
    // dw ['BattleAnimFunction_MoveFromUserToTarget'];
    // dw ['BattleAnimFunction_MoveFromUserToTargetAndDisappear'];
    // dw ['BattleAnimFunction_MoveInCircle'];
    // dw ['BattleAnimFunction_MoveWaveToTarget'];
    // dw ['BattleAnimFunction_ThrowFromUserToTarget'];
    // dw ['BattleAnimFunction_ThrowFromUserToTargetAndDisappear'];
    // dw ['BattleAnimFunction_Drop'];
    // dw ['BattleAnimFunction_MoveFromUserToTargetSpinAround'];
    // dw ['BattleAnimFunction_Shake'];
    // dw ['BattleAnimFunction_FireBlast'];
    // dw ['BattleAnimFunction_RazorLeaf'];
    // dw ['BattleAnimFunction_Bubble'];
    // dw ['BattleAnimFunction_Surf'];
    // dw ['BattleAnimFunction_Sing'];
    // dw ['BattleAnimFunction_WaterGun'];
    // dw ['BattleAnimFunction_Ember'];
    // dw ['BattleAnimFunction_Powder'];
    // dw ['BattleAnimFunction_PokeBall'];
    // dw ['BattleAnimFunction_PokeBallBlocked'];
    // dw ['BattleAnimFunction_Recover'];
    // dw ['BattleAnimFunction_ThunderWave'];
    // dw ['BattleAnimFunction_Clamp_Encore'];
    // dw ['BattleAnimFunction_Bite'];
    // dw ['BattleAnimFunction_SolarBeam'];
    // dw ['BattleAnimFunction_Gust'];
    // dw ['BattleAnimFunction_RazorWind'];
    // dw ['BattleAnimFunction_Kick'];
    // dw ['BattleAnimFunction_Absorb'];
    // dw ['BattleAnimFunction_Egg'];
    // dw ['BattleAnimFunction_MoveUp'];
    // dw ['BattleAnimFunction_Wrap'];
    // dw ['BattleAnimFunction_LeechSeed'];
    // dw ['BattleAnimFunction_Sound'];
    // dw ['BattleAnimFunction_ConfuseRay'];
    // dw ['BattleAnimFunction_Dizzy'];
    // dw ['BattleAnimFunction_Amnesia'];
    // dw ['BattleAnimFunction_FloatUp'];
    // dw ['BattleAnimFunction_Dig'];
    // dw ['BattleAnimFunction_String'];
    // dw ['BattleAnimFunction_Paralyzed'];
    // dw ['BattleAnimFunction_SpiralDescent'];
    // dw ['BattleAnimFunction_PoisonGas'];
    // dw ['BattleAnimFunction_Horn'];
    // dw ['BattleAnimFunction_Needle'];
    // dw ['BattleAnimFunction_PetalDance'];
    // dw ['BattleAnimFunction_ThiefPayday'];
    // dw ['BattleAnimFunction_AbsorbCircle'];
    // dw ['BattleAnimFunction_Bonemerang'];
    // dw ['BattleAnimFunction_Shiny'];
    // dw ['BattleAnimFunction_SkyAttack'];
    // dw ['BattleAnimFunction_GrowthSwordsDance'];
    // dw ['BattleAnimFunction_SmokeFlameWheel'];
    // dw ['BattleAnimFunction_PresentSmokescreen'];
    // dw ['BattleAnimFunction_StrengthSeismicToss'];
    // dw ['BattleAnimFunction_SpeedLine'];
    // dw ['BattleAnimFunction_Sludge'];
    // dw ['BattleAnimFunction_MetronomeHand'];
    // dw ['BattleAnimFunction_MetronomeSparkleSketch'];
    // dw ['BattleAnimFunction_Agility'];
    // dw ['BattleAnimFunction_SacredFire'];
    // dw ['BattleAnimFunction_SafeguardProtect'];
    // dw ['BattleAnimFunction_LockOnMindReader'];
    // dw ['BattleAnimFunction_Spikes'];
    // dw ['BattleAnimFunction_HealBellNotes'];
    // dw ['BattleAnimFunction_BatonPass'];
    // dw ['BattleAnimFunction_Conversion'];
    // dw ['BattleAnimFunction_EncoreBellyDrum'];
    // dw ['BattleAnimFunction_SwaggerMorningSun'];
    // dw ['BattleAnimFunction_HiddenPower'];
    // dw ['BattleAnimFunction_Curse'];
    // dw ['BattleAnimFunction_PerishSong'];
    // dw ['BattleAnimFunction_RapidSpin'];
    // dw ['BattleAnimFunction_BetaPursuit'];
    // dw ['BattleAnimFunction_RainSandstorm'];
    // dw ['BattleAnimFunction_AnimObjB0'];
    // dw ['BattleAnimFunction_PsychUp'];
    // dw ['BattleAnimFunction_AncientPower'];
    // dw ['BattleAnimFunction_RockSmash'];
    // dw ['BattleAnimFunction_Cotton'];

    return BattleAnimFunction_Null();
}

void BattleAnimFunction_Null(void) {
    SET_PC(aBattleAnimFunction_Null);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

one:

    CALL(aDeinitBattleAnimation);

zero:

    RET;
}

void BattleAnimFunction_ThrowFromUserToTargetAndDisappear(void) {
    SET_PC(aBattleAnimFunction_ThrowFromUserToTargetAndDisappear);
    CALL(aBattleAnimFunction_ThrowFromUserToTarget);
    RET_C;
    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_ThrowFromUserToTarget(void) {
    SET_PC(aBattleAnimFunction_ThrowFromUserToTarget);
    // If x coord at $88 or beyond, abort.
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x88);
    RET_NC;
    // Move right 2 pixels
    ADD_A(0x2);
    LD_hl_A;
    // Move down 1 pixel
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;
    // Decrease var1 and hold onto its previous value (argument of the sine function)
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_hl;
    // Get param (amplitude of the sine function)
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    // Store the sine result in the Y offset
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    // Carry flag denotes success
    SCF;
    RET;
}

void BattleAnimFunction_MoveWaveToTarget(void) {
    SET_PC(aBattleAnimFunction_MoveWaveToTarget);
    //  Wave motion from one mon to another. Obj is cleared when it reaches x coord $88. Examples: Shadow Ball, Dragon Rage
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x88);
    IF_C goto move;
    CALL(aDeinitBattleAnimation);
    RET;

move:

    ADD_A(0x2);
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    INC_hl;
    INC_hl;
    INC_hl;
    LD_D(0x10);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    SRA_A;
    SRA_A;
    SRA_A;
    SRA_A;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_MoveInCircle(void) {
    SET_PC(aBattleAnimFunction_MoveInCircle);
    //  Slow circular motion. Examples: Thundershock, Flamethrower
    //  Obj Param: Distance from center (masked with $7F). Bit 7 causes object to start on other side of the circle
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    BIT_hl(7);
    LD_A(0x0);
    IF_Z goto got_starting_position;
    LD_A(0x20);

got_starting_position:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x7f);
    LD_hl_A;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_D_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void BattleAnimFunction_MoveFromUserToTarget(void) {
    SET_PC(aBattleAnimFunction_MoveFromUserToTarget);
    //  Moves object diagonally at a ~30° angle towards opponent and stops when it reaches x coord $84. Obj Param changes the speed
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

one:

    CALL(aDeinitBattleAnimation);
    RET;

zero:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x84);
    RET_NC;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aBattleAnim_StepToTarget);
    RET;
}

void BattleAnimFunction_MoveFromUserToTargetAndDisappear(void) {
    SET_PC(aBattleAnimFunction_MoveFromUserToTargetAndDisappear);
    //  Same as BattleAnimFunction_01 but objs are cleared when they reach x coord $84
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x84);
    IF_NC goto done;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aBattleAnim_StepToTarget);
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_PokeBall(void) {
    SET_PC(aBattleAnimFunction_PokeBall);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;
    if (REG_BC == 5) goto five;
    if (REG_BC == 6) goto six;
    if (REG_BC == 7) goto seven;
    if (REG_BC == 8) goto eight;
    if (REG_BC == 9) goto nine;
    if (REG_BC == 10) goto ten;
    if (REG_BC == 11) goto eleven;

zero:
    //
    //  init
    CALL(aGetBallAnimPal);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

one:

    CALL(aBattleAnimFunction_ThrowFromUserToTarget);
    RET_C;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    LD_A(BATTLEANIMFRAMESET_0B);
    CALL(aReinitBattleAnimFrameset);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

three:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(BATTLEANIMFRAMESET_09);
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x0);
    INC_HL;
    LD_hl(0x10);

four:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_A;
    LD_hl_A;
    AND_A(0x1f);
    RET_NZ;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A(0x4);
    LD_hl_A;
    RET_NZ;
    LD_A(BATTLEANIMFRAMESET_0C);
    CALL(aReinitBattleAnimFrameset);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

six:

    LD_A(BATTLEANIMFRAMESET_0D);
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    DEC_hl;

two:

five:

nine:

    RET;

seven:

    CALL(aGetBallAnimPal);
    LD_A(BATTLEANIMFRAMESET_0A);
    CALL(aReinitBattleAnimFrameset);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl(0x20);

eight:

ten:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_A;
    LD_hl_A;
    AND_A(0x1f);
    IF_Z goto eleven;
    AND_A(0xf);
    RET_NZ;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

eleven:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_PokeBallBlocked(void) {
    SET_PC(aBattleAnimFunction_PokeBallBlocked);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aGetBallAnimPal);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x70);
    IF_NC goto next;
    CALL(aBattleAnimFunction_ThrowFromUserToTarget);
    RET;

next:

    CALL(aBattleAnim_IncAnonJumptableIndex);

two:

    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x80);
    IF_NC goto done;
    ADD_A(0x4);
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    DEC_hl;
    DEC_hl;
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void GetBallAnimPal(void) {
    SET_PC(aGetBallAnimPal);
    LD_HL(mBallColors);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awCurItem));
    LDH_addr_A(rSVBK);
    LD_A_addr(wCurItem);
    LD_E_A;
    POP_AF;
    LDH_addr_A(rSVBK);

IsInArray:

    LD_A_hli;
    CP_A(-1);
    IF_Z goto load;
    CP_A_E;
    IF_Z goto load;
    INC_HL;
    goto IsInArray;

load:

    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_PALETTE);
    ADD_HL_BC;
    LD_hl_A;
    RET;

    // INCLUDE "data/battle_anims/ball_colors.asm"

    return BattleAnimFunction_Ember();
}

void BattleAnimFunction_Ember(void) {
    SET_PC(aBattleAnimFunction_Ember);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;

zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x88);
    RET_NC;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aBattleAnim_StepToTarget);
    RET;

two:

    CALL(aDeinitBattleAnimation);
    RET;

three:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(BATTLEANIMFRAMESET_0F);
    CALL(aReinitBattleAnimFrameset);

four:

    RET;
}

void BattleAnimFunction_Drop(void) {
    SET_PC(aBattleAnimFunction_Drop);
    //  Drops obj. The Obj Param dictates how fast it is (lower value is faster) and how long it stays bouncing (lower value is longer). Example: Rock Slide
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x30);
    INC_HL;
    LD_hl(0x48);

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    AND_A(0x3f);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x20);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    SUB_A_hl;
    IF_Z goto done;
    IF_C goto done;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_A;
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_MoveFromUserToTargetSpinAround(void) {
    SET_PC(aBattleAnimFunction_MoveFromUserToTargetSpinAround);
    //  Object moves from user to target target and spins around it once. Example: Fire Spin, Swift
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

zero:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x80);
    IF_NC goto next;
    CALL(aBattleAnimFunction_MoveFromUserToTargetSpinAround_SetCoords);
    RET;

next:

    CALL(aBattleAnim_IncAnonJumptableIndex);

one:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x0);

two:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x40);
    IF_NC goto loop_back;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x18);
    CALL(aBattleAnim_Cosine);
    SUB_A(0x18);
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x18);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    RET;

loop_back:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf0);
    IF_Z goto finish;
    SUB_A(0x10);
    LD_D_A;
    LD_A_hl;
    AND_A(0xf);
    OR_A_D;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    DEC_hl;
    RET;

finish:

    CALL(aBattleAnim_IncAnonJumptableIndex);

three:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xb0);
    IF_C goto retain;
    CALL(aDeinitBattleAnimation);
    RET;

retain:

    CALL(aBattleAnimFunction_MoveFromUserToTargetSpinAround_SetCoords);
    RET;

SetCoords:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    LD_E_A;
    SRL_E;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;

loop:

    DEC_hl;
    DEC_E;
    IF_NZ goto loop;
    RET;
}

void BattleAnimFunction_Shake(void) {
    SET_PC(aBattleAnimFunction_Shake);
    //  Object switches position side to side. Obj Param defines how far to move it. Example: Dynamic Punch
    //  Some objects use this function with a Param of 0
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x0);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto done_one;
    DEC_hl;
    RET;

done_one:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0xff);
    INC_A;
    LD_hl_A;
    RET;

two:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_FireBlast(void) {
    SET_PC(aBattleAnimFunction_FireBlast);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;
    if (REG_BC == 5) goto five;
    if (REG_BC == 6) goto six;
    if (REG_BC == 7) goto seven;
    if (REG_BC == 8) goto eight;
    if (REG_BC == 9) goto nine;

zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    CP_A(0x7);
    IF_Z goto seven;
    LD_A(BATTLEANIMFRAMESET_11);
    CALL(aReinitBattleAnimFrameset);
    RET;

seven:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x88);
    IF_NC goto set_up_eight;
    ADD_A(0x2);
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;
    RET;

set_up_eight:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(BATTLEANIMFRAMESET_10);
    CALL(aReinitBattleAnimFrameset);

eight:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x10);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    RET;

nine:

    CALL(aDeinitBattleAnimation);
    RET;

one:

    // Flame that moves upward
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    DEC_hl;
    RET;

four:

    // Flame that moves down and left
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    INC_hl;

two:

    // Flame that moves left
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    DEC_hl;
    RET;

five:

    // Flame that moves down and right
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    INC_hl;

three:

    // Flame that moves right
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    INC_hl;

six:

    RET;
}

void BattleAnimFunction_RazorLeaf(void) {
    SET_PC(aBattleAnimFunction_RazorLeaf);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;
    if (REG_BC == 5) goto five;
    if (REG_BC == 6) goto six;
    if (REG_BC == 7) goto seven;
    if (REG_BC == 8) goto eight;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x40);

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x30);
    IF_NC goto sine_cosine;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    XOR_A_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hli_A;
    LD_hl_A;
    LD_A(BATTLEANIMFRAMESET_17);
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    BIT_hl(6);
    RET_Z;
    LD_HL(BATTLEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_hl(0x5);
    RET;

sine_cosine:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3f);
    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_hl;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aBattleAnim_ScatterHorizontal);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_E;
    RET;

two:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    IF_NZ goto sine_cosine_2;
    CALL(aDeinitBattleAnimation);
    RET;

sine_cosine_2:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x10);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    BIT_hl(6);
    IF_NZ goto decrease;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    goto finish;

decrease:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    DEC_hl;

finish:

    LD_DE(0x80);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_E;
    RET;

three:

    LD_A(BATTLEANIMFRAMESET_16);
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
    ADD_HL_BC;
    RES_hl(5);

four:

five:

six:

seven:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

eight:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xc0);
    RET_NC;
    LD_A(0x8);
    CALL(aBattleAnim_StepToTarget);
    RET;
}

void BattleAnim_ScatterHorizontal(void) {
    SET_PC(aBattleAnim_ScatterHorizontal);
    //  Affects horizontal sine movement based on bit 7 of Obj Param
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    BIT_A(7);
    IF_NZ goto negative;
    CP_A(0x20);
    IF_NC goto plus_256;
    CP_A(0x18);
    IF_NC goto plus_384;
    LD_DE(0x200);
    RET;

plus_384:

    LD_DE(0x180);
    RET;

plus_256:

    LD_DE(0x100);
    RET;

negative:

    AND_A(0b00111111);
    CP_A(0x20);
    IF_NC goto minus_256;
    CP_A(0x18);
    IF_NC goto minus_384;
    LD_DE(-0x200);
    RET;

minus_384:

    LD_DE(-0x180);
    RET;

minus_256:

    LD_DE(-0x100);
    RET;
}

void BattleAnimFunction_RockSmash(void) {
    SET_PC(aBattleAnimFunction_RockSmash);
    //  Object moves at an arc
    //  Obj Param: Bit 7 makes arc flip horizontally
    //             Bit 6 defines offset from base frameset FRAMESET_19
    //             Rest defines arc radius
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x40);
    RLCA;
    RLCA;
    ADD_A(BATTLEANIMFRAMESET_19);
    LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x40);

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x30);
    IF_NC goto sine_cosine;
    CALL(aDeinitBattleAnimation);
    RET;

sine_cosine:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3f);
    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_hl;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aBattleAnim_ScatterHorizontal);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_E;
    RET;
}

void BattleAnimFunction_Bubble(void) {
    SET_PC(aBattleAnimFunction_Bubble);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0xc);

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto next;
    DEC_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aBattleAnim_StepToTarget);
    RET;

next:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x0);
    LD_A(BATTLEANIMFRAMESET_22);
    CALL(aReinitBattleAnimFrameset);

two:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x98);
    IF_NC goto okay;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_H_hl;
    LD_L_A;
    LD_DE(0x60);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_D;

okay:

    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    RET_C;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf0);
    LD_E_A;
    LD_D(0xff);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_H_hl;
    LD_L_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hl_D;
    RET;
}

void BattleAnimFunction_Surf(void) {
    SET_PC(aBattleAnimFunction_Surf);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(LOW(rSCY));
    LDH_addr_A(hLCDCPointer);
    LD_A(0x58);
    LDH_addr_A(hLYOverrideStart);
    LD_A(0x5e);
    LDH_addr_A(hLYOverrideEnd);
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A_E;
    IF_NC goto move;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    XOR_A_A;
    LDH_addr_A(hLYOverrideStart);
    RET;

move:

    DEC_A;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x10);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    ADD_A_hl;
    SUB_A(0x10);
    RET_C;
    LDH_addr_A(hLYOverrideStart);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    INC_A;
    AND_A(0x7);
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    INC_hl;

two:

    RET;

three:

    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x70);
    IF_C goto move_down;
    XOR_A_A;
    LDH_addr_A(hLCDCPointer);
    LDH_addr_A(hLYOverrideStart);
    LDH_addr_A(hLYOverrideEnd);

four:

    CALL(aDeinitBattleAnimation);
    RET;

move_down:

    INC_A;
    INC_A;
    LD_hl_A;
    SUB_A(0x10);
    RET_C;
    LDH_addr_A(hLYOverrideStart);
    RET;
}

void BattleAnimFunction_Sing(void) {
    SET_PC(aBattleAnimFunction_Sing);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A(BATTLEANIMFRAMESET_24);
    ADD_A_hl;  // BATTLEANIMFRAMESET_25 BATTLEANIMFRAMESET_26
    CALL(aReinitBattleAnimFrameset);

one:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xb8);
    IF_C goto move;
    CALL(aDeinitBattleAnimation);
    RET;

move:

    LD_A(0x2);
    CALL(aBattleAnim_StepToTarget);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_hl;
    LD_D(0x8);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_WaterGun(void) {
    SET_PC(aBattleAnimFunction_WaterGun);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);

one:

    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x30);
    IF_C goto run_down;
    LD_A(0x2);
    CALL(aBattleAnim_StepToTarget);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_hl;
    LD_D(0x8);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

run_down:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(BATTLEANIMFRAMESET_28);
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl(0x0);
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hl(0x30);
    LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x1);
    LD_hl_A;

two:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x18);
    IF_NC goto splash;
    INC_hl;
    RET;

splash:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(BATTLEANIMFRAMESET_29);
    CALL(aReinitBattleAnimFrameset);

three:

    RET;
}

void BattleAnimFunction_Powder(void) {
    SET_PC(aBattleAnimFunction_Powder);
    //  Obj moves down and disappears at x coord $38
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x38);
    IF_C goto move;
    CALL(aDeinitBattleAnimation);
    RET;

move:

    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_L_hl;
    LD_H_A;
    LD_DE(0x80);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_D;
    // Shakes object back and forth 16 pixels
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0x10);
    LD_hl_A;
    RET;
}

void BattleAnimFunction_Recover(void) {
    SET_PC(aBattleAnimFunction_Recover);
    //  Obj moves in an ever shrinking circle. Obj Param defines initial position in the circle
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf0);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    SLA_A;
    SLA_A;
    SLA_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0x1);

one:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_NZ goto move;
    CALL(aDeinitBattleAnimation);
    RET;

move:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_D_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0x1);
    LD_hl_A;
    RET_Z;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    DEC_hl;
    RET;
}

void BattleAnimFunction_ThunderWave(void) {
    SET_PC(aBattleAnimFunction_ThunderWave);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

one:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(BATTLEANIMFRAMESET_35);
    CALL(aReinitBattleAnimFrameset);

zero:

two:

    RET;

three:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_Clamp_Encore(void) {
    SET_PC(aBattleAnimFunction_Clamp_Encore);
    //  Claps two objects together, twice. Also used by Encore
    //  Second object's frameset and position relative to first are both defined via this function
    //  Obj Param: Distance from center (masked with $7F). Bit 7 flips object horizontally by switching to a different frameset
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;
    if (REG_BC == 5) goto five;
    if (REG_BC == 6) goto six;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    BIT_hl(7);
    IF_NZ goto flipped;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x10);
    goto got_sine_start;

flipped:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x30);

got_sine_start:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x7f);
    LD_hl_A;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    BIT_A(7);
    IF_NZ goto load_no_inc;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    INC_A;  // BATTLEANIMFRAMESET_3B (Clamp Flipped)
    // ['?']  // BATTLEANIMFRAMESET_A1 (Hands Flipped)
    goto reinit;

load_no_inc:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;  // BATTLEANIMFRAMESET_3A (Clamp)
    // ['?']  // BATTLEANIMFRAMESET_A0 (Hands)

reinit:

    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    AND_A(0x1f);
    RET_NZ;

two:

three:

four:

five:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

six:

    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl(0x1);
    RET;
}

void BattleAnimFunction_Bite(void) {
    SET_PC(aBattleAnimFunction_Bite);
    //  Claps two objects together (vertically), twice
    //  Second object's frameset and position relative to first are both defined via this function
    //  Obj Param: Distance from center (masked with $7F). Bit 7 flips object vertically by switching to a different frameset
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;
    if (REG_BC == 5) goto five;
    if (REG_BC == 6) goto six;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    BIT_hl(7);
    IF_NZ goto flipped;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x10);
    goto got_sine_start;

flipped:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x30);

got_sine_start:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x7f);
    LD_hl_A;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    BIT_A(7);
    IF_NZ goto flipped2;
    LD_A(BATTLEANIMFRAMESET_3D);
    goto got_frameset;

flipped2:

    LD_A(BATTLEANIMFRAMESET_3C);

got_frameset:

    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    INC_hl;
    LD_A_hl;
    AND_A(0x1f);
    RET_NZ;

two:

three:

four:

five:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

six:

    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl(0x1);
    RET;
}

void BattleAnimFunction_SolarBeam(void) {
    SET_PC(aBattleAnimFunction_SolarBeam);
    //  Solar Beam charge up animation
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x28);
    INC_HL;
    LD_hl(0x0);

one:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_D_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto zero_radius;
    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(-0x80);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_D;
    RET;

zero_radius:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_Gust(void) {
    SET_PC(aBattleAnimFunction_Gust);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;
    if (REG_BC == 4) goto four;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_hl(0);

one:

three:

    CALL(aBattleAnimFunction_Gust_GustWobble);
    RET;

two:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x88);
    IF_C goto move;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

four:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xb8);
    IF_C goto move;
    CALL(aDeinitBattleAnimation);
    RET;

move:

    CALL(aBattleAnimFunction_Gust_GustWobble);
    // Move horizontally every frame
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    // Move in the vertically every other frame
    AND_A(0x1);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;
    RET;

GustWobble:

    // Circular movement where width is retrieved from a list, and height is 1/16 of that
    CALL(aBattleAnimFunction_Gust_GetGustRadius);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A(0x8);
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto start_wobble;
    CP_A(0xc2);
    IF_C goto finish_wobble;

start_wobble:

    DEC_A;
    LD_hl_A;
    AND_A(0x7);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    INC_hl;
    RET;

finish_wobble:

    XOR_A_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hli_A;
    LD_hl_A;
    RET;

GetGustRadius:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    LD_HL(mBattleAnimFunction_Gust_GustOffsets);
    ADD_HL_DE;
    LD_D_hl;
    RET;

GustOffsets:

    // db ['8', '6', '5', '4', '5', '6', '8', '12', '16'];

    return BattleAnimFunction_Absorb();
}

void BattleAnimFunction_Absorb(void) {
    SET_PC(aBattleAnimFunction_Absorb);
    //  Moves object from target to user and disappears when reaches x coord $30. Example: Absorb, Mega Drain, Leech Seed status
    //  Obj Param: Speed in the X axis
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x30);
    IF_NC goto move;
    CALL(aDeinitBattleAnimation);
    RET;

move:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    LD_E_A;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A_E;
    LD_hl_A;
    SRL_E;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;

loop:

    INC_hl;
    DEC_E;
    IF_NZ goto loop;
    RET;
}

void BattleAnimFunction_Wrap(void) {
    SET_PC(aBattleAnimFunction_Wrap);
    //  Plays out object Frameset. Use anim_incobj to move to next frameset
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

one:

    LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_A_hl;
    INC_A;  // BATTLEANIMFRAMESET_53
    // ['?']  // BATTLEANIMFRAMESET_55
    CALL(aReinitBattleAnimFrameset);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);  // Unused?
    ADD_HL_BC;
    LD_hl(0x8);

zero:

two:

    RET;
}

void BattleAnimFunction_LeechSeed(void) {
    SET_PC(aBattleAnimFunction_LeechSeed);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl(0x40);
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    IF_C goto sprout;
    CALL(aBattleAnim_StepThrownToTarget);
    RET;

sprout:

    LD_hl(0x40);
    LD_A(BATTLEANIMFRAMESET_57);
    CALL(aReinitBattleAnimFrameset);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

two:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto flutter;
    DEC_hl;
    RET;

flutter:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(BATTLEANIMFRAMESET_58);
    CALL(aReinitBattleAnimFrameset);

three:

    RET;
}

void BattleAnim_StepThrownToTarget(void) {
    SET_PC(aBattleAnim_StepThrownToTarget);
    //  Inches object towards the opponent's side in a parabola arc defined by the lower and upper nybble of Obj Param
    DEC_hl;
    LD_D(0x20);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_FIX_Y);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x2);
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_H_hl;
    LD_A_H;
    AND_A(0xf);
    SWAP_A;
    LD_L_A;
    LD_A_H;
    AND_A(0xf0);
    SWAP_A;
    LD_H_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_E;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x1);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;
    RET;
}

void BattleAnimFunction_Spikes(void) {
    SET_PC(aBattleAnimFunction_Spikes);
    //  Object is thrown at target. After $20 frames it stops and waits another $20 frames then disappear
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl(0x40);
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    IF_C goto wait;
    CALL(aBattleAnim_StepThrownToTarget);
    RET;

wait:

    CALL(aBattleAnim_IncAnonJumptableIndex);

two:

    RET;
}

void BattleAnimFunction_RazorWind(void) {
    SET_PC(aBattleAnimFunction_RazorWind);
    CALL(aBattleAnimFunction_MoveInCircle);
    // Causes object to skip ahead the circular motion every frame
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0xf);
    LD_hl_A;
    RET;
}

void BattleAnimFunction_Kick(void) {
    SET_PC(aBattleAnimFunction_Kick);
    //  Uses anim_setobj for different kick types
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;  // Jump Kick, Hi Jump Kick
    // dw ['.three'];  // Rolling Kick
    // dw ['.four'];  // Rolling Kick (continued)

zero:

    RET;

one:
    //
    //  Unused?
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x30);
    IF_C goto move_down;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl(0x0);
    RET;

move_down:

    ADD_A(0x4);
    LD_hl_A;
    RET;

two:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x98);
    RET_NC;
    INC_hl;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
    ADD_HL_BC;
    SET_hl(0);
    LD_HL(BATTLEANIMSTRUCT_FIX_Y);
    ADD_HL_BC;
    LD_hl(0x90);
    LD_HL(BATTLEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_hl(0x0);
    LD_HL(BATTLEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl(0x2);
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;
    RET;

three:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x2c);
    LD_HL(BATTLEANIMSTRUCT_FRAME);
    ADD_HL_BC;
    LD_hl(0x0);
    LD_HL(BATTLEANIMSTRUCT_DURATION);
    ADD_HL_BC;
    LD_hl(0x80);

four:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x98);
    RET_NC;
    INC_hl;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_D(0x8);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_Egg(void) {
    SET_PC(aBattleAnimFunction_Egg);
    //  Used by Egg Bomb and Softboiled
    //  Obj Param: Defines jumptable starting index
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;  // Egg Bomb start
    // dw ['.two'];
    // dw ['.three'];
    // dw ['.four'];  // ret
    // dw ['.five'];
    // dw ['.six'];  // Softboiled obj 1 start
    // dw ['.seven'];
    // dw ['.eight'];
    // dw ['.nine'];
    // dw ['.ten'];  // ret
    // dw ['.eleven'];  // Softboiled obj 2 start
    // dw ['.twelve'];
    // dw ['.thirteen'];  // ret

zero:

    // Object starts here then jumps to the jumptable index defined by the Obj Param
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x28);
    INC_HL;  // BATTLEANIMSTRUCT_VAR2
    LD_hl(0x10);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    RET;

one:

    // Initial Egg Bomb arc movement to x coord $40
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x40);
    IF_NC goto egg_bomb_vertical_wave;
    INC_hl;

egg_bomb_vertical_wave:

    CALL(aBattleAnimFunction_Egg_EggVerticalWaveMotion);
    RET;

six:

    // Initial Softboiled arc movement to x coord $4b
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x4b);
    IF_NC goto softboiled_vertical_wave;
    INC_hl;

softboiled_vertical_wave:

    CALL(aBattleAnimFunction_Egg_EggVerticalWaveMotion);
    RET;

two:

    // Compares the egg's x coord to determine whether to move, wait or end animation
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x88);
    IF_NC goto egg_bomb_done;
    AND_A(0xf);
    IF_NZ goto egg_bomb_step;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl(0x10);
    CALL(aBattleAnim_IncAnonJumptableIndex);  // jumps to three
    RET;

egg_bomb_done:

    // Increases jumptable index twice to four
    CALL(aBattleAnim_IncAnonJumptableIndex);
    INC_hl;
    RET;

three:

    // Waits in place
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto done_waiting;
    DEC_hl;
    RET;

done_waiting:

    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    DEC_hl;

egg_bomb_step:

    // Moves towards the target
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(-0x80);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_E;
    RET;

five:

    // Clears Egg Bomb object via anim_incobj
    CALL(aDeinitBattleAnimation);
    RET;

seven:

    // Switches Softboiled frameset to egg wobbling
    LD_A(BATTLEANIMFRAMESET_4E);  // Egg wobbling
    CALL(aReinitBattleAnimFrameset);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

eight:

    // Softboiled object waves slightly side to side
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    INC_hl;
    LD_D(0x2);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

nine:

    // First Softboiled ANIM_OBJ_EGG turns into the bottom half frameset
    LD_A(BATTLEANIMFRAMESET_50);  // Cracked egg bottom
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl(0x4);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

eleven:

    // Second Softboiled ANIM_OBJ_EGG
    LD_A(BATTLEANIMFRAMESET_4F);  // Cracked egg top
    CALL(aReinitBattleAnimFrameset);
    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x40);
    RET;

twelve:

    // Top half of egg moves upward for $30 frames
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x20);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x30);
    IF_C goto done_top_shell;
    DEC_hl;
    RET;

done_top_shell:

    CALL(aBattleAnim_IncAnonJumptableIndex);

four:

ten:

thirteen:

    RET;

EggVerticalWaveMotion:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;  // BATTLEANIMSTRUCT_VAR2
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    AND_A(0x3f);  // cp 64
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x20);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A(0x8);
    LD_hl_A;
    RET_NZ;
    XOR_A_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hli_A;
    LD_hl_A;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;
}

void BattleAnimFunction_MoveUp(void) {
    SET_PC(aBattleAnimFunction_MoveUp);
    //  Moves object up for 41 frames
    //  Obj Param: Movement speed
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto move;
    CP_A(0xd8);
    IF_NC goto move;
    CALL(aDeinitBattleAnimation);
    RET;

move:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A_D;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_Sound(void) {
    SET_PC(aBattleAnimFunction_Sound);
    //  Moves object back and forth in one of three angles using a sine behavior and disappear after 8 frames. Used in Growl, Snore and Kinesis
    //  Obj Param: Used to define object angle. How much to increase from base frameset, which is hardcoded as BATTLEANIMFRAMESET_59
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_Z goto got_turn;
    // enemy
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0xff);
    ADD_A(0x3);
    LD_hl_A;

got_turn:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x8);  // duration
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A(BATTLEANIMFRAMESET_59);
    ADD_A_hl;  // BATTLEANIMFRAMESET_5A BATTLEANIMFRAMESET_5B
    CALL(aReinitBattleAnimFrameset);
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto done_anim;
    DEC_hl;
    CALL(aBattleAnimFunction_Sound_SoundWaveMotion);
    RET;

done_anim:

    CALL(aDeinitBattleAnimation);
    RET;

SoundWaveMotion:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    INC_hl;
    LD_D(0x10);
    CALL(aBattleAnim_Sine);
    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto negative;
    DEC_A;
    RET_Z;
    // Obj Param 2
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_D;
    RET;

negative:

    // Obj Param 0
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_D;
    XOR_A(0xff);
    INC_A;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_ConfuseRay(void) {
    SET_PC(aBattleAnimFunction_ConfuseRay);
    //  Creates the Confuse Ray object and moves it across the screen until x coord $80
    //  Moves horizontally every frame and vertically every 3 frames
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3f);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x80);
    RLCA;
    LD_hl_A;
    ADD_A(BATTLEANIMFRAMESET_5D);  // BATTLEANIMFRAMESET_5E
    CALL(aReinitBattleAnimFrameset);
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    SWAP_A;
    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x80);
    RET_NC;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3);
    IF_NZ goto skip_vertical_movement;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;

skip_vertical_movement:

    AND_A(0x1);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void BattleAnimFunction_Dizzy(void) {
    SET_PC(aBattleAnimFunction_Dizzy);
    //  Moves object in a circle where the height is 1/4 the width, with the next frameset from base whether moving left or right. Also used for Nightmare
    //  Obj Param: Defines starting position in the circle (masked with $80). Bit 7 flips it at the start
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x80);
    RLCA;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    ADD_A_hl;  // BATTLEANIMFRAMESET_61 BATTLEANIMFRAMESET_62
    // ['?']  // BATTLEANIMFRAMESET_9C BATTLEANIMFRAMESET_9D
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x7f);
    LD_hl_A;

one:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x10);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    AND_A(0x3f);
    IF_Z goto not_flipped;
    AND_A(0x1f);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_A;  // BATTLEANIMFRAMESET_62
    // ['?']  // BATTLEANIMFRAMESET_9D
    goto got_frameset;

not_flipped:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;  // BATTLEANIMFRAMESET_61
    // ['?']  // BATTLEANIMFRAMESET_9C

got_frameset:

    CALL(aReinitBattleAnimFrameset);
    RET;
}

void BattleAnimFunction_Amnesia(void) {
    SET_PC(aBattleAnimFunction_Amnesia);
    //  Creates 3 objects based on Obj Param
    //  Obj Param: How much to increase from base frameset, which is hardcoded as BATTLEANIMFRAMESET_63
    //  anim_incobj is used to DeInit object (used by Present)
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(BATTLEANIMFRAMESET_63);  // BATTLEANIMFRAMESET_64 BATTLEANIMFRAMESET_65
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_E_hl;
    LD_D(0);
    LD_HL(mBattleAnimFunction_Amnesia_AmnesiaOffsets);
    ADD_HL_DE;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;

one:

    RET;

two:

    // anim_incobj forces obj to deinit
    CALL(aDeinitBattleAnimation);
    RET;

AmnesiaOffsets:
    //
    //  Hardcoded Y Offsets for each Obj Param
    // db ['0xec', '0xf8', '0x00'];

    return BattleAnimFunction_FloatUp();
}

void BattleAnimFunction_FloatUp(void) {
    SET_PC(aBattleAnimFunction_FloatUp);
    //  Object moves horizontally in a sine wave, while also moving up. Also used by Charm and the Nightmare status
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    INC_hl;
    LD_D(0x4);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL((0xFF << 8) | 0xa0);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_E;
    RET;
}

void BattleAnimFunction_Dig(void) {
    SET_PC(aBattleAnimFunction_Dig);
    //  Object moves up then down with a wave motion, while also moving away from the user 1 pixel per frame
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_hl;
    DEC_hl;
    LD_D(0x10);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void BattleAnimFunction_String(void) {
    SET_PC(aBattleAnimFunction_String);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_NZ goto not_param_zero;
    // Obj Param 0 flips when used by enemy
    LD_HL(BATTLEANIMSTRUCT_OAMFLAGS);
    ADD_HL_BC;
    SET_hl(OAM_Y_FLIP);

not_param_zero:

    ADD_A(BATTLEANIMFRAMESET_6A);  // BATTLEANIMFRAMESET_6B BATTLEANIMFRAMESET_6C
    CALL(aReinitBattleAnimFrameset);

one:

    RET;
}

void BattleAnimFunction_Paralyzed(void) {
    SET_PC(aBattleAnimFunction_Paralyzed);
    //  Also used by Disable
    //  Obj Param: When bit 7 is set, frameset is replaced with flipped version. This bit is discarded and object then moves back and forth between position in lower nybble and upper nybble of Param every other frame
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x0);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_E_hl;
    LD_A_E;
    AND_A(0x70);
    SWAP_A;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_A_E;
    AND_A(0x80);
    IF_NZ goto right;
    LD_A_E;
    AND_A(0xf);
    LD_hl_A;
    RET;

right:

    LD_A_E;
    AND_A(0xf);
    XOR_A(0xff);
    INC_A;
    LD_hl_A;
    LD_A(BATTLEANIMFRAMESET_6E);
    CALL(aReinitBattleAnimFrameset);
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto var1_zero;
    DEC_hl;
    RET;

var1_zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0xff);
    INC_A;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_SpiralDescent(void) {
    SET_PC(aBattleAnimFunction_SpiralDescent);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x18);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    AND_A(0x7);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x28);
    IF_NC goto delete;
    INC_hl;
    RET;

    delete :

        CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_PetalDance(void) {
    SET_PC(aBattleAnimFunction_PetalDance);
    //  Object moves downwards in a spiral around the user. Object disappears at y coord $28
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x18);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    AND_A(0x3);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x28);
    IF_NC goto end;
    INC_hl;
    RET;

end:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_PoisonGas(void) {
    SET_PC(aBattleAnimFunction_PoisonGas);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    // dw ['BattleAnimFunction_SpiralDescent'];

zero:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x84);
    IF_NC goto next;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_D(0x18);
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x1);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    DEC_hl;
    RET;

next:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;
}

void BattleAnimFunction_SmokeFlameWheel(void) {
    SET_PC(aBattleAnimFunction_SmokeFlameWheel);
    //  Object spins around target while also moving upward until it disappears at x coord $e8
    //  Obj Param: Defines where the object starts in the circle
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x18);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    INC_hl;
    INC_hl;
    LD_A_hl;
    AND_A(0x7);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xe8);
    IF_Z goto done;
    DEC_hl;
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_SacredFire(void) {
    SET_PC(aBattleAnimFunction_SacredFire);
    //  Moves object in a circle where the height is 1/8 the width, while also moving upward 2 pixels per frame for 24 frames after which it disappears
    //  Obj Param: Is used internally only
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x18);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    INC_hl;
    INC_hl;
    LD_A_hl;
    AND_A(0x3);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xd0);
    IF_Z goto done;
    DEC_hl;
    DEC_hl;
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_PresentSmokescreen(void) {
    SET_PC(aBattleAnimFunction_PresentSmokescreen);
    //  Object bounces from user to target and stops at x coord $6c. Uses anim_incobj to clear object
    //  Obj Param: Defined but not used
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x34);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl(0x10);

one:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x6c);
    IF_C goto do_move;
    RET;

do_move:

    LD_A(0x2);
    CALL(aBattleAnim_StepToTarget);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    BIT_A(7);
    IF_NZ goto negative;
    XOR_A(0xff);
    INC_A;

negative:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A(0x4);
    LD_hl_A;
    AND_A(0x1f);
    CP_A(0x20);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    SRL_hl;
    RET;

two:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_Horn(void) {
    SET_PC(aBattleAnimFunction_Horn);
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x58);
    RET_NC;
    LD_A(0x2);
    CALL(aBattleAnim_StepToTarget);
    RET;

two:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    IF_C goto three;
    CALL(aDeinitBattleAnimation);
    RET;

three:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x8);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    SRA_A;
    XOR_A(0xff);
    INC_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x8);
    LD_hl_A;
    RET;
}

void BattleAnimFunction_Needle(void) {
    SET_PC(aBattleAnimFunction_Needle);
    //  Moves object towards target, either in a straight line or arc. Stops at x coord $84
    //  Obj Param: Upper nybble defines the index of the jumptable. Lower nybble defines the speed.
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf0);
    SWAP_A;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    RET;

two:

    // Pin Missile needle (arc)
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x10);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    BIT_A(7);
    IF_Z goto negative;
    LD_hl_A;

negative:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A(0x4);
    LD_hl_A;

one:

    // Normal needle (line)
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x84);
    IF_C goto move_to_target;
    CALL(aDeinitBattleAnimation);
    RET;

move_to_target:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    CALL(aBattleAnim_StepToTarget);
    RET;
}

void BattleAnimFunction_ThiefPayday(void) {
    SET_PC(aBattleAnimFunction_ThiefPayday);
    //  Object drops off target and bounces once on the floor
    //  Obj Param: Defines every how many frames the object moves horizontally
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x28);
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    SUB_A(0x28);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_A;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    AND_A_hl;
    IF_NZ goto var_doesnt_equal_param;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    DEC_hl;

var_doesnt_equal_param:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    AND_A(0x3f);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x20);
    INC_HL;
    SRL_hl;
    RET;
}

void BattleAnimFunction_AbsorbCircle(void) {
    SET_PC(aBattleAnimFunction_AbsorbCircle);
    //  A circle of objects that starts at the target and moves to the user. It expands until x coord $5a and then shrinks. Once radius reaches 0, the object disappears. Also used by Mimic and Conversion2
    //  Obj Param: Defines the position in the circle the object starts at
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_D_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    INC_hl;
    LD_A_hl;
    AND_A(0x1);
    IF_NZ goto dont_move_x;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    DEC_hl;

dont_move_x:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3);
    IF_NZ goto dont_move_y;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    INC_hl;

dont_move_y:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    CP_A(0x5a);
    IF_NC goto increase_radius;
    LD_A_hl;
    AND_A_A;
    IF_Z goto end;
    DEC_hl;  // decreases radius
    RET;

increase_radius:

    INC_hl;
    RET;

end:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_Conversion(void) {
    SET_PC(aBattleAnimFunction_Conversion);
    //  A rotating circle of objects centered at a position. It expands for $40 frames and then shrinks. Once radius reaches 0, the object disappears.
    //  Obj Param: Defines starting point in the circle
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_D_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    CP_A(0x40);
    IF_NC goto shrink;
    INC_hl;
    RET;

shrink:

    LD_A_hl;
    DEC_hl;
    AND_A_A;
    RET_NZ;
    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_Bonemerang(void) {
    SET_PC(aBattleAnimFunction_Bonemerang);
    //  Boomerang-like movement from user to target
    //  Obj Param: Defines position to start at in the circle
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_hl_A;

one:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x30);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x8);
    LD_D(0x30);
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void BattleAnimFunction_Shiny(void) {
    SET_PC(aBattleAnimFunction_Shiny);
    //  Puts object in a circle formation of radius $10. Also used by Flash and Light Screen
    //  Obj Param: Defines where the object starts in the circle
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x10);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x10);
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);  // unused?
    ADD_HL_BC;
    LD_hl(0xf);

one:

    RET;
}

void BattleAnimFunction_SkyAttack(void) {
    SET_PC(aBattleAnimFunction_SkyAttack);
    //  Uses anim_incobj to move to next step
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LDH_A_addr(hBattleTurn);
    AND_A_A;
    IF_NZ goto enemy_turn;
    LD_A(0xf0);
    goto got_var1;

enemy_turn:

    LD_A(0xcc);

got_var1:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_A;
    RET;

one:

    CALL(aBattleAnimFunction_SkyAttack_SkyAttack_CyclePalette);
    RET;

two:

    //  Moves towards target and stops at x coord $84
    CALL(aBattleAnimFunction_SkyAttack_SkyAttack_CyclePalette);
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x84);
    RET_NC;
    LD_A(0x4);
    CALL(aBattleAnim_StepToTarget);
    RET;

three:

    //  Moves towards target and disappears at x coord $d0
    CALL(aBattleAnimFunction_SkyAttack_SkyAttack_CyclePalette);
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xd0);
    IF_NC goto done;
    LD_A(0x4);
    CALL(aBattleAnim_StepToTarget);
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;

SkyAttack_CyclePalette:

    //  Cycles wOBP0 pallete
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x7);
    INC_hl;
    SRL_A;
    LD_E_A;
    LD_D(0);
    LDH_A_addr(hSGB);
    AND_A_A;
    IF_NZ goto sgb;
    LD_HL(mBattleAnimFunction_SkyAttack_GBCPals);
    goto got_pals;

sgb:

    LD_HL(mBattleAnimFunction_SkyAttack_SGBPals);

got_pals:

    ADD_HL_DE;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    AND_A_hl;
    LD_addr_A(wOBP0);
    RET;

GBCPals:

    // db ['0xff', '0xaa', '0x55', '0xaa'];

SGBPals:

    // db ['0xff', '0xff', '0x00', '0x00'];

    return BattleAnimFunction_GrowthSwordsDance();
}

void BattleAnimFunction_GrowthSwordsDance(void) {
    SET_PC(aBattleAnimFunction_GrowthSwordsDance);
    //  Moves object in a circle where the height is 1/8 the width, while also moving upward 2 pixels per frame
    //  Obj Param: Defines where the object starts in the circle
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x18);
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    ADD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_D(0x18);
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    DEC_hl;
    DEC_hl;
    RET;
}

void BattleAnimFunction_StrengthSeismicToss(void) {
    SET_PC(aBattleAnimFunction_StrengthSeismicToss);
    //  Moves object up for $e0 frames, then shakes it vertically and throws it at the target. Uses anim_incobj to move to final phase
    //  Obj Param: Defined but not used
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xe0);
    IF_NZ goto move_up;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x2);
    RET;

move_up:

    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(-0x80);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_E;
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto switch_position;
    DEC_hl;
    RET;

switch_position:

    LD_hl(0x4);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    XOR_A(0xff);
    INC_A;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    RET;

two:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x84);
    IF_NC goto done;
    LD_A(0x4);
    CALL(aBattleAnim_StepToTarget);
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_SpeedLine(void) {
    SET_PC(aBattleAnimFunction_SpeedLine);
    //  Used in moves where the user disappears for a speed-based attack such as Quick Attack, Mach Punch and Extremespeed
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x7f);
    ADD_A(BATTLEANIMFRAMESET_81);  // BATTLEANIMFRAMESET_82 BATTLEANIMFRAMESET_83
    CALL(aReinitBattleAnimFrameset);

one:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    BIT_hl(7);
    IF_NZ goto inverted;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    INC_hl;
    RET;

inverted:

    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    DEC_hl;
    RET;
}

void BattleAnimFunction_Sludge(void) {
    SET_PC(aBattleAnimFunction_Sludge);
    //  Object moves upward for $c frames and switches to FRAMESET_20
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0xc);
    RET;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    DEC_hl;
    RET;

done:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_A(BATTLEANIMFRAMESET_20);
    CALL(aReinitBattleAnimFrameset);

two:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    DEC_hl;
    RET;
}

void BattleAnimFunction_MetronomeHand(void) {
    SET_PC(aBattleAnimFunction_MetronomeHand);
    //  Fast circular motion with an x radius of $8 and y radius of $2
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    INC_hl;
    PUSH_AF;
    LD_D(0x2);
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_AF;
    LD_D(0x8);
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_MetronomeSparkleSketch(void) {
    SET_PC(aBattleAnimFunction_MetronomeSparkleSketch);
    //  Sideways wave motion while also moving downward until it disappears at y coord $20
    //  Obj Param: Is used internally only
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    IF_C goto do_move;
    CALL(aDeinitBattleAnimation);
    RET;

do_move:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x8);
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x2);
    LD_hl_A;
    AND_A(0x7);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void BattleAnimFunction_Agility(void) {
    SET_PC(aBattleAnimFunction_Agility);
    //  Object moves sideways at a speed determined by Obj Param. Can use anim_incobj to make it disappear
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    RET;

one:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_SafeguardProtect(void) {
    SET_PC(aBattleAnimFunction_SafeguardProtect);
    //  Moves object in a circle where the width is 1/2 the height
    //  Obj Param: Defines starting point in circle
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_D(0x18);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    SRA_A;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    RET;
}

void BattleAnimFunction_LockOnMindReader(void) {
    SET_PC(aBattleAnimFunction_LockOnMindReader);
    //  Moves objects towards a center position
    //  Obj Param: Used to define object angle from 0 to 3. Lower nybble defines how much to increase from base frameset while upper nybble defines angle of movement. The object moves for $28 frames, then waits for $10 frames and disappears
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x28);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf);
    LD_HL(BATTLEANIMSTRUCT_FRAMESET_ID);
    ADD_HL_BC;
    ADD_A_hl;  // BATTLEANIMFRAMESET_8F BATTLEANIMFRAMESET_90 BATTLEANIMFRAMESET_91
    // ['?']  // BATTLEANIMFRAMESET_93 BATTLEANIMFRAMESET_94 BATTLEANIMFRAMESET_95
    CALL(aReinitBattleAnimFrameset);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0xf0);
    OR_A(0x8);
    LD_hl_A;

one:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    DEC_hl;
    ADD_A(0x8);
    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

done:

    LD_hl(0x10);
    CALL(aBattleAnim_IncAnonJumptableIndex);

two:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    DEC_hl;
    AND_A_A;
    RET_NZ;
    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_HealBellNotes(void) {
    SET_PC(aBattleAnimFunction_HealBellNotes);
    //  Object moves horizontally in a sine wave, while also moving left every other frame and downwards for $38 frames after which it disappears
    //  Obj Param: Defines a frameset offset from FRAMESET_24
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

zero:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A(BATTLEANIMFRAMESET_24);
    ADD_A_hl;  // BATTLEANIMFRAMESET_25 BATTLEANIMFRAMESET_26
    CALL(aReinitBattleAnimFrameset);

one:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x38);
    IF_NC goto done;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    LD_D(0x18);
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x1);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    DEC_hl;
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_BatonPass(void) {
    SET_PC(aBattleAnimFunction_BatonPass);
    //  Object falls vertially and bounces on the ground
    //  Obj Param: Defines speed and duration
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    RET_Z;
    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    CALL(aBattleAnim_Sine);
    BIT_A(7);
    IF_NZ goto negative;
    XOR_A(0xff);
    INC_A;

negative:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x1f);
    RET_NZ;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    SRL_hl;
    RET;
}

void BattleAnimFunction_EncoreBellyDrum(void) {
    SET_PC(aBattleAnimFunction_EncoreBellyDrum);
    //  Object moves at an arc for 8 frames and disappears
    //  Obj Param: Defines startging position in the arc
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x10);
    IF_NC goto done;
    INC_hl;
    INC_hl;
    LD_D_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_SwaggerMorningSun(void) {
    SET_PC(aBattleAnimFunction_SwaggerMorningSun);
    //  Moves object at an angle
    //  Obj Param: Lower 6 bits define angle of movement and upper 2 bits define speed
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_D_hl;
    LD_A_E;
    AND_A(0xc0);
    RLCA;
    RLCA;
    ADD_A_hl;
    LD_hl_A;
    LD_A_E;
    AND_A(0x3f);
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_HiddenPower(void) {
    SET_PC(aBattleAnimFunction_HiddenPower);
    //  Moves object in a ring around position. Uses anim_incobj to move to second phase,  where it expands the radius 8 pixels at a time for 13 frames and then disappears
    //  Obj Param: Defines starting position in circle
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;

zero:

    LD_D(0x18);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    goto step_circle;

one:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl(0x18);

two:

    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x80);
    IF_NC goto done;
    LD_D_A;
    ADD_A(0x8);
    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    goto step_circle;

done:

    CALL(aDeinitBattleAnimation);
    RET;

step_circle:

    CALL(aBattleAnim_StepCircle);
    RET;
}

void BattleAnimFunction_Curse(void) {
    SET_PC(aBattleAnimFunction_Curse);
    //  Object moves down and to the left 2 pixels at a time until it reaches x coord $30 and disappears
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;

one:

    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x30);
    IF_C goto done;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    DEC_hl;
    DEC_hl;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    INC_hl;
    INC_hl;
    RET;

done:

    CALL(aDeinitBattleAnimation);

zero:

    RET;
}

void BattleAnimFunction_PerishSong(void) {
    SET_PC(aBattleAnimFunction_PerishSong);
    //  Moves object in a large circle with a x radius of $50 and a y radius 1/4 or that, while also moving downwards
    //  Obj Param: Defines starting position in the circle
    LD_D(0x50);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    INC_hl;
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    ADD_A_hl;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void BattleAnimFunction_RapidSpin(void) {
    SET_PC(aBattleAnimFunction_RapidSpin);
    //  Object moves upwards 4 pixels per frame until it disappears at y coord $d0
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xd0);
    IF_Z goto done;
    DEC_hl;
    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnimFunction_BetaPursuit(void) {
    SET_PC(aBattleAnimFunction_BetaPursuit);
    //  Working but unused animation
    //  Object moves either down or up 4 pixels per frame, depending on Obj Param. Object disappears after 23 frames when going down, or at y coord $d8 when going up
    //  Obj Param: 0 moves downwards, 1 moves upwards
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_NZ goto move_up;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl(0xec);

one:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x4);
    IF_Z goto three;
    INC_hl;
    INC_hl;
    INC_hl;
    INC_hl;
    RET;

three:

    CALL(aDeinitBattleAnimation);
    RET;

move_up:

    CALL(aBattleAnim_IncAnonJumptableIndex);
    CALL(aBattleAnim_IncAnonJumptableIndex);

two:

    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0xd8);
    RET_Z;
    DEC_hl;
    DEC_hl;
    DEC_hl;
    DEC_hl;
    RET;
}

void BattleAnimFunction_RainSandstorm(void) {
    SET_PC(aBattleAnimFunction_RainSandstorm);
    //  Object moves down 4 pixels at a time and right a variable distance
    //  Obj Param: Defines variation in the movement
    //             $0: 2 pixels horizontal movement
    //             $1: 8 pixels horizontal movement
    //             $2: 4 pixels horizontal movement
    // CALL(aBattleAnim_AnonJumptable);

anon_dw:

    if (REG_BC == 0) goto zero;
    if (REG_BC == 1) goto one;
    if (REG_BC == 2) goto two;
    if (REG_BC == 3) goto three;

zero:

    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_hl_A;
    CALL(aBattleAnim_IncAnonJumptableIndex);
    RET;

one:
    //
    //  Obj Param 0
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x4);
    CP_A(0x70);
    IF_C goto dont_reset_y_offset_one;
    XOR_A_A;

dont_reset_y_offset_one:

    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    INC_hl;
    INC_hl;
    RET;

two:
    //
    //  Obj Param 1
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x4);
    CP_A(0x70);
    IF_C goto dont_reset_y_offset_two;
    XOR_A_A;

dont_reset_y_offset_two:

    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x8);
    LD_hl_A;
    RET;

three:
    //
    //  Obj Param 2
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x4);
    CP_A(0x70);
    IF_C goto dont_reset_y_offset_three;
    XOR_A_A;

dont_reset_y_offset_three:

    LD_hl_A;
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_A_hl;
    ADD_A(0x4);
    LD_hl_A;
    RET;
}

void BattleAnimFunction_AnimObjB0(void) {
    SET_PC(aBattleAnimFunction_AnimObjB0);
    //  //  unused
    //  Used by object ANIM_OBJ_B0, with itself is not used in any animation
    //  Obj Param: Lower nybble is added to VAR1 while upper nybble is added to XCOORD
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_D_hl;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_E_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    LD_L_A;
    AND_A(0xf0);
    LD_H_A;
    SWAP_A;
    OR_A_H;
    LD_H_A;
    LD_A_L;
    AND_A(0xf);
    SWAP_A;
    LD_L_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hl_D;
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_hl_E;
    RET;
}

void BattleAnimFunction_PsychUp(void) {
    SET_PC(aBattleAnimFunction_PsychUp);
    //  Object moves in a circle
    //  Obj Param: Defines starting position in the circle
    LD_D(0x18);
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    CALL(aBattleAnim_StepCircle);
    RET;
}

void BattleAnimFunction_Cotton(void) {
    SET_PC(aBattleAnimFunction_Cotton);
    //  Object moves in a circle slowly
    //  Obj Param: Defines starting position in the circle
    LD_D(0x18);
    LD_HL(BATTLEANIMSTRUCT_VAR2);
    ADD_HL_BC;
    LD_A_hl;
    INC_hl;
    SRL_A;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    ADD_A_hl;
    CALL(aBattleAnim_StepCircle);
    RET;
}

void BattleAnimFunction_AncientPower(void) {
    SET_PC(aBattleAnimFunction_AncientPower);
    //  Object moves up and down in an arc for $20 frames and then disappear
    //  Obj Param: Defines range of arc motion
    LD_HL(BATTLEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x20);
    IF_NC goto done;
    INC_hl;
    LD_HL(BATTLEANIMSTRUCT_PARAM);
    ADD_HL_BC;
    LD_D_hl;
    CALL(aBattleAnim_Sine);
    XOR_A(0xff);
    INC_A;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

done:

    CALL(aDeinitBattleAnimation);
    RET;
}

void BattleAnim_StepCircle(void) {
    SET_PC(aBattleAnim_StepCircle);
    //  Inches object in a circular movement where its height is 1/4 the width
    PUSH_AF;
    PUSH_DE;
    CALL(aBattleAnim_Sine);
    SRA_A;
    SRA_A;
    LD_HL(BATTLEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    POP_DE;
    POP_AF;
    CALL(aBattleAnim_Cosine);
    LD_HL(BATTLEANIMSTRUCT_XOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;
}

void BattleAnim_StepToTarget(void) {
    SET_PC(aBattleAnim_StepToTarget);
    //  Inches object towards the opponent's side, moving half as much in the Y axis as it did in the X axis. Uses lower nybble of A
    AND_A(0xf);
    LD_E_A;
    LD_HL(BATTLEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    ADD_A_hl;
    LD_hl_A;
    SRL_E;
    LD_HL(BATTLEANIMSTRUCT_YCOORD);
    ADD_HL_BC;

loop:

    DEC_hl;
    DEC_E;
    IF_NZ goto loop;
    RET;
}

void BattleAnim_AnonJumptable(void) {
    SET_PC(aBattleAnim_AnonJumptable);
    POP_DE;
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    LD_L_hl;
    LD_H(0x0);
    ADD_HL_HL;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;
}

void BattleAnim_IncAnonJumptableIndex(void) {
    SET_PC(aBattleAnim_IncAnonJumptableIndex);
    LD_HL(BATTLEANIMSTRUCT_JUMPTABLE_INDEX);
    ADD_HL_BC;
    INC_hl;
    RET;
}

void BattleAnim_Cosine(void) {
    SET_PC(aBattleAnim_Cosine);
    //  a = d * cos(a * pi/32)
    ADD_A(0b010000);  // cos(x) = sin(x + pi/2)
                      // fallthrough
    return BattleAnim_Sine();
}

void BattleAnim_Sine(void) {
    SET_PC(aBattleAnim_Sine);
    //  a = d * sin(a * pi/32)
    // calc_sine_wave ['BattleAnimSineWave']

    return BattleAnim_Sine_e();
}

void BattleAnim_Sine_e(void) {
    SET_PC(aBattleAnim_Sine_e);
    LD_A_E;
    CALL(aBattleAnim_Sine);
    LD_E_A;
    RET;
}

void BattleAnim_Cosine_e(void) {
    SET_PC(aBattleAnim_Cosine_e);
    LD_A_E;
    CALL(aBattleAnim_Cosine);
    LD_E_A;
    RET;
}

void BattleAnim_AbsSinePrecise(void) {
    SET_PC(aBattleAnim_AbsSinePrecise);
    //  //  unreferenced
    LD_A_E;
    CALL(aBattleAnim_Sine);
    LD_E_L;
    LD_D_H;
    RET;
}

void BattleAnim_AbsCosinePrecise(void) {
    SET_PC(aBattleAnim_AbsCosinePrecise);
    //  //  unreferenced
    LD_A_E;
    CALL(aBattleAnim_Cosine);
    LD_E_L;
    LD_D_H;
    RET;
}

void BattleAnimSineWave(void) {
    SET_PC(aBattleAnimSineWave);
    // sine_table ['32']
}
