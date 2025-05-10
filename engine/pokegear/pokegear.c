#include "../../constants.h"
#include "pokegear.h"
#include "radio.h"
#include "townmap_convertlinebreakcharacters.h"
#include "../../home/audio.h"
#include "../../home/gfx.h"
#include "../../home/map.h"
#include "../../home/delay.h"
#include "../../home/decompress.h"
#include "../../home/copy.h"
#include "../../home/palettes.h"
#include "../../home/text.h"
#include "../../home/time.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/joypad.h"
#include "../../home/region.h"
#include "../../home/lcd.h"
#include "../../home/sprite_anims.h"
#include "../../home/menu.h"
#include "../../home/names.h"
#include "../smallflag.h"
#include "../overworld/landmarks.h"
#include "../overworld/wildmons.h"
#include "../gfx/player_gfx.h"
#include "../gfx/sprites.h"
#include "../gfx/mon_icons.h"
#include "../../data/maps/flypoints.h"
#include "../../audio/engine.h"
#include "../rtc/print_hours_mins.h"
#include "../../gfx/font.h"
#include "../../data/text/common.h"
#include "../../gfx/misc.h"
#include "../phone/phone.h"
#include "../../charmap.h"

void (*gPokegearRadioChannelAddr)(void);
struct SpriteAnim* gPokegearMapCursorObjectPointer = NULL;
struct SpriteAnim* gTownMapCursorObjectPointer = NULL;
struct SpriteAnim* gTownMapCursorCoordinates = NULL;

//  Pokégear cards
enum {
    POKEGEARCARD_CLOCK = 0,
    POKEGEARCARD_MAP = 1,
    POKEGEARCARD_PHONE = 2,
    POKEGEARCARD_RADIO = 3,
    NUM_POKEGEAR_CARDS
};
    //const_def ['?']
    //const ['POKEGEARCARD_CLOCK']  // 0
    //const ['POKEGEARCARD_MAP']  // 1
    //const ['POKEGEARCARD_PHONE']  // 2
    //const ['POKEGEARCARD_RADIO']  // 3
// #define NUM_POKEGEAR_CARDS (POKEGEARCARD_RADIO + 1)

#define PHONE_DISPLAY_HEIGHT (4)

//  PokegearJumptable.Jumptable indexes
enum {
    POKEGEARSTATE_CLOCKINIT = 0,   //const ['POKEGEARSTATE_CLOCKINIT']  // 0
    POKEGEARSTATE_CLOCKJOYPAD, //const ['POKEGEARSTATE_CLOCKJOYPAD']  // 1
    POKEGEARSTATE_MAPCHECKREGION, //const ['POKEGEARSTATE_MAPCHECKREGION']  // 2
    POKEGEARSTATE_JOHTOMAPINIT,//const ['POKEGEARSTATE_JOHTOMAPINIT']  // 3
    POKEGEARSTATE_JOHTOMAPJOYPAD, //const ['POKEGEARSTATE_JOHTOMAPJOYPAD']  // 4
    POKEGEARSTATE_KANTOMAPINIT,//const ['POKEGEARSTATE_KANTOMAPINIT']  // 5
    POKEGEARSTATE_KANTOMAPJOYPAD, //const ['POKEGEARSTATE_KANTOMAPJOYPAD']  // 6
    POKEGEARSTATE_PHONEINIT, //const ['POKEGEARSTATE_PHONEINIT']  // 7
    POKEGEARSTATE_PHONEJOYPAD, //const ['POKEGEARSTATE_PHONEJOYPAD']  // 8
    POKEGEARSTATE_MAKEPHONECALL, //const ['POKEGEARSTATE_MAKEPHONECALL']  // 9
    POKEGEARSTATE_FINISHPHONECALL, //const ['POKEGEARSTATE_FINISHPHONECALL']  // a
    POKEGEARSTATE_RADIOINIT, //const ['POKEGEARSTATE_RADIOINIT']  // b
    POKEGEARSTATE_RADIOJOYPAD //const ['POKEGEARSTATE_RADIOJOYPAD']  // c
};

static const char PokegearSpritesGFX[] = "gfx/pokegear/pokegear_sprites.png";
static const char FastShipGFX[] = "gfx/pokegear/fast_ship.png";

static const char RadioTilemapRLE[] = "gfx/pokegear/radio.tilemap.rle";
static const char PhoneTilemapRLE[] = "gfx/pokegear/phone.tilemap.rle";
static const char ClockTilemapRLE[] = "gfx/pokegear/clock.tilemap.rle";

static const char OaksPKMNTalkName[] = "OAK's <PK><MN> Talk@";
static const char PokedexShowName[] = "#DEX Show@";
static const char PokemonMusicName[] = "#MON Music@";
static const char LuckyChannelName[] = "Lucky Channel@";
static const char UnownStationName[] = "?????@";
static const char PlacesAndPeopleName[] = "Places & People@";
static const char LetsAllSingName[] = "Let's All Sing!@";
static const char PokeFluteStationName[] = "# FLUTE@";

static const char JohtoMap[] = "gfx/pokegear/johto.bin";
static const char KantoMap[] = "gfx/pokegear/kanto.bin";
static const char PokedexNestIconGFX[] = "gfx/pokegear/dexmap_nest_icon.png";
static const char FlyMapLabelBorderGFX[] = "gfx/pokegear/flymap_label_border.png";

static void PokeGear_InitTilemap(void);
static void Pokegear_LoadGFX(void);

static void InitPokegearModeIndicatorArrow(void);
static uint8_t TownMap_GetCurrentLandmark(void);
static void TownMap_InitCursorAndPlayerIconPositions(void);
static void Pokegear_InitJumptableIndices(void);
static void InitPokegearTilemap(void);
static void InitPokegearTilemap_UpdateBGMap(void);
static void InitPokegearTilemap_PlacePhoneBars(void);
static void Pokegear_FinishTilemap(void);

static void PokegearClock_Init(void);
static void PokegearClock_Joypad(void);
static void Pokegear_UpdateClock(void);

static void PokegearMap_CheckRegion(void);
static void PokegearMap_Init(void);
static void PokegearMap_KantoMap(void);
static void PokegearMap_JohtoMap(void);
static void PokegearMap_ContinueMap(u8_pair_s de);
static void PokegearMap_InitPlayerIcon(uint8_t landmark);
static struct SpriteAnim* PokegearMap_InitCursor(uint8_t landmark);
static void PokegearMap_UpdateLandmarkName(uint8_t landmark);
static void PokegearMap_UpdateCursorPosition(struct SpriteAnim* bc, uint8_t landmark);

static u8_pair_s TownMap_GetKantoLandmarkLimits(void);

static void PokegearRadio_Init(void);
static void PokegearRadio_Joypad(void);

static void PokegearPhone_Init(void);
static void PokegearPhone_Joypad(void);
static void PokegearPhone_MakePhoneCall(void);
static void PokegearPhone_FinishPhoneCall(void);
static void PokegearPhone_GetDPad(void);
static void PokegearPhone_UpdateCursor(void);
static void PokegearPhone_UpdateDisplayList(void);
static void PokegearPhone_DeletePhoneNumber(void);

static void Pokegear_SwitchPage(uint8_t c, uint8_t b);
static void Pokegear_LoadTilemapRLE(const char* path);

static void v_UpdateRadioStation(void);
static void UpdateRadioStation(void);
static void Radio_BackUpFarCallParams(void (*hl)(void));

static const char* LoadStation_PokemonChannel(void);
static const char* LoadStation_OaksPokemonTalk(void);
static const char* LoadStation_PokedexShow(void);
static const char* LoadStation_PokemonMusic(void);
static const char* LoadStation_LuckyChannel(void);
static const char* LoadStation_BuenasPassword(void);
static const char* LoadStation_UnownRadio(void);
static const char* LoadStation_PlacesAndPeople(void);
static const char* LoadStation_LetsAllSing(void);
static const char* LoadStation_RocketRadio(void);
static const char* LoadStation_PokeFluteRadio(void);
static const char* LoadStation_EvolutionRadio(void);

static void TownMapBGUpdate(uint16_t hl);
static void FillJohtoMap(void);
static void FillKantoMap(void);
static void FillTownMap(const uint8_t* map);
static void TownMapPals(void);
static struct SpriteAnim* TownMapMon(void);
static struct SpriteAnim* TownMapPlayerIcon(uint8_t location);

void PokeGear(void){
    PEEK("");
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
#if DEBUG
    bit_set(wram->wPokegearFlags, POKEGEAR_RADIO_CARD_F);
    bit_set(wram->wPokegearFlags, POKEGEAR_MAP_CARD_F);
#endif
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;
    // CALL(aPokeGear_InitTilemap);
    PokeGear_InitTilemap();
    // CALL(aDelayFrame);
    DelayFrame();

    while(1) {
    // loop:
        // SET_PC(aPokeGear_loop);
        // CALL(aUpdateTime);
        UpdateTime();
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aPokegearJumptable);
        PokegearJumptable();

        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }


// done:
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // CALL(aWaitSFX);
    WaitSFX();
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // XOR_A_A;  // LOW(vBGMap0)
    // LDH_addr_A(hBGMapAddress);
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap0;
    // LD_A(SCREEN_HEIGHT_PX);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // RET;


// InitTilemap:
//     CALL(aClearBGPalettes);
//     CALL(aClearTilemap);
//     CALL(aClearSprites);
//     CALL(aDisableLCD);
//     XOR_A_A;
//     LDH_addr_A(hSCY);
//     LDH_addr_A(hSCX);
//     LD_A(0x7);
//     LDH_addr_A(hWX);
//     CALL(aPokegear_LoadGFX);
//     FARCALL(aClearSpriteAnims);
//     CALL(aInitPokegearModeIndicatorArrow);
//     LD_A(8);
//     CALL(aSkipMusic);
//     LD_A(LCDC_DEFAULT);
//     LDH_addr_A(rLCDC);
//     CALL(aTownMap_InitCursorAndPlayerIconPositions);
//     XOR_A_A;
//     LD_addr_A(wJumptableIndex);  // POKEGEARSTATE_CLOCKINIT
//     LD_addr_A(wPokegearCard);  // POKEGEARCARD_CLOCK
//     LD_addr_A(wPokegearMapRegion);  // JOHTO_REGION
//     LD_addr_A(wUnusedPokegearByte);
//     LD_addr_A(wPokegearPhoneScrollPosition);
//     LD_addr_A(wPokegearPhoneCursorPosition);
//     LD_addr_A(wPokegearPhoneSelectedPerson);
//     LD_addr_A(wPokegearRadioChannelBank);
//     LD_addr_A(wPokegearRadioChannelAddr);
//     LD_addr_A(wPokegearRadioChannelAddr + 1);
//     CALL(aPokegear_InitJumptableIndices);
//     CALL(aInitPokegearTilemap);
//     LD_B(SCGB_POKEGEAR_PALS);
//     CALL(aGetSGBLayout);
//     CALL(aSetPalettes);
//     LDH_A_addr(hCGB);
//     AND_A_A;
//     RET_Z ;
//     LD_A(0b11100100);
//     CALL(aDmgToCgbObjPal0);
//     RET;

}

static void PokeGear_InitTilemap(void) {
    // CALL(aClearBGPalettes);
    ClearBGPalettes();

    // CALL(aClearTilemap);
    ClearTilemap();

    // CALL(aClearSprites);
    ClearSprites();

    // CALL(aDisableLCD);
    DisableLCD();

    //XOR_A_A;
    //LDH_addr_A(hSCY);
    //LDH_addr_A(hSCX);
    hram->hSCY = 0;
    hram->hSCX = 0;

    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;

    // CALL(aPokegear_LoadGFX);
    Pokegear_LoadGFX();
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aInitPokegearModeIndicatorArrow);
    InitPokegearModeIndicatorArrow();
    // LD_A(8);
    // CALL(aSkipMusic);
    SkipMusic(4);

    // LD_A(LCDC_DEFAULT);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, LCDC_DEFAULT);

    //CALL(aTownMap_InitCursorAndPlayerIconPositions);
    TownMap_InitCursorAndPlayerIconPositions();

    //XOR_A_A;
    //LD_addr_A(wJumptableIndex);  // POKEGEARSTATE_CLOCKINIT
    //LD_addr_A(wPokegearCard);  // POKEGEARCARD_CLOCK
    //LD_addr_A(wPokegearMapRegion);  // JOHTO_REGION
    //LD_addr_A(wUnusedPokegearByte);
    //LD_addr_A(wPokegearPhoneScrollPosition);
    //LD_addr_A(wPokegearPhoneCursorPosition);
    //LD_addr_A(wPokegearPhoneSelectedPerson);
    //LD_addr_A(wPokegearRadioChannelBank);
    //LD_addr_A(wPokegearRadioChannelAddr);
    //LD_addr_A(wPokegearRadioChannelAddr + 1);

    wram->wJumptableIndex = POKEGEARSTATE_CLOCKINIT;  // POKEGEARSTATE_CLOCKINIT
    wram->wPokegearCard = POKEGEARCARD_CLOCK;  // POKEGEARCARD_CLOCK
    wram->wPokegearMapRegion = JOHTO_REGION;  // JOHTO_REGION
    wram->wUnusedPokegearByte = 0;
    wram->wPokegearPhoneScrollPosition = 0;
    wram->wPokegearPhoneCursorPosition = 0;
    wram->wPokegearPhoneSelectedPerson = 0;
    // gb_write(wPokegearRadioChannelBank, 0);
    gPokegearRadioChannelAddr = NULL;

    //CALL(aPokegear_InitJumptableIndices);
    Pokegear_InitJumptableIndices();

    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap();

    // LD_B(SCGB_POKEGEAR_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_POKEGEAR_PALS);

    // CALL(aSetPalettes);
    SetPalettes();
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z return;
    if(hram->hCGB == 0)
        return;
    // LD_A(0b11100100);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0(0b11100100);
    //RET;
}

static void Pokegear_LoadGFX(void){
    ClearVBank1();
    // FarDecompress_Conv(BANK(aTownMapGFX), mTownMapGFX, vTiles2);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, TownMapGFX);
    // FarDecompress_Conv(BANK(aPokegearGFX), mPokegearGFX, (vTiles2 + LEN_2BPP_TILE * 0x30));
    LoadPNG2bppAssetToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x30, PokegearGFX);
    // LD_HL(mPokegearSpritesGFX);
    // LD_DE(vTiles0);
    // LD_A(BANK(aPokegearSpritesGFX));
    // CALL(aDecompress);
    // FarDecompress_Conv(BANK(aPokegearSpritesGFX), mPokegearSpritesGFX, vTiles0);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, PokegearSpritesGFX);

    uint8_t landmark = GetWorldMapLocation(wram->wMapGroup, wram->wMapNumber);
    if(landmark == LANDMARK_FAST_SHIP) {
        LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x10, FastShipGFX, 0, 8);
        return;
    }

    // uint16_t iconptr;
    // uint8_t iconbank;
    // GetPlayerIcon_Conv(&iconptr, &iconbank);
    const char* iconpath = GetPlayerIcon();
// standing sprite
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x10, iconpath, 0, 4);
// walking sprite
    // iconptr += (12 * LEN_2BPP_TILE);
    // FarCopyBytes_Conv(vTiles0 + LEN_2BPP_TILE * 0x14, iconbank, iconptr, 4 * LEN_2BPP_TILE);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x14, iconpath, 12, 4);
}

static void InitPokegearModeIndicatorArrow(void){
    // depixel4(4, 2, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_POKEGEAR_ARROW);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_POKEGEAR_ARROW, pixel4(4, 2, 4, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x0);
    // RET;
    bc->tileID = 0x0;
}

void AnimatePokegearModeIndicatorArrow(struct SpriteAnim* bc){
    static const uint8_t XCoords[] = {
        [POKEGEARCARD_CLOCK]    = 0x00,  // POKEGEARCARD_CLOCK
        [POKEGEARCARD_MAP]      = 0x10,  // POKEGEARCARD_MAP
        [POKEGEARCARD_PHONE]    = 0x20,  // POKEGEARCARD_PHONE
        [POKEGEARCARD_RADIO]    = 0x30,  // POKEGEARCARD_RADIO
    };
    bc->xOffset = XCoords[wram->wPokegearCard];
}

static uint8_t TownMap_GetCurrentLandmark(void){
    uint8_t landmark = GetWorldMapLocation(wram->wMapGroup, wram->wMapNumber);
    if(landmark == LANDMARK_SPECIAL) {
        landmark = GetWorldMapLocation(wram->wBackupMapGroup, wram->wBackupMapNumber);
    }
    return landmark;
}

static void TownMap_InitCursorAndPlayerIconPositions(void){
    //LD_A_addr(wMapGroup);
    //LD_B_A;
    //LD_A_addr(wMapNumber);
    //LD_C_A;
    //CALL(aGetWorldMapLocation);
    uint8_t landmark = GetWorldMapLocation(gb_read(wMapGroup), gb_read(wMapNumber));

    //CP_A(LANDMARK_FAST_SHIP);
    //IF_Z goto FastShip;
    if(landmark == LANDMARK_FAST_SHIP)
    {
        //LD_addr_A(wPokegearMapPlayerIconLandmark);
        wram->wPokegearMapPlayerIconLandmark = landmark;
        //LD_A(LANDMARK_NEW_BARK_TOWN);
        //LD_addr_A(wPokegearMapCursorLandmark);
        wram->wPokegearMapCursorLandmark = LANDMARK_NEW_BARK_TOWN;
        return;
    }
    
    //CP_A(LANDMARK_SPECIAL);
    //IF_NZ goto LoadLandmark;
    if(landmark == LANDMARK_SPECIAL)
    {
        landmark = GetWorldMapLocation(wram->wBackupMapGroup, wram->wBackupMapNumber);
    }

    //LD_addr_A(wPokegearMapPlayerIconLandmark);
    //LD_addr_A(wPokegearMapCursorLandmark);
    wram->wPokegearMapPlayerIconLandmark = landmark;
    wram->wPokegearMapCursorLandmark = landmark;
    return;
}

static void Pokegear_InitJumptableIndices(void){
    wram->wJumptableIndex = POKEGEARSTATE_CLOCKINIT;
    wram->wPokegearCard = POKEGEARCARD_CLOCK;  // POKEGEARCARD_CLOCK
}

static void InitPokegearTilemap(void){
    hram->hBGMapMode = BGMAPMODE_NONE;
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x4F);
    uint8_t card = wram->wPokegearCard & (NUM_POKEGEAR_CARDS - 1);
    switch(card)
    {
        case POKEGEARCARD_CLOCK:
        {
            Pokegear_LoadTilemapRLE(ClockTilemapRLE);
            // hlcoord(12, 1, wTilemap);
            // LD_DE(mInitPokegearTilemap_switch);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(" SWITCH▶@"), coord(12, 1, wram->wTilemap));
            Textbox(coord(0, 12, wram->wTilemap), 4, 18);
            Pokegear_UpdateClock();
        }
        break;
        case POKEGEARCARD_MAP:
        {
            uint8_t landmark = wram->wPokegearMapPlayerIconLandmark;
            if(landmark != LANDMARK_FAST_SHIP && landmark >= KANTO_LANDMARK) {
                PokegearMap(1);
            }
            else {
                PokegearMap(0);
            }
            // FARCALL(aPokegearMap);
            ByteFill(coord(1, 2, wram->wTilemap), (SCREEN_WIDTH - 2), 0x07);
            *coord(0, 2, wram->wTilemap) = 0x06;
            *coord(19, 2, wram->wTilemap) = 0x17;
            // REG_A = gb_read(wPokegearMapCursorLandmark);
            // CALL(aPokegearMap_UpdateLandmarkName);
            PokegearMap_UpdateLandmarkName(wram->wPokegearMapCursorLandmark);
        }
        break;
        case POKEGEARCARD_PHONE:
        {
            Pokegear_LoadTilemapRLE(PhoneTilemapRLE);
            Textbox(coord(0, 12, wram->wTilemap), 4, 18);
            InitPokegearTilemap_PlacePhoneBars();
            // CALL(aPokegearPhone_UpdateDisplayList);
            PokegearPhone_UpdateDisplayList();
            //RET;
        }
        break;
        case POKEGEARCARD_RADIO:
        {
            Pokegear_LoadTilemapRLE(RadioTilemapRLE);
            Textbox(coord(0, 12, wram->wTilemap), 4, 18);
        }
        break;
    }

    // CALL(aPokegear_FinishTilemap);
    Pokegear_FinishTilemap();

    // FARCALL(aTownMapPals);
    TownMapPals();
    if(wram->wPokegearMapRegion == KANTO_REGION)
    {
        hram->hBGMapAddress = vBGMap1;
        InitPokegearTilemap_UpdateBGMap();
        hram->hWY = 0;
    }
    else 
    {
        hram->hBGMapAddress = vBGMap0;
        InitPokegearTilemap_UpdateBGMap();
        hram->hWY = SCREEN_HEIGHT_PX;
    }
// swap region maps
    wram->wPokegearMapRegion = (wram->wPokegearMapRegion & (NUM_REGIONS - 1)) ^ 1;
}

static void InitPokegearTilemap_UpdateBGMap(void) {
    if(hram->hCGB == 0)
    {
        // CALL(aWaitBGMap);
        WaitBGMap();
        return;
    }

    hram->hBGMapMode = BGMAPMODE_UPDATE_ATTRS;
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames(3);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
}

static void InitPokegearTilemap_PlacePhoneBars(void) {
    tile_t* hl = coord(17, 1, wram->wTilemap);
    uint8_t tile = 0x3C;
    *(hl++) = tile++;
    *hl = tile++;
    hl = coord(17, 2, wram->wTilemap);
    *(hl++) = tile;

    // CALL(aGetMapPhoneService);
    uint8_t srv = GetMapPhoneService();
    if(srv != 0)
    {
        return;
    }
    *coord(18, 2, wram->wTilemap) = 0x3F;
}

static void Pokegear_FinishTilemap(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(0x8);
    // LD_A(0x4f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), 0x8, 0x4f);

    // hlcoord(0, 1, wTilemap);
    // LD_BC(0x8);
    // LD_A(0x4f);
    // CALL(aByteFill);
    ByteFill(coord(0, 1, wram->wTilemap), 0x8, 0x4f);

    // LD_DE(wPokegearFlags);
    // LD_A_de;
    uint8_t flags = wram->wPokegearFlags;

    // BIT_A(POKEGEAR_MAP_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlaceMapIcon);
    if(flags & (1 << POKEGEAR_MAP_CARD_F))
    {
        // hlcoord(2, 0, wTilemap);
        uint8_t* hl = coord(2, 0, wram->wTilemap);

        // LD_A(0x40);
        // LD_hli_A;
        hl[0] = 0x40;

        // INC_A;
        // LD_hld_A;
        hl[1] = 0x41;

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        hl[0] = 0x50;

        // INC_A;
        // LD_hld_A;
        hl[1] = 0x51;
    }

    // LD_A_de;
    // BIT_A(POKEGEAR_PHONE_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlacePhoneIcon);
    if(flags & (1 << POKEGEAR_PHONE_CARD_F))
    {
        // hlcoord(4, 0, wTilemap);
        uint8_t* hl = coord(4, 0, wram->wTilemap);

        // LD_A(0x44);
        // LD_hli_A;
        hl[0] = 0x44;

        // INC_A;
        // LD_hld_A;
        hl[1] = 0x45;

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        hl[0] = 0x54;

        // INC_A;
        // LD_hld_A;
        hl[1] = 0x55;
    }

    // LD_A_de;
    // BIT_A(POKEGEAR_RADIO_CARD_F);
    // CALL_NZ (aPokegear_FinishTilemap_PlaceRadioIcon);
    if(flags & (1 << POKEGEAR_RADIO_CARD_F))
    {
        // hlcoord(6, 0, wTilemap);
        tile_t* hl = coord(6, 0, wram->wTilemap);

        // LD_A(0x42);
        // LD_hli_A;
        *(hl++) = 0x42;

        // INC_A;
        // LD_hld_A;
        *(hl--) = 0x43;

        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += 0x14;

        // ADD_A(0xf);
        // LD_hli_A;
        *(hl++) = 0x52;

        // INC_A;
        // LD_hld_A;
        *(hl--) = 0x53;
    }

    // hlcoord(0, 0, wTilemap);
    uint8_t* hl = coord(0, 0, wram->wTilemap);

    // LD_A(0x46);
    // LD_hli_A;
    hl[0] = 0x46;

    // INC_A;
    // LD_hld_A;
    hl[1] = 0x47;

    // LD_BC(0x14);
    // ADD_HL_BC;
    hl += 0x14;

    // ADD_A(0xf);
    // LD_hli_A;
    hl[0] = 0x56;

    // INC_A;
    // LD_hld_A;
    hl[1] = 0x57;
}

void PokegearJumptable(void) {
    //jumptable ['.Jumptable', 'wJumptableIndex']
    // jumptable(mPokegearJumptable_Jumptable, wJumptableIndex);
    // return;


// Jumptable:
//  entries correspond to POKEGEARSTATE_* constants
    switch(wram->wJumptableIndex)
    {
        case POKEGEARSTATE_CLOCKINIT:       return PokegearClock_Init();
        case POKEGEARSTATE_CLOCKJOYPAD:     return PokegearClock_Joypad();
        case POKEGEARSTATE_MAPCHECKREGION:  return PokegearMap_CheckRegion();
        case POKEGEARSTATE_JOHTOMAPINIT:    return PokegearMap_Init();
        case POKEGEARSTATE_JOHTOMAPJOYPAD:  return PokegearMap_JohtoMap();
        case POKEGEARSTATE_KANTOMAPINIT:    return PokegearMap_Init();
        case POKEGEARSTATE_KANTOMAPJOYPAD:  return PokegearMap_KantoMap();
        case POKEGEARSTATE_PHONEINIT:       return PokegearPhone_Init();
        case POKEGEARSTATE_PHONEJOYPAD:     return PokegearPhone_Joypad();
        case POKEGEARSTATE_MAKEPHONECALL:   return PokegearPhone_MakePhoneCall();
        case POKEGEARSTATE_FINISHPHONECALL: return PokegearPhone_FinishPhoneCall();
        case POKEGEARSTATE_RADIOINIT:       return PokegearRadio_Init();
        case POKEGEARSTATE_RADIOJOYPAD:     return PokegearRadio_Joypad();
        default: return;
    }
    //dw ['PokegearClock_Init'];
    //dw ['PokegearClock_Joypad'];
    //dw ['PokegearMap_CheckRegion'];
    //dw ['PokegearMap_Init'];
    //dw ['PokegearMap_JohtoMap'];
    //dw ['PokegearMap_Init'];
    //dw ['PokegearMap_KantoMap'];
    //dw ['PokegearPhone_Init'];
    //dw ['PokegearPhone_Joypad'];
    //dw ['PokegearPhone_MakePhoneCall'];
    //dw ['PokegearPhone_FinishPhoneCall'];
    //dw ['PokegearRadio_Init'];
    //dw ['PokegearRadio_Joypad'];
}

static void PokegearClock_Init(void) {
    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap();

    // REG_HL = mPokegearPressButtonText;
    // CALL(aPrintText);
    PrintText(PokegearPressButtonText);

    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;

    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // RET;

}

static void PokegearClock_Joypad_UpdateClock(void) {
    // SET_PC(aPokegearClock_Joypad_UpdateClock);
    // PEEK("UpdateClock");
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aPokegear_UpdateClock);
    // Pokegear_UpdateClock();
    Pokegear_UpdateClock();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

static void PokegearClock_Joypad(void) {
    // SET_PC(aPokegearClock_Joypad);
    // CALL(aPokegearClock_Joypad_UpdateClock);
    PokegearClock_Joypad_UpdateClock();
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(A_BUTTON | B_BUTTON | START | SELECT);
    // IF_NZ goto quit;
    if(hram->hJoyLast & (A_BUTTON | B_BUTTON | START | SELECT)) {
    // quit:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // RET_Z ;
    if(!(hram->hJoyLast & D_RIGHT))
        return;
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_MAP_CARD_F);
    // IF_Z goto no_map_card;
    if(bit_test(wram->wPokegearFlags, POKEGEAR_MAP_CARD_F)) {
        // LD_C(POKEGEARSTATE_MAPCHECKREGION);
        // LD_B(POKEGEARCARD_MAP);
        // goto done;
        Pokegear_SwitchPage(POKEGEARSTATE_MAPCHECKREGION, POKEGEARCARD_MAP);
        return;
    }


// no_map_card:
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_PHONE_CARD_F);
    // IF_Z goto no_phone_card;
    else if(bit_test(wram->wPokegearFlags, POKEGEAR_PHONE_CARD_F)) {
        // LD_C(POKEGEARSTATE_PHONEINIT);
        // LD_B(POKEGEARCARD_PHONE);
        // goto done;
        Pokegear_SwitchPage(POKEGEARSTATE_PHONEINIT, POKEGEARCARD_PHONE);
        return;
    }


// no_phone_card:
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_RADIO_CARD_F);
    // RET_Z ;
    else if(bit_test(wram->wPokegearFlags, POKEGEAR_RADIO_CARD_F)) {
        // LD_C(POKEGEARSTATE_RADIOINIT);
        // LD_B(POKEGEARCARD_RADIO);
    // done:
        // CALL(aPokegear_SwitchPage);
        // return;
        // RET;
        Pokegear_SwitchPage(POKEGEARSTATE_RADIOINIT, POKEGEARCARD_RADIO);
        return;
    }

    else {
        return;
    }


// quit:
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    // return;
    // RET;


// UpdateClock:
    // // PEEK("UpdateClock");
    // SET_PC(aPokegearClock_Joypad_UpdateClock);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    // // CALL(aPokegear_UpdateClock);
    // Pokegear_UpdateClock();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    // RET;

}

static void Pokegear_UpdateClock(void){
    static const txt_cmd_s GearTodayText[] = {
        text_far(v_GearTodayText)
        text_end
    };
    // PEEK("UpdateClock");
    UpdateTime();
    // hlcoord(3, 5, wTilemap);
    // LD_BC((5 << 8) | 14);
    // CALL(aClearBox);
    ClearBox(coord(3, 5, wram->wTilemap), 14, 5);
    // LDH_A_addr(hHours);
    // LD_B_A;
    // LDH_A_addr(hMinutes);
    // LD_C_A;
    // decoord(6, 8, wTilemap);
    // FARCALL(aPrintHoursMins);
    PrintHoursMins(wram->wTilemap + coordidx(6, 8), hram->hHours, hram->hMinutes);
    // LD_HL(mPokegear_UpdateClock_GearTodayText);
    // bccoord(6, 6, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC(coord(6, 6, wram->wTilemap), GearTodayText);
}

static void PokegearMap_CheckRegion(void){
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CP_A(LANDMARK_FAST_SHIP);
    // IF_Z goto johto;
    // CP_A(KANTO_LANDMARK);
    // IF_NC goto kanto;
    if(wram->wPokegearMapPlayerIconLandmark != LANDMARK_FAST_SHIP
    && wram->wPokegearMapPlayerIconLandmark >= KANTO_LANDMARK) {
    // kanto:
        // LD_A(POKEGEARSTATE_KANTOMAPINIT);
        wram->wJumptableIndex = POKEGEARSTATE_KANTOMAPINIT;
    }
    else {
    // johto:
        // LD_A(POKEGEARSTATE_JOHTOMAPINIT);
        wram->wJumptableIndex = POKEGEARSTATE_JOHTOMAPINIT;
        // goto done;
        // RET;
    }

// done:
    // LD_addr_A(wJumptableIndex);
    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // RET;
}

static void PokegearMap_Init(void){
    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap();
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CALL(aPokegearMap_InitPlayerIcon);
    PokegearMap_InitPlayerIcon(wram->wPokegearMapPlayerIconLandmark);
    // LD_A_addr(wPokegearMapCursorLandmark);
    // CALL(aPokegearMap_InitCursor);
    // LD_A_C;
    // LD_addr_A(wPokegearMapCursorObjectPointer);
    // LD_A_B;
    // LD_addr_A(wPokegearMapCursorObjectPointer + 1);
    gPokegearMapCursorObjectPointer = PokegearMap_InitCursor(wram->wPokegearMapPlayerIconLandmark);
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // return;
    // RET;
}

static void PokegearMap_KantoMap(void){
    // CALL(aTownMap_GetKantoLandmarkLimits);
    // JR(mPokegearMap_ContinueMap);
    return PokegearMap_ContinueMap(TownMap_GetKantoLandmarkLimits());
}

static void PokegearMap_JohtoMap(void){
    // LD_D(LANDMARK_SILVER_CAVE);
    // LD_E(LANDMARK_NEW_BARK_TOWN);
    return PokegearMap_ContinueMap(u8_pair(LANDMARK_SILVER_CAVE, LANDMARK_NEW_BARK_TOWN));
}

static void PokegearMap_ContinueMap_DPad(u8_pair_s de) {
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(hram->hJoyLast & D_UP) {
    // up:
        // LD_HL(wPokegearMapCursorLandmark);
        // LD_A_hl;
        // CP_A_D;
        // IF_C goto wrap_around_up;
        if(wram->wPokegearMapCursorLandmark >= de.a) {
            // LD_A_E;
            // DEC_A;
            // LD_hl_A;
            wram->wPokegearMapCursorLandmark = de.b - 1;
        }

    // wrap_around_up:
        // INC_hl;
        wram->wPokegearMapCursorLandmark++;
        // goto done_dpad;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_HL(wPokegearMapCursorLandmark);
        // LD_A_hl;
        // CP_A_E;
        // IF_NZ goto wrap_around_down;
        if(wram->wPokegearMapCursorLandmark == de.b) {
            // LD_A_D;
            // INC_A;
            // LD_hl_A;
            wram->wPokegearMapCursorLandmark = de.a + 1;
        }

    // wrap_around_down:
        // DEC_hl;
        wram->wPokegearMapCursorLandmark--;
    }
    else {
        return;
        // RET;
    }

// done_dpad:
    // LD_A_addr(wPokegearMapCursorLandmark);
    // CALL(aPokegearMap_UpdateLandmarkName);
    PokegearMap_UpdateLandmarkName(wram->wPokegearMapCursorLandmark);
    // LD_A_addr(wPokegearMapCursorObjectPointer);
    // LD_C_A;
    // LD_A_addr(wPokegearMapCursorObjectPointer + 1);
    // LD_B_A;
    // LD_A_addr(wPokegearMapCursorLandmark);
    // CALL(aPokegearMap_UpdateCursorPosition);
    PokegearMap_UpdateCursorPosition(gPokegearMapCursorObjectPointer, wram->wPokegearMapCursorLandmark);
    // RET;
    // return;
}

static void PokegearMap_ContinueMap(u8_pair_s de){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto cancel;
    if(hram->hJoyLast & B_BUTTON) {
    // cancel:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        return;
        // RET;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    if(hram->hJoyLast & D_RIGHT) {
    // right:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_PHONE_CARD_F);
        // IF_Z goto no_phone;
        if(bit_test(wram->wPokegearFlags, POKEGEAR_PHONE_CARD_F)) {
            // LD_C(POKEGEARSTATE_PHONEINIT);
            // LD_B(POKEGEARCARD_PHONE);
            Pokegear_SwitchPage(POKEGEARSTATE_PHONEINIT, POKEGEARCARD_PHONE);
            // goto done;
        }
    // no_phone:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_RADIO_CARD_F);
        // RET_Z ;
        // LD_C(POKEGEARSTATE_RADIOINIT);
        // LD_B(POKEGEARCARD_RADIO);
        // goto done;
        else if(bit_test(wram->wPokegearFlags, POKEGEAR_RADIO_CARD_F)) {
            Pokegear_SwitchPage(POKEGEARSTATE_RADIOINIT, POKEGEARCARD_RADIO);
        }
        
        return;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(hram->hJoyLast & D_LEFT) {
    // left:
        // LD_C(POKEGEARSTATE_CLOCKINIT);
        // LD_B(POKEGEARCARD_CLOCK);

    // done:
        // CALL(aPokegear_SwitchPage);
        // RET;
        return Pokegear_SwitchPage(POKEGEARSTATE_CLOCKINIT, POKEGEARCARD_CLOCK);
    }
    // CALL(aPokegearMap_ContinueMap_DPad);
    PokegearMap_ContinueMap_DPad(de);
    //RET;
}

static void PokegearMap_InitPlayerIcon(uint8_t landmark){
    // PUSH_AF;
    //depixel ['0', '0']
    // depixel2(0, 0);
    // LD_B(SPRITE_ANIM_INDEX_RED_WALK);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_gender;
    // LD_B(SPRITE_ANIM_INDEX_BLUE_WALK);
    uint8_t b = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? SPRITE_ANIM_INDEX_BLUE_WALK: SPRITE_ANIM_INDEX_RED_WALK;

// got_gender:
    // LD_A_B;
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(b, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x10);
    bc->tileID = 0x10;
    // POP_AF;
    // LD_E_A;
    // PUSH_BC;
    // FARCALL(aGetLandmarkCoords);
    struct Coords coord = GetLandmarkCoords(landmark);
    // POP_BC;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->xCoord = coord.x;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yCoord = coord.y;
    // RET;
}

static struct SpriteAnim* PokegearMap_InitCursor(uint8_t landmark) {
    // PUSH_AF;
    // depixel2(0, 0);
    // LD_A(SPRITE_ANIM_INDEX_POKEGEAR_ARROW);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_POKEGEAR_ARROW, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x04);
    bc->tileID = 0x04;
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_NULL);
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
    // POP_AF;
    // PUSH_BC;
    // CALL(aPokegearMap_UpdateCursorPosition);
    PokegearMap_UpdateCursorPosition(bc, landmark);
    // POP_BC;
    // RET;
    return bc;
}

static void PokegearMap_UpdateLandmarkName(uint8_t landmark){
    // hlcoord(8, 0, wTilemap);
    // LD_BC((2 << 8) | 12);
    // CALL(aClearBox);
    ClearBox(coord(8, 0, wram->wTilemap), 12, 2);

    // LD_E_A;
    // REG_DE = landmark;
    // PUSH_DE;
    // FARCALL(aGetLandmarkName);
    GetLandmarkName(landmark);
    // POP_DE;
    // FARCALL(aTownMap_ConvertLineBreakCharacters);
    TownMap_ConvertLineBreakCharacters();

    // hlcoord(8, 0, wTilemap);
    // LD_hl(0x34);
    *coord(8, 0, wram->wTilemap) = 0x34;
}

static void PokegearMap_UpdateCursorPosition(struct SpriteAnim* bc, uint8_t landmark){
    // PUSH_BC;
    // LD_E_A;
    // FARCALL(aGetLandmarkCoords);
    struct Coords coord = GetLandmarkCoords(landmark);
    // POP_BC;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->xCoord = coord.x;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yCoord = coord.y;
    // RET;
}

static u8_pair_s TownMap_GetKantoLandmarkLimits(void){
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
    // IF_Z goto not_hof;
    if(bit_test(wram->wStatusFlags, STATUSFLAGS_HALL_OF_FAME_F)) {
        // LD_D(LANDMARK_ROUTE_28);
        // LD_E(LANDMARK_PALLET_TOWN);
        return u8_pair(LANDMARK_ROUTE_28, LANDMARK_PALLET_TOWN);
    }
    else {
    // not_hof:
        // LD_D(LANDMARK_ROUTE_28);
        // LD_E(LANDMARK_VICTORY_ROAD);
        // RET;
        return u8_pair(LANDMARK_ROUTE_28, LANDMARK_VICTORY_ROAD);
    }
    // RET;
}

static void PokegearRadio_Init(void){
    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap();
    //depixel ['4', '10', '4', '4']
    // depixel4(4, 10, 4, 4);
    // LD_A(SPRITE_ANIM_INDEX_RADIO_TUNING_KNOB);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_RADIO_TUNING_KNOB, pixel4(4, 10, 4, 4));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x08);
    bc->tileID = 0x08;
    // CALL(av_UpdateRadioStation);
    v_UpdateRadioStation();
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    //RET;

}

static void PokegearRadio_Joypad(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto cancel;
    if(hram->hJoyLast & B_BUTTON) {
    // cancel:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        //RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(hram->hJoyLast & D_LEFT) {
    // left:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_PHONE_CARD_F);
        // IF_Z goto no_phone;
        if(bit_set(wram->wPokegearFlags, POKEGEAR_PHONE_CARD_F)) {
            // LD_C(POKEGEARSTATE_PHONEINIT);
            // LD_B(POKEGEARCARD_PHONE);
            // goto switch_page;
            Pokegear_SwitchPage(POKEGEARSTATE_PHONEINIT, POKEGEARCARD_PHONE);
        }

    // no_phone:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_MAP_CARD_F);
        // IF_Z goto no_map;
        else if(bit_set(wram->wPokegearFlags, POKEGEAR_MAP_CARD_F)) {
            // LD_C(POKEGEARSTATE_MAPCHECKREGION);
            // LD_B(POKEGEARCARD_MAP);
            // goto switch_page;
            Pokegear_SwitchPage(POKEGEARSTATE_MAPCHECKREGION, POKEGEARCARD_MAP);
        }

    // no_map:
        else {
            // LD_C(POKEGEARSTATE_CLOCKINIT);
            // LD_B(POKEGEARCARD_CLOCK);
            Pokegear_SwitchPage(POKEGEARSTATE_CLOCKINIT, POKEGEARCARD_CLOCK);
        }

    // switch_page:
        // CALL(aPokegear_SwitchPage);
        return;
        //RET;
    }
    // LD_A_addr(wPokegearRadioChannelAddr);
    // LD_L_A;
    // LD_A_addr(wPokegearRadioChannelAddr + 1);
    // LD_H_A;
    // LD_A_addr(wPokegearRadioChannelBank);
    // AND_A_A;
    // RET_Z ;
    if(gPokegearRadioChannelAddr == NULL)
        return;
    // RST(aFarCall);
    return gPokegearRadioChannelAddr();
    //RET;

}

static void PokegearPhone_Init(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // XOR_A_A;
    // LD_addr_A(wPokegearPhoneScrollPosition);
    // LD_addr_A(wPokegearPhoneCursorPosition);
    // LD_addr_A(wPokegearPhoneSelectedPerson);
    wram->wPokegearPhoneScrollPosition = 0;
    wram->wPokegearPhoneCursorPosition = 0;
    wram->wPokegearPhoneSelectedPerson = 0;
    // CALL(aInitPokegearTilemap);
    InitPokegearTilemap();
    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // LD_HL(mPokegearAskWhoCallText);
    // CALL(aPrintText);
    PrintText(PokegearAskWhoCallText);
    // RET;

}

static void PokegearPhone_Joypad(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    uint8_t pressed = hram->hJoyPressed;
    // AND_A(B_BUTTON);
    // IF_NZ goto b;
    if(pressed & B_BUTTON) {
    // b:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto a;
    else if(pressed & A_BUTTON) {
    // a:
        // LD_HL(wPhoneList);
        // LD_A_addr(wPokegearPhoneScrollPosition);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // LD_A_addr(wPokegearPhoneCursorPosition);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // LD_A_hl;
        uint8_t contact = wram->wPhoneList[wram->wPokegearPhoneScrollPosition + wram->wPokegearPhoneCursorPosition];
        // AND_A_A;
        // RET_Z ;
        if(contact == 0)
            return;
        // LD_addr_A(wPokegearPhoneSelectedPerson);
        wram->wPokegearPhoneSelectedPerson = contact;
        // hlcoord(1, 4, wTilemap);
        // LD_A_addr(wPokegearPhoneCursorPosition);
        // LD_BC(SCREEN_WIDTH * 2);
        // CALL(aAddNTimes);
        // LD_hl(0xec);
        *coord(1, 4 + wram->wPokegearPhoneCursorPosition * 2, wram->wTilemap) = CHAR_RIGHT_CURSOR_SEL;
        // CALL(aPokegearPhoneContactSubmenu);
        // IF_C goto quit_submenu;
        if(PokegearPhoneContactSubmenu()) {
        // quit_submenu:
            // LD_A(POKEGEARSTATE_PHONEJOYPAD);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = POKEGEARSTATE_PHONEJOYPAD;
            // RET;
            return;
        }
        // LD_HL(wJumptableIndex);
        // INC_hl;
        wram->wJumptableIndex++;
        // RET;
        return;
    }
    // LD_HL(hJoyLast);
    // LD_A_hl;
    uint8_t last = hram->hJoyLast;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(last & D_LEFT) {
    // left:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_MAP_CARD_F);
        // IF_Z goto no_map;
        if(bit_test(wram->wPokegearFlags, POKEGEAR_MAP_CARD_F)) {
            // LD_C(POKEGEARSTATE_MAPCHECKREGION);
            // LD_B(POKEGEARCARD_MAP);
            // goto switch_page;
            Pokegear_SwitchPage(POKEGEARSTATE_MAPCHECKREGION, POKEGEARCARD_MAP);
            return;
        }
        else {
        // no_map:
            // LD_C(POKEGEARSTATE_CLOCKINIT);
            // LD_B(POKEGEARCARD_CLOCK);
            // goto switch_page;
            Pokegear_SwitchPage(POKEGEARSTATE_CLOCKINIT, POKEGEARCARD_CLOCK);
            return;
        }
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    else if(last & D_RIGHT) {
    // right:
        // LD_A_addr(wPokegearFlags);
        // BIT_A(POKEGEAR_RADIO_CARD_F);
        // RET_Z ;
        if(!bit_test(wram->wPokegearFlags, POKEGEAR_RADIO_CARD_F))
            return;
        // LD_C(POKEGEARSTATE_RADIOINIT);
        // LD_B(POKEGEARCARD_RADIO);
        Pokegear_SwitchPage(POKEGEARSTATE_RADIOINIT, POKEGEARCARD_RADIO);
        return;
    }
    // CALL(aPokegearPhone_GetDPad);
    PokegearPhone_GetDPad();
    // RET;
    return;

// switch_page:
    // CALL(aPokegear_SwitchPage);
    // return;
    // RET;

}

static void PokegearPhone_MakePhoneCall(void){
    static const txt_cmd_s GearEllipseText[] = {
        text_far(v_GearEllipseText)
        text_end
    };
    static const txt_cmd_s GearOutOfServiceText[] = {
        text_far(v_GearOutOfServiceText)
        text_end
    };
    // CALL(aGetMapPhoneService);
    // AND_A_A;
    // IF_NZ goto no_service;
    if(!GetMapPhoneService()) {
        // LD_HL(wOptions);
        // RES_hl(NO_TEXT_SCROLL);
        bit_reset(wram->wOptions, NO_TEXT_SCROLL);
        // XOR_A_A;
        // LDH_addr_A(hInMenu);
        hram->hInMenu = FALSE;
        // LD_DE(SFX_CALL);
        // CALL(aPlaySFX);
        PlaySFX(SFX_CALL);
        // LD_HL(mPokegearPhone_MakePhoneCall_GearEllipseText);
        // CALL(aPrintText);
        PrintText(GearEllipseText);
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_DE(SFX_CALL);
        // CALL(aPlaySFX);
        PlaySFX(SFX_CALL);
        // LD_HL(mPokegearPhone_MakePhoneCall_GearEllipseText);
        // CALL(aPrintText);
        PrintText(GearEllipseText);
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_A_addr(wPokegearPhoneSelectedPerson);
        // LD_B_A;
        // CALL(aMakePhoneCallFromPokegear);
        MakePhoneCallFromPokegear(wram->wPokegearPhoneSelectedPerson);
        // LD_C(10);
        // CALL(aDelayFrames);
        DelayFrames(10);
        // LD_HL(wOptions);
        // SET_hl(NO_TEXT_SCROLL);
        bit_set(wram->wOptions, NO_TEXT_SCROLL);
        // LD_A(0x1);
        // LDH_addr_A(hInMenu);
        hram->hInMenu = TRUE;
        // CALL(aPokegearPhone_UpdateCursor);
        PokegearPhone_UpdateCursor();
        // LD_HL(wJumptableIndex);
        // INC_hl;
        wram->wJumptableIndex++;
        //RET;
    }
    else {
    // no_service:
        // FARCALL(aPhone_NoSignal);
        Phone_NoSignal();
        // LD_HL(mPokegearPhone_MakePhoneCall_GearOutOfServiceText);
        // CALL(aPrintText);
        PrintText(GearOutOfServiceText);
        // LD_A(POKEGEARSTATE_PHONEJOYPAD);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = POKEGEARSTATE_PHONEJOYPAD;
        // LD_HL(mPokegearAskWhoCallText);
        // CALL(aPrintText);
        PrintText(PokegearAskWhoCallText);
        //RET;
    }
}

static void PokegearPhone_FinishPhoneCall(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON | B_BUTTON);
    // RET_Z ;
    if((hram->hJoyPressed & (A_BUTTON | B_BUTTON)) == 0)
        return;
    // FARCALL(aHangUp);
    HangUp();
    // LD_A(POKEGEARSTATE_PHONEJOYPAD);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = POKEGEARSTATE_PHONEJOYPAD;
    // LD_HL(mPokegearAskWhoCallText);
    // CALL(aPrintText);
    PrintText(PokegearAskWhoCallText);
    //RET;

}

static void PokegearPhone_GetDPad(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(hram->hJoyLast & D_UP) {
    // up:
        // LD_HL(wPokegearPhoneCursorPosition);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto scroll_page_up;
        if(wram->wPokegearPhoneCursorPosition == 0) {
        // scroll_page_up:
            // LD_HL(wPokegearPhoneScrollPosition);
            // LD_A_hl;
            // AND_A_A;
            // RET_Z ;
            if(wram->wPokegearPhoneScrollPosition == 0)
                return;
            // DEC_hl;
            --wram->wPokegearPhoneScrollPosition;
            goto done_joypad_update_page;
        }
        // DEC_hl;
        --wram->wPokegearPhoneCursorPosition;
        goto done_joypad_same_page;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_HL(wPokegearPhoneCursorPosition);
        // LD_A_hl;
        // CP_A(PHONE_DISPLAY_HEIGHT - 1);
        // IF_NC goto scroll_page_down;
        if(wram->wPokegearPhoneCursorPosition >= PHONE_DISPLAY_HEIGHT - 1) {
        // scroll_page_down:
            // LD_HL(wPokegearPhoneScrollPosition);
            // LD_A_hl;
            // CP_A(CONTACT_LIST_SIZE - PHONE_DISPLAY_HEIGHT);
            // RET_NC ;
            if(wram->wPokegearPhoneScrollPosition >= CONTACT_LIST_SIZE - PHONE_DISPLAY_HEIGHT)
                return;
            // INC_hl;
            ++wram->wPokegearPhoneScrollPosition;
            goto done_joypad_update_page;
        }
        // INC_hl;
        ++wram->wPokegearPhoneCursorPosition;
        goto done_joypad_same_page;
    }
    // RET;
    return;


done_joypad_same_page:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aPokegearPhone_UpdateCursor);
    PokegearPhone_UpdateCursor();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // RET;
    return;


done_joypad_update_page:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aPokegearPhone_UpdateDisplayList);
    PokegearPhone_UpdateDisplayList();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // RET;
    return;

}

static void PokegearPhone_UpdateCursor(void){
    // LD_A(0x7f);
    uint8_t a = CHAR_SPACE;
    for(int y = 0; y < PHONE_DISPLAY_HEIGHT; y++){
        // hlcoord(1, 4 + y * 2, wTilemap);
        // LD_hl_A;
        *coord(1, 4 + y * 2, wram->wTilemap) = a;
    }
    // hlcoord(1, 4, wTilemap);
    // LD_A_addr(wPokegearPhoneCursorPosition);
    // LD_BC(2 * SCREEN_WIDTH);
    // CALL(aAddNTimes);
    // LD_hl(0xed);
    *coord(1, 4 + wram->wPokegearPhoneCursorPosition * 2, wram->wTilemap) = CHAR_RIGHT_CURSOR;
    // RET;

}

static void PokegearPhone_UpdateDisplayList(void){
    // hlcoord(1, 3, wTilemap);
    tile_t* hl = coord(1, 3, wram->wTilemap);
    // LD_B(PHONE_DISPLAY_HEIGHT * 2 + 1);
    // LD_A(0x7f);

    for(uint32_t b = 0; b < PHONE_DISPLAY_HEIGHT * 2 + 1; ++b) {
    // row:
        // LD_C(SCREEN_WIDTH - 2);
        for(uint32_t c = 0; c < SCREEN_WIDTH - 2; ++c) {
        // col:
            // LD_hli_A;
            // DEC_C;
            // IF_NZ goto col;
            hl[c + (SCREEN_WIDTH * b)] = CHAR_SPACE;
        }
        // INC_HL;
        // INC_HL;
        // DEC_B;
        // IF_NZ goto row;
    }
    // LD_A_addr(wPokegearPhoneScrollPosition);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPhoneList);
    // ADD_HL_DE;
    uint8_t* de = wram->wPhoneList + wram->wPokegearPhoneScrollPosition;
    // XOR_A_A;
    // LD_addr_A(wPokegearPhoneDisplayPosition);
    wram->wPokegearPhoneDisplayPosition = 0;

    do {
    // loop:
        // LD_A_hli;
        uint8_t contact = de[wram->wPokegearPhoneDisplayPosition];
        // PUSH_HL;
        // PUSH_AF;
        // hlcoord(2, 4, wTilemap);
        // LD_A_addr(wPokegearPhoneDisplayPosition);
        // LD_BC(2 * SCREEN_WIDTH);
        // CALL(aAddNTimes);
        // LD_D_H;
        // LD_E_L;
        // POP_AF;
        // LD_B_A;
        // CALL(aGetCallerClassAndName);
        GetCallerClassAndName(coord(2, 4 + (2 * wram->wPokegearPhoneDisplayPosition), wram->wTilemap), contact);
        // POP_HL;
        // LD_A_addr(wPokegearPhoneDisplayPosition);
        // INC_A;
        // LD_addr_A(wPokegearPhoneDisplayPosition);
        // CP_A(PHONE_DISPLAY_HEIGHT);
        // IF_C goto loop;
    } while(++wram->wPokegearPhoneDisplayPosition < PHONE_DISPLAY_HEIGHT);
    // CALL(aPokegearPhone_UpdateCursor);
    PokegearPhone_UpdateCursor();
    // RET;

}

static void PokegearPhone_DeletePhoneNumber(void){
    // LD_HL(wPhoneList);
    // LD_A_addr(wPokegearPhoneScrollPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_addr(wPokegearPhoneCursorPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    uint8_t* hl = wram->wPhoneList + wram->wPokegearPhoneScrollPosition + wram->wPokegearPhoneCursorPosition;
    // LD_hl(0);
    *hl = 0;
    // LD_HL(wPhoneList);
    // LD_C(CONTACT_LIST_SIZE);

    for(uint32_t i = 0; i < CONTACT_LIST_SIZE; ++i) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_NZ goto skip;
        if(wram->wPhoneList[i] == 0) {
            // LD_A_hld;
            // LD_hli_A;
            // LD_hl(0);
            wram->wPhoneList[i] = wram->wPhoneList[i+1];
            wram->wPhoneList[i+1] = 0;
        }

    // skip:
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;

}

struct PokegearPhoneSubmenu {
    tile_t* coord;
    uint8_t count;
    const char* strings;
};

static void PokegearPhoneContactSubmenu_UpdateCursor(const struct PokegearPhoneSubmenu* de) {
    // PUSH_DE;
    // LD_A_de;
    // INC_DE;
    // LD_L_A;
    // LD_A_de;
    // INC_DE;
    // LD_H_A;
    tile_t* hl = de->coord;
    // LD_A_de;
    // LD_C_A;
    // PUSH_HL;
    // LD_A(0x7f);
    // LD_DE(SCREEN_WIDTH * 2);

    for(uint32_t i = 0; i < de->count; ++i) {
    // clear_column:
        // LD_hl_A;
        // ADD_HL_DE;
        hl[SCREEN_WIDTH * 2 * i] = CHAR_SPACE;
        // DEC_C;
        // IF_NZ goto clear_column;
    }
    // POP_HL;
    // LD_A_addr(wPokegearPhoneSubmenuCursor);
    // LD_BC(SCREEN_WIDTH * 2);
    // CALL(aAddNTimes);
    // LD_hl(0xed);
    hl[SCREEN_WIDTH * 2 * wram->wPokegearPhoneSubmenuCursor] = CHAR_RIGHT_CURSOR;
    // POP_DE;
    // RET;
}

bool PokegearPhoneContactSubmenu(void){
    static const struct PokegearPhoneSubmenu Submenus[] = {
        {
            //dwcoord ['10', '6'];
            .coord = coord(10, 6, wram_ptr(wTilemap)),
            //db ['2'];
            .count = 3,
            .strings =
                //db ['"CALL"'];
                "CALL" t_next
                //next ['"DELETE"']
                "DELETE" t_next
                //next ['"CANCEL"']
                "CANCEL@",
                //db ['"@"'];
        },
        {
            //dwcoord ['10', '8'];
            .coord = coord(10, 8, wram_ptr(wTilemap)),
            //db ['2'];
            .count = 2,
            .strings =
                //db ['"CALL"'];
                "CALL" t_next
                //next ['"CANCEL"']
                "CANCEL@",
                //db ['"@"'];
        }
    };
    // LD_HL(wPhoneList);
    // LD_A_addr(wPokegearPhoneScrollPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_addr(wPokegearPhoneCursorPosition);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_C_hl;
    uint8_t contact = wram->wPhoneList[wram->wPokegearPhoneScrollPosition + wram->wPokegearPhoneCursorPosition];
    // FARCALL(aCheckCanDeletePhoneNumber);
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto cant_delete;
    uint8_t which;
    if(CheckCanDeletePhoneNumber(contact)) {
        // LD_HL(mPokegearPhoneContactSubmenu_CallDeleteCancelJumptable);
        // LD_DE(mPokegearPhoneContactSubmenu_CallDeleteCancelStrings);
        which = 0;
        // goto got_menu_data;
    }
    else {
    // cant_delete:
        // LD_HL(mPokegearPhoneContactSubmenu_CallCancelJumptable);
        // LD_DE(mPokegearPhoneContactSubmenu_CallCancelStrings);
        which = 1;
    }

// got_menu_data:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // PUSH_HL;
    // PUSH_DE;
    // LD_A_de;
    // LD_L_A;
    // INC_DE;
    // LD_A_de;
    // LD_H_A;
    // INC_DE;
    // PUSH_HL;
    tile_t* hl = Submenus[which].coord;
    // bccoord(-1, -2, 0);
    // ADD_HL_BC;
    // LD_A_de;
    // INC_DE;
    // SLA_A;
    // LD_B_A;
    // LD_C(8);
    // PUSH_DE;
    // CALL(aTextbox);
    Textbox(hl + coord(-1, -2, 0), Submenus[which].count * 2, 8);
    // POP_DE;
    // POP_HL;
    // INC_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Submenus[which].strings), hl + 1);
    // POP_DE;
    // XOR_A_A;
    // LD_addr_A(wPokegearPhoneSubmenuCursor);
    wram->wPokegearPhoneSubmenuCursor = 0;
    // CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
    PokegearPhoneContactSubmenu_UpdateCursor(Submenus + which);
    // CALL(aWaitBGMap);
    WaitBGMap();

    while(1) {
    // loop:
        // PUSH_DE;
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // POP_DE;
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        uint8_t pressed = hram->hJoyPressed;
        // AND_A(D_UP);
        // IF_NZ goto d_up;
        if(pressed & D_UP) {
        // d_up:
            // LD_HL(wPokegearPhoneSubmenuCursor);
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto loop;
            if(wram->wPokegearPhoneSubmenuCursor == 0)
                continue;
            // DEC_hl;
            wram->wPokegearPhoneSubmenuCursor--;
            // CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
            PokegearPhoneContactSubmenu_UpdateCursor(Submenus + which);
            // goto loop;
            continue;
        }
        // LD_A_hl;
        // AND_A(D_DOWN);
        // IF_NZ goto d_down;
        else if(pressed & D_DOWN) {
        // d_down:
            // LD_HL(2);
            // ADD_HL_DE;
            uint8_t count = Submenus[which].count;
            // LD_A_addr(wPokegearPhoneSubmenuCursor);
            // INC_A;
            // CP_A_hl;
            // IF_NC goto loop;
            if(wram->wPokegearPhoneSubmenuCursor + 1 >= count)
                continue;
            // LD_addr_A(wPokegearPhoneSubmenuCursor);
            wram->wPokegearPhoneSubmenuCursor++;
            // CALL(aPokegearPhoneContactSubmenu_UpdateCursor);
            PokegearPhoneContactSubmenu_UpdateCursor(Submenus + which);
            // goto loop;
            continue;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto a_b;
        else if(pressed & (A_BUTTON | B_BUTTON)) {
        // a_b:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // CALL(aPokegearPhone_UpdateDisplayList);
            PokegearPhone_UpdateDisplayList();
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // POP_HL;
            // LDH_A_addr(hJoyPressed);
            // AND_A(B_BUTTON);
            // IF_NZ goto Cancel;
            if(hram->hJoyPressed & B_BUTTON)
                goto Cancel;
            // LD_A_addr(wPokegearPhoneSubmenuCursor);
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // ADD_HL_DE;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // JP_hl;
            switch(wram->wPokegearPhoneSubmenuCursor) {
            case 0:
            // Call:
                // AND_A_A;
                // RET;
                return false;
            case 1:
                if(which == 0) {
                // Delete:
                    // LD_HL(mPokegearAskDeleteText);
                    // CALL(aMenuTextbox);
                    MenuTextbox(PokegearAskDeleteText);
                    // CALL(aYesNoBox);
                    bool cancel = !YesNoBox();
                    // CALL(aExitMenu);
                    ExitMenu();
                    // IF_C goto CancelDelete;
                    if(!cancel) {
                        // CALL(aPokegearPhone_DeletePhoneNumber);
                        PokegearPhone_DeletePhoneNumber();
                        // XOR_A_A;
                        // LDH_addr_A(hBGMapMode);
                        hram->hBGMapMode = BGMAPMODE_NONE;
                        // CALL(aPokegearPhone_UpdateDisplayList);
                        PokegearPhone_UpdateDisplayList();
                        // LD_HL(mPokegearAskWhoCallText);
                        // CALL(aPrintText);
                        PrintText(PokegearAskWhoCallText);
                        // CALL(aWaitBGMap);
                        WaitBGMap();
                    }

                // CancelDelete:
                    // SCF;
                    // RET;
                    return true;
                }
                fallthrough;
            case 2:
            Cancel:
                // LD_HL(mPokegearAskWhoCallText);
                // CALL(aPrintText);
                PrintText(PokegearAskWhoCallText);
                // SCF;
                // RET;
                return true;
            }
        }
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }
}

void GetAMPMHours(void){
//  //  unreferenced
    LDH_A_addr(hHours);
    CP_A(NOON_HOUR);
    IF_C goto am;
    SUB_A(NOON_HOUR);
    LD_addr_A(wTempByteValue);
    SCF;
    RET;


am:
    LD_addr_A(wTempByteValue);
    AND_A_A;
    RET;

}

static void Pokegear_SwitchPage(uint8_t c, uint8_t b){
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // LD_A_C;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = c;
    // LD_A_B;
    // LD_addr_A(wPokegearCard);
    wram->wPokegearCard = b;
    // CALL(aDeleteSpriteAnimStruct2ToEnd);
    DeleteSpriteAnimStruct2ToEnd();
    // RET;
}

void ExitPokegearRadio_HandleMusic(void){
    // LD_A_addr(wPokegearRadioMusicPlaying);
    // CP_A(RESTART_MAP_MUSIC);
    // IF_Z goto restart_map_music;
    if(wram->wPokegearRadioMusicPlaying == RESTART_MAP_MUSIC) {
    // restart_map_music:
        // CALL(aRestartMapMusic);
        RestartMapMusic();
        // XOR_A_A;
        // LD_addr_A(wPokegearRadioMusicPlaying);
        wram->wPokegearRadioMusicPlaying = 0;
        // RET;
        return;
    }
    // CP_A(ENTER_MAP_MUSIC);
    // CALL_Z (aPlayMapMusicBike);
    else if(wram->wPokegearRadioMusicPlaying == ENTER_MAP_MUSIC) {
        return PlayMapMusicBike();
    }
    // XOR_A_A;
    // LD_addr_A(wPokegearRadioMusicPlaying);
    // RET;
    wram->wPokegearRadioMusicPlaying = 0;
}

void DeleteSpriteAnimStruct2ToEnd(void){
    // LD_HL(wSpriteAnim2);
    struct SpriteAnim* hl = wram->wSpriteAnim + 1;
    // LD_BC(wSpriteAnimationStructsEnd - wSpriteAnim2);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(hl, wSpriteAnimationStructsEnd - wSpriteAnim2, 0);
    // LD_A(2);
    // LD_addr_A(wSpriteAnimCount);
    wram->wSpriteAnimCount = 2;
    // RET;
}

// Format: repeat count, tile ID
// Terminated with -1
static void Pokegear_LoadTilemapRLE(const char* path){
    asset_s a = LoadAsset(path);
    const uint8_t* de = a.ptr;
    uint8_t* hl = coord(0, 0, wram->wTilemap);

    while(1)
    {
        uint8_t id = *(de++);
        if(id == 0xff) 
            break;
        
        uint8_t repeat = *(de++);
        do {
            *(hl++) = id;
        } while(--repeat != 0);
    }

    FreeAsset(a);
}

const txt_cmd_s PokegearAskWhoCallText[] = {
    text_far(v_PokegearAskWhoCallText)
    text_end
};

const txt_cmd_s PokegearPressButtonText[] = {
    text_far(v_PokegearPressButtonText)
    text_end
};

const txt_cmd_s PokegearAskDeleteText[] = {
    text_far(v_PokegearAskDeleteText)
    text_end
};

static void v_UpdateRadioStation(void){
    // JR(mUpdateRadioStation);
    return UpdateRadioStation();
}

static void AnimateTuningKnob_TuningKnob(void) {
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_HL(wRadioTuningKnob);
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wRadioTuningKnob == 0)
            return;
        // DEC_hl;
        // DEC_hl;
        wram->wRadioTuningKnob -= 2;
        // goto update;
    }
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    else if(hram->hJoyLast & D_UP) {
    // up:
        // LD_HL(wRadioTuningKnob);
        // LD_A_hl;
        // CP_A(80);
        // RET_NC ;
        if(wram->wRadioTuningKnob >= 80)
            return;
        // INC_hl;
        // INC_hl;
        wram->wRadioTuningKnob += 2;
    }
    // RET;
    else {
        return;
    }

// update:
    return UpdateRadioStation();
}

//  called from engine/gfx/sprite_anims.asm
void AnimateTuningKnob(struct SpriteAnim* bc){
    // PUSH_BC;
    // CALL(aAnimateTuningKnob_TuningKnob);
    AnimateTuningKnob_TuningKnob();
    // POP_BC;
    // LD_A_addr(wRadioTuningKnob);
    // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->xOffset = wram->wRadioTuningKnob;
    // RET;
}

void LoadPokegearRadioChannelPointer(void){
//  //  unreferenced
    LD_addr_A(wPokegearRadioChannelBank);
    LD_A_hli;
    LD_addr_A(wPokegearRadioChannelAddr);
    LD_A_hli;
    LD_addr_A(wPokegearRadioChannelAddr + 1);
    RET;

}

static const char* RadioChannels_NoSignal(void) {
    // CALL(aNoRadioStation);
    NoRadioStation();
    // RET;
    return NULL;
}

static bool RadioChannels_InJohto(void) {
//  if in Johto or on the S.S. Aqua, set carry
//  otherwise clear carry
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CP_A(LANDMARK_FAST_SHIP);
    // IF_Z goto johto;
    // CP_A(KANTO_LANDMARK);
    // IF_C goto johto;
    if(wram->wPokegearMapPlayerIconLandmark != LANDMARK_FAST_SHIP && wram->wPokegearMapPlayerIconLandmark >= KANTO_LANDMARK) {
    //  kanto
        // AND_A_A;
        // RET;
        return false;
    }

// johto:
    // SCF;
    // RET;
    return true;
}

//  Pokédex Show in the morning
//  Oak's Pokémon Talk in the afternoon and evening
static const char* RadioChannels_PKMNTalkAndPokedexShow(void){
    // CALL(aRadioChannels_InJohto);
    // IF_NC goto NoSignal;
    if(!RadioChannels_InJohto()) 
        return RadioChannels_NoSignal();
    // LD_A_addr(wTimeOfDay);
    // AND_A_A;
    // JP_Z (mLoadStation_PokedexShow);
    if(wram->wTimeOfDay == MORN_F)
        return LoadStation_PokedexShow();
    // JP(mLoadStation_OaksPokemonTalk);
    return LoadStation_OaksPokemonTalk();
}

static const char* RadioChannels_PokemonMusic(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_NC goto NoSignal;
    if(!RadioChannels_InJohto()) 
        return RadioChannels_NoSignal();
    // JP(mLoadStation_PokemonMusic);
    return LoadStation_PokemonMusic();
}

static const char* RadioChannels_LuckyChannel(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_NC goto NoSignal;
    if(!RadioChannels_InJohto()) 
        return RadioChannels_NoSignal();
    // JP(mLoadStation_LuckyChannel);
    return LoadStation_LuckyChannel();
}

static const char* RadioChannels_BuenasPassword(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_NC goto NoSignal;
    if(!RadioChannels_InJohto()) 
        return RadioChannels_NoSignal();
    // JP(mLoadStation_BuenasPassword);
    return LoadStation_BuenasPassword();
}

static const char* RadioChannels_RuinsOfAlphRadio(void) {
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CP_A(LANDMARK_RUINS_OF_ALPH);
    // IF_NZ goto NoSignal;
    if(wram->wPokegearMapPlayerIconLandmark != LANDMARK_RUINS_OF_ALPH)
        return RadioChannels_NoSignal();
    // JP(mLoadStation_UnownRadio);
    return LoadStation_UnownRadio();
}

static const char* RadioChannels_PlacesAndPeople(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_C goto NoSignal;
    if(RadioChannels_InJohto())
        return RadioChannels_NoSignal();
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_EXPN_CARD_F);
    // IF_Z goto NoSignal;
    if(!bit_test(wram->wPokegearFlags, POKEGEAR_EXPN_CARD_F))
        return RadioChannels_NoSignal();
    // JP(mLoadStation_PlacesAndPeople);
    return LoadStation_PlacesAndPeople();
}

static const char* RadioChannels_LetsAllSing(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_C goto NoSignal;
    if(RadioChannels_InJohto())
        return RadioChannels_NoSignal();
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_EXPN_CARD_F);
    // IF_Z goto NoSignal;
    if(!bit_test(wram->wPokegearFlags, POKEGEAR_EXPN_CARD_F))
        return RadioChannels_NoSignal();
    // JP(mLoadStation_LetsAllSing);
    return LoadStation_LetsAllSing();
}

static const char* RadioChannels_PokeFluteRadio(void) {
    // CALL(aRadioChannels_InJohto);
    // IF_C goto NoSignal;
    if(RadioChannels_InJohto())
        return RadioChannels_NoSignal();
    // LD_A_addr(wPokegearFlags);
    // BIT_A(POKEGEAR_EXPN_CARD_F);
    // IF_Z goto NoSignal;
    if(!bit_test(wram->wPokegearFlags, POKEGEAR_EXPN_CARD_F))
        return RadioChannels_NoSignal();
    // JP(mLoadStation_PokeFluteRadio);
    return LoadStation_PokeFluteRadio();
}

//  This station airs in the Lake of Rage area when Team Rocket is still in Mahogany.
static const char* RadioChannels_EvolutionRadio(void) {
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_ROCKET_SIGNAL_F);
    // IF_Z goto NoSignal;
    if(!bit_test(wram->wStatusFlags, STATUSFLAGS_ROCKET_SIGNAL_F))
        return RadioChannels_NoSignal();
    // LD_A_addr(wPokegearMapPlayerIconLandmark);
    // CP_A(LANDMARK_MAHOGANY_TOWN);
    // IF_Z goto ok;
    // CP_A(LANDMARK_ROUTE_43);
    // IF_Z goto ok;
    // CP_A(LANDMARK_LAKE_OF_RAGE);
    // IF_NZ goto NoSignal;
    if(wram->wPokegearMapPlayerIconLandmark == LANDMARK_MAHOGANY_TOWN
    || wram->wPokegearMapPlayerIconLandmark == LANDMARK_ROUTE_43
    || wram->wPokegearMapPlayerIconLandmark == LANDMARK_LAKE_OF_RAGE) {
        return LoadStation_EvolutionRadio();
    }

// ok:
    // JP(mLoadStation_EvolutionRadio);
    return RadioChannels_NoSignal();
}

#define radio_freq(_x) (uint8_t)((_x * 4) - 2)

struct RadioChannel {
    uint8_t freq;
    const char* (*fn)(void);
};

const struct RadioChannel RadioChannels[] = {
    {radio_freq(04.5), RadioChannels_PKMNTalkAndPokedexShow},
    {radio_freq(07.5), RadioChannels_PokemonMusic},
    {radio_freq(08.5), RadioChannels_LuckyChannel},
    {radio_freq(10.5), RadioChannels_BuenasPassword},
    {radio_freq(13.5), RadioChannels_RuinsOfAlphRadio},
    {radio_freq(16.5), RadioChannels_PlacesAndPeople},
    {radio_freq(18.5), RadioChannels_LetsAllSing},
    {radio_freq(20.0), RadioChannels_PokeFluteRadio},
    {radio_freq(20.5), RadioChannels_EvolutionRadio},
};

#if 0
void RadioChannels(void){
//  entries correspond to constants/radio_constants.asm
//  frequency value given here = 4 × ingame_frequency − 2
    //dbw ['16', '.PKMNTalkAndPokedexShow']  // 04.5
    //dbw ['28', '.PokemonMusic']  // 07.5
    //dbw ['32', '.LuckyChannel']  // 08.5
    //dbw ['40', '.BuenasPassword']  // 10.5
    //dbw ['52', '.RuinsOfAlphRadio']  // 13.5
    //dbw ['64', '.PlacesAndPeople']  // 16.5
    //dbw ['72', '.LetsAllSing']  // 18.5
    //dbw ['78', '.PokeFluteRadio']  // 20.0
    //dbw ['80', '.EvolutionRadio']  // 20.5
    //db ['-1'];


PKMNTalkAndPokedexShow:
//  Pokédex Show in the morning
//  Oak's Pokémon Talk in the afternoon and evening
    CALL(aRadioChannels_InJohto);
    IF_NC goto NoSignal;
    LD_A_addr(wTimeOfDay);
    AND_A_A;
    JP_Z (mLoadStation_PokedexShow);
    JP(mLoadStation_OaksPokemonTalk);


PokemonMusic:
    CALL(aRadioChannels_InJohto);
    IF_NC goto NoSignal;
    JP(mLoadStation_PokemonMusic);


LuckyChannel:
    CALL(aRadioChannels_InJohto);
    IF_NC goto NoSignal;
    JP(mLoadStation_LuckyChannel);


BuenasPassword:
    CALL(aRadioChannels_InJohto);
    IF_NC goto NoSignal;
    JP(mLoadStation_BuenasPassword);


RuinsOfAlphRadio:
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CP_A(LANDMARK_RUINS_OF_ALPH);
    IF_NZ goto NoSignal;
    JP(mLoadStation_UnownRadio);


PlacesAndPeople:
    CALL(aRadioChannels_InJohto);
    IF_C goto NoSignal;
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_EXPN_CARD_F);
    IF_Z goto NoSignal;
    JP(mLoadStation_PlacesAndPeople);


LetsAllSing:
    CALL(aRadioChannels_InJohto);
    IF_C goto NoSignal;
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_EXPN_CARD_F);
    IF_Z goto NoSignal;
    JP(mLoadStation_LetsAllSing);


PokeFluteRadio:
    CALL(aRadioChannels_InJohto);
    IF_C goto NoSignal;
    LD_A_addr(wPokegearFlags);
    BIT_A(POKEGEAR_EXPN_CARD_F);
    IF_Z goto NoSignal;
    JP(mLoadStation_PokeFluteRadio);


EvolutionRadio:
//  This station airs in the Lake of Rage area when Team Rocket is still in Mahogany.
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_ROCKET_SIGNAL_F);
    IF_Z goto NoSignal;
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CP_A(LANDMARK_MAHOGANY_TOWN);
    IF_Z goto ok;
    CP_A(LANDMARK_ROUTE_43);
    IF_Z goto ok;
    CP_A(LANDMARK_LAKE_OF_RAGE);
    IF_NZ goto NoSignal;

ok:
    JP(mLoadStation_EvolutionRadio);


NoSignal:
    CALL(aNoRadioStation);
    RET;


InJohto:
//  if in Johto or on the S.S. Aqua, set carry
//  otherwise clear carry
    LD_A_addr(wPokegearMapPlayerIconLandmark);
    CP_A(LANDMARK_FAST_SHIP);
    IF_Z goto johto;
    CP_A(KANTO_LANDMARK);
    IF_C goto johto;
//  kanto
    AND_A_A;
    RET;


johto:
    SCF;
    RET;

}
#endif

static void UpdateRadioStation(void){
    // LD_HL(wRadioTuningKnob);
    // LD_D_hl;
    //REG_D = gb_read(wRadioTuningKnob);
    //REG_HL = mRadioChannels;
    uint8_t d = wram->wRadioTuningKnob;
    // LD_HL(mRadioChannels);

// loop:
    for(uint32_t i = 0; i < lengthof(RadioChannels); ++i) {
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto nostation;
        // CP_A_D;
        // IF_Z goto foundstation;
        if(RadioChannels[i].freq == d) {
        // foundstation:
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // LD_DE(mUpdateRadioStation_returnafterstation);
            // PUSH_DE;
            // JP_hl;
            const char* de = RadioChannels[i].fn();

        // returnafterstation:
            // LD_A_addr(wPokegearRadioChannelBank);
            // AND_A_A;
            // RET_Z ;
            if(!de)
                return;
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // hlcoord(2, 9, wTilemap);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(de), coord(2, 9, wram->wTilemap));
            // LD_A(0x1);
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
            // RET;
            return;
        }
        // INC_HL;
        // INC_HL;
        // goto loop;
    }


// nostation:
    // CALL(aNoRadioStation);
    NoRadioStation();
    // RET;
}

static const char* LoadStation_OaksPokemonTalk(void){
    // XOR_A_A;  // OAKS_POKEMON_TALK
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = OAKS_POKEMON_TALK;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mOaksPKMNTalkName);
    // RET;
    return OaksPKMNTalkName;
}

static const char* LoadStation_PokedexShow(void){
    // LD_A(POKEDEX_SHOW);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = POKEDEX_SHOW;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mPokedexShowName);
    // RET;
    return PokedexShowName;
}

static const char* LoadStation_PokemonMusic(void){
    // LD_A(POKEMON_MUSIC);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = POKEMON_MUSIC;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mPokemonMusicName);
    // RET;
    return PokemonMusicName;
}

static const char* LoadStation_LuckyChannel(void){
    // LD_A(LUCKY_CHANNEL);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = LUCKY_CHANNEL;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mLuckyChannelName);
    // RET;
    return LuckyChannelName;
}

static const char* LoadStation_BuenasPassword(void){
    static const char BuenasPasswordName[] = "BUENA'S PASSWORD@";
    static const char NotBuenasPasswordName[] = "@";
    // LD_A(BUENAS_PASSWORD);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = BUENAS_PASSWORD;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mNotBuenasPasswordName);
    // LD_A_addr(wStatusFlags2);
    // BIT_A(STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F);
    // RET_Z ;
    // LD_DE(mBuenasPasswordName);
    // RET;
    return (bit_test(wram->wStatusFlags2, STATUSFLAGS2_ROCKETS_IN_RADIO_TOWER_F))? BuenasPasswordName: NotBuenasPasswordName;
}

static const char* LoadStation_UnownRadio(void){
    // LD_A(UNOWN_RADIO);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = UNOWN_RADIO;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mUnownStationName);
    // RET;
    return UnownStationName;
}

static const char* LoadStation_PlacesAndPeople(void){
    // LD_A(PLACES_AND_PEOPLE);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = PLACES_AND_PEOPLE;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mPlacesAndPeopleName);
    // RET;
    return PlacesAndPeopleName;
}

static const char* LoadStation_LetsAllSing(void){
    // LD_A(LETS_ALL_SING);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = LETS_ALL_SING;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mLetsAllSingName);
    // RET;
    return LetsAllSingName;
}

static const char* LoadStation_RocketRadio(void){
    // LD_A(ROCKET_RADIO);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = ROCKET_RADIO;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mLetsAllSingName);
    // RET;
    return LetsAllSingName;
}

static const char* LoadStation_PokeFluteRadio(void){
    // LD_A(POKE_FLUTE_RADIO);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = POKE_FLUTE_RADIO;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mPokeFluteStationName);
    // RET;
    return PokeFluteStationName;
}

static const char* LoadStation_EvolutionRadio(void){
    // LD_A(EVOLUTION_RADIO);
    // LD_addr_A(wCurRadioLine);
    wram->wCurRadioLine = EVOLUTION_RADIO;
    // XOR_A_A;
    // LD_addr_A(wNumRadioLinesPrinted);
    wram->wNumRadioLinesPrinted = 0;
    // LD_A(BANK(aPlayRadioShow));
    // LD_HL(mPlayRadioShow);
    // CALL(aRadio_BackUpFarCallParams);
    Radio_BackUpFarCallParams(PlayRadioShow);
    // LD_DE(mUnownStationName);
    // RET;
    return UnownStationName;
}

void DummyLoadStation(void){
//  //  unreferenced
    // RET;
}

void RadioMusicRestartDE(uint16_t de){
    wram->wPokegearRadioMusicPlaying = (uint8_t)(de & 0xFF);
    PlayMusic(MUSIC_NONE);
    wram->wMapMusic = (uint8_t)(de & 0xFF);
    PlayMusic(de);
}

void RadioMusicRestartPokemonChannel(void){
    wram->wPokegearRadioMusicPlaying = RESTART_MAP_MUSIC;
    PlayMusic(MUSIC_NONE);
    PlayMusic(MUSIC_POKEMON_CHANNEL);
}

static void Radio_BackUpFarCallParams(void (*hl)(void)){
    // LD_addr_A(wPokegearRadioChannelBank);
    // LD_A_L;
    // LD_addr_A(wPokegearRadioChannelAddr);
    // LD_A_H;
    // LD_addr_A(wPokegearRadioChannelAddr + 1);
    // RET;
    gPokegearRadioChannelAddr = hl;
}

void NoRadioStation(void){
    NoRadioMusic();
    NoRadioName();
//  no radio channel
    wram->wPokegearRadioChannelBank = 0;
    // gb_write16(wPokegearRadioChannelAddr, 0);
    gPokegearRadioChannelAddr = NULL;
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
}

void NoRadioMusic(void){
    PlayMusic(MUSIC_NONE);
    wram->wPokegearRadioMusicPlaying = ENTER_MAP_MUSIC;
}

void NoRadioName(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;

    // hlcoord(1, 8, wTilemap);
    // LD_BC((3 << 8) | 18);
    // CALL(aClearBox);
    ClearBox(coord(1, 8, wram->wTilemap), 18, 3);

    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 4, 18);
    // RET;
}

static void v_TownMap_loop(uint8_t d, uint8_t e){
    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // RET_NZ ;
        if(hram->hJoyPressed & B_BUTTON)
            return;

        // LD_HL(hJoyLast);
        // LD_A_hl;
        // AND_A(D_UP);
        // IF_NZ goto pressed_up;
        if(hram->hJoyLast & D_UP) {
        // pressed_up:
            // LD_HL(wTownMapCursorLandmark);
            // LD_A_hl;
            // CP_A_D;
            // IF_C goto okay;
            // LD_A_E;
            // DEC_A;
            // LD_hl_A;


        // okay:
            // INC_hl;
            wram->wTownMapCursorLandmark = (wram->wTownMapCursorLandmark < d)
                ? wram->wTownMapCursorLandmark + 1
                : e;
            // goto next;
            break;
        }

        // LD_A_hl;
        // AND_A(D_DOWN);
        // IF_NZ goto pressed_down;
        else if(hram->hJoyLast & D_DOWN) {
        // pressed_down:
            // LD_HL(wTownMapCursorLandmark);
            // LD_A_hl;
            // CP_A_E;
            // IF_NZ goto okay2;
            // LD_A_D;
            // INC_A;
            // LD_hl_A;


        // okay2:
            wram->wTownMapCursorLandmark = (wram->wTownMapCursorLandmark != e)
                ? wram->wTownMapCursorLandmark - 1
                : d;
            // DEC_hl;
            break;
        }
        else {
        loop2:
            // PUSH_DE;
            // FARCALL(aPlaySpriteAnimations);
            PlaySpriteAnimations();
            // POP_DE;
            // CALL(aDelayFrame);
            DelayFrame();
            // goto loop;
        }
    } while(1);


// next:
    // PUSH_DE;
    // LD_A_addr(wTownMapCursorLandmark);
    // CALL(aPokegearMap_UpdateLandmarkName);
    PokegearMap_UpdateLandmarkName(wram->wTownMapCursorLandmark);
    // LD_A_addr(wTownMapCursorObjectPointer);
    // LD_C_A;
    // LD_A_addr(wTownMapCursorObjectPointer + 1);
    // LD_B_A;
    struct SpriteAnim* bc = gTownMapCursorObjectPointer;
    // LD_A_addr(wTownMapCursorLandmark);
    // CALL(aPokegearMap_UpdateCursorPosition);
    PokegearMap_UpdateCursorPosition(bc, wram->wTownMapCursorLandmark);
    // POP_DE;
    goto loop2;
}

static void v_TownMap_InitTilemap(void) {
// InitTilemap:
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // CP_A(KANTO_LANDMARK);
    // IF_NC goto kanto2;
    // LD_E(JOHTO_REGION);
    // goto okay_tilemap;


// kanto2:
    // LD_E(KANTO_REGION);
    uint8_t region = (wram->wTownMapPlayerIconLandmark >= KANTO_LANDMARK)
        ? KANTO_REGION
        : JOHTO_REGION;

// okay_tilemap:
    // FARCALL(aPokegearMap);
    PokegearMap(region);
    // LD_A(0x07);
    // LD_BC(6);
    // hlcoord(1, 0, wTilemap);
    // CALL(aByteFill);
    ByteFill(coord(1, 0, wram->wTilemap), 6, 0x07);
    // hlcoord(0, 0, wTilemap);
    // LD_hl(0x06);
    *coord(0, 0, wram->wTilemap) = 0x06;
    // hlcoord(7, 0, wTilemap);
    // LD_hl(0x17);
    *coord(7, 0, wram->wTilemap) = 0x17;
    // hlcoord(7, 1, wTilemap);
    // LD_hl(0x16);
    *coord(7, 1, wram->wTilemap) = 0x16;
    // hlcoord(7, 2, wTilemap);
    // LD_hl(0x26);
    *coord(7, 2, wram->wTilemap) = 0x26;
    // LD_A(0x07);
    // LD_BC(NAME_LENGTH);
    // hlcoord(8, 2, wTilemap);
    // CALL(aByteFill);
    ByteFill(coord(8, 2, wram->wTilemap), NAME_LENGTH, 0x07);
    // hlcoord(19, 2, wTilemap);
    // LD_hl(0x17);
    *coord(19, 2, wram->wTilemap) = 0x17;
    // LD_A_addr(wTownMapCursorLandmark);
    // CALL(aPokegearMap_UpdateLandmarkName);
    PokegearMap_UpdateLandmarkName(wram->wTownMapCursorLandmark);
    // FARCALL(aTownMapPals);
    TownMapPals();
    // RET;
}

void v_TownMap(void){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);

    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;

    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;

    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aPokegear_LoadGFX);
    Pokegear_LoadGFX();
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // LD_A(8);
    // CALL(aSkipMusic);
    SkipMusic(4);
    // LD_A(LCDC_DEFAULT);
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, LCDC_DEFAULT);
    // CALL(aTownMap_GetCurrentLandmark);
    uint8_t landmark = TownMap_GetCurrentLandmark();
    // LD_addr_A(wTownMapPlayerIconLandmark);
    wram->wTownMapPlayerIconLandmark = landmark;
    // LD_addr_A(wTownMapCursorLandmark);
    wram->wTownMapCursorLandmark = landmark;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(av_TownMap_InitTilemap);
    v_TownMap_InitTilemap();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // CALL(aPokegearMap_InitPlayerIcon);
    PokegearMap_InitPlayerIcon(landmark);
    // LD_A_addr(wTownMapCursorLandmark);
    // CALL(aPokegearMap_InitCursor);
    struct SpriteAnim* bc = PokegearMap_InitCursor(wram->wTownMapCursorLandmark);
    // LD_A_C;
    // LD_addr_A(wTownMapCursorObjectPointer);
    // LD_A_B;
    // LD_addr_A(wTownMapCursorObjectPointer + 1);
    gTownMapCursorObjectPointer = bc;
    // LD_B(SCGB_POKEGEAR_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_POKEGEAR_PALS);
    // CALL(aSetPalettes);
    SetPalettes();
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto dmg;
    if(hram->hCGB == 0) {
    // dmg:
        // LD_A_addr(wTownMapPlayerIconLandmark);
        // CP_A(KANTO_LANDMARK);
        // IF_NC goto kanto;
        if(wram->wTownMapPlayerIconLandmark >= KANTO_LANDMARK)
            goto kanto;
        // LD_D(KANTO_LANDMARK - 1);
        // LD_E(1);
        // CALL(av_TownMap_loop);
        v_TownMap_loop(KANTO_LANDMARK - 1, 1);
        // goto resume;
    }
    else {
        // LD_A(0b11100100);
        // CALL(aDmgToCgbObjPal0);
        DmgToCgbObjPal0(0b11100100);
        // CALL(aDelayFrame);
        DelayFrame();

        kanto: {
            // CALL(aTownMap_GetKantoLandmarkLimits);
            u8_pair_s de = TownMap_GetKantoLandmarkLimits();
            // CALL(av_TownMap_loop);
            v_TownMap_loop(de.a, de.b);
        }
    }

// resume:
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // RET;
}

static const char* (*const PlayRadioStationPointers[])(void) = {
//  entries correspond to MAPRADIO_* constants
    //table_width ['2', 'PlayRadioStationPointers']
    [MAPRADIO_POKEMON_CHANNEL]  = LoadStation_PokemonChannel,
    [MAPRADIO_OAKS_POKEMON_TALK]= LoadStation_OaksPokemonTalk,
    [MAPRADIO_POKEDEX_SHOW]     = LoadStation_PokedexShow,
    [MAPRADIO_POKEMON_MUSIC]    = LoadStation_PokemonMusic,
    [MAPRADIO_LUCKY_CHANNEL]    = LoadStation_LuckyChannel,
    [MAPRADIO_UNOWN]            = LoadStation_UnownRadio,
    [MAPRADIO_PLACES_PEOPLE]    = LoadStation_PlacesAndPeople,
    [MAPRADIO_LETS_ALL_SING]    = LoadStation_LetsAllSing,
    [MAPRADIO_ROCKET]           = LoadStation_RocketRadio,
    //assert_table_length ['NUM_MAP_RADIO_STATIONS']
};

static_assert(lengthof(PlayRadioStationPointers) == NUM_MAP_RADIO_STATIONS, "");

static void PlayRadio_PlayStation(uint8_t e) {
    // LD_A(ENTER_MAP_MUSIC);
    // LD_addr_A(wPokegearRadioMusicPlaying);
    wram->wPokegearRadioMusicPlaying = ENTER_MAP_MUSIC;
    // LD_HL(mPlayRadioStationPointers);
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mPlayRadio_jump_return);
    // PUSH_DE;
    // JP_hl;
    const char* de = PlayRadioStationPointers[e]();


// jump_return:
    // PUSH_DE;
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 4, 18);
    // hlcoord(1, 14, wTilemap);
    // LD_hl(0x72);
    *coord(1, 14, wram->wTilemap) = 0x72;
    // POP_DE;
    // hlcoord(2, 14, wTilemap);
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = U82C(de), .hl = coord(2, 14, wram->wTilemap)};
    PlaceString(&st, st.hl);
    // LD_H_B;
    // LD_L_C;
    // LD_hl(0x73);
    *st.bc = 0x73;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // RET;
}

void PlayRadio(uint8_t e){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aPlayRadio_PlayStation);
    PlayRadio_PlayStation(e);
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames(100);

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LDH_A_addr(hJoyPressed);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto stop;
        if(hram->hJoyPressed & (A_BUTTON | B_BUTTON))
            break;
        // LD_A_addr(wPokegearRadioChannelAddr);
        // LD_L_A;
        // LD_A_addr(wPokegearRadioChannelAddr + 1);
        // LD_H_A;
        // LD_A_addr(wPokegearRadioChannelBank);
        // AND_A_A;
        // IF_Z goto zero;
        // RST(aFarCall);
        if(gPokegearRadioChannelAddr != NULL)
            gPokegearRadioChannelAddr();

    // zero:
        // CALL(aDelayFrame);
        // goto loop;
        DelayFrame();
    }


// stop:
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // CALL(aExitPokegearRadio_HandleMusic);
    ExitPokegearRadio_HandleMusic();
    // RET;
}

static const char* LoadStation_PokemonChannel(void){
    // CALL(aIsInJohto);
    // AND_A_A;
    // IF_NZ goto kanto;
    if(IsInJohto() == JOHTO_REGION) {
        // CALL(aUpdateTime);
        UpdateTime();
        // LD_A_addr(wTimeOfDay);
        // AND_A_A;
        // JP_Z (mLoadStation_PokedexShow);
        if(wram->wTimeOfDay == MORN_F)
            return LoadStation_PokedexShow();
        // JP(mLoadStation_OaksPokemonTalk);
        return LoadStation_OaksPokemonTalk();
    }
    else {
    // kanto:
        // JP(mLoadStation_PlacesAndPeople);
        return LoadStation_PlacesAndPeople();
    }
}

void PokegearMap(uint8_t e){
    // LD_A_E;
    // AND_A_A;
    // IF_NZ goto kanto;
    if(e != JOHTO_REGION) {
    // kanto:
        // CALL(aLoadTownMapGFX);
        LoadTownMapGFX();
        // CALL(aFillKantoMap);
        FillKantoMap();
        // RET;
        return;
    }
    else {
        // CALL(aLoadTownMapGFX);
        LoadTownMapGFX();
        // CALL(aFillJohtoMap);
        FillJohtoMap();
        // RET;
        return;
    }
}

static void v_FlyMap_HandleDPad(void){
    // LD_A_addr(wStartFlypoint);
    // LD_E_A;
    uint8_t e = wram->wStartFlypoint;
    // LD_A_addr(wEndFlypoint);
    // LD_D_A;
    uint8_t d = wram->wEndFlypoint;
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto ScrollNext;
    if(hram->hJoyLast & D_UP) {
        do {
        // ScrollNext:
            // LD_HL(wTownMapPlayerIconLandmark);
            // LD_A_hl;
            // CP_A_D;
            // IF_NZ goto NotAtEndYet;
            if(wram->wTownMapPlayerIconLandmark == d) {
                // LD_A_E;
                // DEC_A;
                // LD_hl_A;
                wram->wTownMapPlayerIconLandmark = e;
            }
            else {
                wram->wTownMapPlayerIconLandmark++;
            }

        // NotAtEndYet:
            // INC_hl;
            // CALL(aCheckIfVisitedFlypoint);
            // IF_Z goto ScrollNext;
        } while(!CheckIfVisitedFlypoint(wram->wTownMapPlayerIconLandmark));
        // goto Finally;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto ScrollPrev;
    else if(hram->hJoyLast & D_DOWN) {
        do {
        // ScrollPrev:
            // LD_HL(wTownMapPlayerIconLandmark);
            // LD_A_hl;
            // CP_A_E;
            // IF_NZ goto NotAtStartYet;
            if(wram->wTownMapPlayerIconLandmark == e) {
                // LD_A_D;
                // INC_A;
                // LD_hl_A;
                wram->wTownMapPlayerIconLandmark = d;
            }
            else {
            // NotAtStartYet:
                // DEC_hl;
                wram->wTownMapPlayerIconLandmark--;
            }
            // CALL(aCheckIfVisitedFlypoint);
            // IF_Z goto ScrollPrev;
        } while(!CheckIfVisitedFlypoint(wram->wTownMapPlayerIconLandmark));
    }
    else {
        // RET;
        return;
    }

// Finally:
    // CALL(aTownMapBubble);
    TownMapBubble();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // RET;
}

uint8_t v_FlyMap(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aClearSprites);
    ClearSprites();
    // LD_HL(hInMenu);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_hl(0x1);
    hram->hInMenu = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aLoadTownMapGFX);
    LoadTownMapGFX();
    // LD_DE(mFlyMapLabelBorderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x30);
    // LD_BC((BANK(aFlyMapLabelBorderGFX) << 8) | 6);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x30, FlyMapLabelBorderGFX, 0, 6);
    // CALL(aFlyMap);
    FlyMap();
    // CALL(aPokegear_DummyFunction);
    // LD_B(SCGB_POKEGEAR_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_POKEGEAR_PALS);
    // CALL(aSetPalettes);
    SetPalettes();

    uint8_t a;
    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto pressedB;
        if(hram->hJoyPressed & B_BUTTON) {
        // pressedB:
            // LD_A(-1);
            a = 0xff;
            // goto exit;
            break;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON);
        // IF_NZ goto pressedA;
        else if(hram->hJoyPressed & A_BUTTON) {
        // pressedA:
            // LD_A_addr(wTownMapPlayerIconLandmark);
            // LD_L_A;
            // LD_H(0);
            // ADD_HL_HL;
            // LD_DE(mFlypoints + 1);
            // ADD_HL_DE;
            // LD_A_hl;
            a = Flypoints[wram->wTownMapPlayerIconLandmark].spawn;
            break;
        }
        // CALL(av_FlyMap_HandleDPad);
        v_FlyMap_HandleDPad();
        // CALL(aGetMapCursorCoordinates);
        GetMapCursorCoordinates();
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// exit:
    // LD_addr_A(wTownMapPlayerIconLandmark);
    wram->wTownMapPlayerIconLandmark = a;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // LD_A(SCREEN_HEIGHT_PX);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // XOR_A_A;  // LOW(vBGMap0)
    // LDH_addr_A(hBGMapAddress);
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap0;
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // LD_E_A;
    // RET;
    return wram->wTownMapPlayerIconLandmark;
}

static void TownMapBubble_Name(void) {
//  We need the map location of the default flypoint
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;  // two bytes per flypoint
    // LD_DE(mFlypoints);
    // ADD_HL_DE;
    // LD_E_hl;
    // FARCALL(aGetLandmarkName);
    // hlcoord(2, 1, wTilemap);
    // LD_DE(wStringBuffer1);
    // CALL(aPlaceString);
    PlaceStringSimple(GetLandmarkName(Flypoints[wram->wTownMapPlayerIconLandmark].landmark), coord(2, 1, wram->wTilemap));
    // RET;
}

void TownMapBubble(void){
//  Draw the bubble containing the location text in the town map HUD

//  Top-left corner
    // hlcoord(1, 0, wTilemap);
    // LD_A(0x30);
    // LD_hli_A;
    *coord(1, 0, wram->wTilemap) = 0x30;
//  Top row
    // LD_BC(16);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(2, 0, wram->wTilemap), 16, 0x7f);
//  Top-right corner
    // LD_A(0x31);
    // LD_hl_A;
    *coord(18, 0, wram->wTilemap) = 0x31;
    // hlcoord(1, 1, wTilemap);

//  Middle row
    // LD_BC(SCREEN_WIDTH - 2);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(1, 1, wram->wTilemap), SCREEN_WIDTH - 2, 0x7f);

//  Bottom-left corner
    // hlcoord(1, 2, wTilemap);
    // LD_A(0x32);
    // LD_hli_A;
    *coord(1, 2, wram->wTilemap) = 0x32;
//  Bottom row
    // LD_BC(16);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(2, 2, wram->wTilemap), 16, 0x7f);
//  Bottom-right corner
    // LD_A(0x33);
    // LD_hl_A;
    *coord(18, 2, wram->wTilemap) = 0x33;

//  Print "Where?"
    // hlcoord(2, 0, wTilemap);
    // LD_DE(mTownMapBubble_Where);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("Where?@"), coord(2, 0, wram->wTilemap));
//  Print the name of the default flypoint
    // CALL(aTownMapBubble_Name);
    TownMapBubble_Name();
//  Up/down arrows
    // hlcoord(18, 1, wTilemap);
    // LD_hl(0x34);
    *coord(18, 1, wram->wTilemap) = 0x34;
    // RET;
    return;

// Where:
    //db ['"Where?@"'];
}

void GetMapCursorCoordinates(void){
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // LD_DE(mFlypoints);
    // ADD_HL_DE;
    // LD_E_hl;
    uint8_t e = Flypoints[wram->wTownMapPlayerIconLandmark].landmark;
    // FARCALL(aGetLandmarkCoords);
    struct Coords coord = GetLandmarkCoords(e);
    // LD_A_addr(wTownMapCursorCoordinates);
    // LD_C_A;
    // LD_A_addr(wTownMapCursorCoordinates + 1);
    // LD_B_A;
    // LD_HL(4);
    // ADD_HL_BC;
    // LD_hl_E;
    gTownMapCursorCoordinates->xCoord = (uint8_t)coord.x;
    // LD_HL(5);
    // ADD_HL_BC;
    // LD_hl_D;
    gTownMapCursorCoordinates->yCoord = (uint8_t)coord.y;
    // RET;
}

//  Check if the flypoint loaded in [hl] has been visited yet.
bool CheckIfVisitedFlypoint(uint8_t fp){
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // LD_L_hl;
    // LD_H(0);
    // ADD_HL_HL;
    // LD_DE(mFlypoints + 1);
    // ADD_HL_DE;
    // LD_C_hl;
    // CALL(aHasVisitedSpawn);
    // POP_HL;
    // POP_DE;
    // POP_BC;
    // AND_A_A;
    // RET;
    return HasVisitedSpawn(Flypoints[fp].spawn) != 0;
}

//  Check if spawn point c has been visited.
uint8_t HasVisitedSpawn(uint8_t c){
    // LD_HL(wVisitedSpawns);
    // LD_B(CHECK_FLAG);
    // LD_D(0);
    // PREDEF(pSmallFarFlagAction);
    // LD_A_C;
    // RET;
    return SmallFarFlagAction(wram->wVisitedSpawns, c, CHECK_FLAG);

// INCLUDE "data/maps/flypoints.asm"
}

void Pokegear_DummyFunction(void){
    RET;

}

static void FlyMap_MapHud(void){
    // CALL(aTownMapBubble);
    TownMapBubble();
    // CALL(aTownMapPals);
    TownMapPals();
    // hlbgcoord(0, 0, vBGMap0);  // BG Map 0
    // CALL(aTownMapBGUpdate);
    TownMapBGUpdate(bgcoord(0, 0, vBGMap0));
    // CALL(aTownMapMon);
    struct SpriteAnim* bc = TownMapMon();
    // LD_A_C;
    // LD_addr_A(wTownMapCursorCoordinates);
    // LD_A_B;
    // LD_addr_A(wTownMapCursorCoordinates + 1);
    gTownMapCursorCoordinates = bc;
    // RET;
}

void FlyMap(void){
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aGetWorldMapLocation);
    uint8_t loc = GetWorldMapLocation(wram->wMapGroup, wram->wMapNumber);
//  If we're not in a valid location, i.e. Pokecenter floor 2F,
//  the backup map information is used.
    // CP_A(LANDMARK_SPECIAL);
    // IF_NZ goto CheckRegion;
    if(loc == LANDMARK_SPECIAL) {
        // LD_A_addr(wBackupMapGroup);
        // LD_B_A;
        // LD_A_addr(wBackupMapNumber);
        // LD_C_A;
        // CALL(aGetWorldMapLocation);
        loc = GetWorldMapLocation(wram->wBackupMapGroup, wram->wBackupMapNumber);
    }

// CheckRegion:
//  The first 46 locations are part of Johto. The rest are in Kanto.
    // CP_A(KANTO_LANDMARK);
    // IF_NC goto KantoFlyMap;
    if(loc < KANTO_LANDMARK) {
    //  Johto fly map
    //  Note that .NoKanto should be modified in tandem with this branch
        // PUSH_AF;
        // LD_A(JOHTO_FLYPOINT);  // first Johto flypoint
        // LD_addr_A(wTownMapPlayerIconLandmark);  // first one is default (New Bark Town)
        wram->wTownMapPlayerIconLandmark = JOHTO_FLYPOINT;
        // LD_addr_A(wStartFlypoint);
        wram->wStartFlypoint = JOHTO_FLYPOINT;
        // LD_A(KANTO_FLYPOINT - 1);  // last Johto flypoint
        // LD_addr_A(wEndFlypoint);
        wram->wEndFlypoint = KANTO_FLYPOINT - 1;
    //  Fill out the map
        // CALL(aFillJohtoMap);
        FillJohtoMap();
        // CALL(aFlyMap_MapHud);
        FlyMap_MapHud();
        // POP_AF;
        // CALL(aTownMapPlayerIcon);
        TownMapPlayerIcon(loc);
        // RET;
        return;
    }
    else {
    // KantoFlyMap:
    //  The event that there are no flypoints enabled in a map is not
    //  accounted for. As a result, if you attempt to select a flypoint
    //  when there are none enabled, the game will crash. Additionally,
    //  the flypoint selection has a default starting point that
    //  can be flown to even if none are enabled.
    //  To prevent both of these things from happening when the player
    //  enters Kanto, fly access is restricted until Indigo Plateau is
    //  visited and its flypoint enabled.
        // PUSH_AF;
        // LD_C(SPAWN_INDIGO);
        // CALL(aHasVisitedSpawn);
        // AND_A_A;
        // IF_Z goto NoKanto;
        if(HasVisitedSpawn(SPAWN_INDIGO) != 0) {
        //  Kanto's map is only loaded if we've visited Indigo Plateau
            // LD_A(KANTO_FLYPOINT);  // first Kanto flypoint
            // LD_addr_A(wStartFlypoint);
            wram->wStartFlypoint = KANTO_FLYPOINT;
            // LD_A(NUM_FLYPOINTS - 1);  // last Kanto flypoint
            // LD_addr_A(wEndFlypoint);
            wram->wEndFlypoint = NUM_FLYPOINTS - 1;
            // LD_addr_A(wTownMapPlayerIconLandmark);  // last one is default (Indigo Plateau)
            wram->wTownMapPlayerIconLandmark = NUM_FLYPOINTS - 1;
        //  Fill out the map
            // CALL(aFillKantoMap);
            FillKantoMap();
            // CALL(aFlyMap_MapHud);
            FlyMap_MapHud();
            // POP_AF;
            // CALL(aTownMapPlayerIcon);
            TownMapPlayerIcon(loc);
            // RET;
            return;
        }
        else {
        // NoKanto:
        //  If Indigo Plateau hasn't been visited, we use Johto's map instead
            // LD_A(JOHTO_FLYPOINT);  // first Johto flypoint
            // LD_addr_A(wTownMapPlayerIconLandmark);  // first one is default (New Bark Town)
            wram->wTownMapPlayerIconLandmark = JOHTO_FLYPOINT;
            // LD_addr_A(wStartFlypoint);
            wram->wStartFlypoint = JOHTO_FLYPOINT;
            // LD_A(KANTO_FLYPOINT - 1);  // last Johto flypoint
            // LD_addr_A(wEndFlypoint);
            wram->wEndFlypoint = KANTO_FLYPOINT - 1;
            // CALL(aFillJohtoMap);
            FillJohtoMap();
            // POP_AF;
            return FlyMap_MapHud();
        }
    }
}

static const char* GetPlayerOrFastShipIcon(void){
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // CP_A(LANDMARK_FAST_SHIP);
    // IF_Z goto FastShip;
    if(wram->wTownMapPlayerIconLandmark == LANDMARK_FAST_SHIP) {
    // FastShip:
        // LD_DE(mFastShipGFX);
        // LD_B(BANK(aFastShipGFX));
        // RET;
        return FastShipGFX;
    }
    // FARCALL(aGetPlayerIcon);
    // RET;
    return GetPlayerIcon();
}

static void PlaceString_MonsNest(species_t species) {
    static const char String_SNest[] = "\'S NEST";
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH, 0x7f);
    // hlcoord(0, 1, wTilemap);
    // LD_A(0x06);
    // LD_hli_A;
    *coord(0, 1, wram->wTilemap) = 0x06;
    // LD_BC(SCREEN_WIDTH - 2);
    // LD_A(0x07);
    // CALL(aByteFill);
    ByteFill(coord(1, 1, wram->wTilemap), SCREEN_WIDTH - 2, 0x07);
    // LD_hl(0x17);
    *coord(SCREEN_WIDTH - 1, 1, wram->wTilemap) = 0x17;
    // CALL(aGetPokemonName);
    uint8_t* de = GetPokemonName(species);
    // hlcoord(2, 0, wTilemap);
    struct TextPrintState st = {.hl = coord(2, 0, wram->wTilemap), .de = de};
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_H_B;
    // LD_L_C;
    st.hl = st.bc;
    // LD_DE(mPokedex_GetArea_String_SNest);
    st.de = U82C(String_SNest);
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // RET;
}

static void Pokedex_GetArea_GetAndPlaceNest(uint8_t a, species_t species){
    // LD_addr_A(wTownMapCursorLandmark);
    wram->wTownMapCursorLandmark = a;
    // LD_E_A;
    // FARCALL(aFindNest);  // load nest landmarks into wTilemap[0,0]
    FindNest_Conv(a, species);
    // decoord(0, 0, wTilemap);
    tile_t* de = coord(0, 0, wram->wTilemap);
    // LD_HL(wVirtualOAMSprite00);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;

    while(*de != 0) {
    // nestloop:
        // LD_A_de;
        // AND_A_A;
        // IF_Z goto done_nest;
        // PUSH_DE;
        // LD_E_A;
        // PUSH_HL;
        // FARCALL(aGetLandmarkCoords);
        const struct Coords coords = GetLandmarkCoords(*de);
        // POP_HL;
    // load into OAM
        // LD_A_D;
        // SUB_A(4);
        // LD_hli_A;  // y
        hl->yCoord = coords.y - 4;
        // LD_A_E;
        // SUB_A(4);
        // LD_hli_A;  // x
        hl->xCoord = coords.x - 4;
        // LD_A(0x7f);  // nest icon
        // LD_hli_A;  // tile id
        hl->tileID = 0x7f;
        // XOR_A_A;
        // LD_hli_A;  // attributes
        hl->attributes = 0;
        hl++;
    // next
        // POP_DE;
        // INC_DE;
        de++;
        // goto nestloop;
    }

// done_nest:
    // LD_HL(wVirtualOAM);
    // decoord(0, 0, wTilemap);
    // LD_BC(wVirtualOAMEnd - wVirtualOAM);
    // CALL(aCopyBytes);
    CopyBytes(coord(0, 0, wram->wTilemap), wram->wVirtualOAMSprite, sizeof(wram->wVirtualOAMSprite)); // ...why?
    // RET;
}

static void Pokedex_GetArea_LeftRightInput(uint8_t joypad, species_t species){
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    if(joypad & D_LEFT) {
    // left:
        // LDH_A_addr(hWY);
        // CP_A(SCREEN_HEIGHT_PX);
        // RET_Z ;
        if(hram->hWY == SCREEN_HEIGHT_PX)
            return;
        // CALL(aClearSprites);
        ClearSprites();
        // LD_A(SCREEN_HEIGHT_PX);
        // LDH_addr_A(hWY);
        hram->hWY = SCREEN_HEIGHT_PX;
        // XOR_A_A;  // JOHTO_REGION
        // CALL(aPokedex_GetArea_GetAndPlaceNest);
        Pokedex_GetArea_GetAndPlaceNest(JOHTO_REGION, species);
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    if(joypad & D_RIGHT) {
    // right:
        // LD_A_addr(wStatusFlags);
        // BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
        // RET_Z ;
        if(!bit_test(wram->wStatusFlags, STATUSFLAGS_HALL_OF_FAME_F))
            return;
        // LDH_A_addr(hWY);
        // AND_A_A;
        // RET_Z ;
        if(hram->hWY == 0)
            return;
        // CALL(aClearSprites);
        ClearSprites();
        // XOR_A_A;
        // LDH_addr_A(hWY);
        hram->hWY = 0;
        // LD_A(KANTO_REGION);
        // CALL(aPokedex_GetArea_GetAndPlaceNest);
        Pokedex_GetArea_GetAndPlaceNest(KANTO_REGION, species);
        // RET;
        return;
    }
    // RET;
}

static void Pokedex_GetArea_BlinkNestIcons(void) {
    // LDH_A_addr(hVBlankCounter);
    // LD_E_A;
    uint8_t e = hram->hVBlankCounter;
    // AND_A(0xf);
    // RET_NZ ;
    if((e & 0xf) != 0)
        return;
    // LD_A_E;
    // AND_A(0x10);
    // IF_NZ goto copy_sprites;
    if((e & 0x10) != 0) {
    // copy_sprites:
        // hlcoord(0, 0, wTilemap);
        // LD_DE(wVirtualOAM);
        // LD_BC(wVirtualOAMEnd - wVirtualOAM);
        // CALL(aCopyBytes);
        CopyBytes(wram->wVirtualOAMSprite, coord(0, 0, wram->wTilemap), sizeof(wram->wVirtualOAMSprite));
        // RET;
        return;
    }
    else {
        // CALL(aClearSprites);
        ClearSprites();
        // RET;
        return;
    }
}

//  Don't show the player's sprite if you're
//  not in the same region as what's currently
//  on the screen.
static bool Pokedex_GetArea_CheckPlayerLocation(void){
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // CP_A(LANDMARK_FAST_SHIP);
    // IF_Z goto johto;
    // CP_A(KANTO_LANDMARK);
    // IF_C goto johto;
    bool clear;
    if(wram->wTownMapPlayerIconLandmark == LANDMARK_FAST_SHIP || wram->wTownMapPlayerIconLandmark < KANTO_LANDMARK) {
    // johto:
        // LD_A_addr(wTownMapCursorLandmark);
        // AND_A_A;
        // IF_NZ goto clear;
        clear = wram->wTownMapCursorLandmark != 0;
    }
//  kanto
    else {
        // LD_A_addr(wTownMapCursorLandmark);
        // AND_A_A;
        // IF_Z goto clear;
        clear = wram->wTownMapCursorLandmark == 0;
    }
    if(clear) {
    // clear:
        // LD_HL(wVirtualOAM);
        // LD_BC(wVirtualOAMEnd - wVirtualOAM);
        // XOR_A_A;
        // CALL(aByteFill);
        ByteFill(wram->wVirtualOAMSprite, sizeof(wram->wVirtualOAMSprite), 0);
        // SCF;
        // RET;
        return false;
    }
    // goto ok;

// ok:
    // AND_A_A;
    // RET;
    return true;
}

static void Pokedex_GetArea_HideNestsShowPlayer(void){
    static const uint8_t PlayerOAM[] = {
    // y pxl, x pxl, tile offset
        -1 * 8, -1 * 8, 0,  // top left
        -1 * 8,  0 * 8, 1,  // top right
         0 * 8, -1 * 8, 2,  // bottom left
         0 * 8,  0 * 8, 3,  // bottom right
        0x80,  // terminator
    };
    // CALL(aPokedex_GetArea_CheckPlayerLocation);
    // RET_C ;
    if(!Pokedex_GetArea_CheckPlayerLocation())
        return;
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // LD_E_A;
    // FARCALL(aGetLandmarkCoords);
    const struct Coords coords = GetLandmarkCoords(wram->wTownMapPlayerIconLandmark);
    // LD_C_E;
    // LD_B_D;
    // LD_DE(mPokedex_GetArea_PlayerOAM);
    const uint8_t* de = PlayerOAM;
    // LD_HL(wVirtualOAMSprite00);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;

    while(*de != 0x80) {
    // ShowPlayerLoop:
        // LD_A_de;
        // CP_A(0x80);
        // IF_Z goto clear_oam;
        // ADD_A_B;
        // LD_hli_A;  // y
        hl->yCoord = *de + coords.y;
        // INC_DE;
        de++;
        // LD_A_de;
        // ADD_A_C;
        // LD_hli_A;  // x
        hl->xCoord = *de + coords.x;
        // INC_DE;
        de++;
        // LD_A_de;
        // ADD_A(0x78);  // where the player's sprite is loaded
        // LD_hli_A;  // tile id
        hl->tileID = *de + 0x78;
        // INC_DE;
        de++;
        // PUSH_BC;
        // LD_C(PAL_OW_RED);
        // LD_A_addr(wPlayerGender);
        // BIT_A(PLAYERGENDER_FEMALE_F);
        // IF_Z goto male;
        // INC_C;  // PAL_OW_BLUE

    // male:
        // LD_A_C;
        // LD_hli_A;  // attributes
        hl->attributes = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? PAL_OW_BLUE: PAL_OW_RED;
        // POP_BC;
        // goto ShowPlayerLoop;
    }

// clear_oam:
    // LD_HL(wVirtualOAMSprite04);
    // LD_BC(wVirtualOAMEnd - wVirtualOAMSprite04);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wVirtualOAMSprite + 4, sizeof(wram->wVirtualOAMSprite) - 4 * sizeof(wram->wVirtualOAMSprite[0]), 0x0);
    // RET;
}

void Pokedex_GetArea(uint8_t e, species_t species){
//  e: Current landmark
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // PUSH_AF;
    uint8_t playerIconLandmark = wram->wTownMapPlayerIconLandmark;
    // LD_A_addr(wTownMapCursorLandmark);
    // PUSH_AF;
    uint8_t cursorLandmark = wram->wTownMapCursorLandmark;
    // LD_A_E;
    // LD_addr_A(wTownMapPlayerIconLandmark);
    wram->wTownMapPlayerIconLandmark = e;
    // CALL(aClearSprites);
    ClearSprites();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // LD_DE(mPokedexNestIconGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x7f);
    // LD_BC((BANK(aPokedexNestIconGFX) << 8) | 1);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x7f, PokedexNestIconGFX, 0, 1);
    // CALL(aPokedex_GetArea_GetPlayerOrFastShipIcon);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x78);
    // LD_C(4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x78, GetPlayerOrFastShipIcon(), 0, 4);
    // CALL(aLoadTownMapGFX);
    LoadTownMapGFX();
    // CALL(aFillKantoMap);
    FillKantoMap();
    // CALL(aPokedex_GetArea_PlaceString_MonsNest);
    PlaceString_MonsNest(species);
    // CALL(aTownMapPals);
    TownMapPals();
    // hlbgcoord(0, 0, vBGMap1);
    // CALL(aTownMapBGUpdate);
    TownMapBGUpdate(bgcoord(0, 0, vBGMap1));
    // CALL(aFillJohtoMap);
    FillJohtoMap();
    // CALL(aPokedex_GetArea_PlaceString_MonsNest);
    PlaceString_MonsNest(species);
    // CALL(aTownMapPals);
    TownMapPals();
    // hlbgcoord(0, 0, vBGMap0);
    // CALL(aTownMapBGUpdate);
    TownMapBGUpdate(bgcoord(0, 0, vBGMap0));
    // LD_B(SCGB_POKEGEAR_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_POKEGEAR_PALS);
    // CALL(aSetPalettes);
    SetPalettes();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // XOR_A_A;  // JOHTO_REGION
    // CALL(aPokedex_GetArea_GetAndPlaceNest);
    Pokedex_GetArea_GetAndPlaceNest(JOHTO_REGION, species);

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto a_b;
        if(hram->hJoyPressed & (A_BUTTON | B_BUTTON)) {
        // a_b:
            // CALL(aClearSprites);
            ClearSprites();
            // POP_AF;
            // LD_addr_A(wTownMapCursorLandmark);
            wram->wTownMapCursorLandmark = cursorLandmark;
            // POP_AF;
            // LD_addr_A(wTownMapPlayerIconLandmark);
            wram->wTownMapPlayerIconLandmark = playerIconLandmark;
            // RET;
            return;
        }
        // LDH_A_addr(hJoypadDown);
        // AND_A(SELECT);
        // IF_NZ goto select;
        if(hram->hJoypadDown & SELECT) {
        // select:
            // CALL(aPokedex_GetArea_HideNestsShowPlayer);
            Pokedex_GetArea_HideNestsShowPlayer();
        }
        else {
            // CALL(aPokedex_GetArea_LeftRightInput);
            Pokedex_GetArea_LeftRightInput(hram->hJoypadDown, species);
            // CALL(aPokedex_GetArea_BlinkNestIcons);
            Pokedex_GetArea_BlinkNestIcons();
            // goto next;
        }
    // next:
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }
}

//  Update BG Map tiles and attributes
static void TownMapBGUpdate(uint16_t hl){
//  BG Map address
    // LD_A_L;
    // LDH_addr_A(hBGMapAddress);
    // LD_A_H;
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = hl;
//  Only update palettes on CGB
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto tiles;
    if(hram->hCGB != 0) {
    //  BG Map mode 2 (palettes)
        // LD_A(2);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_ATTRS;
    //  The BG Map is updated in thirds, so we wait

    //  3 frames to update the whole screen's palettes.
        // LD_C(3);
        // CALL(aDelayFrames);
#if ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
        DelayFrame();
#else
        DelayFrames(3);
#endif
    }
// tiles:
//  Update BG Map tiles
    // CALL(aWaitBGMap);
    WaitBGMap();
//  Turn off BG Map update
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // RET;
    return;
}

static void FillJohtoMap(void){
    asset_s a = LoadAsset(JohtoMap);
    FillTownMap(a.ptr);
    FreeAsset(a);
}

static void FillKantoMap(void){
    asset_s a = LoadAsset(KantoMap);
    FillTownMap(a.ptr);
    FreeAsset(a);
}

static void FillTownMap(const uint8_t* map){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    const uint8_t* de = map;

    while(*de != 0xff)
    {
        // LD_A_de;

        // CP_A(-1);
        // RET_Z ;

        // LD_A_de;
        // LD_hli_A;
        // INC_DE;
        *(hl++) = *(de++);
    }
}

enum {
    PAL_TOWNMAP_BORDER,   // 0
    PAL_TOWNMAP_EARTH,    // 1
    PAL_TOWNMAP_MOUNTAIN, // 2
    PAL_TOWNMAP_CITY,     // 3
    PAL_TOWNMAP_POI,      // 4
    PAL_TOWNMAP_POI_MTN,  // 5
};

#define townmappair(_0, _1) ((PAL_TOWNMAP_##_1 & 0xf) << 4) | (PAL_TOWNMAP_##_0 & 0xf)
#define townmappals(_0, _1, _2, _3, _4, _5, _6, _7) townmappair(_0, _1), townmappair(_2, _3), townmappair(_4, _5), townmappair(_6, _7)

static void TownMapPals(void){
    static const uint8_t PalMap[] = {
    // gfx/pokegear/town_map.png
        townmappals(EARTH,    EARTH,    EARTH,    MOUNTAIN, MOUNTAIN, MOUNTAIN, BORDER,   BORDER),
        townmappals(EARTH,    EARTH,    CITY,     EARTH,    POI,      POI_MTN,  POI,      POI_MTN),
        townmappals(EARTH,    EARTH,    EARTH,    MOUNTAIN, MOUNTAIN, MOUNTAIN, BORDER,   BORDER),
        townmappals(EARTH,    EARTH,    BORDER,   EARTH,    EARTH,    BORDER,   BORDER,   BORDER),
        townmappals(EARTH,    EARTH,    EARTH,    MOUNTAIN, MOUNTAIN, MOUNTAIN, BORDER,   BORDER),
        townmappals(BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER),
    // gfx/pokegear/pokegear.png
        townmappals(BORDER,   BORDER,   BORDER,   BORDER,   POI,      POI,      POI,      BORDER),
        townmappals(BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER),
        townmappals(CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY),
        townmappals(CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     BORDER),
        townmappals(CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY,     CITY),
        townmappals(BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER,   BORDER),
    };
//  Assign palettes based on tile ids
    // hlcoord(0, 0, wTilemap);
    const uint8_t* hl = coord(0, 0, wram->wTilemap);
    // decoord(0, 0, wAttrmap);
    uint8_t* de = coord(0, 0, wram->wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    uint16_t bc = SCREEN_WIDTH * SCREEN_HEIGHT;

    do {
    // loop:
    //  Current tile
        // LD_A_hli;
        uint8_t a = *(hl++);
        // PUSH_HL;
    //  The palette map covers tiles $00 to $5f
        // CP_A(0x60);
        // IF_NC goto pal0;
        if(a < 0x60) {

        //  The palette data is condensed to nybbles, least-significant first.
            // LD_HL(mTownMapPals_PalMap);
            // SRL_A;
            // IF_C goto odd;
            if((a & 1) == 0) {
            //  Even-numbered tile ids take the bottom nybble...
                // ADD_A_L;
                // LD_L_A;
                // LD_A_H;
                // ADC_A(0);
                // LD_H_A;
                // LD_A_hl;
                // AND_A(PALETTE_MASK);
                a = PalMap[a >> 1] & PALETTE_MASK;
                // goto update;
            }
            else {
            // odd:
            //  ...and odd ids take the top.
                // ADD_A_L;
                // LD_L_A;
                // LD_A_H;
                // ADC_A(0);
                // LD_H_A;
                // LD_A_hl;
                // SWAP_A;
                // AND_A(PALETTE_MASK);
                a = (PalMap[a >> 1] >> 4) & PALETTE_MASK;
                // goto update;
            }
        } else {
        // pal0:
            // XOR_A_A;
            a = 0;
        }
    // update:
        // POP_HL;
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
    return;
}

//  Draw the FlyMon icon at town map location
static struct SpriteAnim* TownMapMon(void){

//  Get FlyMon species
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartySpecies);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wTempIconSpecies);
    wram->wTempIconSpecies = wram->wPartySpecies[wram->wCurPartyMon];
//  Get FlyMon icon
    // LD_E(0x08);  // starting tile in VRAM
    // FARCALL(aGetSpeciesIcon);
    GetSpeciesIcon(0x08);
//  Animation/palette
    //depixel ['0', '0']
    // depixel2(0, 0);
    // LD_A(SPRITE_ANIM_INDEX_PARTY_MON);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(SPRITE_ANIM_INDEX_PARTY_MON, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x08);
    bc->tileID = 0x08;
    // LD_HL(SPRITEANIMSTRUCT_ANIM_SEQ_ID);
    // ADD_HL_BC;
    // LD_hl(SPRITE_ANIM_SEQ_NULL);
    bc->animSeqID = SPRITE_ANIM_SEQ_NULL;
    // RET;
    return bc;
}

static struct SpriteAnim* TownMapPlayerIcon(uint8_t location){
//  Draw the player icon at town map location in a
    // PUSH_AF;
    // FARCALL(aGetPlayerIcon);
    const char* path = GetPlayerIcon();
//  Standing icon
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x10);
    // LD_C(4);  // # tiles
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x10, path, 0, 4);
//  Walking icon
    // LD_HL(12 * LEN_2BPP_TILE);
    // ADD_HL_DE;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x14);
    // LD_C(4);  // # tiles
    // LD_A(BANK(aChrisSpriteGFX));  // does nothing
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x14, path, 12, 4);
//  Animation/palette
    //depixel ['0', '0']
    // depixel2(0, 0);
    // LD_B(SPRITE_ANIM_INDEX_RED_WALK);  // Male
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto got_gender;
    // LD_B(SPRITE_ANIM_INDEX_BLUE_WALK);  // Female
    uint8_t b = (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? SPRITE_ANIM_INDEX_BLUE_WALK: SPRITE_ANIM_INDEX_RED_WALK;

// got_gender:
    // LD_A_B;
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct(b, pixel2(0, 0));
    // LD_HL(SPRITEANIMSTRUCT_TILE_ID);
    // ADD_HL_BC;
    // LD_hl(0x10);
    bc->tileID = 0x10;
    // POP_AF;
    // LD_E_A;
    // PUSH_BC;
    // FARCALL(aGetLandmarkCoords);
    struct Coords coord = GetLandmarkCoords(location);
    // POP_BC;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_hl_E;
    bc->xCoord = (uint8_t)coord.x;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_hl_D;
    bc->yCoord = (uint8_t)coord.y;
    // RET;
    return bc;
}

void LoadTownMapGFX(void){
    // LD_HL(mTownMapGFX);
    // LD_DE(vTiles2);
    // LD_BC((BANK(aTownMapGFX) << 8) | 48);
    // CALL(aDecompressRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, TownMapGFX, 0, 48);
    // RET;
}

static void EntireFlyMap_HandleDPad(void){
    // LD_HL(hJoyLast);
    uint8_t joy = hram->hJoyLast;
    // LD_A_hl;
    // AND_A(D_DOWN | D_RIGHT);
    // IF_NZ goto ScrollNext;
    if(joy & (D_DOWN | D_RIGHT)) {
    // ScrollNext:
        // LD_HL(wTownMapPlayerIconLandmark);
        // LD_A_hl;
        // CP_A(NUM_FLYPOINTS - 1);
        // IF_C goto NotAtEndYet;
        if(wram->wTownMapPlayerIconLandmark >= NUM_FLYPOINTS - 1) {
            // LD_hl(-1);
            wram->wTownMapPlayerIconLandmark = 0xff;
        }
    // NotAtEndYet:
        // INC_hl;
        wram->wTownMapPlayerIconLandmark++;
        // goto FillMap;
    }
    // LD_A_hl;
    // AND_A(D_UP | D_LEFT);
    // IF_NZ goto ScrollPrev;
    else if(joy & (D_UP | D_LEFT)) {
    // ScrollPrev:
        // LD_HL(wTownMapPlayerIconLandmark);
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto NotAtStartYet;
        if(wram->wTownMapPlayerIconLandmark == 0) {
            // LD_hl(NUM_FLYPOINTS);
            wram->wTownMapPlayerIconLandmark = NUM_FLYPOINTS;
        }

    // NotAtStartYet:
        // DEC_hl;
        wram->wTownMapPlayerIconLandmark--;
    }
    else {
        return;
    }
    // RET;

// FillMap:
    uint16_t b;
    uint8_t y;
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // CP_A(KANTO_FLYPOINT);
    // IF_C goto InJohto;
    if(wram->wTownMapPlayerIconLandmark >= KANTO_FLYPOINT) {
        // CALL(aFillKantoMap);
        FillKantoMap();
        // XOR_A_A;
        y = 0;
        // LD_B(HIGH(vBGMap1));
        b = vBGMap1;
        // goto Finally;
    }
    else {
    // InJohto:
        // CALL(aFillJohtoMap);
        FillJohtoMap();
        // LD_A(SCREEN_HEIGHT_PX);
        y = SCREEN_HEIGHT_PX;
        // LD_B(HIGH(vBGMap0));
        b = vBGMap0;
    }

// Finally:
    // LDH_addr_A(hWY);
    hram->hWY = y;
    // LD_A_B;
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = b;
    // CALL(aTownMapBubble);
    TownMapBubble();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // RET;
}

//  //  unreferenced
//  Similar to _FlyMap, but scrolls through the entire
//  Flypoints data of both regions. A debug function?
uint8_t EntireFlyMap(void){
    // XOR_A_A;
    // LD_addr_A(wTownMapPlayerIconLandmark);
    wram->wTownMapPlayerIconLandmark = 0;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aClearSprites);
    ClearSprites();
    // LD_HL(hInMenu);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_hl(0x1);
    hram->hInMenu = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // CALL(aLoadTownMapGFX);
    LoadTownMapGFX();
    // LD_DE(mFlyMapLabelBorderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x30);
    // LD_BC((BANK(aFlyMapLabelBorderGFX) << 8) | 6);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x30, FlyMapLabelBorderGFX, 0, 6);
    // CALL(aFillKantoMap);
    FillKantoMap();
    // CALL(aTownMapBubble);
    TownMapBubble();
    // CALL(aTownMapPals);
    TownMapPals();
    // hlbgcoord(0, 0, vBGMap1);
    // CALL(aTownMapBGUpdate);
    TownMapBGUpdate(vBGMap1);
    // CALL(aFillJohtoMap);
    FillJohtoMap();
    // CALL(aTownMapBubble);
    TownMapBubble();
    // CALL(aTownMapPals);
    TownMapPals();
    // hlbgcoord(0, 0, vBGMap0);
    // CALL(aTownMapBGUpdate);
    TownMapBGUpdate(vBGMap0);
    // CALL(aTownMapMon);
    // LD_A_C;
    // LD_addr_A(wTownMapCursorCoordinates);
    // LD_A_B;
    // LD_addr_A(wTownMapCursorCoordinates + 1);
    gTownMapCursorCoordinates = TownMapPlayerIcon(wram->wTownMapPlayerIconLandmark);
    // LD_B(SCGB_POKEGEAR_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_POKEGEAR_PALS);
    // CALL(aSetPalettes);
    SetPalettes();

    uint8_t a;
    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto pressedB;
        if(hram->hJoyPressed & B_BUTTON) {
        // pressedB:
            // LD_A(-1);
            // goto exit;
            a = 0xff;
            break;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON);
        // IF_NZ goto pressedA;
        else if(hram->hJoypadPressed & A_BUTTON) {
        // pressedA:
            // LD_A_addr(wTownMapPlayerIconLandmark);
            // LD_L_A;
            // LD_H(0);
            // ADD_HL_HL;
            // LD_DE(mFlypoints + 1);
            // ADD_HL_DE;
            // LD_A_hl;
            a = Flypoints[wram->wTownMapPlayerIconLandmark].spawn;
            break;
        }
        // CALL(aEntireFlyMap_HandleDPad);
        EntireFlyMap_HandleDPad();
        // CALL(aGetMapCursorCoordinates);
        GetMapCursorCoordinates();
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// exit:
    // LD_addr_A(wTownMapPlayerIconLandmark);
    wram->wTownMapPlayerIconLandmark = a;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // LD_A(SCREEN_HEIGHT_PX);
    // LDH_addr_A(hWY);
    hram->hWY = SCREEN_HEIGHT_PX;
    // XOR_A_A;  // LOW(vBGMap0)
    // LDH_addr_A(hBGMapAddress);
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap0;
    // LD_A_addr(wTownMapPlayerIconLandmark);
    // LD_E_A;
    return wram->wTownMapPlayerIconLandmark;
    // RET;

}
