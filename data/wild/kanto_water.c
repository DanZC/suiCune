#include "../../constants.h"
// Kanto Pokémon in water
#if FEATURE_EMBED_DATA
struct WildWaterMons* KantoWaterWildMons = (struct WildWaterMons[]){
  {MAP_ID(TOHJO_FALLS),
    .encounterRate=4,
    .mons={
      {20, GOLDEEN},
      {20, SLOWPOKE},
      {20, SEAKING}
    }
  },
  {MAP_ID(VERMILION_PORT),
    .encounterRate=2,
    .mons={
      {35, TENTACOOL},
      {30, TENTACOOL},
      {35, TENTACRUEL}
    }
  },
  {MAP_ID(ROUTE_4),
    .encounterRate=4,
    .mons={
      {10, GOLDEEN},
      {5, GOLDEEN},
      {10, SEAKING}
    }
  },
  {MAP_ID(ROUTE_6),
    .encounterRate=2,
    .mons={
      {10, PSYDUCK},
      {5, PSYDUCK},
      {10, GOLDUCK}
    }
  },
  {MAP_ID(ROUTE_9),
    .encounterRate=4,
    .mons={
      {15, GOLDEEN},
      {10, GOLDEEN},
      {15, SEAKING}
    }
  },
  {MAP_ID(ROUTE_10_NORTH),
    .encounterRate=4,
    .mons={
      {15, GOLDEEN},
      {10, GOLDEEN},
      {15, SEAKING}
    }
  },
  {MAP_ID(ROUTE_12),
    .encounterRate=6,
    .mons={
      {25, TENTACOOL},
      {25, QUAGSIRE},
      {25, TENTACRUEL}
    }
  },
  {MAP_ID(ROUTE_13),
    .encounterRate=6,
    .mons={
      {25, TENTACOOL},
      {25, QUAGSIRE},
      {25, TENTACRUEL}
    }
  },
  {MAP_ID(ROUTE_19),
    .encounterRate=6,
    .mons={
      {35, TENTACOOL},
      {30, TENTACOOL},
      {35, TENTACRUEL}
    }
  },
  {MAP_ID(ROUTE_20),
    .encounterRate=6,
    .mons={
      {35, TENTACOOL},
      {30, TENTACOOL},
      {35, TENTACRUEL}
    }
  },
  {MAP_ID(ROUTE_21),
    .encounterRate=6,
    .mons={
      {35, TENTACOOL},
      {30, TENTACOOL},
      {35, TENTACRUEL}
    }
  },
  {MAP_ID(ROUTE_22),
    .encounterRate=2,
    .mons={
      {10, POLIWAG},
      {5, POLIWAG},
      {10, POLIWHIRL}
    }
  },
  {MAP_ID(ROUTE_24),
    .encounterRate=4,
    .mons={
      {10, GOLDEEN},
      {5, GOLDEEN},
      {10, SEAKING}
    }
  },
  {MAP_ID(ROUTE_25),
    .encounterRate=4,
    .mons={
      {10, GOLDEEN},
      {5, GOLDEEN},
      {10, SEAKING}
    }
  },
  {MAP_ID(ROUTE_26),
    .encounterRate=6,
    .mons={
      {30, TENTACOOL},
      {25, TENTACOOL},
      {30, TENTACRUEL}
    }
  },
  {MAP_ID(ROUTE_27),
    .encounterRate=6,
    .mons={
      {20, TENTACOOL},
      {15, TENTACOOL},
      {20, TENTACRUEL}
    }
  },
  {MAP_ID(ROUTE_28),
    .encounterRate=2,
    .mons={
      {40, POLIWAG},
      {35, POLIWAG},
      {40, POLIWHIRL}
    }
  },
  {MAP_ID(PALLET_TOWN),
    .encounterRate=6,
    .mons={
      {35, TENTACOOL},
      {30, TENTACOOL},
      {35, TENTACRUEL}
    }
  },
  {MAP_ID(VIRIDIAN_CITY),
    .encounterRate=2,
    .mons={
      {10, POLIWAG},
      {5, POLIWAG},
      {10, POLIWHIRL}
    }
  },
  {MAP_ID(CERULEAN_CITY),
    .encounterRate=4,
    .mons={
      {10, GOLDEEN},
      {5, GOLDEEN},
      {10, SEAKING}
    }
  },
  {MAP_ID(VERMILION_CITY),
    .encounterRate=6,
    .mons={
      {35, TENTACOOL},
      {30, TENTACOOL},
      {35, TENTACRUEL}
    }
  },
  {MAP_ID(CELADON_CITY),
    .encounterRate=2,
    .mons={
      {20, GRIMER},
      {15, GRIMER},
      {15, MUK}
    }
  },
  {MAP_ID(FUCHSIA_CITY),
    .encounterRate=2,
    .mons={
      {20, MAGIKARP},
      {15, MAGIKARP},
      {10, MAGIKARP}
    }
  },
  {MAP_ID(CINNABAR_ISLAND),
    .encounterRate=6,
    .mons={
      {35, TENTACOOL},
      {30, TENTACOOL},
      {35, TENTACRUEL}
    }
  }
}
#else
// Data is stored in kanto_water.json
struct WildWaterMons* KantoWaterWildMons;
#endif // FEATURE_EMBED_DATA
