#include "../../constants.h"

static const uint8_t OAMData_11[] = {
    dbsprite( -1,  -1, 4, 0, 0x00, 0x0),
    dbsprite( -1,   0, 4, 0, 0x01, 0x0),
};

static const uint8_t OAMData_56[] = {
    dbsprite( -1,  -1, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x01, 0x0),
};

static const uint8_t OAMData_03[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x01, 0x0),
    dbsprite( -1,   0, 0, 0, 0x02, 0x0),
    dbsprite(  0,   0, 0, 0, 0x03, 0x0),
};

static const uint8_t OAMData_02[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x00, X_FLIP),
    dbsprite( -1,   0, 0, 0, 0x00, Y_FLIP),
    dbsprite(  0,   0, 0, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_c3[] = {
    dbsprite( -2,  -2, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x01, 0x0),
    dbsprite(  0,  -2, 4, 4, 0x02, 0x0),
    dbsprite( -2,  -1, 4, 4, 0x03, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x04, 0x0),
    dbsprite(  0,  -1, 4, 4, 0x05, 0x0),
    dbsprite( -2,   0, 4, 4, 0x06, 0x0),
    dbsprite( -1,   0, 4, 4, 0x07, 0x0),
    dbsprite(  0,   0, 4, 4, 0x08, 0x0),
};

static const uint8_t OAMData_01[] = {
    dbsprite( -2,  -2, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x01, 0x0),
    dbsprite(  0,  -2, 4, 4, 0x00, X_FLIP),
    dbsprite( -2,  -1, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x03, 0x0),
    dbsprite(  0,  -1, 4, 4, 0x02, X_FLIP | Y_FLIP),
    dbsprite( -2,   0, 4, 4, 0x00, Y_FLIP),
    dbsprite( -1,   0, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,   0, 4, 4, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_cf[] = {
    dbsprite( -2,  -2, 4, 0, 0x00, 0x0),
    dbsprite( -1,  -2, 4, 0, 0x01, 0x0),
    dbsprite(  0,  -2, 4, 0, 0x02, 0x0),
    dbsprite( -2,  -1, 4, 0, 0x03, 0x0),
    dbsprite( -1,  -1, 4, 0, 0x04, 0x0),
    dbsprite(  0,  -1, 4, 0, 0x05, 0x0),
    dbsprite( -2,   0, 4, 0, 0x05, X_FLIP | Y_FLIP),
    dbsprite( -1,   0, 4, 0, 0x04, X_FLIP | Y_FLIP),
    dbsprite(  0,   0, 4, 0, 0x03, X_FLIP | Y_FLIP),
    dbsprite( -2,   1, 4, 0, 0x02, X_FLIP | Y_FLIP),
    dbsprite( -1,   1, 4, 0, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,   1, 4, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_1c[] = {
    dbsprite( -2,  -2, 0, 0, 0x00, 0x0),
    dbsprite( -1,  -2, 0, 0, 0x01, 0x0),
    dbsprite(  0,  -2, 0, 0, 0x02, 0x0),
    dbsprite(  1,  -2, 0, 0, 0x03, 0x0),
    dbsprite( -2,  -1, 0, 0, 0x04, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x05, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x06, 0x0),
    dbsprite(  1,  -1, 0, 0, 0x07, 0x0),
    dbsprite( -2,   0, 0, 0, 0x08, 0x0),
    dbsprite( -1,   0, 0, 0, 0x09, 0x0),
    dbsprite(  0,   0, 0, 0, 0x0a, 0x0),
    dbsprite(  1,   0, 0, 0, 0x0b, 0x0),
    dbsprite( -2,   1, 0, 0, 0x0c, 0x0),
    dbsprite( -1,   1, 0, 0, 0x0d, 0x0),
    dbsprite(  0,   1, 0, 0, 0x0e, 0x0),
    dbsprite(  1,   1, 0, 0, 0x0f, 0x0),
};

static const uint8_t OAMData_00[] = {
    dbsprite( -2,  -2, 0, 0, 0x00, 0x0),
    dbsprite( -1,  -2, 0, 0, 0x01, 0x0),
    dbsprite( -2,  -1, 0, 0, 0x02, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x03, 0x0),
    dbsprite(  0,  -2, 0, 0, 0x01, X_FLIP),
    dbsprite(  1,  -2, 0, 0, 0x00, X_FLIP),
    dbsprite(  0,  -1, 0, 0, 0x03, X_FLIP),
    dbsprite(  1,  -1, 0, 0, 0x02, X_FLIP),
    dbsprite( -2,   0, 0, 0, 0x02, Y_FLIP),
    dbsprite( -1,   0, 0, 0, 0x03, Y_FLIP),
    dbsprite( -2,   1, 0, 0, 0x00, Y_FLIP),
    dbsprite( -1,   1, 0, 0, 0x01, Y_FLIP),
    dbsprite(  0,   0, 0, 0, 0x03, X_FLIP | Y_FLIP),
    dbsprite(  1,   0, 0, 0, 0x02, X_FLIP | Y_FLIP),
    dbsprite(  0,   1, 0, 0, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,   1, 0, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_09[] = {
    dbsprite( -3,  -3, 4, 4, 0x00, 0x0),
    dbsprite( -2,  -3, 4, 4, 0x01, 0x0),
    dbsprite( -3,  -2, 4, 4, 0x02, 0x0),
    dbsprite( -2,  -2, 4, 4, 0x03, 0x0),
    dbsprite(  0,  -3, 4, 4, 0x01, X_FLIP),
    dbsprite(  1,  -3, 4, 4, 0x00, X_FLIP),
    dbsprite(  0,  -2, 4, 4, 0x03, X_FLIP),
    dbsprite(  1,  -2, 4, 4, 0x02, X_FLIP),
    dbsprite( -3,   0, 4, 4, 0x02, Y_FLIP),
    dbsprite( -2,   0, 4, 4, 0x03, Y_FLIP),
    dbsprite( -3,   1, 4, 4, 0x00, Y_FLIP),
    dbsprite( -2,   1, 4, 4, 0x01, Y_FLIP),
    dbsprite(  0,   0, 4, 4, 0x03, X_FLIP | Y_FLIP),
    dbsprite(  1,   0, 4, 4, 0x02, X_FLIP | Y_FLIP),
    dbsprite(  0,   1, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,   1, 4, 4, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_0c[] = {
    dbsprite( -1,  -1, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x00, X_FLIP),
};

static const uint8_t OAMData_6a[] = {
    dbsprite( -1,   0, 0, 0, 0x00, 0x0),
    dbsprite(  0,   0, 0, 0, 0x00, X_FLIP),
};

static const uint8_t OAMData_04[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x00, X_FLIP),
    dbsprite( -1,   0, 0, 0, 0x01, 0x0),
    dbsprite(  0,   0, 0, 0, 0x01, X_FLIP),
};

static const uint8_t OAMData_5d[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x01, 0x0),
    dbsprite( -1,   0, 0, 0, 0x00, Y_FLIP),
    dbsprite(  0,   0, 0, 0, 0x01, Y_FLIP),
};

static const uint8_t OAMData_13[] = {
    dbsprite( -1,  -1, 0, 2, 0x02, 0x0),
    dbsprite( -1,   0, 0, 2, 0x03, 0x0),
    dbsprite(  0,  -2, 0, 6, 0x02, 0x0),
    dbsprite(  0,  -1, 0, 6, 0x03, 0x0),
};

static const uint8_t OAMData_22[] = {
    dbsprite(-11,   1, 0, 0, 0x01, 0x0),
    dbsprite(-10,   0, 0, 0, 0x02, 0x0),
    dbsprite( -9,   0, 0, 0, 0x03, 0x0),
    dbsprite( -8,   0, 0, 0, 0x00, 0x0),
    dbsprite( -7,   0, 0, 0, 0x03, 0x0),
    dbsprite( -6,   0, 0, 0, 0x00, 0x0),
    dbsprite( -5,   0, 0, 0, 0x03, 0x0),
    dbsprite( -4,   0, 0, 0, 0x00, 0x0),
    dbsprite( -3,   0, 0, 0, 0x03, 0x0),
    dbsprite( -2,   0, 0, 0, 0x00, 0x0),
    dbsprite( -1,   0, 0, 0, 0x01, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x02, 0x0),
    dbsprite(  1,  -1, 0, 0, 0x03, 0x0),
    dbsprite(  2,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  3,  -1, 0, 0, 0x03, 0x0),
    dbsprite(  4,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  5,  -1, 0, 0, 0x03, 0x0),
    dbsprite(  6,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  7,  -1, 0, 0, 0x03, 0x0),
    dbsprite(  8,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  9,  -1, 0, 0, 0x01, 0x0),
    dbsprite( 10,  -2, 0, 0, 0x02, 0x0),
};

static const uint8_t OAMData_2a[] = {
    dbsprite( -1,  -3, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -3, 0, 4, 0x00, X_FLIP),
    dbsprite( -1,  -2, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x01, X_FLIP),
    dbsprite( -1,  -1, 4, 4, 0x02, 0x0),
};

static const uint8_t OAMData_2b[] = {
    dbsprite( -1,  -4, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -4, 0, 4, 0x00, X_FLIP),
    dbsprite( -1,  -3, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -3, 0, 4, 0x01, X_FLIP),
    dbsprite( -1,  -2, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x02, 0x0),
};

static const uint8_t OAMData_2c[] = {
    dbsprite( -1,  -5, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -5, 0, 4, 0x00, X_FLIP),
    dbsprite( -1,  -4, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -4, 0, 4, 0x01, X_FLIP),
    dbsprite( -1,  -3, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x02, 0x0),
};

static const uint8_t OAMData_2d[] = {
    dbsprite( -1,  -6, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -6, 0, 4, 0x00, X_FLIP),
    dbsprite( -1,  -5, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -5, 0, 4, 0x01, X_FLIP),
    dbsprite( -1,  -4, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -3, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x02, 0x0),
};

static const uint8_t OAMData_2e[] = {
    dbsprite( -1,  -7, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -7, 0, 4, 0x00, X_FLIP),
    dbsprite( -1,  -6, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -6, 0, 4, 0x01, X_FLIP),
    dbsprite( -1,  -5, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -4, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -3, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x02, 0x0),
};

static const uint8_t OAMData_2f[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x00, X_FLIP),
    dbsprite( -1,   0, 0, 0, 0x01, 0x0),
    dbsprite(  0,   0, 0, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_30[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x01, 0x0),
    dbsprite( -1,   0, 0, 0, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,   0, 0, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_31[] = {
    dbsprite( -1,  -2, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x01, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x03, 0x0),
    dbsprite( -1,   0, 0, 4, 0x04, 0x0),
    dbsprite(  0,   0, 0, 4, 0x05, 0x0),
};

static const uint8_t OAMData_76[] = {
    dbsprite( -1,  -1, 0, 5, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 1, 0x00, 0x0),
};

static const uint8_t OAMData_32[] = {
    dbsprite( -2,  -1, 4, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 4, 0, 0x00, 0x0),
    dbsprite( -2,  -3, 4, 0, 0x00, 0x0),
    dbsprite(  0,  -3, 4, 0, 0x00, 0x0),
    dbsprite( -3,  -2, 4, 0, 0x00, 0x0),
    dbsprite( -2,  -2, 4, 0, 0x01, 0x0),
    dbsprite( -1,  -2, 4, 0, 0x00, 0x0),
    dbsprite(  0,  -2, 4, 0, 0x01, 0x0),
    dbsprite(  1,  -2, 4, 0, 0x00, 0x0),
    dbsprite( -4,  -1, 4, 0, 0x00, 0x0),
    dbsprite( -3,  -1, 4, 0, 0x01, 0x0),
    dbsprite( -1,  -1, 4, 0, 0x01, 0x0),
    dbsprite(  1,  -1, 4, 0, 0x01, 0x0),
    dbsprite(  2,  -1, 4, 0, 0x00, 0x0),
};

static const uint8_t OAMData_33[] = {
    dbsprite( -2,  -2, 4, 0, 0x00, 0x0),
    dbsprite(  0,  -2, 4, 0, 0x00, 0x0),
    dbsprite( -3,  -1, 4, 0, 0x00, 0x0),
    dbsprite( -2,  -1, 4, 0, 0x01, 0x0),
    dbsprite( -1,  -1, 4, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 4, 0, 0x01, 0x0),
    dbsprite(  1,  -1, 4, 0, 0x00, 0x0),
    dbsprite( -2,  -4, 4, 0, 0x00, 0x0),
    dbsprite(  0,  -4, 4, 0, 0x00, 0x0),
    dbsprite( -3,  -3, 4, 0, 0x00, 0x0),
    dbsprite( -2,  -3, 4, 0, 0x01, 0x0),
    dbsprite( -1,  -3, 4, 0, 0x00, 0x0),
    dbsprite(  0,  -3, 4, 0, 0x01, 0x0),
    dbsprite(  1,  -3, 4, 0, 0x00, 0x0),
    dbsprite( -4,  -2, 4, 0, 0x00, 0x0),
    dbsprite( -3,  -2, 4, 0, 0x01, 0x0),
    dbsprite( -1,  -2, 4, 0, 0x01, 0x0),
    dbsprite(  1,  -2, 4, 0, 0x01, 0x0),
    dbsprite(  2,  -2, 4, 0, 0x00, 0x0),
    dbsprite( -4,  -1, 4, 0, 0x01, 0x0),
    dbsprite(  2,  -1, 4, 0, 0x01, 0x0),
};

static const uint8_t OAMData_36[] = {
    dbsprite( -1,  -7, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -7, 0, 4, 0x01, 0x0),
    dbsprite( -1,  -6, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -6, 0, 4, 0x03, 0x0),
    dbsprite( -1,  -5, 0, 4, 0x04, 0x0),
    dbsprite(  0,  -5, 0, 4, 0x05, 0x0),
    dbsprite( -1,  -4, 0, 4, 0x06, 0x0),
    dbsprite(  0,  -4, 0, 4, 0x07, 0x0),
    dbsprite( -1,  -3, 0, 4, 0x08, 0x0),
    dbsprite(  0,  -3, 0, 4, 0x09, 0x0),
    dbsprite( -1,  -2, 0, 4, 0x0a, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x0b, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x0c, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x0d, 0x0),
};

static const uint8_t OAMData_3a[] = {
    dbsprite( -1,  -7, 0, 4, 0x0c, 0x0),
    dbsprite(  0,  -7, 0, 4, 0x0d, 0x0),
    dbsprite( -1,  -6, 0, 4, 0x08, 0x0),
    dbsprite(  0,  -6, 0, 4, 0x09, 0x0),
    dbsprite( -1,  -5, 0, 4, 0x04, 0x0),
    dbsprite(  0,  -5, 0, 4, 0x05, 0x0),
    dbsprite( -1,  -4, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -4, 0, 4, 0x01, 0x0),
    dbsprite( -1,  -3, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -3, 0, 4, 0x03, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x02, 0x0),
    dbsprite(  1,  -2, 0, 4, 0x03, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x0a, 0x0),
    dbsprite(  1,  -1, 0, 4, 0x0b, 0x0),
};

static const uint8_t OAMData_3e[] = {
    dbsprite( -2,   1, 0, 4, 0x00, Y_FLIP),
    dbsprite( -1,   1, 0, 4, 0x02, Y_FLIP),
    dbsprite(  0,   1, 0, 4, 0x02, X_FLIP | Y_FLIP),
    dbsprite(  1,   1, 0, 4, 0x00, X_FLIP | Y_FLIP),
    dbsprite( -3,  -1, 0, 4, 0x09, X_FLIP),
    dbsprite( -2,  -1, 0, 4, 0x08, X_FLIP),
    dbsprite( -1,  -1, 0, 4, 0x06, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x07, 0x0),
    dbsprite(  1,  -1, 0, 4, 0x08, 0x0),
    dbsprite(  2,  -1, 0, 4, 0x09, 0x0),
    dbsprite( -3,   0, 0, 4, 0x01, X_FLIP),
    dbsprite( -2,   0, 0, 4, 0x00, X_FLIP),
    dbsprite( -1,   0, 0, 4, 0x0c, 0x0),
    dbsprite(  0,   0, 0, 4, 0x0d, 0x0),
    dbsprite(  1,   0, 0, 4, 0x00, 0x0),
    dbsprite(  2,   0, 0, 4, 0x01, 0x0),
    dbsprite( -2,  -3, 0, 4, 0x00, 0x0),
    dbsprite( -1,  -3, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -3, 0, 4, 0x02, X_FLIP),
    dbsprite(  1,  -3, 0, 4, 0x00, X_FLIP),
    dbsprite( -3,  -2, 0, 4, 0x03, X_FLIP),
    dbsprite( -2,  -2, 0, 4, 0x02, X_FLIP),
    dbsprite( -1,  -2, 0, 4, 0x04, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x05, 0x0),
    dbsprite(  1,  -2, 0, 4, 0x02, 0x0),
    dbsprite(  2,  -2, 0, 4, 0x03, 0x0),
};

static const uint8_t OAMData_41[] = {
    dbsprite( -2,  -3, 0, 4, 0x00, 0x0),
    dbsprite( -1,  -3, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -3, 0, 4, 0x02, X_FLIP),
    dbsprite(  1,  -3, 0, 4, 0x00, X_FLIP),
    dbsprite( -3,  -2, 4, 4, 0x00, 0x0),
    dbsprite( -2,  -2, 4, 4, 0x01, 0x0),
    dbsprite( -1,  -2, 0, 4, 0x05, X_FLIP),
    dbsprite(  0,  -2, 0, 4, 0x04, X_FLIP),
    dbsprite(  0,  -2, 4, 4, 0x01, X_FLIP),
    dbsprite(  1,  -2, 4, 4, 0x00, X_FLIP),
    dbsprite( -3,  -1, 4, 4, 0x02, 0x0),
    dbsprite( -2,  -1, 4, 4, 0x03, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x07, X_FLIP),
    dbsprite(  0,  -1, 0, 4, 0x06, X_FLIP),
    dbsprite(  0,  -1, 4, 4, 0x03, X_FLIP),
    dbsprite(  1,  -1, 4, 4, 0x02, X_FLIP),
    dbsprite( -3,   0, 4, 4, 0x04, 0x0),
    dbsprite( -2,   0, 4, 4, 0x05, 0x0),
    dbsprite( -1,   0, 0, 4, 0x0d, X_FLIP),
    dbsprite(  0,   0, 0, 4, 0x0c, X_FLIP),
    dbsprite(  0,   0, 4, 4, 0x05, X_FLIP),
    dbsprite(  1,   0, 4, 4, 0x04, X_FLIP),
    dbsprite( -2,   1, 0, 4, 0x00, Y_FLIP),
    dbsprite( -1,   1, 0, 4, 0x02, Y_FLIP),
    dbsprite(  0,   1, 0, 4, 0x02, X_FLIP | Y_FLIP),
    dbsprite(  1,   1, 0, 4, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_42[] = {
    dbsprite( -1,  -3, 4, 0, 0x02, 0x0),
    dbsprite( -1,   2, 4, 0, 0x02, X_FLIP | Y_FLIP),
    dbsprite( -3,  -1, 0, 4, 0x01, 0x0),
    dbsprite(  2,  -1, 0, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -1,  -4, 4, 0, 0x02, 0x0),
    dbsprite( -1,   3, 4, 0, 0x02, X_FLIP | Y_FLIP),
    dbsprite( -4,  -1, 0, 4, 0x01, 0x0),
    dbsprite(  3,  -1, 0, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_44[] = {
    dbsprite( -3,  -3, 5, 5, 0x00, X_FLIP),
    dbsprite(  1,  -3, 3, 5, 0x00, 0x0),
    dbsprite( -3,   1, 5, 3, 0x00, X_FLIP | Y_FLIP),
    dbsprite(  1,   1, 3, 3, 0x00, Y_FLIP),
    dbsprite( -4,  -4, 5, 5, 0x00, X_FLIP),
    dbsprite(  2,  -4, 3, 5, 0x00, 0x0),
    dbsprite( -4,   2, 5, 3, 0x00, X_FLIP | Y_FLIP),
    dbsprite(  2,   2, 3, 3, 0x00, Y_FLIP),
};

static const uint8_t OAMData_46[] = {
    dbsprite( -1,  -3, 4, 4, 0x02, 0x0),
    dbsprite( -1,   1, 4, 4, 0x02, X_FLIP | Y_FLIP),
    dbsprite( -3,  -1, 4, 4, 0x01, 0x0),
    dbsprite(  1,  -1, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_47[] = {
    dbsprite( -2,  -2, 0, 0, 0x00, X_FLIP),
    dbsprite(  1,  -2, 0, 0, 0x00, 0x0),
    dbsprite( -2,   1, 0, 0, 0x00, X_FLIP | Y_FLIP),
    dbsprite(  1,   1, 0, 0, 0x00, Y_FLIP),
};

static const uint8_t OAMData_48[] = {
    dbsprite( -1,  -3, 4, 0, 0x00, 0x0),
    dbsprite( -1,  -2, 2, 0, 0x00, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite( -1,   0, 0, 0, 0x00, 0x0),
    dbsprite( -1,   1, 2, 0, 0x00, 0x0),
    dbsprite( -1,   2, 4, 0, 0x00, 0x0),
};

static const uint8_t OAMData_49[] = {
    dbsprite( -2,  -1, 0, 4, 0x00, X_FLIP),
    dbsprite( -1,  -1, 0, 2, 0x00, X_FLIP),
    dbsprite(  0,  -1, 0, 2, 0x00, 0x0),
    dbsprite(  1,  -1, 0, 4, 0x00, 0x0),
};

static const uint8_t OAMData_4a[] = {
    dbsprite( -1,  -1, 0, 4, 0x00, X_FLIP | Y_FLIP),
    dbsprite(  0,  -1, 0, 4, 0x00, Y_FLIP),
};

static const uint8_t OAMData_0f[] = {
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -2,  -1, 4, 4, 0x01, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x01, X_FLIP),
    dbsprite( -2,   0, 4, 4, 0x01, Y_FLIP),
    dbsprite( -1,   0, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_4c[] = {
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -2,   0, 6, 2, 0x00, 0x0),
    dbsprite( -3,   0, 6, 2, 0x01, 0x0),
    dbsprite( -2,   0, 6, 2, 0x01, X_FLIP),
    dbsprite( -3,   1, 6, 2, 0x01, Y_FLIP),
    dbsprite( -2,   1, 6, 2, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_4d[] = {
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -2,   0, 6, 2, 0x00, 0x0),
    dbsprite( -2,   1, 0, 0, 0x00, 0x0),
    dbsprite( -3,   1, 0, 0, 0x01, 0x0),
    dbsprite( -2,   1, 0, 0, 0x01, X_FLIP),
    dbsprite( -3,   2, 0, 0, 0x01, Y_FLIP),
    dbsprite( -2,   2, 0, 0, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_4f[] = {
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -2,   0, 6, 2, 0x00, 0x0),
    dbsprite( -2,   1, 0, 0, 0x00, 0x0),
    dbsprite( -3,   1, 2, 6, 0x00, 0x0),
    dbsprite( -4,   1, 2, 6, 0x01, 0x0),
    dbsprite( -3,   1, 2, 6, 0x01, X_FLIP),
    dbsprite( -4,   2, 2, 6, 0x01, Y_FLIP),
    dbsprite( -3,   2, 2, 6, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_50[] = {
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -2,   0, 6, 2, 0x00, 0x0),
    dbsprite( -2,   1, 0, 0, 0x00, 0x0),
    dbsprite( -3,   1, 2, 6, 0x00, 0x0),
    dbsprite( -4,   2, 4, 4, 0x00, 0x0),
    dbsprite( -5,   2, 4, 4, 0x01, 0x0),
    dbsprite( -4,   2, 4, 4, 0x01, X_FLIP),
    dbsprite( -5,   3, 4, 4, 0x01, Y_FLIP),
    dbsprite( -4,   3, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_51[] = {
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -2,   0, 6, 2, 0x00, 0x0),
    dbsprite( -2,   1, 0, 0, 0x00, 0x0),
    dbsprite( -3,   1, 2, 6, 0x00, 0x0),
    dbsprite( -4,   2, 4, 4, 0x00, 0x0),
    dbsprite( -5,   3, 6, 2, 0x00, 0x0),
    dbsprite( -6,   3, 6, 2, 0x01, 0x0),
    dbsprite( -5,   3, 6, 2, 0x01, X_FLIP),
    dbsprite( -6,   4, 6, 2, 0x01, Y_FLIP),
    dbsprite( -5,   4, 6, 2, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_59[] = {
    dbsprite( -2,  -1, 0, 4, 0x00, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x01, X_FLIP),
    dbsprite(  1,  -1, 0, 4, 0x00, X_FLIP),
};

static const uint8_t OAMData_5a[] = {
    dbsprite( -2,  -1, 0, 4, 0x02, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x01, X_FLIP),
    dbsprite(  1,  -1, 0, 4, 0x02, X_FLIP),
};

static const uint8_t OAMData_60[] = {
    dbsprite( -1,  -1, 4, 0, 0x00, 0x0),
};

static const uint8_t OAMData_69[] = {
    dbsprite( -1,   0, 4, 0, 0x00, 0x0),
};

static const uint8_t OAMData_61[] = {
    dbsprite( -4,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -3,  -1, 4, 4, 0x01, 0x0),
    dbsprite( -2,  -1, 4, 4, 0x02, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x03, 0x0),
    dbsprite(  0,  -1, 4, 4, 0x04, 0x0),
    dbsprite(  1,  -1, 4, 4, 0x05, 0x0),
    dbsprite(  2,  -1, 4, 4, 0x06, 0x0),
    dbsprite(  1,  -2, 4, 4, 0x07, 0x0),
    dbsprite(  2,  -2, 4, 4, 0x08, 0x0),
};

static const uint8_t OAMData_65[] = {
    dbsprite( -4,  -2, 4, 4, 0x08, X_FLIP),
    dbsprite( -3,  -2, 4, 4, 0x07, X_FLIP),
    dbsprite( -4,  -1, 4, 4, 0x06, X_FLIP),
    dbsprite( -3,  -1, 4, 4, 0x05, X_FLIP),
    dbsprite( -2,  -1, 4, 4, 0x04, X_FLIP),
    dbsprite( -1,  -1, 4, 4, 0x03, X_FLIP),
    dbsprite(  0,  -1, 4, 4, 0x02, X_FLIP),
    dbsprite(  1,  -1, 4, 4, 0x01, X_FLIP),
    dbsprite(  2,  -1, 4, 4, 0x00, X_FLIP),
};

static const uint8_t OAMData_d4[] = {
    dbsprite( -4,   0, 4, 0, 0x00, OBP_NUM),
    dbsprite( -3,   0, 4, 0, 0x01, OBP_NUM),
    dbsprite( -2,   0, 4, 0, 0x02, OBP_NUM),
    dbsprite( -1,   0, 4, 0, 0x03, OBP_NUM),
    dbsprite(  0,   0, 4, 0, 0x04, OBP_NUM),
    dbsprite(  1,   0, 4, 0, 0x05, OBP_NUM),
    dbsprite(  2,   0, 4, 0, 0x06, OBP_NUM),
};

static const uint8_t OAMData_d6[] = {
    dbsprite( -4,  -1, 4, 0, 0x00, OBP_NUM),
    dbsprite( -4,   0, 4, 0, 0x01, OBP_NUM),
    dbsprite( -3,  -1, 4, 0, 0x02, OBP_NUM),
    dbsprite( -3,   0, 4, 0, 0x03, OBP_NUM),
    dbsprite( -2,  -1, 4, 0, 0x04, OBP_NUM),
    dbsprite( -2,   0, 4, 0, 0x05, OBP_NUM),
    dbsprite( -1,  -1, 4, 0, 0x06, OBP_NUM),
    dbsprite( -1,   0, 4, 0, 0x07, OBP_NUM),
    dbsprite(  0,  -1, 4, 0, 0x08, OBP_NUM),
    dbsprite(  0,   0, 4, 0, 0x09, OBP_NUM),
    dbsprite(  1,  -1, 4, 0, 0x0a, OBP_NUM),
    dbsprite(  1,   0, 4, 0, 0x0b, OBP_NUM),
    dbsprite(  2,  -1, 4, 0, 0x0c, OBP_NUM),
    dbsprite(  2,   0, 4, 0, 0x0d, OBP_NUM),
};

static const uint8_t OAMData_d5[] = {
    dbsprite( -3,   0, 0, 0, 0x00, 0x1 | OBP_NUM),
    dbsprite( -2,   0, 0, 0, 0x01, 0x1 | OBP_NUM),
    dbsprite( -1,   0, 0, 0, 0x02, 0x1 | OBP_NUM),
    dbsprite(  0,   0, 0, 0, 0x03, 0x1 | OBP_NUM),
    dbsprite(  1,   0, 0, 0, 0x04, 0x1 | OBP_NUM),
    dbsprite(  2,   0, 0, 0, 0x05, 0x1 | OBP_NUM),
};

static const uint8_t OAMData_d7[] = {
    dbsprite( -3,   0, 0, 0, 0x00, 0x1 | OBP_NUM),
    dbsprite( -3,   1, 0, 0, 0x01, 0x1 | OBP_NUM),
    dbsprite( -2,   0, 0, 0, 0x02, 0x1 | OBP_NUM),
    dbsprite( -2,   1, 0, 0, 0x03, 0x1 | OBP_NUM),
    dbsprite( -1,   0, 0, 0, 0x04, 0x1 | OBP_NUM),
    dbsprite( -1,   1, 0, 0, 0x05, 0x1 | OBP_NUM),
    dbsprite(  0,   0, 0, 0, 0x06, 0x1 | OBP_NUM),
    dbsprite(  0,   1, 0, 0, 0x07, 0x1 | OBP_NUM),
    dbsprite(  1,   0, 0, 0, 0x08, 0x1 | OBP_NUM),
    dbsprite(  1,   1, 0, 0, 0x09, 0x1 | OBP_NUM),
    dbsprite(  2,   0, 0, 0, 0x0a, 0x1 | OBP_NUM),
    dbsprite(  2,   1, 0, 0, 0x0b, 0x1 | OBP_NUM),
};

static const uint8_t OAMData_6e[] = {
    dbsprite(  0,  -2, 4, 4, 0x00, 0x0),
    dbsprite( -2,  -1, 4, 4, 0x01, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x02, 0x0),
    dbsprite(  0,  -1, 4, 4, 0x03, 0x0),
    dbsprite( -2,   0, 4, 4, 0x04, 0x0),
};

static const uint8_t OAMData_6f[] = {
    dbsprite( -2,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x01, 0x0),
    dbsprite(  0,  -1, 4, 4, 0x02, 0x0),
};

static const uint8_t OAMData_77[] = {
    dbsprite(  1,  -4, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_78[] = {
    dbsprite(  1,  -4, 4, 4, 0x00, 0x0),
    dbsprite(  0,  -4, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,  -3, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_79[] = {
    dbsprite(  1,  -4, 4, 4, 0x01, 0x0),
    dbsprite(  0,  -4, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -4, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,  -3, 4, 4, 0x00, 0x0),
    dbsprite(  0,  -3, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,  -2, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_7a[] = {
    dbsprite( -2,  -4, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -1,  -4, 4, 4, 0x00, 0x0),
    dbsprite(  0,  -4, 4, 4, 0x01, 0x0),
    dbsprite( -1,  -3, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,  -3, 4, 4, 0x00, 0x0),
    dbsprite(  1,  -3, 4, 4, 0x01, 0x0),
    dbsprite(  0,  -2, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,  -2, 4, 4, 0x00, 0x0),
    dbsprite(  1,  -1, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_7b[] = {
    dbsprite( -3,  -4, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -2,  -4, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -4, 4, 4, 0x01, 0x0),
    dbsprite( -2,  -3, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -1,  -3, 4, 4, 0x00, 0x0),
    dbsprite(  0,  -3, 4, 4, 0x01, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,  -2, 4, 4, 0x00, 0x0),
    dbsprite(  1,  -2, 4, 4, 0x01, 0x0),
    dbsprite(  0,  -1, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,  -1, 4, 4, 0x00, 0x0),
    dbsprite(  1,   0, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_7c[] = {
    dbsprite( -3,  -4, 4, 4, 0x00, 0x0),
    dbsprite( -2,  -4, 4, 4, 0x01, 0x0),
    dbsprite( -3,  -3, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -2,  -3, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -3, 4, 4, 0x01, 0x0),
    dbsprite( -2,  -2, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -1,  -2, 4, 4, 0x00, 0x0),
    dbsprite(  0,  -2, 4, 4, 0x01, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,  -1, 4, 4, 0x00, 0x0),
    dbsprite(  1,  -1, 4, 4, 0x01, 0x0),
    dbsprite(  0,   0, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,   0, 4, 4, 0x00, 0x0),
    dbsprite(  1,   1, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_7d[] = {
    dbsprite( -3,  -4, 4, 4, 0x01, 0x0),
    dbsprite( -3,  -3, 4, 4, 0x00, 0x0),
    dbsprite( -2,  -3, 4, 4, 0x01, 0x0),
    dbsprite( -3,  -2, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -2,  -2, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x01, 0x0),
    dbsprite( -2,  -1, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite(  0,  -1, 4, 4, 0x01, 0x0),
    dbsprite( -1,   0, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,   0, 4, 4, 0x00, 0x0),
    dbsprite(  1,   0, 4, 4, 0x01, 0x0),
    dbsprite(  0,   1, 4, 4, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,   1, 4, 4, 0x00, 0x0),
    dbsprite(  1,   2, 4, 4, 0x01, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_70[] = {
    dbsprite( -1,  -2, 0, 0, 0x00, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x01, 0x0),
    dbsprite(  0,  -2, 0, 0, 0x00, X_FLIP),
    dbsprite(  0,  -1, 0, 0, 0x01, X_FLIP),
    dbsprite( -1,   0, 0, 0, 0x01, Y_FLIP),
    dbsprite( -1,   1, 0, 0, 0x00, Y_FLIP),
    dbsprite(  0,   0, 0, 0, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,   1, 0, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_81[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x01, 0x0),
    dbsprite( -1,   0, 0, 0, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  0,   0, 0, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_87[] = {
    dbsprite( -1,  -2, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x01, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x03, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x01, 0x0),
    dbsprite( -1,   0, 0, 4, 0x02, 0x0),
    dbsprite(  0,   0, 0, 4, 0x03, 0x0),
    dbsprite( -1,  -3, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -3, 0, 4, 0x01, 0x0),
    dbsprite( -1,  -2, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x03, 0x0),
    dbsprite( -1,   0, 0, 4, 0x00, 0x0),
    dbsprite(  0,   0, 0, 4, 0x01, 0x0),
    dbsprite( -1,   1, 0, 4, 0x02, 0x0),
    dbsprite(  0,   1, 0, 4, 0x03, 0x0),
};

static const uint8_t OAMData_88[] = {
    dbsprite( -1,  -2, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -2, 0, 0, 0x01, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x02, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x03, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x01, 0x0),
    dbsprite( -1,   0, 0, 0, 0x02, 0x0),
    dbsprite(  0,   0, 0, 0, 0x03, 0x0),
    dbsprite( -1,   0, 0, 0, 0x00, 0x0),
    dbsprite(  0,   0, 0, 0, 0x01, 0x0),
    dbsprite( -1,   1, 0, 0, 0x02, 0x0),
    dbsprite(  0,   1, 0, 0, 0x03, 0x0),
};

static const uint8_t OAMData_8a[] = {
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite(  0,  -1, 4, 0, 0x00, 0x0),
    dbsprite(  1,  -2, 4, 4, 0x00, 0x0),
    dbsprite(  2,  -2, 4, 0, 0x00, 0x0),
    dbsprite(  3,  -3, 4, 4, 0x00, 0x0),
    dbsprite(  4,  -3, 4, 0, 0x00, 0x0),
    dbsprite(  5,  -4, 4, 0, 0x00, 0x0),
    dbsprite(  6,  -5, 4, 4, 0x00, 0x0),
};

static const uint8_t OAMData_8e[] = {
    dbsprite( -1,  -3, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x01, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x02, 0x0),
    dbsprite( -1,   0, 4, 4, 0x01, Y_FLIP),
    dbsprite( -1,   1, 4, 4, 0x00, Y_FLIP),
};

static const uint8_t OAMData_8f[] = {
    dbsprite( -2,  -1, 0, 4, 0x00, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x02, 0x0),
    dbsprite(  1,  -1, 0, 4, 0x03, 0x0),
};

static const uint8_t OAMData_93[] = {
    dbsprite( -2,  -1, 4, 0, 0x00, 0x0),
    dbsprite( -1,  -1, 4, 0, 0x01, 0x0),
    dbsprite(  0,  -1, 4, 0, 0x02, 0x0),
    dbsprite( -2,   0, 4, 0, 0x03, 0x0),
    dbsprite( -1,   0, 4, 0, 0x04, 0x0),
    dbsprite(  0,   0, 4, 0, 0x05, 0x0),
};

static const uint8_t OAMData_99[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x05, 0x0),
    dbsprite( -1,   0, 0, 0, 0x01, 0x0),
    dbsprite(  0,   0, 0, 0, 0x05, 0x0),
};

static const uint8_t OAMData_9b[] = {
    dbsprite(  1,  -4, 0, 4, 0x00, 0x0),
    dbsprite(  2,  -4, 0, 4, 0x01, 0x0),
    dbsprite( -1,  -3, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -3, 0, 4, 0x03, 0x0),
    dbsprite(  1,  -3, 0, 4, 0x04, 0x0),
    dbsprite(  2,  -3, 0, 4, 0x05, 0x0),
    dbsprite(  3,  -3, 0, 4, 0x06, 0x0),
    dbsprite( -2,  -2, 0, 4, 0x07, 0x0),
    dbsprite( -1,  -2, 0, 4, 0x08, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x09, 0x0),
    dbsprite(  1,  -2, 0, 4, 0x0a, 0x0),
    dbsprite(  2,  -2, 0, 4, 0x0b, 0x0),
    dbsprite(  3,  -2, 0, 4, 0x0c, 0x0),
    dbsprite(  4,  -2, 0, 4, 0x0d, 0x0),
    dbsprite( -3,  -1, 0, 4, 0x0e, 0x0),
    dbsprite( -2,  -1, 0, 4, 0x0f, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x10, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x11, 0x0),
    dbsprite(  1,  -1, 0, 4, 0x12, 0x0),
    dbsprite(  2,  -1, 0, 4, 0x13, 0x0),
    dbsprite( -5,   0, 0, 4, 0x14, 0x0),
    dbsprite( -4,   0, 0, 4, 0x15, 0x0),
    dbsprite( -3,   0, 0, 4, 0x16, 0x0),
    dbsprite( -2,   0, 0, 4, 0x17, 0x0),
    dbsprite( -1,   0, 0, 4, 0x18, 0x0),
    dbsprite(  0,   0, 0, 4, 0x19, 0x0),
    dbsprite(  1,   0, 0, 4, 0x1a, 0x0),
    dbsprite(  2,   0, 0, 4, 0x1b, 0x0),
    dbsprite(  3,   0, 0, 4, 0x1c, 0x0),
    dbsprite( -5,   1, 0, 4, 0x1d, 0x0),
    dbsprite( -4,   1, 0, 4, 0x1e, 0x0),
    dbsprite( -2,   1, 0, 4, 0x1f, 0x0),
    dbsprite( -1,   1, 0, 4, 0x20, 0x0),
    dbsprite(  0,   1, 0, 4, 0x21, 0x0),
    dbsprite(  1,   1, 0, 4, 0x22, 0x0),
    dbsprite(  0,   2, 0, 4, 0x23, 0x0),
};

static const uint8_t OAMData_9c[] = {
    dbsprite( -1,   0, 0, 4, 0x02, 0x0),
    dbsprite(  0,   0, 0, 4, 0x03, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x01, X_FLIP),
    dbsprite( -1,  -2, 0, 4, 0x00, 0x0),
    dbsprite(  0,  -2, 0, 4, 0x00, X_FLIP),
};

static const uint8_t OAMData_9f[] = {
    dbsprite( -2,  -1, 0, 0, 0x00, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x01, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x02, 0x0),
    dbsprite(  1,  -1, 0, 0, 0x03, 0x0),
    dbsprite( -2,   0, 0, 0, 0x04, 0x0),
    dbsprite( -1,   0, 0, 0, 0x05, 0x0),
    dbsprite(  0,   0, 0, 0, 0x06, 0x0),
    dbsprite(  1,   0, 0, 0, 0x07, 0x0),
};

static const uint8_t OAMData_a0[] = {
    dbsprite( -1,  -2, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x00, 0x0),
    dbsprite( -1,   0, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -3, 4, 4, 0x00, 0x0),
    dbsprite( -1,   1, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -4, 4, 4, 0x00, 0x0),
    dbsprite( -1,   2, 4, 4, 0x00, 0x0),
};

static const uint8_t OAMData_a4[] = {
    dbsprite( -2,  -2, 4, 4, 0x00, 0x0),
    dbsprite( -1,  -2, 4, 4, 0x01, 0x0),
    dbsprite(  0,  -2, 4, 4, 0x02, 0x0),
    dbsprite( -2,  -1, 4, 4, 0x03, 0x0),
    dbsprite( -1,  -1, 4, 4, 0x04, 0x0),
    dbsprite(  0,  -1, 4, 4, 0x05, 0x0),
    dbsprite( -2,   0, 4, 4, 0x00, Y_FLIP),
    dbsprite( -1,   0, 4, 4, 0x01, Y_FLIP),
    dbsprite(  0,   0, 4, 4, 0x02, Y_FLIP),
};

static const uint8_t OAMData_ac[] = {
    dbsprite( -2,  -1, 0, 4, 0x00, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x01, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x01, X_FLIP),
    dbsprite(  1,  -1, 0, 4, 0x00, X_FLIP),
};

static const uint8_t OAMData_bc[] = {
    dbsprite( -3,  -1, 0, 4, 0x00, 0x0),
    dbsprite( -2,  -1, 0, 4, 0x01, 0x0),
    dbsprite( -1,  -1, 0, 4, 0x02, 0x0),
    dbsprite(  0,  -1, 0, 4, 0x02, X_FLIP),
    dbsprite(  1,  -1, 0, 4, 0x01, X_FLIP),
    dbsprite(  2,  -1, 0, 4, 0x00, X_FLIP),
};

static const uint8_t OAMData_c1[] = {
    dbsprite( -2,  -2, 0, 0, 0x00, 0x0),
    dbsprite( -1,  -2, 0, 0, 0x01, 0x0),
    dbsprite(  0,  -2, 0, 0, 0x02, 0x0),
    dbsprite(  1,  -2, 0, 0, 0x00, X_FLIP),
    dbsprite( -2,  -1, 0, 0, 0x03, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x04, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x04, X_FLIP),
    dbsprite(  1,  -1, 0, 0, 0x05, 0x0),
    dbsprite( -2,   0, 0, 0, 0x05, X_FLIP | Y_FLIP),
    dbsprite( -1,   0, 0, 0, 0x04, Y_FLIP),
    dbsprite(  0,   0, 0, 0, 0x04, X_FLIP | Y_FLIP),
    dbsprite(  1,   0, 0, 0, 0x03, X_FLIP | Y_FLIP),
    dbsprite( -2,   1, 0, 0, 0x00, Y_FLIP),
    dbsprite( -1,   1, 0, 0, 0x02, X_FLIP | Y_FLIP),
    dbsprite(  0,   1, 0, 0, 0x01, X_FLIP | Y_FLIP),
    dbsprite(  1,   1, 0, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_c2[] = {
    dbsprite( -2,  -1, 0, 0, 0x00, 0x0),
    dbsprite( -1,  -1, 0, 0, 0x01, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x00, X_FLIP | Y_FLIP),
    dbsprite( -1,   0, 0, 0, 0x00, 0x0),
    dbsprite(  0,   0, 0, 0, 0x01, 0x0),
    dbsprite(  1,   0, 0, 0, 0x00, X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_c8[] = {
    dbsprite(  1,  -1, 4, 0, 0x00, 0x0),
    dbsprite(  2,  -1, 4, 0, 0x01, 0x0),
    dbsprite( -1,   0, 4, 0, 0x02, 0x0),
    dbsprite(  0,   0, 4, 0, 0x03, 0x0),
    dbsprite(  1,   0, 4, 0, 0x04, 0x0),
    dbsprite(  2,   0, 4, 0, 0x05, 0x0),
};

static const uint8_t OAMData_ca[] = {
    dbsprite( -1,  -1, 0, 0, 0x00, 0x0),
    dbsprite(  0,  -1, 0, 0, 0x01, X_FLIP | Y_FLIP),
    dbsprite( -1,   0, 0, 0, 0x01, 0x0),
    dbsprite(  0,   0, 0, 0, 0x01, X_FLIP),
};

static const uint8_t OAMData_cc[] = {
    dbsprite(-13,  -2, 4, 0, 0x00, 0x0),
    dbsprite(-11,  -4, 4, 0, 0x00, 0x0),
    dbsprite( -9,  -1, 4, 0, 0x00, 0x0),
    dbsprite( -7,  -5, 4, 0, 0x00, 0x0),
    dbsprite( -5,  -3, 4, 0, 0x00, 0x0),
    dbsprite( -3,  -5, 4, 0, 0x00, 0x0),
    dbsprite( -1,  -3, 4, 0, 0x00, 0x0),
    dbsprite(  0,  -3, 4, 0, 0x00, 0x0),
    dbsprite(  2,  -5, 4, 0, 0x00, 0x0),
    dbsprite(  4,   0, 4, 0, 0x00, 0x0),
    dbsprite(  6,  -2, 4, 0, 0x00, 0x0),
    dbsprite(  8,  -4, 4, 0, 0x00, 0x0),
    dbsprite( 10,  -2, 4, 0, 0x00, 0x0),
};

// battleanimoam: MACRO
// ; vtile offset, data length, data pointer
// 	db \1, \2
// 	dw \3
// ENDM
#define battleanimoam(_vo, _dl, _dp) {_vo, _dl, _dp}

const struct BattleOAMData BattleAnimOAMData[] = {
// entries correspond to BATTLEANIMOAMSET_* constants
// table_width 4, BattleAnimOAMData
    [BATTLEANIMOAMSET_00] = battleanimoam(0x00, 16, OAMData_00 ),
    [BATTLEANIMOAMSET_01] = battleanimoam(0x04,  9, OAMData_01 ),
    [BATTLEANIMOAMSET_02] = battleanimoam(0x08,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_03] = battleanimoam(0x09,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_04] = battleanimoam(0x0d,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_05] = battleanimoam(0x0f,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_06] = battleanimoam(0x13,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_07] = battleanimoam(0x04, 16, OAMData_00 ),
    [BATTLEANIMOAMSET_08] = battleanimoam(0x08, 16, OAMData_00 ),
    [BATTLEANIMOAMSET_09] = battleanimoam(0x08, 16, OAMData_09 ),
    [BATTLEANIMOAMSET_0A] = battleanimoam(0x00,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_0B] = battleanimoam(0x02,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_0C] = battleanimoam(0x06,  2, OAMData_0c ),
    [BATTLEANIMOAMSET_0D] = battleanimoam(0x07,  2, OAMData_0c ),
    [BATTLEANIMOAMSET_0E] = battleanimoam(0x02,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_0F] = battleanimoam(0x04,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_10] = battleanimoam(0x05,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_11] = battleanimoam(0x00,  2, OAMData_11 ),
    [BATTLEANIMOAMSET_12] = battleanimoam(0x02,  2, OAMData_11 ),
    [BATTLEANIMOAMSET_13] = battleanimoam(0x00,  4, OAMData_13 ),
    [BATTLEANIMOAMSET_14] = battleanimoam(0x00,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_15] = battleanimoam(0x01,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_16] = battleanimoam(0x02,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_17] = battleanimoam(0x03,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_18] = battleanimoam(0x00,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_19] = battleanimoam(0x01, 16, OAMData_00 ),
    [BATTLEANIMOAMSET_1A] = battleanimoam(0x05, 16, OAMData_00 ),
    [BATTLEANIMOAMSET_1B] = battleanimoam(0x00,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_1C] = battleanimoam(0x05, 12, OAMData_1c ),
    [BATTLEANIMOAMSET_1D] = battleanimoam(0x02,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_1E] = battleanimoam(0x06,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_1F] = battleanimoam(0x07,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_20] = battleanimoam(0x08,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_21] = battleanimoam(0x04,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_22] = battleanimoam(0x09, 22, OAMData_22 ),
    [BATTLEANIMOAMSET_23] = battleanimoam(0x04,  2, OAMData_11 ),
    [BATTLEANIMOAMSET_24] = battleanimoam(0x06,  2, OAMData_11 ),
    [BATTLEANIMOAMSET_25] = battleanimoam(0x0c,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_26] = battleanimoam(0x0a,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_27] = battleanimoam(0x0b,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_28] = battleanimoam(0x08,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_29] = battleanimoam(0x06,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_2A] = battleanimoam(0x00,  5, OAMData_2a ),
    [BATTLEANIMOAMSET_2B] = battleanimoam(0x03,  6, OAMData_2b ),
    [BATTLEANIMOAMSET_2C] = battleanimoam(0x00,  7, OAMData_2c ),
    [BATTLEANIMOAMSET_2D] = battleanimoam(0x03,  8, OAMData_2d ),
    [BATTLEANIMOAMSET_2E] = battleanimoam(0x00,  9, OAMData_2e ),
    [BATTLEANIMOAMSET_2F] = battleanimoam(0x00,  4, OAMData_2f ),
    [BATTLEANIMOAMSET_30] = battleanimoam(0x02,  4, OAMData_30 ),
    [BATTLEANIMOAMSET_31] = battleanimoam(0x04,  6, OAMData_31 ),
    [BATTLEANIMOAMSET_32] = battleanimoam(0x00,  2, OAMData_32 ),
    [BATTLEANIMOAMSET_33] = battleanimoam(0x00,  7, OAMData_33 ),
    [BATTLEANIMOAMSET_34] = battleanimoam(0x00, 14, OAMData_32 ),
    [BATTLEANIMOAMSET_35] = battleanimoam(0x00, 21, OAMData_33 ),
    [BATTLEANIMOAMSET_36] = battleanimoam(0x00,  2, OAMData_36 ),
    [BATTLEANIMOAMSET_37] = battleanimoam(0x00,  6, OAMData_36 ),
    [BATTLEANIMOAMSET_38] = battleanimoam(0x00, 10, OAMData_36 ),
    [BATTLEANIMOAMSET_39] = battleanimoam(0x00, 14, OAMData_36 ),
    [BATTLEANIMOAMSET_3A] = battleanimoam(0x00,  2, OAMData_3a ),
    [BATTLEANIMOAMSET_3B] = battleanimoam(0x00,  6, OAMData_3a ),
    [BATTLEANIMOAMSET_3C] = battleanimoam(0x00, 10, OAMData_3a ),
    [BATTLEANIMOAMSET_3D] = battleanimoam(0x00, 14, OAMData_3a ),
    [BATTLEANIMOAMSET_3E] = battleanimoam(0x00,  4, OAMData_3e ),
    [BATTLEANIMOAMSET_3F] = battleanimoam(0x00, 16, OAMData_3e ),
    [BATTLEANIMOAMSET_40] = battleanimoam(0x00, 26, OAMData_3e ),
    [BATTLEANIMOAMSET_41] = battleanimoam(0x00, 26, OAMData_41 ),
    [BATTLEANIMOAMSET_42] = battleanimoam(0x0e,  4, OAMData_42 ),
    [BATTLEANIMOAMSET_43] = battleanimoam(0x0e,  8, OAMData_42 ),
    [BATTLEANIMOAMSET_44] = battleanimoam(0x0e,  4, OAMData_44 ),
    [BATTLEANIMOAMSET_45] = battleanimoam(0x0e,  8, OAMData_44 ),
    [BATTLEANIMOAMSET_46] = battleanimoam(0x0e,  4, OAMData_46 ),
    [BATTLEANIMOAMSET_47] = battleanimoam(0x0e,  4, OAMData_47 ),
    [BATTLEANIMOAMSET_48] = battleanimoam(0x00,  6, OAMData_48 ),
    [BATTLEANIMOAMSET_49] = battleanimoam(0x03,  4, OAMData_49 ),
    [BATTLEANIMOAMSET_4A] = battleanimoam(0x03,  2, OAMData_4a ),
    [BATTLEANIMOAMSET_4B] = battleanimoam(0x01,  5, OAMData_0f ),
    [BATTLEANIMOAMSET_4C] = battleanimoam(0x01,  6, OAMData_4c ),
    [BATTLEANIMOAMSET_4D] = battleanimoam(0x01,  7, OAMData_4d ),
    [BATTLEANIMOAMSET_4E] = battleanimoam(0x01,  3, OAMData_4d ),
    [BATTLEANIMOAMSET_4F] = battleanimoam(0x01,  8, OAMData_4f ),
    [BATTLEANIMOAMSET_50] = battleanimoam(0x01,  9, OAMData_50 ),
    [BATTLEANIMOAMSET_51] = battleanimoam(0x01, 10, OAMData_51 ),
    [BATTLEANIMOAMSET_52] = battleanimoam(0x01,  6, OAMData_51 ),
    [BATTLEANIMOAMSET_53] = battleanimoam(0x00,  9, OAMData_01 ),
    [BATTLEANIMOAMSET_54] = battleanimoam(0x04,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_55] = battleanimoam(0x05,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_56] = battleanimoam(0x00,  2, OAMData_56 ),
    [BATTLEANIMOAMSET_57] = battleanimoam(0x02,  2, OAMData_56 ),
    [BATTLEANIMOAMSET_58] = battleanimoam(0x04,  2, OAMData_56 ),
    [BATTLEANIMOAMSET_59] = battleanimoam(0x02,  4, OAMData_59 ),
    [BATTLEANIMOAMSET_5A] = battleanimoam(0x02,  4, OAMData_5a ),
    [BATTLEANIMOAMSET_5B] = battleanimoam(0x02,  2, OAMData_0c ),
    [BATTLEANIMOAMSET_5C] = battleanimoam(0x04,  2, OAMData_0c ),
    [BATTLEANIMOAMSET_5D] = battleanimoam(0x06,  4, OAMData_5d ),
    [BATTLEANIMOAMSET_5E] = battleanimoam(0x08,  2, OAMData_0c ),
    [BATTLEANIMOAMSET_5F] = battleanimoam(0x09,  2, OAMData_0c ),
    [BATTLEANIMOAMSET_60] = battleanimoam(0x05,  2, OAMData_60 ),
    [BATTLEANIMOAMSET_61] = battleanimoam(0x00,  2, OAMData_61 ),
    [BATTLEANIMOAMSET_62] = battleanimoam(0x00,  5, OAMData_61 ),
    [BATTLEANIMOAMSET_63] = battleanimoam(0x00,  9, OAMData_61 ),
    [BATTLEANIMOAMSET_64] = battleanimoam(0x09,  9, OAMData_61 ),
    [BATTLEANIMOAMSET_65] = battleanimoam(0x00,  4, OAMData_65 ),
    [BATTLEANIMOAMSET_66] = battleanimoam(0x00,  7, OAMData_65 ),
    [BATTLEANIMOAMSET_67] = battleanimoam(0x00,  9, OAMData_65 ),
    [BATTLEANIMOAMSET_68] = battleanimoam(0x09,  9, OAMData_65 ),
    [BATTLEANIMOAMSET_69] = battleanimoam(0x04,  1, OAMData_69 ),
    [BATTLEANIMOAMSET_6A] = battleanimoam(0x05,  2, OAMData_6a ),
    [BATTLEANIMOAMSET_6B] = battleanimoam(0x06,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_6C] = battleanimoam(0x0a,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_6D] = battleanimoam(0x0e,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_6E] = battleanimoam(0x08,  5, OAMData_6e ),
    [BATTLEANIMOAMSET_6F] = battleanimoam(0x0d,  3, OAMData_6f ),
    [BATTLEANIMOAMSET_70] = battleanimoam(0x01,  8, OAMData_70 ),
    [BATTLEANIMOAMSET_71] = battleanimoam(0x03,  8, OAMData_70 ),
    [BATTLEANIMOAMSET_72] = battleanimoam(0x05,  8, OAMData_70 ),
    [BATTLEANIMOAMSET_73] = battleanimoam(0x07,  8, OAMData_70 ),
    [BATTLEANIMOAMSET_74] = battleanimoam(0x06,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_75] = battleanimoam(0x07,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_76] = battleanimoam(0x0a,  2, OAMData_76 ),
    [BATTLEANIMOAMSET_77] = battleanimoam(0x00,  1, OAMData_77 ),
    [BATTLEANIMOAMSET_78] = battleanimoam(0x00,  3, OAMData_78 ),
    [BATTLEANIMOAMSET_79] = battleanimoam(0x00,  6, OAMData_79 ),
    [BATTLEANIMOAMSET_7A] = battleanimoam(0x00,  9, OAMData_7a ),
    [BATTLEANIMOAMSET_7B] = battleanimoam(0x00, 12, OAMData_7b ),
    [BATTLEANIMOAMSET_7C] = battleanimoam(0x00, 14, OAMData_7c ),
    [BATTLEANIMOAMSET_7D] = battleanimoam(0x00, 15, OAMData_7d ),
    [BATTLEANIMOAMSET_7E] = battleanimoam(0x04,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_7F] = battleanimoam(0x08,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_80] = battleanimoam(0x0d,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_81] = battleanimoam(0x0e,  4, OAMData_81 ),
    [BATTLEANIMOAMSET_82] = battleanimoam(0x10,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_83] = battleanimoam(0x11,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_84] = battleanimoam(0x04,  2, OAMData_6a ),
    [BATTLEANIMOAMSET_85] = battleanimoam(0x05,  2, OAMData_6a ),
    [BATTLEANIMOAMSET_86] = battleanimoam(0x0a,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_87] = battleanimoam(0x00,  8, OAMData_87 ),
    [BATTLEANIMOAMSET_88] = battleanimoam(0x00, 12, OAMData_88 ),
    [BATTLEANIMOAMSET_89] = battleanimoam(0x00, 16, OAMData_87 ),
    [BATTLEANIMOAMSET_8A] = battleanimoam(0x09,  2, OAMData_8a ),
    [BATTLEANIMOAMSET_8B] = battleanimoam(0x09,  4, OAMData_8a ),
    [BATTLEANIMOAMSET_8C] = battleanimoam(0x09,  6, OAMData_8a ),
    [BATTLEANIMOAMSET_8D] = battleanimoam(0x09,  8, OAMData_8a ),
    [BATTLEANIMOAMSET_8E] = battleanimoam(0x12,  5, OAMData_8e ),
    [BATTLEANIMOAMSET_8F] = battleanimoam(0x00,  4, OAMData_8f ),
    [BATTLEANIMOAMSET_90] = battleanimoam(0x04,  4, OAMData_8f ),
    [BATTLEANIMOAMSET_91] = battleanimoam(0x08,  4, OAMData_8f ),
    [BATTLEANIMOAMSET_92] = battleanimoam(0x0c,  4, OAMData_8f ),
    [BATTLEANIMOAMSET_93] = battleanimoam(0x00,  6, OAMData_93 ),
    [BATTLEANIMOAMSET_94] = battleanimoam(0x04,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_95] = battleanimoam(0x0a,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_96] = battleanimoam(0x15,  4, OAMData_30 ),
    [BATTLEANIMOAMSET_97] = battleanimoam(0x04,  4, OAMData_30 ),
    [BATTLEANIMOAMSET_98] = battleanimoam(0x0c,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_99] = battleanimoam(0x0a,  4, OAMData_99 ),
    [BATTLEANIMOAMSET_9A] = battleanimoam(0x0c,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_9B] = battleanimoam(0x00, 36, OAMData_9b ),
    [BATTLEANIMOAMSET_9C] = battleanimoam(0x0d,  2, OAMData_9c ),
    [BATTLEANIMOAMSET_9D] = battleanimoam(0x0d,  4, OAMData_9c ),
    [BATTLEANIMOAMSET_9E] = battleanimoam(0x0d,  6, OAMData_9c ),
    [BATTLEANIMOAMSET_9F] = battleanimoam(0x02,  8, OAMData_9f ),
    [BATTLEANIMOAMSET_A0] = battleanimoam(0x08,  7, OAMData_a0 ),
    [BATTLEANIMOAMSET_A1] = battleanimoam(0x08,  5, OAMData_a0 ),
    [BATTLEANIMOAMSET_A2] = battleanimoam(0x08,  3, OAMData_a0 ),
    [BATTLEANIMOAMSET_A3] = battleanimoam(0x00, 16, OAMData_1c ),
    [BATTLEANIMOAMSET_A4] = battleanimoam(0x00,  9, OAMData_a4 ),
    [BATTLEANIMOAMSET_A5] = battleanimoam(0x06,  9, OAMData_a4 ),
    [BATTLEANIMOAMSET_A6] = battleanimoam(0x0c,  9, OAMData_a4 ),
    [BATTLEANIMOAMSET_A7] = battleanimoam(0x12,  9, OAMData_a4 ),
    [BATTLEANIMOAMSET_A8] = battleanimoam(0x18,  9, OAMData_a4 ),
    [BATTLEANIMOAMSET_A9] = battleanimoam(0x1e,  9, OAMData_a4 ),
    [BATTLEANIMOAMSET_AA] = battleanimoam(0x24,  9, OAMData_a4 ),
    [BATTLEANIMOAMSET_AB] = battleanimoam(0x2a,  9, OAMData_a4 ),
    [BATTLEANIMOAMSET_AC] = battleanimoam(0x03,  4, OAMData_ac ),
    [BATTLEANIMOAMSET_AD] = battleanimoam(0x12,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_AE] = battleanimoam(0x10,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_AF] = battleanimoam(0x16,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_B0] = battleanimoam(0x17,  4, OAMData_02 ),
    [BATTLEANIMOAMSET_B1] = battleanimoam(0x18,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_B2] = battleanimoam(0x1c,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_B3] = battleanimoam(0x20,  3, OAMData_03 ),
    [BATTLEANIMOAMSET_B4] = battleanimoam(0x23,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_B5] = battleanimoam(0x25,  3, OAMData_03 ),
    [BATTLEANIMOAMSET_B6] = battleanimoam(0x17,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_B7] = battleanimoam(0x0a, 16, OAMData_00 ),
    [BATTLEANIMOAMSET_B8] = battleanimoam(0x10, 16, OAMData_1c ),
    [BATTLEANIMOAMSET_B9] = battleanimoam(0x00, 16, OAMData_1c ),
    [BATTLEANIMOAMSET_BA] = battleanimoam(0x04,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_BB] = battleanimoam(0x08,  2, OAMData_11 ),
    [BATTLEANIMOAMSET_BC] = battleanimoam(0x20,  6, OAMData_bc ),
    [BATTLEANIMOAMSET_BD] = battleanimoam(0x08,  1, OAMData_0f ),
    [BATTLEANIMOAMSET_BE] = battleanimoam(0x04,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_BF] = battleanimoam(0x1a,  4, OAMData_30 ),
    [BATTLEANIMOAMSET_C0] = battleanimoam(0x16,  9, OAMData_01 ),
    [BATTLEANIMOAMSET_C1] = battleanimoam(0x10, 16, OAMData_c1 ),
    [BATTLEANIMOAMSET_C2] = battleanimoam(0x09,  6, OAMData_c2 ),
    [BATTLEANIMOAMSET_C3] = battleanimoam(0x11,  9, OAMData_c3 ),
    [BATTLEANIMOAMSET_C4] = battleanimoam(0x0e,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_C5] = battleanimoam(0x0b,  4, OAMData_30 ),
    [BATTLEANIMOAMSET_C6] = battleanimoam(0x1c,  6, OAMData_02 ),
    [BATTLEANIMOAMSET_C7] = battleanimoam(0x20, 16, OAMData_c1 ),
    [BATTLEANIMOAMSET_C8] = battleanimoam(0x05,  6, OAMData_c8 ),
    [BATTLEANIMOAMSET_C9] = battleanimoam(0x0b,  4, OAMData_03 ),
    [BATTLEANIMOAMSET_CA] = battleanimoam(0x09,  4, OAMData_ca ),
    [BATTLEANIMOAMSET_CB] = battleanimoam(0x0b,  4, OAMData_04 ),
    [BATTLEANIMOAMSET_CC] = battleanimoam(0x11, 13, OAMData_cc ),
    [BATTLEANIMOAMSET_CD] = battleanimoam(0x00,  9, OAMData_c3 ),
    [BATTLEANIMOAMSET_CE] = battleanimoam(0x09,  9, OAMData_c3 ),
    [BATTLEANIMOAMSET_CF] = battleanimoam(0x00, 12, OAMData_cf ),
    [BATTLEANIMOAMSET_D0] = battleanimoam(0x06, 12, OAMData_cf ),
    [BATTLEANIMOAMSET_D1] = battleanimoam(0x0c, 12, OAMData_cf ),
    [BATTLEANIMOAMSET_D2] = battleanimoam(0x12, 12, OAMData_cf ),
    [BATTLEANIMOAMSET_D3] = battleanimoam(0x00, 13, OAMData_cc ),
    [BATTLEANIMOAMSET_D4] = battleanimoam(0x00,  7, OAMData_d4 ),
    [BATTLEANIMOAMSET_D5] = battleanimoam(0x00,  6, OAMData_d5 ),
    [BATTLEANIMOAMSET_D6] = battleanimoam(0x00, 14, OAMData_d6 ),
    [BATTLEANIMOAMSET_D7] = battleanimoam(0x00, 12, OAMData_d7 ),
};
static_assert(lengthof(BattleAnimOAMData) == NUM_BATTLEANIMOAMSETS, "");
