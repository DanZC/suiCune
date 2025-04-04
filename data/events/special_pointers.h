#pragma once

#define special_const(_n) SP_##_n

enum {
    special_const(WarpToSpawnPoint),
// Communications
    special_const(SetBitsForLinkTradeRequest),
    special_const(WaitForLinkedFriend),
    special_const(CheckLinkTimeout_Receptionist),
    special_const(TryQuickSave),
    special_const(CheckBothSelectedSameRoom),
    special_const(FailedLinkToPast),
    special_const(CloseLink),
    special_const(WaitForOtherPlayerToExit),
    special_const(SetBitsForBattleRequest),
    special_const(SetBitsForTimeCapsuleRequest),
    special_const(CheckTimeCapsuleCompatibility),
    special_const(EnterTimeCapsule),
    special_const(TradeCenter),
    special_const(Colosseum),
    special_const(TimeCapsule),
    special_const(CableClubCheckWhichChris),
    special_const(CheckMysteryGift),
    special_const(GetMysteryGiftItem),
    special_const(UnlockMysteryGift),
// Map events
    special_const(BugContestJudging),
    special_const(CheckPartyFullAfterContest),
    special_const(ContestDropOffMons),
    special_const(ContestReturnMons),
    special_const(GiveParkBalls),
    special_const(CheckMagikarpLength),
    special_const(MagikarpHouseSign),
    special_const(HealParty), // this is both a special and a predef
    special_const(PokemonCenterPC),
    special_const(PlayersHousePC),
    special_const(DayCareMan),
    special_const(DayCareLady),
    special_const(DayCareManOutside),
    special_const(MoveDeletion),
    special_const(BankOfMom),
    special_const(MagnetTrain),
    special_const(NameRival),
    special_const(SetDayOfWeek),
    special_const(OverworldTownMap),
    special_const(UnownPrinter),
    special_const(MapRadio),
    special_const(UnownPuzzle),
    special_const(SlotMachine),
    special_const(CardFlip),
    special_const(UnusedMemoryGame), // unused
    special_const(ClearBGPalettesBufferScreen), // unused
    special_const(FadeOutPalettes),
    special_const(BattleTowerFade),
    special_const(FadeBlackQuickly),
    special_const(FadeInPalettes),
    special_const(FadeInQuickly),
    special_const(ReloadSpritesNoPalettes), // bank 0
    special_const(ClearBGPalettes), // bank 0
    special_const(UpdateTimePals), // bank 0
    special_const(ClearTilemap), // bank 0// unused as special
    special_const(UpdateSprites), // bank 0
    special_const(UpdatePlayerSprite), // bank 0
    special_const(GameCornerPrizeMonCheckDex),
    special_const(UnusedSetSeenMon), // unused
    special_const(WaitSFX), // bank 0
    special_const(PlayMapMusic), // bank 0
    special_const(RestartMapMusic), // bank 0
    special_const(HealMachineAnim),
    special_const(SurfStartStep),
    special_const(FindPartyMonAboveLevel), // unused // 0x40
    special_const(FindPartyMonAtLeastThatHappy), // unused
    special_const(FindPartyMonThatSpecies),
    special_const(FindPartyMonThatSpeciesYourTrainerID),
    special_const(UnusedCheckUnusedTwoDayTimer), // unused
    special_const(DayCareMon1),
    special_const(DayCareMon2),
    special_const(SelectRandomBugContestContestants),
    special_const(ActivateFishingSwarm),
    special_const(ToggleMaptileDecorations),
    special_const(ToggleDecorationsVisibility),
    special_const(GiveShuckle),
    special_const(ReturnShuckie),
    special_const(BillsGrandfather),
    special_const(CheckPokerus),
    special_const(DisplayCoinCaseBalance),
    special_const(DisplayMoneyAndCoinBalance), // 0x50
    special_const(PlaceMoneyTopRight),
    special_const(CheckForLuckyNumberWinners),
    special_const(CheckLuckyNumberShowFlag),
    special_const(ResetLuckyNumberShowFlag),
    special_const(PrintTodaysLuckyNumber),
    special_const(SelectApricornForKurt),
    special_const(NameRater),
    special_const(DisplayLinkRecord),
    special_const(GetFirstPokemonHappiness),
    special_const(CheckFirstMonIsEgg),
    special_const(RandomUnseenWildMon),
    special_const(RandomPhoneWildMon),
    special_const(RandomPhoneMon),
    special_const(LoadUsedSpritesGFX),
    special_const(PlaySlowCry),
    special_const(SnorlaxAwake), // 0x60
    special_const(OlderHaircutBrother),
    special_const(YoungerHaircutBrother),
    special_const(DaisysGrooming),
    special_const(PlayCurMonCry),
    special_const(ProfOaksPCBoot),
    special_const(GameboyCheck),
    special_const(TrainerHouse),
    special_const(PhotoStudio),
    special_const(InitRoamMons),
    special_const(FadeOutMusic),
    special_const(Diploma),
    special_const(PrintDiploma),

// Crystal only
    special_const(Function11ac3e),
    special_const(Function11b444),
    special_const(Function11b5e8),
    special_const(Function11b7e5), // 0x70
    special_const(Function11b879),
    special_const(Function11b920),
    special_const(Function11b93b),
    special_const(BattleTowerRoomMenu),
    special_const(Function1700ba),
    special_const(Function170114),
    special_const(BattleTowerBattle),
    special_const(Function1704e1),
    special_const(UnusedBattleTowerDummySpecial1),
    special_const(LoadOpponentTrainerAndPokemonWithOTSprite),
    special_const(Function11ba38),
    special_const(CheckForBattleTowerRules),
    special_const(GiveOddEgg),
    special_const(Reset), // bank 0
    special_const(Function1011f1),
    special_const(Function101220), // 0x80
    special_const(Function101225),
    special_const(Function101231),
    special_const(MoveTutor),
    special_const(OmanyteChamber),
    special_const(Function11c1ab),
    special_const(BattleTowerAction),
    special_const(DisplayUnownWords),
    special_const(Menu_ChallengeExplanationCancel),
    special_const(Function17d2b6),
    special_const(Function17d2ce),
    special_const(BattleTowerMobileError),
    special_const(AskMobileOrCable),
    special_const(HoOhChamber),
    special_const(Function102142),
    special_const(CelebiShrineEvent),
    special_const(CheckCaughtCelebi), // 0x90
    special_const(PokeSeer),
    special_const(BuenasPassword),
    special_const(BuenaPrize),
    special_const(GiveDratini),
    special_const(SampleKenjiBreakCountdown),
    special_const(BeastsCheck),
    special_const(MonCheck),
    special_const(SetPlayerPalette),
    special_const(UnusedBattleTowerDummySpecial2),
    special_const(Mobile_SelectThreeMons),
    special_const(Function1037eb),
    special_const(Function10383c),
    special_const(StubbedTrainerRankings_Healings),
    special_const(RefreshSprites),
    special_const(Function1037c2),
    special_const(Mobile_DummyReturnFalse), // 0xA0
    special_const(Function103780),
    special_const(Function10387b),
    special_const(AskRememberPassword),
    special_const(LoadMapPalettes),
    special_const(UnusedFindItemInPCOrBag),

    special_const(InitialSetDSTFlag),
    special_const(InitialClearDSTFlag),
    special_const(UnusedDummySpecial), // unused
    special_const(BattleTowerRoomMenu_Mobile),
};

extern void (*const SpecialsPointers[])(void);