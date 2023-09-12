#pragma once

struct Emote {
    const char* graphicsPath;
    uint8_t length;
    uint16_t startingTile;
};

extern const struct Emote Emotes[];