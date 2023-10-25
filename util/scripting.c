#include "../constants.h"
#include "../home/audio.h"
#include "../home/delay.h"

struct TextPrintState;

#include "scripting.h"

void Script_Pop(script_s* s) {
    uint16_t i = --s->stack_ptr;
    s->position = s->stack[i].position;
    s->fn = s->stack[i].fn;
}

void Script_Push(script_s* s) {
    uint16_t i = s->stack_ptr++;
    s->stack[i].fn = s->fn;
    s->stack[i].position = s->position;
}

void Script_Goto(script_s* s, Script_fn_t fn) {
    s->fn = fn;
    s->position = 0;
}

void Script_GotoPos(script_s* s, Script_fn_t fn, int pos) {
    s->fn = fn;
    s->position = pos;
}

void Script_CallScript(script_s* s, Script_fn_t fn) {
    Script_Push(s);
    Script_Goto(s, fn);
}

void Script_CallScriptPos(script_s* s, Script_fn_t fn, int pos) {
    Script_Push(s);
    Script_GotoPos(s, fn, pos);
}

void Script_Ret(script_s* s) {
    Script_Pop(s);
}

#include "text_cmd.h"
#include "scripting_macros.h"
#include "../engine/overworld/scripting.h"

void Script_checkscene_Conv(struct Script* s) {
    return;

no_scene:
	s->var = 0xff;
    return;
}

script_s gCurScript;
