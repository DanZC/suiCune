#pragma once

// audio/music_4.asm
enum {
    oMusic_ViridianCity               = 0x0000,
    oMusic_ViridianCity_Ch1           = 0x000c,
    oMusic_ViridianCity_Ch2           = 0x0125,
    oMusic_ViridianCity_Ch3           = 0x021e,
    oMusic_ViridianCity_Ch4           = 0x02df,
    oMusic_CeladonCity                = 0x035b,
    oMusic_CeladonCity_Ch1            = 0x0364,
    oMusic_CeladonCity_Ch2            = 0x0406,
    oMusic_CeladonCity_Ch3            = 0x0492,
    oMusic_WildPokemonVictory         = 0x0518,
    oMusic_WildPokemonVictory_Ch1     = 0x0521,
    oMusic_WildPokemonVictory_Ch2     = 0x0575,
    oMusic_WildPokemonVictory_Ch3     = 0x05c4,
    oMusic_SuccessfulCapture          = 0x0602,
    oMusic_SuccessfulCapture_Ch1      = 0x060b,
    oMusic_SuccessfulCapture_Ch2      = 0x061b,
    oMusic_SuccessfulCapture_Ch3      = 0x0626,
    oMusic_GymLeaderVictory           = 0x062c,
    oMusic_GymLeaderVictory_Ch1       = 0x0638,
    oMusic_GymLeaderVictory_Ch2       = 0x06bd,
    oMusic_GymLeaderVictory_Ch3       = 0x0737,
    oMusic_GymLeaderVictory_Ch4       = 0x07e5,
    oMusic_MtMoonSquare               = 0x0815,
    oMusic_MtMoonSquare_Ch1           = 0x081b,
    oMusic_MtMoonSquare_Ch2           = 0x085d,
    oMusic_Gym                        = 0x08ae,
    oMusic_Gym_Ch1                    = 0x08ba,
    oMusic_Gym_Ch2                    = 0x097c,
    oMusic_Gym_Ch3                    = 0x0a37,
    oMusic_Gym_Ch4                    = 0x0ac5,
    oMusic_PalletTown                 = 0x0b0c,
    oMusic_PalletTown_Ch1             = 0x0b15,
    oMusic_PalletTown_Ch2             = 0x0ba1,
    oMusic_PalletTown_Ch3             = 0x0c2a,
    oMusic_ProfOaksPokemonTalk        = 0x0c9f,
    oMusic_ProfOaksPokemonTalk_Ch1    = 0x0ca9,
    oMusic_ProfOaksPokemonTalk_Ch2    = 0x0d31,
    oMusic_ProfOaksPokemonTalk_Ch3    = 0x0d82,
    oMusic_ProfOak                    = 0x0dea,
    oMusic_ProfOak_Ch1                = 0x0df3,
    oMusic_ProfOak_Ch2                = 0x0e7e,
    oMusic_ProfOak_Ch3                = 0x0ef5,
    oMusic_LookRival                  = 0x0f79,
    oMusic_LookRival_Ch1              = 0x0f85,
    oMusic_LookRival_Ch2              = 0x1010,
    oMusic_LookRival_Ch3              = 0x1086,
    oMusic_LookRival_Ch4              = 0x1106,
    oMusic_AfterTheRivalFight         = 0x1127,
    oMusic_AfterTheRivalFight_Ch1     = 0x1133,
    oMusic_AfterTheRivalFight_Ch2     = 0x1153,
    oMusic_AfterTheRivalFight_Ch3     = 0x116a,
    oMusic_AfterTheRivalFight_Ch4     = 0x117a,
    oMusic_Surf                       = 0x118a,
    oMusic_Surf_Ch1                   = 0x1194,
    oMusic_Surf_Ch2                   = 0x1317,
    oMusic_Surf_Ch3                   = 0x140c,
    oMusic_NationalPark               = 0x14e8,
    oMusic_NationalPark_Ch1           = 0x14f4,
    oMusic_NationalPark_Ch2           = 0x1652,
    oMusic_NationalPark_Ch3           = 0x1723,
    oMusic_NationalPark_Ch4           = 0x17b8,
    oMusic_AzaleaTown                 = 0x17e8,
    oMusic_AzaleaTown_Ch1             = 0x17f4,
    oMusic_AzaleaTown_Ch2             = 0x191d,
    oMusic_AzaleaTown_Ch3             = 0x1a08,
    oMusic_AzaleaTown_Ch4             = 0x1ae5,
    oMusic_CherrygroveCity            = 0x1b03,
    oMusic_CherrygroveCity_Ch1        = 0x1b0f,
    oMusic_CherrygroveCity_Ch2        = 0x1b74,
    oMusic_CherrygroveCity_Ch3        = 0x1bd8,
    oMusic_CherrygroveCity_Ch4        = 0x1c48,
    oMusic_UnionCave                  = 0x1c60,
    oMusic_UnionCave_Ch1              = 0x1c6c,
    oMusic_UnionCave_Ch2              = 0x1cd5,
    oMusic_UnionCave_Ch3              = 0x1d58,
    oMusic_UnionCave_Ch4              = 0x1da5,
    oMusic_JohtoWildBattle            = 0x1dc5,
    oMusic_JohtoWildBattle_Ch1        = 0x1dce,
    oMusic_JohtoWildBattle_Ch2        = 0x1ea2,
    oMusic_JohtoWildBattle_Ch3        = 0x1f91,
    oMusic_JohtoWildBattleNight       = 0x205c,
    oMusic_JohtoWildBattleNight_Ch1   = 0x2065,
    oMusic_JohtoWildBattleNight_Ch2   = 0x2076,
    oMusic_JohtoWildBattleNight_Ch3   = 0x208f,
    oMusic_JohtoTrainerBattle         = 0x2096,
    oMusic_JohtoTrainerBattle_Ch1     = 0x209f,
    oMusic_JohtoTrainerBattle_Ch2     = 0x22b3,
    oMusic_JohtoTrainerBattle_Ch3     = 0x24de,
    oMusic_LookYoungster              = 0x26c3,
    oMusic_LookYoungster_Ch1          = 0x26cc,
    oMusic_LookYoungster_Ch2          = 0x270f,
    oMusic_LookYoungster_Ch3          = 0x2784,
    oMusic_TinTower                   = 0x2811,
    oMusic_TinTower_Ch1               = 0x281d,
    oMusic_TinTower_Ch2               = 0x288b,
    oMusic_TinTower_Ch3               = 0x28f8,
    oMusic_TinTower_Ch4               = 0x2948,
    oMusic_SproutTower                = 0x2974,
    oMusic_SproutTower_Ch1            = 0x2980,
    oMusic_SproutTower_Ch2            = 0x29c8,
    oMusic_SproutTower_Ch3            = 0x2a25,
    oMusic_SproutTower_Ch4            = 0x2a7a,
    oMusic_BurnedTower                = 0x2a99,
    oMusic_BurnedTower_Ch1            = 0x2aa5,
    oMusic_BurnedTower_Ch2            = 0x2b29,
    oMusic_BurnedTower_Ch3            = 0x2ba2,
    oMusic_BurnedTower_Ch4            = 0x2bdd,
    oMusic_Mom                        = 0x2bf2,
    oMusic_Mom_Ch2                    = 0x2bfb,
    oMusic_Mom_Ch3                    = 0x2c20,
    oMusic_Mom_Ch4                    = 0x2c51,
    oMusic_VictoryRoad                = 0x2c72,
    oMusic_VictoryRoad_Ch1            = 0x2c7e,
    oMusic_VictoryRoad_Ch2            = 0x2cce,
    oMusic_VictoryRoad_Ch3            = 0x2d2c,
    oMusic_VictoryRoad_Ch4            = 0x2d5f,
    oMusic_PokemonLullaby             = 0x2d79,
    oMusic_PokemonLullaby_Ch1         = 0x2d82,
    oMusic_PokemonLullaby_Ch2         = 0x2dc4,
    oMusic_PokemonLullaby_Ch3         = 0x2e03,
    oMusic_PokemonMarch               = 0x2e23,
    oMusic_PokemonMarch_Ch1           = 0x2e2f,
    oMusic_PokemonMarch_Ch2           = 0x2ec1,
    oMusic_PokemonMarch_Ch3           = 0x2f4d,
    oMusic_PokemonMarch_Ch4           = 0x2ffa,
    oMusic_GoldSilverOpening          = 0x3055,
    oMusic_GoldSilverOpening_Ch1      = 0x305e,
    oMusic_GoldSilverOpening_Ch2      = 0x30f8,
    oMusic_GoldSilverOpening_Ch3      = 0x31c8,
    oMusic_GoldSilverOpening2         = 0x3308,
    oMusic_GoldSilverOpening2_Ch1     = 0x3314,
    oMusic_GoldSilverOpening2_Ch2     = 0x3358,
    oMusic_GoldSilverOpening2_Ch3     = 0x339c,
    oMusic_GoldSilverOpening2_Ch4     = 0x33ea,
    oMusic_LookHiker                  = 0x3411,
    oMusic_LookHiker_Ch1              = 0x341d,
    oMusic_LookHiker_Ch2              = 0x3443,
    oMusic_LookHiker_Ch3              = 0x346b,
    oMusic_LookHiker_Ch4              = 0x3494,
    oMusic_LookRocket                 = 0x34a2,
    oMusic_LookRocket_Ch1             = 0x34ae,
    oMusic_LookRocket_Ch2             = 0x3514,
    oMusic_LookRocket_Ch3             = 0x3597,
    oMusic_LookRocket_Ch4             = 0x3638,
    oMusic_RocketTheme                = 0x366d,
    oMusic_RocketTheme_Ch1            = 0x3679,
    oMusic_RocketTheme_Ch2            = 0x373e,
    oMusic_RocketTheme_Ch3            = 0x3826,
    oMusic_RocketTheme_Ch4            = 0x38be,
    oMusic_MainMenu                   = 0x38fd,
    oMusic_MainMenu_Ch1               = 0x3909,
    oMusic_MainMenu_Ch2               = 0x3940,
    oMusic_MainMenu_Ch3               = 0x3969,
    oMusic_MainMenu_Ch4               = 0x3996,
    oMusic_LookKimonoGirl             = 0x39b8,
    oMusic_LookKimonoGirl_Ch1         = 0x39c2,
    oMusic_LookKimonoGirl_Ch2         = 0x3a55,
    oMusic_LookKimonoGirl_Ch3         = 0x3ad4,
    oMusic_PokeFluteChannel           = 0x3b13,
    oMusic_PokeFluteChannel_Ch1       = 0x3b1c,
    oMusic_PokeFluteChannel_Ch2       = 0x3b68,
    oMusic_PokeFluteChannel_Ch3       = 0x3bd5,
    oMusic_BugCatchingContest         = 0x3c16,
    oMusic_BugCatchingContest_Ch1     = 0x3c22,
    oMusic_BugCatchingContest_Ch2     = 0x3cf4,
    oMusic_BugCatchingContest_Ch3     = 0x3db7,
    oMusic_BugCatchingContest_Ch4     = 0x3e9a,
};
