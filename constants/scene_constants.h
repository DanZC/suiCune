// See data/maps/scenes.asm for which maps have scene variables.
// Each scene_script and coord_event is associated with a current scene ID.

// Scene variables default to 0.
#define SCENE_DEFAULT 0
// Often a map will have a one-time default event for scene 0, and switch to a
// do-nothing scene 1 when the event finishes.
#define SCENE_FINISHED 1
// A coord_event for scene -1 will always activate, regardless of the map's
// scene variable value.
#define SCENE_ALWAYS -1

// wPokecenter2FSceneID
enum {
    SCENE_POKECENTER2F_LEAVE_TRADE_CENTER = 1,
    SCENE_POKECENTER2F_LEAVE_COLOSSEUM,           // 2
    SCENE_POKECENTER2F_LEAVE_TIME_CAPSULE,        // 3
    SCENE_POKECENTER2F_LEAVE_MOBILE_TRADE_ROOM,   // 4
    SCENE_POKECENTER2F_LEAVE_MOBILE_BATTLE_ROOM,  // 5
};

// wPowerPlantSceneID
enum {
    SCENE_POWERPLANT_NOTHING,                // 0
    SCENE_POWERPLANT_GUARD_GETS_PHONE_CALL,  // 1
};

// wCeruleanGymSceneID
enum {
    SCENE_CERULEANGYM_NOTHING,         // 0
    SCENE_CERULEANGYM_GRUNT_RUNS_OUT,  // 1
};

// wRoute25SceneID
enum {
    SCENE_ROUTE25_NOTHING,      // 0
    SCENE_ROUTE25_MISTYS_DATE,  // 1
};

// wLancesRoomSceneID
enum {
    SCENE_LANCESROOM_APPROACH_LANCE = 1,  // 1
};

// wElmsLabSceneID
enum {
    SCENE_ELMSLAB_CANT_LEAVE = 1,         // 1
    SCENE_ELMSLAB_NOTHING,                // 2
    SCENE_ELMSLAB_MEET_OFFICER,           // 3
    SCENE_ELMSLAB_UNUSED,                 // 4
    SCENE_ELMSLAB_AIDE_GIVES_POTION,      // 5
    SCENE_ELMSLAB_AIDE_GIVES_POKE_BALLS,  // 6
};

// wRoute29SceneID
enum {
    SCENE_ROUTE29_NOTHING,         // 0
    SCENE_ROUTE29_CATCH_TUTORIAL,  // 1
};

// wCherrygroveCitySceneID
enum {
    SCENE_CHERRYGROVECITY_NOTHING,     // 0
    SCENE_CHERRYGROVECITY_MEET_RIVAL,  // 1
};

// wRoute32SceneID
enum {
    SCENE_ROUTE32_OFFER_SLOWPOKETAIL = 1,  // 1
    SCENE_ROUTE32_NOTHING,                 // 2
};

// wRoute35NationalParkGateSceneID
enum {
    SCENE_ROUTE35NATIONALPARKGATE_NOTHING,              // 0
    SCENE_ROUTE35NATIONALPARKGATE_UNUSED,               // 1
    SCENE_ROUTE35NATIONALPARKGATE_LEAVE_CONTEST_EARLY,  // 2
};

// wRoute36SceneID
enum {
    SCENE_ROUTE36_NOTHING,  // 0
    SCENE_ROUTE36_SUICUNE,  // 1
};

// wRoute36NationalParkGateSceneID
enum {
    SCENE_ROUTE36NATIONALPARKGATE_NOTHING,              // 0
    SCENE_ROUTE36NATIONALPARKGATE_UNUSED,               // 1
    SCENE_ROUTE36NATIONALPARKGATE_LEAVE_CONTEST_EARLY,  // 2
};

// wAzaleaTownSceneID
enum {
    SCENE_AZALEATOWN_NOTHING,               // 0
    SCENE_AZALEATOWN_RIVAL_BATTLE,          // 1
    SCENE_AZALEATOWN_KURT_RETURNS_GS_BALL,  // 2
};

// wGoldenrodGymSceneID
enum {
    SCENE_GOLDENRODGYM_NOTHING,               // 0
    SCENE_GOLDENRODGYM_WHITNEY_STOPS_CRYING,  // 1
};

// wRoute42SceneID
enum {
    SCENE_ROUTE42_NOTHING,  // 0
    SCENE_ROUTE42_SUICUNE,  // 1
};

// wCianwoodCitySceneID
enum {
    SCENE_CIANWOODCITY_NOTHING,             // 0
    SCENE_CIANWOODCITY_SUICUNE_AND_EUSINE,  // 1
};

// wBurnedTower1FSceneID
enum {
    SCENE_BURNEDTOWER1F_RIVAL_BATTLE = 1,  // 1
    SCENE_BURNEDTOWER1F_NOTHING,           // 2
};

// wRadioTower5FSceneID
enum {
    SCENE_RADIOTOWER5F_ROCKET_BOSS = 1,  // 1
    SCENE_RADIOTOWER5F_NOTHING,          // 2
};

// wRuinsOfAlphOutsideSceneID
enum {
    SCENE_RUINSOFALPHOUTSIDE_NOTHING,        // 0
    SCENE_RUINSOFALPHOUTSIDE_GET_UNOWN_DEX,  // 1
};

// wRuinsOfAlphResearchCenterSceneID
enum {
    SCENE_RUINSOFALPHRESEARCHCENTER_NOTHING,        // 0
    SCENE_RUINSOFALPHRESEARCHCENTER_GET_UNOWN_DEX,  // 1
};

// wRuinsOfAlphInnerChamberSceneID
enum {
    SCENE_RUINSOFALPHINNERCHAMBER_NOTHING,           // 0
    SCENE_RUINSOFALPHINNERCHAMBER_STRANGE_PRESENCE,  // 1
};

// wMahoganyMart1FSceneID
enum {
    SCENE_MAHOGANYMART1F_NOTHING,                // 0
    SCENE_MAHOGANYMART1F_LANCE_UNCOVERS_STAIRS,  // 1
};

// wTeamRocketBaseB2FSceneID
enum {
    SCENE_TEAMROCKETBASEB2F_ROCKET_BOSS = 1,  // 1
    SCENE_TEAMROCKETBASEB2F_ELECTRODES,       // 2
    SCENE_TEAMROCKETBASEB2F_NOTHING,          // 3
};

// wTeamRocketBaseB3FSceneID
enum {
    SCENE_TEAMROCKETBASEB3F_RIVAL_ENCOUNTER = 1,  // 1
    SCENE_TEAMROCKETBASEB3F_ROCKET_BOSS,          // 2
    SCENE_TEAMROCKETBASEB3F_NOTHING,              // 3
};

// wDragonsDenB1FSceneID
enum {
    SCENE_DRAGONSDENB1F_NOTHING,         // 0
    SCENE_DRAGONSDENB1F_CLAIR_GIVES_TM,  // 1
};

// wOlivinePortSceneID
enum {
    SCENE_OLIVINEPORT_LEAVE_SHIP = 1,  // 1
};

// wVermilionPortSceneID
enum {
    SCENE_VERMILIONPORT_LEAVE_SHIP = 1,  // 1
};

// wFastShip1FSceneID
enum {
    SCENE_FASTSHIP1F_ENTER_SHIP = 1,  // 1
    SCENE_FASTSHIP1F_MEET_GRANDPA,    // 2
};

// wBattleTower1FSceneID
enum {
    SCENE_BATTLETOWER1F_CHECKSTATE,
    SCENE_BATTLETOWER1F_NOOP,
};
