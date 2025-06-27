#include "../constants.h"

const struct OptionsData DefaultOptions = {
// wOptions: med text speed
    .options = TEXT_DELAY_MED,
// wSaveFileExists: no
    .saveFileExists = FALSE,
// wTextboxFrame: frame 1
    .textboxFrame = FRAME_1,
// wTextboxFlags: use text speed
    .textboxFlags = 1 << FAST_TEXT_DELAY_F,
// wGBPrinterBrightness: normal
    .GBPrinterBrightness = GBPRINTER_NORMAL,
// wOptions2: menu account on
    .options2 = 1 << MENU_ACCOUNT,

    .unused = {
        0x00,
        0x00,
    },
};
// End
