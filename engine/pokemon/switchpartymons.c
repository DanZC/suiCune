#include "../../constants.h"
#include "switchpartymons.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/sram.h"

static void v_SwitchPartyMons_ClearSprite(uint8_t a) {
    // PUSH_AF;
    // hlcoord(0, 1, wTilemap);
    // LD_BC(2 * SCREEN_WIDTH);
    // CALL(aAddNTimes);
    // LD_BC(2 * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 1, wram->wTilemap) + 2 * SCREEN_WIDTH * a, 2 * SCREEN_WIDTH, 0x7f);
    // POP_AF;
    // LD_HL(wVirtualOAMSprite00);
    // LD_BC(4 * SPRITEOAMSTRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_DE(SPRITEOAMSTRUCT_LENGTH);
    // LD_C(4);
    for(uint32_t i = 0; i < 4; ++i) {
    // gfx_loop:
        // LD_hl(SCREEN_WIDTH_PX);  // y (off-screen)
        wram->wVirtualOAMSprite[4 * a + i].yCoord = SCREEN_WIDTH_PX;
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto gfx_loop;
    }
    // LD_DE(SFX_SWITCH_POKEMON);
    // CALL(aWaitPlaySFX);
    WaitPlaySFX(SFX_SWITCH_POKEMON);
    // RET;
}

static void v_SwitchPartyMons_SwapMonAndMail(uint8_t from, uint8_t to) {
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_BC(wPartySpecies);
    // LD_A_addr(wSwitchMonTo);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    species_t* species_to = wram->wPartySpecies + to;
    // LD_A_addr(wSwitchMonFrom);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_BC;
    species_t* species_from = wram->wPartySpecies + from;
    // LD_A_hl;
    // PUSH_AF;
    species_t temp_species = *species_from;
    // LD_A_de;
    // LD_hl_A;
    *species_from = *species_to;
    // POP_AF;
    // LD_de_A;
    *species_to = temp_species;
    // LD_A_addr(wSwitchMonTo);
    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // PUSH_HL;
    // LD_DE(wSwitchMonBuffer);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wSwitchMonBuffer, wram->wPartyMon + to, PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wSwitchMonFrom);
    // LD_HL(wPartyMon1);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // POP_DE;
    // PUSH_HL;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPartyMon + to, wram->wPartyMon + from, PARTYMON_STRUCT_LENGTH);
    // POP_DE;
    // LD_HL(wSwitchMonBuffer);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPartyMon + from, wram->wSwitchMonBuffer, PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wSwitchMonTo);
    // LD_HL(wPartyMonOTs);
    // CALL(aSkipNames);
    // PUSH_HL;
    // CALL(av_SwitchPartyMons_CopyNameToSwitchMonBuffer);
    CopyBytes(wram->wSwitchMonBuffer, wram->wPartyMonOT[to], NAME_LENGTH);
    // LD_A_addr(wSwitchMonFrom);
    // LD_HL(wPartyMonOTs);
    // CALL(aSkipNames);
    // POP_DE;
    // PUSH_HL;
    // CALL(av_SwitchPartyMons_CopyName);
    CopyBytes(wram->wPartyMonOT[to], wram->wPartyMonOT[from], NAME_LENGTH);
    // POP_DE;
    // LD_HL(wSwitchMonBuffer);
    // CALL(av_SwitchPartyMons_CopyName);
    CopyBytes(wram->wPartyMonOT[from], wram->wSwitchMonBuffer, NAME_LENGTH);
    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wSwitchMonTo);
    // CALL(aSkipNames);
    // PUSH_HL;
    // CALL(av_SwitchPartyMons_CopyNameToSwitchMonBuffer);
    CopyBytes(wram->wSwitchMonBuffer, wram->wPartyMonNickname[to], NAME_LENGTH);
    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wSwitchMonFrom);
    // CALL(aSkipNames);
    // POP_DE;
    // PUSH_HL;
    // CALL(av_SwitchPartyMons_CopyName);
    CopyBytes(wram->wPartyMonNickname[to], wram->wPartyMonNickname[from], NAME_LENGTH);
    // POP_DE;
    // LD_HL(wSwitchMonBuffer);
    // CALL(av_SwitchPartyMons_CopyName);
    CopyBytes(wram->wPartyMonNickname[from], wram->wSwitchMonBuffer, NAME_LENGTH);
    // LD_HL(sPartyMail);
    // LD_A_addr(wSwitchMonTo);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // PUSH_HL;
    OpenSRAM(MBANK(asPartyMail));
    struct MailMsg* hl = (struct MailMsg*)GBToRAMAddr(sPartyMail);
    // LD_DE(wSwitchMonBuffer);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    // CALL(aCopyBytes);
    CopyBytes(wram->wSwitchMonBuffer, hl + to, MAIL_STRUCT_LENGTH);
    // LD_HL(sPartyMail);
    // LD_A_addr(wSwitchMonFrom);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // POP_DE;
    // PUSH_HL;
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(hl + to, hl + from, MAIL_STRUCT_LENGTH);
    // POP_DE;
    // LD_HL(wSwitchMonBuffer);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(hl + from, wram->wSwitchMonBuffer, MAIL_STRUCT_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;

// CopyNameToSwitchMonBuffer:
    // LD_DE(wSwitchMonBuffer);

// CopyName:
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    // RET;
}

void v_SwitchPartyMons(void){
    // LD_A_addr(wSwitchMon);
    // DEC_A;
    // LD_addr_A(wSwitchMonFrom);
    wram->wSwitchMonFrom = wram->wSwitchMon - 1;
    // LD_B_A;
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_addr_A(wSwitchMonTo);
    wram->wSwitchMonTo = wram->wMenuCursorY - 1;
    // CP_A_B;
    // IF_Z goto skip;
    if(wram->wSwitchMonFrom != wram->wSwitchMonTo) {
        // CALL(av_SwitchPartyMons_SwapMonAndMail);
        v_SwitchPartyMons_SwapMonAndMail(wram->wSwitchMonFrom, wram->wSwitchMonTo);
        // LD_A_addr(wSwitchMonFrom);
        // CALL(av_SwitchPartyMons_ClearSprite);
        v_SwitchPartyMons_ClearSprite(wram->wSwitchMonFrom);
        // LD_A_addr(wSwitchMonTo);
        // CALL(av_SwitchPartyMons_ClearSprite);
        v_SwitchPartyMons_ClearSprite(wram->wSwitchMonTo);
    }

// skip:
    // RET;
    return;

}
