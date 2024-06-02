#include "../../constants.h"

const char *ItemPocketNames[] = {
// entries correspond to item type constants
    [ITEM-1] = "ITEM POCKET@",
    [KEY_ITEM-1] = "KEY POCKET@",
    [BALL-1] = "BALL POCKET@",
    [TM_HM-1] = "TM POCKET@",
};
static_assert(lengthof(ItemPocketNames) == NUM_ITEM_TYPES, "");
