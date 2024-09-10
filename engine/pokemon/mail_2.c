#include "../../constants.h"
#include "mail_2.h"
#include "european_mail.h"
#include "../gfx/color.h"
#include "../../home/array.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/gfx.h"
#include "../../home/lcd.h"
#include "../../home/sram.h"
#include "../../home/pokemon.h"
#include "../../home/joypad.h"
#include "../../data/items/mail_items.h"
#include "../../gfx/mail.h"
#include "../printer/printer.h"

//  MailGFXPointers indexes
//  LoadMailPalettes.MailPals indexes (see gfx/mail/mail.pal)
enum {
    FLOWER_MAIL_INDEX,  // 0
    SURF_MAIL_INDEX,  // 1
    LITEBLUEMAIL_INDEX,  // 2
    PORTRAITMAIL_INDEX,  // 3
    LOVELY_MAIL_INDEX,  // 4
    EON_MAIL_INDEX,  // 5
    MORPH_MAIL_INDEX,  // 6
    BLUESKY_MAIL_INDEX,  // 7
    MUSIC_MAIL_INDEX,  // 8
    MIRAGE_MAIL_INDEX,  // 9
    NUM_MAIL
};

void ReadPartyMonMail(void){
    OpenSRAM_Conv(MBANK(asPartyMail));
    // LD_A_addr(wCurPartyMon);
    // LD_HL(sPartyMail);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    const struct MailMsg* de = ((struct MailMsg*)GBToRAMAddr(sPartyMail)) + wram->wCurPartyMon;
    ReadAnyMail_Conv(de);
    CloseSRAM_Conv();
}

void ReadAnyMail(void){
    PUSH_DE;
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    CALL(aDisableLCD);
    CALL(aLoadFontsExtra);
    POP_DE;
    PUSH_DE;
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    FARCALL(aIsMailEuropean);
    CALL(aCloseSRAM);
    LD_A_C;
    LD_DE(mStandardEnglishFont);
    OR_A_A;
    IF_Z goto got_font;
    LD_DE(mFrenchGermanFont);
    SUB_A(0x3);
    IF_C goto got_font;
    LD_DE(mSpanishItalianFont);


got_font:
    LD_HL(vTiles1);
    LD_BC((BANK(aStandardEnglishFont) << 8) | 0x80);
    CALL(aGet1bpp);
    POP_DE;
    CALL(aReadAnyMail_LoadGFX);
    CALL(aEnableLCD);
    CALL(aWaitBGMap);
    LD_A_addr(wCurMailIndex);
    LD_E_A;
    FARCALL(aLoadMailPalettes);
    CALL(aSetPalettes);
    XOR_A_A;
    LDH_addr_A(hJoyPressed);
    CALL(aReadAnyMail_loop);
    CALL(aClearBGPalettes);
    CALL(aDisableLCD);
    CALL(aLoadStandardFont);
    JP(mEnableLCD);


loop:
    CALL(aGetJoypad);
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON | B_BUTTON | START);
    IF_Z goto loop;
    AND_A(START);
    IF_NZ goto pressed_start;
    RET;


pressed_start:
    LD_A_addr(wJumptableIndex);
    PUSH_AF;
    CALLFAR(aPrintMailAndExit);  // printer
    POP_AF;
    LD_addr_A(wJumptableIndex);
    goto loop;


LoadGFX:
    LD_H_D;
    LD_L_E;
    PUSH_HL;
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    LD_DE(sPartyMon1MailAuthorID - sPartyMon1Mail);
    ADD_HL_DE;
    LD_A_hli;  // author id
    LD_addr_A(wCurMailAuthorID);
    LD_A_hli;
    LD_addr_A(wCurMailAuthorID + 1);
    LD_A_hli;  // species
    LD_addr_A(wCurPartySpecies);
    LD_B_hl;  // type
    CALL(aCloseSRAM);
    LD_HL(mMailGFXPointers);
    LD_C(0);

loop2:
    LD_A_hli;
    CP_A_B;
    IF_Z goto got_pointer;
    CP_A(-1);
    IF_Z goto invalid;
    INC_C;
    INC_HL;
    INC_HL;
    goto loop2;


invalid:
    LD_HL(mMailGFXPointers);
    INC_HL;


got_pointer:
    LD_A_C;
    LD_addr_A(wCurMailIndex);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(mReadAnyMail_done);
    POP_BC;
    PUSH_DE;
    JP_hl;

done:
    RET;

}

struct MailGFX {
    uint8_t mail;
    void (*loadGfx)(const struct MailMsg*);
};

const struct MailGFX MailGFXPointers[] = {
//  entries correspond to *MAIL_INDEX constants
    //table_width ['3', 'MailGFXPointers']
    {FLOWER_MAIL,   LoadFlowerMailGFX},
    {SURF_MAIL,     LoadSurfMailGFX},
    {LITEBLUEMAIL,  LoadLiteBlueMailGFX},
    {PORTRAITMAIL,  LoadPortraitMailGFX},
    {LOVELY_MAIL,   LoadLovelyMailGFX},
    {EON_MAIL,      LoadEonMailGFX},
    {MORPH_MAIL,    LoadMorphMailGFX},
    {BLUESKY_MAIL,  LoadBlueSkyMailGFX},
    {MUSIC_MAIL,    LoadMusicMailGFX},
    {MIRAGE_MAIL,   LoadMirageMailGFX},
    //assert_table_length ['NUM_MAIL']
    //db ['-1'];  // end
    {(uint8_t)-1,   NULL},
};
static_assert(lengthof(MailGFXPointers) == NUM_MAIL + 1);

static void ReadAnyMail_LoadGFX(const struct MailMsg* de){
    // LD_H_D;
    // LD_L_E;
    // PUSH_HL;
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    // LD_DE(sPartyMon1MailAuthorID - sPartyMon1Mail);
    // ADD_HL_DE;
    // LD_A_hli;  // author id
    // LD_addr_A(wCurMailAuthorID);
    // LD_A_hli;
    // LD_addr_A(wCurMailAuthorID + 1);
    wram->wCurMailAuthorID = de->authorID;
    // LD_A_hli;  // species
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = de->species;
    // LD_B_hl;  // type
    uint8_t b = de->type;
    // CALL(aCloseSRAM);
    // LD_HL(mMailGFXPointers);
    // LD_C(0);
    const struct MailGFX* hl = MailGFXPointers;
    uint8_t c = 0;

    while(hl->mail != 0xff) {
    // loop2:
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto got_pointer;
        if(hl->mail == b) {
        got_pointer:
            // LD_A_C;
            // LD_addr_A(wCurMailIndex);
            wram->wCurMailIndex = c;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // LD_DE(mReadAnyMail_done);
            // POP_BC;
            // PUSH_DE;
            // JP_hl;
            return hl->loadGfx(de);
        }
        // CP_A(-1);
        // IF_Z goto invalid;
        // INC_C;
        c++;
        // INC_HL;
        // INC_HL;
        hl++;
        // goto loop2;
    }

// invalid:
    // LD_HL(mMailGFXPointers);
    hl = MailGFXPointers;
    // INC_HL;
    goto got_pointer;

// done:
    // RET;
}

static void ReadAnyMail_loop(void){
    while(1) {
        // CALL(aGetJoypad);
        GetJoypad_Conv2();
        DelayFrame();
        // LDH_A_addr(hJoyPressed);
        // AND_A(A_BUTTON | B_BUTTON | START);
        // IF_Z goto loop;
        if((hram->hJoyPressed & (A_BUTTON | B_BUTTON | START)) == 0)
            continue;
        // AND_A(START);
        // IF_NZ goto pressed_start;
        if((hram->hJoyPressed & START) == 0) {
            // RET;
            return;
        }

    // pressed_start:
        // LD_A_addr(wJumptableIndex);
        // PUSH_AF;
        uint8_t jumptableIndex = wram->wJumptableIndex;
        // CALLFAR(aPrintMailAndExit);  // printer
        PrintMailAndExit();
        // POP_AF;
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = jumptableIndex;
        // goto loop;
    }
}

void ReadAnyMail_Conv(const struct MailMsg* de){
    // PUSH_DE;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // POP_DE;
    // PUSH_DE;
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    // FARCALL(aIsMailEuropean);
    uint8_t c = IsMailEuropean_Conv(de);
    // CALL(aCloseSRAM);
    // LD_A_C;
    // LD_DE(mStandardEnglishFont);
    // OR_A_A;
    // IF_Z goto got_font;
    const char* font;
    if(c == 0) {
        font = StandardEnglishFont;
    }
    // LD_DE(mFrenchGermanFont);
    // SUB_A(0x3);
    // IF_C goto got_font;
    else if(c < 0x3) {
        font = FrenchGermanFont;
    }
    // LD_DE(mSpanishItalianFont);
    else {
        font = SpanishItalianFont;
    }

// got_font:
    // LD_HL(vTiles1);
    // LD_BC((BANK(aStandardEnglishFont) << 8) | 0x80);
    // CALL(aGet1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1, font, 0, 0x80);
    // POP_DE;
    // CALL(aReadAnyMail_LoadGFX);
    ReadAnyMail_LoadGFX(de);
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_A_addr(wCurMailIndex);
    // LD_E_A;
    // FARCALL(aLoadMailPalettes);
    LoadMailPalettes(wram->wCurMailIndex);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // XOR_A_A;
    // LDH_addr_A(hJoyPressed);
    hram->hJoyPressed = 0x0;
    // CALL(aReadAnyMail_loop);
    ReadAnyMail_loop();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // JP(mEnableLCD);
    return EnableLCD_Conv();
}

void LoadSurfMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(mSurfMailBorderGFX);
    // LD_C(8 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    uint8_t* hl = LoadMailGFX_Color1(vram->vTiles2 + LEN_2BPP_TILE * 0x31, SurfMailBorderGFX, 0, 8 * LEN_1BPP_TILE);
    // LD_DE(mMailLaprasGFX);
    // LD_C(6 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, MailLaprasGFX, 0, 6 * LEN_1BPP_TILE);
    // LD_DE(mSurfMailWaveGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, SurfMailWaveGFX, 0, 1 * LEN_1BPP_TILE);
    // JR(mFinishLoadingSurfLiteBlueMailGFX);
    return FinishLoadingSurfLiteBlueMailGFX(bc, hl);
}

void LoadLiteBlueMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(mLiteBlueMailBorderGFX);
    // LD_C(8 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    uint8_t* hl = LoadMailGFX_Color2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, LiteBlueMailBorderGFX, 0, 8 * LEN_1BPP_TILE);
    // LD_DE(mMailDratiniGFX);
    // LD_C(6 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, MailDratiniGFX, 0, 6 * LEN_1BPP_TILE);
    // LD_DE(mPortraitMailUnderlineGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, PortraitMailUnderlineGFX, 0, 1 * LEN_1BPP_TILE);

    return FinishLoadingSurfLiteBlueMailGFX(bc, hl);
}

void FinishLoadingSurfLiteBlueMailGFX(const struct MailMsg* bc, uint8_t* hl){
    // LD_DE(mSurfLiteBlueMailSmallShapesGFX);
    // LD_C(2 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, SurfLiteBlueMailSmallShapesGFX, 0, 2 * LEN_1BPP_TILE);
    // LD_C(2 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, SurfLiteBlueMailSmallShapesGFX, 0, 2 * LEN_1BPP_TILE);
    // LD_DE(mSurfLiteBlueMailLargeShapesGFX);
    // LD_C(8 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, SurfLiteBlueMailLargeShapesGFX, 0, 8 * LEN_1BPP_TILE);
    // LD_C(8 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, SurfLiteBlueMailLargeShapesGFX, 0, 8 * LEN_1BPP_TILE);

    // CALL(aDrawMailBorder);
    DrawMailBorder();
    // hlcoord(2, 15, wTilemap);
    // LD_A(0x3f);
    // CALL(aMail_Draw16TileRow);
    Mail_Draw16TileRow(coord(2, 15, wram->wTilemap), 0x3f);
    // LD_A(0x39);
    // hlcoord(15, 14, wTilemap);
    // CALL(aMail_Draw3x2Graphic);
    Mail_Draw3x2Graphic(coord(15, 14, wram->wTilemap), 0x39);
    // LD_A(0x44);
    // hlcoord(2, 2, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(2, 2, wram->wTilemap), 0x44);
    // hlcoord(15, 11, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(15, 11, wram->wTilemap), 0x44);
    // LD_A(0x4c);
    // hlcoord(3, 12, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(3, 12, wram->wTilemap), 0x4c);
    // hlcoord(15, 2, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(15, 2, wram->wTilemap), 0x4c);
    // LD_A(0x50);
    // hlcoord(6, 3, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(6, 3, wram->wTilemap), 0x50);
    // LD_A(0x40);
    // hlcoord(13, 2, wTilemap);
    // LD_hli_A;
    *coord(13, 2, wram->wTilemap) = 0x40;
    // hlcoord(6, 14, wTilemap);
    // LD_hl_A;
    *coord(6, 14, wram->wTilemap) = 0x40;
    // LD_A(0x41);
    // hlcoord(4, 5, wTilemap);
    // LD_hli_A;
    *coord(4, 5, wram->wTilemap) = 0x41;
    // hlcoord(17, 5, wTilemap);
    // LD_hli_A;
    *coord(17, 5, wram->wTilemap) = 0x41;
    // hlcoord(13, 12, wTilemap);
    // LD_hl_A;
    *coord(13, 12, wram->wTilemap) = 0x41;
    // LD_A(0x42);
    // hlcoord(9, 2, wTilemap);
    // LD_hli_A;
    *coord(9, 2, wram->wTilemap) = 0x42;
    // hlcoord(14, 5, wTilemap);
    // LD_hli_A;
    *coord(14, 5, wram->wTilemap) = 0x42;
    // hlcoord(3, 10, wTilemap);
    // LD_hl_A;
    *coord(3, 10, wram->wTilemap) = 0x42;
    // LD_A(0x43);
    // hlcoord(6, 11, wTilemap);
    // LD_hli_A;
    *coord(6, 11, wram->wTilemap) = 0x43;
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

void LoadEonMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(mEonMailBorder1GFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    uint8_t* hl = LoadMailGFX_Color2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, EonMailBorder1GFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mEonMailBorder2GFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, EonMailBorder2GFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mEonMailBorder2GFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, EonMailBorder2GFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mEonMailBorder1GFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, EonMailBorder1GFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mSurfMailBorderGFX + 6 * LEN_1BPP_TILE);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, SurfMailBorderGFX, 6 * LEN_1BPP_TILE, 1 * LEN_1BPP_TILE);
    // LD_DE(mMailEeveeGFX);
    // LD_C(6 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, MailEeveeGFX, 0, 6 * LEN_1BPP_TILE);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x3d);
    // LD_DE(mMailLargeCircleGFX);
    // LD_C(4 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(vram->vTiles2 + LEN_2BPP_TILE * 0x3d, MailLargeCircleGFX, 0, 4 * LEN_1BPP_TILE);
    // LD_DE(mEonMailBorder2GFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, EonMailBorder2GFX, 0, 1 * LEN_1BPP_TILE);

    // LD_A(0x31);
    // hlcoord(0, 0, wTilemap);
    // CALL(aMail_Place18TileAlternatingRow);
    Mail_Place18TileAlternatingRow(coord(0, 0, wram->wTilemap), 0x31);
    // hlcoord(1, 17, wTilemap);
    // CALL(aMail_Place18TileAlternatingRow);
    Mail_Place18TileAlternatingRow(coord(1, 17, wram->wTilemap), 0x31);
    // LD_A(0x33);
    // hlcoord(0, 1, wTilemap);
    // CALL(aMail_Place16TileAlternatingColumn);
    Mail_Place16TileAlternatingColumn(coord(0, 1, wram->wTilemap), 0x33);
    // hlcoord(19, 0, wTilemap);
    // CALL(aMail_Place16TileAlternatingColumn);
    Mail_Place16TileAlternatingColumn(coord(19, 0, wram->wTilemap), 0x33);
    // hlcoord(2, 15, wTilemap);
    // LD_A(0x35);
    // CALL(aMail_Draw16TileRow);
    Mail_Draw16TileRow(coord(2, 15, wram->wTilemap), 0x35);
    // INC_A;
    // hlcoord(15, 14, wTilemap);
    // CALL(aMail_Draw3x2Graphic);
    Mail_Draw3x2Graphic(coord(15, 14, wram->wTilemap), 0x36);
    // CALL(aLovelyEonMail_PlaceIcons);
    LovelyEonMail_PlaceIcons();
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

void LoadLovelyMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(mLovelyMailBorderGFX);
    // LD_C(5 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    uint8_t* hl = LoadMailGFX_Color2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, LovelyMailBorderGFX, 0, 5 * LEN_1BPP_TILE);
    // LD_DE(mMailPoliwagGFX);
    // LD_C(6 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, MailPoliwagGFX, 0, 6 * LEN_1BPP_TILE);
    // LD_DE(mLovelyMailUnderlineGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, LovelyMailUnderlineGFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mLovelyMailLargeHeartGFX);
    // LD_C(4 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, LovelyMailLargeHeartGFX, 0, 4 * LEN_1BPP_TILE);
    // LD_DE(mLovelyMailSmallHeartGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, LovelyMailSmallHeartGFX, 0, 1 * LEN_1BPP_TILE);

    // CALL(aDrawMailBorder2);
    DrawMailBorder2();
    // hlcoord(2, 15, wTilemap);
    // LD_A(0x3c);
    // CALL(aMail_Draw16TileRow);
    Mail_Draw16TileRow(coord(2, 15, wram->wTilemap), 0x3c);
    // LD_A(0x36);
    // hlcoord(15, 14, wTilemap);
    // CALL(aMail_Draw3x2Graphic);
    Mail_Draw3x2Graphic(coord(15, 14, wram->wTilemap), 0x36);
    // CALL(aLovelyEonMail_PlaceIcons);
    LovelyEonMail_PlaceIcons();
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

void LovelyEonMail_PlaceIcons(void){
    // LD_A(0x3d);
    // hlcoord(2, 2, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(2, 2, wram->wTilemap), 0x3d);
    // hlcoord(16, 2, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(16, 2, wram->wTilemap), 0x3d);
    // hlcoord(9, 4, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(9, 4, wram->wTilemap), 0x3d);
    // hlcoord(2, 11, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(2, 11, wram->wTilemap), 0x3d);
    // hlcoord(6, 12, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(6, 12, wram->wTilemap), 0x3d);
    // hlcoord(12, 11, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(12, 11, wram->wTilemap), 0x3d);
    // LD_A(0x41);
    // hlcoord(5, 4, wTilemap);
    // LD_hl_A;
    *coord(5, 4, wram->wTilemap) = 0x41;
    // hlcoord(6, 2, wTilemap);
    // LD_hl_A;
    *coord(6, 2, wram->wTilemap) = 0x41;
    // hlcoord(12, 4, wTilemap);
    // LD_hl_A;
    *coord(12, 4, wram->wTilemap) = 0x41;
    // hlcoord(14, 2, wTilemap);
    // LD_hl_A;
    *coord(14, 2, wram->wTilemap) = 0x41;
    // hlcoord(3, 13, wTilemap);
    // LD_hl_A;
    *coord(3, 13, wram->wTilemap) = 0x41;
    // hlcoord(9, 11, wTilemap);
    // LD_hl_A;
    *coord(9, 11, wram->wTilemap) = 0x41;
    // hlcoord(16, 12, wTilemap);
    // LD_hl_A;
    *coord(16, 12, wram->wTilemap) = 0x41;
    // RET;
}

void LoadMorphMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_BC(5 * LEN_1BPP_TILE);
    // CALL(aMailGFX_GenerateMonochromeTilesColor2);
    uint8_t* hl = MailGFX_GenerateMonochromeTilesColor2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, 5 * LEN_1BPP_TILE);
    // LD_DE(mMorphMailBorderCornerGFX + 3 * LEN_1BPP_TILE);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, MorphMailBorderCornerGFX, 3 * LEN_1BPP_TILE, 1 * LEN_1BPP_TILE);
    // LD_DE(mMorphMailBorderCornerGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, MorphMailBorderCornerGFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mMorphMailBorderGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, MorphMailBorderGFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mEonMailBorder1GFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, EonMailBorder1GFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mMorphMailDividerGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, MorphMailDividerGFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mMailDittoGFX);
    // LD_C(6 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, MailDittoGFX, 0, 6 * LEN_1BPP_TILE);
    // CALL(aDrawMailBorder2);
    DrawMailBorder2();
    // LD_A(0x31);
    // hlcoord(1, 1, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(1, 1, wram->wTilemap), 0x31);
    // hlcoord(17, 15, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(17, 15, wram->wTilemap), 0x31);
    // hlcoord(1, 3, wTilemap);
    // LD_hl_A;
    *coord(1, 3, wram->wTilemap) = 0x31;
    // hlcoord(3, 1, wTilemap);
    // LD_hl_A;
    *coord(3, 1, wram->wTilemap) = 0x31;
    // hlcoord(16, 16, wTilemap);
    // LD_hl_A;
    *coord(16, 16, wram->wTilemap) = 0x31;
    // hlcoord(18, 14, wTilemap);
    // LD_hl_A;
    *coord(18, 14, wram->wTilemap) = 0x31;
    // LD_A(0x36);
    // hlcoord(1, 4, wTilemap);
    // LD_hl_A;
    *coord(1, 4, wram->wTilemap) = 0x36;
    // hlcoord(2, 3, wTilemap);
    // LD_hl_A;
    *coord(2, 3, wram->wTilemap) = 0x36;
    // hlcoord(3, 2, wTilemap);
    // LD_hl_A;
    *coord(3, 2, wram->wTilemap) = 0x36;
    // hlcoord(4, 1, wTilemap);
    // LD_hl_A;
    *coord(4, 1, wram->wTilemap) = 0x36;
    // INC_A;
    // hlcoord(15, 16, wTilemap);
    // LD_hl_A;
    *coord(15, 16, wram->wTilemap) = 0x37;
    // hlcoord(16, 15, wTilemap);
    // LD_hl_A;
    *coord(16, 15, wram->wTilemap) = 0x37;
    // hlcoord(17, 14, wTilemap);
    // LD_hl_A;
    *coord(17, 14, wram->wTilemap) = 0x37;
    // hlcoord(18, 13, wTilemap);
    // LD_hl_A;
    *coord(18, 13, wram->wTilemap) = 0x37;
    // INC_A;
    // hlcoord(2, 15, wTilemap);
    // LD_B(0xe);
    // CALL(aMail_DrawRowLoop);
    Mail_DrawRowLoop(coord(2, 15, wram->wTilemap), 0x38, 0xe);
    // INC_A;
    // hlcoord(2, 11, wTilemap);
    // CALL(aMail_Draw16TileRow);
    Mail_Draw16TileRow(coord(2, 11, wram->wTilemap), 0x39);
    // hlcoord(2, 5, wTilemap);
    // CALL(aMail_Draw16TileRow);
    Mail_Draw16TileRow(coord(2, 5, wram->wTilemap), 0x39);
    // INC_A;
    // hlcoord(6, 1, wTilemap);
    // CALL(aMail_Draw13TileRow);
    Mail_Draw13TileRow(coord(6, 1, wram->wTilemap), 0x3a);
    // hlcoord(1, 16, wTilemap);
    // CALL(aMail_Draw13TileRow);
    Mail_Draw13TileRow(coord(1, 16, wram->wTilemap), 0x3a);
    // INC_A;
    // hlcoord(3, 13, wTilemap);
    // CALL(aMail_Draw3x2Graphic);
    Mail_Draw3x2Graphic(coord(3, 13, wram->wTilemap), 0x3b);
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

void LoadBlueSkyMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(mEonMailBorder1GFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    uint8_t* hl = LoadMailGFX_Color2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, EonMailBorder1GFX, 0, 1 * LEN_1BPP_TILE);
    // LD_A(0xff);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aByteFill);
    ByteFill_Conv2(hl, 1 * LEN_2BPP_TILE, 0xff);
    hl += 1 * LEN_2BPP_TILE;
    // LD_DE(mBlueSkyMailGrassGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, BlueSkyMailGrassGFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mMailDragoniteAndSentretGFX);
    // LD_C(23 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, MailDragoniteGFX, 0, 17 * LEN_1BPP_TILE);
    hl = LoadMailGFX_Color3(hl, MailSentretGFX, 0, 6 * LEN_1BPP_TILE);
    // LD_DE(mMailCloudGFX);
    // LD_C(6 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, MailCloudGFX, 0, 6 * LEN_1BPP_TILE);
    // LD_DE(mFlowerMailBorderGFX + 6 * LEN_1BPP_TILE);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, FlowerMailBorderGFX, 6 * LEN_1BPP_TILE, 1 * LEN_1BPP_TILE);
    // LD_DE(mMailCloudGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, MailCloudGFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mMailCloudGFX + 2 * LEN_1BPP_TILE);
    // LD_C(2 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, MailCloudGFX, 2 * LEN_1BPP_TILE, 2 * LEN_1BPP_TILE);
    // LD_DE(mMailCloudGFX + 5 * LEN_1BPP_TILE);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, MailCloudGFX, 5 * LEN_1BPP_TILE, 1 * LEN_1BPP_TILE);

    // LD_A(0x31);
    // hlcoord(0, 0, wTilemap);
    // CALL(aMail_DrawFullWidthBorder);
    Mail_DrawFullWidthBorder(coord(0, 0, wram->wTilemap), 0x31);
    // hlcoord(0, 1, wTilemap);
    // CALL(aMail_DrawLeftRightBorder);
    Mail_DrawLeftRightBorder(coord(0, 1, wram->wTilemap), 0x31);
    // hlcoord(19, 1, wTilemap);
    // CALL(aMail_DrawLeftRightBorder);
    Mail_DrawLeftRightBorder(coord(19, 1, wram->wTilemap), 0x31);
    // INC_A;
    // hlcoord(0, 17, wTilemap);
    // CALL(aMail_DrawFullWidthBorder);
    Mail_DrawFullWidthBorder(coord(0, 17, wram->wTilemap), 0x32);
    // INC_A;
    // hlcoord(0, 16, wTilemap);
    // CALL(aMail_DrawFullWidthBorder);
    Mail_DrawFullWidthBorder(coord(0, 16, wram->wTilemap), 0x33);
    // INC_A;
    tile_t a = 0x34;
    // hlcoord(2, 2, wTilemap);
    // CALL(aMail_Place6TileRow);
    a = Mail_Place6TileRow(coord(2, 2, wram->wTilemap), a);
    // hlcoord(3, 3, wTilemap);
    // CALL(aMail_Place6TileRow);
    a = Mail_Place6TileRow(coord(3, 3, wram->wTilemap), a);
    // hlcoord(4, 4, wTilemap);
    // CALL(aMail_Place6TileRow);
    a = Mail_Place6TileRow(coord(4, 4, wram->wTilemap), a);
    // DEC_HL;
    // LD_hl(0x7f);
    coord(4, 4, wram->wTilemap)[5] = 0x7f;
    // DEC_A;
    --a;
    // hlcoord(15, 14, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(15, 14, wram->wTilemap), a);
    // ADD_A(0x4);
    a += 0x4;
    // hlcoord(15, 16, wTilemap);
    // LD_hli_A;
    // INC_A;
    *coord(15, 16, wram->wTilemap) = a++;
    // LD_hl_A;
    // INC_A;
    *coord(16, 16, wram->wTilemap) = a++;
    // PUSH_AF;
    // hlcoord(12, 1, wTilemap);
    // CALL(aMail_Draw3x2Graphic);
    Mail_Draw3x2Graphic(coord(12, 1, wram->wTilemap), a);
    // POP_AF;
    // hlcoord(15, 4, wTilemap);
    // CALL(aMail_Draw3x2Graphic);
    a = Mail_Draw3x2Graphic(coord(15, 4, wram->wTilemap), a);
    // INC_A;
    a++;
    // hlcoord(2, 11, wTilemap);
    // CALL(aMail_Draw16TileRow);
    Mail_Draw16TileRow(coord(2, 11, wram->wTilemap), a);
    // INC_A;
    a++;
    // hlcoord(10, 3, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(10, 3, wram->wTilemap), a);
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

tile_t Mail_Place6TileRow(tile_t* hl, tile_t a){
    // LD_B(0x6);
    uint8_t b = 0x6;

    do {
    // loop:
        // LD_hli_A;
        // INC_A;
        *(hl++) = a++;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
    return a;
}

void LoadFlowerMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(mFlowerMailBorderGFX);
    // LD_C(8 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    uint8_t* hl = LoadMailGFX_Color1(vram->vTiles2 + LEN_2BPP_TILE * 0x31, FlowerMailBorderGFX, 0, 8 * LEN_1BPP_TILE);
    // LD_DE(mMailOddishGFX);
    // LD_C(4 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, MailOddishGFX, 0, 4 * LEN_1BPP_TILE);
    // LD_DE(mFlowerMailBorderGFX + 6 * LEN_1BPP_TILE);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, FlowerMailBorderGFX, 6 * LEN_1BPP_TILE, 1 * LEN_1BPP_TILE);
    // LD_DE(mFlowerMailFlowerGFX);
    // LD_C(4 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, FlowerMailBorderGFX, 0, 4 * LEN_1BPP_TILE);
    // LD_C(4 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    LoadMailGFX_Color2(hl, FlowerMailBorderGFX, 4 * LEN_1BPP_TILE, 4 * LEN_1BPP_TILE);

    // CALL(aDrawMailBorder);
    DrawMailBorder();
    // hlcoord(2, 15, wTilemap);
    // LD_A(0x3d);  // underline
    // CALL(aMail_Draw16TileRow);
    Mail_Draw16TileRow(coord(2, 15, wram->wTilemap), 0x3d);
    // LD_A(0x39);  // oddish
    // hlcoord(16, 13, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(16, 13, wram->wTilemap), 0x39);
    // hlcoord(2, 13, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(2, 13, wram->wTilemap), 0x39);
    // LD_A(0x3e);
    // hlcoord(2, 2, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(2, 2, wram->wTilemap), 0x3e);
    // hlcoord(5, 3, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(5, 3, wram->wTilemap), 0x3e);
    // hlcoord(10, 2, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(10, 2, wram->wTilemap), 0x3e);
    // hlcoord(16, 3, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(16, 3, wram->wTilemap), 0x3e);
    // hlcoord(5, 11, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(5, 11, wram->wTilemap), 0x3e);
    // hlcoord(16, 10, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(16, 10, wram->wTilemap), 0x3e);
    // LD_A(0x42);
    // hlcoord(3, 4, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(3, 4, wram->wTilemap), 0x42);
    // hlcoord(12, 3, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(12, 3, wram->wTilemap), 0x42);
    // hlcoord(14, 2, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(14, 2, wram->wTilemap), 0x42);
    // hlcoord(2, 10, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(2, 10, wram->wTilemap), 0x42);
    // hlcoord(14, 11, wTilemap);
    // CALL(aMail_Draw2x2Graphic);
    Mail_Draw2x2Graphic(coord(14, 11, wram->wTilemap), 0x42);
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

void LoadPortraitMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(mPortraitMailBorderGFX);
    // LD_C(5 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    uint8_t* hl = LoadMailGFX_Color2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, PortraitMailBorderGFX, 0, 5 * LEN_1BPP_TILE);
    // LD_DE(mPortraitMailUnderlineGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, PortraitMailUnderlineGFX, 0, 1 * LEN_1BPP_TILE);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x3d);
    // LD_DE(mPortraitMailLargePokeballGFX);
    // LD_C(4 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(vram->vTiles2 + LEN_2BPP_TILE * 0x3d, PortraitMailLargePokeballGFX, 0, 4 * LEN_1BPP_TILE);
    // LD_DE(mPortraitMailSmallPokeballGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, PortraitMailSmallPokeballGFX, 0, 1 * LEN_1BPP_TILE);

    // CALL(aDrawMailBorder2);
    DrawMailBorder2();
    // hlcoord(8, 15, wTilemap);
    // LD_A(0x36);
    // LD_B(0xa);
    // CALL(aMail_DrawRowLoop);
    Mail_DrawRowLoop(coord(8, 15, wram->wTilemap), 0x36, 0xa);
    // CALL(aLovelyEonMail_PlaceIcons);
    LovelyEonMail_PlaceIcons();
    // LD_A(0x1);
    // LD_addr_A(wUnownLetter);
    wram->wUnownLetter = 0x1; // Maybe in the future take into account the holding unown's DVs.
    // hlcoord(1, 10, wTilemap);
    // CALL(aPrepMonFrontpic);
    PrepMonFrontpic_Conv(coord(1, 10, wram->wTilemap));
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

void LoadMusicMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_DE(mMusicMailBorderGFX);
    // LD_C(4 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    uint8_t* hl = LoadMailGFX_Color2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, MusicMailBorderGFX, 0, 4 * LEN_1BPP_TILE);
    // LD_DE(mMorphMailBorderGFX);
    // LD_C(2 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, MorphMailBorderGFX, 0, 2 * LEN_1BPP_TILE);
    // LD_DE(mMailNatuGFX);
    // LD_C(6 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color3);
    hl = LoadMailGFX_Color3(hl, MailNatuGFX, 0, 6 * LEN_1BPP_TILE);
    // XOR_A_A;
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aByteFill);
    ByteFill_Conv2(hl, 1 * LEN_2BPP_TILE, 0x0);
    hl += 1 * LEN_2BPP_TILE;
    // LD_DE(mMusicMailLargeNoteGFX);
    // LD_C(3 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, MusicMailLargeNoteGFX, 0, 3 * LEN_1BPP_TILE);
    // LD_DE(mMusicMailSmallNoteGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    LoadMailGFX_Color1(hl, MusicMailSmallNoteGFX, 0, 1 * LEN_1BPP_TILE);

    // LD_A(0x31);
    // hlcoord(0, 0, wTilemap);
    // CALL(aMail_Place18TileAlternatingRow);
    Mail_Place18TileAlternatingRow(coord(0, 0, wram->wTilemap), 0x31);
    // hlcoord(1, 17, wTilemap);
    // CALL(aMail_Place18TileAlternatingRow);
    Mail_Place18TileAlternatingRow(coord(1, 17, wram->wTilemap), 0x31);
    // LD_A(0x33);
    // hlcoord(0, 1, wTilemap);
    // CALL(aMail_Place16TileAlternatingColumn);
    Mail_Place16TileAlternatingColumn(coord(0, 1, wram->wTilemap), 0x33);
    // hlcoord(19, 0, wTilemap);
    // CALL(aMail_Place16TileAlternatingColumn);
    Mail_Place16TileAlternatingColumn(coord(19, 0, wram->wTilemap), 0x33);
    // LD_A(0x35);
    // hlcoord(2, 15, wTilemap);
    // CALL(aMail_Place14TileAlternatingRow);
    Mail_Place18TileAlternatingRow(coord(2, 15, wram->wTilemap), 0x35);
    // LD_A(0x37);
    // hlcoord(15, 14, wTilemap);
    // CALL(aMail_Draw3x2Graphic);
    Mail_Draw3x2Graphic(coord(15, 14, wram->wTilemap), 0x37);
    // CALL(aLovelyEonMail_PlaceIcons);
    LovelyEonMail_PlaceIcons();
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

void LoadMirageMailGFX(const struct MailMsg* bc){
    // PUSH_BC;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_BC(5 * LEN_1BPP_TILE);
    // CALL(aMailGFX_GenerateMonochromeTilesColor2);
    uint8_t* hl = MailGFX_GenerateMonochromeTilesColor2(vram->vTiles2 + LEN_2BPP_TILE * 0x31, 5 * LEN_1BPP_TILE);
    // LD_DE(mBlueSkyMailGrassGFX);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, BlueSkyMailGrassGFX, 0, 1 * LEN_1BPP_TILE);
    // LD_DE(mMailMewGFX);
    // LD_C(18 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color2);
    hl = LoadMailGFX_Color2(hl, MailMewGFX, 0, 18 * LEN_1BPP_TILE);
    // LD_DE(mLiteBlueMailBorderGFX + 1 * LEN_1BPP_TILE);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    hl = LoadMailGFX_Color1(hl, LiteBlueMailBorderGFX, 1 * LEN_1BPP_TILE, 1 * LEN_1BPP_TILE);
    // LD_DE(mLiteBlueMailBorderGFX + 6 * LEN_1BPP_TILE);
    // LD_C(1 * LEN_1BPP_TILE);
    // CALL(aLoadMailGFX_Color1);
    LoadMailGFX_Color1(hl, LiteBlueMailBorderGFX, 6 * LEN_1BPP_TILE, 1 * LEN_1BPP_TILE);

    // CALL(aDrawMailBorder2);
    DrawMailBorder2();
    // LD_A(0x36);
    // hlcoord(1, 16, wTilemap);
    // CALL(aMail_DrawTopBottomBorder);
    Mail_DrawTopBottomBorder(coord(1, 16, wram->wTilemap), 0x36);
    // INC_A;
    // hlcoord(15, 14, wTilemap);
    // CALL(aMail_Draw3x2Graphic);
    tile_t a = Mail_Draw3x2Graphic(coord(15, 14, wram->wTilemap), 0x37);
    // INC_A;
    a++;
    // hlcoord(15, 16, wTilemap);
    // LD_hli_A;
    // INC_A;
    *coord(15, 16, wram->wTilemap) = a++;
    // LD_hl_A;
    *coord(16, 16, wram->wTilemap) = a;
    // LD_A(0x3f);
    // hlcoord(1, 1, wTilemap);
    // CALL(aMail_Place18TileAlternatingRow);
    Mail_Place18TileAlternatingRow(coord(1, 1, wram->wTilemap), 0x3f);
    // LD_A(0x41);
    // hlcoord(0, 2, wTilemap);
    // CALL(aMail_Place14TileAlternatingColumn);
    Mail_Place14TileAlternatingColumn(coord(0, 2, wram->wTilemap), 0x41);
    // LD_A(0x43);
    // hlcoord(19, 2, wTilemap);
    // CALL(aMail_Place14TileAlternatingColumn);
    Mail_Place14TileAlternatingColumn(coord(19, 2, wram->wTilemap), 0x43);
    // LD_A(0x45);
    a = 0x45;
    // hlcoord(0, 1, wTilemap);
    // LD_hl_A;
    // INC_A;
    *coord(0, 1, wram->wTilemap) = a++;
    // hlcoord(19, 1, wTilemap);
    // LD_hl_A;
    // INC_A;
    *coord(19, 1, wram->wTilemap) = a++;
    // hlcoord(0, 16, wTilemap);
    // LD_hl_A;
    // INC_A;
    *coord(0, 16, wram->wTilemap) = a++;
    // hlcoord(19, 16, wTilemap);
    // LD_hl_A;
    // INC_A;
    *coord(19, 16, wram->wTilemap) = a++;
    // hlcoord(2, 5, wTilemap);
    // CALL(aMail_Draw16TileRow);
    // INC_A;
    Mail_Draw16TileRow(coord(2, 5, wram->wTilemap), a++);
    // hlcoord(2, 11, wTilemap);
    // CALL(aMail_Draw16TileRow);
    Mail_Draw16TileRow(coord(2, 11, wram->wTilemap), a);
    // POP_HL;
    // JP(mMailGFX_PlaceMessage);
    MailGFX_PlaceMessage(bc);
}

uint8_t* MailGFX_GenerateMonochromeTilesColor2(uint8_t* hl, uint16_t bc){
    do {
    // loop:
        // XOR_A_A;
        // LD_hli_A;
        *(hl++) = 0x0;
        // LD_A(0xff);
        // LD_hli_A;
        *(hl++) = 0xff;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
    return hl;
}

void MailGFX_PlaceMessage(const struct MailMsg* hl){
    // LD_BC(MAIL_STRUCT_LENGTH);
    // LD_DE(wTempMail);
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wTempMail, hl, sizeof(*hl));
    // CALL(aCloseSRAM);
    // LD_HL(wTempMailAuthor);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wMonOrItemNameBuffer, wram->wTempMail.author, NAME_LENGTH - 1);
    // LD_A(0x50);
    // LD_addr_A(wTempMailAuthor);
    wram->wTempMail.author[0] = 0x50;
    // LD_addr_A(wMonOrItemNameBuffer + NAME_LENGTH - 1);
    wram->wMonOrItemNameBuffer[NAME_LENGTH - 1] = 0x50;
    // LD_DE(wTempMailMessage);
    // hlcoord(2, 7, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wTempMail.message, coord(2, 7, wram->wTilemap));
    // LD_DE(wMonOrItemNameBuffer);
    // LD_A_de;
    // AND_A_A;
    // RET_Z ;
    if(wram->wMonOrItemNameBuffer[0] == 0)
        return;
    tile_t* de;
    // LD_A_addr(wCurMailIndex);
    // hlcoord(8, 14, wTilemap);
    // CP_A(PORTRAITMAIL_INDEX);
    if(wram->wCurMailIndex == PORTRAITMAIL_INDEX)
        de = coord(8, 14, wram->wTilemap);
    // IF_Z goto place_author;
    // hlcoord(6, 14, wTilemap);
    // CP_A(MORPH_MAIL_INDEX);
    else if(wram->wCurMailIndex == MORPH_MAIL_INDEX)
        de = coord(6, 14, wram->wTilemap);
    // IF_Z goto place_author;
    // hlcoord(5, 14, wTilemap);
    else
        de = coord(5, 14, wram->wTilemap);


// place_author:
    // JP(mPlaceString);
    PlaceStringSimple(wram->wMonOrItemNameBuffer, de);
}

void InvertBytes(void){
//  //  unreferenced
//  invert bc bytes starting at hl

loop:
    LD_A_hl;
    XOR_A(0xff);
    LD_hli_A;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;

}

void DrawMailBorder(void){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_A(0x31);
    tile_t a = 0x31;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // CALL(aMail_DrawTopBottomBorder);
    // INC_A;
    hl = Mail_DrawTopBottomBorder(hl, a++);
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // CALL(aMail_DrawLeftRightBorder);
    hl = Mail_DrawLeftRightBorder(hl, a);
    // LD_A(0x36);
    a = 0x36;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // CALL(aMail_DrawTopBottomBorder);
    Mail_DrawTopBottomBorder(hl, a);
    // hlcoord(19, 1, wTilemap);
    // LD_A(0x35);
    // CALL(aMail_DrawLeftRightBorder);
    hl = Mail_DrawLeftRightBorder(coord(19, 1, wram->wTilemap), 0x35);
    // LD_A(0x38);
    // LD_hl_A;
    *hl = 0x38;
    // RET;
}

void DrawMailBorder2(void){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_A(0x31);
    tile_t a = 0x31;
    // LD_hli_A;
    // INC_A;
    *(hl++) = a++;
    // CALL(aMail_DrawTopBottomBorder);
    hl = Mail_DrawTopBottomBorder(hl, a);
    // LD_hl(0x31);
    *hl = 0x31;
    // INC_HL;
    hl++;
    // INC_A;
    a++;
    // CALL(aMail_DrawLeftRightBorder);
    hl = Mail_DrawLeftRightBorder(hl, a);
    // LD_hl(0x31);
    *hl = 0x31;
    // INC_HL;
    hl++;
    // INC_A;
    a++;
    // CALL(aMail_DrawTopBottomBorder);
    Mail_DrawTopBottomBorder(hl, a);
    // hlcoord(19, 1, wTilemap);
    // LD_A(0x35);
    // CALL(aMail_DrawLeftRightBorder);
    hl = Mail_DrawLeftRightBorder(coord(19, 1, wram->wTilemap), 0x35);
    // LD_hl(0x31);
    *hl = 0x31;
    // RET;
}

void Mail_Place14TileAlternatingRow(tile_t* hl, tile_t a){
    // PUSH_AF;
    // LD_B(14 / 2);
    // JR(mMail_PlaceAlternatingRow);
    return Mail_PlaceAlternatingRow(hl, a, 14 / 2);
}

void Mail_Place16TileAlternatingRow(void){
//  //  unreferenced
    PUSH_AF;
    LD_B(16 / 2);
    JR(mMail_PlaceAlternatingRow);

}

void Mail_Place18TileAlternatingRow(tile_t* hl, tile_t a){
    // PUSH_AF;
    // LD_B(18 / 2);
// fallthrough

    return Mail_PlaceAlternatingRow(hl, a, 18 / 2);
}

void Mail_PlaceAlternatingRow(tile_t* hl, tile_t a, uint8_t b){
    do {
    // loop:
        // LD_hli_A;
        // INC_A;
        *(hl++) = a++;
        // LD_hli_A;
        // DEC_A;
        *(hl++) = a--;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // LD_hl_A;
    *hl = a;
    // POP_AF;
    // RET;
}

void Mail_Place14TileAlternatingColumn(tile_t* hl, tile_t a){
    // PUSH_AF;
    // LD_B(14 / 2);
    // JR(mMail_PlaceAlternatingColumn);
    return Mail_PlaceAlternatingColumn(hl, a, 14 / 2);
}

void Mail_Place16TileAlternatingColumn(tile_t* hl, tile_t a){
    // PUSH_AF;
    // LD_B(16 / 2);

    return Mail_PlaceAlternatingColumn(hl, a, 16 / 2);
}

void Mail_PlaceAlternatingColumn(tile_t* hl, tile_t a, uint8_t b){
    do {
    // loop:
        // LD_hl_A;
        *hl = a++;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // INC_A;
        // LD_hl_A;
        *hl = a--;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_A;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // LD_hl_A;
    *hl = a;
    // POP_AF;
    // RET;
}

void Mail_Draw7TileRow(void){
//  //  unreferenced
    LD_B(7);
    JR(mMail_DrawRowLoop);

}

tile_t* Mail_Draw13TileRow(tile_t* hl, tile_t a){
    // LD_B(13);
    // JR(mMail_DrawRowLoop);
    return Mail_DrawRowLoop(hl, a, 13);
}

tile_t* Mail_Draw16TileRow(tile_t* hl, tile_t a){
    // LD_B(16);
    // JR(mMail_DrawRowLoop);
    return Mail_DrawRowLoop(hl, a, 16);
}

tile_t* Mail_DrawTopBottomBorder(tile_t* hl, tile_t a){
    // LD_B(SCREEN_WIDTH - 2);
    // JR(mMail_DrawRowLoop);
    return Mail_DrawRowLoop(hl, a, SCREEN_WIDTH - 2);
}

tile_t* Mail_DrawFullWidthBorder(tile_t* hl, tile_t a){
    // LD_B(SCREEN_WIDTH);
// fallthrough

    return Mail_DrawRowLoop(hl, a, SCREEN_WIDTH);
}

tile_t* Mail_DrawRowLoop(tile_t* hl, tile_t a, uint8_t b){
    do {
    // loop:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
    return hl;
}

tile_t* Mail_DrawLeftRightBorder(tile_t* hl, tile_t a){
    // LD_B(SCREEN_HEIGHT - 2);
    uint8_t b = SCREEN_HEIGHT - 2;
    // LD_DE(SCREEN_WIDTH);

    do {
    // loop:
        // LD_hl_A;
        *hl = a;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
    return hl;
}

void Mail_Draw2x2Graphic(tile_t* hl, tile_t a){
    // PUSH_AF;
    // LD_hli_A;
    hl[0] = a + 0;
    // INC_A;
    // LD_hl_A;
    hl[1] = a + 1;
    // LD_BC(SCREEN_WIDTH - 1);
    // ADD_HL_BC;
    // INC_A;
    // LD_hli_A;
    hl[SCREEN_WIDTH] = a + 2;
    // INC_A;
    // LD_hl_A;
    hl[SCREEN_WIDTH+1] = a + 3;
    // POP_AF;
    // RET;
}

tile_t Mail_Draw3x2Graphic(tile_t* hl, tile_t a){
    // LD_hli_A;
    // INC_A;
    hl[0] = a++;
    // LD_hli_A;
    // INC_A;
    hl[1] = a++;
    // LD_hl_A;
    hl[2] = a++;
    // LD_BC(SCREEN_WIDTH - 2);
    // ADD_HL_BC;
    // INC_A;
    // LD_hli_A;
    hl[SCREEN_WIDTH] = a++;
    // INC_A;
    // LD_hli_A;
    hl[SCREEN_WIDTH+1] = a++;
    // INC_A;
    // LD_hl_A;
    hl[SCREEN_WIDTH+2] = a;
    // RET;
    return a;
}

uint8_t* LoadMailGFX_Color1(uint8_t* hl, const char* de, uint8_t start, uint8_t c){
    uint8_t buffer[c * 2];
    LoadPNG1bppAssetSectionToVRAM_SkipEmptyTiles(buffer, de, start / LEN_1BPP_TILE, c / LEN_1BPP_TILE);
    const uint8_t* de_ = buffer;
    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        *(hl++) = *de_;
        de_ += 2;
        // XOR_A_A;
        // LD_hli_A;
        *(hl++) = 0;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
    return hl;
}

uint8_t* LoadMailGFX_Color2(uint8_t* hl, const char* de, uint8_t start, uint8_t c){
    uint8_t buffer[c * 2];
    LoadPNG1bppAssetSectionToVRAM_SkipEmptyTiles(buffer, de, start / LEN_1BPP_TILE, c / LEN_1BPP_TILE);
    const uint8_t* de_ = buffer;
    do {
    // loop:
        // XOR_A_A;
        // LD_hli_A;
        *(hl++) = 0;
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        *(hl++) = *de_;
        de_ += 2;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
    return hl;
}

uint8_t* LoadMailGFX_Color3(uint8_t* hl, const char* de, uint8_t start, uint8_t c){
    uint8_t buffer[c * 2];
    LoadPNG1bppAssetSectionToVRAM_SkipEmptyTiles(buffer, de, start / LEN_1BPP_TILE, c / LEN_1BPP_TILE);
    const uint8_t* de_ = buffer;
    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        uint8_t a = *de_;
        de_ += 2;
        // LD_hli_A;
        *(hl++) = a;
        // LD_hli_A;
        *(hl++) = a;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
    return hl;

// INCLUDE "gfx/mail.asm"
}

void ItemIsMail(void){
    LD_A_D;
    LD_HL(mMailItems);
    LD_DE(1);
    JP(mIsInArray);

// INCLUDE "data/items/mail_items.asm"

}

bool ItemIsMail_Conv(item_t d){
    // LD_A_D;
    // LD_HL(mMailItems);
    // LD_DE(1);
    // JP(mIsInArray);
    return IsInArray_Conv_Item(MailItems, d) != 0xffff;

// INCLUDE "data/items/mail_items.asm"

}
