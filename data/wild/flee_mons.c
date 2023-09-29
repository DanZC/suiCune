#include "../../constants.h"

// referenced by TryEnemyFlee and FastBallMultiplier

const species_t SometimesFleeMons[] = {
    MAGNEMITE,
    GRIMER,
    TANGELA,
    MR__MIME,
    EEVEE,
    PORYGON,
    DRATINI,
    DRAGONAIR,
    TOGETIC,
    UMBREON,
    UNOWN,
    SNUBBULL,
    HERACROSS,
    -1,
};

const species_t OftenFleeMons[] = {
    CUBONE,
    ARTICUNO,
    ZAPDOS,
    MOLTRES,
    QUAGSIRE,
    DELIBIRD,
    PHANPY,
    TEDDIURSA,
    -1,
};

const species_t AlwaysFleeMons[] = {
    RAIKOU,
    ENTEI,
    -1,
};

const species_t* FleeMons[] = {
    SometimesFleeMons,
    OftenFleeMons,
    AlwaysFleeMons
};