void v_AnimateTileset(void);
// void Tileset0Anim(void);
// void TilesetJohtoModernAnim(void);
#define Tileset0Anim TilesetKantoAnim
#define TilesetJohtoModernAnim TilesetKantoAnim
extern const struct TileAnimFrame TilesetKantoAnim[];
extern const struct TileAnimFrame TilesetParkAnim[];
extern const struct TileAnimFrame TilesetForestAnim[];
extern const struct TileAnimFrame TilesetJohtoAnim[];
extern const struct TileAnimFrame UnusedTilesetAnim1[];
extern const struct TileAnimFrame UnusedTilesetAnim2[];
extern const struct TileAnimFrame TilesetPortAnim[];
extern const struct TileAnimFrame TilesetEliteFourRoomAnim[];
void UnusedTilesetAnim3(void);
void UnusedTilesetAnim4(void);
// void TilesetCaveAnim(void);
#define TilesetCaveAnim TilesetDarkCaveAnim
extern const struct TileAnimFrame TilesetDarkCaveAnim[];
extern const struct TileAnimFrame TilesetIcePathAnim[];
extern const struct TileAnimFrame TilesetTowerAnim[];
void UnusedTilesetAnim5(void);
// void TilesetBattleTowerOutsideAnim(void);
// void TilesetHouseAnim(void);
// void TilesetPlayersHouseAnim(void);
// void TilesetPokecenterAnim(void);
// void TilesetGateAnim(void);
// void TilesetLabAnim(void);
// void TilesetFacilityAnim(void);
// void TilesetMartAnim(void);
// void TilesetMansionAnim(void);
// void TilesetGameCornerAnim(void);
// void TilesetTraditionalHouseAnim(void);
// void TilesetTrainStationAnim(void);
// void TilesetChampionsRoomAnim(void);
// void TilesetLighthouseAnim(void);
// void TilesetPlayersRoomAnim(void);
// void TilesetPokeComCenterAnim(void);
// void TilesetBattleTowerInsideAnim(void);
// void TilesetRuinsOfAlphAnim(void);
// void TilesetRadioTowerAnim(void);
// void TilesetUndergroundAnim(void);
// void TilesetBetaWordRoomAnim(void);
// void TilesetHoOhWordRoomAnim(void);
// void TilesetKabutoWordRoomAnim(void);
// void TilesetOmanyteWordRoomAnim(void);
#define TilesetBattleTowerOutsideAnim TilesetAerodactylWordRoomAnim
#define TilesetHouseAnim TilesetAerodactylWordRoomAnim
#define TilesetPlayersHouseAnim TilesetAerodactylWordRoomAnim
#define TilesetPokecenterAnim TilesetAerodactylWordRoomAnim
#define TilesetGateAnim TilesetAerodactylWordRoomAnim
#define TilesetLabAnim TilesetAerodactylWordRoomAnim
#define TilesetFacilityAnim TilesetAerodactylWordRoomAnim
#define TilesetMartAnim TilesetAerodactylWordRoomAnim
#define TilesetMansionAnim TilesetAerodactylWordRoomAnim
#define TilesetGameCornerAnim TilesetAerodactylWordRoomAnim
#define TilesetTraditionalHouseAnim TilesetAerodactylWordRoomAnim
#define TilesetTrainStationAnim TilesetAerodactylWordRoomAnim
#define TilesetChampionsRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetLighthouseAnim TilesetAerodactylWordRoomAnim
#define TilesetPlayersRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetPokeComCenterAnim TilesetAerodactylWordRoomAnim
#define TilesetBattleTowerInsideAnim TilesetAerodactylWordRoomAnim
#define TilesetRuinsOfAlphAnim TilesetAerodactylWordRoomAnim
#define TilesetRadioTowerAnim TilesetAerodactylWordRoomAnim
#define TilesetUndergroundAnim TilesetAerodactylWordRoomAnim
#define TilesetBetaWordRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetHoOhWordRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetKabutoWordRoomAnim TilesetAerodactylWordRoomAnim
#define TilesetOmanyteWordRoomAnim TilesetAerodactylWordRoomAnim
extern const struct TileAnimFrame TilesetAerodactylWordRoomAnim[];
void DoneTileAnimation(uint8_t*);
void WaitTileAnimation(uint8_t*);
void StandingTileFrame8(uint8_t*);
void ScrollTileRightLeft(uint8_t*);
void ScrollTileUpDown(void);
void ScrollTileLeft(uint8_t*);
void ScrollTileRight(uint8_t*);
void ScrollTileUp(uint8_t*);
void ScrollTileDown(uint8_t*);
void AnimateFountainTile(uint8_t*);
void AnimateWaterTile(uint8_t*);
void ForestTreeLeftAnimation(uint8_t*);
extern const char* ForestTreeLeftFrames[];
extern const char* ForestTreeRightFrames[];
void ForestTreeRightAnimation(uint8_t*);
void ForestTreeLeftAnimation2(uint8_t*);
void ForestTreeRightAnimation2(uint8_t*);
uint8_t GetForestTreeFrame(uint8_t);
void AnimateFlowerTile(uint8_t*);
void AnimateLavaBubbleTile1(uint8_t*);
void AnimateLavaBubbleTile2(uint8_t*);
extern const char* LavaBubbleTileFrames[];
void AnimateTowerPillarTile(uint8_t*);
void StandingTileFrame(uint8_t*);
void AnimateWhirlpoolTile(uint8_t*);
void WriteTileFromAnimBuffer(uint8_t*);
void ReadTileToAnimBuffer(uint8_t*);
void WriteTile(uint8_t* hl, const uint8_t* sp);
void AnimateWaterPalette(uint8_t*);
void FlickeringCaveEntrancePalette(uint8_t*);
// void TowerPillarTilePointer1(void);
// void TowerPillarTilePointer2(void);
// void TowerPillarTilePointer3(void);
// void TowerPillarTilePointer4(void);
// void TowerPillarTilePointer5(void);
// void TowerPillarTilePointer6(void);
// void TowerPillarTilePointer7(void);
// void TowerPillarTilePointer8(void);
// void TowerPillarTilePointer9(void);
// void TowerPillarTilePointer10(void);
extern const char TowerPillarTile1[];
extern const char TowerPillarTile2[];
extern const char TowerPillarTile3[];
extern const char TowerPillarTile4[];
extern const char TowerPillarTile5[];
extern const char TowerPillarTile6[];
extern const char TowerPillarTile7[];
extern const char TowerPillarTile8[];
extern const char TowerPillarTile9[];
extern const char TowerPillarTile10[];
// void WhirlpoolFrames1(void);
// void WhirlpoolFrames2(void);
// void WhirlpoolFrames3(void);
// void WhirlpoolFrames4(void);
extern const char WhirlpoolTiles1[];
extern const char WhirlpoolTiles2[];
extern const char WhirlpoolTiles3[];
extern const char WhirlpoolTiles4[];
