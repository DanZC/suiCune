#include "../constants.h"
#include "mobile_12.h"
#include "mobile_menu.h"
#include "../engine/menus/init_gender.h"
#include "../home/math.h"
#include "../home/tilemap.h"
#include "../home/gfx.h"
#include "../home/delay.h"
#include "../home/copy.h"
#include "../home/text.h"
#include "../home/print_text.h"
#include "../home/menu.h"
#include "../home/joypad.h"
#include "../home/scrolling_menu.h"
#include "../engine/gfx/crystal_layouts.h"
#include "../engine/gfx/dma_transfer.h"
#include "../data/mobile/charmaps.h"
#include "../data/mobile/postcode_formats.h"
#include "../data/mobile/postcode_to_country_pairs.h"
#include "../util/variadic_macros.h"

const char* Prefectures[] = {
// Quick and dirty solution for the margin offset. In this list, strings must be left-aligned.
#if defined(_CRYSTAL_AU)
    "AU-ACT@",      // Australian Capital Territory
    "AU-NSW@",      // New South Wales
    "AU-NT @",      // Northern Territory
    "AU-QLD@",      // Queensland
    "AU-SA @",      // South Australia
    "AU-TAS@",      // Tasmania
    "AU-VIC@",      // Victoria
    "AU-WA @",      // Western Australia
    "NZ-AUK@",      // Auckland
    "NZ-BOP@",      // Bay of Plenty
    "NZ-CAN@",      // Canterbury
    "NZ-CIT@",      // Chatham Islands Territory
    "NZ-GIS@",      // Gisborne
    "NZ-WGN@",      // Wellington	
    "NZ-HKB@",      // Hawke's Bay
    "NZ-MWT@",      // Manawatu-Wanganui	
    "NZ-MBH@",      // Marlborough
    "NZ-NSN@",      // Nelson
    "NZ-NTL@",      // Northland
    "NZ-OTA@",      // Otago
    "NZ-STL@",      // Southland
    "NZ-TKI@",      // Taranaki	
    "NZ-TAS@",      // Tasman
    "NZ-WKO@",      // Waikato
    "NZ-WTC@",      // West Coast
#elif defined(_CRYSTAL_EU)
    "EU-AD@",       // Andorra
    "EU-AL@",       // Albania
    "EU-AT@",       // Austria
    "EU-BA@",       // Bosnia and Herzegovina
    "EU-BE@",       // Belgium
    "EU-BG@",       // Bulgaria
    "EU-BY@",       // Belarus
    "EU-CH@",       // Switzerland
    "EU-CZ@",       // Czech Republic
    "EU-DE@",       // Germany
    "EU-DK@",       // Denmark
    "EU-EE@",       // Estonia
    "EU-ES@",       // Spain
    "EU-FI@",       // Finland
    "EU-FR@",       // France
    "EU-GB@",       // United Kingdom
    "EU-GR@",       // Greece
    "EU-HR@",       // Croatia
    "EU-HU@",       // Hungary
    "EU-IE@",       // Ireland
    "EU-IS@",       // Iceland
    "EU-IT@",       // Italy
    "EU-LI@",       // Liechtenstein
    "EU-LT@",       // Lithuania
    "EU-LU@",       // Luxembourg
    "EU-LV@",       // Latvia
    "EU-MD@",       // Moldova
    "EU-MT@",       // Malta
    "EU-NL@",       // Netherlands
    "EU-NO@",       // Norway
    "EU-PL@",       // Poland
    "EU-PT@",       // Portugal
    "EU-RO@",       // Romania
    "EU-RS@",       // Serbia
    "EU-RU@",       // Russian Federation
    "EU-SE@",       // Sweden
    "EU-SI@",       // Slovenia
    "EU-SK@",       // Slovakia
    "EU-SM@",       // San Marino
    "EU-UA@",       // Ukraine
#elif defined(_CRYSTAL_JP)
    "あいちけん@"     //  Aichi
    "あおもりけん@"   //  Aomori
    "あきたけん@"     //  Akita
    "いしかわけん@"   //  Ishikawa
    "いばらきけん@"   //  Ibaraki
    "いわてけん@"     //  Iwate
    "えひめけん@"     //  Ehime
    "おおいたけん@"   //  Oita
    "おおさかふ@"     //  Osakafu
    "おかやまけん@"   //  Okayama
    "おきなわけん@"   //  Okinawa
    "かがわけん@"     //  Kagawa
    "かごしまけん@"   //  Kagoshima
    "かながわけん@"   //  Kanagawa
    "ぎふけん@"       //  Gifu
    "きょうとふ@"     //  Kyotofu
    "くまもとけん@"   //  Kumamoto
    "ぐんまけん@"     //  Gunma
    "こうちけん@"     //  Kochi
    "さいたまけん@"   //  Saitama
    "さがけん@"       //  Saga
    "しがけん@"       //  Shiga
    "しずおかけん@"   //  Shizuoka
    "しまねけん@"     //  Shimane
    "ちばけん@"       //  Chiba
    "とうきょうと@"   //  Tokyo
    "とくしまけん@"   //  Tokushima
    "とちぎけん@"     //  Tochigi
    "とっとりけん@"   //  Tottori
    "とやまけん@"     //  Toyama
    "ながさきけん@"   //  Nagasaki
    "ながのけん@"     //  Nagano
    "ならけん@"       //  Naraken
    "にいがたけん@"   //  Niigata
    "ひょうごけん@"   //  Hyogo
    "ひろしまけん@"   //  Hiroshima
    "ふくいけん@"     //  Fukui
    "ふくおかけん@"   //  Fukuoka
    "ふくしまけん@"   //  Fukushima
    "ほっかいどう@"   //  Hokkaido
    "みえけん@"       //  Mie
    "みやぎけん@"     //  Miyagi
    "みやざきけん@"   //  Miyazaki
    "やまがたけん@"   //  Yamagata
    "やまぐちけん@"   //  Yamaguchi
    "やまなしけん@"   //  Yamanashi
    "わかやまけん@"   //  Wakayama
#else
    "US-AL@",       // Alabama
    "US-AK@",       // Alaska
    "US-AZ@",       // Arizona
    "US-AR@",       // Arkansas
    "US-CA@",       // California
    "US-CO@",       // Colorado
    "US-CT@",       // Connecticut
    "US-DE@",       // Delaware
    "US-FL@",       // Florida
    "US-GA@",       // Georgia
    "US-HI@",       // Hawaii
    "US-ID@",       // Idaho
    "US-IL@",       // Illinois
    "US-IN@",       // Indiana
    "US-IA@",       // Iowa
    "US-KS@",       // Kansas
    "US-KY@",       // Kentucky
    "US-LA@",       // Louisiana
    "US-ME@",       // Maine
    "US-MD@",       // Maryland
    "US-MA@",       // Massachusetts
    "US-MI@",       // Michigan
    "US-MN@",       // Minnesota
    "US-MS@",       // Mississippi
    "US-MO@",       // Missouri
    "US-MT@",       // Montana
    "US-NE@",       // Nebraska
    "US-NV@",       // Nevada
    "US-NH@",       // New_Hampshire
    "US-NJ@",       // New_Jersey
    "US-NM@",       // New_Mexico
    "US-NY@",       // New_York
    "US-NC@",       // North_Carolina
    "US-ND@",       // North_Dakota
    "US-OH@",       // Ohio
    "US-OK@",       // Oklahoma
    "US-OR@",       // Oregon
    "US-PA@",       // Pennsylvania
    "US-RI@",       // Rhode_Island
    "US-SC@",       // South_Carolina
    "US-SD@",       // South_Dakota
    "US-TN@",       // Tennessee
    "US-TX@",       // Texas
    "US-UT@",       // Utah
    "US-VT@",       // Vermont
    "US-VA@",       // Virginia
    "US-WA@",       // Washington
    "US-WV@",       // West_Virginia
    "US-WI@",       // Wisconsin
    "US-WY@",       // Wyoming
    "CA-AB@",       // Alberta
    "CA-BC@",       // British Columbia
    "CA-MB@",       // Manitoba
    "CA-NB@",       // New Brunswick
    "CA-NL@",       // Newfoundland and Labrador
    "CA-NT@",       // Northwest Territories
    "CA-NS@",       // Nova Scotia
    "CA-NU@",       // Nunavut
    "CA-ON@",       // Ontario
    "CA-PE@",       // Prince Edward Island
    "CA-QC@",       // Quebec
    "CA-SK@",       // Saskatchewan
    "CA-YT@",       // Yukon
#endif
};

uint8_t InitMobileProfile(uint8_t c){
    // XOR_A_A;
    // SET_A(6);
    // LD_addr_A(wd002);
    wram->wd002 = (1 << 6);
    // LD_HL(wd003);
    // SET_hl(0);
    bit_set(wram->wd003, 0);
    // LD_A_C;
    // AND_A_A;
    // CALL_Z (aInitCrystalData);
    if(c == 0)
        InitCrystalData();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aFunction48d3d);
    Function48d3d();
    // LD_A_addr(wd479);
    // BIT_A(1);
    // IF_Z goto not_yet_initialized;
    if(bit_test(wram->wd479[0], 1)) {
        // LD_A_addr(wd003);
        uint8_t d003 = wram->wd003;
        // SET_A(0);
        // SET_A(1);
        // SET_A(2);
        // SET_A(3);
        d003 |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
        // LD_addr_A(wd003);
        wram->wd003 = d003;
    }

// not_yet_initialized:
    // CALL(aFunction486bf);
    Function486bf();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // LD_DE(mMobileUpArrowGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x10);
    // LD_BC((BANK(aMobileUpArrowGFX) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x10, MobileUpArrowGFX, 0, 1);
    // LD_DE(mMobileDownArrowGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x11);
    // LD_BC((BANK(aMobileDownArrowGFX) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x11, MobileDownArrowGFX, 0, 1);
    // CALL(aFunction4a3a7);
    Function4a3a7();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_Z goto asm_4808a;
    if(bit_test(wram->wd002, 6)) {
        // CALL(aFunction48689);
        Function48689();
        // goto asm_480d7;
    }
    else {
    // asm_4808a:
        // LD_A(0x5);
        // LD_addr_A(wMusicFade);
        wram->wMusicFade = 0x5;
        // LD_A(LOW(MUSIC_MOBILE_ADAPTER_MENU));
        // LD_addr_A(wMusicFadeID);
        // LD_A(HIGH(MUSIC_MOBILE_ADAPTER_MENU));
        // LD_addr_A(wMusicFadeID + 1);
        wram->wMusicFadeID = MUSIC_MOBILE_ADAPTER_MENU;
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames_Conv(20);
        // LD_B(CRYSTAL_CGB_MOBILE_1);
        // CALL(aGetCrystalCGBLayout);
        GetCrystalCGBLayout(CRYSTAL_CGB_MOBILE_1);
        // CALL(aClearBGPalettes);
        ClearBGPalettes_Conv();
        // hlcoord(0, 0, wTilemap);
        // LD_B(2);
        // LD_C(20);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(0, 0, wram->wTilemap), 20, 2);
        // hlcoord(0, 1, wTilemap);
        // LD_A(0xc);
        // LD_hl_A;
        coord(0, 1, wram->wTilemap)[0] = 0xc;
        // LD_BC(0x13);
        // ADD_HL_BC;
        // LD_hl_A;
        coord(0, 1, wram->wTilemap)[0x13] = 0xc;
        // LD_DE(mMobileProfileString);
        // hlcoord(1, 1, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileProfileString), coord(1, 1, wram->wTilemap));
        // hlcoord(0, 2, wTilemap);
        // LD_B(0xa);
        // LD_C(0x12);
        // CALL(aFunction48cdc);
        Function48cdc(coord(0, 2, wram->wTilemap), 0xa, 0x12);
        // hlcoord(2, 4, wTilemap);
        // LD_DE(mMobileString_Gender);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileString_Gender), coord(2, 4, wram->wTilemap));
    }

// asm_480d7:
    // hlcoord(2, 6, wTilemap);
    // LD_DE(mMobileString_Age);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileString_Age), coord(2, 6, wram->wTilemap));
    // hlcoord(2, 8, wTilemap);
    // LD_DE(mMobileString_Address);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileString_Address), coord(2, 8, wram->wTilemap));
    // hlcoord(2, 10, wTilemap);
    // LD_DE(mMobileString_ZipCode);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileString_ZipCode), coord(2, 10, wram->wTilemap));
    // hlcoord(2, 12, wTilemap);
    // LD_DE(mMobileString_OK);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileString_OK), coord(2, 12, wram->wTilemap));
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_NZ goto asm_48113;
    if(bit_test(wram->wd002, 6)) {
        // LD_A_addr(wPlayerGender);
        // LD_HL(mStrings_484fb);
        // CALL(aGetNthString);
        // LD_D_H;
        // LD_E_L;
        // hlcoord(11, 4, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(Strings_484fb[wram->wPlayerGender]), coord(11, 4, wram->wTilemap));
    }

// asm_48113:
    // hlcoord(11, 6, wTilemap);
    // CALL(aFunction487ec);
    Function487ec(coord(11, 6, wram->wTilemap));
    // LD_A_addr(wd474);
    // DEC_A;
    // LD_HL(mPrefectures);
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // hlcoord(11, 8, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Prefectures[wram->wPrefecture]), coord(11, 8, wram->wTilemap));
    // hlcoord(11, 10, wTilemap);
    // CALL(aFunction489ea);
    Function489ea(coord(11, 10, wram->wTilemap));
    // hlcoord(0, 14, wTilemap);
    // LD_B(0x2);
    // LD_C(0x12);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 14, wram->wTilemap), 0x2, 0x12);
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mMobileString_PersonalInfo);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileString_PersonalInfo), coord(1, 16, wram->wTilemap));
    // CALL(aFunction48187);
    Function48187();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aStaticMenuJoypad);
    uint8_t joypad = StaticMenuJoypad_Conv();
    // LD_HL(wMenuCursorY);
    // LD_B_hl;
    // PUSH_BC;
    uint8_t b = wram->wMenuCursorY;
    // JR(masm_4815f); // Inlined
    while(1) {
        // BIT_A(A_BUTTON_F);
        // JP_NZ (mFunction4820d);
        if(bit_test(joypad, A_BUTTON_F)) {
            // Inlined
            uint8_t res = Function4820d();
            if(res != 0xff)
                return res;
            goto Function4840c;
        }
        // LD_B_A;
        // LD_A_addr(wd002);
        // BIT_A(6);
        // IF_Z goto dont_check_b_button;
        // LD_HL(wd479);
        // BIT_hl(1);
        // IF_Z goto dont_check_b_button;
        // BIT_B(B_BUTTON_F);
        // IF_NZ goto b_button;
        if(bit_test(wram->wd002, 6) && bit_test(wram->wd479[0], 1) && bit_test(joypad, B_BUTTON_F)) {
        // b_button:
            // CALL(aClearBGPalettes);
            ClearBGPalettes_Conv();
            // CALL(aFunction48d30);
            Function48d30();
            // POP_BC;
            // CALL(aClearTilemap);
            ClearTilemap_Conv2();
            // LD_A(0xff);
            // RET;
            return 0xff;
        }
    // dont_check_b_button:
        // JP(mFunction48272);

    Function4840c:
        // CALL(aFunction48187);
        Function48187();
        // CALL(aFunction48283);
        Function48283();
        // hlcoord(1, 16, wTilemap);
        // LD_DE(mMobileString_PersonalInfo);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileString_PersonalInfo), coord(1, 16, wram->wTilemap));
        // CALL(aFunction486bf);
        Function486bf();
        // POP_BC;
        // LD_HL(wMenuCursorY);
        // LD_hl_B;
        wram->wMenuCursorY = b;
        // LD_A_addr(wd002);
        // BIT_A(6);
        // IF_NZ goto narrower_box;
        if(bit_test(wram->wd002, 6)) {
        // narrower_box:
            // LD_B(7);
            // LD_C(1);
            // hlcoord(1, 6, wTilemap);
            // CALL(aClearBox);
            ClearBox_Conv2(coord(1, 6, wram->wTilemap), 1, 7);
            // JP(mFunction48157);
        }
        else {
            // LD_B(9);
            // LD_C(1);
            // hlcoord(1, 4, wTilemap);
            // CALL(aClearBox);
            ClearBox_Conv2(coord(1, 4, wram->wTilemap), 1, 9);
            // JP(mFunction48157);
        }

    // Function48157:
        // Inlined
        // CALL(aScrollingMenuJoypad);
        joypad = ScrollingMenuJoypad_Conv();
        // LD_HL(wMenuCursorY);
        // LD_B_hl;
        b = wram->wMenuCursorY;
        // PUSH_BC;
        // return asm_4815f();
    }
}

void Function48157(void){
    CALL(aScrollingMenuJoypad);
    LD_HL(wMenuCursorY);
    LD_B_hl;
    PUSH_BC;
    return asm_4815f();
}

void asm_4815f(void){
    BIT_A(A_BUTTON_F);
    JP_NZ (mFunction4820d);
    LD_B_A;
    LD_A_addr(wd002);
    BIT_A(6);
    IF_Z goto dont_check_b_button;
    LD_HL(wd479);
    BIT_hl(1);
    IF_Z goto dont_check_b_button;
    BIT_B(B_BUTTON_F);
    IF_NZ goto b_button;

dont_check_b_button:
    JP(mFunction48272);


b_button:
    CALL(aClearBGPalettes);
    CALL(aFunction48d30);
    POP_BC;
    CALL(aClearTilemap);
    LD_A(0xff);
    RET;

}

void Function48187(void){
static const char String_TellLater[] = "Tell Later@";
    // LD_A_addr(wd479);
    // BIT_A(1);
    // IF_NZ goto asm_481f1;
    if(bit_test(wram->wd479[0], 1))
        goto asm_481f1;
    // LD_A_addr(wd003);
    // LD_D_A;
    uint8_t d = wram->wd003;
    // CALL(aFunction48725);
    // IF_C goto asm_481a2;
    if(!Function48725()) {
        // LD_BC((1 << 8) | 4);
        // hlcoord(2, 12, wTilemap);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(2, 12, wram->wTilemap), 4, 1);
        // goto asm_481ad;
    }
    else {
    // asm_481a2:
        // PUSH_DE;
        // hlcoord(2, 12, wTilemap);
        // LD_DE(mMobileString_OK);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileString_OK), coord(2, 12, wram->wTilemap));
        // POP_DE;
    }

// asm_481ad:
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_NZ goto asm_481c1;
    // BIT_D(0);
    // IF_NZ goto asm_481c1;
    if(!bit_test(wram->wd002, 6) && !bit_test(d, 0)) {
        // LD_BC((1 << 8) | 8);
        // hlcoord(11, 4, wTilemap);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(11, 4, wram->wTilemap), 8, 1);
    }

// asm_481c1:
    // BIT_D(1);
    // IF_NZ goto asm_481ce;
    if(!bit_test(d, 1)) {
        // LD_BC((1 << 8) | 8);
        // hlcoord(11, 6, wTilemap);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(11, 6, wram->wTilemap), 8, 1);
    }

// asm_481ce:
    // BIT_D(2);
    // IF_NZ goto asm_481db;
    if(!bit_test(d, 2)) {
        // LD_BC((2 << 8) | 8);
        // hlcoord(11, 7, wTilemap);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(11, 7, wram->wTilemap), 8, 2);
    }

// asm_481db:
    // BIT_D(3);
    // IF_NZ goto asm_481f1;
    if(!bit_test(d, 3)) {
        // LD_A_addr(wd479);
        // BIT_A(0);
        // IF_NZ goto asm_481f8;
        if(bit_test(wram->wd479[0], 0))
            goto asm_481f8;
        // LD_BC((1 << 8) | 8);
        // hlcoord(11, 10, wTilemap);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(11, 10, wram->wTilemap), 8, 1);
        // goto asm_48201;
        return;
    }

asm_481f1:
    // LD_A_addr(wd479);
    // BIT_A(0);
    // IF_NZ goto asm_48201;
    if(!bit_test(wram->wd479[0], 0)) {
    asm_481f8:
        // hlcoord(11, 10, wTilemap);
        // LD_DE(mFunction48187_String_TellLater);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_TellLater), coord(11, 10, wram->wTilemap));
    }

// asm_48201:
    // RET;
    return;
}

uint8_t Function4820d(void){
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor_Conv();
    // LD_HL(wMenuCursorY);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t cursorY = wram->wMenuCursorY;
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_Z goto asm_4821f;
    if(bit_test(wram->wd002, 6)) {
        // POP_AF;
        // INC_A;
        cursorY++;
        // PUSH_AF;
    }

// asm_4821f:
    // POP_AF;
    switch(cursorY) {
        // CP_A(0x1);
        // JR_Z (masm_4828d);
        case 0x1: asm_4828d(); return 0xff;
        // CP_A(0x2);
        // JP_Z (mFunction4876f);
        case 0x2: Function4876f(); return 0xff;
        // CP_A(0x3);
        // JP_Z (mFunction48304);
        case 0x3: Function48304(); return 0xff; // TODO: Finish converting Function48304. // Function48304(); break;
        // CP_A(0x4);
        // JP_Z (mFunction488d3);
        case 0x4: Function488d3(); return 0xff;
    }
    // LD_A(0x2);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(0x2);
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_Z goto asm_4825c;
    // goto asm_4825c;
    if(bit_test(wram->wd002, 6) && false) { // dummied out?
        // hlcoord(1, 15, wTilemap);
        // LD_B(0x2);
        // LD_C(0x12);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(1, 15, wram->wTilemap), 0x12, 0x2);
        // LD_DE(mMobileString_ProfileChanged);
        // hlcoord(1, 16, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileString_ProfileChanged), coord(1, 16, wram->wTilemap));
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // LD_C(48);
        // CALL(aDelayFrames);
        DelayFrames_Conv(48);
    }

// asm_4825c:
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aFunction48d30);
    Function48d30();
    // POP_BC;
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // LD_HL(wd479);
    // SET_hl(1);
    bit_set(wram->wd479[0], 1);
    // XOR_A_A;
    // RET;
    return 0x0;
}

void Function48272(void){
    // JP(mFunction4840c);

}

const char MobileString_PersonalInfo[] = "Personal Info@";

// MobileProfile_ClearTextbox?
void Function48283(void){
    // LD_BC((2 << 8) | 18);
    // hlcoord(1, 15, wTilemap);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 15, wram->wTilemap), 18, 2);
    // RET;
}

void asm_4828d(void){
    // CALL(aFunction48283);
    Function48283();
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mMobileDesc_Gender);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileDesc_Gender), coord(1, 16, wram->wTilemap));
    // LD_HL(mMenuHeader_0x484f1);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_0x484f1);
    // CALL(aFunction4873c);
    Function4873c();
    // hlcoord(11, 2, wTilemap);
    // LD_B(0x4);
    // LD_C(0x7);
    // CALL(aFunction48cdc);
    Function48cdc(coord(11, 2, wram->wTilemap), 0x4, 0x7);
    // hlcoord(13, 4, wTilemap);
    // LD_DE(mString_484fb);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Strings_484fb[0]), coord(13, 4, wram->wTilemap));
    // hlcoord(13, 6, wTilemap);
    // LD_DE(mString_484ff);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Strings_484fb[1]), coord(13, 6, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_A_addr(wPlayerGender);
    // INC_A;
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wPlayerGender + 1;
    // CALL(aStaticMenuJoypad);
    uint8_t joypad = StaticMenuJoypad_Conv();
    // CALL(aPlayClickSFX);
    PlayClickSFX_Conv();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // BIT_A(0);
    // JP_Z (mFunction4840c);
    if(bit_test(joypad, A_BUTTON_F)) {
        // LD_HL(wMenuCursorY);
        // LD_A_hl;
        // LD_HL(mStrings_484fb);
        // CP_A(0x1);
        // IF_Z goto asm_482ed;
        const char* str;
        if(wram->wMenuCursorY == 0x1) {
        // asm_482ed:
            // XOR_A_A;
            // LD_addr_A(wPlayerGender);
            wram->wPlayerGender = 0x0;
            str = Strings_484fb[0];
        }
        else {
        // asm_482e1:
            // LD_A_hli;
            // CP_A(0x50);
            // IF_NZ goto asm_482e1;
            str = Strings_484fb[1];
            // LD_A(1 << PLAYERGENDER_FEMALE_F);
            // LD_addr_A(wPlayerGender);
            wram->wPlayerGender = 1 << PLAYERGENDER_FEMALE_F;
            // goto asm_482f1;
        }

    // asm_482f1:
        // LD_D_H;
        // LD_E_L;
        // hlcoord(11, 4, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(str), coord(11, 4, wram->wTilemap));
        // LD_A_addr(wd003);
        // SET_A(0);
        // LD_addr_A(wd003);
        bit_set(wram->wd003, 0);
    }
    // JP(mFunction4840c);
}

void Function48304(void){
    // CALL(aFunction48283);
    Function48283();
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mMobileDesc_Address);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileDesc_Address), coord(1, 16, wram->wTilemap));
    // LD_HL(mMenuHeader_0x48504);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_0x48504);
    // LD_HL(mMenuHeader_0x48513);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_0x48513);
    // hlcoord(10, 0, wTilemap);
    // LD_B(0xc);
    // LD_C(0x8);
    // CALL(aFunction48cdc);
    Function48cdc(coord(10, 0, wram->wTilemap), 0xc, 0x8);
    // LD_A_addr(wMenuCursorPosition);
    // LD_B_A;
    uint8_t cursorPos = wram->wMenuCursorPosition;
    // LD_A_addr(wMenuScrollPosition);
    // LD_C_A;
    uint8_t scrollPos = wram->wMenuScrollPosition;
    // PUSH_BC;
    // LD_A_addr(wd474);
    // DEC_A;
    uint8_t a = wram->wPrefecture - 1;
    // CP_A(0x29);
    // IF_C goto asm_4833f;
    if(a >= 0x29) {
        // SUB_A(0x29);
        // INC_A;
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = (a - 0x29) + 1;
        // LD_A(0x29);
        a = 0x29;
    }

// asm_4833f:
    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = a;
    // FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();

    bool cont = true;
    do {
    // asm_48348:
        // CALL(aScrollingMenu);
        uint8_t a = ScrollingMenu_Conv();
        // LD_DE(0x629);
        // CALL(aFunction48383);
        cont = Function48383(a, 0x629);
        // IF_C goto asm_48348;
    } while(cont);
    // LD_D_A;
    // POP_BC;
    // LD_A_B;
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = cursorPos;
    // LD_A_C;
    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = scrollPos;
    // LD_A_D;
    // PUSH_AF;
    // CALL(aExitMenu);
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    ExitMenu_Conv2();
    // POP_AF;
    // LDH_A_addr(hJoyPressed);
    // BIT_A(0);
    // IF_Z goto asm_48377;
    if(bit_test(hram->hJoyPressed, A_BUTTON_F)) {
        // CALL(aFunction483bb);
        Function483bb();
        // LD_A_addr(wd003);
        // SET_A(2);
        // LD_addr_A(wd003);
        bit_set(wram->wd003, 2);
    }

// asm_48377:
    // CALL(aFunction48187);
    Function48187();
    // FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    // JP(mFunction4840c);
}

bool Function48383(uint8_t a, uint16_t de){
    // PUSH_BC;
    // PUSH_AF;
    // BIT_A(5);
    // IF_NZ goto asm_48390;
    if(bit_test(a, 5)) {
    // asm_48390:
        // LD_A_addr(wMenuScrollPosition);
        // SUB_A_D;
        // LD_addr_A(wMenuScrollPosition);
        // IF_NC goto asm_483af;
        // XOR_A_A;
        // LD_addr_A(wMenuScrollPosition);
        // goto asm_483af;
        if(wram->wMenuScrollPosition < HIGH(de)) {
            wram->wMenuScrollPosition = 0;
        } else {
            wram->wMenuScrollPosition -= HIGH(de);
        }
    }
    // BIT_A(4);
    // IF_NZ goto asm_4839f;
    else if(bit_test(a, 4)) {
    // asm_4839f:
        // LD_A_addr(wMenuScrollPosition);
        // ADD_A_D;
        // LD_addr_A(wMenuScrollPosition);
        // CP_A_E;
        // IF_C goto asm_483af;
        // LD_A_E;
        // LD_addr_A(wMenuScrollPosition);
        // goto asm_483af;
        if(wram->wMenuScrollPosition + HIGH(de) > LOW(de)) {
            wram->wMenuScrollPosition = LOW(de);
        } else {
            wram->wMenuScrollPosition += HIGH(de);
        }
    }
    else {
        // AND_A_A;
        // goto asm_483b7;
        return false;
    }

// asm_483af:
    // LD_HL(wMenuCursorY);
    // LD_A_hl;
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wMenuCursorY;
    // SCF;

// asm_483b7:
    // POP_BC;
    // LD_A_B;
    // POP_BC;
    // RET;
    return true;
}

void Function483bb(void){
    // LD_HL(wScrollingMenuCursorPosition);
    // LD_A_hl;
    // INC_A;
    // LD_addr_A(wd474);
    wram->wPrefecture = wram->wScrollingMenuCursorPosition + 1;
    // DEC_A;
    // LD_B_A;
    uint8_t b = wram->wScrollingMenuCursorPosition;
    // LD_HL(mPrefectures);

// asm_483c8:
    // AND_A_A;
    // IF_Z goto asm_483d5;

// asm_483cb:
    // LD_A_hli;
    // CP_A(0x50);
    // IF_NZ goto asm_483cb;
    // LD_A_B;
    // DEC_A;
    // LD_B_A;
    // goto asm_483c8;
    const char* pref = (b < lengthof(Prefectures))? Prefectures[b]: "";

// asm_483d5:
    // LD_D_H;
    // LD_E_L;
    // LD_B(0x2);
    // LD_C(0x8);
    // hlcoord(11, 7, wTilemap);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(11, 7, wram->wTilemap), 0x8, 0x2);
    // hlcoord(11, 8, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(pref), coord(11, 8, wram->wTilemap));
    // RET;
}

void Function483e8(const struct MenuData* data, tile_t* de){
    (void)data;
    // PUSH_DE;
    // LD_HL(mPrefectures);
    // LD_A_addr(wMenuSelection);
    // CP_A(0xff);
    // IF_NZ goto asm_483f8;
    const char* hl;
    if(wram->wMenuSelection == 0xff || wram->wMenuSelection > lengthof(Prefectures) - 1) {
        // LD_HL(mWakayama);  // last string
        hl = Prefectures[lengthof(Prefectures) - 1];
        // goto asm_48405;
    }
    else {
    // asm_483f8:
        // LD_D_A;
        // AND_A_A;
        // IF_Z goto asm_48405;

    // asm_483fc:
        // LD_A_hli;
        // CP_A(0x50);
        // IF_NZ goto asm_483fc;
        // LD_A_D;
        // DEC_A;
        // goto asm_483f8;
        hl = Prefectures[wram->wMenuSelection];
    }

// asm_48405:
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(hl), de);
    // RET;
}

void Function4840c(void){
    // CALL(aFunction48187);
    Function48187();
    // CALL(aFunction48283);
    Function48283();
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mMobileString_PersonalInfo);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileString_PersonalInfo), coord(1, 16, wram->wTilemap));
    // CALL(aFunction486bf);
    Function486bf();
    POP_BC;
    LD_HL(wMenuCursorY);
    LD_hl_B;
    LD_A_addr(wd002);
    BIT_A(6);
    IF_NZ goto narrower_box;
    LD_B(9);
    LD_C(1);
    hlcoord(1, 4, wTilemap);
    CALL(aClearBox);
    JP(mFunction48157);


narrower_box:
    LD_B(7);
    LD_C(1);
    hlcoord(1, 6, wTilemap);
    CALL(aClearBox);
    JP(mFunction48157);

}

void Mobile12_Bin2Dec(tile_t* hl, uint8_t a){
    static const char* DigitStrings[] = {
        "0@",
        "1@",
        "2@",
        "3@",
        "4@",
        "5@",
        "6@",
        "7@",
        "8@",
        "9@",
    };
    // PUSH_BC;
    // PUSH_AF;
    // PUSH_DE;
    // PUSH_HL;
    // LD_HL(mMobile12_Bin2Dec_DigitStrings);

// loop:
    // AND_A_A;
    // IF_Z goto got_string;
    // INC_HL;
    // INC_HL;
    // DEC_A;
    // goto loop;

// got_string:
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(DigitStrings[a]), hl);
    // POP_DE;
    // POP_AF;
    // POP_BC;
    // RET;
}

const char MobileProfileString[] = "  Mobile Profile@";
const char MobileString_Gender[] = "Gender@";
const char MobileString_Age[] = "Age@";
const char MobileString_Address[] = "Address@";
const char MobileString_ZipCode[] = "Zip Code@";
const char MobileString_OK[] = "OK@";
const char MobileString_ProfileChanged[] = "Profile Changed@";
const char MobileDesc_Gender[] = "Boy or girl?@";
const char MobileDesc_Age[] = "How old are you?@";
const char MobileDesc_Address[] = "Where do you live?@";
const char MobileDesc_ZipCode[] = "Your zip code?@";

const struct MenuHeader MenuHeader_0x484f1 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 2, SCREEN_WIDTH - 1, 7),
    .data = &MenuData_0x484f9,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_0x484f9 = {
    .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
    //db ['2'];  // items
};

const char* Strings_484fb[] = {
// void String_484fb(void){
    "Boy@",
// void String_484ff(void){
    "Girl@",
};

const struct MenuHeader MenuHeader_0x48504 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(10, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
};

const struct MenuHeader MenuHeader_0x48509 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(10, 5, SCREEN_WIDTH - 1, 7),
};

const struct MenuHeader MenuHeader_0x4850e = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(10, 9, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
};

const struct MenuHeader MenuHeader_0x48513 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 1, SCREEN_WIDTH - 2, TEXTBOX_Y), // 18, 12
    .data = &MenuData_0x4851b,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_0x4851b = {
    .flags = SCROLLINGMENU_DISPLAY_ARROWS | SCROLLINGMENU_ENABLE_RIGHT | SCROLLINGMENU_ENABLE_LEFT | SCROLLINGMENU_CALL_FUNCTION1_CANCEL,  // flags
    .scrollingMenu = {
        .rows = 6, .cols = 0,  // rows, columns
        .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
        .list = (uint8_t[]) {
        // Items:
            lengthof(Prefectures),
            // for(int x = 0; x < 46; x++){
            //db ['x'];
            // In the future, replace this with a macro that automatically does this.
             0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
            10,11,12,13,14,15,16,17,18,19,
            20,21,22,23,24,25,26,27,28,29,
            30,31,32,33,34,35,36,37,38,39,
            40,41,42,43,44,45,46,47,48,49,
            50,51,52,53,54,55,56,57,58,59,
            60,61,62,
            // }
            //db ['-1'];
            -1,
        },
        .func1 = Function483e8,
        .func2 = NULL,
        .func3 = NULL,
    },
};

void Function48689(void){
    // LD_C(7);
    // CALL(aDelayFrames);
    DelayFrames_Conv(7);
    // LD_B(CRYSTAL_CGB_MOBILE_1);
    // CALL(aGetCrystalCGBLayout);
    GetCrystalCGBLayout(CRYSTAL_CGB_MOBILE_1);
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // hlcoord(0, 0, wTilemap);
    // LD_B(4);
    // LD_C(SCREEN_WIDTH);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(0, 0, wram->wTilemap), SCREEN_WIDTH, 4);
    // hlcoord(0, 2, wTilemap);
    // LD_A(0xc);
    // LD_hl_A;
    *coord(0, 2, wram->wTilemap) = 0xc;
    // LD_BC(SCREEN_WIDTH - 1);
    // ADD_HL_BC;
    // LD_hl_A;
    coord(0, 2, wram->wTilemap)[SCREEN_WIDTH - 1] = 0xc;
    // LD_DE(mMobileProfileString);
    // hlcoord(1, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileProfileString), coord(1, 2, wram->wTilemap));
    // hlcoord(0, 4, wTilemap);
    // LD_B(0x8);
    // LD_C(0x12);
    // CALL(aFunction48cdc);
    Function48cdc(coord(0, 4, wram->wTilemap), 0x8, 0x12);
    // RET;
}

// InitMobileProfile_InitMenu
void Function486bf(void){
    // LD_HL(w2DMenuCursorInitY);
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_NZ goto start_at_6;
    if(bit_test(wram->wd002, 6)) {
    // start_at_6:
        // LD_A(6);
        // LD_hli_A;
        wram->w2DMenuCursorInitY = 6;
    }
    else {
        // LD_A(4);
        // LD_hli_A;
        wram->w2DMenuCursorInitY = 4;
        // goto got_init_y;
    }

// got_init_y:
    // LD_A(1);
    // LD_hli_A;  // init x
    wram->w2DMenuCursorInitX = 1;
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_NZ goto check_wd479;
    if(bit_test(wram->wd002, 6)) {
    // check_wd479:
        // LD_A_addr(wd479);
        // BIT_A(1);
        // IF_NZ goto four_rows;
        // CALL(aFunction48725);
        // IF_C goto four_rows;
        if(bit_test(wram->wd479[0], 1) || Function48725()) {
        // four_rows:
            // LD_A(4);
            // LD_hli_A;
            wram->w2DMenuNumRows = 4;
        }
        else {
            // LD_A(3);
            // LD_hli_A;
            wram->w2DMenuNumRows = 3;
            // goto got_num_rows_2;
        }
    }
    // CALL(aFunction48725);
    // LD_A(4);
    // IF_NC goto got_num_rows_1;
    else if(!Function48725()) {
        wram->w2DMenuNumRows = 4;
    }
    // LD_A(5);
    else {
        wram->w2DMenuNumRows = 5;
    }

// got_num_rows_1:
    // LD_hli_A;
    // goto got_num_rows_2;

// got_num_rows_2:
    // LD_A(1);
    // LD_hli_A;  // num cols
    wram->w2DMenuNumCols = 1;
    // LD_hl(0);  // flags 1
    // SET_hl(5);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // INC_HL;
    // XOR_A_A;
    // LD_hli_A;  // flags 2
    wram->w2DMenuFlags2 = 0;
    // LD_A(0x20);
    // LD_hli_A;  // cursor offsets
    wram->w2DMenuCursorOffsets = (2 << 4) | 0;
    // LD_A(A_BUTTON);
    // ADD_A(D_UP);
    // ADD_A(D_DOWN);
    // PUSH_AF;
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_Z goto got_joypad_mask;
    if(bit_test(wram->wd002, 6)) {
        wram->wMenuJoypadFilter = (A_BUTTON | D_UP | D_DOWN);
    }
    else {
        wram->wMenuJoypadFilter = (A_BUTTON | D_UP | D_DOWN | B_BUTTON);
    }
    // POP_AF;
    // ADD_A(B_BUTTON);
    // PUSH_AF;

// got_joypad_mask:
    // POP_AF;
    // LD_hli_A;
    // LD_A(0x1);
    // LD_hli_A;  // cursor y
    wram->wMenuCursorY = 0x1;
    // LD_hli_A;  // cursor x
    wram->wMenuCursorX = 0x1;
    // XOR_A_A;
    // LD_hli_A;  // off char
    wram->wCursorOffCharacter = 0x0;
    // LD_hli_A;  // cursor tile
    // LD_hli_A;  // cursor tile + 1
    wram->wCursorCurrentTile = 0x0;
    // RET;
}

bool Function48725(void){
//      ld a, [wd003]
//      and $f
//      cp $f
//      jr nz, .clear_carry
//      scf
//      ret
//  .clear_carry
//      and a
//      ret

    // LD_A_addr(wd003);
    // BIT_A(0);
    // IF_Z goto clear_carry;
    // BIT_A(1);
    // IF_Z goto clear_carry;
    // BIT_A(2);
    // IF_Z goto clear_carry;
    // BIT_A(3);
    // IF_Z goto clear_carry;
    // SCF;
    // RET;


// clear_carry:
    // AND_A_A;
    // RET;
    return (wram->wd003 & 0xf) == 0xf;
}

void Function4873c(void){
    // LD_HL(w2DMenuCursorInitY);
    // LD_A(4);
    // LD_hli_A;
    wram->w2DMenuCursorInitY = 4;
    // LD_A(12);
    // LD_hli_A;  // init x
    wram->w2DMenuCursorInitX = 12;
    // LD_A(2);
    // LD_hli_A;  // num rows
    wram->w2DMenuNumRows = 2;
    // LD_A(1);
    // LD_hli_A;  // num cols
    wram->w2DMenuNumCols = 1;
    // LD_hl(0);  // flags 1
    // SET_hl(5);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // INC_HL;
    // XOR_A_A;
    // LD_hli_A;  // flags 2
    wram->w2DMenuFlags2 = 0;
    // LD_A((2 << 4) | 0);
    // LD_hli_A;  // cursor offsets
    wram->w2DMenuCursorOffsets = (2 << 4) | 0;
    // LD_A(A_BUTTON);
    // ADD_A(B_BUTTON);
    // LD_hli_A;  // joypad filter
    wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON);
// ld a, [wPlayerGender]
// xor 1 << PLAYERGENDER_FEMALE_F
// inc a
    // LD_A_addr(wPlayerGender);
    // AND_A_A;
    // IF_Z goto male;
    // LD_A(2);
    // goto okay_gender;

// male:
    // LD_A(1);

// okay_gender:
    // LD_hli_A;  // cursor y
    wram->wMenuCursorY = (wram->wPlayerGender ^ (1 << PLAYERGENDER_FEMALE_F)) + 1;
    // LD_A(0x1);
    // LD_hli_A;  // cursor x
    wram->wMenuCursorX = 0x1;
    // XOR_A_A;
    // LD_hli_A;  // off char
    wram->wCursorOffCharacter = 0x0;
    // LD_hli_A;  // cursor tile
    // LD_hli_A;  // cursor tile + 1
    wram->wCursorCurrentTile = 0x0;
    // RET;
}

// MobileProfile_Age
void Function4876f(void){
    // CALL(aFunction48283);
    Function48283();
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mMobileDesc_Age);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileDesc_Age), coord(1, 16, wram->wTilemap));
    // LD_HL(mMenuHeader_0x48509);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_0x48509);
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // hlcoord(10, 5, wTilemap);
    // LD_B(0x1);
    // LD_C(0x8);
    // CALL(aFunction48cdc);
    Function48cdc(coord(10, 5, wram->wTilemap), 0x1, 0x8);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_A_addr(wd473);
    // AND_A_A;
    // IF_Z goto asm_487ab;
    if(wram->wAge == 0) {
    // asm_487ab:
        // hlcoord(12, 5, wTilemap);
        // LD_hl(0x10);
        *coord(12, 5, wram->wTilemap) = 0x10;
        // goto asm_487b7;
    }
    // CP_A(0x64);
    // IF_Z goto asm_487b2;
    else if(wram->wAge == 0x64) {
    // asm_487b2:
        // hlcoord(12, 7, wTilemap);
        // LD_hl(0x11);
        *coord(12, 7, wram->wTilemap) = 0x11;
    }
    else {
        // hlcoord(12, 5, wTilemap);
        // LD_hl(0x10);
        *coord(12, 5, wram->wTilemap) = 0x10;
        // hlcoord(12, 7, wTilemap);
        // LD_hl(0x11);
        *coord(12, 7, wram->wTilemap) = 0x11;
        // goto asm_487b7;
    }

// asm_487b7:
    // hlcoord(11, 6, wTilemap);
    // CALL(aFunction487ec);
    Function487ec(coord(11, 6, wram->wTilemap));
    // LD_C(10);
    // CALL(aDelayFrames);
    DelayFrames_Conv(10);
    // LD_A_addr(wd473);
    // PUSH_AF;
    uint8_t d473 = wram->wAge;

    u8_flag_s res;
    do {
    // asm_487c6:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        DelayFrame();
        // CALL(aFunction4880e);
        res = Function4880e();
        // IF_NC goto asm_487c6;
    } while(!res.flag);
    // LD_A(0x1);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(0x1);
    // POP_BC;
    // IF_NZ goto asm_487da;
    if(res.a == 0) {
        // LD_A_B;
        // LD_addr_A(wd473);
        wram->wAge = d473;
    }

// asm_487da:
    // LD_A_addr(wd473);
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // hlcoord(11, 6, wTilemap);
    // CALL(aFunction487ec);
    Function487ec(coord(11, 6, wram->wTilemap));
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // JP(mFunction4840c);
}

// MobileProfile_PrintCurrentSelectionNumber
void Function487ec(tile_t* hl){
    // PUSH_HL;
    // LD_DE(wd473);
    // CALL(aFunction487ff);
    Function487ff(hl, &wram->wAge);
    // POP_HL;
    // for(int rept = 0; rept < 4; rept++){
    // INC_HL;
    // }
    // LD_DE(mString_4880d);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_4880d), hl + 4);
    // RET;
}

// MobileProfile_PrintNumber
void Function487ff(tile_t* hl, const uint8_t* de){
    // PUSH_HL;
    // LD_A(0x7f);
    // LD_hli_A;
    hl[0] = 0x7f;
    // LD_hl_A;
    hl[1] = 0x7f;
    // POP_HL;
    // LD_B(PRINTNUM_LEADINGZEROS | 1);
    // LD_C(3);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, de, PRINTNUM_LEADINGZEROS | 1, 3);
    // RET;
}

const char String_4880d[] = "@"; // Dummied out?

u8_flag_s Function4880e(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON);
    // JP_NZ (mFunction488b9);
    if(hram->hJoyPressed & A_BUTTON)
        return Function488b9();
    // LDH_A_addr(hJoyPressed);
    // AND_A(B_BUTTON);
    // JP_NZ (mFunction488b4);
    if(hram->hJoyPressed & B_BUTTON)
        return Function488b4();
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto asm_48843;
    if(hram->hJoyLast & D_UP) {
    // asm_48843:
        // LD_HL(wd473);
        // LD_A_hl;
        // CP_A(0x64);
        // IF_NC goto asm_4884c;
        if(wram->wAge < 0x64) {
            // INC_A;
            wram->wAge++;
        }

    // asm_4884c:
        // LD_hl_A;
        // goto asm_4886f;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto asm_48838;
    else if(hram->hJoyLast & D_DOWN) {
    // asm_48838:
        // LD_HL(wd473);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto asm_48840;
        if(wram->wAge != 0x0) {
            // DEC_A;
            wram->wAge--;
        }

    // asm_48840:
        // LD_hl_A;
        // goto asm_4886f;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto asm_4884f;
    else if(hram->hJoyLast & D_LEFT) {
    // asm_4884f:
        // LD_A_addr(wd473);
        // CP_A(0x5b);
        // IF_C goto asm_48858;
        if(wram->wAge > (0x64 - 0xa)) {
            // LD_A(0x5a);
            wram->wAge = (0x64 - 0xa);
        }

    // asm_48858:
        // ADD_A(0xa);
        // LD_addr_A(wd473);
        wram->wAge += 0xa;
        // goto asm_4886f;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto asm_4885f;
    else if(hram->hJoyLast & D_RIGHT) {
    // asm_4885f:
        // LD_A_addr(wd473);
        // CP_A(0xa);
        // IF_NC goto asm_48868;
        if(wram->wAge < 0xa) {
            // LD_A(0xa);
            wram->wAge = 0xa;
        }

    // asm_48868:
        // SUB_A(0xa);
        // LD_addr_A(wd473);
        wram->wAge -= 0xa;
        // goto asm_4886f;
    }
    else {
        // CALL(aDelayFrame);
        // AND_A_A;
        // RET;
        return u8_flag(0, false);
    }

// asm_4886f:
    // LD_A_addr(wd473);
    // AND_A_A;
    // IF_Z goto asm_48887;
    if(wram->wAge == 0) {
    // asm_48887:
        // hlcoord(10, 5, wTilemap);
        // LD_B(0x1);
        // LD_C(0x8);
        // CALL(aFunction48cdc);
        Function48cdc(coord(10, 5, wram->wTilemap), 0x1, 0x8);
        // hlcoord(12, 5, wTilemap);
        // LD_hl(0x10);
        *coord(12, 5, wram->wTilemap) = 0x10;
        // goto asm_488a7;
    }
    // CP_A(0x64);
    // IF_Z goto asm_48898;
    // IF_Z goto asm_488a7; // Dummied out destination?
    else if(wram->wAge == 0x64) {
    // asm_48898:
        // hlcoord(10, 5, wTilemap);
        // LD_B(0x1);
        // LD_C(0x8);
        // CALL(aFunction48cdc);
        Function48cdc(coord(10, 5, wram->wTilemap), 0x1, 0x8);
        // hlcoord(12, 7, wTilemap);
        // LD_hl(0x11);
        *coord(12, 7, wram->wTilemap) = 0x11;
    }
    else {
        // hlcoord(12, 5, wTilemap);
        // LD_hl(0x10);
        *coord(12, 5, wram->wTilemap) = 0x10;
        // hlcoord(12, 7, wTilemap);
        // LD_hl(0x11);
        *coord(12, 7, wram->wTilemap) = 0x11;
        // goto asm_488a7;
    }

// asm_488a7:
    // hlcoord(11, 6, wTilemap);
    // CALL(aFunction487ec);
    Function487ec(coord(11, 6, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_A(0x1);
    // AND_A_A;
    // RET;
    return u8_flag(0x1, false);
}

u8_flag_s Function488b4(void){
    // LD_A(0x0);
    // AND_A_A;
    // SCF;
    // RET;
    return u8_flag(0x0, true);
}

u8_flag_s Function488b9(void){
    // LD_A_addr(wd003);
    // SET_A(1);
    // LD_addr_A(wd003);
    bit_set(wram->wd003, 1);
    // SCF;
    // RET;
    return u8_flag(wram->wd003, true);
}

const char MobileUpArrowGFX[] = "gfx/mobile/up_arrow.png";
const char MobileDownArrowGFX[] = "gfx/mobile/down_arrow.png";

// MobileProfile_ZipCode
void Function488d3(void){
    // CALL(aFunction48283);
    Function48283();
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mMobileDesc_ZipCode);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileDesc_ZipCode), coord(1, 16, wram->wTilemap));
    // CALL(aFunction48a3a);
    // JP_C (mFunction4840c);
    if(Function48a3a())
        return;
    // LD_HL(mMenuHeader_0x4850e);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_0x4850e);
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // hlcoord(10, 9, wTilemap);
    // LD_B(0x1);
    // LD_C(0x8);
    // CALL(aFunction48cdc);
    Function48cdc(coord(10, 9, wram->wTilemap), 0x1, 0x8);
    // LD_A_addr(wd475);
    // AND_A(0xf);
    // LD_D(0x0); // This doesn't appear to have any effect.
    // hlcoord(11, 10, wTilemap);
    // CALL(aFunction489ea);
    Function489ea(coord(11, 10, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_A_addr(wd475);
    // LD_B_A;
    // LD_A_addr(wd476);
    // LD_C_A;
    uint16_t bc = (wram->wd475 << 8) | wram->wd476;
    // LD_A_addr(wd477);
    // LD_D_A;
    // LD_A_addr(wd478);
    // LD_E_A;
    uint16_t de = (wram->wd477 << 8) | wram->wd478;
    // PUSH_DE;
    // PUSH_BC;
    // LD_D(0x0);
    uint8_t d = 0x0;
    // LD_B(0x0);
    uint8_t b = 0x0;

    return asm_48922(bc, de, b, d, inMenu);
}

// MobileProfile_ZipCodeLoop
void asm_48922(uint16_t bc, uint16_t de, uint8_t b, uint8_t d, uint8_t inMenu){
    u8_flag_s res;
    do {
        // PUSH_BC;
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        DelayFrame();
        // LDH_A_addr(hJoyDown);
        // AND_A_A;
        // JP_Z (mFunction4896e);
        // BIT_A(0);
        // JP_NZ (mFunction4896e);
        // BIT_A(1);
        // JP_NZ (mFunction4896e);
        if(hram->hJoyDown == 0 || bit_test(hram->hJoyDown, A_BUTTON_F) || bit_test(hram->hJoyDown, B_BUTTON_F)) {
            // return Function4896e(bc, de, d); // inlined
            b = 0;
        }
        else {
            // LD_A_addr(wd002);
            // AND_A(0b11001111);
            // RES_A(7);
            // LD_addr_A(wd002);
            wram->wd002 = ((wram->wd002 & 0b11001111) & (uint8_t)~(1 << 7)); // wd002 & 0b01001111
            // POP_BC;
            // INC_B;
            ++b;
            // LD_A_B;
            // CP_A(0x5);
            // PUSH_BC;
            // IF_C goto asm_4894c;
            if(b >= 0x5) {
                // POP_BC;
                // LD_B(0x4);
                // PUSH_BC;
                b = 0x4;
            }

        // asm_4894c:
            // POP_BC;
            // PUSH_BC;
            // LD_A_B;
            // CP_A(0x4);
            // JR_NZ (masm_48972);
            if(b == 0x4) {
                // LD_C(10);
                // CALL(aDelayFrames);
                DelayFrames_Conv(10); // why?
            }
        }
        // JR(masm_48972); // inlined
        // CALL(aFunction48ab5);
        res = Function48ab5(&d);
        // PUSH_AF;
        // CP_A(0xf0);
        // IF_Z goto asm_48994;
        if(res.a & 0xf0) {
            // CP_A(0xf);
            // IF_NZ goto asm_48988;
            if((res.a & 0xf) == 0) {
                // LD_A_addr(wd002);
                // SET_A(7);
                // AND_A(0xcf);
                // LD_addr_A(wd002);
                wram->wd002 = (wram->wd002 | (1 << 7)) & 0xcf;
            }

        // asm_48988:
            // hlcoord(11, 10, wTilemap);
            // LD_B(0x0);
            // LD_C_D;
            // ADD_HL_BC;
            // LD_B(0x3);
            // CALL(aFunction48c11);
            Function48c11(coord(11, 10, wram->wTilemap) + d, 0x3, d);
        }

    // asm_48994:
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // POP_AF;
        // POP_BC;
        // JR_NC (masm_48922);
    } while(!res.flag);
    // IF_NZ goto asm_489b1;
    if(res.a == 0) {
        // POP_BC;
        // LD_A_B;
        // LD_addr_A(wd475);
        wram->wd475 = HIGH(de);
        // LD_A_C;
        // LD_addr_A(wd476);
        wram->wd476 = LOW(de);
        // POP_BC;
        // LD_A_B;
        // LD_addr_A(wd477);
        wram->wd477 = HIGH(bc);
        // LD_A_C;
        // LD_addr_A(wd478);
        wram->wd478 = LOW(bc);
        // goto asm_489c5;
    }
    else {
    // asm_489b1:
        // PUSH_AF;
        // LD_A_addr(wd479);
        // SET_A(0);
        // LD_addr_A(wd479);
        bit_set(wram->wd479[0], 0);
        // LD_A_addr(wd003);
        // SET_A(3);
        // LD_addr_A(wd003);
        bit_set(wram->wd003, 3);
        // POP_AF;
        // POP_BC;
        // POP_BC;
    }

// asm_489c5:
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // LD_A(0x1);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(0x1);
    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // hlcoord(11, 10, wTilemap);
    // CALL(aFunction489ea);
    Function489ea(coord(11, 10, wram->wTilemap));
    // hlcoord(11, 9, wTilemap);
    // LD_BC((1 << 8) | 8);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(11, 9, wram->wTilemap), 8, 1);
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // JP(mFunction4840c);
}

void Function4895a(void){
//  //  unreferenced
    // LDH_A_addr(hJoyPressed);
    // AND_A_A;
    // IF_Z goto asm_48965;
    // POP_BC;
    // LD_B(0x1);
    // PUSH_BC;
    // JR(masm_48972);


// asm_48965:
    // LDH_A_addr(hJoyLast);
    // AND_A_A;
    // JR_Z (masm_48972);

    // POP_BC;
    // LD_B(0x1);
    // PUSH_BC;

    // return Function4896e();
}

// void Function4896e(uint16_t bc, uint16_t de, uint8_t d){
    // POP_BC;
    // LD_B(0x0);
    // PUSH_BC;

    // return asm_48972(bc, de, 0x0, d);
// }

// inlined
// void asm_48972(uint16_t bc, uint16_t de, uint8_t b, uint8_t d){
//     // CALL(aFunction48ab5);
//     u8_flag_s res = Function48ab5(d);
//     // PUSH_AF;
//     // CP_A(0xf0);
//     // IF_Z goto asm_48994;
//     if(res.a & 0xf0) {
//         // CP_A(0xf);
//         // IF_NZ goto asm_48988;
//         if((res.a & 0xf) == 0) {
//             // LD_A_addr(wd002);
//             // SET_A(7);
//             // AND_A(0xcf);
//             // LD_addr_A(wd002);
//             wram->wd002 = (wram->wd002 | (1 << 7)) & 0xcf;
//         }

//     // asm_48988:
//         // hlcoord(11, 10, wTilemap);
//         // LD_B(0x0);
//         // LD_C_D;
//         // ADD_HL_BC;
//         // LD_B(0x3);
//         // CALL(aFunction48c11);
//         Function48c11(coord(11, 10, wram->wTilemap) + d, 0x3, d);
//     }

// // asm_48994:
//     // CALL(aWaitBGMap);
//     WaitBGMap_Conv();
//     // POP_AF;
//     // POP_BC;
//     // JR_NC (masm_48922);
//     IF_NZ goto asm_489b1;
//     POP_BC;
//     LD_A_B;
//     LD_addr_A(wd475);
//     LD_A_C;
//     LD_addr_A(wd476);
//     POP_BC;
//     LD_A_B;
//     LD_addr_A(wd477);
//     LD_A_C;
//     LD_addr_A(wd478);
//     goto asm_489c5;

// asm_489b1:
//     PUSH_AF;
//     LD_A_addr(wd479);
//     SET_A(0);
//     LD_addr_A(wd479);
//     LD_A_addr(wd003);
//     SET_A(3);
//     LD_addr_A(wd003);
//     POP_AF;
//     POP_BC;
//     POP_BC;

// asm_489c5:
//     PUSH_AF;
//     PUSH_BC;
//     PUSH_DE;
//     PUSH_HL;
//     LD_A(0x1);
//     CALL(aMenuClickSound);
//     POP_HL;
//     POP_DE;
//     POP_BC;
//     POP_AF;
//     CALL(aExitMenu);
//     hlcoord(11, 10, wTilemap);
//     CALL(aFunction489ea);
//     hlcoord(11, 9, wTilemap);
//     LD_BC((1 << 8) | 8);
//     CALL(aClearBox);
//     POP_AF;
//     LDH_addr_A(hInMenu);
//     JP(mFunction4840c);

// }

// MobileProfile_PrintSelections?
void Function489ea(tile_t* hl){
    // PUSH_DE;
    // LD_A_addr(wd475);
    // AND_A(0xf);
    // CALL(aMobile12_Bin2Dec);
    Mobile12_Bin2Dec(hl, wram->wd475 & 0xf);
    // LD_A_addr(wd476);
    // AND_A(0xf0);
    // SWAP_A;
    // INC_HL;
    // CALL(aMobile12_Bin2Dec);
    Mobile12_Bin2Dec(hl + 1, (wram->wd476 & 0xf0) >> 4);
    // LD_A_addr(wd476);
    // AND_A(0xf);
    // INC_HL;
    // CALL(aMobile12_Bin2Dec);
    Mobile12_Bin2Dec(hl + 2, wram->wd476 & 0xf);
    // INC_HL;
    // LD_DE(mString_48a38);
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl = hl + 3, .de = U82C(String_48a38)};
    PlaceString_Conv(&st, st.hl);
    // LD_A_addr(wd477);
    // AND_A(0xf0);
    // SWAP_A;
    // INC_HL;
    // CALL(aMobile12_Bin2Dec);
    Mobile12_Bin2Dec(st.hl + 1, (wram->wd477 & 0xf0) >> 4);
    // LD_A_addr(wd477);
    // AND_A(0xf);
    // INC_HL;
    // CALL(aMobile12_Bin2Dec);
    Mobile12_Bin2Dec(st.hl + 2, wram->wd477 & 0xf);
    // LD_A_addr(wd478);
    // AND_A(0xf0);
    // SWAP_A;
    // INC_HL;
    // CALL(aMobile12_Bin2Dec);
    Mobile12_Bin2Dec(st.hl + 3, (wram->wd478 & 0xf0) >> 4);
    // LD_A_addr(wd478);
    // AND_A(0xf);
    // INC_HL;
    // CALL(aMobile12_Bin2Dec);
    Mobile12_Bin2Dec(st.hl + 4, wram->wd478 & 0xf);
    // POP_DE;
    // RET;
}

const char String_48a38[] = "-@";

// MobileProfile_ZipCodeMenu
bool Function48a3a(void){
    // LD_HL(mMenuHeader_0x48a9c);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_0x48a9c);
    // CALL(aFunction4873c);
    Function4873c();
    // LD_A(0xa);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 0xa;
    // LD_A(0xb);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 0xb;
    // LD_A(0x1);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 0x1;
    // hlcoord(10, 8, wTilemap);
    // LD_B(0x4);
    // LD_C(0x8);
    // CALL(aFunction48cdc);
    Function48cdc(coord(10, 8, wram->wTilemap), 0x4, 0x8);
    // hlcoord(12, 10, wTilemap);
    // LD_DE(mString_48aa1);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_48aa1), coord(12, 10, wram->wTilemap));
    // CALL(aStaticMenuJoypad);
    // PUSH_AF;
    uint8_t joypad = StaticMenuJoypad_Conv();
    // CALL(aPlayClickSFX);
    PlayClickSFX_Conv();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // POP_AF;
    // BIT_A(1);
    // JP_NZ (mFunction48a9a);
    if(bit_test(joypad, B_BUTTON_F))
        return true;
    // LD_A_addr(wMenuCursorY);
    // CP_A(0x1);
    // IF_Z goto asm_48a98;
    else if(wram->wMenuCursorY == 0x1)
        return false;
    // LD_A_addr(wd003);
    // SET_A(3);
    // LD_addr_A(wd003);
    bit_set(wram->wd003, 3);
    // LD_A_addr(wd479);
    // RES_A(0);
    // LD_addr_A(wd479);
    bit_reset(wram->wd479[0], 0);
    // XOR_A_A;
    // LD_BC(0x4);
    // LD_HL(wd475);
    // CALL(aByteFill);
    wram->wd475 = 0;
    wram->wd476 = 0;
    wram->wd477 = 0;
    wram->wd478 = 0;
    // JR(mFunction48a9a);

// asm_48a98:
    // AND_A_A;
    // RET;

// Function48a9a: // MobileProfile_ZipCodeMenu_SetCarry
    // SCF;
    // RET;
    return true;
}

const struct MenuHeader MenuHeader_0x48a9c = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(8, 8, SCREEN_WIDTH - 1, 13),
};

const char String_48aa1[] =
            "Tell Now"
    t_next  "Tell Later@";

u8_flag_s Function48ab5(uint8_t* d){
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON);
    // JP_NZ (mFunction48c0f);
    if(hram->hJoyPressed & A_BUTTON)
        return Function48c0f(hram->hJoyPressed & A_BUTTON);
    // LDH_A_addr(hJoyPressed);
    // AND_A(B_BUTTON);
    // JP_NZ (mFunction48c0d);
    if(hram->hJoyPressed & B_BUTTON)
        return Function48c0d();
    // LD_A_D;
    // AND_A_A;
    uint8_t* hl;
    uint8_t a;
    switch(*d) {
    // IF_Z goto asm_48adf;
    case 0x0:
    // asm_48adf:
        // LD_HL(wd475);
        hl = &wram->wd475;
        // LD_A_hl;
        // AND_A(0xf);
        a = *hl & 0xf;
        // goto asm_48b1d;
        break;
    // CP_A(0x1);
    // IF_Z goto asm_48ae7;
    case 0x1:
    // asm_48ae7:
        // LD_HL(wd476);
        hl = &wram->wd476;
        // LD_A_hl;
        // SWAP_A;
        // OR_A(0xf0);
        a = (*hl >> 4) | 0xf0;
        // goto asm_48b1d;
        break;
    // CP_A(0x2);
    // IF_Z goto asm_48af1;
    case 0x2:
    // asm_48af1:
        // LD_HL(wd476);
        hl = &wram->wd476;
        // LD_A_hl;
        // AND_A(0xf);
        a = *hl & 0xf;
        // goto asm_48b1d;
        break;
    // CP_A(0x3);
    // IF_Z goto asm_48af9;
    case 0x3:
    // asm_48af9:
        // LD_HL(wd477);
        hl = &wram->wd477;
        // LD_A_hl;
        // SWAP_A;
        // OR_A(0xf0);
        a = (*hl >> 4) | 0xf0;
        // goto asm_48b1d;
        break;
    // CP_A(0x4);
    // IF_Z goto asm_48b03;
    case 0x4:
    // asm_48b03:
        // LD_HL(wd477);
        hl = &wram->wd477;
        // LD_A_hl;
        // AND_A(0xf);
        a = *hl & 0xf;
        // goto asm_48b1d;
        break;
    // CP_A(0x5);
    // IF_Z goto asm_48b0b;
    case 0x5:
    // asm_48b0b:
        // LD_HL(wd478);
        hl = &wram->wd478;
        // LD_A_hl;
        // SWAP_A;
        // OR_A(0xf0);
        a = (*hl >> 4) | 0xf0;
        // goto asm_48b1d;
        break;
    // CP_A(0x6);
    // goto asm_48b15;
    default:
    case 0x6:
    // asm_48b15:
        // LD_HL(wd478);
        hl = &wram->wd478;
        // LD_A_hl;
        // AND_A(0xf);
        a = *hl & 0xf;
        // goto asm_48b1d;
        break;
    }

// asm_48b1d:
    // PUSH_HL;
    // PUSH_AF;
    // LD_E(0x0);
    uint8_t e = 0x0;
    // hlcoord(11, 10, wTilemap);
    // LD_A_D;
    uint8_t a2 = *d;

    while(a2) {
    // asm_48b25:
        // AND_A_A;
        // IF_Z goto asm_48b2c;
        // INC_E;
        e++;
        // DEC_A;
        a2--;
        // goto asm_48b25;
    }

// asm_48b2c:
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto asm_48b8d;
    if(hram->hJoyLast & D_UP) {
    // asm_48b8d:
        // POP_AF;
        // LD_B_A;
        // AND_A(0xf);
        // CP_A(0x9);
        // LD_A_B;
        // IF_C goto asm_48b9a;
        if((a & 0xf) >= 0x9) {
            // AND_A(0xf0);
            // ADD_A(0xff);
            a = a & 0xf0;
        }
        else {
        // asm_48b9a:
            // INC_A;
            a++;
        }
        goto asm_48b62;
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto asm_48b55;
    else if(hram->hJoyLast & D_DOWN) {
    // asm_48b55:
        // POP_AF;
        // LD_B_A;
        // AND_A(0xf);
        // AND_A_A;
        // LD_A_B;
        // IF_NZ goto asm_48b61;
        if((a & 0xf) == 0) {
            // AND_A(0xf0);
            // ADD_A(0xa);
            a = (a & 0xf0) + 0xa;
        }

    // asm_48b61:
        // DEC_A;
        a--;
        goto asm_48b62;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // JP_NZ (mFunction48bd7);
    else if(hram->hJoyLast & D_LEFT) {
        return Function48bd7(d);
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto asm_48b9d;
    else if(hram->hJoyLast & D_RIGHT) {
    // asm_48b9d:
        // PUSH_DE;
        // hlcoord(10, 9, wTilemap);
        // LD_B(0x1);
        // LD_C(0x8);
        // CALL(aFunction48cdc);
        Function48cdc(coord(10, 9, wram->wTilemap), 0x1, 0x8);
        // POP_DE;
        // LD_A_D;
        // CP_A(0x6);
        // IF_NC goto asm_48baf;
        if(*d < 0x6) {
            // INC_D;
            (*d)++;
        }

    // asm_48baf:
        // POP_AF;
        // POP_HL;
        // LD_B_A;
        // LD_A_D;
        // CP_A(0x6);
        // LD_A_B;
        // IF_Z goto asm_48bc4;
        // BIT_A(7);
        // IF_NZ goto asm_48bc4;
        if(*d != 0x6 && !bit_test(a, 7)) {
            // INC_HL;
            // LD_A_hl;
            // SWAP_A;
            // AND_A(0xf);
            // JR(masm_48bc7);
            return asm_48bc7();
        }
        else {
        // asm_48bc4:
            // LD_A_hl;
            // AND_A(0xf);

            return asm_48bc7();
        }
    }
    // hlcoord(11, 10, wTilemap);
    // CALL(aFunction489ea);
    Function489ea(coord(11, 10, wram->wTilemap));
    // LD_A_addr(wd002);
    // BIT_A(7);
    // IF_NZ goto asm_48b51; // Fallthrough to asm_48b51 anyway...
// asm_48b51:
    // POP_BC;
    // POP_BC;
    // AND_A_A;
    // RET;
    return u8_flag(wram->wd002, false);

asm_48b62:
    // PUSH_DE;
    // PUSH_AF;
    // hlcoord(10, 9, wTilemap);
    // LD_B(0x1);
    // LD_C(0x8);
    // CALL(aFunction48cdc);
    Function48cdc(coord(10, 9, wram->wTilemap), 0x1, 0x8);
    // POP_AF;
    // POP_DE;
    // hlcoord(11, 10, wTilemap);
    // tile_t* hl2 = coord(11, 10, wram->wTilemap); // Not used; pop hl overwrites this.
    // LD_B_A;
    // LD_A_D;
    // CP_A(0x3);
    // IF_C goto asm_48b7a;
    // if(d >= 0x3) {
        // INC_HL;
        // hl2++;
    // } // Pointless since pop hl overwrites this.

// asm_48b7a:
    // LD_A_B;
    // POP_HL;
    // BIT_A(7);
    // IF_Z goto asm_48b85;
    if(bit_test(a, 7)) {
        // CALL(aFunction48c4d);
        Function48c4d(hl, a);
        // goto asm_48b88;
    }
    else {
    // asm_48b85:
        // CALL(aFunction48c5a);
        Function48c5a(hl, a);
    }

// asm_48b88:
    // LD_A(0xf0);
    // JP(mFunction48c00);
    return Function48c00(0xf0);
}

u8_flag_s asm_48bc7(void){
    // hlcoord(11, 10, wTilemap); // Pointless. Never used.
    // PUSH_AF;
    // LD_A_D;
    // CP_A(0x3);
    // POP_BC;
    // LD_A_B;
    // IF_C goto asm_48bd3;
    // if(!carry) {
        // INC_HL;
    // }

// asm_48bd3:
    // LD_A(0xf);
    // JR(mFunction48c00);
    return Function48c00(0xf);
}

u8_flag_s Function48bd7(uint8_t* d){
    // PUSH_DE;
    // hlcoord(10, 9, wTilemap);
    // LD_B(0x1);
    // LD_C(0x8);
    // CALL(aFunction48cdc);
    Function48cdc(coord(10, 9, wram->wTilemap), 0x1, 0x8);
    // POP_DE;
    // LD_A_D;
    // AND_A_A;
    // POP_AF;
    // POP_HL;
    // LD_B_A;
    // LD_A_D;
    // AND_A_A;
    // LD_A_B;
    // IF_Z goto asm_48bf3;
    // BIT_A(7);
    // IF_Z goto asm_48bf8;
    if(*d == 0 || (*d != 0 && !bit_test(*d, 7))) {
        (*d)--;
    }
    // DEC_D;
    // DEC_HL;

// asm_48bf3:
    // LD_A_hl;
    // AND_A(0xf);
    // JR(masm_48bc7);

// asm_48bf8:
    // DEC_D;
    // LD_A_hl;
    // SWAP_A;
    // AND_A(0xf);
    // JR(masm_48bc7);
    return asm_48bc7();
}

u8_flag_s Function48c00(uint8_t a){
    // PUSH_AF;
    // hlcoord(11, 10, wTilemap);
    // CALL(aFunction489ea);
    Function489ea(coord(11, 10, wram->wTilemap));
    // LD_A(0x1);
    // AND_A_A;
    // POP_BC;
    // LD_A_B;
    // RET;
    return u8_flag(a, false);
}

u8_flag_s Function48c0d(void){
    // XOR_A_A;
    // AND_A_A;

    return Function48c0f(0x0);
}

u8_flag_s Function48c0f(uint8_t a){
    // SCF;
    // RET;
    return u8_flag(a, true);
}

void Function48c11(tile_t* hl, uint8_t b, uint8_t d){
    // LD_A_addr(wd002);
    // BIT_A(7);
    // IF_Z goto asm_48c20;
    if(bit_test(wram->wd002, 7)) {
        // LD_A_D;
        // CP_A(0x3);
        // IF_C goto asm_48c1e;
        if(d >= 0x3) {
            // INC_HL;
            hl++;
        }

    // asm_48c1e:
        // LD_hl(0x7f);
        *hl = 0x7f;
    }

// asm_48c20:
    // LD_A_addr(wd002);
    // SWAP_A;
    // AND_A(0x3);
    // INC_A;
    uint8_t a = (wram->wd002 >> 4) & 0x3;
    // CP_A_B;
    // IF_NZ goto asm_48c40;
    if(a == b) {
        // LD_A_addr(wd002);
        // BIT_A(7);
        // IF_Z goto asm_48c3a;
        // RES_A(7);
        // LD_addr_A(wd002);
        // XOR_A_A;
        // goto asm_48c40;
    // asm_48c3a:
        // SET_A(7);
        // LD_addr_A(wd002);
        // XOR_A_A;
        bit_toggle(wram->wd002, 7);
        a = 0;
    }

// asm_48c40:
    // SWAP_A;
    // LD_B_A;
    // LD_A_addr(wd002);
    // AND_A(0xcf);
    // OR_A_B;
    // LD_addr_A(wd002);
    wram->wd002 = (wram->wd002 & 0xcf) | (a << 4);
    // RET;
}

void Function48c4d(uint8_t* hl, uint8_t a){
    // SWAP_A;
    // AND_A(0xf0);
    // PUSH_AF;
    // LD_A_hl;
    // AND_A(0xf);
    // LD_hl_A;
    // POP_AF;
    // OR_A_hl;
    // LD_hl_A;
    // RET;
    *hl = ((*hl & 0xf) | ((a << 4) & 0xf0));
}

void Function48c5a(uint8_t* hl, uint8_t a){
    // PUSH_AF;
    // LD_A_hl;
    // AND_A(0xf0);
    // LD_hl_A;
    // POP_AF;
    // OR_A_hl;
    // LD_hl_A;
    // RET;
    *hl = ((*hl & 0xf0) | a);
}

// Mobile_CopyPrefectureNameString
bool Function48c63(uint8_t* de, uint8_t c){
    uint8_t buffer[0x20];
    // LD_A(0x50);
    // LD_de_A;
    *de = c;
    // LD_A_C;
    // CP_A(0x30);
    // IF_NC goto asm_48c8c;
    // AND_A_A;
    // IF_Z goto asm_48c8c;
    if(c >= lengthof(Prefectures) || c == 0) {
    // asm_48c8c:
        // SCF;
        // RET;
        return true;
    }
    // DEC_C;
    --c;
    // PUSH_DE;
    // LD_H_D;
    // LD_L_E;
    uint8_t* hl = de;
    // LD_A(0x50);
    // LD_B(7);
    uint8_t b = 7;

    do {
    // asm_48c76:
        // LD_hli_A;
        *(hl++) = 0x50;
        // DEC_B;
        // IF_NZ goto asm_48c76;
    } while(--b != 0);
    // LD_HL(mPrefectures);
    // LD_A_C;
    // CALL(aGetNthString);
    hl = U82CA(buffer, Prefectures[c]);

    do {
    // asm_48c81:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(de++) = *(hl++);
        // LD_A_hl;
        // CP_A(0x50);
        // IF_NZ goto asm_48c81;
    } while(*hl != 0x50);
    // AND_A_A;
    // POP_DE;
    // RET;
    return false;
}

void Function48c8e(void){
//  //  unreferenced
    LD_HL(wd019 + 0x11);
    LD_D_H;
    LD_E_L;
    FARCALL(aFunction48c63);
    hlcoord(10, 7, wTilemap);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    RET;

}

void Function48ca3(void){
//  //  unreferenced
    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_B(0);
    LD_C(0);
    LD_D(0);

asm_48cad:
    CP_A(100);
    IF_C goto asm_48cb6;
    SUB_A(100);
    INC_B;
    goto asm_48cad;


asm_48cb6:
    CP_A(10);
    IF_C goto asm_48cbf;
    SUB_A(10);
    INC_C;
    goto asm_48cb6;


asm_48cbf:
    CP_A(1);
    IF_C goto asm_48cc7;
    DEC_A;
    INC_D;
    goto asm_48cbf;


asm_48cc7:
    LD_A_B;
    CALL(aMobile12_Bin2Dec);
    INC_HL;
    LD_A_C;
    CALL(aMobile12_Bin2Dec);
    INC_HL;
    LD_A_D;
    CALL(aMobile12_Bin2Dec);
    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    RET;

}

// MobileTextboxFrame_de
void Function48cda(tile_t* de, uint8_t b, uint8_t c){
    // LD_H_D;
    // LD_L_E;

    return Function48cdc(de, b, c);
}

// MobileTextboxFrame
void Function48cdc(tile_t* hl, uint8_t b, uint8_t c){
    // PUSH_BC;
    // PUSH_HL;
    // CALL(aFunction48cfd);
    Function48cfd(hl, b, c);
    // POP_HL;
    // POP_BC;
    // LD_DE(wAttrmap - wTilemap);
    // ADD_HL_DE;
    hl += wAttrmap - wTilemap;
    // INC_B;
    // INC_B;
    b += 2;
    // INC_C;
    // INC_C;
    c += 2;
    // LD_A(0x0);
    uint8_t a = 0x0;

    do {
    // asm_48ced:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        tile_t* hl2 = hl;
        
        do {
        // asm_48cef:
            // LD_hli_A;
            *(hl2++) = a;
            // DEC_C;
            // IF_NZ goto asm_48cef;
        } while(--c2 != 0);
        // POP_HL;
        // LD_DE(0x14);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto asm_48ced;
    } while(--b != 0);
    // RET;
}

void Function48cfd(tile_t* hl, uint8_t b, uint8_t c){
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x4);
    // LD_hli_A;
    *(hl2++) = 0x4;
    // INC_A;
    // CALL(aFunction48d2a);
    hl2 = Function48d2a(hl2, 0x5, c);
    // INC_A;
    // LD_hl_A;
    *hl2 = 0x6;
    // POP_HL;
    // LD_DE(0x14);
    // ADD_HL_DE;
    hl += SCREEN_WIDTH;

    do {
    // asm_48d0c:
        // PUSH_HL;
        hl2 = hl;
        // LD_A(0x7);
        // LD_hli_A;
        *(hl2++) = 0x7;
        // LD_A(0x7f);
        // CALL(aFunction48d2a);
        hl2 = Function48d2a(hl2, 0x7f, c);
        // LD_hl(0x8);
        *hl2 = 0x8;
        // POP_HL;
        // LD_DE(0x14);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto asm_48d0c;
    } while(--b != 0);
    // LD_A(0x9);
    // LD_hli_A;
    *(hl++) = 0x9;
    // LD_A(0xa);
    // CALL(aFunction48d2a);
    hl = Function48d2a(hl, 0xa, c);
    // LD_hl(0xb);
    *hl = 0xb;
    // RET;
}

// MobileTextboxFrame_DrawTiles
tile_t* Function48d2a(tile_t* hl, tile_t a, uint8_t c){
    // LD_D_C;

    do {
    // asm_48d2b:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_D;
        // IF_NZ goto asm_48d2b;
    } while(--c != 0);
    // RET;
    return hl;
}

void Function48d30(void){
    // LD_HL(wd475);
    // CALL(aFunction48d4a);
    Function48d4a(&wram->wd475);
    // LD_HL(wd477);
    // CALL(aFunction48d4a);
    Function48d4a(&wram->wd477);
    // RET;

}

void Function48d3d(void){
    // LD_HL(wd475);
    // CALL(aFunction48d94);
    Function48d94(&wram->wd475);
    // LD_HL(wd477);
    // CALL(aFunction48d94);
    Function48d94(&wram->wd477);
    // RET;
}

void Function48d4a(uint8_t* hl){
    // INC_HL;
    // LD_A_hl;
    // LD_B_A;
    uint8_t b = (hl[1] >> 4) & 0xf;
    // AND_A(0xf);
    // LD_C_A;
    uint8_t c = hl[1] & 0xf;
    // SRL_B;
    // SRL_B;
    // SRL_B;
    // SRL_B;
    // PUSH_BC;
    // LD_C(10);
    // LD_A_B;
    // CALL(aSimpleMultiply);
    // POP_BC;
    // ADD_A_C;
    // LD_hld_A;
    hl[1] = (b * 10) + c;
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hl;
    // SRL_A;
    // SRL_A;
    // SRL_A;
    // SRL_A;
    // LD_C(10);
    // CALL(aSimpleMultiply);
    // LD_B_A;
    b = 10 * (hl[0] >> 4);
    // LD_A_hli;
    // AND_A(0xf);
    // ADD_A_B;
    // LDH_addr_A(hMultiplicand + 2);
    // LD_A(100);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    // LDH_A_addr(hProduct + 2);
    // LD_B_A;
    // LDH_A_addr(hProduct + 3);
    // LD_C_A;
    uint16_t bc = (((hl[0] & 0xf) + b) * 100) + hl[1];
    // LD_E_hl;
    // ADD_A_E;
    // LD_C_A;
    // LD_A_B;
    // ADC_A(0);
    // LD_B_A;
    // LD_A_C;
    // LD_hld_A;
    hl[1] = LOW(bc);
    // LD_hl_B;
    hl[0] = HIGH(bc);
    // RET;
}

void Function48d94(uint8_t* hl){
    // XOR_A_A;
    // LDH_addr_A(hDividend + 0);
    // LDH_addr_A(hDividend + 1);
    // LD_A_hli;
    // LDH_addr_A(hDividend + 0);
    // LD_A_hl;
    // LDH_addr_A(hDividend + 1);
    uint16_t x = (hl[0] | hl[1] << 8);
    // LD_A(100);
    // LDH_addr_A(hDivisor);
    // LD_B(2);
    // CALL(aDivide);
    // LDH_A_addr(hRemainder);
    // LD_C(10);
    // CALL(aSimpleDivide);
    struct DivideResult_t res1 = SimpleDivide_Conv(x % 100, 10);
    // SLA_B;
    // SLA_B;
    // SLA_B;
    // SLA_B;
    // OR_A_B;
    // LD_hld_A;
    hl[1] = (res1.quot << 4) | res1.rem;
    // LDH_A_addr(hQuotient + 3);
    // LD_C(10);
    // CALL(aSimpleDivide);
    struct DivideResult_t res2 = SimpleDivide_Conv(x / 100, 10);
    // SLA_B;
    // SLA_B;
    // SLA_B;
    // SLA_B;
    // OR_A_B;
    hl[0] = (res2.quot << 4) | res2.rem;
    // LD_hl_A;
    // RET;
}
