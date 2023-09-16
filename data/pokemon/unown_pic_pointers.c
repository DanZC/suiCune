#include "../../constants.h"
#include "unown_pic_pointers.h"
#include "../../gfx/pics.h"

const char* UnownPicPointers[][2] = {
// entries correspond to Unown letters, two apiece
// table_width 3 * 2, UnownPicPointers
	[UNOWN_A-1] = { UnownAFrontpic, UnownABackpic },
	[UNOWN_B-1] = { UnownBFrontpic, UnownBBackpic },
	[UNOWN_C-1] = { UnownCFrontpic, UnownCBackpic },
	[UNOWN_D-1] = { UnownDFrontpic, UnownDBackpic },
	[UNOWN_E-1] = { UnownEFrontpic, UnownEBackpic },
	[UNOWN_F-1] = { UnownFFrontpic, UnownFBackpic },
	[UNOWN_G-1] = { UnownGFrontpic, UnownGBackpic },
	[UNOWN_H-1] = { UnownHFrontpic, UnownHBackpic },
	[UNOWN_I-1] = { UnownIFrontpic, UnownIBackpic },
	[UNOWN_J-1] = { UnownJFrontpic, UnownJBackpic },
	[UNOWN_K-1] = { UnownKFrontpic, UnownKBackpic },
	[UNOWN_L-1] = { UnownLFrontpic, UnownLBackpic },
	[UNOWN_M-1] = { UnownMFrontpic, UnownMBackpic },
	[UNOWN_N-1] = { UnownNFrontpic, UnownNBackpic },
	[UNOWN_O-1] = { UnownOFrontpic, UnownOBackpic },
	[UNOWN_P-1] = { UnownPFrontpic, UnownPBackpic },
	[UNOWN_Q-1] = { UnownQFrontpic, UnownQBackpic },
	[UNOWN_R-1] = { UnownRFrontpic, UnownRBackpic },
	[UNOWN_S-1] = { UnownSFrontpic, UnownSBackpic },
	[UNOWN_T-1] = { UnownTFrontpic, UnownTBackpic },
	[UNOWN_U-1] = { UnownUFrontpic, UnownUBackpic },
	[UNOWN_V-1] = { UnownVFrontpic, UnownVBackpic },
	[UNOWN_W-1] = { UnownWFrontpic, UnownWBackpic },
	[UNOWN_X-1] = { UnownXFrontpic, UnownXBackpic },
	[UNOWN_Y-1] = { UnownYFrontpic, UnownYBackpic },
	[UNOWN_Z-1] = { UnownZFrontpic, UnownZBackpic },
};
static_assert(lengthof(UnownPicPointers) == NUM_UNOWN, "");
