void ClearUnusedMapBuffer(void);
uint8_t CheckScenes(void);
uint16_t GetCurrentMapSceneID(void);
uint8_t* GetMapSceneID(uint8_t group, uint8_t map);
void OverworldTextModeSwitch(void);
void LoadMapPart(void);
void LoadMetatiles(void);
void ReturnToMapFromSubmenu(void);
bool CheckWarpTile(void);
bool WarpCheck(void);
u8_flag_s GetDestinationWarpNumber(void);
void CopyWarpData(uint8_t c);
bool CheckOutdoorMap(uint8_t a);
bool CheckIndoorMap(uint8_t a);
bool CheckUnknownMap(uint8_t a);
void LoadMapAttributes(void);
void LoadMapAttributes_SkipObjects(void);
void CopyMapPartialAndAttributes(void);
void ReadMapEvents(bool skipObjectEvents);
void ReadMapScripts(void);
void CopyMapAttributes(const struct MapAttr* attr);
void GetMapConnections(const struct MapAttr* attr);
void GetMapConnection(struct MapConnectionData* de, const struct MapConnectionData* hl);
void ReadMapSceneScripts(const struct MapScripts* hl);
void ReadMapCallbacks(const struct MapScripts* hl);
void ReadWarps(const struct MapEvents* hl);
void ReadCoordEvents(const struct MapEvents* hl);
void ReadBGEvents(const struct MapEvents* hl);
void ReadObjectEvents(const struct MapEvents* hl);
uint8_t CopyMapObjectEvents(struct MapObject* hl, const struct ObjEvent* de, uint8_t count);
void ClearObjectStructs(void);
void GetWarpDestCoords(void);
void LoadBlockData(void);
void ChangeMap(void);
void FillMapConnections(void);
void FillNorthConnectionStrip(uint8_t* de, const uint8_t* hl);
void FillSouthConnectionStrip(uint8_t* de, const uint8_t* hl);
void FillWestConnectionStrip(uint8_t* de, const uint8_t* hl, uint8_t b);
void FillEastConnectionStrip(uint8_t* de, const uint8_t* hl, uint8_t b);
void LoadMapStatus(uint8_t a);
uint8_t CallScript(Script_fn_t hl);
uint8_t CallMapScript(Script_fn_t hl);
void RunMapCallback(uint8_t a);
void ExecuteCallbackScript(Script_fn_t de);
void MapTextbox(const struct TextCmd* text);
void Call_a_de(void);
bool GetMovementData(uint8_t c, const uint8_t* hl);
void GetScriptByte(void);
bool ObjectEvent(script_s* s);
extern const txt_cmd_s ObjectEventText[];
bool BGEvent(script_s* s);
extern const txt_cmd_s BGEventText[];
bool CoordinatesEvent(script_s* s);
extern const txt_cmd_s CoordinatesEventText[];
uint8_t CheckObjectMask(uint8_t a);
void MaskObject(uint8_t a);
void UnmaskObject(uint8_t a);
void ComputeROMXChecksum(void);
void ScrollMapUp(void);
void ScrollMapDown(void);
void ScrollMapLeft(void);
void ScrollMapRight(void);
void BackupBGMapRow(tile_t* de, const tile_t* hl);
void BackupBGMapColumn(tile_t* de, const tile_t* hl);
void UpdateBGMapRow(uint16_t de);
void UpdateBGMapColumn(uint16_t de);
void ClearBGMapBuffer(void);
void LoadTilesetGFX(void);
void BufferScreen(void);
void SaveScreen(void);
void LoadConnectionBlockData(void);
void SaveScreen_LoadConnection(uint8_t* hl, const uint8_t* de, uint8_t b, uint8_t c);
void GetMovementPermissions(void);
struct CoordsTileId GetFacingTileCoord(void);
uint8_t GetCoordTile(uint8_t d, uint8_t e);
uint8_t* GetBlockLocation(uint8_t d, uint8_t e);
bool CheckFacingBGEvent(void);
bool CheckIfFacingTileCoordIsBGEvent(uint8_t c, uint8_t d, uint8_t e);
const struct CoordEvent* CheckCurrentMapCoordEvents(void);
void FadeToMenu(void);
void CloseSubmenu(void);
void ExitAllMenus(void);
void FinishExitMenu(void);
void ReturnToMapWithSpeechTextbox(void);
void ReloadTilesetAndPalettes(void);
const struct MapHeader* GetMapPointer(void);
const struct MapHeader* GetAnyMapPointer(uint8_t group, uint8_t map);
// uint16_t GetMapField_Conv(uint16_t offset);
void GetAnyMapField(void);
// uint16_t GetAnyMapField_Conv(uint16_t offset, uint8_t group, uint8_t map);
void SwitchToMapAttributesBank(void);
void SwitchToAnyMapAttributesBank(void);
void GetMapAttributesBank(void);
void GetAnyMapAttributesBank(void);
void CopyMapPartial(void);
void SwitchToMapScriptsBank(void);
uint8_t GetMapScriptsBank(void);
void GetAnyMapBlocksBank(void);
const struct MapAttr* GetMapAttributesPointer(void);
uint8_t GetMapEnvironment(void);
void Map_DummyFunction(void);
uint8_t GetAnyMapEnvironment(uint8_t group, uint8_t map);
uint8_t GetAnyMapTileset(uint8_t group, uint8_t map);
uint8_t GetWorldMapLocation(uint8_t group, uint8_t map);
uint16_t GetMapMusic(void);
uint8_t GetMapTimeOfDay(void);
uint8_t GetMapPhoneService(void);
uint8_t GetPhoneServiceTimeOfDayByte(void);
uint8_t GetFishingGroup(void);
void LoadMapTileset(void);
void DummyEndPredef(void);

extern uint8_t gCurMapCallbackCount;
extern const struct MapCallback* gCurMapCallbacksPointer;
extern uint8_t gCurMapSceneScriptCount;
extern const Script_fn_t* gCurMapSceneScriptsPointer;
extern uint8_t gCurMapWarpCount;
extern const struct WarpEventData* gCurMapWarpsPointer;
extern uint8_t gCurMapBGEventCount;
extern const struct BGEvent* gCurMapBGEventsPointer;
extern uint8_t gCurMapObjectEventCount;
extern const struct ObjEvent* gCurMapObjectEventsPointer;

extern const struct TileAnimFrame* gTilesetAnim;
extern const struct Tileset* gTilesetPointer;

extern struct BGEvent gCurBGEvent;
extern struct MapConnectionData gMapConnections[4];
