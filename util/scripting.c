#include "../constants.h"
#include "../home/audio.h"
#include "../home/delay.h"

struct TextCmdState;

struct TextCmd
{
    uint8_t cmd;
    union {
        const char* const text;
        uint8_t* const ram;
        void (*const as)(struct TextCmdState*);
        int end;
    };
};

#define text_start(_s) {TX_START, .text=_s},
#define text_ram(_r)   {TX_RAM, .ram=_r},
#define text_asm(_fn)  {TX_START_ASM, .as=_fn},
#define text_end       {TX_END, .ram=NULL},
#define wram_ptr(_p)   (gb.wram + (WRAM_BANK_SIZE * (MBANK(a##_p))) + (_p - WRAM_0_ADDR))

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

#include "scripting_macros.h"
#include "../engine/overworld/scripting.h"

void Script_checkscene_Conv(struct Script* s) {
    return;

no_scene:
	s->var = 0xff;
    return;
}

void Script_pause_Conv(struct Script* s, uint8_t a) {
    (void)s;
    if(a != 0) {
        wram->wScriptDelay = a;
    }
    do {
        DelayFrames_Conv(2);
    } while(--wram->wScriptDelay != 0);
}

void Script_waitsfx_Conv(struct Script* s) {
    (void)s;
    WaitSFX_Conv();
    return;
}

void Script_playsound_Conv(struct Script* s, uint16_t sfx) {
    (void)s;
    PlaySFX_Conv(sfx);
    return;
}

void Script_writetext_Conv(struct Script* s, const struct TextCmd* text) {
    (void)s, (void)text;
    return;
}

const struct TextCmd ReceivedItemText[] = {
    text_start("@")
    text_ram(wram_ptr(wStringBuffer1))
    text_end
};

enum {
    ReceiveItemScript_lbl1 = 1
};

bool ReceiveItemScript(script_s* s) {
    SCRIPT_BEGIN
far_label(ReceiveItemScript_lbl1)
    waitsfx;
    // farwritetext ReceivedItemText
    writetext(ReceivedItemText);
    playsound(SFX_ITEM);
    waitsfx;
    SCRIPT_END
}


bool OtherScript(script_s* s) {
    SCRIPT_BEGIN
    playsound(SFX_ITEM);
    scall_far(ReceiveItemScript, ReceiveItemScript_lbl1);
    checkflag(ENGINE_62);
    waitsfx;
    SCRIPT_END
}