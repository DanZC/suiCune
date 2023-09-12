#include "../../constants.h"
#include "emotes.h"
#include "../../gfx/emotes.h"

const struct Emote Emotes[] = {
    [EMOTE_SHOCK]        = {ShockEmote,     4, 0xf8},
    [EMOTE_QUESTION]     = {QuestionEmote,  4, 0xf8},
    [EMOTE_HAPPY]        = {HappyEmote,     4, 0xf8},
    [EMOTE_SAD]          = {SadEmote,       4, 0xf8},
    [EMOTE_HEART]        = {HeartEmote,     4, 0xf8},
    [EMOTE_BOLT]         = {BoltEmote,      4, 0xf8},
    [EMOTE_SLEEP]        = {SleepEmote,     4, 0xf8},
    [EMOTE_FISH]         = {FishEmote,      4, 0xf8},
    [EMOTE_SHADOW]       = {JumpShadowGFX,  1, 0xfc},
    [EMOTE_ROD]          = {FishingRodGFX,  2, 0xfc},
    [EMOTE_BOULDER_DUST] = {BoulderDustGFX, 2, 0xfe},
    [EMOTE_GRASS_RUSTLE] = {GrassRustleGFX, 1, 0xfe},
};

static_assert(lengthof(Emotes) == NUM_EMOTES, "");
