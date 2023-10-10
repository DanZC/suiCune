#include "../../constants.h"
#include "blocks.h"

#define map_attributes(name, id, block, connections) const struct MapAttr name##_MapAttributes = {\
    .width = id##_WIDTH, .height = id##_HEIGHT, .borderBlock = block, .blocksPath = name##_Blocks, \
    .events = name##_Events, .connections={ connections }}
