#include "../../constants.h"
#include "halloffame.h"
#include "prof_oaks_pc.h"
#include "../../home/sprite_updates.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/sram.h"
#include "../../home/fade.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/print_text.h"
#include "../../home/pokemon.h"
#include "../../home/names.h"
#include "../../home/gfx.h"
#include "../../home/joypad.h"
#include "../pokemon/mon_stats.h"
#include "../gfx/load_pics.h"
#include "../gfx/place_graphic.h"
#include "../gfx/pic_animation.h"
#include "../gfx/player_gfx.h"
#include "../tilesets/timeofday_pals.h"
#include "../movie/init_hof_credits.h"
#include "../movie/credits.h"
#include "../menus/save.h"
#include "../../gfx/font.h"

#define HALLOFFAME_COLON (0x63)

void HallOfFame(void){
    // CALL(aHallOfFame_FadeOutMusic);
    HallOfFame_FadeOutMusic();
    // LD_A_addr(wStatusFlags);
    // PUSH_AF;
    uint8_t statusFlags = wram->wStatusFlags;
    // LD_A(1);
    // LD_addr_A(wGameLogicPaused);
    wram->wGameLogicPaused = 1;
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // LD_A(SPAWN_LANCE);
    // LD_addr_A(wSpawnAfterChampion);
    wram->wSpawnAfterChampion = SPAWN_LANCE;

// Enable the Pokégear map to cycle through all of Kanto
    // LD_HL(wStatusFlags);
    // SET_hl(STATUSFLAGS_HALL_OF_FAME_F);
    bit_set(wram->wStatusFlags, STATUSFLAGS_HALL_OF_FAME_F);

    // FARCALL(aHallOfFame_InitSaveIfNeeded);
    HallOfFame_InitSaveIfNeeded();

    // LD_HL(wHallOfFameCount);
    // LD_A_hl;
    // CP_A(HOF_MASTER_COUNT);
    // IF_NC goto ok;
    if(wram->wHallOfFameCount < HOF_MASTER_COUNT) {
        // INC_hl;
        wram->wHallOfFameCount++;
    }

// ok:
    // FARCALL(aSaveGameData);
    SaveGameData();
    // CALL(aGetHallOfFameParty);
    GetHallOfFameParty();
    // FARCALL(aAddHallOfFameEntry);
    AddHallOfFameEntry();

    // XOR_A_A;
    // LD_addr_A(wGameLogicPaused);
    wram->wGameLogicPaused = 0x0;
    // CALL(aAnimateHallOfFame);
    AnimateHallOfFame();
    // POP_AF;
    // LD_B_A;
    // FARCALL(aCredits);
    Credits(statusFlags);
    // RET;
}

void RedCredits(void){
    // LD_A(LOW(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID);
    // LD_A(HIGH(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_A(10);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 10;
    // FARCALL(aFadeOutPalettes);
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0x0;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = FALSE;
    // FARCALL(aInitDisplayForRedCredits);
    InitDisplayForRedCredits();
    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames(8);
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // LD_A(SPAWN_RED);
    // LD_addr_A(wSpawnAfterChampion);
    wram->wSpawnAfterChampion = SPAWN_RED;
    // LD_A_addr(wStatusFlags);
    // LD_B_A;
    // FARCALL(aCredits);
    Credits(wram->wStatusFlags);
    // RET;
}

void HallOfFame_FadeOutMusic(void){
    // LD_A(LOW(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID);
    // LD_A(HIGH(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_A(10);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 10;
    // FARCALL(aFadeOutPalettes);
    FadeOutPalettes();
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0x0;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0x0;
    // FARCALL(aInitDisplayForHallOfFame);
    InitDisplayForHallOfFame();
    // LD_C(100);
    // JP(mDelayFrames);
    return DelayFrames(100);
}

void HallOfFame_PlayMusicDE(uint16_t de){
    // PUSH_DE;
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // POP_DE;
    // CALL(aPlayMusic);
    PlayMusic(de);
    // RET;
}

static void AnimateHallOfFame_DisplayNewHallOfFamer(struct HOFMon* hl){
    // CALL(aDisplayHOFMon);
    DisplayHOFMon(hl);
    // LD_DE(mAnimateHallOfFame_String_NewHallOfFamer);
    // hlcoord(1, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("New Hall of Famer!"), coord(1, 2, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap();
    // decoord(6, 5, wTilemap);
    // LD_C(ANIM_MON_HOF);
    // PREDEF(pHOF_AnimateFrontpic);
    HOF_AnimateFrontpic_Conv(coord(6, 5, wram->wTilemap), ANIM_MON_HOF);
    // LD_C(60);
    // CALL(aDelayFrames);
    DelayFrames(60);
    // AND_A_A;
    // RET;

// String_NewHallOfFamer:
    //db ['"New Hall of Famer!@"'];
}

void AnimateHallOfFame(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // CALL(aLoadHOFTeam);
    bool error = LoadHOFTeam();
    // IF_C goto done;
    if(!error) {
        // LD_DE(MUSIC_HALL_OF_FAME);
        // CALL(aHallOfFame_PlayMusicDE);
        HallOfFame_PlayMusicDE(MUSIC_HALL_OF_FAME);
        // XOR_A_A;
        // LD_addr_A(wHallOfFameMonCounter);
        uint8_t counter = 0;

        while(counter < PARTY_LENGTH) {
        // loop:
            // LD_A_addr(wHallOfFameMonCounter);
            // CP_A(PARTY_LENGTH);
            // IF_NC goto done;
            // LD_HL(wHallOfFameTempMon1);
            // LD_BC(wHallOfFameTempMon1End - wHallOfFameTempMon1);
            // CALL(aAddNTimes);
            // LD_A_hl;
            // CP_A(-1);
            // IF_Z goto done;
            if(wram->wHallOfFameTemp.mon[counter].species == (species_t)-1)
                break;
            // PUSH_HL;
            // CALL(aAnimateHOFMonEntrance);
            AnimateHOFMonEntrance(wram->wHallOfFameTemp.mon + counter);
            // POP_HL;
            // CALL(aAnimateHallOfFame_DisplayNewHallOfFamer);
            AnimateHallOfFame_DisplayNewHallOfFamer(wram->wHallOfFameTemp.mon + counter);
            // IF_C goto done;
            // LD_HL(wHallOfFameMonCounter);
            // INC_hl;
            counter++;
            // goto loop;
        }
        wram->wHallOfFameMonCounter = counter;
    }

// done:
    // CALL(aHOF_AnimatePlayerPic);
    HOF_AnimatePlayerPic();
    // LD_A(0x4);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x4;
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames(8);
    // RET;
    return;
}

void GetHallOfFameParty(void){
    // LD_HL(wHallOfFamePokemonList);
    // LD_BC(wHallOfFamePokemonListEnd - wHallOfFamePokemonList + 1);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(&wram->wHallOfFamePokemonList, sizeof(wram->wHallOfFamePokemonList), 0x0);
    // LD_A_addr(wHallOfFameCount);
    // LD_DE(wHallOfFamePokemonList);
    // LD_de_A;
    wram->wHallOfFamePokemonList.winCount = wram->wHallOfFameCount;
    // INC_DE;
    struct HOFMon* de = wram->wHallOfFamePokemonList.mon;
    // LD_HL(wPartySpecies);
    species_t* hl = wram->wPartySpecies;
    // LD_C(0);
    uint8_t c = 0;

    while(1) {
    // next:
        // LD_A_hli;
        species_t a = *(hl++);
        // CP_A(-1);
        // IF_Z goto done;
        if(a == (species_t)-1) {
        // done:
            // LD_A(-1);
            // LD_de_A;
            de->species = (species_t)-1;
            // RET;
            return;
        }
        // CP_A(EGG);
        // IF_NZ goto mon;
        if(a != EGG) {
        // mon:
            // PUSH_HL;
            // PUSH_DE;
            // PUSH_BC;

            // LD_A_C;
            // LD_HL(wPartyMons);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // CALL(aAddNTimes);
            // LD_C_L;
            // LD_B_H;
            struct BoxMon* bc = &wram->wPartyMon[c].mon;

            // LD_HL(MON_SPECIES);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_de_A;
            de->species = bc->species;
            // INC_DE;

            // LD_HL(MON_ID);
            // ADD_HL_BC;
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            // LD_A_hl;
            // LD_de_A;
            de->id = bc->id;
            // INC_DE;

            // LD_HL(MON_DVS);
            // ADD_HL_BC;
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            // LD_A_hl;
            // LD_de_A;
            de->DVs = bc->DVs;
            // INC_DE;

            // LD_HL(MON_LEVEL);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_de_A;
            de->level = bc->level;
            // INC_DE;

            // POP_BC;
            // PUSH_BC;
            // LD_A_C;
            // LD_HL(wPartyMonNicknames);
            // LD_BC(MON_NAME_LENGTH);
            // CALL(aAddNTimes);
            // LD_BC(MON_NAME_LENGTH - 1);
            // CALL(aCopyBytes);
            CopyBytes(de->nickname, wram->wPartyMonNickname[c], MON_NAME_LENGTH - 1);

            // POP_BC;
            // INC_C;
            c++;
            // POP_DE;
            // LD_HL(wHallOfFamePokemonListMon1End - wHallOfFamePokemonListMon1);
            // ADD_HL_DE;
            // LD_E_L;
            // LD_D_H;
            de++;
            // POP_HL;
            // goto next;
            continue;
        }
        // INC_C;
        ++c;
        // goto next;
    }
}

void AnimateHOFMonEntrance(struct HOFMon* mon){
    // PUSH_HL;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // FARCALL(aResetDisplayBetweenHallOfFameMons);
    ResetDisplayBetweenHallOfFameMons();
    // POP_HL;
    // LD_A_hli;
    // LD_addr_A(wTempMonSpecies);
    wram->wTempWildMonSpecies = mon->species;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = mon->species;
    // INC_HL;
    // INC_HL;
    // LD_A_hli;
    // LD_addr_A(wTempMonDVs);
    // LD_A_hli;
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = mon->DVs;
    // LD_HL(wTempMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter_Conv(mon->DVs);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // PREDEF(pGetMonBackpic);
    GetMonBackpic_Conv(vram->vTiles2 + LEN_2BPP_TILE * 0x31, mon->species);
    // LD_A(0x31);
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0x31;
    // hlcoord(6, 6, wTilemap);
    // LD_BC((6 << 8) | 6);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(6, 6, wram->wTilemap), 6, 6);
    // LD_A(0xd0);
    // LDH_addr_A(hSCY);
    hram->hSCY = 0xd0;
    // LD_A(0x90);
    // LDH_addr_A(hSCX);
    hram->hSCY = 0x90;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aHOF_SlideBackpic);
    HOF_SlideBackpic();
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x0;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // hlcoord(6, 5, wTilemap);
    // CALL(av_PrepMonFrontpic);
    v_PrepMonFrontpic_Conv(coord(6, 5, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0x0;
    // CALL(aHOF_SlideFrontpic);
    HOF_SlideFrontpic();
    // RET;

}

void HOF_SlideBackpic(void){
    while(hram->hSCX != 0x70) {
    // backpicloop:
        // LDH_A_addr(hSCX);
        // CP_A(0x70);
        // RET_Z ;
        // ADD_A(4);
        // LDH_addr_A(hSCX);
        hram->hSCX += 4;
        // CALL(aDelayFrame);
        DelayFrame();
        // goto backpicloop;
    }
}

void HOF_SlideFrontpic(void){
    while(hram->hSCX != 0x0) {
    // frontpicloop:
        // LDH_A_addr(hSCX);
        // AND_A_A;
        // RET_Z ;
        // DEC_A;
        // DEC_A;
        // LDH_addr_A(hSCX);
        hram->hSCX -= 2;
        // CALL(aDelayFrame);
        DelayFrame();
        // goto frontpicloop;
    }
}

//  Print the number of times the player has entered the Hall of Fame.
//  If that number is at least HOF_MASTER_COUNT, print "HOF Master!" instead.
static bool v_HallOfFamePC_DisplayMonAndStrings(uint8_t counter){
    static const char HOFMaster[] = "    HOF Master!";
    static const char TimeFamer[] = "    -Time Famer";
    // LD_A_addr(wHallOfFameMonCounter);
    // CP_A(PARTY_LENGTH);
    // IF_NC goto fail;
    if(counter >= PARTY_LENGTH)
        return true;
    // LD_HL(wHallOfFameTempMon1);
    // LD_BC(wHallOfFameTempMon1End - wHallOfFameTempMon1);
    // CALL(aAddNTimes);
    const struct HOFMon* mon = wram->wHallOfFameTemp.mon + counter;
    // LD_A_hl;
    // CP_A(-1);
    // IF_NZ goto okay;
    if(mon->species == (species_t)-1) {
    // fail:
        // SCF;
        // RET;
        return true;
    }

// okay:
    // PUSH_HL;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // POP_HL;
    // CALL(aDisplayHOFMon);
    DisplayHOFMon(mon);
    // LD_A_addr(wHallOfFameTempWinCount);
    // CP_A(HOF_MASTER_COUNT + 1);  // should be HOF_MASTER_COUNT
    // IF_C goto print_num_hof;
    tile_t* hl;
#if BUGFIX_HOFPC_DISPLAY_WIN_COUNT
    if(wram->wHallOfFameTemp.winCount >= HOF_MASTER_COUNT)
#else
    if(wram->wHallOfFameTemp.winCount >= HOF_MASTER_COUNT + 1) // should be HOF_MASTER_COUNT
#endif
    {
        // LD_DE(mv_HallOfFamePC_HOFMaster);
        // hlcoord(1, 2, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(HOFMaster), coord(1, 2, wram->wTilemap));
        // hlcoord(13, 2, wTilemap);
        hl = coord(13, 2, wram->wTilemap);
        // goto finish;
    }
    else 
    {
    // print_num_hof:
        // LD_DE(mv_HallOfFamePC_TimeFamer);
        // hlcoord(1, 2, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(TimeFamer), coord(1, 2, wram->wTilemap));
        // hlcoord(2, 2, wTilemap);
        // LD_DE(wHallOfFameTempWinCount);
        // LD_BC((1 << 8) | 3);
        // CALL(aPrintNum);
        PrintNum_Conv2(coord(2, 2, wram->wTilemap), &wram->wHallOfFameTemp.winCount, 1, 3);
        // hlcoord(11, 2, wTilemap);
        hl = coord(11, 2, wram->wTilemap);
    }

// finish:
    // LD_DE(mv_HallOfFamePC_EmptyString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(""), hl);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aSetPalettes);
    SetPalettes();
    // decoord(6, 5, wTilemap);
    // LD_C(ANIM_MON_HOF);
    // PREDEF(pHOF_AnimateFrontpic);
    HOF_AnimateFrontpic_Conv(coord(6, 5, wram->wTilemap), ANIM_MON_HOF);
    // AND_A_A;
    // RET;
    return false;

// EmptyString:
    //db ['"@"'];
}

static bool v_HallOfFamePC_DisplayTeam(void){
    // XOR_A_A;
    // LD_addr_A(wHallOfFameMonCounter);
    uint8_t counter = 0;

    while(!v_HallOfFamePC_DisplayMonAndStrings(counter)){
    // next:
        // CALL(av_HallOfFamePC_DisplayMonAndStrings);
        // IF_C goto start_button;

        while(1) {
        // loop:
            // CALL(aJoyTextDelay);
            JoyTextDelay_Conv();
            // LD_HL(hJoyLast);
            // LD_A_hl;
            // AND_A(B_BUTTON);
            // IF_NZ goto b_button;
            if(hram->hJoyLast & B_BUTTON){
            // b_button:
                // SCF;
                // RET;
                return true;
            }
            // LD_A_hl;
            // AND_A(A_BUTTON);
            // IF_NZ goto a_button;
            if(hram->hJoyLast & A_BUTTON){
            // a_button:
                // LD_HL(wHallOfFameMonCounter);
                // INC_hl;
                counter++;
                // goto next;
                break;
            }
            // LD_A_hl;
            // AND_A(START);
            // IF_NZ goto start_button;
            if(hram->hJoyLast & START){
            // start_button:
                // AND_A_A;
                // RET;
                return false;
            }
            // CALL(aDelayFrame);
            DelayFrame();
            // goto loop;
        }
    }
    return false;
}

void v_HallOfFamePC(void){
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;

    while(1) {
    // MasterLoop:
        // CALL(aLoadHOFTeam);
        // RET_C ;
        if(LoadHOFTeam())
            return;
        // CALL(av_HallOfFamePC_DisplayTeam);
        // RET_C ;
        if(v_HallOfFamePC_DisplayTeam())
            return;
        // LD_HL(wJumptableIndex);
        // INC_hl;
        wram->wJumptableIndex++;
        // goto MasterLoop;
    }
}

bool LoadHOFTeam(void){
    // LD_A_addr(wJumptableIndex);
    uint8_t index = wram->wJumptableIndex;
    // CP_A(NUM_HOF_TEAMS);
    // IF_NC goto invalid;
    if(index >= NUM_HOF_TEAMS)
        return true;
    // LD_HL(sHallOfFame);
    // LD_BC(wHallOfFameTempEnd - wHallOfFameTemp + 1);
    // CALL(aAddNTimes);
    uint16_t hl = sHallOfFame + (wHallOfFameTempEnd - wHallOfFameTemp + 1) * index;
    // LD_A(BANK(sHallOfFame));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asHallOfFame));
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto absent;
    if(gb_read(hl) == 0) {
    // absent:
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();

    // invalid:
        // SCF;
        // RET;
        return true;
    }
    // LD_DE(wHallOfFameTemp);
    // LD_BC(wHallOfFameTempEnd - wHallOfFameTemp + 1);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wHallOfFameTemp, GBToRAMAddr(hl), (wHallOfFameTempEnd - wHallOfFameTemp + 1));
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // AND_A_A;
    // RET;
    return false;
}

void DisplayHOFMon(const struct HOFMon* mon){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A_hli;
    // LD_addr_A(wTempMonSpecies);
    wram->wTempMon.mon.species = mon->species;
    // LD_A_hli;
    // LD_addr_A(wTempMonID);
    // LD_A_hli;
    // LD_addr_A(wTempMonID + 1);
    wram->wTempMon.mon.id = mon->id;
    // LD_A_hli;
    // LD_addr_A(wTempMonDVs);
    // LD_A_hli;
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = mon->DVs;
    // LD_A_hli;
    // LD_addr_A(wTempMonLevel);
    wram->wTempMon.mon.level = mon->level;
    // LD_DE(wStringBuffer2);
    // LD_BC(MON_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes(wram->wStringBuffer2, mon->nickname, MON_NAME_LENGTH - 1);
    // LD_A(0x50);
    // LD_addr_A(wStringBuffer2 + MON_NAME_LENGTH - 1);
    wram->wStringBuffer2[MON_NAME_LENGTH - 1] = 0x50;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // hlcoord(0, 0, wTilemap);
    // LD_BC((3 << 8) | SCREEN_WIDTH - 2);
    // CALL(aTextbox);
    Textbox(coord(0, 0, wram->wTilemap), 3, SCREEN_WIDTH - 2);
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | SCREEN_WIDTH - 2);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 4, SCREEN_WIDTH - 2);
    // LD_A_addr(wTempMonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempMon.mon.species;
    // LD_addr_A(wTextDecimalByte);
    species_t species = wram->wTempMon.mon.species;
    // LD_HL(wTempMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter_Conv(wram->wTempMon.mon.DVs);
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x0;
    // hlcoord(6, 5, wTilemap);
    // CALL(av_PrepMonFrontpic);
    v_PrepMonFrontpic_Conv(coord(6, 5, wram->wTilemap));
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto print_id_no;
    if(wram->wCurPartySpecies != EGG) {
        // hlcoord(1, 13, wTilemap);
        // LD_A(0x74);
        // LD_hli_A;
        *coord(1, 13, wram->wTilemap) = 0x74;
        // LD_hl(0xf2);
        *coord(2, 13, wram->wTilemap) = 0xf2;
        // hlcoord(3, 13, wTilemap);
        // LD_DE(wTextDecimalByte);
        // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
        // CALL(aPrintNum);
        PrintNum_Conv2(coord(3, 13, wram->wTilemap), &species, PRINTNUM_LEADINGZEROS | sizeof(species), 3);
        // CALL(aGetBasePokemonName);
        // hlcoord(7, 13, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(GetBasePokemonName(species), coord(7, 13, wram->wTilemap));
        // LD_A(TEMPMON);
        // LD_addr_A(wMonType);
        wram->wMonType = TEMPMON;
        // FARCALL(aGetGender);
        u8_flag_s res = GetGender_Conv(TEMPMON);
        // LD_A(0x7f);
        // IF_C goto got_gender;
        if(res.flag)
            *coord(18, 13, wram->wTilemap) = 0x7f;
        // LD_A(0xef);
        // IF_NZ goto got_gender;
        else if(res.a != 0)
            *coord(18, 13, wram->wTilemap) = 0xef;
        // LD_A(0xf5);
        else
            *coord(18, 13, wram->wTilemap) = 0xf5;

    // got_gender:
        // hlcoord(18, 13, wTilemap);
        // LD_hli_A;
        // hlcoord(8, 14, wTilemap);
        // LD_A(0xf3);
        // LD_hli_A;
        *coord(8, 14, wram->wTilemap) = 0xf3;
        // LD_DE(wStringBuffer2);
        // CALL(aPlaceString);
        PlaceStringSimple(wram->wStringBuffer2, coord(8, 15, wram->wTilemap));
        // hlcoord(1, 16, wTilemap);
        // CALL(aPrintLevel);
        PrintLevel_Conv(coord(1, 16, wram->wTilemap), wram->wTempMon.mon.level);
    }

// print_id_no:
    // hlcoord(7, 16, wTilemap);
    // LD_A(0x73);
    *coord(7, 16, wram->wTilemap) = 0x73;
    // LD_hli_A;
    // LD_A(0x74);
    *coord(8, 16, wram->wTilemap) = 0x74;
    // LD_hli_A;
    // LD_hl(0xf3);
    *coord(9, 16, wram->wTilemap) = 0xf3;
    // hlcoord(10, 16, wTilemap);
    // LD_DE(wTempMonID);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(10, 16, wram->wTilemap), &wram->wTempMon.mon.id, PRINTNUM_LEADINGZEROS | 2, 5);
    // RET;
}

void HOF_AnimatePlayerPic(void){
    static const char PlayTime[] = "PLAY TIME";
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // LD_HL(vTiles2 + LEN_2BPP_TILE * HALLOFFAME_COLON);
    // LD_DE(mFontExtra + 13 * LEN_2BPP_TILE);  // "<COLON>"
    // LD_BC((BANK(aFontExtra) << 8) | 1);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * HALLOFFAME_COLON, FontExtra, 13, 1);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // FARCALL(aGetPlayerBackpic);
    GetPlayerBackpic();
    // LD_A(0x31);
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0x31;
    // hlcoord(6, 6, wTilemap);
    // LD_BC((6 << 8) | 6);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(6, 6, wram->wTilemap), 6, 6);
    // LD_A(0xd0);
    // LDH_addr_A(hSCY);
    hram->hSCY = 0xd0;
    // LD_A(0x90);
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x90;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = 0x0;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aHOF_SlideBackpic);
    HOF_SlideBackpic();
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x0;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // FARCALL(aHOF_LoadTrainerFrontpic);
    HOF_LoadTrainerFrontpic();
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0x0;
    // hlcoord(12, 5, wTilemap);
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(12, 5, wram->wTilemap), 7, 7);
    // LD_A(0xc0);
    // LDH_addr_A(hSCX);
    hram->hSCX = 0xc0;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0x0;
    // CALL(aHOF_SlideFrontpic);
    HOF_SlideFrontpic();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 2, wTilemap);
    // LD_BC((8 << 8) | 9);
    // CALL(aTextbox);
    Textbox(coord(0, 2, wram->wTilemap), 8, 9);
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 4, 18);
    // hlcoord(2, 4, wTilemap);
    // LD_DE(wPlayerName);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wPlayerName, coord(2, 4, wram->wTilemap));
    // hlcoord(1, 6, wTilemap);
    // LD_A(0x73);
    // LD_hli_A;
    *coord(1, 6, wram->wTilemap) = 0x73;
    // LD_A(0x74);
    // LD_hli_A;
    *coord(2, 6, wram->wTilemap) = 0x74;
    // LD_hl(0xf3);
    *coord(3, 6, wram->wTilemap) = 0xf3;
    // hlcoord(4, 6, wTilemap);
    // LD_DE(wPlayerID);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(4, 6, wram->wTilemap), &wram->wPlayerID, PRINTNUM_LEADINGZEROS | 2, 5);
    // hlcoord(1, 8, wTilemap);
    // LD_DE(mHOF_AnimatePlayerPic_PlayTime);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(PlayTime), coord(1, 8, wram->wTilemap));
    // hlcoord(3, 9, wTilemap);
    // LD_DE(wGameTimeHours);
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    uint8_t* hl = PrintNum_Conv2(coord(3, 9, wram->wTilemap), &wram->wGameTimeHours, 2, 3);
    // LD_hl(HALLOFFAME_COLON);
    // INC_HL;
    *(hl++) = HALLOFFAME_COLON;
    // LD_DE(wGameTimeMinutes);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, &wram->wGameTimeMinutes, PRINTNUM_LEADINGZEROS | 1, 2);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // FARCALL(aProfOaksPCRating);
    ProfOaksPCRating();
    // RET;

}
