#include "../../constants.h"
#include "print_photo.h"
#include "../../home/text.h"
#include "../../home/sprite_updates.h"
#include "../../home/map.h"
#include "../pokemon/party_menu.h"
#include "../printer/printer.h"
#include "../../data/text/common.h"

void PhotoStudio(void){
    static const txt_cmd_s WhichMonPhotoText[] = {
        text_far(v_WhichMonPhotoText)
        text_end
    };

    static const txt_cmd_s HoldStillText[] = {
        text_far(v_HoldStillText)
        text_end
    };

    static const txt_cmd_s PrestoAllDoneText[] = {
        text_far(v_PrestoAllDoneText)
        text_end
    };

    static const txt_cmd_s NoPhotoText[] = {
        text_far(v_NoPhotoText)
        text_end
    };

    static const txt_cmd_s EggPhotoText[] = {
        text_far(v_EggPhotoText)
        text_end
    };

    // LD_HL(mPhotoStudio_WhichMonPhotoText);
    // CALL(aPrintText);
    PrintText_Conv2(WhichMonPhotoText);
    // FARCALL(aSelectMonFromParty);
    // IF_C goto cancel;
    SelectMonFromParty();
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto egg;
    if(wram->wCurPartySpecies == EGG) {
    // egg:
        // LD_HL(mPhotoStudio_EggPhotoText);
        return PrintText_Conv2(EggPhotoText);
    }

    // LD_HL(mPhotoStudio_HoldStillText);
    // CALL(aPrintText);
    PrintText_Conv2(HoldStillText);
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates_Conv();
    // FARCALL(aPrintPartymon);
    PrintPartymon();
    // CALL(aReturnToMapWithSpeechTextbox);
    ReturnToMapWithSpeechTextbox_Conv();
    // LDH_A_addr(hPrinter);
    // AND_A_A;
    // IF_NZ goto cancel;
    if(hPrinter != 0x0) {
    // cancel:
        // LD_HL(mPhotoStudio_NoPhotoText);
        // goto print_text;
        return PrintText_Conv2(NoPhotoText);
    }
    // LD_HL(mPhotoStudio_PrestoAllDoneText);
    // goto print_text;

// print_text:
    // CALL(aPrintText);
    // RET;
    return PrintText_Conv2(PrestoAllDoneText);
}
