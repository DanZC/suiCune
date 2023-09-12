#include "../../constants.h"
#include "player_sprites.h"

const uint8_t ChrisStateSprites[][2] = {
    {PLAYER_NORMAL,    SPRITE_CHRIS},
    {PLAYER_BIKE,      SPRITE_CHRIS_BIKE},
    {PLAYER_SURF,      SPRITE_SURF},
    {PLAYER_SURF_PIKA, SPRITE_SURFING_PIKACHU},
    {-1,               -1}, // end
};

const uint8_t KrisStateSprites[][2] = {
    {PLAYER_NORMAL,    SPRITE_KRIS},
    {PLAYER_BIKE,      SPRITE_KRIS_BIKE},
    {PLAYER_SURF,      SPRITE_SURF},
    {PLAYER_SURF_PIKA, SPRITE_SURFING_PIKACHU},
    {-1,               -1}, // end
};
