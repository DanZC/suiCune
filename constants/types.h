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

struct ByteWord 
{
    uint8_t byte;
    uint16_t word;
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

// Configurable types

typedef uint8_t species_t; // Mon species type
typedef uint8_t dex_t;     // Dex number type
typedef uint8_t item_t;    // Item id type
typedef uint8_t move_t;    // Move id type

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
    uint8_t padding[8];
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
NPCTrade
{
    uint8_t dialog;
    uint8_t giveMon;
    uint8_t getMon;
    uint8_t nickname[MON_NAME_LENGTH];
    uint16_t dvs;
    uint8_t item;
    uint16_t otId;
    uint8_t otName[NAME_LENGTH];
    uint16_t gender;
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct 
#else
struct __attribute__((packed))
#endif
PhoneContact
{
    uint8_t trainerClass; // 0x0
    uint8_t trainerNumber; // 0x1
    uint8_t mapGroup; // 0x2
    uint8_t mapNumber; // 0x3
    struct
    {
        uint8_t time; // 0x0
        uint8_t bank; // 0x1
        uint16_t addr; // 0x2-0x3
    } script[2]; // 0x04-0x0B
};

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
    uint8_t connectedMapLength;
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

struct BattleTowerData
{
    uint8_t name[NAME_LENGTH - 1];
    uint8_t trainerClass;
    struct 
    {
        struct PartyMon mon;
        uint8_t monName[MON_NAME_LENGTH];
    } party[BATTLETOWER_PARTY_LENGTH];
    uint8_t trainerData[BATTLETOWER_TRAINERDATALENGTH];
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
    uint8_t message[NAME_LENGTH + 1];
    uint8_t author[PLAYER_NAME_LENGTH];
    uint16_t nationality;
    uint16_t authorID;
    species_t species;
    uint8_t type;
};

#if defined(__cplusplus) || defined(_MSC_VER)
struct
#else
struct __attribute__((packed)) 
#endif
Roamer
{
    species_t species;
    uint8_t level;
    uint8_t mapGroup;
    uint8_t mapNumber;
    uint8_t HP;
    uint16_t DVs;
};

struct BugContestWinner
{
    uint8_t winnerID;
    uint8_t mon;
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

struct LinkBattleRecord
{
    uint16_t id;
    uint8_t name[NAME_LENGTH - 1];
    uint16_t wins;
    uint16_t losses;
    uint16_t draws;
};

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

struct CustomMartItem
{
    uint8_t id;
    uint16_t price;
};

struct WildGrassMons
{
    uint8_t mapGroup;
    uint8_t mapNumber;
    uint8_t encounterRates[3];
    struct { species_t species; uint8_t level; } mons[3][7];
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

typedef struct Script script_s;

#if defined(__cplusplus) || defined(_MSC_VER)
#pragma pack(pop)
#endif
