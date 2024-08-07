void TMHMPocket(void);
void ConvertCurItemIntoCurTMHM(void);
void GetTMHMItemMove(void);
move_t GetTMHMItemMove_Conv(item_t item);
void AskTeachTMHM(void);
u8_flag_s ChooseMonToLearnTMHM(void);
u8_flag_s ChooseMonToLearnTMHM_NoRefresh(void);
void TeachTMHM(void);
extern const txt_cmd_s BootedTMText[];
extern const txt_cmd_s BootedHMText[];
extern const txt_cmd_s ContainedMoveText[];
extern const txt_cmd_s TMHMNotCompatibleText[];
void TMHM_PocketLoop(void);
void TMHM_JoypadLoop(void);
void TMHM_ShowTMMoveDescription(void);
void TMHM_ChooseTMorHM(void);
void TMHM_CheckHoveringOverCancel(void);
void TMHM_ExitPack(void);
void v_TMHM_ExitPack(void);
void TMHM_ExitPocket(void);
void TMHM_ScrollPocket(void);
void TMHM_DisplayPocketItems(void);
void TMHMPocket_GetCurrentLineCoord(void);
void PlaceMoveNameAfterTMHMName(void);
void TMHM_CancelString(void);
void TMHM_GetCurrentPocketPosition(void);
void Tutorial_TMHMPocket(void);
void TMHM_PlaySFX_ReadText2(void);
void VerboseReceiveTMHM(void);
void ConsumeTM(void);
void CountTMsHMs(void);
