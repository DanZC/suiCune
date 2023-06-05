#include "../../constants.h"

// referenced by TryEnemyFlee and FastBallMultiplier

const uint8_t SometimesFleeMons[] = {
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
    0xff,
};

const uint8_t OftenFleeMons[] = {
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

const uint8_t AlwaysFleeMons[] = {
    RAIKOU,
    ENTEI,
    -1,
};

const uint8_t* FleeMons[] = {
    SometimesFleeMons,
    OftenFleeMons,
    AlwaysFleeMons
};