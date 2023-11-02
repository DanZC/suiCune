struct StepVector {
    int8_t x;
    int8_t y;
    uint8_t duration;
    uint8_t speed;
};
void DeleteMapObject(void);
void DeleteMapObject_Conv(struct Object* obj);
void HandleObjectStep(void);
void CheckObjectStillVisible(void);
void HandleStepType(void);
void HandleObjectAction(void);
void HandleFrozenObjectAction(void);
void HandleFrozenObjectAction_Conv(struct Object* bc);
void v_CallFrozenObjectAction(void);
void v_CallFrozenObjectAction_Conv(struct Object* bc);
void CallObjectAction(void);
void CallObjectAction_Conv(struct Object* bc, int column);
void CopyNextCoordsTileToStandingCoordsTile(void);
uint8_t CopyNextCoordsTileToStandingCoordsTile_Conv(struct Object* bc);
void CopyStandingCoordsTileToNextCoordsTile(void);
void UpdateTallGrassFlags(void);
void UpdateTallGrassFlags_Conv(struct Object* bc);
void SetTallGrassFlags(void);
void SetTallGrassFlags_Conv(struct Object* bc, uint8_t a);
void UselessAndA(void);
void EndSpriteMovement(void);
void EndSpriteMovement_Conv(struct Object* bc);
void InitStep(void);
void InitStep_Conv(struct Object* bc, uint8_t a);
void GetNextTile(void);
void GetNextTile_Conv(struct Object* bc);
void AddStepVector(void);
struct StepVector AddStepVector_Conv(struct Object* bc);
void GetStepVector(void);
struct StepVector GetStepVector_Conv(struct Object* bc);
// void StepVectors(void);
extern const struct StepVector StepVectors[];
void GetStepVectorSign(void);
int8_t GetStepVectorSign_Conv(int8_t a);
void UpdatePlayerStep(void);
void UpdatePlayerStep_Conv(struct Object* bc);
void GetMapObjectField(void);
void RestoreDefaultMovement(void);
uint8_t RestoreDefaultMovement_Conv(struct Object* bc);
void ObjectMovementByte_ZeroAnonJumptableIndex(void);
void ObjectMovementByte_IncAnonJumptableIndex(void);
void ObjectMovementByte_DecAnonJumptableIndex(void);
void ObjectMovementByte_AnonJumptable(void);
void Field1c_ZeroAnonJumptableIndex(void);
void Field1c_IncAnonJumptableIndex(void);
void Field1c_AnonJumptable(void);
void Field1c_GetAnonJumptableIndex(void);
void Field1c_SetAnonJumptableIndex(void);
void StepFunction_Reset(void);
void StepFunction_FromMovement(void);
void MovementFunction_Null(void);
void MovementFunction_RandomWalkY(void);
void MovementFunction_RandomWalkX(void);
void MovementFunction_RandomWalkXY(void);
void MovementFunction_RandomSpinSlow(void);
void MovementFunction_RandomSpinFast(void);
void MovementFunction_Standing(void);
void MovementFunction_ObeyDPad(void);
void MovementFunction_Indexed1(void);
void MovementFunction_Indexed2(void);
void MovementFunction_0a(void);
void MovementFunction_0b(void);
void MovementFunction_0c(void);
void MovementFunction_0d(void);
void MovementFunction_0e(void);
void MovementFunction_Follow(void);
void MovementFunction_Script(void);
void MovementFunction_Strength(void);
void MovementFunction_FollowNotExact(void);
void MovementFunction_BigStanding(void);
void MovementFunction_Bouncing(void);
void MovementFunction_SpinCounterclockwise(void);
void MovementFunction_SpinClockwise(void);
void v_MovementSpinInit(void);
void v_MovementSpinRepeat(void);
void v_MovementSpinTurnLeft(void);
void v_MovementSpinTurnRight(void);
void v_MovementSpinNextFacing(void);
void MovementFunction_Shadow(void);
void MovementFunction_Emote(void);
void MovementFunction_BoulderDust(void);
void MovementFunction_ShakingGrass(void);
void InitMovementField1dField1e(void);
void MovementFunction_ScreenShake(void);
void v_RandomWalkContinue(void);
void RandomStepDuration_Slow(void);
void RandomStepDuration_Fast(void);
void v_SetRandomStepDuration(void);
void StepTypesJumptable(void);
void WaitStep_InPlace(void);
void StepFunction_NPCJump(void);
void StepFunction_PlayerJump(void);
void StepFunction_TeleportFrom(void);
void StepFunction_TeleportTo(void);
void StepFunction_Skyfall(void);
void StepFunction_GotBite(void);
void StepFunction_RockSmash(void);
void StepFunction_DigTo(void);
void StepFunction_Sleep(void);
void StepFunction_Delete(void);
void StepFunction_Bump(void);
void StepFunction_Restore(void);
void StepFunction_Standing(void);
void StepFunction_NPCWalk(void);
void StepFunction_ContinueWalk(void);
void StepFunction_PlayerWalk(void);
void StepFunction_Turn(void);
void StepFunction_StrengthBoulder(void);
void StepFunction_TrackingObject(void);
void StepFunction_14(void);
void StepFunction_ScreenShake(void);
void StepFunction_16(void);
void StepFunction_17(void);
void StepFunction_SkyfallTop(void);
void Stubbed_UpdateYOffset(void);
void UpdateJumpPosition(void);
void GetPlayerNextMovementByte(void);
void GetMovementByte(void);
void GetIndexedMovementByte1(void);
void GetIndexedMovementByte2(void);
void v_GetMovementObject(void);
uint8_t GetMovementObject(void);
void HandleMovementData(void);
void HandleMovementData_Conv(struct Object* bc, uint8_t (*hl)(void));
void JumpMovementPointer(void);
uint8_t JumpMovementPointer_Conv(void);
void ContinueReadingMovement(void);
void DoMovementFunction(void);
void DoMovementFunction_Conv(struct Object* bc, uint8_t a);
void ApplyMovementToFollower(void);
void ApplyMovementToFollower_Conv(uint8_t a);
void GetFollowerNextMovementByte(void);
void SpawnShadow(void);
void SpawnShadow_Conv(struct Object* bc);
void SpawnStrengthBoulderDust(void);
void SpawnEmote(void);
void SpawnEmote_Conv(struct Object* bc);
void ShakeGrass(void);
void ShakeGrass_Conv(struct Object* bc);
void ShakeScreen(void);
void ShakeScreen_Conv(struct Object* bc, uint8_t a);
void DespawnEmote(void);
void DespawnEmote_Conv(struct Object* bc);
void InitTempObject(void);
void InitTempObject_Conv(void);
void CopyTempObjectData(void);
void CopyTempObjectData_Conv(struct Object* bc, const uint8_t* de);
void UpdateAllObjectsFrozen(void);
void UpdateAllObjectsFrozen_Conv(void);
void RespawnPlayerAndOpponent(void);
void RespawnPlayerAndOpponent_Conv(void);
void RespawnPlayer(void);
void RespawnObject(void);
void RespawnObject_Conv(uint8_t a);
void HideAllObjects(void);
void UpdateObjectFrozen(void);
bool UpdateObjectFrozen_Conv(struct Object* bc);
void UpdateRespawnedObjectFrozen(void);
void UpdateRespawnedObjectFrozen_Conv(struct Object* bc);
void SetFacing_Standing(void);
bool SetFacing_Standing_Conv(struct Object* bc);
void UpdateObjectNextTile(void);
void UpdateObjectNextTile_Conv(struct Object* bc);
void CheckObjectOnScreen(void);
bool CheckObjectOnScreen_Conv(struct Object* bc);
void CheckObjectCoveredByTextbox(void);
bool CheckObjectCoveredByTextbox_Conv(struct Object* bc);
void HandleNPCStep(void);
void ResetStepVector(void);
void DoStepsForAllObjects(void);
void RefreshPlayerSprite(void);
void TryResetPlayerAction(void);
void SpawnInCustomFacing(void);
void SpawnInFacingDown(void);
void v_ContinueSpawnFacing(void);
void v_SetPlayerPalette(void);
void StartFollow(void);
void StartFollow_Conv(uint8_t b, uint8_t c);
void SetLeaderIfVisible(void);
bool SetLeaderIfVisible_Conv(uint8_t a);
void StopFollow(void);
void StopFollow_Conv(void);
void ResetLeader(void);
void ResetLeader_Conv(void);
void SetFollowerIfVisible(void);
bool SetFollowerIfVisible_Conv(uint8_t a);
void ResetFollower(void);
void ResetFollower_Conv(void);
void FreezeAllOtherObjects(void);
bool FreezeAllOtherObjects_Conv(uint8_t c);
void FreezeObject(void);
void FreezeAllObjects(void);
void FreezeAllObjects_Conv(void);
void v_UnfreezeFollowerObject(void);
void v_UnfreezeFollowerObject_Conv(uint8_t c);
void UnfreezeAllObjects(void);
void UnfreezeAllObjects_Conv(void);
void UnfreezeObject(void);
void ResetObject(void);
void ResetObject_Conv(struct Object* bc);
void v_UpdateSprites(void);
void v_UpdateSprites_Conv(void);
void ApplyBGMapAnchorToObjects(void);
void ApplyBGMapAnchorToObjects_Conv(void);
void InitSprites(void);
//#include "data/sprites/facings.h"
//#include "data/sprites/map_objects.h"
//#include "engine/overworld/map_object_action.h"
//#include "engine/overworld/movement.h"
