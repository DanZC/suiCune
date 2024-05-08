bool Elevator(const struct ElevatorData* de);
void Elevator_GoToFloor(void);
void Elevator_GoToFloor_Conv(uint8_t a);
void Elevator_AskWhichFloor(void);
u8_flag_s Elevator_AskWhichFloor_Conv(void);
// void AskFloorElevatorText(void);
void Elevator_GetCurrentFloorText(void);
// void Elevator_CurrentFloorText(void);
void Elevator_GetCurrentFloorString(tile_t* hl);
extern const struct MenuHeader Elevator_MenuHeader;
// void Elevator_MenuData(void);
void GetElevatorFloorStrings(const struct MenuData* data, tile_t* de);
void GetFloorString(tile_t* de, uint8_t a);
const char* FloorToString(uint8_t a);
//#include "data/events/elevator_floors.h"
