#pragma once
//// EVENTS
extern const struct MapScripts Route29_MapScripts;
extern const struct MapEvents Route29_MapEvents;

//// CODE

bool Route29_MapScripts_DummyScene0(script_s* s);
bool Route29_MapScripts_DummyScene1(script_s* s);
bool Route29_MapScripts_Tuscany(script_s* s);
bool Route29_MapScripts_TuscanyDisappears(script_s* s);
bool Route29_MapScripts_DoesTuscanyAppear(script_s* s);
bool Route29Tutorial1(script_s* s);
bool Route29Tutorial2(script_s* s);
bool Script_RefusedTutorial1(script_s* s);
bool Script_RefusedTutorial2(script_s* s);
bool CatchingTutorialDudeScript(script_s* s);
bool Route29YoungsterScript(script_s* s);
bool Route29TeacherScript(script_s* s);
bool Route29FisherScript(script_s* s);
bool Route29CooltrainerMScript(script_s* s);
bool TuscanyScript(script_s* s);
bool TuscanyTuesdayScript(script_s* s);
bool TuscanyDoneScript(script_s* s);
bool TuscanyNotTuesdayScript(script_s* s);
bool Route29Sign1(script_s* s);
bool Route29Sign2(script_s* s);
bool Route29FruitTree(script_s* s);
extern const struct ItemBall Route29Potion;
extern const uint8_t DudeMovementData1a[];
extern const uint8_t DudeMovementData2a[];
extern const uint8_t DudeMovementData1b[];
extern const uint8_t DudeMovementData2b[];
extern const struct TextCmd CatchingTutorialBoxFullText[];
extern const struct TextCmd CatchingTutorialIntroText[];
extern const struct TextCmd CatchingTutorialDebriefText[];
extern const struct TextCmd CatchingTutorialDeclinedText[];
extern const struct TextCmd CatchingTutorialRepeatText[];
extern const struct TextCmd Route29YoungsterText[];
extern const struct TextCmd Route29TeacherText[];
extern const struct TextCmd Route29FisherText[];
extern const struct TextCmd Route29CooltrainerMText_WaitingForDay[];
extern const struct TextCmd Route29CooltrainerMText_WaitingForNight[];
extern const struct TextCmd Route29CooltrainerMText_WaitingForMorning[];
extern const struct TextCmd MeetTuscanyText[];
extern const struct TextCmd TuscanyGivesGiftText[];
extern const struct TextCmd TuscanyGaveGiftText[];
extern const struct TextCmd TuscanyTuesdayText[];
extern const struct TextCmd TuscanyNotTuesdayText[];
extern const struct TextCmd Route29Sign1Text[];
extern const struct TextCmd Route29Sign2Text[];
