#include "../../constants.h"
#include "dratini.h"
#include "../../data/moves/moves.h"

//  inputs:
//  hl must be set to 0 before calling this function.
//  a must be set to the number of Pokémon in the party.
//  outputs:
//  returns the address of the last Pokémon in the party in hl.
//  sets carry if a is 0.
static struct PartyMon* GiveDratini_GetNthPartyMon(uint8_t count){
    // LD_DE(wPartyMon1);
    // ADD_HL_DE;
    // AND_A_A;
    // IF_Z goto EmptyParty;
    if(count == 0) {
    // EmptyParty:
        // SCF;
        // RET;
        return NULL;
    }
    // DEC_A;
    // RET_Z ;
    // LD_DE(PARTYMON_STRUCT_LENGTH);

// loop:
    // ADD_HL_DE;
    // DEC_A;
    // IF_NZ goto loop;
    // RET;
    return wram->wPartyMon + (count - 1);

}

//  if wScriptVar is 0 or 1, change the moveset of the last Dratini in the party.
//   0: give it a special moveset with Extremespeed.
//   1: give it the normal moveset of a level 15 Dratini.
void GiveDratini(void){
    static const move_t Movesets[][4] = {
        // Moveset0:
        //  Dratini does not normally learn Extremespeed. This is a special gift.
        [0] = {
            WRAP,
            THUNDER_WAVE,
            TWISTER,
            EXTREMESPEED,
            //db ['0'];
        },
        // Moveset1:
        //  This is the normal moveset of a level 15 Dratini
        [1] = {
            WRAP,
            LEER,
            THUNDER_WAVE,
            TWISTER,
            //db ['0'];
        },
    };
    // LD_A_addr(wScriptVar);
    // CP_A(0x2);
    // RET_NC ;
    if(wram->wScriptVar >= 0x2)
        return;
    // LD_BC(wPartyCount);
    // LD_A_bc;
    uint8_t count = wram->wPartyCount;
    // LD_HL(MON_SPECIES);
    // CALL(aGiveDratini_GetNthPartyMon);
    struct PartyMon* mon = GiveDratini_GetNthPartyMon(count);
    if(mon == NULL)
        return;
    // LD_A_bc;
    // LD_C_A;
    // LD_DE(PARTYMON_STRUCT_LENGTH);

    do {
    // CheckForDratini:
    //  start at the end of the party and search backwards for a Dratini
        // LD_A_hl;
        // CP_A(DRATINI);
        // IF_Z goto GiveMoveset;
        if(mon->mon.species == DRATINI) {
        // GiveMoveset:
            // PUSH_HL;
            // LD_A_addr(wScriptVar);
            // LD_HL(mGiveDratini_Movesets);
            // LD_BC(mGiveDratini_Moveset1 - mGiveDratini_Moveset0);
            // CALL(aAddNTimes);
            const move_t* mv = Movesets[wram->wScriptVar];

        // get address of mon's first move
            // POP_DE;
            // INC_DE;
            // INC_DE;

            for(uint32_t i = 0; i < NUM_MOVES; ++i) {
            // GiveMoves:
                // LD_A_hl;
                // AND_A_A;  // is the move 00?
                // RET_Z ;  // if so, we're done here
                move_t mv_ = mv[i];

                // PUSH_HL;
                // PUSH_DE;
                // LD_de_A;  // give the Pokémon the new move
                mon->mon.moves[i] = mv_;

            // get the PP of the new move
                // DEC_A;
                // LD_HL(mMoves + MOVE_PP);
                // LD_BC(MOVE_LENGTH);
                // CALL(aAddNTimes);
                // LD_A(BANK(aMoves));
                // CALL(aGetFarByte);

            // get the address of the move's PP and update the PP
                // LD_HL(MON_PP - MON_MOVES);
                // ADD_HL_DE;
                // LD_hl_A;
                mon->mon.PP[i] = Moves[mv_].pp;

                // POP_DE;
                // POP_HL;
                // INC_DE;
                // INC_HL;
                // goto GiveMoves;
            }
            return;
        }
        // LD_A_L;
        // SUB_A_E;
        // LD_L_A;
        // LD_A_H;
        // SBC_A_D;
        // LD_H_A;
        mon--;
        // DEC_C;
        // IF_NZ goto CheckForDratini;
    } while(--count != 0);
    // RET;
    return;
}
