#include "../../constants.h"

struct TrainerPartyNormal 
{
    species_t species;
    uint8_t level;
};

struct TrainerPartyMoves 
{
    species_t species;
    uint8_t level;
    move_t moves[4];
};

struct TrainerPartyItem 
{
    species_t species;
    uint8_t level;
    item_t item;
};

struct TrainerPartyItemMoves 
{
    species_t species;
    uint8_t level;
    item_t item;
    move_t moves[4];
};

struct TrainerParty
{
    const char* const name;
    uint8_t trainer_type;
    union {
        const struct TrainerPartyNormal* const pnormal;
        const struct TrainerPartyMoves* const pmoves;
        const struct TrainerPartyItem* const pitem;
        const struct TrainerPartyItemMoves* const pitemmoves;
    };
};

#define party_moves(_name, ...) {.name = _name, TRAINERTYPE_MOVES, .pmoves = (const struct TrainerPartyMoves[]){__VA_ARGS__, {0xff, 0,  {NO_MOVE, NO_MOVE, NO_MOVE, NO_MOVE}}}}
#define mon_moves(_lvl, _mon, _moves) {_lvl, _mon, _moves}
#define moves4(_move1, _move2, _move3, _move4) {_move1, _move2, _move3, _move4}
#define moves3(_move1, _move2, _move3) {_move1, _move2, _move3, NO_MOVE}
#define moves2(_move1, _move2) {_move1, _move2, NO_MOVE, NO_MOVE}
#define moves1(_move1) {_move1, NO_MOVE, NO_MOVE, NO_MOVE}
#define overloadselect4(_1,_2,_3,_4,NAME,...) NAME
#define moves(...) overloadselect4(__VA_ARGS__, moves4, moves3, moves2, moves1, error)(__VA_ARGS__)
#define party_normal(_name, ...) {.name = _name, TRAINERTYPE_NORMAL, .pnormal = (const struct TrainerPartyNormal[]){__VA_ARGS__, {0xff, 0}}}
#define mon_normal(_lvl, _mon) {_lvl, _mon}

const struct TrainerParty FalknerGroup[] = {
    party_moves("FALKNER@",
        mon_moves(7, PIDGEY,     moves(TACKLE, MUD_SLAP)),
        mon_moves(9, PIDGEOTTO,  moves(TACKLE, MUD_SLAP, GUST))
    )
};

const struct TrainerParty WhitneyGroup[] = {
    party_moves("WHITNEY@",
        mon_moves(18, CLEFAIRY,  moves(DOUBLESLAP, MIMIC, ENCORE, METRONOME)),
        mon_moves(20, MILTANK,   moves(ROLLOUT, ATTRACT, STOMP, MILK_DRINK))
    )
};

const struct TrainerParty BugsyGroup[] = {
    party_moves("BUGSY@",
        mon_moves(14, METAPOD,  moves(TACKLE, STRING_SHOT, HARDEN)),
        mon_moves(14, KAKUNA,  moves(POISON_STING, STRING_SHOT, HARDEN)),
        mon_moves(16, SCYTHER,   moves(QUICK_ATTACK, LEER, FURY_CUTTER))
    )
};

const struct TrainerParty MortyGroup[] = {
    // MORTY (1)
    party_moves("MORTY@",
        mon_moves(21, GASTLY,    moves(LICK, SPITE, MEAN_LOOK, CURSE)),
        mon_moves(21, HAUNTER,    moves(HYPNOSIS, MIMIC, CURSE, NIGHT_SHADE)),
        mon_moves(25, GENGAR,     moves(HYPNOSIS, SHADOW_BALL, MEAN_LOOK, DREAM_EATER)),
        mon_moves(23, HAUNTER,    moves(SPITE, MEAN_LOOK, MIMIC, NIGHT_SHADE))
    )
};

const struct TrainerParty PryceGroup[] = {
	// PRYCE (1)
	party_moves("PRYCE@",
        mon_moves(27, SEEL,       moves(HEADBUTT, ICY_WIND, AURORA_BEAM, REST)),
        mon_moves(29, DEWGONG,    moves(HEADBUTT, ICY_WIND, AURORA_BEAM, REST)),
        mon_moves(31, PILOSWINE,  moves(ICY_WIND, FURY_ATTACK, MIST, BLIZZARD))
	)
};

const struct TrainerParty JasmineGroup[] = {
	// JASMINE (1)
	party_moves("JASMINE@",
        mon_moves(30, MAGNEMITE,  moves(THUNDERBOLT, SUPERSONIC, SONICBOOM, THUNDER_WAVE)),
        mon_moves(30, MAGNEMITE,  moves(THUNDERBOLT, SUPERSONIC, SONICBOOM, THUNDER_WAVE)),
        mon_moves(35, STEELIX,    moves(SCREECH, SUNNY_DAY, ROCK_THROW, IRON_TAIL))
	)
};

const struct TrainerParty ChuckGroup[] = {
	// CHUCK (1)
	party_moves("CHUCK@", 
        mon_moves(27, PRIMEAPE,   moves(LEER, RAGE, KARATE_CHOP, FURY_SWIPES)),
        mon_moves(30, POLIWRATH,  moves(HYPNOSIS, MIND_READER, SURF, DYNAMICPUNCH))
    )
};

const struct TrainerParty ClairGroup[] = {
	// CLAIR (1)
	party_moves("CLAIR@", 
        mon_moves(37, DRAGONAIR,  moves(THUNDER_WAVE, SURF, SLAM, DRAGONBREATH)),
        mon_moves(37, DRAGONAIR,  moves(THUNDER_WAVE, THUNDERBOLT, SLAM, DRAGONBREATH)),
        mon_moves(37, DRAGONAIR,  moves(THUNDER_WAVE, ICE_BEAM, SLAM, DRAGONBREATH)),
        mon_moves(40, KINGDRA,    moves(SMOKESCREEN, SURF, HYPER_BEAM, DRAGONBREATH))
	)
};

const struct TrainerParty Rival1Group[] = {
    // RIVAL1 (1)
	party_normal("?@",
	    mon_normal( 5, CHIKORITA)
	),

	// RIVAL1 (2)
    party_normal("?@",
	    mon_normal( 5, CYNDAQUIL)
	),

	// RIVAL1 (3)
    party_normal("?@",
	    mon_normal( 5, TOTODILE)
	),

	// RIVAL1 (4)
    party_normal("?@",
	    mon_normal(12, GASTLY),
        mon_normal(14, ZUBAT),
        mon_normal(16, BAYLEEF)
	),

	// RIVAL1 (5)
    party_normal("?@",
	    mon_normal(12, GASTLY),
        mon_normal(14, ZUBAT),
        mon_normal(16, QUILAVA)
	),

	// RIVAL1 (6)
    party_normal("?@",
	    mon_normal(12, GASTLY),
        mon_normal(14, ZUBAT),
        mon_normal(16, CROCONAW)
	),

	// RIVAL1 (7)
    party_moves("?@",
        mon_moves(20, HAUNTER,    moves(LICK, SPITE, MEAN_LOOK, CURSE)),
        mon_moves(18, MAGNEMITE,  moves(TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM)),
        mon_moves(20, ZUBAT,      moves(LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY)),
        mon_moves(22, BAYLEEF,    moves(GROWL, REFLECT, RAZOR_LEAF, POISONPOWDER))
    ),

    // RIVAL1 (8)
    party_moves("?@",
        mon_moves(20, HAUNTER,    moves(LICK, SPITE, MEAN_LOOK, CURSE)),
        mon_moves(18, MAGNEMITE,  moves(TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM)),
        mon_moves(20, ZUBAT,      moves(LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY)),
        mon_moves(22, QUILAVA,    moves(LEER, SMOKESCREEN, EMBER, QUICK_ATTACK))
    ),

	// RIVAL1 (9)
    party_moves("?@",
        mon_moves(20, HAUNTER,    moves(LICK, SPITE, MEAN_LOOK, CURSE)),
        mon_moves(18, MAGNEMITE,  moves(TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM)),
        mon_moves(20, ZUBAT,      moves(LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY)),
        mon_moves(22, CROCONAW,   moves(LEER, RAGE, WATER_GUN, BITE))
    ),

	// RIVAL1 (10)
	party_moves("?@", 
        mon_moves(30, GOLBAT,     moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(28, MAGNEMITE,  moves(TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE)),
        mon_moves(30, HAUNTER,    moves(LICK, MEAN_LOOK, CURSE, SHADOW_BALL)),
        mon_moves(32, SNEASEL,    moves(LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK)),
        mon_moves(32, MEGANIUM,   moves(REFLECT, RAZOR_LEAF, POISONPOWDER, BODY_SLAM))
	),

	// RIVAL1 (11)
    party_moves("?@", 
        mon_moves(30, GOLBAT,     moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(28, MAGNEMITE,  moves(TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE)),
        mon_moves(30, HAUNTER,    moves(LICK, MEAN_LOOK, CURSE, SHADOW_BALL)),
        mon_moves(32, SNEASEL,    moves(LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK)),
        mon_moves(32, QUILAVA,    moves(SMOKESCREEN, EMBER, QUICK_ATTACK, FLAME_WHEEL))
	),

	// RIVAL1 (12)
    party_moves("?@", 
        mon_moves(30, GOLBAT,     moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(28, MAGNEMITE,  moves(TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE)),
        mon_moves(30, HAUNTER,    moves(LICK, MEAN_LOOK, CURSE, SHADOW_BALL)),
        mon_moves(32, SNEASEL,    moves(LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK)),
        mon_moves(32, FERALIGATR, moves(RAGE, WATER_GUN, BITE, SCARY_FACE))
	),

	// RIVAL1 (13)
	party_moves("?@", 
        mon_moves(34, SNEASEL,    moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(36, GOLBAT,     moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(35, MAGNETON,   moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(35, HAUNTER,    moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(35, KADABRA,    moves(DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT)),
        mon_moves(38, MEGANIUM,   moves(REFLECT, RAZOR_LEAF, POISONPOWDER, BODY_SLAM))
	),

	// RIVAL1 (14)
	party_moves("?@", 
        mon_moves(34, SNEASEL,    moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(36, GOLBAT,     moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(35, MAGNETON,   moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(35, HAUNTER,    moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(35, KADABRA,    moves(DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT)),
        mon_moves(38, TYPHLOSION, moves(SMOKESCREEN, EMBER, QUICK_ATTACK, FLAME_WHEEL))
	),

	// RIVAL1 (15)
	party_moves("?@", 
        mon_moves(34, SNEASEL,    moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(36, GOLBAT,     moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(35, MAGNETON,   moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(35, HAUNTER,    moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(35, KADABRA,    moves(DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT)),
        mon_moves(38, FERALIGATR, moves(RAGE, WATER_GUN, SCARY_FACE, SLASH))
	)
};

const struct TrainerParty PokemonProfGroup[] = {};

const struct TrainerParty WillGroup[] = {
    party_moves("WILL@", 
        mon_moves(40, XATU,     moves(QUICK_ATTACK, FUTURE_SIGHT, CONFUSE_RAY, PSYCHIC_M)),
        mon_moves(41, JYNX,     moves(DOUBLESLAP, LOVELY_KISS, ICE_PUNCH, PSYCHIC_M)),
        mon_moves(41, EXEGGUTOR,moves(REFLECT, LEECH_SEED, EGG_BOMB, PSYCHIC_M)),
        mon_moves(41, SLOWBRO,  moves(CURSE, AMNESIA, BODY_SLAM, PSYCHIC_M)),
        mon_moves(42, XATU,     moves(QUICK_ATTACK, FUTURE_SIGHT, CONFUSE_RAY, PSYCHIC_M))
	)
};

const struct TrainerParty PKMNTrainerGroup[] = {
    // CAL (1)
    party_normal("CAL@", 
        mon_normal(10, CHIKORITA),
        mon_normal(10, CYNDAQUIL),
        mon_normal(10, TOTODILE)
    ),
    // CAL (2)
    party_normal("CAL@", 
        mon_normal(30, BAYLEEF),
        mon_normal(30, QUILAVA),
        mon_normal(30, CROCONAW)
    ),
    // CAL (3)
    party_normal("CAL@", 
        mon_normal(50, MEGANIUM),
        mon_normal(50, TYPHLOSION),
        mon_normal(50, FERALIGATR)
    )
};

const struct TrainerParty BrunoGroup[] = {
	// BRUNO (1)
	party_moves("BRUNO@",
        mon_moves(42, HITMONTOP,  moves(PURSUIT, QUICK_ATTACK, DIG, DETECT)),
        mon_moves(42, HITMONLEE,  moves(SWAGGER, DOUBLE_KICK, HI_JUMP_KICK, FORESIGHT)),
        mon_moves(42, HITMONCHAN, moves(THUNDERPUNCH, ICE_PUNCH, FIRE_PUNCH, MACH_PUNCH)),
        mon_moves(43, ONIX,       moves(BIND, EARTHQUAKE, SANDSTORM, ROCK_SLIDE)),
        mon_moves(46, MACHAMP,    moves(ROCK_SLIDE, FORESIGHT, VITAL_THROW, CROSS_CHOP))
	)
};

const struct TrainerParty* TrainerGroups[] = {
    FalknerGroup,
    WhitneyGroup,
    BugsyGroup,
    MortyGroup,
    PryceGroup,
    JasmineGroup,
    ChuckGroup,
    ClairGroup,
    Rival1Group,
    PokemonProfGroup,
    WillGroup,
    PKMNTrainerGroup,
    BrunoGroup,
};
