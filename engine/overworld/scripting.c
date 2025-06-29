#include "../../constants.h"
#include "../../util/scripting.h"
#include "../../audio/engine.h"
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/print_text.h"
#include "../../home/copy_name.h"
#include "../../home/flag.h"
#include "../../home/math.h"
#include "../../home/map.h"
#include "../../home/names.h"
#include "../../home/item.h"
#include "../../home/map_objects.h"
#include "../../home/pokemon.h"
#include "../../home/random.h"
#include "../../home/joypad.h"
#include "../../home/tilemap.h"
#include "../../home/window.h"
#include "../../home/trainers.h"
#include "../../home/text.h"
#include "../battle/core.h"
#include "../battle/read_trainer_party.h"
#include "../events/engine_flags.h"
#include "../events/catch_tutorial.h"
#include "../events/checktime.h"
#include "../events/money.h"
#include "../events/pokepic.h"
#include "../events/fruit_trees.h"
#include "../events/whiteout.h"
#include "../events/mom_phone.h"
#include "../events/checksave.h"
#include "../events/npc_trade.h"
#include "../events/elevator.h"
#include "../events/halloffame.h"
#include "../events/battle_tower/trainer_text.h"
#include "events.h"
#include "variables.h"
#include "landmarks.h"
#include "overworld.h"
#include "map_objects.h"
#include "player_object.h"
#include "tile_events.h"
#include "decorations.h"
#include "../events/specials.h"
#include "../items/items.h"
#include "../items/mart.h"
#include "../pokemon/move_mon.h"
#include "../pokemon/mail.h"
#include "../../data/text/common.h"
#include "../../data/items/pocket_names.h"
#include "../events/std_scripts.h"
#include "../../home/menu.h"
#include "../phone/phone.h"
#include "../gfx/dma_transfer.h"
#include "../../mobile/mobile_41.h"
#include <assert.h>

static const struct TextCmd* lScriptText = NULL;
Script_fn_t gDeferredScriptAddr = NULL;

static void StartScript(void);
static bool CheckScript(void);
static void StopScript(void);

static uint8_t GetScriptObject(uint8_t a);
static void ApplyMovement(uint8_t c, const uint8_t* hl);
static bool ApplyObjectFacing(uint8_t d, uint8_t e);
static bool ApplyEventActionAppearDisappear(uint8_t mapObjIdx, uint8_t b);
static Script_fn_t StdScript(uint16_t std);
static void DoScene(uint8_t group, uint8_t map, uint8_t scene);
static uint8_t* GetVarAction(uint8_t a);
static void GetStringBuffer(uint8_t a, const uint8_t* de);
static void CopyConvertedText(uint8_t a, const uint8_t* de);
static void ConvertLandmarkToText(uint8_t a, uint8_t b);
static void ResetStringBuffer1(void);
static void CompareMoneyAction(script_s* s, u8_flag_s res);
static uint8_t* GetMoneyAccount(uint8_t a);
static uint8_t* LoadMoneyAmountToMem(uint32_t amount);
static uint8_t* LoadCoinAmountToMem(uint16_t amount);
static bool v_EngineFlagAction(uint16_t de, uint8_t b);

static bool ExitScriptSubroutine(script_s* s);

//  Event scripting commands.

void EnableScriptMode(void){
    // PUSH_AF;
    // LD_A(SCRIPT_READ);
    // LD_addr_A(wScriptMode);
    // POP_AF;
    wram->wScriptMode = SCRIPT_READ;
    // RET;
}

void ScriptEvents(void){
    // CALL(aStartScript);
    StartScript();

    bool wait = false;
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
            case SCRIPT_OFF: StopScript(); DelayFrame(); break;
            case SCRIPT_READ: wait = gCurScript.fn(&gCurScript); if(wait) DelayFrame(); break;
            case SCRIPT_WAIT_MOVEMENT: WaitScriptMovement(); DelayFrame(); break;
            case SCRIPT_WAIT: WaitScript(); DelayFrame(); break;
        }
        // CALL(aCheckScript);
        // IF_NZ goto loop;
    } while(CheckScript());
    // RET;
}

void EndScript(void){
    // CALL(aStopScript);
    StopScript();
    // RET;
}

void WaitScript(void){
    // CALL(aStopScript);
    StopScript();

    // LD_HL(wScriptDelay);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wScriptDelay != 0) {
        // RET;
        return;
    }

    // FARCALL(aUnfreezeAllObjects);
    UnfreezeAllObjects();

    // LD_A(SCRIPT_READ);
    // LD_addr_A(wScriptMode);
    wram->wScriptMode = SCRIPT_READ;
    // CALL(aStartScript);
    StartScript();
    // RET;
}

void WaitScriptMovement(void){
    // CALL(aStopScript);
    StopScript();

    // LD_HL(wVramState);
    // BIT_hl(7);
    // RET_NZ ;
    if(bit_test(wram->wVramState, 7))
        return;

    // FARCALL(aUnfreezeAllObjects);
    UnfreezeAllObjects();

    // LD_A(SCRIPT_READ);
    // LD_addr_A(wScriptMode);
    wram->wScriptMode = SCRIPT_READ;
    // CALL(aStartScript);
    StartScript();
    // RET;
}

#include "../../macros/scripts/events.h"

void RunScriptCommand(void){
    // CALL(aGetScriptByte);
    // LD_HL(mScriptCommandTable);
    // RST(aJumpTable);
    // switch(REG_A)
    // {
    //     case CMD_SCALL: CALL(aScript_scall); break; // $00
    //     case CMD_FARSCALL: CALL(aScript_farscall); break; // $01
    //     case CMD_MEMCALL: CALL(aScript_memcall); break; // $02
    //     case CMD_SJUMP: CALL(aScript_sjump); break; // $03
    //     case CMD_FARSJUMP: CALL(aScript_farsjump); break; // $04
    //     case CMD_MEMJUMP: CALL(aScript_memjump); break; // $05
    //     case CMD_IFEQUAL: CALL(aScript_ifequal); break; // $06
    //     case CMD_IFNOTEQUAL: CALL(aScript_ifnotequal); break; // $07
    //     case CMD_IFFALSE: CALL(aScript_iffalse); break; // $08
    //     case CMD_IFTRUE: CALL(aScript_iftrue); break; // $09
    //     case CMD_IFGREATER: CALL(aScript_ifgreater); break; // $0a
    //     case CMD_IFLESS: CALL(aScript_ifless); break; // $0b
    //     case CMD_JUMPSTD: CALL(aScript_jumpstd); break; // $0c
    //     case CMD_CALLSTD: CALL(aScript_callstd); break; // $0d
    //     case CMD_CALLASM: CALL(aScript_callasm); break; // $0e
    //     case CMD_SPECIAL: CALL(aScript_special); break; // $0f
    //     case CMD_MEMCALLASM: CALL(aScript_memcallasm); break; // $10
    //     case CMD_CHECKMAPSCENE: CALL(aScript_checkmapscene); break; // $11
    //     case CMD_SETMAPSCENE: CALL(aScript_setmapscene); break; // $12
    //     case CMD_CHECKSCENE: CALL(aScript_checkscene); break; // $13
    //     case CMD_SETSCENE: CALL(aScript_setscene); break; // $14
    //     case CMD_SETVAL: CALL(aScript_setval); break; // $15
    //     case CMD_ADDVAL: CALL(aScript_addval); break; // $16
    //     case CMD_RANDOM: CALL(aScript_random); break; // $17
    //     case CMD_CHECKVER: CALL(aScript_checkver); break; // $18
    //     case CMD_READMEM: CALL(aScript_readmem); break; // $19
    //     case CMD_WRITEMEM: CALL(aScript_writemem); break; // $1a
    //     case CMD_LOADMEM: CALL(aScript_loadmem); break; // $1b
    //     case CMD_READVAR: CALL(aScript_readvar); break; // $1c
    //     case CMD_WRITEVAR: CALL(aScript_writevar); break; // $1d
    //     case CMD_LOADVAR: CALL(aScript_loadvar); break; // $1e
    //     case CMD_GIVEITEM: CALL(aScript_giveitem); break; // $1f
    //     case CMD_TAKEITEM: CALL(aScript_takeitem); break; // $20
    //     case CMD_CHECKITEM: CALL(aScript_checkitem); break; // $21
    //     case CMD_GIVEMONEY: CALL(aScript_givemoney); break; // $22
    //     case CMD_TAKEMONEY: CALL(aScript_takemoney); break; // $23
    //     case CMD_CHECKMONEY: CALL(aScript_checkmoney); break; // $24
    //     case CMD_GIVECOINS: CALL(aScript_givecoins); break; // $25
    //     case CMD_TAKECOINS: CALL(aScript_takecoins); break; // $26
    //     case CMD_CHECKCOINS: CALL(aScript_checkcoins); break; // $27
    //     case CMD_ADDCELLNUM: CALL(aScript_addcellnum); break; // $28
    //     case CMD_DELCELLNUM: CALL(aScript_delcellnum); break; // $29
    //     case CMD_CHECKCELLNUM: CALL(aScript_checkcellnum); break; // $2a
    //     case CMD_CHECKTIME: CALL(aScript_checktime); break; // $2b
    //     case CMD_CHECKPOKE: CALL(aScript_checkpoke); break; // $2c
    //     case CMD_GIVEPOKE: CALL(aScript_givepoke); break; // $2d
    //     case CMD_GIVEEGG: CALL(aScript_giveegg); break; // $2e
    //     case CMD_GIVEPOKEMAIL: CALL(aScript_givepokemail); break; // $2f
    //     case CMD_CHECKPOKEMAIL: CALL(aScript_checkpokemail); break; // $30
    //     case CMD_CHECKEVENT: CALL(aScript_checkevent); break; // $31
    //     case CMD_CLEAREVENT: CALL(aScript_clearevent); break; // $32
    //     case CMD_SETEVENT: CALL(aScript_setevent); break; // $33
    //     case CMD_CHECKFLAG: CALL(aScript_checkflag); break; // $34
    //     case CMD_CLEARFLAG: CALL(aScript_clearflag); break; // $35
    //     case CMD_SETFLAG: CALL(aScript_setflag); break; // $36
    //     case CMD_WILDON: CALL(aScript_wildon); break; // $37
    //     case CMD_WILDOFF: CALL(aScript_wildoff); break; // $38
    //     case CMD_XYCOMPARE: CALL(aScript_xycompare); break; // $39
    //     case CMD_WARPMOD: CALL(aScript_warpmod); break; // $3a
    //     case CMD_BLACKOUTMOD: CALL(aScript_blackoutmod); break; // $3b
    //     case CMD_WARP: CALL(aScript_warp); break; // $3c
    //     case CMD_GETMONEY: CALL(aScript_getmoney); break; // $3d
    //     case CMD_GETCOINS: CALL(aScript_getcoins); break; // $3e
    //     case CMD_GETNUM: CALL(aScript_getnum); break; // $3f
    //     case CMD_GETMONNAME: CALL(aScript_getmonname); break; // $40
    //     case CMD_GETITEMNAME: CALL(aScript_getitemname); break; // $41
    //     case CMD_GETCURLANDMARKNAME: CALL(aScript_getcurlandmarkname); break; // $42
    //     case CMD_GETTRAINERNAME: CALL(aScript_gettrainername); break; // $43
    //     case CMD_GETSTRING: CALL(aScript_getstring); break; // $44
    //     case CMD_ITEMNOTIFY: CALL(aScript_itemnotify); break; // $45
    //     case CMD_POCKETISFULL: CALL(aScript_pocketisfull); break; // $46
    //     case CMD_OPENTEXT: CALL(aScript_opentext); break; // $47
    //     case CMD_REFRESHSCREEN: CALL(aScript_refreshscreen); break; // $48
    //     case CMD_CLOSETEXT: CALL(aScript_closetext); break; // $49
    //     case CMD_WRITEUNUSEDBYTE: CALL(aScript_writeunusedbyte); break; // $4a
    //     case CMD_FARWRITETEXT: CALL(aScript_farwritetext); break; // $4b
    //     case CMD_WRITETEXT: CALL(aScript_writetext); break; // $4c
    //     case CMD_REPEATTEXT: CALL(aScript_repeattext); break; // $4d
    //     case CMD_YESORNO: CALL(aScript_yesorno); break; // $4e
    //     case CMD_LOADMENU: CALL(aScript_loadmenu); break; // $4f
    //     case CMD_CLOSEWINDOW: CALL(aScript_closewindow); break; // $50
    //     case CMD_JUMPTEXTFACEPLAYER: CALL(aScript_jumptextfaceplayer); break; // $51
    //     case CMD_FARJUMPTEXT: CALL(aScript_farjumptext); break; // $52
    //     case CMD_JUMPTEXT: CALL(aScript_jumptext); break; // $53
    //     case CMD_WAITBUTTON: CALL(aScript_waitbutton); break; // $54
    //     case CMD_PROMPTBUTTON: CALL(aScript_promptbutton); break; // $55
    //     case CMD_POKEPIC: CALL(aScript_pokepic); break; // $56
    //     case CMD_CLOSEPOKEPIC: CALL(aScript_closepokepic); break; // $57
    //     case CMD__2DMENU: CALL(aScript__2dmenu); break; // $58
    //     case CMD_VERTICALMENU: CALL(aScript_verticalmenu); break; // $59
    //     case CMD_LOADPIKACHUDATA: CALL(aScript_loadpikachudata); break; // $5a
    //     case CMD_RANDOMWILDMON: CALL(aScript_randomwildmon); break; // $5b
    //     case CMD_LOADTEMPTRAINER: CALL(aScript_loadtemptrainer); break; // $5c
    //     case CMD_LOADWILDMON: CALL(aScript_loadwildmon); break; // $5d
    //     case CMD_LOADTRAINER: CALL(aScript_loadtrainer); break; // $5e
    //     case CMD_STARTBATTLE: CALL(aScript_startbattle); break; // $5f
    //     case CMD_RELOADMAPAFTERBATTLE: CALL(aScript_reloadmapafterbattle); break; // $60
    //     case CMD_CATCHTUTORIAL: CALL(aScript_catchtutorial); break; // $61
    //     case CMD_TRAINERTEXT: CALL(aScript_trainertext); break; // $62
    //     case CMD_TRAINERFLAGACTION: CALL(aScript_trainerflagaction); break; // $63
    //     case CMD_WINLOSSTEXT: CALL(aScript_winlosstext); break; // $64
    //     case CMD_SCRIPTTALKAFTER: CALL(aScript_scripttalkafter); break; // $65
    //     case CMD_ENDIFJUSTBATTLED: CALL(aScript_endifjustbattled); break; // $66
    //     case CMD_CHECKJUSTBATTLED: CALL(aScript_checkjustbattled); break; // $67
    //     case CMD_SETLASTTALKED: CALL(aScript_setlasttalked); break; // $68
    //     case CMD_APPLYMOVEMENT: CALL(aScript_applymovement); break; // $69
    //     case CMD_APPLYMOVEMENTLASTTALKED: CALL(aScript_applymovementlasttalked); break; // $6a
    //     case CMD_FACEPLAYER: CALL(aScript_faceplayer); break; // $6b
    //     case CMD_FACEOBJECT: CALL(aScript_faceobject); break; // $6c
    //     case CMD_VARIABLESPRITE: CALL(aScript_variablesprite); break; // $6d
    //     case CMD_DISAPPEAR: CALL(aScript_disappear); break; // $6e
    //     case CMD_APPEAR: CALL(aScript_appear); break; // $6f
    //     case CMD_FOLLOW: CALL(aScript_follow); break; // $70
    //     case CMD_STOPFOLLOW: CALL(aScript_stopfollow); break; // $71
    //     case CMD_MOVEOBJECT: CALL(aScript_moveobject); break; // $72
    //     case CMD_WRITEOBJECTXY: CALL(aScript_writeobjectxy); break; // $73
    //     case CMD_LOADEMOTE: CALL(aScript_loademote); break; // $74
    //     case CMD_SHOWEMOTE: CALL(aScript_showemote); break; // $75
    //     case CMD_TURNOBJECT: CALL(aScript_turnobject); break; // $76
    //     case CMD_FOLLOWNOTEXACT: CALL(aScript_follownotexact); break; // $77
    //     case CMD_EARTHQUAKE: CALL(aScript_earthquake); break; // $78
    //     case CMD_CHANGEMAPBLOCKS: CALL(aScript_changemapblocks); break; // $79
    //     case CMD_CHANGEBLOCK: CALL(aScript_changeblock); break; // $7a
    //     case CMD_RELOADMAP: CALL(aScript_reloadmap); break; // $7b
    //     case CMD_RELOADMAPPART: CALL(aScript_reloadmappart); break; // $7c
    //     case CMD_WRITECMDQUEUE: CALL(aScript_writecmdqueue); break; // $7d
    //     case CMD_DELCMDQUEUE: CALL(aScript_delcmdqueue); break; // $7e
    //     case CMD_PLAYMUSIC: CALL(aScript_playmusic); break; // $7f
    //     case CMD_ENCOUNTERMUSIC: CALL(aScript_encountermusic); break; // $80
    //     case CMD_MUSICFADEOUT: CALL(aScript_musicfadeout); break; // $81
    //     case CMD_PLAYMAPMUSIC: CALL(aScript_playmapmusic); break; // $82
    //     case CMD_DONTRESTARTMAPMUSIC: CALL(aScript_dontrestartmapmusic); break; // $83
    //     case CMD_CRY: CALL(aScript_cry); break; // $84
    //     case CMD_PLAYSOUND: CALL(aScript_playsound); break; // $85
    //     case CMD_WAITSFX: CALL(aScript_waitsfx); break; // $86
    //     case CMD_WARPSOUND: CALL(aScript_warpsound); break; // $87
    //     case CMD_SPECIALSOUND: CALL(aScript_specialsound); break; // $88
    //     case CMD_AUTOINPUT: CALL(aScript_autoinput); break; // $89
    //     case CMD_NEWLOADMAP: CALL(aScript_newloadmap); break; // $8a
    //     case CMD_PAUSE: CALL(aScript_pause); break; // $8b
    //     case CMD_DEACTIVATEFACING: CALL(aScript_deactivatefacing); break; // $8c
    //     case CMD_SDEFER: CALL(aScript_sdefer); break; // $8d
    //     case CMD_WARPCHECK: CALL(aScript_warpcheck); break; // $8e
    //     case CMD_STOPANDSJUMP: CALL(aScript_stopandsjump); break; // $8f
    //     case CMD_ENDCALLBACK: CALL(aScript_endcallback); break; // $90
    //     case CMD_END: CALL(aScript_end); break; // $91
    //     case CMD_RELOADEND: CALL(aScript_reloadend); break; // $92
    //     case CMD_ENDALL: CALL(aScript_endall); break; // $93
    //     case CMD_POKEMART: CALL(aScript_pokemart); break; // $94
    //     case CMD_ELEVATOR: CALL(aScript_elevator); break; // $95
    //     case CMD_TRADE: CALL(aScript_trade); break; // $96
    //     case CMD_ASKFORPHONENUMBER: CALL(aScript_askforphonenumber); break; // $97
    //     case CMD_PHONECALL: CALL(aScript_phonecall); break; // $98
    //     case CMD_HANGUP: CALL(aScript_hangup); break; // $99
    //     case CMD_DESCRIBEDECORATION: CALL(aScript_describedecoration); break; // $9a
    //     case CMD_FRUITTREE: CALL(aScript_fruittree); break; // $9b
    //     case CMD_SPECIALPHONECALL: CALL(aScript_specialphonecall); break; // $9c
    //     case CMD_CHECKPHONECALL: CALL(aScript_checkphonecall); break; // $9d
    //     case CMD_VERBOSEGIVEITEM: CALL(aScript_verbosegiveitem); break; // $9e
    //     case CMD_VERBOSEGIVEITEMVAR: CALL(aScript_verbosegiveitemvar); break; // $9f
    //     case CMD_SWARM: CALL(aScript_swarm); break; // $a0
    //     case CMD_HALLOFFAME: CALL(aScript_halloffame); break; // $a1
    //     case CMD_CREDITS: CALL(aScript_credits); break; // $a2
    //     case CMD_WARPFACING: CALL(aScript_warpfacing); break; // $a3
    //     case CMD_BATTLETOWERTEXT: CALL(aScript_battletowertext); break; // $a4
    //     case CMD_GETLANDMARKNAME: CALL(aScript_getlandmarkname); break; // $a5
    //     case CMD_GETTRAINERCLASSNAME: CALL(aScript_gettrainerclassname); break; // $a6
    //     case CMD_GETNAME: CALL(aScript_getname); break; // $a7
    //     case CMD_WAIT: CALL(aScript_wait); break; // $a8
    //     case CMD_CHECKSAVE: CALL(aScript_checksave); break; // $a9
    // }
    // RET;

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
}

static void StartScript(void){
    // LD_HL(wScriptFlags);
    // SET_hl(SCRIPT_RUNNING);
    // RET;
    bit_set(wram->wScriptFlags, SCRIPT_RUNNING);
}

static bool CheckScript(void){
    // LD_HL(wScriptFlags);
    // BIT_hl(SCRIPT_RUNNING);
    // RET;
    return bit_test(wram->wScriptFlags, SCRIPT_RUNNING);
}

static void StopScript(void){
    // LD_HL(wScriptFlags);
    // RES_hl(SCRIPT_RUNNING);
    // RET;
    bit_reset(wram->wScriptFlags, SCRIPT_RUNNING);
}

void Script_callasm(void){
    // CALL(aGetScriptByte);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_B;
    // RST(aFarCall);
    // RET;
}

void Script_special(script_s* s, uint16_t de){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // FARCALL(aSpecial);
    // RET;
    Special(de);
}

void Script_memcallasm(void){
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_B_hl;
    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_B;
    // RST(aFarCall);
    // RET;
}

void Script_jumptextfaceplayer(script_s* s, const struct TextCmd* text){
    // LD_A_addr(wScriptBank);
    // LD_addr_A(wScriptTextBank);
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptTextAddr);
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptTextAddr + 1);
    lScriptText = text;
    // LD_B(BANK(aJumpTextFacePlayerScript));
    // LD_HL(mJumpTextFacePlayerScript);
    // JP(mScriptJump);
    Script_Goto(s, JumpTextFacePlayerScript);
}

void Script_jumptext(script_s* s, const struct TextCmd* text){
    // LD_A_addr(wScriptBank);
    // LD_addr_A(wScriptTextBank);
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptTextAddr);
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptTextAddr + 1);
    lScriptText = text;
    // LD_B(BANK(aJumpTextScript));
    // LD_HL(mJumpTextScript);
    // JP(mScriptJump);
    Script_Goto(s, JumpTextScript);
}

#include "../../util/scripting.h"

bool JumpTextFacePlayerScript(script_s* s){
    SCRIPT_BEGIN
    faceplayer;
    SCRIPT_FALLTHROUGH(JumpTextScript)
}

bool JumpTextScript(script_s* s){
    SCRIPT_BEGIN
    opentext;
    repeattext(0xffff);
    waitbutton;
    closetext;
    s_end
    SCRIPT_END
}

void Script_farjumptext(void){
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptTextBank);
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptTextAddr);
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptTextAddr + 1);
    // LD_B(BANK(aJumpTextScript));
    // LD_HL(mJumpTextScript);
    // JP(mScriptJump);
}

void Script_writetext(script_s* s, const struct TextCmd* text){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // CALL(aMapTextbox);
    // RET;
    return MapTextbox(text);
}

// UNUSED
void Script_farwritetext(void){
    // CALL(aGetScriptByte);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // CALL(aMapTextbox);
    // RET;
}

void Script_repeattext(script_s* s, uint16_t hl){
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
    if(hl != 0xffff)
        return;
    // LD_HL(wScriptTextBank);
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // REG_B = wram->wScriptTextBank;
    // REG_HL = wram->wScriptTextAddr;
    // CALL(aMapTextbox);
    MapTextbox(lScriptText);
    // RET;


// done:
    // RET;
}

void Script_waitbutton(script_s* s){
    (void)s;
    // JP(mWaitButton);
    return WaitButton();
}

void Script_promptbutton(script_s* s){
    (void)s;
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t oamupdate = hram.hOAMUpdate;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram.hOAMUpdate = 0x1;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aPromptButton);
    PromptButton();
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    // RET;
    hram.hOAMUpdate = oamupdate;
}

void Script_yesorno(script_s* s){
    (void)s;
    // CALL(aYesNoBox);
    // LD_A(FALSE);
    // IF_C goto no;
    if(YesNoBox()) {
        // LD_A(TRUE);
        wram->wScriptVar = TRUE;
    }
    else {
    // no:
        wram->wScriptVar = FALSE;
        // LD_addr_A(wScriptVar);
        // RET;
    }
}

void Script_loadmenu(script_s* s, const struct MenuHeader* header){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_DE(mLoadMenuHeader);
    // LD_A_addr(wScriptBank);
    // CALL(aCall_a_de);
    LoadMenuHeader(header);
    // CALL(aUpdateSprites);
    UpdateSprites();
    // RET;
}

void Script_closewindow(script_s* s){
    (void)s;
    // CALL(aCloseWindow);
    CloseWindow();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // RET;
}

void Script_pokepic(script_s* s, species_t species){
    (void)s;
    // CALL(aGetScriptByte);
    // AND_A_A;
    // IF_NZ goto ok;
    // LD_A_addr(wScriptVar);
    if(species == 0) {
        species = wram->wScriptVar;
    }

// ok:
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // FARCALL(aPokepic);
    Pokepic();
    // RET;
}

void Script_closepokepic(script_s* s){
    (void)s;
    // FARCALL(aClosePokepic);
    ClosePokepic();
    // RET;
}

void Script_verticalmenu(script_s* s){
    (void)s;
    // LD_A_addr(wScriptBank);
    // LD_HL(mVerticalMenu);
    // RST(aFarCall);
    bool cancel = VerticalMenu();
    // LD_A_addr(wMenuCursorY);
    // IF_NC goto ok;
    // XOR_A_A;

// ok:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (cancel)? 0 : wram->wMenuCursorY;
    // RET;
}

void Script__2dmenu(script_s* s){
    (void)s;
    // LD_A_addr(wScriptBank);
    // LD_HL(mv_2DMenu);
    u8_flag_s res = v_2DMenu();
    // RST(aFarCall);
    // LD_A_addr(wMenuCursorPosition);
    // IF_NC goto ok;
    // XOR_A_A;

// ok:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (res.flag)? 0: res.a;
    // RET;
}

void Script_battletowertext(script_s* s, uint8_t text){
    (void)s;
    // CALL(aSetUpTextbox);
    SetUpTextbox();
    // CALL(aGetScriptByte);
    // LD_C_A;
    // FARCALL(aBattleTowerText);
    BattleTowerText(text);
    // RET;
}

void Script_verbosegiveitem(script_s* s, item_t item, uint8_t quantity){
    (void)s;
    // CALL(aScript_giveitem);
    Script_giveitem(s, item, quantity);
    // CALL(aCurItemName);
    CurItemName(item);
    // LD_DE(wStringBuffer1);
    // LD_A(STRING_BUFFER_4);
    // CALL(aCopyConvertedText);
    CopyConvertedText(STRING_BUFFER_4, wram->wStringBuffer1);
    // LD_B(BANK(aGiveItemScript));
    // LD_DE(mGiveItemScript);
    // JP(mScriptCall);
    Script_CallScript(s, GiveItemScript);
}

void GiveItemScript_DummyFunction(void){
    // RET;

}

bool GiveItemScript(script_s* s){
    static const txt_cmd_s ReceivedItemText[] = {
        text_far(v_ReceivedItemText)
        text_end
    };
    SCRIPT_BEGIN
    GiveItemScript_DummyFunction();
    writetext(ReceivedItemText)
    iffalse(Full);
    waitsfx
    specialsound
    waitbutton
    itemnotify
    s_end

Full:
    promptbutton
    pocketisfull
    s_end
    SCRIPT_END
}

void Script_verbosegiveitemvar(script_s* s, item_t item, uint8_t action){
    // CALL(aGetScriptByte);
    // CP_A(ITEM_FROM_MEM);
    // IF_NZ goto ok;
    // LD_A_addr(wScriptVar);

// ok:
    // LD_addr_A(wCurItem);
    wram->wCurItem = (item != ITEM_FROM_MEM)? item: wram->wScriptVar;
    // CALL(aGetScriptByte);
    // CALL(aGetVarAction);
    // LD_A_de;
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = *GetVarAction(action);
    // LD_HL(wNumItems);
    // CALL(aReceiveItem);
    bool ok = ReceiveItem(GetItemPocket(ITEM_POCKET), wram->wCurItem, wram->wItemQuantityChange);
    // LD_A(TRUE);
    // IF_C goto ok2;
    // XOR_A_A;

// ok2:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (ok)? TRUE: FALSE;
    // CALL(aCurItemName);
    // LD_DE(wStringBuffer1);
    // LD_A(STRING_BUFFER_4);
    // CALL(aCopyConvertedText);
    CopyConvertedText(STRING_BUFFER_4, CurItemName(wram->wCurItem));
    // LD_B(BANK(aGiveItemScript));
    // LD_DE(mGiveItemScript);
    // JP(mScriptCall);
    Script_CallScript(s, GiveItemScript);
}

void Script_itemnotify(script_s* s){
    (void)s;
    // CALL(aGetPocketName);
    GetPocketName();
    // CALL(aCurItemName);
    CurItemName(wram->wCurItem);
    // LD_B(BANK(aPutItemInPocketText));
    // LD_HL(mPutItemInPocketText);
    // CALL(aMapTextbox);
    MapTextbox(PutItemInPocketText);
    // RET;

}

void Script_pocketisfull(script_s* s){
    (void)s;
    // CALL(aGetPocketName);
    GetPocketName();
    // CALL(aCurItemName);
    CurItemName(wram->wCurItem);
    // LD_B(BANK(aPocketIsFullText));
    // LD_HL(mPocketIsFullText);
    // CALL(aMapTextbox);
    MapTextbox(PocketIsFullText);
    // RET;
}

void Script_specialsound(script_s* s){
    (void)s;
    // FARCALL(aCheckItemPocket);
    // LD_A_addr(wItemAttributeValue);
    uint8_t pocket = CheckItemPocket(wram->wCurItem);
    // CP_A(TM_HM);
    // LD_DE(SFX_GET_TM);
    // IF_Z goto play;
    // LD_DE(SFX_ITEM);
    if(pocket == TM_HM) {
    // play:
        // CALL(aPlaySFX);
        PlaySFX(SFX_GET_TM);
        // CALL(aWaitSFX);
        WaitSFX();
        // RET;
        return;
    }
    else {
    // play:
        // CALL(aPlaySFX);
        PlaySFX(SFX_ITEM);
        // CALL(aWaitSFX);
        WaitSFX();
        // RET;
        return;
    }
}

uint8_t* GetPocketName(void){
    // FARCALL(aCheckItemPocket);
    // LD_A_addr(wItemAttributeValue);
    // DEC_A;
    // LD_HL(mItemPocketNames);
    // maskbits(NUM_POCKETS, 0);
    // ADD_A_A;
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // LD_HL(wStringBuffer3);
    // CALL(aCopyName2);
    return Utf8ToCrystalBuffer(wram->wStringBuffer3, sizeof(wram->wStringBuffer3), ItemPocketNames[CheckItemPocket(wram->wCurItem) - 1]);
    // RET;

// INCLUDE "data/items/pocket_names.asm"
}

uint8_t* CurItemName(item_t item){
    // LD_A_addr(wCurItem);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    // RET;
    return GetItemName(item);
}

const txt_cmd_s PutItemInPocketText[] = {
    text_far(v_PutItemInPocketText)
    text_end

    // return PocketIsFullText();
};

const txt_cmd_s PocketIsFullText[] = {
    text_far(v_PocketIsFullText)
    text_end

    // return Script_pokemart();
};

void Script_pokemart(script_s* s, uint8_t mart_type, uint16_t mart_id){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_C_A;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // FARCALL(aOpenMartDialog);
    OpenMartDialog(mart_type, mart_id);
    // RET;
}

void Script_elevator(script_s* s, const struct ElevatorData* data){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // FARCALL(aElevator);
    // RET_C ;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (Elevator(data))? FALSE: TRUE;
    // RET;
}

void Script_trade(script_s* s, uint8_t trade){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // FARCALL(aNPCTrade);
    NPCTrade(trade);
    // RET;
}

// UNUSED
void Script_phonecall(void){
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // FARCALL(aPhoneCall);
    // RET;
}

void Script_hangup(script_s* s){
    (void)s;
    // FARCALL(aHangUp);
    HangUp();
    // RET;
}

void Script_askforphonenumber(script_s* s, uint8_t contact){
    (void)s;
    // CALL(aYesNoBox);
    // IF_C goto refused;
    uint8_t var;
    if(YesNoBox()) {
        // CALL(aGetScriptByte);
        // LD_C_A;
        // FARCALL(aAddPhoneNumber);
        // IF_C goto phonefull;
        if(AddPhoneNumber(contact)) {
            // XOR_A_A;  // PHONE_CONTACT_GOT
            // goto done;
            var = PHONE_CONTACT_GOT;
        }
        else {
        // phonefull:
            // LD_A(PHONE_CONTACTS_FULL);
            // goto done;
            var = PHONE_CONTACTS_FULL;
        }
    }
    else {
    // refused:
        // CALL(aGetScriptByte);
        // LD_A(PHONE_CONTACT_REFUSED);
        var = PHONE_CONTACT_REFUSED;
    }

// done:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = var;
    // RET;
}

void Script_describedecoration(script_s* s, uint8_t deco){
    // CALL(aGetScriptByte);
    // LD_B_A;
    // FARCALL(aDescribeDecoration);
    Script_fn_t script = DescribeDecoration(deco);
    // LD_H_D;
    // LD_L_E;
    // JP(mScriptJump);
    Script_Goto(s, script);
}

void Script_fruittree(script_s* s, uint8_t tree){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurFruitTree);
    wram->wCurFruitTree = tree;
    // LD_B(BANK(aFruitTreeScript));
    // LD_HL(mFruitTreeScript);
    // JP(mScriptJump);
    Script_Goto(s, FruitTreeScript);
}

void Script_swarm(script_s* s, uint8_t flag, uint8_t group, uint8_t number){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_C_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // FARCALL(aStoreSwarmMapIndices);
    StoreSwarmMapIndices(flag, group, number);
    // RET;
}

void Script_trainertext(script_s* s, uint8_t a){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wSeenTextPointer);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wSeenTrainerBank);
    // LD_B_A;
    switch(a) {
    default:
    case TRAINERTEXT_SEEN: return MapTextbox(gSeenTextPointer);
    case TRAINERTEXT_WIN:  return MapTextbox(gWinTextPointer);
    case TRAINERTEXT_LOSS: return MapTextbox(gLossTextPointer);
    }
    // CALL(aMapTextbox);
    // RET;
}

void Script_scripttalkafter(script_s* s){
    // LD_HL(wScriptAfterPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wSeenTrainerBank);
    // LD_B_A;
    // JP(mScriptJump);
    Script_Goto(s, gScriptAfterPointer);
}

void Script_trainerflagaction(script_s* s, uint8_t action){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // LD_HL(wTempTrainerEventFlag);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    uint16_t de = wram->wTempTrainerEventFlag;
    // CALL(aGetScriptByte);
    // LD_B_A;
    // CALL(aEventFlagAction);
    uint8_t c = EventFlagAction(de, action);
    // LD_A_C;
    // AND_A_A;
    // RET_Z ;
    if(c == 0)
        return;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = TRUE;
}

void Script_winlosstext(script_s* s, const struct TextCmd* wintext, const struct TextCmd* losstext){
    (void)s;
    // LD_HL(wWinTextPointer);
    // CALL(aGetScriptByte);
    // LD_hli_A;
    // CALL(aGetScriptByte);
    // LD_hli_A;
    gWinTextPointer = wintext;
    // LD_HL(wLossTextPointer);
    // CALL(aGetScriptByte);
    // LD_hli_A;
    // CALL(aGetScriptByte);
    // LD_hli_A;
    gLossTextPointer = losstext;
    // RET;
}

void Script_endifjustbattled(script_s* s){
    // LD_A_addr(wRunningTrainerBattleScript);
    // AND_A_A;
    // RET_Z ;
    if(wram->wRunningTrainerBattleScript == 0)
        return;
    // JP(mScript_end);
    return Script_end(s);
}

void Script_checkjustbattled(script_s* s){
    (void)s;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    // LD_A_addr(wRunningTrainerBattleScript);
    // AND_A_A;
    // RET_NZ ;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = wram->wRunningTrainerBattleScript != 0;
}

void Script_encountermusic(script_s* s){
    (void)s;
    // LD_A_addr(wOtherTrainerClass);
    // LD_E_A;
    // FARCALL(aPlayTrainerEncounterMusic);
    PlayTrainerEncounterMusic(wram->wOtherTrainerClass);
    // RET;
}

void Script_playmapmusic(script_s* s){
    (void)s;
    // CALL(aPlayMapMusic);
    // RET;
    PlayMapMusic();
}

void Script_playmusic(script_s* s, uint16_t music){
    (void)s;
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);
    // XOR_A_A;
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0;
    // CALL(aMaxVolume);
    MaxVolume();
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // CALL(aPlayMusic);
    PlayMusic(music);
    // RET;
}

void Script_musicfadeout(script_s* s, uint16_t id, uint8_t fade){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wMusicFadeID);
    // CALL(aGetScriptByte);
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = id;
    // CALL(aGetScriptByte);
    // AND_A(~(1 << MUSIC_FADE_IN_F));
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = fade;
    // RET;
}

void Script_playsound(script_s* s, uint16_t sfx){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // CALL(aPlaySFX);
    // RET;
    return PlaySFX(sfx);
}

void Script_waitsfx(script_s* s){
    (void)s;
    // CALL(aWaitSFX);
    // RET;
    return WaitSFX();
}

void Script_warpsound(script_s* s){
    (void)s;
    // FARCALL(aGetWarpSFX);
    // CALL(aPlaySFX);
    // RET;
    return PlaySFX(GetWarpSFX());
}

void Script_cry(script_s* s, species_t id){
    (void)s;
    // CALL(aGetScriptByte);
    // PUSH_AF;
    // CALL(aGetScriptByte);
    // POP_AF;
    // AND_A_A;
    // IF_NZ goto ok;
    if(id == 0) {
        // LD_A_addr(wScriptVar);
        id = (species_t)wram->wScriptVar;
    }

// ok:
    // CALL(aPlayMonCry);
    PlayMonCry(id);
    // RET;
}

static uint8_t GetScriptObject(uint8_t a){
    // AND_A_A;  // PLAYER?
    // RET_Z ;
    // CP_A(LAST_TALKED);
    // RET_Z ;
    if(a == PLAYER || a == (uint8_t)LAST_TALKED)
        return a;
    // DEC_A;
    // RET;
    return a - 1;
}

void Script_setlasttalked(script_s* s, uint8_t a){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    // LDH_addr_A(hLastTalked);
    hram.hLastTalked = GetScriptObject(a);
    // RET;
}

void Script_applymovement(script_s* s, uint8_t a, const uint8_t* hl){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    // LD_C_A;

    return ApplyMovement(GetScriptObject(a), hl);
}

static void ApplyMovement(uint8_t c, const uint8_t* hl){
    // PUSH_BC;
    // LD_A_C;
    // FARCALL(aFreezeAllOtherObjects);
    // POP_BC;
    FreezeAllOtherObjects(c);

    // PUSH_BC;
    // CALL(aUnfreezeFollowerObject);
    UnfreezeFollowerObject(c);
    // POP_BC;


    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // CALL(aGetMovementData);
    // RET_C ;
    if(!GetMovementData(c, hl))
        return;

    // LD_A(SCRIPT_WAIT_MOVEMENT);
    // LD_addr_A(wScriptMode);
    wram->wScriptMode = SCRIPT_WAIT_MOVEMENT;
    // CALL(aStopScript);
    // RET;
    StopScript();
}

void UnfreezeFollowerObject(uint8_t c){
    // FARCALL(av_UnfreezeFollowerObject);
    v_UnfreezeFollowerObject(c);
    // RET;

}

//  apply movement to last talked
void Script_applymovementlasttalked(script_s* s, const uint8_t* hl){
    (void)s;
    // LDH_A_addr(hLastTalked);
    // LD_C_A;
    // JP(mApplyMovement);
    return ApplyMovement(hram.hLastTalked, hl);
}

void Script_faceplayer(script_s* s){
    (void)s;
    // LDH_A_addr(hLastTalked);
    // AND_A_A;
    // RET_Z ;
    if(hram.hLastTalked == 0)
        return;
    // LD_D(0x0);
    // LDH_A_addr(hLastTalked);
    // LD_E_A;
    // FARCALL(aGetRelativeFacing);
    uint8_t d = GetRelativeFacing(hram.hLastTalked, 0);
    // LD_A_D;
    // ADD_A_A;
    // ADD_A_A;
    // LD_E_A;
    // LDH_A_addr(hLastTalked);
    // LD_D_A;
    // CALL(aApplyObjectFacing);
    ApplyObjectFacing(hram.hLastTalked, d << 2);
    // RET;

}

void Script_faceobject(script_s* s, uint8_t e, uint8_t d){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    uint8_t obje = GetScriptObject(e);
    // CP_A(LAST_TALKED);
    // IF_C goto ok;
    // LDH_A_addr(hLastTalked);
    if(obje == (uint8_t)LAST_TALKED)
        obje = hram.hLastTalked;

// ok:
    // LD_E_A;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    uint8_t objd = GetScriptObject(d);
    // CP_A(LAST_TALKED);
    // IF_NZ goto ok2;
    // LDH_A_addr(hLastTalked);
    if(objd == (uint8_t)LAST_TALKED)
        objd = hram.hLastTalked;

// ok2:
    // LD_D_A;
    // PUSH_DE;
    // FARCALL(aGetRelativeFacing);
    d = GetRelativeFacing(obje, objd);
    // POP_BC;
    // RET_C ;
    if(d == 0xff)
        return;
    // LD_A_D;
    // ADD_A_A;
    // ADD_A_A;
    // LD_E_A;
    // LD_D_C;
    // CALL(aApplyObjectFacing);
    ApplyObjectFacing(obje, d << 2);
    // RET;
}

void Script_turnobject(script_s* s, uint8_t obj, uint8_t dir){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    uint8_t a = GetScriptObject(obj);
    // CP_A(LAST_TALKED);
    // IF_NZ goto ok;
    // LDH_A_addr(hLastTalked);
    if(a == (uint8_t)LAST_TALKED)
        a = hram.hLastTalked;

// ok:
    // LD_D_A;
    // CALL(aGetScriptByte);
    // ADD_A_A;
    // ADD_A_A;
    // LD_E_A;
    uint8_t e = dir << 2;
    // CALL(aApplyObjectFacing);
    ApplyObjectFacing(a, e);
    // RET;
}

static void ApplyObjectFacing_DisableTextTiles(void) {
// DisableTextTiles:
    // CALL(aLoadMapPart);
    LoadMapPart();
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

static bool ApplyObjectFacing(uint8_t d, uint8_t e){
    // LD_A_D;
    // PUSH_DE;
    // CALL(aCheckObjectVisibility);
    // IF_C goto not_visible;
    struct Object* bc = CheckObjectVisibility(d);
    if(bc == NULL)
        return false;
    // LD_HL(OBJECT_SPRITE);
    // ADD_HL_BC;
    // LD_A_hl;
    // PUSH_BC;
    // CALL(aDoesSpriteHaveFacings);
    // POP_BC;
    // IF_C goto not_visible;  // STILL_SPRITE
    if(!DoesSpriteHaveFacings(bc->sprite))
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
    SetSpriteDirection(bc, e);
    // LD_HL(wVramState);
    // BIT_hl(6);
    // IF_NZ goto text_state;
    if(!bit_test(wram->wVramState, 6)) {
        // CALL(aApplyObjectFacing_DisableTextTiles);
        ApplyObjectFacing_DisableTextTiles();
    }

// text_state:
    // CALL(aUpdateSprites);
    UpdateSprites();
    // RET;
    return true;


// not_visible:
    // POP_DE;
    // SCF;
    // RET;
}

void Script_variablesprite(script_s* s, uint8_t slot, uint8_t val){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wVariableSprites);
    // ADD_HL_DE;
    // CALL(aGetScriptByte);
    // LD_hl_A;
    wram->wVariableSprites[slot] = val;
    // RET;
}

void Script_appear(script_s* s, uint8_t a){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    uint8_t obj = GetScriptObject(a);
    // CALL(aUnmaskCopyMapObjectStruct);
    UnmaskCopyMapObjectStruct(obj);
    // LDH_A_addr(hMapObjectIndex);
    // LD_B(0);  // clear
    // CALL(aApplyEventActionAppearDisappear);
    ApplyEventActionAppearDisappear(obj, RESET_FLAG);
    // RET;
}

void Script_disappear(script_s* s, uint8_t a){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    uint8_t obj = GetScriptObject(a);
    // CP_A(LAST_TALKED);
    // IF_NZ goto ok;
    // LDH_A_addr(hLastTalked);
    if(obj == (uint8_t)LAST_TALKED)
        obj = hram.hLastTalked;

// ok:
    // CALL(aDeleteObjectStruct);
    DeleteObjectStruct(obj);
    // LDH_A_addr(hMapObjectIndex);
    // LD_B(1);  // set
    // CALL(aApplyEventActionAppearDisappear);
    ApplyEventActionAppearDisappear(obj, SET_FLAG);
    // FARCALL(av_UpdateSprites);
    v_UpdateSprites();
    // RET;
}

static bool ApplyEventActionAppearDisappear(uint8_t mapObjIdx, uint8_t b){
    // PUSH_BC;
    // CALL(aGetMapObject);
    struct MapObject* bc = GetMapObject(mapObjIdx);
    // LD_HL(MAPOBJECT_EVENT_FLAG);
    // ADD_HL_BC;
    // POP_BC;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    uint16_t de = bc->objectEventFlag;
    // LD_A(-1);
    // CP_A_E;
    // IF_NZ goto okay;
    // CP_A_D;
    // IF_NZ goto okay;
    if(de == 0xffff) {
        // XOR_A_A;
        // RET;
        return false;
    }

// okay:
    // CALL(aEventFlagAction);
    // RET;
    return EventFlagAction(de, b) != 0;
}

void Script_follow(script_s* s, uint8_t leader, uint8_t follower){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    // LD_C_A;
    // FARCALL(aStartFollow);
    StartFollow(GetScriptObject(leader), GetScriptObject(follower));
    // RET;
}

void Script_stopfollow(script_s* s){
    (void)s;
    // FARCALL(aStopFollow);
    // RET;
    StopFollow();
}

void Script_moveobject(script_s* s, uint8_t obj, uint8_t x, uint8_t y){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // ADD_A(4);
    // LD_D_A;
    // CALL(aGetScriptByte);
    // ADD_A(4);
    // LD_E_A;
    // FARCALL(aCopyDECoordsToMapObject);
    CopyDECoordsToMapObject(x + 4, y + 4, GetScriptObject(obj));
    // RET;
}

void Script_writeobjectxy(script_s* s, uint8_t obj){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    uint8_t a = GetScriptObject(obj);
    // CP_A(LAST_TALKED);
    // IF_NZ goto ok;
    // LDH_A_addr(hLastTalked);
    if(a == (uint8_t)LAST_TALKED)
        a = hram.hLastTalked;

// ok:
    // LD_B_A;
    // FARCALL(aWriteObjectXY);
    // RET;
    WriteObjectXY(a);
}

void Script_follownotexact(script_s* s, uint8_t b, uint8_t c){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    // LD_C_A;
    // FARCALL(aFollowNotExact);
    FollowNotExact(GetScriptObject(c), GetScriptObject(b));
    // RET;
}

void Script_loademote(script_s* s, uint8_t emote){
    (void)s;
    // CALL(aGetScriptByte);
    // CP_A(EMOTE_FROM_MEM);
    // IF_NZ goto not_var_emote;
    // LD_A_addr(wScriptVar);
    if(emote == (uint8_t)EMOTE_FROM_MEM)
        emote = wram->wScriptVar;

// not_var_emote:
    // LD_C_A;
    // FARCALL(aLoadEmote);
    LoadEmote(emote);
    // RET;
}

void Script_showemote(script_s* s, uint8_t emote, uint8_t obj, uint8_t frames){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = emote;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptObject);
    uint8_t a = GetScriptObject(obj);
    // CP_A(LAST_TALKED);
    // IF_Z goto ok;
    // LDH_addr_A(hLastTalked);
    if(a != (uint8_t)LAST_TALKED)
        hram.hLastTalked = a;

// ok:
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptDelay);
    wram->wScriptDelay = frames;
    // LD_B(BANK(aShowEmoteScript));
    // LD_DE(mShowEmoteScript);
    // JP(mScriptCall);
    Script_CallScript(s, ShowEmoteScript);
}

bool ShowEmoteScript(script_s* s){
    static const uint8_t Show[] = {
        movement_show_emote,
        step_sleep(1),
        movement_step_end,
    };

    static const uint8_t Hide[] = {
        movement_hide_emote,
        step_sleep(1),
        movement_step_end,
    };

    SCRIPT_BEGIN
    loademote(EMOTE_FROM_MEM)
    applymovementlasttalked(Show)
    pause(0)
    applymovementlasttalked(Hide)
    s_end
    SCRIPT_END
}

const uint8_t EarthquakeMovement[] = {
    step_shake(16),  // the 16 gets overwritten with the script byte
    step_sleep2(16),  // the 16 gets overwritten with the lower 6 bits of the script byte
    movement_step_end
};

bool Script_earthquake_script(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, wram_ptr(wEarthquakeMovementDataBuffer))
    s_end
    SCRIPT_END
}

void Script_earthquake(script_s* s, uint8_t amt){
    // LD_HL(mEarthquakeMovement);
    // LD_DE(wEarthquakeMovementDataBuffer);
    // LD_BC(mEarthquakeMovement_End - mEarthquakeMovement);
    // CALL(aCopyBytes);
    CopyBytes(wram->wEarthquakeMovementDataBuffer, EarthquakeMovement, sizeof(EarthquakeMovement));
    // CALL(aGetScriptByte);
    // LD_addr_A(wEarthquakeMovementDataBuffer + 1);
    wram->wEarthquakeMovementDataBuffer[1] = amt;
    // AND_A(0b00111111);
    // LD_addr_A(wEarthquakeMovementDataBuffer + 3);
    wram->wEarthquakeMovementDataBuffer[3] = amt & 0b00111111;
    // LD_B(BANK(aScript_earthquake_script));
    // LD_DE(mScript_earthquake_script);
    // JP(mScriptCall);
    Script_CallScript(s, Script_earthquake_script);

// script:
    //applymovement ['PLAYER', 'wEarthquakeMovementDataBuffer']
    //end ['?']
}

// UNUSED
void Script_loadpikachudata(void){
    // LD_A(PIKACHU);
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = PIKACHU;
    // LD_A(5);
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = 5;
    // RET;
}

void Script_randomwildmon(script_s* s){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wBattleScriptFlags);
    // RET;
    wram->wBattleScriptFlags = 0;
}

void Script_loadtemptrainer(script_s* s){
    (void)s;
    // LD_A((1 << 7) | 1);
    // LD_addr_A(wBattleScriptFlags);
    wram->wBattleScriptFlags = (1 << 7) | 1;
    // LD_A_addr(wTempTrainerClass);
    // LD_addr_A(wOtherTrainerClass);
    wram->wOtherTrainerClass = wram->wTempTrainerClass;
    // LD_A_addr(wTempTrainerID);
    // LD_addr_A(wOtherTrainerID);
    wram->wOtherTrainerID = wram->wTempTrainerID;
    // RET;
}

void Script_loadwildmon(script_s* s, species_t sp, uint8_t level){
    (void)s;
    // LD_A((1 << 7));
    // LD_addr_A(wBattleScriptFlags);
    wram->wBattleScriptFlags = (1 << 7);
    // CALL(aGetScriptByte);
    // LD_addr_A(wTempWildMonSpecies);
    wram->wTempWildMonSpecies = sp;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = level;
    // RET;
}

void Script_loadtrainer(script_s* s, uint8_t tclass, uint8_t tid){
    (void)s;
    // LD_A((1 << 7) | 1);
    // LD_addr_A(wBattleScriptFlags);
    wram->wBattleScriptFlags = (1 << 7) | 1;
    // CALL(aGetScriptByte);
    // LD_addr_A(wOtherTrainerClass);
    wram->wOtherTrainerClass = tclass;
    // CALL(aGetScriptByte);
    // LD_addr_A(wOtherTrainerID);
    wram->wOtherTrainerID = tid;
    // RET;
}

void Script_startbattle(script_s* s){
    (void)s;
    // CALL(aBufferScreen);
    BufferScreen();
    // PREDEF(pStartBattle);
    StartBattle();
    // LD_A_addr(wBattleResult);
    // AND_A(~BATTLERESULT_BITMASK);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wBattleResult & ~BATTLERESULT_BITMASK;
    // RET;
}

void Script_catchtutorial(script_s* s, uint8_t type){
    // CALL(aGetScriptByte);
    // LD_addr_A(wBattleType);
    wram->wBattleType = type;
    // CALL(aBufferScreen);
    BufferScreen();
    // FARCALL(aCatchTutorial);
    CatchTutorial();
    // JP(mScript_reloadmap);
    return Script_reloadmap(s);
}

void Script_reloadmapafterbattle(script_s* s){
    (void)s;
    // LD_HL(wBattleScriptFlags);
    // LD_D_hl;
    uint8_t d = wram->wBattleScriptFlags;
    // LD_hl(0);
    wram->wBattleScriptFlags = 0;
    // LD_A_addr(wBattleResult);
    // AND_A(~BATTLERESULT_BITMASK);
    // CP_A(LOSE);
    // IF_NZ goto notblackedout;
    if((wram->wBattleResult & ~BATTLERESULT_BITMASK) == LOSE) {
        // LD_B(BANK(aScript_BattleWhiteout));
        // LD_HL(mScript_BattleWhiteout);
        // JP(mScriptJump);
        return Script_Goto(s, Script_BattleWhiteout);
    }

// notblackedout:
    // BIT_D(0);
    // IF_Z goto was_wild;
    if(bit_test(d, 0)) {
        // FARCALL(aMomTriesToBuySomething);
        MomTriesToBuySomething();
        // goto done;
    }
    else {
    // was_wild:
        // LD_A_addr(wBattleResult);
        // BIT_A(BATTLERESULT_BOX_FULL);
        // IF_Z goto done;
        if(bit_test(wram->wBattleResult, BATTLERESULT_BOX_FULL)) {
            // LD_B(BANK(aScript_SpecialBillCall));
            // LD_DE(mScript_SpecialBillCall);
            // FARCALL(aLoadScriptBDE);
            LoadScriptBDE(Script_SpecialBillCall);
        }
    }
// done:
    // JP(mScript_reloadmap);
    return Script_reloadmap(s);

}

void Script_reloadmap(script_s* s){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wBattleScriptFlags);
    wram->wBattleScriptFlags = 0;
    // LD_A(MAPSETUP_RELOADMAP);
    // LDH_addr_A(hMapEntryMethod);
    hram.hMapEntryMethod = MAPSETUP_RELOADMAP;
    // LD_A(MAPSTATUS_ENTER);
    // CALL(aLoadMapStatus);
    LoadMapStatus(MAPSTATUS_ENTER);
    // CALL(aStopScript);
    StopScript();
    // RET;
}

// UNUSED
void Script_scall(void){
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // JR(mScriptCall);

}

// UNUSED
void Script_farscall(void){
    // CALL(aGetScriptByte);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // JR(mScriptCall);
}

// UNUSED
void Script_memcall(void){
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_B_hl;
    // INC_HL;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
// fallthrough

    return ScriptCall();
}

// UNUSED
void ScriptCall(void){
//  Bug: The script stack has a capacity of 5 scripts, yet there is
//  nothing to stop you from pushing a sixth script.  The high part
//  of the script address can then be overwritten by modifications
//  to wScriptDelay, causing the script to return to the rst/interrupt
//  space.

    // PUSH_DE;
    // LD_HL(wScriptStackSize);
    // LD_E_hl;
    // INC_hl;
    // LD_D(0);
    // LD_HL(wScriptStack);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // POP_DE;
    // LD_A_addr(wScriptBank);
    // LD_hli_A;
    // LD_A_addr(wScriptPos);
    // LD_hli_A;
    // LD_A_addr(wScriptPos + 1);
    // LD_hl_A;
    // LD_A_B;
    // LD_addr_A(wScriptBank);
    // LD_A_E;
    // LD_addr_A(wScriptPos);
    // LD_A_D;
    // LD_addr_A(wScriptPos + 1);
    // RET;
}

void CallCallback(Script_fn_t callback){
    // LD_A_addr(wScriptBank);
    // OR_A(0x80);
    // LD_addr_A(wScriptBank);
    wram->wScriptBank |= 0x80;
    // JP(mScriptCall);
    Script_CallScript(&gCurScript, callback);
}

// UNUSED
void Script_sjump(void){
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // JP(mScriptJump);
}

// UNUSED
void Script_farsjump(void){
    // CALL(aGetScriptByte);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // JP(mScriptJump);

}

// UNUSED
void Script_memjump(void){
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_B_hl;
    // INC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP(mScriptJump);

}

// UNUSED
void Script_iffalse(void){
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // JP_NZ (mSkipTwoScriptBytes);
    // JP(mScript_sjump);

}

// UNUSED
void Script_iftrue(void){
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // JP_NZ (mScript_sjump);
    // JP(mSkipTwoScriptBytes);

}

// UNUSED
void Script_ifequal(void){
    // CALL(aGetScriptByte);
    // LD_HL(wScriptVar);
    // CP_A_hl;
    // JR_Z (mScript_sjump);
    // JR(mSkipTwoScriptBytes);
}

// UNUSED
void Script_ifnotequal(void){
    // CALL(aGetScriptByte);
    // LD_HL(wScriptVar);
    // CP_A_hl;
    // JR_NZ (mScript_sjump);
    // JR(mSkipTwoScriptBytes);
}

// UNUSED
void Script_ifgreater(void){
    // LD_A_addr(wScriptVar);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // CP_A_B;
    // JR_C (mScript_sjump);
    // JR(mSkipTwoScriptBytes);
}

// UNUSED
void Script_ifless(void){
    // CALL(aGetScriptByte);
    // LD_B_A;
    // LD_A_addr(wScriptVar);
    // CP_A_B;
    // JR_C (mScript_sjump);
    // JR(mSkipTwoScriptBytes);
}

void Script_jumpstd(script_s* s, uint16_t std){
    // CALL(aStdScript);
    // JR(mScriptJump);
    return Script_Goto(s, StdScript(std));
}

void Script_callstd(script_s* s, uint16_t std){
    // CALL(aStdScript);
    // LD_D_H;
    // LD_E_L;
    // JP(mScriptCall);
    return Script_CallScript(s, StdScript(std));
}

static Script_fn_t StdScript(uint16_t std){
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_HL(mStdScripts);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A(BANK(aStdScripts));
    // CALL(aGetFarByte);
    // LD_B_A;
    // INC_HL;
    // LD_A(BANK(aStdScripts));
    // CALL(aGetFarWord);
    // RET;
    return StdScripts[std];
}

// UNUSED
void SkipTwoScriptBytes(void){
    // CALL(aGetScriptByte);
    // CALL(aGetScriptByte);
    // RET;
}

// UNUSED
void ScriptJump(void){
    // LD_A_B;
    // LD_addr_A(wScriptBank);
    // LD_A_L;
    // LD_addr_A(wScriptPos);
    // LD_A_H;
    // LD_addr_A(wScriptPos + 1);
    // RET;
}

void Script_sdefer(script_s* s, Script_fn_t script){
    (void)s;
    // LD_A_addr(wScriptBank);
    // LD_addr_A(wDeferredScriptBank);
    // CALL(aGetScriptByte);
    // LD_addr_A(wDeferredScriptAddr);
    // CALL(aGetScriptByte);
    // LD_addr_A(wDeferredScriptAddr + 1);
    gDeferredScriptAddr = script;
    // LD_HL(wScriptFlags);
    // SET_hl(3);
    bit_set(wram->wScriptFlags, 3);
    // RET;
}

void Script_checkscene(script_s* s) {
    (void)s;
    wram->wScriptVar = CheckScenes();
}

void Script_checkmapscene(script_s* s, uint8_t group, uint8_t map){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // LD_C_A;
    // CALL(aGetMapSceneID);
    uint8_t* de = GetMapSceneID(group, map);
    // LD_A_D;
    // OR_A_E;
    // IF_Z goto no_scene;
    if(de != NULL) {
        // LD_A_de;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = *de;
        // RET;
        return;
    }
    else {
    // no_scene:
        // LD_A(0xff);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0xff;
        // RET;
        return;
    }
}

void Script_setscene(script_s* s, uint8_t scene){
    (void)s;
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // JR(mDoScene);
    return DoScene(gCurMapData.mapGroup, gCurMapData.mapNumber, scene);
}

void Script_setmapscene(script_s* s, uint8_t group, uint8_t map, uint8_t scene){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_B_A;
    // CALL(aGetScriptByte);
    // LD_C_A;
    // return DoScene();
    return DoScene(group, map, scene);
}

static void DoScene(uint8_t group, uint8_t map, uint8_t scene){
    // CALL(aGetMapSceneID);
    // LD_A_D;
    // OR_A_E;
    uint8_t* de = GetMapSceneID(group, map);
    // IF_Z goto no_scene;
    if(de != NULL) {
        // CALL(aGetScriptByte);
        // LD_de_A;
        *de = scene;
    }

// no_scene:
    // RET;
}

void Script_readmem(script_s* s, uint8_t* hl){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_hl;
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = *hl;
}

void Script_writemem(script_s* s, uint8_t* hl){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_addr(wScriptVar);
    // LD_hl_A;
    // RET;
    *hl = wram->wScriptVar;
}

void Script_loadmem(script_s* s, uint8_t* hl, uint8_t val){
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

void Script_setval(script_s* s, uint8_t val){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = val;
}

void Script_addval(script_s* s, uint8_t val){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_HL(wScriptVar);
    // ADD_A_hl;
    // LD_hl_A;
    // RET;
    wram->wScriptVar += val;
}

void Script_random(script_s* s, uint8_t a){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = a;
    // AND_A_A;
    // RET_Z ;
    if(a == 0)
        return;

    // LD_C_A;
    // CALL(aScript_random_Divide256byC);
    a = (uint8_t)(256 % a);
    // AND_A_A;
    // IF_Z goto no_restriction;  // 256 % b == 0
    if(a == 0) {
    // no_restriction:
        // PUSH_BC;
        // CALL(aRandom);
        // POP_BC;
        Random();
        // LDH_A_addr(hRandomAdd);
        a = hram.hRandomAdd;
    }
    else {
        // LD_B_A;
        // XOR_A_A;
        // SUB_A_B;
        // LD_B_A;
        uint8_t b = 0 - a;

        do {
        // loop:
            // PUSH_BC;
            // CALL(aRandom);
            Random();
            // POP_BC;
            // LDH_A_addr(hRandomAdd);
            a = hram.hRandomAdd;
            // CP_A_B;
            // IF_NC goto loop;
        } while(a >= b);
        // goto finish;
    }

// finish:
    // PUSH_AF;
    // LD_A_addr(wScriptVar);
    // LD_C_A;
    // POP_AF;
    // CALL(aSimpleDivide);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = a % wram->wScriptVar;
    // RET;
}

void Script_readvar(script_s* s, uint8_t var){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetVarAction);
    // LD_A_de;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = *GetVarAction(var);
    // RET;
}

void Script_writevar(script_s* s, uint8_t var){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetVarAction);
    // LD_A_addr(wScriptVar);
    // LD_de_A;
    *GetVarAction(var) = wram->wScriptVar;
    // RET;
}

void Script_loadvar(script_s* s, uint8_t var, uint8_t value){
    (void)s;
    // CALL(aGetScriptByte);
    // CALL(aGetVarAction);
    // CALL(aGetScriptByte);
    // LD_de_A;
    *GetVarAction(var) = value;
    // RET;
}

static uint8_t* GetVarAction(uint8_t a){
    // LD_C_A;
    // FARCALL(av_GetVarAction);
    // RET;
    return v_GetVarAction(a);
}

// UNUSED
void Script_checkver(void){
    // LD_A_addr(mScript_checkver_gs_version);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = GS_VERSION;
    // RET;


// gs_version:
    //db ['GS_VERSION'];

    // return Script_getmonname();
}

void Script_getmonname(script_s* s, uint8_t buf, species_t species){
    (void)s;
    // CALL(aGetScriptByte);
    // AND_A_A;
    // IF_NZ goto gotit;
    if(species == 0) {
        // LD_A_addr(wScriptVar);
        species = wram->wScriptVar;
    }
// gotit:
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(species);
    // LD_DE(wStringBuffer1);

    return GetStringBuffer(buf, wram->wStringBuffer1);
}

static void GetStringBuffer(uint8_t a, const uint8_t* de){
    // CALL(aGetScriptByte);
    // CP_A(NUM_STRING_BUFFERS);
    // IF_C goto ok;
    // XOR_A_A;
    if(a >= NUM_STRING_BUFFERS)
        return CopyConvertedText(0, de);

// ok:
    return CopyConvertedText(a, de);
}

static void CopyConvertedText(uint8_t a, const uint8_t* de){
    // LD_HL(wStringBuffer3);
    // LD_BC(STRING_BUFFER_LENGTH);
    // CALL(aAddNTimes);
    uint8_t* hl = wram->wStringBuffer3 + (a * STRING_BUFFER_LENGTH);
    // CALL(aCopyName2);
    // RET;
    CopyName2(hl, de);
}

void Script_getitemname(script_s* s, item_t item, uint8_t buf){
    (void)s;
    // CALL(aGetScriptByte);
    // AND_A_A;  // USE_SCRIPT_VAR
    // IF_NZ goto ok;
    if(item == NO_ITEM) {
        // LD_A_addr(wScriptVar);
        item = (item_t)wram->wScriptVar;
    }

// ok:
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    // LD_DE(wStringBuffer1);
    // JR(mGetStringBuffer);
    return GetStringBuffer(buf, GetItemName(item));
}

void Script_getcurlandmarkname(script_s* s, uint8_t b){
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aGetWorldMapLocation);
    (void)s;
    uint8_t loc = GetWorldMapLocation(gCurMapData.mapGroup, gCurMapData.mapNumber);

    return ConvertLandmarkToText(loc, b);
}

static void ConvertLandmarkToText(uint8_t a, uint8_t b){
    // LD_E_A;
    // FARCALL(aGetLandmarkName);
    // LD_DE(wStringBuffer1);
    // JP(mGetStringBuffer);
    
    return GetStringBuffer(b, GetLandmarkName(a));
}

void Script_getlandmarkname(script_s* s, uint8_t a, uint8_t b){
    // CALL(aGetScriptByte);
    // JR(mConvertLandmarkToText);
    (void)s;
    return ConvertLandmarkToText(a, b);
}

void Script_gettrainername(script_s* s, uint8_t a, uint8_t b, uint8_t c){
    // CALL(aGetScriptByte);
    // LD_C_A;
    // CALL(aGetScriptByte);
    // LD_B_A;
    // FARCALL(aGetTrainerName);
    // JR(mGetStringBuffer);
    (void)s;
    return GetStringBuffer(a, GetTrainerName(c-1, b));
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

void Script_gettrainerclassname(script_s* s, uint8_t buffer, uint8_t tclass){
    (void)s;
    // LD_A(TRAINER_NAME);
    // LD_addr_A(wNamedObjectType);
    // JR(mContinueToGetName);
    return GetStringBuffer(buffer, GetName(TRAINER_NAME, tclass));
}

void Script_getmoney(script_s* s, uint8_t buffer, uint8_t which){
    (void)s;
    // CALL(aResetStringBuffer1);
    ResetStringBuffer1();
    // CALL(aGetMoneyAccount);
    uint8_t* de = GetMoneyAccount(which);
    // LD_HL(wStringBuffer1);
    // LD_BC((PRINTNUM_LEFTALIGN | 3 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum(wram->wStringBuffer1, de, PRINTNUM_LEFTALIGN | 3, 6);
    // LD_DE(wStringBuffer1);
    // JP(mGetStringBuffer);
    return GetStringBuffer(buffer, wram->wStringBuffer1);
}

void Script_getcoins(script_s* s, uint8_t a){
    (void)s;
    // CALL(aResetStringBuffer1);
    ResetStringBuffer1();
    // LD_HL(wStringBuffer1);
    // LD_DE(wCoins);
    // LD_BC((PRINTNUM_LEFTALIGN | 2 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum(wram->wStringBuffer1, (uint8_t*)&wram->wCoins, (PRINTNUM_LEFTALIGN | 2), 6);
    // LD_DE(wStringBuffer1);
    // JP(mGetStringBuffer);
    return GetStringBuffer(a, wram->wStringBuffer1);
}

void Script_getnum(script_s* s, uint8_t a){
    (void)s;
    // CALL(aResetStringBuffer1);
    ResetStringBuffer1();
    // LD_DE(wScriptVar);
    // LD_HL(wStringBuffer1);
    // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum(wram->wStringBuffer1, &wram->wScriptVar, (PRINTNUM_LEFTALIGN | 1), 3);
    // LD_DE(wStringBuffer1);
    // JP(mGetStringBuffer);
    return GetStringBuffer(a, wram->wStringBuffer1);
}

void ResetStringBuffer1(void){
    // LD_HL(wStringBuffer1);
    // LD_BC(NAME_LENGTH);
    // LD_A(0x50);
    // CALL(aByteFill);
    // RET;
    return ByteFill(wram->wStringBuffer1, NAME_LENGTH, 0x50);
}

void Script_getstring(script_s* s, uint8_t a, const char* hl){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_A_addr(wScriptBank);
    // LD_HL(mCopyName1);
    // RST(aFarCall);
    CopyName1(U82C(hl));
    // LD_DE(wStringBuffer2);
    // JP(mGetStringBuffer);
    return GetStringBuffer(a, wram->wStringBuffer2);
}

void Script_givepokemail(script_s* s, const struct Pokemail* mail){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // LD_A_addr(wScriptBank);
    // CALL(aGetFarByte);
    // LD_B_A;
    // PUSH_BC;
    // INC_HL;
    // LD_BC(MAIL_MSG_LENGTH);
    // LD_DE(wMonMailMessageBuffer);
    // LD_A_addr(wScriptBank);
    // CALL(aFarCopyBytes);
    U82CB(wram->wMonMailMessageBuffer, MAIL_MSG_LENGTH, mail->message);
    // POP_BC;
    // FARCALL(aGivePokeMail);
    GivePokeMail(mail);
    // RET;
}

void Script_checkpokemail(script_s* s, const char* text){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // FARCALL(aCheckPokeMail);
    CheckPokeMail(text);
    // RET;
}

void Script_giveitem(script_s* s, item_t item, uint8_t quantity){
    (void)s;
    // CALL(aGetScriptByte);
    // CP_A(ITEM_FROM_MEM);
    // IF_NZ goto ok;
    // LD_A_addr(wScriptVar);
    if(item == ITEM_FROM_MEM)
        item = wram->wScriptVar;

// ok:
    // LD_addr_A(wCurItem);
    wram->wCurItem = item;
    // CALL(aGetScriptByte);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = quantity;
    // LD_HL(wNumItems);
    // CALL(aReceiveItem);
    // IF_NC goto full;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = ReceiveItem(GetItemPocket(ITEM_POCKET), item, quantity);

// full:
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // RET;
    return;
}

void Script_takeitem(script_s* s, item_t item, uint8_t quantity){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurItem);
    // CALL(aGetScriptByte);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = quantity;
    // LD_A(-1);
    // LD_addr_A(wCurItemQuantity);
    wram->wCurItemQuantity = 0xff;
    // LD_HL(wNumItems);
    // CALL(aTossItem);
    // RET_NC ;
    if(!TossItem(GetItemPocket(ITEM_POCKET), item, quantity))
        return;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

void Script_checkitem(script_s* s, item_t item){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurItem);
    wram->wCurItem = item;
    // LD_HL(wNumItems);
    // CALL(aCheckItem);
    if(!CheckItem(GetItemPocket(ITEM_POCKET), item))
        return;
    // RET_NC ;

    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = TRUE;
}

void Script_givemoney(script_s* s, uint8_t account, uint32_t amount){
    (void)s;
    // CALL(aGetMoneyAccount);
    uint8_t* act = GetMoneyAccount(account);
    // CALL(aLoadMoneyAmountToMem);
    uint8_t* amt = LoadMoneyAmountToMem(amount);
    // FARCALL(aGiveMoney);
    GiveMoney(act, amt);
    // RET;
}

void Script_takemoney(script_s* s, uint8_t account, uint32_t amount){
    (void)s;
    // CALL(aGetMoneyAccount);
    uint8_t* act = GetMoneyAccount(account);
    // CALL(aLoadMoneyAmountToMem);
    uint8_t* amt = LoadMoneyAmountToMem(amount);
    // FARCALL(aTakeMoney);
    TakeMoney(act, amt);
    // RET;
}

void Script_checkmoney(script_s* s, uint8_t account, uint32_t amt){
    // CALL(aGetMoneyAccount);
    uint8_t* acct = GetMoneyAccount(account);
    // CALL(aLoadMoneyAmountToMem);
    uint8_t* bc = LoadMoneyAmountToMem(amt);
    // FARCALL(aCompareMoney);
    u8_flag_s cmp = CompareMoney(bc, acct);

    return CompareMoneyAction(s, cmp);
}

static void CompareMoneyAction(script_s* s, u8_flag_s res){
    (void)s;
    // IF_C goto less;
    if(res.flag)
        wram->wScriptVar = HAVE_LESS;
    // IF_Z goto exact;
    else if(res.a == 0)
        wram->wScriptVar = HAVE_AMOUNT;
    // LD_A(HAVE_MORE);
    // goto done;
    else
        wram->wScriptVar = HAVE_MORE;

// exact:
    // LD_A(HAVE_AMOUNT);
    // goto done;

// less:
    // LD_A(HAVE_LESS);

// done:
    // LD_addr_A(wScriptVar);
    // RET;
}

static uint8_t* GetMoneyAccount(uint8_t a){
    // CALL(aGetScriptByte);
    // AND_A_A;
    // LD_DE(wMoney);  // YOUR_MONEY
    // RET_Z ;
    // LD_DE(wMomsMoney);  // MOMS_MONEY
    // RET;
    return (a == YOUR_MONEY)? wram->wMoney: wram->wMomsMoney;
}

static uint8_t* LoadMoneyAmountToMem(uint32_t amount){
    // LD_BC(hMoneyTemp);
    // PUSH_BC;
    // CALL(aGetScriptByte);
    // LD_bc_A;
    hram.hMoneyTemp[0] = (uint8_t)((amount >> 16) & 0xff);
    // INC_BC;
    // CALL(aGetScriptByte);
    // LD_bc_A;
    hram.hMoneyTemp[1] = (uint8_t)((amount >> 8) & 0xff);
    // INC_BC;
    // CALL(aGetScriptByte);
    // LD_bc_A;
    hram.hMoneyTemp[2] = (uint8_t)(amount & 0xff);
    // POP_BC;
    // RET;
    return hram.hMoneyTemp;
}

void Script_givecoins(script_s* s, uint16_t amount){
    (void)s;
    // CALL(aLoadCoinAmountToMem);
    uint8_t* amt = LoadCoinAmountToMem(amount);
    // FARCALL(aGiveCoins);
    GiveCoins(amt);
    // RET;
}

void Script_takecoins(script_s* s, uint16_t amount){
    (void)s;
    // CALL(aLoadCoinAmountToMem);
    uint8_t* amt = LoadCoinAmountToMem(amount);
    // FARCALL(aTakeCoins);
    TakeCoins(amt);
    // RET;
}

void Script_checkcoins(script_s* s, uint16_t amount){
    // CALL(aLoadCoinAmountToMem);
    uint8_t* amt = LoadCoinAmountToMem(amount);
    // FARCALL(aCheckCoins);
    // JR(mCompareMoneyAction);
    return CompareMoneyAction(s, CheckCoins(amt));
}

static uint8_t* LoadCoinAmountToMem(uint16_t amount){
    // CALL(aGetScriptByte);
    // LDH_addr_A(hMoneyTemp + 1);
    hram.hMoneyTemp[1] = LOW(amount);
    // CALL(aGetScriptByte);
    // LDH_addr_A(hMoneyTemp);
    hram.hMoneyTemp[0] = HIGH(amount);
    // LD_BC(hMoneyTemp);
    // RET;
    return hram.hMoneyTemp;
}

void Script_checktime(script_s* s, uint8_t time){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // FARCALL(aCheckTime);
    u8_flag_s res = CheckTime();
    // CALL(aGetScriptByte);
    // AND_A_C;
    // RET_Z ;
    if(res.a & time) {
        // LD_A(TRUE);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = TRUE;
    }
    // RET;
}

void Script_checkpoke(script_s* s, species_t a){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // CALL(aGetScriptByte);
    // LD_HL(wPartySpecies);
    // LD_DE(1);
    // CALL(aIsInArray);
    for(uint32_t i = 0; i < lengthof(wram->wPartySpecies); ++i) {
        if(wram->wPartySpecies[i] == a) {
            wram->wScriptVar = TRUE;
            return;
        }
    }
    // RET_NC ;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    // RET;

}

void Script_addcellnum(script_s* s, uint8_t contact){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // CALL(aGetScriptByte);
    // LD_C_A;
    // FARCALL(aAddPhoneNumber);
    // RET_NC ;
    if(AddPhoneNumber(contact))
        return;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

void Script_delcellnum(script_s* s, uint8_t c){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // CALL(aGetScriptByte);
    // LD_C_A;
    // FARCALL(aDelCellNum);
    // RET_NC ;
    if(DelCellNum(c))
        return;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

//  returns false if the cell number is not in your phone
void Script_checkcellnum(script_s* s, uint8_t c){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // CALL(aGetScriptByte);
    // LD_C_A;
    // FARCALL(aCheckCellNum);
    // RET_NC ;
    if(CheckCellNum(c) == NULL)
        return;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

void Script_specialphonecall(script_s* s, uint16_t id){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wSpecialPhoneCallID);
    // CALL(aGetScriptByte);
    // LD_addr_A(wSpecialPhoneCallID + 1);
    wram->wSpecialPhoneCallID = id;
    // RET;
}

//  returns false if no special phone call is stored
void Script_checkphonecall(script_s* s){
    (void)s;
    // LD_A_addr(wSpecialPhoneCallID);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_A(TRUE);

// ok:
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = (wram->wSpecialPhoneCallID != 0)? TRUE: FALSE;
}

void Script_givepoke(script_s* s, species_t species, uint8_t lvl, item_t item, bool ext, const char* nickname, const char* otName){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = lvl;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurItem);
    wram->wCurItem = item;
    // CALL(aGetScriptByte);
    // AND_A_A;
    // LD_B_A;
    // IF_Z goto ok;
    // LD_HL(wScriptPos);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // CALL(aGetScriptByte);
    // CALL(aGetScriptByte);
    // CALL(aGetScriptByte);
    // CALL(aGetScriptByte);
// ok:
    // FARCALL(aGivePoke);
    wram->wScriptVar = GivePoke(ext? 1: 0, nickname, otName);
    // LD_A_B;
    // LD_addr_A(wScriptVar);
    // RET;
}

void Script_givepokesimple(script_s* s, species_t species, uint8_t lvl, item_t item){
    return Script_givepoke(s, species, lvl, item, false, NULL, NULL);
}

//  if no room in the party, return 0 in wScriptVar
//  Does not seem to matter in the code since the
//  scripts check party length before giving the egg
//  anyway.
void Script_giveegg(script_s* s, species_t species, uint8_t lvl){
    (void)s;
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // CALL(aGetScriptByte);
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = lvl;
    // FARCALL(aGiveEgg);
    // RET_NC ;
    if(GiveEgg())
        return;
    // LD_A(2);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 2;
    // RET;
}

void Script_setevent(script_s* s, uint16_t flag){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_B(SET_FLAG);
    // CALL(aEventFlagAction);
    EventFlagAction(flag, SET_FLAG);
    // RET;
}

void Script_clearevent(script_s* s, uint16_t flag){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_B(RESET_FLAG);
    // CALL(aEventFlagAction);
    EventFlagAction(flag, RESET_FLAG);
    // RET;
}

void Script_checkevent(script_s* s, uint16_t flag){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_B(CHECK_FLAG);
    // CALL(aEventFlagAction);
    if(EventFlagAction(flag, CHECK_FLAG) == 0) {
        wram->wScriptVar = FALSE;
    }
    else {
        wram->wScriptVar = TRUE;
    }
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto false_;
    // LD_A(TRUE);

// false_:
    // LD_addr_A(wScriptVar);
    // RET;
}

void Script_setflag(script_s* s, uint16_t flag){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_B(SET_FLAG);
    // CALL(av_EngineFlagAction);
    // RET;
    v_EngineFlagAction(flag, SET_FLAG);
}

void Script_clearflag(script_s* s, uint16_t flag){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_B(RESET_FLAG);
    // CALL(av_EngineFlagAction);
    // RET;
    v_EngineFlagAction(flag, RESET_FLAG);
}

void Script_checkflag(script_s* s, uint16_t flag){
    (void)s;
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
    wram->wScriptVar = (v_EngineFlagAction(flag, CHECK_FLAG))? TRUE: FALSE;
}

static bool v_EngineFlagAction(uint16_t de, uint8_t b){
    // FARCALL(aEngineFlagAction);
    // RET;
    return EngineFlagAction(de, b);
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

// UNUSED
void Script_xycompare(void){
    // CALL(aGetScriptByte);
    // LD_addr_A(wXYComparePointer);
    // CALL(aGetScriptByte);
    // LD_addr_A(wXYComparePointer + 1);
    // RET;
}

void Script_warpfacing(script_s* s, uint8_t dir, uint8_t group, uint8_t num, uint8_t x, uint8_t y){
    // CALL(aGetScriptByte);
    // maskbits(NUM_DIRECTIONS, 0);
    // LD_C_A;
    dir &= 3;
    // LD_A_addr(wPlayerSpriteSetupFlags);
    // SET_A(PLAYERSPRITESETUP_CUSTOM_FACING_F);
    bit_set(wram->wPlayerSpriteSetupFlags, PLAYERSPRITESETUP_CUSTOM_FACING_F);
    // OR_A_C;
    // LD_addr_A(wPlayerSpriteSetupFlags);
    wram->wPlayerSpriteSetupFlags |= dir;
//  fallthrough

    return Script_warp(s, group, num, x, y);
}

void Script_warp(script_s* s, uint8_t group, uint8_t num, uint8_t x, uint8_t y){
    (void)s;
//  This seems to be some sort of error handling case.
    // CALL(aGetScriptByte);
    // AND_A_A;
    // IF_Z goto not_ok;
    if(group == 0) {
    // not_ok:
        // CALL(aGetScriptByte);
        // CALL(aGetScriptByte);
        // CALL(aGetScriptByte);
        // LD_A(SPAWN_N_A);
        // LD_addr_A(wDefaultSpawnpoint);
        wram->wDefaultSpawnpoint = SPAWN_N_A;
        // LD_A(MAPSETUP_BADWARP);
        // LDH_addr_A(hMapEntryMethod);
        hram.hMapEntryMethod = MAPSETUP_BADWARP;
        // LD_A(MAPSTATUS_ENTER);
        // CALL(aLoadMapStatus);
        LoadMapStatus(MAPSTATUS_ENTER);
        // CALL(aStopScript);
        StopScript();
        // RET;
        return;
    }
    // LD_addr_A(wMapGroup);
    gCurMapData.mapGroup = group;
    // CALL(aGetScriptByte);
    // LD_addr_A(wMapNumber);
    gCurMapData.mapNumber = num;
    // CALL(aGetScriptByte);
    // LD_addr_A(wXCoord);
    gCurMapData.xCoord = x;
    // CALL(aGetScriptByte);
    // LD_addr_A(wYCoord);
    gCurMapData.yCoord = y;
    // LD_A(SPAWN_N_A);
    // LD_addr_A(wDefaultSpawnpoint);
    wram->wDefaultSpawnpoint = SPAWN_N_A;
    // LD_A(MAPSETUP_WARP);
    // LDH_addr_A(hMapEntryMethod);
    hram.hMapEntryMethod = MAPSETUP_WARP;
    // LD_A(MAPSTATUS_ENTER);
    // CALL(aLoadMapStatus);
    LoadMapStatus(MAPSTATUS_ENTER);
    // CALL(aStopScript);
    StopScript();
    // RET;
}

void Script_warpmod(script_s* s, uint8_t warp, uint8_t group, uint8_t num){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wBackupWarpNumber);
    gCurMapData.backupWarpNumber = warp;
    // CALL(aGetScriptByte);
    // LD_addr_A(wBackupMapGroup);
    gCurMapData.backupMapGroup = group;
    // CALL(aGetScriptByte);
    // LD_addr_A(wBackupMapNumber);
    gCurMapData.backupMapNumber = num;
    // RET;
}

void Script_blackoutmod(script_s* s, uint8_t group, uint8_t num){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wLastSpawnMapGroup);
    gCurMapData.lastSpawnMapGroup = group;
    // CALL(aGetScriptByte);
    // LD_addr_A(wLastSpawnMapNumber);
    gCurMapData.lastSpawnMapNumber = num;
    // RET;
}

void Script_dontrestartmapmusic(script_s* s){
    (void)s;
    // LD_A(TRUE);
    // LD_addr_A(wDontPlayMapMusicOnReload);
    wram->wDontPlayMapMusicOnReload = TRUE;
    // RET;
}

void Script_writecmdqueue(script_s* s, const struct CmdQueue* cmd){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_E_A;
    // CALL(aGetScriptByte);
    // LD_D_A;
    // LD_A_addr(wScriptBank);
    // LD_B_A;
    // FARCALL(aWriteCmdQueue);  // no need to farcall
    WriteCmdQueue(cmd);
    // RET;
}

void Script_delcmdqueue(script_s* s, uint8_t b){
    (void)s;
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // CALL(aGetScriptByte);
    // LD_B_A;
    // FARCALL(aDelCmdQueue);  // no need to farcall
    // RET_C ;
    if(DelCmdQueue(b))
        return;
    // LD_A(TRUE);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

// UNUSED
void Script_changemapblocks(void){
    // CALL(aGetScriptByte);
    // LD_addr_A(wMapBlocksBank);
    // CALL(aGetScriptByte);
    // LD_addr_A(wMapBlocksPointer);
    // CALL(aGetScriptByte);
    // LD_addr_A(wMapBlocksPointer + 1);
    // CALL(aChangeMap);
    ChangeMap();
    // CALL(aBufferScreen);
    BufferScreen();
    // RET;
}

void Script_changeblock(script_s* s, uint8_t x, uint8_t y, uint8_t b){
    (void)s;
    // CALL(aGetScriptByte);
    // ADD_A(4);
    // LD_D_A;
    // CALL(aGetScriptByte);
    // ADD_A(4);
    // LD_E_A;
    // CALL(aGetBlockLocation);
    // CALL(aGetScriptByte);
    // LD_hl_A;
    *GetBlockLocation(x + 4, y + 4) = b;
    // CALL(aBufferScreen);
    BufferScreen();
    // RET;
}

void Script_reloadmappart(script_s* s){
    (void)s;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch();
    // CALL(aGetMovementPermissions);
    GetMovementPermissions();
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // RET;
}

void Script_warpcheck(script_s* s){
    (void)s;
    // CALL(aWarpCheck);
    // RET_NC ;
    if(!WarpCheck())
        return;
    // FARCALL(aEnableEvents);
    EnableEvents();
    // RET;
}

//  //  unreferenced
void Script_enableevents(void){
    // FARCALL(aEnableEvents);
    EnableEvents();
    // RET;
}

void Script_newloadmap(script_s* s, uint8_t method){
    (void)s;
    // CALL(aGetScriptByte);
    // LDH_addr_A(hMapEntryMethod);
    hram.hMapEntryMethod = method;
    // LD_A(MAPSTATUS_ENTER);
    // CALL(aLoadMapStatus);
    LoadMapStatus(MAPSTATUS_ENTER);
    // CALL(aStopScript);
    StopScript();
    // RET;
}

void Script_reloadend(script_s* s, uint8_t method){
    // CALL(aScript_newloadmap);
    Script_newloadmap(s, method);
    // JP(mScript_end);
    Script_end(s);
}

void Script_opentext(script_s* s){
    (void)s;
    // CALL(aOpenText);
    OpenText();
    // RET;
}

void Script_refreshscreen(script_s* s){
    (void)s;
    // CALL(aRefreshScreen);
    // CALL(aGetScriptByte);
    // RET;
    RefreshScreen();
}

// UNUSED
void Script_writeunusedbyte(script_s* s, uint8_t byte){
    (void)s;
    // CALL(aGetScriptByte);
    // LD_addr_A(wUnusedScriptByte);
    wram->wUnusedScriptByte = byte;
    // RET;
}

void UnusedClosetextScript(void){
//  //  unreferenced
    //closetext ['?']
}

void Script_closetext(script_s* s){
    (void)s;
    // CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap();
    // CALL(aCloseText);
    CloseText();
    // RET;
}

void Script_autoinput(script_s* s, const uint8_t* autoinput){
    (void)s;
    // Useless bank
    // CALL(aGetScriptByte);
    // PUSH_AF;
    // CALL(aGetScriptByte);
    // LD_L_A;
    // CALL(aGetScriptByte);
    // LD_H_A;
    // POP_AF;
    // CALL(aStartAutoInput);
    StartAutoInput(autoinput);
    // RET;
}

void Script_pause(script_s* s, uint8_t a) {
    (void)s;
    if(a != 0) {
        wram->wScriptDelay = a;
    }
    do {
        DelayFrames(2);
    } while(--wram->wScriptDelay != 0);
}

void Script_deactivatefacing(script_s* s, uint8_t delay){
    (void)s;
    // CALL(aGetScriptByte);
    // AND_A_A;
    // IF_Z goto no_time;
    if(delay != 0) {
        // LD_addr_A(wScriptDelay);
        wram->wScriptDelay = delay;
    }
// no_time:
    // LD_A(SCRIPT_WAIT);
    // LD_addr_A(wScriptMode);
    wram->wScriptMode = SCRIPT_WAIT;
    // CALL(aStopScript);
    StopScript();
    // RET;
}

void Script_stopandsjump(script_s* s, Script_fn_t script){
    // CALL(aStopScript);
    StopScript();
    // JP(mScript_sjump);
    Script_GotoPos(s, script, 0);
}

void Script_end(script_s* s){
    // CALL(aExitScriptSubroutine);
    // IF_C goto resume;
    // RET;
    if(!ExitScriptSubroutine(s)) {
    // resume:
        // XOR_A_A;
        // LD_addr_A(wScriptRunning);
        wram->wScriptRunning = 0;
        // LD_A(SCRIPT_OFF);
        // LD_addr_A(wScriptMode);
        wram->wScriptMode = SCRIPT_OFF;
        // LD_HL(wScriptFlags);
        // RES_hl(0);
        bit_reset(wram->wScriptFlags, 0);
        // CALL(aStopScript);
        StopScript();
        // RET;
    }

}

void Script_endcallback(script_s* s){
    // CALL(aExitScriptSubroutine);
    // IF_C goto dummy;
    ExitScriptSubroutine(s);
    // dummy:
    // LD_HL(wScriptFlags);
    // RES_hl(0);
    bit_reset(wram->wScriptFlags, 0);
    // CALL(aStopScript);
    StopScript();
    // RET;
}

//  Return false (c) if there's no parent to return to.
static bool ExitScriptSubroutine(script_s* s){
    // LD_HL(wScriptStackSize);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto done;
    if(s->stack_ptr == 0)
        return false;
    // DEC_hl;
    // LD_E_hl;
    // LD_D(0x0);
    // LD_HL(wScriptStack);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_B_A;
    // AND_A(0x7f);
    // LD_addr_A(wScriptBank);
    // LD_A_hli;
    // LD_E_A;
    // LD_addr_A(wScriptPos);
    // LD_A_hl;
    // LD_D_A;
    // LD_addr_A(wScriptPos + 1);
    // AND_A_A;
    // RET;
    Script_Pop(s);
    return true;

// done:
    // SCF;
    // RET;

}

void Script_endall(script_s* s){
    // XOR_A_A;
    // LD_addr_A(wScriptStackSize);
    s->fn = NULL;
    s->position = 0;
    s->stack_ptr = 0;
    s->stack[0].fn = NULL;
    s->stack[0].position = 0;
    // LD_addr_A(wScriptRunning);
    wram->wScriptRunning = 0;
    // LD_A(SCRIPT_OFF);
    // LD_addr_A(wScriptMode);
    wram->wScriptMode = SCRIPT_OFF;
    // LD_HL(wScriptFlags);
    // RES_hl(0);
    bit_reset(wram->wScriptFlags, 0);
    // CALL(aStopScript);
    StopScript();
    // RET;
}

void Script_halloffame(script_s* s){
    // LD_HL(wGameTimerPaused);
    // RES_hl(GAME_TIMER_PAUSED_F);
    bit_reset(wram->wGameTimerPaused, GAME_TIMER_PAUSED_F);
    // FARCALL(aStubbedTrainerRankings_HallOfFame);
    StubbedTrainerRankings_HallOfFame();
    // FARCALL(aStubbedTrainerRankings_HallOfFame2);
    StubbedTrainerRankings_HallOfFame2();
    // FARCALL(aHallOfFame);
    HallOfFame();
    // LD_HL(wGameTimerPaused);
    // SET_hl(GAME_TIMER_PAUSED_F);
    bit_set(wram->wGameTimerPaused, GAME_TIMER_PAUSED_F);
    // JR(mReturnFromCredits);
    return ReturnFromCredits(s);
}

void Script_credits(script_s* s){
    // FARCALL(aRedCredits);
    RedCredits();
    // return ReturnFromCredits();
    return ReturnFromCredits(s);
}

void ReturnFromCredits(script_s* s){
    // CALL(aScript_endall);
    Script_endall(s);
    // LD_A(MAPSTATUS_DONE);
    // CALL(aLoadMapStatus);
    LoadMapStatus(MAPSTATUS_DONE);
    // CALL(aStopScript);
    StopScript();
    // RET;
}

void Script_wait(script_s* s, uint8_t a){
    (void)s;
    // PUSH_BC;
    // CALL(aGetScriptByte);

    do {
    // loop:
        // PUSH_AF;
        // LD_C(6);
        // CALL(aDelayFrames);
        DelayFrames(6);
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // POP_BC;
    // RET;
}

void Script_checksave(script_s* s){
    (void)s;
    // FARCALL(aCheckSave);
    // LD_A_C;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = CheckSave();
    // RET;
}

void Script_checkver_duplicate(void){
//  //  unreferenced
    // LD_A_addr(mScript_checkver_duplicate_gs_version);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = GS_VERSION;
    // RET;

// gs_version:
    //db ['GS_VERSION'];

}
