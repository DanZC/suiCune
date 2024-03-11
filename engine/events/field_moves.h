void PlayWhirlpoolSound(void);
void BlindingFlash(void);
void ShakeHeadbuttTree(void);
extern const char HeadbuttTreeGFX[];
void HideHeadbuttTree(void);
extern const uint16_t TreeRelativeLocationTable[];
void OWCutAnimation(void);
void OWCutAnimation_Conv(uint8_t e);
// void CutTreeGFX(void);
// void CutGrassGFX(void);
void OWCutJumptable(void);
void Cut_SpawnAnimateTree(void);
void Cut_SpawnAnimateLeaves(void);
void Cut_StartWaiting(void);
void Cut_WaitAnimSFX(void);
void Cut_SpawnLeaf(void);
struct SpriteAnim* Cut_SpawnLeaf_Conv(uint16_t de, uint8_t a);
void Cut_GetLeafSpawnCoords(void);
uint16_t Cut_GetLeafSpawnCoords_Conv(void);
void Cut_Headbutt_GetPixelFacing(void);
uint16_t Cut_Headbutt_GetPixelFacing_Conv(void);
void FlyFromAnim(void);
void FlyToAnim(void);
void FlyFunction_InitGFX(void);
void FlyFunction_FrameTimer(void);
//#include "gfx/overworld/headbutt_tree.2bpp"
//#include "gfx/overworld/cut_tree.2bpp"
//#include "gfx/overworld/cut_grass.2bpp"
