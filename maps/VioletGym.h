#pragma once
//// EVENTS
extern const struct MapScripts VioletGym_MapScripts;
extern const struct MapEvents VioletGym_MapEvents;

//// CODE

bool VioletGymFalknerScript(script_s* s);
bool VioletGymActivateRockets(script_s* s);
extern const struct TrainerObj TrainerBirdKeeperRod;
bool TrainerBirdKeeperRod_Script(script_s* s);
extern const struct TrainerObj TrainerBirdKeeperAbe;
bool TrainerBirdKeeperAbe_Script(script_s* s);
bool VioletGymGuideScript(script_s* s);
bool VioletGymStatue(script_s* s);
extern const txt_cmd_s FalknerIntroText[];
extern const txt_cmd_s FalknerWinLossText[];
extern const txt_cmd_s ReceivedZephyrBadgeText[];
extern const txt_cmd_s FalknerZephyrBadgeText[];
extern const txt_cmd_s FalknerTMMudSlapText[];
extern const txt_cmd_s FalknerFightDoneText[];
extern const txt_cmd_s BirdKeeperRodSeenText[];
extern const txt_cmd_s BirdKeeperRodBeatenText[];
extern const txt_cmd_s BirdKeeperRodAfterBattleText[];
extern const txt_cmd_s BirdKeeperAbeSeenText[];
extern const txt_cmd_s BirdKeeperAbeBeatenText[];
extern const txt_cmd_s BirdKeeperAbeAfterBattleText[];
extern const txt_cmd_s VioletGymGuideText[];
extern const txt_cmd_s VioletGymGuideWinText[];
