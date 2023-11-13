void QueueScript(void);
void QueueScript_Conv(uint16_t hl);
void FarQueueScript(void);
void FarQueueScript_Conv(uint8_t a, uint16_t hl);
void QueueScript_Conv2(Script_fn_t hl);
void QueueFunc_Conv2(void (*hl)(void));

extern Script_fn_t gQueuedScriptAddr;
extern void (*gQueuedFuncAddr)(void);
