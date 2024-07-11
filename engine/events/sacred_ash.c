#include "../../constants.h"
#include "sacred_ash.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"
#include "../../home/queue_script.h"

void v_SacredAsh(void){
    // LD_A(0x0);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = FALSE;
    // CALL(aCheckAnyFaintedMon);
    // RET_NC ;
    if(!CheckAnyFaintedMon())
        return;

    // LD_HL(mSacredAshScript);
    // CALL(aQueueScript);
    QueueScript_Conv2(SacredAshScript);
    // LD_A(0x1);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = TRUE;
    // RET;
}

bool CheckAnyFaintedMon(void){
    // LD_DE(PARTYMON_STRUCT_LENGTH);
    // LD_BC(wPartySpecies);
    species_t* bc = wram->wPartySpecies;
    // LD_HL(wPartyMon1HP);
    struct PartyMon* hl = wram->wPartyMon;
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(wram->wPartyCount == 0)
        return false;

    uint8_t a = wram->wPartyCount;

    do {
    // loop:
        // PUSH_AF;
        // PUSH_HL;
        // LD_A_bc;
        // INC_BC;
        // CP_A(EGG);
        // IF_Z goto next;
        if(*bc == EGG)
            continue;

        // LD_A_hli;
        // OR_A_hl;
        // IF_Z goto done;
        if(hl->HP == 0) {
        // done:
            // POP_HL;
            // POP_AF;
            // SCF;
            // RET;
            return true;
        }

    // next:
        // POP_HL;
        // ADD_HL_DE;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(bc++, hl++, --a != 0);
    // XOR_A_A;
    // RET;
    return false;
}

bool SacredAshScript(script_s* s){
    static const txt_cmd_s UseSacredAshText[] = {
        text_far(v_UseSacredAshText)
        text_end
    };
    SCRIPT_BEGIN
    special(HealParty)
    reloadmappart
    playsound(SFX_WARP_TO)
    special(FadeOutPalettes)
    special(FadeInPalettes)
    special(FadeOutPalettes)
    special(FadeInPalettes)
    special(FadeOutPalettes)
    special(FadeInPalettes)
    waitsfx
    writetext(UseSacredAshText)
    playsound(SFX_CAUGHT_MON)
    waitsfx
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
