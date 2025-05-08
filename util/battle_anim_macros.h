#pragma once
#define ANIM_BEGIN                  switch(anim->pos) { case 0:
#define ANIM_END                    default: break; } return 0x1;
#define ANIM_CMD1(_cmd, ...)        anim->pos = __LINE__; _cmd(anim, ##__VA_ARGS__); return 0x0; case __LINE__:
#define ANIM_CMD2(_cmd, ...)        anim->pos = __LINE__; _cmd(__VA_ARGS__); return 0x0; case __LINE__:
#define ANIM_RET                    anim->pos = __LINE__; BattleAnimCmd_Ret(anim); return 0x1; case __LINE__:
#define ANIM_FALLTHROUGH(_s)        default: BattleAnimCmd_Jump(anim, _s); return 0x0; } return true;
#define ANIM_WAIT(_w)               anim->pos = __LINE__; BattleAnimCmd_Wait(_w); return 0x2; case __LINE__:

#define anim_wait(_w)               ANIM_WAIT(_w)
#define anim_obj(_obj, _x, _y, _p)  ANIM_CMD2(BattleAnimCmd_Obj, _obj, _x, _y, _p)
#define anim_1gfx(_1)               ANIM_CMD2(BattleAnimCmd_NGFX, 1, _1)
#define anim_2gfx(_1,_2)            ANIM_CMD2(BattleAnimCmd_NGFX, 2, _1, _2)
#define anim_3gfx(_1,_2,_3)         ANIM_CMD2(BattleAnimCmd_NGFX, 3, _1, _2, _3)
#define anim_4gfx(_1,_2,_3,_4)      ANIM_CMD2(BattleAnimCmd_NGFX, 4, _1, _2, _3, _4)
#define anim_5gfx(_1,_2,_3,_4,_5)   ANIM_CMD2(BattleAnimCmd_NGFX, 5, _1, _2, _3, _4, _5)
#define anim_incobj(_obj)           ANIM_CMD2(BattleAnimCmd_IncObj, _obj)
#define anim_setobj(_a, _jt)        ANIM_CMD2(BattleAnimCmd_SetObj, _a, _jt)
#define anim_incbgeffect(_a)        ANIM_CMD2(BattleAnimCmd_IncBGEffect, _a)
#define anim_battlergfx_2row        ANIM_CMD2(BattleAnimCmd_BattlerGFX_2Row)
#define anim_battlergfx_1row        ANIM_CMD2(BattleAnimCmd_BattlerGFX_1Row)
#define anim_checkpokeball          ANIM_CMD2(BattleAnimCmd_CheckPokeball)
#define anim_transform              ANIM_CMD2(BattleAnimCmd_Transform)
#define anim_raisesub               ANIM_CMD2(BattleAnimCmd_RaiseSub)
#define anim_dropsub                ANIM_CMD2(BattleAnimCmd_DropSub)
#define anim_resetobp0              ANIM_CMD2(BattleAnimCmd_ResetObp0)
#define anim_sound(_d, _t, _s)      ANIM_CMD2(BattleAnimCmd_Sound, _d, _t, _s)
#define anim_cry(_cry)              ANIM_CMD2(BattleAnimCmd_Cry, _cry)
#define anim_minimizeopp            ANIM_CMD2(BattleAnimCmd_MinimizeOpp)
#define anim_oamon                  ANIM_CMD2(BattleAnimCmd_OAMOn)
#define anim_oamoff                 ANIM_CMD2(BattleAnimCmd_OAMOff)
#define anim_clearobjs              ANIM_CMD2(BattleAnimCmd_ClearObjs)
#define anim_beatup                 ANIM_CMD2(BattleAnimCmd_BeatUp)
//#define anim_0xe7
#define anim_updateactorpic         ANIM_CMD2(BattleAnimCmd_UpdateActorPic)
#define anim_minimize               ANIM_CMD2(BattleAnimCmd_Minimize)
//#define anim_0xea
//#define anim_0xeb
//#define anim_0xec
//#define anim_0xed
#define anim_if_param_and_(_n, _f)  ANIM_CMD1(BattleAnimCmd_IfParamAnd, _n, _f)
#define anim_jumpuntil_(_f)         ANIM_CMD1(BattleAnimCmd_JumpUntil, _f)
#define anim_bgeffect(_i,_j,_t,_p)  ANIM_CMD2(BattleAnimCmd_BGEffect, _i, _j, _t, _p)
#define anim_bgp(_bgp)              ANIM_CMD2(BattleAnimCmd_BGP, _bgp)
#define anim_obp0(_obp0)            ANIM_CMD2(BattleAnimCmd_OBP0, _obp0)
#define anim_obp1(_obp1)            ANIM_CMD2(BattleAnimCmd_OBP1, _obp1)
#define anim_keepsprites            ANIM_CMD2(BattleAnimCmd_KeepSprites)
//#define anim_0xf5
//#define anim_0xf6
//#define anim_0xf7
#define anim_if_param_equal_(_n, _f) ANIM_CMD1(BattleAnimCmd_IfParamEqual, _n, _f)
#define anim_setvar(_val)           ANIM_CMD2(BattleAnimCmd_SetVar, _val)
#define anim_incvar                 ANIM_CMD2(BattleAnimCmd_IncVar)
#define anim_if_var_equal_(_n, _f)  ANIM_CMD1(BattleAnimCmd_IfVarEqual, _n, _f)
#define anim_jump_(_dest)           ANIM_CMD1(BattleAnimCmd_Jump, _dest)
#define anim_loop_(_c, _f)          ANIM_CMD1(BattleAnimCmd_Loop, _c, _f)
#define anim_call(_f)               ANIM_CMD1(BattleAnimCmd_Call, _f)
#define anim_ret                    ANIM_RET

#define anim_if_param_and(_n, _f)   if(wram->wBattleAnimParam & (_n)) goto _f;
#define anim_if_param_equal(_n, _f) if(wram->wBattleAnimParam == (_n)) goto _f;
#define anim_if_var_equal(_n, _f)   if(wram->wBattleAnimVar == (_n)) goto _f;
#define anim_jump(_dest)            goto _dest;
#define anim_loop(_c, _d)           if(BattleAnimCmd_LoopInline(_c)) goto _d;
#define anim_jumpuntil(_d)          if(wram->wBattleAnimParam-- != 0) goto _d; wram->wBattleAnimParam = 0;
