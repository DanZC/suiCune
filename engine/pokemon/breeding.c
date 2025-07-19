#include "../../constants.h"
#include "breeding.h"
#include "mon_stats.h"
#include "move_mon.h"
#include "caught_data.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/joypad.h"
#include "../../home/audio.h"
#include "../../home/clear_sprites.h"
#include "../../home/text.h"
#include "../../home/flag.h"
#include "../../home/pokedex_flags.h"
#include "../../home/string.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"
#include "../../home/sprite_anims.h"
#include "../../home/lcd.h"
#include "../../home/video.h"
#include "../../home/window.h"
#include "../../home/map.h"
#include "../../home/menu.h"
#include "../../home/names.h"
#include "../items/tmhm2.h"
#include "../menus/naming_screen.h"
#include "../gfx/sprites.h"
#include "../gfx/load_pics.h"
#include "../gfx/pic_animation.h"
#include "../gfx/place_graphic.h"
#include "../overworld/player_object.h"
#include "../../mobile/mobile_41.h"
#include "../../data/pokemon/egg_moves.h"
#include "../../data/pokemon/evos_attacks_pointers.h"
#include "../../data/moves/tmhm_moves.h"
#include "../../data/text/common.h"

static bool GetEggMove(const move_t* de);
static void LoadEggMove(const move_t* de2);
static const move_t* GetHeritableMoves(void);
static move_t* GetBreedmonMovePointer(void);

static bool CheckBreedmonCompatibility_CheckBreedingGroupCompatibility(void){
//  If either mon is in the No Eggs group,
//  they are not compatible.
    // LD_A_addr(wBreedMon2Species);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = gPokemon.breedMon2.species;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurSpecies);
    // LD_A_addr(wBaseEggGroups);
    // CP_A(EGG_NONE * 0x11);
    // IF_Z goto Incompatible;
    if(wram->wBaseEggGroups == EGG_NONE * 0x11)
        return false;

    // LD_A_addr(wBreedMon1Species);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = gPokemon.breedMon1.species;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurSpecies);
    // LD_A_addr(wBaseEggGroups);
    // CP_A(EGG_NONE * 0x11);
    // IF_Z goto Incompatible;
    if(wram->wBaseEggGroups == EGG_NONE * 0x11)
        return false;

//  Ditto is automatically compatible with everything.
//  If not Ditto, load the breeding groups into b/c and d/e.
    // LD_A_addr(wBreedMon2Species);
    // CP_A(DITTO);
    // IF_Z goto Compatible;
    if(gPokemon.breedMon2.species == DITTO)
        return true;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = gPokemon.breedMon2.species;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurSpecies);
    // LD_A_addr(wBaseEggGroups);
    // PUSH_AF;
    // AND_A(0xf);
    // LD_B_A;
    uint8_t b = wram->wBaseEggGroups & 0xf;
    // POP_AF;
    // AND_A(0xf0);
    // SWAP_A;
    // LD_C_A;
    uint8_t c = (wram->wBaseEggGroups & 0xf0) >> 4;

    // LD_A_addr(wBreedMon1Species);
    // CP_A(DITTO);
    // IF_Z goto Compatible;
    if(gPokemon.breedMon1.species == DITTO)
        return true;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = gPokemon.breedMon1.species;
    // PUSH_BC;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurSpecies);
    // POP_BC;
    // LD_A_addr(wBaseEggGroups);
    // PUSH_AF;
    // AND_A(0xf);
    // LD_D_A;
    uint8_t d = wram->wBaseEggGroups & 0xf;
    // POP_AF;
    // AND_A(0xf0);
    // SWAP_A;
    // LD_E_A;
    uint8_t e = (wram->wBaseEggGroups & 0xf0) >> 4;

    // LD_A_D;
    // CP_A_B;
    // IF_Z goto Compatible;
    // CP_A_C;
    // IF_Z goto Compatible;
    if(d == b || d == c)
        return true;

    // LD_A_E;
    // CP_A_B;
    // IF_Z goto Compatible;
    // CP_A_C;
    // IF_Z goto Compatible;
    if(e == b || e == c)
        return true;

// Incompatible:
    // AND_A_A;
    // RET;
    return false;

// Compatible:
    // SCF;
    // RET;
}

static bool CheckBreedmonCompatibility_CheckDVs(void){
//  If Defense DVs match and the lower 3 bits of the Special DVs match,
//  avoid breeding
    // LD_A_addr(wBreedMon1DVs);
    // AND_A(0b1111);
    // LD_B_A;
    // LD_A_addr(wBreedMon2DVs);
    // AND_A(0b1111);
    // CP_A_B;
    // RET_NZ ;
    if((gPokemon.breedMon1.DVs & 0b1111) != (gPokemon.breedMon2.DVs & 0b1111))
        return true;
    // LD_A_addr(wBreedMon1DVs + 1);
    // AND_A(0b111);
    // LD_B_A;
    // LD_A_addr(wBreedMon2DVs + 1);
    // AND_A(0b111);
    // CP_A_B;
    // RET;
    return ((gPokemon.breedMon1.DVs >> 8) & 0b111) != ((gPokemon.breedMon2.DVs >> 8) & 0b111);
}

uint8_t CheckBreedmonCompatibility(void){
    // CALL(aCheckBreedmonCompatibility_CheckBreedingGroupCompatibility);
    bool compatible = CheckBreedmonCompatibility_CheckBreedingGroupCompatibility();
    // LD_C(0x0);
    // JP_NC (mCheckBreedmonCompatibility_done);
    if(!compatible) {
        wram->wBreedingCompatibility = 0x0;
        return wram->wBreedingCompatibility;
    }
    // LD_A_addr(wBreedMon1Species);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = gPokemon.breedMon1.species;
    // LD_A_addr(wBreedMon1DVs);
    // LD_addr_A(wTempMonDVs);
    wram->wTempMon.mon.DVs = gPokemon.breedMon1.DVs;
    // LD_A_addr(wBreedMon1DVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    // LD_A(TEMPMON);
    // LD_addr_A(wMonType);
    // PREDEF(pGetGender);
    u8_flag_s gender = GetGender(TEMPMON);
    // IF_C goto genderless;
    if(gender.flag)
        goto genderless;
    // LD_B(0x1);
    // IF_NZ goto breedmon2;
    // INC_B;
    uint8_t b = (gender.a != 0)? 0x1: 0x2;

// breedmon2:
    // PUSH_BC;
    // LD_A_addr(wBreedMon2Species);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = gPokemon.breedMon2.species;
    // LD_A_addr(wBreedMon2DVs);
    // LD_addr_A(wTempMonDVs);
    wram->wTempMon.mon.DVs = gPokemon.breedMon2.DVs;
    // LD_A_addr(wBreedMon2DVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    // LD_A(TEMPMON);
    // LD_addr_A(wMonType);
    // PREDEF(pGetGender);
    u8_flag_s gender2 = GetGender(TEMPMON);
    // POP_BC;
    // IF_C goto genderless;
    if(gender2.flag)
        goto genderless;
    // LD_A(0x1);
    // IF_NZ goto compare_gender;
    // INC_A;
    uint8_t a = (gender2.a != 0)? 0x1: 0x2;

// compare_gender:
    // CP_A_B;
    // IF_NZ goto compute;
    if(a == b) {
    genderless:
        // LD_C(0x0);
        // LD_A_addr(wBreedMon1Species);
        // CP_A(DITTO);
        // IF_Z goto ditto1;
        if(gPokemon.breedMon1.species == DITTO) {
        // ditto1:
            // LD_A_addr(wBreedMon2Species);
            // CP_A(DITTO);
            // IF_Z goto done;
            if(gPokemon.breedMon2.species == DITTO) {
                wram->wBreedingCompatibility = 0x0;
                return wram->wBreedingCompatibility;
            }
        }
        else {
            // LD_A_addr(wBreedMon2Species);
            // CP_A(DITTO);
            // IF_NZ goto done;
            if(gPokemon.breedMon2.species != DITTO) {
                wram->wBreedingCompatibility = 0x0;
                return wram->wBreedingCompatibility;
            }
            // goto compute;
        }
    }

// compute:
    // CALL(aCheckBreedmonCompatibility_CheckDVs);
    // LD_C(255);
    // JP_Z (mCheckBreedmonCompatibility_done);
    if(!CheckBreedmonCompatibility_CheckDVs()) {
        wram->wBreedingCompatibility = 255;
        return wram->wBreedingCompatibility;
    }
    // LD_A_addr(wBreedMon2Species);
    // LD_B_A;
    // LD_A_addr(wBreedMon1Species);
    // CP_A_B;
    // LD_C(254);
    // IF_Z goto compare_ids;
    // LD_C(128);
    uint8_t c = (gPokemon.breedMon2.species == gPokemon.breedMon1.species)? 254: 128;

// compare_ids:
// Speed up
    // LD_A_addr(wBreedMon1ID);
    // LD_B_A;
    // LD_A_addr(wBreedMon2ID);
    // CP_A_B;
    // IF_NZ goto done;
    // LD_A_addr(wBreedMon1ID + 1);
    // LD_B_A;
    // LD_A_addr(wBreedMon2ID + 1);
    // CP_A_B;
    // IF_NZ goto done;
    if(gPokemon.breedMon1.id == gPokemon.breedMon2.id) {
        // LD_A_C;
        // SUB_A(77);
        // LD_C_A;
        c -= 77;
    }

// done:
    // LD_A_C;
    // LD_addr_A(wBreedingCompatibility);
    wram->wBreedingCompatibility = c;
    // RET;
    return wram->wBreedingCompatibility;
}

bool DoEggStep(void){
    // LD_DE(wPartySpecies);
    species_t* de = gPokemon.partySpecies;
    // LD_HL(wPartyMon1Happiness);
    struct PartyMon* hl = gPokemon.partyMon;
    // LD_C(0);

    while(1) {
    // loop:
        // LD_A_de;
        // INC_DE;
        species_t a = *(de++);
        // CP_A(-1);
        // RET_Z ;
        if(a == (species_t)-1)
            return false;
        // CP_A(EGG);
        // IF_NZ goto next;
        if(a == EGG) {
            // DEC_hl;
            // IF_NZ goto next;
            if(--hl->mon.happiness == 0) {
                // LD_A(1);
                // AND_A_A;
                // RET;
                return true;
            }
        }

    // next:
        // PUSH_DE;
        // LD_DE(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_DE;
        hl++;
        // POP_DE;
        // goto loop;
    }
}

void OverworldHatchEgg(void){
    // CALL(aRefreshScreen);
    RefreshScreen();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aHatchEggs);
    HatchEggs();
    // CALL(aExitAllMenus);
    ExitAllMenus();
    // CALL(aRestartMapMusic);
    RestartMapMusic();
    // JP(mCloseText);
    CloseText();
}

static void Text_HatchEgg_Function(struct TextCmdState* state);
static const txt_cmd_s Text_HatchEgg[] = {
// Huh? @ @
    text_far(v_Text_BreedHuh)
    text_asm(Text_HatchEgg_Function)
};

static void Text_HatchEgg_Function(struct TextCmdState* state) {
    static const txt_cmd_s BreedClearboxText[] = {
        text_far(v_BreedClearboxText)
        text_end
    };
    static const txt_cmd_s BreedEggHatchText[] = {
        text_far(v_BreedEggHatchText)
        text_end
    };
    // LD_HL(wVramState);
    // RES_hl(0);
    bit_reset(wram->wVramState, 0);
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wCurPartySpecies);
    // PUSH_AF;
    // CALL(aEggHatch_AnimationSequence);
    EggHatch_AnimationSequence();
    // LD_HL(mHatchEggs_BreedClearboxText);
    // CALL(aPrintText);
    PrintText(BreedClearboxText);
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // LD_HL(mHatchEggs_BreedEggHatchText);
    state->hl = BreedEggHatchText;
    // RET;
}

void HatchEggs(void){
    static const txt_cmd_s BreedAskNicknameText[] = {
        text_far(v_BreedAskNicknameText)
        text_end
    };

    // LD_DE(wPartySpecies);
    species_t* de = gPokemon.partySpecies;
    // LD_HL(wPartyMon1Happiness);
    struct PartyMon* hl = gPokemon.partyMon;
    // XOR_A_A;
    // LD_addr_A(wCurPartyMon);
    uint8_t mon = 0;

    while(*de != (species_t)-1) {
    // loop:
        // LD_A_de;
        // INC_DE;
        // CP_A(-1);
        // JP_Z (mHatchEggs_done);
        species_t species = *(de++);
        // PUSH_DE;
        // PUSH_HL;
        // CP_A(EGG);
        // JP_NZ (mHatchEggs_next);
        // LD_A_hl;
        // AND_A_A;
        // JP_NZ (mHatchEggs_next);
        if(species == EGG && hl->mon.happiness == 0) {
            // LD_hl(0x78);
            hl->mon.happiness = 0x78;

            // PUSH_DE;

            // FARCALL(aSetEggMonCaughtData);
            SetEggMonCaughtData(mon);
            // FARCALL(aStubbedTrainerRankings_EggsHatched);
            StubbedTrainerRankings_EggsHatched();
            // LD_A_addr(wCurPartyMon);
            // LD_HL(wPartyMon1Species);
            species_t partySpecies = hl->mon.species;
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // CALL(aAddNTimes);
            // LD_A_hl;
            // LD_addr_A(wCurPartySpecies);
            wram->wCurPartySpecies = partySpecies;
            wram->wCurPartyMon = mon;
            // DEC_A;
            // CALL(aSetSeenAndCaughtMon);
            SetSeenAndCaughtMon(partySpecies - 1);

            // LD_A_addr(wCurPartySpecies);
            // CP_A(TOGEPI);
            // IF_NZ goto nottogepi;
            if(partySpecies == TOGEPI) {
            // set the event flag for hatching togepi
                // LD_DE(EVENT_TOGEPI_HATCHED);
                // LD_B(SET_FLAG);
                // CALL(aEventFlagAction);
                EventFlagAction(EVENT_TOGEPI_HATCHED, SET_FLAG);
            }

        // nottogepi:
            // POP_DE;

            // LD_A_addr(wCurPartySpecies);
            // DEC_DE;
            --de;
            // LD_de_A;
            *de = partySpecies;
            de++;
            // LD_addr_A(wNamedObjectIndex);
            // LD_addr_A(wCurSpecies);
            // CALL(aGetPokemonName);
            GetPokemonName(partySpecies);
            // XOR_A_A;
            // LD_addr_A(wUnusedEggHatchFlag);
            wram->wUnusedEggHatchFlag = 0;
            // CALL(aGetBaseData);
            GetBaseData(partySpecies);
            // LD_A_addr(wCurPartyMon);
            // LD_HL(wPartyMon1);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // CALL(aAddNTimes);
            // PUSH_HL;
            // LD_BC(MON_MAXHP);
            // ADD_HL_BC;
            // LD_D_H;
            // LD_E_L;
            // POP_HL;
            // PUSH_HL;
            // LD_BC(MON_LEVEL);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_addr_A(wCurPartyLevel);
            wram->wCurPartyLevel = hl->mon.level;
            // POP_HL;
            // PUSH_HL;
            // LD_BC(MON_STATUS);
            // ADD_HL_BC;
            // XOR_A_A;
            // LD_hli_A;
            // LD_hl_A;
            hl->status = 0;
            hl->unused = 0;
            // POP_HL;
            // PUSH_HL;
            // LD_BC(MON_STAT_EXP - 1);
            // ADD_HL_BC;
            // LD_B(FALSE);
            // PREDEF(pCalcMonStats);
            CalcMonStats_PartyMon(hl, FALSE);
            // POP_BC;
            // LD_HL(MON_MAXHP);
            // ADD_HL_BC;
            // LD_D_H;
            // LD_E_L;
            // LD_HL(MON_HP);
            // ADD_HL_BC;
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            // LD_A_de;
            // LD_hl_A;
            hl->HP = hl->maxHP;
            // LD_HL(MON_ID);
            // ADD_HL_BC;
            // LD_A_addr(wPlayerID);
            // LD_hli_A;
            // LD_A_addr(wPlayerID + 1);
            // LD_hl_A;
            hl->mon.id = gPlayer.playerID;
            // LD_A_addr(wCurPartyMon);
            // LD_HL(wPartyMonOTs);
            // LD_BC(NAME_LENGTH);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // LD_HL(wPlayerName);
            // CALL(aCopyBytes);
            CopyBytes(gPokemon.partyMonOT[mon], gPlayer.playerName, NAME_LENGTH);
            // LD_HL(mHatchEggs_Text_HatchEgg);
            // CALL(aPrintText);
            PrintText(Text_HatchEgg);
            // LD_A_addr(wCurPartyMon);
            // LD_HL(wPartyMonNicknames);
            // LD_BC(MON_NAME_LENGTH);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // PUSH_DE;
            // LD_HL(mHatchEggs_BreedAskNicknameText);
            // CALL(aPrintText);
            PrintText(BreedAskNicknameText);
            // CALL(aYesNoBox);
            // POP_DE;
            // IF_C goto nonickname;

            if(YesNoBox()) {
                // LD_A(TRUE);
                // LD_addr_A(wUnusedEggHatchFlag);
                // XOR_A_A;
                // LD_addr_A(wMonType);
                wram->wMonType = 0;
                // PUSH_DE;
                // LD_B(NAME_MON);
                // FARCALL(aNamingScreen);
                NamingScreen(gPokemon.partyMonNickname[mon], NAME_MON);
                // POP_HL;
                // LD_DE(wStringBuffer1);
                // CALL(aInitName);
                InitName(gPokemon.partyMonNickname[mon], wram->wStringBuffer1);
                // goto next;
            }
            else {
            // nonickname:
                // LD_HL(wStringBuffer1);
                // LD_BC(MON_NAME_LENGTH);
                // CALL(aCopyBytes);
                CopyBytes(gPokemon.partyMonNickname[mon], wram->wStringBuffer1, MON_NAME_LENGTH);
            }
        }

    // next:
        // LD_HL(wCurPartyMon);
        // INC_hl;
        mon++;
        // POP_HL;
        // LD_DE(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_DE;
        hl++;
        // POP_DE;
        // JP(mHatchEggs_loop);
    }

// done:
    // RET;
}

void InitEggMoves(void){
    // CALL(aGetHeritableMoves);
    // LD_D_H;
    // LD_E_L;
    const move_t* de = GetHeritableMoves();
    // LD_B(NUM_MOVES);
    uint8_t b = NUM_MOVES;

    do {
    // loop:
        // LD_A_de;
        // AND_A_A;
        // IF_Z goto done;
        if(*de == NO_MOVE)
            break;
        // LD_HL(wEggMonMoves);
        move_t* hl = gPokemon.eggMon.moves;
        // LD_C(NUM_MOVES);
        uint8_t c = NUM_MOVES;

        do {
        // next:
            // LD_A_de;
            // CP_A_hl;
            // IF_Z goto skip;
            if(*de == *hl)
                goto skip;
            // INC_HL;
            // DEC_C;
            // IF_NZ goto next;
        } while(hl++, --c != 0);
        // CALL(aGetEggMove);
        // IF_NC goto skip;
        if(GetEggMove(de)) {
            // CALL(aLoadEggMove);
            LoadEggMove(de);
        }

    skip:;
        // INC_DE;
        // DEC_B;
        // IF_NZ goto loop;
    } while(de++, --b != 0);


// done:
    // RET;
}

static bool GetEggMove(const move_t* de){
    // PUSH_BC;
    // LD_A_addr(wEggMonSpecies);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mEggMovePointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A(BANK(aEggMovePointers));
    // CALL(aGetFarWord);
    const move_t* hl2 = EggMovePointers[gPokemon.eggMon.species - 1];

    while(*hl2 != (move_t)-1) {
    // loop:
        // LD_A(BANK(aBulbasaurEggMoves)); // LD_A(BANK("Egg Moves"));
        // CALL(aGetFarByte);
        // CP_A(-1);
        // IF_Z goto reached_end;
        // LD_B_A;
        // LD_A_de;
        // CP_A_B;
        // IF_Z goto done_carry;
        if(*de == *hl2) {
            return true;
        }
        // INC_HL;
        hl2++;
        // goto loop;
    }

// reached_end:
    // CALL(aGetBreedmonMovePointer);
    move_t* hl = GetBreedmonMovePointer();
    // LD_B(NUM_MOVES);
    uint8_t b = NUM_MOVES;

    while(*de != *hl) {
    // loop2:
        // LD_A_de;
        // CP_A_hl;
        // IF_Z goto found_eggmove;
        // INC_HL;
        hl++;
        // DEC_B;
        // IF_Z goto inherit_tmhm;
        if(--b == 0)
            goto inherit_tmhm;
        // goto loop2;
    }

// found_eggmove:
    // LD_A_addr(wEggMonSpecies);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mEvosAttacksPointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A(BANK(aEvosAttacksPointers));
    // CALL(aGetFarWord);
    const struct EvoMoves* evoAttacks = EvosAttacksPointers[gPokemon.eggMon.species - 1];
    const struct LevelMove* mvs = evoAttacks->learnset;

// loop3:
    // LD_A(BANK(aBulbasaurEvosAttacks)); // LD_A(BANK("Evolutions and Attacks"));
    // CALL(aGetFarByte);
    // INC_HL;
    // AND_A_A;
    // IF_NZ goto loop3;

    while(1) {
    // loop4:
        // LD_A(BANK(aBulbasaurEvosAttacks)); // LD_A(BANK("Evolutions and Attacks"));
        // CALL(aGetFarByte);
        // AND_A_A;
        // IF_Z goto inherit_tmhm;
        if(mvs->level == 0xff)
            break;
        // INC_HL;
        // LD_A(BANK(aBulbasaurEvosAttacks)); // LD_A(BANK("Evolutions and Attacks"));
        // CALL(aGetFarByte);
        // LD_B_A;
        // LD_A_de;
        // CP_A_B;
        // IF_Z goto done_carry;
        if(mvs->move == *de) {
            return true;
        }
        // INC_HL;
        mvs++;
        // goto loop4;
    }

    const move_t* tmhm = TMHMMoves;

inherit_tmhm:
    // LD_HL(mTMHMMoves);
    //const move_t* tmhm = TMHMMoves;

    do {
    // loop5:
        // LD_A(BANK(aTMHMMoves));
        // CALL(aGetFarByte);
        // INC_HL;
        // AND_A_A;
        // IF_Z goto done;
        if(*tmhm == NO_MOVE)
            return false;
        // LD_B_A;
        // LD_A_de;
        // CP_A_B;
        // IF_NZ goto loop5;
    } while(*tmhm != *de);
    // LD_addr_A(wPutativeTMHMMove);
    // PREDEF(pCanLearnTMHMMove);
    uint8_t c = CanLearnTMHMMove(wram->wCurPartySpecies, *de);
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto done;
    if(c == 0)
        return false;

// done_carry:
    // POP_BC;
    // SCF;
    // RET;
    return true;

// done:
    // POP_BC;
    // AND_A_A;
    // RET;
}

static void LoadEggMove(const move_t* de2){
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_de;
    // LD_B_A;
    move_t b = *de2;
    // LD_HL(wEggMonMoves);
    move_t* hl = gPokemon.eggMon.moves;
    // LD_C(NUM_MOVES);
    uint8_t c = NUM_MOVES;

    do {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto done;
        if(*(hl++) == NO_MOVE)
            goto done;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_DE(wEggMonMoves);
    move_t* de = gPokemon.eggMon.moves;
    // LD_HL(wEggMonMoves + 1);
    hl = gPokemon.eggMon.moves + 1;
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    *(de++) = *(hl++);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    *(de++) = *(hl++);
    // LD_A_hli;
    // LD_de_A;
    *de = *(hl++);

done:
    // DEC_HL;
    --hl;
    // LD_hl_B;
    *hl = b;
    // LD_HL(wEggMonMoves);
    // LD_DE(wEggMonPP);
    // PREDEF(pFillPP);
    FillPP(gPokemon.eggMon.PP, gPokemon.eggMon.moves);
    // POP_BC;
    // POP_DE;
    // RET;
}

static const move_t* GetHeritableMoves(void){
    // LD_HL(wBreedMon2Moves);
    move_t* hl = gPokemon.breedMon2.moves;
    // LD_A_addr(wBreedMon1Species);
    species_t sp = wram->wCurPartySpecies;
    // CP_A(DITTO);
    // IF_Z goto ditto1;
    if(gPokemon.breedMon1.species == DITTO) {
    // ditto1:
        // LD_A_addr(wCurPartySpecies);
        // PUSH_AF;
        // LD_A_addr(wBreedMon2Species);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = gPokemon.breedMon2.species;
        // LD_A_addr(wBreedMon2DVs);
        // LD_addr_A(wTempMonDVs);
        // LD_A_addr(wBreedMon2DVs + 1);
        // LD_addr_A(wTempMonDVs + 1);
        wram->wTempMon.mon.DVs = gPokemon.breedMon2.DVs;
        // LD_A(TEMPMON);
        // LD_addr_A(wMonType);
        // PREDEF(pGetGender);
        u8_flag_s gender = GetGender(TEMPMON);
        // IF_C goto inherit_mon2_moves;
        // IF_NZ goto inherit_mon2_moves;
        if(gender.flag || gender.a != 0) {
        // inherit_mon2_moves:
            // LD_HL(wBreedMon2Moves);
            // POP_AF;
            // LD_addr_A(wCurPartySpecies);
            wram->wCurPartySpecies = sp;
            // RET;
            return gPokemon.breedMon2.moves;
        }
    // inherit_mon1_moves:
        // LD_HL(wBreedMon1Moves);
        // POP_AF;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = sp;
        // RET;
        return gPokemon.breedMon1.moves;
    }
    // LD_A_addr(wBreedMon2Species);
    // CP_A(DITTO);
    // IF_Z goto ditto2;
    else if(gPokemon.breedMon1.species == DITTO) {
    // ditto2:
        // LD_A_addr(wCurPartySpecies);
        // PUSH_AF;
        // LD_A_addr(wBreedMon1Species);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = gPokemon.breedMon1.species;
        // LD_A_addr(wBreedMon1DVs);
        // LD_addr_A(wTempMonDVs);
        // LD_A_addr(wBreedMon1DVs + 1);
        // LD_addr_A(wTempMonDVs + 1);
        wram->wTempMon.mon.DVs = gPokemon.breedMon1.DVs;
        // LD_A(TEMPMON);
        // LD_addr_A(wMonType);
        // PREDEF(pGetGender);
        u8_flag_s gender = GetGender(TEMPMON);
        // IF_C goto inherit_mon1_moves;
        // IF_NZ goto inherit_mon1_moves;
        if(gender.flag || gender.a != 0) {
        // inherit_mon1_moves:
            // LD_HL(wBreedMon1Moves);
            // POP_AF;
            // LD_addr_A(wCurPartySpecies);
            wram->wCurPartySpecies = sp;
            // RET;
            return gPokemon.breedMon1.moves;
        }
    // inherit_mon2_moves:
        // LD_HL(wBreedMon2Moves);
        // POP_AF;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = sp;
        // RET;
        return gPokemon.breedMon2.moves;
    }
    // LD_A_addr(wBreedMotherOrNonDitto);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.breedMotherOrNonDitto == 0)
        return hl;
    // LD_HL(wBreedMon1Moves);
    // RET;
    return gPokemon.breedMon1.moves;
}

static move_t* GetBreedmonMovePointer(void){
    // LD_HL(wBreedMon1Moves);
    // LD_A_addr(wBreedMon1Species);
    // CP_A(DITTO);
    // RET_Z ;
    if(gPokemon.breedMon1.species == DITTO)
        return gPokemon.breedMon1.moves;
    // LD_A_addr(wBreedMon2Species);
    // CP_A(DITTO);
    // IF_Z goto ditto;
    // LD_A_addr(wBreedMotherOrNonDitto);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.breedMon2.species != DITTO && gPokemon.breedMotherOrNonDitto == 0)
        return gPokemon.breedMon1.moves;

// ditto:
    // LD_HL(wBreedMon2Moves);
    // RET;
    return gPokemon.breedMon2.moves;
}

void GetEggFrontpic(tile_t* de, species_t a){
    // PUSH_DE;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = a;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = a;
    // CALL(aGetBaseData);
    GetBaseData(a);
    // LD_HL(wBattleMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter(wram->wBattleMon.dvs);
    // POP_DE;
    // PREDEF_JUMP(pGetMonFrontpic);
    GetMonFrontpic(de);
}

void GetHatchlingFrontpic(tile_t* de, species_t a){
    // PUSH_DE;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = a;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = a;
    // CALL(aGetBaseData);
    GetBaseData(a);
    // LD_HL(wBattleMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter(wram->wBattleMon.dvs);
    // POP_DE;
    // PREDEF_JUMP(pGetAnimatedFrontpic);
    GetAnimatedFrontpic(de, 0);
}

void Hatch_UpdateFrontpicBGMapCenter(tile_t* hl, uint8_t b, uint8_t c, uint8_t a){
    // PUSH_AF;
    // CALL(aWaitTop);
    WaitTop();
    // PUSH_HL;
    // PUSH_BC;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x7f);
    // POP_BC;
    // POP_HL;
    // LD_A_B;
    // LDH_addr_A(hBGMapAddress + 1);
    hram.hBGMapAddress = (b << 8) | (hram.hBGMapAddress & 0xff);
    // LD_A_C;
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = c;
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(hl, 7, 7);
    // POP_AF;
    // CALL(aHatch_LoadFrontpicPal);
    Hatch_LoadFrontpicPal(a);
    // CALL(aSetPalettes);
    SetPalettes();
    // JP(mWaitBGMap);
    WaitBGMap();
}

void EggHatch_DoAnimFrame(void){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALLFAR(aPlaySpriteAnimations);
    PlaySpriteAnimations();
    // CALL(aDelayFrame);
    DelayFrame();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

static const char EggHatchGFX[] = "gfx/evo/egg_hatch.png";

void EggHatch_AnimationSequence(void){
    // LD_A_addr(wNamedObjectIndex);
    // LD_addr_A(wJumptableIndex);
    species_t species = wram->wCurPartySpecies;
    // LD_A_addr(wCurSpecies);
    // PUSH_AF;
    species_t curSpecies = wram->wCurSpecies;
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);
    // FARCALL(aBlankScreen);
    BlankScreen();
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(mEggHatchGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // LD_BC(2 * LEN_2BPP_TILE);
    // LD_A(BANK(aEggHatchGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, EggHatchGFX, 0, 2);
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_A_addr(wJumptableIndex);
    // CALL(aGetHatchlingFrontpic);
    GetHatchlingFrontpic(vram->vTiles2 + LEN_2BPP_TILE * 0x00, species);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_A(EGG);
    // CALL(aGetEggFrontpic);
    GetEggFrontpic(vram->vTiles2 + LEN_2BPP_TILE * 0x31, EGG);
    // LD_DE(MUSIC_EVOLUTION);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_EVOLUTION);
    // CALL(aEnableLCD);
    EnableLCD();
    // hlcoord(7, 4, wTilemap);
    // LD_B(HIGH(vBGMap0));
    // LD_C(0x31);  // Egg tiles start here
    // LD_A(EGG);
    // CALL(aHatch_UpdateFrontpicBGMapCenter);
    Hatch_UpdateFrontpicBGMapCenter(coord(7, 4, wram->wTilemap), HIGH(vBGMap0), 0x31, EGG);
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // XOR_A_A;
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 0;
    // LDH_A_addr(hSCX);
    // LD_B_A;

    while(1) {
    // outerloop:
        // LD_HL(wFrameCounter);
        // LD_A_hl;
        uint8_t frames = wram->wFrameCounter;
        // INC_hl;
        wram->wFrameCounter++;
        // CP_A(8);
        // IF_NC goto done;
        if(frames >= 8)
            break;
        // LD_E_hl;
        uint8_t e = wram->wFrameCounter;

        do {
        // loop:
        //  wobble e times
            // LD_A(2);
            // LDH_addr_A(hSCX);
            hram.hSCX = 2;
            // LD_A(-2);
            // LD_addr_A(wGlobalAnimXOffset);
            wram->wGlobalAnimXOffset = (uint8_t)-2;
            // CALL(aEggHatch_DoAnimFrame);
            EggHatch_DoAnimFrame();
            // LD_C(2);
            // CALL(aDelayFrames);
            DelayFrames(2);
            // LD_A(-2);
            // LDH_addr_A(hSCX);
            hram.hSCX = (uint8_t)-2;
            // LD_A(2);
            // LD_addr_A(wGlobalAnimXOffset);
            wram->wGlobalAnimXOffset = 2;
            // CALL(aEggHatch_DoAnimFrame);
            EggHatch_DoAnimFrame();
            // LD_C(2);
            // CALL(aDelayFrames);
            DelayFrames(2);
            // DEC_E;
            // IF_NZ goto loop;
        } while(--e != 0);
        // LD_C(16);
        // CALL(aDelayFrames);
        DelayFrames(16);
        // CALL(aEggHatch_CrackShell);
        EggHatch_CrackShell();
        // goto outerloop;
    }

// done:
    // LD_DE(SFX_EGG_HATCH);
    // CALL(aPlaySFX);
    PlaySFX(SFX_EGG_HATCH);
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0;
    // LD_addr_A(wGlobalAnimXOffset);
    wram->wGlobalAnimXOffset = 0;
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aHatch_InitShellFragments);
    Hatch_InitShellFragments();
    // hlcoord(6, 3, wTilemap);
    // LD_B(HIGH(vBGMap0));
    // LD_C(0x00);  // Hatchling tiles start here
    // LD_A_addr(wJumptableIndex);
    // CALL(aHatch_UpdateFrontpicBGMapCenter);
    Hatch_UpdateFrontpicBGMapCenter(coord(6, 3, wram->wTilemap), HIGH(vBGMap0), 0x00, species);
    // CALL(aHatch_ShellFragmentLoop);
    Hatch_ShellFragmentLoop();
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_A_addr(wJumptableIndex);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // hlcoord(6, 3, wTilemap);
    // LD_D(0x0);
    // LD_E(ANIM_MON_HATCH);
    // PREDEF(pAnimateFrontpic);
    AnimateFrontpic(coord(6, 3, wram->wTilemap), 0x0, ANIM_MON_HATCH);
    // POP_AF;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = curSpecies;
    // RET;
}

void Hatch_LoadFrontpicPal(uint8_t a){
    // LD_addr_A(wPlayerHPPal);
    wram->wPlayerHPPal = a;
    // LD_B(SCGB_EVOLUTION);
    // LD_C(0x0);
    // JP(mGetSGBLayout);
    return GetSGBLayout(SCGB_EVOLUTION);
}

void EggHatch_CrackShell(void){
    // LD_A_addr(wFrameCounter);
    // DEC_A;
    uint8_t a = (wram->wFrameCounter - 1) & 0x7;
    // AND_A(0x7);
    // CP_A(0x7);
    // RET_Z ;
    if(a == 0x7)
        return;
    // SRL_A;
    // RET_NC ;
    if((a & 1) == 0)
        return;
    a >>= 1;
    // SWAP_A;
    a = (a >> 4) | (a << 4);
    // SRL_A;
    // ADD_A(9 * 8 + 4);
    // LD_D_A;
    uint16_t de = ((uint16_t)((a >> 1) + 9 * 8 + 4) << 8) | (11 * 8);
    // LD_E(11 * 8);
    // LD_A(SPRITE_ANIM_INDEX_EGG_CRACK);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_EGG_CRACK, de);
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->tileID = 0x0;
    // LD_DE(SFX_EGG_CRACK);
    // JP(mPlaySFX);
    PlaySFX(SFX_EGG_CRACK);
}

void Hatch_InitShellFragments(void){
    // shell_fragment: MACRO
    // ; y tile, y pxl, x tile, x pxl, frameset offset, ???
    //     db (\1 * 8) % $100 + \2, (\3 * 8) % $100 + \4, \5 - SPRITE_ANIM_FRAMESET_EGG_HATCH_1, \6
    // ENDM
    #define shell_fragment(_yt, _yp, _xt, _xp, _fo, _unk) (_yt * 8) % 0x100 + _yp, (_xt * 8) % 0x100 + _xp, _fo - SPRITE_ANIM_FRAMESET_EGG_HATCH_1, _unk

    static const uint8_t SpriteData[] = {
        shell_fragment(10, 4,  9, 0, SPRITE_ANIM_FRAMESET_EGG_HATCH_1, 0x3c),
        shell_fragment(11, 4,  9, 0, SPRITE_ANIM_FRAMESET_EGG_HATCH_2, 0x04),
        shell_fragment(10, 4, 10, 0, SPRITE_ANIM_FRAMESET_EGG_HATCH_1, 0x30),
        shell_fragment(11, 4, 10, 0, SPRITE_ANIM_FRAMESET_EGG_HATCH_2, 0x10),
        shell_fragment(10, 4, 11, 0, SPRITE_ANIM_FRAMESET_EGG_HATCH_3, 0x24),
        shell_fragment(11, 4, 11, 0, SPRITE_ANIM_FRAMESET_EGG_HATCH_4, 0x1c),
        shell_fragment(10, 0,  9, 4, SPRITE_ANIM_FRAMESET_EGG_HATCH_1, 0x36),
        shell_fragment(12, 0,  9, 4, SPRITE_ANIM_FRAMESET_EGG_HATCH_2, 0x0a),
        shell_fragment(10, 0, 10, 4, SPRITE_ANIM_FRAMESET_EGG_HATCH_3, 0x2a),
        shell_fragment(12, 0, 10, 4, SPRITE_ANIM_FRAMESET_EGG_HATCH_4, 0x16),
        -1,
    };
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // LD_HL(mHatch_InitShellFragments_SpriteData);
    const uint8_t* hl = SpriteData;

    while(*hl != (uint8_t)-1) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto done;
        // LD_E_A;
        uint8_t e = *(hl++);
        // LD_A_hli;
        // LD_D_A;
        uint8_t d = *(hl++);
        // LD_A_hli;
        // LD_C_A;
        uint8_t c = *(hl++);
        // LD_A_hli;
        // LD_B_A;
        uint8_t b = *(hl++);
        // PUSH_HL;
        // PUSH_BC;

        // LD_A(SPRITE_ANIM_INDEX_EGG_HATCH);
        // CALL(aInitSpriteAnimStruct);
        struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_EGG_HATCH, (d << 8) | e);

        // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->tileID = 0x0;

        // POP_DE;
        // LD_A_E;
        // LD_HL(SPRITEANIMSTRUCT_FRAMESET_ID);
        // ADD_HL_BC;
        // ADD_A_hl;
        // LD_hl_A;
        bc->framesetID += c;

        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // LD_hl_D;
        bc->jumptableIndex = b;

        // POP_HL;
        // goto loop;
    }

// done:
    // LD_DE(SFX_EGG_HATCH);
    // CALL(aPlaySFX);
    PlaySFX(SFX_EGG_HATCH);
    // CALL(aEggHatch_DoAnimFrame);
    EggHatch_DoAnimFrame();
    // RET;
}

void Hatch_ShellFragmentLoop(void){
    // LD_C(129);
    uint8_t c = 129;

    do {
    // loop:
        // CALL(aEggHatch_DoAnimFrame);
        EggHatch_DoAnimFrame();
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;

}

void DayCareMon1(void){
    // LD_HL(mLeftWithDayCareManText);
    // CALL(aPrintText);
    PrintText(LeftWithDayCareManText);
    // LD_A_addr(wBreedMon1Species);
    // CALL(aPlayMonCry);
    PlayMonCry(gPokemon.breedMon1.species);
    // LD_A_addr(wDayCareLady);
    // BIT_A(DAYCARELADY_HAS_MON_F);
    // JR_Z (mDayCareMonCursor);
    if(!bit_test(gPokemon.dayCareLady, DAYCARELADY_HAS_MON_F))
        return DayCareMonCursor();
    // CALL(aPromptButton);
    PromptButton();
    // LD_HL(wBreedMon2Nickname);
    // CALL(aDayCareMonCompatibilityText);
    // JP(mPrintText);
    PrintText(DayCareMonCompatibilityText(gPokemon.breedMon2Nickname));
}

void DayCareMon2(void){
    // LD_HL(mLeftWithDayCareLadyText);
    // CALL(aPrintText);
    PrintText(LeftWithDayCareLadyText);
    // LD_A_addr(wBreedMon2Species);
    // CALL(aPlayMonCry);
    PlayMonCry(gPokemon.breedMon1.species);
    // LD_A_addr(wDayCareMan);
    // BIT_A(DAYCAREMAN_HAS_MON_F);
    // JR_Z (mDayCareMonCursor);
    if(!bit_test(gPokemon.dayCareMan, DAYCARELADY_HAS_MON_F))
        return DayCareMonCursor();
    // CALL(aPromptButton);
    PromptButton();
    // LD_HL(wBreedMon1Nickname);
    // CALL(aDayCareMonCompatibilityText);
    // JP(mPrintText);
    PrintText(DayCareMonCompatibilityText(gPokemon.breedMon1Nickname));
}

void DayCareMonCursor(void){
    // JP(mWaitPressAorB_BlinkCursor);
    return WaitPressAorB_BlinkCursor();
}

const txt_cmd_s LeftWithDayCareLadyText[] = {
    text_far(v_LeftWithDayCareLadyText)
    text_end
};

const txt_cmd_s LeftWithDayCareManText[] = {
    text_far(v_LeftWithDayCareManText)
    text_end
};

const txt_cmd_s* DayCareMonCompatibilityText(const uint8_t* nickname){
static const txt_cmd_s BreedBrimmingWithEnergyText[] = {
    text_far(v_BreedBrimmingWithEnergyText)
    text_end
};
static const txt_cmd_s BreedNoInterestText[] = {
    text_far(v_BreedNoInterestText)
    text_end
};
static const txt_cmd_s BreedAppearsToCareForText[] = {
    text_far(v_BreedAppearsToCareForText)
    text_end
};
static const txt_cmd_s BreedFriendlyText[] = {
    text_far(v_BreedFriendlyText)
    text_end
};
static const txt_cmd_s BreedShowsInterestText[] = {
    text_far(v_BreedShowsInterestText)
    text_end
};
    // PUSH_BC;
    // LD_DE(wStringBuffer1);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wStringBuffer1, nickname, NAME_LENGTH);
    // CALL(aCheckBreedmonCompatibility);
    uint8_t compat = CheckBreedmonCompatibility();
    // POP_BC;
    // LD_A_addr(wBreedingCompatibility);
    // LD_HL(mDayCareMonCompatibilityText_BreedBrimmingWithEnergyText);
    // CP_A(-1);
    // IF_Z goto done;
    if(compat == (uint8_t)-1)
        return BreedBrimmingWithEnergyText;
    // LD_HL(mDayCareMonCompatibilityText_BreedNoInterestText);
    // AND_A_A;
    // IF_Z goto done;
    if(compat == 0)
        return BreedNoInterestText;
    // LD_HL(mDayCareMonCompatibilityText_BreedAppearsToCareForText);
    // CP_A(230);
    // IF_NC goto done;
    if(compat >= 230)
        return BreedAppearsToCareForText;
    // CP_A(70);
    // LD_HL(mDayCareMonCompatibilityText_BreedFriendlyText);
    // IF_NC goto done;
    if(compat >= 70)
        return BreedFriendlyText;
    // LD_HL(mDayCareMonCompatibilityText_BreedShowsInterestText);

// done:
    // RET;
    return BreedShowsInterestText;
}

void DayCareMonPrintEmptyString(void){
//  //  unreferenced
    LD_HL(mDayCareMonPrintEmptyString_string);
    RET;


//string:
    //db ['"@"'];

}
