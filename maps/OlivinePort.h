#pragma once
//// EVENTS
extern const struct MapScripts OlivinePort_MapScripts;
extern const struct MapEvents OlivinePort_MapEvents;

//// CODE

bool OlivinePort_MapScripts_DummyScene0(script_s* s);
bool OlivinePort_MapScripts_LeaveFastShip(script_s* s);
bool OlivinePort_MapScripts_LeaveFastShipScript(script_s* s);
bool OlivinePortSailorAtGangwayScript(script_s* s);
bool OlivinePortAlreadyRodeScript(script_s* s);
bool OlivinePortWalkUpToShipScript(script_s* s);
bool OlivinePortNotRidingScript(script_s* s);
bool OlivinePortNotRidingMoveAwayScript(script_s* s);
bool OlivinePortSailorAfterHOFScript(script_s* s);
bool OlivinePortSailorBeforeHOFScript(script_s* s);
bool OlivinePortFishingGuru1Script(script_s* s);
bool OlivinePortFishingGuru2Script(script_s* s);
bool OlivinePortYoungsterScript(script_s* s);
bool OlivinePortCooltrainerFScript(script_s* s);
extern const struct HiddenItem OlivinePortHiddenProtein;
extern const uint8_t OlivinePortEnterFastShipMovement[];
extern const uint8_t OlivinePortLeaveFastShipMovement[];
extern const uint8_t OlivinePortCannotEnterFastShipMovement[];
extern const uint8_t OlivinePortApproachFastShipFirstTimeMovement[];
extern const uint8_t OlivinePortApproachFastShipAfterHOFMovement[];
extern const uint8_t OlivinePortApproachFastShipAfterHOFRightMovement[];
extern const txt_cmd_s OlivinePortSailorGetOnBoardText[];
extern const txt_cmd_s OlivinePortCantBoardText[];
extern const txt_cmd_s OlivinePortAskBoardText[];
extern const txt_cmd_s OlivinePortAskTicketText[];
extern const txt_cmd_s OlivinePortComeAgainText[];
extern const txt_cmd_s OlivinePortFlashTicketText[];
extern const txt_cmd_s OlivinePortNoTicketText[];
extern const txt_cmd_s OlivinePortMondayShipText[];
extern const txt_cmd_s OlivinePortFridayShipText[];
extern const txt_cmd_s OlivinePortFishingGuru1Text[];
extern const txt_cmd_s OlivinePortFishingGuru2Text[];
extern const txt_cmd_s OlivinePortYoungsterText[];
extern const txt_cmd_s OlivinePortCooltrainerFText[];
extern const txt_cmd_s OlivinePortSailorBeforeHOFText[];
