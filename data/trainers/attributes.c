#include "../../constants.h"

const struct TrainerClassAttr TrainerClassAttributes[] = {
    [FALKNER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [WHITNEY] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BUGSY] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [MORTY] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [PRYCE] = {
        .items={ HYPER_POTION, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [JASMINE] = {
        .items={ HYPER_POTION, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [CHUCK] = {
        .items={ FULL_HEAL, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [CLAIR] = {
        .items={ FULL_HEAL, HYPER_POTION },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [RIVAL1] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=15,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [WILL] = {
        .items={ MAX_POTION, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [CAL] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BRUNO] = {
        .items={ MAX_POTION, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [KAREN] = {
        .items={ FULL_HEAL, MAX_POTION },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [KOGA] = {
        .items={ FULL_HEAL, FULL_RESTORE },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [CHAMPION] = {
        .items={ FULL_HEAL, FULL_RESTORE },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BROCK] = {
        .items={ HYPER_POTION, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [MISTY] = {
        .items={ FULL_HEAL, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [LT_SURGE] = {
        .items={ HYPER_POTION, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [SCIENTIST] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [ERIKA] = {
        .items={ HYPER_POTION, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [YOUNGSTER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=4,
        .aiMoveWeights=(AI_BASIC | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [SCHOOLBOY] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=8,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_OFTEN)
    },
    [BIRD_KEEPER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=6,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_OFFENSIVE | AI_OPPORTUNIST | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [LASS] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=6,
        .aiMoveWeights=(AI_BASIC | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_OFTEN)
    },
    [JANINE] = {
        .items={ DIRE_HIT, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [COOLTRAINERM] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=12,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [COOLTRAINERF] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=12,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BEAUTY] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=22,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [POKEMANIAC] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=15,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_OFFENSIVE | AI_AGGRESSIVE | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [GRUNTM] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=10,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [GENTLEMAN] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=18,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_AGGRESSIVE | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [SKIER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=18,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [TEACHER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=18,
        .aiMoveWeights=(AI_BASIC | AI_OPPORTUNIST | AI_AGGRESSIVE | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [SABRINA] = {
        .items={ HYPER_POTION, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BUG_CATCHER] = {
	    .items={ NO_ITEM, NO_ITEM },
	    .baseMoney=4,
	    .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_STATUS),
	    .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [FISHER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=10,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_OFTEN)
    },
    [SWIMMERM] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=2,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_OFFENSIVE | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [SWIMMERF] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=5,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [SAILOR] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=10,
        .aiMoveWeights=(AI_BASIC | AI_OFFENSIVE | AI_OPPORTUNIST | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [SUPER_NERD] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=8,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_SMART | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [RIVAL2] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [GUITARIST] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=8,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [HIKER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=8,
        .aiMoveWeights=(AI_BASIC | AI_OFFENSIVE | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BIKER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=8,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BLAINE] = {
        .items={ MAX_POTION, FULL_HEAL },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BURGLAR] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=22,
        .aiMoveWeights=(AI_BASIC | AI_OFFENSIVE | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [FIREBREATHER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=12,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_OFFENSIVE | AI_OPPORTUNIST | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [JUGGLER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=10,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_SMART | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BLACKBELT_T] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=6,
        .aiMoveWeights=(AI_BASIC | AI_OFFENSIVE | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [EXECUTIVEM] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=18,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_SMART | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [PSYCHIC_T] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=8,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [PICNICKER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=5,
        .aiMoveWeights=(AI_BASIC | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [CAMPER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=5,
        .aiMoveWeights=(AI_BASIC | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [EXECUTIVEF] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=18,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_SMART | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [SAGE] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=8,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [MEDIUM] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=10,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_TYPES | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BOARDER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=18,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_OPPORTUNIST | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [POKEFANM] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=20,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_SMART | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [KIMONO_GIRL] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=18,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [TWINS] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=5,
        .aiMoveWeights=(NO_AI),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_OFTEN)
    },
    [POKEFANF] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=20,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_SMART | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [RED] = {
        .items={ FULL_RESTORE, FULL_RESTORE },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [BLUE] = {
        .items={ FULL_RESTORE, FULL_RESTORE },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [OFFICER] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=10,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_OPPORTUNIST | AI_STATUS),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [GRUNTF] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=10,
        .aiMoveWeights=(AI_BASIC | AI_TYPES | AI_OPPORTUNIST | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [MYSTICALMAN] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
    [JODI] = {
        .items={ NO_ITEM, NO_ITEM },
        .baseMoney=25,
        .aiMoveWeights=(AI_BASIC | AI_SETUP | AI_SMART | AI_AGGRESSIVE | AI_CAUTIOUS | AI_STATUS | AI_RISKY),
        .aiItemSwitch=(CONTEXT_USE | SWITCH_SOMETIMES)
    },
};

static_assert(lengthof(TrainerClassAttributes) == NUM_TRAINER_CLASSES + 1, "");
