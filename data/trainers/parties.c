#include "../../constants.h"

#define party_moves(_name, ...) {.name = _name, TRAINERTYPE_MOVES, .size = sizeof((const struct TrainerPartyMoves[]){__VA_ARGS__}) / sizeof(struct TrainerPartyMoves), .pmoves = (const struct TrainerPartyMoves[]){__VA_ARGS__}}
#define mon_moves(_lvl, _mon, _moves) {.level=_lvl, .species=_mon, _moves}
#define moves4(_move1, _move2, _move3, _move4) {_move1, _move2, _move3, _move4}
#define moves3(_move1, _move2, _move3) {_move1, _move2, _move3, NO_MOVE}
#define moves2(_move1, _move2) {_move1, _move2, NO_MOVE, NO_MOVE}
#define moves1(_move1) {_move1, NO_MOVE, NO_MOVE, NO_MOVE}
#define overloadselect4(_1,_2,_3,_4,NAME,...) NAME
#define moves(...) overloadselect4(__VA_ARGS__, moves4, moves3, moves2, moves1, error)(__VA_ARGS__)
#define party_normal(_name, ...) {.name = _name, TRAINERTYPE_NORMAL, .size = sizeof((const struct TrainerPartyNormal[]){__VA_ARGS__}) / sizeof(struct TrainerPartyNormal), .pnormal = (const struct TrainerPartyNormal[]){__VA_ARGS__}}
#define mon_normal(_lvl, _mon) {.level=_lvl, .species=_mon}
#define party_item(_name, ...) {.name = _name, TRAINERTYPE_ITEM, .size = sizeof((const struct TrainerPartyItem[]){__VA_ARGS__}) / sizeof(struct TrainerPartyItem), .pitem = (const struct TrainerPartyItem[]){__VA_ARGS__}}
#define mon_item(_lvl, _mon, _item) {_lvl, _mon, _item}
#define party_item_moves(_name, ...) {.name = _name, TRAINERTYPE_ITEM_MOVES, .size = sizeof((const struct TrainerPartyItemMoves[]){__VA_ARGS__}) / sizeof(struct TrainerPartyItemMoves), .pitemmoves = (const struct TrainerPartyItemMoves[]){__VA_ARGS__}}
#define mon_item_moves(_lvl, _mon, _item, _moves) {_lvl, _mon, _item, _moves}
const struct TrainerParty FalknerGroup[] = {
    party_moves("FALKNER@",
        mon_moves(7, PIDGEY, moves(TACKLE, MUD_SLAP, NO_MOVE, NO_MOVE)),
        mon_moves(9, PIDGEOTTO, moves(TACKLE, MUD_SLAP, GUST, NO_MOVE))
    ),
};

const struct TrainerParty WhitneyGroup[] = {
    party_moves("WHITNEY@",
        mon_moves(18, CLEFAIRY, moves(DOUBLESLAP, MIMIC, ENCORE, METRONOME)),
        mon_moves(20, MILTANK, moves(ROLLOUT, ATTRACT, STOMP, MILK_DRINK))
    ),
};

const struct TrainerParty BugsyGroup[] = {
    party_moves("BUGSY@",
        mon_moves(14, METAPOD, moves(TACKLE, STRING_SHOT, HARDEN, NO_MOVE)),
        mon_moves(14, KAKUNA, moves(POISON_STING, STRING_SHOT, HARDEN, NO_MOVE)),
        mon_moves(16, SCYTHER, moves(QUICK_ATTACK, LEER, FURY_CUTTER, NO_MOVE))
    ),
};

const struct TrainerParty MortyGroup[] = {
    party_moves("MORTY@",
        mon_moves(21, GASTLY, moves(LICK, SPITE, MEAN_LOOK, CURSE)),
        mon_moves(21, HAUNTER, moves(HYPNOSIS, MIMIC, CURSE, NIGHT_SHADE)),
        mon_moves(25, GENGAR, moves(HYPNOSIS, SHADOW_BALL, MEAN_LOOK, DREAM_EATER)),
        mon_moves(23, HAUNTER, moves(SPITE, MEAN_LOOK, MIMIC, NIGHT_SHADE))
    ),
};

const struct TrainerParty PryceGroup[] = {
    party_moves("PRYCE@",
        mon_moves(27, SEEL, moves(HEADBUTT, ICY_WIND, AURORA_BEAM, REST)),
        mon_moves(29, DEWGONG, moves(HEADBUTT, ICY_WIND, AURORA_BEAM, REST)),
        mon_moves(31, PILOSWINE, moves(ICY_WIND, FURY_ATTACK, MIST, BLIZZARD))
    ),
};

const struct TrainerParty JasmineGroup[] = {
    party_moves("JASMINE@",
        mon_moves(30, MAGNEMITE, moves(THUNDERBOLT, SUPERSONIC, SONICBOOM, THUNDER_WAVE)),
        mon_moves(30, MAGNEMITE, moves(THUNDERBOLT, SUPERSONIC, SONICBOOM, THUNDER_WAVE)),
        mon_moves(35, STEELIX, moves(SCREECH, SUNNY_DAY, ROCK_THROW, IRON_TAIL))
    ),
};

const struct TrainerParty ChuckGroup[] = {
    party_moves("CHUCK@",
        mon_moves(27, PRIMEAPE, moves(LEER, RAGE, KARATE_CHOP, FURY_SWIPES)),
        mon_moves(30, POLIWRATH, moves(HYPNOSIS, MIND_READER, SURF, DYNAMICPUNCH))
    ),
};

const struct TrainerParty ClairGroup[] = {
    party_moves("CLAIR@",
        mon_moves(37, DRAGONAIR, moves(THUNDER_WAVE, SURF, SLAM, DRAGONBREATH)),
        mon_moves(37, DRAGONAIR, moves(THUNDER_WAVE, THUNDERBOLT, SLAM, DRAGONBREATH)),
        mon_moves(37, DRAGONAIR, moves(THUNDER_WAVE, ICE_BEAM, SLAM, DRAGONBREATH)),
        mon_moves(40, KINGDRA, moves(SMOKESCREEN, SURF, HYPER_BEAM, DRAGONBREATH))
    ),
};

const struct TrainerParty Rival1Group[] = {
    party_normal("?@",
        mon_normal(5, CHIKORITA)
    ),
    party_normal("?@",
        mon_normal(5, CYNDAQUIL)
    ),
    party_normal("?@",
        mon_normal(5, TOTODILE)
    ),
    party_normal("?@",
        mon_normal(12, GASTLY),
        mon_normal(14, ZUBAT),
        mon_normal(16, BAYLEEF)
    ),
    party_normal("?@",
        mon_normal(12, GASTLY),
        mon_normal(14, ZUBAT),
        mon_normal(16, QUILAVA)
    ),
    party_normal("?@",
        mon_normal(12, GASTLY),
        mon_normal(14, ZUBAT),
        mon_normal(16, CROCONAW)
    ),
    party_moves("?@",
        mon_moves(20, HAUNTER, moves(LICK, SPITE, MEAN_LOOK, CURSE)),
        mon_moves(18, MAGNEMITE, moves(TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM)),
        mon_moves(20, ZUBAT, moves(LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY)),
        mon_moves(22, BAYLEEF, moves(GROWL, REFLECT, RAZOR_LEAF, POISONPOWDER))
    ),
    party_moves("?@",
        mon_moves(20, HAUNTER, moves(LICK, SPITE, MEAN_LOOK, CURSE)),
        mon_moves(18, MAGNEMITE, moves(TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM)),
        mon_moves(20, ZUBAT, moves(LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY)),
        mon_moves(22, QUILAVA, moves(LEER, SMOKESCREEN, EMBER, QUICK_ATTACK))
    ),
    party_moves("?@",
        mon_moves(20, HAUNTER, moves(LICK, SPITE, MEAN_LOOK, CURSE)),
        mon_moves(18, MAGNEMITE, moves(TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM)),
        mon_moves(20, ZUBAT, moves(LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY)),
        mon_moves(22, CROCONAW, moves(LEER, RAGE, WATER_GUN, BITE))
    ),
    party_moves("?@",
        mon_moves(30, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(28, MAGNEMITE, moves(TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE)),
        mon_moves(30, HAUNTER, moves(LICK, MEAN_LOOK, CURSE, SHADOW_BALL)),
        mon_moves(32, SNEASEL, moves(LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK)),
        mon_moves(32, MEGANIUM, moves(REFLECT, RAZOR_LEAF, POISONPOWDER, BODY_SLAM))
    ),
    party_moves("?@",
        mon_moves(30, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(28, MAGNEMITE, moves(TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE)),
        mon_moves(30, HAUNTER, moves(LICK, MEAN_LOOK, CURSE, SHADOW_BALL)),
        mon_moves(32, SNEASEL, moves(LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK)),
        mon_moves(32, QUILAVA, moves(SMOKESCREEN, EMBER, QUICK_ATTACK, FLAME_WHEEL))
    ),
    party_moves("?@",
        mon_moves(30, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(28, MAGNEMITE, moves(TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE)),
        mon_moves(30, HAUNTER, moves(LICK, MEAN_LOOK, CURSE, SHADOW_BALL)),
        mon_moves(32, SNEASEL, moves(LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK)),
        mon_moves(32, FERALIGATR, moves(RAGE, WATER_GUN, BITE, SCARY_FACE))
    ),
    party_moves("?@",
        mon_moves(34, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(36, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(35, MAGNETON, moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(35, HAUNTER, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(35, KADABRA, moves(DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT)),
        mon_moves(38, MEGANIUM, moves(REFLECT, RAZOR_LEAF, POISONPOWDER, BODY_SLAM))
    ),
    party_moves("?@",
        mon_moves(34, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(36, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(35, MAGNETON, moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(35, HAUNTER, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(35, KADABRA, moves(DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT)),
        mon_moves(38, TYPHLOSION, moves(SMOKESCREEN, EMBER, QUICK_ATTACK, FLAME_WHEEL))
    ),
    party_moves("?@",
        mon_moves(34, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(36, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(34, MAGNETON, moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(35, HAUNTER, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(35, KADABRA, moves(DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT)),
        mon_moves(38, FERALIGATR, moves(RAGE, WATER_GUN, SCARY_FACE, SLASH))
    ),
};

const struct TrainerParty PokemonProfGroup[] = {};

const struct TrainerParty WillGroup[] = {
    party_moves("WILL@",
        mon_moves(40, XATU, moves(QUICK_ATTACK, FUTURE_SIGHT, CONFUSE_RAY, PSYCHIC_M)),
        mon_moves(41, JYNX, moves(DOUBLESLAP, LOVELY_KISS, ICE_PUNCH, PSYCHIC_M)),
        mon_moves(41, EXEGGUTOR, moves(REFLECT, LEECH_SEED, EGG_BOMB, PSYCHIC_M)),
        mon_moves(41, SLOWBRO, moves(CURSE, AMNESIA, BODY_SLAM, PSYCHIC_M)),
        mon_moves(42, XATU, moves(QUICK_ATTACK, FUTURE_SIGHT, CONFUSE_RAY, PSYCHIC_M))
    ),
};

const struct TrainerParty PKMNTrainerGroup[] = {
    party_normal("CAL@",
        mon_normal(10, CHIKORITA),
        mon_normal(10, CYNDAQUIL),
        mon_normal(10, TOTODILE)
    ),
    party_normal("CAL@",
        mon_normal(30, BAYLEEF),
        mon_normal(30, QUILAVA),
        mon_normal(30, CROCONAW)
    ),
    party_normal("CAL@",
        mon_normal(50, MEGANIUM),
        mon_normal(50, TYPHLOSION),
        mon_normal(50, FERALIGATR)
    ),
};

const struct TrainerParty BrunoGroup[] = {
    party_moves("BRUNO@",
        mon_moves(42, HITMONTOP, moves(PURSUIT, QUICK_ATTACK, DIG, DETECT)),
        mon_moves(42, HITMONLEE, moves(SWAGGER, DOUBLE_KICK, HI_JUMP_KICK, FORESIGHT)),
        mon_moves(42, HITMONCHAN, moves(THUNDERPUNCH, ICE_PUNCH, FIRE_PUNCH, MACH_PUNCH)),
        mon_moves(43, ONIX, moves(BIND, EARTHQUAKE, SANDSTORM, ROCK_SLIDE)),
        mon_moves(46, MACHAMP, moves(ROCK_SLIDE, FORESIGHT, VITAL_THROW, CROSS_CHOP))
    ),
};

const struct TrainerParty KarenGroup[] = {
    party_moves("KAREN@",
        mon_moves(42, UMBREON, moves(SAND_ATTACK, CONFUSE_RAY, FAINT_ATTACK, MEAN_LOOK)),
        mon_moves(42, VILEPLUME, moves(STUN_SPORE, ACID, MOONLIGHT, PETAL_DANCE)),
        mon_moves(45, GENGAR, moves(LICK, SPITE, CURSE, DESTINY_BOND)),
        mon_moves(44, MURKROW, moves(QUICK_ATTACK, WHIRLWIND, PURSUIT, FAINT_ATTACK)),
        mon_moves(47, HOUNDOOM, moves(ROAR, PURSUIT, FLAMETHROWER, CRUNCH))
    ),
};

const struct TrainerParty KogaGroup[] = {
    party_moves("KOGA@",
        mon_moves(40, ARIADOS, moves(DOUBLE_TEAM, SPIDER_WEB, BATON_PASS, GIGA_DRAIN)),
        mon_moves(41, VENOMOTH, moves(SUPERSONIC, GUST, PSYCHIC_M, TOXIC)),
        mon_moves(43, FORRETRESS, moves(PROTECT, SWIFT, EXPLOSION, SPIKES)),
        mon_moves(42, MUK, moves(MINIMIZE, ACID_ARMOR, SLUDGE_BOMB, TOXIC)),
        mon_moves(44, CROBAT, moves(DOUBLE_TEAM, QUICK_ATTACK, WING_ATTACK, TOXIC))
    ),
};

const struct TrainerParty ChampionGroup[] = {
    party_moves("LANCE@",
        mon_moves(44, GYARADOS, moves(FLAIL, RAIN_DANCE, SURF, HYPER_BEAM)),
        mon_moves(47, DRAGONITE, moves(THUNDER_WAVE, TWISTER, THUNDER, HYPER_BEAM)),
        mon_moves(47, DRAGONITE, moves(THUNDER_WAVE, TWISTER, BLIZZARD, HYPER_BEAM)),
        mon_moves(46, AERODACTYL, moves(WING_ATTACK, ANCIENTPOWER, ROCK_SLIDE, HYPER_BEAM)),
        mon_moves(46, CHARIZARD, moves(FLAMETHROWER, WING_ATTACK, SLASH, HYPER_BEAM)),
        mon_moves(50, DRAGONITE, moves(FIRE_BLAST, SAFEGUARD, OUTRAGE, HYPER_BEAM))
    ),
};

const struct TrainerParty BrockGroup[] = {
    party_moves("BROCK@",
        mon_moves(41, GRAVELER, moves(DEFENSE_CURL, ROCK_SLIDE, ROLLOUT, EARTHQUAKE)),
        mon_moves(41, RHYHORN, moves(FURY_ATTACK, SCARY_FACE, EARTHQUAKE, HORN_DRILL)),
        mon_moves(42, OMASTAR, moves(BITE, SURF, PROTECT, SPIKE_CANNON)),
        mon_moves(44, ONIX, moves(BIND, ROCK_SLIDE, BIDE, SANDSTORM)),
        mon_moves(42, KABUTOPS, moves(SLASH, SURF, ENDURE, GIGA_DRAIN))
    ),
};

const struct TrainerParty MistyGroup[] = {
    party_moves("MISTY@",
        mon_moves(42, GOLDUCK, moves(SURF, DISABLE, PSYCH_UP, PSYCHIC_M)),
        mon_moves(42, QUAGSIRE, moves(SURF, AMNESIA, EARTHQUAKE, RAIN_DANCE)),
        mon_moves(44, LAPRAS, moves(SURF, PERISH_SONG, BLIZZARD, RAIN_DANCE)),
        mon_moves(47, STARMIE, moves(SURF, CONFUSE_RAY, RECOVER, ICE_BEAM))
    ),
};

const struct TrainerParty LtSurgeGroup[] = {
    party_moves("LT.SURGE@",
        mon_moves(44, RAICHU, moves(THUNDER_WAVE, QUICK_ATTACK, THUNDERBOLT, THUNDER)),
        mon_moves(40, ELECTRODE, moves(SCREECH, DOUBLE_TEAM, SWIFT, EXPLOSION)),
        mon_moves(40, MAGNETON, moves(LOCK_ON, DOUBLE_TEAM, SWIFT, ZAP_CANNON)),
        mon_moves(40, ELECTRODE, moves(SCREECH, DOUBLE_TEAM, SWIFT, EXPLOSION)),
        mon_moves(46, ELECTABUZZ, moves(QUICK_ATTACK, THUNDERPUNCH, LIGHT_SCREEN, THUNDER))
    ),
};

const struct TrainerParty ScientistGroup[] = {
    party_normal("ROSS@",
        mon_normal(22, KOFFING),
        mon_normal(22, KOFFING)
    ),
    party_normal("MITCH@",
        mon_normal(24, DITTO)
    ),
    party_normal("JED@",
        mon_normal(20, MAGNEMITE),
        mon_normal(20, MAGNEMITE),
        mon_normal(20, MAGNEMITE)
    ),
    party_normal("MARC@",
        mon_normal(27, MAGNEMITE),
        mon_normal(27, MAGNEMITE),
        mon_normal(27, MAGNEMITE)
    ),
    party_moves("RICH@",
        mon_moves(30, PORYGON, moves(CONVERSION, CONVERSION2, RECOVER, TRI_ATTACK))
    ),
};

const struct TrainerParty ErikaGroup[] = {
    party_moves("ERIKA@",
        mon_moves(42, TANGELA, moves(VINE_WHIP, BIND, GIGA_DRAIN, SLEEP_POWDER)),
        mon_moves(41, JUMPLUFF, moves(MEGA_DRAIN, LEECH_SEED, COTTON_SPORE, GIGA_DRAIN)),
        mon_moves(46, VICTREEBEL, moves(SUNNY_DAY, SYNTHESIS, ACID, RAZOR_LEAF)),
        mon_moves(46, BELLOSSOM, moves(SUNNY_DAY, SYNTHESIS, PETAL_DANCE, SOLARBEAM))
    ),
};

const struct TrainerParty YoungsterGroup[] = {
    party_normal("JOEY@",
        mon_normal(4, RATTATA)
    ),
    party_normal("MIKEY@",
        mon_normal(2, PIDGEY),
        mon_normal(4, RATTATA)
    ),
    party_normal("ALBERT@",
        mon_normal(6, RATTATA),
        mon_normal(8, ZUBAT)
    ),
    party_normal("GORDON@",
        mon_normal(10, WOOPER)
    ),
    party_normal("SAMUEL@",
        mon_normal(7, RATTATA),
        mon_normal(10, SANDSHREW),
        mon_normal(8, SPEAROW),
        mon_normal(8, SPEAROW)
    ),
    party_normal("IAN@",
        mon_normal(10, MANKEY),
        mon_normal(12, DIGLETT)
    ),
    party_normal("JOEY@",
        mon_normal(15, RATTATA)
    ),
    party_moves("JOEY@",
        mon_moves(21, RATICATE, moves(TAIL_WHIP, QUICK_ATTACK, HYPER_FANG, SCARY_FACE))
    ),
    party_normal("WARREN@",
        mon_normal(35, FEAROW)
    ),
    party_normal("JIMMY@",
        mon_normal(33, RATICATE),
        mon_normal(33, ARBOK)
    ),
    party_normal("OWEN@",
        mon_normal(35, GROWLITHE)
    ),
    party_normal("JASON@",
        mon_normal(33, SANDSLASH),
        mon_normal(33, CROBAT)
    ),
    party_moves("JOEY@",
        mon_moves(30, RATICATE, moves(TAIL_WHIP, QUICK_ATTACK, HYPER_FANG, PURSUIT))
    ),
    party_moves("JOEY@",
        mon_moves(37, RATICATE, moves(HYPER_BEAM, QUICK_ATTACK, HYPER_FANG, PURSUIT))
    ),
};

const struct TrainerParty SchoolboyGroup[] = {
    party_normal("JACK@",
        mon_normal(12, ODDISH),
        mon_normal(15, VOLTORB)
    ),
    party_normal("KIPP@",
        mon_normal(27, VOLTORB),
        mon_normal(27, MAGNEMITE),
        mon_normal(31, VOLTORB),
        mon_normal(31, MAGNETON)
    ),
    party_normal("ALAN@",
        mon_normal(16, TANGELA)
    ),
    party_normal("JOHNNY@",
        mon_normal(29, BELLSPROUT),
        mon_normal(31, WEEPINBELL),
        mon_normal(33, VICTREEBEL)
    ),
    party_normal("DANNY@",
        mon_normal(31, JYNX),
        mon_normal(31, ELECTABUZZ),
        mon_normal(31, MAGMAR)
    ),
    party_normal("TOMMY@",
        mon_normal(32, XATU),
        mon_normal(34, ALAKAZAM)
    ),
    party_normal("DUDLEY@",
        mon_normal(35, ODDISH)
    ),
    party_normal("JOE@",
        mon_normal(33, TANGELA),
        mon_normal(33, VAPOREON)
    ),
    party_normal("BILLY@",
        mon_normal(27, PARAS),
        mon_normal(27, PARAS),
        mon_normal(27, POLIWHIRL),
        mon_normal(35, DITTO)
    ),
    party_normal("CHAD@",
        mon_normal(19, MR__MIME)
    ),
    party_normal("NATE@",
        mon_normal(32, LEDIAN),
        mon_normal(32, EXEGGUTOR)
    ),
    party_normal("RICKY@",
        mon_normal(32, AIPOM),
        mon_normal(32, DITTO)
    ),
    party_normal("JACK@",
        mon_normal(14, ODDISH),
        mon_normal(17, VOLTORB)
    ),
    party_normal("JACK@",
        mon_normal(28, GLOOM),
        mon_normal(31, ELECTRODE)
    ),
    party_normal("ALAN@",
        mon_normal(17, TANGELA),
        mon_normal(17, YANMA)
    ),
    party_normal("ALAN@",
        mon_normal(20, NATU),
        mon_normal(22, TANGELA),
        mon_normal(20, QUAGSIRE),
        mon_normal(25, YANMA)
    ),
    party_normal("CHAD@",
        mon_normal(19, MR__MIME),
        mon_normal(19, MAGNEMITE)
    ),
    party_normal("CHAD@",
        mon_normal(27, MR__MIME),
        mon_normal(31, MAGNETON)
    ),
    party_normal("JACK@",
        mon_normal(30, GLOOM),
        mon_normal(33, GROWLITHE),
        mon_normal(33, ELECTRODE)
    ),
    party_moves("JACK@",
        mon_moves(35, ELECTRODE, moves(SCREECH, SONICBOOM, ROLLOUT, LIGHT_SCREEN)),
        mon_moves(35, GROWLITHE, moves(SUNNY_DAY, LEER, TAKE_DOWN, FLAME_WHEEL)),
        mon_moves(37, VILEPLUME, moves(SOLARBEAM, SLEEP_POWDER, ACID, MOONLIGHT))
    ),
    party_normal("ALAN@",
        mon_normal(27, NATU),
        mon_normal(27, TANGELA),
        mon_normal(30, QUAGSIRE),
        mon_normal(30, YANMA)
    ),
    party_moves("ALAN@",
        mon_moves(35, XATU, moves(PECK, NIGHT_SHADE, SWIFT, FUTURE_SIGHT)),
        mon_moves(32, TANGELA, moves(POISONPOWDER, VINE_WHIP, BIND, MEGA_DRAIN)),
        mon_moves(32, YANMA, moves(QUICK_ATTACK, DOUBLE_TEAM, SONICBOOM, SUPERSONIC)),
        mon_moves(35, QUAGSIRE, moves(TAIL_WHIP, SLAM, AMNESIA, EARTHQUAKE))
    ),
    party_normal("CHAD@",
        mon_normal(30, MR__MIME),
        mon_normal(34, MAGNETON)
    ),
    party_moves("CHAD@",
        mon_moves(34, MR__MIME, moves(PSYCHIC_M, LIGHT_SCREEN, REFLECT, ENCORE)),
        mon_moves(38, MAGNETON, moves(ZAP_CANNON, THUNDER_WAVE, LOCK_ON, SWIFT))
    ),
};

const struct TrainerParty BirdKeeperGroup[] = {
    party_normal("ROD@",
        mon_normal(7, PIDGEY),
        mon_normal(7, PIDGEY)
    ),
    party_normal("ABE@",
        mon_normal(9, SPEAROW)
    ),
    party_normal("BRYAN@",
        mon_normal(12, PIDGEY),
        mon_normal(14, PIDGEOTTO)
    ),
    party_normal("THEO@",
        mon_normal(17, PIDGEY),
        mon_normal(15, PIDGEY),
        mon_normal(19, PIDGEY),
        mon_normal(15, PIDGEY),
        mon_normal(15, PIDGEY)
    ),
    party_normal("TOBY@",
        mon_normal(15, DODUO),
        mon_normal(16, DODUO),
        mon_normal(17, DODUO)
    ),
    party_normal("DENIS@",
        mon_normal(18, SPEAROW),
        mon_normal(20, FEAROW),
        mon_normal(18, SPEAROW)
    ),
    party_normal("VANCE@",
        mon_normal(25, PIDGEOTTO),
        mon_normal(25, PIDGEOTTO)
    ),
    party_normal("HANK@",
        mon_normal(12, PIDGEY),
        mon_normal(34, PIDGEOT)
    ),
    party_normal("ROY@",
        mon_normal(29, FEAROW),
        mon_normal(35, FEAROW)
    ),
    party_normal("BORIS@",
        mon_normal(30, DODUO),
        mon_normal(28, DODUO),
        mon_normal(32, DODRIO)
    ),
    party_normal("BOB@",
        mon_normal(34, NOCTOWL)
    ),
    party_normal("JOSE@",
        mon_normal(36, FARFETCH_D)
    ),
    party_normal("PETER@",
        mon_normal(6, PIDGEY),
        mon_normal(6, PIDGEY),
        mon_normal(8, SPEAROW)
    ),
    party_normal("JOSE@",
        mon_normal(34, FARFETCH_D)
    ),
    party_normal("PERRY@",
        mon_normal(34, FARFETCH_D)
    ),
    party_normal("BRET@",
        mon_normal(32, PIDGEOTTO),
        mon_normal(32, FEAROW)
    ),
    party_moves("JOSE@",
        mon_moves(40, FARFETCH_D, moves(FURY_ATTACK, DETECT, FLY, SLASH))
    ),
    party_normal("VANCE@",
        mon_normal(32, PIDGEOTTO),
        mon_normal(32, PIDGEOTTO)
    ),
    party_moves("VANCE@",
        mon_moves(38, PIDGEOT, moves(TOXIC, QUICK_ATTACK, WHIRLWIND, FLY)),
        mon_moves(38, PIDGEOT, moves(SWIFT, DETECT, STEEL_WING, FLY))
    ),
};

const struct TrainerParty LassGroup[] = {
    party_moves("CARRIE@",
        mon_moves(18, SNUBBULL, moves(SCARY_FACE, CHARM, BITE, LICK))
    ),
    party_normal("BRIDGET@",
        mon_normal(15, JIGGLYPUFF),
        mon_normal(15, JIGGLYPUFF),
        mon_normal(15, JIGGLYPUFF)
    ),
    party_normal("ALICE@",
        mon_normal(30, GLOOM),
        mon_normal(34, ARBOK),
        mon_normal(30, GLOOM)
    ),
    party_normal("KRISE@",
        mon_normal(12, ODDISH),
        mon_normal(15, CUBONE)
    ),
    party_normal("CONNIE@",
        mon_normal(21, MARILL)
    ),
    party_normal("LINDA@",
        mon_normal(30, BULBASAUR),
        mon_normal(32, IVYSAUR),
        mon_normal(34, VENUSAUR)
    ),
    party_normal("LAURA@",
        mon_normal(28, GLOOM),
        mon_normal(31, PIDGEOTTO),
        mon_normal(31, BELLOSSOM)
    ),
    party_normal("SHANNON@",
        mon_normal(29, PARAS),
        mon_normal(29, PARAS),
        mon_normal(32, PARASECT)
    ),
    party_normal("MICHELLE@",
        mon_normal(32, SKIPLOOM),
        mon_normal(33, HOPPIP),
        mon_normal(34, JUMPLUFF)
    ),
    party_moves("DANA@",
        mon_moves(18, FLAAFFY, moves(TACKLE, GROWL, THUNDERSHOCK, THUNDER_WAVE)),
        mon_moves(18, PSYDUCK, moves(SCRATCH, TAIL_WHIP, DISABLE, CONFUSION))
    ),
    party_normal("ELLEN@",
        mon_normal(30, WIGGLYTUFF),
        mon_normal(34, GRANBULL)
    ),
    party_normal("CONNIE@",
        mon_normal(21, MARILL)
    ),
    party_normal("CONNIE@",
        mon_normal(21, MARILL)
    ),
    party_moves("DANA@",
        mon_moves(21, FLAAFFY, moves(TACKLE, GROWL, THUNDERSHOCK, THUNDER_WAVE)),
        mon_moves(21, PSYDUCK, moves(SCRATCH, TAIL_WHIP, DISABLE, CONFUSION))
    ),
    party_moves("DANA@",
        mon_moves(29, PSYDUCK, moves(SCRATCH, DISABLE, CONFUSION, SCREECH)),
        mon_moves(29, AMPHAROS, moves(TACKLE, THUNDERSHOCK, THUNDER_WAVE, COTTON_SPORE))
    ),
    party_moves("DANA@",
        mon_moves(32, PSYDUCK, moves(SCRATCH, DISABLE, CONFUSION, SCREECH)),
        mon_moves(32, AMPHAROS, moves(TACKLE, THUNDERPUNCH, THUNDER_WAVE, COTTON_SPORE))
    ),
    party_moves("DANA@",
        mon_moves(36, AMPHAROS, moves(SWIFT, THUNDERPUNCH, THUNDER_WAVE, COTTON_SPORE)),
        mon_moves(36, GOLDUCK, moves(DISABLE, SURF, PSYCHIC_M, SCREECH))
    ),
};

const struct TrainerParty JanineGroup[] = {
    party_moves("JANINE@",
        mon_moves(36, CROBAT, moves(SCREECH, SUPERSONIC, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(36, WEEZING, moves(SMOG, SLUDGE_BOMB, TOXIC, EXPLOSION)),
        mon_moves(36, WEEZING, moves(SMOG, SLUDGE_BOMB, TOXIC, EXPLOSION)),
        mon_moves(33, ARIADOS, moves(SCARY_FACE, GIGA_DRAIN, STRING_SHOT, NIGHT_SHADE)),
        mon_moves(39, VENOMOTH, moves(FORESIGHT, DOUBLE_TEAM, GUST, PSYCHIC_M))
    ),
};

const struct TrainerParty CooltrainerMGroup[] = {
    party_moves("NICK@",
        mon_moves(26, CHARMANDER, moves(EMBER, SMOKESCREEN, RAGE, SCARY_FACE)),
        mon_moves(26, SQUIRTLE, moves(WITHDRAW, WATER_GUN, BITE, CURSE)),
        mon_moves(26, BULBASAUR, moves(LEECH_SEED, POISONPOWDER, SLEEP_POWDER, RAZOR_LEAF))
    ),
    party_normal("AARON@",
        mon_normal(24, IVYSAUR),
        mon_normal(24, CHARMELEON),
        mon_normal(24, WARTORTLE)
    ),
    party_normal("PAUL@",
        mon_normal(34, DRATINI),
        mon_normal(34, DRATINI),
        mon_normal(34, DRATINI)
    ),
    party_normal("CODY@",
        mon_normal(34, HORSEA),
        mon_normal(36, SEADRA)
    ),
    party_normal("MIKE@",
        mon_normal(37, DRAGONAIR)
    ),
    party_moves("GAVEN@",
        mon_moves(35, VICTREEBEL, moves(WRAP, TOXIC, ACID, RAZOR_LEAF)),
        mon_moves(35, KINGLER, moves(BUBBLEBEAM, STOMP, GUILLOTINE, PROTECT)),
        mon_moves(35, FLAREON, moves(SAND_ATTACK, QUICK_ATTACK, BITE, FIRE_SPIN))
    ),
    party_item_moves("GAVEN@",
        mon_item_moves(39, VICTREEBEL, NO_ITEM, moves(GIGA_DRAIN, TOXIC, SLUDGE_BOMB, RAZOR_LEAF)),
        mon_item_moves(39, KINGLER, KINGS_ROCK, moves(SURF, STOMP, GUILLOTINE, BLIZZARD)),
        mon_item_moves(39, FLAREON, NO_ITEM, moves(FLAMETHROWER, QUICK_ATTACK, BITE, FIRE_SPIN))
    ),
    party_moves("RYAN@",
        mon_moves(25, PIDGEOT, moves(SAND_ATTACK, QUICK_ATTACK, WHIRLWIND, WING_ATTACK)),
        mon_moves(27, ELECTABUZZ, moves(THUNDERPUNCH, LIGHT_SCREEN, SWIFT, SCREECH))
    ),
    party_moves("JAKE@",
        mon_moves(33, PARASECT, moves(LEECH_LIFE, SPORE, SLASH, SWORDS_DANCE)),
        mon_moves(35, GOLDUCK, moves(CONFUSION, SCREECH, PSYCH_UP, FURY_SWIPES))
    ),
    party_moves("GAVEN@",
        mon_moves(32, VICTREEBEL, moves(WRAP, TOXIC, ACID, RAZOR_LEAF)),
        mon_moves(32, KINGLER, moves(BUBBLEBEAM, STOMP, GUILLOTINE, PROTECT)),
        mon_moves(32, FLAREON, moves(SAND_ATTACK, QUICK_ATTACK, BITE, FIRE_SPIN))
    ),
    party_moves("BLAKE@",
        mon_moves(33, MAGNETON, moves(THUNDERBOLT, SUPERSONIC, SWIFT, SCREECH)),
        mon_moves(31, QUAGSIRE, moves(WATER_GUN, SLAM, AMNESIA, EARTHQUAKE)),
        mon_moves(31, EXEGGCUTE, moves(LEECH_SEED, CONFUSION, SLEEP_POWDER, SOLARBEAM))
    ),
    party_moves("BRIAN@",
        mon_moves(35, SANDSLASH, moves(SAND_ATTACK, POISON_STING, SLASH, SWIFT))
    ),
    party_normal("ERICK@",
        mon_normal(10, BULBASAUR),
        mon_normal(10, CHARMANDER),
        mon_normal(10, SQUIRTLE)
    ),
    party_normal("ANDY@",
        mon_normal(10, BULBASAUR),
        mon_normal(10, CHARMANDER),
        mon_normal(10, SQUIRTLE)
    ),
    party_normal("TYLER@",
        mon_normal(10, BULBASAUR),
        mon_normal(10, CHARMANDER),
        mon_normal(10, SQUIRTLE)
    ),
    party_normal("SEAN@",
        mon_normal(35, FLAREON),
        mon_normal(35, TANGELA),
        mon_normal(35, TAUROS)
    ),
    party_normal("KEVIN@",
        mon_normal(38, RHYHORN),
        mon_normal(35, CHARMELEON),
        mon_normal(35, WARTORTLE)
    ),
    party_normal("STEVE@",
        mon_normal(14, BULBASAUR),
        mon_normal(14, CHARMANDER),
        mon_normal(14, SQUIRTLE)
    ),
    party_moves("ALLEN@",
        mon_moves(27, CHARMELEON, moves(EMBER, SMOKESCREEN, RAGE, SCARY_FACE))
    ),
    party_moves("DARIN@",
        mon_moves(37, DRAGONAIR, moves(WRAP, SURF, DRAGON_RAGE, SLAM))
    ),
};

const struct TrainerParty CooltrainerFGroup[] = {
    party_normal("GWEN@",
        mon_normal(26, EEVEE),
        mon_normal(22, FLAREON),
        mon_normal(22, VAPOREON),
        mon_normal(22, JOLTEON)
    ),
    party_moves("LOIS@",
        mon_moves(25, SKIPLOOM, moves(SYNTHESIS, POISONPOWDER, MEGA_DRAIN, LEECH_SEED)),
        mon_moves(25, NINETALES, moves(EMBER, QUICK_ATTACK, CONFUSE_RAY, SAFEGUARD))
    ),
    party_normal("FRAN@",
        mon_normal(37, SEADRA)
    ),
    party_normal("LOLA@",
        mon_normal(34, DRATINI),
        mon_normal(36, DRAGONAIR)
    ),
    party_normal("KATE@",
        mon_normal(26, SHELLDER),
        mon_normal(28, CLOYSTER)
    ),
    party_normal("IRENE@",
        mon_normal(22, GOLDEEN),
        mon_normal(24, SEAKING)
    ),
    party_normal("KELLY@",
        mon_normal(27, MARILL),
        mon_normal(24, WARTORTLE),
        mon_normal(24, WARTORTLE)
    ),
    party_moves("JOYCE@",
        mon_moves(36, PIKACHU, moves(QUICK_ATTACK, DOUBLE_TEAM, THUNDERBOLT, THUNDER)),
        mon_moves(32, BLASTOISE, moves(BITE, CURSE, SURF, RAIN_DANCE))
    ),
    party_moves("BETH@",
        mon_moves(36, RAPIDASH, moves(STOMP, FIRE_SPIN, FURY_ATTACK, AGILITY))
    ),
    party_normal("REENA@",
        mon_normal(31, STARMIE),
        mon_normal(33, NIDOQUEEN),
        mon_normal(31, STARMIE)
    ),
    party_moves("MEGAN@",
        mon_moves(32, BULBASAUR, moves(GROWL, LEECH_SEED, POISONPOWDER, RAZOR_LEAF)),
        mon_moves(32, IVYSAUR, moves(GROWL, LEECH_SEED, POISONPOWDER, RAZOR_LEAF)),
        mon_moves(32, VENUSAUR, moves(BODY_SLAM, SLEEP_POWDER, RAZOR_LEAF, SWEET_SCENT))
    ),
    party_moves("BETH@",
        mon_moves(39, RAPIDASH, moves(STOMP, FIRE_SPIN, FURY_ATTACK, AGILITY))
    ),
    party_normal("CAROL@",
        mon_normal(35, ELECTRODE),
        mon_normal(35, STARMIE),
        mon_normal(35, NINETALES)
    ),
    party_normal("QUINN@",
        mon_normal(38, IVYSAUR),
        mon_normal(38, STARMIE)
    ),
    party_normal("EMMA@",
        mon_normal(28, POLIWHIRL)
    ),
    party_moves("CYBIL@",
        mon_moves(25, BUTTERFREE, moves(CONFUSION, SLEEP_POWDER, WHIRLWIND, GUST)),
        mon_moves(25, BELLOSSOM, moves(ABSORB, STUN_SPORE, ACID, SOLARBEAM))
    ),
    party_normal("JENN@",
        mon_normal(24, STARYU),
        mon_normal(26, STARMIE)
    ),
    party_item_moves("BETH@",
        mon_item_moves(43, RAPIDASH, FOCUS_BAND, moves(STOMP, FIRE_SPIN, FURY_ATTACK, FIRE_BLAST))
    ),
    party_normal("REENA@",
        mon_normal(34, STARMIE),
        mon_normal(36, NIDOQUEEN),
        mon_normal(34, STARMIE)
    ),
    party_item_moves("REENA@",
        mon_item_moves(38, STARMIE, NO_ITEM, moves(DOUBLE_TEAM, PSYCHIC_M, WATERFALL, CONFUSE_RAY)),
        mon_item_moves(40, NIDOQUEEN, PINK_BOW, moves(EARTHQUAKE, DOUBLE_KICK, TOXIC, BODY_SLAM)),
        mon_item_moves(38, STARMIE, NO_ITEM, moves(BLIZZARD, PSYCHIC_M, WATERFALL, RECOVER))
    ),
    party_moves("CARA@",
        mon_moves(33, HORSEA, moves(SMOKESCREEN, LEER, WHIRLPOOL, TWISTER)),
        mon_moves(33, HORSEA, moves(SMOKESCREEN, LEER, WHIRLPOOL, TWISTER)),
        mon_moves(35, SEADRA, moves(SWIFT, LEER, WATERFALL, TWISTER))
    ),
};

const struct TrainerParty BeautyGroup[] = {
    party_normal("VICTORIA@",
        mon_normal(9, SENTRET),
        mon_normal(13, SENTRET),
        mon_normal(17, SENTRET)
    ),
    party_moves("SAMANTHA@",
        mon_moves(16, MEOWTH, moves(SCRATCH, GROWL, BITE, PAY_DAY)),
        mon_moves(16, MEOWTH, moves(SCRATCH, GROWL, BITE, SLASH))
    ),
    party_normal("JULIE@",
        mon_normal(15, SENTRET)
    ),
    party_normal("JACLYN@",
        mon_normal(15, SENTRET)
    ),
    party_normal("BRENDA@",
        mon_normal(16, FURRET)
    ),
    party_normal("CASSIE@",
        mon_normal(28, VILEPLUME),
        mon_normal(34, BUTTERFREE)
    ),
    party_normal("CAROLINE@",
        mon_normal(30, MARILL),
        mon_normal(32, SEEL),
        mon_normal(30, MARILL)
    ),
    party_normal("CARLENE@",
        mon_normal(15, SENTRET)
    ),
    party_normal("JESSICA@",
        mon_normal(15, SENTRET)
    ),
    party_normal("RACHAEL@",
        mon_normal(15, SENTRET)
    ),
    party_normal("ANGELICA@",
        mon_normal(15, SENTRET)
    ),
    party_normal("KENDRA@",
        mon_normal(15, SENTRET)
    ),
    party_normal("VERONICA@",
        mon_normal(15, SENTRET)
    ),
    party_normal("JULIA@",
        mon_normal(32, PARAS),
        mon_normal(32, EXEGGCUTE),
        mon_normal(35, PARASECT)
    ),
    party_normal("THERESA@",
        mon_normal(15, SENTRET)
    ),
    party_moves("VALERIE@",
        mon_moves(17, HOPPIP, moves(SYNTHESIS, TAIL_WHIP, TACKLE, POISONPOWDER)),
        mon_moves(17, SKIPLOOM, moves(SYNTHESIS, TAIL_WHIP, TACKLE, STUN_SPORE))
    ),
    party_normal("OLIVIA@",
        mon_normal(19, CORSOLA)
    ),
};

const struct TrainerParty PokemaniacGroup[] = {
    party_normal("LARRY@",
        mon_normal(10, SLOWPOKE)
    ),
    party_normal("ANDREW@",
        mon_normal(24, MAROWAK),
        mon_normal(24, MAROWAK)
    ),
    party_normal("CALVIN@",
        mon_normal(26, KANGASKHAN)
    ),
    party_normal("SHANE@",
        mon_normal(16, NIDORINA),
        mon_normal(16, NIDORINO)
    ),
    party_normal("BEN@",
        mon_normal(19, SLOWBRO)
    ),
    party_normal("BRENT@",
        mon_normal(19, LICKITUNG)
    ),
    party_normal("RON@",
        mon_normal(19, NIDOKING)
    ),
    party_normal("ETHAN@",
        mon_normal(31, RHYHORN),
        mon_normal(31, RHYDON)
    ),
    party_normal("BRENT@",
        mon_normal(25, KANGASKHAN)
    ),
    party_moves("BRENT@",
        mon_moves(36, PORYGON, moves(RECOVER, PSYCHIC_M, CONVERSION2, TRI_ATTACK))
    ),
    party_moves("ISSAC@",
        mon_moves(12, LICKITUNG, moves(LICK, SUPERSONIC, CUT, NO_MOVE))
    ),
    party_normal("DONALD@",
        mon_normal(10, SLOWPOKE),
        mon_normal(10, SLOWPOKE)
    ),
    party_normal("ZACH@",
        mon_normal(27, RHYHORN)
    ),
    party_moves("BRENT@",
        mon_moves(41, CHANSEY, moves(ROLLOUT, ATTRACT, EGG_BOMB, SOFTBOILED))
    ),
    party_normal("MILLER@",
        mon_normal(17, NIDOKING),
        mon_normal(17, NIDOQUEEN)
    ),
};

const struct TrainerParty GruntMGroup[] = {
    party_normal("GRUNT@",
        mon_normal(14, KOFFING)
    ),
    party_normal("GRUNT@",
        mon_normal(7, RATTATA),
        mon_normal(9, ZUBAT),
        mon_normal(9, ZUBAT)
    ),
    party_normal("GRUNT@",
        mon_normal(24, RATICATE),
        mon_normal(24, RATICATE)
    ),
    party_normal("GRUNT@",
        mon_normal(23, GRIMER),
        mon_normal(23, GRIMER),
        mon_normal(25, MUK)
    ),
    party_normal("GRUNT@",
        mon_normal(21, RATTATA),
        mon_normal(21, RATTATA),
        mon_normal(23, RATTATA),
        mon_normal(23, RATTATA),
        mon_normal(23, RATTATA)
    ),
    party_normal("GRUNT@",
        mon_normal(26, ZUBAT),
        mon_normal(26, ZUBAT)
    ),
    party_normal("GRUNT@",
        mon_normal(23, KOFFING),
        mon_normal(23, GRIMER),
        mon_normal(23, ZUBAT),
        mon_normal(23, RATTATA)
    ),
    party_normal("GRUNT@",
        mon_normal(26, WEEZING)
    ),
    party_normal("GRUNT@",
        mon_normal(24, RATICATE),
        mon_normal(26, KOFFING)
    ),
    party_normal("GRUNT@",
        mon_normal(22, ZUBAT),
        mon_normal(24, GOLBAT),
        mon_normal(22, GRIMER)
    ),
    party_normal("GRUNT@",
        mon_normal(23, MUK),
        mon_normal(23, KOFFING),
        mon_normal(25, RATTATA)
    ),
    party_normal("EXECUTIVE@",
        mon_normal(33, HOUNDOUR)
    ),
    party_normal("GRUNT@",
        mon_normal(27, RATTATA)
    ),
    party_normal("GRUNT@",
        mon_normal(24, RATICATE),
        mon_normal(24, GOLBAT)
    ),
    party_normal("GRUNT@",
        mon_normal(26, GRIMER),
        mon_normal(23, WEEZING)
    ),
    party_normal("GRUNT@",
        mon_normal(16, RATTATA),
        mon_normal(16, RATTATA),
        mon_normal(16, RATTATA),
        mon_normal(16, RATTATA)
    ),
    party_normal("GRUNT@",
        mon_normal(18, GOLBAT)
    ),
    party_normal("GRUNT@",
        mon_normal(17, RATTATA),
        mon_normal(17, ZUBAT),
        mon_normal(17, RATTATA)
    ),
    party_normal("GRUNT@",
        mon_normal(18, VENONAT),
        mon_normal(18, VENONAT)
    ),
    party_normal("GRUNT@",
        mon_normal(17, DROWZEE),
        mon_normal(19, ZUBAT)
    ),
    party_normal("GRUNT@",
        mon_normal(16, ZUBAT),
        mon_normal(17, GRIMER),
        mon_normal(18, RATTATA)
    ),
    party_normal("EXECUTIVE@",
        mon_normal(36, GOLBAT)
    ),
    party_normal("EXECUTIVE@",
        mon_normal(30, KOFFING)
    ),
    party_normal("GRUNT@",
        mon_normal(25, KOFFING),
        mon_normal(25, KOFFING)
    ),
    party_normal("GRUNT@",
        mon_normal(24, KOFFING),
        mon_normal(24, MUK)
    ),
    party_normal("GRUNT@",
        mon_normal(15, RATTATA),
        mon_normal(15, RATTATA)
    ),
    party_normal("EXECUTIVE@",
        mon_normal(22, ZUBAT)
    ),
    party_normal("GRUNT@",
        mon_normal(19, RATICATE)
    ),
    party_normal("GRUNT@",
        mon_normal(9, RATTATA),
        mon_normal(9, RATTATA)
    ),
    party_normal("GRUNT@",
        mon_normal(25, GOLBAT),
        mon_normal(25, GOLBAT),
        mon_normal(30, ARBOK)
    ),
    party_normal("GRUNT@",
        mon_normal(30, GOLBAT)
    ),
};

const struct TrainerParty GentlemanGroup[] = {
    party_normal("PRESTON@",
        mon_normal(18, GROWLITHE),
        mon_normal(18, GROWLITHE)
    ),
    party_normal("EDWARD@",
        mon_normal(33, PERSIAN)
    ),
    party_normal("GREGORY@",
        mon_normal(37, PIKACHU),
        mon_normal(33, FLAAFFY)
    ),
    party_normal("VIRGIL@",
        mon_normal(20, PONYTA)
    ),
    party_normal("ALFRED@",
        mon_normal(20, NOCTOWL)
    ),
};

const struct TrainerParty SkierGroup[] = {
    party_normal("ROXANNE@",
        mon_normal(28, JYNX)
    ),
    party_normal("CLARISSA@",
        mon_normal(28, DEWGONG)
    ),
};

const struct TrainerParty TeacherGroup[] = {
    party_normal("COLETTE@",
        mon_normal(36, CLEFAIRY)
    ),
    party_normal("HILLARY@",
        mon_normal(32, AIPOM),
        mon_normal(36, CUBONE)
    ),
    party_normal("SHIRLEY@",
        mon_normal(35, JIGGLYPUFF)
    ),
};

const struct TrainerParty SabrinaGroup[] = {
    party_moves("SABRINA@",
        mon_moves(46, ESPEON, moves(SAND_ATTACK, QUICK_ATTACK, SWIFT, PSYCHIC_M)),
        mon_moves(46, MR__MIME, moves(BARRIER, REFLECT, BATON_PASS, PSYCHIC_M)),
        mon_moves(48, ALAKAZAM, moves(RECOVER, FUTURE_SIGHT, PSYCHIC_M, REFLECT))
    ),
};

const struct TrainerParty BugCatcherGroup[] = {
    party_normal("DON@",
        mon_normal(3, CATERPIE),
        mon_normal(3, CATERPIE)
    ),
    party_normal("ROB@",
        mon_normal(32, BEEDRILL),
        mon_normal(32, BUTTERFREE)
    ),
    party_normal("ED@",
        mon_normal(30, BEEDRILL),
        mon_normal(30, BEEDRILL),
        mon_normal(30, BEEDRILL)
    ),
    party_normal("WADE@",
        mon_normal(2, CATERPIE),
        mon_normal(2, CATERPIE),
        mon_normal(3, WEEDLE),
        mon_normal(2, CATERPIE)
    ),
    party_normal("BENNY@",
        mon_normal(7, WEEDLE),
        mon_normal(9, KAKUNA),
        mon_normal(12, BEEDRILL)
    ),
    party_normal("AL@",
        mon_normal(12, CATERPIE),
        mon_normal(12, WEEDLE)
    ),
    party_normal("JOSH@",
        mon_normal(13, PARAS)
    ),
    party_normal("ARNIE@",
        mon_normal(15, VENONAT)
    ),
    party_normal("KEN@",
        mon_normal(30, ARIADOS),
        mon_normal(32, PINSIR)
    ),
    party_normal("WADE@",
        mon_normal(9, METAPOD),
        mon_normal(9, METAPOD),
        mon_normal(10, KAKUNA),
        mon_normal(9, METAPOD)
    ),
    party_normal("WADE@",
        mon_normal(14, BUTTERFREE),
        mon_normal(14, BUTTERFREE),
        mon_normal(15, BEEDRILL),
        mon_normal(14, BUTTERFREE)
    ),
    party_normal("DOUG@",
        mon_normal(34, ARIADOS)
    ),
    party_normal("ARNIE@",
        mon_normal(19, VENONAT)
    ),
    party_moves("ARNIE@",
        mon_moves(28, VENOMOTH, moves(DISABLE, SUPERSONIC, CONFUSION, LEECH_LIFE))
    ),
    party_moves("WADE@",
        mon_moves(24, BUTTERFREE, moves(CONFUSION, POISONPOWDER, SUPERSONIC, WHIRLWIND)),
        mon_moves(24, BUTTERFREE, moves(CONFUSION, STUN_SPORE, SUPERSONIC, WHIRLWIND)),
        mon_moves(25, BEEDRILL, moves(FURY_ATTACK, FOCUS_ENERGY, TWINEEDLE, RAGE)),
        mon_moves(24, BUTTERFREE, moves(CONFUSION, SLEEP_POWDER, SUPERSONIC, WHIRLWIND))
    ),
    party_moves("WADE@",
        mon_moves(30, BUTTERFREE, moves(CONFUSION, POISONPOWDER, SUPERSONIC, GUST)),
        mon_moves(30, BUTTERFREE, moves(CONFUSION, STUN_SPORE, SUPERSONIC, GUST)),
        mon_moves(32, BEEDRILL, moves(FURY_ATTACK, PURSUIT, TWINEEDLE, DOUBLE_TEAM)),
        mon_moves(34, BUTTERFREE, moves(PSYBEAM, SLEEP_POWDER, GUST, WHIRLWIND))
    ),
    party_moves("ARNIE@",
        mon_moves(36, VENOMOTH, moves(GUST, SUPERSONIC, PSYBEAM, LEECH_LIFE))
    ),
    party_moves("ARNIE@",
        mon_moves(40, VENOMOTH, moves(GUST, SUPERSONIC, PSYCHIC_M, TOXIC))
    ),
    party_normal("WAYNE@",
        mon_normal(8, LEDYBA),
        mon_normal(10, PARAS)
    ),
};

const struct TrainerParty FisherGroup[] = {
    party_normal("JUSTIN@",
        mon_normal(5, MAGIKARP),
        mon_normal(5, MAGIKARP),
        mon_normal(15, MAGIKARP),
        mon_normal(5, MAGIKARP)
    ),
    party_normal("RALPH@",
        mon_normal(10, GOLDEEN)
    ),
    party_normal("ARNOLD@",
        mon_normal(34, TENTACRUEL)
    ),
    party_normal("KYLE@",
        mon_normal(28, SEAKING),
        mon_normal(31, POLIWHIRL),
        mon_normal(31, SEAKING)
    ),
    party_normal("HENRY@",
        mon_normal(8, POLIWAG),
        mon_normal(8, POLIWAG)
    ),
    party_normal("MARVIN@",
        mon_normal(10, MAGIKARP),
        mon_normal(10, GYARADOS),
        mon_normal(15, MAGIKARP),
        mon_normal(15, GYARADOS)
    ),
    party_normal("TULLY@",
        mon_normal(18, QWILFISH)
    ),
    party_normal("ANDRE@",
        mon_normal(27, GYARADOS)
    ),
    party_normal("RAYMOND@",
        mon_normal(22, MAGIKARP),
        mon_normal(22, MAGIKARP),
        mon_normal(22, MAGIKARP),
        mon_normal(22, MAGIKARP)
    ),
    party_normal("WILTON@",
        mon_normal(23, GOLDEEN),
        mon_normal(23, GOLDEEN),
        mon_normal(25, SEAKING)
    ),
    party_moves("EDGAR@",
        mon_moves(25, REMORAID, moves(LOCK_ON, PSYBEAM, AURORA_BEAM, BUBBLEBEAM)),
        mon_moves(25, REMORAID, moves(LOCK_ON, PSYBEAM, AURORA_BEAM, BUBBLEBEAM))
    ),
    party_normal("JONAH@",
        mon_normal(25, SHELLDER),
        mon_normal(29, OCTILLERY),
        mon_normal(25, REMORAID),
        mon_normal(29, CLOYSTER)
    ),
    party_normal("MARTIN@",
        mon_normal(32, REMORAID),
        mon_normal(32, REMORAID)
    ),
    party_normal("STEPHEN@",
        mon_normal(25, MAGIKARP),
        mon_normal(25, MAGIKARP),
        mon_normal(31, QWILFISH),
        mon_normal(31, TENTACRUEL)
    ),
    party_normal("BARNEY@",
        mon_normal(30, GYARADOS),
        mon_normal(30, GYARADOS),
        mon_normal(30, GYARADOS)
    ),
    party_normal("RALPH@",
        mon_normal(17, GOLDEEN)
    ),
    party_normal("RALPH@",
        mon_normal(17, QWILFISH),
        mon_normal(19, GOLDEEN)
    ),
    party_normal("TULLY@",
        mon_normal(23, QWILFISH)
    ),
    party_normal("TULLY@",
        mon_normal(32, GOLDEEN),
        mon_normal(32, GOLDEEN),
        mon_normal(32, QWILFISH)
    ),
    party_normal("WILTON@",
        mon_normal(29, GOLDEEN),
        mon_normal(29, GOLDEEN),
        mon_normal(32, SEAKING)
    ),
    party_normal("SCOTT@",
        mon_normal(30, QWILFISH),
        mon_normal(30, QWILFISH),
        mon_normal(34, SEAKING)
    ),
    party_moves("WILTON@",
        mon_moves(34, SEAKING, moves(SUPERSONIC, WATERFALL, FLAIL, FURY_ATTACK)),
        mon_moves(34, SEAKING, moves(SUPERSONIC, WATERFALL, FLAIL, FURY_ATTACK)),
        mon_moves(38, REMORAID, moves(PSYBEAM, AURORA_BEAM, BUBBLEBEAM, HYPER_BEAM))
    ),
    party_normal("RALPH@",
        mon_normal(30, QWILFISH),
        mon_normal(32, GOLDEEN)
    ),
    party_moves("RALPH@",
        mon_moves(35, QWILFISH, moves(TOXIC, MINIMIZE, SURF, PIN_MISSILE)),
        mon_moves(39, SEAKING, moves(ENDURE, FLAIL, FURY_ATTACK, WATERFALL))
    ),
    party_moves("TULLY@",
        mon_moves(34, SEAKING, moves(SUPERSONIC, RAIN_DANCE, WATERFALL, FURY_ATTACK)),
        mon_moves(34, SEAKING, moves(SUPERSONIC, RAIN_DANCE, WATERFALL, FURY_ATTACK)),
        mon_moves(37, QWILFISH, moves(ROLLOUT, SURF, PIN_MISSILE, TAKE_DOWN))
    ),
};

const struct TrainerParty SwimmerMGroup[] = {
    party_normal("HAROLD@",
        mon_normal(32, REMORAID),
        mon_normal(30, SEADRA)
    ),
    party_normal("SIMON@",
        mon_normal(20, TENTACOOL),
        mon_normal(20, TENTACOOL)
    ),
    party_normal("RANDALL@",
        mon_normal(18, SHELLDER),
        mon_normal(20, WARTORTLE),
        mon_normal(18, SHELLDER)
    ),
    party_normal("CHARLIE@",
        mon_normal(21, SHELLDER),
        mon_normal(19, TENTACOOL),
        mon_normal(19, TENTACRUEL)
    ),
    party_normal("GEORGE@",
        mon_normal(16, TENTACOOL),
        mon_normal(17, TENTACOOL),
        mon_normal(16, TENTACOOL),
        mon_normal(19, STARYU),
        mon_normal(17, TENTACOOL),
        mon_normal(19, REMORAID)
    ),
    party_normal("BERKE@",
        mon_normal(23, QWILFISH)
    ),
    party_normal("KIRK@",
        mon_normal(20, GYARADOS),
        mon_normal(20, GYARADOS)
    ),
    party_normal("MATHEW@",
        mon_normal(23, KRABBY)
    ),
    party_normal("HAL@",
        mon_normal(24, SEEL),
        mon_normal(25, DEWGONG),
        mon_normal(24, SEEL)
    ),
    party_normal("PATON@",
        mon_normal(26, PILOSWINE),
        mon_normal(26, PILOSWINE)
    ),
    party_normal("DARYL@",
        mon_normal(24, SHELLDER),
        mon_normal(25, CLOYSTER),
        mon_normal(24, SHELLDER)
    ),
    party_normal("WALTER@",
        mon_normal(15, HORSEA),
        mon_normal(15, HORSEA),
        mon_normal(20, SEADRA)
    ),
    party_normal("TONY@",
        mon_normal(13, STARYU),
        mon_normal(18, STARMIE),
        mon_normal(16, HORSEA)
    ),
    party_normal("JEROME@",
        mon_normal(26, SEADRA),
        mon_normal(28, TENTACOOL),
        mon_normal(30, TENTACRUEL),
        mon_normal(28, GOLDEEN)
    ),
    party_normal("TUCKER@",
        mon_normal(30, SHELLDER),
        mon_normal(34, CLOYSTER)
    ),
    party_normal("RICK@",
        mon_normal(13, STARYU),
        mon_normal(18, STARMIE),
        mon_normal(16, HORSEA)
    ),
    party_normal("CAMERON@",
        mon_normal(34, MARILL)
    ),
    party_normal("SETH@",
        mon_normal(29, QUAGSIRE),
        mon_normal(29, OCTILLERY),
        mon_normal(32, QUAGSIRE)
    ),
    party_normal("JAMES@",
        mon_normal(13, STARYU),
        mon_normal(18, STARMIE),
        mon_normal(16, HORSEA)
    ),
    party_normal("LEWIS@",
        mon_normal(13, STARYU),
        mon_normal(18, STARMIE),
        mon_normal(16, HORSEA)
    ),
    party_normal("PARKER@",
        mon_normal(32, HORSEA),
        mon_normal(32, HORSEA),
        mon_normal(35, SEADRA)
    ),
};

const struct TrainerParty SwimmerFGroup[] = {
    party_normal("ELAINE@",
        mon_normal(21, STARYU)
    ),
    party_normal("PAULA@",
        mon_normal(19, STARYU),
        mon_normal(19, SHELLDER)
    ),
    party_normal("KAYLEE@",
        mon_normal(18, GOLDEEN),
        mon_normal(20, GOLDEEN),
        mon_normal(20, SEAKING)
    ),
    party_moves("SUSIE@",
        mon_moves(20, PSYDUCK, moves(SCRATCH, TAIL_WHIP, DISABLE, CONFUSION)),
        mon_moves(22, GOLDEEN, moves(PECK, TAIL_WHIP, SUPERSONIC, HORN_ATTACK))
    ),
    party_normal("DENISE@",
        mon_normal(22, SEEL)
    ),
    party_normal("KARA@",
        mon_normal(20, STARYU),
        mon_normal(20, STARMIE)
    ),
    party_moves("WENDY@",
        mon_moves(21, HORSEA, moves(BUBBLE, SMOKESCREEN, LEER, WATER_GUN)),
        mon_moves(21, HORSEA, moves(DRAGON_RAGE, SMOKESCREEN, LEER, WATER_GUN))
    ),
    party_normal("LISA@",
        mon_normal(28, JYNX)
    ),
    party_normal("JILL@",
        mon_normal(28, DEWGONG)
    ),
    party_normal("MARY@",
        mon_normal(20, SEAKING)
    ),
    party_normal("KATIE@",
        mon_normal(33, DEWGONG)
    ),
    party_normal("DAWN@",
        mon_normal(34, SEAKING)
    ),
    party_normal("TARA@",
        mon_normal(20, SEAKING)
    ),
    party_normal("NICOLE@",
        mon_normal(29, MARILL),
        mon_normal(29, MARILL),
        mon_normal(32, LAPRAS)
    ),
    party_normal("LORI@",
        mon_normal(32, STARMIE),
        mon_normal(32, STARMIE)
    ),
    party_normal("JODY@",
        mon_normal(20, SEAKING)
    ),
    party_normal("NIKKI@",
        mon_normal(28, SEEL),
        mon_normal(28, SEEL),
        mon_normal(28, SEEL),
        mon_normal(28, DEWGONG)
    ),
    party_normal("DIANA@",
        mon_normal(37, GOLDUCK)
    ),
    party_normal("BRIANA@",
        mon_normal(35, SEAKING),
        mon_normal(35, SEAKING)
    ),
};

const struct TrainerParty SailorGroup[] = {
    party_normal("EUGENE@",
        mon_normal(17, POLIWHIRL),
        mon_normal(17, RATICATE),
        mon_normal(19, KRABBY)
    ),
    party_normal("HUEY@",
        mon_normal(18, POLIWAG),
        mon_normal(18, POLIWHIRL)
    ),
    party_normal("TERRELL@",
        mon_normal(20, POLIWHIRL)
    ),
    party_moves("KENT@",
        mon_moves(18, KRABBY, moves(BUBBLE, LEER, VICEGRIP, HARDEN)),
        mon_moves(20, KRABBY, moves(BUBBLEBEAM, LEER, VICEGRIP, HARDEN))
    ),
    party_normal("ERNEST@",
        mon_normal(18, MACHOP),
        mon_normal(18, MACHOP),
        mon_normal(18, POLIWHIRL)
    ),
    party_normal("JEFF@",
        mon_normal(32, RATICATE),
        mon_normal(32, RATICATE)
    ),
    party_normal("GARRETT@",
        mon_normal(34, KINGLER)
    ),
    party_normal("KENNETH@",
        mon_normal(28, MACHOP),
        mon_normal(28, MACHOP),
        mon_normal(28, POLIWRATH),
        mon_normal(28, MACHOP)
    ),
    party_normal("STANLY@",
        mon_normal(31, MACHOP),
        mon_normal(33, MACHOKE),
        mon_normal(26, PSYDUCK)
    ),
    party_normal("HARRY@",
        mon_normal(19, WOOPER)
    ),
    party_normal("HUEY@",
        mon_normal(28, POLIWHIRL),
        mon_normal(28, POLIWHIRL)
    ),
    party_normal("HUEY@",
        mon_normal(34, POLIWHIRL),
        mon_normal(34, POLIWRATH)
    ),
    party_moves("HUEY@",
        mon_moves(38, POLITOED, moves(WHIRLPOOL, RAIN_DANCE, BODY_SLAM, PERISH_SONG)),
        mon_moves(38, POLIWRATH, moves(SURF, STRENGTH, ICE_PUNCH, SUBMISSION))
    ),
};

const struct TrainerParty SuperNerdGroup[] = {
    party_normal("STAN@",
        mon_normal(20, GRIMER)
    ),
    party_normal("ERIC@",
        mon_normal(11, GRIMER),
        mon_normal(11, GRIMER)
    ),
    party_normal("GREGG@",
        mon_normal(20, MAGNEMITE),
        mon_normal(20, MAGNEMITE),
        mon_normal(20, MAGNEMITE)
    ),
    party_normal("JAY@",
        mon_normal(22, KOFFING),
        mon_normal(22, KOFFING)
    ),
    party_normal("DAVE@",
        mon_normal(24, DITTO)
    ),
    party_normal("SAM@",
        mon_normal(34, GRIMER),
        mon_normal(34, MUK)
    ),
    party_normal("TOM@",
        mon_normal(32, MAGNEMITE),
        mon_normal(32, MAGNEMITE),
        mon_normal(32, MAGNEMITE)
    ),
    party_normal("PAT@",
        mon_normal(36, PORYGON)
    ),
    party_normal("SHAWN@",
        mon_normal(31, MAGNEMITE),
        mon_normal(33, MUK),
        mon_normal(31, MAGNEMITE)
    ),
    party_normal("TERU@",
        mon_normal(7, MAGNEMITE),
        mon_normal(11, VOLTORB),
        mon_normal(7, MAGNEMITE),
        mon_normal(9, MAGNEMITE)
    ),
    party_normal("RUSS@",
        mon_normal(27, MAGNEMITE),
        mon_normal(27, MAGNEMITE),
        mon_normal(27, MAGNEMITE)
    ),
    party_moves("NORTON@",
        mon_moves(30, PORYGON, moves(CONVERSION, CONVERSION2, RECOVER, TRI_ATTACK))
    ),
    party_moves("HUGH@",
        mon_moves(39, SEADRA, moves(SMOKESCREEN, TWISTER, SURF, WATERFALL))
    ),
    party_moves("MARKUS@",
        mon_moves(19, SLOWPOKE, moves(CURSE, WATER_GUN, GROWL, STRENGTH))
    ),
};

const struct TrainerParty Rival2Group[] = {
    party_moves("?@",
        mon_moves(41, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(42, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(41, MAGNETON, moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(43, GENGAR, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(43, ALAKAZAM, moves(DISABLE, RECOVER, FUTURE_SIGHT, PSYCHIC_M)),
        mon_moves(45, MEGANIUM, moves(RAZOR_LEAF, POISONPOWDER, BODY_SLAM, LIGHT_SCREEN))
    ),
    party_moves("?@",
        mon_moves(41, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(42, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(41, MAGNETON, moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(43, GENGAR, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(43, ALAKAZAM, moves(DISABLE, RECOVER, FUTURE_SIGHT, PSYCHIC_M)),
        mon_moves(45, TYPHLOSION, moves(SMOKESCREEN, QUICK_ATTACK, FLAME_WHEEL, SWIFT))
    ),
    party_moves("?@",
        mon_moves(41, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(42, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(41, MAGNETON, moves(THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(43, GENGAR, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(43, ALAKAZAM, moves(DISABLE, RECOVER, FUTURE_SIGHT, PSYCHIC_M)),
        mon_moves(45, FERALIGATR, moves(RAGE, WATER_GUN, SCARY_FACE, SLASH))
    ),
    party_moves("?@",
        mon_moves(45, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(48, CROBAT, moves(TOXIC, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(45, MAGNETON, moves(THUNDER, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(46, GENGAR, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(46, ALAKAZAM, moves(RECOVER, FUTURE_SIGHT, PSYCHIC_M, REFLECT)),
        mon_moves(50, MEGANIUM, moves(GIGA_DRAIN, BODY_SLAM, LIGHT_SCREEN, SAFEGUARD))
    ),
    party_moves("?@",
        mon_moves(45, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(48, CROBAT, moves(TOXIC, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(45, MAGNETON, moves(THUNDER, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(46, GENGAR, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(46, ALAKAZAM, moves(RECOVER, FUTURE_SIGHT, PSYCHIC_M, REFLECT)),
        mon_moves(50, TYPHLOSION, moves(SMOKESCREEN, QUICK_ATTACK, FIRE_BLAST, SWIFT))
    ),
    party_moves("?@",
        mon_moves(45, SNEASEL, moves(QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER)),
        mon_moves(48, CROBAT, moves(TOXIC, BITE, CONFUSE_RAY, WING_ATTACK)),
        mon_moves(45, MAGNETON, moves(THUNDER, SONICBOOM, THUNDER_WAVE, SWIFT)),
        mon_moves(46, GENGAR, moves(MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY)),
        mon_moves(46, ALAKAZAM, moves(RECOVER, FUTURE_SIGHT, PSYCHIC_M, REFLECT)),
        mon_moves(50, FERALIGATR, moves(SURF, RAIN_DANCE, SLASH, SCREECH))
    ),
};

const struct TrainerParty GuitaristGroup[] = {
    party_normal("CLYDE@",
        mon_normal(34, ELECTABUZZ)
    ),
    party_normal("VINCENT@",
        mon_normal(27, MAGNEMITE),
        mon_normal(33, VOLTORB),
        mon_normal(32, MAGNEMITE),
        mon_normal(32, MAGNEMITE)
    ),
};

const struct TrainerParty HikerGroup[] = {
    party_normal("ANTHONY@",
        mon_normal(16, GEODUDE),
        mon_normal(18, MACHAMP)
    ),
    party_normal("RUSSELL@",
        mon_normal(4, GEODUDE),
        mon_normal(6, GEODUDE),
        mon_normal(8, GEODUDE)
    ),
    party_normal("PHILLIP@",
        mon_normal(23, GEODUDE),
        mon_normal(23, GEODUDE),
        mon_normal(23, GRAVELER)
    ),
    party_normal("LEONARD@",
        mon_normal(23, GEODUDE),
        mon_normal(25, MACHOP)
    ),
    party_normal("ANTHONY@",
        mon_normal(11, GEODUDE),
        mon_normal(11, MACHOP)
    ),
    party_normal("BENJAMIN@",
        mon_normal(14, DIGLETT),
        mon_normal(14, GEODUDE),
        mon_normal(16, DUGTRIO)
    ),
    party_normal("ERIK@",
        mon_normal(24, MACHOP),
        mon_normal(27, GRAVELER),
        mon_normal(27, MACHOP)
    ),
    party_normal("MICHAEL@",
        mon_normal(25, GEODUDE),
        mon_normal(25, GRAVELER),
        mon_normal(25, GOLEM)
    ),
    party_normal("PARRY@",
        mon_normal(35, ONIX),
        mon_normal(33, SWINUB)
    ),
    party_moves("TIMOTHY@",
        mon_moves(27, DIGLETT, moves(MAGNITUDE, DIG, SAND_ATTACK, SLASH)),
        mon_moves(27, DUGTRIO, moves(MAGNITUDE, DIG, SAND_ATTACK, SLASH))
    ),
    party_normal("BAILEY@",
        mon_normal(13, GEODUDE),
        mon_normal(13, GEODUDE),
        mon_normal(13, GEODUDE),
        mon_normal(13, GEODUDE),
        mon_normal(13, GEODUDE)
    ),
    party_normal("ANTHONY@",
        mon_normal(25, GRAVELER),
        mon_normal(27, GRAVELER),
        mon_normal(29, MACHOKE)
    ),
    party_normal("TIM@",
        mon_normal(31, GRAVELER),
        mon_normal(31, GRAVELER),
        mon_normal(31, GRAVELER)
    ),
    party_normal("NOLAND@",
        mon_normal(31, SANDSLASH),
        mon_normal(33, GOLEM)
    ),
    party_normal("SIDNEY@",
        mon_normal(34, DUGTRIO),
        mon_normal(32, ONIX)
    ),
    party_normal("KENNY@",
        mon_normal(27, SANDSLASH),
        mon_normal(29, GRAVELER),
        mon_normal(31, GOLEM),
        mon_normal(29, GRAVELER)
    ),
    party_normal("JIM@",
        mon_normal(35, MACHAMP)
    ),
    party_normal("DANIEL@",
        mon_normal(11, ONIX)
    ),
    party_moves("PARRY@",
        mon_moves(35, PILOSWINE, moves(EARTHQUAKE, BLIZZARD, REST, TAKE_DOWN)),
        mon_moves(35, DUGTRIO, moves(MAGNITUDE, DIG, MUD_SLAP, SLASH)),
        mon_moves(38, STEELIX, moves(DIG, IRON_TAIL, SANDSTORM, SLAM))
    ),
    party_normal("PARRY@",
        mon_normal(29, ONIX)
    ),
    party_normal("ANTHONY@",
        mon_normal(30, GRAVELER),
        mon_normal(30, GRAVELER),
        mon_normal(32, MACHOKE)
    ),
    party_moves("ANTHONY@",
        mon_moves(34, GRAVELER, moves(MAGNITUDE, SELFDESTRUCT, DEFENSE_CURL, ROLLOUT)),
        mon_moves(36, GOLEM, moves(MAGNITUDE, SELFDESTRUCT, DEFENSE_CURL, ROLLOUT)),
        mon_moves(34, MACHOKE, moves(KARATE_CHOP, VITAL_THROW, HEADBUTT, DIG))
    ),
};

const struct TrainerParty BikerGroup[] = {
    party_normal("BENNY@",
        mon_normal(20, KOFFING),
        mon_normal(20, KOFFING),
        mon_normal(20, KOFFING)
    ),
    party_normal("KAZU@",
        mon_normal(20, KOFFING),
        mon_normal(20, KOFFING),
        mon_normal(20, KOFFING)
    ),
    party_normal("DWAYNE@",
        mon_normal(27, KOFFING),
        mon_normal(28, KOFFING),
        mon_normal(29, KOFFING),
        mon_normal(30, KOFFING)
    ),
    party_normal("HARRIS@",
        mon_normal(34, FLAREON)
    ),
    party_normal("ZEKE@",
        mon_normal(32, KOFFING),
        mon_normal(32, KOFFING)
    ),
    party_normal("CHARLES@",
        mon_normal(30, KOFFING),
        mon_normal(30, CHARMELEON),
        mon_normal(30, WEEZING)
    ),
    party_normal("RILEY@",
        mon_normal(34, WEEZING)
    ),
    party_normal("JOEL@",
        mon_normal(32, MAGMAR),
        mon_normal(32, MAGMAR)
    ),
    party_normal("GLENN@",
        mon_normal(28, KOFFING),
        mon_normal(30, MAGMAR),
        mon_normal(32, WEEZING)
    ),
};

const struct TrainerParty BlaineGroup[] = {
    party_moves("BLAINE@",
        mon_moves(45, MAGCARGO, moves(CURSE, SMOG, FLAMETHROWER, ROCK_SLIDE)),
        mon_moves(45, MAGMAR, moves(THUNDERPUNCH, FIRE_PUNCH, SUNNY_DAY, CONFUSE_RAY)),
        mon_moves(50, RAPIDASH, moves(QUICK_ATTACK, FIRE_SPIN, FURY_ATTACK, FIRE_BLAST))
    ),
};

const struct TrainerParty BurglarGroup[] = {
    party_normal("DUNCAN@",
        mon_normal(23, KOFFING),
        mon_normal(25, MAGMAR),
        mon_normal(23, KOFFING)
    ),
    party_moves("EDDIE@",
        mon_moves(26, GROWLITHE, moves(ROAR, EMBER, LEER, TAKE_DOWN)),
        mon_moves(24, KOFFING, moves(TACKLE, SMOG, SLUDGE, SMOKESCREEN))
    ),
    party_normal("COREY@",
        mon_normal(25, KOFFING),
        mon_normal(28, MAGMAR),
        mon_normal(25, KOFFING),
        mon_normal(30, KOFFING)
    ),
};

const struct TrainerParty FirebreatherGroup[] = {
    party_normal("OTIS@",
        mon_normal(29, MAGMAR),
        mon_normal(32, WEEZING),
        mon_normal(29, MAGMAR)
    ),
    party_normal("DICK@",
        mon_normal(17, CHARMELEON)
    ),
    party_normal("NED@",
        mon_normal(15, KOFFING),
        mon_normal(16, GROWLITHE),
        mon_normal(15, KOFFING)
    ),
    party_normal("BURT@",
        mon_normal(32, KOFFING),
        mon_normal(32, SLUGMA)
    ),
    party_normal("BILL@",
        mon_normal(6, KOFFING),
        mon_normal(6, KOFFING)
    ),
    party_normal("WALT@",
        mon_normal(11, MAGMAR),
        mon_normal(13, MAGMAR)
    ),
    party_normal("RAY@",
        mon_normal(9, VULPIX)
    ),
    party_normal("LYLE@",
        mon_normal(28, KOFFING),
        mon_normal(31, FLAREON),
        mon_normal(28, KOFFING)
    ),
};

const struct TrainerParty JugglerGroup[] = {
    party_normal("IRWIN@",
        mon_normal(2, VOLTORB),
        mon_normal(6, VOLTORB),
        mon_normal(10, VOLTORB),
        mon_normal(14, VOLTORB)
    ),
    party_normal("FRITZ@",
        mon_normal(29, MR__MIME),
        mon_normal(29, MAGMAR),
        mon_normal(29, MACHOKE)
    ),
    party_normal("HORTON@",
        mon_normal(33, ELECTRODE),
        mon_normal(33, ELECTRODE),
        mon_normal(33, ELECTRODE),
        mon_normal(33, ELECTRODE)
    ),
    party_normal("IRWIN@",
        mon_normal(6, VOLTORB),
        mon_normal(10, VOLTORB),
        mon_normal(14, VOLTORB),
        mon_normal(18, VOLTORB)
    ),
    party_normal("IRWIN@",
        mon_normal(18, VOLTORB),
        mon_normal(22, VOLTORB),
        mon_normal(26, VOLTORB),
        mon_normal(30, ELECTRODE)
    ),
    party_normal("IRWIN@",
        mon_normal(18, VOLTORB),
        mon_normal(22, VOLTORB),
        mon_normal(26, VOLTORB),
        mon_normal(30, ELECTRODE)
    ),
};

const struct TrainerParty BlackbeltGroup[] = {
    party_normal("KENJI@",
        mon_normal(27, ONIX),
        mon_normal(30, HITMONLEE),
        mon_normal(27, ONIX),
        mon_normal(32, MACHOKE)
    ),
    party_moves("YOSHI@",
        mon_moves(27, HITMONLEE, moves(DOUBLE_KICK, MEDITATE, JUMP_KICK, FOCUS_ENERGY))
    ),
    party_moves("KENJI@",
        mon_moves(33, ONIX, moves(BIND, ROCK_THROW, TOXIC, DIG)),
        mon_moves(38, MACHAMP, moves(HEADBUTT, SWAGGER, THUNDERPUNCH, VITAL_THROW)),
        mon_moves(33, STEELIX, moves(EARTHQUAKE, ROCK_THROW, IRON_TAIL, SANDSTORM)),
        mon_moves(36, HITMONLEE, moves(DOUBLE_TEAM, HI_JUMP_KICK, MUD_SLAP, SWIFT))
    ),
    party_moves("LAO@",
        mon_moves(27, HITMONCHAN, moves(COMET_PUNCH, THUNDERPUNCH, ICE_PUNCH, FIRE_PUNCH))
    ),
    party_moves("NOB@",
        mon_moves(25, MACHOP, moves(LEER, FOCUS_ENERGY, KARATE_CHOP, SEISMIC_TOSS)),
        mon_moves(25, MACHOKE, moves(LEER, KARATE_CHOP, SEISMIC_TOSS, ROCK_SLIDE))
    ),
    party_normal("KIYO@",
        mon_normal(34, HITMONLEE),
        mon_normal(34, HITMONCHAN)
    ),
    party_normal("LUNG@",
        mon_normal(23, MANKEY),
        mon_normal(23, MANKEY),
        mon_normal(25, PRIMEAPE)
    ),
    party_normal("KENJI@",
        mon_normal(28, MACHOKE)
    ),
    party_normal("WAI@",
        mon_normal(30, MACHOKE),
        mon_normal(32, MACHOKE),
        mon_normal(34, MACHOKE)
    ),
};

const struct TrainerParty ExecutiveMGroup[] = {
    party_moves("EXECUTIVE@",
        mon_moves(33, HOUNDOUR, moves(EMBER, ROAR, BITE, FAINT_ATTACK)),
        mon_moves(33, KOFFING, moves(TACKLE, SLUDGE, SMOKESCREEN, HAZE)),
        mon_moves(35, HOUNDOOM, moves(EMBER, SMOG, BITE, FAINT_ATTACK))
    ),
    party_moves("EXECUTIVE@",
        mon_moves(36, GOLBAT, moves(LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK))
    ),
    party_moves("EXECUTIVE@",
        mon_moves(30, KOFFING, moves(TACKLE, SELFDESTRUCT, SLUDGE, SMOKESCREEN)),
        mon_moves(30, KOFFING, moves(TACKLE, SELFDESTRUCT, SLUDGE, SMOKESCREEN)),
        mon_moves(30, KOFFING, moves(TACKLE, SELFDESTRUCT, SLUDGE, SMOKESCREEN)),
        mon_moves(32, WEEZING, moves(TACKLE, EXPLOSION, SLUDGE, SMOKESCREEN)),
        mon_moves(30, KOFFING, moves(TACKLE, SELFDESTRUCT, SLUDGE, SMOKESCREEN)),
        mon_moves(30, KOFFING, moves(TACKLE, SMOG, SLUDGE, SMOKESCREEN))
    ),
    party_normal("EXECUTIVE@",
        mon_normal(22, ZUBAT),
        mon_normal(24, RATICATE),
        mon_normal(22, KOFFING)
    ),
};

const struct TrainerParty PsychicGroup[] = {
    party_normal("NATHAN@",
        mon_normal(26, GIRAFARIG)
    ),
    party_normal("FRANKLIN@",
        mon_normal(37, KADABRA)
    ),
    party_normal("HERMAN@",
        mon_normal(30, EXEGGCUTE),
        mon_normal(30, EXEGGCUTE),
        mon_normal(30, EXEGGUTOR)
    ),
    party_normal("FIDEL@",
        mon_normal(34, XATU)
    ),
    party_moves("GREG@",
        mon_moves(17, DROWZEE, moves(HYPNOSIS, DISABLE, DREAM_EATER, NO_MOVE))
    ),
    party_moves("NORMAN@",
        mon_moves(17, SLOWPOKE, moves(TACKLE, GROWL, WATER_GUN, NO_MOVE)),
        mon_moves(20, SLOWPOKE, moves(CURSE, BODY_SLAM, WATER_GUN, CONFUSION))
    ),
    party_moves("MARK@",
        mon_moves(13, ABRA, moves(TELEPORT, FLASH, NO_MOVE, NO_MOVE)),
        mon_moves(13, ABRA, moves(TELEPORT, FLASH, NO_MOVE, NO_MOVE)),
        mon_moves(15, KADABRA, moves(TELEPORT, KINESIS, CONFUSION, NO_MOVE))
    ),
    party_moves("PHIL@",
        mon_moves(24, NATU, moves(LEER, NIGHT_SHADE, FUTURE_SIGHT, CONFUSE_RAY)),
        mon_moves(26, KADABRA, moves(DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT))
    ),
    party_normal("RICHARD@",
        mon_normal(36, ESPEON)
    ),
    party_normal("GILBERT@",
        mon_normal(30, STARMIE),
        mon_normal(30, EXEGGCUTE),
        mon_normal(34, GIRAFARIG)
    ),
    party_normal("JARED@",
        mon_normal(32, MR__MIME),
        mon_normal(32, EXEGGCUTE),
        mon_normal(35, EXEGGCUTE)
    ),
    party_normal("RODNEY@",
        mon_normal(29, DROWZEE),
        mon_normal(33, HYPNO)
    ),
};

const struct TrainerParty PicnickerGroup[] = {
    party_normal("LIZ@",
        mon_normal(9, NIDORAN_F)
    ),
    party_normal("GINA@",
        mon_normal(9, HOPPIP),
        mon_normal(9, HOPPIP),
        mon_normal(12, BULBASAUR)
    ),
    party_moves("BROOKE@",
        mon_moves(16, PIKACHU, moves(THUNDERSHOCK, GROWL, QUICK_ATTACK, DOUBLE_TEAM))
    ),
    party_normal("KIM@",
        mon_normal(15, VULPIX)
    ),
    party_normal("CINDY@",
        mon_normal(36, NIDOQUEEN)
    ),
    party_normal("HOPE@",
        mon_normal(34, FLAAFFY)
    ),
    party_normal("SHARON@",
        mon_normal(31, FURRET),
        mon_normal(33, RAPIDASH)
    ),
    party_normal("DEBRA@",
        mon_normal(33, SEAKING)
    ),
    party_normal("GINA@",
        mon_normal(14, HOPPIP),
        mon_normal(14, HOPPIP),
        mon_normal(17, IVYSAUR)
    ),
    party_normal("ERIN@",
        mon_normal(16, PONYTA),
        mon_normal(16, PONYTA)
    ),
    party_normal("LIZ@",
        mon_normal(15, WEEPINBELL),
        mon_normal(15, NIDORINA)
    ),
    party_normal("LIZ@",
        mon_normal(19, WEEPINBELL),
        mon_normal(19, NIDORINO),
        mon_normal(21, NIDOQUEEN)
    ),
    party_normal("HEIDI@",
        mon_normal(32, SKIPLOOM),
        mon_normal(32, SKIPLOOM)
    ),
    party_normal("EDNA@",
        mon_normal(30, NIDORINA),
        mon_normal(34, RAICHU)
    ),
    party_normal("GINA@",
        mon_normal(26, SKIPLOOM),
        mon_normal(26, SKIPLOOM),
        mon_normal(29, IVYSAUR)
    ),
    party_moves("TIFFANY@",
        mon_moves(31, CLEFAIRY, moves(ENCORE, SING, DOUBLESLAP, MINIMIZE))
    ),
    party_moves("TIFFANY@",
        mon_moves(37, CLEFAIRY, moves(ENCORE, DOUBLESLAP, MINIMIZE, METRONOME))
    ),
    party_normal("ERIN@",
        mon_normal(32, PONYTA),
        mon_normal(32, PONYTA)
    ),
    party_normal("TANYA@",
        mon_normal(37, EXEGGUTOR)
    ),
    party_moves("TIFFANY@",
        mon_moves(20, CLEFAIRY, moves(ENCORE, SING, DOUBLESLAP, MINIMIZE))
    ),
    party_moves("ERIN@",
        mon_moves(36, PONYTA, moves(DOUBLE_TEAM, STOMP, FIRE_SPIN, SUNNY_DAY)),
        mon_moves(34, RAICHU, moves(SWIFT, MUD_SLAP, QUICK_ATTACK, THUNDERBOLT)),
        mon_moves(36, PONYTA, moves(DOUBLE_TEAM, STOMP, FIRE_SPIN, SUNNY_DAY))
    ),
    party_normal("LIZ@",
        mon_normal(24, WEEPINBELL),
        mon_normal(26, NIDORINO),
        mon_normal(26, NIDOQUEEN)
    ),
    party_moves("LIZ@",
        mon_moves(30, WEEPINBELL, moves(SLEEP_POWDER, POISONPOWDER, STUN_SPORE, SLUDGE_BOMB)),
        mon_moves(32, NIDOKING, moves(EARTHQUAKE, DOUBLE_KICK, POISON_STING, IRON_TAIL)),
        mon_moves(32, NIDOQUEEN, moves(EARTHQUAKE, DOUBLE_KICK, TAIL_WHIP, BODY_SLAM))
    ),
    party_normal("GINA@",
        mon_normal(30, SKIPLOOM),
        mon_normal(30, SKIPLOOM),
        mon_normal(32, IVYSAUR)
    ),
    party_moves("GINA@",
        mon_moves(33, JUMPLUFF, moves(STUN_SPORE, SUNNY_DAY, LEECH_SEED, COTTON_SPORE)),
        mon_moves(33, JUMPLUFF, moves(SUNNY_DAY, SLEEP_POWDER, LEECH_SEED, COTTON_SPORE)),
        mon_moves(38, VENUSAUR, moves(SOLARBEAM, RAZOR_LEAF, HEADBUTT, MUD_SLAP))
    ),
    party_moves("TIFFANY@",
        mon_moves(43, CLEFAIRY, moves(METRONOME, ENCORE, MOONLIGHT, MINIMIZE))
    ),
};

const struct TrainerParty CamperGroup[] = {
    party_normal("ROLAND@",
        mon_normal(9, NIDORAN_M)
    ),
    party_normal("TODD@",
        mon_normal(14, PSYDUCK)
    ),
    party_normal("IVAN@",
        mon_normal(10, DIGLETT),
        mon_normal(10, ZUBAT),
        mon_normal(14, DIGLETT)
    ),
    party_normal("ELLIOT@",
        mon_normal(13, SANDSHREW),
        mon_normal(15, MARILL)
    ),
    party_normal("BARRY@",
        mon_normal(36, NIDOKING)
    ),
    party_normal("LLOYD@",
        mon_normal(34, NIDOKING)
    ),
    party_normal("DEAN@",
        mon_normal(33, GOLDUCK),
        mon_normal(31, SANDSLASH)
    ),
    party_normal("SID@",
        mon_normal(32, DUGTRIO),
        mon_normal(29, PRIMEAPE),
        mon_normal(29, POLIWRATH)
    ),
    party_normal("HARVEY@",
        mon_normal(15, NIDORINO)
    ),
    party_normal("DALE@",
        mon_normal(15, NIDORINO)
    ),
    party_normal("TED@",
        mon_normal(17, MANKEY)
    ),
    party_normal("TODD@",
        mon_normal(17, GEODUDE),
        mon_normal(17, GEODUDE),
        mon_normal(23, PSYDUCK)
    ),
    party_normal("TODD@",
        mon_normal(23, GEODUDE),
        mon_normal(23, GEODUDE),
        mon_normal(26, PSYDUCK)
    ),
    party_normal("THOMAS@",
        mon_normal(33, GRAVELER),
        mon_normal(36, GRAVELER),
        mon_normal(40, GOLBAT),
        mon_normal(42, GOLDUCK)
    ),
    party_normal("LEROY@",
        mon_normal(33, GRAVELER),
        mon_normal(36, GRAVELER),
        mon_normal(40, GOLBAT),
        mon_normal(42, GOLDUCK)
    ),
    party_normal("DAVID@",
        mon_normal(33, GRAVELER),
        mon_normal(36, GRAVELER),
        mon_normal(40, GOLBAT),
        mon_normal(42, GOLDUCK)
    ),
    party_normal("JOHN@",
        mon_normal(33, GRAVELER),
        mon_normal(36, GRAVELER),
        mon_normal(40, GOLBAT),
        mon_normal(42, GOLDUCK)
    ),
    party_normal("JERRY@",
        mon_normal(37, SANDSLASH)
    ),
    party_normal("SPENCER@",
        mon_normal(17, SANDSHREW),
        mon_normal(17, SANDSLASH),
        mon_normal(19, ZUBAT)
    ),
    party_normal("TODD@",
        mon_normal(30, GRAVELER),
        mon_normal(30, GRAVELER),
        mon_normal(30, SLUGMA),
        mon_normal(32, PSYDUCK)
    ),
    party_moves("TODD@",
        mon_moves(33, GRAVELER, moves(SELFDESTRUCT, ROCK_THROW, HARDEN, MAGNITUDE)),
        mon_moves(33, GRAVELER, moves(SELFDESTRUCT, ROCK_THROW, HARDEN, MAGNITUDE)),
        mon_moves(36, MAGCARGO, moves(ROCK_THROW, HARDEN, AMNESIA, FLAMETHROWER)),
        mon_moves(34, GOLDUCK, moves(DISABLE, PSYCHIC_M, SURF, PSYCH_UP))
    ),
    party_normal("QUENTIN@",
        mon_normal(30, FEAROW),
        mon_normal(30, PRIMEAPE),
        mon_normal(30, TAUROS)
    ),
};

const struct TrainerParty ExecutiveFGroup[] = {
    party_moves("EXECUTIVE@",
        mon_moves(32, ARBOK, moves(WRAP, POISON_STING, BITE, GLARE)),
        mon_moves(32, VILEPLUME, moves(ABSORB, SWEET_SCENT, SLEEP_POWDER, ACID)),
        mon_moves(32, MURKROW, moves(PECK, PURSUIT, HAZE, NIGHT_SHADE))
    ),
    party_moves("EXECUTIVE@",
        mon_moves(23, ARBOK, moves(WRAP, LEER, POISON_STING, BITE)),
        mon_moves(23, GLOOM, moves(ABSORB, SWEET_SCENT, SLEEP_POWDER, ACID)),
        mon_moves(25, MURKROW, moves(PECK, PURSUIT, HAZE, NO_MOVE))
    ),
};

const struct TrainerParty SageGroup[] = {
    party_normal("CHOW@",
        mon_normal(3, BELLSPROUT),
        mon_normal(3, BELLSPROUT),
        mon_normal(3, BELLSPROUT)
    ),
    party_normal("NICO@",
        mon_normal(3, BELLSPROUT),
        mon_normal(3, BELLSPROUT),
        mon_normal(3, BELLSPROUT)
    ),
    party_normal("JIN@",
        mon_normal(6, BELLSPROUT)
    ),
    party_normal("TROY@",
        mon_normal(7, BELLSPROUT),
        mon_normal(7, HOOTHOOT)
    ),
    party_normal("JEFFREY@",
        mon_normal(22, HAUNTER)
    ),
    party_normal("PING@",
        mon_normal(16, GASTLY),
        mon_normal(16, GASTLY),
        mon_normal(16, GASTLY),
        mon_normal(16, GASTLY),
        mon_normal(16, GASTLY)
    ),
    party_normal("EDMOND@",
        mon_normal(3, BELLSPROUT),
        mon_normal(3, BELLSPROUT),
        mon_normal(3, BELLSPROUT)
    ),
    party_normal("NEAL@",
        mon_normal(6, BELLSPROUT)
    ),
    party_normal("LI@",
        mon_normal(7, BELLSPROUT),
        mon_normal(7, BELLSPROUT),
        mon_normal(10, HOOTHOOT)
    ),
    party_normal("GAKU@",
        mon_normal(32, NOCTOWL),
        mon_normal(32, FLAREON)
    ),
    party_normal("MASA@",
        mon_normal(32, NOCTOWL),
        mon_normal(32, JOLTEON)
    ),
    party_normal("KOJI@",
        mon_normal(32, NOCTOWL),
        mon_normal(32, VAPOREON)
    ),
};

const struct TrainerParty MediumGroup[] = {
    party_normal("MARTHA@",
        mon_normal(18, GASTLY),
        mon_normal(20, HAUNTER),
        mon_normal(20, GASTLY)
    ),
    party_normal("GRACE@",
        mon_normal(20, HAUNTER),
        mon_normal(20, HAUNTER)
    ),
    party_normal("BETHANY@",
        mon_normal(25, HAUNTER)
    ),
    party_normal("MARGRET@",
        mon_normal(25, HAUNTER)
    ),
    party_normal("ETHEL@",
        mon_normal(25, HAUNTER)
    ),
    party_normal("REBECCA@",
        mon_normal(35, DROWZEE),
        mon_normal(35, HYPNO)
    ),
    party_normal("DORIS@",
        mon_normal(34, SLOWPOKE),
        mon_normal(36, SLOWBRO)
    ),
};

const struct TrainerParty BoarderGroup[] = {
    party_normal("RONALD@",
        mon_normal(24, SEEL),
        mon_normal(25, DEWGONG),
        mon_normal(24, SEEL)
    ),
    party_normal("BRAD@",
        mon_normal(26, SWINUB),
        mon_normal(26, SWINUB)
    ),
    party_normal("DOUGLAS@",
        mon_normal(24, SHELLDER),
        mon_normal(25, CLOYSTER),
        mon_normal(24, SHELLDER)
    ),
};

const struct TrainerParty PokefanMGroup[] = {
    party_item("WILLIAM@",
        mon_item(14, RAICHU, BERRY)
    ),
    party_item("DEREK@",
        mon_item(17, PIKACHU, BERRY)
    ),
    party_item("ROBERT@",
        mon_item(33, QUAGSIRE, BERRY)
    ),
    party_item("JOSHUA@",
        mon_item(23, PIKACHU, BERRY),
        mon_item(23, PIKACHU, BERRY),
        mon_item(23, PIKACHU, BERRY),
        mon_item(23, PIKACHU, BERRY),
        mon_item(23, PIKACHU, BERRY),
        mon_item(23, PIKACHU, BERRY)
    ),
    party_item("CARTER@",
        mon_item(29, BULBASAUR, BERRY),
        mon_item(29, CHARMANDER, BERRY),
        mon_item(29, SQUIRTLE, BERRY)
    ),
    party_item("TREVOR@",
        mon_item(33, PSYDUCK, BERRY)
    ),
    party_item("BRANDON@",
        mon_item(13, SNUBBULL, BERRY)
    ),
    party_item("JEREMY@",
        mon_item(28, MEOWTH, BERRY),
        mon_item(28, MEOWTH, BERRY),
        mon_item(28, MEOWTH, BERRY)
    ),
    party_item("COLIN@",
        mon_item(32, DELIBIRD, BERRY)
    ),
    party_item("DEREK@",
        mon_item(19, PIKACHU, BERRY)
    ),
    party_item("DEREK@",
        mon_item(36, PIKACHU, BERRY)
    ),
    party_item("ALEX@",
        mon_item(29, NIDOKING, BERRY),
        mon_item(29, SLOWKING, BERRY),
        mon_item(29, SEAKING, BERRY)
    ),
    party_item("REX@",
        mon_item(35, PHANPY, BERRY)
    ),
    party_item("ALLAN@",
        mon_item(35, TEDDIURSA, BERRY)
    ),
};

const struct TrainerParty KimonoGirlGroup[] = {
    party_normal("NAOKO@",
        mon_normal(20, SKIPLOOM),
        mon_normal(20, VULPIX),
        mon_normal(18, SKIPLOOM)
    ),
    party_normal("NAOKO@",
        mon_normal(17, FLAREON)
    ),
    party_normal("SAYO@",
        mon_normal(17, ESPEON)
    ),
    party_normal("ZUKI@",
        mon_normal(17, UMBREON)
    ),
    party_normal("KUNI@",
        mon_normal(17, VAPOREON)
    ),
    party_normal("MIKI@",
        mon_normal(17, JOLTEON)
    ),
};

const struct TrainerParty TwinsGroup[] = {
    party_normal("AMY & MAY@",
        mon_normal(10, SPINARAK),
        mon_normal(10, LEDYBA)
    ),
    party_moves("ANN & ANNE@",
        mon_moves(16, CLEFAIRY, moves(GROWL, ENCORE, DOUBLESLAP, METRONOME)),
        mon_moves(16, JIGGLYPUFF, moves(SING, DEFENSE_CURL, POUND, DISABLE))
    ),
    party_moves("ANN & ANNE@",
        mon_moves(16, JIGGLYPUFF, moves(SING, DEFENSE_CURL, POUND, DISABLE)),
        mon_moves(16, CLEFAIRY, moves(GROWL, ENCORE, DOUBLESLAP, METRONOME))
    ),
    party_normal("AMY & MAY@",
        mon_normal(10, LEDYBA),
        mon_normal(10, SPINARAK)
    ),
    party_normal("JO & ZOE@",
        mon_normal(35, VICTREEBEL),
        mon_normal(35, VILEPLUME)
    ),
    party_normal("JO & ZOE@",
        mon_normal(35, VILEPLUME),
        mon_normal(35, VICTREEBEL)
    ),
    party_normal("MEG & PEG@",
        mon_normal(31, TEDDIURSA),
        mon_normal(31, PHANPY)
    ),
    party_normal("MEG & PEG@",
        mon_normal(31, PHANPY),
        mon_normal(31, TEDDIURSA)
    ),
    party_moves("LEA & PIA@",
        mon_moves(35, DRATINI, moves(THUNDER_WAVE, TWISTER, FLAMETHROWER, HEADBUTT)),
        mon_moves(35, DRATINI, moves(THUNDER_WAVE, TWISTER, ICE_BEAM, HEADBUTT))
    ),
    party_moves("LEA & PIA@",
        mon_moves(38, DRATINI, moves(THUNDER_WAVE, TWISTER, ICE_BEAM, HEADBUTT)),
        mon_moves(38, DRATINI, moves(THUNDER_WAVE, TWISTER, FLAMETHROWER, HEADBUTT))
    ),
};

const struct TrainerParty PokefanFGroup[] = {
    party_item("BEVERLY@",
        mon_item(14, SNUBBULL, BERRY)
    ),
    party_item("RUTH@",
        mon_item(17, PIKACHU, BERRY)
    ),
    party_item("BEVERLY@",
        mon_item(18, SNUBBULL, BERRY)
    ),
    party_item("BEVERLY@",
        mon_item(30, GRANBULL, BERRY)
    ),
    party_item("GEORGIA@",
        mon_item(23, SENTRET, BERRY),
        mon_item(23, SENTRET, BERRY),
        mon_item(23, SENTRET, BERRY),
        mon_item(28, FURRET, BERRY),
        mon_item(23, SENTRET, BERRY)
    ),
    party_item("JAIME@",
        mon_item(16, MEOWTH, BERRY)
    ),
};

const struct TrainerParty RedGroup[] = {
    party_moves("RED@",
        mon_moves(81, PIKACHU, moves(CHARM, QUICK_ATTACK, THUNDERBOLT, THUNDER)),
        mon_moves(73, ESPEON, moves(MUD_SLAP, REFLECT, SWIFT, PSYCHIC_M)),
        mon_moves(75, SNORLAX, moves(AMNESIA, SNORE, REST, BODY_SLAM)),
        mon_moves(77, VENUSAUR, moves(SUNNY_DAY, GIGA_DRAIN, SYNTHESIS, SOLARBEAM)),
        mon_moves(77, CHARIZARD, moves(FLAMETHROWER, WING_ATTACK, SLASH, FIRE_SPIN)),
        mon_moves(77, BLASTOISE, moves(RAIN_DANCE, SURF, BLIZZARD, WHIRLPOOL))
    ),
};

const struct TrainerParty BlueGroup[] = {
    party_moves("BLUE@",
        mon_moves(56, PIDGEOT, moves(QUICK_ATTACK, WHIRLWIND, WING_ATTACK, MIRROR_MOVE)),
        mon_moves(54, ALAKAZAM, moves(DISABLE, RECOVER, PSYCHIC_M, REFLECT)),
        mon_moves(56, RHYDON, moves(FURY_ATTACK, SANDSTORM, ROCK_SLIDE, EARTHQUAKE)),
        mon_moves(58, GYARADOS, moves(TWISTER, HYDRO_PUMP, RAIN_DANCE, HYPER_BEAM)),
        mon_moves(58, EXEGGUTOR, moves(SUNNY_DAY, LEECH_SEED, EGG_BOMB, SOLARBEAM)),
        mon_moves(58, ARCANINE, moves(ROAR, SWIFT, FLAMETHROWER, EXTREMESPEED))
    ),
};

const struct TrainerParty OfficerGroup[] = {
    party_normal("KEITH@",
        mon_normal(17, GROWLITHE)
    ),
    party_normal("DIRK@",
        mon_normal(14, GROWLITHE),
        mon_normal(14, GROWLITHE)
    ),
};

const struct TrainerParty GruntFGroup[] = {
    party_normal("GRUNT@",
        mon_normal(9, ZUBAT),
        mon_normal(11, EKANS)
    ),
    party_normal("GRUNT@",
        mon_normal(26, ARBOK)
    ),
    party_normal("GRUNT@",
        mon_normal(25, GLOOM),
        mon_normal(25, GLOOM)
    ),
    party_normal("GRUNT@",
        mon_normal(21, EKANS),
        mon_normal(23, ODDISH),
        mon_normal(21, EKANS),
        mon_normal(24, GLOOM)
    ),
    party_moves("GRUNT@",
        mon_moves(18, EKANS, moves(WRAP, LEER, POISON_STING, BITE)),
        mon_moves(18, GLOOM, moves(ABSORB, SWEET_SCENT, STUN_SPORE, SLEEP_POWDER))
    ),
};

const struct TrainerParty MysticalmanGroup[] = {
    party_moves("EUSINE@",
        mon_moves(23, DROWZEE, moves(DREAM_EATER, HYPNOSIS, DISABLE, CONFUSION)),
        mon_moves(23, HAUNTER, moves(LICK, HYPNOSIS, MEAN_LOOK, CURSE)),
        mon_moves(25, ELECTRODE, moves(SCREECH, SONICBOOM, THUNDER, ROLLOUT)),
    ),
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
    KarenGroup,
    KogaGroup,
    ChampionGroup,
    BrockGroup,
    MistyGroup,
    LtSurgeGroup,
    ScientistGroup,
    ErikaGroup,
    YoungsterGroup,
    SchoolboyGroup,
    BirdKeeperGroup,
    LassGroup,
    JanineGroup,
    CooltrainerMGroup,
    CooltrainerFGroup,
    BeautyGroup,
    PokemaniacGroup,
    GruntMGroup,
    GentlemanGroup,
    SkierGroup,
    TeacherGroup,
    SabrinaGroup,
    BugCatcherGroup,
    FisherGroup,
    SwimmerMGroup,
    SwimmerFGroup,
    SailorGroup,
    SuperNerdGroup,
    Rival2Group,
    GuitaristGroup,
    HikerGroup,
    BikerGroup,
    BlaineGroup,
    BurglarGroup,
    FirebreatherGroup,
    JugglerGroup,
    BlackbeltGroup,
    ExecutiveMGroup,
    PsychicGroup,
    PicnickerGroup,
    CamperGroup,
    ExecutiveFGroup,
    SageGroup,
    MediumGroup,
    BoarderGroup,
    PokefanMGroup,
    KimonoGirlGroup,
    TwinsGroup,
    PokefanFGroup,
    RedGroup,
    BlueGroup,
    OfficerGroup,
    GruntFGroup,
    MysticalmanGroup,
};
