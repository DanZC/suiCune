struct FacingDist {
    bool facing;
    uint8_t dist; // d or b
    uint8_t dir;  // e or c
};
void CheckTrainerBattle(void);
bool CheckTrainerBattle_Conv(void);
void v_CheckTrainerBattle(void);
bool v_CheckTrainerBattle_Conv(void);
void TalkToTrainer(void);
bool TalkToTrainer_Conv(void);
void LoadTrainer_continue(void);
bool LoadTrainer_continue_Conv(void);
void FacingPlayerDistance_bc(void);
struct FacingDist FacingPlayerDistance_bc_Conv(struct Object* bc);
void FacingPlayerDistance(void);
struct FacingDist FacingPlayerDistance_Conv(struct Object* bc);
void CheckTrainerFlag(void);
void PrintWinLossText(void);
void PrintWinLossText_Conv(void);

extern const struct TextCmd* gWinTextPointer;
extern const struct TextCmd* gLossTextPointer;
