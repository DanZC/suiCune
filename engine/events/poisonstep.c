#include "../../constants.h"
#include "poisonstep.h"
#include "poisonstep_pals.h"
#include "whiteout.h"
#include "happiness_egg.h"
#include "overworld.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/map.h"
#include "../../home/text.h"
#include "../battle/core.h"
#include "../../data/text/common.h"
#include "../../util/scripting.h"

static void Script_MonFaintedToPoison_CheckWhitedOut(void);
static void PlayPoisonSFX(void);

static bool Script_MonFaintedToPoison(script_s* s) {
    SCRIPT_BEGIN
    PlayPoisonSFX();
    opentext
    Script_MonFaintedToPoison_CheckWhitedOut();
    iffalse(whiteout)
    closetext
    s_end

whiteout:
    sjump(OverworldWhiteoutScript)
    SCRIPT_END
}

static void PlayPoisonSFX(void) {
    // LD_DE(SFX_POISON);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_POISON);
    // LD_B(0x2);
    // PREDEF(pLoadPoisonBGPals);
    LoadPoisonBGPals();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

static void Script_MonFaintedToPoison_CheckWhitedOut(void) {
    static const txt_cmd_s PoisonFaintText[] = {
        text_far(v_PoisonFaintText)
        text_end
    };
    // XOR_A_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = 0;
    // LD_DE(wPoisonStepPartyFlags);
    uint8_t* de = wram->wPoisonStepPartyFlags;

    do {
    // party_loop:
        // PUSH_DE;
        // LD_A_de;
        // AND_A(0b10);
        // IF_Z goto mon_not_fainted;
        if(de[wram->wCurPartyMon] & 0b10) {
            // LD_C(HAPPINESS_POISONFAINT);
            // FARCALL(aChangeHappiness);
            ChangeHappiness_Conv(HAPPINESS_POISONFAINT);
            // FARCALL(aGetPartyNickname);
            GetPartyNickname();
            // LD_HL(mDoPoisonStep_PoisonFaintText);
            // CALL(aPrintText);
            PrintText_Conv2(PoisonFaintText);
        }

    // mon_not_fainted:
        // POP_DE;
        // INC_DE;
        // LD_HL(wCurPartyMon);
        // INC_hl;
        // LD_A_addr(wPartyCount);
        // CP_A_hl;
        // IF_NZ goto party_loop;
    } while(++wram->wCurPartyMon != wram->wPartyCount);
    // PREDEF(pCheckPlayerPartyForFitMon);
    // LD_A_D;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = CheckPlayerPartyForFitMon_Conv()? TRUE: FALSE;
    // RET;
}

static u8_flag_s DoPoisonStep_DamageMonIfPoisoned(void) {
//  check if mon is poisoned, return if not
    // LD_A(MON_STATUS);
    // CALL(aGetPartyParamLocation);
    // LD_A_hl;
    // AND_A(1 << PSN);
    // RET_Z ;
    if((wram->wPartyMon[wram->wCurPartyMon].status & (1 << PSN)) == 0)
        return u8_flag(0, false);

//  check if mon is already fainted, return if so
    // LD_A(MON_HP);
    // CALL(aGetPartyParamLocation);
    // LD_A_hli;
    // LD_B_A;
    // LD_C_hl;
    // OR_A_C;
    // RET_Z ;
    if(wram->wPartyMon[wram->wCurPartyMon].HP == 0)
        return u8_flag(0, false);

//  do 1 HP damage
    // DEC_BC;
    // LD_hl_C;
    // DEC_HL;
    // LD_hl_B;
    wram->wPartyMon[wram->wCurPartyMon].HP = NativeToBigEndian16(BigEndianToNative16(wram->wPartyMon[wram->wCurPartyMon].HP) - 1);

//  check if mon has fainted as a result of poison damage
    // LD_A_B;
    // OR_A_C;
    // IF_NZ goto not_fainted;

    if(wram->wPartyMon[wram->wCurPartyMon].HP == 0) {
    //  the mon has fainted, reset its status, set carry, and return %10
        // LD_A(MON_STATUS);
        // CALL(aGetPartyParamLocation);
        // LD_hl(0);
        wram->wPartyMon[wram->wCurPartyMon].status = 0;
        // LD_C(0b10);
        // SCF;
        // RET;
        return u8_flag(0b10, true);
    }

// not_fainted:
//  set carry and return %01
    // LD_C(0b01);
    // SCF;
    // RET;
    return u8_flag(0b01, true);
}

bool DoPoisonStep(void){
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // IF_Z goto no_faint;
    if(wram->wPartyCount == 0) {
        return false;
    }

    // XOR_A_A;
    // LD_C(wPoisonStepDataEnd - wPoisonStepData);
    // LD_HL(wPoisonStepData);

// loop_clearPoisonStepData:
    // LD_hli_A;
    // DEC_C;
    // IF_NZ goto loop_clearPoisonStepData;
    wram->wPoisonStepFlagSum = 0;
    ByteFill_Conv2(wram->wPoisonStepPartyFlags, sizeof(wram->wPoisonStepPartyFlags), 0);

    // XOR_A_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = 0;

    do {
    // loop_check_poison:
        // CALL(aDoPoisonStep_DamageMonIfPoisoned);
        u8_flag_s res = DoPoisonStep_DamageMonIfPoisoned();
        // IF_NC goto not_poisoned;
        if(res.flag) {
        //  the output flag is stored in c, copy it to [wPoisonStepPartyFlags + [wCurPartyMon]]
        //  and set the corresponding flag in wPoisonStepFlagSum
            // LD_A_addr(wCurPartyMon);
            // LD_E_A;
            // LD_D(0);
            // LD_HL(wPoisonStepPartyFlags);
            // ADD_HL_DE;
            // LD_hl_C;
            wram->wPoisonStepPartyFlags[wram->wCurPartyMon] = res.a;
            // LD_A_addr(wPoisonStepFlagSum);
            // OR_A_C;
            // LD_addr_A(wPoisonStepFlagSum);
            wram->wPoisonStepFlagSum |= res.a;
        }

    // not_poisoned:
        // LD_A_addr(wPartyCount);
        // LD_HL(wCurPartyMon);
        // INC_hl;
        // CP_A_hl;
        // IF_NZ goto loop_check_poison;
    } while(++wram->wCurPartyMon < wram->wPartyCount);

    // LD_A_addr(wPoisonStepFlagSum);
    // AND_A(0b10);
    // IF_NZ goto someone_has_fainted;
    if(wram->wPoisonStepFlagSum & 0b10) {
    // someone_has_fainted:
        // LD_A(BANK(aDoPoisonStep_Script_MonFaintedToPoison));
        // LD_HL(mDoPoisonStep_Script_MonFaintedToPoison);
        // CALL(aCallScript);
        CallScript_Conv2(Script_MonFaintedToPoison);
        // SCF;
        // RET;
        return true;
    }
    // LD_A_addr(wPoisonStepFlagSum);
    // AND_A(0b01);
    // IF_Z goto no_faint;
    if(wram->wPoisonStepFlagSum & 0b01) {
        // CALL(aDoPoisonStep_PlayPoisonSFX);
        PlayPoisonSFX();
        // XOR_A_A;
        // RET;
        return false;
    }

// no_faint:
    // XOR_A_A;
    // RET;
    return false;


// PoisonWhiteoutText:
//   //  unreferenced
    //text_far ['_PoisonWhiteoutText']
    //text_end ['?']
}
