void BattleStart_TrainerHuds(void);
void EnemySwitch_TrainerHud(void);
void ShowPlayerMonsRemaining(void);
void ShowOTTrainerMonsRemaining(void);
void StageBallTilesData(void);
void StageBallTilesData_Conv(uint8_t count, const struct PartyMon* hl);
void DrawPlayerHUDBorder(void);
void DrawPlayerPartyIconHUDBorder(void);
void DrawEnemyHUDBorder(void);
void PlaceHUDBorderTiles(void);
void PlaceHUDBorderTiles_Conv(tile_t* hl, int16_t de);
void LinkBattle_TrainerHuds(void);
void LoadTrainerHudOAM(void);
void LoadTrainerHudOAM_Conv(struct SpriteOAM* hl, uint8_t y, uint8_t x, int8_t dir);
void LoadBallIconGFX(void);
void v_ShowLinkBattleParticipants(void);
//#include "gfx/battle/balls.2bpp"
