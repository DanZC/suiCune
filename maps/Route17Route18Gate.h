#pragma once
//// EVENTS
extern const struct MapScripts Route17Route18Gate_MapScripts;
extern const struct MapEvents Route17Route18Gate_MapEvents;

//// CODE

bool Route17Route18Gate_MapScripts_DummyScene(script_s* s);
bool Route17Route18GateOfficerScript(script_s* s);
bool Route17Route18GateBicycleCheck(script_s* s);
extern const uint8_t Route17Route18GateCannotPassMovement[];
extern const txt_cmd_s Route17Route18GateOfficerText[];
extern const txt_cmd_s Route17Route18GateCannotPassText[];
