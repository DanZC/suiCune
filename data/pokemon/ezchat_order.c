#include "../../constants.h"
#include "ezchat_order.h"

static const species_t A[] = {ABRA, AERODACTYL, AIPOM, ALAKAZAM, AMPHAROS, ARBOK, ARCANINE, ARIADOS, ARTICUNO, AZUMARILL, (species_t)-1}; // a
static const species_t B[] = {BAYLEEF, BEEDRILL, BELLOSSOM, BELLSPROUT, BLASTOISE, BLISSEY, BULBASAUR, BUTTERFREE, (species_t)-1}; // b
static const species_t C[] = {CATERPIE, CELEBI, CHANSEY, CHARIZARD, CHARMANDER, CHARMELEON, CHIKORITA, CHINCHOU, CLEFABLE, CLEFAIRY, CLEFFA, CLOYSTER, CORSOLA, CROBAT, CROCONAW, CUBONE, CYNDAQUIL, (species_t)-1}; // c
static const species_t D[] = {DELIBIRD, DEWGONG, DIGLETT, DITTO, DODRIO, DODUO, DONPHAN, DRAGONAIR, DRAGONITE, DRATINI, DROWZEE, DUGTRIO, DUNSPARCE, (species_t)-1}; // d
static const species_t E[] = {EEVEE, EKANS, ELECTABUZZ, ELECTRODE, ELEKID, ENTEI, ESPEON, EXEGGCUTE, EXEGGUTOR, -1};
static const species_t F[] = {FARFETCH_D, FEAROW, FERALIGATR, FLAAFFY, FLAREON, FORRETRESS, FURRET, -1};
static const species_t G[] = {GASTLY, GENGAR, GEODUDE, GIRAFARIG, GLIGAR, GLOOM, GOLBAT, GOLDEEN, GOLDUCK, GOLEM, GRANBULL, GRAVELER, GRIMER, GROWLITHE, GYARADOS, -1};
static const species_t H[] = {HAUNTER, HERACROSS, HITMONCHAN, HITMONLEE, HITMONTOP, HO_OH, HOOTHOOT, HOPPIP, HORSEA, HOUNDOOM, HOUNDOUR, HYPNO, -1};
static const species_t I[] = {IGGLYBUFF, IVYSAUR, -1};
static const species_t J[] = {JIGGLYPUFF, JOLTEON, JUMPLUFF, JYNX, -1};
static const species_t K[] = {KABUTO, KABUTOPS, KADABRA, KAKUNA, KANGASKHAN, KINGDRA, KINGLER, KOFFING, KRABBY, -1};
static const species_t L[] = {LANTURN, LAPRAS, LARVITAR, LEDIAN, LEDYBA, LICKITUNG, LUGIA, -1};
static const species_t M[] = {MACHAMP, MACHOKE, MACHOP, MAGBY, MAGCARGO, MAGIKARP, MAGMAR, MAGNEMITE, MAGNETON, MANKEY, MANTINE, MAREEP, MARILL, MAROWAK, MEGANIUM, MEOWTH, METAPOD, MEW, MEWTWO, MILTANK, MISDREAVUS, MOLTRES, MR__MIME, MUK, MURKROW, -1};
static const species_t N[] = {NATU, NIDOKING, NIDOQUEEN, NIDORAN_F, NIDORAN_M, NIDORINA, NIDORINO, NINETALES, NOCTOWL, -1};
static const species_t O[] = {OCTILLERY, ODDISH, OMANYTE, OMASTAR, ONIX, -1};
static const species_t P[] = {PARAS, PARASECT, PERSIAN, PHANPY, PICHU, PIDGEOT, PIDGEOTTO, PIDGEY, PIKACHU, PILOSWINE, PINECO, PINSIR, POLITOED, POLIWAG, POLIWHIRL, POLIWRATH, PONYTA, PORYGON, PORYGON2, PRIMEAPE, PSYDUCK, PUPITAR, -1};
static const species_t Q[] = {QUAGSIRE, QUILAVA, QWILFISH, -1};
static const species_t R[] = {RAICHU, RAIKOU, RAPIDASH, RATICATE, RATTATA, REMORAID, RHYDON, RHYHORN, -1};
static const species_t S[] = {SANDSHREW, SANDSLASH, SCIZOR, SCYTHER, SEADRA, SEAKING, SEEL, SENTRET, SHELLDER, SHUCKLE, SKARMORY, SKIPLOOM, SLOWBRO, SLOWKING, SLOWPOKE, SLUGMA, SMEARGLE, SMOOCHUM, SNEASEL, SNORLAX, SNUBBULL, SPEAROW, SPINARAK, SQUIRTLE, STANTLER, STARMIE, STARYU, STEELIX, SUDOWOODO, SUICUNE, SUNFLORA, SUNKERN, SWINUB, -1};
static const species_t T[] = {TANGELA, TAUROS, TEDDIURSA, TENTACOOL, TENTACRUEL, TOGEPI, TOGETIC, TOTODILE, TYPHLOSION, TYRANITAR, TYROGUE, -1};
static const species_t U[] = {UMBREON, UNOWN, URSARING, -1};
static const species_t V[] = {VAPOREON, VENOMOTH, VENONAT, VENUSAUR, VICTREEBEL, VILEPLUME, VOLTORB, VULPIX, -1};
static const species_t W[] = {WARTORTLE, WEEDLE, WEEPINBELL, WEEZING, WIGGLYTUFF, WOBBUFFET, WOOPER, -1};
static const species_t X[] = {XATU, -1};
static const species_t Y[] = {YANMA,  -1};
static const species_t Z[] = {ZAPDOS, ZUBAT, -1};
static const species_t ETC[] = {-1};
static const species_t end[] = {-1};

// Every Pokémon sorted by their English names in alphabetic order.

const species_t * const EZChat_SortedPokemon[] = {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    ETC,
    end,
};
