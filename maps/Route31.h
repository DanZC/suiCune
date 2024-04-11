#pragma once
//// EVENTS
extern const struct MapScripts Route31_MapScripts;
extern const struct MapEvents Route31_MapEvents;

//// CODE

bool Route31_MapScripts_CheckMomCall(script_s* s);
bool Route31_MapScripts_DoMomCall(script_s* s);
extern const struct TrainerObj TrainerBugCatcherWade1;
bool TrainerBugCatcherWade1_Script(script_s* s);
bool Route31MailRecipientScript(script_s* s);
extern const char ReceivedSpearowMailText[];
bool Route31YoungsterScript(script_s* s);
bool Route31Sign(script_s* s);
bool DarkCaveSign(script_s* s);
bool Route31CooltrainerMScript(script_s* s);
bool Route31FruitTree(script_s* s);
extern const struct ItemBall Route31Potion;
extern const struct ItemBall Route31PokeBall;
extern const txt_cmd_s Route31CooltrainerMText[];
extern const txt_cmd_s BugCatcherWade1SeenText[];
extern const txt_cmd_s BugCatcherWade1BeatenText[];
extern const txt_cmd_s BugCatcherWade1AfterText[];
extern const txt_cmd_s Text_Route31SleepyMan[];
extern const txt_cmd_s Text_Route31SleepyManGotMail[];
extern const txt_cmd_s Text_Route31HandOverMailMon[];
extern const txt_cmd_s Text_Route31ReadingMail[];
extern const txt_cmd_s Text_Route31DescribeNightmare[];
extern const txt_cmd_s Text_Route31WrongMail[];
extern const txt_cmd_s Text_Route31MissingMail[];
extern const txt_cmd_s Text_Route31DeclinedToHandOverMail[];
extern const txt_cmd_s Text_Route31CantTakeLastMon[];
extern const txt_cmd_s Route31YoungsterText[];
extern const txt_cmd_s Route31SignText[];
extern const txt_cmd_s DarkCaveSignText[];
