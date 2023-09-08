#include "../../constants.h"
#include "mail_2.h"
#include "../../home/array.h"
#include "../../data/items/mail_items.h"

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
    LD_A_addr(wCurPartyMon);
    LD_HL(sPartyMail);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    return ReadAnyMail();
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

void MailGFXPointers(void){
//  entries correspond to *MAIL_INDEX constants
    //table_width ['3', 'MailGFXPointers']
    //dbw ['FLOWER_MAIL', 'LoadFlowerMailGFX']
    //dbw ['SURF_MAIL', 'LoadSurfMailGFX']
    //dbw ['LITEBLUEMAIL', 'LoadLiteBlueMailGFX']
    //dbw ['PORTRAITMAIL', 'LoadPortraitMailGFX']
    //dbw ['LOVELY_MAIL', 'LoadLovelyMailGFX']
    //dbw ['EON_MAIL', 'LoadEonMailGFX']
    //dbw ['MORPH_MAIL', 'LoadMorphMailGFX']
    //dbw ['BLUESKY_MAIL', 'LoadBlueSkyMailGFX']
    //dbw ['MUSIC_MAIL', 'LoadMusicMailGFX']
    //dbw ['MIRAGE_MAIL', 'LoadMirageMailGFX']
    //assert_table_length ['NUM_MAIL']
    //db ['-1'];  // end

    return LoadSurfMailGFX();
}

void LoadSurfMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(mSurfMailBorderGFX);
    LD_C(8 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMailLaprasGFX);
    LD_C(6 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    LD_DE(mSurfMailWaveGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    JR(mFinishLoadingSurfLiteBlueMailGFX);

}

void LoadLiteBlueMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(mLiteBlueMailBorderGFX);
    LD_C(8 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMailDratiniGFX);
    LD_C(6 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    LD_DE(mPortraitMailUnderlineGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);

    return FinishLoadingSurfLiteBlueMailGFX();
}

void FinishLoadingSurfLiteBlueMailGFX(void){
    LD_DE(mSurfLiteBlueMailSmallShapesGFX);
    LD_C(2 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_C(2 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mSurfLiteBlueMailLargeShapesGFX);
    LD_C(8 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_C(8 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);

    CALL(aDrawMailBorder);
    hlcoord(2, 15, wTilemap);
    LD_A(0x3f);
    CALL(aMail_Draw16TileRow);
    LD_A(0x39);
    hlcoord(15, 14, wTilemap);
    CALL(aMail_Draw3x2Graphic);
    LD_A(0x44);
    hlcoord(2, 2, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(15, 11, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    LD_A(0x4c);
    hlcoord(3, 12, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(15, 2, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    LD_A(0x50);
    hlcoord(6, 3, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    LD_A(0x40);
    hlcoord(13, 2, wTilemap);
    LD_hli_A;
    hlcoord(6, 14, wTilemap);
    LD_hl_A;
    LD_A(0x41);
    hlcoord(4, 5, wTilemap);
    LD_hli_A;
    hlcoord(17, 5, wTilemap);
    LD_hli_A;
    hlcoord(13, 12, wTilemap);
    LD_hl_A;
    LD_A(0x42);
    hlcoord(9, 2, wTilemap);
    LD_hli_A;
    hlcoord(14, 5, wTilemap);
    LD_hli_A;
    hlcoord(3, 10, wTilemap);
    LD_hl_A;
    LD_A(0x43);
    hlcoord(6, 11, wTilemap);
    LD_hli_A;
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void LoadEonMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(mEonMailBorder1GFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mEonMailBorder2GFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mEonMailBorder2GFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mEonMailBorder1GFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mSurfMailBorderGFX + 6 * LEN_1BPP_TILE);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMailEeveeGFX);
    LD_C(6 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x3d);
    LD_DE(mMailLargeCircleGFX);
    LD_C(4 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mEonMailBorder2GFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);

    LD_A(0x31);
    hlcoord(0, 0, wTilemap);
    CALL(aMail_Place18TileAlternatingRow);
    hlcoord(1, 17, wTilemap);
    CALL(aMail_Place18TileAlternatingRow);
    LD_A(0x33);
    hlcoord(0, 1, wTilemap);
    CALL(aMail_Place16TileAlternatingColumn);
    hlcoord(19, 0, wTilemap);
    CALL(aMail_Place16TileAlternatingColumn);
    hlcoord(2, 15, wTilemap);
    LD_A(0x35);
    CALL(aMail_Draw16TileRow);
    INC_A;
    hlcoord(15, 14, wTilemap);
    CALL(aMail_Draw3x2Graphic);
    CALL(aLovelyEonMail_PlaceIcons);
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void LoadLovelyMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(mLovelyMailBorderGFX);
    LD_C(5 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMailPoliwagGFX);
    LD_C(6 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    LD_DE(mLovelyMailUnderlineGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mLovelyMailLargeHeartGFX);
    LD_C(4 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mLovelyMailSmallHeartGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);

    CALL(aDrawMailBorder2);
    hlcoord(2, 15, wTilemap);
    LD_A(0x3c);
    CALL(aMail_Draw16TileRow);
    LD_A(0x36);
    hlcoord(15, 14, wTilemap);
    CALL(aMail_Draw3x2Graphic);
    CALL(aLovelyEonMail_PlaceIcons);
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void LovelyEonMail_PlaceIcons(void){
    LD_A(0x3d);
    hlcoord(2, 2, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(16, 2, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(9, 4, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(2, 11, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(6, 12, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(12, 11, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    LD_A(0x41);
    hlcoord(5, 4, wTilemap);
    LD_hl_A;
    hlcoord(6, 2, wTilemap);
    LD_hl_A;
    hlcoord(12, 4, wTilemap);
    LD_hl_A;
    hlcoord(14, 2, wTilemap);
    LD_hl_A;
    hlcoord(3, 13, wTilemap);
    LD_hl_A;
    hlcoord(9, 11, wTilemap);
    LD_hl_A;
    hlcoord(16, 12, wTilemap);
    LD_hl_A;
    RET;

}

void LoadMorphMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_BC(5 * LEN_1BPP_TILE);
    CALL(aMailGFX_GenerateMonochromeTilesColor2);
    LD_DE(mMorphMailBorderCornerGFX + 3 * LEN_1BPP_TILE);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMorphMailBorderCornerGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMorphMailBorderGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mEonMailBorder1GFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mMorphMailDividerGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMailDittoGFX);
    LD_C(6 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    CALL(aDrawMailBorder2);
    LD_A(0x31);
    hlcoord(1, 1, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(17, 15, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(1, 3, wTilemap);
    LD_hl_A;
    hlcoord(3, 1, wTilemap);
    LD_hl_A;
    hlcoord(16, 16, wTilemap);
    LD_hl_A;
    hlcoord(18, 14, wTilemap);
    LD_hl_A;
    LD_A(0x36);
    hlcoord(1, 4, wTilemap);
    LD_hl_A;
    hlcoord(2, 3, wTilemap);
    LD_hl_A;
    hlcoord(3, 2, wTilemap);
    LD_hl_A;
    hlcoord(4, 1, wTilemap);
    LD_hl_A;
    INC_A;
    hlcoord(15, 16, wTilemap);
    LD_hl_A;
    hlcoord(16, 15, wTilemap);
    LD_hl_A;
    hlcoord(17, 14, wTilemap);
    LD_hl_A;
    hlcoord(18, 13, wTilemap);
    LD_hl_A;
    INC_A;
    hlcoord(2, 15, wTilemap);
    LD_B(0xe);
    CALL(aMail_DrawRowLoop);
    INC_A;
    hlcoord(2, 11, wTilemap);
    CALL(aMail_Draw16TileRow);
    hlcoord(2, 5, wTilemap);
    CALL(aMail_Draw16TileRow);
    INC_A;
    hlcoord(6, 1, wTilemap);
    CALL(aMail_Draw13TileRow);
    hlcoord(1, 16, wTilemap);
    CALL(aMail_Draw13TileRow);
    INC_A;
    hlcoord(3, 13, wTilemap);
    CALL(aMail_Draw3x2Graphic);
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void LoadBlueSkyMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(mEonMailBorder1GFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_A(0xff);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aByteFill);
    LD_DE(mBlueSkyMailGrassGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    LD_DE(mMailDragoniteAndSentretGFX);
    LD_C(23 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    LD_DE(mMailCloudGFX);
    LD_C(6 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mFlowerMailBorderGFX + 6 * LEN_1BPP_TILE);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mMailCloudGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mMailCloudGFX + 2 * LEN_1BPP_TILE);
    LD_C(2 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mMailCloudGFX + 5 * LEN_1BPP_TILE);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);

    LD_A(0x31);
    hlcoord(0, 0, wTilemap);
    CALL(aMail_DrawFullWidthBorder);
    hlcoord(0, 1, wTilemap);
    CALL(aMail_DrawLeftRightBorder);
    hlcoord(19, 1, wTilemap);
    CALL(aMail_DrawLeftRightBorder);
    INC_A;
    hlcoord(0, 17, wTilemap);
    CALL(aMail_DrawFullWidthBorder);
    INC_A;
    hlcoord(0, 16, wTilemap);
    CALL(aMail_DrawFullWidthBorder);
    INC_A;
    hlcoord(2, 2, wTilemap);
    CALL(aMail_Place6TileRow);
    hlcoord(3, 3, wTilemap);
    CALL(aMail_Place6TileRow);
    hlcoord(4, 4, wTilemap);
    CALL(aMail_Place6TileRow);
    DEC_HL;
    LD_hl(0x7f);
    DEC_A;
    hlcoord(15, 14, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    ADD_A(0x4);
    hlcoord(15, 16, wTilemap);
    LD_hli_A;
    INC_A;
    LD_hl_A;
    INC_A;
    PUSH_AF;
    hlcoord(12, 1, wTilemap);
    CALL(aMail_Draw3x2Graphic);
    POP_AF;
    hlcoord(15, 4, wTilemap);
    CALL(aMail_Draw3x2Graphic);
    INC_A;
    hlcoord(2, 11, wTilemap);
    CALL(aMail_Draw16TileRow);
    INC_A;
    hlcoord(10, 3, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void Mail_Place6TileRow(void){
    LD_B(0x6);

loop:
    LD_hli_A;
    INC_A;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void LoadFlowerMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(mFlowerMailBorderGFX);
    LD_C(8 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mMailOddishGFX);
    LD_C(4 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    LD_DE(mFlowerMailBorderGFX + 6 * LEN_1BPP_TILE);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mFlowerMailFlowerGFX);
    LD_C(4 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_C(4 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);

    CALL(aDrawMailBorder);
    hlcoord(2, 15, wTilemap);
    LD_A(0x3d);  // underline
    CALL(aMail_Draw16TileRow);
    LD_A(0x39);  // oddish
    hlcoord(16, 13, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(2, 13, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    LD_A(0x3e);
    hlcoord(2, 2, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(5, 3, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(10, 2, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(16, 3, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(5, 11, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(16, 10, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    LD_A(0x42);
    hlcoord(3, 4, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(12, 3, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(14, 2, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(2, 10, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    hlcoord(14, 11, wTilemap);
    CALL(aMail_Draw2x2Graphic);
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void LoadPortraitMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(mPortraitMailBorderGFX);
    LD_C(5 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mPortraitMailUnderlineGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x3d);
    LD_DE(mPortraitMailLargePokeballGFX);
    LD_C(4 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mPortraitMailSmallPokeballGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);

    CALL(aDrawMailBorder2);
    hlcoord(8, 15, wTilemap);
    LD_A(0x36);
    LD_B(0xa);
    CALL(aMail_DrawRowLoop);
    CALL(aLovelyEonMail_PlaceIcons);
    LD_A(0x1);
    LD_addr_A(wUnownLetter);
    hlcoord(1, 10, wTilemap);
    CALL(aPrepMonFrontpic);
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void LoadMusicMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_DE(mMusicMailBorderGFX);
    LD_C(4 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMorphMailBorderGFX);
    LD_C(2 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMailNatuGFX);
    LD_C(6 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color3);
    XOR_A_A;
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aByteFill);
    LD_DE(mMusicMailLargeNoteGFX);
    LD_C(3 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mMusicMailSmallNoteGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);

    LD_A(0x31);
    hlcoord(0, 0, wTilemap);
    CALL(aMail_Place18TileAlternatingRow);
    hlcoord(1, 17, wTilemap);
    CALL(aMail_Place18TileAlternatingRow);
    LD_A(0x33);
    hlcoord(0, 1, wTilemap);
    CALL(aMail_Place16TileAlternatingColumn);
    hlcoord(19, 0, wTilemap);
    CALL(aMail_Place16TileAlternatingColumn);
    LD_A(0x35);
    hlcoord(2, 15, wTilemap);
    CALL(aMail_Place14TileAlternatingRow);
    LD_A(0x37);
    hlcoord(15, 14, wTilemap);
    CALL(aMail_Draw3x2Graphic);
    CALL(aLovelyEonMail_PlaceIcons);
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void LoadMirageMailGFX(void){
    PUSH_BC;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    LD_BC(5 * LEN_1BPP_TILE);
    CALL(aMailGFX_GenerateMonochromeTilesColor2);
    LD_DE(mBlueSkyMailGrassGFX);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mMailMewGFX);
    LD_C(18 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color2);
    LD_DE(mLiteBlueMailBorderGFX + 1 * LEN_1BPP_TILE);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);
    LD_DE(mLiteBlueMailBorderGFX + 6 * LEN_1BPP_TILE);
    LD_C(1 * LEN_1BPP_TILE);
    CALL(aLoadMailGFX_Color1);

    CALL(aDrawMailBorder2);
    LD_A(0x36);
    hlcoord(1, 16, wTilemap);
    CALL(aMail_DrawTopBottomBorder);
    INC_A;
    hlcoord(15, 14, wTilemap);
    CALL(aMail_Draw3x2Graphic);
    INC_A;
    hlcoord(15, 16, wTilemap);
    LD_hli_A;
    INC_A;
    LD_hl_A;
    LD_A(0x3f);
    hlcoord(1, 1, wTilemap);
    CALL(aMail_Place18TileAlternatingRow);
    LD_A(0x41);
    hlcoord(0, 2, wTilemap);
    CALL(aMail_Place14TileAlternatingColumn);
    LD_A(0x43);
    hlcoord(19, 2, wTilemap);
    CALL(aMail_Place14TileAlternatingColumn);
    LD_A(0x45);
    hlcoord(0, 1, wTilemap);
    LD_hl_A;
    INC_A;
    hlcoord(19, 1, wTilemap);
    LD_hl_A;
    INC_A;
    hlcoord(0, 16, wTilemap);
    LD_hl_A;
    INC_A;
    hlcoord(19, 16, wTilemap);
    LD_hl_A;
    INC_A;
    hlcoord(2, 5, wTilemap);
    CALL(aMail_Draw16TileRow);
    INC_A;
    hlcoord(2, 11, wTilemap);
    CALL(aMail_Draw16TileRow);
    POP_HL;
    JP(mMailGFX_PlaceMessage);

}

void MailGFX_GenerateMonochromeTilesColor2(void){

loop:
    XOR_A_A;
    LD_hli_A;
    LD_A(0xff);
    LD_hli_A;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;

}

void MailGFX_PlaceMessage(void){
    LD_BC(MAIL_STRUCT_LENGTH);
    LD_DE(wTempMail);
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_HL(wTempMailAuthor);
    LD_DE(wMonOrItemNameBuffer);
    LD_BC(NAME_LENGTH - 1);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_addr_A(wTempMailAuthor);
    LD_addr_A(wMonOrItemNameBuffer + NAME_LENGTH - 1);
    LD_DE(wTempMailMessage);
    hlcoord(2, 7, wTilemap);
    CALL(aPlaceString);
    LD_DE(wMonOrItemNameBuffer);
    LD_A_de;
    AND_A_A;
    RET_Z ;
    LD_A_addr(wCurMailIndex);
    hlcoord(8, 14, wTilemap);
    CP_A(PORTRAITMAIL_INDEX);
    IF_Z goto place_author;
    hlcoord(6, 14, wTilemap);
    CP_A(MORPH_MAIL_INDEX);
    IF_Z goto place_author;
    hlcoord(5, 14, wTilemap);


place_author:
    JP(mPlaceString);

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
    hlcoord(0, 0, wTilemap);
    LD_A(0x31);
    LD_hli_A;
    INC_A;
    CALL(aMail_DrawTopBottomBorder);
    INC_A;
    LD_hli_A;
    INC_A;
    CALL(aMail_DrawLeftRightBorder);
    LD_A(0x36);
    LD_hli_A;
    INC_A;
    CALL(aMail_DrawTopBottomBorder);
    hlcoord(19, 1, wTilemap);
    LD_A(0x35);
    CALL(aMail_DrawLeftRightBorder);
    LD_A(0x38);
    LD_hl_A;
    RET;

}

void DrawMailBorder2(void){
    hlcoord(0, 0, wTilemap);
    LD_A(0x31);
    LD_hli_A;
    INC_A;
    CALL(aMail_DrawTopBottomBorder);
    LD_hl(0x31);
    INC_HL;
    INC_A;
    CALL(aMail_DrawLeftRightBorder);
    LD_hl(0x31);
    INC_HL;
    INC_A;
    CALL(aMail_DrawTopBottomBorder);
    hlcoord(19, 1, wTilemap);
    LD_A(0x35);
    CALL(aMail_DrawLeftRightBorder);
    LD_hl(0x31);
    RET;

}

void Mail_Place14TileAlternatingRow(void){
    PUSH_AF;
    LD_B(14 / 2);
    JR(mMail_PlaceAlternatingRow);

}

void Mail_Place16TileAlternatingRow(void){
//  //  unreferenced
    PUSH_AF;
    LD_B(16 / 2);
    JR(mMail_PlaceAlternatingRow);

}

void Mail_Place18TileAlternatingRow(void){
    PUSH_AF;
    LD_B(18 / 2);
// fallthrough

    return Mail_PlaceAlternatingRow();
}

void Mail_PlaceAlternatingRow(void){

loop:
    LD_hli_A;
    INC_A;
    LD_hli_A;
    DEC_A;
    DEC_B;
    IF_NZ goto loop;
    LD_hl_A;
    POP_AF;
    RET;

}

void Mail_Place14TileAlternatingColumn(void){
    PUSH_AF;
    LD_B(14 / 2);
    JR(mMail_PlaceAlternatingColumn);

}

void Mail_Place16TileAlternatingColumn(void){
    PUSH_AF;
    LD_B(16 / 2);

    return Mail_PlaceAlternatingColumn();
}

void Mail_PlaceAlternatingColumn(void){

loop:
    LD_hl_A;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    INC_A;
    LD_hl_A;
    ADD_HL_DE;
    DEC_A;
    DEC_B;
    IF_NZ goto loop;
    LD_hl_A;
    POP_AF;
    RET;

}

void Mail_Draw7TileRow(void){
//  //  unreferenced
    LD_B(7);
    JR(mMail_DrawRowLoop);

}

void Mail_Draw13TileRow(void){
    LD_B(13);
    JR(mMail_DrawRowLoop);

}

void Mail_Draw16TileRow(void){
    LD_B(16);
    JR(mMail_DrawRowLoop);

}

void Mail_DrawTopBottomBorder(void){
    LD_B(SCREEN_WIDTH - 2);
    JR(mMail_DrawRowLoop);

}

void Mail_DrawFullWidthBorder(void){
    LD_B(SCREEN_WIDTH);
// fallthrough

    return Mail_DrawRowLoop();
}

void Mail_DrawRowLoop(void){

loop:
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void Mail_DrawLeftRightBorder(void){
    LD_B(SCREEN_HEIGHT - 2);
    LD_DE(SCREEN_WIDTH);

loop:
    LD_hl_A;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void Mail_Draw2x2Graphic(void){
    PUSH_AF;
    LD_hli_A;
    INC_A;
    LD_hl_A;
    LD_BC(SCREEN_WIDTH - 1);
    ADD_HL_BC;
    INC_A;
    LD_hli_A;
    INC_A;
    LD_hl_A;
    POP_AF;
    RET;

}

void Mail_Draw3x2Graphic(void){
    LD_hli_A;
    INC_A;
    LD_hli_A;
    INC_A;
    LD_hl_A;
    LD_BC(SCREEN_WIDTH - 2);
    ADD_HL_BC;
    INC_A;
    LD_hli_A;
    INC_A;
    LD_hli_A;
    INC_A;
    LD_hl_A;
    RET;

}

void LoadMailGFX_Color1(void){

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void LoadMailGFX_Color2(void){

loop:
    XOR_A_A;
    LD_hli_A;
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void LoadMailGFX_Color3(void){

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    RET;

// INCLUDE "gfx/mail.asm"

    return ItemIsMail();
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
