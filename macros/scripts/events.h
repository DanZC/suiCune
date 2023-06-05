// ScriptCommandTable indexes (see engine/overworld/scripting.asm)
#define _dw(_w) LOW(_w), HIGH(_w)
#define _dba(_a) BANK(a##_a), _dw(m##_a)
#define _dt(_t) _dw(_t), (((_t) >> 16) & 0xff)
#define MAP_ID(_a) MAPGROUP_##_a, MAP_##_a

#define overloadselect2(_1,_2,NAME,...) NAME
#define overloadselect3(_1,_2,_3,NAME,...) NAME
#define overloadselect6(_1,_2,_3,_4,_5,_6,NAME,...) NAME

enum {
    CMD_SCALL, // $00
    CMD_FARSCALL, // $01
    CMD_MEMCALL, // $02
    CMD_SJUMP, // $03
    CMD_FARSJUMP, // $04
    CMD_MEMJUMP, // $05
    CMD_IFEQUAL, // $06
    CMD_IFNOTEQUAL, // $07
    CMD_IFFALSE, // $08
    CMD_IFTRUE, // $09
    CMD_IFGREATER, // $0a
    CMD_IFLESS, // $0b
    CMD_JUMPSTD, // $0c
    CMD_CALLSTD, // $0d
    CMD_CALLASM, // $0e
    CMD_SPECIAL, // $0f
    CMD_MEMCALLASM, // $10
    CMD_CHECKMAPSCENE, // $11
    CMD_SETMAPSCENE, // $12
    CMD_CHECKSCENE, // $13
    CMD_SETSCENE, // $14
    CMD_SETVAL, // $15
    CMD_ADDVAL, // $16
    CMD_RANDOM, // $17
    CMD_CHECKVER, // $18
    CMD_READMEM, // $19
    CMD_WRITEMEM, // $1a
    CMD_LOADMEM, // $1b
    CMD_READVAR, // $1c
    CMD_WRITEVAR, // $1d
    CMD_LOADVAR, // $1e
    CMD_GIVEITEM, // $1f
    CMD_TAKEITEM, // $20
    CMD_CHECKITEM, // $21
    CMD_GIVEMONEY, // $22
    CMD_TAKEMONEY, // $23
    CMD_CHECKMONEY, // $24
    CMD_GIVECOINS, // $25
    CMD_TAKECOINS, // $26
    CMD_CHECKCOINS, // $27
    CMD_ADDCELLNUM, // $28
    CMD_DELCELLNUM, // $29
    CMD_CHECKCELLNUM, // $2a
    CMD_CHECKTIME, // $2b
    CMD_CHECKPOKE, // $2c
    CMD_GIVEPOKE, // $2d
    CMD_GIVEEGG, // $2e
    CMD_GIVEPOKEMAIL, // $2f
    CMD_CHECKPOKEMAIL, // $30
    CMD_CHECKEVENT, // $31
    CMD_CLEAREVENT, // $32
    CMD_SETEVENT, // $33
    CMD_CHECKFLAG, // $34
    CMD_CLEARFLAG, // $35
    CMD_SETFLAG, // $36
    CMD_WILDON, // $37
    CMD_WILDOFF, // $38
    CMD_XYCOMPARE, // $39
    CMD_WARPMOD, // $3a
    CMD_BLACKOUTMOD, // $3b
    CMD_WARP, // $3c
    CMD_GETMONEY, // $3d
    CMD_GETCOINS, // $3e
    CMD_GETNUM, // $3f
    CMD_GETMONNAME, // $40
    CMD_GETITEMNAME, // $41
    CMD_GETCURLANDMARKNAME, // $42
    CMD_GETTRAINERNAME, // $43
    CMD_GETSTRING, // $44
    CMD_ITEMNOTIFY, // $45
    CMD_POCKETISFULL, // $46
    CMD_OPENTEXT, // $47
    CMD_REFRESHSCREEN, // $48
    CMD_CLOSETEXT, // $49
    CMD_WRITEUNUSEDBYTE, // $4a
    CMD_FARWRITETEXT, // $4b
    CMD_WRITETEXT, // $4c
    CMD_REPEATTEXT, // $4d
    CMD_YESORNO, // $4e
    CMD_LOADMENU, // $4f
    CMD_CLOSEWINDOW, // $50
    CMD_JUMPTEXTFACEPLAYER, // $51
    CMD_FARJUMPTEXT, // $52
    CMD_JUMPTEXT, // $53
    CMD_WAITBUTTON, // $54
    CMD_PROMPTBUTTON, // $55
    CMD_POKEPIC, // $56
    CMD_CLOSEPOKEPIC, // $57
    CMD__2DMENU, // $58
    CMD_VERTICALMENU, // $59
    CMD_LOADPIKACHUDATA, // $5a
    CMD_RANDOMWILDMON, // $5b
    CMD_LOADTEMPTRAINER, // $5c
    CMD_LOADWILDMON, // $5d
    CMD_LOADTRAINER, // $5e
    CMD_STARTBATTLE, // $5f
    CMD_RELOADMAPAFTERBATTLE, // $60
    CMD_CATCHTUTORIAL, // $61
    CMD_TRAINERTEXT, // $62
    CMD_TRAINERFLAGACTION, // $63
    CMD_WINLOSSTEXT, // $64
    CMD_SCRIPTTALKAFTER, // $65
    CMD_ENDIFJUSTBATTLED, // $66
    CMD_CHECKJUSTBATTLED, // $67
    CMD_SETLASTTALKED, // $68
    CMD_APPLYMOVEMENT, // $69
    CMD_APPLYMOVEMENTLASTTALKED, // $6a
    CMD_FACEPLAYER, // $6b
    CMD_FACEOBJECT, // $6c
    CMD_VARIABLESPRITE, // $6d
    CMD_DISAPPEAR, // $6e
    CMD_APPEAR, // $6f
    CMD_FOLLOW, // $70
    CMD_STOPFOLLOW, // $71
    CMD_MOVEOBJECT, // $72
    CMD_WRITEOBJECTXY, // $73
    CMD_LOADEMOTE, // $74
    CMD_SHOWEMOTE, // $75
    CMD_TURNOBJECT, // $76
    CMD_FOLLOWNOTEXACT, // $77
    CMD_EARTHQUAKE, // $78
    CMD_CHANGEMAPBLOCKS, // $79
    CMD_CHANGEBLOCK, // $7a
    CMD_RELOADMAP, // $7b
    CMD_RELOADMAPPART, // $7c
    CMD_WRITECMDQUEUE, // $7d
    CMD_DELCMDQUEUE, // $7e
    CMD_PLAYMUSIC, // $7f
    CMD_ENCOUNTERMUSIC, // $80
    CMD_MUSICFADEOUT, // $81
    CMD_PLAYMAPMUSIC, // $82
    CMD_DONTRESTARTMAPMUSIC, // $83
    CMD_CRY, // $84
    CMD_PLAYSOUND, // $85
    CMD_WAITSFX, // $86
    CMD_WARPSOUND, // $87
    CMD_SPECIALSOUND, // $88
    CMD_AUTOINPUT, // $89
    CMD_NEWLOADMAP, // $8a
    CMD_PAUSE, // $8b
    CMD_DEACTIVATEFACING, // $8c
    CMD_SDEFER, // $8d
    CMD_WARPCHECK, // $8e
    CMD_STOPANDSJUMP, // $8f
    CMD_ENDCALLBACK, // $90
    CMD_END, // $91
    CMD_RELOADEND, // $92
    CMD_ENDALL, // $93
    CMD_POKEMART, // $94
    CMD_ELEVATOR, // $95
    CMD_TRADE, // $96
    CMD_ASKFORPHONENUMBER, // $97
    CMD_PHONECALL, // $98
    CMD_HANGUP, // $99
    CMD_DESCRIBEDECORATION, // $9a
    CMD_FRUITTREE, // $9b
    CMD_SPECIALPHONECALL, // $9c
    CMD_CHECKPHONECALL, // $9d
    CMD_VERBOSEGIVEITEM, // $9e
    CMD_VERBOSEGIVEITEMVAR, // $9f
    CMD_SWARM, // $a0
    CMD_HALLOFFAME, // $a1
    CMD_CREDITS, // $a2
    CMD_WARPFACING, // $a3
    CMD_BATTLETOWERTEXT, // $a4
    CMD_GETLANDMARKNAME, // $a5
    CMD_GETTRAINERCLASSNAME, // $a6
    CMD_GETNAME, // $a7
    CMD_WAIT, // $a8
    CMD_CHECKSAVE, // $a9
};
#define ev_scall(_a1) CMD_SCALL, _dw(_a1)
#define ev_farscall(_a1) CMD_FARSCALL, _dba(_a1)
#define ev_memcall(_a1) CMD_MEMCALL, _dw(_a1)
#define ev_sjump(_a1) CMD_SJUMP, _dw(_a1)
#define ev_farsjump(_a1) CMD_FARSJUMP, _dba(_a1)
#define ev_memjump(_a1) CMD_MEMJUMP, _dw(_a1)
#define ev_ifequal(_a1, _a2) CMD_IFEQUAL, _a1, _dw(_a2)
#define ev_ifnotequal(_a1, _a2) CMD_IFNOTEQUAL, _a1, _dw(_a2)
#define ev_iffalse(_a1) CMD_IFFALSE, _dw(_a1)
#define ev_iftrue(_a1) CMD_IFTRUE, _dw(_a1)
#define ev_ifgreater(_a1, _a2) CMD_IFGREATER, _a1, _dw(_a2)
#define ev_ifless(_a1, _a2) CMD_IFLESS, _a1, _dw(_a2)
#define ev_jumpstd(_a1) CMD_JUMPSTD, _dw((a##_a1##StdScript - aStdScripts) / 3)
#define ev_callstd(_a1) CMD_CALLSTD, _dw((a##_a1##StdScript - aStdScripts) / 3)
#define ev_callasm(_a1) CMD_CALLASM, _dba(_a1)
#define ev_special(_a1) CMD_SPECIAL, _dw((a##_a1##Special - aSpecialsPointers) / 3)
#define ev_memcallasm(_a1) CMD_MEMCALLASM, _dw(_a1)
#define ev_checkmapscene(_a1) CMD_CHECKMAPSCENE, MAP_ID(_a1)
#define ev_setmapscene(_a1, _a2) CMD_SETMAPSCENE, MAP_ID(_a1), _a2
#define ev_checkscene CMD_CHECKSCENE
#define ev_setscene(_a1) CMD_SETSCENE, _a1
#define ev_setval(_a1) CMD_SETVAL, _a1
#define ev_addval(_a1) CMD_ADDVAL, _a1
#define ev_random(_a1) CMD_RANDOM, _a1
#define ev_checkver CMD_CHECKVER
#define ev_readmem(_a1) CMD_READMEM, _dw(_a1)
#define ev_writemem(_a1) CMD_WRITEMEM, _dw(_a1)
#define ev_loadmem(_a1, _a2) CMD_LOADMEM, _dw(_a1), _a2
#define ev_readvar(_a1) CMD_READVAR, _a1
#define ev_writevar(_a1) CMD_WRITEVAR, _a1
#define ev_loadvar(_a1, _a2) CMD_LOADVAR, _a1, _a2
#define ev_giveitem1(_a1, _a2) CMD_GIVEITEM, _a1, _a2
#define ev_giveitem2(_a1) CMD_GIVEITEM, _a1, 1
#define ev_giveitem(...) overloadselect2(__VA_ARGS__, ev_giveitem2, ev_giveitem1)(__VA_ARGS__)
#define ev_takeitem1(_a1, _a2) CMD_TAKEITEM, _a1, _a2
#define ev_takeitem2(_a1) CMD_TAKEITEM, _a1, 1
#define ev_takeitem(...) overloadselect2(__VA_ARGS__, ev_takeitem2, ev_takeitem1)(__VA_ARGS__)
#define ev_checkitem(_a1) CMD_CHECKITEM, _a1
#define ev_givemoney(_a1, _a2) CMD_GIVEMONEY, _a1, _dt(_a2)
#define ev_takemoney(_a1, _a2) CMD_TAKEMONEY, _a1, _dt(_a2)
#define ev_checkmoney(_a1, _a2) CMD_CHECKMONEY, _a1, _dt(_a2)
#define ev_givecoins(_a1) CMD_GIVECOINS, _dw(_a1)
#define ev_takecoins(_a1) CMD_TAKECOINS, _dw(_a1)
#define ev_checkcoins(_a1) CMD_CHECKCOINS, _dw(_a1)
#define ev_addcellnum(_a1) CMD_ADDCELLNUM, _a1
#define ev_delcellnum(_a1) CMD_DELCELLNUM, _a1
#define ev_checkcellnum(_a1) CMD_CHECKCELLNUM, _a1
#define ev_checktime(_a1) CMD_CHECKTIME, _a1
#define ev_checkpoke(_a1) CMD_CHECKPOKE, _a1
#define ev_givepoke2(_a1, _a2) CMD_GIVEPOKE, _a1, _a2, NO_ITEM, FALSE
#define ev_givepoke3(_a1, _a2, _a3) CMD_GIVEPOKE, _a1, _a2, _a3, FALSE
#define ev_givepoke5(_a1, _a2, _a3, _a4, _a5) CMD_GIVEPOKE, _a1, _a2, _a3, TRUE, _dw(_a4), _dw(_a5)
#define ev_givepoke6(_a1, _a2, _a3, _a4, _a5, _a6) CMD_GIVEPOKE, _a1, _a2, _a3, _a4, _dw(_a5), _dw(_a6)
#define ev_givepoke(...) overloadselect6(__VA_ARGS__, ev_givepoke6, ev_givepoke5, error, ev_givepoke3, ev_givepoke2, error)(__VA_ARGS__)
#define ev_giveegg(_a1, _a2) CMD_GIVEEGG, _a1, _a2
#define ev_givepokemail(_a1) CMD_GIVEPOKEMAIL, _dw(_a1)
#define ev_checkpokemail(_a1) CMD_CHECKPOKEMAIL, _dw(_a1)
#define ev_checkevent(_a1) CMD_CHECKEVENT, _dw(_a1)
#define ev_clearevent(_a1) CMD_CLEAREVENT, _dw(_a1)
#define ev_setevent(_a1) CMD_SETEVENT, _dw(_a1)
#define ev_checkflag(_a1) CMD_CHECKFLAG, _dw(_a1)
#define ev_clearflag(_a1) CMD_CLEARFLAG, _dw(_a1)
#define ev_setflag(_a1) CMD_SETFLAG, _dw(_a1)
#define ev_wildon CMD_WILDON
#define ev_wildoff CMD_WILDOFF
#define ev_xycompare(_a1) CMD_XYCOMPARE, _dw(_a1)
#define ev_warpmod(_a1, _a2) CMD_WARPMOD, _a1, MAP_ID(_a2)
#define ev_blackoutmod(_a1) CMD_BLACKOUTMOD, MAP_ID(_a1)
#define ev_warp(_a1, _a2, _a3) CMD_WARP, MAP_ID(_a1), _a2, _a3
#define ev_getmoney(_a1, _a2) CMD_GETMONEY, _a2, _a1
#define ev_getcoins(_a1) CMD_GETCOINS, _a1
#define ev_getnum(_a1) CMD_GETNUM, _a1
#define ev_getmonname(_a1, _a2) CMD_GETMONNAME, _a2, _a1
#define ev_getitemname(_a1, _a2) CMD_GETITEMNAME, _a2, _a1
#define ev_getcurlandmarkname(_a1) CMD_GETCURLANDMARKNAME, _a1
#define ev_gettrainername(_a1, _a2, _a3) CMD_GETTRAINERNAME, _a2, _a3, _a1
#define ev_getstring(_a1, _a2) CMD_GETSTRING, _dw(_a2), _a1
#define ev_itemnotify CMD_ITEMNOTIFY
#define ev_pocketisfull CMD_POCKETISFULL
#define ev_opentext CMD_OPENTEXT
#define ev_refreshscreen CMD_REFRESHSCREEN, 0
#define ev_refreshscreen1(_a1) CMD_REFRESHSCREEN, _a1
#define ev_closetext CMD_CLOSETEXT
#define ev_writeunusedbyte(_a1) CMD_WRITEUNUSEDBYTE, _a1
#define ev_farwritetext(_a1) CMD_FARWRITETEXT, _dba(_a1)
#define ev_writetext(_a1) CMD_WRITETEXT, _dw(_a1)
#define ev_repeattext(_a1, _a2) CMD_REPEATTEXT, _a1, _a2
#define ev_yesorno CMD_YESORNO
#define ev_loadmenu(_a1) CMD_LOADMENU, _dw(_a1)
#define ev_closewindow CMD_CLOSEWINDOW
#define ev_jumptextfaceplayer(_a1) CMD_JUMPTEXTFACEPLAYER, _dw(_a1)
#define ev_farjumptext(_a1) CMD_FARJUMPTEXT, _dba(_a1)
#define ev_jumptext(_a1) CMD_JUMPTEXT, _dw(_a1)
#define ev_waitbutton CMD_WAITBUTTON
#define ev_promptbutton CMD_PROMPTBUTTON
#define ev_pokepic(_a1) CMD_POKEPIC, _a1
#define ev_closepokepic CMD_CLOSEPOKEPIC
#define ev__2dmenu CMD__2DMENU
#define ev_verticalmenu CMD_VERTICALMENU
#define ev_loadpikachudata CMD_LOADPIKACHUDATA
#define ev_randomwildmon CMD_RANDOMWILDMON
#define ev_loadtemptrainer CMD_LOADTEMPTRAINER
#define ev_loadwildmon(_a1, _a2) CMD_LOADWILDMON, _a1, _a2
#define ev_loadtrainer(_a1, _a2) CMD_LOADTRAINER, _a1, _a2
#define ev_startbattle CMD_STARTBATTLE
#define ev_reloadmapafterbattle CMD_RELOADMAPAFTERBATTLE
#define ev_catchtutorial(_a1) CMD_CATCHTUTORIAL, _a1
#define ev_trainertext(_a1) CMD_TRAINERTEXT, _a1
#define ev_trainerflagaction(_a1) CMD_TRAINERFLAGACTION, _a1
#define ev_winlosstext(_a1, _a2) CMD_WINLOSSTEXT, _dw(_a1), _dw(_a2)
#define ev_scripttalkafter CMD_SCRIPTTALKAFTER
#define ev_endifjustbattled CMD_ENDIFJUSTBATTLED
#define ev_checkjustbattled CMD_CHECKJUSTBATTLED
#define ev_setlasttalked(_a1) CMD_SETLASTTALKED, _a1
#define ev_applymovement(_a1, _a2) CMD_APPLYMOVEMENT, _a1, _dw(_a2)
#define ev_applymovementlasttalked(_a1) CMD_APPLYMOVEMENTLASTTALKED, _dw(_a1)
#define ev_faceplayer CMD_FACEPLAYER
#define ev_faceobject(_a1, _a2) CMD_FACEOBJECT, _a1, _a2
#define ev_variablesprite(_a1, _a2) CMD_VARIABLESPRITE, _a1, _a2
#define ev_disappear(_a1) CMD_DISAPPEAR, _a1
#define ev_appear(_a1) CMD_APPEAR, _a1
#define ev_follow(_a1, _a2) CMD_FOLLOW, _a1, _a2
#define ev_stopfollow CMD_STOPFOLLOW
#define ev_moveobject(_a1, _a2, _a3) CMD_MOVEOBJECT, _a1, _a2, _a3
#define ev_writeobjectxy(_a1) CMD_WRITEOBJECTXY, _a1
#define ev_loademote(_a1) CMD_LOADEMOTE, _a1
#define ev_showemote(_a1, _a2, _a3) CMD_SHOWEMOTE, _a1, _a2, _a3
#define ev_turnobject(_a1, _a2) CMD_TURNOBJECT, _a1, _a2
#define ev_follownotexact(_a1, _a2) CMD_FOLLOWNOTEXACT, _a1, _a2
#define ev_earthquake(_a1) CMD_EARTHQUAKE, _a1
#define ev_changemapblocks(_a1) CMD_CHANGEMAPBLOCKS, _dba(_a1)
#define ev_changeblock(_a1, _a2, _a3) CMD_CHANGEBLOCK, _a1, _a2, _a3
#define ev_reloadmap CMD_RELOADMAP
#define ev_reloadmappart CMD_RELOADMAPPART
#define ev_writecmdqueue(_a1) CMD_WRITECMDQUEUE, _dw(_a1)
#define ev_delcmdqueue(_a1) CMD_DELCMDQUEUE, _a1
#define ev_playmusic(_a1) CMD_PLAYMUSIC, _dw(_a1)
#define ev_encountermusic CMD_ENCOUNTERMUSIC
#define ev_musicfadeout(_a1, _a2) CMD_MUSICFADEOUT, _dw(_a1), _a2
#define ev_playmapmusic CMD_PLAYMAPMUSIC
#define ev_dontrestartmapmusic CMD_DONTRESTARTMAPMUSIC
#define ev_cry(_a1) CMD_CRY, _dw(_a1)
#define ev_playsound(_a1) CMD_PLAYSOUND, _dw(_a1)
#define ev_waitsfx CMD_WAITSFX
#define ev_warpsound CMD_WARPSOUND
#define ev_specialsound CMD_SPECIALSOUND
#define ev_autoinput(_a1) CMD_AUTOINPUT, _dba(_a1)
#define ev_newloadmap(_a1) CMD_NEWLOADMAP, _a1
#define ev_pause(_a1) CMD_PAUSE, _a1
#define ev_deactivatefacing(_a1) CMD_DEACTIVATEFACING, _a1
#define ev_sdefer(_a1) CMD_SDEFER, _dw(_a1)
#define ev_warpcheck CMD_WARPCHECK
#define ev_stopandsjump(_a1) CMD_STOPANDSJUMP, _dw(_a1)
#define ev_endcallback CMD_ENDCALLBACK
#define ev_end CMD_END
#define ev_reloadend(_a1) CMD_RELOADEND, _a1
#define ev_endall CMD_ENDALL
#define ev_pokemart(_a1, _a2) CMD_POKEMART, _a1, _dw(_a2)
#define ev_elevator(_a1) CMD_ELEVATOR, _dw(_a1)
#define ev_trade(_a1) CMD_TRADE, _a1
#define ev_askforphonenumber(_a1) CMD_ASKFORPHONENUMBER, _a1
#define ev_phonecall(_a1) CMD_PHONECALL, _dw(_a1)
#define ev_hangup CMD_HANGUP
#define ev_describedecoration(_a1) CMD_DESCRIBEDECORATION, _a1
#define ev_fruittree(_a1) CMD_FRUITTREE, _a1
#define ev_specialphonecall(_a1) CMD_SPECIALPHONECALL, _dw(_a1)
#define ev_checkphonecall CMD_CHECKPHONECALL
#define ev_verbosegiveitem2(_a1, _a2) CMD_VERBOSEGIVEITEM, _a1, _a2
#define ev_verbosegiveitem1(_a1) CMD_VERBOSEGIVEITEM, _a1, 1
#define ev_verbosegiveitem(...) overloadselect2(__VA_ARGS__, ev_verbosegiveitem2, ev_verbosegiveitem1)(__VA_ARGS__)
#define ev_verbosegiveitemvar(_a1, _a2) CMD_VERBOSEGIVEITEMVAR, _a1, _a2
#define ev_swarm(_a1, _a2) CMD_SWARM, _a1, MAP_ID(_a2)
#define ev_halloffame CMD_HALLOFFAME
#define ev_credits CMD_CREDITS
#define ev_warpfacing(_a1, _a2, _a3, _a4) CMD_WARPFACING, _a1, MAP_ID(_a2), _a3, _a4
#define ev_battletowertext(_a1) CMD_BATTLETOWERTEXT, _a1
#define ev_getlandmarkname(_a1, _a2) CMD_GETLANDMARKNAME, _a2, _a1
#define ev_gettrainerclassname(_a1, _a2) CMD_GETTRAINERCLASSNAME, _a2, _a1
#define ev_getname(_a1, _a2, _a3) CMD_GETNAME, _a2, _a3, _a1
#define ev_wait(_a1) CMD_WAIT, _a1
#define ev_checksave CMD_CHECKSAVE
