#pragma once

struct GrowthRate {
    uint8_t b: 4;
    uint8_t a: 4;
    uint8_t c;
    uint8_t d;
    uint8_t e;
};

static_assert(sizeof(struct GrowthRate) == 4, "");

extern const struct GrowthRate GrowthRates[];
