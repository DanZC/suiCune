#include "../../constants.h"
#include "odd_egg.h"
#include "../../home/random.h"
#include "../../home/copy.h"
#include "../../home/item.h"
#include "../../mobile/mobile_46.h"
#include "../../data/events/odd_eggs.h"

// Figure out which egg to give.
void v_GiveOddEgg(void){
// Compare a random word to
// probabilities out of 0xffff.
    // CALL(aRandom);
    Random();
    // LD_HL(mOddEggProbabilities);
    const uint16_t* hl = OddEggProbabilities;
    // LD_C(0);
    // LD_B_C;
    uint16_t bc = 0;

    while(1) {
    // loop:
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint16_t de = *hl;

    // Break on $ffff.
        // LD_A_D;
        // CP_A(HIGH(0xffff));
        // IF_NZ goto not_done;
        // LD_A_E;
        // CP_A(LOW(0xffff));
        // IF_Z goto done;
        if(de == 0xffff)
            break;

    // not_done:

    // Break when the random word <= the next probability in de.
        // LDH_A_addr(hRandomSub);
        // CP_A_D;
        // IF_C goto done;
        // IF_Z goto ok;
        // goto next;

        uint16_t value = hram->hRandomAdd | (hram->hRandomSub << 8);
    // ok:
        // LDH_A_addr(hRandomAdd);
        // CP_A_E;
        // IF_C goto done;
        // IF_Z goto done;
        if(de <= value)
            break;

    // next:
        // INC_BC;
        bc++;
        // goto loop;
    }

// done:

    // LD_HL(mOddEggs);
    // LD_A(NICKNAMED_MON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    const struct NicknamedMon* mon = OddEggs + bc;

// Writes to wOddEgg, wOddEggName, and wOddEggOT,
// even though OddEggs does not have data for wOddEggOT
    // LD_DE(wOddEgg);
    // LD_BC(NICKNAMED_MON_STRUCT_LENGTH + NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wOddEgg, mon, sizeof(wram->wOddEgg));
    CopyBytes(wram->wOddEggName, mon->nickname, sizeof(wram->wOddEggName));

    // LD_A(EGG_TICKET);
    // LD_addr_A(wCurItem);
    wram->wCurItem = EGG_TICKET;
    // LD_A(1);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = 1;
    // LD_A(-1);
    // LD_addr_A(wCurItemQuantity);
    wram->wCurItemQuantity = (uint8_t)-1;
    // LD_HL(wNumItems);
    // CALL(aTossItem);
    TossItem_Conv((item_pocket_s*)&wram->wNumItems, EGG_TICKET);

// load species in wMobileMonSpecies
    // LD_A(EGG);
    // LD_addr_A(wMobileMonSpecies);
    wram->wMobileMonSpecies = EGG;

// load pointer to (wMobileMonSpecies - 1) in wMobileMonSpeciesPointer
    // LD_A(LOW(wMobileMonSpecies - 1));
    // LD_addr_A(wMobileMonSpeciesPointer);
    // LD_A(HIGH(wMobileMonSpecies - 1));
    // LD_addr_A(wMobileMonSpeciesPointer + 1);
    wram->wMobileMonSpeciesPointer = wMobileMonSpecies - 1;
// load pointer to wOddEgg in wMobileMonStructPointer
    // LD_A(LOW(wOddEgg));
    // LD_addr_A(wMobileMonStructPointer);
    // LD_A(HIGH(wOddEgg));
    // LD_addr_A(wMobileMonStructPointer + 1);
    wram->wMobileMonStructPointer = wOddEgg;

// load Odd Egg Name in wTempOddEggNickname
    // LD_HL(mv_GiveOddEgg_Odd);
    // LD_DE(wTempOddEggNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
static const char Odd[] = "ODD@@@@@@@@@";
    CopyBytes(wram->wTempOddEggNickname, U82C(Odd), MON_NAME_LENGTH);

// load pointer to wTempOddEggNickname in wMobileMonOTPointer
    // LD_A(LOW(wTempOddEggNickname));
    // LD_addr_A(wMobileMonOTPointer);
    // LD_A(HIGH(wTempOddEggNickname));
    // LD_addr_A(wMobileMonOTPointer + 1);
    wram->wMobileMonOTPointer = wTempOddEggNickname;
// load pointer to wOddEggName in wMobileMonNicknamePointer
    // LD_A(LOW(wOddEggName));
    // LD_addr_A(wMobileMonNicknamePointer);
    // LD_A(HIGH(wOddEggName));
    // LD_addr_A(wMobileMonNicknamePointer + 1);
    wram->wMobileMonNicknamePointer = wOddEggName;
    // FARCALL(aAddMobileMonToParty);
    AddMobileMonToParty(&wram->wMobileMonSpecies, &wram->wOddEgg, wram->wTempOddEggNickname, wram->wOddEggName, NULL);
    // RET;

// INCLUDE "data/events/odd_eggs.asm"

}
