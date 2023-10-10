#pragma once

struct SceneVar {
    uint8_t group;
    uint8_t map;
    uint8_t* const var;
};

extern const struct SceneVar MapScenes[];
