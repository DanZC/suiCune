struct PuzzleCoord {
    uint16_t oamCoord;
    uint16_t coord;
    uint8_t vacantTile;
    uint8_t filler;
};
void v_UnownPuzzle(void);
void InitUnownPuzzlePiecePositions(void);
void PlaceStartCancelBox(void);
void PlaceStartCancelBoxBorder(void);
void UnownPuzzleJumptable(void);
void UnownPuzzle_A(void);
void UnownPuzzle_Quit(void);
void UnownPuzzle_InvalidAction(void);
void UnownPuzzle_FillBox(tile_t* hl, uint8_t b, uint8_t c, tile_t a);
void UnownPuzzle_UpdateTilemap(void);
void PlaceUnownPuzzlePieceGFX(void);
void FillUnoccupiedPuzzleSpace(void);
const uint8_t* GetUnownPuzzleCoordData(uint8_t a);
uint8_t* UnownPuzzle_CheckCurrentTileOccupancy(void);
uint8_t GetCurrentPuzzlePieceVTileCorner(void);
bool CheckSolvedUnownPuzzle(void);
void RedrawUnownPuzzlePieces(void);
extern const struct PuzzleCoord UnownPuzzleCoordData[];
void ConvertLoadedPuzzlePieces(void);
void UnownPuzzle_AddPuzzlePieceBorders(void);
// void PuzzlePieceBorderData(void);
void LoadUnownPuzzlePiecesGFX(void);
extern const char UnownPuzzleCursorGFX[];
extern const char UnownPuzzleStartCancelLZ[];
extern const char HoOhPuzzleLZ[];
extern const char AerodactylPuzzleLZ[];
extern const char KabutoPuzzleLZ[];
extern const char OmanytePuzzleLZ[];
//#include "gfx/unown_puzzle/tile_borders.2bpp"
//#include "gfx/unown_puzzle/cursor.2bpp"
//#include "gfx/unown_puzzle/start_cancel.2bpp.lz"
//#include "gfx/unown_puzzle/hooh.2bpp.lz"
//#include "gfx/unown_puzzle/aerodactyl.2bpp.lz"
//#include "gfx/unown_puzzle/kabuto.2bpp.lz"
//#include "gfx/unown_puzzle/omanyte.2bpp.lz"
