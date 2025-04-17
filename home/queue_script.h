void QueueScript(Script_fn_t hl);
void QueueFunc(void (*hl)(void));
void QueueScript_GB(uint16_t hl);
void FarQueueScript_GB(uint8_t a, uint16_t hl);

extern Script_fn_t gQueuedScriptAddr;
extern void (*gQueuedFuncAddr)(void);
