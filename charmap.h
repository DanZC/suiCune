
/*
	charmap "<NULL>",    $00
	charmap "<PLAY_G>",  $14 ; "<PLAYER>くん" or "<PLAYER>ちゃん"; same as "<PLAYER>" in English
	charmap "<MOBILE>",  $15
	charmap "<CR>",      $16
	charmap "¯",         $1f ; soft linebreak
	charmap "<LF>",      $22
	charmap "<POKE>",    $24 ; "<PO><KE>"
	charmap "%",         $25 ; soft linebreak in landmark names
	charmap "<RED>",     $38 ; wRedsName
	charmap "<GREEN>",   $39 ; wGreensName
	charmap "<ENEMY>",   $3f
	charmap "<MOM>",     $49 ; wMomsName
	charmap "<PKMN>",    $4a ; "<PK><MN>"
	charmap "<_CONT>",   $4b ; implements "<CONT>"
	charmap "<SCROLL>",  $4c
	charmap "<NEXT>",    $4e
	charmap "<LINE>",    $4f
	charmap "@",         $50 ; string terminator
	charmap "<PARA>",    $51
	charmap "<PLAYER>",  $52 ; wPlayerName
	charmap "<RIVAL>",   $53 ; wRivalName
	charmap "#",         $54 ; "POKé"
	charmap "<CONT>",    $55
	charmap "<……>",      $56 ; "……"
	charmap "<DONE>",    $57
	charmap "<PROMPT>",  $58
	charmap "<TARGET>",  $59
	charmap "<USER>",    $5a
	charmap "<PC>",      $5b ; "PC"
	charmap "<TM>",      $5c ; "TM"
	charmap "<TRAINER>", $5d ; "TRAINER"
	charmap "<ROCKET>",  $5e ; "ROCKET"
	charmap "<DEXEND>",  $5f

	charmap " ",         $7f
*/

#define CHAR_NULL    ('\x00')
#define CHAR_PLAY_G  ('\x14') // "<PLAYER>くん" or "<PLAYER>ちゃん"; same as "<PLAYER>" in English
#define CHAR_MOBILE  ('\x15')
#define CHAR_CR      ('\x16')
#define CHAR_SOFTLB  ('\x1f') // "¯" soft linebreak
#define CHAR_LF      ('\x22')
#define CHAR_POKE    ('\x24') // "<PO><KE>"
#define CHAR_LM_SLB  ('\x25') // soft linebreak in landmark names
#define CHAR_RED     ('\x38') // wRedsName
#define CHAR_GREEN   ('\x39') // wGreensName
#define CHAR_ENEMY   ('\x3f') 
#define CHAR_MOM     ('\x49') // wMomsName
#define CHAR_PKMN    ('\x4a') // "<PK><MN>"
#define CHAR__CONT   ('\x4b') // implements "<CONT>"
#define CHAR_SCROLL  ('\x4c')
#define CHAR_NEXT    ('\x4e')
#define CHAR_LINE    ('\x4f')
#define CHAR_TERM    ('\x50') // string terminator
#define CHAR_PARA    ('\x51') 
#define CHAR_PLAYER  ('\x52') // wPlayerName
#define CHAR_RIVAL   ('\x53') // wRivalName
#define CHAR_POKe    ('\x54') // "POKé"
#define CHAR_CONT    ('\x55') 
#define CHAR_SIXDOTS ('\x56') // "……"
#define CHAR_DONE    ('\x57') 
#define CHAR_PROMPT  ('\x58') 
#define CHAR_TARGET  ('\x59') 
#define CHAR_USER    ('\x5a') 
#define CHAR_PC      ('\x5b') // "PC"
#define CHAR_TM      ('\x5c') // "TM"
#define CHAR_TRAINER ('\x5d') // "TRAINER"
#define CHAR_ROCKET  ('\x5e') // "ROCKET"
#define CHAR_DEXEND  ('\x5f') 

#define CHAR_SPACE   ('\x7f') // " "

/*
; Japanese control characters (see home/text.asm)

	charmap "<JP_18>",   $18 ; "ノ゛" (ungrammatical)
	charmap "<NI>",      $1d ; "に　"
	charmap "<TTE>",     $1e ; "って"
	charmap "<WO>",      $1f ; "を　"
	charmap "<TA!>",     $22 ; "た！"
	charmap "<KOUGEKI>", $23 ; "こうげき"
	charmap "<WA>",      $24 ; "は　"
	charmap "<NO>",      $25 ; "の　"
	charmap "<ROUTE>",   $35 ; "ばん　どうろ"
	charmap "<WATASHI>", $36 ; "わたし"
	charmap "<KOKO_WA>", $37 ; "ここは"
	charmap "<GA>",      $4a ; "が　"

	charmap "ﾟ", $e4
	charmap "ﾞ", $e5

; Japanese kana, for those bits of text that were not translated to English

	charmap "ガ", $05
*/
#define CHAR_JP_18   ('\x18') // "ノ゛" (ungrammatical)
#define CHAR_JP_NI   ('\x1d') // "に　"
#define CHAR_JP_NO   ('\x25') // "の　"
#define CHAR_JP_05   ('\x05') // "ガ"

/*
	charmap "<BOLD_D>",  $63 ; unused
	charmap "<BOLD_V>",  $69
	charmap "<BOLD_S>",  $6a
	charmap "<COLON>",   $6d ; colon with tinier dots than ":"
	charmap "<PO>",      $70
	charmap "<KE>",      $71
	charmap "“",         $72 ; opening quote
	charmap "”",         $73 ; closing quote
	charmap "…",         $75 ; ellipsis
*/
#define CHAR_BOLD_D      ('\x63') // "<BOLD_D>"
#define CHAR_BOLD_V      ('\x69') // "<BOLD_V>"
#define CHAR_BOLD_S      ('\x6a') // "<BOLD_S>"
#define CHAR_COLON       ('\x6d') // "<COLON>", colon with tinier dots than ":"
#define CHAR_PO          ('\x70') // "<PO>"
#define CHAR_KE          ('\x71') // "<KE>"
#define CHAR_OPEN_QUOTE  ('\x72') // "“", opening quote
#define CHAR_CLOSE_QUOTE ('\x73') // "”", closing quote
#define CHAR_ELLIPSIS    ('\x75') // "…", ellipsis

/*
; Actual characters (from gfx/font/font_battle_extra.png)

	charmap "<LV>",      $6e

	charmap "<DO>",      $70 ; hiragana small do, unused
	charmap "◀",         $71
	charmap "『",         $72 ; Japanese opening quote, unused
	charmap "<ID>",      $73
	charmap "№",         $74
*/
#define CHAR_LV          ('\x6e') // "<LV>"
#define CHAR_LEFT_CURSOR ('\x71') // "◀"
#define CHAR_ID          ('\x73') // "<ID>"
#define CHAR_NO          ('\x74') // "№" No.

/*
  Actual characters (from gfx/font/font.png)

	charmap "A",         $80
	charmap "B",         $81
	charmap "C",         $82
	charmap "D",         $83
	charmap "E",         $84
	charmap "F",         $85
	charmap "G",         $86
	charmap "H",         $87
	charmap "I",         $88
	charmap "J",         $89
	charmap "K",         $8a
	charmap "L",         $8b
	charmap "M",         $8c
	charmap "N",         $8d
	charmap "O",         $8e
	charmap "P",         $8f
	charmap "Q",         $90
	charmap "R",         $91
	charmap "S",         $92
	charmap "T",         $93
	charmap "U",         $94
	charmap "V",         $95
	charmap "W",         $96
	charmap "X",         $97
	charmap "Y",         $98
	charmap "Z",         $99
*/
#define CHAR_A          ((uint8_t)'\x80') // "A"
#define CHAR_Z          ((uint8_t)'\x99') // "Z"

/*
	charmap "a",         $a0
	charmap "b",         $a1
	charmap "c",         $a2
	charmap "d",         $a3
	charmap "e",         $a4
	charmap "f",         $a5
	charmap "g",         $a6
	charmap "h",         $a7
	charmap "i",         $a8
	charmap "j",         $a9
	charmap "k",         $aa
	charmap "l",         $ab
	charmap "m",         $ac
	charmap "n",         $ad
	charmap "o",         $ae
	charmap "p",         $af
	charmap "q",         $b0
	charmap "r",         $b1
	charmap "s",         $b2
	charmap "t",         $b3
	charmap "u",         $b4
	charmap "v",         $b5
	charmap "w",         $b6
	charmap "x",         $b7
	charmap "y",         $b8
	charmap "z",         $b9
*/
#define CHAR_a          ((uint8_t)'\xa0') // "a"
#define CHAR_z          ((uint8_t)'\xb9') // "z"

/*
	charmap "?",         $e6
	charmap "!",         $e7
	charmap ".",         $e8
	charmap "&",         $e9
*/
#define CHAR_QMARK      ((uint8_t)'\xe6') // "?"
#define CHAR_EMARK      ((uint8_t)'\xe7') // "!"
#define CHAR_PERIOD     ((uint8_t)'\xe8') // "."
#define CHAR_AMPERSAND  ((uint8_t)'\xe6') // "&"

/*
	charmap "(",         $9a
	charmap ")",         $9b
	charmap ":",         $9c
	charmap ";",         $9d
	charmap "[",         $9e
	charmap "]",         $9f
*/
#define CHAR_LPAREN     ((uint8_t)'\x9a') // "("
#define CHAR_RPAREN     ((uint8_t)'\x9b') // ")"
#define CHAR_COLON2     ((uint8_t)'\x9c') // ":"
#define CHAR_SEMICOLON  ((uint8_t)'\x9d') // ";"
#define CHAR_LBRACKET   ((uint8_t)'\x9e') // "["
#define CHAR_RBRACKET   ((uint8_t)'\x9f') // "]"

/*
	charmap "'d",        $d0
	charmap "'l",        $d1
	charmap "'m",        $d2
	charmap "'r",        $d3
	charmap "'s",        $d4
	charmap "'t",        $d5
	charmap "'v",        $d6
*/
#define CHAR_APOS_D     ((uint8_t)'\xd0') // "'d"
#define CHAR_APOS_L     ((uint8_t)'\xd1') // "'l"
#define CHAR_APOS_M     ((uint8_t)'\xd2') // "'m"
#define CHAR_APOS_R     ((uint8_t)'\xd3') // "'r"
#define CHAR_APOS_S     ((uint8_t)'\xd4') // "'s"
#define CHAR_APOS_T     ((uint8_t)'\xd5') // "'t"
#define CHAR_APOS_V     ((uint8_t)'\xd6') // "'v"

/*
	charmap "←",         $df
	charmap "'",         $e0
	charmap "<PK>",      $e1
	charmap "<MN>",      $e2
	charmap "-",         $e3
*/
#define CHAR_LEFT_ARROW    ((uint8_t)'\xdf') // "←"
#define CHAR_SINGLE_QUOTE  ((uint8_t)'\xe0') // "'"
#define CHAR_PK            ((uint8_t)'\xe1') // "<PK>"
#define CHAR_MN            ((uint8_t)'\xe2') // "<MN>"
#define CHAR_DASH          ((uint8_t)'\xe3') // "-"

/*
	charmap "0",         $f6
	charmap "1",         $f7
	charmap "2",         $f8
	charmap "3",         $f9
	charmap "4",         $fa
	charmap "5",         $fb
	charmap "6",         $fc
	charmap "7",         $fd
	charmap "8",         $fe
	charmap "9",         $ff
*/
#define CHAR_0       ((uint8_t)'\xf6')
#define CHAR_9       ((uint8_t)'\xff')

/*
	charmap "┌",         $79
	charmap "─",         $7a
	charmap "┐",         $7b
	charmap "│",         $7c
	charmap "└",         $7d
	charmap "┘",         $7e
*/
#define CHAR_FRAME_TOP_LEFT     ('\x79') // "┌"
#define CHAR_FRAME_TOP          ('\x7a') // "─"
#define CHAR_FRAME_TOP_RIGHT    ('\x7b') // "┐"
#define CHAR_FRAME_SIDE         ('\x7c') // "│"
#define CHAR_FRAME_BOTTOM_LEFT  ('\x7d') // "└"
#define CHAR_FRAME_BOTTOM_RIGHT ('\x7e') // "┘"

/*
	charmap "■",         $60 ; gfx/font/black.2bpp
	charmap "▲",         $61 ; gfx/font/up_arrow.png
	charmap "☎",         $62 ; gfx/font/phone_icon.2bpp
*/
// needed for _LoadFontsExtra1 (see engine/gfx/load_font.asm)
#define CHAR_BLACK_SQUARE       ('\x60') // "■", gfx/font/black.2bpp
#define CHAR_UP_ARROW           ('\x61') // "▲", gfx/font/up_arrow.png
#define CHAR_PHONE_ICON         ('\x62') // "☎", gfx/font/phone_icon.2bpp

// needed for MagikarpHouseSign (see engine/events/magikarp.asm)
#define CHAR_FEET               ('\x6e') // "′", gfx/font/feet_inches.png
#define CHAR_INCHES             ('\x6f') // "″", gfx/font/feet_inches.png

// needed for StatsScreen_PlaceShinyIcon and PrintPartyMonPage1
#define CHAR_SHINY_ICON         ('\x3f') // "⁂", gfx/stats/stats_tiles.png, tile 14

/*
	charmap "é",         $ea
	charmap "→",         $eb
	charmap "▷",         $ec
	charmap "▶",         $ed
	charmap "▼",         $ee
	charmap "♂",         $ef
	charmap "¥",         $f0
	charmap "×",         $f1
	charmap "<DOT>",     $f2 ; decimal point; same as "." in English
	charmap "/",         $f3
	charmap ",",         $f4
	charmap "♀",         $f5
*/
#define CHAR_ACCENT_E         ((uint8_t)'\xea') // "é"
#define CHAR_RIGHT_ARROW      ((uint8_t)'\xeb') // "→"
#define CHAR_RIGHT_CURSOR_SEL ((uint8_t)'\xec') // "▷"
#define CHAR_RIGHT_CURSOR     ((uint8_t)'\xed') // "▶"
#define CHAR_DOWN_CURSOR      ((uint8_t)'\xee') // "▼"
#define CHAR_MALE_ICON        ((uint8_t)'\xef') // "♂"
#define CHAR_MONEY_ICON       ((uint8_t)'\xf0') // "¥"
#define CHAR_TIMES            ((uint8_t)'\xf1') // "×"
#define CHAR_DOT              ((uint8_t)'\xf2') // "<DOT>", decimal point; same as "." in English
#define CHAR_FWD_SLASH        ((uint8_t)'\xf3') // "/"
#define CHAR_COMMA            ((uint8_t)'\xf4') // ","
#define CHAR_FEMALE_ICON      ((uint8_t)'\xf5') // "♀"

// Japanese control characters (see home/text.asm)
#define CHAR_KOUGEKI ('\x23') // "こうげき"
#define CHAR_ROUTE   ('\x35') // "ばん　どうろ"
#define CHAR_WATASHI ('\x36') // "わたし"
#define CHAR_KOKO_WA ('\x37') // "ここは"