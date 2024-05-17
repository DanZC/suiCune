#pragma once
//// EVENTS
extern const struct MapScripts GoldenrodMagnetTrainStation_MapScripts;
extern const struct MapEvents GoldenrodMagnetTrainStation_MapEvents;

//// CODE

bool GoldenrodMagnetTrainStation_MapScripts_DummyScene(script_s* s);
bool GoldenrodMagnetTrainStationOfficerScript(script_s* s);
bool Script_ArriveFromSaffron(script_s* s);
bool GoldenrodMagnetTrainStationGentlemanScript(script_s* s);
extern const uint8_t GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement[];
extern const uint8_t GoldenrodMagnetTrainStationOfficerReturnToBoardingGateMovement[];
extern const uint8_t GoldenrodMagnetTrainStationPlayerApproachAndEnterTrainMovement[];
extern const uint8_t GoldenrodMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement[];
extern const txt_cmd_s GoldenrodMagnetTrainStationOfficerTheTrainHasntComeInText[];
extern const txt_cmd_s GoldenrodMagnetTrainStationOfficerAreYouComingAboardText[];
extern const txt_cmd_s GoldenrodMagnetTrainStationOfficerRightThisWayText[];
extern const txt_cmd_s GoldenrodMagnetTrainStationOfficerYouDontHaveARailPassText[];
extern const txt_cmd_s GoldenrodMagnetTrainStationOfficerHopeToSeeYouAgainText[];
extern const txt_cmd_s GoldenrodMagnetTrainStationOfficerArrivedInGoldenrodText[];
extern const txt_cmd_s GoldenrodMagnetTrainStationGentlemanText[];
