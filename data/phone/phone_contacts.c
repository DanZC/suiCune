#include "../../constants.h"
#include "phone_contacts.h"
#include "../../engine/phone/scripts/mom.h"
#include "../../engine/phone/scripts/bill.h"
#include "../../engine/phone/scripts/elm.h"
#include "../../engine/phone/scripts/jack.h"
#include "../../engine/phone/scripts/beverly.h"
#include "../../engine/phone/scripts/huey.h"
#include "../../engine/phone/scripts/gaven.h"
#include "../../engine/phone/scripts/beth.h"
#include "../../engine/phone/scripts/jose.h"
#include "../../engine/phone/scripts/reena.h"
#include "../../engine/phone/scripts/joey.h"
#include "../../engine/phone/scripts/wade.h"
#include "../../engine/phone/scripts/ralph.h"
#include "../../engine/phone/scripts/liz.h"
#include "../../engine/phone/scripts/anthony.h"
#include "../../engine/phone/scripts/todd.h"
#include "../../engine/phone/scripts/gina.h"
#include "../../engine/phone/scripts/irwin.h"
#include "../../engine/phone/scripts/arnie.h"
#include "../../engine/phone/scripts/alan.h"
#include "../../engine/phone/scripts/dana.h"
#include "../../engine/phone/scripts/chad.h"
#include "../../engine/phone/scripts/derek.h"
#include "../../engine/phone/scripts/tully.h"
#include "../../engine/phone/scripts/brent.h"
#include "../../engine/phone/scripts/tiffany.h"
#include "../../engine/phone/scripts/vance.h"
#include "../../engine/phone/scripts/wilton.h"
#include "../../engine/phone/scripts/kenji.h"
#include "../../engine/phone/scripts/parry.h"
#include "../../engine/phone/scripts/erin.h"
#include "../../engine/phone/scripts/buena.h"
#include "../../engine/phone/scripts/unused.h"

#define phone(_tc, _tid, _map, _callee_time, _callee_script, _caller_time, _caller_script) {_tc, _tid, MAP_ID(_map), _callee_time, _callee_script, _caller_time, _caller_script}

const struct PhoneContact PhoneContacts[] = {
// entries correspond to PHONE_* constants
    [PHONE_00]                  = phone(TRAINER_NONE, PHONE_00,              N_A,                       0,       UnusedPhoneScript,        0,       UnusedPhoneScript),
    [PHONE_MOM]                 = phone(TRAINER_NONE, PHONECONTACT_MOM,      PLAYERS_HOUSE_1F,          ANYTIME, MomPhoneCalleeScript,     0,       UnusedPhoneScript),
    [PHONE_OAK]                 = phone(TRAINER_NONE, PHONECONTACT_BIKESHOP, OAKS_LAB,                  0,       UnusedPhoneScript,        0,       UnusedPhoneScript),
    [PHONE_BILL]                = phone(TRAINER_NONE, PHONECONTACT_BILL,     N_A,                       ANYTIME, BillPhoneCalleeScript,    0,       BillPhoneCallerScript),
    [PHONE_ELM]                 = phone(TRAINER_NONE, PHONECONTACT_ELM,      ELMS_LAB,                  ANYTIME, ElmPhoneCalleeScript,     0,       ElmPhoneCallerScript),
    [PHONE_SCHOOLBOY_JACK]      = phone(SCHOOLBOY,    JACK1,                 NATIONAL_PARK,             ANYTIME, JackPhoneCalleeScript,    ANYTIME, JackPhoneCallerScript),
    [PHONE_POKEFAN_BEVERLY]     = phone(POKEFANF,     BEVERLY1,              NATIONAL_PARK,             ANYTIME, BeverlyPhoneCalleeScript, ANYTIME, BeverlyPhoneCallerScript),
    [PHONE_SAILOR_HUEY]         = phone(SAILOR,       HUEY1,                 OLIVINE_LIGHTHOUSE_2F,     ANYTIME, HueyPhoneCalleeScript,    ANYTIME, HueyPhoneCallerScript),
    [PHONE_UNUSED_01]           = phone(TRAINER_NONE, PHONE_00,              N_A,                       0,       UnusedPhoneScript,        0,       UnusedPhoneScript),
    [PHONE_UNUSED_02]           = phone(TRAINER_NONE, PHONE_00,              N_A,                       0,       UnusedPhoneScript,        0,       UnusedPhoneScript),
    [PHONE_UNUSED_03]           = phone(TRAINER_NONE, PHONE_00,              N_A,                       0,       UnusedPhoneScript,        0,       UnusedPhoneScript),
    [PHONE_COOLTRAINERM_GAVEN]  = phone(COOLTRAINERM, GAVEN3,                ROUTE_26,                  ANYTIME, GavenPhoneCalleeScript,   ANYTIME, GavenPhoneCallerScript),
    [PHONE_COOLTRAINERF_BETH]   = phone(COOLTRAINERF, BETH1,                 ROUTE_26,                  ANYTIME, BethPhoneCalleeScript,    ANYTIME, BethPhoneCallerScript),
    [PHONE_BIRDKEEPER_JOSE]     = phone(BIRD_KEEPER,  JOSE2,                 ROUTE_27,                  ANYTIME, JosePhoneCalleeScript,    ANYTIME, JosePhoneCallerScript),
    [PHONE_COOLTRAINERF_REENA]  = phone(COOLTRAINERF, REENA1,                ROUTE_27,                  ANYTIME, ReenaPhoneCalleeScript,   ANYTIME, ReenaPhoneCallerScript),
    [PHONE_YOUNGSTER_JOEY]      = phone(YOUNGSTER,    JOEY1,                 ROUTE_30,                  ANYTIME, JoeyPhoneCalleeScript,    ANYTIME, JoeyPhoneCallerScript),
    [PHONE_BUG_CATCHER_WADE]    = phone(BUG_CATCHER,  WADE1,                 ROUTE_31,                  ANYTIME, WadePhoneCalleeScript,    ANYTIME, WadePhoneCallerScript),
    [PHONE_FISHER_RALPH]        = phone(FISHER,       RALPH1,                ROUTE_32,                  ANYTIME, RalphPhoneCalleeScript,   ANYTIME, RalphPhoneCallerScript),
    [PHONE_PICNICKER_LIZ]       = phone(PICNICKER,    LIZ1,                  ROUTE_32,                  ANYTIME, LizPhoneCalleeScript,     ANYTIME, LizPhoneCallerScript),
    [PHONE_HIKER_ANTHONY]       = phone(HIKER,        ANTHONY2,              ROUTE_33,                  ANYTIME, AnthonyPhoneCalleeScript, ANYTIME, AnthonyPhoneCallerScript),
    [PHONE_CAMPER_TODD]         = phone(CAMPER,       TODD1,                 ROUTE_34,                  ANYTIME, ToddPhoneCalleeScript,    ANYTIME, ToddPhoneCallerScript),
    [PHONE_PICNICKER_GINA]      = phone(PICNICKER,    GINA1,                 ROUTE_34,                  ANYTIME, GinaPhoneCalleeScript,    ANYTIME, GinaPhoneCallerScript),
    [PHONE_JUGGLER_IRWIN]       = phone(JUGGLER,      IRWIN1,                ROUTE_35,                  ANYTIME, IrwinPhoneCalleeScript,   ANYTIME, IrwinPhoneCallerScript),
    [PHONE_BUG_CATCHER_ARNIE]   = phone(BUG_CATCHER,  ARNIE1,                ROUTE_35,                  ANYTIME, ArniePhoneCalleeScript,   ANYTIME, ArniePhoneCallerScript),
    [PHONE_SCHOOLBOY_ALAN]      = phone(SCHOOLBOY,    ALAN1,                 ROUTE_36,                  ANYTIME, AlanPhoneCalleeScript,    ANYTIME, AlanPhoneCallerScript),
    [PHONE_UNUSED_04]           = phone(TRAINER_NONE, PHONE_00,              N_A,                       0,       UnusedPhoneScript,        0,       UnusedPhoneScript),
    [PHONE_LASS_DANA]           = phone(LASS,         DANA1,                 ROUTE_38,                  ANYTIME, DanaPhoneCalleeScript,    ANYTIME, DanaPhoneCallerScript),
    [PHONE_SCHOOLBOY_CHAD]      = phone(SCHOOLBOY,    CHAD1,                 ROUTE_38,                  ANYTIME, ChadPhoneCalleeScript,    ANYTIME, ChadPhoneCallerScript),
    [PHONE_POKEFANM_DEREK]      = phone(POKEFANM,     DEREK1,                ROUTE_39,                  ANYTIME, DerekPhoneCalleeScript,   ANYTIME, DerekPhoneCallerScript),
    [PHONE_FISHER_TULLY]        = phone(FISHER,       TULLY1,                ROUTE_42,                  ANYTIME, TullyPhoneCalleeScript,   ANYTIME, TullyPhoneCallerScript),
    [PHONE_POKEMANIAC_BRENT]    = phone(POKEMANIAC,   BRENT1,                ROUTE_43,                  ANYTIME, BrentPhoneCalleeScript,   ANYTIME, BrentPhoneCallerScript),
    [PHONE_PICNICKER_TIFFANY]   = phone(PICNICKER,    TIFFANY3,              ROUTE_43,                  ANYTIME, TiffanyPhoneCalleeScript, ANYTIME, TiffanyPhoneCallerScript),
    [PHONE_BIRDKEEPER_VANCE]    = phone(BIRD_KEEPER,  VANCE1,                ROUTE_44,                  ANYTIME, VancePhoneCalleeScript,   ANYTIME, VancePhoneCallerScript),
    [PHONE_FISHER_WILTON]       = phone(FISHER,       WILTON1,               ROUTE_44,                  ANYTIME, WiltonPhoneCalleeScript,  ANYTIME, WiltonPhoneCallerScript),
    [PHONE_BLACKBELT_KENJI]     = phone(BLACKBELT_T,  KENJI3,                ROUTE_45,                  ANYTIME, KenjiPhoneCalleeScript,   ANYTIME, KenjiPhoneCallerScript),
    [PHONE_HIKER_PARRY]         = phone(HIKER,        PARRY1,                ROUTE_45,                  ANYTIME, ParryPhoneCalleeScript,   ANYTIME, ParryPhoneCallerScript),
    [PHONE_PICNICKER_ERIN]      = phone(PICNICKER,    ERIN1,                 ROUTE_46,                  ANYTIME, ErinPhoneCalleeScript,    ANYTIME, ErinPhoneCallerScript),
    [PHONE_BUENA]               = phone(TRAINER_NONE, PHONECONTACT_BUENA,    GOLDENROD_DEPT_STORE_ROOF, ANYTIME, BuenaPhoneCalleeScript,   ANYTIME, BuenaPhoneCallerScript),
};

static_assert(lengthof(PhoneContacts) == NUM_PHONE_CONTACTS + 1, "");
