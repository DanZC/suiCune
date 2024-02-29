#include "../../constants.h"

static const uint8_t OAMData_1x1_Palette0[] = {
    1,
    dbsprite(-1, -1,  4,  4, 0x00, 0),
};

static const uint8_t OAMData_GSIntroShellder[] = {
    4,
    dbsprite(-1, -1,  0,  0, 0x00, 0),
    dbsprite( 0, -1,  0,  0, 0x01, 0),
    dbsprite(-1,  0,  0,  0, 0x10, 0),
    dbsprite( 0,  0,  0,  0, 0x11, 0),
};

static const uint8_t OAMData_GSGameFreakLogoStar[] = {
    4,
    dbsprite(-1, -1,  0,  0, 0x00, 0),
    dbsprite( 0, -1,  0,  0, 0x00, 0 | X_FLIP),
    dbsprite(-1,  0,  0,  0, 0x01, 0),
    dbsprite( 0,  0,  0,  0, 0x01, 0 | X_FLIP),
};

static const uint8_t OAMData_TradePokeBall1[] = {
    4,
    dbsprite(-1, -1,  0,  0, 0x00, 0 | PRIORITY),
    dbsprite( 0, -1,  0,  0, 0x00, 0 | X_FLIP | PRIORITY),
    dbsprite(-1,  0,  0,  0, 0x01, 0 | PRIORITY),
    dbsprite( 0,  0,  0,  0, 0x01, 0 | X_FLIP | PRIORITY),
};

static const uint8_t OAMData_IntroUnownF2_1[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, 0),
    dbsprite(  0, -1,  0,  0, 0x00, 0 | X_FLIP),
    dbsprite( -1,  0,  0,  0, 0x00, 0 | Y_FLIP),
    dbsprite(  0,  0,  0,  0, 0x00, 0 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_TradeTubeBulge[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, 7),
    dbsprite(  0, -1,  0,  0, 0x00, 7 | X_FLIP),
    dbsprite( -1,  0,  0,  0, 0x00, 7 | Y_FLIP),
    dbsprite(  0,  0,  0,  0, 0x00, 7 | X_FLIP | Y_FLIP),
};

// .OAMData_Unknown1: ; unreferenced
// 	db 4
// 	dbsprite( -1, -1,  0,  0, 0x00, 0 | PRIORITY),
// 	dbsprite(  0, -1,  0,  0, 0x00, 0 | X_FLIP | PRIORITY),
// 	dbsprite( -1,  0,  0,  0, 0x00, 0 | Y_FLIP | PRIORITY),
// 	dbsprite(  0,  0,  0,  0, 0x00, 0 | X_FLIP | Y_FLIP | PRIORITY),

static const uint8_t OAMData_TradePoofBubble[] = {
    16,
    dbsprite( -2, -2,  0,  0, 0x00, 0),
    dbsprite( -1, -2,  0,  0, 0x01, 0),
    dbsprite( -2, -1,  0,  0, 0x02, 0),
    dbsprite( -1, -1,  0,  0, 0x03, 0),
    dbsprite(  0, -2,  0,  0, 0x01, 0 | X_FLIP),
    dbsprite(  1, -2,  0,  0, 0x00, 0 | X_FLIP),
    dbsprite(  0, -1,  0,  0, 0x03, 0 | X_FLIP),
    dbsprite(  1, -1,  0,  0, 0x02, 0 | X_FLIP),
    dbsprite( -2,  0,  0,  0, 0x02, 0 | Y_FLIP),
    dbsprite( -1,  0,  0,  0, 0x03, 0 | Y_FLIP),
    dbsprite( -2,  1,  0,  0, 0x00, 0 | Y_FLIP),
    dbsprite( -1,  1,  0,  0, 0x01, 0 | Y_FLIP),
    dbsprite(  0,  0,  0,  0, 0x03, 0 | X_FLIP | Y_FLIP),
    dbsprite(  1,  0,  0,  0, 0x02, 0 | X_FLIP | Y_FLIP),
    dbsprite(  0,  1,  0,  0, 0x01, 0 | X_FLIP | Y_FLIP),
    dbsprite(  1,  1,  0,  0, 0x00, 0 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_GSIntroBigFireball[] = {
    36,
    dbsprite( -3, -3,  0,  0, 0x00, 0),
    dbsprite( -2, -3,  0,  0, 0x01, 0),
    dbsprite( -1, -3,  0,  0, 0x02, 0),
    dbsprite( -3, -2,  0,  0, 0x03, 0),
    dbsprite( -2, -2,  0,  0, 0x04, 0),
    dbsprite( -1, -2,  0,  0, 0x05, 0),
    dbsprite( -3, -1,  0,  0, 0x06, 0),
    dbsprite( -2, -1,  0,  0, 0x05, 0),
    dbsprite( -1, -1,  0,  0, 0x05, 0),
    dbsprite(  0, -3,  0,  0, 0x02, 0 | X_FLIP),
    dbsprite(  1, -3,  0,  0, 0x01, 0 | X_FLIP),
    dbsprite(  2, -3,  0,  0, 0x00, 0 | X_FLIP),
    dbsprite(  0, -2,  0,  0, 0x05, 0 | X_FLIP),
    dbsprite(  1, -2,  0,  0, 0x04, 0 | X_FLIP),
    dbsprite(  2, -2,  0,  0, 0x03, 0 | X_FLIP),
    dbsprite(  0, -1,  0,  0, 0x05, 0 | X_FLIP),
    dbsprite(  1, -1,  0,  0, 0x05, 0 | X_FLIP),
    dbsprite(  2, -1,  0,  0, 0x06, 0 | X_FLIP),
    dbsprite( -3,  0,  0,  0, 0x06, 0 | Y_FLIP),
    dbsprite( -2,  0,  0,  0, 0x05, 0 | Y_FLIP),
    dbsprite( -1,  0,  0,  0, 0x05, 0 | Y_FLIP),
    dbsprite( -3,  1,  0,  0, 0x03, 0 | Y_FLIP),
    dbsprite( -2,  1,  0,  0, 0x04, 0 | Y_FLIP),
    dbsprite( -1,  1,  0,  0, 0x05, 0 | Y_FLIP),
    dbsprite( -3,  2,  0,  0, 0x00, 0 | Y_FLIP),
    dbsprite( -2,  2,  0,  0, 0x01, 0 | Y_FLIP),
    dbsprite( -1,  2,  0,  0, 0x02, 0 | Y_FLIP),
    dbsprite(  0,  0,  0,  0, 0x05, 0 | X_FLIP | Y_FLIP),
    dbsprite(  1,  0,  0,  0, 0x05, 0 | X_FLIP | Y_FLIP),
    dbsprite(  2,  0,  0,  0, 0x06, 0 | X_FLIP | Y_FLIP),
    dbsprite(  0,  1,  0,  0, 0x05, 0 | X_FLIP | Y_FLIP),
    dbsprite(  1,  1,  0,  0, 0x04, 0 | X_FLIP | Y_FLIP),
    dbsprite(  2,  1,  0,  0, 0x03, 0 | X_FLIP | Y_FLIP),
    dbsprite(  0,  2,  0,  0, 0x02, 0 | X_FLIP | Y_FLIP),
    dbsprite(  1,  2,  0,  0, 0x01, 0 | X_FLIP | Y_FLIP),
    dbsprite(  2,  2,  0,  0, 0x00, 0 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_Unused43_4A[] = {
    9,
    dbsprite( -2, -2,  4,  4, 0x00, 0),
    dbsprite( -1, -2,  4,  4, 0x01, 0),
    dbsprite(  0, -2,  4,  4, 0x02, 0),
    dbsprite( -2, -1,  4,  4, 0x10, 0),
    dbsprite( -1, -1,  4,  4, 0x11, 0),
    dbsprite(  0, -1,  4,  4, 0x12, 0),
    dbsprite( -2,  0,  4,  4, 0x20, 0),
    dbsprite( -1,  0,  4,  4, 0x21, 0),
    dbsprite(  0,  0,  4,  4, 0x22, 0),
};

static const uint8_t OAMData_GSIntroJigglypuffPikachu[] = {
    16,
    dbsprite( -2, -2,  0,  0, 0x00, 0),
    dbsprite( -1, -2,  0,  0, 0x01, 0),
    dbsprite(  0, -2,  0,  0, 0x02, 0),
    dbsprite(  1, -2,  0,  0, 0x03, 0),
    dbsprite( -2, -1,  0,  0, 0x10, 0),
    dbsprite( -1, -1,  0,  0, 0x11, 0),
    dbsprite(  0, -1,  0,  0, 0x12, 0),
    dbsprite(  1, -1,  0,  0, 0x13, 0),
    dbsprite( -2,  0,  0,  0, 0x20, 0),
    dbsprite( -1,  0,  0,  0, 0x21, 0),
    dbsprite(  0,  0,  0,  0, 0x22, 0),
    dbsprite(  1,  0,  0,  0, 0x23, 0),
    dbsprite( -2,  1,  0,  0, 0x30, 0),
    dbsprite( -1,  1,  0,  0, 0x31, 0),
    dbsprite(  0,  1,  0,  0, 0x32, 0),
    dbsprite(  1,  1,  0,  0, 0x33, 0),
};

static const uint8_t OAMData_GSIntroStarter[] = {
    25,
    dbsprite( -3, -3,  4,  4, 0x00, 0),
    dbsprite( -3, -2,  4,  4, 0x01, 0),
    dbsprite( -3, -1,  4,  4, 0x02, 0),
    dbsprite( -3,  0,  4,  4, 0x03, 0),
    dbsprite( -3,  1,  4,  4, 0x04, 0),
    dbsprite( -2, -3,  4,  4, 0x05, 0),
    dbsprite( -2, -2,  4,  4, 0x06, 0),
    dbsprite( -2, -1,  4,  4, 0x07, 0),
    dbsprite( -2,  0,  4,  4, 0x08, 0),
    dbsprite( -2,  1,  4,  4, 0x09, 0),
    dbsprite( -1, -3,  4,  4, 0x0a, 0),
    dbsprite( -1, -2,  4,  4, 0x0b, 0),
    dbsprite( -1, -1,  4,  4, 0x0c, 0),
    dbsprite( -1,  0,  4,  4, 0x0d, 0),
    dbsprite( -1,  1,  4,  4, 0x0e, 0),
    dbsprite(  0, -3,  4,  4, 0x0f, 0),
    dbsprite(  0, -2,  4,  4, 0x10, 0),
    dbsprite(  0, -1,  4,  4, 0x11, 0),
    dbsprite(  0,  0,  4,  4, 0x12, 0),
    dbsprite(  0,  1,  4,  4, 0x13, 0),
    dbsprite(  1, -3,  4,  4, 0x14, 0),
    dbsprite(  1, -2,  4,  4, 0x15, 0),
    dbsprite(  1, -1,  4,  4, 0x16, 0),
    dbsprite(  1,  0,  4,  4, 0x17, 0),
    dbsprite(  1,  1,  4,  4, 0x18, 0),
};

// .OAMData_Unknown2: ; unreferenced
// 	db 36
// 	dbsprite( -3, -3,  0,  0, 0x00, 0),
// 	dbsprite( -2, -3,  0,  0, 0x01, 0),
// 	dbsprite( -1, -3,  0,  0, 0x02, 0),
// 	dbsprite(  0, -3,  0,  0, 0x03, 0),
// 	dbsprite(  1, -3,  0,  0, 0x04, 0),
// 	dbsprite(  2, -3,  0,  0, 0x05, 0),
// 	dbsprite( -3, -2,  0,  0, 0x06, 0),
// 	dbsprite( -2, -2,  0,  0, 0x07, 0),
// 	dbsprite( -1, -2,  0,  0, 0x08, 0),
// 	dbsprite(  0, -2,  0,  0, 0x09, 0),
// 	dbsprite(  1, -2,  0,  0, 0x0a, 0),
// 	dbsprite(  2, -2,  0,  0, 0x0b, 0),
// 	dbsprite( -3, -1,  0,  0, 0x0c, 0),
// 	dbsprite( -2, -1,  0,  0, 0x0d, 0),
// 	dbsprite( -1, -1,  0,  0, 0x0e, 0),
// 	dbsprite(  0, -1,  0,  0, 0x0f, 0),
// 	dbsprite(  1, -1,  0,  0, 0x10, 0),
// 	dbsprite(  2, -1,  0,  0, 0x11, 0),
// 	dbsprite( -3,  0,  0,  0, 0x12, 0),
// 	dbsprite( -2,  0,  0,  0, 0x13, 0),
// 	dbsprite( -1,  0,  0,  0, 0x14, 0),
// 	dbsprite(  0,  0,  0,  0, 0x15, 0),
// 	dbsprite(  1,  0,  0,  0, 0x16, 0),
// 	dbsprite(  2,  0,  0,  0, 0x17, 0),
// 	dbsprite( -3,  1,  0,  0, 0x18, 0),
// 	dbsprite( -2,  1,  0,  0, 0x19, 0),
// 	dbsprite( -1,  1,  0,  0, 0x1a, 0),
// 	dbsprite(  0,  1,  0,  0, 0x1b, 0),
// 	dbsprite(  1,  1,  0,  0, 0x1c, 0),
// 	dbsprite(  2,  1,  0,  0, 0x1d, 0),
// 	dbsprite( -3,  2,  0,  0, 0x1e, 0),
// 	dbsprite( -2,  2,  0,  0, 0x1f, 0),
// 	dbsprite( -1,  2,  0,  0, 0x20, 0),
// 	dbsprite(  0,  2,  0,  0, 0x21, 0),
// 	dbsprite(  1,  2,  0,  0, 0x22, 0),
// 	dbsprite(  2,  2,  0,  0, 0x23, 0),

static const uint8_t OAMData_RedWalk[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, PAL_OW_RED),
    dbsprite(  0, -1,  0,  0, 0x01, PAL_OW_RED),
    dbsprite( -1,  0,  0,  0, 0x02, PAL_OW_RED),
    dbsprite(  0,  0,  0,  0, 0x03, PAL_OW_RED),
};

static const uint8_t OAMData_MagnetTrainRed[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, PAL_OW_RED | PRIORITY),
    dbsprite(  0, -1,  0,  0, 0x01, PAL_OW_RED | PRIORITY),
    dbsprite( -1,  0,  0,  0, 0x02, PAL_OW_RED | PRIORITY),
    dbsprite(  0,  0,  0,  0, 0x03, PAL_OW_RED | PRIORITY),
};

static const uint8_t OAMData_PartyMonWithMail1[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, PAL_OW_RED),
    dbsprite(  0, -1,  0,  0, 0x01, PAL_OW_RED),
    dbsprite( -1,  0,  0,  0, 0x08, PAL_OW_RED),
    dbsprite(  0,  0,  0,  0, 0x03, PAL_OW_RED),
};

static const uint8_t OAMData_PartyMonWithMail2[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x04, PAL_OW_RED),
    dbsprite(  0, -1,  0,  0, 0x05, PAL_OW_RED),
    dbsprite( -1,  0,  0,  0, 0x08, PAL_OW_RED),
    dbsprite(  0,  0,  0,  0, 0x07, PAL_OW_RED),
};

static const uint8_t OAMData_PartyMonWithItem1[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, PAL_OW_RED),
    dbsprite(  0, -1,  0,  0, 0x01, PAL_OW_RED),
    dbsprite( -1,  0,  0,  0, 0x09, PAL_OW_RED),
    dbsprite(  0,  0,  0,  0, 0x03, PAL_OW_RED),
};

static const uint8_t OAMData_PartyMonWithItem2[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x04, PAL_OW_RED),
    dbsprite(  0, -1,  0,  0, 0x05, PAL_OW_RED),
    dbsprite( -1,  0,  0,  0, 0x09, PAL_OW_RED),
    dbsprite(  0,  0,  0,  0, 0x07, PAL_OW_RED),
};

static const uint8_t OAMData_GSIntroMagikarp[] = {
    6,
    dbsprite( -2, -1,  4,  0, 0x00, 1),
    dbsprite( -1, -1,  4,  0, 0x01, 1),
    dbsprite(  0, -1,  4,  0, 0x02, 1),
    dbsprite( -2,  0,  4,  0, 0x10, 1),
    dbsprite( -1,  0,  4,  0, 0x11, 1),
    dbsprite(  0,  0,  4,  0, 0x12, 1),
};

static const uint8_t OAMData_GSIntroLapras[] = {
    29,
    dbsprite( -3, -3,  0,  0, 0x00, 0),
    dbsprite( -2, -3,  0,  0, 0x01, 0),
    dbsprite( -1, -3,  0,  0, 0x02, 0),
    dbsprite(  0, -3,  0,  0, 0x03, 0),
    dbsprite( -3, -2,  0,  0, 0x10, 0),
    dbsprite( -2, -2,  0,  0, 0x11, 0),
    dbsprite( -1, -2,  0,  0, 0x12, 0),
    dbsprite(  0, -2,  0,  0, 0x13, 0),
    dbsprite( -3, -1,  0,  0, 0x20, 0),
    dbsprite( -2, -1,  0,  0, 0x21, 0),
    dbsprite( -1, -1,  0,  0, 0x22, 0),
    dbsprite(  0, -1,  0,  0, 0x23, 0),
    dbsprite(  1, -1,  0,  0, 0x24, 0),
    dbsprite( -3,  0,  0,  0, 0x30, 0 | PRIORITY),
    dbsprite( -2,  0,  0,  0, 0x31, 0 | PRIORITY),
    dbsprite( -1,  0,  0,  0, 0x32, 0 | PRIORITY),
    dbsprite(  0,  0,  0,  0, 0x33, 0 | PRIORITY),
    dbsprite(  1,  0,  0,  0, 0x34, 0 | PRIORITY),
    dbsprite( -3,  1,  0,  0, 0x40, 0 | PRIORITY),
    dbsprite( -2,  1,  0,  0, 0x41, 0 | PRIORITY),
    dbsprite( -1,  1,  0,  0, 0x42, 0 | PRIORITY),
    dbsprite(  0,  1,  0,  0, 0x43, 0 | PRIORITY),
    dbsprite(  1,  1,  0,  0, 0x44, 0 | PRIORITY),
    dbsprite(  2,  1,  0,  0, 0x45, 0 | PRIORITY),
    dbsprite( -2,  2,  0,  0, 0x51, 0 | PRIORITY),
    dbsprite( -1,  2,  0,  0, 0x52, 0 | PRIORITY),
    dbsprite(  0,  2,  0,  0, 0x53, 0 | PRIORITY),
    dbsprite(  1,  2,  0,  0, 0x54, 0 | PRIORITY),
    dbsprite(  2,  2,  0,  0, 0x55, 0 | PRIORITY),
};

static const uint8_t OAMData_GSIntroNote[] = {
    2,
    dbsprite( -1, -1,  4,  0, 0x00, 0),
    dbsprite( -1,  0,  4,  0, 0x10, 0),
};

static const uint8_t OAMData_GSIntroPikachuTail[] = {
    5,
    dbsprite(  3, -2,  0,  0, 0x00, 0),
    dbsprite(  4, -2,  0,  0, 0x01, 0),
    dbsprite(  2, -1,  0,  0, 0x02, 0),
    dbsprite(  3, -1,  0,  0, 0x03, 0),
    dbsprite(  2,  0,  0,  0, 0x04, 0),
};

static const uint8_t OAMData_Leaf[] = {
    1,
    dbsprite( -1, -1,  4,  4, 0x00, PAL_OW_TREE),
};

static const uint8_t OAMData_Tree[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, PAL_OW_TREE),
    dbsprite(  0, -1,  0,  0, 0x01, PAL_OW_TREE),
    dbsprite( -1,  0,  0,  0, 0x02, PAL_OW_TREE),
    dbsprite(  0,  0,  0,  0, 0x03, PAL_OW_TREE),
};

static const uint8_t OAMData_TextEntryCursor[] = {
    4,
    dbsprite( -1, -1,  7,  7, 0x00, 0),
    dbsprite(  0, -1,  0,  7, 0x00, 0 | X_FLIP),
    dbsprite( -1,  0,  7,  0, 0x00, 0 | Y_FLIP),
    dbsprite(  0,  0,  0,  0, 0x00, 0 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_TextEntryCursorBig[] = {
    10,
    dbsprite(  0, -1,  0,  7, 0x00, 0),
    dbsprite(  1, -1,  0,  7, 0x01, 0),
    dbsprite(  2, -1,  0,  7, 0x01, 0),
    dbsprite(  3, -1,  0,  7, 0x01, 0),
    dbsprite(  4, -1,  0,  7, 0x00, 0 | X_FLIP),
    dbsprite(  0,  0,  0,  0, 0x00, 0 | Y_FLIP),
    dbsprite(  1,  0,  0,  0, 0x01, 0 | Y_FLIP),
    dbsprite(  2,  0,  0,  0, 0x01, 0 | Y_FLIP),
    dbsprite(  3,  0,  0,  0, 0x01, 0 | Y_FLIP),
    dbsprite(  4,  0,  0,  0, 0x00, 0 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_GSGameFreakLogo[] = {
    15,
    dbsprite( -2, -3,  4,  4, 0x00, 1 | OBP_NUM),
    dbsprite( -1, -3,  4,  4, 0x01, 1 | OBP_NUM),
    dbsprite(  0, -3,  4,  4, 0x02, 1 | OBP_NUM),
    dbsprite( -2, -2,  4,  4, 0x03, 1 | OBP_NUM),
    dbsprite( -1, -2,  4,  4, 0x04, 1 | OBP_NUM),
    dbsprite(  0, -2,  4,  4, 0x05, 1 | OBP_NUM),
    dbsprite( -2, -1,  4,  4, 0x06, 1 | OBP_NUM),
    dbsprite( -1, -1,  4,  4, 0x07, 1 | OBP_NUM),
    dbsprite(  0, -1,  4,  4, 0x08, 1 | OBP_NUM),
    dbsprite( -2,  0,  4,  4, 0x09, 1 | OBP_NUM),
    dbsprite( -1,  0,  4,  4, 0x0a, 1 | OBP_NUM),
    dbsprite(  0,  0,  4,  4, 0x0b, 1 | OBP_NUM),
    dbsprite( -2,  1,  4,  4, 0x0c, 1 | OBP_NUM),
    dbsprite( -1,  1,  4,  4, 0x0d, 1 | OBP_NUM),
    dbsprite(  0,  1,  4,  4, 0x0e, 1 | OBP_NUM),
};

static const uint8_t OAMData_SlotsGolem[] = {
    6,
    dbsprite( -2, -2,  4,  4, 0x00, 5 | OBP_NUM),
    dbsprite( -1, -2,  4,  4, 0x02, 5 | OBP_NUM),
    dbsprite(  0, -2,  4,  4, 0x00, 5 | OBP_NUM | X_FLIP),
    dbsprite( -2,  0,  4,  4, 0x04, 5 | OBP_NUM),
    dbsprite( -1,  0,  4,  4, 0x06, 5 | OBP_NUM),
    dbsprite(  0,  0,  4,  4, 0x04, 5 | OBP_NUM | X_FLIP),
};

static const uint8_t OAMData_SlotsChansey1[] = {
    6,
    dbsprite( -2, -2,  4,  4, 0x00, 6 | OBP_NUM),
    dbsprite( -1, -2,  4,  4, 0x02, 6 | OBP_NUM),
    dbsprite(  0, -2,  4,  4, 0x04, 6 | OBP_NUM),
    dbsprite( -2,  0,  4,  4, 0x06, 6 | OBP_NUM),
    dbsprite( -1,  0,  4,  4, 0x08, 6 | OBP_NUM),
    dbsprite(  0,  0,  4,  4, 0x0a, 6 | OBP_NUM),
};

static const uint8_t OAMData_SlotsChansey2[] = {
    6,
    dbsprite( -2, -2,  4,  4, 0x00, 6 | OBP_NUM),
    dbsprite( -1, -2,  4,  4, 0x02, 6 | OBP_NUM),
    dbsprite(  0, -2,  4,  4, 0x04, 6 | OBP_NUM),
    dbsprite( -2,  0,  4,  4, 0x0c, 6 | OBP_NUM),
    dbsprite( -1,  0,  4,  4, 0x0e, 6 | OBP_NUM),
    dbsprite(  0,  0,  4,  4, 0x10, 6 | OBP_NUM),
};

static const uint8_t OAMData_SlotsChansey3[] = {
    6,
    dbsprite( -2, -2,  4,  4, 0x00, 6 | OBP_NUM),
    dbsprite( -1, -2,  4,  4, 0x02, 6 | OBP_NUM),
    dbsprite(  0, -2,  4,  4, 0x04, 6 | OBP_NUM),
    dbsprite( -2,  0,  4,  4, 0x12, 6 | OBP_NUM),
    dbsprite( -1,  0,  4,  4, 0x14, 6 | OBP_NUM),
    dbsprite(  0,  0,  4,  4, 0x16, 6 | OBP_NUM),
};

static const uint8_t OAMData_SlotsChansey4[] = {
    6,
    dbsprite( -2, -2,  4,  4, 0x00, 6 | OBP_NUM),
    dbsprite( -1, -2,  4,  4, 0x02, 6 | OBP_NUM),
    dbsprite(  0, -2,  4,  4, 0x04, 6 | OBP_NUM),
    dbsprite( -2,  0,  4,  4, 0x18, 6 | OBP_NUM),
    dbsprite( -1,  0,  4,  4, 0x1a, 6 | OBP_NUM),
    dbsprite(  0,  0,  4,  4, 0x1c, 6 | OBP_NUM),
};

static const uint8_t OAMData_SlotsChansey5[] = {
    6,
    dbsprite( -2, -2,  4,  4, 0x1e, 6 | OBP_NUM),
    dbsprite( -1, -2,  4,  4, 0x20, 6 | OBP_NUM),
    dbsprite(  0, -2,  4,  4, 0x22, 6 | OBP_NUM),
    dbsprite( -2,  0,  4,  4, 0x24, 6 | OBP_NUM),
    dbsprite( -1,  0,  4,  4, 0x26, 6 | OBP_NUM),
    dbsprite(  0,  0,  4,  4, 0x28, 6 | OBP_NUM),
};

static const uint8_t OAMData_RadioTuningKnob[] = {
    3,
    dbsprite( -1, -2,  4,  4, 0x00, 0 | OBP_NUM),
    dbsprite( -1, -1,  4,  4, 0x00, 0 | OBP_NUM),
    dbsprite( -1,  0,  4,  4, 0x00, 0 | OBP_NUM),
};

static const uint8_t OAMData_Unused4B[] = {
    6,
    dbsprite(  0,  0,  0,  0, 0x00, 0),
    dbsprite(  1,  0,  0,  0, 0x01, 0),
    dbsprite(  2,  0,  0,  0, 0x01, 0),
    dbsprite(  3,  0,  0,  0, 0x01, 0),
    dbsprite(  4,  0,  0,  0, 0x02, 0),
    dbsprite(  5,  0,  0,  0, 0x03, 0),
};

static const uint8_t OAMData_Unused4C[] = {
    4,
    dbsprite(  0,  0,  0,  0, 0x00, 0),
    dbsprite(  1,  0,  0,  0, 0x01, 0),
    dbsprite(  2,  0,  0,  0, 0x02, 0),
    dbsprite(  3,  0,  0,  0, 0x03, 0),
};

static const uint8_t OAMData_CutTree2[] = {
    4,
    dbsprite( -2, -1,  6,  0, 0x00, PAL_OW_TREE),
    dbsprite(  0, -1,  2,  0, 0x01, PAL_OW_TREE),
    dbsprite( -2,  0,  6,  0, 0x02, PAL_OW_TREE),
    dbsprite(  0,  0,  2,  0, 0x03, PAL_OW_TREE),
};

static const uint8_t OAMData_CutTree3[] = {
    4,
    dbsprite( -2, -1,  4,  0, 0x00, PAL_OW_TREE),
    dbsprite(  0, -1,  4,  0, 0x01, PAL_OW_TREE),
    dbsprite( -2,  0,  4,  0, 0x02, PAL_OW_TREE),
    dbsprite(  0,  0,  4,  0, 0x03, PAL_OW_TREE),
};

static const uint8_t OAMData_CutTree4[] = {
    4,
    dbsprite( -2, -1,  0,  0, 0x00, PAL_OW_TREE),
    dbsprite(  1, -1,  0,  0, 0x01, PAL_OW_TREE),
    dbsprite( -2,  0,  0,  0, 0x02, PAL_OW_TREE),
    dbsprite(  1,  0,  0,  0, 0x03, PAL_OW_TREE),
};

static const uint8_t OAMData_GSIntroHoOhLugia1[] = {
    19,
    dbsprite( -4, -1,  0,  0, 0x00, 0),
    dbsprite( -3, -2,  0,  0, 0x02, 0),
    dbsprite( -3,  0,  0,  0, 0x04, 0),
    dbsprite( -2, -3,  0,  0, 0x06, 0),
    dbsprite( -2, -1,  0,  0, 0x08, 0),
    dbsprite( -2,  1,  0,  0, 0x0a, 0),
    dbsprite( -1, -3,  0,  0, 0x0c, 0),
    dbsprite( -1, -1,  0,  0, 0x0e, 0),
    dbsprite( -1,  1,  0,  0, 0x10, 0),
    dbsprite(  0, -3,  0,  0, 0x12, 0),
    dbsprite(  0, -1,  0,  0, 0x14, 0),
    dbsprite(  0,  1,  0,  0, 0x16, 0),
    dbsprite(  1, -3,  0,  0, 0x18, 0),
    dbsprite(  1, -1,  0,  0, 0x1a, 0),
    dbsprite(  1,  1,  0,  0, 0x1c, 0),
    dbsprite(  2, -1,  0,  0, 0x1e, 0),
    dbsprite(  2,  1,  0,  0, 0x20, 0),
    dbsprite(  3, -2,  0,  0, 0x22, 0),
    dbsprite(  3,  0,  0,  0, 0x24, 0),
};

static const uint8_t OAMData_GSIntroHoOhLugia2[] = {
    16,
    dbsprite( -4, -1,  0,  0, 0x00, 0),
    dbsprite( -3, -2,  0,  0, 0x02, 0),
    dbsprite( -3,  0,  0,  0, 0x04, 0),
    dbsprite( -2, -1,  0,  0, 0x26, 0),
    dbsprite( -2,  1,  0,  0, 0x0a, 0),
    dbsprite( -1, -3,  0,  0, 0x28, 0),
    dbsprite( -1, -1,  0,  0, 0x2a, 0),
    dbsprite( -1,  1,  0,  0, 0x10, 0),
    dbsprite(  0, -1,  0,  0, 0x2c, 0),
    dbsprite(  0,  1,  0,  0, 0x16, 0),
    dbsprite(  1, -1,  0,  0, 0x30, 0),
    dbsprite(  1,  1,  0,  0, 0x1c, 0),
    dbsprite(  2, -1,  0,  0, 0x1e, 0),
    dbsprite(  2,  1,  0,  0, 0x20, 0),
    dbsprite(  3, -2,  0,  0, 0x22, 0),
    dbsprite(  3,  0,  0,  0, 0x24, 0),
};

static const uint8_t OAMData_GSIntroHoOhLugia3[] = {
    15,
    dbsprite( -4, -1,  0,  0, 0x00, 0),
    dbsprite( -3, -2,  0,  0, 0x02, 0),
    dbsprite( -3,  0,  0,  0, 0x32, 0),
    dbsprite( -2, -1,  0,  0, 0x34, 0),
    dbsprite( -2,  1,  0,  0, 0x36, 0),
    dbsprite( -1, -1,  0,  0, 0x38, 0),
    dbsprite( -1,  1,  0,  0, 0x3a, 0),
    dbsprite(  0, -1,  0,  0, 0x3c, 0),
    dbsprite(  0,  1,  0,  0, 0x3e, 0),
    dbsprite(  1, -1,  0,  0, 0x30, 0),
    dbsprite(  1,  1,  0,  0, 0x1c, 0),
    dbsprite(  2, -1,  0,  0, 0x1e, 0),
    dbsprite(  2,  1,  0,  0, 0x20, 0),
    dbsprite(  3, -2,  0,  0, 0x22, 0),
    dbsprite(  3,  0,  0,  0, 0x24, 0),
};

static const uint8_t OAMData_GSIntroHoOhLugia4[] = {
    17,
    dbsprite( -4, -1,  0,  0, 0x00, 0),
    dbsprite( -3, -2,  0,  0, 0x02, 0),
    dbsprite( -3,  0,  0,  0, 0x04, 0),
    dbsprite( -2, -1,  0,  0, 0x40, 0),
    dbsprite( -2,  1,  0,  0, 0x42, 0),
    dbsprite( -2,  3,  0,  0, 0x44, 0),
    dbsprite( -1, -1,  0,  0, 0x46, 0),
    dbsprite( -1,  1,  0,  0, 0x48, 0),
    dbsprite( -1,  3,  0,  0, 0x4a, 0),
    dbsprite(  0, -1,  0,  0, 0x4c, 0),
    dbsprite(  0,  1,  0,  0, 0x4e, 0),
    dbsprite(  1, -1,  0,  0, 0x30, 0),
    dbsprite(  1,  1,  0,  0, 0x1c, 0),
    dbsprite(  2, -1,  0,  0, 0x1e, 0),
    dbsprite(  2,  1,  0,  0, 0x20, 0),
    dbsprite(  3, -2,  0,  0, 0x22, 0),
    dbsprite(  3,  0,  0,  0, 0x24, 0),
};

static const uint8_t OAMData_GSIntroHoOhLugia5[] = {
    17,
    dbsprite( -4, -1,  0,  0, 0x00, 0),
    dbsprite( -3, -2,  0,  0, 0x02, 0),
    dbsprite( -3,  0,  0,  0, 0x04, 0),
    dbsprite( -2, -1,  0,  0, 0x50, 0),
    dbsprite( -2,  1,  0,  0, 0x0a, 0),
    dbsprite( -1, -3,  0,  0, 0x52, 0),
    dbsprite( -1, -1,  0,  0, 0x54, 0),
    dbsprite( -1,  1,  0,  0, 0x10, 0),
    dbsprite(  0, -3,  0,  0, 0x56, 0),
    dbsprite(  0, -1,  0,  0, 0x2e, 0),
    dbsprite(  0,  1,  0,  0, 0x16, 0),
    dbsprite(  1, -1,  0,  0, 0x30, 0),
    dbsprite(  1,  1,  0,  0, 0x1c, 0),
    dbsprite(  2, -1,  0,  0, 0x1e, 0),
    dbsprite(  2,  1,  0,  0, 0x20, 0),
    dbsprite(  3, -2,  0,  0, 0x22, 0),
    dbsprite(  3,  0,  0,  0, 0x24, 0),
};

static const uint8_t OAMData_GSTitleTrail[] = {
    1,
    dbsprite( -1, -1,  4,  4, 0x00, 1 | OBP_NUM),
};

static const uint8_t OAMData_EZChatCursor1[] = {
    12,
    dbsprite(  0,  0,  0,  0, 0x30, 0),
    dbsprite(  1,  0,  0,  0, 0x31, 0),
    dbsprite(  2,  0,  0,  0, 0x31, 0),
    dbsprite(  3,  0,  0,  0, 0x31, 0),
    dbsprite(  4,  0,  0,  0, 0x31, 0),
    dbsprite(  5,  0,  0,  0, 0x32, 0),
    dbsprite(  0,  1,  0,  0, 0x33, 0),
    dbsprite(  1,  1,  0,  0, 0x34, 0),
    dbsprite(  2,  1,  0,  0, 0x34, 0),
    dbsprite(  3,  1,  0,  0, 0x34, 0),
    dbsprite(  4,  1,  0,  0, 0x34, 0),
    dbsprite(  5,  1,  0,  0, 0x35, 0),
};

static const uint8_t OAMData_EZChatCursor2[] = {
    1,
    dbsprite(  0,  0,  0,  0, 0xed, 0),
};

static const uint8_t OAMData_EZChatCursor3[] = {
    4,
    dbsprite( -1, -1,  7,  7, 0x30, 0),
    dbsprite(  0, -1,  1,  7, 0x32, 0),
    dbsprite( -1,  0,  7,  1, 0x33, 0),
    dbsprite(  0,  0,  1,  1, 0x35, 0),
};

static const uint8_t OAMData_EZChatCursor4[] = {
    8,
    dbsprite( -1, -1,  7,  7, 0x30, 0),
    dbsprite(  0, -1,  4,  7, 0x31, 0),
    dbsprite(  1, -1,  4,  7, 0x31, 0),
    dbsprite(  2, -1,  1,  7, 0x32, 0),
    dbsprite( -1,  0,  7,  1, 0x33, 0),
    dbsprite(  0,  0,  4,  1, 0x34, 0),
    dbsprite(  1,  0,  4,  1, 0x34, 0),
    dbsprite(  2,  0,  1,  1, 0x35, 0),
};

static const uint8_t OAMData_EZChatCursor5[] = {
    1,
    dbsprite(  0,  0,  0,  0, 0x34, 0),
};

static const uint8_t OAMData_EZChatCursor6[] = {
    2,
    dbsprite(  0,  0,  0,  0, 0x30, 0),
    dbsprite(  0,  1,  0,  0, 0x33, 0),
};

static const uint8_t OAMData_EZChatCursor7[] = {
    2,
    dbsprite(  0,  0,  0,  0, 0x32, 0),
    dbsprite(  0,  1,  0,  0, 0x35, 0),
};

static const uint8_t OAMData_BlueWalk[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, PAL_OW_BLUE),
    dbsprite(  0, -1,  0,  0, 0x01, PAL_OW_BLUE),
    dbsprite( -1,  0,  0,  0, 0x02, PAL_OW_BLUE),
    dbsprite(  0,  0,  0,  0, 0x03, PAL_OW_BLUE),
};

static const uint8_t OAMData_MagnetTrainBlue[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, PAL_OW_BLUE | PRIORITY),
    dbsprite(  0, -1,  0,  0, 0x01, PAL_OW_BLUE | PRIORITY),
    dbsprite( -1,  0,  0,  0, 0x02, PAL_OW_BLUE | PRIORITY),
    dbsprite(  0,  0,  0,  0, 0x03, PAL_OW_BLUE | PRIORITY),
};

static const uint8_t OAMData_MobileTradeCableBulge[] = {
    1,
    dbsprite( -1, -1,  4,  4, 0x00, 2),
};

static const uint8_t OAMData_MobileTradeSentPulse[] = {
    4,
    dbsprite( -1, -2,  4,  0, 0x00, 3),
    dbsprite( -1, -1,  4,  0, 0x01, 3),
    dbsprite( -1,  0,  4,  0, 0x02, 3),
    dbsprite( -1,  1,  4,  0, 0x03, 3),
};

static const uint8_t OAMData_MobileTradeOTPulse[] = {
    4,
    dbsprite( -1, -2,  4,  0, 0x03, 4 | Y_FLIP),
    dbsprite( -1, -1,  4,  0, 0x02, 4 | Y_FLIP),
    dbsprite( -1,  0,  4,  0, 0x01, 4 | Y_FLIP),
    dbsprite( -1,  1,  4,  0, 0x00, 4 | Y_FLIP),
};

static const uint8_t OAMData_MobileTradePing1[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, 1),
    dbsprite(  0, -1,  0,  0, 0x00, 1 | X_FLIP),
    dbsprite( -1,  0,  0,  0, 0x00, 1 | Y_FLIP),
    dbsprite(  0,  0,  0,  0, 0x00, 1 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_MobileTradePing2[] = {
    8,
    dbsprite( -2, -2,  4,  4, 0x00, 1),
    dbsprite( -1, -2,  4,  4, 0x01, 1),
    dbsprite(  0, -2,  4,  4, 0x00, 1 | X_FLIP),
    dbsprite( -2, -1,  4,  4, 0x02, 1),
    dbsprite(  0, -1,  4,  4, 0x02, 1 | X_FLIP),
    dbsprite( -2,  0,  4,  4, 0x00, 1 | Y_FLIP),
    dbsprite( -1,  0,  4,  4, 0x01, 1 | Y_FLIP),
    dbsprite(  0,  0,  4,  4, 0x00, 1 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_MobileTradePing3[] = {
    12,
    dbsprite( -2, -2,  0,  0, 0x00, 1),
    dbsprite( -1, -2,  0,  0, 0x01, 1),
    dbsprite( -2, -1,  0,  0, 0x02, 1),
    dbsprite(  0, -2,  0,  0, 0x01, 1 | X_FLIP),
    dbsprite(  1, -2,  0,  0, 0x00, 1 | X_FLIP),
    dbsprite(  1, -1,  0,  0, 0x02, 1 | X_FLIP),
    dbsprite( -2,  0,  0,  0, 0x02, 1 | Y_FLIP),
    dbsprite( -2,  1,  0,  0, 0x00, 1 | Y_FLIP),
    dbsprite( -1,  1,  0,  0, 0x01, 1 | Y_FLIP),
    dbsprite(  1,  0,  0,  0, 0x02, 1 | X_FLIP | Y_FLIP),
    dbsprite(  0,  1,  0,  0, 0x01, 1 | X_FLIP | Y_FLIP),
    dbsprite(  1,  1,  0,  0, 0x00, 1 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_IntroSuicune1[] = {
    36,
    dbsprite(  1, -3,  0,  0, 0x05, 0),
    dbsprite(  2, -3,  0,  0, 0x06, 0),
    dbsprite(  3, -3,  0,  0, 0x07, 0),
    dbsprite( -3, -2,  0,  0, 0x11, 0),
    dbsprite( -2, -2,  0,  0, 0x12, 0),
    dbsprite( -1, -2,  0,  0, 0x13, 0),
    dbsprite(  0, -2,  0,  0, 0x14, 0),
    dbsprite(  1, -2,  0,  0, 0x15, 0),
    dbsprite(  2, -2,  0,  0, 0x16, 0),
    dbsprite(  3, -2,  0,  0, 0x17, 0),
    dbsprite( -4, -1,  0,  0, 0x20, 0),
    dbsprite( -3, -1,  0,  0, 0x21, 0),
    dbsprite( -2, -1,  0,  0, 0x22, 0),
    dbsprite( -1, -1,  0,  0, 0x23, 0),
    dbsprite(  0, -1,  0,  0, 0x24, 0),
    dbsprite(  1, -1,  0,  0, 0x25, 0),
    dbsprite(  2, -1,  0,  0, 0x26, 0),
    dbsprite(  3, -1,  0,  0, 0x27, 0),
    dbsprite( -4,  0,  0,  0, 0x30, 0),
    dbsprite( -3,  0,  0,  0, 0x31, 0),
    dbsprite( -2,  0,  0,  0, 0x32, 0),
    dbsprite( -1,  0,  0,  0, 0x33, 0),
    dbsprite(  0,  0,  0,  0, 0x34, 0),
    dbsprite(  1,  0,  0,  0, 0x35, 0),
    dbsprite(  2,  0,  0,  0, 0x36, 0),
    dbsprite( -4,  1,  0,  0, 0x40, 0),
    dbsprite( -3,  1,  0,  0, 0x41, 0),
    dbsprite( -2,  1,  0,  0, 0x42, 0),
    dbsprite( -1,  1,  0,  0, 0x43, 0),
    dbsprite(  0,  1,  0,  0, 0x44, 0),
    dbsprite(  1,  1,  0,  0, 0x45, 0),
    dbsprite(  2,  1,  0,  0, 0x46, 0),
    dbsprite(  3,  1,  0,  0, 0x47, 0),
    dbsprite( -4,  2,  0,  0, 0x50, 0),
    dbsprite( -3,  2,  0,  0, 0x51, 0),
    dbsprite(  3,  2,  0,  0, 0x57, 0),
};

static const uint8_t OAMData_IntroSuicune2[] = {
    28,
    dbsprite(  0, -3,  0,  0, 0x04, 0),
    dbsprite(  1, -3,  0,  0, 0x05, 0),
    dbsprite(  2, -3,  0,  0, 0x06, 0),
    dbsprite( -3, -2,  0,  0, 0x11, 0),
    dbsprite( -2, -2,  0,  0, 0x12, 0),
    dbsprite( -1, -2,  0,  0, 0x13, 0),
    dbsprite(  0, -2,  0,  0, 0x14, 0),
    dbsprite(  1, -2,  0,  0, 0x15, 0),
    dbsprite(  2, -2,  0,  0, 0x16, 0),
    dbsprite( -3, -1,  0,  0, 0x21, 0),
    dbsprite( -2, -1,  0,  0, 0x22, 0),
    dbsprite( -1, -1,  0,  0, 0x23, 0),
    dbsprite(  0, -1,  0,  0, 0x24, 0),
    dbsprite(  1, -1,  0,  0, 0x25, 0),
    dbsprite(  2, -1,  0,  0, 0x26, 0),
    dbsprite( -4,  0,  0,  0, 0x30, 0),
    dbsprite( -3,  0,  0,  0, 0x31, 0),
    dbsprite( -2,  0,  0,  0, 0x32, 0),
    dbsprite( -1,  0,  0,  0, 0x33, 0),
    dbsprite(  0,  0,  0,  0, 0x34, 0),
    dbsprite(  1,  0,  0,  0, 0x35, 0),
    dbsprite( -2,  1,  0,  0, 0x42, 0),
    dbsprite( -1,  1,  0,  0, 0x43, 0),
    dbsprite(  0,  1,  0,  0, 0x44, 0),
    dbsprite(  1,  1,  0,  0, 0x45, 0),
    dbsprite( -1,  2,  0,  0, 0x53, 0),
    dbsprite(  0,  2,  0,  0, 0x54, 0),
    dbsprite(  1,  2,  0,  0, 0x55, 0),
};

static const uint8_t OAMData_IntroSuicune3[] = {
    30,
    dbsprite(  0, -3,  0,  0, 0x04, 0),
    dbsprite(  1, -3,  0,  0, 0x05, 0),
    dbsprite( -3, -2,  0,  0, 0x11, 0),
    dbsprite( -2, -2,  0,  0, 0x12, 0),
    dbsprite( -1, -2,  0,  0, 0x13, 0),
    dbsprite(  0, -2,  0,  0, 0x14, 0),
    dbsprite(  1, -2,  0,  0, 0x15, 0),
    dbsprite(  2, -2,  0,  0, 0x16, 0),
    dbsprite(  3, -2,  0,  0, 0x17, 0),
    dbsprite( -4, -1,  0,  0, 0x20, 0),
    dbsprite( -3, -1,  0,  0, 0x21, 0),
    dbsprite( -2, -1,  0,  0, 0x22, 0),
    dbsprite( -1, -1,  0,  0, 0x23, 0),
    dbsprite(  0, -1,  0,  0, 0x24, 0),
    dbsprite(  1, -1,  0,  0, 0x25, 0),
    dbsprite(  2, -1,  0,  0, 0x26, 0),
    dbsprite( -4,  0,  0,  0, 0x30, 0),
    dbsprite( -3,  0,  0,  0, 0x31, 0),
    dbsprite( -2,  0,  0,  0, 0x32, 0),
    dbsprite( -1,  0,  0,  0, 0x33, 0),
    dbsprite(  0,  0,  0,  0, 0x34, 0),
    dbsprite(  1,  0,  0,  0, 0x35, 0),
    dbsprite( -2,  1,  0,  0, 0x42, 0),
    dbsprite( -1,  1,  0,  0, 0x43, 0),
    dbsprite(  0,  1,  0,  0, 0x44, 0),
    dbsprite(  1,  1,  0,  0, 0x45, 0),
    dbsprite( -2,  2,  0,  0, 0x52, 0),
    dbsprite( -1,  2,  0,  0, 0x53, 0),
    dbsprite(  0,  2,  0,  0, 0x54, 0),
    dbsprite(  1,  2,  0,  0, 0x55, 0),
};

static const uint8_t OAMData_IntroSuicune4[] = {
    31,
    dbsprite( -3, -2,  0,  0, 0x11, 0),
    dbsprite( -2, -2,  0,  0, 0x12, 0),
    dbsprite( -1, -2,  0,  0, 0x13, 0),
    dbsprite(  0, -2,  0,  0, 0x14, 0),
    dbsprite(  1, -2,  0,  0, 0x15, 0),
    dbsprite(  2, -2,  0,  0, 0x16, 0),
    dbsprite(  3, -2,  0,  0, 0x17, 0),
    dbsprite( -4, -1,  0,  0, 0x20, 0),
    dbsprite( -3, -1,  0,  0, 0x21, 0),
    dbsprite( -2, -1,  0,  0, 0x22, 0),
    dbsprite( -1, -1,  0,  0, 0x23, 0),
    dbsprite(  0, -1,  0,  0, 0x24, 0),
    dbsprite(  1, -1,  0,  0, 0x25, 0),
    dbsprite(  2, -1,  0,  0, 0x26, 0),
    dbsprite(  3, -1,  0,  0, 0x27, 0),
    dbsprite( -4,  0,  0,  0, 0x30, 0),
    dbsprite( -3,  0,  0,  0, 0x31, 0),
    dbsprite( -2,  0,  0,  0, 0x32, 0),
    dbsprite( -1,  0,  0,  0, 0x33, 0),
    dbsprite(  0,  0,  0,  0, 0x34, 0),
    dbsprite(  1,  0,  0,  0, 0x35, 0),
    dbsprite(  2,  0,  0,  0, 0x36, 0),
    dbsprite( -3,  1,  0,  0, 0x41, 0),
    dbsprite( -2,  1,  0,  0, 0x42, 0),
    dbsprite( -1,  1,  0,  0, 0x43, 0),
    dbsprite(  0,  1,  0,  0, 0x44, 0),
    dbsprite(  1,  1,  0,  0, 0x45, 0),
    dbsprite( -3,  2,  0,  0, 0x51, 0),
    dbsprite( -2,  2,  0,  0, 0x52, 0),
    dbsprite(  0,  2,  0,  0, 0x54, 0),
    dbsprite(  1,  2,  0,  0, 0x55, 0),
};

static const uint8_t OAMData_IntroPichu[] = {
    25,
    dbsprite( -3, -3,  4,  4, 0x00, 1 | VRAM_BANK_1),
    dbsprite( -2, -3,  4,  4, 0x01, 1 | VRAM_BANK_1),
    dbsprite( -1, -3,  4,  4, 0x02, 1 | VRAM_BANK_1),
    dbsprite(  0, -3,  4,  4, 0x03, 1 | VRAM_BANK_1),
    dbsprite(  1, -3,  4,  4, 0x04, 1 | VRAM_BANK_1),
    dbsprite( -3, -2,  4,  4, 0x10, 1 | VRAM_BANK_1),
    dbsprite( -2, -2,  4,  4, 0x11, 1 | VRAM_BANK_1),
    dbsprite( -1, -2,  4,  4, 0x12, 1 | VRAM_BANK_1),
    dbsprite(  0, -2,  4,  4, 0x13, 1 | VRAM_BANK_1),
    dbsprite(  1, -2,  4,  4, 0x14, 1 | VRAM_BANK_1),
    dbsprite( -3, -1,  4,  4, 0x20, 1 | VRAM_BANK_1),
    dbsprite( -2, -1,  4,  4, 0x21, 1 | VRAM_BANK_1),
    dbsprite( -1, -1,  4,  4, 0x22, 1 | VRAM_BANK_1),
    dbsprite(  0, -1,  4,  4, 0x23, 1 | VRAM_BANK_1),
    dbsprite(  1, -1,  4,  4, 0x24, 1 | VRAM_BANK_1),
    dbsprite( -3,  0,  4,  4, 0x30, 1 | VRAM_BANK_1),
    dbsprite( -2,  0,  4,  4, 0x31, 1 | VRAM_BANK_1),
    dbsprite( -1,  0,  4,  4, 0x32, 1 | VRAM_BANK_1),
    dbsprite(  0,  0,  4,  4, 0x33, 1 | VRAM_BANK_1),
    dbsprite(  1,  0,  4,  4, 0x34, 1 | VRAM_BANK_1),
    dbsprite( -3,  1,  4,  4, 0x40, 1 | VRAM_BANK_1),
    dbsprite( -2,  1,  4,  4, 0x41, 1 | VRAM_BANK_1),
    dbsprite( -1,  1,  4,  4, 0x42, 1 | VRAM_BANK_1),
    dbsprite(  0,  1,  4,  4, 0x43, 1 | VRAM_BANK_1),
    dbsprite(  1,  1,  4,  4, 0x44, 1 | VRAM_BANK_1),
};

static const uint8_t OAMData_IntroWooper[] = {
    16,
    dbsprite( -3, -2,  4,  0, 0x00, 2 | VRAM_BANK_1),
    dbsprite( -2, -2,  4,  0, 0x01, 2 | VRAM_BANK_1),
    dbsprite( -1, -2,  4,  0, 0x02, 2 | VRAM_BANK_1),
    dbsprite(  0, -2,  4,  0, 0x03, 2 | VRAM_BANK_1),
    dbsprite( -3, -1,  4,  0, 0x04, 2 | VRAM_BANK_1),
    dbsprite( -2, -1,  4,  0, 0x05, 2 | VRAM_BANK_1),
    dbsprite( -1, -1,  4,  0, 0x06, 2 | VRAM_BANK_1),
    dbsprite(  0, -1,  4,  0, 0x07, 2 | VRAM_BANK_1),
    dbsprite( -3,  0,  4,  0, 0x08, 2 | VRAM_BANK_1),
    dbsprite( -2,  0,  4,  0, 0x09, 2 | VRAM_BANK_1),
    dbsprite( -1,  0,  4,  0, 0x0a, 2 | VRAM_BANK_1),
    dbsprite(  0,  0,  4,  0, 0x0b, 2 | VRAM_BANK_1),
    dbsprite( -3,  1,  4,  0, 0x0c, 2 | VRAM_BANK_1),
    dbsprite( -2,  1,  4,  0, 0x0d, 2 | VRAM_BANK_1),
    dbsprite( -1,  1,  4,  0, 0x0e, 2 | VRAM_BANK_1),
    dbsprite(  0,  1,  4,  0, 0x0f, 2 | VRAM_BANK_1),
};

static const uint8_t OAMData_IntroUnown1[] = {
    1,
    dbsprite( -1, -1,  4,  4, 0x00, 0),
};

static const uint8_t OAMData_IntroUnown2[] = {
    3,
    dbsprite( -1,  0,  0,  0, 0x00, 0),
    dbsprite( -1, -1,  0,  0, 0x01, 0),
    dbsprite(  0, -1,  0,  0, 0x02, 0),
};

static const uint8_t OAMData_IntroUnown3[] = {
    7,
    dbsprite( -2,  1,  0,  0, 0x00, 0),
    dbsprite( -2,  0,  0,  0, 0x01, 0),
    dbsprite( -2, -1,  0,  0, 0x02, 0),
    dbsprite( -1, -1,  0,  0, 0x03, 0),
    dbsprite( -1, -2,  0,  0, 0x04, 0),
    dbsprite(  0, -2,  0,  0, 0x05, 0),
    dbsprite(  1, -2,  0,  0, 0x06, 0),
};

static const uint8_t OAMData_IntroUnownF2_2[] = {
    8,
    dbsprite( -2, -1,  0,  0, 0x00, 0),
    dbsprite( -1, -1,  0,  0, 0x01, 0),
    dbsprite(  0, -1,  0,  0, 0x01, 0 | X_FLIP),
    dbsprite(  1, -1,  0,  0, 0x00, 0 | X_FLIP),
    dbsprite( -2,  0,  0,  0, 0x00, 0 | Y_FLIP),
    dbsprite( -1,  0,  0,  0, 0x01, 0 | Y_FLIP),
    dbsprite(  0,  0,  0,  0, 0x01, 0 | X_FLIP | Y_FLIP),
    dbsprite(  1,  0,  0,  0, 0x00, 0 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_IntroUnownF2_3[] = {
    12,
    dbsprite( -1, -3,  0,  0, 0x00, 0),
    dbsprite( -1, -2,  0,  0, 0x01, 0),
    dbsprite( -1, -1,  0,  0, 0x02, 0),
    dbsprite(  0, -3,  0,  0, 0x00, 0 | X_FLIP),
    dbsprite(  0, -2,  0,  0, 0x01, 0 | X_FLIP),
    dbsprite(  0, -1,  0,  0, 0x02, 0 | X_FLIP),
    dbsprite( -1,  0,  0,  0, 0x02, 0 | Y_FLIP),
    dbsprite( -1,  1,  0,  0, 0x01, 0 | Y_FLIP),
    dbsprite( -1,  2,  0,  0, 0x00, 0 | Y_FLIP),
    dbsprite(  0,  0,  0,  0, 0x02, 0 | X_FLIP | Y_FLIP),
    dbsprite(  0,  1,  0,  0, 0x01, 0 | X_FLIP | Y_FLIP),
    dbsprite(  0,  2,  0,  0, 0x00, 0 | X_FLIP | Y_FLIP),
};

static const uint8_t OAMData_IntroUnownF2_4_5[] = {
    20,
    dbsprite( -2, -3,  0,  4, 0x00, 0),
    dbsprite( -1, -3,  0,  4, 0x01, 0),
    dbsprite(  0, -3,  0,  4, 0x02, 0),
    dbsprite(  1, -3,  0,  4, 0x03, 0),
    dbsprite( -2, -2,  0,  4, 0x04, 0),
    dbsprite( -1, -2,  0,  4, 0x05, 0),
    dbsprite(  0, -2,  0,  4, 0x06, 0),
    dbsprite(  1, -2,  0,  4, 0x07, 0),
    dbsprite( -2, -1,  0,  4, 0x08, 0),
    dbsprite( -1, -1,  0,  4, 0x09, 0),
    dbsprite(  0, -1,  0,  4, 0x0a, 0),
    dbsprite(  1, -1,  0,  4, 0x0b, 0),
    dbsprite( -2,  0,  0,  4, 0x0c, 0),
    dbsprite( -1,  0,  0,  4, 0x0d, 0),
    dbsprite(  0,  0,  0,  4, 0x0e, 0),
    dbsprite(  1,  0,  0,  4, 0x0f, 0),
    dbsprite( -2,  1,  0,  4, 0x10, 0),
    dbsprite( -1,  1,  0,  4, 0x11, 0),
    dbsprite(  0,  1,  0,  4, 0x12, 0),
    dbsprite(  1,  1,  0,  4, 0x13, 0),
};

static const uint8_t OAMData_IntroSuicuneAway[] = {
    20,
    dbsprite(   1,  0,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(   2,  1,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(   3,  2,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(   4,  3,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(   5,  4,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(   6,  3,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(   7,  2,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(   8,  1,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(   9,  0,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(  10,  1,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(  11,  2,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(  12,  3,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(  13,  4,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(  14,  3,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(  15,  2,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite(  16,  1,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite( -15,  0,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite( -14,  1,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite( -13,  2,  0,  0, 0x00, 1 | PRIORITY),
    dbsprite( -12,  3,  0,  0, 0x00, 1 | PRIORITY),
};

static const uint8_t OAMData_Celebi[] = {
    4,
    dbsprite( -1, -1,  0,  0, 0x00, PAL_OW_GREEN),
    dbsprite(  0, -1,  0,  0, 0x01, PAL_OW_GREEN),
    dbsprite( -1,  0,  0,  0, 0x02, PAL_OW_GREEN),
    dbsprite(  0,  0,  0,  0, 0x03, PAL_OW_GREEN),
};

static const uint8_t OAMData_GameFreakLogo1_3[] = {
    9,
    dbsprite( -2, -2,  4,  0, 0x00, 1),
    dbsprite( -1, -2,  4,  0, 0x01, 1),
    dbsprite(  0, -2,  4,  0, 0x02, 1),
    dbsprite( -2, -1,  4,  0, 0x10, 1),
    dbsprite( -1, -1,  4,  0, 0x11, 1),
    dbsprite(  0, -1,  4,  0, 0x12, 1),
    dbsprite( -2,  0,  4,  0, 0x20, 1),
    dbsprite( -1,  0,  4,  0, 0x21, 1),
    dbsprite(  0,  0,  4,  0, 0x22, 1),
};

static const uint8_t OAMData_GameFreakLogo4_11[] = {
    24,
    dbsprite( -2, -5,  4,  0, 0x00, 1),
    dbsprite( -1, -5,  4,  0, 0x01, 1),
    dbsprite(  0, -5,  4,  0, 0x02, 1),
    dbsprite(  1, -5,  4,  0, 0x03, 1),
    dbsprite( -2, -4,  4,  0, 0x10, 1),
    dbsprite( -1, -4,  4,  0, 0x11, 1),
    dbsprite(  0, -4,  4,  0, 0x12, 1),
    dbsprite(  1, -4,  4,  0, 0x13, 1),
    dbsprite( -2, -3,  4,  0, 0x20, 1),
    dbsprite( -1, -3,  4,  0, 0x21, 1),
    dbsprite(  0, -3,  4,  0, 0x22, 1),
    dbsprite(  1, -3,  4,  0, 0x23, 1),
    dbsprite( -2, -2,  4,  0, 0x30, 1),
    dbsprite( -1, -2,  4,  0, 0x31, 1),
    dbsprite(  0, -2,  4,  0, 0x32, 1),
    dbsprite(  1, -2,  4,  0, 0x33, 1),
    dbsprite( -2, -1,  4,  0, 0x40, 1),
    dbsprite( -1, -1,  4,  0, 0x41, 1),
    dbsprite(  0, -1,  4,  0, 0x42, 1),
    dbsprite(  1, -1,  4,  0, 0x43, 1),
    dbsprite( -2,  0,  4,  0, 0x50, 1),
    dbsprite( -1,  0,  4,  0, 0x51, 1),
    dbsprite(  0,  0,  4,  0, 0x52, 1),
    dbsprite(  1,  0,  4,  0, 0x53, 1),
};

const struct OAMData SpriteAnimOAMData[] = {
// entries correspond to SPRITE_ANIM_OAMSET_* constants (see constants/sprite_anim_constants.asm)
    //table_width 3, SpriteAnimOAMData
    // vtile offset, data pointer
    [SPRITE_ANIM_OAMSET_RED_WALK_1]                 = {0x00, OAMData_RedWalk                 }, // SPRITE_ANIM_OAMSET_RED_WALK_1
    [SPRITE_ANIM_OAMSET_RED_WALK_2]                 = {0x04, OAMData_RedWalk                 }, // SPRITE_ANIM_OAMSET_RED_WALK_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_BUBBLE_1]          = {0x4c, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_GS_INTRO_BUBBLE_1
    [SPRITE_ANIM_OAMSET_GS_INTRO_BUBBLE_2]          = {0x5c, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_GS_INTRO_BUBBLE_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_SHELLDER_1]        = {0x6c, OAMData_GSIntroShellder         }, // SPRITE_ANIM_OAMSET_GS_INTRO_SHELLDER_1
    [SPRITE_ANIM_OAMSET_GS_INTRO_SHELLDER_2]        = {0x6e, OAMData_GSIntroShellder         }, // SPRITE_ANIM_OAMSET_GS_INTRO_SHELLDER_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_MAGIKARP_1]        = {0x2d, OAMData_GSIntroMagikarp         }, // SPRITE_ANIM_OAMSET_GS_INTRO_MAGIKARP_1
    [SPRITE_ANIM_OAMSET_GS_INTRO_MAGIKARP_2]        = {0x4d, OAMData_GSIntroMagikarp         }, // SPRITE_ANIM_OAMSET_GS_INTRO_MAGIKARP_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_UNUSED_LAPRAS]     = {0x60, OAMData_GSIntroLapras           }, // SPRITE_ANIM_OAMSET_GS_INTRO_UNUSED_LAPRAS
    [SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_1]          = {0x00, OAMData_GSIntroLapras           }, // SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_1
    [SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_2]          = {0x00, OAMData_GSIntroLapras           }, // SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_3]          = {0x06, OAMData_GSIntroLapras           }, // SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_3
    [SPRITE_ANIM_OAMSET_GS_INTRO_NOTE]              = {0x0c, OAMData_GSIntroNote             }, // SPRITE_ANIM_OAMSET_GS_INTRO_NOTE
    [SPRITE_ANIM_OAMSET_GS_INTRO_INVISIBLE_NOTE]    = {0x0d, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_GS_INTRO_INVISIBLE_NOTE
    [SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_1]      = {0x00, OAMData_GSIntroJigglypuffPikachu}, // SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_1
    [SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_2]      = {0x04, OAMData_GSIntroJigglypuffPikachu}, // SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_3]      = {0x08, OAMData_GSIntroJigglypuffPikachu}, // SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_3
    [SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_1]         = {0x40, OAMData_GSIntroJigglypuffPikachu}, // SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_1
    [SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_2]         = {0x44, OAMData_GSIntroJigglypuffPikachu}, // SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_3]         = {0x48, OAMData_GSIntroJigglypuffPikachu}, // SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_3
    [SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_4]         = {0x4c, OAMData_GSIntroJigglypuffPikachu}, // SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_4
    [SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_1]    = {0x80, OAMData_GSIntroPikachuTail      }, // SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_1
    [SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_2]    = {0x85, OAMData_GSIntroPikachuTail      }, // SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_3]    = {0x8a, OAMData_GSIntroPikachuTail      }, // SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_3
    [SPRITE_ANIM_OAMSET_GS_INTRO_SMALL_FIREBALL]    = {0x00, OAMData_IntroUnownF2_1          }, // SPRITE_ANIM_OAMSET_GS_INTRO_SMALL_FIREBALL
    [SPRITE_ANIM_OAMSET_GS_INTRO_MED_FIREBALL]      = {0x01, OAMData_TradePoofBubble         }, // SPRITE_ANIM_OAMSET_GS_INTRO_MED_FIREBALL
    [SPRITE_ANIM_OAMSET_GS_INTRO_BIG_FIREBALL]      = {0x09, OAMData_GSIntroBigFireball      }, // SPRITE_ANIM_OAMSET_GS_INTRO_BIG_FIREBALL
    [SPRITE_ANIM_OAMSET_GS_INTRO_CHIKORITA]         = {0x10, OAMData_GSIntroStarter          }, // SPRITE_ANIM_OAMSET_GS_INTRO_CHIKORITA
    [SPRITE_ANIM_OAMSET_GS_INTRO_CYNDAQUIL]         = {0x29, OAMData_GSIntroStarter          }, // SPRITE_ANIM_OAMSET_GS_INTRO_CYNDAQUIL
    [SPRITE_ANIM_OAMSET_GS_INTRO_TOTODILE]          = {0x42, OAMData_GSIntroStarter          }, // SPRITE_ANIM_OAMSET_GS_INTRO_TOTODILE
    [SPRITE_ANIM_OAMSET_GS_TITLE_TRAIL_1]           = {0xf8, OAMData_GSTitleTrail            }, // SPRITE_ANIM_OAMSET_GS_TITLE_TRAIL_1
    [SPRITE_ANIM_OAMSET_GS_TITLE_TRAIL_2]           = {0xfa, OAMData_GSTitleTrail            }, // SPRITE_ANIM_OAMSET_GS_TITLE_TRAIL_2
    [SPRITE_ANIM_OAMSET_TEXT_ENTRY_CURSOR]          = {0x00, OAMData_TextEntryCursor         }, // SPRITE_ANIM_OAMSET_TEXT_ENTRY_CURSOR
    [SPRITE_ANIM_OAMSET_TEXT_ENTRY_CURSOR_BIG]      = {0x00, OAMData_TextEntryCursorBig      }, // SPRITE_ANIM_OAMSET_TEXT_ENTRY_CURSOR_BIG
    [SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO]          = {0x00, OAMData_GSGameFreakLogo         }, // SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO
    [SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_STAR]     = {0x0f, OAMData_GSGameFreakLogoStar     }, // SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_STAR
    [SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_1]= {0x11, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_1
    [SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_2]= {0x12, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_2
    [SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_3]= {0x13, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_3
    [SPRITE_ANIM_OAMSET_SLOTS_GOLEM_1]              = {0x00, OAMData_SlotsGolem              }, // SPRITE_ANIM_OAMSET_SLOTS_GOLEM_1
    [SPRITE_ANIM_OAMSET_SLOTS_GOLEM_2]              = {0x08, OAMData_SlotsGolem              }, // SPRITE_ANIM_OAMSET_SLOTS_GOLEM_2
    [SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_1]            = {0x10, OAMData_SlotsChansey1           }, // SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_1
    [SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_2]            = {0x10, OAMData_SlotsChansey2           }, // SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_2
    [SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_3]            = {0x10, OAMData_SlotsChansey3           }, // SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_3
    [SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_4]            = {0x10, OAMData_SlotsChansey4           }, // SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_4
    [SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_5]            = {0x10, OAMData_SlotsChansey5           }, // SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_5
    [SPRITE_ANIM_OAMSET_SLOTS_EGG]                  = {0x3a, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_SLOTS_EGG
    [SPRITE_ANIM_OAMSET_STILL_CURSOR]               = {0x00, OAMData_RedWalk                 }, // SPRITE_ANIM_OAMSET_STILL_CURSOR
    [SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1]          = {0x00, OAMData_TradePokeBall1          }, // SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1
    [SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2]          = {0x02, OAMData_MagnetTrainRed          }, // SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2
    [SPRITE_ANIM_OAMSET_TRADE_POOF_1]               = {0x06, OAMData_TradePoofBubble         }, // SPRITE_ANIM_OAMSET_TRADE_POOF_1
    [SPRITE_ANIM_OAMSET_TRADE_POOF_2]               = {0x0a, OAMData_TradePoofBubble         }, // SPRITE_ANIM_OAMSET_TRADE_POOF_2
    [SPRITE_ANIM_OAMSET_TRADE_POOF_3]               = {0x0e, OAMData_TradePoofBubble         }, // SPRITE_ANIM_OAMSET_TRADE_POOF_3
    [SPRITE_ANIM_OAMSET_TRADE_TUBE_BULGE_1]         = {0x12, OAMData_TradeTubeBulge          }, // SPRITE_ANIM_OAMSET_TRADE_TUBE_BULGE_1
    [SPRITE_ANIM_OAMSET_TRADE_TUBE_BULGE_2]         = {0x13, OAMData_TradeTubeBulge          }, // SPRITE_ANIM_OAMSET_TRADE_TUBE_BULGE_2
    [SPRITE_ANIM_OAMSET_TRADEMON_ICON_1]            = {0x00, OAMData_RedWalk                 }, // SPRITE_ANIM_OAMSET_TRADEMON_ICON_1
    [SPRITE_ANIM_OAMSET_TRADEMON_ICON_2]            = {0x04, OAMData_RedWalk                 }, // SPRITE_ANIM_OAMSET_TRADEMON_ICON_2
    [SPRITE_ANIM_OAMSET_TRADEMON_BUBBLE]            = {0x10, OAMData_TradePoofBubble         }, // SPRITE_ANIM_OAMSET_TRADEMON_BUBBLE
    [SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_1]  = {0x00, OAMData_MagnetTrainRed          }, // SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_1
    [SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_2]  = {0x04, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_2
    [SPRITE_ANIM_OAMSET_RADIO_TUNING_KNOB]          = {0x00, OAMData_RadioTuningKnob         }, // SPRITE_ANIM_OAMSET_RADIO_TUNING_KNOB
    [SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_1]      = {0x00, OAMData_PartyMonWithMail1       }, // SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_1
    [SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_2]      = {0x00, OAMData_PartyMonWithMail2       }, // SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_2
    [SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_1]      = {0x00, OAMData_PartyMonWithItem1       }, // SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_1
    [SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_2]      = {0x00, OAMData_PartyMonWithItem2       }, // SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_2
    [SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_1]         = {0x00, OAMData_MagnetTrainRed          }, // SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_1
    [SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_2]         = {0x04, OAMData_MagnetTrainRed          }, // SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_2
    [SPRITE_ANIM_OAMSET_UNUSED_43]                  = {0x00, OAMData_Unused43_4A             }, // SPRITE_ANIM_OAMSET_UNUSED_43
    [SPRITE_ANIM_OAMSET_UNUSED_44]                  = {0x30, OAMData_Unused43_4A             }, // SPRITE_ANIM_OAMSET_UNUSED_44
    [SPRITE_ANIM_OAMSET_UNUSED_45]                  = {0x03, OAMData_Unused43_4A             }, // SPRITE_ANIM_OAMSET_UNUSED_45
    [SPRITE_ANIM_OAMSET_UNUSED_46]                  = {0x33, OAMData_Unused43_4A             }, // SPRITE_ANIM_OAMSET_UNUSED_46
    [SPRITE_ANIM_OAMSET_UNUSED_47]                  = {0x06, OAMData_Unused43_4A             }, // SPRITE_ANIM_OAMSET_UNUSED_47
    [SPRITE_ANIM_OAMSET_UNUSED_48]                  = {0x36, OAMData_Unused43_4A             }, // SPRITE_ANIM_OAMSET_UNUSED_48
    [SPRITE_ANIM_OAMSET_UNUSED_49]                  = {0x09, OAMData_Unused43_4A             }, // SPRITE_ANIM_OAMSET_UNUSED_49
    [SPRITE_ANIM_OAMSET_UNUSED_4A]                  = {0x39, OAMData_Unused43_4A             }, // SPRITE_ANIM_OAMSET_UNUSED_4A
    [SPRITE_ANIM_OAMSET_UNUSED_4B]                  = {0x0c, OAMData_Unused4B                }, // SPRITE_ANIM_OAMSET_UNUSED_4B
    [SPRITE_ANIM_OAMSET_UNUSED_4C]                  = {0x0c, OAMData_Unused4C                }, // SPRITE_ANIM_OAMSET_UNUSED_4C
    [SPRITE_ANIM_OAMSET_UNUSED_4D]                  = {0x3c, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_UNUSED_4D
    [SPRITE_ANIM_OAMSET_UNUSED_4E]                  = {0x3e, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_UNUSED_4E
    [SPRITE_ANIM_OAMSET_LEAF]                       = {0x00, OAMData_Leaf                    }, // SPRITE_ANIM_OAMSET_LEAF
    [SPRITE_ANIM_OAMSET_TREE_1]                     = {0x00, OAMData_Tree                    }, // SPRITE_ANIM_OAMSET_TREE_1
    [SPRITE_ANIM_OAMSET_CUT_TREE_2]                 = {0x00, OAMData_CutTree2                }, // SPRITE_ANIM_OAMSET_CUT_TREE_2
    [SPRITE_ANIM_OAMSET_CUT_TREE_3]                 = {0x00, OAMData_CutTree3                }, // SPRITE_ANIM_OAMSET_CUT_TREE_3
    [SPRITE_ANIM_OAMSET_CUT_TREE_4]                 = {0x00, OAMData_CutTree4                }, // SPRITE_ANIM_OAMSET_CUT_TREE_4
    [SPRITE_ANIM_OAMSET_EGG_CRACK]                  = {0x00, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_EGG_CRACK
    [SPRITE_ANIM_OAMSET_EGG_HATCH]                  = {0x01, OAMData_1x1_Palette0            }, // SPRITE_ANIM_OAMSET_EGG_HATCH
    [SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_1]     = {0x00, OAMData_GSIntroHoOhLugia1       }, // SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_1
    [SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_2]     = {0x00, OAMData_GSIntroHoOhLugia2       }, // SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_2
    [SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_3]     = {0x00, OAMData_GSIntroHoOhLugia3       }, // SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_3
    [SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_4]     = {0x00, OAMData_GSIntroHoOhLugia4       }, // SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_4
    [SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_5]     = {0x00, OAMData_GSIntroHoOhLugia5       }, // SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_5
    [SPRITE_ANIM_OAMSET_HEADBUTT_TREE_2]            = {0x04, OAMData_Tree                    }, // SPRITE_ANIM_OAMSET_HEADBUTT_TREE_2
    [SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_1]            = {0x00, OAMData_EZChatCursor1           }, // SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_1
    [SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_2]            = {0x00, OAMData_EZChatCursor2           }, // SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_2
    [SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_3]            = {0x00, OAMData_EZChatCursor3           }, // SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_3
    [SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_4]            = {0x00, OAMData_EZChatCursor4           }, // SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_4
    [SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_5]            = {0x00, OAMData_EZChatCursor5           }, // SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_5
    [SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_6]            = {0x00, OAMData_EZChatCursor6           }, // SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_6
    [SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_7]            = {0x00, OAMData_EZChatCursor7           }, // SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_7
    [SPRITE_ANIM_OAMSET_BLUE_WALK_1]                = {0x00, OAMData_BlueWalk                }, // SPRITE_ANIM_OAMSET_BLUE_WALK_1
    [SPRITE_ANIM_OAMSET_BLUE_WALK_2]                = {0x04, OAMData_BlueWalk                }, // SPRITE_ANIM_OAMSET_BLUE_WALK_2
    [SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_1]        = {0x00, OAMData_MagnetTrainBlue         }, // SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_1
    [SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_2]        = {0x04, OAMData_MagnetTrainBlue         }, // SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_2
    [SPRITE_ANIM_OAMSET_MOBILE_TRADE_CABLE_BULGE_1] = {0x20, OAMData_MobileTradeCableBulge   }, // SPRITE_ANIM_OAMSET_MOBILE_TRADE_CABLE_BULGE_1
    [SPRITE_ANIM_OAMSET_MOBILE_TRADE_CABLE_BULGE_2] = {0x21, OAMData_MobileTradeCableBulge   }, // SPRITE_ANIM_OAMSET_MOBILE_TRADE_CABLE_BULGE_2
    [SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_1]        = {0x22, OAMData_MobileTradePing1        }, // SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_1
    [SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_2]        = {0x23, OAMData_MobileTradePing2        }, // SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_2
    [SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_3]        = {0x27, OAMData_MobileTradePing3        }, // SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_3
    [SPRITE_ANIM_OAMSET_MOBILE_TRADE_SENT_PULSE]    = {0x2a, OAMData_MobileTradeSentPulse    }, // SPRITE_ANIM_OAMSET_MOBILE_TRADE_SENT_PULSE
    [SPRITE_ANIM_OAMSET_MOBILE_TRADE_OT_PULSE]      = {0x2a, OAMData_MobileTradeOTPulse      }, // SPRITE_ANIM_OAMSET_MOBILE_TRADE_OT_PULSE
    [SPRITE_ANIM_OAMSET_INTRO_SUICUNE_1]            = {0x00, OAMData_IntroSuicune1           }, // SPRITE_ANIM_OAMSET_INTRO_SUICUNE_1
    [SPRITE_ANIM_OAMSET_INTRO_SUICUNE_2]            = {0x08, OAMData_IntroSuicune2           }, // SPRITE_ANIM_OAMSET_INTRO_SUICUNE_2
    [SPRITE_ANIM_OAMSET_INTRO_SUICUNE_3]            = {0x60, OAMData_IntroSuicune3           }, // SPRITE_ANIM_OAMSET_INTRO_SUICUNE_3
    [SPRITE_ANIM_OAMSET_INTRO_SUICUNE_4]            = {0x68, OAMData_IntroSuicune4           }, // SPRITE_ANIM_OAMSET_INTRO_SUICUNE_4
    [SPRITE_ANIM_OAMSET_INTRO_PICHU_1]              = {0x00, OAMData_IntroPichu              }, // SPRITE_ANIM_OAMSET_INTRO_PICHU_1
    [SPRITE_ANIM_OAMSET_INTRO_PICHU_2]              = {0x05, OAMData_IntroPichu              }, // SPRITE_ANIM_OAMSET_INTRO_PICHU_2
    [SPRITE_ANIM_OAMSET_INTRO_PICHU_3]              = {0x0a, OAMData_IntroPichu              }, // SPRITE_ANIM_OAMSET_INTRO_PICHU_3
    [SPRITE_ANIM_OAMSET_INTRO_WOOPER]               = {0x50, OAMData_IntroWooper             }, // SPRITE_ANIM_OAMSET_INTRO_WOOPER
    [SPRITE_ANIM_OAMSET_INTRO_UNOWN_1]              = {0x00, OAMData_IntroUnown1             }, // SPRITE_ANIM_OAMSET_INTRO_UNOWN_1
    [SPRITE_ANIM_OAMSET_INTRO_UNOWN_2]              = {0x01, OAMData_IntroUnown2             }, // SPRITE_ANIM_OAMSET_INTRO_UNOWN_2
    [SPRITE_ANIM_OAMSET_INTRO_UNOWN_3]              = {0x04, OAMData_IntroUnown3             }, // SPRITE_ANIM_OAMSET_INTRO_UNOWN_3
    [SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_1]          = {0x00, OAMData_IntroUnownF2_1          }, // SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_1
    [SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_2]          = {0x01, OAMData_IntroUnownF2_2          }, // SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_2
    [SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_3]          = {0x03, OAMData_IntroUnownF2_3          }, // SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_3
    [SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_4]          = {0x08, OAMData_IntroUnownF2_4_5        }, // SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_4
    [SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_5]          = {0x1c, OAMData_IntroUnownF2_4_5        }, // SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_5
    [SPRITE_ANIM_OAMSET_INTRO_SUICUNE_AWAY]         = {0x80, OAMData_IntroSuicuneAway        }, // SPRITE_ANIM_OAMSET_INTRO_SUICUNE_AWAY
    [SPRITE_ANIM_OAMSET_CELEBI_1]                   = {0x00, OAMData_Celebi                  }, // SPRITE_ANIM_OAMSET_CELEBI_1
    [SPRITE_ANIM_OAMSET_CELEBI_2]                   = {0x04, OAMData_Celebi                  }, // SPRITE_ANIM_OAMSET_CELEBI_2
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_1]           = {0xd0, OAMData_GameFreakLogo1_3        }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_1
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_2]           = {0xd3, OAMData_GameFreakLogo1_3        }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_2
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_3]           = {0xd6, OAMData_GameFreakLogo1_3        }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_3
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_4]           = {0x6c, OAMData_GameFreakLogo4_11       }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_4
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_5]           = {0x68, OAMData_GameFreakLogo4_11       }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_5
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_6]           = {0x64, OAMData_GameFreakLogo4_11       }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_6
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_7]           = {0x60, OAMData_GameFreakLogo4_11       }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_7
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_8]           = {0x0c, OAMData_GameFreakLogo4_11       }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_8
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_9]           = {0x08, OAMData_GameFreakLogo4_11       }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_9
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_10]          = {0x04, OAMData_GameFreakLogo4_11       }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_10
    [SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_11]          = {0x00, OAMData_GameFreakLogo4_11       }, // SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_11
};
static_assert(lengthof(SpriteAnimOAMData) == NUM_SPRITE_ANIM_OAMSETS, "");