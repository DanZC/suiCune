#include "../constants.h"

const uint8_t DefaultOptions[] = {
// wOptions: med text speed
    TEXT_DELAY_MED,
// wSaveFileExists: no
    FALSE,
// wTextboxFrame: frame 1
    FRAME_1,
// wTextboxFlags: use text speed
    1 << FAST_TEXT_DELAY_F,
// wGBPrinterBrightness: normal
    GBPRINTER_NORMAL,
// wOptions2: menu account on
    1 << MENU_ACCOUNT,

    0x00,
    0x00,
};

const uint32_t DefaultOptions_Size = lengthof(DefaultOptions);
// End
static_assert(wOptionsEnd - wOptions == lengthof(DefaultOptions), "");
