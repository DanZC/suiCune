#pragma once

struct CustomSpeciesPalEntry {
    species_t id;
    uint16_t pals[4];
};

extern const char* PokemonShinyPals[];
extern const struct CustomSpeciesPalEntry PokemonCustomPals[];