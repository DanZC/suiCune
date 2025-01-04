#pragma once

enum {
	CHARPOOL_0_TO_9,
	CHARPOOL_A_TO_Z,
	CHARPOOL_A_TO_9,
	CHARPOOL_L,
	CHARPOOL_V,
	CHARPOOL_M,
	CHARPOOL_D,
	CHARPOOL_S,
	CHARPOOL_I,
	CHARPOOL_4,
	CHARPOOL_7,
	CHARPOOL_8,
	CHARPOOL_9,
	CHARPOOL_A_TO_Z_2,
	CHARPOOL_0_TO_9_2,
	CHARPOOL_A_TO_9_BLANK,	
	CHARPOOL_BLANK,
	CHARPOOL_DASH,
};

struct CharPool {
    const char* addr;
    uint32_t size;
};

extern const struct CharPool Zipcode_CharPools[];
