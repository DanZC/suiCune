void PlayWhirlpoolSound(void);
void BlindingFlash(void);
void ShakeHeadbuttTree(void);
extern const char HeadbuttTreeGFX[];
void HideHeadbuttTree(void);
extern const uint16_t TreeRelativeLocationTable[];
void OWCutAnimation(uint8_t e);
// void CutTreeGFX(void);
// void CutGrassGFX(void);
void OWCutJumptable(void);
void Cut_SpawnAnimateTree(void);
void Cut_SpawnAnimateLeaves(void);
void Cut_StartWaiting(void);
void Cut_WaitAnimSFX(void);
// struct SpriteAnim* Cut_SpawnLeaf(uint16_t de, uint8_t a);
// uint16_t Cut_GetLeafSpawnCoords(void);
// uint16_t Cut_Headbutt_GetPixelFacing(void);
void FlyFromAnim(void);
void FlyToAnim(void);
void FlyFunction_InitGFX(void);
void FlyFunction_FrameTimer(void);
//#include "gfx/overworld/headbutt_tree.2bpp"
//#include "gfx/overworld/cut_tree.2bpp"
//#include "gfx/overworld/cut_grass.2bpp"
