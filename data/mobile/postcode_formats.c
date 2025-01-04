#include <stdint.h>
#include "charmaps.h"
#if defined(_CRYSTAL_AU) // AU build
static const uint8_t Zipcode_CharPools_Format0[] = {         // 0-9   0-9   0-9   0-9
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};
const uint8_t* const Zipcode_CharPool_Formats[] = {
	Zipcode_CharPools_Format0,
};
#elif defined(_CRYSTAL_EU) // EU build
const uint8_t Zipcode_CharPools_Format0[] = {         // -     -     -
    CHARPOOL_DASH,
    CHARPOOL_DASH,
    CHARPOOL_DASH,
};

const uint8_t Zipcode_CharPools_Format9[] = {         // A-Z   A-Z   A-Z   0-9   0-9
    CHARPOOL_A_TO_Z,
    CHARPOOL_A_TO_Z,
    CHARPOOL_A_TO_Z,
    CHARPOOL_BLANK,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};

const uint8_t Zipcode_CharPools_Format5[] = {         // 0-9   0-9   0-9   0-9   0-9   0-9   0-9
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_DASH,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};
const uint8_t Zipcode_CharPools_Format4[] = {         // 0-9   0-9   0-9   0-9   0-9   0-9
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};
const uint8_t Zipcode_CharPools_Format3[] = {         // 0-9   0-9   0-9   0-9   0-9
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};
const uint8_t Zipcode_CharPools_Format6[] = {         // 0-9   0-9   0-9   0-9   A-Z   A-Z
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_A_TO_Z,
    CHARPOOL_A_TO_Z,
};
const uint8_t Zipcode_CharPools_Format2[] = {         // 0-9   0-9   0-9   0-9
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};
const uint8_t Zipcode_CharPools_Format1[] = {         // 0-9   0-9   0-9
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};
const uint8_t Zipcode_CharPools_Format7[] = {         // A-Z   0-9   0-Z   0-Z   0-Z   0-Z   0-Z
    CHARPOOL_A_TO_Z,
    CHARPOOL_0_TO_9,
    CHARPOOL_A_TO_9,
    CHARPOOL_BLANK,
    CHARPOOL_A_TO_9,
    CHARPOOL_A_TO_9,
    CHARPOOL_A_TO_9,
    CHARPOOL_A_TO_9,
};

const uint8_t Zipcode_CharPools_Format8[] = {         // A-Z   0-Z   0-Z   0-Z   0-Z   A-Z_Blank   A-Z+Blank
    CHARPOOL_A_TO_Z,
    CHARPOOL_A_TO_9,
    CHARPOOL_A_TO_9_BLANK,
    CHARPOOL_A_TO_9_BLANK,
    CHARPOOL_BLANK,
    CHARPOOL_A_TO_9,
    CHARPOOL_A_TO_Z,
    CHARPOOL_A_TO_Z,
};

const uint8_t Zipcode_CharPools_Format10[] = {        // L     V     0-9   0-9   0-9   0-9
    CHARPOOL_L,
    CHARPOOL_V,
    CHARPOOL_DASH,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};

const uint8_t Zipcode_CharPools_Format11[] = {        // M     D     0-9   0-9   0-9   0-9
    CHARPOOL_M,
    CHARPOOL_D,
    CHARPOOL_DASH,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};

const uint8_t Zipcode_CharPools_Format12[] = {        // S     I     0-9   0-9   0-9   0-9
    CHARPOOL_S,
    CHARPOOL_I,
    CHARPOOL_DASH,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};
	
const uint8_t Zipcode_CharPools_Format13[] = {        // 4     7     8   9   0-9
    CHARPOOL_4,
    CHARPOOL_7,
    CHARPOOL_8,
    CHARPOOL_9,
    CHARPOOL_0_TO_9,
};

const uint8_t Zipcode_CharPools_Format14[] = {         // 0-9   0-9   0-9         0-9   0-9
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_DASH,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};

const uint8_t Zipcode_CharPools_Format15[] = {         // 0-9   0-9   0-9         0-9   0-9
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
    CHARPOOL_BLANK,
    CHARPOOL_0_TO_9,
    CHARPOOL_0_TO_9,
};

const uint8_t* const Zipcode_CharPool_Formats[] = {
    Zipcode_CharPools_Format0,
    Zipcode_CharPools_Format1,
    Zipcode_CharPools_Format2,
    Zipcode_CharPools_Format3,
    Zipcode_CharPools_Format4,
    Zipcode_CharPools_Format5,
    Zipcode_CharPools_Format6,
    Zipcode_CharPools_Format7,
    Zipcode_CharPools_Format8,
    Zipcode_CharPools_Format9,
    Zipcode_CharPools_Format10,
    Zipcode_CharPools_Format11,
    Zipcode_CharPools_Format12,
    Zipcode_CharPools_Format13,
    Zipcode_CharPools_Format14,
    Zipcode_CharPools_Format15,
};

#else // US build
static const uint8_t Zipcode_CharPools_Format_CA[] = {          // A-Z   0-9   A-Z   0-9   A-Z   0-9
	CHARPOOL_A_TO_Z,
	CHARPOOL_0_TO_9,
	CHARPOOL_A_TO_Z,
	CHARPOOL_BLANK,
	CHARPOOL_0_TO_9,
	CHARPOOL_A_TO_Z,
    CHARPOOL_0_TO_9,
};
static const uint8_t Zipcode_CharPools_Format_US[] = {          // 0-9   0-9   0-9   0-9   0-9
	CHARPOOL_0_TO_9,
	CHARPOOL_0_TO_9,
	CHARPOOL_0_TO_9,
	CHARPOOL_0_TO_9,
	CHARPOOL_0_TO_9,
};
const uint8_t* const Zipcode_CharPool_Formats[] = {
	Zipcode_CharPools_Format_US,
	Zipcode_CharPools_Format_CA
};
#endif