#include "../../constants.h"

const char* ElevatorFloorNames[] = {
// entries correspond to FLOOR_* constants
// table_width 2, ElevatorFloorNames
    [FLOOR_B4F] = "B4F@",
    [FLOOR_B3F] = "B3F@",
    [FLOOR_B2F] = "B2F@",
    [FLOOR_B1F] = "B1F@",
    [FLOOR_1F] = "1F@",
    [FLOOR_2F] = "2F@",
    [FLOOR_3F] = "3F@",
    [FLOOR_4F] = "4F@",
    [FLOOR_5F] = "5F@",
    [FLOOR_6F] = "6F@",
    [FLOOR_7F] = "7F@",
    [FLOOR_8F] = "8F@",
    [FLOOR_9F] = "9F@",
    [FLOOR_10F] = "10F@",
    [FLOOR_11F] = "11F@",
    [FLOOR_ROOF] = "ROOF@",
};
static_assert(lengthof(ElevatorFloorNames) == NUM_FLOORS);

