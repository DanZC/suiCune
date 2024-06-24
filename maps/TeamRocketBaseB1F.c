#include "../constants.h"
#include "../util/scripting.h"
#include "TeamRocketBaseB1F.h"
//// EVENTS
enum {
    TEAMROCKETBASEB1F_ROCKET1 = 2,
    TEAMROCKETBASEB1F_ROCKET2,
    TEAMROCKETBASEB1F_SCIENTIST,
    TEAMROCKETBASEB1F_POKE_BALL1,
    TEAMROCKETBASEB1F_POKE_BALL2,
    TEAMROCKETBASEB1F_POKE_BALL3,
};

const Script_fn_t TeamRocketBaseB1F_SceneScripts[] = {
    TeamRocketBaseB1F_MapScripts_DummyScene , //  SCENE_DEFAULT,
};

const struct MapCallback TeamRocketBaseB1F_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, TeamRocketBaseB1F_MapScripts_HideSecurityGrunt),
};

const struct MapScripts TeamRocketBaseB1F_MapScripts = {
    .scene_script_count = lengthof(TeamRocketBaseB1F_SceneScripts),
    .scene_scripts = TeamRocketBaseB1F_SceneScripts,

    .callback_count = lengthof(TeamRocketBaseB1F_MapCallbacks),
    .callbacks = TeamRocketBaseB1F_MapCallbacks,
};

static const struct CoordEvent TeamRocketBaseB1F_CoordEvents[] = {
    0,
};

static const struct BGEvent TeamRocketBaseB1F_BGEvents[] = {
    bg_event(19, 11, BGEVENT_READ, &TeamRocketBaseB1FSecretSwitch),
    bg_event(24, 1, BGEVENT_UP, &TeamRocketBaseB1FSecurityCamera),
    bg_event(6, 1, BGEVENT_UP, &TeamRocketBaseB1FSecurityCamera),
    bg_event(8, 15, BGEVENT_UP, &TeamRocketBaseB1FSecurityCamera),
    bg_event(22, 15, BGEVENT_UP, &TeamRocketBaseB1FSecurityCamera),
    bg_event(24, 5, BGEVENT_UP, &TeamRocketBaseB1FSecurityCamera),
    bg_event(20, 11, BGEVENT_READ, &TeamRocketBaseB1FBookshelf),
    bg_event(21, 11, BGEVENT_READ, &TeamRocketBaseB1FBookshelf),
    bg_event(3, 11, BGEVENT_ITEM, &TeamRocketBaseB1FHiddenRevive),
};

static const struct WarpEventData TeamRocketBaseB1F_WarpEvents[] = {
    warp_event(27, 2, MAHOGANY_MART_1F, 3),
    warp_event(3, 14, TEAM_ROCKET_BASE_B2F, 1),
    warp_event(5, 15, TEAM_ROCKET_BASE_B1F, 4),
    warp_event(25, 2, TEAM_ROCKET_BASE_B1F, 3),
};

static const struct ObjEvent TeamRocketBaseB1F_ObjectEvents[] = {
    object_event(0, 0, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_TEAM_ROCKET_BASE_SECURITY_GRUNTS),
    object_event(2, 4, SPRITE_ROCKET, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_TRAINER, 3, &TrainerGruntM16, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(18, 12, SPRITE_SCIENTIST, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_TRAINER, 3, &TrainerScientistJed, EVENT_TEAM_ROCKET_BASE_POPULATION),
    object_event(27, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB1FHyperPotion, EVENT_TEAM_ROCKET_BASE_B1F_HYPER_POTION),
    object_event(14, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB1FNugget, EVENT_TEAM_ROCKET_BASE_B1F_NUGGET),
    object_event(21, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TeamRocketBaseB1FGuardSpec, EVENT_TEAM_ROCKET_BASE_B1F_GUARD_SPEC),
};

const struct MapEvents TeamRocketBaseB1F_MapEvents = {
    .warp_event_count = lengthof(TeamRocketBaseB1F_WarpEvents),
    .warp_events = TeamRocketBaseB1F_WarpEvents,

    .coord_event_count = 0, // lengthof(TeamRocketBaseB1F_CoordEvents),
    .coord_events = TeamRocketBaseB1F_CoordEvents,

    .bg_event_count = lengthof(TeamRocketBaseB1F_BGEvents),
    .bg_events = TeamRocketBaseB1F_BGEvents,

    .obj_event_count = lengthof(TeamRocketBaseB1F_ObjectEvents),
    .obj_events = TeamRocketBaseB1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "TeamRocketBaseB1F.h"

bool TeamRocketBaseB1F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB1F_MapScripts_HideSecurityGrunt(script_s* s) {
    SCRIPT_BEGIN
    disappear(TEAMROCKETBASEB1F_ROCKET1)
    s_endcallback
    SCRIPT_END
}
bool SecurityCamera1a(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SECURITY_CAMERA_1)
    iftrue_jump(NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    checkevent(EVENT_TEAM_ROCKET_BASE_POPULATION)
    iftrue_jump(NoSecurityCamera)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 19, 2)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    turnobject(PLAYER, LEFT)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement1)
    scall(TrainerCameraGrunt1)
    ifequal_jump(TRUE, NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 19, 2)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement1)
    scall(TrainerCameraGrunt2)
    ifequal_jump(TRUE, NoSecurityCamera)
    setevent(EVENT_SECURITY_CAMERA_1)
    s_end
    SCRIPT_END
}
bool SecurityCamera1b(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SECURITY_CAMERA_1)
    iftrue_jump(NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    checkevent(EVENT_TEAM_ROCKET_BASE_POPULATION)
    iftrue_jump(NoSecurityCamera)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 19, 3)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    turnobject(PLAYER, LEFT)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement1)
    scall(TrainerCameraGrunt1)
    ifequal_jump(TRUE, NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 19, 3)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement1)
    scall(TrainerCameraGrunt2)
    ifequal_jump(TRUE, NoSecurityCamera)
    setevent(EVENT_SECURITY_CAMERA_1)
    s_end
    SCRIPT_END
}
bool SecurityCamera2a(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SECURITY_CAMERA_2)
    iftrue_jump(NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    checkevent(EVENT_TEAM_ROCKET_BASE_POPULATION)
    iftrue_jump(NoSecurityCamera)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 4, 7)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    turnobject(PLAYER, LEFT)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement2)
    scall(TrainerCameraGrunt1)
    ifequal_jump(TRUE, NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    turnobject(PLAYER, RIGHT)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 12, 5)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement3)
    scall(TrainerCameraGrunt2)
    ifequal_jump(TRUE, NoSecurityCamera)
    setevent(EVENT_SECURITY_CAMERA_2)
    s_end
    SCRIPT_END
}
bool SecurityCamera2b(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SECURITY_CAMERA_2)
    iftrue_jump(NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    checkevent(EVENT_TEAM_ROCKET_BASE_POPULATION)
    iftrue_jump(NoSecurityCamera)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 4, 8)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    turnobject(PLAYER, LEFT)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement4)
    scall(TrainerCameraGrunt1)
    ifequal_jump(TRUE, NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    turnobject(PLAYER, RIGHT)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 12, 5)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement5)
    scall(TrainerCameraGrunt2)
    ifequal_jump(TRUE, NoSecurityCamera)
    setevent(EVENT_SECURITY_CAMERA_2)
    s_end
    SCRIPT_END
}
bool SecurityCamera3a(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SECURITY_CAMERA_3)
    iftrue_jump(NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    checkevent(EVENT_TEAM_ROCKET_BASE_POPULATION)
    iftrue_jump(NoSecurityCamera)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 19, 6)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    turnobject(PLAYER, LEFT)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement1)
    scall(TrainerCameraGrunt1)
    ifequal_jump(TRUE, NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    turnobject(PLAYER, RIGHT)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 25, 11)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement6)
    scall(TrainerCameraGrunt2)
    ifequal_jump(TRUE, NoSecurityCamera)
    setevent(EVENT_SECURITY_CAMERA_3)
    s_end
    SCRIPT_END
}
bool SecurityCamera3b(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SECURITY_CAMERA_3)
    iftrue_jump(NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    checkevent(EVENT_TEAM_ROCKET_BASE_POPULATION)
    iftrue_jump(NoSecurityCamera)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 19, 7)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    turnobject(PLAYER, LEFT)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement1)
    scall(TrainerCameraGrunt1)
    ifequal_jump(TRUE, NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    turnobject(PLAYER, RIGHT)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 25, 12)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement7)
    scall(TrainerCameraGrunt2)
    ifequal_jump(TRUE, NoSecurityCamera)
    setevent(EVENT_SECURITY_CAMERA_3)
    s_end
    SCRIPT_END
}
bool SecurityCamera4(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SECURITY_CAMERA_4)
    iftrue_jump(NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    checkevent(EVENT_TEAM_ROCKET_BASE_POPULATION)
    iftrue_jump(NoSecurityCamera)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 17, 16)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    turnobject(PLAYER, LEFT)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement1)
    scall(TrainerCameraGrunt1)
    ifequal_jump(TRUE, NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    turnobject(PLAYER, RIGHT)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 25, 11)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement8)
    scall(TrainerCameraGrunt2)
    ifequal_jump(TRUE, NoSecurityCamera)
    setevent(EVENT_SECURITY_CAMERA_4)
    s_end
    SCRIPT_END
}
bool SecurityCamera5(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_SECURITY_CAMERA_5)
    iftrue_jump(NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    checkevent(EVENT_TEAM_ROCKET_BASE_POPULATION)
    iftrue_jump(NoSecurityCamera)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 3, 16)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    turnobject(PLAYER, LEFT)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement1)
    scall(TrainerCameraGrunt1)
    ifequal_jump(TRUE, NoSecurityCamera)
    scall(PlaySecurityCameraSounds)
    showemote(EMOTE_SHOCK, PLAYER, 15)
    playmusic(MUSIC_ROCKET_ENCOUNTER)
    turnobject(PLAYER, RIGHT)
    moveobject(TEAMROCKETBASEB1F_ROCKET1, 14, 16)
    appear(TEAMROCKETBASEB1F_ROCKET1)
    applymovement(TEAMROCKETBASEB1F_ROCKET1, SecurityCameraMovement9)
    scall(TrainerCameraGrunt2)
    ifequal_jump(TRUE, NoSecurityCamera)
    setevent(EVENT_SECURITY_CAMERA_5)
    s_end
    SCRIPT_END
}
bool NoSecurityCamera(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TrainerCameraGrunt1(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CameraGrunt1SeenText)
    waitbutton
    closetext
    winlosstext(CameraGrunt1BeatenText, 0)
    setlasttalked(TEAMROCKETBASEB1F_ROCKET1)
    loadtrainer(GRUNTM, GRUNTM_20)
    startbattle
    disappear(TEAMROCKETBASEB1F_ROCKET1)
    reloadmapafterbattle
    s_end
    SCRIPT_END
}
bool TrainerCameraGrunt2(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CameraGrunt2SeenText)
    waitbutton
    closetext
    winlosstext(CameraGrunt2BeatenText, 0)
    setlasttalked(TEAMROCKETBASEB1F_ROCKET1)
    loadtrainer(GRUNTM, GRUNTM_21)
    startbattle
    disappear(TEAMROCKETBASEB1F_ROCKET1)
    reloadmapafterbattle
    s_end
    SCRIPT_END
}
bool PlaySecurityCameraSounds(script_s* s) {
    SCRIPT_BEGIN
    playsound(SFX_LICK)
    pause(10)
    playsound(SFX_LICK)
    pause(10)
    playsound(SFX_LICK)
    pause(10)
    playsound(SFX_LICK)
    pause(10)
    playsound(SFX_LICK)
    pause(10)
    playsound(SFX_LICK)
    s_end
    SCRIPT_END
}
bool ExplodingTrap1(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_1)
    iftrue_jump(NoExplodingTrap)
    scall(KoffingExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_1)
    s_end
    SCRIPT_END
}
bool ExplodingTrap2(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_2)
    iftrue_jump(NoExplodingTrap)
    scall(VoltorbExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_2)
    s_end
    SCRIPT_END
}
bool ExplodingTrap3(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_3)
    iftrue_jump(NoExplodingTrap)
    scall(GeodudeExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_3)
    s_end
    SCRIPT_END
}
bool ExplodingTrap4(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_4)
    iftrue_jump(NoExplodingTrap)
    scall(VoltorbExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_4)
    s_end
    SCRIPT_END
}
bool ExplodingTrap5(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_5)
    iftrue_jump(NoExplodingTrap)
    scall(GeodudeExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_5)
    s_end
    SCRIPT_END
}
bool ExplodingTrap6(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_6)
    iftrue_jump(NoExplodingTrap)
    scall(KoffingExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_6)
    s_end
    SCRIPT_END
}
bool ExplodingTrap7(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_7)
    iftrue_jump(NoExplodingTrap)
    scall(VoltorbExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_7)
    s_end
    SCRIPT_END
}
bool ExplodingTrap8(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_8)
    iftrue_jump(NoExplodingTrap)
    scall(KoffingExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_8)
    s_end
    SCRIPT_END
}
bool ExplodingTrap9(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_9)
    iftrue_jump(NoExplodingTrap)
    scall(KoffingExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_9)
    s_end
    SCRIPT_END
}
bool ExplodingTrap10(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_10)
    iftrue_jump(NoExplodingTrap)
    scall(VoltorbExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_10)
    s_end
    SCRIPT_END
}
bool ExplodingTrap11(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_11)
    iftrue_jump(NoExplodingTrap)
    scall(GeodudeExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_11)
    s_end
    SCRIPT_END
}
bool ExplodingTrap12(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_12)
    iftrue_jump(NoExplodingTrap)
    scall(GeodudeExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_12)
    s_end
    SCRIPT_END
}
bool ExplodingTrap13(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_13)
    iftrue_jump(NoExplodingTrap)
    scall(GeodudeExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_13)
    s_end
    SCRIPT_END
}
bool ExplodingTrap14(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_14)
    iftrue_jump(NoExplodingTrap)
    scall(KoffingExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_14)
    s_end
    SCRIPT_END
}
bool ExplodingTrap15(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_15)
    iftrue_jump(NoExplodingTrap)
    scall(VoltorbExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_15)
    s_end
    SCRIPT_END
}
bool ExplodingTrap16(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_16)
    iftrue_jump(NoExplodingTrap)
    scall(KoffingExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_16)
    s_end
    SCRIPT_END
}
bool ExplodingTrap17(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_17)
    iftrue_jump(NoExplodingTrap)
    scall(VoltorbExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_17)
    s_end
    SCRIPT_END
}
bool ExplodingTrap18(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_18)
    iftrue_jump(NoExplodingTrap)
    scall(GeodudeExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_18)
    s_end
    SCRIPT_END
}
bool ExplodingTrap19(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_19)
    iftrue_jump(NoExplodingTrap)
    scall(GeodudeExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_19)
    s_end
    SCRIPT_END
}
bool ExplodingTrap20(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_20)
    iftrue_jump(NoExplodingTrap)
    scall(VoltorbExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_20)
    s_end
    SCRIPT_END
}
bool ExplodingTrap21(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_21)
    iftrue_jump(NoExplodingTrap)
    scall(KoffingExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_21)
    s_end
    SCRIPT_END
}
bool ExplodingTrap22(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_EXPLODING_TRAP_22)
    iftrue_jump(NoExplodingTrap)
    scall(VoltorbExplodingTrap)
    reloadmapafterbattle
    setevent(EVENT_EXPLODING_TRAP_22)
    s_end
    SCRIPT_END
}
bool VoltorbExplodingTrap(script_s* s) {
    SCRIPT_BEGIN
    special(FadeOutPalettes)
    playcry(VOLTORB)
    special(FadeInPalettes)
    setlasttalked(-1)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_TRAP)
    loadwildmon(VOLTORB, 23)
    startbattle
    s_end
    SCRIPT_END
}
bool GeodudeExplodingTrap(script_s* s) {
    SCRIPT_BEGIN
    special(FadeOutPalettes)
    playcry(GEODUDE)
    special(FadeInPalettes)
    setlasttalked(-1)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_TRAP)
    loadwildmon(GEODUDE, 21)
    startbattle
    s_end
    SCRIPT_END
}
bool KoffingExplodingTrap(script_s* s) {
    SCRIPT_BEGIN
    special(FadeOutPalettes)
    playcry(KOFFING)
    special(FadeInPalettes)
    setlasttalked(-1)
    loadvar(VAR_BATTLETYPE, BATTLETYPE_TRAP)
    loadwildmon(KOFFING, 21)
    startbattle
    s_end
    SCRIPT_END
}
bool NoExplodingTrap(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerScientistJed = {SCIENTIST, JED, EVENT_BEAT_SCIENTIST_JED, ScientistJedSeenText, ScientistJedBeatenText, 0, TrainerScientistJed_Script};
bool TrainerScientistJed_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(ScientistJedAfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TrainerObj TrainerGruntM16 = {GRUNTM, GRUNTM_16, EVENT_BEAT_ROCKET_GRUNTM_16, GruntM16SeenText, GruntM16BeatenText, 0, TrainerGruntM16_Script};
bool TrainerGruntM16_Script(script_s* s) {
    SCRIPT_BEGIN
    endifjustbattled
    opentext
    writetext(GruntM16AfterBattleText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TeamRocketBaseB1FSecurityCamera(script_s* s) {
    SCRIPT_BEGIN
    jumptext(TeamRocketBaseB1FSecurityCameraText)
    SCRIPT_END
}
bool TeamRocketBaseB1FBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(TeamRocketOathScript)
    SCRIPT_END
}
bool TeamRocketBaseB1FSecretSwitch(script_s* s) {
    SCRIPT_BEGIN
    opentext
    checkevent(EVENT_TURNED_OFF_SECURITY_CAMERAS)
    iftrue(SecretSwitchOff)
    writetext(TeamRocketBaseB1FSecretSwitchText)
    playsound(SFX_TALLY)
    waitbutton
    closetext
    setevent(EVENT_TURNED_OFF_SECURITY_CAMERAS)
    setevent(EVENT_SECURITY_CAMERA_1)
    setevent(EVENT_SECURITY_CAMERA_2)
    setevent(EVENT_SECURITY_CAMERA_3)
    setevent(EVENT_SECURITY_CAMERA_4)
    setevent(EVENT_SECURITY_CAMERA_5)
    s_end
SecretSwitchOff:
    writetext(TeamRocketBaseB1FSwitchOffText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct ItemBall TeamRocketBaseB1FHyperPotion = {HYPER_POTION, 1};
const struct ItemBall TeamRocketBaseB1FNugget = {NUGGET, 1};
const struct ItemBall TeamRocketBaseB1FGuardSpec = {GUARD_SPEC, 1};
const struct HiddenItem TeamRocketBaseB1FHiddenRevive = {REVIVE, EVENT_TEAM_ROCKET_BASE_B1F_HIDDEN_REVIVE};
const uint8_t SecurityCameraMovement1[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    movement_step_end,
};
const uint8_t SecurityCameraMovement2[] = {
    big_step(UP),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t SecurityCameraMovement3[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t SecurityCameraMovement4[] = {
// he jumps over a trap
    jump_step(UP),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t SecurityCameraMovement5[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t SecurityCameraMovement6[] = {
    big_step(UP),
    big_step(UP),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t SecurityCameraMovement7[] = {
    big_step(UP),
    big_step(UP),
    big_step(UP),
    big_step(RIGHT),
    big_step(UP),
    big_step(UP),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t SecurityCameraMovement8[] = {
    big_step(DOWN),
    big_step(DOWN),
    big_step(RIGHT),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const uint8_t SecurityCameraMovement9[] = {
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    big_step(LEFT),
    movement_step_end,
};
const txt_cmd_s CameraGrunt1SeenText[] = {
    text_start("Hey!"
        t_line "Intruder alert!"
        t_done )
};
const txt_cmd_s CameraGrunt1BeatenText[] = {
    text_start("Dang… I failed…"
        t_done )
};
const txt_cmd_s CameraGrunt2SeenText[] = {
    text_start("It's my turn!"
        t_line "There's no escape!"
        t_done )
};
const txt_cmd_s CameraGrunt2BeatenText[] = {
    text_start("Surveillance cams"
        t_line "are in the #MON"
        t_cont "statues."
        t_para "We'll keep appear-"
        t_line "ing until you trip"
        t_cont "a secret switch."
        t_done )
};
const txt_cmd_s ScientistJedSeenText[] = {
    text_start("This was once a"
        t_line "ninja hideout."
        t_para "There are traps to"
        t_line "confound intruders"
        t_cont "like you."
        t_done )
};
const txt_cmd_s ScientistJedBeatenText[] = {
    text_start("I get it…"
        t_done )
};
const txt_cmd_s ScientistJedAfterBattleText[] = {
    text_start("All right. I'll"
        t_line "divulge a secret"
        t_cont "about our hideout."
        t_para "That thing on the"
        t_line "floor up ahead is"
        t_cont "a warp panel."
        t_para "If you step on it,"
        t_line "you'll be warped"
        t_para "back to the en-"
        t_line "trance."
        t_done )
};
const txt_cmd_s GruntM16SeenText[] = {
    text_start("Heheh. Feeling"
        t_line "lucky, punk?"
        t_para "Go ahead, take"
        t_line "another step."
        t_para "We've got traps"
        t_line "set in the floor!"
        t_done )
};
const txt_cmd_s GruntM16BeatenText[] = {
    text_start("Kaboom!"
        t_done )
};
const txt_cmd_s GruntM16AfterBattleText[] = {
    text_start("I don't even know"
        t_line "where the traps"
        t_cont "are planted."
        t_para "You'll just have"
        t_line "to collect your"
        t_cont "courage and walk."
        t_done )
};
const txt_cmd_s TeamRocketBaseB1FSecurityCameraText[] = {
    text_start("It's a PERSIAN"
        t_line "statue…"
        t_para "Its eyes are oddly"
        t_line "shiny."
        t_done )
};
const txt_cmd_s TeamRocketBaseB1FSecretSwitchText[] = {
    text_start("A secret switch!"
        t_line "Better press it."
        t_done )
};
const txt_cmd_s TeamRocketBaseB1FSwitchOffText[] = {
    text_start("The switch is"
        t_line "turned off."
        t_done )
    //db(0, 0) // filler
    // There are five security cameras in the base.
    // Walking in front of one triggers two Rocket Grunts.
    //coord_event(24, 2, SCENE_DEFAULT, SecurityCamera1a)
    //coord_event(24, 3, SCENE_DEFAULT, SecurityCamera1b)
    //coord_event(6, 2, SCENE_DEFAULT, SecurityCamera2a)
    //coord_event(6, 3, SCENE_DEFAULT, SecurityCamera2b)
    //coord_event(24, 6, SCENE_DEFAULT, SecurityCamera3a)
    //coord_event(24, 7, SCENE_DEFAULT, SecurityCamera3b)
    //coord_event(22, 16, SCENE_DEFAULT, SecurityCamera4)
    //coord_event(8, 16, SCENE_DEFAULT, SecurityCamera5)
    // There are spots on the floor that trigger a Pokémon battle.
    // Each Pokémon (Voltorb, Koffing, Geodude) knows Selfdestruct.
    //coord_event(2, 7, SCENE_DEFAULT, ExplodingTrap1)
    //coord_event(3, 7, SCENE_DEFAULT, ExplodingTrap2)
    //coord_event(4, 7, SCENE_DEFAULT, ExplodingTrap3)
    //coord_event(1, 8, SCENE_DEFAULT, ExplodingTrap4)
    //coord_event(3, 8, SCENE_DEFAULT, ExplodingTrap5)
    //coord_event(5, 8, SCENE_DEFAULT, ExplodingTrap6)
    //coord_event(3, 9, SCENE_DEFAULT, ExplodingTrap7)
    //coord_event(4, 9, SCENE_DEFAULT, ExplodingTrap8)
    //coord_event(1, 10, SCENE_DEFAULT, ExplodingTrap9)
    //coord_event(2, 10, SCENE_DEFAULT, ExplodingTrap10)
    //coord_event(3, 10, SCENE_DEFAULT, ExplodingTrap11)
    //coord_event(5, 10, SCENE_DEFAULT, ExplodingTrap12)
    //coord_event(2, 11, SCENE_DEFAULT, ExplodingTrap13)
    //coord_event(4, 11, SCENE_DEFAULT, ExplodingTrap14)
    //coord_event(1, 12, SCENE_DEFAULT, ExplodingTrap15)
    //coord_event(2, 12, SCENE_DEFAULT, ExplodingTrap16)
    //coord_event(4, 12, SCENE_DEFAULT, ExplodingTrap17)
    //coord_event(5, 12, SCENE_DEFAULT, ExplodingTrap18)
    //coord_event(1, 13, SCENE_DEFAULT, ExplodingTrap19)
    //coord_event(3, 13, SCENE_DEFAULT, ExplodingTrap20)
    //coord_event(4, 13, SCENE_DEFAULT, ExplodingTrap21)
    //coord_event(5, 13, SCENE_DEFAULT, ExplodingTrap22)
};
