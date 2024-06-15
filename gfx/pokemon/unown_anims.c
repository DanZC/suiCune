#include "../../constants.h"
#include "unown_a/anim.h"
#include "unown_b/anim.h"
#include "unown_c/anim.h"
#include "unown_d/anim.h"
#include "unown_e/anim.h"
#include "unown_f/anim.h"
#include "unown_g/anim.h"
#include "unown_h/anim.h"
#include "unown_i/anim.h"
#include "unown_j/anim.h"
#include "unown_k/anim.h"
#include "unown_l/anim.h"
#include "unown_m/anim.h"
#include "unown_n/anim.h"
#include "unown_o/anim.h"
#include "unown_p/anim.h"
#include "unown_q/anim.h"
#include "unown_r/anim.h"
#include "unown_s/anim.h"
#include "unown_t/anim.h"
#include "unown_u/anim.h"
#include "unown_v/anim.h"
#include "unown_w/anim.h"
#include "unown_x/anim.h"
#include "unown_y/anim.h"
#include "unown_z/anim.h"

const uint8_t* UnownAnimationPointers[] = {
    [UNOWN_A-1] = UnownAAnimation,
    [UNOWN_B-1] = UnownBAnimation,
    [UNOWN_C-1] = UnownCAnimation,
    [UNOWN_D-1] = UnownDAnimation,
    [UNOWN_E-1] = UnownEAnimation,
    [UNOWN_F-1] = UnownFAnimation,
    [UNOWN_G-1] = UnownGAnimation,
    [UNOWN_H-1] = UnownHAnimation,
    [UNOWN_I-1] = UnownIAnimation,
    [UNOWN_J-1] = UnownJAnimation,
    [UNOWN_K-1] = UnownKAnimation,
    [UNOWN_L-1] = UnownLAnimation,
    [UNOWN_M-1] = UnownMAnimation,
    [UNOWN_N-1] = UnownNAnimation,
    [UNOWN_O-1] = UnownOAnimation,
    [UNOWN_P-1] = UnownPAnimation,
    [UNOWN_Q-1] = UnownQAnimation,
    [UNOWN_R-1] = UnownRAnimation,
    [UNOWN_S-1] = UnownSAnimation,
    [UNOWN_T-1] = UnownTAnimation,
    [UNOWN_U-1] = UnownUAnimation,
    [UNOWN_V-1] = UnownVAnimation,
    [UNOWN_W-1] = UnownWAnimation,
    [UNOWN_X-1] = UnownXAnimation,
    [UNOWN_Y-1] = UnownYAnimation,
    [UNOWN_Z-1] = UnownZAnimation,
};
static_assert(lengthof(UnownAnimationPointers) == NUM_UNOWN, "");
