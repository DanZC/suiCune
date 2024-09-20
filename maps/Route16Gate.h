#pragma once
//// EVENTS
extern const struct MapScripts Route16Gate_MapScripts;
extern const struct MapEvents Route16Gate_MapEvents;

//// CODE

bool Route16Gate_MapScripts_DummyScene(script_s* s);
bool Route16GateOfficerScript(script_s* s);
bool Route16GateBicycleCheck(script_s* s);
extern const uint8_t Route16GateCannotPassMovement[];
extern const txt_cmd_s Route16GateOfficerText[];
extern const txt_cmd_s Route16GateCannotPassText[];
