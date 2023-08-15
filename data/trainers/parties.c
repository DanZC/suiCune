#include "../../constants.h"

const struct TrainerParty FalknerGroup[] = {
    {"FALKNER@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=7, .species=PIDGEY, .moves={TACKLE, MUD_SLAP, NO_MOVE, NO_MOVE}},
        {.level=9, .species=PIDGEOTTO, .moves={TACKLE, MUD_SLAP, GUST, NO_MOVE}}
    }},
};

const struct TrainerParty WhitneyGroup[] = {
    {"WHITNEY@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=18, .species=CLEFAIRY, .moves={DOUBLESLAP, MIMIC, ENCORE, METRONOME}},
        {.level=20, .species=MILTANK, .moves={ROLLOUT, ATTRACT, STOMP, MILK_DRINK}}
    }},
};

const struct TrainerParty BugsyGroup[] = {
    {"BUGSY@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=14, .species=METAPOD, .moves={TACKLE, STRING_SHOT, HARDEN, NO_MOVE}},
        {.level=14, .species=KAKUNA, .moves={POISON_STING, STRING_SHOT, HARDEN, NO_MOVE}},
        {.level=16, .species=SCYTHER, .moves={QUICK_ATTACK, LEER, FURY_CUTTER, NO_MOVE}}
    }},
};

const struct TrainerParty MortyGroup[] = {
    {"MORTY@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=21, .species=GASTLY, .moves={LICK, SPITE, MEAN_LOOK, CURSE}},
        {.level=21, .species=HAUNTER, .moves={HYPNOSIS, MIMIC, CURSE, NIGHT_SHADE}},
        {.level=25, .species=GENGAR, .moves={HYPNOSIS, SHADOW_BALL, MEAN_LOOK, DREAM_EATER}},
        {.level=23, .species=HAUNTER, .moves={SPITE, MEAN_LOOK, MIMIC, NIGHT_SHADE}}
    }},
};

const struct TrainerParty PryceGroup[] = {
    {"PRYCE@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=27, .species=SEEL, .moves={HEADBUTT, ICY_WIND, AURORA_BEAM, REST}},
        {.level=29, .species=DEWGONG, .moves={HEADBUTT, ICY_WIND, AURORA_BEAM, REST}},
        {.level=31, .species=PILOSWINE, .moves={ICY_WIND, FURY_ATTACK, MIST, BLIZZARD}}
    }},
};

const struct TrainerParty JasmineGroup[] = {
    {"JASMINE@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=MAGNEMITE, .moves={THUNDERBOLT, SUPERSONIC, SONICBOOM, THUNDER_WAVE}},
        {.level=30, .species=MAGNEMITE, .moves={THUNDERBOLT, SUPERSONIC, SONICBOOM, THUNDER_WAVE}},
        {.level=35, .species=STEELIX, .moves={SCREECH, SUNNY_DAY, ROCK_THROW, IRON_TAIL}}
    }},
};

const struct TrainerParty ChuckGroup[] = {
    {"CHUCK@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=27, .species=PRIMEAPE, .moves={LEER, RAGE, KARATE_CHOP, FURY_SWIPES}},
        {.level=30, .species=POLIWRATH, .moves={HYPNOSIS, MIND_READER, SURF, DYNAMICPUNCH}}
    }},
};

const struct TrainerParty ClairGroup[] = {
    {"CLAIR@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=37, .species=DRAGONAIR, .moves={THUNDER_WAVE, SURF, SLAM, DRAGONBREATH}},
        {.level=37, .species=DRAGONAIR, .moves={THUNDER_WAVE, THUNDERBOLT, SLAM, DRAGONBREATH}},
        {.level=37, .species=DRAGONAIR, .moves={THUNDER_WAVE, ICE_BEAM, SLAM, DRAGONBREATH}},
        {.level=40, .species=KINGDRA, .moves={SMOKESCREEN, SURF, HYPER_BEAM, DRAGONBREATH}}
    }},
};

const struct TrainerParty Rival1Group[] = {
    {"?@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=5, .species=CHIKORITA}
    }},
    {"?@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=5, .species=CYNDAQUIL}
    }},
    {"?@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=5, .species=TOTODILE}
    }},
    {"?@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=12, .species=GASTLY},
        {.level=14, .species=ZUBAT},
        {.level=16, .species=BAYLEEF}
    }},
    {"?@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=12, .species=GASTLY},
        {.level=14, .species=ZUBAT},
        {.level=16, .species=QUILAVA}
    }},
    {"?@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=12, .species=GASTLY},
        {.level=14, .species=ZUBAT},
        {.level=16, .species=CROCONAW}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=20, .species=HAUNTER, .moves={LICK, SPITE, MEAN_LOOK, CURSE}},
        {.level=18, .species=MAGNEMITE, .moves={TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM}},
        {.level=20, .species=ZUBAT, .moves={LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY}},
        {.level=22, .species=BAYLEEF, .moves={GROWL, REFLECT, RAZOR_LEAF, POISONPOWDER}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=20, .species=HAUNTER, .moves={LICK, SPITE, MEAN_LOOK, CURSE}},
        {.level=18, .species=MAGNEMITE, .moves={TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM}},
        {.level=20, .species=ZUBAT, .moves={LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY}},
        {.level=22, .species=QUILAVA, .moves={LEER, SMOKESCREEN, EMBER, QUICK_ATTACK}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=20, .species=HAUNTER, .moves={LICK, SPITE, MEAN_LOOK, CURSE}},
        {.level=18, .species=MAGNEMITE, .moves={TACKLE, THUNDERSHOCK, SUPERSONIC, SONICBOOM}},
        {.level=20, .species=ZUBAT, .moves={LEECH_LIFE, SUPERSONIC, BITE, CONFUSE_RAY}},
        {.level=22, .species=CROCONAW, .moves={LEER, RAGE, WATER_GUN, BITE}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=28, .species=MAGNEMITE, .moves={TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE}},
        {.level=30, .species=HAUNTER, .moves={LICK, MEAN_LOOK, CURSE, SHADOW_BALL}},
        {.level=32, .species=SNEASEL, .moves={LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK}},
        {.level=32, .species=MEGANIUM, .moves={REFLECT, RAZOR_LEAF, POISONPOWDER, BODY_SLAM}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=28, .species=MAGNEMITE, .moves={TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE}},
        {.level=30, .species=HAUNTER, .moves={LICK, MEAN_LOOK, CURSE, SHADOW_BALL}},
        {.level=32, .species=SNEASEL, .moves={LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK}},
        {.level=32, .species=QUILAVA, .moves={SMOKESCREEN, EMBER, QUICK_ATTACK, FLAME_WHEEL}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=28, .species=MAGNEMITE, .moves={TACKLE, THUNDERSHOCK, SONICBOOM, THUNDER_WAVE}},
        {.level=30, .species=HAUNTER, .moves={LICK, MEAN_LOOK, CURSE, SHADOW_BALL}},
        {.level=32, .species=SNEASEL, .moves={LEER, QUICK_ATTACK, SCREECH, FAINT_ATTACK}},
        {.level=32, .species=FERALIGATR, .moves={RAGE, WATER_GUN, BITE, SCARY_FACE}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=34, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=36, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=35, .species=MAGNETON, .moves={THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=35, .species=HAUNTER, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=35, .species=KADABRA, .moves={DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT}},
        {.level=38, .species=MEGANIUM, .moves={REFLECT, RAZOR_LEAF, POISONPOWDER, BODY_SLAM}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=34, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=36, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=35, .species=MAGNETON, .moves={THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=35, .species=HAUNTER, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=35, .species=KADABRA, .moves={DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT}},
        {.level=38, .species=TYPHLOSION, .moves={SMOKESCREEN, EMBER, QUICK_ATTACK, FLAME_WHEEL}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=34, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=36, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=34, .species=MAGNETON, .moves={THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=35, .species=HAUNTER, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=35, .species=KADABRA, .moves={DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT}},
        {.level=38, .species=FERALIGATR, .moves={RAGE, WATER_GUN, SCARY_FACE, SLASH}}
    }},
};

const struct TrainerParty PokemonProfGroup[] = {
    // VS complains about empty arrays, so there is a dummy item here.
    {"DUMMY@", TRAINERTYPE_NORMAL, .size=0, .pnormal=NULL},
};

const struct TrainerParty WillGroup[] = {
    {"WILL@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=40, .species=XATU, .moves={QUICK_ATTACK, FUTURE_SIGHT, CONFUSE_RAY, PSYCHIC_M}},
        {.level=41, .species=JYNX, .moves={DOUBLESLAP, LOVELY_KISS, ICE_PUNCH, PSYCHIC_M}},
        {.level=41, .species=EXEGGUTOR, .moves={REFLECT, LEECH_SEED, EGG_BOMB, PSYCHIC_M}},
        {.level=41, .species=SLOWBRO, .moves={CURSE, AMNESIA, BODY_SLAM, PSYCHIC_M}},
        {.level=42, .species=XATU, .moves={QUICK_ATTACK, FUTURE_SIGHT, CONFUSE_RAY, PSYCHIC_M}}
    }},
};

const struct TrainerParty PKMNTrainerGroup[] = {
    {"CAL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=CHIKORITA},
        {.level=10, .species=CYNDAQUIL},
        {.level=10, .species=TOTODILE}
    }},
    {"CAL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=BAYLEEF},
        {.level=30, .species=QUILAVA},
        {.level=30, .species=CROCONAW}
    }},
    {"CAL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=50, .species=MEGANIUM},
        {.level=50, .species=TYPHLOSION},
        {.level=50, .species=FERALIGATR}
    }},
};

const struct TrainerParty BrunoGroup[] = {
    {"BRUNO@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=42, .species=HITMONTOP, .moves={PURSUIT, QUICK_ATTACK, DIG, DETECT}},
        {.level=42, .species=HITMONLEE, .moves={SWAGGER, DOUBLE_KICK, HI_JUMP_KICK, FORESIGHT}},
        {.level=42, .species=HITMONCHAN, .moves={THUNDERPUNCH, ICE_PUNCH, FIRE_PUNCH, MACH_PUNCH}},
        {.level=43, .species=ONIX, .moves={BIND, EARTHQUAKE, SANDSTORM, ROCK_SLIDE}},
        {.level=46, .species=MACHAMP, .moves={ROCK_SLIDE, FORESIGHT, VITAL_THROW, CROSS_CHOP}}
    }},
};

const struct TrainerParty KarenGroup[] = {
    {"KAREN@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=42, .species=UMBREON, .moves={SAND_ATTACK, CONFUSE_RAY, FAINT_ATTACK, MEAN_LOOK}},
        {.level=42, .species=VILEPLUME, .moves={STUN_SPORE, ACID, MOONLIGHT, PETAL_DANCE}},
        {.level=45, .species=GENGAR, .moves={LICK, SPITE, CURSE, DESTINY_BOND}},
        {.level=44, .species=MURKROW, .moves={QUICK_ATTACK, WHIRLWIND, PURSUIT, FAINT_ATTACK}},
        {.level=47, .species=HOUNDOOM, .moves={ROAR, PURSUIT, FLAMETHROWER, CRUNCH}}
    }},
};

const struct TrainerParty KogaGroup[] = {
    {"KOGA@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=40, .species=ARIADOS, .moves={DOUBLE_TEAM, SPIDER_WEB, BATON_PASS, GIGA_DRAIN}},
        {.level=41, .species=VENOMOTH, .moves={SUPERSONIC, GUST, PSYCHIC_M, TOXIC}},
        {.level=43, .species=FORRETRESS, .moves={PROTECT, SWIFT, EXPLOSION, SPIKES}},
        {.level=42, .species=MUK, .moves={MINIMIZE, ACID_ARMOR, SLUDGE_BOMB, TOXIC}},
        {.level=44, .species=CROBAT, .moves={DOUBLE_TEAM, QUICK_ATTACK, WING_ATTACK, TOXIC}}
    }},
};

const struct TrainerParty ChampionGroup[] = {
    {"LANCE@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=44, .species=GYARADOS, .moves={FLAIL, RAIN_DANCE, SURF, HYPER_BEAM}},
        {.level=47, .species=DRAGONITE, .moves={THUNDER_WAVE, TWISTER, THUNDER, HYPER_BEAM}},
        {.level=47, .species=DRAGONITE, .moves={THUNDER_WAVE, TWISTER, BLIZZARD, HYPER_BEAM}},
        {.level=46, .species=AERODACTYL, .moves={WING_ATTACK, ANCIENTPOWER, ROCK_SLIDE, HYPER_BEAM}},
        {.level=46, .species=CHARIZARD, .moves={FLAMETHROWER, WING_ATTACK, SLASH, HYPER_BEAM}},
        {.level=50, .species=DRAGONITE, .moves={FIRE_BLAST, SAFEGUARD, OUTRAGE, HYPER_BEAM}}
    }},
};

const struct TrainerParty BrockGroup[] = {
    {"BROCK@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=41, .species=GRAVELER, .moves={DEFENSE_CURL, ROCK_SLIDE, ROLLOUT, EARTHQUAKE}},
        {.level=41, .species=RHYHORN, .moves={FURY_ATTACK, SCARY_FACE, EARTHQUAKE, HORN_DRILL}},
        {.level=42, .species=OMASTAR, .moves={BITE, SURF, PROTECT, SPIKE_CANNON}},
        {.level=44, .species=ONIX, .moves={BIND, ROCK_SLIDE, BIDE, SANDSTORM}},
        {.level=42, .species=KABUTOPS, .moves={SLASH, SURF, ENDURE, GIGA_DRAIN}}
    }},
};

const struct TrainerParty MistyGroup[] = {
    {"MISTY@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=42, .species=GOLDUCK, .moves={SURF, DISABLE, PSYCH_UP, PSYCHIC_M}},
        {.level=42, .species=QUAGSIRE, .moves={SURF, AMNESIA, EARTHQUAKE, RAIN_DANCE}},
        {.level=44, .species=LAPRAS, .moves={SURF, PERISH_SONG, BLIZZARD, RAIN_DANCE}},
        {.level=47, .species=STARMIE, .moves={SURF, CONFUSE_RAY, RECOVER, ICE_BEAM}}
    }},
};

const struct TrainerParty LtSurgeGroup[] = {
    {"LT.SURGE@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=44, .species=RAICHU, .moves={THUNDER_WAVE, QUICK_ATTACK, THUNDERBOLT, THUNDER}},
        {.level=40, .species=ELECTRODE, .moves={SCREECH, DOUBLE_TEAM, SWIFT, EXPLOSION}},
        {.level=40, .species=MAGNETON, .moves={LOCK_ON, DOUBLE_TEAM, SWIFT, ZAP_CANNON}},
        {.level=40, .species=ELECTRODE, .moves={SCREECH, DOUBLE_TEAM, SWIFT, EXPLOSION}},
        {.level=46, .species=ELECTABUZZ, .moves={QUICK_ATTACK, THUNDERPUNCH, LIGHT_SCREEN, THUNDER}}
    }},
};

const struct TrainerParty ScientistGroup[] = {
    {"ROSS@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=KOFFING},
        {.level=22, .species=KOFFING}
    }},
    {"MITCH@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=DITTO}
    }},
    {"JED@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=MAGNEMITE},
        {.level=20, .species=MAGNEMITE},
        {.level=20, .species=MAGNEMITE}
    }},
    {"MARC@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=MAGNEMITE},
        {.level=27, .species=MAGNEMITE},
        {.level=27, .species=MAGNEMITE}
    }},
    {"RICH@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=PORYGON, .moves={CONVERSION, CONVERSION2, RECOVER, TRI_ATTACK}}
    }},
};

const struct TrainerParty ErikaGroup[] = {
    {"ERIKA@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=42, .species=TANGELA, .moves={VINE_WHIP, BIND, GIGA_DRAIN, SLEEP_POWDER}},
        {.level=41, .species=JUMPLUFF, .moves={MEGA_DRAIN, LEECH_SEED, COTTON_SPORE, GIGA_DRAIN}},
        {.level=46, .species=VICTREEBEL, .moves={SUNNY_DAY, SYNTHESIS, ACID, RAZOR_LEAF}},
        {.level=46, .species=BELLOSSOM, .moves={SUNNY_DAY, SYNTHESIS, PETAL_DANCE, SOLARBEAM}}
    }},
};

const struct TrainerParty YoungsterGroup[] = {
    {"JOEY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=4, .species=RATTATA}
    }},
    {"MIKEY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=2, .species=PIDGEY},
        {.level=4, .species=RATTATA}
    }},
    {"ALBERT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=6, .species=RATTATA},
        {.level=8, .species=ZUBAT}
    }},
    {"GORDON@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=WOOPER}
    }},
    {"SAMUEL@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=7, .species=RATTATA},
        {.level=10, .species=SANDSHREW},
        {.level=8, .species=SPEAROW},
        {.level=8, .species=SPEAROW}
    }},
    {"IAN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=MANKEY},
        {.level=12, .species=DIGLETT}
    }},
    {"JOEY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=RATTATA}
    }},
    {"JOEY@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=21, .species=RATICATE, .moves={TAIL_WHIP, QUICK_ATTACK, HYPER_FANG, SCARY_FACE}}
    }},
    {"WARREN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=FEAROW}
    }},
    {"JIMMY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=RATICATE},
        {.level=33, .species=ARBOK}
    }},
    {"OWEN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=GROWLITHE}
    }},
    {"JASON@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=SANDSLASH},
        {.level=33, .species=CROBAT}
    }},
    {"JOEY@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=RATICATE, .moves={TAIL_WHIP, QUICK_ATTACK, HYPER_FANG, PURSUIT}}
    }},
    {"JOEY@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=37, .species=RATICATE, .moves={HYPER_BEAM, QUICK_ATTACK, HYPER_FANG, PURSUIT}}
    }},
};

const struct TrainerParty SchoolboyGroup[] = {
    {"JACK@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=12, .species=ODDISH},
        {.level=15, .species=VOLTORB}
    }},
    {"KIPP@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=VOLTORB},
        {.level=27, .species=MAGNEMITE},
        {.level=31, .species=VOLTORB},
        {.level=31, .species=MAGNETON}
    }},
    {"ALAN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=TANGELA}
    }},
    {"JOHNNY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=BELLSPROUT},
        {.level=31, .species=WEEPINBELL},
        {.level=33, .species=VICTREEBEL}
    }},
    {"DANNY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=JYNX},
        {.level=31, .species=ELECTABUZZ},
        {.level=31, .species=MAGMAR}
    }},
    {"TOMMY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=XATU},
        {.level=34, .species=ALAKAZAM}
    }},
    {"DUDLEY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=ODDISH}
    }},
    {"JOE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=TANGELA},
        {.level=33, .species=VAPOREON}
    }},
    {"BILLY@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=PARAS},
        {.level=27, .species=PARAS},
        {.level=27, .species=POLIWHIRL},
        {.level=35, .species=DITTO}
    }},
    {"CHAD@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=MR__MIME}
    }},
    {"NATE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=LEDIAN},
        {.level=32, .species=EXEGGUTOR}
    }},
    {"RICKY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=AIPOM},
        {.level=32, .species=DITTO}
    }},
    {"JACK@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=14, .species=ODDISH},
        {.level=17, .species=VOLTORB}
    }},
    {"JACK@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=GLOOM},
        {.level=31, .species=ELECTRODE}
    }},
    {"ALAN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=TANGELA},
        {.level=17, .species=YANMA}
    }},
    {"ALAN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=NATU},
        {.level=22, .species=TANGELA},
        {.level=20, .species=QUAGSIRE},
        {.level=25, .species=YANMA}
    }},
    {"CHAD@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=MR__MIME},
        {.level=19, .species=MAGNEMITE}
    }},
    {"CHAD@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=MR__MIME},
        {.level=31, .species=MAGNETON}
    }},
    {"JACK@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=GLOOM},
        {.level=33, .species=GROWLITHE},
        {.level=33, .species=ELECTRODE}
    }},
    {"JACK@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=35, .species=ELECTRODE, .moves={SCREECH, SONICBOOM, ROLLOUT, LIGHT_SCREEN}},
        {.level=35, .species=GROWLITHE, .moves={SUNNY_DAY, LEER, TAKE_DOWN, FLAME_WHEEL}},
        {.level=37, .species=VILEPLUME, .moves={SOLARBEAM, SLEEP_POWDER, ACID, MOONLIGHT}}
    }},
    {"ALAN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=NATU},
        {.level=27, .species=TANGELA},
        {.level=30, .species=QUAGSIRE},
        {.level=30, .species=YANMA}
    }},
    {"ALAN@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=35, .species=XATU, .moves={PECK, NIGHT_SHADE, SWIFT, FUTURE_SIGHT}},
        {.level=32, .species=TANGELA, .moves={POISONPOWDER, VINE_WHIP, BIND, MEGA_DRAIN}},
        {.level=32, .species=YANMA, .moves={QUICK_ATTACK, DOUBLE_TEAM, SONICBOOM, SUPERSONIC}},
        {.level=35, .species=QUAGSIRE, .moves={TAIL_WHIP, SLAM, AMNESIA, EARTHQUAKE}}
    }},
    {"CHAD@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=MR__MIME},
        {.level=34, .species=MAGNETON}
    }},
    {"CHAD@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=34, .species=MR__MIME, .moves={PSYCHIC_M, LIGHT_SCREEN, REFLECT, ENCORE}},
        {.level=38, .species=MAGNETON, .moves={ZAP_CANNON, THUNDER_WAVE, LOCK_ON, SWIFT}}
    }},
};

const struct TrainerParty BirdKeeperGroup[] = {
    {"ROD@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=7, .species=PIDGEY},
        {.level=7, .species=PIDGEY}
    }},
    {"ABE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=SPEAROW}
    }},
    {"BRYAN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=12, .species=PIDGEY},
        {.level=14, .species=PIDGEOTTO}
    }},
    {"THEO@", TRAINERTYPE_NORMAL, .size=5, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=PIDGEY},
        {.level=15, .species=PIDGEY},
        {.level=19, .species=PIDGEY},
        {.level=15, .species=PIDGEY},
        {.level=15, .species=PIDGEY}
    }},
    {"TOBY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=DODUO},
        {.level=16, .species=DODUO},
        {.level=17, .species=DODUO}
    }},
    {"DENIS@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=SPEAROW},
        {.level=20, .species=FEAROW},
        {.level=18, .species=SPEAROW}
    }},
    {"VANCE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=PIDGEOTTO},
        {.level=25, .species=PIDGEOTTO}
    }},
    {"HANK@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=12, .species=PIDGEY},
        {.level=34, .species=PIDGEOT}
    }},
    {"ROY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=FEAROW},
        {.level=35, .species=FEAROW}
    }},
    {"BORIS@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=DODUO},
        {.level=28, .species=DODUO},
        {.level=32, .species=DODRIO}
    }},
    {"BOB@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=NOCTOWL}
    }},
    {"JOSE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=36, .species=FARFETCH_D}
    }},
    {"PETER@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=6, .species=PIDGEY},
        {.level=6, .species=PIDGEY},
        {.level=8, .species=SPEAROW}
    }},
    {"JOSE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=FARFETCH_D}
    }},
    {"PERRY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=FARFETCH_D}
    }},
    {"BRET@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=PIDGEOTTO},
        {.level=32, .species=FEAROW}
    }},
    {"JOSE@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=40, .species=FARFETCH_D, .moves={FURY_ATTACK, DETECT, FLY, SLASH}}
    }},
    {"VANCE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=PIDGEOTTO},
        {.level=32, .species=PIDGEOTTO}
    }},
    {"VANCE@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=38, .species=PIDGEOT, .moves={TOXIC, QUICK_ATTACK, WHIRLWIND, FLY}},
        {.level=38, .species=PIDGEOT, .moves={SWIFT, DETECT, STEEL_WING, FLY}}
    }},
};

const struct TrainerParty LassGroup[] = {
    {"CARRIE@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=18, .species=SNUBBULL, .moves={SCARY_FACE, CHARM, BITE, LICK}}
    }},
    {"BRIDGET@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=JIGGLYPUFF},
        {.level=15, .species=JIGGLYPUFF},
        {.level=15, .species=JIGGLYPUFF}
    }},
    {"ALICE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=GLOOM},
        {.level=34, .species=ARBOK},
        {.level=30, .species=GLOOM}
    }},
    {"KRISE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=12, .species=ODDISH},
        {.level=15, .species=CUBONE}
    }},
    {"CONNIE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=21, .species=MARILL}
    }},
    {"LINDA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=BULBASAUR},
        {.level=32, .species=IVYSAUR},
        {.level=34, .species=VENUSAUR}
    }},
    {"LAURA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=GLOOM},
        {.level=31, .species=PIDGEOTTO},
        {.level=31, .species=BELLOSSOM}
    }},
    {"SHANNON@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=PARAS},
        {.level=29, .species=PARAS},
        {.level=32, .species=PARASECT}
    }},
    {"MICHELLE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=SKIPLOOM},
        {.level=33, .species=HOPPIP},
        {.level=34, .species=JUMPLUFF}
    }},
    {"DANA@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=18, .species=FLAAFFY, .moves={TACKLE, GROWL, THUNDERSHOCK, THUNDER_WAVE}},
        {.level=18, .species=PSYDUCK, .moves={SCRATCH, TAIL_WHIP, DISABLE, CONFUSION}}
    }},
    {"ELLEN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=WIGGLYTUFF},
        {.level=34, .species=GRANBULL}
    }},
    {"CONNIE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=21, .species=MARILL}
    }},
    {"CONNIE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=21, .species=MARILL}
    }},
    {"DANA@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=21, .species=FLAAFFY, .moves={TACKLE, GROWL, THUNDERSHOCK, THUNDER_WAVE}},
        {.level=21, .species=PSYDUCK, .moves={SCRATCH, TAIL_WHIP, DISABLE, CONFUSION}}
    }},
    {"DANA@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=29, .species=PSYDUCK, .moves={SCRATCH, DISABLE, CONFUSION, SCREECH}},
        {.level=29, .species=AMPHAROS, .moves={TACKLE, THUNDERSHOCK, THUNDER_WAVE, COTTON_SPORE}}
    }},
    {"DANA@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=32, .species=PSYDUCK, .moves={SCRATCH, DISABLE, CONFUSION, SCREECH}},
        {.level=32, .species=AMPHAROS, .moves={TACKLE, THUNDERPUNCH, THUNDER_WAVE, COTTON_SPORE}}
    }},
    {"DANA@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=36, .species=AMPHAROS, .moves={SWIFT, THUNDERPUNCH, THUNDER_WAVE, COTTON_SPORE}},
        {.level=36, .species=GOLDUCK, .moves={DISABLE, SURF, PSYCHIC_M, SCREECH}}
    }},
};

const struct TrainerParty JanineGroup[] = {
    {"JANINE@", TRAINERTYPE_MOVES, .size=5, .pmoves=(struct TrainerPartyMoves[]){
        {.level=36, .species=CROBAT, .moves={SCREECH, SUPERSONIC, CONFUSE_RAY, WING_ATTACK}},
        {.level=36, .species=WEEZING, .moves={SMOG, SLUDGE_BOMB, TOXIC, EXPLOSION}},
        {.level=36, .species=WEEZING, .moves={SMOG, SLUDGE_BOMB, TOXIC, EXPLOSION}},
        {.level=33, .species=ARIADOS, .moves={SCARY_FACE, GIGA_DRAIN, STRING_SHOT, NIGHT_SHADE}},
        {.level=39, .species=VENOMOTH, .moves={FORESIGHT, DOUBLE_TEAM, GUST, PSYCHIC_M}}
    }},
};

const struct TrainerParty CooltrainerMGroup[] = {
    {"NICK@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=26, .species=CHARMANDER, .moves={EMBER, SMOKESCREEN, RAGE, SCARY_FACE}},
        {.level=26, .species=SQUIRTLE, .moves={WITHDRAW, WATER_GUN, BITE, CURSE}},
        {.level=26, .species=BULBASAUR, .moves={LEECH_SEED, POISONPOWDER, SLEEP_POWDER, RAZOR_LEAF}}
    }},
    {"AARON@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=IVYSAUR},
        {.level=24, .species=CHARMELEON},
        {.level=24, .species=WARTORTLE}
    }},
    {"PAUL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=DRATINI},
        {.level=34, .species=DRATINI},
        {.level=34, .species=DRATINI}
    }},
    {"CODY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=HORSEA},
        {.level=36, .species=SEADRA}
    }},
    {"MIKE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=37, .species=DRAGONAIR}
    }},
    {"GAVEN@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=35, .species=VICTREEBEL, .moves={WRAP, TOXIC, ACID, RAZOR_LEAF}},
        {.level=35, .species=KINGLER, .moves={BUBBLEBEAM, STOMP, GUILLOTINE, PROTECT}},
        {.level=35, .species=FLAREON, .moves={SAND_ATTACK, QUICK_ATTACK, BITE, FIRE_SPIN}}
    }},
    {"GAVEN@", TRAINERTYPE_ITEM_MOVES, .size=3, .pitemmoves=(struct TrainerPartyItemMoves[]){
        {.level=39, .species=VICTREEBEL, .item=NO_ITEM, .moves={GIGA_DRAIN, TOXIC, SLUDGE_BOMB, RAZOR_LEAF}},
        {.level=39, .species=KINGLER, .item=KINGS_ROCK, .moves={SURF, STOMP, GUILLOTINE, BLIZZARD}},
        {.level=39, .species=FLAREON, .item=NO_ITEM, .moves={FLAMETHROWER, QUICK_ATTACK, BITE, FIRE_SPIN}}
    }},
    {"RYAN@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=25, .species=PIDGEOT, .moves={SAND_ATTACK, QUICK_ATTACK, WHIRLWIND, WING_ATTACK}},
        {.level=27, .species=ELECTABUZZ, .moves={THUNDERPUNCH, LIGHT_SCREEN, SWIFT, SCREECH}}
    }},
    {"JAKE@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=33, .species=PARASECT, .moves={LEECH_LIFE, SPORE, SLASH, SWORDS_DANCE}},
        {.level=35, .species=GOLDUCK, .moves={CONFUSION, SCREECH, PSYCH_UP, FURY_SWIPES}}
    }},
    {"GAVEN@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=32, .species=VICTREEBEL, .moves={WRAP, TOXIC, ACID, RAZOR_LEAF}},
        {.level=32, .species=KINGLER, .moves={BUBBLEBEAM, STOMP, GUILLOTINE, PROTECT}},
        {.level=32, .species=FLAREON, .moves={SAND_ATTACK, QUICK_ATTACK, BITE, FIRE_SPIN}}
    }},
    {"BLAKE@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=33, .species=MAGNETON, .moves={THUNDERBOLT, SUPERSONIC, SWIFT, SCREECH}},
        {.level=31, .species=QUAGSIRE, .moves={WATER_GUN, SLAM, AMNESIA, EARTHQUAKE}},
        {.level=31, .species=EXEGGCUTE, .moves={LEECH_SEED, CONFUSION, SLEEP_POWDER, SOLARBEAM}}
    }},
    {"BRIAN@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=35, .species=SANDSLASH, .moves={SAND_ATTACK, POISON_STING, SLASH, SWIFT}}
    }},
    {"ERICK@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=BULBASAUR},
        {.level=10, .species=CHARMANDER},
        {.level=10, .species=SQUIRTLE}
    }},
    {"ANDY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=BULBASAUR},
        {.level=10, .species=CHARMANDER},
        {.level=10, .species=SQUIRTLE}
    }},
    {"TYLER@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=BULBASAUR},
        {.level=10, .species=CHARMANDER},
        {.level=10, .species=SQUIRTLE}
    }},
    {"SEAN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=FLAREON},
        {.level=35, .species=TANGELA},
        {.level=35, .species=TAUROS}
    }},
    {"KEVIN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=38, .species=RHYHORN},
        {.level=35, .species=CHARMELEON},
        {.level=35, .species=WARTORTLE}
    }},
    {"STEVE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=14, .species=BULBASAUR},
        {.level=14, .species=CHARMANDER},
        {.level=14, .species=SQUIRTLE}
    }},
    {"ALLEN@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=27, .species=CHARMELEON, .moves={EMBER, SMOKESCREEN, RAGE, SCARY_FACE}}
    }},
    {"DARIN@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=37, .species=DRAGONAIR, .moves={WRAP, SURF, DRAGON_RAGE, SLAM}}
    }},
};

const struct TrainerParty CooltrainerFGroup[] = {
    {"GWEN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=EEVEE},
        {.level=22, .species=FLAREON},
        {.level=22, .species=VAPOREON},
        {.level=22, .species=JOLTEON}
    }},
    {"LOIS@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=25, .species=SKIPLOOM, .moves={SYNTHESIS, POISONPOWDER, MEGA_DRAIN, LEECH_SEED}},
        {.level=25, .species=NINETALES, .moves={EMBER, QUICK_ATTACK, CONFUSE_RAY, SAFEGUARD}}
    }},
    {"FRAN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=37, .species=SEADRA}
    }},
    {"LOLA@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=DRATINI},
        {.level=36, .species=DRAGONAIR}
    }},
    {"KATE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=SHELLDER},
        {.level=28, .species=CLOYSTER}
    }},
    {"IRENE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=GOLDEEN},
        {.level=24, .species=SEAKING}
    }},
    {"KELLY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=MARILL},
        {.level=24, .species=WARTORTLE},
        {.level=24, .species=WARTORTLE}
    }},
    {"JOYCE@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=36, .species=PIKACHU, .moves={QUICK_ATTACK, DOUBLE_TEAM, THUNDERBOLT, THUNDER}},
        {.level=32, .species=BLASTOISE, .moves={BITE, CURSE, SURF, RAIN_DANCE}}
    }},
    {"BETH@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=36, .species=RAPIDASH, .moves={STOMP, FIRE_SPIN, FURY_ATTACK, AGILITY}}
    }},
    {"REENA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=STARMIE},
        {.level=33, .species=NIDOQUEEN},
        {.level=31, .species=STARMIE}
    }},
    {"MEGAN@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=32, .species=BULBASAUR, .moves={GROWL, LEECH_SEED, POISONPOWDER, RAZOR_LEAF}},
        {.level=32, .species=IVYSAUR, .moves={GROWL, LEECH_SEED, POISONPOWDER, RAZOR_LEAF}},
        {.level=32, .species=VENUSAUR, .moves={BODY_SLAM, SLEEP_POWDER, RAZOR_LEAF, SWEET_SCENT}}
    }},
    {"BETH@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=39, .species=RAPIDASH, .moves={STOMP, FIRE_SPIN, FURY_ATTACK, AGILITY}}
    }},
    {"CAROL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=ELECTRODE},
        {.level=35, .species=STARMIE},
        {.level=35, .species=NINETALES}
    }},
    {"QUINN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=38, .species=IVYSAUR},
        {.level=38, .species=STARMIE}
    }},
    {"EMMA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=POLIWHIRL}
    }},
    {"CYBIL@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=25, .species=BUTTERFREE, .moves={CONFUSION, SLEEP_POWDER, WHIRLWIND, GUST}},
        {.level=25, .species=BELLOSSOM, .moves={ABSORB, STUN_SPORE, ACID, SOLARBEAM}}
    }},
    {"JENN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=STARYU},
        {.level=26, .species=STARMIE}
    }},
    {"BETH@", TRAINERTYPE_ITEM_MOVES, .size=1, .pitemmoves=(struct TrainerPartyItemMoves[]){
        {.level=43, .species=RAPIDASH, .item=FOCUS_BAND, .moves={STOMP, FIRE_SPIN, FURY_ATTACK, FIRE_BLAST}}
    }},
    {"REENA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=STARMIE},
        {.level=36, .species=NIDOQUEEN},
        {.level=34, .species=STARMIE}
    }},
    {"REENA@", TRAINERTYPE_ITEM_MOVES, .size=3, .pitemmoves=(struct TrainerPartyItemMoves[]){
        {.level=38, .species=STARMIE, .item=NO_ITEM, .moves={DOUBLE_TEAM, PSYCHIC_M, WATERFALL, CONFUSE_RAY}},
        {.level=40, .species=NIDOQUEEN, .item=PINK_BOW, .moves={EARTHQUAKE, DOUBLE_KICK, TOXIC, BODY_SLAM}},
        {.level=38, .species=STARMIE, .item=NO_ITEM, .moves={BLIZZARD, PSYCHIC_M, WATERFALL, RECOVER}}
    }},
    {"CARA@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=33, .species=HORSEA, .moves={SMOKESCREEN, LEER, WHIRLPOOL, TWISTER}},
        {.level=33, .species=HORSEA, .moves={SMOKESCREEN, LEER, WHIRLPOOL, TWISTER}},
        {.level=35, .species=SEADRA, .moves={SWIFT, LEER, WATERFALL, TWISTER}}
    }},
};

const struct TrainerParty BeautyGroup[] = {
    {"VICTORIA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=SENTRET},
        {.level=13, .species=SENTRET},
        {.level=17, .species=SENTRET}
    }},
    {"SAMANTHA@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=16, .species=MEOWTH, .moves={SCRATCH, GROWL, BITE, PAY_DAY}},
        {.level=16, .species=MEOWTH, .moves={SCRATCH, GROWL, BITE, SLASH}}
    }},
    {"JULIE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"JACLYN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"BRENDA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=FURRET}
    }},
    {"CASSIE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=VILEPLUME},
        {.level=34, .species=BUTTERFREE}
    }},
    {"CAROLINE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=MARILL},
        {.level=32, .species=SEEL},
        {.level=30, .species=MARILL}
    }},
    {"CARLENE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"JESSICA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"RACHAEL@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"ANGELICA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"KENDRA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"VERONICA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"JULIA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=PARAS},
        {.level=32, .species=EXEGGCUTE},
        {.level=35, .species=PARASECT}
    }},
    {"THERESA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=SENTRET}
    }},
    {"VALERIE@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=17, .species=HOPPIP, .moves={SYNTHESIS, TAIL_WHIP, TACKLE, POISONPOWDER}},
        {.level=17, .species=SKIPLOOM, .moves={SYNTHESIS, TAIL_WHIP, TACKLE, STUN_SPORE}}
    }},
    {"OLIVIA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=CORSOLA}
    }},
};

const struct TrainerParty PokemaniacGroup[] = {
    {"LARRY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=SLOWPOKE}
    }},
    {"ANDREW@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=MAROWAK},
        {.level=24, .species=MAROWAK}
    }},
    {"CALVIN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=KANGASKHAN}
    }},
    {"SHANE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=NIDORINA},
        {.level=16, .species=NIDORINO}
    }},
    {"BEN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=SLOWBRO}
    }},
    {"BRENT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=LICKITUNG}
    }},
    {"RON@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=NIDOKING}
    }},
    {"ETHAN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=RHYHORN},
        {.level=31, .species=RHYDON}
    }},
    {"BRENT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=KANGASKHAN}
    }},
    {"BRENT@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=36, .species=PORYGON, .moves={RECOVER, PSYCHIC_M, CONVERSION2, TRI_ATTACK}}
    }},
    {"ISSAC@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=12, .species=LICKITUNG, .moves={LICK, SUPERSONIC, CUT, NO_MOVE}}
    }},
    {"DONALD@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=SLOWPOKE},
        {.level=10, .species=SLOWPOKE}
    }},
    {"ZACH@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=RHYHORN}
    }},
    {"BRENT@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=41, .species=CHANSEY, .moves={ROLLOUT, ATTRACT, EGG_BOMB, SOFTBOILED}}
    }},
    {"MILLER@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=NIDOKING},
        {.level=17, .species=NIDOQUEEN}
    }},
};

const struct TrainerParty GruntMGroup[] = {
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=14, .species=KOFFING}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=7, .species=RATTATA},
        {.level=9, .species=ZUBAT},
        {.level=9, .species=ZUBAT}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=RATICATE},
        {.level=24, .species=RATICATE}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=GRIMER},
        {.level=23, .species=GRIMER},
        {.level=25, .species=MUK}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=5, .pnormal=(struct TrainerPartyNormal[]){
        {.level=21, .species=RATTATA},
        {.level=21, .species=RATTATA},
        {.level=23, .species=RATTATA},
        {.level=23, .species=RATTATA},
        {.level=23, .species=RATTATA}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=ZUBAT},
        {.level=26, .species=ZUBAT}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=KOFFING},
        {.level=23, .species=GRIMER},
        {.level=23, .species=ZUBAT},
        {.level=23, .species=RATTATA}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=WEEZING}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=RATICATE},
        {.level=26, .species=KOFFING}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=ZUBAT},
        {.level=24, .species=GOLBAT},
        {.level=22, .species=GRIMER}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=MUK},
        {.level=23, .species=KOFFING},
        {.level=25, .species=RATTATA}
    }},
    {"EXECUTIVE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=HOUNDOUR}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=RATTATA}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=RATICATE},
        {.level=24, .species=GOLBAT}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=GRIMER},
        {.level=23, .species=WEEZING}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=RATTATA},
        {.level=16, .species=RATTATA},
        {.level=16, .species=RATTATA},
        {.level=16, .species=RATTATA}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=GOLBAT}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=RATTATA},
        {.level=17, .species=ZUBAT},
        {.level=17, .species=RATTATA}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=VENONAT},
        {.level=18, .species=VENONAT}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=DROWZEE},
        {.level=19, .species=ZUBAT}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=ZUBAT},
        {.level=17, .species=GRIMER},
        {.level=18, .species=RATTATA}
    }},
    {"EXECUTIVE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=36, .species=GOLBAT}
    }},
    {"EXECUTIVE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=KOFFING}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=KOFFING},
        {.level=25, .species=KOFFING}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=KOFFING},
        {.level=24, .species=MUK}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=RATTATA},
        {.level=15, .species=RATTATA}
    }},
    {"EXECUTIVE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=ZUBAT}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=RATICATE}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=RATTATA},
        {.level=9, .species=RATTATA}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=GOLBAT},
        {.level=25, .species=GOLBAT},
        {.level=30, .species=ARBOK}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=GOLBAT}
    }},
};

const struct TrainerParty GentlemanGroup[] = {
    {"PRESTON@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=GROWLITHE},
        {.level=18, .species=GROWLITHE}
    }},
    {"EDWARD@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=PERSIAN}
    }},
    {"GREGORY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=37, .species=PIKACHU},
        {.level=33, .species=FLAAFFY}
    }},
    {"VIRGIL@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=PONYTA}
    }},
    {"ALFRED@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=NOCTOWL}
    }},
};

const struct TrainerParty SkierGroup[] = {
    {"ROXANNE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=JYNX}
    }},
    {"CLARISSA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=DEWGONG}
    }},
};

const struct TrainerParty TeacherGroup[] = {
    {"COLETTE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=36, .species=CLEFAIRY}
    }},
    {"HILLARY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=AIPOM},
        {.level=36, .species=CUBONE}
    }},
    {"SHIRLEY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=JIGGLYPUFF}
    }},
};

const struct TrainerParty SabrinaGroup[] = {
    {"SABRINA@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=46, .species=ESPEON, .moves={SAND_ATTACK, QUICK_ATTACK, SWIFT, PSYCHIC_M}},
        {.level=46, .species=MR__MIME, .moves={BARRIER, REFLECT, BATON_PASS, PSYCHIC_M}},
        {.level=48, .species=ALAKAZAM, .moves={RECOVER, FUTURE_SIGHT, PSYCHIC_M, REFLECT}}
    }},
};

const struct TrainerParty BugCatcherGroup[] = {
    {"DON@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=3, .species=CATERPIE},
        {.level=3, .species=CATERPIE}
    }},
    {"ROB@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=BEEDRILL},
        {.level=32, .species=BUTTERFREE}
    }},
    {"ED@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=BEEDRILL},
        {.level=30, .species=BEEDRILL},
        {.level=30, .species=BEEDRILL}
    }},
    {"WADE@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=2, .species=CATERPIE},
        {.level=2, .species=CATERPIE},
        {.level=3, .species=WEEDLE},
        {.level=2, .species=CATERPIE}
    }},
    {"BENNY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=7, .species=WEEDLE},
        {.level=9, .species=KAKUNA},
        {.level=12, .species=BEEDRILL}
    }},
    {"AL@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=12, .species=CATERPIE},
        {.level=12, .species=WEEDLE}
    }},
    {"JOSH@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=13, .species=PARAS}
    }},
    {"ARNIE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=VENONAT}
    }},
    {"KEN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=ARIADOS},
        {.level=32, .species=PINSIR}
    }},
    {"WADE@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=METAPOD},
        {.level=9, .species=METAPOD},
        {.level=10, .species=KAKUNA},
        {.level=9, .species=METAPOD}
    }},
    {"WADE@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=14, .species=BUTTERFREE},
        {.level=14, .species=BUTTERFREE},
        {.level=15, .species=BEEDRILL},
        {.level=14, .species=BUTTERFREE}
    }},
    {"DOUG@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=ARIADOS}
    }},
    {"ARNIE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=VENONAT}
    }},
    {"ARNIE@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=28, .species=VENOMOTH, .moves={DISABLE, SUPERSONIC, CONFUSION, LEECH_LIFE}}
    }},
    {"WADE@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=24, .species=BUTTERFREE, .moves={CONFUSION, POISONPOWDER, SUPERSONIC, WHIRLWIND}},
        {.level=24, .species=BUTTERFREE, .moves={CONFUSION, STUN_SPORE, SUPERSONIC, WHIRLWIND}},
        {.level=25, .species=BEEDRILL, .moves={FURY_ATTACK, FOCUS_ENERGY, TWINEEDLE, RAGE}},
        {.level=24, .species=BUTTERFREE, .moves={CONFUSION, SLEEP_POWDER, SUPERSONIC, WHIRLWIND}}
    }},
    {"WADE@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=BUTTERFREE, .moves={CONFUSION, POISONPOWDER, SUPERSONIC, GUST}},
        {.level=30, .species=BUTTERFREE, .moves={CONFUSION, STUN_SPORE, SUPERSONIC, GUST}},
        {.level=32, .species=BEEDRILL, .moves={FURY_ATTACK, PURSUIT, TWINEEDLE, DOUBLE_TEAM}},
        {.level=34, .species=BUTTERFREE, .moves={PSYBEAM, SLEEP_POWDER, GUST, WHIRLWIND}}
    }},
    {"ARNIE@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=36, .species=VENOMOTH, .moves={GUST, SUPERSONIC, PSYBEAM, LEECH_LIFE}}
    }},
    {"ARNIE@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=40, .species=VENOMOTH, .moves={GUST, SUPERSONIC, PSYCHIC_M, TOXIC}}
    }},
    {"WAYNE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=8, .species=LEDYBA},
        {.level=10, .species=PARAS}
    }},
};

const struct TrainerParty FisherGroup[] = {
    {"JUSTIN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=5, .species=MAGIKARP},
        {.level=5, .species=MAGIKARP},
        {.level=15, .species=MAGIKARP},
        {.level=5, .species=MAGIKARP}
    }},
    {"RALPH@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=GOLDEEN}
    }},
    {"ARNOLD@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=TENTACRUEL}
    }},
    {"KYLE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=SEAKING},
        {.level=31, .species=POLIWHIRL},
        {.level=31, .species=SEAKING}
    }},
    {"HENRY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=8, .species=POLIWAG},
        {.level=8, .species=POLIWAG}
    }},
    {"MARVIN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=MAGIKARP},
        {.level=10, .species=GYARADOS},
        {.level=15, .species=MAGIKARP},
        {.level=15, .species=GYARADOS}
    }},
    {"TULLY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=QWILFISH}
    }},
    {"ANDRE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=GYARADOS}
    }},
    {"RAYMOND@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=MAGIKARP},
        {.level=22, .species=MAGIKARP},
        {.level=22, .species=MAGIKARP},
        {.level=22, .species=MAGIKARP}
    }},
    {"WILTON@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=GOLDEEN},
        {.level=23, .species=GOLDEEN},
        {.level=25, .species=SEAKING}
    }},
    {"EDGAR@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=25, .species=REMORAID, .moves={LOCK_ON, PSYBEAM, AURORA_BEAM, BUBBLEBEAM}},
        {.level=25, .species=REMORAID, .moves={LOCK_ON, PSYBEAM, AURORA_BEAM, BUBBLEBEAM}}
    }},
    {"JONAH@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=SHELLDER},
        {.level=29, .species=OCTILLERY},
        {.level=25, .species=REMORAID},
        {.level=29, .species=CLOYSTER}
    }},
    {"MARTIN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=REMORAID},
        {.level=32, .species=REMORAID}
    }},
    {"STEPHEN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=MAGIKARP},
        {.level=25, .species=MAGIKARP},
        {.level=31, .species=QWILFISH},
        {.level=31, .species=TENTACRUEL}
    }},
    {"BARNEY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=GYARADOS},
        {.level=30, .species=GYARADOS},
        {.level=30, .species=GYARADOS}
    }},
    {"RALPH@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=GOLDEEN}
    }},
    {"RALPH@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=QWILFISH},
        {.level=19, .species=GOLDEEN}
    }},
    {"TULLY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=QWILFISH}
    }},
    {"TULLY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=GOLDEEN},
        {.level=32, .species=GOLDEEN},
        {.level=32, .species=QWILFISH}
    }},
    {"WILTON@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=GOLDEEN},
        {.level=29, .species=GOLDEEN},
        {.level=32, .species=SEAKING}
    }},
    {"SCOTT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=QWILFISH},
        {.level=30, .species=QWILFISH},
        {.level=34, .species=SEAKING}
    }},
    {"WILTON@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=34, .species=SEAKING, .moves={SUPERSONIC, WATERFALL, FLAIL, FURY_ATTACK}},
        {.level=34, .species=SEAKING, .moves={SUPERSONIC, WATERFALL, FLAIL, FURY_ATTACK}},
        {.level=38, .species=REMORAID, .moves={PSYBEAM, AURORA_BEAM, BUBBLEBEAM, HYPER_BEAM}}
    }},
    {"RALPH@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=QWILFISH},
        {.level=32, .species=GOLDEEN}
    }},
    {"RALPH@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=35, .species=QWILFISH, .moves={TOXIC, MINIMIZE, SURF, PIN_MISSILE}},
        {.level=39, .species=SEAKING, .moves={ENDURE, FLAIL, FURY_ATTACK, WATERFALL}}
    }},
    {"TULLY@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=34, .species=SEAKING, .moves={SUPERSONIC, RAIN_DANCE, WATERFALL, FURY_ATTACK}},
        {.level=34, .species=SEAKING, .moves={SUPERSONIC, RAIN_DANCE, WATERFALL, FURY_ATTACK}},
        {.level=37, .species=QWILFISH, .moves={ROLLOUT, SURF, PIN_MISSILE, TAKE_DOWN}}
    }},
};

const struct TrainerParty SwimmerMGroup[] = {
    {"HAROLD@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=REMORAID},
        {.level=30, .species=SEADRA}
    }},
    {"SIMON@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=TENTACOOL},
        {.level=20, .species=TENTACOOL}
    }},
    {"RANDALL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=SHELLDER},
        {.level=20, .species=WARTORTLE},
        {.level=18, .species=SHELLDER}
    }},
    {"CHARLIE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=21, .species=SHELLDER},
        {.level=19, .species=TENTACOOL},
        {.level=19, .species=TENTACRUEL}
    }},
    {"GEORGE@", TRAINERTYPE_NORMAL, .size=6, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=TENTACOOL},
        {.level=17, .species=TENTACOOL},
        {.level=16, .species=TENTACOOL},
        {.level=19, .species=STARYU},
        {.level=17, .species=TENTACOOL},
        {.level=19, .species=REMORAID}
    }},
    {"BERKE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=QWILFISH}
    }},
    {"KIRK@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=GYARADOS},
        {.level=20, .species=GYARADOS}
    }},
    {"MATHEW@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=KRABBY}
    }},
    {"HAL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=SEEL},
        {.level=25, .species=DEWGONG},
        {.level=24, .species=SEEL}
    }},
    {"PATON@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=PILOSWINE},
        {.level=26, .species=PILOSWINE}
    }},
    {"DARYL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=SHELLDER},
        {.level=25, .species=CLOYSTER},
        {.level=24, .species=SHELLDER}
    }},
    {"WALTER@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=HORSEA},
        {.level=15, .species=HORSEA},
        {.level=20, .species=SEADRA}
    }},
    {"TONY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=13, .species=STARYU},
        {.level=18, .species=STARMIE},
        {.level=16, .species=HORSEA}
    }},
    {"JEROME@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=SEADRA},
        {.level=28, .species=TENTACOOL},
        {.level=30, .species=TENTACRUEL},
        {.level=28, .species=GOLDEEN}
    }},
    {"TUCKER@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=SHELLDER},
        {.level=34, .species=CLOYSTER}
    }},
    {"RICK@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=13, .species=STARYU},
        {.level=18, .species=STARMIE},
        {.level=16, .species=HORSEA}
    }},
    {"CAMERON@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=MARILL}
    }},
    {"SETH@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=QUAGSIRE},
        {.level=29, .species=OCTILLERY},
        {.level=32, .species=QUAGSIRE}
    }},
    {"JAMES@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=13, .species=STARYU},
        {.level=18, .species=STARMIE},
        {.level=16, .species=HORSEA}
    }},
    {"LEWIS@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=13, .species=STARYU},
        {.level=18, .species=STARMIE},
        {.level=16, .species=HORSEA}
    }},
    {"PARKER@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=HORSEA},
        {.level=32, .species=HORSEA},
        {.level=35, .species=SEADRA}
    }},
};

const struct TrainerParty SwimmerFGroup[] = {
    {"ELAINE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=21, .species=STARYU}
    }},
    {"PAULA@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=STARYU},
        {.level=19, .species=SHELLDER}
    }},
    {"KAYLEE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=GOLDEEN},
        {.level=20, .species=GOLDEEN},
        {.level=20, .species=SEAKING}
    }},
    {"SUSIE@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=20, .species=PSYDUCK, .moves={SCRATCH, TAIL_WHIP, DISABLE, CONFUSION}},
        {.level=22, .species=GOLDEEN, .moves={PECK, TAIL_WHIP, SUPERSONIC, HORN_ATTACK}}
    }},
    {"DENISE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=SEEL}
    }},
    {"KARA@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=STARYU},
        {.level=20, .species=STARMIE}
    }},
    {"WENDY@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=21, .species=HORSEA, .moves={BUBBLE, SMOKESCREEN, LEER, WATER_GUN}},
        {.level=21, .species=HORSEA, .moves={DRAGON_RAGE, SMOKESCREEN, LEER, WATER_GUN}}
    }},
    {"LISA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=JYNX}
    }},
    {"JILL@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=DEWGONG}
    }},
    {"MARY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=SEAKING}
    }},
    {"KATIE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=DEWGONG}
    }},
    {"DAWN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=SEAKING}
    }},
    {"TARA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=SEAKING}
    }},
    {"NICOLE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=MARILL},
        {.level=29, .species=MARILL},
        {.level=32, .species=LAPRAS}
    }},
    {"LORI@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=STARMIE},
        {.level=32, .species=STARMIE}
    }},
    {"JODY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=SEAKING}
    }},
    {"NIKKI@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=SEEL},
        {.level=28, .species=SEEL},
        {.level=28, .species=SEEL},
        {.level=28, .species=DEWGONG}
    }},
    {"DIANA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=37, .species=GOLDUCK}
    }},
    {"BRIANA@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=SEAKING},
        {.level=35, .species=SEAKING}
    }},
};

const struct TrainerParty SailorGroup[] = {
    {"EUGENE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=POLIWHIRL},
        {.level=17, .species=RATICATE},
        {.level=19, .species=KRABBY}
    }},
    {"HUEY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=POLIWAG},
        {.level=18, .species=POLIWHIRL}
    }},
    {"TERRELL@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=POLIWHIRL}
    }},
    {"KENT@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=18, .species=KRABBY, .moves={BUBBLE, LEER, VICEGRIP, HARDEN}},
        {.level=20, .species=KRABBY, .moves={BUBBLEBEAM, LEER, VICEGRIP, HARDEN}}
    }},
    {"ERNEST@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=MACHOP},
        {.level=18, .species=MACHOP},
        {.level=18, .species=POLIWHIRL}
    }},
    {"JEFF@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=RATICATE},
        {.level=32, .species=RATICATE}
    }},
    {"GARRETT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=KINGLER}
    }},
    {"KENNETH@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=MACHOP},
        {.level=28, .species=MACHOP},
        {.level=28, .species=POLIWRATH},
        {.level=28, .species=MACHOP}
    }},
    {"STANLY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=MACHOP},
        {.level=33, .species=MACHOKE},
        {.level=26, .species=PSYDUCK}
    }},
    {"HARRY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=WOOPER}
    }},
    {"HUEY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=POLIWHIRL},
        {.level=28, .species=POLIWHIRL}
    }},
    {"HUEY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=POLIWHIRL},
        {.level=34, .species=POLIWRATH}
    }},
    {"HUEY@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=38, .species=POLITOED, .moves={WHIRLPOOL, RAIN_DANCE, BODY_SLAM, PERISH_SONG}},
        {.level=38, .species=POLIWRATH, .moves={SURF, STRENGTH, ICE_PUNCH, SUBMISSION}}
    }},
};

const struct TrainerParty SuperNerdGroup[] = {
    {"STAN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=GRIMER}
    }},
    {"ERIC@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=11, .species=GRIMER},
        {.level=11, .species=GRIMER}
    }},
    {"GREGG@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=MAGNEMITE},
        {.level=20, .species=MAGNEMITE},
        {.level=20, .species=MAGNEMITE}
    }},
    {"JAY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=KOFFING},
        {.level=22, .species=KOFFING}
    }},
    {"DAVE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=DITTO}
    }},
    {"SAM@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=GRIMER},
        {.level=34, .species=MUK}
    }},
    {"TOM@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=MAGNEMITE},
        {.level=32, .species=MAGNEMITE},
        {.level=32, .species=MAGNEMITE}
    }},
    {"PAT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=36, .species=PORYGON}
    }},
    {"SHAWN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=MAGNEMITE},
        {.level=33, .species=MUK},
        {.level=31, .species=MAGNEMITE}
    }},
    {"TERU@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=7, .species=MAGNEMITE},
        {.level=11, .species=VOLTORB},
        {.level=7, .species=MAGNEMITE},
        {.level=9, .species=MAGNEMITE}
    }},
    {"RUSS@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=MAGNEMITE},
        {.level=27, .species=MAGNEMITE},
        {.level=27, .species=MAGNEMITE}
    }},
    {"NORTON@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=PORYGON, .moves={CONVERSION, CONVERSION2, RECOVER, TRI_ATTACK}}
    }},
    {"HUGH@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=39, .species=SEADRA, .moves={SMOKESCREEN, TWISTER, SURF, WATERFALL}}
    }},
    {"MARKUS@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=19, .species=SLOWPOKE, .moves={CURSE, WATER_GUN, GROWL, STRENGTH}}
    }},
};

const struct TrainerParty Rival2Group[] = {
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=41, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=42, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=41, .species=MAGNETON, .moves={THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=43, .species=GENGAR, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=43, .species=ALAKAZAM, .moves={DISABLE, RECOVER, FUTURE_SIGHT, PSYCHIC_M}},
        {.level=45, .species=MEGANIUM, .moves={RAZOR_LEAF, POISONPOWDER, BODY_SLAM, LIGHT_SCREEN}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=41, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=42, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=41, .species=MAGNETON, .moves={THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=43, .species=GENGAR, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=43, .species=ALAKAZAM, .moves={DISABLE, RECOVER, FUTURE_SIGHT, PSYCHIC_M}},
        {.level=45, .species=TYPHLOSION, .moves={SMOKESCREEN, QUICK_ATTACK, FLAME_WHEEL, SWIFT}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=41, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=42, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=41, .species=MAGNETON, .moves={THUNDERSHOCK, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=43, .species=GENGAR, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=43, .species=ALAKAZAM, .moves={DISABLE, RECOVER, FUTURE_SIGHT, PSYCHIC_M}},
        {.level=45, .species=FERALIGATR, .moves={RAGE, WATER_GUN, SCARY_FACE, SLASH}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=45, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=48, .species=CROBAT, .moves={TOXIC, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=45, .species=MAGNETON, .moves={THUNDER, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=46, .species=GENGAR, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=46, .species=ALAKAZAM, .moves={RECOVER, FUTURE_SIGHT, PSYCHIC_M, REFLECT}},
        {.level=50, .species=MEGANIUM, .moves={GIGA_DRAIN, BODY_SLAM, LIGHT_SCREEN, SAFEGUARD}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=45, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=48, .species=CROBAT, .moves={TOXIC, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=45, .species=MAGNETON, .moves={THUNDER, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=46, .species=GENGAR, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=46, .species=ALAKAZAM, .moves={RECOVER, FUTURE_SIGHT, PSYCHIC_M, REFLECT}},
        {.level=50, .species=TYPHLOSION, .moves={SMOKESCREEN, QUICK_ATTACK, FIRE_BLAST, SWIFT}}
    }},
    {"?@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=45, .species=SNEASEL, .moves={QUICK_ATTACK, SCREECH, FAINT_ATTACK, FURY_CUTTER}},
        {.level=48, .species=CROBAT, .moves={TOXIC, BITE, CONFUSE_RAY, WING_ATTACK}},
        {.level=45, .species=MAGNETON, .moves={THUNDER, SONICBOOM, THUNDER_WAVE, SWIFT}},
        {.level=46, .species=GENGAR, .moves={MEAN_LOOK, CURSE, SHADOW_BALL, CONFUSE_RAY}},
        {.level=46, .species=ALAKAZAM, .moves={RECOVER, FUTURE_SIGHT, PSYCHIC_M, REFLECT}},
        {.level=50, .species=FERALIGATR, .moves={SURF, RAIN_DANCE, SLASH, SCREECH}}
    }},
};

const struct TrainerParty GuitaristGroup[] = {
    {"CLYDE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=ELECTABUZZ}
    }},
    {"VINCENT@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=MAGNEMITE},
        {.level=33, .species=VOLTORB},
        {.level=32, .species=MAGNEMITE},
        {.level=32, .species=MAGNEMITE}
    }},
};

const struct TrainerParty HikerGroup[] = {
    {"ANTHONY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=GEODUDE},
        {.level=18, .species=MACHAMP}
    }},
    {"RUSSELL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=4, .species=GEODUDE},
        {.level=6, .species=GEODUDE},
        {.level=8, .species=GEODUDE}
    }},
    {"PHILLIP@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=GEODUDE},
        {.level=23, .species=GEODUDE},
        {.level=23, .species=GRAVELER}
    }},
    {"LEONARD@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=GEODUDE},
        {.level=25, .species=MACHOP}
    }},
    {"ANTHONY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=11, .species=GEODUDE},
        {.level=11, .species=MACHOP}
    }},
    {"BENJAMIN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=14, .species=DIGLETT},
        {.level=14, .species=GEODUDE},
        {.level=16, .species=DUGTRIO}
    }},
    {"ERIK@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=MACHOP},
        {.level=27, .species=GRAVELER},
        {.level=27, .species=MACHOP}
    }},
    {"MICHAEL@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=GEODUDE},
        {.level=25, .species=GRAVELER},
        {.level=25, .species=GOLEM}
    }},
    {"PARRY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=ONIX},
        {.level=33, .species=SWINUB}
    }},
    {"TIMOTHY@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=27, .species=DIGLETT, .moves={MAGNITUDE, DIG, SAND_ATTACK, SLASH}},
        {.level=27, .species=DUGTRIO, .moves={MAGNITUDE, DIG, SAND_ATTACK, SLASH}}
    }},
    {"BAILEY@", TRAINERTYPE_NORMAL, .size=5, .pnormal=(struct TrainerPartyNormal[]){
        {.level=13, .species=GEODUDE},
        {.level=13, .species=GEODUDE},
        {.level=13, .species=GEODUDE},
        {.level=13, .species=GEODUDE},
        {.level=13, .species=GEODUDE}
    }},
    {"ANTHONY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=GRAVELER},
        {.level=27, .species=GRAVELER},
        {.level=29, .species=MACHOKE}
    }},
    {"TIM@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=GRAVELER},
        {.level=31, .species=GRAVELER},
        {.level=31, .species=GRAVELER}
    }},
    {"NOLAND@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=SANDSLASH},
        {.level=33, .species=GOLEM}
    }},
    {"SIDNEY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=DUGTRIO},
        {.level=32, .species=ONIX}
    }},
    {"KENNY@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=SANDSLASH},
        {.level=29, .species=GRAVELER},
        {.level=31, .species=GOLEM},
        {.level=29, .species=GRAVELER}
    }},
    {"JIM@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=MACHAMP}
    }},
    {"DANIEL@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=11, .species=ONIX}
    }},
    {"PARRY@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=35, .species=PILOSWINE, .moves={EARTHQUAKE, BLIZZARD, REST, TAKE_DOWN}},
        {.level=35, .species=DUGTRIO, .moves={MAGNITUDE, DIG, MUD_SLAP, SLASH}},
        {.level=38, .species=STEELIX, .moves={DIG, IRON_TAIL, SANDSTORM, SLAM}}
    }},
    {"PARRY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=ONIX}
    }},
    {"ANTHONY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=GRAVELER},
        {.level=30, .species=GRAVELER},
        {.level=32, .species=MACHOKE}
    }},
    {"ANTHONY@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=34, .species=GRAVELER, .moves={MAGNITUDE, SELFDESTRUCT, DEFENSE_CURL, ROLLOUT}},
        {.level=36, .species=GOLEM, .moves={MAGNITUDE, SELFDESTRUCT, DEFENSE_CURL, ROLLOUT}},
        {.level=34, .species=MACHOKE, .moves={KARATE_CHOP, VITAL_THROW, HEADBUTT, DIG}}
    }},
};

const struct TrainerParty BikerGroup[] = {
    {"BENNY@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=KOFFING},
        {.level=20, .species=KOFFING},
        {.level=20, .species=KOFFING}
    }},
    {"KAZU@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=KOFFING},
        {.level=20, .species=KOFFING},
        {.level=20, .species=KOFFING}
    }},
    {"DWAYNE@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=KOFFING},
        {.level=28, .species=KOFFING},
        {.level=29, .species=KOFFING},
        {.level=30, .species=KOFFING}
    }},
    {"HARRIS@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=FLAREON}
    }},
    {"ZEKE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=KOFFING},
        {.level=32, .species=KOFFING}
    }},
    {"CHARLES@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=KOFFING},
        {.level=30, .species=CHARMELEON},
        {.level=30, .species=WEEZING}
    }},
    {"RILEY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=WEEZING}
    }},
    {"JOEL@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=MAGMAR},
        {.level=32, .species=MAGMAR}
    }},
    {"GLENN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=KOFFING},
        {.level=30, .species=MAGMAR},
        {.level=32, .species=WEEZING}
    }},
};

const struct TrainerParty BlaineGroup[] = {
    {"BLAINE@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=45, .species=MAGCARGO, .moves={CURSE, SMOG, FLAMETHROWER, ROCK_SLIDE}},
        {.level=45, .species=MAGMAR, .moves={THUNDERPUNCH, FIRE_PUNCH, SUNNY_DAY, CONFUSE_RAY}},
        {.level=50, .species=RAPIDASH, .moves={QUICK_ATTACK, FIRE_SPIN, FURY_ATTACK, FIRE_BLAST}}
    }},
};

const struct TrainerParty BurglarGroup[] = {
    {"DUNCAN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=KOFFING},
        {.level=25, .species=MAGMAR},
        {.level=23, .species=KOFFING}
    }},
    {"EDDIE@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=26, .species=GROWLITHE, .moves={ROAR, EMBER, LEER, TAKE_DOWN}},
        {.level=24, .species=KOFFING, .moves={TACKLE, SMOG, SLUDGE, SMOKESCREEN}}
    }},
    {"COREY@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=KOFFING},
        {.level=28, .species=MAGMAR},
        {.level=25, .species=KOFFING},
        {.level=30, .species=KOFFING}
    }},
};

const struct TrainerParty FirebreatherGroup[] = {
    {"OTIS@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=MAGMAR},
        {.level=32, .species=WEEZING},
        {.level=29, .species=MAGMAR}
    }},
    {"DICK@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=CHARMELEON}
    }},
    {"NED@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=KOFFING},
        {.level=16, .species=GROWLITHE},
        {.level=15, .species=KOFFING}
    }},
    {"BURT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=KOFFING},
        {.level=32, .species=SLUGMA}
    }},
    {"BILL@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=6, .species=KOFFING},
        {.level=6, .species=KOFFING}
    }},
    {"WALT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=11, .species=MAGMAR},
        {.level=13, .species=MAGMAR}
    }},
    {"RAY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=VULPIX}
    }},
    {"LYLE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=KOFFING},
        {.level=31, .species=FLAREON},
        {.level=28, .species=KOFFING}
    }},
};

const struct TrainerParty JugglerGroup[] = {
    {"IRWIN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=2, .species=VOLTORB},
        {.level=6, .species=VOLTORB},
        {.level=10, .species=VOLTORB},
        {.level=14, .species=VOLTORB}
    }},
    {"FRITZ@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=MR__MIME},
        {.level=29, .species=MAGMAR},
        {.level=29, .species=MACHOKE}
    }},
    {"HORTON@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=ELECTRODE},
        {.level=33, .species=ELECTRODE},
        {.level=33, .species=ELECTRODE},
        {.level=33, .species=ELECTRODE}
    }},
    {"IRWIN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=6, .species=VOLTORB},
        {.level=10, .species=VOLTORB},
        {.level=14, .species=VOLTORB},
        {.level=18, .species=VOLTORB}
    }},
    {"IRWIN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=VOLTORB},
        {.level=22, .species=VOLTORB},
        {.level=26, .species=VOLTORB},
        {.level=30, .species=ELECTRODE}
    }},
    {"IRWIN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=VOLTORB},
        {.level=22, .species=VOLTORB},
        {.level=26, .species=VOLTORB},
        {.level=30, .species=ELECTRODE}
    }},
};

const struct TrainerParty BlackbeltGroup[] = {
    {"KENJI@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=27, .species=ONIX},
        {.level=30, .species=HITMONLEE},
        {.level=27, .species=ONIX},
        {.level=32, .species=MACHOKE}
    }},
    {"YOSHI@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=27, .species=HITMONLEE, .moves={DOUBLE_KICK, MEDITATE, JUMP_KICK, FOCUS_ENERGY}}
    }},
    {"KENJI@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=33, .species=ONIX, .moves={BIND, ROCK_THROW, TOXIC, DIG}},
        {.level=38, .species=MACHAMP, .moves={HEADBUTT, SWAGGER, THUNDERPUNCH, VITAL_THROW}},
        {.level=33, .species=STEELIX, .moves={EARTHQUAKE, ROCK_THROW, IRON_TAIL, SANDSTORM}},
        {.level=36, .species=HITMONLEE, .moves={DOUBLE_TEAM, HI_JUMP_KICK, MUD_SLAP, SWIFT}}
    }},
    {"LAO@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=27, .species=HITMONCHAN, .moves={COMET_PUNCH, THUNDERPUNCH, ICE_PUNCH, FIRE_PUNCH}}
    }},
    {"NOB@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=25, .species=MACHOP, .moves={LEER, FOCUS_ENERGY, KARATE_CHOP, SEISMIC_TOSS}},
        {.level=25, .species=MACHOKE, .moves={LEER, KARATE_CHOP, SEISMIC_TOSS, ROCK_SLIDE}}
    }},
    {"KIYO@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=HITMONLEE},
        {.level=34, .species=HITMONCHAN}
    }},
    {"LUNG@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=MANKEY},
        {.level=23, .species=MANKEY},
        {.level=25, .species=PRIMEAPE}
    }},
    {"KENJI@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=28, .species=MACHOKE}
    }},
    {"WAI@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=MACHOKE},
        {.level=32, .species=MACHOKE},
        {.level=34, .species=MACHOKE}
    }},
};

const struct TrainerParty ExecutiveMGroup[] = {
    {"EXECUTIVE@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=33, .species=HOUNDOUR, .moves={EMBER, ROAR, BITE, FAINT_ATTACK}},
        {.level=33, .species=KOFFING, .moves={TACKLE, SLUDGE, SMOKESCREEN, HAZE}},
        {.level=35, .species=HOUNDOOM, .moves={EMBER, SMOG, BITE, FAINT_ATTACK}}
    }},
    {"EXECUTIVE@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=36, .species=GOLBAT, .moves={LEECH_LIFE, BITE, CONFUSE_RAY, WING_ATTACK}}
    }},
    {"EXECUTIVE@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=KOFFING, .moves={TACKLE, SELFDESTRUCT, SLUDGE, SMOKESCREEN}},
        {.level=30, .species=KOFFING, .moves={TACKLE, SELFDESTRUCT, SLUDGE, SMOKESCREEN}},
        {.level=30, .species=KOFFING, .moves={TACKLE, SELFDESTRUCT, SLUDGE, SMOKESCREEN}},
        {.level=32, .species=WEEZING, .moves={TACKLE, EXPLOSION, SLUDGE, SMOKESCREEN}},
        {.level=30, .species=KOFFING, .moves={TACKLE, SELFDESTRUCT, SLUDGE, SMOKESCREEN}},
        {.level=30, .species=KOFFING, .moves={TACKLE, SMOG, SLUDGE, SMOKESCREEN}}
    }},
    {"EXECUTIVE@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=ZUBAT},
        {.level=24, .species=RATICATE},
        {.level=22, .species=KOFFING}
    }},
};

const struct TrainerParty PsychicGroup[] = {
    {"NATHAN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=GIRAFARIG}
    }},
    {"FRANKLIN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=37, .species=KADABRA}
    }},
    {"HERMAN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=EXEGGCUTE},
        {.level=30, .species=EXEGGCUTE},
        {.level=30, .species=EXEGGUTOR}
    }},
    {"FIDEL@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=XATU}
    }},
    {"GREG@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=17, .species=DROWZEE, .moves={HYPNOSIS, DISABLE, DREAM_EATER, NO_MOVE}}
    }},
    {"NORMAN@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=17, .species=SLOWPOKE, .moves={TACKLE, GROWL, WATER_GUN, NO_MOVE}},
        {.level=20, .species=SLOWPOKE, .moves={CURSE, BODY_SLAM, WATER_GUN, CONFUSION}}
    }},
    {"MARK@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=13, .species=ABRA, .moves={TELEPORT, FLASH, NO_MOVE, NO_MOVE}},
        {.level=13, .species=ABRA, .moves={TELEPORT, FLASH, NO_MOVE, NO_MOVE}},
        {.level=15, .species=KADABRA, .moves={TELEPORT, KINESIS, CONFUSION, NO_MOVE}}
    }},
    {"PHIL@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=24, .species=NATU, .moves={LEER, NIGHT_SHADE, FUTURE_SIGHT, CONFUSE_RAY}},
        {.level=26, .species=KADABRA, .moves={DISABLE, PSYBEAM, RECOVER, FUTURE_SIGHT}}
    }},
    {"RICHARD@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=36, .species=ESPEON}
    }},
    {"GILBERT@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=STARMIE},
        {.level=30, .species=EXEGGCUTE},
        {.level=34, .species=GIRAFARIG}
    }},
    {"JARED@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=MR__MIME},
        {.level=32, .species=EXEGGCUTE},
        {.level=35, .species=EXEGGCUTE}
    }},
    {"RODNEY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=29, .species=DROWZEE},
        {.level=33, .species=HYPNO}
    }},
};

const struct TrainerParty PicnickerGroup[] = {
    {"LIZ@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=NIDORAN_F}
    }},
    {"GINA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=HOPPIP},
        {.level=9, .species=HOPPIP},
        {.level=12, .species=BULBASAUR}
    }},
    {"BROOKE@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=16, .species=PIKACHU, .moves={THUNDERSHOCK, GROWL, QUICK_ATTACK, DOUBLE_TEAM}}
    }},
    {"KIM@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=VULPIX}
    }},
    {"CINDY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=36, .species=NIDOQUEEN}
    }},
    {"HOPE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=FLAAFFY}
    }},
    {"SHARON@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=FURRET},
        {.level=33, .species=RAPIDASH}
    }},
    {"DEBRA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=SEAKING}
    }},
    {"GINA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=14, .species=HOPPIP},
        {.level=14, .species=HOPPIP},
        {.level=17, .species=IVYSAUR}
    }},
    {"ERIN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=PONYTA},
        {.level=16, .species=PONYTA}
    }},
    {"LIZ@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=WEEPINBELL},
        {.level=15, .species=NIDORINA}
    }},
    {"LIZ@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=19, .species=WEEPINBELL},
        {.level=19, .species=NIDORINO},
        {.level=21, .species=NIDOQUEEN}
    }},
    {"HEIDI@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=SKIPLOOM},
        {.level=32, .species=SKIPLOOM}
    }},
    {"EDNA@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=NIDORINA},
        {.level=34, .species=RAICHU}
    }},
    {"GINA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=SKIPLOOM},
        {.level=26, .species=SKIPLOOM},
        {.level=29, .species=IVYSAUR}
    }},
    {"TIFFANY@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=31, .species=CLEFAIRY, .moves={ENCORE, SING, DOUBLESLAP, MINIMIZE}}
    }},
    {"TIFFANY@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=37, .species=CLEFAIRY, .moves={ENCORE, DOUBLESLAP, MINIMIZE, METRONOME}}
    }},
    {"ERIN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=PONYTA},
        {.level=32, .species=PONYTA}
    }},
    {"TANYA@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=37, .species=EXEGGUTOR}
    }},
    {"TIFFANY@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=20, .species=CLEFAIRY, .moves={ENCORE, SING, DOUBLESLAP, MINIMIZE}}
    }},
    {"ERIN@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=36, .species=PONYTA, .moves={DOUBLE_TEAM, STOMP, FIRE_SPIN, SUNNY_DAY}},
        {.level=34, .species=RAICHU, .moves={SWIFT, MUD_SLAP, QUICK_ATTACK, THUNDERBOLT}},
        {.level=36, .species=PONYTA, .moves={DOUBLE_TEAM, STOMP, FIRE_SPIN, SUNNY_DAY}}
    }},
    {"LIZ@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=WEEPINBELL},
        {.level=26, .species=NIDORINO},
        {.level=26, .species=NIDOQUEEN}
    }},
    {"LIZ@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=30, .species=WEEPINBELL, .moves={SLEEP_POWDER, POISONPOWDER, STUN_SPORE, SLUDGE_BOMB}},
        {.level=32, .species=NIDOKING, .moves={EARTHQUAKE, DOUBLE_KICK, POISON_STING, IRON_TAIL}},
        {.level=32, .species=NIDOQUEEN, .moves={EARTHQUAKE, DOUBLE_KICK, TAIL_WHIP, BODY_SLAM}}
    }},
    {"GINA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=SKIPLOOM},
        {.level=30, .species=SKIPLOOM},
        {.level=32, .species=IVYSAUR}
    }},
    {"GINA@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=33, .species=JUMPLUFF, .moves={STUN_SPORE, SUNNY_DAY, LEECH_SEED, COTTON_SPORE}},
        {.level=33, .species=JUMPLUFF, .moves={SUNNY_DAY, SLEEP_POWDER, LEECH_SEED, COTTON_SPORE}},
        {.level=38, .species=VENUSAUR, .moves={SOLARBEAM, RAZOR_LEAF, HEADBUTT, MUD_SLAP}}
    }},
    {"TIFFANY@", TRAINERTYPE_MOVES, .size=1, .pmoves=(struct TrainerPartyMoves[]){
        {.level=43, .species=CLEFAIRY, .moves={METRONOME, ENCORE, MOONLIGHT, MINIMIZE}}
    }},
};

const struct TrainerParty CamperGroup[] = {
    {"ROLAND@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=NIDORAN_M}
    }},
    {"TODD@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=14, .species=PSYDUCK}
    }},
    {"IVAN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=DIGLETT},
        {.level=10, .species=ZUBAT},
        {.level=14, .species=DIGLETT}
    }},
    {"ELLIOT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=13, .species=SANDSHREW},
        {.level=15, .species=MARILL}
    }},
    {"BARRY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=36, .species=NIDOKING}
    }},
    {"LLOYD@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=NIDOKING}
    }},
    {"DEAN@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=GOLDUCK},
        {.level=31, .species=SANDSLASH}
    }},
    {"SID@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=DUGTRIO},
        {.level=29, .species=PRIMEAPE},
        {.level=29, .species=POLIWRATH}
    }},
    {"HARVEY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=NIDORINO}
    }},
    {"DALE@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=15, .species=NIDORINO}
    }},
    {"TED@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=MANKEY}
    }},
    {"TODD@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=GEODUDE},
        {.level=17, .species=GEODUDE},
        {.level=23, .species=PSYDUCK}
    }},
    {"TODD@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=23, .species=GEODUDE},
        {.level=23, .species=GEODUDE},
        {.level=26, .species=PSYDUCK}
    }},
    {"THOMAS@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=GRAVELER},
        {.level=36, .species=GRAVELER},
        {.level=40, .species=GOLBAT},
        {.level=42, .species=GOLDUCK}
    }},
    {"LEROY@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=GRAVELER},
        {.level=36, .species=GRAVELER},
        {.level=40, .species=GOLBAT},
        {.level=42, .species=GOLDUCK}
    }},
    {"DAVID@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=GRAVELER},
        {.level=36, .species=GRAVELER},
        {.level=40, .species=GOLBAT},
        {.level=42, .species=GOLDUCK}
    }},
    {"JOHN@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=33, .species=GRAVELER},
        {.level=36, .species=GRAVELER},
        {.level=40, .species=GOLBAT},
        {.level=42, .species=GOLDUCK}
    }},
    {"JERRY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=37, .species=SANDSLASH}
    }},
    {"SPENCER@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=SANDSHREW},
        {.level=17, .species=SANDSLASH},
        {.level=19, .species=ZUBAT}
    }},
    {"TODD@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=GRAVELER},
        {.level=30, .species=GRAVELER},
        {.level=30, .species=SLUGMA},
        {.level=32, .species=PSYDUCK}
    }},
    {"TODD@", TRAINERTYPE_MOVES, .size=4, .pmoves=(struct TrainerPartyMoves[]){
        {.level=33, .species=GRAVELER, .moves={SELFDESTRUCT, ROCK_THROW, HARDEN, MAGNITUDE}},
        {.level=33, .species=GRAVELER, .moves={SELFDESTRUCT, ROCK_THROW, HARDEN, MAGNITUDE}},
        {.level=36, .species=MAGCARGO, .moves={ROCK_THROW, HARDEN, AMNESIA, FLAMETHROWER}},
        {.level=34, .species=GOLDUCK, .moves={DISABLE, PSYCHIC_M, SURF, PSYCH_UP}}
    }},
    {"QUENTIN@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=30, .species=FEAROW},
        {.level=30, .species=PRIMEAPE},
        {.level=30, .species=TAUROS}
    }},
};

const struct TrainerParty ExecutiveFGroup[] = {
    {"EXECUTIVE@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=32, .species=ARBOK, .moves={WRAP, POISON_STING, BITE, GLARE}},
        {.level=32, .species=VILEPLUME, .moves={ABSORB, SWEET_SCENT, SLEEP_POWDER, ACID}},
        {.level=32, .species=MURKROW, .moves={PECK, PURSUIT, HAZE, NIGHT_SHADE}}
    }},
    {"EXECUTIVE@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=23, .species=ARBOK, .moves={WRAP, LEER, POISON_STING, BITE}},
        {.level=23, .species=GLOOM, .moves={ABSORB, SWEET_SCENT, SLEEP_POWDER, ACID}},
        {.level=25, .species=MURKROW, .moves={PECK, PURSUIT, HAZE, NO_MOVE}}
    }},
};

const struct TrainerParty SageGroup[] = {
    {"CHOW@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=3, .species=BELLSPROUT},
        {.level=3, .species=BELLSPROUT},
        {.level=3, .species=BELLSPROUT}
    }},
    {"NICO@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=3, .species=BELLSPROUT},
        {.level=3, .species=BELLSPROUT},
        {.level=3, .species=BELLSPROUT}
    }},
    {"JIN@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=6, .species=BELLSPROUT}
    }},
    {"TROY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=7, .species=BELLSPROUT},
        {.level=7, .species=HOOTHOOT}
    }},
    {"JEFFREY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=22, .species=HAUNTER}
    }},
    {"PING@", TRAINERTYPE_NORMAL, .size=5, .pnormal=(struct TrainerPartyNormal[]){
        {.level=16, .species=GASTLY},
        {.level=16, .species=GASTLY},
        {.level=16, .species=GASTLY},
        {.level=16, .species=GASTLY},
        {.level=16, .species=GASTLY}
    }},
    {"EDMOND@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=3, .species=BELLSPROUT},
        {.level=3, .species=BELLSPROUT},
        {.level=3, .species=BELLSPROUT}
    }},
    {"NEAL@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=6, .species=BELLSPROUT}
    }},
    {"LI@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=7, .species=BELLSPROUT},
        {.level=7, .species=BELLSPROUT},
        {.level=10, .species=HOOTHOOT}
    }},
    {"GAKU@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=NOCTOWL},
        {.level=32, .species=FLAREON}
    }},
    {"MASA@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=NOCTOWL},
        {.level=32, .species=JOLTEON}
    }},
    {"KOJI@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=32, .species=NOCTOWL},
        {.level=32, .species=VAPOREON}
    }},
};

const struct TrainerParty MediumGroup[] = {
    {"MARTHA@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=18, .species=GASTLY},
        {.level=20, .species=HAUNTER},
        {.level=20, .species=GASTLY}
    }},
    {"GRACE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=HAUNTER},
        {.level=20, .species=HAUNTER}
    }},
    {"BETHANY@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=HAUNTER}
    }},
    {"MARGRET@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=HAUNTER}
    }},
    {"ETHEL@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=HAUNTER}
    }},
    {"REBECCA@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=DROWZEE},
        {.level=35, .species=HYPNO}
    }},
    {"DORIS@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=34, .species=SLOWPOKE},
        {.level=36, .species=SLOWBRO}
    }},
};

const struct TrainerParty BoarderGroup[] = {
    {"RONALD@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=SEEL},
        {.level=25, .species=DEWGONG},
        {.level=24, .species=SEEL}
    }},
    {"BRAD@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=SWINUB},
        {.level=26, .species=SWINUB}
    }},
    {"DOUGLAS@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=24, .species=SHELLDER},
        {.level=25, .species=CLOYSTER},
        {.level=24, .species=SHELLDER}
    }},
};

const struct TrainerParty PokefanMGroup[] = {
    {"WILLIAM@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=14, .species=RAICHU, .item=BERRY}
    }},
    {"DEREK@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=17, .species=PIKACHU, .item=BERRY}
    }},
    {"ROBERT@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=33, .species=QUAGSIRE, .item=BERRY}
    }},
    {"JOSHUA@", TRAINERTYPE_ITEM, .size=6, .pitem=(struct TrainerPartyItem[]){
        {.level=23, .species=PIKACHU, .item=BERRY},
        {.level=23, .species=PIKACHU, .item=BERRY},
        {.level=23, .species=PIKACHU, .item=BERRY},
        {.level=23, .species=PIKACHU, .item=BERRY},
        {.level=23, .species=PIKACHU, .item=BERRY},
        {.level=23, .species=PIKACHU, .item=BERRY}
    }},
    {"CARTER@", TRAINERTYPE_ITEM, .size=3, .pitem=(struct TrainerPartyItem[]){
        {.level=29, .species=BULBASAUR, .item=BERRY},
        {.level=29, .species=CHARMANDER, .item=BERRY},
        {.level=29, .species=SQUIRTLE, .item=BERRY}
    }},
    {"TREVOR@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=33, .species=PSYDUCK, .item=BERRY}
    }},
    {"BRANDON@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=13, .species=SNUBBULL, .item=BERRY}
    }},
    {"JEREMY@", TRAINERTYPE_ITEM, .size=3, .pitem=(struct TrainerPartyItem[]){
        {.level=28, .species=MEOWTH, .item=BERRY},
        {.level=28, .species=MEOWTH, .item=BERRY},
        {.level=28, .species=MEOWTH, .item=BERRY}
    }},
    {"COLIN@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=32, .species=DELIBIRD, .item=BERRY}
    }},
    {"DEREK@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=19, .species=PIKACHU, .item=BERRY}
    }},
    {"DEREK@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=36, .species=PIKACHU, .item=BERRY}
    }},
    {"ALEX@", TRAINERTYPE_ITEM, .size=3, .pitem=(struct TrainerPartyItem[]){
        {.level=29, .species=NIDOKING, .item=BERRY},
        {.level=29, .species=SLOWKING, .item=BERRY},
        {.level=29, .species=SEAKING, .item=BERRY}
    }},
    {"REX@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=35, .species=PHANPY, .item=BERRY}
    }},
    {"ALLAN@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=35, .species=TEDDIURSA, .item=BERRY}
    }},
};

const struct TrainerParty KimonoGirlGroup[] = {
    {"NAOKO@", TRAINERTYPE_NORMAL, .size=3, .pnormal=(struct TrainerPartyNormal[]){
        {.level=20, .species=SKIPLOOM},
        {.level=20, .species=VULPIX},
        {.level=18, .species=SKIPLOOM}
    }},
    {"NAOKO@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=FLAREON}
    }},
    {"SAYO@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=ESPEON}
    }},
    {"ZUKI@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=UMBREON}
    }},
    {"KUNI@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=VAPOREON}
    }},
    {"MIKI@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=JOLTEON}
    }},
};

const struct TrainerParty TwinsGroup[] = {
    {"AMY & MAY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=SPINARAK},
        {.level=10, .species=LEDYBA}
    }},
    {"ANN & ANNE@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=16, .species=CLEFAIRY, .moves={GROWL, ENCORE, DOUBLESLAP, METRONOME}},
        {.level=16, .species=JIGGLYPUFF, .moves={SING, DEFENSE_CURL, POUND, DISABLE}}
    }},
    {"ANN & ANNE@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=16, .species=JIGGLYPUFF, .moves={SING, DEFENSE_CURL, POUND, DISABLE}},
        {.level=16, .species=CLEFAIRY, .moves={GROWL, ENCORE, DOUBLESLAP, METRONOME}}
    }},
    {"AMY & MAY@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=10, .species=LEDYBA},
        {.level=10, .species=SPINARAK}
    }},
    {"JO & ZOE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=VICTREEBEL},
        {.level=35, .species=VILEPLUME}
    }},
    {"JO & ZOE@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=35, .species=VILEPLUME},
        {.level=35, .species=VICTREEBEL}
    }},
    {"MEG & PEG@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=TEDDIURSA},
        {.level=31, .species=PHANPY}
    }},
    {"MEG & PEG@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=31, .species=PHANPY},
        {.level=31, .species=TEDDIURSA}
    }},
    {"LEA & PIA@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=35, .species=DRATINI, .moves={THUNDER_WAVE, TWISTER, FLAMETHROWER, HEADBUTT}},
        {.level=35, .species=DRATINI, .moves={THUNDER_WAVE, TWISTER, ICE_BEAM, HEADBUTT}}
    }},
    {"LEA & PIA@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=38, .species=DRATINI, .moves={THUNDER_WAVE, TWISTER, ICE_BEAM, HEADBUTT}},
        {.level=38, .species=DRATINI, .moves={THUNDER_WAVE, TWISTER, FLAMETHROWER, HEADBUTT}}
    }},
};

const struct TrainerParty PokefanFGroup[] = {
    {"BEVERLY@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=14, .species=SNUBBULL, .item=BERRY}
    }},
    {"RUTH@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=17, .species=PIKACHU, .item=BERRY}
    }},
    {"BEVERLY@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=18, .species=SNUBBULL, .item=BERRY}
    }},
    {"BEVERLY@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=30, .species=GRANBULL, .item=BERRY}
    }},
    {"GEORGIA@", TRAINERTYPE_ITEM, .size=5, .pitem=(struct TrainerPartyItem[]){
        {.level=23, .species=SENTRET, .item=BERRY},
        {.level=23, .species=SENTRET, .item=BERRY},
        {.level=23, .species=SENTRET, .item=BERRY},
        {.level=28, .species=FURRET, .item=BERRY},
        {.level=23, .species=SENTRET, .item=BERRY}
    }},
    {"JAIME@", TRAINERTYPE_ITEM, .size=1, .pitem=(struct TrainerPartyItem[]){
        {.level=16, .species=MEOWTH, .item=BERRY}
    }},
};

const struct TrainerParty RedGroup[] = {
    {"RED@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=81, .species=PIKACHU, .moves={CHARM, QUICK_ATTACK, THUNDERBOLT, THUNDER}},
        {.level=73, .species=ESPEON, .moves={MUD_SLAP, REFLECT, SWIFT, PSYCHIC_M}},
        {.level=75, .species=SNORLAX, .moves={AMNESIA, SNORE, REST, BODY_SLAM}},
        {.level=77, .species=VENUSAUR, .moves={SUNNY_DAY, GIGA_DRAIN, SYNTHESIS, SOLARBEAM}},
        {.level=77, .species=CHARIZARD, .moves={FLAMETHROWER, WING_ATTACK, SLASH, FIRE_SPIN}},
        {.level=77, .species=BLASTOISE, .moves={RAIN_DANCE, SURF, BLIZZARD, WHIRLPOOL}}
    }},
};

const struct TrainerParty BlueGroup[] = {
    {"BLUE@", TRAINERTYPE_MOVES, .size=6, .pmoves=(struct TrainerPartyMoves[]){
        {.level=56, .species=PIDGEOT, .moves={QUICK_ATTACK, WHIRLWIND, WING_ATTACK, MIRROR_MOVE}},
        {.level=54, .species=ALAKAZAM, .moves={DISABLE, RECOVER, PSYCHIC_M, REFLECT}},
        {.level=56, .species=RHYDON, .moves={FURY_ATTACK, SANDSTORM, ROCK_SLIDE, EARTHQUAKE}},
        {.level=58, .species=GYARADOS, .moves={TWISTER, HYDRO_PUMP, RAIN_DANCE, HYPER_BEAM}},
        {.level=58, .species=EXEGGUTOR, .moves={SUNNY_DAY, LEECH_SEED, EGG_BOMB, SOLARBEAM}},
        {.level=58, .species=ARCANINE, .moves={ROAR, SWIFT, FLAMETHROWER, EXTREMESPEED}}
    }},
};

const struct TrainerParty OfficerGroup[] = {
    {"KEITH@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=17, .species=GROWLITHE}
    }},
    {"DIRK@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=14, .species=GROWLITHE},
        {.level=14, .species=GROWLITHE}
    }},
};

const struct TrainerParty GruntFGroup[] = {
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=9, .species=ZUBAT},
        {.level=11, .species=EKANS}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=1, .pnormal=(struct TrainerPartyNormal[]){
        {.level=26, .species=ARBOK}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=2, .pnormal=(struct TrainerPartyNormal[]){
        {.level=25, .species=GLOOM},
        {.level=25, .species=GLOOM}
    }},
    {"GRUNT@", TRAINERTYPE_NORMAL, .size=4, .pnormal=(struct TrainerPartyNormal[]){
        {.level=21, .species=EKANS},
        {.level=23, .species=ODDISH},
        {.level=21, .species=EKANS},
        {.level=24, .species=GLOOM}
    }},
    {"GRUNT@", TRAINERTYPE_MOVES, .size=2, .pmoves=(struct TrainerPartyMoves[]){
        {.level=18, .species=EKANS, .moves={WRAP, LEER, POISON_STING, BITE}},
        {.level=18, .species=GLOOM, .moves={ABSORB, SWEET_SCENT, STUN_SPORE, SLEEP_POWDER}}
    }},
};

const struct TrainerParty MysticalmanGroup[] = {
    {"EUSINE@", TRAINERTYPE_MOVES, .size=3, .pmoves=(struct TrainerPartyMoves[]){
        {.level=23, .species=DROWZEE, .moves={DREAM_EATER, HYPNOSIS, DISABLE, CONFUSION}},
        {.level=25, .species=HAUNTER, .moves={LICK, HYPNOSIS, MEAN_LOOK, CURSE}},
        {.level=25, .species=ELECTRODE, .moves={SCREECH, SONICBOOM, THUNDER, ROLLOUT}}
    }},
};

#define TRAINERGROUP(_a) {_a, lengthof(_a)}

const struct TrainerGroup TrainerGroups[] = {
    TRAINERGROUP(FalknerGroup),
    TRAINERGROUP(WhitneyGroup),
    TRAINERGROUP(BugsyGroup),
    TRAINERGROUP(MortyGroup),
    TRAINERGROUP(PryceGroup),
    TRAINERGROUP(JasmineGroup),
    TRAINERGROUP(ChuckGroup),
    TRAINERGROUP(ClairGroup),
    TRAINERGROUP(Rival1Group),
    TRAINERGROUP(PokemonProfGroup),
    TRAINERGROUP(WillGroup),
    TRAINERGROUP(PKMNTrainerGroup),
    TRAINERGROUP(BrunoGroup),
    TRAINERGROUP(KarenGroup),
    TRAINERGROUP(KogaGroup),
    TRAINERGROUP(ChampionGroup),
    TRAINERGROUP(BrockGroup),
    TRAINERGROUP(MistyGroup),
    TRAINERGROUP(LtSurgeGroup),
    TRAINERGROUP(ScientistGroup),
    TRAINERGROUP(ErikaGroup),
    TRAINERGROUP(YoungsterGroup),
    TRAINERGROUP(SchoolboyGroup),
    TRAINERGROUP(BirdKeeperGroup),
    TRAINERGROUP(LassGroup),
    TRAINERGROUP(JanineGroup),
    TRAINERGROUP(CooltrainerMGroup),
    TRAINERGROUP(CooltrainerFGroup),
    TRAINERGROUP(BeautyGroup),
    TRAINERGROUP(PokemaniacGroup),
    TRAINERGROUP(GruntMGroup),
    TRAINERGROUP(GentlemanGroup),
    TRAINERGROUP(SkierGroup),
    TRAINERGROUP(TeacherGroup),
    TRAINERGROUP(SabrinaGroup),
    TRAINERGROUP(BugCatcherGroup),
    TRAINERGROUP(FisherGroup),
    TRAINERGROUP(SwimmerMGroup),
    TRAINERGROUP(SwimmerFGroup),
    TRAINERGROUP(SailorGroup),
    TRAINERGROUP(SuperNerdGroup),
    TRAINERGROUP(Rival2Group),
    TRAINERGROUP(GuitaristGroup),
    TRAINERGROUP(HikerGroup),
    TRAINERGROUP(BikerGroup),
    TRAINERGROUP(BlaineGroup),
    TRAINERGROUP(BurglarGroup),
    TRAINERGROUP(FirebreatherGroup),
    TRAINERGROUP(JugglerGroup),
    TRAINERGROUP(BlackbeltGroup),
    TRAINERGROUP(ExecutiveMGroup),
    TRAINERGROUP(PsychicGroup),
    TRAINERGROUP(PicnickerGroup),
    TRAINERGROUP(CamperGroup),
    TRAINERGROUP(ExecutiveFGroup),
    TRAINERGROUP(SageGroup),
    TRAINERGROUP(MediumGroup),
    TRAINERGROUP(BoarderGroup),
    TRAINERGROUP(PokefanMGroup),
    TRAINERGROUP(KimonoGirlGroup),
    TRAINERGROUP(TwinsGroup),
    TRAINERGROUP(PokefanFGroup),
    TRAINERGROUP(RedGroup),
    TRAINERGROUP(BlueGroup),
    TRAINERGROUP(OfficerGroup),
    TRAINERGROUP(GruntFGroup),
    TRAINERGROUP(MysticalmanGroup),
};

static_assert(lengthof(TrainerGroups) == NUM_TRAINER_CLASSES, "");