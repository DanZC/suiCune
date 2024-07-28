#pragma once
//// EVENTS
extern const struct MapScripts VermilionPort_MapScripts;
extern const struct MapEvents VermilionPort_MapEvents;

//// CODE

bool VermilionPort_MapScripts_DummyScene0(script_s* s);
bool VermilionPort_MapScripts_LeaveFastShip(script_s* s);
bool VermilionPort_MapScripts_FlyPoint(script_s* s);
bool VermilionPort_MapScripts_LeaveFastShipScript(script_s* s);
bool VermilionPortSailorAtGangwayScript(script_s* s);
bool VermilionPortAlreadyRodeScript(script_s* s);
bool VermilionPortWalkUpToShipScript(script_s* s);
bool VermilionPortNotRidingScript(script_s* s);
bool VermilionPortNotRidingMoveAwayScript(script_s* s);
bool VermilionPortSailorScript(script_s* s);
bool VermilionPortSuperNerdScript(script_s* s);
extern const struct HiddenItem VermilionPortHiddenIron;
extern const uint8_t VermilionPortEnterFastShipMovement[];
extern const uint8_t VermilionPortLeaveFastShipMovement[];
extern const uint8_t VermilionPortCannotEnterFastShipMovement[];
extern const uint8_t VermilionPortApproachFastShipMovement[];
extern const uint8_t VermilionPortApproachFastShipRightMovement[];
extern const txt_cmd_s VermilionPortDepartingText[];
extern const txt_cmd_s VermilionPortCantBoardText[];
extern const txt_cmd_s VermilionPortAskBoardingText[];
extern const txt_cmd_s VermilionPortAskTicketText[];
extern const txt_cmd_s VermilionPortComeAgainText[];
extern const txt_cmd_s VermilionPortSSTicketText[];
extern const txt_cmd_s VermilionPortNoTicketText[];
extern const txt_cmd_s VermilionPortSailMondayText[];
extern const txt_cmd_s VermilionPortSailSundayText[];
extern const txt_cmd_s VermilionPortSuperNerdText[];
