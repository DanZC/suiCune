#pragma once

struct EngineFlag
{
    uint8_t* const ptr;
    uint8_t bit;
};

extern const struct EngineFlag EngineFlags[];
