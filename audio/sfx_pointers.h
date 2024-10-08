#include "sfx.h"
#include "sfx_crystal.h"
#include "load.h"

static const struct BankAddr SFX[] = {
// entries correspond to SFX_* constants
    // table_width 3, SFX
    {AUDIO_BANK_SFX, oSfx_DexFanfare5079},
    {AUDIO_BANK_SFX, oSfx_Item},
    {AUDIO_BANK_SFX, oSfx_CaughtMon},
    {AUDIO_BANK_SFX, oSfx_PokeballsPlacedOnTable},
    {AUDIO_BANK_SFX, oSfx_Potion},
    {AUDIO_BANK_SFX, oSfx_FullHeal},
    {AUDIO_BANK_SFX, oSfx_Menu},
    {AUDIO_BANK_SFX, oSfx_ReadText},
    {AUDIO_BANK_SFX, oSfx_ReadText2},
    {AUDIO_BANK_SFX, oSfx_DexFanfare2049},
    {AUDIO_BANK_SFX, oSfx_DexFanfare80109},
    {AUDIO_BANK_SFX, oSfx_Poison},
    {AUDIO_BANK_SFX, oSfx_GotSafariBalls},
    {AUDIO_BANK_SFX, oSfx_BootPc},
    {AUDIO_BANK_SFX, oSfx_ShutDownPc},
    {AUDIO_BANK_SFX, oSfx_ChoosePcOption},
    {AUDIO_BANK_SFX, oSfx_EscapeRope},
    {AUDIO_BANK_SFX, oSfx_PushButton},
    {AUDIO_BANK_SFX, oSfx_SecondPartOfItemfinder},
    {AUDIO_BANK_SFX, oSfx_WarpTo},
    {AUDIO_BANK_SFX, oSfx_WarpFrom},
    {AUDIO_BANK_SFX, oSfx_ChangeDexMode},
    {AUDIO_BANK_SFX, oSfx_JumpOverLedge},
    {AUDIO_BANK_SFX, oSfx_GrassRustle},
    {AUDIO_BANK_SFX, oSfx_Fly},
    {AUDIO_BANK_SFX, oSfx_Wrong},
    {AUDIO_BANK_SFX, oSfx_Squeak},
    {AUDIO_BANK_SFX, oSfx_Strength},
    {AUDIO_BANK_SFX, oSfx_Boat},
    {AUDIO_BANK_SFX, oSfx_WallOpen},
    {AUDIO_BANK_SFX, oSfx_PlacePuzzlePieceDown},
    {AUDIO_BANK_SFX, oSfx_EnterDoor},
    {AUDIO_BANK_SFX, oSfx_SwitchPokemon},
    {AUDIO_BANK_SFX, oSfx_Tally},
    {AUDIO_BANK_SFX, oSfx_Transaction},
    {AUDIO_BANK_SFX, oSfx_ExitBuilding},
    {AUDIO_BANK_SFX, oSfx_Bump},
    {AUDIO_BANK_SFX, oSfx_Save},
    {AUDIO_BANK_SFX, oSfx_Pokeflute},
    {AUDIO_BANK_SFX, oSfx_ElevatorEnd},
    {AUDIO_BANK_SFX, oSfx_ThrowBall},
    {AUDIO_BANK_SFX, oSfx_BallPoof},
    {AUDIO_BANK_SFX, oSfx_Unknown3A},
    {AUDIO_BANK_SFX, oSfx_Run},
    {AUDIO_BANK_SFX, oSfx_SlotMachineStart},
    {AUDIO_BANK_SFX, oSfx_Fanfare},
    {AUDIO_BANK_SFX, oSfx_Peck},
    {AUDIO_BANK_SFX, oSfx_Kinesis},
    {AUDIO_BANK_SFX, oSfx_Lick},
    {AUDIO_BANK_SFX, oSfx_Pound},
    {AUDIO_BANK_SFX, oSfx_MovePuzzlePiece},
    {AUDIO_BANK_SFX, oSfx_CometPunch},
    {AUDIO_BANK_SFX, oSfx_MegaPunch},
    {AUDIO_BANK_SFX, oSfx_Scratch},
    {AUDIO_BANK_SFX, oSfx_Vicegrip},
    {AUDIO_BANK_SFX, oSfx_RazorWind},
    {AUDIO_BANK_SFX, oSfx_Cut},
    {AUDIO_BANK_SFX, oSfx_WingAttack},
    {AUDIO_BANK_SFX, oSfx_Whirlwind},
    {AUDIO_BANK_SFX, oSfx_Bind},
    {AUDIO_BANK_SFX, oSfx_VineWhip},
    {AUDIO_BANK_SFX, oSfx_DoubleKick},
    {AUDIO_BANK_SFX, oSfx_MegaKick},
    {AUDIO_BANK_SFX, oSfx_Headbutt},
    {AUDIO_BANK_SFX, oSfx_HornAttack},
    {AUDIO_BANK_SFX, oSfx_Tackle},
    {AUDIO_BANK_SFX, oSfx_PoisonSting},
    {AUDIO_BANK_SFX, oSfx_Powder},
    {AUDIO_BANK_SFX, oSfx_Doubleslap},
    {AUDIO_BANK_SFX, oSfx_Bite},
    {AUDIO_BANK_SFX, oSfx_JumpKick},
    {AUDIO_BANK_SFX, oSfx_Stomp},
    {AUDIO_BANK_SFX, oSfx_TailWhip},
    {AUDIO_BANK_SFX, oSfx_KarateChop},
    {AUDIO_BANK_SFX, oSfx_Submission},
    {AUDIO_BANK_SFX, oSfx_WaterGun},
    {AUDIO_BANK_SFX, oSfx_SwordsDance},
    {AUDIO_BANK_SFX, oSfx_Thunder},
    {AUDIO_BANK_SFX, oSfx_Supersonic},
    {AUDIO_BANK_SFX, oSfx_Leer},
    {AUDIO_BANK_SFX, oSfx_Ember},
    {AUDIO_BANK_SFX, oSfx_Bubblebeam},
    {AUDIO_BANK_SFX, oSfx_HydroPump},
    {AUDIO_BANK_SFX, oSfx_Surf},
    {AUDIO_BANK_SFX, oSfx_Psybeam},
    {AUDIO_BANK_SFX, oSfx_Charge},
    {AUDIO_BANK_SFX, oSfx_Thundershock},
    {AUDIO_BANK_SFX, oSfx_Psychic},
    {AUDIO_BANK_SFX, oSfx_Screech},
    {AUDIO_BANK_SFX, oSfx_BoneClub},
    {AUDIO_BANK_SFX, oSfx_Sharpen},
    {AUDIO_BANK_SFX, oSfx_EggBomb},
    {AUDIO_BANK_SFX, oSfx_Sing},
    {AUDIO_BANK_SFX, oSfx_HyperBeam},
    {AUDIO_BANK_SFX, oSfx_Shine},
    {AUDIO_BANK_SFX, oSfx_Unknown5F},
    {AUDIO_BANK_SFX, oSfx_Unknown60},
    {AUDIO_BANK_SFX, oSfx_Unknown61},
    {AUDIO_BANK_SFX, oSfx_SwitchPockets},
    {AUDIO_BANK_SFX, oSfx_Unknown63},
    {AUDIO_BANK_SFX, oSfx_Burn},
    {AUDIO_BANK_SFX, oSfx_TitleScreenEntrance},
    {AUDIO_BANK_SFX, oSfx_Unknown66},
    {AUDIO_BANK_SFX, oSfx_GetCoinFromSlots},
    {AUDIO_BANK_SFX, oSfx_PayDay},
    {AUDIO_BANK_SFX, oSfx_Metronome},
    {AUDIO_BANK_SFX, oSfx_Call},
    {AUDIO_BANK_SFX, oSfx_HangUp},
    {AUDIO_BANK_SFX, oSfx_NoSignal},
    {AUDIO_BANK_SFX, oSfx_Sandstorm},
    {AUDIO_BANK_SFX, oSfx_Elevator},
    {AUDIO_BANK_SFX, oSfx_Protect},
    {AUDIO_BANK_SFX, oSfx_Sketch},
    {AUDIO_BANK_SFX, oSfx_RainDance},
    {AUDIO_BANK_SFX, oSfx_Aeroblast},
    {AUDIO_BANK_SFX, oSfx_Spark},
    {AUDIO_BANK_SFX, oSfx_Curse},
    {AUDIO_BANK_SFX, oSfx_Rage},
    {AUDIO_BANK_SFX, oSfx_Thief},
    {AUDIO_BANK_SFX, oSfx_Thief2},
    {AUDIO_BANK_SFX, oSfx_SpiderWeb},
    {AUDIO_BANK_SFX, oSfx_MindReader},
    {AUDIO_BANK_SFX, oSfx_Nightmare},
    {AUDIO_BANK_SFX, oSfx_Snore},
    {AUDIO_BANK_SFX, oSfx_SweetKiss},
    {AUDIO_BANK_SFX, oSfx_SweetKiss2},
    {AUDIO_BANK_SFX, oSfx_BellyDrum},
    {AUDIO_BANK_SFX, oSfx_Unknown7F},
    {AUDIO_BANK_SFX, oSfx_SludgeBomb},
    {AUDIO_BANK_SFX, oSfx_Foresight},
    {AUDIO_BANK_SFX, oSfx_Spite},
    {AUDIO_BANK_SFX, oSfx_Outrage},
    {AUDIO_BANK_SFX, oSfx_PerishSong},
    {AUDIO_BANK_SFX, oSfx_GigaDrain},
    {AUDIO_BANK_SFX, oSfx_Attract},
    {AUDIO_BANK_SFX, oSfx_Kinesis2},
    {AUDIO_BANK_SFX, oSfx_ZapCannon},
    {AUDIO_BANK_SFX, oSfx_MeanLook},
    {AUDIO_BANK_SFX, oSfx_HealBell},
    {AUDIO_BANK_SFX, oSfx_Return},
    {AUDIO_BANK_SFX, oSfx_ExpBar},
    {AUDIO_BANK_SFX, oSfx_MilkDrink},
    {AUDIO_BANK_SFX, oSfx_Present},
    {AUDIO_BANK_SFX, oSfx_MorningSun},
    {AUDIO_BANK_SFX, oSfx_LevelUp},
    {AUDIO_BANK_SFX, oSfx_KeyItem},
    {AUDIO_BANK_SFX, oSfx_Fanfare2},
    {AUDIO_BANK_SFX, oSfx_RegisterPhoneNumber},
    {AUDIO_BANK_SFX, oSfx_3rdPlace},
    {AUDIO_BANK_SFX, oSfx_GetEgg},
    {AUDIO_BANK_SFX, oSfx_GetEgg},
    {AUDIO_BANK_SFX, oSfx_MoveDeleted},
    {AUDIO_BANK_SFX, oSfx_2ndPlace},
    {AUDIO_BANK_SFX, oSfx_1stPlace},
    {AUDIO_BANK_SFX, oSfx_ChooseACard},
    {AUDIO_BANK_SFX, oSfx_GetTm},
    {AUDIO_BANK_SFX, oSfx_GetBadge},
    {AUDIO_BANK_SFX, oSfx_QuitSlots},
    {AUDIO_BANK_SFX, oSfx_EggCrack},
    {AUDIO_BANK_SFX, oSfx_DexFanfareLessThan20},
    {AUDIO_BANK_SFX, oSfx_DexFanfare140169},
    {AUDIO_BANK_SFX, oSfx_DexFanfare170199},
    {AUDIO_BANK_SFX, oSfx_DexFanfare200229},
    {AUDIO_BANK_SFX, oSfx_DexFanfare230Plus},
    {AUDIO_BANK_SFX, oSfx_Evolved},
    {AUDIO_BANK_SFX, oSfx_MasterBall},
    {AUDIO_BANK_SFX, oSfx_EggHatch},
    {AUDIO_BANK_SFX, oSfx_GsIntroCharizardFireball},
    {AUDIO_BANK_SFX, oSfx_GsIntroPokemonAppears},
    {AUDIO_BANK_SFX, oSfx_Flash},
    {AUDIO_BANK_SFX, oSfx_GameFreakLogoGs},
    {AUDIO_BANK_SFX, oSfx_NotVeryEffective},
    {AUDIO_BANK_SFX, oSfx_Damage},
    {AUDIO_BANK_SFX, oSfx_SuperEffective},
    {AUDIO_BANK_SFX, oSfx_BallBounce},
    {AUDIO_BANK_SFX, oSfx_Moonlight},
    {AUDIO_BANK_SFX, oSfx_Encore},
    {AUDIO_BANK_SFX, oSfx_BeatUp},
    {AUDIO_BANK_SFX, oSfx_BatonPass},
    {AUDIO_BANK_SFX, oSfx_BallWobble},
    {AUDIO_BANK_SFX, oSfx_SweetScent},
    {AUDIO_BANK_SFX, oSfx_SweetScent2},
    {AUDIO_BANK_SFX, oSfx_HitEndOfExpBar},
    {AUDIO_BANK_SFX, oSfx_GiveTrademon},
    {AUDIO_BANK_SFX, oSfx_GetTrademon},
    {AUDIO_BANK_SFX, oSfx_TrainArrived},
    {AUDIO_BANK_SFX, oSfx_StopSlot},
    {AUDIO_BANK_SFX, oSfx_2Boops},
// new to Crystal
    {AUDIO_BANK_SFX, oSfx_GlassTing},
    {AUDIO_BANK_SFX, oSfx_GlassTing2},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_IntroUnown1},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_IntroUnown2},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_IntroUnown3},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_DittoPopUp},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_DittoTransform},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_IntroSuicune1},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_IntroPichu},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_IntroSuicune2},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_IntroSuicune3},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_DittoBounce},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_IntroSuicune4},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_GameFreakPresents},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_Tingle},
    {AUDIO_BANK_SFX, oSfx_IntroWhoosh},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_TwoPcBeeps},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_4NoteDitty},
    {AUDIO_BANK_SFX_CRYSTAL, oSfx_Twinkle},
};
static_assert(lengthof(SFX) == NUM_SFX, "");
