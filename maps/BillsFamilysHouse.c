#include "../constants.h"
#include "../util/scripting.h"
#include "BillsFamilysHouse.h"
//// EVENTS
enum {
    BILLSFAMILYSHOUSE_BILL = 2,
    BILLSFAMILYSHOUSE_POKEFAN_F,
    BILLSFAMILYSHOUSE_TWIN,
};

const Script_fn_t BillsFamilysHouse_SceneScripts[] = {
    0,
};

const struct MapCallback BillsFamilysHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts BillsFamilysHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(BillsFamilysHouse_SceneScripts),
    .scene_scripts = BillsFamilysHouse_SceneScripts,

    .callback_count = 0, // lengthof(BillsFamilysHouse_MapCallbacks),
    .callbacks = BillsFamilysHouse_MapCallbacks,
};

static const struct CoordEvent BillsFamilysHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent BillsFamilysHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &BillsHouseBookshelf2),
    bg_event(1, 1, BGEVENT_READ, &BillsHouseBookshelf1),
    bg_event(7, 1, BGEVENT_READ, &BillsHouseRadio),
};

static const struct WarpEventData BillsFamilysHouse_WarpEvents[] = {
    warp_event(2, 7, GOLDENROD_CITY, 4),
    warp_event(3, 7, GOLDENROD_CITY, 4),
};

static const struct ObjEvent BillsFamilysHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_BILL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BillScript, EVENT_MET_BILL),
    object_event(5, 3, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BillsMomScript, -1),
    object_event(5, 4, SPRITE_TWIN, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BillsSisterScript, -1),
};

const struct MapEvents BillsFamilysHouse_MapEvents = {
    .warp_event_count = lengthof(BillsFamilysHouse_WarpEvents),
    .warp_events = BillsFamilysHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(BillsFamilysHouse_CoordEvents),
    .coord_events = BillsFamilysHouse_CoordEvents,

    .bg_event_count = lengthof(BillsFamilysHouse_BGEvents),
    .bg_events = BillsFamilysHouse_BGEvents,

    .obj_event_count = lengthof(BillsFamilysHouse_ObjectEvents),
    .obj_events = BillsFamilysHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BillsFamilysHouse.h"

bool BillScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_EEVEE)
    iftrue(GotEevee)
    writetext(BillTakeThisEeveeText)
    yesorno
    iffalse(Refused)
    writetext(BillImCountingOnYouText)
    promptbutton
    waitsfx
    readvar(VAR_PARTYCOUNT)
    ifequal(PARTY_LENGTH, NoRoom)
    writetext(ReceivedEeveeText)
    playsound(SFX_CAUGHT_MON)
    waitsfx
    givepoke(EEVEE, 20, NO_ITEM)
    setevent(EVENT_GOT_EEVEE)
    writetext(BillEeveeMayEvolveText)
    waitbutton
    closetext
    s_end
NoRoom:
    writetext(BillPartyFullText)
    waitbutton
    closetext
    s_end
Refused:
    writetext(BillNoEeveeText)
    waitbutton
    closetext
    s_end
GotEevee:
    writetext(BillPopWontWorkText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BillsMomScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_MET_BILL)
    iffalse(HaventMetBill)
    writetext(BillsMomText_BeforeEcruteak)
    waitbutton
    closetext
    s_end
HaventMetBill:
    writetext(BillsMomText_AfterEcruteak)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool BillsSisterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkcellnum(PHONE_BILL)
    iftrue(GotBillsNumber)
    writetext(BillsSisterUsefulNumberText)
    askforphonenumber(PHONE_BILL)
    ifequal(PHONE_CONTACTS_FULL, NoRoom)
    ifequal(PHONE_CONTACT_REFUSED, Refused)
    waitsfx
    addcellnum(PHONE_BILL)
    writetext(RecordedBillsNumberText)
    playsound(SFX_REGISTER_PHONE_NUMBER)
    waitsfx
    promptbutton
GotBillsNumber:
    writetext(BillsSisterStorageSystemText)
    waitbutton
    closetext
    s_end
Refused:
    writetext(BillsSisterRefusedNumberText)
    waitbutton
    closetext
    s_end
NoRoom:
    writetext(BillsSisterPhoneFullText)
    promptbutton
    goto Refused;
    SCRIPT_END
}
bool BillsHouseBookshelf1(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
bool BillsHouseBookshelf2(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
bool BillsHouseRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
    SCRIPT_END
}
const txt_cmd_s BillTakeThisEeveeText[] = {
    text_start("BILL: Hi, <PLAYER>!"
        t_line "Do us a favor and"
        t_cont "take this EEVEE."
        t_para "It came over when"
        t_line "I was adjusting"
        t_cont "the TIME CAPSULE."
        t_para "Someone has to"
        t_line "take care of it,"
        t_para "but I don't like"
        t_line "being outside."
        t_para "Can I count on you"
        t_line "to play with it,"
        t_cont "<PLAYER>?"
        t_done )
};
const txt_cmd_s BillImCountingOnYouText[] = {
    text_start("BILL: I knew you'd"
        t_line "come through!"
        t_para "Way to go! You're"
        t_line "the real deal!"
        t_para "OK, I'm counting"
        t_line "on you."
        t_para "Take good care of"
        t_line "it!"
        t_done )
};
const txt_cmd_s ReceivedEeveeText[] = {
    text_start("<PLAYER> received"
        t_line "EEVEE!"
        t_done )
};
const txt_cmd_s BillEeveeMayEvolveText[] = {
    text_start("BILL: PROF.ELM"
        t_line "claims EEVEE may"
        t_para "evolve in new and"
        t_line "unknown ways."
        t_done )
};
const txt_cmd_s BillPartyFullText[] = {
    text_start("Whoa, wait. You"
        t_line "can't carry any"
        t_cont "more #MON."
        t_done )
};
const txt_cmd_s BillNoEeveeText[] = {
    text_start("Oh… Now what to"
        t_line "do?"
        t_done )
};
const txt_cmd_s BillPopWontWorkText[] = {
    text_start("BILL: My pop, he"
        t_line "won't work. All he"
        t_para "does is goof off"
        t_line "all day long."
        t_para "He's getting to be"
        t_line "a real headache…"
        t_done )
};
const txt_cmd_s BillsMomText_BeforeEcruteak[] = {
    text_start("Oh, you collect"
        t_line "#MON? My son"
        t_cont "BILL is an expert."
        t_para "He just got called"
        t_line "to the #MON"
        t_para "CENTER in ECRUTEAK"
        t_line "CITY."
        t_para "My husband went"
        t_line "off to the GAME"
        t_para "CORNER without"
        t_line "being called…"
        t_done )
};
const txt_cmd_s BillsMomText_AfterEcruteak[] = {
    text_start("My husband was"
        t_line "once known as a"
        t_para "#MANIAC."
        t_line "BILL must have"
        t_para "taken after his"
        t_line "father."
        t_done )
};
const txt_cmd_s BillsSisterUsefulNumberText[] = {
    text_start("Are you a trainer?"
        t_para "I've got a useful"
        t_line "phone number for"
        t_cont "you."
        t_done )
};
const txt_cmd_s RecordedBillsNumberText[] = {
    text_start("<PLAYER> recorded"
        t_line "BILL's number."
        t_done )
};
const txt_cmd_s BillsSisterRefusedNumberText[] = {
    text_start("My brother made"
        t_line "the PC #MON"
        t_cont "storage system."
        t_para "I was going to"
        t_line "give you BILL's"
        t_cont "number…"
        t_done )
};
const txt_cmd_s BillsSisterPhoneFullText[] = {
    text_start("You can't record"
        t_line "any more numbers."
        t_done )
};
const txt_cmd_s BillsSisterStorageSystemText[] = {
    text_start("My big brother"
        t_line "BILL made the PC"
        t_para "#MON storage"
        t_line "system."
        t_done )
    //db(0, 0) // filler
};
