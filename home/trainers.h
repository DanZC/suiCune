struct FacingDist {
    bool facing;
    uint8_t dist; // d or b
    uint8_t dir;  // e or c
};
bool CheckTrainerBattle(void);
bool v_CheckTrainerBattle(void);
bool TalkToTrainer(void);
bool LoadTrainer_continue(void);
struct FacingDist FacingPlayerDistance_bc(struct Object* bc);
struct FacingDist FacingPlayerDistance(struct Object* bc);
void CheckTrainerFlag(void);
void PrintWinLossText(void);

extern const struct TextCmd* gSeenTextPointer;
extern const struct TextCmd* gWinTextPointer;
extern const struct TextCmd* gLossTextPointer;
extern Script_fn_t gScriptAfterPointer;
