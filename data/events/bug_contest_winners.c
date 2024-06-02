#include "../../constants.h"

// contestant format:
//   db class, id
//   dbw 1st-place mon, score
//   dbw 2nd-place mon, score
//   dbw 3rd-place mon, score

const struct BugContestant BugContestant_BugCatcherDon = {
    BUG_CATCHER, DON, {
        {KAKUNA,     300},
        {METAPOD,    285},
        {CATERPIE,   226},
    },
};

const struct BugContestant BugContestant_BugCatcherEd = {
    BUG_CATCHER, ED, {
        {BUTTERFREE, 286},
        {BUTTERFREE, 251},
        {CATERPIE,   237},
    }
};

const struct BugContestant BugContestant_CooltrainerMNick = {
    COOLTRAINERM, NICK, {
        {SCYTHER,    357},
        {BUTTERFREE, 349},
        {PINSIR,     368},
    },
};

const struct BugContestant BugContestant_PokefanMWilliam = {
    POKEFANM, WILLIAM, {
        {PINSIR,     332},
        {BUTTERFREE, 324},
        {VENONAT,    321},
    },
};

const struct BugContestant BugContestant_BugCatcherBenny = {
    BUG_CATCHER, BUG_CATCHER_BENNY, {
        {BUTTERFREE, 318},
        {WEEDLE,     295},
        {CATERPIE,   285},
    },
};

const struct BugContestant BugContestant_CamperBarry = {
    CAMPER, BARRY, {
        {PINSIR,     366},
        {VENONAT,    329},
        {KAKUNA,     314},
    },
};

const struct BugContestant BugContestant_PicnickerCindy = {
    PICNICKER, CINDY, {
        {BUTTERFREE, 341},
        {METAPOD,    301},
        {CATERPIE,   264},
    },
};

const struct BugContestant BugContestant_BugCatcherJosh = {
    BUG_CATCHER, JOSH, {
        {SCYTHER,    326},
        {BUTTERFREE, 292},
        {METAPOD,    282},
    },
};

const struct BugContestant BugContestant_YoungsterSamuel = {
    YOUNGSTER, SAMUEL, {
        {WEEDLE,     270},
        {PINSIR,     282},
        {CATERPIE,   251},
    },
};

const struct BugContestant BugContestant_SchoolboyKipp = {
    SCHOOLBOY, KIPP, {
        {VENONAT,    267},
        {PARAS,      254},
        {KAKUNA,     259},
    },
};

const struct BugContestant* const BugContestantPointers[] = {
// table_width 2, BugContestantPointers
    &BugContestant_BugCatcherDon, // this reverts back to the player
    &BugContestant_BugCatcherDon,
    &BugContestant_BugCatcherEd,
    &BugContestant_CooltrainerMNick,
    &BugContestant_PokefanMWilliam,
    &BugContestant_BugCatcherBenny,
    &BugContestant_CamperBarry,
    &BugContestant_PicnickerCindy,
    &BugContestant_BugCatcherJosh,
    &BugContestant_YoungsterSamuel,
    &BugContestant_SchoolboyKipp,
};
static_assert(lengthof(BugContestantPointers) == NUM_BUG_CONTESTANTS + 1, "");