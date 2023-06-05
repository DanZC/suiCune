#include "../../constants.h"

const uint8_t TrainerEncounterMusic[] = {
    [0x00]         = {MUSIC_HIKER_ENCOUNTER}, // none
    [FALKNER]      = {MUSIC_YOUNGSTER_ENCOUNTER}, // falkner
    [WHITNEY]      = {MUSIC_LASS_ENCOUNTER}, // whitney
    [BUGSY]        = {MUSIC_YOUNGSTER_ENCOUNTER}, // bugsy
    [MORTY]        = {MUSIC_OFFICER_ENCOUNTER}, // morty
    [PRYCE]        = {MUSIC_OFFICER_ENCOUNTER}, // pryce
    [JASMINE]      = {MUSIC_LASS_ENCOUNTER}, // jasmine
    [CHUCK]        = {MUSIC_OFFICER_ENCOUNTER}, // chuck
    [CLAIR]        = {MUSIC_BEAUTY_ENCOUNTER}, // clair
    [RIVAL1]       = {MUSIC_RIVAL_ENCOUNTER}, // rival1
    [POKEMON_PROF] = {MUSIC_HIKER_ENCOUNTER}, // pokemon_prof
    [WILL]         = {MUSIC_HIKER_ENCOUNTER}, // will
    [CAL]          = {MUSIC_HIKER_ENCOUNTER}, // cal
    [BRUNO]        = {MUSIC_OFFICER_ENCOUNTER}, // bruno
    [KAREN]        = {MUSIC_HIKER_ENCOUNTER}, // karen
    [KOGA]         = {MUSIC_HIKER_ENCOUNTER}, // koga
    [CHAMPION]     = {MUSIC_OFFICER_ENCOUNTER}, // champion
    [BROCK]        = {MUSIC_YOUNGSTER_ENCOUNTER}, // brock
    [MISTY]        = {MUSIC_LASS_ENCOUNTER}, // misty
    [LT_SURGE]     = {MUSIC_OFFICER_ENCOUNTER}, // lt_surge
    [SCIENTIST]    = {MUSIC_ROCKET_ENCOUNTER}, // scientist
    [ERIKA]        = {MUSIC_OFFICER_ENCOUNTER}, // erika
    [YOUNGSTER]    = {MUSIC_YOUNGSTER_ENCOUNTER}, // youngster
    [SCHOOLBOY]    = {MUSIC_YOUNGSTER_ENCOUNTER}, // schoolboy
    [BIRD_KEEPER]  = {MUSIC_YOUNGSTER_ENCOUNTER}, // bird_keeper
    [LASS]         = {MUSIC_LASS_ENCOUNTER}, // lass
    [JANINE]       = {MUSIC_LASS_ENCOUNTER}, // janine
    [COOLTRAINERM] = {MUSIC_HIKER_ENCOUNTER}, // cooltrainerm
    [COOLTRAINERF] = {MUSIC_BEAUTY_ENCOUNTER}, // cooltrainerf
    [BEAUTY]       = {MUSIC_BEAUTY_ENCOUNTER}, // beauty
    [POKEMANIAC]   = {MUSIC_POKEMANIAC_ENCOUNTER}, // pokemaniac
    [GRUNTM]       = {MUSIC_ROCKET_ENCOUNTER}, // gruntm
    [GENTLEMAN]    = {MUSIC_HIKER_ENCOUNTER}, // gentleman
    [SKIER]        = {MUSIC_BEAUTY_ENCOUNTER}, // skier
    [TEACHER]      = {MUSIC_BEAUTY_ENCOUNTER}, // teacher
    [SABRINA]      = {MUSIC_BEAUTY_ENCOUNTER}, // sabrina
    [BUG_CATCHER]  = {MUSIC_YOUNGSTER_ENCOUNTER}, // bug_catcher
    [FISHER]       = {MUSIC_HIKER_ENCOUNTER}, // fisher
    [SWIMMERM]     = {MUSIC_HIKER_ENCOUNTER}, // swimmerm
    [SWIMMERF]     = {MUSIC_BEAUTY_ENCOUNTER}, // swimmerf
    [SAILOR]       = {MUSIC_HIKER_ENCOUNTER}, // sailor
    [SUPER_NERD]   = {MUSIC_POKEMANIAC_ENCOUNTER}, // super_nerd
    [RIVAL2]       = {MUSIC_RIVAL_ENCOUNTER}, // rival2
    [GUITARIST]    = {MUSIC_HIKER_ENCOUNTER}, // guitarist
    [HIKER]        = {MUSIC_HIKER_ENCOUNTER}, // hiker
    [BIKER]        = {MUSIC_HIKER_ENCOUNTER}, // biker
    [BLAINE]       = {MUSIC_OFFICER_ENCOUNTER}, // blaine
    [BURGLAR]      = {MUSIC_POKEMANIAC_ENCOUNTER}, // burglar
    [FIREBREATHER] = {MUSIC_HIKER_ENCOUNTER}, // firebreather
    [JUGGLER]      = {MUSIC_POKEMANIAC_ENCOUNTER}, // juggler
    [BLACKBELT_T]  = {MUSIC_HIKER_ENCOUNTER}, // blackbelt_t
    [EXECUTIVEM]   = {MUSIC_ROCKET_ENCOUNTER}, // executivem
    [PSYCHIC_T]    = {MUSIC_YOUNGSTER_ENCOUNTER}, // psychic_t
    [PICNICKER]    = {MUSIC_LASS_ENCOUNTER}, // picnicker
    [CAMPER]       = {MUSIC_YOUNGSTER_ENCOUNTER}, // camper
    [EXECUTIVEF]   = {MUSIC_ROCKET_ENCOUNTER}, // executivef
    [SAGE]         = {MUSIC_SAGE_ENCOUNTER}, // sage
    [MEDIUM]       = {MUSIC_SAGE_ENCOUNTER}, // medium
    [BOARDER]      = {MUSIC_HIKER_ENCOUNTER}, // boarder
    [POKEFANM]     = {MUSIC_HIKER_ENCOUNTER}, // pokefanm
    [KIMONO_GIRL]  = {MUSIC_KIMONO_ENCOUNTER}, // kimono_girl
    [TWINS]        = {MUSIC_LASS_ENCOUNTER}, // twins
    [POKEFANF]     = {MUSIC_BEAUTY_ENCOUNTER}, // pokefanf
    [RED]          = {MUSIC_HIKER_ENCOUNTER}, // red
    [BLUE]         = {MUSIC_RIVAL_ENCOUNTER}, // blue
    [OFFICER]      = {MUSIC_HIKER_ENCOUNTER}, // officer
    [GRUNTF]       = {MUSIC_ROCKET_ENCOUNTER}, // gruntf
    [MYSTICALMAN]  = {MUSIC_HIKER_ENCOUNTER}, // mysticalman
};

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(lengthof(TrainerEncounterMusic) == NUM_TRAINER_CLASSES + 1, "");
#else
_Static_assert(lengthof(TrainerEncounterMusic) == NUM_TRAINER_CLASSES + 1, "");
#endif