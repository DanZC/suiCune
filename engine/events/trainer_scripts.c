#include "../../constants.h"
#include "../../util/scripting.h"
#include "trainer_scripts.h"
#include "../overworld/player_object.h"

bool TalkToTrainerScript(script_s* s){
    SCRIPT_BEGIN
    faceplayer
    trainerflagaction(CHECK_FLAG)
    iftrue_jump(AlreadyBeatenTrainerScript)
    loadtemptrainer
    encountermusic
    sjump(StartBattleWithMapTrainerScript)
    SCRIPT_END
}

bool SeenByTrainerScript(script_s* s){
    SCRIPT_BEGIN
    loadtemptrainer
    encountermusic
    showemote(EMOTE_SHOCK, LAST_TALKED, 30)
    TrainerWalkToPlayer();
    applymovementlasttalked(wram_ptr(wMovementBuffer))
    writeobjectxy(LAST_TALKED)
    faceobject(PLAYER, LAST_TALKED)
    sjump(StartBattleWithMapTrainerScript)
    SCRIPT_END
}

bool StartBattleWithMapTrainerScript(script_s* s){
    SCRIPT_BEGIN
    opentext
    trainertext(TRAINERTEXT_SEEN)
    waitbutton
    closetext
    loadtemptrainer
    startbattle
    reloadmapafterbattle
    trainerflagaction(SET_FLAG)
    loadmem(wram_ptr(wRunningTrainerBattleScript), -1)
    SCRIPT_FALLTHROUGH(AlreadyBeatenTrainerScript)
}

bool AlreadyBeatenTrainerScript(script_s* s){
    SCRIPT_BEGIN
    scripttalkafter
    SCRIPT_END
}
