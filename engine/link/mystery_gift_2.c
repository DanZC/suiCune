#include "../../constants.h"
#include "mystery_gift_2.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../home/pokedex_flags.h"
#include "../../home/random.h"
#include "../../data/items/mystery_gift_items.h"
#include "../../data/decorations/mystery_gift_decos.h"

static uint8_t StageDataForMysteryGift_RandomSample(uint8_t b, uint8_t c){
    uint8_t a;
    // PUSH_DE;
    // CALL(aRandom);
    // CP_A(10 percent);
    // IF_C goto tenpercent;
    if(Random() < 10 percent) {
    // tenpercent:
        // CALL(aRandom);
        // CP_A(20 percent - 1);
        // IF_C goto twopercent;
        if(Random() < 20 percent - 1) {
        // twopercent:
            // CALL(aRandom);
            // CP_A(20 percent - 1);
            // IF_C goto pointfourpercent;
            if(Random() >= 20 percent - 1) {
                // LD_A_B;
                // SWAP_A;
                // AND_A(0x7);
                // ADD_A(0x18);
                a = (((b >> 4) | (b << 4)) & 0x7) + 0x18;
                // goto done;
            }
            else {
            // pointfourpercent:
                // LD_A_B;
                // AND_A(0x80);
                // LD_A(0x20);
                // IF_Z goto done;
                // LD_A(0x21);
                a = (b & 0x80)? 0x21: 0x20;
            }
        }
        else {
            // CALL(aRandom);
            // AND_A(0b011);
            a = Random() & 0b011;
            // LD_D_A;
            // RL_D;
            uint8_t d = RotateLeftC8(a);
            // LD_E(0x80);
            uint8_t e = 0x80;

            do {
            // loop2:
                // RLC_E;
                e = RotateLeftC8(e);
                // DEC_A;
                // IF_NZ goto loop2;
            } while(--a != 0);
            // LD_A_E;
            // AND_A_B;
            // IF_Z goto skip2;
            if(e & b) {
                // LD_A(0x1);
                a = 0x1;
            }
            else {
                a = e;
            }

        // skip2:
            // ADD_A_D;
            // ADD_A(0x10);
            a += d + 0x10;
            // goto done;
        }
    }
    else {
        // CALL(aRandom);
        // AND_A(0b111);
        a = Random() & 0b111;
        // LD_D_A;
        // RL_D;
        uint8_t d = RotateLeftC8(a);
        // LD_E(0x80);
        uint8_t e = 0x80;

        do {
        // loop:
            // RLC_E;
            e = RotateLeftC8(e);
            // DEC_A;
            // IF_NZ goto loop;
        } while(--a != 0);
        // LD_A_E;
        // AND_A_C;
        // IF_Z goto skip;
        if(e & c) {
            // LD_A(0x1);
            a = 0x1;
        }
        else {
            a = e;
        }

    // skip:
        // ADD_A_D;
        a += d;
        // goto done;
    }

// done:
    // POP_DE;
    // RET;
    return a;
}

void StageDataForMysteryGift(void){
    // LD_DE(wMysteryGiftStaging);
    uint8_t* de = wram->wMysteryGiftStaging;
    // LD_A(GS_VERSION + 1);
    // LD_de_A;
    *(de++) = GS_VERSION + 1;
    // INC_DE;  // wMysteryGiftStaging+1
    // LD_A(BANK(sGameData));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asGameData));
    // LD_HL(sPlayerData + wPlayerID - wPlayerData);
    uint16_t id = gb_read16(sPlayerData + wPlayerID - wPlayerData);
    // LD_A_hli;
    // LD_de_A;
    *(de++) = LOW(id);
    // LD_B_A;
    // INC_DE;  // wMysteryGiftStaging+2
    // LD_A_hl;
    // LD_de_A;
    *(de++) = HIGH(id);
    // LD_C_A;
    // INC_DE;  // wMysteryGiftStaging+3
    // PUSH_BC;
    // LD_HL(sPlayerData + wPlayerName - wPlayerData);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(de, GBToRAMAddr(sPlayerData + wPlayerName - wPlayerData), NAME_LENGTH);
    de += NAME_LENGTH;
    // PUSH_DE;  // wMysteryGiftStaging+14
    // LD_HL(sPokemonData + wPokedexCaught - wPokemonData);
    // LD_B(wEndPokedexCaught - wPokedexCaught);
    // CALL(aCountSetBits);
    *(de++) = CountSetBits_Conv2(GBToRAMAddr(sPokemonData + wPokedexCaught - wPokemonData), sizeof(wram->wPokedexCaught));
    // POP_DE;
    // POP_BC;
    // LD_A_addr(wNumSetBits);
    // LD_de_A;
    // INC_DE;  // wMysteryGiftStaging+15
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // CALL(aRandom);
    // AND_A(1);
    // LD_de_A;
    *(de++) = Random() & 1;
    // INC_DE;  // wMysteryGiftStaging+16
    // CALL(aStageDataForMysteryGift_RandomSample);
    // LD_de_A;
    *(de++) = StageDataForMysteryGift_RandomSample(LOW(id), HIGH(id));
    // INC_DE;  // wMysteryGiftStaging+17
    // LD_A_C;
    // LD_C_B;
    // LD_B_A;
    // CALL(aStageDataForMysteryGift_RandomSample);
    // LD_de_A;
    *(de++) = StageDataForMysteryGift_RandomSample(HIGH(id), LOW(id));
    // INC_DE;  // wMysteryGiftStaging+18
    // LD_A(BANK(sBackupMysteryGiftItem));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBackupMysteryGiftItem));
    // LD_A_addr(sBackupMysteryGiftItem);
    // LD_de_A;
    *(de++) = gb_read(sBackupMysteryGiftItem);
    // INC_DE;
    // LD_A_addr(sNumDailyMysteryGiftPartnerIDs);
    *(de++) = gb_read(sNumDailyMysteryGiftPartnerIDs);
    // LD_de_A;
    // LD_A(wMysteryGiftPlayerDataEnd - wMysteryGiftPlayerData);
    // LD_addr_A(wUnusedMysteryGiftStagedDataLength);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_HL(wMysteryGiftStaging);
    // LD_DE(wMysteryGiftPlayerData);
    // LD_BC(wMysteryGiftPlayerDataEnd - wMysteryGiftPlayerData);
    // JP(mCopyBytes);
    CopyBytes(wram->wMysteryGiftPlayerData, wram->wMysteryGiftStaging, wMysteryGiftPlayerDataEnd - wMysteryGiftPlayerData);
}

item_t MysteryGiftGetItem(uint8_t c){
    // LD_A_C;
    // CP_A(MysteryGiftItems.End - MysteryGiftItems);
    // JR_NC (mMysteryGiftFallbackItem);
    if(c >= MysteryGiftItems_Size)
        return GREAT_BALL; // fallback item
    // LD_HL(mMysteryGiftItems);
    // LD_B(0);
    // ADD_HL_BC;
    // LD_C_hl;
    // RET;
    return MysteryGiftItems[c];
}

uint8_t MysteryGiftGetDecoration(uint8_t c){
    // LD_A_C;
    // CP_A(MysteryGiftDecos.End - MysteryGiftDecos);
    // JR_NC (mMysteryGiftFallbackItem);
    if(c >= MysteryGiftDecos_Size)
        return DECO_POLKADOT_BED; // fallback deco
    // LD_HL(mMysteryGiftDecos);
    // LD_B(0);
    // ADD_HL_BC;
    // LD_C_hl;
    // RET;
    return MysteryGiftDecos[c];
}

void MysteryGiftFallbackItem(void){
    // LD_C(DECO_POLKADOT_BED);  // GREAT_BALL
    // RET;

// INCLUDE "data/items/mystery_gift_items.asm"

// INCLUDE "data/decorations/mystery_gift_decos.asm"

}
