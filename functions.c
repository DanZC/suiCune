#include "functions.h"
#include "data/maps/scripts.h"

#define ROM_SIZE 0x200000
void init_function_pointers(void) {
    for (int i = 0; i < ROM_SIZE; i++) redirectFunc[i] = convertedFunc[i] = NULL;

    // home/array.c
    // CONVERTED(AddNTimes);
    // CONVERTED(IsInArray);
    // CONVERTED(SkipNames);

    // home/audio.c
    CONVERTED(MaxVolume);
    // CONVERTED(PlayMusic2);
    CONVERTED(MinVolume);
    // CONVERTED(RestartMapMusic);
    // CONVERTED(IsSFXPlaying);
    CONVERTED(UpdateSound);
    REDIRECTED(FadeOutToMusic);
    // CONVERTED(SpecialMapMusic);
    // CONVERTED(GetMapMusic_MaybeSpecial);
    // CONVERTED(WaitPlaySFX);
    REDIRECTED(PlaceBCDNumberSprite);
    CONVERTED(LowVolume);
    // CONVERTED(PlaySFX);
    CONVERTED(TerminateExpBarSound);
    CONVERTED(InitSound);
    // CONVERTED(TryRestartMapMusic);
    CONVERTED(FadeInToMusic);
    CONVERTED(PlayMapMusicBike);
    // CONVERTED(WaitSFX);
    // CONVERTED(PlayMapMusic);
    // CONVERTED(PlayMusic);
    CONVERTED(FadeToMapMusic);
    // CONVERTED(PlayCry);
    // CONVERTED(SkipMusic);
    // CONVERTED(CheckSFX);
    CONVERTED(ChannelsOff);
    CONVERTED(SFXChannelsOff);

    // home/battle.c
    CONVERTED(UpdateBattleHuds);
    // CONVERTED(OpponentPartyAttr);
    CONVERTED(UpdateOpponentInParty);
    // CONVERTED(GetPartyLocation);
    // CONVERTED(UserPartyAttr);
    CONVERTED(SetPlayerTurn);
    CONVERTED(PushLYOverrides);
    // CONVERTED(GetBattleAnimByte);
    CONVERTED(RefreshBattleHuds);
    CONVERTED(MobileTextBorder);
    // CONVERTED(OTPartyAttr);
    REDIRECTED(FarCopyRadioText);
    // CONVERTED(BattleTextbox);
    CONVERTED(UpdateUserInParty);
    // CONVERTED(GetPartyParamLocation);
    // CONVERTED(BattlePartyAttr);
    CONVERTED(UpdateBattleMonInParty);
    REDIRECTED(GetDexNumber);
    // CONVERTED(GetBattleAnimPointer);
    // CONVERTED(StdBattleTextbox);
    CONVERTED(SetEnemyTurn);
    // CONVERTED(UpdateBattleMon);
    CONVERTED(UpdateEnemyMonInParty);
    CONVERTED(ResetDamage);

    // home/battle_vars.c
    // CONVERTED(BattleVarLocations);
    // CONVERTED(BattleVarPairs);
    // CONVERTED(GetBattleVar);
    // CONVERTED(GetBattleVarAddr);

    // home/call_regs.c
    // REDIRECTED(v_hl_);
    REDIRECTED(v_de_);

    // home/clear_sprites.c
    CONVERTED(HideSprites);
    CONVERTED(ClearSprites);

    // home/compare.c
    // CONVERTED(CompareBytesLong);
    // CONVERTED(CompareBytes);

    // home/copy.c
    // REDIRECTED(GetFarWRAMWord);
    // CONVERTED(GetFarByte);
    // CONVERTED(FarCopyWRAM);
    // CONVERTED(CopyBytes);
    // CONVERTED(GetFarWRAMByte);
    // CONVERTED(ByteFill);
    // CONVERTED(SwapBytes);
    // CONVERTED(GetFarWord);

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
    // CONVERTED(DelayFrame);
    // CONVERTED(DelayFrames);

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
    // CONVERTED(RotatePalettesLeft);
    // CONVERTED(RotatePalettesRight);
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
    // CONVERTED(ClearsScratch);
    // CONVERTED(ClearWRAM);
    // CONVERTED(Reset);
    // CONVERTED(ClearVRAM);
    // CONVERTED(Init);
    // CONVERTED(v_Start);

    // home/item.c
    // REDIRECTED(ReceiveItem);
    // REDIRECTED(CheckTossableItem);
    // REDIRECTED(CheckItem);
    CONVERTED(DoItemEffect);
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
    // CONVERTED(BlinkCursor);
    // CONVERTED(WaitPressAorB_BlinkCursor);
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
    // CONVERTED(SimpleMultiply);
    // CONVERTED(SimpleDivide);
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
    // CONVERTED(ComputePathToWalkToPlayer);
    // CONVERTED(DecrementMovementBufferCount);
    // CONVERTED(InitMovementBuffer);
    // CONVERTED(AppendToMovementBufferNTimes);
    // CONVERTED(AppendToMovementBuffer);

    // home/names.c
    // CONVERTED(GetItemName);
    // CONVERTED(GetMoveName);
    // CONVERTED(GetBasePokemonName);
    // CONVERTED(GetPokemonName);
    // CONVERTED(GetName);
    // CONVERTED(GetTMHMName);
    // CONVERTED(GetNthString);
    // CONVERTED(NamesPointers);

    // home/palettes.c
    // CONVERTED(UpdatePalsIfCGB);
    // CONVERTED(ClearVBank1);
    // REDIRECTED(DmgToCgbObjPal0);
    // CONVERTED(UpdateCGBPals);
    // CONVERTED(DmgToCgbBGPals);
    // CONVERTED(DmgToCgbObjPals);
    // CONVERTED(CopyPals);
    // CONVERTED(SwapTextboxPalettes);
    // CONVERTED(ScrollBGMapPalettes);
    // CONVERTED(ForceUpdateCGBPals);
    // REDIRECTED(DmgToCgbObjPal1);
    CONVERTED(ReloadSpritesNoPalettes);
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
    // CONVERTED(PrintBCDNumber);
    // CONVERTED(PrintBCDDigit);

    // home/printer.c
    // REDIRECTED(PrinterReceive);
    // REDIRECTED(AskSerial);

    // home/print_text.c
    // CONVERTED(CopyDataUntil);
    // CONVERTED(PrintNum);
    // CONVERTED(FarPrintText);
    // CONVERTED(MobilePrintNum);
    // CONVERTED(PrintLetterDelay);
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
    // CONVERTED(Cosine);
    // CONVERTED(Sine);

    // home/sprite_anims.c
    // REDIRECTED(InitSpriteAnimStruct);
    // REDIRECTED(ReinitSpriteAnimFrame);

    // home/sprite_updates.c
    // REDIRECTED(DisableSpriteUpdates);
    // REDIRECTED(EnableSpriteUpdates);

    // home/sram.c
    // CONVERTED(CloseSRAM);
    // CONVERTED(OpenSRAM);

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
    // CONVERTED(TextCommand_RAM);
    // CONVERTED(TextCommand_STRINGBUFFER);
    // REDIRECTED(TextboxPalette);
    // REDIRECTED(v_ContText);
    // REDIRECTED(CheckDict);  // Manualy convert?
    // REDIRECTED(PCChar);
    // REDIRECTED(PlaceString);
    // REDIRECTED(LineFeedChar);
    // CONVERTED(TextCommand_SOUND);
    // REDIRECTED(Paragraph);
    // REDIRECTED(PokeFluteTerminator);
    // REDIRECTED(Diacritic);
    // REDIRECTED(PlaceMoveTargetsName);
    // REDIRECTED(TMCharText);
    // CONVERTED(TextCommand_START);
    // REDIRECTED(PlaceKokoWaText);
    // REDIRECTED(PlacePOKe);
    // REDIRECTED(LineChar);
    // CONVERTED(TextCommand_FAR);
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
    // CONVERTED(TextCommand_SCROLL);
    // REDIRECTED(PlaceBattlersName);
    // REDIRECTED(TextSFX);
    // REDIRECTED(NextLineChar);
    // REDIRECTED(TextboxBorder);
    // CONVERTED(TextCommand_PROMPT_BUTTON);
    // REDIRECTED(v_ContTextNoPause);
    // REDIRECTED(CarriageReturnChar);
    CONVERTED(UnloadBlinkingCursor);
    // REDIRECTED(Text_WaitBGMap);
    // REDIRECTED(PlaceGenderedPlayerName);
    // REDIRECTED(PlaceWatashi);
    // REDIRECTED(PlacePOKeText);
    // CONVERTED(FillBoxWithByte);
    // REDIRECTED(GameFreakText);
    // CONVERTED(TextCommand_DOTS);
    // REDIRECTED(NullChar);
    // REDIRECTED(PlaceDexEnd);
    // CONVERTED(TextCommand_MOVE);
    // REDIRECTED(PrintText);
    // REDIRECTED(Textbox);
    // REDIRECTED(SixDotsChar);
    // REDIRECTED(PlaceKokoWa);
    // REDIRECTED(PlaceCommandCharacter);
    // CONVERTED(TextCommand_BCD);
    // CONVERTED(TextCommand_LOW);
    // CONVERTED(TextCommand_WAIT_BUTTON);
    // REDIRECTED(SpeechTextbox);
    // REDIRECTED(BuenaPrintText);
    // REDIRECTED(PlaceKougeki);
    // REDIRECTED(SixDotsCharText);
    CONVERTED(LoadBlinkingCursor);
    // CONVERTED(DoTextUntilTerminator);
    // CONVERTED(DoTextUntilTerminator_TextCommand);
    // REDIRECTED(ContText);
    // REDIRECTED(PrintPlayerName);
    // REDIRECTED(DummyChar);
    // REDIRECTED(RocketChar);
    // CONVERTED(TextCommand_START_ASM);
    // REDIRECTED(PrintRivalName);
    // REDIRECTED(PlaceFarString);
    // REDIRECTED(ClearScreen);
    // CONVERTED(PlaceHLTextAtBC);
    // REDIRECTED(PlaceMoveUsersName);
    // REDIRECTED(PCCharText);
    // CONVERTED(ClearBox);
    // REDIRECTED(PrintRedsName);
    // REDIRECTED(EnemyText);
    // CONVERTED(TextCommand_DECIMAL);
    // REDIRECTED(PrintGreensName);
    // CONVERTED(TextCommand_CRY);
    // REDIRECTED(RadioTerminator);
    // CONVERTED(TextCommand_PAUSE);
    // REDIRECTED(TrainerChar);
    // REDIRECTED(TextScroll);
    // CONVERTED(TextCommand_DAY);
    // REDIRECTED(PromptText);
    // REDIRECTED(PlaceEnemysName);
    // REDIRECTED(DoneText);
    // REDIRECTED(ChanSuffixText);
    // REDIRECTED(TextCommands);
    // REDIRECTED(SetUpTextbox);
    // REDIRECTED(KunSuffixText);
    // CONVERTED(TextCommand_BOX);
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
    // CONVERTED(UpdateTimeAndPals);
    // CONVERTED(TimeOfDayPals);
    // CONVERTED(UpdateTimePals);

    // home/trainers.c
    // REDIRECTED(CheckTrainerFlag);
    // REDIRECTED(FacingPlayerDistance_bc);
    // REDIRECTED(TalkToTrainer);
    // REDIRECTED(LoadTrainer_continue);
    // REDIRECTED(FacingPlayerDistance);
#if CONVERTED_OVERWORLD_LOOP
    CONVERTED(PrintWinLossText);
#endif
    // REDIRECTED(v_CheckTrainerBattle);
    // REDIRECTED(CheckTrainerBattle);

    // home/vblank.c
    // CONVERTED(VBlank3);
    // CONVERTED(VBlank1);
    // CONVERTED(UpdatePals);
    // CONVERTED(VBlank2);
    CONVERTED(VBlank);
    // CONVERTED(VBlank0);
    // CONVERTED(VBlank5);
    // CONVERTED(VBlank6);
    // CONVERTED(VBlank4);

    // home/video.c
    CONVERTED(WaitTop);
    // CONVERTED(DMATransfer);
    // CONVERTED(UpdateBGMapBuffer);
    CONVERTED(Serve1bppRequest);
    CONVERTED(UpdateBGMap);
    CONVERTED(v_Serve2bppRequest);
    CONVERTED(Serve2bppRequest_VBlank);
    CONVERTED(Serve2bppRequest);
    CONVERTED(AnimateTileset);

    // home/window.c
    REDIRECTED(CloseText);
    REDIRECTED(SafeUpdateSprites);
    CONVERTED(RefreshScreen);
    REDIRECTED(OpenText);
    // REDIRECTED(SetCarryFlag);
    REDIRECTED(v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);

    // home/tilemap.c
    // CONVERTED(IsCGB);
    // CONVERTED(SetHPPal);
    CONVERTED(WaitBGMap);
    REDIRECTED(CGBOnly_CopyTilemapAtOnce);
    REDIRECTED(v_CopyTilemapAtOnce);
    // CONVERTED(v_CopyTilemapAtOnce_CopyBGMapViaStack);
    REDIRECTED(SetPalettes);
    CONVERTED(ClearBGPalettes);
    REDIRECTED(CopyTilemapAtOnce);
    REDIRECTED(CopyAttrmapAndTilemapToWRAMBank3);
    REDIRECTED(GetMemSGBLayout);
    // CONVERTED(GetHPPal);
    // CONVERTED(GetSGBLayout);
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
    CONVERTED(SetDefaultBoxNames);
    CONVERTED(InitializeNPCNames);
    CONVERTED(InitializeWorld);
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
    CONVERTED(NamePlayer);
    //REDIRECTED(ShrinkFrame);
    //REDIRECTED(OakText7);
    CONVERTED(OakSpeech);
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
    CONVERTED(IntroSequence);
    CONVERTED(GameInit);
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
    CONVERTED(SaveMenu_CopyTilemapAtOnce);
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
    // CONVERTED(BattleAnimFunction_MoveWaveToTarget);
    // CONVERTED(BattleAnimFunction_FloatUp);
    // CONVERTED(BattleAnimFunction_ThrowFromUserToTargetAndDisappear);
    // CONVERTED(BattleAnim_Cosine_e);
    // CONVERTED(BattleAnimFunction_MoveFromUserToTargetSpinAround);
    // CONVERTED(BattleAnimFunction_SacredFire);
    // CONVERTED(BattleAnimFunction_PerishSong);
    // CONVERTED(BattleAnimFunction_PsychUp);
    // CONVERTED(BattleAnimFunction_Null);
    // CONVERTED(BattleAnimFunction_Drop);
    // CONVERTED(BattleAnimFunction_SpeedLine);
    // CONVERTED(BattleAnimFunction_SpiralDescent);
    // CONVERTED(BattleAnimFunction_AncientPower);
    // REDIRECTED(BattleAnim_AbsCosinePrecise);
    // CONVERTED(BattleAnimFunction_Agility);
    // CONVERTED(BattleAnimFunction_RapidSpin);
    // CONVERTED(BattleAnimFunction_SwaggerMorningSun);
    // CONVERTED(BattleAnimFunction_BatonPass);
    // CONVERTED(BattleAnimFunction_LeechSeed);
    // CONVERTED(BattleAnim_Sine_e);
    // CONVERTED(BattleAnimFunction_Recover);
    // REDIRECTED(BattleAnimSineWave);
    // CONVERTED(BattleAnimFunction_Conversion);
    // CONVERTED(BattleAnimFunction_BetaPursuit);
    // CONVERTED(BattleAnimFunction_Horn);
    // CONVERTED(BattleAnimFunction_Bite);
    // CONVERTED(BattleAnim_Cosine);
    // CONVERTED(BattleAnimFunction_Absorb);
    // REDIRECTED(GetBallAnimPal);
    // CONVERTED(BattleAnimFunction_ConfuseRay);
    // CONVERTED(BattleAnimFunction_SafeguardProtect);
    // CONVERTED(BattleAnimFunction_Ember);
    // CONVERTED(BattleAnimFunction_EncoreBellyDrum);
    // CONVERTED(BattleAnimFunction_Amnesia);
    // CONVERTED(BattleAnimFunction_PokeBallBlocked);
    // CONVERTED(BattleAnimFunction_Spikes);
    // CONVERTED(BattleAnimFunction_Dig);
    // CONVERTED(BattleAnimFunction_Shiny);
    // CONVERTED(BattleAnimFunction_SkyAttack);
    // CONVERTED(BattleAnimFunction_GrowthSwordsDance);
    // CONVERTED(BattleAnimFunction_WaterGun);
    // CONVERTED(BattleAnimFunction_Needle);
    // CONVERTED(BattleAnim_Sine);
    // CONVERTED(BattleAnimFunction_Sound);
    // CONVERTED(BattleAnimFunction_PoisonGas);
    // CONVERTED(BattleAnimFunction_String);
    // CONVERTED(BattleAnimFunction_FireBlast);
    // CONVERTED(BattleAnimFunction_PokeBall);
    // CONVERTED(BattleAnimFunction_Sludge);
    // CONVERTED(BattleAnimFunction_Surf);
    // REDIRECTED(BattleAnim_AbsSinePrecise);
    // REDIRECTED(BattleAnim_StepThrownToTarget);
    // CONVERTED(BattleAnimFunction_Dizzy);
    // CONVERTED(BattleAnimFunction_ThiefPayday);
    // REDIRECTED(BattleAnim_StepToTarget);
    // CONVERTED(BattleAnimFunction_ThunderWave);
    // CONVERTED(BattleAnimFunction_Cotton);
    // CONVERTED(BattleAnimFunction_Egg);
    // CONVERTED(BattleAnimFunction_MetronomeHand);
    // CONVERTED(BattleAnimFunction_PresentSmokescreen);
    // REDIRECTED(BattleAnim_IncAnonJumptableIndex);
    // CONVERTED(BattleAnimFunction_Wrap);
    // CONVERTED(BattleAnimFunction_RazorLeaf);
    // CONVERTED(BattleAnimFunction_Sing);
    // CONVERTED(BattleAnimFunction_HiddenPower);
    // CONVERTED(BattleAnimFunction_SmokeFlameWheel);
    // CONVERTED(BattleAnimFunction_Paralyzed);
    // CONVERTED(BattleAnimFunction_HealBellNotes);
    // CONVERTED(BattleAnimFunction_Curse);
    // CONVERTED(BattleAnimFunction_Bubble);
    // CONVERTED(BattleAnimFunction_AbsorbCircle);
    REDIRECTED(DoBattleAnimFrame);
    REDIRECTED(BattleAnimFunction_AnimObjB0);
    // REDIRECTED(BattleAnim_ScatterHorizontal);
    // CONVERTED(BattleAnimFunction_RazorWind);
    // CONVERTED(BattleAnimFunction_Clamp_Encore);
    // REDIRECTED(BattleAnim_StepCircle);
    // REDIRECTED(BattleAnim_AnonJumptable);
    // CONVERTED(BattleAnimFunction_MetronomeSparkleSketch);
    // CONVERTED(BattleAnimFunction_Bonemerang);
    // CONVERTED(BattleAnimFunction_ThrowFromUserToTarget);
    // CONVERTED(BattleAnimFunction_MoveFromUserToTarget);
    // CONVERTED(BattleAnimFunction_LockOnMindReader);
    // CONVERTED(BattleAnimFunction_SolarBeam);
    // CONVERTED(BattleAnimFunction_RockSmash);
    // CONVERTED(BattleAnimFunction_Gust);
    // CONVERTED(BattleAnimFunction_Powder);
    // CONVERTED(BattleAnimFunction_PetalDance);
    // CONVERTED(BattleAnimFunction_StrengthSeismicToss);
    // CONVERTED(BattleAnimFunction_Kick);
    // CONVERTED(BattleAnimFunction_MoveInCircle);
    // CONVERTED(BattleAnimFunction_Shake);
    // CONVERTED(BattleAnimFunction_RainSandstorm);
    // CONVERTED(BattleAnimFunction_MoveUp);
    // CONVERTED(BattleAnimFunction_MoveFromUserToTargetAndDisappear);

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
    // CONVERTED(v_PlayCry);
    // CONVERTED(v_PlaySFX);
    // CONVERTED(PlayStereoSFX);
    // CONVERTED(LoadChannel);
    // CONVERTED(ChannelInit);
    // CONVERTED(LoadMusicByte);
    // CONVERTED(GetLRTracks);
    CONVERTED(ClearChannels);
    // CONVERTED(ClearChannel);
    // CONVERTED(PlayTrainerEncounterMusic);

    // home/map.c
    CONVERTED(ClearBGMapBuffer);
    // CONVERTED(UpdateBGMapColumn);
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
#if CONVERTED_OVERWORLD_LOOP
    CONVERTED(GetWarpDestCoords);
#endif
    // REDIRECTED(GetMapPointer);
    // REDIRECTED(CopyMapPartialAndAttributes);
    // CONVERTED(GetWorldMapLocation);
    // CONVERTED(GetMapMusic);
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
    // CONVERTED(MapTextbox);
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
    CONVERTED(LoadTownMapGFX);
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
    CONVERTED(InitRoamMons);
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
    CONVERTED(ExitBattle);
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
    CONVERTED(SendOutPlayerMon);
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
    CONVERTED(Battle_EnemyFirst);
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
    // REDIRECTED(ResidualDamage);
    CONVERTED(BattleStartMessage);
    // CONVERTED(EnemySwitch);
    CONVERTED(BattleTurn);
    CONVERTED(EnemyTurn_EndOpponentProtectEndureDestinyBond);
    // REDIRECTED(GetSixteenthMaxHP);
    // REDIRECTED(GetMaxHP);
    // REDIRECTED(PickSwitchMonInBattle);
    CONVERTED(FinishBattleAnim);
    // CONVERTED(BattleMenu);
    // REDIRECTED(UpdateHPBar);
    // REDIRECTED(CheckSleepingTreeMon);
    // REDIRECTED(CheckUserHasEnoughHP);
    CONVERTED(LoadTrainerOrWildMonPic);
    // REDIRECTED(BattleWinSlideInEnemyTrainerFrontpic);
    // REDIRECTED(PickPartyMonInBattle);
    // REDIRECTED(AskUseNextPokemon);
    CONVERTED(HandlePerishSong);
    // REDIRECTED(ResetEnemyStatLevels);
    CONVERTED(ShowSetEnemyMonAndSendOutAnimation);
    // REDIRECTED(ExpPointsText);
    CONVERTED(PlayerTurn_EndOpponentProtectEndureDestinyBond);
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
    CONVERTED(ResetVarsForSubstatusRage);
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
    CONVERTED(HandleDefrost);
    // REDIRECTED(SwitchTurnCore);
    // REDIRECTED(CheckPlayerPartyForFitMon);
    // REDIRECTED(ItemRecoveryAnim);
    // REDIRECTED(ShowLinkBattleParticipantsAfterEnd);
    // REDIRECTED(UpdateBattleStateAndExperienceAfterEnemyFaint);
    // REDIRECTED(GetRoamMonMapNumber);
    CONVERTED(RecallPlayerMon);
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
    CONVERTED(Battle_PlayerFirst);
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
    CONVERTED(HandleLeftovers);
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
    CONVERTED(GiveExperiencePoints);
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
    CONVERTED(BattleIntro);
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
    // REDIRECTED(RadioJumptable);
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
    // REDIRECTED(RocketRadioText8);
    REDIRECTED(RocketRadio4);
    REDIRECTED(OaksPKMNTalk2);
    // REDIRECTED(BuenasPasswordAfterMidnight);
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
    // REDIRECTED(BuenasPasswordCheckTime);
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
    // CONVERTED(StartTrainerBattle_DrawSineWave);
    CONVERTED(StartTrainerBattle_SetUpForRandomScatterOutro);
    REDIRECTED(StartTrainerBattle_LoadPokeBallGraphics);
    REDIRECTED(LoadTrainerBattlePokeballTiles);

    // engine/menus/main_menu.c
    // REDIRECTED(MainMenuItems);
    // REDIRECTED(ClearTilemapEtc);
    // REDIRECTED(MainMenu_Continue);
    // REDIRECTED(MainMenu_Option);
    // REDIRECTED(MainMenu_MysteryGift);
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
    // CONVERTED(GetSpriteAnimFrame);
    // REDIRECTED(InitSpriteAnimBuffer);
    // REDIRECTED(AnimateEndOfExpBar);
    // CONVERTED(Sprites_Sine);
    // CONVERTED(UpdateAnimFrame);
    // CONVERTED(AddOrSubtractX);
    // CONVERTED(Sprites_Cosine);
    // REDIRECTED(DeinitializeAllSprites);
    // REDIRECTED(v_ReinitSpriteAnimFrame);
    // REDIRECTED(v_InitSpriteAnimStruct);
    REDIRECTED(PlaySpriteAnimations);
    // CONVERTED(GetSpriteOAMAttr);
    REDIRECTED(DoNextFrameForAllSprites);
    // CONVERTED(GetSpriteAnimVTile);
    // CONVERTED(GetFrameOAMPointer);
    // REDIRECTED(SGBEndOfExpBarGFX);
    // REDIRECTED(ClearSpriteAnims2);
    // REDIRECTED(UnusedLoadSpriteAnimGFX);
    // REDIRECTED(EndOfExpBarGFX);
    // CONVERTED(DeinitializeSprite);
    // CONVERTED(AddOrSubtractY);

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
    // CONVERTED(DoAnimFrame);
    // REDIRECTED(AnimSeq_PartyMonSelected);

    // engine/gfx/player_gfx.c
    // REDIRECTED(GetPlayerBackpic);
    // REDIRECTED(TrainerCardGFX);
    CONVERTED(ShowPlayerNamingChoices);
    CONVERTED(GetChrisBackpic);
    // REDIRECTED(MovePlayerPic);
    // REDIRECTED(KrisCardPic);
    // REDIRECTED(ChrisPic);
    // CONVERTED(HOF_LoadTrainerFrontpic);
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
    CONVERTED(PlayBattleAnim);
    REDIRECTED(BattleAnimCmd_ClearObjs);
    REDIRECTED(BattleAnimCmd_DropSub);
    REDIRECTED(BattleAnimCmd_BattlerGFX_2Row);
    REDIRECTED(BattleAnimCmd_1GFX);
    CONVERTED(BattleAnimClearHud);
    REDIRECTED(BattleAnimCmd_ResetObp0);
    CONVERTED(v_PlayBattleAnim);
    REDIRECTED(BattleAnimCmd_Jump);
    REDIRECTED(BattleAnimCmd_OBP0);
    REDIRECTED(RunBattleAnimCommand);
    REDIRECTED(BattleAnimCmd_Call);
    REDIRECTED(BattleAnimCmd_SetVar);
    REDIRECTED(BattleAnimCmd_IncVar);
    REDIRECTED(BattleAnimCmd_IncObj);
    REDIRECTED(BattleAnimCmd_IncBGEffect);
    REDIRECTED(RunBattleAnimScript);
    CONVERTED(BattleAnimRequestPals);
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
    CONVERTED(BattleAnim_RevertPals);
    REDIRECTED(BattleAnimCmd_BGP);
    // REDIRECTED(GetMinimizePic);
    REDIRECTED(BattleAnimCmd_KeepSprites);
    REDIRECTED(BattleAnimCmd_Obj);
    REDIRECTED(BattleAnimCmd_EA);
    REDIRECTED(BattleAnimCmd_IfParamAnd);
    CONVERTED(BattleAnim_ClearOAM);
    CONVERTED(ClearActorHud);
    REDIRECTED(BattleAnimCmd_BattlerGFX_1Row);
    REDIRECTED(BattleAnimCmd_CheckPokeball);
    REDIRECTED(BattleAnimCmd_EC);
    REDIRECTED(BattleAnimCmd_UpdateActorPic);
    // CONVERTED(BattleAnim_SetOBPals);
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
    // CONVERTED(MinimizePic);
    CONVERTED(PlayHitSound);
    REDIRECTED(BattleAnimCmd_IfVarEqual);
    REDIRECTED(GetSubstitutePic);
    REDIRECTED(BattleAnimRunScript);
    REDIRECTED(BattleAnimCmd_Minimize);
    // CONVERTED(BattleAnim_SetBGPals);
    REDIRECTED(BattleAnimCmd_F6);
    REDIRECTED(BattleAnimCmd_2GFX);
    REDIRECTED(BattleAnimCmd_SetObj);
    REDIRECTED(BattleAnimCmd_EB);
    CONVERTED(BattleAnimAssignPals);

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
    CONVERTED(PlayDamageAnim);
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
    CONVERTED(AnimateCurrentMoveEitherSide);
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
    CONVERTED(AnimateCurrentMove);
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
#if CONVERTED_OVERWORLD_LOOP
    CONVERTED(OverworldLoop);
#endif
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
    CONVERTED(AIChooseMove);

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
    CONVERTED(LoadPartyMenuGFX);
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
    CONVERTED(BattleStatsScreenInit);
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
    CONVERTED(ClearPCItemScreen);
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
    CONVERTED(HealParty);
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
    CONVERTED(CantUseOnEggMessage);
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
    CONVERTED(IsntTheTimeMessage);
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
    CONVERTED(WontHaveAnyEffectMessage);
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
    // CONVERTED(NameRival);
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
    CONVERTED(FoundNone);
    // REDIRECTED(FindPartyMonThatSpeciesYourTrainerID);
    // REDIRECTED(NameRater);
    CONVERTED(FoundOne);
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
    CONVERTED(BlankScreen);
    REDIRECTED(QueueFollowerFirstStep);
    // REDIRECTED(InitializeVisibleSprites);
    REDIRECTED(CopyMapObjectToObjectStruct);
    // REDIRECTED(SpawnPlayer);
    REDIRECTED(CopyDECoordsToMapObject);
    REDIRECTED(SurfStartStep);
    REDIRECTED(WriteObjectXY);
    // REDIRECTED(RefreshPlayerCoords);
    CONVERTED(TrainerWalkToPlayer);
    REDIRECTED(FollowNotExact);
    REDIRECTED(CopyTempObjectToObjectStruct);
    REDIRECTED(CopyObjectStruct);
    REDIRECTED(GetRelativeFacing);
    REDIRECTED(PlayerSpawn_ConvertCoords);
    // REDIRECTED(PlayerObjectTemplate);
    // REDIRECTED(CheckObjectEnteringVisibleRange);

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
    CONVERTED(DoMysteryGiftIfDayHasPassed);
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
    CONVERTED(v_InitializeStartDay);
    // REDIRECTED(CalcHoursDaysSince);
    // REDIRECTED(GetHoursSinceIfLessThan24);
    CONVERTED(ClearDailyTimers);
    // REDIRECTED(GetSecondsSinceIfLessThan60);
    // REDIRECTED(SampleKenjiBreakCountdown);
    // REDIRECTED(UnusedSetSwarmFlag);
    // REDIRECTED(GetTimeElapsed_ExceedsUnitLimit);
    // REDIRECTED(v_CalcMinsHoursDaysSince);
    CONVERTED(InitializeStartDay);
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
    // CONVERTED(ContestBattleMenu);
    // CONVERTED(CommonBattleMenu);
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
    CONVERTED(CheckFirstMonIsEgg);
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
    // REDIRECTED(EnemyUsedXSpecial);
    // REDIRECTED(EnemyPotionFinish);
    // REDIRECTED(EnemyUsedFullHeal);
    // REDIRECTED(EnemyUsedOnText);
    // REDIRECTED(AI_TryItem);
    // REDIRECTED(EnemyUsedXItem);
    // CONVERTED(AI_Switch);
    // REDIRECTED(EnemyUsedXAccuracy);
    // REDIRECTED(EnemyUsedXAttack);
    // REDIRECTED(EnemyWithdrewText);
    // REDIRECTED(SwitchSometimes);
    // REDIRECTED(FullRestoreContinue);
    // REDIRECTED(AICheckEnemyFractionMaxHP);
    // REDIRECTED(EnemyUsedXSpeed);
    // REDIRECTED(EnemyUsedDireHit);
    // REDIRECTED(AI_Items);
    // REDIRECTED(EnemyUsedPotion);
    // REDIRECTED(EnemyUsedXDefend);
    // REDIRECTED(SwitchOften);
    // REDIRECTED(DontSwitch);
    // REDIRECTED(EnemyUsedSuperPotion);
    // REDIRECTED(AIUpdateHUD);
    // REDIRECTED(AI_SwitchOrTryItem);
    // REDIRECTED(EnemyUsedHyperPotion);
    // REDIRECTED(AI_HealStatus);
    // REDIRECTED(AI_TrySwitch);
    // REDIRECTED(CheckSubstatusCantRun);
    // REDIRECTED(EnemyUsedFullHealRed);
    // REDIRECTED(EnemyPotionContinue);
    // REDIRECTED(PrintText_UsedItemOn);
    // REDIRECTED(EnemyUsedGuardSpec);
    // REDIRECTED(PrintText_UsedItemOn_AND_AIUpdateHUD);
    // REDIRECTED(EnemyUsedMaxPotion);
    // REDIRECTED(SwitchRarely);
    // REDIRECTED(AIUsedItemSound);
    // REDIRECTED(EnemyUsedFullRestore);

    // engine/rtc/restart_clock.c
    // REDIRECTED(JPMinuteString);
    // CONVERTED(RestartClock);
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

    // engine/events/trainer_scripts.c
    // REDIRECTED(AlreadyBeatenTrainerScript);
    // REDIRECTED(TalkToTrainerScript);
    // REDIRECTED(SeenByTrainerScript);
    // REDIRECTED(StartBattleWithMapTrainerScript);

    // engine/menus/menu_2.c
    // REDIRECTED(PlaceMenuItemName);
    // REDIRECTED(PlaceMoneyTopRight);
    // REDIRECTED(DisplayMoneyAndCoinBalance);
    // REDIRECTED(MoneyTopRightMenuHeader);
    // REDIRECTED(MoneyBottomLeftMenuHeader);
    // REDIRECTED(CoinString);
    // REDIRECTED(PlaceMoneyBottomLeft);
    // REDIRECTED(PlaceMoneyAtTopLeftOfTextbox);
    // REDIRECTED(FindApricornsInBag);
    // REDIRECTED(MoneyString);
    // CONVERTED(StartMenu_DrawBugContestStatusBox);
    CONVERTED(StartMenu_PrintBugContestStatus);
    // REDIRECTED(PlaceMoneyTextbox);
    // REDIRECTED(PlaceMenuItemQuantity);
    // REDIRECTED(StartMenu_PrintSafariGameStatus);
    // REDIRECTED(ShowMoney_TerminatorString);
    // REDIRECTED(DisplayCoinCaseBalance);

    // engine/pokegear/townmap_convertlinebreakcharacters.c
    CONVERTED(TownMap_ConvertLineBreakCharacters);

    // maps/NewBarkTown.c
    CONVERTED_SCRIPT(NewBarkTownTeacherScript);
    CONVERTED_SCRIPT(NewBarkTownFisherScript);
    CONVERTED_SCRIPT(NewBarkTownSilverScript);

    // maps/CherrygroveCity.c
    CONVERTED_SCRIPT(CherrygroveCityGuideGent);
    CONVERTED_SCRIPT(CherrygroveSilverSceneSouth);
    CONVERTED_SCRIPT(CherrygroveSilverSceneNorth);
    CONVERTED_SCRIPT(CherrygroveTeacherScript);
    CONVERTED_SCRIPT(CherrygroveYoungsterScript);
    CONVERTED_SCRIPT(MysticWaterGuy);
    CONVERTED_SCRIPT(CherrygroveCitySign);
    CONVERTED_SCRIPT(GuideGentsHouseSign);
    CONVERTED_SCRIPT(CherrygroveCityPokecenterSign);
    CONVERTED_SCRIPT(CherrygroveCityMartSign);

    // maps/VioletCity.c
    CONVERTED_SCRIPT(VioletCityEarlScript);
    CONVERTED_SCRIPT(VioletCityLassScript);
    CONVERTED_SCRIPT(VioletCitySuperNerdScript);
    CONVERTED_SCRIPT(VioletCityGrampsScript);
    CONVERTED_SCRIPT(VioletCityYoungsterScript);
    CONVERTED_SCRIPT(VioletCityFruitTree);
    CONVERTED_SCRIPT(VioletCityPPUp);
    CONVERTED_SCRIPT(VioletCityRareCandy);

    // maps/AzaleaTown.c
    CONVERTED_SCRIPT(AzaleaTownRocket1Script);
    CONVERTED_SCRIPT(AzaleaTownGrampsScript);
    CONVERTED_SCRIPT(AzaleaTownTeacherScript);
    CONVERTED_SCRIPT(AzaleaTownYoungsterScript);
    CONVERTED_SCRIPT(AzaleaTownSlowpokeScript);
    CONVERTED_SCRIPT(AzaleaTownSlowpokeScript);
    CONVERTED_SCRIPT(AzaleaTownSlowpokeScript);
    CONVERTED_SCRIPT(AzaleaTownSlowpokeScript);
    CONVERTED_SCRIPT(WhiteApricornTree);
    CONVERTED_SCRIPT(AzaleaTownRocket2Script);
    CONVERTED_SCRIPT(AzaleaTownKurtScript);

    // maps/CianwoodCity.c
    CONVERTED_SCRIPT(CianwoodCityYoungster);
    CONVERTED_SCRIPT(CianwoodCityPokefanM);
    CONVERTED_SCRIPT(CianwoodCityLass);
    CONVERTED_SCRIPT(CianwoodCityRock);
    // CONVERTED_SCRIPT(CianwoodCityRock);
    // CONVERTED_SCRIPT(CianwoodCityRock);
    // CONVERTED_SCRIPT(CianwoodCityRock);
    // CONVERTED_SCRIPT(CianwoodCityRock);
    // CONVERTED_SCRIPT(CianwoodCityRock);
    CONVERTED_SCRIPT(CianwoodCityChucksWife);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/GoldenrodCity.c
    CONVERTED_SCRIPT(GoldenrodCityPokefanMScript);
    CONVERTED_SCRIPT(GoldenrodCityYoungster1Script);
    CONVERTED_SCRIPT(GoldenrodCityCooltrainerF1Script);
    CONVERTED_SCRIPT(GoldenrodCityCooltrainerF2Script);
    CONVERTED_SCRIPT(GoldenrodCityYoungster2Script);
    CONVERTED_SCRIPT(GoldenrodCityLassScript);
    CONVERTED_SCRIPT(GoldenrodCityGrampsScript);
    CONVERTED_SCRIPT(GoldenrodCityRocketScoutScript);
    CONVERTED_SCRIPT(GoldenrodCityRocket1Script);
    CONVERTED_SCRIPT(GoldenrodCityRocket2Script);
    CONVERTED_SCRIPT(GoldenrodCityRocket3Script);
    CONVERTED_SCRIPT(GoldenrodCityRocket4Script);
    CONVERTED_SCRIPT(GoldenrodCityRocket5Script);
    CONVERTED_SCRIPT(GoldenrodCityRocket6Script);
    CONVERTED_SCRIPT(MoveTutorScript);

    // maps/OlivineCity.c
    CONVERTED_SCRIPT(OlivineCitySailor1Script);
    CONVERTED_SCRIPT(OlivineCityStandingYoungsterScript);
    CONVERTED_SCRIPT(OlivineCitySailor2Script);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/EcruteakCity.c
    CONVERTED_SCRIPT(EcruteakCityGramps1Script);
    CONVERTED_SCRIPT(EcruteakCityGramps2Script);
    CONVERTED_SCRIPT(EcruteakCityLass1Script);
    CONVERTED_SCRIPT(EcruteakCityLass2Script);
    CONVERTED_SCRIPT(EcruteakCityFisherScript);
    CONVERTED_SCRIPT(EcruteakCityYoungsterScript);
    CONVERTED_SCRIPT(EcruteakCityGramps3Script);

    // maps/MahoganyTown.c
    CONVERTED_SCRIPT(MahoganyTownPokefanMScript);
    CONVERTED_SCRIPT(MahoganyTownGrampsScript);
    CONVERTED_SCRIPT(MahoganyTownFisherScript);
    CONVERTED_SCRIPT(MahoganyTownLassScript);

    // maps/LakeOfRage.c
    CONVERTED_SCRIPT(LakeOfRageLanceScript);
    CONVERTED_SCRIPT(LakeOfRageGrampsScript);
    CONVERTED_SCRIPT(LakeOfRageSuperNerdScript);
    CONVERTED_SCRIPT(LakeOfRageCooltrainerFScript);
    CONVERTED_SCRIPT(TrainerFisherAndre);
    CONVERTED_SCRIPT(TrainerFisherRaymond);
    CONVERTED_SCRIPT(TrainerCooltrainermAaron);
    CONVERTED_SCRIPT(TrainerCooltrainerfLois);
    CONVERTED_SCRIPT(RedGyarados);
    CONVERTED_SCRIPT(WesleyScript);
    CONVERTED_SCRIPT(LakeOfRageElixer);
    CONVERTED_SCRIPT(LakeOfRageTMDetect);

    // maps/BlackthornCity.c
    CONVERTED_SCRIPT(BlackthornSuperNerdScript);
    CONVERTED_SCRIPT(BlackthornSuperNerdScript);
    CONVERTED_SCRIPT(BlackthornGramps1Script);
    CONVERTED_SCRIPT(BlackthornGramps2Script);
    CONVERTED_SCRIPT(BlackthornBlackBeltScript);
    CONVERTED_SCRIPT(BlackthornCooltrainerF1Script);
    CONVERTED_SCRIPT(BlackthornYoungsterScript);
    CONVERTED_SCRIPT(SantosScript);
    CONVERTED_SCRIPT(BlackthornCooltrainerF2Script);

    // maps/PalletTown.c
    CONVERTED_SCRIPT(PalletTownTeacherScript);
    CONVERTED_SCRIPT(PalletTownFisherScript);

    // maps/ViridianCity.c
    CONVERTED_SCRIPT(ViridianCityCoffeeGramps);
    CONVERTED_SCRIPT(ViridianCityGrampsNearGym);
    CONVERTED_SCRIPT(ViridianCityDreamEaterFisher);
    CONVERTED_SCRIPT(ViridianCityYoungsterScript);

    // maps/PewterCity.c
    CONVERTED_SCRIPT(PewterCityCooltrainerFScript);
    CONVERTED_SCRIPT(PewterCityBugCatcherScript);
    CONVERTED_SCRIPT(PewterCityGrampsScript);
    CONVERTED_SCRIPT(PewterCityFruitTree1);
    CONVERTED_SCRIPT(PewterCityFruitTree2);

    // maps/CeruleanCity.c
    CONVERTED_SCRIPT(CeruleanCityCooltrainerMScript);
    CONVERTED_SCRIPT(CeruleanCitySuperNerdScript);
    CONVERTED_SCRIPT(CeruleanCitySlowbro);
    CONVERTED_SCRIPT(CeruleanCityCooltrainerFScript);
    CONVERTED_SCRIPT(CeruleanCityFisherScript);
    CONVERTED_SCRIPT(CeruleanCityYoungsterScript);

    // maps/VermilionCity.c
    CONVERTED_SCRIPT(VermilionCityTeacherScript);
    CONVERTED_SCRIPT(VermilionMachopOwner);
    CONVERTED_SCRIPT(VermilionMachop);
    CONVERTED_SCRIPT(VermilionCitySuperNerdScript);
    CONVERTED_SCRIPT(VermilionSnorlax);
    CONVERTED_SCRIPT(VermilionGymBadgeGuy);

    // maps/LavenderTown.c
    CONVERTED_SCRIPT(LavenderTownPokefanMScript);
    CONVERTED_SCRIPT(LavenderTownTeacherScript);
    CONVERTED_SCRIPT(LavenderTownGrampsScript);
    CONVERTED_SCRIPT(LavenderTownYoungsterScript);

    // maps/CeladonCity.c
    CONVERTED_SCRIPT(CeladonCityFisherScript);
    CONVERTED_SCRIPT(CeladonCityPoliwrath);
    CONVERTED_SCRIPT(CeladonCityTeacher1Script);
    CONVERTED_SCRIPT(CeladonCityGramps1Script);
    CONVERTED_SCRIPT(CeladonCityGramps2Script);
    CONVERTED_SCRIPT(CeladonCityYoungster1Script);
    CONVERTED_SCRIPT(CeladonCityYoungster2Script);
    CONVERTED_SCRIPT(CeladonCityTeacher2Script);
    CONVERTED_SCRIPT(CeladonCityLassScript);

    // maps/SaffronCity.c
    CONVERTED_SCRIPT(SaffronCityLass1Script);
    CONVERTED_SCRIPT(SaffronCityPokefanMScript);
    CONVERTED_SCRIPT(SaffronCityCooltrainerMScript);
    CONVERTED_SCRIPT(SaffronCityCooltrainerFScript);
    CONVERTED_SCRIPT(SaffronCityFisherScript);
    CONVERTED_SCRIPT(SaffronCityYoungster1Script);
    CONVERTED_SCRIPT(SaffronCityYoungster2Script);
    CONVERTED_SCRIPT(SaffronCityLass2Script);

    // maps/FuchsiaCity.c
    CONVERTED_SCRIPT(FuchsiaCityYoungster);
    CONVERTED_SCRIPT(FuchsiaCityPokefanM);
    CONVERTED_SCRIPT(FuchsiaCityTeacher);
    CONVERTED_SCRIPT(FuchsiaCityFruitTree);

    // maps/CinnabarIsland.c
    CONVERTED_SCRIPT(CinnabarIslandBlue);

    // maps/Route1.c
    CONVERTED_SCRIPT(TrainerSchoolboyDanny);
    CONVERTED_SCRIPT(TrainerCooltrainerfQuinn);
    CONVERTED_SCRIPT(Route1FruitTree);

    // maps/Route2.c
    CONVERTED_SCRIPT(TrainerBugCatcherRob);
    CONVERTED_SCRIPT(TrainerBugCatcherEd);
    CONVERTED_SCRIPT(TrainerBugCatcherDoug);
    CONVERTED_SCRIPT(Route2DireHit);
    CONVERTED_SCRIPT(Route2MaxPotion);
    CONVERTED_SCRIPT(Route2Carbos);
    CONVERTED_SCRIPT(Route2Elixer);
    CONVERTED_SCRIPT(Route2FruitTree);

    // maps/Route3.c
    CONVERTED_SCRIPT(TrainerFirebreatherOtis);
    CONVERTED_SCRIPT(TrainerYoungsterWarren);
    CONVERTED_SCRIPT(TrainerYoungsterJimmy);
    CONVERTED_SCRIPT(TrainerFirebreatherBurt);

    // maps/Route4.c
    CONVERTED_SCRIPT(TrainerBirdKeeperHank);
    CONVERTED_SCRIPT(TrainerPicnickerHope);
    CONVERTED_SCRIPT(TrainerPicnickerSharon);
    CONVERTED_SCRIPT(Route4HPUp);

    // maps/Route5.c
    CONVERTED_SCRIPT(Route5PokefanMScript);

    // maps/Route6.c
    CONVERTED_SCRIPT(Route6PokefanMScript);
    CONVERTED_SCRIPT(TrainerPokefanmRex);
    CONVERTED_SCRIPT(TrainerPokefanmAllan);

    // maps/Route7.c

    // maps/Route8.c
    CONVERTED_SCRIPT(TrainerBikerDwayne);
    CONVERTED_SCRIPT(TrainerBikerHarris);
    CONVERTED_SCRIPT(TrainerBikerZeke);
    CONVERTED_SCRIPT(TrainerSupernerdSam);
    CONVERTED_SCRIPT(TrainerSupernerdTom);
    CONVERTED_SCRIPT(Route8FruitTree);

    // maps/Route9.c
    CONVERTED_SCRIPT(TrainerCamperDean);
    CONVERTED_SCRIPT(TrainerPicnickerHeidi);
    CONVERTED_SCRIPT(TrainerCamperSid);
    CONVERTED_SCRIPT(TrainerPicnickerEdna);
    CONVERTED_SCRIPT(TrainerHikerTim);
    CONVERTED_SCRIPT(TrainerHikerSidney);

    // maps/Route10North.c

    // maps/Route10South.c
    CONVERTED_SCRIPT(TrainerHikerJim);
    CONVERTED_SCRIPT(TrainerPokefanmRobert);

    // maps/Route11.c
    CONVERTED_SCRIPT(TrainerYoungsterOwen);
    CONVERTED_SCRIPT(TrainerYoungsterJason);
    CONVERTED_SCRIPT(TrainerPsychicHerman);
    CONVERTED_SCRIPT(TrainerPsychicFidel);
    CONVERTED_SCRIPT(Route11FruitTree);

    // maps/Route12.c
    CONVERTED_SCRIPT(TrainerFisherMartin);
    CONVERTED_SCRIPT(TrainerFisherStephen);
    CONVERTED_SCRIPT(TrainerFisherBarney);
    CONVERTED_SCRIPT(TrainerFisherKyle);
    CONVERTED_SCRIPT(Route12Calcium);
    CONVERTED_SCRIPT(Route12Nugget);

    // maps/Route13.c
    CONVERTED_SCRIPT(TrainerBirdKeeperPerry);
    CONVERTED_SCRIPT(TrainerBirdKeeperBret);
    CONVERTED_SCRIPT(TrainerPokefanmJoshua);
    CONVERTED_SCRIPT(TrainerHikerKenny);
    CONVERTED_SCRIPT(TrainerPokefanmAlex);

    // maps/Route14.c
    CONVERTED_SCRIPT(TrainerPokefanmCarter);
    CONVERTED_SCRIPT(TrainerBirdKeeperRoy);
    CONVERTED_SCRIPT(TrainerPokefanmTrevor);
    CONVERTED_SCRIPT(Kim);

    // maps/Route15.c
    CONVERTED_SCRIPT(TrainerSchoolboyKipp);
    CONVERTED_SCRIPT(TrainerSchoolboyTommy);
    CONVERTED_SCRIPT(TrainerSchoolboyJohnny);
    CONVERTED_SCRIPT(TrainerSchoolboyBilly);
    CONVERTED_SCRIPT(TrainerTeacherColette);
    CONVERTED_SCRIPT(TrainerTeacherHillary);
    CONVERTED_SCRIPT(Route15PPUp);

    // maps/Route16.c

    // maps/Route17.c
    CONVERTED_SCRIPT(TrainerBikerRiley);
    CONVERTED_SCRIPT(TrainerBikerJoel);
    CONVERTED_SCRIPT(TrainerBikerGlenn);
    CONVERTED_SCRIPT(TrainerBikerCharles);

    // maps/Route18.c
    CONVERTED_SCRIPT(TrainerBirdKeeperBoris);
    CONVERTED_SCRIPT(TrainerBirdKeeperBob);

    // maps/Route19.c
    CONVERTED_SCRIPT(TrainerSwimmerfDawn);
    CONVERTED_SCRIPT(TrainerSwimmermHarold);
    CONVERTED_SCRIPT(TrainerSwimmermJerome);
    CONVERTED_SCRIPT(TrainerSwimmermTucker);
    CONVERTED_SCRIPT(Route19Fisher1Script);
    CONVERTED_SCRIPT(Route19Fisher2Script);

    // maps/Route20.c
    CONVERTED_SCRIPT(TrainerSwimmerfNicole);
    CONVERTED_SCRIPT(TrainerSwimmerfLori);
    CONVERTED_SCRIPT(TrainerSwimmermCameron);

    // maps/Route21.c
    CONVERTED_SCRIPT(TrainerSwimmerfNikki);
    CONVERTED_SCRIPT(TrainerSwimmermSeth);
    CONVERTED_SCRIPT(TrainerFisherArnold);

    // maps/Route22.c

    // maps/Route23.c

    // maps/Route24.c
    CONVERTED_SCRIPT(Route24RocketScript);

    // maps/Route25.c
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(TrainerSchoolboyDudley);
    CONVERTED_SCRIPT(TrainerLassEllen);
    CONVERTED_SCRIPT(TrainerSchoolboyJoe);
    CONVERTED_SCRIPT(TrainerLassLaura);
    CONVERTED_SCRIPT(TrainerCamperLloyd);
    CONVERTED_SCRIPT(TrainerLassShannon);
    CONVERTED_SCRIPT(TrainerSupernerdPat);
    CONVERTED_SCRIPT(TrainerCooltrainermKevin);
    CONVERTED_SCRIPT(Route25Protein);

    // maps/Route26.c
    CONVERTED_SCRIPT(TrainerCooltrainermJake);
    CONVERTED_SCRIPT(TrainerCooltrainermGaven3);
    CONVERTED_SCRIPT(TrainerCooltrainerfJoyce);
    CONVERTED_SCRIPT(TrainerCooltrainerfBeth1);
    CONVERTED_SCRIPT(TrainerPsychicRichard);
    CONVERTED_SCRIPT(TrainerFisherScott);
    CONVERTED_SCRIPT(Route26FruitTree);
    CONVERTED_SCRIPT(Route26MaxElixer);

    // maps/Route27.c
    CONVERTED_SCRIPT(TrainerCooltrainermBlake);
    CONVERTED_SCRIPT(TrainerCooltrainermBrian);
    CONVERTED_SCRIPT(TrainerCooltrainerfReena);
    CONVERTED_SCRIPT(TrainerCooltrainerfMegan);
    CONVERTED_SCRIPT(TrainerPsychicGilbert);
    CONVERTED_SCRIPT(TrainerBirdKeeperJose2);
    CONVERTED_SCRIPT(Route27TMSolarbeam);
    CONVERTED_SCRIPT(Route27RareCandy);
    CONVERTED_SCRIPT(Route27FisherScript);

    // maps/Route28.c

    // maps/Route29.c
    CONVERTED_SCRIPT(Route29Tutorial1);
    CONVERTED_SCRIPT(Route29Tutorial2);
    CONVERTED_SCRIPT(Script_RefusedTutorial1);
    CONVERTED_SCRIPT(Script_RefusedTutorial2);
    CONVERTED_SCRIPT(CatchingTutorialDudeScript);
    CONVERTED_SCRIPT(Route29YoungsterScript);
    CONVERTED_SCRIPT(Route29TeacherScript);
    CONVERTED_SCRIPT(Route29FisherScript);
    CONVERTED_SCRIPT(Route29CooltrainerMScript);
    CONVERTED_SCRIPT(TuscanyScript);
    CONVERTED_SCRIPT(TuscanyTuesdayScript);
    CONVERTED_SCRIPT(TuscanyDoneScript);
    CONVERTED_SCRIPT(TuscanyNotTuesdayScript);
    CONVERTED_SCRIPT(Route29Sign1);
    CONVERTED_SCRIPT(Route29Sign2);
    CONVERTED_SCRIPT(Route29FruitTree);

    // maps/Route30.c
    CONVERTED_SCRIPT(YoungsterJoey_ImportantBattleScript);
    CONVERTED_SCRIPT(TrainerYoungsterJoey);
    CONVERTED_SCRIPT(TrainerYoungsterMikey);
    CONVERTED_SCRIPT(TrainerBugCatcherDon);
    CONVERTED_SCRIPT(Route30YoungsterScript);
    CONVERTED_SCRIPT(Route30FruitTree1);
    CONVERTED_SCRIPT(Route30FruitTree2);
    CONVERTED_SCRIPT(Route30CooltrainerFScript);
    CONVERTED_SCRIPT(Route30Antidote);

    // maps/Route31.c
    CONVERTED_SCRIPT(Route31MailRecipientScript);
    CONVERTED_SCRIPT(Route31YoungsterScript);
    CONVERTED_SCRIPT(TrainerBugCatcherWade1);
    CONVERTED_SCRIPT(Route31CooltrainerMScript);
    CONVERTED_SCRIPT(Route31FruitTree);
    CONVERTED_SCRIPT(Route31Potion);
    CONVERTED_SCRIPT(Route31PokeBall);

    // maps/Route32.c
    CONVERTED_SCRIPT(TrainerFisherJustin);
    CONVERTED_SCRIPT(TrainerFisherRalph1);
    CONVERTED_SCRIPT(TrainerFisherHenry);
    CONVERTED_SCRIPT(TrainerYoungsterAlbert);
    CONVERTED_SCRIPT(TrainerYoungsterGordon);
    CONVERTED_SCRIPT(TrainerCamperRoland);
    CONVERTED_SCRIPT(TrainerPicnickerLiz1);
    CONVERTED_SCRIPT(Route32CooltrainerMScript);
    CONVERTED_SCRIPT(TrainerBirdKeeperPeter);
    CONVERTED_SCRIPT(SlowpokeTailSalesmanScript);
    CONVERTED_SCRIPT(Route32GreatBall);
    CONVERTED_SCRIPT(Route32RoarTMGuyScript);
    CONVERTED_SCRIPT(FriedaScript);
    CONVERTED_SCRIPT(Route32Repel);

    // maps/Route33.c
    CONVERTED_SCRIPT(TrainerHikerAnthony);
    CONVERTED_SCRIPT(Route33LassScript);
    CONVERTED_SCRIPT(Route33FruitTree);

    // maps/Route34.c
    CONVERTED_SCRIPT(TrainerCamperTodd1);
    CONVERTED_SCRIPT(TrainerYoungsterSamuel);
    CONVERTED_SCRIPT(TrainerYoungsterIan);
    CONVERTED_SCRIPT(TrainerPicnickerGina1);
    CONVERTED_SCRIPT(OfficerKeithScript);
    CONVERTED_SCRIPT(TrainerPokefanmBrandon);
    CONVERTED_SCRIPT(DayCareManScript_Outside);
    CONVERTED_SCRIPT(DayCareMon1Script);
    CONVERTED_SCRIPT(DayCareMon2Script);
    CONVERTED_SCRIPT(TrainerCooltrainerfIrene);
    CONVERTED_SCRIPT(TrainerCooltrainerfJenn);
    CONVERTED_SCRIPT(TrainerCooltrainerfKate);
    CONVERTED_SCRIPT(Route34Nugget);

    // maps/Route35.c
    CONVERTED_SCRIPT(TrainerCamperIvan);
    CONVERTED_SCRIPT(TrainerCamperElliot);
    CONVERTED_SCRIPT(TrainerPicnickerBrooke);
    CONVERTED_SCRIPT(TrainerPicnickerKim);
    CONVERTED_SCRIPT(TrainerBirdKeeperBryan);
    CONVERTED_SCRIPT(TrainerFirebreatherWalt);
    CONVERTED_SCRIPT(TrainerBugCatcherArnie);
    CONVERTED_SCRIPT(TrainerJugglerIrwin);
    CONVERTED_SCRIPT(TrainerOfficerDirk);
    CONVERTED_SCRIPT(Route35FruitTree);
    CONVERTED_SCRIPT(Route35TMRollout);

    // maps/Route36.c
    CONVERTED_SCRIPT(TrainerPsychicMark);
    CONVERTED_SCRIPT(TrainerSchoolboyAlan1);
    CONVERTED_SCRIPT(SudowoodoScript);
    CONVERTED_SCRIPT(Route36LassScript);
    CONVERTED_SCRIPT(Route36RockSmashGuyScript);
    CONVERTED_SCRIPT(Route36FruitTree);
    CONVERTED_SCRIPT(ArthurScript);
    CONVERTED_SCRIPT(Route36FloriaScript);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/Route37.c
    CONVERTED_SCRIPT(TrainerTwinsAnnandanne1);
    CONVERTED_SCRIPT(TrainerTwinsAnnandanne2);
    CONVERTED_SCRIPT(TrainerPsychicGreg);
    CONVERTED_SCRIPT(Route37FruitTree1);
    CONVERTED_SCRIPT(SunnyScript);
    CONVERTED_SCRIPT(Route37FruitTree2);
    CONVERTED_SCRIPT(Route37FruitTree3);

    // maps/Route38.c
    CONVERTED_SCRIPT(TrainerSchoolboyChad1);
    CONVERTED_SCRIPT(TrainerLassDana1);
    CONVERTED_SCRIPT(TrainerBirdKeeperToby);
    CONVERTED_SCRIPT(TrainerBeautyValerie);
    CONVERTED_SCRIPT(TrainerSailorHarry);
    CONVERTED_SCRIPT(Route38FruitTree);
    CONVERTED_SCRIPT(TrainerBeautyOlivia);

    // maps/Route39.c
    CONVERTED_SCRIPT(TrainerSailorEugene);
    CONVERTED_SCRIPT(TrainerPokefanmDerek);
    CONVERTED_SCRIPT(TrainerPokefanfRuth);
    CONVERTED_SCRIPT(Route39Miltank);
    // CONVERTED_SCRIPT(Route39Miltank);
    // CONVERTED_SCRIPT(Route39Miltank);
    // CONVERTED_SCRIPT(Route39Miltank);
    CONVERTED_SCRIPT(TrainerPsychicNorman);
    CONVERTED_SCRIPT(Route39FruitTree);
    CONVERTED_SCRIPT(TrainerPokefanfJaime);

    // maps/Route40.c
    CONVERTED_SCRIPT(TrainerSwimmermSimon);
    CONVERTED_SCRIPT(TrainerSwimmermRandall);
    CONVERTED_SCRIPT(TrainerSwimmerfElaine);
    CONVERTED_SCRIPT(TrainerSwimmerfPaula);
    CONVERTED_SCRIPT(Route40Rock);
    // CONVERTED_SCRIPT(Route40Rock);
    // CONVERTED_SCRIPT(Route40Rock);
    CONVERTED_SCRIPT(Route40Lass1Script);
    CONVERTED_SCRIPT(MonicaScript);
    CONVERTED_SCRIPT(Route40PokefanMScript);
    CONVERTED_SCRIPT(Route40Lass2Script);
    CONVERTED_SCRIPT(Route40StandingYoungsterScript);

    // maps/Route41.c
    CONVERTED_SCRIPT(TrainerSwimmermCharlie);
    CONVERTED_SCRIPT(TrainerSwimmermGeorge);
    CONVERTED_SCRIPT(TrainerSwimmermBerke);
    CONVERTED_SCRIPT(TrainerSwimmermKirk);
    CONVERTED_SCRIPT(TrainerSwimmermMathew);
    CONVERTED_SCRIPT(TrainerSwimmerfKaylee);
    CONVERTED_SCRIPT(TrainerSwimmerfSusie);
    CONVERTED_SCRIPT(TrainerSwimmerfDenise);
    CONVERTED_SCRIPT(TrainerSwimmerfKara);
    CONVERTED_SCRIPT(TrainerSwimmerfWendy);

    // maps/Route42.c
    CONVERTED_SCRIPT(TrainerFisherTully);
    CONVERTED_SCRIPT(TrainerHikerBenjamin);
    CONVERTED_SCRIPT(TrainerPokemaniacShane);
    CONVERTED_SCRIPT(Route42FruitTree1);
    CONVERTED_SCRIPT(Route42FruitTree2);
    CONVERTED_SCRIPT(Route42FruitTree3);
    CONVERTED_SCRIPT(Route42UltraBall);
    CONVERTED_SCRIPT(Route42SuperPotion);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/Route43.c
    CONVERTED_SCRIPT(TrainerPokemaniacBen);
    CONVERTED_SCRIPT(TrainerPokemaniacBrent);
    CONVERTED_SCRIPT(TrainerPokemaniacRon);
    CONVERTED_SCRIPT(TrainerFisherMarvin);
    CONVERTED_SCRIPT(TrainerPicnickerTiffany);
    CONVERTED_SCRIPT(TrainerCamperSpencer);
    CONVERTED_SCRIPT(Route43FruitTree);
    CONVERTED_SCRIPT(Route43MaxEther);

    // maps/Route44.c
    CONVERTED_SCRIPT(TrainerFisherWilton1);
    CONVERTED_SCRIPT(TrainerFisherEdgar);
    CONVERTED_SCRIPT(TrainerPsychicPhil);
    CONVERTED_SCRIPT(TrainerPokemaniacZach);
    CONVERTED_SCRIPT(TrainerBirdKeeperVance1);
    CONVERTED_SCRIPT(TrainerCooltrainermAllen);
    CONVERTED_SCRIPT(TrainerCooltrainerfCybil);
    CONVERTED_SCRIPT(Route44FruitTree);
    CONVERTED_SCRIPT(Route44MaxRevive);
    CONVERTED_SCRIPT(Route44UltraBall);
    CONVERTED_SCRIPT(Route44MaxRepel);

    // maps/Route45.c
    CONVERTED_SCRIPT(TrainerHikerErik);
    CONVERTED_SCRIPT(TrainerHikerMichael);
    CONVERTED_SCRIPT(TrainerHikerParry);
    CONVERTED_SCRIPT(TrainerHikerTimothy);
    CONVERTED_SCRIPT(TrainerBlackbeltKenji);
    CONVERTED_SCRIPT(TrainerCooltrainermRyan);
    CONVERTED_SCRIPT(TrainerCooltrainerfKelly);
    CONVERTED_SCRIPT(Route45FruitTree);
    CONVERTED_SCRIPT(Route45Nugget);
    CONVERTED_SCRIPT(Route45Revive);
    CONVERTED_SCRIPT(Route45Elixer);
    CONVERTED_SCRIPT(Route45MaxPotion);
    CONVERTED_SCRIPT(TrainerCamperQuentin);

    // maps/Route46.c
    CONVERTED_SCRIPT(TrainerHikerBailey);
    CONVERTED_SCRIPT(TrainerCamperTed);
    CONVERTED_SCRIPT(TrainerPicnickerErin1);
    CONVERTED_SCRIPT(Route46FruitTree1);
    CONVERTED_SCRIPT(Route46FruitTree2);
    CONVERTED_SCRIPT(Route46XSpeed);

    // maps/Route2Gate.c
    CONVERTED_SCRIPT(Route2GateScientistScript);

    // maps/Route2NuggetHouse.c
    CONVERTED_SCRIPT(Route2NuggetHouseFisherScript);

    // maps/Route5UndergroundPathEntrance.c
    CONVERTED_SCRIPT(Route5UndergroundPathEntranceTeacherScript);

    // maps/Route5CleanseTagHouse.c
    CONVERTED_SCRIPT(Route5CleanseTagHouseGrannyScript);
    CONVERTED_SCRIPT(Route5CleanseTagHouseTeacherScript);

    // maps/Route5SaffronGate.c
    CONVERTED_SCRIPT(Route5SaffronGateOfficerScript);

    // maps/Route6UndergroundPathEntrance.c

    // maps/Route6SaffronGate.c
    CONVERTED_SCRIPT(Route6SaffronGuardScript);

    // maps/Route7SaffronGate.c
    CONVERTED_SCRIPT(Route7SaffronGuardScript);

    // maps/Route8SaffronGate.c
    CONVERTED_SCRIPT(Route8SaffronGateOfficerScript);

    // maps/Route10Pokecenter1F.c
    CONVERTED_SCRIPT(Route10Pokecenter1FNurseScript);
    CONVERTED_SCRIPT(Route10Pokecenter1FGentlemanScript);
    CONVERTED_SCRIPT(Route10Pokecenter1FGymGuideScript);
    CONVERTED_SCRIPT(Route10Pokecenter1FCooltrainerFScript);

    // maps/Route12SuperRodHouse.c
    CONVERTED_SCRIPT(Route12SuperRodHouseFishingGuruScript);

    // maps/Route15FuchsiaGate.c
    CONVERTED_SCRIPT(Route15FuchsiaGateOfficerScript);

    // maps/Route16Gate.c
    CONVERTED_SCRIPT(Route16GateOfficerScript);

    // maps/Route16FuchsiaSpeechHouse.c
    CONVERTED_SCRIPT(Route16FuchsiaSpeechHouseSuperNerdScript);

    // maps/Route17Route18Gate.c
    CONVERTED_SCRIPT(Route17Route18GateOfficerScript);

    // maps/Route19FuchsiaGate.c
    CONVERTED_SCRIPT(Route19FuchsiaGateOfficerScript);

    // maps/Route26HealHouse.c
    CONVERTED_SCRIPT(Route26HealHouseTeacherScript);

    // maps/Route27SandstormHouse.c
    CONVERTED_SCRIPT(SandstormHouseWoman);

    // maps/Route28SteelWingHouse.c
    CONVERTED_SCRIPT(Celebrity);
    CONVERTED_SCRIPT(CelebritysFearow);

    // maps/Route29Route46Gate.c
    CONVERTED_SCRIPT(Route29Route46GateOfficerScript);
    CONVERTED_SCRIPT(Route29Route46GateYoungsterScript);

    // maps/Route30BerryHouse.c
    CONVERTED_SCRIPT(Route30BerryHousePokefanMScript);

    // maps/Route31VioletGate.c
    CONVERTED_SCRIPT(Route31VioletGateOfficerScript);
    CONVERTED_SCRIPT(Route31VioletGateCooltrainerFScript);

    // maps/Route32RuinsOfAlphGate.c
    CONVERTED_SCRIPT(Route32RuinsOfAlphGateOfficerScript);
    CONVERTED_SCRIPT(Route32RuinsOfAlphGatePokefanMScript);
    CONVERTED_SCRIPT(Route32RuinsOfAlphGateYoungsterScript);

    // maps/Route32Pokecenter1F.c
    CONVERTED_SCRIPT(Route32Pokecenter1FNurseScript);
    CONVERTED_SCRIPT(Route32Pokecenter1FFishingGuruScript);
    CONVERTED_SCRIPT(Route32Pokecenter1FCooltrainerFScript);

    // maps/DayCare.c
    CONVERTED_SCRIPT(DayCareManScript_Inside);
    CONVERTED_SCRIPT(DayCareLadyScript);

    // maps/Route35GoldenrodGate.c
    CONVERTED_SCRIPT(RandyScript);
    CONVERTED_SCRIPT(Route35GoldenrodGatePokefanFScript);
    CONVERTED_SCRIPT(Route35GoldenrodGateFisherScript);

    // maps/Route35NationalParkGate.c
    CONVERTED_SCRIPT(Route35OfficerScriptContest);
    CONVERTED_SCRIPT(Route35NationalParkGateYoungsterScript);
    CONVERTED_SCRIPT(Route35NationalParkGateOfficerScript);

    // maps/Route36NationalParkGate.c
    CONVERTED_SCRIPT(Route36OfficerScriptContest);
    CONVERTED_SCRIPT(BugCatchingContestant1BScript);
    CONVERTED_SCRIPT(BugCatchingContestant2BScript);
    CONVERTED_SCRIPT(BugCatchingContestant3BScript);
    CONVERTED_SCRIPT(BugCatchingContestant4BScript);
    CONVERTED_SCRIPT(BugCatchingContestant5BScript);
    CONVERTED_SCRIPT(BugCatchingContestant6BScript);
    CONVERTED_SCRIPT(BugCatchingContestant7BScript);
    CONVERTED_SCRIPT(BugCatchingContestant8BScript);
    CONVERTED_SCRIPT(BugCatchingContestant9BScript);
    CONVERTED_SCRIPT(BugCatchingContestant10BScript);
    CONVERTED_SCRIPT(Route36NationalParkGateOfficerScript);

    // maps/Route36RuinsOfAlphGate.c
    CONVERTED_SCRIPT(Route36RuinsOfAlphGateOfficerScript);
    CONVERTED_SCRIPT(Route36RuinsOfAlphGateGrampsScript);

    // maps/Route38EcruteakGate.c
    CONVERTED_SCRIPT(Route38EcruteakGateOfficerScript);

    // maps/Route39Barn.c
    CONVERTED_SCRIPT(Route39BarnTwin1Script);
    CONVERTED_SCRIPT(Route39BarnTwin2Script);
    CONVERTED_SCRIPT(MoomooScript);

    // maps/Route39Farmhouse.c
    CONVERTED_SCRIPT(PokefanM_DairyFarmer);
    CONVERTED_SCRIPT(PokefanF_SnoreFarmer);

    // maps/Route40BattleTowerGate.c
    CONVERTED_SCRIPT(Route40BattleTowerGateRockerScript);
    CONVERTED_SCRIPT(Route40BattleTowerGateTwinScript);

    // maps/Route42EcruteakGate.c
    CONVERTED_SCRIPT(Route42EcruteakGateOfficerScript);

    // maps/Route43MahoganyGate.c
    CONVERTED_SCRIPT(Route43MahoganyGateOfficer);

    // maps/Route43Gate.c
    CONVERTED_SCRIPT(OfficerScript_GuardWithSludgeBomb);
    CONVERTED_SCRIPT(RocketScript_MakingABundle);
    CONVERTED_SCRIPT(RocketScript_MakingABundle);

    // maps/CherrygroveEvolutionSpeechHouse.c
    CONVERTED_SCRIPT(CherrygroveEvolutionSpeechHouseLassScript);
    CONVERTED_SCRIPT(CherrygroveEvolutionSpeechHouseYoungsterScript);

    // maps/CherrygroveGymSpeechHouse.c
    CONVERTED_SCRIPT(CherrygroveGymSpeechHousePokefanMScript);
    CONVERTED_SCRIPT(CherrygroveGymSpeechHouseBugCatcherScript);

    // maps/CherrygrovePokecenter1F.c
    CONVERTED_SCRIPT(CherrygrovePokecenter1FNurseScript);
    CONVERTED_SCRIPT(CherrygrovePokecenter1FFisherScript);
    CONVERTED_SCRIPT(CherrygrovePokecenter1FGentlemanScript);
    CONVERTED_SCRIPT(CherrygrovePokecenter1FTeacherScript);

    // maps/CherrygroveMart.c
    CONVERTED_SCRIPT(CherrygroveMartClerkScript);
    CONVERTED_SCRIPT(CherrygroveMartCooltrainerMScript);
    CONVERTED_SCRIPT(CherrygroveMartYoungsterScript);

    // maps/GuideGentsHouse.c
    CONVERTED_SCRIPT(GuideGentsHouseGuideGent);

    // maps/Pokecenter2F.c
    CONVERTED_SCRIPT(LinkReceptionistScript_Trade);
    CONVERTED_SCRIPT(LinkReceptionistScript_Battle);
    CONVERTED_SCRIPT(LinkReceptionistScript_TimeCapsule);
    CONVERTED_SCRIPT(Pokecenter2FOfficerScript);

    // maps/MrPokemonsHouse.c
    CONVERTED_SCRIPT(MrPokemonsHouse_MrPokemonScript);

    // maps/PlayersNeighborsHouse.c
    CONVERTED_SCRIPT(PlayersNeighborsDaughterScript);
    CONVERTED_SCRIPT(PlayersNeighborScript);

    // maps/ElmsLab.c
    CONVERTED_SCRIPT(ProfElmScript);
    CONVERTED_SCRIPT(ElmsAideScript);
    CONVERTED_SCRIPT(CyndaquilPokeBallScript);
    CONVERTED_SCRIPT(TotodilePokeBallScript);
    CONVERTED_SCRIPT(ChikoritaPokeBallScript);
    CONVERTED_SCRIPT(CopScript);

    // maps/ElmsHouse.c
    CONVERTED_SCRIPT(ElmsWife);
    CONVERTED_SCRIPT(ElmsSon);

    // maps/PlayersHouse2F.c
    CONVERTED_SCRIPT(PlayersHouseGameConsoleScript);
    CONVERTED_SCRIPT(PlayersHouseDoll1Script);
    CONVERTED_SCRIPT(PlayersHouseDoll2Script);
    CONVERTED_SCRIPT(PlayersHouseBigDollScript);

    // maps/PlayersHouse1F.c
    CONVERTED_SCRIPT(MomScript);
    CONVERTED_SCRIPT(NeighborScript);

    // maps/VioletPokecenter1F.c
    CONVERTED_SCRIPT(VioletPokecenterNurse);
    CONVERTED_SCRIPT(VioletPokecenter1FGameboyKidScript);
    CONVERTED_SCRIPT(VioletPokecenter1FGentlemanScript);
    CONVERTED_SCRIPT(VioletPokecenter1FYoungsterScript);
    CONVERTED_SCRIPT(VioletPokecenter1F_ElmsAideScript);

    // maps/VioletMart.c
    CONVERTED_SCRIPT(VioletMartClerkScript);
    CONVERTED_SCRIPT(VioletMartGrannyScript);
    CONVERTED_SCRIPT(VioletMartCooltrainerMScript);

    // maps/VioletKylesHouse.c
    CONVERTED_SCRIPT(VioletKylesHousePokefanMScript);
    CONVERTED_SCRIPT(Kyle);

    // maps/EarlsPokemonAcedemy.c
    CONVERTED_SCRIPT(AcademyEarl);
    CONVERTED_SCRIPT(EarlsPokemonAcademyYoungster1Script);
    CONVERTED_SCRIPT(EarlsPokemonAcademyGameboyKid1Script);
    CONVERTED_SCRIPT(EarlsPokemonAcademyGameboyKid2Script);
    CONVERTED_SCRIPT(EarlsPokemonAcademyYoungster2Script);
    CONVERTED_SCRIPT(AcademyNotebook);

    // maps/VioletGym.c
    CONVERTED_SCRIPT(VioletGymFalknerScript);
    CONVERTED_SCRIPT(TrainerBirdKeeperRod);
    CONVERTED_SCRIPT(TrainerBirdKeeperAbe);
    CONVERTED_SCRIPT(VioletGymGuideScript);

    // maps/AzaleaPokecenter1F.c
    CONVERTED_SCRIPT(AzaleaPokecenter1FNurseScript);
    CONVERTED_SCRIPT(AzaleaPokecenter1FGentlemanScript);
    CONVERTED_SCRIPT(AzaleaPokecenter1FFishingGuruScript);
    CONVERTED_SCRIPT(AzaleaPokecenter1FPokefanFScript);

    // maps/AzaleaMart.c
    CONVERTED_SCRIPT(AzaleaMartClerkScript);
    CONVERTED_SCRIPT(AzaleaMartCooltrainerMScript);
    CONVERTED_SCRIPT(AzaleaMartBugCatcherScript);

    // maps/AzaleaGym.c
    CONVERTED_SCRIPT(AzaleaGymBugsyScript);
    CONVERTED_SCRIPT(TrainerBugCatcherBenny);
    CONVERTED_SCRIPT(TrainerBugCatcherAl);
    CONVERTED_SCRIPT(TrainerBugCatcherJosh);
    CONVERTED_SCRIPT(TrainerTwinsAmyandmay1);
    CONVERTED_SCRIPT(TrainerTwinsAmyandmay2);
    CONVERTED_SCRIPT(AzaleaGymGuideScript);

    // maps/KurtsHouse.c
    CONVERTED_SCRIPT(Kurt1);
    CONVERTED_SCRIPT(KurtsGranddaughter1);
    CONVERTED_SCRIPT(KurtsHouseSlowpoke);
    CONVERTED_SCRIPT(Kurt2);
    CONVERTED_SCRIPT(KurtsGranddaughter2);

    // maps/CharcoalKiln.c
    CONVERTED_SCRIPT(CharcoalKilnBoss);
    CONVERTED_SCRIPT(CharcoalKilnApprentice);
    CONVERTED_SCRIPT(CharcoalKilnFarfetchd);

    // maps/GoldenrodBikeShop.c
    CONVERTED_SCRIPT(GoldenrodBikeShopClerkScript);

    // maps/GoldenrodFlowerShop.c
    CONVERTED_SCRIPT(FlowerShopTeacherScript);
    CONVERTED_SCRIPT(FlowerShopFloriaScript);

    // maps/GoldenrodHappinessRater.c
    CONVERTED_SCRIPT(GoldenrodHappinessRaterTeacherScript);
    CONVERTED_SCRIPT(GoldenrodHappinessRaterPokefanMScript);
    CONVERTED_SCRIPT(GoldenrodHappinessRaterTwinScript);

    // maps/GoldenrodMagnetTrainStation.c
    CONVERTED_SCRIPT(GoldenrodMagnetTrainStationOfficerScript);
    CONVERTED_SCRIPT(GoldenrodMagnetTrainStationGentlemanScript);

    // maps/GoldenrodNameRater.c
    CONVERTED_SCRIPT(GoldenrodNameRater);

    // maps/GoldenrodPPSpeechHouse.c
    CONVERTED_SCRIPT(GoldenrodPPSpeechHouseFisherScript);
    CONVERTED_SCRIPT(GoldenrodPPSpeechHouseLassScript);

    // maps/BillsFamilysHouse.c
    CONVERTED_SCRIPT(BillScript);
    CONVERTED_SCRIPT(BillsMomScript);
    CONVERTED_SCRIPT(BillsSisterScript);

    // maps/GoldenrodGameCorner.c
    CONVERTED_SCRIPT(GoldenrodGameCornerCoinVendorScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerTMVendorScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerPrizeMonVendorScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerPharmacistScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerPharmacistScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerPokefanM1Script);
    CONVERTED_SCRIPT(GoldenrodGameCornerCooltrainerMScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerPokefanFScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerCooltrainerFScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerGentlemanScript);
    CONVERTED_SCRIPT(GoldenrodGameCornerPokefanM2Script);
    CONVERTED_SCRIPT(MoveTutorInsideScript);

    // maps/GoldenrodGym.c
    CONVERTED_SCRIPT(GoldenrodGymWhitneyScript);
    CONVERTED_SCRIPT(TrainerLassCarrie);
    CONVERTED_SCRIPT(TrainerLassBridget);
    CONVERTED_SCRIPT(TrainerBeautyVictoria);
    CONVERTED_SCRIPT(TrainerBeautySamantha);
    CONVERTED_SCRIPT(GoldenrodGymGuideScript);

    // maps/GoldenrodUnderground.c
    CONVERTED_SCRIPT(TrainerSupernerdEric);
    CONVERTED_SCRIPT(TrainerSupernerdTeru);
    CONVERTED_SCRIPT(TrainerPokemaniacIssac);
    CONVERTED_SCRIPT(TrainerPokemaniacDonald);
    CONVERTED_SCRIPT(GoldenrodUndergroundCoinCase);
    CONVERTED_SCRIPT(BargainMerchantScript);
    CONVERTED_SCRIPT(OlderHaircutBrotherScript);
    CONVERTED_SCRIPT(YoungerHaircutBrotherScript);
    CONVERTED_SCRIPT(BitterMerchantScript);

    // maps/GoldenrodUndergroundSwitchRoomEntrances.c
    CONVERTED_SCRIPT(TrainerBurglarDuncan);
    CONVERTED_SCRIPT(TrainerBurglarEddie);
    CONVERTED_SCRIPT(TrainerGruntM13);
    CONVERTED_SCRIPT(TrainerGruntM11);
    CONVERTED_SCRIPT(TrainerGruntM25);
    CONVERTED_SCRIPT(TrainerGruntF3);
    CONVERTED_SCRIPT(GoldenrodUndergroundSwitchRoomEntrancesTeacherScript);
    CONVERTED_SCRIPT(GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript);
    CONVERTED_SCRIPT(GoldenrodUndergroundSwitchRoomEntrancesSmokeBall);
    CONVERTED_SCRIPT(GoldenrodUndergroundSwitchRoomEntrancesFullHeal);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/GoldenrodUndergroundWarehouse.c
    CONVERTED_SCRIPT(TrainerGruntM24);
    CONVERTED_SCRIPT(TrainerGruntM14);
    CONVERTED_SCRIPT(TrainerGruntM15);
    CONVERTED_SCRIPT(GoldenrodUndergroundWarehouseDirectorScript);
    CONVERTED_SCRIPT(GoldenrodUndergroundWarehouseMaxEther);
    CONVERTED_SCRIPT(GoldenrodUndergroundWarehouseTMSleepTalk);
    CONVERTED_SCRIPT(GoldenrodUndergroundWarehouseUltraBall);

    // maps/GoldenrodDeptStore1F.c
    CONVERTED_SCRIPT(GoldenrodDeptStore1FReceptionistScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore1FPokefanFScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore1FBugCatcherScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore1FGentlemanScript);

    // maps/GoldenrodDeptStore2F.c
    CONVERTED_SCRIPT(GoldenrodDeptStore2FClerk1Script);
    CONVERTED_SCRIPT(GoldenrodDeptStore2FClerk2Script);
    CONVERTED_SCRIPT(GoldenrodDeptStore2FYoungsterScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore2FCooltrainerFScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore2FGentlemanScript);

    // maps/GoldenrodDeptStore3F.c
    CONVERTED_SCRIPT(GoldenrodDeptStore3FClerkScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore3FSuperNerdScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore3FRockerScript);

    // maps/GoldenrodDeptStore4F.c
    CONVERTED_SCRIPT(GoldenrodDeptStore4FClerkScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore4FCooltrainerMScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore4FBugCatcherScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore4FGameboyKidScript);

    // maps/GoldenrodDeptStore5F.c
    CONVERTED_SCRIPT(GoldenrodDeptStore5FClerkScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore5FLassScript);
    CONVERTED_SCRIPT(Mike);
    CONVERTED_SCRIPT(GoldenrodDeptStore5FPokefanMScript);
    CONVERTED_SCRIPT(Carrie);
    CONVERTED_SCRIPT(GoldenrodDeptStore5FReceptionistScript);

    // maps/GoldenrodDeptStore6F.c
    CONVERTED_SCRIPT(GoldenrodDeptStore6FLassScript);
    CONVERTED_SCRIPT(GoldenrodDeptStore6FSuperNerdScript);

    // maps/GoldenrodDeptStoreB1F.c
    CONVERTED_SCRIPT(GoldenrodDeptStoreB1FEther);
    CONVERTED_SCRIPT(GoldenrodDeptStoreB1FAmuletCoin);
    CONVERTED_SCRIPT(GoldenrodDeptStoreB1FBurnHeal);
    CONVERTED_SCRIPT(GoldenrodDeptStoreB1FUltraBall);
    CONVERTED_SCRIPT(GoldenrodDeptStoreB1FBlackBelt1Script);
    CONVERTED_SCRIPT(GoldenrodDeptStoreB1FBlackBelt2Script);
    CONVERTED_SCRIPT(GoldenrodDeptStoreB1FBlackBelt3Script);
    CONVERTED_SCRIPT(GoldenrodDeptStoreB1FMachopScript);

    // maps/PokecomCenter.c
    CONVERTED_SCRIPT(GoldenrodPokecenter1FNurseScript);
    CONVERTED_SCRIPT2(GoldenrodPokecenter1FTradeCornerAttendantScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball);
    CONVERTED_SCRIPT2(GoldenrodPokecenter1FSuperNerdScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 1);
    CONVERTED_SCRIPT(GoldenrodPokecenter1FGameboyKidScript);
    CONVERTED_SCRIPT(GoldenrodPokecenter1FLassScript);
    CONVERTED_SCRIPT(GoldenrodPokecenter1FPokefanF);
    CONVERTED_SCRIPT2(GoldenrodPokecenter1FLass2Script, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 2);
    CONVERTED_SCRIPT2(GoldenrodPokecenter1FYoungsterScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 3);
    CONVERTED_SCRIPT2(GoldenrodPokecenter1FTeacherScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 4);
    CONVERTED_SCRIPT2(GoldenrodPokecenter1FRockerScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 5);
    CONVERTED_SCRIPT2(GoldenrodPokecenter1FGrampsScript, aGoldenrodPokecenter1F_GSBallSceneLeft_gsball + 6);

    // maps/PokecomCenterAdminOfficeMobile.c
    CONVERTED_SCRIPT(PokecomCenterAdminOfficeMobileScientist1Script);
    CONVERTED_SCRIPT(PokecomCenterAdminOfficeMobileScientist2Script);
    CONVERTED_SCRIPT(PokecomCenterAdminOfficeMobileScientist3Script);

    // maps/EcruteakGym.c
    CONVERTED_SCRIPT(EcruteakGymMortyScript);
    CONVERTED_SCRIPT(TrainerSageJeffrey);
    CONVERTED_SCRIPT(TrainerSagePing);
    CONVERTED_SCRIPT(TrainerMediumMartha);
    CONVERTED_SCRIPT(TrainerMediumGrace);
    CONVERTED_SCRIPT(EcruteakGymGuideScript);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/EcruteakItemfinderHouse.c
    CONVERTED_SCRIPT(EcruteakItemfinderGuy);
    CONVERTED_SCRIPT(EcruteakHistoryBook);

    // maps/EcruteakLugiaSpeechHouse.c
    CONVERTED_SCRIPT(EcruteakLugiaSpeechHouseGrampsScript);
    CONVERTED_SCRIPT(EcruteakLugiaSpeechHouseYoungsterScript);

    // maps/EcruteakMart.c
    CONVERTED_SCRIPT(EcruteakMartClerkScript);
    CONVERTED_SCRIPT(EcruteakMartSuperNerdScript);
    CONVERTED_SCRIPT(EcruteakMartGrannyScript);

    // maps/EcruteakPokecenter1F.c
    CONVERTED_SCRIPT(EcruteakPokecenter1FNurseScript);
    CONVERTED_SCRIPT(EcruteakPokecenter1FPokefanMScript);
    CONVERTED_SCRIPT(EcruteakPokecenter1FCooltrainerFScript);
    CONVERTED_SCRIPT(EcruteakPokecenter1FGymGuideScript);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/EcruteakTinTowerEntrance.c
    CONVERTED_SCRIPT(EcruteakTinTowerEntranceSageScript);
    CONVERTED_SCRIPT(EcruteakTinTowerEntranceSageScript);
    CONVERTED_SCRIPT(EcruteakTinTowerEntranceWanderingSageScript);
    CONVERTED_SCRIPT(EcruteakTinTowerEntranceGrampsScript);

    // maps/DanceTheatre.c
    CONVERTED_SCRIPT(TrainerKimonoGirlNaoko);
    CONVERTED_SCRIPT(TrainerKimonoGirlSayo);
    CONVERTED_SCRIPT(TrainerKimonoGirlZuki);
    CONVERTED_SCRIPT(TrainerKimonoGirlKuni);
    CONVERTED_SCRIPT(TrainerKimonoGirlMiki);
    CONVERTED_SCRIPT(DanceTheaterSurfGuy);
    CONVERTED_SCRIPT(DanceTheaterRhydon);
    CONVERTED_SCRIPT(DanceTheatreCooltrainerMScript);
    CONVERTED_SCRIPT(DanceTheatreGrannyScript);

    // maps/WiseTriosRoom.c
    CONVERTED_SCRIPT(WiseTriosRoomSage1Script);
    CONVERTED_SCRIPT(WiseTriosRoomSage2Script);
    CONVERTED_SCRIPT(WiseTriosRoomSage3Script);
    CONVERTED_SCRIPT(TrainerSageGaku);
    CONVERTED_SCRIPT(TrainerSageMasa);
    CONVERTED_SCRIPT(TrainerSageKoji);

    // maps/OlivineCafe.c
    CONVERTED_SCRIPT(OlivineCafeStrengthSailorScript);
    CONVERTED_SCRIPT(OlivineCafeFishingGuruScript);
    CONVERTED_SCRIPT(OlivineCafeSailorScript);

    // maps/OlivineGoodRodHouse.c
    CONVERTED_SCRIPT(GoodRodGuru);

    // maps/OlivineGym.c
    CONVERTED_SCRIPT(OlivineGymJasmineScript);
    CONVERTED_SCRIPT(OlivineGymGuideScript);

    // maps/OlivineLighthouse1F.c
    CONVERTED_SCRIPT(OlivineLighthouse1FSailorScript);
    CONVERTED_SCRIPT(OlivineLighthouse1FPokefanFScript);

    // maps/OlivineLighthouse2F.c
    CONVERTED_SCRIPT(TrainerSailorHuey);
    CONVERTED_SCRIPT(TrainerGentlemanAlfred);

    // maps/OlivineLighthouse3F.c
    CONVERTED_SCRIPT(TrainerSailorTerrell);
    CONVERTED_SCRIPT(TrainerGentlemanPreston);
    CONVERTED_SCRIPT(TrainerBirdKeeperTheo);
    CONVERTED_SCRIPT(OlivineLighthouse3FEther);

    // maps/OlivineLighthouse4F.c
    CONVERTED_SCRIPT(TrainerSailorKent);
    CONVERTED_SCRIPT(TrainerLassConnie);

    // maps/OlivineLighthouse5F.c
    CONVERTED_SCRIPT(TrainerSailorErnest);
    CONVERTED_SCRIPT(TrainerBirdKeeperDenis);
    CONVERTED_SCRIPT(OlivineLighthouse5FRareCandy);
    CONVERTED_SCRIPT(OlivineLighthouse5FSuperRepel);
    CONVERTED_SCRIPT(OlivineLighthouse5FTMSwagger);

    // maps/OlivineLighthouse6F.c
    CONVERTED_SCRIPT(OlivineLighthouseJasmine);
    CONVERTED_SCRIPT(OlivineLighthouseAmphy);
    CONVERTED_SCRIPT(OlivineLighthouse6FSuperPotion);

    // maps/OlivineMart.c
    CONVERTED_SCRIPT(OlivineMartClerkScript);
    CONVERTED_SCRIPT(OlivineMartCooltrainerFScript);
    CONVERTED_SCRIPT(OlivineMartLassScript);

    // maps/OlivinePokecenter1F.c
    CONVERTED_SCRIPT(OlivinePokecenter1FNurseScript);
    CONVERTED_SCRIPT(OlivinePokecenter1FFishingGuruScript);
    CONVERTED_SCRIPT(OlivinePokecenter1FFisherScript);
    CONVERTED_SCRIPT(OlivinePokecenter1FTeacherScript);

    // maps/OlivinePort.c
    CONVERTED_SCRIPT(OlivinePortSailorAtGangwayScript);
    CONVERTED_SCRIPT(OlivinePortSailorBeforeHOFScript);
    CONVERTED_SCRIPT(OlivinePortSailorAfterHOFScript);
    CONVERTED_SCRIPT(OlivinePortFishingGuru1Script);
    CONVERTED_SCRIPT(OlivinePortFishingGuru2Script);
    CONVERTED_SCRIPT(OlivinePortYoungsterScript);
    CONVERTED_SCRIPT(OlivinePortCooltrainerFScript);

    // maps/OlivinePortPassage.c
    CONVERTED_SCRIPT(OlivinePortPassagePokefanMScript);

    // maps/OlivinePunishmentSpeechHouse.c
    CONVERTED_SCRIPT(OlivinePunishmentSpeechHouseDad);
    CONVERTED_SCRIPT(OlivinePunishmentSpeechHouseDaughter);

    // maps/OlivineTimsHouse.c
    CONVERTED_SCRIPT(Tim);

    // maps/BattleTower1F.c
    CONVERTED_SCRIPT(BattleTower1FReceptionistScript);
    CONVERTED_SCRIPT(BattleTower1FYoungsterScript);
    CONVERTED_SCRIPT(BattleTower1FCooltrainerFScript);
    CONVERTED_SCRIPT(BattleTower1FBugCatcherScript);
    CONVERTED_SCRIPT(BattleTower1FGrannyScript);

    // maps/CianwoodGym.c
    CONVERTED_SCRIPT(CianwoodGymChuckScript);
    CONVERTED_SCRIPT(TrainerBlackbeltYoshi);
    CONVERTED_SCRIPT(TrainerBlackbeltLao);
    CONVERTED_SCRIPT(TrainerBlackbeltNob);
    CONVERTED_SCRIPT(TrainerBlackbeltLung);
    CONVERTED_SCRIPT(CianwoodGymBoulder);
    // CONVERTED_SCRIPT(CianwoodGymBoulder);
    // CONVERTED_SCRIPT(CianwoodGymBoulder);
    // CONVERTED_SCRIPT(CianwoodGymBoulder);

    // maps/CianwoodLugiaSpeechHouse.c
    CONVERTED_SCRIPT(CianwoodLugiaSpeechHouseTeacherScript);
    CONVERTED_SCRIPT(CianwoodLugiaSpeechHouseLassScript);
    CONVERTED_SCRIPT(CianwoodLugiaSpeechHouseTwinScript);

    // maps/CianwoodPharmacy.c
    CONVERTED_SCRIPT(CianwoodPharmacist);

    // maps/CianwoodPhotoStudio.c
    CONVERTED_SCRIPT(CianwoodPhotoStudioFishingGuruScript);

    // maps/CianwoodPokecenter1F.c
    CONVERTED_SCRIPT(CianwoodPokecenter1FNurseScript);
    CONVERTED_SCRIPT(CianwoodPokecenter1FLassScript);
    CONVERTED_SCRIPT(CianwoodGymGuideScript);
    CONVERTED_SCRIPT(CianwoodPokecenter1FSuperNerdScript);

    // maps/ManiasHouse.c
    CONVERTED_SCRIPT(ManiaScript);

    // maps/PokeSeersHouse.c
    CONVERTED_SCRIPT(SeerScript);

    // maps/MahoganyGym.c
    CONVERTED_SCRIPT(MahoganyGymPryceScript);
    CONVERTED_SCRIPT(TrainerSkierRoxanne);
    CONVERTED_SCRIPT(TrainerBoarderRonald);
    CONVERTED_SCRIPT(TrainerSkierClarissa);
    CONVERTED_SCRIPT(TrainerBoarderBrad);
    CONVERTED_SCRIPT(TrainerBoarderDouglas);
    CONVERTED_SCRIPT(MahoganyGymGuideScript);

    // maps/MahoganyMart1F.c
    CONVERTED_SCRIPT(MahoganyMart1FPharmacistScript);
    CONVERTED_SCRIPT(MahoganyMart1FBlackBeltScript);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(MahoganyMart1FGrannyScript);

    // maps/MahoganyPokecenter1F.c
    CONVERTED_SCRIPT(MahoganyPokecenter1FNurseScript);
    CONVERTED_SCRIPT(MahoganyPokecenter1FPokefanMScript);
    CONVERTED_SCRIPT(MahoganyPokecenter1FYoungsterScript);
    CONVERTED_SCRIPT(MahoganyPokecenter1FCooltrainerFScript);

    // maps/MahoganyRedGyaradosSpeechHouse.c
    CONVERTED_SCRIPT(MahoganyRedGyaradosSpeechHouseBlackBeltScript);
    CONVERTED_SCRIPT(MahoganyRedGyaradosSpeechHouseTeacherScript);

    // maps/LakeOfRageHiddenPowerHouse.c
    CONVERTED_SCRIPT(HiddenPowerGuy);

    // maps/LakeOfRageMagikarpHouse.c
    CONVERTED_SCRIPT(MagikarpLengthRaterScript);

    // maps/BlackthornDragonSpeechHouse.c
    CONVERTED_SCRIPT(BlackthornDragonSpeechHouseGrannyScript);
    CONVERTED_SCRIPT(BlackthornDragonSpeechHouseDratiniScript);

    // maps/BlackthornEmysHouse.c
    CONVERTED_SCRIPT(Emy);

    // maps/BlackthornGym1F.c
    CONVERTED_SCRIPT(BlackthornGymClairScript);
    CONVERTED_SCRIPT(TrainerCooltrainermMike);
    CONVERTED_SCRIPT(TrainerCooltrainermPaul);
    CONVERTED_SCRIPT(TrainerCooltrainerfLola);
    CONVERTED_SCRIPT(BlackthornGymGuideScript);

    // maps/BlackthornGym2F.c
    CONVERTED_SCRIPT(TrainerCooltrainermCody);
    CONVERTED_SCRIPT(TrainerCooltrainerfFran);
    CONVERTED_SCRIPT(BlackthornGymBoulder);
    // CONVERTED_SCRIPT(BlackthornGymBoulder);
    // CONVERTED_SCRIPT(BlackthornGymBoulder);
    // CONVERTED_SCRIPT(BlackthornGymBoulder);
    // CONVERTED_SCRIPT(BlackthornGymBoulder);
    // CONVERTED_SCRIPT(BlackthornGymBoulder);

    // maps/BlackthornMart.c
    CONVERTED_SCRIPT(BlackthornMartClerkScript);
    CONVERTED_SCRIPT(BlackthornMartCooltrainerMScript);
    CONVERTED_SCRIPT(BlackthornMartBlackBeltScript);

    // maps/BlackthornPokecenter1F.c
    CONVERTED_SCRIPT(BlackthornPokecenter1FNurseScript);
    CONVERTED_SCRIPT(BlackthornPokecenter1FGentlemanScript);
    CONVERTED_SCRIPT(BlackthornPokecenter1FTwinScript);
    CONVERTED_SCRIPT(BlackthornPokecenter1FCooltrainerMScript);

    // maps/MoveDeletersHouse.c
    CONVERTED_SCRIPT(MoveDeleter);

    // maps/IndigoPlateauPokecenter1F.c
    CONVERTED_SCRIPT(IndigoPlateauPokecenter1FNurseScript);
    CONVERTED_SCRIPT(IndigoPlateauPokecenter1FClerkScript);
    CONVERTED_SCRIPT(IndigoPlateauPokecenter1FCooltrainerMScript);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(TeleportGuyScript);
    CONVERTED_SCRIPT(AbraScript);

    // maps/WillsRoom.c
    CONVERTED_SCRIPT(WillScript_Battle);

    // maps/KogasRoom.c
    CONVERTED_SCRIPT(KogaScript_Battle);

    // maps/BrunosRoom.c
    CONVERTED_SCRIPT(BrunoScript_Battle);

    // maps/KarensRoom.c
    CONVERTED_SCRIPT(KarenScript_Battle);

    // maps/LancesRoom.c
    CONVERTED_SCRIPT(LancesRoomLanceScript);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/HallOfFame.c
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/RedsHouse1F.c
    CONVERTED_SCRIPT(RedsMom);

    // maps/BluesHouse.c
    CONVERTED_SCRIPT(DaisyScript);

    // maps/OaksLab.c
    CONVERTED_SCRIPT(Oak);
    CONVERTED_SCRIPT(OaksAssistant1Script);
    CONVERTED_SCRIPT(OaksAssistant2Script);
    CONVERTED_SCRIPT(OaksAssistant3Script);

    // maps/ViridianGym.c
    CONVERTED_SCRIPT(ViridianGymBlueScript);
    CONVERTED_SCRIPT(ViridianGymGuideScript);

    // maps/ViridianMart.c
    CONVERTED_SCRIPT(ViridianMartClerkScript);
    CONVERTED_SCRIPT(ViridianMartLassScript);
    CONVERTED_SCRIPT(ViridianMartCooltrainerMScript);

    // maps/ViridianNicknameSpeechHouse.c
    CONVERTED_SCRIPT(ViridianNicknameSpeechHousePokefanMScript);
    CONVERTED_SCRIPT(ViridianNicknameSpeechHouseLassScript);
    CONVERTED_SCRIPT(Speary);
    CONVERTED_SCRIPT(Rattey);

    // maps/ViridianPokecenter1F.c
    CONVERTED_SCRIPT(ViridianPokecenter1FNurseScript);
    CONVERTED_SCRIPT(ViridianPokecenter1FCooltrainerMScript);
    CONVERTED_SCRIPT(ViridianPokecenter1FCooltrainerFScript);
    CONVERTED_SCRIPT(ViridianPokecenter1FBugCatcherScript);

    // maps/TrainerHouse1F.c
    CONVERTED_SCRIPT(TrainerHouse1FReceptionistScript);
    CONVERTED_SCRIPT(TrainerHouse1FCooltrainerMScript);
    CONVERTED_SCRIPT(TrainerHouse1FCooltrainerFScript);
    CONVERTED_SCRIPT(TrainerHouse1FYoungsterScript);
    CONVERTED_SCRIPT(TrainerHouse1FGentlemanScript);

    // maps/TrainerHouseB1F.c
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/PewterGym.c
    CONVERTED_SCRIPT(PewterGymBrockScript);
    CONVERTED_SCRIPT(TrainerCamperJerry);
    CONVERTED_SCRIPT(PewterGymGuideScript);

    // maps/PewterMart.c
    CONVERTED_SCRIPT(PewterMartClerkScript);
    CONVERTED_SCRIPT(PewterMartYoungsterScript);
    CONVERTED_SCRIPT(PewterMartSuperNerdScript);

    // maps/PewterNidoranSpeechHouse.c
    CONVERTED_SCRIPT(PewterNidoranSpeechHouseSuperNerdScript);
    CONVERTED_SCRIPT(PewterNidoran);

    // maps/PewterPokecenter1F.c
    CONVERTED_SCRIPT(PewterPokecenter1FNurseScript);
    CONVERTED_SCRIPT(PewterPokecenter1FTeacherScript);
    CONVERTED_SCRIPT(PewterJigglypuff);
    CONVERTED_SCRIPT(PewterPokecenter1FBugCatcherScript);
    CONVERTED_SCRIPT(Chris);

    // maps/PewterSnoozeSpeechHouse.c
    CONVERTED_SCRIPT(PewterSnoozeSpeechHouseGrampsScript);

    // maps/CeruleanGym.c
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(CeruleanGymMistyScript);
    CONVERTED_SCRIPT(TrainerSwimmerfDiana);
    CONVERTED_SCRIPT(TrainerSwimmerfBriana);
    CONVERTED_SCRIPT(TrainerSwimmermParker);
    CONVERTED_SCRIPT(CeruleanGymGuideScript);

    // maps/CeruleanGymBadgeSpeechHouse.c
    CONVERTED_SCRIPT(CeruleanGymBadgeSpeechHousePokefanMScript);

    // maps/CeruleanMart.c
    CONVERTED_SCRIPT(CeruleanMart_Clerk);
    CONVERTED_SCRIPT(CeruleanMart_CooltrainerM);
    CONVERTED_SCRIPT(CeruleanMart_CooltrainerF);

    // maps/CeruleanPokecenter1F.c
    CONVERTED_SCRIPT(CeruleanPokecenter1FNurseScript);
    CONVERTED_SCRIPT(CeruleanPokecenter1FSuperNerdScript);
    CONVERTED_SCRIPT(CeruleanPokecenter1FGymGuideScript);

    // maps/CeruleanPoliceStation.c
    CONVERTED_SCRIPT(CeruleanPoliceStationFishingGuruScript);
    CONVERTED_SCRIPT(CeruleanPoliceStationPokefanFScript);
    CONVERTED_SCRIPT(CeruleanDiglett);

    // maps/CeruleanTradeSpeechHouse.c
    CONVERTED_SCRIPT(CeruleanTradeSpeechHouseGrannyScript);
    CONVERTED_SCRIPT(CeruleanTradeSpeechHouseGrampsScript);
    CONVERTED_SCRIPT(CeruleanTradeSpeechHouseRhydonScript);
    CONVERTED_SCRIPT(CeruleanTradeSpeechHouseZubatScript);

    // maps/VermilionDiglettsCaveSpeechHouse.c
    CONVERTED_SCRIPT(VermilionDiglettsCaveSpeechHouseGentlemanScript);

    // maps/VermilionFishingSpeechHouse.c
    CONVERTED_SCRIPT(FishingDude);

    // maps/VermilionGym.c
    CONVERTED_SCRIPT(VermilionGymSurgeScript);
    CONVERTED_SCRIPT(TrainerGentlemanGregory);
    CONVERTED_SCRIPT(TrainerGuitaristVincent);
    CONVERTED_SCRIPT(TrainerJugglerHorton);
    CONVERTED_SCRIPT(VermilionGymGuideScript);

    // maps/VermilionMagnetTrainSpeechHouse.c
    CONVERTED_SCRIPT(VermilionMagnetTrainSpeechHousePokefanFScript);
    CONVERTED_SCRIPT(VermilionMagnetTrainSpeechHouseYoungsterScript);

    // maps/VermilionMart.c
    CONVERTED_SCRIPT(VermilionMartClerkScript);
    CONVERTED_SCRIPT(VermilionMartSuperNerdScript);
    CONVERTED_SCRIPT(VermilionMartBeautyScript);

    // maps/VermilionPokecenter1F.c
    CONVERTED_SCRIPT(VermilionPokecenter1FNurseScript);
    CONVERTED_SCRIPT(VermilionPokecenter1FFishingGuruScript);
    CONVERTED_SCRIPT(VermilionPokecenter1FSailorScript);
    CONVERTED_SCRIPT(VermilionPokecenter1FBugCatcherScript);

    // maps/PokemonFanClub.c
    CONVERTED_SCRIPT(PokemonFanClubChairmanScript);
    CONVERTED_SCRIPT(PokemonFanClubReceptionistScript);
    CONVERTED_SCRIPT(PokemonFanClubClefairyGuyScript);
    CONVERTED_SCRIPT(PokemonFanClubTeacherScript);
    CONVERTED_SCRIPT(PokemonFanClubClefairyDollScript);
    CONVERTED_SCRIPT(PokemonFanClubBayleefScript);

    // maps/LavenderMart.c
    CONVERTED_SCRIPT(LavenderMartClerkScript);
    CONVERTED_SCRIPT(LavenderMartPokefanMScript);
    CONVERTED_SCRIPT(LavenderMartRockerScript);

    // maps/LavenderNameRater.c
    CONVERTED_SCRIPT(LavenderNameRater);

    // maps/LavenderPokecenter1F.c
    CONVERTED_SCRIPT(LavenderPokecenter1FNurseScript);
    CONVERTED_SCRIPT(LavenderPokecenter1FGentlemanScript);
    CONVERTED_SCRIPT(LavenderPokecenter1FTeacherScript);
    CONVERTED_SCRIPT(LavenderPokecenter1FYoungsterScript);

    // maps/LavenderSpeechHouse.c
    CONVERTED_SCRIPT(LavenderSpeechHousePokefanFScript);

    // maps/LavRadioTower1F.c
    CONVERTED_SCRIPT(LavRadioTower1FReceptionistScript);
    CONVERTED_SCRIPT(LavRadioTower1FOfficerScript);
    CONVERTED_SCRIPT(LavRadioTower1FSuperNerd1Script);
    CONVERTED_SCRIPT(LavRadioTower1FGentlemanScript);
    CONVERTED_SCRIPT(LavRadioTower1FSuperNerd2Script);

    // maps/SoulHouse.c
    CONVERTED_SCRIPT(MrFuji);
    CONVERTED_SCRIPT(SoulHouseTeacherScript);
    CONVERTED_SCRIPT(SoulHouseLassScript);
    CONVERTED_SCRIPT(SoulHouseGrannyScript);

    // maps/CeladonCafe.c
    CONVERTED_SCRIPT(CeladonCafeChef);
    CONVERTED_SCRIPT(CeladonCafeFisher1);
    CONVERTED_SCRIPT(CeladonCafeFisher2);
    CONVERTED_SCRIPT(CeladonCafeFisher3);
    CONVERTED_SCRIPT(CeladonCafeTeacher);

    // maps/CeladonDeptStore1F.c
    CONVERTED_SCRIPT(CeladonDeptStore1FReceptionistScript);
    CONVERTED_SCRIPT(CeladonDeptStore1FGentlemanScript);
    CONVERTED_SCRIPT(CeladonDeptStore1FTeacherScript);

    // maps/CeladonDeptStore2F.c
    CONVERTED_SCRIPT(CeladonDeptStore2FClerk1Script);
    CONVERTED_SCRIPT(CeladonDeptStore2FClerk2Script);
    CONVERTED_SCRIPT(CeladonDeptStore2FPokefanMScript);
    CONVERTED_SCRIPT(CeladonDeptStore2FYoungsterScript);

    // maps/CeladonDeptStore3F.c
    CONVERTED_SCRIPT(CeladonDeptStore3FClerkScript);
    CONVERTED_SCRIPT(CeladonDeptStore3FYoungsterScript);
    CONVERTED_SCRIPT(CeladonDeptStore3FGameboyKid1Script);
    CONVERTED_SCRIPT(CeladonDeptStore3FGameboyKid2Script);
    CONVERTED_SCRIPT(CeladonDeptStore3FSuperNerdScript);

    // maps/CeladonDeptStore4F.c
    CONVERTED_SCRIPT(CeladonDeptStore4FClerkScript);
    CONVERTED_SCRIPT(CeladonDeptStore4FSuperNerdScript);
    CONVERTED_SCRIPT(CeladonDeptStore4FYoungsterScript);

    // maps/CeladonDeptStore5F.c
    CONVERTED_SCRIPT(CeladonDeptStore5FClerk1Script);
    CONVERTED_SCRIPT(CeladonDeptStore5FClerk2Script);
    CONVERTED_SCRIPT(CeladonDeptStore5FGentlemanScript);
    CONVERTED_SCRIPT(CeladonDeptStore5FSailorScript);
    CONVERTED_SCRIPT(CeladonDeptStore5FTeacherScript);

    // maps/CeladonDeptStore6F.c
    CONVERTED_SCRIPT(CeladonDeptStore6FSuperNerdScript);
    CONVERTED_SCRIPT(CeladonDeptStore6FYoungsterScript);

    // maps/CeladonDeptStoreElevator.c

    // maps/CeladonGameCorner.c
    CONVERTED_SCRIPT(CeladonGameCornerClerkScript);
    CONVERTED_SCRIPT(CeladonGameCornerReceptionistScript);
    CONVERTED_SCRIPT(CeladonGameCornerPokefanMScript);
    CONVERTED_SCRIPT(CeladonGameCornerTeacherScript);
    CONVERTED_SCRIPT(CeladonGameCornerFishingGuruScript);
    CONVERTED_SCRIPT(CeladonGameCornerFisherScript);
    CONVERTED_SCRIPT(CeladonGameCornerFisherScript);
    CONVERTED_SCRIPT(CeladonGymGuideScript);
    CONVERTED_SCRIPT(CeladonGameCornerGrampsScript);

    // maps/CeladonGameCornerPrizeRoom.c
    CONVERTED_SCRIPT(CeladonGameCornerPrizeRoomGentlemanScript);
    CONVERTED_SCRIPT(CeladonGameCornerPrizeRoomPharmacistScript);

    // maps/CeladonGym.c
    CONVERTED_SCRIPT(CeladonGymErikaScript);
    CONVERTED_SCRIPT(TrainerLassMichelle);
    CONVERTED_SCRIPT(TrainerPicnickerTanya);
    CONVERTED_SCRIPT(TrainerBeautyJulia);
    CONVERTED_SCRIPT(TrainerTwinsJoAndZoe1);
    CONVERTED_SCRIPT(TrainerTwinsJoAndZoe2);

    // maps/CeladonMansion1F.c
    CONVERTED_SCRIPT(CeladonMansionManager);
    CONVERTED_SCRIPT(CeladonMansion1FMeowth);
    CONVERTED_SCRIPT(CeladonMansion1FClefairy);
    CONVERTED_SCRIPT(CeladonMansion1FNidoranF);

    // maps/CeladonMansion2F.c

    // maps/CeladonMansion3F.c
    CONVERTED_SCRIPT(GameFreakGameDesignerScript);
    CONVERTED_SCRIPT(GameFreakGraphicArtistScript);
    CONVERTED_SCRIPT(GameFreakProgrammerScript);
    CONVERTED_SCRIPT(GameFreakCharacterDesignerScript);

    // maps/CeladonMansionRoof.c
    CONVERTED_SCRIPT(CeladonMansionRoofFisherScript);

    // maps/CeladonMansionRoofHouse.c
    CONVERTED_SCRIPT(CeladonMansionRoofHousePharmacistScript);

    // maps/CeladonPokecenter1F.c
    CONVERTED_SCRIPT(CeladonPokecenter1FNurseScript);
    CONVERTED_SCRIPT(CeladonPokecenter1FGentlemanScript);
    CONVERTED_SCRIPT(CeladonPokecenter1FPharmacistScript);
    CONVERTED_SCRIPT(CeladonPokecenter1FCooltrainerFScript);
    CONVERTED_SCRIPT(CeladonEusine);

    // maps/SaffronMagnetTrainStation.c
    CONVERTED_SCRIPT(SaffronMagnetTrainStationOfficerScript);
    CONVERTED_SCRIPT(SaffronMagnetTrainStationGymGuideScript);
    CONVERTED_SCRIPT(SaffronMagnetTrainStationTeacherScript);
    CONVERTED_SCRIPT(SaffronMagnetTrainStationLassScript);

    // maps/MrPsychicsHouse.c
    CONVERTED_SCRIPT(MrPsychic);

    // maps/CopycatsHouse1F.c
    CONVERTED_SCRIPT(CopycatsHouse1FPokefanMScript);
    CONVERTED_SCRIPT(CopycatsHouse1FPokefanFScript);
    CONVERTED_SCRIPT(CopycatsHouse1FBlisseyScript);

    // maps/CopycatsHouse2F.c
    CONVERTED_SCRIPT(Copycat);
    CONVERTED_SCRIPT(CopycatsDodrio);
    CONVERTED_SCRIPT(CopycatsHouse2FDoll);
    CONVERTED_SCRIPT(CopycatsHouse2FDoll);
    CONVERTED_SCRIPT(CopycatsHouse2FDoll);
    CONVERTED_SCRIPT(Copycat);

    // maps/FightingDojo.c
    CONVERTED_SCRIPT(FightingDojoBlackBelt);
    CONVERTED_SCRIPT(FightingDojoFocusBand);

    // maps/SilphCo1F.c
    CONVERTED_SCRIPT(SilphCoReceptionistScript);
    CONVERTED_SCRIPT(SilphCoOfficerScript);

    // maps/SaffronGym.c
    CONVERTED_SCRIPT(SaffronGymSabrinaScript);
    CONVERTED_SCRIPT(TrainerMediumRebecca);
    CONVERTED_SCRIPT(TrainerPsychicFranklin);
    CONVERTED_SCRIPT(TrainerMediumDoris);
    CONVERTED_SCRIPT(TrainerPsychicJared);
    CONVERTED_SCRIPT(SaffronGymGuideScript);

    // maps/SaffronMart.c
    CONVERTED_SCRIPT(SaffronMartClerkScript);
    CONVERTED_SCRIPT(SaffronMartCooltrainerMScript);
    CONVERTED_SCRIPT(SaffronMartCooltrainerFScript);

    // maps/SaffronPokecenter1F.c
    CONVERTED_SCRIPT(SaffronPokecenter1FNurseScript);
    CONVERTED_SCRIPT(SaffronPokecenter1FTeacherScript);
    CONVERTED_SCRIPT(SaffronPokecenter1FFisherScript);
    CONVERTED_SCRIPT(SaffronPokecenter1FYoungsterScript);

    // maps/FuchsiaGym.c
    CONVERTED_SCRIPT(FuchsiaGymJanineScript);
    CONVERTED_SCRIPT(LassAliceScript);
    CONVERTED_SCRIPT(LassLindaScript);
    CONVERTED_SCRIPT(PicnickerCindyScript);
    CONVERTED_SCRIPT(CamperBarryScript);
    CONVERTED_SCRIPT(FuchsiaGymGuideScript);

    // maps/FuchsiaMart.c
    CONVERTED_SCRIPT(FuchsiaMartClerkScript);
    CONVERTED_SCRIPT(FuchsiaMartFisherScript);
    CONVERTED_SCRIPT(FuchsiaMartCooltrainerFScript);

    // maps/FuchsiaPokecenter1F.c
    CONVERTED_SCRIPT(FuchsiaPokecenter1FNurseScript);
    CONVERTED_SCRIPT(FuchsiaPokecenter1FCooltrainerMScript);
    CONVERTED_SCRIPT(FuchsiaPokecenter1FCooltrainerFScript);
    CONVERTED_SCRIPT(FuchsiaPokecenter1FJanineImpersonatorScript);

    // maps/SafariZoneMainOffice.c

    // maps/SafariZoneWardensHome.c
    CONVERTED_SCRIPT(WardensGranddaughter);

    // maps/BillsBrothersHouse.c
    CONVERTED_SCRIPT(BillsBrotherScript);
    CONVERTED_SCRIPT(BillsBrothersHouseYoungsterScript);

    // maps/CinnabarPokecenter1F.c
    CONVERTED_SCRIPT(CinnabarPokecenter1FNurseScript);
    CONVERTED_SCRIPT(CinnabarPokecenter1FCooltrainerFScript);
    CONVERTED_SCRIPT(CinnabarPokecenter1FFisherScript);

    // maps/SilverCavePokecenter1F.c
    CONVERTED_SCRIPT(SilverCavePokecenter1FNurseScript);
    CONVERTED_SCRIPT(SilverCavePokecenter1FGrannyScript);

    // maps/SproutTower1F.c
    CONVERTED_SCRIPT(SproutTower1FSage1Script);
    CONVERTED_SCRIPT(SproutTower1FSage2Script);
    CONVERTED_SCRIPT(SproutTower1FGrannyScript);
    CONVERTED_SCRIPT(SproutTower1FTeacherScript);
    CONVERTED_SCRIPT(TrainerSageChow);
    CONVERTED_SCRIPT(SproutTower1FParlyzHeal);

    // maps/SproutTower2F.c
    CONVERTED_SCRIPT(TrainerSageNico);
    CONVERTED_SCRIPT(TrainerSageEdmond);
    CONVERTED_SCRIPT(SproutTower2FXAccuracy);

    // maps/SproutTower3F.c
    CONVERTED_SCRIPT(TrainerSageJin);
    CONVERTED_SCRIPT(TrainerSageTroy);
    CONVERTED_SCRIPT(SageLiScript);
    CONVERTED_SCRIPT(TrainerSageNeal);
    CONVERTED_SCRIPT(SproutTower3FPotion);
    CONVERTED_SCRIPT(SproutTower3FEscapeRope);

    // maps/RuinsOfAlphOutside.c
    CONVERTED_SCRIPT(TrainerPsychicNathan);
    CONVERTED_SCRIPT(RuinsOfAlphOutsideScientistScript);
    CONVERTED_SCRIPT(RuinsOfAlphOutsideFisherScript);
    CONVERTED_SCRIPT(RuinsOfAlphOutsideYoungster1Script);
    CONVERTED_SCRIPT(RuinsOfAlphOutsideYoungster2Script);

    // maps/RuinsOfAlphInnerChamber.c
    CONVERTED_SCRIPT(RuinsOfAlphInnerChamberFisherScript);
    CONVERTED_SCRIPT(RuinsOfAlphInnerChamberTeacherScript);
    CONVERTED_SCRIPT(RuinsOfAlphInnerChamberGrampsScript);

    // maps/RuinsOfAlphResearchCenter.c
    CONVERTED_SCRIPT(RuinsOfAlphResearchCenterScientist1Script);
    CONVERTED_SCRIPT(RuinsOfAlphResearchCenterScientist2Script);
    CONVERTED_SCRIPT(RuinsOfAlphResearchCenterScientist3Script);

    // maps/RuinsOfAlphKabutoChamber.c
    CONVERTED_SCRIPT(RuinsOfAlphKabutoChamberReceptionistScript);
    CONVERTED_SCRIPT(RuinsOfAlphKabutoChamberScientistScript);

    // maps/RuinsOfAlphKabutoItemRoom.c
    CONVERTED_SCRIPT(RuinsOfAlphKabutoItemRoomBerry);
    CONVERTED_SCRIPT(RuinsOfAlphKabutoItemRoomPsncureberry);
    CONVERTED_SCRIPT(RuinsOfAlphKabutoItemRoomHealPowder);
    CONVERTED_SCRIPT(RuinsOfAlphKabutoItemRoomEnergypowder);

    // maps/RuinsOfAlphOmanyteItemRoom.c
    CONVERTED_SCRIPT(RuinsOfAlphOmanyteItemRoomMysteryberry);
    CONVERTED_SCRIPT(RuinsOfAlphOmanyteItemRoomMysticWater);
    CONVERTED_SCRIPT(RuinsOfAlphOmanyteItemRoomStardust);
    CONVERTED_SCRIPT(RuinsOfAlphOmanyteItemRoomStarPiece);

    // maps/RuinsOfAlphAerodactylItemRoom.c
    CONVERTED_SCRIPT(RuinsOfAlphAerodactylItemRoomGoldBerry);
    CONVERTED_SCRIPT(RuinsOfAlphAerodactylItemRoomMoonStone);
    CONVERTED_SCRIPT(RuinsOfAlphAerodactylItemRoomHealPowder);
    CONVERTED_SCRIPT(RuinsOfAlphAerodactylItemRoomEnergyRoot);

    // maps/RuinsOfAlphHoOhItemRoom.c
    CONVERTED_SCRIPT(RuinsOfAlphHoOhItemRoomGoldBerry);
    CONVERTED_SCRIPT(RuinsOfAlphHoOhItemRoomMysteryberry);
    CONVERTED_SCRIPT(RuinsOfAlphHoOhItemRoomRevivalHerb);
    CONVERTED_SCRIPT(RuinsOfAlphHoOhItemRoomCharcoal);

    // maps/UnionCave1F.c
    CONVERTED_SCRIPT(TrainerHikerDaniel);
    CONVERTED_SCRIPT(TrainerPokemaniacLarry);
    CONVERTED_SCRIPT(TrainerHikerRussell);
    CONVERTED_SCRIPT(TrainerFirebreatherRay);
    CONVERTED_SCRIPT(TrainerFirebreatherBill);
    CONVERTED_SCRIPT(UnionCave1FGreatBall);
    CONVERTED_SCRIPT(UnionCave1FXAttack);
    CONVERTED_SCRIPT(UnionCave1FPotion);
    CONVERTED_SCRIPT(UnionCave1FAwakening);

    // maps/UnionCaveB1F.c
    CONVERTED_SCRIPT(TrainerHikerPhillip);
    CONVERTED_SCRIPT(TrainerHikerLeonard);
    CONVERTED_SCRIPT(TrainerPokemaniacAndrew);
    CONVERTED_SCRIPT(TrainerPokemaniacCalvin);
    CONVERTED_SCRIPT(UnionCaveB1FTMSwift);
    CONVERTED_SCRIPT(UnionCaveB1FBoulder);
    CONVERTED_SCRIPT(UnionCaveB1FXDefend);

    // maps/UnionCaveB2F.c
    CONVERTED_SCRIPT(TrainerCooltrainermNick);
    CONVERTED_SCRIPT(TrainerCooltrainerfGwen);
    CONVERTED_SCRIPT(TrainerCooltrainerfEmma);
    CONVERTED_SCRIPT(UnionCaveB2FElixer);
    CONVERTED_SCRIPT(UnionCaveB2FHyperPotion);
    CONVERTED_SCRIPT(UnionCaveLapras);

    // maps/SlowpokeWellB1F.c
    CONVERTED_SCRIPT(TrainerGruntM29);
    CONVERTED_SCRIPT(TrainerGruntM1);
    CONVERTED_SCRIPT(TrainerGruntM2);
    CONVERTED_SCRIPT(TrainerGruntF1);
    CONVERTED_SCRIPT(SlowpokeWellB1FSlowpokeWithMailScript);
    CONVERTED_SCRIPT(SlowpokeWellB1FTaillessSlowpokeScript);
    CONVERTED_SCRIPT(SlowpokeWellB1FKurtScript);
    CONVERTED_SCRIPT(SlowpokeWellB1FBoulder);
    CONVERTED_SCRIPT(SlowpokeWellB1FSuperPotion);

    // maps/SlowpokeWellB2F.c
    CONVERTED_SCRIPT(SlowpokeWellB2FGymGuideScript);
    CONVERTED_SCRIPT(SlowpokeWellB2FTMRainDance);

    // maps/IlexForest.c
    CONVERTED_SCRIPT(IlexForestFarfetchdScript);
    CONVERTED_SCRIPT(IlexForestCharcoalApprenticeScript);
    CONVERTED_SCRIPT(IlexForestCharcoalMasterScript);
    CONVERTED_SCRIPT(IlexForestHeadbuttGuyScript);
    CONVERTED_SCRIPT(IlexForestRevive);
    CONVERTED_SCRIPT(IlexForestLassScript);
    CONVERTED_SCRIPT(TrainerBugCatcherWayne);
    CONVERTED_SCRIPT(IlexForestXAttack);
    CONVERTED_SCRIPT(IlexForestAntidote);
    CONVERTED_SCRIPT(IlexForestEther);

    // maps/IlexForestAzaleaGate.c
    CONVERTED_SCRIPT(IlexForestAzaleaGateOfficerScript);
    CONVERTED_SCRIPT(IlexForestAzaleaGateGrannyScript);

    // maps/RadioTower1F.c
    CONVERTED_SCRIPT(RadioTower1FReceptionistScript);
    CONVERTED_SCRIPT(RadioTower1FLassScript);
    CONVERTED_SCRIPT(RadioTower1FYoungsterScript);
    CONVERTED_SCRIPT(TrainerGruntM3);
    CONVERTED_SCRIPT(RadioTower1FLuckyNumberManScript);
    CONVERTED_SCRIPT(RadioTower1FRadioCardWomanScript);

    // maps/RadioTower2F.c
    CONVERTED_SCRIPT(RadioTower2FSuperNerdScript);
    CONVERTED_SCRIPT(RadioTower2FTeacherScript);
    CONVERTED_SCRIPT(TrainerGruntM4);
    CONVERTED_SCRIPT(TrainerGruntM5);
    CONVERTED_SCRIPT(TrainerGruntM6);
    CONVERTED_SCRIPT(TrainerGruntF2);
    CONVERTED_SCRIPT(RadioTower2FBlackBelt1Script);
    CONVERTED_SCRIPT(RadioTower2FBlackBelt2Script);
    CONVERTED_SCRIPT(RadioTowerJigglypuff);
    CONVERTED_SCRIPT(Buena);
    CONVERTED_SCRIPT(RadioTowerBuenaPrizeReceptionist);

    // maps/RadioTower3F.c
    CONVERTED_SCRIPT(RadioTower3FSuperNerdScript);
    CONVERTED_SCRIPT(RadioTower3FGymGuideScript);
    CONVERTED_SCRIPT(RadioTower3FCooltrainerFScript);
    CONVERTED_SCRIPT(TrainerGruntM7);
    CONVERTED_SCRIPT(TrainerGruntM8);
    CONVERTED_SCRIPT(TrainerGruntM9);
    CONVERTED_SCRIPT(TrainerScientistMarc);

    // maps/RadioTower4F.c
    CONVERTED_SCRIPT(RadioTower4FFisherScript);
    CONVERTED_SCRIPT(RadioTower4FDJMaryScript);
    CONVERTED_SCRIPT(RadioTowerMeowth);
    CONVERTED_SCRIPT(TrainerGruntM10);
    CONVERTED_SCRIPT(TrainerExecutivem2);
    CONVERTED_SCRIPT(TrainerGruntF4);
    CONVERTED_SCRIPT(TrainerScientistRich);

    // maps/RadioTower5F.c
    CONVERTED_SCRIPT(Director);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(TrainerExecutivef1);
    CONVERTED_SCRIPT(Ben);
    CONVERTED_SCRIPT(RadioTower5FUltraBall);

    // maps/NationalPark.c
    CONVERTED_SCRIPT(NationalParkLassScript);
    CONVERTED_SCRIPT(NationalParkPokefanFScript);
    CONVERTED_SCRIPT(NationalParkTeacher1Script);
    CONVERTED_SCRIPT(NationalParkYoungster1Script);
    CONVERTED_SCRIPT(NationalParkYoungster2Script);
    CONVERTED_SCRIPT(NationalParkTeacher2Script);
    CONVERTED_SCRIPT(NationalParkPersian);
    CONVERTED_SCRIPT(TrainerSchoolboyJack1);
    CONVERTED_SCRIPT(TrainerPokefanfBeverly1);
    CONVERTED_SCRIPT(TrainerPokefanmWilliam);
    CONVERTED_SCRIPT(TrainerLassKrise);
    CONVERTED_SCRIPT(NationalParkParlyzHeal);
    CONVERTED_SCRIPT(NationalParkGameboyKidScript);
    CONVERTED_SCRIPT(NationalParkTMDig);

    // maps/NationalParkBugContest.c
    CONVERTED_SCRIPT(BugCatchingContestant1AScript);
    CONVERTED_SCRIPT(BugCatchingContestant2AScript);
    CONVERTED_SCRIPT(BugCatchingContestant3AScript);
    CONVERTED_SCRIPT(BugCatchingContestant4AScript);
    CONVERTED_SCRIPT(BugCatchingContestant5AScript);
    CONVERTED_SCRIPT(BugCatchingContestant6AScript);
    CONVERTED_SCRIPT(BugCatchingContestant7AScript);
    CONVERTED_SCRIPT(BugCatchingContestant8AScript);
    CONVERTED_SCRIPT(BugCatchingContestant9AScript);
    CONVERTED_SCRIPT(BugCatchingContestant10AScript);
    CONVERTED_SCRIPT(NationalParkBugContestParlyzHeal);
    CONVERTED_SCRIPT(NationalParkBugContestTMDig);

    // maps/BurnedTower1F.c
    CONVERTED_SCRIPT(BurnedTower1FRock);
    CONVERTED_SCRIPT(BurnedTower1FEusineScript);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(BurnedTower1FMortyScript);
    CONVERTED_SCRIPT(BurnedTower1FHPUp);

    // maps/BurnedTowerB1F.c
    CONVERTED_SCRIPT(BurnedTowerB1FBoulder);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(BurnedTowerB1FTMEndure);
    CONVERTED_SCRIPT(BurnedTowerB1FEusine);

    // maps/BattleTowerOutside.c
    CONVERTED_SCRIPT(BattleTowerOutsideYoungsterScript);
    CONVERTED_SCRIPT(BattleTowerOutsideBeautyScript);
    CONVERTED_SCRIPT(BattleTowerOutsideSailorScript);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/WhirlIslandSW.c
    CONVERTED_SCRIPT(WhirlIslandSWUltraBall);

    // maps/WhirlIslandB1F.c
    CONVERTED_SCRIPT(WhirlIslandB1FFullRestore);
    CONVERTED_SCRIPT(WhirlIslandB1FCarbos);
    CONVERTED_SCRIPT(WhirlIslandB1FCalcium);
    CONVERTED_SCRIPT(WhirlIslandB1FNugget);
    CONVERTED_SCRIPT(WhirlIslandB1FEscapeRope);
    CONVERTED_SCRIPT(WhirlIslandB1FBoulder);

    // maps/WhirlIslandB2F.c
    CONVERTED_SCRIPT(WhirlIslandB2FFullRestore);
    CONVERTED_SCRIPT(WhirlIslandB2FMaxRevive);
    CONVERTED_SCRIPT(WhirlIslandB2FMaxElixer);

    // maps/WhirlIslandLugiaChamber.c
    CONVERTED_SCRIPT(Lugia);

    // maps/MountMortar1FInside.c
    CONVERTED_SCRIPT(MountMortar1FBoulder);
    CONVERTED_SCRIPT(MountMortar1FInsideEscapeRope);
    CONVERTED_SCRIPT(MountMortar1FInsideMaxRevive);
    CONVERTED_SCRIPT(MountMortar1FInsideHyperPotion);
    CONVERTED_SCRIPT(MountMortar1FInsideMaxPotion);
    CONVERTED_SCRIPT(MountMortar1FInsideNugget);
    CONVERTED_SCRIPT(TrainerPokemaniacMiller);
    CONVERTED_SCRIPT(TrainerSupernerdMarkus);
    CONVERTED_SCRIPT(MountMortar1FInsideIron);
    CONVERTED_SCRIPT(MountMortar1FInsideUltraBall);

    // maps/MountMortar1FOutside.c
    CONVERTED_SCRIPT(MountMortar1FOutsideEther);
    CONVERTED_SCRIPT(MountMortar1FOutsideRevive);

    // maps/MountMortar2FInside.c
    CONVERTED_SCRIPT(MountMortar2FInsideMaxPotion);
    CONVERTED_SCRIPT(MountMortar2FInsideRareCandy);
    CONVERTED_SCRIPT(MountMortar2FInsideTMDefenseCurl);
    CONVERTED_SCRIPT(MountMortar2FInsideDragonScale);
    CONVERTED_SCRIPT(MountMortar2FInsideElixer);
    CONVERTED_SCRIPT(MountMortar2FInsideEscapeRope);
    CONVERTED_SCRIPT(TrainerSupernerdHugh);

    // maps/MountMortarB1F.c
    CONVERTED_SCRIPT(MountMortarB1FHyperPotion);
    CONVERTED_SCRIPT(MountMortarB1FCarbos);
    CONVERTED_SCRIPT(MountMortarB1FBoulder);
    CONVERTED_SCRIPT(MountMortarB1FKiyoScript);
    CONVERTED_SCRIPT(MountMortarB1FFullRestore);
    CONVERTED_SCRIPT(MountMortarB1FMaxEther);
    CONVERTED_SCRIPT(MountMortarB1FPPUp);

    // maps/TeamRocketBaseB1F.c
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(TrainerGruntM16);
    CONVERTED_SCRIPT(TrainerScientistJed);
    CONVERTED_SCRIPT(TeamRocketBaseB1FHyperPotion);
    CONVERTED_SCRIPT(TeamRocketBaseB1FNugget);
    CONVERTED_SCRIPT(TeamRocketBaseB1FGuardSpec);

    // maps/TeamRocketBaseB2F.c
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(RocketElectrode1);
    CONVERTED_SCRIPT(RocketElectrode2);
    CONVERTED_SCRIPT(RocketElectrode3);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(TrainerGruntM17);
    CONVERTED_SCRIPT(TrainerGruntM18);
    CONVERTED_SCRIPT(TrainerGruntM19);
    CONVERTED_SCRIPT(TeamRocketBaseB2FTMThief);

    // maps/TeamRocketBaseB3F.c
    CONVERTED_SCRIPT(LanceGetPasswordScript);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(RocketBaseMurkrow);
    CONVERTED_SCRIPT(SlowpokeTailGrunt);
    CONVERTED_SCRIPT(RaticateTailGrunt);
    CONVERTED_SCRIPT(TrainerScientistRoss);
    CONVERTED_SCRIPT(TrainerScientistMitch);
    CONVERTED_SCRIPT(TeamRocketBaseB3FRocketScript);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(TeamRocketBaseB3FProtein);
    CONVERTED_SCRIPT(TeamRocketBaseB3FXSpecial);
    CONVERTED_SCRIPT(TeamRocketBaseB3FFullHeal);
    CONVERTED_SCRIPT(TeamRocketBaseB3FIceHeal);
    CONVERTED_SCRIPT(TeamRocketBaseB3FUltraBall);

    // maps/IcePath1F.c
    CONVERTED_SCRIPT(IcePath1FHMWaterfall);
    CONVERTED_SCRIPT(IcePath1FPPUp);
    CONVERTED_SCRIPT(IcePath1FProtein);

    // maps/IcePathB1F.c
    CONVERTED_SCRIPT(IcePathB1FBoulder);
    // CONVERTED_SCRIPT(IcePathB1FBoulder);
    // CONVERTED_SCRIPT(IcePathB1FBoulder);
    // CONVERTED_SCRIPT(IcePathB1FBoulder);
    CONVERTED_SCRIPT(IcePathB1FIron);

    // maps/IcePathB2FBlackthornSide.c
    CONVERTED_SCRIPT(IcePathB2FBlackthornSideTMRest);

    // maps/IcePathB2FMahoganySide.c
    CONVERTED_SCRIPT(IcePathB2FMahoganySideBoulder);
    // CONVERTED_SCRIPT(IcePathB2FMahoganySideBoulder);
    // CONVERTED_SCRIPT(IcePathB2FMahoganySideBoulder);
    // CONVERTED_SCRIPT(IcePathB2FMahoganySideBoulder);
    CONVERTED_SCRIPT(IcePathB2FMahoganySideFullHeal);
    CONVERTED_SCRIPT(IcePathB2FMahoganySideMaxPotion);

    // maps/IcePathB3F.c
    CONVERTED_SCRIPT(IcePathB3FNevermeltice);
    CONVERTED_SCRIPT(IcePathB3FRock);

    // maps/DragonsDenB1F.c
    CONVERTED_SCRIPT(DragonsDenB1FDragonFangScript);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(DragonsDenB1FSilverScript);
    CONVERTED_SCRIPT(TrainerCooltrainermDarin);
    CONVERTED_SCRIPT(TrainerCooltrainerfCara);
    CONVERTED_SCRIPT(TrainerTwinsLeaandpia1);
    CONVERTED_SCRIPT(TrainerTwinsLeaandpia2);
    CONVERTED_SCRIPT(DragonsDenB1FCalcium);
    CONVERTED_SCRIPT(DragonsDenB1FMaxElixer);

    // maps/DragonShrine.c
    CONVERTED_SCRIPT(DragonShrineElder1Script);
    CONVERTED_SCRIPT(DragonShrineElder2Script);
    CONVERTED_SCRIPT(DragonShrineElder3Script);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/DarkCaveBlackthornEntrance.c
    CONVERTED_SCRIPT(DarkCaveBlackthornEntrancePharmacistScript);
    CONVERTED_SCRIPT(DarkCaveBlackthornEntranceRevive);
    CONVERTED_SCRIPT(DarkCaveBlackthornEntranceTMSnore);

    // maps/DarkCaveVioletEntrance.c
    CONVERTED_SCRIPT(DarkCaveVioletEntrancePotion);
    CONVERTED_SCRIPT(DarkCaveVioletEntranceRock);
    CONVERTED_SCRIPT(DarkCaveVioletEntranceRock);
    CONVERTED_SCRIPT(DarkCaveVioletEntranceRock);
    CONVERTED_SCRIPT(DarkCaveVioletEntranceRock);
    CONVERTED_SCRIPT(DarkCaveVioletEntranceFullHeal);
    CONVERTED_SCRIPT(DarkCaveVioletEntranceHyperPotion);
    CONVERTED_SCRIPT(DarkCaveVioletEntranceDireHit);

    // maps/TinTower1F.c
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(TinTower1FEusine);
    CONVERTED_SCRIPT(TinTower1FSage1Script);
    CONVERTED_SCRIPT(TinTower1FSage2Script);
    CONVERTED_SCRIPT(TinTower1FSage3Script);
    CONVERTED_SCRIPT(TinTower1FSage4Script);
    CONVERTED_SCRIPT(TinTower1FSage5Script);
    CONVERTED_SCRIPT(TinTower1FSage6Script);

    // maps/TinTower2F.c

    // maps/TinTower3F.c
    CONVERTED_SCRIPT(TinTower3FFullHeal);

    // maps/TinTower4F.c
    CONVERTED_SCRIPT(TinTower4FUltraBall);
    CONVERTED_SCRIPT(TinTower4FPPUp);
    CONVERTED_SCRIPT(TinTower4FEscapeRope);

    // maps/TinTower5F.c
    CONVERTED_SCRIPT(TinTower5FRareCandy);

    // maps/TinTower6F.c
    CONVERTED_SCRIPT(TinTower6FMaxPotion);

    // maps/TinTower7F.c
    CONVERTED_SCRIPT(TinTower7FMaxRevive);

    // maps/TinTower8F.c
    CONVERTED_SCRIPT(TinTower8FNugget);
    CONVERTED_SCRIPT(TinTower8FMaxElixer);
    CONVERTED_SCRIPT(TinTower8FFullRestore);

    // maps/TinTower9F.c
    CONVERTED_SCRIPT(TinTower9FHPUp);

    // maps/TinTowerRoof.c
    CONVERTED_SCRIPT(TinTowerHoOh);

    // maps/TohjoFalls.c
    CONVERTED_SCRIPT(TohjoFallsMoonStone);

    // maps/VictoryRoadGate.c
    CONVERTED_SCRIPT(VictoryRoadGateOfficerScript);
    CONVERTED_SCRIPT(VictoryRoadGateLeftBlackBeltScript);
    CONVERTED_SCRIPT(VictoryRoadGateRightBlackBeltScript);

    // maps/VictoryRoad.c
    // CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(VictoryRoadTMEarthquake);
    CONVERTED_SCRIPT(VictoryRoadMaxRevive);
    CONVERTED_SCRIPT(VictoryRoadFullRestore);
    CONVERTED_SCRIPT(VictoryRoadFullHeal);
    CONVERTED_SCRIPT(VictoryRoadHPUp);

    // maps/SilverCaveItemRooms.c
    CONVERTED_SCRIPT(SilverCaveItemRoomsMaxRevive);
    CONVERTED_SCRIPT(SilverCaveItemRoomsFullRestore);

    // maps/SilverCaveRoom1.c
    CONVERTED_SCRIPT(SilverCaveRoom1MaxElixer);
    CONVERTED_SCRIPT(SilverCaveRoom1Protein);
    CONVERTED_SCRIPT(SilverCaveRoom1EscapeRope);
    CONVERTED_SCRIPT(SilverCaveRoom1UltraBall);

    // maps/SilverCaveRoom2.c
    CONVERTED_SCRIPT(SilverCaveRoom2Calcium);
    CONVERTED_SCRIPT(SilverCaveRoom2UltraBall);
    CONVERTED_SCRIPT(SilverCaveRoom2PPUp);

    // maps/SilverCaveRoom3.c
    CONVERTED_SCRIPT(Red);

    // maps/FastShip1F.c
    CONVERTED_SCRIPT(FastShip1FSailor1Script);
    CONVERTED_SCRIPT(FastShip1FSailor2Script);
    CONVERTED_SCRIPT(FastShip1FSailor3Script);
    // CONVERTED_SCRIPT(ObjectEvent);

    // maps/FastShipB1F.c
    CONVERTED_SCRIPT(FastShipB1FSailorScript);
    CONVERTED_SCRIPT(FastShipB1FSailorScript);
    CONVERTED_SCRIPT(TrainerSailorJeff);
    CONVERTED_SCRIPT(TrainerPicnickerDebra);
    CONVERTED_SCRIPT(TrainerJugglerFritz);
    CONVERTED_SCRIPT(TrainerSailorGarrett);
    CONVERTED_SCRIPT(TrainerFisherJonah);
    CONVERTED_SCRIPT(TrainerBlackbeltWai);
    CONVERTED_SCRIPT(TrainerSailorKenneth);
    CONVERTED_SCRIPT(TrainerTeacherShirley);
    CONVERTED_SCRIPT(TrainerSchoolboyNate);
    CONVERTED_SCRIPT(TrainerSchoolboyRicky);

    // maps/FastShipCabins_NNW_NNE_NE.c
    CONVERTED_SCRIPT(TrainerCooltrainermSean);
    CONVERTED_SCRIPT(TrainerCooltrainerfCarol);
    CONVERTED_SCRIPT(TrainerPokemaniacEthan);
    CONVERTED_SCRIPT(TrainerHikerNoland);
    CONVERTED_SCRIPT(FastShipLazySailorScript);
    CONVERTED_SCRIPT(TrainerGentlemanEdward);
    CONVERTED_SCRIPT(TrainerBurglarCorey);

    // maps/FastShipCabins_SE_SSE_CaptainsCabin.c
    CONVERTED_SCRIPT(SSAquaCaptain);
    CONVERTED_SCRIPT(SSAquaGrandpa);
    CONVERTED_SCRIPT(SSAquaGranddaughterAfter);
    CONVERTED_SCRIPT(SSAquaGranddaughterBefore);
    CONVERTED_SCRIPT(TrainerPokefanmColin);
    CONVERTED_SCRIPT(TrainerTwinsMegandpeg1);
    CONVERTED_SCRIPT(TrainerTwinsMegandpeg2);
    CONVERTED_SCRIPT(TrainerPsychicRodney);
    CONVERTED_SCRIPT(TrainerPokefanmJeremy);
    CONVERTED_SCRIPT(TrainerPokefanfGeorgia);
    CONVERTED_SCRIPT(TrainerSupernerdShawn);

    // maps/FastShipCabins_SW_SSW_NW.c
    CONVERTED_SCRIPT(TrainerFirebreatherLyle);
    CONVERTED_SCRIPT(TrainerBugCatcherKen);
    CONVERTED_SCRIPT(TrainerBeautyCassie);
    CONVERTED_SCRIPT(TrainerGuitaristClyde);

    // maps/VermilionPort.c
    CONVERTED_SCRIPT(VermilionPortSailorAtGangwayScript);
    CONVERTED_SCRIPT(VermilionPortSailorScript);
    CONVERTED_SCRIPT(VermilionPortSuperNerdScript);

    // maps/VermilionPortPassage.c
    CONVERTED_SCRIPT(VermilionPortPassageTeacherScript);

    // maps/DiglettsCave.c
    CONVERTED_SCRIPT(DiglettsCavePokefanMScript);

    // maps/BillsHouse.c
    CONVERTED_SCRIPT(BillsGrandpa);

    // maps/MountMoon.c
    CONVERTED_SCRIPT(ObjectEvent);
    
    // maps/MountMoonSquare.c
    CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(ObjectEvent);
    CONVERTED_SCRIPT(MtMoonSquareRock);
    
    // maps/MountMoonGiftShop.c
    CONVERTED_SCRIPT(MountMoonGiftShopClerkScript);
    CONVERTED_SCRIPT(MountMoonGiftShopClerkScript);
    CONVERTED_SCRIPT(MountMoonGiftShopLassScript);
    CONVERTED_SCRIPT(MountMoonGiftShopLassScript);
    
    // maps/RockTunnel1F.c
    CONVERTED_SCRIPT(RockTunnel1FElixer);
    CONVERTED_SCRIPT(RockTunnel1FTMSteelWing);

    // maps/RockTunnelB1F.c
    CONVERTED_SCRIPT(RockTunnelB1FIron);
    CONVERTED_SCRIPT(RockTunnelB1FPPUp);
    CONVERTED_SCRIPT(RockTunnelB1FRevive);

    // maps/SeafoamGym.c
    CONVERTED_SCRIPT(SeafoamGymBlaineScript);
    CONVERTED_SCRIPT(SeafoamGymGuideScript);

    // maps/PowerPlant.c
    CONVERTED_SCRIPT(PowerPlantOfficerScript);
    CONVERTED_SCRIPT(PowerPlantGymGuide1Script);
    CONVERTED_SCRIPT(PowerPlantGymGuide2Script);
    CONVERTED_SCRIPT(PowerPlantOfficer2Script);
    CONVERTED_SCRIPT(PowerPlantGymGuide4Script);
    CONVERTED_SCRIPT(PowerPlantManager);
    CONVERTED_SCRIPT(Forest);

    // CableClubFriendScript
    CONVERTED_SCRIPT(CableClubFriendScript);

    // engine/events/overworld.c
    // REDIRECTED(Script_WaterfallFromMenu);
    // REDIRECTED(UseFlash);
    // REDIRECTED(Script_WhirlpoolFromMenu);
    // REDIRECTED(AskSurfScript);
    // REDIRECTED(Script_UseFlash);
    // REDIRECTED(TryWaterfallOW);
    // REDIRECTED(RockSmashFunction);
    // REDIRECTED(FieldMoveJumptableReset);
    // REDIRECTED(Script_GetOffBike_Register);
    // REDIRECTED(AskSurfText);
    // REDIRECTED(TryHeadbuttFromMenu);
    // REDIRECTED(BouldersMoveText);
    // REDIRECTED(UsedSurfText);
    // REDIRECTED(UseFlashTextScript);
    // REDIRECTED(FinishGettingOffBike);
    // REDIRECTED(CutDownTreeOrGrass);
    // REDIRECTED(HeadbuttNothingText);
    // REDIRECTED(AskHeadbuttText);
    // REDIRECTED(StrengthFunction);
    // REDIRECTED(UseHeadbuttText);
    CONVERTED(BikeFunction);
    // REDIRECTED(AskCutScript);
    // REDIRECTED(DigFunction);
    // REDIRECTED(PutTheRodAway);
    // REDIRECTED(UseRockSmashText);
    // REDIRECTED(Script_CantGetOffBike);
    // REDIRECTED(CheckEngineFlag);
    // REDIRECTED(Script_GetOffBike);
    // REDIRECTED(DisappearWhirlpool);
    // REDIRECTED(Script_NotEvenANibble);
    // REDIRECTED(UsedSurfScript);
    // REDIRECTED(Script_NotEvenANibble2);
    // REDIRECTED(TryHeadbuttOW);
    // REDIRECTED(RockSmashScript);
    // REDIRECTED(CheckMapForSomethingToCut);
    // REDIRECTED(FieldMoveFailed);
    // REDIRECTED(Script_GetOnBike_Register);
    // REDIRECTED(CheckBadge);
    // REDIRECTED(HeadbuttScript);
    // REDIRECTED(Script_NotEvenANibble_FallThrough);
    // REDIRECTED(MaySmashText);
    // REDIRECTED(AskRockSmashScript);
    // REDIRECTED(GetSurfType);
    // REDIRECTED(Script_AskWaterfall);
    // REDIRECTED(Overworld_DummyFunction);
    // REDIRECTED(AskHeadbuttScript);
    // REDIRECTED(GotOnBikeText);
    // REDIRECTED(CheckMapCanWaterfall);
    // REDIRECTED(FlashFunction);
    // REDIRECTED(CheckPartyMove);
    // REDIRECTED(Script_Cut);
    // REDIRECTED(UseWhirlpoolText);
    // REDIRECTED(Script_CantDoWaterfall);
    // REDIRECTED(Script_GotABite);
    // REDIRECTED(GetFacingObject);
    // REDIRECTED(CheckOverworldTileArrays);
    // REDIRECTED(WhirlpoolFunction);
    // REDIRECTED(MovementData_CastRod);
    // REDIRECTED(Script_MightyWhirlpool);
    // REDIRECTED(CantCutScript);
    // REDIRECTED(UseCutText);
    // REDIRECTED(CutNothingText);
    // REDIRECTED(AskRockSmashText);
    // REDIRECTED(AlreadySurfingText);
    // REDIRECTED(CanCutText);
    // REDIRECTED(TryCutOW);
    // REDIRECTED(Fishing_CheckFacingUp);
    // REDIRECTED(EscapeRopeOrDig);
    // REDIRECTED(AskStrengthScript);
    // REDIRECTED(WaterfallFunction);
    // REDIRECTED(Script_FishCastRod);
    // REDIRECTED(HeadbuttFunction);
    // REDIRECTED(AskCutText);
    CONVERTED(FishFunction);
    // REDIRECTED(TryWhirlpoolOW);
    // REDIRECTED(HasRockSmash);
    // REDIRECTED(RodNothingText);
    // REDIRECTED(TryWhirlpoolMenu);
    // REDIRECTED(FlyFunction);
    // REDIRECTED(TeleportFunction);
    // REDIRECTED(BouldersMayMoveText);
    // REDIRECTED(Script_UsedWhirlpool);
    // REDIRECTED(AskWhirlpoolText);
    // REDIRECTED(EscapeRopeFunction);
    // REDIRECTED(UnusedNothingHereText);
    // REDIRECTED(MovementData_RockSmash);
    // REDIRECTED(Script_CutFromMenu);
    // REDIRECTED(CutFunction);
    // REDIRECTED(SurfFunction);
    // REDIRECTED(CantSurfText);
    // REDIRECTED(GetPartyNickname);
    // REDIRECTED(HeadbuttFromMenuScript);
    // REDIRECTED(Script_AskWhirlpoolOW);
    // REDIRECTED(AskStrengthText);
    // REDIRECTED(TryRockSmashFromMenu);
    // REDIRECTED(Script_UsedStrength);
    // REDIRECTED(Script_UsedWaterfall);
    // REDIRECTED(Script_StrengthFromMenu);
    // REDIRECTED(RodBiteText);
    // REDIRECTED(Script_GetOnBike);
    // REDIRECTED(SetStrengthFlag);
    // REDIRECTED(TryStrengthOW);
    // REDIRECTED(TrySurfOW);
    // REDIRECTED(CheckDirection);
    // REDIRECTED(FieldMoveJumptable);
    // REDIRECTED(SurfFromMenuScript);
    // REDIRECTED(GotOffBikeText);
    // REDIRECTED(RockSmashFromMenuScript);

    // engine/events/field_moves.c
    // REDIRECTED(OWCutJumptable);
    // REDIRECTED(Cut_SpawnLeaf);
    // REDIRECTED(Cut_Headbutt_GetPixelFacing);
    // REDIRECTED(Cut_GetLeafSpawnCoords);
    // REDIRECTED(HeadbuttTreeGFX);
    // REDIRECTED(FlyFunction_InitGFX);
    // REDIRECTED(CutTreeGFX);
    // REDIRECTED(PlayWhirlpoolSound);
    // REDIRECTED(OWCutAnimation);
    // REDIRECTED(Cut_StartWaiting);
    // REDIRECTED(Cut_WaitAnimSFX);
    // REDIRECTED(Cut_SpawnAnimateTree);
    // REDIRECTED(ShakeHeadbuttTree);
    // REDIRECTED(FlyFromAnim);
    // REDIRECTED(FlyToAnim);
    // REDIRECTED(HideHeadbuttTree);
    // REDIRECTED(Cut_SpawnAnimateLeaves);
    // REDIRECTED(TreeRelativeLocationTable);
    // REDIRECTED(FlyFunction_FrameTimer);
    // REDIRECTED(BlindingFlash);
    // REDIRECTED(CutGrassGFX);

    // engine/events/unown_walls.c
    // REDIRECTED(v_DisplayUnownWords_CopyWord);
    // REDIRECTED(DisplayUnownWords);
    // REDIRECTED(SpecialKabutoChamber);
    // REDIRECTED(SpecialAerodactylChamber);
    // REDIRECTED(v_DisplayUnownWords_FillAttr);
    CONVERTED(HoOhChamber);
    CONVERTED(OmanyteChamber);

    // engine/events/std_collision.c
    // REDIRECTED(Script_JumpStdFromRAM);
    // REDIRECTED(CheckFacingTileForStdScript);

    // engine/menus/options_menu.c
    // REDIRECTED(GetTextSpeed);
    // REDIRECTED(GetOptionPointer);
    // REDIRECTED(Options_MenuAccount);
    // REDIRECTED(Options_Cancel);
    // REDIRECTED(StringOptions);
    CONVERTED(v_Option);
    // REDIRECTED(Options_Sound);
    // REDIRECTED(GetPrinterSetting);
    // REDIRECTED(Options_BattleStyle);
    // REDIRECTED(Options_Print);
    // REDIRECTED(Options_TextSpeed);
    // REDIRECTED(Options_Frame);
    // REDIRECTED(Options_BattleScene);
    // REDIRECTED(UpdateFrame);
    // REDIRECTED(OptionsControl);
    // REDIRECTED(Options_UpdateCursorPosition);

    // engine/events/checksave.c
    REDIRECTED(CheckSave);

    // engine/overworld/decorations.c
    // REDIRECTED(GetDecorationFlag);
    // REDIRECTED(DecoExitMenu);
    // REDIRECTED(DescribeDecoration);
    // REDIRECTED(WhichSidePutAwayText);
    // REDIRECTED(PutAwayTheDecoText);
    // REDIRECTED(DecoAction_setupplant);
    // REDIRECTED(DecorationDesc_TownMapPoster);
    // REDIRECTED(DecoAction_putawayposter);
    // REDIRECTED(DecorationDesc_JigglypuffPoster);
    // REDIRECTED(DecoPlantMenu);
    // REDIRECTED(CheckAllDecorationFlags);
    // REDIRECTED(AlreadySetUpText);
    // REDIRECTED(DecoAction_setupbigdoll);
    // REDIRECTED(DecorationMenuFunction);
    // REDIRECTED(FindOwnedCarpets);
    // REDIRECTED(DecoOrnamentMenu);
    // REDIRECTED(DecorationDesc_LeftOrnament);
    // REDIRECTED(DecorationDesc_PikachuPoster);
    // REDIRECTED(DecoAction_putawayornament);
    // REDIRECTED(DecoAction_TrySetItUp);
    // REDIRECTED(DecorationFlagAction_c);
    // REDIRECTED(DecoPosterMenu);
    // REDIRECTED(DecoAction_putawayconsole);
    // REDIRECTED(DecoAction_setupbed);
    // REDIRECTED(FindOwnedDecosInCategory);
    // REDIRECTED(DecoCarpetMenu);
    // REDIRECTED(DecorationDesc_Poster);
    // REDIRECTED(SetPosterVisibility);
    // REDIRECTED(FindOwnedBigDolls);
    // REDIRECTED(ToggleDecorationVisibility);
    // REDIRECTED(AppendDecoIndex);
    // REDIRECTED(DecoAction_SetItUp_Ornament);
    // REDIRECTED(DecoBigDollMenu);
    // REDIRECTED(DecoAction_setupposter);
    // REDIRECTED(DecoAction_putawaybigdoll);
    // REDIRECTED(v_PlayerDecorationMenu);
    // REDIRECTED(DecorationDesc_NullPoster);
    // REDIRECTED(SetAllDecorationFlags);
    // REDIRECTED(GetDecoName);
    // REDIRECTED(DecoAction_setupcarpet);
    // REDIRECTED(GetDecorationSprite);
    CONVERTED(ToggleMaptileDecorations);
    // REDIRECTED(DecoAction_FinishUp_Ornament);
    // REDIRECTED(GetDecorationName);
    CONVERTED(ToggleDecorationsVisibility);
    // REDIRECTED(PopulateDecoCategoryMenu);
    // REDIRECTED(DecoAction_TryPutItAway);
    // REDIRECTED(DecoConsoleMenu);
    // REDIRECTED(DecoAction_PutItAway_Ornament);
    // REDIRECTED(FindOwnedPosters);
    // REDIRECTED(DecorationDesc_GiantOrnament);
    // REDIRECTED(GetDecorationData);
    // REDIRECTED(SetUpTheDecoText);
    // REDIRECTED(DecoAction_setupconsole);
    // REDIRECTED(DecorationDesc_ClefairyPoster);
    // REDIRECTED(DecoSideMenuHeader);
    // REDIRECTED(DecorationDesc_RightOrnament);
    // REDIRECTED(DoDecorationAction2);
    // REDIRECTED(FindOwnedPlants);
    // REDIRECTED(DecorationFlagAction);
    // REDIRECTED(DecoAction_SetItUp);
    // REDIRECTED(v_GetDecorationSprite);
    // REDIRECTED(DecorationDesc_PosterPointers);
    // REDIRECTED(DecoAction_putawaycarpet);
    // REDIRECTED(SetSpecificDecorationFlag);
    // REDIRECTED(DecorationDesc_Console);
    // REDIRECTED(DecoAction_setupornament);
    // REDIRECTED(FindOwnedConsoles);
    // REDIRECTED(DecoAction_putawayplant);
    // REDIRECTED(PutAwayAndSetUpText);
    // REDIRECTED(DecoAction_AskWhichSide);
    // REDIRECTED(DecoBedMenu);
    // REDIRECTED(GetDecorationID);
    // REDIRECTED(FindOwnedOrnaments);
    // REDIRECTED(DecoAction_putawaybed);
    // REDIRECTED(GetDecorationName_c_de);
    // REDIRECTED(PadCoords_de);
    // REDIRECTED(WhichSidePutOnText);
    // REDIRECTED(SetDecorationTile);
    // REDIRECTED(FindOwnedBeds);
    // REDIRECTED(QueryWhichSide);
    CONVERTED(InitDecorations);
    // REDIRECTED(Deco_FillTempWithMinusOne);
    // REDIRECTED(DecoAction_nothing);
    // REDIRECTED(DecorationDesc_OrnamentOrConsole);
    // REDIRECTED(NothingToPutAwayText);
    // REDIRECTED(GetDecorationName_c);

    // engine/events/treemons.c
    // REDIRECTED(NoTreeMon);
    // REDIRECTED(SelectTreeMon);
    // REDIRECTED(GetTreeScore);
    CONVERTED(RockMonEncounter);
    // REDIRECTED(GetTreeMons);
    // REDIRECTED(GetTreeMon);
    // REDIRECTED(GetTreeMonSet);
    CONVERTED(TreeMonEncounter);

    // engine/menus/save.c
    // REDIRECTED(TryLoadSaveFile);
    // REDIRECTED(ResumeGameLogic);
    // REDIRECTED(ErasePreviousSave);
    // REDIRECTED(SaveTheGame_yesorno);
    // REDIRECTED(SavePokemonData);
    // REDIRECTED(SaveBackupOptions);
    // REDIRECTED(BoxAddresses);
    // REDIRECTED(ChangeBoxSaveText);
    // REDIRECTED(EraseBoxes);
    // REDIRECTED(SaveAfterLinkTrade);
    // REDIRECTED(MoveMonWOMail_SaveGame);
    // REDIRECTED(EraseLinkBattleStats);
    // REDIRECTED(SaveBackupPlayerData);
    // REDIRECTED(SaveBackupChecksum);
    CONVERTED(TryLoadSaveData);
    // REDIRECTED(VerifyBackupChecksum);
    // REDIRECTED(FindStackTop);
    // REDIRECTED(SaveChecksum);
    CONVERTED(SavingDontTurnOffThePower);
    // REDIRECTED(StartMoveMonWOMail_SaveGame);
    // REDIRECTED(v_SaveGameData);
    // REDIRECTED(EraseBattleTowerStatus);
    // REDIRECTED(SaveMenu);
    // REDIRECTED(VerifyChecksum);
    // REDIRECTED(Function14d6c);
    // REDIRECTED(SaveFileCorruptedText);
    // REDIRECTED(AskOverwriteSaveFile);
    // REDIRECTED(GetBoxAddress);
    // REDIRECTED(SavedTheGameText);
    // REDIRECTED(LoadBackupPlayerData);
    // REDIRECTED(SavePlayerData);
    // REDIRECTED(v_SavingDontTurnOffThePower);
    // REDIRECTED(SaveGameData);
    // REDIRECTED(ValidateSave);
    // REDIRECTED(MoveMonWOMailSaveText);
    // REDIRECTED(SaveBoxAddress);
    // REDIRECTED(Link_SaveGame);
    // REDIRECTED(v_LoadData);
    // REDIRECTED(LoadBox);
    // REDIRECTED(v_SaveData);
    // REDIRECTED(ChangeBoxSaveGame);
    // REDIRECTED(AnotherSaveFileText);
    // REDIRECTED(Checksum);
    // REDIRECTED(SaveData);
    // REDIRECTED(CompareLoadedAndSavedPlayerID);
    // REDIRECTED(PauseGameLogic);
    // REDIRECTED(MoveMonWOMail_InsertMon_SaveGame);
    // REDIRECTED(SaveOptions);
    // REDIRECTED(Function14d93);
    // REDIRECTED(HallOfFame_InitSaveIfNeeded);
    // REDIRECTED(UpdateStackTop);
    // REDIRECTED(Function14d18);
    // REDIRECTED(LoadBackupPokemonData);
    // REDIRECTED(AlreadyASaveFileText);
    // REDIRECTED(AddHallOfFameEntry);
    // REDIRECTED(LoadPokemonData);
    // REDIRECTED(CheckBackupSaveFile);
    // REDIRECTED(LoadPlayerData);
    // REDIRECTED(CheckPrimarySaveFile);
    // REDIRECTED(LoadBoxAddress);
    // REDIRECTED(SavedTheGame);
    // REDIRECTED(EraseHallOfFame);
    // REDIRECTED(ValidateBackupSave);
    // REDIRECTED(SaveBackupPokemonData);
    // REDIRECTED(EraseMysteryGift);
    // REDIRECTED(WouldYouLikeToSaveTheGameText);
    // REDIRECTED(Function14d83);
    // REDIRECTED(SavingDontTurnOffThePowerText);
    // REDIRECTED(SaveBox);

    // engine/link/mystery_gift.c
    // REDIRECTED(CopyMysteryGiftReceivedDecorationsToPC);
    // REDIRECTED(ReceiveInfraredLEDOn);
    // REDIRECTED(BackupMysteryGift);
    // REDIRECTED(ReceiveNameCardDataPayload);
    // REDIRECTED(ReceiveMysteryGiftDataPayload);
    // REDIRECTED(SendIRDataBlock);
    // REDIRECTED(ReceiveInfraredLEDOff);
    // REDIRECTED(ExchangeNameCardData);
    // REDIRECTED(ToggleIRCommunication);
    // REDIRECTED(CardTradeGFX);
    // REDIRECTED(SendMysteryGiftDataPayload);
    // REDIRECTED(ReceivedWrongIRChecksum);
    // REDIRECTED(StartSlowIRTimer);
    // REDIRECTED(InfraredLEDReceiveTimedOut);
    // REDIRECTED(ReceiveMysteryGiftDataPayload_GotRegionPrefix);
    CONVERTED(DoMysteryGift);
    // REDIRECTED(ReceivedWrongIRMessagePrefix);
    // REDIRECTED(ClearMysteryGiftTrainer);
    // REDIRECTED(UnlockMysteryGift);
    // REDIRECTED(InitializeIRCommunicationInterrupts);
    // REDIRECTED(SendIRHelloMessageAfterDelay);
    // REDIRECTED(EndNameCardIRCommunication);
    // REDIRECTED(SendEmptyIRDataBlock);
    // REDIRECTED(ResetDailyMysteryGiftLimitIfUnlocked);
    // REDIRECTED(ExchangeMysteryGiftData);
    // REDIRECTED(ReceiverExchangeMysteryGiftDataPayloads_GotPayload);
    // REDIRECTED(SendIRHelloMessage);
    // REDIRECTED(StagePartyDataForMysteryGift);
    // REDIRECTED(BeginReceivingIRCommunication);
    // REDIRECTED(StartFastIRTimer);
    // REDIRECTED(SendInfraredLEDOn);
    // REDIRECTED(TrySendingIRDataBlock);
    // REDIRECTED(GetMysteryGiftBank);
    // REDIRECTED(InitNameCardLayout);
    // REDIRECTED(ReceiverExchangeMysteryGiftDataPayloads);
    // REDIRECTED(MysteryGift_UpdateJoypad);
    // REDIRECTED(WrongMysteryGiftRegion);
    // REDIRECTED(CheckAndSetMysteryGiftDecorationAlreadyReceived);
    // REDIRECTED(EndIRCommunication);
    // REDIRECTED(ReceiveIRDataMessage);
    // REDIRECTED(InitMysteryGiftLayout);
    // REDIRECTED(MysteryGiftGFX);
    // REDIRECTED(CardTradeSpriteGFX);
    // REDIRECTED(InitializeIRCommunicationRoles);
    // REDIRECTED(SendIRDataMessage);
    // REDIRECTED(SendNameCardDataPayload);
    // REDIRECTED(RestoreMysteryGift);
    // REDIRECTED(TryReceivingIRDataBlock);
    // REDIRECTED(DoNameCardSwap);
    // REDIRECTED(EndOrContinueMysteryGiftIRCommunication);
    // REDIRECTED(ReceiveEmptyIRDataBlock);
    // REDIRECTED(StageDataForNameCard);
    // REDIRECTED(BeginSendingIRCommunication);
    // REDIRECTED(SendInfraredLEDOff);
    // REDIRECTED(ReceiveIRHelloMessage);
    // REDIRECTED(ReceiveIRDataBlock);
    // REDIRECTED(BeginIRCommunication);
    // REDIRECTED(SenderExchangeMysteryGiftDataPayloads);

    // engine/pokemon/mail.c
    // REDIRECTED(SendMailToPC);
    // REDIRECTED(DeleteMailFromPC);
    // REDIRECTED(v_PlayerMailBoxMenu);
    // REDIRECTED(MoveMailFromPCToParty);
    // REDIRECTED(InitMail);
    // REDIRECTED(BackupPartyMonMail);
    // REDIRECTED(MailboxPC_PrintMailAuthor);
    // REDIRECTED(GivePokeMail);
    // REDIRECTED(IsAnyMonHoldingMail);
    // REDIRECTED(CheckPokeMail);
    // REDIRECTED(GetMailboxCount);
    // REDIRECTED(RestorePartyMonMail);
    // REDIRECTED(MailboxPC_GetMailAuthor);
    // REDIRECTED(ReadMailMessage);
    // REDIRECTED(MailboxPC);
    // REDIRECTED(DeletePartyMonMail);

    // engine/events/fishing_gfx.c
    CONVERTED(LoadFishingGFX);
    // REDIRECTED(FishingGFX);
    // REDIRECTED(KrisFishingGFX);

    // engine/items/pack.c
    // REDIRECTED(GiveItem);
    // REDIRECTED(Pack_InitGFX);
    // REDIRECTED(Pack_PrintTextNoScroll);
    // REDIRECTED(DepositSellInitPackBuffers);
    // REDIRECTED(ItemSubmenu);
    // REDIRECTED(DrawPackGFX);
    // REDIRECTED(Jumptable_UseGiveTossRegisterQuit);
    // REDIRECTED(PC_Mart_BallsPocketMenuHeader);
    // REDIRECTED(WaitBGMap_DrawPackGFX);
    // REDIRECTED(QuitItemSubmenu);
    // REDIRECTED(DepositSellPack);
    // REDIRECTED(CantRegisterText);
    // REDIRECTED(YouCantUseItInABattleText);
    // REDIRECTED(AskItemMoveText);
    // REDIRECTED(MenuHeader_HoldableItem);
    // REDIRECTED(RegisteredItemText);
    // REDIRECTED(Pack_QuitRunScript);
    // REDIRECTED(PackEmptyText);
    // REDIRECTED(Pack_QuitNoScript);
    // REDIRECTED(PackMenuGFX);
    // REDIRECTED(Jumptable_GiveTossRegisterQuit);
    // REDIRECTED(YouDontHaveAMonText);
    // REDIRECTED(BattlePack);
    // REDIRECTED(DepositSellTutorial_InterpretJoypad);
    // REDIRECTED(PC_Mart_KeyItemsPocketMenuHeader);
    // REDIRECTED(InitPackBuffers);
    // REDIRECTED(OakThisIsntTheTimeText);
    // REDIRECTED(TossMenu);
    // REDIRECTED(Pack_ClearTilemap);
    // REDIRECTED(KeyItemsPocketMenuHeader);
    // REDIRECTED(AskQuantityThrowAwayText);
    // REDIRECTED(Pack_JumptableNext);
    // REDIRECTED(ItemsPocketMenuHeader);
    // REDIRECTED(ResetPocketCursorPositions);
    // REDIRECTED(Pack);
    // REDIRECTED(Jumptable_UseRegisterQuit);
    // REDIRECTED(PackGFXPointers);
    // REDIRECTED(PlacePackGFX);
    // REDIRECTED(PackGFX);
    // REDIRECTED(PackNoItemText);
    // REDIRECTED(Pack_InterpretJoypad);
    // REDIRECTED(Pack_InitColors);
    // REDIRECTED(Jumptable_UseGiveTossQuit);
    // REDIRECTED(Pack_GetJumptablePointer);
    // REDIRECTED(MenuHeader_UsableKeyItem);
    // REDIRECTED(RegisterItem);
    // REDIRECTED(Pack_GetItemName);
    // REDIRECTED(MenuHeader_HoldableKeyItem);
    // REDIRECTED(BallsPocketMenuHeader);
    // REDIRECTED(Jumptable_GiveTossQuit);
    CONVERTED(UseItem);
    // REDIRECTED(Jumptable_UseQuit);
    // REDIRECTED(MenuHeader_UnusableItem);
    // REDIRECTED(TMHMSubmenu);
    // REDIRECTED(DrawPocketName);
    // REDIRECTED(ThrewAwayText);
    // REDIRECTED(MenuHeader_UnusableKeyItem);
    // REDIRECTED(MenuHeader_UsableItem);
    // REDIRECTED(AskThrowAwayText);
    // REDIRECTED(TutorialPack);
    // REDIRECTED(InitPocket);
    // REDIRECTED(PC_Mart_ItemsPocketMenuHeader);
    // REDIRECTED(ClearPocketList);

    // engine/items/pack_kris.c
    // REDIRECTED(DrawKrisPackGFX);
    // REDIRECTED(PackFGFXPointers);
    // REDIRECTED(PackFGFX);

    // engine/items/update_item_description.c
    // CONVERTED(UpdateItemDescription);

    // engine/items/print_item_description.c
    // REDIRECTED(PrintItemDescription);

    // engine/pokemon/print_move_description.c
    // REDIRECTED(PrintMoveDescription);

    // engine/menus/scrolling_menu.c
    // REDIRECTED(ScrollingMenu_InitDisplay);
    // REDIRECTED(v_ScrollingMenu);
    // REDIRECTED(ScrollingMenu_CheckCallFunction3);
    // REDIRECTED(ScrollingMenu_PlaceCursor);
    // REDIRECTED(ScrollingMenu_CallFunctions1and2);
    // REDIRECTED(ScrollingMenuJoyAction);
    // REDIRECTED(v_InitScrollingMenu);
    // REDIRECTED(InitScrollingMenuCursor);
    // REDIRECTED(ScrollingMenu_GetCursorPosition);
    // REDIRECTED(ScrollingMenu_ValidateSwitchItem);
    // REDIRECTED(ScrollingMenu_UpdateDisplay);
    // REDIRECTED(ScrollingMenu_ClearLeftColumn);
    // REDIRECTED(ScrollingMenu_GetListItemCoordAndFunctionArgs);
    // REDIRECTED(ScrollingMenu_InitFlags);

    // engine/items/tmhm.c
    // REDIRECTED(Tutorial_TMHMPocket);
    CONVERTED(TMHMPocket);
    // REDIRECTED(TMHM_ExitPack);
    // REDIRECTED(TMHM_ExitPocket);
    // REDIRECTED(BootedHMText);
    // REDIRECTED(TMHM_ShowTMMoveDescription);
    // REDIRECTED(TMHM_JoypadLoop);
    // REDIRECTED(TMHMPocket_GetCurrentLineCoord);
    // REDIRECTED(v_TMHM_ExitPack);
    // REDIRECTED(TMHMNotCompatibleText);
    // REDIRECTED(TMHM_ScrollPocket);
    // REDIRECTED(TMHM_GetCurrentPocketPosition);
    // REDIRECTED(ChooseMonToLearnTMHM);
    // REDIRECTED(TMHM_PlaySFX_ReadText2);
    // REDIRECTED(ConsumeTM);
    // REDIRECTED(TMHM_CheckHoveringOverCancel);
    // REDIRECTED(AskTeachTMHM);
    // REDIRECTED(PlaceMoveNameAfterTMHMName);
    // REDIRECTED(TMHM_ChooseTMorHM);
    // REDIRECTED(TMHM_DisplayPocketItems);
    // REDIRECTED(ChooseMonToLearnTMHM_NoRefresh);
    // REDIRECTED(TMHM_PocketLoop);
    // REDIRECTED(VerboseReceiveTMHM);
    // REDIRECTED(TeachTMHM);
    // REDIRECTED(ContainedMoveText);
    // REDIRECTED(ConvertCurItemIntoCurTMHM);
    // REDIRECTED(CountTMsHMs);
    // REDIRECTED(TMHM_CancelString);
    // REDIRECTED(GetTMHMItemMove);
    // REDIRECTED(BootedTMText);

    // engine/items/tmhm2.c
    // REDIRECTED(GetTMHMMove);
    // REDIRECTED(CanLearnTMHMMove);

    // engine/items/mart.c
    // REDIRECTED(ReadMart);
    // REDIRECTED(GetMartPrice);
    // REDIRECTED(PharmacyComeAgainText);
    // REDIRECTED(BuyMenu);
    // REDIRECTED(PharmacyHowManyText);
    // REDIRECTED(MartSellHowManyText);
    // REDIRECTED(HerbalLadyFinalPriceText);
    // REDIRECTED(GetMartDialogGroup);
    // REDIRECTED(HerbalLadyComeAgainText);
    // REDIRECTED(PharmacyIntroText);
    // REDIRECTED(BuyMenuLoop);
    // REDIRECTED(HerbShopLadyIntroText);
    // REDIRECTED(RooftopSale);
    // REDIRECTED(BargainShopNoFundsText);
    // REDIRECTED(BargainShop);
    // REDIRECTED(FarReadMart);
    // REDIRECTED(GetMartItemPrice);
    // REDIRECTED(PharmacyFinalPriceText);
    // REDIRECTED(MartAskMoreText);
    // REDIRECTED(BargainShopAskPurchaseQuantity);
    // REDIRECTED(MartWelcomeText);
    // REDIRECTED(GetMart);
    // REDIRECTED(MartThanksText);
    // REDIRECTED(PharmacyThanksText);
    // REDIRECTED(MartNoMoneyText);
    // REDIRECTED(HerbalLadyPackFullText);
    // REDIRECTED(MartTextbox);
    // REDIRECTED(BargainShopThanksText);
    // REDIRECTED(BargainShopComeAgainText);
    // REDIRECTED(MartDialog);
    // REDIRECTED(PharmacyPackFullText);
    // REDIRECTED(BargainShopPackFullText);
    // REDIRECTED(MartConfirmPurchase);
    // REDIRECTED(HerbalLadyThanksText);
    // REDIRECTED(LoadBuyMenuText);
    // REDIRECTED(RooftopSaleAskPurchaseQuantity);
    // REDIRECTED(MartHowManyText);
    // REDIRECTED(SellMenu);
    // REDIRECTED(MenuHeader_Buy);
    // REDIRECTED(BargainShopIntroText);
    // REDIRECTED(UnusedDummyString);
    // REDIRECTED(LoadMartPointer);
    // REDIRECTED(PlayTransactionSound);
    // REDIRECTED(Pharmacist);
    // REDIRECTED(HerbShop);
    // REDIRECTED(MenuHeader_BuySell);
    // REDIRECTED(BargainShopSoldOutText);
    // REDIRECTED(MartCantBuyText);
    // REDIRECTED(HerbalLadyHowManyText);
    // REDIRECTED(MartFinalPriceText);
    // REDIRECTED(StandardMartAskPurchaseQuantity);
    // REDIRECTED(MartPackFullText);
    // REDIRECTED(MartComeAgainText);
    // REDIRECTED(StandardMart);
    // REDIRECTED(HerbalLadyNoMoneyText);
    // REDIRECTED(BargainShopFinalPriceText);
    REDIRECTED(OpenMartDialog);
    // REDIRECTED(MartBoughtText);
    // REDIRECTED(MartSellPriceText);
    // REDIRECTED(PharmacyNoMoneyText);
    // REDIRECTED(MartAskPurchaseQuantity);

    // engine/items/buy_sell_toss.c
    // REDIRECTED(SelectQuantityToToss);
    // REDIRECTED(BuySell_MultiplyPrice);
    // REDIRECTED(BuySellToss_InterpretJoypad);
    // REDIRECTED(DisplayPurchasePrice);
    // REDIRECTED(BuySellToss_UpdateQuantityDisplay);
    // REDIRECTED(NoPriceToDisplay);
    // REDIRECTED(Sell_HalvePrice);
    // REDIRECTED(BuySell_DisplaySubtotal);
    // REDIRECTED(TossItem_MenuHeader);
    // REDIRECTED(SelectQuantityToBuy);
    // REDIRECTED(DisplaySellingPrice);
    // REDIRECTED(Toss_Sell_Loop);
    // REDIRECTED(SelectQuantityToSell);
    // REDIRECTED(BuyItem_MenuHeader);
    // REDIRECTED(SellItem_MenuHeader);
    // REDIRECTED(RooftopSale_SelectQuantityToBuy);

    // engine/pokemon/mon_menu.c
    // REDIRECTED(PrepareToPlaceMoveData);
    // REDIRECTED(MoveScreenLoop);
    // REDIRECTED(MoveScreen2DMenuData);
    // REDIRECTED(PokemonTookItemText);
    // REDIRECTED(DeleteMoveScreen2DMenuData);
    // REDIRECTED(TryGiveItemToPartymon);
    // REDIRECTED(PlaceMoveScreenLeftArrow);
    // REDIRECTED(TossItemFromPC);
    // REDIRECTED(OpenPartyStats);
    // REDIRECTED(PokemonRemoveMailText);
    // REDIRECTED(MonMenu_Fly);
    // REDIRECTED(MonMenu_Dig);
    // REDIRECTED(MonMenu_SweetScent);
    // REDIRECTED(SetUpMoveScreenBG);
    // REDIRECTED(MonMenu_Surf);
    // REDIRECTED(String_MoveType_Bottom);
    // REDIRECTED(TakePartyItem);
    // REDIRECTED(MonMenu_Teleport);
    // REDIRECTED(PokemonSwapItemText);
    // REDIRECTED(MonMenu_Whirlpool);
    // REDIRECTED(CancelPokemonAction);
    // REDIRECTED(MonMenu_Strength);
    // REDIRECTED(StartMenuYesNo);
    // REDIRECTED(SetUpMoveList);
    // REDIRECTED(PlaceMoveScreenArrows);
    // REDIRECTED(ManagePokemonMoves);
    // REDIRECTED(GiveTakeItemMenuData);
    // REDIRECTED(GetPartyItemLocation);
    // REDIRECTED(ReceiveItemFromPokemon);
    // REDIRECTED(GiveItemToPokemon);
    // REDIRECTED(String_MoveNoPower);
    // REDIRECTED(ItemCantHeldText);
    // REDIRECTED(MonMenu_Headbutt);
    // REDIRECTED(PokemonActionSubmenu);
    // REDIRECTED(GivePartyItem);
    // REDIRECTED(ItemStorageFullText);
    // REDIRECTED(PokemonAskSwapItemText);
    // REDIRECTED(PlaceMoveData);
    // REDIRECTED(PokemonNotHoldingText);
    // REDIRECTED(String_MoveAtk);
    // REDIRECTED(MonMailAction);
    // REDIRECTED(SwitchPartyMons);
    // REDIRECTED(PartyMonItemName);
    // REDIRECTED(PokemonHoldItemText);
    // REDIRECTED(GiveTakePartyMonItem);
    // REDIRECTED(MonMenu_Flash);
    // REDIRECTED(ChooseMoveToDelete);
    // REDIRECTED(MonMenu_Cut);
    // REDIRECTED(MonMenu_Waterfall);
    // REDIRECTED(HasNoItems);
    // REDIRECTED(ItemsOakWarningText);
    // REDIRECTED(MonMenu_Softboiled_MilkDrink);
    // REDIRECTED(CantUseItem);
    // REDIRECTED(String_MoveWhere);
    // REDIRECTED(String_MoveType_Top);
    // REDIRECTED(MonMenu_RockSmash);
    // REDIRECTED(PlaceMoveScreenRightArrow);
    // REDIRECTED(ComposeMailMessage);

    // engine/tilesets/tileset_anims.c
    // REDIRECTED(WriteTileFromAnimBuffer);
    // REDIRECTED(DoneTileAnimation);
    // REDIRECTED(TilesetHouseAnim);
    // REDIRECTED(TilesetOmanyteWordRoomAnim);
    // REDIRECTED(AnimateWaterTile);
    // REDIRECTED(TilesetPlayersHouseAnim);
    // REDIRECTED(WhirlpoolFrames2);
    // REDIRECTED(TowerPillarTile1);
    // REDIRECTED(TowerPillarTilePointer5);
    // REDIRECTED(TowerPillarTilePointer7);
    // REDIRECTED(AnimateTowerPillarTile);
    // REDIRECTED(ForestTreeLeftAnimation2);
    // REDIRECTED(TilesetMansionAnim);
    // REDIRECTED(UnusedTilesetAnim2);
    // REDIRECTED(TowerPillarTile6);
    // REDIRECTED(ForestTreeLeftAnimation);
    // REDIRECTED(TowerPillarTilePointer10);
    // REDIRECTED(GetForestTreeFrame);
    // REDIRECTED(TowerPillarTile8);
    // REDIRECTED(AnimateLavaBubbleTile2);
    // REDIRECTED(TilesetEliteFourRoomAnim);
    // REDIRECTED(ScrollTileRightLeft);
    // REDIRECTED(TilesetTrainStationAnim);
    // REDIRECTED(TilesetPokecenterAnim);
    // REDIRECTED(WhirlpoolFrames3);
    // REDIRECTED(TilesetJohtoAnim);
    // REDIRECTED(AnimateFlowerTile);
    // REDIRECTED(TilesetKantoAnim);
    // REDIRECTED(TilesetBetaWordRoomAnim);
    // REDIRECTED(TowerPillarTilePointer6);
    // REDIRECTED(TilesetBattleTowerInsideAnim);
    // REDIRECTED(WhirlpoolTiles1);
    // REDIRECTED(TowerPillarTilePointer1);
    // REDIRECTED(TowerPillarTile4);
    // REDIRECTED(WhirlpoolFrames1);
    // REDIRECTED(ScrollTileLeft);
    // REDIRECTED(UnusedTilesetAnim5);
    // REDIRECTED(WhirlpoolFrames4);
    // REDIRECTED(TilesetMartAnim);
    // REDIRECTED(TilesetTowerAnim);
    // REDIRECTED(ReadTileToAnimBuffer);
    // REDIRECTED(TowerPillarTile3);
    // REDIRECTED(TilesetPokeComCenterAnim);
    // REDIRECTED(WhirlpoolTiles4);
    // REDIRECTED(TowerPillarTilePointer9);
    // REDIRECTED(TilesetAerodactylWordRoomAnim);
    // REDIRECTED(StandingTileFrame8);
    // REDIRECTED(TilesetParkAnim);
    // REDIRECTED(UnusedTilesetAnim1);
    // REDIRECTED(ForestTreeLeftFrames);
    // REDIRECTED(TowerPillarTile5);
    // REDIRECTED(TowerPillarTilePointer8);
    // REDIRECTED(AnimateWhirlpoolTile);
    // REDIRECTED(TowerPillarTilePointer2);
    // REDIRECTED(TilesetChampionsRoomAnim);
    // REDIRECTED(WhirlpoolTiles2);
    // REDIRECTED(TilesetForestAnim);
    // REDIRECTED(ScrollTileDown);
    // REDIRECTED(TilesetFacilityAnim);
    // REDIRECTED(ForestTreeRightAnimation);
    // REDIRECTED(TowerPillarTile10);
    // REDIRECTED(TilesetBattleTowerOutsideAnim);
    // REDIRECTED(WaitTileAnimation);
    // REDIRECTED(TilesetIcePathAnim);
    // REDIRECTED(StandingTileFrame);
    // REDIRECTED(TilesetRuinsOfAlphAnim);
    // REDIRECTED(TowerPillarTile9);
    // REDIRECTED(ScrollTileUp);
    // REDIRECTED(WhirlpoolTiles3);
    // REDIRECTED(AnimateFountainTile);
    // REDIRECTED(TilesetDarkCaveAnim);
    // REDIRECTED(TilesetPlayersRoomAnim);
    // REDIRECTED(TowerPillarTile2);
    // REDIRECTED(LavaBubbleTileFrames);
    // REDIRECTED(FlickeringCaveEntrancePalette);
    // REDIRECTED(ScrollTileUpDown);
    // REDIRECTED(TilesetLabAnim);
    // REDIRECTED(TowerPillarTilePointer3);
    // REDIRECTED(ForestTreeRightFrames);
    // REDIRECTED(ScrollTileRight);
    // REDIRECTED(TowerPillarTile7);
    // REDIRECTED(TilesetTraditionalHouseAnim);
    // REDIRECTED(TilesetGameCornerAnim);
    // REDIRECTED(TowerPillarTilePointer4);
    // REDIRECTED(TilesetLighthouseAnim);
    // REDIRECTED(TilesetGateAnim);
    // REDIRECTED(UnusedTilesetAnim3);
    // REDIRECTED(AnimateWaterPalette);
    // REDIRECTED(TilesetUndergroundAnim);
    // REDIRECTED(AnimateLavaBubbleTile1);
    // REDIRECTED(TilesetJohtoModernAnim);
    // REDIRECTED(UnusedTilesetAnim4);
CONVERTED(v_AnimateTileset);
    // REDIRECTED(TilesetRadioTowerAnim);
    // REDIRECTED(TilesetHoOhWordRoomAnim);
    // REDIRECTED(TilesetKabutoWordRoomAnim);
    // REDIRECTED(TilesetCaveAnim);
    // REDIRECTED(TilesetPortAnim);
    // REDIRECTED(WriteTile);
    // REDIRECTED(ForestTreeRightAnimation2);
    // REDIRECTED(Tileset0Anim);

    // engine/menus/trainer_card.c
    // REDIRECTED(CardStatusGFX);
    // REDIRECTED(TrainerCard_Page2_LoadGFX);
    // REDIRECTED(BadgeGFX);
    // REDIRECTED(TrainerCard_Page3_Joypad);
    // REDIRECTED(TrainerCard_IncrementJumptable);
    // REDIRECTED(TrainerCard_Page1_Joypad);
    // REDIRECTED(TrainerCardSetup_PlaceTilemapString);
    // REDIRECTED(TrainerCard_Page2_3_InitObjectsAndStrings);
    // REDIRECTED(LeaderGFX);
    // REDIRECTED(TrainerCard_PrintTopHalfOfCard);
    // REDIRECTED(TrainerCard_Page2_3_AnimateBadges);
    // REDIRECTED(TrainerCard_Page2_Joypad);
    // REDIRECTED(LeaderGFX2);
    // REDIRECTED(TrainerCard_InitBorder);
    // REDIRECTED(TrainerCard_Page2_3_PlaceLeadersFaces);
    // REDIRECTED(CardRightCornerGFX);
    // REDIRECTED(TrainerCard_Page1_LoadGFX);
    // REDIRECTED(TrainerCard_Page1_PrintDexCaught_GameTime);
    // REDIRECTED(TrainerCard_Quit);
    // REDIRECTED(TrainerCard_Page1_PrintGameTime);
    // REDIRECTED(TrainerCard_JohtoBadgesOAM);
    // REDIRECTED(TrainerCard_Page2_3_OAMUpdate);
    // REDIRECTED(TrainerCard);
    // REDIRECTED(BadgeGFX2);
    // REDIRECTED(TrainerCard_Page3_LoadGFX);

    // engine/events/heal_machine_anim.c
    CONVERTED(HealMachineAnim);

    // engine/events/hidden_item.c
    // REDIRECTED(SetMemEvent);
    // REDIRECTED(HiddenItemScript);

    // engine/events/npc_trade.c
    // REDIRECTED(NPCTradeWrongText3);
    // REDIRECTED(NPCTradeAfterText1);
    // REDIRECTED(NPCTradeWrongText1);
    // REDIRECTED(DoNPCTrade);
    // REDIRECTED(TradeFlagAction);
    // REDIRECTED(NPCTradeCompleteText2);
    // REDIRECTED(NPCTradeIntroText1);
    // REDIRECTED(TradeTexts);
    // REDIRECTED(NPCTradeCancelText3);
    // REDIRECTED(NPCTradeAfterText4);
    // REDIRECTED(NPCTradeAfterText3);
    // REDIRECTED(Trade_CopyThreeCharString);
    // REDIRECTED(Trade_CopyTwoBytesReverseEndian);
    // REDIRECTED(Trade_CopyFourCharString);
    // REDIRECTED(Trade_GetAttributeOfCurrentPartymon);
    // REDIRECTED(NPCTradeCompleteText4);
    // REDIRECTED(CheckTradeGender);
    // REDIRECTED(NPCTradeIntroText2);
    // REDIRECTED(NPCTradeAfterText2);
    // REDIRECTED(Trade_GetAttributeOfLastPartymon);
    // REDIRECTED(GetTradeMonName);
    // REDIRECTED(NPCTradeCompleteText3);
    // REDIRECTED(GetTradeAttr);
    // REDIRECTED(Trade_CopyTwoBytes);
    // REDIRECTED(NPCTradeCableText);
    // REDIRECTED(NPCTradeCancelText1);
    // REDIRECTED(NPCTradeCompleteText1);
    // REDIRECTED(Trade_GetDialog);
    // REDIRECTED(NPCTradeWrongText2);
    // REDIRECTED(PrintTradeText);
    // REDIRECTED(TradedForText);
    // REDIRECTED(NPCTradeIntroText3);
    // REDIRECTED(NPCTradeCancelText2);
    // REDIRECTED(CopyTradeName);
    // REDIRECTED(GetTradeMonNames);
    // REDIRECTED(NPCTrade);

    // engine/pokemon/caught_data.c
    // REDIRECTED(SetGiftPartyMonCaughtData);
    // CONVERTED(CheckPartyFullAfterContest);
    // REDIRECTED(CaughtAskNicknameText);
    // REDIRECTED(SetBoxmonOrEggmonCaughtData);
    // REDIRECTED(GiveANickname_YesNo);
    // REDIRECTED(SetGiftMonCaughtData);
    // REDIRECTED(SetGiftBoxMonCaughtData);
    // REDIRECTED(SetBoxMonCaughtData);
    // REDIRECTED(SetCaughtData);
    // REDIRECTED(SetEggMonCaughtData);

    // engine/overworld/select_menu.c
    // REDIRECTED(CheckRegisteredItem);
    // REDIRECTED(SelectMenu);
    // REDIRECTED(UseRegisteredItem);
    // REDIRECTED(MayRegisterItemText);

    // engine/events/mom.c
    // REDIRECTED(Mom_ContinueMenuSetup);
    // REDIRECTED(MomJustDoWhatYouCanText);
    // REDIRECTED(MomBankWhatDoYouWantToDoText);
    // REDIRECTED(MomNotEnoughRoomInBankText);
    // REDIRECTED(MomLeavingText2);
    // REDIRECTED(MomSaveMoneyText);
    // REDIRECTED(DSTChecks);
    // REDIRECTED(Mom_DepositString);
    // REDIRECTED(MomIsThisAboutYourMoneyText);
    // REDIRECTED(MomStoredMoneyText);
    // REDIRECTED(Mom_WithdrawDepositMenuJoypad);
    // REDIRECTED(Mom_SetUpDepositMenu);
    // REDIRECTED(MomNotEnoughRoomInWalletText);
    CONVERTED(BankOfMom);
    // REDIRECTED(MomLeavingText3);
    // REDIRECTED(Mon_WithdrawString);
    // REDIRECTED(Mom_Wait10Frames);
    // REDIRECTED(Mom_SavedString);
    // REDIRECTED(Mom_HeldString);
    // REDIRECTED(MomStoreMoneyText);
    // REDIRECTED(MomLeavingText1);
    // REDIRECTED(Mom_SetUpWithdrawMenu);
    // REDIRECTED(MomTakeMoneyText);
    // REDIRECTED(MomInsufficientFundsInWalletText);
    // REDIRECTED(MomStartSavingMoneyText);
    // REDIRECTED(MomHaventSavedThatMuchText);
    // REDIRECTED(MomTakenMoneyText);
    // REDIRECTED(BankOfMom_MenuHeader);

    // engine/events/pokecenter_pc.c
    // REDIRECTED(PokemonCenterPC);
    // REDIRECTED(PlayerLogOffMenu);
    // REDIRECTED(PC_CheckPartyForPokemon);
    // REDIRECTED(PlayerDecorationMenu);
    // REDIRECTED(PCItemsJoypad);
    // REDIRECTED(PC_PlaySwapItemsSound);
    // REDIRECTED(v_PlayersHousePC);
    // REDIRECTED(PlayerTossItemMenu);
    // REDIRECTED(OaksPC);
    // REDIRECTED(PlayerMailBoxMenu);
    // REDIRECTED(PlayerWithdrawItemMenu);
    // REDIRECTED(PC_DisplayText);
    // REDIRECTED(PokecenterBillsPCText);
    // REDIRECTED(PC_PlayBootSound);
    // REDIRECTED(PokecenterOaksPCText);
    // REDIRECTED(PlayersPC);
    // REDIRECTED(PlayersPCTurnOnText);
    // REDIRECTED(PlayersPCMenuData);
    // REDIRECTED(v_PlayersPC);
    // REDIRECTED(PokecenterPCWhoseText);
    // REDIRECTED(PokecenterPCTurnOnText);
    // REDIRECTED(PC_DisplayTextWaitMenu);
    // REDIRECTED(PlayerDepositItemMenu);
    // REDIRECTED(BillsPC);
    // REDIRECTED(PokecenterPlayersPCText);
    // REDIRECTED(HallOfFamePC);
    // REDIRECTED(PlayersPCAskWhatDoText);
    // REDIRECTED(PokecenterPCOaksClosedText);
    // REDIRECTED(PC_PlayChoosePCSound);
    // REDIRECTED(PC_PlayShutdownSound);
    // REDIRECTED(PC_WaitPlaySFX);
    // REDIRECTED(TurnOffPC);

    // engine/battle/returntobattle_useball.c
    CONVERTED(v_ReturnToBattle_UseBall);

    // engine/battle_anims/helpers.c
    // CONVERTED(ReinitBattleAnimFrameset);
    // CONVERTED(GetBattleAnimFrame);
    // CONVERTED(GetBattleAnimOAMPointer);
    // CONVERTED(LoadBattleAnimGFX);

    // engine/battle_anims/pokeball_wobble.c
    // CONVERTED(GetPokeBallWobble);

    // engine/battle/consume_held_item.c
    CONVERTED(ConsumeHeldItem);

    // engine/menus/init_gender.c
    // CONVERTED(LoadGenderScreenLightBlueTile);
    // CONVERTED(AreYouABoyOrAreYouAGirlText);
    CONVERTED(InitCrystalData);
    CONVERTED(InitGender);
    CONVERTED(InitGenderScreen);
    // CONVERTED(LoadGenderScreenPal);

    // engine/events/elevator.c
    // CONVERTED(Elevator_MenuData);
    // CONVERTED(Elevator_GetCurrentFloorText);
    // CONVERTED(GetElevatorFloorStrings);
    // CONVERTED(GetFloorString);
    // CONVERTED(AskFloorElevatorText);
    // CONVERTED(Elevator_GoToFloor);
    // CONVERTED(FloorToString);
    // CONVERTED(Elevator_MenuHeader);
    // CONVERTED(Elevator_AskWhichFloor);
    // CONVERTED(Elevator);
    // CONVERTED(Elevator_GetCurrentFloorString);
    // CONVERTED(Elevator_CurrentFloorText);

    // engine/menus/delete_save.c
    CONVERTED(v_DeleteSaveData);

    // engine/menus/empty_sram.c
    CONVERTED(EmptyAllSRAMBanks);

    // engine/events/card_key.c
    // CONVERTED(v_CardKey);

    // engine/battle/move_effects/sketch.c
    // CONVERTED(BattleCommand_Sketch);

    // engine/battle/move_effects/transform.c
    // CONVERTED(BattleCommand_Transform);
    // CONVERTED(BattleSideCopy);

    // engine/events/prof_oaks_pc.c
    // CONVERTED(FindOakRating);
    // CONVERTED(OakRating11);
    // CONVERTED(OakPCText4);
    // CONVERTED(Rate);
    // CONVERTED(OakRating12);
    // CONVERTED(OakRating03);
    CONVERTED(ProfOaksPCBoot);
    // CONVERTED(OakRating09);
    // CONVERTED(OakPCText2);
    // CONVERTED(OakRating15);
    // CONVERTED(OakRating14);
    // CONVERTED(OakRating17);
    // CONVERTED(OakRating02);
    // CONVERTED(OakRating04);
    // CONVERTED(OakRating18);
    // CONVERTED(OakRating10);
    // CONVERTED(OakPCText3);
    // CONVERTED(OakRating19);
    // CONVERTED(OakPCText1);
    // CONVERTED(OakRating06);
    // CONVERTED(OakRating13);
    // CONVERTED(OakRating16);
    // CONVERTED(OakRating08);
    CONVERTED(ProfOaksPCRating);
    // CONVERTED(OakRating05);
    // CONVERTED(OakRating07);
    CONVERTED(ProfOaksPC);
    // CONVERTED(OakRating01);

    // engine/events/squirtbottle.c
    CONVERTED(v_Squirtbottle);

    // engine/events/checkforhiddenitems.c
    // CONVERTED(CheckForHiddenItems);

    // engine/events/itemfinder.c
    CONVERTED(ItemFinder);

    // engine/events/kurt.c
    // REDIRECTED(Kurt_GetRidOfItem);
    // REDIRECTED(Kurt_SelectApricorn);
    // REDIRECTED(Kurt_SelectQuantity);
    // CONVERTED(Kurt_PrintTextHowMany);
    CONVERTED(SelectApricornForKurt);
    // REDIRECTED(Kurt_GiveUpSelectedQuantityOfSelectedApricorn);
    // REDIRECTED(Kurt_GetQuantityOfApricorn);
    // CONVERTED(Kurt_PrintTextWhichApricorn);
    // REDIRECTED(Kurt_GetAddressOfApricornQuantity);
    // REDIRECTED(PlaceApricornQuantity);

    // engine/events/kurt_selectquantity_interpretjoypad.c
    // CONVERTED(Kurt_SelectQuantity_InterpretJoypad);

    // engine/events/name_rater.c
    // CONVERTED(NameRaterWhatNameText);
    // CONVERTED(NameRaterEggText);
    // CONVERTED(NameRaterComeAgainText);
    CONVERTED(v_NameRater);
    // CONVERTED(NameRaterNamedText);
    // CONVERTED(CheckIfMonIsYourOT);
    // CONVERTED(NameRaterBetterNameText);
    // CONVERTED(GetNicknamenameLength);
    // CONVERTED(IsNewNameEmpty);
    // CONVERTED(NameRaterSameNameText);
    // CONVERTED(NameRaterHelloText);
    // CONVERTED(CompareNewToOld);
    // CONVERTED(NameRaterWhichMonText);
    // CONVERTED(NameRaterFinishedText);
    // CONVERTED(NameRaterPerfectNameText);

    // engine/events/haircut.c
    CONVERTED(BillsGrandfather);
    CONVERTED(DaisysGrooming);
    // REDIRECTED(HaircutOrGrooming);
    CONVERTED(CopyPokemonName_Buffer1_Buffer3);
    CONVERTED(YoungerHaircutBrother);
    CONVERTED(OlderHaircutBrother);
    // REDIRECTED(DummyPredef1);

    // engine/menus/naming_screen.c
    // REDIRECTED(NamingScreenGFX_UnderLine);
    // REDIRECTED(NamingScreenGFX_Border);
    // REDIRECTED(NamingScreen_GetTextCursorPosition);
    // REDIRECTED(MailComposition_TryAddLastCharacter);
    CONVERTED(LoadNamingScreenGFX);
    // REDIRECTED(NamingScreen);
    // REDIRECTED(NamingScreen_TryAddCharacter);
    // REDIRECTED(NamingScreen_LoadNextCharacter);
    // REDIRECTED(v_NamingScreen);
    // REDIRECTED(NamingScreenGFX_Cursor);
    // REDIRECTED(v_ComposeMailMessage);
    // REDIRECTED(ComposeMail_GetCursorPosition);
    // REDIRECTED(NamingScreen_InitNameEntry);
    // REDIRECTED(NamingScreen_StoreEntry);
    // REDIRECTED(NamingScreen_GetCursorPosition);
    // REDIRECTED(NamingScreenGFX_MiddleLine);
    // REDIRECTED(AddDakutenToCharacter);
    // REDIRECTED(NamingScreen_AnimateCursor);
    // REDIRECTED(NamingScreenJoypadLoop);
    // REDIRECTED(ComposeMail_AnimateCursor);
    // REDIRECTED(NamingScreen_AdvanceCursor_CheckEndOfString);
    // REDIRECTED(MailComposition_TryAddCharacter);
    // REDIRECTED(NamingScreen_PressedA_GetCursorCommand);
    // REDIRECTED(NamingScreen_IsTargetBox);
    // REDIRECTED(NamingScreenGFX_End);
    // REDIRECTED(NamingScreen_ApplyTextInputMode);
    // REDIRECTED(NamingScreen_GetLastCharacter);
    // REDIRECTED(NamingScreen_DeleteCharacter);
    // REDIRECTED(NamingScreen_InitText);

    // engine/pokedex/pokedex.c
    // REDIRECTED(Pokedex_PlaceFrontpicTopLeftCorner);
    // REDIRECTED(Pokedex_UpdateDexEntryScreen);
    // REDIRECTED(Pokedex_FillBackgroundColor2);
    // REDIRECTED(Pokedex_DisplayTypeNotFoundMessage);
    // REDIRECTED(Pokedex_RunJumptable);
    // REDIRECTED(Pokedex_ListingHandleDPadInput);
    // REDIRECTED(Pokedex_PlaceCaughtSymbolIfCaught);
    // REDIRECTED(Pokedex_InitSearchScreen);
    // REDIRECTED(PokedexLZ);
    // REDIRECTED(Pokedex_RedisplayDexEntry);
    // REDIRECTED(Pokedex_InitArrowCursor);
    // REDIRECTED(Pokedex_NextOrPreviousDexEntry);
    // REDIRECTED(Pokedex_InitMainScreen);
    // REDIRECTED(Pokedex_PlaceBorder);
    // REDIRECTED(Pokedex_LoadPointer);
    // REDIRECTED(Pokedex_LoadGFX);
    // REDIRECTED(Pokedex_CheckUnlockedUnownMode);
    // REDIRECTED(Pokedex_DrawOptionScreenBG);
    // REDIRECTED(Pokedex_PrintNumberIfOldMode);
    // REDIRECTED(Pokedex_DrawDexEntryScreenBG);
    // REDIRECTED(Pokedex_ListingMoveCursorDown);
    // REDIRECTED(Pokedex_ApplyUsualPals);
    // REDIRECTED(Pokedex_DrawSearchResultsScreenBG);
    // REDIRECTED(String_SEEN);
    // REDIRECTED(Pokedex_PlaceTypeString);
    // REDIRECTED(Pokedex_InitOptionScreen);
    // REDIRECTED(String_START_SEARCH);
    // REDIRECTED(Pokedex_BlinkArrowCursor);
    // REDIRECTED(Pokedex_OrderMonsByMode);
    // REDIRECTED(Pokedex_ArrowCursorDelay);
    // REDIRECTED(Pokedex_ABCMode);
    // REDIRECTED(Pokedex_GetArrowCursorPos);
    // REDIRECTED(Pokedex_UpdateSearchScreen);
    // REDIRECTED(Pokedex_InitDexEntryScreen);
    // REDIRECTED(Pokedex_IncrementDexPointer);
    // REDIRECTED(PokedexSlowpokeLZ);
    // REDIRECTED(Pokedex_UpdateSearchMonType);
    // REDIRECTED(Pokedex_ListingPosChanged);
    CONVERTED(Pokedex);
    // REDIRECTED(Pokedex_DrawSearchScreenBG);
    // REDIRECTED(Pokedex_CheckCaught);
    // REDIRECTED(Pokedex_UpdateUnownMode);
    // REDIRECTED(Pokedex_PlaceSearchScreenTypeStrings);
    // REDIRECTED(Pokedex_UpdateSearchResultsCursorOAM);
    // REDIRECTED(Pokedex_FillBox);
    // REDIRECTED(Pokedex_Page);
    // REDIRECTED(Pokedex_PrintListing);
    // REDIRECTED(Pokedex_BlackOutBG);
    // REDIRECTED(Pokedex_UpdateOptionScreen);
    // REDIRECTED(Pokedex_Exit);
    // REDIRECTED(Pokedex_PlaceFrontpicAtHL);
    // REDIRECTED(Pokedex_DrawFootprint);
    // REDIRECTED(Pokedex_NextSearchMonType);
    // REDIRECTED(Pokedex_PrevSearchMonType);
    // REDIRECTED(Pokedex_SetBGMapMode4);
    // REDIRECTED(Pokedex_PutNewModeABCModeCursorOAM);
    // REDIRECTED(Pokedex_LoadCurrentFootprint);
    // REDIRECTED(Pokedex_ResetBGMapMode);
    // REDIRECTED(Pokedex_LoadUnownFont);
    // REDIRECTED(Pokedex_DisplayModeDescription);
    // REDIRECTED(Pokedex_ListingMoveUpOnePage);
    // REDIRECTED(Pokedex_InitSearchResultsScreen);
    // REDIRECTED(UnownModeLetterAndCursorCoords);
    // REDIRECTED(Pokedex_PlaceSearchResultsTypeStrings);
    // REDIRECTED(String_OWN);
    // REDIRECTED(Pokedex_UnownModeHandleDPadInput);
    // REDIRECTED(DexEntryScreen_ArrowCursorData);
    // REDIRECTED(Pokedex_SearchForMons);
    // REDIRECTED(Pokedex_InvertTiles);
    // REDIRECTED(Pokedex_PutOldModeCursorOAM);
    // REDIRECTED(Pokedex_CheckSeen);
    // REDIRECTED(Pokedex_SetBGMapMode3);
    // REDIRECTED(v_NewPokedexEntry);
    // REDIRECTED(String_SELECT_OPTION);
    // REDIRECTED(Pokedex_MoveArrowCursor);
    // REDIRECTED(Pokedex_UnownModeEraseCursor);
    // REDIRECTED(Pokedex_UpdateSearchResultsScreen);
    // REDIRECTED(Pokedex_DisplayChangingModesMessage);
    // REDIRECTED(Pokedex_GetLandmark);
    // REDIRECTED(Pokedex_LoadCursorOAM);
    // REDIRECTED(Pokedex_PlaceString);
    // REDIRECTED(Pokedex_DrawUnownModeBG);
    // REDIRECTED(Pokedex_LoadAnyFootprint);
    // REDIRECTED(InitPokedex);
    // REDIRECTED(DexEntryScreen_MenuActionJumptable);
    // REDIRECTED(Pokedex_SetBGMapMode_3ifDMG_4ifCGB);
    // REDIRECTED(Pokedex_InitCursorPosition);
    // REDIRECTED(Pokedex_ListingMoveCursorUp);
    // REDIRECTED(Pokedex_ReinitDexEntryScreen);
    // REDIRECTED(Pokedex_FillColumn);
    // REDIRECTED(Pokedex_ListingMoveDownOnePage);
    // REDIRECTED(Pokedex_LoadUnownFrontpicTiles);
    // REDIRECTED(Pokedex_InitUnownMode);
    // REDIRECTED(Pokedex_GetSGBLayout);
    // REDIRECTED(Pokedex_LoadInvertedFont);
    // REDIRECTED(Pokedex_ListingPosStayedSame);
    // REDIRECTED(Pokedex_LoadSelectedMonTiles);
    // REDIRECTED(Pokedex_PutScrollbarOAM);
    // REDIRECTED(Pokedex_UpdateCursorOAM);
    // REDIRECTED(Pokedex_DrawMainScreenBG);
    // REDIRECTED(Pokedex_GetSelectedMon);
    // REDIRECTED(Pokedex_ApplyPrintPals);
    // REDIRECTED(Pokedex_CheckSGB);
    // REDIRECTED(Pokedex_UnownModePlaceCursor);
    // REDIRECTED(Pokedex_PlaceDefaultStringIfNotSeen);
    // REDIRECTED(Pokedex_UnownModeUpdateCursorGfx);
    // REDIRECTED(String_ChangingModesPleaseWait);
    // REDIRECTED(Pokedex_UpdateMainScreen);

    // engine/pokedex/pokedex_3.c
    // REDIRECTED(LoadSGBPokedexGFX2);
    // REDIRECTED(DrawPokedexSearchResultsWindow);
    // REDIRECTED(Pokedex_FillColumn2);
    // REDIRECTED(SGBPokedexGFX_LZ);
    // REDIRECTED(LoadSGBPokedexGFX);
    // REDIRECTED(DrawPokedexListWindow);
    // REDIRECTED(DrawDexEntryScreenRightEdge);
    // REDIRECTED(LoadQuestionMarkPic);

    // engine/events/daycare.c
    // CONVERTED(DayCare_InitBreeding);
    // CONVERTED(DayCareManIntroText);
    // CONVERTED(DayCare_AskWithdrawBreedMon);
    // CONVERTED(DayCare_GetCurrentPartyMember);
    // CONVERTED(DayCare_GiveEgg);
    CONVERTED(DayCareLady);
    // CONVERTED(DayCareAskDepositPokemon);
    // CONVERTED(GetPriceToRetrieveBreedmon);
    // CONVERTED(PrintDayCareText);
    // CONVERTED(DayCare_GetBackMonForMoney);
    CONVERTED(DayCareManOutside);
    CONVERTED(DayCareMan);
    // CONVERTED(DayCare_DepositPokemonText);
    // CONVERTED(DayCareLadyIntroText);

    // engine/pokemon/breedmon_level_growth.c
    // REDIRECTED(GetBreedMon2LevelGrowth);
    // REDIRECTED(GetBreedMon1LevelGrowth);

    // engine/pokemon/breeding.c
    // REDIRECTED(LeftWithDayCareLadyText);
    // REDIRECTED(LeftWithDayCareManText);
    // REDIRECTED(GetEggMove);
    // REDIRECTED(EggHatch_DoAnimFrame);
    // REDIRECTED(DayCareMon2);
    // REDIRECTED(DoEggStep);
    // REDIRECTED(GetBreedmonMovePointer);
    // REDIRECTED(HatchEggs);
    // REDIRECTED(LoadEggMove);
    // REDIRECTED(Hatch_ShellFragmentLoop);
    // REDIRECTED(GetEggFrontpic);
    // REDIRECTED(EggHatch_AnimationSequence);
    // REDIRECTED(Hatch_LoadFrontpicPal);
    // REDIRECTED(EggHatchGFX);
    // REDIRECTED(GetHeritableMoves);
    // REDIRECTED(GetHatchlingFrontpic);
    // REDIRECTED(CheckBreedmonCompatibility);
    // REDIRECTED(OverworldHatchEgg);
    // REDIRECTED(InitEggMoves);
    // REDIRECTED(DayCareMonPrintEmptyString);
    // REDIRECTED(Hatch_InitShellFragments);
    // REDIRECTED(DayCareMon1);
    // REDIRECTED(EggHatch_CrackShell);
    // REDIRECTED(DayCareMonCursor);
    // REDIRECTED(DayCareMonCompatibilityText);
    // REDIRECTED(Hatch_UpdateFrontpicBGMapCenter);

    // engine/events/odd_egg.c
    CONVERTED(v_GiveOddEgg);

    // mobile/mobile_46.c
    // REDIRECTED(Function11a452);
    // REDIRECTED(Function118b10);
    // REDIRECTED(Function11a16d);
    // REDIRECTED(Text_CancelBattleRoomChallenge);
    // REDIRECTED(BattleTowerRoomMenu_WriteMessage_DoNothing);
    // REDIRECTED(Function118624);
    // REDIRECTED(Function118a65);
    // REDIRECTED(String_11aff0);
    // REDIRECTED(String_11b303);
    // REDIRECTED(Function11a1ff);
    // REDIRECTED(Function11a88c);
    // REDIRECTED(Function1191d3);
    // REDIRECTED(String_11a692);
    // REDIRECTED(Text_WhatLevelDoYouWantToChallenge);
    // REDIRECTED(Function11886a);
    // REDIRECTED(Text_LinkingWithCenter);
    // REDIRECTED(Function11b239);
    // REDIRECTED(Function119612);
    // REDIRECTED(String_11a743);
    // REDIRECTED(Function118007);
    // REDIRECTED(MenuHeader_11b013);
    // REDIRECTED(Function118d9b);
    // REDIRECTED(Function1188c0);
    // REDIRECTED(Function118ad0);
    // REDIRECTED(Function11a41b);
    // REDIRECTED(asm_11b26f);
    // REDIRECTED(Function1186f5);
    // REDIRECTED(Function119380);
    // REDIRECTED(String_11ae40);
    // REDIRECTED(Function11a131);
    // REDIRECTED(MenuHeader_11a2de);
    // REDIRECTED(Function11a129);
    // REDIRECTED(Function119054);
    // REDIRECTED(Function11a466);
    // REDIRECTED(Function118671);
    // REDIRECTED(CheckSeenMemMon);
    // REDIRECTED(Function11a5f5);
    // REDIRECTED(Function119954);
    // REDIRECTED(BattleTowerRoomMenu_QuitMessage);
    // REDIRECTED(String_11a7ac);
    // REDIRECTED(String_11b30e);
    // REDIRECTED(Mobile46_InitJumptable);
    // REDIRECTED(Function11b7e5);
    // REDIRECTED(Function11a4db);
    // REDIRECTED(MenuHeader_11afe8);
    // REDIRECTED(Function11b175);
    // REDIRECTED(String_11a762);
    // REDIRECTED(Function11a9ce);
    // REDIRECTED(Function119223);
    // REDIRECTED(asm_119b4d);
    // REDIRECTED(Strings_L10ToL100);
    // REDIRECTED(Function118746);
    // REDIRECTED(Function1185c3);
    // REDIRECTED(String_11a706);
    // REDIRECTED(Function119b0d);
    // REDIRECTED(Function1196f2);
    // REDIRECTED(Unknown_11afd2);
    // REDIRECTED(Function11837a);
    // REDIRECTED(Function11b879);
    // REDIRECTED(Function119b45);
    // REDIRECTED(Unknown_11a8ba);
    // REDIRECTED(Text_SaveFileWillBeSent);
    // REDIRECTED(Function118b9a);
    // REDIRECTED(CheckCaughtMemMon);
    // REDIRECTED(Function1181da);
    // REDIRECTED(Function119798);
    // REDIRECTED(BattleTowerRoomMenu2_UpdateYesNoMenu);
    // REDIRECTED(Function11a9f4);
    // REDIRECTED(Function118eb0);
    // REDIRECTED(Function119940);
    // REDIRECTED(String_11a7f4);
    // REDIRECTED(Function11b267);
    // REDIRECTED(Function11a4fe);
    // REDIRECTED(Function11915d);
    // REDIRECTED(Function11a5b9);
    // REDIRECTED(Function118821);
    // REDIRECTED(BattleTowerRoomMenu_PickLevelMessage);
    // REDIRECTED(Function11b099);
    // REDIRECTED(Function11a1d6);
    // REDIRECTED(String_11a70b);
    // REDIRECTED(Function11afbb);
    // REDIRECTED(Function11af04);
    // REDIRECTED(TilemapPack_11ba44);
    // REDIRECTED(Function11a80c);
    // REDIRECTED(Function1196de);
    // REDIRECTED(BattleTowerRoomMenu_WriteMessage);
    // REDIRECTED(Function11a357);
    // REDIRECTED(asm_11800b);
    // REDIRECTED(BattleTowerRoomMenu_UpdatePickLevelMenu);
    // REDIRECTED(Function11a884);
    // REDIRECTED(Function11811a);
    // REDIRECTED(Function1193a0);
    // REDIRECTED(BattleTowerRoomMenu_DelayRestartMenu);
    // REDIRECTED(Text_ThisBattleRoomPleaseWait);
    // REDIRECTED(Function11b0ff);
    // REDIRECTED(Text_UberRestriction);
    // REDIRECTED(Function11ba38);
    // REDIRECTED(String_11a755);
    // REDIRECTED(Function1190d0);
    // REDIRECTED(Function1195f8);
    // REDIRECTED(Function119b52);
    // REDIRECTED(String_11a72a);
    // REDIRECTED(AddMobileMonToParty);
    // REDIRECTED(SetMobileErrorCode);
    // REDIRECTED(Function118e6d);
    // REDIRECTED(Function11884c);
    // REDIRECTED(Function118b8c);
    // REDIRECTED(BattleTowerRoomMenu_UberRestrictionMessage);
    // REDIRECTED(Function11b295);
    // REDIRECTED(Function1199b4);
    // REDIRECTED(Function118d35);
    // REDIRECTED(Text_SentSaveFileReadingNews);
    // REDIRECTED(Function118f14);
    // REDIRECTED(Function1197dc);
    // REDIRECTED(Function11a3d9);
    // REDIRECTED(Function11886e);
    // REDIRECTED(String_11a6f1);
    // REDIRECTED(Function1197bf);
    // REDIRECTED(Function119694);
    // REDIRECTED(Function119b3b);
    // REDIRECTED(BattleTowerRoomMenu_CallRoomMenu2);
    // REDIRECTED(Function118d80);
    // REDIRECTED(Function11a3f9);
    // REDIRECTED(Function11b5c0);
    // REDIRECTED(Text_ReceivedNews);
    // REDIRECTED(BattleTowerRoomMenu_InitRAM);
    // REDIRECTED(Unknown_11afcc);
    // REDIRECTED(Function119f98);
    // REDIRECTED(Function1191ad);
    // REDIRECTED(asm_118d9f);
    // REDIRECTED(Function119629);
    // REDIRECTED(Function11afb7);
    // REDIRECTED(Function11a9f0);
    // REDIRECTED(Text_BattleRoomVisitLimit);
    // REDIRECTED(Function119471);
    // REDIRECTED(Function118e06);
    // REDIRECTED(Function118abc);
    // REDIRECTED(Function11ad1b);
    // REDIRECTED(Function119e4f);
    // REDIRECTED(Function119648);
    // REDIRECTED(Function1188c8);
    // REDIRECTED(Function1180b8);
    // REDIRECTED(Function118e39);
    // REDIRECTED(Function11b66d);
    // REDIRECTED(Function11a36b);
    // REDIRECTED(String_119d07);
    // REDIRECTED(Function118180);
    // REDIRECTED(Function1190ec);
    // REDIRECTED(MenuHeader_119cf7);
    // REDIRECTED(MenuHeader_11a2d6);
    // REDIRECTED(BattleTowerRoomMenu_DoNothing);
    // REDIRECTED(Function11b20b);
    // REDIRECTED(Text_RegisteringRecord);
    // REDIRECTED(BattleTowerRoomMenu_SetMessage);
    // REDIRECTED(Function119584);
    // REDIRECTED(BattleTowerRoomMenu2_PlaceYesNoMenu);
    // REDIRECTED(String_11a6aa);
    // REDIRECTED(Function119800);
    // REDIRECTED(Function118440);
    // REDIRECTED(Function11ad6e);
    // REDIRECTED(Function11a488);
    // REDIRECTED(TilemapPack_11bb7d);
    // REDIRECTED(String_11a7d7);
    // REDIRECTED(Function118fc0);
    // REDIRECTED(Function11b275);
    // REDIRECTED(Function119685);
    // REDIRECTED(Function119388);
    // REDIRECTED(Function11b236);
    // REDIRECTED(Function11878d);
    // REDIRECTED(Function11a33a);
    // REDIRECTED(Function11ac51);
    // REDIRECTED(Function118e7e);
    // REDIRECTED(MenuData_119cff);
    // REDIRECTED(String_11a779);
    // REDIRECTED(Function1198ee);
    // REDIRECTED(Function11ad95);
    // REDIRECTED(NewsDownloadURL);
    // REDIRECTED(MenuHeader_11ae38);
    // REDIRECTED(Function11afd6);
    // REDIRECTED(Function119f76);
    // REDIRECTED(Function119413);
    // REDIRECTED(Function118880);
    // REDIRECTED(Function11b444);
    // REDIRECTED(Function119300);
    // REDIRECTED(BattleTowerRoomMenu_Cleanup);
    // REDIRECTED(Function11b31b);
    // REDIRECTED(Function11b5e7);
    // REDIRECTED(Function119f3f);
    // REDIRECTED(Function1195c4);
    // REDIRECTED(asm_11b26a);
    // REDIRECTED(Function11a47a);
    // REDIRECTED(Function118f68);
    // REDIRECTED(Function1184ec);
    // REDIRECTED(Function11b242);
    // REDIRECTED(Function11b272);
    // REDIRECTED(Function119ec2);
    // REDIRECTED(Function11b920);
    // REDIRECTED(Function1188b0);
    // REDIRECTED(Function118284);
    // REDIRECTED(Function119937);
    // REDIRECTED(Function119e8e);
    // REDIRECTED(String_11b003);
    // REDIRECTED(Function118b24);
    // REDIRECTED(Function11914e);
    // REDIRECTED(Function1182d5);
    // REDIRECTED(String_11b01b);
    // REDIRECTED(Function1193e3);
    // REDIRECTED(Function11ad8f);
    // REDIRECTED(Function119665);
    // REDIRECTED(Function118f0d);
    // REDIRECTED(Function1188e7);
    // REDIRECTED(Unknown_1196b8);
    // REDIRECTED(Function118a7a);
    // REDIRECTED(String_11a6db);
    // REDIRECTED(BattleDownloadURL);
    // REDIRECTED(Function11966d);
    // REDIRECTED(Function119e98);
    // REDIRECTED(Function119451);
    // REDIRECTED(Text_CheckBattleRoomListByMaxLevel);
    // REDIRECTED(Function11b279);
    // REDIRECTED(Function1193fb);
    // REDIRECTED(Function11a2e6);
    // REDIRECTED(Function11b397);
    // REDIRECTED(Function118e92);
    // REDIRECTED(Function1196cd);
    // REDIRECTED(BattleTowerRoomMenu2);
    // REDIRECTED(MenuDownloadURL);
    // REDIRECTED(Function11920f);
    // REDIRECTED(Function11a90f);
    // REDIRECTED(Function119eb4);
    // REDIRECTED(Function118a54);
    // REDIRECTED(Function11a971);
    // REDIRECTED(Function11b314);
    // REDIRECTED(Function11b022);
    // REDIRECTED(BattleTowerRoomMenu_WaitForMessage);
    // REDIRECTED(Function118ec6);
    // REDIRECTED(Function119b6b);
    // REDIRECTED(Function1192cc);
    // REDIRECTED(Function119192);
    // REDIRECTED(Function118aa4);
    // REDIRECTED(asm_11afbd);
    // REDIRECTED(BattleTowerRoomMenu_UpdateYesNoMenu);
    // REDIRECTED(BattleTower_LevelCheck);
    // REDIRECTED(Strings_Ll0ToL40);
    // REDIRECTED(Function118e76);
    // REDIRECTED(Function11a536);
    // REDIRECTED(Function11a38d);
    // REDIRECTED(String_11a7c1);
    // REDIRECTED(BattleTowerRoomMenu2_IncrementJumptable);
    // REDIRECTED(Function11b082);
    // REDIRECTED(asm_118e3e);
    // REDIRECTED(BattleTowerRoomMenu_IncrementJumptable);
    // REDIRECTED(XGameCodePrefix);
    // REDIRECTED(Function118125);
    // REDIRECTED(Function1186b2);
    // REDIRECTED(Text_QuitReadingNews);
    // REDIRECTED(Function11967d);
    // REDIRECTED(Function118473);
    // REDIRECTED(IndexDownloadURL);
    // REDIRECTED(XGameResultPrefix);
    // REDIRECTED(Function119973);
    // REDIRECTED(v_BattleTowerRoomMenu);
    // REDIRECTED(Function11a0ca);
    // REDIRECTED(Function11a4e8);
    // REDIRECTED(Function118896);
    // REDIRECTED(Function11b570);
    // REDIRECTED(Function118233);
    // REDIRECTED(Mobile46_RunJumptable);
    // REDIRECTED(Jumptable_11ad78);
    // REDIRECTED(Function11acb7);
    // REDIRECTED(Text_ReadingNews);
    // REDIRECTED(Function11b3d9);
    // REDIRECTED(Function119ac9);
    // REDIRECTED(Function11857c);
    // REDIRECTED(Unknown_11a8da);
    // REDIRECTED(Text_ExitGymLeaderHonorRoll);
    // REDIRECTED(Function11b93b);
    // REDIRECTED(Function11b6b3);
    // REDIRECTED(String_11b2fe);
    // REDIRECTED(Function11b03d);
    // REDIRECTED(Function11a192);
    // REDIRECTED(Function1197c9);
    // REDIRECTED(Unknown_11a89a);
    // REDIRECTED(Function11b6b4);
    // REDIRECTED(Function11a63c);
    // REDIRECTED(Text_EnterWhichBattleRoom);
    // REDIRECTED(String_11a2cf);
    // REDIRECTED(BattleTowerRoomMenu_PlaceYesNoMenu);
    // REDIRECTED(Function11a13d);
    // REDIRECTED(Function119f45);
    // REDIRECTED(Function118b42);
    // REDIRECTED(String_11a661);
    // REDIRECTED(BattleTowerRoomMenu_PartyMonTopsThisLevelMessage);
    // REDIRECTED(Function1197b4);
    // REDIRECTED(Function11af4e);
    // REDIRECTED(Text_WhichBattleRoom);
    // REDIRECTED(Function1198f7);
    // REDIRECTED(Function119e2b);
    // REDIRECTED(Function119009);
    // REDIRECTED(Function11ae98);
    // REDIRECTED(Function1199ca);
    // REDIRECTED(Text_ReceivedOddEgg);
    // REDIRECTED(Function11a302);
    // REDIRECTED(Function11a00e);
    // REDIRECTED(Function118866);
    // REDIRECTED(Function118000);
    // REDIRECTED(BattleTower_UbersCheck);
    // REDIRECTED(String_11b308);
    // REDIRECTED(ExchangeDownloadURL);
    // REDIRECTED(Function118329);
    // REDIRECTED(Function11a14b);
    // REDIRECTED(Function1188b8);
    // REDIRECTED(XGameCode);
    // REDIRECTED(Function11ac3e);
    // REDIRECTED(Function11ad8a);
    // REDIRECTED(FillScreenWithTile32);
    // REDIRECTED(Function11b483);
    // REDIRECTED(XGameResult);
    // REDIRECTED(Function11805f);
    // REDIRECTED(String_11a791);
    // REDIRECTED(BattleTowerRoomMenu_Jumptable);
    // REDIRECTED(Function118f5e);
    // REDIRECTED(Function11a113);
    // REDIRECTED(Text_PartyMonTopsThisLevel);
    // REDIRECTED(String_11a71e);
    // REDIRECTED(Function11adc4);
    // REDIRECTED(Function11b3b6);
    // REDIRECTED(asm_11886f);
    // REDIRECTED(Function118a8f);
    // REDIRECTED(Function119987);
    // REDIRECTED(Function11ae4e);
    // REDIRECTED(Function118ded);
    // REDIRECTED(BattleTowerRoomMenu_PlacePickLevelMenu);
    // REDIRECTED(BattleTowerCancelString);
    // REDIRECTED(Function11a49e);
    // REDIRECTED(Function11b5e0);
    // REDIRECTED(Text_CanceledSendingSaveFile);
    // REDIRECTED(Function11891c);
    // REDIRECTED(Function11a3c5);
    // REDIRECTED(MenuHeader_11a804);
    // REDIRECTED(CopyDataUntilFF);
    // REDIRECTED(Function11a1e6);
    // REDIRECTED(String_11a6d2);
    // REDIRECTED(Function119f56);
    // REDIRECTED(Function118ae4);
    // REDIRECTED(String_11a679);
    // REDIRECTED(Function1199e2);
    // REDIRECTED(Function118903);
    // REDIRECTED(Function11b5e8);
    // REDIRECTED(String_11a2d3);
    // REDIRECTED(Function11984e);
    // REDIRECTED(String_11a6c8);
    // REDIRECTED(Function1184a5);

    // mobile/mobile_45_stadium.c
    // REDIRECTED(MobileStudium_JumptableIncrement);
    // REDIRECTED(MobileStadiumEntryText);
    // REDIRECTED(MobilePassword_IncrementJumptable);
    // REDIRECTED(Function1177cb);
    // REDIRECTED(Function1179a7);
    // REDIRECTED(Function117b28);
    // REDIRECTED(Function117942);
    // REDIRECTED(YessNoString_1179c5);
    // REDIRECTED(MenuHeader_117cc4);
    // REDIRECTED(Function1178e8);
    // REDIRECTED(Function117984);
    // REDIRECTED(Function117ae9);
    // REDIRECTED(NotAPokemonPasswordString);
    // REDIRECTED(Function117b4f);
    // REDIRECTED(MenuHeader_1179b5);
    // REDIRECTED(MobileStudium);
    // REDIRECTED(Function117c4a);
    // REDIRECTED(Function11765d);
    // REDIRECTED(Unknown_117a0f);
    // REDIRECTED(Function117a8d);
    // REDIRECTED(Function117764_select);
    // REDIRECTED(Function117764_d_up);
    // REDIRECTED(MenuHeader_117cbc);
    // REDIRECTED(asm_11797e);
    // REDIRECTED(Function1176ee);
    // REDIRECTED(Function117b14);
    // REDIRECTED(Function117bb6);
    // REDIRECTED(YesNo117ccc);
    // REDIRECTED(Function117976);
    // REDIRECTED(Function117764_start);
    // REDIRECTED(Function1177b7);
    // REDIRECTED(Function1178aa);
    // REDIRECTED(Function11766b);
    CONVERTED(GiveOddEgg);
    // REDIRECTED(Function117764_d_down);
    // REDIRECTED(Function117acd);
    // REDIRECTED(Function117719);
    // REDIRECTED(AskSavePasswordString);
    // REDIRECTED(Function117c89);
    // REDIRECTED(Function117764_d_vertical_load);
    // REDIRECTED(Function117b31);
    // REDIRECTED(MenuHeader_1179bd);
    // REDIRECTED(SavedPasswordString);
    // REDIRECTED(Jumptable_117728);
    // REDIRECTED(MobileStadiumSuccessText);
    // REDIRECTED(Function117699);
    // REDIRECTED(Function117764);
    // REDIRECTED(Function117ab4);
    // REDIRECTED(Function117764_d_left);
    // REDIRECTED(Function117764_a_button);
    // REDIRECTED(Function117738);
    // REDIRECTED(Function117764_d_right);
    // REDIRECTED(Function117a94);
    // REDIRECTED(Function117b06);
    // REDIRECTED(Unknown_117a47);
    // REDIRECTED(Function117764_b_button);

    // engine/events/bug_contest/contest.c
    // REDIRECTED(BugCatchingContestOverScript);
    // REDIRECTED(BugCatchingContestIsOverText);
    CONVERTED(GiveParkBalls);
    // REDIRECTED(BugCatchingContestOutOfBallsScript);
    // REDIRECTED(BugCatchingContestBattleScript);
    // REDIRECTED(BugCatchingContestTimeUpText);
    // REDIRECTED(BugCatchingContestReturnToGateScript);

    // engine/events/bug_contest/contest_2.c
    CONVERTED(ContestReturnMons);
    CONVERTED(ContestDropOffMons);
    CONVERTED(SelectRandomBugContestContestants);
    // CONVERTED(CheckBugContestContestantFlag);

    // engine/events/bug_contest/judging.c
    // CONVERTED(ContestScore);
    // CONVERTED(BugContest_JudgeContestants);
    // CONVERTED(DetermineContestWinners);
    // CONVERTED(ContestJudging_FirstPlaceText);
    // CONVERTED(ContestJudging_SecondPlaceScoreText);
    // CONVERTED(v_BugContestJudging);
    // CONVERTED(ContestJudging_ThirdPlaceScoreText);
    // CONVERTED(LoadContestantName);
    // CONVERTED(ContestJudging_SecondPlaceText);
    // CONVERTED(BugContest_GetPlayersResult);
    // CONVERTED(CopyTempContestant);
    // CONVERTED(ContestJudging_ThirdPlaceText);
    // CONVERTED(ComputeAIContestantScores);
    // CONVERTED(ContestJudging_FirstPlaceScoreText);
    // CONVERTED(ClearContestResults);

    // engine/events/bug_contest/display_stats.c
    // CONVERTED(DisplayCaughtContestMonStats);
    // CONVERTED(DisplayAlreadyCaughtText);
    // CONVERTED(DummyPredef2F);
    // CONVERTED(ContestAskSwitchText);
    // CONVERTED(DummyPredef38);
    // CONVERTED(DummyPredef39);

    // engine/events/bug_contest/caught_mon.c
    CONVERTED(BugContest_SetCaughtContestMon);

    // engine/pokedex/unown_dex.c
    // CONVERTED(UpdateUnownDex);
    // REDIRECTED(PrintUnownWord);

    // engine/pokemon/move_mon_wo_mail.c
    // CONVERTED(InsertPokemonIntoBox);
    // CONVERTED(InsertPokemonIntoParty);
    // CONVERTED(InsertSpeciesIntoBoxOrParty);
    // CONVERTED(InsertDataIntoBoxOrParty);

    // engine/events/battle_tower/battle_tower.c
    // REDIRECTED(Function170aaf);
    // REDIRECTED(Function170139);
    // REDIRECTED(ReadBTTrainerParty);
    // REDIRECTED(Function1708c8);
    // REDIRECTED(BattleTowerAction_GetChallengeState);
    CONVERTED(Function170923);
    // REDIRECTED(UnusedBattleTowerDummySpecial1);
    // REDIRECTED(BT_ChrisName);
    // REDIRECTED(Function1707ac);
    CONVERTED(BattleTower_CheckSaveFileExistsAndIsYours);
    // REDIRECTED(Function170abe);
    // REDIRECTED(CheckForBattleTowerRules);
    // REDIRECTED(SkipBattleTowerTrainer);
    // REDIRECTED(Function1700c4);
    // REDIRECTED(LoadOpponentTrainerAndPokemonWithOTSprite);
    // REDIRECTED(Function170aa0);
    // REDIRECTED(Function170a9c);
    // REDIRECTED(SetBattleTowerChallengeState);
    // REDIRECTED(UnusedBattleTowerDummySpecial2);
    // REDIRECTED(Function17081d);
    // REDIRECTED(Function1704ca);
    // REDIRECTED(Function170114);
    // REDIRECTED(LoadBattleTowerLevelGroup);
    // REDIRECTED(BattleTowerAction_LevelCheck);
    // REDIRECTED(SaveBattleTowerLevelGroup);
    // REDIRECTED(BattleTowerAction_CheckExplanationRead);
    // REDIRECTED(BattleTowerAction_SetByteToCancelChallenge);
    // REDIRECTED(Function1708b1);
    // REDIRECTED(ValidateBTParty);
    // REDIRECTED(BattleTower_RandomlyChooseReward);
    // REDIRECTED(BattleTowerAction_SetByteToQuickSaveChallenge);
    // REDIRECTED(Function1709aa);
    // REDIRECTED(RunBattleTowerTrainer);
    // REDIRECTED(Function17071b);
    // REDIRECTED(BattleTowerRoomMenu);
    // REDIRECTED(Function1708f0);
    // REDIRECTED(Function170807);
    // REDIRECTED(Set_s5_aa8d);
    // REDIRECTED(BattleTowerAction_UbersCheck);
    // REDIRECTED(v_BattleTowerBattle);
    // REDIRECTED(BattleTowerAction_SetExplanationRead);
    // REDIRECTED(Function17042c);
    // REDIRECTED(ResetBattleTowerTrainersSRAM);
    // REDIRECTED(CheckMobileEventIndex);
    // REDIRECTED(CopyBTTrainer_FromBT_OT_TowBT_OTTemp);
    // REDIRECTED(Function1709bb);
    // REDIRECTED(Function1700ba);
    // REDIRECTED(InitBattleTowerChallengeRAM);
    // REDIRECTED(BattleTowerAction_EggTicket);
    // REDIRECTED(Function1707f4);
    // REDIRECTED(BattleTower_GiveReward);
    // REDIRECTED(Function170729);
    // REDIRECTED(BattleTowerBattle);
    // REDIRECTED(String_MysteryJP);
    // REDIRECTED(BattleTower_SaveOptions);
    // REDIRECTED(Function170ad7);
    // REDIRECTED(Function1704e1);
    // REDIRECTED(BattleTowerAction);

    // engine/events/battle_tower/rules.c
    // REDIRECTED(OnlyThreeMonMayBeEnteredText);
    // REDIRECTED(BattleTower_ExecuteJumptable);
    // REDIRECTED(BattleTower_CheckPartyLengthIs3);
    // REDIRECTED(ExcuseMeYoureNotReadyText);
    // REDIRECTED(TheMonMustAllBeDifferentKindsText);
    // REDIRECTED(CheckForMobileBattleRules);
    // REDIRECTED(EggDoesNotQualifyText);
    // REDIRECTED(CheckBTRule_PartySpeciesAreUnique);
    // REDIRECTED(YouCantTakeAnEggText);
    // REDIRECTED(CheckBTRule_HasPartyAnEgg);
    // REDIRECTED(BattleTower_PleaseReturnWhenReady);
    // REDIRECTED(CheckPartyValueIsUnique);
    // REDIRECTED(CheckBTRule_PartyCountEq3);
    // REDIRECTED(TheMonMustNotHoldTheSameItemsText);
    // REDIRECTED(NeedAtLeastThreeMonText);
    // REDIRECTED(CheckBTRule_PartyItemsAreUnique);
    // REDIRECTED(BattleTower_CheckPartyHasThreeMonsThatAreNotEggs);
    // CONVERTED(v_CheckForBattleTowerRules);

    // mobile/mobile_5f.c
    // REDIRECTED(MobileErrorCode_33_201_Text);
    // REDIRECTED(MenuHeader_17d26a);
    // REDIRECTED(MenuData_ChallengeExplanationCancel);
    // REDIRECTED(MobileErrorCodes_33);
    // REDIRECTED(MobileErrorCode_33_103_Text);
    // REDIRECTED(MobileErrorCode_11_000_Text);
    // REDIRECTED(Function17f081);
    // REDIRECTED(MobileErrorCodes_17);
    // REDIRECTED(MobileErrorCodes_12);
    // REDIRECTED(MobileErrorCodes_23);
    // REDIRECTED(String_17fe9a);
    // REDIRECTED(MobileErrorCode_14_000_Text);
    // REDIRECTED(MobileErrorCode_CommuncationErrorText);
    // REDIRECTED(asm_17e0ee);
    // REDIRECTED(CheckStringForErrors);
    // REDIRECTED(MobileErrorCode_15_001_Text);
    // REDIRECTED(Function17e026);
    // REDIRECTED(Function17f181);
    // REDIRECTED(MobileErrorCodes_26);
    // REDIRECTED(MobileErrorCode_33_299_Text);
    // REDIRECTED(Mobile_CopyDefaultOTName);
    // REDIRECTED(MobileErrorCode_101_008_Text);
    // REDIRECTED(Function17f1d0);
    // REDIRECTED(Function17f0f8);
    // REDIRECTED(MobileErrorCode_32_408_Text);
    // REDIRECTED(Function17d0f3);
    // REDIRECTED(Function17f220);
    // REDIRECTED(MobileCommunicationErrorText);
    // REDIRECTED(Function17e165);
    // REDIRECTED(Function17e27f);
    // REDIRECTED(Function17e4dd);
    // REDIRECTED(Function17d246);
    // REDIRECTED(MobileScript_Prefecture);
    // REDIRECTED(Function17d1f1);
    // REDIRECTED(MobileErrorCodes_25);
    // REDIRECTED(Function17ded9);
    // REDIRECTED(Mobile5F_PlayersName);
    // REDIRECTED(Function17e3f0);
    // REDIRECTED(Function17d833);
    // REDIRECTED(Function17dbb1);
    // REDIRECTED(Function17f41d);
    // REDIRECTED(Function17dccf);
    // REDIRECTED(IncCrashCheckPointer_SaveGameData);
    // REDIRECTED(MobileErrorCodes_31);
    // REDIRECTED(Function17de32);
    // REDIRECTED(Function17e270);
    // REDIRECTED(Function17d902);
    // REDIRECTED(Function17dcaf);
    // REDIRECTED(Function17e309);
    // REDIRECTED(Unknown_17da94);
    // REDIRECTED(MobileErrorCode_31_002_Text);
    // REDIRECTED(MobileErrorCode_32_403_Text);
    // REDIRECTED(Function17e566);
    // REDIRECTED(Function17f5d2);
    // REDIRECTED(MobileErrorCode_101_004_Text);
    // REDIRECTED(MobileErrorCodes_14);
    // REDIRECTED(MobileErrorCodes_15);
    // REDIRECTED(PostalMarkGFX);
    // REDIRECTED(IncCrashCheckPointer);
    // REDIRECTED(String_17f6e8);
    // REDIRECTED(Function17d9e3);
    // REDIRECTED(Function17f3c9);
    // REDIRECTED(Function17da9c);
    // REDIRECTED(Function17e254);
    // REDIRECTED(MobileErrorCode_33_102_Text);
    // REDIRECTED(MobileErrorCode_ServerConnectionFailedText);
    // REDIRECTED(CheckStringContainsLessThanBNextCharacters);
    // REDIRECTED(Function17d2c0);
    // REDIRECTED(Function17e438);
    // REDIRECTED(Function17e261);
    // REDIRECTED(Function17d60b);
    // REDIRECTED(PokemonNewsPalettes);
    // REDIRECTED(MobileErrorCode_ServerErrorText);
    // REDIRECTED(Function17d5be);
    // REDIRECTED(Function17e5af);
    // REDIRECTED(Function17f3f0);
    // REDIRECTED(MobileErrorCode_33_101_Text);
    // REDIRECTED(Table_17f699);
    // REDIRECTED(Function17e32b);
    // REDIRECTED(Function17e691);
    // REDIRECTED(Function17f5c3);
    // REDIRECTED(Function17dca9);
    // REDIRECTED(Function17e349);
    // REDIRECTED(Function17d2ce);
    // REDIRECTED(Function17e613);
    // REDIRECTED(Function17ff23);
    // REDIRECTED(MenuData_17d272);
    // REDIRECTED(DisplayMobileError);
    // REDIRECTED(Function17db77);
    // REDIRECTED(IncCrashCheckPointer_SaveAfterLinkTrade);
    // REDIRECTED(Function17e600);
    // REDIRECTED(Function17d405);
    // REDIRECTED(Function17d3f6);
    // REDIRECTED(Mobile_CopyDefaultNickname);
    // REDIRECTED(Function17dc1f);
    // REDIRECTED(MobileErrorCodes_10);
    // REDIRECTED(Function17e1a1);
    // REDIRECTED(MobileErrorCodes_21);
    // REDIRECTED(Function17d85d);
    // REDIRECTED(Function17d6a1);
    // REDIRECTED(MobileErrorCodes_24);
    // REDIRECTED(Function17dadc);
    // REDIRECTED(Function17e133);
    // REDIRECTED(Function17d45a);
    // REDIRECTED(Function17e451);
    // REDIRECTED(MobileErrorCode_13_000_Text);
    // REDIRECTED(Function17d48d);
    // REDIRECTED(MobileErrorCode_15_002_Text);
    // REDIRECTED(RunMobileScript);
    // REDIRECTED(MobileErrorCode_32_404_Text);
    // REDIRECTED(Jumptable_17d483);
    // REDIRECTED(Function17d5f6);
    // REDIRECTED(Function17e51b);
    // REDIRECTED(Function17d78c);
    // REDIRECTED(MobileErrorCodes_22);
    // REDIRECTED(Function17dbe9);
    // REDIRECTED(MobileErrorCode_33_206_Text);
    // REDIRECTED(Function17f524);
    // REDIRECTED(Unknown_17da8c);
    // REDIRECTED(Mobile_CopyDefaultMailAuthor);
    // REDIRECTED(MobileErrorCode_101_002_Text);
    // REDIRECTED(Function17e2a7);
    // REDIRECTED(Function17d5c4);
    // REDIRECTED(Function17f154);
    // REDIRECTED(MobileErrorCode_12_000_Text);
    // REDIRECTED(MobileErrorCode_101_000_Text);
    // REDIRECTED(Function17e3e0);
    // REDIRECTED(Function17f6b7);
    // REDIRECTED(v_RunMobileScript);
    // REDIRECTED(MobileErrorCode_30_553_Text);
    // REDIRECTED(Function17d7b4);
    // REDIRECTED(Function17db2d);
    // REDIRECTED(Jumptable17d72a);
    // REDIRECTED(MobileErrorCode_26_000_Text);
    // REDIRECTED(MobileErrorCode_33_105_Text);
    // REDIRECTED(MobileErrorCodes_30);
    // REDIRECTED(Palette_17f6af);
    // REDIRECTED(PokemonNewsTileAttrmap);
    // REDIRECTED(Function17d6fd);
    // REDIRECTED(MobileErrorCode_10_000_Text);
    // REDIRECTED(Function17da31);
    // REDIRECTED(MobileErrorCode_30_450_Text);
    // REDIRECTED(asm_17d721);
    // REDIRECTED(Function17d314);
    // REDIRECTED(IncCrashCheckPointer_SaveBox);
    // REDIRECTED(HaveWantPals);
    // REDIRECTED(Function17dd30);
    // REDIRECTED(MobileErrorCode_33_104_Text);
    // REDIRECTED(MobileErrorCode_31_003_Text);
    // REDIRECTED(Function17e447);
    // REDIRECTED(MobileErrorCode_101_001_Text);
    // REDIRECTED(Function17e55b);
    // REDIRECTED(MobileSelectGFX);
    // REDIRECTED(Function17d78d);
    // REDIRECTED(Function17d370);
    // REDIRECTED(Function17dd13);
    // REDIRECTED(Function17f4f6);
    // REDIRECTED(MobileErrorCodes_13);
    // REDIRECTED(MobileErrorCode_101_009_Text);
    // REDIRECTED(MobileErrorCode_101_003_Text);
    // REDIRECTED(Function17d818);
    // REDIRECTED(IncCrashCheckPointer_SaveTrainerRankingsChecksum);
    // REDIRECTED(MobileScript_PlayerName);
    // REDIRECTED(MobileErrorCodes_20);
    // REDIRECTED(MobileErrorCode_15_003_Text);
    // REDIRECTED(HaveWantMap);
    // REDIRECTED(MobileErrorCode_32_503_Text);
    // REDIRECTED(MobileErrorCode_33_106_Text);
    // REDIRECTED(MobileErrorCodes_11);
    // REDIRECTED(MobileErrorCode_30_551_Text);
    // REDIRECTED(Function17f44f);
    // REDIRECTED(MobileErrorCode_101_006_Text);
    // REDIRECTED(Function17e0fd);
    // REDIRECTED(Function17f50f);
    // REDIRECTED(MobileErrorCode_22_000_Text);
    // REDIRECTED(HlToCrashCheckPointer);
    // REDIRECTED(MobileErrorCode_25_000_Text);
    // REDIRECTED(CheckStringForErrors_IgnoreTerminator);
    // REDIRECTED(Function17d2b6);
    // REDIRECTED(HaveWantGFX);
    // REDIRECTED(MobileErrorCode_101_005_Text);
    // REDIRECTED(MenuData_17dc96);
    // REDIRECTED(MobileErrorCode_15_000_Text);
    // REDIRECTED(MobileErrorCode_30_550_Text);
    // REDIRECTED(Function17dd49);
    // REDIRECTED(Function17e40f);
    // REDIRECTED(MenuHeader_ChallengeExplanationCancel);
    // REDIRECTED(Function17d98b);
    // REDIRECTED(MobileErrorCode_23_000_Text);
    // REDIRECTED(Function17d7c2);
    // REDIRECTED(MobileErrorCodes_16);
    // REDIRECTED(Mobile_CopyDefaultMail);
    // REDIRECTED(Function17e409);
    // REDIRECTED(Function17e427);
    // REDIRECTED(Function17f5e4);
    // REDIRECTED(MobileErrorCode_101_007_Text);
    // REDIRECTED(PokemonNewsGFX);
    // REDIRECTED(Function17ff3c);
    // REDIRECTED(Function17e43d);
    // REDIRECTED(Function17e571);
    // REDIRECTED(MobileErrorCodeTable);
    // REDIRECTED(MobileErrorCode_33_203_Text);
    // REDIRECTED(IncCrashCheckPointer_SaveChecksum);
    // REDIRECTED(Function17d93a);
    // REDIRECTED(MobileErrorCodes_32);
    // REDIRECTED(BattleTowerMobileError);
    // REDIRECTED(Function17de91);
    // REDIRECTED(Function17f27b);
    // REDIRECTED(Function17c000);
    // REDIRECTED(Function17db56);
    // REDIRECTED(Function17ddcd);
    // REDIRECTED(Function17d474);
    // REDIRECTED(Menu_ChallengeExplanationCancel);
    // REDIRECTED(Function17dc9f);
    // REDIRECTED(Function17d7d3);
    // REDIRECTED(Function17d711);
    // REDIRECTED(Function17d7e5);
    // REDIRECTED(Function17f2cb);
    // REDIRECTED(Function17e293);
    // REDIRECTED(Function17f382);
    // REDIRECTED(Function17e6de);
    // REDIRECTED(String_17ff68);

    // mobile/mobile_41.c
    // REDIRECTED(Function106403);
    // REDIRECTED(StubbedTrainerRankings_WildMonsCaught);
    // REDIRECTED(v_MobilePrintNum);
    // REDIRECTED(StubbedTrainerRankings_BattleTowerWins);
    // REDIRECTED(StubbedTrainerRankings_MonsEvolved);
    // REDIRECTED(StubbedTrainerRankings_FruitPicked);
    // REDIRECTED(UpdateTrainerRankingsChecksum);
    // REDIRECTED(InitializeTrainerRankings);
    // REDIRECTED(Function10649b);
    // REDIRECTED(Function1064d8);
    // REDIRECTED(StubbedTrainerRankings_EndSlotsWinStreak);
    // REDIRECTED(Function106453);
    // REDIRECTED(StubbedTrainerRankings_HallOfFame);
    // REDIRECTED(StubbedTrainerRankings_ColosseumDraws);
    // REDIRECTED(StubbedTrainerRankings_Selfdestruct);
    // REDIRECTED(StubbedTrainerRankings_StepCount);
    // REDIRECTED(StubbedTrainerRankings_MagikarpLength);
    // REDIRECTED(StubbedTrainerRankings_Increment4Byte);
    // REDIRECTED(DeleteMobileEventIndex);
    // REDIRECTED(Function1063cc);
    // REDIRECTED(StubbedTrainerRankings_Splash);
    // REDIRECTED(Stubbed_Function106462);
    // REDIRECTED(StubbedTrainerRankings_Healings);
    // REDIRECTED(Function1063d8);
    // REDIRECTED(StubbedTrainerRankings_AddToBattlePayouts);
    // REDIRECTED(RestoreMobileEventIndex);
    // REDIRECTED(StubbedTrainerRankings_Fly);
    // REDIRECTED(Function1063e5);
    // REDIRECTED(StubbedTrainerRankings_HallOfFame2);
    // REDIRECTED(StubbedTrainerRankings_WhiteOuts);
    // REDIRECTED(StubbedTrainerRankings_ColosseumLosses);
    // REDIRECTED(MobileDialingFrameGFX);
    // REDIRECTED(StubbedTrainerRankings_LinkBattles);
    // REDIRECTED(Function106331);
    // REDIRECTED(StubbedTrainerRankings_Unused1);
    // REDIRECTED(StubbedTrainerRankings_Increment2Byte);
    // REDIRECTED(StubbedTrainerRankings_Increment3Byte);
    // REDIRECTED(Function106442);
    // REDIRECTED(StubbedTrainerRankings_Increment);
    // REDIRECTED(StubbedTrainerRankings_Battles);
    // REDIRECTED(StubbedTrainerRankings_TMsHMsTaught);
    // REDIRECTED(Function106464);
    // REDIRECTED(StubbedTrainerRankings_Unused2);
    // REDIRECTED(StubbedTrainerRankings_PhoneCalls);
    // REDIRECTED(asm_1064ed);
    // REDIRECTED(CalculateTrainerRankingsChecksum);
    // REDIRECTED(StubbedTrainerRankings_WildBattles);
    // REDIRECTED(StubbedTrainerRankings_MysteryGift);
    // REDIRECTED(StubbedTrainerRankings_ColosseumWins);
    // REDIRECTED(Stubbed_Function106314);
    // REDIRECTED(StubbedTrainerRankings_AddToSlotsWinStreak);
    // REDIRECTED(Mobile_AlwaysReturnNotCarry);
    // REDIRECTED(Function1064c3);
    // REDIRECTED(StubbedTrainerRankings_Surf);
    // REDIRECTED(StubbedTrainerRankings_TreeEncounters);
    // REDIRECTED(StubbedTrainerRankings_AddToSlotsPayouts);
    // REDIRECTED(StubbedTrainerRankings_HookedEncounters);
    // REDIRECTED(Mobile_DummyReturnFalse);
    // REDIRECTED(StubbedTrainerRankings_Unused3);
    // REDIRECTED(StubbedTrainerRankings_TrainerBattles);
    // REDIRECTED(StubbedTrainerRankings_Trades);
    // REDIRECTED(Function106392);
    // REDIRECTED(StubbedTrainerRankings_Waterfall);
    // REDIRECTED(StubbedTrainerRankings_BugContestScore);
    // REDIRECTED(Function1063f3);
    // REDIRECTED(BackupMobileEventIndex);
    // REDIRECTED(Function10635c);
    // REDIRECTED(StubbedTrainerRankings_Increment1Byte);
    // REDIRECTED(StubbedTrainerRankings_EggsHatched);
    // REDIRECTED(StubbedTrainerRankings_LuckyNumberShow);
    // REDIRECTED(UpdateTrainerRankingsChecksum2);
    // REDIRECTED(VerifyTrainerRankingsChecksum);
    // REDIRECTED(Function10650a);

    // mobile/mobile_45_sprite_engine.c
    // REDIRECTED(Function11636e);
    // REDIRECTED(Unknown_115f13);
    // REDIRECTED(Unknown_115fc6);
    // REDIRECTED(Unknown_115ecc);
    // REDIRECTED(MobileDialingGFX);
    // REDIRECTED(Unknown_115fb1);
    // REDIRECTED(Unknown_115e86);
    // REDIRECTED(Unknown_115f30);
    // REDIRECTED(Unknown_115eb7);
    // REDIRECTED(Unknown_115ef6);
    // REDIRECTED(Unknown_115ee1);
    // REDIRECTED(Unknown_115e6c);
    // REDIRECTED(Function1161d5);
    // REDIRECTED(Function115dd3);
    // REDIRECTED(Function115d99);
    // REDIRECTED(Unknown_115f9c);
    // REDIRECTED(Unknown_115e61);
    // REDIRECTED(Function115e18);
    // REDIRECTED(Unknown_115e76);
    // REDIRECTED(Unknown_115e79);
    // REDIRECTED(Function11619d);
    // REDIRECTED(Unknown_115ff0);
    // REDIRECTED(MenuHeader_11628c);
    // REDIRECTED(Function115e22);
    // REDIRECTED(Function115dc3);
    // REDIRECTED(Unknown_116005);
    // REDIRECTED(Function1163c0);
    // REDIRECTED(Function1162cb);
    // REDIRECTED(Unknown_115f87);
    // REDIRECTED(Unknown_115f6a);
    // REDIRECTED(Function115e2b);
    // REDIRECTED(Unknown_115fdb);
    // REDIRECTED(Unknown_115ea6);
    // REDIRECTED(Function1162f2);
    // REDIRECTED(Function116294);
    // REDIRECTED(Function116441);
    // REDIRECTED(Function1161b8);
    // REDIRECTED(Unknown_115f4d);
    // REDIRECTED(Function116468);
    // REDIRECTED(Function11615a);
    // REDIRECTED(Unknown_115e59);

    // engine/events/battle_tower/trainer_text.c
    // CONVERTED(BTWinF15Text);
    // CONVERTED(BTGreetingM8Text);
    // CONVERTED(BTLossM10Text);
    // CONVERTED(BTWinM6Text);
    // CONVERTED(BTLossF4Text);
    // CONVERTED(BTFemaleTrainerTexts);
    // CONVERTED(BTWinF13Text);
    // CONVERTED(BTLossM20Text);
    // CONVERTED(BTLossM4Text);
    // CONVERTED(BTGreetingF10Text);
    // CONVERTED(BTLossM1Text);
    // CONVERTED(BTWinM9Text);
    // CONVERTED(BTWinM21Text);
    // CONVERTED(BTGreetingM2Text);
    // CONVERTED(BTWinM17Text);
    // CONVERTED(BTGreetingM16Text);
    // CONVERTED(BTGreetingM20Text);
    // CONVERTED(BTWinF3Text);
    // CONVERTED(BTGreetingF14Text);
    // CONVERTED(BTLossF9Text);
    // CONVERTED(BTGreetingF7Text);
    // CONVERTED(BTLossF7Text);
    // CONVERTED(BTGreetingM7Text);
    // CONVERTED(BTGreetingM11Text);
    // CONVERTED(BTLossM21Text);
    // CONVERTED(BTLossF14Text);
    // CONVERTED(BTLossF6Text);
    // CONVERTED(BTWinM7Text);
    // CONVERTED(BTGreetingF11Text);
    // CONVERTED(BTLossM7Text);
    // CONVERTED(BTGreetingM1Text);
    // CONVERTED(BTWinM19Text);
    // CONVERTED(BTLossM25Text);
    // CONVERTED(BTLossM5Text);
    // CONVERTED(BTLossM2Text);
    // CONVERTED(BTWinM11Text);
    // CONVERTED(BTGreetingM21Text);
    // CONVERTED(BTWinM24Text);
    // CONVERTED(BTGreetingM6Text);
    // CONVERTED(BTGreetingF4Text);
    // CONVERTED(BTLossF15Text);
    // CONVERTED(BTGreetingF6Text);
    // CONVERTED(BTGreetingM13Text);
    // CONVERTED(BTLossM8Text);
    // CONVERTED(BTLossM6Text);
    // CONVERTED(BTLossF1Text);
    // CONVERTED(BTLossF3Text);
    // CONVERTED(BTWinF4Text);
    // CONVERTED(BTLossM12Text);
    // CONVERTED(BTGreetingM24Text);
    // CONVERTED(BTGreetingM3Text);
    // CONVERTED(BTGreetingF2Text);
    // CONVERTED(BTWinF7Text);
    // CONVERTED(BTWinM12Text);
    // CONVERTED(BattleTowerText);
    // CONVERTED(BTLossM16Text);
    // CONVERTED(BTLossM19Text);
    // CONVERTED(BTWinM2Text);
    // CONVERTED(BTWinM8Text);
    // CONVERTED(BTLossF10Text);
    // CONVERTED(BTGreetingM10Text);
    // CONVERTED(BTLossM18Text);
    // CONVERTED(BTWinM15Text);
    // CONVERTED(BTWinM4Text);
    // CONVERTED(BTGreetingF12Text);
    // CONVERTED(BTWinM5Text);
    // CONVERTED(BTWinF6Text);
    // CONVERTED(BTMaleTrainerTexts);
    // CONVERTED(BTWinF10Text);
    // CONVERTED(BTGreetingF13Text);
    // CONVERTED(BTWinM13Text);
    // CONVERTED(BTWinM25Text);
    // CONVERTED(BTWinF11Text);
    // CONVERTED(BTLossM17Text);
    // CONVERTED(BTGreetingM14Text);
    // CONVERTED(BTGreetingM12Text);
    // CONVERTED(BTWinF12Text);
    // CONVERTED(BTLossF8Text);
    // CONVERTED(BTLossF11Text);
    // CONVERTED(BTWinM14Text);
    // CONVERTED(BTLossM23Text);
    // CONVERTED(BTWinF5Text);
    // CONVERTED(BTGreetingF8Text);
    // CONVERTED(BTGreetingM25Text);
    // CONVERTED(BTLossM24Text);
    // CONVERTED(BTGreetingM18Text);
    // CONVERTED(BTGreetingF15Text);
    // CONVERTED(BTWinM16Text);
    // CONVERTED(BTWinM18Text);
    // CONVERTED(BTGreetingM5Text);
    // CONVERTED(BTGreetingM22Text);
    // CONVERTED(BTWinF9Text);
    // CONVERTED(BTGreetingF3Text);
    // CONVERTED(BTGreetingF5Text);
    // CONVERTED(BTLossM15Text);
    // CONVERTED(BTLossM11Text);
    // CONVERTED(BTLossM22Text);
    // CONVERTED(BTLossF2Text);
    // CONVERTED(BTGreetingF1Text);
    // CONVERTED(BTWinF14Text);
    // CONVERTED(BTWinM3Text);
    // CONVERTED(BTLossF13Text);
    // CONVERTED(BTLossM9Text);
    // CONVERTED(BTWinM22Text);
    // CONVERTED(BTGreetingM23Text);
    // CONVERTED(BTGreetingM9Text);
    // CONVERTED(BTLossF12Text);
    // CONVERTED(BTGreetingM19Text);
    // CONVERTED(BTGreetingF9Text);
    // CONVERTED(BTLossM13Text);
    // CONVERTED(BTGreetingM15Text);
    // CONVERTED(BTGreetingM17Text);
    // CONVERTED(BTWinM10Text);
    // CONVERTED(BTLossM3Text);
    // CONVERTED(BTWinF2Text);
    // CONVERTED(BTGreetingM4Text);
    // CONVERTED(BTWinM20Text);
    // CONVERTED(BTWinM23Text);
    // CONVERTED(BTWinF8Text);
    // CONVERTED(BTWinM1Text);
    // CONVERTED(BTWinF1Text);
    // CONVERTED(BTLossM14Text);
    // CONVERTED(BTLossF5Text);

    // engine/pokedex/pokedex_2.c
    // CONVERTED(DisplayDexEntry);
    // CONVERTED(GetDexEntryPointer);
    // REDIRECTED(AnimateDexSearchSlowpoke);
    // REDIRECTED(DoDexSearchSlowpokeFrame);
    // REDIRECTED(POKeString);
    // REDIRECTED(GetDexEntryPagePointer);

    // engine/pokedex/new_pokedex_entry.c
    CONVERTED(NewPokedexEntry);

    // engine/events/fish.c
    // REDIRECTED(GetFishGroupIndex);
    CONVERTED(Fish);

    // engine/events/shuckle.c
    CONVERTED(ReturnShuckie);
    CONVERTED(GiveShuckle);
    // CONVERTED(SpecialShuckleNickname);
    // CONVERTED(SpecialShuckleOT);

    // engine/events/poisonstep.c
    // CONVERTED(DoPoisonStep);

    // engine/events/poisonstep_pals.c
    // CONVERTED(LoadPoisonBGPals);

    // engine/events/pokerus/check_pokerus.c
    // CONVERTED(v_CheckPokerus);

    // engine/events/pokerus/apply_pokerus_tick.c
    // CONVERTED(ApplyPokerusTick);

    // engine/pokemon/knows_move.c
    // CONVERTED(KnowsMove);

    // engine/events/battle_tower/load_trainer.c
    // CONVERTED(LoadRandomBattleTowerMon);
    CONVERTED(LoadOpponentTrainerAndPokemon);

    // engine/pokemon/search2.c
    // CONVERTED(FindThatSpecies);
    // REDIRECTED(FindAboveLevel);
    // REDIRECTED(v_FindPartyMonAboveLevel);
    // CONVERTED(v_FindPartyMonThatSpeciesYourTrainerID);
    // REDIRECTED(FindAtLeastThatHappy);
    // CONVERTED(v_FindPartyMonThatSpecies);
    // REDIRECTED(v_FindPartyMonAtLeastThatHappy);
    // REDIRECTED(RetroactivelyIgnoreEggs);

    // engine/events/battle_tower/get_trainer_class.c
    // CONVERTED(GetMobileOTTrainerClass);

    // mobile/mobile_5c.c
    // CONVERTED(AsciiFontGFX);
    // CONVERTED(Function170c8b);
    // CONVERTED(Function172eb9);
    // CONVERTED(String_171c73);
    // CONVERTED(String_172e4e);
    // CONVERTED(Palette_172edf);
    // CONVERTED(Function171a36);
    // CONVERTED(Function170c06);
    // CONVERTED(Function171a95);
    // CONVERTED(Function172e78);
    // CONVERTED(PasswordBottomTilemap);
    // CONVERTED(PichuAnimatedMobileGFX);
    // CONVERTED(asm_171baf);
    // CONVERTED(ChooseMobileCenterTilemap);
    // CONVERTED(Function17005a);
    // CONVERTED(Function1719c8);
    // CONVERTED(String_171aa7);
    // CONVERTED(Function171ac9);
    CONVERTED(Clears5_a89a);
    // CONVERTED(String_172e3f);
    // CONVERTED(Stadium2N64Tilemap);
    // CONVERTED(Function171a11);
    // CONVERTED(Stadium2N64Attrmap);
    // CONVERTED(PasswordSlowpokeLZ);
    // CONVERTED(Function170000);
    // CONVERTED(Function170d02);
    // CONVERTED(Function171bcc);
    // CONVERTED(Function171ccd);
    // CONVERTED(CheckBTMonMovesForErrors);
    // CONVERTED(Function171c66);
    // CONVERTED(Function171cf0);
    // CONVERTED(String_172e5d);
    // CONVERTED(asm_171ba5);
    // CONVERTED(Stadium2N64GFX);
    // CONVERTED(Function171ad7);
    // CONVERTED(MobilePasswordAttrmap);
    // CONVERTED(Function171c2c);
    // CONVERTED(Function1719ed);
    // CONVERTED(Function171c41);
    // CONVERTED(Function171aec);
    // CONVERTED(Function171bdc);
    // CONVERTED(ElectroBallMobileGFX);
    // CONVERTED(Function170cc6);
    // CONVERTED(Function171c87);
    // CONVERTED(Function171b9f);
    // CONVERTED(Function171beb);
    // CONVERTED(Function171c39);
    // CONVERTED(PasswordShiftTilemap);
    // CONVERTED(MenuHeader_171c6b);
    // CONVERTED(ChooseMobileCenterAttrmap);
    // CONVERTED(String_172e58);
    // CONVERTED(PasswordTopTilemap);
    // CONVERTED(PichuBorderMobileGFX);
    // CONVERTED(Jumptable_171a45);
    // CONVERTED(Function171bbd);
    // CONVERTED(Function1719d6);
    // CONVERTED(MobilePasswordPalettes);
    // CONVERTED(Function171b42);
    // CONVERTED(String_172e31);
    // CONVERTED(Function171b4b);
    // CONVERTED(asm_171c60);
    // CONVERTED(Function171a5d);
    // CONVERTED(Function171d2b);
    // CONVERTED(Function171b85);
    // CONVERTED(Function170be4);

    // engine/pokemon/level_up_happiness.c
    CONVERTED(LevelUpHappinessMod);

    // engine/games/unown_puzzle.c
    // REDIRECTED(HoOhPuzzleLZ);
    // REDIRECTED(UnownPuzzle_AddPuzzlePieceBorders);
    // REDIRECTED(GetUnownPuzzleCoordData);
    // REDIRECTED(CheckSolvedUnownPuzzle);
    // REDIRECTED(UnownPuzzle_UpdateTilemap);
    // REDIRECTED(UnownPuzzle_InvalidAction);
    // REDIRECTED(ConvertLoadedPuzzlePieces);
    // REDIRECTED(UnownPuzzleCoordData);
    // REDIRECTED(UnownPuzzle_A);
    // REDIRECTED(PlaceStartCancelBox);
    // REDIRECTED(PuzzlePieceBorderData);
    // REDIRECTED(UnownPuzzleStartCancelLZ);
    // REDIRECTED(KabutoPuzzleLZ);
    // REDIRECTED(UnownPuzzleCursorGFX);
    // REDIRECTED(UnownPuzzle_CheckCurrentTileOccupancy);
    // REDIRECTED(UnownPuzzleJumptable);
    // REDIRECTED(FillUnoccupiedPuzzleSpace);
    // REDIRECTED(OmanytePuzzleLZ);
    // REDIRECTED(UnownPuzzle_Quit);
    // REDIRECTED(PlaceUnownPuzzlePieceGFX);
    // REDIRECTED(LoadUnownPuzzlePiecesGFX);
    // REDIRECTED(RedrawUnownPuzzlePieces);
    // REDIRECTED(InitUnownPuzzlePiecePositions);
    // REDIRECTED(PlaceStartCancelBoxBorder);
    // REDIRECTED(GetCurrentPuzzlePieceVTileCorner);
    CONVERTED(v_UnownPuzzle);
    // REDIRECTED(AerodactylPuzzleLZ);
    // REDIRECTED(UnownPuzzle_FillBox);

    // engine/link/place_waiting_text.c
    CONVERTED(PlaceWaitingText);

    // engine/events/pokerus/pokerus.c
    CONVERTED(GivePokerusAndConvertBerries);
    CONVERTED(ConvertBerriesToBerryJuice);

    // engine/events/basement_key.c
    CONVERTED(v_BasementKey);

    // engine/events/buena.c
    // CONVERTED(Buena_PrizeMenu);
    // CONVERTED(Buena_GetPrize);
    // CONVERTED(Buena_PlacePrizeMenuBox);
    // CONVERTED(PrintBlueCardBalance);
    CONVERTED(BuenasPassword);
    // CONVERTED(Buena_DisplayBlueCardBalance);
    // CONVERTED(BlueCardBalanceMenuHeader);
    CONVERTED(BuenaPrize);

    // engine/events/buena_menu.c
    CONVERTED(AskRememberPassword);
    CONVERTED(Buena_ExitMenu);

    // engine/pokemon/search.c
    // CONVERTED(CheckOwnMonAnywhere);
    // CONVERTED(CheckOwnMon);
    CONVERTED(MonCheck);
    // CONVERTED(SearchBoxAddressTable);
    CONVERTED(BeastsCheck);
    // CONVERTED(UpdateOTPointer);

    // engine/events/move_deleter.c
    CONVERTED(MoveDeletion);

    // engine/events/dratini.c
    CONVERTED(GiveDratini);

    // engine/pokemon/learn.c
    // CONVERTED(AskForgetMoveText);
    // CONVERTED(MoveAskForgetText);
    // CONVERTED(LearnMove);
    // CONVERTED(Text_1_2_and_Poof);
    // CONVERTED(ForgetMove);
    // CONVERTED(DidNotLearnMoveText);
    // CONVERTED(StopLearningMoveText);
    // CONVERTED(MoveCantForgetHMText);
    // CONVERTED(LearnedMoveText);

    // engine/movie/trade_animation.c
    // CONVERTED(LoadTradeBallAndCableGFX);
    // CONVERTED(TradeAnim_TubeToPlayer5);
    // CONVERTED(TradeCableGFX);
    // CONVERTED(TradeAnim_OTSendsText1);
    // CONVERTED(TradeAnim_TubeToOT2);
    // CONVERTED(TradeAnim_CopyBoxFromDEtoHL);
    // CONVERTED(TradeGameBoyLZ);
    // CONVERTED(TradeAnim_AnimateFrontpic);
    // CONVERTED(TrademonStats_PrintOTName);
    // CONVERTED(TradeAnim_TubeToPlayer1);
    // CONVERTED(TradeAnim_Wait40);
    // CONVERTED(TradeAnim_ScrollOutRight);
    // CONVERTED(LoadTradeBubbleGFX);
    // CONVERTED(TrademonStats_PrintSpeciesName);
    // CONVERTED(TradeAnim_TubeToPlayer6);
    // CONVERTED(TradeAnim_GiveTrademonSFX);
    // CONVERTED(TradeAnim_TubeToOT6);
    // CONVERTED(TradeAnim_Wait96);
    // CONVERTED(TradeAnim_TubeToPlayer2);
    CONVERTED(TradeAnimation);
    // CONVERTED(TrademonStats_Egg);
    // CONVERTED(ShowPlayerTrademonStats);
    // CONVERTED(TradeAnim_OTBidsFarewell);
    // CONVERTED(TradeAnim_NormalPals);
    // CONVERTED(TradeBubbleGFX);
    // CONVERTED(DebugTrade);
    // CONVERTED(TradeAnim_GetTrademonSFX);
    // CONVERTED(TradeAnim_Poof);
    // CONVERTED(TrademonStats_PrintTrademonID);
    // CONVERTED(TradeAnim_AnimateTrademonInTube);
    // CONVERTED(TradeAnim_Wait180IfOTEgg);
    // CONVERTED(TradeAnim_GetNicknamename);
    // CONVERTED(TradeAnim_RockingBall);
    // CONVERTED(TradeAnim_SetupGivemonScroll);
    // CONVERTED(LinkTradeAnim_LoadTradePlayerNames);
    // CONVERTED(TradeAnim_TubeToOT5);
    // CONVERTED(TradeAnim_EnterLinkTube2);
    // CONVERTED(TradeAnim_OTSendsText2);
    // CONVERTED(TradeLinkTubeTilemap);
    // CONVERTED(TradeAnim_End);
    // CONVERTED(TradeAnim_TubeToPlayer8);
    // CONVERTED(TradeArrowLeftGFX);
    // CONVERTED(TradeAnim_GetFrontpic);
    // CONVERTED(IsOTTrademonEgg);
    // CONVERTED(TradeAnim_TubeAnimJumptable);
    // CONVERTED(TradeAnim_InitTubeAnim);
    // CONVERTED(TradeAnim_SentToOTText);
    // CONVERTED(TradeAnim_DropBall);
    // CONVERTED(TradeAnim_ShowGetmonData);
    // CONVERTED(ShowOTTrademonStats);
    // CONVERTED(TradeAnim_TubeToOT4);
    // CONVERTED(TradeAnim_TubeToPlayer7);
    // CONVERTED(TradeAnim_Wait80);
    // CONVERTED(TradeAnim_Wait80IfOTEgg);
    // CONVERTED(TradeAnim_TextboxScrollStart);
    // CONVERTED(TrademonStats_WaitBGMap);
    // CONVERTED(TradeAnim_TubeToOT3);
    // CONVERTED(TradeAnim_EnterLinkTube1);
    // CONVERTED(TradeArrowRightGFX);
    // CONVERTED(TradeAnim_WaitAnim);
    // CONVERTED(TradeAnim_WaitAnim2);
    // CONVERTED(TradeAnim_BlankTilemap);
    // CONVERTED(TradeAnim_FlashBGPals);
    // CONVERTED(TrademonStats_MonTemplate);
    // CONVERTED(TradeGameBoyTilemap);
    // CONVERTED(TradeAnim_TubeToOT7);
    // CONVERTED(LinkTradeAnim_LoadTradeMonSpecies);
    // CONVERTED(TradeAnim_Wait80Frames);
    // CONVERTED(TradeAnim_TubeToPlayer3);
    CONVERTED(TradeAnimationPlayer2);
    // CONVERTED(TradeAnim_ExitLinkTube);
    // CONVERTED(TradePoofGFX);
    // CONVERTED(TradeAnim_ShowGivemonFrontpic);
    // CONVERTED(TradeBallGFX);
    // CONVERTED(TradeAnim_ScrollOutRight2);
    // CONVERTED(TradeAnim_TakeCareOfText);
    // CONVERTED(TradeAnim_DoGivemonScroll);
    // CONVERTED(TrademonStats_PrintSpeciesNumber);
    // CONVERTED(TradeAnim_AdvanceScriptPointer);
    // CONVERTED(RunTradeAnimScript);
    // CONVERTED(TradeAnim_BulgeThroughTube);
    // CONVERTED(TradeAnim_FrontpicScrollStart);
    // CONVERTED(TradeAnim_TubeToPlayer4);
    // CONVERTED(TradeAnim_ShowFrontpic);
    // CONVERTED(TradeAnim_ShowGetmonFrontpic);
    // CONVERTED(TradeAnim_TubeToOT8);
    // CONVERTED(TradeAnim_PlaceTrademonStatsOnTubeAnim);
    // CONVERTED(TradeAnim_ShowGivemonData);
    // CONVERTED(DoTradeAnimation);
    // CONVERTED(TradeAnim_CopyTradeGameBoyTilemap);
    // CONVERTED(TradeAnim_IncrementJumptableIndex);
    // CONVERTED(TradeAnim_TubeToOT1);

    // engine/gfx/trademon_frontpic.c
    CONVERTED(GetTrademonFrontpic);
    CONVERTED(AnimateTrademonFrontpic);

    // engine/events/lucky_number.c
    CONVERTED(PrintTodaysLuckyNumber);
    CONVERTED(CheckForLuckyNumberWinners);

    // engine/events/move_tutor.c
    // REDIRECTED(CheckCanLearnMoveTutorMove);
    CONVERTED(MoveTutor);

    // engine/events/play_slow_cry.c
    CONVERTED(PlaySlowCry);

    // engine/movie/init_hof_credits.c
    // CONVERTED(InitDisplayForRedCredits);
    // CONVERTED(InitDisplayForHallOfFame);
    // CONVERTED(ResetDisplayBetweenHallOfFameMons);

    // engine/movie/credits.c
    // CONVERTED(Credits_HandleBButton);
    // CONVERTED(Credits_HandleAButton);
    // CONVERTED(Credits);
    // CONVERTED(Credits_RequestGFX);
    // CONVERTED(Credits_Jumptable);
    // CONVERTED(CreditsDittoGFX);
    // CONVERTED(DrawCreditsBorder);
    // CONVERTED(Credits_LoadBorderGFX);
    // CONVERTED(CreditsPalettes);
    // CONVERTED(Credits_LoopBack);
    // CONVERTED(CreditsBorderGFX);
    // CONVERTED(ParseCredits);
    // CONVERTED(CreditsPichuGFX);
    // CONVERTED(CreditsMonsGFX);
    // CONVERTED(Credits_Next);
    // CONVERTED(CreditsSmoochumGFX);
    // CONVERTED(Credits_PrepBGMapUpdate);
    // CONVERTED(GetCreditsPalette);
    // CONVERTED(CreditsIgglybuffGFX);
    // CONVERTED(Credits_LYOverride);
    // CONVERTED(Credits_TheEnd);
    // CONVERTED(Credits_UpdateGFXRequestPath);
    // CONVERTED(ConstructCreditsTilemap);

    // engine/events/halloffame.c
    // CONVERTED(HOF_SlideBackpic);
    // CONVERTED(DisplayHOFMon);
    // CONVERTED(HOF_SlideFrontpic);
    // CONVERTED(LoadHOFTeam);
    // CONVERTED(HOF_AnimatePlayerPic);
    // CONVERTED(v_HallOfFamePC);
    CONVERTED(HallOfFame);
    // CONVERTED(HallOfFame_PlayMusicDE);
    // CONVERTED(HallOfFame_FadeOutMusic);
    // CONVERTED(AnimateHallOfFame);
    // CONVERTED(GetHallOfFameParty);
    CONVERTED(RedCredits);
    // CONVERTED(AnimateHOFMonEntrance);

    // engine/pokemon/european_mail.c
    // CONVERTED(ConvertSpanishItalianMailToEnglish);
    // CONVERTED(ConvertFrenchGermanMailToEnglish);
    // CONVERTED(StandardEnglishFont);
    // CONVERTED(ConvertEnglishMailToSpanishItalian);
    // CONVERTED(ConvertEnglishMailToFrenchGerman);
    // CONVERTED(SpanishItalianFont);
    // CONVERTED(IsMailEuropean);
    // CONVERTED(FrenchGermanFont);

    // engine/pokemon/switchpartymons.c
    CONVERTED(v_SwitchPartyMons);

    // engine/pokemon/mon_submenu.c
    // CONVERTED(TerminateMonSubmenu);
    // CONVERTED(AddMonMenuItem);
    // CONVERTED(PopulateMonMenu);
    // CONVERTED(ResetMonSubmenu);
    // CONVERTED(GetMonMenuString);
    // CONVERTED(MonMenuLoop);
    // CONVERTED(BattleMonMenu);
    // CONVERTED(MonSubmenu);
    // CONVERTED(IsFieldMove);
    // CONVERTED(GetMonSubmenuItems);

    // engine/battle/link_result.c
    CONVERTED(DetermineLinkBattleResult);

    // engine/events/sacred_ash.c
    CONVERTED(v_SacredAsh);
    // CONVERTED(SacredAshScript);
    // CONVERTED(CheckAnyFaintedMon);

    // engine/events/sweet_scent.c
    // CONVERTED(UseSweetScentText);
    // CONVERTED(SweetScentNothingText);
    // CONVERTED(SweetScentNothing);
    // CONVERTED(SweetScentEncounter);
    CONVERTED(SweetScentFromMenu);

    // engine/printer/print_party.c
    CONVERTED(PrintPage1);
    CONVERTED(PrintPartyMonPage2);
    // CONVERTED(PrintParty_MoveString);
    // CONVERTED(GBPrinterString_Printing);
    // CONVERTED(GBPrinterString_CheckingLink);
    // REDIRECTED(GetCurPartyMonName);
    CONVERTED(PrintPage2);
    // CONVERTED(PrintParty_IDNoString);
    // CONVERTED(PlaceGenderAndShininess);
    // CONVERTED(PrintParty_NoMoveString);
    // CONVERTED(GBPrinterString_PrinterError2);
    // CONVERTED(PlaceMoveNameString);
    // CONVERTED(GBPrinterString_PrinterError1);
    // CONVERTED(GBPrinterHPIcon);
    // CONVERTED(GBPrinterString_Transmitting);
    // CONVERTED(GBPrinterLvIcon);
    // CONVERTED(PrintParty_OTString);
    // CONVERTED(PrintParty_StatsString);
    CONVERTED(PrintPartyMonPage1);
    // CONVERTED(GBPrinterString_Null);
    // CONVERTED(GBPrinterStrings);
    // CONVERTED(GBPrinterString_PrinterError4);
    // CONVERTED(GBPrinterString_PrinterError3);

    // engine/printer/printer.c
    // REDIRECTED(PlacePrinterStatusStringBorderless);
    // REDIRECTED(Printer_PlaceBottomBorders);
    // REDIRECTED(CheckPrinterStatus);
    CONVERTED(Printer_ResetJoypadRegisters);
    // CONVERTED(Printer_PrepareTilemapForPrint);
    CONVERTED(Printer_ExitPrinter);
    // REDIRECTED(PrintPCBox_Page3);
    // CONVERTED(PrintMailAndExit);
    CONVERTED(Printer_CopyTilemapToBuffer);
    // REDIRECTED(PrinterStatusStringPointers);
    // CONVERTED(SendScreenToPrinter);
    // REDIRECTED(PrintPCBox);
    // REDIRECTED(PlacePrinterStatusString);
    // REDIRECTED(PrintPCBox_Page2);
    // REDIRECTED(String_PressBToCancel);
    CONVERTED(Printer_PlaceTopBorder);
    // REDIRECTED(Printer_CopyBufferToTilemap);
    // REDIRECTED(Printer_RestartMapMusic);
    // REDIRECTED(v_PrintDiploma);
    // REDIRECTED(PrintUnownStamp);
    // REDIRECTED(Printer_PlaceSideBorders);
    // REDIRECTED(CheckCancelPrint);
    CONVERTED(PrintDexEntry);
    // REDIRECTED(Printer_GetMonGender);
    CONVERTED(PrintPartymon);
    // REDIRECTED(Printer_PrintBoxListSegment);
    CONVERTED(Printer_PlayMusic);
    // REDIRECTED(Printer_GetBoxMonSpecies);
    // REDIRECTED(PrintMail);
    // REDIRECTED(PrintPCBox_Page4);
    // REDIRECTED(Printer_PlaceEmptyBoxSlotString);
    CONVERTED(Printer_CleanUpAfterSend);
    // REDIRECTED(Printer_ResetRegistersAndStartDataSend);
    // REDIRECTED(PrintPCBox_Page1);

    // engine/events/print_photo.c
    CONVERTED(PhotoStudio);

    // engine/link/mystery_gift_2.c
    // CONVERTED(MysteryGiftFallbackItem);
    // CONVERTED(MysteryGiftGetItem);
    CONVERTED(StageDataForMysteryGift);
    // CONVERTED(MysteryGiftGetDecoration);

    // engine/movie/evolution_animation.c
    CONVERTED(EvolutionAnimation);

    // engine/events/diploma.c
    // CONVERTED(PrintDiplomaPage2);
    // CONVERTED(PlaceDiplomaOnScreen);
    // CONVERTED(DiplomaPage1Tilemap);
    // CONVERTED(Diploma_DummyFunction);
    // CONVERTED(DiplomaPage2Tilemap);
    // CONVERTED(DiplomaGFX);
    // CONVERTED(v_Diploma);

    // engine/games/slot_machine.c
    // CONVERTED(Slots_StopReel2);
    // CONVERTED(Slots_InitBias);
    // CONVERTED(SlotsAction_GiveEarnedCoins);
    // CONVERTED(Slots_StopReel1);
    // CONVERTED(Slots_GetPals);
    // CONVERTED(SlotsLoop);
    // CONVERTED(Slots_UpdateReelPositionAndOAM);
    // CONVERTED(ReelAction_DoubleRate);
    // CONVERTED(ReelAction_QuadrupleRate);
    // CONVERTED(ReelAction_InitChansey);
    // CONVERTED(AnimateSlotReelIcons);
    // CONVERTED(SlotsAction_WaitReel3);
    // CONVERTED(SlotsAction_WaitStopReel2);
    // CONVERTED(SlotsAction_WaitStart);
    // CONVERTED(SlotsAction_WaitReel1);
    // CONVERTED(Slots_WaitSFX);
    // CONVERTED(Slots_Lights3OnOff);
    CONVERTED(v_SlotMachine);
    // CONVERTED(Slots_GetPayout);
    // CONVERTED(ReelAction_StartSlowAdvanceReel3);
    // CONVERTED(Slots_CheckCoinCaseFull);
    // CONVERTED(ReelAction_StopReelIgnoreJoypad);
    // CONVERTED(Slots_AskBet);
    // CONVERTED(Reel3Tilemap);
    // CONVERTED(ReelAction_StopReel1);
    // CONVERTED(Slots1LZ);
    // CONVERTED(ReelAction_WaitChansey);
    // CONVERTED(ReelAction_InitGolem);
    // CONVERTED(Slots_GetNumberOfGolems);
    // CONVERTED(Slots_Lights1OnOff);
    // CONVERTED(DebugPrintSlotBias);
    // CONVERTED(Slots2LZ);
    // CONVERTED(SlotsAction_PayoutAnim);
    // CONVERTED(SlotsAction_FlashScreen);
    // CONVERTED(ReelAction_QuarterRate);
    // CONVERTED(ReelAction_DoNothing);
    // CONVERTED(ReelAction_Unused);
    // CONVERTED(ReelAction_WaitReel2SkipTo7);
    // CONVERTED(SlotsAction_WaitStopReel3);
    // CONVERTED(ReelAction_NormalRate);
    // CONVERTED(Slots_CopyReelState);
    // CONVERTED(Slots_StopReel3);
    // CONVERTED(ReelAction_WaitDropReel);
    // CONVERTED(SlotsAction_Init);
    // CONVERTED(Slots_CheckMatchedFirstTwoReels);
    // CONVERTED(SlotsJumptable);
    // CONVERTED(Slots_IlluminateBetLights);
    // CONVERTED(Slots_Lights2OnOff);
    // CONVERTED(SlotsAction_Next);
    // CONVERTED(Slots_StopReel);
    // CONVERTED(Reel2Tilemap);
    // CONVERTED(ReelAction_EndGolem);
    // CONVERTED(Slots_LoadReelState);
    // CONVERTED(Slots_AnimateGolem);
    // CONVERTED(ReelActionJumptable);
    // CONVERTED(Slots_PlaySFX);
    // CONVERTED(Slots3LZ);
    // CONVERTED(ReelAction_StopReel2);
    // CONVERTED(SlotsAction_WaitReel2);
    // CONVERTED(ReelAction_CheckDropReel);
    // CONVERTED(SlotsAction_Quit);
    // CONVERTED(Slots_PayoutText);
    // CONVERTED(ReelAction_WaitSlowAdvanceReel3);
    // CONVERTED(Slots_TurnLightsOnOrOff);
    // CONVERTED(ReelAction_HalfRate);
    // CONVERTED(SlotsAction_BetAndStart);
    // CONVERTED(SlotsTilemap);
    // CONVERTED(Slots_AnimateChansey);
    // CONVERTED(SlotsAction_PayoutTextAndAnim);
    // CONVERTED(ReelAction_SetUpReel2SkipTo7);
    // CONVERTED(ReelAction_StopReel3);
    // CONVERTED(Slots_GetCurrentReelState);
    // CONVERTED(ReelAction_WaitGolem);
    // CONVERTED(Slots_InitReelTiles);
    // CONVERTED(Slots_CheckMatchedAllThreeReels);
    // CONVERTED(GetUnknownSlotReelData);
    // CONVERTED(ReelAction_WaitEgg);
    // CONVERTED(Slots_AskPlayAgain);
    // CONVERTED(ReelAction_FastSpinReel2UntilLinedUp7s);
    // CONVERTED(Slots_DeilluminateBetLights);
    // CONVERTED(SlotsAction_FlashIfWin);
    // CONVERTED(Slots_SpinReels);
    // CONVERTED(SlotsAction_WaitStopReel1);
    // CONVERTED(ReelAction_DropReel);
    // CONVERTED(SlotsAction_RestartOrQuit);
    // CONVERTED(Reel1Tilemap);

    // engine/events/magnet_train.c
    // CONVERTED(MagnetTrainBGTiles);
    // CONVERTED(MagnetTrain_LoadGFX_PlayMusic);
    // CONVERTED(MagnetTrain_UpdateLYOverrides);
    // CONVERTED(GetMagnetTrainBGTiles);
    CONVERTED(MagnetTrain);
    // CONVERTED(MagnetTrain_Jumptable);
    // CONVERTED(SetMagnetTrainPals);
    // CONVERTED(MagnetTrain_Jumptable_FirstRunThrough);
    // CONVERTED(DrawMagnetTrain);
    // CONVERTED(MagnetTrain_InitLYOverrides);
    // CONVERTED(MagnetTrainTilemap);

    // mobile/mobile_40.c
    // REDIRECTED(Function10107d);
    // REDIRECTED(Function10342c);
    // REDIRECTED(ClosingLinkText);
    // REDIRECTED(Function100720);
    // REDIRECTED(Function1010de);
    // REDIRECTED(Function1004e9);
    // REDIRECTED(Jumptable_1024ba);
    // REDIRECTED(Function101d03);
    // REDIRECTED(Function101e4f);
    // REDIRECTED(Function100697);
    // REDIRECTED(Function102f50);
    // REDIRECTED(Function10219f);
    // REDIRECTED(v_SelectMonsForMobileBattle);
    // REDIRECTED(Function10307f);
    // REDIRECTED(Function1035c6);
    // REDIRECTED(Function100b45);
    // REDIRECTED(Mobile_SetOverworldDelay);
    // REDIRECTED(Function102c2e);
    // REDIRECTED(Function1034f1);
    // REDIRECTED(Function10296e);
    // REDIRECTED(Function10176f);
    // REDIRECTED(Function1018a8);
    // REDIRECTED(String_101f32);
    // REDIRECTED(Function101705);
    // REDIRECTED(Function102d34);
    // REDIRECTED(Function101ed3);
    // REDIRECTED(WantToRushThroughAMobileBattleText);
    // REDIRECTED(String1006c2);
    // REDIRECTED(String_10355f);
    // REDIRECTED(Jumptable_101494);
    // REDIRECTED(Function100675);
    // REDIRECTED(MobileTradeLightsGFX);
    // REDIRECTED(Function1008e0);
    // REDIRECTED(Unknown_1035e7);
    // REDIRECTED(Function100970);
    // REDIRECTED(Function1037eb);
    // REDIRECTED(Function102ea8);
    // REDIRECTED(Function102b68);
    // REDIRECTED(Function10228e);
    // REDIRECTED(Function10383c);
    // REDIRECTED(Function102738);
    // REDIRECTED(MobileBattleRulesText);
    // REDIRECTED(Function10350f);
    // REDIRECTED(Function1029cf);
    // REDIRECTED(Unknown_1035fe);
    // REDIRECTED(Function1011f1);
    // REDIRECTED(Function10145b);
    // REDIRECTED(Function1028a5);
    // REDIRECTED(Function101663);
    // REDIRECTED(Jumptable_101457);
    // REDIRECTED(Function1007f6);
    // REDIRECTED(Function102c21);
    // REDIRECTED(Function102775);
    // REDIRECTED(Function1009d2);
    // REDIRECTED(Function101724);
    // REDIRECTED(Function10218d);
    // REDIRECTED(Function1027a0);
    // REDIRECTED(Function101cbc);
    // REDIRECTED(Function102b9c);
    // REDIRECTED(Unknown_101ef5);
    // REDIRECTED(Function100e72);
    // REDIRECTED(Function10234b);
    // REDIRECTED(MobileBattleLessThanOneMinuteLeftText);
    // REDIRECTED(Function101467);
    // REDIRECTED(Function102c07);
    // REDIRECTED(Function1014b7);
    // REDIRECTED(Function1034f7);
    // REDIRECTED(Function1006d3);
    // REDIRECTED(MobileBattleNoTimeLeftForLinkingText);
    // REDIRECTED(Function1034be);
    // REDIRECTED(Function101db2);
    // REDIRECTED(Function1027eb);
    // REDIRECTED(Function100665);
    // REDIRECTED(Function1013d6);
    // REDIRECTED(MenuHeader_1029bb);
    // REDIRECTED(Function1013aa);
    // REDIRECTED(Function101c42);
    // REDIRECTED(MobileCopyTransferData);
    // REDIRECTED(asm_1027c6);
    // REDIRECTED(SetRAMStateForMobile);
    // REDIRECTED(Function102b32);
    // REDIRECTED(Jumptable_1022f5);
    // REDIRECTED(Function101e64);
    // REDIRECTED(Mobile_MoveSelectionScreen);
    // REDIRECTED(StartMobileInactivityTimer);
    // REDIRECTED(Function101b70);
    // REDIRECTED(Function10226a);
    // REDIRECTED(Function100754);
    // REDIRECTED(String_103571);
    // REDIRECTED(Function10079c);
    // REDIRECTED(Function101e8d);
    // REDIRECTED(Function1024f6);
    // REDIRECTED(Function101251);
    // REDIRECTED(Function1023b5);
    // REDIRECTED(MenuData3_102a33);
    // REDIRECTED(Function1002c9);
    // REDIRECTED(Function100493);
    // REDIRECTED(Function101400);
    // REDIRECTED(Function100c98);
    // REDIRECTED(String_102ef4);
    // REDIRECTED(Function10016f);
    // REDIRECTED(Function101649);
    // REDIRECTED(Function1026b7);
    // REDIRECTED(Function10054d);
    // REDIRECTED(Function101ab4);
    // REDIRECTED(Function100edf);
    // REDIRECTED(Function101bc8);
    // REDIRECTED(Function10294f);
    // REDIRECTED(Jumptable_102917);
    // REDIRECTED(Function100989);
    // REDIRECTED(String_103598);
    // REDIRECTED(Function10039c);
    // REDIRECTED(Function100dc0);
    // REDIRECTED(Function101aed);
    // REDIRECTED(Function103490);
    // REDIRECTED(Function1024af);
    // REDIRECTED(Function100efb);
    // REDIRECTED(Function1028c6);
    // REDIRECTED(String_102fb2);
    // REDIRECTED(Function100acf);
    // REDIRECTED(String_10354f);
    // REDIRECTED(Function1025c7);
    // REDIRECTED(Function101225);
    // REDIRECTED(Unknown_100feb);
    // REDIRECTED(PutCardInCardFolderText);
    // REDIRECTED(Function101d2a);
    // REDIRECTED(Jumptable_1005cb);
    // REDIRECTED(Function101cf6);
    // REDIRECTED(Function100000);
    // REDIRECTED(asm_1027e2);
    // REDIRECTED(Function10142c);
    // REDIRECTED(Function100320);
    // REDIRECTED(Function10202c);
    // REDIRECTED(Function1005c3);
    // REDIRECTED(Function1004a4);
    // REDIRECTED(Function1025e9);
    // REDIRECTED(Function100ec4);
    // REDIRECTED(Function100597);
    // REDIRECTED(Function10208e);
    // REDIRECTED(Function102180);
    // REDIRECTED(Function100e2d);
    // REDIRECTED(Function101719);
    // REDIRECTED(Function101d6b);
    // REDIRECTED(MenuData_10374f);
    // REDIRECTED(Function100513);
    // REDIRECTED(MenuHeader_103640);
    // REDIRECTED(Function1027b7);
    // REDIRECTED(StartMobileBattle);
    // REDIRECTED(Function102933);
    // REDIRECTED(Function100301);
    // REDIRECTED(Function1018ec);
    // REDIRECTED(Function102274);
    // REDIRECTED(WantAQuickMobileBattleText);
    // REDIRECTED(Function100e84);
    // REDIRECTED(Mobile_SelectThreeMons);
    // REDIRECTED(Jumptable_100581);
    // REDIRECTED(Function1022ca);
    // REDIRECTED(Function101b2b);
    // REDIRECTED(Function101a4f);
    // REDIRECTED(Function101600);
    // REDIRECTED(String_1035b1);
    // REDIRECTED(String_103545);
    // REDIRECTED(Function10152a);
    // REDIRECTED(Function100144);
    // REDIRECTED(Function10177b);
    // REDIRECTED(Function1018d6);
    // REDIRECTED(Function102921);
    // REDIRECTED(Function1016de);
    // REDIRECTED(Function102b12);
    // REDIRECTED(Function101ac6);
    // REDIRECTED(String_1035a8);
    // REDIRECTED(String_10302e);
    // REDIRECTED(Function10127d);
    // REDIRECTED(Function100902);
    // REDIRECTED(IncrementMobileInactivityTimerByCFrames);
    // REDIRECTED(Function102ff5);
    // REDIRECTED(Function1003c9);
    // REDIRECTED(Function100772);
    // REDIRECTED(Function102591);
    // REDIRECTED(Function10174c);
    // REDIRECTED(Function102984);
    // REDIRECTED(Function100534);
    // REDIRECTED(Function10283c);
    // REDIRECTED(Function10244b);
    // REDIRECTED(MobileBattleMustPickThreeMonText);
    // REDIRECTED(Unknown_10173a);
    // REDIRECTED(Function100da5);
    // REDIRECTED(Function102c71);
    // REDIRECTED(Function1002dc);
    // REDIRECTED(Function102048);
    // REDIRECTED(Function102496);
    // REDIRECTED(Function101be5);
    // REDIRECTED(Function101b59);
    // REDIRECTED(LoadSelectedPartiesForColosseum);
    // REDIRECTED(Function102e07);
    // REDIRECTED(String_103585);
    // REDIRECTED(Function102241);
    // REDIRECTED(Function1026c8);
    // REDIRECTED(Function1014a6);
    // REDIRECTED(CardWasListedText);
    // REDIRECTED(Function103094);
    // REDIRECTED(Function1025b0);
    // REDIRECTED(Function102c3b);
    // REDIRECTED(Unknown_103522);
    // REDIRECTED(Function100ef4);
    // REDIRECTED(Function102b4e);
    // REDIRECTED(Function101ead);
    // REDIRECTED(String_101faa);
    // REDIRECTED(Function10020b);
    // REDIRECTED(Function1000fa);
    // REDIRECTED(asm_101416);
    // REDIRECTED(Function1003ba);
    // REDIRECTED(Function102080);
    // REDIRECTED(Function10167d);
    // REDIRECTED(Function102d3e);
    // REDIRECTED(Function102ee7);
    // REDIRECTED(MenuData_102b73);
    // REDIRECTED(Function10046a);
    // REDIRECTED(Function1009f3);
    // REDIRECTED(Function100057);
    // REDIRECTED(Function101ecc);
    // REDIRECTED(Function102862);
    // REDIRECTED(String_101f93);
    // REDIRECTED(Function10043a);
    // REDIRECTED(Function100681);
    // REDIRECTED(Function103021);
    // REDIRECTED(Function1014e2);
    // REDIRECTED(Function101a97);
    // REDIRECTED(Function10378c);
    // REDIRECTED(Function101d1e);
    // REDIRECTED(NewCardArrivedText);
    // REDIRECTED(IncrementMobileInactivityTimerBy1Frame);
    // REDIRECTED(Function10162a);
    // REDIRECTED(Function100337);
    // REDIRECTED(Function100eae);
    // REDIRECTED(Function1034e0);
    // REDIRECTED(PleaseTryAgainTomorrowText);
    // REDIRECTED(Function101c11);
    // REDIRECTED(Function10295d);
    // REDIRECTED(Function101406);
    // REDIRECTED(Function101231);
    // REDIRECTED(Function1030cd);
    // REDIRECTED(Function101418);
    // REDIRECTED(Function102e4f);
    // REDIRECTED(Function10343c);
    // REDIRECTED(DisableMobile);
    // REDIRECTED(Function1005e1);
    // REDIRECTED(Jumptable_101d4d);
    // REDIRECTED(String1006ca);
    // REDIRECTED(Function100ae7);
    // REDIRECTED(Jumptable_1026da);
    // REDIRECTED(MenuHeader_103747);
    // REDIRECTED(Function1024c0);
    // REDIRECTED(Function101e39);
    // REDIRECTED(Function10159d);
    // REDIRECTED(Function101ca0);
    // REDIRECTED(Function101557);
    // REDIRECTED(Function100f8d);
    // REDIRECTED(Function1015be);
    // REDIRECTED(Function100ec5);
    // REDIRECTED(String10025e);
    // REDIRECTED(Function1013e1);
    // REDIRECTED(MenuData_1005ba);
    // REDIRECTED(AdvanceMobileInactivityTimerAndCheckExpired);
    // REDIRECTED(Function102233);
    // REDIRECTED(Function10387b);
    // REDIRECTED(Function10224b);
    // REDIRECTED(Function10034d);
    // REDIRECTED(Jumptable_102766);
    // REDIRECTED(String_101fd2);
    // REDIRECTED(Function101d5d);
    // REDIRECTED(Function101d51);
    // REDIRECTED(Function103700);
    // REDIRECTED(Function1006dc);
    // REDIRECTED(Function1037c2);
    // REDIRECTED(Function102f6d);
    // REDIRECTED(Function10161f);
    // REDIRECTED(Function1028bf);
    // REDIRECTED(Function10127e);
    // REDIRECTED(Function10158a);
    // REDIRECTED(Function100eb4);
    // REDIRECTED(Function100b7a);
    // REDIRECTED(Function103487);
    // REDIRECTED(MenuHeader_1005b2);
    // REDIRECTED(Function1023a1);
    // REDIRECTED(Function1020bf);
    // REDIRECTED(Function1009ae);
    // REDIRECTED(Unknown_101d8d);
    // REDIRECTED(Function10047c);
    // REDIRECTED(Function1024cb);
    // REDIRECTED(Jumptable_101297);
    // REDIRECTED(MobileBattleRemainingTimeText);
    // REDIRECTED(MobileBattleMonMenu);
    // REDIRECTED(Function100e63);
    // REDIRECTED(Function102dd3);
    // REDIRECTED(LinkTerminatedText);
    // REDIRECTED(Function102c48);
    // REDIRECTED(Function100232);
    // REDIRECTED(Function101050);
    // REDIRECTED(Function1016f8);
    // REDIRECTED(Function10204c);
    // REDIRECTED(asm_100eb8);
    // REDIRECTED(Function1015df);
    // REDIRECTED(Jumptable_100e8c);
    // REDIRECTED(MenuData_100604);
    // REDIRECTED(Function101de3);
    // REDIRECTED(Function10138b);
    // REDIRECTED(Function1004de);
    // REDIRECTED(Function1028e8);
    // REDIRECTED(Function102e3e);
    // REDIRECTED(Function10032e);
    // REDIRECTED(Function10306e);
    // REDIRECTED(Function101c2b);
    // REDIRECTED(String_1035ba);
    // REDIRECTED(Function102652);
    // REDIRECTED(Function100382);
    // REDIRECTED(Function1000ba);
    // REDIRECTED(Function10278c);
    // REDIRECTED(Function1029fe);
    // REDIRECTED(Jumptable_101247);
    // REDIRECTED(Function10299e);
    // REDIRECTED(Function10126c);
    // REDIRECTED(Unknown_103608);
    // REDIRECTED(Function10194b);
    // REDIRECTED(StartingLinkText);
    // REDIRECTED(Function101220);
    // REDIRECTED(Unknown_100fc0);
    // REDIRECTED(String_101fef);
    // REDIRECTED(Function100f3d);
    // REDIRECTED(String_10200c);
    // REDIRECTED(Function1024de);
    // REDIRECTED(Function1036f9);
    // REDIRECTED(Function10127c);
    // REDIRECTED(Function1017f1);
    // REDIRECTED(Function100826);
    // REDIRECTED(Mobile_LoadBattleMenu);
    // REDIRECTED(String_101f69);
    // REDIRECTED(Function1028d3);
    // REDIRECTED(Unknown_1035d7);
    // REDIRECTED(Function10038a);
    // REDIRECTED(Jumptable_10052a);
    // REDIRECTED(Function10151d);
    // REDIRECTED(Function1004ce);
    // REDIRECTED(String_103546);
    // REDIRECTED(Function1016cf);
    // REDIRECTED(Function101674);
    CONVERTED(v_LinkBattleSendReceiveAction);
    // REDIRECTED(String_103002);
    // REDIRECTED(Function10304f);
    // REDIRECTED(Function101e98);
    // REDIRECTED(Function10173b);
    // REDIRECTED(Function1020ea);
    // REDIRECTED(Unknown_10327a);
    // REDIRECTED(String1006c6);
    // REDIRECTED(Function1017f5);
    // REDIRECTED(Unknown_101895);
    // REDIRECTED(Function103302);
    // REDIRECTED(Function102996);
    // REDIRECTED(Function101e82);
    // REDIRECTED(Function102361);
    // REDIRECTED(String_102a26);
    // REDIRECTED(Function102d48);
    // REDIRECTED(Function101e09);
    // REDIRECTED(Function102f85);
    // REDIRECTED(String_1035a0);
    // REDIRECTED(Function101c62);
    // REDIRECTED(Function100022);
    // REDIRECTED(Function1021e0);
    // REDIRECTED(String_101fc5);
    // REDIRECTED(String_102fdb);
    // REDIRECTED(Unknown_1035f3);
    // REDIRECTED(Function100579);
    // REDIRECTED(Function102dc3);
    // REDIRECTED(Function1028da);
    // REDIRECTED(Function10236e);
    // REDIRECTED(Function10339a);
    // REDIRECTED(MenuHeader_1005fc);
    // REDIRECTED(String_1035bd);
    // REDIRECTED(Function100163);
    // REDIRECTED(Function1009a5);
    // REDIRECTED(Function1005cf);
    // REDIRECTED(String10024d);
    // REDIRECTED(Unknown_103112);
    // REDIRECTED(Jumptable_1029cb);
    // REDIRECTED(MobileTradeLightsPalettes);
    // REDIRECTED(Jumptable_1016c3);
    // REDIRECTED(Function1003ab);
    // REDIRECTED(Function100522);
    // REDIRECTED(Function100ee6);
    // REDIRECTED(Function102068);
    // REDIRECTED(Function101cc8);
    // REDIRECTED(Function100eed);
    // REDIRECTED(Function1002ed);
    // REDIRECTED(TradingMonForOTMonText);
    // REDIRECTED(String_101f13);
    // REDIRECTED(String_101f81);
    // REDIRECTED(PickThreeMonForMobileBattleText);
    // REDIRECTED(Function1014f4);
    // REDIRECTED(Function10165a);
    // REDIRECTED(Function101826);
    // REDIRECTED(Function101b0f);
    // REDIRECTED(Function1034a7);
    // REDIRECTED(Function101265);
    // REDIRECTED(Function101438);
    // REDIRECTED(Function1025bd);
    // REDIRECTED(Function1024a8);
    // REDIRECTED(Function10168e);
    // REDIRECTED(Function1000e8);
    // REDIRECTED(TryAgainUsingSameSettingsText);
    // REDIRECTED(Function1021f9);
    // REDIRECTED(Function101e31);
    // REDIRECTED(MobileBattleResetTimer);
    // REDIRECTED(v_StartMobileBattle);
    // REDIRECTED(Function102db7);
    // REDIRECTED(Function1017e4);
    // REDIRECTED(Function1028ab);
    // REDIRECTED(Function102dec);
    // REDIRECTED(Function1017b0);
    // REDIRECTED(Function1014ce);
    // REDIRECTED(Function101544);
    // REDIRECTED(Function1020a8);
    // REDIRECTED(EnableMobile);
    // REDIRECTED(Mobile_PartyMenuSelect);
    // REDIRECTED(Function1029c3);
    // REDIRECTED(Function101ee4);
    // REDIRECTED(Function100ed4);
    // REDIRECTED(Function102423);
    // REDIRECTED(String_1035c1);
    // REDIRECTED(Function10123d);
    // REDIRECTED(String_10088e);
    // REDIRECTED(Function1025dc);
    // REDIRECTED(Function102c87);
    // REDIRECTED(Function103309);
    // REDIRECTED(Function1013c0);
    // REDIRECTED(Function10250c);
    // REDIRECTED(Function101571);
    // REDIRECTED(Function102a3b);
    // REDIRECTED(Function102f15);
    // REDIRECTED(Function102770);
    // REDIRECTED(Function102814);
    // REDIRECTED(Function101475);
    // REDIRECTED(Function1028fc);
    // REDIRECTED(String_102fcc);
    // REDIRECTED(Function101d7b);
    // REDIRECTED(Function102416);
    // REDIRECTED(Function10168a);
    // REDIRECTED(String_102014);
    // REDIRECTED(Function102f32);
    // REDIRECTED(String_10089f);
    // REDIRECTED(Function102b7b);
    // REDIRECTED(Function10209c);
    // REDIRECTED(Jumptable_10292f);
    // REDIRECTED(Unknown_100b0a);
    // REDIRECTED(Function102283);
    // REDIRECTED(Mobile_CommunicationStandby);
    // REDIRECTED(Function1003d8);
    // REDIRECTED(Function100846);
    // REDIRECTED(Function100545);
    // REDIRECTED(Function1004f4);
    // REDIRECTED(Function10266b);
    // REDIRECTED(Function100d67);
    // REDIRECTED(CopyOtherPlayersBattleMonSelection);
    // REDIRECTED(Function1025ff);
    // REDIRECTED(Function102bac);
    // REDIRECTED(Function101537);
    // REDIRECTED(Function10286f);
    // REDIRECTED(Function100327);
    // REDIRECTED(Function100495);
    // REDIRECTED(Function102fce);
    // REDIRECTED(Unknown_100ff3);
    // REDIRECTED(Function100db0);
    // REDIRECTED(Function100dd8);
    // REDIRECTED(Function101dd0);
    // REDIRECTED(Function100504);
    // REDIRECTED(Function1017c7);
    // REDIRECTED(MobileCheckRemainingBattleTime);
    // REDIRECTED(Function102112);
    // REDIRECTED(Function102cee);
    // REDIRECTED(Function100eca);
    // REDIRECTED(Function101ee2);
    // REDIRECTED(Function102387);
    // REDIRECTED(Function103362);
    // REDIRECTED(String_101fe1);
    // REDIRECTED(Function103780);
    // REDIRECTED(Function1022d0);
    // REDIRECTED(Function101b8f);
    // REDIRECTED(asm_100497);
    // REDIRECTED(String_103557);
    // REDIRECTED(Function1004ba);
    // REDIRECTED(Function1026de);
    // REDIRECTED(Function101cc2);
    // REDIRECTED(Function103654);
    // REDIRECTED(String_101f14);
    // REDIRECTED(Function102bdc);
    // REDIRECTED(Function101d10);
    // REDIRECTED(Unknown_10186f);
    // REDIRECTED(Function10149a);
    // REDIRECTED(MenuData_103648);
    // REDIRECTED(Unknown_10102c);
    // REDIRECTED(Function10246a);
    // REDIRECTED(MobileBattleMoreInfoText);
    // REDIRECTED(Function102754);
    // REDIRECTED(Function1029af);
    // REDIRECTED(Function100393);
    // REDIRECTED(String_102000);
    // REDIRECTED(Function1013f5);
    // REDIRECTED(Function101cdf);
    // REDIRECTED(Function10248d);
    // REDIRECTED(asm_1027d1);
    // REDIRECTED(Function100f02);
    // REDIRECTED(Function100ea2);
    // REDIRECTED(Function1021b8);
    // REDIRECTED(Function101507);
    // REDIRECTED(Function100585);
    // REDIRECTED(Function102480);
    // REDIRECTED(Function101913);
    // REDIRECTED(MobileCopyTransferData2);
    // REDIRECTED(Function101d95);
    // REDIRECTED(Function102142);
    // REDIRECTED(Function101c50);
    // REDIRECTED(MenuData_102b94);
    // REDIRECTED(Function1003f5);
    // REDIRECTED(Function102c14);
    // REDIRECTED(AskMobileOrCable);
    // REDIRECTED(WouldYouLikeToMobileBattleText);
    // REDIRECTED(MobileComms_CheckInactivityTimer);
    // REDIRECTED(Function100406);
    // REDIRECTED(String_101f4f);
    // REDIRECTED(Function10305d);
    // REDIRECTED(Function102d9a);
    // REDIRECTED(MobileBattleFixTimer);
    // REDIRECTED(Function1018fb);
    // REDIRECTED(Function1026f3);
    // REDIRECTED(Function100276);
    // REDIRECTED(Unknown_101882);
    // REDIRECTED(Function1018e1);
    // REDIRECTED(Function1023c6);
    // REDIRECTED(Function1033af);
    // REDIRECTED(MobileBattleGetRemainingTime);
    // REDIRECTED(Jumptable_10044e);
    // REDIRECTED(Function102298);
    // REDIRECTED(Function1013dd);
    // REDIRECTED(Function101c92);
    // REDIRECTED(Function10156d);

    // engine/battle/anim_hp_bar.c
    // CONVERTED(ShortHPBar_CalcPixelFrame);
    // CONVERTED(HPBarAnim_PaletteUpdate);
    // CONVERTED(ShortAnim_UpdateVariables);
    // CONVERTED(HPBarAnim_RedrawHPBar);
    // CONVERTED(v_AnimateHPBar);
    // CONVERTED(HPBarAnim_BGMapUpdate);
    // CONVERTED(LongAnim_UpdateVariables);
    // CONVERTED(HPBarAnim_UpdateHPRemaining);
    // CONVERTED(LongHPBarAnim_UpdateTiles);
    // CONVERTED(ShortHPBarAnim_UpdateTiles);

    // engine/events/celebi.c
    // CONVERTED(CelebiEvent_SetBattleType);
    // CONVERTED(UpdateCelebiPosition);
    // CONVERTED(SpecialCelebiGFX);
    CONVERTED(CelebiShrineEvent);
    // REDIRECTED(CelebiEvent_SpawnLeaf);
    // CONVERTED(CheckCaughtCelebi);
    // CONVERTED(CelebiEvent_CountDown);
    // CONVERTED(GetCelebiSpriteTile);
    // CONVERTED(SpecialCelebiLeafGFX);
    // CONVERTED(LoadCelebiGFX);
    // CONVERTED(UnusedForestTreeFrames);
    // CONVERTED(CelebiEvent_Cosine);

    // engine/games/card_flip.c
    CONVERTED(v_CardFlip);
    // CONVERTED(CardFlip_ShuffleDeck);
    // CONVERTED(PlaceOAMCardBorder);
    // CONVERTED(CollapseCursorPosition);
    // CONVERTED(CardFlip_CheckWinCondition);
    // CONVERTED(CardFlip_PrintCoinBalance);
    // CONVERTED(CardFlip_InitTilemap);
    // CONVERTED(CardFlip_FillGreenBox);
    // CONVERTED(GetCoordsOfChosenCard);
    // CONVERTED(MemoryGameGFX);
    // CONVERTED(UnusedCursor_InterpretJoypad_AnimateCursor);
    // CONVERTED(CardFlip_CopyToBox);
    // CONVERTED(CardFlip_InitAttrPals);
    // CONVERTED(CardFlip_BlankDiscardedCardSlot);
    // CONVERTED(CardFlipOffButtonGFX);
    // CONVERTED(CardFlipLZ03);
    // CONVERTED(ChooseCard_HandleJoypad);
    // CONVERTED(CardFlipLZ02);
    // CONVERTED(PlaceCardFaceDown);
    // CONVERTED(CardFlipLZ01);
    // CONVERTED(CardFlip_DisplayCardFaceUp);
    // CONVERTED(CardFlip_UpdateCoinBalanceDisplay);
    // CONVERTED(CardFlip_UpdateCursorOAM);
    // CONVERTED(CardFlipTilemap);
    // CONVERTED(CardFlipOnButtonGFX);
    // CONVERTED(CardFlip_FillBox);
    // CONVERTED(CardFlip_ShiftDigitsUpOnePixel);
    // CONVERTED(CardFlip_CopyOAM);

    // engine/rtc/reset_password.c
    CONVERTED(ClockResetPassword);
    REDIRECTED(v_ResetClock);

    // engine/events/print_unown.c
    CONVERTED(v_UnownPrinter);
    // CONVERTED(UnownDexATile);
    // CONVERTED(UnownDexVacantString);
    // CONVERTED(UnownDexDoWhatString);
    // CONVERTED(AlphRuinsStampString);
    // CONVERTED(UnownDexBTile);
    // CONVERTED(UnownDexMenuString);
    CONVERTED(PlaceUnownPrinterFrontpic);

    // engine/events/print_unown_2.c
    // CONVERTED(RotateUnownFrontpic);
    // CONVERTED(UnownPrinter_GBPrinterRectangle);

    // engine/items/switch_items.c
    // REDIRECTED(ItemSwitch_CopyBufferToItem);
    // REDIRECTED(ItemSwitch_GetItemFormatSize);
    // REDIRECTED(ItemSwitch_CopyItemToBuffer);
    // REDIRECTED(ItemSwitch_GetItemQuantity);
    // REDIRECTED(ItemSwitch_GetItemOffset);
    // REDIRECTED(ItemSwitch_GetNthItem);
    // REDIRECTED(ItemSwitch_BackwardsCopyBytes);
    CONVERTED(SwitchItemsInBag);

    // mobile/mobile_menu.c
    CONVERTED(Function4a118);
    // CONVERTED(Function4a28a);
    // CONVERTED(String_4a34b);
    CONVERTED(Function4a4c4);
    // CONVERTED(String_4a5e6);
    // CONVERTED(Function4a6d8);
    REDIRECTED(Function4a149);
    REDIRECTED(Function4a3aa);
    REDIRECTED(Function4a13b);
    REDIRECTED(Function4a485);
    REDIRECTED(MenuHeader_0x4a346);
    // REDIRECTED(String_4a1ef);
    // REDIRECTED(String_0x49fe9);
    // CONVERTED(String_4a5f2);
    REDIRECTED(Function4a098);
    REDIRECTED(Function4a0c2);
    REDIRECTED(Function4a221);
    REDIRECTED(Function4a449);
    REDIRECTED(Function4a680);
    // REDIRECTED(Function4a195);
    // CONVERTED(MainMenu_Mobile);
    REDIRECTED(Function49f0a);
    // REDIRECTED(Function4a5b0);
    // CONVERTED(Strings_4a5f6);
    REDIRECTED(Function4a6ab);
    // CONVERTED(Function4a6c5);
    REDIRECTED(Function4a373);
    REDIRECTED(Function4a239);
    // CONVERTED(DeletedTheLoginPasswordText);
    // CONVERTED(DeleteSavedLoginPasswordText);
    // CONVERTED(String_4a5cd);
    REDIRECTED(Function49f16);
    REDIRECTED(Function4a20e);
    // REDIRECTED(MenuData_0x4a36a);
    // REDIRECTED(asm_4a54d);
    REDIRECTED(Function4a39a);
    REDIRECTED(Function4a100);
    REDIRECTED(Function4a3a7);
    REDIRECTED(asm_4a111);
    // CONVERTED(MainMenu_MobileStudium);
    // REDIRECTED(asm_4a19d);
    // CONVERTED(MobileString1);
    // CONVERTED(MobileStrings2);
    // REDIRECTED(Function4a545);
    // CONVERTED(String_4a5da);
    // CONVERTED(String_4a5c5);
    REDIRECTED(Function4a492);
    REDIRECTED(MobileMenu_InitMenuBuffers);
    // CONVERTED(Strings_4a23d);
    REDIRECTED(Function4a0b9);
    // REDIRECTED(DeletePassword_YesNo_MenuHeader);

    // mobile/mobile_12.c
    REDIRECTED(Function488d3);
    // CONVERTED(asm_48922);
    REDIRECTED(Function4873c);
    // CONVERTED(Function48a3a);
    // CONVERTED(Function48cdc);
    // CONVERTED(Function48d2a);
    REDIRECTED(Function4895a);
    // CONVERTED(Miyagi);
    REDIRECTED(asm_4815f);
    // CONVERTED(Function487ff);
    REDIRECTED(Function48157);
    // CONVERTED(MobileString_Gender);
    // CONVERTED(MenuHeader_0x484f1);
    // CONVERTED(Strings_484fb);
    // CONVERTED(Function48d4a);
    REDIRECTED(Function4840c);
    // CONVERTED(MobileString_OK);
    // CONVERTED(asm_48bc7);
    // CONVERTED(Function48c0f);
    // CONVERTED(Function489ea);
    REDIRECTED(Function48272);
    // CONVERTED(MobileDownArrowGFX);
    // CONVERTED(Function48725);
    REDIRECTED(Function48c8e);
    REDIRECTED(Function486bf);
    // CONVERTED(String_48a38);
    // CONVERTED(Function4880e);
    // CONVERTED(InitMobileProfile);
    // CONVERTED(Mobile12_Bin2Dec);
    // CONVERTED(Function48ab5);
    REDIRECTED(Function483bb);
    // CONVERTED(String_48aa1);
    // CONVERTED(MobileDesc_Address);
    // CONVERTED(Function48cda);
    // CONVERTED(MobileDesc_Gender);
    // CONVERTED(Function48c5a);
    // CONVERTED(Function4896e);
    // CONVERTED(Function48c0d);
    // CONVERTED(asm_48972);
    // CONVERTED(Prefectures);
    // CONVERTED(MobileString_Age);
    // CONVERTED(MenuData_0x484f9);
    // CONVERTED(Function48bd7);
    REDIRECTED(Function48689);
    // CONVERTED(Function4820d);
    REDIRECTED(Function4876f);
    // CONVERTED(MobileString_PersonalInfo);
    // CONVERTED(MobileString_ProfileChanged);
    // CONVERTED(MenuHeader_0x48504);
    REDIRECTED(asm_4828d);
    // CONVERTED(Function48c63);
    REDIRECTED(Function48304);
    REDIRECTED(Function48d30);
    // CONVERTED(MenuHeader_0x48a9c);
    REDIRECTED(Function48187);
    REDIRECTED(Function48d3d);
    // CONVERTED(Function48c00);
    // CONVERTED(Function48c11);
    // CONVERTED(MobileDesc_Age);
    // CONVERTED(Function48d94);
    // CONVERTED(MenuHeader_0x48513);
    // CONVERTED(MobileString_ZipCode);
    // CONVERTED(MobileProfileString);
    REDIRECTED(Function48283);
    // CONVERTED(Function487ec);
    // CONVERTED(MobileUpArrowGFX);
    // CONVERTED(String_484ff);
    // CONVERTED(String_4880d);
    // CONVERTED(Function48383);
    // CONVERTED(Function488b9);
    // CONVERTED(String_484fb);
    // CONVERTED(Function48c4d);
    // CONVERTED(MenuHeader_0x48509);
    // CONVERTED(MenuData_0x4851b);
    // CONVERTED(Function48a9a);
    // CONVERTED(Function48cfd);
    // CONVERTED(Function488b4);
    // CONVERTED(MenuHeader_0x4850e);
    REDIRECTED(Function48ca3);
    // CONVERTED(MobileDesc_ZipCode);
    // CONVERTED(MobileString_Address);
    // CONVERTED(Function483e8);

    // mobile/mobile_45_2.c
    // REDIRECTED(Function116655);
    // REDIRECTED(Unknown_116b13);
    // REDIRECTED(Function11668d);
    // REDIRECTED(PichuBorderMobileBGPalettes);
    // REDIRECTED(PichuBorderMobileOBPalettes);
    // REDIRECTED(Unknown_116dbe);
    // REDIRECTED(Unknown_1169a1);
    // REDIRECTED(Unknown_117177);
    // REDIRECTED(Unknown_116ad6);
    // REDIRECTED(Function116758);
    // REDIRECTED(Unknown_116960);
    // REDIRECTED(Unknown_116a1b);
    // REDIRECTED(Unknown_116d4c);
    // REDIRECTED(Function116780);
    // REDIRECTED(Function1167a6);
    // REDIRECTED(Function1165d8);
    // REDIRECTED(Unknown_11727a);
    // REDIRECTED(Function116623);
    // REDIRECTED(PichuBorderMobileTilemapAttrmap);
    // REDIRECTED(Unknown_117230);
    // REDIRECTED(Unknown_116923);
    // REDIRECTED(Unknown_116fb7);
    // REDIRECTED(Unknown_116f0c);
    // REDIRECTED(Unknown_116bd6);
    // REDIRECTED(Unknown_1170fd);
    // REDIRECTED(Unknown_116e9a);
    // REDIRECTED(asm_1167af);
    // REDIRECTED(Unknown_116c58);
    // REDIRECTED(Unknown_117255);
    // REDIRECTED(Unknown_116b54);
    // REDIRECTED(Unknown_11729f);
    // REDIRECTED(Function116600);
    // REDIRECTED(Unknown_116f7e);
    // REDIRECTED(Function1166c4);
    // REDIRECTED(Function11679c);
    // REDIRECTED(Unknown_116867);
    // REDIRECTED(Unknown_117056);
    // REDIRECTED(Unknown_11683e);
    // REDIRECTED(Unknown_1171e6);
    // REDIRECTED(Unknown_11713a);
    // REDIRECTED(Unknown_1167eb);
    // REDIRECTED(Unknown_11720b);
    // REDIRECTED(Unknown_1168c5);
    // REDIRECTED(Function11659d);
    // REDIRECTED(Jumptable_1165af);
    // REDIRECTED(Unknown_116e69);
    // REDIRECTED(Unknown_116881);
    // REDIRECTED(Unknown_11719c);
    // REDIRECTED(Unknown_116ed3);
    // REDIRECTED(Unknown_1171c1);
    // REDIRECTED(Function116618);
    // REDIRECTED(Unknown_1168ae);
    // REDIRECTED(Function1165f5);
    // REDIRECTED(Function1165e3);
    // REDIRECTED(Unknown_116c17);
    // REDIRECTED(Function11678e);
    // REDIRECTED(Function1165d5);
    // REDIRECTED(Unknown_1167fb);
    // REDIRECTED(Unknown_116d85);
    // REDIRECTED(Unknown_117025);
    // REDIRECTED(Function1166a2);
    // REDIRECTED(Unknown_116a99);
    // REDIRECTED(Unknown_116c99);
    // REDIRECTED(Unknown_116f45);
    // REDIRECTED(Unknown_116df7);
    // REDIRECTED(Function116567);
    // REDIRECTED(Unknown_1172c4);
    // REDIRECTED(Function1166f4);
    // REDIRECTED(Function116635);
    // REDIRECTED(Unknown_1169de);
    // REDIRECTED(Unknown_116808);
    // REDIRECTED(Unknown_116a58);
    // REDIRECTED(Function116747);
    // REDIRECTED(Unknown_116cda);
    // REDIRECTED(Unknown_116815);
    // REDIRECTED(Function11669f);
    // REDIRECTED(Unknown_116fec);
    // REDIRECTED(Function116615);
    // REDIRECTED(Unknown_117083);
    // REDIRECTED(Function11665c);
    // REDIRECTED(Unknown_116e30);
    // REDIRECTED(Function116797);
    // REDIRECTED(Function1166d6);
    // REDIRECTED(Unknown_116b95);
    // REDIRECTED(Function116640);
    // REDIRECTED(Unknown_1170c0);
    // REDIRECTED(Unknown_116d1b);
    // REDIRECTED(Unknown_1172e9);
    // REDIRECTED(Unknown_116870);
    // REDIRECTED(Function11671f);
    // REDIRECTED(Function11677e);

    // lib/mobile/main.c
    // REDIRECTED(Function113281);
    // REDIRECTED(asm_111a47);
    // REDIRECTED(MobileAPI_SetTimer);
    // REDIRECTED(Function113089);
    // REDIRECTED(MobilePacket_Idle);
    // REDIRECTED(Function113c8e);
    // REDIRECTED(Function111b3b);
    // REDIRECTED(Function113909);
    // REDIRECTED(Function11164f);
    // REDIRECTED(Function113180);
    // REDIRECTED(Function113268);
    // REDIRECTED(Function1135ba);
    // REDIRECTED(Function1104c6);
    // REDIRECTED(Function1121f6);
    // REDIRECTED(Function1115e4);
    // REDIRECTED(Function111540);
    // REDIRECTED(Function113ec7);
    // REDIRECTED(Function111c17);
    // REDIRECTED(Function11261c);
    // REDIRECTED(Unknown_112102);
    // REDIRECTED(Function112bbb);
    // REDIRECTED(Function110c9e);
    // REDIRECTED(MobilePacket_HangUpTelephone);
    // REDIRECTED(Unknown_113b70);
    // REDIRECTED(Unknown_1120a4);
    // REDIRECTED(Function111892);
    // REDIRECTED(Function1106ef);
    // REDIRECTED(Function113e42);
    // REDIRECTED(Function113a40);
    // REDIRECTED(Function1104b0);
    // REDIRECTED(Function112d20);
    // REDIRECTED(Function11236b);
    // REDIRECTED(ParseResponse_BeginSession);
    // REDIRECTED(Function1116a9);
    // REDIRECTED(Function112251);
    // REDIRECTED(Function110757);
    // REDIRECTED(Function1127e7);
    // REDIRECTED(Function1131a9);
    // REDIRECTED(Function11269b);
    // REDIRECTED(Function111541);
    // REDIRECTED(HTTPDownloadURL);
    // REDIRECTED(Function112807);
    // REDIRECTED(Function110af4);
    // REDIRECTED(Function112840);
    // REDIRECTED(Function110ddd);
    // REDIRECTED(Unknown_112089);
    // REDIRECTED(Function111664);
    // REDIRECTED(Function110899);
    // REDIRECTED(Function1100b4);
    // REDIRECTED(Function110236);
    // REDIRECTED(asm_111a40);
    // REDIRECTED(Function1128d3);
    // REDIRECTED(Function11306b);
    // REDIRECTED(Function1116a4);
    // REDIRECTED(Function112724);
    // REDIRECTED(Function1133fe);
    // REDIRECTED(Unknown_1132dd);
    // REDIRECTED(Function1108a3);
    // REDIRECTED(Function112373);
    // REDIRECTED(Function1127e1);
    // REDIRECTED(Function110228);
    // REDIRECTED(Function11299c);
    // REDIRECTED(MobilePacket_DialTelephone);
    // REDIRECTED(Function112bec);
    // REDIRECTED(Function113672);
    // REDIRECTED(Unknown_1132a6);
    // REDIRECTED(Function1126ac);
    // REDIRECTED(Function11177c);
    // REDIRECTED(Function111a42);
    // REDIRECTED(MobilePacket_BeginSession);
    // REDIRECTED(Function11264e);
    // REDIRECTED(Function113008);
    // REDIRECTED(Function111e28);
    // REDIRECTED(Unknown_1120c1);
    // REDIRECTED(asm_1117a2);
    // REDIRECTED(Function112654);
    // REDIRECTED(Function1109f9);
    // REDIRECTED(Function11295e);
    // REDIRECTED(Function113054);
    // REDIRECTED(Function11329d);
    // REDIRECTED(Unknown_11330c);
    // REDIRECTED(Function1107ff);
    // REDIRECTED(Function11214e);
    // REDIRECTED(Function11359d);
    // REDIRECTED(Unknown_113b7e);
    // REDIRECTED(Function113d47);
    // REDIRECTED(Unknown_11209e);
    // REDIRECTED(Function1111ca);
    // REDIRECTED(Function1135eb);
    // REDIRECTED(Function111a0b);
    // REDIRECTED(Function110485);
    // REDIRECTED(MD5_K_Table);
    // REDIRECTED(Function110615);
    // REDIRECTED(Function110432);
    // REDIRECTED(Function110578);
    // REDIRECTED(Unknown_1120d4);
    // REDIRECTED(Function112fd5);
    // REDIRECTED(Function113072);
    // REDIRECTED(Function110291);
    // REDIRECTED(Function11225d);
    // REDIRECTED(Function1135ad);
    // REDIRECTED(Function1113ea);
    // REDIRECTED(Function11032c);
    // REDIRECTED(Function1113f7);
    // REDIRECTED(Function113095);
    // REDIRECTED(Unknown_1120ce);
    // REDIRECTED(Function113623);
    // REDIRECTED(Function112b60);
    // REDIRECTED(MobilePacket_ISPLogin);
    // REDIRECTED(Function1117e7);
    // REDIRECTED(Function111f63);
    // REDIRECTED(MobilePacket_WaitForTelephoneCall);
    // REDIRECTED(Function1134cb);
    // REDIRECTED(Function112aac);
    // REDIRECTED(Function111f97);
    // REDIRECTED(Unknown_112110);
    // REDIRECTED(Function112269);
    // REDIRECTED(HTTPRankingURL);
    // REDIRECTED(Function111796);
    // REDIRECTED(Function111ab9);
    // REDIRECTED(MobilePacket_EndSession);
    // REDIRECTED(Function11039a);
    // REDIRECTED(Function1105dd);
    // REDIRECTED(MobilePacket_ReadConfigurationDataPart2);
    // REDIRECTED(Function11234b);
    // REDIRECTED(Function113a28);
    // REDIRECTED(Function1126e6);
    // REDIRECTED(HTTPUtilityURL);
    // REDIRECTED(Unknown_1120c8);
    // REDIRECTED(Function1123e1);
    // REDIRECTED(Function110231);
    // REDIRECTED(Unknown_1120b0);
    // REDIRECTED(Jumptable_1121ac);
    // REDIRECTED(Function1108ab);
    // REDIRECTED(Unknown_1132bf);
    // REDIRECTED(Function11392f);
    // REDIRECTED(Function11162d);
    // REDIRECTED(Function111e15);
    // REDIRECTED(v_MobileAPI);
    // REDIRECTED(Function1127c5);
    // REDIRECTED(Function112969);
    // REDIRECTED(Function11235a);
    // REDIRECTED(Function113a32);
    // REDIRECTED(Unknown_112137);
    // REDIRECTED(Function11273a);
    // REDIRECTED(asm_11179a);
    // REDIRECTED(Function113167);
    // REDIRECTED(Function1139b7);
    // REDIRECTED(Function111d07);
    // REDIRECTED(Function111686);
    // REDIRECTED(Function110d37);
    // REDIRECTED(Function1126b0);
    // REDIRECTED(Function110c3c);
    // REDIRECTED(HTTPUploadURL);
    // REDIRECTED(Unknown_1132b2);
    // REDIRECTED(Function110226);
    // REDIRECTED(Function1113fe);
    // REDIRECTED(v_MobileReceive);
    // REDIRECTED(MobilePacket_TransferData);
    // REDIRECTED(Unknown_112132);
    // REDIRECTED(Unknown_113372);
    // REDIRECTED(Function1116a0);
    // REDIRECTED(Function112a56);
    // REDIRECTED(Function113026);
    // REDIRECTED(Unknown_1132ff);
    // REDIRECTED(MobileSDK_CopyBytes);
    // REDIRECTED(Function113973);
    // REDIRECTED(Function113386);
    // REDIRECTED(Function11148c);
    // REDIRECTED(Function111044);
    // REDIRECTED(Function111610);
    // REDIRECTED(PacketSendEmptyBody);
    // REDIRECTED(Function1103ac);
    // REDIRECTED(MobileSDK_CopyString);
    // REDIRECTED(v_Timer);
    // REDIRECTED(Function111884);
    // REDIRECTED(Function110438);
    // REDIRECTED(Function110a5b);
    // REDIRECTED(Function111a2a);
    // REDIRECTED(Function111d23);
    // REDIRECTED(Unknown_112121);
    // REDIRECTED(Unknown_113a55);
    // REDIRECTED(MobilePacket_OpenTCPConnection);
    // REDIRECTED(Function112715);
    // REDIRECTED(Function113a1f);
    // REDIRECTED(Function111b21);
    // REDIRECTED(Function113197);
    // REDIRECTED(MobilePacket_DNSQuery);
    // REDIRECTED(Function1125c7);
    // REDIRECTED(Function111cc2);
    // REDIRECTED(Function113d66);
    // REDIRECTED(Function113a0b);
    // REDIRECTED(Function112430);
    // REDIRECTED(Function1133de);
    // REDIRECTED(Function110596);
    // REDIRECTED(Function112d33);
    // REDIRECTED(Function112b71);
    // REDIRECTED(Function112597);
    // REDIRECTED(Function111596);
    // REDIRECTED(Function111f8d);
    // REDIRECTED(Function1126b6);
    // REDIRECTED(Function1127cd);
    // REDIRECTED(ResetReceivePacketBuffer);
    // REDIRECTED(Function1111d7);
    // REDIRECTED(Function112f61);
    // REDIRECTED(Function1113f8);
    // REDIRECTED(Function1118bc);
    // REDIRECTED(Function113a15);
    // REDIRECTED(MobilePacket_ISPLogout);
    // REDIRECTED(Unknown_1120ba);
    // REDIRECTED(Function112729);
    // REDIRECTED(Function112451);
    // REDIRECTED(Function1109a4);
    // REDIRECTED(GetErrorCode);
    // REDIRECTED(Function110115);
    // REDIRECTED(Function110905);
    // REDIRECTED(Unknown_1120e8);
    // REDIRECTED(Function111c06);
    // REDIRECTED(Function113273);
    // REDIRECTED(Function111335);
    // REDIRECTED(Function1118c2);
    // REDIRECTED(Function110235);
    // REDIRECTED(Function11186e);
    // REDIRECTED(Function112271);
    // REDIRECTED(Function113592);
    // REDIRECTED(Function11115f);
    // REDIRECTED(Function112566);
    // REDIRECTED(Function113482);
    // REDIRECTED(Function113317);
    // REDIRECTED(Function111dd9);
    // REDIRECTED(Unknown_1120f5);
    // REDIRECTED(Function1128bd);
    // REDIRECTED(Function112b11);
    // REDIRECTED(MobilePacket_TelephoneStatus);
    // REDIRECTED(Function1125bf);
    // REDIRECTED(Function1111fe);
    // REDIRECTED(Function113f2d);
    // REDIRECTED(Function1117a0);
    // REDIRECTED(PacketSendBytes);
    // REDIRECTED(Function1123b6);
    // REDIRECTED(Function113519);
    // REDIRECTED(Function1136c1);
    // REDIRECTED(Function113206);
    // REDIRECTED(Function11391e);
    // REDIRECTED(Function111abd);
    // REDIRECTED(Function110582);
    // REDIRECTED(Function112a2c);
    // REDIRECTED(Function1127f3);
    // REDIRECTED(Function1128db);
    // REDIRECTED(Unknown_113001);
    // REDIRECTED(MobilePacket_WriteConfigurationData);
    // REDIRECTED(Unknown_112115);
    // REDIRECTED(Function110393);
    // REDIRECTED(Function113eb8);
    // REDIRECTED(Function111b3c);
    // REDIRECTED(Function113ef2);
    // REDIRECTED(Function110f07);
    // REDIRECTED(MobileSDK_CopyStringLen);
    // REDIRECTED(Function11058c);
    // REDIRECTED(Function111ef8);
    // REDIRECTED(Function111d70);
    // REDIRECTED(Function113245);
    // REDIRECTED(MobilePacket_ReadConfigurationDataPart1);
    // REDIRECTED(Function111f02);
    // REDIRECTED(Function113620);
    // REDIRECTED(Function113626);
    // REDIRECTED(Function112a42);
    // REDIRECTED(Unknown_113a70);
    // REDIRECTED(Function1139de);
    // REDIRECTED(URIPrefix);
    // REDIRECTED(Function111b2e);
    // REDIRECTED(Function111d65);
    // REDIRECTED(Function112534);
    // REDIRECTED(Function1119f0);
    // REDIRECTED(Unknown_1120db);
    // REDIRECTED(Unknown_11213d);
    // REDIRECTED(MobilePacket_CloseTCPConnection);

    // mobile/fixed_words.c
    // REDIRECTED(Function11c05d);
    // REDIRECTED(Function11c618);
    // REDIRECTED(Function11cd20);
    // REDIRECTED(Unknown_11c854);
    // REDIRECTED(Function11c9c3);
    // REDIRECTED(Function11c08f);
    // REDIRECTED(Function11ca19);
    // REDIRECTED(Function11c95d);
    // REDIRECTED(Function11c4be);
    // REDIRECTED(EZChat_GetSeenPokemonByKana);
    // REDIRECTED(String_11ccb9);
    // REDIRECTED(String_11cf79);
    // REDIRECTED(GetLengthOfWordAtC608);
    // REDIRECTED(PrintEZChatBattleMessage);
    // REDIRECTED(Function11ce2b);
    // REDIRECTED(Function11ca01);
    // REDIRECTED(String_11ca38);
    // REDIRECTED(Function11cb66);
    // REDIRECTED(MobileEZChatCategoryNames);
    // REDIRECTED(Function11c658);
    // REDIRECTED(Function11c4a5);
    // REDIRECTED(Function11c53d);
    // REDIRECTED(String_11c51b);
    // REDIRECTED(Function11c52c);
    // REDIRECTED(Function11c38a);
    // REDIRECTED(Unknown_11ceb9);
    // REDIRECTED(EZChat_SortedWords);
    // REDIRECTED(Function11ce0b);
    // REDIRECTED(EZChatSlowpokeLZ);
    // REDIRECTED(Function11c675);
    // REDIRECTED(Function11cdaa);
    // REDIRECTED(Function11cfb5);
    // REDIRECTED(EZChat_PlaceCategoryNames);
    // REDIRECTED(Function11cbf5);
    // REDIRECTED(String_11cc09);
    // REDIRECTED(Function11c075);
    // REDIRECTED(String_11c4db);
    // REDIRECTED(Unknown_11cc7e);
    // REDIRECTED(MobileEZChatCategoryPointers);
    // REDIRECTED(CopyMobileEZChatToC608);
    // REDIRECTED(Function11c1ab);
    // REDIRECTED(Function11ca7f);
    // REDIRECTED(MobileEZChatData_WordAndPageCounts);
    // REDIRECTED(EZChat_ClearBottom12Rows);
    // REDIRECTED(AnimateEZChatCursor);
    // REDIRECTED(EZChat_MasterLoop);
    // REDIRECTED(Function11c373);
    // REDIRECTED(Unknown_11cfc2);
    // REDIRECTED(Function11c082);
    // REDIRECTED(MobileString_Page);
    // REDIRECTED(String_11cc60);
    // REDIRECTED(Function11ca6a);
    // REDIRECTED(String_11cdd9);
    // REDIRECTED(Function11c9bd);
    // REDIRECTED(Function11cd54);
    // REDIRECTED(Palette_11d33a);
    // REDIRECTED(Coords_11c63a);
    // REDIRECTED(String_11cd10);
    // REDIRECTED(Unknown_11cfca);
    // REDIRECTED(Function11d035);
    // REDIRECTED(Function11c254);
    // REDIRECTED(String_11ca57);
    // REDIRECTED(BCD2String);
    // REDIRECTED(Unknown_11cfba);
    // REDIRECTED(EZChat_GetCategoryWordsByKana);
    // REDIRECTED(String_11cb1c);
    // REDIRECTED(String_11cc42);
    // REDIRECTED(MobileString_Prev);
    // REDIRECTED(Function11c8f6);
    // REDIRECTED(Function11d323);
    // REDIRECTED(Function11c7bc);
    // REDIRECTED(MobileString_Next);
    // REDIRECTED(String_11cc86);
    // REDIRECTED(String_11cc9d);
    // REDIRECTED(Unknown_11cfc6);
    // REDIRECTED(Unknown_11c986);
    // REDIRECTED(Function11cd04);
    // REDIRECTED(String_11cc23);
    // REDIRECTED(Function11c3c2);
    // REDIRECTED(Function11c9ab);
    // REDIRECTED(Function11cfce);
    // REDIRECTED(String_11cdc7);
    // REDIRECTED(Function11c3ed);
    // REDIRECTED(String_11cdf5);
    // REDIRECTED(String_11ccd4);
    // REDIRECTED(SelectStartGFX);
    // REDIRECTED(Function11c86e);
    // REDIRECTED(Function11c770);
    // REDIRECTED(Function11ca5e);
    // REDIRECTED(Unknown_11cc01);
    // REDIRECTED(Function11c1b9);
    // REDIRECTED(Unknown_11cfbe);
    // REDIRECTED(Function11ccef);
    // REDIRECTED(Function11cb52);
    // REDIRECTED(Function11c35f);
    // REDIRECTED(Function11caad);
    // REDIRECTED(EZChatString_Stop_Mode_Cancel);
    // REDIRECTED(Function11cab3);
    // REDIRECTED(String_11c3bc);
    // REDIRECTED(Function11c992);
    // REDIRECTED(String_11cb31);

    // mobile/print_opp_message.c
    // CONVERTED(Mobile_PrintOpponentBattleMessage);

    // mobile/mobile_5b.c
    // CONVERTED(Function16cc73);
    // CONVERTED(Unknown_16cfa9);
    // CONVERTED(Function16c0a8);
    // CONVERTED(Function16cbba);
    // CONVERTED(Function16cb40);
    // CONVERTED(Function16c089);
    // CONVERTED(Function16cc49);
    // CONVERTED(Function16c0dc);
    // CONVERTED(Function16c0ec);
    // CONVERTED(Function16cc6e);
    // CONVERTED(Function16cae8);
    // CONVERTED(Unknown_16cbfb);
    // CONVERTED(Function16cc90);
    // CONVERTED(Function16cb08);
    // CONVERTED(Function16cb2e);
    // CONVERTED(Function16cad8);
    // CONVERTED(Function16cbd1);
    // CONVERTED(Function16cc62);
    // CONVERTED(Function16cbae);
    // CONVERTED(Function16ca11);
    // CONVERTED(MobileAdapterCheckGFX);
    // CONVERTED(Function16cb5d);
    // CONVERTED(Function16c000);
    // CONVERTED(Unknown_16cb86);
    // CONVERTED(Function16cba3);
    // CONVERTED(Function16cabb);
    // CONVERTED(Function16c0fa);
    // CONVERTED(Function16c0ca);
    // CONVERTED(Function16cc02);
    // CONVERTED(MobileSystemSplashScreen_InitGFX);
    // CONVERTED(Function16c943);
    // CONVERTED(Function16c0ba);
    // CONVERTED(Function16cc18);
    // CONVERTED(Function16cc5a);
    // CONVERTED(Function16cb0f);
    // CONVERTED(Function16c09e);
    // CONVERTED(Function16cab6);
    // CONVERTED(Function16cadc);
    // CONVERTED(Function16cc25);
    // CONVERTED(MobileSplashScreenPalettes);
    // CONVERTED(Unknown_16cfb9);
    // CONVERTED(Function16cac4);
    // CONVERTED(Unknown_16cfb1);
    // CONVERTED(Unknown_16cfa3);

    // mobile/mobile_12_2.c
    // CONVERTED(Function4aa34);
    // REDIRECTED(MobileCheckOwnMonAnywhere);
    // CONVERTED(String_4ada0);
    // CONVERTED(String_4ada7);
    // CONVERTED(Function4ab06);
    // CONVERTED(String_4ad9a);
    // CONVERTED(Function4a94e);
    // CONVERTED(MobilePickThreeMonForBattleText);
    // CONVERTED(Function4ab99);
    // CONVERTED(MobileUseTheseThreeMonText);
    // CONVERTED(Function4a9c3);
    // CONVERTED(Function4aa7a);
    // CONVERTED(Function4acaa);
    // CONVERTED(Function4adf7);
    // CONVERTED(Function4aba8);
    // CONVERTED(Function4ac58);
    // CONVERTED(Function4adb2);
    // CONVERTED(UnusedFindItemInPCOrBag);
    // CONVERTED(Function4a9d7);
    // CONVERTED(Function4ab1a);
    // CONVERTED(Function4aa6e);
    // CONVERTED(Function4aad3);
    // CONVERTED(Function4abc3);
    // CONVERTED(MobileOnlyThreeMonMayEnterText);
    // CONVERTED(MenuHeader_0x4aca2);
    // CONVERTED(Function4ad68);
    // CONVERTED(Function4aab6);
    // CONVERTED(Function4aafb);
    // CONVERTED(Function4adc2);
    // CONVERTED(Function4ad67);
    // CONVERTED(Function4ad60);
    // CONVERTED(Function4aa25);
    // CONVERTED(Function4ad17);
    // CONVERTED(Function4aa22);
    // CONVERTED(String_4ad88);
    // CONVERTED(Function4ad56);

    // mobile/mobile_22.c
    // REDIRECTED(Function89c44);
    // REDIRECTED(Unknown_8994a);
    // REDIRECTED(Function89e0a);
    // REDIRECTED(asm_89d90);
    // REDIRECTED(Function8ac70);
    // REDIRECTED(Function89254);
    // REDIRECTED(Function8ad0b);
    // REDIRECTED(Function891fe);
    // REDIRECTED(Function89856);
    // REDIRECTED(Function896f5);
    // REDIRECTED(MobileCardFolderDeleteAreYouSureText);
    // REDIRECTED(MobileCardFolderIntro1Text);
    // REDIRECTED(Function893ef);
    // REDIRECTED(Function8a573);
    // REDIRECTED(Function89a2e);
    // REDIRECTED(String_89116);
    // REDIRECTED(Function896eb);
    // REDIRECTED(Function8939a);
    // REDIRECTED(Function8a03d);
    // REDIRECTED(Function8919e);
    // REDIRECTED(Function895c7);
    // REDIRECTED(Function89e68);
    // REDIRECTED(Function89ff6);
    // REDIRECTED(Function89e58);
    // REDIRECTED(Function8a584);
    // REDIRECTED(Function89a57);
    // REDIRECTED(Function89215);
    // REDIRECTED(Function8a0f5);
    // REDIRECTED(Palette_8a605);
    // REDIRECTED(Function892b7);
    // REDIRECTED(Function8ab11);
    // REDIRECTED(Function8a0a1);
    // REDIRECTED(Function891b8);
    // REDIRECTED(String_8aaf0);
    // REDIRECTED(Function89b00);
    // REDIRECTED(Function8aab6);
    // REDIRECTED(Function895f2);
    // REDIRECTED(Function89261);
    // REDIRECTED(Function89d75);
    // REDIRECTED(Function898f3);
    // REDIRECTED(Function8aa09);
    // REDIRECTED(Function89ee1);
    // REDIRECTED(Function8a3b2);
    // REDIRECTED(Function8977a);
    // REDIRECTED(MobileCardFolderDeletedText);
    // REDIRECTED(Function898be);
    // REDIRECTED(Function89a23);
    // REDIRECTED(Unknown_89bf5);
    // REDIRECTED(MenuHeader_0x8a40f);
    // REDIRECTED(Function893fe);
    // REDIRECTED(Function8987f);
    // REDIRECTED(Function8a4d3);
    // REDIRECTED(Function8949c);
    // REDIRECTED(Function89f6a);
    // REDIRECTED(Function8aa73);
    // REDIRECTED(Function89d5e);
    // REDIRECTED(Unknown_8a408);
    // REDIRECTED(Function891de);
    // REDIRECTED(Function8963d);
    // REDIRECTED(Function8a818);
    // REDIRECTED(Function892b4);
    // REDIRECTED(MenuHeader_0x8a9f2);
    // REDIRECTED(Function8a20d);
    // REDIRECTED(Jumptable_8a9c5);
    // REDIRECTED(Function8ac76);
    // REDIRECTED(Function89363);
    // REDIRECTED(MenuData_0x8a1a2);
    // REDIRECTED(Function8adb3);
    // REDIRECTED(MenuHeader_0x8a2ef);
    // REDIRECTED(MenuHeader_0x8a9c9);
    // REDIRECTED(Function8999c);
    // REDIRECTED(Function89b3b);
    // REDIRECTED(String_8911c);
    // REDIRECTED(Function89688);
    // REDIRECTED(Strings_8a483);
    // REDIRECTED(Function89d0d);
    // REDIRECTED(Function89f77);
    // REDIRECTED(Function89e1e);
    // REDIRECTED(Function89b1e);
    // REDIRECTED(Function8aba9);
    // REDIRECTED(MobileCardFolderAskDeleteOldText);
    // REDIRECTED(Function8a2fe);
    // REDIRECTED(Function8a0ec);
    // REDIRECTED(Function8a262);
    // REDIRECTED(Function8921f);
    // REDIRECTED(Mobile22_PromptButton);
    // REDIRECTED(Function8a31c);
    // REDIRECTED(MenuData_0x8a43d);
    // REDIRECTED(Function89185);
    // REDIRECTED(Function894dc);
    // REDIRECTED(Function89193);
    // REDIRECTED(Function89cdf);
    // REDIRECTED(MobileCardFolderAskDeleteText);
    // REDIRECTED(Function8a5a3);
    // REDIRECTED(String_8a919);
    // REDIRECTED(String_8ad89);
    // REDIRECTED(Function89807);
    // REDIRECTED(Function89de0);
    // REDIRECTED(Function8a0de);
    // REDIRECTED(MobileCardFolderIntro4Text);
    // REDIRECTED(Jumptable_89e04);
    // REDIRECTED(Function89fce);
    // REDIRECTED(MenuHeader_0x8a19a);
    // REDIRECTED(Function89f9a);
    // REDIRECTED(Function8aa0a);
    // REDIRECTED(Function8a7cb);
    // REDIRECTED(MenuHeader_0x892a3);
    // REDIRECTED(Function89b97);
    // REDIRECTED(Function899fe);
    // REDIRECTED(Function8a453);
    // REDIRECTED(Function8967a);
    // REDIRECTED(Function8a6c0);
    // REDIRECTED(String_8ad9c);
    // REDIRECTED(Function8a8c3);
    // REDIRECTED(Mobile22_SetBGMapMode1);
    // REDIRECTED(Function8a1b0);
    // REDIRECTED(Jumptable_8a6bc);
    // REDIRECTED(Function8a62c);
    // REDIRECTED(Function896ff);
    // REDIRECTED(Palette_895de);
    // REDIRECTED(Function8adbf);
    // REDIRECTED(Function8ac7c);
    // REDIRECTED(MenuData_0x892ab);
    // REDIRECTED(Unknown_89c1f);
    // REDIRECTED(Function8a17b);
    // REDIRECTED(Palette_8a5e5);
    // REDIRECTED(Function89381);
    // REDIRECTED(Function8916e);
    // REDIRECTED(Function894bb);
    // REDIRECTED(asm_8a529);
    // REDIRECTED(Function8a6c5);
    // REDIRECTED(Jumptable_8a74f);
    // REDIRECTED(String_89153);
    // REDIRECTED(Function8a78c);
    // REDIRECTED(Function8a999);
    // REDIRECTED(Function89844);
    // REDIRECTED(Function893b3);
    // REDIRECTED(Function8a3a2);
    // REDIRECTED(asm_89e2e);
    // REDIRECTED(Function89605);
    // REDIRECTED(Function8a04c);
    // REDIRECTED(Function89e6f);
    // REDIRECTED(Unknown_89942);
    // REDIRECTED(Function89174);
    // REDIRECTED(Function8a0e6);
    // REDIRECTED(Function89168);
    // REDIRECTED(v_incave);
    // REDIRECTED(Function89d85);
    // REDIRECTED(Function89464);
    // REDIRECTED(Function89eb9);
    // REDIRECTED(EZChatCursorGFX);
    // REDIRECTED(MenuHeader_0x8a435);
    // REDIRECTED(Function89771);
    // REDIRECTED(String_899ac);
    // REDIRECTED(Function8a53d);
    // REDIRECTED(String_8ac3b);
    // REDIRECTED(Function8932d);
    // REDIRECTED(Function898aa);
    // REDIRECTED(Function891ab);
    // REDIRECTED(Palette_894b3);
    // REDIRECTED(Jumptable_8aa6d);
    // REDIRECTED(Function89481);
    // REDIRECTED(Function8adcc);
    // REDIRECTED(String_89a53);
    // REDIRECTED(Function89245);
    // REDIRECTED(MobileCardFolderFinishRegisteringCardsText);
    // REDIRECTED(Function89a0c);
    // REDIRECTED(Function8a116);
    // REDIRECTED(Function896d6);
    // REDIRECTED(Function89b07);
    // REDIRECTED(Function8a8a1);
    // REDIRECTED(MenuData_0x8a417);
    // REDIRECTED(Function8ab3b);
    // REDIRECTED(Function89c67);
    // REDIRECTED(Function8a2aa);
    // REDIRECTED(Function899b2);
    // REDIRECTED(Function896cb);
    // REDIRECTED(String_89135);
    // REDIRECTED(Function8a60d);
    // REDIRECTED(Function89655);
    // REDIRECTED(Function8a6cd);
    // REDIRECTED(Function89448);
    // REDIRECTED(Function89736);
    // REDIRECTED(Function89829);
    // REDIRECTED(Function89753);
    // REDIRECTED(Function8998b);
    // REDIRECTED(Function89b45);
    // REDIRECTED(Jumptable_89e3c);
    // REDIRECTED(MobileCardFolderIntro2Text);
    // REDIRECTED(Function8ac4e);
    // REDIRECTED(Function891ca);
    // REDIRECTED(Mobile_EnableSpriteUpdates);
    // REDIRECTED(Function89346);
    // REDIRECTED(Function89492);
    // REDIRECTED(Function89962);
    // REDIRECTED(Function89e9a);
    // REDIRECTED(Function8934a);
    // REDIRECTED(Function893e2);
    // REDIRECTED(Function896e1);
    // REDIRECTED(Function8a0ff);
    // REDIRECTED(Function898dc);
    // REDIRECTED(String_8a476);
    // REDIRECTED(Function8a400);
    // REDIRECTED(Unknown_89c0a);
    // REDIRECTED(Function8a765);
    // REDIRECTED(Function89c34);
    // REDIRECTED(Function89b14);
    // REDIRECTED(Strings_8a1cc);
    // REDIRECTED(Function89b78);
    // REDIRECTED(Function8a383);
    // REDIRECTED(Function8975b);
    // REDIRECTED(Function8a4fc);
    // REDIRECTED(String_8a926);
    // REDIRECTED(Function8a679);
    // REDIRECTED(String_8a88b);
    // REDIRECTED(Function895e6);
    // REDIRECTED(Function89455);
    // REDIRECTED(Function89975);
    // REDIRECTED(Function899c9);
    // REDIRECTED(Function894ca);
    // REDIRECTED(Function8a3df);
    // REDIRECTED(Function8a930);
    // REDIRECTED(Function8994e);
    // REDIRECTED(Function8a5b6);
    // REDIRECTED(Function89259);
    // REDIRECTED(Function8917a);
    // REDIRECTED(Palette_8a5fd);
    // REDIRECTED(Function89305);
    // REDIRECTED(Function8931b);
    // REDIRECTED(Unknown_89bd8);
    // REDIRECTED(MobileCardFolderIntro3Text);
    // REDIRECTED(OpenSRAMBank4);
    // REDIRECTED(Function8a241);
    // REDIRECTED(Function89797);
    // REDIRECTED(Function8971f);
    // REDIRECTED(Function89915);
    // REDIRECTED(Function89e36);
    // REDIRECTED(Function8a0c1);
    // REDIRECTED(Unknown_89be0);
    // REDIRECTED(Function8a515);
    // REDIRECTED(Function89331);
    // REDIRECTED(Mobile22_SetBGMapMode0);
    // REDIRECTED(Function8ab93);
    // REDIRECTED(MenuHeader_0x8a176);
    // REDIRECTED(Function8966c);
    // REDIRECTED(Function899d3);
    // REDIRECTED(Function897d5);
    // REDIRECTED(Function8942b);
    // REDIRECTED(MenuData_0x8a9fa);
    // REDIRECTED(Jumptable_89e18);
    // REDIRECTED(Function8a58d);
    // REDIRECTED(Function8956f);
    // REDIRECTED(Function8a57c);
    // REDIRECTED(Function89fa5);
    // REDIRECTED(Function8ab00);
    // REDIRECTED(Function8a313);
    // REDIRECTED(Palette_89eb1);
    // REDIRECTED(Function893cc);
    // REDIRECTED(String_89a4e);
    // REDIRECTED(Function8a0c9);
    // REDIRECTED(Function891d3);
    // REDIRECTED(Function89fed);
    // REDIRECTED(Unknown_8a40b);
    // REDIRECTED(Function89efd);
    // REDIRECTED(Function897af);
    // REDIRECTED(Function89dab);
    // REDIRECTED(Palette_8a624);
    // REDIRECTED(Jumptable_8a671);
    // REDIRECTED(Function8a9ce);
    // REDIRECTED(Function8a055);
    // REDIRECTED(Mobile_DisableSpriteUpdates);
    // REDIRECTED(Function8a757);
    // REDIRECTED(Function89b28);
    // REDIRECTED(Function8925e);
    // REDIRECTED(MobileCardFolderAskOpenOldText);

    // mobile/mobile_22_2.c
    // REDIRECTED(Function8b677);
    // REDIRECTED(Function8b75d);
    // REDIRECTED(MenuData_0x8b870);
    // REDIRECTED(Function8b4a4);
    // REDIRECTED(Function8b4d8);
    // REDIRECTED(UnknownText_0x8b64c);
    // REDIRECTED(Function8b83e);
    // REDIRECTED(Function8b855);
    // REDIRECTED(String_8b90b);
    // REDIRECTED(Function8b4b8);
    // REDIRECTED(Function8b45c);
    // REDIRECTED(MenuData_0x8b9b9);
    // REDIRECTED(Function8b6bb);
    // REDIRECTED(Function8b3b0);
    // REDIRECTED(Palette_8b6d5);
    // REDIRECTED(Function8b4cc);
    // REDIRECTED(PasscodeSetText);
    // REDIRECTED(MenuHeader_0x8b9b1);
    // REDIRECTED(Function8b342);
    // REDIRECTED(MenuHeader_0x8b9ca);
    // REDIRECTED(Function8b379);
    // REDIRECTED(Function8b36c);
    // REDIRECTED(Function8b787);
    // REDIRECTED(Function8b3a4);
    // REDIRECTED(Function8b84b);
    // REDIRECTED(String_8b919);
    // REDIRECTED(Function8b960);
    // REDIRECTED(Function8b3cd);
    // REDIRECTED(Jumptable_8b4a0);
    // REDIRECTED(Function8b788);
    // REDIRECTED(Function8b88c);
    // REDIRECTED(Function8b5e7);
    // REDIRECTED(Function8b690);
    // REDIRECTED(Function8b664);
    // REDIRECTED(Function8b8c8);
    // REDIRECTED(MenuData_0x8b9d2);
    // REDIRECTED(Function8b4ea);
    // REDIRECTED(Function8b363);
    // REDIRECTED(PasscodesNotSameText);
    // REDIRECTED(Function8b493);
    // REDIRECTED(Function8b385);
    // REDIRECTED(Function8b3dd);
    // REDIRECTED(Function8b539);
    // REDIRECTED(ConfirmPasscodeText);
    // REDIRECTED(Function8b832);
    // REDIRECTED(String_8b938);
    // REDIRECTED(Function8b703);
    // REDIRECTED(Function8b391);
    // REDIRECTED(String_8b92a);
    // REDIRECTED(Function8b6ed);
    // REDIRECTED(FourZerosInvalidText);
    // REDIRECTED(Unknown_8b529);
    // REDIRECTED(Function8b50a);
    // REDIRECTED(Function8b4fd);
    // REDIRECTED(Function8b99f);
    // REDIRECTED(Function8b9ab);
    // REDIRECTED(Function8b732);
    // REDIRECTED(Function8b521);
    // REDIRECTED(EnterNewPasscodeText);
    // REDIRECTED(Function8b79e);
    // REDIRECTED(Unknown_8ba1f);
    // REDIRECTED(Function8b518);
    // REDIRECTED(MenuHeader_0x8b9ac);
    // REDIRECTED(Function8b35d);
    // REDIRECTED(Function8b555);
    // REDIRECTED(EnterPasscodeText);
    // REDIRECTED(Function8b73e);
    // REDIRECTED(Function8b744);
    // REDIRECTED(MenuHeader_0x8b867);
    // REDIRECTED(Unknown_8b903);
    // REDIRECTED(Function8b9e9);
    // REDIRECTED(Function8b7bd);
    // REDIRECTED(Function8b880);
    // REDIRECTED(Unknown_8ba1c);
    // REDIRECTED(IncorrectPasscodeText);
    // REDIRECTED(Function8b94a);

    // mobile/mobile_5e.c
    // REDIRECTED(Function17ac1d);
    // REDIRECTED(Function17aa98);
    // REDIRECTED(Function17a7cd);
    // REDIRECTED(Function17a6a8);
    // REDIRECTED(ChrisSilhouetteGFX);
    // REDIRECTED(DialpadGFX);
    // REDIRECTED(Function17a8ae);
    // REDIRECTED(Function17aa88);
    // REDIRECTED(Function17a6f5);
    // REDIRECTED(Function17aad7);
    // REDIRECTED(Function17a770);
    // REDIRECTED(Function17a68f);
    // REDIRECTED(Function17aa22);
    // REDIRECTED(Palette_17ac95);
    // REDIRECTED(Palette_17ac55);
    // REDIRECTED(MobileCardListGFX);
    // REDIRECTED(Function17a7c2);
    // REDIRECTED(Function17a964);
    // REDIRECTED(MobileCard2GFX);
    // REDIRECTED(String_17a9b2);
    // REDIRECTED(Function17aa4a);
    // REDIRECTED(Unknown_17aa77);
    // REDIRECTED(Function17a781);
    // REDIRECTED(Function17a7a6);
    // REDIRECTED(Function17a99e);
    // REDIRECTED(Function17ac46);
    // REDIRECTED(Function17a7ae);
    // REDIRECTED(Palette_17b4b5);
    // REDIRECTED(Function17a7ff);
    // REDIRECTED(DialpadTilemap);
    // REDIRECTED(Function17a91e);
    // REDIRECTED(Function17a83c);
    // REDIRECTED(Function17a8de);
    // REDIRECTED(Function17a97b);
    // REDIRECTED(Function17a9f5);
    // REDIRECTED(Function17a713);
    // REDIRECTED(Function17aae3);
    // REDIRECTED(DialpadAttrmap);
    // REDIRECTED(Function17a9cb);
    // REDIRECTED(Function17aac3);
    // REDIRECTED(Function17aaa9);
    // REDIRECTED(Unknown_17aa72);
    // REDIRECTED(Function17abcf);
    // REDIRECTED(Function17a78f);
    // REDIRECTED(Function17aad0);
    // REDIRECTED(CardLargeSpriteAndFolderGFX);
    // REDIRECTED(Function17aad3);
    // REDIRECTED(Function17ac2a);
    // REDIRECTED(Function17a721);
    // REDIRECTED(Jumptable_17a7b6);
    // REDIRECTED(Function17a7d8);
    // REDIRECTED(Function17a81a);
    // REDIRECTED(Unknown_17aaf7);
    // REDIRECTED(Function17ac0c);
    // REDIRECTED(Function17a751);
    // REDIRECTED(asm_17aa91);
    // REDIRECTED(DialpadCursorGFX);
    // REDIRECTED(Function17a9e3);
    // REDIRECTED(Function17aae0);
    // REDIRECTED(CardSpriteGFX);
    // REDIRECTED(KrisSilhouetteGFX);
    // REDIRECTED(Function17a943);
    // REDIRECTED(Function17a7f4);
    // REDIRECTED(Function17aba0);
    // REDIRECTED(MobileCardGFX);
    // REDIRECTED(Function17a848);

    // mobile/mobile_42.c
    // REDIRECTED(MobileTradeAnim_MonDisplay_PrintOTNameAndGender);
    // REDIRECTED(MobileTradeAnim_GetTrademon1);
    // REDIRECTED(RunMobileTradeAnim_NoFrontpics);
    // REDIRECTED(MobileTradeAnim_ShowPlayerMonForGTS);
    // REDIRECTED(LoadMobileAdapterPalette);
    // REDIRECTED(UnusedMobilePulsePalettes);
    // REDIRECTED(Function108b98);
    // REDIRECTED(Function10898a);
    // REDIRECTED(MobileTradeAnimation_SendGivemonToGTS);
    // REDIRECTED(MobileCable1GFX);
    // REDIRECTED(MobileTradeAnim_FadeToBlack);
    // REDIRECTED(MobileTradeAnim_MonDisplay_UpdateBGMap);
    // REDIRECTED(MobileTradeAnim_MonDisplay_PrintSpeciesNumber);
    // REDIRECTED(Function108c6d);
    // REDIRECTED(Function108c16);
    // REDIRECTED(MobileTradeAnim_LoadMonTemplate);
    // REDIRECTED(MobileTradeAnim_JumptableLoop);
    // REDIRECTED(Function108026);
    // REDIRECTED(RunMobileTradeAnim_Frontpics);
    // REDIRECTED(Function108963);
    // REDIRECTED(asm_10802c);
    // REDIRECTED(MobileTradeAnim_ClearBGMap);
    // REDIRECTED(MobileTradeAnim_DisplayEggData);
    // REDIRECTED(Palette_108b98);
    // REDIRECTED(Function10804d);
    // REDIRECTED(Function108b5a);
    // REDIRECTED(MobileTradeOB2Palettes);
    // REDIRECTED(MobileTradeAnim_02);
    // REDIRECTED(MobileTradeAnim_DeleteSprites);
    // REDIRECTED(Function108c80);
    // REDIRECTED(MobileTradeAnim_DisplayReceivedMon);
    // REDIRECTED(MobileTradeAnim_Next);
    // REDIRECTED(MobileTradeAnimation_ReceiveGetmonFromGTS);
    // REDIRECTED(MobileTradeAnim_GetTrademon3);
    // REDIRECTED(MobileTradeAnim_InitSpeciesName);
    // REDIRECTED(MobileTradeAnim_ClearTiles);
    // REDIRECTED(MobileTradeAnim_GetOddEgg);
    // REDIRECTED(MobileTradeAnim_10);
    // REDIRECTED(MobileTradeAnim_05);
    // REDIRECTED(Function1080b7);
    // REDIRECTED(MobileTradeAnim_DisplayMonToBeSent);
    // REDIRECTED(MobileTradeAnim_06);
    // REDIRECTED(GetMobileTradeAnimByte);
    // REDIRECTED(Function1082db);
    // REDIRECTED(MobileTradeAnim_AnimateOTPulse);
    // REDIRECTED(Function10803d);
    // REDIRECTED(Function108bec);
    // REDIRECTED(asm_108966);
    // REDIRECTED(MobileTradeGFX);
    // REDIRECTED(MobileTradeTilemapLZ);
    // REDIRECTED(MobileTradeAnim_11);
    // REDIRECTED(WaitMobileTradeSpriteAnims);
    // REDIRECTED(Function108229);
    // REDIRECTED(MobileTradeOB1Palettes);
    // REDIRECTED(Function108219);
    // REDIRECTED(Function108201);
    // REDIRECTED(asm_108018);
    // REDIRECTED(MobileAdapterPalettes);
    // REDIRECTED(EndMobileTradeAnim);
    // REDIRECTED(MobileTradeAnim_ClearTilemap);
    // REDIRECTED(Function108ad4);
    // REDIRECTED(Function108a33);
    // REDIRECTED(MobileTradeAnim_ShowOTMonFromGTS);
    // REDIRECTED(MobileTradeAnim_AnimateSentPulse);
    // REDIRECTED(MobileTradeAnim_MonDisplay_PrintIDNumber);
    // REDIRECTED(MobileTradeAttrmapLZ);
    // REDIRECTED(MobileTradeAnim_GiveTrademon2);
    // REDIRECTED(MobileTradeAnim_07);
    // REDIRECTED(Function108af4);
    // REDIRECTED(DebugMobileTrade);
    // REDIRECTED(Function10802a);
    // REDIRECTED(MobileTradeSpritesGFX);
    // REDIRECTED(MobileCable2GFX);
    // REDIRECTED(Function108157);
    // REDIRECTED(MobileTradeAnimation_RetrieveGivemonFromGTS);
    // REDIRECTED(MobileTradeAnim_GetFrontpic);
    // REDIRECTED(Function108b45);
    // REDIRECTED(MobileTradeAnim_GiveTrademon1);
    // REDIRECTED(Function1082fa);
    // REDIRECTED(MobileTradeAnim_GetTrademon2);
    // REDIRECTED(MobileTradeAnim_ShowPlayerMonToBeSent);
    // REDIRECTED(Function108c40);
    // REDIRECTED(Function10895e);
    // REDIRECTED(MobileTradeAnim_ShowOTMonFromTrade);
    // REDIRECTED(Function1082f0);
    // REDIRECTED(MobileTradeAnim_MonDisplay_PrintSpeciesName);
    // REDIRECTED(Function108b78);
    // REDIRECTED(MobileTradeBGPalettes);
    // REDIRECTED(MobileTradeAnim_0f);
    // REDIRECTED(Function108c2b);
}
