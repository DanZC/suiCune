#include "../../constants.h"

const struct DVSet TrainerClassDVs[] = {
// entries correspond to trainer classes (see constants/trainer_constants.asm)
	//table_width 2, TrainerClassDVs
	//  atk,def,spd,spc
	[FALKNER-1]         = { 9, 10,  7,  7 }, // FALKNER
	[WHITNEY-1]         = { 8,  8,  8,  8 }, // WHITNEY
	[BUGSY-1]           = { 9,  8,  8,  8 }, // BUGSY
	[MORTY-1]           = { 9,  8,  8,  8 }, // MORTY
	[PRYCE-1]           = { 9,  8,  8,  8 }, // PRYCE
	[JASMINE-1]         = { 9,  8,  8,  8 }, // JASMINE
	[CHUCK-1]           = { 9,  8,  8,  8 }, // CHUCK
	[CLAIR-1]           = { 7, 12, 13, 13 }, // CLAIR
	[RIVAL1-1]          = {13, 13, 13, 13 }, // RIVAL1
	[POKEMON_PROF-1]    = { 9,  8,  8,  8 }, // POKEMON_PROF
	[WILL-1]            = {13, 12, 13, 13 }, // WILL
	[CAL-1]             = {13, 12, 13, 13 }, // CAL
	[BRUNO-1]           = {13, 12, 13, 13 }, // BRUNO
	[KAREN-1]           = { 7, 15, 13, 15 }, // KAREN
	[KOGA-1]            = {13, 12, 13, 13 }, // KOGA
	[CHAMPION-1]        = {13, 12, 13, 13 }, // CHAMPION
	[BROCK-1]           = { 9,  8,  8,  8 }, // BROCK
	[MISTY-1]           = { 7,  8,  8,  8 }, // MISTY
	[LT_SURGE-1]        = { 9,  8,  8,  8 }, // LT_SURGE
	[SCIENTIST-1]       = { 9,  8,  8,  8 }, // SCIENTIST
	[ERIKA-1]           = { 7,  8,  8,  8 }, // ERIKA
	[YOUNGSTER-1]       = { 9,  8,  8,  8 }, // YOUNGSTER
	[SCHOOLBOY-1]       = { 9,  8,  8,  8 }, // SCHOOLBOY
	[BIRD_KEEPER-1]     = { 9,  8,  8,  8 }, // BIRD_KEEPER
	[LASS-1]            = { 5,  8,  8,  8 }, // LASS
	[JANINE-1]          = { 9,  8,  8,  8 }, // JANINE
	[COOLTRAINERM-1]    = {13,  8, 12,  8 }, // COOLTRAINERM
	[COOLTRAINERF-1]    = { 7, 12, 12,  8 }, // COOLTRAINERF
	[BEAUTY-1]          = { 6,  9, 12,  8 }, // BEAUTY
	[POKEMANIAC-1]      = { 9,  8,  8,  8 }, // POKEMANIAC
	[GRUNTM-1]          = {13,  8, 10,  8 }, // GRUNTM
	[GENTLEMAN-1]       = { 9,  8,  8,  8 }, // GENTLEMAN
	[SKIER-1]           = { 9,  8,  8,  8 }, // SKIER
	[TEACHER-1]         = { 6,  8,  8,  8 }, // TEACHER
	[SABRINA-1]         = { 7, 13,  8,  7 }, // SABRINA
	[BUG_CATCHER-1]     = { 9,  8,  8,  8 }, // BUG_CATCHER
	[FISHER-1]          = { 9,  8,  8,  8 }, // FISHER
	[SWIMMERM-1]        = { 9,  8,  8,  8 }, // SWIMMERM
	[SWIMMERF-1]        = { 7,  8,  8,  8 }, // SWIMMERF
	[SAILOR-1]          = { 9,  8,  8,  8 }, // SAILOR
	[SUPER_NERD-1]      = { 9,  8,  8,  8 }, // SUPER_NERD
	[RIVAL2-1]          = { 9,  8,  8,  8 }, // RIVAL2
	[GUITARIST-1]       = { 9,  8,  8,  8 }, // GUITARIST
	[HIKER-1]           = {10,  8,  8,  8 }, // HIKER
	[BIKER-1]           = { 9,  8,  8,  8 }, // BIKER
	[BLAINE-1]          = { 9,  8,  8,  8 }, // BLAINE
	[BURGLAR-1]         = { 9,  8,  8,  8 }, // BURGLAR
	[FIREBREATHER-1]    = { 9,  8,  8,  8 }, // FIREBREATHER
	[JUGGLER-1]         = { 9,  8,  8,  8 }, // JUGGLER
	[BLACKBELT_T-1]     = { 9,  8,  8,  8 }, // BLACKBELT_T
	[EXECUTIVEM-1]      = {13,  8, 10,  8 }, // EXECUTIVEM
	[PSYCHIC_T-1]       = { 9,  8,  8,  8 }, // PSYCHIC_T
	[PICNICKER-1]       = { 6, 10, 10,  8 }, // PICNICKER
	[CAMPER-1]          = { 9,  8,  8,  8 }, // CAMPER
	[EXECUTIVEF-1]      = { 7, 14, 10,  8 }, // EXECUTIVEF
	[SAGE-1]            = { 9,  8,  8,  8 }, // SAGE
	[MEDIUM-1]          = { 7,  8,  8,  8 }, // MEDIUM
	[BOARDER-1]         = { 9,  8,  8,  8 }, // BOARDER
	[POKEFANM-1]        = { 9,  8,  8,  8 }, // POKEFANM
	[KIMONO_GIRL-1]     = { 6,  8,  8, 10 }, // KIMONO_GIRL
	[TWINS-1]           = { 6,  8, 10,  8 }, // TWINS
	[POKEFANF-1]        = { 6, 13,  8,  8 }, // POKEFANF
	[RED-1]             = {15, 13, 13, 14 }, // RED
	[BLUE-1]            = { 9, 13, 13, 13 }, // BLUE
	[OFFICER-1]         = { 9,  8,  8,  8 }, // OFFICER
	[GRUNTF-1]          = { 7, 14, 10,  8 }, // GRUNTF
	[MYSTICALMAN-1]     = { 9,  8,  8,  8 }, // MYSTICALMAN
	[JODI-1]            = {13, 12, 13, 13 }, // JODI
};

static_assert(lengthof(TrainerClassDVs) == NUM_TRAINER_CLASSES, "");
