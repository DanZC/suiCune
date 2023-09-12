#pragma once

struct OverworldSprite {
    const char* path;
    uint8_t length;
    uint8_t type;
    uint8_t pal;
};

extern const struct OverworldSprite OverworldSprites[];