#pragma once

struct Script;
void Script_Pop(script_s* s);
void Script_Push(script_s* s);
void Script_Goto(script_s* s, Script_fn_t fn);
void Script_GotoPos(script_s* s, Script_fn_t fn, int pos);
void Script_CallScript(script_s* s, Script_fn_t fn);
void Script_CallScriptPos(script_s* s, Script_fn_t fn, int pos);
void Script_Ret(script_s* s);

bool ObjectEvent(script_s* s);

#include "../engine/overworld/scripting.h"
#include "../engine/events/std_scripts.h"
#include "scripting_macros.h"
