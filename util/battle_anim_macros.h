#pragma once
#define ANIM_BEGIN                  switch(anim->pos) { case 0:
#define ANIM_END                    default: break; } return 0x1;
#define ANIM_CMD1(_cmd, ...)        anim->pos = __LINE__; _cmd(anim, ##__VA_ARGS__); return 0x0; case __LINE__:
#define ANIM_CMD2(_cmd, ...)        anim->pos = __LINE__; _cmd(__VA_ARGS__); return 0x0; case __LINE__:
#define ANIM_RET                    anim->pos = __LINE__; BattleAnimCmd_Ret_Conv(anim); return 0x1; case __LINE__:
#define ANIM_FALLTHROUGH(_s)        default: BattleAnimCmd_Jump_Conv(anim, _s); return 0x0; } return true;
#define ANIM_WAIT(_w)               anim->pos = __LINE__; BattleAnimCmd_Wait_Conv(_w); return 0x2; case __LINE__:

#define anim_wait(_w)               ANIM_WAIT(_w)
#define anim_obj(_obj, _x, _y, _p)  ANIM_CMD2(BattleAnimCmd_Obj_Conv, _obj, _x, _y, _p)
#define anim_1gfx(_1)               ANIM_CMD2(BattleAnimCmd_NGFX_Conv, 1, _1)
#define anim_2gfx(_1,_2)            ANIM_CMD2(BattleAnimCmd_NGFX_Conv, 2, _1, _2)
#define anim_3gfx(_1,_2,_3)         ANIM_CMD2(BattleAnimCmd_NGFX_Conv, 3, _1, _2, _3)
#define anim_4gfx(_1,_2,_3,_4)      ANIM_CMD2(BattleAnimCmd_NGFX_Conv, 4, _1, _2, _3, _4)
#define anim_5gfx(_1,_2,_3,_4,_5)   ANIM_CMD2(BattleAnimCmd_NGFX_Conv, 5, _1, _2, _3, _4, _5)
#define anim_incobj(_obj)           ANIM_CMD2(BattleAnimCmd_IncObj_Conv, _obj)
#define anim_setobj(_a, _jt)        ANIM_CMD2(BattleAnimCmd_SetObj_Conv, _a, _jt)
#define anim_incbgeffect(_a)        ANIM_CMD2(BattleAnimCmd_IncBGEffect_Conv, _a)
#define anim_battlergfx_2row        ANIM_CMD2(BattleAnimCmd_BattlerGFX_2Row_Conv)
#define anim_battlergfx_1row        ANIM_CMD2(BattleAnimCmd_BattlerGFX_1Row_Conv)
#define anim_checkpokeball          ANIM_CMD2(BattleAnimCmd_CheckPokeball_Conv)
#define anim_transform              ANIM_CMD2(BattleAnimCmd_Transform_Conv)
#define anim_raisesub               ANIM_CMD2(BattleAnimCmd_RaiseSub_Conv)
#define anim_dropsub                ANIM_CMD2(BattleAnimCmd_DropSub_Conv)
#define anim_resetobp0              ANIM_CMD2(BattleAnimCmd_ResetObp0_Conv)
#define anim_sound(_d, _t, _s)      ANIM_CMD2(BattleAnimCmd_Sound_Conv, _d, _t, _s)
#define anim_cry(_cry)              ANIM_CMD2(BattleAnimCmd_Cry_Conv, _cry)
#define anim_minimizeopp            ANIM_CMD2(BattleAnimCmd_MinimizeOpp_Conv)
#define anim_oamon                  ANIM_CMD2(BattleAnimCmd_OAMOn_Conv)
#define anim_oamoff                 ANIM_CMD2(BattleAnimCmd_OAMOff_Conv)
#define anim_clearobjs              ANIM_CMD2(BattleAnimCmd_ClearObjs_Conv)
#define anim_beatup                 ANIM_CMD2(BattleAnimCmd_BeatUp_Conv)
//#define anim_0xe7
#define anim_updateactorpic         ANIM_CMD2(BattleAnimCmd_UpdateActorPic_Conv)
#define anim_minimize               ANIM_CMD2(BattleAnimCmd_Minimize_Conv)
//#define anim_0xea
//#define anim_0xeb
//#define anim_0xec
//#define anim_0xed
#define anim_if_param_and_(_n, _f)  ANIM_CMD1(BattleAnimCmd_IfParamAnd_Conv, _n, _f)
#define anim_jumpuntil_(_f)         ANIM_CMD1(BattleAnimCmd_JumpUntil_Conv, _f)
#define anim_bgeffect(_i,_j,_t,_p)  ANIM_CMD2(BattleAnimCmd_BGEffect_Conv, _i, _j, _t, _p)
#define anim_bgp(_bgp)              ANIM_CMD2(BattleAnimCmd_BGP_Conv, _bgp)
#define anim_obp0(_obp0)            ANIM_CMD2(BattleAnimCmd_OBP0_Conv, _obp0)
#define anim_obp1(_obp1)            ANIM_CMD2(BattleAnimCmd_OBP1_Conv, _obp1)
#define anim_keepsprites            ANIM_CMD2(BattleAnimCmd_KeepSprites_Conv)
//#define anim_0xf5
//#define anim_0xf6
//#define anim_0xf7
#define anim_if_param_equal_(_n, _f) ANIM_CMD1(BattleAnimCmd_IfParamEqual_Conv, _n, _f)
#define anim_setvar(_val)           ANIM_CMD2(BattleAnimCmd_SetVar_Conv, _val)
#define anim_incvar                 ANIM_CMD2(BattleAnimCmd_IncVar_Conv)
#define anim_if_var_equal_(_n, _f)  ANIM_CMD1(BattleAnimCmd_IfVarEqual_Conv, _n, _f)
#define anim_jump_(_dest)           ANIM_CMD1(BattleAnimCmd_Jump_Conv, _dest)
#define anim_loop_(_c, _f)          ANIM_CMD1(BattleAnimCmd_Loop_Conv, _c, _f)
#define anim_call(_f)               ANIM_CMD1(BattleAnimCmd_Call_Conv, _f)
#define anim_ret                    ANIM_RET

#define anim_if_param_and(_n, _f)   if(wram->wBattleAnimParam & (_n)) goto _f;
#define anim_if_param_equal(_n, _f) if(wram->wBattleAnimParam == (_n)) goto _f;
#define anim_if_var_equal(_n, _f)   if(wram->wBattleAnimVar == (_n)) goto _f;
#define anim_jump(_dest)            goto _dest;
#define anim_loop(_c, _d)           if(BattleAnimCmd_LoopInline(_c)) goto _d;
#define anim_jumpuntil(_d)          if(wram->wBattleAnimParam-- != 0) goto _d; wram->wBattleAnimParam = 0;
