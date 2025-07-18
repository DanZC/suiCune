#include "../../constants.h"
#include "lucky_number.h"
#include "../../home/text.h"
#include "../../home/print_text.h"
#include "../../home/sram.h"
#include "../../home/names.h"
#include "../../mobile/mobile_41.h"
#include "../../util/serialize.h"
#include "../../data/text/common.h"

static bool CheckForLuckyNumberWinners_CompareLuckyNumberToMonID(struct BoxMon* mon){
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wMonIDDigitsBuffer);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum(wram->wMonIDDigitsBuffer, &mon->id, PRINTNUM_LEADINGZEROS | 2, 5);
    // LD_HL(wLuckyNumberDigitsBuffer);
    // LD_DE(wLuckyIDNumber);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum(wram->wLuckyNumberDigitsBuffer, &gPlayer.luckyIDNumber, PRINTNUM_LEADINGZEROS | 2, 5);
    // LD_B(5);
    uint8_t b = 5;
    // LD_C(0);
    uint8_t c = 0;
    // LD_HL(wLuckyNumberDigitsBuffer + 4);
    uint8_t* hl = wram->wLuckyNumberDigitsBuffer + 4;
    // LD_DE(wMonIDDigitsBuffer + 4);
    uint8_t* de = wram->wMonIDDigitsBuffer + 4;

    do {
    // loop:
        // LD_A_de;
        // CP_A_hl;
        // IF_NZ goto done;
        if(*de != *hl)
            break;
        // DEC_DE;
        // DEC_HL;
        // INC_C;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--de, --hl, ++c, --b != 0);


// done:
    // POP_HL;
    // PUSH_HL;
    // LD_DE(MON_SPECIES - MON_ID);
    // ADD_HL_DE;
    // LD_A_hl;
    // POP_HL;
    // POP_DE;
    // PUSH_AF;
    species_t s = mon->species;
    // LD_A_C;
    // LD_B(1);
    // CP_A(5);
    // IF_Z goto okay;
    if(c == 5)
        b = 1;
    // LD_B(2);
    // CP_A(3);
    // IF_NC goto okay;
    else if(c >= 3)
        b = 2;
    // LD_B(3);
    // CP_A(2);
    // IF_NZ goto nomatch;
    else if(c != 2)
        return false;

    else
        b = 3;

// okay:
    // INC_B;
    ++b;
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_Z goto bettermatch;
    // CP_A_B;
    // IF_C goto nomatch;
    if(wram->wScriptVar != 0 && wram->wScriptVar < b)
        return false;

// bettermatch:
    // DEC_B;
    // LD_A_B;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = --b;
    // POP_BC;
    // LD_A_B;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = s;
    // POP_BC;
    // SCF;
    // RET;
    return true;

// nomatch:
    // POP_BC;
    // POP_BC;
    // AND_A_A;
    // RET;
}

void CheckForLuckyNumberWinners(void){
    static const uint32_t BoxBankAddresses[] = {
        //table_width ['3', 'CheckForLuckyNumberWinners.BoxBankAddresses']
        asBox1,
        asBox2,
        asBox3,
        asBox4,
        asBox5,
        asBox6,
        asBox7,
        asBox8,
        asBox9,
        asBox10,
        asBox11,
        asBox12,
        asBox13,
        asBox14,
    };
    static_assert(lengthof(BoxBankAddresses) == NUM_BOXES, "");

    static const txt_cmd_s LuckyNumberMatchPartyText[] = {
        text_far(v_LuckyNumberMatchPartyText)
        text_end
    };

    static const txt_cmd_s LuckyNumberMatchPCText[] = {
        text_far(v_LuckyNumberMatchPCText)
        text_end
    };
    struct Box box;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x0;
    // LD_addr_A(wTempByteValue);
    wram->wTempByteValue = FALSE;
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_D_A;
    uint8_t d = gPokemon.partyCount;
    // LD_HL(wPartyMon1ID);
    struct PartyMon* hl = gPokemon.partyMon;
    // LD_BC(wPartySpecies);
    species_t* bc = gPokemon.partySpecies;

    do {
    // PartyLoop:
        // LD_A_bc;
        // INC_BC;
        // CP_A(EGG);
        if(*bc != EGG) {
            // CALL_NZ (aCheckForLuckyNumberWinners_CompareLuckyNumberToMonID);
            CheckForLuckyNumberWinners_CompareLuckyNumberToMonID(&hl->mon);
        }
        bc++;
        // PUSH_BC;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        hl++;
        // POP_BC;
        // DEC_D;
        // IF_NZ goto PartyLoop;
    } while(--d != 0);
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBox));
    Deserialize_Box(&box, GBToRAMAddr(sBox));
    // LD_A_addr(sBoxCount);
    // AND_A_A;
    // IF_Z goto SkipOpenBox;
    if(gb_read(sBoxCount) != 0) {
        // LD_D_A;
        uint8_t d = box.count;
        // LD_HL(sBoxMon1ID);
        struct BoxMon* mon = box.mons;
        // LD_BC(sBoxSpecies);
        species_t* species = box.species;

        do {
        // OpenBoxLoop:
            // LD_A_bc;
            // INC_BC;
            // CP_A(EGG);
            // IF_Z goto SkipOpenBoxMon;
            // CALL(aCheckForLuckyNumberWinners_CompareLuckyNumberToMonID);
            // IF_NC goto SkipOpenBoxMon;
            if(*species != EGG && CheckForLuckyNumberWinners_CompareLuckyNumberToMonID(mon)) {
                // LD_A(TRUE);
                // LD_addr_A(wTempByteValue);
                wram->wTempByteValue = TRUE;
            }

        // SkipOpenBoxMon:
            species++;
            // PUSH_BC;
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            mon++;
            // POP_BC;
            // DEC_D;
            // IF_NZ goto OpenBoxLoop;
        } while(--d != 0);
    }

// SkipOpenBox:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_C(0x0);
    uint8_t c = 0x0;

    do {
    // BoxesLoop:
        // LD_A_addr(wCurBox);
        // AND_A(0xf);
        // CP_A_C;
        // IF_Z goto SkipBox;
        if(gPlayer.curBox == c)
            continue;
        // LD_HL(mCheckForLuckyNumberWinners_BoxBankAddresses);
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(BoxBankAddresses[c]));
        Deserialize_Box(&box, GBToRAMAddr((uint16_t)BoxBankAddresses[c]));
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;  // hl now contains the address of the loaded box in SRAM
        uint8_t count = box.count;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto SkipBox;  // no mons in this box
        if(count == 0)
            continue;
        // PUSH_BC;
        // LD_B_H;
        // LD_C_L;
        // INC_BC;
        species_t* bc = box.species;
        // LD_DE(sBoxMon1ID - sBox);
        // ADD_HL_DE;
        struct BoxMon* hl = box.mons;
        // LD_D_A;
        uint8_t d = count;

        do {
        // BoxNLoop:
            // LD_A_bc;
            // INC_BC;
            species_t species = *(bc++);
            // CP_A(EGG);
            // IF_Z goto SkipBoxMon;

            // CALL(aCheckForLuckyNumberWinners_CompareLuckyNumberToMonID);  // sets wScriptVar and wCurPartySpecies appropriately
            // IF_NC goto SkipBoxMon;
            if(species != EGG && CheckForLuckyNumberWinners_CompareLuckyNumberToMonID(hl)) {
                // LD_A(TRUE);
                // LD_addr_A(wTempByteValue);
                wram->wTempByteValue = TRUE;
            }

        // SkipBoxMon:
            // PUSH_BC;
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            // POP_BC;
            // DEC_D;
            // IF_NZ goto BoxNLoop;
        } while(hl++, --d != 0);
        // POP_BC;

    // SkipBox:
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_BOXES);
        // IF_C goto BoxesLoop;
    } while(++c < NUM_BOXES);

    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // RET_Z ;  // found nothing
    if(wram->wScriptVar == FALSE)
        return;

    // FARCALL(aStubbedTrainerRankings_LuckyNumberShow);
    StubbedTrainerRankings_LuckyNumberShow();
    // LD_A_addr(wTempByteValue);
    // AND_A_A;
    // PUSH_AF;
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wCurPartySpecies);
    // LD_HL(mCheckForLuckyNumberWinners_LuckyNumberMatchPartyText);
    // POP_AF;
    // IF_Z goto print;
    if(wram->wTempByteValue == 0) {
        PrintText(LuckyNumberMatchPartyText);
    }
    else {
        // LD_HL(mCheckForLuckyNumberWinners_LuckyNumberMatchPCText);

    // print:
        // JP(mPrintText);
        PrintText(LuckyNumberMatchPCText);
    }
}

void PrintTodaysLuckyNumber(void){
    // LD_HL(wStringBuffer3);
    // LD_DE(wLuckyIDNumber);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum(wram->wStringBuffer3, &gPlayer.luckyIDNumber, PRINTNUM_LEADINGZEROS | 2, 5);
    // LD_A(0x50);
    // LD_addr_A(wStringBuffer3 + 5);
    wram->wStringBuffer3[5] = 0x50;
    // RET;

}
