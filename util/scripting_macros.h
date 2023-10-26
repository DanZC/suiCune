#pragma once
#define SCRIPT_MAX_FARLABELS    128

#define SCRIPT_BEGIN            switch(s->position) { case 0:
#define SCRIPT_RET              s->position = SCRIPT_MAX_FARLABELS + __LINE__ ; Script_end_Conv(s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_END              default: break; } return true;
#define SCRIPT_CALL(_s)         s->position = SCRIPT_MAX_FARLABELS + __LINE__; Script_CallScript(s, _s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_CALLGOTO(_s, _p) s->position = SCRIPT_MAX_FARLABELS + __LINE__; Script_CallScriptPos(s, _s, _p); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_GOTOPOS(_s, _p)  Script_GotoPos(s, _s, _p); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_END2             s->position = SCRIPT_MAX_FARLABELS + __LINE__; Script_end_Conv(s); return true; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_ENDCALLBACK      s->position = SCRIPT_MAX_FARLABELS + __LINE__; Script_endcallback_Conv(s); return true; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_EVCMD(_cmd, ...) s->position = SCRIPT_MAX_FARLABELS + __LINE__; _cmd(s, ##__VA_ARGS__); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_IFTRUE(_s)       s->position = SCRIPT_MAX_FARLABELS + __LINE__; if(wram->wScriptVar) Script_Goto(s, _s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_IFFALSE(_s)      s->position = SCRIPT_MAX_FARLABELS + __LINE__; if(!wram->wScriptVar) Script_Goto(s, _s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_IFEQUAL(_v,_s)   s->position = SCRIPT_MAX_FARLABELS + __LINE__; if(wram->wScriptVar == (_v)) Script_Goto(s, _s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_IFNEQUAL(_v,_s)  s->position = SCRIPT_MAX_FARLABELS + __LINE__; if(wram->wScriptVar != (_v)) Script_Goto(s, _s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_IFLESS(_v,_s)    s->position = SCRIPT_MAX_FARLABELS + __LINE__; if(wram->wScriptVar <  (_v)) Script_Goto(s, _s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_IFGREATER(_v,_s) s->position = SCRIPT_MAX_FARLABELS + __LINE__; if(wram->wScriptVar >  (_v)) Script_Goto(s, _s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_FALLTHROUGH(_s)  default: Script_Goto(s, _s); return false; } return true;

#define writetext(_t)           SCRIPT_EVCMD(Script_writetext_Conv, _t)
#define jumptext(_t)            SCRIPT_EVCMD(Script_jumptext_Conv, _t)
#define jumptextfaceplayer(_t)  SCRIPT_EVCMD(Script_jumptextfaceplayer_Conv, _t)
#define checkscene              SCRIPT_EVCMD(Script_checkscene_Conv)
#define pause(_a)               SCRIPT_EVCMD(Script_pause_Conv, _a)
#define promptbutton            SCRIPT_EVCMD(Script_promptbutton_Conv)
#define waitsfx                 SCRIPT_EVCMD(Script_waitsfx_Conv)
#define playsound(_sfx)         SCRIPT_EVCMD(Script_playsound_Conv, _sfx)
#define specialsound            SCRIPT_EVCMD(Script_specialsound_Conv)
#define playmusic(_music)       SCRIPT_EVCMD(Script_playmusic_Conv, _music)
#define itemnotify              SCRIPT_EVCMD(Script_itemnotify_Conv)
#define pocketisfull            SCRIPT_EVCMD(Script_pocketisfull_Conv)
#define setscene(_sc)           SCRIPT_EVCMD(Script_setscene_Conv, _sc)
#define setmapscene(_map, _sc)  SCRIPT_EVCMD(Script_setmapscene_Conv, MAP_ID(_map), _sc)
#define setevent(_flag)         SCRIPT_EVCMD(Script_setevent_Conv, _flag)
#define clearevent(_flag)       SCRIPT_EVCMD(Script_clearevent_Conv, _flag)
#define checkevent(_flag)       SCRIPT_EVCMD(Script_checkevent_Conv, _flag)
#define setflag(_flag)          SCRIPT_EVCMD(Script_setflag_Conv, _flag)
#define clearflag(_flag)        SCRIPT_EVCMD(Script_clearflag_Conv, _flag)
#define checkflag(_flag)        SCRIPT_EVCMD(Script_checkflag_Conv, _flag)
#define readvar(_var)           SCRIPT_EVCMD(Script_readvar_Conv, _var)
#define writevar(_var)          SCRIPT_EVCMD(Script_writevar_Conv, _var)
#define loadvar(_var, _value)   SCRIPT_EVCMD(Script_loadvar_Conv, _var, _value)
#define readmem(_ptr)           SCRIPT_EVCMD(Script_readmem_Conv, _ptr)
#define writemem(_ptr)          SCRIPT_EVCMD(Script_writemem_Conv, _ptr)
#define loadmem(_ptr, _value)   SCRIPT_EVCMD(Script_loadmem_Conv, _ptr, _value)
#define setval(_value)          SCRIPT_EVCMD(Script_setval_Conv, _value)
#define addval(_value)          SCRIPT_EVCMD(Script_addval_Conv, _value)
#define srandom(_value)         SCRIPT_EVCMD(Script_random_Conv, _value)
#define scall(_f)               SCRIPT_CALL(_f)
#define scall_far(_f, _p)       SCRIPT_CALLGOTO(_f, _p)
#define sjump(_f)               SCRIPT_GOTOPOS(_f, 0)
#define sjump_far(_f, _p)       SCRIPT_GOTOPOS(_f, _p)
#define s_endcallback           SCRIPT_ENDCALLBACK
#define s_end                   SCRIPT_END2
#define s_endall                SCRIPT_EVCMD(Script_endall_Conv)
#define jumpstd(_std)           SCRIPT_EVCMD(Script_jumpstd_Conv, _std)
#define callstd(_std)           SCRIPT_EVCMD(Script_callstd_Conv, _std)
#define special(_s)             SCRIPT_EVCMD(Script_special_Conv, SP_##_s)
#define getmonname(_mon, _b)    SCRIPT_EVCMD(Script_getmonname_Conv, _mon, _b)
#define getitemname(_item, _b)  SCRIPT_EVCMD(Script_getitemname_Conv, _item, _b)
#define gettrainername(b,c,a)   SCRIPT_EVCMD(Script_gettrainername_Conv, b, c, a)
#define gettrainerclassname(b,c)SCRIPT_EVCMD(Script_gettrainerclassname_Conv, b, c)
#define getcurlandmarkname(b)   SCRIPT_EVCMD(Script_getcurlandmarkname_Conv, b)
#define getlandmarkname(_a, _b) SCRIPT_EVCMD(Script_getlandmarkname_Conv, _a, _b)
#define getstring(_b, _str)     SCRIPT_EVCMD(Script_getstring_Conv, _b, _str)
#define getnum(_num)            SCRIPT_EVCMD(Script_getnum_Conv, _num)
#define faceplayer              SCRIPT_EVCMD(Script_faceplayer_Conv)
#define refreshscreen           SCRIPT_EVCMD(Script_refreshscreen_Conv)
#define opentext                SCRIPT_EVCMD(Script_opentext_Conv)
#define repeattext(_hl)         SCRIPT_EVCMD(Script_repeattext_Conv, _hl)
#define closetext               SCRIPT_EVCMD(Script_closetext_Conv)
#define waitbutton              SCRIPT_EVCMD(Script_waitbutton_Conv)
#define setlasttalked(_o)       SCRIPT_EVCMD(Script_setlasttalked_Conv, _o)
#define applymovement(_o, _mv)  SCRIPT_EVCMD(Script_applymovement_Conv, _o, _mv)
#define autoinput(_hl)          SCRIPT_EVCMD(Script_autoinput_Conv, _hl)
#define variablesprite(_i, _s)  SCRIPT_EVCMD(Script_variablesprite_Conv, _i, _s)
#define earthquake(_m)          SCRIPT_EVCMD(Script_earthquake_Conv, _m)
#define randomwildmon           SCRIPT_EVCMD(Script_randomwildmon_Conv)
#define startbattle             SCRIPT_EVCMD(Script_startbattle_Conv)
#define checktime(_time)        SCRIPT_EVCMD(Script_checktime_Conv, _time)
#define checkitem(_item)        SCRIPT_EVCMD(Script_checkitem_Conv, _item)
#define specialphonecall(_id)   SCRIPT_EVCMD(Script_specialphonecall_Conv, _id)
#define checkphonecall          SCRIPT_EVCMD(Script_checkphonecall_Conv)
#define checkmoney(_act, _amt)  SCRIPT_EVCMD(Script_checkmoney_Conv, _act, _amt)
#define wait(_n)                SCRIPT_EVCMD(Script_wait_Conv, _n)
#define s_ret                   SCRIPT_RET
#define iftrue_jump(_s)         SCRIPT_IFTRUE(_s)
#define iffalse_jump(_s)        SCRIPT_IFFALSE(_s)
#define ifequal_jump(_v, _s)    SCRIPT_IFEQUAL(_v, _s)
#define ifnotequal_jump(_v, _s) SCRIPT_IFNEQUAL(_v, _s)
#define ifless_jump(_v, _s)     SCRIPT_IFLESS(_v, _s)
#define ifgreater_jump(_v, _s)  SCRIPT_IFGREATER(_v, _s)
#define iftrue(_s)              if(wram->wScriptVar) goto _s;
#define iffalse(_s)             if(!wram->wScriptVar) goto _s;
#define ifequal(_v, _s)         if(wram->wScriptVar == (_v)) goto _s;
#define ifnotequal(_v, _s)      if(wram->wScriptVar != (_v)) goto _s;
#define ifless(_v, _s)          if(wram->wScriptVar < (_v)) goto _s;
#define ifgreater(_v, _s)       if(wram->wScriptVar > (_v)) goto _s;

#define far_label(_name)    case _name: