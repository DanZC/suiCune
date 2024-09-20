#pragma once
//// EVENTS
extern const struct MapScripts PowerPlant_MapScripts;
extern const struct MapEvents PowerPlant_MapEvents;

//// CODE

bool PowerPlant_MapScripts_DummyScene0(script_s* s);
bool PowerPlant_MapScripts_DummyScene1(script_s* s);
bool PowerPlantGuardPhoneScript(script_s* s);
bool PowerPlantOfficerScript(script_s* s);
bool PowerPlantGymGuide1Script(script_s* s);
bool PowerPlantGymGuide2Script(script_s* s);
bool PowerPlantOfficer2Script(script_s* s);
bool PowerPlantGymGuide4Script(script_s* s);
bool PowerPlantManager(script_s* s);
bool Forest(script_s* s);
bool PowerPlantBookshelf(script_s* s);
extern const uint8_t PowerPlantOfficer1ApproachGymGuide2Movement[];
extern const uint8_t PowerPlantOfficer1ReturnToPostMovement[];
extern const txt_cmd_s PowerPlantOfficer1AThiefBrokeInText[];
extern const txt_cmd_s PowerPlantOfficer1CeruleanShadyCharacterText[];
extern const txt_cmd_s PowerPlantOfficer1CouldIAskForYourCooperationText[];
extern const txt_cmd_s PowerPlantOfficer1HaveToBeefUpSecurityText[];
extern const txt_cmd_s PowerPlantGymGuide1SomeoneStoleAPartText[];
extern const txt_cmd_s PowerPlantGymGuide1GeneratorUpAndRunningText[];
extern const txt_cmd_s PowerPlantGymGuide2PowerPlantUpAndRunningText[];
extern const txt_cmd_s PowerPlantGymGuide2GeneratorIsRunningAgainText[];
extern const txt_cmd_s PowerPlantOfficer2ManagerHasBeenSadAndFuriousText[];
extern const txt_cmd_s PowerPlantOfficer2ManagerHasBeenCheerfulText[];
extern const txt_cmd_s PowerPlantGymGuide4MagnetTrainConsumesElectricityText[];
extern const txt_cmd_s PowerPlantGymGuide4WeCanGetMagnetTrainRunningText[];
extern const txt_cmd_s PowerPlantManagerWhoWouldRuinMyGeneratorText[];
extern const txt_cmd_s PowerPlantManagerIWontForgiveCulpritText[];
extern const txt_cmd_s PowerPlantManagerThatsThePartText[];
extern const txt_cmd_s PowerPlantManagerTakeThisTMText[];
extern const txt_cmd_s PowerPlantManagerTM07IsZapCannonText[];
extern const txt_cmd_s PowerPlantManagerMyBelovedGeneratorText[];
