#include "../../constants.h"
#include "../../util/variadic_macros.h"
#define frame_value_1(_0) (_0)
#define frame_value_2(_0, _1) (_0 | (1 << (_1 + 1)))
#define frame_value_3(_0, _1, _2) (_0 | (1 << (_1 + 1)) | (1 << (_2 + 1)))
#define frame_value_(...) CPPX_INVOKE( CPPX_CONCAT ( frame_value_, PP_NARG(__VA_ARGS__) ) , (__VA_ARGS__) )
#define frame(_0, ...) frame2(_0, frame_value_(__VA_ARGS__))
#define endanim endanim_command
#define delanim delanim_command
#undef dorestart
#define dorestart dorestart_command

static const uint8_t Frameset_00[] = {
    frame(SPRITE_ANIM_OAMSET_RED_WALK_1, 32),
    endanim
};

static const uint8_t Frameset_PartyMon[] = {
    frame(SPRITE_ANIM_OAMSET_RED_WALK_1,  8),
    frame(SPRITE_ANIM_OAMSET_RED_WALK_2,  8),
    dorestart
};

static const uint8_t Frameset_PartyMonWithMail[] = {
    frame(SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_1,  8),
    frame(SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_2,  8),
    dorestart
};

static const uint8_t Frameset_PartyMonWithItem[] = {
	frame(SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_1,  8),
	frame(SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_2,  8),
	dorestart
};

static const uint8_t Frameset_PartyMonFast[] = {
    frame(SPRITE_ANIM_OAMSET_RED_WALK_1,  4),
    frame(SPRITE_ANIM_OAMSET_RED_WALK_2,  4),
    dorestart
};

static const uint8_t Frameset_PartyMonWithMailFast[] = {
    frame(SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_1,  4),
    frame(SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_2,  4),
    dorestart
};

static const uint8_t Frameset_PartyMonWithItemFast[] = {
    frame(SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_1,  4),
    frame(SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_2,  4),
    dorestart
};

static const uint8_t Frameset_RedWalk[] = {
    frame(SPRITE_ANIM_OAMSET_RED_WALK_1,  8),
    frame(SPRITE_ANIM_OAMSET_RED_WALK_2,  8),
    frame(SPRITE_ANIM_OAMSET_RED_WALK_1,  8),
    frame(SPRITE_ANIM_OAMSET_RED_WALK_2,  8, OAM_X_FLIP),
    dorestart
};

static const uint8_t Frameset_BlueWalk[] = {
    frame(SPRITE_ANIM_OAMSET_BLUE_WALK_1,  8),
    frame(SPRITE_ANIM_OAMSET_BLUE_WALK_2,  8),
    frame(SPRITE_ANIM_OAMSET_BLUE_WALK_1,  8),
    frame(SPRITE_ANIM_OAMSET_BLUE_WALK_2,  8, OAM_X_FLIP),
    dorestart
};

static const uint8_t Frameset_MagnetTrainBlue[] = {
	frame(SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_1,  8),
	frame(SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_2,  8),
	frame(SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_1,  8),
	frame(SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_2,  8, OAM_X_FLIP),
	dorestart
};

static const uint8_t Frameset_GSTitleTrail[] = {
	frame(SPRITE_ANIM_OAMSET_GS_TITLE_TRAIL_1,  1),
	frame(SPRITE_ANIM_OAMSET_GS_TITLE_TRAIL_2,  1),
	dorestart
};

static const uint8_t Frameset_TextEntryCursor[] = {
	frame(SPRITE_ANIM_OAMSET_TEXT_ENTRY_CURSOR,  1),
	dowait(1),
	dorestart
};

static const uint8_t Frameset_TextEntryCursorBig[] = {
	frame(SPRITE_ANIM_OAMSET_TEXT_ENTRY_CURSOR_BIG,  1),
	dowait(1),
	dorestart
};

static const uint8_t Frameset_GameFreakLogo[] = {
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_1,  12),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_2,   1),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_3,   1),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_2,   4),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_1,  12),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_2,  12),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_3,   4),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_4,  32),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_5,   3),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_6,   3),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_7,   4),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_8,   4),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_9,   4),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_10, 10),
    frame(SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_11,  7),
    endanim
};

static const uint8_t Frameset_GSGameFreakLogoStar[] = { // 
	frame(SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_STAR,  3),
	frame(SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_STAR,  3, OAM_Y_FLIP),
	dorestart
};

static const uint8_t Frameset_GSGameFreakLogoSparkle[] = {
    frame(SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_1,  2),
    frame(SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_2,  2),
    frame(SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_3,  2),
    frame(SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_2,  2),
    dorestart
};

static const uint8_t Frameset_SlotsGolem[] = { // 
	frame(SPRITE_ANIM_OAMSET_SLOTS_GOLEM_1,  7),
	frame(SPRITE_ANIM_OAMSET_SLOTS_GOLEM_2,  7),
	frame(SPRITE_ANIM_OAMSET_SLOTS_GOLEM_1,  7, OAM_Y_FLIP),
	frame(SPRITE_ANIM_OAMSET_SLOTS_GOLEM_2,  7, OAM_X_FLIP),
	dorestart
};

static const uint8_t Frameset_SlotsChansey[] = { // 
	frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_1,  7),
	frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_2,  7),
	frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_1,  7),
	frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_3,  7),
	dorestart
};

static const uint8_t Frameset_SlotsChansey2[] = {
    frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_1,  7),
    frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_4,  7),
    frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_5,  7),
    frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_4,  7),
    frame(SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_1,  7),
    endanim
};

static const uint8_t Frameset_SlotsEgg[] = {
    frame(SPRITE_ANIM_OAMSET_SLOTS_EGG, 20),
    endanim
};

static const uint8_t Frameset_StillCursor[] = {
    frame(SPRITE_ANIM_OAMSET_STILL_CURSOR, 32),
    endanim
};

static const uint8_t Frameset_TradePokeBall[] = {
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1, 32),
    endanim
};

static const uint8_t Frameset_TradePokeBallWobble[] = { // 
	frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
	frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3),
	frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
	frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3, OAM_X_FLIP),
	dorestart
};

static const uint8_t Frameset_TradePoof[] = {
	frame(SPRITE_ANIM_OAMSET_TRADE_POOF_1,  4),
	frame(SPRITE_ANIM_OAMSET_TRADE_POOF_2,  4),
	frame(SPRITE_ANIM_OAMSET_TRADE_POOF_3,  4),
	delanim
};

static const uint8_t Frameset_TradeTubeBulge[] = {
	frame(SPRITE_ANIM_OAMSET_TRADE_TUBE_BULGE_1,  3),
	frame(SPRITE_ANIM_OAMSET_TRADE_TUBE_BULGE_2,  3),
	dorestart
};

static const uint8_t Frameset_TrademonIcon[] = {
	frame(SPRITE_ANIM_OAMSET_TRADEMON_ICON_1,  7),
	frame(SPRITE_ANIM_OAMSET_TRADEMON_ICON_2,  7),
	dorestart
};

static const uint8_t Frameset_TrademonBubble[] = {
	frame(SPRITE_ANIM_OAMSET_TRADEMON_BUBBLE, 32),
	endanim
};

static const uint8_t Frameset_EvolutionBallOfLight[] = {
	frame(SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_2,  2),
	frame(SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_1,  2),
	frame(SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_2,  2),
	endanim
};

static const uint8_t Frameset_RadioTuningKnob[] = {
	frame(SPRITE_ANIM_OAMSET_RADIO_TUNING_KNOB, 32),
	endanim
};

static const uint8_t Frameset_MagnetTrainRed[] = { // 
	frame(SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_1,  8),
	frame(SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_2,  8),
	frame(SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_1,  8),
	frame(SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_2,  8, OAM_X_FLIP),
	dorestart
};

// static const uint8_t Frameset_Unknown1[] = { //  ; unreferenced
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_43,  8),
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_44,  8),
// 	dorestart
// };

// static const uint8_t Frameset_Unknown2[] = { //  ; unreferenced
//     frame(SPRITE_ANIM_OAMSET_UNUSED_45,  8),
//     frame(SPRITE_ANIM_OAMSET_UNUSED_46,  8),
//     dorestart
// };

// static const uint8_t Frameset_Unknown3[] = { //  ; unreferenced
//     frame(SPRITE_ANIM_OAMSET_UNUSED_47,  8),
//     frame(SPRITE_ANIM_OAMSET_UNUSED_48,  8),
//     dorestart
// };

// static const uint8_t Frameset_Unknown4[] = { //  ; unreferenced
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_49,  1),
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_49,  1, OAM_X_FLIP),
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_49,  1, OAM_X_FLIP, OAM_Y_FLIP),
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_49,  1, OAM_Y_FLIP),
// 	dorestart
// };

// static const uint8_t Frameset_Unknown5[] = { //  ; unreferenced
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_4A, 32),
// 	endanim
// };

// static const uint8_t Frameset_Unknown6[] = { //  ; unreferenced
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_4B, 32),
// 	endanim
// };

// static const uint8_t Frameset_Unknown7[] = { //  ; unreferenced
// 	frame(SPRITE_ANIM_OAMSET_UNUSED_4C, 32),
// 	endanim
// };

// static const uint8_t Frameset_Unknown8[] = { //  ; unreferenced
//     frame(SPRITE_ANIM_OAMSET_UNUSED_4D, 32),
//     endanim
// };

// static const uint8_t Frameset_Unknown9[] = { // unreferenced
//     frame(SPRITE_ANIM_OAMSET_UNUSED_4E,  3),
//     dowait(3),
//     dorestart
// };

static const uint8_t Frameset_Unused1C[] = {
    dowait(32),
    endanim
};

static const uint8_t Frameset_Leaf[] = { // 
	frame(SPRITE_ANIM_OAMSET_LEAF, 32),
	endanim
};

static const uint8_t Frameset_CutTree[] = {
	frame(SPRITE_ANIM_OAMSET_TREE_1,      2),
	frame(SPRITE_ANIM_OAMSET_CUT_TREE_2, 16),
	dowait(1),
	frame(SPRITE_ANIM_OAMSET_CUT_TREE_3,  1),
	dowait(1),
	frame(SPRITE_ANIM_OAMSET_CUT_TREE_4,  1),
	delanim
};

static const uint8_t Frameset_EggCrack[] = {
	frame(SPRITE_ANIM_OAMSET_EGG_CRACK, 32),
	endanim
};

static const uint8_t Frameset_EggHatch1[] = {
	frame(SPRITE_ANIM_OAMSET_EGG_HATCH, 32),
	endanim
};

static const uint8_t Frameset_EggHatch2[] = {
	frame(SPRITE_ANIM_OAMSET_EGG_HATCH, 32, OAM_X_FLIP),
	endanim
};

static const uint8_t Frameset_EggHatch3[] = {
	frame(SPRITE_ANIM_OAMSET_EGG_HATCH, 32, OAM_Y_FLIP),
	endanim
};

static const uint8_t Frameset_EggHatch4[] = {
	frame(SPRITE_ANIM_OAMSET_EGG_HATCH, 32, OAM_X_FLIP, OAM_Y_FLIP),
	endanim
};

static const uint8_t Frameset_GSIntroHoOhLugia[] = {
	frame(SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_1, 10),
	frame(SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_2,  9),
	frame(SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_3, 10),
	frame(SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_4, 10),
	frame(SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_3,  9),
	frame(SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_5, 10),
	dorestart
};

static const uint8_t Frameset_HeadbuttTree[] = {
    frame(SPRITE_ANIM_OAMSET_TREE_1,           2),
    frame(SPRITE_ANIM_OAMSET_HEADBUTT_TREE_2,  2),
    frame(SPRITE_ANIM_OAMSET_TREE_1,           2),
    frame(SPRITE_ANIM_OAMSET_HEADBUTT_TREE_2,  2, OAM_X_FLIP),
    dorestart
};

static const uint8_t Frameset_EZChatCursor1[] = {
    frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_1,  2),
    endanim
};

static const uint8_t Frameset_EZChatCursor2[] = {
    frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_2,  2),
    endanim
};

static const uint8_t Frameset_EZChatCursor3[] = {
    frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_3,  2),
    endanim
};

static const uint8_t Frameset_EZChatCursor4[] = {
    frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_4,  2),
    endanim
};

static const uint8_t Frameset_EZChatCursor5[] = {
    frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_5,  2),
    endanim
};

static const uint8_t Frameset_EZChatCursor6[] = {
    frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_6,  2),
    endanim
};

static const uint8_t Frameset_EZChatCursor7[] = {
    frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_7,  2),
    endanim
};

static const uint8_t Frameset_EZChatCursor8[] = {
	frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_8,  2),
	endanim
};

static const uint8_t Frameset_EZChatCursor9[] = {
	frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_9,  2),
	endanim
};

static const uint8_t Frameset_EZChatCursor10[] = {
	frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_10,  2),
	endanim
};

static const uint8_t Frameset_EZChatCursorCustomBox[] = {
	frame(SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_CUSTOM_BOX,  2),
	endanim
};

static const uint8_t Frameset_MobileTradeSentBall[] = {
    frame(SPRITE_ANIM_OAMSET_TRADE_POOF_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POOF_2,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POOF_3,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3, OAM_X_FLIP),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3, OAM_X_FLIP),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3, OAM_X_FLIP),
    endanim
};

static const uint8_t Frameset_MobileTradeOTBall[] = {
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3, OAM_X_FLIP),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3, OAM_X_FLIP),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,  3, OAM_X_FLIP),
    frame(SPRITE_ANIM_OAMSET_TRADE_POOF_1,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POOF_2,  3),
    frame(SPRITE_ANIM_OAMSET_TRADE_POOF_3,  3),
    delanim
};

static const uint8_t Frameset_MobileTradeCableBulge[] = {
    frame(SPRITE_ANIM_OAMSET_MOBILE_TRADE_CABLE_BULGE_1,  3),
    frame(SPRITE_ANIM_OAMSET_MOBILE_TRADE_CABLE_BULGE_2,  3),
    dorestart
};

static const uint8_t Frameset_MobileTradeSentPulse[] = {
    frame(SPRITE_ANIM_OAMSET_MOBILE_TRADE_SENT_PULSE,  3),
    endanim
};

static const uint8_t Frameset_MobileTradeOTPulse[] = {
    frame(SPRITE_ANIM_OAMSET_MOBILE_TRADE_OT_PULSE,  3),
    endanim
};

static const uint8_t Frameset_MobileTradePing[] = {
    frame(SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_1,  2),
    frame(SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_2,  2),
    frame(SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_3,  2),
    delanim
};

static const uint8_t Frameset_IntroSuicune[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_SUICUNE_1,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_SUICUNE_2,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_SUICUNE_3,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_SUICUNE_4,  3),
    dorestart
};

static const uint8_t Frameset_IntroSuicune2[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_SUICUNE_4,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_SUICUNE_1,  7),
    endanim
};

static const uint8_t Frameset_IntroPichu[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_PICHU_1, 32),
    frame(SPRITE_ANIM_OAMSET_INTRO_PICHU_2,  7),
    frame(SPRITE_ANIM_OAMSET_INTRO_PICHU_3,  7),
    endanim
};

static const uint8_t Frameset_IntroWooper[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_WOOPER,  3),
    endanim
};

static const uint8_t Frameset_IntroUnown1[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_1,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_2,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_3,  7),
    delanim
};

static const uint8_t Frameset_IntroUnown2[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_1,  3, OAM_X_FLIP),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_2,  3, OAM_X_FLIP),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_3,  7, OAM_X_FLIP),
    delanim
};

static const uint8_t Frameset_IntroUnown3[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_1,  3, OAM_Y_FLIP),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_2,  3, OAM_Y_FLIP),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_3,  7, OAM_Y_FLIP),
    delanim
};

static const uint8_t Frameset_IntroUnown4[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_1,  3, OAM_X_FLIP, OAM_Y_FLIP),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_2,  3, OAM_X_FLIP, OAM_Y_FLIP),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_3,  7, OAM_X_FLIP, OAM_Y_FLIP),
    delanim
};

static const uint8_t Frameset_IntroUnownF2[] = {
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_1,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_2,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_3,  3),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_4,  7),
    frame(SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_5,  7),
    endanim
};

static const uint8_t Frameset_IntroSuicuneAway[] = {
	frame(SPRITE_ANIM_OAMSET_INTRO_SUICUNE_AWAY,  3),
	endanim
};

static const uint8_t Frameset_IntroUnownF[] = {
	dowait(0),
	endanim
};

static const uint8_t Frameset_CelebiLeft[] = {
	frame(SPRITE_ANIM_OAMSET_CELEBI_1,  8),
	frame(SPRITE_ANIM_OAMSET_CELEBI_2,  8),
	endanim
};

static const uint8_t Frameset_CelebiRight[] = {
	frame(SPRITE_ANIM_OAMSET_CELEBI_1,  8, OAM_X_FLIP),
	frame(SPRITE_ANIM_OAMSET_CELEBI_2,  8, OAM_X_FLIP),
	endanim
};

const uint8_t* const SpriteAnimFrameData[] = {
// entries correspond to SPRITE_ANIM_FRAMESET_* constants (see constants/sprite_anim_constants.asm)
    // table_width 2, SpriteAnimFrameData
    [SPRITE_ANIM_FRAMESET_00]                           = Frameset_00,
    [SPRITE_ANIM_FRAMESET_PARTY_MON]                    = Frameset_PartyMon,
    [SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_MAIL]          = Frameset_PartyMonWithMail,
    [SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_ITEM]          = Frameset_PartyMonWithItem,
    [SPRITE_ANIM_FRAMESET_PARTY_MON_FAST]               = Frameset_PartyMonFast,
    [SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_MAIL_FAST]     = Frameset_PartyMonWithMailFast,
    [SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_ITEM_FAST]     = Frameset_PartyMonWithItemFast,
    [SPRITE_ANIM_FRAMESET_GS_TITLE_TRAIL]               = Frameset_GSTitleTrail,
    [SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR]            = Frameset_TextEntryCursor,
    [SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR_BIG]        = Frameset_TextEntryCursorBig,
    [SPRITE_ANIM_FRAMESET_GAMEFREAK_LOGO]               = Frameset_GameFreakLogo,
    [SPRITE_ANIM_FRAMESET_GS_GAMEFREAK_LOGO_STAR]       = Frameset_GSGameFreakLogoStar,
    [SPRITE_ANIM_FRAMESET_GS_GAMEFREAK_LOGO_SPARKLE]    = Frameset_GSGameFreakLogoSparkle,
    [SPRITE_ANIM_FRAMESET_SLOTS_GOLEM]                  = Frameset_SlotsGolem,
    [SPRITE_ANIM_FRAMESET_SLOTS_CHANSEY]                = Frameset_SlotsChansey,
    [SPRITE_ANIM_FRAMESET_SLOTS_CHANSEY_2]              = Frameset_SlotsChansey2,
    [SPRITE_ANIM_FRAMESET_SLOTS_EGG]                    = Frameset_SlotsEgg,
    [SPRITE_ANIM_FRAMESET_RED_WALK]                     = Frameset_RedWalk,
    [SPRITE_ANIM_FRAMESET_STILL_CURSOR]                 = Frameset_StillCursor,
    [SPRITE_ANIM_FRAMESET_TRADE_POKE_BALL]              = Frameset_TradePokeBall,
    [SPRITE_ANIM_FRAMESET_TRADE_POKE_BALL_WOBBLE]       = Frameset_TradePokeBallWobble,
    [SPRITE_ANIM_FRAMESET_TRADE_POOF]                   = Frameset_TradePoof,
    [SPRITE_ANIM_FRAMESET_TRADE_TUBE_BULGE]             = Frameset_TradeTubeBulge,
    [SPRITE_ANIM_FRAMESET_TRADEMON_ICON]                = Frameset_TrademonIcon,
    [SPRITE_ANIM_FRAMESET_TRADEMON_BUBBLE]              = Frameset_TrademonBubble,
    [SPRITE_ANIM_FRAMESET_EVOLUTION_BALL_OF_LIGHT]      = Frameset_EvolutionBallOfLight,
    [SPRITE_ANIM_FRAMESET_RADIO_TUNING_KNOB]            = Frameset_RadioTuningKnob,
    [SPRITE_ANIM_FRAMESET_MAGNET_TRAIN_RED]             = Frameset_MagnetTrainRed,
    [SPRITE_ANIM_FRAMESET_UNUSED_1C]                    = Frameset_Unused1C,
    [SPRITE_ANIM_FRAMESET_LEAF]                         = Frameset_Leaf,
    [SPRITE_ANIM_FRAMESET_CUT_TREE]                     = Frameset_CutTree,
    [SPRITE_ANIM_FRAMESET_EGG_CRACK]                    = Frameset_EggCrack,
    [SPRITE_ANIM_FRAMESET_EGG_HATCH_1]                  = Frameset_EggHatch1,
    [SPRITE_ANIM_FRAMESET_EGG_HATCH_2]                  = Frameset_EggHatch2,
    [SPRITE_ANIM_FRAMESET_EGG_HATCH_3]                  = Frameset_EggHatch3,
    [SPRITE_ANIM_FRAMESET_EGG_HATCH_4]                  = Frameset_EggHatch4,
    [SPRITE_ANIM_FRAMESET_GS_INTRO_HO_OH_LUGIA]         = Frameset_GSIntroHoOhLugia,
    [SPRITE_ANIM_FRAMESET_HEADBUTT]                     = Frameset_HeadbuttTree,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1]              = Frameset_EZChatCursor1,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2]              = Frameset_EZChatCursor2,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3]              = Frameset_EZChatCursor3,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_4]              = Frameset_EZChatCursor4,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_5]              = Frameset_EZChatCursor5,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_6]              = Frameset_EZChatCursor6,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_7]              = Frameset_EZChatCursor7,
    [SPRITE_ANIM_FRAMESET_BLUE_WALK]                    = Frameset_BlueWalk,
    [SPRITE_ANIM_FRAMESET_MAGNET_TRAIN_BLUE]            = Frameset_MagnetTrainBlue,
    [SPRITE_ANIM_FRAMESET_MOBILE_TRADE_SENT_BALL]       = Frameset_MobileTradeSentBall,
    [SPRITE_ANIM_FRAMESET_MOBILE_TRADE_OT_BALL]         = Frameset_MobileTradeOTBall,
    [SPRITE_ANIM_FRAMESET_MOBILE_TRADE_CABLE_BULGE]     = Frameset_MobileTradeCableBulge,
    [SPRITE_ANIM_FRAMESET_MOBILE_TRADE_SENT_PULSE]      = Frameset_MobileTradeSentPulse,
    [SPRITE_ANIM_FRAMESET_MOBILE_TRADE_OT_PULSE]        = Frameset_MobileTradeOTPulse,
    [SPRITE_ANIM_FRAMESET_MOBILE_TRADE_PING]            = Frameset_MobileTradePing,
    [SPRITE_ANIM_FRAMESET_INTRO_SUICUNE]                = Frameset_IntroSuicune,
    [SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_2]              = Frameset_IntroSuicune2,
    [SPRITE_ANIM_FRAMESET_INTRO_PICHU]                  = Frameset_IntroPichu,
    [SPRITE_ANIM_FRAMESET_INTRO_WOOPER]                 = Frameset_IntroWooper,
    [SPRITE_ANIM_FRAMESET_INTRO_UNOWN_1]                = Frameset_IntroUnown1,
    [SPRITE_ANIM_FRAMESET_INTRO_UNOWN_2]                = Frameset_IntroUnown2,
    [SPRITE_ANIM_FRAMESET_INTRO_UNOWN_3]                = Frameset_IntroUnown3,
    [SPRITE_ANIM_FRAMESET_INTRO_UNOWN_4]                = Frameset_IntroUnown4,
    [SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F_2]              = Frameset_IntroUnownF2,
    [SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_AWAY]           = Frameset_IntroSuicuneAway,
    [SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F]                = Frameset_IntroUnownF,
    [SPRITE_ANIM_FRAMESET_CELEBI_LEFT]                  = Frameset_CelebiLeft,
    [SPRITE_ANIM_FRAMESET_CELEBI_RIGHT]                 = Frameset_CelebiRight,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_8]              = Frameset_EZChatCursor8,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_9]              = Frameset_EZChatCursor9,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_10]             = Frameset_EZChatCursor10,
    [SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_CUSTOM_BOX]     = Frameset_EZChatCursorCustomBox,
};
static_assert(lengthof(SpriteAnimFrameData) == NUM_SPRITE_ANIM_FRAMESETS, "");
