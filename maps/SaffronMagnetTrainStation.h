#pragma once
//// EVENTS
extern const struct MapScripts SaffronMagnetTrainStation_MapScripts;
extern const struct MapEvents SaffronMagnetTrainStation_MapEvents;

//// CODE

bool SaffronMagnetTrainStation_MapScripts_DummyScene(script_s* s);
bool SaffronMagnetTrainStationOfficerScript(script_s* s);
bool Script_ArriveFromGoldenrod(script_s* s);
bool SaffronMagnetTrainStationGymGuideScript(script_s* s);
bool SaffronMagnetTrainStationTeacherScript(script_s* s);
bool SaffronMagnetTrainStationLassScript(script_s* s);
extern const uint8_t SaffronMagnetTrainStationOfficerApproachTrainDoorMovement[];
extern const uint8_t SaffronMagnetTrainStationOfficerReturnToBoardingGateMovement[];
extern const uint8_t SaffronMagnetTrainStationPlayerApproachAndEnterTrainMovement[];
extern const uint8_t SaffronMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement[];
extern const txt_cmd_s SaffronMagnetTrainStationOfficerTrainIsntOperatingText[];
extern const txt_cmd_s SaffronMagnetTrainStationOfficerAreYouComingOnBoardText[];
extern const txt_cmd_s SaffronMagnetTrainStationOfficerRightThisWayText[];
extern const txt_cmd_s SaffronMagnetTrainStationOfficerYouDontHaveAPassText[];
extern const txt_cmd_s SaffronMagnetTrainStationOfficerHopeToSeeYouAgainText[];
extern const txt_cmd_s SaffronMagnetTrainStationOfficerArrivedInSaffronText[];
extern const txt_cmd_s SaffronMagnetTrainStationGymGuideText[];
extern const txt_cmd_s SaffronMagnetTrainStationGymGuideText_ReturnedMachinePart[];
extern const txt_cmd_s SaffronMagnetTrainStationTeacherText[];
extern const txt_cmd_s SaffronMagnetTrainStationLassText[];
