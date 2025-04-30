#include "../../constants.h"
#include "radio.h"
#include "pokegear.h"
#include "../../home/array.h"
#include "../../home/copy.h"
#include "../../home/region.h"
#include "../../home/text.h"
#include "../../home/time.h"
#include "../../home/copy_name.h"
#include "../../home/random.h"
#include "../../home/names.h"
#include "../../home/map.h"
#include "../../home/tilemap.h"
#include "../../home/pokedex_flags.h"
#include "../../home/print_text.h"
#include "../overworld/landmarks.h"
#include "../battle/read_trainer_attributes.h"
#include "../battle/read_trainer_party.h"
#include "../../data/text/common.h"
#include "../../data/pokemon/dex_entries.h"
#include "../../data/radio/channel_music.h"
#include "../../data/radio/oaks_pkmn_talk_routes.h"
#include "../../data/radio/pnp_hidden_people.h"
#include "../../data/radio/pnp_places.h"
#include "../../data/radio/buenas_passwords.h"
#include "../../data/wild/johto_grass.h"
#include "../events/specials.h"
#include "../../charmap.h"

const struct TextCmd* gRadioText = NULL;
static struct TextCmd gPokedexShowText[2];
static uint8_t gPokedexShowDescBuffer[128];
static uint8_t* gPokedexShowDescPtr;
static uint8_t gPokedexShowTextBuffer[SCREEN_WIDTH*2];
static uint8_t* gPokedexShowTextPtr;

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
    if((wram->wCurRadioLine < POKE_FLUTE_RADIO)
    && (bit_test(wram->wStatusFlags2, STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F))
    && (IsInJohto() == JOHTO_REGION))
    {
        //  Team Rocket broadcasts on all stations.
        wram->wCurRadioLine = ROCKET_RADIO;
    }
    //  Jump to the currently loaded station.  The index to which we need to jump is in wCurRadioLine.
    // CALL(aRadioJumptable);
    RadioJumptable();
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
    [RADIO_SCROLL] = RadioScroll_Conv,
//  More Pokemon Channel stuff
    [POKEDEX_SHOW_6] = PokedexShow6,
    [POKEDEX_SHOW_7] = PokedexShow7,
    [POKEDEX_SHOW_8] = PokedexShow8,
};

static_assert(lengthof(Radio_Stations) == NUM_RADIO_SEGMENTS, "");

void RadioJumptable(void){
//  entries correspond to constants/radio_constants.asm
    return Radio_Stations[wram->wCurRadioLine]();
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
    wram->wNextRadioLine = a;
    // REG_HL = wRadioText;
    uint8_t lines_printed = wram->wNumRadioLinesPrinted;
    if(lines_printed >= 2)
    {
        // REG_A = lines_printed;
        // CALL(aPrintTextboxText);
        PrintTextboxText(gRadioText);
    }
    else 
    {
        // gb_write(++REG_HL, TX_START);
        wram->wNumRadioLinesPrinted = ++lines_printed;
        if(lines_printed != 2)
        {
            // REG_A = lines_printed;
            // CALL(aPrintTextboxText);
            PrintTextboxText(gRadioText);
        }
        else 
        {
            // bccoord(1, 16, wTilemap);
            // CALL(aPlaceHLTextAtBC);
            PlaceHLTextAtBC(coord(1, 16, wram->wTilemap), gRadioText);
        }
    }
    wram->wCurRadioLine = RADIO_SCROLL;
    wram->wRadioTextDelay = 100;
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
    if(wram->wRadioTextDelay == 0)
    {
        wram->wCurRadioLine = wram->wNextRadioLine;

        if(wram->wNumRadioLinesPrinted != 0)
        {
            // CALL(aCopyBottomLineToTopLine);
            CopyBottomLineToTopLine();
        }
        // JP(mClearBottomLine);
        return ClearBottomLine();
    }
    wram->wRadioTextDelay--;
}

void OaksPKMNTalk1(void){
    // LD_A(5);
    // LD_addr_A(wOaksPKMNTalkSegmentCounter);
    wram->wOaksPKMNTalkSegmentCounter = 5;
    // CALL(aStartRadioStation);
    StartRadioStation_Conv();
    // LD_HL(mOPT_IntroText1);
    // LD_A(OAKS_POKEMON_TALK_2);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(OPT_IntroText1, OAKS_POKEMON_TALK_2);
}

void OaksPKMNTalk2(void){
    // LD_HL(mOPT_IntroText2);
    // LD_A(OAKS_POKEMON_TALK_3);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(OPT_IntroText2, OAKS_POKEMON_TALK_3);
}

void OaksPKMNTalk3(void){
    // LD_HL(mOPT_IntroText3);
    // LD_A(OAKS_POKEMON_TALK_4);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(OPT_IntroText3, OAKS_POKEMON_TALK_4);
}

//  Choose a random route, and a random Pokemon from that route.
void OaksPKMNTalk4(void){
    uint8_t a;
// sample:
    do {
        // CALL(aRandom);
        // AND_A(0b11111);
        a = Random() & 0b11111;
        // CP_A((aOaksPKMNTalkRoutes_End - aOaksPKMNTalkRoutes) / 2);
        // IF_NC goto sample;
    } while(a >= OaksPKMNTalkRoutes_Size);
    // LD_HL(mOaksPKMNTalkRoutes);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_B_hl;
    // INC_HL;
    // LD_C_hl;
    struct MapId map = OaksPKMNTalkRoutes[a];
// bc now contains the chosen map's group and number indices.
    // PUSH_BC;

// Search the JohtoGrassWildMons array for the chosen map.
    // LD_HL(mJohtoGrassWildMons);
    const struct WildGrassMons* hl = JohtoGrassWildMons;

    uint32_t i = 0;
    while(1) {
    // loop:
        // LD_A(BANK(aJohtoGrassWildMons));
        // CALL(aGetFarByte);
        // CP_A(-1);
        // IF_Z goto overflow;
        if(hl[i].mapGroup == 0xff) {
        // overflow:
            // POP_BC;
            // LD_A(OAKS_POKEMON_TALK);
            // JP(mPrintRadioLine);
            return PrintRadioLine_Conv(OAKS_POKEMON_TALK);
        }
        // INC_HL;
        // CP_A_B;
        // IF_NZ goto next;
        // LD_A(BANK(aJohtoGrassWildMons));
        // CALL(aGetFarByte);
        // CP_A_C;
        // IF_Z goto done;
        if(hl[i].mapGroup == map.mapGroup && hl[i].mapNumber == map.mapNumber)
            break;

    // next:
        // DEC_HL;
        // LD_DE(GRASS_WILDDATA_LENGTH);
        // ADD_HL_DE;
        // goto loop;
        i++;
    }


// done:
// Point hl to the list of morning Pokémon., skipping percentages
    // for(int rept = 0; rept < 4; rept++){
    // INC_HL;
    // }
// Generate a number, either 0, 1, or 2, to choose a time of day.

    uint8_t tod;
    do {
    // loop2:
        // CALL(aRandom);
        // maskbits(NUM_DAYTIMES, 0);
        tod = Random() & 3;
        // CP_A(DARKNESS_F);
        // IF_Z goto loop2;
    } while(tod == DARKNESS_F);

    // LD_BC(2 * NUM_GRASSMON);
    // CALL(aAddNTimes);

    uint8_t whichMon;
    do {
    // loop3:
    // Choose one of the middle three Pokemon.
        // CALL(aRandom);
        // maskbits(NUM_GRASSMON, 0);
        whichMon = Random() & NUM_GRASSMON;
        // CP_A(2);
        // IF_C goto loop3;
        // CP_A(5);
        // IF_NC goto loop3;
    } while(whichMon < 2 || whichMon >= 5);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // INC_HL;  // skip level
    // LD_A(BANK(aJohtoGrassWildMons));
    printf("Picked map %d at tod %d.\n", i, tod);
    for(int j = 0; j < 7; ++j) {
        printf("    mon lvl=%d, species=%d\n", hl[i].mons[tod][j].level, hl[i].mons[tod][j].species);
    }
    // CALL(aGetFarByte);
    species_t species = hl[i].mons[tod][whichMon].species;
    printf("species=%d, tod=%d, mon=%d\n", species, tod, whichMon);
    // LD_addr_A(wNamedObjectIndex);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wMonOrItemNameBuffer, GetPokemonName(species), MON_NAME_LENGTH);

// Now that we've chosen our wild Pokemon,
// let's recover the map index info and get its name.
    // POP_BC;
    // CALL(aGetWorldMapLocation);
    // LD_E_A;
    // FARCALL(aGetLandmarkName);
    GetLandmarkName_Conv(GetWorldMapLocation(map.mapGroup, map.mapNumber));
    // LD_HL(mOPT_OakText1);
    // CALL(aCopyRadioTextToRAM);
    CopyRadioTextToRAM_Conv(OPT_OakText1);
    // LD_A(OAKS_POKEMON_TALK_5);
    // JP(mPrintRadioLine);
    return PrintRadioLine_Conv(OAKS_POKEMON_TALK_5);
// INCLUDE "data/radio/oaks_pkmn_talk_routes.asm"
}

void OaksPKMNTalk5(void){
    // LD_HL(mOPT_OakText2);
    // LD_A(OAKS_POKEMON_TALK_6);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(OPT_OakText2, OAKS_POKEMON_TALK_6);
}

void OaksPKMNTalk6(void){
    // LD_HL(mOPT_OakText3);
    // LD_A(OAKS_POKEMON_TALK_7);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(OPT_OakText3, OAKS_POKEMON_TALK_7);
}

const txt_cmd_s OPT_IntroText1[] = {
    text_far(v_OPT_IntroText1)
    text_end
};

const txt_cmd_s OPT_IntroText2[] = {
    text_far(v_OPT_IntroText2)
    text_end
};

const txt_cmd_s OPT_IntroText3[] = {
    text_far(v_OPT_IntroText3)
    text_end
};

const txt_cmd_s OPT_OakText1[] = {
    text_far(v_OPT_OakText1)
    text_end
};

const txt_cmd_s OPT_OakText2[] = {
    text_far(v_OPT_OakText2)
    text_end
};

const txt_cmd_s OPT_OakText3[] = {
    text_far(v_OPT_OakText3)
    text_end
};

void OaksPKMNTalk7(void){
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wCurPartySpecies);
    // LD_HL(mOPT_MaryText1);
    // LD_A(OAKS_POKEMON_TALK_8);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(OPT_MaryText1, OAKS_POKEMON_TALK_8);
}

const txt_cmd_s OPT_MaryText1[] = {
    text_far(v_OPT_MaryText1)
    text_end
};

void OaksPKMNTalk8(void){
    static const txt_cmd_s OPT_SweetAdorablyText[] = {
        text_far(v_OPT_SweetAdorablyText)
        text_end
    };
    static const txt_cmd_s OPT_WigglySlicklyText[] = {
        text_far(v_OPT_WigglySlicklyText)
        text_end
    };
    static const txt_cmd_s OPT_AptlyNamedText[] = {
        text_far(v_OPT_AptlyNamedText)
        text_end
    };
    static const txt_cmd_s OPT_UndeniablyKindOfText[] = {
        text_far(v_OPT_UndeniablyKindOfText)
        text_end
    };
    static const txt_cmd_s OPT_UnbearablyText[] = {
        text_far(v_OPT_UnbearablyText)
        text_end
    };
    static const txt_cmd_s OPT_WowImpressivelyText[] = {
        text_far(v_OPT_WowImpressivelyText)
        text_end
    };
    static const txt_cmd_s OPT_AlmostPoisonouslyText[] = {
        text_far(v_OPT_AlmostPoisonouslyText)
        text_end
    };
    static const txt_cmd_s OPT_SensuallyText[] = {
        text_far(v_OPT_SensuallyText)
        text_end
    };
    static const txt_cmd_s OPT_MischievouslyText[] = {
        text_far(v_OPT_MischievouslyText)
        text_end
    };
    static const txt_cmd_s OPT_TopicallyText[] = {
        text_far(v_OPT_TopicallyText)
        text_end
    };
    static const txt_cmd_s OPT_AddictivelyText[] = {
        text_far(v_OPT_AddictivelyText)
        text_end
    };
    static const txt_cmd_s OPT_LooksInWaterText[] = {
        text_far(v_OPT_LooksInWaterText)
        text_end
    };
    static const txt_cmd_s OPT_EvolutionMustBeText[] = {
        text_far(v_OPT_EvolutionMustBeText)
        text_end
    };
    static const txt_cmd_s OPT_ProvocativelyText[] = {
        text_far(v_OPT_ProvocativelyText)
        text_end
    };
    static const txt_cmd_s OPT_FlippedOutText[] = {
        text_far(v_OPT_FlippedOutText)
        text_end
    };
    static const txt_cmd_s OPT_HeartMeltinglyText[] = {
        text_far(v_OPT_HeartMeltinglyText)
        text_end
    };
    static const struct TextCmd* const Adverbs[] = {
        //table_width ['2', 'OaksPKMNTalk8.Adverbs']
        OPT_SweetAdorablyText,
        OPT_WigglySlicklyText,
        OPT_AptlyNamedText,
        OPT_UndeniablyKindOfText,
        OPT_UnbearablyText,
        OPT_WowImpressivelyText,
        OPT_AlmostPoisonouslyText,
        OPT_SensuallyText,
        OPT_MischievouslyText,
        OPT_TopicallyText,
        OPT_AddictivelyText,
        OPT_LooksInWaterText,
        OPT_EvolutionMustBeText,
        OPT_ProvocativelyText,
        OPT_FlippedOutText,
        OPT_HeartMeltinglyText,
    };
    static_assert(lengthof(Adverbs) == NUM_OAKS_POKEMON_TALK_ADVERBS, "");

// 0-15 are all valid indexes into .Adverbs,
// so no need for a retry loop
    // CALL(aRandom);
    // maskbits(NUM_OAKS_POKEMON_TALK_ADVERBS, 0);
    uint8_t a = Random() & 0xf;
    //assert_power_of_2 ['NUM_OAKS_POKEMON_TALK_ADVERBS']
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mOaksPKMNTalk8_Adverbs);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A(OAKS_POKEMON_TALK_9);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(Adverbs[a], OAKS_POKEMON_TALK_9);
}

void OaksPKMNTalk9(void){
    static const txt_cmd_s OPT_CuteText[] = {
        text_far(v_OPT_CuteText)
        text_end
    };
    static const txt_cmd_s OPT_WeirdText[] = {
        text_far(v_OPT_WeirdText)
        text_end
    };
    static const txt_cmd_s OPT_PleasantText[] = {
        text_far(v_OPT_PleasantText)
        text_end
    };
    static const txt_cmd_s OPT_BoldSortOfText[] = {
        text_far(v_OPT_BoldSortOfText)
        text_end
    };
    static const txt_cmd_s OPT_FrighteningText[] = {
        text_far(v_OPT_FrighteningText)
        text_end
    };
    static const txt_cmd_s OPT_SuaveDebonairText[] = {
        text_far(v_OPT_SuaveDebonairText)
        text_end
    };
    static const txt_cmd_s OPT_PowerfulText[] = {
        text_far(v_OPT_PowerfulText)
        text_end
    };
    static const txt_cmd_s OPT_ExcitingText[] = {
        text_far(v_OPT_ExcitingText)
        text_end
    };
    static const txt_cmd_s OPT_GroovyText[] = {
        text_far(v_OPT_GroovyText)
        text_end
    };
    static const txt_cmd_s OPT_InspiringText[] = {
        text_far(v_OPT_InspiringText)
        text_end
    };
    static const txt_cmd_s OPT_FriendlyText[] = {
        text_far(v_OPT_FriendlyText)
        text_end
    };
    static const txt_cmd_s OPT_HotHotHotText[] = {
        text_far(v_OPT_HotHotHotText)
        text_end
    };
    static const txt_cmd_s OPT_StimulatingText[] = {
        text_far(v_OPT_StimulatingText)
        text_end
    };
    static const txt_cmd_s OPT_GuardedText[] = {
        text_far(v_OPT_GuardedText)
        text_end
    };
    static const txt_cmd_s OPT_LovelyText[] = {
        text_far(v_OPT_LovelyText)
        text_end
    };
    static const txt_cmd_s OPT_SpeedyText[] = {
        text_far(v_OPT_SpeedyText)
        text_end
    };
    static const struct TextCmd* const Adjectives[] = {
        //table_width ['2', 'OaksPKMNTalk9.Adjectives']
        OPT_CuteText,
        OPT_WeirdText,
        OPT_PleasantText,
        OPT_BoldSortOfText,
        OPT_FrighteningText,
        OPT_SuaveDebonairText,
        OPT_PowerfulText,
        OPT_ExcitingText,
        OPT_GroovyText,
        OPT_InspiringText,
        OPT_FriendlyText,
        OPT_HotHotHotText,
        OPT_StimulatingText,
        OPT_GuardedText,
        OPT_LovelyText,
        OPT_SpeedyText,
    };
    static_assert(lengthof(Adjectives) == NUM_OAKS_POKEMON_TALK_ADJECTIVES, "");

// 0-15 are all valid indexes into .Adjectives,
// so no need for a retry loop
    // CALL(aRandom);
    // maskbits(NUM_OAKS_POKEMON_TALK_ADJECTIVES, 0);
    //assert_power_of_2 ['NUM_OAKS_POKEMON_TALK_ADJECTIVES']
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mOaksPKMNTalk9_Adjectives);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct TextCmd* txt = Adjectives[Random() & 0xf];
    // LD_A_addr(wOaksPKMNTalkSegmentCounter);
    // DEC_A;
    // LD_addr_A(wOaksPKMNTalkSegmentCounter);
    // LD_A(OAKS_POKEMON_TALK_4);
    // IF_NZ goto ok;
    if(--wram->wOaksPKMNTalkSegmentCounter == 0) {
        // LD_A(5);
        // LD_addr_A(wOaksPKMNTalkSegmentCounter);
        wram->wOaksPKMNTalkSegmentCounter = 5;
        // LD_A(OAKS_POKEMON_TALK_10);
        return NextRadioLine_Conv(txt, OAKS_POKEMON_TALK_10);
    }

// ok:
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(txt, OAKS_POKEMON_TALK_4);
}

void OaksPKMNTalk10(void){
    // FARCALL(aRadioMusicRestartPokemonChannel);
    RadioMusicRestartPokemonChannel_Conv();
    // LD_HL(mOPT_RestartText);
    // CALL(aPrintText);
    PrintText(OPT_RestartText);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_HL(mOPT_PokemonChannelText);
    // CALL(aPrintText);
    PrintText(OPT_PokemonChannelText);
    // LD_A(OAKS_POKEMON_TALK_11);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = OAKS_POKEMON_TALK_11;
    // LD_A(100);
    // LD_addr_A(wRadioTextDelay);
    wram->wRadioTextDelay = 100;
    // RET;
}

const txt_cmd_s OPT_PokemonChannelText[] = {
    text_far(v_OPT_PokemonChannelText)
    text_end
};

const txt_cmd_s OPT_RestartText[] = {
    text_end
};

void OaksPKMNTalk11(void){
    static const char pokemon_string[] = "#MON@";
    // LD_HL(wRadioTextDelay);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wRadioTextDelay != 0)
        return;
    // hlcoord(9, 14, wTilemap);
    // LD_DE(mOaksPKMNTalk11_pokemon_string);
    // LD_A(OAKS_POKEMON_TALK_12);
    // JP(mPlaceRadioString);
    return PlaceRadioString_Conv(coord(9, 14, wram->wTilemap), U82CA(wram->wStringBuffer2, pokemon_string), OAKS_POKEMON_TALK_12);
}

void OaksPKMNTalk12(void){
    static const char pokemon_channel_string[] = "#MON Channel@";
    // LD_HL(wRadioTextDelay);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wRadioTextDelay != 0)
        return;
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mOaksPKMNTalk12_pokemon_channel_string);
    // LD_A(OAKS_POKEMON_TALK_13);
    // JP(mPlaceRadioString);
    return PlaceRadioString_Conv(coord(1, 16, wram->wTilemap), U82CA(wram->wStringBuffer2, pokemon_channel_string), OAKS_POKEMON_TALK_13);
}

void OaksPKMNTalk13(void){
    // LD_HL(wRadioTextDelay);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wRadioTextDelay != 0)
        return;
    // hlcoord(12, 16, wTilemap);
    // LD_DE(mOaksPKMNTalk13_terminator);
    // LD_A(OAKS_POKEMON_TALK_14);
    // JP(mPlaceRadioString);
    return PlaceRadioString_Conv(coord(12, 16, wram->wTilemap), U82C("@"), OAKS_POKEMON_TALK_14);
}

void OaksPKMNTalk14(void){
    // LD_HL(wRadioTextDelay);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wRadioTextDelay != 0)
        return;
    // LD_DE(MUSIC_POKEMON_TALK);
    // CALLFAR(aRadioMusicRestartDE);
    RadioMusicRestartDE_Conv(MUSIC_POKEMON_TALK);
    // LD_HL(mOaksPKMNTalk14_terminator);
    // CALL(aPrintText);
    PrintText((struct TextCmd[]){
        text_start("@")
        text_end
    });
    // LD_A(OAKS_POKEMON_TALK_4);
    // LD_addr_A(wNextRadioLine);
    wram->wNextRadioLine = OAKS_POKEMON_TALK_4;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(RADIO_SCROLL);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = RADIO_SCROLL;
    // LD_A(10);
    // LD_addr_A(wRadioTextDelay);
    wram->wRadioTextDelay = 10;
    // RET;
}

void PlaceRadioString(void){
    LD_addr_A(wCurRadioLine);
    LD_A(100);
    LD_addr_A(wRadioTextDelay);
    JP(mPlaceString);

}

void PlaceRadioString_Conv(tile_t* hl, uint8_t* de, uint8_t line){
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = line;
    // LD_A(100);
    // LD_addr_A(wRadioTextDelay);
    wram->wRadioTextDelay = 100;
    // JP(mPlaceString);
    return PlaceStringSimple(de, hl);
}

void CopyBottomLineToTopLine(void){
    // hlcoord(0, 15, wTilemap);
    // decoord(0, 13, wTilemap);
    // LD_BC(SCREEN_WIDTH * 2);
    // JP(mCopyBytes);
    CopyBytes(coord(0, 13, wram->wTilemap), coord(0, 15, wram->wTilemap), SCREEN_WIDTH * 2);
}

void ClearBottomLine(void){
    // hlcoord(1, 15, wTilemap);
    // LD_BC(SCREEN_WIDTH - 2);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(1, 15, wram->wTilemap), SCREEN_WIDTH - 2, 0x7f);
    // hlcoord(1, 16, wTilemap);
    // LD_BC(SCREEN_WIDTH - 2);
    // LD_A(0x7f);
    // JP(mByteFill);
    ByteFill(coord(1, 16, wram->wTilemap), SCREEN_WIDTH - 2, 0x7f);
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
    // CALL(aStartRadioStation);
    StartRadioStation_Conv();
    // TODO: Convert Pokedex Show
    // wram->wNumRadioLinesPrinted = 1;
    // return;

    uint8_t a;
    do {
        do {
        // loop:
            // CALL(aRandom);
            a = Random();
            // CP_A(NUM_POKEMON);
            // IF_NC goto loop;
        } while(a >= NUM_POKEMON);
        // LD_C_A;
        // PUSH_BC;
        // LD_A_C;
        // CALL(aCheckCaughtMon);
        // POP_BC;
        // IF_Z goto loop;
    } while(!CheckCaughtMon(a));
    // INC_C;
    // LD_A_C;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = a + 1;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wCurPartySpecies);
    // LD_HL(mPokedexShowText);
    // LD_A(POKEDEX_SHOW_2);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(PokedexShowText, POKEDEX_SHOW_2);
}

void PokedexShow2(void){
    // LD_A_addr(wCurPartySpecies);
    // DEC_A;
    species_t a = wram->wCurPartySpecies - 1;
    // LD_HL(mPokedexDataPointerTable);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A(BANK(aPokedexDataPointerTable));
    // CALL(aGetFarWord);
    const struct DexEntry* hl = PokedexDataPointerTable[a];
    ByteFill(gPokedexShowTextBuffer, sizeof(gPokedexShowTextBuffer), CHAR_TERM);
    gPokedexShowTextBuffer[0] = CHAR_LINE;
    U82CA(gPokedexShowDescBuffer, hl->description);
    gPokedexShowDescPtr = gPokedexShowDescBuffer;
    gPokedexShowTextPtr = gPokedexShowTextBuffer + 1;
    // CALL(aPokedexShow_GetDexEntryBank);
    // PUSH_AF;
    // PUSH_HL;
    // CALL(aCopyDexEntryPart1);
    uint8_t* dst = CopyDexEntryPart1_Conv();
    // DEC_HL;
    // LD_hl(0x57);
    *(dst - 1) = 0x57;
    gPokedexShowText[1].cmd = TX_END;
    // LD_HL(wPokedexShowPointerAddr);
    // CALL(aCopyRadioTextToRAM);
    CopyRadioTextToRAM_Conv(gPokedexShowText);
    // POP_HL;
    // POP_AF;
    // CALL(aCopyDexEntryPart2);
    uint8_t* de = CopyDexEntryPart2_Conv();
    // for(int rept = 0; rept < 4; rept++){
    // INC_HL;
    // }
    // LD_A_L;
    // LD_addr_A(wPokedexShowPointerAddr);
    // LD_A_H;
    // LD_addr_A(wPokedexShowPointerAddr + 1);
    gPokedexShowDescPtr = de;
    // LD_A(POKEDEX_SHOW_3);
    // JP(mPrintRadioLine);
    return PrintRadioLine_Conv(POKEDEX_SHOW_3);
}

void PokedexShow3(void){
    // CALL(aCopyDexEntry);
    CopyDexEntry_Conv();
    // LD_A(POKEDEX_SHOW_4);
    // JP(mPrintRadioLine);
    return PrintRadioLine_Conv(POKEDEX_SHOW_4);
}

void PokedexShow4(void){
    // CALL(aCopyDexEntry);
    CopyDexEntry_Conv();
    // LD_A(POKEDEX_SHOW_5);
    // JP(mPrintRadioLine);
    return PrintRadioLine_Conv(POKEDEX_SHOW_5);
}

void PokedexShow5(void){
    // CALL(aCopyDexEntry);
    CopyDexEntry_Conv();
    // LD_A(POKEDEX_SHOW_6);
    // JP(mPrintRadioLine);
    return PrintRadioLine_Conv(POKEDEX_SHOW_6);
}

void PokedexShow6(void){
    // CALL(aCopyDexEntry);
    CopyDexEntry_Conv();
    // LD_A(POKEDEX_SHOW_7);
    // JP(mPrintRadioLine);
    return PrintRadioLine_Conv(POKEDEX_SHOW_7);
}

void PokedexShow7(void){
    // CALL(aCopyDexEntry);
    CopyDexEntry_Conv();
    // LD_A(POKEDEX_SHOW_8);
    // JP(mPrintRadioLine);
    return PrintRadioLine_Conv(POKEDEX_SHOW_8);
}

void PokedexShow8(void){
    // CALL(aCopyDexEntry);
    CopyDexEntry_Conv();
    // LD_A(POKEDEX_SHOW);
    // JP(mPrintRadioLine);
    return PrintRadioLine_Conv(POKEDEX_SHOW);
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

void CopyDexEntry_Conv(void){
    // LD_A_addr(wPokedexShowPointerAddr);
    // LD_L_A;
    // LD_A_addr(wPokedexShowPointerAddr + 1);
    // LD_H_A;
    // LD_A_addr(wPokedexShowPointerBank);
    // PUSH_AF;
    // PUSH_HL;
    // CALL(aCopyDexEntryPart1);
    uint8_t* hl = CopyDexEntryPart1_Conv();
    // DEC_HL;
    // LD_hl(0x57);
    *(hl - 1) = 0x57;
    // LD_HL(wPokedexShowPointerAddr);
    // CALL(aCopyRadioTextToRAM);
    CopyRadioTextToRAM_Conv(gPokedexShowText);
    // POP_HL;
    // POP_AF;
    // CALL(aCopyDexEntryPart2);
    CopyDexEntryPart2_Conv();
    // RET;

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

uint8_t* CopyDexEntryPart1_Conv(void){
    // LD_DE(wPokedexShowPointerBank);
    // LD_BC(SCREEN_WIDTH - 1);
    // CALL(aFarCopyBytes);
    CopyBytes(gPokedexShowTextBuffer + 1, gPokedexShowDescPtr, SCREEN_WIDTH - 1);
    // LD_HL(wPokedexShowPointerAddr);
    // LD_hl(TX_START);
    gPokedexShowText[0].cmd = TX_RAM;
    // INC_HL;
    // LD_hl(0x4f);
    gPokedexShowText[0].ram = gPokedexShowTextBuffer;
    // INC_HL;
    uint8_t* hl2 = gPokedexShowTextBuffer;

    uint8_t a;
    do {
    // loop:
        // LD_A_hli;
        a = *(hl2++);
        // CP_A(0x50);
        // RET_Z ;
        // CP_A(0x4e);
        // RET_Z ;
        // CP_A(0x5f);
        // RET_Z ;
        // goto loop;
    } while(a != 0x50 && a != 0x4e && a != 0x5f);
    return hl2;
    // return CopyDexEntryPart2();
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

uint8_t* CopyDexEntryPart2_Conv(void){
    // LD_D_A;
    uint8_t* de = gPokedexShowDescPtr;
    uint8_t a;
    do {
    // loop:
        // LD_A_D;
        // CALL(aGetFarByte);
        a = *(de++);
        // INC_HL;
        // CP_A(0x50);
        // IF_Z goto okay;
        // CP_A(0x4e);
        // IF_Z goto okay;
        // CP_A(0x5f);
        // IF_NZ goto loop;
    } while(a != 0x50 && a != 0x4e && a != 0x5f);

// okay:
    // LD_A_L;
    // LD_addr_A(wPokedexShowPointerAddr);
    // LD_A_H;
    // LD_addr_A(wPokedexShowPointerAddr + 1);
    gPokedexShowDescPtr = de;
    // LD_A_D;
    // LD_addr_A(wPokedexShowPointerBank);
    return de;
    // RET;
}

const txt_cmd_s PokedexShowText[] = {
    text_far(v_PokedexShowText)
    text_end
};

void BenMonMusic1(void){
    // CALL(aStartPokemonMusicChannel);
    StartPokemonMusicChannel();
    // LD_HL(mBenIntroText1);
    // LD_A(POKEMON_MUSIC_2);
    // JP(mNextRadioLine);
    NextRadioLine_Conv(BenIntroText1, POKEMON_MUSIC_2);
}

void BenMonMusic2(void){
    // LD_HL(mBenIntroText2);
    // LD_A(POKEMON_MUSIC_3);
    // JP(mNextRadioLine);
    NextRadioLine_Conv(BenIntroText2, POKEMON_MUSIC_3);
}

void BenMonMusic3(void){
    // LD_HL(mBenIntroText3);
    // LD_A(POKEMON_MUSIC_4);
    // JP(mNextRadioLine);
    NextRadioLine_Conv(BenIntroText3, POKEMON_MUSIC_4);
}

void FernMonMusic1(void){
    // CALL(aStartPokemonMusicChannel);
    StartPokemonMusicChannel();
    // LD_HL(mFernIntroText1);
    // LD_A(LETS_ALL_SING_2);
    // JP(mNextRadioLine);
    NextRadioLine_Conv(FernIntroText1, LETS_ALL_SING_2);
}

void FernMonMusic2(void){
    // LD_HL(mFernIntroText2);
    // LD_A(POKEMON_MUSIC_4);
    // JP(mNextRadioLine);
    NextRadioLine_Conv(FernIntroText2, POKEMON_MUSIC_4);
}

void BenFernMusic4(void){
    // LD_HL(mBenFernText1);
    // LD_A(POKEMON_MUSIC_5);
    // JP(mNextRadioLine);
    NextRadioLine_Conv(BenFernText1, POKEMON_MUSIC_5);
}

void BenFernMusic5(void){
    // CALL(aGetWeekday);
    // AND_A(1);
    // LD_HL(mBenFernText2A);
    // IF_Z goto SunTueThurSun;
    // LD_HL(mBenFernText2B);
    if((GetWeekday() & 1) == 0) {
        return NextRadioLine_Conv(BenFernText2A, POKEMON_MUSIC_6);
    }
    else {
        return NextRadioLine_Conv(BenFernText2B, POKEMON_MUSIC_6);
    }
// SunTueThurSun:
    // LD_A(POKEMON_MUSIC_6);
    // JP(mNextRadioLine);
}

void BenFernMusic6(void){
    // CALL(aGetWeekday);
    // AND_A(1);
    // LD_HL(mBenFernText3A);
    // IF_Z goto SunTueThurSun;
    // LD_HL(mBenFernText3B);
    if((GetWeekday() & 1) == 0) {
        return NextRadioLine_Conv(BenFernText3A, POKEMON_MUSIC_7);
    }
    else {
        return NextRadioLine_Conv(BenFernText3B, POKEMON_MUSIC_7);
    }
// SunTueThurSun:
    // LD_A(POKEMON_MUSIC_7);
    // JP(mNextRadioLine);
}

void BenFernMusic7(void){
    // RET;
    return;
}

void StartPokemonMusicChannel(void){
    // CALL(aRadioTerminator);
    // CALL(aPrintText);
    PrintText(RadioTerminator());
    // LD_DE(MUSIC_POKEMON_MARCH);
    // CALL(aGetWeekday);
    // AND_A(1);
    // IF_Z goto SunTueThurSun;
    // LD_DE(MUSIC_POKEMON_LULLABY);
    if(GetWeekday() & 1) {
        RadioMusicRestartDE_Conv(MUSIC_POKEMON_LULLABY);
    }
    else {
    // SunTueThurSun:
        RadioMusicRestartDE_Conv(MUSIC_POKEMON_MARCH);
        // CALLFAR(aRadioMusicRestartDE);
    }
    // RET;
}

const txt_cmd_s BenIntroText1[] = {
    text_far(v_BenIntroText1)
    text_end
};

const txt_cmd_s BenIntroText2[] = {
    text_far(v_BenIntroText2)
    text_end
};

const txt_cmd_s BenIntroText3[] = {
    text_far(v_BenIntroText3)
    text_end
};

const txt_cmd_s FernIntroText1[] = {
    text_far(v_FernIntroText1)
    text_end
};

const txt_cmd_s FernIntroText2[] = {
    text_far(v_FernIntroText2)
    text_end
};

const txt_cmd_s BenFernText1[] = {
    text_far(v_BenFernText1)
    text_end
};

const txt_cmd_s BenFernText2A[] = {
    text_far(v_BenFernText2A)
    text_end
};

const txt_cmd_s BenFernText2B[] = {
    text_far(v_BenFernText2B)
    text_end
};

const txt_cmd_s BenFernText3A[] = {
    text_far(v_BenFernText3A)
    text_end
};

const txt_cmd_s BenFernText3B[] = {
    text_far(v_BenFernText3B)
    text_end
};

void LuckyNumberShow1(void){
    // CALL(aStartRadioStation);
    StartRadioStation_Conv();
    // CALLFAR(aCheckLuckyNumberShowFlag);
    CheckLuckyNumberShowFlag();
    // IF_NC goto dontreset;
    if(wram->wScriptVar) {
        // CALLFAR(aResetLuckyNumberShowFlag);
        ResetLuckyNumberShowFlag();
    }
// dontreset:
    // LD_HL(mLC_Text1);
    // LD_A(LUCKY_NUMBER_SHOW_2);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text1, LUCKY_NUMBER_SHOW_2);
}

void LuckyNumberShow2(void){
    // LD_HL(mLC_Text2);
    // LD_A(LUCKY_NUMBER_SHOW_3);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text2, LUCKY_NUMBER_SHOW_3);
}

void LuckyNumberShow3(void){
    // LD_HL(mLC_Text3);
    // LD_A(LUCKY_NUMBER_SHOW_4);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text3, LUCKY_NUMBER_SHOW_4);
}

void LuckyNumberShow4(void){
    // LD_HL(mLC_Text4);
    // LD_A(LUCKY_NUMBER_SHOW_5);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text4, LUCKY_NUMBER_SHOW_5);
}

void LuckyNumberShow5(void){
    // LD_HL(mLC_Text5);
    // LD_A(LUCKY_NUMBER_SHOW_6);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text5, LUCKY_NUMBER_SHOW_6);
}

void LuckyNumberShow6(void){
    // LD_HL(mLC_Text6);
    // LD_A(LUCKY_NUMBER_SHOW_7);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text6, LUCKY_NUMBER_SHOW_7);
}

void LuckyNumberShow7(void){
    // LD_HL(mLC_Text7);
    // LD_A(LUCKY_NUMBER_SHOW_8);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text7, LUCKY_NUMBER_SHOW_8);
}

void LuckyNumberShow8(void){
    // LD_HL(wStringBuffer1);
    // LD_DE(wLuckyIDNumber);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum(wram->wStringBuffer1, &wram->wLuckyIDNumber, PRINTNUM_LEADINGZEROS | 2, 5);
    // LD_A(0x50);
    // LD_addr_A(wStringBuffer1 + 5);
    wram->wStringBuffer1[5] = CHAR_TERM;
    // LD_HL(mLC_Text8);
    // LD_A(LUCKY_NUMBER_SHOW_9);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text8, LUCKY_NUMBER_SHOW_9);
}

void LuckyNumberShow9(void){
    // LD_HL(mLC_Text9);
    // LD_A(LUCKY_NUMBER_SHOW_10);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text9, LUCKY_NUMBER_SHOW_10);
}

void LuckyNumberShow10(void){
    // LD_HL(mLC_Text7);
    // LD_A(LUCKY_NUMBER_SHOW_11);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text7, LUCKY_NUMBER_SHOW_11);
}

void LuckyNumberShow11(void){
    // LD_HL(mLC_Text8);
    // LD_A(LUCKY_NUMBER_SHOW_12);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text8, LUCKY_NUMBER_SHOW_12);
}

void LuckyNumberShow12(void){
    // LD_HL(mLC_Text10);
    // LD_A(LUCKY_NUMBER_SHOW_13);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_Text10, LUCKY_NUMBER_SHOW_13);
}

void LuckyNumberShow13(void){
    // LD_HL(mLC_Text11);
    // CALL(aRandom);
    // AND_A_A;
    // LD_A(LUCKY_CHANNEL);
    // IF_NZ goto okay;
    if(Random() != 0) {
        return NextRadioLine_Conv(LC_Text11, LUCKY_CHANNEL);
    }
    else { // 1/256 chance.
    // LD_A(LUCKY_NUMBER_SHOW_14);
    // okay:
        // JP(mNextRadioLine);
        return NextRadioLine_Conv(LC_Text11, LUCKY_NUMBER_SHOW_14);
    }
}

void LuckyNumberShow14(void){
    // LD_HL(mLC_DragText1);
    // LD_A(LUCKY_NUMBER_SHOW_15);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_DragText1, LUCKY_NUMBER_SHOW_15);
}

void LuckyNumberShow15(void){
    // LD_HL(mLC_DragText2);
    // LD_A(LUCKY_CHANNEL);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(LC_DragText2, LUCKY_CHANNEL);
}

const txt_cmd_s LC_Text1[] = {
    text_far(v_LC_Text1)
    text_end
};

const txt_cmd_s LC_Text2[] = {
    text_far(v_LC_Text2)
    text_end
};

const txt_cmd_s LC_Text3[] = {
    text_far(v_LC_Text3)
    text_end
};

const txt_cmd_s LC_Text4[] = {
    text_far(v_LC_Text4)
    text_end
};

const txt_cmd_s LC_Text5[] = {
    text_far(v_LC_Text5)
    text_end
};

const txt_cmd_s LC_Text6[] = {
    text_far(v_LC_Text6)
    text_end
};

const txt_cmd_s LC_Text7[] = {
    text_far(v_LC_Text7)
    text_end
};

const txt_cmd_s LC_Text8[] = {
    text_far(v_LC_Text8)
    text_end
};

const txt_cmd_s LC_Text9[] = {
    text_far(v_LC_Text9)
    text_end
};

const txt_cmd_s LC_Text10[] = {
    text_far(v_LC_Text10)
    text_end
};

const txt_cmd_s LC_Text11[] = {
    text_far(v_LC_Text11)
    text_end
};

const txt_cmd_s LC_DragText1[] = {
    text_far(v_LC_DragText1)
    text_end
};

const txt_cmd_s LC_DragText2[] = {
    text_far(v_LC_DragText2)
    text_end
};

void PeoplePlaces1(void){
    // CALL(aStartRadioStation);
    StartRadioStation_Conv();
    // LD_HL(mPnP_Text1);
    // LD_A(PLACES_AND_PEOPLE_2);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(PnP_Text1, PLACES_AND_PEOPLE_2);
}

void PeoplePlaces2(void){
    // LD_HL(mPnP_Text2);
    // LD_A(PLACES_AND_PEOPLE_3);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(PnP_Text2, PLACES_AND_PEOPLE_3);
}

void PeoplePlaces3(void){
    // LD_HL(mPnP_Text3);
    // CALL(aRandom);
    // CP_A(49 percent - 1);
    // LD_A(PLACES_AND_PEOPLE_4);  // People
    // IF_C goto ok;
    if(Random() < 49 percent - 1) {
        return NextRadioLine_Conv(PnP_Text3, PLACES_AND_PEOPLE_4);
    }
    else {
        // LD_A(PLACES_AND_PEOPLE_6);  // Places
    // ok:
        // JP(mNextRadioLine);
        return NextRadioLine_Conv(PnP_Text3, PLACES_AND_PEOPLE_6);
    }
}

const txt_cmd_s PnP_Text1[] = {
    text_far(v_PnP_Text1)
    text_end
};

const txt_cmd_s PnP_Text2[] = {
    text_far(v_PnP_Text2)
    text_end
};

const txt_cmd_s PnP_Text3[] = {
    text_far(v_PnP_Text3)
    text_end
};

void PeoplePlaces4(void){
//  //  People
    uint8_t a;
    const uint8_t* hl;
    do {
        do {
            // CALL(aRandom);
            // maskbits(NUM_TRAINER_CLASSES, 0);
            a = (Random() & 0x7f) + 1;
            // INC_A;
            // CP_A(NUM_TRAINER_CLASSES);  // exclude MYSTICALMAN and JODI
            // JR_NC (mPeoplePlaces4);
        } while(a >= MYSTICALMAN);
        // PUSH_AF;
        // LD_HL(mPnP_HiddenPeople);
        // LD_A_addr(wStatusFlags);
        // BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
        // IF_Z goto ok;
        if(bit_test(wram->wStatusFlags, STATUSFLAGS_HALL_OF_FAME_F)) {
            hl = PnP_HiddenPeople;
        }
        // LD_HL(mPnP_HiddenPeople_BeatE4);
        // LD_A_addr(wKantoBadges);
        // CP_A(0b11111111);  // all badges
        // IF_NZ goto ok;
        else if(wram->wKantoBadges[0] != 0b11111111) {
            hl = PnP_HiddenPeople_BeatE4;
        }
        else {
            // LD_HL(mPnP_HiddenPeople_BeatKanto);
            hl = PnP_HiddenPeople_BeatKanto;
        }

    // ok:
        // POP_AF;
        // LD_C_A;
        // LD_DE(1);
        // PUSH_BC;
        // CALL(aIsInArray);
        // POP_BC;
        // JR_C (mPeoplePlaces4);
    } while(IsInU8Array(hl, a));
    // PUSH_BC;
    // CALLFAR(aGetTrainerClassName);
    GetTrainerClassName_Conv(a);
    // LD_DE(wStringBuffer1);
    // CALL(aCopyName1);
    CopyName1(wram->wStringBuffer1);
    // POP_BC;
    // LD_B(1);
    // CALLFAR(aGetTrainerName);
    GetTrainerName_Conv(1, a);
    // LD_HL(mPnP_Text4);
    // LD_A(PLACES_AND_PEOPLE_5);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(PnP_Text4, PLACES_AND_PEOPLE_5);
// INCLUDE "data/radio/pnp_hidden_people.asm"
}

const txt_cmd_s PnP_Text4[] = {
    text_far(v_PnP_Text4)
    text_end
};

void PeoplePlaces5(void){
    static const struct TextCmd* const Adjectives[] = {
        //table_width ['2', 'PeoplePlaces5.Adjectives']
        PnP_CuteText,
        PnP_LazyText,
        PnP_HappyText,
        PnP_NoisyText,
        PnP_PrecociousText,
        PnP_BoldText,
        PnP_PickyText,
        PnP_SortOfOKText,
        PnP_SoSoText,
        PnP_GreatText,
        PnP_MyTypeText,
        PnP_CoolText,
        PnP_InspiringText,
        PnP_WeirdText,
        PnP_RightForMeText,
        PnP_OddText,
    };
    static_assert(lengthof(Adjectives) == NUM_PNP_PEOPLE_ADJECTIVES, "");
// 0-15 are all valid indexes into .Adjectives,
// so no need for a retry loop
    // CALL(aRandom);
    // maskbits(NUM_PNP_PEOPLE_ADJECTIVES, 0);
    //assert_power_of_2 ['NUM_PNP_PEOPLE_ADJECTIVES']
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mPeoplePlaces5_Adjectives);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct TextCmd* hl = Adjectives[Random() & 0xf];
    // CALL(aRandom);
    // CP_A(4 percent);
    // LD_A(PLACES_AND_PEOPLE);
    // IF_C goto ok;
    if(Random() < 4 percent) {
        return NextRadioLine_Conv(hl, PLACES_AND_PEOPLE);
    }
    // CALL(aRandom);
    // CP_A(49 percent - 1);
    // LD_A(PLACES_AND_PEOPLE_4);  // People
    // IF_C goto ok;
    else if(Random() < 49 percent - 1) {
        return NextRadioLine_Conv(hl, PLACES_AND_PEOPLE_4);
    }
    // LD_A(PLACES_AND_PEOPLE_6);  // Places
    else {
        return NextRadioLine_Conv(hl, PLACES_AND_PEOPLE_6);
    }

// ok:
    // JP(mNextRadioLine);
}

const txt_cmd_s PnP_CuteText[] = {
    text_far(v_PnP_CuteText)
    text_end
};

const txt_cmd_s PnP_LazyText[] = {
    text_far(v_PnP_LazyText)
    text_end
};

const txt_cmd_s PnP_HappyText[] = {
    text_far(v_PnP_HappyText)
    text_end
};

const txt_cmd_s PnP_NoisyText[] = {
    text_far(v_PnP_NoisyText)
    text_end
};

const txt_cmd_s PnP_PrecociousText[] = {
    text_far(v_PnP_PrecociousText)
    text_end
};

const txt_cmd_s PnP_BoldText[] = {
    text_far(v_PnP_BoldText)
    text_end
};

const txt_cmd_s PnP_PickyText[] = {
    text_far(v_PnP_PickyText)
    text_end
};

const txt_cmd_s PnP_SortOfOKText[] = {
    text_far(v_PnP_SortOfOKText)
    text_end
};

const txt_cmd_s PnP_SoSoText[] = {
    text_far(v_PnP_SoSoText)
    text_end
};

const txt_cmd_s PnP_GreatText[] = {
    text_far(v_PnP_GreatText)
    text_end
};

const txt_cmd_s PnP_MyTypeText[] = {
    text_far(v_PnP_MyTypeText)
    text_end
};

const txt_cmd_s PnP_CoolText[] = {
    text_far(v_PnP_CoolText)
    text_end
};

const txt_cmd_s PnP_InspiringText[] = {
    text_far(v_PnP_InspiringText)
    text_end
};

const txt_cmd_s PnP_WeirdText[] = {
    text_far(v_PnP_WeirdText)
    text_end
};

const txt_cmd_s PnP_RightForMeText[] = {
    text_far(v_PnP_RightForMeText)
    text_end
};

const txt_cmd_s PnP_OddText[] = {
    text_far(v_PnP_OddText)
    text_end
};

void PeoplePlaces6(void){
//  //  Places
    uint8_t a;
    do {
        // CALL(aRandom);
        a = Random();
        // CP_A((aPnP_Places_End - aPnP_Places) / 2);
        // JR_NC (mPeoplePlaces6);
    } while(a >= PnP_Places_Size);
    // LD_HL(mPnP_Places);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_B_hl;
    // INC_HL;
    // LD_C_hl;
    struct MapId map = PnP_Places[a];
    // CALL(aGetWorldMapLocation);
    // LD_E_A;
    // FARCALL(aGetLandmarkName);
    GetLandmarkName_Conv(GetWorldMapLocation(map.mapGroup, map.mapNumber));
    // LD_HL(mPnP_Text5);
    // LD_A(PLACES_AND_PEOPLE_7);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(PnP_Text5, PLACES_AND_PEOPLE_7);
// INCLUDE "data/radio/pnp_places.asm"
}

const txt_cmd_s PnP_Text5[] = {
    text_far(v_PnP_Text5)
    text_end
};

void PeoplePlaces7(void){
    static const struct TextCmd* Adjectives[] = {
    //table_width ['2', 'PeoplePlaces7.Adjectives']
        PnP_CuteText,
        PnP_LazyText,
        PnP_HappyText,
        PnP_NoisyText,
        PnP_PrecociousText,
        PnP_BoldText,
        PnP_PickyText,
        PnP_SortOfOKText,
        PnP_SoSoText,
        PnP_GreatText,
        PnP_MyTypeText,
        PnP_CoolText,
        PnP_InspiringText,
        PnP_WeirdText,
        PnP_RightForMeText,
        PnP_OddText,
    };
    static_assert(lengthof(Adjectives) == NUM_PNP_PLACES_ADJECTIVES, "");
// 0-15 are all valid indexes into .Adjectives,
// so no need for a retry loop
    // CALL(aRandom);
    // maskbits(NUM_PNP_PLACES_ADJECTIVES, 0);
    //assert_power_of_2 ['NUM_PNP_PLACES_ADJECTIVES']
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mPeoplePlaces7_Adjectives);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aCopyRadioTextToRAM);
    CopyRadioTextToRAM_Conv(Adjectives[Random() & 0xf]);
    // CALL(aRandom);
    // CP_A(4 percent);
    // LD_A(PLACES_AND_PEOPLE);
    // IF_C goto ok;
    if(Random() < 4 percent) {
        return PrintRadioLine_Conv(PLACES_AND_PEOPLE);
    }
    // CALL(aRandom);
    // CP_A(49 percent - 1);
    // LD_A(PLACES_AND_PEOPLE_4);  // People
    // IF_C goto ok;
    else if(Random() < 49 percent - 1) {
        return PrintRadioLine_Conv(PLACES_AND_PEOPLE_4);
    }
    // LD_A(PLACES_AND_PEOPLE_6);  // Places
    else {
        return PrintRadioLine_Conv(PLACES_AND_PEOPLE_6);
    }
// ok:
    // JP(mPrintRadioLine);
}

void RocketRadio1(void){
    // CALL(aStartRadioStation);
    StartRadioStation_Conv();
    // LD_HL(mRocketRadioText1);
    // LD_A(ROCKET_RADIO_2);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText1, ROCKET_RADIO_2);
}

void RocketRadio2(void){
    // LD_HL(mRocketRadioText2);
    // LD_A(ROCKET_RADIO_3);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText2, ROCKET_RADIO_3);
}

void RocketRadio3(void){
    // LD_HL(mRocketRadioText3);
    // LD_A(ROCKET_RADIO_4);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText3, ROCKET_RADIO_4);
}

void RocketRadio4(void){
    // LD_HL(mRocketRadioText4);
    // LD_A(ROCKET_RADIO_5);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText4, ROCKET_RADIO_5);
}

void RocketRadio5(void){
    // LD_HL(mRocketRadioText5);
    // LD_A(ROCKET_RADIO_6);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText5, ROCKET_RADIO_6);
}

void RocketRadio6(void){
    // LD_HL(mRocketRadioText6);
    // LD_A(ROCKET_RADIO_7);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText6, ROCKET_RADIO_7);
}

void RocketRadio7(void){
    // LD_HL(mRocketRadioText7);
    // LD_A(ROCKET_RADIO_8);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText7, ROCKET_RADIO_8);
}

void RocketRadio8(void){
    // LD_HL(mRocketRadioText8);
    // LD_A(ROCKET_RADIO_9);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText8, ROCKET_RADIO_9);
}

void RocketRadio9(void){
    // LD_HL(mRocketRadioText9);
    // LD_A(ROCKET_RADIO_10);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText9, ROCKET_RADIO_10);
}

void RocketRadio10(void){
    // LD_HL(mRocketRadioText10);
    // LD_A(ROCKET_RADIO);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(RocketRadioText10, ROCKET_RADIO);
}

const txt_cmd_s RocketRadioText1[] = {
    text_far(v_RocketRadioText1)
    text_end
};

const txt_cmd_s RocketRadioText2[] = {
    text_far(v_RocketRadioText2)
    text_end
};

const txt_cmd_s RocketRadioText3[] = {
    text_far(v_RocketRadioText3)
    text_end
};

const txt_cmd_s RocketRadioText4[] = {
    text_far(v_RocketRadioText4)
    text_end
};

const txt_cmd_s RocketRadioText5[] = {
    text_far(v_RocketRadioText5)
    text_end
};

const txt_cmd_s RocketRadioText6[] = {
    text_far(v_RocketRadioText6)
    text_end
};

const txt_cmd_s RocketRadioText7[] = {
    text_far(v_RocketRadioText7)
    text_end
};

const txt_cmd_s RocketRadioText8[] = {
    text_far(v_RocketRadioText8)
    text_end
};

const txt_cmd_s RocketRadioText9[] = {
    text_far(v_RocketRadioText9)
    text_end
};

const txt_cmd_s RocketRadioText10[] = {
    text_far(v_RocketRadioText10)
    text_end
};

void PokeFluteRadio(void){
    // CALL(aStartRadioStation);
    StartRadioStation_Conv();
    // LD_A(1);
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 1;
    // RET;
}

void UnownRadio(void){
    // CALL(aStartRadioStation);
    StartRadioStation_Conv();
    // LD_A(1);
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 1;
    // RET;
}

void EvolutionRadio(void){
    // CALL(aStartRadioStation);
    StartRadioStation_Conv();
    // LD_A(1);
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 1;
    // RET;
}

void BuenasPassword1(void){
//  Determine if we need to be here
    // CALL(aBuenasPasswordCheckTime);
    // JP_NC (mBuenasPassword1_PlayPassword);
    if(!BuenasPasswordCheckTime()) {
    // PlayPassword:
        // CALL(aStartRadioStation);
        StartRadioStation_Conv();
        // LDH_A_addr(hBGMapMode);
        // PUSH_AF;
        uint8_t bgMapMode = hram->hBGMapMode;
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // LD_DE(mBuenasPasswordChannelName);
        // hlcoord(2, 9, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(BuenasPasswordChannelName), coord(2, 9, wram->wTilemap));
        // POP_AF;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = bgMapMode;
        // LD_HL(mBuenaRadioText1);
        // LD_A(BUENAS_PASSWORD_2);
        // JP(mNextRadioLine);
        return NextRadioLine_Conv(BuenaRadioText1, BUENAS_PASSWORD_2);
    }
    // LD_A_addr(wNumRadioLinesPrinted);
    // AND_A_A;
    // JP_Z (mBuenasPassword20);
    if(wram->wNumRadioLinesPrinted == 0)
        return BuenasPassword20();
    // JP(mBuenasPassword8);
    return BuenasPassword8();
}

void BuenasPassword2(void){
    // LD_HL(mBuenaRadioText2);
    // LD_A(BUENAS_PASSWORD_3);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioText2, BUENAS_PASSWORD_3);
}

void BuenasPassword3(void){
    // CALL(aBuenasPasswordCheckTime);
    // LD_HL(mBuenaRadioText3);
    // JP_C (mBuenasPasswordAfterMidnight);
    if(BuenasPasswordCheckTime())
        return BuenasPasswordAfterMidnight(BuenaRadioText3);
    // LD_A(BUENAS_PASSWORD_4);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioText3, BUENAS_PASSWORD_4);
}

void BuenasPassword4(void){
    // CALL(aBuenasPasswordCheckTime);
    // JP_C (mBuenasPassword8);
    if(BuenasPasswordCheckTime())
        return BuenasPassword8();
    // LD_A_addr(wBuenasPassword);
//  If we already generated the password today, we don't need to generate a new one.
    // LD_HL(wDailyFlags2);
    // BIT_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
    // IF_NZ goto AlreadyGotIt;
    if(!bit_test(wram->wDailyFlags2, DAILYFLAGS2_BUENAS_PASSWORD_F)) {
    //  There are only 11 groups to choose from.
    // greater_than_11:
        uint8_t group;
        do {
            // CALL(aRandom);
            group = Random() & 0xf;
            // maskbits(NUM_PASSWORD_CATEGORIES, 0);
            // CP_A(NUM_PASSWORD_CATEGORIES);
            // IF_NC goto greater_than_11;
        } while(group >= NUM_PASSWORD_CATEGORIES);
    //  Store it in the high nybble of e.
        // SWAP_A;
        // LD_E_A;
    //  For each group, choose one of the three passwords.

        uint8_t subgroup;
    // greater_than_three:
        do {
            // CALL(aRandom);
            subgroup = Random() & 3;
            // maskbits(NUM_PASSWORDS_PER_CATEGORY, 0);
            // CP_A(NUM_PASSWORDS_PER_CATEGORY);
            // IF_NC goto greater_than_three;
        } while(subgroup >= NUM_PASSWORDS_PER_CATEGORY);
    //  The high nybble of wBuenasPassword will now contain the password group index, and the low nybble contains the actual password.
        // ADD_A_E;
        // LD_addr_A(wBuenasPassword);
        wram->wBuenasPassword = ((group << 4) & 0xf0) | (subgroup & 0xf);
    //  Set the flag so that we don't generate a new password this week.
        // LD_HL(wDailyFlags2);
        // SET_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
        bit_set(wram->wDailyFlags2, DAILYFLAGS2_BUENAS_PASSWORD_F);
    }

// AlreadyGotIt:
    // LD_C_A;
    uint8_t c = wram->wBuenasPassword;
    // CALL(aGetBuenasPassword);
    GetBuenasPassword_Conv(&c);
    // LD_HL(mBuenaRadioText4);
    // LD_A(BUENAS_PASSWORD_5);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioText4, BUENAS_PASSWORD_5);
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
}

//  The password indices are held in c.  High nybble contains the group index, low nybble contains the word index.
//  Load the password group pointer in hl.
uint8_t* GetBuenasPassword_Conv(uint8_t* c_){
    uint8_t c = *c_;
    // LD_A_C;
    // SWAP_A;
    // AND_A(0xf);
    // LD_HL(mBuenasPasswordTable);
    // LD_D(0);
    // LD_E_A;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct BuenaPassword* pass = BuenasPasswordTable + ((c >> 4) & 0xf);
//  Get the password type and store it in b.
    // LD_A_hli;
    // LD_B_A;
    uint8_t b = pass->passwordType;
    // PUSH_HL;
    // INC_HL;
//  Get the password index.
    // LD_A_C;
    // AND_A(0xf);
    // LD_C_A;
    c &= 0xf;
    // PUSH_HL;
    // LD_HL(mGetBuenasPassword_StringFunctionJumptable);
    // LD_E_B;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_DE;  // de now contains the pointer to the value of this week's password, in Blue Card Points.
    // CALL(av_hl_);
    uint8_t* str;
    switch(b) {
    // StringFunctionJumptable:
    //  entries correspond to BUENA_* constants
        //table_width ['2', 'GetBuenasPassword.StringFunctionJumptable']
        //dw ['.Mon'];  // BUENA_MON
        case BUENA_MON:
        // Mon:
            // CALL(aGetBuenasPassword_GetTheIndex);
            // CALL(aGetPokemonName);
            str = GetPokemonName(pass->mon.options[c]);
            // RET;
            break;

        //dw ['.Item'];  // BUENA_ITEM
        case BUENA_ITEM:
        // Item:
            // CALL(aGetBuenasPassword_GetTheIndex);
            // CALL(aGetItemName);
            str = GetItemName(pass->item.options[c]);
            // RET;
            break;
        //dw ['.Move'];  // BUENA_MOVE
        case BUENA_MOVE:
        // Move:
            // CALL(aGetBuenasPassword_GetTheIndex);
            // CALL(aGetMoveName);
            str = GetMoveName(pass->item.options[c]);
            // RET;
            break;
        //dw ['.RawString'];  // BUENA_STRING
        case BUENA_STRING:
        // RawString:
            str = U82CA(wram->wStringBuffer1, pass->str.options[c]);
            break;
        //  Get the string from the table...
            // LD_A_C;
            // AND_A_A;
            // IF_Z goto skip;

        // read_loop:
            // LD_A_de;
            // INC_DE;
            // CP_A(0x50);
            // IF_NZ goto read_loop;
            // DEC_C;
            // IF_NZ goto read_loop;
        //  ... and copy it into wStringBuffer1.

        // skip:
            // LD_HL(wStringBuffer1);

        // copy_loop:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            // CP_A(0x50);
            // IF_NZ goto copy_loop;
            // LD_DE(wStringBuffer1);
            // RET;
        //assert_table_length ['NUM_BUENA_FUNCTIONS']
        default:
            str = U82CA(wram->wStringBuffer1, "ERROR@");
            break;
    }
    // POP_HL;
    // LD_C_hl;
    *c_ = pass->points;
    // RET;
    return str;
// INCLUDE "data/radio/buenas_passwords.asm"
}

void BuenasPassword5(void){
    // LD_HL(mBuenaRadioText5);
    // LD_A(BUENAS_PASSWORD_6);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioText5, BUENAS_PASSWORD_6);
}

void BuenasPassword6(void){
    // LD_HL(mBuenaRadioText6);
    // LD_A(BUENAS_PASSWORD_7);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioText6, BUENAS_PASSWORD_7);
}

void BuenasPassword7(void){
    // CALL(aBuenasPasswordCheckTime);
    // LD_HL(mBuenaRadioText7);
    // JR_C (mBuenasPasswordAfterMidnight);
    if(BuenasPasswordCheckTime())
        return BuenasPasswordAfterMidnight(BuenaRadioText7);
    // LD_A(BUENAS_PASSWORD);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioText7, BUENAS_PASSWORD);
}

void BuenasPasswordAfterMidnight(const txt_cmd_s* hl){
    // PUSH_HL;
    // LD_HL(wDailyFlags2);
    // RES_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
    bit_reset(wram->wDailyFlags2, DAILYFLAGS2_BUENAS_PASSWORD_F);
    // POP_HL;
    // LD_A(BUENAS_PASSWORD_8);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(hl, BUENAS_PASSWORD_8);
}

void BuenasPassword8(void){
    // LD_HL(wDailyFlags2);
    // RES_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
    bit_reset(wram->wDailyFlags2, DAILYFLAGS2_BUENAS_PASSWORD_F);
    // LD_HL(mBuenaRadioMidnightText10);
    // LD_A(BUENAS_PASSWORD_9);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText10, BUENAS_PASSWORD_9);
}

void BuenasPassword9(void){
    // LD_HL(mBuenaRadioMidnightText1);
    // LD_A(BUENAS_PASSWORD_10);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText1, BUENAS_PASSWORD_10);
}

void BuenasPassword10(void){
    // LD_HL(mBuenaRadioMidnightText2);
    // LD_A(BUENAS_PASSWORD_11);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText2, BUENAS_PASSWORD_11);
}

void BuenasPassword11(void){
    // LD_HL(mBuenaRadioMidnightText3);
    // LD_A(BUENAS_PASSWORD_12);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText3, BUENAS_PASSWORD_12);
}

void BuenasPassword12(void){
    // LD_HL(mBuenaRadioMidnightText4);
    // LD_A(BUENAS_PASSWORD_13);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText4, BUENAS_PASSWORD_13);
}

void BuenasPassword13(void){
    // LD_HL(mBuenaRadioMidnightText5);
    // LD_A(BUENAS_PASSWORD_14);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText5, BUENAS_PASSWORD_14);
}

void BuenasPassword14(void){
    // LD_HL(mBuenaRadioMidnightText6);
    // LD_A(BUENAS_PASSWORD_15);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText6, BUENAS_PASSWORD_15);
}

void BuenasPassword15(void){
    // LD_HL(mBuenaRadioMidnightText7);
    // LD_A(BUENAS_PASSWORD_16);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText7, BUENAS_PASSWORD_16);
}

void BuenasPassword16(void){
    // LD_HL(mBuenaRadioMidnightText8);
    // LD_A(BUENAS_PASSWORD_17);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText8, BUENAS_PASSWORD_17);
}

void BuenasPassword17(void){
    // LD_HL(mBuenaRadioMidnightText9);
    // LD_A(BUENAS_PASSWORD_18);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText9, BUENAS_PASSWORD_18);
}

void BuenasPassword18(void){
    // LD_HL(mBuenaRadioMidnightText10);
    // LD_A(BUENAS_PASSWORD_19);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText10, BUENAS_PASSWORD_19);
}

void BuenasPassword19(void){
    // LD_HL(mBuenaRadioMidnightText10);
    // LD_A(BUENAS_PASSWORD_20);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaRadioMidnightText10, BUENAS_PASSWORD_20);
}

void BuenasPassword20(void){
    // LDH_A_addr(hBGMapMode);
    // PUSH_AF;
    uint8_t bgMapMode = hram->hBGMapMode;
    // FARCALL(aNoRadioMusic);
    NoRadioMusic_Conv();
    // FARCALL(aNoRadioName);
    NoRadioName_Conv();
    // POP_AF;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = bgMapMode;
    // LD_HL(wDailyFlags2);
    // RES_hl(DAILYFLAGS2_BUENAS_PASSWORD_F);
    bit_reset(wram->wDailyFlags2, DAILYFLAGS2_BUENAS_PASSWORD_F);
    // LD_A(BUENAS_PASSWORD);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = BUENAS_PASSWORD;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_HL(mBuenaOffTheAirText);
    // LD_A(BUENAS_PASSWORD_21);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaOffTheAirText, BUENAS_PASSWORD_21);
}

void BuenasPassword21(void){
    // LD_A(BUENAS_PASSWORD);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = BUENAS_PASSWORD;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // CALL(aBuenasPasswordCheckTime);
    // JP_NC (mBuenasPassword1);
    if(!BuenasPasswordCheckTime())
        return BuenasPassword1();
    // LD_HL(mBuenaOffTheAirText);
    // LD_A(BUENAS_PASSWORD_21);
    // JP(mNextRadioLine);
    return NextRadioLine_Conv(BuenaOffTheAirText, BUENAS_PASSWORD_21);
}

bool BuenasPasswordCheckTime(void){
    // CALL(aUpdateTime);
    UpdateTime();
    // LDH_A_addr(hHours);
    // CP_A(NITE_HOUR);
    // RET;
    return hram->hHours < NITE_HOUR;
}

const char BuenasPasswordChannelName[] = "BUENA\'S PASSWORD@";

const txt_cmd_s BuenaRadioText1[] = {
    text_far(v_BuenaRadioText1)
    text_end
};

const txt_cmd_s BuenaRadioText2[] = {
    text_far(v_BuenaRadioText2)
    text_end
};

const txt_cmd_s BuenaRadioText3[] = {
    text_far(v_BuenaRadioText3)
    text_end
};

const txt_cmd_s BuenaRadioText4[] = {
    text_far(v_BuenaRadioText4)
    text_end
};

const txt_cmd_s BuenaRadioText5[] = {
    text_far(v_BuenaRadioText5)
    text_end
};

const txt_cmd_s BuenaRadioText6[] = {
    text_far(v_BuenaRadioText6)
    text_end
};

const txt_cmd_s BuenaRadioText7[] = {
    text_far(v_BuenaRadioText7)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText1[] = {
    text_far(v_BuenaRadioMidnightText1)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText2[] = {
    text_far(v_BuenaRadioMidnightText2)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText3[] = {
    text_far(v_BuenaRadioMidnightText3)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText4[] = {
    text_far(v_BuenaRadioMidnightText4)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText5[] = {
    text_far(v_BuenaRadioMidnightText5)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText6[] = {
    text_far(v_BuenaRadioMidnightText6)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText7[] = {
    text_far(v_BuenaRadioMidnightText7)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText8[] = {
    text_far(v_BuenaRadioMidnightText8)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText9[] = {
    text_far(v_BuenaRadioMidnightText9)
    text_end
};

const txt_cmd_s BuenaRadioMidnightText10[] = {
    text_far(v_BuenaRadioMidnightText10)
    text_end
};

const txt_cmd_s BuenaOffTheAirText[] = {
    text_far(v_BuenaOffTheAirText)
    text_end
};

void CopyRadioTextToRAM(void){
    LD_A_hl;
    CP_A(TX_FAR);
    JP_Z (mFarCopyRadioText);
    LD_DE(wRadioText);
    LD_BC(2 * SCREEN_WIDTH);
    JP(mCopyBytes);

}

void CopyRadioTextToRAM_Conv(const struct TextCmd* hl){
    // LD_A_hl;
    // CP_A(TX_FAR);
    // JP_Z (mFarCopyRadioText);
    // LD_DE(wRadioText);
    // LD_BC(2 * SCREEN_WIDTH);
    // JP(mCopyBytes);
    gRadioText = hl;
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
    if(wram->wNumRadioLinesPrinted != 0)
        return;

    // CALL(aRadioTerminator);
    // CALL(aPrintText);
    PrintText(RadioTerminator());

    uint16_t hl = RadioChannelSongs[wram->wCurRadioLine];
    RadioMusicRestartDE_Conv(hl);

// INCLUDE "data/radio/channel_music.asm"
}

void NextRadioLine_Conv(const struct TextCmd* hl, uint8_t station){
    // PUSH_AF;
    // CALL(aCopyRadioTextToRAM);
    CopyRadioTextToRAM_Conv(hl);
    // POP_AF;
    PrintRadioLine_Conv(station);
}
