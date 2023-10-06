#pragma once

struct SpriteMoveData {
    uint8_t function;
    int8_t facing;
    uint8_t action;
    uint8_t flags1;
    uint8_t flags2;
    uint8_t palette;
};

extern const struct SpriteMoveData SpriteMovementData[];
