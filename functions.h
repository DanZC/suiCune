#include "main.h"
//#define REDIRECTED(x) redirectFunc[a##x] = x
#define REDIRECTED(x) redirectFunc[a##x] = convertedFunc[a##x] = x
#define CONVERTED(x) convertedFunc[a##x] = x

void init_function_pointers() {
    for (int i = 0; i < ROM_SIZE; i++) redirectFunc[i] = convertedFunc[i] = NULL;

    // home/array.c
    REDIRECTED(AddNTimes);
    REDIRECTED(IsInArray);
    REDIRECTED(SkipNames);

    // home/audio.c
    REDIRECTED(MaxVolume);
    REDIRECTED(PlayMusic2);
    REDIRECTED(MinVolume);
    REDIRECTED(RestartMapMusic);
    REDIRECTED(IsSFXPlaying);
    REDIRECTED(UpdateSound);
    REDIRECTED(FadeOutToMusic);
    REDIRECTED(SpecialMapMusic);
    REDIRECTED(GetMapMusic_MaybeSpecial);
    REDIRECTED(WaitPlaySFX);
    REDIRECTED(PlaceBCDNumberSprite);
    REDIRECTED(LowVolume);
    REDIRECTED(PlaySFX);
    REDIRECTED(TerminateExpBarSound);
    REDIRECTED(InitSound);
    REDIRECTED(TryRestartMapMusic);
    REDIRECTED(FadeInToMusic);
    REDIRECTED(PlayMapMusicBike);
    REDIRECTED(WaitSFX);
    REDIRECTED(PlayMapMusic);
    REDIRECTED(PlayMusic);
    REDIRECTED(FadeToMapMusic);
    REDIRECTED(PlayCry);
    REDIRECTED(SkipMusic);
    REDIRECTED(CheckSFX);
    REDIRECTED(ChannelsOff);
    REDIRECTED(SFXChannelsOff);

    // home/battle.c
    REDIRECTED(UpdateBattleHuds);
    REDIRECTED(OpponentPartyAttr);
    REDIRECTED(UpdateOpponentInParty);
    REDIRECTED(GetPartyLocation);
    REDIRECTED(UserPartyAttr);
    REDIRECTED(SetPlayerTurn);
    REDIRECTED(PushLYOverrides);
    REDIRECTED(GetBattleAnimByte);
    REDIRECTED(RefreshBattleHuds);
    REDIRECTED(MobileTextBorder);
    REDIRECTED(OTPartyAttr);
    REDIRECTED(FarCopyRadioText);
    REDIRECTED(BattleTextbox);
    REDIRECTED(UpdateUserInParty);
    REDIRECTED(GetPartyParamLocation);
    REDIRECTED(BattlePartyAttr);
    REDIRECTED(UpdateBattleMonInParty);
    REDIRECTED(GetDexNumber);
    REDIRECTED(GetBattleAnimPointer);
    REDIRECTED(StdBattleTextbox);
    REDIRECTED(SetEnemyTurn);
    REDIRECTED(UpdateBattleMon);
    REDIRECTED(UpdateEnemyMonInParty);
    REDIRECTED(ResetDamage);

    // home/battle_vars.c
    // REDIRECTED(BattleVarLocations);
    // REDIRECTED(BattleVarPairs);
    // REDIRECTED(GetBattleVar);
    // REDIRECTED(GetBattleVarAddr);

    // home/call_regs.c
    // REDIRECTED(v_hl_);
    REDIRECTED(v_de_);

    // home/clear_sprites.c
    // REDIRECTED(HideSprites);
    // REDIRECTED(ClearSprites);

    // home/compare.c
    REDIRECTED(CompareBytesLong);
    REDIRECTED(CompareBytes);

    // home/copy.c
    // REDIRECTED(GetFarWRAMWord);
    // REDIRECTED(GetFarByte);
    // REDIRECTED(FarCopyWRAM);
    // REDIRECTED(CopyBytes);
    // REDIRECTED(GetFarWRAMByte);
    // REDIRECTED(ByteFill);
    // REDIRECTED(SwapBytes);
    // REDIRECTED(GetFarWord);

    // home/copy_name.c
    // REDIRECTED(CopyName1);
    // REDIRECTED(CopyName2);

    // home/copy_tilemap.c
    REDIRECTED(LoadTilemapToTempTilemap);
    REDIRECTED(LoadTempTilemapToTilemap);
    REDIRECTED(SafeLoadTempTilemapToTilemap);

    // home/decompress.c
    REDIRECTED(Decompress);
    REDIRECTED(FarDecompress);

    // home/delay.c
    // REDIRECTED(DelayFrame);
    // REDIRECTED(DelayFrames);

    // home/double_speed.c
    // REDIRECTED(DoubleSpeed);
    // REDIRECTED(NormalSpeed);
    // REDIRECTED(SwitchSpeed);

    // home/fade.c
    // REDIRECTED(TimeOfDayFade);
    // REDIRECTED(RotateThreePalettesRight);
    // REDIRECTED(IncGradGBPalTable_04);
    // REDIRECTED(RotateFourPalettesRight);
    // REDIRECTED(IncGradGBPalTable_14);
    // REDIRECTED(IncGradGBPalTable_12);
    // REDIRECTED(RotateThreePalettesLeft);
    // REDIRECTED(IncGradGBPalTable_02);
    // REDIRECTED(IncGradGBPalTable_08);
    // REDIRECTED(IncGradGBPalTable_07);
    // REDIRECTED(IncGradGBPalTable_03);
    // REDIRECTED(IncGradGBPalTable_06);
    // REDIRECTED(IncGradGBPalTable_11);
    // REDIRECTED(IncGradGBPalTable_01);
    // REDIRECTED(IncGradGBPalTable_10);
    // REDIRECTED(IncGradGBPalTable_15);
    // REDIRECTED(RotatePalettesLeft);
    // REDIRECTED(RotatePalettesRight);
    // REDIRECTED(IncGradGBPalTable_13);
    // REDIRECTED(RotateFourPalettesLeft);
    // REDIRECTED(IncGradGBPalTable_00);
    // REDIRECTED(IncGradGBPalTable_05);
    // REDIRECTED(IncGradGBPalTable_09);

    // home/farcall.c
    // REDIRECTED(FarCall_hl);
    // REDIRECTED(ReturnFarCall);
    // REDIRECTED(FarCall_JumpToHL);
    // REDIRECTED(FarCall_de);
    // REDIRECTED(FarCall_JumpToDE);

    // home/flag.c
    // REDIRECTED(xor_a);
    // REDIRECTED(xor_a_dec_a);
    // REDIRECTED(ResetMapBufferEventFlags);
    // REDIRECTED(FlagAction);
    // REDIRECTED(ResetFlashIfOutOfCave);
    // REDIRECTED(CheckReceivedDex);
    // REDIRECTED(ResetBikeFlags);
    // REDIRECTED(CheckFieldDebug);
    // REDIRECTED(EventFlagAction);
    // REDIRECTED(CheckBPressedDebug);

    // home/game_time.c
    // REDIRECTED(ResetGameTime);
    // REDIRECTED(GameTimer);

    // home/gfx.c
    REDIRECTED(Get2bppViaHDMA);
    REDIRECTED(LoadFontsExtra);
    REDIRECTED(SafeHDMATransfer);
    REDIRECTED(Copy2bpp);
    REDIRECTED(DecompressRequest2bpp);
    REDIRECTED(UpdatePlayerSprite);
    REDIRECTED(LoadStandardFont);
    REDIRECTED(Request1bpp);
    REDIRECTED(Request2bpp);
    REDIRECTED(Get1bppViaHDMA);
    REDIRECTED(Copy1bpp);
    REDIRECTED(LoadFontsBattleExtra);
    REDIRECTED(FarCopyBytes);
    REDIRECTED(FarCopyBytesDouble_DoubleBankSwitch);
    REDIRECTED(Get2bpp);
    REDIRECTED(LoadFontsExtra2);
    REDIRECTED(FarCopyBytesDouble);
    REDIRECTED(Get1bpp);

    // home/header.c
    CONVERTED(Bankswitch);
    // REDIRECTED(FarCall);
    // REDIRECTED(Start);
    CONVERTED(JumpTable);

    // home/hm_moves.c
    // REDIRECTED(IsHM);
    // REDIRECTED(IsHMMove);

    // home/init.c
    REDIRECTED(ClearsScratch);
    REDIRECTED(ClearWRAM);
    REDIRECTED(Reset);
    REDIRECTED(ClearVRAM);
    REDIRECTED(Init);
    REDIRECTED(v_Start);

    // home/item.c
    // REDIRECTED(ReceiveItem);
    // REDIRECTED(CheckTossableItem);
    // REDIRECTED(CheckItem);
    // REDIRECTED(DoItemEffect);
    // REDIRECTED(TossItem);

    // home/joypad.c
    // REDIRECTED(ClearJoypad);
    // REDIRECTED(Joypad);
    // REDIRECTED(StopAutoInput);
    // REDIRECTED(UpdateJoypad);
    // REDIRECTED(JoyTitleScreenInput);
    // REDIRECTED(JoyTextDelay);
    // REDIRECTED(PromptButton);
    // REDIRECTED(GetJoypad);
    // REDIRECTED(SimpleWaitPressAorB);
    // REDIRECTED(JoyWaitAorB);
    // REDIRECTED(BlinkCursor);
    // REDIRECTED(WaitPressAorB_BlinkCursor);
    // REDIRECTED(WaitButton);
    // REDIRECTED(StartAutoInput);

    // home/lcd.c
    // REDIRECTED(Function547);
    // REDIRECTED(DisableLCD);
    // REDIRECTED(EnableLCD);
    CONVERTED(LCD);

    // home/map_objects.c
    // REDIRECTED(GetSpriteVTile);
    // REDIRECTED(SetSpriteDirection);
    // REDIRECTED(CheckIceTile);
    // REDIRECTED(GetPlayerStandingTile);
    // REDIRECTED(ApplyDeletionToMapObject);
    // REDIRECTED(GetSpritePalette);
    // REDIRECTED(DeleteObjectStruct);
    // REDIRECTED(DoesObjectHaveASprite);
    // REDIRECTED(CheckSuperTallGrassTile);
    // REDIRECTED(CheckWhirlpoolTile);
    // REDIRECTED(ResetVramState_Bit0);
    // REDIRECTED(CheckObjectVisibility);
    // REDIRECTED(CheckCounterTile);
    // REDIRECTED(GetSpriteMovementFunction);
    // REDIRECTED(CopyPlayerObjectTemplate);
    // REDIRECTED(GetSpriteDirection);
    // REDIRECTED(DeleteFollowerMapObject);
    // REDIRECTED(CopyMapObjectStruct);
    // REDIRECTED(CheckGrassTile);
    // REDIRECTED(GetMapObject);
    // REDIRECTED(CheckOnWater);
    // REDIRECTED(CheckHeadbuttTreeTile);
    // REDIRECTED(CheckStandingOnEntrance);
    // REDIRECTED(SetVramState_Bit0);
    // REDIRECTED(CopySpriteMovementData);
    // REDIRECTED(GetObjectStruct);
    // REDIRECTED(DoesSpriteHaveFacings);
    // REDIRECTED(CheckCutTreeTile);
    // REDIRECTED(LoadMovementDataPointer);
    // REDIRECTED(CheckObjectTime);
    // REDIRECTED(CheckPitTile);
    // REDIRECTED(GetTileCollision);
    // REDIRECTED(v_GetMovementByte);
    // REDIRECTED(UpdateSprites);
    // REDIRECTED(UnmaskCopyMapObjectStruct);
    // REDIRECTED(GetInitialFacing);
    // REDIRECTED(FindFirstEmptyObjectStruct);
    // REDIRECTED(CheckWaterfallTile);

    // home/math.c
    // REDIRECTED(Divide);
    // REDIRECTED(SimpleMultiply);
    // REDIRECTED(SimpleDivide);
    // REDIRECTED(Multiply);
    // REDIRECTED(SubtractAbsolute);

    // home/menu.c
    // REDIRECTED(InterpretBattleMenu);
    // REDIRECTED(HideCursor);
    // REDIRECTED(LoadStandardMenuHeader);
    // REDIRECTED(MenuTextbox);
    // REDIRECTED(PlayClickSFX);
    // REDIRECTED(SetUpMenu);
    // REDIRECTED(PlaceHollowCursor);
    // REDIRECTED(CopyMenuHeader);
    // REDIRECTED(DrawVariableLengthMenuBox);
    // REDIRECTED(PlaceMenuStrings);
    // REDIRECTED(PlaceVerticalMenuItems);
    // REDIRECTED(GetMenuDataPointerTableEntry);
    // REDIRECTED(PlaceGenericTwoOptionBox);
    // REDIRECTED(PushWindow);
    // REDIRECTED(MenuClickSound);
    // REDIRECTED(RestoreTileBackup);
    // REDIRECTED(ClearWholeMenuBox);
    // REDIRECTED(Place2DMenuItemName);
    // REDIRECTED(v_OffsetMenuHeader);
    // REDIRECTED(GetWindowStackTop);
    // REDIRECTED(GetMenu2);
    // REDIRECTED(GetStaticMenuJoypad);
    // REDIRECTED(GetScrollingMenuJoypad);
    // REDIRECTED(Coord2Tile);
    // REDIRECTED(PlaceYesNoBox);
    // REDIRECTED(InterpretTwoOptionMenu);
    // REDIRECTED(InitVerticalMenuCursor);
    // REDIRECTED(YesNoMenuHeader);
    // REDIRECTED(MenuTextboxBackup);
    // REDIRECTED(LoadMenuTextbox);
    // REDIRECTED(DoNthMenu);
    // REDIRECTED(MenuBox);
    // REDIRECTED(LoadMenuHeader);
    // REDIRECTED(MenuBoxCoord2Attr);
    // REDIRECTED(GetMenuTextStartCoord);
    // REDIRECTED(Call_ExitMenu);
    // REDIRECTED(InterpretMobileMenu);
    // REDIRECTED(CloseWindow);
    // REDIRECTED(StaticMenuJoypad);
    // REDIRECTED(GetNthMenuStrings);
    // REDIRECTED(OffsetMenuHeader);
    // REDIRECTED(MenuTextboxWaitButton);
    // REDIRECTED(RunMenuItemPrintingFunction);
    // REDIRECTED(InitMenuCursorAndButtonPermissions);
    // REDIRECTED(Load2DMenuData);
    // REDIRECTED(VerticalMenu);
    // REDIRECTED(GetMenuJoypad);
    // REDIRECTED(MenuJumptable);
    // REDIRECTED(ExitMenu);
    // REDIRECTED(CopyMenuData);
    // REDIRECTED(GetMenuBoxDims);
    // REDIRECTED(ScrollingMenuJoypad);
    // REDIRECTED(YesNoBox);
    // REDIRECTED(Coord2Attr);
    // REDIRECTED(AutomaticGetMenuBottomCoord);
    // REDIRECTED(ContinueGettingMenuJoypad);
    // REDIRECTED(v_YesNoBox);
    // REDIRECTED(v_2DMenu);
    // REDIRECTED(MenuWriteText);
    // REDIRECTED(ClearMenuBoxInterior);
    // REDIRECTED(PopWindow);
    // REDIRECTED(Menu_DummyFunction);
    // REDIRECTED(MenuBoxCoord2Tile);
    // REDIRECTED(CopyNameFromMenu);
    // REDIRECTED(GetMenuIndexSet);
    // REDIRECTED(PlaceNthMenuStrings);
    // REDIRECTED(StoreMenuCursorPosition);
    // REDIRECTED(ClearWindowData);

    // home/mobile.c
    // REDIRECTED(Function3f9f);
    // REDIRECTED(Function3f7c);
    // REDIRECTED(ReturnMobileAPI);
    // REDIRECTED(Function3f35);
    // REDIRECTED(MobileTimer);
    // REDIRECTED(Function3ed7);
    // REDIRECTED(MobileAPI);
    // REDIRECTED(Function3eea);
    // REDIRECTED(Function3efd);
    // REDIRECTED(Function3f20);
    // REDIRECTED(MobileHome_PlaceBox);
    // REDIRECTED(Function3f88);
    // REDIRECTED(MobileReceive);

    // home/movement.c
    // REDIRECTED(ComputePathToWalkToPlayer);
    // REDIRECTED(DecrementMovementBufferCount);
    // REDIRECTED(InitMovementBuffer);
    // REDIRECTED(AppendToMovementBufferNTimes);
    // REDIRECTED(AppendToMovementBuffer);

    // home/names.c
    // REDIRECTED(GetItemName);
    // REDIRECTED(GetMoveName);
    // REDIRECTED(GetBasePokemonName);
    // REDIRECTED(GetPokemonName);
    // REDIRECTED(GetName);
    // REDIRECTED(GetTMHMName);
    // REDIRECTED(GetNthString);
    // REDIRECTED(NamesPointers);

    // home/palettes.c
    // REDIRECTED(UpdatePalsIfCGB);
    // REDIRECTED(ClearVBank1);
    // REDIRECTED(DmgToCgbObjPal0);
    // REDIRECTED(UpdateCGBPals);
    // REDIRECTED(DmgToCgbBGPals);
    // REDIRECTED(DmgToCgbObjPals);
    // REDIRECTED(CopyPals);
    // REDIRECTED(SwapTextboxPalettes);
    // REDIRECTED(ScrollBGMapPalettes);
    // REDIRECTED(ForceUpdateCGBPals);
    // REDIRECTED(DmgToCgbObjPal1);
    // REDIRECTED(ReloadSpritesNoPalettes);
    // REDIRECTED(GSReloadPalettes);

    // home/pokedex_flags.c
    // REDIRECTED(CheckCaughtMon);
    // REDIRECTED(PokedexFlagAction);
    // REDIRECTED(SetSeenAndCaughtMon);
    // REDIRECTED(GetWeekday);
    // REDIRECTED(CheckSeenMon);
    // REDIRECTED(CountSetBits);
    // REDIRECTED(SetSeenMon);

    // home/pokemon.c
    // REDIRECTED(PlayStereoCry);
    // REDIRECTED(PlayMonCry);
    // REDIRECTED(GetBaseData);
    // REDIRECTED(v_PlayMonCry);
    // REDIRECTED(PrepMonFrontpic);
    // REDIRECTED(GetCryIndex);
    // REDIRECTED(GetNthMove);
    // REDIRECTED(GetCurNickname);
    // REDIRECTED(LoadCry);
    // REDIRECTED(IsAPokemon);
    // REDIRECTED(PlayStereoCry2);
    // REDIRECTED(PrintLevel_Force3Digits);
    // REDIRECTED(GetNickname);
    // REDIRECTED(PlayMonCry2);
    // REDIRECTED(Print8BitNumLeftAlign);
    // REDIRECTED(DrawBattleHPBar);
    // REDIRECTED(v_PrepMonFrontpic);
    // REDIRECTED(PrintLevel);

    // home/predef.c
    REDIRECTED(Predef);
    REDIRECTED(Predef_Return);

    // home/print_bcd.c
    // REDIRECTED(PrintBCDNumber);
    // REDIRECTED(PrintBCDDigit);

    // home/printer.c
    // REDIRECTED(PrinterReceive);
    // REDIRECTED(AskSerial);

    // home/print_text.c
    // REDIRECTED(CopyDataUntil);
    // REDIRECTED(PrintNum);
    // REDIRECTED(FarPrintText);
    // REDIRECTED(MobilePrintNum);
    // REDIRECTED(PrintLetterDelay);
    // REDIRECTED(CallPointerAt);

    // home/queue_script.c
    // REDIRECTED(FarQueueScript);
    // REDIRECTED(QueueScript);

    // home/random.c
    // REDIRECTED(BattleRandom);
    // REDIRECTED(Random);
    // REDIRECTED(RandomRange);

    // home/region.c
    // REDIRECTED(IsInJohto);
    // REDIRECTED(SetXYCompareFlags);

    // home/scrolling_menu.c
    // REDIRECTED(InitScrollingMenu);
    // REDIRECTED(JoyTextDelay_ForcehJoyDown);
    // REDIRECTED(ScrollingMenu);

    // home/serial.c
    // REDIRECTED(Serial);
    // REDIRECTED(Serial_PrintWaitingTextAndSyncAndExchangeNybble);
    // REDIRECTED(Serial_SyncAndExchangeNybble);
    // REDIRECTED(Serial_ExchangeByte);
    // REDIRECTED(WaitLinkTransfer);
    // REDIRECTED(Serial_ExchangeSyncBytes);
    // REDIRECTED(SerialDisconnected);
    // REDIRECTED(LinkDataReceived);
    // REDIRECTED(CheckLinkTimeoutFramesNonzero);
    // REDIRECTED(Serial_ExchangeBytes);
    // REDIRECTED(LinkTransfer);
    // REDIRECTED(SetBitsForTimeCapsuleRequestIfNotLinked);

    // home/sine.c
    // REDIRECTED(Cosine);
    // REDIRECTED(Sine);

    // home/sprite_anims.c
    // REDIRECTED(InitSpriteAnimStruct);
    // REDIRECTED(ReinitSpriteAnimFrame);

    // home/sprite_updates.c
    // REDIRECTED(DisableSpriteUpdates);
    // REDIRECTED(EnableSpriteUpdates);

    // home/sram.c
    REDIRECTED(CloseSRAM);
    REDIRECTED(OpenSRAM);

    // home/stone_queue.c
    // REDIRECTED(HandleStoneQueue);

    // home/string.c
    // REDIRECTED(InitName);
    // REDIRECTED(InitString);
    // REDIRECTED(v_InitString);

    // home/text.c
    // REDIRECTED(PlaceWatashiText);
    // REDIRECTED(String_Space);
    // REDIRECTED(PlaceNextChar);
    // REDIRECTED(TextCommand_RAM);
    // REDIRECTED(TextCommand_STRINGBUFFER);
    // REDIRECTED(TextboxPalette);
    // REDIRECTED(v_ContText);
    // REDIRECTED(CheckDict);  // Manualy convert?
    // REDIRECTED(PCChar);
    // REDIRECTED(PlaceString);
    // REDIRECTED(LineFeedChar);
    // REDIRECTED(TextCommand_SOUND);
    // REDIRECTED(Paragraph);
    // REDIRECTED(PokeFluteTerminator);
    // REDIRECTED(Diacritic);
    // REDIRECTED(PlaceMoveTargetsName);
    // REDIRECTED(TMCharText);
    // REDIRECTED(TextCommand_START);
    // REDIRECTED(PlaceKokoWaText);
    // REDIRECTED(PlacePOKe);
    // REDIRECTED(LineChar);
    // REDIRECTED(TextCommand_FAR);
    // REDIRECTED(TrainerCharText);
    // REDIRECTED(KougekiText);
    // REDIRECTED(PlacePOKEText);
    // REDIRECTED(NextChar);
    // REDIRECTED(PlacePKMNText);
    // REDIRECTED(PlaceJPRouteText);
    // REDIRECTED(TMChar);
    // REDIRECTED(PlaceJPRoute);
    // REDIRECTED(RocketCharText);
    // REDIRECTED(MobileScriptChar);
    // REDIRECTED(TextCommand_SCROLL);
    // REDIRECTED(PlaceBattlersName);
    // REDIRECTED(TextSFX);
    // REDIRECTED(NextLineChar);
    // REDIRECTED(TextboxBorder);
    // REDIRECTED(TextCommand_PROMPT_BUTTON);
    // REDIRECTED(v_ContTextNoPause);
    // REDIRECTED(CarriageReturnChar);
    // REDIRECTED(UnloadBlinkingCursor);
    // REDIRECTED(Text_WaitBGMap);
    // REDIRECTED(PlaceGenderedPlayerName);
    // REDIRECTED(PlaceWatashi);
    // REDIRECTED(PlacePOKeText);
    // REDIRECTED(FillBoxWithByte);
    // REDIRECTED(GameFreakText);
    // REDIRECTED(TextCommand_DOTS);
    // REDIRECTED(NullChar);
    // REDIRECTED(PlaceDexEnd);
    // REDIRECTED(TextCommand_MOVE);
    // REDIRECTED(PrintText);
    // REDIRECTED(Textbox);
    // REDIRECTED(SixDotsChar);
    // REDIRECTED(PlaceKokoWa);
    // REDIRECTED(PlaceCommandCharacter);
    // REDIRECTED(TextCommand_BCD);
    // REDIRECTED(TextCommand_LOW);
    // REDIRECTED(TextCommand_WAIT_BUTTON);
    // REDIRECTED(SpeechTextbox);
    // REDIRECTED(BuenaPrintText);
    // REDIRECTED(PlaceKougeki);
    // REDIRECTED(SixDotsCharText);
    // REDIRECTED(LoadBlinkingCursor);
    REDIRECTED(DoTextUntilTerminator);
    REDIRECTED(DoTextUntilTerminator_TextCommand);
    // REDIRECTED(ContText);
    // REDIRECTED(PrintPlayerName);
    // REDIRECTED(DummyChar);
    // REDIRECTED(RocketChar);
    // REDIRECTED(TextCommand_START_ASM);
    // REDIRECTED(PrintRivalName);
    // REDIRECTED(PlaceFarString);
    // REDIRECTED(ClearScreen);
    // REDIRECTED(PlaceHLTextAtBC);
    // REDIRECTED(PlaceMoveUsersName);
    // REDIRECTED(PCCharText);
    // REDIRECTED(ClearBox);
    // REDIRECTED(PrintRedsName);
    // REDIRECTED(EnemyText);
    // REDIRECTED(TextCommand_DECIMAL);
    // REDIRECTED(PrintGreensName);
    // REDIRECTED(TextCommand_CRY);
    // REDIRECTED(RadioTerminator);
    // REDIRECTED(TextCommand_PAUSE);
    // REDIRECTED(TrainerChar);
    // REDIRECTED(TextScroll);
    // REDIRECTED(TextCommand_DAY);
    // REDIRECTED(PromptText);
    // REDIRECTED(PlaceEnemysName);
    // REDIRECTED(DoneText);
    // REDIRECTED(ChanSuffixText);
    // REDIRECTED(TextCommands);
    // REDIRECTED(SetUpTextbox);
    // REDIRECTED(KunSuffixText);
    // REDIRECTED(TextCommand_BOX);
    // REDIRECTED(ClearTilemap);
    // REDIRECTED(PlacePOKE);
    // REDIRECTED(PlacePKMN);
    // REDIRECTED(PrintMomsName);
    // REDIRECTED(PrintTextboxText);

    // home/time.c
    // REDIRECTED(GetClock);
    // REDIRECTED(LatchClock);
    // REDIRECTED(FixDays);
    // REDIRECTED(UpdateTime);
    // REDIRECTED(Timer);
    // REDIRECTED(FixTime);
    // REDIRECTED(InitDayOfWeek);
    // REDIRECTED(RecordRTCStatus);
    // REDIRECTED(InitTimeOfDay);
    // REDIRECTED(ClearClock);
    // REDIRECTED(SetClock);
    // REDIRECTED(CheckRTCStatus);
    // REDIRECTED(ClearRTCStatus);
    // REDIRECTED(InitTime);

    // home/time_palettes.c
    // REDIRECTED(UpdateTimeAndPals);
    // REDIRECTED(TimeOfDayPals);
    // REDIRECTED(UpdateTimePals);

    // home/trainers.c
    // REDIRECTED(CheckTrainerFlag);
    // REDIRECTED(FacingPlayerDistance_bc);
    // REDIRECTED(TalkToTrainer);
    // REDIRECTED(LoadTrainer_continue);
    // REDIRECTED(FacingPlayerDistance);
    // REDIRECTED(PrintWinLossText);
    // REDIRECTED(v_CheckTrainerBattle);
    // REDIRECTED(CheckTrainerBattle);

    // home/vblank.c
    REDIRECTED(VBlank3);
    REDIRECTED(VBlank1);
    REDIRECTED(UpdatePals);
    REDIRECTED(VBlank2);
    REDIRECTED(VBlank);
    REDIRECTED(VBlank0);
    REDIRECTED(VBlank5);
    REDIRECTED(VBlank6);
    REDIRECTED(VBlank4);

    // home/video.c
    REDIRECTED(WaitTop);
    REDIRECTED(DMATransfer);
    REDIRECTED(UpdateBGMapBuffer);
    REDIRECTED(Serve1bppRequest);
    REDIRECTED(UpdateBGMap);
    REDIRECTED(v_Serve2bppRequest);
    REDIRECTED(Serve2bppRequest_VBlank);
    REDIRECTED(Serve2bppRequest);
    REDIRECTED(AnimateTileset);

    // home/window.c
    REDIRECTED(CloseText);
    REDIRECTED(SafeUpdateSprites);
    REDIRECTED(RefreshScreen);
    REDIRECTED(OpenText);
    REDIRECTED(SetCarryFlag);
    REDIRECTED(v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);

    // home/tilemap.c
    REDIRECTED(IsCGB);
    REDIRECTED(SetHPPal);
    REDIRECTED(WaitBGMap);
    REDIRECTED(CGBOnly_CopyTilemapAtOnce);
    REDIRECTED(v_CopyTilemapAtOnce);
    REDIRECTED(v_CopyTilemapAtOnce_CopyBGMapViaStack);
    REDIRECTED(SetPalettes);
    REDIRECTED(ClearBGPalettes);
    REDIRECTED(CopyTilemapAtOnce);
    REDIRECTED(CopyAttrmapAndTilemapToWRAMBank3);
    REDIRECTED(GetMemSGBLayout);
    REDIRECTED(GetHPPal);
    REDIRECTED(GetSGBLayout);
    REDIRECTED(ApplyTilemap);
    REDIRECTED(WaitBGMap2);
    REDIRECTED(ClearPalettes);

    // engine/menus/savemenu_copytilemapatonce.c
    REDIRECTED(SaveMenu_CopyTilemapAtOnce);
    REDIRECTED(SaveMenu_CopyTilemapAtOnce_CopyBGMapViaStack);

    // engine/overworld/map_objects.c
    REDIRECTED(StepFunction_PlayerJump);
    REDIRECTED(StepFunction_14);
    // REDIRECTED(TryResetPlayerAction);
    // REDIRECTED(GetIndexedMovementByte1);
    // REDIRECTED(WaitStep_InPlace);
    // REDIRECTED(GetIndexedMovementByte2);
    // REDIRECTED(v_ContinueSpawnFacing);
    // REDIRECTED(MovementFunction_Indexed2);
    // REDIRECTED(MovementFunction_RandomWalkXY);
    // REDIRECTED(FreezeAllObjects);
    // REDIRECTED(GetMovementByte);
    // REDIRECTED(GetFollowerNextMovementByte);
    // REDIRECTED(UpdateJumpPosition);
    // REDIRECTED(InitSprites);
    // REDIRECTED(MovementFunction_0a);
    // REDIRECTED(StepVectors);
    // REDIRECTED(MovementFunction_Indexed1);
    // REDIRECTED(v_MovementSpinNextFacing);
    // REDIRECTED(SetFacing_Standing);
    // REDIRECTED(UpdateObjectNextTile);
    // REDIRECTED(CopyStandingCoordsTileToNextCoordsTile);
    // REDIRECTED(UpdatePlayerStep);
    REDIRECTED(StepFunction_TeleportTo);
    // REDIRECTED(ResetStepVector);
    // REDIRECTED(UpdateAllObjectsFrozen);
    REDIRECTED(StepFunction_Restore);
    // REDIRECTED(CallObjectAction);
    // REDIRECTED(MovementFunction_0d);
    // REDIRECTED(CheckObjectCoveredByTextbox);
    // REDIRECTED(GetMovementObject);
    // REDIRECTED(SetLeaderIfVisible);
    // REDIRECTED(v_MovementSpinRepeat);
    // REDIRECTED(InitTempObject);
    // REDIRECTED(HandleMovementData);
    REDIRECTED(StepFunction_Reset);
    REDIRECTED(StepFunction_NPCWalk);
    REDIRECTED(StepFunction_TrackingObject);
    // REDIRECTED(ResetLeader);
    REDIRECTED(StepFunction_TeleportFrom);
    // REDIRECTED(UpdateTallGrassFlags);
    // REDIRECTED(RestoreDefaultMovement);
    REDIRECTED(StepFunction_PlayerWalk);
    // REDIRECTED(MovementFunction_RandomWalkX);
    // REDIRECTED(v_MovementSpinTurnRight);
    // REDIRECTED(MovementFunction_Emote);
    // REDIRECTED(RespawnPlayer);
    // REDIRECTED(MovementFunction_ShakingGrass);
    // REDIRECTED(UpdateRespawnedObjectFrozen);
    REDIRECTED(StepFunction_SkyfallTop);
    // REDIRECTED(DoStepsForAllObjects);
    // REDIRECTED(GetStepVector);
    // REDIRECTED(ShakeGrass);
    REDIRECTED(StepFunction_StrengthBoulder);
    // REDIRECTED(AddStepVector);
    // REDIRECTED(DeleteMapObject);
    // REDIRECTED(SpawnInCustomFacing);
    ////REDIRECTED(Field1c_AnonJumptable);
    // REDIRECTED(MovementFunction_Null);
    // REDIRECTED(Stubbed_UpdateYOffset);
    REDIRECTED(StepFunction_NPCJump);
    // REDIRECTED(RespawnPlayerAndOpponent);
    // REDIRECTED(RespawnObject);
    // REDIRECTED(MovementFunction_RandomWalkY);
    REDIRECTED(StepFunction_GotBite);
    REDIRECTED(StepFunction_ContinueWalk);
    // REDIRECTED(MovementFunction_SpinClockwise);
    // REDIRECTED(SpawnStrengthBoulderDust);
    REDIRECTED(StepFunction_Skyfall);
    // REDIRECTED(MovementFunction_RandomSpinFast);
    // REDIRECTED(v_MovementSpinTurnLeft);
    // REDIRECTED(RandomStepDuration_Slow);
    // REDIRECTED(MovementFunction_Follow);
    // REDIRECTED(v_SetRandomStepDuration);
    // REDIRECTED(CopyTempObjectData);
    REDIRECTED(StepFunction_Sleep);
    // REDIRECTED(MovementFunction_0b);
    // REDIRECTED(FreezeObject);
    // REDIRECTED(MovementFunction_Strength);
    // REDIRECTED(FreezeAllOtherObjects);
    // REDIRECTED(MovementFunction_ScreenShake);
    // REDIRECTED(InitMovementField1dField1e);
    // REDIRECTED(GetNextTile);
    // REDIRECTED(ObjectMovementByte_AnonJumptable);
    REDIRECTED(StepFunction_FromMovement);
    // REDIRECTED(ObjectMovementByte_DecAnonJumptableIndex);
    REDIRECTED(StepFunction_ScreenShake);
    // REDIRECTED(DespawnEmote);
    // REDIRECTED(SpawnInFacingDown);
    // REDIRECTED(ResetObject);
    // REDIRECTED(ContinueReadingMovement);
    // REDIRECTED(UnfreezeAllObjects);
    // REDIRECTED(Field1c_IncAnonJumptableIndex);
    // REDIRECTED(ObjectMovementByte_IncAnonJumptableIndex);
    // REDIRECTED(v_GetMovementObject);
    // REDIRECTED(UselessAndA);
    REDIRECTED(StepFunction_DigTo);
    // REDIRECTED(StepTypesJumptable);
    // REDIRECTED(HandleStepType);
    // REDIRECTED(GetStepVectorSign);
    // REDIRECTED(ObjectMovementByte_ZeroAnonJumptableIndex);
    // REDIRECTED(MovementFunction_Shadow);
    // REDIRECTED(HandleObjectAction);
    // REDIRECTED(InitStep);
    REDIRECTED(StepFunction_Bump);
    REDIRECTED(StepFunction_RockSmash);
    // REDIRECTED(GetMapObjectField);
    // REDIRECTED(v_RandomWalkContinue);
    // REDIRECTED(DoMovementFunction);
    // REDIRECTED(CheckObjectStillVisible);
    // REDIRECTED(MovementFunction_RandomSpinSlow);
    // REDIRECTED(v_MovementSpinInit);
    // REDIRECTED(v_UnfreezeFollowerObject);
    // REDIRECTED(SetFollowerIfVisible);
    // REDIRECTED(MovementFunction_Script);
    // REDIRECTED(MovementFunction_SpinCounterclockwise);
    // REDIRECTED(v_CallFrozenObjectAction);
    // REDIRECTED(v_SetPlayerPalette);
    // REDIRECTED(SpawnEmote);
    // REDIRECTED(SpawnShadow);
    // REDIRECTED(Field1c_SetAnonJumptableIndex);
    // REDIRECTED(RefreshPlayerSprite);
    // REDIRECTED(ShakeScreen);
    // REDIRECTED(ResetFollower);
    REDIRECTED(StepFunction_Turn);
    // REDIRECTED(ApplyMovementToFollower);
    // REDIRECTED(RandomStepDuration_Fast);
    // REDIRECTED(ApplyBGMapAnchorToObjects);
    // REDIRECTED(MovementFunction_Standing);
    REDIRECTED(StepFunction_Delete);
    // REDIRECTED(MovementFunction_FollowNotExact);
    // REDIRECTED(MovementFunction_0c);
    // REDIRECTED(Field1c_GetAnonJumptableIndex);
    // REDIRECTED(CheckObjectOnScreen);
    // REDIRECTED(EndSpriteMovement);
    // REDIRECTED(HandleNPCStep);
    // REDIRECTED(CopyNextCoordsTileToStandingCoordsTile);
    // REDIRECTED(MovementFunction_ObeyDPad);
    // REDIRECTED(UnfreezeObject);
    // REDIRECTED(HandleFrozenObjectAction);
    // REDIRECTED(v_UpdateSprites);
    // REDIRECTED(HandleObjectStep);
    // REDIRECTED(MovementFunction_0e);
    // REDIRECTED(SetTallGrassFlags);
    // REDIRECTED(StartFollow);
    REDIRECTED(StepFunction_17);
    // REDIRECTED(MovementFunction_BoulderDust);
    // REDIRECTED(MovementFunction_Bouncing);
    // REDIRECTED(GetPlayerNextMovementByte);
    // REDIRECTED(UpdateObjectFrozen);
    REDIRECTED(StepFunction_Standing);
    // REDIRECTED(Field1c_ZeroAnonJumptableIndex);
    REDIRECTED(StepFunction_16);
    // REDIRECTED(HideAllObjects);
    // REDIRECTED(MovementFunction_BigStanding);
    // REDIRECTED(StopFollow);
    // REDIRECTED(JumpMovementPointer);

    // engine/battle_anims/functions.c
    REDIRECTED(BattleAnimFunction_MoveWaveToTarget);
    REDIRECTED(BattleAnimFunction_FloatUp);
    REDIRECTED(BattleAnimFunction_ThrowFromUserToTargetAndDisappear);
    // REDIRECTED(BattleAnim_Cosine_e);
    REDIRECTED(BattleAnimFunction_MoveFromUserToTargetSpinAround);
    REDIRECTED(BattleAnimFunction_SacredFire);
    REDIRECTED(BattleAnimFunction_PerishSong);
    REDIRECTED(BattleAnimFunction_PsychUp);
    REDIRECTED(BattleAnimFunction_Null);
    REDIRECTED(BattleAnimFunction_Drop);
    REDIRECTED(BattleAnimFunction_SpeedLine);
    REDIRECTED(BattleAnimFunction_SpiralDescent);
    REDIRECTED(BattleAnimFunction_AncientPower);
    // REDIRECTED(BattleAnim_AbsCosinePrecise);
    REDIRECTED(BattleAnimFunction_Agility);
    REDIRECTED(BattleAnimFunction_RapidSpin);
    REDIRECTED(BattleAnimFunction_SwaggerMorningSun);
    REDIRECTED(BattleAnimFunction_BatonPass);
    REDIRECTED(BattleAnimFunction_LeechSeed);
    // REDIRECTED(BattleAnim_Sine_e);
    REDIRECTED(BattleAnimFunction_Recover);
    // REDIRECTED(BattleAnimSineWave);
    REDIRECTED(BattleAnimFunction_Conversion);
    REDIRECTED(BattleAnimFunction_BetaPursuit);
    REDIRECTED(BattleAnimFunction_Horn);
    REDIRECTED(BattleAnimFunction_Bite);
    // REDIRECTED(BattleAnim_Cosine);
    REDIRECTED(BattleAnimFunction_Absorb);
    // REDIRECTED(GetBallAnimPal);
    REDIRECTED(BattleAnimFunction_ConfuseRay);
    REDIRECTED(BattleAnimFunction_SafeguardProtect);
    REDIRECTED(BattleAnimFunction_Ember);
    REDIRECTED(BattleAnimFunction_EncoreBellyDrum);
    REDIRECTED(BattleAnimFunction_Amnesia);
    REDIRECTED(BattleAnimFunction_PokeBallBlocked);
    REDIRECTED(BattleAnimFunction_Spikes);
    REDIRECTED(BattleAnimFunction_Dig);
    REDIRECTED(BattleAnimFunction_Shiny);
    REDIRECTED(BattleAnimFunction_SkyAttack);
    REDIRECTED(BattleAnimFunction_GrowthSwordsDance);
    REDIRECTED(BattleAnimFunction_WaterGun);
    REDIRECTED(BattleAnimFunction_Needle);
    // REDIRECTED(BattleAnim_Sine);
    REDIRECTED(BattleAnimFunction_Sound);
    REDIRECTED(BattleAnimFunction_PoisonGas);
    REDIRECTED(BattleAnimFunction_String);
    REDIRECTED(BattleAnimFunction_FireBlast);
    REDIRECTED(BattleAnimFunction_PokeBall);
    REDIRECTED(BattleAnimFunction_Sludge);
    REDIRECTED(BattleAnimFunction_Surf);
    // REDIRECTED(BattleAnim_AbsSinePrecise);
    // REDIRECTED(BattleAnim_StepThrownToTarget);
    REDIRECTED(BattleAnimFunction_Dizzy);
    REDIRECTED(BattleAnimFunction_ThiefPayday);
    // REDIRECTED(BattleAnim_StepToTarget);
    REDIRECTED(BattleAnimFunction_ThunderWave);
    REDIRECTED(BattleAnimFunction_Cotton);
    REDIRECTED(BattleAnimFunction_Egg);
    REDIRECTED(BattleAnimFunction_MetronomeHand);
    REDIRECTED(BattleAnimFunction_PresentSmokescreen);
    // REDIRECTED(BattleAnim_IncAnonJumptableIndex);
    REDIRECTED(BattleAnimFunction_Wrap);
    REDIRECTED(BattleAnimFunction_RazorLeaf);
    REDIRECTED(BattleAnimFunction_Sing);
    REDIRECTED(BattleAnimFunction_HiddenPower);
    REDIRECTED(BattleAnimFunction_SmokeFlameWheel);
    REDIRECTED(BattleAnimFunction_Paralyzed);
    REDIRECTED(BattleAnimFunction_HealBellNotes);
    REDIRECTED(BattleAnimFunction_Curse);
    REDIRECTED(BattleAnimFunction_Bubble);
    REDIRECTED(BattleAnimFunction_AbsorbCircle);
    // REDIRECTED(DoBattleAnimFrame);
    REDIRECTED(BattleAnimFunction_AnimObjB0);
    // REDIRECTED(BattleAnim_ScatterHorizontal);
    REDIRECTED(BattleAnimFunction_RazorWind);
    REDIRECTED(BattleAnimFunction_Clamp_Encore);
    // REDIRECTED(BattleAnim_StepCircle);
    // REDIRECTED(BattleAnim_AnonJumptable);
    REDIRECTED(BattleAnimFunction_MetronomeSparkleSketch);
    REDIRECTED(BattleAnimFunction_Bonemerang);
    REDIRECTED(BattleAnimFunction_ThrowFromUserToTarget);
    REDIRECTED(BattleAnimFunction_MoveFromUserToTarget);
    REDIRECTED(BattleAnimFunction_LockOnMindReader);
    REDIRECTED(BattleAnimFunction_SolarBeam);
    REDIRECTED(BattleAnimFunction_RockSmash);
    REDIRECTED(BattleAnimFunction_Gust);
    REDIRECTED(BattleAnimFunction_Powder);
    REDIRECTED(BattleAnimFunction_PetalDance);
    REDIRECTED(BattleAnimFunction_StrengthSeismicToss);
    REDIRECTED(BattleAnimFunction_Kick);
    REDIRECTED(BattleAnimFunction_MoveInCircle);
    REDIRECTED(BattleAnimFunction_Shake);
    REDIRECTED(BattleAnimFunction_RainSandstorm);
    REDIRECTED(BattleAnimFunction_MoveUp);
    REDIRECTED(BattleAnimFunction_MoveFromUserToTargetAndDisappear);

    // engine/battle_anims/bg_effects.c
    REDIRECTED(BattleBGEffect_BetaSendOutMon1);
    REDIRECTED(BattleBGEffect_Psychic);
    // REDIRECTED(BGEffects_LoadBGPal1_OBPal0);
    // REDIRECTED(BGEffect_CheckBattleTurn);
    // REDIRECTED(DeformWater);
    REDIRECTED(BattleBGEffect_FlashWhite);
    REDIRECTED(BattleBGEffect_GetNextDMGPal);
    REDIRECTED(BattleBGEffect_SetLCDStatCustoms1);
    REDIRECTED(BattleBGEffect_ReturnMon);
    // REDIRECTED(BattleAnim_ResetLCDStatCustom);
    REDIRECTED(BattleBGEffect_BounceDown);
    REDIRECTED(BattleBGEffects_ClearLYOverrides);
    REDIRECTED(BattleBGEffect_EndWater);
    // REDIRECTED(BattleBGEffects_SetLYOverrides);
    REDIRECTED(BattleBGEffect_Teleport);
    REDIRECTED(BattleBGEffect_WobbleMon);
    // REDIRECTED(VitalThrow_MoveBackwards);
    REDIRECTED(BattleBGEffect_Rollout);
    // REDIRECTED(BGEffect_CheckFlyDigStatus);
    REDIRECTED(BattleBGEffect_FadeMonToBlackRepeating);
    REDIRECTED(BattleBGEffect_GetFirstDMGPal);
    REDIRECTED(BattleBGEffect_HideMon);
    REDIRECTED(BattleBGEffect_ShakeScreenX);
    // REDIRECTED(DeformScreen);
    // REDIRECTED(BGEffect_FillLYOverridesBackup);
    // REDIRECTED(BGEffects_LoadBGPal0_OBPal1);
    REDIRECTED(BattleBGEffect_BodySlam);
    REDIRECTED(BattleBGEffect_CycleOBPalsGrayAndYellow);
    REDIRECTED(BattleBGEffect_FadeMonsToBlackRepeating);
    REDIRECTED(BattleBGEffect_NightShade);
    // REDIRECTED(BGEffect_DisplaceLYOverridesBackup);
    REDIRECTED(BattleBGEffect_WhiteHues);
    // REDIRECTED(Tackle_MoveForward);
    REDIRECTED(BattleBGEffect_WobbleScreen);
    REDIRECTED(BattleBGEffect_FlashContinue);
    REDIRECTED(BattleBGEffect_FlashInverted);
    REDIRECTED(BattleBGEffect_Withdraw);
    REDIRECTED(BattleBGEffect_BattlerObj_1Row);
    REDIRECTED(BattleBGEffect_End);
    // REDIRECTED(BatttleBGEffects_GetNamedJumptablePointer);
    REDIRECTED(BattleBGEffects_AnonJumptable);
    REDIRECTED(BattleBGEffect_CycleMonLightDarkRepeating);
    // REDIRECTED(BattleBGEffects_CheckSGB);
    //  REDIRECTED(BGEffect_RapidCyclePals);
    // REDIRECTED(BattleBGEffects_Cosine);
    //  REDIRECTED(Rollout_FillLYOverridesBackup);
    REDIRECTED(BattleBGEffect_FadeMonToBlack);
    REDIRECTED(BattleBGEffect_Whirlpool);
    REDIRECTED(BattleBGEffect_AcidArmor);
    // REDIRECTED(Tackle_ReturnMove);
    // REDIRECTED(DoBattleBGEffectFunction);
    REDIRECTED(BattleBGEffect_AlternateHues);
    REDIRECTED(BattleBGEffect_Surf);
    REDIRECTED(BattleBGEffect_FlashMonRepeating);
    REDIRECTED(BattleBGEffect_DoubleTeam);
    REDIRECTED(BattleBGEffect_RemoveMon);
    REDIRECTED(BattleBGEffect_EnterMon);
    // REDIRECTED(v_QueueBattleAnimation);
    REDIRECTED(BattleBGEffect_Water);
    REDIRECTED(BattleBGEffect_GetNthDMGPal);
    // REDIRECTED(BattleBGEffects_ResetVideoHRAM);
    //  REDIRECTED(InitSurfWaves);
    REDIRECTED(BattleBGEffects_GetShakeAmount);
    REDIRECTED(BattleBGEffect_BattlerObj_2Row);
    REDIRECTED(BattleBGEffect_FadeMonToLight);
    REDIRECTED(BattleBGEffect_Tackle);
    REDIRECTED(BattleBGEffect_VibrateMon);
    REDIRECTED(BattleBGEffect_VitalThrow);
    REDIRECTED(BattleBGEffect_StartWater);
    // REDIRECTED(QueueBGEffect);
    REDIRECTED(BattleBGEffect_Flail);
    REDIRECTED(BattleBGEffect_Dig);
    // REDIRECTED(ExecuteBGEffects);
    REDIRECTED(BattleBGEffect_BlackHues);
    REDIRECTED(BattleBGEffect_FadeMonToLightRepeating);
    REDIRECTED(BattleBGEffect_WavyScreenFX);
    REDIRECTED(BattleBGEffect_SetLCDStatCustoms2);
    REDIRECTED(BattleBGEffect_WaveDeformMon);
    // REDIRECTED(BattleBGEffects);
    REDIRECTED(BattleBGEffect_CycleBGPals_Inverted);
    REDIRECTED(BattleBGEffect_RapidFlash);
    REDIRECTED(BattleBGEffect_WobblePlayer);
    REDIRECTED(BattleBGEffect_BetaPursuit);
    REDIRECTED(BattleBGEffects_Sine);
    REDIRECTED(BattleBGEffect_FadeMonToWhiteWaitFadeBack);
    REDIRECTED(BattleBGEffect_BetaSendOutMon2);
    REDIRECTED(BattleBGEffect_ShowMon);
    REDIRECTED(BattleBGEffect_FadeMonFromWhite);
    REDIRECTED(BattleBGEffect_RunPicResizeScript);
    // REDIRECTED(EndBattleBGEffect);
    REDIRECTED(BattleBGEffect_CycleMidOBPalsGrayAndYellow);
    REDIRECTED(BattleBGEffect_ShakeScreenY);
    // REDIRECTED(BattleBGEffects_IncAnonJumptableIndex);

    // engine/gfx/dma_transfer.c
    // REDIRECTED(HDMATransferAttrmapToWRAMBank3);
    REDIRECTED(v_continue_HDMATransfer);
    REDIRECTED(HDMATransfer_NoDI);
    // REDIRECTED(HDMATransfer_OnlyTopFourRows);
    // REDIRECTED(HDMATransfer1bpp);
    // REDIRECTED(Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    // REDIRECTED(WaitDMATransfer);
    // REDIRECTED(HDMATransfer_Wait127Scanlines);
    // REDIRECTED(HDMATransfer2bpp);
    // REDIRECTED(HDMATransfer_Wait123Scanlines_toBGMap);
    // REDIRECTED(HDMATransferAttrmapAndTilemapToWRAMBank3);
    // REDIRECTED(HDMATransfer_Wait123Scanlines);
    // REDIRECTED(HDMATransferToWRAMBank3);
    // REDIRECTED(Function1040fb);
    // REDIRECTED(Function1040d4);
    // REDIRECTED(HDMATransfer_Wait127Scanlines_toBGMap);
    // REDIRECTED(Mobile_ReloadMapPart);
    // REDIRECTED(PadMapForHDMATransfer);
    // REDIRECTED(HDMATransferTilemapToWRAMBank3);
    // REDIRECTED(ReloadMapPart);
    // REDIRECTED(OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    // REDIRECTED(CallInSafeGFXMode);
    // REDIRECTED(v_LoadHDMAParameters);
    // REDIRECTED(PadAttrmapForHDMATransfer);
    // REDIRECTED(PadTilemapForHDMATransfer);

    // audio/engine.c
    CONVERTED(v_InitSound);
    CONVERTED(MusicFadeRestart);
    CONVERTED(MusicOn);
    CONVERTED(MusicOff);
    CONVERTED(v_UpdateSound);
    CONVERTED(UpdateChannels);
    // CONVERTED(v_CheckSFX);
    CONVERTED(PlayDanger);
    CONVERTED(FadeMusic);
    CONVERTED(LoadNote);
    CONVERTED(HandleTrackVibrato);
    CONVERTED(ApplyPitchSlide);
    CONVERTED(HandleNoise);
    CONVERTED(ReadNoiseSample);
    CONVERTED(ParseMusic);
    CONVERTED(RestoreVolume);
    CONVERTED(ParseSFXOrCry);
    CONVERTED(GetNoiseSample);
    CONVERTED(ParseMusicCommand);
    CONVERTED(Music_Ret);
    CONVERTED(Music_Call);
    CONVERTED(Music_Jump);
    CONVERTED(Music_Loop);
    CONVERTED(Music_SetCondition);
    CONVERTED(Music_JumpIf);
    CONVERTED(MusicEE);
    CONVERTED(MusicNone);
    CONVERTED(MusicE2);
    CONVERTED(Music_Vibrato);
    CONVERTED(Music_PitchSlide);
    CONVERTED(Music_PitchOffset);
    CONVERTED(MusicE7);
    CONVERTED(Music_DutyCyclePattern);
    CONVERTED(MusicE8);
    CONVERTED(Music_ToggleSFX);
    CONVERTED(Music_ToggleNoise);
    CONVERTED(Music_SFXToggleNoise);
    CONVERTED(Music_NoteType);
    CONVERTED(Music_PitchSweep);
    CONVERTED(Music_DutyCycle);
    CONVERTED(Music_VolumeEnvelope);
    CONVERTED(Music_Tempo);
    CONVERTED(Music_Octave);
    CONVERTED(Music_Transpose);
    CONVERTED(Music_StereoPanning);
    CONVERTED(Music_ForceStereoPanning);
    CONVERTED(Music_Volume);
    CONVERTED(Music_TempoRelative);
    CONVERTED(Music_SFXPriorityOn);
    CONVERTED(Music_SFXPriorityOff);
    CONVERTED(Music_RestartChannel);
    CONVERTED(Music_NewSong);
    // CONVERTED(GetMusicByte);
    // CONVERTED(GetFrequency);
    // CONVERTED(SetNoteDuration);
    // CONVERTED(SetGlobalTempo);
    CONVERTED(StartChannel);
    CONVERTED(SetLRTracks);
    // CONVERTED(v_PlayMusic);
    CONVERTED(v_PlayCry);
    CONVERTED(v_PlaySFX);
    CONVERTED(PlayStereoSFX);
    // CONVERTED(LoadChannel);
    // CONVERTED(ChannelInit);
    // CONVERTED(LoadMusicByte);
    CONVERTED(GetLRTracks);
    CONVERTED(ClearChannels);
    // CONVERTED(ClearChannel);
    REDIRECTED(PlayTrainerEncounterMusic);

    // home/map.c
    REDIRECTED(ClearBGMapBuffer);
    REDIRECTED(UpdateBGMapColumn);
    // REDIRECTED(ReadMapScripts);
    // REDIRECTED(GetAnyMapAttributesBank);
    // REDIRECTED(GetMapScriptsBank);
    // REDIRECTED(ObjectEvent);
    // REDIRECTED(GetFishingGroup);
    // REDIRECTED(ReloadTilesetAndPalettes);
    // REDIRECTED(FillNorthConnectionStrip);
    // REDIRECTED(CopyMapPartial);
    // REDIRECTED(GetMapAttributesPointer);
    // REDIRECTED(BackupBGMapColumn);
    // REDIRECTED(SaveScreen);
    // REDIRECTED(BGEvent);
    // REDIRECTED(Call_a_de);
    // REDIRECTED(GetBlockLocation);
    // REDIRECTED(GetWarpDestCoords);
    // REDIRECTED(GetMapPointer);
    // REDIRECTED(CopyMapPartialAndAttributes);
    REDIRECTED(GetWorldMapLocation);
    REDIRECTED(GetMapMusic);
    // REDIRECTED(UpdateBGMapRow);
    // REDIRECTED(CheckFacingBGEvent);
    // REDIRECTED(LoadMapTileset);
    // REDIRECTED(CoordinatesEventText);
    // REDIRECTED(LoadMapAttributes_SkipObjects);
    // REDIRECTED(FillWestConnectionStrip);
    // REDIRECTED(ScrollMapRight);
    // REDIRECTED(GetAnyMapTileset);
    // REDIRECTED(ScrollMapLeft);
    // REDIRECTED(SaveScreen_LoadConnection);
    // REDIRECTED(GetDestinationWarpNumber);
    // REDIRECTED(GetMapSceneID);
    // REDIRECTED(ReadCoordEvents);
    // REDIRECTED(GetFacingTileCoord);
    // REDIRECTED(ReadObjectEvents);
    // REDIRECTED(GetAnyMapPointer);
    // REDIRECTED(LoadMapAttributes);
    // REDIRECTED(FinishExitMenu);
    // REDIRECTED(ExecuteCallbackScript);
    // REDIRECTED(FillMapConnections);
    // REDIRECTED(SwitchToMapScriptsBank);
    // REDIRECTED(ReturnToMapFromSubmenu);
    // REDIRECTED(ReadMapEvents);
    // REDIRECTED(ReadBGEvents);
    // REDIRECTED(BGEventText);
    // REDIRECTED(BufferScreen);
    // REDIRECTED(CheckScenes);
    // REDIRECTED(ReadMapSceneScripts);
    REDIRECTED(MapTextbox);
    // REDIRECTED(Map_DummyFunction);
    // REDIRECTED(CopyMapAttributes);
    // REDIRECTED(SwitchToMapAttributesBank);
    // REDIRECTED(ChangeMap);
    // REDIRECTED(LoadMetatiles);
    // REDIRECTED(CheckIndoorMap);
    // REDIRECTED(GetScriptByte);
    // REDIRECTED(BackupBGMapRow);
    // REDIRECTED(ReadWarps);
    // REDIRECTED(OverworldTextModeSwitch);
    // REDIRECTED(GetMapField);
    // REDIRECTED(CheckObjectMask);
    // REDIRECTED(GetCoordTile);
    // REDIRECTED(GetMovementPermissions);
    // REDIRECTED(GetMapConnections);
    // REDIRECTED(GetMapAttributesBank);
    // REDIRECTED(SwitchToAnyMapAttributesBank);
    // REDIRECTED(GetMapTimeOfDay);
    // REDIRECTED(CheckWarpTile);
    // REDIRECTED(GetMovementData);
    // REDIRECTED(GetPhoneServiceTimeOfDayByte);
    // REDIRECTED(GetCurrentMapSceneID);
    // REDIRECTED(ExitAllMenus);
    // REDIRECTED(CheckIfFacingTileCoordIsBGEvent);
    // REDIRECTED(ClearObjectStructs);
    // REDIRECTED(RunMapCallback);
    // REDIRECTED(GetAnyMapEnvironment);
    // REDIRECTED(LoadConnectionBlockData);
    // REDIRECTED(GetAnyMapField);
    // REDIRECTED(ClearUnusedMapBuffer);
    // REDIRECTED(CheckOutdoorMap);
    // REDIRECTED(LoadMapStatus);
    // REDIRECTED(CopyMapObjectEvents);
    // REDIRECTED(GetMapEnvironment);
    // REDIRECTED(MaskObject);
    // REDIRECTED(CopyWarpData);
    // REDIRECTED(LoadTilesetGFX);
    // REDIRECTED(CloseSubmenu);
    // REDIRECTED(CheckUnknownMap);
    // REDIRECTED(CallMapScript);
    // REDIRECTED(UnmaskObject);
    // REDIRECTED(ScrollMapUp);
    // REDIRECTED(LoadMapPart);
    // REDIRECTED(GetMapPhoneService);
    // REDIRECTED(FillSouthConnectionStrip);
    // REDIRECTED(ScrollMapDown);
    // REDIRECTED(GetMapConnection);
    // REDIRECTED(GetAnyMapBlocksBank);
    // REDIRECTED(ReadMapCallbacks);
    // REDIRECTED(CallScript);
    // REDIRECTED(CoordinatesEvent);
    // REDIRECTED(ReturnToMapWithSpeechTextbox);
    // REDIRECTED(FadeToMenu);
    // REDIRECTED(LoadBlockData);
    // REDIRECTED(DummyEndPredef);
    // REDIRECTED(CheckCurrentMapCoordEvents);
    // REDIRECTED(FillEastConnectionStrip);
    // REDIRECTED(WarpCheck);
    // REDIRECTED(ObjectEventText);
}
