#include "../../constants.h"

const char *ItemPocketNames[] = {
// entries correspond to item type constants
    [ITEM_POCKET] = "ITEM POCKET@",
    [KEY_ITEM_POCKET] = "KEY POCKET@",
    [BALL_POCKET] = "BALL POCKET@",
    [TM_HM_POCKET] = "TM POCKET@",
};
static_assert(lengthof(ItemPocketNames) == NUM_ITEM_TYPES);
