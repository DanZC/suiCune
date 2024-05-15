#pragma once
//// EVENTS
extern const struct MapScripts Route34IlexForestGate_MapScripts;
extern const struct MapEvents Route34IlexForestGate_MapEvents;

//// CODE

bool Route34IlexForestGate_MapScripts_IsForestRestless(script_s* s);
bool Route34IlexForestGate_MapScripts_Normal(script_s* s);
bool Route34IlexForestGateCelebiEvent(script_s* s);
bool Route34IlexForestGateTeacherScript(script_s* s);
bool Route34IlexForestGateButterfreeScript(script_s* s);
bool Route34IlexForestGateLassScript(script_s* s);
extern const uint8_t Route34IlexForestGateTeacherBlocksPlayerMovement[];
extern const uint8_t Route34IlexForestGateTeacherReturnsMovement[];
extern const txt_cmd_s Route34IlexForestGateTeacherText[];
extern const txt_cmd_s Route34IlexForestGateTeacher_GotSweetScent[];
extern const txt_cmd_s Route34IlexForestGateTeacher_ForestIsRestless[];
extern const txt_cmd_s Route34IlexForestGateButterfreeText[];
extern const txt_cmd_s Route34IlexForestGateLassText[];
