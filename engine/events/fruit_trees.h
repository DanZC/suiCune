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
extern const struct TextCmd FruitBearingTreeText[];
extern const struct TextCmd HeyItsFruitText[];
extern const struct TextCmd ObtainedFruitText[];
extern const struct TextCmd FruitPackIsFullText[];
extern const struct TextCmd NothingHereText[];
//#include "data/items/fruit_trees.h"
