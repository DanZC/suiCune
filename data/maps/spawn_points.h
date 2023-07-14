#pragma once

struct Spawn
{
    uint8_t mapGroup;
    uint8_t mapId;
    struct Coords coord;
};
extern const struct Spawn SpawnPoints[];