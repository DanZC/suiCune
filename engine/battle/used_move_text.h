void DisplayUsedMoveText(void);
// void UsedMoveText(void);
void UsedMoveText_Function(struct TextCmdState* state);
extern const struct TextCmd UsedMoveText[];
extern const struct TextCmd UsedMove1Text[];
extern const struct TextCmd UsedMove2Text[];
void UsedMoveText_CheckObedience(struct TextCmdState* state);
extern const struct TextCmd MoveNameText[];
void MoveNameText_Function(struct TextCmdState* state);
extern const struct TextCmd EndUsedMove1Text[];
extern const struct TextCmd EndUsedMove2Text[];
extern const struct TextCmd EndUsedMove3Text[];
extern const struct TextCmd EndUsedMove4Text[];
extern const struct TextCmd EndUsedMove5Text[];
void GetMoveGrammar(void);
void UpdateUsedMoves(void);
void UpdateUsedMoves_Conv(move_t a);
//#include "data/moves/grammar.h"
