#include "../../constants.h"
#include "menu_icons.h"

// party menu icons

const uint8_t MonMenuIcons[] = {
	[BULBASAUR-1]   = ICON_BULBASAUR,
	[IVYSAUR-1]     = ICON_BULBASAUR,
	[VENUSAUR-1]    = ICON_BULBASAUR,
	[CHARMANDER-1]  = ICON_CHARMANDER,
	[CHARMELEON-1]  = ICON_CHARMANDER,
	[CHARIZARD-1]   = ICON_BIGMON,
	[SQUIRTLE-1]    = ICON_SQUIRTLE,
	[WARTORTLE-1]   = ICON_SQUIRTLE,
	[BLASTOISE-1]   = ICON_SQUIRTLE,
	[CATERPIE-1]    = ICON_CATERPILLAR,
	[METAPOD-1]     = ICON_CATERPILLAR,
	[BUTTERFREE-1]  = ICON_MOTH,
	[WEEDLE-1]      = ICON_CATERPILLAR,
	[KAKUNA-1]      = ICON_CATERPILLAR,
	[BEEDRILL-1]    = ICON_BUG,
	[PIDGEY-1]      = ICON_BIRD,
	[PIDGEOTTO-1]   = ICON_BIRD,
	[PIDGEOT-1]     = ICON_BIRD,
	[RATTATA-1]     = ICON_FOX,
	[RATICATE-1]    = ICON_FOX,
	[SPEAROW-1]     = ICON_BIRD,
	[FEAROW-1]      = ICON_BIRD,
	[EKANS-1]       = ICON_SERPENT,
	[ARBOK-1]       = ICON_SERPENT,
	[PIKACHU-1]     = ICON_PIKACHU,
	[RAICHU-1]      = ICON_PIKACHU,
	[SANDSHREW-1]   = ICON_MONSTER,
	[SANDSLASH-1]   = ICON_MONSTER,
	[NIDORAN_F-1]   = ICON_FOX,
	[NIDORINA-1]    = ICON_FOX,
	[NIDOQUEEN-1]   = ICON_MONSTER,
	[NIDORAN_M-1]   = ICON_FOX,
	[NIDORINO-1]    = ICON_FOX,
	[NIDOKING-1]    = ICON_MONSTER,
	[CLEFAIRY-1]    = ICON_CLEFAIRY,
	[CLEFABLE-1]    = ICON_CLEFAIRY,
	[VULPIX-1]      = ICON_FOX,
	[NINETALES-1]   = ICON_FOX,
	[JIGGLYPUFF-1]  = ICON_JIGGLYPUFF,
	[WIGGLYTUFF-1]  = ICON_JIGGLYPUFF,
	[ZUBAT-1]       = ICON_BAT,
	[GOLBAT-1]      = ICON_BAT,
	[ODDISH-1]      = ICON_ODDISH,
	[GLOOM-1]       = ICON_ODDISH,
	[VILEPLUME-1]   = ICON_ODDISH,
	[PARAS-1]       = ICON_BUG,
	[PARASECT-1]    = ICON_BUG,
	[VENONAT-1]     = ICON_CATERPILLAR,
	[VENOMOTH-1]    = ICON_MOTH,
	[DIGLETT-1]     = ICON_DIGLETT,
	[DUGTRIO-1]     = ICON_DIGLETT,
	[MEOWTH-1]      = ICON_FOX,
	[PERSIAN-1]     = ICON_FOX,
	[PSYDUCK-1]     = ICON_MONSTER,
	[GOLDUCK-1]     = ICON_MONSTER,
	[MANKEY-1]      = ICON_FIGHTER,
	[PRIMEAPE-1]    = ICON_FIGHTER,
	[GROWLITHE-1]   = ICON_FOX,
	[ARCANINE-1]    = ICON_FOX,
	[POLIWAG-1]     = ICON_POLIWAG,
	[POLIWHIRL-1]   = ICON_POLIWAG,
	[POLIWRATH-1]   = ICON_POLIWAG,
	[ABRA-1]        = ICON_HUMANSHAPE,
	[KADABRA-1]     = ICON_HUMANSHAPE,
	[ALAKAZAM-1]    = ICON_HUMANSHAPE,
	[MACHOP-1]      = ICON_FIGHTER,
	[MACHOKE-1]     = ICON_FIGHTER,
	[MACHAMP-1]     = ICON_FIGHTER,
	[BELLSPROUT-1]  = ICON_ODDISH,
	[WEEPINBELL-1]  = ICON_ODDISH,
	[VICTREEBEL-1]  = ICON_ODDISH,
	[TENTACOOL-1]   = ICON_JELLYFISH,
	[TENTACRUEL-1]  = ICON_JELLYFISH,
	[GEODUDE-1]     = ICON_GEODUDE,
	[GRAVELER-1]    = ICON_GEODUDE,
	[GOLEM-1]       = ICON_GEODUDE,
	[PONYTA-1]      = ICON_EQUINE,
	[RAPIDASH-1]    = ICON_EQUINE,
	[SLOWPOKE-1]    = ICON_SLOWPOKE,
	[SLOWBRO-1]     = ICON_SLOWPOKE,
	[MAGNEMITE-1]   = ICON_VOLTORB,
	[MAGNETON-1]    = ICON_VOLTORB,
	[FARFETCH_D-1]  = ICON_BIRD,
	[DODUO-1]       = ICON_BIRD,
	[DODRIO-1]      = ICON_BIRD,
	[SEEL-1]        = ICON_LAPRAS,
	[DEWGONG-1]     = ICON_LAPRAS,
	[GRIMER-1]      = ICON_BLOB,
	[MUK-1]         = ICON_BLOB,
	[SHELLDER-1]    = ICON_SHELL,
	[CLOYSTER-1]    = ICON_SHELL,
	[GASTLY-1]      = ICON_GHOST,
	[HAUNTER-1]     = ICON_GHOST,
	[GENGAR-1]      = ICON_GHOST,
	[ONIX-1]        = ICON_SERPENT,
	[DROWZEE-1]     = ICON_HUMANSHAPE,
	[HYPNO-1]       = ICON_HUMANSHAPE,
	[KRABBY-1]      = ICON_SHELL,
	[KINGLER-1]     = ICON_SHELL,
	[VOLTORB-1]     = ICON_VOLTORB,
	[ELECTRODE-1]   = ICON_VOLTORB,
	[EXEGGCUTE-1]   = ICON_ODDISH,
	[EXEGGUTOR-1]   = ICON_ODDISH,
	[CUBONE-1]      = ICON_MONSTER,
	[MAROWAK-1]     = ICON_MONSTER,
	[HITMONLEE-1]   = ICON_FIGHTER,
	[HITMONCHAN-1]  = ICON_FIGHTER,
	[LICKITUNG-1]   = ICON_MONSTER,
	[KOFFING-1]     = ICON_BLOB,
	[WEEZING-1]     = ICON_BLOB,
	[RHYHORN-1]     = ICON_EQUINE,
	[RHYDON-1]      = ICON_MONSTER,
	[CHANSEY-1]     = ICON_CLEFAIRY,
	[TANGELA-1]     = ICON_ODDISH,
	[KANGASKHAN-1]  = ICON_MONSTER,
	[HORSEA-1]      = ICON_FISH,
	[SEADRA-1]      = ICON_FISH,
	[GOLDEEN-1]     = ICON_FISH,
	[SEAKING-1]     = ICON_FISH,
	[STARYU-1]      = ICON_STARYU,
	[STARMIE-1]     = ICON_STARYU,
	[MR__MIME-1]    = ICON_HUMANSHAPE,
	[SCYTHER-1]     = ICON_BUG,
	[JYNX-1]        = ICON_HUMANSHAPE,
	[ELECTABUZZ-1]  = ICON_HUMANSHAPE,
	[MAGMAR-1]      = ICON_HUMANSHAPE,
	[PINSIR-1]      = ICON_BUG,
	[TAUROS-1]      = ICON_EQUINE,
	[MAGIKARP-1]    = ICON_FISH,
	[GYARADOS-1]    = ICON_GYARADOS,
	[LAPRAS-1]      = ICON_LAPRAS,
	[DITTO-1]       = ICON_BLOB,
	[EEVEE-1]       = ICON_FOX,
	[VAPOREON-1]    = ICON_FOX,
	[JOLTEON-1]     = ICON_FOX,
	[FLAREON-1]     = ICON_FOX,
	[PORYGON-1]     = ICON_VOLTORB,
	[OMANYTE-1]     = ICON_SHELL,
	[OMASTAR-1]     = ICON_SHELL,
	[KABUTO-1]      = ICON_SHELL,
	[KABUTOPS-1]    = ICON_SHELL,
	[AERODACTYL-1]  = ICON_BIRD,
	[SNORLAX-1]     = ICON_SNORLAX,
	[ARTICUNO-1]    = ICON_BIRD,
	[ZAPDOS-1]      = ICON_BIRD,
	[MOLTRES-1]     = ICON_BIRD,
	[DRATINI-1]     = ICON_SERPENT,
	[DRAGONAIR-1]   = ICON_SERPENT,
	[DRAGONITE-1]   = ICON_BIGMON,
	[MEWTWO-1]      = ICON_HUMANSHAPE,
	[MEW-1]         = ICON_HUMANSHAPE,
	[CHIKORITA-1]   = ICON_ODDISH,
	[BAYLEEF-1]     = ICON_ODDISH,
	[MEGANIUM-1]    = ICON_ODDISH,
	[CYNDAQUIL-1]   = ICON_FOX,
	[QUILAVA-1]     = ICON_FOX,
	[TYPHLOSION-1]  = ICON_FOX,
	[TOTODILE-1]    = ICON_MONSTER,
	[CROCONAW-1]    = ICON_MONSTER,
	[FERALIGATR-1]  = ICON_MONSTER,
	[SENTRET-1]     = ICON_FOX,
	[FURRET-1]      = ICON_FOX,
	[HOOTHOOT-1]    = ICON_BIRD,
	[NOCTOWL-1]     = ICON_BIRD,
	[LEDYBA-1]      = ICON_BUG,
	[LEDIAN-1]      = ICON_BUG,
	[SPINARAK-1]    = ICON_BUG,
	[ARIADOS-1]     = ICON_BUG,
	[CROBAT-1]      = ICON_BAT,
	[CHINCHOU-1]    = ICON_FISH,
	[LANTURN-1]     = ICON_FISH,
	[PICHU-1]       = ICON_PIKACHU,
	[CLEFFA-1]      = ICON_CLEFAIRY,
	[IGGLYBUFF-1]   = ICON_JIGGLYPUFF,
	[TOGEPI-1]      = ICON_CLEFAIRY,
	[TOGETIC-1]     = ICON_BIRD,
	[NATU-1]        = ICON_BIRD,
	[XATU-1]        = ICON_BIRD,
	[MAREEP-1]      = ICON_FOX,
	[FLAAFFY-1]     = ICON_MONSTER,
	[AMPHAROS-1]    = ICON_MONSTER,
	[BELLOSSOM-1]   = ICON_ODDISH,
	[MARILL-1]      = ICON_JIGGLYPUFF,
	[AZUMARILL-1]   = ICON_JIGGLYPUFF,
	[SUDOWOODO-1]   = ICON_SUDOWOODO,
	[POLITOED-1]    = ICON_POLIWAG,
	[HOPPIP-1]      = ICON_ODDISH,
	[SKIPLOOM-1]    = ICON_ODDISH,
	[JUMPLUFF-1]    = ICON_ODDISH,
	[AIPOM-1]       = ICON_MONSTER,
	[SUNKERN-1]     = ICON_ODDISH,
	[SUNFLORA-1]    = ICON_ODDISH,
	[YANMA-1]       = ICON_BUG,
	[WOOPER-1]      = ICON_MONSTER,
	[QUAGSIRE-1]    = ICON_MONSTER,
	[ESPEON-1]      = ICON_FOX,
	[UMBREON-1]     = ICON_FOX,
	[MURKROW-1]     = ICON_BIRD,
	[SLOWKING-1]    = ICON_SLOWPOKE,
	[MISDREAVUS-1]  = ICON_GHOST,
	[UNOWN-1]       = ICON_UNOWN,
	[WOBBUFFET-1]   = ICON_GHOST,
	[GIRAFARIG-1]   = ICON_EQUINE,
	[PINECO-1]      = ICON_BUG,
	[FORRETRESS-1]  = ICON_BUG,
	[DUNSPARCE-1]   = ICON_SERPENT,
	[GLIGAR-1]      = ICON_BUG,
	[STEELIX-1]     = ICON_SERPENT,
	[SNUBBULL-1]    = ICON_MONSTER,
	[GRANBULL-1]    = ICON_MONSTER,
	[QWILFISH-1]    = ICON_FISH,
	[SCIZOR-1]      = ICON_BUG,
	[SHUCKLE-1]     = ICON_BUG,
	[HERACROSS-1]   = ICON_BUG,
	[SNEASEL-1]     = ICON_FOX,
	[TEDDIURSA-1]   = ICON_MONSTER,
	[URSARING-1]    = ICON_MONSTER,
	[SLUGMA-1]      = ICON_BLOB,
	[MAGCARGO-1]    = ICON_BLOB,
	[SWINUB-1]      = ICON_EQUINE,
	[PILOSWINE-1]   = ICON_EQUINE,
	[CORSOLA-1]     = ICON_SHELL,
	[REMORAID-1]    = ICON_FISH,
	[OCTILLERY-1]   = ICON_FISH,
	[DELIBIRD-1]    = ICON_MONSTER,
	[MANTINE-1]     = ICON_FISH,
	[SKARMORY-1]    = ICON_BIRD,
	[HOUNDOUR-1]    = ICON_FOX,
	[HOUNDOOM-1]    = ICON_FOX,
	[KINGDRA-1]     = ICON_BIGMON,
	[PHANPY-1]      = ICON_EQUINE,
	[DONPHAN-1]     = ICON_EQUINE,
	[PORYGON2-1]    = ICON_VOLTORB,
	[STANTLER-1]    = ICON_EQUINE,
	[SMEARGLE-1]    = ICON_MONSTER,
	[TYROGUE-1]     = ICON_FIGHTER,
	[HITMONTOP-1]   = ICON_FIGHTER,
	[SMOOCHUM-1]    = ICON_HUMANSHAPE,
	[ELEKID-1]      = ICON_HUMANSHAPE,
	[MAGBY-1]       = ICON_HUMANSHAPE,
	[MILTANK-1]     = ICON_EQUINE,
	[BLISSEY-1]     = ICON_CLEFAIRY,
	[RAIKOU-1]      = ICON_FOX,
	[ENTEI-1]       = ICON_FOX,
	[SUICUNE-1]     = ICON_FOX,
	[LARVITAR-1]    = ICON_MONSTER,
	[PUPITAR-1]     = ICON_MONSTER,
	[TYRANITAR-1]   = ICON_MONSTER,
	[LUGIA-1]       = ICON_LUGIA,
	[HO_OH-1]       = ICON_HO_OH,
	[CELEBI-1]      = ICON_HUMANSHAPE,
};

static_assert(lengthof(MonMenuIcons) == NUM_POKEMON, "");