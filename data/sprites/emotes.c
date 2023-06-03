#include "../../constants.h"

struct Emote {
    uint16_t graphicsPtr;
    uint8_t length;
    uint16_t startingTile;
};

// TODO: Replace with file loading code.
const struct Emote Emotes[] = {
    [EMOTE_SHOCK]        = {mShockEmote,     4, 0xf8},
    [EMOTE_QUESTION]     = {mQuestionEmote,  4, 0xf8},
    [EMOTE_HAPPY]        = {mHappyEmote,     4, 0xf8},
    [EMOTE_SAD]          = {mSadEmote,       4, 0xf8},
    [EMOTE_HEART]        = {mHeartEmote,     4, 0xf8},
    [EMOTE_BOLT]         = {mBoltEmote,      4, 0xf8},
    [EMOTE_SLEEP]        = {mSleepEmote,     4, 0xf8},
    [EMOTE_FISH]         = {mFishEmote,      4, 0xf8},
    [EMOTE_SHADOW]       = {mJumpShadowGFX,  1, 0xfc},
    [EMOTE_ROD]          = {mFishingRodGFX,  2, 0xfc},
    [EMOTE_BOULDER_DUST] = {mBoulderDustGFX, 2, 0xfe},
    [EMOTE_GRASS_RUSTLE] = {mGrassRustleGFX, 1, 0xfe},
};

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(lengthof(Emotes) == NUM_EMOTES, "");
#else
_Static_assert(lengthof(Emotes) == NUM_EMOTES, "");
#endif