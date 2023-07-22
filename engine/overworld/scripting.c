#include "../../constants.h"
#include "../../util/scripting.h"
#include "scripting.h"
#include "../../home/copy.h"
#include "../../home/print_text.h"
#include "../../home/copy_name.h"
#include "../../home/map.h"
#include "../../home/item.h"
#include "../../home/map_objects.h"
#include "../../home/joypad.h"
#include "../battle/read_trainer_party.h"
#include "../events/engine_flags.h"
#include "landmarks.h"
#include "overworld.h"

//  Event scripting commands.

void EnableScriptMode(void){
    // PUSH_AF;
    // LD_A(SCRIPT_READ);
    // LD_addr_A(wScriptMode);
    // POP_AF;
    wram->wScriptMode = SCRIPT_READ;
    RET;

}

void ScriptEvents(void){
    CALL(aStartScript);

    do {
    // loop:
        // LD_A_addr(wScriptMode);
        // LD_HL(mScriptEvents_modes);
        // RST(aJumpTable);
        // modes:
            //dw ['EndScript'];
            //dw ['RunScriptCommand'];
            //dw ['WaitScriptMovement'];
            //dw ['WaitScript'];
        switch(wram->wScriptMode)
        {
            case SCRIPT_OFF: CALL(aEndScript); break;
            case SCRIPT_READ: CALL(aRunScriptCommand); break;
            case SCRIPT_WAIT_MOVEMENT: CALL(aWaitScriptMovement); break;
            case SCRIPT_WAIT: CALL(aWaitScript); break;
        }
        // CALL(aCheckScript);
        // IF_NZ goto loop;
    } while(CheckScript_Conv());
    RET;
}

void EndScript(void){
    CALL(aStopScript);
    RET;

}

void WaitScript(void){
    // CALL(aStopScript);
    StopScript_Conv();

    // LD_HL(wScriptDelay);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wScriptDelay != 0)
        RET;

    FARCALL(aUnfreezeAllObjects);

    // LD_A(SCRIPT_READ);
    // LD_addr_A(wScriptMode);
    wram->wScriptMode = SCRIPT_READ;
    CALL(aStartScript);
    RET;

}

void WaitScriptMovement(void){
    CALL(aStopScript);

    // LD_HL(wVramState);
    // BIT_hl(7);
    // RET_NZ ;
    if(bit_test(wram->wVramState, 7))
        RET;

    FARCALL(aUnfreezeAllObjects);

    // LD_A(SCRIPT_READ);
    // LD_addr_A(wScriptMode);
    wram->wScriptMode = SCRIPT_READ;
    CALL(aStartScript);
    RET;

}

#include "../../macros/scripts/events.h"

void RunScriptCommand(void){
    CALL(aGetScriptByte);
    // LD_HL(mScriptCommandTable);
    // RST(aJumpTable);
    switch(REG_A)
    {
        case CMD_SCALL: CALL(aScript_scall); break; // $00
        case CMD_FARSCALL: CALL(aScript_farscall); break; // $01
        case CMD_MEMCALL: CALL(aScript_memcall); break; // $02
        case CMD_SJUMP: CALL(aScript_sjump); break; // $03
        case CMD_FARSJUMP: CALL(aScript_farsjump); break; // $04
        case CMD_MEMJUMP: CALL(aScript_memjump); break; // $05
        case CMD_IFEQUAL: CALL(aScript_ifequal); break; // $06
        case CMD_IFNOTEQUAL: CALL(aScript_ifnotequal); break; // $07
        case CMD_IFFALSE: CALL(aScript_iffalse); break; // $08
        case CMD_IFTRUE: CALL(aScript_iftrue); break; // $09
        case CMD_IFGREATER: CALL(aScript_ifgreater); break; // $0a
        case CMD_IFLESS: CALL(aScript_ifless); break; // $0b
        case CMD_JUMPSTD: CALL(aScript_jumpstd); break; // $0c
        case CMD_CALLSTD: CALL(aScript_callstd); break; // $0d
        case CMD_CALLASM: CALL(aScript_callasm); break; // $0e
        case CMD_SPECIAL: CALL(aScript_special); break; // $0f
        case CMD_MEMCALLASM: CALL(aScript_memcallasm); break; // $10
        case CMD_CHECKMAPSCENE: CALL(aScript_checkmapscene); break; // $11
        case CMD_SETMAPSCENE: CALL(aScript_setmapscene); break; // $12
        case CMD_CHECKSCENE: CALL(aScript_checkscene); break; // $13
        case CMD_SETSCENE: CALL(aScript_setscene); break; // $14
        case CMD_SETVAL: CALL(aScript_setval); break; // $15
        case CMD_ADDVAL: CALL(aScript_addval); break; // $16
        case CMD_RANDOM: CALL(aScript_random); break; // $17
        case CMD_CHECKVER: CALL(aScript_checkver); break; // $18
        case CMD_READMEM: CALL(aScript_readmem); break; // $19
        case CMD_WRITEMEM: CALL(aScript_writemem); break; // $1a
        case CMD_LOADMEM: CALL(aScript_loadmem); break; // $1b
        case CMD_READVAR: CALL(aScript_readvar); break; // $1c
        case CMD_WRITEVAR: CALL(aScript_writevar); break; // $1d
        case CMD_LOADVAR: CALL(aScript_loadvar); break; // $1e
        case CMD_GIVEITEM: CALL(aScript_giveitem); break; // $1f
        case CMD_TAKEITEM: CALL(aScript_takeitem); break; // $20
        case CMD_CHECKITEM: CALL(aScript_checkitem); break; // $21
        case CMD_GIVEMONEY: CALL(aScript_givemoney); break; // $22
        case CMD_TAKEMONEY: CALL(aScript_takemoney); break; // $23
        case CMD_CHECKMONEY: CALL(aScript_checkmoney); break; // $24
        case CMD_GIVECOINS: CALL(aScript_givecoins); break; // $25
        case CMD_TAKECOINS: CALL(aScript_takecoins); break; // $26
        case CMD_CHECKCOINS: CALL(aScript_checkcoins); break; // $27
        case CMD_ADDCELLNUM: CALL(aScript_addcellnum); break; // $28
        case CMD_DELCELLNUM: CALL(aScript_delcellnum); break; // $29
        case CMD_CHECKCELLNUM: CALL(aScript_checkcellnum); break; // $2a
        case CMD_CHECKTIME: CALL(aScript_checktime); break; // $2b
        case CMD_CHECKPOKE: CALL(aScript_checkpoke); break; // $2c
        case CMD_GIVEPOKE: CALL(aScript_givepoke); break; // $2d
        case CMD_GIVEEGG: CALL(aScript_giveegg); break; // $2e
        case CMD_GIVEPOKEMAIL: CALL(aScript_givepokemail); break; // $2f
        case CMD_CHECKPOKEMAIL: CALL(aScript_checkpokemail); break; // $30
        case CMD_CHECKEVENT: CALL(aScript_checkevent); break; // $31
        case CMD_CLEAREVENT: CALL(aScript_clearevent); break; // $32
        case CMD_SETEVENT: CALL(aScript_setevent); break; // $33
        case CMD_CHECKFLAG: CALL(aScript_checkflag); break; // $34
        case CMD_CLEARFLAG: CALL(aScript_clearflag); break; // $35
        case CMD_SETFLAG: CALL(aScript_setflag); break; // $36
        case CMD_WILDON: CALL(aScript_wildon); break; // $37
        case CMD_WILDOFF: CALL(aScript_wildoff); break; // $38
        case CMD_XYCOMPARE: CALL(aScript_xycompare); break; // $39
        case CMD_WARPMOD: CALL(aScript_warpmod); break; // $3a
        case CMD_BLACKOUTMOD: CALL(aScript_blackoutmod); break; // $3b
        case CMD_WARP: CALL(aScript_warp); break; // $3c
        case CMD_GETMONEY: CALL(aScript_getmoney); break; // $3d
        case CMD_GETCOINS: CALL(aScript_getcoins); break; // $3e
        case CMD_GETNUM: CALL(aScript_getnum); break; // $3f
        case CMD_GETMONNAME: CALL(aScript_getmonname); break; // $40
        case CMD_GETITEMNAME: CALL(aScript_getitemname); break; // $41
        case CMD_GETCURLANDMARKNAME: CALL(aScript_getcurlandmarkname); break; // $42
        case CMD_GETTRAINERNAME: CALL(aScript_gettrainername); break; // $43
        case CMD_GETSTRING: CALL(aScript_getstring); break; // $44
        case CMD_ITEMNOTIFY: CALL(aScript_itemnotify); break; // $45
        case CMD_POCKETISFULL: CALL(aScript_pocketisfull); break; // $46
        case CMD_OPENTEXT: CALL(aScript_opentext); break; // $47
        case CMD_REFRESHSCREEN: CALL(aScript_refreshscreen); break; // $48
        case CMD_CLOSETEXT: CALL(aScript_closetext); break; // $49
        case CMD_WRITEUNUSEDBYTE: CALL(aScript_writeunusedbyte); break; // $4a
        case CMD_FARWRITETEXT: CALL(aScript_farwritetext); break; // $4b
        case CMD_WRITETEXT: CALL(aScript_writetext); break; // $4c
        case CMD_REPEATTEXT: CALL(aScript_repeattext); break; // $4d
        case CMD_YESORNO: CALL(aScript_yesorno); break; // $4e
        case CMD_LOADMENU: CALL(aScript_loadmenu); break; // $4f
        case CMD_CLOSEWINDOW: CALL(aScript_closewindow); break; // $50
        case CMD_JUMPTEXTFACEPLAYER: CALL(aScript_jumptextfaceplayer); break; // $51
        case CMD_FARJUMPTEXT: CALL(aScript_farjumptext); break; // $52
        case CMD_JUMPTEXT: CALL(aScript_jumptext); break; // $53
        case CMD_WAITBUTTON: CALL(aScript_waitbutton); break; // $54
        case CMD_PROMPTBUTTON: CALL(aScript_promptbutton); break; // $55
        case CMD_POKEPIC: CALL(aScript_pokepic); break; // $56
        case CMD_CLOSEPOKEPIC: CALL(aScript_closepokepic); break; // $57
        case CMD__2DMENU: CALL(aScript__2dmenu); break; // $58
        case CMD_VERTICALMENU: CALL(aScript_verticalmenu); break; // $59
        case CMD_LOADPIKACHUDATA: CALL(aScript_loadpikachudata); break; // $5a
        case CMD_RANDOMWILDMON: CALL(aScript_randomwildmon); break; // $5b
        case CMD_LOADTEMPTRAINER: CALL(aScript_loadtemptrainer); break; // $5c
        case CMD_LOADWILDMON: CALL(aScript_loadwildmon); break; // $5d
        case CMD_LOADTRAINER: CALL(aScript_loadtrainer); break; // $5e
        case CMD_STARTBATTLE: CALL(aScript_startbattle); break; // $5f
        case CMD_RELOADMAPAFTERBATTLE: CALL(aScript_reloadmapafterbattle); break; // $60
        case CMD_CATCHTUTORIAL: CALL(aScript_catchtutorial); break; // $61
        case CMD_TRAINERTEXT: CALL(aScript_trainertext); break; // $62
        case CMD_TRAINERFLAGACTION: CALL(aScript_trainerflagaction); break; // $63
        case CMD_WINLOSSTEXT: CALL(aScript_winlosstext); break; // $64
        case CMD_SCRIPTTALKAFTER: CALL(aScript_scripttalkafter); break; // $65
        case CMD_ENDIFJUSTBATTLED: CALL(aScript_endifjustbattled); break; // $66
        case CMD_CHECKJUSTBATTLED: CALL(aScript_checkjustbattled); break; // $67
        case CMD_SETLASTTALKED: CALL(aScript_setlasttalked); break; // $68
        case CMD_APPLYMOVEMENT: CALL(aScript_applymovement); break; // $69
        case CMD_APPLYMOVEMENTLASTTALKED: CALL(aScript_applymovementlasttalked); break; // $6a
        case CMD_FACEPLAYER: CALL(aScript_faceplayer); break; // $6b
        case CMD_FACEOBJECT: CALL(aScript_faceobject); break; // $6c
        case CMD_VARIABLESPRITE: CALL(aScript_variablesprite); break; // $6d
        case CMD_DISAPPEAR: CALL(aScript_disappear); break; // $6e
        case CMD_APPEAR: CALL(aScript_appear); break; // $6f
        case CMD_FOLLOW: CALL(aScript_follow); break; // $70
        case CMD_STOPFOLLOW: CALL(aScript_stopfollow); break; // $71
        case CMD_MOVEOBJECT: CALL(aScript_moveobject); break; // $72
        case CMD_WRITEOBJECTXY: CALL(aScript_writeobjectxy); break; // $73
        case CMD_LOADEMOTE: CALL(aScript_loademote); break; // $74
        case CMD_SHOWEMOTE: CALL(aScript_showemote); break; // $75
        case CMD_TURNOBJECT: CALL(aScript_turnobject); break; // $76
        case CMD_FOLLOWNOTEXACT: CALL(aScript_follownotexact); break; // $77
        case CMD_EARTHQUAKE: CALL(aScript_earthquake); break; // $78
        case CMD_CHANGEMAPBLOCKS: CALL(aScript_changemapblocks); break; // $79
        case CMD_CHANGEBLOCK: CALL(aScript_changeblock); break; // $7a
        case CMD_RELOADMAP: CALL(aScript_reloadmap); break; // $7b
        case CMD_RELOADMAPPART: CALL(aScript_reloadmappart); break; // $7c
        case CMD_WRITECMDQUEUE: CALL(aScript_writecmdqueue); break; // $7d
        case CMD_DELCMDQUEUE: CALL(aScript_delcmdqueue); break; // $7e
        case CMD_PLAYMUSIC: CALL(aScript_playmusic); break; // $7f
        case CMD_ENCOUNTERMUSIC: CALL(aScript_encountermusic); break; // $80
        case CMD_MUSICFADEOUT: CALL(aScript_musicfadeout); break; // $81
        case CMD_PLAYMAPMUSIC: CALL(aScript_playmapmusic); break; // $82
        case CMD_DONTRESTARTMAPMUSIC: CALL(aScript_dontrestartmapmusic); break; // $83
        case CMD_CRY: CALL(aScript_cry); break; // $84
        case CMD_PLAYSOUND: CALL(aScript_playsound); break; // $85
        case CMD_WAITSFX: CALL(aScript_waitsfx); break; // $86
        case CMD_WARPSOUND: CALL(aScript_warpsound); break; // $87
        case CMD_SPECIALSOUND: CALL(aScript_specialsound); break; // $88
        case CMD_AUTOINPUT: CALL(aScript_autoinput); break; // $89
        case CMD_NEWLOADMAP: CALL(aScript_newloadmap); break; // $8a
        case CMD_PAUSE: CALL(aScript_pause); break; // $8b
        case CMD_DEACTIVATEFACING: CALL(aScript_deactivatefacing); break; // $8c
        case CMD_SDEFER: CALL(aScript_sdefer); break; // $8d
        case CMD_WARPCHECK: CALL(aScript_warpcheck); break; // $8e
        case CMD_STOPANDSJUMP: CALL(aScript_stopandsjump); break; // $8f
        case CMD_ENDCALLBACK: CALL(aScript_endcallback); break; // $90
        case CMD_END: CALL(aScript_end); break; // $91
        case CMD_RELOADEND: CALL(aScript_reloadend); break; // $92
        case CMD_ENDALL: CALL(aScript_endall); break; // $93
        case CMD_POKEMART: CALL(aScript_pokemart); break; // $94
        case CMD_ELEVATOR: CALL(aScript_elevator); break; // $95
        case CMD_TRADE: CALL(aScript_trade); break; // $96
        case CMD_ASKFORPHONENUMBER: CALL(aScript_askforphonenumber); break; // $97
        case CMD_PHONECALL: CALL(aScript_phonecall); break; // $98
        case CMD_HANGUP: CALL(aScript_hangup); break; // $99
        case CMD_DESCRIBEDECORATION: CALL(aScript_describedecoration); break; // $9a
        case CMD_FRUITTREE: CALL(aScript_fruittree); break; // $9b
        case CMD_SPECIALPHONECALL: CALL(aScript_specialphonecall); break; // $9c
        case CMD_CHECKPHONECALL: CALL(aScript_checkphonecall); break; // $9d
        case CMD_VERBOSEGIVEITEM: CALL(aScript_verbosegiveitem); break; // $9e
        case CMD_VERBOSEGIVEITEMVAR: CALL(aScript_verbosegiveitemvar); break; // $9f
        case CMD_SWARM: CALL(aScript_swarm); break; // $a0
        case CMD_HALLOFFAME: CALL(aScript_halloffame); break; // $a1
        case CMD_CREDITS: CALL(aScript_credits); break; // $a2
        case CMD_WARPFACING: CALL(aScript_warpfacing); break; // $a3
        case CMD_BATTLETOWERTEXT: CALL(aScript_battletowertext); break; // $a4
        case CMD_GETLANDMARKNAME: CALL(aScript_getlandmarkname); break; // $a5
        case CMD_GETTRAINERCLASSNAME: CALL(aScript_gettrainerclassname); break; // $a6
        case CMD_GETNAME: CALL(aScript_getname); break; // $a7
        case CMD_WAIT: CALL(aScript_wait); break; // $a8
        case CMD_CHECKSAVE: CALL(aScript_checksave); break; // $a9
    }
    RET;

}

void ScriptCommandTable(void){
//  entries correspond to *_command constants (see macros/scripts/events.asm)
    //table_width ['2', 'ScriptCommandTable']
    //dw ['Script_scall'];  // 00
    //dw ['Script_farscall'];  // 01
    //dw ['Script_memcall'];  // 02
    //dw ['Script_sjump'];  // 03
    //dw ['Script_farsjump'];  // 04
    //dw ['Script_memjump'];  // 05
    //dw ['Script_ifequal'];  // 06
    //dw ['Script_ifnotequal'];  // 07
    //dw ['Script_iffalse'];  // 08
    //dw ['Script_iftrue'];  // 09
    //dw ['Script_ifgreater'];  // 0a
    //dw ['Script_ifless'];  // 0b
    //dw ['Script_jumpstd'];  // 0c
    //dw ['Script_callstd'];  // 0d
    //dw ['Script_callasm'];  // 0e
    //dw ['Script_special'];  // 0f
    //dw ['Script_memcallasm'];  // 10
    //dw ['Script_checkmapscene'];  // 11
    //dw ['Script_setmapscene'];  // 12
    //dw ['Script_checkscene'];  // 13
    //dw ['Script_setscene'];  // 14
    //dw ['Script_setval'];  // 15
    //dw ['Script_addval'];  // 16
    //dw ['Script_random'];  // 17
    //dw ['Script_checkver'];  // 18
    //dw ['Script_readmem'];  // 19
    //dw ['Script_writemem'];  // 1a
    //dw ['Script_loadmem'];  // 1b
    //dw ['Script_readvar'];  // 1c
    //dw ['Script_writevar'];  // 1d
    //dw ['Script_loadvar'];  // 1e
    //dw ['Script_giveitem'];  // 1f
    //dw ['Script_takeitem'];  // 20
    //dw ['Script_checkitem'];  // 21
    //dw ['Script_givemoney'];  // 22
    //dw ['Script_takemoney'];  // 23
    //dw ['Script_checkmoney'];  // 24
    //dw ['Script_givecoins'];  // 25
    //dw ['Script_takecoins'];  // 26
    //dw ['Script_checkcoins'];  // 27
    //dw ['Script_addcellnum'];  // 28
    //dw ['Script_delcellnum'];  // 29
    //dw ['Script_checkcellnum'];  // 2a
    //dw ['Script_checktime'];  // 2b
    //dw ['Script_checkpoke'];  // 2c
    //dw ['Script_givepoke'];  // 2d
    //dw ['Script_giveegg'];  // 2e
    //dw ['Script_givepokemail'];  // 2f
    //dw ['Script_checkpokemail'];  // 30
    //dw ['Script_checkevent'];  // 31
    //dw ['Script_clearevent'];  // 32
    //dw ['Script_setevent'];  // 33
    //dw ['Script_checkflag'];  // 34
    //dw ['Script_clearflag'];  // 35
    //dw ['Script_setflag'];  // 36
    //dw ['Script_wildon'];  // 37
    //dw ['Script_wildoff'];  // 38
    //dw ['Script_xycompare'];  // 39
    //dw ['Script_warpmod'];  // 3a
    //dw ['Script_blackoutmod'];  // 3b
    //dw ['Script_warp'];  // 3c
    //dw ['Script_getmoney'];  // 3d
    //dw ['Script_getcoins'];  // 3e
    //dw ['Script_getnum'];  // 3f
    //dw ['Script_getmonname'];  // 40
    //dw ['Script_getitemname'];  // 41
    //dw ['Script_getcurlandmarkname'];  // 42
    //dw ['Script_gettrainername'];  // 43
    //dw ['Script_getstring'];  // 44
    //dw ['Script_itemnotify'];  // 45
    //dw ['Script_pocketisfull'];  // 46
    //dw ['Script_opentext'];  // 47
    //dw ['Script_refreshscreen'];  // 48
    //dw ['Script_closetext'];  // 49
    //dw ['Script_writeunusedbyte'];  // 4a
    //dw ['Script_farwritetext'];  // 4b
    //dw ['Script_writetext'];  // 4c
    //dw ['Script_repeattext'];  // 4d
    //dw ['Script_yesorno'];  // 4e
    //dw ['Script_loadmenu'];  // 4f
    //dw ['Script_closewindow'];  // 50
    //dw ['Script_jumptextfaceplayer'];  // 51
    //dw ['Script_farjumptext'];  // 52
    //dw ['Script_jumptext'];  // 53
    //dw ['Script_waitbutton'];  // 54
    //dw ['Script_promptbutton'];  // 55
    //dw ['Script_pokepic'];  // 56
    //dw ['Script_closepokepic'];  // 57
    //dw ['Script__2dmenu'];  // 58
    //dw ['Script_verticalmenu'];  // 59
    //dw ['Script_loadpikachudata'];  // 5a
    //dw ['Script_randomwildmon'];  // 5b
    //dw ['Script_loadtemptrainer'];  // 5c
    //dw ['Script_loadwildmon'];  // 5d
    //dw ['Script_loadtrainer'];  // 5e
    //dw ['Script_startbattle'];  // 5f
    //dw ['Script_reloadmapafterbattle'];  // 60
    //dw ['Script_catchtutorial'];  // 61
    //dw ['Script_trainertext'];  // 62
    //dw ['Script_trainerflagaction'];  // 63
    //dw ['Script_winlosstext'];  // 64
    //dw ['Script_scripttalkafter'];  // 65
    //dw ['Script_endifjustbattled'];  // 66
    //dw ['Script_checkjustbattled'];  // 67
    //dw ['Script_setlasttalked'];  // 68
    //dw ['Script_applymovement'];  // 69
    //dw ['Script_applymovementlasttalked'];  // 6a
    //dw ['Script_faceplayer'];  // 6b
    //dw ['Script_faceobject'];  // 6c
    //dw ['Script_variablesprite'];  // 6d
    //dw ['Script_disappear'];  // 6e
    //dw ['Script_appear'];  // 6f
    //dw ['Script_follow'];  // 70
    //dw ['Script_stopfollow'];  // 71
    //dw ['Script_moveobject'];  // 72
    //dw ['Script_writeobjectxy'];  // 73
    //dw ['Script_loademote'];  // 74
    //dw ['Script_showemote'];  // 75
    //dw ['Script_turnobject'];  // 76
    //dw ['Script_follownotexact'];  // 77
    //dw ['Script_earthquake'];  // 78
    //dw ['Script_changemapblocks'];  // 79
    //dw ['Script_changeblock'];  // 7a
    //dw ['Script_reloadmap'];  // 7b
    //dw ['Script_reloadmappart'];  // 7c
    //dw ['Script_writecmdqueue'];  // 7d
    //dw ['Script_delcmdqueue'];  // 7e
    //dw ['Script_playmusic'];  // 7f
    //dw ['Script_encountermusic'];  // 80
    //dw ['Script_musicfadeout'];  // 81
    //dw ['Script_playmapmusic'];  // 82
    //dw ['Script_dontrestartmapmusic'];  // 83
    //dw ['Script_cry'];  // 84
    //dw ['Script_playsound'];  // 85
    //dw ['Script_waitsfx'];  // 86
    //dw ['Script_warpsound'];  // 87
    //dw ['Script_specialsound'];  // 88
    //dw ['Script_autoinput'];  // 89
    //dw ['Script_newloadmap'];  // 8a
    //dw ['Script_pause'];  // 8b
    //dw ['Script_deactivatefacing'];  // 8c
    //dw ['Script_sdefer'];  // 8d
    //dw ['Script_warpcheck'];  // 8e
    //dw ['Script_stopandsjump'];  // 8f
    //dw ['Script_endcallback'];  // 90
    //dw ['Script_end'];  // 91
    //dw ['Script_reloadend'];  // 92
    //dw ['Script_endall'];  // 93
    //dw ['Script_pokemart'];  // 94
    //dw ['Script_elevator'];  // 95
    //dw ['Script_trade'];  // 96
    //dw ['Script_askforphonenumber'];  // 97
    //dw ['Script_phonecall'];  // 98
    //dw ['Script_hangup'];  // 99
    //dw ['Script_describedecoration'];  // 9a
    //dw ['Script_fruittree'];  // 9b
    //dw ['Script_specialphonecall'];  // 9c
    //dw ['Script_checkphonecall'];  // 9d
    //dw ['Script_verbosegiveitem'];  // 9e
    //dw ['Script_verbosegiveitemvar'];  // 9f
    //dw ['Script_swarm'];  // a0
    //dw ['Script_halloffame'];  // a1
    //dw ['Script_credits'];  // a2
    //dw ['Script_warpfacing'];  // a3
    //dw ['Script_battletowertext'];  // a4
    //dw ['Script_getlandmarkname'];  // a5
    //dw ['Script_gettrainerclassname'];  // a6
    //dw ['Script_getname'];  // a7
    //dw ['Script_wait'];  // a8
    //dw ['Script_checksave'];  // a9
    //assert_table_length ['NUM_EVENT_COMMANDS']

    return StartScript();
}

void StartScript(void){
    LD_HL(wScriptFlags);
    SET_hl(SCRIPT_RUNNING);
    RET;

}

void StartScript_Conv(void){
    // LD_HL(wScriptFlags);
    // SET_hl(SCRIPT_RUNNING);
    // RET;
    wram->wScriptFlags |= (1 << SCRIPT_RUNNING);
}

void CheckScript(void){
    LD_HL(wScriptFlags);
    BIT_hl(SCRIPT_RUNNING);
    RET;

}

bool CheckScript_Conv(void){
    // LD_HL(wScriptFlags);
    // BIT_hl(SCRIPT_RUNNING);
    // RET;
    return bit_test(wram->wScriptFlags, SCRIPT_RUNNING);
}

void StopScript(void){
    LD_HL(wScriptFlags);
    RES_hl(SCRIPT_RUNNING);
    RET;

}

void StopScript_Conv(void){
    // LD_HL(wScriptFlags);
    // RES_hl(SCRIPT_RUNNING);
    // RET;
    wram->wScriptFlags &= (1 << SCRIPT_RUNNING) ^ 0xff;
}

void Script_callasm(void){
    CALL(aGetScriptByte);
    LD_B_A;
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_A_B;
    RST(aFarCall);
    RET;

}

void Script_special(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    FARCALL(aSpecial);
    RET;

}

void Script_memcallasm(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_B_hl;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_B;
    RST(aFarCall);
    RET;

}

void Script_jumptextfaceplayer(void){
    LD_A_addr(wScriptBank);
    LD_addr_A(wScriptTextBank);
    CALL(aGetScriptByte);
    LD_addr_A(wScriptTextAddr);
    CALL(aGetScriptByte);
    LD_addr_A(wScriptTextAddr + 1);
    LD_B(BANK(aJumpTextFacePlayerScript));
    LD_HL(mJumpTextFacePlayerScript);
    JP(mScriptJump);

}

void Script_jumptext(void){
    LD_A_addr(wScriptBank);
    LD_addr_A(wScriptTextBank);
    CALL(aGetScriptByte);
    LD_addr_A(wScriptTextAddr);
    CALL(aGetScriptByte);
    LD_addr_A(wScriptTextAddr + 1);
    LD_B(BANK(aJumpTextScript));
    LD_HL(mJumpTextScript);
    JP(mScriptJump);

}

#include "../../util/scripting_macros.h"

bool JumpTextFacePlayerScript(script_s* s){
    SCRIPT_BEGIN
    //faceplayer ['?']
    faceplayer;
    // return JumpTextScript();
    SCRIPT_FALLTHROUGH(JumpTextScript)
}

bool JumpTextScript(script_s* s){
    SCRIPT_BEGIN
    //opentext ['?']
    opentext;
    //repeattext ['-1', '-1']
    repeattext(0xffff);
    //waitbutton ['?']
    waitbutton;
    //closetext ['?']
    closetext;
    //end ['?']
    SCRIPT_END
    // return Script_farjumptext();
}

void Script_farjumptext(void){
    CALL(aGetScriptByte);
    LD_addr_A(wScriptTextBank);
    CALL(aGetScriptByte);
    LD_addr_A(wScriptTextAddr);
    CALL(aGetScriptByte);
    LD_addr_A(wScriptTextAddr + 1);
    LD_B(BANK(aJumpTextScript));
    LD_HL(mJumpTextScript);
    JP(mScriptJump);

}

void Script_writetext(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_A_addr(wScriptBank);
    LD_B_A;
    CALL(aMapTextbox);
    RET;

}

void Script_farwritetext(void){
    CALL(aGetScriptByte);
    LD_B_A;
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    CALL(aMapTextbox);
    RET;

}

void Script_repeattext(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    CP_A(-1);
    IF_NZ goto done;
    LD_A_L;
    CP_A(-1);
    IF_NZ goto done;
    LD_HL(wScriptTextBank);
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aMapTextbox);
    RET;


done:
    RET;

}

void Script_repeattext_Conv(script_s* s, uint16_t hl){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // CP_A(-1);
    // IF_NZ goto done;
    // LD_A_L;
    // CP_A(-1);
    // IF_NZ goto done;
    if(hl == 0xffff)
        return;
    // LD_HL(wScriptTextBank);
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    REG_B = wram->wScriptTextBank;
    REG_HL = wram->wScriptTextAddr;
    CALL(aMapTextbox);
    // RET;


// done:
    // RET;
}

void Script_waitbutton(void){
    JP(mWaitButton);

}

void Script_waitbutton_Conv(script_s* s){
    (void)s;
    // JP(mWaitButton);
    return WaitButton_Conv();
}

void Script_promptbutton(void){
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);
    CALL(aWaitBGMap);
    CALL(aPromptButton);
    POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;

}

void Script_yesorno(void){
    CALL(aYesNoBox);
    LD_A(FALSE);
    IF_C goto no;
    LD_A(TRUE);

no:
    LD_addr_A(wScriptVar);
    RET;

}

void Script_loadmenu(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_DE(mLoadMenuHeader);
    LD_A_addr(wScriptBank);
    CALL(aCall_a_de);
    CALL(aUpdateSprites);
    RET;

}

void Script_closewindow(void){
    CALL(aCloseWindow);
    CALL(aUpdateSprites);
    RET;

}

void Script_pokepic(void){
    CALL(aGetScriptByte);
    AND_A_A;
    IF_NZ goto ok;
    LD_A_addr(wScriptVar);

ok:
    LD_addr_A(wCurPartySpecies);
    FARCALL(aPokepic);
    RET;

}

void Script_closepokepic(void){
    FARCALL(aClosePokepic);
    RET;

}

void Script_verticalmenu(void){
    LD_A_addr(wScriptBank);
    LD_HL(mVerticalMenu);
    RST(aFarCall);
    LD_A_addr(wMenuCursorY);
    IF_NC goto ok;
    XOR_A_A;

ok:
    LD_addr_A(wScriptVar);
    RET;

}

void Script__2dmenu(void){
    LD_A_addr(wScriptBank);
    LD_HL(mv_2DMenu);
    RST(aFarCall);
    LD_A_addr(wMenuCursorPosition);
    IF_NC goto ok;
    XOR_A_A;

ok:
    LD_addr_A(wScriptVar);
    RET;

}

void Script_battletowertext(void){
    CALL(aSetUpTextbox);
    CALL(aGetScriptByte);
    LD_C_A;
    FARCALL(aBattleTowerText);
    RET;

}

void Script_verbosegiveitem(void){
    CALL(aScript_giveitem);
    CALL(aCurItemName);
    LD_DE(wStringBuffer1);
    LD_A(STRING_BUFFER_4);
    CALL(aCopyConvertedText);
    LD_B(BANK(aGiveItemScript));
    LD_DE(mGiveItemScript);
    JP(mScriptCall);

}

void GiveItemScript_DummyFunction(void){
    RET;

}

void GiveItemScript(void){
    //callasm ['GiveItemScript_DummyFunction']
    //writetext ['.ReceivedItemText']
    //iffalse ['.Full']
    //waitsfx ['?']
    //specialsound ['?']
    //waitbutton ['?']
    //itemnotify ['?']
    //end ['?']


Full:
    //promptbutton ['?']
    //pocketisfull ['?']
    //end ['?']


ReceivedItemText:
    //text_far ['_ReceivedItemText']
    //text_end ['?']

    return Script_verbosegiveitemvar();
}

void Script_verbosegiveitemvar(void){
    CALL(aGetScriptByte);
    CP_A(ITEM_FROM_MEM);
    IF_NZ goto ok;
    LD_A_addr(wScriptVar);

ok:
    LD_addr_A(wCurItem);
    CALL(aGetScriptByte);
    CALL(aGetVarAction);
    LD_A_de;
    LD_addr_A(wItemQuantityChange);
    LD_HL(wNumItems);
    CALL(aReceiveItem);
    LD_A(TRUE);
    IF_C goto ok2;
    XOR_A_A;

ok2:
    LD_addr_A(wScriptVar);
    CALL(aCurItemName);
    LD_DE(wStringBuffer1);
    LD_A(STRING_BUFFER_4);
    CALL(aCopyConvertedText);
    LD_B(BANK(aGiveItemScript));
    LD_DE(mGiveItemScript);
    JP(mScriptCall);

}

void Script_itemnotify(void){
    CALL(aGetPocketName);
    CALL(aCurItemName);
    LD_B(BANK(aPutItemInPocketText));
    LD_HL(mPutItemInPocketText);
    CALL(aMapTextbox);
    RET;

}

void Script_pocketisfull(void){
    CALL(aGetPocketName);
    CALL(aCurItemName);
    LD_B(BANK(aPocketIsFullText));
    LD_HL(mPocketIsFullText);
    CALL(aMapTextbox);
    RET;

}

void Script_specialsound(void){
    FARCALL(aCheckItemPocket);
    LD_A_addr(wItemAttributeValue);
    CP_A(TM_HM);
    LD_DE(SFX_GET_TM);
    IF_Z goto play;
    LD_DE(SFX_ITEM);

play:
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    RET;

}

void GetPocketName(void){
    FARCALL(aCheckItemPocket);
    LD_A_addr(wItemAttributeValue);
    DEC_A;
    LD_HL(mItemPocketNames);
    maskbits(NUM_POCKETS, 0);
    ADD_A_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wStringBuffer3);
    CALL(aCopyName2);
    RET;

// INCLUDE "data/items/pocket_names.asm"

    return CurItemName();
}

void CurItemName(void){
    LD_A_addr(wCurItem);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    RET;

}

void PutItemInPocketText(void){
    //text_far ['_PutItemInPocketText']
    //text_end ['?']

    return PocketIsFullText();
}

void PocketIsFullText(void){
    //text_far ['_PocketIsFullText']
    //text_end ['?']

    return Script_pokemart();
}

void Script_pokemart(void){
    CALL(aGetScriptByte);
    LD_C_A;
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_A_addr(wScriptBank);
    LD_B_A;
    FARCALL(aOpenMartDialog);
    RET;

}

void Script_elevator(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_A_addr(wScriptBank);
    LD_B_A;
    FARCALL(aElevator);
    RET_C ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_trade(void){
    CALL(aGetScriptByte);
    LD_E_A;
    FARCALL(aNPCTrade);
    RET;

}

void Script_phonecall(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_A_addr(wScriptBank);
    LD_B_A;
    FARCALL(aPhoneCall);
    RET;

}

void Script_hangup(void){
    FARCALL(aHangUp);
    RET;

}

void Script_askforphonenumber(void){
    CALL(aYesNoBox);
    IF_C goto refused;
    CALL(aGetScriptByte);
    LD_C_A;
    FARCALL(aAddPhoneNumber);
    IF_C goto phonefull;
    XOR_A_A;  // PHONE_CONTACT_GOT
    goto done;

phonefull:
    LD_A(PHONE_CONTACTS_FULL);
    goto done;

refused:
    CALL(aGetScriptByte);
    LD_A(PHONE_CONTACT_REFUSED);

done:
    LD_addr_A(wScriptVar);
    RET;

}

void Script_describedecoration(void){
    CALL(aGetScriptByte);
    LD_B_A;
    FARCALL(aDescribeDecoration);
    LD_H_D;
    LD_L_E;
    JP(mScriptJump);

}

void Script_fruittree(void){
    CALL(aGetScriptByte);
    LD_addr_A(wCurFruitTree);
    LD_B(BANK(aFruitTreeScript));
    LD_HL(mFruitTreeScript);
    JP(mScriptJump);

}

void Script_swarm(void){
    CALL(aGetScriptByte);
    LD_C_A;
    CALL(aGetScriptByte);
    LD_D_A;
    CALL(aGetScriptByte);
    LD_E_A;
    FARCALL(aStoreSwarmMapIndices);
    RET;

}

void Script_trainertext(void){
    CALL(aGetScriptByte);
    LD_C_A;
    LD_B(0);
    LD_HL(wSeenTextPointer);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wSeenTrainerBank);
    LD_B_A;
    CALL(aMapTextbox);
    RET;

}

void Script_scripttalkafter(void){
    LD_HL(wScriptAfterPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wSeenTrainerBank);
    LD_B_A;
    JP(mScriptJump);

}

void Script_trainerflagaction(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    LD_HL(wTempTrainerEventFlag);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALL(aGetScriptByte);
    LD_B_A;
    CALL(aEventFlagAction);
    LD_A_C;
    AND_A_A;
    RET_Z ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_winlosstext(void){
    LD_HL(wWinTextPointer);
    CALL(aGetScriptByte);
    LD_hli_A;
    CALL(aGetScriptByte);
    LD_hli_A;
    LD_HL(wLossTextPointer);
    CALL(aGetScriptByte);
    LD_hli_A;
    CALL(aGetScriptByte);
    LD_hli_A;
    RET;

}

void Script_endifjustbattled(void){
    LD_A_addr(wRunningTrainerBattleScript);
    AND_A_A;
    RET_Z ;
    JP(mScript_end);

}

void Script_checkjustbattled(void){
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    LD_A_addr(wRunningTrainerBattleScript);
    AND_A_A;
    RET_NZ ;
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;

}

void Script_encountermusic(void){
    LD_A_addr(wOtherTrainerClass);
    LD_E_A;
    FARCALL(aPlayTrainerEncounterMusic);
    RET;

}

void Script_playmapmusic(void){
    CALL(aPlayMapMusic);
    RET;

}

void Script_playmusic(void){
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    XOR_A_A;
    LD_addr_A(wMusicFade);
    CALL(aMaxVolume);
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    CALL(aPlayMusic);
    RET;

}

void Script_musicfadeout(void){
    CALL(aGetScriptByte);
    LD_addr_A(wMusicFadeID);
    CALL(aGetScriptByte);
    LD_addr_A(wMusicFadeID + 1);
    CALL(aGetScriptByte);
    AND_A(~(1 << MUSIC_FADE_IN_F));
    LD_addr_A(wMusicFade);
    RET;

}

void Script_playsound(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    CALL(aPlaySFX);
    RET;

}

void Script_waitsfx(void){
    CALL(aWaitSFX);
    RET;

}

void Script_warpsound(void){
    FARCALL(aGetWarpSFX);
    CALL(aPlaySFX);
    RET;

}

void Script_cry(void){
    CALL(aGetScriptByte);
    PUSH_AF;
    CALL(aGetScriptByte);
    POP_AF;
    AND_A_A;
    IF_NZ goto ok;
    LD_A_addr(wScriptVar);

ok:
    CALL(aPlayMonCry);
    RET;

}

void GetScriptObject(void){
    AND_A_A;  // PLAYER?
    RET_Z ;
    CP_A(LAST_TALKED);
    RET_Z ;
    DEC_A;
    RET;

}

void Script_setlasttalked(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    LDH_addr_A(hLastTalked);
    RET;

}

void Script_applymovement(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    LD_C_A;

    return ApplyMovement();
}

void ApplyMovement(void){
    PUSH_BC;
    LD_A_C;
    FARCALL(aFreezeAllOtherObjects);
    POP_BC;

    PUSH_BC;
    CALL(aUnfreezeFollowerObject);
    POP_BC;

    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_A_addr(wScriptBank);
    LD_B_A;
    CALL(aGetMovementData);
    RET_C ;

    LD_A(SCRIPT_WAIT_MOVEMENT);
    LD_addr_A(wScriptMode);
    CALL(aStopScript);
    RET;

}

void UnfreezeFollowerObject(void){
    FARCALL(av_UnfreezeFollowerObject);
    RET;

}

void Script_applymovementlasttalked(void){
//  apply movement to last talked

    LDH_A_addr(hLastTalked);
    LD_C_A;
    JP(mApplyMovement);

}

void Script_faceplayer(void){
    LDH_A_addr(hLastTalked);
    AND_A_A;
    RET_Z ;
    LD_D(0x0);
    LDH_A_addr(hLastTalked);
    LD_E_A;
    FARCALL(aGetRelativeFacing);
    LD_A_D;
    ADD_A_A;
    ADD_A_A;
    LD_E_A;
    LDH_A_addr(hLastTalked);
    LD_D_A;
    CALL(aApplyObjectFacing);
    RET;

}

void Script_faceplayer_Conv(script_s* s){
    (void)s;
    // LDH_A_addr(hLastTalked);
    // AND_A_A;
    // RET_Z ;
    if(hram->hLastTalked == 0)
        return;
    // LD_D(0x0);
    // LDH_A_addr(hLastTalked);
    // LD_E_A;
    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    REG_DE = hram->hLastTalked;
    FARCALL(aGetRelativeFacing);
    // LD_A_D;
    // ADD_A_A;
    // ADD_A_A;
    // LD_E_A;
    // LDH_A_addr(hLastTalked);
    // LD_D_A;
    // CALL(aApplyObjectFacing);
    ApplyObjectFacing_Conv(hram->hLastTalked, REG_D << 2);
    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    // RET;

}

void Script_faceobject(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    CP_A(LAST_TALKED);
    IF_C goto ok;
    LDH_A_addr(hLastTalked);

ok:
    LD_E_A;
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    CP_A(LAST_TALKED);
    IF_NZ goto ok2;
    LDH_A_addr(hLastTalked);

ok2:
    LD_D_A;
    PUSH_DE;
    FARCALL(aGetRelativeFacing);
    POP_BC;
    RET_C ;
    LD_A_D;
    ADD_A_A;
    ADD_A_A;
    LD_E_A;
    LD_D_C;
    CALL(aApplyObjectFacing);
    RET;

}

void Script_turnobject(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    CP_A(LAST_TALKED);
    IF_NZ goto ok;
    LDH_A_addr(hLastTalked);

ok:
    LD_D_A;
    CALL(aGetScriptByte);
    ADD_A_A;
    ADD_A_A;
    LD_E_A;
    CALL(aApplyObjectFacing);
    RET;

}

void ApplyObjectFacing(void){
    LD_A_D;
    PUSH_DE;
    CALL(aCheckObjectVisibility);
    IF_C goto not_visible;
    LD_HL(OBJECT_SPRITE);
    ADD_HL_BC;
    LD_A_hl;
    PUSH_BC;
    CALL(aDoesSpriteHaveFacings);
    POP_BC;
    IF_C goto not_visible;  // STILL_SPRITE
    LD_HL(OBJECT_FLAGS1);
    ADD_HL_BC;
    BIT_hl(FIXED_FACING_F);
    IF_NZ goto not_visible;
    POP_DE;
    LD_A_E;
    CALL(aSetSpriteDirection);
    LD_HL(wVramState);
    BIT_hl(6);
    IF_NZ goto text_state;
    CALL(aApplyObjectFacing_DisableTextTiles);

text_state:
    CALL(aUpdateSprites);
    RET;


not_visible:
    POP_DE;
    SCF;
    RET;


DisableTextTiles:
    CALL(aLoadMapPart);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);

loop:
    RES_hl(7);
    INC_HL;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;

}

static void ApplyObjectFacing_DisableTextTiles(void) {
// DisableTextTiles:
    CALL(aLoadMapPart);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    uint8_t* hl = wram->wTilemap + coordidx(0, 0);
    uint16_t bc = SCREEN_WIDTH * SCREEN_HEIGHT;

// loop:
    do {
        // RES_hl(7);
        *(hl++) &= (1 << 7) ^ 0xff;
        // INC_HL;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
}

bool ApplyObjectFacing_Conv(uint8_t d, uint8_t e){
    // LD_A_D;
    // PUSH_DE;
    // CALL(aCheckObjectVisibility);
    // IF_C goto not_visible;
    if(!CheckObjectVisibility_Conv(d))
        return false;
    struct Object* bc = GetObjectStruct_Conv(hram->hObjectStructIndex);
    // LD_HL(OBJECT_SPRITE);
    // ADD_HL_BC;
    // LD_A_hl;
    // PUSH_BC;
    // CALL(aDoesSpriteHaveFacings);
    // POP_BC;
    // IF_C goto not_visible;  // STILL_SPRITE
    if(!v_DoesSpriteHaveFacings_Conv(bc->sprite))
        return false;
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // BIT_hl(FIXED_FACING_F);s
    // IF_NZ goto not_visible;
    if(bit_test(bc->flags1, FIXED_FACING_F))
        return false;
    // POP_DE;
    // LD_A_E;
    // CALL(aSetSpriteDirection);
    SetSpriteDirection_Conv(bc, e);
    // LD_HL(wVramState);
    // BIT_hl(6);
    // IF_NZ goto text_state;
    if(!bit_test(wram->wVramState, 6)) {
        // CALL(aApplyObjectFacing_DisableTextTiles);
        ApplyObjectFacing_DisableTextTiles();
    }

// text_state:
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // RET;
    return true;


// not_visible:
    // POP_DE;
    // SCF;
    // RET;
}

void Script_variablesprite(void){
    CALL(aGetScriptByte);
    LD_E_A;
    LD_D(0);
    LD_HL(wVariableSprites);
    ADD_HL_DE;
    CALL(aGetScriptByte);
    LD_hl_A;
    RET;

}

void Script_appear(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    CALL(aUnmaskCopyMapObjectStruct);
    LDH_A_addr(hMapObjectIndex);
    LD_B(0);  // clear
    CALL(aApplyEventActionAppearDisappear);
    RET;

}

void Script_disappear(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    CP_A(LAST_TALKED);
    IF_NZ goto ok;
    LDH_A_addr(hLastTalked);

ok:
    CALL(aDeleteObjectStruct);
    LDH_A_addr(hMapObjectIndex);
    LD_B(1);  // set
    CALL(aApplyEventActionAppearDisappear);
    FARCALL(av_UpdateSprites);
    RET;

}

void ApplyEventActionAppearDisappear(void){
    PUSH_BC;
    CALL(aGetMapObject);
    LD_HL(MAPOBJECT_EVENT_FLAG);
    ADD_HL_BC;
    POP_BC;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_A(-1);
    CP_A_E;
    IF_NZ goto okay;
    CP_A_D;
    IF_NZ goto okay;
    XOR_A_A;
    RET;

okay:
    CALL(aEventFlagAction);
    RET;

}

void Script_follow(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    LD_B_A;
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    LD_C_A;
    FARCALL(aStartFollow);
    RET;

}

void Script_stopfollow(void){
    FARCALL(aStopFollow);
    RET;

}

void Script_moveobject(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    LD_B_A;
    CALL(aGetScriptByte);
    ADD_A(4);
    LD_D_A;
    CALL(aGetScriptByte);
    ADD_A(4);
    LD_E_A;
    FARCALL(aCopyDECoordsToMapObject);
    RET;

}

void Script_writeobjectxy(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    CP_A(LAST_TALKED);
    IF_NZ goto ok;
    LDH_A_addr(hLastTalked);

ok:
    LD_B_A;
    FARCALL(aWriteObjectXY);
    RET;

}

void Script_follownotexact(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    LD_B_A;
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    LD_C_A;
    FARCALL(aFollowNotExact);
    RET;

}

void Script_loademote(void){
    CALL(aGetScriptByte);
    CP_A(EMOTE_FROM_MEM);
    IF_NZ goto not_var_emote;
    LD_A_addr(wScriptVar);

not_var_emote:
    LD_C_A;
    FARCALL(aLoadEmote);
    RET;

}

void Script_showemote(void){
    CALL(aGetScriptByte);
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    CALL(aGetScriptObject);
    CP_A(LAST_TALKED);
    IF_Z goto ok;
    LDH_addr_A(hLastTalked);

ok:
    CALL(aGetScriptByte);
    LD_addr_A(wScriptDelay);
    LD_B(BANK(aShowEmoteScript));
    LD_DE(mShowEmoteScript);
    JP(mScriptCall);

}

void ShowEmoteScript(void){
    //loademote ['EMOTE_FROM_MEM']
    //applymovementlasttalked ['.Show']
    //pause ['0']
    //applymovementlasttalked ['.Hide']
    //end ['?']


Show:
    //show_emote ['?']
    //step_sleep ['1']
    //step_end ['?']


Hide:
    //hide_emote ['?']
    //step_sleep ['1']
    //step_end ['?']

    return Script_earthquake();
}

void Script_earthquake(void){
    LD_HL(mEarthquakeMovement);
    LD_DE(wEarthquakeMovementDataBuffer);
    LD_BC(mEarthquakeMovement_End - mEarthquakeMovement);
    CALL(aCopyBytes);
    CALL(aGetScriptByte);
    LD_addr_A(wEarthquakeMovementDataBuffer + 1);
    AND_A(0b00111111);
    LD_addr_A(wEarthquakeMovementDataBuffer + 3);
    LD_B(BANK(aScript_earthquake_script));
    LD_DE(mScript_earthquake_script);
    JP(mScriptCall);


script:
    //applymovement ['PLAYER', 'wEarthquakeMovementDataBuffer']
    //end ['?']

    return EarthquakeMovement();
}

void EarthquakeMovement(void){
    //step_shake ['16']  // the 16 gets overwritten with the script byte
    //step_sleep ['16']  // the 16 gets overwritten with the lower 6 bits of the script byte
    //step_end ['?']

End:

    return Script_loadpikachudata();
}

void Script_loadpikachudata(void){
    LD_A(PIKACHU);
    LD_addr_A(wTempWildMonSpecies);
    LD_A(5);
    LD_addr_A(wCurPartyLevel);
    RET;

}

void Script_randomwildmon(void){
    XOR_A_A;
    LD_addr_A(wBattleScriptFlags);
    RET;

}

void Script_loadtemptrainer(void){
    LD_A((1 << 7) | 1);
    LD_addr_A(wBattleScriptFlags);
    LD_A_addr(wTempTrainerClass);
    LD_addr_A(wOtherTrainerClass);
    LD_A_addr(wTempTrainerID);
    LD_addr_A(wOtherTrainerID);
    RET;

}

void Script_loadwildmon(void){
    LD_A((1 << 7));
    LD_addr_A(wBattleScriptFlags);
    CALL(aGetScriptByte);
    LD_addr_A(wTempWildMonSpecies);
    CALL(aGetScriptByte);
    LD_addr_A(wCurPartyLevel);
    RET;

}

void Script_loadtrainer(void){
    LD_A((1 << 7) | 1);
    LD_addr_A(wBattleScriptFlags);
    CALL(aGetScriptByte);
    LD_addr_A(wOtherTrainerClass);
    CALL(aGetScriptByte);
    LD_addr_A(wOtherTrainerID);
    RET;

}

void Script_startbattle(void){
    CALL(aBufferScreen);
    PREDEF(pStartBattle);
    LD_A_addr(wBattleResult);
    AND_A(~BATTLERESULT_BITMASK);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_catchtutorial(void){
    CALL(aGetScriptByte);
    LD_addr_A(wBattleType);
    CALL(aBufferScreen);
    FARCALL(aCatchTutorial);
    JP(mScript_reloadmap);

}

void Script_reloadmapafterbattle(void){
    LD_HL(wBattleScriptFlags);
    LD_D_hl;
    LD_hl(0);
    LD_A_addr(wBattleResult);
    AND_A(~BATTLERESULT_BITMASK);
    CP_A(LOSE);
    IF_NZ goto notblackedout;
    LD_B(BANK(aScript_BattleWhiteout));
    LD_HL(mScript_BattleWhiteout);
    JP(mScriptJump);


notblackedout:
    BIT_D(0);
    IF_Z goto was_wild;
    FARCALL(aMomTriesToBuySomething);
    goto done;


was_wild:
    LD_A_addr(wBattleResult);
    BIT_A(BATTLERESULT_BOX_FULL);
    IF_Z goto done;
    LD_B(BANK(aScript_SpecialBillCall));
    LD_DE(mScript_SpecialBillCall);
    FARCALL(aLoadScriptBDE);

done:
    JP(mScript_reloadmap);

}

void Script_reloadmap(void){
    XOR_A_A;
    LD_addr_A(wBattleScriptFlags);
    LD_A(MAPSETUP_RELOADMAP);
    LDH_addr_A(hMapEntryMethod);
    LD_A(MAPSTATUS_ENTER);
    CALL(aLoadMapStatus);
    CALL(aStopScript);
    RET;

}

void Script_reloadmap_Conv(script_s* s){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wBattleScriptFlags);
    wram->wBattleScriptFlags = 0;
    // LD_A(MAPSETUP_RELOADMAP);
    // LDH_addr_A(hMapEntryMethod);
    hram->hMapEntryMethod = MAPSETUP_RELOADMAP;
    LD_A(MAPSTATUS_ENTER);
    CALL(aLoadMapStatus);
    CALL(aStopScript);
    // RET;
}

void Script_scall(void){
    LD_A_addr(wScriptBank);
    LD_B_A;
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    JR(mScriptCall);

}

void Script_farscall(void){
    CALL(aGetScriptByte);
    LD_B_A;
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    JR(mScriptCall);

}

void Script_memcall(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_B_hl;
    INC_HL;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
// fallthrough

    return ScriptCall();
}

void ScriptCall(void){
//  Bug: The script stack has a capacity of 5 scripts, yet there is
//  nothing to stop you from pushing a sixth script.  The high part
//  of the script address can then be overwritten by modifications
//  to wScriptDelay, causing the script to return to the rst/interrupt
//  space.

    PUSH_DE;
    LD_HL(wScriptStackSize);
    LD_E_hl;
    INC_hl;
    LD_D(0);
    LD_HL(wScriptStack);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    POP_DE;
    LD_A_addr(wScriptBank);
    LD_hli_A;
    LD_A_addr(wScriptPos);
    LD_hli_A;
    LD_A_addr(wScriptPos + 1);
    LD_hl_A;
    LD_A_B;
    LD_addr_A(wScriptBank);
    LD_A_E;
    LD_addr_A(wScriptPos);
    LD_A_D;
    LD_addr_A(wScriptPos + 1);
    RET;

}

void CallCallback(void){
    LD_A_addr(wScriptBank);
    OR_A(0x80);
    LD_addr_A(wScriptBank);
    JP(mScriptCall);

}

void Script_sjump(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_A_addr(wScriptBank);
    LD_B_A;
    JP(mScriptJump);

}

void Script_farsjump(void){
    CALL(aGetScriptByte);
    LD_B_A;
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    JP(mScriptJump);

}

void Script_memjump(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_B_hl;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP(mScriptJump);

}

void Script_iffalse(void){
    LD_A_addr(wScriptVar);
    AND_A_A;
    JP_NZ (mSkipTwoScriptBytes);
    JP(mScript_sjump);

}

void Script_iftrue(void){
    LD_A_addr(wScriptVar);
    AND_A_A;
    JP_NZ (mScript_sjump);
    JP(mSkipTwoScriptBytes);

}

void Script_ifequal(void){
    CALL(aGetScriptByte);
    LD_HL(wScriptVar);
    CP_A_hl;
    JR_Z (mScript_sjump);
    JR(mSkipTwoScriptBytes);

}

void Script_ifnotequal(void){
    CALL(aGetScriptByte);
    LD_HL(wScriptVar);
    CP_A_hl;
    JR_NZ (mScript_sjump);
    JR(mSkipTwoScriptBytes);

}

void Script_ifgreater(void){
    LD_A_addr(wScriptVar);
    LD_B_A;
    CALL(aGetScriptByte);
    CP_A_B;
    JR_C (mScript_sjump);
    JR(mSkipTwoScriptBytes);

}

void Script_ifless(void){
    CALL(aGetScriptByte);
    LD_B_A;
    LD_A_addr(wScriptVar);
    CP_A_B;
    JR_C (mScript_sjump);
    JR(mSkipTwoScriptBytes);

}

void Script_jumpstd(void){
    CALL(aStdScript);
    JR(mScriptJump);

}

void Script_callstd(void){
    CALL(aStdScript);
    LD_D_H;
    LD_E_L;
    JP(mScriptCall);

}

void StdScript(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_HL(mStdScripts);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A(BANK(aStdScripts));
    CALL(aGetFarByte);
    LD_B_A;
    INC_HL;
    LD_A(BANK(aStdScripts));
    CALL(aGetFarWord);
    RET;

}

void SkipTwoScriptBytes(void){
    CALL(aGetScriptByte);
    CALL(aGetScriptByte);
    RET;

}

void ScriptJump(void){
    LD_A_B;
    LD_addr_A(wScriptBank);
    LD_A_L;
    LD_addr_A(wScriptPos);
    LD_A_H;
    LD_addr_A(wScriptPos + 1);
    RET;

}

void Script_sdefer(void){
    LD_A_addr(wScriptBank);
    LD_addr_A(wDeferredScriptBank);
    CALL(aGetScriptByte);
    LD_addr_A(wDeferredScriptAddr);
    CALL(aGetScriptByte);
    LD_addr_A(wDeferredScriptAddr + 1);
    LD_HL(wScriptFlags);
    SET_hl(3);
    RET;

}

void Script_checkscene(void){
    CALL(aCheckScenes);
    IF_Z goto no_scene;
    LD_addr_A(wScriptVar);
    RET;


no_scene:
    LD_A(0xff);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_checkmapscene(void){
    CALL(aGetScriptByte);
    LD_B_A;
    CALL(aGetScriptByte);
    LD_C_A;
    CALL(aGetMapSceneID);
    LD_A_D;
    OR_A_E;
    IF_Z goto no_scene;
    LD_A_de;
    LD_addr_A(wScriptVar);
    RET;


no_scene:
    LD_A(0xff);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_setscene(void){
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    JR(mDoScene);

}

void Script_setmapscene(void){
    CALL(aGetScriptByte);
    LD_B_A;
    CALL(aGetScriptByte);
    LD_C_A;
    return DoScene();
}

void DoScene(void){
    CALL(aGetMapSceneID);
    LD_A_D;
    OR_A_E;
    IF_Z goto no_scene;
    CALL(aGetScriptByte);
    LD_de_A;

no_scene:
    RET;

}

void Script_readmem(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_A_hl;
    LD_addr_A(wScriptVar);
    RET;

}

void Script_readmem_Conv(script_s* s, uint8_t* hl){
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_hl;
    // LD_addr_A(wScriptVar);
    // RET;
    s->var = *hl;
}

void Script_writemem(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_A_addr(wScriptVar);
    LD_hl_A;
    RET;

}

void Script_writemem_Conv(script_s* s, uint8_t* hl){
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_addr(wScriptVar);
    // LD_hl_A;
    // RET;
    *hl = s->var;
}

void Script_loadmem(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    CALL(aGetScriptByte);
    LD_hl_A;
    RET;

}

void Script_loadmem_Conv(script_s* s, uint8_t* hl, uint8_t val){
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // CALL(aGetScriptByte);
    // LD_hl_A;
    // RET;
    (void)s;
    *hl = val;
}

void Script_setval(void){
    CALL(aGetScriptByte);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_setval_Conv(script_s* s, uint8_t val){
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptVar);
    // RET;
    s->var = val;
}

void Script_addval(void){
    CALL(aGetScriptByte);
    LD_HL(wScriptVar);
    ADD_A_hl;
    LD_hl_A;
    RET;

}

void Script_addval_Conv(script_s* s, uint8_t val){
    // CALL(aGetScriptByte);
    // LD_HL(wScriptVar);
    // ADD_A_hl;
    // LD_hl_A;
    // RET;
    s->var += val;
}

void Script_random(void){
    CALL(aGetScriptByte);
    LD_addr_A(wScriptVar);
    AND_A_A;
    RET_Z ;

    LD_C_A;
    CALL(aScript_random_Divide256byC);
    AND_A_A;
    IF_Z goto no_restriction;  // 256 % b == 0
    LD_B_A;
    XOR_A_A;
    SUB_A_B;
    LD_B_A;

loop:
    PUSH_BC;
    CALL(aRandom);
    POP_BC;
    LDH_A_addr(hRandomAdd);
    CP_A_B;
    IF_NC goto loop;
    goto finish;


no_restriction:
    PUSH_BC;
    CALL(aRandom);
    POP_BC;
    LDH_A_addr(hRandomAdd);


finish:
    PUSH_AF;
    LD_A_addr(wScriptVar);
    LD_C_A;
    POP_AF;
    CALL(aSimpleDivide);
    LD_addr_A(wScriptVar);
    RET;


Divide256byC:
    XOR_A_A;
    LD_B_A;
    SUB_A_C;

mod_loop:
    INC_B;
    SUB_A_C;
    IF_NC goto mod_loop;
    DEC_B;
    ADD_A_C;
    RET;

}

void Script_readvar(void){
    CALL(aGetScriptByte);
    CALL(aGetVarAction);
    LD_A_de;
    LD_addr_A(wScriptVar);
    RET;

}

void Script_writevar(void){
    CALL(aGetScriptByte);
    CALL(aGetVarAction);
    LD_A_addr(wScriptVar);
    LD_de_A;
    RET;

}

void Script_loadvar(void){
    CALL(aGetScriptByte);
    CALL(aGetVarAction);
    CALL(aGetScriptByte);
    LD_de_A;
    RET;

}

void GetVarAction(void){
    LD_C_A;
    FARCALL(av_GetVarAction);
    RET;

}

void Script_checkver(void){
    LD_A_addr(mScript_checkver_gs_version);
    LD_addr_A(wScriptVar);
    RET;


gs_version:
    //db ['GS_VERSION'];

    return Script_getmonname();
}

void Script_getmonname(void){
    CALL(aGetScriptByte);
    AND_A_A;
    IF_NZ goto gotit;
    LD_A_addr(wScriptVar);

gotit:
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_DE(wStringBuffer1);

    return GetStringBuffer();
}

void GetStringBuffer(void){
    CALL(aGetScriptByte);
    CP_A(NUM_STRING_BUFFERS);
    IF_C goto ok;
    XOR_A_A;

ok:

    return CopyConvertedText();
}

void GetStringBuffer_Conv(uint8_t a, const uint8_t* de){
    // CALL(aGetScriptByte);
    // CP_A(NUM_STRING_BUFFERS);
    // IF_C goto ok;
    // XOR_A_A;
    if(a >= NUM_STRING_BUFFERS)
        return CopyConvertedText_Conv(0, de);

// ok:
    return CopyConvertedText_Conv(a, de);
}

void CopyConvertedText(void){
    LD_HL(wStringBuffer3);
    LD_BC(STRING_BUFFER_LENGTH);
    CALL(aAddNTimes);
    CALL(aCopyName2);
    RET;

}

void CopyConvertedText_Conv(uint8_t a, const uint8_t* de){
    // LD_HL(wStringBuffer3);
    // LD_BC(STRING_BUFFER_LENGTH);
    // CALL(aAddNTimes);
    uint8_t* hl = wram->wStringBuffer3 + (a * STRING_BUFFER_LENGTH);
    // CALL(aCopyName2);
    // RET;
    CopyName2_Conv2(hl, de);
}

void Script_getitemname(void){
    CALL(aGetScriptByte);
    AND_A_A;  // USE_SCRIPT_VAR
    IF_NZ goto ok;
    LD_A_addr(wScriptVar);

ok:
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    LD_DE(wStringBuffer1);
    JR(mGetStringBuffer);

}

void Script_getcurlandmarkname(void){
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetWorldMapLocation);

    return ConvertLandmarkToText();
}

void Script_getcurlandmarkname_Conv(script_s* s, uint8_t b){
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aGetWorldMapLocation);
    (void)s;
    uint8_t loc = GetWorldMapLocation_Conv(wram->wMapGroup, wram->wMapNumber);

    return ConvertLandmarkToText_Conv(loc, b);
}

void ConvertLandmarkToText(void){
    LD_E_A;
    FARCALL(aGetLandmarkName);
    LD_DE(wStringBuffer1);
    JP(mGetStringBuffer);

}

void ConvertLandmarkToText_Conv(uint8_t a, uint8_t b){
    // LD_E_A;
    // FARCALL(aGetLandmarkName);
    // LD_DE(wStringBuffer1);
    // JP(mGetStringBuffer);
    
    return GetStringBuffer_Conv(b, GetLandmarkName_Conv(a));
}

void Script_getlandmarkname(void){
    CALL(aGetScriptByte);
    JR(mConvertLandmarkToText);

}

void Script_getlandmarkname_Conv(script_s* s, uint8_t a, uint8_t b){
    // CALL(aGetScriptByte);
    // JR(mConvertLandmarkToText);
    (void)s;
    return ConvertLandmarkToText_Conv(a, b);
}

void Script_gettrainername(void){
    CALL(aGetScriptByte);
    LD_C_A;
    CALL(aGetScriptByte);
    LD_B_A;
    FARCALL(aGetTrainerName);
    JR(mGetStringBuffer);

}

void Script_gettrainername_Conv(script_s* s, uint8_t b, uint8_t c, uint8_t a){
    // CALL(aGetScriptByte);
    // LD_C_A;
    // CALL(aGetScriptByte);
    // LD_B_A;
    // FARCALL(aGetTrainerName);
    // JR(mGetStringBuffer);
    (void)s;
    return GetStringBuffer_Conv(a, GetTrainerName_Conv(b, c));
}

void Script_getname(void){
    CALL(aGetScriptByte);
    LD_addr_A(wNamedObjectType);

    return ContinueToGetName();
}

void ContinueToGetName(void){
    CALL(aGetScriptByte);
    LD_addr_A(wCurSpecies);
    CALL(aGetName);
    LD_DE(wStringBuffer1);
    JP(mGetStringBuffer);

}

void Script_gettrainerclassname(void){
    LD_A(TRAINER_NAME);
    LD_addr_A(wNamedObjectType);
    JR(mContinueToGetName);

}

void Script_getmoney(void){
    CALL(aResetStringBuffer1);
    CALL(aGetMoneyAccount);
    LD_HL(wStringBuffer1);
    LD_BC((PRINTNUM_LEFTALIGN | 3 << 8) | 6);
    CALL(aPrintNum);
    LD_DE(wStringBuffer1);
    JP(mGetStringBuffer);

}

void Script_getcoins(void){
    CALL(aResetStringBuffer1);
    LD_HL(wStringBuffer1);
    LD_DE(wCoins);
    LD_BC((PRINTNUM_LEFTALIGN | 2 << 8) | 6);
    CALL(aPrintNum);
    LD_DE(wStringBuffer1);
    JP(mGetStringBuffer);

}

void Script_getcoins_Conv(script_s* s, uint8_t a){
    (void)s;
    // CALL(aResetStringBuffer1);
    ResetStringBuffer1_Conv();
    // LD_HL(wStringBuffer1);
    // LD_DE(wCoins);
    // LD_BC((PRINTNUM_LEFTALIGN | 2 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum_Conv2(wram->wStringBuffer1, (uint8_t*)&wram->wCoins, (PRINTNUM_LEFTALIGN | 2), 6);
    // LD_DE(wStringBuffer1);
    // JP(mGetStringBuffer);
    return GetStringBuffer_Conv(a, wram->wStringBuffer1);
}

void Script_getnum(void){
    CALL(aResetStringBuffer1);
    LD_DE(wScriptVar);
    LD_HL(wStringBuffer1);
    LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 3);
    CALL(aPrintNum);
    LD_DE(wStringBuffer1);
    JP(mGetStringBuffer);

}

void Script_getnum_Conv(script_s* s, uint8_t a){
    // CALL(aResetStringBuffer1);
    ResetStringBuffer1_Conv();
    // LD_DE(wScriptVar);
    // LD_HL(wStringBuffer1);
    // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(wram->wStringBuffer1, &s->var, (PRINTNUM_LEFTALIGN | 1), 3);
    // LD_DE(wStringBuffer1);
    // JP(mGetStringBuffer);
    return GetStringBuffer_Conv(a, wram->wStringBuffer1);
}

void ResetStringBuffer1(void){
    LD_HL(wStringBuffer1);
    LD_BC(NAME_LENGTH);
    LD_A(0x50);
    CALL(aByteFill);
    RET;

}

void ResetStringBuffer1_Conv(void){
    // LD_HL(wStringBuffer1);
    // LD_BC(NAME_LENGTH);
    // LD_A(0x50);
    // CALL(aByteFill);
    // RET;
    return ByteFill_Conv(wStringBuffer1, NAME_LENGTH, 0x50);
}

void Script_getstring(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_A_addr(wScriptBank);
    LD_HL(mCopyName1);
    RST(aFarCall);
    LD_DE(wStringBuffer2);
    JP(mGetStringBuffer);

}

void Script_givepokemail(void){
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    LD_A_addr(wScriptBank);
    CALL(aGetFarByte);
    LD_B_A;
    PUSH_BC;
    INC_HL;
    LD_BC(MAIL_MSG_LENGTH);
    LD_DE(wMonMailMessageBuffer);
    LD_A_addr(wScriptBank);
    CALL(aFarCopyBytes);
    POP_BC;
    FARCALL(aGivePokeMail);
    RET;

}

void Script_checkpokemail(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_A_addr(wScriptBank);
    LD_B_A;
    FARCALL(aCheckPokeMail);
    RET;

}

void Script_giveitem(void){
    CALL(aGetScriptByte);
    CP_A(ITEM_FROM_MEM);
    IF_NZ goto ok;
    LD_A_addr(wScriptVar);

ok:
    LD_addr_A(wCurItem);
    CALL(aGetScriptByte);
    LD_addr_A(wItemQuantityChange);
    LD_HL(wNumItems);
    CALL(aReceiveItem);
    IF_NC goto full;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

full:
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;

}

void Script_takeitem(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    LD_addr_A(wCurItem);
    CALL(aGetScriptByte);
    LD_addr_A(wItemQuantityChange);
    LD_A(-1);
    LD_addr_A(wCurItemQuantity);
    LD_HL(wNumItems);
    CALL(aTossItem);
    RET_NC ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_checkitem(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    LD_addr_A(wCurItem);
    LD_HL(wNumItems);
    CALL(aCheckItem);
    RET_NC ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_checkitem_Conv(script_s* s, item_t item){
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    s->var = 0;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurItem);
    wram->wCurItem = item;
    // LD_HL(wNumItems);
    // CALL(aCheckItem);
    if(!CheckItem_Conv(item, wram->wItems))
        return;
    // RET_NC ;

    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    // RET;
    s->var = TRUE;
}

void Script_givemoney(void){
    CALL(aGetMoneyAccount);
    CALL(aLoadMoneyAmountToMem);
    FARCALL(aGiveMoney);
    RET;

}

void Script_takemoney(void){
    CALL(aGetMoneyAccount);
    CALL(aLoadMoneyAmountToMem);
    FARCALL(aTakeMoney);
    RET;

}

void Script_checkmoney(void){
    CALL(aGetMoneyAccount);
    CALL(aLoadMoneyAmountToMem);
    FARCALL(aCompareMoney);

    return CompareMoneyAction();
}

void CompareMoneyAction(void){
    IF_C goto less;
    IF_Z goto exact;
    LD_A(HAVE_MORE);
    goto done;

exact:
    LD_A(HAVE_AMOUNT);
    goto done;

less:
    LD_A(HAVE_LESS);

done:
    LD_addr_A(wScriptVar);
    RET;

}

void GetMoneyAccount(void){
    CALL(aGetScriptByte);
    AND_A_A;
    LD_DE(wMoney);  // YOUR_MONEY
    RET_Z ;
    LD_DE(wMomsMoney);  // MOMS_MONEY
    RET;

}

uint8_t* GetMoneyAccount_Conv(uint8_t a){
    // CALL(aGetScriptByte);
    // AND_A_A;
    // LD_DE(wMoney);  // YOUR_MONEY
    // RET_Z ;
    // LD_DE(wMomsMoney);  // MOMS_MONEY
    // RET;
    return (a == YOUR_MONEY)? wram->wMoney: wram->wMomsMoney;
}

void LoadMoneyAmountToMem(void){
    LD_BC(hMoneyTemp);
    PUSH_BC;
    CALL(aGetScriptByte);
    LD_bc_A;
    INC_BC;
    CALL(aGetScriptByte);
    LD_bc_A;
    INC_BC;
    CALL(aGetScriptByte);
    LD_bc_A;
    POP_BC;
    RET;

}

void LoadMoneyAmountToMem_Conv(uint32_t amount){
    // LD_BC(hMoneyTemp);
    // PUSH_BC;
    // CALL(aGetScriptByte);
    // LD_bc_A;
    hram->hMoneyTemp[0] = (uint8_t)(amount & 0xff);
    // INC_BC;
    // CALL(aGetScriptByte);
    // LD_bc_A;
    hram->hMoneyTemp[1] = (uint8_t)((amount >> 8) & 0xff);
    // INC_BC;
    // CALL(aGetScriptByte);
    // LD_bc_A;
    hram->hMoneyTemp[2] = (uint8_t)((amount >> 16) & 0xff);
    // POP_BC;
    // RET;
}

void Script_givecoins(void){
    CALL(aLoadCoinAmountToMem);
    FARCALL(aGiveCoins);
    RET;

}

void Script_takecoins(void){
    CALL(aLoadCoinAmountToMem);
    FARCALL(aTakeCoins);
    RET;

}

void Script_checkcoins(void){
    CALL(aLoadCoinAmountToMem);
    FARCALL(aCheckCoins);
    JR(mCompareMoneyAction);

}

void LoadCoinAmountToMem(void){
    CALL(aGetScriptByte);
    LDH_addr_A(hMoneyTemp + 1);
    CALL(aGetScriptByte);
    LDH_addr_A(hMoneyTemp);
    LD_BC(hMoneyTemp);
    RET;

}

void Script_checktime(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    FARCALL(aCheckTime);
    CALL(aGetScriptByte);
    AND_A_C;
    RET_Z ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_checkpoke(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    LD_HL(wPartySpecies);
    LD_DE(1);
    CALL(aIsInArray);
    RET_NC ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_addcellnum(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    LD_C_A;
    FARCALL(aAddPhoneNumber);
    RET_NC ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_delcellnum(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    LD_C_A;
    FARCALL(aDelCellNum);
    RET_NC ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_checkcellnum(void){
//  returns false if the cell number is not in your phone

    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    LD_C_A;
    FARCALL(aCheckCellNum);
    RET_NC ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_specialphonecall(void){
    CALL(aGetScriptByte);
    LD_addr_A(wSpecialPhoneCallID);
    CALL(aGetScriptByte);
    LD_addr_A(wSpecialPhoneCallID + 1);
    RET;

}

void Script_checkphonecall(void){
//  returns false if no special phone call is stored

    LD_A_addr(wSpecialPhoneCallID);
    AND_A_A;
    IF_Z goto ok;
    LD_A(TRUE);

ok:
    LD_addr_A(wScriptVar);
    RET;

}

void Script_givepoke(void){
    CALL(aGetScriptByte);
    LD_addr_A(wCurPartySpecies);
    CALL(aGetScriptByte);
    LD_addr_A(wCurPartyLevel);
    CALL(aGetScriptByte);
    LD_addr_A(wCurItem);
    CALL(aGetScriptByte);
    AND_A_A;
    LD_B_A;
    IF_Z goto ok;
    LD_HL(wScriptPos);
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALL(aGetScriptByte);
    CALL(aGetScriptByte);
    CALL(aGetScriptByte);
    CALL(aGetScriptByte);

ok:
    FARCALL(aGivePoke);
    LD_A_B;
    LD_addr_A(wScriptVar);
    RET;

}

void Script_giveegg(void){
//  if no room in the party, return 0 in wScriptVar

    XOR_A_A;  // PARTYMON
    LD_addr_A(wScriptVar);
    LD_addr_A(wMonType);
    CALL(aGetScriptByte);
    LD_addr_A(wCurPartySpecies);
    CALL(aGetScriptByte);
    LD_addr_A(wCurPartyLevel);
    FARCALL(aGiveEgg);
    RET_NC ;
    LD_A(2);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_setevent(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_B(SET_FLAG);
    CALL(aEventFlagAction);
    RET;

}

void Script_clearevent(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_B(RESET_FLAG);
    CALL(aEventFlagAction);
    RET;

}

void Script_checkevent(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_B(CHECK_FLAG);
    CALL(aEventFlagAction);
    LD_A_C;
    AND_A_A;
    IF_Z goto false_;
    LD_A(TRUE);

false_:
    LD_addr_A(wScriptVar);
    RET;

}

void Script_setflag(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_B(SET_FLAG);
    CALL(av_EngineFlagAction);
    RET;

}

void Script_setflag_Conv(script_s* s, uint16_t flag){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_B(SET_FLAG);
    // CALL(av_EngineFlagAction);
    // RET;
    v_EngineFlagAction_Conv(flag, SET_FLAG);
}

void Script_clearflag(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_B(RESET_FLAG);
    CALL(av_EngineFlagAction);
    RET;

}

void Script_clearflag_Conv(script_s* s, uint16_t flag){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_B(RESET_FLAG);
    // CALL(av_EngineFlagAction);
    // RET;
    v_EngineFlagAction_Conv(flag, RESET_FLAG);
}

void Script_checkflag(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_B(CHECK_FLAG);
    CALL(av_EngineFlagAction);
    LD_A_C;
    AND_A_A;
    IF_Z goto false_;
    LD_A(TRUE);

false_:
    LD_addr_A(wScriptVar);
    RET;

}

void Script_checkflag_Conv(script_s* s, uint16_t flag){
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_B(CHECK_FLAG);
    // CALL(av_EngineFlagAction);
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto false_;
    // LD_A(TRUE);

// false_:
    // LD_addr_A(wScriptVar);
    // RET;
    s->var = (v_EngineFlagAction_Conv(flag, CHECK_FLAG))? TRUE: FALSE;
}

void v_EngineFlagAction(void){
    FARCALL(aEngineFlagAction);
    RET;

}

bool v_EngineFlagAction_Conv(uint16_t de, uint8_t b){
    // FARCALL(aEngineFlagAction);
    // RET;
    return EngineFlagAction_Conv(de, b);
}

void Script_wildoff(void){
    // LD_HL(wStatusFlags);
    // SET_hl(STATUSFLAGS_NO_WILD_ENCOUNTERS_F);
    // RET;
    wram->wStatusFlags |= (1 << STATUSFLAGS_NO_WILD_ENCOUNTERS_F);
}

void Script_wildon(void){
    // LD_HL(wStatusFlags);
    // RES_hl(STATUSFLAGS_NO_WILD_ENCOUNTERS_F);
    // RET;
    wram->wStatusFlags &= (1 << STATUSFLAGS_NO_WILD_ENCOUNTERS_F) ^ 0xff;
}

void Script_xycompare(void){
    CALL(aGetScriptByte);
    LD_addr_A(wXYComparePointer);
    CALL(aGetScriptByte);
    LD_addr_A(wXYComparePointer + 1);
    RET;

}

void Script_warpfacing(void){
    CALL(aGetScriptByte);
    maskbits(NUM_DIRECTIONS, 0);
    LD_C_A;
    LD_A_addr(wPlayerSpriteSetupFlags);
    SET_A(PLAYERSPRITESETUP_CUSTOM_FACING_F);
    OR_A_C;
    LD_addr_A(wPlayerSpriteSetupFlags);
//  fallthrough

    return Script_warp();
}

void Script_warp(void){
//  This seems to be some sort of error handling case.
    CALL(aGetScriptByte);
    AND_A_A;
    IF_Z goto not_ok;
    LD_addr_A(wMapGroup);
    CALL(aGetScriptByte);
    LD_addr_A(wMapNumber);
    CALL(aGetScriptByte);
    LD_addr_A(wXCoord);
    CALL(aGetScriptByte);
    LD_addr_A(wYCoord);
    LD_A(SPAWN_N_A);
    LD_addr_A(wDefaultSpawnpoint);
    LD_A(MAPSETUP_WARP);
    LDH_addr_A(hMapEntryMethod);
    LD_A(MAPSTATUS_ENTER);
    CALL(aLoadMapStatus);
    CALL(aStopScript);
    RET;


not_ok:
    CALL(aGetScriptByte);
    CALL(aGetScriptByte);
    CALL(aGetScriptByte);
    LD_A(SPAWN_N_A);
    LD_addr_A(wDefaultSpawnpoint);
    LD_A(MAPSETUP_BADWARP);
    LDH_addr_A(hMapEntryMethod);
    LD_A(MAPSTATUS_ENTER);
    CALL(aLoadMapStatus);
    CALL(aStopScript);
    RET;

}

void Script_warpmod(void){
    CALL(aGetScriptByte);
    LD_addr_A(wBackupWarpNumber);
    CALL(aGetScriptByte);
    LD_addr_A(wBackupMapGroup);
    CALL(aGetScriptByte);
    LD_addr_A(wBackupMapNumber);
    RET;

}

void Script_blackoutmod(void){
    CALL(aGetScriptByte);
    LD_addr_A(wLastSpawnMapGroup);
    CALL(aGetScriptByte);
    LD_addr_A(wLastSpawnMapNumber);
    RET;

}

void Script_dontrestartmapmusic(void){
    LD_A(TRUE);
    LD_addr_A(wDontPlayMapMusicOnReload);
    RET;

}

void Script_writecmdqueue(void){
    CALL(aGetScriptByte);
    LD_E_A;
    CALL(aGetScriptByte);
    LD_D_A;
    LD_A_addr(wScriptBank);
    LD_B_A;
    FARCALL(aWriteCmdQueue);  // no need to farcall
    RET;

}

void Script_delcmdqueue(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aGetScriptByte);
    LD_B_A;
    FARCALL(aDelCmdQueue);  // no need to farcall
    RET_C ;
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;

}

void Script_changemapblocks(void){
    CALL(aGetScriptByte);
    LD_addr_A(wMapBlocksBank);
    CALL(aGetScriptByte);
    LD_addr_A(wMapBlocksPointer);
    CALL(aGetScriptByte);
    LD_addr_A(wMapBlocksPointer + 1);
    CALL(aChangeMap);
    CALL(aBufferScreen);
    RET;

}

void Script_changeblock(void){
    CALL(aGetScriptByte);
    ADD_A(4);
    LD_D_A;
    CALL(aGetScriptByte);
    ADD_A(4);
    LD_E_A;
    CALL(aGetBlockLocation);
    CALL(aGetScriptByte);
    LD_hl_A;
    CALL(aBufferScreen);
    RET;

}

void Script_reloadmappart(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aOverworldTextModeSwitch);
    CALL(aGetMovementPermissions);
    FARCALL(aReloadMapPart);
    CALL(aUpdateSprites);
    RET;

}

void Script_warpcheck(void){
    CALL(aWarpCheck);
    RET_NC ;
    FARCALL(aEnableEvents);
    RET;

}

void Script_enableevents(void){
//  //  unreferenced
    FARCALL(aEnableEvents);
    RET;

}

void Script_newloadmap(void){
    CALL(aGetScriptByte);
    LDH_addr_A(hMapEntryMethod);
    LD_A(MAPSTATUS_ENTER);
    CALL(aLoadMapStatus);
    CALL(aStopScript);
    RET;

}

void Script_reloadend(void){
    CALL(aScript_newloadmap);
    JP(mScript_end);

}

void Script_opentext(void){
    CALL(aOpenText);
    RET;

}

void Script_opentext_Conv(script_s* s){
    (void)s;
    CALL(aOpenText);
    // RET;
}

void Script_refreshscreen(void){
    CALL(aRefreshScreen);
    CALL(aGetScriptByte);
    RET;

}

void Script_writeunusedbyte(void){
    CALL(aGetScriptByte);
    LD_addr_A(wUnusedScriptByte);
    RET;

}

void UnusedClosetextScript(void){
//  //  unreferenced
    //closetext ['?']

    return Script_closetext();
}

void Script_closetext(void){
    CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    CALL(aCloseText);
    RET;

}

void Script_closetext_Conv(script_s* s){
    (void)s;
    CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    CALL(aCloseText);
    // RET;
}

void Script_autoinput(void){
    CALL(aGetScriptByte);
    PUSH_AF;
    CALL(aGetScriptByte);
    LD_L_A;
    CALL(aGetScriptByte);
    LD_H_A;
    POP_AF;
    CALL(aStartAutoInput);
    RET;

}

void Script_pause(void){
    CALL(aGetScriptByte);
    AND_A_A;
    IF_Z goto loop;
    LD_addr_A(wScriptDelay);

loop:
    LD_C(2);
    CALL(aDelayFrames);
    LD_HL(wScriptDelay);
    DEC_hl;
    IF_NZ goto loop;
    RET;

}

void Script_deactivatefacing(void){
    CALL(aGetScriptByte);
    AND_A_A;
    IF_Z goto no_time;
    LD_addr_A(wScriptDelay);

no_time:
    LD_A(SCRIPT_WAIT);
    LD_addr_A(wScriptMode);
    CALL(aStopScript);
    RET;

}

void Script_stopandsjump(void){
    CALL(aStopScript);
    JP(mScript_sjump);

}

void Script_end(void){
    CALL(aExitScriptSubroutine);
    IF_C goto resume;
    RET;


resume:
    XOR_A_A;
    LD_addr_A(wScriptRunning);
    LD_A(SCRIPT_OFF);
    LD_addr_A(wScriptMode);
    LD_HL(wScriptFlags);
    RES_hl(0);
    CALL(aStopScript);
    RET;

}

void Script_endcallback(void){
    CALL(aExitScriptSubroutine);
    IF_C goto dummy;

dummy:
    LD_HL(wScriptFlags);
    RES_hl(0);
    CALL(aStopScript);
    RET;

}

void ExitScriptSubroutine(void){
//  Return carry if there's no parent to return to.

    LD_HL(wScriptStackSize);
    LD_A_hl;
    AND_A_A;
    IF_Z goto done;
    DEC_hl;
    LD_E_hl;
    LD_D(0x0);
    LD_HL(wScriptStack);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_B_A;
    AND_A(0x7f);
    LD_addr_A(wScriptBank);
    LD_A_hli;
    LD_E_A;
    LD_addr_A(wScriptPos);
    LD_A_hl;
    LD_D_A;
    LD_addr_A(wScriptPos + 1);
    AND_A_A;
    RET;

done:
    SCF;
    RET;

}

void Script_endall(void){
    XOR_A_A;
    LD_addr_A(wScriptStackSize);
    LD_addr_A(wScriptRunning);
    LD_A(SCRIPT_OFF);
    LD_addr_A(wScriptMode);
    LD_HL(wScriptFlags);
    RES_hl(0);
    CALL(aStopScript);
    RET;

}

void Script_halloffame(void){
    LD_HL(wGameTimerPaused);
    RES_hl(GAME_TIMER_PAUSED_F);
    FARCALL(aStubbedTrainerRankings_HallOfFame);
    FARCALL(aStubbedTrainerRankings_HallOfFame2);
    FARCALL(aHallOfFame);
    LD_HL(wGameTimerPaused);
    SET_hl(GAME_TIMER_PAUSED_F);
    JR(mReturnFromCredits);

}

void Script_credits(void){
    FARCALL(aRedCredits);
    return ReturnFromCredits();
}

void ReturnFromCredits(void){
    CALL(aScript_endall);
    LD_A(MAPSTATUS_DONE);
    CALL(aLoadMapStatus);
    CALL(aStopScript);
    RET;

}

void Script_wait(void){
    PUSH_BC;
    CALL(aGetScriptByte);

loop:
    PUSH_AF;
    LD_C(6);
    CALL(aDelayFrames);
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    POP_BC;
    RET;

}

void Script_checksave(void){
    FARCALL(aCheckSave);
    LD_A_C;
    LD_addr_A(wScriptVar);
    RET;

}

void Script_checkver_duplicate(void){
//  //  unreferenced
    LD_A_addr(mScript_checkver_duplicate_gs_version);
    LD_addr_A(wScriptVar);
    RET;


//gs_version:
    //db ['GS_VERSION'];

}