// object constants
#define PLAYER 0
#define LAST_TALKED -2

// string buffer constants
enum {
    STRING_BUFFER_3,  // use wStringBuffer3
    STRING_BUFFER_4,  // use wStringBuffer4
    STRING_BUFFER_5,  // use wStringBuffer5
    NUM_STRING_BUFFERS,
};

#define STRING_BUFFER_LENGTH 19

// checkmoney/takemoney accounts
enum {
    YOUR_MONEY,  // 0
    MOMS_MONEY,  // 1
};

// checkmoney/checkcoins return values
enum {
    HAVE_MORE,    // 0
    HAVE_AMOUNT,  // 1
    HAVE_LESS,    // 2
};

// checkpokemail return values
enum {
    POKEMAIL_WRONG_MAIL,  // 0
    POKEMAIL_CORRECT,     // 1
    POKEMAIL_REFUSED,     // 2
    POKEMAIL_NO_MAIL,     // 3
    POKEMAIL_LAST_MON,    // 4
};

// askforphonenumber return values
enum {
    PHONE_CONTACT_GOT,      // 0
    PHONE_CONTACTS_FULL,    // 1
    PHONE_CONTACT_REFUSED,  // 2
};

// trainertext arguments
enum {
    TRAINERTEXT_SEEN,
    TRAINERTEXT_WIN,
    TRAINERTEXT_LOSS,
};

// readvar/writevar/loadvar arguments
// _GetVarAction.VarActionTable indexes (see engine/overworld/variables.asm)
enum {
    VAR_STRINGBUFFER2,     // 00
    VAR_PARTYCOUNT,        // 01
    VAR_BATTLERESULT,      // 02
    VAR_BATTLETYPE,        // 03
    VAR_TIMEOFDAY,         // 04
    VAR_DEXCAUGHT,         // 05
    VAR_DEXSEEN,           // 06
    VAR_BADGES,            // 07
    VAR_MOVEMENT,          // 08
    VAR_FACING,            // 09
    VAR_HOUR,              // 0a
    VAR_WEEKDAY,           // 0b
    VAR_MAPGROUP,          // 0c
    VAR_MAPNUMBER,         // 0d
    VAR_UNOWNCOUNT,        // 0e
    VAR_ENVIRONMENT,       // 0f
    VAR_BOXSPACE,          // 10
    VAR_CONTESTMINUTES,    // 11
    VAR_XCOORD,            // 12
    VAR_YCOORD,            // 13
    VAR_SPECIALPHONECALL,  // 14
    VAR_BT_WIN_STREAK,     // 15
    VAR_KURT_APRICORNS,    // 16
    VAR_CALLERID,          // 17
    VAR_BLUECARDBALANCE,   // 18
    VAR_BUENASPASSWORD,    // 19
    VAR_KENJI_BREAK,       // 1a
    NUM_VARS,
};

// variable action types
#define RETVAR_STRBUF2 (0 << 6)
#define RETVAR_ADDR_DE (1 << 6)
#define RETVAR_EXECUTE (2 << 6)

// PlayerEventScriptPointers indexes (see engine/overworld/events.asm)
enum {
    PLAYEREVENT_MAPSCRIPT = -1,
    PLAYEREVENT_NONE,
    PLAYEREVENT_SEENBYTRAINER,
    PLAYEREVENT_TALKTOTRAINER,
    PLAYEREVENT_ITEMBALL,
    PLAYEREVENT_CONNECTION,
    PLAYEREVENT_WARP,
    PLAYEREVENT_FALL,
    PLAYEREVENT_WHITEOUT,
    PLAYEREVENT_HATCH,
    PLAYEREVENT_JOYCHANGEFACING,
    NUM_PLAYER_EVENTS,
};

// PlayerMovementPointers indexes (see engine/overworld/events.asm)
enum {
    PLAYERMOVEMENT_NORMAL,
    PLAYERMOVEMENT_WARP,
    PLAYERMOVEMENT_TURN,
    PLAYERMOVEMENT_FORCE_TURN,
    PLAYERMOVEMENT_FINISH,
    PLAYERMOVEMENT_CONTINUE,
    PLAYERMOVEMENT_EXIT_WATER,
    PLAYERMOVEMENT_JUMP,
    NUM_PLAYER_MOVEMENTS,
};

// script data sizes (see macros/scripts/maps.asm)
#define SCENE_SCRIPT_SIZE 4   // scene_script
#define CALLBACK_SIZE 3       // callback
#define WARP_EVENT_SIZE 5     // warp_event
#define COORD_EVENT_SIZE 8    // coord_event
#define BG_EVENT_SIZE 5       // bg_event
#define OBJECT_EVENT_SIZE 13  // object_event

// bg_event types
// BGEventJumptable indexes (see engine/overworld/events.asm)
enum {
    BGEVENT_READ,
    BGEVENT_UP,
    BGEVENT_DOWN,
    BGEVENT_RIGHT,
    BGEVENT_LEFT,
    BGEVENT_IFSET,
    BGEVENT_IFNOTSET,
    BGEVENT_ITEM,
    BGEVENT_COPY,
    NUM_BGEVENTS,
};

// object_event types
// ObjectEventTypeArray indexes (see engine/overworld/events.asm)
enum {
    OBJECTTYPE_SCRIPT,
    OBJECTTYPE_ITEMBALL,
    OBJECTTYPE_TRAINER,
    OBJECTTYPE_3,
    OBJECTTYPE_4,
    OBJECTTYPE_5,
    OBJECTTYPE_6,
    NUM_OBJECT_TYPES,
};

// command queue members
#define CMDQUEUE_TYPE 0
#define CMDQUEUE_ADDR 1
#define CMDQUEUE_02 2
#define CMDQUEUE_03 3
#define CMDQUEUE_04 4
#define CMDQUEUE_05 5
#define CMDQUEUE_ENTRY_SIZE 6
#define CMDQUEUE_CAPACITY 4

// #define Handl euedCommand.Jumptable indexes (see engine/overworld/events.asm)
enum {
    CMDQUEUE_NULL,
    CMDQUEUE_TYPE1,
    CMDQUEUE_STONETABLE,
    CMDQUEUE_TYPE3,
    CMDQUEUE_TYPE4,
    NUM_CMDQUEUE_TYPES,
};

// elevfloor macro values
// ElevatorFloorNames indexes (see data/events/elevator_floors.asm)
enum {
    FLOOR_B4F,
    FLOOR_B3F,
    FLOOR_B2F,
    FLOOR_B1F,
    FLOOR_1F,
    FLOOR_2F,
    FLOOR_3F,
    FLOOR_4F,
    FLOOR_5F,
    FLOOR_6F,
    FLOOR_7F,
    FLOOR_8F,
    FLOOR_9F,
    FLOOR_10F,
    FLOOR_11F,
    FLOOR_ROOF,
    NUM_FLOORS,
};

// showemote arguments
// Emotes indexes (see data/sprites/emotes.asm)
enum {
    EMOTE_SHOCK,
    EMOTE_QUESTION,
    EMOTE_HAPPY,
    EMOTE_SAD,
    EMOTE_HEART,
    EMOTE_BOLT,
    EMOTE_SLEEP,
    EMOTE_FISH,
    EMOTE_SHADOW,
    EMOTE_ROD,
    EMOTE_BOULDER_DUST,
    EMOTE_GRASS_RUSTLE,
    NUM_EMOTES,
};
#define EMOTE_FROM_MEM -1
#define EMOTE_LENGTH 6

// fruittree arguments
// FruitTreeItems indexes (see data/items/fruit_trees.asm)
enum {
    FRUITTREE_ROUTE_29,       // 01
    FRUITTREE_ROUTE_30_1,     // 02
    FRUITTREE_ROUTE_38,       // 03
    FRUITTREE_ROUTE_46_1,     // 04
    FRUITTREE_ROUTE_30_2,     // 05
    FRUITTREE_ROUTE_33,       // 06
    FRUITTREE_ROUTE_31,       // 07
    FRUITTREE_ROUTE_43,       // 08
    FRUITTREE_VIOLET_CITY,    // 09
    FRUITTREE_ROUTE_46_2,     // 0a
    FRUITTREE_ROUTE_35,       // 0b
    FRUITTREE_ROUTE_45,       // 0c
    FRUITTREE_ROUTE_36,       // 0d
    FRUITTREE_ROUTE_26,       // 0e
    FRUITTREE_ROUTE_39,       // 0f
    FRUITTREE_ROUTE_44,       // 10
    FRUITTREE_ROUTE_37_1,     // 11
    FRUITTREE_ROUTE_37_2,     // 12
    FRUITTREE_ROUTE_37_3,     // 13
    FRUITTREE_AZALEA_TOWN,    // 14
    FRUITTREE_ROUTE_42_1,     // 15
    FRUITTREE_ROUTE_42_2,     // 16
    FRUITTREE_ROUTE_42_3,     // 17
    FRUITTREE_ROUTE_11,       // 18
    FRUITTREE_ROUTE_2,        // 19
    FRUITTREE_ROUTE_1,        // 1a
    FRUITTREE_ROUTE_8,        // 1b
    FRUITTREE_PEWTER_CITY_1,  // 1c
    FRUITTREE_PEWTER_CITY_2,  // 1d
    FRUITTREE_FUCHSIA_CITY,   // 1e
    NUM_FRUIT_TREES
};

// describedecoration arguments
// DescribeDecoration.JumpTable indexes (see engine/overworld/decorations.asm)
enum {
    DECODESC_POSTER,      // 0
    DECODESC_LEFT_DOLL,   // 1
    DECODESC_RIGHT_DOLL,  // 2
    DECODESC_BIG_DOLL,    // 3
    DECODESC_CONSOLE,     // 4
    NUM_DECODESCS,
};

// swarm arguments
// StoreSwarmMapIndices arguments
enum {
    SWARM_DUNSPARCE,  // 0
    SWARM_YANMA,      // 1
};

// ActivateFishingSwarm setval arguments
enum {
    FISHSWARM_NONE,      // 0
    FISHSWARM_QWILFISH,  // 1
    FISHSWARM_REMORAID,  // 2
};

// SpecialGameboyCheck return values
enum {
    GBCHECK_GB,   // 0
    GBCHECK_SGB,  // 1
    GBCHECK_CGB,  // 2
};

// CheckMagikarpLength return values
enum {
    MAGIKARPLENGTH_NOT_MAGIKARP,  // 0
    MAGIKARPLENGTH_REFUSED,       // 1
    MAGIKARPLENGTH_TOO_SHORT,     // 2
    MAGIKARPLENGTH_BEAT_RECORD,   // 3
};

// ReturnShuckie return values
enum {
    SHUCKIE_WRONG_MON,  // 0
    SHUCKIE_REFUSED,    // 1
    SHUCKIE_RETURNED,   // 2
    SHUCKIE_HAPPY,      // 3
    SHUCKIE_FAINTED,    // 4
};

// CheckPartyFullAfterContest return values
enum {
    BUGCONTEST_CAUGHT_MON,  // 0
    BUGCONTEST_BOXED_MON,   // 1
    BUGCONTEST_NO_CATCH,    // 2
};

// Bug-Catching Contest values
#define BUG_CONTEST_BALLS 20
#define BUG_CONTEST_MINUTES 20
#define BUG_CONTEST_SECONDS 0
#define BUG_CONTEST_PLAYER 1
#define NUM_BUG_CONTESTANTS 10  // not counting the player
#define BUG_CONTESTANT_SIZE 4

// HealMachineAnim setval arguments
// HealMachineAnim.Pointers indexes (see engine/events/heal_machine_anim.asm)
enum {
    HEALMACHINE_POKECENTER,    // 0
    HEALMACHINE_ELMS_LAB,      // 1
    HEALMACHINE_HALL_OF_FAME,  // 2
};

// UnownPuzzle setval arguments
// LoadUnownPuzzlePiecesGFX.LZPointers indexes (see engine/games/unown_puzzle.asm)
enum {
    UNOWNPUZZLE_KABUTO,      // 0
    UNOWNPUZZLE_OMANYTE,     // 1
    UNOWNPUZZLE_AERODACTYL,  // 2
    UNOWNPUZZLE_HO_OH,       // 3
    NUM_UNOWN_PUZZLES,
};

// DisplayUnownWords setval arguments
// UnownWalls and MenuHeaders_UnownWalls indexes (see data/events/unown_walls.asm)
enum {
    UNOWNWORDS_ESCAPE,  // 0
    UNOWNWORDS_LIGHT,   // 1
    UNOWNWORDS_WATER,   // 2
    UNOWNWORDS_HO_OH,   // 3
};

// MoveTutor setval arguments
enum {
    MOVETUTOR_FLAMETHROWER = 1,  // 1
    MOVETUTOR_THUNDERBOLT,       // 2
    MOVETUTOR_ICE_BEAM,          // 3
};