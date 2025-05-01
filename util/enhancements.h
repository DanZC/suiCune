#pragma once

// Optional compiler switch for providing enchancements in Pokemon Crystal.

#ifndef ENHANCEMENT_DRAW_BG_IN_ONE_FRAME
// Draws BG Map in single frame instead of across 3 frames like in the original game.
#define ENHANCEMENT_DRAW_BG_IN_ONE_FRAME 0
#endif

#ifndef ENHANCEMENT_USE_PCG
// Replaces Crystal's random number generator with PCG
#define ENHANCEMENT_USE_PCG 0
#endif
