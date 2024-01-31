#include "../../constants.h"
#include "player_step.h"
#include "../../home/map.h"

void v_HandlePlayerStep(void){
    // LD_A_addr(wPlayerStepFlags);
    // AND_A_A;
    // RET_Z ;
    if(wram->wPlayerStepFlags == 0)
        return;
    // BIT_A(PLAYERSTEP_START_F);
    // IF_NZ goto update_overworld_map;
    if(bit_test(wram->wPlayerStepFlags, PLAYERSTEP_START_F)) {
    // update_overworld_map:
        // LD_A(4);
        // LD_addr_A(wHandlePlayerStep);
        wram->wHandlePlayerStep = 4;
        // CALL(aUpdateOverworldMap);
        UpdateOverworldMap();
        // goto finish;
    }
    // BIT_A(PLAYERSTEP_STOP_F);
    // IF_NZ goto update_player_coords;
    else if(bit_test(wram->wPlayerStepFlags, PLAYERSTEP_STOP_F)) {
    // update_player_coords:
        // CALL(aUpdatePlayerCoords);
        UpdatePlayerCoords();
        // goto finish;
    }
    // BIT_A(PLAYERSTEP_CONTINUE_F);
    // IF_NZ goto finish;
    // RET;
    else if(!bit_test(wram->wPlayerStepFlags, PLAYERSTEP_CONTINUE_F))
        return;

// finish:
    // CALL(aHandlePlayerStep);
    HandlePlayerStep();
    // LD_A_addr(wPlayerStepVectorX);
    // LD_D_A;
    // LD_A_addr(wPlayerStepVectorY);
    // LD_E_A;
    // LD_A_addr(wPlayerBGMapOffsetX);
    // SUB_A_D;
    // LD_addr_A(wPlayerBGMapOffsetX);
    wram->wPlayerBGMapOffsetX -= wram->wPlayerStepVectorX;
    // LD_A_addr(wPlayerBGMapOffsetY);
    // SUB_A_E;
    // LD_addr_A(wPlayerBGMapOffsetY);
    wram->wPlayerBGMapOffsetY -= wram->wPlayerStepVectorY;
    // RET;
}

void ScrollScreen(void){
    // LD_A_addr(wPlayerStepVectorX);
    // LD_D_A;
    // LD_A_addr(wPlayerStepVectorY);
    // LD_E_A;
    // LDH_A_addr(hSCX);
    // ADD_A_D;
    // LDH_addr_A(hSCX);
    hram->hSCX += wram->wPlayerStepVectorX;
    // LDH_A_addr(hSCY);
    // ADD_A_E;
    // LDH_addr_A(hSCY);
    hram->hSCY += wram->wPlayerStepVectorY;
    // RET;
}

void HandlePlayerStep(void){
    // LD_HL(wHandlePlayerStep);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(wram->wHandlePlayerStep == 0)
        return;
    // DEC_hl;
    // LD_A_hl;
    uint8_t a = --wram->wHandlePlayerStep;
    // LD_HL(mHandlePlayerStep_Jumptable);
    // RST(aJumpTable);
    // RET;
    switch(a) {
    // Jumptable:
    case 0:
    //dw ['GetMovementPermissions'];
        GetMovementPermissions();
        return;
    case 1:
    //dw ['BufferScreen'];
        BufferScreen_Conv();
        return;
    case 2:
    //dw ['.mobile'];
    // mobile:
        // FARCALL(aStubbedTrainerRankings_StepCount);
        // RET;
        return;
    case 3:
    //dw ['.fail2'];
    // fail2:
        // RET;
        return;
//  The rest are never used.  Ever.
    default:
    //dw ['.fail1'];
    //dw ['.fail1'];
    //dw ['.fail1'];
    //dw ['.fail1'];
    //dw ['.fail1'];
    //dw ['.fail1'];
    //dw ['.fail1'];
    // fail1:
        // RET;
        return;
    }
}

void UpdatePlayerCoords(void){
    // LD_A_addr(wPlayerStepDirection);
    // AND_A_A;
    // IF_NZ goto check_step_down;
    if(wram->wPlayerStepDirection == DOWN) {
        // LD_HL(wYCoord);
        // INC_hl;
        wram->wYCoord++;
        // RET;
        return;
    }

// check_step_down:
    // CP_A(UP);
    // IF_NZ goto check_step_left;
    else if(wram->wPlayerStepDirection == UP) {
        // LD_HL(wYCoord);
        // DEC_hl;
        wram->wYCoord--;
        // RET;
        return;
    }

// check_step_left:
    // CP_A(LEFT);
    // IF_NZ goto check_step_right;
    else if(wram->wPlayerStepDirection == LEFT) {
        // LD_HL(wXCoord);
        // DEC_hl;
        --wram->wXCoord;
        // RET;
        return;
    }

// check_step_right:
    // CP_A(RIGHT);
    // RET_NZ ;
    else if(wram->wPlayerStepDirection == RIGHT) {
        // LD_HL(wXCoord);
        // INC_hl;
        ++wram->wXCoord;
        // RET;
        return;
    }
}

static void UpdateOverworldMap_ScrollMapDataDown(void) {
    // LD_HL(wOverworldMapAnchor);
    // LD_A_addr(wMapWidth);
    // ADD_A(3 * 2);  // surrounding tiles
    // ADD_A_hl;
    // LD_hli_A;
    // RET_NC ;
    // INC_hl;
    // RET;
    wram->wOverworldMapAnchor += wram->wMapWidth + 3 * 2;
    printf("anchor=%d\n", wram->wOverworldMapAnchor - wOverworldMapBlocks);
}

static void UpdateOverworldMap_ScrollOverworldMapDown(void) {
    // LD_A_addr(wBGMapAnchor);
    // ADD_A(2 * BG_MAP_WIDTH);
    // LD_addr_A(wBGMapAnchor);
    // IF_NC goto not_overflowed;
    // LD_A_addr(wBGMapAnchor + 1);
    // INC_A;
    // AND_A(0b11);
    // OR_A(HIGH(vBGMap0));
    // LD_addr_A(wBGMapAnchor + 1);
    wram->wBGMapAnchor += 2 * BG_MAP_WIDTH;
    wram->wBGMapAnchor = LOW(wram->wBGMapAnchor) | (((HIGH(wram->wBGMapAnchor) & 0b11) | HIGH(vBGMap0)) << 8);

// not_overflowed:
    // LD_HL(wMetatileStandingY);
    // INC_hl;
    // LD_A_hl;
    // CP_A(2);  // was 1
    // IF_NZ goto done_down;
    if(++wram->wMetatileStandingY == 2) {
        // LD_hl(0);
        wram->wMetatileStandingY = 0;
        // CALL(aUpdateOverworldMap_ScrollMapDataDown);
        UpdateOverworldMap_ScrollMapDataDown();
    }

// done_down:
    // RET;
    return;
}

static void UpdateOverworldMap_ScrollMapDataUp(void) {
    // LD_HL(wOverworldMapAnchor);
    // LD_A_addr(wMapWidth);
    // ADD_A(3 * 2);  // surrounding tiles
    // LD_B_A;
    // LD_A_hl;
    // SUB_A_B;
    // LD_hli_A;
    // RET_NC ;
    // DEC_hl;
    // RET;
    wram->wOverworldMapAnchor -= wram->wMapWidth + 3 * 2;
    printf("anchor=%d\n", wram->wOverworldMapAnchor - wOverworldMapBlocks);
}

static void UpdateOverworldMap_ScrollOverworldMapUp(void) {
    // LD_A_addr(wBGMapAnchor);
    // SUB_A(2 * BG_MAP_WIDTH);
    // LD_addr_A(wBGMapAnchor);
    // IF_NC goto not_underflowed;
    // LD_A_addr(wBGMapAnchor + 1);
    // DEC_A;
    // AND_A(0b11);
    // OR_A(HIGH(vBGMap0));
    // LD_addr_A(wBGMapAnchor + 1);
    wram->wBGMapAnchor -= 2 * BG_MAP_WIDTH;
    wram->wBGMapAnchor = LOW(wram->wBGMapAnchor) | (((HIGH(wram->wBGMapAnchor) & 0b11) | HIGH(vBGMap0)) << 8);

// not_underflowed:
    // LD_HL(wMetatileStandingY);
    // DEC_hl;
    // LD_A_hl;
    // CP_A(-1);  // was 0
    // IF_NZ goto done_up;
    if(wram->wMetatileStandingY-- == 0) {
        // LD_hl(0x1);
        wram->wMetatileStandingY = 0x1;
        // CALL(aUpdateOverworldMap_ScrollMapDataUp);
        UpdateOverworldMap_ScrollMapDataUp();
    }

// done_up:
    // RET;
}

static void UpdateOverworldMap_ScrollMapDataLeft(void) {
    // LD_HL(wOverworldMapAnchor);
    // LD_A_hl;
    // SUB_A(1);
    // LD_hli_A;
    // RET_NC ;
    // DEC_hl;
    // RET;
    wram->wOverworldMapAnchor--;
    printf("anchor=%d\n", wram->wOverworldMapAnchor - wOverworldMapBlocks);
}

static void UpdateOverworldMap_ScrollOverworldMapLeft(void) {
    // LD_A_addr(wBGMapAnchor);
    // LD_E_A;
    uint8_t e = LOW(wram->wBGMapAnchor);
    // AND_A(0xe0);
    // LD_D_A;
    // LD_A_E;
    // SUB_A(0x2);
    // AND_A(0x1f);
    // OR_A_D;
    // LD_addr_A(wBGMapAnchor);
    wram->wBGMapAnchor = (wram->wBGMapAnchor & 0xff00) | (((e - 0x2) & 0x1f) | (e & 0xe0));
    // LD_HL(wMetatileStandingX);
    // DEC_hl;
    // LD_A_hl;
    // CP_A(-1);
    // IF_NZ goto done_left;
    if(wram->wMetatileStandingX-- == 0) {
        // LD_hl(1);
        wram->wMetatileStandingX = 1;
        // CALL(aUpdateOverworldMap_ScrollMapDataLeft);
        UpdateOverworldMap_ScrollMapDataLeft();
    }

// done_left:
    // RET;
}

static void UpdateOverworldMap_ScrollMapDataRight(void) {
    // LD_HL(wOverworldMapAnchor);
    // LD_A_hl;
    // ADD_A(1);
    // LD_hli_A;
    // RET_NC ;
    // INC_hl;
    // RET;
    wram->wOverworldMapAnchor++;
    printf("anchor=%d\n", wram->wOverworldMapAnchor - wOverworldMapBlocks);
}

static void UpdateOverworldMap_ScrollOverworldMapRight(void) {
    // LD_A_addr(wBGMapAnchor);
    // LD_E_A;
    uint8_t e = LOW(wram->wBGMapAnchor);
    // AND_A(0xe0);
    // LD_D_A;
    // LD_A_E;
    // ADD_A(0x2);
    // AND_A(0x1f);
    // OR_A_D;
    // LD_addr_A(wBGMapAnchor);
    wram->wBGMapAnchor = (wram->wBGMapAnchor & 0xff00) | (((e + 0x2) & 0x1f) | (e & 0xe0));
    // LD_HL(wMetatileStandingX);
    // INC_hl;
    // LD_A_hl;
    // CP_A(2);
    // IF_NZ goto done_right;
    if(++wram->wMetatileStandingX == 2) {
        // LD_hl(0);
        wram->wMetatileStandingX = 0;
        // CALL(aUpdateOverworldMap_ScrollMapDataRight);
        UpdateOverworldMap_ScrollMapDataRight();
    }
// done_right:
    // RET;
}

void UpdateOverworldMap(void){
    // LD_A_addr(wPlayerStepDirection);
    // AND_A_A;
    // IF_Z goto step_down;
    // CP_A(UP);
    // IF_Z goto step_up;
    // CP_A(LEFT);
    // IF_Z goto step_left;
    // CP_A(RIGHT);
    // IF_Z goto step_right;
    // RET;
    switch(wram->wPlayerStepDirection) {
    case DOWN:
    // step_down:
        // CALL(aUpdateOverworldMap_ScrollOverworldMapDown);
        UpdateOverworldMap_ScrollOverworldMapDown();
        // CALL(aLoadMapPart);
        LoadMapPart_Conv();
        // CALL(aScrollMapDown);
        ScrollMapDown();
        // RET;
        return;

    case UP:
    // step_up:
        // CALL(aUpdateOverworldMap_ScrollOverworldMapUp);
        UpdateOverworldMap_ScrollOverworldMapUp();
        // CALL(aLoadMapPart);
        LoadMapPart_Conv();
        // CALL(aScrollMapUp);
        ScrollMapUp();
        // RET;
        return;

    case LEFT:
    // step_left:
        // CALL(aUpdateOverworldMap_ScrollOverworldMapLeft);
        UpdateOverworldMap_ScrollOverworldMapLeft();
        // CALL(aLoadMapPart);
        LoadMapPart_Conv();
        // CALL(aScrollMapLeft);
        ScrollMapLeft();
        // RET;
        return;

    case RIGHT:
    // step_right:
        // CALL(aUpdateOverworldMap_ScrollOverworldMapRight);
        UpdateOverworldMap_ScrollOverworldMapRight();
        // CALL(aLoadMapPart);
        LoadMapPart_Conv();
        // CALL(aScrollMapRight);
        ScrollMapRight();
        // RET;
        return;
    }
}
