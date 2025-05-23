uint8_t GetSpritePalette(uint8_t a);
uint8_t GetSpriteVTile(uint8_t a, uint8_t mapObjIdx);
bool DoesSpriteHaveFacings(uint8_t a);
uint8_t GetPlayerStandingTile(void);
bool CheckOnWater(void);
uint8_t GetTileCollision(uint8_t a);
bool CheckGrassTile(uint8_t col);
bool CheckSuperTallGrassTile(uint8_t a);
bool CheckCutTreeTile(uint8_t a);
bool CheckHeadbuttTreeTile(uint8_t a);
bool CheckCounterTile(uint8_t a);
bool CheckPitTile(uint8_t a);
bool CheckIceTile(uint8_t a);
bool CheckWhirlpoolTile(uint8_t a);
bool CheckWaterfallTile(uint8_t a);
bool CheckStandingOnEntrance(void);
struct MapObject* GetMapObject(uint8_t a);
struct Object* CheckObjectVisibility(uint8_t a);
bool CheckObjectTime(struct MapObject* bc);
uint8_t CopyMapObjectStruct(uint8_t);
void UnmaskCopyMapObjectStruct(uint8_t a);
void ApplyDeletionToMapObject(uint8_t mapObjIdx);
void DeleteObjectStruct(uint8_t a);
void CopyPlayerObjectTemplate(const struct ObjEvent* hl, uint8_t a);
void DeleteFollowerMapObject(uint8_t a);
bool LoadMovementDataPointer(uint8_t a, const uint8_t* hl);
struct Object* FindFirstEmptyObjectStruct(void);
uint8_t GetSpriteMovementFunction(struct Object* bc);
uint8_t GetInitialFacing(uint8_t a);
void CopySpriteMovementData(struct Object* de, uint8_t a);
uint8_t v_GetMovementByte(const uint8_t* hl, struct Object* bc);
void SetVramState_Bit0(void);
void ResetVramState_Bit0(void);
void UpdateSprites(void);
struct Object* GetObjectStruct(uint8_t a);
bool DoesObjectHaveASprite(struct Object* bc);
void SetSpriteDirection(struct Object* bc, uint8_t a);
uint8_t GetSpriteDirection(struct Object* bc);
extern const uint8_t* gMovementDataAddr;
