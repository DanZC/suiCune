bool FruitTreeScript(script_s* s);
void GetCurTreeFruit(void);
void TryResetFruitTrees(void);
void CheckFruitTree(void);
void PickedFruitTree(void);
void ResetFruitTrees(void);
void GetFruitTreeFlag(void);
uint8_t GetFruitTreeFlag_Conv(uint8_t b, uint8_t tree);
void GetFruitTreeItem(void);
item_t GetFruitTreeItem_Conv(uint8_t a);
extern const txt_cmd_s FruitBearingTreeText[];
extern const txt_cmd_s HeyItsFruitText[];
extern const txt_cmd_s ObtainedFruitText[];
extern const txt_cmd_s FruitPackIsFullText[];
extern const txt_cmd_s NothingHereText[];
//#include "data/items/fruit_trees.h"
