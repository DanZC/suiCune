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
    text_start("Would you like to"
        t_line "host or join?"
        t_done)
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

static const struct TextCmd Text_Cancelled[] = {
    text_start("Cancelled."
        t_prompt)
};

static const struct TextCmd Text_CouldntFindAny[] = {
    text_start("Couldn't find"
        t_line "any players."
        t_prompt)
};

static const struct MenuHeader Menu_HostOrJoin = {
    .flags = MENU_BACKUP_TILES, // flags
    .coord = menu_coords(0, 4, 15, TEXTBOX_Y - 1), 
    .data = &(struct MenuData){
    // .MenuData:
        .flags=STATICMENU_CURSOR, // flags
        .verticalMenu = {
            .count=3, // items
            .options = (const char* []) {
                "HOST GAME",
                "JOIN GAME",
                "CANCEL"
            }
        },
    },
	.defaultOption=1 // default option
};

void LANConnection_Host(void);
void LANConnection_Join(void);

void LANConnection(void) {
    NetworkClearLANCache();
    LoadStandardMenuHeader_Conv();
    MapTextbox_Conv(Text_AskHostOrJoin);
    LoadMenuHeader_Conv2(&Menu_HostOrJoin);
    bool noCancel = VerticalMenu_Conv();
    CloseWindow_Conv2();
    if(noCancel) {
        switch(wram->wMenuCursorY) {
            case 1: return LANConnection_Host();
            case 2: return LANConnection_Join();
            case 3: break;
        }
    }
    wram->wScriptVar = FALSE;
    CloseWindow_Conv2();
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
    SpeechTextbox_Conv2();
    LoadStandardMenuHeader_Conv();
    PlaceStringSimple(U82C("Hosting…<LINE>Please wait…"), coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wram->wTilemap));

    if(!NetworkBroadcastLAN(wram->wPlayerName, wram->wPlayerID, wram->wPlayerGender)) {
        CloseWindow_Conv2();
        MapTextbox_Conv(Text_Cancelled);
        CloseWindow_Conv2();
        wram->wScriptVar = FALSE;
        return;
    }

    uint32_t frameCount = 0;
    for(;; frameCount++) {
        DelayFrame();

        GetJoypad_Conv();
        uint8_t pad = hram->hJoyPressed;
        if(pad & B_BUTTON) {
            CloseWindow_Conv2();
            MapTextbox_Conv(Text_Cancelled);
            CloseWindow_Conv2();
            NetworkCloseConnection();
            wram->wScriptVar = FALSE;
            return;
        }

        if(NetworkCheckLAN()) {
            CopyBytes_Conv2(wram->wStringBuffer1, gLANClientCandidates[0].name, sizeof(gLANClientCandidates[0].name) - 1);
            wram->wStringBuffer1[11] = CHAR_TERM;
            MapTextbox_Conv(Text_WillYouAccept);
            bool yes = YesNoBox_Conv();
            CloseWindow_Conv2();
            if(yes) {
                LoadStandardMenuHeader_Conv();
                PlaceStringSimple(U82C("Waiting for a<LINE>response…"), coord(4, 11, wram->wTilemap));
                bool success = NetworkLANDirectConnect(0);
                CloseWindow_Conv2();
                if(success) {
                    wram->wScriptVar = TRUE;
                    return;
                }
                else {
                    NetworkCloseConnection();
                    wram->wScriptVar = FALSE;
                    return;
                }
            }
        }

        // Rebroadcast about every 2 seconds.
        if((frameCount & 0x7f) == 0x7f) {
            if(!NetworkBroadcastLAN(wram->wPlayerName, wram->wPlayerID, wram->wPlayerGender)) {
                CloseWindow_Conv2();
                MapTextbox_Conv(Text_Cancelled);
                CloseWindow_Conv2();
                NetworkCloseConnection();
                wram->wScriptVar = FALSE;
                return;
            }
        }
    }
    MapTextbox_Conv(Text_CouldntFindAny);
    CloseWindow_Conv2();
    CloseWindow_Conv2();
    wram->wScriptVar = FALSE;
    return;
}

static bool LANConnection_TryJoin(uint8_t which) {
    if(!NetworkTryJoinLAN(which, wram->wPlayerName, wram->wPlayerID, wram->wPlayerGender))
        return false;
    for(int i = 0; i < 60 * 16; ++i) {
        DelayFrame();
        if(NetworkCheckLAN())
            return true;
    }
    return false;
}

void LANConnection_Join(void) {
    SpeechTextbox_Conv2();
    LoadStandardMenuHeader_Conv();
    PlaceStringSimple(U82C("Searching for<LINE>players…"), coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wram->wTilemap));

    NetworkStartJoining();

    uint32_t selection = 0;

    Textbox_Conv2(coord(8, 0, wram->wTilemap), TEXTBOX_Y - 2, SCREEN_WIDTH - 8 - 2);
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
            PlayClickSFX_Conv();
            CloseWindow_Conv2();
            CloseWindow_Conv2();
            NetworkCloseConnection();
            wram->wScriptVar = FALSE;
            return;
        }
        else if(pad & A_BUTTON) {
            PlayClickSFX_Conv();
            CloseWindow_Conv2();
            if(selection >= gLANClientCandidateCount - 1 || gLANClientCandidateCount == 0) {
                wram->wScriptVar = FALSE;
                NetworkCloseConnection();
                CloseWindow_Conv2();
                return;
            }

            CopyBytes_Conv2(wram->wStringBuffer1, gLANClientCandidates[selection].name, sizeof(gLANClientCandidates[selection].name) - 1);
            wram->wStringBuffer1[11] = CHAR_TERM;
            MapTextbox_Conv(Text_WillYouConnect);
            bool yes = YesNoBox_Conv();
            CloseWindow_Conv2();
            if(yes) {
                LoadStandardMenuHeader_Conv();
                PlaceStringSimple(U82C("Waiting for a<LINE>response…"), coord(4, 11, wram->wTilemap));
                bool success = LANConnection_TryJoin(selection);
                CloseWindow_Conv2();
                if(success) {
                    wram->wScriptVar = TRUE;
                    return;
                }
                else {
                    NetworkCloseConnection();
                    wram->wScriptVar = FALSE;
                    return;
                }
            }
            else {
                NetworkCloseConnection();
                wram->wScriptVar = FALSE;
                return;
            }
        }
        DelayFrame();
    }

    if(gLANClientCandidateCount == 0) {
        MapTextbox_Conv(Text_CouldntFindAny);
        CloseWindow_Conv2();
        wram->wScriptVar = FALSE;
        CloseWindow_Conv2();
        NetworkCloseConnection();
        return;
    }
}