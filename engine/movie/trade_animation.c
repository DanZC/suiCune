#include "../../constants.h"
#include "trade_animation.h"
#include "../../home/audio.h"
#include "../../home/copy.h"
#include "../../home/gfx.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/video.h"
#include "../../home/print_text.h"
#include "../../home/clear_sprites.h"
#include "../../home/sprite_anims.h"
#include "../../home/palettes.h"
#include "../../home/pokemon.h"
#include "../../home/lcd.h"
#include "../../home/names.h"
#include "../../charmap.h"
#include "../gfx/place_graphic.h"
#include "../gfx/trademon_frontpic.h"
#include "../gfx/sprites.h"
#include "../gfx/load_pics.h"
#include "../gfx/mon_icons.h"
#include "../../data/text/common.h"

#define TRADEANIM_RIGHT_ARROW (0xed)  //  ▶ $ed
#define TRADEANIM_LEFT_ARROW (0xee)  //  ▼ $ee

typedef void (*const tradeanim_func_t)(void);
const uint8_t* gTradeAnimAddress;

//  TradeAnim_TubeAnimJumptable.Jumptable indexes
enum {
    TRADEANIMSTATE_0,  // 0
    TRADEANIMSTATE_1,  // 1
    TRADEANIMSTATE_2,  // 2
    TRADEANIMSTATE_3,  // 3
};
#define TRADEANIMJUMPTABLE_LENGTH (TRADEANIMSTATE_3 + 1)

// tradeanim: MACRO
//     db (\1_TradeCmd - DoTradeAnimation.Jumptable) / 2
// ENDM
#define tradeanim(x) x##_TradeCmd

// add_tradeanim: MACRO
// \1_TradeCmd:
//     dw \1
// ENDM
#define add_tradeanim(x) [x##_TradeCmd] = &x
enum {
    tradeanim(TradeAnim_AdvanceScriptPointer),  // 00
    tradeanim(TradeAnim_ShowGivemonData),  // 01
    tradeanim(TradeAnim_ShowGetmonData),  // 02
    tradeanim(TradeAnim_EnterLinkTube1),  // 03
    tradeanim(TradeAnim_EnterLinkTube2),  // 04
    tradeanim(TradeAnim_ExitLinkTube),  // 05
    tradeanim(TradeAnim_TubeToOT1),  // 06
    tradeanim(TradeAnim_TubeToOT2),  // 07
    tradeanim(TradeAnim_TubeToOT3),  // 08
    tradeanim(TradeAnim_TubeToOT4),  // 09
    tradeanim(TradeAnim_TubeToOT5),  // 0a
    tradeanim(TradeAnim_TubeToOT6),  // 0b
    tradeanim(TradeAnim_TubeToOT7),  // 0c
    tradeanim(TradeAnim_TubeToOT8),  // 0d
    tradeanim(TradeAnim_TubeToPlayer1),  // 0e
    tradeanim(TradeAnim_TubeToPlayer2),  // 0f
    tradeanim(TradeAnim_TubeToPlayer3),  // 10
    tradeanim(TradeAnim_TubeToPlayer4),  // 11
    tradeanim(TradeAnim_TubeToPlayer5),  // 12
    tradeanim(TradeAnim_TubeToPlayer6),  // 13
    tradeanim(TradeAnim_TubeToPlayer7),  // 14
    tradeanim(TradeAnim_TubeToPlayer8),  // 15
    tradeanim(TradeAnim_SentToOTText),  // 16
    tradeanim(TradeAnim_OTBidsFarewell),  // 17
    tradeanim(TradeAnim_TakeCareOfText),  // 18
    tradeanim(TradeAnim_OTSendsText1),  // 19
    tradeanim(TradeAnim_OTSendsText2),  // 1a
    tradeanim(TradeAnim_SetupGivemonScroll),  // 1b
    tradeanim(TradeAnim_DoGivemonScroll),  // 1c
    tradeanim(TradeAnim_FrontpicScrollStart),  // 1d
    tradeanim(TradeAnim_TextboxScrollStart),  // 1e
    tradeanim(TradeAnim_ScrollOutRight),  // 1f
    tradeanim(TradeAnim_ScrollOutRight2),  // 20
    tradeanim(TradeAnim_Wait80),  // 21
    tradeanim(TradeAnim_Wait40),  // 22
    tradeanim(TradeAnim_RockingBall),  // 23
    tradeanim(TradeAnim_DropBall),  // 24
    tradeanim(TradeAnim_WaitAnim),  // 25
    tradeanim(TradeAnim_WaitAnim2),  // 26
    tradeanim(TradeAnim_Poof),  // 27
    tradeanim(TradeAnim_BulgeThroughTube),  // 28
    tradeanim(TradeAnim_GiveTrademonSFX),  // 29
    tradeanim(TradeAnim_GetTrademonSFX),  // 2a
    tradeanim(TradeAnim_End),  // 2b
    tradeanim(TradeAnim_AnimateFrontpic),  // 2c
    tradeanim(TradeAnim_Wait96),  // 2d
    tradeanim(TradeAnim_Wait80IfOTEgg),  // 2e
    tradeanim(TradeAnim_Wait180IfOTEgg),  // 2f
};

static const tradeanim_func_t DoTradeAnimation_Jumptable[] = {
    add_tradeanim(TradeAnim_AdvanceScriptPointer),  // 00
    add_tradeanim(TradeAnim_ShowGivemonData),  // 01
    add_tradeanim(TradeAnim_ShowGetmonData),  // 02
    add_tradeanim(TradeAnim_EnterLinkTube1),  // 03
    add_tradeanim(TradeAnim_EnterLinkTube2),  // 04
    add_tradeanim(TradeAnim_ExitLinkTube),  // 05
    add_tradeanim(TradeAnim_TubeToOT1),  // 06
    add_tradeanim(TradeAnim_TubeToOT2),  // 07
    add_tradeanim(TradeAnim_TubeToOT3),  // 08
    add_tradeanim(TradeAnim_TubeToOT4),  // 09
    add_tradeanim(TradeAnim_TubeToOT5),  // 0a
    add_tradeanim(TradeAnim_TubeToOT6),  // 0b
    add_tradeanim(TradeAnim_TubeToOT7),  // 0c
    add_tradeanim(TradeAnim_TubeToOT8),  // 0d
    add_tradeanim(TradeAnim_TubeToPlayer1),  // 0e
    add_tradeanim(TradeAnim_TubeToPlayer2),  // 0f
    add_tradeanim(TradeAnim_TubeToPlayer3),  // 10
    add_tradeanim(TradeAnim_TubeToPlayer4),  // 11
    add_tradeanim(TradeAnim_TubeToPlayer5),  // 12
    add_tradeanim(TradeAnim_TubeToPlayer6),  // 13
    add_tradeanim(TradeAnim_TubeToPlayer7),  // 14
    add_tradeanim(TradeAnim_TubeToPlayer8),  // 15
    add_tradeanim(TradeAnim_SentToOTText),  // 16
    add_tradeanim(TradeAnim_OTBidsFarewell),  // 17
    add_tradeanim(TradeAnim_TakeCareOfText),  // 18
    add_tradeanim(TradeAnim_OTSendsText1),  // 19
    add_tradeanim(TradeAnim_OTSendsText2),  // 1a
    add_tradeanim(TradeAnim_SetupGivemonScroll),  // 1b
    add_tradeanim(TradeAnim_DoGivemonScroll),  // 1c
    add_tradeanim(TradeAnim_FrontpicScrollStart),  // 1d
    add_tradeanim(TradeAnim_TextboxScrollStart),  // 1e
    add_tradeanim(TradeAnim_ScrollOutRight),  // 1f
    add_tradeanim(TradeAnim_ScrollOutRight2),  // 20
    add_tradeanim(TradeAnim_Wait80),  // 21
    add_tradeanim(TradeAnim_Wait40),  // 22
    add_tradeanim(TradeAnim_RockingBall),  // 23
    add_tradeanim(TradeAnim_DropBall),  // 24
    add_tradeanim(TradeAnim_WaitAnim),  // 25
    add_tradeanim(TradeAnim_WaitAnim2),  // 26
    add_tradeanim(TradeAnim_Poof),  // 27
    add_tradeanim(TradeAnim_BulgeThroughTube),  // 28
    add_tradeanim(TradeAnim_GiveTrademonSFX),  // 29
    add_tradeanim(TradeAnim_GetTrademonSFX),  // 2a
    add_tradeanim(TradeAnim_End),  // 2b
    add_tradeanim(TradeAnim_AnimateFrontpic),  // 2c
    add_tradeanim(TradeAnim_Wait96),  // 2d
    add_tradeanim(TradeAnim_Wait80IfOTEgg),  // 2e
    add_tradeanim(TradeAnim_Wait180IfOTEgg),  // 2f
};

void TradeAnimation(void){
    static const uint8_t script[] = {
        tradeanim(TradeAnim_SetupGivemonScroll),
        tradeanim(TradeAnim_ShowGivemonData),
        tradeanim(TradeAnim_DoGivemonScroll),
        tradeanim(TradeAnim_Wait80),
        tradeanim(TradeAnim_Wait96),
        tradeanim(TradeAnim_Poof),
        tradeanim(TradeAnim_RockingBall),
        tradeanim(TradeAnim_EnterLinkTube1),
        tradeanim(TradeAnim_WaitAnim),
        tradeanim(TradeAnim_BulgeThroughTube),
        tradeanim(TradeAnim_WaitAnim),
        tradeanim(TradeAnim_TextboxScrollStart),
        tradeanim(TradeAnim_GiveTrademonSFX),
        tradeanim(TradeAnim_TubeToOT1),
        tradeanim(TradeAnim_SentToOTText),
        tradeanim(TradeAnim_ScrollOutRight),

        tradeanim(TradeAnim_OTSendsText1),
        tradeanim(TradeAnim_OTBidsFarewell),
        tradeanim(TradeAnim_Wait40),
        tradeanim(TradeAnim_ScrollOutRight),
        tradeanim(TradeAnim_GetTrademonSFX),
        tradeanim(TradeAnim_TubeToPlayer1),
        tradeanim(TradeAnim_EnterLinkTube1),
        tradeanim(TradeAnim_DropBall),
        tradeanim(TradeAnim_ExitLinkTube),
        tradeanim(TradeAnim_WaitAnim),
        tradeanim(TradeAnim_ShowGetmonData),
        tradeanim(TradeAnim_Poof),
        tradeanim(TradeAnim_WaitAnim),
        tradeanim(TradeAnim_FrontpicScrollStart),
        tradeanim(TradeAnim_AnimateFrontpic),
        tradeanim(TradeAnim_Wait80IfOTEgg),
        tradeanim(TradeAnim_TextboxScrollStart),
        tradeanim(TradeAnim_TakeCareOfText),
        tradeanim(TradeAnim_ScrollOutRight),
        tradeanim(TradeAnim_End),
    };
    // XOR_A_A;
    // LD_addr_A(wUnusedTradeAnimPlayEvolutionMusic);
    wram->wUnusedTradeAnimPlayEvolutionMusic = FALSE;
    // LD_HL(wPlayerTrademonSenderName);
    // LD_DE(wOTTrademonSenderName);
    // CALL(aLinkTradeAnim_LoadTradePlayerNames);
    LinkTradeAnim_LoadTradePlayerNames(wram->wPlayerTrademon.senderName, wram->wOTTrademon.senderName);
    // LD_HL(wPlayerTrademonSpecies);
    // LD_DE(wOTTrademonSpecies);
    // CALL(aLinkTradeAnim_LoadTradeMonSpecies);
    LinkTradeAnim_LoadTradeMonSpecies(wram->wPlayerTrademon.species, wram->wOTTrademon.species);
    // LD_DE(mTradeAnimation_script);
    // JR(mRunTradeAnimScript);
    return RunTradeAnimScript(script);
}

void TradeAnimationPlayer2(void){
    static const uint8_t script[] = {
        tradeanim(TradeAnim_OTSendsText2),
        tradeanim(TradeAnim_OTBidsFarewell),
        tradeanim(TradeAnim_Wait40),
        tradeanim(TradeAnim_ScrollOutRight),
        tradeanim(TradeAnim_GetTrademonSFX),
        tradeanim(TradeAnim_TubeToOT1),
        tradeanim(TradeAnim_EnterLinkTube1),
        tradeanim(TradeAnim_DropBall),
        tradeanim(TradeAnim_ExitLinkTube),
        tradeanim(TradeAnim_WaitAnim),
        tradeanim(TradeAnim_ShowGetmonData),
        tradeanim(TradeAnim_Poof),
        tradeanim(TradeAnim_WaitAnim),
        tradeanim(TradeAnim_FrontpicScrollStart),
        tradeanim(TradeAnim_AnimateFrontpic),
        tradeanim(TradeAnim_Wait180IfOTEgg),
        tradeanim(TradeAnim_TextboxScrollStart),
        tradeanim(TradeAnim_TakeCareOfText),
        tradeanim(TradeAnim_ScrollOutRight),

        tradeanim(TradeAnim_SetupGivemonScroll),
        tradeanim(TradeAnim_ShowGivemonData),
        tradeanim(TradeAnim_DoGivemonScroll),
        tradeanim(TradeAnim_Wait40),
        tradeanim(TradeAnim_Poof),
        tradeanim(TradeAnim_RockingBall),
        tradeanim(TradeAnim_EnterLinkTube1),
        tradeanim(TradeAnim_WaitAnim),
        tradeanim(TradeAnim_BulgeThroughTube),
        tradeanim(TradeAnim_WaitAnim),
        tradeanim(TradeAnim_TextboxScrollStart),
        tradeanim(TradeAnim_GiveTrademonSFX),
        tradeanim(TradeAnim_TubeToPlayer1),
        tradeanim(TradeAnim_SentToOTText),
        tradeanim(TradeAnim_ScrollOutRight),
        tradeanim(TradeAnim_End),
    };
    // XOR_A_A;
    // LD_addr_A(wUnusedTradeAnimPlayEvolutionMusic);
    wram->wUnusedTradeAnimPlayEvolutionMusic = FALSE;
    // LD_HL(wOTTrademonSenderName);
    // LD_DE(wPlayerTrademonSenderName);
    // CALL(aLinkTradeAnim_LoadTradePlayerNames);
    LinkTradeAnim_LoadTradePlayerNames(wram->wOTTrademon.senderName, wram->wPlayerTrademon.senderName);
    // LD_HL(wOTTrademonSpecies);
    // LD_DE(wPlayerTrademonSpecies);
    // CALL(aLinkTradeAnim_LoadTradeMonSpecies);
    LinkTradeAnim_LoadTradeMonSpecies(wram->wOTTrademon.species, wram->wPlayerTrademon.species);
    // LD_DE(mTradeAnimationPlayer2_script);
    // JR(mRunTradeAnimScript);
    return RunTradeAnimScript(script);
}

static void RunTradeAnimScript_TradeAnimLayout(void) {
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto NotCGB;
    if(hram->hCGB) {
        // LD_A(0x1);
        // LDH_addr_A(rVBK);
        // LD_HL(vTiles0);
        // LD_BC(VRAM_End - VRAM_Begin);
        // XOR_A_A;
        // CALL(aByteFill);
        ByteFill_Conv2(vram->vTiles3, VRAM_End - VRAM_Begin, 0x0);
        // LD_A(0x0);
        // LDH_addr_A(rVBK);
    }

// NotCGB:
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(VRAM_End - vBGMap0);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(bgcoord(0, 0, vram->vBGMap0), VRAM_End - vBGMap0, 0x7f);
    // LD_HL(mTradeGameBoyLZ);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // CALL(aDecompress);
// Loading gameboy in pieces because it doesn't look correct otherwise.
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x31, TradeGameBoyLZ, 0, 2);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x33, TradeGameBoyLZ, 5, 4);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x37, TradeGameBoyLZ, 10, 2);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x39, TradeGameBoyLZ, 13, 2);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x3b, TradeGameBoyLZ, 16, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x3c, TradeGameBoyLZ, 18, 3);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x3f, TradeGameBoyLZ, 22, 5);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x44, TradeGameBoyLZ, 28, 4);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x48, TradeGameBoyLZ, 33, 3);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x4b, TradeGameBoyLZ, 38, 6);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x51, TradeGameBoyLZ, 46, 2);
// Loading link cable separately since it's in a separate file for some reason.
    LoadPNG2bppAssetToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x53, TradeLinkCableGFX);
    // LD_HL(mTradeArrowRightGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * TRADEANIM_RIGHT_ARROW);
    // LD_BC(1 * LEN_2BPP_TILE);
    // LD_A(BANK(aTradeArrowRightGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * TRADEANIM_RIGHT_ARROW, TradeArrowRightGFX, 0, 1);
    // LD_HL(mTradeArrowLeftGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * TRADEANIM_LEFT_ARROW);
    // LD_BC(1 * LEN_2BPP_TILE);
    // LD_A(BANK(aTradeArrowLeftGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * TRADEANIM_LEFT_ARROW, TradeArrowLeftGFX, 0, 1);
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0x0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // FARCALL(aGetTrademonFrontpic);
    GetTrademonFrontpic();
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // CALL(aLoadTradeBallAndCableGFX);
    LoadTradeBallAndCableGFX();
    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_HL(wPlayerTrademonDVs);
    // LD_DE(vTiles0);
    // CALL(aTradeAnim_GetFrontpic);
    TradeAnim_GetFrontpic(vram->vTiles0, wram->wPlayerTrademon.dvs, wram->wPlayerTrademon.species);
    // LD_A_addr(wOTTrademonSpecies);
    // LD_HL(wOTTrademonDVs);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x31);
    // CALL(aTradeAnim_GetFrontpic);
    TradeAnim_GetFrontpic(vram->vTiles0 + LEN_2BPP_TILE * 0x31, wram->wOTTrademon.dvs, wram->wOTTrademon.species);
    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_DE(wPlayerTrademonSpeciesName);
    // CALL(aTradeAnim_GetNicknamename);
    TradeAnim_GetNicknamename(wram->wPlayerTrademon.speciesName, wram->wPlayerTrademon.species);
    // LD_A_addr(wOTTrademonSpecies);
    // LD_DE(wOTTrademonSpeciesName);
    // CALL(aTradeAnim_GetNicknamename);
    TradeAnim_GetNicknamename(wram->wOTTrademon.speciesName, wram->wOTTrademon.species);
    // CALL(aTradeAnim_NormalPals);
    TradeAnim_NormalPals();
    // RET;
}

void RunTradeAnimScript(const uint8_t* de){
    // LD_HL(wTradeAnimAddress);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gTradeAnimAddress = de;
    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    uint8_t mapAnims = hram->hMapAnims;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = FALSE;
    // LD_HL(wVramState);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // RES_hl(0);
    bit_reset(wram->wVramState, 0);
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aRunTradeAnimScript_TradeAnimLayout);
    RunTradeAnimScript_TradeAnimLayout();
    // LD_A_addr(wUnusedTradeAnimPlayEvolutionMusic);
    // AND_A_A;
    // IF_NZ goto anim_loop;
    if(!wram->wUnusedTradeAnimPlayEvolutionMusic) {
        // LD_DE(MUSIC_EVOLUTION);
        // CALL(aPlayMusic2);
        PlayMusic2_Conv(MUSIC_EVOLUTION);
    }

    bool done;
    do {
    // anim_loop:
        // CALL(aDoTradeAnimation);
        done = DoTradeAnimation();
        // IF_NC goto anim_loop;
    } while(!done);
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = mapAnims;
    // RET;
    return;
}

static void DoTradeAnimation_DoTradeAnimCommand(void) {
    //jumptable ['.Jumptable', 'wJumptableIndex']
    DoTradeAnimation_Jumptable[wram->wJumptableIndex]();
}

bool DoTradeAnimation(void){
    // LD_A_addr(wJumptableIndex);
    // BIT_A(7);
    // IF_NZ goto finished;
    if(bit_test(wram->wJumptableIndex, 7)) {
    // finished:
        // CALL(aLoadStandardFont);
        LoadStandardFont_Conv();
        // SCF;
        // RET;
        return true;
    }
    // CALL(aDoTradeAnimation_DoTradeAnimCommand);
    DoTradeAnimation_DoTradeAnimCommand();
    // CALLFAR(aPlaySpriteAnimations);
    {
        bank_push(BANK(aPlaySpriteAnimations));
        PlaySpriteAnimations_Conv();
        bank_pop;
    }
    // LD_HL(wFrameCounter2);
    // INC_hl;
    wram->wFrameCounter2++;
    // CALL(aDelayFrame);
    DelayFrame();
    // AND_A_A;
    // RET;
    return false;
}

void TradeAnim_IncrementJumptableIndex(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

void TradeAnim_AdvanceScriptPointer(void){
    // LD_HL(wTradeAnimAddress);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // LD_A_de;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = *gTradeAnimAddress;
    // INC_DE;
    // LD_hl_D;
    // DEC_HL;
    // LD_hl_E;
    gTradeAnimAddress++;
    // RET;
}

void TradeAnim_End(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

void TradeAnim_TubeToOT1(void){
    // LD_A(TRADEANIM_RIGHT_ARROW);
    // CALL(aTradeAnim_PlaceTrademonStatsOnTubeAnim);
    TradeAnim_PlaceTrademonStatsOnTubeAnim(TRADEANIM_RIGHT_ARROW);
    // LD_A_addr(wLinkTradeSendmonSpecies);
    // LD_addr_A(wTempIconSpecies);
    wram->wTempIconSpecies = wram->wLinkTradeSendmonSpecies;
    // XOR_A_A;
    // depixel4(5, 11, 4, 0);
    // LD_B(0x0);
    // JR(mTradeAnim_InitTubeAnim);
    return TradeAnim_InitTubeAnim(pixel4(5, 11, 4, 0), 0x0, TRADEANIMSTATE_0);
}

void TradeAnim_TubeToPlayer1(void){
    // LD_A(TRADEANIM_LEFT_ARROW);
    // CALL(aTradeAnim_PlaceTrademonStatsOnTubeAnim);
    TradeAnim_PlaceTrademonStatsOnTubeAnim(TRADEANIM_LEFT_ARROW);
    // LD_A_addr(wLinkTradeGetmonSpecies);
    // LD_addr_A(wTempIconSpecies);
    wram->wTempIconSpecies = wram->wLinkTradeGetmonSpecies;
    // LD_A(TRADEANIMSTATE_2);
    // depixel4(9, 18, 4, 4);
    // LD_B(0x4);
    return TradeAnim_InitTubeAnim(pixel4(9, 18, 4, 4), 0x4, TRADEANIMSTATE_2);
}

void TradeAnim_InitTubeAnim(uint16_t de, uint8_t b, uint8_t a){
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_BC;
    // PUSH_DE;

    // PUSH_AF;
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // hlbgcoord(20, 3, vBGMap0);
    // LD_BC(12);
    // LD_A(0x60);
    // CALL(aByteFill);
    ByteFill_Conv2(bgcoord(20, 3, vram->vBGMap0), 12, 0x60);
    // POP_AF;

    // CALL(aTradeAnim_TubeAnimJumptable);
    TradeAnim_TubeAnimJumptable(a);

    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x70);
    // LDH_addr_A(hWY);
    hram->hWY = 0x70;
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // CALL(aLoadTradeBubbleGFX);
    LoadTradeBubbleGFX();

    // POP_DE;
    // LD_A(SPRITE_ANIM_INDEX_TRADEMON_ICON);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_TRADEMON_ICON, de);

    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // POP_BC;
    // LD_hl_B;
    bc->jumptableIndex = b;

    // POP_DE;
    // LD_A(SPRITE_ANIM_INDEX_TRADEMON_BUBBLE);
    // CALL(aInitSpriteAnimStruct);
    bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_TRADEMON_BUBBLE, de);

    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // POP_BC;
    // LD_hl_B;
    bc->jumptableIndex = b;

    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_TRADE_TUBE);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_TRADE_TUBE);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // LD_A(0b11010000);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0_Conv(0b11010000);

    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // LD_A(92);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 92;
    // RET;
}

void TradeAnim_TubeToOT2(void){
    // CALL(aTradeAnim_FlashBGPals);
    TradeAnim_FlashBGPals();
    // LDH_A_addr(hSCX);
    // ADD_A(0x2);
    // LDH_addr_A(hSCX);
    hram->hSCX += 0x2;
    // CP_A(0x50);
    // RET_NZ ;
    if(hram->hSCX != 0x50)
        return;
    // LD_A(TRADEANIMSTATE_1);
    // CALL(aTradeAnim_TubeAnimJumptable);
    TradeAnim_TubeAnimJumptable(TRADEANIMSTATE_1);
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;
}

void TradeAnim_TubeToOT3(void){
    // CALL(aTradeAnim_FlashBGPals);
    TradeAnim_FlashBGPals();
    // LDH_A_addr(hSCX);
    // ADD_A(0x2);
    // LDH_addr_A(hSCX);
    hram->hSCX += 0x2;
    // CP_A(0xa0);
    // RET_NZ ;
    if(hram->hSCX != 0xa0)
        return;
    // LD_A(TRADEANIMSTATE_2);
    // CALL(aTradeAnim_TubeAnimJumptable);
    TradeAnim_TubeAnimJumptable(TRADEANIMSTATE_2);
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;

}

void TradeAnim_TubeToOT4(void){
    // CALL(aTradeAnim_FlashBGPals);
    TradeAnim_FlashBGPals();
    // LDH_A_addr(hSCX);
    // ADD_A(0x2);
    // LDH_addr_A(hSCX);
    hram->hSCX += 0x2;
    // AND_A_A;
    // RET_NZ ;
    if(hram->hSCX != 0)
        return;
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;

}

void TradeAnim_TubeToPlayer3(void){
    // CALL(aTradeAnim_FlashBGPals);
    TradeAnim_FlashBGPals();
    // LDH_A_addr(hSCX);
    // SUB_A(0x2);
    // LDH_addr_A(hSCX);
    hram->hSCX -= 0x2;
    // CP_A(0xb0);
    // RET_NZ ;
    if(hram->hSCX != 0xb0)
        return;
    // LD_A(TRADEANIMSTATE_1);
    // CALL(aTradeAnim_TubeAnimJumptable);
    TradeAnim_TubeAnimJumptable(TRADEANIMSTATE_1);
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;

}

void TradeAnim_TubeToPlayer4(void){
    // CALL(aTradeAnim_FlashBGPals);
    TradeAnim_FlashBGPals();
    // LDH_A_addr(hSCX);
    // SUB_A(0x2);
    // LDH_addr_A(hSCX);
    hram->hSCX -= 0x2;
    // CP_A(0x60);
    // RET_NZ ;
    if(hram->hSCX != 0x60)
        return;
    // XOR_A_A;  // TRADEANIMSTATE_0
    // CALL(aTradeAnim_TubeAnimJumptable);
    TradeAnim_TubeAnimJumptable(TRADEANIMSTATE_0);
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;
}

void TradeAnim_TubeToPlayer5(void){
    // CALL(aTradeAnim_FlashBGPals);
    TradeAnim_FlashBGPals();
    // LDH_A_addr(hSCX);
    // SUB_A(0x2);
    // LDH_addr_A(hSCX);
    hram->hSCX -= 0x2;
    // AND_A_A;
    // RET_NZ ;
    if(hram->hSCX != 0)
        return;
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;

}

void TradeAnim_TubeToOT6(void){
    return TradeAnim_TubeToPlayer6();
}

void TradeAnim_TubeToPlayer6(void){
    // LD_A(128);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 128;
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;

}

void TradeAnim_TubeToOT8(void){
    return TradeAnim_TubeToPlayer8();
}

void TradeAnim_TubeToPlayer8(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALLFAR(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(VRAM_End - vBGMap0);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(bgcoord(0, 0, vram->vBGMap0), VRAM_End - vBGMap0, 0x7f);
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x0;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // CALL(aLoadTradeBallAndCableGFX);
    LoadTradeBallAndCableGFX();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aTradeAnim_NormalPals);
    TradeAnim_NormalPals();
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_TubeToOT5(void){
    return TradeAnim_TubeToOT7();
}

void TradeAnim_TubeToOT7(void){
    return TradeAnim_TubeToPlayer2();
}

void TradeAnim_TubeToPlayer2(void){
    return TradeAnim_TubeToPlayer7();
}

void TradeAnim_TubeToPlayer7(void){
    // CALL(aTradeAnim_FlashBGPals);
    TradeAnim_FlashBGPals();
    // LD_HL(wFrameCounter);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto done;
    if(wram->wFrameCounter == 0) {
    // done:
        // CALL(aTradeAnim_IncrementJumptableIndex);
        TradeAnim_IncrementJumptableIndex();
        // RET;
        return;
    }
    // DEC_hl;
    wram->wFrameCounter--;
    // RET;
}

void TradeAnim_GiveTrademonSFX(void){
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // LD_DE(SFX_GIVE_TRADEMON);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_GIVE_TRADEMON);
    // RET;
}

void TradeAnim_GetTrademonSFX(void){
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // LD_DE(SFX_GET_TRADEMON);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_GET_TRADEMON);
    // RET;
}

void TradeAnim_TubeAnimJumptable(uint8_t state){
    // maskbits(TRADEANIMJUMPTABLE_LENGTH, 0);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mTradeAnim_TubeAnimJumptable_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;

// Jumptable:
//  entries correspond to TRADEANIMSTATE_* constants
    switch(state & 3) {
        //dw ['.Zero'];
        case TRADEANIMSTATE_0:
        case TRADEANIMSTATE_3:
        // Zero:
        // Three:
            // CALL(aTradeAnim_BlankTilemap);
            TradeAnim_BlankTilemap();
            // hlcoord(9, 3, wTilemap);
            // LD_hl(0x5b);
            *coord(9, 3, wram->wTilemap) = 0x5b;
            // INC_HL;
            // LD_BC(10);
            // LD_A(0x60);
            // CALL(aByteFill);
            ByteFill_Conv2(coord(10, 3, wram->wTilemap), 10, 0x60);
            // hlcoord(3, 2, wTilemap);
            // CALL(aTradeAnim_CopyTradeGameBoyTilemap);
            TradeAnim_CopyTradeGameBoyTilemap(coord(3, 2, wram->wTilemap));
            // RET;
            return;
        //dw ['.One'];
        case TRADEANIMSTATE_1:
        // One:
            // CALL(aTradeAnim_BlankTilemap);
            TradeAnim_BlankTilemap();
            // hlcoord(0, 3, wTilemap);
            // LD_BC(SCREEN_WIDTH);
            // LD_A(0x60);
            // CALL(aByteFill);
            ByteFill_Conv2(coord(0, 3, wram->wTilemap), SCREEN_WIDTH, 0x60);
            // RET;
            return;
        //dw ['.Two'];
        case TRADEANIMSTATE_2: {
        // Two:
            // CALL(aTradeAnim_BlankTilemap);
            TradeAnim_BlankTilemap();
            // hlcoord(0, 3, wTilemap);
            // LD_BC(0x11);
            // LD_A(0x60);
            // CALL(aByteFill);
            ByteFill_Conv2(coord(0, 3, wram->wTilemap), 0x11, 0x60);
            // hlcoord(17, 3, wTilemap);
            uint8_t* hl = coord(17, 3, wram->wTilemap);
            // LD_A(0x5d);
            // LD_hl_A;
            *hl = 0x5d;

            // LD_A(0x61);
            // LD_DE(SCREEN_WIDTH);
            // LD_C(0x3);
            uint8_t c = 0x3;

            do {
            // loop:
                // ADD_HL_DE;
                hl += SCREEN_WIDTH;
                // LD_hl_A;
                *hl = 0x61;
                // DEC_C;
                // IF_NZ goto loop;
            } while(--c != 0);

            // ADD_HL_DE;
            hl += SCREEN_WIDTH;
            // LD_A(0x5f);
            // LD_hld_A;
            *(hl--) = 0x5f;
            // LD_A(0x5b);
            // LD_hl_A;
            *hl = 0x5b;
            // hlcoord(10, 6, wTilemap);
            // CALL(aTradeAnim_CopyTradeGameBoyTilemap);
            TradeAnim_CopyTradeGameBoyTilemap(coord(10, 6, wram->wTilemap));
            // RET;
        } return;
        //dw ['.Three'];
    }

}

void TradeAnim_CopyTradeGameBoyTilemap(uint8_t* hl){
    // LD_DE(mTradeGameBoyTilemap);
    asset_s de = LoadAsset(TradeGameBoyTilemap);
    // LD_BC((8 << 8) | 6);
    // CALL(aTradeAnim_CopyBoxFromDEtoHL);
    TradeAnim_CopyBoxFromDEtoHL(hl, (uint8_t*)de.ptr, 8, 6);
    // RET;
    FreeAsset(de);
}

void TradeAnim_PlaceTrademonStatsOnTubeAnim(uint8_t a){
    // PUSH_AF;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aWaitTop);
    WaitTop_Conv();
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap1;
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH);
    // LD_A(0x7a);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_WIDTH, 0x7a);
    // hlcoord(0, 1, wTilemap);
    // LD_DE(wLinkPlayer1Name);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wLinkPlayer1Name, coord(0, 1, wram->wTilemap));
    // LD_HL(wLinkPlayer2Name);
    uint8_t* hl = wram->wLinkPlayer2Name;
    // LD_DE(0);
    int16_t de = 0;

    while(1) {
    // find_name_end_loop:
        // LD_A_hli;
        uint8_t c = *(hl++);
        // CP_A(0x50);
        // IF_Z goto done;
        if(c == 0x50)
            break;
        // DEC_DE;
        --de;
        // goto find_name_end_loop;
    }


// done:
    // hlcoord(0, 4, wTilemap);
    // ADD_HL_DE;
    // LD_DE(wLinkPlayer2Name);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wLinkPlayer2Name, coord(0, 4, wram->wTilemap) + de);
    // hlcoord(7, 2, wTilemap);
    // LD_BC(6);
    // POP_AF;
    // CALL(aByteFill);
    ByteFill_Conv2(coord(7, 2, wram->wTilemap), 6, a);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aWaitTop);
    WaitTop_Conv();
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap0;
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // RET;
}

void TradeAnim_EnterLinkTube1(void){
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aWaitTop);
    WaitTop_Conv();
    // LD_A(0xa0);
    // LDH_addr_A(hSCX);
    hram->hSCX = 0xa0;
    // CALL(aDelayFrame);
    DelayFrame();
    // hlcoord(8, 2, wTilemap);
    // LD_DE(mTradeLinkTubeTilemap);
    asset_s de = LoadAsset(TradeLinkTubeTilemap);
    // LD_BC((3 << 8) | 12);
    // CALL(aTradeAnim_CopyBoxFromDEtoHL);
    TradeAnim_CopyBoxFromDEtoHL(coord(8, 2, wram->wTilemap), (uint8_t*)de.ptr, 3, 12);
    FreeAsset(de);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_TRADE_TUBE);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_TRADE_TUBE);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // LD_DE((0b11100100 << 8) | 0b11100100);  // 3,2,1,0, 3,2,1,0
    // CALL(aDmgToCgbObjPals);
    DmgToCgbObjPals_Conv(0b11100100, 0b11100100);
    // LD_DE(SFX_POTION);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_POTION);
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;

}

void TradeAnim_EnterLinkTube2(void){
    // LDH_A_addr(hSCX);
    // AND_A_A;
    // IF_Z goto done;
    if(hram->hSCX == 0) {
    // done:
        // LD_C(80);
        // CALL(aDelayFrames);
        DelayFrames_Conv(80);
        // CALL(aTradeAnim_AdvanceScriptPointer);
        TradeAnim_AdvanceScriptPointer();
        // RET;
        return;
    }
    // ADD_A(0x4);
    // LDH_addr_A(hSCX);
    hram->hSCX += 0x4;
    // RET;
}

void TradeAnim_ExitLinkTube(void){
    // LDH_A_addr(hSCX);
    // CP_A(0xa0);
    // IF_Z goto done;
    if(hram->hSCX == 0xa0) {
    // done:
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // XOR_A_A;
        // LDH_addr_A(hSCX);
        hram->hSCX = 0x0;
        // CALL(aTradeAnim_AdvanceScriptPointer);
        TradeAnim_AdvanceScriptPointer();
        // RET;
        return;
    }
    // SUB_A(0x4);
    // LDH_addr_A(hSCX);
    hram->hSCX -= 0x4;
    // RET;
}

void TradeAnim_SetupGivemonScroll(void){
    // LD_A(0x8f);
    // LDH_addr_A(hWX);
    hram->hWX = 0x8f;
    // LD_A(0x88);
    // LDH_addr_A(hSCX);
    hram->hSCX = 0x88;
    // LD_A(0x50);
    // LDH_addr_A(hWY);
    hram->hWY = 0x50;
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_DoGivemonScroll(void){
    // LDH_A_addr(hWX);
    // CP_A(0x7);
    // IF_Z goto done;
    if(hram->hWX == 0x7) {
    // done:
        // LD_A(0x7);
        // LDH_addr_A(hWX);
        hram->hWX = 0x7; // useless?
        // XOR_A_A;
        // LDH_addr_A(hSCX);
        hram->hSCX = 0x0;
        // CALL(aTradeAnim_AdvanceScriptPointer);
        TradeAnim_AdvanceScriptPointer();
        // RET;
        return;
    }
    // SUB_A(0x4);
    // LDH_addr_A(hWX);
    hram->hWX -= 0x4;
    // LDH_A_addr(hSCX);
    // SUB_A(0x4);
    // LDH_addr_A(hSCX);
    hram->hSCX -= 0x4;
    // RET;
}

void TradeAnim_FrontpicScrollStart(void){
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x50);
    // LDH_addr_A(hWY);
    hram->hWY = 0x50;
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_TextboxScrollStart(void){
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_ScrollOutRight(void){
    // CALL(aWaitTop);
    WaitTop_Conv();
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap1;
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram->hWX = 0x7;
    // XOR_A_A;
    // LDH_addr_A(hWY);
    hram->hWY = 0x0;
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aWaitTop);
    WaitTop_Conv();
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap0;
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aTradeAnim_IncrementJumptableIndex);
    TradeAnim_IncrementJumptableIndex();
    // RET;

}

void TradeAnim_ScrollOutRight2(void){
    // LDH_A_addr(hWX);
    // CP_A(0xa1);
    // IF_NC goto done;
    if(hram->hWX >= 0xa1) {
    // done:
        // LD_A(HIGH(vBGMap1));
        // LDH_addr_A(hBGMapAddress + 1);
        hram->hBGMapAddress = vBGMap1;
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // LD_A(0x7);
        // LDH_addr_A(hWX);
        hram->hWX = 0x7;
        // LD_A(0x90);
        // LDH_addr_A(hWY);
        hram->hWY = 0x90;
        // LD_A(HIGH(vBGMap0));
        // LDH_addr_A(hBGMapAddress + 1);
        hram->hBGMapAddress = vBGMap0;
        // CALL(aTradeAnim_AdvanceScriptPointer);
        TradeAnim_AdvanceScriptPointer();
        // RET;
        return;
    }
    // ADD_A(0x4);
    // LDH_addr_A(hWX);
    hram->hWX += 0x4;
    // RET;
}

void TradeAnim_ShowGivemonData(void){
    // CALL(aShowPlayerTrademonStats);
    ShowPlayerTrademonStats();
    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wPlayerTrademon.species;
    // LD_A_addr(wPlayerTrademonDVs);
    // LD_addr_A(wTempMonDVs);
    // LD_A_addr(wPlayerTrademonDVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = wram->wPlayerTrademon.dvs;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // CALL(aTradeAnim_ShowGivemonFrontpic);
    TradeAnim_ShowGivemonFrontpic();

    // LD_A_addr(wPlayerTrademonSpecies);
    // CALL(aGetCryIndex);
    // IF_C goto skip_cry;
    if(GetCryIndex_Conv(wram->wPlayerTrademon.species) >= 0) {
        // LD_E_C;
        // LD_D_B;
        // CALL(aPlayCry);
        v_PlayMonCry_Conv(wram->wPlayerTrademon.species);
    }

// skip_cry:
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_ShowGetmonData(void){
    // CALL(aShowOTTrademonStats);
    ShowOTTrademonStats();
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species;
    // LD_A_addr(wOTTrademonDVs);
    // LD_addr_A(wTempMonDVs);
    // LD_A_addr(wOTTrademonDVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = wram->wOTTrademon.dvs;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // CALL(aTradeAnim_ShowGetmonFrontpic);
    TradeAnim_ShowGetmonFrontpic();
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;

}

void TradeAnim_AnimateFrontpic(void){
    // FARCALL(aAnimateTrademonFrontpic);
    AnimateTrademonFrontpic();
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_GetFrontpic(uint8_t* de, uint16_t dvs, species_t species){
    // PUSH_DE;
    // PUSH_AF;
    // PREDEF(pGetUnownLetter);
    GetUnownLetter_Conv(dvs);
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // LD_addr_A(wCurSpecies);
    // CALL(aGetBaseData);
    GetBaseData_Conv2(species);
    // POP_DE;
    // PREDEF(pGetMonFrontpic);
    GetMonFrontpic_Conv(de);
    // RET;
}

void TradeAnim_GetNicknamename(uint8_t* de, species_t species){
    // PUSH_DE;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // POP_DE;
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, GetPokemonName_Conv2(species), NAME_LENGTH);
    // RET;

}

void TradeAnim_ShowGivemonFrontpic(void){
    // LD_DE(vTiles0);
    // JR(mTradeAnim_ShowFrontpic);
    return TradeAnim_ShowFrontpic(vram->vTiles0);
}

void TradeAnim_ShowGetmonFrontpic(void){
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x31);
    return TradeAnim_ShowFrontpic(vram->vTiles0 + LEN_2BPP_TILE * 0x31);
}

void TradeAnim_ShowFrontpic(const uint8_t* de){
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_HL(vTiles2);
    // LD_BC((10 << 8) | 0x31);
    // CALL(aRequest2bpp);
    CopyBytes_Conv2(vram->vTiles2, de, 0x31 * LEN_2BPP_TILE);
    // CALL(aWaitTop);
    WaitTop_Conv();
    // CALL(aTradeAnim_BlankTilemap);
    TradeAnim_BlankTilemap();
    // hlcoord(7, 2, wTilemap);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0x0;
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(7, 2, wram->wTilemap), 7, 7);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // RET;

}

void TradeAnim_Wait80(void){
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames_Conv(80);
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_Wait40(void){
    // LD_C(40);
    // CALL(aDelayFrames);
    DelayFrames_Conv(40);
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_Wait96(void){
    // LD_C(96);
    // CALL(aDelayFrames);
    DelayFrames_Conv(96);
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_Wait80IfOTEgg(void){
    // CALL(aIsOTTrademonEgg);
    // RET_NZ ;
    if(!IsOTTrademonEgg())
        return;
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames_Conv(80);
    // RET;

}

void TradeAnim_Wait180IfOTEgg(void){
    // CALL(aIsOTTrademonEgg);
    // RET_NZ ;
    if(!IsOTTrademonEgg())
        return;
    // LD_C(180);
    // CALL(aDelayFrames);
    DelayFrames_Conv(180);
    // RET;

}

bool IsOTTrademonEgg(void){
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // LD_A_addr(wOTTrademonSpecies);
    // CP_A(EGG);
    // RET;
    return wram->wOTTrademon.species == EGG;
}

void ShowPlayerTrademonStats(void){
    // LD_DE(wPlayerTrademonSpecies);
    // LD_A_de;
    // CP_A(EGG);
    // JR_Z (mTrademonStats_Egg);
    if(wram->wPlayerTrademon.species == EGG)
        return TrademonStats_Egg();
    // CALL(aTrademonStats_MonTemplate);
    TrademonStats_MonTemplate();
    // LD_DE(wPlayerTrademonSpecies);
    // CALL(aTrademonStats_PrintSpeciesNumber);
    TrademonStats_PrintSpeciesNumber(wram->wPlayerTrademon.species);
    // LD_DE(wPlayerTrademonSpeciesName);
    // CALL(aTrademonStats_PrintSpeciesName);
    TrademonStats_PrintSpeciesName(wram->wPlayerTrademon.speciesName);
    // LD_A_addr(wPlayerTrademonCaughtData);
    // LD_DE(wPlayerTrademonOTName);
    // CALL(aTrademonStats_PrintOTName);
    TrademonStats_PrintOTName(wram->wPlayerTrademon.otName, wram->wPlayerTrademon.caughtData);
    // LD_DE(wPlayerTrademonID);
    // CALL(aTrademonStats_PrintTrademonID);
    TrademonStats_PrintTrademonID(wram->wPlayerTrademon.id);
    // CALL(aTrademonStats_WaitBGMap);
    TrademonStats_WaitBGMap();
    // RET;

}

void ShowOTTrademonStats(void){
    // LD_DE(wOTTrademonSpecies);
    // LD_A_de;
    // CP_A(EGG);
    // JR_Z (mTrademonStats_Egg);
    if(wram->wOTTrademon.species == EGG)
        return TrademonStats_Egg();
    // CALL(aTrademonStats_MonTemplate);
    TrademonStats_MonTemplate();
    // LD_DE(wOTTrademonSpecies);
    // CALL(aTrademonStats_PrintSpeciesNumber);
    TrademonStats_PrintSpeciesNumber(wram->wOTTrademon.species);
    // LD_DE(wOTTrademonSpeciesName);
    // CALL(aTrademonStats_PrintSpeciesName);
    TrademonStats_PrintSpeciesName(wram->wOTTrademon.speciesName);
    // LD_A_addr(wOTTrademonCaughtData);
    // LD_DE(wOTTrademonOTName);
    // CALL(aTrademonStats_PrintOTName);
    TrademonStats_PrintOTName(wram->wOTTrademon.otName, wram->wOTTrademon.caughtData);
    // LD_DE(wOTTrademonID);
    // CALL(aTrademonStats_PrintTrademonID);
    TrademonStats_PrintTrademonID(wram->wOTTrademon.id);
    // CALL(aTrademonStats_WaitBGMap);
    TrademonStats_WaitBGMap();
    // RET;

}

void TrademonStats_MonTemplate(void){
    static const char OTMonData[] = "─── №."
        t_next ""
        t_next "OT/"
        t_next "<ID>№.";
    // CALL(aWaitTop);
    WaitTop_Conv();
    // CALL(aTradeAnim_BlankTilemap);
    TradeAnim_BlankTilemap();
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap1;
    // hlcoord(3, 0, wTilemap);
    // LD_B(0x6);
    // LD_C(0xd);
    // CALL(aTextbox);
    Textbox_Conv2(coord(3, 0, wram->wTilemap), 0x6, 0xd);
    // hlcoord(4, 0, wTilemap);
    // LD_DE(mTrademonStats_MonTemplate_OTMonData);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(OTMonData), coord(4, 0, wram->wTilemap));
    // RET;
}

void TrademonStats_Egg(void){
    static const char EggData[] = "EGG"
        t_next "OT/?????"
        t_next "<ID>№.?????";
    // CALL(aWaitTop);
    WaitTop_Conv();
    // CALL(aTradeAnim_BlankTilemap);
    TradeAnim_BlankTilemap();
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap1;
    // hlcoord(3, 0, wTilemap);
    // LD_B(6);
    // LD_C(13);
    // CALL(aTextbox);
    Textbox_Conv2(coord(3, 0, wram->wTilemap), 6, 13);
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mTrademonStats_Egg_EggData);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(EggData), coord(4, 2, wram->wTilemap));
    // CALL(aTrademonStats_WaitBGMap);
    TrademonStats_WaitBGMap();
    // RET;
}

void TrademonStats_WaitBGMap(void){
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aWaitTop);
    WaitTop_Conv();
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram->hBGMapAddress = vBGMap0;
    // RET;
}

void TrademonStats_PrintSpeciesNumber(species_t species){
    // hlcoord(10, 0, wTilemap);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
    // CALL(aPrintNum);
    uint8_t* hl = PrintNum_Conv2(coord(10, 0, wram->wTilemap), &species, PRINTNUM_LEADINGZEROS | sizeof(species), 3);
    // LD_hl(0x7f);
    *hl = 0x7f;
    // RET;
}

void TrademonStats_PrintSpeciesName(uint8_t* de){
    // hlcoord(4, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(4, 2, wram->wTilemap));
    // RET;
}

void TrademonStats_PrintOTName(uint8_t* de, uint8_t caughtData){
    static const uint8_t gender[] = {CHAR_SPACE, CHAR_MALE_ICON, CHAR_FEMALE_ICON};
    // CP_A(3);
    // IF_C goto caught_gender_okay;
    if(caughtData < 3) {
        // XOR_A_A;
        caughtData = 0;
    }

// caught_gender_okay:
    // PUSH_AF;
    // hlcoord(7, 4, wTilemap);
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl = coord(7, 4, wram->wTilemap), .de = de};
    PlaceString_Conv(&st, st.hl);
    // INC_BC;
    st.bc++;
    // POP_AF;
    // LD_HL(mTrademonStats_PrintOTName_Gender);
    // LD_D(0);
    // LD_E_A;
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_bc_A;
    *st.bc = gender[caughtData];
    // RET;

// Gender:
    //db ['" "', '"♂"', '"♀"'];
}

void TrademonStats_PrintTrademonID(uint16_t id){
    // hlcoord(7, 6, wTilemap);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(7, 6, wram->wTilemap), &id, PRINTNUM_LEADINGZEROS | 2, 5);
    // RET;
}

void TradeAnim_RockingBall(void){
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_TRADE_POKE_BALL);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_TRADE_POKE_BALL, pixel4(10, 11, 4, 0));
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // LD_A(32);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 32;
    // RET;

}

void TradeAnim_DropBall(void){
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_TRADE_POKE_BALL);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_TRADE_POKE_BALL, pixel4(10, 11, 4, 0));
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_hl(0x1);
    bc->jumptableIndex = 0x1;
    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl(0xdc);
    bc->yOffset = 0xdc;
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // LD_A(56);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 56;
    // RET;
}

void TradeAnim_Poof(void){
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_TRADE_POOF);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_TRADE_POOF, pixel4(10, 11, 4, 0));
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // LD_A(16);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 16;
    // LD_DE(SFX_BALL_POOF);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_BALL_POOF);
    // RET;

}

void TradeAnim_BulgeThroughTube(void){
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0_Conv(0b11100100);
    // depixel2(5, 11);
    // LD_A(SPRITE_ANIM_INDEX_TRADE_TUBE_BULGE);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_TRADE_TUBE_BULGE, pixel2(5, 11));
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // LD_A(64);
    // LD_addr_A(wFrameCounter);
    wram->wFrameCounter = 64;
    // RET;

}

static void TradeAnim_AnimateTrademonInTube_JumptableNext(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // INC_hl;
    bc->jumptableIndex++;
    // RET;
}

void TradeAnim_AnimateTrademonInTube(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_JUMPTABLE_INDEX);
    // ADD_HL_BC;
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mTradeAnim_AnimateTrademonInTube_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;


// Jumptable:
    switch(bc->jumptableIndex) {
    case 0:
    //dw ['.InitTimer'];
    // InitTimer:
        // CALL(aTradeAnim_AnimateTrademonInTube_JumptableNext);
        TradeAnim_AnimateTrademonInTube_JumptableNext(bc);
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x80);
        bc->var1 = 0x80;
        // RET;
        return;
    //dw ['.WaitTimer1'];
    case 1:
    // WaitTimer1:
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_hl;
        // AND_A_A;
        // RET_NZ ;
        if(bc->var1-- != 0)
            return;
        // CALL(aTradeAnim_AnimateTrademonInTube_JumptableNext);
        TradeAnim_AnimateTrademonInTube_JumptableNext(bc);
        fallthrough;
    //dw ['.MoveRight'];
    case 2:
    // MoveRight:
        // LD_HL(SPRITEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x94);
        // IF_NC goto done_move_right;
        if(bc->xCoord < 0x94) {
            // INC_hl;
            bc->xCoord++;
            // RET;
            return;
        }

    // done_move_right:
        // CALL(aTradeAnim_AnimateTrademonInTube_JumptableNext);
        TradeAnim_AnimateTrademonInTube_JumptableNext(bc);
        fallthrough;
    //dw ['.MoveDown'];
    case 3:
    // MoveDown:
        // LD_HL(SPRITEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x4c);
        // IF_NC goto done_move_down;
        if(bc->yCoord < 0x4c) {
            // INC_hl;
            bc->yCoord++;
            // RET;
            return;
        }

    // done_move_down:
        // LD_HL(SPRITEANIMSTRUCT_INDEX);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->index = 0x0;
        // RET;
        return;
    //dw ['.MoveUp'];
    case 4:
    // MoveUp:
        // LD_HL(SPRITEANIMSTRUCT_YCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x2c);
        // IF_Z goto done_move_up;
        if(bc->yCoord != 0x2c) {
            // DEC_hl;
            bc->yCoord--;
            // RET;
            return;
        }

    // done_move_up:
        // CALL(aTradeAnim_AnimateTrademonInTube_JumptableNext);
        TradeAnim_AnimateTrademonInTube_JumptableNext(bc);
        fallthrough;
    //dw ['.MoveLeft'];
    case 5:
    // MoveLeft:
        // LD_HL(SPRITEANIMSTRUCT_XCOORD);
        // ADD_HL_BC;
        // LD_A_hl;
        // CP_A(0x58);
        // IF_Z goto done_move_left;
        if(bc->xCoord < 0x58) {
            // DEC_hl;
            bc->xCoord--;
            // RET;
            return;
        }

    // done_move_left:
        // CALL(aTradeAnim_AnimateTrademonInTube_JumptableNext);
        TradeAnim_AnimateTrademonInTube_JumptableNext(bc);
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_hl(0x80);
        bc->var1 = 0x80;
        // RET;
        return;
    //dw ['.WaitTimer2'];
    case 6:
    // WaitTimer2:
        // LD_HL(SPRITEANIMSTRUCT_VAR1);
        // ADD_HL_BC;
        // LD_A_hl;
        // DEC_hl;
        // AND_A_A;
        // RET_NZ ;
        if(bc->var1-- != 0)
            return;
        // LD_HL(SPRITEANIMSTRUCT_INDEX);
        // ADD_HL_BC;
        // LD_hl(0x0);
        bc->index = 0x0;
        // RET;
        return;
    }
}

void TradeAnim_SentToOTText(void){
    static const txt_cmd_s MonWasSentToText[] = {
        text_far(v_MonWasSentToText)
        text_end
    };
    static const txt_cmd_s MonNameSentToText[] = {
        text_far(v_MonNameSentToText)
        text_end
    };
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_TIMECAPSULE);
    // IF_Z goto time_capsule;
    if(wram->wLinkMode == LINK_TIMECAPSULE) {
    // time_capsule:
        // LD_HL(mTradeAnim_SentToOTText_MonWasSentToText);
        // CALL(aPrintText);
        PrintText_Conv2(MonWasSentToText);
        // CALL(aTradeAnim_Wait80Frames);
        TradeAnim_Wait80Frames();
        // CALL(aTradeAnim_AdvanceScriptPointer);
        TradeAnim_AdvanceScriptPointer();
        // RET;
        return;
    }
    // LD_HL(mTradeAnim_SentToOTText_MonNameSentToText);
    // CALL(aPrintText);
    PrintText_Conv2(MonNameSentToText);
    // LD_C(189);
    // CALL(aDelayFrames);
    DelayFrames_Conv(189);
    // LD_HL(mTradeAnim_SentToOTText_MonWasSentToText);
    // CALL(aPrintText);
    PrintText_Conv2(MonWasSentToText);
    // CALL(aTradeAnim_Wait80Frames);
    TradeAnim_Wait80Frames();
    // LD_C(128);
    // CALL(aDelayFrames);
    DelayFrames_Conv(128);
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_OTBidsFarewell(void){
    static const txt_cmd_s BidsFarewellToMonText[] = {
        text_far(v_BidsFarewellToMonText)
        text_end
    };

    static const txt_cmd_s MonNameBidsFarewellText[] = {
        text_far(v_MonNameBidsFarewellText)
        text_end
    };
    // LD_HL(mTradeAnim_OTBidsFarewell_BidsFarewellToMonText);
    // CALL(aPrintText);
    PrintText_Conv2(BidsFarewellToMonText);
    // CALL(aTradeAnim_Wait80Frames);
    TradeAnim_Wait80Frames();
    // LD_HL(mTradeAnim_OTBidsFarewell_MonNameBidsFarewellText);
    // CALL(aPrintText);
    PrintText_Conv2(MonNameBidsFarewellText);
    // CALL(aTradeAnim_Wait80Frames);
    TradeAnim_Wait80Frames();
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_TakeCareOfText(void){
    static const txt_cmd_s TakeGoodCareOfMonText[] = {
        text_far(v_TakeGoodCareOfMonText)
        text_end
    };
    // CALL(aWaitTop);
    WaitTop_Conv();
    // hlcoord(0, 10, wTilemap);
    // LD_BC(8 * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 10, wram->wTilemap), 8 * SCREEN_WIDTH, 0x7f);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_HL(mTradeAnim_TakeCareOfText_TakeGoodCareOfMonText);
    // CALL(aPrintText);
    PrintText_Conv2(TakeGoodCareOfMonText);
    // CALL(aTradeAnim_Wait80Frames);
    TradeAnim_Wait80Frames();
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_OTSendsText1(void){
    static const txt_cmd_s ForYourMonSendsText[] = {
        text_far(v_ForYourMonSendsText)
        text_end
    };
    static const txt_cmd_s OTSendsText[] = {
        text_far(v_OTSendsText)
        text_end
    };
    // LD_HL(mTradeAnim_OTSendsText1_ForYourMonSendsText);
    // CALL(aPrintText);
    PrintText_Conv2(ForYourMonSendsText);
    // CALL(aTradeAnim_Wait80Frames);
    TradeAnim_Wait80Frames();
    // LD_HL(mTradeAnim_OTSendsText1_OTSendsText);
    // CALL(aPrintText);
    PrintText_Conv2(OTSendsText);
    // CALL(aTradeAnim_Wait80Frames);
    TradeAnim_Wait80Frames();
    // LD_C(14);
    // CALL(aDelayFrames);
    DelayFrames_Conv(14);
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_OTSendsText2(void){
    static const txt_cmd_s WillTradeText[] = {
        text_far(v_WillTradeText)
        text_end
    };
    static const txt_cmd_s ForYourMonWillTradeText[] = {
        text_far(v_ForYourMonWillTradeText)
        text_end
    };
    // LD_HL(mTradeAnim_OTSendsText2_WillTradeText);
    // CALL(aPrintText);
    PrintText_Conv2(WillTradeText);
    // CALL(aTradeAnim_Wait80Frames);
    TradeAnim_Wait80Frames();
    // LD_HL(mTradeAnim_OTSendsText2_ForYourMonWillTradeText);
    // CALL(aPrintText);
    PrintText_Conv2(ForYourMonWillTradeText);
    // CALL(aTradeAnim_Wait80Frames);
    TradeAnim_Wait80Frames();
    // LD_C(14);
    // CALL(aDelayFrames);
    DelayFrames_Conv(14);
    // CALL(aTradeAnim_AdvanceScriptPointer);
    TradeAnim_AdvanceScriptPointer();
    // RET;
}

void TradeAnim_Wait80Frames(void){
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames_Conv(80);
    // RET;
}

void TradeAnim_BlankTilemap(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // RET;
}

void TradeAnim_CopyBoxFromDEtoHL(uint8_t* hl, const uint8_t* de, uint8_t b, uint8_t c){
    do {
    // row:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // col:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *(hl2++) = *(de++);
            // DEC_C;
            // IF_NZ goto col;
        } while(--c2 != 0);
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void TradeAnim_NormalPals(void){
    // LDH_A_addr(hSGB);
    // AND_A_A;
    // LD_A(0b11100100);  // 3,2,1,0
    // IF_Z goto not_sgb;
    // LD_A(0xf0);
    const uint8_t a = (hram->hSGB == 0)? 0b11100100: 0xf0;

// not_sgb:
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0_Conv(a);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // RET;
}

void LinkTradeAnim_LoadTradePlayerNames(const uint8_t* hl, const uint8_t* de){
    // PUSH_DE;
    // LD_DE(wLinkPlayer1Name);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wLinkPlayer1Name, hl, NAME_LENGTH);
    // POP_HL;
    // LD_DE(wLinkPlayer2Name);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wLinkPlayer2Name, de, NAME_LENGTH);
    // RET;
}

void LinkTradeAnim_LoadTradeMonSpecies(species_t sendmon, species_t getmon){
    // LD_A_hl;
    // LD_addr_A(wLinkTradeSendmonSpecies);
    wram->wLinkTradeSendmonSpecies = sendmon;
    // LD_A_de;
    // LD_addr_A(wLinkTradeGetmonSpecies);
    wram->wLinkTradeGetmonSpecies = getmon;
    // RET;
}

void TradeAnim_FlashBGPals(void){
    // LD_A_addr(wFrameCounter2);
    // AND_A(0x7);
    // RET_NZ ;
    if(wram->wFrameCounter2 & 0x7)
        return;
    // LDH_A_addr(rBGP);
    // XOR_A(0b00111100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(gb_read(rBGP) ^ 0b00111100);
    // RET;
}

void LoadTradeBallAndCableGFX(void){
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_DE(mTradeBallGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x62);
    // LD_BC((BANK(aTradeBallGFX) << 8) | 6);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM_SkipEmptyTiles(vram->vTiles0 + LEN_2BPP_TILE * 0x62, TradeBallGFX, 0, 6);
    // LD_DE(mTradePoofGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x68);
    // LD_BC((BANK(aTradePoofGFX) << 8) | 12);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x68, TradePoofGFX, 0, 12);
    // LD_DE(mTradeCableGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x74);
    // LD_BC((BANK(aTradeCableGFX) << 8) | 4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x74, TradeCableGFX, 0, 4);
    // XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT
    // LD_HL(wSpriteAnimDict);
    // LD_hli_A;
    wram->wSpriteAnimDict[0] = SPRITE_ANIM_DICT_DEFAULT;
    // LD_hl(0x62);
    wram->wSpriteAnimDict[1] = 0x62;
    // RET;

}

void LoadTradeBubbleGFX(void){
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_E(MONICON_TRADE);
    // CALLFAR(aLoadMenuMonIcon);
    LoadMenuMonIcon_Conv(MONICON_TRADE);
    // LD_DE(mTradeBubbleGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x72);
    // LD_BC((BANK(aTradeBubbleGFX) << 8) | 4);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x72, TradeBubbleGFX, 0, 4);
    // XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT
    // LD_HL(wSpriteAnimDict);
    // LD_hli_A;
    wram->wSpriteAnimDict[0] = SPRITE_ANIM_DICT_DEFAULT;
    // LD_hl(0x62);
    wram->wSpriteAnimDict[1] = 0x62;
    // RET;
}

void TradeAnim_WaitAnim(void){
    // LD_HL(wFrameCounter);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto done;
    if(wram->wFrameCounter == 0) {
    // done:
        // CALL(aTradeAnim_AdvanceScriptPointer);
        TradeAnim_AdvanceScriptPointer();
        // RET;
        return;
    }
    // DEC_hl;
    wram->wFrameCounter--;
    // RET;
}

void TradeAnim_WaitAnim2(void){
    // LD_HL(wFrameCounter);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto done;
    if(wram->wFrameCounter == 0) {
    // done:
        // CALL(aTradeAnim_AdvanceScriptPointer);
        TradeAnim_AdvanceScriptPointer();
        // RET;
        return;
    }
    // DEC_hl;
    wram->wFrameCounter--;
    // RET;
}

void DebugTrade(void){
//  //  unreferenced
//  This function was meant for use in Japanese versions, so the
//  constant used for copy length was changed by accident.

    LD_HL(mDebugTrade_DebugTradeData);

    LD_A_hli;
    LD_addr_A(wPlayerTrademonSpecies);
    LD_DE(wPlayerTrademonSenderName);
    LD_C(NAME_LENGTH + 2);  // JP: NAME_LENGTH_JAPANESE + 2

loop1:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop1;

    LD_A_hli;
    LD_addr_A(wOTTrademonSpecies);
    LD_DE(wOTTrademonSenderName);
    LD_C(NAME_LENGTH + 2);  // JP: NAME_LENGTH_JAPANESE + 2

loop2:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop2;
    RET;

// debugtrade: MACRO
// ; species, ot name, ot id
//     db \1, \2
//     dw \3
// ENDM


// DebugTradeData:
    //debugtrade ['VENUSAUR', '"ゲーフり@@"', '0x0123']  // GAME FREAK
    //debugtrade ['CHARIZARD', '"クりーチャ@"', '0x0456']  // Creatures Inc.
}

const char TradeGameBoyTilemap[] = "gfx/trade/game_boy.tilemap";   //  6x8
// const char TradeGameBoyTilemap[] = "gfx/trade/game_boy2.tilemap";   //  6x8
const char TradeLinkTubeTilemap[] = "gfx/trade/link_cable.tilemap";   //  12x3

const char TradeArrowRightGFX[] = "gfx/trade/arrow_right.png";
const char TradeArrowLeftGFX[] = "gfx/trade/arrow_left.png";
const char TradeCableGFX[] = "gfx/trade/cable.png";
const char TradeBubbleGFX[] = "gfx/trade/bubble.png";
const char TradeGameBoyLZ[] = "gfx/trade/game_boy.png";
const char TradeLinkCableGFX[] = "gfx/trade/link_cable.png";
const char TradeBallGFX[] = "gfx/trade/ball.png";
const char TradePoofGFX[] = "gfx/trade/poof.png";
