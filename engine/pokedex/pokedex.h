void Pokedex(void);
void InitPokedex(void);
void Pokedex_CheckUnlockedUnownMode(void);
void Pokedex_InitCursorPosition(void);
void Pokedex_GetLandmark(void);
void Pokedex_RunJumptable(void);
void Pokedex_IncrementDexPointer(void);
void Pokedex_Exit(void);
void Pokedex_InitMainScreen(void);
void Pokedex_UpdateMainScreen(void);
void Pokedex_InitDexEntryScreen(void);
void Pokedex_UpdateDexEntryScreen(void);
void Pokedex_Page(void);
void Pokedex_ReinitDexEntryScreen(void);
struct ArrowCursorData;
// void DexEntryScreen_ArrowCursorData(void);
void DexEntryScreen_MenuActionJumptable(uint8_t a);
void Pokedex_RedisplayDexEntry(void);
void Pokedex_InitOptionScreen(void);
void Pokedex_UpdateOptionScreen(void);
void Pokedex_InitSearchScreen(void);
void Pokedex_UpdateSearchScreen(void);
void Pokedex_InitSearchResultsScreen(void);
void Pokedex_UpdateSearchResultsScreen(void);
void Pokedex_InitUnownMode(void);
void Pokedex_UpdateUnownMode(void);
void Pokedex_UnownModeHandleDPadInput(void);
void Pokedex_UnownModeEraseCursor(uint8_t a);
void Pokedex_UnownModePlaceCursor(void);
void Pokedex_UnownModeUpdateCursorGfx(uint8_t a, uint8_t c);
bool Pokedex_NextOrPreviousDexEntry(void);
bool Pokedex_ListingHandleDPadInput(void);
bool Pokedex_ListingMoveCursorUp(void);
bool Pokedex_ListingMoveCursorDown(uint8_t d, uint8_t e);
bool Pokedex_ListingMoveUpOnePage(uint8_t d);
bool Pokedex_ListingMoveDownOnePage(uint8_t d, uint8_t e);
bool Pokedex_ListingPosStayedSame(void);
bool Pokedex_ListingPosChanged(void);
tile_t* Pokedex_FillColumn(tile_t* hl, uint8_t b, uint8_t a);
void Pokedex_DrawMainScreenBG(void);
extern const char String_SEEN[];
extern const char String_OWN[];
extern const uint8_t String_SELECT_OPTION[];
extern const uint8_t String_START_SEARCH[];
void Pokedex_DrawDexEntryScreenBG(void);
void Pokedex_DrawOptionScreenBG(void);
void Pokedex_DrawSearchScreenBG(void);
void Pokedex_DrawSearchResultsScreenBG(void);
void Pokedex_PlaceSearchResultsTypeStrings(void);
void Pokedex_DrawUnownModeBG(void);
extern const uint16_t UnownModeLetterAndCursorCoords[];
void Pokedex_FillBackgroundColor2(void);
void Pokedex_PlaceFrontpicTopLeftCorner(void);
void Pokedex_PlaceFrontpicAtHL(tile_t* hl);
void Pokedex_PlaceString(uint8_t* hl, const uint8_t* de);
void Pokedex_PlaceBorder(tile_t* hl, uint8_t b, uint8_t c);
void Pokedex_PrintListing(void);
void Pokedex_PrintNumberIfOldMode(tile_t* hl, species_t a);
tile_t* Pokedex_PlaceCaughtSymbolIfCaught(tile_t* hl, species_t a);
bool Pokedex_PlaceDefaultStringIfNotSeen(tile_t* hl, species_t species);
void Pokedex_DrawFootprint(void);
species_t Pokedex_GetSelectedMon(void);
bool Pokedex_CheckCaught(species_t species);
bool Pokedex_CheckSeen(species_t species);
void Pokedex_OrderMonsByMode(void);
void Pokedex_ABCMode(void);
void Pokedex_DisplayModeDescription(void);
void Pokedex_DisplayChangingModesMessage(void);
extern const char String_ChangingModesPleaseWait[];
bool Pokedex_UpdateSearchMonType(void);
bool Pokedex_PrevSearchMonType(void);
bool Pokedex_NextSearchMonType(void);
void Pokedex_PlaceSearchScreenTypeStrings(void);
void Pokedex_PlaceTypeString(tile_t* hl, uint8_t a);
void Pokedex_SearchForMons(void);
void Pokedex_DisplayTypeNotFoundMessage(void);
void Pokedex_UpdateCursorOAM(void);
void Pokedex_PutOldModeCursorOAM(void);
struct SpriteOAM* Pokedex_PutNewModeABCModeCursorOAM(void);
void Pokedex_UpdateSearchResultsCursorOAM(void);
struct SpriteOAM* Pokedex_LoadCursorOAM(const uint8_t* hl);
void Pokedex_PutScrollbarOAM(struct SpriteOAM*);
void Pokedex_InitArrowCursor(void);
bool Pokedex_MoveArrowCursor(const struct ArrowCursorData* de);
tile_t* Pokedex_GetArrowCursorPos(const struct ArrowCursorData* de);
void Pokedex_BlinkArrowCursor(const struct ArrowCursorData* de);
bool Pokedex_ArrowCursorDelay(void);
void Pokedex_FillBox(tile_t* hl, uint8_t w, uint8_t h, uint8_t byte);
void Pokedex_BlackOutBG(void);
void Pokedex_ApplyPrintPals(void);
void Pokedex_GetSGBLayout(uint8_t a);
void Pokedex_ApplyUsualPals(void);
void Pokedex_LoadPointer(void);
void Pokedex_LoadSelectedMonTiles(void);
void Pokedex_LoadCurrentFootprint(void);
void Pokedex_LoadAnyFootprint(species_t a);
void Pokedex_LoadGFX(void);
void Pokedex_LoadInvertedFont(void);
void Pokedex_InvertTiles(uint8_t* hl, uint16_t bc);
extern const char PokedexLZ[];
extern const char PokedexSlowpokeLZ[];
bool Pokedex_CheckSGB(void);
void Pokedex_LoadUnownFont(void);
void Pokedex_LoadUnownFrontpicTiles(void);
void v_NewPokedexEntry(void);
void Pokedex_SetBGMapMode3(void);
void Pokedex_SetBGMapMode4(void);
void Pokedex_SetBGMapMode_3ifDMG_4ifCGB(void);
void Pokedex_ResetBGMapMode(void);
//#include "data/pokemon/dex_order_alpha.h"
//#include "data/pokemon/dex_order_new.h"
//#include "data/types/search_strings.h"
//#include "data/types/search_types.h"
//#include "gfx/pokedex/pokedex.2bpp.lz"
//#include "gfx/pokedex/slowpoke.2bpp.lz"
