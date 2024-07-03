#include "../constants.h"
#include "../charmap.h"

static const char SatoshiTajiri[] =       "   SATOSHI TAJIRI@"         ; // "たじり　さとし@"
static const char JunichiMasuda[] =       "   JUNICHI MASUDA@"         ; // "ますだ　じゅんいち@"
static const char TetsuyaWatanabe[] =     "  TETSUYA WATANABE@"        ; // "わたなべ　てつや@"
static const char ShigekiMorimoto[] =     "  SHIGEKI MORIMOTO@"        ; // "もりもと　しげき@"
static const char SousukeTamada[] =       "   SOUSUKE TAMADA@"         ; // "たまだ　そうすけ@"
static const char TakenoriOota[] =        "   TAKENORI OOTA@"          ; // "おおた　たけのり@"
static const char KenSugimori[] =         "    KEN SUGIMORI@"          ; // "すぎもり　けん@"
static const char MotofumiFujiwara[] =    " MOTOFUMI FUJIWARA@"        ; // "ふじわら　もとふみ@"
static const char AtsukoNishida[] =       "   ATSUKO NISHIDA@"         ; // "にしだ　あつこ@"
static const char MuneoSaito[] =          "    MUNEO SAITO@"           ; // "さいとう　むねお@"
static const char SatoshiOota[] =         "    SATOSHI OOTA@"          ; // "おおた　さとし@"
static const char RenaYoshikawa[] =       "   RENA YOSHIKAWA@"         ; // "よしかわ　れな@"
static const char JunOkutani[] =          "    JUN OKUTANI@"           ; // "おくたに　じゅん@"
static const char HironobuYoshida[] =     "  HIRONOBU YOSHIDA@"        ; // "よしだ　ひろのぶ@"
static const char AsukaIwashita[] =       "   ASUKA IWASHITA@"         ; // "いわした　あすか@"
static const char GoIchinose[] =          "    GO ICHINOSE@"           ; // "いちのせ　ごう@"
static const char MorikazuAoki[] =        "   MORIKAZU AOKI@"          ; // "あおき　もりかず@"
static const char KohjiNishino[] =        "   KOHJI NISHINO@"          ; // "にしの　こうじ@"
static const char KenjiMatsushima[] =     "  KENJI MATSUSHIMA@"        ; // "まつしま　けんじ@"
static const char ToshinobuMatsumiya[] =  "TOSHINOBU MATSUMIYA@"       ; // "まつみや　としのぶ@"
static const char SatoruIwata[] =         "    SATORU IWATA@"          ; // "いわた　さとる@"
static const char NobuhiroSeya[] =        "   NOBUHIRO SEYA@"          ; // "せや　のぶひろ@"
static const char KazuhitoSekine[] =      "  KAZUHITO SEKINE@"         ; // "せきね　かずひと@"
static const char TetsujiOota[] =         "    TETSUJI OOTA@"          ; // "おおた　てつじ@"
static const char NclSuperMarioClub[] =   "NCL SUPER MARIO CLUB@"      ; // "スーパーマりオクラブ@"
static const char Sarugakucho[] =         "    SARUGAKUCHO@"           ; // "さるがくちょう@"
static const char AkitoMori[] =           "     AKITO MORI@"           ; // "もり　あきと@"
static const char TakahiroHarada[] =      "  TAKAHIRO HARADA@"         ; // "はらだ　たかひろ@"
static const char TohruHashimoto[] =      "  TOHRU HASHIMOTO@"         ; // "はしもと　とおる@"
static const char NoboruMatsumoto[] =     "  NOBORU MATSUMOTO@"        ; // "まつもと　のぼる@"
static const char TakehiroIzushi[] =      "  TAKEHIRO IZUSHI@"         ; // "いずし　たけひろ@"
static const char TakashiKawaguchi[] =    " TAKASHI KAWAGUCHI@"        ; // "かわぐち　たかし@"
static const char TsunekazuIshihara[] =   " TSUNEKAZU ISHIHARA@"       ; // "いしはら　つねかず@"
static const char HiroshiYamauchi[] =     "  HIROSHI YAMAUCHI@"        ; // "やまうち　ひろし@"
static const char KenjiSaiki[] =          "    KENJI SAIKI@"           ; // "さいき　けんじ@"
static const char AtsushiTada[] =         "    ATSUSHI TADA@"          ; // "ただ　あつし@"
static const char NaokoKawakami[] =       "   NAOKO KAWAKAMI@"         ; // "かわかみ　なおこ@"
static const char HiroyukiZinnai[] =      "  HIROYUKI ZINNAI@"         ; // "じんない　ひろゆき@"
static const char KunimiKawamura[] =      "  KUNIMI KAWAMURA@"         ; // "かわむら　くにみ@"
static const char HisashiSogabe[] =       "   HISASHI SOGABE@"         ; // "そがべ　ひさし@"
static const char KeitaKagaya[] =         "    KEITA KAGAYA@"          ; // "かがや　けいた@"
static const char YoshinoriMatsuda[] =    " YOSHINORI MATSUDA@"        ; // "まつだ　よしのり@"
static const char HitomiSato[] =          "    HITOMI SATO@"           ; // "さとう　ひとみ@"
static const char ToruOsawa[] =           "     TORU OSAWA@"           ; // "おおさわ　とおる@"
static const char TakaoOhara[] =          "    TAKAO OHARA@"           ; // "おおはら　たかお@"
static const char YuichiroIto[] =         "    YUICHIRO ITO@"          ; // "いとう　ゆういちろう@"
static const char TakaoShimizu[] =        "   TAKAO SHIMIZU@"          ; // "しみず　たかお@"
static const char Planning[] =            " SPECIAL PRODUCTION"
                                   t_next "      PLANNING"             // "きかくかいはつぶ@"
                                   t_next " & DEVELOPMENT DEPT.@";
static const char KeitaNakamura[] =       "   KEITA NAKAMURA@"         ; // "なかむら　けいた@"
static const char HirotakaUemura[] =      "  HIROTAKA UEMURA@"         ; // "うえむら　ひろたか@"
static const char HiroakiTamura[] =       "   HIROAKI TAMURA@"         ; // "たむら　ひろあき@"
static const char NoriakiSakaguchi[] =    " NORIAKI SAKAGUCHI@"        ; // "さかぐち　のりあき@"
static const char MiyukiSato[] =          "    MIYUKI SATO@"           ; // "さとう　みゆき@"
static const char GakuziNomoto[] =        "   GAKUZI NOMOTO@"          ; // "のもと　がくじ@"
static const char AiMashima[] =           "     AI MASHIMA@"           ; // "ましま　あい@"
static const char MikihiroIshikawa[] =    " MIKIHIRO ISHIKAWA@"        ; // "いしかわ　みきひろ@"
static const char HideyukiHashimoto[] =   " HIDEYUKI HASHIMOTO@"       ; // "はしもと　ひでゆき@"
static const char SatoshiYamato[] =       "   SATOSHI YAMATO@"         ; // "やまと　さとし@"
static const char ShigeruMiyamoto[] =     "  SHIGERU MIYAMOTO@"        ; // "みやもと　しげる@"
static const char End[] =                 "        END@"               ; // "おしまい@"
static const char Unknown[] =             "      ????????@"            ; // "？？？？？？？？@"
static const char GailTilden[] =          "    GAIL TILDEN@";
static const char NobOgasawara[] =        "   NOB OGASAWARA@";
static const char SethMcMahill[] =        "   SETH McMAHILL@";
static const char HirotoAlexander[] =     "  HIROTO ALEXANDER@";
static const char TeresaLillygren[] =     "  TERESA LILLYGREN@";
static const char ThomasHertzog[] =       "   THOMAS HERTZOG@";
static const char ErikJohnson[] =         "    ERIK JOHNSON@";
static const char HiroNakamura[] =        "   HIRO NAKAMURA@";
static const char TerukiMurakawa[] =      "  TERUKI MURAKAWA@";
static const char KazuyoshiOsawa[] =      "  KAZUYOSHI OSAWA@";
static const char KimikoNakamichi[] =     "  KIMIKO NAKAMICHI@";
static const char Staff[] =               "      #MON"                   // "ポケットモンスター"
                                   t_next "  CRYSTAL VERSION"            // "　　クりスタル　バージョン"
                                   t_next "       STAFF@"              ; // "　　　　スタッフ@"
static const char Director[] =            "      DIRECTOR@"            ; // "エグゼクティブ　ディレクター@"
static const char CoDirector[] =          "    CO-DIRECTOR@"           ; // "ディレクター@"
static const char Programmers[] =         "    PROGRAMMERS@"           ; // "プログラム@"
static const char GraphicsDirector[] =    " GRAPHICS DIRECTOR@"        ; // "グラフィック　ディレクター@"
static const char MonsterDesign[] =       "   MONSTER DESIGN@"         ; // "#　デザイン@"
static const char GraphicsDesign[] =      "  GRAPHICS DESIGN@"         ; // "グラフィック　デザイン@"
static const char Music[] =               "       MUSIC@"              ; // "おんがく@"
static const char SoundEffects[] =        "   SOUND EFFECTS@"          ; // "サウンド　エフェクト@"
static const char GameDesign[] =          "    GAME DESIGN@"           ; // "ゲームデザイン@"
static const char GameScenario[] =        "   GAME SCENARIO@"          ; // "シナりオ@"
static const char ToolProgramming[] =     "  TOOL PROGRAMMING@"        ; // "ツール　プログラム@"
static const char ParametricDesign[] =    " PARAMETRIC DESIGN@"        ; // "パラメーター　せってい@"
static const char ScriptDesign[] =        "   SCRIPT DESIGN@"          ; // "スクりプト　せってい@"
static const char MapDataDesign[] =       "  MAP DATA DESIGN@"         ; // "マップデータ　せってい@"
static const char MapDesign[] =           "     MAP DESIGN@"           ; // "マップ　デザイン@"
static const char ProductTesting[] =      "  PRODUCT TESTING@"         ; // "デバッグプレイ@"
static const char SpecialThanks[] =       "   SPECIAL THANKS@"         ; // "スぺシャルサンクス@"
static const char Producers[] =           "     PRODUCERS@"            ; // "プロデューサー@"
static const char ExecutiveProducer[] =   " EXECUTIVE PRODUCER@"       ; // "エグゼクティブ　プロデューサー@"
static const char PokemonAnimation[] =    " #MON ANIMATION@"           ; // "#　アニメーション@"
static const char PokedexText[] =         "    #DEX TEXT@"             ; // "ずかん　テキスト@"
static const char MobilePrjLeader[] =     " MOBILE PRJ. LEADER@"       ; // "モバイルプロジェクト　りーダー@"
static const char MobileSystemAd[] =      " MOBILE SYSTEM AD.@"        ; // "モバイル　システムアドバイザー@"
static const char MobileStadiumDir[] =    "MOBILE STADIUM DIR.@"       ; // "モバイルスタジアム　ディレクター@"
static const char Coordination[] =        "    COORDINATION@"          ; // "コーディネーター@"
static const char UsVersionStaff[] =      "  US VERSION STAFF@";
static const char UsCoordination[] =      "  US COORDINATION@";
static const char TextTranslation[] =     "  TEXT TRANSLATION@";
static const char PaadTesting[] =         "    PAAD TESTING@";

const uint8_t Credits_Copyright[] = {
    //    (C) 1  9  9  5 - 2  0  0  1     N  i  n  t  e  n  d  o
                0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,
    //    (C) 1  9  9  5 - 2  0  0  1    C  r  e  a  t  u  r  e  s     i  n  c .
    CHAR_NEXT,  0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x6d,0x6e,0x6f,0x70,0x71,0x72,  0x7a,0x7b,0x7c,
    //    (C) 1  9  9  5 - 2  0  0  1  G  A  M  E  F  R  E  A  K     i  n  c .
    CHAR_NEXT,  0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x73,0x74,0x75,0x76,0x77,0x78,0x79,  0x7a,0x7b,0x7c,
    CHAR_TERM
};


const char *const CreditsStringsPointers[] = {
// entries correspond to constants/credits_constants.asm
    SatoshiTajiri,
    JunichiMasuda,
    TetsuyaWatanabe,
    ShigekiMorimoto,
    SousukeTamada,
    TakenoriOota,
    KenSugimori,
    MotofumiFujiwara,
    AtsukoNishida,
    MuneoSaito,
    SatoshiOota,
    RenaYoshikawa,
    JunOkutani,
    HironobuYoshida,
    AsukaIwashita,
    GoIchinose,
    MorikazuAoki,
    KohjiNishino,
    KenjiMatsushima,
    ToshinobuMatsumiya,
    SatoruIwata,
    NobuhiroSeya,
    KazuhitoSekine,
    TetsujiOota,
    NclSuperMarioClub,
    Sarugakucho,
    AkitoMori,
    TakahiroHarada,
    TohruHashimoto,
    NoboruMatsumoto,
    TakehiroIzushi,
    TakashiKawaguchi,
    TsunekazuIshihara,
    HiroshiYamauchi,
    KenjiSaiki,
    AtsushiTada,
    NaokoKawakami,
    HiroyukiZinnai,
    KunimiKawamura,
    HisashiSogabe,
    KeitaKagaya,
    YoshinoriMatsuda,
    HitomiSato,
    ToruOsawa,
    TakaoOhara,
    YuichiroIto,
    TakaoShimizu,
    Planning,
    KeitaNakamura,
    HirotakaUemura,
    HiroakiTamura,
    NoriakiSakaguchi,
    MiyukiSato,
    GakuziNomoto,
    AiMashima,
    MikihiroIshikawa,
    HideyukiHashimoto,
    SatoshiYamato,
    ShigeruMiyamoto,
    GailTilden,
    NobOgasawara,
    SethMcMahill,
    HirotoAlexander,
    TeresaLillygren,
    ThomasHertzog,
    ErikJohnson,
    HiroNakamura,
    TerukiMurakawa,
    KazuyoshiOsawa,
    KimikoNakamichi,
    End,
    Unknown,
    Staff,
    Director,
    CoDirector,
    Programmers,
    GraphicsDirector,
    MonsterDesign,
    GraphicsDesign,
    Music,
    SoundEffects,
    GameDesign,
    GameScenario,
    ToolProgramming,
    ParametricDesign,
    ScriptDesign,
    MapDataDesign,
    MapDesign,
    ProductTesting,
    SpecialThanks,
    Producers,
    ExecutiveProducer,
    PokemonAnimation,
    PokedexText,
    MobilePrjLeader,
    MobileSystemAd,
    MobileStadiumDir,
    Coordination,
    NULL, // Copyright,
    UsVersionStaff,
    UsCoordination,
    TextTranslation,
    PaadTesting,
};
static_assert(lengthof(CreditsStringsPointers) == NUM_CREDITS_STRINGS, "");
