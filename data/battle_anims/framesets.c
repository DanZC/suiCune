#include "../../constants.h"
#include "../../util/variadic_macros.h"
#define frame_value_1(_0) (_0)
#define frame_value_2(_0, _1) (_0 | (1 << (_1 + 1)))
#define frame_value_3(_0, _1, _2) (_0 | (1 << (_1 + 1)) | (1 << (_2 + 1)))
#define frame_value_(...) CPPX_INVOKE( CPPX_CONCAT ( frame_value_, PP_NARG(__VA_ARGS__) ) , (__VA_ARGS__) )
#define frame(_0, ...) frame2(_0, frame_value_(__VA_ARGS__))
#define endanim endanim_command
#define delanim delanim_command
#undef dorestart
#define dorestart dorestart_command

static const uint8_t Frameset_00[] = {
    frame(BATTLEANIMOAMSET_00,  6),
    delanim
};

static const uint8_t Frameset_01[] = {
    frame(BATTLEANIMOAMSET_01,  6),
    delanim
};

static const uint8_t Frameset_02[] = {
    frame(BATTLEANIMOAMSET_02,  6),
    delanim
};

static const uint8_t Frameset_03[] = {
    frame(BATTLEANIMOAMSET_03,  6),
    delanim

};

static const uint8_t Frameset_04[] = {
    frame(BATTLEANIMOAMSET_04,  6),
    delanim

};
static const uint8_t Frameset_05[] = {
    frame(BATTLEANIMOAMSET_05,  6),
    delanim

};
static const uint8_t Frameset_06[] = {
    frame(BATTLEANIMOAMSET_06,  6),
    delanim

};
static const uint8_t Frameset_07[] = {
    frame(BATTLEANIMOAMSET_03,  4),
    frame(BATTLEANIMOAMSET_01,  1),
    frame(BATTLEANIMOAMSET_03,  4),
    frame(BATTLEANIMOAMSET_01,  1),
    frame(BATTLEANIMOAMSET_03,  4),
    frame(BATTLEANIMOAMSET_01,  1),
    frame(BATTLEANIMOAMSET_03,  4),
    frame(BATTLEANIMOAMSET_01,  1),
    delanim

};
static const uint8_t Frameset_3e[] = {
    frame(BATTLEANIMOAMSET_4B,  2),
    frame(BATTLEANIMOAMSET_4C,  2),
    frame(BATTLEANIMOAMSET_4D,  4),
    frame(BATTLEANIMOAMSET_4E,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2),
    delanim

};
static const uint8_t Frameset_3f[] = {
    frame(BATTLEANIMOAMSET_4B,  2, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_4C,  2, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_4D,  4, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_4E,  2, OAM_X_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2, OAM_X_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2, OAM_X_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2, OAM_X_FLIP),
    delanim

};
static const uint8_t Frameset_40[] = {
    frame(BATTLEANIMOAMSET_4B,  2, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_4C,  2, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_4D,  4, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_4E,  2, OAM_X_FLIP, OAM_Y_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2, OAM_X_FLIP, OAM_Y_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2, OAM_X_FLIP, OAM_Y_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_4E,  2, OAM_X_FLIP, OAM_Y_FLIP),
    delanim

};
static const uint8_t Frameset_41[] = {
    frame(BATTLEANIMOAMSET_4B,  1),
    frame(BATTLEANIMOAMSET_4C,  1),
    frame(BATTLEANIMOAMSET_4D,  1),
    frame(BATTLEANIMOAMSET_4F,  1),
    frame(BATTLEANIMOAMSET_50,  1),
    frame(BATTLEANIMOAMSET_51,  1),
    frame(BATTLEANIMOAMSET_52,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2),
    delanim

};
static const uint8_t Frameset_42[] = {
    frame(BATTLEANIMOAMSET_4B,  1, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_4C,  1, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_4D,  1, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_4F,  1, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_50,  1, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_51,  1, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_52,  2, OAM_X_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2, OAM_X_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2, OAM_X_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2, OAM_X_FLIP),
    delanim

};
static const uint8_t Frameset_08[] = {
    frame(BATTLEANIMOAMSET_00,  3),
    frame(BATTLEANIMOAMSET_07,  3),
    frame(BATTLEANIMOAMSET_08,  3),
    frame(BATTLEANIMOAMSET_09,  3),
    delanim

};
static const uint8_t Frameset_09[] = {
    frame(BATTLEANIMOAMSET_0A,  7),
    frame(BATTLEANIMOAMSET_0B,  7),
    frame(BATTLEANIMOAMSET_0A,  7),
    frame(BATTLEANIMOAMSET_0B,  7, OAM_X_FLIP),
    dorestart

};
static const uint8_t Frameset_0a[] = {
    frame(BATTLEANIMOAMSET_0C,  8),
    endanim

};
static const uint8_t Frameset_0b[] = {
    frame(BATTLEANIMOAMSET_0D,  8),
    endanim

};
static const uint8_t Frameset_0c[] = {
    frame(BATTLEANIMOAMSET_0A,  8),
    endanim

};
static const uint8_t Frameset_0d[] = {
    frame(BATTLEANIMOAMSET_0A,  7),
    frame(BATTLEANIMOAMSET_0B,  7),
    frame(BATTLEANIMOAMSET_0A,  7),
    frame(BATTLEANIMOAMSET_0B,  7, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_0A,  7),
    endanim

};
static const uint8_t Frameset_0e[] = {
    frame(BATTLEANIMOAMSET_0A,  8),
    endanim

};
static const uint8_t Frameset_0f[] = {
    frame(BATTLEANIMOAMSET_0A,  4),
    frame(BATTLEANIMOAMSET_0E,  4),
    dorestart

};
static const uint8_t Frameset_10[] = {
    frame(BATTLEANIMOAMSET_0F,  4),
    frame(BATTLEANIMOAMSET_10,  4),
    dorestart

};
static const uint8_t Frameset_11[] = {
    frame(BATTLEANIMOAMSET_10,  4),
    frame(BATTLEANIMOAMSET_0F,  4),
    frame(BATTLEANIMOAMSET_0E,  4),
    frame(BATTLEANIMOAMSET_0A,  4),
    frame(BATTLEANIMOAMSET_0E,  4),
    frame(BATTLEANIMOAMSET_0A,  4),
    frame(BATTLEANIMOAMSET_0E,  4),
    frame(BATTLEANIMOAMSET_0A,  4),
    delanim

};
static const uint8_t Frameset_12[] = {
    frame(BATTLEANIMOAMSET_10,  1),
    frame(BATTLEANIMOAMSET_0F,  1),
    frame(BATTLEANIMOAMSET_12,  1),
    frame(BATTLEANIMOAMSET_11,  1),
    frame(BATTLEANIMOAMSET_12,  1),
    frame(BATTLEANIMOAMSET_0F,  1),
    dorestart

};
static const uint8_t Frameset_13[] = {
    frame(BATTLEANIMOAMSET_10,  3),
    frame(BATTLEANIMOAMSET_0F,  3),
    frame(BATTLEANIMOAMSET_12,  1),
    dowait(1),
    frame(BATTLEANIMOAMSET_12,  1),
    dowait(1),
    frame(BATTLEANIMOAMSET_12,  1),
    dowait(1),
    frame(BATTLEANIMOAMSET_12,  1),
    dowait(1),
    frame(BATTLEANIMOAMSET_12,  3),
    delanim

};
static const uint8_t Frameset_14[] = {
    frame(BATTLEANIMOAMSET_13, 20),
    delanim

};
static const uint8_t Frameset_15[] = {
    frame(BATTLEANIMOAMSET_10,  1),
    frame(BATTLEANIMOAMSET_0F,  1),
    dorestart

};
static const uint8_t Frameset_16[] = {
    frame(BATTLEANIMOAMSET_14,  8),
    endanim

};
static const uint8_t Frameset_17[] = {
    frame(BATTLEANIMOAMSET_17,  4),
    frame(BATTLEANIMOAMSET_16,  8),
    frame(BATTLEANIMOAMSET_15,  8),
    frame(BATTLEANIMOAMSET_16,  8),
    frame(BATTLEANIMOAMSET_17,  4),
    frame(BATTLEANIMOAMSET_17,  4),
    frame(BATTLEANIMOAMSET_16,  8, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_15,  8, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_16,  8, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_17,  4),
    dorestart

};
static const uint8_t Frameset_56[] = {
    frame(BATTLEANIMOAMSET_69,  8),
    endanim

};
static const uint8_t Frameset_57[] = {
    frame(BATTLEANIMOAMSET_69, 32),
    frame(BATTLEANIMOAMSET_6A,  4),
    frame(BATTLEANIMOAMSET_6B,  4),
    frame(BATTLEANIMOAMSET_6D,  4),
    frame(BATTLEANIMOAMSET_6C,  4),
    endanim

};
static const uint8_t Frameset_58[] = {
    frame(BATTLEANIMOAMSET_6C,  8),
    frame(BATTLEANIMOAMSET_6D,  8),
    dorestart

};
static const uint8_t Frameset_18[] = {
    frame(BATTLEANIMOAMSET_18,  4),
    frame(BATTLEANIMOAMSET_19,  4),
    frame(BATTLEANIMOAMSET_1A,  4),
    delanim

};
static const uint8_t Frameset_19[] = {
    frame(BATTLEANIMOAMSET_1B,  8),
    endanim

};
static const uint8_t Frameset_1a[] = {
    frame(BATTLEANIMOAMSET_0F,  8),
    endanim

};
static const uint8_t Frameset_1b[] = {
    frame(BATTLEANIMOAMSET_1C,  8),
    endanim

};
static const uint8_t Frameset_1c[] = {
    frame(BATTLEANIMOAMSET_0A,  8),
    delanim

};
static const uint8_t Frameset_1d[] = {
    frame(BATTLEANIMOAMSET_1D,  8),
    endanim

};
static const uint8_t Frameset_1e[] = {
    frame(BATTLEANIMOAMSET_17,  8),
    endanim

};
static const uint8_t Frameset_1f[] = {
    frame(BATTLEANIMOAMSET_0F,  3),
    frame(BATTLEANIMOAMSET_10,  3),
    frame(BATTLEANIMOAMSET_1E,  3),
    endanim

};
static const uint8_t Frameset_20[] = {
    frame(BATTLEANIMOAMSET_1F, 16),
    frame(BATTLEANIMOAMSET_20,  3),
    delanim

};
static const uint8_t Frameset_21[] = {
    frame(BATTLEANIMOAMSET_20,  8),
    endanim

};
static const uint8_t Frameset_22[] = {
    frame(BATTLEANIMOAMSET_20,  8),
    frame(BATTLEANIMOAMSET_21,  8),
    frame(BATTLEANIMOAMSET_1B,  8),
    frame(BATTLEANIMOAMSET_21,  8),
    dorestart

};
static const uint8_t Frameset_23[] = {
    frame(BATTLEANIMOAMSET_22,  8),
    endanim

};
static const uint8_t Frameset_24[] = {
    frame(BATTLEANIMOAMSET_1B,  8),
    endanim

};
static const uint8_t Frameset_25[] = {
    frame(BATTLEANIMOAMSET_23,  8),
    endanim

};
static const uint8_t Frameset_26[] = {
    frame(BATTLEANIMOAMSET_24,  8),
    endanim

};
static const uint8_t Frameset_27[] = {
    frame(BATTLEANIMOAMSET_25,  8),
    endanim

};
static const uint8_t Frameset_28[] = {
    frame(BATTLEANIMOAMSET_26,  8),
    frame(BATTLEANIMOAMSET_27,  8),
    endanim

};
static const uint8_t Frameset_29[] = {
    frame(BATTLEANIMOAMSET_28,  8),
    frame(BATTLEANIMOAMSET_29,  8),
    delanim

};
static const uint8_t Frameset_2a[] = {
    frame(BATTLEANIMOAMSET_2A,  1),
    frame(BATTLEANIMOAMSET_2B,  1),
    frame(BATTLEANIMOAMSET_2C,  1),
    frame(BATTLEANIMOAMSET_2D,  1),
    frame(BATTLEANIMOAMSET_2E,  1),
    frame(BATTLEANIMOAMSET_2D,  1),
    frame(BATTLEANIMOAMSET_2C,  1),
    frame(BATTLEANIMOAMSET_2B,  1),
    frame(BATTLEANIMOAMSET_2A,  1),
    delanim

};
static const uint8_t Frameset_2b[] = {
    frame(BATTLEANIMOAMSET_14,  1),
    frame(BATTLEANIMOAMSET_15,  1),
    dorestart

};
static const uint8_t Frameset_2c[] = {
    frame(BATTLEANIMOAMSET_2F,  4),
    frame(BATTLEANIMOAMSET_30, 40),
    delanim

};
static const uint8_t Frameset_2d[] = {
    frame(BATTLEANIMOAMSET_31,  8),
    endanim

};
static const uint8_t Frameset_2e[] = {
    frame(BATTLEANIMOAMSET_32, 32),
    frame(BATTLEANIMOAMSET_33, 32),
    frame(BATTLEANIMOAMSET_34, 32),
    frame(BATTLEANIMOAMSET_35, 32), // fallthrough
};

static const uint8_t Frameset_2f[] = {
    dowait(2),
    frame(BATTLEANIMOAMSET_35,  4),
    dowait(2),
    frame(BATTLEANIMOAMSET_35,  4),
    dowait(2),
    frame(BATTLEANIMOAMSET_35,  4),
    dowait(2),
    frame(BATTLEANIMOAMSET_35,  4),
    delanim

};

static const uint8_t Frameset_30[] = {
    frame(BATTLEANIMOAMSET_14,  4),
    frame(BATTLEANIMOAMSET_15,  4),
    dorestart

};

static const uint8_t Frameset_31[] = {
    frame(BATTLEANIMOAMSET_36,  2),
    frame(BATTLEANIMOAMSET_37,  2),
    frame(BATTLEANIMOAMSET_38,  2),
    frame(BATTLEANIMOAMSET_39, 32),
    delanim

};

static const uint8_t Frameset_32[] = {
    frame(BATTLEANIMOAMSET_3A,  2),
    frame(BATTLEANIMOAMSET_3B,  2),
    frame(BATTLEANIMOAMSET_3C,  2),
    frame(BATTLEANIMOAMSET_3D, 32),
    delanim

};

static const uint8_t Frameset_33[] = {
    frame(BATTLEANIMOAMSET_3A,  2, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_3B,  2, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_3C,  2, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_3D, 32, OAM_X_FLIP),
    delanim

};
static const uint8_t Frameset_34[] = {
    frame(BATTLEANIMOAMSET_3E,  8),
    frame(BATTLEANIMOAMSET_3F,  8),
    frame(BATTLEANIMOAMSET_40,  8),
    endanim

};

static const uint8_t Frameset_35[] = {
    frame(BATTLEANIMOAMSET_40,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_40,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_41,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_41,  2),
    dowait(2),
    dorestart

};
static const uint8_t Frameset_36[] = {
    frame(BATTLEANIMOAMSET_42,  2),
    frame(BATTLEANIMOAMSET_43,  2),
    frame(BATTLEANIMOAMSET_44,  2),
    frame(BATTLEANIMOAMSET_45,  2),
    dorestart

};
static const uint8_t Frameset_37[] = {
    frame(BATTLEANIMOAMSET_19,  2),
    dowait(2),
    dorestart

};
static const uint8_t Frameset_38[] = {
    frame(BATTLEANIMOAMSET_46,  4),
    frame(BATTLEANIMOAMSET_47,  4),
    dorestart

};
static const uint8_t Frameset_39[] = {
    frame(BATTLEANIMOAMSET_18,  2),
    dowait(2),
    dorestart

};
static const uint8_t Frameset_3a[] = {
    frame(BATTLEANIMOAMSET_48,  8),
    endanim

};
static const uint8_t Frameset_3b[] = {
    frame(BATTLEANIMOAMSET_48,  8, OAM_X_FLIP),
    endanim

};
static const uint8_t Frameset_3c[] = {
    frame(BATTLEANIMOAMSET_49,  8),
    endanim

};
static const uint8_t Frameset_3d[] = {
    frame(BATTLEANIMOAMSET_4A,  8),
    endanim

};
static const uint8_t Frameset_43[] = {
    frame(BATTLEANIMOAMSET_20, 16),
    frame(BATTLEANIMOAMSET_1F, 16),
    frame(BATTLEANIMOAMSET_1E, 16),
    endanim

};
static const uint8_t Frameset_4c[] = {
    frame(BATTLEANIMOAMSET_20,  8),
    frame(BATTLEANIMOAMSET_1F,  8),
    frame(BATTLEANIMOAMSET_1E,  8),
    endanim

};
static const uint8_t Frameset_44[] = {
    dowait(20),
    frame(BATTLEANIMOAMSET_55, 40),
    frame(BATTLEANIMOAMSET_54, 40),
    frame(BATTLEANIMOAMSET_53, 20),
    dowait(4),
    frame(BATTLEANIMOAMSET_53,  4),
    dowait(4),
    frame(BATTLEANIMOAMSET_53,  4),
    dowait(4),
    frame(BATTLEANIMOAMSET_53,  4),
    delanim

};
static const uint8_t Frameset_7e[] = {
    frame(BATTLEANIMOAMSET_1E,  8),
    frame(BATTLEANIMOAMSET_1F,  8),
    frame(BATTLEANIMOAMSET_20,  8),
    delanim

};
static const uint8_t Frameset_45[] = {
    dowait(0),
    frame(BATTLEANIMOAMSET_14,  0),
    frame(BATTLEANIMOAMSET_15,  0),
    frame(BATTLEANIMOAMSET_14,  0, OAM_X_FLIP),
    dowait(0),
    frame(BATTLEANIMOAMSET_16,  0, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_15,  0),
    frame(BATTLEANIMOAMSET_16,  0),
    dorestart

};
static const uint8_t Frameset_46[] = {
    frame(BATTLEANIMOAMSET_56,  2),
    frame(BATTLEANIMOAMSET_57,  4),
    delanim

};
static const uint8_t Frameset_47[] = {
    frame(BATTLEANIMOAMSET_56,  2, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_57,  4, OAM_X_FLIP, OAM_Y_FLIP),
    delanim

};
static const uint8_t Frameset_48[] = {
    frame(BATTLEANIMOAMSET_56,  1),
    frame(BATTLEANIMOAMSET_57,  1),
    frame(BATTLEANIMOAMSET_58,  1),
    frame(BATTLEANIMOAMSET_57,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_58,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_57,  2),
    delanim

};
static const uint8_t Frameset_49[] = {
    frame(BATTLEANIMOAMSET_56,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_57,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_58,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_57,  1),
    frame(BATTLEANIMOAMSET_58,  1),
    frame(BATTLEANIMOAMSET_57,  2, OAM_X_FLIP, OAM_Y_FLIP),
    delanim

};
static const uint8_t Frameset_4a[] = {
    frame(BATTLEANIMOAMSET_57,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_58,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_57,  1),
    frame(BATTLEANIMOAMSET_58,  1),
    dorestart

};
static const uint8_t Frameset_4b[] = {
    frame(BATTLEANIMOAMSET_59,  1),
    frame(BATTLEANIMOAMSET_5A,  1),
    frame(BATTLEANIMOAMSET_5B,  1),
    frame(BATTLEANIMOAMSET_5C,  2),
    delanim

};
static const uint8_t Frameset_4d[] = {
    frame(BATTLEANIMOAMSET_0A, 10),
    frame(BATTLEANIMOAMSET_0B,  3, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_5D,  3, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_0B,  3, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_0A,  2, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_0B,  1, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_5D,  1),
    frame(BATTLEANIMOAMSET_0B,  1),
    dorestart

};
static const uint8_t Frameset_4e[] = {
    frame(BATTLEANIMOAMSET_0A,  3),
    frame(BATTLEANIMOAMSET_0B,  7, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_0A,  7),
    frame(BATTLEANIMOAMSET_0B,  7),
    frame(BATTLEANIMOAMSET_0A,  3),
    dorestart

};
static const uint8_t Frameset_4f[] = {
    frame(BATTLEANIMOAMSET_5E, 32),
    frame(BATTLEANIMOAMSET_5E, 32),
    delanim

};
static const uint8_t Frameset_50[] = {
    frame(BATTLEANIMOAMSET_5F, 32),
    frame(BATTLEANIMOAMSET_5F, 32),
    delanim

};
static const uint8_t Frameset_51[] = {
    frame(BATTLEANIMOAMSET_60,  8),
    endanim

};
static const uint8_t Frameset_52[] = {
    frame(BATTLEANIMOAMSET_61,  1),
    frame(BATTLEANIMOAMSET_62,  1),
    frame(BATTLEANIMOAMSET_63,  1),
    endanim

};
static const uint8_t Frameset_53[] = {
    frame(BATTLEANIMOAMSET_63,  7),
    frame(BATTLEANIMOAMSET_64,  7),
    dorestart

};
static const uint8_t Frameset_54[] = {
    frame(BATTLEANIMOAMSET_65,  1),
    frame(BATTLEANIMOAMSET_66,  1),
    frame(BATTLEANIMOAMSET_67,  1),
    endanim

};
static const uint8_t Frameset_55[] = {
    frame(BATTLEANIMOAMSET_67,  7),
    frame(BATTLEANIMOAMSET_68,  7),
    dorestart

};
static const uint8_t Frameset_59[] = {
    frame(BATTLEANIMOAMSET_6E,  8),
    endanim

};
static const uint8_t Frameset_5a[] = {
    frame(BATTLEANIMOAMSET_6F,  8),
    endanim

};
static const uint8_t Frameset_5b[] = {
    frame(BATTLEANIMOAMSET_6E,  8, OAM_Y_FLIP),
    endanim

};
static const uint8_t Frameset_5c[] = {
    frame(BATTLEANIMOAMSET_18,  4),
    frame(BATTLEANIMOAMSET_70,  4),
    frame(BATTLEANIMOAMSET_71,  4),
    frame(BATTLEANIMOAMSET_72,  4),
    frame(BATTLEANIMOAMSET_73,  4),
    delanim

};
static const uint8_t Frameset_5d[] = {
    frame(BATTLEANIMOAMSET_74,  4),
    frame(BATTLEANIMOAMSET_75,  4),
    dorestart

};
static const uint8_t Frameset_5e[] = {
    frame(BATTLEANIMOAMSET_14,  8),
    endanim

};
static const uint8_t Frameset_7a[] = {
    frame(BATTLEANIMOAMSET_74,  3),
    frame(BATTLEANIMOAMSET_14,  3),
    frame(BATTLEANIMOAMSET_15,  3),
    frame(BATTLEANIMOAMSET_14,  3),
    frame(BATTLEANIMOAMSET_15,  3),
    delanim

};
static const uint8_t Frameset_af[] = {
    frame(BATTLEANIMOAMSET_14,  0),
    frame(BATTLEANIMOAMSET_15,  0),
    frame(BATTLEANIMOAMSET_14,  0),
    frame(BATTLEANIMOAMSET_15,  0),
    frame(BATTLEANIMOAMSET_74, 12),
    delanim

};
static const uint8_t Frameset_5f[] = {
    frame(BATTLEANIMOAMSET_76,  8),
    endanim

};
static const uint8_t Frameset_60[] = {
    frame(BATTLEANIMOAMSET_77,  1),
    frame(BATTLEANIMOAMSET_78,  1),
    frame(BATTLEANIMOAMSET_79,  1),
    frame(BATTLEANIMOAMSET_7A,  1),
    frame(BATTLEANIMOAMSET_7B,  1),
    frame(BATTLEANIMOAMSET_7C,  1),
    frame(BATTLEANIMOAMSET_7D,  1),
    frame(BATTLEANIMOAMSET_7C,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_7B,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_7A,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_79,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_78,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_77,  1, OAM_X_FLIP, OAM_Y_FLIP),
    delanim

};
static const uint8_t Frameset_61[] = {
    frame(BATTLEANIMOAMSET_1B,  4),
    frame(BATTLEANIMOAMSET_7E,  4),
    dorestart

};
static const uint8_t Frameset_62[] = {
    frame(BATTLEANIMOAMSET_1B,  4, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_7E,  4, OAM_X_FLIP),
    dorestart

};
static const uint8_t Frameset_63[] = {
    frame(BATTLEANIMOAMSET_7F,  8),
    endanim

};
static const uint8_t Frameset_64[] = {
    frame(BATTLEANIMOAMSET_25,  8),
    endanim

};
static const uint8_t Frameset_65[] = {
    frame(BATTLEANIMOAMSET_80,  8),
    endanim

};
static const uint8_t Frameset_66[] = {
    frame(BATTLEANIMOAMSET_83,  7),
    frame(BATTLEANIMOAMSET_82,  7),
    frame(BATTLEANIMOAMSET_81,  7),
    frame(BATTLEANIMOAMSET_82,  7),
    frame(BATTLEANIMOAMSET_83,  7),
    frame(BATTLEANIMOAMSET_82,  7),
    frame(BATTLEANIMOAMSET_81,  7),
    delanim

};
static const uint8_t Frameset_67[] = {
    frame(BATTLEANIMOAMSET_1B, 16),
    delanim

};
static const uint8_t Frameset_68[] = {
    dowait(15),
    frame(BATTLEANIMOAMSET_84, 15),
    frame(BATTLEANIMOAMSET_85, 15),
    frame(BATTLEANIMOAMSET_29, 15),
    frame(BATTLEANIMOAMSET_28, 15),
    frame(BATTLEANIMOAMSET_86, 32),
    delanim

};
static const uint8_t Frameset_69[] = {
    frame(BATTLEANIMOAMSET_1B,  3),
    frame(BATTLEANIMOAMSET_87,  3),
    frame(BATTLEANIMOAMSET_88,  3),
    frame(BATTLEANIMOAMSET_89,  3),
    delanim

};
static const uint8_t Frameset_6a[] = {
    frame(BATTLEANIMOAMSET_8A,  2),
    frame(BATTLEANIMOAMSET_8B,  2),
    frame(BATTLEANIMOAMSET_8C,  2),
    frame(BATTLEANIMOAMSET_8D,  2),
    delanim

};
static const uint8_t Frameset_6b[] = {
    frame(BATTLEANIMOAMSET_61,  2),
    frame(BATTLEANIMOAMSET_62,  2),
    frame(BATTLEANIMOAMSET_63,  2),
    endanim

};
static const uint8_t Frameset_6c[] = {
    frame(BATTLEANIMOAMSET_65,  2),
    frame(BATTLEANIMOAMSET_66,  2),
    frame(BATTLEANIMOAMSET_67,  2),
    endanim

};
static const uint8_t Frameset_6d[] = {
    frame(BATTLEANIMOAMSET_8E,  8),
    endanim

};
static const uint8_t Frameset_6e[] = {
    frame(BATTLEANIMOAMSET_8E,  8, OAM_X_FLIP),
    endanim

};
static const uint8_t Frameset_6f[] = {
    frame(BATTLEANIMOAMSET_8F, 16),
    frame(BATTLEANIMOAMSET_90, 16),
    dorestart

};
static const uint8_t Frameset_70[] = {
    frame(BATTLEANIMOAMSET_91, 16),
    frame(BATTLEANIMOAMSET_92, 16),
    dorestart

};
static const uint8_t Frameset_71[] = {
    frame(BATTLEANIMOAMSET_93,  8),
    endanim

};
static const uint8_t Frameset_72[] = {
    frame(BATTLEANIMOAMSET_1E,  8),
    endanim

};
static const uint8_t Frameset_73[] = {
    frame(BATTLEANIMOAMSET_1B,  7),
    frame(BATTLEANIMOAMSET_94,  7),
    dorestart

};
static const uint8_t Frameset_74[] = {
    frame(BATTLEANIMOAMSET_95,  8),
    endanim

};
static const uint8_t Frameset_75[] = {
    frame(BATTLEANIMOAMSET_96,  8),
    endanim

};
static const uint8_t Frameset_76[] = {
    frame(BATTLEANIMOAMSET_95,  8),
    endanim

};
static const uint8_t Frameset_77[] = {
    frame(BATTLEANIMOAMSET_97,  1),
    frame(BATTLEANIMOAMSET_97,  1, OAM_X_FLIP),
    dorestart

};
static const uint8_t Frameset_78[] = {
    frame(BATTLEANIMOAMSET_98,  8),
    endanim

};
static const uint8_t Frameset_79[] = {
    frame(BATTLEANIMOAMSET_99, 32),
    frame(BATTLEANIMOAMSET_99, 32),
    frame(BATTLEANIMOAMSET_99, 32),
    frame(BATTLEANIMOAMSET_99, 32),
    frame(BATTLEANIMOAMSET_99, 32),
    frame(BATTLEANIMOAMSET_9A,  8),
    endanim

};
static const uint8_t Frameset_7b[] = {
    frame(BATTLEANIMOAMSET_9B,  8),
    endanim

};
static const uint8_t Frameset_7c[] = {
    frame(BATTLEANIMOAMSET_9C,  2),
    frame(BATTLEANIMOAMSET_9D,  2),
    frame(BATTLEANIMOAMSET_9E,  8),
    dowait(2),
    frame(BATTLEANIMOAMSET_9E,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_9E,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_9E,  2),
    delanim

};
static const uint8_t Frameset_7d[] = {
    frame(BATTLEANIMOAMSET_9F,  8),
    endanim

};
static const uint8_t Frameset_7f[] = {
    frame(BATTLEANIMOAMSET_0F,  8),
    endanim

};
static const uint8_t Frameset_80[] = {
    frame(BATTLEANIMOAMSET_6B, 24),
    delanim

};

static const uint8_t Frameset_81[] = {
    frame(BATTLEANIMOAMSET_A0,  1), // fallthrough
};
static const uint8_t Frameset_82[] = {
    frame(BATTLEANIMOAMSET_A1,  1), // fallthrough
};
static const uint8_t Frameset_83[] = {
    frame(BATTLEANIMOAMSET_A2,  1),
    delanim
};

static const uint8_t Frameset_84[] = {
    frame(BATTLEANIMOAMSET_A3,  8),
    endanim
};

static const uint8_t Frameset_85[] = {
    frame(BATTLEANIMOAMSET_A4,  4),
    frame(BATTLEANIMOAMSET_A5,  4),
    frame(BATTLEANIMOAMSET_A6,  4),
    frame(BATTLEANIMOAMSET_A7,  4),
    frame(BATTLEANIMOAMSET_A6,  4, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_A5,  4, OAM_X_FLIP),
    dorestart

};
static const uint8_t Frameset_86[] = {
    frame(BATTLEANIMOAMSET_A8,  4),
    frame(BATTLEANIMOAMSET_A9,  4),
    frame(BATTLEANIMOAMSET_AA,  4),
    frame(BATTLEANIMOAMSET_AB,  4),
    frame(BATTLEANIMOAMSET_AA,  4, OAM_X_FLIP),
    frame(BATTLEANIMOAMSET_A9,  4, OAM_X_FLIP),
    dorestart

};
static const uint8_t Frameset_87[] = {
    frame(BATTLEANIMOAMSET_1B,  8),
    endanim

};
static const uint8_t Frameset_88[] = {
    frame(BATTLEANIMOAMSET_AC,  8),
    endanim

};
static const uint8_t Frameset_89[] = {
    frame(BATTLEANIMOAMSET_AD,  8),
    endanim

};
static const uint8_t Frameset_8a[] = {
    frame(BATTLEANIMOAMSET_AE,  8),
    endanim

};
static const uint8_t Frameset_8b[] = {
    frame(BATTLEANIMOAMSET_AF,  8),
    endanim

};
static const uint8_t Frameset_8c[] = {
    frame(BATTLEANIMOAMSET_B0, 32),
    delanim

};
static const uint8_t Frameset_8d[] = {
    frame(BATTLEANIMOAMSET_B1,  7),
    frame(BATTLEANIMOAMSET_B1,  7, OAM_X_FLIP),
    dorestart

};
static const uint8_t Frameset_8e[] = {
    frame(BATTLEANIMOAMSET_B2,  8),
    endanim

};
static const uint8_t Frameset_8f[] = {
    frame(BATTLEANIMOAMSET_B3,  8),
    endanim

};
static const uint8_t Frameset_90[] = {
    frame(BATTLEANIMOAMSET_B3,  8, OAM_X_FLIP),
    endanim

};
static const uint8_t Frameset_91[] = {
    frame(BATTLEANIMOAMSET_B3,  8, OAM_Y_FLIP),
    endanim

};
static const uint8_t Frameset_92[] = {
    frame(BATTLEANIMOAMSET_B3,  8, OAM_X_FLIP, OAM_Y_FLIP),
    endanim

};
static const uint8_t Frameset_93[] = {
    frame(BATTLEANIMOAMSET_B5,  8),
    endanim

};
static const uint8_t Frameset_94[] = {
    frame(BATTLEANIMOAMSET_B5,  8, OAM_X_FLIP),
    endanim

};
static const uint8_t Frameset_95[] = {
    frame(BATTLEANIMOAMSET_B5,  8, OAM_Y_FLIP),
    endanim

};
static const uint8_t Frameset_96[] = {
    frame(BATTLEANIMOAMSET_B5,  8, OAM_X_FLIP, OAM_Y_FLIP),
    endanim

};
static const uint8_t Frameset_97[] = {
    frame(BATTLEANIMOAMSET_B4,  8),
    endanim

};
static const uint8_t Frameset_98[] = {
    frame(BATTLEANIMOAMSET_6B,  8),
    endanim

};
static const uint8_t Frameset_99[] = {
    frame(BATTLEANIMOAMSET_B6,  8),
    endanim

};
static const uint8_t Frameset_9a[] = {
    frame(BATTLEANIMOAMSET_B7, 32),
    endanim

};
static const uint8_t Frameset_9b[] = {
    frame(BATTLEANIMOAMSET_1B, 32),
    endanim

};
static const uint8_t Frameset_9c[] = {
    frame(BATTLEANIMOAMSET_B8, 32),
    endanim

};
static const uint8_t Frameset_9d[] = {
    frame(BATTLEANIMOAMSET_B8, 32, OAM_X_FLIP),
    endanim

};
static const uint8_t Frameset_9e[] = {
    frame(BATTLEANIMOAMSET_B9, 32),
    endanim

};
static const uint8_t Frameset_9f[] = {
    frame(BATTLEANIMOAMSET_BA, 32),
    endanim

};
static const uint8_t Frameset_a0[] = {
    frame(BATTLEANIMOAMSET_BB, 32, OAM_X_FLIP),
    endanim

};
static const uint8_t Frameset_a1[] = {
    frame(BATTLEANIMOAMSET_BB, 32),
    endanim

};
static const uint8_t Frameset_a2[] = {
    frame(BATTLEANIMOAMSET_BC, 32),
    endanim

};
static const uint8_t Frameset_a3[] = {
    frame(BATTLEANIMOAMSET_BD, 11),
    frame(BATTLEANIMOAMSET_BE, 11),
    frame(BATTLEANIMOAMSET_1B, 11),
    delanim

};
static const uint8_t Frameset_a4[] = {
    frame(BATTLEANIMOAMSET_BF,  4),
    frame(BATTLEANIMOAMSET_C0,  4),
    frame(BATTLEANIMOAMSET_C1,  4),
    delanim

};
static const uint8_t Frameset_a5[] = {
    frame(BATTLEANIMOAMSET_C2, 32),
    frame(BATTLEANIMOAMSET_C2, 32),
    delanim

};
static const uint8_t Frameset_a6[] = {
    frame(BATTLEANIMOAMSET_4B,  2),
    frame(BATTLEANIMOAMSET_4C,  2),
    frame(BATTLEANIMOAMSET_4D, 32),
    frame(BATTLEANIMOAMSET_4D, 32),
    frame(BATTLEANIMOAMSET_4D, 32),
    frame(BATTLEANIMOAMSET_4F,  1),
    frame(BATTLEANIMOAMSET_50,  1),
    frame(BATTLEANIMOAMSET_51,  1),
    frame(BATTLEANIMOAMSET_52,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2),
    delanim

};
static const uint8_t Frameset_a7[] = {
    frame(BATTLEANIMOAMSET_4B,  2, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_4C,  2, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_4D, 32, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_4D, 32, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_4D, 32, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_4F,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_50,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_51,  1, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_52,  2, OAM_X_FLIP, OAM_Y_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2, OAM_X_FLIP, OAM_Y_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2, OAM_X_FLIP, OAM_Y_FLIP),
    dowait(2),
    frame(BATTLEANIMOAMSET_52,  2, OAM_X_FLIP, OAM_Y_FLIP),
    delanim

};
static const uint8_t Frameset_a8[] = {
    frame(BATTLEANIMOAMSET_C3,  1),
    frame(BATTLEANIMOAMSET_C3,  1, OAM_X_FLIP, OAM_Y_FLIP),
    dorestart

};
static const uint8_t Frameset_a9[] = {
    frame(BATTLEANIMOAMSET_C4, 32),
    endanim

};
static const uint8_t Frameset_aa[] = {
    frame(BATTLEANIMOAMSET_C5,  4),
    frame(BATTLEANIMOAMSET_C6,  4),
    frame(BATTLEANIMOAMSET_C7,  4),
    delanim

};
static const uint8_t Frameset_ab[] = {
    frame(BATTLEANIMOAMSET_C8,  1),
    frame(BATTLEANIMOAMSET_C8,  1, OAM_X_FLIP),
    dorestart

};
static const uint8_t Frameset_ac[] = {
    frame(BATTLEANIMOAMSET_C9,  3),
    frame(BATTLEANIMOAMSET_05,  3),
    delanim

};
static const uint8_t Frameset_ad[] = {
    frame(BATTLEANIMOAMSET_CA, 32),
    frame(BATTLEANIMOAMSET_CB,  3),
    frame(BATTLEANIMOAMSET_CA,  3),
    frame(BATTLEANIMOAMSET_CB,  3),
    dorestart

};
static const uint8_t Frameset_ae[] = {
    frame(BATTLEANIMOAMSET_03, 32, OAM_Y_FLIP),
    endanim

};
static const uint8_t Frameset_b0[] = {
    frame(BATTLEANIMOAMSET_CC, 32),
    endanim

};
static const uint8_t Frameset_b1[] = {
    frame(BATTLEANIMOAMSET_7F,  2),
    frame(BATTLEANIMOAMSET_25,  2),
    frame(BATTLEANIMOAMSET_80,  2),
    frame(BATTLEANIMOAMSET_25,  2),
    dorestart

};
static const uint8_t Frameset_b2[] = {
    frame(BATTLEANIMOAMSET_CD,  4),
    frame(BATTLEANIMOAMSET_CE,  4),
    frame(BATTLEANIMOAMSET_CD,  4, OAM_X_FLIP, OAM_Y_FLIP),
    frame(BATTLEANIMOAMSET_CE,  4, OAM_X_FLIP, OAM_Y_FLIP),
    dorestart

};
static const uint8_t Frameset_b3[] = {
    frame(BATTLEANIMOAMSET_CF,  4),
    frame(BATTLEANIMOAMSET_D0,  4),
    frame(BATTLEANIMOAMSET_D1,  4),
    frame(BATTLEANIMOAMSET_D2,  4),
    delanim

};
static const uint8_t Frameset_b4[] = {
    frame(BATTLEANIMOAMSET_D3, 32),
    endanim

};
static const uint8_t Frameset_b5[] = {
    frame(BATTLEANIMOAMSET_D4,  8),
    endanim

};
static const uint8_t Frameset_b6[] = {
    frame(BATTLEANIMOAMSET_D5,  8),
    endanim

};
static const uint8_t Frameset_b7[] = {
    frame(BATTLEANIMOAMSET_D6,  8),
    endanim

};
static const uint8_t Frameset_b8[] = {
    frame(BATTLEANIMOAMSET_D7,  8),
    endanim
};

const uint8_t* BattleAnimFrameData[] = {
// entries correspond to BATTLEANIMFRAMESET_* constants
// table_width 2, BattleAnimFrameData
    [BATTLEANIMFRAMESET_00] = Frameset_00,
    [BATTLEANIMFRAMESET_01] = Frameset_01,
    [BATTLEANIMFRAMESET_02] = Frameset_02,
    [BATTLEANIMFRAMESET_03] = Frameset_03,
    [BATTLEANIMFRAMESET_04] = Frameset_04,
    [BATTLEANIMFRAMESET_05] = Frameset_05,
    [BATTLEANIMFRAMESET_06] = Frameset_06,
    [BATTLEANIMFRAMESET_07] = Frameset_07,
    [BATTLEANIMFRAMESET_08] = Frameset_08,
    [BATTLEANIMFRAMESET_09] = Frameset_09,
    [BATTLEANIMFRAMESET_0A] = Frameset_0a,
    [BATTLEANIMFRAMESET_0B] = Frameset_0b,
    [BATTLEANIMFRAMESET_0C] = Frameset_0c,
    [BATTLEANIMFRAMESET_0D] = Frameset_0d,
    [BATTLEANIMFRAMESET_0E] = Frameset_0e,
    [BATTLEANIMFRAMESET_0F] = Frameset_0f,
    [BATTLEANIMFRAMESET_10] = Frameset_10,
    [BATTLEANIMFRAMESET_11] = Frameset_11,
    [BATTLEANIMFRAMESET_12] = Frameset_12,
    [BATTLEANIMFRAMESET_13] = Frameset_13,
    [BATTLEANIMFRAMESET_14] = Frameset_14,
    [BATTLEANIMFRAMESET_15] = Frameset_15,
    [BATTLEANIMFRAMESET_16] = Frameset_16,
    [BATTLEANIMFRAMESET_17] = Frameset_17,
    [BATTLEANIMFRAMESET_18] = Frameset_18,
    [BATTLEANIMFRAMESET_19] = Frameset_19,
    [BATTLEANIMFRAMESET_1A] = Frameset_1a,
    [BATTLEANIMFRAMESET_1B] = Frameset_1b,
    [BATTLEANIMFRAMESET_1C] = Frameset_1c,
    [BATTLEANIMFRAMESET_1D] = Frameset_1d,
    [BATTLEANIMFRAMESET_1E] = Frameset_1e,
    [BATTLEANIMFRAMESET_1F] = Frameset_1f,
    [BATTLEANIMFRAMESET_20] = Frameset_20,
    [BATTLEANIMFRAMESET_21] = Frameset_21,
    [BATTLEANIMFRAMESET_22] = Frameset_22,
    [BATTLEANIMFRAMESET_23] = Frameset_23,
    [BATTLEANIMFRAMESET_24] = Frameset_24,
    [BATTLEANIMFRAMESET_25] = Frameset_25,
    [BATTLEANIMFRAMESET_26] = Frameset_26,
    [BATTLEANIMFRAMESET_27] = Frameset_27,
    [BATTLEANIMFRAMESET_28] = Frameset_28,
    [BATTLEANIMFRAMESET_29] = Frameset_29,
    [BATTLEANIMFRAMESET_2A] = Frameset_2a,
    [BATTLEANIMFRAMESET_2B] = Frameset_2b,
    [BATTLEANIMFRAMESET_2C] = Frameset_2c,
    [BATTLEANIMFRAMESET_2D] = Frameset_2d,
    [BATTLEANIMFRAMESET_2E] = Frameset_2e,
    [BATTLEANIMFRAMESET_2F] = Frameset_2f,
    [BATTLEANIMFRAMESET_30] = Frameset_30,
    [BATTLEANIMFRAMESET_31] = Frameset_31,
    [BATTLEANIMFRAMESET_32] = Frameset_32,
    [BATTLEANIMFRAMESET_33] = Frameset_33,
    [BATTLEANIMFRAMESET_34] = Frameset_34,
    [BATTLEANIMFRAMESET_35] = Frameset_35,
    [BATTLEANIMFRAMESET_36] = Frameset_36,
    [BATTLEANIMFRAMESET_37] = Frameset_37,
    [BATTLEANIMFRAMESET_38] = Frameset_38,
    [BATTLEANIMFRAMESET_39] = Frameset_39,
    [BATTLEANIMFRAMESET_3A] = Frameset_3a,
    [BATTLEANIMFRAMESET_3B] = Frameset_3b,
    [BATTLEANIMFRAMESET_3C] = Frameset_3c,
    [BATTLEANIMFRAMESET_3D] = Frameset_3d,
    [BATTLEANIMFRAMESET_3E] = Frameset_3e,
    [BATTLEANIMFRAMESET_3F] = Frameset_3f,
    [BATTLEANIMFRAMESET_40] = Frameset_40,
    [BATTLEANIMFRAMESET_41] = Frameset_41,
    [BATTLEANIMFRAMESET_42] = Frameset_42,
    [BATTLEANIMFRAMESET_43] = Frameset_43,
    [BATTLEANIMFRAMESET_44] = Frameset_44,
    [BATTLEANIMFRAMESET_45] = Frameset_45,
    [BATTLEANIMFRAMESET_46] = Frameset_46,
    [BATTLEANIMFRAMESET_47] = Frameset_47,
    [BATTLEANIMFRAMESET_48] = Frameset_48,
    [BATTLEANIMFRAMESET_49] = Frameset_49,
    [BATTLEANIMFRAMESET_4A] = Frameset_4a,
    [BATTLEANIMFRAMESET_4B] = Frameset_4b,
    [BATTLEANIMFRAMESET_4C] = Frameset_4c,
    [BATTLEANIMFRAMESET_4D] = Frameset_4d,
    [BATTLEANIMFRAMESET_4E] = Frameset_4e,
    [BATTLEANIMFRAMESET_4F] = Frameset_4f,
    [BATTLEANIMFRAMESET_50] = Frameset_50,
    [BATTLEANIMFRAMESET_51] = Frameset_51,
    [BATTLEANIMFRAMESET_52] = Frameset_52,
    [BATTLEANIMFRAMESET_53] = Frameset_53,
    [BATTLEANIMFRAMESET_54] = Frameset_54,
    [BATTLEANIMFRAMESET_55] = Frameset_55,
    [BATTLEANIMFRAMESET_56] = Frameset_56,
    [BATTLEANIMFRAMESET_57] = Frameset_57,
    [BATTLEANIMFRAMESET_58] = Frameset_58,
    [BATTLEANIMFRAMESET_59] = Frameset_59,
    [BATTLEANIMFRAMESET_5A] = Frameset_5a,
    [BATTLEANIMFRAMESET_5B] = Frameset_5b,
    [BATTLEANIMFRAMESET_5C] = Frameset_5c,
    [BATTLEANIMFRAMESET_5D] = Frameset_5d,
    [BATTLEANIMFRAMESET_5E] = Frameset_5e,
    [BATTLEANIMFRAMESET_5F] = Frameset_5f,
    [BATTLEANIMFRAMESET_60] = Frameset_60,
    [BATTLEANIMFRAMESET_61] = Frameset_61,
    [BATTLEANIMFRAMESET_62] = Frameset_62,
    [BATTLEANIMFRAMESET_63] = Frameset_63,
    [BATTLEANIMFRAMESET_64] = Frameset_64,
    [BATTLEANIMFRAMESET_65] = Frameset_65,
    [BATTLEANIMFRAMESET_66] = Frameset_66,
    [BATTLEANIMFRAMESET_67] = Frameset_67,
    [BATTLEANIMFRAMESET_68] = Frameset_68,
    [BATTLEANIMFRAMESET_69] = Frameset_69,
    [BATTLEANIMFRAMESET_6A] = Frameset_6a,
    [BATTLEANIMFRAMESET_6B] = Frameset_6b,
    [BATTLEANIMFRAMESET_6C] = Frameset_6c,
    [BATTLEANIMFRAMESET_6D] = Frameset_6d,
    [BATTLEANIMFRAMESET_6E] = Frameset_6e,
    [BATTLEANIMFRAMESET_6F] = Frameset_6f,
    [BATTLEANIMFRAMESET_70] = Frameset_70,
    [BATTLEANIMFRAMESET_71] = Frameset_71,
    [BATTLEANIMFRAMESET_72] = Frameset_72,
    [BATTLEANIMFRAMESET_73] = Frameset_73,
    [BATTLEANIMFRAMESET_74] = Frameset_74,
    [BATTLEANIMFRAMESET_75] = Frameset_75,
    [BATTLEANIMFRAMESET_76] = Frameset_76,
    [BATTLEANIMFRAMESET_77] = Frameset_77,
    [BATTLEANIMFRAMESET_78] = Frameset_78,
    [BATTLEANIMFRAMESET_79] = Frameset_79,
    [BATTLEANIMFRAMESET_7A] = Frameset_7a,
    [BATTLEANIMFRAMESET_7B] = Frameset_7b,
    [BATTLEANIMFRAMESET_7C] = Frameset_7c,
    [BATTLEANIMFRAMESET_7D] = Frameset_7d,
    [BATTLEANIMFRAMESET_7E] = Frameset_7e,
    [BATTLEANIMFRAMESET_7F] = Frameset_7f,
    [BATTLEANIMFRAMESET_80] = Frameset_80,
    [BATTLEANIMFRAMESET_81] = Frameset_81,
    [BATTLEANIMFRAMESET_82] = Frameset_82,
    [BATTLEANIMFRAMESET_83] = Frameset_83,
    [BATTLEANIMFRAMESET_84] = Frameset_84,
    [BATTLEANIMFRAMESET_85] = Frameset_85,
    [BATTLEANIMFRAMESET_86] = Frameset_86,
    [BATTLEANIMFRAMESET_87] = Frameset_87,
    [BATTLEANIMFRAMESET_88] = Frameset_88,
    [BATTLEANIMFRAMESET_89] = Frameset_89,
    [BATTLEANIMFRAMESET_8A] = Frameset_8a,
    [BATTLEANIMFRAMESET_8B] = Frameset_8b,
    [BATTLEANIMFRAMESET_8C] = Frameset_8c,
    [BATTLEANIMFRAMESET_8D] = Frameset_8d,
    [BATTLEANIMFRAMESET_8E] = Frameset_8e,
    [BATTLEANIMFRAMESET_8F] = Frameset_8f,
    [BATTLEANIMFRAMESET_90] = Frameset_90,
    [BATTLEANIMFRAMESET_91] = Frameset_91,
    [BATTLEANIMFRAMESET_92] = Frameset_92,
    [BATTLEANIMFRAMESET_93] = Frameset_93,
    [BATTLEANIMFRAMESET_94] = Frameset_94,
    [BATTLEANIMFRAMESET_95] = Frameset_95,
    [BATTLEANIMFRAMESET_96] = Frameset_96,
    [BATTLEANIMFRAMESET_97] = Frameset_97,
    [BATTLEANIMFRAMESET_98] = Frameset_98,
    [BATTLEANIMFRAMESET_99] = Frameset_99,
    [BATTLEANIMFRAMESET_9A] = Frameset_9a,
    [BATTLEANIMFRAMESET_9B] = Frameset_9b,
    [BATTLEANIMFRAMESET_9C] = Frameset_9c,
    [BATTLEANIMFRAMESET_9D] = Frameset_9d,
    [BATTLEANIMFRAMESET_9E] = Frameset_9e,
    [BATTLEANIMFRAMESET_9F] = Frameset_9f,
    [BATTLEANIMFRAMESET_A0] = Frameset_a0,
    [BATTLEANIMFRAMESET_A1] = Frameset_a1,
    [BATTLEANIMFRAMESET_A2] = Frameset_a2,
    [BATTLEANIMFRAMESET_A3] = Frameset_a3,
    [BATTLEANIMFRAMESET_A4] = Frameset_a4,
    [BATTLEANIMFRAMESET_A5] = Frameset_a5,
    [BATTLEANIMFRAMESET_A6] = Frameset_a6,
    [BATTLEANIMFRAMESET_A7] = Frameset_a7,
    [BATTLEANIMFRAMESET_A8] = Frameset_a8,
    [BATTLEANIMFRAMESET_A9] = Frameset_a9,
    [BATTLEANIMFRAMESET_AA] = Frameset_aa,
    [BATTLEANIMFRAMESET_AB] = Frameset_ab,
    [BATTLEANIMFRAMESET_AC] = Frameset_ac,
    [BATTLEANIMFRAMESET_AD] = Frameset_ad,
    [BATTLEANIMFRAMESET_AE] = Frameset_ae,
    [BATTLEANIMFRAMESET_AF] = Frameset_af,
    [BATTLEANIMFRAMESET_B0] = Frameset_b0,
    [BATTLEANIMFRAMESET_B1] = Frameset_b1,
    [BATTLEANIMFRAMESET_B2] = Frameset_b2,
    [BATTLEANIMFRAMESET_B3] = Frameset_b3,
    [BATTLEANIMFRAMESET_B4] = Frameset_b4,
    [BATTLEANIMFRAMESET_B5] = Frameset_b5,
    [BATTLEANIMFRAMESET_B6] = Frameset_b6,
    [BATTLEANIMFRAMESET_B7] = Frameset_b7,
    [BATTLEANIMFRAMESET_B8] = Frameset_b8,
};
static_assert(lengthof(BattleAnimFrameData) == NUM_BATTLEANIMFRAMESETS, "");
