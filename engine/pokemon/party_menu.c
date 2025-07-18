#include "../../constants.h"
#include "party_menu.h"
#include "mon_stats.h"
#include "health.h"
#include "../../home/delay.h"
#include "../../home/audio.h"
#include "../../home/gfx.h"
#include "../../home/menu.h"
#include "../../home/copy.h"
#include "../../home/pokemon.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/print_text.h"
#include "../../home/sprite_updates.h"
#include "../../home/map.h"
#include "../items/tmhm2.h"
#include "../gfx/color.h"
#include "../gfx/sprites.h"
#include "../gfx/mon_icons.h"
#include "../../data/party_menu_qualities.h"
#include "../../data/text/common.h"
#include "../../data/pokemon/evos_attacks_pointers.h"

u8_flag_s SelectMonFromParty(void){
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // XOR_A_A;
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = 0;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aInitPartyMenuLayout);
    InitPartyMenuLayout();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aPartyMenuSelect);
    u8_flag_s res = PartyMenuSelect();
    // CALL(aReturnToMapWithSpeechTextbox);
    ReturnToMapWithSpeechTextbox();
    // RET;
    return res;
}

u8_flag_s SelectTradeOrDayCareMon(uint8_t b){
    // LD_A_B;
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = b;
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aInitPartyMenuLayout);
    InitPartyMenuLayout();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_B(SCGB_PARTY_MENU);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PARTY_MENU);
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aPartyMenuSelect);
    u8_flag_s res = PartyMenuSelect();
    // CALL(aReturnToMapWithSpeechTextbox);
    ReturnToMapWithSpeechTextbox();
    // RET;
    return res;
}

void InitPartyMenuLayout(void){
    // CALL(aLoadPartyMenuGFX);
    LoadPartyMenuGFX();
    // CALL(aInitPartyMenuWithCancel);
    InitPartyMenuWithCancel();
    // CALL(aInitPartyMenuGFX);
    InitPartyMenuGFX();
    // CALL(aWritePartyMenuTilemap);
    WritePartyMenuTilemap();
    // CALL(aPrintPartyMenuText);
    PrintPartyMenuText();
    // RET;
}

void LoadPartyMenuGFX(void){
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra();
    // CALLFAR(aInitPartyMenuPalettes);
    InitPartyMenuPalettes();
    // CALLFAR(aClearSpriteAnims2);
    ClearSpriteAnims2();
    // RET;
}

void WritePartyMenuTilemap(void){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = gOptions.options;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);  // blank the tilemap
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // CALL(aGetPartyMenuQualityIndexes);
    const uint8_t* hl = GetPartyMenuQualityIndexes();

    uint8_t a;
    while(a = *(hl++), a != 0xff) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto end;
        // PUSH_HL;
        // LD_HL(mWritePartyMenuTilemap_Jumptable);
        // RST(aJumpTable);
        switch(a) {
        //  entries correspond to PARTYMENUQUALITY_* constants
            case PARTYMENUQUALITY_NICKNAMES:        PlacePartyNicknames();                  break;
            case PARTYMENUQUALITY_HP_BAR:           PlacePartyHPBar();                      break;
            case PARTYMENUQUALITY_HP_DIGITS:        PlacePartyMenuHPDigits();               break;
            case PARTYMENUQUALITY_LEVEL:            PlacePartyMonLevel();                   break;
            case PARTYMENUQUALITY_STATUS:           PlacePartyMonStatus();                  break;
            case PARTYMENUQUALITY_TMHM_COMPAT:      PlacePartyMonTMHMCompatibility();       break;
            case PARTYMENUQUALITY_EVO_STONE_COMPAT: PlacePartyMonEvoStoneCompatibility();   break;
            case PARTYMENUQUALITY_GENDER:           PlacePartyMonGender();                  break;
            case PARTYMENUQUALITY_MOBILE_SELECTION: PlacePartyMonMobileBattleSelection();   break;
        }
        // POP_HL;
        // goto loop;
    }

// end:
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // RET;
    return;
}

void PlacePartyNicknames(void){
    // hlcoord(3, 1, wTilemap);
    tile_t* hl = coord(3, 1, wram->wTilemap);
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // IF_Z goto end;
    if(gPokemon.partyCount != 0) {
        // LD_C_A;
        uint8_t c = gPokemon.partyCount;
        // LD_B(0);
        uint8_t b = 0;

        do {
        // loop:
            // PUSH_BC;
            // PUSH_HL;
            // PUSH_HL;
            // LD_HL(wPartyMonNicknames);
            // LD_A_B;
            // CALL(aGetNickname);
            uint8_t* de = gPokemon.partyMonNickname[b];
            // POP_HL;
            // CALL(aPlaceString);
            PlaceStringSimple(de, hl);
            // POP_HL;
            // LD_DE(2 * SCREEN_WIDTH);
            // ADD_HL_DE;
            hl += 2 * SCREEN_WIDTH;
            // POP_BC;
            // INC_B;
            b++;
            // DEC_C;
            // IF_NZ goto loop;
        } while(--c != 0);
    }

// end:
    // DEC_HL;
    // DEC_HL;
    // LD_DE(mPlacePartyNicknames_CancelString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("CANCEL@"), hl - 2);
    // RET;
}

void PlacePartyHPBar(void){
    // XOR_A_A;
    // LD_addr_A(wSGBPals);
    wram->wSGBPals[0] = 0;
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // LD_B(0);
    uint8_t b = 0;
    // hlcoord(11, 2, wTilemap);
    tile_t* hl = coord(11, 2, wram->wTilemap);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aPartyMenuCheckEgg);
        // IF_Z goto skip;
        if(!PartyMenuCheckEgg(b)) {
            // PUSH_HL;
            // CALL(aPlacePartymonHPBar);
            uint8_t e = PlacePartymonHPBar(b);
            // POP_HL;
            // LD_D(0x6);
            // LD_B(0x0);
            // CALL(aDrawBattleHPBar);
            DrawBattleHPBar(hl, 0x6, e, 0x0, HIGH(gPokemon.partyMon[b].HP));
            // LD_HL(wHPPals);
            // LD_A_addr(wSGBPals);
            // LD_C_A;
            // LD_B(0);
            // ADD_HL_BC;
            // CALL(aSetHPPal);
            SetHPPal(wram->wHPPals + wram->wSGBPals[0], e);
            // LD_B(SCGB_PARTY_MENU_HP_BARS);
            // CALL(aGetSGBLayout);
            GetSGBLayout(SCGB_PARTY_MENU_HP_BARS);
        }
    // skip:
        // LD_HL(wSGBPals);
        // INC_hl;
        wram->wSGBPals[0]++;
        // POP_HL;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // INC_B;
        b++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_B(SCGB_PARTY_MENU);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PARTY_MENU);
    // RET;
}

uint8_t PlacePartymonHPBar(uint8_t b){
    // LD_A_B;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_HL(wPartyMon1HP);
    // CALL(aAddNTimes);
    // LD_A_hli;
    // OR_A_hl;
    // IF_NZ goto not_fainted;
    if(gPokemon.partyMon[b].HP == 0) {
        // XOR_A_A;
        // LD_E_A;
        // LD_C_A;
        // RET;
        return 0;
    }


// not_fainted:
    // DEC_HL;
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_C_A;
    uint16_t bc = BigEndianToNative16(gPokemon.partyMon[b].HP);
    // LD_A_hli;
    // LD_D_A;
    // LD_A_hli;
    // LD_E_A;
    uint16_t de = BigEndianToNative16(gPokemon.partyMon[b].maxHP);
    // PREDEF(pComputeHPBarPixels);
    return ComputeHPBarPixels(bc, de);
    // RET;
}

void PlacePartyMenuHPDigits(void){
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // LD_B(0);
    uint8_t b = 0;
    // hlcoord(13, 1, wTilemap);
    tile_t* hl = coord(13, 1, wram->wTilemap);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aPartyMenuCheckEgg);
        // IF_Z goto next;
        if(!PartyMenuCheckEgg(b)) {
            // PUSH_HL;
            // LD_A_B;
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // LD_HL(wPartyMon1HP);
            // CALL(aAddNTimes);
            // LD_E_L;
            // LD_D_H;
            uint16_t hp = gPokemon.partyMon[b].HP;
            // POP_HL;
            // PUSH_DE;
            // LD_BC((2 << 8) | 3);
            // CALL(aPrintNum);
            uint8_t* hl2 = PrintNum(hl, &hp, 2, 3);
            // POP_DE;
            // LD_A(0xf3);
            // LD_hli_A;
            *(hl2++) = 0xf3;
            // INC_DE;
            // INC_DE;
            uint16_t maxHP = gPokemon.partyMon[b].maxHP;
            // LD_BC((2 << 8) | 3);
            // CALL(aPrintNum);
            PrintNum(hl2, &maxHP, 2, 3);
        }

    // next:
        // POP_HL;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // INC_B;
        b++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void PlacePartyMonLevel(void){
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // LD_B(0);
    uint8_t b = 0;
    // hlcoord(8, 2, wTilemap);
    tile_t* hl = coord(8, 2, wram->wTilemap);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aPartyMenuCheckEgg);
        // IF_Z goto next;
        if(!PartyMenuCheckEgg(b)) {
            // PUSH_HL;
            tile_t* hl2 = hl;
            // LD_A_B;
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // LD_HL(wPartyMon1Level);
            // CALL(aAddNTimes);
            // LD_E_L;
            // LD_D_H;
            // POP_HL;
            // LD_A_de;
            // CP_A(100);  // This is distinct from MAX_LEVEL.
            // IF_NC goto ThreeDigits;
            if(gPokemon.partyMon[b].mon.level < 100) {
                // LD_A(0x6e);
                // LD_hli_A;
                *(hl2++) = 0x6e;
                // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
            // jr .okay
            }

        // ThreeDigits:
            // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 3);
        //  .okay
            // CALL(aPrintNum);
            PrintNum(hl2, &gPokemon.partyMon[b].mon.level, PRINTNUM_LEFTALIGN | 1, 3);
        }

    // next:
        // POP_HL;
        // LD_DE(SCREEN_WIDTH * 2);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH * 2;
        // POP_BC;
        // INC_B;
        b++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void PlacePartyMonStatus(void){
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // LD_B(0);
    uint8_t b = 0;
    // hlcoord(5, 2, wTilemap);
    tile_t* hl = coord(5, 2, wram->wTilemap);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aPartyMenuCheckEgg);
        // IF_Z goto next;
        if(!PartyMenuCheckEgg(b)) {
            // PUSH_HL;
            // LD_A_B;
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // LD_HL(wPartyMon1Status);
            // CALL(aAddNTimes);
            // LD_E_L;
            // LD_D_H;
            // POP_HL;
            // CALL(aPlaceStatusString);
            PlaceStatusString(hl, gPokemon.partyMon + b);
        }

    // next:
        // POP_HL;
        // LD_DE(SCREEN_WIDTH * 2);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH * 2;
        // POP_BC;
        // INC_B;
        b++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

static uint8_t* PlacePartyMonTMHMCompatibility_PlaceAbleNotAble(uint8_t c){
    static const char string_able[] = "ABLE@";
    static const char string_not_able[] = "NOT ABLE@";
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto able;
    if(c == 0) {
        // LD_DE(mPlacePartyMonTMHMCompatibility_string_not_able);
        // RET;
        return U82C(string_not_able);
    }
    else {
    // able:
        // LD_DE(mPlacePartyMonTMHMCompatibility_string_able);
        // RET;
        return U82C(string_able);
    }
}

void PlacePartyMonTMHMCompatibility(void){
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // LD_B(0);
    uint8_t b = 0;
    // hlcoord(12, 2, wTilemap);
    tile_t* hl = coord(12, 2, wram->wTilemap);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aPartyMenuCheckEgg);
        // IF_Z goto next;
        if(!PartyMenuCheckEgg(b)) {
            // PUSH_HL;
            // LD_HL(wPartySpecies);
            // LD_E_B;
            // LD_D(0);
            // ADD_HL_DE;
            // LD_A_hl;
            // LD_addr_A(wCurPartySpecies);
            // PREDEF(pCanLearnTMHMMove);
            uint8_t c = CanLearnTMHMMove(gPokemon.partySpecies[b], wram->wCurItem);
            // POP_HL;
            // CALL(aPlacePartyMonTMHMCompatibility_PlaceAbleNotAble);
            // CALL(aPlaceString);
            PlaceStringSimple(PlacePartyMonTMHMCompatibility_PlaceAbleNotAble(c), hl);
        }

    // next:
        // POP_HL;
        // LD_DE(SCREEN_WIDTH * 2);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH * 2;
        // POP_BC;
        // INC_B;
        // DEC_C;
        // IF_NZ goto loop;
    } while(b++, --c != 0);
    // RET;
}

static uint8_t* PlacePartyMonEvoStoneCompatibility_DetermineCompatibility(const struct EvoData* data) {
    static const char string_able[] = "ABLE@";
    static const char string_not_able[] = "NOT ABLE@";
    // LD_DE(wStringBuffer1);
    // LD_A(BANK(aEvosAttacksPointers));
    // LD_BC(2);
    // CALL(aFarCopyBytes);
    // LD_HL(wStringBuffer1);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(wStringBuffer1);
    // LD_A(BANK("Evolutions and Attacks"));
    // LD_BC(10);
    // CALL(aFarCopyBytes);
    // LD_HL(wStringBuffer1);

    for(uint8_t a = data->type; a != 0; a = (++data)->type) {
    // loop2:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto nope;
        // INC_HL;
        // INC_HL;
        // CP_A(EVOLVE_ITEM);
        // IF_NZ goto loop2;
        // DEC_HL;
        // DEC_HL;
        // LD_A_addr(wCurItem);
        // CP_A_hl;
        // INC_HL;
        // INC_HL;
        // IF_NZ goto loop2;
        if(a == EVOLVE_ITEM && data->item.useItem == wram->wCurItem) {
            // LD_DE(mPlacePartyMonEvoStoneCompatibility_string_able);
            // RET;
            return U82C(string_able);
        }
    }

// nope:
    // LD_DE(mPlacePartyMonEvoStoneCompatibility_string_not_able);
    // RET;
    return U82C(string_not_able);
}

void PlacePartyMonEvoStoneCompatibility(void){
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // LD_B(0);
    uint8_t b = 0;
    // hlcoord(12, 2, wTilemap);
    tile_t* hl = coord(12, 2, wram->wTilemap);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aPartyMenuCheckEgg);
        // IF_Z goto next;
        if(!PartyMenuCheckEgg(b)) {
            // PUSH_HL;
            // LD_A_B;
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // LD_HL(wPartyMon1Species);
            // CALL(aAddNTimes);
            // LD_A_hl;
            // DEC_A;
            // LD_E_A;
            // LD_D(0);
            // LD_HL(mEvosAttacksPointers);
            const struct EvoData* evos = EvosAttacksPointers[wram->wEvolutionOldSpecies - 1]->evolutions;
            // ADD_HL_DE;
            // ADD_HL_DE;
            // CALL(aPlacePartyMonEvoStoneCompatibility_DetermineCompatibility);
            // POP_HL;
            // CALL(aPlaceString);
            PlaceStringSimple(PlacePartyMonEvoStoneCompatibility_DetermineCompatibility(evos), hl);
        }

    // next:
        // POP_HL;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // INC_B;
        // DEC_C;
        // IF_NZ goto loop;
    } while(b++, --c != 0);
    // RET;
}

void PlacePartyMonGender(void){
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // LD_B(0);
    uint8_t b = 0;
    // hlcoord(12, 2, wTilemap);
    tile_t* hl = coord(12, 2, wram->wTilemap);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aPartyMenuCheckEgg);
        // IF_Z goto next;
        if(!PartyMenuCheckEgg(b)) {
            // LD_addr_A(wCurPartySpecies);
            wram->wCurPartySpecies = gPokemon.partySpecies[b];
            // PUSH_HL;
            // LD_A_B;
            // LD_addr_A(wCurPartyMon);
            wram->wCurPartyMon = b;
            // XOR_A_A;
            // LD_addr_A(wMonType);
            // CALL(aGetGender);
            u8_flag_s res = GetGender(0);
            // LD_DE(mPlacePartyMonGender_unknown);
            // IF_C goto got_gender;
            if(res.flag) {
                PlaceStringSimple(U82C("…UNKNOWN@"), hl);
            }
            // LD_DE(mPlacePartyMonGender_male);
            // IF_NZ goto got_gender;
            else if(res.a != 0) {
                PlaceStringSimple(U82C("♂…MALE@"), hl);
            }
            else {
                // LD_DE(mPlacePartyMonGender_female);


            // got_gender:
                // POP_HL;
                // CALL(aPlaceString);
                PlaceStringSimple(U82C("♀…FEMALE@"), hl);
            }
        }

    // next:
        // POP_HL;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // INC_B;
        b++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void PlacePartyMonMobileBattleSelection(void){
    static const char * const Strings_1_2_3[] = {
        "FIRST", "SECOND", "THIRD"  // 1st, 2nd, 3rd
    };
    static const char String_Able[] = "ABLE"; // "さんかしない@" ; Cancel
    static const char String_NotAble[] = "NOT ABLE";
    static const char String_Kettei_Yameru[] = "OK  CANCEL"; // "けってい　　やめる@" ; Quit
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // LD_B(0);
    uint8_t b = 0;
    // hlcoord(12, 1, wTilemap);
    tile_t* hl = coord(12, 2, wram->wTilemap);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        if(!PartyMenuCheckEgg(b)) {
        // .mon_able	
            // push hl
            // ld de, .String_Able
            // call PlaceString
            PlaceStringSimple(U82C(String_Able), hl);
            // pop hl
        }
        else {
            // LD_DE(mPlacePartyMonMobileBattleSelection_String_Sanka_Shinai);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(String_NotAble), hl);
            // POP_HL;
        }
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_BC;
        // INC_B;
        b++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_A_L;
    // LD_E(MON_NAME_LENGTH);
    // SUB_A_E;
    // LD_L_A;
    // LD_A_H;
    // SBC_A(0x0);
    // LD_H_A;
    hl -= MON_NAME_LENGTH + 20;
    // LD_DE(mPlacePartyMonMobileBattleSelection_String_Kettei_Yameru);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_Kettei_Yameru), hl);
    // LD_B(0x3);
    b = 0x3;
    // LD_C(0x0);
    c = 0x0;
    // LD_HL(wd002);
    uint8_t* hl2 = &wram->wd002;
    // LD_A_hl;
    uint8_t a = *hl2;

    do {
    // loop2:
        // PUSH_HL;
        // PUSH_BC;

    // loop3:
        // AND_A_A;
        // IF_Z goto done;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        // DEC_A;
        // goto loop3;

    // done:
        // LD_DE(mPlacePartyMonMobileBattleSelection_String_Banme);
        // PUSH_HL;
        tile_t* hl3 = coord(12, 2, wram->wTilemap) + SCREEN_WIDTH * 2 * a;
        // CALL(aPlaceString);
        // POP_HL;
        // POP_BC;
        // PUSH_BC;
        // PUSH_HL;
        // LD_A_C;
        // LD_HL(mPlacePartyMonMobileBattleSelection_Strings_1_2_3);
        // CALL(aGetNthString);
        // LD_D_H;
        // LD_E_L;
        // POP_HL;
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(Strings_1_2_3[c]), hl3);
        // POP_BC;
        // POP_HL;
        // INC_HL;
        hl2++;
        // LD_A_hl;
        a = *hl2;
        // INC_C;
        c++;
        // DEC_B;
        // RET_Z ;
        // goto loop2;
    } while(--b != 0);

// String_Banme:
    //db ['"\u3000ばんめ\u3000\u3000@"'];  // Place

// String_Sanka_Shinai:
    //db ['"さんかしない@"'];  // Cancel

// String_Kettei_Yameru:
    //db ['"けってい\u3000\u3000やめる@"'];  // Quit
}

bool PartyMenuCheckEgg(uint8_t b){
    // LD_A(LOW(wPartySpecies));
    // ADD_A_B;
    // LD_E_A;
    // LD_A(HIGH(wPartySpecies));
    // ADC_A(0);
    // LD_D_A;
    // LD_A_de;
    // CP_A(EGG);
    // RET;
    return gPokemon.partySpecies[b] == EGG;
}

const uint8_t* GetPartyMenuQualityIndexes(void){
    // LD_A_addr(wPartyMenuActionText);
    // AND_A(0xf0);
    // IF_NZ goto skip;
    if((wram->wPartyMenuActionText & 0xf0) == 0) {
        // LD_A_addr(wPartyMenuActionText);
        // AND_A(0xf);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mPartyMenuQualityPointers);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // RET;
        return PartyMenuQualityPointers[wram->wPartyMenuActionText & 0xf];
    }

// skip:
    // LD_HL(mPartyMenuQualityPointers_Default);
    // RET;
    return PartyMenuQualityPointers[PARTYMENUACTION_CHOOSE_POKEMON]; // points to PartyMenuQualityPointers_Default
// INCLUDE "data/party_menu_qualities.asm"
}

void InitPartyMenuGFX(void){
    // LD_HL(wPartyCount);
    // LD_A_hli;
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = gPokemon.partyCount;
    // XOR_A_A;
    // LDH_addr_A(hObjectStructIndex);
    hram.hObjectStructIndex = 0;

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // LD_HL(mLoadMenuMonIcon);
        // LD_A(BANK(aLoadMenuMonIcon));
        // LD_E(MONICON_PARTYMENU);
        // RST(aFarCall);
        LoadMenuMonIcon(MONICON_PARTYMENU);
        // LDH_A_addr(hObjectStructIndex);
        // INC_A;
        // LDH_addr_A(hObjectStructIndex);
        hram.hObjectStructIndex++;
        // POP_HL;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // CALLFAR(aPlaySpriteAnimations);
    PlaySpriteAnimations();
    // RET;
}

void InitPartyMenuWithCancel(void){
//  with cancel
    // XOR_A_A;
    // LD_addr_A(wSwitchMon);
    wram->wSwitchMon = 0;
    // LD_DE(mPartyMenu2DMenuData);
    // CALL(aLoad2DMenuData);
    Load2DMenuData(PartyMenu2DMenuData);
    // LD_A_addr(wPartyCount);
    // INC_A;
    // LD_addr_A(w2DMenuNumRows);  // list length
    wram->w2DMenuNumRows = gPokemon.partyCount + 1;
    // DEC_A;
    // LD_B_A;
    // LD_A_addr(wPartyMenuCursor);
    // AND_A_A;
    // IF_Z goto skip;
    // INC_B;
    // CP_A_B;
    // IF_C goto done;
    if(wram->wPartyMenuCursor == 0 || wram->wPartyMenuCursor >= gPokemon.partyCount + 1) {
    // skip:
        // LD_A(1);
        wram->wMenuCursorY = 1;
    }
    else {
        wram->wMenuCursorY = wram->wPartyMenuCursor;
    }

// done:
    // LD_addr_A(wMenuCursorY);
    // LD_A(A_BUTTON | B_BUTTON);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = A_BUTTON | B_BUTTON;
    // RET;
}

void InitPartyMenuNoCancel(void){
//  no cancel
    // LD_DE(mPartyMenu2DMenuData);
    // CALL(aLoad2DMenuData);
    Load2DMenuData(PartyMenu2DMenuData);
    // LD_A_addr(wPartyCount);
    // LD_addr_A(w2DMenuNumRows);  // list length
    wram->w2DMenuNumRows = gPokemon.partyCount;
    // LD_B_A;
    uint8_t b = gPokemon.partyCount;
    // LD_A_addr(wPartyMenuCursor);
    uint8_t a = wram->wPartyMenuCursor;
    // AND_A_A;
    // IF_Z goto skip;
    // INC_B;
    // CP_A_B;
    // IF_C goto done;
    if(a != 0 && a < b + 1) {
        wram->wMenuCursorY = a;
    }
    else {
    // skip:
        // LD_A(1);
        wram->wMenuCursorY = 1;
    }

// done:
    // LD_addr_A(wMenuCursorY);
    // LD_A(A_BUTTON | B_BUTTON);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = A_BUTTON | B_BUTTON;
    // RET;
}

const uint8_t PartyMenu2DMenuData[] = {
    1, 0,  // cursor start y, x
    0, 1,  // rows, columns
    0x60, 0x00,  // flags
    2<<4 | 0,  // cursor offset
    0,  // accepted buttons
};

//  returns true if exitted menu.
u8_flag_s PartyMenuSelect(void){
    // CALL(aStaticMenuJoypad);
    StaticMenuJoypad();
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor();
    // LD_A_addr(wPartyCount);
    // INC_A;
    // LD_B_A;
    uint8_t b = gPokemon.partyCount + 1;
    // LD_A_addr(wMenuCursorY);  // menu selection?
    // CP_A_B;
    // IF_Z goto exitmenu;  // CANCEL
    if(wram->wMenuCursorY != b) {
        // LD_addr_A(wPartyMenuCursor);
        wram->wPartyMenuCursor = wram->wMenuCursorY;
        // LDH_A_addr(hJoyLast);
        // LD_B_A;
        // BIT_B(B_BUTTON_F);
        // IF_NZ goto exitmenu;  // B button
        if(!bit_test(hram.hJoyLast, B_BUTTON_F)) {
            // LD_A_addr(wMenuCursorY);
            // DEC_A;
            // LD_addr_A(wCurPartyMon);
            wram->wCurPartyMon = wram->wMenuCursorY - 1;
            // LD_C_A;
            // LD_B(0);
            // LD_HL(wPartySpecies);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_addr_A(wCurPartySpecies);
            wram->wCurPartySpecies = gPokemon.partySpecies[wram->wCurPartyMon];

            // LD_DE(SFX_READ_TEXT_2);
            // CALL(aPlaySFX);
            PlaySFX(SFX_READ_TEXT_2);
            // CALL(aWaitSFX);
            WaitSFX();
            // AND_A_A;
            // RET;
            return u8_flag(wram->wCurPartyMon, false);
        }
    }

// exitmenu:
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // CALL(aWaitSFX);
    WaitSFX();
    // SCF;
    // RET;
    return u8_flag(0, true);
}

static const char YouHaveNoPKMNString[] = "You have no <PK><MN>!@";
static const char ChooseAMonString[] = "Choose a #MON.@";
static const char UseOnWhichPKMNString[] = "Use on which <PK><MN>?@";
static const char WhichPKMNString[] = "Which <PK><MN>?@";
static const char TeachWhichPKMNString[] = "Teach which <PK><MN>?@";
static const char MoveToWhereString[] = "Move to where?@";
// static const char ChooseAFemalePKMNString[] = "Choose a ♀<PK><MN>.@"; //  //  unreferenced
// static const char ChooseAMalePKMNString[] = "Choose a ♂<PK><MN>.@"; //  //  unreferenced
static const char ToWhichPKMNString[] = "To which <PK><MN>?@";

static const char* const PartyMenuStrings[] = {
    ChooseAMonString,
    UseOnWhichPKMNString,
    WhichPKMNString,
    TeachWhichPKMNString,
    MoveToWhereString,
    UseOnWhichPKMNString,
    ChooseAMonString,  // Probably used to be ChooseAFemalePKMNString
    ChooseAMonString,  // Probably used to be ChooseAMalePKMNString
    ToWhichPKMNString,
};

void PrintPartyMenuText(void){
    uint8_t buf[64];
    // hlcoord(0, 14, wTilemap);
    // LD_BC((2 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 14, wram->wTilemap), 2, 18);
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // IF_NZ goto haspokemon;
    const char* de;
    if(gPokemon.partyCount == 0) {
        // LD_DE(mYouHaveNoPKMNString);
        de = YouHaveNoPKMNString;
        // goto gotstring;
    }
    else {
    // haspokemon:
        // LD_A_addr(wPartyMenuActionText);
        // AND_A(0xf);  // drop high nibble
        // LD_HL(mPartyMenuStrings);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_D_hl;
        // LD_E_A;
        de = PartyMenuStrings[wram->wPartyMenuActionText & 0xf];
    }

// gotstring:
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = gOptions.options;
    // SET_A(NO_TEXT_SCROLL);
    // LD_addr_A(wOptions);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // hlcoord(1, 16, wTilemap);  // Coord
    // CALL(aPlaceString);
    PlaceStringSimple(U82CA(buf, de), coord(1, 16, wram->wTilemap));
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // RET;
}

static void PrintPartyMenuActionText_PrintText(const txt_cmd_s* text) {
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = gOptions.options;
    // SET_A(NO_TEXT_SCROLL);
    // LD_addr_A(wOptions);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // CALL(aPrintText);
    PrintText(text);
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // RET;
}

void PrintPartyMenuActionText(void){
    static const txt_cmd_s RecoveredSomeHPText[] = {
        text_far(v_RecoveredSomeHPText)
        text_end
    };
    static const txt_cmd_s CuredOfPoisonText[] = {
        text_far(v_CuredOfPoisonText)
        text_end
    };
    static const txt_cmd_s RidOfParalysisText[] = {
        text_far(v_RidOfParalysisText)
        text_end
    };
    static const txt_cmd_s BurnWasHealedText[] = {
        text_far(v_BurnWasHealedText)
        text_end
    };
    static const txt_cmd_s WasDefrostedText[] = {
        text_far(v_WasDefrostedText)
        text_end
    };
    static const txt_cmd_s WokeUpText[] = {
        text_far(v_WokeUpText)
        text_end
    };
    static const txt_cmd_s HealthReturnedText[] = {
        text_far(v_HealthReturnedText)
        text_end
    };
    static const txt_cmd_s RevitalizedText[] = {
        text_far(v_RevitalizedText)
        text_end
    };
    static const txt_cmd_s GrewToLevelText[] = {
        text_far(v_GrewToLevelText)
        text_end
    };
    static const txt_cmd_s CameToItsSensesText[] = {
        text_far(v_CameToItsSensesText)
        text_end
    };
    static const txt_cmd_s *MenuActionTexts[] = {
    //  entries correspond to PARTYMENUTEXT_* constants
        [PARTYMENUTEXT_HEAL_PSN       & 0xf] = CuredOfPoisonText,
        [PARTYMENUTEXT_HEAL_BRN       & 0xf] = BurnWasHealedText,
        [PARTYMENUTEXT_HEAL_FRZ       & 0xf] = WasDefrostedText,
        [PARTYMENUTEXT_HEAL_SLP       & 0xf] = WokeUpText,
        [PARTYMENUTEXT_HEAL_PAR       & 0xf] = RidOfParalysisText,
        [PARTYMENUTEXT_HEAL_HP        & 0xf] = RecoveredSomeHPText,
        [PARTYMENUTEXT_HEAL_ALL       & 0xf] = HealthReturnedText,
        [PARTYMENUTEXT_REVIVE         & 0xf] = RevitalizedText,
        [PARTYMENUTEXT_LEVEL_UP       & 0xf] = GrewToLevelText,
        [PARTYMENUTEXT_HEAL_CONFUSION & 0xf] = CameToItsSensesText,
    };
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetNickname);
    GetCurNickname();
    // LD_A_addr(wPartyMenuActionText);
    // AND_A(0xf);
    // LD_HL(mPrintPartyMenuActionText_MenuActionTexts);
    // CALL(aPrintPartyMenuActionText_PrintText);
    PrintPartyMenuActionText_PrintText(MenuActionTexts[wram->wPartyMenuActionText & 0xf]);
    // RET;
}
