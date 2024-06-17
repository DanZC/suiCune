#pragma once
//// EVENTS
extern const struct MapScripts CianwoodPharmacy_MapScripts;
extern const struct MapEvents CianwoodPharmacy_MapEvents;

//// CODE

bool CianwoodPharmacy_MapScripts_DummyScene(script_s* s);
bool CianwoodPharmacist(script_s* s);
bool CianwoodPharmacyBookshelf(script_s* s);
extern const txt_cmd_s PharmacistGiveSecretpotionText[];
extern const txt_cmd_s ReceivedSecretpotionText[];
extern const txt_cmd_s PharmacistDescribeSecretpotionText[];
