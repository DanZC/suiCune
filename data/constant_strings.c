#include "../constants.h"
#include <string.h>
#include <assert.h>
#include "../input_system/uthash.h"

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
    } while(0)

#define hm_entry(hmNum, hmName)       do {  \
        entry(hmNum);                       \
        entry(HM_##hmName);                 \
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
}

u32_flag_s FindConstantValueByString(const char* name) {
    struct StringIDPair* out;
    HASH_FIND_STR(constant_strings,name, out);
    if(out == NULL)
        return u32_flag((uint32_t)-1, false);
    return u32_flag(out->id, true);
}