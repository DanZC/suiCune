#include "../constants.h"
#include "../util/scripting.h"
#include "PowerPlant.h"
//// EVENTS
enum {
    POWERPLANT_OFFICER1 = 2,
    POWERPLANT_GYM_GUIDE1,
    POWERPLANT_GYM_GUIDE2,
    POWERPLANT_OFFICER2,
    POWERPLANT_GYM_GUIDE3,
    POWERPLANT_MANAGER,
    POWERPLANT_FOREST,
};

const Script_fn_t PowerPlant_SceneScripts[] = {
    PowerPlant_MapScripts_DummyScene0 , //  SCENE_POWERPLANT_NOTHING,
    PowerPlant_MapScripts_DummyScene1 , //  SCENE_POWERPLANT_GUARD_GETS_PHONE_CALL,
};

const struct MapCallback PowerPlant_MapCallbacks[] = {
    0,
};

const struct MapScripts PowerPlant_MapScripts = {
    .scene_script_count = lengthof(PowerPlant_SceneScripts),
    .scene_scripts = PowerPlant_SceneScripts,

    .callback_count = 0, // lengthof(PowerPlant_MapCallbacks),
    .callbacks = PowerPlant_MapCallbacks,
};

static const struct CoordEvent PowerPlant_CoordEvents[] = {
    coord_event(5, 12, SCENE_POWERPLANT_GUARD_GETS_PHONE_CALL, &PowerPlantGuardPhoneScript),
};

static const struct BGEvent PowerPlant_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &PowerPlantBookshelf),
    bg_event(1, 1, BGEVENT_READ, &PowerPlantBookshelf),
};

static const struct WarpEventData PowerPlant_WarpEvents[] = {
    warp_event(2, 17, ROUTE_10_NORTH, 2),
    warp_event(3, 17, ROUTE_10_NORTH, 2),
};

static const struct ObjEvent PowerPlant_ObjectEvents[] = {
    object_event(4, 14, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PowerPlantOfficerScript, -1),
    object_event(2, 9, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PowerPlantGymGuide1Script, -1),
    object_event(6, 11, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PowerPlantGymGuide2Script, -1),
    object_event(9, 3, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PowerPlantOfficer2Script, -1),
    object_event(7, 2, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PowerPlantGymGuide4Script, -1),
    object_event(14, 10, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &PowerPlantManager, -1),
    object_event(5, 5, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Forest, -1),
};

const struct MapEvents PowerPlant_MapEvents = {
    .warp_event_count = lengthof(PowerPlant_WarpEvents),
    .warp_events = PowerPlant_WarpEvents,

    .coord_event_count = lengthof(PowerPlant_CoordEvents),
    .coord_events = PowerPlant_CoordEvents,

    .bg_event_count = lengthof(PowerPlant_BGEvents),
    .bg_events = PowerPlant_BGEvents,

    .obj_event_count = lengthof(PowerPlant_ObjectEvents),
    .obj_events = PowerPlant_ObjectEvents,
};

//// CODE

bool PowerPlant_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool PowerPlant_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool PowerPlantGuardPhoneScript(script_s* s) {
    SCRIPT_BEGIN
    playsound(SFX_CALL)
    showemote(EMOTE_SHOCK, POWERPLANT_OFFICER1, 15)
    waitsfx
    pause(30)
    applymovement(POWERPLANT_OFFICER1, PowerPlantOfficer1ApproachGymGuide2Movement)
    turnobject(POWERPLANT_GYM_GUIDE1, DOWN)
    turnobject(POWERPLANT_GYM_GUIDE2, DOWN)
    opentext
    writetext(PowerPlantOfficer1CeruleanShadyCharacterText)
    waitbutton
    closetext
    turnobject(POWERPLANT_OFFICER1, LEFT)
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(PowerPlantOfficer1CouldIAskForYourCooperationText)
    waitbutton
    closetext
    turnobject(PLAYER, DOWN)
    applymovement(POWERPLANT_OFFICER1, PowerPlantOfficer1ReturnToPostMovement)
    setscene(SCENE_POWERPLANT_NOTHING)
    s_end
    SCRIPT_END
}
bool PowerPlantOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    checkevent(EVENT_MET_MANAGER_AT_POWER_PLANT)
    iftrue(MetManager)
    writetext(PowerPlantOfficer1AThiefBrokeInText)
    waitbutton
    closetext
    s_end
MetManager:
    writetext(PowerPlantOfficer1CouldIAskForYourCooperationText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(PowerPlantOfficer1HaveToBeefUpSecurityText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PowerPlantGymGuide1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(PowerPlantGymGuide1SomeoneStoleAPartText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(PowerPlantGymGuide1GeneratorUpAndRunningText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PowerPlantGymGuide2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(PowerPlantGymGuide2PowerPlantUpAndRunningText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(PowerPlantGymGuide2GeneratorIsRunningAgainText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PowerPlantOfficer2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(PowerPlantOfficer2ManagerHasBeenSadAndFuriousText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(PowerPlantOfficer2ManagerHasBeenCheerfulText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PowerPlantGymGuide4Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(PowerPlantGymGuide4MagnetTrainConsumesElectricityText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(PowerPlantGymGuide4WeCanGetMagnetTrainRunningText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PowerPlantManager(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    checkitem(MACHINE_PART)
    iftrue(FoundMachinePart)
    checkevent(EVENT_MET_MANAGER_AT_POWER_PLANT)
    iftrue(MetManager)
    writetext(PowerPlantManagerWhoWouldRuinMyGeneratorText)
    waitbutton
    closetext
    setevent(EVENT_MET_MANAGER_AT_POWER_PLANT)
    clearevent(EVENT_CERULEAN_GYM_ROCKET)
    clearevent(EVENT_FOUND_MACHINE_PART_IN_CERULEAN_GYM)
    setmapscene(CERULEAN_GYM, SCENE_CERULEANGYM_GRUNT_RUNS_OUT)
    setscene(SCENE_POWERPLANT_GUARD_GETS_PHONE_CALL)
    s_end
MetManager:
    writetext(PowerPlantManagerIWontForgiveCulpritText)
    waitbutton
    closetext
    s_end
FoundMachinePart:
    writetext(PowerPlantManagerThatsThePartText)
    promptbutton
    takeitem(MACHINE_PART, 1)
    setevent(EVENT_RETURNED_MACHINE_PART)
    clearevent(EVENT_SAFFRON_TRAIN_STATION_POPULATION)
    setevent(EVENT_ROUTE_5_6_POKEFAN_M_BLOCKS_UNDERGROUND_PATH)
    setevent(EVENT_ROUTE_24_ROCKET)
    setevent(EVENT_RESTORED_POWER_TO_KANTO)
    clearevent(EVENT_GOLDENROD_TRAIN_STATION_GENTLEMAN)
ReturnedMachinePart:
    checkevent(EVENT_GOT_TM07_ZAP_CANNON)
    iftrue(GotZapCannon)
    writetext(PowerPlantManagerTakeThisTMText)
    promptbutton
    verbosegiveitem(TM_ZAP_CANNON, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_TM07_ZAP_CANNON)
    writetext(PowerPlantManagerTM07IsZapCannonText)
    waitbutton
NoRoom:
    closetext
    s_end
GotZapCannon:
    writetext(PowerPlantManagerMyBelovedGeneratorText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Forest(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    trade(NPC_TRADE_FOREST)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PowerPlantBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const uint8_t PowerPlantOfficer1ApproachGymGuide2Movement[] = {
    step(RIGHT),
    step(RIGHT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t PowerPlantOfficer1ReturnToPostMovement[] = {
    step(DOWN),
    step(DOWN),
    step(LEFT),
    step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s PowerPlantOfficer1AThiefBrokeInText[] = {
    text_start("A thief broke into"
        t_line "the POWER PLANT…"
        t_para "What is the world"
        t_line "coming to?"
        t_done )
};
const txt_cmd_s PowerPlantOfficer1CeruleanShadyCharacterText[] = {
    text_start("I just got word"
        t_line "from CERULEAN."
        t_para "It appears that a"
        t_line "shady character"
        t_para "has been loitering"
        t_line "around."
        t_done )
};
const txt_cmd_s PowerPlantOfficer1CouldIAskForYourCooperationText[] = {
    text_start("Could I ask for"
        t_line "your cooperation?"
        t_done )
};
const txt_cmd_s PowerPlantOfficer1HaveToBeefUpSecurityText[] = {
    text_start("We'll have to beef"
        t_line "up our security"
        t_cont "presence."
        t_done )
};
const txt_cmd_s PowerPlantGymGuide1SomeoneStoleAPartText[] = {
    text_start("Someone made off"
        t_line "with a part that's"
        t_para "essential for the"
        t_line "generator."
        t_para "Without it, the"
        t_line "new generator's"
        t_cont "useless!"
        t_done )
};
const txt_cmd_s PowerPlantGymGuide1GeneratorUpAndRunningText[] = {
    text_start("The generator's up"
        t_line "and running. It's"
        t_para "making electricity"
        t_line "to spare."
        t_done )
};
const txt_cmd_s PowerPlantGymGuide2PowerPlantUpAndRunningText[] = {
    text_start("This POWER PLANT"
        t_line "had been abandoned"
        t_cont "in the past."
        t_para "We got it back up"
        t_line "and running to"
        t_para "provide power to"
        t_line "the MAGNET TRAIN."
        t_done )
};
const txt_cmd_s PowerPlantGymGuide2GeneratorIsRunningAgainText[] = {
    text_start("The generator's"
        t_line "running again!"
        t_done )
};
const txt_cmd_s PowerPlantOfficer2ManagerHasBeenSadAndFuriousText[] = {
    text_start("The POWER PLANT's"
        t_line "MANAGER is up"
        t_cont "ahead."
        t_para "But since someone"
        t_line "wrecked the gener-"
        t_cont "ator, he's been"
        t_cont "both sad and"
        t_cont "furious…"
        t_done )
};
const txt_cmd_s PowerPlantOfficer2ManagerHasBeenCheerfulText[] = {
    text_start("Since the gener-"
        t_line "ator's been fixed,"
        t_para "the MANAGER has"
        t_line "been cheerful."
        t_done )
};
const txt_cmd_s PowerPlantGymGuide4MagnetTrainConsumesElectricityText[] = {
    text_start("The MAGNET TRAIN"
        t_line "consumes a lot of"
        t_cont "electricity."
        t_para "It can't move if"
        t_line "the new generator"
        t_cont "isn't operating."
        t_done )
};
const txt_cmd_s PowerPlantGymGuide4WeCanGetMagnetTrainRunningText[] = {
    text_start("All right! We can"
        t_line "finally get the"
        t_para "MAGNET TRAIN"
        t_line "running again."
        t_done )
};
const txt_cmd_s PowerPlantManagerWhoWouldRuinMyGeneratorText[] = {
    text_start("MANAGER: I, I, I'm"
        t_line "ready to blast"
        t_cont "someone!"
        t_para "Who would dare"
        t_line "ruin my generator?"
        t_para "I spent so much"
        t_line "time on it!"
        t_para "If I catch him,"
        t_line "he's going to get"
        t_para "a taste of my ZAP"
        t_line "CANNON!"
        t_done )
};
const txt_cmd_s PowerPlantManagerIWontForgiveCulpritText[] = {
    text_start("MANAGER: I won't"
        t_line "forgive him!"
        t_para "The culprit can"
        t_line "cry and apologize,"
        t_para "but I'll still"
        t_line "hammer him!"
        t_para "Gahahahah!"
        t_done )
};
const txt_cmd_s PowerPlantManagerThatsThePartText[] = {
    text_start("MANAGER: Ah! Yeah!"
        t_para "That's the missing"
        t_line "PART from my be-"
        t_cont "loved generator!"
        t_cont "You found it?"
        t_done )
};
const txt_cmd_s PowerPlantManagerTakeThisTMText[] = {
    text_start("Wahah! Thanks!"
        t_para "Here! Take this TM"
        t_line "as a reward!"
        t_done )
};
const txt_cmd_s PowerPlantManagerTM07IsZapCannonText[] = {
    text_start("MANAGER: TM07 is"
        t_line "my ZAP CANNON."
        t_para "It's a powerful"
        t_line "technique!"
        t_para "It's not what any-"
        t_line "one would consider"
        t_para "accurate, but it"
        t_line "packs a wallop!"
        t_done )
};
const txt_cmd_s PowerPlantManagerMyBelovedGeneratorText[] = {
    text_start("MANAGER: My be-"
        t_line "loved generator!"
        t_para "Keep pumping the"
        t_line "electricity out!"
        t_done )
    //db(0, 0) // filler
};
