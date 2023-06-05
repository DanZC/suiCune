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


// ROM structs

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
    union
    {
        uint16_t price;
        struct {
            uint8_t priceLo;
            uint8_t priceHi;
        };
    };
    uint8_t effect;
    uint8_t param;
    uint8_t permissions;
    uint8_t pocket;
    uint8_t help;
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

struct Object
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

struct NPCTrade
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

struct PhoneContact
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

struct BaseMon
{
    uint8_t dexNo;
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


struct SpriteData
{
    uint16_t addr;
    uint8_t size;
    uint8_t bank;
    uint8_t type;
    uint8_t palette;
};

struct TrainerClassAttr
{
    uint8_t items[2];
    uint8_t baseMoney;
    uint16_t aiMoveWeights;
    uint16_t aiItemSwitch;
};

// WRAM structs

struct BoxMon
{
    uint8_t species;
    uint8_t item;
    uint8_t moves[NUM_MOVES];
    uint16_t id;
    uint8_t exp;
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

struct PartyMon
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

/*

red_box_struct: MACRO
\1Species::    db
\1HP::         dw
\1BoxLevel::   db
\1Status::     db
\1Type::
\1Type1::      db
\1Type2::      db
\1CatchRate::  db
\1Moves::      ds NUM_MOVES
\1ID::         dw
\1Exp::        ds 3
\1HPExp::      dw
\1AttackExp::  dw
\1DefenseExp:: dw
\1SpeedExp::   dw
\1SpecialExp:: dw
\1DVs::        dw
\1PP::         ds NUM_MOVES
ENDM

red_party_struct: MACRO
	red_box_struct \1
\1Level::      db
\1Stats::
\1MaxHP::      dw
\1Attack::     dw
\1Defense::    dw
\1Speed::      dw
\1Special::    dw
ENDM

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

struct Box
{
    uint8_t count;
    uint8_t species[MONS_PER_BOX + 1];
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

struct MailMsg
{
    uint8_t message[NAME_LENGTH + 1];
    uint8_t author[PLAYER_NAME_LENGTH];
    uint16_t nationality;
    uint16_t authorID;
    uint8_t species;
    uint8_t type;
};

struct Roamer
{
    uint8_t species;
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
    uint8_t species;
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

struct TradeMon
{
    uint8_t species;
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

struct SlotReel
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