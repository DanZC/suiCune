#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonMansion3F.h"
//// EVENTS
enum {
    CELADONMANSION3F_COOLTRAINER_M = 2,
    CELADONMANSION3F_GYM_GUIDE,
    CELADONMANSION3F_SUPER_NERD,
    CELADONMANSION3F_FISHER,
};

const Script_fn_t CeladonMansion3F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonMansion3F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonMansion3F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonMansion3F_SceneScripts),
    .scene_scripts = CeladonMansion3F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonMansion3F_MapCallbacks),
    .callbacks = CeladonMansion3F_MapCallbacks,
};

static const struct CoordEvent CeladonMansion3F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonMansion3F_BGEvents[] = {
    bg_event(5, 8, BGEVENT_UP, &CeladonMansion3FDevRoomSign),
    bg_event(4, 3, BGEVENT_UP, &CeladonMansion3FDrawing),
    bg_event(1, 6, BGEVENT_UP, &CeladonMansion3FGameProgram),
    bg_event(1, 3, BGEVENT_UP, &CeladonMansion3FReferenceMaterial),
};

static const struct WarpEventData CeladonMansion3F_WarpEvents[] = {
    warp_event(0, 0, CELADON_MANSION_ROOF, 1),
    warp_event(1, 0, CELADON_MANSION_2F, 2),
    warp_event(6, 0, CELADON_MANSION_2F, 3),
    warp_event(7, 0, CELADON_MANSION_ROOF, 2),
};

static const struct ObjEvent CeladonMansion3F_ObjectEvents[] = {
    object_event(3, 6, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GameFreakGameDesignerScript, -1),
    object_event(3, 4, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GameFreakGraphicArtistScript, -1),
    object_event(0, 7, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &GameFreakProgrammerScript, -1),
    object_event(0, 4, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GameFreakCharacterDesignerScript, -1),
};

const struct MapEvents CeladonMansion3F_MapEvents = {
    .warp_event_count = lengthof(CeladonMansion3F_WarpEvents),
    .warp_events = CeladonMansion3F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonMansion3F_CoordEvents),
    .coord_events = CeladonMansion3F_CoordEvents,

    .bg_event_count = lengthof(CeladonMansion3F_BGEvents),
    .bg_events = CeladonMansion3F_BGEvents,

    .obj_event_count = lengthof(CeladonMansion3F_ObjectEvents),
    .obj_events = CeladonMansion3F_ObjectEvents,
};

//// CODE

bool GameFreakGameDesignerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GameFreakGameDesignerText)
    readvar(VAR_DEXCAUGHT)
    ifgreater(NUM_POKEMON - 2 - 1, CompletedPokedex) // ignore Mew and Celebi
    waitbutton
    closetext
    s_end
CompletedPokedex:
    promptbutton
    writetext(GameFreakGameDesignerCompletedPokedexText)
    playsound(SFX_DEX_FANFARE_230_PLUS)
    waitsfx
    writetext(GameFreakGameDesignerPauseForDiplomaText)
    promptbutton
    special(Diploma)
    writetext(GameFreakGameDesignerAfterDiplomaText)
    waitbutton
    closetext
    setevent(EVENT_ENABLE_DIPLOMA_PRINTING)
    s_end
    SCRIPT_END
}
bool GameFreakGraphicArtistScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_ENABLE_DIPLOMA_PRINTING)
    iftrue(CanPrintDiploma)
    writetext(GameFreakGraphicArtistText)
    waitbutton
    closetext
    s_end
CanPrintDiploma:
    writetext(GameFreakGraphicArtistPrintDiplomaText)
    yesorno
    iffalse(Refused)
    special(PrintDiploma)
    closetext
    s_end
Refused:
    writetext(GameFreakGraphicArtistRefusedText)
    waitbutton
    closetext
    s_end
CancelPrinting:
    writetext(GameFreakGraphicArtistErrorText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GameFreakProgrammerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GameFreakProgrammerText)
    SCRIPT_END
}
bool GameFreakCharacterDesignerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GameFreakCharacterDesignerText)
    SCRIPT_END
}
bool CeladonMansion3FDevRoomSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonMansion3FDevRoomSignText)
    SCRIPT_END
}
bool CeladonMansion3FDrawing(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonMansion3FDrawingText)
    SCRIPT_END
}
bool CeladonMansion3FGameProgram(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonMansion3FGameProgramText)
    SCRIPT_END
}
bool CeladonMansion3FReferenceMaterial(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonMansion3FReferenceMaterialText)
    SCRIPT_END
}
const txt_cmd_s GameFreakGameDesignerText[] = {
    text_start("Is that right?"
        t_para "I'm the GAME"
        t_line "DESIGNER!"
        t_para "Filling up your"
        t_line "#DEX is tough,"
        t_cont "but don't give up!"
        t_done )
};
const txt_cmd_s GameFreakGameDesignerCompletedPokedexText[] = {
    text_start("Wow! Excellent!"
        t_line "You completed your"
        t_cont "#DEX!"
        t_para "Congratulations!"
        t_done )
};
const txt_cmd_s GameFreakGameDesignerPauseForDiplomaText[] = {
    text_start("…"
        t_done )
};
const txt_cmd_s GameFreakGameDesignerAfterDiplomaText[] = {
    text_start("The GRAPHIC ARTIST"
        t_line "will print out a"
        t_cont "DIPLOMA for you."
        t_para "You should go show"
        t_line "it off."
        t_done )
};
const txt_cmd_s GameFreakGraphicArtistText[] = {
    text_start("I'm the GRAPHIC"
        t_line "ARTIST."
        t_para "I drew you!"
        t_done )
};
const txt_cmd_s GameFreakGraphicArtistPrintDiplomaText[] = {
    text_start("I'm the GRAPHIC"
        t_line "ARTIST."
        t_para "Oh, you completed"
        t_line "your #DEX?"
        t_para "Want me to print"
        t_line "out your DIPLOMA?"
        t_done )
};
const txt_cmd_s GameFreakGraphicArtistRefusedText[] = {
    text_start("Give me a shout if"
        t_line "you want your"
        t_cont "DIPLOMA printed."
        t_done )
};
const txt_cmd_s GameFreakGraphicArtistErrorText[] = {
    text_start("Something's wrong."
        t_line "I'll have to can-"
        t_cont "cel printing."
        t_done )
};
const txt_cmd_s GameFreakProgrammerText[] = {
    text_start("Who, me? I'm the"
        t_line "PROGRAMMER."
        t_para "Play the slot"
        t_line "machines!"
        t_done )
};
const txt_cmd_s GameFreakCharacterDesignerText[] = {
    text_start("Aren't the TWINS"
        t_line "adorable?"
        t_para "JASMINE's pretty"
        t_line "too."
        t_para "Oh, I love them!"
        t_done )
};
const txt_cmd_s CeladonMansion3FDevRoomSignText[] = {
    text_start("GAME FREAK"
        t_line "DEVELOPMENT ROOM"
        t_done )
};
const txt_cmd_s CeladonMansion3FDrawingText[] = {
    text_start("It's a detailed"
        t_line "drawing of a"
        t_cont "pretty girl."
        t_done )
};
const txt_cmd_s CeladonMansion3FGameProgramText[] = {
    text_start("It's the game"
        t_line "program. Messing"
        t_para "with it could put"
        t_line "a bug in the game!"
        t_done )
};
const txt_cmd_s CeladonMansion3FReferenceMaterialText[] = {
    text_start("It's crammed with"
        t_line "reference materi-"
        t_cont "als. There's even"
        t_cont "a # DOLL."
        t_done )
    //db(0, 0) // filler
};
