
// Utility types

typedef struct { uint8_t a; bool flag; } u8_flag_s;

#define u8_flag(_u8, _flag) (u8_flag_s){.a = _u8, .flag = _flag}

typedef struct { uint8_t a; uint8_t b; } u8_pair_s;

#define u8_pair(_a, _b) (u8_pair_s){.a = _a, .b = _b}

typedef struct { uint8_t a; uint8_t b; bool flag; } u8_pair_flag_s;
#define u8_pair_flag(_a, _b, _flag) (u8_pair_flag_s){.a = _a, .b = _b, .flag = _flag}

typedef struct { uint32_t a; bool flag; }  u32_flag_s;
#define u32_flag(_a, _flag) (u32_flag_s){.a = _a, .flag = _flag}

typedef struct { int a; bool flag; }  int_flag_s;
#define int_flag(_a, _flag) (int_flag_s){.a = _a, .flag = _flag}

typedef struct { uint16_t a; uint16_t b; } u16_pair_s;
#ifdef _MSC_VER
#define u16_pair(_a, _b) { _a, _b }
#else
#define u16_pair(_a, _b) (u16_pair_s){.a = _a, .b = _b}
#endif

typedef struct U8PtrPair {
    uint8_t* hl;
    uint8_t* de;
} u8_ptr_pair_s;

struct ByteWord 
{
    uint8_t byte;
    uint16_t word;
};

struct WordByte
{
    uint16_t word;
    uint8_t byte;
};

struct Coords
{
    int8_t x;
    int8_t y;
};

struct BankAddr
{
    uint8_t bank;
    uint16_t addr;
};

struct MapId {
    uint8_t mapGroup;
    uint8_t mapNumber;
};

struct TrainerId {
    uint8_t trainerClass;
    uint8_t trainerId;
};

struct ItemEffect {
    uint8_t param;
    uint8_t effect;
};

// Configurable types

typedef uint8_t species_t;      // Mon species type
typedef uint8_t unown_letter_t; // Unown letter type
typedef uint8_t dex_t;          // Dex number type
typedef uint8_t item_t;         // Item id type
typedef uint8_t move_t;         // Move id type

typedef uint8_t tile_t;
typedef uint16_t sfx_t;

// ROM structs

#if defined(__cplusplus) || defined(_MSC_VER)
#pragma pack(push, 1)
#endif

struct BattleAnim
{
    uint8_t index;
    uint8_t oamFlags;
    uint8_t fixY;
    uint8_t framesetId;
    uint8_t function;
    uint8_t palette;
    uint8_t tileId;
    uint8_t xCoord;
    uint8_t yCoord;
    uint8_t xOffset;
    uint8_t yOffset;
    uint8_t param;
    uint8_t duration;
    uint8_t frame;
    uint8_t jumptableIndex;
    uint8_t var1;
    uint8_t var2;
    uint8_t padding[7];
};

struct BattleAnimObj 
{
    uint8_t flags;
    uint8_t enemyAnim;
    uint8_t videoSeq;
    uint8_t callback;
    uint8_t palette;
    uint8_t tileOffset;
};

struct BattleAnimGFX
{
    uint8_t tiles;
    const char* gfxPath;
};

struct ItemAttr
{
    uint16_t price;
    uint8_t effect;
    uint8_t param;
    uint8_t permissions;
    uint8_t pocket;
    uint8_t helpField: 4;
    uint8_t helpBattle: 4;
};

struct Map
{
    uint8_t mapAttrBank;
    uint8_t tileset;
    uint8_t environment;
    uint16_t mapAttr;
    uint8_t mapLocation;
    uint8_t music;
    uint8_t palette;
    uint8_t fishGroup;
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
Object
{
    uint8_t sprite;
    uint8_t mapObjectIndex;
    uint8_t spriteTile;
    uint8_t movementType;
    uint8_t flags1;
    uint8_t flags2;
    uint8_t palette;
    uint8_t dirWalking;
    uint8_t facing;
    uint8_t stepType;
    uint8_t stepDuration;
    uint8_t action;
    uint8_t stepFrame;
    uint8_t facingStep;
    uint8_t nextTile;
    uint8_t standingTile;
    uint8_t nextMapX;
    uint8_t nextMapY;
    uint8_t mapX;
    uint8_t mapY;
    uint8_t initX;
    uint8_t initY;
    uint8_t radius;
    uint8_t spriteX;
    uint8_t spriteY;
    uint8_t spriteXOffset;
    uint8_t spriteYOffset;
    uint8_t movementByteIndex;
    uint8_t field_1C;
    uint8_t field_1D;
    uint8_t field_1E;
    uint8_t field_1F;
    uint8_t range;
    uint8_t padding[7];
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
Object2
{
    uint8_t sprite;
    uint8_t mapObjectIndex;
    uint8_t spriteTile;
    uint8_t movementType;
    uint8_t flags1;
    uint8_t flags2;
    uint8_t palette;
    uint8_t walking;
    uint8_t direction;
    uint8_t stepType;
    uint8_t stepDuration;
    uint8_t action;
    uint8_t stepFrame;
    uint8_t facing;
    uint8_t standingTile;
    uint8_t lastTile;
    uint8_t standingMapX;
    uint8_t standingMapY;
    uint8_t lastMapX;
    uint8_t lastMapY;
    uint8_t initX;
    uint8_t initY;
    uint8_t radius;
    uint8_t spriteX;
    uint8_t spriteY;
    uint8_t spriteXOffset;
    uint8_t spriteYOffset;
    uint8_t movementByteIndex;
    uint8_t field_1C;
    uint8_t field_1D;
    uint8_t field_1E;
    uint8_t field_1F;
    uint8_t range;
    uint8_t padding[7];
};

// #if defined(__cplusplus) || defined(_MSC_VER)
// struct 
// #else
// struct __attribute__((packed))
// #endif
// NPCTrade
// {
//     uint8_t dialog;
//     uint8_t giveMon;
//     uint8_t getMon;
//     uint8_t nickname[MON_NAME_LENGTH];
//     uint16_t dvs;
//     uint8_t item;
//     uint16_t otId;
//     uint8_t otName[NAME_LENGTH];
//     uint16_t gender;
// };

#if defined(__cplusplus) || defined(_MSC_VER)
struct BaseMon
#else
struct __attribute__((packed)) BaseMon
#endif
{
    dex_t dexNo;
    union
    {
        uint8_t stats[6];
        struct 
        {
            uint8_t hp;
            uint8_t atk;
            uint8_t def;
            uint8_t spd;
            uint8_t sat;
            uint8_t sdf;
        };
    };
    union
    {
        uint8_t types[2];
        struct
        {
            uint8_t type_1;
            uint8_t type_2;
        };
    };
    uint8_t catchRate;
    uint8_t exp;
    union 
    {
        uint8_t items[2];
        struct
        {
            uint8_t item_1;
            uint8_t item_2;
        };
    };
    uint16_t gender;
    uint16_t eggSteps;

    uint8_t picSize;
    uint16_t frontPic;
    uint16_t backPic;

    uint8_t growthRate;
    uint8_t eggGroups;
    uint8_t TMHM[(NUM_TM_HM_TUTOR + 7) / 8];
};


#if defined(__cplusplus) || defined(_MSC_VER)
struct SpriteData
#else
struct __attribute__((packed)) SpriteData
#endif
{
    uint16_t addr;
    uint8_t size;
    uint8_t bank;
    uint8_t type;
    uint8_t palette;
};

#pragma pack(push, 1)
struct BaseData
{
    dex_t dexNo;
    union {
        uint8_t stats[6];
        struct {
            uint8_t HP;
            uint8_t attack;
            uint8_t defense;
            uint8_t speed;
            uint8_t specialAttack;
            uint8_t specialDefense;
        };
    };
    union {
        uint8_t types[2];
        struct {
            uint8_t type1;
            uint8_t type2;
        };
    };
    uint8_t catchRate;
    uint8_t exp;
    union {
        item_t items[2];
        struct {
            item_t item1;
            item_t item2;
        };
    };
    uint8_t gender;
    uint8_t unknown1;
    uint8_t eggSteps;
    uint8_t unknown2;
    uint8_t picSize;
    uint16_t unusedFrontpic;
    uint16_t unusedBackpic;
    uint8_t growthRate;
    uint8_t eggGroups;
    uint8_t TMHM[((NUM_TM_HM_TUTOR) + 7) / 8];
};
#pragma pack(pop)

struct TrainerClassAttr
{
    item_t items[2];
    uint8_t baseMoney;
    uint16_t aiMoveWeights;
    uint16_t aiItemSwitch;
};

// WRAM structs

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
BoxMon
{
    species_t species;
    item_t item;
    move_t moves[NUM_MOVES];
    uint16_t id;
    uint8_t exp[3];
    union 
    {
        uint16_t statExp[5];
        struct 
        {
            uint16_t hpExp;
            uint16_t atkExp;
            uint16_t defExp;
            uint16_t spdExp;
            uint16_t spcExp;
        };
    };
    uint16_t DVs;
    uint8_t PP[NUM_MOVES];
    uint8_t happiness;
    uint8_t pokerusStatus;
    union 
    {
        uint8_t caughtData[2];
        struct 
        {
            uint8_t caughtTimeLevel;
            uint8_t caughtGenderLocation;
        };
    };
    uint8_t level;
};
static_assert(sizeof(struct BoxMon) == BOXMON_STRUCT_LENGTH, "");

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
PartyMon
{
    struct BoxMon mon;
    uint8_t status;
    uint8_t unused;
    uint16_t HP;
    uint16_t maxHP;
    union 
    {
        uint16_t stats[5];
        struct 
        {
            uint16_t attack;
            uint16_t defense;
            uint16_t speed;
            uint16_t spclAtk;
            uint16_t spclDef;
        };
    };
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
RedBoxMon
{
    species_t species;
    uint16_t HP;
    uint8_t boxLevel;
    uint8_t status;
    union {
        uint8_t types[2];
        struct 
        {
            uint8_t type1;
            uint8_t type2;
        };
    };
    uint8_t catchRate;
    move_t moves[NUM_MOVES];
    uint16_t id;
    uint8_t exp[3];
    union 
    {
        uint16_t statExp[5];
        struct 
        {
            uint16_t hpExp;
            uint16_t atkExp;
            uint16_t defExp;
            uint16_t speExp;
            uint16_t spcExp;
        };
    };
    uint16_t dvs;
    uint8_t pp[NUM_MOVES];
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
RedPartyMon
{
    struct RedBoxMon boxmon;
    uint8_t level;
    union 
    {
        uint16_t stats[5];
        struct 
        {
            uint16_t maxHP;
            uint16_t attack;
            uint16_t defense;
            uint16_t speed;
            uint16_t spcl;
        };
    };
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
BattleMon 
{
    species_t species;
    item_t item;
    move_t moves[NUM_MOVES];
    uint16_t dvs;
    uint8_t pp[NUM_MOVES];
    uint8_t happiness;
    uint8_t level;
    uint8_t status[2];
    uint16_t hp;
    uint16_t maxHP;
    union // Big endian
    {
        uint8_t stats[5][2];
        struct 
        {
            uint8_t attack[2];
            uint8_t defense[2];
            uint8_t speed[2];
            uint8_t spclAtk[2];
            uint8_t spclDef[2];
        };
    };
    union 
    {
        uint8_t types[2];
        struct 
        {
            uint8_t type1;
            uint8_t type2;
        };
    };
};

/*
battle_struct: MACRO
\1Species::   db
\1Item::      db
\1Moves::     ds NUM_MOVES
\1DVs::       dw
\1PP::        ds NUM_MOVES
\1Happiness:: db
\1Level::     db
\1Status::    ds 2
\1HP::        dw
\1MaxHP::     dw
\1Stats:: ; big endian
\1Attack::    dw
\1Defense::   dw
\1Speed::     dw
\1SpclAtk::   dw
\1SpclDef::   dw
\1Type::
\1Type1::     db
\1Type2::     db
\1StructEnd::
ENDM
*/
#if defined(__cplusplus) || defined(_MSC_VER)
struct
#else
struct __attribute__((packed)) 
#endif
Box
{
    uint8_t count;
    species_t species[MONS_PER_BOX + 1];
    struct BoxMon mons[MONS_PER_BOX];
    uint8_t monOT[MONS_PER_BOX][NAME_LENGTH];
    uint8_t monNicknames[MONS_PER_BOX][MON_NAME_LENGTH];
};

struct MapConnection
{
    uint8_t connectedMapGroup;
    uint8_t connectedMapNumber;
    uint16_t connectionStripPointer;
    uint16_t connectionStripLocation;
    uint8_t connectionStripLength;
    uint8_t connectedMapWidth;
    uint8_t connectionStripYOffset;
    uint8_t connectionStripXOffset;
    uint16_t connectionWindow;
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct
#else
struct __attribute__((packed)) 
#endif
Channel_
{
    uint16_t musicId;
    uint8_t musicBank;
    uint8_t flags1; // 0:on/off 1:subroutine 2:looping 3:sfx 4:noise 5:rest
    uint8_t flags2; // 0:vibrato on/off 1:pitch slide 2:duty cycle pattern 4:pitch offset
    uint8_t flags3; // 0:vibrato up/down 1:pitch slide direction
    uint16_t musicAddress;
    uint16_t lastMusicAddress;
    uint16_t unused;
    uint8_t noteFlags; // 5:rest
    uint8_t condition; // conditional jumps
    uint8_t dutyCycle; // bits 6-7 (0:12.5% 1:25% 2:50% 3:75%)
    uint8_t volumeEnvelope; // hi:volume lo:fade
    uint16_t frequency; // 11 bits
    uint8_t pitch; // 0:rest 1-c:note
    uint8_t octave; // 7-0 (0 is highest)
    uint8_t transposition; // raises existing octaves (to repeat phrases)
    uint8_t noteDuration; // frames remaining for the current note
    uint8_t field16[2];
    uint8_t loopCount;
    uint16_t tempo;
    uint8_t tracks; // hi:left lo:right
    uint8_t dutyCyclePattern;
    uint8_t vibratoDelayCount; // initialized by vibratoDelay
    uint8_t vibratoDelay; // number of frames a note plays until vibrato starts
    uint8_t vibratoExtent;
    uint8_t vibratoRate; // hi:frames for each alt lo:frames to the next alt
    uint16_t pitchSlideTarget; // frequency endpoint for pitch slide
    uint8_t pitchSlideAmount;
    uint8_t pitchSlideAmountFraction;
    uint8_t field25[2];
    uint16_t pitchOffset;
    uint8_t field29;
    uint8_t field2a[2];
    uint8_t field2c;
    uint8_t noteLength; // frames per 16th note
    uint8_t field2e;
    uint8_t field2f;
    uint8_t field30[2];
};

/*

channel_struct: MACRO
\1MusicID::           dw
\1MusicBank::         db
\1Flags1::            db ; 0:on/off 1:subroutine 2:looping 3:sfx 4:noise 5:rest
\1Flags2::            db ; 0:vibrato on/off 1:pitch slide 2:duty cycle pattern 4:pitch offset
\1Flags3::            db ; 0:vibrato up/down 1:pitch slide direction
\1MusicAddress::      dw
\1LastMusicAddress::  dw
                      dw
\1NoteFlags::         db ; 5:rest
\1Condition::         db ; conditional jumps
\1DutyCycle::         db ; bits 6-7 (0:12.5% 1:25% 2:50% 3:75%)
\1VolumeEnvelope::    db ; hi:volume lo:fade
\1Frequency::         dw ; 11 bits
\1Pitch::             db ; 0:rest 1-c:note
\1Octave::            db ; 7-0 (0 is highest)
\1Transposition::     db ; raises existing octaves (to repeat phrases)
\1NoteDuration::      db ; frames remaining for the current note
\1Field16::           ds 1
                      ds 1
\1LoopCount::         db
\1Tempo::             dw
\1Tracks::            db ; hi:left lo:right
\1DutyCyclePattern::  db
\1VibratoDelayCount:: db ; initialized by \1VibratoDelay
\1VibratoDelay::      db ; number of frames a note plays until vibrato starts
\1VibratoExtent::     db
\1VibratoRate::       db ; hi:frames for each alt lo:frames to the next alt
\1PitchSlideTarget::  dw ; frequency endpoint for pitch slide
\1PitchSlideAmount::  db
\1PitchSlideAmountFraction:: db
\1Field25::           db
                      ds 1
\1PitchOffset::       dw
\1Field29::           ds 1
\1Field2a::           ds 2
\1Field2c::           ds 1
\1NoteLength::        db ; frames per 16th note
\1Field2e::           ds 1
\1Field2f::           ds 1
\1Field30::           ds 1
                      ds 1
ENDM*/

struct BattleTowerPartyMon
{
    struct PartyMon mon;
    uint8_t monName[MON_NAME_LENGTH];
};

struct BattleTowerData
{
    uint8_t name[NAME_LENGTH - 1];
    uint8_t trainerClass;
    struct BattleTowerPartyMon party[BATTLETOWER_PARTY_LENGTH];
    uint8_t trainerData[BATTLETOWER_TRAINERDATALENGTH];
};

struct BattleTowerTrainer {
    char name[11];
    uint8_t tclass;
};

/*

mailmsg: MACRO
\1Message::     ds MAIL_MSG_LENGTH
\1MessageEnd::  db
\1Author::      ds PLAYER_NAME_LENGTH
\1Nationality:: dw
\1AuthorID::    dw
\1Species::     db
\1Type::        db
\1End::
ENDM

*/
#if defined(__cplusplus) || defined(_MSC_VER)
struct
#else
struct __attribute__((packed)) 
#endif
MailMsg
{
    uint8_t message[MAIL_MSG_LENGTH + 1];
    uint8_t author[PLAYER_NAME_LENGTH];
    uint16_t nationality;
    uint16_t authorID;
    species_t species;
    uint8_t type;
};
static_assert(sizeof(struct MailMsg) == MAIL_STRUCT_LENGTH, "");

#if defined(__cplusplus) || defined(_MSC_VER)
struct
#else
struct __attribute__((packed)) 
#endif
Roamer
{
    species_t species;
    uint8_t level;
    // uint8_t mapGroup;
    // uint8_t mapNumber;
    struct MapId mapId;
    uint8_t HP;
    uint16_t DVs;
};

struct BugContestWinner
{
    uint8_t winnerID;
    species_t mon;
    uint16_t score;
};

struct HOFMon
{
    species_t species;
    uint16_t id;
    uint16_t DVs;
    uint8_t level;
    uint8_t nickname[MON_NAME_LENGTH - 1];
};

struct HallOfFameData
{
    uint8_t winCount;
    struct HOFMon mon[PARTY_LENGTH];
};

struct LinkBattleRecord {
    uint16_t id;
    uint8_t name[NAME_LENGTH - 1];
    uint16_t wins;
    uint16_t losses;
    uint16_t draws;
};
static_assert(sizeof(struct LinkBattleRecord) == LINK_BATTLE_RECORD_LENGTH, "");

#if defined(__cplusplus) || defined(_MSC_VER)
struct
#else
struct __attribute__((packed)) 
#endif
TradeMon
{
    species_t species;
    uint8_t speciesName[MON_NAME_LENGTH];
    uint8_t nickname[MON_NAME_LENGTH];
    uint8_t senderName[NAME_LENGTH];
    uint8_t otName[NAME_LENGTH];
    uint16_t dvs;
    uint16_t id;
    uint8_t caughtData;
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct
#else
struct __attribute__((packed)) 
#endif
NicknamedMon {
    struct PartyMon pmon;
    uint8_t nickname[MON_NAME_LENGTH];
};
static_assert(sizeof(struct NicknamedMon) == NICKNAMED_MON_STRUCT_LENGTH, "");

struct Move
{
    uint8_t animation;
    uint8_t effect;
    uint8_t power;
    uint8_t type;
    uint8_t accuracy;
    uint8_t pp;
    uint8_t effectChance;
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct
#else
struct __attribute__((packed)) 
#endif
SlotReel
{
    uint8_t reelAction;
    uint16_t tilemapAddr;
    uint8_t position;
    uint8_t spinDistance;
    uint8_t spinRate;
    uint16_t oamAddr;
    uint8_t xCoord;
    uint8_t manipCounter;
    uint8_t manipDelay;
    uint8_t field0b;
    uint8_t field0c;
    uint8_t field0d;
    uint8_t field0e;
    uint8_t stopDelay;
};

// Restructured Reel data using real pointers.
struct SlotReelData
{
    const uint8_t* tilemapAddr;
    struct SpriteOAM* oamAddr;
    uint8_t reelAction;
    uint8_t position;
    uint8_t spinDistance;
    uint8_t spinRate;
    uint8_t xCoord;
    uint8_t manipCounter;
    uint8_t manipDelay;
    uint8_t field0b;
    uint8_t field0c;
    uint8_t field0d;
    uint8_t field0e;
    uint8_t stopDelay;
};

/*

object_struct: MACRO
\1Sprite::            db
\1MapObjectIndex::    db
\1SpriteTile::        db
\1MovementType::      db
\1Flags::             dw
\1Palette::           db
\1Walking::           db
\1Direction::         db
\1StepType::          db
\1StepDuration::      db
\1Action::            db
\1ObjectStepFrame::   db
\1Facing::            db
\1StandingTile::      db ; collision
\1LastTile::          db ; collision
\1StandingMapX::      db
\1StandingMapY::      db
\1LastMapX::          db
\1LastMapY::          db
\1ObjectInitX::       db
\1ObjectInitY::       db
\1Radius::            db
\1SpriteX::           db
\1SpriteY::           db
\1SpriteXOffset::     db
\1SpriteYOffset::     db
\1MovementByteIndex:: db
\1Field1c::           ds 1
\1Field1d::           ds 1
\1Field1e::           ds 1
\1Field1f::           ds 1
\1Range::             db
	ds 7
\1StructEnd::
ENDM*/

struct MapObject
{
    uint8_t structId;
    uint8_t sprite;
    uint8_t objectYCoord;
    uint8_t objectXCoord;
    uint8_t objectMovement;
    uint8_t objectRadius;
    uint8_t objectHour;
    uint8_t objectTimeOfDay;
    uint8_t objectColor;
    uint8_t objectRange;
    uint16_t objectScript;
    uint16_t objectEventFlag;
    uint8_t padding[2];
};

/*

sprite_oam_struct: MACRO
\1YCoord::     db
\1XCoord::     db
\1TileID::     db
\1Attributes:: db
; bit 7: priority
; bit 6: y flip
; bit 5: x flip
; bit 4: pal # (non-cgb)
; bit 3: vram bank (cgb only)
; bit 2-0: pal # (cgb only)
ENDM

*/

struct SpriteOAM
{
    uint8_t yCoord;
    uint8_t xCoord;
    uint8_t tileID;
    union 
    {
        uint8_t attributes;
        struct 
        {
            uint8_t palNum: 3;
            uint8_t vramBank: 1;
            uint8_t palNum_NonCGB: 1;
            uint8_t xFlip: 1;
            uint8_t yFlip: 1;
            uint8_t priority: 1;
        };
    };
};


/*

sprite_anim_struct: MACRO
\1Index::          db
\1FramesetID::     db
\1AnimSeqID::      db
\1TileID::         db
\1XCoord::         db
\1YCoord::         db
\1XOffset::        db
\1YOffset::        db
\1Duration::       db
\1DurationOffset:: db
\1FrameIndex::     db
\1JumptableIndex:: db
\1Var1::           ds 1
\1Var2::           ds 1
\1Var3::           ds 1
\1Var4::           ds 1
ENDM
*/

struct SpriteAnim
{
    uint8_t index;
    uint8_t framesetID;
    uint8_t animSeqID;
    uint8_t tileID;
    uint8_t xCoord;
    uint8_t yCoord;
    uint8_t xOffset;
    uint8_t yOffset;
    uint8_t duration;
    uint8_t durationOffset;
    uint8_t frameIndex;
    uint8_t jumptableIndex;
    uint8_t var1;
    uint8_t var2;
    uint8_t var3;
    uint8_t var4;
};

/*
battle_anim_struct: MACRO
\1Index::          db
\1OAMFlags::       db
\1FixY::           db
\1FramesetID::     db
\1Function::       db
\1Palette::        db
\1TileID::         db
\1XCoord::         db
\1YCoord::         db
\1XOffset::        db
\1YOffset::        db
\1Param::          db
\1Duration::       db
\1Frame::          db
\1JumptableIndex:: db
\1Var1::           db
\1Var2::           db
	ds 7
ENDM
*//*

battle_bg_effect: MACRO
\1Function::       db
\1JumptableIndex:: db
\1BattleTurn::     db
\1Param::          db
ENDM
*/

struct BattleBGEffect
{
    uint8_t function;
    uint8_t jumptableIndex;
    uint8_t battleTurn;
    uint8_t param;
};

struct ItemPrice
{
    item_t id;
    uint16_t price;
};
typedef struct ItemPrice item_price_s;

struct ItemPal 
{
    item_t item;
    uint8_t pal;
};

struct ItemStat
{
    item_t item;
    uint8_t stat;
};

struct HealingAction
{
    item_t item;
    uint8_t action_text;
    uint8_t status;
};

struct HealingHPEntry 
{
    item_t item;
    uint16_t amount;
};

struct WildGrassMons
{
    uint8_t mapGroup;
    uint8_t mapNumber;
    uint8_t encounterRates[3];
    struct { uint8_t level; species_t species; } mons[3][7];
};

struct WildWaterMons
{
    uint8_t mapGroup;
    uint8_t mapNumber;
    uint8_t encounterRate;
    struct { uint8_t level; species_t species; } mons[3];
};

struct WildMons
{
    uint8_t type;
    union {
        const struct WildGrassMons* grassMons;
        const struct WildWaterMons* waterMons;
    };
};

struct TimeFishGroup 
{
    species_t day_mon;
    uint8_t day_lvl;
    species_t nite_mon;
    uint8_t nite_lvl;
};

struct FishEncounter 
{
    uint8_t chance;
    species_t species;
    uint8_t lvl;
};

struct FishGroup 
{
    uint8_t chance;
    const struct FishEncounter* const old_rod;
    const struct FishEncounter* const good_rod;
    const struct FishEncounter* const super_rod;
};

struct TrainerPartyNormal 
{
    uint8_t level;
    species_t species;
};

struct TrainerPartyMoves 
{
    uint8_t level;
    species_t species;
    move_t moves[4];
};

struct TrainerPartyItem 
{
    uint8_t level;
    species_t species;
    item_t item;
};

struct TrainerPartyItemMoves 
{
    uint8_t level;
    species_t species;
    item_t item;
    move_t moves[4];
};

struct TrainerParty
{
    const char* const name;
    uint8_t trainer_type;
    uint8_t size;
    union {
        const struct TrainerPartyNormal* const pnormal;
        const struct TrainerPartyMoves* const pmoves;
        const struct TrainerPartyItem* const pitem;
        const struct TrainerPartyItemMoves* const pitemmoves;
    };
};

struct TrainerGroup 
{
    const struct TrainerParty* const parties;
    size_t count;
};

struct DVSet
{
    uint8_t atk: 4;
    uint8_t def: 4;
    uint8_t spd: 4;
    uint8_t spc: 4;
};

struct BlockPointer 
{
    uint8_t tileset;
    const uint8_t* const list;
};

struct StdCollisionScript 
{
    uint8_t coll;
    uint16_t script;
};

struct BuenaMon {
    species_t options[3];
};

struct BuenaMove {
    move_t options[3];
};

struct BuenaItem {
    item_t options[3];
};

struct BuenaString {
    const char* options[3];
};

struct BuenaPassword {
    uint8_t passwordType;
    uint8_t points;
    union {
        struct BuenaMon mon;
        struct BuenaMove move;
        struct BuenaItem item;
        struct BuenaString str;
    };
};

struct BugPlaceMon {
    species_t mon;
    uint16_t score;
};

struct BugContestant {
    uint8_t tclass; 
    uint8_t tid;
    struct BugPlaceMon place[3];
};

struct SpeciesLevel {
    species_t species;
    uint8_t level;
};

struct Script;

typedef bool (*Script_fn_t)(struct Script*);

struct ScriptPosition
{
    Script_fn_t fn;
    int position;
};

struct Script
{
    Script_fn_t fn;
    size_t args[16];
    uint8_t var;
    int position;
    uint16_t stack_ptr;
    struct ScriptPosition stack[32];
};

struct BattleAnimScript;

typedef int (*battleanim_func)(struct BattleAnimScript*);

typedef struct BattleAnimScript {
    int pos;
    battleanim_func script;
    int parent_pos;
    battleanim_func parent;
} battleanim_s;

struct MapCallback {
    uint8_t type;
    const Script_fn_t script;
};

#define map_callback(type, script) {type, script}

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
WarpEventData
{
    uint8_t y;
    uint8_t x;
    uint8_t warpNumber;
    uint8_t mapGroup;
    uint8_t mapNumber;
};

#define warp_event(_x, _y, _map, _warp) {.y=_y, .x=_x, .warpNumber=_warp, .mapGroup=GROUP_##_map, .mapNumber=MAP_##_map}

struct CoordEvent
{
    uint8_t sceneId;
    uint8_t y;
    uint8_t x;
    Script_fn_t script;
};

#define coord_event(_x, _y, _sceneId, _script) {.sceneId=_sceneId, .y=_y, .x=_x, .script=_script}

struct HiddenItem 
{
    item_t item;
    uint16_t eventFlag;
};

#define hidden_item(_item, _evflag) {.item=_item, .eventFlag=_evflag}

struct ConditionalEvent 
{
    uint16_t eventFlag;
    Script_fn_t script;
};
#define conditional_event(_evflag, _script) {.eventFlag=_evflag, .script=&_script}

struct BGEvent
{
    uint8_t y;
    uint8_t x;
    uint8_t function;
    union {
        const void* const data;
        Script_fn_t script;
        const struct HiddenItem* const hiddenItem;
        const struct ConditionalEvent* const condEvent;
    };
};

#define bg_event(_x, _y, _function, _script) {.y=_y, .x=_x, .function=_function, .data=_script}

struct ItemBall {
    item_t item;
    uint8_t quantity;
};

struct TrainerObj {
    uint8_t tclass;
    uint8_t tid;
    uint16_t event_flag;
    const struct TextCmd* const seenText;
    const struct TextCmd* const winText;
    const struct TextCmd* const lossText;
    Script_fn_t script;
};

struct Stonetable {
    uint8_t warp;
    uint8_t person;
    Script_fn_t script;
};
#define stonetable(_w, _p, _s) {_w, _p, _s}

struct CmdQueue {
    uint8_t type;
    union {
        const struct Stonetable *stonetable;
    };
};
#define cmdqueue(type, table) {type, .stonetable=table}

struct ObjEvent
{
    uint8_t sprite;
    uint8_t y;
    uint8_t x;
    uint8_t movement;
    uint8_t radiusX;
    uint8_t radiusY;
    int8_t h1;
    int8_t h2;
    uint8_t color;
    uint8_t function;
    uint8_t sightRange;
    int16_t eventFlag;
    union {
        const void* data;
        Script_fn_t script;
        const struct ItemBall* item_ball;
        const struct TrainerObj* trainer;
    };
};

#define object_event(_x, _y, _sprite, _mvmt, _radiusX, _radiusY, _h1, _h2, _color, _func, _sight, _data, _evflag) {\
    .x=_x + 4, .y=_y + 4, .sprite=_sprite, .movement=_mvmt, .radiusX=_radiusX, .radiusY=_radiusY, .h1=_h1, .h2=_h2, .color=_color, .function=_func,\
    .sightRange=_sight, .eventFlag=_evflag, .data=_data}

struct MapScripts
{
    uint8_t callback_count;
    const struct MapCallback* const callbacks;

    uint8_t scene_script_count;
    const Script_fn_t* const scene_scripts;
};

struct MapEvents
{
    const uint8_t warp_event_count;
    const struct WarpEventData* warp_events;

    const uint8_t coord_event_count;
    const struct CoordEvent* coord_events;

    const uint8_t bg_event_count;
    const struct BGEvent* bg_events;

    const uint8_t obj_event_count;
    const struct ObjEvent* obj_events;
};

struct MapConnectionData
{
    uint8_t connectedMapGroup;
    uint8_t connectedMapNumber;
    uint16_t connectionStripOffset;
    uint8_t* const connectionStripLocation;
    uint8_t connectionStripLength;
    uint8_t connectedMapWidth;
    uint8_t connectionStripYOffset;
    uint8_t connectionStripXOffset;
    const uint8_t* connectionWindow;
};

struct MapAttr
{
    uint8_t borderBlock;
    uint8_t width;
    uint8_t height;
    const char* const blocksPath;
    const struct MapScripts* const scripts;
    const struct MapEvents* const events;
    const struct MapConnectionData* connections[4];
};

struct MapHeader
{
    const struct MapAttr* const attr;
    uint8_t tileset;
    uint8_t environment;
    uint8_t location;
    uint16_t music;
    uint8_t phoneService;
    uint8_t timeOfDay;
    uint8_t fishingGroup;
};

struct ElevatorFloorData 
{
    uint8_t floor;
    uint8_t warpNum;
    uint8_t mapGroup;
    uint8_t mapNum;
};
#define elevfloor(_floor, _warpNum, _map) {_floor, _warpNum, MAP_ID(_map)}

struct ElevatorData 
{
    uint8_t count;
    const struct ElevatorFloorData* floorData;
};

struct Tileset {
    const char* const gfxPath;
    const char* const metaPath;
    const uint8_t* const coll;
    const struct TileAnimFrame* const anim;
    const uint8_t* const palMap;
};

struct StartMenuItem {
    uint8_t (*function)(void);
    const char* label;
    const char* desc;
};

struct LabeledMenuItem {
    u8_flag_s (*function)(void);
    const char* label;
};

struct MenuCoords {
    uint8_t y1;
    uint8_t x1;
    uint8_t y2;
    uint8_t x2;
};

#define menu_coords(_x1, _y1, _x2, _y2) {.y1 = _y1, .x1 = _x1, .y2 = _y2, .x2 = _x2}

struct MenuHeader {
    uint8_t flags;
    struct MenuCoords coord;
    const void* data;
    uint8_t defaultOption;
};

struct MenuData {
    uint8_t flags;
    uint8_t type;
    union {
        struct {
            uint8_t count;
            const char **const options;
            struct {
                uint8_t indent;
                const char* label;
            } title;
        } verticalMenu;
        struct {
            uint8_t rows;
            uint8_t cols;
            uint8_t spacing;
            const char** const options;
        } _2dMenu;
        struct {
            union {
                uint8_t count;
                struct {
                    uint8_t rows;
                    uint8_t cols;
                };
            };
            union {
                const uint8_t** itemList;
                const uint8_t* itemArr;
            };
            void (*displayFunction)(const char**, uint8_t*, uint8_t);
            union {
                const char ** stringsList;
                const struct StartMenuItem* startMenuList;
                const struct LabeledMenuItem* labelList;
            };
        } setupMenu;
        struct {
            uint8_t flags;
            uint8_t cols;
            uint8_t rows;
            uint8_t format;
            uint8_t* list;
            void (*const func1)(const struct MenuData*, tile_t*);
            void (*const func2)(const struct MenuData*, tile_t*);
            void (*const func3)(void);
        } scrollingMenu;
    };
    void (*const function)(void);
};

struct PhoneContact {
    uint8_t trainerClass;
    uint8_t trainerId;
    uint8_t mapGroup;
    uint8_t mapNumber;
    uint8_t calleeTime;
    Script_fn_t calleeScript;
    uint8_t callerTime;
    Script_fn_t callerScript;
};

struct CallerLocation {
    uint8_t tclass;
    uint8_t tid;
    uint8_t mgroup;
    uint8_t mnum;
};

struct NPCTrade {
    uint8_t dialogSet;
    species_t requestedMon;
    species_t offeredMon;
    const char nickname[12];
    uint8_t dvs[2];
    item_t item;
    uint16_t OTID;
    const char OTName[12];
    uint8_t genderRequested;
};

struct DexEntry {
    const char* category;
    uint16_t height, weight;
    const char* description;
};

struct Pokemail {
    item_t item;
    const char* message;
};

struct MonMenuOption {
    uint8_t category;
    uint8_t item;
    move_t value;
};

struct PokemonCry 
{
    uint16_t index;
    int16_t pitch;
    uint16_t length;
};

typedef struct ItemQuantityPocketEntry {
    item_t item;
    uint8_t quantity;
} item_quantity_pocket_en_s;

typedef struct ItemPocketEntry {
    item_t item;
} item_pocket_en_s;

typedef struct ItemPocket {
    uint8_t count;
    item_pocket_en_s pocket[];
} item_pocket_s;

typedef struct ItemQuantityPocket {
    uint8_t count;
    item_quantity_pocket_en_s pocket[];
} item_quantity_pocket_s;

typedef union ItemPocketU {
    item_quantity_pocket_s quantity_pocket;
    item_pocket_s pocket;
} item_pocket_u;

struct U8Item {
    uint8_t value;
    item_t item;
};

typedef struct MobileAPIData
{
    uint8_t a;
    uint8_t l;
    uint8_t h;
    uint16_t bc;
    void* hl;
    void* de;
} mobile_api_data_s;

struct CoordsTileId
{
    int8_t x;
    int8_t y;
    uint8_t tileId;
};

struct SpriteSeqData
{
    uint8_t frameset;
    uint8_t sequence;
    uint8_t tile;
};

struct PalSet 
{
    uint8_t set;
    uint16_t colors[4];
};

struct TileAnimFrame {
    uint8_t* tile;
    void (*func)(uint8_t*);
};

struct TreeMonMap {
    uint8_t mapGroup;
    uint8_t mapNumber;
    uint8_t set;
};

struct Decoration {
    uint8_t type_id;
    uint8_t name_id;
    uint8_t action;
    uint16_t event_flag;
    uint8_t tile;
};

struct BillsPCMonEntry {
    species_t species;
    uint8_t boxNumber;
    uint8_t listIndex;
};

struct EvoData {
    uint8_t type;
    union {
        struct {
            uint8_t level;
        } lvl;
        struct {
            item_t useItem;
        } item;
        struct {
            item_t heldItem;
        } trade;
        struct {
            uint8_t timeOfDay;
        } happiness;
        struct {
            uint8_t level;
            uint8_t atkDefCmp;
        } stat;
    };
    species_t species;
};

struct LevelMove {
    uint8_t level;
    move_t move;
};

struct EvoMoves {
    const struct EvoData* evolutions;
    const struct LevelMove* learnset;
};

struct RoamMap {
    struct MapId src;
    uint8_t count;
    struct MapId* const maps;
};

typedef struct Script script_s;

#if defined(__cplusplus) || defined(_MSC_VER)
#pragma pack(pop)
#endif

struct OAMData 
{
    uint8_t vtile_offset;
    const uint8_t* ptr;
};

struct BattleOAMData 
{
    uint8_t vtile_offset;
    uint8_t data_length;
    const uint8_t* ptr;
};

struct TextPrintState
{
    uint8_t* hl;
    uint8_t* bc;
    uint8_t* de;
    uint8_t* hltemp;
};

struct TextCmdState
{
    tile_t* bc; // Tilemap cursor
    uint8_t* temp;
    const struct TextCmd* hl; // Current text command
};

// Used for some battle commands.
struct BattleCmdState 
{
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t a;
    bool carry;
};

struct EffectFunc 
{
    uint8_t effect;
    void (*func)(void);
};

struct OfferMon {
    uint8_t email[MOBILE_EMAIL_LENGTH];
    uint16_t trainerID;
    uint16_t secretID;
    uint8_t gender;
    species_t species;
    uint8_t reqGender;
    species_t reqSpecies;
    uint8_t sender[PLAYER_NAME_LENGTH - 1];
    struct PartyMon mon;
    uint8_t OT[PLAYER_NAME_LENGTH - 1];
    uint8_t Nick[MON_NAME_LENGTH - 1];
};

// Serialization structures

struct OptionsData {
    uint8_t options;
    uint8_t saveFileExists;
    // bits 0-2: textbox frame 0-7
    uint8_t textboxFrame;
    // bit 0: 1-frame text delay
    // bit 4: no text delay
    uint8_t textboxFlags;
    // bit 0-6: brightness
    //   lightest: $00
    //   lighter:  $20
    //   normal:   $40 (default)
    //   darker:   $60
    //   darkest:  $7F
    uint8_t GBPrinterBrightness;
    // bit 1: menu account off/on
    uint8_t options2;
    uint8_t unused[2];
};

struct CurMapData {
    uint8_t visitedSpawns[((NUM_SPAWNS) + 7) / 8];
    uint8_t digWarpNumber;
    uint8_t digMapGroup;
    uint8_t digMapNumber;
    // used on maps like second floor pokécenter, which are reused, so we know which
    // map to return to
    uint8_t backupWarpNumber;
    uint8_t backupMapGroup;
    uint8_t backupMapNumber;
    uint8_t unused[3];
    uint8_t lastSpawnMapGroup;
    uint8_t lastSpawnMapNumber;
    uint8_t warpNumber;
    uint8_t mapGroup;
    uint8_t mapNumber;
    uint8_t yCoord;
    uint8_t xCoord;
    uint8_t screenSave[SCREEN_META_WIDTH * SCREEN_META_HEIGHT];
};

struct PlayerData {
    uint16_t playerID;
    uint8_t playerName[NAME_LENGTH];
    uint8_t momsName[NAME_LENGTH];
    uint8_t rivalName[NAME_LENGTH];
    uint8_t redsName[NAME_LENGTH];
    uint8_t greensName[NAME_LENGTH];
    uint8_t savedAtLeastOnce;
    uint8_t spawnAfterChampion;
    // init time set at newgame
    uint8_t startDay;
    uint8_t startHour;
    uint8_t startMinute;
    uint8_t startSecond;
    uint8_t RTC[4];
    uint8_t skip_104[4];
    // bit 7: dst
    uint8_t DST;
    // used only for BANK(wGameTime)
    //union wGameTime
    uint8_t gameTimeCap;
    uint16_t gameTimeHours;
    uint8_t gameTimeMinutes;
    uint8_t gameTimeSeconds;
    uint8_t gameTimeFrames;
    uint8_t skip_105[2];
    uint8_t curDay;
    uint8_t skip_106[1];
    uint8_t objectFollow_Leader;
    uint8_t objectFollow_Follower;
    uint8_t centeredObject;
    uint8_t followerMovementQueueLength;
    uint8_t followMovementQueue[5];
    //union wObjectStructs
    struct Object playerStruct;
    // player is object struct 0
    // wObjectStruct1 - wObjectStruct12
    // for n, 1, NUM_OBJECT_STRUCTS
    struct Object objectStruct[(NUM_OBJECT_STRUCTS) - 1];
    uint8_t cmdQueue[CMDQUEUE_CAPACITY * CMDQUEUE_ENTRY_SIZE];
    uint8_t zipCode_Saved[ZIPCODE_MAX_LENGTH];
    uint8_t skip_107[40 - ZIPCODE_MAX_LENGTH];
    //union wMapObjects
    union {
        struct {
            struct MapObject playerObject;
            // player is map object 0
            // wMap1Object - wMap15Object
            // for n, 1, NUM_OBJECTS
            struct MapObject mapObject[(NUM_OBJECTS) - 1];
        };
        struct MapObject mapObjects[NUM_OBJECTS];
    };
    uint8_t objectMasks[NUM_OBJECTS];
    uint8_t variableSprites[0x100 - SPRITE_VARS];
    uint8_t enteredMapFromContinue;
    uint8_t skip_108[2];
    uint8_t timeOfDayPal;
    uint8_t skip_109[4];
    uint8_t timeOfDayPalFlags;
    uint8_t timeOfDayPalset;
    uint8_t curTimeOfDay;
    uint8_t skip_110[1];
    uint16_t secretID;
    // bit 0: pokedex
    // bit 1: unown dex
    // bit 2: flash
    // bit 3: caught pokerus
    // bit 4: rocket signal
    // bit 5: wild encounters on/off
    // bit 6: hall of fame
    // bit 7: bug contest on
    uint8_t statusFlags;
    // bit 0: rockets
    // bit 1: safari game (unused)
    // bit 2: bug contest timer
    // bit 3: unused
    // bit 4: bike shop call
    // bit 5: can use sweet scent
    // bit 6: reached goldenrod
    // bit 7: rockets in mahogany
    uint8_t statusFlags2;
    uint8_t money[3];
    uint8_t momsMoney[3];
    // bit 0: saving some money
    // bit 1: saving half money (unused)
    // bit 2: saving all money (unused)
    // bit 7: active
    uint8_t momSavingMoney;
    uint16_t coins;
    //union wBadges
    union {
        uint8_t badges[(((NUM_JOHTO_BADGES) + 7) / 8) + ((NUM_KANTO_BADGES) + 7) / 8];
        struct {
            uint8_t johtoBadges[((NUM_JOHTO_BADGES) + 7) / 8];
            uint8_t kantoBadges[((NUM_KANTO_BADGES) + 7) / 8];
        };
    };
    uint8_t TMsHMs[NUM_TMS + NUM_HMS];
    uint8_t numItems;
    item_t items[MAX_ITEMS * 2 + 1];
    uint8_t numKeyItems;
    item_t keyItems[MAX_KEY_ITEMS + 1];
    uint8_t numBalls;
    item_t balls[MAX_BALLS * 2 + 1];
    uint8_t numPCItems;
    item_t PCItems[MAX_PC_ITEMS * 2 + 1];
    // bit 0: map
    // bit 1: radio
    // bit 2: phone
    // bit 3: expn
    // bit 7: on/off
    uint8_t pokegearFlags;
    uint8_t radioTuningKnob;
    uint8_t lastDexMode;
    uint8_t skip_111[1];
    uint8_t whichRegisteredItem;
    uint8_t registeredItem;
    uint8_t playerState;
    uint8_t hallOfFameCount;
    uint8_t skip_112[1];
    uint8_t tradeFlags[((NUM_NPC_TRADES) + 7) / 8];
    uint8_t skip_113[1];
    uint8_t mooMooBerries;
    uint8_t undergroundSwitchPositions;
    uint8_t farfetchdPosition;
    uint8_t skip_114[13];
    // map scene ids
    uint8_t Pokecenter2FSceneID;
    uint8_t TradeCenterSceneID;
    uint8_t ColosseumSceneID;
    uint8_t TimeCapsuleSceneID;
    uint8_t PowerPlantSceneID;
    uint8_t CeruleanGymSceneID;
    uint8_t Route25SceneID;
    uint8_t TrainerHouseB1FSceneID;
    uint8_t VictoryRoadGateSceneID;
    uint8_t SaffronMagnetTrainStationSceneID;
    uint8_t Route16GateSceneID;
    uint8_t Route17Route18GateSceneID;
    uint8_t IndigoPlateauPokecenter1FSceneID;
    uint8_t WillsRoomSceneID;
    uint8_t KogasRoomSceneID;
    uint8_t BrunosRoomSceneID;
    uint8_t KarensRoomSceneID;
    uint8_t LancesRoomSceneID;
    uint8_t HallOfFameSceneID;
    uint8_t Route27SceneID;
    uint8_t NewBarkTownSceneID;
    uint8_t ElmsLabSceneID;
    uint8_t PlayersHouse1FSceneID;
    uint8_t Route29SceneID;
    uint8_t CherrygroveCitySceneID;
    uint8_t MrPokemonsHouseSceneID;
    uint8_t Route32SceneID;
    uint8_t Route35NationalParkGateSceneID;
    uint8_t Route36SceneID;
    uint8_t Route36NationalParkGateSceneID;
    uint8_t AzaleaTownSceneID;
    uint8_t GoldenrodGymSceneID;
    uint8_t GoldenrodMagnetTrainStationSceneID;
    uint8_t GoldenrodPokecenter1FSceneID;
    uint8_t OlivineCitySceneID;
    uint8_t Route34SceneID;
    uint8_t Route34IlexForestGateSceneID;
    uint8_t EcruteakTinTowerEntranceSceneID;
    uint8_t WiseTriosRoomSceneID;
    uint8_t EcruteakPokecenter1FSceneID;
    uint8_t EcruteakGymSceneID;
    uint8_t MahoganyTownSceneID;
    uint8_t Route42SceneID;
    uint8_t CianwoodCitySceneID;
    uint8_t BattleTower1FSceneID;
    uint8_t BattleTowerBattleRoomSceneID;
    uint8_t BattleTowerElevatorSceneID;
    uint8_t BattleTowerHallwaySceneID;
    uint8_t BattleTowerOutsideSceneID;
    uint8_t Route43GateSceneID;
    uint8_t MountMoonSceneID;
    uint8_t SproutTower3FSceneID;
    uint8_t TinTower1FSceneID;
    uint8_t BurnedTower1FSceneID;
    uint8_t BurnedTowerB1FSceneID;
    uint8_t RadioTower5FSceneID;
    uint8_t RuinsOfAlphOutsideSceneID;
    uint8_t RuinsOfAlphResearchCenterSceneID;
    uint8_t RuinsOfAlphHoOhChamberSceneID;
    uint8_t RuinsOfAlphKabutoChamberSceneID;
    uint8_t RuinsOfAlphOmanyteChamberSceneID;
    uint8_t RuinsOfAlphAerodactylChamberSceneID;
    uint8_t RuinsOfAlphInnerChamberSceneID;
    uint8_t MahoganyMart1FSceneID;
    uint8_t TeamRocketBaseB1FSceneID;
    uint8_t TeamRocketBaseB2FSceneID;
    uint8_t TeamRocketBaseB3FSceneID;
    uint8_t GoldenrodUndergroundSwitchRoomEntrancesSceneID;
    uint8_t SilverCaveRoom3SceneID;
    uint8_t VictoryRoadSceneID;
    uint8_t DragonsDenB1FSceneID;
    uint8_t DragonShrineSceneID;
    uint8_t OlivinePortSceneID;
    uint8_t VermilionPortSceneID;
    uint8_t FastShip1FSceneID;
    uint8_t FastShipB1FSceneID;
    uint8_t MountMoonSquareSceneID;
    uint8_t MobileTradeRoomSceneID;
    uint8_t MobileBattleRoomSceneID;
    uint8_t skip_115[49];
    // fight counts
    uint8_t JackFightCount;
    uint8_t BeverlyFightCount;
    // unreferenced
    uint8_t HueyFightCount;
    uint8_t GavenFightCount;
    uint8_t BethFightCount;
    uint8_t JoseFightCount;
    uint8_t ReenaFightCount;
    uint8_t JoeyFightCount;
    uint8_t WadeFightCount;
    uint8_t RalphFightCount;
    uint8_t LizFightCount;
    uint8_t AnthonyFightCount;
    uint8_t ToddFightCount;
    uint8_t GinaFightCount;
    uint8_t IrwinFightCount;
    // unreferenced
    uint8_t ArnieFightCount;
    uint8_t AlanFightCount;
    uint8_t DanaFightCount;
    uint8_t ChadFightCount;
    uint8_t DerekFightCount;
    // unreferenced
    uint8_t TullyFightCount;
    uint8_t BrentFightCount;
    uint8_t TiffanyFightCount;
    uint8_t VanceFightCount;
    uint8_t WiltonFightCount;
    uint8_t KenjiFightCount;
    // unreferenced
    uint8_t ParryFightCount;
    uint8_t ErinFightCount;
    uint8_t skip_116[100];
    uint8_t eventFlags[((NUM_EVENTS) + 7) / 8];
    uint8_t curBox;
    uint8_t skip_117[2];
    uint8_t boxNames[BOX_NAME_LENGTH * NUM_BOXES];
    // bit 2: forest is restless
    uint8_t celebiEvent;
    uint8_t skip_118[1];
    // bit 0: using strength
    // bit 1: always on bike
    // bit 2: downhill
    uint8_t bikeFlags;
    uint8_t skip_119[1];
    // cleared along with wBikeFlags by ResetBikeFlags
    uint16_t curMapSceneScriptPointer;
    uint16_t curCaller;
    uint8_t curMapWarpCount;
    uint16_t curMapWarpsPointer;
    uint8_t curMapCoordEventCount;
    uint16_t curMapCoordEventsPointer;
    uint8_t curMapBGEventCount;
    uint16_t curMapBGEventsPointer;
    uint8_t curMapObjectEventCount;
    uint16_t curMapObjectEventsPointer;
    uint8_t curMapSceneScriptCount;
    uint16_t curMapSceneScriptsPointer;
    uint8_t curMapCallbackCount;
    uint16_t curMapCallbacksPointer;
    uint8_t skip_120[2];
    // Sprite id of each decoration
    uint8_t decoBed;
    uint8_t decoCarpet;
    uint8_t decoPlant;
    uint8_t decoPoster;
    uint8_t decoConsole;
    uint8_t decoLeftOrnament;
    uint8_t decoRightOrnament;
    uint8_t decoBigDoll;
    // Items bought from Mom
    uint8_t whichMomItem;
    uint8_t whichMomItemSet;
    uint8_t momItemTriggerBalance[3];
    uint16_t dailyResetTimer;
    uint8_t dailyFlags1;
    uint8_t dailyFlags2;
    uint8_t swarmFlags;
    uint8_t skip_121[2];
    uint8_t timerEventStartDay;
    uint8_t skip_122[3];
    uint8_t fruitTreeFlags[((NUM_FRUIT_TREES) + 7) / 8];
    uint8_t skip_123[2];
    uint16_t luckyNumberDayTimer;
    uint8_t skip_124[2];
    uint16_t specialPhoneCallID;
    uint8_t skip_125[2];
    uint8_t bugContestStartTime[4];
    // day, hour, min, sec
    uint8_t unusedTwoDayTimerOn;
    uint8_t unusedTwoDayTimer;
    uint8_t unusedTwoDayTimerStartDate;
    uint8_t skip_126[4];
    uint8_t mobileOrCable_LastSelection;
    uint8_t wdc41;
    uint8_t wdc42[8];
    uint8_t buenasPassword;
    uint8_t blueCardBalance;
    uint8_t dailyRematchFlags[4];
    uint8_t dailyPhoneItemFlags[4];
    uint8_t dailyPhoneTimeOfDayFlags[4];
    uint8_t wKenjiBreakTimer[2];
    // Kenji
    uint8_t yanmaMapGroup;
    uint8_t yanmaMapNumber;
    uint8_t playerMonSelection[3];
    uint8_t wdc5f;
    uint8_t wdc60;
    uint8_t skip_127[18];
    uint8_t stepCount;
    uint8_t poisonStepCount;
    uint8_t skip_128[2];
    uint8_t happinessStepCount;
    uint8_t skip_129[1];
    union {
        uint8_t parkBallsRemaining;
        uint8_t safariBallsRemaining;
    };
    uint16_t safariTimeRemaining;
    uint8_t phoneList[CONTACT_LIST_SIZE + 1];
    uint8_t skip_130[22];
    uint8_t luckyNumberShowFlag;
    uint8_t skip_131[1];
    uint16_t luckyIDNumber;
    uint8_t repelEffect;
    // If a Repel is in use, it contains the nr of steps it's still active
    uint16_t bikeStep;
    uint8_t kurtApricornQuantity;
};

struct PokemonData {
    uint8_t partyCount;
    species_t partySpecies[PARTY_LENGTH];
    uint8_t partyEnd; // unused
    // older code doesn't check wPartyCount
    // wPartyMon1 - wPartyMon6
    //union wPartyMons
    // for n, 1, PARTY_LENGTH + 1
    // wPartyMon1 - wPartyMon6
    struct PartyMon partyMon[(PARTY_LENGTH + 1) - 1];
    // wPartyMon1OT - wPartyMon6OT
    //union wPartyMonOTs
    // for n, 1, PARTY_LENGTH + 1
    uint8_t partyMonOT[(PARTY_LENGTH + 1) - 1][NAME_LENGTH];
    // wPartyMon1Nickname - wPartyMon6Nickname
    //union wPartyMonNicknames
    // for n, 1, PARTY_LENGTH + 1
    uint8_t partyMonNickname[(PARTY_LENGTH + 1) - 1][MON_NAME_LENGTH];
    uint8_t partyMonNicknamesEnd[22];
    uint8_t pokedexCaught[((NUM_POKEMON) + 7) / 8];
    //union wEndPokedexCaught
    uint8_t pokedexSeen[((NUM_POKEMON) + 7) / 8];
    //union wEndPokedexSeen
    uint8_t unownDex[NUM_UNOWN];
    uint8_t unlockedUnowns;
    uint8_t firstUnownSeen;
    // bit 7: active
    // bit 6: egg ready
    // bit 5: monsters are compatible
    // bit 0: monster 1 in day-care
    uint8_t dayCareMan;
    uint8_t breedMon1Nickname[MON_NAME_LENGTH];
    uint8_t breedMon1OT[NAME_LENGTH];
    struct BoxMon breedMon1;
    // bit 7: active
    // bit 0: monster 2 in day-care
    uint8_t dayCareLady;
    uint8_t stepsToEgg;
    //  z: yes
    // nz: no
    uint8_t breedMotherOrNonDitto;
    uint8_t breedMon2Nickname[MON_NAME_LENGTH];
    uint8_t breedMon2OT[NAME_LENGTH];
    struct BoxMon breedMon2;
    uint8_t eggMonNickname[MON_NAME_LENGTH];
    uint8_t eggMonOT[NAME_LENGTH];
    struct BoxMon eggMon;
    uint8_t bugContestSecondPartySpecies;
    struct PartyMon contestMon;
    uint8_t dunsparceMapGroup;
    uint8_t dunsparceMapNumber;
    uint8_t fishingSwarmFlag;
    struct Roamer roamMon1;
    struct Roamer roamMon2;
    struct Roamer roamMon3;
    uint8_t roamMons_CurMapNumber;
    uint8_t roamMons_CurMapGroup;
    uint8_t roamMons_LastMapNumber;
    uint8_t roamMons_LastMapGroup;
    uint8_t bestMagikarpLengthFeet;
    uint8_t bestMagikarpLengthInches;
    uint8_t magikarpRecordHoldersName[NAME_LENGTH];
};
