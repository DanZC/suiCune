
// Utility types

union Register
{
    uint16_t reg;
    struct
    {
        uint8_t lo;
        uint8_t hi;
    };
};

typedef struct { uint8_t a; bool flag; } u8_flag_s;

#define u8_flag(_u8, _flag) (u8_flag_s){.a = _u8, .flag = _flag}

typedef struct { uint8_t a; uint8_t b; } u8_pair_s;

#define u8_pair(_a, _b) (u8_pair_s){.a = _a, .b = _b}

typedef struct { uint32_t a; bool flag; }  u32_flag_s;
#define u32_flag(_a, _flag) (u32_flag_s){.a = _a, .flag = _flag}

typedef struct { int a; bool flag; }  int_flag_s;
#define int_flag(_a, _flag) (int_flag_s){.a = _a, .flag = _flag}

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
    uint8_t monOT[NAME_LENGTH][MONS_PER_BOX];
    uint8_t monNicknames[MON_NAME_LENGTH][MONS_PER_BOX];
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
            uint8_t cols;
            uint8_t rows;
            uint8_t spacing;
            const char** const options;
        } _2dMenu;
        struct {
            union {
                uint8_t count;
                struct {
                    uint8_t cols;
                    uint8_t rows;
                };
            };
            const uint8_t** itemList;
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
            const uint8_t* list;
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

typedef struct ItemPocketEntry {
    item_t item;
    uint8_t quantity;
} item_pocket_en_s;

typedef struct ItemPocket {
    uint8_t count;
    item_pocket_en_s pocket[];
} item_pocket_s;

struct U8Item {
    uint8_t value;
    item_t item;
};

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
