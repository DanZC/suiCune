#include "../../constants.h"
#include "map_setup.h"
#include "../../home/map.h"
#include "../../home/map_objects.h"
#include "../../home/gfx.h"
#include "../../data/maps/setup_script_pointers.h"
#include "../../home/fade.h"
#include "../../home/audio.h"
#include "../../engine/tilesets/timeofday_pals.h"
#include "../../engine/overworld/map_objects_2.h"
#include "../../engine/overworld/player_object.h"
#include "../../data/maps/setup_scripts.h"

void RunMapSetupScript(void){
    // LDH_A_addr(hMapEntryMethod);
    // AND_A(0xf);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mMapSetupScripts);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aReadMapSetupScript);
    // RET;

// INCLUDE "data/maps/setup_scripts.asm"

    return ReadMapSetupScript_Conv(MapSetupScripts[(hram->hMapEntryMethod & 0xf) - 1]);
}

void ReadMapSetupScript(void){

loop:
    LD_A_hli;
    CP_A(-1);  // end?
    RET_Z ;

    PUSH_HL;

    LD_C_A;
    LD_B(0);
    LD_HL(mMapSetupCommands);
    ADD_HL_BC;
    ADD_HL_BC;
    ADD_HL_BC;

// bank
    LD_B_hl;
    INC_HL;

// address
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

// Bit 7 of the bank indicates a parameter.
// This is left unused.
    BIT_B(7);
    IF_Z goto go;

    POP_DE;
    LD_A_de;
    LD_C_A;
    INC_DE;
    PUSH_DE;


go:
    LD_A_B;
    AND_A(0x7f);
    RST(aFarCall);

    POP_HL;
    goto loop;

// INCLUDE "data/maps/setup_script_pointers.asm"

    return EnableTextAcceleration();
}

void ReadMapSetupScript_Conv(const uint8_t* script){

    while(1) {
    // loop:
        // LD_A_hli;
        uint8_t c = *(script++);
        // CP_A(-1);  // end?
        // RET_Z ;
        if(c == 0xff)
            return;

        // PUSH_HL;

        // LD_C_A;
        // LD_B(0);
        // LD_HL(mMapSetupCommands);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // ADD_HL_BC;

    // bank
        // LD_B_hl;
        // INC_HL;

    // address
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;

    // Bit 7 of the bank indicates a parameter.
    // This is left unused.
        // BIT_B(7);
        // IF_Z goto go;

        // POP_DE;
        // LD_A_de;
        // LD_C_A;
        // INC_DE;
        // PUSH_DE;


    // go:
        // LD_A_B;
        // AND_A(0x7f);
        // RST(aFarCall);
        MapSetupCommands[c]();

        // POP_HL;
        // goto loop;
    }

// INCLUDE "data/maps/setup_script_pointers.asm"
}

void EnableTextAcceleration(void){
    // XOR_A_A;
    // LD_addr_A(wDisableTextAcceleration);
    wram->wDisableTextAcceleration = 0;
    // RET;
}

void ActivateMapAnims(void){
    // LD_A(TRUE);
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = TRUE;
    // RET;
}

void SuspendMapAnims(void){
    // XOR_A_A;  // FALSE
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = FALSE;
    // RET;
}

void LoadMapObjects(void){
    // LD_A(MAPCALLBACK_OBJECTS);
    // CALL(aRunMapCallback);
    RunMapCallback(MAPCALLBACK_OBJECTS);
    // FARCALL(aLoadObjectMasks);
    LoadObjectMasks();
    // FARCALL(aInitializeVisibleSprites);
    InitializeVisibleSprites();
    // RET;
}

void MapSetup_DummyFunction(void){
//  //  unreferenced
    RET;

}

void ResetPlayerObjectAction(void){
    // LD_HL(wPlayerSpriteSetupFlags);
    // SET_hl(PLAYERSPRITESETUP_RESET_ACTION_F);
    bit_set(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_RESET_ACTION_F);
    // RET;
}

void SkipUpdateMapSprites(void){
    // LD_HL(wPlayerSpriteSetupFlags);
    // SET_hl(PLAYERSPRITESETUP_SKIP_RELOAD_GFX_F);
    bit_set(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_SKIP_RELOAD_GFX_F);
    // RET;
}

static bool CheckUpdatePlayerSprite_CheckBiking(void) {
    // AND_A_A;
    // LD_HL(wBikeFlags);
    // BIT_hl(BIKEFLAGS_ALWAYS_ON_BIKE_F);
    // RET_Z ;
    if(!bit_test(wram->wBikeFlags, BIKEFLAGS_ALWAYS_ON_BIKE_F))
        return false;
    // LD_A(PLAYER_BIKE);
    // LD_addr_A(wPlayerState);
    wram->wPlayerState = PLAYER_BIKE;
    // SCF;
    // RET;
    return true;
}

static bool CheckUpdatePlayerSprite_CheckSurfing(void) {
    // CALL(aCheckOnWater);
    // IF_NZ goto nope2;
    if(CheckOnWater()) {
        // LD_A_addr(wPlayerState);
        // CP_A(PLAYER_SURF);
        // IF_Z goto is_surfing;
        // CP_A(PLAYER_SURF_PIKA);
        // IF_Z goto is_surfing;
        if(wram->wPlayerState != PLAYER_SURF
        && wram->wPlayerState != PLAYER_SURF_PIKA) {
            // LD_A(PLAYER_SURF);
            // LD_addr_A(wPlayerState);
            wram->wPlayerState = PLAYER_SURF;
        }
    // is_surfing:
        // SCF;
        // RET;
        return true;
    }

// nope2:
    // AND_A_A;
    // RET;
    return false;
}

static bool CheckUpdatePlayerSprite_CheckSurfing2(void) {
    // LD_A_addr(wPlayerState);
    switch(wram->wPlayerState) {
        // CP_A(PLAYER_NORMAL);
        // IF_Z goto nope;
        case PLAYER_NORMAL:
        // CP_A(PLAYER_SKATE);
        // IF_Z goto nope;
        case PLAYER_SKATE:
        // nope:
            // AND_A_A;
            // RET;
            return false;
        default:
            // CALL(aGetMapEnvironment);
            switch(GetMapEnvironment()) {
                default:
                    return false;
                // CP_A(INDOOR);
                // IF_Z goto no_biking;
                // CP_A(ENVIRONMENT_5);
                // IF_Z goto no_biking;
                // CP_A(DUNGEON);
                // IF_Z goto no_biking;
                case INDOOR:
                case ENVIRONMENT_5:
                case DUNGEON:
                // no_biking:
                    // LD_A_addr(wPlayerState);
                    // CP_A(PLAYER_BIKE);
                    // IF_NZ goto nope;
                    if(wram->wPlayerState != PLAYER_BIKE)
                        return false;
            }
            fallthrough;
        // goto nope;
        // CP_A(PLAYER_SURF);
        // IF_Z goto surfing;
        case PLAYER_SURF:
        // CP_A(PLAYER_SURF_PIKA);
        // IF_Z goto surfing;
        case PLAYER_SURF_PIKA:
        // surfing:
            // LD_A(PLAYER_NORMAL);
            // LD_addr_A(wPlayerState);
            wram->wPlayerState = PLAYER_NORMAL;
            // SCF;
            // RET;
            return true;
    }

// nope:
    // AND_A_A;
    // RET;
}

void CheckUpdatePlayerSprite(void){
    // NOP;
    // CALL(aCheckUpdatePlayerSprite_CheckBiking);
    // IF_C goto ok;
    if(CheckUpdatePlayerSprite_CheckBiking())
        goto ok;
    // CALL(aCheckUpdatePlayerSprite_CheckSurfing);
    // IF_C goto ok;
    if(CheckUpdatePlayerSprite_CheckSurfing())
        goto ok;
    // CALL(aCheckUpdatePlayerSprite_CheckSurfing2);
    // IF_C goto ok;
    if(CheckUpdatePlayerSprite_CheckSurfing2())
        goto ok;
    // RET;
    return;

ok:
    // CALL(aUpdatePlayerSprite);
    UpdatePlayerSprite();
    // RET;
}

void FadeOutMapMusic(void){
    // LD_A(6);
    // CALL(aSkipMusic);
    SkipMusic(3);
    // RET;

}

void ApplyMapPalettes(void){
    // FARCALL(av_UpdateTimePals);
    v_UpdateTimePals();
    // RET;
}

void FadeMapMusicAndPalettes(void){
    // LD_E(LOW(MUSIC_NONE));
    // LD_A_addr(wMusicFadeID);
    // LD_D(HIGH(MUSIC_NONE));
    // LD_A_addr(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_A(0x4);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x4;
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight();
    // RET;

}

void ForceMapMusic(void){
    // LD_A_addr(wPlayerState);
    // CP_A(PLAYER_BIKE);
    // IF_NZ goto notbiking;
    if(wram->wPlayerState == PLAYER_BIKE) {
        // CALL(aMinVolume);
        MinVolume();
        // LD_A(0x88);
        // LD_addr_A(wMusicFade);
        wram->wMusicFade = 0x88;
    }
// notbiking:
    // CALL(aTryRestartMapMusic);
    TryRestartMapMusic();
    // RET;
}
