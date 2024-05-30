#pragma once

struct ContestMon {
    uint8_t pct;
    species_t species;
    uint8_t min;
    uint8_t max;
};

extern const struct ContestMon ContestMons[];
