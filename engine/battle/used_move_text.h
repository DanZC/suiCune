void DisplayUsedMoveText(void);
// void UsedMoveText(void);
void UsedMoveText_Function(struct TextCmdState* state);
extern const txt_cmd_s UsedMoveText[];
extern const txt_cmd_s UsedMove1Text[];
extern const txt_cmd_s UsedMove2Text[];
void UsedMoveText_CheckObedience(struct TextCmdState* state);
extern const txt_cmd_s MoveNameText[];
void MoveNameText_Function(struct TextCmdState* state);
extern const txt_cmd_s EndUsedMove1Text[];
extern const txt_cmd_s EndUsedMove2Text[];
extern const txt_cmd_s EndUsedMove3Text[];
extern const txt_cmd_s EndUsedMove4Text[];
extern const txt_cmd_s EndUsedMove5Text[];
#if defined(_CRYSTAL_JP)
void GetMoveGrammar(void);
#endif
// void UpdateUsedMoves(move_t a);
//#include "data/moves/grammar.h"
