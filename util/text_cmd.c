#include "../constants.h"
#include "../home/text.h"
#include "../home/window.h"
#include "../home/map.h"

struct TextCmd TestText[] = {
    text_start("Hello,"
        t_line "there!"
        t_prompt "@")
    sound_fanfare
    text_end
};

void ShowTestText(void) {
    OpenText();
    MapTextbox(TestText);
    CloseText();
}

