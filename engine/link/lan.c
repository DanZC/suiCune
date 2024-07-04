#include "../../constants.h"
#include "lan.h"
#include "../../charmap.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/map.h"
#include "../../home/menu.h"
#include "../../home/joypad.h"
#include "../../home/map_objects.h"
#include "../../util/network.h"

static const txt_cmd_s Text_AskHostOrJoin[] = {
    text_start("Would you like to"
        t_line "host or join?"
        t_done)
};

static const txt_cmd_s Text_WillYouConnect[] = {
    text_start("Will you connect"
        t_line "to @")
    text_ram(wram_ptr(wStringBuffer1))
    text_start("?" 
        t_done )
};

static const txt_cmd_s Text_WillYouAccept[] = {
    text_start("Will you accept"
        t_line "@")
    text_ram(wram_ptr(wStringBuffer1))
    text_start("'s connection?"
        t_done )
};

static const txt_cmd_s Text_Cancelled[] = {
    text_start("Cancelled."
        t_prompt)
};

static const txt_cmd_s Text_CouldntFindAny[] = {
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

void LANCloseConnection(void) {
    NetworkCloseConnection();
}

static void PlaceLANConnectionItems(void) {
    char buffer[16];
    uint8_t x = 7, y = 2;
    const uint32_t candidateCount = NetworkGetLANCandidateCount();
    for(uint32_t i = 0; i < candidateCount; ++i) {
        LANClient* candidate = NetworkGetLANCandidate(i);
        PlaceStringSimple(candidate->name, coord(x + 1, y, wram->wTilemap));
        *coord(x + 9, y, wram->wTilemap) = (bit_test(candidate->gender, PLAYERGENDER_FEMALE_F))? CHAR_FEMALE_ICON: CHAR_MALE_ICON;
        sprintf(buffer, "%06d", candidate->trainerId);
        PlaceStringSimple(U82C(buffer), coord(x + 3, y + 1, wram->wTilemap));
        y += 2;
    }
    PlaceStringSimple(U82C("CANCEL"), coord(x + 1, y, wram->wTilemap));
}

static void PlaceLANConnectionMenuCursor(uint32_t selection) {
    uint8_t x = 7, y = 2;
    const uint32_t candidateCount = NetworkGetLANCandidateCount();
    for(uint32_t i = 0; i < candidateCount; ++i) {
        *coord(x, y, wram->wTilemap) = (i == selection)? CHAR_RIGHT_CURSOR: CHAR_SPACE;
        y += 2;
    }
    *coord(x, y, wram->wTilemap) = (selection == candidateCount)? CHAR_RIGHT_CURSOR: CHAR_SPACE;
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

        GetJoypad_Conv2();
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
            const LANClient* candidate = NetworkGetLANCandidate(0);
            CopyBytes_Conv2(wram->wStringBuffer1, candidate->name, sizeof(candidate->name) - 1);
            wram->wStringBuffer1[11] = CHAR_TERM;
            MapTextbox_Conv(Text_WillYouAccept);
            bool yes = YesNoBox_Conv();
            CloseWindow_Conv2();
            if(yes) {
                LoadStandardMenuHeader_Conv();
                SpeechTextbox_Conv2();
                PlaceStringSimple(U82C("Waiting for a<LINE>response…"), coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wram->wTilemap));
                bool success = NetworkLANDirectConnect(0);
                CloseWindow_Conv2();
                if(success) {
                    CloseWindow_Conv2();
                    wram->wScriptVar = TRUE;
                    gOtherPlayerGender = candidate->gender;
                    hram->hSerialConnectionStatus = USING_INTERNAL_CLOCK;
                    return;
                }
                else {
                    CloseWindow_Conv2();
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
        // Try again every two seconds.
        if((i % 120) == 0 && i != 0) {
            if(!NetworkTryJoinLAN(which, wram->wPlayerName, wram->wPlayerID, wram->wPlayerGender))
                return false;
        }
        if(NetworkCheckLAN()) {
            return true;
        }
    }
    return false;
}

void LANConnection_Join(void) {
    SpeechTextbox_Conv2();
    LoadStandardMenuHeader_Conv();
    PlaceStringSimple(U82C("Searching for<LINE>players…"), coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wram->wTilemap));

    NetworkStartJoining();

    uint32_t selection = 0;

    Textbox_Conv2(coord(6, 0, wram->wTilemap), TEXTBOX_Y - 2, SCREEN_WIDTH - 6 - 2);
    PlaceLANConnectionItems();
    PlaceLANConnectionMenuCursor(selection);
    UpdateSprites_Conv();
    DelayFrame();

    int frameCount = 0;
    for(;;++frameCount) {
        if(frameCount >= 8 * 60 && NetworkGetLANCandidateCount() == 0) {
            MapTextbox_Conv(Text_CouldntFindAny);
            CloseWindow_Conv2();
            wram->wScriptVar = FALSE;
            CloseWindow_Conv2();
            NetworkCloseConnection();
            return;
        }
        GetJoypad_Conv2();

        if(frameCount < 8 * 60 && NetworkCheckLAN()) {
            ClearBox_Conv2(coord(9, 1, wram->wTilemap), TEXTBOX_Y - 2, SCREEN_WIDTH - 8 - 3);
            PlaceLANConnectionItems();
            PlaceLANConnectionMenuCursor(selection);
            DelayFrame();
            continue;
        }

        const uint32_t candidateCount = NetworkGetLANCandidateCount();
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
            if(selection >= candidateCount) {
                wram->wScriptVar = FALSE;
                MapTextbox_Conv(Text_Cancelled);
                NetworkCloseConnection();
                CloseWindow_Conv2();
                return;
            }

            const LANClient* candidate = NetworkGetLANCandidate(selection);
            CopyBytes_Conv2(wram->wStringBuffer1, candidate->name, sizeof(candidate->name) - 1);
            wram->wStringBuffer1[11] = CHAR_TERM;
            MapTextbox_Conv(Text_WillYouConnect);
            bool yes = YesNoBox_Conv();
            CloseWindow_Conv2();
            if(yes) {
                LoadStandardMenuHeader_Conv();
                SpeechTextbox_Conv2();
                PlaceStringSimple(U82C("Waiting for a<LINE>response…"), coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wram->wTilemap));
                bool success = LANConnection_TryJoin(selection);
                CloseWindow_Conv2();
                if(success) {
                    wram->wScriptVar = TRUE;
                    gOtherPlayerGender = candidate->gender;
                    hram->hSerialConnectionStatus = USING_EXTERNAL_CLOCK;
                    return;
                }
                else {
                    NetworkCloseConnection();
                    wram->wScriptVar = FALSE;
                    return;
                }
            }
            else {
                CloseWindow_Conv2();
                NetworkCloseConnection();
                wram->wScriptVar = FALSE;
                return;
            }
        }
        else if(hram->hJoyPressed & D_DOWN) {
            selection++;
            if(selection > candidateCount)
                selection = 0;
            PlaceLANConnectionMenuCursor(selection);
        }
        else if(hram->hJoyPressed & D_UP) {
            if(selection == 0)
                selection = candidateCount;
            else
                selection--;
            PlaceLANConnectionMenuCursor(selection);
        }
        DelayFrame();
    }
}