#include "../../constants.h"
#include "radio.h"
#include "pokegear.h"
#include "../../home/region.h"

void PlayRadioShow(void){
//  If we're already in the radio program proper, we don't need to be here.
    LD_A_addr(wCurRadioLine);
    CP_A(POKE_FLUTE_RADIO);
    IF_NC goto ok;
//  If Team Rocket is not occupying the radio tower, we don't need to be here.
    LD_A_addr(wStatusFlags2);
    BIT_A(STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F);
    IF_Z goto ok;
//  If we're in Kanto, we don't need to be here.
    CALL(aIsInJohto);
    AND_A_A;
    IF_NZ goto ok;
//  Team Rocket broadcasts on all stations.
    LD_A(ROCKET_RADIO);
    LD_addr_A(wCurRadioLine);

ok:
//  Jump to the currently loaded station.  The index to which we need to jump is in wCurRadioLine.
    //jumptable ['RadioJumptable', 'wCurRadioLine']

    CALL(aRadioJumptable);
}

//  If we're not already in the radio program proper
//  and Team Rocket is occupying the radio tower
//  and we're in Johto.
void PlayRadioShow_Conv(void){
    if((gb_read(wCurRadioLine) < POKE_FLUTE_RADIO)
    && ((gb_read(wStatusFlags2) & (1 << STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F)) != 0)
    && (IsInJohto_Conv() == JOHTO_REGION))
    {
        //  Team Rocket broadcasts on all stations.
        gb_write(wCurRadioLine, ROCKET_RADIO);
    }
    //  Jump to the currently loaded station.  The index to which we need to jump is in wCurRadioLine.
    CALL(aRadioJumptable);
}

void (*const Radio_Stations[])(void) = {
    [OAKS_POKEMON_TALK] = OaksPKMNTalk1,
    [POKEDEX_SHOW] = PokedexShow1,
    [POKEMON_MUSIC] = BenMonMusic1,
    [LUCKY_CHANNEL] = LuckyNumberShow1,
    [BUENAS_PASSWORD] = BuenasPassword1,
    [PLACES_AND_PEOPLE] = PeoplePlaces1,
    [LETS_ALL_SING] = FernMonMusic1,
    [ROCKET_RADIO] = RocketRadio1,
    [POKE_FLUTE_RADIO] = PokeFluteRadio,
    [UNOWN_RADIO] = UnownRadio,
    [EVOLUTION_RADIO] = EvolutionRadio,
//  OaksPKMNTalk
    [OAKS_POKEMON_TALK_2] = OaksPKMNTalk2,
    [OAKS_POKEMON_TALK_3] = OaksPKMNTalk3,
    [OAKS_POKEMON_TALK_4] = OaksPKMNTalk4,
    [OAKS_POKEMON_TALK_5] = OaksPKMNTalk5,
    [OAKS_POKEMON_TALK_6] = OaksPKMNTalk6,
    [OAKS_POKEMON_TALK_7] = OaksPKMNTalk7,
    [OAKS_POKEMON_TALK_8] = OaksPKMNTalk8,
    [OAKS_POKEMON_TALK_9] = OaksPKMNTalk9,
    [POKEDEX_SHOW_2] = PokedexShow2,
    [POKEDEX_SHOW_3] = PokedexShow3,
    [POKEDEX_SHOW_4] = PokedexShow4,
    [POKEDEX_SHOW_5] = PokedexShow5,
//  Ben Music
    [POKEMON_MUSIC_2] = BenMonMusic2,
    [POKEMON_MUSIC_3] = BenMonMusic3,
    [POKEMON_MUSIC_4] = BenFernMusic4,
    [POKEMON_MUSIC_5] = BenFernMusic5,
    [POKEMON_MUSIC_6] = BenFernMusic6,
    [POKEMON_MUSIC_7] = BenFernMusic7,
    [LETS_ALL_SING_2] = FernMonMusic2,
//  Lucky Number Show
    [LUCKY_NUMBER_SHOW_2] = LuckyNumberShow2,
    [LUCKY_NUMBER_SHOW_3] = LuckyNumberShow3,
    [LUCKY_NUMBER_SHOW_4] = LuckyNumberShow4,
    [LUCKY_NUMBER_SHOW_5] = LuckyNumberShow5,
    [LUCKY_NUMBER_SHOW_6] = LuckyNumberShow6,
    [LUCKY_NUMBER_SHOW_7] = LuckyNumberShow7,
    [LUCKY_NUMBER_SHOW_8] = LuckyNumberShow8,
    [LUCKY_NUMBER_SHOW_9] = LuckyNumberShow9,
    [LUCKY_NUMBER_SHOW_10] = LuckyNumberShow10,
    [LUCKY_NUMBER_SHOW_11] = LuckyNumberShow11,
    [LUCKY_NUMBER_SHOW_12] = LuckyNumberShow12,
    [LUCKY_NUMBER_SHOW_13] = LuckyNumberShow13,
    [LUCKY_NUMBER_SHOW_14] = LuckyNumberShow14,
    [LUCKY_NUMBER_SHOW_15] = LuckyNumberShow15,
//  People & Places
    [PLACES_AND_PEOPLE_2] = PeoplePlaces2,
    [PLACES_AND_PEOPLE_3] = PeoplePlaces3,
    [PLACES_AND_PEOPLE_4] = PeoplePlaces4,
    [PLACES_AND_PEOPLE_5] = PeoplePlaces5,
    [PLACES_AND_PEOPLE_6] = PeoplePlaces6,
    [PLACES_AND_PEOPLE_7] = PeoplePlaces7,
//  Rocket Radio
    [ROCKET_RADIO_2] = RocketRadio2,
    [ROCKET_RADIO_3] = RocketRadio3,
    [ROCKET_RADIO_4] = RocketRadio4,
    [ROCKET_RADIO_5] = RocketRadio5,
    [ROCKET_RADIO_6] = RocketRadio6,
    [ROCKET_RADIO_7] = RocketRadio7,
    [ROCKET_RADIO_8] = RocketRadio8,
    [ROCKET_RADIO_9] = RocketRadio9,
    [ROCKET_RADIO_10] = RocketRadio10,
//  More Pokemon Channel stuff
    [OAKS_POKEMON_TALK_10] = OaksPKMNTalk10,
    [OAKS_POKEMON_TALK_11] = OaksPKMNTalk11,
    [OAKS_POKEMON_TALK_12] = OaksPKMNTalk12,
    [OAKS_POKEMON_TALK_13] = OaksPKMNTalk13,
    [OAKS_POKEMON_TALK_14] = OaksPKMNTalk14,
//  Buenas Password
    [BUENAS_PASSWORD_2] = BuenasPassword2,
    [BUENAS_PASSWORD_3] = BuenasPassword3,
    [BUENAS_PASSWORD_4] = BuenasPassword4,
    [BUENAS_PASSWORD_5] = BuenasPassword5,
    [BUENAS_PASSWORD_6] = BuenasPassword6,
    [BUENAS_PASSWORD_7] = BuenasPassword7,
    [BUENAS_PASSWORD_8] = BuenasPassword8,
    [BUENAS_PASSWORD_9] = BuenasPassword9,
    [BUENAS_PASSWORD_10] = BuenasPassword10,
    [BUENAS_PASSWORD_11] = BuenasPassword11,
    [BUENAS_PASSWORD_12] = BuenasPassword12,
    [BUENAS_PASSWORD_13] = BuenasPassword13,
    [BUENAS_PASSWORD_14] = BuenasPassword14,
    [BUENAS_PASSWORD_15] = BuenasPassword15,
    [BUENAS_PASSWORD_16] = BuenasPassword16,
    [BUENAS_PASSWORD_17] = BuenasPassword17,
    [BUENAS_PASSWORD_18] = BuenasPassword18,
    [BUENAS_PASSWORD_19] = BuenasPassword19,
    [BUENAS_PASSWORD_20] = BuenasPassword20,
    [BUENAS_PASSWORD_21] = BuenasPassword21,
    [RADIO_SCROLL] = RadioScroll,
//  More Pokemon Channel stuff
    [POKEDEX_SHOW_6] = PokedexShow6,
    [POKEDEX_SHOW_7] = PokedexShow7,
    [POKEDEX_SHOW_8] = PokedexShow8,
};

// _Static_assert(sizeof(Radio_Stations) / sizeof(void(*)(void)) == NUM_RADIO_SEGMENTS, "");

void RadioJumptable(void){
//  entries correspond to constants/radio_constants.asm
    return Radio_Stations[gb_read(wCurRadioLine)]();
    //table_width ['2', 'RadioJumptable']
    //dw ['OaksPKMNTalk1'];  // $00
    //dw ['PokedexShow1'];  // $01
    //dw ['BenMonMusic1'];  // $02
    //dw ['LuckyNumberShow1'];  // $03
    //dw ['BuenasPassword1'];  // $04
    //dw ['PeoplePlaces1'];  // $05
    //dw ['FernMonMusic1'];  // $06
    //dw ['RocketRadio1'];  // $07
    //dw ['PokeFluteRadio'];  // $08
    //dw ['UnownRadio'];  // $09
    //dw ['EvolutionRadio'];  // $0a
    //assert_table_length ['NUM_RADIO_CHANNELS']
//  OaksPKMNTalk
    //dw ['OaksPKMNTalk2'];  // $0b
    //dw ['OaksPKMNTalk3'];  // $0c
    //dw ['OaksPKMNTalk4'];  // $0d
    //dw ['OaksPKMNTalk5'];  // $0e
    //dw ['OaksPKMNTalk6'];  // $0f
    //dw ['OaksPKMNTalk7'];  // $10
    //dw ['OaksPKMNTalk8'];  // $11
    //dw ['OaksPKMNTalk9'];  // $12
    //dw ['PokedexShow2'];  // $13
    //dw ['PokedexShow3'];  // $14
    //dw ['PokedexShow4'];  // $15
    //dw ['PokedexShow5'];  // $16
//  Ben Music
    //dw ['BenMonMusic2'];  // $17
    //dw ['BenMonMusic3'];  // $18
    //dw ['BenFernMusic4'];  // $19
    //dw ['BenFernMusic5'];  // $1a
    //dw ['BenFernMusic6'];  // $1b
    //dw ['BenFernMusic7'];  // $1c
    //dw ['FernMonMusic2'];  // $1d
//  Lucky Number Show
    //dw ['LuckyNumberShow2'];  // $1e
    //dw ['LuckyNumberShow3'];  // $1f
    //dw ['LuckyNumberShow4'];  // $20
    //dw ['LuckyNumberShow5'];  // $21
    //dw ['LuckyNumberShow6'];  // $22
    //dw ['LuckyNumberShow7'];  // $23
    //dw ['LuckyNumberShow8'];  // $24
    //dw ['LuckyNumberShow9'];  // $25
    //dw ['LuckyNumberShow10'];  // $26
    //dw ['LuckyNumberShow11'];  // $27
    //dw ['LuckyNumberShow12'];  // $28
    //dw ['LuckyNumberShow13'];  // $29
    //dw ['LuckyNumberShow14'];  // $2a
    //dw ['LuckyNumberShow15'];  // $2b
//  People & Places
    //dw ['PeoplePlaces2'];  // $2c
    //dw ['PeoplePlaces3'];  // $2d
    //dw ['PeoplePlaces4'];  // $2e
    //dw ['PeoplePlaces5'];  // $2f
    //dw ['PeoplePlaces6'];  // $30
    //dw ['PeoplePlaces7'];  // $31
//  Rocket Radio
    //dw ['RocketRadio2'];  // $32
    //dw ['RocketRadio3'];  // $33
    //dw ['RocketRadio4'];  // $34
    //dw ['RocketRadio5'];  // $35
    //dw ['RocketRadio6'];  // $36
    //dw ['RocketRadio7'];  // $37
    //dw ['RocketRadio8'];  // $38
    //dw ['RocketRadio9'];  // $39
    //dw ['RocketRadio10'];  // $3a
//  More Pokemon Channel stuff
    //dw ['OaksPKMNTalk10'];  // $3b
    //dw ['OaksPKMNTalk11'];  // $3c
    //dw ['OaksPKMNTalk12'];  // $3d
    //dw ['OaksPKMNTalk13'];  // $3e
    //dw ['OaksPKMNTalk14'];  // $3f
//  Buenas Password
    //dw ['BuenasPassword2'];  // $40
    //dw ['BuenasPassword3'];  // $41
    //dw ['BuenasPassword4'];  // $42
    //dw ['BuenasPassword5'];  // $43
    //dw ['BuenasPassword6'];  // $44
    //dw ['BuenasPassword7'];  // $45
    //dw ['BuenasPassword8'];  // $46
    //dw ['BuenasPassword9'];  // $47
    //dw ['BuenasPassword10'];  // $48
    //dw ['BuenasPassword11'];  // $49
    //dw ['BuenasPassword12'];  // $4a
    //dw ['BuenasPassword13'];  // $4b
    //dw ['BuenasPassword14'];  // $4c
    //dw ['BuenasPassword15'];  // $4d
    //dw ['BuenasPassword16'];  // $4e
    //dw ['BuenasPassword17'];  // $4f
    //dw ['BuenasPassword18'];  // $50
    //dw ['BuenasPassword19'];  // $51
    //dw ['BuenasPassword20'];  // $52
    //dw ['BuenasPassword21'];  // $53
    //dw ['RadioScroll'];  // $54
//  More Pokemon Channel stuff
    //dw ['PokedexShow6'];  // $55
    //dw ['PokedexShow7'];  // $56
    //dw ['PokedexShow8'];  // $57
    //assert_table_length ['NUM_RADIO_SEGMENTS']

    return PrintRadioLine();
}

void PrintRadioLine(void){
    LD_addr_A(wNextRadioLine);
    LD_HL(wRadioText);
    LD_A_addr(wNumRadioLinesPrinted);
    CP_A(2);
    IF_NC goto print;
    INC_HL;
    LD_hl(TX_START);
    INC_A;
    LD_addr_A(wNumRadioLinesPrinted);
    CP_A(2);
    IF_NZ goto print;
    bccoord(1, 16, wTilemap);
    CALL(aPlaceHLTextAtBC);
    goto skip;

print:
    CALL(aPrintTextboxText);

skip:
    LD_A(RADIO_SCROLL);
    LD_addr_A(wCurRadioLine);
    LD_A(100);
    LD_addr_A(wRadioTextDelay);
    RET;

}

void PrintRadioLine_Conv(uint8_t a){
    gb_write(wNextRadioLine, a);
    REG_HL = wRadioText;
    uint8_t lines_printed = gb_read(wNumRadioLinesPrinted);
    if(lines_printed >= 2)
    {
        REG_A = lines_printed;
        CALL(aPrintTextboxText);
    }
    else 
    {
        gb_write(++REG_HL, TX_START);
        gb_write(wNumRadioLinesPrinted, ++lines_printed);
        if(lines_printed != 2)
        {
            REG_A = lines_printed;
            CALL(aPrintTextboxText);
        }
        else 
        {
            bccoord(1, 16, wTilemap);
            CALL(aPlaceHLTextAtBC);
        }
    }
    gb_write(wCurRadioLine, RADIO_SCROLL);
    gb_write(wRadioTextDelay, 100);
}

void ReplacePeriodsWithSpaces(void){
//  //  unreferenced
    PUSH_HL;
    LD_B(SCREEN_WIDTH * 2);

loop:
    LD_A_hl;
    CP_A(0xe8);
    IF_NZ goto next;
    LD_hl(0x7f);

next:
    INC_HL;
    DEC_B;
    IF_NZ goto loop;
    POP_HL;
    RET;

}

void RadioScroll(void){
    LD_HL(wRadioTextDelay);
    LD_A_hl;
    AND_A_A;
    IF_Z goto proceed;
    DEC_hl;
    RET;

proceed:
    LD_A_addr(wNextRadioLine);
    LD_addr_A(wCurRadioLine);
    LD_A_addr(wNumRadioLinesPrinted);
    CP_A(1);
    CALL_NZ (aCopyBottomLineToTopLine);
    JP(mClearBottomLine);

}

void RadioScroll_Conv(void){
    if(gb_read(wRadioTextDelay) == 0)
    {
        gb_write(wCurRadioLine, gb_read(wNextRadioLine));

        if(gb_read(wNumRadioLinesPrinted) != 1)
        {
            CALL(aCopyBottomLineToTopLine);
        }
        JP(mClearBottomLine);
    }
    gb_write(wRadioTextDelay, gb_read(wRadioTextDelay) - 1);
}

void OaksPKMNTalk1(void){
    LD_A(5);
    LD_addr_A(wOaksPKMNTalkSegmentCounter);
    CALL(aStartRadioStation);
    LD_HL(mOPT_IntroText1);
    LD_A(OAKS_POKEMON_TALK_2);
    JP(mNextRadioLine);

}

void OaksPKMNTalk2(void){
    LD_HL(mOPT_IntroText2);
    LD_A(OAKS_POKEMON_TALK_3);
    JP(mNextRadioLine);

}

void OaksPKMNTalk3(void){
    LD_HL(mOPT_IntroText3);
    LD_A(OAKS_POKEMON_TALK_4);
    JP(mNextRadioLine);

}

void OaksPKMNTalk4(void){
//  Choose a random route, and a random Pokemon from that route.

sample:
    CALL(aRandom);
    AND_A(0b11111);
    CP_A((aOaksPKMNTalkRoutes_End - aOaksPKMNTalkRoutes) / 2);
    IF_NC goto sample;
    LD_HL(mOaksPKMNTalkRoutes);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_B_hl;
    INC_HL;
    LD_C_hl;
// bc now contains the chosen map's group and number indices.
    PUSH_BC;

// Search the JohtoGrassWildMons array for the chosen map.
    LD_HL(mJohtoGrassWildMons);

loop:
    LD_A(BANK(aJohtoGrassWildMons));
    CALL(aGetFarByte);
    CP_A(-1);
    IF_Z goto overflow;
    INC_HL;
    CP_A_B;
    IF_NZ goto next;
    LD_A(BANK(aJohtoGrassWildMons));
    CALL(aGetFarByte);
    CP_A_C;
    IF_Z goto done;

next:
    DEC_HL;
    LD_DE(GRASS_WILDDATA_LENGTH);
    ADD_HL_DE;
    goto loop;


done:
// Point hl to the list of morning Pokémon., skipping percentages
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
// Generate a number, either 0, 1, or 2, to choose a time of day.

loop2:
    CALL(aRandom);
    maskbits(NUM_DAYTIMES, 0);
    CP_A(DARKNESS_F);
    IF_Z goto loop2;

    LD_BC(2 * NUM_GRASSMON);
    CALL(aAddNTimes);

loop3:
// Choose one of the middle three Pokemon.
    CALL(aRandom);
    maskbits(NUM_GRASSMON, 0);
    CP_A(2);
    IF_C goto loop3;
    CP_A(5);
    IF_NC goto loop3;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    INC_HL;  // skip level
    LD_A(BANK(aJohtoGrassWildMons));
    CALL(aGetFarByte);
    LD_addr_A(wNamedObjectIndex);
    LD_addr_A(wCurPartySpecies);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wMonOrItemNameBuffer);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);

// Now that we've chosen our wild Pokemon,
// let's recover the map index info and get its name.
    POP_BC;
    CALL(aGetWorldMapLocation);
    LD_E_A;
    FARCALL(aGetLandmarkName);
    LD_HL(mOPT_OakText1);
    CALL(aCopyRadioTextToRAM);
    LD_A(OAKS_POKEMON_TALK_5);
    JP(mPrintRadioLine);


overflow:
    POP_BC;
    LD_A(OAKS_POKEMON_TALK);
    JP(mPrintRadioLine);

// INCLUDE "data/radio/oaks_pkmn_talk_routes.asm"

    return OaksPKMNTalk5();
}

void OaksPKMNTalk5(void){
    LD_HL(mOPT_OakText2);
    LD_A(OAKS_POKEMON_TALK_6);
    JP(mNextRadioLine);

}

void OaksPKMNTalk6(void){
    LD_HL(mOPT_OakText3);
    LD_A(OAKS_POKEMON_TALK_7);
    JP(mNextRadioLine);

}

void OPT_IntroText1(void){
    //text_far ['_OPT_IntroText1']
    //text_end ['?']

    return OPT_IntroText2();
}

void OPT_IntroText2(void){
    //text_far ['_OPT_IntroText2']
    //text_end ['?']

    return OPT_IntroText3();
}

void OPT_IntroText3(void){
    //text_far ['_OPT_IntroText3']
    //text_end ['?']

    return OPT_OakText1();
}

void OPT_OakText1(void){
    //text_far ['_OPT_OakText1']
    //text_end ['?']

    return OPT_OakText2();
}

void OPT_OakText2(void){
    //text_far ['_OPT_OakText2']
    //text_end ['?']

    return OPT_OakText3();
}

void OPT_OakText3(void){
    //text_far ['_OPT_OakText3']
    //text_end ['?']

    return OaksPKMNTalk7();
}

void OaksPKMNTalk7(void){
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(mOPT_MaryText1);
    LD_A(OAKS_POKEMON_TALK_8);
    JP(mNextRadioLine);

}

void OPT_MaryText1(void){
    //text_far ['_OPT_MaryText1']
    //text_end ['?']

    return OaksPKMNTalk8();
}

void OaksPKMNTalk8(void){
// 0-15 are all valid indexes into .Adverbs,
// so no need for a retry loop
    CALL(aRandom);
    maskbits(NUM_OAKS_POKEMON_TALK_ADVERBS, 0);
    //assert_power_of_2 ['NUM_OAKS_POKEMON_TALK_ADVERBS']
    LD_E_A;
    LD_D(0);
    LD_HL(mOaksPKMNTalk8_Adverbs);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A(OAKS_POKEMON_TALK_9);
    JP(mNextRadioLine);


Adverbs:
    //table_width ['2', 'OaksPKMNTalk8.Adverbs']
    //dw ['.OPT_SweetAdorablyText'];
    //dw ['.OPT_WigglySlicklyText'];
    //dw ['.OPT_AptlyNamedText'];
    //dw ['.OPT_UndeniablyKindOfText'];
    //dw ['.OPT_UnbearablyText'];
    //dw ['.OPT_WowImpressivelyText'];
    //dw ['.OPT_AlmostPoisonouslyText'];
    //dw ['.OPT_SensuallyText'];
    //dw ['.OPT_MischievouslyText'];
    //dw ['.OPT_TopicallyText'];
    //dw ['.OPT_AddictivelyText'];
    //dw ['.OPT_LooksInWaterText'];
    //dw ['.OPT_EvolutionMustBeText'];
    //dw ['.OPT_ProvocativelyText'];
    //dw ['.OPT_FlippedOutText'];
    //dw ['.OPT_HeartMeltinglyText'];
    //assert_table_length ['NUM_OAKS_POKEMON_TALK_ADVERBS']


OPT_SweetAdorablyText:
    //text_far ['_OPT_SweetAdorablyText']
    //text_end ['?']


OPT_WigglySlicklyText:
    //text_far ['_OPT_WigglySlicklyText']
    //text_end ['?']


OPT_AptlyNamedText:
    //text_far ['_OPT_AptlyNamedText']
    //text_end ['?']


OPT_UndeniablyKindOfText:
    //text_far ['_OPT_UndeniablyKindOfText']
    //text_end ['?']


OPT_UnbearablyText:
    //text_far ['_OPT_UnbearablyText']
    //text_end ['?']


OPT_WowImpressivelyText:
    //text_far ['_OPT_WowImpressivelyText']
    //text_end ['?']


OPT_AlmostPoisonouslyText:
    //text_far ['_OPT_AlmostPoisonouslyText']
    //text_end ['?']


OPT_SensuallyText:
    //text_far ['_OPT_SensuallyText']
    //text_end ['?']


OPT_MischievouslyText:
    //text_far ['_OPT_MischievouslyText']
    //text_end ['?']


OPT_TopicallyText:
    //text_far ['_OPT_TopicallyText']
    //text_end ['?']


OPT_AddictivelyText:
    //text_far ['_OPT_AddictivelyText']
    //text_end ['?']


OPT_LooksInWaterText:
    //text_far ['_OPT_LooksInWaterText']
    //text_end ['?']


OPT_EvolutionMustBeText:
    //text_far ['_OPT_EvolutionMustBeText']
    //text_end ['?']


OPT_ProvocativelyText:
    //text_far ['_OPT_ProvocativelyText']
    //text_end ['?']


OPT_FlippedOutText:
    //text_far ['_OPT_FlippedOutText']
    //text_end ['?']


OPT_HeartMeltinglyText:
    //text_far ['_OPT_HeartMeltinglyText']
    //text_end ['?']

    return OaksPKMNTalk9();
}

void OaksPKMNTalk9(void){
// 0-15 are all valid indexes into .Adjectives,
// so no need for a retry loop
    CALL(aRandom);
    maskbits(NUM_OAKS_POKEMON_TALK_ADJECTIVES, 0);
    //assert_power_of_2 ['NUM_OAKS_POKEMON_TALK_ADJECTIVES']
    LD_E_A;
    LD_D(0);
    LD_HL(mOaksPKMNTalk9_Adjectives);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wOaksPKMNTalkSegmentCounter);
    DEC_A;
    LD_addr_A(wOaksPKMNTalkSegmentCounter);
    LD_A(OAKS_POKEMON_TALK_4);
    IF_NZ goto ok;
    LD_A(5);
    LD_addr_A(wOaksPKMNTalkSegmentCounter);
    LD_A(OAKS_POKEMON_TALK_10);

ok:
    JP(mNextRadioLine);


Adjectives:
    //table_width ['2', 'OaksPKMNTalk9.Adjectives']
    //dw ['.OPT_CuteText'];
    //dw ['.OPT_WeirdText'];
    //dw ['.OPT_PleasantText'];
    //dw ['.OPT_BoldSortOfText'];
    //dw ['.OPT_FrighteningText'];
    //dw ['.OPT_SuaveDebonairText'];
    //dw ['.OPT_PowerfulText'];
    //dw ['.OPT_ExcitingText'];
    //dw ['.OPT_GroovyText'];
    //dw ['.OPT_InspiringText'];
    //dw ['.OPT_FriendlyText'];
    //dw ['.OPT_HotHotHotText'];
    //dw ['.OPT_StimulatingText'];
    //dw ['.OPT_GuardedText'];
    //dw ['.OPT_LovelyText'];
    //dw ['.OPT_SpeedyText'];
    //assert_table_length ['NUM_OAKS_POKEMON_TALK_ADJECTIVES']


OPT_CuteText:
    //text_far ['_OPT_CuteText']
    //text_end ['?']


OPT_WeirdText:
    //text_far ['_OPT_WeirdText']
    //text_end ['?']


OPT_PleasantText:
    //text_far ['_OPT_PleasantText']
    //text_end ['?']


OPT_BoldSortOfText:
    //text_far ['_OPT_BoldSortOfText']
    //text_end ['?']


OPT_FrighteningText:
    //text_far ['_OPT_FrighteningText']
    //text_end ['?']


OPT_SuaveDebonairText:
    //text_far ['_OPT_SuaveDebonairText']
    //text_end ['?']


OPT_PowerfulText:
    //text_far ['_OPT_PowerfulText']
    //text_end ['?']


OPT_ExcitingText:
    //text_far ['_OPT_ExcitingText']
    //text_end ['?']


OPT_GroovyText:
    //text_far ['_OPT_GroovyText']
    //text_end ['?']


OPT_InspiringText:
    //text_far ['_OPT_InspiringText']
    //text_end ['?']


OPT_FriendlyText:
    //text_far ['_OPT_FriendlyText']
    //text_end ['?']


OPT_HotHotHotText:
    //text_far ['_OPT_HotHotHotText']
    //text_end ['?']


OPT_StimulatingText:
    //text_far ['_OPT_StimulatingText']
    //text_end ['?']


OPT_GuardedText:
    //text_far ['_OPT_GuardedText']
    //text_end ['?']


OPT_LovelyText:
    //text_far ['_OPT_LovelyText']
    //text_end ['?']


OPT_SpeedyText:
    //text_far ['_OPT_SpeedyText']
    //text_end ['?']

    return OaksPKMNTalk10();
}

void OaksPKMNTalk10(void){
    FARCALL(aRadioMusicRestartPokemonChannel);
    LD_HL(mOPT_RestartText);
    CALL(aPrintText);
    CALL(aWaitBGMap);
    LD_HL(mOPT_PokemonChannelText);
    CALL(aPrintText);
    LD_A(OAKS_POKEMON_TALK_11);
    LD_addr_A(wCurRadioLine);
    LD_A(100);
    LD_addr_A(wRadioTextDelay);
    RET;

}

void OPT_PokemonChannelText(void){
    //text_far ['_OPT_PokemonChannelText']
    //text_end ['?']

    return OPT_RestartText();
}

void OPT_RestartText(void){
    //text_end ['?']

    return OaksPKMNTalk11();
}

void OaksPKMNTalk11(void){
    LD_HL(wRadioTextDelay);
    DEC_hl;
    RET_NZ ;
    hlcoord(9, 14, wTilemap);
    LD_DE(mOaksPKMNTalk11_pokemon_string);
    LD_A(OAKS_POKEMON_TALK_12);
    JP(mPlaceRadioString);


pokemon_string:
    //db ['"#MON@"'];

    return OaksPKMNTalk12();
}

void OaksPKMNTalk12(void){
    LD_HL(wRadioTextDelay);
    DEC_hl;
    RET_NZ ;
    hlcoord(1, 16, wTilemap);
    LD_DE(mOaksPKMNTalk12_pokemon_channel_string);
    LD_A(OAKS_POKEMON_TALK_13);
    JP(mPlaceRadioString);


pokemon_channel_string:
    //db ['"#MON Channel@"'];

    return OaksPKMNTalk13();
}

void OaksPKMNTalk13(void){
    LD_HL(wRadioTextDelay);
    DEC_hl;
    RET_NZ ;
    hlcoord(12, 16, wTilemap);
    LD_DE(mOaksPKMNTalk13_terminator);
    LD_A(OAKS_POKEMON_TALK_14);
    JP(mPlaceRadioString);


terminator:
    //db ['"@"'];

    return OaksPKMNTalk14();
}

void OaksPKMNTalk14(void){
    LD_HL(wRadioTextDelay);
    DEC_hl;
    RET_NZ ;
    LD_DE(MUSIC_POKEMON_TALK);
    CALLFAR(aRadioMusicRestartDE);
    LD_HL(mOaksPKMNTalk14_terminator);
    CALL(aPrintText);
    LD_A(OAKS_POKEMON_TALK_4);
    LD_addr_A(wNextRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_A(RADIO_SCROLL);
    LD_addr_A(wCurRadioLine);
    LD_A(10);
    LD_addr_A(wRadioTextDelay);
    RET;


terminator:
    //db ['"@"'];

    return PlaceRadioString();
}

void PlaceRadioString(void){
    LD_addr_A(wCurRadioLine);
    LD_A(100);
    LD_addr_A(wRadioTextDelay);
    JP(mPlaceString);

}

void CopyBottomLineToTopLine(void){
    hlcoord(0, 15, wTilemap);
    decoord(0, 13, wTilemap);
    LD_BC(SCREEN_WIDTH * 2);
    JP(mCopyBytes);

}

void ClearBottomLine(void){
    hlcoord(1, 15, wTilemap);
    LD_BC(SCREEN_WIDTH - 2);
    LD_A(0x7f);
    CALL(aByteFill);
    hlcoord(1, 16, wTilemap);
    LD_BC(SCREEN_WIDTH - 2);
    LD_A(0x7f);
    JP(mByteFill);

}

void PokedexShow_GetDexEntryBank(void){
    PUSH_HL;
    PUSH_DE;
    LD_A_addr(wCurPartySpecies);
    DEC_A;
    RLCA;
    RLCA;
    maskbits(NUM_DEX_ENTRY_BANKS, 0);
    LD_HL(mPokedexShow_GetDexEntryBank_PokedexEntryBanks);
    LD_D(0);
    LD_E_A;
    ADD_HL_DE;
    LD_A_hl;
    POP_DE;
    POP_HL;
    RET;


PokedexEntryBanks:
    //db ['BANK("Pokedex Entries 001-064")'];
    //db ['BANK("Pokedex Entries 065-128")'];
    //db ['BANK("Pokedex Entries 129-192")'];
    //db ['BANK("Pokedex Entries 193-251")'];

    return PokedexShow1();
}

void PokedexShow1(void){
    CALL(aStartRadioStation);

loop:
    CALL(aRandom);
    CP_A(NUM_POKEMON);
    IF_NC goto loop;
    LD_C_A;
    PUSH_BC;
    LD_A_C;
    CALL(aCheckCaughtMon);
    POP_BC;
    IF_Z goto loop;
    INC_C;
    LD_A_C;
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(mPokedexShowText);
    LD_A(POKEDEX_SHOW_2);
    JP(mNextRadioLine);

}

void PokedexShow2(void){
    LD_A_addr(wCurPartySpecies);
    DEC_A;
    LD_HL(mPokedexDataPointerTable);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A(BANK(aPokedexDataPointerTable));
    CALL(aGetFarWord);
    CALL(aPokedexShow_GetDexEntryBank);
    PUSH_AF;
    PUSH_HL;
    CALL(aCopyDexEntryPart1);
    DEC_HL;
    LD_hl(0x57);
    LD_HL(wPokedexShowPointerAddr);
    CALL(aCopyRadioTextToRAM);
    POP_HL;
    POP_AF;
    CALL(aCopyDexEntryPart2);
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
    LD_A_L;
    LD_addr_A(wPokedexShowPointerAddr);
    LD_A_H;
    LD_addr_A(wPokedexShowPointerAddr + 1);
    LD_A(POKEDEX_SHOW_3);
    JP(mPrintRadioLine);

}

void PokedexShow3(void){
    CALL(aCopyDexEntry);
    LD_A(POKEDEX_SHOW_4);
    JP(mPrintRadioLine);

}

void PokedexShow4(void){
    CALL(aCopyDexEntry);
    LD_A(POKEDEX_SHOW_5);
    JP(mPrintRadioLine);

}

void PokedexShow5(void){
    CALL(aCopyDexEntry);
    LD_A(POKEDEX_SHOW_6);
    JP(mPrintRadioLine);

}

void PokedexShow6(void){
    CALL(aCopyDexEntry);
    LD_A(POKEDEX_SHOW_7);
    JP(mPrintRadioLine);

}

void PokedexShow7(void){
    CALL(aCopyDexEntry);
    LD_A(POKEDEX_SHOW_8);
    JP(mPrintRadioLine);

}

void PokedexShow8(void){
    CALL(aCopyDexEntry);
    LD_A(POKEDEX_SHOW);
    JP(mPrintRadioLine);

}

void CopyDexEntry(void){
    LD_A_addr(wPokedexShowPointerAddr);
    LD_L_A;
    LD_A_addr(wPokedexShowPointerAddr + 1);
    LD_H_A;
    LD_A_addr(wPokedexShowPointerBank);
    PUSH_AF;
    PUSH_HL;
    CALL(aCopyDexEntryPart1);
    DEC_HL;
    LD_hl(0x57);
    LD_HL(wPokedexShowPointerAddr);
    CALL(aCopyRadioTextToRAM);
    POP_HL;
    POP_AF;
    CALL(aCopyDexEntryPart2);
    RET;

}

void CopyDexEntryPart1(void){
    LD_DE(wPokedexShowPointerBank);
    LD_BC(SCREEN_WIDTH - 1);
    CALL(aFarCopyBytes);
    LD_HL(wPokedexShowPointerAddr);
    LD_hl(TX_START);
    INC_HL;
    LD_hl(0x4f);
    INC_HL;

loop:
    LD_A_hli;
    CP_A(0x50);
    RET_Z ;
    CP_A(0x4e);
    RET_Z ;
    CP_A(0x5f);
    RET_Z ;
    goto loop;

    return CopyDexEntryPart2();
}

void CopyDexEntryPart2(void){
    LD_D_A;

loop:
    LD_A_D;
    CALL(aGetFarByte);
    INC_HL;
    CP_A(0x50);
    IF_Z goto okay;
    CP_A(0x4e);
    IF_Z goto okay;
    CP_A(0x5f);
    IF_NZ goto loop;

okay:
    LD_A_L;
    LD_addr_A(wPokedexShowPointerAddr);
    LD_A_H;
    LD_addr_A(wPokedexShowPointerAddr + 1);
    LD_A_D;
    LD_addr_A(wPokedexShowPointerBank);
    RET;

}

void PokedexShowText(void){
    //text_far ['_PokedexShowText']
    //text_end ['?']

    return BenMonMusic1();
}

void BenMonMusic1(void){
    CALL(aStartPokemonMusicChannel);
    LD_HL(mBenIntroText1);
    LD_A(POKEMON_MUSIC_2);
    JP(mNextRadioLine);

}

void BenMonMusic2(void){
    LD_HL(mBenIntroText2);
    LD_A(POKEMON_MUSIC_3);
    JP(mNextRadioLine);

}

void BenMonMusic3(void){
    LD_HL(mBenIntroText3);
    LD_A(POKEMON_MUSIC_4);
    JP(mNextRadioLine);

}

void FernMonMusic1(void){
    CALL(aStartPokemonMusicChannel);
    LD_HL(mFernIntroText1);
    LD_A(LETS_ALL_SING_2);
    JP(mNextRadioLine);

}

void FernMonMusic2(void){
    LD_HL(mFernIntroText2);
    LD_A(POKEMON_MUSIC_4);
    JP(mNextRadioLine);

}

void BenFernMusic4(void){
    LD_HL(mBenFernText1);
    LD_A(POKEMON_MUSIC_5);
    JP(mNextRadioLine);

}

void BenFernMusic5(void){
    CALL(aGetWeekday);
    AND_A(1);
    LD_HL(mBenFernText2A);
    IF_Z goto SunTueThurSun;
    LD_HL(mBenFernText2B);

SunTueThurSun:
    LD_A(POKEMON_MUSIC_6);
    JP(mNextRadioLine);

}

void BenFernMusic6(void){
    CALL(aGetWeekday);
    AND_A(1);
    LD_HL(mBenFernText3A);
    IF_Z goto SunTueThurSun;
    LD_HL(mBenFernText3B);

SunTueThurSun:
    LD_A(POKEMON_MUSIC_7);
    JP(mNextRadioLine);

}

void BenFernMusic7(void){
    RET;

}

void StartPokemonMusicChannel(void){
    CALL(aRadioTerminator);
    CALL(aPrintText);
    LD_DE(MUSIC_POKEMON_MARCH);
    CALL(aGetWeekday);
    AND_A(1);
    IF_Z goto SunTueThurSun;
    LD_DE(MUSIC_POKEMON_LULLABY);

SunTueThurSun:
    CALLFAR(aRadioMusicRestartDE);
    RET;

}

void BenIntroText1(void){
    //text_far ['_BenIntroText1']
    //text_end ['?']

    return BenIntroText2();
}

void BenIntroText2(void){
    //text_far ['_BenIntroText2']
    //text_end ['?']

    return BenIntroText3();
}

void BenIntroText3(void){
    //text_far ['_BenIntroText3']
    //text_end ['?']

    return FernIntroText1();
}

void FernIntroText1(void){
    //text_far ['_FernIntroText1']
    //text_end ['?']

    return FernIntroText2();
}

void FernIntroText2(void){
    //text_far ['_FernIntroText2']
    //text_end ['?']

    return BenFernText1();
}

void BenFernText1(void){
    //text_far ['_BenFernText1']
    //text_end ['?']

    return BenFernText2A();
}

void BenFernText2A(void){
    //text_far ['_BenFernText2A']
    //text_end ['?']

    return BenFernText2B();
}

void BenFernText2B(void){
    //text_far ['_BenFernText2B']
    //text_end ['?']

    return BenFernText3A();
}

void BenFernText3A(void){
    //text_far ['_BenFernText3A']
    //text_end ['?']

    return BenFernText3B();
}

void BenFernText3B(void){
    //text_far ['_BenFernText3B']
    //text_end ['?']

    return LuckyNumberShow1();
}

void LuckyNumberShow1(void){
    CALL(aStartRadioStation);
    CALLFAR(aCheckLuckyNumberShowFlag);
    IF_NC goto dontreset;
    CALLFAR(aResetLuckyNumberShowFlag);

dontreset:
    LD_HL(mLC_Text1);
    LD_A(LUCKY_NUMBER_SHOW_2);
    JP(mNextRadioLine);

}

void LuckyNumberShow2(void){
    LD_HL(mLC_Text2);
    LD_A(LUCKY_NUMBER_SHOW_3);
    JP(mNextRadioLine);

}

void LuckyNumberShow3(void){
    LD_HL(mLC_Text3);
    LD_A(LUCKY_NUMBER_SHOW_4);
    JP(mNextRadioLine);

}

void LuckyNumberShow4(void){
    LD_HL(mLC_Text4);
    LD_A(LUCKY_NUMBER_SHOW_5);
    JP(mNextRadioLine);

}

void LuckyNumberShow5(void){
    LD_HL(mLC_Text5);
    LD_A(LUCKY_NUMBER_SHOW_6);
    JP(mNextRadioLine);

}

void LuckyNumberShow6(void){
    LD_HL(mLC_Text6);
    LD_A(LUCKY_NUMBER_SHOW_7);
    JP(mNextRadioLine);

}

void LuckyNumberShow7(void){
    LD_HL(mLC_Text7);
    LD_A(LUCKY_NUMBER_SHOW_8);
    JP(mNextRadioLine);

}

void LuckyNumberShow8(void){
    LD_HL(wStringBuffer1);
    LD_DE(wLuckyIDNumber);
    LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    CALL(aPrintNum);
    LD_A(0x50);
    LD_addr_A(wStringBuffer1 + 5);
    LD_HL(mLC_Text8);
    LD_A(LUCKY_NUMBER_SHOW_9);
    JP(mNextRadioLine);

}

void LuckyNumberShow9(void){
    LD_HL(mLC_Text9);
    LD_A(LUCKY_NUMBER_SHOW_10);
    JP(mNextRadioLine);

}

void LuckyNumberShow10(void){
    LD_HL(mLC_Text7);
    LD_A(LUCKY_NUMBER_SHOW_11);
    JP(mNextRadioLine);

}

void LuckyNumberShow11(void){
    LD_HL(mLC_Text8);
    LD_A(LUCKY_NUMBER_SHOW_12);
    JP(mNextRadioLine);

}

void LuckyNumberShow12(void){
    LD_HL(mLC_Text10);
    LD_A(LUCKY_NUMBER_SHOW_13);
    JP(mNextRadioLine);

}

void LuckyNumberShow13(void){
    LD_HL(mLC_Text11);
    CALL(aRandom);
    AND_A_A;
    LD_A(LUCKY_CHANNEL);
    IF_NZ goto okay;
    LD_A(LUCKY_NUMBER_SHOW_14);

okay:
    JP(mNextRadioLine);

}

void LuckyNumberShow14(void){
    LD_HL(mLC_DragText1);
    LD_A(LUCKY_NUMBER_SHOW_15);
    JP(mNextRadioLine);

}

void LuckyNumberShow15(void){
    LD_HL(mLC_DragText2);
    LD_A(LUCKY_CHANNEL);
    JP(mNextRadioLine);

}

void LC_Text1(void){
    //text_far ['_LC_Text1']
    //text_end ['?']

    return LC_Text2();
}

void LC_Text2(void){
    //text_far ['_LC_Text2']
    //text_end ['?']

    return LC_Text3();
}

void LC_Text3(void){
    //text_far ['_LC_Text3']
    //text_end ['?']

    return LC_Text4();
}

void LC_Text4(void){
    //text_far ['_LC_Text4']
    //text_end ['?']

    return LC_Text5();
}

void LC_Text5(void){
    //text_far ['_LC_Text5']
    //text_end ['?']

    return LC_Text6();
}

void LC_Text6(void){
    //text_far ['_LC_Text6']
    //text_end ['?']

    return LC_Text7();
}

void LC_Text7(void){
    //text_far ['_LC_Text7']
    //text_end ['?']

    return LC_Text8();
}

void LC_Text8(void){
    //text_far ['_LC_Text8']
    //text_end ['?']

    return LC_Text9();
}

void LC_Text9(void){
    //text_far ['_LC_Text9']
    //text_end ['?']

    return LC_Text10();
}

void LC_Text10(void){
    //text_far ['_LC_Text10']
    //text_end ['?']

    return LC_Text11();
}

void LC_Text11(void){
    //text_far ['_LC_Text11']
    //text_end ['?']

    return LC_DragText1();
}

void LC_DragText1(void){
    //text_far ['_LC_DragText1']
    //text_end ['?']

    return LC_DragText2();
}

void LC_DragText2(void){
    //text_far ['_LC_DragText2']
    //text_end ['?']

    return PeoplePlaces1();
}

void PeoplePlaces1(void){
    CALL(aStartRadioStation);
    LD_HL(mPnP_Text1);
    LD_A(PLACES_AND_PEOPLE_2);
    JP(mNextRadioLine);

}

void PeoplePlaces2(void){
    LD_HL(mPnP_Text2);
    LD_A(PLACES_AND_PEOPLE_3);
    JP(mNextRadioLine);

}

void PeoplePlaces3(void){
    LD_HL(mPnP_Text3);
    CALL(aRandom);
    CP_A(49 percent - 1);
    LD_A(PLACES_AND_PEOPLE_4);  // People
    IF_C goto ok;
    LD_A(PLACES_AND_PEOPLE_6);  // Places

ok:
    JP(mNextRadioLine);

}

void PnP_Text1(void){
    //text_far ['_PnP_Text1']
    //text_end ['?']

    return PnP_Text2();
}

void PnP_Text2(void){
    //text_far ['_PnP_Text2']
    //text_end ['?']

    return PnP_Text3();
}

void PnP_Text3(void){
    //text_far ['_PnP_Text3']
    //text_end ['?']

    return PeoplePlaces4();
}

void PeoplePlaces4(void){
//  //  People
    CALL(aRandom);
    maskbits(NUM_TRAINER_CLASSES, 0);
    INC_A;
    CP_A(NUM_TRAINER_CLASSES);  // exclude MYSTICALMAN
    JR_NC (mPeoplePlaces4);
    PUSH_AF;
    LD_HL(mPnP_HiddenPeople);
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
    IF_Z goto ok;
    LD_HL(mPnP_HiddenPeople_BeatE4);
    LD_A_addr(wKantoBadges);
    CP_A(0b11111111);  // all badges
    IF_NZ goto ok;
    LD_HL(mPnP_HiddenPeople_BeatKanto);

ok:
    POP_AF;
    LD_C_A;
    LD_DE(1);
    PUSH_BC;
    CALL(aIsInArray);
    POP_BC;
    JR_C (mPeoplePlaces4);
    PUSH_BC;
    CALLFAR(aGetTrainerClassName);
    LD_DE(wStringBuffer1);
    CALL(aCopyName1);
    POP_BC;
    LD_B(1);
    CALLFAR(aGetTrainerName);
    LD_HL(mPnP_Text4);
    LD_A(PLACES_AND_PEOPLE_5);
    JP(mNextRadioLine);

// INCLUDE "data/radio/pnp_hidden_people.asm"

    return PnP_Text4();
}

void PnP_Text4(void){
    //text_far ['_PnP_Text4']
    //text_end ['?']

    return PeoplePlaces5();
}

void PeoplePlaces5(void){
// 0-15 are all valid indexes into .Adjectives,
// so no need for a retry loop
    CALL(aRandom);
    maskbits(NUM_PNP_PEOPLE_ADJECTIVES, 0);
    //assert_power_of_2 ['NUM_PNP_PEOPLE_ADJECTIVES']
    LD_E_A;
    LD_D(0);
    LD_HL(mPeoplePlaces5_Adjectives);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aRandom);
    CP_A(4 percent);
    LD_A(PLACES_AND_PEOPLE);
    IF_C goto ok;
    CALL(aRandom);
    CP_A(49 percent - 1);
    LD_A(PLACES_AND_PEOPLE_4);  // People
    IF_C goto ok;
    LD_A(PLACES_AND_PEOPLE_6);  // Places

ok:
    JP(mNextRadioLine);


Adjectives:
    //table_width ['2', 'PeoplePlaces5.Adjectives']
    //dw ['PnP_CuteText'];
    //dw ['PnP_LazyText'];
    //dw ['PnP_HappyText'];
    //dw ['PnP_NoisyText'];
    //dw ['PnP_PrecociousText'];
    //dw ['PnP_BoldText'];
    //dw ['PnP_PickyText'];
    //dw ['PnP_SortOfOKText'];
    //dw ['PnP_SoSoText'];
    //dw ['PnP_GreatText'];
    //dw ['PnP_MyTypeText'];
    //dw ['PnP_CoolText'];
    //dw ['PnP_InspiringText'];
    //dw ['PnP_WeirdText'];
    //dw ['PnP_RightForMeText'];
    //dw ['PnP_OddText'];
    //assert_table_length ['NUM_PNP_PEOPLE_ADJECTIVES']

    return PnP_CuteText();
}

void PnP_CuteText(void){
    //text_far ['_PnP_CuteText']
    //text_end ['?']

    return PnP_LazyText();
}

void PnP_LazyText(void){
    //text_far ['_PnP_LazyText']
    //text_end ['?']

    return PnP_HappyText();
}

void PnP_HappyText(void){
    //text_far ['_PnP_HappyText']
    //text_end ['?']

    return PnP_NoisyText();
}

void PnP_NoisyText(void){
    //text_far ['_PnP_NoisyText']
    //text_end ['?']

    return PnP_PrecociousText();
}

void PnP_PrecociousText(void){
    //text_far ['_PnP_PrecociousText']
    //text_end ['?']

    return PnP_BoldText();
}

void PnP_BoldText(void){
    //text_far ['_PnP_BoldText']
    //text_end ['?']

    return PnP_PickyText();
}

void PnP_PickyText(void){
    //text_far ['_PnP_PickyText']
    //text_end ['?']

    return PnP_SortOfOKText();
}

void PnP_SortOfOKText(void){
    //text_far ['_PnP_SortOfOKText']
    //text_end ['?']

    return PnP_SoSoText();
}

void PnP_SoSoText(void){
    //text_far ['_PnP_SoSoText']
    //text_end ['?']

    return PnP_GreatText();
}

void PnP_GreatText(void){
    //text_far ['_PnP_GreatText']
    //text_end ['?']

    return PnP_MyTypeText();
}

void PnP_MyTypeText(void){
    //text_far ['_PnP_MyTypeText']
    //text_end ['?']

    return PnP_CoolText();
}

void PnP_CoolText(void){
    //text_far ['_PnP_CoolText']
    //text_end ['?']

    return PnP_InspiringText();
}

void PnP_InspiringText(void){
    //text_far ['_PnP_InspiringText']
    //text_end ['?']

    return PnP_WeirdText();
}

void PnP_WeirdText(void){
    //text_far ['_PnP_WeirdText']
    //text_end ['?']

    return PnP_RightForMeText();
}

void PnP_RightForMeText(void){
    //text_far ['_PnP_RightForMeText']
    //text_end ['?']

    return PnP_OddText();
}

void PnP_OddText(void){
    //text_far ['_PnP_OddText']
    //text_end ['?']

    return PeoplePlaces6();
}

void PeoplePlaces6(void){
//  //  Places
    CALL(aRandom);
    CP_A((aPnP_Places_End - aPnP_Places) / 2);
    JR_NC (mPeoplePlaces6);
    LD_HL(mPnP_Places);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    CALL(aGetWorldMapLocation);
    LD_E_A;
    FARCALL(aGetLandmarkName);
    LD_HL(mPnP_Text5);
    LD_A(PLACES_AND_PEOPLE_7);
    JP(mNextRadioLine);

// INCLUDE "data/radio/pnp_places.asm"

    return PnP_Text5();
}

void PnP_Text5(void){
    //text_far ['_PnP_Text5']
    //text_end ['?']

    return PeoplePlaces7();
}

void PeoplePlaces7(void){
// 0-15 are all valid indexes into .Adjectives,
// so no need for a retry loop
    CALL(aRandom);
    maskbits(NUM_PNP_PLACES_ADJECTIVES, 0);
    //assert_power_of_2 ['NUM_PNP_PLACES_ADJECTIVES']
    LD_E_A;
    LD_D(0);
    LD_HL(mPeoplePlaces7_Adjectives);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aCopyRadioTextToRAM);
    CALL(aRandom);
    CP_A(4 percent);
    LD_A(PLACES_AND_PEOPLE);
    IF_C goto ok;
    CALL(aRandom);
    CP_A(49 percent - 1);
    LD_A(PLACES_AND_PEOPLE_4);  // People
    IF_C goto ok;
    LD_A(PLACES_AND_PEOPLE_6);  // Places

ok:
    JP(mPrintRadioLine);


Adjectives:
    //table_width ['2', 'PeoplePlaces7.Adjectives']
    //dw ['PnP_CuteText'];
    //dw ['PnP_LazyText'];
    //dw ['PnP_HappyText'];
    //dw ['PnP_NoisyText'];
    //dw ['PnP_PrecociousText'];
    //dw ['PnP_BoldText'];
    //dw ['PnP_PickyText'];
    //dw ['PnP_SortOfOKText'];
    //dw ['PnP_SoSoText'];
    //dw ['PnP_GreatText'];
    //dw ['PnP_MyTypeText'];
    //dw ['PnP_CoolText'];
    //dw ['PnP_InspiringText'];
    //dw ['PnP_WeirdText'];
    //dw ['PnP_RightForMeText'];
    //dw ['PnP_OddText'];
    //assert_table_length ['NUM_PNP_PLACES_ADJECTIVES']

    return RocketRadio1();
}

void RocketRadio1(void){
    CALL(aStartRadioStation);
    LD_HL(mRocketRadioText1);
    LD_A(ROCKET_RADIO_2);
    JP(mNextRadioLine);

}

void RocketRadio2(void){
    LD_HL(mRocketRadioText2);
    LD_A(ROCKET_RADIO_3);
    JP(mNextRadioLine);

}

void RocketRadio3(void){
    LD_HL(mRocketRadioText3);
    LD_A(ROCKET_RADIO_4);
    JP(mNextRadioLine);

}

void RocketRadio4(void){
    LD_HL(mRocketRadioText4);
    LD_A(ROCKET_RADIO_5);
    JP(mNextRadioLine);

}

void RocketRadio5(void){
    LD_HL(mRocketRadioText5);
    LD_A(ROCKET_RADIO_6);
    JP(mNextRadioLine);

}

void RocketRadio6(void){
    LD_HL(mRocketRadioText6);
    LD_A(ROCKET_RADIO_7);
    JP(mNextRadioLine);

}

void RocketRadio7(void){
    LD_HL(mRocketRadioText7);
    LD_A(ROCKET_RADIO_8);
    JP(mNextRadioLine);

}

void RocketRadio8(void){
    LD_HL(mRocketRadioText8);
    LD_A(ROCKET_RADIO_9);
    JP(mNextRadioLine);

}

void RocketRadio9(void){
    LD_HL(mRocketRadioText9);
    LD_A(ROCKET_RADIO_10);
    JP(mNextRadioLine);

}

void RocketRadio10(void){
    LD_HL(mRocketRadioText10);
    LD_A(ROCKET_RADIO);
    JP(mNextRadioLine);

}

void RocketRadioText1(void){
    //text_far ['_RocketRadioText1']
    //text_end ['?']

    return RocketRadioText2();
}

void RocketRadioText2(void){
    //text_far ['_RocketRadioText2']
    //text_end ['?']

    return RocketRadioText3();
}

void RocketRadioText3(void){
    //text_far ['_RocketRadioText3']
    //text_end ['?']

    return RocketRadioText4();
}

void RocketRadioText4(void){
    //text_far ['_RocketRadioText4']
    //text_end ['?']

    return RocketRadioText5();
}

void RocketRadioText5(void){
    //text_far ['_RocketRadioText5']
    //text_end ['?']

    return RocketRadioText6();
}

void RocketRadioText6(void){
    //text_far ['_RocketRadioText6']
    //text_end ['?']

    return RocketRadioText7();
}

void RocketRadioText7(void){
    //text_far ['_RocketRadioText7']
    //text_end ['?']

    return RocketRadioText8();
}

void RocketRadioText8(void){
    //text_far ['_RocketRadioText8']
    //text_end ['?']

    return RocketRadioText9();
}

void RocketRadioText9(void){
    //text_far ['_RocketRadioText9']
    //text_end ['?']

    return RocketRadioText10();
}

void RocketRadioText10(void){
    //text_far ['_RocketRadioText10']
    //text_end ['?']

    return PokeFluteRadio();
}

void PokeFluteRadio(void){
    CALL(aStartRadioStation);
    LD_A(1);
    LD_addr_A(wNumRadioLinesPrinted);
    RET;

}

void UnownRadio(void){
    CALL(aStartRadioStation);
    LD_A(1);
    LD_addr_A(wNumRadioLinesPrinted);
    RET;

}

void EvolutionRadio(void){
    CALL(aStartRadioStation);
    LD_A(1);
    LD_addr_A(wNumRadioLinesPrinted);
    RET;

}

void BuenasPassword1(void){
//  Determine if we need to be here
    CALL(aBuenasPasswordCheckTime);
    JP_NC (mBuenasPassword1_PlayPassword);
    LD_A_addr(wNumRadioLinesPrinted);
    AND_A_A;
    JP_Z (mBuenasPassword20);
    JP(mBuenasPassword8);


PlayPassword:
    CALL(aStartRadioStation);
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_DE(mBuenasPasswordChannelName);
    hlcoord(2, 9, wTilemap);
    CALL(aPlaceString);
    POP_AF;
    LDH_addr_A(hBGMapMode);
    LD_HL(mBuenaRadioText1);
    LD_A(BUENAS_PASSWORD_2);
    JP(mNextRadioLine);

}

void BuenasPassword2(void){
    LD_HL(mBuenaRadioText2);
    LD_A(BUENAS_PASSWORD_3);
    JP(mNextRadioLine);

}

void BuenasPassword3(void){
    CALL(aBuenasPasswordCheckTime);
    LD_HL(mBuenaRadioText3);
    JP_C (mBuenasPasswordAfterMidnight);
    LD_A(BUENAS_PASSWORD_4);
    JP(mNextRadioLine);

}

void BuenasPassword4(void){
    CALL(aBuenasPasswordCheckTime);
    JP_C (mBuenasPassword8);
    LD_A_addr(wBuenasPassword);
//  If we already generated the password today, we don't need to generate a new one.
    LD_HL(wDailyFlags2);
    BIT_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
    IF_NZ goto AlreadyGotIt;
//  There are only 11 groups to choose from.

greater_than_11:
    CALL(aRandom);
    maskbits(NUM_PASSWORD_CATEGORIES, 0);
    CP_A(NUM_PASSWORD_CATEGORIES);
    IF_NC goto greater_than_11;
//  Store it in the high nybble of e.
    SWAP_A;
    LD_E_A;
//  For each group, choose one of the three passwords.

greater_than_three:
    CALL(aRandom);
    maskbits(NUM_PASSWORDS_PER_CATEGORY, 0);
    CP_A(NUM_PASSWORDS_PER_CATEGORY);
    IF_NC goto greater_than_three;
//  The high nybble of wBuenasPassword will now contain the password group index, and the low nybble contains the actual password.
    ADD_A_E;
    LD_addr_A(wBuenasPassword);
//  Set the flag so that we don't generate a new password this week.
    LD_HL(wDailyFlags2);
    SET_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);

AlreadyGotIt:
    LD_C_A;
    CALL(aGetBuenasPassword);
    LD_HL(mBuenaRadioText4);
    LD_A(BUENAS_PASSWORD_5);
    JP(mNextRadioLine);

}

void GetBuenasPassword(void){
//  The password indices are held in c.  High nybble contains the group index, low nybble contains the word index.
//  Load the password group pointer in hl.
    LD_A_C;
    SWAP_A;
    AND_A(0xf);
    LD_HL(mBuenasPasswordTable);
    LD_D(0);
    LD_E_A;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
//  Get the password type and store it in b.
    LD_A_hli;
    LD_B_A;
    PUSH_HL;
    INC_HL;
//  Get the password index.
    LD_A_C;
    AND_A(0xf);
    LD_C_A;
    PUSH_HL;
    LD_HL(mGetBuenasPassword_StringFunctionJumptable);
    LD_E_B;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_DE;  // de now contains the pointer to the value of this week's password, in Blue Card Points.
    CALL(av_hl_);
    POP_HL;
    LD_C_hl;
    RET;


StringFunctionJumptable:
//  entries correspond to BUENA_* constants
    //table_width ['2', 'GetBuenasPassword.StringFunctionJumptable']
    //dw ['.Mon'];  // BUENA_MON
    //dw ['.Item'];  // BUENA_ITEM
    //dw ['.Move'];  // BUENA_MOVE
    //dw ['.RawString'];  // BUENA_STRING
    //assert_table_length ['NUM_BUENA_FUNCTIONS']


Mon:
    CALL(aGetBuenasPassword_GetTheIndex);
    CALL(aGetPokemonName);
    RET;


Item:
    CALL(aGetBuenasPassword_GetTheIndex);
    CALL(aGetItemName);
    RET;


Move:
    CALL(aGetBuenasPassword_GetTheIndex);
    CALL(aGetMoveName);
    RET;


GetTheIndex:
    LD_H(0);
    LD_L_C;
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    RET;


RawString:
//  Get the string from the table...
    LD_A_C;
    AND_A_A;
    IF_Z goto skip;

read_loop:
    LD_A_de;
    INC_DE;
    CP_A(0x50);
    IF_NZ goto read_loop;
    DEC_C;
    IF_NZ goto read_loop;
//  ... and copy it into wStringBuffer1.

skip:
    LD_HL(wStringBuffer1);

copy_loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    CP_A(0x50);
    IF_NZ goto copy_loop;
    LD_DE(wStringBuffer1);
    RET;

// INCLUDE "data/radio/buenas_passwords.asm"

    return BuenasPassword5();
}

void BuenasPassword5(void){
    LD_HL(mBuenaRadioText5);
    LD_A(BUENAS_PASSWORD_6);
    JP(mNextRadioLine);

}

void BuenasPassword6(void){
    LD_HL(mBuenaRadioText6);
    LD_A(BUENAS_PASSWORD_7);
    JP(mNextRadioLine);

}

void BuenasPassword7(void){
    CALL(aBuenasPasswordCheckTime);
    LD_HL(mBuenaRadioText7);
    JR_C (mBuenasPasswordAfterMidnight);
    LD_A(BUENAS_PASSWORD);
    JP(mNextRadioLine);

}

void BuenasPasswordAfterMidnight(void){
    PUSH_HL;
    LD_HL(wDailyFlags2);
    RES_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
    POP_HL;
    LD_A(BUENAS_PASSWORD_8);
    JP(mNextRadioLine);

}

void BuenasPassword8(void){
    LD_HL(wDailyFlags2);
    RES_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
    LD_HL(mBuenaRadioMidnightText10);
    LD_A(BUENAS_PASSWORD_9);
    JP(mNextRadioLine);

}

void BuenasPassword9(void){
    LD_HL(mBuenaRadioMidnightText1);
    LD_A(BUENAS_PASSWORD_10);
    JP(mNextRadioLine);

}

void BuenasPassword10(void){
    LD_HL(mBuenaRadioMidnightText2);
    LD_A(BUENAS_PASSWORD_11);
    JP(mNextRadioLine);

}

void BuenasPassword11(void){
    LD_HL(mBuenaRadioMidnightText3);
    LD_A(BUENAS_PASSWORD_12);
    JP(mNextRadioLine);

}

void BuenasPassword12(void){
    LD_HL(mBuenaRadioMidnightText4);
    LD_A(BUENAS_PASSWORD_13);
    JP(mNextRadioLine);

}

void BuenasPassword13(void){
    LD_HL(mBuenaRadioMidnightText5);
    LD_A(BUENAS_PASSWORD_14);
    JP(mNextRadioLine);

}

void BuenasPassword14(void){
    LD_HL(mBuenaRadioMidnightText6);
    LD_A(BUENAS_PASSWORD_15);
    JP(mNextRadioLine);

}

void BuenasPassword15(void){
    LD_HL(mBuenaRadioMidnightText7);
    LD_A(BUENAS_PASSWORD_16);
    JP(mNextRadioLine);

}

void BuenasPassword16(void){
    LD_HL(mBuenaRadioMidnightText8);
    LD_A(BUENAS_PASSWORD_17);
    JP(mNextRadioLine);

}

void BuenasPassword17(void){
    LD_HL(mBuenaRadioMidnightText9);
    LD_A(BUENAS_PASSWORD_18);
    JP(mNextRadioLine);

}

void BuenasPassword18(void){
    LD_HL(mBuenaRadioMidnightText10);
    LD_A(BUENAS_PASSWORD_19);
    JP(mNextRadioLine);

}

void BuenasPassword19(void){
    LD_HL(mBuenaRadioMidnightText10);
    LD_A(BUENAS_PASSWORD_20);
    JP(mNextRadioLine);

}

void BuenasPassword20(void){
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    FARCALL(aNoRadioMusic);
    FARCALL(aNoRadioName);
    POP_AF;
    LDH_addr_A(hBGMapMode);
    LD_HL(wDailyFlags2);
    RES_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
    LD_A(BUENAS_PASSWORD);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    LD_HL(mBuenaOffTheAirText);
    LD_A(BUENAS_PASSWORD_21);
    JP(mNextRadioLine);

}

void BuenasPassword21(void){
    LD_A(BUENAS_PASSWORD);
    LD_addr_A(wCurRadioLine);
    XOR_A_A;
    LD_addr_A(wNumRadioLinesPrinted);
    CALL(aBuenasPasswordCheckTime);
    JP_NC (mBuenasPassword1);
    LD_HL(mBuenaOffTheAirText);
    LD_A(BUENAS_PASSWORD_21);
    JP(mNextRadioLine);

}

void BuenasPasswordCheckTime(void){
    CALL(aUpdateTime);
    LDH_A_addr(hHours);
    CP_A(NITE_HOUR);
    RET;

}

void BuenasPasswordChannelName(void){
    //db ['"BUENA\'S PASSWORD@"'];

    return BuenaRadioText1();
}

void BuenaRadioText1(void){
    //text_far ['_BuenaRadioText1']
    //text_end ['?']

    return BuenaRadioText2();
}

void BuenaRadioText2(void){
    //text_far ['_BuenaRadioText2']
    //text_end ['?']

    return BuenaRadioText3();
}

void BuenaRadioText3(void){
    //text_far ['_BuenaRadioText3']
    //text_end ['?']

    return BuenaRadioText4();
}

void BuenaRadioText4(void){
    //text_far ['_BuenaRadioText4']
    //text_end ['?']

    return BuenaRadioText5();
}

void BuenaRadioText5(void){
    //text_far ['_BuenaRadioText5']
    //text_end ['?']

    return BuenaRadioText6();
}

void BuenaRadioText6(void){
    //text_far ['_BuenaRadioText6']
    //text_end ['?']

    return BuenaRadioText7();
}

void BuenaRadioText7(void){
    //text_far ['_BuenaRadioText7']
    //text_end ['?']

    return BuenaRadioMidnightText1();
}

void BuenaRadioMidnightText1(void){
    //text_far ['_BuenaRadioMidnightText1']
    //text_end ['?']

    return BuenaRadioMidnightText2();
}

void BuenaRadioMidnightText2(void){
    //text_far ['_BuenaRadioMidnightText2']
    //text_end ['?']

    return BuenaRadioMidnightText3();
}

void BuenaRadioMidnightText3(void){
    //text_far ['_BuenaRadioMidnightText3']
    //text_end ['?']

    return BuenaRadioMidnightText4();
}

void BuenaRadioMidnightText4(void){
    //text_far ['_BuenaRadioMidnightText4']
    //text_end ['?']

    return BuenaRadioMidnightText5();
}

void BuenaRadioMidnightText5(void){
    //text_far ['_BuenaRadioMidnightText5']
    //text_end ['?']

    return BuenaRadioMidnightText6();
}

void BuenaRadioMidnightText6(void){
    //text_far ['_BuenaRadioMidnightText6']
    //text_end ['?']

    return BuenaRadioMidnightText7();
}

void BuenaRadioMidnightText7(void){
    //text_far ['_BuenaRadioMidnightText7']
    //text_end ['?']

    return BuenaRadioMidnightText8();
}

void BuenaRadioMidnightText8(void){
    //text_far ['_BuenaRadioMidnightText8']
    //text_end ['?']

    return BuenaRadioMidnightText9();
}

void BuenaRadioMidnightText9(void){
    //text_far ['_BuenaRadioMidnightText9']
    //text_end ['?']

    return BuenaRadioMidnightText10();
}

void BuenaRadioMidnightText10(void){
    //text_far ['_BuenaRadioMidnightText10']
    //text_end ['?']

    return BuenaOffTheAirText();
}

void BuenaOffTheAirText(void){
    //text_far ['_BuenaOffTheAirText']
    //text_end ['?']

    return CopyRadioTextToRAM();
}

void CopyRadioTextToRAM(void){
    LD_A_hl;
    CP_A(TX_FAR);
    JP_Z (mFarCopyRadioText);
    LD_DE(wRadioText);
    LD_BC(2 * SCREEN_WIDTH);
    JP(mCopyBytes);

}

void StartRadioStation(void){
    LD_A_addr(wNumRadioLinesPrinted);
    AND_A_A;
    RET_NZ ;
    CALL(aRadioTerminator);
    CALL(aPrintText);
    LD_HL(mRadioChannelSongs);
    LD_A_addr(wCurRadioLine);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALLFAR(aRadioMusicRestartDE);
    RET;

// INCLUDE "data/radio/channel_music.asm"

    return NextRadioLine();
}

void NextRadioLine(void){
    PUSH_AF;
    CALL(aCopyRadioTextToRAM);
    POP_AF;
    JP(mPrintRadioLine);

}

void StartRadioStation_Conv(void){
    if(gb_read(wNumRadioLinesPrinted) != 0)
        return;

    CALL(aRadioTerminator);
    CALL(aPrintText);

    uint16_t hl = mRadioChannelSongs + (gb_read(wCurRadioLine) * 2);
    RadioMusicRestartDE_Conv(gb_read16(hl));

// INCLUDE "data/radio/channel_music.asm"

    return NextRadioLine_Conv();
}

void NextRadioLine_Conv(void){
    PUSH_AF;
    CALL(aCopyRadioTextToRAM);
    POP_AF;
    PrintRadioLine_Conv(gb_read(wCurRadioLine));
}
