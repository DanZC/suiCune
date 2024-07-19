#include "../../constants.h"
#include "slot_machine.h"
#include "../../home/audio.h"
#include "../../home/tilemap.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/clear_sprites.h"
#include "../../home/text.h"
#include "../../home/print_text.h"
#include "../../home/lcd.h"
#include "../../home/palettes.h"
#include "../../home/sprite_anims.h"
#include "../../home/menu.h"
#include "../../home/random.h"
#include "../../home/joypad.h"
#include "../battle_anims/functions.h"
#include "../gfx/sprites.h"
#include "../../mobile/mobile_41.h"
#include "../../data/text/common.h"

//  wSlotMatched values
//  + 4 for each entry
enum {
    SLOTS_SEVEN = 0x00,  // $00
    SLOTS_POKEBALL = 0x04,  // $04
    SLOTS_CHERRY = 0x08,  // $08
    SLOTS_PIKACHU = 0x0c,  // $0c
    SLOTS_SQUIRTLE = 0x10,  // $10
    SLOTS_STARYU = 0x14,  // $14
};
#define NUM_SLOT_REELS ((SLOTS_STARYU + 4) / 4)  //  6
#define SLOTS_NO_MATCH ((uint8_t)-1)

//  wSlotBias values
#define SLOTS_NO_BIAS ((uint8_t)-1)

#define REEL_SIZE (15)

//  Constants for slot_reel offsets (see macros/wram.asm)
#define REEL_ACTION        (wReel1ReelAction - wReel1)
#define REEL_TILEMAP_ADDR  (wReel1TilemapAddr - wReel1)
#define REEL_POSITION      (wReel1Position - wReel1)
#define REEL_SPIN_DISTANCE (wReel1SpinDistance - wReel1)
#define REEL_SPIN_RATE     (wReel1SpinRate - wReel1)
#define REEL_OAM_ADDR      (wReel1OAMAddr - wReel1)
#define REEL_X_COORD       (wReel1XCoord - wReel1)
#define REEL_MANIP_COUNTER (wReel1ManipCounter - wReel1)
#define REEL_MANIP_DELAY   (wReel1ManipDelay - wReel1)
#define REEL_FIELD_0B      (wReel1Field0b - wReel1)
#define REEL_STOP_DELAY    (wReel1StopDelay - wReel1)

//  SlotsJumptable constants
enum {
    SLOTS_INIT,
    SLOTS_BET_AND_START,
    SLOTS_WAIT_START,
    SLOTS_WAIT_REEL1,
    SLOTS_WAIT_STOP_REEL1,
    SLOTS_WAIT_REEL2,
    SLOTS_WAIT_STOP_REEL2,
    SLOTS_WAIT_REEL3,
    SLOTS_WAIT_STOP_REEL3,
    SLOTS_NEXT_09,
    SLOTS_NEXT_0A,
    SLOTS_NEXT_0B,
    SLOTS_FLASH_IF_WIN,
    SLOTS_FLASH_SCREEN,
    SLOTS_GIVE_EARNED_COINS,
    SLOTS_PAYOUT_TEXT_AND_ANIM,
    SLOTS_PAYOUT_ANIM,
    SLOTS_RESTART_OF_QUIT,
    SLOTS_QUIT,
};
#define SLOTS_END_LOOP_F (7)

//  ReelActionJumptable constants
enum {
    REEL_ACTION_DO_NOTHING,
    REEL_ACTION_STOP_REEL_IGNORE_JOYPAD,
    REEL_ACTION_QUADRUPLE_RATE,
    REEL_ACTION_DOUBLE_RATE,
    REEL_ACTION_NORMAL_RATE,
    REEL_ACTION_HALF_RATE,
    REEL_ACTION_QUARTER_RATE,
    REEL_ACTION_STOP_REEL1,
    REEL_ACTION_STOP_REEL2,
    REEL_ACTION_STOP_REEL3,
    REEL_ACTION_SET_UP_REEL2_SKIP_TO_7,
    REEL_ACTION_WAIT_REEL2_SKIP_TO_7,
    REEL_ACTION_FAST_SPIN_REEL2_UNTIL_LINED_UP_7S,
    REEL_ACTION_UNUSED,
    REEL_ACTION_CHECK_DROP_REEL,
    REEL_ACTION_WAIT_DROP_REEL,
    REEL_ACTION_START_SLOW_ADVANCE_REEL3,
    REEL_ACTION_WAIT_SLOW_ADVANCE_REEL3,
    REEL_ACTION_INIT_GOLEM,
    REEL_ACTION_WAIT_GOLEM,
    REEL_ACTION_END_GOLEM,
    REEL_ACTION_INIT_CHANSEY,
    REEL_ACTION_WAIT_CHANSEY,
    REEL_ACTION_WAIT_EGG,
    REEL_ACTION_DROP_REEL,
};

struct SlotData {
    union {
        struct SlotReelData reel[3];
        struct {
            struct SlotReelData reel1;
            struct SlotReelData reel2;
            struct SlotReelData reel3;
        };
    };
    uint8_t reel1Stopped[3];
    uint8_t reel2Stopped[3];
    uint8_t reel3Stopped[3];
    uint8_t slotBias;
    uint8_t slotBet;
    uint8_t firstTwoReelsMatching;
    uint8_t firstTwoReelsMatchingSevens;
    uint8_t slotMatched;
    uint8_t curReelStopped[3];
    uint16_t payout;
    uint8_t curReelXCoord;
    uint8_t curReelYCoord;
    uint8_t slotBuildingMatch;
};

static struct SlotData gSlotData;

static void v_SlotMachine_InitGFX_LoadSlotTiles(uint8_t* dest) {
    LoadPNG2bppAssetToVRAM(dest + LEN_2BPP_TILE * 0x00, Slots2LZ);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x01, dest + LEN_2BPP_TILE * 0x02, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x05, dest + LEN_2BPP_TILE * 0x06, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x09, dest + LEN_2BPP_TILE * 0x0a, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x0d, dest + LEN_2BPP_TILE * 0x0e, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x11, dest + LEN_2BPP_TILE * 0x12, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x15, dest + LEN_2BPP_TILE * 0x16, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x19, dest + LEN_2BPP_TILE * 0x1a, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x1d, dest + LEN_2BPP_TILE * 0x1e, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x21, dest + LEN_2BPP_TILE * 0x22, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x25, dest + LEN_2BPP_TILE * 0x26, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x29, dest + LEN_2BPP_TILE * 0x2a, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x2d, dest + LEN_2BPP_TILE * 0x2e, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x31, dest + LEN_2BPP_TILE * 0x32, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x35, dest + LEN_2BPP_TILE * 0x36, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x39, dest + LEN_2BPP_TILE * 0x3a, LEN_2BPP_TILE);
    SwapBytes_Conv2(dest + LEN_2BPP_TILE * 0x3d, dest + LEN_2BPP_TILE * 0x3e, LEN_2BPP_TILE);
}

static void v_SlotMachine_InitGFX(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(vBGMap1 - vBGMap0);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(bgcoord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), 0x7f);
    // LD_B(SCGB_SLOT_MACHINE);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_SLOT_MACHINE);
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // LD_HL(wSlots);
    // LD_BC(wSlotsDataEnd - wSlots);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(&gSlotData, sizeof(gSlotData), 0x0);

    // LD_HL(mSlots2LZ);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aDecompress);
    v_SlotMachine_InitGFX_LoadSlotTiles(vram->vTiles0 + LEN_2BPP_TILE * 0x00);

    // LD_HL(mSlots3LZ);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x40);
    // CALL(aDecompress);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x40, Slots3LZ, 0, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x41, Slots3LZ, 3, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x42, Slots3LZ, 1, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x43, Slots3LZ, 4, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x44, Slots3LZ, 6, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x45, Slots3LZ, 9, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x46, Slots3LZ, 7, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x47, Slots3LZ, 10, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x48, Slots3LZ, 12, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x49, Slots3LZ, 15, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x4a, Slots3LZ, 13, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x4b, Slots3LZ, 16, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x4c, Slots3LZ, 18, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x4d, Slots3LZ, 21, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x4e, Slots3LZ, 19, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x4f, Slots3LZ, 22, 1);
    
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x50, Slots3LZ, 24, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x51, Slots3LZ, 27, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x52, Slots3LZ, 25, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x53, Slots3LZ, 28, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x54, Slots3LZ, 26, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x55, Slots3LZ, 29, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x56, Slots3LZ, 30, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x57, Slots3LZ, 33, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x58, Slots3LZ, 31, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x59, Slots3LZ, 34, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x5a, Slots3LZ, 32, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x5b, Slots3LZ, 35, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x5c, Slots3LZ, 42, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x5d, Slots3LZ, 45, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x5e, Slots3LZ, 43, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x5f, Slots3LZ, 46, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x60, Slots3LZ, 44, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x61, Slots3LZ, 47, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x62, Slots3LZ, 54, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x63, Slots3LZ, 57, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x64, Slots3LZ, 55, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x65, Slots3LZ, 58, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x66, Slots3LZ, 56, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x67, Slots3LZ, 59, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x68, Slots3LZ, 66, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x69, Slots3LZ, 69, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x6a, Slots3LZ, 67, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x6b, Slots3LZ, 70, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x6c, Slots3LZ, 68, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x6d, Slots3LZ, 71, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x6e, Slots3LZ, 72, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x6f, Slots3LZ, 75, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x70, Slots3LZ, 73, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x71, Slots3LZ, 76, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x72, Slots3LZ, 74, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x73, Slots3LZ, 77, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x74, Slots3LZ, 78, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x75, Slots3LZ, 81, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x76, Slots3LZ, 79, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x77, Slots3LZ, 82, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x78, Slots3LZ, 80, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x79, Slots3LZ, 83, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x7a, Slots3LZ, 84, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x7b, Slots3LZ, 87, 1);

    // LD_HL(mSlots1LZ);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, Slots1LZ);

    // LD_HL(mSlots2LZ);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x25);
    // CALL(aDecompress);
    v_SlotMachine_InitGFX_LoadSlotTiles(vram->vTiles2 + LEN_2BPP_TILE * 0x25);

    // LD_HL(mSlotsTilemap);
    // decoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * 12);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * 12, SlotsTilemap);

    // LD_HL(rLCDC);
    // SET_hl(rLCDC_SPRITE_SIZE);  // 8x16
    gb_write(rLCDC, gb_read(rLCDC) | (1 << rLCDC_SPRITE_SIZE));
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // LD_HL(wSlots);
    // LD_BC(wSlotsEnd - wSlots);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(&gSlotData, sizeof(gSlotData), 0x0);
    // CALL(aSlots_InitReelTiles);
    Slots_InitReelTiles();
    // CALL(aSlots_GetPals);
    Slots_GetPals();
    // LD_A(SPRITE_ANIM_DICT_SLOTS);
    // LD_HL(wSpriteAnimDict);
    // LD_hli_A;
    wram->wSpriteAnimDict[0x0] = SPRITE_ANIM_DICT_SLOTS;
    // LD_hl(0x40);
    wram->wSpriteAnimDict[0x1] = 0x40;
    // XOR_A_A;  // SLOTS_INIT
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = SLOTS_INIT;
    // LD_A(SLOTS_NO_BIAS);
    // LD_addr_A(wSlotBias);
    gSlotData.slotBias = SLOTS_NO_BIAS;
    // LD_DE(MUSIC_GAME_CORNER);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_GAME_CORNER);
    // XOR_A_A;
    // LD_addr_A(wKeepSevenBiasChance);  // 87.5% chance
    wram->wKeepSevenBiasChance = FALSE;
    // CALL(aRandom);
    // AND_A(0b00101010);
    // RET_NZ ;
    if((Random_Conv() & 0b00101010) != 0)
        return;
    // LD_A(TRUE);
    // LD_addr_A(wKeepSevenBiasChance);  // 12.5% chance
    wram->wKeepSevenBiasChance = TRUE;
    // RET;
}

void v_SlotMachine(void){
    // LD_HL(wOptions);
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(av_SlotMachine_InitGFX);
    v_SlotMachine_InitGFX();
    // CALL(aDelayFrame);
    DelayFrame();

    bool done = false;
    do {
    // loop:
        // CALL(aSlotsLoop);
        done = SlotsLoop();
        // IF_NC goto loop;
    } while(!done);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_DE(SFX_QUIT_SLOTS);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_QUIT_SLOTS);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // FARCALL(aStubbedTrainerRankings_EndSlotsWinStreak);
    StubbedTrainerRankings_EndSlotsWinStreak();
    // LD_HL(wOptions);
    // RES_hl(NO_TEXT_SCROLL);
    bit_reset(wram->wOptions, NO_TEXT_SCROLL);
    // LD_HL(rLCDC);
    // RES_hl(rLCDC_SPRITE_SIZE);  // 8x8
    gb_write(rLCDC, gb_read(rLCDC) & (uint8_t)~(1 << rLCDC_SPRITE_SIZE));
    // RET;
}

void Slots_GetPals(void){
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // LD_DE((0b11100100 << 8) | 0b11100100);
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    // LD_DE((0b11000000 << 8) | 0b11100100);

// cgb:
    // CALL(aDmgToCgbObjPals);
    DmgToCgbObjPals_Conv(0b11100100, 0b11100100);
    // RET;
}

static void SlotsLoop_PrintCoinsAndPayout(void){
    // hlcoord(5, 1, wTilemap);
    // LD_DE(wCoins);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 4);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(5, 1, wram->wTilemap), &wram->wCoins, PRINTNUM_LEADINGZEROS | 2, 4);
    // hlcoord(11, 1, wTilemap);
    // LD_DE(wPayout);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 4);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(11, 1, wram->wTilemap), &gSlotData.payout, PRINTNUM_LEADINGZEROS | 2, 4);
    // RET;
}

static void SlotsLoop_Stubbed_AlternateMatchingSevensPalette(void){
//  dummied out
    // RET;
    return;
    // LD_A_addr(wReel1ReelAction);
    // AND_A_A;
    // RET_NZ ;
    // LD_A_addr(wReel2ReelAction);
    // AND_A_A;
    // RET_NZ ;
    // LD_A_addr(wFirstTwoReelsMatchingSevens);
    // AND_A_A;
    // IF_NZ goto matching_sevens;
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    // RET;

// matching_sevens:
    // LD_A_addr(wTextDelayFrames);
    // AND_A(0x7);
    // RET_NZ ;
    // LDH_A_addr(rBGP);
    // XOR_A(0b00001100);  // alternates two palettes
    // CALL(aDmgToCgbBGPals);
    // RET;
}

bool SlotsLoop(void){
    // LD_A_addr(wJumptableIndex);
    // BIT_A(SLOTS_END_LOOP_F);
    // IF_NZ goto stop;
    if(bit_test(wram->wJumptableIndex, SLOTS_END_LOOP_F)) {
    // stop:
        // SCF;
        // RET;
        return true;
    }
    // CALL(aSlotsJumptable);
    SlotsJumptable();
    // CALL(aSlots_SpinReels);
    Slots_SpinReels();
    // XOR_A_A;
    // LD_addr_A(wCurSpriteOAMAddr);
    wram->wCurSpriteOAMAddr = 0x0;
    // CALLFAR(aDoNextFrameForFirst16Sprites);
    DoNextFrameForFirst16Sprites_Conv();
    // CALL(aSlotsLoop_PrintCoinsAndPayout);
    SlotsLoop_PrintCoinsAndPayout();
    // CALL(aSlotsLoop_Stubbed_AlternateMatchingSevensPalette);
    SlotsLoop_Stubbed_AlternateMatchingSevensPalette();
    // CALL(aDelayFrame);
    DelayFrame();
    // AND_A_A;
    // RET;
    return false;
}

void DebugPrintSlotBias(void){
//  //  unreferenced
    LD_A_addr(wSlotBias);
    ADD_A(0);
    DAA;
    LD_E_A;
    AND_A(0xf);
    ADD_A(0xf6);
    hlcoord(1, 0, wTilemap);
    LD_hl_A;
    LD_A_E;
    SWAP_A;
    AND_A(0xf);
    ADD_A(0xf6);
    hlcoord(0, 0, wTilemap);
    LD_hl_A;
    RET;

}

void AnimateSlotReelIcons(void){
//  //  unreferenced
//  This animation was present in pokegold-spaceworld.
    LD_HL(wUnusedSlotReelIconDelay);
    LD_A_hl;
    INC_hl;
    AND_A(0x7);
    RET_NZ ;
    LD_HL(wVirtualOAMSprite16TileID);
    LD_C(NUM_SPRITE_OAM_STRUCTS - 16);

loop:
    LD_A_hl;
    XOR_A(0x20);  // alternate between $00-$1f and $20-$3f
    LD_hli_A;  // tile id
    for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
    INC_HL;
    }
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void SlotsJumptable(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']

// Jumptable:
    switch(wram->wJumptableIndex) {
        case SLOTS_INIT:                    return SlotsAction_Init();  // 00
        case SLOTS_BET_AND_START:           return SlotsAction_BetAndStart();  // 01
        case SLOTS_WAIT_START:              return SlotsAction_WaitStart();  // 02
        case SLOTS_WAIT_REEL1:              return SlotsAction_WaitReel1();  // 03
        case SLOTS_WAIT_STOP_REEL1:         return SlotsAction_WaitStopReel1();  // 04
        case SLOTS_WAIT_REEL2:              return SlotsAction_WaitReel2();  // 05
        case SLOTS_WAIT_STOP_REEL2:         return SlotsAction_WaitStopReel2();  // 06
        case SLOTS_WAIT_REEL3:              return SlotsAction_WaitReel3();  // 07
        case SLOTS_WAIT_STOP_REEL3:         return SlotsAction_WaitStopReel3();  // 08
        case SLOTS_NEXT_09:                 return SlotsAction_Next();  // 09
        case SLOTS_NEXT_0A:                 return SlotsAction_Next();  // 0a
        case SLOTS_NEXT_0B:                 return SlotsAction_Next();  // 0b
        case SLOTS_FLASH_IF_WIN:            return SlotsAction_FlashIfWin();  // 0c
        case SLOTS_FLASH_SCREEN:            return SlotsAction_FlashScreen();  // 0d
        case SLOTS_GIVE_EARNED_COINS:       return SlotsAction_GiveEarnedCoins();  // 0e
        case SLOTS_PAYOUT_TEXT_AND_ANIM:    return SlotsAction_PayoutTextAndAnim();  // 0f
        case SLOTS_PAYOUT_ANIM:             return SlotsAction_PayoutAnim();  // 10
        case SLOTS_RESTART_OF_QUIT:         return SlotsAction_RestartOrQuit();  // 11
        case SLOTS_QUIT:                    return SlotsAction_Quit();  // 12
    }
}

void SlotsAction_Next(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    // RET;
    wram->wJumptableIndex++;
}

void SlotsAction_Init(void){
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // XOR_A_A;
    // LD_addr_A(wFirstTwoReelsMatching);
    gSlotData.firstTwoReelsMatching = FALSE;
    // LD_addr_A(wFirstTwoReelsMatchingSevens);
    gSlotData.firstTwoReelsMatchingSevens = FALSE;
    // LD_A(SLOTS_NO_MATCH);
    // LD_addr_A(wSlotMatched);
    gSlotData.slotMatched = SLOTS_NO_MATCH;
    // RET;
}

void SlotsAction_BetAndStart(void){
    // CALL(aSlots_AskBet);
    bool cancel = Slots_AskBet();
    // IF_NC goto proceed;
    if(cancel) {
        // LD_A(SLOTS_QUIT);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = SLOTS_QUIT;
        // RET;
        return;
    }

// proceed:
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // CALL(aSlots_IlluminateBetLights);
    Slots_IlluminateBetLights();
    // CALL(aSlots_InitBias);
    Slots_InitBias();
    // LD_A(32);
    // LD_addr_A(wSlotsDelay);
    wram->wSlotsDelay = 32;
    // LD_A(REEL_ACTION_NORMAL_RATE);
    // LD_addr_A(wReel1ReelAction);
    gSlotData.reel1.reelAction = REEL_ACTION_NORMAL_RATE;
    // LD_addr_A(wReel2ReelAction);
    gSlotData.reel2.reelAction = REEL_ACTION_NORMAL_RATE;
    // LD_addr_A(wReel3ReelAction);
    gSlotData.reel3.reelAction = REEL_ACTION_NORMAL_RATE;
    // LD_A(4);
    // LD_addr_A(wReel1ManipCounter);
    gSlotData.reel1.manipCounter = 4;
    // LD_addr_A(wReel2ManipCounter);
    gSlotData.reel2.manipCounter = 4;
    // LD_addr_A(wReel3ManipCounter);
    gSlotData.reel3.manipCounter = 4;
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_A(SFX_SLOT_MACHINE_START);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_SLOT_MACHINE_START);
    // RET;
}

void SlotsAction_WaitStart(void){
    // LD_HL(wSlotsDelay);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto proceed;
    if(wram->wSlotsDelay != 0) {
        // DEC_hl;
        wram->wSlotsDelay--;
        // RET;
        return;
    }

// proceed:
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // XOR_A_A;
    // LDH_addr_A(hJoypadSum);
    hram->hJoypadSum = 0x0;
    // RET;
}

void SlotsAction_WaitReel1(void){
    // LD_HL(hJoypadSum);
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // RET_Z ;
    if((hram->hJoypadSum & A_BUTTON) == 0)
        return;
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // CALL(aSlots_StopReel1);
    // LD_addr_A(wReel1ReelAction);
    gSlotData.reel1.reelAction = Slots_StopReel1();
    return SlotsAction_WaitStopReel1();
}

void SlotsAction_WaitStopReel1(void){
    // LD_A_addr(wReel1ReelAction);
    // CP_A(REEL_ACTION_DO_NOTHING);
    // RET_NZ ;
    if(gSlotData.reel1.reelAction != REEL_ACTION_DO_NOTHING)
        return;
    // LD_A(SFX_STOP_SLOT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_STOP_SLOT);
    // LD_BC(wReel1);
    // LD_DE(wReel1Stopped);
    // CALL(aSlots_LoadReelState);
    Slots_LoadReelState(gSlotData.reel1Stopped, &gSlotData.reel1);
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // XOR_A_A;
    // LDH_addr_A(hJoypadSum);
    hram->hJoypadSum = 0x0;
    return SlotsAction_WaitReel2();
}

void SlotsAction_WaitReel2(void){
    // LD_HL(hJoypadSum);
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // RET_Z ;
    if((hram->hJoypadSum & A_BUTTON) == 0)
        return;
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // CALL(aSlots_StopReel2);
    // LD_addr_A(wReel2ReelAction);
    gSlotData.reel2.reelAction = Slots_StopReel2();
    return SlotsAction_WaitStopReel2();
}

void SlotsAction_WaitStopReel2(void){
    // LD_A_addr(wReel2ReelAction);
    // CP_A(REEL_ACTION_DO_NOTHING);
    // RET_NZ ;
    if(gSlotData.reel2.reelAction != REEL_ACTION_DO_NOTHING)
        return;
    // LD_A(SFX_STOP_SLOT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_STOP_SLOT);
    // LD_BC(wReel2);
    // LD_DE(wReel2Stopped);
    // CALL(aSlots_LoadReelState);
    Slots_LoadReelState(gSlotData.reel2Stopped, &gSlotData.reel2);
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // XOR_A_A;
    // LDH_addr_A(hJoypadSum);
    hram->hJoypadSum = 0x0;
    return SlotsAction_WaitReel3();
}

void SlotsAction_WaitReel3(void){
    // LD_HL(hJoypadSum);
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // RET_Z ;
    if((hram->hJoypadSum & A_BUTTON) == 0)
        return;
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // CALL(aSlots_StopReel3);
    // LD_addr_A(wReel3ReelAction);
    gSlotData.reel3.reelAction = Slots_StopReel3();
    return SlotsAction_WaitStopReel3();
}

void SlotsAction_WaitStopReel3(void){
    // LD_A_addr(wReel3ReelAction);
    // CP_A(REEL_ACTION_DO_NOTHING);
    // RET_NZ ;
    if(gSlotData.reel3.reelAction != REEL_ACTION_DO_NOTHING)
        return;
    // LD_A(SFX_STOP_SLOT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_STOP_SLOT);
    // LD_BC(wReel3);
    // LD_DE(wReel3Stopped);
    // CALL(aSlots_LoadReelState);
    Slots_LoadReelState(gSlotData.reel3Stopped, &gSlotData.reel3);
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // XOR_A_A;
    // LDH_addr_A(hJoypadSum);
    hram->hJoypadSum = 0x0;
    // RET;
}

void SlotsAction_FlashIfWin(void){
    // LD_A_addr(wSlotMatched);
    // CP_A(SLOTS_NO_MATCH);
    // IF_NZ goto GotIt;
    if(gSlotData.slotMatched == SLOTS_NO_MATCH) {
        // CALL(aSlotsAction_Next);
        SlotsAction_Next();
        // CALL(aSlotsAction_Next);
        SlotsAction_Next();
        // RET;
        return;
    }

// GotIt:
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // LD_A(16);
    // LD_addr_A(wSlotsDelay);
    wram->wSlotsDelay = 16;
    return SlotsAction_FlashScreen();
}

void SlotsAction_FlashScreen(void){
    // LD_HL(wSlotsDelay);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto done;
    if(wram->wSlotsDelay != 0) {
        // DEC_hl;
        uint8_t delay = wram->wSlotsDelay--;
        // SRL_A;
        // RET_Z ;
        if((delay >> 1) == 0)
            return;

        // LDH_A_addr(rOBP0);
        // XOR_A(0xff);
        uint8_t a = gb_read(rOBP0) ^ 0xff;
        // LD_E_A;
        // LD_D_A;
        // CALL(aDmgToCgbObjPals);
        DmgToCgbObjPals_Conv(a, a);
        // RET;
        return;
    }

// done:
    // CALL(aSlots_GetPals);
    Slots_GetPals();
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // RET;
}

void SlotsAction_GiveEarnedCoins(void){
    // XOR_A_A;
    // LD_addr_A(wFirstTwoReelsMatching);
    gSlotData.firstTwoReelsMatching = FALSE;
    // LD_addr_A(wFirstTwoReelsMatchingSevens);
    gSlotData.firstTwoReelsMatchingSevens = FALSE;
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // CALL(aSlots_GetPayout);
    Slots_GetPayout();
    // XOR_A_A;
    // LD_addr_A(wSlotsDelay);
    wram->wSlotsDelay = 0;
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    // RET;

}

void SlotsAction_PayoutTextAndAnim(void){
    // CALL(aSlots_PayoutText);
    Slots_PayoutText();
    // CALL(aSlotsAction_Next);
    SlotsAction_Next();
    return SlotsAction_PayoutAnim();
}

void SlotsAction_PayoutAnim(void){
    // LD_HL(wSlotsDelay);
    // LD_A_hl;
    // INC_hl;
    uint8_t delay = wram->wSlotsDelay++;
    // AND_A(0x1);
    // RET_Z ;
    if((delay & 0x1) == 0)
        return;
    // LD_HL(wPayout);
    // LD_A_hli;
    // LD_D_A;
    // OR_A_hl;
    // IF_Z goto done;
    uint16_t de = ReverseEndian16(gSlotData.payout);
    if(de == 0) {
    // done:
        // CALL(aSlotsAction_Next);
        SlotsAction_Next();
        // RET;
        return;
    }
    // LD_E_hl;
    // DEC_DE;
    // LD_hl_E;
    // DEC_HL;
    // LD_hl_D;
    gSlotData.payout = ReverseEndian16(--de);
    // LD_HL(wCoins);
    // LD_D_hl;
    // INC_HL;
    // LD_E_hl;
    uint16_t coins = ReverseEndian16(wram->wCoins);
    // CALL(aSlots_CheckCoinCaseFull);
    // IF_C goto okay;
    if(!Slots_CheckCoinCaseFull(coins)) {
        // INC_DE;
        coins++;
    }

// okay:
    // LD_hl_E;
    // DEC_HL;
    // LD_hl_D;
    wram->wCoins = ReverseEndian16(coins);
    // LD_A_addr(wSlotsDelay);
    // AND_A(0x7);
    // RET_Z ;  // ret nz would be more appropriate
#if BUGFIX_SLOT_DELAY_SFX
    if((wram->wSlotsDelay & 0x7) != 0)
#else
    if((wram->wSlotsDelay & 0x7) == 0)
#endif
        return;
    // LD_DE(SFX_GET_COIN_FROM_SLOTS);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_GET_COIN_FROM_SLOTS);
    // RET;
}

void SlotsAction_RestartOrQuit(void){
    // CALL(aSlots_DeilluminateBetLights);
    Slots_DeilluminateBetLights();
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor_Conv();
    // CALL(aSlots_AskPlayAgain);
    // IF_C goto exit_slots;
    if(Slots_AskPlayAgain()) {
    // exit_slots:
        // LD_A(SLOTS_QUIT);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = SLOTS_QUIT;
        // RET;
        return;
    }
    // LD_A(SLOTS_INIT);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = SLOTS_INIT;
    // RET;
}

void SlotsAction_Quit(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(SLOTS_END_LOOP_F);
    // RET;
    bit_set(wram->wJumptableIndex, SLOTS_END_LOOP_F);
}

void Slots_LoadReelState(uint8_t* de, struct SlotReelData* bc){
    // PUSH_DE;
    // CALL(aSlots_GetCurrentReelState);
    const uint8_t* hl = Slots_GetCurrentReelState(bc);
    // POP_DE;
    // LD_A_hli;
    // LD_de_A;
    de[0] = hl[0];
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    de[1] = hl[1];
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    de[2] = hl[2];
    // RET;
}

bool Slots_CheckCoinCaseFull(uint16_t de){
    // LD_A_D;
    // CP_A(HIGH(MAX_COINS));
    // IF_C goto not_full;
    // LD_A_E;
    // CP_A(LOW(MAX_COINS));
    // IF_C goto not_full;
    // SCF;
    // RET;

// not_full:
    // AND_A_A;
    // RET;
    return de >= MAX_COINS;
}

const uint8_t* Slots_GetCurrentReelState(struct SlotReelData* bc){
    // LD_HL(REEL_POSITION);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t pos = bc->position;
    // AND_A_A;
    // IF_NZ goto okay;
    if(pos == 0) {
        // LD_A(0xf);
        pos = 0xf;
    }

// okay:
    // DEC_A;
    // AND_A(0xf);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(REEL_TILEMAP_ADDR);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_DE;
    // RET;
    return bc->tilemapAddr + ((pos - 1) & 0xf);
}

uint8_t Slots_StopReel1(void){
//  Always set the REEL_ACTION_STOP_REEL1 action.
    // LD_A(REEL_ACTION_STOP_REEL1);
    // RET;
    return REEL_ACTION_STOP_REEL1;
}

static bool Slots_StopReel2_CheckReel1ForASeven(void){
    // LD_A_addr(wReel1Stopped);
    // AND_A_A;
    // RET_Z ;
    // LD_A_addr(wReel1Stopped + 1);
    // AND_A_A;
    // RET_Z ;
    // LD_A_addr(wReel1Stopped + 2);
    // AND_A_A;
    // RET;
    return gSlotData.reel1Stopped[0] == 0
        || gSlotData.reel1Stopped[1] == 0
        || gSlotData.reel1Stopped[2] == 0;
}

//  As long as, the following three meet, there's a 31.25% chance
//  to set action REEL_ACTION_SET_UP_REEL2_SKIP_TO_7:
//  - Bet is >= 2 coins
//  - There's a 7 symbol visible in reel #1
//  - Current spin isn't biased or is biased towards SEVEN
//  In any other case, REEL_ACTION_STOP_REEL2 is set.
uint8_t Slots_StopReel2(void){
    // LD_A_addr(wSlotBet);
    // CP_A(0x2);
    // IF_C goto dont_jump;
    // LD_A_addr(wSlotBias);
    // AND_A_A;
    // IF_Z goto skip;
    // CP_A(SLOTS_NO_BIAS);
    // IF_NZ goto dont_jump;
    if(gSlotData.slotBet >= 0x2 && (gSlotData.slotBias == 0 || gSlotData.slotBias == SLOTS_NO_BIAS)) {
    // skip:
        // CALL(aSlots_StopReel2_CheckReel1ForASeven);
        // IF_NZ goto dont_jump;
        // CALL(aRandom);
        // CP_A(31 percent + 1);
        // IF_NC goto dont_jump;
        if(Slots_StopReel2_CheckReel1ForASeven() && Random_Conv() < 31 percent + 1) {
            // LD_A(REEL_ACTION_SET_UP_REEL2_SKIP_TO_7);
            // RET;
            return REEL_ACTION_SET_UP_REEL2_SKIP_TO_7;
        }
    }

// dont_jump:
    // LD_A(REEL_ACTION_STOP_REEL2);
    // RET;
    return REEL_ACTION_STOP_REEL2;
}

//  If no matching SEVEN symbols in reels #1 and #2:
//  - REEL_ACTION_STOP_REEL3, 100%
//
//  If matching SEVEN symbols and NO bias to SEVEN:
//  - REEL_ACTION_STOP_REEL3, 37.5%
//  - REEL_ACTION_START_SLOW_ADVANCE_REEL3, 31.3%
//  - REEL_ACTION_INIT_GOLEM, 31.3%
//  - REEL_ACTION_INIT_CHANSEY, 0%
//
//  If matching SEVEN symbols and bias to SEVEN:
//  - REEL_ACTION_STOP_REEL3, 29.7%
//  - REEL_ACTION_START_SLOW_ADVANCE_REEL3, 23.4%
//  - REEL_ACTION_INIT_GOLEM, 23.4%
//  - REEL_ACTION_INIT_CHANSEY, 23.4%
uint8_t Slots_StopReel3(void){
    // LD_A_addr(wFirstTwoReelsMatching);
    // AND_A_A;
    // IF_Z goto stop;
    // LD_A_addr(wFirstTwoReelsMatchingSevens);
    // AND_A_A;
    // IF_Z goto stop;
    if(gSlotData.firstTwoReelsMatching == FALSE || gSlotData.firstTwoReelsMatchingSevens == FALSE)
        return REEL_ACTION_STOP_REEL3;
    // LD_A_addr(wSlotBias);
    // AND_A_A;
    // IF_NZ goto biased;
    if(gSlotData.slotBias == 0) {
        // CALL(aRandom);
        uint8_t a = Random_Conv();
        // CP_A(71 percent - 1);
        // IF_NC goto stop;
        if(a >= 71 percent - 1)
            return REEL_ACTION_STOP_REEL3;
        // CP_A(47 percent + 1);
        // IF_NC goto slow_advance;
        else if(a >= 47 percent + 1)
            return REEL_ACTION_START_SLOW_ADVANCE_REEL3;
        // CP_A(24 percent - 1);
        // IF_NC goto golem;
        else if(a >= 24 percent - 1)
            return REEL_ACTION_INIT_GOLEM;
        // LD_A(REEL_ACTION_INIT_CHANSEY);
        // RET;
        else
            return REEL_ACTION_INIT_CHANSEY;
    }
    else {
    // biased:
        // CALL(aRandom);
        uint8_t a = Random_Conv();
        // CP_A(63 percent);
        // IF_NC goto stop;
        if(a >= 63 percent)
            return REEL_ACTION_STOP_REEL3;
        // CP_A(31 percent + 1);
        // IF_NC goto slow_advance;
        else if(a >= 31 percent + 1)
            return REEL_ACTION_START_SLOW_ADVANCE_REEL3;

        else {
        // golem:
            // LD_A(REEL_ACTION_INIT_GOLEM);
            // RET;
            return REEL_ACTION_INIT_GOLEM;
        }
    }

// slow_advance:
    // LD_A(REEL_ACTION_START_SLOW_ADVANCE_REEL3);
    // RET;

// stop:
    // LD_A(REEL_ACTION_STOP_REEL3);
    // RET;
}

static void Slots_InitReelTiles_OAM(struct SlotReelData* bc){
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // LD_hl(REEL_ACTION_DO_NOTHING);
    bc->reelAction = REEL_ACTION_DO_NOTHING;
    // LD_HL(REEL_POSITION);
    // ADD_HL_BC;
    // LD_hl(REEL_SIZE - 1);
    bc->position = REEL_SIZE - 1;
    // LD_HL(REEL_SPIN_DISTANCE);
    // ADD_HL_BC;
    // LD_hl(REEL_ACTION_DO_NOTHING);
    bc->spinDistance = REEL_ACTION_DO_NOTHING;
    // CALL(aSlots_UpdateReelPositionAndOAM);
    Slots_UpdateReelPositionAndOAM(bc);
    // RET;
}

void Slots_InitReelTiles(void){
    // LD_BC(wReel1);
    // LD_HL(REEL_OAM_ADDR);
    // ADD_HL_BC;
    // LD_DE(wVirtualOAMSprite16);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gSlotData.reel1.oamAddr = wram->wVirtualOAMSprite + 16;
    // LD_HL(REEL_TILEMAP_ADDR);
    // ADD_HL_BC;
    // LD_DE(mReel1Tilemap);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gSlotData.reel1.tilemapAddr = Reel1Tilemap;
    // LD_HL(REEL_X_COORD);
    // ADD_HL_BC;
    // LD_hl(6 * 8);
    gSlotData.reel1.xCoord = 6 * 8;
    // CALL(aSlots_InitReelTiles_OAM);
    Slots_InitReelTiles_OAM(&gSlotData.reel1);

    // LD_BC(wReel2);
    // LD_HL(REEL_OAM_ADDR);
    // ADD_HL_BC;
    // LD_DE(wVirtualOAMSprite24);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gSlotData.reel2.oamAddr = wram->wVirtualOAMSprite + 24;
    // LD_HL(REEL_TILEMAP_ADDR);
    // ADD_HL_BC;
    // LD_DE(mReel2Tilemap);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gSlotData.reel2.tilemapAddr = Reel2Tilemap;
    // LD_HL(REEL_X_COORD);
    // ADD_HL_BC;
    // LD_hl(10 * 8);
    gSlotData.reel2.xCoord = 10 * 8;
    // CALL(aSlots_InitReelTiles_OAM);
    Slots_InitReelTiles_OAM(&gSlotData.reel2);

    // LD_BC(wReel3);
    // LD_HL(REEL_OAM_ADDR);
    // ADD_HL_BC;
    // LD_DE(wVirtualOAMSprite32);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gSlotData.reel3.oamAddr = wram->wVirtualOAMSprite + 32;
    // LD_HL(REEL_TILEMAP_ADDR);
    // ADD_HL_BC;
    // LD_DE(mReel3Tilemap);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gSlotData.reel3.tilemapAddr = Reel3Tilemap;
    // LD_HL(REEL_X_COORD);
    // ADD_HL_BC;
    // LD_hl(14 * 8);
    gSlotData.reel3.xCoord = 14 * 8;
    // CALL(aSlots_InitReelTiles_OAM);
    Slots_InitReelTiles_OAM(&gSlotData.reel3);
    // RET;
}

static void Slots_SpinReels_SpinReel(struct SlotReelData* bc) {
    // LD_HL(REEL_SPIN_DISTANCE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(0xf);
    // IF_NZ goto skip;
    if((bc->spinDistance & 0xf) == 0) {
        // CALL(aReelActionJumptable);
        ReelActionJumptable(bc);
    }

// skip:
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(bc->spinRate == 0)
        return;
    // LD_D_A;
    uint8_t d = bc->spinRate;
    // LD_HL(REEL_SPIN_DISTANCE);
    // ADD_HL_BC;
    // ADD_A_hl;
    uint8_t dist = bc->spinDistance + d;
    // LD_hl_A;
    bc->spinDistance = dist; 
    // AND_A(0xf);
    // JR_Z (mSlots_UpdateReelPositionAndOAM);
    if((dist & 0xf) == 0)
        return Slots_UpdateReelPositionAndOAM(bc);
    // LD_HL(REEL_OAM_ADDR);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    struct SpriteOAM* hl = bc->oamAddr;
    // LD_E(0x8);
    uint8_t e = 0x8;

    do {
    // loop:
        // LD_A_hl;
        // ADD_A_D;
        // LD_hli_A;
        hl->yCoord += d;
        // INC_HL;
        // INC_HL;
        // INC_HL;
        hl++;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // RET;
}

void Slots_SpinReels(void){
    // LD_BC(wReel1);
    // CALL(aSlots_SpinReels_SpinReel);
    Slots_SpinReels_SpinReel(&gSlotData.reel1);
    // LD_BC(wReel2);
    // CALL(aSlots_SpinReels_SpinReel);
    Slots_SpinReels_SpinReel(&gSlotData.reel2);
    // LD_BC(wReel3);
    // CALL(aSlots_SpinReels_SpinReel);
    Slots_SpinReels_SpinReel(&gSlotData.reel3);
    // RET;
}

static void Slots_UpdateReelPositionAndOAM_LoadOAM(struct SlotReelData* bc, const uint8_t* de){
    // LD_HL(REEL_OAM_ADDR);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    struct SpriteOAM* hl = bc->oamAddr;
    uint8_t yCoord = gSlotData.curReelYCoord;
    uint8_t xCoord = gSlotData.curReelXCoord;

    do {
    // loop:
        // LD_A_addr(wCurReelYCoord);
        // LD_hli_A;  // y
        hl->yCoord = yCoord;
        // LD_A_addr(wCurReelXCoord);
        // LD_hli_A;  // x
        hl->xCoord = xCoord;
        // LD_A_de;
        // LD_hli_A;  // tile id
        hl->tileID = *de;
        // SRL_A;
        // SRL_A;
        // SET_A(OAM_PRIORITY);
        // LD_hli_A;  // attributes
        hl->attributes = (*de >> 2) | (1 << OAM_PRIORITY);

        hl++;

        // LD_A_addr(wCurReelYCoord);
        // LD_hli_A;  // y
        hl->yCoord = yCoord;
        // LD_A_addr(wCurReelXCoord);
        // ADD_A(1 * TILE_WIDTH);
        // LD_hli_A;  // x
        hl->xCoord = xCoord + TILE_WIDTH;
        // LD_A_de;
        // INC_A;
        // INC_A;
        // LD_hli_A;  // tile id
        hl->tileID = (*de) + 2;
        // SRL_A;
        // SRL_A;
        // SET_A(OAM_PRIORITY);
        // LD_hli_A;  // attributes
        hl->attributes = (((*de) + 2) >> 2) | (1 << OAM_PRIORITY);
        // INC_DE;
        hl++;
        de++;
        // LD_A_addr(wCurReelYCoord);
        // SUB_A(2 * TILE_WIDTH);
        // LD_addr_A(wCurReelYCoord);
        yCoord -= 2 * TILE_WIDTH;
        // CP_A(2 * TILE_WIDTH);
        // IF_NZ goto loop;
    } while(yCoord != 2 * TILE_WIDTH);
    // RET;
}

void Slots_UpdateReelPositionAndOAM(struct SlotReelData* bc){
    // LD_HL(REEL_X_COORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wCurReelXCoord);
    gSlotData.curReelXCoord = bc->xCoord;
    // LD_A(10 * 8);
    // LD_addr_A(wCurReelYCoord);
    gSlotData.curReelYCoord = 10 * TILE_WIDTH;
    // LD_HL(REEL_POSITION);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(REEL_TILEMAP_ADDR);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    const uint8_t* tilemap = bc->tilemapAddr + bc->position;
    // CALL(aSlots_UpdateReelPositionAndOAM_LoadOAM);
    Slots_UpdateReelPositionAndOAM_LoadOAM(bc, tilemap);
    // LD_HL(REEL_POSITION);
    // ADD_HL_BC;
    // LD_A_hl;
    // INC_A;
    // AND_A(0xf);
    // CP_A(REEL_SIZE);
    // IF_NZ goto load;
    if(((bc->position + 1) & 0xf) == REEL_SIZE) {
        // XOR_A_A;
        bc->position = 0;
    }
    else {
    // load:
        // LD_hl_A;
        bc->position = (bc->position + 1) & 0xf;
    }
    // RET;
}

void GetUnknownSlotReelData(void){
//  //  unreferenced
//  Used to get OAM attribute values for slot reels?
//  (final Slots_UpdateReelPositionAndOAM above reuses tile IDs as OAM palettes)
    PUSH_HL;
    SRL_A;
    SRL_A;
    ADD_A(LOW(aGetUnknownSlotReelData_data));
    LD_L_A;
    LD_A(0);
    ADC_A(HIGH(aGetUnknownSlotReelData_data));
    LD_H_A;
    LD_A_hl;
    POP_HL;
    RET;


data:
    //table_width ['1', 'GetUnknownSlotReelData.data']
    //db ['0'];  // SLOTS_SEVEN
    //db ['1'];  // SLOTS_POKEBALL
    //db ['2'];  // SLOTS_CHERRY
    //db ['3'];  // SLOTS_PIKACHU
    //db ['4'];  // SLOTS_SQUIRTLE
    //db ['5'];  // SLOTS_STARYU
    //assert_table_length ['NUM_SLOT_REELS']
}

void ReelActionJumptable(struct SlotReelData* bc){
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mReelActionJumptable_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;

    switch(bc->reelAction) {
    // Jumptable:
        case REEL_ACTION_DO_NOTHING:                return ReelAction_DoNothing();  // 00
        case REEL_ACTION_STOP_REEL_IGNORE_JOYPAD:   return ReelAction_StopReelIgnoreJoypad(bc);  // 01
        case REEL_ACTION_QUADRUPLE_RATE:            return ReelAction_QuadrupleRate(bc);  // 02
        case REEL_ACTION_DOUBLE_RATE:               return ReelAction_DoubleRate(bc);  // 03
        case REEL_ACTION_NORMAL_RATE:               return ReelAction_NormalRate(bc);  // 04
        case REEL_ACTION_HALF_RATE:                 return ReelAction_HalfRate(bc);  // 05
        case REEL_ACTION_QUARTER_RATE:              return ReelAction_QuarterRate(bc);  // 06
        case REEL_ACTION_STOP_REEL1:                return ReelAction_StopReel1(bc);  // 07
        case REEL_ACTION_STOP_REEL2:                return ReelAction_StopReel2(bc);  // 08
        case REEL_ACTION_STOP_REEL3:                return ReelAction_StopReel3(bc);  // 09
        case REEL_ACTION_SET_UP_REEL2_SKIP_TO_7:    return ReelAction_SetUpReel2SkipTo7(bc);  // 0a
        case REEL_ACTION_WAIT_REEL2_SKIP_TO_7:      return ReelAction_WaitReel2SkipTo7(bc);  // 0b
        case REEL_ACTION_FAST_SPIN_REEL2_UNTIL_LINED_UP_7S: return ReelAction_FastSpinReel2UntilLinedUp7s(bc);  // 0c
        case REEL_ACTION_UNUSED:                    return ReelAction_Unused(bc);  // 0d
        case REEL_ACTION_CHECK_DROP_REEL:           return ReelAction_CheckDropReel(bc);  // 0e
        case REEL_ACTION_WAIT_DROP_REEL:            return ReelAction_WaitDropReel(bc);  // 0f
        case REEL_ACTION_START_SLOW_ADVANCE_REEL3:  return ReelAction_StartSlowAdvanceReel3(bc);  // 10
        case REEL_ACTION_WAIT_SLOW_ADVANCE_REEL3:   return ReelAction_WaitSlowAdvanceReel3(bc);  // 11
        case REEL_ACTION_INIT_GOLEM:                return ReelAction_InitGolem(bc);  // 12
        case REEL_ACTION_WAIT_GOLEM:                return ReelAction_WaitGolem(bc);  // 13
        case REEL_ACTION_END_GOLEM:                 return ReelAction_EndGolem(bc);  // 14
        case REEL_ACTION_INIT_CHANSEY:              return ReelAction_InitChansey(bc);  // 15
        case REEL_ACTION_WAIT_CHANSEY:              return ReelAction_WaitChansey(bc);  // 16
        case REEL_ACTION_WAIT_EGG:                  return ReelAction_WaitEgg(bc);  // 17
        case REEL_ACTION_DROP_REEL:                 return ReelAction_DropReel(bc);  // 18
    }
}

void ReelAction_DoNothing(void){
    // RET;

}

void ReelAction_QuadrupleRate(struct SlotReelData* bc){
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(16);
    bc->spinRate = 16;
    // RET;
}

void ReelAction_DoubleRate(struct SlotReelData* bc){
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(8);
    bc->spinRate = 8;
    // RET;
}

void ReelAction_NormalRate(struct SlotReelData* bc){
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(4);
    bc->spinRate = 4;
    // RET;
}

void ReelAction_HalfRate(struct SlotReelData* bc){
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(2);
    bc->spinRate = 2;
    // RET;
}

void ReelAction_QuarterRate(struct SlotReelData* bc){
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(1);
    bc->spinRate = 1;
    // RET;
}

void Slots_StopReel(struct SlotReelData* bc){
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spinRate = 0;
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // LD_hl(REEL_ACTION_STOP_REEL_IGNORE_JOYPAD);
    bc->reelAction = REEL_ACTION_STOP_REEL_IGNORE_JOYPAD;
    // LD_HL(REEL_STOP_DELAY);
    // ADD_HL_BC;
    // LD_hl(3);
    bc->stopDelay = 3;
    return ReelAction_StopReelIgnoreJoypad(bc);
}

void ReelAction_StopReelIgnoreJoypad(struct SlotReelData* bc){
    // LD_HL(REEL_STOP_DELAY);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto EndReel;
    if(bc->stopDelay != 0) {
        // DEC_hl;
        bc->stopDelay--;
        // RET;
        return;
    }

// EndReel:
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // LD_A(REEL_ACTION_DO_NOTHING);
    // LD_hl_A;
    bc->reelAction = REEL_ACTION_DO_NOTHING;
    // RET;
}

static bool ReelAction_StopReel1_CheckForBias(struct SlotReelData* bc) {
    // CALL(aSlots_GetCurrentReelState);
    const uint8_t* hl = Slots_GetCurrentReelState(bc);
    // LD_A_addr(wSlotBias);
    // LD_E_A;
    // LD_A_hli;
    // CP_A_E;
    // RET_Z ;
    if(hl[0] == gSlotData.slotBias)
        return true;
    // LD_A_hli;
    // CP_A_E;
    // RET_Z ;
    if(hl[1] == gSlotData.slotBias)
        return true;
    // LD_A_hl;
    // CP_A_E;
    // RET;
    return hl[2] == gSlotData.slotBias;
}

//  If no bias: don't manipulate reel.
//  If bias: manipulate reel up to wReel1ManipCounter (i.e. 4) slots,
//  stoping early if the biased symbol shows up anywhere in reel #1,
//  even if the current bet won't allow lining it up.
void ReelAction_StopReel1(struct SlotReelData* bc){
    // LD_A_addr(wSlotBias);
    // CP_A(SLOTS_NO_BIAS);
    // IF_Z goto NoBias;
    if(gSlotData.slotBias != SLOTS_NO_BIAS) {
        // LD_HL(REEL_MANIP_COUNTER);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto NoBias;
        if(bc->manipCounter != 0) {
            // DEC_hl;
            bc->manipCounter--;
            // CALL(aReelAction_StopReel1_CheckForBias);
            // RET_NZ ;
            if(!ReelAction_StopReel1_CheckForBias(bc))
                return;
        }
    }

// NoBias:
    // CALL(aSlots_StopReel);
    Slots_StopReel(bc);
    // RET;
}

//  If no bias: don't manipulate reel.
//  If bias: manipulate reel up to wReel2ManipCounter (i.e. 4) slots,
//  stoping early if the biased symbol is lined up in the first two
//  reels, according to the lines that the current bet allows.
void ReelAction_StopReel2(struct SlotReelData* bc){
    // CALL(aSlots_CheckMatchedFirstTwoReels);
    // IF_NC goto nope;
    // LD_A_addr(wSlotBuildingMatch);
    // LD_HL(wSlotBias);
    // CP_A_hl;
    // IF_Z goto NoBias;
    if(!Slots_CheckMatchedFirstTwoReels(bc) || gSlotData.slotBuildingMatch != gSlotData.slotBias) {
    // nope:
        // LD_A_addr(wSlotBias);
        // CP_A(SLOTS_NO_BIAS);
        // IF_Z goto NoBias;
        // LD_HL(REEL_MANIP_COUNTER);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto NoBias;
        if(gSlotData.slotBias != 0 && bc->manipCounter != 0) {
            // DEC_hl;
            bc->manipCounter--;
            // RET;
            return;
        }
    }

// NoBias:
    // CALL(aSlots_StopReel);
    Slots_StopReel(bc);
    // RET;
}

//  Manipulate the reel up to wReel3ManipCounter (i.e. 4) slots,
//  stopping early if the bias symbol is lined up for a win.
//  If not biased to any symbols, stop as soon as nothing is lined up.
void ReelAction_StopReel3(struct SlotReelData* bc){
    // CALL(aSlots_CheckMatchedAllThreeReels);
    // IF_NC goto NoMatch;
    if(Slots_CheckMatchedAllThreeReels(bc) && gSlotData.slotMatched != gSlotData.slotBias) {
        // LD_HL(wSlotBias);
        // CP_A_hl;
        // IF_Z goto NoBias;
        if(gSlotData.slotMatched == gSlotData.slotBias)
            return Slots_StopReel(bc);
        // LD_HL(REEL_MANIP_COUNTER);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(bc->manipCounter != 0) {
            // DEC_hl;
            bc->manipCounter--;
            // RET;
            return;
        }
        return;
    }

// NoMatch:
    // LD_A_addr(wSlotBias);
    // CP_A(SLOTS_NO_BIAS);
    // IF_Z goto NoBias;
    // LD_HL(REEL_MANIP_COUNTER);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto NoBias;
    if(gSlotData.slotBias != SLOTS_NO_BIAS && bc->manipCounter != 0) {
        // DEC_hl;
        bc->manipCounter--;
        // RET;
        return;
    }

// NoBias:
    // CALL(aSlots_StopReel);
    // RET;
    return Slots_StopReel(bc);
}

//  Unique reel 2 action (see Slots_StopReel2)
//  Ensures that 7 symbols become lined up in the first two reels,
//  but more often than not, this is only a way to get our hopes up, as
//  it makes exciting reel #3 modes with no success hope more common.
void ReelAction_SetUpReel2SkipTo7(struct SlotReelData* bc){
    // CALL(aSlots_CheckMatchedFirstTwoReels);
    // IF_NC goto no_match;
    // LD_A_addr(wFirstTwoReelsMatchingSevens);
    // AND_A_A;
    // IF_Z goto no_match;
    if(Slots_CheckMatchedFirstTwoReels(bc) && gSlotData.firstTwoReelsMatchingSevens != FALSE) {
        // CALL(aSlots_StopReel);
        Slots_StopReel(bc);
        // RET;
        return;
    }

// no_match:
    // LD_A(SFX_STOP_SLOT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_STOP_SLOT);
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_WAIT_REEL2_SKIP_TO_7
    bc->reelAction = REEL_ACTION_WAIT_REEL2_SKIP_TO_7;
    // LD_HL(REEL_MANIP_DELAY);
    // ADD_HL_BC;
    // LD_hl(32);
    bc->manipDelay = 32;
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spinRate = 0;
    // RET;
}

void ReelAction_WaitReel2SkipTo7(struct SlotReelData* bc){
    // LD_HL(REEL_MANIP_DELAY);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto ready;
    if(bc->manipDelay != 0) {
        // DEC_hl;
        bc->manipDelay--;
        // RET;
        return;
    }

// ready:
    // LD_A(SFX_THROW_BALL);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_THROW_BALL);
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_FAST_SPIN_REEL2_UNTIL_LINED_UP_7S
    bc->reelAction = REEL_ACTION_FAST_SPIN_REEL2_UNTIL_LINED_UP_7S;
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(8);
    bc->spinRate = 8;
    // RET;
}

void ReelAction_FastSpinReel2UntilLinedUp7s(struct SlotReelData* bc){
    // CALL(aSlots_CheckMatchedFirstTwoReels);
    // RET_NC ;
    if(!Slots_CheckMatchedFirstTwoReels(bc))
        return;
    // LD_A_addr(wFirstTwoReelsMatchingSevens);
    // AND_A_A;
    // RET_Z ;
    if(gSlotData.firstTwoReelsMatchingSevens == FALSE)
        return;
    // CALL(aSlots_StopReel);
    Slots_StopReel(bc);
    // RET;
}

//  Ensures SEVENs are lined up if there's bias to SEVEN.
//  Ensures nothing is lined up if there's no bias symbols.
//  No other bias symbols are compatible with this mode.
// 
//  This is achieved by throwing Golem until the desired result
//  is produced. The amount of Golem thrown can be anywhere from
//   1 to 14 for SEVEN bias, and 4-8 for no bias.
void ReelAction_InitGolem(struct SlotReelData* bc){
    // CALL(aSlots_CheckMatchedAllThreeReels);
    // RET_C ;
    if(Slots_CheckMatchedAllThreeReels(bc))
        return;
    // LD_A(SFX_STOP_SLOT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_STOP_SLOT);
    // CALL(aSlots_WaitSFX);
    Slots_WaitSFX();
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_WAIT_GOLEM
    bc->reelAction = REEL_ACTION_WAIT_GOLEM;
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spinRate = 0;
    // CALL(aSlots_GetNumberOfGolems);
    uint8_t golemCount = Slots_GetNumberOfGolems(bc);
    // PUSH_BC;
    // PUSH_AF;
    // depixel2(12, 13);
    // LD_A(SPRITE_ANIM_INDEX_SLOTS_GOLEM);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* anim = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_SLOTS_GOLEM, pixel2(12, 13));
    // LD_HL(SPRITEANIMSTRUCT_VAR3);
    // ADD_HL_BC;
    // POP_AF;
    // LD_hl_A;
    anim->var3 = golemCount;
    // POP_BC;
    // XOR_A_A;
    // LD_addr_A(wSlotsDelay);
    wram->wSlotsDelay = 0;
    return ReelAction_WaitGolem(bc);
}

void ReelAction_WaitGolem(struct SlotReelData* bc){
    // LD_A_addr(wSlotsDelay);
    // CP_A(2);
    // IF_Z goto two;
    // CP_A(1);
    // IF_Z goto one;
    // RET;
    switch(wram->wSlotsDelay) {
    case 2:
    // two:
        // CALL(aSlots_CheckMatchedAllThreeReels);
        Slots_CheckMatchedAllThreeReels(bc);
        // CALL(aSlots_StopReel);
        Slots_StopReel(bc);
        // RET;
        return;

    case 1:
    // one:
        // LD_HL(REEL_ACTION);
        // ADD_HL_BC;
        // INC_hl;  // REEL_ACTION_END_GOLEM
        bc->reelAction++;
        // LD_HL(REEL_SPIN_RATE);
        // ADD_HL_BC;
        // LD_hl(8);
        bc->spinRate = 8;
        // RET;
        return;
    }
}

void ReelAction_EndGolem(struct SlotReelData* bc){
    // XOR_A_A;
    // LD_addr_A(wSlotsDelay);
    wram->wSlotsDelay = 0x0;
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // DEC_hl;  // REEL_ACTION_WAIT_GOLEM
    bc->reelAction--;
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spinRate = 0;
    // RET;
}

//  Ensures the lining up of SEVEN symbols, but this mode is only possible
//  when there is bias to SEVEN symbols (and even then, it's still rare).
//  Chansey releases and egg and reel #3 is made to advance 17 slots very
//  quickly as many times as necessary for the match to SEVENs to show up.
void ReelAction_InitChansey(struct SlotReelData* bc){
    // CALL(aSlots_CheckMatchedAllThreeReels);
    // RET_C ;
    if(Slots_CheckMatchedAllThreeReels(bc))
        return;
    // LD_A(SFX_STOP_SLOT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_STOP_SLOT);
    // CALL(aSlots_WaitSFX);
    Slots_WaitSFX();
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_WAIT_CHANSEY
    bc->reelAction = REEL_ACTION_WAIT_CHANSEY;
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spinRate = 0;
    // PUSH_BC;
    // depixel2(12, 0);
    // LD_A(SPRITE_ANIM_INDEX_SLOTS_CHANSEY);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_SLOTS_CHANSEY, pixel2(12, 0));
    // POP_BC;
    // XOR_A_A;
    // LD_addr_A(wSlotsDelay);
    wram->wSlotsDelay = 0x0;
    // RET;
}

void ReelAction_WaitChansey(struct SlotReelData* bc){
    // LD_A_addr(wSlotsDelay);
    // AND_A_A;
    // RET_Z ;
    if(wram->wSlotsDelay == 0)
        return;
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_WAIT_EGG
    bc->reelAction = REEL_ACTION_WAIT_EGG;
    // LD_A(2);
    // LD_addr_A(wSlotsDelay);
    wram->wSlotsDelay = 2;
    return ReelAction_WaitEgg(bc);
}

void ReelAction_WaitEgg(struct SlotReelData* bc){
    // LD_A_addr(wSlotsDelay);
    // CP_A(0x4);
    // RET_C ;
    if(wram->wSlotsDelay < 0x4)
        return;
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_DROP_REEL
    bc->reelAction = REEL_ACTION_DROP_REEL;
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(16);
    bc->spinRate = 16;
    // LD_HL(REEL_MANIP_DELAY);
    // ADD_HL_BC;
    // LD_hl(17);
    bc->manipDelay = 17;
    return ReelAction_DropReel(bc);
}

void ReelAction_DropReel(struct SlotReelData* bc){
    // LD_HL(REEL_MANIP_DELAY);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto check_match;
    if(bc->manipDelay != 0) {
        // DEC_hl;
        bc->manipDelay--;
        // RET;
        return;
    }

// check_match:
    // CALL(aSlots_CheckMatchedAllThreeReels);
    // IF_NC goto EggAgain;
    // AND_A_A;
    // IF_NZ goto EggAgain;
    if(Slots_CheckMatchedAllThreeReels(bc) && gSlotData.slotMatched == 0) {
        // LD_A(5);
        // LD_addr_A(wSlotsDelay);
        wram->wSlotsDelay = 5;
        // CALL(aSlots_StopReel);
        Slots_StopReel(bc);
        // RET;
        return;
    }

// EggAgain:
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spinRate = 0;
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // DEC_hl;
    // DEC_hl;  // REEL_ACTION_WAIT_CHANSEY
    bc->reelAction = REEL_ACTION_WAIT_CHANSEY;
    // LD_A(1);
    // LD_addr_A(wSlotsDelay);
    wram->wSlotsDelay = 1;
    // RET;
}

void ReelAction_Unused(struct SlotReelData* bc){
    // CALL(aSlots_CheckMatchedAllThreeReels);
    // RET_C ;
    if(Slots_CheckMatchedAllThreeReels(bc))
        return;
    // LD_A(SFX_STOP_SLOT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_STOP_SLOT);
    // CALL(aSlots_WaitSFX);
    Slots_WaitSFX();
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_CHECK_DROP_REEL
    bc->reelAction = REEL_ACTION_CHECK_DROP_REEL;
    // CALL(aSlots_GetNumberOfGolems);
    // LD_HL(REEL_MANIP_DELAY);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->manipDelay = Slots_GetNumberOfGolems(bc);
    return ReelAction_CheckDropReel(bc);
}

void ReelAction_CheckDropReel(struct SlotReelData* bc){
    // LD_HL(REEL_MANIP_DELAY);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_NZ goto spin;
    if(bc->manipDelay == 0) {
        // CALL(aSlots_CheckMatchedAllThreeReels);
        Slots_CheckMatchedAllThreeReels(bc);
        // CALL(aSlots_StopReel);
        Slots_StopReel(bc);
        // RET;
        return;
    }

// spin:
    // DEC_hl;
    bc->manipDelay--;
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_WAIT_DROP_REEL
    bc->reelAction = REEL_ACTION_WAIT_DROP_REEL;
    // LD_HL(REEL_FIELD_0B);
    // ADD_HL_BC;
    // LD_hl(32);
    bc->field0b = 32;
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(0);
    bc->spinRate = 0;
    return ReelAction_WaitDropReel(bc);
}

void ReelAction_WaitDropReel(struct SlotReelData* bc){
    // LD_HL(REEL_FIELD_0B);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto DropReel;
    if(bc->field0b != 0) {
        // DEC_hl;
        bc->field0b--;
        // RET;
        return;
    }

// DropReel:
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // DEC_hl;
    bc->reelAction = REEL_ACTION_CHECK_DROP_REEL;
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(8);
    bc->spinRate = 8;
    // RET;
}

//  Ensures SEVENs are lined up if there's bias to SEVEN.
//  Ensures nothing is lined up if there's no bias symbols.
//  No other bias symbols are compatible with this mode.
//
//  This is achieved by slowly advancing the reel a full round,
//  plus any necessary slot until the desired result is produced.
void ReelAction_StartSlowAdvanceReel3(struct SlotReelData* bc){
    // CALL(aSlots_CheckMatchedAllThreeReels);
    // RET_C ;
    if(Slots_CheckMatchedAllThreeReels(bc))
        return;
    // LD_A(SFX_STOP_SLOT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_STOP_SLOT);
    // CALL(aSlots_WaitSFX);
    Slots_WaitSFX();
    // LD_HL(REEL_SPIN_RATE);
    // ADD_HL_BC;
    // LD_hl(1);
    bc->spinRate = 1;
    // LD_HL(REEL_ACTION);
    // ADD_HL_BC;
    // INC_hl;  // REEL_ACTION_WAIT_SLOW_ADVANCE_REEL3
    bc->reelAction = REEL_ACTION_WAIT_SLOW_ADVANCE_REEL3;
    // LD_HL(REEL_MANIP_DELAY);
    // ADD_HL_BC;
    // LD_hl(16);
    bc->manipDelay = 16;
    return ReelAction_WaitSlowAdvanceReel3(bc);
}

void ReelAction_WaitSlowAdvanceReel3(struct SlotReelData* bc){
    // LD_HL(REEL_MANIP_DELAY);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto check1;
    if(bc->manipDelay != 0) {
        // DEC_hl;
        bc->manipDelay--;
    }

// check1:
    // LD_A_addr(wSlotBias);
    // AND_A_A;
    // IF_NZ goto check2;
    else if(gSlotData.slotBias == 0) {
        // CALL(aSlots_CheckMatchedAllThreeReels);
        // IF_NC goto play_sfx;
        // AND_A_A;
        // IF_NZ goto play_sfx;
        if(Slots_CheckMatchedAllThreeReels(bc) && gSlotData.slotMatched == 0) {
            // CALL(aSlots_StopReel);
            Slots_StopReel(bc);
            // CALL(aWaitSFX);
            WaitSFX_Conv();
            // RET;
            return;
        }
    }

// check2:
    // CALL(aSlots_CheckMatchedAllThreeReels);
    // IF_C goto play_sfx;
    else if(!Slots_CheckMatchedAllThreeReels(bc)) {
        // CALL(aSlots_StopReel);
        Slots_StopReel(bc);
        // CALL(aWaitSFX);
        WaitSFX_Conv();
        // RET;
        return;
    }

// play_sfx:
    // LD_A(SFX_GOT_SAFARI_BALLS);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_GOT_SAFARI_BALLS);
    // RET;
    return;
}

static void Slots_CheckMatchedFirstTwoReels_StoreResult(uint8_t a) {
    // LD_addr_A(wSlotBuildingMatch);
    gSlotData.slotBuildingMatch = a;
    // AND_A_A;
    // IF_NZ goto matching_sevens;
    if(a == SLOTS_SEVEN) {
        // LD_A(1);
        // LD_addr_A(wFirstTwoReelsMatchingSevens);
        gSlotData.firstTwoReelsMatchingSevens = TRUE;
    }

// matching_sevens:
    // LD_A(1);
    // LD_addr_A(wFirstTwoReelsMatching);
    gSlotData.firstTwoReelsMatching = TRUE;
    // RET;
}

static void Slots_CheckMatchedFirstTwoReels_CheckBottomRow(void) {
    // LD_HL(wCurReelStopped);
    // LD_A_addr(wReel1Stopped);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedFirstTwoReels_StoreResult);
    if(gSlotData.curReelStopped[0] == gSlotData.reel1Stopped[0])
        Slots_CheckMatchedFirstTwoReels_StoreResult(gSlotData.reel1Stopped[0]);
    // RET;
}

static void Slots_CheckMatchedFirstTwoReels_CheckUpwardsDiag(void){
    // LD_HL(wCurReelStopped + 1);
    // LD_A_addr(wReel1Stopped);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedFirstTwoReels_StoreResult);
    if(gSlotData.curReelStopped[1] == gSlotData.reel1Stopped[0])
        Slots_CheckMatchedFirstTwoReels_StoreResult(gSlotData.reel1Stopped[0]);
    // RET;
}

static void Slots_CheckMatchedFirstTwoReels_CheckMiddleRow(void){
    // LD_HL(wCurReelStopped + 1);
    // LD_A_addr(wReel1Stopped + 1);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedFirstTwoReels_StoreResult);
    if(gSlotData.curReelStopped[1] == gSlotData.reel1Stopped[1])
        Slots_CheckMatchedFirstTwoReels_StoreResult(gSlotData.reel1Stopped[1]);
    // RET;
}

static void Slots_CheckMatchedFirstTwoReels_CheckDownwardsDiag(void){
    // LD_HL(wCurReelStopped + 1);
    // LD_A_addr(wReel1Stopped + 2);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedFirstTwoReels_StoreResult);
    if(gSlotData.curReelStopped[1] == gSlotData.reel1Stopped[2])
        Slots_CheckMatchedFirstTwoReels_StoreResult(gSlotData.reel1Stopped[2]);
    // RET;
}

static void Slots_CheckMatchedFirstTwoReels_CheckTopRow(void){
    // LD_HL(wCurReelStopped + 2);
    // LD_A_addr(wReel1Stopped + 2);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedFirstTwoReels_StoreResult);
    if(gSlotData.curReelStopped[2] == gSlotData.reel1Stopped[2])
        Slots_CheckMatchedFirstTwoReels_StoreResult(gSlotData.reel1Stopped[2]);
    // RET;
}

bool Slots_CheckMatchedFirstTwoReels(struct SlotReelData* bc){
    // XOR_A_A;
    // LD_addr_A(wFirstTwoReelsMatching);
    gSlotData.firstTwoReelsMatching = FALSE;
    // LD_addr_A(wFirstTwoReelsMatchingSevens);
    gSlotData.firstTwoReelsMatchingSevens = FALSE;
    // CALL(aSlots_GetCurrentReelState);
    const uint8_t* state = Slots_GetCurrentReelState(bc);
    // CALL(aSlots_CopyReelState);
    Slots_CopyReelState(state);
    // LD_A_addr(wSlotBet);
    // AND_A(3);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSlots_CheckMatchedFirstTwoReels_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mSlots_CheckMatchedFirstTwoReels_return);
    // PUSH_DE;
    // JP_hl;
    switch(gSlotData.slotBet & 3) {
    // Jumptable:
        //dw ['.zero'];
        //dw ['.one'];
        //dw ['.two'];
        //dw ['.three'];
        case 3:
        // three:
            // CALL(aSlots_CheckMatchedFirstTwoReels_CheckUpwardsDiag);
            Slots_CheckMatchedFirstTwoReels_CheckUpwardsDiag();
            // CALL(aSlots_CheckMatchedFirstTwoReels_CheckDownwardsDiag);
            Slots_CheckMatchedFirstTwoReels_CheckDownwardsDiag();
            fallthrough;

        case 2:
        // two:
            // CALL(aSlots_CheckMatchedFirstTwoReels_CheckBottomRow);
            Slots_CheckMatchedFirstTwoReels_CheckBottomRow();
            // CALL(aSlots_CheckMatchedFirstTwoReels_CheckTopRow);
            Slots_CheckMatchedFirstTwoReels_CheckTopRow();
            fallthrough;

        case 1:
        // one:
            // CALL(aSlots_CheckMatchedFirstTwoReels_CheckMiddleRow);
            Slots_CheckMatchedFirstTwoReels_CheckMiddleRow();
            fallthrough;

        case 0:
        // zero:
            // RET;
            break;
    }


// l_return:
    // LD_A_addr(wFirstTwoReelsMatching);
    // AND_A_A;
    // RET_Z ;
    // SCF;
    // RET;
    return gSlotData.firstTwoReelsMatching != FALSE;
}

static void Slots_CheckMatchedAllThreeReels_StoreResult(uint8_t a) {
    // LD_addr_A(wSlotMatched);
    gSlotData.slotMatched = a;
    // RET;
}

static void Slots_CheckMatchedAllThreeReels_CheckBottomRow(void){
    // LD_HL(wCurReelStopped);
    // LD_A_addr(wReel1Stopped);
    uint8_t stopped = gSlotData.reel1Stopped[0];
    // CP_A_hl;
    // RET_NZ ;
    // LD_HL(wReel2Stopped);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedAllThreeReels_StoreResult);
    if(stopped == gSlotData.curReelStopped[0] && stopped == gSlotData.reel2Stopped[0])
        Slots_CheckMatchedAllThreeReels_StoreResult(stopped);
    // RET;
}

static void Slots_CheckMatchedAllThreeReels_CheckUpwardsDiag(void){
    // LD_HL(wCurReelStopped + 2);
    // LD_A_addr(wReel1Stopped);
    uint8_t stopped = gSlotData.reel1Stopped[0];
    // CP_A_hl;
    // RET_NZ ;
    // LD_HL(wReel2Stopped + 1);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedAllThreeReels_StoreResult);
    if(stopped == gSlotData.curReelStopped[2] && stopped == gSlotData.reel2Stopped[1])
        Slots_CheckMatchedAllThreeReels_StoreResult(stopped);
    // RET;
}

static void Slots_CheckMatchedAllThreeReels_CheckMiddleRow(void){
    // LD_HL(wCurReelStopped + 1);
    // LD_A_addr(wReel1Stopped + 1);
    uint8_t stopped = gSlotData.reel1Stopped[1];
    // CP_A_hl;
    // RET_NZ ;
    // LD_HL(wReel2Stopped + 1);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedAllThreeReels_StoreResult);
    if(stopped == gSlotData.curReelStopped[1] && stopped == gSlotData.reel2Stopped[1])
        Slots_CheckMatchedAllThreeReels_StoreResult(stopped);
    // RET;
}

static void Slots_CheckMatchedAllThreeReels_CheckDownwardsDiag(void){
    // LD_HL(wCurReelStopped);
    // LD_A_addr(wReel1Stopped + 2);
    uint8_t stopped = gSlotData.reel1Stopped[2];
    // CP_A_hl;
    // RET_NZ ;
    // LD_HL(wReel2Stopped + 1);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedAllThreeReels_StoreResult);
    if(stopped == gSlotData.curReelStopped[0] && stopped == gSlotData.reel2Stopped[1])
        Slots_CheckMatchedAllThreeReels_StoreResult(stopped);
    // RET;
}

static void Slots_CheckMatchedAllThreeReels_CheckTopRow(void){
    // LD_HL(wCurReelStopped + 2);
    // LD_A_addr(wReel1Stopped + 2);
    uint8_t stopped = gSlotData.reel1Stopped[2];
    // CP_A_hl;
    // RET_NZ ;
    // LD_HL(wReel2Stopped + 2);
    // CP_A_hl;
    // CALL_Z (aSlots_CheckMatchedAllThreeReels_StoreResult);
    if(stopped == gSlotData.curReelStopped[2] && stopped == gSlotData.reel2Stopped[2])
        Slots_CheckMatchedAllThreeReels_StoreResult(stopped);
    // RET;
}

bool Slots_CheckMatchedAllThreeReels(struct SlotReelData* bc){
    // LD_A(SLOTS_NO_MATCH);
    // LD_addr_A(wSlotMatched);
    gSlotData.slotMatched = SLOTS_NO_MATCH;
    // CALL(aSlots_GetCurrentReelState);
    // CALL(aSlots_CopyReelState);
    Slots_CopyReelState(Slots_GetCurrentReelState(bc));
    // LD_A_addr(wSlotBet);
    // AND_A(3);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSlots_CheckMatchedAllThreeReels_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mSlots_CheckMatchedAllThreeReels_return);
    // PUSH_DE;
    // JP_hl;
    switch(gSlotData.slotBet & 3) {
    // Jumptable:
        //dw ['.zero'];
        //dw ['.one'];
        //dw ['.two'];
        //dw ['.three'];
    case 3:
    // three:
        // CALL(aSlots_CheckMatchedAllThreeReels_CheckUpwardsDiag);
        Slots_CheckMatchedAllThreeReels_CheckUpwardsDiag();
        // CALL(aSlots_CheckMatchedAllThreeReels_CheckDownwardsDiag);
        Slots_CheckMatchedAllThreeReels_CheckDownwardsDiag();
        fallthrough;

    case 2:
    // two:
        // CALL(aSlots_CheckMatchedAllThreeReels_CheckBottomRow);
        Slots_CheckMatchedAllThreeReels_CheckBottomRow();
        // CALL(aSlots_CheckMatchedAllThreeReels_CheckTopRow);
        Slots_CheckMatchedAllThreeReels_CheckTopRow();
        fallthrough;

    case 1:
    // one:
        // CALL(aSlots_CheckMatchedAllThreeReels_CheckMiddleRow);
        Slots_CheckMatchedAllThreeReels_CheckMiddleRow();
        fallthrough;

    case 0:
    // zero:
        // RET;
        break;
    }


// l_return:
    // LD_A_addr(wSlotMatched);
    // CP_A(SLOTS_NO_MATCH);
    // IF_NZ goto matched_nontrivial;
    if(gSlotData.slotMatched != SLOTS_NO_MATCH) {
    // matched_nontrivial:
        // SCF;
        // RET;
        return true;
    }
    // AND_A_A;
    // RET;
    return false;
}

void Slots_CopyReelState(const uint8_t* state){
    // LD_DE(wCurReelStopped);
    // LD_A_hli;
    // LD_de_A;
    gSlotData.curReelStopped[0] = state[0];
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    gSlotData.curReelStopped[1] = state[1];
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    gSlotData.curReelStopped[2] = state[2];
    // RET;
}

static uint8_t Slots_GetNumberOfGolems_Check7Bias(struct SlotReelData* bc){
    // LD_A_addr(wSlotBias);
    // AND_A_A;
    // IF_NZ goto not_biased_to_seven;
    if(gSlotData.slotBias == SLOTS_SEVEN) {
        // LD_E(0x0);
        uint8_t e = 0x0;

        do {
        // loop1:
            // LD_HL(REEL_POSITION);
            // ADD_HL_BC;
            // INC_hl;
            bc->position++;
            // INC_E;
            e++;
            // PUSH_DE;
            // CALL(aSlots_CheckMatchedAllThreeReels);
            // POP_DE;
            // IF_NC goto loop1;
            // AND_A_A;
            // IF_NZ goto loop1;
        } while(!Slots_CheckMatchedAllThreeReels(bc) || gSlotData.slotMatched != SLOTS_SEVEN);
        // RET;
        return e;
    }
    else {
        uint8_t e;
        do {
        // not_biased_to_seven:
            // CALL(aRandom);
            // AND_A(0x7);
            e = Random_Conv() & 0x7;
            // CP_A(0x8 / 2);  // 50%
            // IF_C goto not_biased_to_seven;
        } while(e < 0x8 / 2);  // 50%
        // LD_E_A;

        do {
        // loop2:
            // LD_A_E;
            // INC_E;
            // LD_HL(REEL_POSITION);
            // ADD_HL_BC;
            // ADD_A_hl;
            // LD_hl_A;
            bc->position += e++;
            // PUSH_DE;
            // CALL(aSlots_CheckMatchedAllThreeReels);
            // POP_DE;
            // IF_C goto loop2;
        } while(Slots_CheckMatchedAllThreeReels(bc));
        // RET;
        return e;
    }
}

uint8_t Slots_GetNumberOfGolems(struct SlotReelData* bc){
    // LD_HL(REEL_POSITION);
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t position = bc->position;
    // PUSH_AF;
    // PUSH_HL;
    // CALL(aSlots_GetNumberOfGolems_Check7Bias);
    uint8_t e = Slots_GetNumberOfGolems_Check7Bias(bc);
    // POP_HL;
    // POP_AF;
    // LD_hl_A;
    bc->position = position;
    // LD_A_E;
    // RET;
    return e;
}

void Slots_InitBias(void){
    static const uint8_t Normal[] = {
        1 percent - 1,  SLOTS_SEVEN,
        1 percent + 1,  SLOTS_POKEBALL,
        4 percent,      SLOTS_STARYU,
        8 percent,      SLOTS_SQUIRTLE,
        16 percent,     SLOTS_PIKACHU,
        19 percent,     SLOTS_CHERRY,
        100 percent,    SLOTS_NO_BIAS,
    };

    static const uint8_t Lucky[] = {
        1 percent,      SLOTS_SEVEN,
        1 percent + 1,  SLOTS_POKEBALL,
        3 percent + 1,  SLOTS_STARYU,
        6 percent + 1,  SLOTS_SQUIRTLE,
        12 percent,     SLOTS_PIKACHU,
        31 percent + 1, SLOTS_CHERRY,
        100 percent,    SLOTS_NO_BIAS,
    };
    // LD_A_addr(wSlotBias);
    // AND_A_A;
    // RET_Z ;
    if(gSlotData.slotBias == 0)
        return;
    // LD_HL(mSlots_InitBias_Normal);
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_Z goto okay;
    // LD_HL(mSlots_InitBias_Lucky);
    const uint8_t* hl = (wram->wScriptVar == 0)? Normal: Lucky;

// okay:
    // CALL(aRandom);
    // LD_C_A;
    uint8_t c = Random_Conv();

    while(c < *hl) {
    // loop:
        // LD_A_hli;
        // CP_A_C;
        // IF_NC goto done;
        // INC_HL;
        hl += 2;
        // goto loop;
    }

// done:
    // LD_A_hl;
    // LD_addr_A(wSlotBias);
    gSlotData.slotBias = hl[1];
    // RET;
}

void Slots_IlluminateBetLights(void){
    // LD_B(0x14);  // turned on
    // LD_A_addr(wSlotBet);
    // DEC_A;
    // JR_Z (mSlots_Lights1OnOff);
    if(gSlotData.slotBet == 1)
        return Slots_Lights1OnOff(0x14);
    // DEC_A;
    // JR_Z (mSlots_Lights2OnOff);
    if(gSlotData.slotBet == 2)
        return Slots_Lights2OnOff(0x14);
    // JR(mSlots_Lights3OnOff);
    return Slots_Lights3OnOff(0x14);
}

void Slots_DeilluminateBetLights(void){
    // LD_B(0x23);  // turned off
    return Slots_Lights3OnOff(0x23);
}

void Slots_Lights3OnOff(uint8_t b){
    // hlcoord(3, 2, wTilemap);
    // CALL(aSlots_TurnLightsOnOrOff);
    Slots_TurnLightsOnOrOff(coord(3, 2, wram->wTilemap), b);
    // hlcoord(3, 10, wTilemap);
    // CALL(aSlots_TurnLightsOnOrOff);
    Slots_TurnLightsOnOrOff(coord(3, 10, wram->wTilemap), b);
    return Slots_Lights2OnOff(b);
}

void Slots_Lights2OnOff(uint8_t b){
    // hlcoord(3, 4, wTilemap);
    // CALL(aSlots_TurnLightsOnOrOff);
    Slots_TurnLightsOnOrOff(coord(3, 4, wram->wTilemap), b);
    // hlcoord(3, 8, wTilemap);
    // CALL(aSlots_TurnLightsOnOrOff);
    Slots_TurnLightsOnOrOff(coord(3, 8, wram->wTilemap), b);
    return Slots_Lights1OnOff(b);
}

void Slots_Lights1OnOff(uint8_t b){
    // hlcoord(3, 6, wTilemap);

    return Slots_TurnLightsOnOrOff(coord(3, 6, wram->wTilemap), b);
}

void Slots_TurnLightsOnOrOff(uint8_t* hl, uint8_t b){
    // LD_A_B;
    // LD_hl_A;
    *hl = b;
    // LD_DE(SCREEN_WIDTH / 2 + 3);
    // ADD_HL_DE;
    hl += SCREEN_WIDTH / 2 + 3;
    // LD_hl_A;
    *hl = b;
    // LD_DE(SCREEN_WIDTH / 2 - 3);
    // ADD_HL_DE;
    hl += SCREEN_WIDTH / 2 - 3;
    // INC_A;
    // LD_hl_A;
    *hl = b + 1;
    // LD_DE(SCREEN_WIDTH / 2 + 3);
    // ADD_HL_DE;
    hl += SCREEN_WIDTH / 2 + 3;
    // LD_hl_A;
    *hl = b + 1;
    // RET;
}

static const struct MenuHeader Slots_AskBet_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(14, 10, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 3,  // items
            .options = (const char*[]) {
                " 3",
                " 2",
                " 1",
            },
        },
    },
    .defaultOption = 1,  // default option
};

bool Slots_AskBet(void){
    static const txt_cmd_s SlotsBetHowManyCoinsText[] = {
        text_far(v_SlotsBetHowManyCoinsText)
        text_end
    };
    static const txt_cmd_s SlotsStartText[] = {
        text_far(v_SlotsStartText)
        text_end
    };
    static const txt_cmd_s SlotsNotEnoughCoinsText[] = {
        text_far(v_SlotsNotEnoughCoinsText)
        text_end
    };
    while(1) {
    // loop:
        // LD_HL(mSlots_AskBet_SlotsBetHowManyCoinsText);
        // CALL(aPrintText);
        PrintText_Conv2(SlotsBetHowManyCoinsText);
        // LD_HL(mSlots_AskBet_MenuHeader);
        // CALL(aLoadMenuHeader);
        LoadMenuHeader_Conv2(&Slots_AskBet_MenuHeader);
        // CALL(aVerticalMenu);
        bool cancel = !VerticalMenu_Conv();
        // CALL(aCloseWindow);
        CloseWindow_Conv2();
        // RET_C ;
        if(cancel)
            return true;
        // LD_A_addr(wMenuCursorY);
        // LD_B_A;
        // LD_A(4);
        // SUB_A_B;
        // LD_addr_A(wSlotBet);
        gSlotData.slotBet = 4 - wram->wMenuCursorY;
        // LD_HL(wCoins);
        // LD_C_A;
        // LD_A_hli;
        // AND_A_A;
        // IF_NZ goto Start;
        // LD_A_hl;
        // CP_A_C;
        // IF_NC goto Start;
        if(ReverseEndian16(wram->wCoins) >= gSlotData.slotBet)
            break;
        // LD_HL(mSlots_AskBet_SlotsNotEnoughCoinsText);
        // CALL(aPrintText);
        PrintText_Conv2(SlotsNotEnoughCoinsText);
        // goto loop;
    }

// Start:
    // LD_HL(wCoins + 1);
    // LD_A_hl;
    // SUB_A_C;
    // LD_hld_A;
    // IF_NC goto ok;
    // DEC_hl;

// ok:
    wram->wCoins = ReverseEndian16(ReverseEndian16(wram->wCoins) - gSlotData.slotBet);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_DE(SFX_PAY_DAY);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_PAY_DAY);
    // LD_HL(mSlots_AskBet_SlotsStartText);
    // CALL(aPrintText);
    PrintText_Conv2(SlotsStartText);
    // AND_A_A;
    // RET;
    return false;
}

bool Slots_AskPlayAgain(void){
    static const txt_cmd_s SlotsRanOutOfCoinsText[] = {
        text_far(v_SlotsRanOutOfCoinsText)
        text_end
    };
    static const txt_cmd_s SlotsPlayAgainText[] = {
        text_far(v_SlotsPlayAgainText)
        text_end
    };
    // LD_HL(wCoins);
    // LD_A_hli;
    // OR_A_hl;
    // IF_NZ goto you_have_coins;
    if(wram->wCoins == 0) {
        // LD_HL(mSlots_AskPlayAgain_SlotsRanOutOfCoinsText);
        // CALL(aPrintText);
        PrintText_Conv2(SlotsRanOutOfCoinsText);
        // LD_C(60);
        // CALL(aDelayFrames);
        DelayFrames_Conv(60);
        // goto exit_slots;
    }
    else {
    // you_have_coins:
        // LD_HL(mSlots_AskPlayAgain_SlotsPlayAgainText);
        // CALL(aPrintText);
        PrintText_Conv2(SlotsPlayAgainText);
        // CALL(aLoadMenuTextbox);
        LoadMenuTextbox_Conv();
        // LD_BC((14 << 8) | 12);
        // CALL(aPlaceYesNoBox);
        PlaceYesNoBox_Conv(14, 12);
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        uint8_t cursor = wram->wMenuCursorY;
        // CALL(aCloseWindow);
        CloseWindow_Conv2();
        // AND_A_A;
        // IF_NZ goto exit_slots;
        if(cursor == 1) {
            // AND_A_A;
            // RET;
            return false;
        }
    }

// exit_slots:
    // SCF;
    // RET;
    return true;
}

uint16_t Slots_GetPayout(void){
    static const uint16_t PayoutTable[] = {
        //table_width ['2', 'Slots_GetPayout.PayoutTable']
        300,  // SLOTS_SEVEN
        50,  // SLOTS_POKEBALL
        6,  // SLOTS_CHERRY
        8,  // SLOTS_PIKACHU
        10,  // SLOTS_SQUIRTLE
        15,  // SLOTS_STARYU
    };
    static_assert(lengthof(PayoutTable) == NUM_SLOT_REELS, "");
    // LD_A_addr(wSlotMatched);
    // CP_A(SLOTS_NO_MATCH);
    // IF_Z goto no_win;
    if(gSlotData.slotMatched == SLOTS_NO_MATCH) {
    // no_win:
        // LD_HL(wPayout);
        // XOR_A_A;
        // LD_hli_A;
        // LD_hl_A;
        gSlotData.payout = 0;
        // RET;
        return 0;
    }
    // SRL_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSlots_GetPayout_PayoutTable);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_addr_A(wPayout + 1);
    // LD_E_A;
    // LD_A_hl;
    // LD_addr_A(wPayout);
    gSlotData.payout = ReverseEndian16(PayoutTable[gSlotData.slotMatched / 4]);
    // LD_D_A;
    // FARCALL(aStubbedTrainerRankings_AddToSlotsPayouts);
    // RET;
    return gSlotData.payout;
}

static const txt_cmd_s Slots_PayoutText_SlotsLinedUpText[] = {
    text_far(v_SlotsLinedUpText)
    text_end
};

static const txt_cmd_s Slots_PayoutText_SlotsDarnText[] = {
    text_far(v_SlotsDarnText)
    text_end
};
static void Text_PrintLayout_Function(struct TextCmdState* state) {
    // LD_A_addr(wSlotMatched);
    // ADD_A(0x25);
    uint8_t a = gSlotData.slotMatched + 0x25;
    // ldcoord_a(2, 13, wTilemap);
    // INC_A;
    *coord(2, 13, wram->wTilemap) = a++;
    // ldcoord_a(2, 14, wTilemap);
    // INC_A;
    *coord(2, 14, wram->wTilemap) = a++;
    // ldcoord_a(3, 13, wTilemap);
    // INC_A;
    *coord(3, 13, wram->wTilemap) = a++;
    // ldcoord_a(3, 14, wTilemap);
    *coord(3, 14, wram->wTilemap) = a;
    // hlcoord(18, 17, wTilemap);
    // LD_hl(0xee);
    *coord(18, 17, wram->wTilemap) = 0xee;
    // LD_HL(mSlots_PayoutText_SlotsLinedUpText);
    state->hl = Slots_PayoutText_SlotsLinedUpText;
    // for(int rept = 0; rept < 4; rept++){
    // INC_BC;
    // }
    state->bc += 4;
    // RET;
}
static const txt_cmd_s Slots_PayoutText_Text_PrintPayout[] = {
    text_asm(Text_PrintLayout_Function)
};

static void Slots_PayoutText_LinedUpSevens(void){
    // LD_A(SFX_2ND_PLACE);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_2ND_PLACE);
    // CALL(aWaitSFX);
    WaitSFX_Conv();

//  Oddly, the rarest mode (wKeepSevenBiasChance = 1) is the one with
//  the worse odds to favor seven symbol streaks (12.5% vs 25%).
//  it's possible that either the wKeepSevenBiasChance initialization
//  or this code was intended to lead to flipped percentages.
    // LD_A_addr(wKeepSevenBiasChance);
    // AND_A_A;
    // IF_NZ goto lower_seven_streak_odds;
    if(wram->wKeepSevenBiasChance == 0) {
        // CALL(aRandom);
        // AND_A(0b0010100);
        // RET_Z ;  // 25% chance to stick with seven symbol bias
        if((Random_Conv() & 0b0010100) == 0)  // 25% chance to stick with seven symbol bias
            return;
        // LD_A(SLOTS_NO_BIAS);
        // LD_addr_A(wSlotBias);
        gSlotData.slotBias = SLOTS_NO_BIAS;
        // RET;
        return;
    }
    else {
    // lower_seven_streak_odds:
        // CALL(aRandom);
        // AND_A(0b0011100);
        // RET_Z ;  // 12.5% chance to stick with seven symbol bias
        if((Random_Conv() & 0b0011100) == 0)  // 12.5% chance to stick with seven symbol bias
            return;
        // LD_A(SLOTS_NO_BIAS);
        // LD_addr_A(wSlotBias);
        gSlotData.slotBias = SLOTS_NO_BIAS;
        // RET;
        return;
    }
}

static void Slots_PayoutText_LinedUpPokeballs(void){
    // LD_A(SFX_3RD_PLACE);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_3RD_PLACE);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // RET;
}

static void Slots_PayoutText_LinedUpMonOrCherry(void){
    // LD_A(SFX_PRESENT);
    // CALL(aSlots_PlaySFX);
    Slots_PlaySFX(SFX_PRESENT);
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // RET;
}

void Slots_PayoutText(void){
    static const struct CostStringFunc {
        const char* string;
        void (*func)(void);
    } PayoutStrings[] = {
        //table_width ['6', 'Slots_PayoutText.PayoutStrings']
        {"300", Slots_PayoutText_LinedUpSevens},  // SLOTS_SEVEN
        {"50@", Slots_PayoutText_LinedUpPokeballs},  // SLOTS_POKEBALL
        {"6@@", Slots_PayoutText_LinedUpMonOrCherry},  // SLOTS_CHERRY
        {"8@@", Slots_PayoutText_LinedUpMonOrCherry},  // SLOTS_PIKACHU
        {"10@", Slots_PayoutText_LinedUpMonOrCherry},  // SLOTS_SQUIRTLE
        {"15@", Slots_PayoutText_LinedUpMonOrCherry},  // SLOTS_STARYU
    };
    static_assert(lengthof(PayoutStrings) == NUM_SLOT_REELS, "");
    // LD_A_addr(wSlotMatched);
    // CP_A(SLOTS_NO_MATCH);
    // IF_NZ goto MatchedSomething;
    if(gSlotData.slotMatched == SLOTS_NO_MATCH) {
        // LD_HL(mSlots_PayoutText_SlotsDarnText);
        // CALL(aPrintText);
        PrintText_Conv2(Slots_PayoutText_SlotsDarnText);
        // FARCALL(aStubbedTrainerRankings_EndSlotsWinStreak);
        // RET;
        return;
    }

// MatchedSomething:
    // SRL_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSlots_PayoutText_PayoutStrings);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_DE(wStringBuffer2);
    // LD_BC(4);
    // CALL(aCopyBytes);
    U82CB(wram->wStringBuffer2, 4, PayoutStrings[gSlotData.slotMatched / 4].string);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mSlots_PayoutText_return);
    // PUSH_DE;
    // JP_hl;
    PayoutStrings[gSlotData.slotMatched / 4].func();

// l_return:
    // LD_HL(mSlots_PayoutText_Text_PrintPayout);
    // CALL(aPrintText);
    PrintText_Conv2(Slots_PayoutText_Text_PrintPayout);
    // FARCALL(aStubbedTrainerRankings_AddToSlotsWinStreak);
    // RET;
}

void Slots_AnimateGolem(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mSlots_AnimateGolem_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;

    switch(bc->jumptableIndex) {
    // Jumptable:
        //dw ['.init'];
        //dw ['.fall'];
        //dw ['.roll'];

    case 0:
    // init:
        // LD_HL(SPRITEANIMSTRUCT_VAR3);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto retain;
        if(bc->var3 == 0) {
            // LD_A(2);
            // LD_addr_A(wSlotsDelay);
            wram->wSlotsDelay = 2;
            // LD_HL(SPRITEANIMSTRUCT_INDEX);
            // ADD_HL_BC;
            // LD_hl(0x0);
            bc->index = 0x0;
            // RET;
            return;
        }

    // retain:
        // DEC_hl;
        bc->var3--;
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // INC_hl;
        bc->jumptableIndex++;
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x30);
        bc->var1 = 0x30;
        // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->xOffset = 0x0;
        fallthrough;

    case 1:
    // fall:
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x20);
        // IF_C goto play_sound;
        if(bc->var1 >= 0x20) {
            // DEC_hl;
            uint8_t var1 = bc->var1--;
            // LD_E_A;
            // LD_D(14 * 8);
            // FARCALL(aBattleAnim_Sine_e);
            // LD_A_E;
            // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
            // ADD_HL_BC;
            // LD_hl_A;
            bc->yOffset = BattleAnim_Sine_e_Conv(var1, 14 * 8);
            // RET;
            return;
        }

    // play_sound:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // INC_hl;
        bc->jumptableIndex++;
        // LD_HL(SPRITEANIMSTRUCT_VAR2);
        // ADD_HL_BC;
        // LD_hl(0x2);
        bc->var2 = 0x2;
        // LD_A(1);
        // LD_addr_A(wSlotsDelay);
        wram->wSlotsDelay = 1;
        // LD_A(SFX_PLACE_PUZZLE_PIECE_DOWN);
        // CALL(aSlots_PlaySFX);
        Slots_PlaySFX(SFX_PLACE_PUZZLE_PIECE_DOWN);
        // RET;
        return;

    case 2: {
    // roll:
        // LD_HL(SPRITEANIMSTRUCT_XOFFSET);
        // ADD_HL_BC;
        // LD_A_hl;
        uint8_t xOffset = bc->xOffset;
        // INC_hl;
        // INC_hl;
        bc->xOffset += 2;
        // CP_A(9 * 8);
        // IF_NC goto restart;
        if(xOffset < 9 * 8) {
            // AND_A(0x3);
            // RET_NZ ;
            if((xOffset & 0x3) == 0) {
                // LD_HL(SPRITEANIMSTRUCT_VAR2);
                // ADD_HL_BC;
                // LD_A_hl;
                // XOR_A(0xff);
                // INC_A;
                // LD_hl_A;
                bc->var2 = (bc->var2 ^ 0xff) + 1;
                // LDH_addr_A(hSCY);
                hram->hSCY = bc->var2;
            }
            // RET;
            return;
        }

    // restart:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // XOR_A_A;
        // LD_hl_A;
        bc->jumptableIndex = 0x0;
        // LDH_addr_A(hSCY);
        hram->hSCY = 0x0;
        // RET;
    } return;
    }
}

void Slots_AnimateChansey(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mSlots_AnimateChansey_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;

    switch(bc->jumptableIndex) {
    // Jumptable:
        //dw ['.walk'];
        //dw ['.one'];
        //dw ['.two'];

    case 0: {
    // walk:
        // LD_HL(SPRITEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // INC_hl;
        uint8_t x = bc->xCoord++;
        // CP_A(13 * 8);
        // IF_Z goto limit;
        if(x != 13 * 8) {
            // AND_A(0xf);
            // RET_NZ ;
            if((x & 0xf) == 0) {
                // LD_DE(SFX_JUMP_OVER_LEDGE);
                // CALL(aPlaySFX);
                PlaySFX_Conv(SFX_JUMP_OVER_LEDGE);
            }
            // RET;
            return;
        }

    // limit:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // INC_hl;
        bc->jumptableIndex++;
        // LD_A(1);
        // LD_addr_A(wSlotsDelay);
        wram->wSlotsDelay = 1;
    } fallthrough;

    case 1: {
    // one:
        // LD_A_addr(wSlotsDelay);
        // CP_A(0x2);
        // IF_Z goto retain;
        if(wram->wSlotsDelay != 0x2) {
            // CP_A(0x5);
            // RET_NZ ;
            if(wram->wSlotsDelay == 0x5) {
                // LD_HL(SPRITEANIMSTRUCT_INDEX);
                // ADD_HL_BC;
                // LD_hl(0x0);
                bc->index = 0x0;
            }
            // RET;
            return;
        }

    // retain:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // INC_hl;
        bc->jumptableIndex++;
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x8);
        bc->var1 = 0x8;
    } fallthrough;

    case 2: {
    // two:
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto spawn_egg;
        if(bc->var1 != 0) {
            // DEC_hl;
            bc->var1--;
            // RET;
            return;
        }

    // spawn_egg:
        // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
        // ADD_HL_BC;
        // DEC_hl;
        bc->jumptableIndex--;
        // PUSH_BC;
        // depixel4(12, 13, 0, 4);
        // LD_A(SPRITE_ANIM_INDEX_SLOTS_EGG);
        // CALL(aInitSpriteAnimStruct);
        InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_SLOTS_EGG, pixel4(12, 13, 0, 4));
        // POP_BC;
        // RET;
    } return;
    }
}

void Slots_WaitSFX(void){
    // PUSH_BC;
    // LD_C(16);
    // CALL(aDelayFrames);
    DelayFrames_Conv(16);
    // POP_BC;
    // RET;
}

void Slots_PlaySFX(uint16_t sfx){
    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // CALL(aPlaySFX);
    PlaySFX_Conv(sfx);
    // POP_DE;
    // RET;
}

//  The first three positions are repeated to
//  avoid needing to check indices when copying.
const uint8_t Reel1Tilemap[] = {
    SLOTS_SEVEN,  //  0
    SLOTS_CHERRY,  //  1
    SLOTS_STARYU,  //  2
    SLOTS_PIKACHU,  //  3
    SLOTS_SQUIRTLE,  //  4
    SLOTS_SEVEN,  //  5
    SLOTS_CHERRY,  //  6
    SLOTS_STARYU,  //  7
    SLOTS_PIKACHU,  //  8
    SLOTS_SQUIRTLE,  //  9
    SLOTS_POKEBALL,  // 10
    SLOTS_CHERRY,  // 11
    SLOTS_STARYU,  // 12
    SLOTS_PIKACHU,  // 13
    SLOTS_SQUIRTLE,  // 14
    SLOTS_SEVEN,  //  0
    SLOTS_CHERRY,  //  1
    SLOTS_STARYU,  //  2
};

const uint8_t Reel2Tilemap[] = {
    SLOTS_SEVEN,  //  0
    SLOTS_PIKACHU,  //  1
    SLOTS_CHERRY,  //  2
    SLOTS_SQUIRTLE,  //  3
    SLOTS_STARYU,  //  4
    SLOTS_POKEBALL,  //  5
    SLOTS_PIKACHU,  //  6
    SLOTS_CHERRY,  //  7
    SLOTS_SQUIRTLE,  //  8
    SLOTS_STARYU,  //  9
    SLOTS_POKEBALL,  // 10
    SLOTS_PIKACHU,  // 11
    SLOTS_CHERRY,  // 12
    SLOTS_SQUIRTLE,  // 13
    SLOTS_STARYU,  // 14
    SLOTS_SEVEN,  //  0
    SLOTS_PIKACHU,  //  1
    SLOTS_CHERRY,  //  2
};

const uint8_t Reel3Tilemap[] = {
    SLOTS_SEVEN,  //  0
    SLOTS_PIKACHU,  //  1
    SLOTS_CHERRY,  //  2
    SLOTS_SQUIRTLE,  //  3
    SLOTS_STARYU,  //  4
    SLOTS_PIKACHU,  //  5
    SLOTS_CHERRY,  //  6
    SLOTS_SQUIRTLE,  //  7
    SLOTS_STARYU,  //  8
    SLOTS_PIKACHU,  //  9
    SLOTS_POKEBALL,  // 10
    SLOTS_CHERRY,  // 11
    SLOTS_SQUIRTLE,  // 12
    SLOTS_STARYU,  // 13
    SLOTS_PIKACHU,  // 14
    SLOTS_SEVEN,  //  0
    SLOTS_PIKACHU,  //  1
    SLOTS_CHERRY,  //  2
};

const char SlotsTilemap[] = "gfx/slots/slots.tilemap";

const char Slots1LZ[] = "gfx/slots/slots_1.png";
const char Slots2LZ[] = "gfx/slots/slots_2.png";
const char Slots3LZ[] = "gfx/slots/slots_3.png";
