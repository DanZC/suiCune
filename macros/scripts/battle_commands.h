#pragma once

enum {
	checkturn_command = 1,           // 01
	checkobedience_command,          // 02
	usedmovetext_command,            // 03
	doturn_command,                  // 04
	critical_command,                // 05
	damagestats_command,             // 06
	stab_command,                    // 07
	damagevariation_command,         // 08
	checkhit_command,                // 09
	lowersub_command,                // 0a
	moveanimnosub_command,           // 0b
	raisesub_command,                // 0c
	failuretext_command,             // 0d
	applydamage_command,             // 0e
	criticaltext_command,            // 0f
	supereffectivetext_command,      // 10
	checkfaint_command,              // 11
	buildopponentrage_command,       // 12
	poisontarget_command,            // 13
	sleeptarget_command,             // 14
	draintarget_command,             // 15
	eatdream_command,                // 16
	burntarget_command,              // 17
	freezetarget_command,            // 18
	paralyzetarget_command,          // 19
	selfdestruct_command,            // 1a
	mirrormove_command,              // 1b
	statup_command,                  // 1c
	statdown_command,                // 1d
	payday_command,                  // 1e
	conversion_command,              // 1f
	resetstats_command,              // 20
	storeenergy_command,             // 21
	unleashenergy_command,           // 22
	forceswitch_command,             // 23
	endloop_command,                 // 24
	flinchtarget_command,            // 25
	ohko_command,                    // 26
	recoil_command,                  // 27
	mist_command,                    // 28
	focusenergy_command,             // 29
	confuse_command,                 // 2a
	confusetarget_command,           // 2b
	heal_command,                    // 2c
	transform_command,               // 2d
	screen_command,                  // 2e
	poison_command,                  // 2f
	paralyze_command,                // 30
	substitute_command,              // 31
	rechargenextturn_command,        // 32
	mimic_command,                   // 33
	metronome_command,               // 34
	leechseed_command,               // 35
	splash_command,                  // 36
	disable_command,                 // 37
	cleartext_command,               // 38
	charge_command,                  // 39
	checkcharge_command,             // 3a
	traptarget_command,              // 3b
	effect0x3c_command,              // 3c
	rampage_command,                 // 3d
	checkrampage_command,            // 3e
	constantdamage_command,          // 3f
	counter_command,                 // 40
	encore_command,                  // 41
	painsplit_command,               // 42
	snore_command,                   // 43
	conversion2_command,             // 44
	lockon_command,                  // 45
	sketch_command,                  // 46
	defrostopponent_command,         // 47
	sleeptalk_command,               // 48
	destinybond_command,             // 49
	spite_command,                   // 4a
	falseswipe_command,              // 4b
	healbell_command,                // 4c
	kingsrock_command,               // 4d
	triplekick_command,              // 4e
	kickcounter_command,             // 4f
	thief_command,                   // 50
	arenatrap_command,               // 51
	nightmare_command,               // 52
	defrost_command,                 // 53
	curse_command,                   // 54
	protect_command,                 // 55
	spikes_command,                  // 56
	foresight_command,               // 57
	perishsong_command,              // 58
	startsandstorm_command,          // 59
	endure_command,                  // 5a
	checkcurl_command,               // 5b
	rolloutpower_command,            // 5c
	effect0x5d_command,              // 5d
	furycutter_command,              // 5e
	attract_command,                 // 5f
	happinesspower_command,          // 60
	present_command,                 // 61
	damagecalc_command,              // 62
	frustrationpower_command,        // 63
	safeguard_command,               // 64
	checksafeguard_command,          // 65
	getmagnitude_command,            // 66
	batonpass_command,               // 67
	pursuit_command,                 // 68
	clearhazards_command,            // 69
	healmorn_command,                // 6a
	healday_command,                 // 6b
	healnite_command,                // 6c
	hiddenpower_command,             // 6d
	startrain_command,               // 6e
	startsun_command,                // 6f
	attackup_command,                // 70
	defenseup_command,               // 71
	speedup_command,                 // 72
	specialattackup_command,         // 73
	specialdefenseup_command,        // 74
	accuracyup_command,              // 75
	evasionup_command,               // 76
	attackup2_command,               // 77
	defenseup2_command,              // 78
	speedup2_command,                // 79
	specialattackup2_command,        // 7a
	specialdefenseup2_command,       // 7b
	accuracyup2_command,             // 7c
	evasionup2_command,              // 7d
	attackdown_command,              // 7e
	defensedown_command,             // 7f
	speeddown_command,               // 80
	specialattackdown_command,       // 81
	specialdefensedown_command,      // 82
	accuracydown_command,            // 83
	evasiondown_command,             // 84
	attackdown2_command,             // 85
	defensedown2_command,            // 86
	speeddown2_command,              // 87
	specialattackdown2_command,      // 88
	specialdefensedown2_command,     // 89
	accuracydown2_command,           // 8a
	evasiondown2_command,            // 8b
	statupmessage_command,           // 8c
	statdownmessage_command,         // 8d
	statupfailtext_command,          // 8e
	statdownfailtext_command,        // 8f
	effectchance_command,            // 90
	statdownanim_command,            // 91
	statupanim_command,              // 92
	switchturn_command,              // 93
	fakeout_command,                 // 94
	bellydrum_command,               // 95
	psychup_command,                 // 96
	rage_command,                    // 97
	doubleflyingdamage_command,      // 98
	doubleundergrounddamage_command, // 99
	mirrorcoat_command,              // 9a
	checkfuturesight_command,        // 9b
	futuresight_command,             // 9c
	doubleminimizedamage_command,    // 9d
	skipsuncharge_command,           // 9e
	thunderaccuracy_command,         // 9f
	teleport_command,                // a0
	beatup_command,                  // a1
	ragedamage_command,              // a2
	resettypematchup_command,        // a3
	allstatsup_command,              // a4
	bidefailtext_command,            // a5
	raisesubnoanim_command,          // a6
	lowersubnoanim_command,          // a7
	beatupfailtext_command,          // a8
	clearmissdamage_command,         // a9
	movedelay_command,               // aa
	moveanim_command,                // ab
	tristatuschance_command,         // ac
	supereffectivelooptext_command,  // ad
	startloop_command,               // ae
	curl_command,                    // af
};

#define NUM_EFFECT_COMMANDS curl_command

enum {
	endmove_command = 0xff,          // ff
	endturn_command = 0xfe,          // fe
};