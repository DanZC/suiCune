#pragma once
struct Landmark
{
    int8_t x;
    int8_t y;
    const char* const name;
};
extern const struct Landmark Landmarks[];