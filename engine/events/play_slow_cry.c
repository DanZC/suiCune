#include "../../constants.h"
#include "play_slow_cry.h"
#include "../../home/pokemon.h"
#include "../../home/audio.h"
#include "../../audio/engine.h"

void PlaySlowCry(void){
    // LD_A_addr(wScriptVar);
    // CALL(aLoadCry);
    // IF_C goto done;
    const struct PokemonCry* cry = LoadCry_Conv2(wram->wScriptVar);
    if(cry == NULL)
        return;

    // LD_HL(wCryPitch);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_BC(-0x140);
    // ADD_HL_BC;
    // LD_A_L;
    // LD_addr_A(wCryPitch);
    // LD_A_H;
    // LD_addr_A(wCryPitch + 1);
    wram->wCryPitch -= 0x140;
    // LD_HL(wCryLength);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_BC(0x60);
    // ADD_HL_BC;
    // LD_A_L;
    // LD_addr_A(wCryLength);
    // LD_A_H;
    // LD_addr_A(wCryLength + 1);
    wram->wCryLength += 0x60;
    // FARCALL(av_PlayCry);
    // SafeCallGBAuto(av_PlayCry);
    v_PlayCry(cry->index);
    // CALL(aWaitSFX);
    WaitSFX_Conv();

// done:
    // RET;
}
