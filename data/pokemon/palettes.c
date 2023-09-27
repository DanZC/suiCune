#include "../../constants.h"
#include "palettes.h"

// Shiny palettes are defined directly, not extracted from front pic.
// NULL entries are defined separately in the PokemonCustomPals list.
// table_width PAL_COLOR_SIZE * 2 * 2, PokemonPalettes
const char* PokemonShinyPals[] = {
    [0x000] = NULL,
    [BULBASAUR] = "gfx/pokemon/bulbasaur/shiny.pal",
    [IVYSAUR] = "gfx/pokemon/ivysaur/shiny.pal",
    [VENUSAUR] = "gfx/pokemon/venusaur/shiny.pal",
    [CHARMANDER] = "gfx/pokemon/charmander/shiny.pal",
    [CHARMELEON] = "gfx/pokemon/charmeleon/shiny.pal",
    [CHARIZARD] = "gfx/pokemon/charizard/shiny.pal",
    [SQUIRTLE] = "gfx/pokemon/squirtle/shiny.pal",
    [WARTORTLE] = "gfx/pokemon/wartortle/shiny.pal",
    [BLASTOISE] = "gfx/pokemon/blastoise/shiny.pal",
    [CATERPIE] = "gfx/pokemon/caterpie/shiny.pal",
    [METAPOD] = "gfx/pokemon/metapod/shiny.pal",
    [BUTTERFREE] = "gfx/pokemon/butterfree/shiny.pal",
    [WEEDLE] = "gfx/pokemon/weedle/shiny.pal",
    [KAKUNA] = "gfx/pokemon/kakuna/shiny.pal",
    [BEEDRILL] = "gfx/pokemon/beedrill/shiny.pal",
    [PIDGEY] = "gfx/pokemon/pidgey/shiny.pal",
    [PIDGEOTTO] = "gfx/pokemon/pidgeotto/shiny.pal",
    [PIDGEOT] = "gfx/pokemon/pidgeot/shiny.pal",
    [RATTATA] = "gfx/pokemon/rattata/shiny.pal",
    [RATICATE] = "gfx/pokemon/raticate/shiny.pal",
    [SPEAROW] = "gfx/pokemon/spearow/shiny.pal",
    [FEAROW] = "gfx/pokemon/fearow/shiny.pal",
    [EKANS] = "gfx/pokemon/ekans/shiny.pal",
    [ARBOK] = "gfx/pokemon/arbok/shiny.pal",
    [PIKACHU] = "gfx/pokemon/pikachu/shiny.pal",
    [RAICHU] = "gfx/pokemon/raichu/shiny.pal",
    [SANDSHREW] = "gfx/pokemon/sandshrew/shiny.pal",
    [SANDSLASH] = "gfx/pokemon/sandslash/shiny.pal",
    [NIDORAN_F] = "gfx/pokemon/nidoran_f/shiny.pal",
    [NIDORINA] = "gfx/pokemon/nidorina/shiny.pal",
    [NIDOQUEEN] = "gfx/pokemon/nidoqueen/shiny.pal",
    [NIDORAN_M] = "gfx/pokemon/nidoran_m/shiny.pal",
    [NIDORINO] = "gfx/pokemon/nidorino/shiny.pal",
    [NIDOKING] = "gfx/pokemon/nidoking/shiny.pal",
    [CLEFAIRY] = "gfx/pokemon/clefairy/shiny.pal",
    [CLEFABLE] = "gfx/pokemon/clefable/shiny.pal",
    [VULPIX] = "gfx/pokemon/vulpix/shiny.pal",
    [NINETALES] = "gfx/pokemon/ninetales/shiny.pal",
    [JIGGLYPUFF] = "gfx/pokemon/jigglypuff/shiny.pal",
    [WIGGLYTUFF] = "gfx/pokemon/wigglytuff/shiny.pal",
    [ZUBAT] = "gfx/pokemon/zubat/shiny.pal",
    [GOLBAT] = "gfx/pokemon/golbat/shiny.pal",
    [ODDISH] = "gfx/pokemon/oddish/shiny.pal",
    [GLOOM] = "gfx/pokemon/gloom/shiny.pal",
    [VILEPLUME] = "gfx/pokemon/vileplume/shiny.pal",
    [PARAS] = "gfx/pokemon/paras/shiny.pal",
    [PARASECT] = "gfx/pokemon/parasect/shiny.pal",
    [VENONAT] = "gfx/pokemon/venonat/shiny.pal",
    [VENOMOTH] = "gfx/pokemon/venomoth/shiny.pal",
    [DIGLETT] = "gfx/pokemon/diglett/shiny.pal",
    [DUGTRIO] = "gfx/pokemon/dugtrio/shiny.pal",
    [MEOWTH] = "gfx/pokemon/meowth/shiny.pal",
    [PERSIAN] = "gfx/pokemon/persian/shiny.pal",
    [PSYDUCK] = "gfx/pokemon/psyduck/shiny.pal",
    [GOLDUCK] = "gfx/pokemon/golduck/shiny.pal",
    [MANKEY] = "gfx/pokemon/mankey/shiny.pal",
    [PRIMEAPE] = "gfx/pokemon/primeape/shiny.pal",
    [GROWLITHE] = "gfx/pokemon/growlithe/shiny.pal",
    [ARCANINE] = "gfx/pokemon/arcanine/shiny.pal",
    [POLIWAG] = "gfx/pokemon/poliwag/shiny.pal",
    [POLIWHIRL] = "gfx/pokemon/poliwhirl/shiny.pal",
    [POLIWRATH] = "gfx/pokemon/poliwrath/shiny.pal",
    [ABRA] = "gfx/pokemon/abra/shiny.pal",
    [KADABRA] = "gfx/pokemon/kadabra/shiny.pal",
    [ALAKAZAM] = "gfx/pokemon/alakazam/shiny.pal",
    [MACHOP] = "gfx/pokemon/machop/shiny.pal",
    [MACHOKE] = "gfx/pokemon/machoke/shiny.pal",
    [MACHAMP] = "gfx/pokemon/machamp/shiny.pal",
    [BELLSPROUT] = "gfx/pokemon/bellsprout/shiny.pal",
    [WEEPINBELL] = "gfx/pokemon/weepinbell/shiny.pal",
    [VICTREEBEL] = "gfx/pokemon/victreebel/shiny.pal",
    [TENTACOOL] = "gfx/pokemon/tentacool/shiny.pal",
    [TENTACRUEL] = "gfx/pokemon/tentacruel/shiny.pal",
    [GEODUDE] = "gfx/pokemon/geodude/shiny.pal",
    [GRAVELER] = "gfx/pokemon/graveler/shiny.pal",
    [GOLEM] = "gfx/pokemon/golem/shiny.pal",
    [PONYTA] = "gfx/pokemon/ponyta/shiny.pal",
    [RAPIDASH] = "gfx/pokemon/rapidash/shiny.pal",
    [SLOWPOKE] = "gfx/pokemon/slowpoke/shiny.pal",
    [SLOWBRO] = "gfx/pokemon/slowbro/shiny.pal",
    [MAGNEMITE] = "gfx/pokemon/magnemite/shiny.pal",
    [MAGNETON] = "gfx/pokemon/magneton/shiny.pal",
    [FARFETCH_D] = "gfx/pokemon/farfetch_d/shiny.pal",
    [DODUO] = "gfx/pokemon/doduo/shiny.pal",
    [DODRIO] = "gfx/pokemon/dodrio/shiny.pal",
    [SEEL] = "gfx/pokemon/seel/shiny.pal",
    [DEWGONG] = "gfx/pokemon/dewgong/shiny.pal",
    [GRIMER] = "gfx/pokemon/grimer/shiny.pal",
    [MUK] = "gfx/pokemon/muk/shiny.pal",
    [SHELLDER] = "gfx/pokemon/shellder/shiny.pal",
    [CLOYSTER] = "gfx/pokemon/cloyster/shiny.pal",
    [GASTLY] = "gfx/pokemon/gastly/shiny.pal",
    [HAUNTER] = "gfx/pokemon/haunter/shiny.pal",
    [GENGAR] = "gfx/pokemon/gengar/shiny.pal",
    [ONIX] = "gfx/pokemon/onix/shiny.pal",
    [DROWZEE] = "gfx/pokemon/drowzee/shiny.pal",
    [HYPNO] = "gfx/pokemon/hypno/shiny.pal",
    [KRABBY] = "gfx/pokemon/krabby/shiny.pal",
    [KINGLER] = "gfx/pokemon/kingler/shiny.pal",
    [VOLTORB] = "gfx/pokemon/voltorb/shiny.pal",
    [ELECTRODE] = "gfx/pokemon/electrode/shiny.pal",
    [EXEGGCUTE] = "gfx/pokemon/exeggcute/shiny.pal",
    [EXEGGUTOR] = "gfx/pokemon/exeggutor/shiny.pal",
    [CUBONE] = "gfx/pokemon/cubone/shiny.pal",
    [MAROWAK] = "gfx/pokemon/marowak/shiny.pal",
    [HITMONLEE] = "gfx/pokemon/hitmonlee/shiny.pal",
    [HITMONCHAN] = "gfx/pokemon/hitmonchan/shiny.pal",
    [LICKITUNG] = "gfx/pokemon/lickitung/shiny.pal",
    [KOFFING] = "gfx/pokemon/koffing/shiny.pal",
    [WEEZING] = "gfx/pokemon/weezing/shiny.pal",
    [RHYHORN] = "gfx/pokemon/rhyhorn/shiny.pal",
    [RHYDON] = "gfx/pokemon/rhydon/shiny.pal",
    [CHANSEY] = "gfx/pokemon/chansey/shiny.pal",
    [TANGELA] = "gfx/pokemon/tangela/shiny.pal",
    [KANGASKHAN] = "gfx/pokemon/kangaskhan/shiny.pal",
    [HORSEA] = "gfx/pokemon/horsea/shiny.pal",
    [SEADRA] = "gfx/pokemon/seadra/shiny.pal",
    [GOLDEEN] = "gfx/pokemon/goldeen/shiny.pal",
    [SEAKING] = "gfx/pokemon/seaking/shiny.pal",
    [STARYU] = "gfx/pokemon/staryu/shiny.pal",
    [STARMIE] = "gfx/pokemon/starmie/shiny.pal",
    [MR__MIME] = "gfx/pokemon/mr__mime/shiny.pal",
    [SCYTHER] = "gfx/pokemon/scyther/shiny.pal",
    [JYNX] = "gfx/pokemon/jynx/shiny.pal",
    [ELECTABUZZ] = "gfx/pokemon/electabuzz/shiny.pal",
    [MAGMAR] = "gfx/pokemon/magmar/shiny.pal",
    [PINSIR] = "gfx/pokemon/pinsir/shiny.pal",
    [TAUROS] = "gfx/pokemon/tauros/shiny.pal",
    [MAGIKARP] = "gfx/pokemon/magikarp/shiny.pal",
    [GYARADOS] = "gfx/pokemon/gyarados/shiny.pal",
    [LAPRAS] = "gfx/pokemon/lapras/shiny.pal",
    [DITTO] = "gfx/pokemon/ditto/shiny.pal",
    [EEVEE] = "gfx/pokemon/eevee/shiny.pal",
    [VAPOREON] = "gfx/pokemon/vaporeon/shiny.pal",
    [JOLTEON] = "gfx/pokemon/jolteon/shiny.pal",
    [FLAREON] = "gfx/pokemon/flareon/shiny.pal",
    [PORYGON] = "gfx/pokemon/porygon/shiny.pal",
    [OMANYTE] = "gfx/pokemon/omanyte/shiny.pal",
    [OMASTAR] = "gfx/pokemon/omastar/shiny.pal",
    [KABUTO] = "gfx/pokemon/kabuto/shiny.pal",
    [KABUTOPS] = "gfx/pokemon/kabutops/shiny.pal",
    [AERODACTYL] = "gfx/pokemon/aerodactyl/shiny.pal",
    [SNORLAX] = "gfx/pokemon/snorlax/shiny.pal",
    [ARTICUNO] = "gfx/pokemon/articuno/shiny.pal",
    [ZAPDOS] = "gfx/pokemon/zapdos/shiny.pal",
    [MOLTRES] = "gfx/pokemon/moltres/shiny.pal",
    [DRATINI] = "gfx/pokemon/dratini/shiny.pal",
    [DRAGONAIR] = "gfx/pokemon/dragonair/shiny.pal",
    [DRAGONITE] = "gfx/pokemon/dragonite/shiny.pal",
    [MEWTWO] = "gfx/pokemon/mewtwo/shiny.pal",
    [MEW] = "gfx/pokemon/mew/shiny.pal",
    [CHIKORITA] = "gfx/pokemon/chikorita/shiny.pal",
    [BAYLEEF] = "gfx/pokemon/bayleef/shiny.pal",
    [MEGANIUM] = "gfx/pokemon/meganium/shiny.pal",
    [CYNDAQUIL] = "gfx/pokemon/cyndaquil/shiny.pal",
    [QUILAVA] = "gfx/pokemon/quilava/shiny.pal",
    [TYPHLOSION] = "gfx/pokemon/typhlosion/shiny.pal",
    [TOTODILE] = "gfx/pokemon/totodile/shiny.pal",
    [CROCONAW] = "gfx/pokemon/croconaw/shiny.pal",
    [FERALIGATR] = "gfx/pokemon/feraligatr/shiny.pal",
    [SENTRET] = "gfx/pokemon/sentret/shiny.pal",
    [FURRET] = "gfx/pokemon/furret/shiny.pal",
    [HOOTHOOT] = "gfx/pokemon/hoothoot/shiny.pal",
    [NOCTOWL] = "gfx/pokemon/noctowl/shiny.pal",
    [LEDYBA] = "gfx/pokemon/ledyba/shiny.pal",
    [LEDIAN] = "gfx/pokemon/ledian/shiny.pal",
    [SPINARAK] = "gfx/pokemon/spinarak/shiny.pal",
    [ARIADOS] = "gfx/pokemon/ariados/shiny.pal",
    [CROBAT] = "gfx/pokemon/crobat/shiny.pal",
    [CHINCHOU] = "gfx/pokemon/chinchou/shiny.pal",
    [LANTURN] = "gfx/pokemon/lanturn/shiny.pal",
    [PICHU] = "gfx/pokemon/pichu/shiny.pal",
    [CLEFFA] = "gfx/pokemon/cleffa/shiny.pal",
    [IGGLYBUFF] = "gfx/pokemon/igglybuff/shiny.pal",
    [TOGEPI] = "gfx/pokemon/togepi/shiny.pal",
    [TOGETIC] = "gfx/pokemon/togetic/shiny.pal",
    [NATU] = "gfx/pokemon/natu/shiny.pal",
    [XATU] = "gfx/pokemon/xatu/shiny.pal",
    [MAREEP] = "gfx/pokemon/mareep/shiny.pal",
    [FLAAFFY] = "gfx/pokemon/flaaffy/shiny.pal",
    [AMPHAROS] = "gfx/pokemon/ampharos/shiny.pal",
    [BELLOSSOM] = "gfx/pokemon/bellossom/shiny.pal",
    [MARILL] = "gfx/pokemon/marill/shiny.pal",
    [AZUMARILL] = "gfx/pokemon/azumarill/shiny.pal",
    [SUDOWOODO] = "gfx/pokemon/sudowoodo/shiny.pal",
    [POLITOED] = "gfx/pokemon/politoed/shiny.pal",
    [HOPPIP] = "gfx/pokemon/hoppip/shiny.pal",
    [SKIPLOOM] = "gfx/pokemon/skiploom/shiny.pal",
    [JUMPLUFF] = "gfx/pokemon/jumpluff/shiny.pal",
    [AIPOM] = "gfx/pokemon/aipom/shiny.pal",
    [SUNKERN] = "gfx/pokemon/sunkern/shiny.pal",
    [SUNFLORA] = "gfx/pokemon/sunflora/shiny.pal",
    [YANMA] = "gfx/pokemon/yanma/shiny.pal",
    [WOOPER] = "gfx/pokemon/wooper/shiny.pal",
    [QUAGSIRE] = "gfx/pokemon/quagsire/shiny.pal",
    [ESPEON] = "gfx/pokemon/espeon/shiny.pal",
    [UMBREON] = "gfx/pokemon/umbreon/shiny.pal",
    [MURKROW] = "gfx/pokemon/murkrow/shiny.pal",
    [SLOWKING] = "gfx/pokemon/slowking/shiny.pal",
    [MISDREAVUS] = "gfx/pokemon/misdreavus/shiny.pal",
    [UNOWN] = "gfx/pokemon/unown/shiny.pal",
    [WOBBUFFET] = "gfx/pokemon/wobbuffet/shiny.pal",
    [GIRAFARIG] = "gfx/pokemon/girafarig/shiny.pal",
    [PINECO] = "gfx/pokemon/pineco/shiny.pal",
    [FORRETRESS] = "gfx/pokemon/forretress/shiny.pal",
    [DUNSPARCE] = "gfx/pokemon/dunsparce/shiny.pal",
    [GLIGAR] = "gfx/pokemon/gligar/shiny.pal",
    [STEELIX] = "gfx/pokemon/steelix/shiny.pal",
    [SNUBBULL] = "gfx/pokemon/snubbull/shiny.pal",
    [GRANBULL] = "gfx/pokemon/granbull/shiny.pal",
    [QWILFISH] = "gfx/pokemon/qwilfish/shiny.pal",
    [SCIZOR] = "gfx/pokemon/scizor/shiny.pal",
    [SHUCKLE] = "gfx/pokemon/shuckle/shiny.pal",
    [HERACROSS] = "gfx/pokemon/heracross/shiny.pal",
    [SNEASEL] = "gfx/pokemon/sneasel/shiny.pal",
    [TEDDIURSA] = "gfx/pokemon/teddiursa/shiny.pal",
    [URSARING] = "gfx/pokemon/ursaring/shiny.pal",
    [SLUGMA] = "gfx/pokemon/slugma/shiny.pal",
    [MAGCARGO] = "gfx/pokemon/magcargo/shiny.pal",
    [SWINUB] = "gfx/pokemon/swinub/shiny.pal",
    [PILOSWINE] = "gfx/pokemon/piloswine/shiny.pal",
    [CORSOLA] = "gfx/pokemon/corsola/shiny.pal",
    [REMORAID] = "gfx/pokemon/remoraid/shiny.pal",
    [OCTILLERY] = "gfx/pokemon/octillery/shiny.pal",
    [DELIBIRD] = "gfx/pokemon/delibird/shiny.pal",
    [MANTINE] = "gfx/pokemon/mantine/shiny.pal",
    [SKARMORY] = "gfx/pokemon/skarmory/shiny.pal",
    [HOUNDOUR] = "gfx/pokemon/houndour/shiny.pal",
    [HOUNDOOM] = "gfx/pokemon/houndoom/shiny.pal",
    [KINGDRA] = "gfx/pokemon/kingdra/shiny.pal",
    [PHANPY] = "gfx/pokemon/phanpy/shiny.pal",
    [DONPHAN] = "gfx/pokemon/donphan/shiny.pal",
    [PORYGON2] = "gfx/pokemon/porygon2/shiny.pal",
    [STANTLER] = "gfx/pokemon/stantler/shiny.pal",
    [SMEARGLE] = "gfx/pokemon/smeargle/shiny.pal",
    [TYROGUE] = "gfx/pokemon/tyrogue/shiny.pal",
    [HITMONTOP] = "gfx/pokemon/hitmontop/shiny.pal",
    [SMOOCHUM] = "gfx/pokemon/smoochum/shiny.pal",
    [ELEKID] = "gfx/pokemon/elekid/shiny.pal",
    [MAGBY] = "gfx/pokemon/magby/shiny.pal",
    [MILTANK] = "gfx/pokemon/miltank/shiny.pal",
    [BLISSEY] = "gfx/pokemon/blissey/shiny.pal",
    [RAIKOU] = "gfx/pokemon/raikou/shiny.pal",
    [ENTEI] = "gfx/pokemon/entei/shiny.pal",
    [SUICUNE] = "gfx/pokemon/suicune/shiny.pal",
    [LARVITAR] = "gfx/pokemon/larvitar/shiny.pal",
    [PUPITAR] = "gfx/pokemon/pupitar/shiny.pal",
    [TYRANITAR] = "gfx/pokemon/tyranitar/shiny.pal",
    [LUGIA] = "gfx/pokemon/lugia/shiny.pal",
    [HO_OH] = "gfx/pokemon/ho_oh/shiny.pal",
    [CELEBI] = "gfx/pokemon/celebi/shiny.pal",
    [252] = NULL,
    [EGG] = "gfx/pokemon/egg/shiny.pal",
    [254] = NULL,
    [255] = NULL,
};

static_assert(lengthof(PokemonShinyPals) == 0x100, "");

const struct CustomSpeciesPalEntry PokemonCustomPals[] = {
    {0x000, .pals= {
    // Normal
        rgb(30, 22, 17),
	    rgb(16, 14, 19),
    // Shiny
        rgb(30, 22, 17),
	    rgb(16, 14, 19),
    }},
    {252, .pals = {
    // 252
        rgb(30, 26, 11),
        rgb(23, 16, 00),
    // 252 shiny
        rgb(30, 26, 11),
        rgb(23, 16, 00),
    }},
    {254, .pals = {
    // 254
        rgb(30, 26, 11),
        rgb(23, 16, 00),
    // 254 shiny
        rgb(30, 26, 11),
        rgb(23, 16, 00),
    }},
    {255, .pals = {
    // 255
        rgb(23, 23, 23),
        rgb(17, 17, 17),
    // 255 shiny
        rgb(23, 23, 23),
        rgb(17, 17, 17),
    }}
};