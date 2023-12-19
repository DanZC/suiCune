#include "../../constants.h"

const uint8_t WeatherTypeModifiers[] = {
    WEATHER_RAIN, WATER, MORE_EFFECTIVE,
    WEATHER_RAIN, FIRE,  NOT_VERY_EFFECTIVE,
    WEATHER_SUN,  FIRE,  MORE_EFFECTIVE,
    WEATHER_SUN,  WATER, NOT_VERY_EFFECTIVE,
    0xff, // end
};

const uint8_t WeatherMoveModifiers[] = {
    WEATHER_RAIN, EFFECT_SOLARBEAM, NOT_VERY_EFFECTIVE,
    -1, // end
};
