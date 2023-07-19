#include <stdint.h>
#include <stdbool.h>
#include "debugmenu.h"

typedef enum {
	DEBUGMENU_FIGHT,
	DEBUGMENU_FIELD,
	DEBUGMENU_SOUNDTEST,
	DEBUGMENU_SUBGAME,
	DEBUGMENU_POKEDEX,
	DEBUGMENU_TRAINERGEAR,
	NUM_DEBUGMENU_OPTIONS
} DebugMenuOption;