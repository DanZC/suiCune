#include <string.h>
#include <assert.h>
#include "../util/uthash.h"
#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif // _MSVC_VER
#include "../constants.h"

struct StringIDPair {
    const char* string;
    uint32_t id;
    UT_hash_handle hh;
};


struct StringIDPair *constant_strings = NULL;

#define STR_IMPL(_name) #_name
#define STR(_name) STR_IMPL(_name)
#define entry(_name) add_entry(#_name, _name)
#define entry_custom(_name, _id) add_entry(_name, _id)

#define tm_entry(tmNum, tmName)       do {  \
        entry(tmNum);                       \
        entry(TM_##tmName);                 \
        entry(tmName##_TMNUM);              \
    } while(0)

#define hm_entry(hmNum, hmName)       do {  \
        entry(hmNum);                       \
        entry(HM_##hmName);                 \
    } while(0)

#define map_entry(map)                                do {\
        entry_custom(#map, ((GROUP_##map) << 8) | (MAP_##map));\
        entry(GROUP_##map);                                     \
        entry(MAP_##map);                                       \
    } while(0)

static void add_entry(const char* str, uint32_t id) {
    struct StringIDPair* item = malloc(sizeof(*item));
    item->id = id;
    item->string = str;
    HASH_ADD_STR(constant_strings,string, item);
}

void PopulateConstantsHashtable(void) {
// Items
    entry(NO_ITEM);
    entry(MASTER_BALL);
    entry(ULTRA_BALL);
    entry(BRIGHTPOWDER);
    entry(GREAT_BALL);
    entry(POKE_BALL);
    entry(TOWN_MAP);
    entry(BICYCLE);
    entry(MOON_STONE);
    entry(ANTIDOTE);
    entry(BURN_HEAL);
    entry(ICE_HEAL);
    entry(AWAKENING);
    entry(PARLYZ_HEAL);
    entry(FULL_RESTORE);
    entry(MAX_POTION);
    entry(HYPER_POTION);
    entry(SUPER_POTION);
    entry(POTION);
    entry(ESCAPE_ROPE);
    entry(REPEL);
    entry(MAX_ELIXER);
    entry(FIRE_STONE);
    entry(THUNDERSTONE);
    entry(WATER_STONE);
    entry(ITEM_19);
    entry(HP_UP);
    entry(PROTEIN);
    entry(IRON);
    entry(CARBOS);
    entry(LUCKY_PUNCH);
    entry(CALCIUM);
    entry(RARE_CANDY);
    entry(X_ACCURACY);
    entry(LEAF_STONE);
    entry(METAL_POWDER);
    entry(NUGGET);
    entry(POKE_DOLL);
    entry(FULL_HEAL);
    entry(REVIVE);
    entry(MAX_REVIVE);
    entry(GUARD_SPEC);
    entry(SUPER_REPEL);
    entry(MAX_REPEL);
    entry(DIRE_HIT);
    entry(ITEM_2D);
    entry(FRESH_WATER);
    entry(SODA_POP);
    entry(LEMONADE);
    entry(X_ATTACK);
    entry(ITEM_32);
    entry(X_DEFEND);
    entry(X_SPEED);
    entry(X_SPECIAL);
    entry(COIN_CASE);
    entry(ITEMFINDER);
    entry(POKE_FLUTE);
    entry(EXP_SHARE);
    entry(OLD_ROD);
    entry(GOOD_ROD);
    entry(SILVER_LEAF);
    entry(SUPER_ROD);
    entry(PP_UP);
    entry(ETHER);
    entry(MAX_ETHER);
    entry(ELIXER);
    entry(RED_SCALE);
    entry(SECRETPOTION);
    entry(S_S_TICKET);
    entry(MYSTERY_EGG);
    entry(CLEAR_BELL);
    entry(SILVER_WING);
    entry(MOOMOO_MILK);
    entry(QUICK_CLAW);
    entry(PSNCUREBERRY);
    entry(GOLD_LEAF);
    entry(SOFT_SAND);
    entry(SHARP_BEAK);
    entry(PRZCUREBERRY);
    entry(BURNT_BERRY);
    entry(ICE_BERRY);
    entry(POISON_BARB);
    entry(KINGS_ROCK);
    entry(BITTER_BERRY);
    entry(MINT_BERRY);
    entry(RED_APRICORN);
    entry(TINYMUSHROOM);
    entry(BIG_MUSHROOM);
    entry(SILVERPOWDER);
    entry(BLU_APRICORN);
    entry(ITEM_5A);
    entry(AMULET_COIN);
    entry(YLW_APRICORN);
    entry(GRN_APRICORN);
    entry(CLEANSE_TAG);
    entry(MYSTIC_WATER);
    entry(TWISTEDSPOON);
    entry(WHT_APRICORN);
    entry(BLACKBELT_I);
    entry(BLK_APRICORN);
    entry(ITEM_64);
    entry(PNK_APRICORN);
    entry(BLACKGLASSES);
    entry(SLOWPOKETAIL);
    entry(PINK_BOW);
    entry(STICK);
    entry(SMOKE_BALL);
    entry(NEVERMELTICE);
    entry(MAGNET);
    entry(MIRACLEBERRY);
    entry(PEARL);
    entry(BIG_PEARL);
    entry(EVERSTONE);
    entry(SPELL_TAG);
    entry(RAGECANDYBAR);
    entry(GS_BALL);
    entry(BLUE_CARD);
    entry(MIRACLE_SEED);
    entry(THICK_CLUB);
    entry(FOCUS_BAND);
    entry(ITEM_78);
    entry(ENERGYPOWDER);
    entry(ENERGY_ROOT);
    entry(HEAL_POWDER);
    entry(REVIVAL_HERB);
    entry(HARD_STONE);
    entry(LUCKY_EGG);
    entry(CARD_KEY);
    entry(MACHINE_PART);
    entry(EGG_TICKET);
    entry(LOST_ITEM);
    entry(STARDUST);
    entry(STAR_PIECE);
    entry(BASEMENT_KEY);
    entry(PASS);
    entry(ITEM_87);
    entry(ITEM_88);
    entry(ITEM_89);
    entry(CHARCOAL);
    entry(BERRY_JUICE);
    entry(SCOPE_LENS);
    entry(ITEM_8D);
    entry(ITEM_8E);
    entry(METAL_COAT);
    entry(DRAGON_FANG);
    entry(ITEM_91);
    entry(LEFTOVERS);
    entry(ITEM_93);
    entry(ITEM_94);
    entry(ITEM_95);
    entry(MYSTERYBERRY);
    entry(DRAGON_SCALE);
    entry(BERSERK_GENE);
    entry(ITEM_99);
    entry(ITEM_9A);
    entry(ITEM_9B);
    entry(SACRED_ASH);
    entry(HEAVY_BALL);
    entry(FLOWER_MAIL);
    entry(LEVEL_BALL);
    entry(LURE_BALL);
    entry(FAST_BALL);
    entry(ITEM_A2);
    entry(LIGHT_BALL);
    entry(FRIEND_BALL);
    entry(MOON_BALL);
    entry(LOVE_BALL);
    entry(NORMAL_BOX);
    entry(GORGEOUS_BOX);
    entry(SUN_STONE);
    entry(POLKADOT_BOW);
    entry(ITEM_AB);
    entry(UP_GRADE);
    entry(BERRY);
    entry(GOLD_BERRY);
    entry(SQUIRTBOTTLE);
    entry(ITEM_B0);
    entry(PARK_BALL);
    entry(RAINBOW_WING);
    entry(ITEM_B3);
    entry(BRICK_PIECE);
    entry(SURF_MAIL);
    entry(LITEBLUEMAIL);
    entry(PORTRAITMAIL);
    entry(LOVELY_MAIL);
    entry(EON_MAIL);
    entry(MORPH_MAIL);
    entry(BLUESKY_MAIL);
    entry(MUSIC_MAIL);
    entry(MIRAGE_MAIL);
    entry(ITEM_BE);

    entry(TM01);
    entry(TM_DYNAMICPUNCH);
    tm_entry(TM02, HEADBUTT);
    tm_entry(TM03, CURSE);
    tm_entry(TM04, ROLLOUT);
    tm_entry(TM05, ROAR);
    tm_entry(TM06, TOXIC);
    tm_entry(TM07, ZAP_CANNON);
    tm_entry(TM08, ROCK_SMASH);
    tm_entry(TM09, PSYCH_UP);
    tm_entry(TM10, HIDDEN_POWER);
    tm_entry(TM11, SUNNY_DAY);
    tm_entry(TM12, SWEET_SCENT);
    tm_entry(TM13, SNORE);
    tm_entry(TM14, BLIZZARD);
    tm_entry(TM15, HYPER_BEAM);
    tm_entry(TM16, ICY_WIND);
    tm_entry(TM17, PROTECT);
    tm_entry(TM18, RAIN_DANCE);
    tm_entry(TM19, GIGA_DRAIN);
    tm_entry(TM20, ENDURE);
    tm_entry(TM21, FRUSTRATION);
    tm_entry(TM22, SOLARBEAM);
    tm_entry(TM23, IRON_TAIL);
    tm_entry(TM24, DRAGONBREATH);
    tm_entry(TM25, THUNDER);
    tm_entry(TM26, EARTHQUAKE);
    tm_entry(TM27, RETURN);
    tm_entry(TM28, DIG);
    entry_custom("ITEM_DC", ITEM_DC);
    tm_entry(TM29, PSYCHIC_M);
    tm_entry(TM30, SHADOW_BALL);
    tm_entry(TM31, MUD_SLAP);
    tm_entry(TM32, DOUBLE_TEAM);
    tm_entry(TM33, ICE_PUNCH);
    tm_entry(TM34, SWAGGER);
    tm_entry(TM35, SLEEP_TALK);
    tm_entry(TM36, SLUDGE_BOMB);
    tm_entry(TM37, SANDSTORM);
    tm_entry(TM38, FIRE_BLAST);
    tm_entry(TM39, SWIFT);
    tm_entry(TM40, DEFENSE_CURL);
    tm_entry(TM41, THUNDERPUNCH);
    tm_entry(TM42, DREAM_EATER);
    tm_entry(TM43, DETECT);
    tm_entry(TM44, REST);
    tm_entry(TM45, ATTRACT);
    tm_entry(TM46, THIEF);
    tm_entry(TM47, STEEL_WING);
    tm_entry(TM48, FIRE_PUNCH);
    tm_entry(TM49, FURY_CUTTER);
    tm_entry(TM50, NIGHTMARE);
    entry(HM01);
    entry(HM_CUT);
    hm_entry(HM02, FLY);
    hm_entry(HM03, SURF);
    hm_entry(HM04, STRENGTH);
    hm_entry(HM05, FLASH);
    hm_entry(HM06, WHIRLPOOL);
    hm_entry(HM07, WATERFALL);

// Species
    entry(BULBASAUR);
    entry(IVYSAUR);
    entry(VENUSAUR);
    entry(CHARMANDER);
    entry(CHARMELEON);
    entry(CHARIZARD);
    entry(SQUIRTLE);
    entry(WARTORTLE);
    entry(BLASTOISE);
    entry(CATERPIE);
    entry(METAPOD);
    entry(BUTTERFREE);
    entry(WEEDLE);
    entry(KAKUNA);
    entry(BEEDRILL);
    entry(PIDGEY);
    entry(PIDGEOTTO);
    entry(PIDGEOT);
    entry(RATTATA);
    entry(RATICATE);
    entry(SPEAROW);
    entry(FEAROW);
    entry(EKANS);
    entry(ARBOK);
    entry(PIKACHU);
    entry(RAICHU);
    entry(SANDSHREW);
    entry(SANDSLASH);
    entry(NIDORAN_F);
    entry(NIDORINA);
    entry(NIDOQUEEN);
    entry(NIDORAN_M);
    entry(NIDORINO);
    entry(NIDOKING);
    entry(CLEFAIRY);
    entry(CLEFABLE);
    entry(VULPIX);
    entry(NINETALES);
    entry(JIGGLYPUFF);
    entry(WIGGLYTUFF);
    entry(ZUBAT);
    entry(GOLBAT);
    entry(ODDISH);
    entry(GLOOM);
    entry(VILEPLUME);
    entry(PARAS);
    entry(PARASECT);
    entry(VENONAT);
    entry(VENOMOTH);
    entry(DIGLETT);
    entry(DUGTRIO);
    entry(MEOWTH);
    entry(PERSIAN);
    entry(PSYDUCK);
    entry(GOLDUCK);
    entry(MANKEY);
    entry(PRIMEAPE);
    entry(GROWLITHE);
    entry(ARCANINE);
    entry(POLIWAG);
    entry(POLIWHIRL);
    entry(POLIWRATH);
    entry(ABRA);
    entry(KADABRA);
    entry(ALAKAZAM);
    entry(MACHOP);
    entry(MACHOKE);
    entry(MACHAMP);
    entry(BELLSPROUT);
    entry(WEEPINBELL);
    entry(VICTREEBEL);
    entry(TENTACOOL);
    entry(TENTACRUEL);
    entry(GEODUDE);
    entry(GRAVELER);
    entry(GOLEM);
    entry(PONYTA);
    entry(RAPIDASH);
    entry(SLOWPOKE);
    entry(SLOWBRO);
    entry(MAGNEMITE);
    entry(MAGNETON);
    entry(FARFETCH_D);
    entry(DODUO);
    entry(DODRIO);
    entry(SEEL);
    entry(DEWGONG);
    entry(GRIMER);
    entry(MUK);
    entry(SHELLDER);
    entry(CLOYSTER);
    entry(GASTLY);
    entry(HAUNTER);
    entry(GENGAR);
    entry(ONIX);
    entry(DROWZEE);
    entry(HYPNO);
    entry(KRABBY);
    entry(KINGLER);
    entry(VOLTORB);
    entry(ELECTRODE);
    entry(EXEGGCUTE);
    entry(EXEGGUTOR);
    entry(CUBONE);
    entry(MAROWAK);
    entry(HITMONLEE);
    entry(HITMONCHAN);
    entry(LICKITUNG);
    entry(KOFFING);
    entry(WEEZING);
    entry(RHYHORN);
    entry(RHYDON);
    entry(CHANSEY);
    entry(TANGELA);
    entry(KANGASKHAN);
    entry(HORSEA);
    entry(SEADRA);
    entry(GOLDEEN);
    entry(SEAKING);
    entry(STARYU);
    entry(STARMIE);
    entry(MR__MIME);
    entry(SCYTHER);
    entry(JYNX);
    entry(ELECTABUZZ);
    entry(MAGMAR);
    entry(PINSIR);
    entry(TAUROS);
    entry(MAGIKARP);
    entry(GYARADOS);
    entry(LAPRAS);
    entry(DITTO);
    entry(EEVEE);
    entry(VAPOREON);
    entry(JOLTEON);
    entry(FLAREON);
    entry(PORYGON);
    entry(OMANYTE);
    entry(OMASTAR);
    entry(KABUTO);
    entry(KABUTOPS);
    entry(AERODACTYL);
    entry(SNORLAX);
    entry(ARTICUNO);
    entry(ZAPDOS);
    entry(MOLTRES);
    entry(DRATINI);
    entry(DRAGONAIR);
    entry(DRAGONITE);
    entry(MEWTWO);
    entry(MEW);
    entry(CHIKORITA);
    entry(BAYLEEF);
    entry(MEGANIUM);
    entry(CYNDAQUIL);
    entry(QUILAVA);
    entry(TYPHLOSION);
    entry(TOTODILE);
    entry(CROCONAW);
    entry(FERALIGATR);
    entry(SENTRET);
    entry(FURRET);
    entry(HOOTHOOT);
    entry(NOCTOWL);
    entry(LEDYBA);
    entry(LEDIAN);
    entry(SPINARAK);
    entry(ARIADOS);
    entry(CROBAT);
    entry(CHINCHOU);
    entry(LANTURN);
    entry(PICHU);
    entry(CLEFFA);
    entry(IGGLYBUFF);
    entry(TOGEPI);
    entry(TOGETIC);
    entry(NATU);
    entry(XATU);
    entry(MAREEP);
    entry(FLAAFFY);
    entry(AMPHAROS);
    entry(BELLOSSOM);
    entry(MARILL);
    entry(AZUMARILL);
    entry(SUDOWOODO);
    entry(POLITOED);
    entry(HOPPIP);
    entry(SKIPLOOM);
    entry(JUMPLUFF);
    entry(AIPOM);
    entry(SUNKERN);
    entry(SUNFLORA);
    entry(YANMA);
    entry(WOOPER);
    entry(QUAGSIRE);
    entry(ESPEON);
    entry(UMBREON);
    entry(MURKROW);
    entry(SLOWKING);
    entry(MISDREAVUS);
    entry(UNOWN);
    entry(WOBBUFFET);
    entry(GIRAFARIG);
    entry(PINECO);
    entry(FORRETRESS);
    entry(DUNSPARCE);
    entry(GLIGAR);
    entry(STEELIX);
    entry(SNUBBULL);
    entry(GRANBULL);
    entry(QWILFISH);
    entry(SCIZOR);
    entry(SHUCKLE);
    entry(HERACROSS);
    entry(SNEASEL);
    entry(TEDDIURSA);
    entry(URSARING);
    entry(SLUGMA);
    entry(MAGCARGO);
    entry(SWINUB);
    entry(PILOSWINE);
    entry(CORSOLA);
    entry(REMORAID);
    entry(OCTILLERY);
    entry(DELIBIRD);
    entry(MANTINE);
    entry(SKARMORY);
    entry(HOUNDOUR);
    entry(HOUNDOOM);
    entry(KINGDRA);
    entry(PHANPY);
    entry(DONPHAN);
    entry(PORYGON2);
    entry(STANTLER);
    entry(SMEARGLE);
    entry(TYROGUE);
    entry(HITMONTOP);
    entry(SMOOCHUM);
    entry(ELEKID);
    entry(MAGBY);
    entry(MILTANK);
    entry(BLISSEY);
    entry(RAIKOU);
    entry(ENTEI);
    entry(SUICUNE);
    entry(LARVITAR);
    entry(PUPITAR);
    entry(TYRANITAR);
    entry(LUGIA);
    entry(HO_OH);
    entry(CELEBI);
    entry(EGG);

// Moves
    entry(NO_MOVE);
    entry(POUND);
    entry(KARATE_CHOP);
    entry(DOUBLESLAP);
    entry(COMET_PUNCH);
    entry(MEGA_PUNCH);
    entry(PAY_DAY);
    entry(FIRE_PUNCH);
    entry(ICE_PUNCH);
    entry(THUNDERPUNCH);
    entry(SCRATCH);
    entry(VICEGRIP);
    entry(GUILLOTINE);
    entry(RAZOR_WIND);
    entry(SWORDS_DANCE);
    entry(CUT);
    entry(GUST);
    entry(WING_ATTACK);
    entry(WHIRLWIND);
    entry(FLY);
    entry(BIND);
    entry(SLAM);
    entry(VINE_WHIP);
    entry(STOMP);
    entry(DOUBLE_KICK);
    entry(MEGA_KICK);
    entry(JUMP_KICK);
    entry(ROLLING_KICK);
    entry(SAND_ATTACK);
    entry(HEADBUTT);
    entry(HORN_ATTACK);
    entry(FURY_ATTACK);
    entry(HORN_DRILL);
    entry(TACKLE);
    entry(BODY_SLAM);
    entry(WRAP);
    entry(TAKE_DOWN);
    entry(THRASH);
    entry(DOUBLE_EDGE);
    entry(TAIL_WHIP);
    entry(POISON_STING);
    entry(TWINEEDLE);
    entry(PIN_MISSILE);
    entry(LEER);
    entry(BITE);
    entry(GROWL);
    entry(ROAR);
    entry(SING);
    entry(SUPERSONIC);
    entry(SONICBOOM);
    entry(DISABLE);
    entry(ACID);
    entry(EMBER);
    entry(FLAMETHROWER);
    entry(MIST);
    entry(WATER_GUN);
    entry(HYDRO_PUMP);
    entry(SURF);
    entry(ICE_BEAM);
    entry(BLIZZARD);
    entry(PSYBEAM);
    entry(BUBBLEBEAM);
    entry(AURORA_BEAM);
    entry(HYPER_BEAM);
    entry(PECK);
    entry(DRILL_PECK);
    entry(SUBMISSION);
    entry(LOW_KICK);
    entry(COUNTER);
    entry(SEISMIC_TOSS);
    entry(STRENGTH);
    entry(ABSORB);
    entry(MEGA_DRAIN);
    entry(LEECH_SEED);
    entry(GROWTH);
    entry(RAZOR_LEAF);
    entry(SOLARBEAM);
    entry(POISONPOWDER);
    entry(STUN_SPORE);
    entry(SLEEP_POWDER);
    entry(PETAL_DANCE);
    entry(STRING_SHOT);
    entry(DRAGON_RAGE);
    entry(FIRE_SPIN);
    entry(THUNDERSHOCK);
    entry(THUNDERBOLT);
    entry(THUNDER_WAVE);
    entry(THUNDER);
    entry(ROCK_THROW);
    entry(EARTHQUAKE);
    entry(FISSURE);
    entry(DIG);
    entry(TOXIC);
    entry(CONFUSION);
    entry(PSYCHIC_M);
    entry(HYPNOSIS);
    entry(MEDITATE);
    entry(AGILITY);
    entry(QUICK_ATTACK);
    entry(RAGE);
    entry(TELEPORT);
    entry(NIGHT_SHADE);
    entry(MIMIC);
    entry(SCREECH);
    entry(DOUBLE_TEAM);
    entry(RECOVER);
    entry(HARDEN);
    entry(MINIMIZE);
    entry(SMOKESCREEN);
    entry(CONFUSE_RAY);
    entry(WITHDRAW);
    entry(DEFENSE_CURL);
    entry(BARRIER);
    entry(LIGHT_SCREEN);
    entry(HAZE);
    entry(REFLECT);
    entry(FOCUS_ENERGY);
    entry(BIDE);
    entry(METRONOME);
    entry(MIRROR_MOVE);
    entry(SELFDESTRUCT);
    entry(EGG_BOMB);
    entry(LICK);
    entry(SMOG);
    entry(SLUDGE);
    entry(BONE_CLUB);
    entry(FIRE_BLAST);
    entry(WATERFALL);
    entry(CLAMP);
    entry(SWIFT);
    entry(SKULL_BASH);
    entry(SPIKE_CANNON);
    entry(CONSTRICT);
    entry(AMNESIA);
    entry(KINESIS);
    entry(SOFTBOILED);
    entry(HI_JUMP_KICK);
    entry(GLARE);
    entry(DREAM_EATER);
    entry(POISON_GAS);
    entry(BARRAGE);
    entry(LEECH_LIFE);
    entry(LOVELY_KISS);
    entry(SKY_ATTACK);
    entry(TRANSFORM);
    entry(BUBBLE);
    entry(DIZZY_PUNCH);
    entry(SPORE);
    entry(FLASH);
    entry(PSYWAVE);
    entry(SPLASH);
    entry(ACID_ARMOR);
    entry(CRABHAMMER);
    entry(EXPLOSION);
    entry(FURY_SWIPES);
    entry(BONEMERANG);
    entry(REST);
    entry(ROCK_SLIDE);
    entry(HYPER_FANG);
    entry(SHARPEN);
    entry(CONVERSION);
    entry(TRI_ATTACK);
    entry(SUPER_FANG);
    entry(SLASH);
    entry(SUBSTITUTE);
    entry(STRUGGLE);
    entry(SKETCH);
    entry(TRIPLE_KICK);
    entry(THIEF);
    entry(SPIDER_WEB);
    entry(MIND_READER);
    entry(NIGHTMARE);
    entry(FLAME_WHEEL);
    entry(SNORE);
    entry(CURSE);
    entry(FLAIL);
    entry(CONVERSION2);
    entry(AEROBLAST);
    entry(COTTON_SPORE);
    entry(REVERSAL);
    entry(SPITE);
    entry(POWDER_SNOW);
    entry(PROTECT);
    entry(MACH_PUNCH);
    entry(SCARY_FACE);
    entry(FAINT_ATTACK);
    entry(SWEET_KISS);
    entry(BELLY_DRUM);
    entry(SLUDGE_BOMB);
    entry(MUD_SLAP);
    entry(OCTAZOOKA);
    entry(SPIKES);
    entry(ZAP_CANNON);
    entry(FORESIGHT);
    entry(DESTINY_BOND);
    entry(PERISH_SONG);
    entry(ICY_WIND);
    entry(DETECT);
    entry(BONE_RUSH);
    entry(LOCK_ON);
    entry(OUTRAGE);
    entry(SANDSTORM);
    entry(GIGA_DRAIN);
    entry(ENDURE);
    entry(CHARM);
    entry(ROLLOUT);
    entry(FALSE_SWIPE);
    entry(SWAGGER);
    entry(MILK_DRINK);
    entry(SPARK);
    entry(FURY_CUTTER);
    entry(STEEL_WING);
    entry(MEAN_LOOK);
    entry(ATTRACT);
    entry(SLEEP_TALK);
    entry(HEAL_BELL);
    entry(RETURN);
    entry(PRESENT);
    entry(FRUSTRATION);
    entry(SAFEGUARD);
    entry(PAIN_SPLIT);
    entry(SACRED_FIRE);
    entry(MAGNITUDE);
    entry(DYNAMICPUNCH);
    entry(MEGAHORN);
    entry(DRAGONBREATH);
    entry(BATON_PASS);
    entry(ENCORE);
    entry(PURSUIT);
    entry(RAPID_SPIN);
    entry(SWEET_SCENT);
    entry(IRON_TAIL);
    entry(METAL_CLAW);
    entry(VITAL_THROW);
    entry(MORNING_SUN);
    entry(SYNTHESIS);
    entry(MOONLIGHT);
    entry(HIDDEN_POWER);
    entry(CROSS_CHOP);
    entry(TWISTER);
    entry(RAIN_DANCE);
    entry(SUNNY_DAY);
    entry(CRUNCH);
    entry(MIRROR_COAT);
    entry(PSYCH_UP);
    entry(EXTREMESPEED);
    entry(ANCIENTPOWER);
    entry(SHADOW_BALL);
    entry(FUTURE_SIGHT);
    entry(ROCK_SMASH);
    entry(WHIRLPOOL);
    entry(BEAT_UP);

// Marts
    entry(MART_CHERRYGROVE);
    entry(MART_CHERRYGROVE_DEX);
    entry(MART_VIOLET);
    entry(MART_AZALEA);
    entry(MART_CIANWOOD);
    entry(MART_GOLDENROD_2F_1);
    entry(MART_GOLDENROD_2F_2);
    entry(MART_GOLDENROD_3F);
    entry(MART_GOLDENROD_4F);
    entry(MART_GOLDENROD_5F_1);
    entry(MART_GOLDENROD_5F_2);
    entry(MART_GOLDENROD_5F_3);
    entry(MART_GOLDENROD_5F_4);
    entry(MART_OLIVINE);
    entry(MART_ECRUTEAK);
    entry(MART_MAHOGANY_1);
    entry(MART_MAHOGANY_2);
    entry(MART_BLACKTHORN);
    entry(MART_VIRIDIAN);
    entry(MART_PEWTER);
    entry(MART_CERULEAN);
    entry(MART_LAVENDER);
    entry(MART_VERMILION);
    entry(MART_CELADON_2F_1);
    entry(MART_CELADON_2F_2);
    entry(MART_CELADON_3F);
    entry(MART_CELADON_4F);
    entry(MART_CELADON_5F_1);
    entry(MART_CELADON_5F_2);
    entry(MART_FUCHSIA);
    entry(MART_SAFFRON);
    entry(MART_MT_MOON);
    entry(MART_INDIGO_PLATEAU);
    entry(MART_UNDERGROUND);

    map_entry(OLIVINE_POKECENTER_1F);
    map_entry(OLIVINE_GYM);
    map_entry(OLIVINE_TIMS_HOUSE);
    map_entry(OLIVINE_HOUSE_BETA);
    map_entry(OLIVINE_PUNISHMENT_SPEECH_HOUSE);
    map_entry(OLIVINE_GOOD_ROD_HOUSE);
    map_entry(OLIVINE_CAFE);
    map_entry(OLIVINE_MART);
    map_entry(ROUTE_38_ECRUTEAK_GATE);
    map_entry(ROUTE_39_BARN);
    map_entry(ROUTE_39_FARMHOUSE);
    map_entry(ROUTE_38);
    map_entry(ROUTE_39);
    map_entry(OLIVINE_CITY);

    map_entry(MAHOGANY_RED_GYARADOS_SPEECH_HOUSE);
    map_entry(MAHOGANY_GYM);
    map_entry(MAHOGANY_POKECENTER_1F);
    map_entry(ROUTE_42_ECRUTEAK_GATE);
    map_entry(ROUTE_42);
    map_entry(ROUTE_44);
    map_entry(MAHOGANY_TOWN);

    map_entry(SPROUT_TOWER_1F);
    map_entry(SPROUT_TOWER_2F);
    map_entry(SPROUT_TOWER_3F);
    map_entry(TIN_TOWER_1F);
    map_entry(TIN_TOWER_2F);
    map_entry(TIN_TOWER_3F);
    map_entry(TIN_TOWER_4F);
    map_entry(TIN_TOWER_5F);
    map_entry(TIN_TOWER_6F);
    map_entry(TIN_TOWER_7F);
    map_entry(TIN_TOWER_8F);
    map_entry(TIN_TOWER_9F);
    map_entry(BURNED_TOWER_1F);
    map_entry(BURNED_TOWER_B1F);
    map_entry(NATIONAL_PARK);
    map_entry(NATIONAL_PARK_BUG_CONTEST);
    map_entry(RADIO_TOWER_1F);
    map_entry(RADIO_TOWER_2F);
    map_entry(RADIO_TOWER_3F);
    map_entry(RADIO_TOWER_4F);
    map_entry(RADIO_TOWER_5F);
    map_entry(RUINS_OF_ALPH_OUTSIDE);
    map_entry(RUINS_OF_ALPH_HO_OH_CHAMBER);
    map_entry(RUINS_OF_ALPH_KABUTO_CHAMBER);
    map_entry(RUINS_OF_ALPH_OMANYTE_CHAMBER);
    map_entry(RUINS_OF_ALPH_AERODACTYL_CHAMBER);
    map_entry(RUINS_OF_ALPH_INNER_CHAMBER);
    map_entry(RUINS_OF_ALPH_RESEARCH_CENTER);
    map_entry(RUINS_OF_ALPH_HO_OH_ITEM_ROOM);
    map_entry(RUINS_OF_ALPH_KABUTO_ITEM_ROOM);
    map_entry(RUINS_OF_ALPH_OMANYTE_ITEM_ROOM);
    map_entry(RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM);
    map_entry(RUINS_OF_ALPH_HO_OH_WORD_ROOM);
    map_entry(RUINS_OF_ALPH_KABUTO_WORD_ROOM);
    map_entry(RUINS_OF_ALPH_OMANYTE_WORD_ROOM);
    map_entry(RUINS_OF_ALPH_AERODACTYL_WORD_ROOM);
    map_entry(UNION_CAVE_1F);
    map_entry(UNION_CAVE_B1F);
    map_entry(UNION_CAVE_B2F);
    map_entry(SLOWPOKE_WELL_B1F);
    map_entry(SLOWPOKE_WELL_B2F);
    map_entry(OLIVINE_LIGHTHOUSE_1F);
    map_entry(OLIVINE_LIGHTHOUSE_2F);
    map_entry(OLIVINE_LIGHTHOUSE_3F);
    map_entry(OLIVINE_LIGHTHOUSE_4F);
    map_entry(OLIVINE_LIGHTHOUSE_5F);
    map_entry(OLIVINE_LIGHTHOUSE_6F);
    map_entry(MAHOGANY_MART_1F);
    map_entry(TEAM_ROCKET_BASE_B1F);
    map_entry(TEAM_ROCKET_BASE_B2F);
    map_entry(TEAM_ROCKET_BASE_B3F);
    map_entry(ILEX_FOREST);
    map_entry(GOLDENROD_UNDERGROUND);
    map_entry(GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES);
    map_entry(GOLDENROD_DEPT_STORE_B1F);
    map_entry(GOLDENROD_UNDERGROUND_WAREHOUSE);
    map_entry(MOUNT_MORTAR_1F_OUTSIDE);
    map_entry(MOUNT_MORTAR_1F_INSIDE);
    map_entry(MOUNT_MORTAR_2F_INSIDE);
    map_entry(MOUNT_MORTAR_B1F);
    map_entry(ICE_PATH_1F);
    map_entry(ICE_PATH_B1F);
    map_entry(ICE_PATH_B2F_MAHOGANY_SIDE);
    map_entry(ICE_PATH_B2F_BLACKTHORN_SIDE);
    map_entry(ICE_PATH_B3F);
    map_entry(WHIRL_ISLAND_NW);
    map_entry(WHIRL_ISLAND_NE);
    map_entry(WHIRL_ISLAND_SW);
    map_entry(WHIRL_ISLAND_CAVE);
    map_entry(WHIRL_ISLAND_SE);
    map_entry(WHIRL_ISLAND_B1F);
    map_entry(WHIRL_ISLAND_B2F);
    map_entry(WHIRL_ISLAND_LUGIA_CHAMBER);
    map_entry(SILVER_CAVE_ROOM_1);
    map_entry(SILVER_CAVE_ROOM_2);
    map_entry(SILVER_CAVE_ROOM_3);
    map_entry(SILVER_CAVE_ITEM_ROOMS);
    map_entry(DARK_CAVE_VIOLET_ENTRANCE);
    map_entry(DARK_CAVE_BLACKTHORN_ENTRANCE);
    map_entry(DRAGONS_DEN_1F);
    map_entry(DRAGONS_DEN_B1F);
    map_entry(DRAGON_SHRINE);
    map_entry(TOHJO_FALLS);
    map_entry(DIGLETTS_CAVE);
    map_entry(MOUNT_MOON);
    map_entry(UNDERGROUND_PATH);
    map_entry(ROCK_TUNNEL_1F);
    map_entry(ROCK_TUNNEL_B1F);
    map_entry(SAFARI_ZONE_FUCHSIA_GATE_BETA);
    map_entry(SAFARI_ZONE_BETA);
    map_entry(VICTORY_ROAD);

    map_entry(ECRUTEAK_TIN_TOWER_ENTRANCE);
    map_entry(WISE_TRIOS_ROOM);
    map_entry(ECRUTEAK_POKECENTER_1F);
    map_entry(ECRUTEAK_LUGIA_SPEECH_HOUSE);
    map_entry(DANCE_THEATRE);
    map_entry(ECRUTEAK_MART);
    map_entry(ECRUTEAK_GYM);
    map_entry(ECRUTEAK_ITEMFINDER_HOUSE);
    map_entry(ECRUTEAK_CITY);

    map_entry(BLACKTHORN_GYM_1F);
    map_entry(BLACKTHORN_GYM_2F);
    map_entry(BLACKTHORN_DRAGON_SPEECH_HOUSE);
    map_entry(BLACKTHORN_EMYS_HOUSE);
    map_entry(BLACKTHORN_MART);
    map_entry(BLACKTHORN_POKECENTER_1F);
    map_entry(MOVE_DELETERS_HOUSE);
    map_entry(ROUTE_45);
    map_entry(ROUTE_46);
    map_entry(BLACKTHORN_CITY);

    map_entry(CINNABAR_POKECENTER_1F);
    map_entry(CINNABAR_POKECENTER_2F_BETA);
    map_entry(ROUTE_19_FUCHSIA_GATE);
    map_entry(SEAFOAM_GYM);
    map_entry(ROUTE_19);
    map_entry(ROUTE_20);
    map_entry(ROUTE_21);
    map_entry(CINNABAR_ISLAND);

    map_entry(CERULEAN_GYM_BADGE_SPEECH_HOUSE);
    map_entry(CERULEAN_POLICE_STATION);
    map_entry(CERULEAN_TRADE_SPEECH_HOUSE);
    map_entry(CERULEAN_POKECENTER_1F);
    map_entry(CERULEAN_POKECENTER_2F_BETA);
    map_entry(CERULEAN_GYM);
    map_entry(CERULEAN_MART);
    map_entry(ROUTE_10_POKECENTER_1F);
    map_entry(ROUTE_10_POKECENTER_2F_BETA);
    map_entry(POWER_PLANT);
    map_entry(BILLS_HOUSE);
    map_entry(ROUTE_4);
    map_entry(ROUTE_9);
    map_entry(ROUTE_10_NORTH);
    map_entry(ROUTE_24);
    map_entry(ROUTE_25);
    map_entry(CERULEAN_CITY);

    map_entry(AZALEA_POKECENTER_1F);
    map_entry(CHARCOAL_KILN);
    map_entry(AZALEA_MART);
    map_entry(KURTS_HOUSE);
    map_entry(AZALEA_GYM);
    map_entry(ROUTE_33);
    map_entry(AZALEA_TOWN);

    map_entry(LAKE_OF_RAGE_HIDDEN_POWER_HOUSE);
    map_entry(LAKE_OF_RAGE_MAGIKARP_HOUSE);
    map_entry(ROUTE_43_MAHOGANY_GATE);
    map_entry(ROUTE_43_GATE);
    map_entry(ROUTE_43);
    map_entry(LAKE_OF_RAGE);

    map_entry(ROUTE_32);
    map_entry(ROUTE_35);
    map_entry(ROUTE_36);
    map_entry(ROUTE_37);
    map_entry(VIOLET_CITY);
    map_entry(VIOLET_MART);
    map_entry(VIOLET_GYM);
    map_entry(EARLS_POKEMON_ACADEMY);
    map_entry(VIOLET_NICKNAME_SPEECH_HOUSE);
    map_entry(VIOLET_POKECENTER_1F);
    map_entry(VIOLET_KYLES_HOUSE);
    map_entry(ROUTE_32_RUINS_OF_ALPH_GATE);
    map_entry(ROUTE_32_POKECENTER_1F);
    map_entry(ROUTE_35_GOLDENROD_GATE);
    map_entry(ROUTE_35_NATIONAL_PARK_GATE);
    map_entry(ROUTE_36_RUINS_OF_ALPH_GATE);
    map_entry(ROUTE_36_NATIONAL_PARK_GATE);

    map_entry(ROUTE_34);
    map_entry(GOLDENROD_CITY);
    map_entry(GOLDENROD_GYM);
    map_entry(GOLDENROD_BIKE_SHOP);
    map_entry(GOLDENROD_HAPPINESS_RATER);
    map_entry(BILLS_FAMILYS_HOUSE);
    map_entry(GOLDENROD_MAGNET_TRAIN_STATION);
    map_entry(GOLDENROD_FLOWER_SHOP);
    map_entry(GOLDENROD_PP_SPEECH_HOUSE);
    map_entry(GOLDENROD_NAME_RATER);
    map_entry(GOLDENROD_DEPT_STORE_1F);
    map_entry(GOLDENROD_DEPT_STORE_2F);
    map_entry(GOLDENROD_DEPT_STORE_3F);
    map_entry(GOLDENROD_DEPT_STORE_4F);
    map_entry(GOLDENROD_DEPT_STORE_5F);
    map_entry(GOLDENROD_DEPT_STORE_6F);
    map_entry(GOLDENROD_DEPT_STORE_ELEVATOR);
    map_entry(GOLDENROD_DEPT_STORE_ROOF);
    map_entry(GOLDENROD_GAME_CORNER);
    map_entry(GOLDENROD_POKECENTER_1F);
    map_entry(POKECOM_CENTER_ADMIN_OFFICE_MOBILE);
    map_entry(ILEX_FOREST_AZALEA_GATE);
    map_entry(ROUTE_34_ILEX_FOREST_GATE);
    map_entry(DAY_CARE);

    map_entry(ROUTE_6);
    map_entry(ROUTE_11);
    map_entry(VERMILION_CITY);
    map_entry(VERMILION_FISHING_SPEECH_HOUSE);
    map_entry(VERMILION_POKECENTER_1F);
    map_entry(VERMILION_POKECENTER_2F_BETA);
    map_entry(POKEMON_FAN_CLUB);
    map_entry(VERMILION_MAGNET_TRAIN_SPEECH_HOUSE);
    map_entry(VERMILION_MART);
    map_entry(VERMILION_DIGLETTS_CAVE_SPEECH_HOUSE);
    map_entry(VERMILION_GYM);
    map_entry(ROUTE_6_SAFFRON_GATE);
    map_entry(ROUTE_6_UNDERGROUND_PATH_ENTRANCE);

    map_entry(ROUTE_1);
    map_entry(PALLET_TOWN);
    map_entry(REDS_HOUSE_1F);
    map_entry(REDS_HOUSE_2F);
    map_entry(BLUES_HOUSE);
    map_entry(OAKS_LAB);

    map_entry(ROUTE_3);
    map_entry(PEWTER_CITY);
    map_entry(PEWTER_NIDORAN_SPEECH_HOUSE);
    map_entry(PEWTER_GYM);
    map_entry(PEWTER_MART);
    map_entry(PEWTER_POKECENTER_1F);
    map_entry(PEWTER_POKECENTER_2F_BETA);
    map_entry(PEWTER_SNOOZE_SPEECH_HOUSE);

    map_entry(OLIVINE_PORT);
    map_entry(VERMILION_PORT);
    map_entry(FAST_SHIP_1F);
    map_entry(FAST_SHIP_CABINS_NNW_NNE_NE);
    map_entry(FAST_SHIP_CABINS_SW_SSW_NW);
    map_entry(FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN);
    map_entry(FAST_SHIP_B1F);
    map_entry(OLIVINE_PORT_PASSAGE);
    map_entry(VERMILION_PORT_PASSAGE);
    map_entry(MOUNT_MOON_SQUARE);
    map_entry(MOUNT_MOON_GIFT_SHOP);
    map_entry(TIN_TOWER_ROOF);

    map_entry(ROUTE_23);
    map_entry(INDIGO_PLATEAU_POKECENTER_1F);
    map_entry(WILLS_ROOM);
    map_entry(KOGAS_ROOM);
    map_entry(BRUNOS_ROOM);
    map_entry(KARENS_ROOM);
    map_entry(LANCES_ROOM);
    map_entry(HALL_OF_FAME);

    map_entry(ROUTE_13);
    map_entry(ROUTE_14);
    map_entry(ROUTE_15);
    map_entry(ROUTE_18);
    map_entry(FUCHSIA_CITY);
    map_entry(FUCHSIA_MART);
    map_entry(SAFARI_ZONE_MAIN_OFFICE);
    map_entry(FUCHSIA_GYM);
    map_entry(BILLS_BROTHERS_HOUSE);
    map_entry(FUCHSIA_POKECENTER_1F);
    map_entry(FUCHSIA_POKECENTER_2F_BETA);
    map_entry(SAFARI_ZONE_WARDENS_HOME);
    map_entry(ROUTE_15_FUCHSIA_GATE);

    map_entry(ROUTE_8);
    map_entry(ROUTE_12);
    map_entry(ROUTE_10_SOUTH);
    map_entry(LAVENDER_TOWN);
    map_entry(LAVENDER_POKECENTER_1F);
    map_entry(LAVENDER_POKECENTER_2F_BETA);
    map_entry(MR_FUJIS_HOUSE);
    map_entry(LAVENDER_SPEECH_HOUSE);
    map_entry(LAVENDER_NAME_RATER);
    map_entry(LAVENDER_MART);
    map_entry(SOUL_HOUSE);
    map_entry(LAV_RADIO_TOWER_1F);
    map_entry(ROUTE_8_SAFFRON_GATE);
    map_entry(ROUTE_12_SUPER_ROD_HOUSE);

    map_entry(ROUTE_28);
    map_entry(SILVER_CAVE_OUTSIDE);
    map_entry(SILVER_CAVE_POKECENTER_1F);
    map_entry(ROUTE_28_STEEL_WING_HOUSE);

    map_entry(POKECENTER_2F);
    map_entry(TRADE_CENTER);
    map_entry(COLOSSEUM);
    map_entry(TIME_CAPSULE);
    map_entry(MOBILE_TRADE_ROOM);
    map_entry(MOBILE_BATTLE_ROOM);

    map_entry(ROUTE_7);
    map_entry(ROUTE_16);
    map_entry(ROUTE_17);
    map_entry(CELADON_CITY);
    map_entry(CELADON_DEPT_STORE_1F);
    map_entry(CELADON_DEPT_STORE_2F);
    map_entry(CELADON_DEPT_STORE_3F);
    map_entry(CELADON_DEPT_STORE_4F);
    map_entry(CELADON_DEPT_STORE_5F);
    map_entry(CELADON_DEPT_STORE_6F);
    map_entry(CELADON_DEPT_STORE_ELEVATOR);
    map_entry(CELADON_MANSION_1F);
    map_entry(CELADON_MANSION_2F);
    map_entry(CELADON_MANSION_3F);
    map_entry(CELADON_MANSION_ROOF);
    map_entry(CELADON_MANSION_ROOF_HOUSE);
    map_entry(CELADON_POKECENTER_1F);
    map_entry(CELADON_POKECENTER_2F_BETA);
    map_entry(CELADON_GAME_CORNER);
    map_entry(CELADON_GAME_CORNER_PRIZE_ROOM);
    map_entry(CELADON_GYM);
    map_entry(CELADON_CAFE);
    map_entry(ROUTE_16_FUCHSIA_SPEECH_HOUSE);
    map_entry(ROUTE_16_GATE);
    map_entry(ROUTE_7_SAFFRON_GATE);
    map_entry(ROUTE_17_ROUTE_18_GATE);

    map_entry(ROUTE_40);
    map_entry(ROUTE_41);
    map_entry(CIANWOOD_CITY);
    map_entry(MANIAS_HOUSE);
    map_entry(CIANWOOD_GYM);
    map_entry(CIANWOOD_POKECENTER_1F);
    map_entry(CIANWOOD_PHARMACY);
    map_entry(CIANWOOD_PHOTO_STUDIO);
    map_entry(CIANWOOD_LUGIA_SPEECH_HOUSE);
    map_entry(POKE_SEERS_HOUSE);
    map_entry(BATTLE_TOWER_1F);
    map_entry(BATTLE_TOWER_BATTLE_ROOM);
    map_entry(BATTLE_TOWER_ELEVATOR);
    map_entry(BATTLE_TOWER_HALLWAY);
    map_entry(ROUTE_40_BATTLE_TOWER_GATE);
    map_entry(BATTLE_TOWER_OUTSIDE);

    map_entry(ROUTE_2);
    map_entry(ROUTE_22);
    map_entry(VIRIDIAN_CITY);
    map_entry(VIRIDIAN_GYM);
    map_entry(VIRIDIAN_NICKNAME_SPEECH_HOUSE);
    map_entry(TRAINER_HOUSE_1F);
    map_entry(TRAINER_HOUSE_B1F);
    map_entry(VIRIDIAN_MART);
    map_entry(VIRIDIAN_POKECENTER_1F);
    map_entry(VIRIDIAN_POKECENTER_2F_BETA);
    map_entry(ROUTE_2_NUGGET_HOUSE);
    map_entry(ROUTE_2_GATE);
    map_entry(VICTORY_ROAD_GATE);

    map_entry(ROUTE_26);
    map_entry(ROUTE_27);
    map_entry(ROUTE_29);
    map_entry(NEW_BARK_TOWN);
    map_entry(ELMS_LAB);
    map_entry(PLAYERS_HOUSE_1F);
    map_entry(PLAYERS_HOUSE_2F);
    map_entry(PLAYERS_NEIGHBORS_HOUSE);
    map_entry(ELMS_HOUSE);
    map_entry(ROUTE_26_HEAL_HOUSE);
    map_entry(DAY_OF_WEEK_SIBLINGS_HOUSE);
    map_entry(ROUTE_27_SANDSTORM_HOUSE);
    map_entry(ROUTE_29_ROUTE_46_GATE);

    map_entry(ROUTE_5);
    map_entry(SAFFRON_CITY);
    map_entry(FIGHTING_DOJO);
    map_entry(SAFFRON_GYM);
    map_entry(SAFFRON_MART);
    map_entry(SAFFRON_POKECENTER_1F);
    map_entry(SAFFRON_POKECENTER_2F_BETA);
    map_entry(MR_PSYCHICS_HOUSE);
    map_entry(SAFFRON_MAGNET_TRAIN_STATION);
    map_entry(SILPH_CO_1F);
    map_entry(COPYCATS_HOUSE_1F);
    map_entry(COPYCATS_HOUSE_2F);
    map_entry(ROUTE_5_UNDERGROUND_PATH_ENTRANCE);
    map_entry(ROUTE_5_SAFFRON_GATE);
    map_entry(ROUTE_5_CLEANSE_TAG_HOUSE);

    map_entry(ROUTE_30);
    map_entry(ROUTE_31);
    map_entry(CHERRYGROVE_CITY);
    map_entry(CHERRYGROVE_MART);
    map_entry(CHERRYGROVE_POKECENTER_1F);
    map_entry(CHERRYGROVE_GYM_SPEECH_HOUSE);
    map_entry(GUIDE_GENTS_HOUSE);
    map_entry(CHERRYGROVE_EVOLUTION_SPEECH_HOUSE);
    map_entry(ROUTE_30_BERRY_HOUSE);
    map_entry(MR_POKEMONS_HOUSE);
    map_entry(ROUTE_31_VIOLET_GATE);

    entry(NORMAL);
    entry(FIGHTING);
    entry(FLYING);
    entry(POISON);
    entry(GROUND);
    entry(ROCK);
    entry(BIRD);
    entry(BUG);
    entry(GHOST);
    entry(STEEL);
    entry(CURSE_TYPE);
    entry(FIRE);
    entry(WATER);
    entry(GRASS);
    entry(ELECTRIC);
    entry(PSYCHIC_TYPE);
    entry(ICE);
    entry(DRAGON);
    entry(DARK);

    entry(EGG_MONSTER);
    entry(EGG_WATER_1);
    entry(EGG_BUG);
    entry(EGG_FLYING);
    entry(EGG_GROUND);
    entry(EGG_FAIRY);
    entry(EGG_PLANT);
    entry(EGG_HUMANSHAPE);
    entry(EGG_WATER_3);
    entry(EGG_MINERAL);
    entry(EGG_INDETERMINATE);
    entry(EGG_WATER_2);
    entry(EGG_DITTO);
    entry(EGG_DRAGON);
    entry(EGG_NONE);

    entry(GENDER_F0);
    entry(GENDER_F12_5);
    entry(GENDER_F25);
    entry(GENDER_F50);
    entry(GENDER_F75);
    entry(GENDER_F100);
    entry(GENDER_UNKNOWN);

    entry(GROWTH_MEDIUM_FAST);
    entry(GROWTH_SLIGHTLY_FAST);
    entry(GROWTH_SLIGHTLY_SLOW);
    entry(GROWTH_MEDIUM_SLOW);
    entry(GROWTH_FAST);
    entry(GROWTH_SLOW);
    entry(NUM_GROWTH_RATES);

    entry(SDL_CONTROLLER_BUTTON_INVALID);
    entry(SDL_CONTROLLER_BUTTON_A);
    entry(SDL_CONTROLLER_BUTTON_B);
    entry(SDL_CONTROLLER_BUTTON_X);
    entry(SDL_CONTROLLER_BUTTON_Y);
    entry(SDL_CONTROLLER_BUTTON_BACK);
    entry(SDL_CONTROLLER_BUTTON_GUIDE);
    entry(SDL_CONTROLLER_BUTTON_START);
    entry(SDL_CONTROLLER_BUTTON_LEFTSTICK);
    entry(SDL_CONTROLLER_BUTTON_RIGHTSTICK);
    entry(SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    entry(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
    entry(SDL_CONTROLLER_BUTTON_DPAD_UP);
    entry(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    entry(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    entry(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    entry(SDL_CONTROLLER_BUTTON_MISC1);    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
    entry(SDL_CONTROLLER_BUTTON_PADDLE1);  /* Xbox Elite paddle P1 (upper left, facing the back) */
    entry(SDL_CONTROLLER_BUTTON_PADDLE2);  /* Xbox Elite paddle P3 (upper right, facing the back) */
    entry(SDL_CONTROLLER_BUTTON_PADDLE3);  /* Xbox Elite paddle P2 (lower left, facing the back) */
    entry(SDL_CONTROLLER_BUTTON_PADDLE4);  /* Xbox Elite paddle P4 (lower right, facing the back) */
    entry(SDL_CONTROLLER_BUTTON_TOUCHPAD); /* PS4/PS5 touchpad button */

    entry(SDLK_UNKNOWN);

    entry(SDLK_RETURN);
    entry(SDLK_ESCAPE);
    entry(SDLK_BACKSPACE);
    entry(SDLK_TAB);
    entry(SDLK_SPACE);
    entry(SDLK_EXCLAIM);
    entry(SDLK_QUOTEDBL);
    entry(SDLK_HASH);
    entry(SDLK_PERCENT);
    entry(SDLK_DOLLAR);
    entry(SDLK_AMPERSAND);
    entry(SDLK_QUOTE);
    entry(SDLK_LEFTPAREN);
    entry(SDLK_RIGHTPAREN);
    entry(SDLK_ASTERISK);
    entry(SDLK_PLUS);
    entry(SDLK_COMMA);
    entry(SDLK_MINUS);
    entry(SDLK_PERIOD);
    entry(SDLK_SLASH);
    entry(SDLK_0);
    entry(SDLK_1);
    entry(SDLK_2);
    entry(SDLK_3);
    entry(SDLK_4);
    entry(SDLK_5);
    entry(SDLK_6);
    entry(SDLK_7);
    entry(SDLK_8);
    entry(SDLK_9);
    entry(SDLK_COLON);
    entry(SDLK_SEMICOLON);
    entry(SDLK_LESS);
    entry(SDLK_EQUALS);
    entry(SDLK_GREATER);
    entry(SDLK_QUESTION);
    entry(SDLK_AT);

    /*
       Skip uppercase letters
     */

    entry(SDLK_LEFTBRACKET);
    entry(SDLK_BACKSLASH);
    entry(SDLK_RIGHTBRACKET);
    entry(SDLK_CARET);
    entry(SDLK_UNDERSCORE);
    entry(SDLK_BACKQUOTE);
    entry(SDLK_a);
    entry(SDLK_b);
    entry(SDLK_c);
    entry(SDLK_d);
    entry(SDLK_e);
    entry(SDLK_f);
    entry(SDLK_g);
    entry(SDLK_h);
    entry(SDLK_i);
    entry(SDLK_j);
    entry(SDLK_k);
    entry(SDLK_l);
    entry(SDLK_m);
    entry(SDLK_n);
    entry(SDLK_o);
    entry(SDLK_p);
    entry(SDLK_q);
    entry(SDLK_r);
    entry(SDLK_s);
    entry(SDLK_t);
    entry(SDLK_u);
    entry(SDLK_v);
    entry(SDLK_w);
    entry(SDLK_x);
    entry(SDLK_y);
    entry(SDLK_z);

    entry(SDLK_CAPSLOCK);

    entry(SDLK_F1);
    entry(SDLK_F2);
    entry(SDLK_F3);
    entry(SDLK_F4);
    entry(SDLK_F5);
    entry(SDLK_F6);
    entry(SDLK_F7);
    entry(SDLK_F8);
    entry(SDLK_F9);
    entry(SDLK_F10);
    entry(SDLK_F11);
    entry(SDLK_F12);

    entry(SDLK_PRINTSCREEN);
    entry(SDLK_SCROLLLOCK);
    entry(SDLK_PAUSE);
    entry(SDLK_INSERT);
    entry(SDLK_HOME);
    entry(SDLK_PAGEUP);
    entry(SDLK_DELETE);
    entry(SDLK_END);
    entry(SDLK_PAGEDOWN);
    entry(SDLK_RIGHT);
    entry(SDLK_LEFT);
    entry(SDLK_DOWN);
    entry(SDLK_UP);

    entry(SDLK_NUMLOCKCLEAR);
    entry(SDLK_KP_DIVIDE);
    entry(SDLK_KP_MULTIPLY);
    entry(SDLK_KP_MINUS);
    entry(SDLK_KP_PLUS);
    entry(SDLK_KP_ENTER);
    entry(SDLK_KP_1);
    entry(SDLK_KP_2);
    entry(SDLK_KP_3);
    entry(SDLK_KP_4);
    entry(SDLK_KP_5);
    entry(SDLK_KP_6);
    entry(SDLK_KP_7);
    entry(SDLK_KP_8);
    entry(SDLK_KP_9);
    entry(SDLK_KP_0);
    entry(SDLK_KP_PERIOD);

    entry(SDLK_APPLICATION);
    entry(SDLK_POWER);
    entry(SDLK_KP_EQUALS);
    entry(SDLK_F13);
    entry(SDLK_F14);
    entry(SDLK_F15);
    entry(SDLK_F16);
    entry(SDLK_F17);
    entry(SDLK_F18);
    entry(SDLK_F19);
    entry(SDLK_F20);
    entry(SDLK_F21);
    entry(SDLK_F22);
    entry(SDLK_F23);
    entry(SDLK_F24);
    entry(SDLK_EXECUTE);
    entry(SDLK_HELP);
    entry(SDLK_MENU);
    entry(SDLK_SELECT);
    entry(SDLK_STOP);
    entry(SDLK_AGAIN);
    entry(SDLK_UNDO);
    entry(SDLK_CUT);
    entry(SDLK_COPY);
    entry(SDLK_PASTE);
    entry(SDLK_FIND);
    entry(SDLK_MUTE);
    entry(SDLK_VOLUMEUP);
    entry(SDLK_VOLUMEDOWN);
    entry(SDLK_KP_COMMA);
    entry(SDLK_KP_EQUALSAS400);

    entry(SDLK_ALTERASE);
    entry(SDLK_SYSREQ);
    entry(SDLK_CANCEL);
    entry(SDLK_CLEAR);
    entry(SDLK_PRIOR);
    entry(SDLK_RETURN2);
    entry(SDLK_SEPARATOR);
    entry(SDLK_OUT);
    entry(SDLK_OPER);
    entry(SDLK_CLEARAGAIN);
    entry(SDLK_CRSEL);
    entry(SDLK_EXSEL);

    entry(SDLK_KP_00);
    entry(SDLK_KP_000);
    entry(SDLK_THOUSANDSSEPARATOR);
    entry(SDLK_DECIMALSEPARATOR);
    entry(SDLK_CURRENCYUNIT);
    entry(SDLK_CURRENCYSUBUNIT);
    entry(SDLK_KP_LEFTPAREN);
    entry(SDLK_KP_RIGHTPAREN);
    entry(SDLK_KP_LEFTBRACE);
    entry(SDLK_KP_RIGHTBRACE);
    entry(SDLK_KP_TAB);
    entry(SDLK_KP_BACKSPACE);
    entry(SDLK_KP_A);
    entry(SDLK_KP_B);
    entry(SDLK_KP_C);
    entry(SDLK_KP_D);
    entry(SDLK_KP_E);
    entry(SDLK_KP_F);
    entry(SDLK_KP_XOR);
    entry(SDLK_KP_POWER);
    entry(SDLK_KP_PERCENT);
    entry(SDLK_KP_LESS);
    entry(SDLK_KP_GREATER);
    entry(SDLK_KP_AMPERSAND);
    entry(SDLK_KP_DBLAMPERSAND);
    entry(SDLK_KP_VERTICALBAR);
    entry(SDLK_KP_DBLVERTICALBAR);
    entry(SDLK_KP_COLON);
    entry(SDLK_KP_HASH);
    entry(SDLK_KP_SPACE);
    entry(SDLK_KP_AT);
    entry(SDLK_KP_EXCLAM);
    entry(SDLK_KP_MEMSTORE);
    entry(SDLK_KP_MEMRECALL);
    entry(SDLK_KP_MEMCLEAR);
    entry(SDLK_KP_MEMADD);
    entry(SDLK_KP_MEMSUBTRACT);
    entry(SDLK_KP_MEMMULTIPLY);
    entry(SDLK_KP_MEMDIVIDE);
    entry(SDLK_KP_PLUSMINUS);
    entry(SDLK_KP_CLEAR);
    entry(SDLK_KP_CLEARENTRY);
    entry(SDLK_KP_BINARY);
    entry(SDLK_KP_OCTAL);
    entry(SDLK_KP_DECIMAL);
    entry(SDLK_KP_HEXADECIMAL);

    entry(SDLK_LCTRL);
    entry(SDLK_LSHIFT);
    entry(SDLK_LALT);
    entry(SDLK_LGUI);
    entry(SDLK_RCTRL);
    entry(SDLK_RSHIFT);
    entry(SDLK_RALT);
    entry(SDLK_RGUI);

    entry(SDLK_MODE);

    entry(SDLK_AUDIONEXT);
    entry(SDLK_AUDIOPREV);
    entry(SDLK_AUDIOSTOP);
    entry(SDLK_AUDIOPLAY);
    entry(SDLK_AUDIOMUTE);
    entry(SDLK_MEDIASELECT);
    entry(SDLK_WWW);
    entry(SDLK_MAIL);
    entry(SDLK_CALCULATOR);
    entry(SDLK_COMPUTER);
    entry(SDLK_AC_SEARCH);
    entry(SDLK_AC_HOME);
    entry(SDLK_AC_BACK);
    entry(SDLK_AC_FORWARD);
    entry(SDLK_AC_STOP);
    entry(SDLK_AC_REFRESH);
    entry(SDLK_AC_BOOKMARKS);

    entry(SDLK_BRIGHTNESSDOWN);
    entry(SDLK_BRIGHTNESSUP);
    entry(SDLK_DISPLAYSWITCH);
    entry(SDLK_KBDILLUMTOGGLE);
    entry(SDLK_KBDILLUMDOWN);
    entry(SDLK_KBDILLUMUP);
    entry(SDLK_EJECT);
    entry(SDLK_SLEEP);
    entry(SDLK_APP1);
    entry(SDLK_APP2);

    entry(SDLK_AUDIOREWIND);
    entry(SDLK_AUDIOFASTFORWARD);

    entry(SDLK_SOFTLEFT);
    entry(SDLK_SOFTRIGHT);
    entry(SDLK_CALL);
    entry(SDLK_ENDCALL);

    entry(SDL_SCANCODE_UNKNOWN);

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    entry(SDL_SCANCODE_A);
    entry(SDL_SCANCODE_B);
    entry(SDL_SCANCODE_C);
    entry(SDL_SCANCODE_D);
    entry(SDL_SCANCODE_E);
    entry(SDL_SCANCODE_F);
    entry(SDL_SCANCODE_G);
    entry(SDL_SCANCODE_H);
    entry(SDL_SCANCODE_I);
    entry(SDL_SCANCODE_J);
    entry(SDL_SCANCODE_K);
    entry(SDL_SCANCODE_L);
    entry(SDL_SCANCODE_M);
    entry(SDL_SCANCODE_N);
    entry(SDL_SCANCODE_O);
    entry(SDL_SCANCODE_P);
    entry(SDL_SCANCODE_Q);
    entry(SDL_SCANCODE_R);
    entry(SDL_SCANCODE_S);
    entry(SDL_SCANCODE_T);
    entry(SDL_SCANCODE_U);
    entry(SDL_SCANCODE_V);
    entry(SDL_SCANCODE_W);
    entry(SDL_SCANCODE_X);
    entry(SDL_SCANCODE_Y);
    entry(SDL_SCANCODE_Z);

    entry(SDL_SCANCODE_1);
    entry(SDL_SCANCODE_2);
    entry(SDL_SCANCODE_3);
    entry(SDL_SCANCODE_4);
    entry(SDL_SCANCODE_5);
    entry(SDL_SCANCODE_6);
    entry(SDL_SCANCODE_7);
    entry(SDL_SCANCODE_8);
    entry(SDL_SCANCODE_9);
    entry(SDL_SCANCODE_0);

    entry(SDL_SCANCODE_RETURN);
    entry(SDL_SCANCODE_ESCAPE);
    entry(SDL_SCANCODE_BACKSPACE);
    entry(SDL_SCANCODE_TAB);
    entry(SDL_SCANCODE_SPACE);

    entry(SDL_SCANCODE_MINUS);
    entry(SDL_SCANCODE_EQUALS);
    entry(SDL_SCANCODE_LEFTBRACKET);
    entry(SDL_SCANCODE_RIGHTBRACKET);
    entry(SDL_SCANCODE_BACKSLASH); /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    entry(SDL_SCANCODE_NONUSHASH); /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate SDL_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    entry(SDL_SCANCODE_SEMICOLON);
    entry(SDL_SCANCODE_APOSTROPHE);
    entry(SDL_SCANCODE_GRAVE); /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    entry(SDL_SCANCODE_COMMA);
    entry(SDL_SCANCODE_PERIOD);
    entry(SDL_SCANCODE_SLASH);

    entry(SDL_SCANCODE_CAPSLOCK);

    entry(SDL_SCANCODE_F1);
    entry(SDL_SCANCODE_F2);
    entry(SDL_SCANCODE_F3);
    entry(SDL_SCANCODE_F4);
    entry(SDL_SCANCODE_F5);
    entry(SDL_SCANCODE_F6);
    entry(SDL_SCANCODE_F7);
    entry(SDL_SCANCODE_F8);
    entry(SDL_SCANCODE_F9);
    entry(SDL_SCANCODE_F10);
    entry(SDL_SCANCODE_F11);
    entry(SDL_SCANCODE_F12);

    entry(SDL_SCANCODE_PRINTSCREEN);
    entry(SDL_SCANCODE_SCROLLLOCK);
    entry(SDL_SCANCODE_PAUSE);
    entry(SDL_SCANCODE_INSERT); /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    entry(SDL_SCANCODE_HOME);
    entry(SDL_SCANCODE_PAGEUP);
    entry(SDL_SCANCODE_DELETE);
    entry(SDL_SCANCODE_END);
    entry(SDL_SCANCODE_PAGEDOWN);
    entry(SDL_SCANCODE_RIGHT);
    entry(SDL_SCANCODE_LEFT);
    entry(SDL_SCANCODE_DOWN);
    entry(SDL_SCANCODE_UP);

    entry(SDL_SCANCODE_NUMLOCKCLEAR); /**< num lock on PC, clear on Mac keyboards
                                     */
    entry(SDL_SCANCODE_KP_DIVIDE);
    entry(SDL_SCANCODE_KP_MULTIPLY);
    entry(SDL_SCANCODE_KP_MINUS);
    entry(SDL_SCANCODE_KP_PLUS);
    entry(SDL_SCANCODE_KP_ENTER);
    entry(SDL_SCANCODE_KP_1);
    entry(SDL_SCANCODE_KP_2);
    entry(SDL_SCANCODE_KP_3);
    entry(SDL_SCANCODE_KP_4);
    entry(SDL_SCANCODE_KP_5);
    entry(SDL_SCANCODE_KP_6);
    entry(SDL_SCANCODE_KP_7);
    entry(SDL_SCANCODE_KP_8);
    entry(SDL_SCANCODE_KP_9);
    entry(SDL_SCANCODE_KP_0);
    entry(SDL_SCANCODE_KP_PERIOD);

    entry(SDL_SCANCODE_NONUSBACKSLASH); /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    entry(SDL_SCANCODE_APPLICATION); /**< windows contextual menu, compose */
    entry(SDL_SCANCODE_POWER); /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    entry(SDL_SCANCODE_KP_EQUALS);
    entry(SDL_SCANCODE_F13);
    entry(SDL_SCANCODE_F14);
    entry(SDL_SCANCODE_F15);
    entry(SDL_SCANCODE_F16);
    entry(SDL_SCANCODE_F17);
    entry(SDL_SCANCODE_F18);
    entry(SDL_SCANCODE_F19);
    entry(SDL_SCANCODE_F20);
    entry(SDL_SCANCODE_F21);
    entry(SDL_SCANCODE_F22);
    entry(SDL_SCANCODE_F23);
    entry(SDL_SCANCODE_F24);
    entry(SDL_SCANCODE_EXECUTE);
    entry(SDL_SCANCODE_HELP);    /**< AL Integrated Help Center */
    entry(SDL_SCANCODE_MENU);    /**< Menu (show menu) */
    entry(SDL_SCANCODE_SELECT);
    entry(SDL_SCANCODE_STOP);    /**< AC Stop */
    entry(SDL_SCANCODE_AGAIN);   /**< AC Redo/Repeat */
    entry(SDL_SCANCODE_UNDO);    /**< AC Undo */
    entry(SDL_SCANCODE_CUT);     /**< AC Cut */
    entry(SDL_SCANCODE_COPY);    /**< AC Copy */
    entry(SDL_SCANCODE_PASTE);   /**< AC Paste */
    entry(SDL_SCANCODE_FIND);    /**< AC Find */
    entry(SDL_SCANCODE_MUTE);
    entry(SDL_SCANCODE_VOLUMEUP);
    entry(SDL_SCANCODE_VOLUMEDOWN);
/* not sure whether there's a reason to enable these */
/*     SDL_SCANCODE_LOCKINGCAPSLOCK = 130,  */
/*     SDL_SCANCODE_LOCKINGNUMLOCK = 131, */
/*     SDL_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    entry(SDL_SCANCODE_KP_COMMA);
    entry(SDL_SCANCODE_KP_EQUALSAS400);

    entry(SDL_SCANCODE_INTERNATIONAL1); /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    entry(SDL_SCANCODE_INTERNATIONAL2);
    entry(SDL_SCANCODE_INTERNATIONAL3); /**< Yen */
    entry(SDL_SCANCODE_INTERNATIONAL4);
    entry(SDL_SCANCODE_INTERNATIONAL5);
    entry(SDL_SCANCODE_INTERNATIONAL6);
    entry(SDL_SCANCODE_INTERNATIONAL7);
    entry(SDL_SCANCODE_INTERNATIONAL8);
    entry(SDL_SCANCODE_INTERNATIONAL9);
    entry(SDL_SCANCODE_LANG1); /**< Hangul/English toggle */
    entry(SDL_SCANCODE_LANG2); /**< Hanja conversion */
    entry(SDL_SCANCODE_LANG3); /**< Katakana */
    entry(SDL_SCANCODE_LANG4); /**< Hiragana */
    entry(SDL_SCANCODE_LANG5); /**< Zenkaku/Hankaku */
    entry(SDL_SCANCODE_LANG6); /**< reserved */
    entry(SDL_SCANCODE_LANG7); /**< reserved */
    entry(SDL_SCANCODE_LANG8); /**< reserved */
    entry(SDL_SCANCODE_LANG9); /**< reserved */

    entry(SDL_SCANCODE_ALTERASE);    /**< Erase-Eaze */
    entry(SDL_SCANCODE_SYSREQ);
    entry(SDL_SCANCODE_CANCEL);      /**< AC Cancel */
    entry(SDL_SCANCODE_CLEAR);
    entry(SDL_SCANCODE_PRIOR);
    entry(SDL_SCANCODE_RETURN2);
    entry(SDL_SCANCODE_SEPARATOR);
    entry(SDL_SCANCODE_OUT);
    entry(SDL_SCANCODE_OPER);
    entry(SDL_SCANCODE_CLEARAGAIN);
    entry(SDL_SCANCODE_CRSEL);
    entry(SDL_SCANCODE_EXSEL);

    entry(SDL_SCANCODE_KP_00);
    entry(SDL_SCANCODE_KP_000);
    entry(SDL_SCANCODE_THOUSANDSSEPARATOR);
    entry(SDL_SCANCODE_DECIMALSEPARATOR);
    entry(SDL_SCANCODE_CURRENCYUNIT);
    entry(SDL_SCANCODE_CURRENCYSUBUNIT);
    entry(SDL_SCANCODE_KP_LEFTPAREN);
    entry(SDL_SCANCODE_KP_RIGHTPAREN);
    entry(SDL_SCANCODE_KP_LEFTBRACE);
    entry(SDL_SCANCODE_KP_RIGHTBRACE);
    entry(SDL_SCANCODE_KP_TAB);
    entry(SDL_SCANCODE_KP_BACKSPACE);
    entry(SDL_SCANCODE_KP_A);
    entry(SDL_SCANCODE_KP_B);
    entry(SDL_SCANCODE_KP_C);
    entry(SDL_SCANCODE_KP_D);
    entry(SDL_SCANCODE_KP_E);
    entry(SDL_SCANCODE_KP_F);
    entry(SDL_SCANCODE_KP_XOR);
    entry(SDL_SCANCODE_KP_POWER);
    entry(SDL_SCANCODE_KP_PERCENT);
    entry(SDL_SCANCODE_KP_LESS);
    entry(SDL_SCANCODE_KP_GREATER);
    entry(SDL_SCANCODE_KP_AMPERSAND);
    entry(SDL_SCANCODE_KP_DBLAMPERSAND);
    entry(SDL_SCANCODE_KP_VERTICALBAR);
    entry(SDL_SCANCODE_KP_DBLVERTICALBAR);
    entry(SDL_SCANCODE_KP_COLON);
    entry(SDL_SCANCODE_KP_HASH);
    entry(SDL_SCANCODE_KP_SPACE);
    entry(SDL_SCANCODE_KP_AT);
    entry(SDL_SCANCODE_KP_EXCLAM);
    entry(SDL_SCANCODE_KP_MEMSTORE);
    entry(SDL_SCANCODE_KP_MEMRECALL);
    entry(SDL_SCANCODE_KP_MEMCLEAR);
    entry(SDL_SCANCODE_KP_MEMADD);
    entry(SDL_SCANCODE_KP_MEMSUBTRACT);
    entry(SDL_SCANCODE_KP_MEMMULTIPLY);
    entry(SDL_SCANCODE_KP_MEMDIVIDE);
    entry(SDL_SCANCODE_KP_PLUSMINUS);
    entry(SDL_SCANCODE_KP_CLEAR);
    entry(SDL_SCANCODE_KP_CLEARENTRY);
    entry(SDL_SCANCODE_KP_BINARY);
    entry(SDL_SCANCODE_KP_OCTAL);
    entry(SDL_SCANCODE_KP_DECIMAL);
    entry(SDL_SCANCODE_KP_HEXADECIMAL);

    entry(SDL_SCANCODE_LCTRL);
    entry(SDL_SCANCODE_LSHIFT);
    entry(SDL_SCANCODE_LALT); /**< alt, option */
    entry(SDL_SCANCODE_LGUI); /**< windows, command (apple), meta */
    entry(SDL_SCANCODE_RCTRL);
    entry(SDL_SCANCODE_RSHIFT);
    entry(SDL_SCANCODE_RALT); /**< alt gr, option */
    entry(SDL_SCANCODE_RGUI); /**< windows, command (apple), meta */

    entry(SDL_SCANCODE_MODE);    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     *  See https://usb.org/sites/default/files/hut1_2.pdf
     *
     *  There are way more keys in the spec than we can represent in the
     *  current scancode range, so pick the ones that commonly come up in
     *  real world usage.
     */
    /* @{ */

    entry(SDL_SCANCODE_AUDIONEXT);
    entry(SDL_SCANCODE_AUDIOPREV);
    entry(SDL_SCANCODE_AUDIOSTOP);
    entry(SDL_SCANCODE_AUDIOPLAY);
    entry(SDL_SCANCODE_AUDIOMUTE);
    entry(SDL_SCANCODE_MEDIASELECT);
    entry(SDL_SCANCODE_WWW);             /**< AL Internet Browser */
    entry(SDL_SCANCODE_MAIL);
    entry(SDL_SCANCODE_CALCULATOR);      /**< AL Calculator */
    entry(SDL_SCANCODE_COMPUTER);
    entry(SDL_SCANCODE_AC_SEARCH);       /**< AC Search */
    entry(SDL_SCANCODE_AC_HOME);         /**< AC Home */
    entry(SDL_SCANCODE_AC_BACK);         /**< AC Back */
    entry(SDL_SCANCODE_AC_FORWARD);      /**< AC Forward */
    entry(SDL_SCANCODE_AC_STOP);         /**< AC Stop */
    entry(SDL_SCANCODE_AC_REFRESH);      /**< AC Refresh */
    entry(SDL_SCANCODE_AC_BOOKMARKS);    /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    entry(SDL_SCANCODE_BRIGHTNESSDOWN);
    entry(SDL_SCANCODE_BRIGHTNESSUP);
    entry(SDL_SCANCODE_DISPLAYSWITCH); /**< display mirroring/dual display
                                           switch, video mode switch */
    entry(SDL_SCANCODE_KBDILLUMTOGGLE);
    entry(SDL_SCANCODE_KBDILLUMDOWN);
    entry(SDL_SCANCODE_KBDILLUMUP);
    entry(SDL_SCANCODE_EJECT);
    entry(SDL_SCANCODE_SLEEP);           /**< SC System Sleep */

    entry(SDL_SCANCODE_APP1);
    entry(SDL_SCANCODE_APP2);

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    entry(SDL_SCANCODE_AUDIOREWIND);
    entry(SDL_SCANCODE_AUDIOFASTFORWARD);

    /* @} *//* Usage page 0x0C (additional media keys) */

    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
    /* @{ */

    entry(SDL_SCANCODE_SOFTLEFT); /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    entry(SDL_SCANCODE_SOFTRIGHT); /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    entry(SDL_SCANCODE_CALL); /**< Used for accepting phone calls. */
    entry(SDL_SCANCODE_ENDCALL); /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */
}

u32_flag_s FindConstantValueByString(const char* name) {
    struct StringIDPair* out;
    HASH_FIND_STR(constant_strings,name, out);
    if(out == NULL)
        return u32_flag((uint32_t)-1, false);
    return u32_flag(out->id, true);
}
