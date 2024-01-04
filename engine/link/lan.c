#include "../../constants.h"
#include "lan.h"
#include "../../charmap.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/map.h"
#include "../../home/menu.h"
#include "../../home/joypad.h"
#include "../../util/network.h"

static const struct TextCmd Text_AskHostOrJoin[] = {
    text_start("Would you like to host"
        t_line "or join a game?"
        t_prompt)
};

static const struct TextCmd Text_WillYouConnect[] = {
    text_start("Will you connect to"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?@")
};

static const struct TextCmd Text_WillYouAccept[] = {
    text_start("Will you accept"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s connection?@")
};

static const struct MenuHeader Menu_HostOrJoin = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 2, 15, TEXTBOX_Y - 1), 
    .data = &(struct MenuData){
    // .MenuData:
        .flags=STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count=2, // items
            .options = (const char* []) {
                "HOST",
                "JOIN",
                "CANCEL"
            }
        },
    },
	.defaultOption=2 // default option
};

void LANConnection_Host(void);
void LANConnection_Join(void);

void LANConnection(void) {
    MapTextbox_Conv(Text_AskHostOrJoin);
    LoadMenuHeader_Conv2(&Menu_HostOrJoin);
    bool noCancel = VerticalMenu_Conv();
    ExitMenu_Conv2();
    if(noCancel) {
        switch(wram->wMenuSelection) {
            case 0: return LANConnection_Host();
            case 1: return LANConnection_Join();
            case 2: break;
        }
    }
    wram->wScriptVar = FALSE;
}

static void PlaceLANConnectionItems(void) {
    char buffer[16];
    uint8_t x = 9, y = 0;
    for(uint32_t i = 0; i < gLANClientCandidateCount; ++i) {
        PlaceStringSimple(gLANClientCandidates[i].name, coord(x, y, wram->wTilemap));
        *coord(x + 10, y, wram->wTilemap) = (bit_test(gLANClientCandidates[i].gender, PLAYERGENDER_FEMALE_F))? CHAR_FEMALE_ICON: CHAR_MALE_ICON;
        sprintf(buffer, "%d", gLANClientCandidates[i].trainerId);
        PlaceStringSimple(U82C(buffer), coord(x + 2, y + 1, wram->wTilemap));
        y += 2;
    }
    PlaceStringSimple(U82C("CANCEL"), coord(x, y, wram->wTilemap));
}

void LANConnection_Host(void) {
    LoadStandardMenuHeader_Conv();
    PlaceStringSimple(U82C("Hosting. Please wait…"), coord(4, 11, wram->wTilemap));

    if(!NetworkBroadcastLAN(wram->wPlayerName, wram->wPlayerID, wram->wPlayerGender)) {
        ExitMenu_Conv2();
        wram->wScriptVar = FALSE;
        return;
    }

    for(int i = 0; i < 60 * 8; ++i) {
        DelayFrame();

        if(NetworkCheckLAN()) {
            CopyBytes_Conv2(wram->wStringBuffer1, gLANClientCandidates[0].name, sizeof(gLANClientCandidates[0].name) - 1);
            wram->wStringBuffer1[11] = CHAR_TERM;
            MapTextbox_Conv(Text_WillYouAccept);
            bool yes = YesNoBox_Conv();
            ExitMenu_Conv2();
            if(yes) {
                LoadStandardMenuHeader_Conv();
                PlaceStringSimple(U82C("Waiting for a<LINE>response…"), coord(4, 11, wram->wTilemap));
                bool success = NetworkLANDirectConnect(0);
                ExitMenu_Conv2();
                if(success) {
                    wram->wScriptVar = TRUE;
                    return;
                }
                else {
                    wram->wScriptVar = FALSE;
                    return;
                }
            }
        }
    }
    wram->wScriptVar = FALSE;
    return;
}

static bool LANConnection_TryJoin(uint8_t which) {
    if(!NetworkTryJoinLAN(which, wram->wPlayerName, wram->wPlayerID, wram->wPlayerGender))
        return false;
    for(int i = 0; i < 60 * 8; ++i) {
        DelayFrame();
        if(NetworkCheckLAN())
            return true;
    }
    return false;
}

void LANConnection_Join(void) {
    LoadStandardMenuHeader_Conv();
    PlaceStringSimple(U82C("Searching for players…"), coord(4, 11, wram->wTilemap));

    uint32_t selection = 0;

    Textbox_Conv2(coord(8, 0, wram->wTilemap), TEXTBOX_Y - 1, SCREEN_WIDTH - 8 - 2);
    DelayFrame();

    for(int i = 0; i < 60 * 8; ++i) {
        GetJoypad_Conv();

        if(NetworkCheckLAN()) {
            ClearBox_Conv2(coord(9, 1, wram->wTilemap), TEXTBOX_Y - 2, SCREEN_WIDTH - 8 - 3);
            PlaceLANConnectionItems();
            DelayFrame();
            continue;
        }

        uint8_t pad = GetMenuJoypad_Conv();
        if(pad & B_BUTTON) {
            ExitMenu_Conv2();
            wram->wScriptVar = FALSE;
            return;
        }
        else if(pad & A_BUTTON) {
            PlayClickSFX_Conv();
            ExitMenu_Conv2();
            if(selection == gLANClientCandidateCount - 1) {
                wram->wScriptVar = FALSE;
                return;
            }

            CopyBytes_Conv2(wram->wStringBuffer1, gLANClientCandidates[selection].name, sizeof(gLANClientCandidates[selection].name) - 1);
            wram->wStringBuffer1[11] = CHAR_TERM;
            MapTextbox_Conv(Text_WillYouConnect);
            bool yes = YesNoBox_Conv();
            ExitMenu_Conv2();
            if(yes) {
                LoadStandardMenuHeader_Conv();
                PlaceStringSimple(U82C("Waiting for a<LINE>response…"), coord(4, 11, wram->wTilemap));
                bool success = LANConnection_TryJoin(selection);
                ExitMenu_Conv2();
                if(success) {
                    wram->wScriptVar = TRUE;
                    return;
                }
                else {
                    wram->wScriptVar = FALSE;
                    return;
                }
            }
            else {
                wram->wScriptVar = FALSE;
                return;
            }
        }
        DelayFrame();
    }

    if(gLANClientCandidateCount == 0) {
        ExitMenu_Conv2();
        wram->wScriptVar = FALSE;
        return;
    }
}