#include "../../../constants.h"
#include "pokerus.h"
#include "../../../home/random.h"

#define out_of *0x100 /

void GivePokerusAndConvertBerries(void){
    PEEK("");
    // CALL(aConvertBerriesToBerryJuice);
    ConvertBerriesToBerryJuice();
    // LD_HL(wPartyMon1PokerusStatus);
    struct PartyMon* hl = wram->wPartyMon;
    // LD_A_addr(wPartyCount);
    // LD_B_A;
    uint8_t b = wram->wPartyCount;
    // LD_DE(PARTYMON_STRUCT_LENGTH);
//  Check to see if any of your Pokemon already has Pokerus.
//  If so, sample its spread through your party.
//  This means that you cannot get Pokerus de novo while
//  a party member has an active infection.

    do {
    // loopMons:
        // LD_A_hl;
        // AND_A(0xf);
        // IF_NZ goto TrySpreadPokerus;
        if(hl->mon.pokerusStatus & 0xf) {
        // TrySpreadPokerus:
            // CALL(aRandom);
            // CP_A(33 percent + 1);
            // RET_NC ;  // 1/3 chance
            if(Random_Conv() >= 33 percent + 1)
                return;

            // LD_A_addr(wPartyCount);
            // CP_A(1);
            // RET_Z ;  // only one mon, nothing to do
            if(wram->wPartyCount <= 1)
                return;

            // LD_C_hl;
            uint8_t c = hl->mon.pokerusStatus;
            // LD_A_B;
            // CP_A(2);
            // IF_C goto checkPreviousMonsLoop;  // no more mons after this one, go backwards

            // CALL(aRandom);
            // CP_A(50 percent + 1);
            // IF_C goto checkPreviousMonsLoop;  // 1/2 chance, go backwards
            if(b < 2 || Random_Conv() < 50 percent + 1) {
                while(1) {
                // checkPreviousMonsLoop:
                    // LD_A_addr(wPartyCount);
                    // CP_A_B;
                    // RET_Z ;  // no more mons
                    if(wram->wPartyCount == b)
                        return;
                    // LD_A_L;
                    // SUB_A_E;
                    // LD_L_A;
                    // LD_A_H;
                    // SBC_A_D;
                    // LD_H_A;
                    hl--;
                    // LD_A_hl;
                    // AND_A_A;
                    // IF_Z goto infectMon;
                    if(hl->mon.pokerusStatus == 0)
                        break;
                    // LD_C_A;
                    // AND_A(0x3);
                    // RET_Z ;  // if mon has cured pokerus, stop searching
                    if((c & 0x3) == 0)
                        return;
                    // INC_B;  // go on to next mon
                    b++;
                    // goto checkPreviousMonsLoop;
                }
            }
            else {
                while(1) {
                // checkFollowingMonsLoop:
                    // ADD_HL_DE;
                    hl++;
                    // LD_A_hl;
                    // AND_A_A;
                    // IF_Z goto infectMon;
                    if(hl->mon.pokerusStatus == 0)
                        break;
                    // LD_C_A;
                    // AND_A(0x3);
                    // RET_Z ;  // if mon has cured pokerus, stop searching
                    if((c & 0x3) == 0)
                        return;
                    // DEC_B;  // go on to next mon
                    --b;
                    // LD_A_B;
                    // CP_A(1);
                    // IF_NZ goto checkFollowingMonsLoop;  // no more mons left
                    if(b == 1)
                        return;
                    // RET;
                }
            }

        // infectMon:
            // LD_A_C;
            // AND_A(0xf0);
            // LD_B_A;
            b = c & 0xf0;
            // LD_A_C;
            // SWAP_A;
            // AND_A(0x3);
            // INC_A;
            // ADD_A_B;
            b += (((c & 0xf0) >> 4) & 0x3) + 1;
            // LD_hl_A;
            hl->mon.pokerusStatus = b;
            // RET;
            return;
        }
        // ADD_HL_DE;
        // DEC_B;
        // IF_NZ goto loopMons;
    } while(hl++, --b != 0);

//  If we haven't been to Goldenrod City at least once,
//  prevent the contraction of Pokerus.
    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_REACHED_GOLDENROD_F);
    // RET_Z ;
    if(!bit_test(wram->wStatusFlags2, STATUSFLAGS2_REACHED_GOLDENROD_F))
        return;
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // AND_A_A;
    // RET_NZ ;
    if(hram->hRandomAdd != 0)
        return;
    // LDH_A_addr(hRandomSub);
    // CP_A(3);
    // RET_NC ;  // 3/65536 chance (00 00, 00 01 or 00 02)
    if(hram->hRandomSub >= 3)
        return;
    // LD_A_addr(wPartyCount);
    // LD_B_A;
    b = wram->wPartyCount;

    uint8_t a;
    do {
    // randomMonSelectLoop:
        // CALL(aRandom);
        // AND_A(0x7);
        a = Random_Conv() & 0x7;
        // CP_A_B;
        // IF_NC goto randomMonSelectLoop;
    } while(a >= b);
    // LD_HL(wPartyMon1PokerusStatus);
    // CALL(aGetPartyLocation);  // get pokerus byte of random mon
    hl = wram->wPartyMon + a;
    // LD_A_hl;
    // AND_A(0xf0);
    // RET_NZ ;  // if it already has pokerus, do nothing
    if((hl->mon.pokerusStatus & 0xf0) != 0)
        return;

    do {
    // randomPokerusLoop:
    //   //  Simultaneously sample the strain and duration
        // CALL(aRandom);
        b = Random_Conv();
        // AND_A_A;
        // IF_Z goto randomPokerusLoop;
    } while(b == 0);
    // LD_B_A;
    // AND_A(0xf0);
    // IF_Z goto load_pkrs;
    if(b & 0xf0) {
        // LD_A_B;
        // AND_A(0x7);
        // INC_A;
        b = (b & 0x7) + 1;
    }

// load_pkrs:
    // LD_B_A;  // this should come before the label
    // SWAP_B;
    // AND_A(0x3);
    // INC_A;
    // ADD_A_B;
    hl->mon.pokerusStatus = (b << 4) + ((b & 0x3) + 1);
    // LD_hl_A;
    // RET;
}

void ConvertBerriesToBerryJuice(void){
//  If we haven't been to Goldenrod City at least once,
//  prevent Shuckle from turning held Berry into Berry Juice.
    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_REACHED_GOLDENROD_F);
    // RET_Z ;
    if(!bit_test(wram->wStatusFlags2, STATUSFLAGS2_REACHED_GOLDENROD_F))
        return;
    // CALL(aRandom);
    // CP_A(1 out_of 16);  // 6.25% chance
    // RET_NC ;
    if(Random_Conv() >= 1 out_of 16)
        return;
    // LD_HL(wPartyMons);
    struct PartyMon* hl = wram->wPartyMon;
    // LD_A_addr(wPartyCount);
    uint8_t a = wram->wPartyCount;

    do {
    // partyMonLoop:
        // PUSH_AF;
        // PUSH_HL;
        // LD_A_hl;
        // CP_A(SHUCKLE);
        // IF_NZ goto loopMon;
        if(hl->mon.species == SHUCKLE) {
            // LD_BC(MON_ITEM);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(BERRY);
            // IF_Z goto convertToJuice;
            if(hl->mon.item == BERRY) {
            // convertToJuice:
                // LD_A(BERRY_JUICE);
                // LD_hl_A;
                hl->mon.item = BERRY_JUICE;
                // POP_HL;
                // POP_AF;
                // RET;
                return;
            }
        }

    // loopMon:
        // POP_HL;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto partyMonLoop;
    } while(hl++, --a != 0);
    // RET;
}
