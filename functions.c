#include "functions.h"

#define ROM_SIZE 0x200000
void init_function_pointers(void) {
    for (int i = 0; i < ROM_SIZE; i++) redirectFunc[i] = convertedFunc[i] = NULL;

    // home/array.c
    REDIRECTED(AddNTimes);
    REDIRECTED(IsInArray);
    REDIRECTED(SkipNames);

    // home/audio.c
    REDIRECTED(MaxVolume);
    REDIRECTED(PlayMusic2);
    REDIRECTED(MinVolume);
    // CONVERTED(RestartMapMusic);
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
    CONVERTED(InitSound);
    REDIRECTED(TryRestartMapMusic);
    CONVERTED(FadeInToMusic);
    CONVERTED(PlayMapMusicBike);
    CONVERTED(WaitSFX);
    // CONVERTED(PlayMapMusic);
    REDIRECTED(PlayMusic);
    REDIRECTED(FadeToMapMusic);
    REDIRECTED(PlayCry);
    REDIRECTED(SkipMusic);
    REDIRECTED(CheckSFX);
    REDIRECTED(ChannelsOff);
    REDIRECTED(SFXChannelsOff);

    // home/battle.c
    // REDIRECTED(UpdateBattleHuds);
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
    REDIRECTED(HideSprites);
    REDIRECTED(ClearSprites);

    // home/compare.c
    REDIRECTED(CompareBytesLong);
    REDIRECTED(CompareBytes);

    // home/copy.c
    REDIRECTED(GetFarWRAMWord);
    REDIRECTED(GetFarByte);
    REDIRECTED(FarCopyWRAM);
    REDIRECTED(CopyBytes);
    REDIRECTED(GetFarWRAMByte);
    REDIRECTED(ByteFill);
    REDIRECTED(SwapBytes);
    REDIRECTED(GetFarWord);

    // home/copy_name.c
    // REDIRECTED(CopyName1);
    // REDIRECTED(CopyName2);

    // home/copy_tilemap.c
    REDIRECTED(LoadTilemapToTempTilemap);
    REDIRECTED(LoadTempTilemapToTilemap);
    REDIRECTED(SafeLoadTempTilemapToTilemap);

    // home/decompress.c
    CONVERTED(Decompress);
    REDIRECTED(FarDecompress);

    // home/delay.c
    CONVERTED(DelayFrame);
    CONVERTED(DelayFrames);

    // home/double_speed.c
    // REDIRECTED(DoubleSpeed);
    // REDIRECTED(NormalSpeed);
    // REDIRECTED(SwitchSpeed);

    // home/fade.c
    // REDIRECTED(TimeOfDayFade);
    REDIRECTED(RotateThreePalettesRight);
    // REDIRECTED(IncGradGBPalTable_04);
    REDIRECTED(RotateFourPalettesRight);
    // REDIRECTED(IncGradGBPalTable_14);
    // REDIRECTED(IncGradGBPalTable_12);
    REDIRECTED(RotateThreePalettesLeft);
    // REDIRECTED(IncGradGBPalTable_02);
    // REDIRECTED(IncGradGBPalTable_08);
    // REDIRECTED(IncGradGBPalTable_07);
    // REDIRECTED(IncGradGBPalTable_03);
    // REDIRECTED(IncGradGBPalTable_06);
    // REDIRECTED(IncGradGBPalTable_11);
    // REDIRECTED(IncGradGBPalTable_01);
    // REDIRECTED(IncGradGBPalTable_10);
    // REDIRECTED(IncGradGBPalTable_15);
    REDIRECTED(RotatePalettesLeft);
    REDIRECTED(RotatePalettesRight);
    // REDIRECTED(IncGradGBPalTable_13);
    REDIRECTED(RotateFourPalettesLeft);
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
    CONVERTED(UpdatePlayerSprite);
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
    // CONVERTED(Bankswitch);
    // REDIRECTED(FarCall);
    // REDIRECTED(Start);
    // CONVERTED(JumpTable);

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
    REDIRECTED(BlinkCursor);
    REDIRECTED(WaitPressAorB_BlinkCursor);
    // REDIRECTED(WaitButton);
    // REDIRECTED(StartAutoInput);

    // home/lcd.c
    // REDIRECTED(Function547);
    CONVERTED(DisableLCD);
    CONVERTED(EnableLCD);
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
    CONVERTED(UpdateSprites);
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
    REDIRECTED(ClearWindowData);

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
    REDIRECTED(GetMoveName);
    // REDIRECTED(GetBasePokemonName);
    // REDIRECTED(GetPokemonName);
    // REDIRECTED(GetName);
    // REDIRECTED(GetTMHMName);
    // REDIRECTED(GetNthString);
    // REDIRECTED(NamesPointers);

    // home/palettes.c
    REDIRECTED(UpdatePalsIfCGB);
    REDIRECTED(ClearVBank1);
    // REDIRECTED(DmgToCgbObjPal0);
    REDIRECTED(UpdateCGBPals);
    REDIRECTED(DmgToCgbBGPals);
    REDIRECTED(DmgToCgbObjPals);
    REDIRECTED(CopyPals);
    // REDIRECTED(SwapTextboxPalettes);
    // REDIRECTED(ScrollBGMapPalettes);
    REDIRECTED(ForceUpdateCGBPals);
    // REDIRECTED(DmgToCgbObjPal1);
    // REDIRECTED(ReloadSpritesNoPalettes);
    CONVERTED(GSReloadPalettes);

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
    REDIRECTED(PrintBCDNumber);
    REDIRECTED(PrintBCDDigit);

    // home/printer.c
    // REDIRECTED(PrinterReceive);
    // REDIRECTED(AskSerial);

    // home/print_text.c
    REDIRECTED(CopyDataUntil);
    REDIRECTED(PrintNum);
    REDIRECTED(FarPrintText);
    REDIRECTED(MobilePrintNum);
    REDIRECTED(PrintLetterDelay);
    REDIRECTED(CallPointerAt);

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
    REDIRECTED(Cosine);
    REDIRECTED(Sine);

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
    REDIRECTED(TextCommand_RAM);
    REDIRECTED(TextCommand_STRINGBUFFER);
    // REDIRECTED(TextboxPalette);
    // REDIRECTED(v_ContText);
    // REDIRECTED(CheckDict);  // Manualy convert?
    // REDIRECTED(PCChar);
    // REDIRECTED(PlaceString);
    // REDIRECTED(LineFeedChar);
    REDIRECTED(TextCommand_SOUND);
    // REDIRECTED(Paragraph);
    // REDIRECTED(PokeFluteTerminator);
    // REDIRECTED(Diacritic);
    // REDIRECTED(PlaceMoveTargetsName);
    // REDIRECTED(TMCharText);
    REDIRECTED(TextCommand_START);
    // REDIRECTED(PlaceKokoWaText);
    // REDIRECTED(PlacePOKe);
    // REDIRECTED(LineChar);
    REDIRECTED(TextCommand_FAR);
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
    REDIRECTED(TextCommand_SCROLL);
    // REDIRECTED(PlaceBattlersName);
    // REDIRECTED(TextSFX);
    // REDIRECTED(NextLineChar);
    // REDIRECTED(TextboxBorder);
    REDIRECTED(TextCommand_PROMPT_BUTTON);
    // REDIRECTED(v_ContTextNoPause);
    // REDIRECTED(CarriageReturnChar);
    CONVERTED(UnloadBlinkingCursor);
    // REDIRECTED(Text_WaitBGMap);
    // REDIRECTED(PlaceGenderedPlayerName);
    // REDIRECTED(PlaceWatashi);
    // REDIRECTED(PlacePOKeText);
    REDIRECTED(FillBoxWithByte);
    // REDIRECTED(GameFreakText);
    REDIRECTED(TextCommand_DOTS);
    // REDIRECTED(NullChar);
    // REDIRECTED(PlaceDexEnd);
    REDIRECTED(TextCommand_MOVE);
    // REDIRECTED(PrintText);
    // REDIRECTED(Textbox);
    // REDIRECTED(SixDotsChar);
    // REDIRECTED(PlaceKokoWa);
    // REDIRECTED(PlaceCommandCharacter);
    REDIRECTED(TextCommand_BCD);
    REDIRECTED(TextCommand_LOW);
    REDIRECTED(TextCommand_WAIT_BUTTON);
    // REDIRECTED(SpeechTextbox);
    // REDIRECTED(BuenaPrintText);
    // REDIRECTED(PlaceKougeki);
    // REDIRECTED(SixDotsCharText);
    CONVERTED(LoadBlinkingCursor);
    REDIRECTED(DoTextUntilTerminator);
    REDIRECTED(DoTextUntilTerminator_TextCommand);
    // REDIRECTED(ContText);
    // REDIRECTED(PrintPlayerName);
    // REDIRECTED(DummyChar);
    // REDIRECTED(RocketChar);
    REDIRECTED(TextCommand_START_ASM);
    // REDIRECTED(PrintRivalName);
    // REDIRECTED(PlaceFarString);
    // REDIRECTED(ClearScreen);
    REDIRECTED(PlaceHLTextAtBC);
    // REDIRECTED(PlaceMoveUsersName);
    // REDIRECTED(PCCharText);
    REDIRECTED(ClearBox);
    // REDIRECTED(PrintRedsName);
    // REDIRECTED(EnemyText);
    REDIRECTED(TextCommand_DECIMAL);
    // REDIRECTED(PrintGreensName);
    REDIRECTED(TextCommand_CRY);
    // REDIRECTED(RadioTerminator);
    REDIRECTED(TextCommand_PAUSE);
    // REDIRECTED(TrainerChar);
    // REDIRECTED(TextScroll);
    REDIRECTED(TextCommand_DAY);
    // REDIRECTED(PromptText);
    // REDIRECTED(PlaceEnemysName);
    // REDIRECTED(DoneText);
    // REDIRECTED(ChanSuffixText);
    // REDIRECTED(TextCommands);
    // REDIRECTED(SetUpTextbox);
    // REDIRECTED(KunSuffixText);
    REDIRECTED(TextCommand_BOX);
    // CONVERTED(ClearTilemap);
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
    CONVERTED(RefreshScreen);
    REDIRECTED(OpenText);
    // REDIRECTED(SetCarryFlag);
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

    // engine/menus/intro_menu.c
    REDIRECTED(Intro_MainMenu);
    //REDIRECTED(IntroMenu_DummyFunction);
    //REDIRECTED(PrintDayOfWeek);
    //REDIRECTED(NewGame_ClearTilemapEtc);
    //REDIRECTED(MysteryGift);
    //REDIRECTED(Option);
    //REDIRECTED(NewGame);
    //REDIRECTED(AreYouABoyOrAreYouAGirl);
    //REDIRECTED(DebugRoom);
    //REDIRECTED(ResetWRAM);
    //REDIRECTED(_ResetWRAM);
    //REDIRECTED(SetDefaultBoxNames);
    //REDIRECTED(InitializeNPCNames);
    //REDIRECTED(InitializeWorld);
    //REDIRECTED(LoadOrRegenerateLuckyIDNumber);
    //REDIRECTED(Continue);
    CONVERTED(SpawnAfterRed);
    //REDIRECTED(PostCreditsSpawn);
    //REDIRECTED(Continue_MobileAdapterMenu);
    //REDIRECTED(ConfirmContinue);
    //REDIRECTED(InitializeWorld);
    //REDIRECTED(Continue);
    //REDIRECTED(Continue_PrintGameTime);
    //REDIRECTED(Continue_CheckRTC_RestartClock);
    //REDIRECTED(Continue_DisplayBadgeCount);
    //REDIRECTED(LoadOrRegenerateLuckyIDNumber);
    //REDIRECTED(DisplaySaveInfoOnSave);
    //REDIRECTED(Continue_DisplayBadgesDexPlayerName);
    //REDIRECTED(SpawnAfterRed);
    //REDIRECTED(DisplayNormalContinueData);
    //REDIRECTED(DisplayContinueDataWithRTCError);
    //REDIRECTED(FinishContinueFunction);
    //REDIRECTED(Continue_LoadMenuHeader);
    //REDIRECTED(Continue_MobileAdapterMenu);
    //REDIRECTED(Continue_UnknownGameTime);
    //REDIRECTED(PostCreditsSpawn);
    //REDIRECTED(DisplaySaveInfoOnContinue);
    //REDIRECTED(Continue_DisplayGameTime);
    //REDIRECTED(OakText5);
    //REDIRECTED(OakText6);
    //REDIRECTED(OakText2);
    CONVERTED(StorePlayerName);
    //REDIRECTED(OakText4);
    //REDIRECTED(GSShowPlayerNamingChoices);
    CONVERTED(ShrinkPlayer);
    //REDIRECTED(OakText3);
    //REDIRECTED(Continue_DisplayPokedexNumCaught);
    //REDIRECTED(Intro_PrepTrainerPic);
    //REDIRECTED(Intro_WipeInFrontpic);
    //REDIRECTED(OakText1);
    //REDIRECTED(NamePlayer);
    //REDIRECTED(ShrinkFrame);
    //REDIRECTED(OakText7);
    //REDIRECTED(OakSpeech);
    //REDIRECTED(IntroFadePalettes);
    //REDIRECTED(Intro_RotatePalettesLeftFrontpic);
    CONVERTED(TitleScreenScene);
    REDIRECTED(RunTitleScreen);
    //REDIRECTED(Intro_PlacePlayerSprite);
    //REDIRECTED(UnusedTitlePerspectiveScroll);
    //REDIRECTED(TitleScreenNextScene);
    //REDIRECTED(TitleScreenTimer);
    //REDIRECTED(TitleScreenEntrance);
    //REDIRECTED(StartTitleScreen);
    REDIRECTED(IntroSequence);
    //REDIRECTED(GameInit);
    //REDIRECTED(Copyright);
    //REDIRECTED(ResetClock);
    //REDIRECTED(UpdateTitleTrailSprite);
    //REDIRECTED(CopyrightString);
    //REDIRECTED(TitleScreenEnd);
    //REDIRECTED(DeleteSaveData);
    REDIRECTED(TitleScreenMain);
    //REDIRECTED(TitleScreenEnd);
    //REDIRECTED(DeleteSaveData);
    //REDIRECTED(ResetClock);
    //REDIRECTED(UpdateTitleTrailSprite);
    //REDIRECTED(Copyright);
    //REDIRECTED(CopyrightString);
    //REDIRECTED(GameInit);

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
    // CONVERTED(HandleNPCStep);
    // REDIRECTED(CopyNextCoordsTileToStandingCoordsTile);
    // REDIRECTED(MovementFunction_ObeyDPad);
    // REDIRECTED(UnfreezeObject);
    // REDIRECTED(HandleFrozenObjectAction);
    CONVERTED(v_UpdateSprites);
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
    CONVERTED(HideAllObjects);
    // REDIRECTED(MovementFunction_BigStanding);
    // REDIRECTED(StopFollow);
    // REDIRECTED(JumpMovementPointer);

    // engine/battle_anims/functions.c
    REDIRECTED(BattleAnimFunction_MoveWaveToTarget);
    REDIRECTED(BattleAnimFunction_FloatUp);
    REDIRECTED(BattleAnimFunction_ThrowFromUserToTargetAndDisappear);
    REDIRECTED(BattleAnim_Cosine_e);
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
    REDIRECTED(BattleAnim_Sine_e);
    REDIRECTED(BattleAnimFunction_Recover);
    // REDIRECTED(BattleAnimSineWave);
    REDIRECTED(BattleAnimFunction_Conversion);
    REDIRECTED(BattleAnimFunction_BetaPursuit);
    REDIRECTED(BattleAnimFunction_Horn);
    REDIRECTED(BattleAnimFunction_Bite);
    REDIRECTED(BattleAnim_Cosine);
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
    REDIRECTED(BattleAnim_Sine);
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
    REDIRECTED(DoBattleAnimFrame);
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
    REDIRECTED(DeformScreen);
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
    REDIRECTED(DoBattleBGEffectFunction);
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
    CONVERTED(ReloadMapPart);
    REDIRECTED(OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
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
    CONVERTED(LoadMapTileset);
    // REDIRECTED(CoordinatesEventText);
    // CONVERTED(LoadMapAttributes_SkipObjects);
    // REDIRECTED(FillWestConnectionStrip);
    CONVERTED(ScrollMapRight);
    // REDIRECTED(GetAnyMapTileset);
    CONVERTED(ScrollMapLeft);
    // REDIRECTED(SaveScreen_LoadConnection);
    // REDIRECTED(GetDestinationWarpNumber);
    // REDIRECTED(GetMapSceneID);
    // REDIRECTED(ReadCoordEvents);
    // REDIRECTED(GetFacingTileCoord);
    // REDIRECTED(ReadObjectEvents);
    // REDIRECTED(GetAnyMapPointer);
    // CONVERTED(LoadMapAttributes);
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
    // CONVERTED(ChangeMap);
    // REDIRECTED(LoadMetatiles);
    // REDIRECTED(CheckIndoorMap);
    // REDIRECTED(GetScriptByte);
    // REDIRECTED(BackupBGMapRow);
    // REDIRECTED(ReadWarps);
    // REDIRECTED(OverworldTextModeSwitch);
    // REDIRECTED(GetMapField);
    // REDIRECTED(CheckObjectMask);
    // REDIRECTED(GetCoordTile);
    // CONVERTED(GetMovementPermissions);
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
    CONVERTED(ScrollMapUp);
    CONVERTED(LoadMapPart);
    // REDIRECTED(GetMapPhoneService);
    // REDIRECTED(FillSouthConnectionStrip);
    CONVERTED(ScrollMapDown);
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

    // engine/pokegear/pokegear.c
    // REDIRECTED(PokegearMap_JohtoMap);
    // REDIRECTED(PokegearPhone_MakePhoneCall);
    // REDIRECTED(PokegearPressButtonText);
    // REDIRECTED(NoRadioMusic);
    //REDIRECTED(PhoneTilemapRLE);
    // REDIRECTED(PokegearAskDeleteText);
    // REDIRECTED(v_TownMap);
    //REDIRECTED(BuenasPasswordName);
    // REDIRECTED(Pokegear_FinishTilemap);
    // REDIRECTED(LoadStation_RocketRadio);
    CONVERTED(PokeGear);
    // REDIRECTED(TownMapPlayerIcon);
    //REDIRECTED(NotBuenasPasswordName);
    // REDIRECTED(Radio_BackUpFarCallParams);
    // REDIRECTED(v_UpdateRadioStation);
    // REDIRECTED(PokegearMap_Init);
    // REDIRECTED(TownMapBubble);
    // REDIRECTED(Pokegear_InitJumptableIndices);
    // REDIRECTED(PokegearPhone_FinishPhoneCall);
    // REDIRECTED(PokegearPhoneContactSubmenu);
    //REDIRECTED(ClockTilemapRLE);
    // REDIRECTED(PokegearMap);
    //REDIRECTED(LetsAllSingName);
    // REDIRECTED(InitPokegearModeIndicatorArrow);
    // REDIRECTED(PokegearMap_KantoMap);
    // REDIRECTED(PokegearMap_InitPlayerIcon);
    // REDIRECTED(EntireFlyMap);
    // REDIRECTED(FillTownMap);
    // REDIRECTED(GetAMPMHours);
    // REDIRECTED(LoadStation_BuenasPassword);
    // REDIRECTED(LoadStation_PlacesAndPeople);
    //REDIRECTED(PlacesAndPeopleName);
    // REDIRECTED(PokegearPhone_GetDPad);
    // REDIRECTED(RadioMusicRestartPokemonChannel);
    // REDIRECTED(PokegearPhone_UpdateCursor);
    // REDIRECTED(PokegearMap_ContinueMap);
    // REDIRECTED(TownMap_InitCursorAndPlayerIconPositions);
    // REDIRECTED(PokegearMap_UpdateCursorPosition);
    // REDIRECTED(TownMap_GetKantoLandmarkLimits);
    // REDIRECTED(LoadStation_LuckyChannel);
    // REDIRECTED(PokegearPhone_DeletePhoneNumber);
    // REDIRECTED(NoRadioStation);
    REDIRECTED(Pokegear_UpdateClock);
    // REDIRECTED(CheckIfVisitedFlypoint);
    // REDIRECTED(PokegearSpritesGFX);
    // REDIRECTED(TownMapMon);
    // REDIRECTED(LoadStation_PokemonMusic);
    // REDIRECTED(PokegearRadio_Joypad);
    // REDIRECTED(LoadStation_LetsAllSing);
    //REDIRECTED(RadioChannels);
    // REDIRECTED(DummyLoadStation);
    // REDIRECTED(Pokegear_DummyFunction);
    // REDIRECTED(FlyMap);
    //REDIRECTED(PokeFluteStationName);
    //REDIRECTED(OaksPKMNTalkName);
    // REDIRECTED(TownMap_GetCurrentLandmark);
    // REDIRECTED(TownMapBGUpdate);
    // REDIRECTED(PokegearPhone_UpdateDisplayList);
    //REDIRECTED(Pokegear_LoadTilemapRLE);
    // REDIRECTED(PokegearPhone_Joypad);
    REDIRECTED(PokegearClock_Init);
    // REDIRECTED(JohtoMap);
    // REDIRECTED(PokegearPhone_Init);
    // REDIRECTED(AnimateTuningKnob);
    //REDIRECTED(LuckyChannelName);
    // REDIRECTED(Pokedex_GetArea);
    // REDIRECTED(FillJohtoMap);
    //REDIRECTED(RadioTilemapRLE);
    // REDIRECTED(v_FlyMap);
    //REDIRECTED(NoRadioName);
    //REDIRECTED(PokegearAskWhoCallText);
    // REDIRECTED(RadioMusicRestartDE);
    // REDIRECTED(PokegearMap_InitCursor);
    // REDIRECTED(PlayRadioStationPointers);
    // REDIRECTED(FillKantoMap);
    //REDIRECTED(UnownStationName);
    // REDIRECTED(PlayRadio);
    //REDIRECTED(FastShipGFX);
    // REDIRECTED(PokegearMap_UpdateLandmarkName);
    // REDIRECTED(Pokegear_SwitchPage);
    // REDIRECTED(LoadStation_OaksPokemonTalk);
    // REDIRECTED(HasVisitedSpawn);
    // REDIRECTED(DeleteSpriteAnimStruct2ToEnd);
    REDIRECTED(PokegearJumptable);
    // REDIRECTED(LoadStation_PokeFluteRadio);
    // REDIRECTED(LoadPokegearRadioChannelPointer);
    // REDIRECTED(PokegearClock_Joypad);
    // REDIRECTED(PokegearClock_Joypad_UpdateClock);
    // REDIRECTED(PokegearMap_CheckRegion);
    //REDIRECTED(PokemonMusicName);
    // REDIRECTED(LoadStation_PokedexShow);
    REDIRECTED(InitPokegearTilemap);
    //REDIRECTED(FlyMapLabelBorderGFX);
    // REDIRECTED(LoadStation_UnownRadio);
    // REDIRECTED(TownMapPals);
    // REDIRECTED(LoadStation_PokemonChannel);
    // REDIRECTED(LoadTownMapGFX);
    //REDIRECTED(KantoMap);
    // REDIRECTED(AnimatePokegearModeIndicatorArrow);
    // REDIRECTED(ExitPokegearRadio_HandleMusic);
    // REDIRECTED(Pokegear_LoadGFX);
    //REDIRECTED(PokedexShowName);
    // REDIRECTED(PokegearRadio_Init);
    //REDIRECTED(PokedexNestIconGFX);
    // REDIRECTED(UpdateRadioStation);
    // REDIRECTED(GetMapCursorCoordinates);
    // REDIRECTED(LoadStation_EvolutionRadio);
    REDIRECTED(PokeGear_InitTilemap);

    // engine/overworld/wildmons.c
    // REDIRECTED(CheckEncounterRoamMon);
    // REDIRECTED(LoadWildMonDataPointer);
    // REDIRECTED(ChooseWildEncounter);
    // REDIRECTED(CheckRepelEffect);
    // REDIRECTED(GetMapEncounterRate);
    // REDIRECTED(TryWildEncounter);
    // REDIRECTED(RandomPhoneWildMon);
    // REDIRECTED(v_NoSwarmWildmon);
    // REDIRECTED(UpdateRoamMons);
    // REDIRECTED(LoadWildMonData);
    // REDIRECTED(RandomPhoneMon);
    // REDIRECTED(LookUpWildmonsForMapDE);
    // REDIRECTED(JumpRoamMon);
    // REDIRECTED(JumpRoamMons);
    // REDIRECTED(v_SwarmWildmonCheck);
    // REDIRECTED(ApplyMusicEffectOnEncounterRate);
    // REDIRECTED(v_JohtoWildmonCheck);
    // REDIRECTED(CopyCurrMapDE);
    // REDIRECTED(ValidateTempWildMonSpecies);
    // REDIRECTED(ApplyCleanseTagEffectOnEncounterRate);
    // REDIRECTED(FindNest);
    // REDIRECTED(InitRoamMons);
    // REDIRECTED(v_GrassWildmonLookup);
    // REDIRECTED(v_NormalWildmonOK);
    // REDIRECTED(RandomUnseenWildMon);
    // REDIRECTED(v_WaterWildmonLookup);
    // REDIRECTED(v_BackUpMapIndices);

    // engine/battle/core.c
    // REDIRECTED(HandleHPHealingItem);
    // REDIRECTED(SubtractHP);
    // REDIRECTED(DisplayLinkBattleResult);
    // REDIRECTED(GetHalfHP);
    // REDIRECTED(ExitBattle);
    // REDIRECTED(GetPartyMonDVs);
    CONVERTED(PrintPlayerHUD);
    CONVERTED(EndUserDestinyBond);
    // REDIRECTED(CheckContestBattleOver);
    // REDIRECTED(HandleBetweenTurnEffects);
    // REDIRECTED(UpdateBattleHUDs);
    // REDIRECTED(LoadHPExpBarGFX);
    // REDIRECTED(CheckWhetherSwitchmonIsPredetermined);
    // REDIRECTED(CleanUpBattleRAM);
    CONVERTED(Battle_DummyFunction);
    // REDIRECTED(CheckIfCurPartyMonIsFitToFight);
    // REDIRECTED(FillEnemyMovesFromMoveIndicesBuffer);
    // REDIRECTED(PlayerMonFaintedAnimation);
    // CONVERTED(SendOutPlayerMon);
    // REDIRECTED(BattleMenu_PKMN);
    CONVERTED(EndOpponentProtectEndureDestinyBond);
    // REDIRECTED(GetRoamMonMapGroup);
    // REDIRECTED(BoostStat);
    // REDIRECTED(SwapBattlerLevels);
    // REDIRECTED(DropEnemySub);
    // REDIRECTED(UseHeldStatusHealingItem);
    // REDIRECTED(ScoreMonTypeMatchups);
    // REDIRECTED(OfferSwitch);
    // REDIRECTED(ApplyBrnEffectOnAttack);
    CONVERTED(DoBattle);
    // REDIRECTED(PlayerPartyMonEntrance);
    // REDIRECTED(PursuitSwitch);
    // REDIRECTED(CompareMovePriority);
    // REDIRECTED(ParsePlayerAction);
    // REDIRECTED(IsGymLeaderCommon);
    // REDIRECTED(AddBattleMoneyToAccount);
    REDIRECTED(StartBattle);
    REDIRECTED(Battle_EnemyFirst);
    CONVERTED(InitBattleMon);
    // REDIRECTED(IsMobileBattle);
    // REDIRECTED(v_LoadHPBar);
    // REDIRECTED(SwitchMonAlreadyOut);
    // REDIRECTED(CallDoBattle);
    // REDIRECTED(MoveSelectionScreen);
    // REDIRECTED(ComeBackText);
    // REDIRECTED(MoveInfoBox);
    // REDIRECTED(SwitchPlayerMon);
    CONVERTED(CheckDanger);
    // REDIRECTED(PassedBattleMonEntrance);
    // REDIRECTED(HandleHealingItems);
    // REDIRECTED(CheckEnemyLockedIn);
    // REDIRECTED(PlayerSwitch);
    // REDIRECTED(YourFoesWeakGetmMonText);
    // REDIRECTED(EnemyMonEntrance);
    // REDIRECTED(IsKantoGymLeader);
    // REDIRECTED(SelectBattleMon);
    // REDIRECTED(HandlePlayerMonFaint);
    // REDIRECTED(GoMonText);
    REDIRECTED(ResidualDamage);
    CONVERTED(BattleStartMessage);
    // CONVERTED(EnemySwitch);
    REDIRECTED(BattleTurn);
    // REDIRECTED(EnemyTurn_EndOpponentProtectEndureDestinyBond);
    // REDIRECTED(GetSixteenthMaxHP);
    // REDIRECTED(GetMaxHP);
    // REDIRECTED(PickSwitchMonInBattle);
    CONVERTED(FinishBattleAnim);
    // CONVERTED(BattleMenu);
    // REDIRECTED(UpdateHPBar);
    // REDIRECTED(CheckSleepingTreeMon);
    // REDIRECTED(CheckUserHasEnoughHP);
    // REDIRECTED(LoadTrainerOrWildMonPic);
    // REDIRECTED(BattleWinSlideInEnemyTrainerFrontpic);
    // REDIRECTED(PickPartyMonInBattle);
    // REDIRECTED(AskUseNextPokemon);
    // REDIRECTED(HandlePerishSong);
    // REDIRECTED(ResetEnemyStatLevels);
    CONVERTED(ShowSetEnemyMonAndSendOutAnimation);
    // REDIRECTED(ExpPointsText);
    // REDIRECTED(PlayerTurn_EndOpponentProtectEndureDestinyBond);
    // REDIRECTED(UseConfusionHealingItem);
    // REDIRECTED(BadgeStatBoosts);
    // REDIRECTED(DrawEnemyHUD);
    // REDIRECTED(CheckEnemyTrainerDefeated);
    // REDIRECTED(SubtractHPFromTarget);
    // REDIRECTED(HasUserFainted);
    CONVERTED(ResetPlayerStatLevels);
    // REDIRECTED(ReadAndPrintLinkBattleRecord);
    // CONVERTED(BreakAttraction);
    // REDIRECTED(FillInExpBar);
    // REDIRECTED(GetHalfMaxHP);
    // REDIRECTED(GetPartymonItem);
    // REDIRECTED(ThatsEnoughComeBackText);
    // REDIRECTED(InitEnemyWildmon);
    // REDIRECTED(ResetVarsForSubstatusRage);
    // REDIRECTED(DoItMonText);
    // REDIRECTED(GetRoamMonHP);
    // REDIRECTED(ApplyStatLevelMultiplier);
    // REDIRECTED(DropPlayerSub);
    // REDIRECTED(BattleMonNicknameText);
    // REDIRECTED(HasPlayerFainted);
    // REDIRECTED(DrawPlayerHUD);
    CONVERTED(GetTrainerBackpic);
    // REDIRECTED(GetRoamMonDVs);
    // REDIRECTED(HandleScreens);
    // REDIRECTED(HandleDefrost);
    // REDIRECTED(SwitchTurnCore);
    // REDIRECTED(CheckPlayerPartyForFitMon);
    // REDIRECTED(ItemRecoveryAnim);
    // REDIRECTED(ShowLinkBattleParticipantsAfterEnd);
    // REDIRECTED(UpdateBattleStateAndExperienceAfterEnemyFaint);
    // REDIRECTED(GetRoamMonMapNumber);
    // REDIRECTED(RecallPlayerMon);
    // CONVERTED(NewBattleMonStatus);
    CONVERTED(AddBattleParticipant);
    // REDIRECTED(LoadEnemyMonToSwitchTo);
    REDIRECTED(InitEnemyTrainer);
    // REDIRECTED(UpdateHPBarBattleHuds);
    CONVERTED(LoadEnemyMon);
    // REDIRECTED(LoadBattleMenu2);
    // REDIRECTED(SendOutMonText);
    // REDIRECTED(TextJump_ComeBack);
    // REDIRECTED(CheckMobileBattleError);
    // REDIRECTED(GetOTPartymonItem);
    // REDIRECTED(BoostedExpPointsText);
    // REDIRECTED(HandleSafeguard);
    // REDIRECTED(JumpToPartyMenuAndPrintText);
    // REDIRECTED(CheckPayDay);
    // REDIRECTED(FindMonInOTPartyToSwitchIntoBattle);
    CONVERTED(GetEnemyMonFrontpic);
    // REDIRECTED(BoostExp);
    // REDIRECTED(ApplyPrzEffectOnSpeed);
    REDIRECTED(Battle_PlayerFirst);
    CONVERTED(FaintEnemyPokemon);
    // REDIRECTED(ApplyStatusEffectOnEnemyStats);
    // REDIRECTED(HandleMysteryberry);
    // REDIRECTED(RestoreHP);
    // REDIRECTED(BattleMenu_Run);
    // REDIRECTED(GoForItMonText);
    // REDIRECTED(ParseEnemyAction);
    // REDIRECTED(GetEighthMaxHP);
    // REDIRECTED(SetUpBattlePartyMenu);
    // REDIRECTED(InitEnemyMon);
    // REDIRECTED(CopyBackpic);
    // REDIRECTED(IsThePlayerMonTypesEffectiveAgainstOTMon);
    // REDIRECTED(SetUpBattlePartyMenu_Loop);
    // REDIRECTED(BattleEnd_HandleRoamMons);
    // REDIRECTED(HandleEncore);
    // REDIRECTED(ForcePlayerMonChoice);
    // REDIRECTED(NewEnemyMonStatus);
    // REDIRECTED(AddLastLinkBattleToLinkRecord);
    CONVERTED(BackUpBGMap2);
    // REDIRECTED(BattleMenuPKMN_Loop);
    // REDIRECTED(Call_PlayBattleAnim_OnlyIfVisible);
    // REDIRECTED(GetMoveEffect);
    // REDIRECTED(EnemyMonFaintedAnimation);
    CONVERTED(ShowBattleTextEnemySentOut);
    // REDIRECTED(SpikesDamage);
    // REDIRECTED(BattleMonEntrance);
    // REDIRECTED(WithdrawMonText);
    // REDIRECTED(CheckIfHPIsZero);
    // REDIRECTED(HandleLeftovers);
    // REDIRECTED(ApplyStatusEffectOnStats);
    // REDIRECTED(CheckPlayerLockedIn);
    // REDIRECTED(UpdatePlayerHPPal);
    // REDIRECTED(CheckUnownLetter);
    // REDIRECTED(HandleFutureSight);
    // REDIRECTED(Text_MonGainedExpPoint);
    // REDIRECTED(IsGymLeader);
    // REDIRECTED(LinkBattleSendReceiveAction);
    CONVERTED(InitEnemy);
    // REDIRECTED(BattleCheckShininess);
    // REDIRECTED(v_BattleRandom);
    // REDIRECTED(ForcePickSwitchMonInBattle);
    // REDIRECTED(HandleWrap);
    // REDIRECTED(GiveExperiencePoints);
    // REDIRECTED(CheckPlayerHasUsableMoves);
    // REDIRECTED(Call_PlayBattleAnim);
    // REDIRECTED(LostBattle);
    // REDIRECTED(HandleWeather);
    // REDIRECTED(TryPlayerSwitch);
    // REDIRECTED(BattleMenu_Fight);
    // REDIRECTED(GoodComeBackText);
    // REDIRECTED(IsAnyMonHoldingExpShare);
    // REDIRECTED(HandleEnemySwitch);
    // REDIRECTED(HandleStatBoostingHeldItems);
    // REDIRECTED(CheckFaint_PlayerThenEnemy);
    // REDIRECTED(ForcePickPartyMonInBattle);
    // REDIRECTED(UpdateEnemyHPPal);
    // REDIRECTED(PlaceExpBar);
    // REDIRECTED(BattleCheckPlayerShininess);
    // REDIRECTED(GetEnemyMonDVs);
    CONVERTED(EmptyBattleTextbox);
    REDIRECTED(BattleIntro);
    // REDIRECTED(HasEnemyFainted);
    // REDIRECTED(EnemyPartyMonEntrance);
    // REDIRECTED(GetBattleMonBackpic_DoAnim);
    // REDIRECTED(StopDangerSound);
    // REDIRECTED(UpdateFaintedPlayerMon);
    // REDIRECTED(ResetEnemyBattleVars);
    // REDIRECTED(PlayVictoryMusic);
    // REDIRECTED(UseOpponentItem);
    // REDIRECTED(CheckWhetherToAskSwitch);
    // REDIRECTED(TryEnemyFlee);
    // REDIRECTED(AnimateExpBar);
    // REDIRECTED(DoubleSwitch);
    // REDIRECTED(Battle_StatsScreen);
    // REDIRECTED(WildFled_EnemyFled_LinkBattleCanceled);
    // CONVERTED(EnemySwitch_SetMode);
    // REDIRECTED(ClearEnemyMonBox);
    // REDIRECTED(Stubbed_Increments5_a89a);
    // REDIRECTED(BattleCheckEnemyShininess);
    // REDIRECTED(MonFaintedAnimation);
    REDIRECTED(WinTrainerBattle);
    // REDIRECTED(EnemyTriesToFlee);
    // REDIRECTED(CheckFaint_EnemyThenPlayer);
    // REDIRECTED(TryToRunAwayFromBattle);
    // REDIRECTED(UpdateHPPal);
    // REDIRECTED(BattleMenuPKMN_ReturnFromStats);
    // REDIRECTED(PrepareBattleMonNicknameText);
    // REDIRECTED(GetEnemyMonFrontpic_DoAnim);
    // REDIRECTED(SubtractHPFromUser);
    // REDIRECTED(GetQuarterMaxHP);
    // REDIRECTED(HandleBerserkGene);
    // REDIRECTED(OKComeBackText);
    // REDIRECTED(FaintYourPokemon);
    // REDIRECTED(LookUpTheEffectivenessOfEveryMove);
    CONVERTED(UpdatePlayerHUD);
    REDIRECTED(HandleEnemyMonFaint);
    // REDIRECTED(UpdateEnemyHUD);
    // REDIRECTED(GetMovePriority);
    // REDIRECTED(CalcExpBar);
    // REDIRECTED(GetRoamMonSpecies);
    // REDIRECTED(ApplyStatusEffectOnPlayerStats);
    CONVERTED(v_LoadBattleFontsHPBar);
    // REDIRECTED(InitBattleDisplay);
    // REDIRECTED(DetermineMoveOrder);
    // REDIRECTED(ApplyStatLevelMultiplierOnAllStats);
    // REDIRECTED(SlideBattlePicOut);
    // REDIRECTED(BattleMenu_Pack);
    // REDIRECTED(ForceEnemySwitch);
    CONVERTED(ResetBattleParticipants);
    // REDIRECTED(IsMobileBattle2);
    // REDIRECTED(GetBattleMonBackpic);
    // REDIRECTED(HandleSafariAngerEatingStatus);
    // REDIRECTED(CheckAmuletCoin);
    // REDIRECTED(v_DisplayLinkRecord);

    // engine/movie/intro.c
    // CONVERTED(IntroScene27);
    // REDIRECTED(IntroGrass4GFX);
    // REDIRECTED(IntroSuicuneCloseTilemap);
    // CONVERTED(IntroScene6);
    // REDIRECTED(IntroPichuWooperGFX);
    // REDIRECTED(IntroSuicuneClosePalette);
    // REDIRECTED(IntroUnownHIAttrmap);
    // REDIRECTED(IntroCrystalUnownsTilemap);
    // CONVERTED(IntroScene24);
    // CONVERTED(Intro_ColoredSuicuneFrameSwap);
    CONVERTED(CrystalIntro);
    // REDIRECTED(Intro_PerspectiveScrollBG);
    // REDIRECTED(IntroUnownHITilemap);
    // CONVERTED(IntroScene15);
    // CONVERTED(Intro_Scene16_AnimateSuicune);
    // REDIRECTED(IntroCrystalUnownsGFX);
    // REDIRECTED(Intro_FadeUnownWordPals);
    // CONVERTED(IntroScene9);
    // CONVERTED(IntroScene2);
    // REDIRECTED(IntroGrass3GFX);
    // CONVERTED(IntroScene28);
    // REDIRECTED(IntroScenes);
    // CONVERTED(IntroScene8);
    // REDIRECTED(IntroUnownAAttrmap);
    // REDIRECTED(IntroSuicuneBackAttrmap);
    // REDIRECTED(CrystalIntro_InitUnownAnim);
    // REDIRECTED(IntroUnownsGFX);
    // CONVERTED(IntroScene1);
    // CONVERTED(IntroScene12);
    // CONVERTED(IntroScene13);
    // REDIRECTED(IntroUnownATilemap);
    // REDIRECTED(IntroUnownBackGFX);
    // REDIRECTED(Intro_DecompressRequest2bpp_255Tiles);
    // REDIRECTED(IntroCrystalUnownsPalette);
    // CONVERTED(IntroScene7);
    // CONVERTED(IntroScene25);
    // REDIRECTED(IntroBackgroundTilemap);
    // CONVERTED(IntroScene4);
    // REDIRECTED(Intro_Scene20_AppearUnown);
    // REDIRECTED(Intro_DecompressRequest2bpp_64Tiles);
    // CONVERTED(IntroScene21);
    // CONVERTED(IntroScene3);
    // REDIRECTED(IntroSuicuneJumpTilemap);
    // CONVERTED(IntroScene5);
    // REDIRECTED(IntroGrass2GFX);
    // REDIRECTED(Intro_DecompressRequest2bpp_128Tiles);
    // REDIRECTED(IntroUnownsAttrmap);
    // REDIRECTED(Intro_ClearBGPals);
    // REDIRECTED(IntroSuicuneBackGFX);
    // CONVERTED(IntroScene22);
    // REDIRECTED(Intro_Scene24_ApplyPaletteFade);
    // REDIRECTED(IntroUnownsPalette);
    // CONVERTED(IntroScene20);
    // REDIRECTED(IntroSuicuneJumpGFX);
    // REDIRECTED(IntroSuicunePalette);
    // REDIRECTED(IntroSuicuneJumpAttrmap);
    // REDIRECTED(IntroGrass1GFX);
    // CONVERTED(IntroScene10);
    // REDIRECTED(CrystalIntro_UnownFade);
    // CONVERTED(IntroScene19);
    // REDIRECTED(Intro_LoadTilemap);
    // REDIRECTED(IntroSuicuneRunGFX);
    // REDIRECTED(IntroBackgroundGFX);
    // REDIRECTED(Intro_RustleGrass);
    // CONVERTED(IntroSceneJumper);
    // CONVERTED(IntroScene26);
    // REDIRECTED(IntroUnownsTilemap);
    // REDIRECTED(IntroCrystalUnownsAttrmap);
    // CONVERTED(NextIntroScene);
    // REDIRECTED(IntroBackgroundAttrmap);
    // CONVERTED(IntroScene11);
    // CONVERTED(IntroScene16);
    // CONVERTED(IntroScene18);
    // REDIRECTED(Intro_SetCGBPalUpdate);
    // REDIRECTED(Intro_ResetLYOverrides);
    // REDIRECTED(IntroBackgroundPalette);
    // REDIRECTED(IntroSuicuneCloseAttrmap);
    // REDIRECTED(IntroPulseGFX);
    // CONVERTED(IntroScene23);
    // REDIRECTED(IntroSuicuneBackTilemap);
    // CONVERTED(IntroScene17);
    // REDIRECTED(IntroSuicuneCloseGFX);
    // CONVERTED(IntroScene14);

    // engine/pokegear/radio.c
    REDIRECTED(OaksPKMNTalk12);
    REDIRECTED(LuckyNumberShow7);
    REDIRECTED(BuenasPassword6);
    // REDIRECTED(LC_DragText1);
    REDIRECTED(PokedexShow2);
    REDIRECTED(BenFernMusic5);
    REDIRECTED(LuckyNumberShow1);
    REDIRECTED(LuckyNumberShow4);
    REDIRECTED(PeoplePlaces5);
    REDIRECTED(PokedexShow1);
    // REDIRECTED(PnP_Text3);
    // REDIRECTED(RocketRadioText2);
    // REDIRECTED(RocketRadioText9);
    // REDIRECTED(BenFernText3A);
    REDIRECTED(EvolutionRadio);
    REDIRECTED(PlayRadioShow);
    // REDIRECTED(PnP_Text5);
    // REDIRECTED(BuenaRadioMidnightText10);
    REDIRECTED(BenMonMusic1);
    REDIRECTED(BuenasPassword4);
    REDIRECTED(BenMonMusic3);
    // REDIRECTED(RocketRadioText7);
    REDIRECTED(LuckyNumberShow14);
    REDIRECTED(LuckyNumberShow9);
    // REDIRECTED(LC_Text7);
    // REDIRECTED(PnP_PickyText);
    REDIRECTED(ReplacePeriodsWithSpaces);
    REDIRECTED(RocketRadio8);
    // REDIRECTED(OPT_IntroText3);
    REDIRECTED(OaksPKMNTalk7);
    // REDIRECTED(RocketRadioText1);
    REDIRECTED(NextRadioLine);
    REDIRECTED(RocketRadio5);
    REDIRECTED(BuenasPassword20);
    REDIRECTED(PokedexShow3);
    REDIRECTED(PeoplePlaces3);
    REDIRECTED(RadioScroll);
    REDIRECTED(CopyDexEntryPart1);
    REDIRECTED(BuenasPassword7);
    REDIRECTED(PeoplePlaces4);
    REDIRECTED(LuckyNumberShow12);
    REDIRECTED(OaksPKMNTalk11);
    // REDIRECTED(BuenaRadioMidnightText7);
    REDIRECTED(LuckyNumberShow6);
    REDIRECTED(CopyDexEntryPart2);
    REDIRECTED(BuenasPassword21);
    REDIRECTED(PeoplePlaces6);
    // REDIRECTED(RocketRadioText5);
    // REDIRECTED(BuenaRadioMidnightText3);
    REDIRECTED(BenFernMusic7);
    // REDIRECTED(PnP_HappyText);
    REDIRECTED(BuenasPassword14);
    // REDIRECTED(LC_Text10);
    // REDIRECTED(PnP_PrecociousText);
    // REDIRECTED(PnP_SortOfOKText);
    REDIRECTED(RocketRadio6);
    REDIRECTED(PokedexShow_GetDexEntryBank);
    // CONVERTED(ClearBottomLine);
    // REDIRECTED(OPT_IntroText2);
    REDIRECTED(CopyDexEntry);
    // REDIRECTED(BuenaRadioText6);
    // REDIRECTED(PnP_MyTypeText);
    // REDIRECTED(LC_Text1);
    REDIRECTED(RadioJumptable);
    // REDIRECTED(PnP_InspiringText);
    // REDIRECTED(PnP_RightForMeText);
    REDIRECTED(PrintRadioLine);
    REDIRECTED(BuenasPassword15);
    REDIRECTED(BuenasPassword9);
    // REDIRECTED(OPT_IntroText1);
    // REDIRECTED(BuenasPasswordChannelName);
    REDIRECTED(BuenasPassword18);
    REDIRECTED(OaksPKMNTalk4);
    REDIRECTED(PeoplePlaces2);
    REDIRECTED(LuckyNumberShow10);
    REDIRECTED(OaksPKMNTalk13);
    REDIRECTED(OaksPKMNTalk5);
    REDIRECTED(OaksPKMNTalk9);
    // REDIRECTED(PnP_CuteText);
    // REDIRECTED(OPT_OakText2);
    // REDIRECTED(BenFernText2A);
    REDIRECTED(RocketRadioText8);
    REDIRECTED(RocketRadio4);
    REDIRECTED(OaksPKMNTalk2);
    REDIRECTED(BuenasPasswordAfterMidnight);
    // REDIRECTED(LC_Text3);
    // REDIRECTED(PnP_NoisyText);
    REDIRECTED(PokedexShow6);
    REDIRECTED(OaksPKMNTalk10);
    // REDIRECTED(PnP_SoSoText);
    REDIRECTED(BuenasPassword1);
    REDIRECTED(OaksPKMNTalk8);
    // REDIRECTED(BuenaRadioMidnightText2);
    // REDIRECTED(BuenaRadioMidnightText6);
    REDIRECTED(LuckyNumberShow8);
    // REDIRECTED(LC_Text5);
    // REDIRECTED(PnP_GreatText);
    REDIRECTED(FernMonMusic2);
    REDIRECTED(StartPokemonMusicChannel);
    REDIRECTED(OaksPKMNTalk3);
    // REDIRECTED(LC_Text4);
    REDIRECTED(RocketRadio1);
    REDIRECTED(RocketRadio3);
    REDIRECTED(LuckyNumberShow2);
    REDIRECTED(LuckyNumberShow15);
    REDIRECTED(RocketRadio9);
    REDIRECTED(PokedexShow7);
    REDIRECTED(BuenasPassword13);
    // REDIRECTED(BenFernText1);
    // REDIRECTED(LC_Text9);
    // REDIRECTED(BuenaRadioMidnightText8);
    // REDIRECTED(BenIntroText1);
    REDIRECTED(LuckyNumberShow13);
    // REDIRECTED(LC_Text6);
    REDIRECTED(LuckyNumberShow11);
    // REDIRECTED(PnP_LazyText);
    // REDIRECTED(PnP_Text1);
    REDIRECTED(BenMonMusic2);
    // REDIRECTED(LC_DragText2);
    // REDIRECTED(BuenaRadioMidnightText1);
    // REDIRECTED(BuenaRadioMidnightText5);
    REDIRECTED(OaksPKMNTalk1);
    REDIRECTED(PokedexShow8);
    // CONVERTED(PokedexShowText);
    REDIRECTED(BenFernMusic4);
    REDIRECTED(StartRadioStation);
    REDIRECTED(PokeFluteRadio);
    // REDIRECTED(OPT_OakText3);
    REDIRECTED(GetBuenasPassword);
    // REDIRECTED(BenFernText3B);
    REDIRECTED(LuckyNumberShow5);
    // REDIRECTED(PnP_WeirdText);
    REDIRECTED(PeoplePlaces7);
    // REDIRECTED(RocketRadioText3);
    REDIRECTED(BuenasPassword8);
    REDIRECTED(BuenasPassword3);
    // REDIRECTED(FernIntroText2);
    // REDIRECTED(BuenaOffTheAirText);
    // REDIRECTED(BuenaRadioMidnightText9);
    REDIRECTED(FernMonMusic1);
    REDIRECTED(PokedexShow4);
    REDIRECTED(BuenasPassword19);
    // REDIRECTED(OPT_PokemonChannelText);
    REDIRECTED(BuenasPassword12);
    REDIRECTED(BuenasPasswordCheckTime);
    // REDIRECTED(BuenaRadioText5);
    REDIRECTED(BuenasPassword11);
    // REDIRECTED(PnP_Text4);
    REDIRECTED(BuenasPassword5);
    // REDIRECTED(BuenaRadioText3);
    // REDIRECTED(FernIntroText1);
    // REDIRECTED(BuenaRadioText1);
    // REDIRECTED(RocketRadioText4);
    // REDIRECTED(BenFernText2B);
    REDIRECTED(RocketRadio10);
    // REDIRECTED(BuenaRadioText4);
    REDIRECTED(PokedexShow5);
    // REDIRECTED(BuenaRadioText2);
    REDIRECTED(UnownRadio);
    // REDIRECTED(LC_Text2);
    // REDIRECTED(OPT_RestartText);
    REDIRECTED(OaksPKMNTalk6);
    // REDIRECTED(PnP_OddText);
    // REDIRECTED(PnP_CoolText);
    REDIRECTED(RocketRadio2);
    // REDIRECTED(LC_Text8);
    // REDIRECTED(BuenaRadioMidnightText4);
    REDIRECTED(BuenasPassword16);
    // REDIRECTED(LC_Text11);
    REDIRECTED(OaksPKMNTalk14);
    REDIRECTED(LuckyNumberShow3);
    // REDIRECTED(OPT_MaryText1);
    REDIRECTED(BuenasPassword2);
    // CONVERTED(CopyBottomLineToTopLine);
    REDIRECTED(BenFernMusic6);
    // REDIRECTED(CopyRadioTextToRAM);
    // REDIRECTED(PnP_BoldText);
    // REDIRECTED(BenIntroText2);
    REDIRECTED(BuenasPassword10);
    REDIRECTED(BuenasPassword17);
    // REDIRECTED(OPT_OakText1);
    REDIRECTED(PeoplePlaces1);
    // REDIRECTED(RocketRadioText10);
    // REDIRECTED(PnP_Text2);
    REDIRECTED(PlaceRadioString);
    // REDIRECTED(RocketRadioText6);
    // REDIRECTED(BenIntroText3);
    REDIRECTED(RocketRadio7);
    // REDIRECTED(BuenaRadioText7);

    // engine/battle_anims/core.c
    REDIRECTED(v_QueueBGEffect);
    REDIRECTED(InitBattleAnimation);
    REDIRECTED(GetBattleAnimTileOffset);
    REDIRECTED(InitBattleAnimBuffer);
    REDIRECTED(DeinitBattleAnimation);
    REDIRECTED(BattleAnimOAMUpdate);
    REDIRECTED(v_ExecuteBGEffects);
    REDIRECTED(QueueBattleAnimation);

    // engine/battle/battle_transition.c
    REDIRECTED(StartTrainerBattle_ZoomToBlack);
    CONVERTED(StartTrainerBattle_NextScene);
    REDIRECTED(BattleTransitionJumptable);
    CONVERTED(StartTrainerBattle_SetUpForSpinOutro);
    CONVERTED(DoBattleTransition);
    // REDIRECTED(PokeBallTransition);
    CONVERTED(StartTrainerBattle_SetUpBGMap);
    CONVERTED(StartTrainerBattle_Flash);
    CONVERTED(StartTrainerBattle_Finish);
    CONVERTED(StartTrainerBattle_SpinToBlack);
    // REDIRECTED(TrainerBattlePokeballTiles);
    CONVERTED(StartTrainerBattle_SineWave);
    REDIRECTED(UnusedWaitBGMapOnce);
    REDIRECTED(ConvertTrainerBattlePokeballTilesTo2bpp);
    CONVERTED(StartTrainerBattle_DetermineWhichAnimation);
    CONVERTED(StartTrainerBattle_SetUpForWavyOutro);
    CONVERTED(StartTrainerBattle_SpeckleToBlack);
    REDIRECTED(WipeLYOverrides);
    REDIRECTED(StartTrainerBattle_DrawSineWave);
    CONVERTED(StartTrainerBattle_SetUpForRandomScatterOutro);
    REDIRECTED(StartTrainerBattle_LoadPokeBallGraphics);
    REDIRECTED(LoadTrainerBattlePokeballTiles);

    // engine/menus/main_menu.c
    // REDIRECTED(MainMenuItems);
    // REDIRECTED(ClearTilemapEtc);
    // REDIRECTED(MainMenu_Continue);
    // REDIRECTED(MainMenu_Option);
    REDIRECTED(MainMenu_MysteryGift);
    // REDIRECTED(MainMenuJoypadLoop);
    CONVERTED(MainMenu_PrintCurrentTimeAndDay);
    // REDIRECTED(MobileMenuGFX);
    REDIRECTED(MainMenu_GetWhichMenu);
    // REDIRECTED(MainMenu);
    // REDIRECTED(MainMenu_NewGame);

    // engine/phone/phone.c
    // REDIRECTED(HangUp_Beep);
    // REDIRECTED(SpecialCallOnlyWhenOutside);
    // REDIRECTED(Phone_FindOpenSlot);
    // REDIRECTED(Phone_StartRinging);
    // REDIRECTED(HangUp_Wait20Frames);
    // REDIRECTED(v_CheckCellNum);
    // REDIRECTED(PhoneThankYouText);
    // REDIRECTED(PhoneEllipseText);
    // REDIRECTED(GetRemainingSpaceInPhoneList);
    // REDIRECTED(SpecialCallWhereverYouAre);
    // REDIRECTED(Script_SpecialElmCall);
    // REDIRECTED(HangUp_BoopOff);
    // REDIRECTED(LoadCallerScript);
    // REDIRECTED(WrongNumber);
    // REDIRECTED(PhoneOutOfAreaScript);
    // REDIRECTED(LoadOutOfAreaScript);
    // REDIRECTED(GetCallerClassAndName);
    // REDIRECTED(HangUp_BoopOn);
    // REDIRECTED(HangUp_ShutDown);
    // REDIRECTED(CheckCellNum);
    // REDIRECTED(CheckPhoneCall);
    // REDIRECTED(MakePhoneCallFromPokegear);
    // REDIRECTED(Phone_Wait20Frames);
    // REDIRECTED(Phone_GetTrainerClassName);
    // REDIRECTED(DelCellNum);
    // REDIRECTED(Phone_GetTrainerName);
    // REDIRECTED(CheckSpecialPhoneCall);
    // REDIRECTED(HangUp);
    // REDIRECTED(AddPhoneNumber);
    // REDIRECTED(Phone_CallerTextbox);
    // REDIRECTED(GetCallerTrainerClass);
    // REDIRECTED(PhoneJustTalkToThemText);
    // REDIRECTED(Phone_TextboxWithName);
    // REDIRECTED(ChooseRandomCaller);
    // REDIRECTED(Script_SpecialBillCall);
    // REDIRECTED(LoadPhoneScriptBank);
    // REDIRECTED(PhoneOutOfAreaText);
    // REDIRECTED(PhoneClickText);
    // REDIRECTED(RingTwice_StartCall);
    // REDIRECTED(PhoneThankYouTextScript);
    // REDIRECTED(BrokenPlaceFarString);
    // REDIRECTED(CheckPhoneContactTimeOfDay);
    // REDIRECTED(PhoneCall);
    // REDIRECTED(GetAvailableCallers);
    // REDIRECTED(Phone_NoSignal);
    // REDIRECTED(GetCallerName);
    // REDIRECTED(Phone_CallEnd);
    // REDIRECTED(Script_ReceivePhoneCall);
    // REDIRECTED(CheckCanDeletePhoneNumber);
    // REDIRECTED(GetCallerLocation);
    // REDIRECTED(PhoneScript_JustTalkToThem);

    // engine/gfx/sprites.c
    // REDIRECTED(ClearSpriteAnims);
    // REDIRECTED(PlaySpriteAnimationsAndDelayFrame);
    // REDIRECTED(DoNextFrameForFirst16Sprites);
    REDIRECTED(GetSpriteAnimFrame);
    // REDIRECTED(InitSpriteAnimBuffer);
    // REDIRECTED(AnimateEndOfExpBar);
    REDIRECTED(Sprites_Sine);
    REDIRECTED(UpdateAnimFrame);
    REDIRECTED(AddOrSubtractX);
    REDIRECTED(Sprites_Cosine);
    // REDIRECTED(DeinitializeAllSprites);
    // REDIRECTED(v_ReinitSpriteAnimFrame);
    // REDIRECTED(v_InitSpriteAnimStruct);
    REDIRECTED(PlaySpriteAnimations);
    REDIRECTED(GetSpriteOAMAttr);
    REDIRECTED(DoNextFrameForAllSprites);
    REDIRECTED(GetSpriteAnimVTile);
    REDIRECTED(GetFrameOAMPointer);
    // REDIRECTED(SGBEndOfExpBarGFX);
    // REDIRECTED(ClearSpriteAnims2);
    // REDIRECTED(UnusedLoadSpriteAnimGFX);
    // REDIRECTED(EndOfExpBarGFX);
    REDIRECTED(DeinitializeSprite);
    REDIRECTED(AddOrSubtractY);

    // engine/gfx/sprite_anims.c
    // REDIRECTED(AnimSeq_PartyMonSwitch);
    // REDIRECTED(AnimSeq_FlyLeaf);
    // REDIRECTED(AnimSeq_NamingScreenCursor);
    // REDIRECTED(AnimSeq_IntroUnownF);
    // REDIRECTED(AnimSeq_MemoryGameCursor);
    // REDIRECTED(AnimSeq_MailCursor);
    // REDIRECTED(AnimSeq_GSGameFreakLogoStar);
    // REDIRECTED(AnimSeq_GSIntroHoOhLugia);
    // REDIRECTED(AnimSeq_EZChatCursor);
    // REDIRECTED(AnimSeqs_Cosine);
    // REDIRECTED(AnimSeqs_Sine);
    // REDIRECTED(AnimSeq_TradeTubeBulge);
    // REDIRECTED(AnimSeq_TrademonInTube);
    // REDIRECTED(AnimSeq_Celebi);
    // REDIRECTED(AnimSeq_GSGameFreakLogoSparkle);
    // REDIRECTED(AnimSeq_SlotsChanseyEgg);
    // REDIRECTED(AnimSeq_GameFreakLogo);
    // REDIRECTED(AnimSeq_TradePokeBall);
    // REDIRECTED(AnimSeq_IntroUnown);
    // REDIRECTED(AnimSeq_PartyMon);
    // REDIRECTED(AnimSeq_GSTitleTrail);
    // REDIRECTED(AnimSeq_SlotsChansey);
    // REDIRECTED(AnimSeq_SlotsGolem);
    // REDIRECTED(AnimSeq_CutLeaves);
    // REDIRECTED(AnimSeq_IntroSuicuneAway);
    // REDIRECTED(AnimSeq_RadioTuningKnob);
    // REDIRECTED(AnimSeq_MobileTradeSentPulse);
    // REDIRECTED(AnimSeq_MobileTradeOTPulse);
    // REDIRECTED(AnimSeqs_AnonJumptable);
    // REDIRECTED(AnimSeq_PokegearArrow);
    // REDIRECTED(AnimSeq_FlyFrom);
    // REDIRECTED(AnimSeqs_IncAnonJumptableIndex);
    // REDIRECTED(AnimSeq_FlyTo);
    // REDIRECTED(AnimSeq_IntroPichuWooper);
    // REDIRECTED(AnimSeq_UnusedCursor);
    // REDIRECTED(AnimSeq_RevealNewMon);
    // REDIRECTED(AnimSeq_IntroSuicune);
    // REDIRECTED(AnimSeq_Null);
    REDIRECTED(DoAnimFrame);
    // REDIRECTED(AnimSeq_PartyMonSelected);

    // engine/gfx/player_gfx.c
    // REDIRECTED(GetPlayerBackpic);
    // REDIRECTED(TrainerCardGFX);
    // REDIRECTED(ShowPlayerNamingChoices);
    CONVERTED(GetChrisBackpic);
    // REDIRECTED(MovePlayerPic);
    // REDIRECTED(KrisCardPic);
    // REDIRECTED(ChrisPic);
    // REDIRECTED(HOF_LoadTrainerFrontpic);
    // REDIRECTED(GetPlayerNameArray);
    // REDIRECTED(GetPlayerIcon);
    CONVERTED(GetKrisBackpic);
    // REDIRECTED(GetCardPic);
    // REDIRECTED(DrawIntroPlayerPic);
    // REDIRECTED(BetaLoadPlayerTrainerClass);
    // REDIRECTED(MovePlayerPicRight);
    // REDIRECTED(KrisPic);
    // REDIRECTED(ChrisCardPic);
    // REDIRECTED(MovePlayerPicLeft);
    // REDIRECTED(KrisBackpic);

    // engine/battle/start_battle.c
    // REDIRECTED(ShowLinkBattleParticipants);
    // REDIRECTED(ClearBattleRAM);
    // REDIRECTED(PlayBattleMusic);
    // REDIRECTED(FindFirstAliveMonAndStartBattle);

    // engine/battle/sliding_intro.c
    CONVERTED(BattleIntroSlidingPics);

    // engine/rtc/rtc.c
    // REDIRECTED(SaveRTC);
    // REDIRECTED(v_InitTime);
    // REDIRECTED(GetTimeOfDay);
    // REDIRECTED(StartClock);
    // REDIRECTED(TimesOfDay);
    // REDIRECTED(StopRTC);
    // REDIRECTED(StartRTC);
    // REDIRECTED(StageRTCTimeForSave);
    // REDIRECTED(v_FixDays);
    // REDIRECTED(ClockContinue);
    // REDIRECTED(BetaTimesOfDay);

    // engine/math/print_num.c
    REDIRECTED(v_PrintNum);

    // engine/math/math.c
    REDIRECTED(v_Multiply);
    REDIRECTED(v_Divide);

    // engine/battle/hidden_power.c
    // REDIRECTED(HiddenPowerDamage);

    // engine/phone/phonering_copytilemapatonce.c
    CONVERTED(PhoneRing_CopyTilemapAtOnce);
    
    // engine/battle/check_battle_scene.c
    REDIRECTED(CheckBattleScene);

    // engine/rtc/print_hours_mins.c
    // REDIRECTED(String_PM);
    REDIRECTED(PrintHoursMins);
    // REDIRECTED(String_AM);
    // REDIRECTED(PrintFiveDigitNumber);

    // engine/overworld/init_map.c
    REDIRECTED(HDMATransfer_FillBGMap0WithBlack);
    REDIRECTED(LoadFonts_NoOAMUpdate);
    REDIRECTED(ReanchorBGMap_NoOAMUpdate);

    // engine/overworld/map_object_action.c
    // REDIRECTED(SetFacingStanding);
    // REDIRECTED(SetFacingWeirdTree);
    // REDIRECTED(SetFacingGrassShake);
    // REDIRECTED(SetFacingEmote);
    // REDIRECTED(CounterclockwiseSpinAction);
    // REDIRECTED(SetFacingFreezeBounce);
    // REDIRECTED(SetFacingStandAction);
    // REDIRECTED(SetFacingBigDollAsym);
    // REDIRECTED(SetFacingBigDollSym);
    // REDIRECTED(SetFacingBigDoll);
    // REDIRECTED(SetFacingFish);
    // REDIRECTED(SetFacingSkyfall);
    // REDIRECTED(SetFacingStepAction);
    // REDIRECTED(ObjectActionPairPointers);
    // REDIRECTED(SetFacingCounterclockwiseSpin2);
    // REDIRECTED(SetFacingBounce);
    // REDIRECTED(SetFacingBoulderDust);
    // REDIRECTED(SetFacingCurrent);
    // REDIRECTED(SetFacingShadow);
    // REDIRECTED(SetFacingCounterclockwiseSpin);
    // REDIRECTED(SetFacingBumpAction);

    // engine/math/sine.c
    // REDIRECTED(v_Sine);

    // engine/overworld/landmarks.c
    REDIRECTED(RegionCheck);
    REDIRECTED(GetLandmarkName);
    REDIRECTED(GetLandmarkCoords);

    // engine/battle/read_trainer_party.c
    REDIRECTED(TrainerType1);
    REDIRECTED(CopyTrainerName);
    REDIRECTED(TrainerType3);
    CONVERTED(ReadTrainerParty);
    // REDIRECTED(TrainerTypes);
    REDIRECTED(TrainerType4);
    REDIRECTED(TrainerType2);
    REDIRECTED(Battle_GetTrainerName);
    REDIRECTED(IncompleteCopyNameFunction);
    CONVERTED(ComputeTrainerReward);
    REDIRECTED(GetTrainerName);

    // engine/battle_anims/anim_commands.c
    REDIRECTED(PlayBattleAnim);
    REDIRECTED(BattleAnimCmd_ClearObjs);
    REDIRECTED(BattleAnimCmd_DropSub);
    REDIRECTED(BattleAnimCmd_BattlerGFX_2Row);
    REDIRECTED(BattleAnimCmd_1GFX);
    REDIRECTED(BattleAnimClearHud);
    REDIRECTED(BattleAnimCmd_ResetObp0);
    REDIRECTED(v_PlayBattleAnim);
    REDIRECTED(BattleAnimCmd_Jump);
    REDIRECTED(BattleAnimCmd_OBP0);
    REDIRECTED(RunBattleAnimCommand);
    REDIRECTED(BattleAnimCmd_Call);
    REDIRECTED(BattleAnimCmd_SetVar);
    REDIRECTED(BattleAnimCmd_IncVar);
    REDIRECTED(BattleAnimCmd_IncObj);
    REDIRECTED(BattleAnimCmd_IncBGEffect);
    REDIRECTED(RunBattleAnimScript);
    REDIRECTED(BattleAnimRequestPals);
    REDIRECTED(BattleAnimCmd_BeatUp);
    REDIRECTED(BattleAnimCmd_OAMOff);
    REDIRECTED(BattleAnimCmd_OBP1);
    REDIRECTED(BattleAnimCmd_3GFX);
    REDIRECTED(BattleAnimRestoreHuds);
    REDIRECTED(BattleAnimCmd_Transform);
    REDIRECTED(BattleAnimCmd_F7);
    REDIRECTED(BattleAnimCmd_Cry);
    REDIRECTED(BattleAnimCmd_5GFX);
    REDIRECTED(BattleAnimCmd_Ret);
    REDIRECTED(BattleAnimCmd_E7);
    REDIRECTED(BattleAnimCmd_Loop);
    REDIRECTED(BattleAnimCmd_Sound);
    REDIRECTED(BattleAnimCmd_ED);
    REDIRECTED(ClearBattleAnims);
    REDIRECTED(BattleAnim_RevertPals);
    REDIRECTED(BattleAnimCmd_BGP);
    REDIRECTED(GetMinimizePic);
    REDIRECTED(BattleAnimCmd_KeepSprites);
    REDIRECTED(BattleAnimCmd_Obj);
    REDIRECTED(BattleAnimCmd_EA);
    REDIRECTED(BattleAnimCmd_IfParamAnd);
    REDIRECTED(BattleAnim_ClearOAM);
    REDIRECTED(ClearActorHud);
    REDIRECTED(BattleAnimCmd_BattlerGFX_1Row);
    REDIRECTED(BattleAnimCmd_CheckPokeball);
    REDIRECTED(BattleAnimCmd_EC);
    REDIRECTED(BattleAnimCmd_UpdateActorPic);
    REDIRECTED(BattleAnim_SetOBPals);
    REDIRECTED(BattleAnimCmd_IfParamEqual);
    REDIRECTED(BattleAnimCmd_MinimizeOpp);
    REDIRECTED(BattleAnimCmd_4GFX);
    REDIRECTED(BattleAnimCmd_RaiseSub);
    REDIRECTED(BattleAnimCmd_JumpUntil);
    REDIRECTED(BattleAnimCmd_OAMOn);
    REDIRECTED(CopyMinimizePic);
    REDIRECTED(BattleAnimCmd_BGEffect);
    REDIRECTED(BattleAnim_UpdateOAM_All);
    REDIRECTED(PlaceWindowOverBattleTextbox);
    // REDIRECTED(BattleAnimCommands);
    REDIRECTED(BattleAnimCmd_F5);
    CONVERTED(BattleAnimDelayFrame);
    REDIRECTED(MinimizePic);
    REDIRECTED(PlayHitSound);
    REDIRECTED(BattleAnimCmd_IfVarEqual);
    REDIRECTED(GetSubstitutePic);
    REDIRECTED(BattleAnimRunScript);
    REDIRECTED(BattleAnimCmd_Minimize);
    REDIRECTED(BattleAnim_SetBGPals);
    REDIRECTED(BattleAnimCmd_F6);
    REDIRECTED(BattleAnimCmd_2GFX);
    REDIRECTED(BattleAnimCmd_SetObj);
    REDIRECTED(BattleAnimCmd_EB);
    REDIRECTED(BattleAnimAssignPals);

    // engine/battle/effect_commands.c
    REDIRECTED(BattleCommand_TriStatusChance);
    REDIRECTED(BattleCommand_AccuracyDown);
    REDIRECTED(DoEnemyTurn);
    REDIRECTED(BattleCommand_MoveAnim);
    REDIRECTED(CalcEnemyStats);
    REDIRECTED(PrintParalyze);
    REDIRECTED(BattleCommand_Defrost);
    REDIRECTED(CheckDamageStatsCritical);
    REDIRECTED(AppearUserLowerSub);
    REDIRECTED(BattleCommand_OHKO);
    REDIRECTED(LoadMoveAnim);
    REDIRECTED(EndMoveEffect);
    REDIRECTED(BattleCommand_CheckTurn);
    REDIRECTED(BattleCommand_SuperEffectiveText);
    REDIRECTED(BattleCommand_StatUpMessage);
    REDIRECTED(BattleCommand_Charge);
    REDIRECTED(SafeCheckSafeguard);
    REDIRECTED(BattleCommand_SpeedUp);
    REDIRECTED(BattleCommand_StartLoop);
    REDIRECTED(LightBallBoost);
    REDIRECTED(SetBattleDraw);
    REDIRECTED(PlayDamageAnim);
    REDIRECTED(BattleCommand_DrainTarget);
    REDIRECTED(BattleCommand_DefenseUp2);
    REDIRECTED(GetStatName);
    REDIRECTED(BattleCommand_LowerSub);
    REDIRECTED(BattleCommand_FinishConfusingTarget);
    REDIRECTED(BattleCommand_PoisonTarget);
    REDIRECTED(TruncateHL_BC);
    REDIRECTED(SpeciesItemBoost);
    REDIRECTED(BattleCommand_SpecialDefenseDown);
    REDIRECTED(BattleCommand_HealDay);
    REDIRECTED(BattleCommand_HeldFlinch);
    REDIRECTED(BattleCommand_Curl);
    // REDIRECTED(BattleCommand_StatUpDownAnim);
    REDIRECTED(LoadAnim);
    REDIRECTED(IgnoreSleepOnly);
    REDIRECTED(HitConfusion);
    REDIRECTED(GetUserItem);
    REDIRECTED(AppearUserRaiseSub);
    REDIRECTED(DittoMetalPowder);
    REDIRECTED(HitSelfInConfusion);
    REDIRECTED(SapHealth);
    REDIRECTED(BattleCommand_UsedMoveText);
    REDIRECTED(DoMove);
    REDIRECTED(BattleCommand_SpecialAttackUp);
    REDIRECTED(BattleCommand_FlinchTarget);
    REDIRECTED(BattleCommand_Screen);
    REDIRECTED(PlayUserBattleAnim);
    REDIRECTED(DoPlayerTurn);
    REDIRECTED(BattleCommand_RageDamage);
    REDIRECTED(BattleCommand_DefenseUp);
    REDIRECTED(BattleCommand_MoveDelay);
    REDIRECTED(BattleCommand_RaiseSub);
    REDIRECTED(GetMoveByte);
    REDIRECTED(BattleCommand_EvasionDown2);
    REDIRECTED(CalcPlayerStats);
    REDIRECTED(BattleCommand_FailureText);
    REDIRECTED(GetOpponentItem);
    REDIRECTED(PrintDidntAffect);
    REDIRECTED(TryLowerStat);
    REDIRECTED(CheckHiddenOpponent);
    REDIRECTED(BattleCommand_CheckHit);
    REDIRECTED(BattleCommand_StatDownMessage);
    REDIRECTED(DoSubstituteDamage);
    REDIRECTED(BattleCommand_AccuracyDown2);
    REDIRECTED(BattleCommand_DefenseDown);
    REDIRECTED(BattleCommand_BideFailText);
    REDIRECTED(BattleCommand_MoveAnimNoSub);
    REDIRECTED(BattleCommand_DamageCalc);
    REDIRECTED(BattleCommand_RechargeNextTurn);
    REDIRECTED(BattleCommand_Critical);
    REDIRECTED(BattleCommand_DefenseDown2);
    REDIRECTED(BattleCommand_LowerSubNoAnim);
    // REDIRECTED(SkipToBattleCommand);
    // REDIRECTED(EnemyAttackDamage);
    REDIRECTED(BattleCommand_DefrostOpponent);
    REDIRECTED(FailMove);
    REDIRECTED(BattleCommand_Rampage);
    REDIRECTED(BattleCommand_HealNite);
    REDIRECTED(PrintDidntAffect2);
    REDIRECTED(AnimateCurrentMoveEitherSide);
    REDIRECTED(BattleCommand_BuildOpponentRage);
    REDIRECTED(BattleCommand_CheckRampage);
    REDIRECTED(BattleCommand_EffectChance);
    REDIRECTED(BattleCommand_Unused5D);
    REDIRECTED(CheckSubstituteOpp);
    REDIRECTED(BattleCommand_ResetStats);
    REDIRECTED(ResetActorDisable);
    REDIRECTED(DoTurn);
    REDIRECTED(BattleCommand_FreezeTarget);
    REDIRECTED(DoEnemyDamage);
    REDIRECTED(BattleEffect_ButItFailed);
    REDIRECTED(BattleCommand_SpeedUp2);
    REDIRECTED(AnimateFailedMove);
    REDIRECTED(CheckEnemyTurn);
    REDIRECTED(PrintNothingHappened);
    REDIRECTED(FailText_CheckOpponentProtect);
    REDIRECTED(BattleCommand_AttackDown);
    REDIRECTED(CheckMoveTypeMatchesTarget);
    REDIRECTED(BattleCommand_DoubleFlyingDamage);
    REDIRECTED(TryPrintButItFailed);
    REDIRECTED(BattleCommand_ClearText);
    REDIRECTED(BattleCommand_CriticalText);
    REDIRECTED(PlayOpponentBattleAnim);
    REDIRECTED(BattleCommand_Stab);
    REDIRECTED(BattleCommand_ConfuseTarget);
    REDIRECTED(BattleCommand_EvasionUp);
    REDIRECTED(UpdateMoveData);
    REDIRECTED(BattleCommand_BurnTarget);
    REDIRECTED(CheckTypeMatchup);
    REDIRECTED(CheckMimicUsed);
    REDIRECTED(CheckMist);
    REDIRECTED(BattleCommand_SpecialDefenseUp2);
    REDIRECTED(BattleCommand_ForceSwitch);
    REDIRECTED(AnimateCurrentMove);
    REDIRECTED(GetMoveData);
    REDIRECTED(BattleCommand_DamageVariation);
    REDIRECTED(PrintDoesntAffect);
    REDIRECTED(MoveDisabled);
    REDIRECTED(BattleCommand_Unused3C);
    REDIRECTED(BattleCommand_SpecialAttackDown2);
    REDIRECTED(BattleCommand_ApplyDamage);
    REDIRECTED(EndRechargeOpp);
    REDIRECTED(v_CheckBattleScene);
    REDIRECTED(CheckUserIsCharging);
    REDIRECTED(BattleCommand_Paralyze);
    REDIRECTED(ClearLastMove);
    REDIRECTED(DoPlayerDamage);
    REDIRECTED(CheckOpponentWentFirst);
    REDIRECTED(BattleCommand_StatUp);
    REDIRECTED(DisappearUser);
    REDIRECTED(BattleCommand_TrapTarget);
    REDIRECTED(BattleCommand_ParalyzeTarget);
    REDIRECTED(BattleCommand_Recoil);
    REDIRECTED(BattleCommand_DoubleMinimizeDamage);
    REDIRECTED(CalcBattleStats);
    REDIRECTED(BattleCommand_Confuse);
    REDIRECTED(PoisonOpponent);
    REDIRECTED(BattleCommand_StatDownFailText);
    REDIRECTED(ResetMiss);
    REDIRECTED(BattleCommand_CheckCharge);
    REDIRECTED(LowerStat);
    REDIRECTED(DoubleDamage);
    REDIRECTED(BattleCommand_AttackUp2);
    REDIRECTED(BattleCommand_RaiseSubNoAnim);
    REDIRECTED(GetItemHeldEffect);
    REDIRECTED(BattleCommand_SpecialDefenseUp);
    REDIRECTED(BattleCommand_DamageStats);
    REDIRECTED(BattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit);
    REDIRECTED(BattleCommand_StatUpFailText);
    REDIRECTED(OpponentCantMove);
    REDIRECTED(CheckUserMove);
    REDIRECTED(CheckIfTargetIsPoisonType);
    REDIRECTED(BattleCommand_Poison);
    REDIRECTED(CheckPlayerHasMonToSwitchTo);
    REDIRECTED(MinimizeDropSub);
    REDIRECTED(CheckTurn);
    REDIRECTED(FarPlayBattleAnimation);
    REDIRECTED(BattleCommand_AllStatsUp);
    REDIRECTED(BattleCommand_StatUpAnim);
    REDIRECTED(BattleCommand_SpeedDown2);
    REDIRECTED(EndTurn);
    REDIRECTED(BattleCheckTypeMatchup);
    REDIRECTED(BattleCommand_EvasionUp2);
    REDIRECTED(CallBattleCore);
    REDIRECTED(BattleCommand_ResetTypeMatchup);
    REDIRECTED(FailMimic);
    REDIRECTED(BattleCommand_CheckSafeguard);
    REDIRECTED(PrintButItFailed);
    REDIRECTED(BattleCommand_AttackUp);
    REDIRECTED(BattleCommand_DoubleUndergroundDamage);
    REDIRECTED(RaiseStat);
    REDIRECTED(BattleCommand_SleepTarget);
    REDIRECTED(BattleCommand_StatDown);
    REDIRECTED(BattleCommand_EndLoop);
    REDIRECTED(BattleCommand_CheckFaint);
    REDIRECTED(BattleCommand_SwitchTurn);
    REDIRECTED(BattleCommand_FakeOut);
    REDIRECTED(FlinchTarget);
    REDIRECTED(BattleCommand_EatDream);
    REDIRECTED(BattleCommand_SpeedDown);
    REDIRECTED(BattleCommand_HealMorn);
    REDIRECTED(BattleCommand_AccuracyUp);
    REDIRECTED(BattleCommand_Heal);
    REDIRECTED(BattleCommand_SpecialDefenseDown2);
    // REDIRECTED(PlayerAttackDamage);
    REDIRECTED(BattleCommand_SkipSunCharge);
    REDIRECTED(BattleCommand_DoTurn);
    REDIRECTED(BattleCommand_SpecialAttackUp2);
    // REDIRECTED(BattleCommand_TimeBasedHealContinue);
    REDIRECTED(ThickClubBoost);
    REDIRECTED(BattleCommand_SuperEffectiveLoopText);
    REDIRECTED(CantMove);
    REDIRECTED(BattleCommand_CheckObedience);
    REDIRECTED(BattleCommand_StatDownAnim);
    REDIRECTED(Defrost);
    REDIRECTED(BattleCommand_ClearMissDamage);
    REDIRECTED(BattleCommand_ConstantDamage);
    REDIRECTED(BattleCommand_AccuracyUp2);
    REDIRECTED(GetFailureResultText);
    REDIRECTED(BattleCommand_SpecialAttackDown);
    REDIRECTED(BattleCommand_EvasionDown);
    REDIRECTED(ResetTurn);
    REDIRECTED(PlayFXAnimID);
    REDIRECTED(GetMoveAttr);
    REDIRECTED(BattleCommand_AttackDown2);
    REDIRECTED(BattleCommand_ArenaTrap);

    // engine/overworld/scripting.c
    // REDIRECTED(ExitScriptSubroutine);
    // REDIRECTED(Script_wait);
    // REDIRECTED(Script_warpcheck);
    // REDIRECTED(Script_addcellnum);
    // REDIRECTED(Script_playsound);
    // REDIRECTED(Script_readvar);
    // REDIRECTED(Script_verticalmenu);
    // REDIRECTED(Script_changeblock);
    // REDIRECTED(Script_addval);
    // REDIRECTED(Script_loadwildmon);
    // REDIRECTED(Script_farjumptext);
    // REDIRECTED(Script_readmem);
    // REDIRECTED(Script_follownotexact);
    // REDIRECTED(CopyConvertedText);
    // REDIRECTED(Script_givepoke);
    // REDIRECTED(LoadCoinAmountToMem);
    // REDIRECTED(Script_credits);
    // REDIRECTED(Script_randomwildmon);
    // REDIRECTED(Script_hangup);
    // REDIRECTED(Script__2dmenu);
    // REDIRECTED(Script_closepokepic);
    // REDIRECTED(Script_loadpikachudata);
    // REDIRECTED(Script_getnum);
    // REDIRECTED(Script_wildon);
    // REDIRECTED(Script_getitemname);
    // REDIRECTED(Script_checkcellnum);
    // REDIRECTED(Script_yesorno);
    // REDIRECTED(Script_trainertext);
    // REDIRECTED(Script_itemnotify);
    // REDIRECTED(Script_sdefer);
    // REDIRECTED(Script_reloadmappart);
    // REDIRECTED(Script_iffalse);
    // REDIRECTED(GetPocketName);
    // REDIRECTED(Script_takeitem);
    // REDIRECTED(RunScriptCommand);
    // REDIRECTED(Script_endifjustbattled);
    // REDIRECTED(Script_dontrestartmapmusic);
    // REDIRECTED(Script_refreshscreen);
    // REDIRECTED(UnusedClosetextScript);
    // REDIRECTED(Script_waitbutton);
    // REDIRECTED(Script_special);
    // REDIRECTED(Script_writetext);
    // REDIRECTED(Script_repeattext);
    // REDIRECTED(Script_encountermusic);
    // REDIRECTED(Script_trainerflagaction);
    // REDIRECTED(CurItemName);
    // REDIRECTED(Script_ifnotequal);
    // REDIRECTED(Script_setflag);
    // REDIRECTED(Script_variablesprite);
    // REDIRECTED(Script_checkmapscene);
    // REDIRECTED(StopScript);
    // REDIRECTED(Script_verbosegiveitemvar);
    // REDIRECTED(Script_delcmdqueue);
    // REDIRECTED(Script_specialphonecall);
    // REDIRECTED(Script_pocketisfull);
    // REDIRECTED(Script_battletowertext);
    // REDIRECTED(Script_playmapmusic);
    // REDIRECTED(Script_warpfacing);
    // REDIRECTED(Script_loadvar);
    // REDIRECTED(StartScript);
    // REDIRECTED(Script_checkcoins);
    // REDIRECTED(Script_blackoutmod);
    // REDIRECTED(ShowEmoteScript);
    // REDIRECTED(Script_gettrainername);
    // REDIRECTED(Script_scall);
    // REDIRECTED(ApplyMovement);
    // REDIRECTED(LoadMoneyAmountToMem);
    // REDIRECTED(Script_checkphonecall);
    // REDIRECTED(Script_pokepic);
    // REDIRECTED(Script_applymovement);
    // REDIRECTED(Script_ifless);
    // REDIRECTED(Script_musicfadeout);
    // REDIRECTED(Script_farsjump);
    // REDIRECTED(Script_giveegg);
    // REDIRECTED(Script_givemoney);
    // REDIRECTED(Script_checktime);
    // REDIRECTED(Script_waitsfx);
    // REDIRECTED(Script_verbosegiveitem);
    // REDIRECTED(UnfreezeFollowerObject);
    // REDIRECTED(Script_setmapscene);
    // REDIRECTED(Script_takemoney);
    // REDIRECTED(PutItemInPocketText);
    // REDIRECTED(Script_endcallback);
    // REDIRECTED(Script_loadmem);
    // REDIRECTED(Script_writecmdqueue);
    // REDIRECTED(Script_loadtrainer);
    // REDIRECTED(Script_delcellnum);
    // REDIRECTED(DoScene);
    // REDIRECTED(Script_stopfollow);
    // REDIRECTED(Script_callstd);
    // REDIRECTED(Script_promptbutton);
    // REDIRECTED(Script_writeobjectxy);
    // REDIRECTED(Script_setevent);
    // REDIRECTED(Script_phonecall);
    // REDIRECTED(WaitScriptMovement);
    // REDIRECTED(Script_faceplayer);
    // REDIRECTED(Script_trade);
    // REDIRECTED(ScriptCall);
    // REDIRECTED(ContinueToGetName);
    // REDIRECTED(Script_specialsound);
    // REDIRECTED(Script_jumptext);
    // REDIRECTED(Script_pause);
    // REDIRECTED(ReturnFromCredits);
    // REDIRECTED(Script_giveitem);
    // REDIRECTED(Script_closetext);
    // REDIRECTED(GetScriptObject);
    // REDIRECTED(CallCallback);
    // REDIRECTED(Script_loadmenu);
    // REDIRECTED(Script_reloadmapafterbattle);
    // REDIRECTED(Script_gettrainerclassname);
    // REDIRECTED(Script_deactivatefacing);
    // REDIRECTED(Script_getcurlandmarkname);
    // REDIRECTED(CheckScript);
    // REDIRECTED(GiveItemScript);
    // REDIRECTED(ScriptCommandTable);
    // REDIRECTED(SkipTwoScriptBytes);
    // REDIRECTED(Script_earthquake);
    // REDIRECTED(Script_cry);
    // REDIRECTED(Script_ifgreater);
    // REDIRECTED(Script_setval);
    // REDIRECTED(ResetStringBuffer1);
    // REDIRECTED(Script_givecoins);
    // REDIRECTED(Script_reloadmap);
    // REDIRECTED(ScriptJump);
    // REDIRECTED(GetVarAction);
    // REDIRECTED(Script_checkevent);
    // REDIRECTED(Script_warp);
    // REDIRECTED(Script_pokemart);
    // REDIRECTED(Script_checkmoney);
    // REDIRECTED(WaitScript);
    // REDIRECTED(Script_warpsound);
    // REDIRECTED(Script_checkflag);
    // REDIRECTED(GiveItemScript_DummyFunction);
    // REDIRECTED(Script_checkscene);
    // REDIRECTED(Script_applymovementlasttalked);
    // REDIRECTED(Script_askforphonenumber);
    // REDIRECTED(CompareMoneyAction);
    // REDIRECTED(Script_takecoins);
    // REDIRECTED(Script_farwritetext);
    // REDIRECTED(Script_jumptextfaceplayer);
    // REDIRECTED(Script_checkver_duplicate);
    // REDIRECTED(Script_setscene);
    // REDIRECTED(Script_iftrue);
    // REDIRECTED(Script_moveobject);
    // REDIRECTED(Script_writevar);
    // REDIRECTED(Script_checkpoke);
    // REDIRECTED(Script_checksave);
    // REDIRECTED(EarthquakeMovement);
    // REDIRECTED(Script_givepokemail);
    // REDIRECTED(Script_xycompare);
    // REDIRECTED(JumpTextScript);
    // REDIRECTED(Script_getlandmarkname);
    // REDIRECTED(Script_getcoins);
    // REDIRECTED(Script_loadtemptrainer);
    // REDIRECTED(Script_getname);
    // REDIRECTED(Script_end);
    // REDIRECTED(Script_newloadmap);
    // REDIRECTED(Script_checkver);
    // REDIRECTED(Script_writemem);
    // REDIRECTED(Script_stopandsjump);
    // REDIRECTED(StdScript);
    // REDIRECTED(Script_closewindow);
    // REDIRECTED(Script_autoinput);
    // REDIRECTED(Script_elevator);
    // REDIRECTED(Script_ifequal);
    // REDIRECTED(ApplyObjectFacing);
    // REDIRECTED(Script_playmusic);
    // REDIRECTED(Script_follow);
    // REDIRECTED(ApplyEventActionAppearDisappear);
    // REDIRECTED(Script_halloffame);
    // REDIRECTED(Script_endall);
    // REDIRECTED(ConvertLandmarkToText);
    // REDIRECTED(Script_warpmod);
    // REDIRECTED(Script_showemote);
    // REDIRECTED(Script_checkpokemail);
    // REDIRECTED(Script_random);
    // REDIRECTED(Script_writeunusedbyte);
    // REDIRECTED(Script_changemapblocks);
    // REDIRECTED(Script_memjump);
    // REDIRECTED(Script_wildoff);
    // REDIRECTED(EndScript);
    // REDIRECTED(Script_memcallasm);
    // REDIRECTED(Script_getmoney);
    // REDIRECTED(Script_memcall);
    // REDIRECTED(Script_callasm);
    // REDIRECTED(Script_turnobject);
    // REDIRECTED(Script_catchtutorial);
    // REDIRECTED(Script_checkjustbattled);
    // REDIRECTED(Script_farscall);
    // REDIRECTED(GetMoneyAccount);
    // REDIRECTED(Script_getstring);
    // REDIRECTED(v_EngineFlagAction);
    // REDIRECTED(JumpTextFacePlayerScript);
    // REDIRECTED(Script_loademote);
    // REDIRECTED(Script_swarm);
    // REDIRECTED(Script_clearflag);
    // REDIRECTED(Script_disappear);
    // REDIRECTED(GetStringBuffer);
    // REDIRECTED(Script_clearevent);
    // REDIRECTED(Script_scripttalkafter);
    // REDIRECTED(ScriptEvents);
    // REDIRECTED(Script_checkitem);
    // REDIRECTED(Script_getmonname);
    // REDIRECTED(Script_enableevents);
    // REDIRECTED(Script_winlosstext);
    // REDIRECTED(Script_faceobject);
    // REDIRECTED(Script_appear);
    // REDIRECTED(Script_describedecoration);
    // REDIRECTED(Script_sjump);
    // REDIRECTED(Script_fruittree);
    // REDIRECTED(PocketIsFullText);
    // REDIRECTED(Script_opentext);
    // REDIRECTED(Script_setlasttalked);
    // REDIRECTED(Script_jumpstd);
    // REDIRECTED(EnableScriptMode);
    // REDIRECTED(Script_startbattle);
    // REDIRECTED(Script_reloadend);

    // engine/items/items.c
    // REDIRECTED(CheckSelectableItem);
    // REDIRECTED(v_TossItem);
    // REDIRECTED(CheckItemMenu);
    // REDIRECTED(ItemAttr_ReturnCarry);
    // REDIRECTED(TossKeyItem);
    // REDIRECTED(CheckTheItem);
    // REDIRECTED(CheckItemContext);
    // REDIRECTED(TossTMHM);
    // REDIRECTED(GetItemAttr);
    // REDIRECTED(CheckKeyItems);
    // REDIRECTED(GetPocketCapacity);
    // REDIRECTED(PutItemInPocket);
    // REDIRECTED(GetNumberedTMHM);
    // REDIRECTED(GetTMHMNumber);
    // REDIRECTED(v_CheckTossableItem);
    // REDIRECTED(v_CheckItem);
    // REDIRECTED(RemoveItemFromPocket);
    // REDIRECTED(CheckTMHM);
    // REDIRECTED(DoesHLEqualNumItems);
    // REDIRECTED(ReceiveTMHM);
    // REDIRECTED(v_ReceiveItem);
    // REDIRECTED(CheckItemPocket);
    // REDIRECTED(ReceiveKeyItem);
    // REDIRECTED(GetItemPrice);

    // engine/events/engine_flags.c
    // REDIRECTED(EngineFlagAction);

    // engine/overworld/events.c
    // REDIRECTED(PlayerEventScriptPointers);
    // REDIRECTED(FallIntoMapScript);
    // CONVERTED(OverworldLoop);
    // REDIRECTED(OWPlayerInput);
    // REDIRECTED(DisableCoordEvents);
    // REDIRECTED(UnusedPlayerEventScript);
    // REDIRECTED(TryObjectEvent);
    CONVERTED(EnableEvents);
    // REDIRECTED(CanUseSweetScent);
    // REDIRECTED(CheckStepCountScriptFlag);
    // REDIRECTED(PlayerMovement);
    // REDIRECTED(RunMemScript);
    // REDIRECTED(CountStep);
    // REDIRECTED(RunSceneScript);
    // REDIRECTED(StartMenuCallback);
    // REDIRECTED(v_CheckObjectEnteringVisibleRange);
    // REDIRECTED(MaxOverworldDelay);
    // CONVERTED(MapEvents);
    // REDIRECTED(v_TryWildEncounter_BugContest);
    // REDIRECTED(WarpToNewMapScript);
    // REDIRECTED(CheckMenuOW);
    CONVERTED(EnableWildEncounters);
    // REDIRECTED(CheckWildEncounterCooldown);
    // REDIRECTED(RandomEncounter);
    // REDIRECTED(DisableWildEncounters);
    // REDIRECTED(TryTileCollisionEvent);
    CONVERTED(HandleMapBackground);
    // REDIRECTED(ObjectEventTypeArray);
    // REDIRECTED(DoRepelStep);
    // REDIRECTED(PlayTalkObject);
    // REDIRECTED(CheckBGEventFlag);
    // REDIRECTED(SelectMenuScript);
    // REDIRECTED(ChooseWildEncounter_BugContest);
    // REDIRECTED(PlayerMovementPointers);
    // REDIRECTED(ChangeDirectionScript);
    // REDIRECTED(InvalidEventScript);
    CONVERTED(WarpToSpawnPoint);
    // REDIRECTED(LandAfterPitfallScript);
    // REDIRECTED(EdgeWarpScript);
    // REDIRECTED(EnableCoordEvents);
    // REDIRECTED(CheckTrainerBattle_GetPlayerEvent);
    // REDIRECTED(Dummy_CheckScriptFlags2Bit5);
    // REDIRECTED(EnableStepCount);
    // REDIRECTED(BGEventJumptable);
    // REDIRECTED(DisableStepCount);
    // REDIRECTED(SelectMenuCallback);
    // CONVERTED(DisableEvents);
    // CONVERTED(EnterMap);
    // REDIRECTED(TryWildEncounter_BugContest);
    // REDIRECTED(CheckAPressOW);
    // REDIRECTED(CheckCoordEventScriptFlag);
    // REDIRECTED(TryBGEvent);
    // REDIRECTED(CheckTileEvent);
    // REDIRECTED(StartMenuScript);
    // REDIRECTED(EnableWarpsConnxns);
    // REDIRECTED(HatchEggScript);
    // REDIRECTED(DoPlayerEvent);
    CONVERTED(ResetOverworldDelay);
    // REDIRECTED(PlayerEvents);
    // REDIRECTED(StartMap);
    // REDIRECTED(HandleMap);
    // REDIRECTED(NextOverworldFrame);
    // CONVERTED(SetUpFiveStepWildEncounterCooldown);
    // REDIRECTED(DoBikeStep);
    // REDIRECTED(CheckTimeEvents);
    // REDIRECTED(CheckWildEncountersScriptFlag);
    // REDIRECTED(DisableWarpsConnxns);
    // REDIRECTED(HandleMapTimeAndJoypad);
    // REDIRECTED(CheckPlayerState);
    // REDIRECTED(SetMinTwoStepWildEncounterCooldown);
    // REDIRECTED(LoadScriptBDE);
    // REDIRECTED(UnusedWait30Frames);
    // REDIRECTED(WildBattleScript);
    // REDIRECTED(CheckWarpConnxnScriptFlag);
    // REDIRECTED(HandleMapObjects);
    // REDIRECTED(CheckBit5_ScriptFlags2);

    // engine/overworld/overworld.c
    // REDIRECTED(v_GetSpritePalette);
    // REDIRECTED(LoadEmote);
    // REDIRECTED(AddOutdoorSprites);
    // REDIRECTED(GetMonSprite);
    // REDIRECTED(GetUsedSprites);
    // REDIRECTED(RefreshSprites);
    // REDIRECTED(v_DoesSpriteHaveFacings);
    // REDIRECTED(LoadUsedSpritesGFX);
    // REDIRECTED(GetPlayerSprite);
    // REDIRECTED(GetUsedSprite);
    // REDIRECTED(v_RefreshSprites);
    // REDIRECTED(LoadAndSortSprites);
    // REDIRECTED(v_UpdatePlayerSprite);
    // REDIRECTED(ArrangeUsedSprites);
    // REDIRECTED(AddSpriteGFX);
    // REDIRECTED(SafeGetSprite);
    // REDIRECTED(LoadSpriteGFX);
    // REDIRECTED(v_ClearSprites);
    // REDIRECTED(GetEmote2bpp);
    // REDIRECTED(AddIndoorSprites);
    // REDIRECTED(AddMapSprites);
    // REDIRECTED(GetSprite);
    // REDIRECTED(SortUsedSprites);
    // REDIRECTED(GetSpriteLength);
    // REDIRECTED(LoadMiscTiles);

    // engine/battle/ai/move.c
    // REDIRECTED(AIScoringPointers);
    REDIRECTED(AIChooseMove);

    // engine/battle/ai/scoring.c
    REDIRECTED(AI_Setup);
    REDIRECTED(AI_Smart_DestinyBond);
    REDIRECTED(AI_Smart_Foresight);
    REDIRECTED(AI_Smart_EvasionUp);
    REDIRECTED(AICheckEnemyHalfHP);
    REDIRECTED(AICheckPlayerHalfHP);
    REDIRECTED(AI_Smart_BatonPass);
    REDIRECTED(AI_Smart_TrapTarget);
    REDIRECTED(AI_50_50);
    REDIRECTED(AI_None);
    REDIRECTED(AI_Smart_PriorityHit);
    REDIRECTED(AI_Smart_Synthesis);
    REDIRECTED(AI_Smart_AccuracyDown);
    REDIRECTED(AI_Smart_LightScreen);
    REDIRECTED(AI_Smart_EffectHandlers);
    REDIRECTED(AI_Status);
    REDIRECTED(AI_Basic);
    REDIRECTED(AI_Smart_Paralyze);
    REDIRECTED(AI_Smart_RainDance);
    REDIRECTED(AICheckPlayerQuarterHP);
    REDIRECTED(AI_Smart_SkullBash);
    REDIRECTED(AI_Smart_LeechHit);
    REDIRECTED(AI_Smart_Magnitude);
    REDIRECTED(AI_Smart_Ohko);
    REDIRECTED(AI_Smart_HyperBeam);
    REDIRECTED(AI_Smart_Endure);
    REDIRECTED(AICheckMaxHP);
    REDIRECTED(AI_Smart_Counter);
    REDIRECTED(AI_Smart_FuryCutter);
    REDIRECTED(AIGetEnemyMove);
    REDIRECTED(AI_Smart_DreamEater);
    REDIRECTED(AI_Smart_PsychUp);
    REDIRECTED(AI_Smart_SpDefenseUp2);
    REDIRECTED(AI_Types);
    REDIRECTED(AIScoring);
    REDIRECTED(AI_Smart_PainSplit);
    REDIRECTED(AI_Smart_Solarbeam);
    REDIRECTED(AI_Smart_LockOn);
    REDIRECTED(AI_Smart_Encore);
    REDIRECTED(AIBadWeatherType);
    REDIRECTED(AI_Smart_WeatherMove);
    REDIRECTED(AI_Smart);
    REDIRECTED(AI_Smart_Curse);
    REDIRECTED(AI_Smart_SunnyDay);
    REDIRECTED(AI_Smart_Attract);
    REDIRECTED(AIHasMoveEffect);
    REDIRECTED(AI_Smart_MorningSun);
    REDIRECTED(AIGoodWeatherType);
    REDIRECTED(AI_Smart_Sandstorm);
    REDIRECTED(AI_Smart_Rollout);
    REDIRECTED(AI_Smart_MirrorMove);
    REDIRECTED(AI_Smart_Thunder);
    REDIRECTED(AI_80_20);
    REDIRECTED(AI_Smart_Safeguard);
    REDIRECTED(AI_Smart_Reflect);
    REDIRECTED(AI_Smart_Nightmare);
    REDIRECTED(AI_Aggressive);
    REDIRECTED(AI_Smart_Sleep);
    REDIRECTED(AI_Smart_SuperFang);
    REDIRECTED(AI_Smart_AlwaysHit);
    REDIRECTED(AI_Offensive);
    REDIRECTED(AI_Smart_Rage);
    REDIRECTED(AI_Smart_Bide);
    REDIRECTED(AI_Smart_Thief);
    REDIRECTED(AICheckPlayerMaxHP);
    REDIRECTED(AI_Smart_ForceSwitch);
    REDIRECTED(AI_Smart_Snore);
    REDIRECTED(AI_Smart_Swagger);
    REDIRECTED(AIHasMoveInArray);
    REDIRECTED(AI_Smart_ResetStats);
    REDIRECTED(AI_Smart_Spite);
    REDIRECTED(AI_Smart_Toxic);
    REDIRECTED(AI_Smart_HiddenPower);
    REDIRECTED(AI_Smart_Fly);
    REDIRECTED(AI_Cautious);
    REDIRECTED(AICheckEnemyMaxHP);
    REDIRECTED(AI_Smart_Stomp);
    REDIRECTED(AI_Smart_Disable);
    REDIRECTED(AICheckEnemyQuarterHP);
    REDIRECTED(AI_Risky);
    REDIRECTED(AI_Smart_Earthquake);
    REDIRECTED(AI_Smart_Pursuit);
    REDIRECTED(AI_Smart_PerishSong);
    REDIRECTED(AI_Smart_Moonlight);
    REDIRECTED(AI_Smart_Conversion2);
    REDIRECTED(AI_Smart_Substitute);
    REDIRECTED(AI_Smart_Selfdestruct);
    REDIRECTED(AI_Smart_MeanLook);
    REDIRECTED(AI_Smart_RapidSpin);
    REDIRECTED(AI_Smart_Twister);
    REDIRECTED(AI_Smart_RazorWind);
    REDIRECTED(AI_Smart_HealBell);
    REDIRECTED(AI_Smart_Unused2B);
    REDIRECTED(AIDiscourageMove);
    REDIRECTED(AI_Smart_BellyDrum);
    REDIRECTED(AI_Smart_FutureSight);
    REDIRECTED(AI_Smart_DefrostOpponent);
    REDIRECTED(AICheckLastPlayerMon);
    CONVERTED(AIDamageCalc);
    REDIRECTED(AI_Smart_MirrorCoat);
    REDIRECTED(AI_Smart_LeechSeed);
    REDIRECTED(AICompareSpeed);
    REDIRECTED(AI_Smart_Protect);
    REDIRECTED(AI_Smart_FlameWheel);
    REDIRECTED(AI_Smart_SpeedDownHit);
    REDIRECTED(AI_Smart_SleepTalk);
    REDIRECTED(AI_Smart_Heal);
    REDIRECTED(AI_Smart_Gust);
    REDIRECTED(AI_Opportunist);
    REDIRECTED(AI_Smart_Confuse);
    REDIRECTED(AI_Smart_Reversal);
    REDIRECTED(AI_Smart_Mimic);

    // engine/menus/menu.c
    // REDIRECTED(v_2DMenu_);
    // REDIRECTED(Init2DMenuCursorPosition);
    // REDIRECTED(Menu_WasButtonPressed);
    // REDIRECTED(v_ExitMenu);
    // REDIRECTED(Function241d5);
    // REDIRECTED(Move2DMenuCursor);
    // REDIRECTED(Place2DMenuItemStrings);
    // REDIRECTED(Get2DMenuNumberOfColumns);
    // REDIRECTED(Get2DMenuNumberOfRows);
    // REDIRECTED(v_InitVerticalMenuCursor);
    // REDIRECTED(Get2DMenuSelection);
    // REDIRECTED(MobileMenuJoypad);
    // REDIRECTED(RestoreOverworldMapTiles);
    // REDIRECTED(Draw2DMenu);
    // REDIRECTED(v_StaticMenuJoypad);
    // REDIRECTED(v_InterpretMobileMenu);
    // REDIRECTED(v_InterpretBattleMenu);
    // REDIRECTED(Mobile_GetMenuSelection);
    // REDIRECTED(v_ScrollingMenuJoypad);
    // REDIRECTED(Error_Cant_ExitMenu);
    // REDIRECTED(v_PushWindow);
    // REDIRECTED(Do2DMenuRTCJoypad);
    // REDIRECTED(Place2DMenuCursor);
    // REDIRECTED(v_2DMenuInterpretJoypad);
    // REDIRECTED(MenuJoypadLoop);

    // engine/smallflag.c
    REDIRECTED(SmallFarFlagAction);

    // engine/gfx/load_font.c
    REDIRECTED(v_LoadFontsExtra2);
    REDIRECTED(StatsScreen_LoadFont);
    // REDIRECTED(EnableHDMAForGraphics);
    REDIRECTED(LoadHPBar);
    REDIRECTED(LoadBattleFontsHPBar);
    REDIRECTED(Get2bppOptionalHDMA);
    REDIRECTED(v_LoadFontsBattleExtra);
    REDIRECTED(v_LoadFontsExtra1);
    REDIRECTED(v_LoadStandardFont);
    REDIRECTED(LoadStatsScreenPageTilesGFX);
    REDIRECTED(Get1bppOptionalHDMA);
    REDIRECTED(LoadFrame);

    // engine/gfx/place_graphic.c
    REDIRECTED(PlaceGraphic);

    // engine/gfx/load_overworld_font.c
    REDIRECTED(LoadOverworldFont);

    // engine/gfx/mon_icons.c
    REDIRECTED(MoveList_InitAnimatedMonIcon);
    REDIRECTED(LoadOverworldMonIcon);
    REDIRECTED(FreezeMonIcons);
    REDIRECTED(UnfreezeMonIcons);
    REDIRECTED(GetMonIconDE);
    REDIRECTED(GetIcon_de);
    REDIRECTED(GetGFXUnlessMobile);
    REDIRECTED(PartyMenu_InitAnimatedMonIcon);
    REDIRECTED(GetSpeciesIcon);
    REDIRECTED(LoadMenuMonIcon);
    // REDIRECTED(HeldItemIcons);
    REDIRECTED(GetIconGFX);
    REDIRECTED(HoldSwitchmonIcon);
    REDIRECTED(Unused_GetPartyMenuMonIcon);
    REDIRECTED(SetPartyMonIconAnimSpeed);
    REDIRECTED(Trade_LoadMonIconGFX);
    REDIRECTED(GetIcon);
    REDIRECTED(Mobile_InitAnimatedMonIcon);
    REDIRECTED(FlyFunction_GetMonIcon);
    REDIRECTED(NamingScreen_InitAnimatedMonIcon);
    REDIRECTED(Mobile_InitPartyMenuBGPal71);
    REDIRECTED(GetMemIconGFX);
    REDIRECTED(GetIcon_a);
    REDIRECTED(InitPartyMenuIcon);
    REDIRECTED(ReadMonMenuIcon);

    // engine/pokemon/mail_2.c
    // REDIRECTED(Mail_Place14TileAlternatingRow);
    // REDIRECTED(ReadPartyMonMail);
    // REDIRECTED(MailGFX_PlaceMessage);
    // REDIRECTED(Mail_Draw2x2Graphic);
    // REDIRECTED(LoadLovelyMailGFX);
    // REDIRECTED(InvertBytes);
    // REDIRECTED(ReadAnyMail);
    // REDIRECTED(MailGFXPointers);
    // REDIRECTED(Mail_Place16TileAlternatingRow);
    // REDIRECTED(LoadEonMailGFX);
    // REDIRECTED(Mail_Draw16TileRow);
    // REDIRECTED(LoadMusicMailGFX);
    // REDIRECTED(LoadFlowerMailGFX);
    // REDIRECTED(Mail_Draw7TileRow);
    // REDIRECTED(LoadMailGFX_Color2);
    // REDIRECTED(LoadLiteBlueMailGFX);
    // REDIRECTED(MailGFX_GenerateMonochromeTilesColor2);
    // REDIRECTED(LovelyEonMail_PlaceIcons);
    // REDIRECTED(LoadMorphMailGFX);
    // REDIRECTED(FinishLoadingSurfLiteBlueMailGFX);
    // REDIRECTED(LoadBlueSkyMailGFX);
    // REDIRECTED(Mail_Place14TileAlternatingColumn);
    // REDIRECTED(Mail_PlaceAlternatingColumn);
    // REDIRECTED(DrawMailBorder);
    // REDIRECTED(LoadPortraitMailGFX);
    // REDIRECTED(Mail_DrawFullWidthBorder);
    // REDIRECTED(Mail_DrawLeftRightBorder);
    // REDIRECTED(LoadMailGFX_Color3);
    // REDIRECTED(DrawMailBorder2);
    // REDIRECTED(LoadSurfMailGFX);
    // REDIRECTED(Mail_Place18TileAlternatingRow);
    // REDIRECTED(Mail_Draw3x2Graphic);
    // REDIRECTED(LoadMirageMailGFX);
    // REDIRECTED(Mail_Place6TileRow);
    // REDIRECTED(Mail_PlaceAlternatingRow);
    // REDIRECTED(LoadMailGFX_Color1);
    // REDIRECTED(Mail_DrawTopBottomBorder);
    // REDIRECTED(Mail_Draw13TileRow);
    // REDIRECTED(Mail_DrawRowLoop);
    // REDIRECTED(Mail_Place16TileAlternatingColumn);
    // REDIRECTED(ItemIsMail);

    // engine/pokemon/party_menu.c
    // REDIRECTED(PlacePartyMonEvoStoneCompatibility);
    // REDIRECTED(PartyMenu2DMenuData);
    // REDIRECTED(SelectMonFromParty);
    // REDIRECTED(InitPartyMenuGFX);
    // REDIRECTED(YouHaveNoPKMNString);
    // REDIRECTED(GetPartyMenuQualityIndexes);
    // REDIRECTED(SelectTradeOrDayCareMon);
    // REDIRECTED(InitPartyMenuWithCancel);
    // REDIRECTED(PlacePartyHPBar);
    // REDIRECTED(PlacePartyMonLevel);
    // REDIRECTED(MoveToWhereString);
    // REDIRECTED(ChooseAMonString);
    // REDIRECTED(PlacePartyMonMobileBattleSelection);
    // REDIRECTED(InitPartyMenuLayout);
    // REDIRECTED(PrintPartyMenuText);
    // REDIRECTED(PartyMenuSelect);
    // REDIRECTED(PartyMenuCheckEgg);
    // REDIRECTED(ChooseAFemalePKMNString);
    // REDIRECTED(TeachWhichPKMNString);
    // REDIRECTED(PartyMenuStrings);
    // REDIRECTED(InitPartyMenuNoCancel);
    // REDIRECTED(PlacePartyMenuHPDigits);
    // REDIRECTED(PlacePartyMonTMHMCompatibility);
    // REDIRECTED(PlacePartyMonGender);
    // REDIRECTED(PlacePartyNicknames);
    // REDIRECTED(PlacePartymonHPBar);
    // REDIRECTED(ToWhichPKMNString);
    // REDIRECTED(ChooseAMalePKMNString);
    // REDIRECTED(LoadPartyMenuGFX);
    // REDIRECTED(WritePartyMenuTilemap);
    // REDIRECTED(PrintPartyMenuActionText);
    // REDIRECTED(UseOnWhichPKMNString);
    // REDIRECTED(WhichPKMNString);
    // REDIRECTED(PlacePartyMonStatus);

    // engine/overworld/load_map_part.c
    CONVERTED(v_LoadMapPart);

    // engine/tilesets/map_palettes.c
    // REDIRECTED(v_ScrollBGMapPalettes);
    // REDIRECTED(v_SwapTextboxPalettes);

    // engine/gfx/color.c
    REDIRECTED(ApplyPals);
    // REDIRECTED(GSIntro_LoadMonPalette);
    // REDIRECTED(HPBarPals);
    // REDIRECTED(ResetBGPals);
    // REDIRECTED(SGB_ClearVRAM);
    // REDIRECTED(UpdateSGBBorder);
    // REDIRECTED(GetPredefPal);
    // REDIRECTED(PushSGBBorder);
    // REDIRECTED(GetMonNormalOrShinyPalettePointer);
    // REDIRECTED(BattleObjectPals);
    // REDIRECTED(LoadHLPaletteIntoDE);
    // REDIRECTED(ClearBytes);
    // REDIRECTED(PushSGBPals);
    // REDIRECTED(GetFrontpicPalettePointer);
    // REDIRECTED(CopyFourPalettes);
    // REDIRECTED(SGBBorder_YetMorePalPushing);
    // REDIRECTED(PredefPals);
    // REDIRECTED(CGBCopyBattleObjectPals);
    // REDIRECTED(DiplomaPalettes);
    // REDIRECTED(LoadNthMiddleBGPal);
    // REDIRECTED(Intro_LoadPackPalettes);
    // REDIRECTED(LoadMapPals);
    // REDIRECTED(InitSGBBorder);
    // REDIRECTED(v_InitSGBBorderPals);
    // REDIRECTED(InitPartyMenuPalettes);
    // REDIRECTED(Unused_CheckShininess);
    // REDIRECTED(GetEnemyFrontpicPalettePointer);
    // REDIRECTED(v_PushSGBPals);
    // REDIRECTED(PartyMenuBGPalette);
    // REDIRECTED(CheckShininess);
    // REDIRECTED(SGBBorder_MorePalPushing);
    // REDIRECTED(SGB_ApplyCreditsPals);
    // REDIRECTED(SGBDelayCycles);
    // REDIRECTED(GetBattlemonBackpicPalettePointer);
    // REDIRECTED(LoadBetaPokerPalettes);
    // REDIRECTED(FemalePokegearPals);
    // REDIRECTED(LoadPalette_White_Col1_Col2_Black);
    // REDIRECTED(BetaPokerPals);
    // REDIRECTED(CGBCopyTwoPredefObjectPals);
    // REDIRECTED(CopyData);
    // REDIRECTED(SlotMachinePals);
    // REDIRECTED(PushSGBBorderPalsAndWait);
    // REDIRECTED(ApplyAttrmap);
    // REDIRECTED(MapObjectPals);
    // REDIRECTED(SGB_ApplyPartyMenuHPPals);
    // REDIRECTED(Intro_LoadMagikarpPalettes);
    // REDIRECTED(LoadTrainerClassPaletteAsNthBGPal);
    // REDIRECTED(GetTrainerPalettePointer);
    // REDIRECTED(ApplyMonOrTrainerPals);
    // REDIRECTED(UnusedGSTitleBGPals);
    // REDIRECTED(GetMonPalettePointer);
    // REDIRECTED(PartyMenuBGMobilePalette);
    // REDIRECTED(MalePokegearPals);
    // REDIRECTED(Intro_LoadAllPal0);
    // REDIRECTED(SGBBorderGFX);
    // REDIRECTED(TilesetBGPalette);
    // REDIRECTED(FillBoxCGB);
    // REDIRECTED(InitCGBPals);
    // REDIRECTED(CGB_ApplyPartyMenuHPPals);
    // REDIRECTED(WipeAttrmap);
    // REDIRECTED(PartyMenuOBPals);
    // REDIRECTED(InitPartyMenuOBPals);
    // REDIRECTED(ApplyHPBarPals);
    // REDIRECTED(ExpBarPalette);
    // REDIRECTED(CopyPalettes);
    // REDIRECTED(DrawDefaultTiles);
    // REDIRECTED(LoadMailPalettes);
    // REDIRECTED(Intro_LoadBetaIntroVenusaurPalettes);
    // REDIRECTED(UnusedBattleObjectPals);
    // REDIRECTED(GetPlayerOrMonPalettePointer);
    // REDIRECTED(UnusedGSTitleOBPals);
    // REDIRECTED(SGBBorder_PushBGPals);
    // REDIRECTED(LoadStatsScreenPals);
    // REDIRECTED(RoofPals);
    // REDIRECTED(LoadMonPaletteAsNthBGPal);
    // REDIRECTED(v_GetMonPalettePointer);
    // REDIRECTED(SGBBorderMapAndPalettes);

    // engine/gfx/crystal_layouts.c
    // REDIRECTED(TradeRoomPalette);
    // REDIRECTED(InitMG_Mobile_LinkTradePalMap);
    // REDIRECTED(v_CrystalCGB_NameCard);
    // REDIRECTED(v_CrystalCGB_MobileLayout1);
    // REDIRECTED(Function49742);
    // REDIRECTED(v_LoadTradeRoomBGPals);
    // REDIRECTED(v_InitMG_Mobile_LinkTradePalMap);
    // REDIRECTED(Crystal_FillBoxCGB);
    // REDIRECTED(Palette_TextBG7);
    // REDIRECTED(MG_Mobile_Layout_LoadPals);
    // REDIRECTED(v_CrystalCGB_MobileLayout0);
    // REDIRECTED(GetCrystalCGBLayout);
    // REDIRECTED(Crystal_WipeAttrmap);
    // REDIRECTED(Palette_MysteryGiftMobile);
    // REDIRECTED(Function49420);
    // CONVERTED(LoadOW_BGPal7);
    // REDIRECTED(MG_Mobile_Layout_CreatePalBoxes);

    // engine/events/map_name_sign.c
    // REDIRECTED(PlaceMapNameSign);
    // REDIRECTED(InitMapNameSign);
    // REDIRECTED(LoadMapNameSignGFX);
    // REDIRECTED(InitMapNameFrame);
    // REDIRECTED(InitMapSignAttrmap);
    // REDIRECTED(PlaceMapNameCenterAlign);
    // REDIRECTED(PlaceMapNameFrame);

    // engine/pokemon/stats_screen.c
    REDIRECTED(StatsScreen_LoadPage);
    REDIRECTED(StatsScreen_InitUpperHalf);
    REDIRECTED(StatsScreen_AnimateEgg);
    // REDIRECTED(OTString);
    REDIRECTED(MonStatsInit);
    REDIRECTED(StatsScreenSpaceGFX);
    REDIRECTED(EggStatsJoypad);
    REDIRECTED(GetNicknamenamePointer);
    REDIRECTED(StatsScreen_PlacePageSwitchArrows);
    REDIRECTED(StatsScreenMain);
    REDIRECTED(StatsScreen_PlaceHorizontalDivider);
    REDIRECTED(EggStatsScreen);
    REDIRECTED(StatsScreen_SetJumptableIndex);
    REDIRECTED(StatsScreen_LoadGFX);
    REDIRECTED(StatsScreen_LoadTextboxSpaceGFX);
    REDIRECTED(BattleStatsScreenInit);
    REDIRECTED(StatsScreen_LoadPageIndicators);
    CONVERTED(LoadGreenPage);
    REDIRECTED(StatsScreen_JoypadAction);
    REDIRECTED(EggStatsInit);
    REDIRECTED(CheckFaintedFrzSlp);
    REDIRECTED(StatsScreenMobile);
    REDIRECTED(StatsScreen_PlaceVerticalDivider);
    // REDIRECTED(EggCloseString);
    CONVERTED(v_MobileStatsScreenInit);
    REDIRECTED(StatsScreen_CopyToTempMon);
    // REDIRECTED(EggALotMoreTimeString);
    REDIRECTED(CopyNickname);
    REDIRECTED(StatsScreen_Exit);
    CONVERTED(LoadBluePage);
    REDIRECTED(StatsScreen_PlaceFrontpic);
    REDIRECTED(MonStatsJoypad);
    REDIRECTED(StatsScreen_GetJoypad);
    // REDIRECTED(EggString);
    // REDIRECTED(EggSoonString);
    CONVERTED(LoadPinkPage);
    REDIRECTED(StatsScreenInit_gotaddress);
    REDIRECTED(StatsScreenWaitCry);
    // REDIRECTED(EggMoreTimeString);
    // REDIRECTED(FiveQMarkString);
    REDIRECTED(StatsScreen_GetAnimationParam);
    // REDIRECTED(StatsScreenPointerTable);
    REDIRECTED(StatsScreen_PlaceShinyIcon);
    // REDIRECTED(IDNoString);
    CONVERTED(StatsScreenInit);
    REDIRECTED(StatsScreen_WaitAnim);

    // engine/pokemon/tempmon.c
    REDIRECTED(GetMonSpecies);
    REDIRECTED(CalcTempmonStats);
    REDIRECTED(v_TempMonStatsCalculation);
    REDIRECTED(CalcBufferMonStats);
    REDIRECTED(CopyMonToTempMon);

    // engine/gfx/load_pics.c
    REDIRECTED(GetAnimatedFrontpic);
    REDIRECTED(LoadFrontpicTiles);
    REDIRECTED(GetAnimatedEnemyFrontpic);
    REDIRECTED(PadFrontpic);
    REDIRECTED(GSIntro_GetMonFrontpic);
    REDIRECTED(DecompressGet2bpp);
    REDIRECTED(LoadOrientedFrontpic);
    REDIRECTED(GetUnownLetter);
    REDIRECTED(FixPicBank);
    REDIRECTED(GetMonFrontpic);
    REDIRECTED(GetMonBackpic);
    REDIRECTED(GetTrainerPic);
    REDIRECTED(v_GetFrontpic);
    REDIRECTED(GetFrontpicPointer);
    REDIRECTED(FixBackpicAlignment);

    // engine/pokemon/bills_pc.c
    // REDIRECTED(PCMonInfo);
    // REDIRECTED(v_StatsScreenDPad);
    // REDIRECTED(BillsPC_LoadMonStats);
    // REDIRECTED(BillsPC_CopyMon);
    // REDIRECTED(BillsPC_PlaceEmptyBoxString_SFX);
    // REDIRECTED(MoveMonWithoutMail_DPad);
    // REDIRECTED(CopyOTNameToTemp);
    // REDIRECTED(BillsPC_ClearTilemap);
    // REDIRECTED(DepositPokemon);
    // REDIRECTED(ReleasePKMN_ByePKMN);
    // REDIRECTED(v_ChangeBox_MenuHeader);
    // REDIRECTED(BillsPCDepositFuncCancel);
    // REDIRECTED(PCString_Non);
    // REDIRECTED(MovePKMNWitoutMail_InsertMon);
    // REDIRECTED(PCString_Got);
    // REDIRECTED(BillsPC_PressUp);
    // REDIRECTED(PCString_Bye);
    // REDIRECTED(BillsPC_JoypadDidNothing);
    // REDIRECTED(v_ChangeBox);
    // REDIRECTED(PCString_ChooseaPKMN);
    // REDIRECTED(BillsPC_ApplyPalettes);
    // REDIRECTED(BillsPC_UpdateInsertCursor);
    // REDIRECTED(CopyBoxmonSpecies);
    // REDIRECTED(PCSelectLZ);
    // REDIRECTED(BillsPC_UpDownDidSomething);
    // REDIRECTED(BillsPC_FillBox);
    // REDIRECTED(BillsPC_PlaceChangeBoxString);
    // REDIRECTED(BillsPC_PlaceChooseABoxString);
    // REDIRECTED(PCString_ItsYourLastPKMN);
    // REDIRECTED(BillsPCDepositFuncDeposit);
    // REDIRECTED(v_WithdrawPKMN);
    // REDIRECTED(BillsPC_Withdraw);
    // REDIRECTED(BillsPC_PrintBoxCountAndCapacity);
    // REDIRECTED(PCString_RemoveMail);
    // REDIRECTED(BillsPCDepositJumptable);
    // REDIRECTED(MoveMonWithoutMail_DPad_2);
    // REDIRECTED(BillsPC_CheckSpaceInDestination);
    // REDIRECTED(BillsPC_IsMonAnEgg);
    // REDIRECTED(BillsPC_CheckMail_PreventBlackout);
    // REDIRECTED(CopyNicknameToTemp);
    // REDIRECTED(BillsPC_ChangeBoxSubmenu);
    // REDIRECTED(CopyMonToTemp);
    // REDIRECTED(GetBoxCount);
    // REDIRECTED(BillsPC_IncrementJumptableIndex);
    // REDIRECTED(BillsPC_EndJumptableLoop);
    // REDIRECTED(PCMailGFX);
    // REDIRECTED(Withdraw_UpDown);
    // REDIRECTED(BillsPC_PrintBoxName);
    // REDIRECTED(PCString_NoMoreUsablePKMN);
    // REDIRECTED(BillsPCDepositMenuHeader);
    // REDIRECTED(PCString_Stored);
    // REDIRECTED(StatsScreenDPad);
    // REDIRECTED(PCString_TheresNoRoom);
    // REDIRECTED(PCString_PartyFull);
    // REDIRECTED(TryWithdrawPokemon);
    // REDIRECTED(PCString_BoxFull);
    // REDIRECTED(PCString_NoReleasingEGGS);
    // REDIRECTED(BillsPCDepositFuncStats);
    // REDIRECTED(PCString_ReleasePKMN);
    // REDIRECTED(BillsPC_InitRAM);
    // REDIRECTED(PCString_ReleasedPKMN);
    // REDIRECTED(BillsPC_GetSelectedPokemonSpecies);
    // REDIRECTED(BillsPC_LeftRightDidSomething);
    // REDIRECTED(BillsPCClearThreeBoxes);
    // REDIRECTED(BillsPC_StatsScreen);
    // REDIRECTED(BillsPC_PressLeft);
    // REDIRECTED(BillsPC_UpdateSelectionCursor);
    // REDIRECTED(PCString_WhatsUp);
    // REDIRECTED(v_MovePKMNWithoutMail);
    // REDIRECTED(BillsPC_InitGFX);
    // REDIRECTED(BillsPC_PlaceWhatsUpString);
    // REDIRECTED(BillsPCDepositFuncRelease);
    // REDIRECTED(GetBoxPointer);
    // REDIRECTED(CopySpeciesToTemp);
    // REDIRECTED(BillsPC_PressRight);
    // REDIRECTED(BillsPC_RefreshTextboxes);
    // REDIRECTED(GetBoxName);
    // REDIRECTED(BillsPC_BoxName);
    // REDIRECTED(BillsPC_Jumptable);
    // REDIRECTED(v_DepositPKMN);
    // REDIRECTED(BillsPC_PlaceString);
    // REDIRECTED(PCString_MoveToWhere);
    // REDIRECTED(BillsPC_MoveMonWOMail_BoxNameAndArrows);
    // REDIRECTED(BillsPC_PressDown);

    // engine/pokemon/bills_pc_top.c
    // REDIRECTED(CheckCurPartyMonFainted);
    // REDIRECTED(BillsPC_Deposit_CheckPartySize);
    // REDIRECTED(CopyBoxmonToTempMon);
    // REDIRECTED(BillsPC_DepositMenu);
    // REDIRECTED(BillsPC_ChangeBoxMenu);
    // REDIRECTED(ClearPCItemScreen);
    // REDIRECTED(LoadBoxMonListing);
    // REDIRECTED(v_BillsPC);
    // REDIRECTED(PCCantTakeText);
    // REDIRECTED(BillsPC_WithdrawMenu);
    // REDIRECTED(BillsPC_MovePKMNMenu);
    // REDIRECTED(BillsPC_Withdraw_CheckPartySize);
    // REDIRECTED(BillsPC_SeeYa);

    // engine/pokemon/mon_stats.c
    REDIRECTED(PrintTempMonStats);
    REDIRECTED(BrokenPlacePPUnits);
    REDIRECTED(PlaceStatusString);
    REDIRECTED(PlaceNonFaintStatus);
    // REDIRECTED(PsnString);
    REDIRECTED(Unused_PlaceEnemyHPLevel);
    // REDIRECTED(SlpString);
    // REDIRECTED(DrawEnemyHP);
    // REDIRECTED(FrzString);
    // REDIRECTED(DrawPlayerHP);
    REDIRECTED(CopyStatusString);
    // REDIRECTED(BrnString);
    REDIRECTED(ListMovePP);
    // REDIRECTED(ParString);
    REDIRECTED(ListMoves);
    // REDIRECTED(FntString);
    // REDIRECTED(DrawHP);
    // REDIRECTED(GetGender);

    // engine/gfx/pic_animation.c
    // REDIRECTED(PokeAnim_SetupCommands);
    // REDIRECTED(PokeAnim_DeinitFrames);
    // REDIRECTED(PokeAnim_InitAnim);
    // REDIRECTED(AnimateMon_Evolve);
    // REDIRECTED(PokeAnim_GetPointer);
    // REDIRECTED(Unused_HOF_AnimateAlignedFrontpic);
    // REDIRECTED(AnimateMon_Trade);
    // REDIRECTED(PokeAnim_Cry);
    // REDIRECTED(AnimateMon_CheckIfPokemon);
    // REDIRECTED(PokeAnim_SetVBank0);
    // REDIRECTED(PokeAnim_ConvertAndApplyBitmask);
    // REDIRECTED(HOF_AnimateFrontpic);
    // REDIRECTED(PokeAnim_InitPicAttributes);
    // REDIRECTED(PokeAnim_CryNoWait);
    // REDIRECTED(PokeAnim_StopWaitAnim);
    // REDIRECTED(PokeAnim_Setup);
    // REDIRECTED(PokeAnim_StartWaitAnim);
    // REDIRECTED(PokeAnim_DoAnimScript);
    // REDIRECTED(PokeAnim_GetFrontpicDims);
    // REDIRECTED(PokeAnim_GetDuration);
    // REDIRECTED(GetMonFramesPointer);
    // REDIRECTED(PokeAnim_Play2);
    // REDIRECTED(AnimateMon_Hatch);
    // REDIRECTED(GetMonBitmaskPointer);
    // REDIRECTED(PokeAnim_End);
    // REDIRECTED(PokeAnim_BasePic);
    // REDIRECTED(PokeAnim_SetVBank1);
    // REDIRECTED(PokeAnim_Play);
    // REDIRECTED(PokeAnim_CopyBitmaskToBuffer);
    // REDIRECTED(PokeAnim_PlaceGraphic);
    // REDIRECTED(PokeAnim_SetWait);
    // REDIRECTED(LoadMonAnimation);
    // REDIRECTED(PokeAnim_Wait);
    // REDIRECTED(AnimateMon_Menu);
    // REDIRECTED(PokeAnim_GetSpeciesOrUnown);
    // REDIRECTED(PokeAnim_GetAttrmapCoord);
    // REDIRECTED(PokeAnims);
    // REDIRECTED(PokeAnim_StereoCry);
    // REDIRECTED(AnimateFrontpic);
    // REDIRECTED(PokeAnim_IsUnown);
    // REDIRECTED(PokeAnim_Idle);
    // REDIRECTED(PokeAnim_Finish);
    // REDIRECTED(SetUpPokeAnim);
    // REDIRECTED(AnimateMon_HOF);
    // REDIRECTED(PokeAnim_IsEgg);
    // REDIRECTED(GetMonAnimPointer);
    // REDIRECTED(Unused_AnimateMon_Slow_Normal);
    // REDIRECTED(PokeAnim_GetFrame);
    // REDIRECTED(PokeAnim_Setup2);
    // REDIRECTED(PokeAnim_GetBitmaskIndex);

    // engine/pokemon/health.c
    REDIRECTED(HealParty);
    REDIRECTED(HealPartyMon);
    REDIRECTED(ComputeHPBarPixels);
    REDIRECTED(AnimateHPBar);

    // engine/gfx/cgb_layouts.c
    // REDIRECTED(v_CGB_Unknown);
    // REDIRECTED(InitPartyMenuBGPal0);
    // REDIRECTED(StatsScreenPals);
    // REDIRECTED(v_CGB_PackPals);
    // REDIRECTED(v_CGB_PokegearPals);
    // REDIRECTED(v_CGB_TradeTube);
    // REDIRECTED(v_CGB_MagnetTrain);
    // REDIRECTED(v_CGB_GamefreakLogo);
    // REDIRECTED(v_CGB_MysteryGift);
    // REDIRECTED(v_CGB_Evolution);
    // REDIRECTED(v_CGB_BattleColors);
    // REDIRECTED(v_CGB_GSIntro);
    // REDIRECTED(v_CGB_PlayerOrMonFrontpicPals);
    // REDIRECTED(v_CGB_BillsPC);
    // REDIRECTED(v_CGB_BattleGrayscale);
    // REDIRECTED(v_CGB_PokedexUnownMode);
    // REDIRECTED(BillsPCOrangePalette);
    // REDIRECTED(InitPartyMenuBGPal7);
    // REDIRECTED(v_CGB_GSTitleScreen);
    // REDIRECTED(v_CGB_UnownPuzzle);
    // REDIRECTED(v_CGB_TrainerOrMonFrontpicPals);
    // REDIRECTED(v_CGB_Unused1E);
    // REDIRECTED(v_CGB_FinishBattleScreenLayout);
    // REDIRECTED(v_CGB_StatsScreenHPPals);
    // REDIRECTED(CGBLayoutJumptable);
    // REDIRECTED(v_CGB_BetaTitleScreen);
    // REDIRECTED(v_CGB_TrainerCard);
    // REDIRECTED(v_CGB_SlotMachine);
    // REDIRECTED(v_CGB_BetaPoker);
    // REDIRECTED(v_CGB_MoveList);
    // REDIRECTED(v_CGB_Pokepic);
    // REDIRECTED(v_CGB_PokedexSearchOption);
    // REDIRECTED(v_CGB_MapPals);
    // REDIRECTED(v_CGB_Pokedex);
    // REDIRECTED(CheckCGB);
    // REDIRECTED(StatsScreenPagePals);
    // REDIRECTED(v_CGB_Diploma);
    // REDIRECTED(v_CGB_Unused0D);
    // REDIRECTED(PokedexQuestionMarkPalette);
    // REDIRECTED(v_CGB_BetaPikachuMinigame);
    // REDIRECTED(PokedexCursorPalette);
    // REDIRECTED(v_CGB_PartyMenu);
    // REDIRECTED(Mobile_InitPartyMenuBGPal7);
    // REDIRECTED(LoadSGBLayoutCGB);
    // REDIRECTED(GS_CGB_MysteryGift);

    // engine/items/item_effects.c
    // REDIRECTED(BallSoCloseText);
    // REDIRECTED(PPRestoredText);
    // REDIRECTED(SafariBallMultiplier);
    // REDIRECTED(RestorePPEffect);
    // REDIRECTED(LoadHPIntoBuffer3);
    // REDIRECTED(BallBlockedText);
    // REDIRECTED(ReviveHalfHP);
    // REDIRECTED(SuperRodEffect);
    // REDIRECTED(BallMissedText);
    // REDIRECTED(RevivalHerbEffect);
    // REDIRECTED(ComputeMaxPP);
    // REDIRECTED(Text_GotchaMonWasCaught);
    // REDIRECTED(BicycleEffect);
    // REDIRECTED(CardKeyEffect);
    // REDIRECTED(ItemWontHaveEffectText);
    // REDIRECTED(UseRod);
    // REDIRECTED(FullyHealStatus);
    // REDIRECTED(UseRepel);
    // REDIRECTED(FullRestoreEffect);
    // REDIRECTED(PPRestoreItem_NoEffect);
    // REDIRECTED(PPIsMaxedOutText);
    // REDIRECTED(LoadMaxHPIntoBuffer1);
    // REDIRECTED(StatusHealingEffect);
    // REDIRECTED(FinishPPRestore);
    // REDIRECTED(RaiseThePPOfWhichMoveText);
    // REDIRECTED(LoadHPFromBuffer2);
    // REDIRECTED(StatusHealer_NoEffect);
    // REDIRECTED(PPsIncreasedText);
    // REDIRECTED(SacredAshEffect);
    // REDIRECTED(RemoveHP);
    // REDIRECTED(Elixer_RestorePPofAllMoves);
    // REDIRECTED(GoodRodEffect);
    // REDIRECTED(UseDisposableItem);
    // REDIRECTED(UseItemText);
    // REDIRECTED(PokeBallEffect);
    // REDIRECTED(UpdateStatsAfterItem);
    // REDIRECTED(BallAppearedCaughtText);
    // // REDIRECTED(ItemLooksBitterText);
    // REDIRECTED(LureBallMultiplier);
    // REDIRECTED(Ball_BoxIsFullMessage);
    // REDIRECTED(CantUseOnEggMessage);
    // REDIRECTED(ItemUsedText);
    // REDIRECTED(PPRestoreItem_Cancel);
    // REDIRECTED(LooksBitterMessage);
    // REDIRECTED(ParkBallMultiplier);
    // REDIRECTED(BasementKeyEffect);
    // REDIRECTED(GetHealingItemAmount);
    // REDIRECTED(ItemEffects);
    // REDIRECTED(GreatBallMultiplier);
    // REDIRECTED(TownMapEffect);
    // REDIRECTED(ItemActionTextWaitButton);
    // REDIRECTED(ReviveEffect);
    // REDIRECTED(NewDexDataText);
    // REDIRECTED(PokeFluteEffect);
    // REDIRECTED(WaitButtonText);
    // REDIRECTED(ItemRestoreHP);
    // REDIRECTED(BallMultiplierFunctionTable);
    // REDIRECTED(StatusHealer_ExitMenu);
    // REDIRECTED(GetMthMoveOfNthPartymon);
    // REDIRECTED(BlueCardEffect);
    // REDIRECTED(RevivePokemon);
    // REDIRECTED(PokeDollEffect);
    // REDIRECTED(FastBallMultiplier);
    // REDIRECTED(LoadHPFromBuffer1);
    // REDIRECTED(RestorePP);
    // REDIRECTED(BallAlmostHadItText);
    // REDIRECTED(HealPowderEffect);
    // REDIRECTED(ItemStatRoseText);
    // REDIRECTED(NoEffect);
    // REDIRECTED(StatusHealer_ClearPalettes);
    // REDIRECTED(BallBrokeFreeText);
    // REDIRECTED(ReturnToBattle_UseBall);
    // REDIRECTED(BattlemonRestoreHealth);
    // REDIRECTED(MoonBallMultiplier);
    // REDIRECTED(ApplyPPUp);
    // REDIRECTED(AskGiveNicknameText);
    // REDIRECTED(ItemCantGetOnText);
    // REDIRECTED(UseStatusHealer);
    // REDIRECTED(GuardSpecEffect);
    // REDIRECTED(NoEffectMessage);
    // REDIRECTED(BitterBerryEffect);
    // REDIRECTED(ItemGotOnText);
    // REDIRECTED(Not_PP_Up);
    // REDIRECTED(EnergypowderEffect);
    // REDIRECTED(GetPokedexEntryBank);
    // REDIRECTED(RestoreHealth);
    // REDIRECTED(XItemEffect);
    // REDIRECTED(BallDontBeAThiefText);
    // REDIRECTED(RepelUsedEarlierIsStillInEffectText);
    // REDIRECTED(StatStrings);
    // REDIRECTED(NormalBoxEffect);
    // REDIRECTED(Softboiled_MilkDrinkFunction);
    // REDIRECTED(BallSentToPCText);
    // REDIRECTED(Play_SFX_FULL_HEAL);
    // REDIRECTED(CoinCaseEffect);
    // REDIRECTED(IsMonFainted);
    // REDIRECTED(IsMonAtFullHealth);
    // REDIRECTED(RestoreAllPP);
    // REDIRECTED(IsntTheTimeMessage);
    // REDIRECTED(HealStatus);
    // REDIRECTED(LoadCurHPIntoBuffer3);
    // REDIRECTED(GorgeousBoxEffect);
    // REDIRECTED(GetMaxPPOfMove);
    // REDIRECTED(EvoStoneEffect);
    // REDIRECTED(OldRodEffect);
    // REDIRECTED(IsItemUsedOnBattleMon);
    // REDIRECTED(MaxRepelEffect);
    // REDIRECTED(LoadCurHPIntoBuffer2);
    // REDIRECTED(IsItemUsedOnConfusedMon);
    // REDIRECTED(GetOneFifthMaxHP);
    // REDIRECTED(UseBallInTrainerBattle);
    // REDIRECTED(SuperRepelEffect);
    // REDIRECTED(BallDodgedText);
    // REDIRECTED(RestoreThePPOfWhichMoveText);
    // REDIRECTED(ItemfinderEffect);
    // REDIRECTED(RareCandy_StatBooster_ExitMenu);
    // REDIRECTED(v_DoItemEffect);
    // REDIRECTED(DireHitEffect);
    // REDIRECTED(RareCandy_StatBooster_GetParameters);
    // REDIRECTED(SquirtbottleEffect);
    // REDIRECTED(GetStatExpRelativePointer);
    // REDIRECTED(ItemOakWarningText);
    // REDIRECTED(ItemGotOffText);
    // REDIRECTED(StatusHealer_Jumptable);
    // REDIRECTED(ReviveFullHP);
    // REDIRECTED(CantGetOnYourBikeMessage);
    // REDIRECTED(EnergyRootEffect);
    // REDIRECTED(NoCyclingText);
    // REDIRECTED(RareCandyEffect);
    // REDIRECTED(UseItem_SelectMon);
    // REDIRECTED(OpenBox);
    // REDIRECTED(BallBoxFullText);
    // REDIRECTED(GetItemHealingAction);
    // REDIRECTED(ChooseMonToUseItemOn);
    // REDIRECTED(VitaminEffect);
    // REDIRECTED(LoveBallMultiplier);
    // REDIRECTED(EscapeRopeEffect);
    // REDIRECTED(RestoreHPEffect);
    // REDIRECTED(ItemCantUseOnEggText);
    // REDIRECTED(UltraBallMultiplier);
    // REDIRECTED(WontHaveAnyEffectMessage);
    // REDIRECTED(RepelEffect);
    // REDIRECTED(BattleRestorePP);
    // REDIRECTED(HeavyBallMultiplier);
    // REDIRECTED(EnergypowderEnergyRootCommon);
    // REDIRECTED(WontHaveAnyEffect_NotUsedMessage);
    // REDIRECTED(LoadHPFromBuffer3);
    // REDIRECTED(ItemActionText);
    // REDIRECTED(XAccuracyEffect);
    // REDIRECTED(ContinueRevive);
    // REDIRECTED(LevelBallMultiplier);
    // REDIRECTED(CyclingIsntAllowedMessage);
    // REDIRECTED(BelongsToSomeoneElseMessage);
    // REDIRECTED(StatExpItemPointerOffsets);
    // REDIRECTED(ItemBelongsToSomeoneElseText);
    // REDIRECTED(GetMthMoveOfCurrentMon);
    // REDIRECTED(CantUseItemMessage);
    // REDIRECTED(HealHP_SFX_GFX);

    // engine/pokemon/experience.c
    REDIRECTED(CalcExpAtLevel);
    REDIRECTED(CalcLevel);

    // engine/pokemon/types.c
    REDIRECTED(PrintMoveType);
    REDIRECTED(PrintType);
    REDIRECTED(PrintMonTypes);
    REDIRECTED(GetTypeName);

    // engine/events/specials.c
    // REDIRECTED(CheckLuckyNumberShowFlag);
    // REDIRECTED(MapRadio);
    // REDIRECTED(CheckCoinsAndCoinCase);
    // REDIRECTED(ResetLuckyNumberShowFlag);
    // REDIRECTED(GetMysteryGiftItem);
    // REDIRECTED(PrintDiploma);
    // REDIRECTED(CheckMysteryGift);
    // REDIRECTED(UnusedCheckUnusedTwoDayTimer);
    // REDIRECTED(UnusedSetSeenMon);
    // REDIRECTED(GameCornerPrizeMonCheckDex);
    // REDIRECTED(Special);
    // REDIRECTED(PlayersHousePC);
    // REDIRECTED(UnownPrinter);
    // REDIRECTED(CardFlip);
    // REDIRECTED(ClearBGPalettesBufferScreen);
    // REDIRECTED(StoreSwarmMapIndices);
    // REDIRECTED(SlotMachine);
    // REDIRECTED(ScriptReturnCarry);
    // REDIRECTED(CheckPokerus);
    // REDIRECTED(NameRival);
    // REDIRECTED(DisplayLinkRecord);
    // REDIRECTED(StartGameCornerGame);
    // REDIRECTED(Diploma);
    // REDIRECTED(ActivateFishingSwarm);
    // REDIRECTED(UnusedMemoryGame);
    // REDIRECTED(TrainerHouse);
    // REDIRECTED(FindPartyMonAtLeastThatHappy);
    // REDIRECTED(OverworldTownMap);
    // REDIRECTED(GameboyCheck);
    // REDIRECTED(PlayCurMonCry);
    // REDIRECTED(SnorlaxAwake);
    // REDIRECTED(SetPlayerPalette);
    // REDIRECTED(FindPartyMonAboveLevel);
    // REDIRECTED(FadeOutMusic);
    // REDIRECTED(UnusedDummySpecial);
    // REDIRECTED(FindPartyMonThatSpecies);
    // REDIRECTED(FoundNone);
    // REDIRECTED(FindPartyMonThatSpeciesYourTrainerID);
    // REDIRECTED(NameRater);
    // REDIRECTED(FoundOne);
    // REDIRECTED(UnownPuzzle);
    // REDIRECTED(BugContestJudging);

    // engine/overworld/player_movement.c
    // REDIRECTED(StopPlayerForEvent);
    CONVERTED(DoPlayerMovement);
    // REDIRECTED(CheckStandingOnIce);

    // engine/overworld/npc_movement.c
    // REDIRECTED(GetSideWallDirectionMask);
    // REDIRECTED(CanObjectMoveInDirection);
    // REDIRECTED(HasObjectReachedMovementLimit);
    // REDIRECTED(CanObjectLeaveTile);
    // REDIRECTED(IsNPCAtCoord);
    // REDIRECTED(WillObjectRemainOnWater);
    // REDIRECTED(WillObjectBumpIntoSomeoneElse);
    // REDIRECTED(IsNPCAtPlayerCoord);
    // REDIRECTED(WillObjectBumpIntoWater);
    // REDIRECTED(IsObjectFacingSomeoneElse);
    // REDIRECTED(IsObjectMovingOffEdgeOfScreen);
    // REDIRECTED(WillObjectBumpIntoTile);
    // REDIRECTED(CheckFacingObject);
    // REDIRECTED(WillObjectBumpIntoLand);
    // REDIRECTED(WillObjectIntersectBigObject);

    // engine/overworld/tile_events.c
    // REDIRECTED(CheckDirectionalWarp);
    // REDIRECTED(CheckGrassCollision);
    // REDIRECTED(CheckCutCollision);
    REDIRECTED(GetWarpSFX);
    // REDIRECTED(CheckWarpCollision);
    // REDIRECTED(CheckWarpFacingDown);

    // engine/overworld/movement.c
    // REDIRECTED(Movement_big_step_up);
    // REDIRECTED(TurnStep);
    // REDIRECTED(Movement_turn_step_left);
    // REDIRECTED(Movement_hide_object);
    // REDIRECTED(Movement_turn_in_right);
    // REDIRECTED(Movement_fish_got_bite);
    // REDIRECTED(Movement_turn_head_down);
    // REDIRECTED(Movement_slide_step_right);
    // REDIRECTED(Movement_step_loop);
    // REDIRECTED(Movement_slow_jump_step_left);
    // REDIRECTED(Movement_step_right);
    // REDIRECTED(Movement_turn_away_up);
    // REDIRECTED(Movement_remove_object);
    // REDIRECTED(Movement_turn_head_up);
    // REDIRECTED(Movement_step_down);
    // REDIRECTED(Movement_turn_step_right);
    // REDIRECTED(Movement_remove_fixed_facing);
    // REDIRECTED(NormalStep);
    // REDIRECTED(Movement_slow_jump_step_down);
    // REDIRECTED(Movement_turn_in_up);
    // REDIRECTED(Movement_step_shake);
    // REDIRECTED(Movement_jump_step_down);
    // REDIRECTED(Movement_slow_step_right);
    // REDIRECTED(Movement_rock_smash);
    // REDIRECTED(Movement_48);
    // REDIRECTED(Movement_turn_waterfall_down);
    // REDIRECTED(Movement_turn_away_left);
    // REDIRECTED(MovementPointers);
    // REDIRECTED(Movement_step_dig);
    // REDIRECTED(Movement_turn_step_up);
    // REDIRECTED(Movement_slow_step_up);
    // REDIRECTED(Movement_turn_waterfall_up);
    // REDIRECTED(Movement_turn_head_left);
    // REDIRECTED(Movement_slide_step_up);
    // REDIRECTED(Movement_big_step_down);
    // REDIRECTED(Movement_tree_shake);
    // REDIRECTED(Movement_slow_slide_step_left);
    // REDIRECTED(Movement_skyfall);
    // REDIRECTED(Movement_slow_jump_step_up);
    // REDIRECTED(Movement_fast_jump_step_up);
    // REDIRECTED(Movement_slow_step_down);
    // REDIRECTED(Movement_turn_away_down);
    // REDIRECTED(Movement_teleport_to);
    // REDIRECTED(Movement_step_sleep_1);
    // REDIRECTED(Movement_show_emote);
    // REDIRECTED(Movement_jump_step_left);
    // REDIRECTED(Movement_step_sleep_7);
    // REDIRECTED(Movement_fast_jump_step_down);
    // REDIRECTED(Movement_slow_slide_step_up);
    // REDIRECTED(Movement_step_sleep_3);
    // REDIRECTED(SlideStep);
    // REDIRECTED(Movement_turn_away_right);
    // REDIRECTED(Movement_turn_in_left);
    // REDIRECTED(Movement_step_sleep_2);
    // REDIRECTED(Movement_fast_jump_step_right);
    // REDIRECTED(Movement_fast_slide_step_right);
    // REDIRECTED(Movement_step_bump);
    // REDIRECTED(Movement_slide_step_left);
    // REDIRECTED(Movement_4b);
    // REDIRECTED(Movement_slow_step_left);
    // REDIRECTED(Movement_fast_jump_step_left);
    // REDIRECTED(Movement_step_sleep);
    // REDIRECTED(Movement_turn_head_right);
    // REDIRECTED(Movement_remove_sliding);
    // REDIRECTED(Movement_turn_waterfall_left);
    // REDIRECTED(Movement_fast_slide_step_down);
    // REDIRECTED(Movement_fix_facing);
    // REDIRECTED(TurnHead);
    // REDIRECTED(Movement_turn_waterfall_right);
    // REDIRECTED(Movement_jump_step_right);
    // REDIRECTED(Movement_hide_emote);
    // REDIRECTED(Movement_fish_cast_rod);
    // REDIRECTED(Movement_turn_in_down);
    // REDIRECTED(Movement_slide_step_down);
    // REDIRECTED(Movement_step_sleep_8);
    // REDIRECTED(Movement_slow_slide_step_down);
    // REDIRECTED(TurningStep);
    // REDIRECTED(Movement_step_up);
    // REDIRECTED(Movement_fast_slide_step_left);
    // REDIRECTED(Movement_slow_slide_step_right);
    // REDIRECTED(Movement_step_end);
    // REDIRECTED(Movement_fast_slide_step_up);
    // REDIRECTED(Movement_jump_step_up);
    // REDIRECTED(Movement_big_step_left);
    // REDIRECTED(Movement_teleport_from);
    // REDIRECTED(JumpStep);
    // REDIRECTED(Movement_big_step_right);
    // REDIRECTED(Movement_step_sleep_4);
    // REDIRECTED(Movement_skyfall_top);
    // REDIRECTED(Movement_step_sleep_common);
    // REDIRECTED(Movement_step_sleep_5);
    // REDIRECTED(Movement_slow_jump_step_right);
    // REDIRECTED(Movement_turn_step_down);
    // REDIRECTED(Movement_step_sleep_6);
    // REDIRECTED(Movement_return_dig);
    // REDIRECTED(Movement_show_object);
    // REDIRECTED(Movement_set_sliding);
    // REDIRECTED(Movement_step_left);

    // engine/overworld/player_object.c
    REDIRECTED(BlankScreen);
    REDIRECTED(QueueFollowerFirstStep);
    // REDIRECTED(InitializeVisibleSprites);
    REDIRECTED(CopyMapObjectToObjectStruct);
    // REDIRECTED(SpawnPlayer);
    REDIRECTED(CopyDECoordsToMapObject);
    REDIRECTED(SurfStartStep);
    REDIRECTED(WriteObjectXY);
    // REDIRECTED(RefreshPlayerCoords);
    REDIRECTED(TrainerWalkToPlayer);
    REDIRECTED(FollowNotExact);
    REDIRECTED(CopyTempObjectToObjectStruct);
    REDIRECTED(CopyObjectStruct);
    REDIRECTED(GetRelativeFacing);
    REDIRECTED(PlayerSpawn_ConvertCoords);
    // REDIRECTED(PlayerObjectTemplate);
    REDIRECTED(CheckObjectEnteringVisibleRange);

    // engine/tilesets/mapgroup_roofs.c
    CONVERTED(LoadMapGroupRoof);

    // engine/events/catch_tutorial.c
    CONVERTED(CatchTutorial);

    // engine/events/catch_tutorial_input.c
    CONVERTED(v_DudeAutoInput_DownA);
    CONVERTED(v_DudeAutoInput_RightA);
    CONVERTED(v_DudeAutoInput_A);
    // REDIRECTED(DudeAutoInputs);
    // CONVERTED(v_DudeAutoInput);
    // REDIRECTED(DudeAutoInput_DownA);
    // REDIRECTED(DudeAutoInput_RightA);
    // REDIRECTED(DudeAutoInput_A);

    // engine/movie/splash.c
    // REDIRECTED(GameFreakLogo_Done);
    // REDIRECTED(GameFreakLogo_Ditto);
    // CONVERTED(SplashScreen);
    // REDIRECTED(GameFreakPresentsInit);
    // REDIRECTED(GameFreakLogoSpriteAnim);
    // REDIRECTED(GameFreakLogo_Init);
    // REDIRECTED(GameFreakPresents_PlacePresents);
    // REDIRECTED(GameFreakPresentsEnd);
    // REDIRECTED(GameFreakPresents_NextScene);
    // REDIRECTED(GameFreakPresents_PlaceGameFreak);
    // REDIRECTED(GameFreakPresents_WaitForTimer);
    // REDIRECTED(GameFreakLogo_Transform);
    // REDIRECTED(GameFreakPresentsScene);
    // REDIRECTED(GameFreakLogo_Bounce);
    // REDIRECTED(GameFreakLogoGFX);
    // REDIRECTED(GameFreakDittoPaletteFade);
    // REDIRECTED(GameFreakPresents_WaitSpriteAnim);

    // engine/movie/gbc_only.c
    // REDIRECTED(GBCOnlyGFX);
    // REDIRECTED(DrawGBCOnlyGraphic);
    // REDIRECTED(DrawGBCOnlyBorder);
    // REDIRECTED(GBCOnlyString);
    CONVERTED(GBCOnlyScreen);
    // REDIRECTED(DrawGBCOnlyScreen);

    // engine/events/checktime.c
    CONVERTED(CheckTime);

    // engine/overworld/variables.c
    // REDIRECTED(v_GetVarAction);

    // engine/battle/read_trainer_attributes.c
    REDIRECTED(GetTrainerClassName);
    REDIRECTED(GetOTName);
    REDIRECTED(GetTrainerAttributes);

    // engine/overworld/time.c
    // REDIRECTED(RestartDailyResetTimer);
    // REDIRECTED(CheckBugContestTimer);
    // REDIRECTED(DoMysteryGiftIfDayHasPassed);
    // REDIRECTED(CopyDayHourToHL);
    // REDIRECTED(CheckDayDependentEventHL);
    // REDIRECTED(CopyDayToHL);
    // REDIRECTED(UpdateTimeRemaining);
    // REDIRECTED(CheckDailyResetTimer);
    // REDIRECTED(CalcSecsMinsHoursDaysSince);
    // REDIRECTED(v_CalcHoursDaysSince);
    // REDIRECTED(InitCallReceiveDelay);
    // REDIRECTED(InitOneDayCountdown);
    // REDIRECTED(RestartReceiveCallDelay);
    // REDIRECTED(GetDaysSince);
    // REDIRECTED(v_CalcDaysSince);
    // REDIRECTED(SetUnusedTwoDayTimer);
    // REDIRECTED(UnusedCheckSwarmFlag);
    // REDIRECTED(CalcDaysSince);
    // REDIRECTED(CheckReceiveCallDelay);
    // REDIRECTED(GetMinutesSinceIfLessThan60);
    // REDIRECTED(CopyDayHourMinToHL);
    // REDIRECTED(v_InitializeStartDay);
    // REDIRECTED(CalcHoursDaysSince);
    // REDIRECTED(GetHoursSinceIfLessThan24);
    CONVERTED(ClearDailyTimers);
    // REDIRECTED(GetSecondsSinceIfLessThan60);
    // REDIRECTED(SampleKenjiBreakCountdown);
    // REDIRECTED(UnusedSetSwarmFlag);
    // REDIRECTED(GetTimeElapsed_ExceedsUnitLimit);
    // REDIRECTED(v_CalcMinsHoursDaysSince);
    // REDIRECTED(InitializeStartDay);
    // REDIRECTED(CheckPokerusTick);
    // REDIRECTED(RestartLuckyNumberCountdown);
    // REDIRECTED(v_CheckLuckyNumberShowFlag);
    // REDIRECTED(CalcMinsHoursDaysSince);
    // REDIRECTED(NextCallReceiveDelay);
    // REDIRECTED(CopyDayHourMinSecToHL);
    // REDIRECTED(StartBugContestTimer);
    // REDIRECTED(CheckReceiveCallTimer);
    // REDIRECTED(InitNDaysCountdown);
    // REDIRECTED(CheckUnusedTwoDayTimer);

    // engine/events/money.c
    // REDIRECTED(SubtractMoney);
    // REDIRECTED(GiveCoins);
    // REDIRECTED(MaxMoney);
    // REDIRECTED(CompareFunds);
    // REDIRECTED(GiveMoney);
    // REDIRECTED(TakeCoins);
    // REDIRECTED(AddFunds);
    // REDIRECTED(TakeMoney);
    // REDIRECTED(AddMoney);
    // REDIRECTED(CompareMoney);
    // REDIRECTED(SubtractFunds);
    // REDIRECTED(CheckCoins);

    // engine/movie/title.c
    // REDIRECTED(TitleSuicuneGFX);
    // REDIRECTED(TitleCrystalGFX);
    REDIRECTED(DrawTitleGraphic);
    REDIRECTED(SuicuneFrameIterator);
    // REDIRECTED(TitleLogoGFX);
    CONVERTED(v_TitleScreen);
    // REDIRECTED(TitleScreenPalettes);
    REDIRECTED(InitializeBackground);
    REDIRECTED(AnimateTitleCrystal);
    REDIRECTED(LoadSuicuneFrame);

    // engine/battle/menu.c
    REDIRECTED(SafariBattleMenu);
    // REDIRECTED(BattleMenuHeader);
    REDIRECTED(LoadBattleMenu);
    // REDIRECTED(SafariBattleMenuHeader);
    REDIRECTED(ContestBattleMenu);
    REDIRECTED(CommonBattleMenu);
    // REDIRECTED(ContestBattleMenuHeader);

    // engine/rtc/timeset.c
    // REDIRECTED(SetMinutes);
    // REDIRECTED(OakTimeWokeUpText);
    // REDIRECTED(DisplayHourOClock);
    // REDIRECTED(MrChrono);
    // REDIRECTED(TimeSetBackgroundGFX);
    CONVERTED(InitialClearDSTFlag);
    CONVERTED(InitClock);
    CONVERTED(SetDayOfWeek);
    // REDIRECTED(SetHour);
    // REDIRECTED(OakText_ResponseToSetTime);
    // REDIRECTED(String_min);
    // REDIRECTED(DisplayMinutesWithMinString);
    // REDIRECTED(PrintHour);
    // REDIRECTED(AdjustHourForAMorPM);
    // REDIRECTED(OakTimeWhoaMinutesText);
    // REDIRECTED(OakTimeWhatTimeIsItText);
    // REDIRECTED(OakTimeWhatHoursText);
    // REDIRECTED(TimeSetUpArrowGFX);
    // REDIRECTED(String_oclock);
    CONVERTED(InitialSetDSTFlag);
    // REDIRECTED(TimeSetDownArrowGFX);
    // REDIRECTED(DisplayHoursMinutesWithMinString);
    // REDIRECTED(PrintTwoDigitNumberLeftAlign);
    // REDIRECTED(OakTimeHowManyMinutesText);
    // REDIRECTED(GetTimeOfDayString);

    // engine/events/pokepic.c
    CONVERTED(Pokepic);
    CONVERTED(ClosePokepic);
    // REDIRECTED(PokepicMenuHeader);

    // engine/menus/start_menu.c
    // REDIRECTED(StartMenu_Pokedex);
    // REDIRECTED(StartMenu_Pack);
    // REDIRECTED(StartMenu_Status);
    // REDIRECTED(StartMenu_Save);
    // REDIRECTED(StartMenu_Option);
    // REDIRECTED(StartMenu_Exit);
    // REDIRECTED(StartMenu_Pokegear);
    // REDIRECTED(StartMenu_Quit);
    // CONVERTED(StartMenu);
    // REDIRECTED(StartMenu_Pokemon);

    // engine/overworld/warp_connection.c
    // REDIRECTED(HandleNewMap);
    // REDIRECTED(HandleContinueMap);
    // REDIRECTED(LoadMapGraphics);
    // REDIRECTED(CheckMovingOffEdgeOfMap);
    // REDIRECTED(GetMapScreenCoords);
    // REDIRECTED(LoadMapPalettes);
    // REDIRECTED(EnterMapWarp);
    // REDIRECTED(LoadMapTimeOfDay);
    // REDIRECTED(RefreshMapSprites);
    // REDIRECTED(EnterMapConnection);

    // engine/events/happiness_egg.c
    // REDIRECTED(GetFirstPokemonHappiness);
    // REDIRECTED(CheckFirstMonIsEgg);
    // REDIRECTED(DayCareStep);
    // REDIRECTED(ChangeHappiness);
    // REDIRECTED(StepHappiness);

    // engine/battle/used_move_text.c
    CONVERTED(DisplayUsedMoveText);
    // REDIRECTED(MoveNameText);
    // REDIRECTED(EndUsedMove2Text);
    // REDIRECTED(UpdateUsedMoves);
    // REDIRECTED(EndUsedMove3Text);
    // REDIRECTED(EndUsedMove5Text);
    // REDIRECTED(GetMoveGrammar);
    // REDIRECTED(UsedMoveText);
    // REDIRECTED(UsedMove1Text);
    // REDIRECTED(EndUsedMove4Text);
    // REDIRECTED(UsedMove2Text);
    // REDIRECTED(UsedMoveText_CheckObedience);
    // REDIRECTED(EndUsedMove1Text);

    // engine/battle/ai/items.c
    REDIRECTED(EnemyUsedXSpecial);
    REDIRECTED(EnemyPotionFinish);
    REDIRECTED(EnemyUsedFullHeal);
    // REDIRECTED(EnemyUsedOnText);
    REDIRECTED(AI_TryItem);
    REDIRECTED(EnemyUsedXItem);
    REDIRECTED(AI_Switch);
    REDIRECTED(EnemyUsedXAccuracy);
    REDIRECTED(EnemyUsedXAttack);
    // REDIRECTED(EnemyWithdrewText);
    REDIRECTED(SwitchSometimes);
    REDIRECTED(FullRestoreContinue);
    REDIRECTED(AICheckEnemyFractionMaxHP);
    REDIRECTED(EnemyUsedXSpeed);
    REDIRECTED(EnemyUsedDireHit);
    REDIRECTED(AI_Items);
    REDIRECTED(EnemyUsedPotion);
    REDIRECTED(EnemyUsedXDefend);
    REDIRECTED(SwitchOften);
    REDIRECTED(DontSwitch);
    REDIRECTED(EnemyUsedSuperPotion);
    REDIRECTED(AIUpdateHUD);
    REDIRECTED(AI_SwitchOrTryItem);
    REDIRECTED(EnemyUsedHyperPotion);
    REDIRECTED(AI_HealStatus);
    REDIRECTED(AI_TrySwitch);
    REDIRECTED(CheckSubstatusCantRun);
    REDIRECTED(EnemyUsedFullHealRed);
    REDIRECTED(EnemyPotionContinue);
    REDIRECTED(PrintText_UsedItemOn);
    REDIRECTED(EnemyUsedGuardSpec);
    REDIRECTED(PrintText_UsedItemOn_AND_AIUpdateHUD);
    REDIRECTED(EnemyUsedMaxPotion);
    REDIRECTED(SwitchRarely);
    REDIRECTED(AIUsedItemSound);
    REDIRECTED(EnemyUsedFullRestore);

    // engine/rtc/restart_clock.c
    // REDIRECTED(JPMinuteString);
    CONVERTED(RestartClock);
    // REDIRECTED(RestartClock_GetWraparoundTime);
    // REDIRECTED(JPHourString);

    // engine/tilesets/timeofday_pals.c
    // REDIRECTED(DummyPredef35);
    // REDIRECTED(FadeInQuickly);
    // REDIRECTED(UpdateTimeOfDayPal);
    // REDIRECTED(v_TimeOfDayPals);
    // REDIRECTED(FillWhiteBGColor);
    // REDIRECTED(DummyPredef36);
    // REDIRECTED(GetTimePalette);
    // REDIRECTED(ConvertTimePalsDecHL);
    // REDIRECTED(GetTimePalFade);
    // REDIRECTED(FadeInPalettes);
    // REDIRECTED(FadeOutPalettes);
    // REDIRECTED(FadeBlackQuickly);
    // REDIRECTED(ConvertTimePalsIncHL);
    // REDIRECTED(DmgToCgbTimePals);
    // REDIRECTED(v_UpdateTimePals);
    // REDIRECTED(ReplaceTimeOfDayPals);
    // REDIRECTED(BattleTowerFade);

    // engine/battle/trainer_huds.c
    // REDIRECTED(StageBallTilesData);
    // REDIRECTED(DrawPlayerHUDBorder);
    // REDIRECTED(LoadTrainerHudOAM);
    // REDIRECTED(PlaceHUDBorderTiles);
    // REDIRECTED(DrawEnemyHUDBorder);
    // REDIRECTED(EnemySwitch_TrainerHud);
    // REDIRECTED(ShowOTTrainerMonsRemaining);
    // REDIRECTED(BattleStart_TrainerHuds);
    // REDIRECTED(DrawPlayerPartyIconHUDBorder);
    // REDIRECTED(ShowPlayerMonsRemaining);
    // REDIRECTED(LinkBattle_TrainerHuds);
    // REDIRECTED(LoadBallIconGFX);
    // REDIRECTED(v_ShowLinkBattleParticipants);

    // engine/battle/read_trainer_dvs.c
    // REDIRECTED(GetTrainerDVs);

    // engine/pokemon/move_mon.c
    // REDIRECTED(RetrieveMonFromDayCareMan);
    // REDIRECTED(GeneratePartyMonStats);
    // REDIRECTED(ComputeNPCTrademonStats);
    // REDIRECTED(RemoveMonFromPartyOrBox);
    // REDIRECTED(TryAddMonToParty);
    // REDIRECTED(SendGetMonIntoFromBox);
    // REDIRECTED(SendMonIntoBox);
    // REDIRECTED(RetrieveMonFromDayCareLady);
    // REDIRECTED(DepositMonWithDayCareLady);
    // REDIRECTED(RestorePPOfDepositedPokemon);
    // REDIRECTED(WasSentToBillsPCText);
    // REDIRECTED(GivePoke);
    // REDIRECTED(String_Egg);
    // REDIRECTED(CloseSRAM_And_SetCarryFlag);
    // REDIRECTED(GiveEgg);
    // REDIRECTED(CalcMonStatC);
    // REDIRECTED(DepositMonWithDayCareMan);
    // REDIRECTED(AddTempmonToParty);
    // REDIRECTED(InitNickname);
    // REDIRECTED(ShiftBoxMon);
    // REDIRECTED(CalcMonStats);
    // REDIRECTED(GetLastPartyMon);
    // REDIRECTED(DepositBreedmon);
    // REDIRECTED(RetrieveBreedmon);
    // REDIRECTED(FillPP);

    // engine/math/get_square_root.c
    // REDIRECTED(GetSquareRoot);

    // engine/pokemon/evolve.c
    // REDIRECTED(GetPreEvolution);
    // REDIRECTED(CongratulationsYourPokemonText);
    // REDIRECTED(IsMonHoldingEverstone);
    // REDIRECTED(EvolveAfterBattle_MasterLoop);
    // REDIRECTED(FillMoves);
    // REDIRECTED(LearnLevelMoves);
    // REDIRECTED(ShiftMoves);
    // REDIRECTED(StoppedEvolvingText);
    // REDIRECTED(UpdateSpeciesNameIfNotNicknamed);
    // REDIRECTED(EvolvedIntoText);
    // REDIRECTED(EvolvingText);
    // REDIRECTED(EvolvePokemon);
    // REDIRECTED(CancelEvolution);
    // REDIRECTED(EvoFlagAction);
    // REDIRECTED(EvolveAfterBattle);

    // engine/events/magikarp.c
    // REDIRECTED(PrintMagikarpLength);
    // REDIRECTED(CalcMagikarpLength);
    // REDIRECTED(CheckMagikarpLength);
    // REDIRECTED(Magikarp_LoadFeetInchesChars);
    // REDIRECTED(MagikarpHouseSign);

    // engine/events/fruit_trees.c
    // REDIRECTED(PickedFruitTree);
    // REDIRECTED(TryResetFruitTrees);
    // REDIRECTED(ObtainedFruitText);
    // REDIRECTED(FruitBearingTreeText);
    // REDIRECTED(ResetFruitTrees);
    // REDIRECTED(CheckFruitTree);
    // REDIRECTED(FruitTreeScript);
    // REDIRECTED(GetCurTreeFruit);
    // REDIRECTED(HeyItsFruitText);
    // REDIRECTED(FruitPackIsFullText);
    // REDIRECTED(GetFruitTreeFlag);
    // REDIRECTED(GetFruitTreeItem);
    // REDIRECTED(NothingHereText);

    // engine/events/forced_movement.c
    // REDIRECTED(Script_ForcedMovement);

    // engine/battle/ai/redundant.c
    // REDIRECTED(AI_Redundant);

    // engine/battle/move_effects/attract.c
    // REDIRECTED(CheckOppositeGender);
    // REDIRECTED(BattleCommand_Attract);

    // engine/battle/ai/switch.c
    // REDIRECTED(FindEnemyMonsImmuneToLastCounterMove);
    // REDIRECTED(FindAliveEnemyMons);
    // REDIRECTED(CheckPlayerMoveTypeMatchups);
    // REDIRECTED(FindAliveEnemyMonsWithASuperEffectiveMove);
    // REDIRECTED(FindEnemyMonsWithASuperEffectiveMove);
    // REDIRECTED(CheckAbleToSwitch);
    // REDIRECTED(FindEnemyMonsThatResistPlayer);
    // REDIRECTED(FindEnemyMonsWithAtLeastQuarterMaxHP);

    // engine/battle/move_effects/fury_cutter.c
    // REDIRECTED(ResetFuryCutterCount);
    // REDIRECTED(BattleCommand_FuryCutter);

    // engine/battle/misc.c
    REDIRECTED(GetEnemyFrontpicCoords);
    REDIRECTED(GetPlayerBackpicCoords);
    REDIRECTED(v_AppearUserRaiseSub);
    REDIRECTED(FinishAppearDisappearUser);
    REDIRECTED(DoWeatherModifiers);
    REDIRECTED(AppearUser);
    REDIRECTED(v_AppearUserLowerSub);
    REDIRECTED(DoBadgeTypeBoosts);
    REDIRECTED(v_DisappearUser);

    // engine/battle/move_effects/false_swipe.c
    // REDIRECTED(BattleCommand_FalseSwipe);

    // engine/battle/move_effects/splash.c
    REDIRECTED(BattleCommand_Splash);

    // engine/battle/move_effects/hidden_power.c
    REDIRECTED(BattleCommand_HiddenPower);

    // engine/battle/move_effects/rain_dance.c
    REDIRECTED(BattleCommand_StartRain);

    // engine/battle/move_effects/sunny_day.c
    REDIRECTED(BattleCommand_StartSun);

    // engine/battle/move_effects/safeguard.c
    REDIRECTED(BattleCommand_Safeguard);

    // engine/battle/move_effects/focus_energy.c
    REDIRECTED(BattleCommand_FocusEnergy);

    // engine/battle/move_effects/lock_on.c
    REDIRECTED(BattleCommand_LockOn);

    // engine/battle/move_effects/destiny_bond.c
    REDIRECTED(BattleCommand_DestinyBond);

    // engine/battle/move_effects/pursuit.c
    REDIRECTED(BattleCommand_Pursuit);

    // engine/battle/move_effects/spikes.c
    REDIRECTED(BattleCommand_Spikes);

    // engine/battle/move_effects/thunder.c
    REDIRECTED(BattleCommand_ThunderAccuracy);

    // engine/link/link.c
    // REDIRECTED(Colosseum);
    // REDIRECTED(LinkTrade);
    // REDIRECTED(LinkTradeOTPartymonMenuCheckCancel);
    // REDIRECTED(GSLinkCommsBorderGFX);
    // REDIRECTED(LinkCommunications);
    // REDIRECTED(GSPlaceTradeScreenFooter);
    // REDIRECTED(LinkTrade_TradeStatsMenu);
    // REDIRECTED(CableClubCheckWhichChris);
    // REDIRECTED(PlaceTradeScreenTextbox);
    // REDIRECTED(TradeCenter);
    // REDIRECTED(FixDataForLinkTransfer);
    // REDIRECTED(FailedLinkToPast);
    // REDIRECTED(Link_CopyRandomNumbers);
    // REDIRECTED(LinkTradePartymonMenuLoop);
    // REDIRECTED(Link_CopyOTData);
    // REDIRECTED(String_PleaseWait);
    // REDIRECTED(WaitForLinkedFriend);
    // REDIRECTED(ExchangeBytes);
    // REDIRECTED(LinkTimeout);
    // REDIRECTED(CheckBothSelectedSameRoom);
    // REDIRECTED(CheckTimeCapsuleCompatibility);
    // REDIRECTED(TryQuickSave);
    // REDIRECTED(Link_PrepPartyData_Gen1);
    // REDIRECTED(LinkTradePartymonMenuCheckCancel);
    // REDIRECTED(String_TradeCompleted);
    // REDIRECTED(InitTradeMenuDisplay_Delay);
    // REDIRECTED(CheckLinkTimeout_Gen2);
    // REDIRECTED(Link_ConvertPartyStruct1to2);
    // REDIRECTED(LinkTradePartiesMenuMasterLoop);
    // REDIRECTED(LinkEngine_FillBox);
    // REDIRECTED(LinkAskTradeForText);
    // REDIRECTED(WaitForOtherPlayerToExit);
    // REDIRECTED(CloseLink);
    // REDIRECTED(GetIncompatibleMonName);
    // REDIRECTED(String_TradeCancel);
    // REDIRECTED(SetBitsForBattleRequest);
    // REDIRECTED(Link_ResetSerialRegistersAfterLinkClosure);
    // REDIRECTED(ClearLinkData);
    // REDIRECTED(EnterTimeCapsule);
    // REDIRECTED(LoadTradeScreenBorderGFX);
    // REDIRECTED(Link_PrepPartyData_Gen2);
    // REDIRECTED(LinkTextboxAtHL);
    // REDIRECTED(CheckSRAM0Flag);
    // REDIRECTED(InitTradeMenuDisplay);
    // REDIRECTED(Gen2ToGen2LinkComms);
    // REDIRECTED(Link_FindFirstNonControlCharacter_AllowZero);
    // REDIRECTED(Link_EnsureSync);
    // REDIRECTED(LinkTradeOTPartymonMenuLoop);
    // REDIRECTED(SetTradeRoomBGPals);
    // REDIRECTED(Gen2ToGen1LinkComms);
    // REDIRECTED(Link_CopyMailPreamble);
    // REDIRECTED(TimeCapsule);
    // REDIRECTED(LinkTrade_PlayerPartyMenu);
    // REDIRECTED(Link_FindFirstNonControlCharacter_SkipZero);
    // REDIRECTED(TimeCapsule_ReplaceTeruSama);
    // REDIRECTED(String_TooBadTheTradeWasCanceled);
    // REDIRECTED(LinkTrade_OTPartyMenu);
    // REDIRECTED(CheckLinkTimeout_Receptionist);
    // REDIRECTED(ExitLinkCommunications);
    // REDIRECTED(LinkTradePlaceArrow);
    // REDIRECTED(SetBitsForTimeCapsuleRequest);
    // REDIRECTED(Link_CheckCommunicationError);
    // REDIRECTED(SetBitsForLinkTradeRequest);

    // engine/battle/move_effects/pay_day.c
    REDIRECTED(BattleCommand_PayDay);

    // engine/battle/move_effects/mist.c
    REDIRECTED(BattleCommand_Mist);

    // engine/battle/move_effects/triple_kick.c
    REDIRECTED(BattleCommand_KickCounter);
    REDIRECTED(BattleCommand_TripleKick);

    // engine/battle/move_effects/leech_seed.c
    REDIRECTED(BattleCommand_LeechSeed);

    // engine/battle/move_effects/magnitude.c
    REDIRECTED(BattleCommand_GetMagnitude);

    // engine/battle/move_effects/selfdestruct.c
    REDIRECTED(BattleCommand_Selfdestruct);

    // engine/battle/move_effects/snore.c
    REDIRECTED(BattleCommand_Snore);

    // engine/battle/move_effects/rollout.c
    REDIRECTED(BattleCommand_RolloutPower);
    REDIRECTED(BattleCommand_CheckCurl);

    // engine/battle/move_effects/belly_drum.c
    REDIRECTED(BattleCommand_BellyDrum);

    // engine/battle/move_effects/counter.c
    REDIRECTED(BattleCommand_Counter);

    // engine/battle/move_effects/metronome.c
    REDIRECTED(BattleCommand_Metronome);

    // engine/battle/move_effects/return.c
    REDIRECTED(BattleCommand_HappinessPower);

    // engine/battle/move_effects/curse.c
    REDIRECTED(BattleCommand_Curse);

    // engine/battle/move_effects/sandstorm.c
    REDIRECTED(BattleCommand_StartSandstorm);

    // engine/battle/move_effects/teleport.c
    REDIRECTED(BattleCommand_Teleport);

    // engine/battle/move_effects/protect.c
    REDIRECTED(ProtectChance);
    REDIRECTED(BattleCommand_Protect);

    // engine/battle/move_effects/future_sight.c
    REDIRECTED(BattleCommand_CheckFutureSight);
    REDIRECTED(BattleCommand_FutureSight);

    // engine/battle/move_effects/frustration.c
    REDIRECTED(BattleCommand_FrustrationPower);

    // engine/battle/move_effects/rage.c
    REDIRECTED(BattleCommand_Rage);

    // engine/battle/move_effects/bide.c
    REDIRECTED(BattleCommand_StoreEnergy);
    REDIRECTED(BattleCommand_UnleashEnergy);

    // engine/battle/move_effects/endure.c
    REDIRECTED(BattleCommand_Endure);

    // engine/battle/move_effects/heal_bell.c
    REDIRECTED(BattleCommand_HealBell);

    // engine/battle/move_effects/nightmare.c
    REDIRECTED(BattleCommand_Nightmare);

    // engine/battle/move_effects/perish_song.c
    REDIRECTED(BattleCommand_PerishSong);

    // engine/battle/move_effects/foresight.c
    REDIRECTED(BattleCommand_Foresight);

    // engine/battle/move_effects/beat_up.c
    REDIRECTED(BattleCommand_BeatUp);
    REDIRECTED(BattleCommand_BeatUpFailText);
    // REDIRECTED(GetBeatupMonLocation);

    // engine/pokemon/correct_nick_errors.c
    // REDIRECTED(CorrectNickErrors);

    // engine/battle/move_effects/mirror_coat.c
    REDIRECTED(BattleCommand_MirrorCoat);

    // engine/battle/move_effects/psych_up.c
    REDIRECTED(BattleCommand_PsychUp);

    // engine/battle/move_effects/rapid_spin.c
    REDIRECTED(BattleCommand_ClearHazards);

    // engine/battle/move_effects/disable.c
    REDIRECTED(BattleCommand_Disable);

    // engine/battle/update_battle_huds.c
    // CONVERTED(v_UpdateBattleHUDs);

    // engine/battle/move_effects/pain_split.c
    REDIRECTED(BattleCommand_PainSplit);

    // engine/battle/move_effects/substitute.c
    REDIRECTED(BattleCommand_Substitute);

    // engine/battle/move_effects/baton_pass.c
    REDIRECTED(CheckAnyOtherAlivePartyMons);
    REDIRECTED(BatonPass_LinkPlayerSwitch);
    REDIRECTED(CheckAnyOtherAliveMons);
    REDIRECTED(BatonPass_LinkEnemySwitch);
    REDIRECTED(BattleCommand_BatonPass);
    REDIRECTED(CheckAnyOtherAliveEnemyMons);
    REDIRECTED(FailedBatonPass);
    REDIRECTED(ResetBatonPassStatus);

    // engine/battle/move_effects/encore.c
    REDIRECTED(BattleCommand_Encore);

    // engine/battle/move_effects/mirror_move.c
    REDIRECTED(BattleCommand_MirrorMove);

    // engine/battle/move_effects/mimic.c
    REDIRECTED(BattleCommand_Mimic);

    // engine/battle/move_effects/present.c
    REDIRECTED(BattleCommand_Present);

    // engine/battle/move_effects/spite.c
    REDIRECTED(BattleCommand_Spite);

    // engine/battle/move_effects/thief.c
    REDIRECTED(BattleCommand_Thief);

    // engine/battle/move_effects/conversion.c
    REDIRECTED(BattleCommand_Conversion);

    // engine/battle/move_effects/sleep_talk.c
    REDIRECTED(BattleCommand_SleepTalk);

    // engine/battle/move_effects/conversion2.c
    REDIRECTED(BattleCommand_Conversion2);

    // engine/events/whiteout.c
    REDIRECTED(GetWhiteoutSpawn);
    REDIRECTED(OverworldBGMap);
    // REDIRECTED(Script_BattleWhiteout);
    // REDIRECTED(Script_Whiteout);
    REDIRECTED(HalveMoney);
    REDIRECTED(BattleBGMap);
    // REDIRECTED(OverworldWhiteoutScript);

    // engine/overworld/spawn_points.c
    REDIRECTED(IsSpawnPoint);
    // CONVERTED(EnterMapSpawnPoint);

    // engine/events/misc_scripts.c
    // REDIRECTED(Script_AbortBugContest);
    // REDIRECTED(FindItemInBallScript);

    // engine/events/mom_phone.c
    // CONVERTED(MomBuysItem_DeductFunds);
    // REDIRECTED(MomBoughtWithYourMoneyText);
    // REDIRECTED(MomFoundADollText);
    // CONVERTED(CheckBalance_MomItem2);
    // CONVERTED(DummyPredef3A_DummyData);
    // CONVERTED(GetItemFromMom);
    // REDIRECTED(MomItsInPCText);
    // REDIRECTED(MomItsInYourRoomText);
    // CONVERTED(Mom_GiveItemOrDoll);
    // CONVERTED(Mom_GetScriptPointer);
    // CONVERTED(DummyPredef3A);
    // CONVERTED(MomTriesToBuySomething);
    // REDIRECTED(MomHiHowAreYouText);
    // CONVERTED(DummyPredef3A_DummyFunction);
    // REDIRECTED(MomFoundAnItemText);

    // engine/overworld/map_setup.c
    // REDIRECTED(ReadMapSetupScript);
    // REDIRECTED(RunMapSetupScript);
    // REDIRECTED(SkipUpdateMapSprites);
    // REDIRECTED(FadeOutMapMusic);
    // REDIRECTED(ApplyMapPalettes);
    // REDIRECTED(SuspendMapAnims);
    // REDIRECTED(EnableTextAcceleration);
    // REDIRECTED(ActivateMapAnims);
    // REDIRECTED(LoadMapObjects);
    // REDIRECTED(FadeMapMusicAndPalettes);
    // REDIRECTED(CheckUpdatePlayerSprite);
    // REDIRECTED(ForceMapMusic);
    // REDIRECTED(ResetPlayerObjectAction);
    // REDIRECTED(MapSetup_DummyFunction);

    // engine/overworld/map_objects_2.c
    // REDIRECTED(CheckObjectFlag);
    // REDIRECTED(GetObjectTimeMask);
    // REDIRECTED(LoadObjectMasks);

    // engine/overworld/cmd_queue.c
    // REDIRECTED(CmdQueue_StoneTable);
    // REDIRECTED(GetNthCmdQueueEntry);
    // REDIRECTED(DelCmdQueue);
    // REDIRECTED(HandleCmdQueue);
    // REDIRECTED(WriteCmdQueue);
    // REDIRECTED(v_DelCmdQueue);
    // REDIRECTED(CmdQueues_DecAnonJumptableIndex);
    // REDIRECTED(CmdQueue_Type1);
    // REDIRECTED(CmdQueue_Type4);
    // REDIRECTED(ClearCmdQueue);
    // REDIRECTED(CmdQueue_Type3);
    // REDIRECTED(HandleQueuedCommand);
    // REDIRECTED(CmdQueues_IncAnonJumptableIndex);
    // REDIRECTED(CmdQueue_Null);
    // REDIRECTED(CmdQueues_AnonJumptable);

    // engine/link/link_trade.c
    // REDIRECTED(LinkComms_LoadPleaseWaitTextboxBorderGFX);
    // REDIRECTED(LinkCommsBorderGFX);
    // REDIRECTED(v_LinkTextbox);
    // REDIRECTED(LoadMobileTradeBorderTilemap);
    // REDIRECTED(v__LoadTradeScreenBorderGFX);
    // REDIRECTED(LinkTradeMenu);
    // REDIRECTED(LinkTextbox);
    // REDIRECTED(TestMobileTradeBorderTilemap);
    // REDIRECTED(v_LoadTradeScreenBorderGFX);
    // REDIRECTED(InitTradeSpeciesList);
    // REDIRECTED(CableTradeBorderBottomTilemap);
    // REDIRECTED(CableTradeBorderTopTilemap);
    // REDIRECTED(PrintWaitingTextAndSyncAndExchangeNybble);
    // REDIRECTED(LoadCableTradeBorderTilemap);
    // REDIRECTED(MobileTradeBorderTilemap);
    // REDIRECTED(LoadTradeRoomBGPals);

    // engine/link/time_capsule.c
    // REDIRECTED(CheckAnyOtherAliveMonsForTrade);
    // REDIRECTED(ValidateOTTrademon);
    // REDIRECTED(PlaceTradePartnerNamesAndParty);

    // engine/link/link_2.c
    // REDIRECTED(Link_WaitBGMap);
    // REDIRECTED(LinkTextbox2);
    // REDIRECTED(LinkMonStatsScreen);

    // engine/events/poke_seer.c
    // REDIRECTED(PrintSeerText);
    // REDIRECTED(SeerMoreConfidentText);
    // REDIRECTED(UnknownCaughtData);
    // REDIRECTED(SeerAction4);
    // REDIRECTED(SeerSeeAllText);
    // REDIRECTED(SeerEggText);
    // REDIRECTED(GetCaughtTime);
    // REDIRECTED(SeerMightyText);
    // REDIRECTED(GetCaughtName);
    // REDIRECTED(SeerNoLocationText);
    // REDIRECTED(GetCaughtOT);
    // REDIRECTED(SeerAction1);
    // REDIRECTED(GetCaughtLevel);
    // REDIRECTED(SeerCantTellAThingText);
    // REDIRECTED(SeerTimeLevelText);
    // REDIRECTED(PokeSeer);
    // REDIRECTED(GetCaughtLocation);
    // REDIRECTED(SeerTradeText);
    // REDIRECTED(GetCaughtGender);
    // REDIRECTED(ReadCaughtData);
    // REDIRECTED(SeerImpressedText);
    // REDIRECTED(SeerTexts);
    // REDIRECTED(SeerAction2);
    // REDIRECTED(SeerNameLocationText);
    // REDIRECTED(SeerMoreCareText);
    // REDIRECTED(SeerActions);
    // REDIRECTED(SeerAction);
    // REDIRECTED(SeerAdviceTexts);
    // REDIRECTED(SeerAdvice);
    // REDIRECTED(SeerAction3);
    // REDIRECTED(SeerAction0);
    // REDIRECTED(SeerMuchStrengthText);
    // REDIRECTED(SeerDoNothingText);

    // engine/events/repel.c
    // REDIRECTED(RepelWoreOffScript);

    // engine/overworld/player_step.c
    // CONVERTED(v_HandlePlayerStep);
    CONVERTED(UpdatePlayerCoords);
    CONVERTED(HandlePlayerStep);
    CONVERTED(UpdateOverworldMap);
    CONVERTED(ScrollScreen);

    // engine/tilesets/tileset_palettes.c
    // REDIRECTED(LoadBattleTowerInsidePalette);
    // REDIRECTED(MansionPalette2);
    // REDIRECTED(IcePathPalette);
    // REDIRECTED(PokeComPalette);
    // REDIRECTED(LoadPokeComPalette);
    // REDIRECTED(LoadIcePathPalette);
    // REDIRECTED(LoadRadioTowerPalette);
    // REDIRECTED(HousePalette);
    // REDIRECTED(LoadMansionPalette);
    // REDIRECTED(LoadSpecialMapPalette);
    // REDIRECTED(BattleTowerInsidePalette);
    // REDIRECTED(LoadHousePalette);
    // REDIRECTED(MansionPalette1);
    // REDIRECTED(RadioTowerPalette);
}
