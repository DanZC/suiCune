#pragma once
#define SCRIPT_MAX_FARLABELS    128

#define SCRIPT_BEGIN            switch(s->position) { case 0:
#define SCRIPT_RET              s->position = SCRIPT_MAX_FARLABELS + __LINE__ ; Script_Ret(s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_END              default: break; } return true;
#define SCRIPT_CALL(_s)         s->position = SCRIPT_MAX_FARLABELS + __LINE__; Script_CallScript(s, _s); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_CALLGOTO(_s, _p) s->position = SCRIPT_MAX_FARLABELS + __LINE__; Script_CallScriptPos(s, _s, _p); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_GOTOPOS(_s, _p)  Script_GotoPos(s, _s, _p); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_END2             s->position = SCRIPT_MAX_FARLABELS + __LINE__; return true; case SCRIPT_MAX_FARLABELS + __LINE__: return true;
#define SCRIPT_EVCMD(_cmd, ...) s->position = SCRIPT_MAX_FARLABELS + __LINE__; _cmd(s, ##__VA_ARGS__); return false; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_IFTRUE(_s)       s->position = SCRIPT_MAX_FARLABELS + __LINE__; if(wram->wScriptVar) Script_Goto(s, _s); return; case SCRIPT_MAX_FARLABELS + __LINE__:
#define SCRIPT_FALLTHROUGH(_s)  default: Script_Goto(s, _s); return false; } return true;

#define writetext(_t)       SCRIPT_EVCMD(Script_writetext_Conv, _t)
#define checkscene          SCRIPT_EVCMD(Script_checkscene_Conv)
#define pause(_a)           SCRIPT_EVCMD(Script_pause_Conv, _a)
#define waitsfx             SCRIPT_EVCMD(Script_waitsfx_Conv)
#define playsound(_sfx)     SCRIPT_EVCMD(Script_playsound_Conv, _sfx)
#define setflag(_flag)      SCRIPT_EVCMD(Script_setflag_Conv, _flag)
#define clearflag(_flag)    SCRIPT_EVCMD(Script_clearflag_Conv, _flag)
#define checkflag(_flag)    SCRIPT_EVCMD(Script_checkflag_Conv, _flag)
#define scall(_f)           SCRIPT_CALL(_f)
#define scall_far(_f, _p)   SCRIPT_CALLGOTO(_f, _p)
#define end                 SCRIPT_END2
#define getcurlandmarkname  SCRIPT_EVCMD(Script_getcurlandmarkname_Conv)
#define ret                 SCRIPT_RET

#define far_label(_name)    case _name: