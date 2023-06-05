
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

// Japanese control characters (see home/text.asm)
#define CHAR_KOUGEKI ('\x23') // "こうげき"
#define CHAR_ROUTE   ('\x35') // "ばん　どうろ"
#define CHAR_WATASHI ('\x36') // "わたし"
#define CHAR_KOKO_WA ('\x37') // "ここは"